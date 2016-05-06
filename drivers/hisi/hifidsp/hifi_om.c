/*
 * hifi om.
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/kthread.h>
#include <linux/semaphore.h>
#include <linux/platform_device.h>
#include <linux/rtc.h>
#include <linux/syscalls.h>
#include <linux/vmalloc.h>
#include <linux/slab.h>
#include <linux/workqueue.h>
#include <linux/spinlock.h>
#include <linux/list.h>
#include <asm/memory.h>
/*lint -e451*/
#include <asm/types.h>
/*lint +e451*/
#include <asm/io.h>

#include <linux/time.h>
#include <linux/timex.h>
#include <linux/rtc.h>

#include "audio_hifi.h"
#include "hifi_lpp.h"
#include "hifi_om.h"
#include "drv_mailbox_msg.h"
#include <dsm/dsm_pub.h>
#include <linux/hisi/rdr_pub.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*lint -e773*/
#define HI_DECLARE_SEMAPHORE(name) \
	struct semaphore name = __SEMAPHORE_INITIALIZER(name, 0)
HI_DECLARE_SEMAPHORE(hifi_log_sema);
/*lint +e773*/
struct hifi_om_s g_om_data;
static struct proc_dir_entry *hifi_debug_dir = NULL;

#define MAX_LEVEL_STR_LEN 32
#define UNCONFIRM_ADDR (0)
static struct hifi_dsp_dump_info s_dsp_dump_info[] = {
	{DSP_NORMAL, DUMP_DSP_LOG, FILE_NAME_DUMP_DSP_LOG, UNCONFIRM_ADDR, (DRV_DSP_UART_TO_MEM_SIZE-DRV_DSP_UART_TO_MEM_RESERVE_SIZE)},
	{DSP_NORMAL, DUMP_DSP_BIN, FILE_NAME_DUMP_DSP_BIN, UNCONFIRM_ADDR, HIFI_DUMP_BIN_SIZE},
	{DSP_PANIC,  DUMP_DSP_LOG, FILE_NAME_DUMP_DSP_PANIC_LOG, UNCONFIRM_ADDR, (DRV_DSP_UART_TO_MEM_SIZE-DRV_DSP_UART_TO_MEM_RESERVE_SIZE)},
	{DSP_PANIC,  DUMP_DSP_BIN, FILE_NAME_DUMP_DSP_PANIC_BIN, UNCONFIRM_ADDR, HIFI_DUMP_BIN_SIZE},
	{DSP_PANIC,  DUMP_DSP_BIN, FILE_NAME_DUMP_DSP_OCRAM_BIN, UNCONFIRM_ADDR, HIFI_IMAGE_OCRAMBAK_SIZE},
	{DSP_PANIC,  DUMP_DSP_BIN, FILE_NAME_DUMP_DSP_TCM_BIN,	 UNCONFIRM_ADDR, HIFI_IMAGE_TCMBAK_SIZE},
};

static struct hifi_effect_info_stru effect_algo[] = {
	{ID_EFFECT_ALGO_FORMATER, "FORMATER"},

	{ID_EFFECT_ALGO_FORTE_VOICE_SPKOUT, "FORTE_VOICE_SPKOUT"},
	{ID_EFFECT_ALGO_FORTE_VOICE_MICIN, "FORTE_VOICE_MICIN"},
	{ID_EFFECT_ALGO_FORTE_VOICE_SPKOUT_BWE, "FORTE_VOICE_SPKOUT_BWE"},

	{ID_EFFECT_ALGO_FORTE_VOIP_MICIN, "FORTE_VOIP_MICIN"},
	{ID_EFFECT_ALGO_FORTE_VOIP_SPKOUT, "FORTE_VOIP_SPKOUT"},

	{ID_EFFECT_ALGO_IN_CONVERT_I2S_GENERAL, "IN_CONVERT_I2S_GENERAL"},
	{ID_EFFECT_ALGO_IN_CONVERT_I2S_HI363X, "IN_CONVERT_I2S_HI363X"},

	{ID_EFFECT_ALGO_INTERLACE, "INTERLACE"},

	{ID_EFFECT_ALGO_OUT_CONVERT_I2S_GENERAL, "OUT_CONVERT_I2S_GENERAL"},
	{ID_EFFECT_ALGO_OUT_CONVERT_I2S_HI363X, "OUT_CONVERT_I2S_HI363X"},

	{ID_EFFECT_ALGO_SWAP, "SWAP"},

	{ID_EFFECT_ALGO_IMEDIA_WNR_MICIN, "IMEDIA_WNR_MICIN"},
	{ID_EFFECT_ALGO_IMEDIA_WNR_SPKOUT, "IMEDIA_WNR_SPKOUT"},

	{ID_EFFECT_ALGO_SWS_INTERFACE, "SWS_INTERFACE"},
	{ID_EFFECT_ALGO_DTS, "DTS"},
	{ID_EFFECT_ALGO_DRE, "DRE"},
	{ID_EFFECT_ALGO_CHC, "CHC"},
	{ID_EFFECT_ALGO_SRC, "SRC"},
	{ID_EFFECT_ALGO_TTY, "TTY"},

	{ID_EFFECT_ALGO_KARAOKE_RECORD, "KARAOKE_RECORD"},
	{ID_EFFECT_ALGO_KARAOKE_PLAY, "KARAOKE_PLAY"},

	{ID_EFFECT_ALGO_MLIB_CS_VOICE_CALL_MICIN, "MLIB_CS_VOICE_CALL_MICIN"},
	{ID_EFFECT_ALGO_MLIB_CS_VOICE_CALL_SPKOUT, "MLIB_CS_VOICE_CALL_SPKOUT"},
	{ID_EFFECT_ALGO_MLIB_VOIP_CALL_MICIN, "MLIB_VOIP_CALL_MICIN"},
	{ID_EFFECT_ALGO_MLIB_VOIP_CALL_SPKOUT, "MLIB_VOIP_CALL_MICIN"},
	{ID_EFFECT_ALGO_MLIB_AUDIO_PLAY, "MLIB_AUDIO_PLAY"},
	{ID_EFFECT_ALGO_MLIB_AUDIO_RECORD, "MLIB_AUDIO_RECORD"},
	{ID_EFFECT_ALGO_MLIB_SIRI_MICIN, "MLIB_SIRI_MICIN"},
	{ID_EFFECT_ALGO_MLIB_SIRI_SPKOUT, "MLIB_SIRI_SPKOUT"},

	{ID_EFFECT_ALGO_EQ, "EQ"},
	{ID_EFFECT_ALGO_MBDRC6402, "MBDRC6402"},

