/*
 *  Hisilicon K3 soc camera v4l2 driver source file
 *
 *  CopyRight (C) Hisilicon Co., Ltd.
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include <linux/err.h>
#include <linux/fs.h>
#include <asm/segment.h>
#include <linux/list.h>
#include <linux/uaccess.h>
#include <linux/stat.h>
#include <linux/io.h>
#include <linux/delay.h>

#include "cam_dbg.h"
#include "cam_util.h"
/* #define DEBUG_DEBUG 1 */
#define LOG_TAG "K3_CAM_DBG"
#include "cam_log.h"
#include "sensor_common.h"
#include "isp_io_mutex.h"

#include "video_reg_ops.h"
#ifdef DUMP_SCCTRL_ISP_REG
#include "soc_ao_sctrl_interface.h"
#include "soc_pmctrl_interface.h"
#include "soc_baseaddr_interface.h"
#include "soc_media_sctrl_interface.h"
#endif
#ifdef	CONFIG_DEBUG_FS
#include <linux/debugfs.h>
#include <linux/string.h>
#endif
#include <linux/string.h>

#include "video_config.h"

#define DUMP_CMD_REG
//#define DUMP_SIZE_REG

//#define DUMP_FILE


#ifdef CONFIG_DEBUG_FS
#define CAM_DEBUGFS_DIR_NAME            "mit2isp"
#define CAM_DEBUGFS_PWDN_FILE_NAME      "pwdn"
#define CAM_DEBUGFS_FLASH_FILE_NAME     "flash"
#define CAM_DEBUGFS_FLASH_FILE_MAXSIZE  (32)
#endif

#define DBG_BIG_ENDIAN(a) ((a)+3-2*((a)&0x3))

#define DBG_SETREG8(reg, value) \
	(((reg) >= 0x20000) ? \
	iowrite8_mutex((value), (cam_dbg_info.dbg_isp_base_addr + (reg))) : \
	iowrite8_mutex((value), (cam_dbg_info.dbg_isp_base_addr + DBG_BIG_ENDIAN(reg))))

#define DBG_GETREG8(reg) \
	(((reg) >= 0x20000) ?	\
	(*(volatile u8*)(cam_dbg_info.dbg_isp_base_addr + (reg))) : \
	(*(volatile u8*)(cam_dbg_info.dbg_isp_base_addr + DBG_BIG_ENDIAN (reg))))

#define DBG_GETREG32(reg, value) \
    do { \
        (value) = (DBG_GETREG8(reg) << 24) + \
            (DBG_GETREG8((reg) + 1) << 16) + \
            (DBG_GETREG8((reg) + 2) << 8) + \
            (DBG_GETREG8((reg) + 3)); \
    } while (0)


static cam_dbg_info_t cam_dbg_info;

static u32 cam_dbgfs_pwdncfg = 1;
static cam_pwdn_status_t cam_pwdn_status = {0};
#ifdef CONFIG_DEBUG_FS
struct dentry *cam_dbgfs_dir = NULL;
static u8 cam_dbgfs_flash_timeout = 2;
static u8 cam_dbgfs_flash_timeout_valid = 0;
#endif

#ifdef ISP_DEBUG_ZSL
/* GLOBAL VARIABLES */
#define ISP_CMD_REG_MAX         (1024)
#define ISP_CMD_PRINT_MAX       (32)
#define ISP_IRQ_REG_MAX         (32)
#define ISP_IRQ_PRINT_MAX       (30*60*5)
#define ISP_DEBUG_INVALID_TAG   (0xFFFFFFFF)

u8    zsl_online_enable = 1;
u8    zsl_back_idx      = 5;
u8    print_flg         = 0;
u8    zsl_copy_flg      = 1;
u8    ap_ae_flg         = 1;
u8    color_bar_flg     = 0;
u32   g_cmd_reg_cnt     = 0;
u32   g_cmd_loop_cnt    = 0;
u32   g_irq_reg_cnt     = 0;
u32   g_irq_loop_cnt    = 0;
u32   g_cmd_reg_key[ISP_CMD_REG_MAX];
char  g_cmd_reg_val[ISP_CMD_PRINT_MAX][ISP_CMD_REG_MAX];
u32   g_cmd_loop_tag[ISP_CMD_PRINT_MAX];
u32   g_irq_reg_key[ISP_IRQ_REG_MAX];
char  g_irq_reg_val[ISP_IRQ_PRINT_MAX][ISP_IRQ_REG_MAX];
u32   g_irq_loop_tag[ISP_IRQ_PRINT_MAX];

int isp_debug_load_cfg(char *cfg_file,char *key_name,u8 *key_var)
{
	struct kstat stat;
	mm_segment_t fs;
	struct file *fp = NULL;
	int file_flag = O_RDONLY;
	ssize_t ret = 0;
	char temp_array[64] = {0};
	char temp = 0;
	int  cnt=0;
	bool bRegStart = false;
	bool bKeyFound = false;
	bool bKeyCfg   = false;


	print_debug("enter %s", __func__);

	if (NULL == cfg_file) {
		print_error("%s cfg_file null ptr.", __func__);
		return -EINVAL;
	}

	if (NULL == key_name) {
		print_error("%s key_name null ptr.", __func__);
		return -EINVAL;
	}

	if (NULL == key_var) {
		print_error("%s key_var null ptr.", __func__);
		return -EINVAL;
	}

	/* must have the following 2 statement */
	fs = get_fs();
	set_fs(KERNEL_DS);

	fp = filp_open(cfg_file, file_flag, 0666);
	if (IS_ERR_OR_NULL(fp)) {
		print_debug("no debug configuration file(%s) - do nothing, just skip it!\n",cfg_file);
		return -1;
	}

	if (0 != vfs_stat(cfg_file, &stat)) {
		print_error("failed to get file %s state!",cfg_file);
		goto error_out;
	}

	print_debug("%s size : %d",cfg_file, (u32)stat.size);

	while (0 < vfs_read(fp, &temp, 1, &fp->f_pos)) {
		switch (temp) {
		case '{':
			bRegStart = true;
			cnt       = 0;
			bKeyFound = false;
			memset(temp_array,sizeof(char),sizeof(temp_array));
			break;
		case '}':
			bRegStart = false;
			if(bKeyFound)
			{
			    *key_var = atoi16(temp_array);
	            bKeyCfg  = true;
			    print_debug("%s:0x%x",key_name,*key_var);
			}
			break;
		case '=':
		    if (bRegStart)
		    {
		        bKeyFound = false;
		        if (0 == strncmp(key_name,temp_array,strlen(key_name)))
		        {
                    bKeyFound = true;
		        }
		        cnt = 0;
		    }
		    break;
		default:
		    if (bRegStart){
    		    if (cnt >= 64)
    		    {
    		        bRegStart = false;
    		    }
    		    else
    		    {
    		        temp_array[cnt] = temp;
    		        cnt=cnt+1;
    		    }
		    }
		    break;
		}

		if (bKeyCfg)
		{
		    break;
		}
	}

	/* must have the following 1 statement */
	set_fs(fs);

error_out:
	if (NULL != fp)
		filp_close(fp, 0);
	return ret;
}

int isp_debug_load_reg(char *reg_file,u32 *reg_key,u32 reg_max,u32 *reg_cnt)
{
	struct kstat stat;
	mm_segment_t fs;
	struct file *fp = NULL;
	int file_flag = O_RDONLY;
	ssize_t ret = 0;
	u32 addr = 0;
	char addr_array[8] = {0};
	char temp = 0;
	bool bRegStart = false;

	if (NULL == reg_file) {
		print_error("%s param error", __func__);
		return -EINVAL;
	}

	print_debug("enter %s", __func__);

	/* must have the following 2 statement */
	fs = get_fs();
	set_fs(KERNEL_DS);

	fp = filp_open(reg_file, file_flag, 0666);
	if (IS_ERR_OR_NULL(fp)) {
		print_debug("no debug configuration file(%s) - do nothing, just skip it!\n",reg_file);
		return -1;
	}

	if (0 != vfs_stat(reg_file, &stat)) {
		print_error("failed to get file state!");
		goto error_out;
	}

	*reg_cnt = 0;
	print_debug("file size : %d", (u32) stat.size);


	while (0 < vfs_read(fp, &temp, 1, &fp->f_pos)) {
		switch (temp) {
		case '{':
			bRegStart = true;
			if (0 == vfs_read(fp, addr_array, 7, &fp->f_pos))
				goto error_out;
			addr = atoi16(addr_array);

			if (*reg_cnt < reg_max){
    			reg_key[*reg_cnt]=addr;
    			*reg_cnt=*reg_cnt+1;
    		}
			break;

		case '}':
			bRegStart = false;
			break;

		default:
			break;
		}
	}

	/* must have the following 1 statement */
	set_fs(fs);

error_out:
	if (NULL != fp)
		filp_close(fp, 0);
	return ret;
}

