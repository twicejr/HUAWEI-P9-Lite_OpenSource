/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <linux/proc_fs.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/suspend.h>
#include <asm/uaccess.h>
#include <bsp_hardtimer.h>
#include <bsp_pm.h>
#include <bsp_dump.h>
#include <bsp_pm_om.h>
#include "pm_om_platform.h"
#include "pm_om_debug.h"

struct pm_om_debug g_pmom_debug;

void pm_om_wakeup_log(void)
{
	if (g_pmom_debug.stat.wrs_flag == 1)
	{
		bsp_pm_log(PM_OM_PMLG, 0, NULL);
		g_pmom_debug.stat.wrs_flag = 0;
	}
}

void pm_om_wakeup_stat(void)
{
	u32 cur_slice   = bsp_get_slice_value();
	u32 delta_slice = 0;

	g_pmom_debug.stat.wakeup_cnt++;

	delta_slice = delta_slice - g_pmom_debug.stat.waket_prev;
	g_pmom_debug.stat.waket_prev = cur_slice;
	if (delta_slice > g_pmom_debug.stat.waket_max)
	{
		g_pmom_debug.stat.waket_max = delta_slice;
	}
	if (delta_slice < g_pmom_debug.stat.waket_min)
	{
		g_pmom_debug.stat.waket_min = delta_slice;
	}

	/* 32768hz，转换成秒 */
	delta_slice /= TIME_SLICE_FREQ;
	g_pmom_debug.stat.wrs_flag = 1;
	pmom_print("[C SR]pm om wakeup\n");
}

u32 pm_om_log_time_rec(u32 time_log_start)
{
	u32 ret = 0;
	u32 delta_slice = bsp_get_slice_value();
	delta_slice = delta_slice - time_log_start;

	if (g_pmom_debug.stat.logt_print_sw && delta_slice > g_pmom_debug.stat.logt_max)
	{
		g_pmom_debug.stat.logt_max = delta_slice;
		ret = delta_slice;
	}
	return ret;
}

void pm_om_dbg_on(void)
{
	bsp_mod_level_set(BSP_MODU_PM_OM, BSP_LOG_LEVEL_DEBUG);
}

void pm_om_dbg_off(void)
{
	bsp_mod_level_set(BSP_MODU_PM_OM, BSP_LOG_LEVEL_ERROR);
}

void pm_om_dump_show(void)
{
	u32 i = 0;
	char *magic = NULL;
	struct pm_om_ctrl *ctrl = pm_om_ctrl_get();

	pmom_print("**********************************************\n");
	pmom_print("init_flag : 0x%x\n", ctrl->dump.init_flag);
	pmom_print("base_addr : 0x%x\n", ctrl->dump.base);
	pmom_print("length    : 0x%x\n", PM_OM_DUMP_SIZE);
	pmom_print("region_num: 0x%x\n", ctrl->dump.region_cnt);

	for (i = 0; i < ctrl->dump.region_cnt; i++)
	{
		magic = (char *)(&(ctrl->dump.cfg->entry_tbl[i].magic));
		pmom_print("[%c%c%c%c]    : 0x%x\n",magic[0], magic[1], magic[2], magic[3], ctrl->dump.cfg->entry_tbl[i].len);
	}
	pmom_print("**********************************************\n");
}

void pm_om_log_show(void)
{
	struct pm_om_ctrl *ctrl = pm_om_ctrl_get();
	pmom_print("**********************************************\n");
	pmom_print("init_flag   : 0x%x\n", ctrl->log.init_flag);
	pmom_print("buf_is_full : 0x%x\n", ctrl->log.buf_is_full);
	pmom_print("threshold   : 0x%x\n", ctrl->log.threshold);
	pmom_print("debug       : 0x%p\n", ctrl->debug);
	pmom_print("platform    : 0x%p\n", ctrl->platform);
	pmom_print("**********************************************\n");
}

void pm_om_debug_show(void)
{
	pmom_print("**********************************************\n");
	pmom_print("logt_print_sw: 0x%x\n", g_pmom_debug.stat.logt_print_sw);
	pmom_print("logt_max\t: 0x%x\n", g_pmom_debug.stat.logt_max);
	pmom_print("**********************************************\n");
}

