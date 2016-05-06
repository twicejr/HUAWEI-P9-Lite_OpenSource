/* Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 and
* only version 2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
* GNU General Public License for more details.
*
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/miscdevice.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/unistd.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/io.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/of.h>
#include <linux/delay.h>
#include <linux/suspend.h>
#include <linux/reboot.h>
#include <linux/rtc.h>
#include <linux/time.h>
#include <linux/syscalls.h>

#include <linux/firmware.h>
#include <linux/errno.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#include <hi6402_algo_interface.h>
#include <hi6402_hifi_interface.h>

#include <linux/hisi/hi64xx/hi64xx_dsp_regs.h>
#include "hi64xx_hifi_debug.h"
#include "hi64xx_hifi_img_dl.h"

#include <linux/hisi/hi64xx/hi64xx_utils.h>
#include <linux/hisi/hi64xx_hifi_misc.h>
#include <dsm/dsm_pub.h>
#include "slimbus.h"

#include <linux/hisi/rdr_pub.h>

extern void rdr_codec_hifi_watchdog_process(void);

#define MAX_MSG_SIZE 128
#define MAX_PARA_SIZE 4096
#define RESULT_SIZE 4
#define MAX_OUT_PARA_SIZE ((RESULT_SIZE) + (MAX_PARA_SIZE))
#define MAX_USR_INPUT_SIZE (MAX_MSG_SIZE + MAX_PARA_SIZE)

#define HI64XX_EXCEPTION_RETRY 3
#define HI64XX_VERSION_CS      0x11
#define HI64XX_VERSION_ES      0x10
#define MAX_STR_LEN 64
#define HI64XX_IFOPEN_WAIT4DPCLK       1000    //wait 100ms.(1000 cycles * 100us every cycle)

#define SOC_GPIO_ADDR				   0xfff0e3fc
#define SOC_GPIO_DIR_ADDR			   0xfff0e400
#define HI64XX_HIFI_FPGA_OM_TEST_ADDR  0xE86120D4

#define HI64XXDEBUG_LEVEL_PROC_FILE   "hi64xxdebuglevel"
#define HI64XXDEBUG_PROC_FILE		  "hi64xxdebug"
#define HI64XXDEBUG_PATH			  "hi64xxdbg"

#define ROOT_UID     0
#define SYSTEM_GID   1000

/*XXX: change to 4 to enbale debug print*/
unsigned long hi64xx_dsp_debug_level = 3;

#ifdef ENABLE_HI6402_HIFI_DEBUG
static struct proc_dir_entry *hi64xx_debug_dir = NULL;
#endif

enum pll_state {
	PLL_PD,
	PLL_HIGH_FREQ,
	PLL_LOW_FREQ,
	PLL_RST,
};

struct reg_rw_struct {
	unsigned int	reg;
	unsigned int	val;
};

struct hi64xx_dsp_priv {
	struct hi64xx_irq *p_irq;
	struct hi64xx_resmgr *resmgr;
	struct snd_soc_codec *codec;
	struct notifier_block resmgr_nb;
	struct hi64xx_dsp_config dsp_config;
	struct mutex msg_mutex;
	struct mutex peri_mutex;

	unsigned int sync_msg_ret;
	wait_queue_head_t sync_msg_wq;

	unsigned int dsp_pllswitch_done;
	wait_queue_head_t dsp_pllswitch_wq;

	unsigned int dsp_pwron_done;
	wait_queue_head_t dsp_pwron_wq;

	/* we lock the two below to avoid a change after config */
	enum pll_state pll_state;
	bool dsp_is_running;
	struct mutex state_mutex;

	unsigned int low_freq_scene_status;
	unsigned int high_freq_scene_status;
	unsigned int uart_mode;

	bool is_watchdog_coming;
	bool is_sync_write_timeout;
};

static struct hi64xx_dsp_priv *dsp_priv = NULL;

static struct notifier_block hi64xx_sr_nb;
static struct notifier_block hi64xx_reboot_nb;
atomic_t volatile hi64xx_in_suspend = ATOMIC_INIT(0);
atomic_t volatile hi64xx_in_saving = ATOMIC_INIT(0);

extern struct dsm_client *dsm_audio_client;


void hi64xx_hifi_write_reg(unsigned int reg, unsigned int val)
{
	(void)snd_soc_write(dsp_priv->codec, reg, val);
}

unsigned int hi64xx_hifi_read_reg(unsigned int reg)
{
	return snd_soc_read(dsp_priv->codec, reg);
}

void hi64xx_hifi_reg_set_bit(unsigned int reg, unsigned int offset)
{

	(void)hi64xx_update_bits(dsp_priv->codec, reg, 1 << offset, 1 << offset);
}

void hi64xx_hifi_reg_clr_bit(unsigned int reg, unsigned int offset)
{
	(void)hi64xx_update_bits(dsp_priv->codec, reg, 1 << offset, 0);
}

void hi64xx_hifi_reg_write_bits(unsigned int reg,
				unsigned int value,
				unsigned int mask)
{
	(void)hi64xx_update_bits(dsp_priv->codec, reg, mask, value);
}

void hi64xx_memset(uint32_t dest, size_t n)
{
	int i = 0;
	for (i = 0; i < n; i = i + 4) {
		hi64xx_hifi_write_reg(dest, 0x0);
		dest += 4;
	}
}

void hi64xx_memcpy(uint32_t dest, uint32_t *src, size_t n)
{
	int i = 0;
	for (i = 0; i < n; i = i + 4) {
		hi64xx_hifi_write_reg(dest, *src);
		src++;
		dest += 4;
	}
}

void hi64xx_write(const unsigned int start_addr,
			 const unsigned int *buf,
			 const unsigned int len)
{
	int i = 0;

	BUG_ON(buf == NULL);
	BUG_ON(len == 0);

	for (i = 0; i < len; i += 4) {
		hi64xx_hifi_write_reg(start_addr + i, *buf++);
	}
}


static void hi64xx_read_per_4byte(const unsigned int start_addr,
			unsigned int *buf,
			const unsigned int len)
{
	int i = 0;

	BUG_ON(buf == NULL);
	BUG_ON(len == 0);

	for (i = 0; i < len; i += 4) {
		*buf++ = hi64xx_hifi_read_reg(start_addr + i);
	}
}

static void hi64xx_read_per_1byte(const unsigned int start_addr,
			      unsigned char *buf,
			      const unsigned int len)
{
	int i = 0;

	BUG_ON(buf == NULL);
	BUG_ON(len == 0);

	for (i = 0; i < len; i++) {
		*buf++ = hi64xx_hifi_read_reg(start_addr + i);
	}
}

static int hi64xx_chown(char *path, uid_t user, gid_t group)
{
	int ret = 0;
	mm_segment_t old_fs;

	if (NULL == path)
		return -1;

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	ret = (int)sys_chown((const char __user *)path, user, group);
	if (ret) {
		HI64XX_DSP_ERROR("chown %s uid [%d] gid [%d] failed error [%d]!\n", path, user, group, ret);
	}

	ret = (int)sys_chmod((const char __user *)path, 0770);
	if (ret) {
		HI64XX_DSP_ERROR("chmod %s 0770 failed error [%d]!\n", path, ret);
	}

	set_fs(old_fs);

	return ret;
}

void hi64xx_read(const unsigned int start_addr,
			unsigned char *arg,
			const unsigned int len)
{
	/* XXX:dont read a block from within 20007xxx to outside, vice versa */
	/* start_addr NOT in 0x20007000~0x20007xxx */
	if (start_addr < HI64XX_1BYTE_SUB_START
	    || start_addr > HI64XX_1BYTE_SUB_END) {
		if ((start_addr < HI64XX_1BYTE_SUB_START)
			&& (start_addr + len >= HI64XX_1BYTE_SUB_START)) {
			HI64XX_DSP_ERROR("range error: start:0x%x, len:0x%x\n",
				start_addr, len);
			return;
		}
		hi64xx_read_per_4byte(start_addr, (unsigned int *)arg, len);
	/* start_addr in 0x20007000~0x20007xxx */
	} else {
		if (start_addr + len > HI64XX_1BYTE_SUB_END) {
			HI64XX_DSP_ERROR("range error: start:0x%x, len:0x%x\n",
				start_addr, len);
			return;
		}
		hi64xx_read_per_1byte(start_addr, arg, len);
	}
}


static void hi64xx_hifi_set_pll(bool enable)
{
	/* set pll */
	if (enable)
		hi64xx_resmgr_request_pll(dsp_priv->resmgr, PLL_HIGH);
	else
		hi64xx_resmgr_release_pll(dsp_priv->resmgr, PLL_HIGH);
}

static void hi64xx_hifi_set_low_pll(bool enable)
{
	/* set mad_pll */
	if (enable)
		hi64xx_resmgr_request_pll(dsp_priv->resmgr, PLL_LOW);
	else
		hi64xx_resmgr_release_pll(dsp_priv->resmgr, PLL_LOW);
}

/* HI64xx_DSP_CMD_STATUS :
 * bit 0 sync_msg
 * bit 1 dsp_pllswitch
 * bit 2 dsp_pwron
 */
static irqreturn_t hi64xx_msg_irq_handler(int irq, void *data)
{
	IN_FUNCTION;

	if(!hi64xx_hifi_read_reg(HI64xx_DSP_CMD_STATUS_VLD)){
		HI64XX_DSP_ERROR("CMD invalid\n");
		return IRQ_HANDLED;
	}
	/*
	 * todo : 2.use else if ? cmd should not come together ?
	 * todo : 3.freq high -> freq low and stop mad cmd maybe come together
	 *			(eg.headset play and mad on,then stop play and stop mad)
	 */

	HI64XX_DSP_INFO("cmd status:%d\n", hi64xx_hifi_read_reg(HI64xx_DSP_CMD_STATUS));

	if(hi64xx_hifi_read_reg(HI64xx_DSP_CMD_STATUS) & (0x1 << 0)){

		HI64XX_DSP_INFO("6402 hifi msg cnf\n");
		hi64xx_hifi_reg_clr_bit(HI64xx_DSP_SUB_CMD_STATUS, 0);
		dsp_priv->sync_msg_ret = 1;
		wake_up_interruptible_all(&dsp_priv->sync_msg_wq);
	}
	if(hi64xx_hifi_read_reg(HI64xx_DSP_CMD_STATUS) & (0x1 << 1)){

		HI64XX_DSP_INFO("6402 hifi pll switch done cnf\n");
		hi64xx_hifi_reg_clr_bit(HI64xx_DSP_SUB_CMD_STATUS, 1);
		dsp_priv->dsp_pllswitch_done= 1;
		wake_up_interruptible_all(&dsp_priv->dsp_pllswitch_wq);
	}
	if(hi64xx_hifi_read_reg(HI64xx_DSP_CMD_STATUS) & (0x1 << 2)){

		HI64XX_DSP_INFO("6402 hifi pwron done cnf\n");
		hi64xx_hifi_reg_clr_bit(HI64xx_DSP_SUB_CMD_STATUS, 2);
		dsp_priv->dsp_pwron_done = HIFI_STATE_INIT;
		wake_up_interruptible_all(&dsp_priv->dsp_pwron_wq);
	}

	OUT_FUNCTION;

	return IRQ_HANDLED;
}

static int hi64xx_write_mlib_para(const unsigned char *arg,
				  const unsigned int len)
{
	if (len > MAX_PARA_SIZE) {
		HI64XX_DSP_ERROR("msg length:%u exceed limit!\n", len);
		return ERROR;
	}

	if ((len & 0x3) != 0) {
		HI64XX_DSP_ERROR("msg length:%u is not 4 byte aligned\n", len);
		return ERROR;
	}

	hi64xx_write(dsp_priv->dsp_config.para_addr, arg, len);

	return OK;
}

static int hi64xx_read_mlib_para(unsigned char *arg, const unsigned int len)
{
	BUG_ON(arg == NULL);
	BUG_ON(len == 0);

	if (len > MAX_PARA_SIZE) {
		HI64XX_DSP_ERROR("msg length:%u exceed limit!\n", len);
		return ERROR;
	}

	if ((len & 0x3) != 0) {
		HI64XX_DSP_ERROR("msg length:%u is not 4 byte aligned\n", len);
		return ERROR;
	}

	hi64xx_read(dsp_priv->dsp_config.para_addr, arg, len);

	return OK;
}