void isp_debug_init_cmd_reg(void)
{
	unsigned int reg;
	unsigned int idx;

	g_cmd_loop_cnt = 0;
	g_cmd_reg_cnt  = 0;

	for(idx = 0; idx < ISP_CMD_PRINT_MAX; idx++)
		g_cmd_loop_tag[idx] = ISP_DEBUG_INVALID_TAG;

    /* default print cmd reg */
	for(reg = 0x1e800; reg < 0x1e8bf; reg++)
		g_cmd_reg_key[g_cmd_reg_cnt++] = reg;
	for(reg = 0x63900; reg < 0x63917; reg++)
		g_cmd_reg_key[g_cmd_reg_cnt++] = reg;
	for(reg = 0x63b00; reg <= 0x63b1f ; reg++)
		g_cmd_reg_key[g_cmd_reg_cnt++] = reg;
	for(reg = 0x63b30; reg <= 0x63b5f ; reg++)
		g_cmd_reg_key[g_cmd_reg_cnt++] = reg;
	for(reg = 0x63c00; reg <= 0x63c59 ; reg++)
		g_cmd_reg_key[g_cmd_reg_cnt++] = reg;
	for(reg = 0x65000; reg <= 0x6503f ; reg++)
		g_cmd_reg_key[g_cmd_reg_cnt++] = reg;
	for(reg = 0x65050; reg <= 0x6505f ; reg++)
		g_cmd_reg_key[g_cmd_reg_cnt++] = reg;
	for(reg = 0x650f0; reg <= 0x650fb ; reg++)
		g_cmd_reg_key[g_cmd_reg_cnt++] = reg;
	for(reg = 0x671f0; reg <= 0x671fb ; reg++)
		g_cmd_reg_key[g_cmd_reg_cnt++] = reg;
	for(reg = 0x63b20; reg <= 0x63b23 ; reg++)
		g_cmd_reg_key[g_cmd_reg_cnt++] = reg;
	for(reg = 0x63b28; reg <= 0x63b2b ; reg++)
		g_cmd_reg_key[g_cmd_reg_cnt++] = reg;
	for(reg = 0x63106; reg <= 0x63109 ; reg++)
		g_cmd_reg_key[g_cmd_reg_cnt++] = reg;
	for(reg = 0x1c781; reg <= 0x1c786 ; reg++)
		g_cmd_reg_key[g_cmd_reg_cnt++] = reg;
	for(reg = 0x1d920; reg <= 0x1d96f ; reg++)
		g_cmd_reg_key[g_cmd_reg_cnt++] = reg;
	for(reg = 0x1c5e8; reg <= 0x1c5e9 ; reg++)
		g_cmd_reg_key[g_cmd_reg_cnt++] = reg;
	for(reg = 0x1c150; reg <= 0x1c15f ; reg++)
		g_cmd_reg_key[g_cmd_reg_cnt++] = reg;
	for(reg = 0x1c52C; reg <= 0x1c573 ; reg++)
		g_cmd_reg_key[g_cmd_reg_cnt++] = reg;

    /* init from file */
    isp_debug_load_reg("/data/k3_camera/ov-cmd-reg.txt",
                       g_cmd_reg_key,
                       ISP_CMD_REG_MAX,
                       &g_cmd_reg_cnt);

}

void isp_debug_dump_cmd_reg(void)
{
    unsigned int loop;
	unsigned int idx;

	if (print_flg == ISP_DBG_PRINT_DIRECT){
        printk("cmd:0x%x=0x%x,0x%x=0x%x,0x%x=0x%x,0x%x=0x%x,0x%x=0x%x,0x%x=0x%x,0x%x=0x%x,0x%x=0x%x\n",
                g_cmd_reg_key[0],DBG_GETREG8(g_cmd_reg_key[0]),
                g_cmd_reg_key[1],DBG_GETREG8(g_cmd_reg_key[1]),
                g_cmd_reg_key[2],DBG_GETREG8(g_cmd_reg_key[2]),
                g_cmd_reg_key[3],DBG_GETREG8(g_cmd_reg_key[3]),
                g_cmd_reg_key[4],DBG_GETREG8(g_cmd_reg_key[4]),
                g_cmd_reg_key[5],DBG_GETREG8(g_cmd_reg_key[5]),
                g_cmd_reg_key[6],DBG_GETREG8(g_cmd_reg_key[6]),
                g_cmd_reg_key[7],DBG_GETREG8(g_cmd_reg_key[7]));
	} else if (print_flg == ISP_DBG_PRINT_TO_MEM){
        idx = g_cmd_loop_cnt % ISP_CMD_PRINT_MAX;

        printk("cmd=%d.\n",g_cmd_loop_cnt);

        g_cmd_loop_tag[idx]=g_cmd_loop_cnt;
    	for(loop = 0; loop < g_cmd_reg_cnt; loop++){
    		g_cmd_reg_val[idx][loop] = DBG_GETREG8(g_cmd_reg_key[loop]);
        }

        g_cmd_loop_cnt++;
    }
}

void isp_debug_print_cmd_reg(void)
{
    unsigned int loop;
	unsigned int idx;

    printk("enter isp_debug_print_cmd_reg.\n");

    for (idx = 0; idx < ISP_CMD_PRINT_MAX; idx++)
    {
        printk("idx=%d,g_cmd_loop_tag[idx]=0x%x\n",idx,g_cmd_loop_tag[idx]);

        if (g_cmd_loop_tag[idx] == ISP_DEBUG_INVALID_TAG)
        {
            break;
        }

        printk("isp_debug_print_cmd_reg:g_cmd_loop_cnt=%d begin.\n",g_cmd_loop_tag[idx]);

    	for(loop = 0; loop < g_cmd_reg_cnt; loop++)
    		printk("0x%x=0x%x\n",g_cmd_reg_key[loop],g_cmd_reg_val[idx][loop]);

        printk("isp_debug_print_cmd_reg:g_cmd_loop_cnt=%d end.\n",g_cmd_loop_tag[idx]);
    }

}

void isp_debug_init_irq_reg(void)
{
	unsigned int reg;
	unsigned int idx;

	g_irq_loop_cnt = 0;
	g_irq_reg_cnt  = 0;

	for(idx = 0; idx < ISP_IRQ_PRINT_MAX; idx++)
		g_irq_loop_tag[idx] = ISP_DEBUG_INVALID_TAG;

	for(reg = 0x63b99; reg <= 0x63ba0; reg++)
		g_irq_reg_key[g_irq_reg_cnt++] = reg;
	for(reg = 0x650f8; reg <= 0x650fb; reg++)
		g_irq_reg_key[g_irq_reg_cnt++] = reg;
	for(reg = 0x671f8; reg <= 0x671fb; reg++)
		g_irq_reg_key[g_irq_reg_cnt++] = reg;
	for(reg = 0x63c42; reg <= 0x63c45; reg++)
		g_irq_reg_key[g_irq_reg_cnt++] = reg;
	for(reg = 0x63b37; reg <= 0x63b3b; reg++)
		g_irq_reg_key[g_irq_reg_cnt++] = reg;
	for(reg = 0x63b55; reg <= 0x63b59; reg++)
		g_irq_reg_key[g_irq_reg_cnt++] = reg;


    /* init from file */
    isp_debug_load_reg("/data/k3_camera/ov-irq-reg.txt",
                       g_irq_reg_key,
                       ISP_IRQ_REG_MAX,
                       &g_irq_reg_cnt);


}

