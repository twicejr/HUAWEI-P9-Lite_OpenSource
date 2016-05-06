/*
 * audio soc rdr.
 *
 * Copyright (c) 2015 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/kernel.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/kthread.h>
#include <linux/thread_info.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>

#include <linux/hisi/util.h>
#include <linux/hisi/rdr_hisi_ap_hook.h>
#include <linux/interrupt.h>
#include <linux/hisi/hisi_rproc.h>
#include <linux/delay.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/clk.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/kmod.h>
#include <linux/proc_fs.h>
#include <linux/sysctl.h>
#include <linux/uaccess.h>
#include <linux/wakelock.h>
#include "rdr_print.h"
#include "rdr_inner.h"
#include "rdr_field.h"
#include "load_image.h"

#include "rdr_hisi_audio_adapter.h"
#include "rdr_hisi_audio_soc.h"

#include "hifi_lpp.h"
#include <dsm/dsm_pub.h>


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*lint -e750*/
#define RDR_HIFI_DUMP_ADDR				(HIFI_DUMP_BIN_ADDR)
#define RDR_HIFI_DUMP_SIZE				(HIFI_DUMP_BIN_SIZE)
#define RDR_COMMENT_LEN					(128)

#define HIFI_BSS_SEC					(2)
#define SOC_HIFI_MODID					(0x84000000)
#define SOC_WDT_TIMEOUT_IRQ_NUM			(245)
#define OM_SOC_LOG_PATH					"sochifi_logs"

#define DRV_WATCHDOG_BASE_ADDR          (0xe804d000)
#define DRV_WATCHDOG_CONTROL            (DRV_WATCHDOG_BASE_ADDR + 0x008)
#define DRV_WATCHDOG_INTCLR             (DRV_WATCHDOG_BASE_ADDR + 0x00C)
#define DRV_WATCHDOG_LOCK               (DRV_WATCHDOG_BASE_ADDR + 0xC00)
#define DRV_WATCHDOG_UNLOCK_NUM	        (0x1ACCE551)
#define DRV_WATCHDOG_LOCK_NUM           (0x0)
#define DRV_WATCHDOG_CONTROL_DISABLE    (0x0)
#define DRV_WATCHDOG_INTCLR_NUM         (0x4455) /* Generally speaking, any number is okay */

#define HIFI_DIE_NOTIFY_LPM3			((0 << 24) | (16 << 16) | (3 << 8) | (1 << 0))
										/*	bit 24-31 OBJ_AP
											bit 16-23 OBJ_PSCI
											bit 8-15  CMD_SETTING
											bit 0-7   TYPE_POWER */

#define CFG_DSP_NMI                     (0x3C)               /*DSP NMI ,bit0-bit15*/
#define CFG_MMBUF_REMAP_EN              (0x130)              /*mmbuf remap enable，9bit*/
#define CFG_OCRAM_REMAP_EN              (0x13C)              /*ocram remap enable，9bit*/
#define ASP_CFG_BASE                    (0xE804E000)

struct rdr_soc_des_s {
	u32   modid;
	char *pathname;
	u32  *control_addr;
	u32  *lock_addr;
	u32  *intclr_addr;
	pfn_cb_dump_done dumpdone_cb;

	struct semaphore dump_sem;
	struct semaphore handler_sem;
	struct wake_lock rdr_wl;
	struct task_struct *kdump_task;
	struct task_struct *khandler_task;
};
static struct rdr_soc_des_s soc_des;

static void hisi_rdr_nmi_notify_hifi(void)
{
	unsigned int value;
	void __iomem *rdr_aspcfg_base = NULL;

	rdr_aspcfg_base = ioremap(ASP_CFG_BASE, SZ_4K);
	if (!rdr_aspcfg_base) {
		BB_PRINT_ERR("%s():rdr_aspcfg_base ioremap error\n", __func__);
		return;
	}

	value = readl(rdr_aspcfg_base + CFG_DSP_NMI);
	value &= ~(0x1 << 0);
	writel(value, (rdr_aspcfg_base + CFG_DSP_NMI));

	value |= (0x1 << 0);
	writel(value, (rdr_aspcfg_base + CFG_DSP_NMI));

	iounmap(rdr_aspcfg_base);
	rdr_aspcfg_base = NULL;

	BB_PRINT_PN("%s\n", __func__);
	return;
}

