/*
 * hifi misc driver.
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/kthread.h>
#include <linux/semaphore.h>
#include <linux/miscdevice.h>
#include <linux/platform_device.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/gfp.h>
#include <linux/wakelock.h>
#include <linux/errno.h>
#include <linux/of_address.h>
#include <linux/mm.h>
#include <linux/io.h>
#include <linux/syscalls.h>
#include <linux/unistd.h>
#include <linux/completion.h>
#include <linux/suspend.h>
#include <linux/reboot.h>
#include <linux/delay.h>

#include <asm/memory.h>
/*lint -e451*/
#include <asm/types.h>
/*lint +e451*/
#include <asm/io.h>

#ifdef CONFIG_ARM64
#include <linux/compat.h>
#endif

#include "hifi_lpp.h"
#include "audio_hifi.h"
#include "drv_mailbox_msg.h"
#include "bsp_drv_ipc.h"
#include "hifi_om.h"
#include <dsm/dsm_pub.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define DTS_COMP_HIFIDSP_NAME "hisilicon,k3hifidsp"
#define SEND_MSG_TO_HIFI mailbox_send_msg
#define RETRY_COUNT	3

static DEFINE_SEMAPHORE(s_misc_sem);

LIST_HEAD(recv_sync_work_queue_head);
LIST_HEAD(recv_proc_work_queue_head);

/* 3mic add for reset hi6402 audio dp clk */
struct multi_mic {
	struct workqueue_struct *reset_audio_dp_clk_wq;
	struct work_struct reset_audio_dp_clk_work;
	unsigned int audio_clk_state;
	struct list_head cmd_queue;
	spinlock_t cmd_lock;  /* protects cmd queue */
};

struct hifi_misc_priv {
	spinlock_t	recv_sync_lock;
	spinlock_t	recv_proc_lock;

	struct completion	completion;
	wait_queue_head_t	proc_waitq;

	int	wait_flag;
	unsigned int	sn;

	struct wake_lock	hifi_misc_wakelock;

	unsigned char	*hifi_priv_base_virt;
	unsigned char	*hifi_priv_base_phy;

	struct device	*dev;

#ifdef MULTI_MIC
	struct multi_mic multi_mic_ctrl;

#endif
};
static struct hifi_misc_priv s_misc_data;

static struct notifier_block s_hifi_sr_nb;
static struct notifier_block s_hifi_reboot_nb;
static atomic_t volatile s_hifi_in_suspend = ATOMIC_INIT(0);
static atomic_t volatile s_hifi_in_saving = ATOMIC_INIT(0);

void sochifi_watchdog_send_event(void)
{
	int retval = 0;
	char *envp[2] = {"hifi_watchdog", NULL};

	can_reset_system();

	logi("soc hifi watchdog coming, now reset mediaserver \n");
	retval = kobject_uevent_env(&s_misc_data.dev->kobj, KOBJ_CHANGE, envp);
	if (retval) {
		loge("send uevent failed, retval: %d\n", retval);
	}

	return;
}

static void hifi_misc_msg_info(unsigned short _msg_id)
{
	HIFI_MSG_ID msg_id =  (HIFI_MSG_ID)_msg_id;

	switch(msg_id) {
		case ID_AP_AUDIO_PLAY_START_REQ:
			logi("MSG: ID_AP_AUDIO_PLAY_START_REQ.\n");
			break;
		case ID_AUDIO_AP_PLAY_START_CNF:
			logi("MSG: ID_AUDIO_AP_PLAY_START_CNF.\n");
			break;
		case ID_AP_AUDIO_PLAY_PAUSE_REQ:
			logi("MSG: ID_AP_AUDIO_PLAY_PAUSE_REQ.\n");
			break;
		case ID_AUDIO_AP_PLAY_PAUSE_CNF:
			logi("MSG: ID_AUDIO_AP_PLAY_PAUSE_CNF.\n");
			break;
		case ID_AUDIO_AP_PLAY_DONE_IND:
			logi("MSG: ID_AUDIO_AP_PLAY_DONE_IND.\n");
			break;
		case ID_AP_AUDIO_PLAY_UPDATE_BUF_CMD:
			logi("MSG: ID_AP_AUDIO_PLAY_UPDATE_BUF_CMD.\n");
			break;
		case ID_AP_AUDIO_PLAY_WAKEUPTHREAD_REQ:
			logi("MSG: ID_AP_AUDIO_PLAY_WAKEUPTHREAD_REQ.\n");
			break;
		case ID_AP_AUDIO_PLAY_QUERY_TIME_REQ:
			logd("MSG: ID_AP_AUDIO_PLAY_QUERY_TIME_REQ.\n");
			break;
		case ID_AUDIO_AP_PLAY_QUERY_TIME_CNF:
			logd("MSG: ID_AUDIO_AP_PLAY_QUERY_TIME_CNF.\n");
			break;
		case ID_AP_AUDIO_PLAY_QUERY_STATUS_REQ:
			logd("MSG: ID_AP_AUDIO_PLAY_QUERY_STATUS_REQ.\n");
			break;
		case ID_AUDIO_AP_PLAY_QUERY_STATUS_CNF:
			logd("MSG: ID_AUDIO_AP_PLAY_QUERY_STATUS_CNF.\n");
			break;
		case ID_AP_AUDIO_PLAY_SEEK_REQ:
			logi("MSG: ID_AP_AUDIO_PLAY_SEEK_REQ.\n");
			break;
		case ID_AUDIO_AP_PLAY_SEEK_CNF:
			logi("MSG: ID_AUDIO_AP_PLAY_SEEK_CNF.\n");
			break;
		case ID_AP_AUDIO_PLAY_SET_VOL_CMD:
			logi("MSG: ID_AP_AUDIO_PLAY_SET_VOL_CMD.\n");
			break;
		case ID_AP_HIFI_ENHANCE_START_REQ:
			logi("MSG: ID_AP_HIFI_ENHANCE_START_REQ.\n");
			break;
		case ID_HIFI_AP_ENHANCE_START_CNF:
			logi("MSG: ID_HIFI_AP_ENHANCE_START_CNF.\n");
			break;
		case ID_AP_HIFI_ENHANCE_STOP_REQ:
			logi("MSG: ID_AP_HIFI_ENHANCE_STOP_REQ.\n");
			break;
		case ID_HIFI_AP_ENHANCE_STOP_CNF:
			logi("MSG: ID_HIFI_AP_ENHANCE_STOP_CNF.\n");
			break;
		case ID_AP_HIFI_ENHANCE_SET_DEVICE_REQ:
			logi("MSG: ID_AP_HIFI_ENHANCE_SET_DEVICE_REQ.\n");
			break;
		case ID_HIFI_AP_ENHANCE_SET_DEVICE_CNF:
			logi("MSG: ID_HIFI_AP_ENHANCE_SET_DEVICE_CNF.\n");
			break;
		case ID_AP_AUDIO_ENHANCE_SET_DEVICE_IND:
			logi("MSG: ID_AP_AUDIO_ENHANCE_SET_DEVICE_IND.\n");
			break;
		case ID_AP_AUDIO_MLIB_SET_PARA_IND:
			logi("MSG: ID_AP_AUDIO_MLIB_SET_PARA_IND.\n");
			break;
		case ID_AP_HIFI_VOICE_RECORD_START_CMD:
			logi("MSG: ID_AP_HIFI_VOICE_RECORD_START_CMD.\n");
			break;
		case ID_AP_HIFI_VOICE_RECORD_STOP_CMD:
			logi("MSG: ID_AP_HIFI_VOICE_RECORD_STOP_CMD.\n");
			break;
		case ID_AP_VOICEPP_START_REQ:
			logi("MSG: ID_AP_VOICEPP_START_REQ .\n");
			break;
		case ID_VOICEPP_AP_START_CNF:
			logi("MSG: ID_VOICEPP_AP_START_CNF .\n");
			break;
		case ID_AP_VOICEPP_STOP_REQ:
			logi("MSG: ID_AP_VOICEPP_STOP_REQ .\n");
			break;
		case ID_VOICEPP_AP_STOP_CNF:
			logi("MSG: ID_VOICEPP_AP_STOP_CNF .\n");
			break;
		case ID_AP_VOICEPP_SET_DEVICE_REQ:
			logi("MSG: ID_AP_VOICEPP_SET_DEVICE_REQ .\n");
			break;
		case ID_VOICEPP_AP_SET_DEVICE_CNF:
			logi("MSG: ID_VOICEPP_AP_SET_DEVICE_CNF .\n");
			break;
		case ID_AP_VOICEPP_SET_WB_REQ:
			logi("MSG: ID_AP_VOICEPP_SET_WB_REQ .\n");
			break;
		case ID_VOICEPP_AP_SET_WB_CNF:
			logi("MSG: ID_VOICEPP_AP_SET_WB_CNF .\n");
			break;
		case ID_AP_AUDIO_SET_DTS_ENABLE_CMD:
			logi("MSG: ID_AP_AUDIO_SET_DTS_ENABLE_CMD.\n");
			break;
		case ID_AP_AUDIO_SET_DTS_DEV_CMD:
			logi("MSG: ID_AP_AUDIO_SET_DTS_DEV_CMD.\n");
			break;
		case ID_AP_AUDIO_SET_DTS_GEQ_CMD:
			logi("MSG: ID_AP_AUDIO_SET_DTS_GEQ_CMD.\n");
			break;
		case ID_AP_AUDIO_SET_DTS_GEQ_ENABLE_CMD:
			logi("MSG: ID_AP_AUDIO_SET_DTS_GEQ_ENABLE_CMD.\n");
			break;
		case ID_AP_AUDIO_RECORD_PCM_HOOK_CMD:
			logi("MSG: ID_AP_AUDIO_RECORD_PCM_HOOK_CMD.\n");
			break;
		case ID_AP_AUDIO_CMD_SET_SOURCE_CMD:
			logi("MSG: ID_AP_AUDIO_CMD_SET_SOURCE_CMD.\n");
			break;
		case ID_AP_AUDIO_CMD_SET_DEVICE_CMD:
			logi("MSG: ID_AP_AUDIO_CMD_SET_DEVICE_CMD.\n");
			break;
		case ID_AP_AUDIO_CMD_SET_MODE_CMD:
			logi("MSG: ID_AP_AUDIO_CMD_SET_MODE_CMD.\n");
			break;
		case ID_AP_AUDIO_CMD_SET_ANGLE_CMD:
			logi("MSG: ID_AP_AUDIO_CMD_SET_ANGLE_CMD.\n");
			break;
		case ID_AP_AUDIO_ROUTING_COMPLETE_REQ:
			logi("MSG: ID_AP_AUDIO_ROUTING_COMPLETE_REQ.\n");
			break;
		case ID_AUDIO_AP_FADE_OUT_REQ:
			logi("MSG: ID_AUDIO_AP_FADE_OUT_REQ.\n");
			break;
		case ID_AUDIO_AP_OM_DUMP_CMD:
			logi("MSG: ID_AUDIO_AP_OM_DUMP_CMD.\n");
			break;
		default:
			logw("MSG: Not defined msg id: 0x%x.\n", msg_id);
			break;
	}
	return;
}