u32 pm_om_feature_on(void)
{
	struct pm_om_ctrl *ctrl = pm_om_ctrl_get();
	struct pm_om_platform *linux_plat = NULL;
	if (NULL == ctrl || NULL == ctrl->platform)
	{
		return 1;
	}

	linux_plat = (struct pm_om_platform *)ctrl->platform;
	ctrl->log.init_flag = PM_OM_INIT_MAGIC;
	ctrl->log.smem->nv_cfg.mod_sw_bitmap = 0xFFFFFFFFFFFFFFFF;
	linux_plat->log_info.mem_is_ok = 1;

	return 0;
}

/* pmom在mbb/phone共代码, 都需要实现. pm_wakeup_ccore在phone需要在pmom模块实现,mbb上在pm模块实现 */
s32 pm_wakeup_ccore(enum debug_wake_type type)
{
	u32 channel_id = (ICC_CHN_IFC << 16) | IFC_RECV_FUNC_WAKEUP;
	s32 ret = 0;
	struct debug_pm_s pm_msg;
	u32 msglen = sizeof(pm_msg);
	pm_msg.wake_type=type;

	ret = bsp_icc_send(ICC_CPU_MODEM, channel_id, (u8*)(&pm_msg), msglen);
	if(ret != msglen)
	{
		return -1;
	}
    return 0;
}

void debug_pm_wake_lock(void)
{
    wake_lock(&g_pmom_debug.wakelock_debug);
}

void debug_pm_wake_unlock(void)
{
    wake_unlock(&g_pmom_debug.wakelock_debug);
}

static s32 pm_wakeup_icc_msg(u32 id , u32 len, void* context)
{
	u32 ret = 0;
	struct debug_pm_s read_data;

	/* 不可以通过icc发送非法长度的消息过来(包括长度为0) */
	if(len != (u32)sizeof(read_data))
	{
		pmom_pr_err("icc packet len(%d) != sizeof(struct debug_pm_s)(%d)\n", len, (u32)sizeof(read_data));
		return -1;
	}

	ret = bsp_icc_read(id, (u8*)&read_data, len);
	if (ret != (int)sizeof(read_data))
	{
		pmom_pr_err("readed len(%d) != icc packet len(%d)", ret, len);
		return -1;
	}
	if(PM_WAKEUP == read_data.wake_type)
	{
		debug_pm_wake_lock();
	}
	else if(PM_WAKEUP_THEN_SLEEP== read_data.wake_type)
	{
		debug_pm_wake_unlock();
	}
	return 0;
}

void print_ccpu_pm_info(void)
{
	printk(KERN_ERR"****************cp pm info****************\n");
	printk(KERN_ERR"shared mem, phy_addr: 0x%p, virt_addr:0x%p\n", \
		bsp_dump_get_field_phy_addr(DUMP_CP_DRX), g_pmom_debug.cdrx_dump_addr);
	printk(KERN_ERR"soft wakelock:        0x%x\n", *((u32 *)g_pmom_debug.cdrx_dump_addr + CDRX_DUMP_WAKE_OFFSET));
	printk(KERN_ERR"[SLEEP COUNT] pm enter cnt: 0x%x, dpm fail cnt: 0x%x\n"\
		,*((u32 *)(g_pmom_debug.cdrx_dump_corepm_addr + PM_ENTER_COUNT)) \
		,*((u32 *)(g_pmom_debug.cdrx_dump_corepm_addr + PM_DPM_FAIL_COUNT)));
	printk(KERN_ERR"[STAMP SLICE] sleep start: 0x%x, sleep end: 0x%x, wake start: 0x%x, wake end: 0x%x\n"\
		,*((u32 *)(g_pmom_debug.cdrx_dump_corepm_addr + STAMP_PM_SUSPEND_START)) \
		, *((u32 *)(g_pmom_debug.cdrx_dump_corepm_addr + STAMP_AFTER_SEND_IPC)) \
		,*((u32 *)(g_pmom_debug.cdrx_dump_corepm_addr + STAMP_PWRUP_CODE_BEGIN)) \
		, *((u32 *)(g_pmom_debug.cdrx_dump_corepm_addr + STAMP_AFTER_DPM_RESUME)));
}