static void hisi_rdr_remap_init(void)
{
	void __iomem *rdr_aspcfg_base = NULL;

	rdr_aspcfg_base = ioremap(ASP_CFG_BASE, SZ_4K);
	if (!rdr_aspcfg_base) {
		BB_PRINT_ERR("%s():rdr_aspcfg_base ioremap error\n", __func__);
		return;
	}

	if (readl(rdr_aspcfg_base + CFG_MMBUF_REMAP_EN) & (0x1<<9))
		writel(0x0, (rdr_aspcfg_base + CFG_MMBUF_REMAP_EN));

	if (readl(rdr_aspcfg_base + CFG_OCRAM_REMAP_EN) & (0x1<<9))
		writel(0x0, (rdr_aspcfg_base + CFG_OCRAM_REMAP_EN));

	iounmap(rdr_aspcfg_base);
	rdr_aspcfg_base = NULL;

	BB_PRINT_PN("%s\n", __func__);
	return;
}

static bool is_dsp_power_on(void)
{
	unsigned int *power_status_addr = NULL;
	unsigned int power_status = 0;
	bool is_power_on = false;

	power_status_addr = (unsigned int *)ioremap_wc(DRV_DSP_POWER_STATUS_ADDR, 0x4);
	if (NULL == power_status_addr) {
		BB_PRINT_ERR("%s():DRV_DSP_POWER_STATUS_ADDR ioremap failed\n", __func__);
		return false;
	}

	power_status = readl(power_status_addr);
	if (DRV_DSP_POWER_ON == power_status)
		is_power_on = true;
	else if (DRV_DSP_POWER_OFF == power_status)
		is_power_on = false;
	else
		BB_PRINT_ERR("Get dsp power status error.[0x%x]\n", power_status);

	iounmap(power_status_addr);
	power_status_addr = NULL;

	return is_power_on;
}

static bool is_nmi_complete(void)
{
	unsigned int *nmi_flag_addr = NULL;
	bool is_complete = false;

	nmi_flag_addr = (unsigned int *)ioremap_wc(DRV_DSP_NMI_FLAG_ADDR, 0x4);
	if (NULL == nmi_flag_addr) {
		BB_PRINT_ERR("%s():DRV_DSP_NMI_FLAG_ADDR ioremap failed\n", __func__);
		return false;
	}

	if (DRV_DSP_NMI_COMPLETE == readl(nmi_flag_addr))
		is_complete = true;
	else
		is_complete = false;

	iounmap(nmi_flag_addr);
	nmi_flag_addr = NULL;

	return is_complete;
}

static int dump_hifi_ddr(char *filepath)
{
	char *buf = NULL;
	char *full_text = NULL;
	int ret = 0;
	char xn[RDR_FNAME_LEN] = {0};
	char comment[RDR_COMMENT_LEN] = {0};
	int count = 0;

	if (NULL == filepath) {
		BB_PRINT_ERR("%s error: filepath is NULL\n", __func__);
		return -ENOENT;
	}

	while (count < 10) {
		if (is_nmi_complete()) {
			break;
		} else {
			count++;
			msleep(1);
		}
	}

	if (10 == count) {
		BB_PRINT_ERR("NMI process is uncomplete in hifi, om log maybe inaccurate\n");
		snprintf(comment, RDR_COMMENT_LEN, "NMI process is uncomplete in hifi, OM log maybe inaccurate");
	} else {
		snprintf(comment, RDR_COMMENT_LEN, "OM log is fine.");
	}

	snprintf(xn, RDR_FNAME_LEN, "%s%s/hifi_ddr.bin", filepath, OM_SOC_LOG_PATH); /* [false alarm]: RDR_FNAME_LEN As expected */

	buf = (char *)ioremap_wc(RDR_HIFI_DUMP_ADDR, RDR_HIFI_DUMP_SIZE);
	if (!buf) {
		BB_PRINT_ERR("%s error: ioremap hifi dump addr fail\n", __func__);
		return -ENOMEM;
	}

	full_text = vmalloc((size_t)(RDR_HIFI_DUMP_SIZE + RDR_COMMENT_LEN));
	if (NULL == full_text) {
		BB_PRINT_ERR("%s error: alloc full_text failed\n", __func__);
		ret = -ENOMEM;
		goto error;
	}

	memcpy(full_text, comment, RDR_COMMENT_LEN);
	memcpy(full_text + RDR_COMMENT_LEN, buf, RDR_HIFI_DUMP_SIZE);

	ret = rdr_audio_write_file(xn, full_text, RDR_HIFI_DUMP_SIZE + RDR_COMMENT_LEN);
	if (ret)
		BB_PRINT_ERR("rdr:dump %s fail\n", xn);

	vfree(full_text);
	full_text = NULL;
error:
	iounmap(buf);
	buf = NULL;

	return ret;
}

