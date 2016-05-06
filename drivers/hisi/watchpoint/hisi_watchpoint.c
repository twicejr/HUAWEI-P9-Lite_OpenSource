/*
 * hisi_watchpoint.c - HW watchpoint file to watch kernel address
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 */
#define MERROR_LEVEL    1
#define MWARNING_LEVEL  1
#define MNOTICE_LEVEL   1
#define MINFO_LEVEL     1
#define MDEBUG_LEVEL    0
#define MLOG_TAG        "watchpoint"

#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_ERR */
#include <linux/init.h>		/* Needed for the macros */
#include <linux/slab.h>
#include <linux/kallsyms.h>

#include <linux/perf_event.h>
#include <linux/hw_breakpoint.h>
#include <linux/hisi/util.h>
#ifdef CONFIG_DEBUG_FS
#include <linux/debugfs.h>
#endif
#include "../mntn/mntn_log.h"
#include "hisi_watchpoint.h"

/*#define __WP_STARTUP_SUPPORT__*/

/* Variable */
static struct wp_strct wp_info[ARM_MAX_BRP];
static int wp_info_num;
#ifdef __WP_STARTUP_SUPPORT__
static void *pe_addr;
#endif
#ifdef CONFIG_DEBUG_FS
static struct dentry *wp_df_dir;	/* debugfs dir */
static char *tget_mem_addr;
static unsigned int tget_mem_size;
static unsigned int tacc_value;
#endif

static int wp_find_pe(void *ibp_addr, struct perf_event *__percpu **ppe)
{
	int idx;

	for (idx = 0; idx < ARM_MAX_BRP; idx++) {
		if (wp_info[idx].wp_addr == ibp_addr) {
			if (ppe != NULL) {
				*ppe = wp_info[idx].wp_hbp;
			}
			break;
		}
	}

	if (idx == ARM_MAX_BRP) {
		mlog_e("cannot find the addr(0x%p)\n", ibp_addr);
		return -1;
	}

	return idx;
}

static int wp_add_pe(int idx, void *ibp_addr, unsigned int ibp_len,
		     unsigned int ibp_type, struct perf_event *__percpu *pe)
{
	wp_info[idx].wp_addr = ibp_addr;
	wp_info[idx].wp_len = ibp_len;
	wp_info[idx].wp_type = ibp_type;
	wp_info[idx].wp_hbp = pe;

	/* register ensure the num bigger than ARM_MAX_BRP */
	wp_info_num++;

	if (wp_info_num > ARM_MAX_BRP) {
		mlog_e("wp_info_num(%d) overflowed\n", wp_info_num);
		return -1;
	}

	return 0;
}

static void wp_delete_pe(int idx)
{
	/* delete the cooresponding addr */
	wp_info[idx].wp_addr = NULL;
	wp_info[idx].wp_type = 0;
	wp_info[idx].wp_len = 0;
	wp_info[idx].wp_hbp = NULL;

	wp_info_num--;

	if (wp_info_num < 0) {
		mlog_e("wp_info_num underflowed\n");
		wp_info_num = 0;
	}

	return;
}

static void wp_hbp_handler(struct perf_event *bp,
			   struct perf_sample_data *data, struct pt_regs *regs)
{
	die("Watchpoint", regs, 0);
}

static int
wp_hbp_register(void *ibp_addr, unsigned int ibp_len, unsigned int ibp_type)
{
	struct perf_event *__percpu *pe;
	struct perf_event_attr attr;
	int ret, idx;

	mlog_i("Begin, addr=0x%p, len=%u, type=%d\n", ibp_addr, ibp_len,
	       ibp_type);

	/* init one watchpoint for startup watch */
	hw_breakpoint_init(&attr);
	attr.bp_addr = (__u64) ibp_addr;
	attr.bp_len = ibp_len;
	/*HW_BREAKPOINT_W | HW_BREAKPOINT_R */
	attr.bp_type = ibp_type;

	pe = register_wide_hw_breakpoint(&attr, wp_hbp_handler, NULL);
	if (IS_ERR((void __force *)pe)) {
		mlog_e("register failed, addr=0x%p\n", ibp_addr);
		ret = -1;

	} else {
		/* find and record pe in array */
		idx = wp_find_pe(NULL, NULL);
		if (idx >= 0) {
			ret = wp_add_pe(idx, ibp_addr, ibp_len, ibp_type, pe);

		} else {
			mlog_e("find space failed, addr=0x%p, idx=%d\n",
			       ibp_addr, idx);
			ret = -2;
		}

	}

	mlog_i("End, ret = %d\n", ret);

	return ret;
}