/*****************************************************************************
 函 数 名  : hifi_misc_async_write
 功能描述  : Hifi MISC 设备异步发送接口，将异步消息发给Hifi，非阻塞接口
 输入参数  :
			 unsigned char *arg  :需要下发的数据buff指针
			 unsigned int len	 :下发的数据长度
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年8月1日
	作	  者   : 夏青 00195127
	修改内容   : 新生成函数

*****************************************************************************/
static int hifi_misc_async_write(unsigned char *arg, unsigned int len)
{
	int ret = OK;

	IN_FUNCTION;

	if (NULL == arg) {
		loge("input arg is NULL.\n");
		ret = ERROR;
		goto END;
	}

	/*调用核间通信接口发送数据*/
	ret = SEND_MSG_TO_HIFI(MAILBOX_MAILCODE_ACPU_TO_HIFI_MISC, arg, len);
	if (OK != ret) {
		loge("msg send to hifi fail,ret is %d.\n", ret);
		ret = ERROR;
		goto END;
	}

END:
	OUT_FUNCTION;
	return ret;
}

/*****************************************************************************
 函 数 名  : hifi_misc_sync_write
 功能描述  : Hifi MISC 设备同步发送接口，将同步消息发给Hifi，阻塞接口
 输入参数  :
			 unsigned char	*buff  :需要下发的数据buff指针
			 unsigned int len	  :下发的数据长度
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年8月1日
	作	  者   : 夏青 00195127
	修改内容   : 新生成函数

*****************************************************************************/
static int hifi_misc_sync_write(unsigned char  *buff, unsigned int len)
{
	int ret = OK;

	IN_FUNCTION;

	if (NULL == buff) {
		loge("input arg is NULL.\n");
		ret = ERROR;
		goto END;
	}

	INIT_COMPLETION(s_misc_data.completion);

	/*调用核间通信接口发送数据，得到返回值ret*/
	ret = SEND_MSG_TO_HIFI(MAILBOX_MAILCODE_ACPU_TO_HIFI_MISC, buff, len);
	if (OK != ret) {
		loge("msg send to hifi fail,ret is %d.\n", ret);
		ret = ERROR;
		goto END;
	}

#ifndef PLATFORM_FPGA
	ret = wait_for_completion_timeout(&s_misc_data.completion, msecs_to_jiffies(2000));
#else
    ret = wait_for_completion_timeout(&s_misc_data.completion, msecs_to_jiffies(10000));  //AUSTIN PLATFORM_FPGA
#endif

	s_misc_data.sn++;
	if (unlikely(s_misc_data.sn & 0x10000000)){
		s_misc_data.sn = 0;
	}

	if (!ret) {
		loge("wait completion timeout.\n");
		hifi_dump_panic_log();
		ret = ERROR;
		goto END;
	} else {
		ret = OK;
	}

END:
	OUT_FUNCTION;
	return ret;
}

static int hifi_misc_send_hifi_msg_async(struct common_hifi_cmd* cmd)
{
	int ret = OK;
	logi("send msg: 0x%x to hifi !\n", cmd->msg_id);
	ret = (unsigned int)mailbox_send_msg(MAILBOX_MAILCODE_ACPU_TO_HIFI_MISC, cmd, sizeof(struct common_hifi_cmd));
	if (OK != ret) {
		loge("msg: 0x%x send to hifi fail, ret is %d.\n", cmd->msg_id, ret);
	}

	return ret;
}

static bool hifi_misc_local_process(unsigned short _msg_id)
{
	bool ret = false;
	HIFI_MSG_ID msg_id =  (HIFI_MSG_ID)_msg_id;

	switch(msg_id) {
	case ID_AUDIO_AP_OM_DUMP_CMD:
	case ID_AUDIO_AP_FADE_OUT_REQ:
	case ID_AUDIO_AP_DP_CLK_EN_IND:
	case ID_AUDIO_AP_VOICE_BSD_PARAM_CMD:
	case ID_AUDIO_AP_OM_CMD:
		ret = true;
		break;
	default:
		break;
	}

	return ret;
}