inline void isp_debug_dump_irq_reg(void)
{
    unsigned int loop;
	unsigned int idx;

	if (print_flg == ISP_DBG_PRINT_DIRECT){
	    printk("0x%x=0x%x,0x%x=0x%x,0x%x=0x%x,0x%x=0x%x,0x%x=0x%x,0x%x=0x%x,0x%x=0x%x,0x%x=0x%x,\n",
	            g_irq_reg_key[0],DBG_GETREG8(g_irq_reg_key[0]),
	            g_irq_reg_key[1],DBG_GETREG8(g_irq_reg_key[1]),
	            g_irq_reg_key[2],DBG_GETREG8(g_irq_reg_key[2]),
	            g_irq_reg_key[3],DBG_GETREG8(g_irq_reg_key[3]),
	            g_irq_reg_key[4],DBG_GETREG8(g_irq_reg_key[4]),
	            g_irq_reg_key[5],DBG_GETREG8(g_irq_reg_key[5]),
	            g_irq_reg_key[6],DBG_GETREG8(g_irq_reg_key[6]),
	            g_irq_reg_key[7],DBG_GETREG8(g_irq_reg_key[7]));
	} else if (print_flg == ISP_DBG_PRINT_TO_MEM){
        idx = g_irq_loop_cnt % ISP_IRQ_PRINT_MAX;

        printk("irq=%d.\n",g_irq_loop_cnt);

        g_irq_loop_tag[idx]=g_irq_loop_cnt;
    	for(loop = 0; loop < g_irq_reg_cnt; loop++)
    		g_irq_reg_val[idx][loop] = DBG_GETREG8(g_irq_reg_key[loop]);

        g_irq_loop_cnt++;
    }
}



void isp_debug_print_irq_reg(void)
{
    unsigned int loop;
	unsigned int idx;

    printk("enter isp_debug_print_irq_reg.\n");

    for (idx = 0; idx < ISP_IRQ_PRINT_MAX; idx++)
    {

        printk("idx=%d,g_irq_loop_tag[idx]=0x%x\n",idx,g_irq_loop_tag[idx]);

        if (g_irq_loop_tag[idx] == ISP_DEBUG_INVALID_TAG)
        {
            break;
        }

        printk("irq_loop=%d begin.\n",g_irq_loop_tag[idx]);

    	for(loop = 0; loop < g_irq_reg_cnt; loop++)
    		printk("0x%x=0x%x\n",g_irq_reg_key[loop],g_irq_reg_val[idx][loop]);

        printk("irq_loop=%d end.\n",g_irq_loop_tag[idx]);
    }

}

int isp_debug_init()
{
    /* load debug cfg and regs. */
    isp_debug_load_cfg("/data/k3_camera/ov-isp-cfg.txt","camera.debug.zsl.onlineenable", &zsl_online_enable);
    isp_debug_load_cfg("/data/k3_camera/ov-isp-cfg.txt","camera.debug.zsl.backidx", &zsl_back_idx);
    isp_debug_load_cfg("/data/k3_camera/ov-isp-cfg.txt","camera.debug.printflg", &print_flg);
    isp_debug_load_cfg("/data/k3_camera/ov-isp-cfg.txt", "camera.debug.zsl.copyflg", &zsl_copy_flg);
    isp_debug_load_cfg("/data/k3_camera/ov-isp-cfg.txt", "camera.debug.sensor.apaeflg", &ap_ae_flg);
    isp_debug_load_cfg("/data/k3_camera/ov-isp-cfg.txt", "camera.debug.sensor.colorbarflg", &color_bar_flg);


    print_info("zsl_online_enable=%d", zsl_online_enable);
    print_info("zsl_back_idx=%d", zsl_back_idx);
    print_info("zsl_copy_flg=%d", zsl_copy_flg);
    print_info("print_flg=%d", print_flg);
    print_info("ap_ae_flg=%d", ap_ae_flg);
    print_info("color_bar_flg=%d", color_bar_flg);

    /* load debug regs. */
	isp_debug_init_cmd_reg();
	isp_debug_init_irq_reg();
    return 0;
}


int isp_debug_deinit()
{
    if (print_flg == ISP_DBG_PRINT_TO_MEM){
        msleep(2000);
        isp_debug_print_cmd_reg();
    	isp_debug_print_irq_reg();
	}
    return 0;
}


#endif

/*
 **************************************************************************
 * FunctionName: register_cam_dbg_info;
 * Description : NA;
 * Input       :
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void register_cam_dbg_info(int dbg_info_type, void *context)
{
	switch (dbg_info_type) {
	case DBG_INFO_ISP_BASE:
		{
			cam_dbg_info.dbg_isp_base_addr = (u8*) context;
			print_info("cam_dbg_info.dbg_isp_base_addr=%p", cam_dbg_info.dbg_isp_base_addr);
			break;
		}
	case DBG_INFO_CSI0_BASE:
		{
			cam_dbg_info.dbg_csi0_base_addr = (u8*) context;
			print_info("cam_dbg_info.dbg_csi0_base_addr=%p", cam_dbg_info.dbg_csi0_base_addr);
			break;
		}
	case DBG_INFO_CSI1_BASE:
		{
			cam_dbg_info.dbg_csi1_base_addr = (u8*) context;
			print_info("cam_dbg_info.dbg_csi1_base_addr=%p", cam_dbg_info.dbg_csi1_base_addr);
			break;
		}
	default:
		{
			print_error("%s invalid parameters", __func__);
			break;
		}
	}
}

/*
 **************************************************************************
 * FunctionName: unregister_cam_dbg_info;
 * Description : NA;
 * Input       :
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void unregister_cam_dbg_info(int dbg_info_type)
{
	switch (dbg_info_type) {
	case DBG_INFO_ISP_BASE:
		{
			cam_dbg_info.dbg_isp_base_addr = NULL;
			break;
		}
	case DBG_INFO_CSI0_BASE:
		{
			cam_dbg_info.dbg_csi0_base_addr = NULL;
			break;
		}
	case DBG_INFO_CSI1_BASE:
		{
			cam_dbg_info.dbg_csi1_base_addr = NULL;
			break;
		}
	default:
		{
			print_error("%s invalid parameters", __func__);
			break;
		}
	}
}

/*
 **************************************************************************
 * FunctionName: dump_queue;
 * Description : NA;
 * Input       :
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void dump_queue(struct list_head *list_queue, u32 flag)
{
#ifdef DUMP_QUEUE
	camera_frame_buf *frame = NULL;
	struct list_head *pos = NULL;

	print_info("dump queue flag %d:", flag);
	list_for_each(pos, list_queue) {
		frame = list_entry(pos, camera_frame_buf, queue);
		if (frame)
			print_info("phyaddr:%#x, index:%d", frame->phyaddr, frame->index);
	}
#endif
}
/*
 **************************************************************************
 * FunctionName: dump_file;
 * Description : NA;
 * Input       :
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void dump_file(char *filename, u32 addr, u32 size)
{
#ifdef DUMP_FILE
	struct file *file1 = NULL;
	mm_segment_t old_fs;
	memset(&old_fs, 0x0, sizeof(old_fs));

	print_info("dumpfile %s with size %u", filename, size);
	if (filename == NULL) {
		print_error("dump file with NULL file name!");
		return;
	}
	file1 = filp_open(filename, O_CREAT | O_RDWR, 0644);
	if (IS_ERR(file1)) {
		print_error("error occured while opening file %s, exiting...\n", filename);
		return;
	} else {
		old_fs = get_fs();
		set_fs(KERNEL_DS);
		file1->f_op->write(file1, (char *)addr, size, &file1->f_pos);
		set_fs(old_fs);
		filp_close(file1, NULL);
		return;
	}
#endif
}

/*
 **************************************************************************
 * FunctionName: dump_cmd_reg;
 * Description : NA;
 * Input       :
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void dump_cmd_reg(void)
{
#ifdef	DUMP_CMD_REG
	int i = 0;

	/* command set register range : 0x1e800 ~ 0x1e8 */
	for (i = 0x1e800; i < 0x1e8da; i++)
	{
		print_info("%#x=%#x", i, DBG_GETREG8(i));
	}

	print_info("0x63901=%#x", DBG_GETREG8(0x63901));
	print_info("0x63902=%#x", DBG_GETREG8(0x63902));
	print_info("0x63903=%#x", DBG_GETREG8(0x63903));
	print_info("0x63904=%#x", DBG_GETREG8(0x63904));
	print_info("0x63905=%#x", DBG_GETREG8(0x63905));
	print_info("0x63906=%#x", DBG_GETREG8(0x63906));
	print_info("0x63907=%#x", DBG_GETREG8(0x63907));
	print_info("0x63908=%#x", DBG_GETREG8(0x63908));
	print_info("0x63909=%#x", DBG_GETREG8(0x63909));
	print_info("0x6390a=%#x", DBG_GETREG8(0x6390a));
#endif
}