static void wp_hbp_unregister(void *ibp_addr)
{
	int idx;
	struct perf_event *__percpu *pe;

	mlog_i("Begin, addr=0x%p", ibp_addr);

	if (0 == wp_info_num) {
		mlog_e("wp_info_num is zero");
		return;
	}

	/* find pe according to addr */
	idx = wp_find_pe(ibp_addr, &pe);
	if (idx >= 0) {
		unregister_wide_hw_breakpoint(pe);

		/* delete the cooresponding addr */
		wp_delete_pe(idx);

	} else {
		mlog_e("error, addr=0x%p", ibp_addr);
	}

	mlog_i("End");

	return;
}

#ifdef CONFIG_DEBUG_FS
static void wp_state_dp(char *buf)
{
	int i;

	memset(buf, 0, WP_DBG_SIZE_PAGE);

	mlog_i("B");

	/* show watchpoint registered in array */
	buf += snprintf(buf, WP_DBG_SIZE_PAGE,
			"watchpoint registered num = %d\n",
			wp_info_num);
	for (i = 0; i < ARM_MAX_BRP; i++) {
		if (wp_info[i].wp_addr == NULL) {
			continue;
		}

		buf +=
		    snprintf(buf, WP_DBG_SIZE_PAGE, "[%d] addr = 0x%p\n", i,
			     wp_info[i].wp_addr);
		buf +=
		    snprintf(buf, WP_DBG_SIZE_PAGE, "[%d] len = %u\n", i,
			     wp_info[i].wp_len);
		buf +=
		    snprintf(buf, WP_DBG_SIZE_PAGE, "[%d] rw = %u\n", i,
			     wp_info[i].wp_type);
		buf +=
		    snprintf(buf, WP_DBG_SIZE_PAGE, "[%d] pe = 0x%p\n", i,
			     wp_info[i].wp_hbp);
	}
	buf += snprintf(buf, WP_DBG_SIZE_PAGE, "<end>\n");

	mlog_i("E");
}

/*
"stat" : state

cat stat
*/
static ssize_t wp_state_read(struct file *file, char __user *user_buf,
			     size_t count, loff_t *ppos)
{
	char *kn_buf = NULL;
	ssize_t byte_read = 0;

	mlog_i("Begin");

	kn_buf = kmalloc(WP_DBG_SIZE_PAGE, GFP_KERNEL);
	if (NULL == kn_buf) {
		mlog_e("kn_buf is null\n");
		return simple_read_from_buffer(user_buf, count, ppos,
					       "kn_buf alloc fail\n", 18);
	}

	wp_state_dp(kn_buf);

	byte_read =
	    simple_read_from_buffer(user_buf, count, ppos, kn_buf,
				    strlen(kn_buf));

	kfree(kn_buf);
	kn_buf = NULL;

	mlog_i("End");

	return byte_read;
}

/*
watchpoint config 说明
*/
static ssize_t wp_config_read(struct file *file, char __user *user_buf,
			      size_t count, loff_t *ppos)
{
	char *kn_buf = NULL;
	char *pt_kn_buf;
	ssize_t byte_read = 0;

	mlog_i("Begin");

	kn_buf = kmalloc(WP_DBG_SIZE_PAGE, GFP_KERNEL);
	if (NULL == kn_buf) {
		mlog_e("kn_buf is null\n");
		return simple_read_from_buffer(user_buf, count, ppos,
					       "kn_buf alloc fail\n", 18);
	}

	memset(kn_buf, 0, WP_DBG_SIZE_PAGE);

	pt_kn_buf = kn_buf;

	/* context */
	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE, "usage:\n");
	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE,
					"s addr size(4) rw(1-3)\n");
	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE,
					"    set watchpoint\n");
	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE,
					"    size: default is 4\n");
	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE,
					"    rw   : 1-r, 2-w, 3-rw\n");
	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE, "c addr\n");
	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE,
					"    clear watchpoint\n");

	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE, "<end>\n");

	byte_read = simple_read_from_buffer(user_buf,
					count, ppos, kn_buf, strlen(kn_buf));

	kfree(kn_buf);
	kn_buf = NULL;

	mlog_i("End");

	return byte_read;
}