int cp_pm_notify(struct notifier_block *nb, unsigned long event, void *dummy)
{
	char* dump_base = NULL;
	if(event == PM_SUSPEND_PREPARE)
	{
		if(!g_pmom_debug.cdrx_dump_addr)
		{
			/*获取DUMP 低功耗共享内存地址*/
			dump_base = (char *)bsp_dump_get_field_addr(DUMP_CP_DRX);
			if(NULL == dump_base)
			{
				pmom_pr_err("*******get cdrx dump buffer failed!*******\n");
				return 0;
			}
			g_pmom_debug.cdrx_dump_addr        = (char*)dump_base;
			g_pmom_debug.cdrx_dump_corepm_addr = (char*)(dump_base + CDRX_DUMP_PM_OFFSET);
		}
	}
	if ((event == PM_POST_SUSPEND)&&(g_pmom_debug.cdrx_dump_addr))
	{
		printk(KERN_ERR"\n############ Ccpu Debug Info,Current Slice 0x%x ############\n",bsp_get_slice_value());
		/*此处用于增加CCPU的打印信息函数*/
		print_ccpu_pm_info();
	}
	return 0;
}


void pm_wakeup_init(void)
{
	char* dump_base = NULL;

	wake_lock_init(&g_pmom_debug.wakelock_debug, WAKE_LOCK_SUSPEND, "cp_pm_wakeup");

	/* 即使注册icc失败(有错误打印),只影响调测,不影响功能 */
	(void)bsp_icc_event_register(ICC_CHN_IFC << 16 | IFC_RECV_FUNC_WAKEUP, \
		(read_cb_func)pm_wakeup_icc_msg, NULL, NULL, NULL);
	(void)bsp_icc_event_register(ICC_CHN_MCORE_ACORE << 16 | MCORE_ACORE_FUNC_WAKEUP, \
		(read_cb_func)pm_wakeup_icc_msg, NULL, NULL, NULL);

	g_pmom_debug.pm.notifier_call = cp_pm_notify;
	register_pm_notifier(&g_pmom_debug.pm);

	if(!g_pmom_debug.cdrx_dump_addr)
	{
    	/*获取DUMP 低功耗共享内存地址*/
		dump_base = (char *)bsp_dump_get_field_addr(DUMP_CP_DRX);
		if(NULL == dump_base)
		{
			printk(KERN_ERR"*******!get dump buffer failed!*******\n");
			return;
		}
        g_pmom_debug.cdrx_dump_addr        = (void*)dump_base;
		g_pmom_debug.cdrx_dump_corepm_addr = (char*)(dump_base + CDRX_DUMP_PM_OFFSET);
    }
}

void pm_om_help(void)
{
	pmom_print("***********************\n");
	pmom_print("pm_om_dump_show\n");
	pmom_print("pm_om_log_show\n");
	pmom_print("pm_om_debug_show\n");
	pmom_print("pm_om_dbg_on\n");
	pmom_print("pm_om_dbg_off\n");
	pmom_print("pm_om_wake_interval_set slice\n");
	pmom_print("pm_om_feature_on\n");
	pmom_print("pm_wakeup_ccore 0|1\n");
	pmom_print("debug_pm_wake_lock\n");
	pmom_print("debug_pm_wake_unlock\n");
	pmom_print("***********************\n");
}