	{ID_EFFECT_ALGO_IMEDIA_VOIP_MICIN, "IMEDIA_VOIP_MICIN"},
	{ID_EFFECT_ALGO_IMEDIA_VOIP_SPKOUT, "IMEDIA_VOIP_SPKOUT"},
	{ID_EFFECT_ALGO_IMEDIA_VOICE_CALL_MICIN, "IMEDIA_VOICE_CALL_MICIN"},
	{ID_EFFECT_ALGO_IMEDIA_VOICE_CALL_SPKOUT, "IMEDIA_VOICE_CALL_SPKOUT"},
	{ID_EFFECT_ALGO_IMEDIA_VOICE_CALL_SPKOUT_BWE, "IMEDIA_VOICE_CALL_SPKOUT_BWE"},
};

static  void hifi_om_voice_bsd_work_handler(struct work_struct *work);
static  void hifi_om_show_audio_detect_info(struct work_struct *work);

static struct hifi_om_work_info work_info[] = {
	{HIFI_OM_WORK_VOICE_BSD, "hifi_om_work_voice_bsd", hifi_om_voice_bsd_work_handler, {0}},
	{HIFI_OM_WORK_AUDIO_OM_DETECTION, "hifi_om_work_audio_om_detect", hifi_om_show_audio_detect_info, {0}},
};

extern struct dsm_client *dsm_audio_client;
static unsigned int dsm_notify_limit = 0xF;

static void hifi_get_time_stamp(char *timestamp_buf, unsigned int len)
{
	struct timeval tv = {0};
	struct rtc_time tm = {0};

	BUG_ON(NULL == timestamp_buf);

	memset(&tv, 0, sizeof(struct timeval));
	memset(&tm, 0, sizeof(struct rtc_time));

	do_gettimeofday(&tv);
	tv.tv_sec -= sys_tz.tz_minuteswest * 60;
	rtc_time_to_tm(tv.tv_sec, &tm);

	snprintf(timestamp_buf, len, "%04d%02d%02d%02d%02d%02d",
		tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
		tm.tm_hour, tm.tm_min, tm.tm_sec);

	return;
}

static int hifi_chown(char *path, uid_t user, gid_t group)
{
	int ret = 0;
	mm_segment_t old_fs;

	if (NULL == path)
		return -1;

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	ret = (int)sys_chown((const char __user *)path, user, group);
	if (ret) {
		loge("chown %s uid [%d] gid [%d] failed error [%d]!\n", path, user, group, ret);
	}

	set_fs(old_fs);

	return ret;
}

static int hifi_create_dir(char *path)
{
	int fd = -1;
	mm_segment_t old_fs = 0;

	if (!path) {
		loge("path(%p) is invailed\n", path);
		return -1;
	}

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	fd = sys_access(path, 0);
	if (0 != fd) {
		logi("need create dir %s.\n", path);
		fd = sys_mkdir(path, HIFI_OM_DIR_LIMIT);
		if (fd < 0) {
			loge("create dir %s fail, ret: %d.\n", path, fd);
			return fd;
		}
		logi("create dir %s successed, fd: %d.\n", path, fd);

		/* hifi_log dir limit root-system */
		if (hifi_chown(path, ROOT_UID, SYSTEM_GID)) {
			loge("chown %s failed!\n", path);
		}
	}

	set_fs(old_fs);

	return 0;
}

static int hifi_om_create_log_dir(char *path)
{
	char cur_path[HIFI_DUMP_FILE_NAME_MAX_LEN];
	int index = 0;

	if (!path || (strlen(path) + 1) > HIFI_DUMP_FILE_NAME_MAX_LEN) {
		loge("path(%p) is invailed\n", path);
		return -1;
	}

	if (0 == sys_access(path, 0))
		return 0;

	memset(cur_path, 0, HIFI_DUMP_FILE_NAME_MAX_LEN);

	if (*path != '/')
		return -1;

	cur_path[index++] = *path++;

	while (*path != '\0') {
		if (*path == '/') {
			if (hifi_create_dir(cur_path)) {
				loge("create dir %s failed\n", cur_path);
				return -1;
			}
		}
		cur_path[index++] = *path++;
	}

	return 0;

}

int hifi_om_get_voice_bsd_param(void __user * uaddr)
{
	int ret = OK;
	int work_id = HIFI_OM_WORK_VOICE_BSD;
	struct hifi_om_work *om_work = NULL;
	unsigned char data[MAIL_LEN_MAX] = {'\0'};
	unsigned int data_len = 0;
	struct voice_bsd_param_hsm param;

	memset(&param, 0, sizeof(param));
	if (copy_from_user(&param, uaddr, sizeof(param))) {
		loge("copy_from_user failed\n");
		ret = -EFAULT;
		goto exit;
	}

	if (!param.pdata) {
		loge("user buffer is null\n");
		ret = -EINVAL;
		goto exit;
	}

	spin_lock_bh(&work_info[work_id].ctl.lock);
	if (!list_empty(&work_info[work_id].ctl.list)) {
		om_work = list_entry(work_info[work_id].ctl.list.next, struct hifi_om_work, om_node);

		data_len = om_work->data_len;
		memcpy(data, om_work->data, om_work->data_len);

		list_del(&om_work->om_node);
		kzfree(om_work);
	}
	spin_unlock_bh(&work_info[work_id].ctl.lock);

	if (param.data_len < data_len) {
		loge("userspace len(%u) is less than data_len(%u)\n", param.data_len, data_len);
		ret = -EINVAL;
		goto exit;
	}

	if (copy_to_user((void __user *)param.pdata, data, data_len)) {
		loge("copy_to_user failed\n");
		ret = -EFAULT;
		goto exit;
	}
	logd("size(%u)copy to user success\n", data_len);

exit:

	return ret;
}

static void hifi_om_voice_bsd_work_handler(struct work_struct *work)
{
	int retval = 0;
	char *envp[2] = {"hifi_voice_bsd_param", NULL};

	retval = kobject_uevent_env(&g_om_data.dev->kobj, KOBJ_CHANGE, envp);
	if (retval) {
		loge("send uevent failed, retval: %d\n", retval);
		return;
	}
	logi("report uevent success\n");

	return;
}

void hifi_om_rev_data_handle(int work_id, const unsigned char *addr, unsigned int len)
{
	struct hifi_om_work *work = NULL;

	if (!addr || 0 == len || len > MAIL_LEN_MAX) {
		loge("addr is null or len is invaled, len: %u", len);
		return;
	}

	work = kzalloc(sizeof(*work) + len, GFP_ATOMIC);
	if (!work) {
		loge("malloc size %zu failed\n", sizeof(*work) + len);
		return;
	}
	memcpy(work->data, addr, len);
	work->data_len = len;

	spin_lock_bh(&work_info[work_id].ctl.lock);
	list_add_tail(&work->om_node, &work_info[work_id].ctl.list);
	spin_unlock_bh(&work_info[work_id].ctl.lock);

	if (!queue_work(work_info[work_id].ctl.wq, &work_info[work_id].ctl.work)) {
		loge("work_id: %d, This work was already on the queue\n", work_id);
	}

	return;
}