static void hifi_misc_mesg_process(void *cmd)
{
	unsigned int cmd_id = 0;
	struct common_hifi_cmd * common_cmd = NULL;
	struct dp_clk_request *dp_clk_cmd = NULL;
	struct hifi_om_ap_data *hifi_om_rev_data = NULL;

	BUG_ON(NULL == cmd);

	hifi_om_rev_data = (struct hifi_om_ap_data *)cmd;
	common_cmd =(struct common_hifi_cmd *)cmd;
	cmd_id = *(unsigned short*)cmd;

	switch (cmd_id) {
	case ID_AUDIO_AP_OM_CMD:
		hifi_om_rev_data_handle(HIFI_OM_WORK_AUDIO_OM_DETECTION, hifi_om_rev_data->data,
			hifi_om_rev_data->data_len);
		break;
	case ID_AUDIO_AP_VOICE_BSD_PARAM_CMD:
		hifi_om_rev_data_handle(HIFI_OM_WORK_VOICE_BSD, hifi_om_rev_data->data,
			hifi_om_rev_data->data_len);
		break;
	case ID_AUDIO_AP_OM_DUMP_CMD:
		logi("hifi notify to dump hifi log, hifi errtype: %d.\n", common_cmd->value);
		break;
#ifdef MULTI_MIC
	case ID_AUDIO_AP_DP_CLK_EN_IND:
	case ID_AUDIO_AP_FADE_OUT_REQ:
		dp_clk_cmd = (struct dp_clk_request *)kmalloc(sizeof(struct dp_clk_request), GFP_ATOMIC);
		if (!dp_clk_cmd) {
			loge("malloc fail\n");
			break;
		}
		memset(dp_clk_cmd, 0, sizeof(struct dp_clk_request));

		logi("multi mic cmd: 0x%x.\n", common_cmd->msg_id);
		memcpy(&(dp_clk_cmd->dp_clk_msg), common_cmd, sizeof(struct common_hifi_cmd));

		spin_lock_bh(&(s_misc_data.multi_mic_ctrl.cmd_lock));
		list_add_tail(&dp_clk_cmd->dp_clk_node, &(s_misc_data.multi_mic_ctrl.cmd_queue));
		spin_unlock_bh(&(s_misc_data.multi_mic_ctrl.cmd_lock));
		wake_lock_timeout(&s_misc_data.hifi_misc_wakelock, HZ/2);
		if (queue_work(s_misc_data.multi_mic_ctrl.reset_audio_dp_clk_wq,
				&s_misc_data.multi_mic_ctrl.reset_audio_dp_clk_work))
			logw("cmd 0x%x no trigger queue work\n", common_cmd->msg_id);
		break;
#endif
	default:
		break;
	}

	return;
}
/*****************************************************************************
 函 数 名  : hifi_misc_handle_mail
 功能描述  : Hifi MISC 设备双核通信接收中断处理函数
			约定收到HIIF邮箱消息的首4个字节是MSGID
 输入参数  : void *usr_para			: 注册时传递的参数
			 void *mail_handle			: 邮箱数据参数
			 unsigned int mail_len		: 邮箱数据长度
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年8月1日
	作	  者   : 夏青 00195127
	修改内容   : 新生成函数

*****************************************************************************/
static void hifi_misc_handle_mail(void *usr_para, void *mail_handle, unsigned int mail_len)
{
	unsigned int ret_mail			= 0;
	struct recv_request *recv = NULL;
	HIFI_CHN_CMD *cmd_para = NULL;
	void *recmsg = NULL;

	IN_FUNCTION;

	if (NULL == mail_handle) {
		loge("mail_handle is NULL.\n");
		goto END;
	}

	if (mail_len >= MAIL_LEN_MAX || mail_len <= SIZE_CMD_ID) {
		loge("mail_len is invalid: %u(>= 512 or <= 8)\n", mail_len);
		goto END;
	}

	recv = (struct recv_request *)kmalloc(sizeof(struct recv_request), GFP_ATOMIC);
	if (NULL == recv)
	{
		loge("recv kmalloc failed.\n");
		goto ERR;
	}
	memset(recv, 0, sizeof(struct recv_request));

	/* 设定SIZE */
	recv->rev_msg.mail_buff_len = mail_len;
	/* 分配总的空间 */
	recv->rev_msg.mail_buff = (unsigned char *)kmalloc(mail_len, GFP_ATOMIC);
	if (NULL == recv->rev_msg.mail_buff)
	{
		loge("recv->rev_msg.mail_buff kmalloc failed.\n");
		goto ERR;
	}
	memset(recv->rev_msg.mail_buff, 0, mail_len);

	/* 将剩余内容copy透传到buff中 */
	ret_mail = mailbox_read_msg_data(mail_handle, (char*)(recv->rev_msg.mail_buff), (unsigned int *)(&(recv->rev_msg.mail_buff_len)));

	if ((ret_mail != MAILBOX_OK) || (recv->rev_msg.mail_buff_len <= 0)) {
		loge("Empty point or data length error! ret=0x%x, mail_size: %d.\n", (unsigned int)ret_mail, recv->rev_msg.mail_buff_len);
		goto ERR;
	}

	logd("ret_mail=%d, mail_buff_len=%d, msgID=0x%x.\n", ret_mail, recv->rev_msg.mail_buff_len,
		 *((unsigned int *)(recv->rev_msg.mail_buff + mail_len - SIZE_CMD_ID)));

	/* 约定，前4个字节是cmd_id */
	cmd_para   = (HIFI_CHN_CMD *)(recv->rev_msg.mail_buff + mail_len - SIZE_CMD_ID);
	recmsg = (void*)recv->rev_msg.mail_buff;
	/* 赋予不同的接收指针，由接收者释放分配空间 */
	if (HIFI_CHN_SYNC_CMD == cmd_para->cmd_type) {
		if (s_misc_data.sn == cmd_para->sn) {
			spin_lock_bh(&s_misc_data.recv_sync_lock);
			list_add_tail(&recv->recv_node, &recv_sync_work_queue_head);
			spin_unlock_bh(&s_misc_data.recv_sync_lock);
			complete(&s_misc_data.completion);
		} else {
			loge("s_misc_data.sn !== cmd_para->sn: %d, %d.\n", s_misc_data.sn, cmd_para->sn);
		}
		goto END;
	} else if ((HIFI_CHN_READNOTICE_CMD == cmd_para->cmd_type) && (ACPU_TO_HIFI_ASYNC_CMD == cmd_para->sn)) {
		if (ID_AUDIO_AP_PLAY_DONE_IND == *((unsigned short *)recmsg)) {
			/* only mesg ID_AUDIO_AP_PLAY_DONE_IND lock 5s */
			wake_lock_timeout(&s_misc_data.hifi_misc_wakelock, 5*HZ);
		}

		if(hifi_misc_local_process(*(unsigned short*)recmsg)){
			hifi_misc_mesg_process(recmsg);
			goto OUT;
		}

		spin_lock_bh(&s_misc_data.recv_proc_lock);
		list_add_tail(&recv->recv_node, &recv_proc_work_queue_head);
		s_misc_data.wait_flag++;
		spin_unlock_bh(&s_misc_data.recv_proc_lock);
		wake_up(&s_misc_data.proc_waitq);
		goto END;
	} else {
		loge("unknown msg comed from hifi .\n");
	}

ERR:
OUT:
	if (recv) {
		if (recv->rev_msg.mail_buff) {
			kfree(recv->rev_msg.mail_buff);
		}
		kfree(recv);
	}

END:
	OUT_FUNCTION;

	return;
}