void dump_ispzyk_reg(void)
{
	unsigned int reg;
	mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "dump command set reg start++++++++++++++++++++++++++++++\n");
	mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "dump command ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	for(reg = 0x1e800; reg < 0x1e8bf; reg++)
		mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "0x%0x:0x%0x\n", reg, DBG_GETREG8(reg));
	for(reg = 0x63900; reg < 0x63917; reg++)
		mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "0x%0x:0x%0x\n", reg, DBG_GETREG8(reg));
	mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "dump MAC ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	for(reg = 0x63b00; reg <= 0x63b1f ; reg++) {
		mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "0x%0x:0x%0x\n", reg, DBG_GETREG8(reg));
	}
	for(reg = 0x63b30; reg <= 0x63b5f ; reg++) {
		mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "0x%0x:0x%0x\n", reg, DBG_GETREG8(reg));
	}
	mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "0x63b78: 0x%0x\n", DBG_GETREG8(0x63b78));
	mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "dump IDI ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	for(reg = 0x63c00; reg <= 0x63c59 ; reg++) {
		mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "0x%0x:0x%0x\n", reg, DBG_GETREG8(reg));
	}
	mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "dump ISP ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	for(reg = 0x65000; reg <= 0x6503f ; reg++) {
		mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "0x%0x:0x%0x\n", reg, DBG_GETREG8(reg));
	}
	for(reg = 0x65050; reg <= 0x6505f ; reg++) {
		mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "0x%0x:0x%0x\n", reg, DBG_GETREG8(reg));
	}
	for(reg = 0x650f0; reg <= 0x650fb ; reg++) {
		mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "0x%0x:0x%0x\n", reg, DBG_GETREG8(reg));
	}
	for(reg = 0x671f0; reg <= 0x671fb ; reg++) {
		mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "0x%0x:0x%0x\n", reg, DBG_GETREG8(reg));
	}
	for(reg = 0x63b20; reg <= 0x63b23 ; reg++) {
		mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "0x%0x:0x%0x\n", reg, DBG_GETREG8(reg));
	}
	for(reg = 0x63b28; reg <= 0x63b2b ; reg++) {
		mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "0x%0x:0x%0x\n", reg, DBG_GETREG8(reg));
	}
	mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "dump Sys ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "0x63022: 0x%0x\n", DBG_GETREG8(reg));
	for(reg = 0x63106; reg <= 0x63109 ; reg++) {
		mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "0x%0x:0x%0x\n", reg, DBG_GETREG8(reg));
	}
	mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "dump MCU ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	for(reg = 0x1c781; reg <= 0x1c786 ; reg++) {
		mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "0x%0x:0x%0x\n", reg, DBG_GETREG8(reg));
	}
	for(reg = 0x1d920; reg <= 0x1d96f ; reg++) {
		mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "0x%0x:0x%0x\n", reg, DBG_GETREG8(reg));
	}
	for(reg = 0x1c5e8; reg <= 0x1c5e9 ; reg++) {
		mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "0x%0x:0x%0x\n", reg, DBG_GETREG8(reg));
	}
	mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "dump ACE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

	for(reg = 0x1c150; reg <= 0x1c15f ; reg++) {
		mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "0x%0x:0x%0x\n", reg, DBG_GETREG8(reg));
	}

	for(reg = 0x1c52C; reg <= 0x1c573 ; reg++) {
		mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "0x%0x:0x%0x\n", reg, DBG_GETREG8(reg));
	}
	mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "dump command set reg end++++++++++++++++++++++++++++++\n");
}


void dump_status_after_reg (void)
{
        unsigned int reg;

	for(reg = 0x63c42; reg <= 0x63c45 ; reg++) {
		mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "0x%0x:0x%0x\n", reg, DBG_GETREG8(reg));
	}
	for(reg = 0x65037; reg <= 0x6503a ; reg++) {
		mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "0x%0x:0x%0x\n", reg, DBG_GETREG8(reg));
	}
	for(reg = 0x650f0; reg <= 0x650fb ; reg++) {
		mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "0x%0x:0x%0x\n", reg, DBG_GETREG8(reg));
	}
	for(reg = 0x63b8e; reg <= 0x63b8f ; reg++) {
		mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "0x%0x:0x%0x\n", reg, DBG_GETREG8(reg));
	}
}
/*
 **************************************************************************
 * FunctionName: dump_sensor_reg;
 * Description : NA;
 * Input       :
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void dump_sensor_reg(u32 addr)
{
	DBG_SETREG8(0x63602, (addr >> 8) & 0xff);
	DBG_SETREG8(0x63603, addr & 0xff);
	DBG_SETREG8(0x63609, 0x33);
	msleep(10);
	DBG_SETREG8(0x63609, 0xf9);
	msleep(4);
	print_info("dump sensor: 0x%0x 0x%0x", addr, DBG_GETREG8(0x63608));
}

/*
 **************************************************************************
 * FunctionName: dump_size_reg;
 * Description : NA;
 * Input       :
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void dump_size_reg(void)
{
#ifdef DUMP_SIZE_REG
	print_info("enter %s", __func__);
	print_info("0x63b34 is 0x%0x", DBG_GETREG8(0x63b34));

	print_info("=write img width=");
	print_info("0x63b36 is 0x%0x", DBG_GETREG8(0x63b36));
	print_info("0x63b37 is 0x%0x", DBG_GETREG8(0x63b37));
	print_info("=write img height=");
	print_info("0x63b3a is 0x%0x", DBG_GETREG8(0x63b3a));
	print_info("0x63b3b is 0x%0x", DBG_GETREG8(0x63b3b));
	print_info("=write mem width=");
	print_info("0x63b38 is 0x%0x", DBG_GETREG8(0x63b38));
	print_info("0x63b39 is 0x%0x", DBG_GETREG8(0x63b39));

	print_info("=isp input width=");
	print_info("0x65010 is 0x%0x", DBG_GETREG8(0x65010));
	print_info("0x65011 is 0x%0x", DBG_GETREG8(0x65011));
	print_info("=isp input height=");
	print_info("0x65012 is 0x%0x", DBG_GETREG8(0x65012));
	print_info("0x65013 is 0x%0x", DBG_GETREG8(0x65013));

	print_info("=raw scale down=");
	print_info("0x65000 is 0x%0x", DBG_GETREG8(0x65000));
	print_info("0x65080 is 0x%0x", DBG_GETREG8(0x65080));
	print_info("=raw scale output size=");
	print_info("0x65032 is 0x%0x", DBG_GETREG8(0x65032));
	print_info("0x65033 is 0x%0x", DBG_GETREG8(0x65033));
	print_info("0x65034 is 0x%0x", DBG_GETREG8(0x65034));
	print_info("0x65035 is 0x%0x", DBG_GETREG8(0x65035));

	print_info("=yuv scale down switch=");
	print_info("0x65002 is 0x%0x", DBG_GETREG8(0x65002));
	print_info("=yuv dcw=");
	print_info("0x65023 is 0x%0x", DBG_GETREG8(0x65023));
	print_info("=yuv scale down=");
	print_info("0x65024 is 0x%0x", DBG_GETREG8(0x65024));
	print_info("0x65025 is 0x%0x", DBG_GETREG8(0x65025));

	print_info("=yuv scale up=");
	print_info("0x65026 is 0x%0x", DBG_GETREG8(0x65026));
	print_info("0x65027 is 0x%0x", DBG_GETREG8(0x65027));
	print_info("0x65028 is 0x%0x", DBG_GETREG8(0x65028));
	print_info("0x65029 is 0x%0x", DBG_GETREG8(0x65029));

	print_info("yuv scale out size");
	print_info("0x65014 is 0x%0x", DBG_GETREG8(0x65014));
	print_info("0x65015 is 0x%0x", DBG_GETREG8(0x65015));
	print_info("0x65016 is 0x%0x", DBG_GETREG8(0x65016));
	print_info("0x65017 is 0x%0x", DBG_GETREG8(0x65017));

	print_info("=yuv crop size=");
	print_info("0x650f4 is 0x%0x", DBG_GETREG8(0x650f4));
	print_info("0x650f5 is 0x%0x", DBG_GETREG8(0x650f5));
	print_info("0x650f6 is 0x%0x", DBG_GETREG8(0x650f6));
	print_info("0x650f7 is 0x%0x", DBG_GETREG8(0x650f7));

	print_info("=image vsize for 3d mode=");
	print_info("0x63106 is 0x%0x", DBG_GETREG8(0x63106));
	print_info("0x63107 is 0x%0x", DBG_GETREG8(0x63107));
	print_info("= IDI size=");
	print_info("0x63c04 is 0x%0x", DBG_GETREG8(0x63c04));
	print_info("0x63c05 is 0x%0x", DBG_GETREG8(0x63c05));
	print_info("0x63c06 is 0x%0x", DBG_GETREG8(0x63c06));
	print_info("0x63c07 is 0x%0x", DBG_GETREG8(0x63c07));
#endif
}

/***********************************************************************************
* Function:       dump_isp_size_reg
* Description:    dump CSI output, IDI output, ISP input YUV crop input reg
* Data Accessed:
* Data Updated:
* Input:                       NA
* Output:                     NA
* Return:                     NA
* Others:
***********************************************************************************/
void dump_isp_size_reg(void)
{
       print_info("enter %s", __func__);
       //CSI output channel1 , pixel counter
       print_info("0x63c52:0x%0x", DBG_GETREG8(0x63c52));
       print_info("0x63c53:0x%0x", DBG_GETREG8(0x63c53));

       //CSI output channel2 , pixel counter
       print_info("0x63c54:0x%0x", DBG_GETREG8(0x63c54));
       print_info("0x63c55:0x%0x", DBG_GETREG8(0x63c55));

       //IDI output channel1 , pixel counter
       print_info("0x63c42:0x%0x", DBG_GETREG8(0x63c42));
       print_info("0x63c43:0x%0x", DBG_GETREG8(0x63c43));

       //IDI output channel1 , line counter
       print_info("0x63c44:0x%0x", DBG_GETREG8(0x63c44));
       print_info("0x63c45:0x%0x", DBG_GETREG8(0x63c45));

       //IDI output channel2 , pixel counter
       print_info("0x63c46:0x%0x", DBG_GETREG8(0x63c46));
       print_info("0x63c47:0x%0x", DBG_GETREG8(0x63c47));

       //IDI output channel2 , line counter
       print_info("0x63c48:0x%0x", DBG_GETREG8(0x63c48));
       print_info("0x63c49:0x%0x", DBG_GETREG8(0x63c49));

       //CLK cnt
       print_info("0x63c58:0x%0x", DBG_GETREG8(0x63c58));
       print_info("0x63c59:0x%0x", DBG_GETREG8(0x63c59));

       //ISP input, pixel counter
       print_info("0x65037:0x%0x", DBG_GETREG8(0x65037));
       print_info("0x65038:0x%0x", DBG_GETREG8(0x65038));

       //ISP input, line counter
       print_info("0x65039:0x%0x", DBG_GETREG8(0x65039));
	print_info("0x6503a:0x%0x", DBG_GETREG8(0x6503a));

       //YUV1 crop input, pixel counter
       print_info("0x650f8:0x%0x", DBG_GETREG8(0x650f8));
       print_info("0x650f9:0x%0x", DBG_GETREG8(0x650f9));

       //YUV1 crop input, line counter
       print_info("0x650fa:0x%0x", DBG_GETREG8(0x650fa));
       print_info("0x650fb:0x%0x", DBG_GETREG8(0x650fb));

       //YUV2 crop input, pixel counter
       print_info("0x671f8:0x%0x", DBG_GETREG8(0x671f8));
       print_info("0x671f9:0x%0x", DBG_GETREG8(0x671f9));

       //YUV2 crop input, line counter
       print_info("0x671fa:0x%0x", DBG_GETREG8(0x671fa));
       print_info("0x671fb:0x%0x", DBG_GETREG8(0x671fb));

}