static void hifi_om_show_audio_detect_info(struct work_struct *work)
{
	int work_id = HIFI_OM_WORK_AUDIO_OM_DETECTION;
	struct hifi_om_work *om_work = NULL;
	unsigned char data[MAIL_LEN_MAX] = {'\0'};
	unsigned int data_len = 0;
	unsigned int hifi_msg_type = 0;
	struct hifi_om_load_info_stru hifi_om_info;
	struct hifi_om_effect_mcps_stru mcps_info;
	struct hifi_om_update_buff_delay_info update_buff_delay_info;

	spin_lock_bh(&work_info[work_id].ctl.lock);
	if (!list_empty(&work_info[work_id].ctl.list)) {
		om_work = list_entry(work_info[work_id].ctl.list.next, struct hifi_om_work, om_node);

		data_len = om_work->data_len;
		memcpy(data, om_work->data, om_work->data_len);

		list_del(&om_work->om_node);
		kzfree(om_work);
	}
	spin_unlock_bh(&work_info[work_id].ctl.lock);

	memset(&hifi_om_info, 0, sizeof(hifi_om_info));
	memset(&mcps_info, 0, sizeof(mcps_info));
	memset(&update_buff_delay_info, 0, sizeof(update_buff_delay_info));

	hifi_msg_type = *(unsigned int *)data;

	switch (hifi_msg_type) {
	case HIFI_CPU_OM_LOAD_INFO:
		if ((sizeof(hifi_om_info)) != data_len) {
			logw("unavailable data from hifi, data_len: %u\n");
			return;
		}
		memcpy(&hifi_om_info, data, sizeof(hifi_om_info));

		hifi_om_cpu_load_info_show(&hifi_om_info);
		break;
	case HIFI_CPU_OM_ALGO_MCPS_INFO:
		if ((sizeof(mcps_info)) != data_len) {
			logw("unavailable data from hifi, data_len: %u\n");
			return;
		}
		memcpy(&mcps_info, data, sizeof(mcps_info));

		hifi_om_effect_mcps_info_show(&mcps_info);
		break;
	case HIFI_CPU_OM_UPDATE_BUFF_DELAY_INFO:
		if ((sizeof(update_buff_delay_info)) != data_len) {
			logw("unavailable data from hifi, data_len: %u\n");
			return;
		}
		memcpy(&update_buff_delay_info, data, sizeof(update_buff_delay_info));

		hifi_om_update_buff_delay_info_show(&update_buff_delay_info);
		break;
	default:
		logi("type(%d), not support\n", hifi_msg_type);
		break;
	}

	return;
}

int hifi_get_dmesg(void __user *arg)
{
	int ret = OK;
	unsigned int len = 0;
	struct misc_io_dump_buf_param dump_info;
	void __user * dump_info_user_buf = NULL;

	len = (unsigned int)(*g_om_data.dsp_log_cur_addr);
	if (len > DRV_DSP_UART_TO_MEM_SIZE)
	{
		loge("len is larger: %d(%d), don't dump log\n", len, DRV_DSP_UART_TO_MEM_SIZE);
		return 0;
	}

	if (copy_from_user(&dump_info, arg, sizeof(struct misc_io_dump_buf_param))) {
		loge("copy_from_user fail, don't dump log\n");
		return 0;
	}

	if (dump_info.buf_size == 0) {
		loge("input buf size is zero, don't dump log\n");
		return 0;
	}

	if (len > dump_info.buf_size) {
		logw("input buf size smaller, input buf size: %d, log size: %d, contiue to dump using smaller size\n", dump_info.buf_size, len);
		len = dump_info.buf_size;
	}

	dump_info_user_buf = INT_TO_ADDR(dump_info.user_buf_l, dump_info.user_buf_h);
	if (!dump_info_user_buf) {
		loge("input dump buff addr is null\n");
		return 0;
	}
	logi("get msg: len:%d from:%p to:%p.\n", len, s_dsp_dump_info[0].data_addr, dump_info_user_buf);

	g_om_data.dsp_log_addr = (char*)ioremap_wc(DRV_DSP_UART_TO_MEM, DRV_DSP_UART_TO_MEM_SIZE);
	if (NULL == g_om_data.dsp_log_addr) {
		loge("dsp log ioremap Error.\n");
		return 0;
	}
	s_dsp_dump_info[0].data_addr = g_om_data.dsp_log_addr;

	ret = copy_to_user(dump_info_user_buf, s_dsp_dump_info[0].data_addr, len);
	if (OK != ret) {
		loge("copy_to_user fail: %d\n", ret);
		len -= ret;
	}

	if (dump_info.clear) {
		*g_om_data.dsp_log_cur_addr = DRV_DSP_UART_TO_MEM_RESERVE_SIZE;
		if(s_dsp_dump_info[0].data_len > DRV_DSP_UART_TO_MEM_SIZE) {
			loge("s_dsp_dump_info[0].data_len is larger than DRV_DSP_UART_TO_MEM_SIZE\n");
			len = 0;
		} else {
			memset(s_dsp_dump_info[0].data_addr, 0, s_dsp_dump_info[0].data_len);
		}
	}

	if(g_om_data.dsp_log_addr) {
		iounmap(g_om_data.dsp_log_addr);
		g_om_data.dsp_log_addr = NULL;
	}

	return (int)len;
}