static ssize_t pm_om_mod_sw_show(struct file *file,  char  __user *buffer, size_t count, loff_t *ppos)
{
    int  len      = 0;
    char buf[32]  = {0};
    u64  sw_value = 0;
    u32  tmp_low  = 0;
    u32  tmp_high = 0;
	struct pm_om_ctrl *ctrl = g_pmom_debug.ctrl;

    sw_value = ctrl->log.smem->nv_cfg.mod_sw_bitmap;
    tmp_low  = (u32)(sw_value & (u32)0xFFFFFFFF);
    tmp_high = (u32)((sw_value >> 32) & (u32)0xFFFFFFFF);

    len = snprintf(buf, 32, "0x%08x%08x\n", tmp_high, tmp_low);
	return simple_read_from_buffer(buffer, count, ppos, (void *)buf, len);
}

static ssize_t get_u32_data_from_user(const char  __user *usr_buf, size_t count)
{
	char buf[32]= {0};
	u32  value  = 0;
	int  ret = 0;

	if(count >= sizeof(buf))
	{
		pmom_pr_err("input size(%d) >= buf size(%d)\n", count, sizeof(buf));
		return -ENOMEM;
	}
	if (copy_from_user(buf, usr_buf, count))
	{
		pmom_pr_err("copy_from_user err\n");
		return -EFAULT;
	}

	ret = sscanf(buf, "%u", &value);
	if (ret < 0)
	{
		return ret;
	}
	return value;
}

static int get_u32_seq_data_from_user(const char  __user *usr_buf, size_t usr_count, u8 *seq_data)
{
	char buf[PM_OM_LOG_THRE_BUF_SIZE]= {0};
	int ret = 0;

	if(usr_count >= sizeof(buf))
	{
		pmom_pr_err("input size(%d) >= buf size(%d)\n", usr_count, sizeof(buf));
		return -ENOMEM;
	}
	if (copy_from_user(buf, usr_buf, usr_count))
	{
		pmom_pr_err("copy_from_user err\n");
		return -EFAULT;
	}

	ret = sscanf(buf, "%c %c %c %c", &seq_data[0], &seq_data[1], &seq_data[2], &seq_data[3]);/* [false alarm]:fortify */
	if (ret != 4)
	{
		return  -EFAULT;
	}
	return 0;
}

/* 通知其他核开启log功能 */
void pm_om_notify_other_core(pm_om_icc_data_type data)
{
	s32 ret = 0;
	u32 channel_id = 0;

	channel_id = PM_OM_ICC_ACORE_CHN_ID;
	ret = bsp_icc_send(ICC_CPU_MODEM, channel_id, (u8 *)&data, sizeof(data));
	if(sizeof(data) != ret)
	{
		goto icc_send_fail;
	}

	/* TODO:  等M3开启后打开 */
	return;

icc_send_fail:
	pmom_pr_err("icc[0x%x] send fail: 0x%x\n", PM_OM_ICC_ACORE_CHN_ID, ret);
	return;
}

static ssize_t pm_om_mod_on_store(struct file *file,  const char  __user *usr_buf, size_t count, loff_t *ppos)
{
	struct pm_om_ctrl *ctrl = g_pmom_debug.ctrl;
	ssize_t mod_id = get_u32_data_from_user(usr_buf, count);

	if(mod_id < 0)
	{
		return mod_id;
	}
	else if(mod_id < 64)
	{
		ctrl->log.init_flag = PM_OM_INIT_MAGIC;
		pm_om_log_mod_on(&(ctrl->log.smem->nv_cfg.mod_sw_bitmap), mod_id);
		pm_om_notify_other_core(1);
	}
	else if(mod_id == 64)/* enable all */
	{
		ctrl->log.init_flag = PM_OM_INIT_MAGIC;
		pm_om_log_sw_set(&(ctrl->log.smem->nv_cfg.mod_sw_bitmap), 0xffffffffffffffff);
		pm_om_notify_other_core(1);
	}

	return count;
}

static ssize_t pm_om_mod_off_store(struct file *fil,  const char  __user *usr_buf, size_t count, loff_t *ppos)
{
	struct pm_om_ctrl *ctrl = g_pmom_debug.ctrl;
	ssize_t mod_id = get_u32_data_from_user(usr_buf, count);

	if(mod_id < 0)
	{
		return mod_id;
	}
	else if(mod_id < 64)
	{
		pm_om_log_mod_off(&(ctrl->log.smem->nv_cfg.mod_sw_bitmap), mod_id);
	}
	else if(mod_id == 64)/* disable all */
	{
		ctrl->log.init_flag = 0;
		pm_om_log_sw_set(&(ctrl->log.smem->nv_cfg.mod_sw_bitmap), 0);
		pm_om_notify_other_core(0);
	}

	return count;
}