/*****************************************************************************
 函 数 名  : hifi_dsp_get_input_param
 功能描述  : 获取用户空间入参，并转换为内核空间入参
 输入参数  : usr_para_size，用户空间入参SIZE
			usr_para_addr，用户空间入参地址
 输出参数  : krn_para_size，转换后的内核空间入参SIZE
			krn_para_addr，转换后的内核空间入参地址
 返 回 值  : OK / ERROR
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年3月26日
	作	  者   : s00212991
	修改内容   : 新生成函数

*****************************************************************************/
static int hifi_dsp_get_input_param(unsigned int usr_para_size, void *usr_para_addr,
									unsigned int *krn_para_size, void **krn_para_addr)
{
	void *para_in = NULL;
	unsigned int para_size_in = 0;

	IN_FUNCTION;

	/*获取arg入参*/
	para_size_in = usr_para_size + SIZE_CMD_ID;

	/* 限制分配空间 */
	if ((para_size_in > SIZE_LIMIT_PARAM) || (para_size_in <= SIZE_CMD_ID)) {
		loge("para_size_in(%u) exceed LIMIT(%u/%u).\n", para_size_in, SIZE_CMD_ID, SIZE_LIMIT_PARAM);
		goto ERR;
	}

	para_in = kzalloc(para_size_in, GFP_KERNEL);
	if (NULL == para_in) {
		loge("kzalloc fail.\n");
		goto ERR;
	}

	if (NULL != usr_para_addr) {
		if (copy_from_user(para_in , usr_para_addr, usr_para_size)) {
			loge("copy_from_user fail.\n");
			goto ERR;
		}
	} else {
		loge("usr_para_addr is null no user data.\n");
		goto ERR;
	}

	/* 设置出参 */
	*krn_para_size = para_size_in;
	*krn_para_addr = para_in;

	hifi_misc_msg_info(*(unsigned short*)para_in);

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

/*****************************************************************************
 函 数 名  : hifi_dsp_get_input_param_free
 功能描述  : 释放分配的内核空间
 输入参数  : krn_para_addr，待释放的内核空间地址
 输出参数  : 无
 返 回 值  : OK / ERROR
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年3月26日
	作	  者   : s00212991
	修改内容   : 新生成函数

*****************************************************************************/
static void hifi_dsp_get_input_param_free(void **krn_para_addr)
{
	IN_FUNCTION;

	if (*krn_para_addr != NULL) {
		kfree(*krn_para_addr);
		*krn_para_addr = NULL;
	} else {
		loge("krn_para_addr to free is NULL.\n");
	}

	OUT_FUNCTION;
	return;
}

/*****************************************************************************
 函 数 名  : hifi_dsp_get_output_param
 功能描述  : 内核空间出参转换为用户空间出参
 输入参数  : krn_para_size，转换后的内核空间出参SIZE
			krn_para_addr，转换后的内核空间出参地址
 输出参数  : usr_para_size，用户空间出参SIZE
			usr_para_addr，用户空间出参地址
 返 回 值  : OK / ERROR
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年3月26日
	作	  者   : s00212991
	修改内容   : 新生成函数

*****************************************************************************/
static int hifi_dsp_get_output_param(unsigned int krn_para_size, void *krn_para_addr,
									 unsigned int *usr_para_size, void __user *usr_para_addr)
{
	int ret			= OK;
	void __user *para_to = NULL;
	unsigned int para_n = 0;

	IN_FUNCTION;

	/* 入参判定 */
	if (NULL == krn_para_addr) {
		loge("krn_para_addr is NULL.\n");
		ret = -EINVAL;
		goto END;
	}

	/* 入参判定 */
	if ((NULL == usr_para_addr) || (NULL == usr_para_size)) {
		loge("usr_size_p=0x%p, usr_addr=0x%p.\n", usr_para_size, usr_para_addr);
		ret = -EINVAL;
		goto END;
	}

	para_to = usr_para_addr;
	para_n = krn_para_size;
	if (para_n > SIZE_LIMIT_PARAM) {
		loge("para_n exceed limit (%d / %d).\n", para_n, SIZE_LIMIT_PARAM);
		ret = -EINVAL;
		goto END;
	}

	if (para_n > *usr_para_size) {
		loge("para_n exceed usr_size(%d / %d).\n", para_n, *usr_para_size);
		ret = -EINVAL;
		goto END;
	}

	/* Copy data from kernel space to user space
		to, from, n */
	ret = copy_to_user(para_to, krn_para_addr, para_n);
	if (OK != ret) {
		loge("copy_to_user fail, ret is %d.\n", ret);
		ret = ERROR;
		goto END;
	}

	*usr_para_size = para_n;
	hifi_misc_msg_info(*(unsigned short*)krn_para_addr);

END:
	OUT_FUNCTION;
	return ret;
}

/*****************************************************************************
 函 数 名  : hifi_dsp_async_cmd
 功能描述  : Hifi MISC IOCTL异步命令处理函数
 输入参数  : unsigned long arg : ioctl的入参
 输出参数  : 无
 返 回 值  : 成功:OK 失败:BUSY
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2013年3月18日
	作	  者   : 石旺来 00212991
	修改内容   : 新生成函数

*****************************************************************************/
static int hifi_dsp_async_cmd(unsigned long arg)
{
	int ret = OK;
	struct misc_io_async_param param;
	void *para_krn_in = NULL;
	unsigned int para_krn_size_in = 0;
	HIFI_CHN_CMD *cmd_para = NULL;
	void* para_addr_in = NULL;

	IN_FUNCTION;

	if (copy_from_user(&param,(void*) arg, sizeof(struct misc_io_async_param))) {
		loge("copy_from_user fail.\n");
		ret = ERROR;
		goto END;
	}

	para_addr_in = INT_TO_ADDR(param.para_in_l,param.para_in_h);
	/*获取arg入参*/
	ret = hifi_dsp_get_input_param(param.para_size_in, para_addr_in,
								   &para_krn_size_in, &para_krn_in);
	if (OK != ret) {
		loge("get ret=%d.\n", ret);
		goto END;
	}
	/* add cmd id and sn  */
	cmd_para = (HIFI_CHN_CMD *)(para_krn_in+para_krn_size_in-SIZE_CMD_ID);
	cmd_para->cmd_type = HIFI_CHN_SYNC_CMD;
	cmd_para->sn = ACPU_TO_HIFI_ASYNC_CMD;

	/*邮箱发送至HIFI, 异步*/
	ret = hifi_misc_async_write(para_krn_in, para_krn_size_in);
	if (OK != ret) {
		loge("async_write ret=%d.\n", ret);
		goto END;
	}

END:
	hifi_dsp_get_input_param_free(&para_krn_in);
	OUT_FUNCTION;
	return ret;
}

/*****************************************************************************
 函 数 名  : hifi_dsp_sync_cmd
 功能描述  : Hifi MISC IOCTL同步命令处理函数
 输入参数  : unsigned long arg : ioctl的入参
 输出参数  : 无
 返 回 值  : 成功:OK 失败:BUSY
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2013年3月18日
	作	  者   : 石旺来 00212991
	修改内容   : 新生成函数

*****************************************************************************/
static int hifi_dsp_sync_cmd(unsigned long arg)
{
	int ret = OK;
	struct misc_io_sync_param param;
	void *para_krn_in = NULL;
	unsigned int para_krn_size_in = 0;
	HIFI_CHN_CMD *cmd_para = NULL;
	void __user *para_addr_in	= NULL;
	void __user *para_addr_out = NULL;
	struct recv_request *recv = NULL;

	IN_FUNCTION;

	if (copy_from_user(&param,(void*) arg, sizeof(struct misc_io_sync_param))) {
		loge("copy_from_user fail.\n");
		ret = ERROR;
		goto END;
	}
	logd("para_size_in=%d.\n", param.para_size_in);

	para_addr_in   = INT_TO_ADDR(param.para_in_l ,param.para_in_h);
	para_addr_out  = INT_TO_ADDR(param.para_out_l,param.para_out_h);
	/*获取arg入参*/
	ret = hifi_dsp_get_input_param(param.para_size_in, para_addr_in,
						&para_krn_size_in, &para_krn_in);
	if (OK != ret) {
		loge("hifi_dsp_get_input_param fail: ret=%d.\n", ret);
		goto END;
	}

	/* add cmd id and sn  */
	cmd_para = (HIFI_CHN_CMD *)(para_krn_in+para_krn_size_in-SIZE_CMD_ID);
	cmd_para->cmd_type = HIFI_CHN_SYNC_CMD;

	cmd_para->sn = s_misc_data.sn;

	/*邮箱发送至HIFI, 同步*/
	ret = hifi_misc_sync_write(para_krn_in, para_krn_size_in);
	if (OK != ret) {
		loge("hifi_misc_sync_write ret=%d.\n", ret);
		goto END;
	}

	/*将获得的rev_msg信息填充到出参arg*/
	spin_lock_bh(&s_misc_data.recv_sync_lock);

	if (!list_empty(&recv_sync_work_queue_head)) {
		recv = list_entry(recv_sync_work_queue_head.next, struct recv_request, recv_node);
		ret = hifi_dsp_get_output_param(recv->rev_msg.mail_buff_len- SIZE_CMD_ID, recv->rev_msg.mail_buff,
						&param.para_size_out, para_addr_out);
		if (OK != ret) {
			loge("get_out ret=%d.\n", ret);
		}

		list_del(&recv->recv_node);
		kfree(recv->rev_msg.mail_buff);
		kfree(recv);
		recv = NULL;
	}
	spin_unlock_bh(&s_misc_data.recv_sync_lock);

	if (copy_to_user((void*)arg, &param, sizeof(struct misc_io_sync_param))) {
		loge("copy_to_user fail.\n");
		ret = ERROR;
		goto END;
	}

END:
	/*释放krn入参*/
	hifi_dsp_get_input_param_free(&para_krn_in);

	OUT_FUNCTION;
	return ret;
}

/*****************************************************************************
 函 数 名  : hifi_dsp_get_phys_cmd
 功能描述  : Hifi MISC IOCTL获取物理地址
 输入参数  : unsigned long arg : ioctl的入参
 输出参数  : 无
 返 回 值  : 成功:OK 失败:BUSY
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2013年3月18日
	作	  者   : 石旺来 00212991
	修改内容   : 新生成函数

*****************************************************************************/
static int hifi_dsp_get_phys_cmd(unsigned long arg)
{
	int ret  =	OK;
	struct misc_io_get_phys_param param;
	unsigned long para_addr_in = 0;

	IN_FUNCTION;

	if (copy_from_user(&param,(void*) arg, sizeof(struct misc_io_get_phys_param))) {
		loge("copy_from_user fail.\n");
		OUT_FUNCTION;
		return ERROR;
	}

	switch (param.flag)
	{
		case 0:
			para_addr_in = (unsigned long)s_misc_data.hifi_priv_base_phy;
			param.phys_addr_l = GET_LOW32(para_addr_in);
			param.phys_addr_h = GET_HIG32(para_addr_in);
			logd("para_addr_in = 0x%ld.\n", para_addr_in);
			break;

		default:
			ret = ERROR;
			loge("invalid flag=%d.\n", param.flag);
			break;
	}

	if (copy_to_user((void*)arg, &param, sizeof(struct misc_io_get_phys_param))) {
		loge("copy_to_user fail.\n");
		ret = ERROR;
	}

	OUT_FUNCTION;
	return ret;
}

/*****************************************************************************
 函 数 名  : hifi_dsp_senddata_sync_cmd
 功能描述  : Hifi MISC IOCTL发送数据同步命令处理函数
 输入参数  : unsigned long arg : ioctl的入参
 输出参数  : 无
 返 回 值  : 成功:OK 失败:BUSY
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2013年3月18日
	作	  者   : 石旺来 00212991
	修改内容   : 新生成函数

*****************************************************************************/
static int hifi_dsp_senddata_sync_cmd(unsigned long arg)
{
	loge("this cmd is not supported by now .\n");
	return ERROR;
}

/*****************************************************************************
 函 数 名  : hifi_dsp_wakeup_read_thread
 功能描述  : 唤醒read线程, 返回RESET消息
 输入参数  : unsigned long arg : ioctl的入参
 输出参数  : 无
 返 回 值  : 成功:OK 失败:BUSY
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2014年4月24日
	作	  者   : 张恩忠 00222844
	修改内容   : 新生成函数

*****************************************************************************/
static int hifi_dsp_wakeup_read_thread(unsigned long arg)
{
	struct recv_request *recv = NULL;
	struct misc_recmsg_param *recmsg = NULL;
	unsigned int wake_cmd = (unsigned int)arg;

	recv = (struct recv_request *)kmalloc(sizeof(struct recv_request), GFP_ATOMIC);
	if (NULL == recv)
	{
		loge("recv kmalloc failed.\n");
		return -ENOMEM;
	}
	memset(recv, 0, sizeof(struct recv_request));

	wake_lock_timeout(&s_misc_data.hifi_misc_wakelock, HZ);

	/* 设定SIZE */
	recv->rev_msg.mail_buff_len = sizeof(struct misc_recmsg_param) + SIZE_CMD_ID;

	/* 分配总的空间 */
	recv->rev_msg.mail_buff = (unsigned char *)kmalloc(recv->rev_msg.mail_buff_len, GFP_ATOMIC);
	if (NULL == recv->rev_msg.mail_buff)
	{
		kfree(recv);
		loge("recv->rev_msg.mail_buff kmalloc failed.\n");
		return -ENOMEM;
	}
	memset(recv->rev_msg.mail_buff, 0, recv->rev_msg.mail_buff_len);

	recmsg = (struct misc_recmsg_param *)recv->rev_msg.mail_buff;
	recmsg->msgID = ID_AUDIO_AP_PLAY_DONE_IND;
	recmsg->playStatus = (unsigned short)wake_cmd;

	spin_lock_bh(&s_misc_data.recv_proc_lock);
	list_add_tail(&recv->recv_node, &recv_proc_work_queue_head);
	s_misc_data.wait_flag++;
	spin_unlock_bh(&s_misc_data.recv_proc_lock);

	wake_up(&s_misc_data.proc_waitq);

	return OK;
}

/*****************************************************************************
 函 数 名  : hifi_dsp_write_param
 功能描述  : 将用户态算法参数拷贝到HIFI中
 输入参数  : unsigned long arg : ioctl的入参
 输出参数  : 无
 返 回 值  : 成功:OK 失败:BUSY
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2013年10月24日
	作	  者   : 侯良军 00215385
	修改内容   : 新生成函数

*****************************************************************************/
static int hifi_dsp_write_param(unsigned long arg)
{
	int ret = OK;
	void*		hifi_param_vir_addr = NULL;
	void*		para_addr_in		= NULL;
	void*		para_addr_out		= NULL;
	struct misc_io_sync_param para;

	IN_FUNCTION;

	if (copy_from_user(&para, (void*)arg, sizeof(struct misc_io_sync_param))) {
		loge("copy_from_user fail.\n");
		ret = ERROR;
		goto error1;
	}

	para_addr_in  = INT_TO_ADDR(para.para_in_l ,para.para_in_h);
	para_addr_out = INT_TO_ADDR(para.para_out_l,para.para_out_h);

	hifi_param_vir_addr = (unsigned char*)(s_misc_data.hifi_priv_base_virt + (HIFI_AP_NV_DATA_ADDR - HIFI_BASE_ADDR));

	logd("hifi_param_vir_addr = 0x%p. (*hifi_param_vir_addr) = 0x%x\n",
			hifi_param_vir_addr, (*(int *)hifi_param_vir_addr));

	logd("user addr = 0x%p, size = %d \n", para_addr_in, para.para_size_in);

	if (para.para_size_in != NVPARAM_TOTAL_SIZE) {
		loge("the para_size_in(%u) is not equal to NVPARAM_TOTAL_SIZE(%u). \n",
			para.para_size_in, (unsigned int)(NVPARAM_TOTAL_SIZE));
		ret = ERROR;
		goto error1;
	}

	ret = copy_from_user(hifi_param_vir_addr, (void __user *)para_addr_in, para.para_size_in);

	if (ret != 0) {
		loge("copy data to hifi error! ret = %d.\n", ret);
		ret = ERROR;
	}

	if (para.para_size_out != sizeof(ret)) {
		loge("the para_size_out(%u) is not equal to sizeof(ret)(%zu) \n", para.para_size_out, sizeof(ret));
		ret = ERROR;
		goto error1;
	}

	ret = copy_to_user((void __user *)para_addr_out, &ret, sizeof(ret));
	if (ret) {
		loge("copy data to user fail! ret = %d.\n", ret);
		ret = ERROR;
	}

error1:
	OUT_FUNCTION;
	return ret;
}

/*****************************************************************************
 函 数 名  : hifi_misc_open
 功能描述  : Hifi MISC 设备打开操作
 输入参数  : struct inode *finode  :设备节点信息
			 struct file *fd	:对应设备fd
 输出参数  : 无
 返 回 值  : 成功:OK 失败:BUSY
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年8月1日
	作	  者   : 夏青 00195127
	修改内容   : 新生成函数

*****************************************************************************/
static int hifi_misc_open(struct inode *finode, struct file *fd)
{
	logi("open device.\n");
	return OK;
}

/*****************************************************************************
 函 数 名  : hifi_misc_release
 功能描述  : Hifi MISC 设备不再使用时释放函数
 输入参数  : struct inode *finode  :设备节点信息
			 struct file *fd	:对应设备fd
 输出参数  : 无
 返 回 值  : OK
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年8月1日
	作	  者   : 夏青 00195127
	修改内容   : 新生成函数

*****************************************************************************/
static int hifi_misc_release(struct inode *finode, struct file *fd)
{
	logi("close device.\n");
	return OK;
}

/*****************************************************************************
 函 数 名  : hifi_misc_ioctl
 功能描述  : Hifi MISC 设备提供给上层与设备交互的控制通道接口
 输入参数  : struct file *fd  :对应fd
			 unsigned int cmd	:cmd类型
			 unsigned long arg	:上层传下来的buff地址
 输出参数  : 无
 返 回 值  : 成功:OK 失败:ERROR
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年8月1日
	作	  者   : 夏青 00195127
	修改内容   : 新生成函数

*****************************************************************************/
static long hifi_misc_ioctl(struct file *fd,
							unsigned int cmd,
							unsigned long arg)
{
	int ret = OK;
	void __user *data32 = (void __user *)arg;

	IN_FUNCTION;

	if (!(void __user *)arg) {
		loge("Input buff is NULL.\n");
		OUT_FUNCTION;
		return (long)-EINVAL;
	}

	if (!hifi_is_loaded()) {
		loge("hifi isn't loaded.\n");
		return (long)-EINVAL;
	}

	/*cmd命令处理*/
	switch(cmd) {
		case HIFI_MISC_IOCTL_ASYNCMSG/*异步命令*/:
			logd("ioctl: HIFI_MISC_IOCTL_ASYNCMSG.\n");
			ret = hifi_dsp_async_cmd((unsigned long)data32);
			break;

		case HIFI_MISC_IOCTL_SYNCMSG/*同步命令*/:
			logd("ioctl: HIFI_MISC_IOCTL_SYNCMSG.\n");
			ret = down_interruptible(&s_misc_sem);
			if (ret != 0)
			{
				loge("SYNCMSG wake up by other irq err:%d.\n",ret);
				goto out;
			}
			ret = hifi_dsp_sync_cmd((unsigned long)data32);
			up(&s_misc_sem);
			break;

		case HIFI_MISC_IOCTL_SENDDATA_SYNC/*发送接收数据*/:
			logd("ioctl: HIFI_MISC_IOCTL_SENDDATA_SYNC.\n");
			ret = down_interruptible(&s_misc_sem);
			if (ret != 0)
			{
				loge("SENDDATA_SYNC wake up by other irq err:%d.\n",ret);
				goto out;
			}
			ret = hifi_dsp_senddata_sync_cmd((unsigned long)data32); /*not used by now*/
			up(&s_misc_sem);
			break;

		case HIFI_MISC_IOCTL_GET_PHYS/*获取*/:
			logd("ioctl: HIFI_MISC_IOCTL_GET_PHYS.\n");
			ret = hifi_dsp_get_phys_cmd((unsigned long)data32);
			break;

		case HIFI_MISC_IOCTL_WRITE_PARAMS : /* write algo param to hifi*/
			ret = hifi_dsp_write_param((unsigned long)data32);
			break;

		case HIFI_MISC_IOCTL_DUMP_HIFI:
			logi("ioctl: HIFI_MISC_IOCTL_DUMP_HIFI.\n");
			ret = hifi_dsp_dump_hifi((unsigned long)data32);
			break;

		case HIFI_MISC_IOCTL_DISPLAY_MSG:
			logi("ioctl: HIFI_MISC_IOCTL_DISPLAY_MSG.\n");
			ret = hifi_get_dmesg((void __user *)arg);
			break;

		case HIFI_MISC_IOCTL_GET_VOICE_BSD_PARAM:
			logi("ioctl:HIFI_MISC_IOCTL_GET_VOICE_BSD_PARAM.\n");
			ret = hifi_om_get_voice_bsd_param(data32);
			break;
		case HIFI_MISC_IOCTL_WAKEUP_THREAD:
			logi("ioctl: HIFI_MISC_IOCTL_WAKEUP_THREAD.\n");
			ret = hifi_dsp_wakeup_read_thread((unsigned long)data32);
			break;
		default:
			/*打印无该CMD类型*/
			ret = (long)ERROR;
			loge("ioctl: Invalid CMD =0x%x.\n", (unsigned int)cmd);
			break;
	}
out:
	OUT_FUNCTION;
	return (long)ret;
}

static long hifi_misc_ioctl32(struct file *fd,
							unsigned int cmd,
							unsigned long arg)
{
	void *user_ptr = compat_ptr(arg);
	return hifi_misc_ioctl(fd, cmd, (unsigned long)user_ptr);
}

static int hifi_misc_mmap(struct file *file, struct vm_area_struct *vma)
{
	int ret = OK;
	unsigned long phys_page_addr = 0;
	unsigned long size = 0;
	IN_FUNCTION;

	if (NULL == (void *)vma) {
		logd("input error: vma is NULL\n");
		return ERROR;
	}

	phys_page_addr = (u64)s_misc_data.hifi_priv_base_phy >> PAGE_SHIFT;
	size = ((unsigned long)vma->vm_end - (unsigned long)vma->vm_start);
	logd("vma=0x%p.\n", vma);
	logd("size=%ld, vma->vm_start=%ld, end=%ld.\n", ((unsigned long)vma->vm_end - (unsigned long)vma->vm_start),
		 (unsigned long)vma->vm_start, (unsigned long)vma->vm_end);
	logd("phys_page_addr=0x%ld.\n", (unsigned long)phys_page_addr);

	vma->vm_page_prot = PAGE_SHARED;
	vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);

	if (size > HIFI_MUSIC_DATA_SIZE) {
		size = HIFI_MUSIC_DATA_SIZE;
	}

	ret = remap_pfn_range(vma,
					vma->vm_start,
					phys_page_addr,
					size,
					vma->vm_page_prot);
	if (ret != 0)
	{
		loge("remap_pfn_range ret=%d\n", ret);
		return ERROR;
	}

	OUT_FUNCTION;
	return ret;
}