static int save_icc_channel_fifo(void)
{
	int i = 0;
	struct icc_channel_fifo *dst_fifo = NULL;
	struct icc_channel_fifo *src_fifo = NULL;
	struct icc_dbg *icc_dbg_info = NULL;

	icc_dbg_info = (struct icc_dbg *)ioremap_wc(HIFI_ICC_DEBUG_LOCATION, HIFI_ICC_DEBUG_SIZE);
	if (!icc_dbg_info) {
		BB_PRINT_ERR("%s(): ioremap hifi icc_dbg_info fail\n", __func__);
		return -ENOMEM;
	}

	if ((ICC_DEBUG_PROTECT_WORD1 != icc_dbg_info->protectword1)
		|| (ICC_DEBUG_PROTECT_WORD2 != icc_dbg_info->protectword2)) {
		BB_PRINT_ERR("%s(): check ICC_DEBUG_PROTECT_WORD fail [0x%x, 0x%x], do not save icc fifo\n",
			__func__, icc_dbg_info->protectword1, icc_dbg_info->protectword2);
		iounmap(icc_dbg_info);
		icc_dbg_info = NULL;
		return -EINVAL;
	}

	for (i = 0; i < 2; i++) {
		struct icc_channel *channel = &icc_dbg_info->icc_channels[i];
		/* 保存接收fifo */
		if (0 != channel->fifo_recv) {
			dst_fifo = (struct icc_channel_fifo *)(((char *)&(channel->fifo_recv)) + *(unsigned int *)(&channel->fifo_recv));
			src_fifo = (struct icc_channel_fifo *)ioremap_wc(*((unsigned int *)dst_fifo->data), dst_fifo->size + sizeof(struct icc_channel_fifo));
			if (!src_fifo) {
				BB_PRINT_ERR("rdr: remap hifi recv src_fifo fail\n");
				iounmap(icc_dbg_info);
				icc_dbg_info = NULL;
				return -ENOMEM;
			}
			/* 拷贝fifo通道数据 */
			memcpy((void *)((char *)dst_fifo + sizeof(struct icc_channel_fifo)), (void *)((char *)src_fifo + sizeof(struct icc_channel_fifo)), dst_fifo->size);
			/* 更新Fifo头信息 */
			dst_fifo->magic = src_fifo->magic;
			dst_fifo->read  = src_fifo->read;
			dst_fifo->write = src_fifo->write;
			iounmap(src_fifo);
			src_fifo = NULL;
		}

		/* 保存发送fifo */
		if (0 != channel->fifo_send) {
			dst_fifo = (struct icc_channel_fifo *)((char *)&(channel->fifo_send) + *(unsigned int *)(&channel->fifo_send));
			src_fifo = (struct icc_channel_fifo *)ioremap_wc(*((unsigned int *)dst_fifo->data), dst_fifo->size + sizeof(struct icc_channel_fifo));

			if (!src_fifo) {
				BB_PRINT_ERR("rdr: remap hifi send src_fifo fail\n");
				iounmap(icc_dbg_info);
				icc_dbg_info = NULL;
				return -ENOMEM;
			}
			/* 拷贝fifo通道数据 */
			memcpy((void *)((char *)dst_fifo + sizeof(struct icc_channel_fifo)), (void *)((char *)src_fifo + sizeof(struct icc_channel_fifo)), dst_fifo->size);
			/* 更新Fifo头信息 */
			dst_fifo->magic = src_fifo->magic;
			dst_fifo->read = src_fifo->read;
			dst_fifo->write = src_fifo->write;

			iounmap(src_fifo);
			src_fifo = NULL;
		}
	}
	iounmap(icc_dbg_info);
	icc_dbg_info = NULL;

	return 0;
}