/***********************************************************************************
* Function:       dump_isp_cmd_reg
* Description:    dump ISP cmd set reg
* Data Accessed:
* Data Updated:
* Input:                NA
* Output:               NA
* Return:             NA
* Others:
***********************************************************************************/
void dump_isp_cmd_reg(void)
{
       //ISP cmd set reg
       //I2C idle/busy flag
       print_info("0x1c5a2:0x%0x", DBG_GETREG8(0x1c5a2));
       print_info("0x1c5a3:0x%0x", DBG_GETREG8(0x1c5a3));

       print_info("0x1dad8:0x%0x", DBG_GETREG8(0x1dad8));
       print_info("0x1dad9:0x%0x", DBG_GETREG8(0x1dad9));

       //cmd set reg
       print_info("0x63900:0x%0x", DBG_GETREG8(0x63900));
       print_info("0x63901:0x%0x", DBG_GETREG8(0x63901));
       print_info("0x63902:0x%0x", DBG_GETREG8(0x63902));
       print_info("0x63903:0x%0x", DBG_GETREG8(0x63903));
       print_info("0x63904:0x%0x", DBG_GETREG8(0x63904));
       print_info("0x63905:0x%0x", DBG_GETREG8(0x63905));
       print_info("0x63906:0x%0x", DBG_GETREG8(0x63906));
       print_info("0x63907:0x%0x", DBG_GETREG8(0x63907));
       print_info("0x63908:0x%0x", DBG_GETREG8(0x63908));
       print_info("0x63909:0x%0x", DBG_GETREG8(0x63909));
       print_info("0x6390a:0x%0x", DBG_GETREG8(0x6390a));
       print_info("0x6390b:0x%0x", DBG_GETREG8(0x6390b));
       print_info("0x6390c:0x%0x", DBG_GETREG8(0x6390c));
       print_info("0x6390d:0x%0x", DBG_GETREG8(0x6390d));
       print_info("0x6390e:0x%0x", DBG_GETREG8(0x6390e));
       print_info("0x6390f:0x%0x", DBG_GETREG8(0x6390f));
       print_info("0x63910:0x%0x", DBG_GETREG8(0x63910));
       print_info("0x63911:0x%0x", DBG_GETREG8(0x63911));
	print_info("0x63912:0x%0x", DBG_GETREG8(0x63912));

       //FW data buffer
	print_info("0x1c000:0x%0x", DBG_GETREG8(0x1c000));
	print_info("0x1c001:0x%0x", DBG_GETREG8(0x1c001));
	print_info("0x1c002:0x%0x", DBG_GETREG8(0x1c002));
	print_info("0x1c003:0x%0x", DBG_GETREG8(0x1c003));
	print_info("0x1c004:0x%0x", DBG_GETREG8(0x1c004));
	print_info("0x1c005:0x%0x", DBG_GETREG8(0x1c005));
	print_info("0x1c006:0x%0x", DBG_GETREG8(0x1c006));
	print_info("0x1c007:0x%0x", DBG_GETREG8(0x1c007));
	print_info("0x1c008:0x%0x", DBG_GETREG8(0x1c008));
	print_info("0x1c009:0x%0x", DBG_GETREG8(0x1c009));
	print_info("0x1c00a:0x%0x", DBG_GETREG8(0x1c00a));
	print_info("0x1c00b:0x%0x", DBG_GETREG8(0x1c00b));
	print_info("0x1c00c:0x%0x", DBG_GETREG8(0x1c00c));
	print_info("0x1c00d:0x%0x", DBG_GETREG8(0x1c00d));
	print_info("0x1c00e:0x%0x", DBG_GETREG8(0x1c00e));
	print_info("0x1c00f:0x%0x", DBG_GETREG8(0x1c00f));

       //SCCB Master 1
	print_info("0x63600:0x%0x", DBG_GETREG8(0x63600));
	print_info("0x63601:0x%0x", DBG_GETREG8(0x63601));
	print_info("0x63602:0x%0x", DBG_GETREG8(0x63602));
	print_info("0x63603:0x%0x", DBG_GETREG8(0x63603));
	print_info("0x63604:0x%0x", DBG_GETREG8(0x63604));
	print_info("0x63605:0x%0x", DBG_GETREG8(0x63605));
	print_info("0x63606:0x%0x", DBG_GETREG8(0x63606));
	print_info("0x63607:0x%0x", DBG_GETREG8(0x63607));
	print_info("0x63608:0x%0x", DBG_GETREG8(0x63608));
	print_info("0x63609:0x%0x", DBG_GETREG8(0x63609));
	print_info("0x6360a:0x%0x", DBG_GETREG8(0x6360a));

       //SCCB Master 2
	print_info("0x63700:0x%0x", DBG_GETREG8(0x63700));
	print_info("0x63701:0x%0x", DBG_GETREG8(0x63701));
	print_info("0x63702:0x%0x", DBG_GETREG8(0x63702));
	print_info("0x63703:0x%0x", DBG_GETREG8(0x63703));
	print_info("0x63704:0x%0x", DBG_GETREG8(0x63704));
	print_info("0x63705:0x%0x", DBG_GETREG8(0x63705));
	print_info("0x63706:0x%0x", DBG_GETREG8(0x63706));
	print_info("0x63707:0x%0x", DBG_GETREG8(0x63707));
	print_info("0x63708:0x%0x", DBG_GETREG8(0x63708));
	print_info("0x63709:0x%0x", DBG_GETREG8(0x63709));
	print_info("0x6370a:0x%0x", DBG_GETREG8(0x6370a));
}