static void hifi_dump_dsp(DUMP_DSP_INDEX index)
{
	int ret = 0;

	mm_segment_t fs = 0;
	struct file *fp = NULL;
	int file_flag = O_RDWR;
	struct kstat file_stat;
	int write_size = 0;
	unsigned int err_no = 0xFFFFFFFF;

	char tmp_buf[64] = {0};
	unsigned long tmp_len = 0;
	struct rtc_time cur_tm;
	struct timespec now;

	char  path_name[HIFI_DUMP_FILE_NAME_MAX_LEN] = {0};
	char* file_name		= s_dsp_dump_info[index].file_name;
	char* data_addr		= NULL;
	unsigned int data_len = s_dsp_dump_info[index].data_len;

	char* is_panic		= "i'm panic.\n";
	char* is_exception	= "i'm exception.\n";
	char* not_panic		= "i'm ok.\n";

	memset(path_name, 0, HIFI_DUMP_FILE_NAME_MAX_LEN);

	if (down_interruptible(&g_om_data.dsp_dump_sema) < 0) {
		loge("acquire the semaphore error.\n");
		return;
	}

	IN_FUNCTION;

	hifi_get_log_signal();

	g_om_data.dsp_log_addr = (char*)ioremap_wc(DRV_DSP_UART_TO_MEM, DRV_DSP_UART_TO_MEM_SIZE);
	if (NULL == g_om_data.dsp_log_addr) {
		loge("dsp log remap fail.\n");
		goto END;
	}

	s_dsp_dump_info[NORMAL_LOG].data_addr = g_om_data.dsp_log_addr + DRV_DSP_UART_TO_MEM_RESERVE_SIZE;
	s_dsp_dump_info[PANIC_LOG].data_addr  = g_om_data.dsp_log_addr + DRV_DSP_UART_TO_MEM_RESERVE_SIZE;

	if(index == OCRAM_BIN)
	{
		s_dsp_dump_info[index].data_addr = (unsigned char*)ioremap_wc(HIFI_OCRAM_BASE_ADDR, HIFI_IMAGE_OCRAMBAK_SIZE);
	}
	if(index == TCM_BIN)
	{
		s_dsp_dump_info[index].data_addr = (unsigned char*)ioremap_wc(HIFI_TCM_BASE_ADDR, HIFI_IMAGE_TCMBAK_SIZE);
	}

	if (NULL == s_dsp_dump_info[index].data_addr) {
		loge("dsp log ioremap fail.\n");
		goto END;
	}

	data_addr = s_dsp_dump_info[index].data_addr;

	fs = get_fs();
	set_fs(KERNEL_DS);

	ret = hifi_om_create_log_dir(LOG_PATH_HIFI_LOG);
	if (0 != ret) {
		goto END;
	}

	snprintf(path_name, HIFI_DUMP_FILE_NAME_MAX_LEN, "%s%s", LOG_PATH_HIFI_LOG, file_name);

	ret = vfs_stat(path_name, &file_stat);
	if (ret < 0) {
		logi("there isn't a dsp log file:%s, and need to create.\n", path_name);
		file_flag |= O_CREAT;
	}

	fp = filp_open(path_name, file_flag, HIFI_OM_FILE_LIMIT);
	if (IS_ERR(fp)) {
		loge("open file fail: %s.\n", path_name);
		fp = NULL;
		goto END;
	}

	/*write from file start*/
	vfs_llseek(fp, 0, SEEK_SET);

	/*write file head*/
	if (DUMP_DSP_LOG == s_dsp_dump_info[index].dump_type) {
		/*write dump log time*/
		now = current_kernel_time();
		rtc_time_to_tm(now.tv_sec, &cur_tm);

		memset(tmp_buf, 0, sizeof(tmp_buf));
		tmp_len = snprintf(tmp_buf, sizeof(tmp_buf), "%04d-%02d-%02d %02d:%02d:%02d.\n",
								cur_tm.tm_year+1900, cur_tm.tm_mon+1,
								cur_tm.tm_mday, cur_tm.tm_hour,
								cur_tm.tm_min, cur_tm.tm_sec);
		vfs_write(fp, tmp_buf, tmp_len, &fp->f_pos);

		/*write exception no*/
		memset(tmp_buf, 0, sizeof(tmp_buf));
		err_no = (unsigned int)(*(g_om_data.dsp_exception_no));
		if (err_no != 0xFFFFFFFF) {
			tmp_len = snprintf(tmp_buf, sizeof(tmp_buf), "the exception no: %u.\n", err_no);
		} else {
			tmp_len = snprintf(tmp_buf, sizeof(tmp_buf), "%s", "hifi is fine, just dump log.\n");
		}

		vfs_write(fp, tmp_buf, tmp_len, &fp->f_pos);

		/*write error type*/
		if (0xdeadbeaf == *g_om_data.dsp_panic_mark) {
			vfs_write(fp, is_panic, strlen(is_panic), &fp->f_pos);
		} else if(0xbeafdead == *g_om_data.dsp_panic_mark){
			vfs_write(fp, is_exception, strlen(is_exception), &fp->f_pos);
		} else {
			vfs_write(fp, not_panic, strlen(not_panic), &fp->f_pos);
		}
	}

	/*write dsp info*/
	if((write_size = vfs_write(fp, data_addr, data_len, &fp->f_pos)) < 0) {
		loge("write file fail.\n");
	}

	/* hifi.log file limit root-system */
	if (hifi_chown(path_name, ROOT_UID, SYSTEM_GID)) {
		loge("chown %s failed!\n", path_name);
	}

	logi("write file size: %d.\n", write_size);

END:
	if (fp) {
		filp_close(fp, 0);
	}
	set_fs(fs);

	if (NULL != g_om_data.dsp_log_addr) {
		iounmap(g_om_data.dsp_log_addr);
		g_om_data.dsp_log_addr = NULL;
	}

	if((index == OCRAM_BIN || index == TCM_BIN) && (NULL != s_dsp_dump_info[index].data_addr))
	{
		iounmap(s_dsp_dump_info[index].data_addr);
		s_dsp_dump_info[index].data_addr = NULL;
	}

	hifi_release_log_signal();

	up(&g_om_data.dsp_dump_sema);
	OUT_FUNCTION;

	return;
}

static debug_level_com s_debug_level_com[4] = {{'d', 3},{'i', 2},{'w', 1},{'e', 0}};

static unsigned int hifi_get_debug_level_num(char level_char)
{
	int i = 0;
	int len = sizeof(s_debug_level_com)/sizeof(s_debug_level_com[0]);

	for (i = 0; i < len; i++) {
		if(level_char == s_debug_level_com[i].level_char) {
			return s_debug_level_com[i].level_num;
		}
	}

	return 2; /*info*/
}

static char hifi_get_debug_level_char(char level_num)
{
	int i = 0;
	int len = sizeof(s_debug_level_com)/sizeof(s_debug_level_com[0]);

	for (i = 0; i < len; i++) {
		if(level_num == s_debug_level_com[i].level_num) {
			return s_debug_level_com[i].level_char;
		}
	}

	return 'i'; /*info*/
}

static void hifi_set_dsp_debug_level(unsigned int level)
{
	*(unsigned int*)g_om_data.dsp_debug_level_addr = level;
}

static ssize_t hifi_debug_level_show(struct file *file, char __user *buf,
		size_t size, loff_t *data)
{
	char level_str[MAX_LEVEL_STR_LEN] = {0};

	if(NULL == buf) {
		loge("Input param buf is invalid\n");
		return -EINVAL;
	}

	snprintf(level_str, MAX_LEVEL_STR_LEN, "debug level: %c.\n", hifi_get_debug_level_char(g_om_data.debug_level));

	return simple_read_from_buffer(buf, size, data, level_str, strlen(level_str));
}