extern struct dsm_client *dsm_audio_client;
static void dump_hifi(char *filepath)
{
	int ret = 0;

	BUG_ON(NULL == filepath);

	ret = save_icc_channel_fifo();
	BB_PRINT_PN("rdr:%s()save_icc_channel_fifo,%s\n", __func__, ret ? "fail" : "success");

	ret = dump_hifi_ddr(filepath);
	BB_PRINT_PN("rdr:%s():dump hifi ddr, %s\n", __func__, ret ? "fail" : "success");

	if ((!dsm_client_ocuppy(dsm_audio_client)) &&
		(soc_des.modid != RDR_MODEM_CP_MOD_ID) && (soc_des.modid != RDR_MODEM_CP_RESET_3RD_MOD_ID)) {
		dsm_client_record(dsm_audio_client, "DSM_SOC_HIFI_RESET\n");
		dsm_client_notify(dsm_audio_client, DSM_SOC_HIFI_RESET);
	}

	return;
}

static int reset_hifi_sec(void)
{
	struct drv_hifi_sec_ddr_head *head;
	char *sec_head = NULL;
	char *sec_addr = NULL;
	int i;
	int ret = 0;

	sec_head = (char *)ioremap_wc(HIFI_SEC_HEAD_BACKUP, HIFI_SEC_HEAD_SIZE);
	if (!sec_head) {
		ret = -ENOMEM;
		goto error;
	}
	head = (struct drv_hifi_sec_ddr_head *)sec_head;

	BB_PRINT_PN("sections_num = 0x%x\n", head->sections_num);

	for (i = 0; i < head->sections_num; i++) {
		if (head->sections[i].type == HIFI_BSS_SEC) {
			BB_PRINT_PN("sec_id = %d, type = 0x%x, src_addr = 0x%x, des_addr = 0x%x, size = %d\n",
					i,
					head->sections[i].type,
					head->sections[i].src_addr,
					head->sections[i].des_addr,
					head->sections[i].size);
			sec_addr = (char *)ioremap_wc(head->sections[i].des_addr,
							head->sections[i].size);
			if (NULL == sec_addr) {
				ret = -ENOMEM;
				goto error1;
			}

			memset(sec_addr, 0x0, head->sections[i].size);
			iounmap(sec_addr);
			sec_addr = NULL;
		}
	}

error1:
	iounmap(sec_head);
	sec_head = NULL;
error:
	return ret;
}

static int dump_thread(void *arg)
{
	BB_PRINT_START();

	while (!kthread_should_stop()) {
		if (down_interruptible(&soc_des.dump_sem)) {
			BB_PRINT_ERR("dump_thread down sem fail\n");
			continue;
		}

		BB_PRINT_DBG("begin to dump soc hifi log\n");
		dump_hifi(soc_des.pathname);
		BB_PRINT_DBG("end dump soc hifi log\n");

		if (soc_des.dumpdone_cb) {
			BB_PRINT_DBG("begin dump soc hifi done callback, modid: 0x%x\n", soc_des.modid);
			soc_des.dumpdone_cb(soc_des.modid, RDR_HIFI);
			BB_PRINT_DBG("end dump soc hifi done callback\n");
		}
	}

	BB_PRINT_END();

	return 0;
}

static int irq_handler_thread(void *arg)
{
	char hifi_dump_path[PATH_MAXLEN];

	BB_PRINT_START();

	while (!kthread_should_stop()) {
		if (down_interruptible(&soc_des.handler_sem)) {
			BB_PRINT_ERR("irq_handler_thread down sem fail\n");
			continue;
		}

		BB_PRINT_PN("%s():sochifi watchdog coming\n", __func__);

		if (is_dsp_power_on()) {
			hisi_rdr_nmi_notify_hifi();
			hisi_rdr_remap_init();
		} else {
			BB_PRINT_ERR("hifi is power off, do not send nmi & remap\n");
		}

		hifireset_runcbfun(DRV_RESET_CALLCBFUN_RESET_BEFORE);

		snprintf(hifi_dump_path, PATH_MAXLEN, "%s%s-%08lld/", PATH_ROOT, rdr_get_timestamp(), rdr_get_tick());

		dump_hifi(hifi_dump_path);

		BB_PRINT_PN("enter rdr process for sochifi watchdog\n");
		rdr_system_error(SOC_HIFI_MODID, 0, 0);
		BB_PRINT_PN("exit rdr process for sochifi watchdog\n");
	}

	BB_PRINT_END();

	return 0;
}