/*****************************************************************************
 函 数 名  : hifi_misc_proc_read
 功能描述  : 用于将Hifi MISC 设备接收Hifi的消息/数据通过文件的方式递交给用户
			 态
 输入参数  : char *pg	:系统自动填充的用以填充数据的buff，为系统申请的一页
			 char**start  :指示读文件的起始位置，page的偏移量
			 off_t off	  :读文件时page的偏移，当*start存在时，
						   off会被系统忽略而认为*start就是off
			 int count	  :表示读多少字节
			 int *eof	  :读动作是否停止下发标志
			 void *data   :保留为驱动内部使用
 输出参数  : 无
 返 回 值  : 尚未读取部分的长度,如果长度大于4K则返回ERROR
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年8月1日
	作	  者   : 夏青 00195127
	修改内容   : 新生成函数

*****************************************************************************/
static ssize_t hifi_misc_proc_read(struct file *file, char __user *buf,
								   size_t count, loff_t *ppos)
{
	static unsigned int len = 0;
	static int retry_cnt = 0;
	static char *to_user_buf = NULL;
	int ret = -EAGAIN;
	struct recv_request *recv = NULL;
	struct misc_recmsg_param *recmsg = NULL;

	IN_FUNCTION;

	if (NULL == buf) {
		loge("input error: buf is NULL\n");
		return -EINVAL;
	}

	if (!hifi_is_loaded()) {
		loge("hifi isn't loaded.\n");
		return -ENXIO;
	}

	if (to_user_buf)
		goto RETRY;

	if (list_empty(&recv_proc_work_queue_head)) {
		/* wait wake_up() has to be called after change the result of the wait condition. */
		ret = wait_event_interruptible(s_misc_data.proc_waitq, s_misc_data.wait_flag!=0);
		if (ret) {
			logi("wait interrupted by a signal, ret: %d\n", ret);
			return ret;
		}
		logi("wait_event_interruptible success.\n");
	}

	/* locked recv_proc_lock */
	spin_lock_bh(&s_misc_data.recv_proc_lock);

	if (likely(s_misc_data.wait_flag > 0)) {
		s_misc_data.wait_flag--;
	}

	if (!list_empty(&recv_proc_work_queue_head)) {
		recv = list_entry(recv_proc_work_queue_head.next, struct recv_request, recv_node);
		len = recv->rev_msg.mail_buff_len;
		recmsg = (struct misc_recmsg_param*)recv->rev_msg.mail_buff;

		if (unlikely(len >= MAIL_LEN_MAX || len <= SIZE_CMD_ID || !recmsg)) {
			loge("buff size is invalid: %u(>= 512 or <= 8) or recmsg is null\n", len);
			ret = -EINVAL;
		} else {
			len -= SIZE_CMD_ID;
			to_user_buf = kzalloc(len, GFP_ATOMIC);
			if (!to_user_buf) {
				loge("kzalloc failed\n");
				ret = -ENOMEM;
				goto ERR;
			}
			memcpy(to_user_buf, recv->rev_msg.mail_buff, len);
		}

		list_del(&recv->recv_node);
		kfree(recv->rev_msg.mail_buff);
		kfree(recv);
		recv = NULL;
	} else {
		loge("recv proc list is empty.\n");
	}

	/* release recv_proc_lock */
	spin_unlock_bh(&s_misc_data.recv_proc_lock);

RETRY:
	if (to_user_buf) {
		recmsg = (struct misc_recmsg_param*)to_user_buf;
		logi("msgid: 0x%x, len: %u, "
			"play status : %d (0 - done normal, 1 - done complete, 2 - done abnormal, 3 - reset)\n",
			recmsg->msgID, len, recmsg->playStatus);

		ret = (int)copy_to_user(buf, to_user_buf, len);
		if (ret != 0) {
			loge("copy to user fail, ret : %d len : %u, retry_cnt: %d\n", ret, len, retry_cnt);
			retry_cnt++;
			ret = -EFAULT;
		}

		if (0 == ret || retry_cnt >= RETRY_COUNT) {
			kzfree(to_user_buf);
			to_user_buf = NULL;
			retry_cnt = 0;
			len = 0;
		}
	}

	OUT_FUNCTION;
	return ret;

ERR:
	spin_unlock_bh(&s_misc_data.recv_proc_lock);
	return ret;

}