unsigned int hi64xx_read_mlib_test_para(unsigned char *arg, unsigned int len)
{
	unsigned int addr = 0;
	unsigned int count;
	unsigned int value;
	IN_FUNCTION;

	addr = HI64xx_MLIB_TO_AP_MSG_ADDR;

	if (hi64xx_hifi_read_reg(addr) != UCOM_PROTECT_WORD) {
		HI64XX_DSP_ERROR("mlib test cannot find parameters!\n");
		return -1;
	}

	for (count = 1; count < (HI64xx_MLIB_TO_AP_MSG_LEN / sizeof(unsigned int)); count++) {
		value = hi64xx_hifi_read_reg(addr + count * sizeof(unsigned int));
		if(count * sizeof(unsigned int) >= len) {
			HI64XX_DSP_ERROR("input not enough space!\n");
			return 0;
		}

		if(value == UCOM_PROTECT_WORD && count > 0) {
			break;
		}

		memcpy(arg + (count - 1) * sizeof(unsigned int), &value, sizeof(value));
		HI64XX_DSP_INFO("mlib test para[0x%x]\n", value);
	}

	OUT_FUNCTION;
	return (count - 1) * sizeof(unsigned int);
}

static int hi64xx_write_msg(const unsigned char *arg, const unsigned int len)
{
	int ret = OK;

	IN_FUNCTION;

	if (len > MAX_MSG_SIZE) {
		HI64XX_DSP_ERROR("msg length exceed limit!\n");
		return ERROR;
	}

	if ((len & 0x3) != 0) {
		HI64XX_DSP_ERROR("msg length:%u is not 4 byte aligned\n", len);
		return ERROR;
	}

	hi64xx_write(dsp_priv->dsp_config.msg_addr, arg, len);

	dsp_priv->sync_msg_ret = 0;

	hi64xx_hifi_write_reg(dsp_priv->dsp_config.cmd1_addr, dsp_priv->pll_state);

	if(dsp_priv->dsp_config.dsp_ops.notify_dsp)
		dsp_priv->dsp_config.dsp_ops.notify_dsp();

	OUT_FUNCTION;

	return ret;
}

static int hi64xx_get_input_param(unsigned int usr_para_size,
				  void __user *usr_para_addr,
				  unsigned int *krn_para_size,
				  void **krn_para_addr)
{
	void *para_in = NULL;
	unsigned int para_size_in = 0;

	IN_FUNCTION;

	if (NULL == usr_para_addr) {
		HI64XX_DSP_ERROR("usr_para_addr is null no user data\n");
		goto ERR;
	}

	if ((0 == usr_para_size) || (usr_para_size > MAX_USR_INPUT_SIZE)) {
		HI64XX_DSP_ERROR("usr buffer size:%u out of range\n", usr_para_size);
		goto ERR;
	}

	para_size_in = roundup(usr_para_size, 4);

	para_in = kzalloc(para_size_in, GFP_KERNEL);
	if (para_in == NULL) {
		HI64XX_DSP_ERROR("kzalloc fail\n");
		goto ERR;
	}

	if (copy_from_user(para_in, usr_para_addr, usr_para_size)) {
		HI64XX_DSP_ERROR("copy_from_user fail\n");
		goto ERR;
	}

	*krn_para_size = para_size_in;
	*krn_para_addr = para_in;

	OUT_FUNCTION;

	return OK;

ERR:
	if (para_in != NULL) {
		kfree(para_in);
		para_in = NULL;
	}

	OUT_FUNCTION;

	return ERROR;
}

static void hi64xx_param_free(void **krn_para_addr)
{
	IN_FUNCTION;

	if (*krn_para_addr != NULL) {
		kfree(*krn_para_addr);
		*krn_para_addr = NULL;
	} else {
		HI64XX_DSP_ERROR("krn_para_addr to free is NULL\n");
	}

	OUT_FUNCTION;

	return;
}

static int hi64xx_alloc_output_param_buffer(unsigned int usr_para_size,
					    void __user *usr_para_addr,
						unsigned int *krn_para_size,
						void **krn_para_addr)
{
	BUG_ON(*krn_para_addr != NULL);

	HI64XX_DSP_DEBUG("malloc size: %u\n", usr_para_size);
	if (usr_para_size == 0 || usr_para_size > MAX_OUT_PARA_SIZE) {
		HI64XX_DSP_ERROR("usr space size invalid\n");
		return ERROR;
	}

	if (usr_para_addr == NULL) {
		HI64XX_DSP_ERROR("usr_para_addr is NULL\n");
		return ERROR;
	}

	*krn_para_addr = kzalloc(usr_para_size, GFP_KERNEL);
	if (*krn_para_addr == NULL) {
		HI64XX_DSP_ERROR("kzalloc fail\n");
		return ERROR;
	}

	*krn_para_size = usr_para_size;

	return OK;
}

static int hi64xx_put_output_param(unsigned int usr_para_size,
				   void __user *usr_para_addr,
				   unsigned int krn_para_size,
				   void *krn_para_addr)
{
	int ret = OK;

	BUG_ON(usr_para_size == 0);
	BUG_ON(usr_para_addr == NULL);
	BUG_ON(krn_para_size == 0);
	BUG_ON(krn_para_addr == NULL);

	IN_FUNCTION;

	if (krn_para_size != usr_para_size) {
		HI64XX_DSP_ERROR("krn para size:%d != usr para size%d\n",
				 krn_para_size, usr_para_size);
		return ERROR;
	}

	HI64XX_DSP_DEBUG("user_para_size:%d\n", usr_para_size);
	ret = copy_to_user(usr_para_addr, krn_para_addr, usr_para_size);
	if (ret != OK) {
		HI64XX_DSP_ERROR("copy_to_user fail, ret is %d\n", ret);
		return ERROR;
	}

	OUT_FUNCTION;

	return OK;
}

static bool hi64xx_error_detect(void)
{
	unsigned int version = hi64xx_hifi_read_reg(HI64xx_VERSION);

	if (HI64XX_VERSION_CS != version
		&& HI64XX_VERSION_ES != version) {
		HI64XX_DSP_ERROR("Codec err,ver 0x%x,pll 0x%x\n",
			version, hi64xx_hifi_read_reg(HI64xx_CODEC_ANA_PLL));

		if (!dsm_client_ocuppy(dsm_audio_client)) {
			dsm_client_record(dsm_audio_client, "DSM_HI6402_CRASH\n");
			dsm_client_notify(dsm_audio_client, DSM_CODEC_HIFI_RESET);
		}

		return true;
	}

	return false;
}

static int hi64xx_sync_write(const unsigned char *arg, const unsigned int len)
{
	int ret = OK;
	int count = HI64XX_EXCEPTION_RETRY;
	IN_FUNCTION;

	dsp_priv->sync_msg_ret = 0;

	/* can't get codec version,reset system */
	BUG_ON(hi64xx_error_detect());

	while (count) {
		ret = hi64xx_write_msg(arg, len);
		if (OK != ret) {
			HI64XX_DSP_ERROR("send msg failed\n");
			goto out;
		}

		if (wait_event_interruptible_timeout(dsp_priv->sync_msg_wq,
			(dsp_priv->sync_msg_ret == 1), HZ) != 0) {
			goto out;
		}

		if (dsp_priv->is_watchdog_coming) {
			HI64XX_DSP_INFO("no need to retry because watchdog've already come\n");
			ret = BUSY;
			goto out;
		}

		count--;
		HI64XX_DSP_ERROR("cmd timeout retry %d\n",
			HI64XX_EXCEPTION_RETRY - count);
	}

	if (0 == count) {
		hi64xx_dump_debug_info();

		/* can't get codec version,reset system */
		BUG_ON(hi64xx_error_detect());

		HI64XX_DSP_ERROR("cmd timeout\n");
		if (!(dsp_priv->is_watchdog_coming) && !(dsp_priv->is_sync_write_timeout)) {
			HI64XX_DSP_ERROR("save log and reset media \n");
			dsp_priv->is_sync_write_timeout = true;
#if !defined(PLATFORM_HI3660)
			rdr_codec_hifi_watchdog_process();
#endif
		}
		ret = BUSY;
	}

out:
	OUT_FUNCTION;

	return ret;
}

static void hi64xx_hifi_pause(void)
{
	IN_FUNCTION;

	if(dsp_priv->dsp_config.dsp_ops.wtd_enable)
		dsp_priv->dsp_config.dsp_ops.wtd_enable(false);

	if (dsp_priv->dsp_config.dsp_ops.clk_enable)
		dsp_priv->dsp_config.dsp_ops.clk_enable(false);

	OUT_FUNCTION;
}

static void hi64xx_hifi_resume(enum pll_state state)
{
	IN_FUNCTION;

	if (dsp_priv->dsp_config.dsp_ops.clk_enable)
		dsp_priv->dsp_config.dsp_ops.clk_enable(true);

	if(dsp_priv->dsp_config.dsp_ops.wtd_enable)
		dsp_priv->dsp_config.dsp_ops.wtd_enable(true);

	OUT_FUNCTION;
	return;
}

static bool hi64xx_hifi_notify_dsp_pllswitch(unsigned char state)
{

	/* notify dsp stop dma and close dspif */
	dsp_priv->dsp_pllswitch_done = 0;
	hi64xx_hifi_write_reg(dsp_priv->dsp_config.cmd0_addr, state);

	HI64XX_DSP_INFO("cmd[0x%x]reg[0x%x]\n",state,
			hi64xx_hifi_read_reg(dsp_priv->dsp_config.cmd0_addr));

	if(dsp_priv->dsp_config.dsp_ops.notify_dsp)
		dsp_priv->dsp_config.dsp_ops.notify_dsp();

	/* wait 100s(600ms in total) for dsp close dma and dsspif */
	if (wait_event_interruptible_timeout(dsp_priv->dsp_pllswitch_wq,
					   (dsp_priv->dsp_pllswitch_done == 1), HZ) == 0) {
		HI64XX_DSP_ERROR("wait for dsp_pllswitch_done timeout\n");
	}
	return true;
}

static void hi64xx_hifi_cfg_before_pll_switch(void)
{
	IN_FUNCTION;

	mutex_lock(&dsp_priv->state_mutex);
	if (dsp_priv->dsp_is_running) {
		/* todo : put below code in hi64xx_hifi_pause() */
		HI64XX_DSP_INFO("notify dsp close dma\n");

		hi64xx_hifi_notify_dsp_pllswitch(HIFI_POWER_CLK_OFF);
		hi64xx_hifi_pause();
	}

	mutex_unlock(&dsp_priv->state_mutex);

	OUT_FUNCTION;

	return;
}

bool hi64xx_hifi_is_running(void)
{
	return dsp_priv->dsp_is_running;
}

static const char *state_name[] = {
	"PLL_DOWN",
	"PLL_HIGH_FREQ",
	"PLL_LOW_FREQ",
};

static void hi64xx_hifi_cfg_after_pll_switch(enum pll_state state)
{
	int value = 0;

	IN_FUNCTION;

	mutex_lock(&dsp_priv->state_mutex);

	value = hi64xx_hifi_read_reg(0x20007000);
	HI64XX_DSP_INFO("%s->%s, dsp_is_runing:%d, version:%#x, \n",
		state_name[dsp_priv->pll_state], state_name[state], dsp_priv->dsp_is_running, value);

	dsp_priv->pll_state = state;

	hi64xx_hifi_write_reg(dsp_priv->dsp_config.cmd1_addr, dsp_priv->pll_state);

	if (dsp_priv->dsp_is_running) {
		hi64xx_hifi_resume(dsp_priv->pll_state);
		/* todo : put below code in hi64xx_hifi_resume() */

		hi64xx_hifi_notify_dsp_pllswitch(HIFI_POWER_CLK_ON);
	}
	mutex_unlock(&dsp_priv->state_mutex);

	OUT_FUNCTION;
	return;
}

/* dsp_if bypass config bit 6,7 */
static unsigned int hi6402_sc_src_lr_ctrls_m[] = {
	HI64xx_SC_S1_SRC_LR_CTRL_M,
	HI64xx_SC_S2_SRC_LR_CTRL_M,
	HI64xx_SC_S3_SRC_LR_CTRL_M,
	HI64xx_SC_S4_SRC_LR_CTRL_M,
	HI64xx_SC_MISC_SRC_CTRL_H,
};

/* dsp_if io sample rate config */
static unsigned int hi6402_sc_fs_ctrls_h[] = {
	HI64xx_SC_FS_S1_CTRL_H,
	HI64xx_SC_FS_S2_CTRL_H,
	HI64xx_SC_FS_S3_CTRL_H,
	HI64xx_SC_FS_S4_CTRL_H,
	HI64xx_SC_FS_MISC_CTRL,
};