void rdr_audio_soc_dump(u32 modid, char *pathname, pfn_cb_dump_done pfb)
{
	BUG_ON(NULL == pathname);
	BUG_ON(NULL == pfb);

	BB_PRINT_START();

	soc_des.modid = modid;
	soc_des.dumpdone_cb = pfb;
	soc_des.pathname = pathname;

	up(&soc_des.dump_sem);

	BB_PRINT_END();

	return;
}

static int hisi_rdr_ipc_notify_lpm3(u32 *msg, unsigned long len)
{
	int ret = 0;
	unsigned long i;

	for (i = 0; i < len; i++)
		BB_PRINT_PN("rdr:[ap2lpm3 notifiy] msg[%lu] = 0x%x\n", i, msg[i]);

	ret = RPROC_ASYNC_SEND(HISI_RPROC_LPM3_MBX17, msg, len);
	if (ret)
		BB_PRINT_ERR("%s(): send mesg to lpm3 fail\n", __func__);

	return ret;
}

static int reset_hifi(void)
{
	unsigned int *hifi_power_status_addr = NULL;
	unsigned int msg = 0xdead;
	int ret = 0;

	BB_PRINT_START();

	hifi_power_status_addr = ioremap_wc(DRV_DSP_POWER_STATUS_ADDR, 0x4);
	if (NULL == hifi_power_status_addr) {
		BB_PRINT_ERR("%s():DRV_DSP_POWER_STATUS_ADDR ioremap failed\n", __func__);
	} else {
		writel(DRV_DSP_POWER_OFF, hifi_power_status_addr);
		iounmap(hifi_power_status_addr);
		hifi_power_status_addr = NULL;
	}

	msg = HIFI_DIE_NOTIFY_LPM3;
	ret = hisi_rdr_ipc_notify_lpm3(&msg, 1);
	BB_PRINT_PN("rdr:%s(): power off hifi %s\n", __func__, ret ? "fail" : "success\n");

	BB_PRINT_END();

	return ret;
}

/*Link used for hifi reset*/
struct sreset_mgr_lli *g_pmgr_hifireset_data;

/*****************************************************************************
 函 数 名  : reset_link_insert
 功能描述  : 将数据插入链表
 输入参数  :
			struct sreset_mgr_lli *plink, 链表指针
			struct sreset_mgr_lli *punit，待插入的节点指针
 输出参数  : 无
 返 回 值  : int
*****************************************************************************/
struct sreset_mgr_lli *reset_link_insert(struct sreset_mgr_lli *plink, struct sreset_mgr_lli *punit)
{
	struct sreset_mgr_lli *phead = plink;
	struct sreset_mgr_lli *ppose = plink;
	struct sreset_mgr_lli *ptail = plink;

	if (NULL == plink || NULL == punit) {
		BB_PRINT_ERR("%s: input params are not legitimate\n", __func__);
		return NULL;
	}

	while (NULL != ppose) {
		/*根据优先级插入到链表中*/
		if (ppose->cbfuninfo.priolevel > punit->cbfuninfo.priolevel) {
			if (phead == ppose) {
				punit->pnext = ppose;
				phead = punit;
			} else {
				ptail->pnext = punit;
				punit->pnext = ppose;
			}
			break;
		}
		ptail = ppose;
		ppose = ppose->pnext;
	}

	if (NULL == ppose)
		ptail->pnext = punit;

	return phead;
}

/*****************************************************************************
 函 数 名  : reset_do_regcbfunc
 功能描述  : 用于其它组件注册回调函数，处理Modem复位前后相关数据。
 输入参数  :
			struct sreset_mgr_lli *plink,管理链表，注意，允许为空.
			const char *pname, 组件注册的名字
			pdrv_reset_cbfun cbfun,    组件注册的回调函数
			int userdata,组件的私有数据
			Int Priolevel, 回调函数调用优先级 0-49，其中0-9 保留。
 输出参数  : 无
 返 回 值  : int
*****************************************************************************/
struct sreset_mgr_lli *reset_do_regcbfunc(struct sreset_mgr_lli *plink, const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel)
{
	struct sreset_mgr_lli  *phead = plink;
	struct sreset_mgr_lli  *pmgr_unit = NULL;