void dump_isp_reg(int start, int size)
{
	int reg_addr;

	for (reg_addr = start; reg_addr < (start + size); reg_addr++) {
		if ((reg_addr % 16) == 0)
			mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "0x%5x:", reg_addr);

		mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "0x%2x ", DBG_GETREG8(reg_addr));

		if (((reg_addr + 1) % 16) == 0)
			mntn_print_log(EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE, EN_VIDEO_LOG_LEVLE_INFO, "\n");
	}
}

void dump_isp_mac_reg(void)
{
	unsigned int reg;
	unsigned int val;

	if (cam_dbg_info.dbg_isp_base_addr == NULL){
        printk(KERN_ERR "isp is not running.\n");
	    return;
	}

    printk(KERN_ERR "isp cmdset para:\n");
	for(reg = 0x63900; reg <= 0x63911; reg++)
        printk(KERN_ERR "0x%0x=0x%0x\n", reg, DBG_GETREG8(reg));

    reg=0x63b30;printk(KERN_ERR "0x%0x=0x%0x\n", reg, DBG_GETREG8(reg));
    reg=0x63b31;printk(KERN_ERR "0x%0x=0x%0x\n", reg, DBG_GETREG8(reg));

    printk(KERN_ERR "mac channel 0:\n");
    reg=0x63b00;DBG_GETREG32(reg,val);printk(KERN_ERR "0x%0x=0x%0x\n", reg, val);
    reg=0x63b04;DBG_GETREG32(reg,val);printk(KERN_ERR "0x%0x=0x%0x\n", reg, val);
    reg=0x63b70;DBG_GETREG32(reg,val);printk(KERN_ERR "0x%0x=0x%0x\n", reg, val);
    reg=0x63b10;DBG_GETREG32(reg,val);printk(KERN_ERR "0x%0x=0x%0x\n", reg, val);
    reg=0x63b14;DBG_GETREG32(reg,val);printk(KERN_ERR "0x%0x=0x%0x\n", reg, val);
    reg=0x63b74;DBG_GETREG32(reg,val);printk(KERN_ERR "0x%0x=0x%0x\n", reg, val);

    printk(KERN_ERR "zsl cap all:\n");
    reg=0x1d950;DBG_GETREG32(reg,val);printk(KERN_ERR "0x%0x=0x%0x\n", reg, val);
    reg=0x1d954;DBG_GETREG32(reg,val);printk(KERN_ERR "0x%0x=0x%0x\n", reg, val);
    reg=0x1d958;DBG_GETREG32(reg,val);printk(KERN_ERR "0x%0x=0x%0x\n", reg, val);
    reg=0x1d95c;DBG_GETREG32(reg,val);printk(KERN_ERR "0x%0x=0x%0x\n", reg, val);
    reg=0x1d960;DBG_GETREG32(reg,val);printk(KERN_ERR "0x%0x=0x%0x\n", reg, val);
    reg=0x1d964;DBG_GETREG32(reg,val);printk(KERN_ERR "0x%0x=0x%0x\n", reg, val);
    reg=0x1d968;DBG_GETREG32(reg,val);printk(KERN_ERR "0x%0x=0x%0x\n", reg, val);
    reg=0x1d96c;DBG_GETREG32(reg,val);printk(KERN_ERR "0x%0x=0x%0x\n", reg, val);

    printk(KERN_ERR "zsl proc,read,left&right:\n");
    reg=0x63b20;DBG_GETREG32(reg,val);printk(KERN_ERR "0x%0x=0x%0x\n", reg, val);
    reg=0x63b28;DBG_GETREG32(reg,val);printk(KERN_ERR "0x%0x=0x%0x\n", reg, val);

    printk(KERN_ERR "zsl cap raw&yuv write or zsl proc write,left&right:\n");
    reg=0x63b0c;DBG_GETREG32(reg,val);printk(KERN_ERR "0x%0x=0x%0x\n", reg, val);
    reg=0x63b60;DBG_GETREG32(reg,val);printk(KERN_ERR "0x%0x=0x%0x\n", reg, val);
    reg=0x63b1c;DBG_GETREG32(reg,val);printk(KERN_ERR "0x%0x=0x%0x\n", reg, val);
    reg=0x63b68;DBG_GETREG32(reg,val);printk(KERN_ERR "0x%0x=0x%0x\n", reg, val);

}

EXPORT_SYMBOL(dump_isp_mac_reg);

/***********************************************************************************
* Function:       dump_isp_mac_size_reg
* Description:    dump SCCTRL/AO_SCCTRL/PMCTRL register about ISP/CSI power on/off,
                  rst en/dis, clk en/dis.
* Data Accessed:
* Data Updated:
* Input:                NA
* Output:                NA
* Return:                NA
* Others:
***********************************************************************************/
void dump_isp_mac_size_reg(void)
{
       //MAC debug
       print_info("0x63b80:0x%0x", DBG_GETREG8(0x63b80));
       print_info("0x63b81:0x%0x", DBG_GETREG8(0x63b81));
       print_info("0x63b82:0x%0x", DBG_GETREG8(0x63b82));
       print_info("0x63b83:0x%0x", DBG_GETREG8(0x63b83));
       print_info("0x63b84:0x%0x", DBG_GETREG8(0x63b84));
       print_info("0x63b85:0x%0x", DBG_GETREG8(0x63b85));
       print_info("0x63b86:0x%0x", DBG_GETREG8(0x63b86));
       print_info("0x63b87:0x%0x", DBG_GETREG8(0x63b87));

       //write count
       print_info("0x63b88:0x%0x", DBG_GETREG8(0x63b88));
       print_info("0x63b89:0x%0x", DBG_GETREG8(0x63b89));
       print_info("0x63b8a:0x%0x", DBG_GETREG8(0x63b8a));
       print_info("0x63b8b:0x%0x", DBG_GETREG8(0x63b8b));

       //buffer 0 x/y count
       print_info("0x63b8c:0x%0x", DBG_GETREG8(0x63b8c));
       print_info("0x63b8d:0x%0x", DBG_GETREG8(0x63b8d));
       print_info("0x63b8e:0x%0x", DBG_GETREG8(0x63b8e));
       print_info("0x63b8f:0x%0x", DBG_GETREG8(0x63b8f));

       //buffer 1 x/y count
       print_info("0x63b90:0x%0x", DBG_GETREG8(0x63b90));
       print_info("0x63b91:0x%0x", DBG_GETREG8(0x63b91));
       print_info("0x63b92:0x%0x", DBG_GETREG8(0x63b92));
       print_info("0x63b93:0x%0x", DBG_GETREG8(0x63b93));
       print_info("0x63b94:0x%0x", DBG_GETREG8(0x63b94));

       //write latch count
       print_info("0x63b95:0x%0x", DBG_GETREG8(0x63b95));
       print_info("0x63b96:0x%0x", DBG_GETREG8(0x63b96));
       print_info("0x63b97:0x%0x", DBG_GETREG8(0x63b97));
       print_info("0x63b98:0x%0x", DBG_GETREG8(0x63b98));

       //buffer 0 x/y latch count
       print_info("0x63b99:0x%0x", DBG_GETREG8(0x63b99));
       print_info("0x63b9a:0x%0x", DBG_GETREG8(0x63b9a));
       print_info("0x63b9b:0x%0x", DBG_GETREG8(0x63b9b));
       print_info("0x63b9c:0x%0x", DBG_GETREG8(0x63b9c));

       //buffer 1 x/y latch count
       print_info("0x63b9d:0x%0x", DBG_GETREG8(0x63b9d));
       print_info("0x63b9e:0x%0x", DBG_GETREG8(0x63b9e));
       print_info("0x63b9f:0x%0x", DBG_GETREG8(0x63b9f));
       print_info("0x63ba0:0x%0x", DBG_GETREG8(0x63ba0));

       //MAC output channel 1 X count
       print_info("0x63b99:0x%0x", DBG_GETREG8(0x63b99));
       print_info("0x63b9a:0x%0x", DBG_GETREG8(0x63b9a));

       //MAC output channel 1 Y count
       print_info("0x63b9b:0x%0x", DBG_GETREG8(0x63b9b));
       print_info("0x63b9c:0x%0x", DBG_GETREG8(0x63b9c));

       //MAC output channel 2 X count
       print_info("0x63b9d:0x%0x", DBG_GETREG8(0x63b9d));
       print_info("0x63b9e:0x%0x", DBG_GETREG8(0x63b9e));

       //MAC output channel 2 Y count
       print_info("0x63b9f:0x%0x", DBG_GETREG8(0x63b9f));
       print_info("0x63ba0:0x%0x", DBG_GETREG8(0x63ba0));
}
EXPORT_SYMBOL(dump_isp_mac_size_reg);