static ssize_t hifi_debug_level_store(struct file *file, const char __user *buf,
		size_t size, loff_t *data)
{
	ssize_t ret;
	char level_str[MAX_LEVEL_STR_LEN] = {0};
	loff_t pos = 0;

	if (NULL == buf) {
		loge("Input param buf is invalid\n");
		return -EINVAL;
	}
	ret = simple_write_to_buffer(level_str, MAX_LEVEL_STR_LEN - 1 , &pos, buf, size);
	if (ret != size) {
		loge("Input param buf read error, return value: %zd\n", ret);
		return -EINVAL;
	}

	if (!strchr("diwe", level_str[0])) {
		loge("Input param buf is error(valid: d,i,w,e): %s.\n", level_str);
		return -EINVAL;
	}
	if (level_str[1] != '\n') {
		loge("Input param buf is error, last char is not \\n .\n");
		return -EINVAL;
	}

	g_om_data.debug_level = hifi_get_debug_level_num(level_str[0]);
	return size;
}
static const struct file_operations hifi_debug_proc_ops = {
	.owner = THIS_MODULE,
	.read  = hifi_debug_level_show,
	.write = hifi_debug_level_store,
};

static int hifi_send_str_todsp(const char* cmd_str, size_t size)
{
	int           ret     = OK;
	unsigned int  msg_len = 0;
	hifi_str_cmd *pcmd    = NULL;

	BUG_ON(cmd_str == NULL);

	msg_len = sizeof(hifi_str_cmd) + size + 1; //add 1 for last \0

	pcmd = (hifi_str_cmd *)kmalloc(msg_len, GFP_ATOMIC);
	if (!pcmd) {
		loge("cmd malloc is null\n");
		return -ENOMEM;
	}
	memset(pcmd, 0, msg_len);

	pcmd->msg_id = ID_AP_AUDIO_STR_CMD;
	pcmd->str_len = size;
	strncpy(pcmd->str, cmd_str, size);

	ret = (int)mailbox_send_msg(MAILBOX_MAILCODE_ACPU_TO_HIFI_MISC, pcmd, msg_len);

	kfree(pcmd);

	return ret;
}

static ssize_t hifi_dsp_fault_inject_show(struct file *file, char __user *buf,
		size_t size, loff_t *data)
{
	char useage[] = "Useage:\necho \"test_case param1 param2 ...\" > dspfaultinject\n"
					"test_case maybe:\n"
					"read_mem addr\n"
					"write_mem addr value\n"
					"endless_loop\n"
					"overload\n"
					"auto_reset\n"
					"param_test\n"
					"exit\n"
					"dyn_mem_leak [size count type(1:DDR 2:TCM)]\n"
					"dyn_mem_overlap [type(0:DDR 1:TCM)]\n"
					"stack_overflow\n"
					"isr_ipc\n"
					"om_report_ctrl [type(on off status)]\n";

	if (!buf) {
		loge("Input param buf is invalid\n");
		return -EINVAL;
	}

	return simple_read_from_buffer(buf, size, data, useage, strlen(useage));
}

#define FAULT_INJECT_CMD_STR_MAX_LEN 200
static ssize_t hifi_dsp_fault_inject_store(struct file *file, const char __user *buf,
		size_t size, loff_t *data)
{
	int ret = OK;
	ssize_t len = 0;
	loff_t pos = 0;
	char cmd_str[FAULT_INJECT_CMD_STR_MAX_LEN] = {0};

	if (!buf) {
		loge("param buf is NULL\n");
		return -EINVAL;
	}

	if (size > FAULT_INJECT_CMD_STR_MAX_LEN) {
		loge("input size(%zd) is larger than max-len(%d)\n", size, FAULT_INJECT_CMD_STR_MAX_LEN);
		return -EINVAL;
	}

	memset(cmd_str, 0, sizeof(cmd_str));
	len = simple_write_to_buffer(cmd_str, (FAULT_INJECT_CMD_STR_MAX_LEN - 1) , &pos, buf, size);
	if (len != size) {
		loge("write to buffer fail: %zd\n", len);
		return -EINVAL;
	}

	ret = hifi_send_str_todsp(cmd_str, size);
	if (ret) {
		loge("msg: %s send to hifi fail: %d\n", cmd_str, ret);
		return ret;
	}

	return size;
}

static const struct file_operations hifi_dspfaultinject_proc_ops = {
	.owner = THIS_MODULE,
	.read  = hifi_dsp_fault_inject_show,
	.write = hifi_dsp_fault_inject_store,
};

#define RESET_OPTION_LEN 100

static ssize_t hifi_dsp_reset_option_show(struct file *file, char __user *buf,
		size_t size, loff_t *data)
{
	char reset_option[RESET_OPTION_LEN] = {0};

	if(NULL == buf) {
		loge("Input param buf is invalid\n");
		return -EINVAL;
	}

	snprintf(reset_option, RESET_OPTION_LEN,
		"reset_option: 0(reset mediasever) 1(reset system) current:%d.\n", g_om_data.reset_system);

	return simple_read_from_buffer(buf, size, data, reset_option, strlen(reset_option));
}


static ssize_t hifi_dsp_reset_option_store(struct file *file, const char __user *buf,
		size_t size, loff_t *data)
{
	ssize_t ret;
	char reset_option[RESET_OPTION_LEN] = {0};
	loff_t pos = 0;

	if (NULL == buf) {
		loge("Input param buf is invalid\n");
		return -EINVAL;
	}
	ret = simple_write_to_buffer(reset_option, RESET_OPTION_LEN-1, &pos, buf, size);
	if (ret != size) {
		loge("Input param buf read error, return value: %zd\n", ret);
		return -EINVAL;
	}

	if (!strchr("01", reset_option[0])) {
		loge("Input param buf is error(valid: d,i,w,e): %s.\n", reset_option);
		return -EINVAL;
	}
	if (reset_option[1] != '\n') {
		loge("Input param buf is error, last char is not \\n .\n");
		return -EINVAL;
	}

	g_om_data.reset_system = (reset_option[0] == '0') ? false : true;
	return size;
}



static const struct file_operations hifi_reset_option_proc_ops = {
	.owner = THIS_MODULE,
	.read  = hifi_dsp_reset_option_show,
	.write = hifi_dsp_reset_option_store,
};