/* check for parameters used by misc, only for if_open/if_close */
static int hi64xx_dsp_if_para_check(const struct krn_param_io_buf *param)
{
	unsigned int i = 0;
	unsigned int message_size = 0;
	DSP_IF_OPEN_REQ_STRU *dsp_if_open_req = NULL;
	PCM_PROCESS_DMA_MSG_STRU *dma_msg_stru = NULL;

	BUG_ON(param == NULL);
	BUG_ON(param->buf_in == NULL);
	BUG_ON(param->buf_size_in == 0);

	if (param->buf_size_in < sizeof(DSP_IF_OPEN_REQ_STRU)) {
		HI64XX_DSP_ERROR("input size:%u invalid\n", param->buf_size_in);
		return ERROR;
	}

	dsp_if_open_req = (DSP_IF_OPEN_REQ_STRU *)(param->buf_in);
	dma_msg_stru = &dsp_if_open_req->stProcessDMA;

	if (dma_msg_stru->uwIFCount >= HI6402_HIFI_DSP_IF_PORT_BUTT) {
		HI64XX_DSP_ERROR("try to open too many ifs\n");
		return ERROR;
	}

	message_size = sizeof(PCM_IF_MSG_STRU) * (dma_msg_stru->uwIFCount)
			+ sizeof(DSP_IF_OPEN_REQ_STRU);
	if (param->buf_size_in < message_size) {
		HI64XX_DSP_ERROR("input size:%u invalid\n", param->buf_size_in);
		return ERROR;
	}

	for (i = 0; i < dma_msg_stru->uwIFCount; i++) {
		PCM_IF_MSG_STRU *pcm_if_msg = &dma_msg_stru->stIFCfgList[i];

		if (pcm_if_msg->uwIFId >= HI6402_HIFI_DSP_IF_PORT_BUTT) {
			HI64XX_DSP_ERROR("dsp if ID %d is out of range\n",
					pcm_if_msg->uwIFId);
			return ERROR;
		}

		switch (pcm_if_msg->uwSampleRateIn) {
		case 0:
			HI64XX_DSP_INFO("DATA_HOOK_PROCESS, sample_rate=0\n");
			break;
		case 8000:
		case 16000:
		case 32000:
		case 48000:
		case 96000:
		case 192000:
			break;
		default:
			HI64XX_DSP_ERROR("unsupport sample_rate %d \n",
					pcm_if_msg->uwSampleRateIn);
			return ERROR;
		}
	}

	return OK;
}

static int hi64xx_dsp_if_set_sample_rate(unsigned int dsp_if_id,
						unsigned int sample_rate)
{
	unsigned int addr = 0;
	unsigned char mask = 0;
	unsigned char sample_rate_index = 0;

	unsigned int i2s_id = dsp_if_id / 2;
	unsigned int direct =
		(dsp_if_id & 0x1) ? HI6402_HIFI_PCM_OUT : HI6402_HIFI_PCM_IN;

	IN_FUNCTION;

	BUG_ON(i2s_id >= ARRAY_SIZE(hi6402_sc_fs_ctrls_h));

	switch (sample_rate) {

	case 0:
		HI64XX_DSP_INFO("DATA_HOOK_PROCESS, sample_rate=0\n");
		break;
	case 8000:
		sample_rate_index = HI6402_HIFI_PCM_SAMPLE_RATE_8K;
		break;
	case 16000:
		sample_rate_index = HI6402_HIFI_PCM_SAMPLE_RATE_16K;
		break;
	case 32000:
		sample_rate_index = HI6402_HIFI_PCM_SAMPLE_RATE_32K;
		break;
	case 48000:
		sample_rate_index = HI6402_HIFI_PCM_SAMPLE_RATE_48K;
		break;
	case 96000:
		sample_rate_index = HI6402_HIFI_PCM_SAMPLE_RATE_96K;
		break;
	case 192000:
		sample_rate_index = HI6402_HIFI_PCM_SAMPLE_RATE_192K;
		break;
	default:
		/* shouldn't be here */
		HI64XX_DSP_ERROR("unsupport sample_rate %d!! \n", sample_rate);
	}

	addr = hi6402_sc_fs_ctrls_h[i2s_id];
	mask = (direct == HI6402_HIFI_PCM_IN) ? 0xf : 0xf0;
	sample_rate_index = (direct == HI6402_HIFI_PCM_IN)
		                ? sample_rate_index : sample_rate_index << 4;
	/* Todo: dac dspif sample rate maybe different */
	if(dsp_if_id == HI6402_HIFI_DSP_IF_PORT_8){
		mask = 0x7c;
		sample_rate_index = sample_rate_index << 4;
	}
	hi64xx_hifi_reg_write_bits(addr, sample_rate_index, mask);

	OUT_FUNCTION;

	return 0;
}

static void hi64xx_dsp_if_set_bypass(unsigned int dsp_if_id, bool enable)
{
	unsigned int addr = 0;
	unsigned int bit = 0;

	unsigned int i2s_id = dsp_if_id / 2;
	unsigned int direct =
		(dsp_if_id & 0x1) ? HI6402_HIFI_PCM_OUT : HI6402_HIFI_PCM_IN;

	IN_FUNCTION;

	BUG_ON(i2s_id >= ARRAY_SIZE(hi6402_sc_src_lr_ctrls_m));

	bit = (direct == HI6402_HIFI_PCM_IN) ? 6 : 7;
	if(dsp_if_id == HI6402_HIFI_DSP_IF_PORT_8)
		bit = 4;
	addr = hi6402_sc_src_lr_ctrls_m[i2s_id];

	if (enable) {
		hi64xx_hifi_reg_set_bit(addr, bit);
	} else {
		hi64xx_hifi_reg_clr_bit(addr, bit);
	}

	OUT_FUNCTION;
}

/* now we'v alread check the para, so don't do it again */
static void hi64xx_dsp_if_sample_rate_set(const char *arg)
{
	unsigned int i = 0;

	DSP_IF_OPEN_REQ_STRU *dsp_if_open_req = (DSP_IF_OPEN_REQ_STRU *)arg;
	PCM_PROCESS_DMA_MSG_STRU *dma_msg_stru = &dsp_if_open_req->stProcessDMA;

	IN_FUNCTION;

	for (i = 0; i < dma_msg_stru->uwIFCount; i++) {
		PCM_IF_MSG_STRU *pcm_if_msg = &dma_msg_stru->stIFCfgList[i];

		hi64xx_dsp_if_set_sample_rate(pcm_if_msg->uwIFId,
				pcm_if_msg->uwSampleRateIn);
	}

	OUT_FUNCTION;
}

void hi64xx_hifi_misc_peri_lock(void)
{
	if (dsp_priv != NULL)
		mutex_lock(&dsp_priv->peri_mutex);
}

void hi64xx_hifi_misc_peri_unlock(void)
{
	if (dsp_priv != NULL)
		mutex_unlock(&dsp_priv->peri_mutex);
}

static void hi64xx_dsp_run(void)
{
	IN_FUNCTION;

	mutex_lock(&dsp_priv->state_mutex);
	hi64xx_hifi_misc_peri_lock();

	if (!dsp_priv->dsp_is_running) {

		if (dsp_priv->dsp_config.dsp_ops.ram2axi)
			dsp_priv->dsp_config.dsp_ops.ram2axi(true);

		if (dsp_priv->dsp_config.dsp_ops.clk_enable)
			dsp_priv->dsp_config.dsp_ops.clk_enable(true);

		if(dsp_priv->dsp_config.dsp_ops.wtd_enable)
			dsp_priv->dsp_config.dsp_ops.wtd_enable(true);

		dsp_priv->dsp_is_running = true;
	}

	hi64xx_hifi_misc_peri_unlock();
	mutex_unlock(&dsp_priv->state_mutex);

	OUT_FUNCTION;
}

static void hi64xx_dsp_stop(void)
{
	IN_FUNCTION;

	mutex_lock(&dsp_priv->state_mutex);

	if (dsp_priv->dsp_is_running) {
		if(dsp_priv->dsp_config.dsp_ops.wtd_enable)
			dsp_priv->dsp_config.dsp_ops.wtd_enable(false);

		if (dsp_priv->dsp_config.dsp_ops.clk_enable)
			dsp_priv->dsp_config.dsp_ops.clk_enable(false);

		if (dsp_priv->dsp_config.dsp_ops.ram2axi)
			dsp_priv->dsp_config.dsp_ops.ram2axi(false);

		dsp_priv->dsp_is_running = false;
	}

	mutex_unlock(&dsp_priv->state_mutex);

	OUT_FUNCTION;
}

static int hi64xx_request_pll_resource(unsigned int scene_id)
{
	IN_FUNCTION;

	HI64XX_DSP_INFO("sid[0x%x]hifreq_status[0x%x]", scene_id,
		dsp_priv->high_freq_scene_status);

	if (scene_id >= HI_FREQ_SCENE_BUTT) {
		HI64XX_DSP_ERROR("unknow scene for pll: %u\n", scene_id);
		return ERROR;
	}

	if ((dsp_priv->high_freq_scene_status & (1 << scene_id)) != 0) {
		HI64XX_DSP_WARNING("scene: %u is alread started.\n", scene_id);
		return REDUNDANT;
	}

	if (dsp_priv->high_freq_scene_status == 0) {
		hi64xx_hifi_set_pll(true);
		hi64xx_dsp_run();
	}

	dsp_priv->high_freq_scene_status |= (1 << scene_id);

	OUT_FUNCTION;

	return OK;
}

static int hi64xx_release_pll_resource(unsigned int scene_id)
{
	IN_FUNCTION;

	if (scene_id >= HI_FREQ_SCENE_BUTT) {
		HI64XX_DSP_ERROR("unknow scene for pll: %u\n", scene_id);
		return ERROR;
	}

	if ((dsp_priv->high_freq_scene_status & (1 << scene_id)) == 0) {
		HI64XX_DSP_WARNING("scene: %u is NOT started\n", scene_id);
		return REDUNDANT;
	}

	dsp_priv->high_freq_scene_status &= ~(1 << scene_id);

	if (dsp_priv->high_freq_scene_status == 0) {
		if (dsp_priv->low_freq_scene_status == 0) {
			hi64xx_dsp_stop();
		}
		hi64xx_hifi_set_pll(false);
	}

	OUT_FUNCTION;

	return OK;
}

static int hi64xx_request_low_pll_resource(unsigned int scene_id)
{
	IN_FUNCTION;

	if (scene_id >= LOW_FREQ_SCENE_BUTT) {
		HI64XX_DSP_ERROR("unknow scene for mad pll: %u\n", scene_id);
		return ERROR;
	}

	if ((dsp_priv->low_freq_scene_status & (1 << scene_id)) != 0) {
		HI64XX_DSP_WARNING("scene: %u is alread started.\n", scene_id);
		return REDUNDANT;
	}

	if (dsp_priv->low_freq_scene_status == 0) {
		hi64xx_hifi_set_low_pll(true);
		hi64xx_dsp_run();
	}

	dsp_priv->low_freq_scene_status |= (1 << scene_id);
	HI64XX_DSP_INFO("low scene: 0x%x\n", dsp_priv->low_freq_scene_status);

	OUT_FUNCTION;

	return OK;
}

static int hi64xx_release_low_pll_resource(unsigned int scene_id)
{
	IN_FUNCTION;

	if (scene_id >= LOW_FREQ_SCENE_BUTT) {
		HI64XX_DSP_ERROR("unknow scene for low pll: %u\n", scene_id);
		return ERROR;
	}

	if ((dsp_priv->low_freq_scene_status & (1 << scene_id)) == 0) {
		HI64XX_DSP_WARNING("scene: %u is NOT started\n", scene_id);
		return REDUNDANT;
	}

	dsp_priv->low_freq_scene_status &= ~(1 << scene_id);

	if (dsp_priv->low_freq_scene_status == 0) {
		if (dsp_priv->high_freq_scene_status == 0) {
			hi64xx_dsp_stop();
		}
		hi64xx_hifi_set_low_pll(false);
	}

	OUT_FUNCTION;

	return OK;
}

void hi64xx_hifi_pwr_off(void)
{
	hi64xx_dsp_stop();
	if (dsp_priv->dsp_config.dsp_ops.runstall)
		dsp_priv->dsp_config.dsp_ops.runstall(false);
}

static int check_dp_clk(void)
{
	/* waiting 100ms at most before send if_open cmd, when dpclk is disable */
	unsigned int uwCnt = HI64XX_IFOPEN_WAIT4DPCLK;
	while(--uwCnt) {
		if(1 == hi64xx_hifi_read_reg(HI64xx_CODEC_DP_CLK_EN)) {
			HI64XX_DSP_INFO("DP clk is enable, goto send if_open\n");
			return OK;
		} else {
			/* wait 100 to 110us every cycle, if dpclk is disable. */
			usleep_range(100, 110);
		}
	}

	return ERROR;
}

/*
 * cmd_process_functions
 * */