#ifdef DUMP_SCCTRL_ISP_REG
/***********************************************************************************
* Function:       dump_scctrl_isp_reg
* Description:    dump SCCTRL/AO_SCCTRL/PMCTRL register about ISP/CSI power on/off,
                  rst en/dis, clk en/dis.
* Data Accessed:
* Data Updated:
* Input:		  NA
* Output:
* Return:		  0
* Others:
***********************************************************************************/
void dump_scctrl_isp_reg(void)
{
    unsigned int reg_value;

    reg_value = phy_reg_readl(SOC_AO_SCTRL_BASE_ADDR, SOC_AO_SCTRL_SC_PW_MTCMOS_STAT0_ADDR(0), 0, 31);
    print_info("%s, SOC_AO_SCTRL_SC_PW_MTCMOS_STAT0_ADDR = 0x%0x,", __func__, reg_value);

    reg_value = phy_reg_readl(SOC_PMCTRL_BASE_ADDR, SOC_PMCTRL_MEDPLLCTRL_ADDR(0), 0, 31);
    print_info("%s, SOC_PMCTRL_MEDPLLCTRL_ADDR = 0x%0x,", __func__, reg_value);

    reg_value = phy_reg_readl(SOC_MEDIA_SCTRL_BASE_ADDR, SOC_MEDIA_SCTRL_SC_MEDIA_NOC_DFS_ADDR(0), 0, 31);
    print_info("%s, SOC_MEDIA_SCTRL_SC_MEDIA_NOC_DFS_ADDR = 0x%0x,", __func__, reg_value);

    reg_value = phy_reg_readl(SOC_MEDIA_SCTRL_BASE_ADDR, SOC_MEDIA_SCTRL_SC_MEDIA_CLKCFG0_ADDR(0), 0, 31);
    print_info("%s, SOC_MEDIA_SCTRL_SC_MEDIA_CLKCFG0_ADDR = 0x%0x,", __func__, reg_value);

    reg_value = phy_reg_readl(SOC_PMCTRL_BASE_ADDR, SOC_PMCTRL_DDRCLKDIVCFG_ADDR(0), 0, 31);
    print_info("%s, SOC_PMCTRL_DDRCLKDIVCFG_ADDR = 0x%0x,", __func__, reg_value);

    reg_value = phy_reg_readl(SOC_AO_SCTRL_BASE_ADDR, SOC_AO_SCTRL_SC_PW_RST_STAT0_ADDR(0), 0, 31);
    print_info("%s, SOC_AO_SCTRL_SC_PW_RST_STAT0_ADDR = 0x%0x,", __func__, reg_value);

    reg_value = phy_reg_readl(SOC_AO_SCTRL_BASE_ADDR, SOC_AO_SCTRL_SC_PW_ISO_STAT0_ADDR(0), 0, 31);
    print_info("%s, SOC_AO_SCTRL_SC_PW_ISO_STAT0_ADDR = 0x%0x,", __func__, reg_value);

    reg_value = phy_reg_readl(SOC_AO_SCTRL_BASE_ADDR, SOC_AO_SCTRL_SC_PW_CLK_STAT0_ADDR(0), 0, 31);
    print_info("%s, SOC_AO_SCTRL_SC_PW_CLK_STAT0_ADDR = 0x%0x,", __func__, reg_value);

    reg_value = phy_reg_readl(SOC_MEDIA_SCTRL_BASE_ADDR, SOC_MEDIA_SCTRL_SC_MEDIA_RST_STAT_ADDR(0), 0, 31);
    print_info("%s, SOC_MEDIA_SCTRL_SC_MEDIA_RST_STAT_ADDR = 0x%0x,", __func__, reg_value);

    reg_value = phy_reg_readl(SOC_MEDIA_SCTRL_BASE_ADDR, SOC_MEDIA_SCTRL_SC_MEDIA_CLK_STAT_ADDR(0), 0, 31);
    print_info("%s, SOC_MEDIA_SCTRL_SC_MEDIA_CLK_STAT_ADDR = 0x%0x,", __func__, reg_value);

}
#endif