static const struct file_operations hifi_misc_fops = {
	.owner			= THIS_MODULE,
	.open			= hifi_misc_open,
	.release		= hifi_misc_release,
	.unlocked_ioctl = hifi_misc_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl   = hifi_misc_ioctl32,
#endif
	.mmap			= hifi_misc_mmap,
};

static struct miscdevice hifi_misc_device = {
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= "hifi_misc",
	.fops	= &hifi_misc_fops,
};

static const struct file_operations hifi_proc_fops = {
	.owner = THIS_MODULE,
	.read = hifi_misc_proc_read,
};

static void hifi_misc_proc_init( void )
{
	struct proc_dir_entry * entry ;
	struct proc_dir_entry * hifi_misc_dir;

	hifi_misc_dir = proc_mkdir("hifidsp", NULL);
	if (hifi_misc_dir == NULL) {
		loge("Unable to create /proc/hifidsp directory.\n");
		return ;
	}

	/* Creating read/write "status" entry */
	entry = proc_create("hifi", S_IRUSR|S_IRGRP|S_IROTH, hifi_misc_dir, &hifi_proc_fops);
	if (entry == NULL) {
		remove_proc_entry("dsp", 0);
		loge("Unable to create /proc/hifidsp/hifi entry.\n");
		return ;
	}
}