static int hi64xx_func_if_open(struct krn_param_io_buf *param)
{
	int ret = 0;

	DSP_IF_OPEN_REQ_STRU *dsp_if_open_req = NULL;
	PCM_PROCESS_DMA_MSG_STRU *dma_msg_stru = NULL;

	IN_FUNCTION;

	ret = hi64xx_dsp_if_para_check(param);
	if (ret != OK) {
		HI64XX_DSP_ERROR("dsp if parameter invalid\n");
		goto end;
	}

	dsp_if_open_req = (DSP_IF_OPEN_REQ_STRU *)(param->buf_in);
	dma_msg_stru = &dsp_if_open_req->stProcessDMA;

	switch (dma_msg_stru->uwProcessId) {
// current not support HOOK
#if 0
	case MLIB_PATH_DATA_HOOK:
		ret = hi64xx_request_pll_resource(HI_FREQ_SCENE_HOOK);
		if (ret != OK) {
			goto end;
		}
		break;
#endif
	case MLIB_PATH_WAKEUP:
		ret = hi64xx_request_low_pll_resource(LOW_FREQ_SCENE_WAKE_UP);
		if (ret != OK) {
			goto end;
		}
		break;
	case MLIB_PATH_SMARTPA:
		ret = check_dp_clk();
		if (ret != OK) {
			HI64XX_DSP_ERROR("DP clk is disable, it's dangerous to send if_open\n");
			if (!dsm_client_ocuppy(dsm_audio_client)) {
				dsm_client_record(dsm_audio_client, "DSM_CODEC_HIFI_IF_OPEN_WITHOUT_DPCLK\n");
				dsm_client_notify(dsm_audio_client, DSM_CODEC_HIFI_IF_OPEN_ERR);
			}
			goto end;
		}
		ret = hi64xx_request_pll_resource(HI_FREQ_SCENE_PA);
		if (ret != OK) {
			goto end;
		}
		break;
	default:
		HI64XX_DSP_ERROR("ProcessId:%u unsupport\n", dma_msg_stru->uwProcessId);
		ret = ERROR;
		goto end;
	}

	hi64xx_dsp_if_sample_rate_set(param->buf_in);
	hi64xx_hifi_write_reg(dsp_priv->dsp_config.cmd1_addr, dsp_priv->pll_state);
	ret = hi64xx_sync_write(param->buf_in, param->buf_size_in);
	if (ret != OK) {
		goto end;
	}

end:
	OUT_FUNCTION;
	return ret;
}

static int hi64xx_func_if_close(struct krn_param_io_buf *param)
{
	int ret = 0;
	DSP_IF_OPEN_REQ_STRU *dsp_if_open_req = NULL;
	PCM_PROCESS_DMA_MSG_STRU *dma_msg_stru = NULL;

	IN_FUNCTION;

	ret = hi64xx_dsp_if_para_check(param);
	if (ret != OK) {
		HI64XX_DSP_ERROR("dsp if parameter invalid\n");
		goto end;
	}

	dsp_if_open_req = (DSP_IF_OPEN_REQ_STRU *)(param->buf_in);
	dma_msg_stru = &dsp_if_open_req->stProcessDMA;

	if (dma_msg_stru->uwProcessId == MLIB_PATH_WAKEUP) {
		if ((dsp_priv->low_freq_scene_status & (1 << LOW_FREQ_SCENE_WAKE_UP)) == 0) {
			HI64XX_DSP_WARNING("scene wakeup is NOT opened.\n");
			ret = REDUNDANT;
			goto end;
		}
// current not support HOOK
#if 0
	} else if (dma_msg_stru->uwProcessId == MLIB_PATH_DATA_HOOK) {
		if ((dsp_priv->high_freq_scene_status & (1 << HI_FREQ_SCENE_HOOK)) == 0) {
			HI64XX_DSP_WARNING("scene datahook is NOT opened.\n");
			ret = REDUNDANT;
			goto end;
		}
#endif
	} else if (dma_msg_stru->uwProcessId == MLIB_PATH_SMARTPA) {
		if ((dsp_priv->high_freq_scene_status & (1 << HI_FREQ_SCENE_PA)) == 0) {
			HI64XX_DSP_WARNING("scene smartpa is NOT opened.\n");
			ret = REDUNDANT;
			goto end;
		}
	} else {
		HI64XX_DSP_ERROR("ProcessId:%u unsupport\n", dma_msg_stru->uwProcessId);
		ret = ERROR;
		goto end;
	}

	hi64xx_hifi_write_reg(dsp_priv->dsp_config.cmd1_addr, dsp_priv->pll_state);
	ret = hi64xx_sync_write(param->buf_in, param->buf_size_in);
	if (ret != OK) {
		HI64XX_DSP_ERROR("sync_write ret=%d\n", ret);
		goto end;
	}

	if (dma_msg_stru->uwProcessId == MLIB_PATH_WAKEUP) {
		hi64xx_release_low_pll_resource(LOW_FREQ_SCENE_WAKE_UP);
// current not support HOOK
#if 0
	} else if (dma_msg_stru->uwProcessId == MLIB_PATH_DATA_HOOK) {
		hi64xx_release_pll_resource(HI_FREQ_SCENE_HOOK);
#endif
	} else if (dma_msg_stru->uwProcessId == MLIB_PATH_SMARTPA) {
		hi64xx_release_pll_resource(HI_FREQ_SCENE_PA);
	}
end:
	OUT_FUNCTION;

	return ret;
}

static int hi64xx_func_fastmode(struct krn_param_io_buf *param)
{
	int ret = OK;

	IN_FUNCTION;

	hi64xx_request_low_pll_resource(LOW_FREQ_SCENE_FAST_TRANS_SET);

	ret = hi64xx_sync_write(param->buf_in, param->buf_size_in);

	hi64xx_release_low_pll_resource(LOW_FREQ_SCENE_FAST_TRANS_SET);

	return ret;
}

static int hi64xx_func_para_set(struct krn_param_io_buf *param)
{
	int ret = OK;
	MLIB_PARA_SET_REQ_STRU *mlib_para = NULL;
	struct MlibParameterST *mlib_para_content = NULL;

	IN_FUNCTION;

	BUG_ON(param == NULL);
	BUG_ON(param->buf_in == NULL);
	BUG_ON(param->buf_size_in == 0);

	if (param->buf_size_in < sizeof(MLIB_PARA_SET_REQ_STRU)) {
		HI64XX_DSP_ERROR("input size:%u invalid\n", param->buf_size_in);
		return ERROR;
	}

	mlib_para = (MLIB_PARA_SET_REQ_STRU *)param->buf_in;

	mlib_para_content= (struct MlibParameterST *)mlib_para->aucData;

	if (0 == mlib_para->uwSize
		|| mlib_para->uwSize > (param->buf_size_in - sizeof(MLIB_PARA_SET_REQ_STRU))) {
		HI64XX_DSP_ERROR("mlib_para size is out of range.\n");
		return ERROR;
	}

	if (MLIB_ST_PARA_TRANSACTION == mlib_para_content->key) {
		hi64xx_request_low_pll_resource(LOW_FREQ_SCENE_SET_PARA);
	} else {
		hi64xx_request_pll_resource(HI_FREQ_SCENE_SET_PARA);
	}
	ret = hi64xx_write_mlib_para(mlib_para->aucData, mlib_para->uwSize);

	if (ret != OK) {
		HI64XX_DSP_ERROR("write mlib para failed\n");
		goto end;
	}

	ret = hi64xx_sync_write(param->buf_in, sizeof(MLIB_PARA_SET_REQ_STRU));
	if (ret != OK) {
		HI64XX_DSP_ERROR("sync write failed\n");
		goto end;
	}

end:
	if (MLIB_ST_PARA_TRANSACTION == mlib_para_content->key) {
		hi64xx_release_low_pll_resource(LOW_FREQ_SCENE_SET_PARA);
	} else {
		hi64xx_release_pll_resource(HI_FREQ_SCENE_SET_PARA);
	}
	OUT_FUNCTION;
	return ret;
}

static int hi64xx_func_para_get(struct krn_param_io_buf *param)
{
	int ret = OK;

	IN_FUNCTION;

	BUG_ON(param == NULL);
	BUG_ON(param->buf_in == NULL);
	BUG_ON(param->buf_size_in == 0);
	BUG_ON(param->buf_out == NULL);
	BUG_ON(param->buf_size_out == 0);

	hi64xx_request_pll_resource(HI_FREQ_SCENE_GET_PARA);
	/* send request */
	ret = hi64xx_sync_write(param->buf_in, param->buf_size_in);
	if (ret != OK) {
		HI64XX_DSP_ERROR("sync write failed\n");
		goto end;
	}

	if (param->buf_size_out <= RESULT_SIZE) {
		HI64XX_DSP_ERROR("not enough space for para get\n");
		goto end;
	}

	/* skip buffer that record result */
	ret = hi64xx_read_mlib_para(param->buf_out + RESULT_SIZE,
				param->buf_size_out - RESULT_SIZE);
	if (ret != OK) {
		HI64XX_DSP_ERROR("read para failed\n");
		goto end;
	}

end:
	hi64xx_release_pll_resource(HI_FREQ_SCENE_GET_PARA);

	OUT_FUNCTION;

	return ret;
}

#ifdef ENABLE_HI6402_HIFI_DEBUG
static int hi64xx_func_om(struct krn_param_io_buf *param)
{
	int ret = OK;

	IN_FUNCTION;

	BUG_ON(param == NULL);
	BUG_ON(param->buf_in == NULL);
	BUG_ON(param->buf_size_in == 0);

	hi64xx_request_pll_resource(HI_FREQ_SCENE_OM);

	ret = hi64xx_sync_write(param->buf_in, param->buf_size_in);
	if (ret != OK) {
		HI64XX_DSP_ERROR("sync write failed\n");
		goto end;
	}

end:
	hi64xx_release_pll_resource(HI_FREQ_SCENE_OM);
	OUT_FUNCTION;
	return ret;
}
#endif /* ENABLE_HI6402_HIFI_DEBUG */


static int hi64xx_func_fasttrans_config(struct krn_param_io_buf *param)
{
	int ret = OK;
	FAST_TRANS_CFG_REQ_STRU* pFastCfg = NULL;

	IN_FUNCTION;

	BUG_ON(param == NULL);
	BUG_ON(param->buf_in == NULL);
	BUG_ON(param->buf_size_in == 0);

	pFastCfg =	(FAST_TRANS_CFG_REQ_STRU*)(param->buf_in);
	HI64XX_DSP_INFO("hi64xx_func_fasttrans_config [%d]\n", pFastCfg->uhwMsgId);

	if (ID_AP_DSP_FASTTRANS_OPEN == pFastCfg->uhwMsgId) {

		hi64xx_hifi_write_reg(0x200072C6, 0x66);/*S2_OL_PGA 192K*/
		hi64xx_hifi_write_reg(0x200072C8, 0x11);/*S3_OL_PGA 16K*/

		if ((pFastCfg->swStatus) & 0x1) {
			hi64xx_hifi_write_reg(0x200072B0, 0x0C);/*S2_CTRL  48K*/
		} else {
			hi64xx_hifi_write_reg(0x200072B0, 0x0E);/*S2_CTRL  192K*/
		}

		hi64xx_hifi_write_reg(0x200072B2, 0x09);/*S3_CTRL*/
		hi64xx_hifi_write_reg(0x200073FE, 0xFF);/*SLIMBUS INPUT ENABLE*/

	} else {
		hi64xx_hifi_write_reg(0x200072C6, 0x00);/*S2_OL_PGA 192K*/
		hi64xx_hifi_write_reg(0x200072C8, 0x00);/*S3_OL_PGA 16K*/

		if ((pFastCfg->swStatus) & 0x1) {
			hi64xx_hifi_write_reg(0x200072B0, 0x0C);/*S2_CTRL  48K*/
		} else {
			hi64xx_hifi_write_reg(0x200072B0, 0x04);/*S2_CTRL  disable*/
		}
		hi64xx_hifi_write_reg(0x200072B2, 0x00);
		hi64xx_hifi_write_reg(0x200073FE, 0xAA);
	}


	ret = hi64xx_sync_write(param->buf_in, param->buf_size_in);
	if (ret != OK) {
		HI64XX_DSP_ERROR("sync write failed\n");
		goto end;
	}

end:
	OUT_FUNCTION;
	return ret;
}

#ifdef ENABLE_HI6402_HIFI_DEBUG
static void hi64xx_reset_codec(void)
{
	unsigned int* addr_gpio = NULL;
	unsigned int* addr_gpio_dir = NULL;

	addr_gpio = (unsigned int*)ioremap_wc(SOC_GPIO_ADDR, 0x4);

	if (NULL == addr_gpio) {
		HI64XX_DSP_INFO("HI6402 RESET GPIO ADDR REMAP ERROR\n");
		return;
	}

	addr_gpio_dir = (unsigned int*)ioremap_wc(SOC_GPIO_DIR_ADDR, 0x4);

	if (NULL == addr_gpio_dir) {
		iounmap(addr_gpio);
		HI64XX_DSP_INFO("HI6402 RESET GPIO DIR ADDR REMAP ERROR\n");
		return;
	}

	*(unsigned int *)(addr_gpio_dir) = 0x02;
	*(unsigned int *)(addr_gpio) = 0x5a;
	mdelay(100);
	*(unsigned int *)(addr_gpio) = 0x58;
	mdelay(100);
	*(unsigned int *)(addr_gpio) = 0x5a;

	iounmap(addr_gpio);
	iounmap(addr_gpio_dir);
}