/*
 **************************************************************************
 * FunctionName: get_cam_pwdn_status;
 * Description : get camera pwdn status, include isp/csi/sensor
 * Input       :
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
u32 get_cam_pwdn_status(int module)
{
    u32 status = 0;

   	switch (module) {
	case DEBUGFS_PWDN_ISP:
		{
			status = cam_pwdn_status.isp_pwdn_status;
			print_debug("%s, isp_pwdn_status = %d", __func__, cam_pwdn_status.isp_pwdn_status);
			break;
		}
	case DEBUGFS_PWDN_CSI:
		{
			status = cam_pwdn_status.csi_pwdn_status;
			print_debug("%s, csi_pwdn_status = %d", __func__, cam_pwdn_status.csi_pwdn_status);
			break;
		}
	case DEBUGFS_PWDN_SENSOR:
		{
			status = cam_pwdn_status.sensor_pwdn_status;
			print_debug("%s, sensor_pwdn_status = %d", __func__, cam_pwdn_status.sensor_pwdn_status);
			break;
		}
	default:
		{
			print_error("%s, invalid parameters", __func__);
			break;
		}
	}

    return status;
}

/*
 **************************************************************************
 * FunctionName: set_cam_pwdn_status;
 * Description : set camera pwdn status, include isp/csi/sensor
 * Input       :
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void set_cam_pwdn_status(int module, u32 status)
{
   	switch (module) {
	case DEBUGFS_PWDN_ISP:
		{
			cam_pwdn_status.isp_pwdn_status = status;
			print_info("%s, isp_pwdn_status = %d", __func__, cam_pwdn_status.isp_pwdn_status);
			break;
		}
	case DEBUGFS_PWDN_CSI:
		{
			cam_pwdn_status.csi_pwdn_status = status;
			print_info("%s, csi_pwdn_status = %d", __func__, cam_pwdn_status.csi_pwdn_status);
			break;
		}
	case DEBUGFS_PWDN_SENSOR:
		{
			cam_pwdn_status.sensor_pwdn_status = status;
			print_info("%s, sensor_pwdn_status = %d", __func__, cam_pwdn_status.sensor_pwdn_status);
			break;
		}
	default:
		{
			print_error("%s, invalid parameters", __func__);
			break;
		}
	}
}

/*
 **************************************************************************
 * FunctionName: get_cam_dbgfs_pwdncfg;
 * Description : get camera debugfs config
 * Input       :
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
u32 get_cam_dbgfs_pwdncfg(void)
{
    return cam_dbgfs_pwdncfg;
}
#define MTCOMS_ISP (1<<2)
#define MEDPLL_ISP (1)
#define RST_ISP (1<< 2)

#define RST_SOFT_ISP (1<< 4)
#define SOFT_CLK_GATE_ISP (1<< 5)
#define SOFT_SCLK_ISP (1<< 11)
#define SOFT_SCLK2_ISP (1<< 12)

#define CLK_STATE_ISP (SOFT_SCLK2_ISP|SOFT_SCLK_ISP|SOFT_CLK_GATE_ISP)

int check_videoharden_power(void)
{
	u32 reg_value = 0;

	reg_value = phy_reg_readl(SOC_AO_SCTRL_BASE_ADDR, SOC_AO_SCTRL_SC_PW_MTCMOS_STAT0_ADDR(0), 0, 31);

	if(!(reg_value &MTCOMS_ISP)){
	    print_info("%s, SOC_AO_SCTRL_SC_PW_MTCMOS_STAT0_ADDR bit[2] = 0x%0x,", __func__, reg_value);
	    return -1;

	}

	reg_value = phy_reg_readl(SOC_PMCTRL_BASE_ADDR, SOC_PMCTRL_MEDPLLCTRL_ADDR(0), 0, 31);
	if(!(reg_value &MEDPLL_ISP)){
	    print_info("%s, SOC_PMCTRL_MEDPLLCTRL_ADDR bit[0]= 0x%0x,", __func__, reg_value);

	    return -1;

	}

    	reg_value = phy_reg_readl(SOC_AO_SCTRL_BASE_ADDR, SOC_AO_SCTRL_SC_PW_RST_STAT0_ADDR(0), 0, 31);
	if(reg_value &RST_ISP){
	    print_info("%s, SOC_AO_SCTRL_SC_PW_RST_STAT0_ADDR bit[2] = 0x%0x,", __func__, reg_value);

	    return -1;

	}

   	 reg_value = phy_reg_readl(SOC_AO_SCTRL_BASE_ADDR, SOC_AO_SCTRL_SC_PW_ISO_STAT0_ADDR(0), 0, 31);
	if(reg_value &RST_ISP){
	    print_info("%s, SOC_AO_SCTRL_BASE_ADDR bit[2] = 0x%0x,", __func__, reg_value);
	    return -1;

	}

    	reg_value = phy_reg_readl(SOC_AO_SCTRL_BASE_ADDR, SOC_AO_SCTRL_SC_PW_CLK_STAT0_ADDR(0), 0, 31);
	if(!(reg_value &RST_ISP)){
	    print_info("%s, SOC_AO_SCTRL_SC_PW_CLK_STAT0_ADDR bit[2] = 0x%0x,", __func__, reg_value);
	    return -1;

	}

   	 reg_value = phy_reg_readl(SOC_MEDIA_SCTRL_BASE_ADDR, SOC_MEDIA_SCTRL_SC_MEDIA_RST_STAT_ADDR(0), 0, 31);
   	 if(reg_value &RST_SOFT_ISP){
	    print_info("%s, SOC_MEDIA_SCTRL_SC_MEDIA_RST_STAT_ADDR soft reset bit[4] = 0x%0x,", __func__, reg_value);

	    return -1;

	}

    	reg_value = phy_reg_readl(SOC_MEDIA_SCTRL_BASE_ADDR, SOC_MEDIA_SCTRL_SC_MEDIA_CLK_STAT_ADDR(0), 0, 31);
   	 if(CLK_STATE_ISP !=(reg_value &CLK_STATE_ISP)){
	    print_info("%s, SOC_MEDIA_SCTRL_SC_MEDIA_CLK_STAT_ADDR soft gate bit[4] bit[11] bit[12]= 0x%0x,", __func__, (reg_value &CLK_STATE_ISP));

	    return -1;

	}

	return 0;
}

#ifdef CONFIG_DEBUG_FS
/*
 **************************************************************************
 * FunctionName: flash_test_help;
 * Description : flash test help
 * Input       :
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void flash_test_help(void)
{
    printk("[%s], Usage:   echo mode action lum timeout > flash.\n", __func__);
    printk("[%s],      mode   : 0--flash mode, 1--torch mode .\n", __func__);
    printk("[%s],      action : 0--off, 1--on.\n", __func__);
    printk("[%s],      lum    : flash mode, 0~15.\n", __func__);
    printk("[%s],               torch mode, 0~7.\n", __func__);
    printk("[%s],      timout : flash mode, used as timeout(0~7).\n", __func__);
}

/*
 **************************************************************************
 * FunctionName: flash_test_open;
 * Description : open flash test file
 * Input       :
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int flash_test_open(struct inode *inode, struct file *filp)
{
    printk("enter %s.\n", __func__);
    filp->private_data = inode->i_private;
    return 0;
}

/*
 **************************************************************************
 * FunctionName: flash_test_read;
 * Description : read flash test file
 * Input       :
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static ssize_t flash_test_read(struct file *filp, char __user *buffer,
    size_t count, loff_t *ppos)
{
    char tips[CAM_DEBUGFS_FLASH_FILE_MAXSIZE] = "help!\n";

    if (*ppos >= CAM_DEBUGFS_FLASH_FILE_MAXSIZE)
        return 0;

    if (*ppos +count > CAM_DEBUGFS_FLASH_FILE_MAXSIZE) {
        count = CAM_DEBUGFS_FLASH_FILE_MAXSIZE - *ppos;
    }

    if (copy_to_user(buffer, tips + *ppos, count)) {
        return -EFAULT;
    }

    *ppos += count;

    flash_test_help();

    return count;
}

/*
 **************************************************************************
 * FunctionName: flash_test_write;
 * Description : write flash test file
 * Input       :
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static ssize_t flash_test_write(struct file *filp, const char __user *buffer,
    size_t count, loff_t *ppos)
{
    char charinfo[CAM_DEBUGFS_FLASH_FILE_MAXSIZE];
    u8 mode = 0;
    u8 lum = 0;
    u8 timeout = 9;
    u8 action = 0;
    u32 index = 0;
    camera_flashlight *flashlight = NULL;

	print_info("enter %s", __func__);

    flashlight = get_camera_flash();
    if (NULL == flashlight) {
        printk(KERN_ERR "%s, flashlight null.\n", __func__);
        return -EFAULT;
    }

    if ((count < 6) || (count > CAM_DEBUGFS_FLASH_FILE_MAXSIZE)) {
        flash_test_help();
        return -EFAULT;
    }

    memset(charinfo, 0, CAM_DEBUGFS_FLASH_FILE_MAXSIZE);

    if (copy_from_user(charinfo, buffer, count)) {
        return -EFAULT;
    }
    printk("%s, length = %zu, %s", __func__, count, charinfo);

    /*parser mode*/
    index = 0;
    if ((charinfo[index] != '0') && (charinfo[index] != '1')) {
        printk("%s, mode %c is error.\n", __func__, charinfo[index]);
        flash_test_help();
        return -EFAULT;
    }
    mode = charinfo[index] - 48;
    index += 2;

    /*parser on/off*/
    if ((charinfo[index] != '0') && (charinfo[index] != '1')) {
        printk("%s, turnon %c is error.\n", __func__, charinfo[index]);
        return -EFAULT;
    }
    action = charinfo[index] - 48;
    index += 2;

    /*parser lum*/
    if ((charinfo[index] < '0') || (charinfo[index] > '9')) {
        printk("%s, turnon %c is error.\n", __func__, charinfo[index]);
        return -EFAULT;
    }
    lum = charinfo[index] - 48;
    index ++;
    if ((index < count) && ((charinfo[index] >= '0') && (charinfo[index] <= '9'))) {
        lum *= 10;
        lum += charinfo[index] - 48;
        index ++;
    }
    index ++;

    if ((FLASH_MODE == mode) && (1 == action) && (index < count)) {
        /*parser timeout*/
        if ((charinfo[index] >= '0') && (charinfo[index] <= '7')) {
            timeout = charinfo[index] - 48;
            cam_dbgfs_flash_timeout = timeout & 0x7;
            cam_dbgfs_flash_timeout_valid = 1;
        } else {
            printk("%s, turnon %c is error.\n", __func__, charinfo[index]);
        }
    }

    printk("%s, mode = %d, turn_on = %d, lum = %d, timeout = %d.\n",
        __func__, mode, action, lum, timeout);

    if (0 != action) {
        flashlight->turn_on(mode, lum);
    } else {
        flashlight->turn_off();
    }

    return count;
}

/*
 **************************************************************************
 * FunctionName: get_cam_dbgfs_flash_timeout;
 * Description : get flash timeout in flash mode
 * Input       :
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
u8 get_cam_dbgfs_flash_timeout(void)
{
    return cam_dbgfs_flash_timeout;
}

/*
 **************************************************************************
 * FunctionName: get_cam_dbgfs_flash_timeout_valid;
 * Description : is flash timeout valid?
 * Input       :
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
u8 get_cam_dbgfs_flash_timeout_valid(void)
{
    return cam_dbgfs_flash_timeout_valid;
}

void set_cam_dbgfs_flash_timeout_valid(u8 valid)
{
    cam_dbgfs_flash_timeout_valid = valid;
}

struct file_operations cam_dbgfs_flash_fops = {
    .open = flash_test_open,
    .read = flash_test_read,
    .write = flash_test_write,
};

int __init cam_dbgfs_init(void)
{
    cam_dbgfs_dir = debugfs_create_dir(CAM_DEBUGFS_DIR_NAME, NULL);
    if (ERR_PTR(-ENODEV) == cam_dbgfs_dir) {
        printk("debugfs_create_dir create dir %s failed!\n", CAM_DEBUGFS_DIR_NAME);
        return -EINVAL;
    }

    debugfs_create_u32(CAM_DEBUGFS_PWDN_FILE_NAME, 0664, cam_dbgfs_dir, &cam_dbgfs_pwdncfg);
    printk("%s, cam_dbgfs_pwdncfg = %d, \n", __func__, cam_dbgfs_pwdncfg);

    debugfs_create_file(CAM_DEBUGFS_FLASH_FILE_NAME, 0664, cam_dbgfs_dir, NULL, &cam_dbgfs_flash_fops);

    return 0;
}

void __exit cam_dbgfs_exit(void)
{
    printk("enter %s.\n", __func__);

    debugfs_remove_recursive(cam_dbgfs_dir);
    cam_dbgfs_dir = NULL;

    return;
}

late_initcall(cam_dbgfs_init);
module_exit(cam_dbgfs_exit);
#endif

/************************* END ******************************/