static ssize_t hifi_dsp_dump_log_show(struct file *file, char __user *buf,
		size_t size, loff_t *ppos)
{
	ssize_t ret = 0;

	if(NULL == buf) {
		loge("Input param buf is invalid\n");
		return -EINVAL;
	}

	/*Do not create the /data/hisi_logs/running_trace/hifi_log/ folder*/
	/*and files within when not in internal beta phase*/
	if (EDITION_INTERNAL_BETA != bbox_check_edition()) {
		loge("Not internal beta, Do not dump hifi\n");
		return ret;
	}

	ret =  simple_read_from_buffer(buf, size, ppos,
			LOG_PATH_HIFI_LOG, (strlen(LOG_PATH_HIFI_LOG) + 1));
	if (!ret) {
		g_om_data.force_dump_log = true;
		up(&hifi_log_sema);
	}

	return ret;
}

static const struct file_operations hifi_dspdumplog_proc_ops = {
	.owner = THIS_MODULE,
	.read  = hifi_dsp_dump_log_show,
};
static void create_hifidebug_proc_file(void)
{
	struct proc_dir_entry *ent_debuglevel;
	struct proc_dir_entry *ent_dspdumplog;
	struct proc_dir_entry *ent_dspfaultinject;
	struct proc_dir_entry *poc_reset_option;


	/* Creating read/write "status" entry */
	ent_debuglevel = proc_create(HIFIDEBUG_LEVEL_PROC_FILE, S_IRUGO | S_IWUSR|S_IWGRP,
			hifi_debug_dir, &hifi_debug_proc_ops);
	ent_dspdumplog = proc_create(HIFIDEBUG_DSPDUMPLOG_PROC_FILE,
			S_IRUGO,hifi_debug_dir,
			&hifi_dspdumplog_proc_ops);
	if ((ent_debuglevel == NULL) || (ent_dspdumplog == NULL)){
		remove_proc_entry("hifidebug", 0);
		loge("create proc file fail\n");
		return ;
	}
	ent_dspfaultinject = proc_create(HIFIDEBUG_FAULTINJECT_PROC_FILE, S_IRUGO | S_IWUSR|S_IWGRP,
		hifi_debug_dir, &hifi_dspfaultinject_proc_ops);
	if (ent_dspfaultinject == NULL) {
		remove_proc_entry("hifidebug", 0);
		loge("create proc file fail\n");
	}

	poc_reset_option = proc_create(HIFIDEBUG_RESETOPTION_PROC_FILE, S_IRUGO|S_IWUSR|S_IWGRP,
		hifi_debug_dir, &hifi_reset_option_proc_ops);
	if (poc_reset_option == NULL) {
		remove_proc_entry("hifidebug", 0);
		loge("create proc file fail\n");
	}

}
static void remove_hifidebug_proc_file(void)
{
	remove_proc_entry(HIFIDEBUG_LEVEL_PROC_FILE, hifi_debug_dir);
	remove_proc_entry(HIFIDEBUG_DSPDUMPLOG_PROC_FILE, hifi_debug_dir);
	remove_proc_entry(HIFIDEBUG_FAULTINJECT_PROC_FILE, hifi_debug_dir);
	remove_proc_entry(HIFIDEBUG_RESETOPTION_PROC_FILE, hifi_debug_dir);
}

static void hifi_create_procfs(void)
{
#ifdef ENABLE_HIFI_DEBUG
	hifi_debug_dir = proc_mkdir(HIFIDEBUG_PATH, NULL);
	if (hifi_debug_dir == NULL) {
		loge("Unable to create /proc/hifidebug directory\n");
		return ;
	}
	create_hifidebug_proc_file();
#endif
}

static void hifi_remove_procfs(void)
{
#ifdef ENABLE_HIFI_DEBUG
	remove_hifidebug_proc_file();
	remove_proc_entry("hifidebug", 0);
#endif
}

static int hifi_dump_dsp_thread(void *p)
{
	#define HIFI_TIME_STAMP_1S	  32768
	#define HIFI_DUMPLOG_TIMESPAN (10 * HIFI_TIME_STAMP_1S)

	unsigned int exception_no = 0;
	unsigned int time_now = 0;
	unsigned int time_diff = 0;
	unsigned int* hifi_info_addr = NULL;
	unsigned int hifi_stack_addr = 0;
	int i;

	IN_FUNCTION;

	while (!kthread_should_stop()) {
		if (down_interruptible(&hifi_log_sema) != 0) {
			loge("hifi_dump_dsp_thread wake up err.\n");
		}
		time_now = (unsigned int)readl(g_om_data.dsp_time_stamp);
		time_diff = time_now - g_om_data.pre_dsp_dump_timestamp;
		g_om_data.pre_dsp_dump_timestamp = time_now;

		hifi_info_addr = (unsigned int*)ioremap_wc(DRV_DSP_STACK_TO_MEM, DRV_DSP_STACK_TO_MEM_SIZE);
		if (NULL == hifi_info_addr) {
			loge("dsp log ioremap_wc hifi_info_addr fail.\n");
			continue;
		}

		exception_no = *(unsigned int*)(hifi_info_addr + 3);
		hifi_stack_addr = *(unsigned int*)(hifi_info_addr + 4);
		logi("errno:%x pre_errno:%x is_first:%d is_force:%d time_diff:%d ms.\n", exception_no, g_om_data.pre_exception_no, g_om_data.first_dump_log, g_om_data.force_dump_log, (time_diff * 1000) / HIFI_TIME_STAMP_1S);

		hifi_get_time_stamp(g_om_data.cur_dump_time, HIFI_DUMP_FILE_NAME_MAX_LEN);

		if (exception_no < 40 && (exception_no != g_om_data.pre_exception_no)) {
			logi("panic addr:0x%x, cur_pc:0x%x, pre_pc:0x%x, cause:0x%x\n", *(unsigned int*)(hifi_info_addr), *(unsigned int*)(hifi_info_addr+1), *(unsigned int*)(hifi_info_addr+2), *(unsigned int*)(hifi_info_addr+3));
			for( i = 0; i < (DRV_DSP_STACK_TO_MEM_SIZE/2)/sizeof(int)/4; i+=4){
				logi("0x%x: 0x%08x 0x%08x 0x%08x 0x%08x\n", (hifi_stack_addr+i*4), *(hifi_info_addr+i),*(hifi_info_addr+1+i),*(hifi_info_addr+2+i),*(hifi_info_addr+i+3));
			}

			hifi_dump_dsp(PANIC_LOG);
			hifi_dump_dsp(PANIC_BIN);

			g_om_data.pre_exception_no = exception_no;
		} else if (g_om_data.first_dump_log || g_om_data.force_dump_log || time_diff > HIFI_DUMPLOG_TIMESPAN) {
			hifi_dump_dsp(NORMAL_LOG);
			if (DSP_LOG_BUF_FULL != g_om_data.dsp_error_type) {/*needn't dump bin when hifi log buffer full*/
				hifi_dump_dsp(NORMAL_BIN);
			}
			g_om_data.first_dump_log = false;
		}

		iounmap(hifi_info_addr);
		hifi_info_addr = NULL;
	}
	OUT_FUNCTION;
	return 0;
}