	/*判断入参是否合法，不合法返回错误*/
	if ((NULL == pname)
		|| (NULL == pcbfun)
		|| (priolevel < RESET_CBFUNC_PRIO_LEVEL_LOWT || priolevel > RESET_CBFUNC_PRIO_LEVEL_HIGH)) {
		BB_PRINT_ERR("fail in ccore reset regcb,fail, name 0x%s, cbfun 0x%p, prio %d\n", pname, pcbfun, priolevel);
		return NULL;
	}

	/*分配空间*/
	pmgr_unit = kmalloc(sizeof(*pmgr_unit), GFP_KERNEL);
	if (NULL != pmgr_unit) {
		memset((void *)pmgr_unit, 0, (sizeof(*pmgr_unit)));
		/*赋值*/
		strncpy(pmgr_unit->cbfuninfo.name, pname, DRV_MODULE_NAME_LEN);
		pmgr_unit->cbfuninfo.priolevel = priolevel;
		pmgr_unit->cbfuninfo.userdata = userdata;
		pmgr_unit->cbfuninfo.cbfun = pcbfun;
	} else {
		BB_PRINT_ERR("pmgr_unit malloc fail!\n");
		return NULL;
	}

	/*第一次调用该函数，链表为空*/
	if (NULL == phead) {
		phead = pmgr_unit;
	} else {
	/*根据优先级插入链表*/
		phead = reset_link_insert(phead, pmgr_unit);
	}

	return phead;
}

#ifdef CONFIG_HISI_HIFI_BB
/*****************************************************************************
 函 数 名  : hifireset_regcbfunc
 功能描述  : 用于其它组件注册回调函数，处理HIFI复位前后相关数据。
 输入参数  :
			const char *pname, 组件注册的名字
			pdrv_reset_cbfun cbfun,    组件注册的回调函数
			int userdata,组件的私有数据
			Int Priolevel, 回调函数调用优先级 0-49，其中0-9 保留。
 输出参数  : 无
 返 回 值  : int
*****************************************************************************/
int hifireset_regcbfunc(const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel)
{
	g_pmgr_hifireset_data = reset_do_regcbfunc(g_pmgr_hifireset_data, pname, pcbfun, userdata, priolevel);
	BB_PRINT_PN("%s registered a cbfun for hifi reset\n", pname);

	return 0;
}
#endif /* end of CONFIG_HISI_HIFI_BB */

/*****************************************************************************
 函 数 名  :  hifireset_doruncbfun
 功能描述  : HIFI复位前后调用回调函数的函数。由于圈复杂度超标，所以这里封装函数
 输入参数  : enum DRV_RESET_CALLCBFUN_MOMENT eparam, 0 表示HIFI复位前；非零表示复位后。

 输出参数  : 无
 返 回 值  : 0, 成功，非0，失败
*****************************************************************************/
int hifireset_doruncbfun(const char *pname, enum DRV_RESET_CALLCBFUN_MOMENT eparam)
{
	int  iresult = BSP_RESET_OK;
	struct sreset_mgr_lli  *phead = g_pmgr_hifireset_data;

	BUG_ON(NULL == pname);

	/*不判断模块名字,按顺序执行*/
	if (strcmp(pname, RESET_CBFUN_IGNORE_NAME) == 0) {
		while (NULL != phead) {
			if (NULL != phead->cbfuninfo.cbfun) {
				iresult = phead->cbfuninfo.cbfun(eparam, phead->cbfuninfo.userdata);

				if (BSP_RESET_OK != iresult) {
					/*如果返回失败，记录下组件名字,返回值*/
					BB_PRINT_ERR("fail to run cbfun of %s, at %d return %d\n", phead->cbfuninfo.name, eparam, iresult);
					break;
				}
				BB_PRINT_PN("run %s cb function 0x%p\n", phead->cbfuninfo.name, phead->cbfuninfo.cbfun);
			}
			phead = phead->pnext;
		}
	} else {
	/*需要判断模块名字，执行指定的回调函数*/
		while (NULL != phead) {
			if (strcmp(pname, phead->cbfuninfo.name) == 0
				&& NULL != phead->cbfuninfo.cbfun) {
				iresult  = phead->cbfuninfo.cbfun(eparam, phead->cbfuninfo.userdata);
				BB_PRINT_PN("run %s cb function 0x%p\n", phead->cbfuninfo.name, phead->cbfuninfo.cbfun);
				break;
			}
			phead = phead->pnext;
		}
	}

	if (BSP_RESET_OK != iresult) {
		if (NULL != phead) {
			BB_PRINT_ERR("fail to run cbfun of %s, at %d, return %d\n", phead->cbfuninfo.name, eparam, iresult);
		} else {
			BB_PRINT_ERR("fail to run cbfun, but phead or pname is null\n");
		}
	}

	return iresult;
}