static ssize_t pm_om_fwrite_trigger_on_store(struct file *file,  const char  __user *usr_buf, size_t count, loff_t *ppos)
{
	struct pm_om_ctrl *ctrl = g_pmom_debug.ctrl;
	ssize_t sw = get_u32_data_from_user(usr_buf, count);

	if(sw < 0)
	{
		return sw;
	}
	else if(sw)
	{
		ctrl->log.smem->mem_info.app_is_active = 1;
	}
	else if(sw == 0)
	{
		ctrl->log.smem->mem_info.app_is_active = 0;
	}

	return count;
}

static ssize_t pm_om_fwrite_trigger_on_show(struct file *file,  char  __user *usr_buf, size_t count, loff_t *ppos)
{
	int  len      = 0;
	char buf[32]  = {0};
	u32  sw_value = 0;
	struct pm_om_ctrl *ctrl = pm_om_ctrl_get();

	sw_value = ctrl->log.smem->mem_info.app_is_active;
	len = snprintf(buf, 32, "0x%08x\n", sw_value);
	return simple_read_from_buffer(usr_buf, count, ppos, (void *)buf, len);
}

static ssize_t pm_om_rb_size_store(struct file *file,  const char  __user *usr_buf, size_t count, loff_t *ppos)
{
	struct pm_om_ctrl *ctrl = g_pmom_debug.ctrl;
	ssize_t rb_size = get_u32_data_from_user(usr_buf, count);

	if(rb_size < 0)
	{
		return rb_size;
	}
	else if(rb_size)
	{
		ctrl->log.rb.size = rb_size;
	}

	return count;
}

static ssize_t pm_om_rb_info_show(struct file *file,  char  __user *usr_buf, size_t count, loff_t *ppos)
{
	int  len      = 0;
	char buf[PM_OM_LOG_THRE_BUF_SIZE]  = {0};

	struct pm_om_ctrl *ctrl = g_pmom_debug.ctrl;
	struct ring_buffer *rb = &(ctrl->log.rb);
	len = snprintf(buf, PM_OM_LOG_THRE_BUF_SIZE, 
		"rb_base\t\t\trb_size\t\trb_write\trb_read\n0x%p(0x%p)\t0x%08x\t0x%08x\t0x%08x\t\n",
		(void *)rb->buf, (void *)SHD_DDR_V2P((void *)rb->buf), rb->size, rb->write, rb->read);
	return simple_read_from_buffer(usr_buf, count, ppos, (void *)buf, len);
}

static ssize_t pm_om_log_threshold_store(struct file *file,  const char  __user *usr_buf, size_t count, loff_t *ppos)
{
	struct pm_om_ctrl *ctrl = g_pmom_debug.ctrl;
	u8 *seq_data = NULL;
	int ret = 0;
	u32 len = sizeof(u8) * PM_OM_LOG_THRE_CORE_NUM;

	seq_data = kmalloc(len, GFP_KERNEL);
	if (!seq_data)
	{
		return -ENOMEM;
	}

	ret = get_u32_seq_data_from_user(usr_buf, count, seq_data);
	if(ret < 0)
	{
		kfree(seq_data);
		seq_data = NULL;
		return ret;
	}
	else
	{
		memcpy((void *)ctrl->log.smem->nv_cfg.log_threshold, (void *)seq_data, len);
		ctrl->log.threshold = ctrl->log.smem->nv_cfg.log_threshold[PM_OM_CPUID];
	}

	kfree(seq_data);
	seq_data = NULL;
	return count;
}