void hifi_dump_panic_log(void)
{
	/*Do not create the /data/hisi_logs/running_trace/hifi_log/ folder*/
	/*and files within when not in internal beta phase*/
	if (EDITION_INTERNAL_BETA != bbox_check_edition()) {
		loge("Not beta, Do not dump hifi\n");
		return;
	}

	if (!g_om_data.dsp_loaded) {
		loge("hifi isn't loaded, errno: 0x%x .\n" , g_om_data.dsp_loaded_sign);
		return;
	}
	up(&hifi_log_sema);
	return;
}

static bool hifi_check_img_loaded(void)
{
	bool dsp_loaded = false;
	unsigned int* img_loaded = (unsigned int*)ioremap_wc(DRV_DSP_LOADED_INDICATE, 0x4);
	if (NULL == img_loaded) {
		loge("remap hifi img loaded fail.\n");
		g_om_data.dsp_loaded_sign = 0xffffffff;
		return false;
	}
	g_om_data.dsp_loaded_sign = *img_loaded;

	if (0xA5A55A5A == g_om_data.dsp_loaded_sign) {
		loge("hifi img is not be loaded.\n");
	} else if (g_om_data.dsp_loaded_sign > 0) {
		loge("hifi img is loaded fail: 0x%x.\n", g_om_data.dsp_loaded_sign);
	} else {
		logi("hifi img be loaded.\n");
		dsp_loaded = true;
	}

	iounmap(img_loaded);

	return dsp_loaded;
}

bool hifi_is_loaded(void)
{
	if(!g_om_data.dsp_loaded) {
		loge("hifi isn't load, errno is 0x%x.\n", g_om_data.dsp_loaded_sign);
	}
	return g_om_data.dsp_loaded;
}

int hifi_dsp_dump_hifi(unsigned long arg)
{
	g_om_data.dsp_error_type = (unsigned int)arg;

	/*Do not create the /data/hisi_logs/running_trace/hifi_log/ folder*/
	/*and files within when not in internal beta phase*/
	if (EDITION_INTERNAL_BETA != bbox_check_edition()) {
		loge("Not internal beta, Do not dump hifi\n");
		return 0;
	}

	g_om_data.force_dump_log = true;
	up(&hifi_log_sema);

	return 0;
}

void hifi_om_init(struct platform_device *pdev, unsigned char* hifi_priv_base_virt, unsigned char* hifi_priv_base_phy)
{
	int i = 0;
	BUG_ON(NULL == pdev);

	BUG_ON(NULL == hifi_priv_base_virt);
	BUG_ON(NULL == hifi_priv_base_phy);

	memset(&g_om_data, 0, sizeof(struct hifi_om_s));

	g_om_data.dev = &pdev->dev;
	g_om_data.debug_level = 2; /*info level*/
	g_om_data.reset_system = false;

	g_om_data.dsp_time_stamp = (unsigned int*)ioremap(SYS_TIME_STAMP_REG, 0x4);
	if (NULL == g_om_data.dsp_time_stamp) {
		printk("time stamp reg ioremap Error.\n");//can't use logx
		return;
	}

	g_om_data.dsp_loaded = hifi_check_img_loaded();

	IN_FUNCTION;

	g_om_data.dsp_debug_level = 2; /*info level*/
	g_om_data.first_dump_log = true;

	g_om_data.dsp_panic_mark = (unsigned int*)(hifi_priv_base_virt + (DRV_DSP_PANIC_MARK - HIFI_BASE_ADDR));
	g_om_data.dsp_bin_addr = (char*)(hifi_priv_base_virt + (HIFI_DUMP_BIN_ADDR - HIFI_BASE_ADDR));
	g_om_data.dsp_exception_no = (unsigned int*)(hifi_priv_base_virt + (DRV_DSP_EXCEPTION_NO - HIFI_BASE_ADDR));
	g_om_data.dsp_log_cur_addr = (unsigned int*)(hifi_priv_base_virt + (DRV_DSP_UART_TO_MEM_CUR_ADDR - HIFI_BASE_ADDR));
	g_om_data.dsp_log_addr = NULL;
	*g_om_data.dsp_log_cur_addr = DRV_DSP_UART_TO_MEM_RESERVE_SIZE;

	g_om_data.dsp_debug_level_addr = (unsigned int*)(hifi_priv_base_virt + (DRV_DSP_UART_LOG_LEVEL - HIFI_BASE_ADDR));
	g_om_data.dsp_debug_kill_addr = (unsigned int*)(hifi_priv_base_virt + (DRV_DSP_KILLME_ADDR - HIFI_BASE_ADDR));

	*(g_om_data.dsp_exception_no) = ~0;
	g_om_data.pre_exception_no = ~0;

	s_dsp_dump_info[NORMAL_BIN].data_addr = g_om_data.dsp_bin_addr;
	s_dsp_dump_info[PANIC_BIN].data_addr  = g_om_data.dsp_bin_addr;

	hifi_set_dsp_debug_level(g_om_data.dsp_debug_level);

	sema_init(&g_om_data.dsp_dump_sema, 1);

	g_om_data.kdumpdsp_task = kthread_create(hifi_dump_dsp_thread, 0, "dspdumplog");
	if (IS_ERR(g_om_data.kdumpdsp_task)) {
		loge("creat hifi dump log thread fail.\n");
	} else {
		wake_up_process(g_om_data.kdumpdsp_task);
	}

	hifi_create_procfs();

	for (i = 0; i < ARRAY_SIZE(work_info); i++) {
		work_info[i].ctl.wq = create_singlethread_workqueue(work_info[i].work_name);
		if (!work_info[i].ctl.wq) {
			pr_err("%s(%u):workqueue create failed!\n", __FUNCTION__, __LINE__);
		} else {
			INIT_WORK(&work_info[i].ctl.work, work_info[i].func);
			spin_lock_init(&work_info[i].ctl.lock);
			INIT_LIST_HEAD(&work_info[i].ctl.list);
		}
	}

	OUT_FUNCTION;
	return;
}