/*
"cfg" : set/clear watchpoint

echo "s addr size rw" > cfg
echo "c addr" > cfg
*/
static ssize_t wp_config_write(struct file *file, const char __user *user_buf,
			       size_t count, loff_t *ppos)
{
	char *kn_buf = NULL;
	ssize_t byte_writen = 0;
	int num = 0;
	void *addr;
	unsigned int size, rw;

	mlog_i("Begin\n");

	kn_buf = kmalloc(WP_DBG_SIZE_PAGE, GFP_KERNEL);
	if (NULL == kn_buf) {
		mlog_e("kn_buf is null\n");
		return -EFAULT;
	}

	byte_writen = simple_write_to_buffer(kn_buf,
					WP_DBG_SIZE_PAGE, ppos, user_buf,
					count);

	if ('s' == kn_buf[0]) {
		/* set watchpoint */
		num =
		    sscanf(kn_buf, "s %lx %u %u", (unsigned long *)&addr, &size,
			   &rw);
		if (3 == num) {
			if (wp_hbp_register(addr, size, rw)) {
				/* fail */
				byte_writen = -EINVAL;
			}
		} else {
			mlog_e("sscanf err, num=%d", num);
			byte_writen = -EINVAL;
		}

	} else if ('c' == kn_buf[0]) {
		/* clear watchpoint */
		num = sscanf(kn_buf, "c %lx", (unsigned long *)&addr);
		mlog_e("sscanf addr=0x%p, num=%d", addr, num);
		if (1 == num) {
			if (addr != 0) {
				/* clear the specific addr */
				wp_hbp_unregister(addr);

			} else {
				byte_writen = -EINVAL;
			}

		} else {
			mlog_e("sscanf err, num=%d", num);
			byte_writen = -EINVAL;
		}

	} else {
		/* 异常 */
		byte_writen = -EINVAL;
	}

	kfree(kn_buf);
	kn_buf = NULL;

	mlog_i("End\n");

	return byte_writen;
}

/*
"tgetm" : get memory, for test

cat tgetm
	-- addr: 0x1000 //size: 0x1000 type: k/v/d
*/
static ssize_t wp_tgetmem_read(struct file *file, char __user *user_buf,
			       size_t count, loff_t *ppos)
{
	char *kn_buf = NULL;
	char *pt_kn_buf;
	ssize_t byte_read = 0;

	mlog_i("B");

	kn_buf = kmalloc(WP_DBG_SIZE_PAGE, GFP_KERNEL);
	if (NULL == kn_buf) {
		mlog_e("kn_buf is null\n");
		return simple_read_from_buffer(user_buf, count, ppos,
					       "kn_buf alloc fail\n", 18);
	}

	memset(kn_buf, 0, WP_DBG_SIZE_PAGE);
	pt_kn_buf = kn_buf;

	/* context */
	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE,
					"addr got = 0x%p, size=0x%08x\n", tget_mem_addr,
					tget_mem_size);
	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE, "\n");

	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE, "usage:\n");
	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE, "m size\n");
	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE,
					"      malloc memory\n");
	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE,
					"      size  : size in byte\n");
	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE,
					"      example: m 4\n");
	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE, "f addr\n");
	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE,
					"      free memory\n");
	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE,
					"      addr  : in hex, such as 0x..\n");
	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE,
					"      example: f 0x..\n");

	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE, "<end>\n");

	byte_read = simple_read_from_buffer(user_buf,
				count, ppos, kn_buf, strlen(kn_buf));

	kfree(kn_buf);
	kn_buf = NULL;

	mlog_i("E");

	return byte_read;
}