#ifdef CONFIG_PM
static int hifi_sr_event(struct notifier_block *this,
		unsigned long event, void *ptr) {
	switch (event) {
	case PM_POST_HIBERNATION:
	case PM_POST_SUSPEND:
		logi("resume +.\n");
		atomic_set(&s_hifi_in_suspend, 0);
		logi("resume -.\n");
		break;

	case PM_HIBERNATION_PREPARE:
	case PM_SUSPEND_PREPARE:
		logi("suspend +.\n");
		atomic_set(&s_hifi_in_suspend, 1);
		while (true) {
			if (atomic_read(&s_hifi_in_saving)) {
				msleep(100);
			} else {
				break;
			}
		}
		logi("suspend -.\n");
		break;
	default:
		return NOTIFY_DONE;
	}
	return NOTIFY_OK;
}
#endif

static int hifi_reboot_notifier(struct notifier_block *nb,
		unsigned long foo, void *bar)
{
	logi("reboot +.\n");
	atomic_set(&s_hifi_in_suspend, 1);
	while (true) {
		if (atomic_read(&s_hifi_in_saving)) {
			msleep(100);
		} else {
			break;
		}
	}
	logi("reboot -.\n");

	return 0;
}

void hifi_get_log_signal(void)
{
	while (true) {
		if (atomic_read(&s_hifi_in_suspend)) {
			msleep(100);
		} else {
			atomic_set(&s_hifi_in_saving, 1);
			break;
		}
	}
	return;
}

void hifi_release_log_signal(void)
{
	atomic_set(&s_hifi_in_saving, 0);
}

int hifi_send_msg(unsigned int mailcode, void *data, unsigned int length)
{
	if (hifi_is_loaded()) {
		return (unsigned int)mailbox_send_msg(mailcode, data, length);
	}
	return -1;
}
EXPORT_SYMBOL(hifi_send_msg);