/*****************************************************************************
 函 数 名  :  hifireset _runcbfun
 功能描述  : HIFI复位前后调用回调函数的函数。
 输入参数  : enum DRV_RESET_CALLCBFUN_MOMENT eparam, 0 表示HIFI复位前；非零表示复位后。

 输出参数  : 无
 返 回 值  : 0, 成功，非0，失败
*****************************************************************************/
int hifireset_runcbfun(enum DRV_RESET_CALLCBFUN_MOMENT eparam)
{
	int  iresult = 0;

	if (DRV_RESET_CALLCBFUN_RESET_BEFORE == eparam) {
		/*遍历回调函数链表，调用NAS的回调*/
		iresult = hifireset_doruncbfun("NAS_AT", eparam);
		if (BSP_RESET_OK != iresult) {
			/*如果返回失败，记录下组建name, 返回值，保存到文件*/
			goto return_error;
		}
	} else {
		/*遍历回调函数链表，调用回调函数*/
		iresult = hifireset_doruncbfun(RESET_CBFUN_IGNORE_NAME, eparam);
		if (BSP_RESET_OK != iresult)
			goto return_error;
	}
	BB_PRINT_PN("end of run cb functions for hifi reset at %d, %d\n", eparam, iresult);
	return BSP_RESET_OK;
return_error:
	return BSP_RESET_ERROR;
}

void rdr_audio_soc_reset(u32 modid, u32 etype, u64 coreid)
{
	int ret = 0;

	BB_PRINT_START();

	ret = bsp_reset_loadimage(BSP_HIFI);
	if (ret) {
		wake_unlock(&soc_des.rdr_wl);
		BB_PRINT_ERR("rdr:%s(): image seccheck fail\n", __func__);
		/* todo : check secimage fail, need reboot */
		return;
	}

	ret = reset_hifi_sec();
	BB_PRINT_PN("rdr:%s():reset hifi sec,%s\n", __func__, ret ? "fail" : "success\n");

	ret = reset_hifi();
	if (ret) {
		wake_unlock(&soc_des.rdr_wl);
		BB_PRINT_ERR("rdr:%s():reset hifi error\n", __func__);
		return;
	}

/* todo :sochifi_watchdog_send_event undefined in dallas */
#ifdef CONFIG_HIFI_DSP_ONE_TRACK
	sochifi_watchdog_send_event();
#endif
	hifireset_runcbfun(DRV_RESET_CALLCBFUN_RESET_AFTER);

	wake_unlock(&soc_des.rdr_wl);

	BB_PRINT_END();

	return;
}

static irqreturn_t soc_wtd_irq_handler(int irq, void *data)
{
	writel(DRV_WATCHDOG_UNLOCK_NUM, soc_des.lock_addr);
	writel(DRV_WATCHDOG_INTCLR_NUM, soc_des.intclr_addr);
	writel(DRV_WATCHDOG_CONTROL_DISABLE, soc_des.control_addr);
	writel(DRV_WATCHDOG_LOCK_NUM, soc_des.lock_addr);

	wake_lock(&soc_des.rdr_wl);

	up(&soc_des.handler_sem);

	return IRQ_HANDLED;
}