static int hi64xx_fw_download(void)
{
	int ret = 0;
	const struct firmware *fw = NULL;
	/* download dsp image */
	ret = request_firmware(&fw, "hifi_6402.img", dsp_priv->p_irq->dev);
	if (ret != 0) {
		dev_err(dsp_priv->p_irq->dev, "Failed to request application(%s): %d\n",
			"hifi_6402.img", ret);
		return ret;
	}
	BUG_ON(fw == NULL);
	if (dsp_priv->dsp_config.dsp_ops.ram2axi)
		dsp_priv->dsp_config.dsp_ops.ram2axi(true);
	hi64xx_hifi_download(fw);
	release_firmware(fw);

	return ret;
}

static int hi64xx_func_uartmode(struct krn_param_io_buf *param)
{
	BUG_ON(param == NULL);
	BUG_ON(param->buf_in == NULL);
	BUG_ON(param->buf_size_in == 0);

	dsp_priv->uart_mode = ((UARTMODE_STRU *)(param->buf_in))->uwUartMode;

	return OK;
}
#endif /* ENABLE_HI6402_HIFI_DEBUG */

static void release_requested_pll(void)
{
	int i = 0;

	for(i = 0; i < HI_FREQ_SCENE_BUTT; i++) {
		hi64xx_release_pll_resource(i);
	}

	for(i = 0; i < LOW_FREQ_SCENE_BUTT; i++) {
		hi64xx_release_low_pll_resource(i);
	}

}

static int hi64xx_func_fw_download(struct krn_param_io_buf *param)
{
	char *fw_name = NULL;
	const struct firmware *fw = NULL;
	FW_DOWNLOAD_STRU *dsp_fw_download = NULL;

	int ret = 0;
	int i = 0;

	IN_FUNCTION;

	/* request dsp firmware */
	BUG_ON(param == NULL);
	dsp_fw_download = (FW_DOWNLOAD_STRU *)(param->buf_in);

	BUG_ON(dsp_fw_download == NULL);
	fw_name = dsp_fw_download->chwname;

	ret = request_firmware(&fw, fw_name, dsp_priv->p_irq->dev);
	if (ret != 0) {
		dev_err(dsp_priv->p_irq->dev, "Failed to request dsp image(%s): %d\n", fw_name, ret);
		return ret;
	}
	BUG_ON(fw == NULL);

	/* release all requeseted PLL first beacuse 6402 maybe request PLL but didn't release when exception */
	release_requested_pll();
	hi64xx_hifi_set_pll(true);

	/* restore dsp_if work status */
	for(i = 0; i < HI6402_HIFI_DSP_IF_PORT_BUTT;i++) {
		hi64xx_dsp_if_set_bypass(i,true);
	}

	if (dsp_priv->dsp_config.dsp_ops.runstall)
		dsp_priv->dsp_config.dsp_ops.runstall(false);
	if (dsp_priv->dsp_config.dsp_ops.deinit)
		dsp_priv->dsp_config.dsp_ops.deinit();
	if (dsp_priv->dsp_config.dsp_ops.init)
		dsp_priv->dsp_config.dsp_ops.init();

	dsp_priv->is_watchdog_coming = false;
	dsp_priv->is_sync_write_timeout = false;

	if (dsp_priv->dsp_config.dsp_ops.clk_enable)
		dsp_priv->dsp_config.dsp_ops.clk_enable(true);
	if (dsp_priv->dsp_config.dsp_ops.ram2axi)
		dsp_priv->dsp_config.dsp_ops.ram2axi(true);

	if (dsp_priv->dsp_config.slimbus_load) {
		HI64XX_DSP_INFO("slimbus down load\n");
		hi64xx_release_all_dma();
		hi64xx_hifi_download_slimbus(fw);
	} else {
		HI64XX_DSP_INFO("reg write down load\n");
		hi64xx_hifi_write_reg(dsp_priv->dsp_config.cmd2_addr, dsp_priv->uart_mode);
		hi64xx_hifi_download(fw);
	}

	release_firmware(fw);

	/* notify dsp pwr on */
	hi64xx_hifi_write_reg(dsp_priv->dsp_config.cmd0_addr, HIFI_POWER_ON);
	dsp_priv->dsp_pwron_done = HIFI_STATE_UNINIT;

	/* irq clr,unmask*/
	if (hi64xx_hifi_read_reg(0x20007016)&0x1) {
		hi64xx_hifi_write_reg(0x20007016, 0x1);
	}
	hi64xx_hifi_reg_clr_bit(0x20007019, 0x0);

	if (dsp_priv->dsp_config.dsp_ops.runstall)
		dsp_priv->dsp_config.dsp_ops.runstall(true);

	/*wait 3s for dsp power on */
	/* todo : add a new wq */
	if (wait_event_interruptible_timeout(dsp_priv->dsp_pwron_wq,
		(dsp_priv->dsp_pwron_done == HIFI_STATE_INIT), (3*HZ)) == 0) {
		unsigned int read_res[6];

		HI64XX_DSP_ERROR("wait for dsp pwron timeout\n");
		read_res[0] = hi64xx_hifi_read_reg(0x20007014);
		read_res[1] = hi64xx_hifi_read_reg(0x20007015);
		read_res[2] = hi64xx_hifi_read_reg(0x20007016);
		read_res[3] = hi64xx_hifi_read_reg(0x20007017);
		read_res[4] = hi64xx_hifi_read_reg(0x20007018);
		read_res[5] = hi64xx_hifi_read_reg(0x20007019);
		HI64XX_DSP_ERROR("14:%#x, 15:%#x, 16:%#x, 17:%#x, 18:%#x, 19:%#x\n",read_res[0],read_res[1],read_res[2],read_res[3],read_res[4],read_res[5]);
	}
	msleep(1);
	if (dsp_priv->dsp_config.dsp_ops.ram2axi)
		dsp_priv->dsp_config.dsp_ops.ram2axi(false);
	if (dsp_priv->dsp_config.dsp_ops.clk_enable)
		dsp_priv->dsp_config.dsp_ops.clk_enable(false);
	hi64xx_hifi_set_pll(false);

	OUT_FUNCTION;

	return ret;
}

#ifdef ENABLE_HI6402_HIFI_DEBUG
static int hi64xx_func_mad_test_start(struct krn_param_io_buf *param)
{
	int ret = OK;
	IN_FUNCTION;

	BUG_ON(param == NULL);
	BUG_ON(param->buf_in == NULL);
	BUG_ON(param->buf_size_in == 0);

	ret = hi64xx_request_pll_resource(HI_FREQ_SCENE_MAD_TEST);
	if (ret != OK) {
		goto end;
	}

	ret = hi64xx_sync_write(param->buf_in, param->buf_size_in);
	if (ret != OK) {
		HI64XX_DSP_ERROR("sync write failed\n");
		hi64xx_release_pll_resource(HI_FREQ_SCENE_MAD_TEST);
		goto end;
	}

end:
	OUT_FUNCTION;

	return ret;
}

static int hi64xx_func_mad_test_stop(struct krn_param_io_buf *param)
{
	int ret = OK;
	IN_FUNCTION;

	BUG_ON(param == NULL);
	BUG_ON(param->buf_in == NULL);
	BUG_ON(param->buf_size_in == 0);

	if ((dsp_priv->high_freq_scene_status & (1 << HI_FREQ_SCENE_MAD_TEST)) == 0) {
		HI64XX_DSP_ERROR("scene mad test is NOT opened.\n");
		ret = ERROR;
		goto end;
	}

	ret = hi64xx_sync_write(param->buf_in, param->buf_size_in);
	if (ret != OK) {
		HI64XX_DSP_ERROR("sync write failed\n");
	}

	hi64xx_release_pll_resource(HI_FREQ_SCENE_MAD_TEST);
end:
	OUT_FUNCTION;
	return ret;
}

static int hi64xx_func_wakeup_test(struct krn_param_io_buf *param)
{
	int ret = OK;
	IN_FUNCTION;
	BUG_ON(param == NULL);
	BUG_ON(param->buf_in == NULL);
	BUG_ON(param->buf_size_in == 0);

	if ((dsp_priv->low_freq_scene_status & (1 << LOW_FREQ_SCENE_WAKE_UP)) == 0) {
		HI64XX_DSP_INFO("scene wakeup is NOT opened, status:%d.\n", dsp_priv->low_freq_scene_status);
		ret = ERROR;
		goto end;
	}

	ret = hi64xx_sync_write(param->buf_in, param->buf_size_in);
	if (ret != OK)
		HI64XX_DSP_ERROR("sync write failed, ret:%d.\n", ret);

end:
	OUT_FUNCTION;
	return ret;
}

static int hi64xx_func_fault_inject(struct krn_param_io_buf *param)
{
	int ret = OK;
	IN_FUNCTION;
	BUG_ON(param == NULL);
	BUG_ON(param->buf_in == NULL);
	BUG_ON(param->buf_size_in == 0);

	ret = hi64xx_request_pll_resource(HI_FREQ_SCENE_FAULT_INJECT);
	if (ret != OK) {
		goto end;
	}

	ret = hi64xx_sync_write(param->buf_in, param->buf_size_in);
	if (ret != OK)
		HI64XX_DSP_ERROR("sync write failed, ret:%d.\n", ret);

	/* don't release pll for fault process done */

end:
	OUT_FUNCTION;
	return ret;
}

#endif /* ENABLE_HI6402_HIFI_DEBUG */

static cmd_process_func hi64xx_select_func(const unsigned char *arg,
					   const struct cmd_func_pair *func_map,
					   const unsigned int func_map_size)
{
	unsigned int i = 0;
	unsigned short msg_id;

	BUG_ON(arg == NULL);

	msg_id = *(unsigned short*)arg;

	IN_FUNCTION;
	for (i = 0; i < func_map_size; i++) {
		if (func_map[i].cmd_id == msg_id) {
			HI64XX_DSP_INFO("cmd:%s\n", func_map[i].cmd_name);
			return func_map[i].func;
		}
	}

	HI64XX_DSP_ERROR("cmd_process_func for id:%d not found!\n", msg_id);

	OUT_FUNCTION;
	return (cmd_process_func)NULL;
}

/* not sure whether async commond would be used in future */
#if 0
static struct cmd_func_pair async_cmd_func_map[] = {
};

static int hi6402_hifi_async_cmd(unsigned long arg)
{
	int ret = OK;
	cmd_process_func func = NULL;
	struct misc_io_async_param param;
	struct krn_param_io_buf krn_param;

	memset(&param, 0, sizeof(param));
	memset(&krn_param, 0, sizeof(krn_param));

	IN_FUNCTION;

	//FIXME: should check arg not be NULL?
	if (copy_from_user(&param, (void*)arg,
			sizeof(struct misc_io_async_param))) {
		HI64XX_DSP_ERROR("copy_from_user fail.\n");
		ret = ERROR;
		goto end;
	}

	ret = hi64xx_get_input_param(param.para_size_in,
			INT_TO_ADDR(param.para_in_l, param.para_in_h),
			&krn_param.buf_size_in,
			(void **)&krn_param.buf_in);
	if (ret != OK) {
		HI64XX_DSP_ERROR("get_input_param ret=%d\n", ret);
		goto end;
	}

	func = hi64xx_select_func(krn_param.buf_in, async_cmd_func_map,
				  ARRAY_SIZE(async_cmd_func_map));
	if (func == NULL) {
		HI64XX_DSP_ERROR("select_func error.\n");
		ret = ERROR;
		goto end;
	}

	ret = func(&krn_param);
	if (ret != OK) {
		HI64XX_DSP_ERROR("func process error.\n");
		goto end;
	}

end:
	hi64xx_param_free((void **)&krn_param.buf_in);

	OUT_FUNCTION;

	return ret;
}
#endif