void hifi_om_deinit(struct platform_device *dev)
{
	int i = 0;

	IN_FUNCTION;

	BUG_ON(NULL == dev);

	up(&g_om_data.dsp_dump_sema);
	kthread_stop(g_om_data.kdumpdsp_task);

	if (NULL != g_om_data.dsp_time_stamp) {
		iounmap(g_om_data.dsp_time_stamp);
		g_om_data.dsp_time_stamp = NULL;
	}

	if (NULL != g_om_data.dsp_log_addr) {
		iounmap(g_om_data.dsp_log_addr);
		g_om_data.dsp_log_addr = NULL;
	}

	hifi_remove_procfs();

	for (i = 0; i < ARRAY_SIZE(work_info); i++) {
		if (work_info[i].ctl.wq) {
			flush_workqueue(work_info[i].ctl.wq);
			destroy_workqueue(work_info[i].ctl.wq);
			work_info[i].ctl.wq = NULL;
		}
	}

	OUT_FUNCTION;

	return;
}


void hifi_om_cpu_load_info_show(struct hifi_om_load_info_stru *hifi_om_info)
{
	switch (hifi_om_info->info_type) {
	case HIFI_CPU_LOAD_VOTE_UP:
	case HIFI_CPU_LOAD_VOTE_DOWN:
		logi("CpuUtilization:%d%%, Vote DDR to %dM\n", hifi_om_info->cpu_load_info.cpu_load, hifi_om_info->cpu_load_info.ddr_freq);
		break;

	case HIFI_CPU_LOAD_LACK_PERFORMANCE:
		logw("DDRFreq: %dM, CpuUtilization:%d%%, Lack of performance!!!\n", hifi_om_info->cpu_load_info.ddr_freq,hifi_om_info->cpu_load_info.cpu_load);
		/*upload totally 16 times in every 16 times in case of flushing msg*/
		if (unlikely((dsm_notify_limit <= 0x100) && (dsm_notify_limit & 0xF))) {
			if (!dsm_client_ocuppy(dsm_audio_client)) {
				dsm_client_record(dsm_audio_client, "DSM_SOC_HIFI_HIGH_CPU\n");
				dsm_client_notify(dsm_audio_client, DSM_SOC_HIFI_HIGH_CPU);
			}
		}
		dsm_notify_limit++;
		break;

	default:
		break;
	}
}

void hifi_om_effect_mcps_info_show(struct hifi_om_effect_mcps_stru *hifi_mcps_info)
{
	unsigned int i;

	logw("DDRFreq: %dM, CpuUtilization:%d%%\n",hifi_mcps_info->cpu_load_info.ddr_freq, hifi_mcps_info->cpu_load_info.cpu_load);

	for(i = 0; i < (sizeof(hifi_mcps_info->effect_mcps_info)/sizeof(hifi_effect_mcps_stru)); i++) {
		if (hifi_mcps_info->effect_mcps_info[i].effect_algo_id < ID_EFFECT_ALGO_BUTT && hifi_mcps_info->effect_mcps_info[i].effect_algo_id > ID_EFFECT_ALGO_START) {
			switch (hifi_mcps_info->effect_mcps_info[i].effect_stream_id) {
			case AUDIO_STREAM_PCM_OUTPUT:
				logw("Algorithm: %s, Mcps: %d, Stream: PCM_OUTPUT \n",
					effect_algo[hifi_mcps_info->effect_mcps_info[i].effect_algo_id - 1].effect_name,
					hifi_mcps_info->effect_mcps_info[i].effect_algo_mcps);
				break;

			case AUDIO_STREAM_PLAYER_OUTPUT:
				logw("Algorithm: %s, Mcps: %d, Stream: PLAYER_OUTPUT \n",
					effect_algo[hifi_mcps_info->effect_mcps_info[i].effect_algo_id - 1].effect_name,
					hifi_mcps_info->effect_mcps_info[i].effect_algo_mcps);
				break;

			case AUDIO_STREAM_MIXER_OUTPUT:
				logw("Algorithm: %s, Mcps: %d, Stream: MIXER_OUTPUT \n",
					effect_algo[hifi_mcps_info->effect_mcps_info[i].effect_algo_id - 1].effect_name,
					hifi_mcps_info->effect_mcps_info[i].effect_algo_mcps);
				break;

			case AUDIO_STREAM_VOICE_OUTPUT:
				logw("Algorithm: %s, Mcps: %d, Stream: VOICE_OUTPUT \n",
					effect_algo[hifi_mcps_info->effect_mcps_info[i].effect_algo_id - 1].effect_name,
					hifi_mcps_info->effect_mcps_info[i].effect_algo_mcps);
				break;

			case AUDIO_STREAM_VOICEPP_OUTPUT:
				logw("Algorithm: %s, Mcps: %d, Stream: VOICEPP_OUTPUT \n",
					effect_algo[hifi_mcps_info->effect_mcps_info[i].effect_algo_id- 1].effect_name,
					hifi_mcps_info->effect_mcps_info[i].effect_algo_mcps);
				break;

			case AUDIO_STREAM_PCM_INPUT:
				logw("Algorithm: %s, Mcps: %d, Stream: PCM_INPUT \n",
					effect_algo[hifi_mcps_info->effect_mcps_info[i].effect_algo_id - 1].effect_name,
					hifi_mcps_info->effect_mcps_info[i].effect_algo_mcps);
				break;

			case AUDIO_STREAM_VOICE_INPUT:
				logw("Algorithm: %s, Mcps: %d, Stream: VOICE_INPUT \n",
					effect_algo[hifi_mcps_info->effect_mcps_info[i].effect_algo_id - 1].effect_name,
					hifi_mcps_info->effect_mcps_info[i].effect_algo_mcps);
				break;

			case AUDIO_STREAM_VOICEPP_INPUT:
				logw("Algorithm: %s, Mcps: %d, Stream: VOICEPP_INPUT \n",
					effect_algo[hifi_mcps_info->effect_mcps_info[i].effect_algo_id - 1].effect_name,
					hifi_mcps_info->effect_mcps_info[i].effect_algo_mcps);
				break;

			default:
				break;
			}
		}
	}
}

void hifi_om_update_buff_delay_info_show(struct hifi_om_update_buff_delay_info *info)
{
	static unsigned int dsm_update_buff_delay_cnt = 0;
	logw("Hifi continuous update play/capture buff delay : %d(0-play, 1-capture)\n", info->pcm_mode);
	if (0 == (dsm_update_buff_delay_cnt % 8)) {
		if (!dsm_client_ocuppy(dsm_audio_client)) {
			dsm_client_record(dsm_audio_client, "update play or capture buff delay\n");
			dsm_client_notify(dsm_audio_client, DSM_SOC_HIFI_UPDATE_BUFF_DELAY);
		}
	}
	dsm_update_buff_delay_cnt++;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