int rdr_audio_soc_init(void)
{
	int ret = 0;

	BB_PRINT_START();

	soc_des.modid = ~0;
	soc_des.pathname = NULL;
	soc_des.lock_addr = NULL;
	soc_des.control_addr = NULL;
	soc_des.intclr_addr = NULL;
	soc_des.dumpdone_cb = NULL;

	sema_init(&soc_des.dump_sem, 0);
	sema_init(&soc_des.handler_sem, 0);
	wake_lock_init(&soc_des.rdr_wl, WAKE_LOCK_SUSPEND, "rdr_sochifi");
	soc_des.kdump_task = NULL;
	soc_des.khandler_task = NULL;

	soc_des.lock_addr = (u32 *)ioremap(DRV_WATCHDOG_LOCK, 0x4);
	if (!soc_des.lock_addr) {
		BB_PRINT_ERR("rdr: remap watchdog lock addr fail\n");
		ret = -ENOMEM;
		goto error;
	}

	soc_des.control_addr = (u32 *)ioremap(DRV_WATCHDOG_CONTROL, 0x4);
	if (!soc_des.control_addr) {
		BB_PRINT_ERR("rdr: remap watchdog control addr fail\n");
		ret = -ENOMEM;
		goto error;
	}

	soc_des.intclr_addr = (u32 *)ioremap(DRV_WATCHDOG_INTCLR, 0x4);
	if (!soc_des.intclr_addr) {
		BB_PRINT_ERR("rdr: remap watchdog interrupt clear addr fail\n");
		ret = -ENOMEM;
		goto error;
	}

	soc_des.kdump_task = kthread_run(dump_thread, NULL, "rdr_audio_soc_thread");
	if (!soc_des.kdump_task) {
		BB_PRINT_ERR("create rdr soc dump thead fail\n");
		ret = -EBUSY;
		goto error;
	}

	soc_des.khandler_task = kthread_run(irq_handler_thread, NULL, "rdr_audio_soc_wtd_irq_handler_thread");
	if (!soc_des.khandler_task) {
		BB_PRINT_ERR("create rdr soc wtd irq handler thead fail\n");
		ret = -EBUSY;
		goto error;
	}

	ret = request_irq(SOC_WDT_TIMEOUT_IRQ_NUM, soc_wtd_irq_handler, 0, "soc wdt handler", NULL);
	if (ret) {
		BB_PRINT_ERR("request_irq soc_wdt_irq_handler failed! return 0x%x\n", ret);
		goto error;
	}

	BB_PRINT_END();

	return ret;

error:
	if (soc_des.kdump_task != NULL) {
		kthread_stop(soc_des.kdump_task);
		up(&soc_des.dump_sem);
		soc_des.kdump_task = NULL;
	}

	if (soc_des.khandler_task != NULL) {
		kthread_stop(soc_des.khandler_task);
		up(&soc_des.handler_sem);
		soc_des.khandler_task = NULL;
	}

	wake_lock_destroy(&soc_des.rdr_wl);

	if (NULL != soc_des.lock_addr) {
		iounmap(soc_des.lock_addr);
		soc_des.lock_addr = NULL;
	}

	if (NULL != soc_des.control_addr) {
		iounmap(soc_des.control_addr);
		soc_des.control_addr = NULL;
	}

	if (NULL != soc_des.intclr_addr) {
		iounmap(soc_des.intclr_addr);
		soc_des.intclr_addr = NULL;
	}

	wake_lock_destroy(&soc_des.rdr_wl);

	BB_PRINT_END();

	return ret;
}

void rdr_audio_soc_exit(void)
{
	BB_PRINT_START();

	free_irq(SOC_WDT_TIMEOUT_IRQ_NUM, NULL);

	if (soc_des.kdump_task != NULL) {
		kthread_stop(soc_des.kdump_task);
		up(&soc_des.dump_sem);
		soc_des.kdump_task = NULL;
	}

	if (soc_des.khandler_task != NULL) {
		kthread_stop(soc_des.khandler_task);
		up(&soc_des.handler_sem);
		soc_des.khandler_task = NULL;
	}

	wake_lock_destroy(&soc_des.rdr_wl);

	if (NULL != soc_des.lock_addr) {
		iounmap(soc_des.lock_addr);
		soc_des.lock_addr = NULL;
	}

	if (NULL != soc_des.control_addr) {
		iounmap(soc_des.control_addr);
		soc_des.control_addr = NULL;
	}

	if (NULL != soc_des.intclr_addr) {
		iounmap(soc_des.intclr_addr);
		soc_des.intclr_addr = NULL;
	}

	BB_PRINT_END();

	return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