#ifdef MULTI_MIC
extern void hi6402_3mic_audio_clk(int mode);
extern void hi6402_3mic_fade_out(void);
/* 3mic add for reset hi6402 audio clk */
void reset_audio_clk_work(struct work_struct *work)
{
	struct common_hifi_cmd cmd_cnf;
	struct common_hifi_cmd tmp_mesg;
	struct common_hifi_cmd* mesg = &(tmp_mesg);
	struct dp_clk_request* dp_clk_cmd = NULL;
	unsigned short msg_id =  0;

	while (!list_empty(&s_misc_data.multi_mic_ctrl.cmd_queue)) {
		memset(&cmd_cnf, 0, sizeof(struct common_hifi_cmd));
		memset(mesg, 0, sizeof(struct common_hifi_cmd));

		spin_lock_bh(&s_misc_data.multi_mic_ctrl.cmd_lock);

		if (!list_empty(&s_misc_data.multi_mic_ctrl.cmd_queue)) {
			dp_clk_cmd = list_entry(s_misc_data.multi_mic_ctrl.cmd_queue.next, struct dp_clk_request, dp_clk_node);

			if (NULL == dp_clk_cmd) {
				loge("request is NULL.\n");
				spin_unlock_bh(&s_misc_data.multi_mic_ctrl.cmd_lock);
				return;
			} else {
				memcpy(mesg, &(dp_clk_cmd->dp_clk_msg), sizeof(struct common_hifi_cmd));
			}

			list_del(&dp_clk_cmd->dp_clk_node);
			kfree(dp_clk_cmd);
			dp_clk_cmd = NULL;
		} else {
			logw("list is empty!\n");
			spin_unlock_bh(&s_misc_data.multi_mic_ctrl.cmd_lock);
			return;
		}
		spin_unlock_bh(&s_misc_data.multi_mic_ctrl.cmd_lock);

		msg_id =  mesg->msg_id;

		logi("%s++,mesg[0x%x],value[0x%x],reserve[0x%x]\n", __FUNCTION__, mesg->msg_id, mesg->value, mesg->reserve);

		switch(msg_id) {
			case ID_AUDIO_AP_DP_CLK_EN_IND:
			{
				int audio_clk_state = s_misc_data.multi_mic_ctrl.audio_clk_state;

				/* reset hi6402 audio dp clk */
				if((audio_clk_state & HI6402_DP_CLK_ON) != (mesg->value & HI6402_DP_CLK_ON)) {
					hi6402_3mic_audio_clk(mesg->value);
					s_misc_data.multi_mic_ctrl.audio_clk_state = mesg->value;
				}

				/* send ack to hifi */
				if ((mesg->value & HI6402_DP_CLK_ON) == HI6402_DP_CLK_ON) {
					cmd_cnf.reserve = HI6402_DP_CLK_ON;
				} else {
					cmd_cnf.reserve = HI6402_DP_CLK_OFF;
				}

				cmd_cnf.msg_id = ID_AP_AUDIO_DP_CLK_STATE_IND;
				cmd_cnf.value = mesg->reserve;
				hifi_misc_send_hifi_msg_async(&cmd_cnf);
			}
			break;

			case ID_AUDIO_AP_FADE_OUT_REQ:
			{
				hi6402_3mic_fade_out();
				cmd_cnf.msg_id = ID_AP_AUDIO_FADE_OUT_IND;
				cmd_cnf.value = mesg->value;
				hifi_misc_send_hifi_msg_async(&cmd_cnf);

			}
			break;

			default:
			{
				loge("error msg:0x%x\n", msg_id);
			}
			break;
		}
	}

	if(!list_empty(&s_misc_data.multi_mic_ctrl.cmd_queue)){
		pr_info("%s have other cmd in list\n",__FUNCTION__);
	}

	logi("%s--\n",__FUNCTION__);
}
#endif
/*****************************************************************************
 函 数 名  : hifi_misc_probe
 功能描述  : Hifi MISC设备探测注册函数
 输入参数  : struct platform_device *pdev
 输出参数  : 无
 返 回 值  : 成功:OK 失败:ERROR
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年8月1日
	作	  者   : 夏青 00195127
	修改内容   : 新生成函数

*****************************************************************************/
static int hifi_misc_probe (struct platform_device *pdev)
{
	int ret = OK;

	IN_FUNCTION;

	memset(&s_misc_data, 0, sizeof(struct hifi_misc_priv));

	s_misc_data.dev = &pdev->dev;

#ifdef CONFIG_PM
	/* Register to get PM events */
	s_hifi_sr_nb.notifier_call = hifi_sr_event;
	s_hifi_sr_nb.priority = -1;
	(void)register_pm_notifier(&s_hifi_sr_nb);
#endif

	s_hifi_reboot_nb.notifier_call = hifi_reboot_notifier;
	s_hifi_reboot_nb.priority = -1;
	(void)register_reboot_notifier(&s_hifi_reboot_nb);

	s_misc_data.hifi_priv_base_virt = (unsigned char*)ioremap_wc(HIFI_BASE_ADDR, HIFI_UNSEC_REGION_SIZE);

	if (NULL == s_misc_data.hifi_priv_base_virt) {
		printk("hifi ioremap_wc error.\n");//can't use logx
		ret = ERROR;
		goto ERR;
	}
	s_misc_data.hifi_priv_base_phy = (unsigned char*)HIFI_MUSIC_DATA_LOCATION;

	hifi_om_init(pdev, s_misc_data.hifi_priv_base_virt, s_misc_data.hifi_priv_base_phy);

	printk("hifi pdev name[%s].\n", pdev->name);//can't use logx

	ret = misc_register(&hifi_misc_device);
	if (OK != ret) {
		loge("hifi misc device register fail,ERROR is %d.\n", ret);
		ret = ERROR;
		goto ERR;
	}

	hifi_misc_proc_init();

	/*初始化接受信号量*/
	spin_lock_init(&s_misc_data.recv_sync_lock);
	spin_lock_init(&s_misc_data.recv_proc_lock);

	/*初始化同步信号量*/
	init_completion(&s_misc_data.completion);

	/*初始化读文件信号量*/
	init_waitqueue_head(&s_misc_data.proc_waitq);
	s_misc_data.wait_flag = 0;
	s_misc_data.sn = 0;

	wake_lock_init(&s_misc_data.hifi_misc_wakelock,WAKE_LOCK_SUSPEND, "hifi_wakelock");

	ret = DRV_IPCIntInit();
	if (OK != ret) {
		loge("hifi ipc init fail.\n");
		goto ERR;
	}
	ret = (int)mailbox_init();
	if (OK != ret) {
		loge("hifi mailbox init fail.\n");
		goto ERR;
	}

#ifdef MULTI_MIC
	/* init 3mic reset clk workqueue */
	/* 3mic add for reset hi6402 audio dp clk
	 * init 3mic reset clk workqueue
	 */
	s_misc_data.multi_mic_ctrl.reset_audio_dp_clk_wq =
		create_singlethread_workqueue("multi_mic_reset_clk_wq");
	if (!(s_misc_data.multi_mic_ctrl.reset_audio_dp_clk_wq)) {
		pr_err("%s(%u) : workqueue create failed", __FUNCTION__,__LINE__);
		ret = -ENOMEM;
		goto ERR;
	}
	INIT_WORK(&s_misc_data.multi_mic_ctrl.reset_audio_dp_clk_work, reset_audio_clk_work);
	s_misc_data.multi_mic_ctrl.audio_clk_state = HI6402_DP_CLK_ON;
	INIT_LIST_HEAD(&s_misc_data.multi_mic_ctrl.cmd_queue);
	spin_lock_init(&(s_misc_data.multi_mic_ctrl.cmd_lock));
#endif
	/*注册双核通信处理函数*/
	ret = mailbox_reg_msg_cb(MAILBOX_MAILCODE_HIFI_TO_ACPU_MISC, (mb_msg_cb)hifi_misc_handle_mail, NULL);

	if (OK != ret) {
		loge("hifi mailbox handle func register fail.\n");
		goto ERR;
	}

	OUT_FUNCTION;
	return OK;

ERR:
	hifi_om_deinit(pdev);

	if (NULL != s_misc_data.hifi_priv_base_virt) {
		iounmap(s_misc_data.hifi_priv_base_virt);
		s_misc_data.hifi_priv_base_virt = NULL;
	}

#ifdef MULTI_MIC
	if(s_misc_data.multi_mic_ctrl.reset_audio_dp_clk_wq) {
		flush_workqueue(s_misc_data.multi_mic_ctrl.reset_audio_dp_clk_wq);
		destroy_workqueue(s_misc_data.multi_mic_ctrl.reset_audio_dp_clk_wq);
	}
#endif

#ifdef CONFIG_PM
	unregister_pm_notifier(&s_hifi_sr_nb);
#endif
	unregister_reboot_notifier(&s_hifi_reboot_nb);

	(void)misc_deregister(&hifi_misc_device);

	OUT_FUNCTION;
	return ERROR;
}

/*****************************************************************************
 函 数 名  : hifi_misc_remove
 功能描述  : Hifi MISC 设备移除
 输入参数  : struct platform_device *pdev
 输出参数  : 无
 返 回 值  : OK
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年8月1日
	作	  者   : 夏青 00195127
	修改内容   : 新生成函数

*****************************************************************************/
static int hifi_misc_remove(struct platform_device *pdev)
{
	IN_FUNCTION;

	hifi_om_deinit(pdev);

	if (NULL != s_misc_data.hifi_priv_base_virt) {
		iounmap(s_misc_data.hifi_priv_base_virt);
		s_misc_data.hifi_priv_base_virt = NULL;
	}

#ifdef CONFIG_PM
	/* Unregister for PM events */
	unregister_pm_notifier(&s_hifi_sr_nb);
#endif
	unregister_reboot_notifier(&s_hifi_reboot_nb);

	/* misc deregister*/
	(void)misc_deregister(&hifi_misc_device);

	OUT_FUNCTION;
	return OK;
}

static const struct of_device_id hifi_match_table[] = {
	{
		.compatible = DTS_COMP_HIFIDSP_NAME,
		.data = NULL,
	},
	{}
};
MODULE_DEVICE_TABLE(of, hifi_match_table);

static struct platform_driver hifi_misc_driver = {
	.driver =
	{
		.name  = "hifi_dsp_misc",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(hifi_match_table),
	},
	.probe	= hifi_misc_probe,
	.remove = hifi_misc_remove,
};

module_platform_driver(hifi_misc_driver);


MODULE_DESCRIPTION("hifi driver");
MODULE_LICENSE("GPL");

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