/*
"tgetm" : get memory, for test

echo "m osize" > tgetm
	 -- malloc a memory
	-- osize : size in order, size=2^osize
		(0/1/2)3--8 Byte, 4--16, 5--32 .. 31--2^31
	-- type  : 0-kmalloc, 1-vmalloc, 2-dma
*/
static ssize_t wp_tgetmem_write(struct file *file, const char __user *user_buf,
				size_t count, loff_t *ppos)
{
	char *kn_buf = NULL;
	ssize_t byte_writen = 0;
	int num = 0;
	unsigned int size;
	char *addr;

	mlog_i("B");

	kn_buf = kmalloc(WP_DBG_SIZE_PAGE, GFP_KERNEL);
	if (NULL == kn_buf) {
		mlog_e("kn_buf is null\n");
		return -EFAULT;
	}

	byte_writen = simple_write_to_buffer(kn_buf,
					WP_DBG_SIZE_PAGE, ppos, user_buf, count);

	if ('m' == kn_buf[0]) {
		/* malloc */
		num = sscanf(kn_buf, "m %u", &size);
		if (1 == num) {
			if (NULL == tget_mem_addr) {
				tget_mem_addr = kmalloc(size, GFP_KERNEL);
				if (NULL == tget_mem_addr) {
					tget_mem_size = 0;
				} else {
					tget_mem_size = size;
				}
			}

		} else {
			byte_writen = -EINVAL;
		}

	} else if ('f' == kn_buf[0]) {
		/* free */
		num = sscanf(kn_buf, "f %lx", (unsigned long *)&addr);
		mlog_e("sscanf addr=0x%p, num=%d", addr, num);
		if (1 == num) {
			if ((tget_mem_addr == addr) && (addr != NULL)) {
				kfree(tget_mem_addr);
				tget_mem_addr = NULL;
				tget_mem_size = 0;
			}
		} else {
			byte_writen = -EINVAL;
		}

	} else {
		/* 异常 */
		byte_writen = -EINVAL;
	}

	kfree(kn_buf);
	kn_buf = NULL;

	mlog_i("E");

	return byte_writen;
}

/*
"tacc" : access, read or write, for test
		unit is interger

cat tacc
*/
static ssize_t wp_taccess_read(struct file *file, char __user *user_buf,
			       size_t count, loff_t *ppos)
{
	char *kn_buf = NULL;
	char *pt_kn_buf;
	ssize_t byte_read = 0;

	mlog_i("B");

	kn_buf = kmalloc(WP_DBG_SIZE_PAGE, GFP_KERNEL);
	if (NULL == kn_buf) {
		mlog_e("kn_buf is null\n");
		return simple_read_from_buffer(user_buf, count, ppos,
					       "kn_buf alloc fail\n", 18);
	}

	memset(kn_buf, 0, WP_DBG_SIZE_PAGE);
	pt_kn_buf = kn_buf;

	/* context */
	if (tget_mem_addr != NULL) {
		pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE,
						"addr(0x%p) = 0x%x\n",
						tget_mem_addr, tacc_value);
		pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE, "\n");
	}
	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE, "usage:\n");
	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE, "w value\n");
	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE,
					"    write value to the definite addr\n");
	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE, "    example: w 30\n");
	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE, "r\n");
	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE, "    example: r\n");

	pt_kn_buf += snprintf(pt_kn_buf, WP_DBG_SIZE_PAGE, "<end>\n");

	byte_read = simple_read_from_buffer(user_buf,
				count, ppos, kn_buf, strlen(kn_buf));

	kfree(kn_buf);
	kn_buf = NULL;

	mlog_i("E");

	return byte_read;
}