static struct cmd_func_pair sync_cmd_func_map[] = {
	{ ID_AP_DSP_IF_OPEN,		hi64xx_func_if_open,		"ID_AP_DSP_IF_OPEN"		},
	{ ID_AP_DSP_IF_CLOSE,		hi64xx_func_if_close,		"ID_AP_DSP_IF_CLOSE"		},
	{ ID_AP_DSP_PARAMETER_SET,	hi64xx_func_para_set,		"ID_AP_DSP_PARAMETER_SET"	},
	{ ID_AP_DSP_PARAMETER_GET,	hi64xx_func_para_get,		"ID_AP_DSP_PARAMETER_GET"	},
	{ ID_AP_DSP_FASTMODE,		hi64xx_func_fastmode,		"ID_AP_DSP_FASTMODE"		},
	{ ID_AP_IMGAE_DOWNLOAD, 	hi64xx_func_fw_download,	"ID_AP_IMGAE_DOWNLOAD"		},
	{ ID_AP_DSP_FASTTRANS_OPEN,	hi64xx_func_fasttrans_config,	"ID_AP_DSP_FASTTRANS_OPEN"	},
	{ ID_AP_DSP_FASTTRANS_CLOSE,	hi64xx_func_fasttrans_config,	"ID_AP_DSP_FASTTRANS_CLOSE"	},
#ifdef ENABLE_HI6402_HIFI_DEBUG
	{ ID_AP_DSP_UARTMODE,		hi64xx_func_uartmode,		"ID_AP_DSP_UARTMODE"		},
	{ ID_AP_DSP_OM,			hi64xx_func_om,			"ID_AP_DSP_OM"			},
	{ ID_AP_DSP_MADTEST_START,	hi64xx_func_mad_test_start,	"ID_AP_DSP_MADTEST_START"	},
	{ ID_AP_DSP_MADTEST_STOP,	hi64xx_func_mad_test_stop,	"ID_AP_DSP_MADTEST_STOP"	},
	{ ID_AP_DSP_WAKEUP_TEST,	hi64xx_func_wakeup_test,	"ID_AP_DSP_WAKEUP_TEST"		},
	{ ID_FAULTINJECT,		hi64xx_func_fault_inject,	"ID_FAULTINJECT"		},
#endif
};

#ifdef ENABLE_HI6402_HIFI_DEBUG
static int hi64xx_hifi_read_msg_cmd(unsigned long arg)
{
	int ret = OK;
	struct misc_io_sync_param param;
	struct krn_param_io_buf krn_param;
	unsigned short msg_id = 0;
	int len = 0;
	IN_FUNCTION;

	memset(&param, 0, sizeof(param));
	memset(&krn_param, 0, sizeof(krn_param));

	if (copy_from_user(&param, (void __user *)arg,
		sizeof(struct misc_io_sync_param))) {
		HI64XX_DSP_ERROR("copy_from_user fail.\n");
		ret = ERROR;
		goto end;
	}

	ret = hi64xx_alloc_output_param_buffer(param.para_size_out,
		INT_TO_ADDR(param.para_out_l, param.para_out_h),
		&krn_param.buf_size_out,
		(void **)&krn_param.buf_out);

	if (ret != OK) {
		HI64XX_DSP_ERROR("alloc output buffer failed.\n");
		goto end;
	}

	ret = hi64xx_get_input_param(param.para_size_in,
		INT_TO_ADDR(param.para_in_l, param.para_in_h),
		&krn_param.buf_size_in,
		(void **)&krn_param.buf_in);

	if (ret != OK) {
		HI64XX_DSP_ERROR("get_input_param ret=%d\n", ret);
		goto end;
	}

	msg_id = *(unsigned short*)krn_param.buf_in;
	if ((msg_id != ID_AP_IMGAE_DOWNLOAD && msg_id != ID_AP_DSP_UARTMODE)
		&& dsp_priv->dsp_pwron_done == HIFI_STATE_UNINIT) {
		HI64XX_DSP_ERROR("6402 firmware not load!!cmd[%d] not send!!\n",msg_id);
		goto end;
	}

	len = hi64xx_read_mlib_test_para(krn_param.buf_out, krn_param.buf_size_out);
	krn_param.buf_size_out = len;
	param.para_size_out = krn_param.buf_size_out;

	/* copy result to user space */
	ret = hi64xx_put_output_param(param.para_size_out,
			INT_TO_ADDR(param.para_out_l, param.para_out_h),
			krn_param.buf_size_out,
			(void *)krn_param.buf_out);

	if (ret != OK) {
		HI64XX_DSP_ERROR("copy result to user failed\n");
		goto end;
	}

	ret = len;
end:
	hi64xx_param_free((void **)&krn_param.buf_in);
	hi64xx_param_free((void **)&krn_param.buf_out);

	OUT_FUNCTION;
	return ret;
}
#endif /* ENABLE_HI6402_HIFI_DEBUG */

static int hi64xx_hifi_sync_cmd(unsigned long arg)
{
	int ret = OK;
	cmd_process_func func = NULL;
	struct misc_io_sync_param param;
	struct krn_param_io_buf krn_param;
	unsigned short msg_id = 0;

	IN_FUNCTION;

	memset(&param, 0, sizeof(param));
	memset(&krn_param, 0, sizeof(krn_param));

	if (copy_from_user(&param, (void __user *)arg,
			   sizeof(struct misc_io_sync_param))) {
		HI64XX_DSP_ERROR("copy_from_user fail.\n");
		ret = ERROR;
		goto end;
	}

	ret = hi64xx_alloc_output_param_buffer(param.para_size_out,
			INT_TO_ADDR(param.para_out_l, param.para_out_h),
			&krn_param.buf_size_out,
			(void **)&krn_param.buf_out);
	if (ret != OK) {
		HI64XX_DSP_ERROR("alloc output buffer failed.\n");
		goto end;
	}

	ret = hi64xx_get_input_param(param.para_size_in,
			INT_TO_ADDR(param.para_in_l, param.para_in_h),
			&krn_param.buf_size_in,
			(void **)&krn_param.buf_in);
	if (ret != OK) {
		HI64XX_DSP_ERROR("get_input_param ret=%d\n", ret);
		goto end;
	}

	msg_id = *(unsigned short*)krn_param.buf_in;
	if ((msg_id != ID_AP_IMGAE_DOWNLOAD && msg_id != ID_AP_DSP_UARTMODE)
		&& dsp_priv->dsp_pwron_done == HIFI_STATE_UNINIT) {
		HI64XX_DSP_ERROR("6402 firmware not load,cmd:%d not send\n", msg_id);
		goto end;
	}

	func = hi64xx_select_func(krn_param.buf_in, sync_cmd_func_map,
				  ARRAY_SIZE(sync_cmd_func_map));
	if (func == NULL) {
		HI64XX_DSP_ERROR("select_func error.\n");
		ret = ERROR;
		goto end;
	}

	ret = func(&krn_param);
	if (ret != OK) {
		/* don't print err if redundant cmd was received */
		if (ret != REDUNDANT) {
			HI64XX_DSP_ERROR("func process error.\n");
		}
		goto end;
	}

	/* write result to out buf */
	BUG_ON(krn_param.buf_out == NULL);
	if (krn_param.buf_size_out >= sizeof(int)) {
		*(int *)krn_param.buf_out = ret;
	} else {
		HI64XX_DSP_ERROR("not enough space to save result\n");
		goto end;
	}

	/* copy result to user space */
	ret = hi64xx_put_output_param(param.para_size_out,
			INT_TO_ADDR(param.para_out_l, param.para_out_h),
			krn_param.buf_size_out,
			(void *)krn_param.buf_out);
	if (ret != OK) {
		HI64XX_DSP_ERROR("copy result to user failed\n");
		goto end;
	}

end:
	hi64xx_param_free((void **)&krn_param.buf_in);
	hi64xx_param_free((void **)&krn_param.buf_out);

	OUT_FUNCTION;

	return ret;
}

/*****************************************************************************
 * misc driver
 * */
static int hi64xx_hifi_misc_open(struct inode *finode, struct file *fd)
{
	return 0;
}

static int hi64xx_hifi_misc_release(struct inode *finode, struct file *fd)
{
	return 0;
}

static long hi64xx_hifi_misc_ioctl(struct file *fd,
                                   unsigned int cmd,
                                   unsigned long arg)
{
	int ret = 0;

	IN_FUNCTION;

	if (NULL == (void __user *)arg) {
		HI64XX_DSP_ERROR("input error: arg is NULL\n");
		return -EINVAL;
	}

	switch(cmd) {
/* not sure whether async commond would be used in future */
#if 0
		case HI6402_HIFI_MISC_IOCTL_ASYNCMSG:
			HI64XX_DSP_DEBUG("ioctl: HIFI_MISC_IOCTL_ASYNCMSG\n");
			mutex_lock(&dsp_priv->msg_mutex);
			ret = hi6402_hifi_async_cmd(arg);
			mutex_unlock(&dsp_priv->msg_mutex);
			break;
#endif
		case HI6402_HIFI_MISC_IOCTL_SYNCMSG:
			HI64XX_DSP_DEBUG("ioctl: HIFI_MISC_IOCTL_SYNCMSG\n");
			mutex_lock(&dsp_priv->msg_mutex);
			ret = hi64xx_hifi_sync_cmd(arg);
			mutex_unlock(&dsp_priv->msg_mutex);
			break;
#ifdef ENABLE_HI6402_HIFI_DEBUG
		case HI6402_HIFI_MISC_IOCTL_MLIB_TEST_MSG:
			HI64XX_DSP_DEBUG("ioctl: HI6402_HIFI_MISC_IOCTL_MLIB_TEST_MSG\n");
			mutex_lock(&dsp_priv->msg_mutex);
			ret = hi64xx_hifi_read_msg_cmd(arg);
			mutex_unlock(&dsp_priv->msg_mutex);
			break;
#endif
		default:
			HI64XX_DSP_ERROR("ioctl: Invalid CMD =0x%x\n", cmd);
			//TODO: should return a meaningful value
			ret = -1;
			break;
	}
	HI64XX_DSP_INFO("ioctl: ret %d\n",ret);
	OUT_FUNCTION;

	return (long)ret;
}

static long hi64xx_hifi_misc_ioctl32(struct file *fd,
                                   unsigned int cmd,
                                   unsigned long arg)
{
	void __user *user_ptr = (void __user *)compat_ptr(arg);

	return hi64xx_hifi_misc_ioctl(fd, cmd, (unsigned long)user_ptr);
}

#ifdef ENABLE_HI6402_HIFI_DEBUG
static ssize_t hi64xx_hifi_misc_read(struct file *file, char __user *buf,
                                     size_t nbytes, loff_t *pos)
{
	struct reg_rw_struct kern_buf;

	if (NULL == buf) {
		HI64XX_DSP_ERROR("input error: buf is NULL\n");
		return -EFAULT;
	}

	if (nbytes != sizeof(kern_buf)) {
		HI64XX_DSP_ERROR("nbytes:%zu from user space exceed" \
			"sizeof(kern_buf):%zu\n", nbytes, sizeof(kern_buf));
		return -EFAULT;
	}

	if (copy_from_user(&kern_buf, buf, nbytes)) {
		HI64XX_DSP_ERROR("copy_from_user fail.\n");
		return -EFAULT;
	}

	kern_buf.val = hi64xx_hifi_read_reg(kern_buf.reg);
	if (copy_to_user(buf, &kern_buf, nbytes)) {
		HI64XX_DSP_ERROR("copy_to_user fail.\n");
		return -EFAULT;
	}

	return sizeof(kern_buf);
}

static ssize_t hi64xx_hifi_misc_write(struct file *file,
				      const char __user *buf,
				      size_t nbytes, loff_t *pos)
{
	struct reg_rw_struct kern_buf;

	if (NULL == buf) {
		HI64XX_DSP_ERROR("input error: buf is NULL\n");
		return -EFAULT;
	}

	if (nbytes != sizeof(kern_buf)) {
		HI64XX_DSP_ERROR("nbytes:%zu from user space exceed" \
			"sizeof(kern_buf):%zu\n", nbytes, sizeof(kern_buf));
		return -EFAULT;
	}

	if (copy_from_user(&kern_buf, buf, nbytes)) {
		HI64XX_DSP_ERROR("copy_from_user fail.\n");
		return -EFAULT;
	}

	hi64xx_hifi_write_reg(kern_buf.reg, kern_buf.val);

	return sizeof(kern_buf);
}
#endif /* ENABLE_HI6402_HIFI_DEBUG */

static const struct file_operations hi64xx_hifi_misc_fops = {
	.owner			= THIS_MODULE,
	.open			= hi64xx_hifi_misc_open,
	.release		= hi64xx_hifi_misc_release,
#ifdef ENABLE_HI6402_HIFI_DEBUG
	.read			= hi64xx_hifi_misc_read,
	.write			= hi64xx_hifi_misc_write,
#endif /* ENABLE_HI6402_HIFI_DEBUG */
	.unlocked_ioctl 	= hi64xx_hifi_misc_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl 		= hi64xx_hifi_misc_ioctl32,
#endif
};

static struct miscdevice hi64xx_hifi_misc_device = {
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= "hi6402_hifi_misc",
	.fops	= &hi64xx_hifi_misc_fops,
};

#ifdef ENABLE_HI6402_HIFI_DEBUG
static void hi64xx_hifi_enable_jtag(void)
{
	hi64xx_hifi_write_reg(HI64xx_DSP_IOS_IOM_I2S2_SDO, 0x1c4);
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_IOS_AF_CTRL0, 0);
	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_IOSHARE_BASE, 5);
}

static void hi64xx_hifi_enable_uart(void)
{
	/* enable jtag and uart should set in dsp just for test*/
	hi64xx_hifi_write_reg(HI64xx_DSP_IOS_IOM_UART_TXD, 0x1c4);
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_IOSHARE_BASE, 12);
}