static ssize_t pm_om_log_threshold_show(struct file *file,  char  __user *usr_buf, size_t count, loff_t *ppos)
{
	int len = 0;
	char buf[PM_OM_LOG_THRE_BUF_SIZE] = {0};
	struct pm_om_ctrl *ctrl = g_pmom_debug.ctrl;

	len = snprintf(buf, PM_OM_LOG_THRE_BUF_SIZE, "%2d %2d %2d %2d\n", 
		ctrl->log.smem->nv_cfg.log_threshold[0], 
		ctrl->log.smem->nv_cfg.log_threshold[1],
		ctrl->log.smem->nv_cfg.log_threshold[2],
		ctrl->log.smem->nv_cfg.log_threshold[3]);
	return simple_read_from_buffer(usr_buf, count, ppos, (void *)buf, len);
}

static int pm_om_wakeup_stats_show(struct seq_file *m, void *unused)
{
	struct pm_om_debug *debug = &g_pmom_debug;

	seq_puts(m, "wake_times\twaket_min\twaket_max\n");
 	seq_printf(m, "%u\t\t%u\t\t%u\n", debug->stat.wakeup_cnt,debug->stat.waket_min, debug->stat.waket_max);

	return 0;
}

static int wakeup_sources_stats_open(struct inode *inode, struct file *file)
{
	return single_open(file, pm_om_wakeup_stats_show, NULL);
}


static const struct file_operations pm_om_mod_on_fops = {
	.read  = pm_om_mod_sw_show,
	.write = pm_om_mod_on_store,
};

static const struct file_operations pm_om_mod_off_fops = {
	.read  = pm_om_mod_sw_show,
	.write = pm_om_mod_off_store,
};

static const struct file_operations pm_om_fwrite_trigger_fops = {
	.read  = pm_om_fwrite_trigger_on_show,
	.write = pm_om_fwrite_trigger_on_store,
};

static const struct file_operations pm_om_rb_info_fops = {
	.read  = pm_om_rb_info_show,
	.write = pm_om_rb_size_store,
};

static const struct file_operations pm_om_log_threshold_fops = {
	.read  = pm_om_log_threshold_show,
	.write = pm_om_log_threshold_store,
};

static const struct file_operations pm_om_wakeup_stats_fops = {
	.open = wakeup_sources_stats_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int pm_om_debugfs_create(void)
{
	struct dentry *debugfs_root;

	debugfs_root = debugfs_create_dir("pm_om", NULL);
	if (!debugfs_root)
		return (-ENOENT);

	debugfs_create_file("mod_on", (S_IRUGO|S_IWUSR), debugfs_root, NULL, &pm_om_mod_on_fops);
	debugfs_create_file("mod_off", (S_IRUGO|S_IWUSR), debugfs_root, NULL, &pm_om_mod_off_fops);
	debugfs_create_file("fwrite_trigger", (S_IRUGO|S_IWUSR), debugfs_root, NULL, &pm_om_fwrite_trigger_fops);
	debugfs_create_file("rb_info", (S_IRUGO|S_IWUSR), debugfs_root, NULL, &pm_om_rb_info_fops);
	debugfs_create_file("log_threshold", (S_IRUGO|S_IWUSR), debugfs_root, NULL, &pm_om_log_threshold_fops);
	debugfs_create_file("wakeup_stats",(S_IRUGO|S_IWUSR), debugfs_root, NULL, &pm_om_wakeup_stats_fops);

	return 0;
}

int pm_om_debug_init(void)
{
	struct pm_om_ctrl *ctrl = pm_om_ctrl_get();

	memset((void *)&g_pmom_debug, 0, sizeof(g_pmom_debug));

	g_pmom_debug.stat.waket_prev    = bsp_get_slice_value();
	g_pmom_debug.stat.waket_min     = 0xffffffff;
	g_pmom_debug.stat.logt_print_sw = ctrl->log.smem->nv_cfg.reserved;

	g_pmom_debug.ctrl = ctrl;
	ctrl->debug = (void *)&g_pmom_debug;

	pm_wakeup_init();

	pm_om_debugfs_create();

	return 0;
}

EXPORT_SYMBOL(pm_wakeup_ccore);
EXPORT_SYMBOL(pm_om_notify_other_core);