/*
"tacc" : access, read or write, for test
		unit is interger
echo "r addr" > tacc
echo "w addr value" > tacc
*/
static ssize_t wp_taccess_write(struct file *file, const char __user *user_buf,
				size_t count, loff_t *ppos)
{
	char *kn_buf = NULL;
	ssize_t byte_writen = 0;
	int num = 0;
	unsigned int value;

	mlog_i("B");

	kn_buf = kmalloc(WP_DBG_SIZE_PAGE, GFP_KERNEL);
	if (NULL == kn_buf) {
		mlog_e("kn_buf is null\n");
		return -EFAULT;
	}

	byte_writen = simple_write_to_buffer(kn_buf,
					WP_DBG_SIZE_PAGE, ppos, user_buf, count);

	if ('w' == kn_buf[0]) {
		/* write */
		num = sscanf(kn_buf, "w %u", &value);
		if (1 == num) {
			if (tget_mem_addr != NULL) {
				*(unsigned int *)(tget_mem_addr) = value;
			}

		} else {
			byte_writen = -EINVAL;
		}

	} else if ('r' == kn_buf[0]) {
		/* read */
		if (tget_mem_addr != NULL) {
			tacc_value = *(unsigned int *)tget_mem_addr;
		}
	} else {
		/* 异常 */
		byte_writen = -EINVAL;
	}

	kfree(kn_buf);
	kn_buf = NULL;

	mlog_i("E");

	return byte_writen;
}

static const struct file_operations wp_state_fops = {
	.read = wp_state_read,
};

static const struct file_operations wp_config_fops = {
	.read = wp_config_read,
	.write = wp_config_write,
};

static const struct file_operations wp_tgetm_fops = {
	.read = wp_tgetmem_read,
	.write = wp_tgetmem_write,
};

static const struct file_operations wp_taccess_fops = {
	.read = wp_taccess_read,
	.write = wp_taccess_write,
};

#endif /* CONFIG_DEBUG_FS */

static int __init hw_break_module_init(void)
{
	int ret = 0;

	/* NVE Switch */
	if (!check_himntn(HIMNTN_WATCHPOINT_EN)) {
		/* not enabled */
		mlog_i("HIMNTN_WATCHPOINT_EN is Not Enabled\n");
		return 0;
	}
#ifdef __WP_STARTUP_SUPPORT__
	/* just for test begin
	tget_mem_addr = kmalloc(4, GFP_KERNEL);
	if (NULL == tget_mem_addr) {
		mlog_e("kmalloc 4 failed\n");
		return -ENOMEM;
	}
	tget_mem_size = 4;
	pe_addr = tget_mem_addr;
	just for test end */

	/* you MUST config 2 param, pe_addr && rw */
	if (wp_hbp_register
	    (pe_addr, HW_BREAKPOINT_LEN_4, HW_BREAKPOINT_W | HW_BREAKPOINT_R)) {
		mlog_e("watchpoint register failed, addr=0x%p\n", pe_addr);
		return -EFAULT;
	}
#endif

#ifdef CONFIG_DEBUG_FS
	wp_df_dir = debugfs_create_dir("watchpt", NULL);
	if (!wp_df_dir) {
		mlog_e("create wp debugfs dir");
		ret = -ENOMEM;
		goto fail;
	}

	/* status */
	if (!debugfs_create_file("stat", 0660, wp_df_dir, NULL, &wp_state_fops)) {
		mlog_e("create wp debugfs stat\n");
		ret = -ENOMEM;
		goto fail;
	}

	/* set */
	if (!debugfs_create_file("cfg", 0660, wp_df_dir, NULL, &wp_config_fops)) {
		mlog_e("create wp debugfs cfg\n");
		ret = -ENOMEM;
		goto fail;
	}

	/* tst malloc */
	if (!debugfs_create_file("tm", 0660, wp_df_dir, NULL, &wp_tgetm_fops)) {
		mlog_e("create wp debugfs tm\n");
		ret = -ENOMEM;
		goto fail;
	}

	/* tst access */
	if (!debugfs_create_file("ta", 0660, wp_df_dir, NULL, &wp_taccess_fops)) {
		mlog_e("create wp debugfs ta\n");
		ret = -ENOMEM;
		goto fail;
	}
#endif

	return 0;

#ifdef CONFIG_DEBUG_FS
fail:
	if (NULL != wp_df_dir) {
		debugfs_remove(wp_df_dir);
		wp_df_dir = NULL;
	}

	return ret;
#endif
}

static void __exit hw_break_module_exit(void)
{
#ifdef __WP_STARTUP_SUPPORT__
	if (pe_addr != NULL) {
		wp_hbp_unregister(pe_addr);
		pe_addr = NULL;
	}
#endif
}

module_init(hw_break_module_init);
module_exit(hw_break_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("WangLai.Shi");
MODULE_DESCRIPTION("watchpoint callback");