/* dump 64xxdsp manually, debug only */
#define DUMP_DIR_LEN  128
#define DUMP_DIR_ROOT "/data/hisi_logs/hi64xxdump/" /* length:28 */

static int create_dir(const char *path)
{
	int fd = -1;
	mm_segment_t old_fs;

	BUG_ON(NULL == path);

	old_fs = get_fs();
	set_fs(KERNEL_DS);
	fd = sys_access(path, 0);
	if (fd) {
		HI64XX_DSP_INFO("need create dir %s.\n", path);
		fd = sys_mkdir(path, 0770);
		if (fd < 0) {
			HI64XX_DSP_ERROR("create dir %s failed, fd:%d.\n", path, fd);
			set_fs(old_fs);
			return -1;
		}
		HI64XX_DSP_INFO("create dir %s successed, fd: %d.\n", path, fd);
	}
	set_fs(old_fs);

	return 0;
}

/* get dir_name with timestamp */
static void get_dir_name(char *dir_name, size_t size)
{
	struct rtc_time tm;
	struct timeval tv;

	memset(&tm, 0, sizeof(tm));
	memset(&tv, 0, sizeof(tv));

	do_gettimeofday(&tv);
	tv.tv_sec -= sys_tz.tz_minuteswest * 60;
	rtc_time_to_tm(tv.tv_sec, &tm);

	snprintf(dir_name, size, "%s%04d%02d%02d%02d%02d%02d/",
		DUMP_DIR_ROOT,
		tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
		tm.tm_hour, tm.tm_min, tm.tm_sec);

	return;
}

extern void rdr_audio_codec_dump(u32 modid, char* pathname, pfn_cb_dump_done pfb);

static void hi64xx_hifi_dump(void)
{
#ifdef CONFIG_HISI_HIFI_BB
	static char dirname[DUMP_DIR_LEN];

	HI64XX_DSP_INFO("manual dump 64xxdsp\n");

	if (create_dir(DUMP_DIR_ROOT) != 0) {
		HI64XX_DSP_ERROR("create dir %s failed\n", DUMP_DIR_ROOT);
		return;
	}

	if (hi64xx_chown(DUMP_DIR_ROOT, ROOT_UID, SYSTEM_GID)) {
		HI64XX_DSP_ERROR("chown %s failed!\n", DUMP_DIR_ROOT);
	}

	memset(dirname, 0, sizeof(dirname));
	get_dir_name(dirname, sizeof(dirname));
	HI64XX_DSP_INFO("dir name is: %s\n", dirname);

	if (create_dir(dirname) != 0) {
		HI64XX_DSP_ERROR("create dir %s failed\n", dirname);
		return;
	}

	if (hi64xx_chown(dirname, ROOT_UID, SYSTEM_GID)) {
		HI64XX_DSP_ERROR("chown %s failed!\n", dirname);
	}

	/* for debug purpose,  use "rdr_system_error" if there's a real error */
	rdr_audio_codec_dump(~0, dirname, NULL);
#endif
}

/* ********************************************************************
 * sysfs device, for debugging
 * ********************************************************************/
static ssize_t hi64xx_debug_show(struct file *file, char __user *buf,
				size_t size, loff_t *data)
{
	char *info_string = " 0:img download\n"            \
			    " 1:init\n"                    \
			    " 2:deinit\n"                  \
			    " 3:run\n"                     \
			    " 4:stop\n"                    \
			    " 5:jtag enable\n"             \
			    " 6:uart enable\n"             \
			    " 7:pll ebable\n"              \
			    " 8:pll disable\n"             \
			    " 9:low_pll enable\n"          \
			    "10:low_pll disable\n"         \
			    "11:FPGA codec reset\n"        \
			    "12:FPGA power_on test\n"      \
			    "13:FPGA om test\n"            \
			    "14:FPGA factory test\n"       \
			    "15:dump\n";

	if (NULL == buf) {
		HI64XX_DSP_ERROR("input error: buf is NULL\n");
		return -EINVAL;
	}

	return simple_read_from_buffer(buf, size, data, info_string, strlen(info_string));
}

static ssize_t hi64xx_debug_store(struct file *file, const char __user *buf,
				size_t size, loff_t *data)
{
	unsigned long cmd = 0;
	unsigned int* addr;
	ssize_t ret;
	char level_str[MAX_STR_LEN] = {0};

	if (buf == NULL) {
		HI64XX_DSP_ERROR("buf is NULL\n");
		return -EINVAL;
	}

	ret = simple_write_to_buffer(level_str, MAX_STR_LEN - 1 , data, buf, size);
	if (ret != size) {
		HI64XX_DSP_ERROR("Input param buf read error, return value: %zd\n", ret);
		return -EINVAL;
	}

	if (strict_strtoul(level_str, 0, &cmd) != 0) {
		HI64XX_DSP_ERROR("input para is error\n");
		return -EINVAL;
	}

	switch (cmd) {
	case HI64XX_HIFI_IMG_DOWNLOAD:
		hi64xx_fw_download();
		break;
	case HI64XX_HIFI_INIT:
		if (dsp_priv->dsp_config.dsp_ops.init)
			dsp_priv->dsp_config.dsp_ops.init();
		dsp_priv->is_watchdog_coming = false;
		dsp_priv->is_sync_write_timeout = false;
		break;
	case HI64XX_HIFI_DEINIT:
		if (dsp_priv->dsp_config.dsp_ops.deinit)
			dsp_priv->dsp_config.dsp_ops.deinit();
		break;
	case HI64XX_HIFI_RUNSTALL_PULL_DOWN:
		if (dsp_priv->dsp_config.dsp_ops.runstall)
			dsp_priv->dsp_config.dsp_ops.runstall(true);
		break;
	case HI64XX_HIFI_RUNSTALL_PULL_UP:
		if (dsp_priv->dsp_config.dsp_ops.runstall)
			dsp_priv->dsp_config.dsp_ops.runstall(false);
		break;
	case HI64XX_HIFI_JTAG_ENABLE:
		hi64xx_hifi_enable_jtag();
		break;
	case HI64XX_HIFI_UART_ENABLE:
		hi64xx_hifi_enable_uart();
		break;
	case HI64XX_HIFI_HIPLL_ENABLE:
		hi64xx_hifi_set_pll(true);
		break;
	case HI64XX_HIFI_HIPLL_DIAABLE:
		hi64xx_hifi_set_pll(false);
		break;
	case HI64XX_HIFI_LOWPLL_ENABLE:
		hi64xx_hifi_set_low_pll(true);
		break;
	case HI64XX_HIFI_LOWPLL_DIAABLE:
		hi64xx_hifi_set_low_pll(false);
		break;
	/* this case just for assic and FPGA test */
	case HI64XX_HIFI_FPGA_CODEC_RESET:
		hi64xx_reset_codec();
		break;
	case HI64XX_HIFI_FPGA_PWRON_TEST:
		if (dsp_priv->dsp_config.dsp_ops.runstall)
			dsp_priv->dsp_config.dsp_ops.runstall(false);
		if (dsp_priv->dsp_config.dsp_ops.deinit)
			dsp_priv->dsp_config.dsp_ops.deinit();
		if (dsp_priv->dsp_config.dsp_ops.init)
			dsp_priv->dsp_config.dsp_ops.init();

		dsp_priv->is_watchdog_coming = false;
		dsp_priv->is_sync_write_timeout = false;
		hi64xx_fw_download();

		if (dsp_priv->dsp_config.dsp_ops.runstall)
			dsp_priv->dsp_config.dsp_ops.runstall(true);

		break;
	/* this case just for om set GPIO */
	case HI64XX_HIFI_FPGA_OM_TEST:
		addr = (unsigned int*)ioremap_wc(HI64XX_HIFI_FPGA_OM_TEST_ADDR, 0x4);

		if (NULL == addr) {
			HI64XX_DSP_INFO("HI6402_HIFI_FPGA_OM_TEST ADDR REMAP ERROR\n");
			return -EINVAL;
		}

		*(unsigned int *)(addr) = 0x2;
		iounmap(addr);
		break;
	/* dump 6402 panic stack; logs; regs*/
	case HI64XX_HIFI_DUMP:
		hi64xx_hifi_dump();
		break;
	default:
		break;
	}

	return size;
}

static const struct file_operations hi64xxdebug_proc_ops = {
	.owner = THIS_MODULE,
	.read = hi64xx_debug_show,
	.write = hi64xx_debug_store,
};

static ssize_t hi64xx_debuglevel_show(struct file *file, char __user *buf,
				size_t size, loff_t *data)
{
	ssize_t ret;
	char level_str[MAX_STR_LEN] = {0};

	IN_FUNCTION;

	if (NULL == buf) {
		HI64XX_DSP_ERROR("input error: buf is NULL\n");
		return -EINVAL;
	}

	snprintf(level_str, MAX_STR_LEN-1, "%lu\n", hi64xx_dsp_debug_level);
	ret = simple_read_from_buffer(buf, size, data, level_str, strlen(level_str));

	OUT_FUNCTION;

	return ret;
}

static ssize_t hi64xx_debuglevel_store(struct file *file, const char __user *buf,
				size_t size, loff_t *data)
{
	ssize_t ret;
	char level_str[MAX_STR_LEN] = {0};

	IN_FUNCTION;

	if (buf == NULL) {
		HI64XX_DSP_ERROR("buf is NULL\n");
		return -EINVAL;
	}

	ret = simple_write_to_buffer(level_str, MAX_STR_LEN - 1 , data, buf, size);
	if (ret != size) {
		HI64XX_DSP_ERROR("Input param buf read error, return value: %zd\n", ret);
		return -EINVAL;
	}

	if (strict_strtoul(level_str, 0, &hi64xx_dsp_debug_level) != 0) {
		HI64XX_DSP_ERROR("input para is error\n");
		return -EINVAL;
	}

	OUT_FUNCTION;

	return size;
}

static const struct file_operations hi64xx_debuglevel_proc_ops = {
	.owner = THIS_MODULE,
	.read = hi64xx_debuglevel_show,
	.write = hi64xx_debuglevel_store,
};

static void create_hi64xxdebug_proc_file(void)
{
	struct proc_dir_entry *ent_debug;
	struct proc_dir_entry *ent_debuglevel;

	/* Creating read/write "status" entry */
	ent_debug = proc_create(HI64XXDEBUG_PROC_FILE, S_IRUGO | S_IWUSR|S_IWGRP,
							hi64xx_debug_dir, &hi64xxdebug_proc_ops);
	ent_debuglevel = proc_create(HI64XXDEBUG_LEVEL_PROC_FILE,
							S_IRUGO | S_IWUSR|S_IWGRP,hi64xx_debug_dir,
							&hi64xx_debuglevel_proc_ops);

	if ((ent_debug == NULL) || (ent_debuglevel == NULL)) {
		remove_proc_entry("hi6402dbg", 0);
		HI64XX_DSP_ERROR("create proc file fail\n");
	}
}

static void remove_hi64xxdebug_proc_file(void)
{
	remove_proc_entry(HI64XXDEBUG_PROC_FILE, hi64xx_debug_dir);
	remove_proc_entry(HI64XXDEBUG_LEVEL_PROC_FILE, hi64xx_debug_dir);
}

static int hi64xx_create_procfs(void)
{
	hi64xx_debug_dir = proc_mkdir(HI64XXDEBUG_PATH, NULL);
	if (hi64xx_debug_dir == NULL) {
		HI64XX_DSP_ERROR("Unable to create /proc/hi64xxdbg directory\n");
		return -ENOMEM;
	}
	create_hi64xxdebug_proc_file();
	return 0;
}

static void hi64xx_remove_procfs(void)
{
	remove_hi64xxdebug_proc_file();

	return;
}
#endif /* ENABLE_HI6402_HIFI_DEBUG */

#ifdef CONFIG_PM
static int hi64xx_sr_event(struct notifier_block *this,
		unsigned long event, void *ptr)
{
	switch (event) {
	case PM_POST_HIBERNATION:
	case PM_POST_SUSPEND:
		HI64XX_DSP_INFO("resume +\n");
		atomic_set(&hi64xx_in_suspend, 0);
		HI64XX_DSP_INFO("resume -\n");
		break;

	case PM_HIBERNATION_PREPARE:
	case PM_SUSPEND_PREPARE:
		HI64XX_DSP_INFO("suspend +\n");
		atomic_set(&hi64xx_in_suspend, 1);
		while (1) {
			if (atomic_read(&hi64xx_in_saving))
				msleep(100);
			else
				break;
		}
		HI64XX_DSP_INFO("suspend -\n");
		break;
	default:
		return NOTIFY_DONE;
	}
	return NOTIFY_OK;
}
#endif /* CONFIG_PM */

static int hi64xx_reboot_notifier(struct notifier_block *nb,
		unsigned long foo, void *bar)
{
	HI64XX_DSP_INFO("reboot +\n");
	atomic_set(&hi64xx_in_suspend, 1);
	while (1) {
		if (atomic_read(&hi64xx_in_saving))
			msleep(100);
		else
			break;
	}
	HI64XX_DSP_INFO("reboot -\n");

	return 0;
}

static int hi64xx_resmgr_notifier(struct notifier_block *this,
		unsigned long event, void *ptr)
{
	struct pll_switch_event *switch_event = (struct pll_switch_event *)ptr;
	enum pll_state pll_state = PLL_RST;

	HI64XX_DSP_INFO("event:%lu, from:%d, to:%d\n", event, switch_event->from, switch_event->to);

	switch (switch_event->to) {
	case PLL_HIGH:
		pll_state = PLL_HIGH_FREQ;
		break;
	case PLL_LOW:
		pll_state = PLL_LOW_FREQ;
		break;
	case PLL_NONE:
		pll_state = PLL_PD;
		break;
	default:
		HI64XX_DSP_ERROR("unsupport pll state:%d\n", switch_event->to);
		return 0;
	}

	switch (event) {
	case PRE_PLL_SWITCH:
		hi64xx_hifi_cfg_before_pll_switch();
		break;
	case POST_PLL_SWITCH:
		hi64xx_hifi_cfg_after_pll_switch(pll_state);
		break;
	default:
		HI64XX_DSP_ERROR("err pll swtich event:%lu\n", event);
		break;
	}

	return 0;
}

void hi64xx_watchdog_send_event(void)
{
	char *envp[2] = {"hi6402_watchdog", NULL};
	HI64XX_DSP_ERROR("hi6402 watchdog coming, now reset mediaserver !\n");
	kobject_uevent_env(&dsp_priv->p_irq->dev->kobj, KOBJ_CHANGE, envp);
}

static irqreturn_t hi64xx_wtd_irq_handler(int irq, void *data)
{
	dsp_priv->is_watchdog_coming = true;

	/* call rdr_hisi_audio_codec.c watchdog process */
#if !defined(PLATFORM_HI3660)
	rdr_codec_hifi_watchdog_process();
#endif
	return IRQ_HANDLED;
}

struct reg_dump {
	unsigned int addr;
	unsigned int len;
	const char *name;
};

static const struct reg_dump s_reg_dump[] = {
	{HI64xx_DUMP_CFG_SUB_ADDR1,		HI64xx_DUMP_CFG_SUB_SIZE1,	"page_cfg_subsys:"},
	{HI64xx_DUMP_CFG_SUB_ADDR2,		HI64xx_DUMP_CFG_SUB_SIZE2,	"page_cfg_subsys:"},
	{HI64xx_DUMP_AUDIO_SUB_ADDR,		HI64xx_DUMP_AUDIO_SUB_SIZE,	"aud_reg:"},
	{HI64xx_DUMP_DSP_EDMA_ADDR1,		HI64xx_DUMP_DSP_EDMA_SIZE1,	"DMA:"},
	{HI64xx_DUMP_DSP_EDMA_ADDR2,		HI64xx_DUMP_DSP_EDMA_SIZE2,	"DMA:"},
	{HI64xx_DUMP_DSP_EDMA_ADDR3,		HI64xx_DUMP_DSP_EDMA_SIZE3,	"DMA:"},
	{HI64xx_DUMP_DSP_WATCHDOG_ADDR1,	HI64xx_DUMP_DSP_WATCHDOG_SIZE1,	"WTD:"},
	{HI64xx_DUMP_DSP_WATCHDOG_ADDR2,	HI64xx_DUMP_DSP_WATCHDOG_SIZE2,	"WTD:"},
	{HI64xx_DUMP_DSP_SCTRL_ADDR1,		HI64xx_DUMP_DSP_SCTRL_SIZE1,	"SCTRL:"},
	{HI64xx_DUMP_DSP_SCTRL_ADDR2,		HI64xx_DUMP_DSP_SCTRL_SIZE2,	"SCTRL:"},
	/* XXX: 0x20007038, 0x20007039 should always read in the end */
	{HI64xx_DUMP_CFG_SUB_ADDR3,		HI64xx_DUMP_CFG_SUB_SIZE3,	"page_cfg_subsys:"},
};

size_t hi64xx_get_dump_reg_size(void)
{
	int i = 0;
	size_t size = 0;

	for (i = 0; i < ARRAY_SIZE(s_reg_dump); i++) {
		size += s_reg_dump[i].len;
	}

	HI64XX_DSP_INFO("dump size of 64xx regs is 0x%lx\n", size);

	return size;
}

size_t hi64xx_append_comment(char *buf, const size_t size)
{
	int i = 0;
	size_t offset = 0;
	size_t buffer_used = 0;

	for (i = 0; i < ARRAY_SIZE(s_reg_dump); i++) {
		BUG_ON(buffer_used >= size);
		snprintf(buf + buffer_used, size - buffer_used,
			"%s 0x%08x->0x%08lx ",
			s_reg_dump[i].name, s_reg_dump[i].addr, offset);
		offset += s_reg_dump[i].len;
		buffer_used = strlen(buf);
	}

	HI64XX_DSP_INFO("comment for reg dump size is 0x%lx\n", buffer_used);

	return buffer_used;
}

/* caller should guarantee input para valid */
void hi64xx_misc_dump_reg(char *buf, const size_t size)
{
	size_t i = 0;
	size_t buffer_used = 0;
	int ret = 0;

	BUG_ON(NULL == buf);

	ret = hi64xx_request_pll_resource(HI_FREQ_SCENE_DUMP);
	if (ret != 0) {
		HI64XX_DSP_ERROR("dump reg request pll failed\n");
		return;
	}

	for (i = 0; i < ARRAY_SIZE(s_reg_dump); i++) {
		BUG_ON(buffer_used + s_reg_dump[i].len > size);
		hi64xx_read(s_reg_dump[i].addr, buf + buffer_used, s_reg_dump[i].len);
		buffer_used += s_reg_dump[i].len;
	}

	ret = hi64xx_release_pll_resource(HI_FREQ_SCENE_DUMP);
	if (ret != 0) {
		HI64XX_DSP_ERROR("dump reg release pll failed\n");
		return;
	}
}

void hi64xx_misc_dump_bin(const unsigned int addr, char *buf, const size_t len)
{
	int ret = 0;

	ret = hi64xx_request_pll_resource(HI_FREQ_SCENE_DUMP);
	if (ret != 0) {
		HI64XX_DSP_ERROR("dump bin request pll failed\n");
		return;
	}

	hi64xx_read(addr, buf, len);

	ret = hi64xx_release_pll_resource(HI_FREQ_SCENE_DUMP);
	if (ret != 0) {
		HI64XX_DSP_ERROR("dump bin release pll failed\n");
		return;
	}
}


int hi64xx_hifi_misc_suspend(void)
{
	int ret = 0;

	HI64XX_DSP_INFO("suspend+\n");

	/* mad */
	if ((NULL != dsp_priv) && (PLL_LOW_FREQ == dsp_priv->pll_state) && dsp_priv->dsp_is_running) {
		if (dsp_priv->dsp_config.dsp_ops.suspend)
			ret = dsp_priv->dsp_config.dsp_ops.suspend();
	}

	HI64XX_DSP_INFO("suspend-\n");

	return ret;
}

int hi64xx_hifi_misc_resume(void)
{
	int ret = 0;

	HI64XX_DSP_INFO("resume+\n");

	/* mad */
	if ((NULL != dsp_priv) && (PLL_LOW_FREQ == dsp_priv->pll_state) && dsp_priv->dsp_is_running) {
		if (dsp_priv->dsp_config.dsp_ops.resume)
			ret = dsp_priv->dsp_config.dsp_ops.resume();
	}

	HI64XX_DSP_INFO("resume-\n");

	return ret;
}

int hi64xx_hifi_misc_init(struct snd_soc_codec *codec,
				struct hi64xx_resmgr *resmgr,
				struct hi64xx_irq *irqmgr,
				struct hi64xx_dsp_config *dsp_config)
{
	int ret = 0;

	IN_FUNCTION;

	dsp_priv = kzalloc(sizeof(*dsp_priv), GFP_KERNEL);
	if(!dsp_priv){
		pr_err("%s : kzalloc error!\n", __FUNCTION__);
		return -ENOMEM;
	}

	dsp_priv->p_irq = irqmgr;
	dsp_priv->resmgr = resmgr;
	dsp_priv->codec = codec;
	mutex_init(&dsp_priv->peri_mutex);

	memcpy(&dsp_priv->dsp_config, dsp_config, sizeof(*dsp_config));

#ifdef CONFIG_PM
	hi64xx_sr_nb.notifier_call = hi64xx_sr_event;
	hi64xx_sr_nb.priority = -1;
	if (register_pm_notifier(&hi64xx_sr_nb)) {
		HI64XX_DSP_ERROR(" Failed to register for PM events\n");
		goto err_exit;
	}
#endif

	hi64xx_reboot_nb.notifier_call = hi64xx_reboot_notifier;
	hi64xx_reboot_nb.priority = -1;
	if (register_reboot_notifier(&hi64xx_reboot_nb)) {
		HI64XX_DSP_ERROR(" Failed to register for reboot notifier\n");
		goto err_exit;
	}

	dsp_priv->resmgr_nb.notifier_call = hi64xx_resmgr_notifier;
	dsp_priv->resmgr_nb.priority = -1;
	if (hi64xx_resmgr_register_notifier(dsp_priv->resmgr, &dsp_priv->resmgr_nb)) {
		HI64XX_DSP_ERROR(" Failed to register for resmgr notifier\n");
		goto err_exit;
	}

	ret = hi64xx_irq_request_irq(dsp_priv->p_irq, dsp_priv->dsp_config.vld_irq_num,
				hi64xx_msg_irq_handler,
				"cmd_valid", dsp_priv);
	if (0 > ret) {
		HI64XX_DSP_ERROR("request_irq failed! \n");
		goto err_exit;
	}

	dsp_priv->is_watchdog_coming = false;
	dsp_priv->is_sync_write_timeout = false;

	ret = hi64xx_irq_request_irq(dsp_priv->p_irq, dsp_priv->dsp_config.wtd_irq_num,
				hi64xx_wtd_irq_handler,
				"wd_irq", dsp_priv);
	if (0 > ret) {
		HI64XX_DSP_ERROR("request_irq failed! \n");
		goto err_exit;
	}


	dsp_priv->dsp_pwron_done = HIFI_STATE_UNINIT;
	dsp_priv->dsp_pllswitch_done = 0;
	dsp_priv->sync_msg_ret = 0;
	dsp_priv->uart_mode = UART_MODE_OFF;

	init_waitqueue_head(&dsp_priv->dsp_pwron_wq);
	init_waitqueue_head(&dsp_priv->dsp_pllswitch_wq);
	init_waitqueue_head(&dsp_priv->sync_msg_wq);

	mutex_init(&dsp_priv->msg_mutex);
	mutex_init(&dsp_priv->state_mutex);

	misc_register(&hi64xx_hifi_misc_device);

#ifdef ENABLE_HI6402_HIFI_DEBUG
	hi64xx_create_procfs();
#endif

	OUT_FUNCTION;

	return 0;

err_exit:
	hi64xx_hifi_misc_deinit();
	return -ENOENT;
}
EXPORT_SYMBOL(hi64xx_hifi_misc_init);

void hi64xx_hifi_misc_deinit(void)
{
	IN_FUNCTION;

	if (!dsp_priv)
		return;

#ifdef CONFIG_PM
	unregister_pm_notifier(&hi64xx_sr_nb);
#endif

	unregister_reboot_notifier(&hi64xx_reboot_nb);

	hi64xx_resmgr_unregister_notifier(dsp_priv->resmgr, &dsp_priv->resmgr_nb);

	if (dsp_priv->dsp_config.dsp_ops.deinit)
		dsp_priv->dsp_config.dsp_ops.deinit();

	(void)misc_deregister(&hi64xx_hifi_misc_device);

	if (dsp_priv->p_irq) {
		hi64xx_irq_free_irq(dsp_priv->p_irq, dsp_priv->dsp_config.vld_irq_num, dsp_priv);

		hi64xx_irq_free_irq(dsp_priv->p_irq, dsp_priv->dsp_config.wtd_irq_num, dsp_priv);
	}

	mutex_destroy(&dsp_priv->peri_mutex);

	kfree(dsp_priv);

	dsp_priv = NULL;

#ifdef ENABLE_HI6402_HIFI_DEBUG
	hi64xx_remove_procfs();
#endif

	OUT_FUNCTION;
}
EXPORT_SYMBOL(hi64xx_hifi_misc_deinit);

MODULE_DESCRIPTION("hi64xx hifi misc driver");
MODULE_LICENSE("GPL");
