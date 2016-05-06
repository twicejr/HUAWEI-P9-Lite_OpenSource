/*
 * SOCP channel config and data process
 *
 * Copyright (c) 2012-2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/gfp.h>
#include <linux/mm.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <linux/interrupt.h>
#include <linux/spinlock.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/mman.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/io.h>
#include <asm/system.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>
#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/highmem.h>

#include "socp.h"

SOCP_GBL_STATE	  g_strSocpStat = { 0 };
SOCP_DEBUG_INFO_S g_stSocpDebugInfo;

/* define code and decode task priority*/
#define SOCP_ENCSRC_TASK_PRO	79
#define SOCP_ENCDST_TASK_PRO	81
#define SOCP_DECSRC_TASK_PRO	79
#define SOCP_DECDST_TASK_PRO	81

u32 g_SocpRegBaseAddr = 0xFF030900;
spinlock_t lock;

/**
 *	socp_get_idle_buffer		-	get ring buffer's idle buffer
 *	@pRingBuffer: query buffer
 *	@pRWBuffer: result of the idle buffer
 *
 *	use for query ring buffer's idle buffer
 */
void socp_get_idle_buffer(SOCP_RING_BUF_S *pRingBuffer,
						  SOCP_BUFFER_RW_S *pRWBuffer)
{
	if (pRingBuffer->u32Write < pRingBuffer->u32Read) {
		pRWBuffer->pBuffer = (s8 *)(pRingBuffer->u32Write);
		pRWBuffer->u32Size =
			(u32)(pRingBuffer->u32Read - pRingBuffer->u32Write - 1);
		pRWBuffer->pRbBuffer = (s8 *)BSP_NULL;
		pRWBuffer->u32RbSize = 0;
	} else {
		if (pRingBuffer->u32Read != pRingBuffer->u32Start) {
			pRWBuffer->pBuffer = (s8 *)(pRingBuffer->u32Write);
			pRWBuffer->u32Size =
				(u32)(pRingBuffer->u32End -
					  pRingBuffer->u32Write + 1);
			pRWBuffer->pRbBuffer = (s8 *)(pRingBuffer->u32Start);
			pRWBuffer->u32RbSize =
				(u32)(pRingBuffer->u32Read - pRingBuffer->u32Start - 1);
		} else {
			pRWBuffer->pBuffer = (s8 *)(pRingBuffer->u32Write);
			pRWBuffer->u32Size =
				(u32)(pRingBuffer->u32End - pRingBuffer->u32Write);
			pRWBuffer->pRbBuffer = (s8 *)BSP_NULL;
			pRWBuffer->u32RbSize = 0;
		}
	}

	return;
}

/**
 *	socp_get_data_buffer		-	get idle buffer's data
 *	@pRingBuffer: query buffer
 *	@pRWBuffer: result of the idle buffer
 *
 *	use for query  idle buffer's data
 */
void socp_get_data_buffer(SOCP_RING_BUF_S *pRingBuffer,
						  SOCP_BUFFER_RW_S *pRWBuffer)
{
	if (pRingBuffer->u32Read <= pRingBuffer->u32Write) {
		pRWBuffer->pBuffer = (s8 *)(pRingBuffer->u32Read);
		pRWBuffer->u32Size =
			(u32)(pRingBuffer->u32Write - pRingBuffer->u32Read);
		pRWBuffer->pRbBuffer = (s8 *)BSP_NULL;
		pRWBuffer->u32RbSize = 0;
	} else {
		pRWBuffer->pBuffer = (s8 *)(pRingBuffer->u32Read);
		pRWBuffer->u32Size =
			(u32)(pRingBuffer->u32End - pRingBuffer->u32Read + 1);
		pRWBuffer->pRbBuffer = (s8 *)(pRingBuffer->u32Start);
		pRWBuffer->u32RbSize =
			(u32)(pRingBuffer->u32Write - pRingBuffer->u32Start);
	}

	return;
}

void socp_write_done(SOCP_RING_BUF_S *pRingBuffer, u32 u32Size)
{
	u32 tmp_size;

	tmp_size = pRingBuffer->u32End - pRingBuffer->u32Write + 1;
	if (tmp_size > u32Size) {
		SOCP_FLUSH_CACHE((u8 *)pRingBuffer->u32Write, u32Size);
		pRingBuffer->u32Write += u32Size;
	} else {
		u32 rb_size = u32Size - tmp_size;
		SOCP_FLUSH_CACHE((u8 *)pRingBuffer->u32Write, tmp_size);
		SOCP_FLUSH_CACHE((u8 *)pRingBuffer->u32Start, rb_size);
		pRingBuffer->u32Write = pRingBuffer->u32Start + rb_size;
	}
	return;
}

void socp_read_done(SOCP_RING_BUF_S *pRingBuffer, u32 u32Size)
{
	pRingBuffer->u32Read += u32Size;
	if (pRingBuffer->u32Read > pRingBuffer->u32End)
		pRingBuffer->u32Read -= pRingBuffer->u32Length;
}

u32 bsp_socp_clean_encsrc_chan(SOCP_CODER_SRC_ENUM_U32 enSrcChanID)
{
	u32 ulResetFlag;
	u32 i;
	u32 ulChanID;
	u32 ulChanType;

	ulChanID = SOCP_REAL_CHAN_ID(enSrcChanID);
	ulChanType = SOCP_REAL_CHAN_TYPE(enSrcChanID);

	SOCP_CHECK_CHAN_TYPE(ulChanType, SOCP_CODER_SRC_CHAN);
	SOCP_CHECK_ENCSRC_CHAN_ID(ulChanID);

	SOCP_REG_SETBITS(SOCP_REG_ENCRST, ulChanID, 1, 1);

	for (i = 0; i < SOCP_RESET_TIME; i++) {
		ulResetFlag = SOCP_REG_GETBITS(SOCP_REG_ENCRST, ulChanID, 1);

		if (0 == ulResetFlag)
			break;
	}

	if (SOCP_RESET_TIME == i)
		pr_info("SocpCleanEncChan failed!\n");

	return BSP_OK;
}

s32 socp_reset_enc_chan(u32 u32ChanID)
{
	u32 ResetFlag;
	u32 i;
	SOCP_ENCSRC_CHAN_S *pChan;

	pChan = &g_strSocpStat.sEncSrcChan[u32ChanID];

	SOCP_REG_SETBITS(SOCP_REG_ENCRST, u32ChanID, 1, 1);

	for (i = 0; i < SOCP_RESET_TIME; i++) {
		ResetFlag = SOCP_REG_GETBITS(SOCP_REG_ENCRST, u32ChanID, 1);
		if (0 == ResetFlag)
			break;

		if ((SOCP_RESET_TIME - 1) == i) {
			pr_info("socp_reset_enc_chan 0x%x failed!\n",
					u32ChanID);
		}
	}

	SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFADDR(u32ChanID),
				   SOCP_VIRT_PHY(pChan->sEncSrcBuf.u32Start));
	SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFWPTR(u32ChanID),
				   SOCP_VIRT_PHY(pChan->sEncSrcBuf.u32Start));
	SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFRPTR(u32ChanID),
				   SOCP_VIRT_PHY(pChan->sEncSrcBuf.u32Start));
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(u32ChanID), 0, 27,
					 pChan->sEncSrcBuf.u32Length);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(u32ChanID), 27, 5, 0);
	g_strSocpStat.sEncSrcChan[u32ChanID].sEncSrcBuf.u32Read =
		pChan->sEncSrcBuf.u32Start;
	g_strSocpStat.sEncSrcChan[u32ChanID].sEncSrcBuf.u32Write =
		pChan->sEncSrcBuf.u32Start;

	if (SOCP_ENCSRC_CHNMODE_LIST == pChan->eChnMode) {
		SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQADDR(u32ChanID),
					   (u32)SOCP_VIRT_PHY(pChan->sRdBuf.u32Start));
		SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQRPTR(u32ChanID),
					   SOCP_VIRT_PHY(pChan->sRdBuf.u32Start));
		SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQWPTR(u32ChanID),
					   SOCP_VIRT_PHY(pChan->sRdBuf.u32Start));
		pr_info("%s: ID is %d, VBuf addr is 0x%X, PBuf addr is 0x%X\n",
				__func__, u32ChanID, pChan->sRdBuf.u32Start,
				SOCP_VIRT_PHY(pChan->sRdBuf.u32Start));
		SOCP_REG_SETBITS(SOCP_REG_ENCSRC_RDQCFG(u32ChanID), 0, 16,
						 pChan->sRdBuf.u32Length);
		SOCP_REG_SETBITS(SOCP_REG_ENCSRC_RDQCFG(u32ChanID), 16, 16, 0);

		g_strSocpStat.sEncSrcChan[u32ChanID].sRdBuf.u32Read =
			pChan->sRdBuf.u32Start;
		g_strSocpStat.sEncSrcChan[u32ChanID].sRdBuf.u32Write =
			pChan->sRdBuf.u32Start;
	}

	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 1, 2,
					 pChan->eChnMode);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 4, 4,
					 pChan->u32DestChanID);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 8, 2,
					 pChan->ePriority);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 10, 1,
					 pChan->u32BypassEn);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 16, 8,
					 pChan->eDataType);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 11, 1,
					 pChan->eDataTypeEn);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 31, 1,
					 pChan->eDebugEn);

	if (pChan->u32ChanEn)
		SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 0, 1, 1);

	return BSP_OK;
}

s32 socp_reset_dsp_log_chan(u32 u32ChanID)
{
	u32 ResetFlag;
	u32 j;
	u32 u32FixChanId = 0;
	SOCP_ENCSRC_CHAN_S *pChan;

	u32FixChanId = u32ChanID;
	pChan = &g_strSocpStat.sEncSrcChan[u32FixChanId];

	SOCP_REG_SETBITS(SOCP_REG_ENCRST, SOCP_DSPLOG_CHN, 1, 1);

	for (j = 0; j < SOCP_RESET_TIME; j++) {
		ResetFlag =
			SOCP_REG_GETBITS(SOCP_REG_ENCRST, SOCP_DSPLOG_CHN, 1);
		if (0 == ResetFlag)
			break;

		if ((SOCP_RESET_TIME - 1) == j) {
			pr_info("socp_reset_dsp_log_chan 0x%x failed!\n",
					SOCP_DSPLOG_CHN);
		}
	}

	SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFADDR(SOCP_DSPLOG_CHN),
				   (u32) SOCP_DSPLOG_CHN_ADDR);
	SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFWPTR(SOCP_DSPLOG_CHN),
				   (u32) SOCP_DSPLOG_CHN_ADDR);
	SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFRPTR(SOCP_DSPLOG_CHN),
				   (u32) SOCP_DSPLOG_CHN_ADDR);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(SOCP_DSPLOG_CHN), 0, 27,
					 SOCP_DSPLOG_CHN_SIZE);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(SOCP_DSPLOG_CHN), 27, 5, 0);

	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_DSPLOG_CHN), 1, 2,
					 SOCP_ENCSRC_CHNMODE_CTSPACKET);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_DSPLOG_CHN), 4, 4,
					 SOCP_DSPLOG_DST_BUFID);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_DSPLOG_CHN), 8, 2,
					 SOCP_CHAN_PRIORITY_0);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_DSPLOG_CHN), 10, 1,
					 SOCP_ENCSRC_BYPASS_DISABLE);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_DSPLOG_CHN), 16, 8,
					 SOCP_DATA_TYPE_0);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_DSPLOG_CHN), 11, 1,
					 SOCP_DATA_TYPE_EN);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_DSPLOG_CHN), 31, 1,
					 SOCP_ENC_DEBUG_DIS);

	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_DSPLOG_CHN), 0, 1, 1);

	pChan->sEncSrcBuf.u32Read = (u32) SOCP_DSPLOG_CHN_ADDR;
	pChan->sEncSrcBuf.u32Write = (u32) SOCP_DSPLOG_CHN_ADDR;
	pChan->u32ChanEn = SOCP_CHN_ENABLE;

	return BSP_OK;
}

s32 socp_reset_bbp_log_chan(u32 u32ChanID)
{
	u32 ResetFlag;
	u32 j;
	u32 u32BbpLogAddr;
	u32 u32FixChanId = 0;
	SOCP_ENCSRC_CHAN_S *pChan;

	u32FixChanId = u32ChanID;
	pChan = &g_strSocpStat.sEncSrcChan[u32FixChanId];

	SOCP_REG_SETBITS(SOCP_REG_ENCRST, u32ChanID, 1, 1);
	for (j = 0; j < SOCP_RESET_TIME; j++) {
		ResetFlag = SOCP_REG_GETBITS(SOCP_REG_ENCRST, u32ChanID, 1);
		if (0 == ResetFlag)
			break;

		if ((SOCP_RESET_TIME - 1) == j)
			pr_info("%s 0x%x failed!\n", __func__, u32ChanID);
	}

	BBP_REG_READ(BBP_REG_LOG_ADDR((u32ChanID - SOCP_FIXCHN_BASE)),
				 u32BbpLogAddr);

	SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFADDR(u32ChanID), u32BbpLogAddr);
	SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFWPTR(u32ChanID), u32BbpLogAddr);
	SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFRPTR(u32ChanID), u32BbpLogAddr);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(u32ChanID), 0, 27,
					 SOCP_BBPLOG_CHN_SIZE);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(u32ChanID), 27, 5, 0);

	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 1, 2,
					 SOCP_ENCSRC_CHNMODE_CTSPACKET);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 4, 4,
					 SOCP_BBPLOG_DST_BUFID);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 8, 2,
					 SOCP_CHAN_PRIORITY_0);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 10, 1,
					 SOCP_ENCSRC_BYPASS_DISABLE);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 16, 8,
					 SOCP_DATA_TYPE_0);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 11, 1,
					 SOCP_DATA_TYPE_EN);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 31, 1,
					 SOCP_ENC_DEBUG_DIS);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32ChanID), 0, 1, 1);

	pChan->sEncSrcBuf.u32Write = u32BbpLogAddr;
	pChan->sEncSrcBuf.u32Read = u32BbpLogAddr;
	pChan->u32ChanEn = SOCP_CHN_ENABLE;

	return BSP_OK;
}

s32 socp_reset_bbp_ds_chan(u32 u32ChanId)
{
	u32 ResetFlag;
	u32 j;
	u32 u32FixChanId = 0;
	SOCP_ENCSRC_CHAN_S *pChan;

	u32FixChanId = u32ChanId;
	pChan = &g_strSocpStat.sEncSrcChan[u32FixChanId];

	SOCP_REG_SETBITS(SOCP_REG_ENCRST, SOCP_BBPDS_CHN, 1, 1);
	for (j = 0; j < SOCP_RESET_TIME; j++) {
		ResetFlag =
			SOCP_REG_GETBITS(SOCP_REG_ENCRST, SOCP_BBPDS_CHN, 1);
		if (0 == ResetFlag)
			break;
		if ((SOCP_RESET_TIME - 1) == j)
			pr_info("socp_reset_bbp_ds_chan 0x%x failed!\n", SOCP_BBPDS_CHN);
	}

	BBP_REG_WRITE(BBP_REG_DS_ADDR, SOCP_BBPDS_CHN_ADDR);
	BBP_REG_SETBITS(BBP_REG_DS_CFG, 31, 1, SOCP_BBP_DS_MODE_OVERRIDE);
	BBP_REG_SETBITS(BBP_REG_DS_CFG, 0, 28, SOCP_BBPDS_CHN_SIZE);

	SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFADDR(SOCP_BBPDS_CHN),
				   SOCP_BBPDS_CHN_ADDR);
	SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFWPTR(SOCP_BBPDS_CHN),
				   SOCP_BBPDS_CHN_ADDR);
	SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFRPTR(SOCP_BBPDS_CHN),
				   SOCP_BBPDS_CHN_ADDR);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(SOCP_BBPDS_CHN), 0, 27,
					 SOCP_BBPDS_CHN_SIZE);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(SOCP_BBPDS_CHN), 27, 5, 0);

	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_BBPDS_CHN), 1, 2,
					 SOCP_ENCSRC_CHNMODE_FIXPACKET);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_BBPDS_CHN), 4, 4,
					 SOCP_BBPDS_DST_BUFID);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_BBPDS_CHN), 8, 2,
					 SOCP_CHAN_PRIORITY_0);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_BBPDS_CHN), 10, 1,
					 SOCP_ENCSRC_BYPASS_DISABLE);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_BBPDS_CHN), 16, 8,
					 SOCP_DATA_TYPE_0);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_BBPDS_CHN), 11, 1,
					 SOCP_DATA_TYPE_EN);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_BBPDS_CHN), 31, 1,
					 SOCP_ENC_DEBUG_DIS);

	pChan->sEncSrcBuf.u32Write = SOCP_BBPDS_CHN_ADDR;
	pChan->sEncSrcBuf.u32Read = SOCP_BBPDS_CHN_ADDR;

	return BSP_OK;
}

s32 socp_reset_dec_chan(u32 u32ChanID)
{
	u32 u32ResetFlag;
	u32 i;
	SOCP_DECSRC_CHAN_S *pChan;

	pChan = &g_strSocpStat.sDecSrcChan[u32ChanID];

	SOCP_REG_SETBITS(SOCP_REG_DECRST, u32ChanID, 1, 1);

	for (i = 0; i < SOCP_RESET_TIME; i++) {
		u32ResetFlag = SOCP_REG_GETBITS(SOCP_REG_DECRST, u32ChanID, 1);
		if (0 == u32ResetFlag)
			break;
		if ((SOCP_RESET_TIME - 1) == i)
			pr_info("%s 0x%x failed!\n", __func__, u32ChanID);
	}

	SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFADDR(u32ChanID),
				   SOCP_VIRT_PHY(pChan->sDecSrcBuf.u32Start));
	SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFWPTR(u32ChanID),
				   SOCP_VIRT_PHY(pChan->sDecSrcBuf.u32Start));
	SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFRPTR(u32ChanID),
				   SOCP_VIRT_PHY(pChan->sDecSrcBuf.u32Start));

	SOCP_REG_SETBITS(SOCP_REG_DECSRC_BUFCFG0(u32ChanID), 0, 16,
					 pChan->sDecSrcBuf.u32Length);
	SOCP_REG_SETBITS(SOCP_REG_DECSRC_BUFCFG0(u32ChanID), 31, 1,
					 pChan->eDataTypeEn);
	g_strSocpStat.sDecSrcChan[u32ChanID].sDecSrcBuf.u32Read =
		pChan->sDecSrcBuf.u32Start;
	g_strSocpStat.sDecSrcChan[u32ChanID].sDecSrcBuf.u32Write =
		pChan->sDecSrcBuf.u32Start;

	return BSP_OK;
}

s32 socp_soft_free_encdst_chan(u32 u32EncDstChanId)
{
	u32 u32ChanID;
	u32 u32ChanType;
	SOCP_ENCDST_CHAN_S *pChan;

	u32ChanID = SOCP_REAL_CHAN_ID(u32EncDstChanId);
	u32ChanType = SOCP_REAL_CHAN_TYPE(u32EncDstChanId);

	SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_CODER_DEST_CHAN);
	SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_ENCDST_CHN);

	pChan = &g_strSocpStat.sEncDstChan[u32ChanID];

	SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFADDR(u32ChanID),
				   SOCP_VIRT_PHY(pChan->sEncDstBuf.u32Start));
	SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFRPTR(u32ChanID),
				   SOCP_VIRT_PHY(pChan->sEncDstBuf.u32Start));
	SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFWPTR(u32ChanID),
				   SOCP_VIRT_PHY(pChan->sEncDstBuf.u32Start));

	g_strSocpStat.sEncDstChan[u32ChanID].u32SetStat = SOCP_CHN_UNSET;
	g_strSocpStat.sEncDstChan[u32ChanID].sEncDstBuf.u32Write =
		pChan->sEncDstBuf.u32Start;
	g_strSocpStat.sEncDstChan[u32ChanID].sEncDstBuf.u32Read =
		pChan->sEncDstBuf.u32Start;

	return BSP_OK;
}

s32 socp_soft_free_decsrc_chan(u32 u32DecSrcChanId)
{
	u32 u32ChanID;
	u32 u32ChanType;
	SOCP_DECSRC_CHAN_S *pDecSrcChan;

	u32ChanID = SOCP_REAL_CHAN_ID(u32DecSrcChanId);
	u32ChanType = SOCP_REAL_CHAN_TYPE(u32DecSrcChanId);

	SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_SRC_CHAN);
	SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECSRC_CHN);

	pDecSrcChan = &g_strSocpStat.sDecSrcChan[u32ChanID];

	SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFWPTR(u32ChanID),
				   SOCP_VIRT_PHY(pDecSrcChan->sDecSrcBuf.u32Start));
	SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFADDR(u32ChanID),
				   SOCP_VIRT_PHY(pDecSrcChan->sDecSrcBuf.u32Start));
	SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFRPTR(u32ChanID),
				   SOCP_VIRT_PHY(pDecSrcChan->sDecSrcBuf.u32Start));

	g_strSocpStat.sDecSrcChan[u32ChanID].u32SetStat = SOCP_CHN_UNSET;
	g_strSocpStat.sDecSrcChan[u32ChanID].sDecSrcBuf.u32Write =
		pDecSrcChan->sDecSrcBuf.u32Start;
	g_strSocpStat.sDecSrcChan[u32ChanID].sDecSrcBuf.u32Read =
		pDecSrcChan->sDecSrcBuf.u32Start;

	return BSP_OK;
}

s32 socp_init_lte_dsp(void)
{
	u32 u32FixChanId = 0;
	SOCP_ENCSRC_CHAN_S *pChan;

	u32FixChanId = SOCP_CODER_SRC_LDSP1;
	pChan = &g_strSocpStat.sEncSrcChan[u32FixChanId];

	SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFADDR(SOCP_DSPLOG_CHN),
				   (u32) SOCP_DSPLOG_CHN_ADDR);
	SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFWPTR(SOCP_DSPLOG_CHN),
				   (u32) SOCP_DSPLOG_CHN_ADDR);
	SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFRPTR(SOCP_DSPLOG_CHN),
				   (u32) SOCP_DSPLOG_CHN_ADDR);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(SOCP_DSPLOG_CHN), 0, 27,
					 SOCP_DSPLOG_CHN_SIZE);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(SOCP_DSPLOG_CHN), 27, 5, 0);

	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_DSPLOG_CHN), 0, 1, 1);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_DSPLOG_CHN), 1, 2,
					 SOCP_ENCSRC_CHNMODE_CTSPACKET);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_DSPLOG_CHN), 4, 4,
					 SOCP_DSPLOG_DST_BUFID);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_DSPLOG_CHN), 8, 2,
					 SOCP_CHAN_PRIORITY_0);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_DSPLOG_CHN), 10, 1,
					 SOCP_ENCSRC_BYPASS_DISABLE);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_DSPLOG_CHN), 16, 8,
					 SOCP_DATA_TYPE_0);

	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_DSPLOG_CHN), 11, 1,
					 SOCP_DATA_TYPE_EN);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_DSPLOG_CHN), 31, 1,
					 SOCP_ENC_DEBUG_DIS);

	SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT1, SOCP_DSPLOG_CHN, 1, 1);
	SOCP_REG_SETBITS(SOCP_REG_APP_MASK1, SOCP_DSPLOG_CHN, 1, 0);

	pChan->u32ChanID = SOCP_DSPLOG_CHN;
	pChan->u32DestChanID = SOCP_DSPLOG_DST_BUFID;
	pChan->eChnMode = SOCP_ENCSRC_CHNMODE_CTSPACKET;
	pChan->eDataType = SOCP_DATA_TYPE_0;
	pChan->ePriority = SOCP_CHAN_PRIORITY_0;
	pChan->eDataTypeEn = SOCP_DATA_TYPE_EN;
	pChan->eDebugEn = SOCP_ENC_DEBUG_DIS;
	pChan->sEncSrcBuf.u32Start = (u32) SOCP_DSPLOG_CHN_ADDR;
	pChan->sEncSrcBuf.u32Write = (u32) SOCP_DSPLOG_CHN_ADDR;
	pChan->sEncSrcBuf.u32End =
		(u32) (SOCP_DSPLOG_CHN_ADDR + SOCP_DSPLOG_CHN_SIZE);
	pChan->sEncSrcBuf.u32Read = (u32) SOCP_DSPLOG_CHN_ADDR;
	pChan->sEncSrcBuf.u32Length = (u32) SOCP_DSPLOG_CHN_SIZE;
	pChan->u32ChanEn = SOCP_CHN_ENABLE;

	return BSP_OK;
}

s32 socp_init_lte_bbp(void)
{
	u32 i, j;
	u32 u32FixChanId = 0;
	u32 u32RealId = 0;
	u8 *pBbpLogBuf[BBP_MAX_LOG_CHN];
	SOCP_ENCSRC_CHAN_S *pChan;

	for (i = 0; i < BBP_MAX_LOG_CHN; i++) {
		pBbpLogBuf[i] = kmalloc(SOCP_BBPLOG_CHN_SIZE, GFP_KERNEL);
		if (NULL == pBbpLogBuf[i]) {
			for (j = 0; j < i; j++)
				kfree(pBbpLogBuf[j]);
			pr_info("%s: malloc bbp channel error!\n", __func__);
			return BSP_ERR_SOCP_MEM_ALLOC;
		}

		BBP_REG_WRITE(BBP_REG_LOG_ADDR(i),
					  virt_to_phys(pBbpLogBuf[i]));
		BBP_REG_SETBITS(BBP_REG_LOG_CFG(i), 0, 24,
						SOCP_BBPLOG_CHN_SIZE);

		SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFADDR((i + SOCP_BBPLOG_CHN)),
					   virt_to_phys(pBbpLogBuf[i]));
		SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFWPTR((i + SOCP_BBPLOG_CHN)),
					   virt_to_phys(pBbpLogBuf[i]));
		SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFRPTR((i + SOCP_BBPLOG_CHN)),
					   virt_to_phys(pBbpLogBuf[i]));
		SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0
						 ((i + SOCP_BBPLOG_CHN)), 0, 27,
						 SOCP_BBPLOG_CHN_SIZE);
		SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0
						 ((i + SOCP_BBPLOG_CHN)), 27, 5, 0);

		SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1
						 ((i + SOCP_BBPLOG_CHN)), 0, 1, 1);
		SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1
						 ((i + SOCP_BBPLOG_CHN)), 1, 2,
						 SOCP_ENCSRC_CHNMODE_CTSPACKET);
		SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1
						 ((i + SOCP_BBPLOG_CHN)), 4, 4,
						 SOCP_BBPLOG_DST_BUFID);
		SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1
						 ((i + SOCP_BBPLOG_CHN)), 8, 2,
						 SOCP_CHAN_PRIORITY_0);
		SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1
						 ((i + SOCP_BBPLOG_CHN)), 10, 1,
						 SOCP_ENCSRC_BYPASS_DISABLE);
		SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1
						 ((i + SOCP_BBPLOG_CHN)), 16, 8,
						 SOCP_DATA_TYPE_0);
		SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1
						 ((i + SOCP_BBPLOG_CHN)), 11, 1,
						 SOCP_DATA_TYPE_EN);
		SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1
						 ((i + SOCP_BBPLOG_CHN)), 31, 1,
						 SOCP_ENC_DEBUG_DIS);

		u32RealId = SOCP_BBPLOG_CHN + i;
		SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT1, u32RealId, 1, 1);
		SOCP_REG_SETBITS(SOCP_REG_APP_MASK1, u32RealId, 1, 0);

		u32FixChanId = i + SOCP_CODER_SRC_LBBP1;
		pChan = &g_strSocpStat.sEncSrcChan[u32FixChanId];

		pChan->u32ChanID = i + SOCP_BBPLOG_CHN;
		pChan->u32DestChanID = SOCP_BBPLOG_DST_BUFID;
		pChan->eChnMode = SOCP_ENCSRC_CHNMODE_CTSPACKET;
		pChan->eDataType = SOCP_DATA_TYPE_0;
		pChan->ePriority = SOCP_CHAN_PRIORITY_0;
		pChan->eDataTypeEn = SOCP_DATA_TYPE_EN;
		pChan->eDebugEn = SOCP_ENC_DEBUG_DIS;
		pChan->sEncSrcBuf.u32Start = virt_to_phys(pBbpLogBuf[i]);
		pChan->sEncSrcBuf.u32Write = virt_to_phys(pBbpLogBuf[i]);
		pChan->sEncSrcBuf.u32Read = virt_to_phys(pBbpLogBuf[i]);
		pChan->sEncSrcBuf.u32End =
			(virt_to_phys(pBbpLogBuf[i]) + SOCP_BBPLOG_CHN_SIZE);
		pChan->sEncSrcBuf.u32Length = (u32) SOCP_BBPLOG_CHN_SIZE;
		pChan->u32ChanEn = SOCP_CHN_ENABLE;
	}

	BBP_REG_WRITE(BBP_REG_DS_ADDR, SOCP_BBPDS_CHN_ADDR);
	BBP_REG_SETBITS(BBP_REG_DS_CFG, 31, 1, SOCP_BBP_DS_MODE_OVERRIDE);
	BBP_REG_SETBITS(BBP_REG_DS_CFG, 0, 28, SOCP_BBPDS_CHN_SIZE);

	SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFADDR(SOCP_BBPDS_CHN),
				   SOCP_BBPDS_CHN_ADDR);
	SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFWPTR(SOCP_BBPDS_CHN),
				   SOCP_BBPDS_CHN_ADDR);
	SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFRPTR(SOCP_BBPDS_CHN),
				   SOCP_BBPDS_CHN_ADDR);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(SOCP_BBPDS_CHN), 0, 27,
					 SOCP_BBPDS_CHN_SIZE);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(SOCP_BBPDS_CHN), 27, 5, 0);

	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_BBPDS_CHN), 1, 2,
					 SOCP_ENCSRC_CHNMODE_FIXPACKET);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_BBPDS_CHN), 4, 4,
					 SOCP_BBPDS_DST_BUFID);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_BBPDS_CHN), 8, 2,
					 SOCP_CHAN_PRIORITY_0);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_BBPDS_CHN), 10, 1,
					 SOCP_ENCSRC_BYPASS_DISABLE);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_BBPDS_CHN), 16, 8,
					 SOCP_DATA_TYPE_0);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_BBPDS_CHN), 11, 1,
					 SOCP_DATA_TYPE_EN);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_BBPDS_CHN), 31, 1,
					 SOCP_ENC_DEBUG_DIS);

	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_BBPDS_CHN), 0, 1, 0);

	SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT1, SOCP_BBPDS_CHN, 1, 1);
	SOCP_REG_SETBITS(SOCP_REG_APP_MASK1, SOCP_BBPDS_CHN, 1, 0);

	BBP_REG_WRITE(BBP_REG_PTR_ADDR,
				  (g_strSocpStat.baseAddr +
				   SOCP_REG_ENCSRC_BUFWPTR(SOCP_BBPLOG_CHN)));
	BBP_REG_SETBITS(BBP_REG_CH_EN, 0, 1, 1);

	u32FixChanId = SOCP_CODER_SRC_LBBP9;
	pChan = &g_strSocpStat.sEncSrcChan[u32FixChanId];
	pChan->u32ChanID = SOCP_BBPDS_CHN;
	pChan->u32DestChanID = SOCP_BBPDS_DST_BUFID;
	pChan->eChnMode = SOCP_ENCSRC_CHNMODE_FIXPACKET;
	pChan->eDataType = SOCP_DATA_TYPE_0;
	pChan->ePriority = SOCP_CHAN_PRIORITY_0;
	pChan->eDataTypeEn = SOCP_DATA_TYPE_EN;
	pChan->eDebugEn = SOCP_ENC_DEBUG_DIS;
	pChan->sEncSrcBuf.u32Start = (u32) SOCP_BBPDS_CHN_ADDR;
	pChan->sEncSrcBuf.u32Write = (u32) SOCP_BBPDS_CHN_ADDR;
	pChan->sEncSrcBuf.u32Read = (u32) SOCP_BBPDS_CHN_ADDR;
	pChan->sEncSrcBuf.u32End =
		(u32) (SOCP_BBPDS_CHN_ADDR + SOCP_BBPDS_CHN_SIZE);
	pChan->sEncSrcBuf.u32Length = (u32) SOCP_BBPDS_CHN_SIZE;

	return BSP_OK;
}


u32 socp_get_enc_rd_size(u32 u32ChanID)
{
	SOCP_BUFFER_RW_S Buff;
	u32 PAddr;
	u32 ret;

	SOCP_REG_READ(SOCP_REG_ENCSRC_RDQRPTR(u32ChanID), PAddr);
	g_strSocpStat.sEncSrcChan[u32ChanID].sRdBuf.u32Read =
		(u32)SOCP_PHY_VIRT(PAddr);
	SOCP_REG_READ(SOCP_REG_ENCSRC_RDQWPTR(u32ChanID), PAddr);
	g_strSocpStat.sEncSrcChan[u32ChanID].sRdBuf.u32Write =
		(u32)SOCP_PHY_VIRT(PAddr);

	socp_get_data_buffer(&g_strSocpStat.sEncSrcChan[u32ChanID].sRdBuf,
						 &Buff);
	ret = Buff.u32Size + Buff.u32RbSize;
	return ret;
}

void socp_encsrc_rd_handler(u32 RdSize, u32 i)
{
	u32 u32ChanId;

	if (RdSize == g_strSocpStat.sEncSrcChan[i].u32LastRdSize) {
		if (g_strSocpStat.sEncSrcChan[i].rd_cb) {
			u32ChanId = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN, i);
			(void)g_strSocpStat.sEncSrcChan[i].rd_cb(u32ChanId);

			g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpEncSrcTskRdCbCnt[i]++;
		}

		g_strSocpStat.sEncSrcChan[i].u32LastRdSize = 0;
	} else {
		g_strSocpStat.sEncSrcChan[i].u32LastRdSize = RdSize;
	}

	return;
}

int socp_encsrc_task(void *data)
{
	u32 i;
	u32 IntHeadState = 0;
	u32 IntRdState = 0;
	u32 u32ChanId;
	unsigned long lock_flag;

	do {
		down(&g_strSocpStat.u32EncSrcSemID);

		spin_lock_irqsave(&lock, lock_flag);
		IntHeadState = g_strSocpStat.u32IntEncSrcHeader;
		g_strSocpStat.u32IntEncSrcHeader = 0;
		IntRdState = g_strSocpStat.u32IntEncSrcRD;
		g_strSocpStat.u32IntEncSrcRD = 0;
		spin_unlock_irqrestore(&lock, lock_flag);

		if (IntHeadState) {
			for (i = 0; i < SOCP_MAX_ENCSRC_CHN; i++) {
				if (SOCP_CHN_ALLOCATED == g_strSocpStat.sEncSrcChan[i].u32AllocStat) {
					if (IntHeadState & ((u32)1 << i)) {
						if (g_strSocpStat.sEncSrcChan[i].event_cb) {
							g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpEncSrcTskHeadCbOriCnt[i]++;
							u32ChanId = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN, i);
							pr_info("%s: packet header Error Channel is %d\n",
									__func__, u32ChanId);
							(void)g_strSocpStat.sEncSrcChan[i].event_cb
							(u32ChanId, SOCP_EVENT_PKT_HEADER_ERROR, 0);
							g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpEncSrcTskHeadCbCnt[i]++;
						}
					}
				}
			}
		}
	} while (1);
	return 0;
}

int socp_encdst_task(void *data)
{
	u32 i;
	u32 IntTfrState = 0;
	u32 IntOvfState = 0;
	u32 IntThresholdOvfState = 0;
	u32 u32ChanId;
	unsigned long lock_flag;

	do {
		down(&g_strSocpStat.u32EncDstSemID);

		spin_lock_irqsave(&lock, lock_flag);
		IntTfrState = g_strSocpStat.u32IntEncDstTfr;
		g_strSocpStat.u32IntEncDstTfr = 0;
		IntOvfState = g_strSocpStat.u32IntEncDstOvf;
		g_strSocpStat.u32IntEncDstOvf = 0;
		IntThresholdOvfState = g_strSocpStat.u32IntEncDstThresholdOvf;
		g_strSocpStat.u32IntEncDstThresholdOvf = 0;
		spin_unlock_irqrestore(&lock, lock_flag);

		if (IntTfrState) {
			for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++) {
				if (SOCP_CHN_SET == g_strSocpStat.sEncDstChan[i].u32SetStat) {
					if (IntTfrState & ((u32)1 << i)) {
						if (g_strSocpStat.sEncDstChan[i].read_cb) {
							g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskTrfCbOriCnt[i]++;
							u32ChanId = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, i);
							(void)g_strSocpStat.sEncDstChan[i].read_cb(u32ChanId);
							g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskTrfCbCnt[i]++;
						}
					}
				}
			}
		}

		if (IntOvfState) {
			for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++) {
				if (SOCP_CHN_SET == g_strSocpStat.sEncDstChan[i].u32SetStat) {
					if (IntOvfState & ((u32) 1 << i)) {
						if (g_strSocpStat.sEncDstChan[i].event_cb) {
							g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskOvfCbOriCnt[i]++;
							u32ChanId = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, i);
							(void)g_strSocpStat.sEncDstChan[i].event_cb(u32ChanId, SOCP_EVENT_OUTBUFFER_OVERFLOW, 0);
							g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskOvfCbCnt[i]++;
						}
					}
				}
			}
		}

		if (IntThresholdOvfState) {
			for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++) {
				if (SOCP_CHN_SET == g_strSocpStat.sEncDstChan[i].u32SetStat) {
					if (IntThresholdOvfState & ((u32) 1 << (i + SOCP_ENC_DST_BUFF_THRESHOLD_OVF_BEGIN))) {
						if (g_strSocpStat.sEncDstChan[i].event_cb) {
							g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskThresholdOvfCbOriCnt[i]++;
							u32ChanId = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, i);
							(void)g_strSocpStat.sEncDstChan[i].event_cb(u32ChanId, SOCP_EVENT_OUTBUFFER_THRESHOLD_OVERFLOW, 0);
							g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstTskThresholdOvfCbCnt[i]++;
						}
					}
				}
			}
		}
	} while (1);
	return 0;
}

void socp_decsrc_event_handler(u32 id, u32 secIntState)
{
	u32 u32ChanId = SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN, id);

	if (g_strSocpStat.sDecSrcChan[id].event_cb) {
		if (secIntState & 0x10) {
			g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbOriCnt[id]++;
			(void)g_strSocpStat.sDecSrcChan[id].event_cb(u32ChanId, SOCP_EVENT_DECODER_UNDERFLOW, 0);
			g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbCnt[id]++;
		}

		if (secIntState & 0x100) {
			g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbOriCnt[id]++;
			(void)g_strSocpStat.sDecSrcChan[id].event_cb(u32ChanId, SOCP_EVENT_HDLC_HEADER_ERROR, 0);
			g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbCnt[id]++;
		}

		if (secIntState & 0x1000) {
			g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbOriCnt[id]++;
			(void)g_strSocpStat.sDecSrcChan[id].event_cb(u32ChanId, SOCP_EVENT_DATA_TYPE_ERROR, 0);
			g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbCnt[id]++;
		}

		if (secIntState & 0x10000) {
			g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbOriCnt[id]++;
			(void)g_strSocpStat.sDecSrcChan[id].event_cb(u32ChanId, SOCP_EVENT_CRC_ERROR, 0);
			g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbCnt[id]++;
		}

		if (secIntState & 0x100000) {
			g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbOriCnt[id]++;
			(void)g_strSocpStat.sDecSrcChan[id].event_cb(u32ChanId, SOCP_EVENT_PKT_LENGTH_ERROR, 0);
			g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcTskErrCbCnt[id]++;
		}
	}
}

void socp_decsrc_handler(void)
{
	u32 IntState, secIntState;
	u32 u32ChanId;
	u32 i;

	if (g_strSocpStat.u32IntDecSrcErr) {
		IntState = g_strSocpStat.u32IntDecSrcErr;
		g_strSocpStat.u32IntDecSrcErr = 0;

		for (i = 0; i < SOCP_MAX_DECSRC_CHN; i++) {
			if (SOCP_CHN_SET ==
				g_strSocpStat.sDecSrcChan[i].u32SetStat) {
				secIntState = IntState >> i;
				u32ChanId =
					SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN, i);

				if (g_strSocpStat.sDecSrcChan[i].rd_cb) {
					if (secIntState & 0x1)
						(void)g_strSocpStat.sDecSrcChan[i].rd_cb(u32ChanId);
				}

				socp_decsrc_event_handler(i, secIntState);
			}
		}
	}
}

void socp_decsrc_task(void)
{
	unsigned long lock_flag;

	do {
		down(&g_strSocpStat.u32DecSrcSemID);
		spin_lock_irqsave(&lock, lock_flag);
		socp_decsrc_handler();
		spin_unlock_irqrestore(&lock, lock_flag);
	} while (1);
}

int socp_decdst_task(void *data)
{
	u32 i;
	u32 IntTfrState = 0;
	u32 IntOvfState = 0;
	u32 u32ChanId;
	unsigned long lock_flag;

	do {
		down(&g_strSocpStat.u32DecDstSemID);
		spin_lock_irqsave(&lock, lock_flag);
		IntTfrState = g_strSocpStat.u32IntDecDstTfr;
		g_strSocpStat.u32IntDecDstTfr = 0;
		IntOvfState = g_strSocpStat.u32IntDecDstOvf;
		g_strSocpStat.u32IntDecDstOvf = 0;
		spin_unlock_irqrestore(&lock, lock_flag);

		if (IntTfrState) {
			for (i = 0; i < SOCP_MAX_DECDST_CHN; i++) {
				if (SOCP_CHN_ALLOCATED ==
					g_strSocpStat.sDecDstChan[i].u32AllocStat) {
					if (IntTfrState & ((u32) 1 << i)) {
						if (g_strSocpStat.sDecDstChan[i].read_cb) {
							g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpDecDstTskTrfCbOriCnt[i]++;

							u32ChanId =
								SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, i);

							(void)g_strSocpStat.sDecDstChan[i].read_cb(u32ChanId);

							g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpDecDstTskTrfCbCnt[i]++;
						}
					}
				}
			}
		}

		if (IntOvfState) {
			for (i = 0; i < SOCP_MAX_DECDST_CHN; i++) {
				if (SOCP_CHN_ALLOCATED ==
					g_strSocpStat.sDecDstChan[i].u32AllocStat) {
					if (IntOvfState & ((u32) 1 << i)) {
						if (g_strSocpStat.sDecDstChan[i].event_cb) {
							g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpDecDstTskOvfCbOriCnt[i]++;

							u32ChanId =
								SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, i);
							pr_info("%s: Call Event Cb, Channel is %d",
									__func__, u32ChanId);
							(void)g_strSocpStat.sDecDstChan[i].event_cb(u32ChanId,
									SOCP_EVENT_OUTBUFFER_OVERFLOW, 0);

							g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpDecDstTskOvfCbCnt[i]++;
						}
					}
				}
			}
		}
	} while (1);
	return 0;
}

s32 socp_create_task(s8 *puchName,
					 u32 *pu32TaskID,
					 socp_task_entry pfnFunc,
					 u32 u32Priority, u32 u32StackSize, void *pParam)
{
	struct task_struct *tsk;
	struct sched_param param;

	tsk = kthread_run(pfnFunc, pParam, puchName);
	if (IS_ERR(tsk)) {
		pr_info("socp_create_task: create kthread failed!\n");
		return BSP_ERROR;
	}

	param.sched_priority = u32Priority;
	if (0 != sched_setscheduler(tsk, SCHED_FIFO, &param)) {
		pr_info("%s: Creat Task %s ID %d sched_setscheduler Error",
				__func__, puchName, *pu32TaskID);
		return BSP_ERROR;
	}

	*pu32TaskID = (u32) tsk;

	return BSP_OK;
}

s32 socp_init_task(void)
{
	u32 aulArguments[4] = { 0, 0, 0, 0 };

	sema_init(&g_strSocpStat.u32EncSrcSemID, 0);
	if (!g_strSocpStat.u32EncSrcTskID) {
		if (BSP_OK !=
			socp_create_task("EncSrc",
							 (u32 *) &g_strSocpStat.u32EncSrcTskID,
							 (socp_task_entry) socp_encsrc_task,
							 SOCP_ENCSRC_TASK_PRO, 0x1000,
							 aulArguments)) {
			pr_info("%s: create encsrc task failed\n", __func__);
			return BSP_ERR_SOCP_TSK_CREATE;
		}
	}

	sema_init(&g_strSocpStat.u32EncDstSemID, 0);
	if (!g_strSocpStat.u32EncDstTskID) {
		if (BSP_OK !=
			socp_create_task("EncDst",
							 (u32 *) &g_strSocpStat.u32EncDstTskID,
							 (socp_task_entry) socp_encdst_task,
							 SOCP_ENCDST_TASK_PRO, 0x1000,
							 aulArguments)) {
			pr_info("%s: create encdst_task failed\n", __func__);
			return BSP_ERR_SOCP_TSK_CREATE;
		}
	}

	sema_init(&g_strSocpStat.u32DecSrcSemID, 0);
	if (!g_strSocpStat.u32DecSrcTskID) {
		if (BSP_OK !=
			socp_create_task("DecSrc",
							 (u32 *) &g_strSocpStat.u32DecSrcTskID,
							 (socp_task_entry) socp_decsrc_task,
							 SOCP_DECSRC_TASK_PRO, 0x1000,
							 aulArguments)) {
			pr_info("%s: create DecSrcTskID failed\n", __func__);
			return BSP_ERR_SOCP_TSK_CREATE;
		}
	}

	sema_init(&g_strSocpStat.u32DecDstSemID, 0);
	if (!g_strSocpStat.u32DecDstTskID) {
		if (BSP_OK !=
			socp_create_task("DecDst",
							 (u32 *) &g_strSocpStat.u32DecDstTskID,
							 (socp_task_entry) socp_decdst_task,
							 SOCP_DECDST_TASK_PRO, 0x1000,
							 aulArguments)) {
			pr_info("%s: create DecDstD failed\n", __func__);
			return BSP_ERR_SOCP_TSK_CREATE;
		}
	}

	return BSP_OK;
}

void socp_handler_encsrc(void)
{
	u32 IntFlag = 0;
	u32 IntState = 0;
	int bHandle = BSP_FALSE;
	u32 i = 0;

	/*read and clear the interrupt flags */
	SOCP_REG_READ(SOCP_REG_GBL_INTSTAT, IntFlag);
	if (IntFlag & SOCP_APP_ENC_FLAGINT_MASK) {
		SOCP_REG_READ(SOCP_REG_APP_INTSTAT1, IntState);
		SOCP_REG_WRITE(SOCP_REG_ENC_RAWINT1, IntState);

		g_strSocpStat.u32IntEncSrcHeader |= IntState;
		bHandle = BSP_TRUE;

		for (i = 0; i < SOCP_MAX_ENCSRC_CHN; i++) {
			if (IntState & ((u32) 1 << i)) {
				if (SOCP_REG_GETBITS(SOCP_REG_ENCSRC_BUFCFG1(i), 31, 1))
					SOCP_REG_SETBITS(SOCP_REG_APP_MASK1, i, 1, 1);
				g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpEncSrcIsrHeadIntCnt[i]++;
			}
		}
	}

	if (bHandle)
		up(&g_strSocpStat.u32EncSrcSemID);

	return;
}

void socp_handler_encdst(void)
{
	u32 IntFlag = 0;
	u32 IntFlag1 = 0;
	u32 IntState = 0;
	int bHandle = BSP_FALSE;
	u32 i;
	u32 mask;
	unsigned long lock_flag;
	SOCP_REG_READ(SOCP_REG_GBL_INTSTAT, IntFlag);
	if (IntFlag & SOCP_APP_ENC_TFRINT_MASK) {
		spin_lock_irqsave(&lock, lock_flag);
		SOCP_REG_READ(SOCP_REG_ENC_INTSTAT0, IntState);
		SOCP_REG_READ(SOCP_REG_ENC_MASK0, mask);
		SOCP_REG_WRITE(SOCP_REG_ENC_MASK0, (IntState | mask));
		SOCP_REG_WRITE(SOCP_REG_ENC_RAWINT0, IntState);

		g_strSocpStat.u32IntEncDstTfr |= IntState;
		spin_unlock_irqrestore(&lock, lock_flag);
		bHandle = BSP_TRUE;

		for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++) {
			if (IntState & ((u32) 1 << i))
				g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstIsrTrfIntCnt[i]++;
		}
	}
	SOCP_REG_READ(SOCP_REG_GBL_INTSTAT, IntFlag1);
	if (IntFlag1 & SOCP_APP_ENC_OUTOVFINT_MASK) {
		SOCP_REG_READ(SOCP_REG_ENC_INTSTAT2, IntState);
		if (0 != (IntState & SOCP_ENC_DST_BUFF_THRESHOLD_OVF_MASK)) {
			SOCP_REG_READ(SOCP_REG_ENC_MASK2, mask);
			SOCP_REG_WRITE(SOCP_REG_ENC_MASK2, (IntState | mask));
			SOCP_REG_WRITE(SOCP_REG_ENC_RAWINT2, IntState);
			g_strSocpStat.u32IntEncDstThresholdOvf |= IntState;
			bHandle = BSP_TRUE;

			for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++) {
				if (IntState &
					((u32) 1 << (i + SOCP_ENC_DST_BUFF_THRESHOLD_OVF_BEGIN)))
					g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstIsrThresholdOvfIntCnt[i]++;
			}

		}
		if (0 != (IntState & SOCP_ENC_DST_BUFF_OVF_MASK)) {
			SOCP_REG_READ(SOCP_REG_ENC_MASK2, mask);
			SOCP_REG_WRITE(SOCP_REG_ENC_MASK2, (IntState | mask));
			SOCP_REG_WRITE(SOCP_REG_ENC_RAWINT2, IntState);
			g_strSocpStat.u32IntEncDstOvf |= IntState;
			bHandle = BSP_TRUE;

			for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++) {
				if (IntState & ((u32) 1 << i))
					g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpEncDstIsrOvfIntCnt[i]++;
			}
		}
	}
	if (bHandle)
		up(&g_strSocpStat.u32EncDstSemID);

	return;
}

void socp_handler_decsrc(void)
{
	u32 IntFlag = 0;
	u32 IntState = 0;
	int bHandle = BSP_FALSE;
	u32 i = 0;

	SOCP_REG_READ(SOCP_REG_GBL_INTSTAT, IntFlag);
	if (IntFlag & SOCP_DEC_INERRINT_MASK) {
		SOCP_REG_READ(SOCP_REG_DEC_INTSTAT1, IntState);
		SOCP_REG_WRITE(SOCP_REG_DEC_RAWINT1, IntState);

		g_strSocpStat.u32IntDecSrcErr |= IntState;
		bHandle = BSP_TRUE;

		for (i = 0; i < SOCP_MAX_DECSRC_CHN; i++) {
			if (IntState & 0x1)
				g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpDecSrcIsrErrIntCnt[i]++;
		}
	}

	if (bHandle)
		up(&g_strSocpStat.u32DecSrcSemID);

	return;
}

void socp_handler_decdst(void)
{
	u32 IntFlag = 0;
	u32 IntState = 0;
	int bHandle = BSP_FALSE;
	u32 TfMask = 0;
	u32 TfState = 0;
	u32 OvMask = 0;
	u32 OvState = 0;
	u32 TfMaskReg = 0;
	u32 i = 0;

	TfMask = SOCP_CORE0_DEC_TFRINT_MASK;
	TfState = SOCP_REG_DEC_CORE0ISTAT0;
	TfMaskReg = SOCP_REG_DEC_CORE0MASK0;
	OvMask = SOCP_CORE0_DEC_OUTOVFINT_MASK;
	OvState = SOCP_REG_DEC_CORE0ISTAT2;

	SOCP_REG_READ(SOCP_REG_GBL_INTSTAT, IntFlag);
	if (IntFlag & TfMask) {
		u32 mask;

		SOCP_REG_READ(TfState, IntState);
		IntState = IntState & 0xffff;
		SOCP_REG_READ(TfMaskReg, mask);
		SOCP_REG_WRITE(TfMaskReg, (IntState | mask));
		SOCP_REG_WRITE(SOCP_REG_DEC_RAWINT0, IntState);

		g_strSocpStat.u32IntDecDstTfr |= IntState;
		bHandle = BSP_TRUE;

		for (i = 0; i < SOCP_MAX_DECDST_CHN; i++) {
			if (IntState & ((u32) 1 << i))
				g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpDecDstIsrTrfIntCnt[i]++;
		}
	}

	SOCP_REG_READ(SOCP_REG_GBL_INTSTAT, IntFlag);
	if (IntFlag & OvMask) {
		SOCP_REG_READ(OvState, IntState);
		IntState = IntState & 0xffff;
		SOCP_REG_WRITE(SOCP_REG_DEC_RAWINT2, IntState);

		g_strSocpStat.u32IntDecDstOvf |= IntState;
		bHandle = BSP_TRUE;

		for (i = 0; i < SOCP_MAX_DECDST_CHN; i++) {
			if (IntState & ((u32) 1 << i))
				g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpDecDstIsrOvfIntCnt[i]++;
		}
	}

	if (bHandle)
		up(&g_strSocpStat.u32DecDstSemID);

	return;
}
static irqreturn_t socp_app_int_handler(int irq, void *dev_instance)
{
	g_stSocpDebugInfo.sSocpDebugGBl.u32SocpAppEtrIntCnt++;

	socp_handler_encsrc();

	socp_handler_encdst();
	socp_handler_decsrc();
	socp_handler_decdst();

	g_stSocpDebugInfo.sSocpDebugGBl.u32SocpAppSucIntCnt++;

	return 1;
}

static int hs_socp_probe(struct platform_device *pdev)
{
	s32 ret;
	u32 i;
	u32 u32ResetValue = 0;

	struct device_node *np = NULL;
	void __iomem *base;
	int irq = 0;

	pr_info("!!!!!socp_init: enter!!!!.\n");

	if (BSP_TRUE == g_strSocpStat.bInitFlag)
		return BSP_OK;
	np = of_find_compatible_node(NULL, NULL, "hisilicon,socp");
	pr_info("socp node info fullname[%s],name[%s],type[%s]\n",
			np->full_name, np->name, np->type);
	if (np == NULL) {
		pr_err("%s can not find socp node\n", __func__);
		goto error;
	}
	base = of_iomap(np, 0);
	if (base != NULL) {
		g_strSocpStat.baseAddr = (unsigned int)base;
	} else {
		pr_err("socp Reg Base Addr ioremap Error!\n");
		goto error;
	}
	pr_info("ioremap0 [%0x]->[%0x]\n", SOCP_REG_BASEADDR,
			g_strSocpStat.baseAddr);
	if (0 == g_strSocpStat.baseAddr) {
		pr_info("socp_init: Socp Reg Base Addr ioremap Error.\n");
		return BSP_ERROR;
	}

	memset(&g_stSocpDebugInfo, 0x0, sizeof(SOCP_DEBUG_INFO_S));
#if 0
	/* ´ò¿ªSOCPÊ±ÖÓ */
	sc_base = INTEGRATOR_SC_BASE;
	writel(1 << 11, sc_base + 0x0);
#endif
	g_strSocpStat.u32EncSrcTskID = 0;
	g_strSocpStat.u32DecDstTskID = 0;
	g_strSocpStat.u32EncDstTskID = 0;
	g_strSocpStat.u32DecSrcTskID = 0;

	g_strSocpStat.u32IntEncSrcHeader = 0;
	g_strSocpStat.u32IntEncSrcRD = 0;
	g_strSocpStat.u32IntDecDstTfr = 0;
	g_strSocpStat.u32IntDecDstOvf = 0;
	g_strSocpStat.u32IntEncDstTfr = 0;
	g_strSocpStat.u32IntEncDstOvf = 0;
	g_strSocpStat.u32IntDecSrcErr = 0;

	for (i = 0; i < SOCP_MAX_ENCSRC_CHN; i++) {
		g_strSocpStat.sEncSrcChan[i].u32ChanID = i;
		g_strSocpStat.sEncSrcChan[i].u32ChanEn = SOCP_CHN_DISABLE;
		g_strSocpStat.sEncSrcChan[i].u32AllocStat =
			SOCP_CHN_UNALLOCATED;
		g_strSocpStat.sEncSrcChan[i].u32LastRdSize = 0;
		g_strSocpStat.sEncSrcChan[i].u32DestChanID = 0xff;
		g_strSocpStat.sEncSrcChan[i].u32BypassEn = 0;
		g_strSocpStat.sEncSrcChan[i].ePriority = SOCP_CHAN_PRIORITY_3;
		g_strSocpStat.sEncSrcChan[i].eDataType = SOCP_DATA_TYPE_BUTT;
		g_strSocpStat.sEncSrcChan[i].eDataTypeEn =
			SOCP_DATA_TYPE_EN_BUTT;
		g_strSocpStat.sEncSrcChan[i].eDebugEn = SOCP_ENC_DEBUG_EN_BUTT;
		g_strSocpStat.sEncSrcChan[i].event_cb =
			(socp_event_cb) BSP_NULL;
		g_strSocpStat.sEncSrcChan[i].rd_cb = (socp_rd_cb) BSP_NULL;
	}

	for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++) {
		g_strSocpStat.sEncDstChan[i].u32ChanID = i;
		g_strSocpStat.sEncDstChan[i].u32Thrh = 0;
		g_strSocpStat.sEncDstChan[i].u32SetStat = SOCP_CHN_UNSET;
		g_strSocpStat.sEncDstChan[i].event_cb =
			(socp_event_cb) BSP_NULL;
		g_strSocpStat.sEncDstChan[i].read_cb = (socp_rd_cb) BSP_NULL;
		g_strSocpStat.sEncDstChan[i].eChnEvent = (SOCP_EVENT_E) 0;
	}

	for (i = 0; i < SOCP_MAX_DECSRC_CHN; i++) {
		g_strSocpStat.sDecSrcChan[i].u32ChanID = i;
		g_strSocpStat.sDecSrcChan[i].u32ChanEn = SOCP_CHN_DISABLE;
		g_strSocpStat.sDecSrcChan[i].eDataTypeEn =
			SOCP_DATA_TYPE_EN_BUTT;
		g_strSocpStat.sDecSrcChan[i].u32SetStat = SOCP_CHN_UNSET;
		g_strSocpStat.sDecSrcChan[i].event_cb =
			(socp_event_cb) BSP_NULL;
		g_strSocpStat.sDecSrcChan[i].rd_cb = (socp_rd_cb) BSP_NULL;
	}

	for (i = 0; i < SOCP_MAX_DECDST_CHN; i++) {
		g_strSocpStat.sDecDstChan[i].u32ChanID = i;
		g_strSocpStat.sDecDstChan[i].u32AllocStat =
			SOCP_CHN_UNALLOCATED;
		g_strSocpStat.sDecDstChan[i].eDataType = SOCP_DATA_TYPE_BUTT;
		g_strSocpStat.sDecDstChan[i].event_cb =
			(socp_event_cb) BSP_NULL;
		g_strSocpStat.sDecDstChan[i].read_cb = (socp_rd_cb) BSP_NULL;
	}

	SOCP_REG_WRITE(SOCP_REG_GBLRST, 1);

	for (i = 0; i < SOCP_RESET_TIME; i++) {
		SOCP_REG_READ(SOCP_REG_GBLRST, u32ResetValue);
		if (0 == u32ResetValue)
			break;
		if ((SOCP_RESET_TIME - 1) == i)
			pr_info("socp_init: reset global regs failed!\n");
	}

	for (i = 0; i < SOCP_TOTAL_ENCSRC_CHN; i++) {
		SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFADDR(i), 0);
		SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFCFG0(i), 0);
		SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQWPTR(i), 0);
		SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQRPTR(i), 0);
		SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQADDR(i), 0);
		SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQCFG(i), 0);
	}
	for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++)
		SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFADDR(i), 0);

	SOCP_REG_WRITE(SOCP_REG_INTTIMEOUT, SOCP_TRANS_TIMEOUT_DEFAULT);
	SOCP_REG_SETBITS(SOCP_REG_BUFTIMEOUT, 31, 1, 0);
	SOCP_REG_SETBITS(SOCP_REG_BUFTIMEOUT, 0, 16,
					 SOCP_OVERFLOW_TIMEOUT_DEFAULT);

	SOCP_REG_SETBITS(SOCP_REG_DEC_PKTLEN, 0, 12, SOCP_DEC_PKTLGTH_MAX);
	SOCP_REG_SETBITS(SOCP_REG_DEC_PKTLEN, 12, 5, SOCP_DEC_PKTLGTH_MIN);

	SOCP_REG_WRITE(SOCP_REG_BASEADDR + 0x14, 0xffffffff);

	SOCP_REG_SETBITS(SOCP_REG_ENC_MASK0, 0, 7, 0x7f);
	SOCP_REG_WRITE(SOCP_REG_APP_MASK1, 0xffffffff);
	SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, 0, 7, 0x7f);
	SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, 16, 7, 0x7f);
	SOCP_REG_WRITE(SOCP_REG_APP_MASK3, 0xffffffff);
	SOCP_REG_SETBITS(SOCP_REG_DEC_CORE0MASK0, 0, 16, 0xffff);
	SOCP_REG_SETBITS(SOCP_REG_DEC_MASK1, 0, 24, 0xffffff);
	SOCP_REG_SETBITS(SOCP_REG_DEC_CORE0MASK2, 0, 16, 0xffff);

	irq = irq_of_parse_and_map(np, 0);
	pr_info("socp irq is[%d]\n", irq);
	ret = request_irq(irq, socp_app_int_handler, 0, "SOCP_APP_IRQ", NULL);
	if (BSP_OK != ret) {
		pr_info("socp_init: connect app core int failed.\n");
		return BSP_ERROR;
	}
	ret = socp_init_task();
	if (BSP_OK != ret) {
		pr_info("socp_init: create task failed(0x%x).\n", ret);
		return (s32) ret;
	}

	g_strSocpStat.bInitFlag = BSP_TRUE;
	return BSP_OK;
error:
	return BSP_ERROR;
}

s32 bsp_socp_coder_set_src_chan(SOCP_CODER_SRC_ENUM_U32 enSrcChanID,
								SOCP_CODER_SRC_CHAN_S *pSrcAttr)
{
	u32 start;
	u32 end;
	u32 rdstart = 0;
	u32 rdend = 0;
	u32 buflength = 0;
	u32 Rdbuflength = 0;
	u32 i;
	u32 srcChanId;
	u32 u32SrcChanType;
	u32 u32DstChanID;
	u32 u32DstChanType;
	u32 ResetFlag;
	SOCP_ENCSRC_CHAN_S *pChan;

	g_stSocpDebugInfo.sSocpDebugGBl.u32SocpAllocEncSrcCnt++;

	SOCP_CHECK_INIT();

	SOCP_CHECK_PARA(pSrcAttr);
	SOCP_CHECK_CHAN_PRIORITY(pSrcAttr->ePriority);
	SOCP_CHECK_DATA_TYPE(pSrcAttr->eDataType);
	SOCP_CHECK_DATA_TYPE_EN(pSrcAttr->eDataTypeEn);
	SOCP_CHECK_ENC_DEBUG_EN(pSrcAttr->eDebugEn);

	srcChanId = SOCP_REAL_CHAN_ID(enSrcChanID);
	u32SrcChanType = SOCP_REAL_CHAN_TYPE(enSrcChanID);

	SOCP_CHECK_CHAN_TYPE(u32SrcChanType, SOCP_CODER_SRC_CHAN);
	SOCP_CHECK_ENCSRC_CHAN_ID(srcChanId);

	u32DstChanID = SOCP_REAL_CHAN_ID(pSrcAttr->u32DestChanID);
	u32DstChanType = SOCP_REAL_CHAN_TYPE(pSrcAttr->u32DestChanID);
	SOCP_CHECK_CHAN_TYPE(u32DstChanType, SOCP_CODER_DEST_CHAN);
	SOCP_CHECK_CHAN_ID(u32DstChanID, SOCP_MAX_ENCDST_CHN);

	if ((SOCP_ENCSRC_CHNMODE_CTSPACKET != pSrcAttr->eMode)
		&& (SOCP_ENCSRC_CHNMODE_LIST != pSrcAttr->eMode)) {
		pr_info("%s: chnnel mode is invalid %d!\n",
				__func__, pSrcAttr->eMode);
		return BSP_ERR_SOCP_INVALID_PARA;
	}

	start = pSrcAttr->sCoderSetSrcBuf.u32InputStart;
	end = pSrcAttr->sCoderSetSrcBuf.u32InputEnd;

	SOCP_CHECK_PARA((void *)start);
	SOCP_CHECK_8BYTESALIGN(start);
	SOCP_CHECK_PARA((void *)end);
	SOCP_CHECK_BUF_ADDR(start, end);
	buflength = end - start + 1;
	SOCP_CHECK_8BYTESALIGN(buflength);
	if (buflength > SOCP_ENC_SRC_BUFLGTH_MAX) {
		pr_info("%s: buffer length is too large!\n", __func__);
		return BSP_ERR_SOCP_INVALID_PARA;
	}

	if (SOCP_ENCSRC_CHNMODE_LIST == pSrcAttr->eMode) {
		rdstart = pSrcAttr->sCoderSetSrcBuf.u32RDStart;
		rdend = pSrcAttr->sCoderSetSrcBuf.u32RDEnd;

		SOCP_CHECK_PARA((void *)rdstart);
		SOCP_CHECK_8BYTESALIGN(rdstart);
		SOCP_CHECK_PARA((void *)rdend);
		SOCP_CHECK_BUF_ADDR(rdstart, rdend);
		/* RD threshold not used */
		Rdbuflength = rdend - rdstart + 1;
		SOCP_CHECK_8BYTESALIGN(Rdbuflength);
		if (Rdbuflength > SOCP_ENC_SRC_RDLGTH_MAX) {
			pr_info("%s: RD buffer length is too large!\n", __func__);
			return BSP_ERR_SOCP_INVALID_PARA;
		}
	}

	SOCP_REG_SETBITS(SOCP_REG_ENCRST, srcChanId, 1, 1);

	for (i = 0; i < SOCP_RESET_TIME; i++) {
		ResetFlag = SOCP_REG_GETBITS(SOCP_REG_ENCRST, srcChanId, 1);
		if (0 == ResetFlag)
			break;

		if ((SOCP_RESET_TIME - 1) == i)
			pr_info("%s: reset channel 0x%x failed!\n", __func__, srcChanId);
	}

	SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFADDR(srcChanId),
				   SOCP_VIRT_PHY(start));
	SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFWPTR(srcChanId),
				   SOCP_VIRT_PHY(start));
	SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFRPTR(srcChanId),
				   SOCP_VIRT_PHY(start));
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(srcChanId), 0, 27, buflength);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(srcChanId), 27, 5, 0);

	if (SOCP_ENCSRC_CHNMODE_LIST == pSrcAttr->eMode) {
		SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQADDR(srcChanId),
					   SOCP_VIRT_PHY(rdstart));
		SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQRPTR(srcChanId),
					   SOCP_VIRT_PHY(rdstart));
		SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQWPTR(srcChanId),
					   SOCP_VIRT_PHY(rdstart));
		pr_info("%s: ID %d, RD VBuf addr 0x%X, RD PBuf addr 0x%X\n",
				__func__, srcChanId, rdstart, SOCP_VIRT_PHY(rdstart));
		SOCP_REG_SETBITS(SOCP_REG_ENCSRC_RDQCFG(srcChanId), 0, 16,
						 Rdbuflength);
		SOCP_REG_SETBITS(SOCP_REG_ENCSRC_RDQCFG(srcChanId), 16, 16, 0);
	}

	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(srcChanId), 1, 2,
					 pSrcAttr->eMode);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(srcChanId), 4, 4,
					 pSrcAttr->u32DestChanID);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(srcChanId), 8, 2,
					 pSrcAttr->ePriority);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(srcChanId), 10, 1,
					 pSrcAttr->u32BypassEn);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(srcChanId), 11, 1,
					 pSrcAttr->eDataTypeEn);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(srcChanId), 31, 1,
					 pSrcAttr->eDebugEn);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(srcChanId), 16, 8,
					 pSrcAttr->eDataType);

	pChan = &g_strSocpStat.sEncSrcChan[srcChanId];
	pChan->eChnMode = pSrcAttr->eMode;
	pChan->ePriority = pSrcAttr->ePriority;
	pChan->eDataType = pSrcAttr->eDataType;
	pChan->eDataTypeEn = pSrcAttr->eDataTypeEn;
	pChan->eDebugEn = pSrcAttr->eDebugEn;
	pChan->u32DestChanID = pSrcAttr->u32DestChanID;
	pChan->u32BypassEn = pSrcAttr->u32BypassEn;
	pChan->sEncSrcBuf.u32Start = start;
	pChan->sEncSrcBuf.u32End = end;
	pChan->sEncSrcBuf.u32Write = start;
	pChan->sEncSrcBuf.u32Read = start;
	pChan->sEncSrcBuf.u32Length = buflength;
	pChan->sEncSrcBuf.u32IdleSize = 0;

	if (SOCP_ENCSRC_CHNMODE_LIST == pSrcAttr->eMode) {
		pChan->sRdBuf.u32Start = rdstart;
		pChan->sRdBuf.u32End = rdend;
		pChan->sRdBuf.u32Write = rdstart;
		pChan->sRdBuf.u32Read = rdstart;
		pChan->sRdBuf.u32Length = Rdbuflength;
		pChan->u32RdThreshold =
			pSrcAttr->sCoderSetSrcBuf.u32RDThreshold;
	}

	g_strSocpStat.sEncSrcChan[srcChanId].u32AllocStat = SOCP_CHN_ALLOCATED;
	g_stSocpDebugInfo.sSocpDebugGBl.u32SocpAllocEncSrcSucCnt++;
	return BSP_OK;

}

s32 bsp_socp_decoder_set_dest_chan(SOCP_DECODER_DST_ENUM_U32 enDestChanID,
								   SOCP_DECODER_DEST_CHAN_S *pAttr)
{
	u32 start;
	u32 end;
	u32 bufThreshold;
	u32 buflength;
	u32 u32ChanID;
	u32 u32SrcChanID;
	u32 u32ChanType;
	SOCP_DECDST_CHAN_S *pChan;

	g_stSocpDebugInfo.sSocpDebugGBl.u32SocpAllocDecDstCnt++;

	SOCP_CHECK_INIT();

	SOCP_CHECK_PARA(pAttr);
	SOCP_CHECK_DATA_TYPE(pAttr->eDataType);

	u32ChanID = SOCP_REAL_CHAN_ID(enDestChanID);
	u32ChanType = SOCP_REAL_CHAN_TYPE(enDestChanID);
	SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_DEST_CHAN);
	SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECDST_CHN);

	u32SrcChanID = SOCP_REAL_CHAN_ID(pAttr->u32SrcChanID);
	u32ChanType = SOCP_REAL_CHAN_TYPE(pAttr->u32SrcChanID);
	SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_SRC_CHAN);
	SOCP_CHECK_CHAN_ID(u32SrcChanID, SOCP_MAX_DECSRC_CHN);

	if (u32SrcChanID != u32ChanID % 4) {
		pr_info("%s: dest ID(%d) is not matching src ID(%d)!\n",
				__func__, u32ChanID, u32SrcChanID);
		return BSP_ERR_SOCP_INVALID_PARA;
	}

	start = pAttr->sDecoderDstSetBuf.u32OutputStart;
	end = pAttr->sDecoderDstSetBuf.u32OutputEnd;
	bufThreshold = pAttr->sDecoderDstSetBuf.u32Threshold;
	SOCP_CHECK_PARA((void *)start);
	SOCP_CHECK_8BYTESALIGN(start);
	SOCP_CHECK_PARA((void *)end);
	SOCP_CHECK_BUF_ADDR(start, end);
	if (bufThreshold > SOCP_DEC_DST_TH_MAX || bufThreshold == 0) {
		pr_info("%s: buffer threshold is too large!\n", __func__);
		return BSP_ERR_SOCP_INVALID_PARA;
	}

	buflength = end - start + 1;
	SOCP_CHECK_8BYTESALIGN(buflength);
	if (buflength > SOCP_DEC_DST_BUFLGTH_MAX) {
		pr_info("%s: buffer length is too large!\n", __func__);
		return BSP_ERR_SOCP_INVALID_PARA;
	}

	SOCP_REG_SETBITS(SOCP_REG_DECDEST_BUFCFG(u32ChanID), 24, 8,
					 pAttr->eDataType);
	SOCP_REG_WRITE(SOCP_REG_DECDEST_BUFRPTR(u32ChanID),
				   SOCP_VIRT_PHY(start));
	SOCP_REG_WRITE(SOCP_REG_DECDEST_BUFADDR(u32ChanID),
				   SOCP_VIRT_PHY(start));
	SOCP_REG_WRITE(SOCP_REG_DECDEST_BUFWPTR(u32ChanID),
				   SOCP_VIRT_PHY(start));
	SOCP_REG_SETBITS(SOCP_REG_DECDEST_BUFCFG(u32ChanID), 0, 16, buflength);
	SOCP_REG_SETBITS(SOCP_REG_DECDEST_BUFCFG(u32ChanID), 16, 8,
					 bufThreshold);

	pChan = &g_strSocpStat.sDecDstChan[u32ChanID];
	pChan->eDataType = pAttr->eDataType;
	pChan->sDecDstBuf.u32Start = start;
	pChan->sDecDstBuf.u32End = end;
	pChan->sDecDstBuf.u32Length = buflength;
	pChan->sDecDstBuf.u32Read = start;
	pChan->sDecDstBuf.u32Write = start;

	SOCP_REG_SETBITS(SOCP_REG_DEC_RAWINT0, u32ChanID, 1, 1);
	SOCP_REG_SETBITS(SOCP_REG_DEC_CORE0MASK0, u32ChanID, 1, 0);
	SOCP_REG_SETBITS(SOCP_REG_DEC_RAWINT2, u32ChanID, 1, 1);
	SOCP_REG_SETBITS(SOCP_REG_DEC_CORE0MASK2, u32ChanID, 1, 0);

	g_strSocpStat.sDecDstChan[u32ChanID].u32AllocStat = SOCP_CHN_ALLOCATED;
	g_stSocpDebugInfo.sSocpDebugGBl.u32SocpAllocDecDstSucCnt++;

	return BSP_OK;
}

s32 bsp_socp_coder_set_dest_chan_attr(u32 u32DestChanID,
									  SOCP_CODER_DEST_CHAN_S *pDestAttr)
{
	u32 start;
	u32 end;
	u32 bufThreshold;
	u32 buflength;
	u32 u32ChanID;
	u32 u32ChanType;
	u32 u32Thrh;
	SOCP_ENCDST_CHAN_S *pChan;

	g_stSocpDebugInfo.sSocpDebugGBl.u32SocpSetEncDstCnt++;

	SOCP_CHECK_INIT();

	SOCP_CHECK_PARA(pDestAttr);
	u32ChanID = SOCP_REAL_CHAN_ID(u32DestChanID);
	u32ChanType = SOCP_REAL_CHAN_TYPE(u32DestChanID);
	SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_CODER_DEST_CHAN);
	SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_ENCDST_CHN);

	start = pDestAttr->sCoderSetDstBuf.u32OutputStart;
	end = pDestAttr->sCoderSetDstBuf.u32OutputEnd;
	bufThreshold = pDestAttr->sCoderSetDstBuf.u32Threshold;
	u32Thrh = pDestAttr->u32EncDstThrh;

	SOCP_CHECK_PARA((void *)start);
	SOCP_CHECK_8BYTESALIGN(start);
	SOCP_CHECK_PARA((void *)end);
	SOCP_CHECK_BUF_ADDR(start, end);
	if (bufThreshold == 0) {
		pr_info("bufThreshold is 0\n");
		return BSP_ERR_SOCP_INVALID_PARA;
	}

	buflength = end - start + 1;
	SOCP_CHECK_8BYTESALIGN(buflength);
	if (buflength > SOCP_ENC_DST_BUFLGTH_MAX) {
		pr_info("%s: buffer length is too large!\n", __func__);
		return BSP_ERR_SOCP_INVALID_PARA;
	}

	if (bufThreshold > SOCP_ENC_DST_TH_MAX) {
		pr_info("%s: buffer threshold is too large!\n", __func__);
		return BSP_ERR_SOCP_INVALID_PARA;
	}

	pChan = &g_strSocpStat.sEncDstChan[u32ChanID];
	if (!pChan->u32SetStat) {
		SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFADDR(u32ChanID),
					   SOCP_VIRT_PHY(start));
		SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFRPTR(u32ChanID),
					   SOCP_VIRT_PHY(start));
		SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFWPTR(u32ChanID),
					   SOCP_VIRT_PHY(start));
		SOCP_REG_SETBITS(SOCP_REG_ENCDEST_BUFCFG(u32ChanID), 0, 21,
						 buflength);
		SOCP_REG_SETBITS(SOCP_REG_ENCDEST_BUFCFG(u32ChanID), 21, 11,
						 bufThreshold);
		SOCP_REG_SETBITS(SOCP_REG_ENCDEST_BUFTHRH(u32ChanID), 0, 31,
						 u32Thrh);

		pChan->u32ChanID = u32ChanID;
		pChan->u32Thrh = u32Thrh;
		pChan->sEncDstBuf.u32Start = start;
		pChan->sEncDstBuf.u32End = end;
		pChan->sEncDstBuf.u32Write = start;
		pChan->sEncDstBuf.u32Read = start;
		pChan->sEncDstBuf.u32Length = buflength;

		pChan->u32SetStat = SOCP_CHN_SET;

		SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT0, u32ChanID, 1, 1);
		SOCP_REG_SETBITS(SOCP_REG_ENC_MASK0, u32ChanID, 1, 0);
		SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT2, u32ChanID, 1, 1);
		SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, u32ChanID, 1, 0);

		SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT2, u32ChanID + 16, 1, 1);
		SOCP_REG_SETBITS(SOCP_REG_ENC_MASK2, u32ChanID + 16, 1, 0);
	} else {
		pr_info("%s: channel 0x%x can't be set twice!\n", __func__, u32ChanID);
		return BSP_ERR_SOCP_SET_FAIL;
	}

	pr_info("%s:ID %d VBuf addr 0x%X PBuf addr 0x%X Buf Len 0x%X\n",
			__func__, u32DestChanID, start, SOCP_VIRT_PHY(start),
			buflength);

	g_stSocpDebugInfo.sSocpDebugGBl.u32SocpSetEncDstSucCnt++;

	return BSP_OK;
}

s32 bsp_socp_decoder_set_src_chan_attr(u32 u32SrcChanID,
									   SOCP_DECODER_SRC_CHAN_S *pInputAttr)
{
	u32 start;
	u32 end;
	u32 buflength = 0;
	u32 u32ChanID;
	u32 u32ChanType;
	u32 i;
	u32 u32ResetFlag;
	SOCP_DECSRC_CHAN_S *pDecSrcChan;

	g_stSocpDebugInfo.sSocpDebugGBl.u32SocpSetDecSrcCnt++;

	SOCP_CHECK_INIT();

	SOCP_CHECK_PARA(pInputAttr);
	u32ChanID = SOCP_REAL_CHAN_ID(u32SrcChanID);
	u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);
	SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_SRC_CHAN);
	SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECSRC_CHN);
	SOCP_CHECK_DATA_TYPE_EN(pInputAttr->eDataTypeEn);

	start = pInputAttr->sDecoderSetSrcBuf.u32InputStart;
	end = pInputAttr->sDecoderSetSrcBuf.u32InputEnd;
	SOCP_CHECK_PARA((void *)start);
	SOCP_CHECK_8BYTESALIGN(start);
	SOCP_CHECK_PARA((void *)end);
	SOCP_CHECK_BUF_ADDR(start, end);
	buflength = end - start + 1;
	SOCP_CHECK_8BYTESALIGN(buflength);
	if (buflength > SOCP_DEC_SRC_BUFLGTH_MAX) {
		pr_info("%s: buffer length is too large!\n", __func__);
		return BSP_ERR_SOCP_INVALID_PARA;
	}

	pDecSrcChan = &g_strSocpStat.sDecSrcChan[u32ChanID];
	if (SOCP_CHN_SET == pDecSrcChan->u32SetStat) {
		pr_info("%s: channel 0x%x has been configed!\n",
				__func__, u32ChanID);
		return BSP_ERR_SOCP_DECSRC_SET;
	}

	SOCP_REG_SETBITS(SOCP_REG_DECRST, u32ChanID, 1, 1);

	for (i = 0; i < SOCP_RESET_TIME; i++) {
		u32ResetFlag = SOCP_REG_GETBITS(SOCP_REG_DECRST, u32ChanID, 1);
		if (0 == u32ResetFlag)
			break;

		if ((SOCP_RESET_TIME - 1) == i) {
			pr_info("%s: reset channel 0x%x failed!\n",
					__func__, u32ChanID);
		}
	}

	SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFWPTR(u32ChanID),
				   SOCP_VIRT_PHY(start));
	SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFADDR(u32ChanID),
				   SOCP_VIRT_PHY(start));
	SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFRPTR(u32ChanID),
				   SOCP_VIRT_PHY(start));
	SOCP_REG_SETBITS(SOCP_REG_DECSRC_BUFCFG0(u32ChanID), 0, 16, buflength);
	SOCP_REG_SETBITS(SOCP_REG_DECSRC_BUFCFG0(u32ChanID), 31, 1,
					 pInputAttr->eDataTypeEn);

	pDecSrcChan->u32ChanID = u32ChanID;
	pDecSrcChan->eDataTypeEn = pInputAttr->eDataTypeEn;
	pDecSrcChan->sDecSrcBuf.u32Start = start;
	pDecSrcChan->sDecSrcBuf.u32End = end;
	pDecSrcChan->sDecSrcBuf.u32Length = buflength;
	pDecSrcChan->sDecSrcBuf.u32Read = start;
	pDecSrcChan->sDecSrcBuf.u32Write = start;

	pDecSrcChan->u32SetStat = SOCP_CHN_SET;

	g_stSocpDebugInfo.sSocpDebugGBl.u32SocpSetDeSrcSucCnt++;

	return BSP_OK;
}

s32 bsp_socp_decoder_get_err_cnt(u32 u32DstChanID,
								 SOCP_DECODER_ERROR_CNT_S *pErrCnt)
{
	u32 u32ChanID;
	u32 u32ChanType;

	SOCP_CHECK_INIT();

	u32ChanID = SOCP_REAL_CHAN_ID(u32DstChanID);
	u32ChanType = SOCP_REAL_CHAN_TYPE(u32DstChanID);
	SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_SRC_CHAN);
	SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECSRC_CHN);
	SOCP_CHECK_DECSRC_SET(u32ChanID);

	SOCP_CHECK_PARA(pErrCnt);

	if (g_strSocpStat.sDecSrcChan[u32ChanID].u32ChanEn) {
		pErrCnt->u32PktlengthCnt =
			SOCP_REG_GETBITS(SOCP_REG_DEC_BUFSTAT0(u32ChanID), 16, 16);
		pErrCnt->u32CrcCnt =
			SOCP_REG_GETBITS(SOCP_REG_DEC_BUFSTAT0(u32ChanID), 0, 16);
		pErrCnt->u32DataTypeCnt =
			SOCP_REG_GETBITS(SOCP_REG_DEC_BUFSTAT1(u32ChanID), 16, 16);
		pErrCnt->u32HdlcHeaderCnt =
			SOCP_REG_GETBITS(SOCP_REG_DEC_BUFSTAT1(u32ChanID), 0, 16);
	} else {
		pr_info("DecoderGetErrCnt: debug mode is closed!\n");
		return BSP_ERR_SOCP_SET_FAIL;
	}

	return BSP_OK;
}
s32 bsp_socp_set_timeout(SOCP_TIMEOUT_EN_E eTmOutEn, u32 u32Timeout)
{
	SOCP_CHECK_INIT();

	if (u32Timeout > SOCP_TIMEOUT_MAX) {
		pr_info("SetTimeout: the value is too large!\n");
		return BSP_ERR_SOCP_INVALID_PARA;
	}

	switch (eTmOutEn) {
		case SOCP_TIMEOUT_BUFOVF_DISABLE: {
			SOCP_REG_SETBITS(SOCP_REG_BUFTIMEOUT, 31, 1, 0);
			break;
		}
		case SOCP_TIMEOUT_BUFOVF_ENABLE: {
			SOCP_REG_SETBITS(SOCP_REG_BUFTIMEOUT, 31, 1, 1);
			SOCP_REG_SETBITS(SOCP_REG_BUFTIMEOUT, 0, 16,
							 u32Timeout);
			break;
		}
		case SOCP_TIMEOUT_TRF: {
			SOCP_REG_WRITE(SOCP_REG_INTTIMEOUT, u32Timeout);
			break;
		}
		default: {
			pr_info("SetTimeout: invalid timeout choice type!\n");
			return BSP_ERR_SOCP_SET_FAIL;
		}
	}

	return BSP_OK;
}

s32 bsp_socp_set_dec_pkt_lgth(SOCP_DEC_PKTLGTH_S *pPktlgth)
{
	u32 u32PktMaxLgth;
	u32 u32PktMinLgth;

	SOCP_CHECK_INIT();

	SOCP_CHECK_PARA(pPktlgth);
	u32PktMaxLgth = pPktlgth->u32PktMax;
	u32PktMinLgth = pPktlgth->u32PktMin;

	if (u32PktMaxLgth * 1024 > SOCP_DEC_MAXPKT_MAX) {
		pr_info("%s: u32PktMaxLgth 0x%x is too large!\n",
				__func__, u32PktMaxLgth);
		return BSP_ERR_SOCP_INVALID_PARA;
	}

	if (u32PktMinLgth > SOCP_DEC_MINPKT_MAX) {
		pr_info("%s: u32PktMinLgth 0x%x is too large!\n",
				__func__, u32PktMinLgth);
		return BSP_ERR_SOCP_INVALID_PARA;
	}

	if ((u32PktMaxLgth * 1024) < u32PktMinLgth) {
		pr_info("%s: max length is snmaller than min length!\n",
				__func__);
		return BSP_ERR_SOCP_INVALID_PARA;
	}

	SOCP_REG_SETBITS(SOCP_REG_DEC_PKTLEN, 0, 12, u32PktMaxLgth);
	SOCP_REG_SETBITS(SOCP_REG_DEC_PKTLEN, 12, 5, u32PktMinLgth);

	return BSP_OK;
}

s32 bsp_socp_set_debug(u32 u32DecChanID, u32 u32DebugEn)
{
	u32 u32ChanID;
	u32 u32ChanType;

	SOCP_CHECK_INIT();

	u32ChanID = SOCP_REAL_CHAN_ID(u32DecChanID);
	u32ChanType = SOCP_REAL_CHAN_TYPE(u32DecChanID);
	SOCP_CHECK_CHAN_TYPE(u32ChanType, SOCP_DECODER_SRC_CHAN);
	SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECSRC_CHN);
	SOCP_CHECK_DECSRC_SET(u32ChanID);

	if (g_strSocpStat.sDecSrcChan[u32ChanID].u32ChanEn) {
		pr_info("%s: decoder channel is open, can't set debug bit\n",
				__func__);
		return BSP_ERR_SOCP_SET_FAIL;
	} else {
		SOCP_REG_SETBITS(SOCP_REG_DECSRC_BUFCFG0(u32ChanID), 29, 1,
						 u32DebugEn);
	}

	return BSP_OK;
}

s32 bsp_socp_free_channel(u32 u32ChanID)
{
	u32 u32RealChanID;
	u32 u32ChanType;

	SOCP_CHECK_INIT();

	u32RealChanID = SOCP_REAL_CHAN_ID(u32ChanID);
	u32ChanType = SOCP_REAL_CHAN_TYPE(u32ChanID);

	if (SOCP_CODER_SRC_CHAN == u32ChanType) {
		SOCP_ENCSRC_CHAN_S *pChan;

		SOCP_CHECK_ENCSRC_CHAN_ID(u32RealChanID);
		SOCP_CHECK_ENCSRC_ALLOC(u32RealChanID);

		pChan = &g_strSocpStat.sEncSrcChan[u32RealChanID];
		if (SOCP_CHN_ENABLE == pChan->u32ChanEn) {
			pr_info("FreeChannel: chan 0x%x is running!\n",
					u32ChanID);
			return BSP_ERR_SOCP_CHAN_RUNNING;
		}

		(void)socp_reset_enc_chan(u32RealChanID);

		pChan->u32AllocStat = SOCP_CHN_UNALLOCATED;

		g_stSocpDebugInfo.sSocpDebugEncSrc.
		u32SocpFreeEncSrcCnt[u32RealChanID]++;
	} else if (SOCP_DECODER_DEST_CHAN == u32ChanType) {
		SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_DECDST_CHN);
		SOCP_CHECK_DECDST_ALLOC(u32RealChanID);

		SOCP_REG_SETBITS(SOCP_REG_DECDEST_BUFCFG(u32RealChanID), 24, 8,
						 0xff);

		g_strSocpStat.sDecDstChan[u32RealChanID].u32AllocStat =
			SOCP_CHN_UNALLOCATED;

		g_stSocpDebugInfo.sSocpDebugDecDst.
		u32SocpFreeDecDstCnt[u32RealChanID]++;
	} else {
		pr_info("FreeChannel: invalid chan type 0x%x!\n", u32ChanType);
		return BSP_ERR_SOCP_INVALID_CHAN;
	}

	return BSP_OK;
}

s32 bsp_socp_chan_soft_reset(u32 u32ChanID)
{
	u32 u32RealChanID;
	u32 u32ChanType;

	SOCP_CHECK_INIT();

	u32RealChanID = SOCP_REAL_CHAN_ID(u32ChanID);
	u32ChanType = SOCP_REAL_CHAN_TYPE(u32ChanID);
	if (SOCP_CODER_SRC_CHAN == u32ChanType) {
		if (u32RealChanID < SOCP_CCORE_ENCSRC_CHN_BASE) {
			SOCP_CHECK_ENCSRC_ALLOC(u32RealChanID);
			(void)socp_reset_enc_chan(u32RealChanID);
		} else if ((u32RealChanID >= SOCP_CODER_SRC_LBBP1)
				   && (u32RealChanID < SOCP_CODER_SRC_LBBP9)) {
			(void)socp_reset_bbp_log_chan(u32RealChanID);
		} else if (SOCP_CODER_SRC_LBBP9 == u32RealChanID) {
			(void)socp_reset_bbp_ds_chan(u32RealChanID);
		} else if (SOCP_CODER_SRC_LDSP1 == u32RealChanID) {
			(void)socp_reset_dsp_log_chan(u32RealChanID);
		} else {
			printk
			("ChnSoftReset: reset enc src chan 0x%x failed!\n",
			 u32ChanID);
			return BSP_ERR_SOCP_INVALID_CHAN;
		}

		g_stSocpDebugInfo.sSocpDebugEncSrc.
		u32SocpSoftResetEncSrcCnt[u32RealChanID]++;
	} else if (SOCP_DECODER_SRC_CHAN == u32ChanType) {
		SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_DECSRC_CHN);
		SOCP_CHECK_DECSRC_SET(u32RealChanID);

		(void)socp_reset_dec_chan(u32RealChanID);

		g_stSocpDebugInfo.sSocpDebugDecSrc.
		u32SocpSoftResetDecSrcCnt[u32RealChanID]++;
	} else {
		pr_info("ChnSoftReset: invalid chan type: 0x%x!\n",
				u32ChanType);
		return BSP_ERR_SOCP_INVALID_CHAN;
	}

	return BSP_OK;
}

s32 bsp_socp_start(u32 u32SrcChanID)
{
	u32 u32RealChanID;
	u32 u32ChanType;
	u32 u32Logic = (u32) 1;
	u32 u32DstId;
	u32 i;
	u32 IntIDMask = 0;

	SOCP_CHECK_INIT();

	u32RealChanID = SOCP_REAL_CHAN_ID(u32SrcChanID);
	u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);

	if (SOCP_CODER_SRC_CHAN == u32ChanType) {
		if (u32RealChanID < SOCP_MAX_ENCSRC_CHN) {
			SOCP_CHECK_ENCSRC_CHAN_ID(u32RealChanID);
			SOCP_CHECK_ENCSRC_ALLOC(u32RealChanID);
		} else {
			pr_info("Start: enc src 0x%x is valid!\n",
					u32SrcChanID);
			return BSP_ERR_SOCP_INVALID_CHAN;
		}

		u32DstId =
			SOCP_REG_GETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32RealChanID), 4,
							 4);
		if (SOCP_CHN_SET !=
			g_strSocpStat.sEncDstChan[u32DstId].u32SetStat) {
			pr_info("AppStart: enc dst chan is valid!\n");
			return BSP_ERR_SOCP_DEST_CHAN;
		}

		SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT1, u32RealChanID, 1, 1);
		SOCP_REG_SETBITS(SOCP_REG_APP_MASK1, u32RealChanID, 1, 0);
		if (SOCP_ENCSRC_CHNMODE_LIST ==
			g_strSocpStat.sEncSrcChan[u32RealChanID].eChnMode) {
			SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT3, u32RealChanID, 1, 1);
		}

		SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32RealChanID), 0, 1, 1);
		if (u32RealChanID < SOCP_MAX_ENCSRC_CHN) {
			g_strSocpStat.sEncSrcChan[u32RealChanID].u32ChanEn = SOCP_CHN_ENABLE;
			g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpStartEncSrcCnt[u32RealChanID]++;
		}
	} else if (SOCP_DECODER_SRC_CHAN == u32ChanType) {
		SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_DECSRC_CHN);
		SOCP_CHECK_DECSRC_SET(u32RealChanID);

		if (SOCP_DECSRC_CHNMODE_LIST ==
			g_strSocpStat.sDecSrcChan[u32RealChanID].eChnMode) {
			SOCP_REG_SETBITS(SOCP_REG_DEC_RAWINT1, u32RealChanID, 1, 1);
			SOCP_REG_SETBITS(SOCP_REG_DEC_MASK1, u32RealChanID, 1, 0);
		}

		for (i = 1; i < SOCP_DEC_SRCINT_NUM; i++) {
			IntIDMask = SOCP_REG_GETBITS(SOCP_REG_DEC_RAWINT1, i * 4, 4);
			IntIDMask |= 1 << u32RealChanID;
			SOCP_REG_SETBITS(SOCP_REG_DEC_RAWINT1, i * 4, 4, IntIDMask);

			IntIDMask =
				SOCP_REG_GETBITS(SOCP_REG_DEC_MASK1, i * 4, 4);
			IntIDMask &= ~(u32Logic << u32RealChanID);
			SOCP_REG_SETBITS(SOCP_REG_DEC_MASK1, i * 4, 4, IntIDMask);
		}

		SOCP_REG_SETBITS(SOCP_REG_DECSRC_BUFCFG0(u32RealChanID), 30, 1, 1);
		g_strSocpStat.sDecSrcChan[u32RealChanID].u32ChanEn =
			SOCP_CHN_ENABLE;

		g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpStartDecSrcCnt[u32RealChanID]++;
	} else {
		pr_info("Start: invalid chan type: 0x%x!\n", u32ChanType);
		return BSP_ERR_SOCP_INVALID_CHAN;
	}

	return BSP_OK;
}

s32 bsp_socp_stop(u32 u32SrcChanID)
{
	u32 u32RealChanID;
	u32 u32ChanType;
	u32 IntIDMask = 0;
	u32 i;

	SOCP_CHECK_INIT();

	u32RealChanID = SOCP_REAL_CHAN_ID(u32SrcChanID);
	u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);

	if (SOCP_CODER_SRC_CHAN == u32ChanType) {
		if (u32RealChanID < SOCP_MAX_ENCSRC_CHN) {
			SOCP_CHECK_ENCSRC_CHAN_ID(u32RealChanID);
			SOCP_CHECK_ENCSRC_ALLOC(u32RealChanID);
		} else {
			pr_info("Stop: enc src 0x%x is valid!\n", u32SrcChanID);
			return BSP_ERR_SOCP_INVALID_CHAN;
		}

		SOCP_REG_SETBITS(SOCP_REG_APP_MASK1, u32RealChanID, 1, 1);
		if (SOCP_ENCSRC_CHNMODE_LIST ==
			g_strSocpStat.sEncSrcChan[u32RealChanID].eChnMode) {
			SOCP_REG_SETBITS(SOCP_REG_APP_MASK3, u32RealChanID, 1, 1);
		}

		SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(u32RealChanID), 0, 1, 0);
		if (u32RealChanID < SOCP_MAX_ENCSRC_CHN) {
			g_strSocpStat.sEncSrcChan[u32RealChanID].u32ChanEn =
				SOCP_CHN_DISABLE;
			g_stSocpDebugInfo.sSocpDebugEncSrc.
			u32SocpStopEncSrcCnt[u32RealChanID]++;
		}
	} else if (SOCP_DECODER_SRC_CHAN == u32ChanType) {
		SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_DECSRC_CHN);
		SOCP_CHECK_DECSRC_SET(u32RealChanID);

		if (SOCP_DECSRC_CHNMODE_LIST ==
			g_strSocpStat.sDecSrcChan[u32RealChanID].eChnMode) {
			SOCP_REG_SETBITS(SOCP_REG_DEC_CORE0MASK0, u32RealChanID, 1, 1);
		}

		for (i = 1; i < SOCP_DEC_SRCINT_NUM; i++) {
			IntIDMask =
				SOCP_REG_GETBITS(SOCP_REG_DEC_MASK1, i * 4, 4);
			IntIDMask |= 1 << u32RealChanID;
			SOCP_REG_SETBITS(SOCP_REG_DEC_CORE0MASK0, i * 4, 4, IntIDMask);
		}

		SOCP_REG_SETBITS(SOCP_REG_DECSRC_BUFCFG0(u32RealChanID), 30, 1, 0);
		g_strSocpStat.sDecSrcChan[u32RealChanID].u32ChanEn =
			SOCP_CHN_DISABLE;

		g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpStopDecSrcCnt[u32RealChanID]++;
	} else {
		pr_info("Stop: invalid chan type: 0x%x!\n", u32ChanType);
		return BSP_ERR_SOCP_INVALID_CHAN;
	}

	return BSP_OK;
}

s32 bsp_socp_register_event_cb(u32 u32ChanID, socp_event_cb EventCB)
{
	u32 u32RealChanID;
	u32 u32ChanType;

	SOCP_CHECK_INIT();

	u32RealChanID = SOCP_REAL_CHAN_ID(u32ChanID);
	u32ChanType = SOCP_REAL_CHAN_TYPE(u32ChanID);

	switch (u32ChanType) {
		case SOCP_CODER_SRC_CHAN: {
			if (u32RealChanID < SOCP_MAX_ENCSRC_CHN) {
				SOCP_CHECK_ENCSRC_CHAN_ID(u32RealChanID);
				SOCP_CHECK_ENCSRC_ALLOC(u32RealChanID);
				g_strSocpStat.sEncSrcChan[u32RealChanID].event_cb = EventCB;

				g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpRegEventEncSrcCnt[u32RealChanID]++;
			}
			break;
		}
		case SOCP_CODER_DEST_CHAN: {
			SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_ENCDST_CHN);
			SOCP_CHECK_ENCDST_SET(u32RealChanID);

			g_strSocpStat.sEncDstChan[u32RealChanID].event_cb = EventCB;

			g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpRegEventEncDstCnt[u32RealChanID]++;
			break;
		}
		case SOCP_DECODER_SRC_CHAN: {
			SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_DECSRC_CHN);
			SOCP_CHECK_DECSRC_SET(u32RealChanID);

			g_strSocpStat.sDecSrcChan[u32RealChanID].event_cb = EventCB;

			g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpRegEventDecSrcCnt[u32RealChanID]++;
			break;
		}
		case SOCP_DECODER_DEST_CHAN: {
			SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_DECDST_CHN);
			SOCP_CHECK_DECDST_ALLOC(u32RealChanID);

			g_strSocpStat.sDecDstChan[u32RealChanID].event_cb = EventCB;

			g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpRegEventDecDstCnt[u32RealChanID]++;
			break;
		}
		default: {
			pr_info("RegisterEventCB: invalid chan type: 0x%x!\n",
					u32ChanType);
			return BSP_ERR_SOCP_INVALID_CHAN;
		}
	}

	return BSP_OK;
}

s32 bsp_socp_get_write_buff(u32 u32SrcChanID, SOCP_BUFFER_RW_S *pBuff)
{
	u32 u32ChanID;
	u32 u32ChanType;
	u32 uPAddr;

	SOCP_CHECK_INIT();

	SOCP_CHECK_PARA(pBuff);

	u32ChanID = SOCP_REAL_CHAN_ID(u32SrcChanID);
	u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);

	if (SOCP_CODER_SRC_CHAN == u32ChanType) {
		g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpGetWBufEncSrcEtrCnt[u32ChanID]++;

		SOCP_CHECK_ENCSRC_CHAN_ID(u32ChanID);
		SOCP_CHECK_ENCSRC_ALLOC(u32ChanID);

		SOCP_REG_READ(SOCP_REG_ENCSRC_BUFRPTR(u32ChanID), uPAddr);
		g_strSocpStat.sEncSrcChan[u32ChanID].sEncSrcBuf.u32Read =
			(u32)SOCP_PHY_VIRT(uPAddr);
		SOCP_REG_READ(SOCP_REG_ENCSRC_BUFWPTR(u32ChanID), uPAddr);
		g_strSocpStat.sEncSrcChan[u32ChanID].sEncSrcBuf.u32Write =
			(u32)SOCP_PHY_VIRT(uPAddr);
		socp_get_idle_buffer(&g_strSocpStat.sEncSrcChan[u32ChanID].sEncSrcBuf, pBuff);
		g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpGetWBufEncSrcSucCnt[u32ChanID]++;
	} else if (SOCP_DECODER_SRC_CHAN == u32ChanType) {
		g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpGetWBufDecSrcEtrCnt[u32ChanID]++;

		SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECSRC_CHN);
		SOCP_CHECK_DECSRC_SET(u32ChanID);
		SOCP_REG_READ(SOCP_REG_DECSRC_BUFRPTR(u32ChanID), uPAddr);
		g_strSocpStat.sDecSrcChan[u32ChanID].sDecSrcBuf.u32Read =
			(u32)SOCP_PHY_VIRT(uPAddr);
		SOCP_REG_READ(SOCP_REG_DECSRC_BUFWPTR(u32ChanID), uPAddr);
		g_strSocpStat.sDecSrcChan[u32ChanID].sDecSrcBuf.u32Write =
			(u32)SOCP_PHY_VIRT(uPAddr);
		socp_get_idle_buffer(&g_strSocpStat.sDecSrcChan[u32ChanID].sDecSrcBuf, pBuff);
		g_stSocpDebugInfo.sSocpDebugDecSrc.u32SocpGetWBufDecSrcSucCnt[u32ChanID]++;
	} else {
		pr_info("GetWriteBuff: invalid chan type: 0x%x!\n", u32ChanType);
		return BSP_ERR_SOCP_INVALID_CHAN;
	}

	return BSP_OK;
}

s32 bsp_socp_write_done(u32 u32SrcChanID, u32 u32WrtSize)
{
	u32 u32ChanID;
	u32 u32ChanType;
	u32 u32WrtPad;
	SOCP_BUFFER_RW_S RwBuff;
	u32 uPAddr;

	SOCP_CHECK_INIT();

	if (0 == u32WrtSize) {
		pr_info("write size is 0\n");
		return BSP_ERR_SOCP_NULL;
	}

	u32ChanID = SOCP_REAL_CHAN_ID(u32SrcChanID);
	u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);

	if (SOCP_CODER_SRC_CHAN == u32ChanType) {
		SOCP_ENCSRC_CHAN_S *pChan;

		g_stSocpDebugInfo.sSocpDebugEncSrc.u32socp_write_doneEncSrcEtrCnt[u32ChanID]++;

		SOCP_CHECK_ENCSRC_CHAN_ID(u32ChanID);
		SOCP_CHECK_ENCSRC_ALLOC(u32ChanID);

		pChan = &g_strSocpStat.sEncSrcChan[u32ChanID];
		u32WrtPad = u32WrtSize % 8;
		if (0 != u32WrtPad)
			u32WrtSize += (8 - u32WrtPad);

		SOCP_REG_READ(SOCP_REG_ENCSRC_BUFWPTR(u32ChanID), uPAddr);
		pChan->sEncSrcBuf.u32Write = (u32)SOCP_PHY_VIRT(uPAddr);
		SOCP_REG_READ(SOCP_REG_ENCSRC_BUFRPTR(u32ChanID), uPAddr);
		pChan->sEncSrcBuf.u32Read = (u32)SOCP_PHY_VIRT(uPAddr);

		socp_get_idle_buffer(&pChan->sEncSrcBuf, &RwBuff);

		if (RwBuff.u32Size + RwBuff.u32RbSize < u32WrtSize) {
			pr_info("%s: enc src, too large write size!\n", __func__);
			pr_info("%s: enc src, write ptr is 0x%x, read ptr is 0x%x\n",
					__func__, pChan->sEncSrcBuf.u32Write,
					pChan->sEncSrcBuf.u32Read);
			pr_info("%s: enc src, u32Size is 0x%x, u32RbSize is 0x%x\n",
					__func__, RwBuff.u32Size, RwBuff.u32RbSize);
			pr_info("%s: enc src, u32WrtSize is 0x%x, u32SrcChanID is 0x%x\n",
					__func__, u32WrtSize, u32SrcChanID);
			g_stSocpDebugInfo.sSocpDebugEncSrc.u32socp_write_doneEncSrcFailCnt[u32ChanID]++;
			return BSP_ERR_SOCP_INVALID_PARA;
		}

		socp_write_done(&pChan->sEncSrcBuf, u32WrtSize);

		uPAddr = SOCP_VIRT_PHY(pChan->sEncSrcBuf.u32Write);
		SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFWPTR(u32ChanID), uPAddr);
		g_stSocpDebugInfo.sSocpDebugEncSrc.u32socp_write_doneEncSrcSucCnt[u32ChanID]++;
	} else if (SOCP_DECODER_SRC_CHAN == u32ChanType) {
		SOCP_DECSRC_CHAN_S *pChan;

		g_stSocpDebugInfo.sSocpDebugDecSrc.u32socp_write_doneDecSrcEtrCnt[u32ChanID]++;

		SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECSRC_CHN);
		SOCP_CHECK_DECSRC_SET(u32ChanID);
		pChan = &g_strSocpStat.sDecSrcChan[u32ChanID];
		SOCP_REG_READ(SOCP_REG_DECSRC_BUFWPTR(u32ChanID), uPAddr);
		pChan->sDecSrcBuf.u32Write = (u32)SOCP_PHY_VIRT(uPAddr);
		SOCP_REG_READ(SOCP_REG_DECSRC_BUFRPTR(u32ChanID), uPAddr);
		pChan->sDecSrcBuf.u32Read = (u32)SOCP_PHY_VIRT(uPAddr);
		socp_get_idle_buffer(&pChan->sDecSrcBuf, &RwBuff);

		if (RwBuff.u32Size + RwBuff.u32RbSize < u32WrtSize) {
			pr_info("%s: dec src, too large write size!\n", __func__);
			pr_info("%s: dec src, write ptr is 0x%x, read ptr is 0x%x\n",
					__func__, pChan->sDecSrcBuf.u32Write,
					pChan->sDecSrcBuf.u32Read);
			pr_info("%s: dec src, u32Size is 0x%x, u32RbSize is 0x%x\n",
					__func__, RwBuff.u32Size, RwBuff.u32RbSize);
			pr_info("%s: dec src, u32WrtSize is 0x%x, u32SrcChanID is 0x%x\n",
					__func__, u32WrtSize, u32SrcChanID);
			g_stSocpDebugInfo.sSocpDebugDecSrc.u32socp_write_doneDecSrcFailCnt[u32ChanID]++;

			return BSP_ERR_SOCP_INVALID_PARA;
		}

		socp_write_done(&pChan->sDecSrcBuf, u32WrtSize);

		uPAddr = SOCP_VIRT_PHY(pChan->sDecSrcBuf.u32Write);
		SOCP_REG_WRITE(SOCP_REG_DECSRC_BUFWPTR(u32ChanID), uPAddr);
		g_stSocpDebugInfo.sSocpDebugDecSrc.u32socp_write_doneDecSrcSucCnt[u32ChanID]++;
	} else {
		pr_info("%s: invalid chan type: 0x%x!\n", __func__, u32ChanType);
		return BSP_ERR_SOCP_INVALID_CHAN;
	}

	return BSP_OK;
}

s32 bsp_socp_register_rd_cb(u32 u32SrcChanID, socp_rd_cb RdCB)
{
	u32 u32RealChanID;
	u32 u32ChanType;

	SOCP_CHECK_INIT();

	u32RealChanID = SOCP_REAL_CHAN_ID(u32SrcChanID);
	u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);

	if (SOCP_CODER_SRC_CHAN == u32ChanType) {
		SOCP_CHECK_ENCSRC_CHAN_ID(u32RealChanID);
		SOCP_CHECK_ENCSRC_ALLOC(u32RealChanID);

		if (SOCP_ENCSRC_CHNMODE_LIST ==
			g_strSocpStat.sEncSrcChan[u32RealChanID].eChnMode) {
			g_strSocpStat.sEncSrcChan[u32RealChanID].rd_cb = RdCB;
		} else {
			pr_info("RegisterRdCB: invalid chan mode!\n");
			return BSP_ERR_SOCP_CHAN_MODE;
		}

		g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpRegRdCBEncSrcCnt[u32RealChanID]++;
	} else {
		pr_info("RegisterRdCB: invalid chan type: 0x%x!\n",
				u32ChanType);
		return BSP_ERR_SOCP_INVALID_CHAN;
	}

	return BSP_OK;
}

s32 bsp_socp_get_rd_buffer(u32 u32SrcChanID, SOCP_BUFFER_RW_S *pBuff)
{
	u32 u32ChanID;
	u32 u32ChanType;
	u32 uPAddr;

	SOCP_CHECK_INIT();

	SOCP_CHECK_PARA(pBuff);

	u32ChanID = SOCP_REAL_CHAN_ID(u32SrcChanID);
	u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);

	if (SOCP_CODER_SRC_CHAN == u32ChanType) {
		g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpGetRdBufEncSrcEtrCnt[u32ChanID]++;

		SOCP_CHECK_ENCSRC_CHAN_ID(u32ChanID);
		SOCP_CHECK_ENCSRC_ALLOC(u32ChanID);

		SOCP_REG_READ(SOCP_REG_ENCSRC_RDQRPTR(u32ChanID), uPAddr);
		g_strSocpStat.sEncSrcChan[u32ChanID].sRdBuf.u32Read =
			(u32)SOCP_PHY_VIRT(uPAddr);
		SOCP_REG_READ(SOCP_REG_ENCSRC_RDQWPTR(u32ChanID), uPAddr);
		g_strSocpStat.sEncSrcChan[u32ChanID].sRdBuf.u32Write =
			(u32)SOCP_PHY_VIRT(uPAddr);
		socp_get_data_buffer(&g_strSocpStat.sEncSrcChan[u32ChanID].sRdBuf, pBuff);
		g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpGetRdBufEncSrcSucCnt[u32ChanID]++;
	} else {
		pr_info("GetRDBuffer: invalid chan type: 0x%x!\n", u32ChanType);
		return BSP_ERR_SOCP_INVALID_CHAN;
	}

	return BSP_OK;
}

s32 bsp_socp_read_rd_done(u32 u32SrcChanID, u32 u32RDSize)
{
	u32 u32ChanID;
	u32 u32ChanType;
	SOCP_BUFFER_RW_S RwBuff;
	u32 uPAddr;

	SOCP_CHECK_INIT();

	if (0 == u32RDSize) {
		pr_info("RD size is 0\n");
		return BSP_ERR_SOCP_NULL;
	}

	u32ChanID = SOCP_REAL_CHAN_ID(u32SrcChanID);
	u32ChanType = SOCP_REAL_CHAN_TYPE(u32SrcChanID);

	if (SOCP_CODER_SRC_CHAN == u32ChanType) {
		SOCP_ENCSRC_CHAN_S *pChan;

		g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpReadRdDoneEncSrcEtrCnt[u32ChanID]++;

		SOCP_CHECK_ENCSRC_CHAN_ID(u32ChanID);
		SOCP_CHECK_ENCSRC_ALLOC(u32ChanID);

		pChan = &g_strSocpStat.sEncSrcChan[u32ChanID];
		g_strSocpStat.sEncSrcChan[u32ChanID].u32LastRdSize = 0;

		SOCP_REG_READ(SOCP_REG_ENCSRC_RDQWPTR(u32ChanID), uPAddr);
		pChan->sRdBuf.u32Write = (u32)SOCP_PHY_VIRT(uPAddr);
		SOCP_REG_READ(SOCP_REG_ENCSRC_RDQRPTR(u32ChanID), uPAddr);
		pChan->sRdBuf.u32Read = (u32)SOCP_PHY_VIRT(uPAddr);
		socp_get_data_buffer(&pChan->sRdBuf, &RwBuff);

		if (RwBuff.u32Size + RwBuff.u32RbSize < u32RDSize) {
			pr_info("%s: enc src, too large rd size!\n", __func__);
			pr_info("%s: enc src, write ptr 0x%x, read ptr 0x%x\n",
					__func__, pChan->sRdBuf.u32Write,
					pChan->sRdBuf.u32Read);
			pr_info("%s: enc src Size 0x%x, RbSize 0x%x\n",
					__func__, RwBuff.u32Size, RwBuff.u32RbSize);
			pr_info("%s: enc src RDSize 0x%x, SrcChanID 0x%x\n",
					__func__, u32RDSize, u32SrcChanID);
			g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpReadRdDoneEncSrcFailCnt[u32ChanID]++;

			return BSP_ERR_SOCP_INVALID_PARA;
		}

		socp_read_done(&pChan->sRdBuf, u32RDSize);

		uPAddr = SOCP_VIRT_PHY(pChan->sRdBuf.u32Read);
		SOCP_REG_WRITE(SOCP_REG_ENCSRC_RDQRPTR(u32ChanID), uPAddr);
		g_stSocpDebugInfo.sSocpDebugEncSrc.u32SocpReadRdDoneEncSrcSucCnt[u32ChanID]++;
	} else {
		pr_info("%s: invalid chan type: 0x%x!", __func__, u32ChanType);
		return BSP_ERR_SOCP_INVALID_CHAN;
	}

	return BSP_OK;
}

s32 bsp_socp_register_read_cb(u32 u32DestChanID, socp_read_cb ReadCB)
{
	u32 u32RealChanID;
	u32 u32ChanType;

	SOCP_CHECK_INIT();

	u32RealChanID = SOCP_REAL_CHAN_ID(u32DestChanID);
	u32ChanType = SOCP_REAL_CHAN_TYPE(u32DestChanID);

	if (SOCP_DECODER_DEST_CHAN == u32ChanType) {
		SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_DECDST_CHN);
		SOCP_CHECK_DECDST_ALLOC(u32RealChanID);

		g_strSocpStat.sDecDstChan[u32RealChanID].read_cb = ReadCB;

		g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpRegReadCBDecDstCnt[u32RealChanID]++;
	} else if (SOCP_CODER_DEST_CHAN == u32ChanType) {
		SOCP_CHECK_CHAN_ID(u32RealChanID, SOCP_MAX_ENCDST_CHN);
		SOCP_CHECK_ENCDST_SET(u32RealChanID);

		g_strSocpStat.sEncDstChan[u32RealChanID].read_cb = ReadCB;

		g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpRegReadCBEncDstCnt[u32RealChanID]++;
	} else {
		pr_info("RegisterReadCB: invalid chan type: 0x%x!\n",
				u32ChanType);
		return BSP_ERR_SOCP_INVALID_CHAN;
	}

	return BSP_OK;
}

s32 bsp_socp_get_read_buff(u32 u32DestChanID, SOCP_BUFFER_RW_S *pBuffer)
{
	u32 u32ChanID;
	u32 u32ChanType;
	u32 uPAddr;

	SOCP_CHECK_INIT();

	SOCP_CHECK_PARA(pBuffer);

	u32ChanID = SOCP_REAL_CHAN_ID(u32DestChanID);
	u32ChanType = SOCP_REAL_CHAN_TYPE(u32DestChanID);
	pBuffer->u32Size = 0;
	pBuffer->u32RbSize = 0;

	if (SOCP_DECODER_DEST_CHAN == u32ChanType) {
		g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpGetReadBufDecDstEtrCnt[u32ChanID]++;

		SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECDST_CHN);
		SOCP_CHECK_DECDST_ALLOC(u32ChanID);

		SOCP_REG_READ(SOCP_REG_DECDEST_BUFRPTR(u32ChanID), uPAddr);
		g_strSocpStat.sDecDstChan[u32ChanID].sDecDstBuf.u32Read =
			(u32)SOCP_PHY_VIRT(uPAddr);
		SOCP_REG_READ(SOCP_REG_DECDEST_BUFWPTR(u32ChanID), uPAddr);
		g_strSocpStat.sDecDstChan[u32ChanID].sDecDstBuf.u32Write =
			(u32)SOCP_PHY_VIRT(uPAddr);
		socp_get_data_buffer(&g_strSocpStat.sDecDstChan[u32ChanID].sDecDstBuf, pBuffer);
		g_stSocpDebugInfo.sSocpDebugDecDst.u32SocpGetReadBufDecDstSucCnt[u32ChanID]++;
	} else if (SOCP_CODER_DEST_CHAN == u32ChanType) {
		g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpGetReadBufEncDstEtrCnt[u32ChanID]++;

		SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_ENCDST_CHN);
		SOCP_CHECK_ENCDST_SET(u32ChanID);

		SOCP_REG_READ(SOCP_REG_ENCDEST_BUFRPTR(u32ChanID), uPAddr);
		g_strSocpStat.sEncDstChan[u32ChanID].sEncDstBuf.u32Read =
			(u32)SOCP_PHY_VIRT(uPAddr);
		SOCP_REG_READ(SOCP_REG_ENCDEST_BUFWPTR(u32ChanID), uPAddr);
		g_strSocpStat.sEncDstChan[u32ChanID].sEncDstBuf.u32Write =
			(u32)SOCP_PHY_VIRT(uPAddr);
		socp_get_data_buffer(&g_strSocpStat.sEncDstChan[u32ChanID].sEncDstBuf, pBuffer);
		g_stSocpDebugInfo.sSocpDebugEncDst.u32SocpGetReadBufEncDstSucCnt[u32ChanID]++;
	} else {
		pr_info("GetReadBuff: invalid chan type: 0x%x!\n", u32ChanType);
		return BSP_ERR_SOCP_INVALID_CHAN;
	}

	return BSP_OK;
}

s32 bsp_socp_read_data_done(u32 u32DestChanID, u32 u32ReadSize)
{
	u32 u32ChanID;
	u32 u32ChanType;
	SOCP_BUFFER_RW_S RwBuff;
	u32 uPAddr;
	u32 reg_value;
	unsigned long lock_flag;

	SOCP_CHECK_INIT();


	u32ChanID = SOCP_REAL_CHAN_ID(u32DestChanID);
	u32ChanType = SOCP_REAL_CHAN_TYPE(u32DestChanID);

	if (SOCP_DECODER_DEST_CHAN == u32ChanType) {
		u32 TfMaskReg = 0;
		SOCP_DECDST_CHAN_S *pChan;

		g_stSocpDebugInfo.sSocpDebugDecDst.
		u32socp_read_doneDecDstEtrCnt[u32ChanID]++;

		SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_DECDST_CHN);
		SOCP_CHECK_DECDST_ALLOC(u32ChanID);

		TfMaskReg = SOCP_REG_DEC_CORE0MASK0;
		pChan = &g_strSocpStat.sDecDstChan[u32ChanID];
		SOCP_REG_READ(SOCP_REG_DECDEST_BUFWPTR(u32ChanID), uPAddr);
		pChan->sDecDstBuf.u32Write = (u32)SOCP_PHY_VIRT(uPAddr);
		SOCP_REG_READ(SOCP_REG_DECDEST_BUFRPTR(u32ChanID), uPAddr);
		pChan->sDecDstBuf.u32Read = (u32)SOCP_PHY_VIRT(uPAddr);
		socp_get_data_buffer(&pChan->sDecDstBuf, &RwBuff);

		if (RwBuff.u32Size + RwBuff.u32RbSize < u32ReadSize) {
			pr_info("%s:dec dst too large read size!\n", __func__);
			pr_info("%s:dec dst write ptr 0x%x,read ptr 0x%x\n",
					__func__, pChan->sDecDstBuf.u32Write,
					pChan->sDecDstBuf.u32Read);
			pr_info("%s:dec dst Size 0x%x RbSize 0x%x\n",
					__func__, RwBuff.u32Size, RwBuff.u32RbSize);
			pr_info("%s: dec dst ReadSize 0x%x,DestChanID 0x%x\n",
					__func__, u32ReadSize, u32DestChanID);
			spin_lock_irqsave(&lock, lock_flag);
			SOCP_REG_SETBITS(TfMaskReg, u32ChanID, 1, 0);
			spin_unlock_irqrestore(&lock, lock_flag);
			g_stSocpDebugInfo.sSocpDebugDecDst.u32socp_read_doneDecDstFailCnt[u32ChanID]++;

			return BSP_ERR_SOCP_INVALID_PARA;
		}

		socp_read_done(&pChan->sDecDstBuf, u32ReadSize);

		uPAddr = SOCP_VIRT_PHY(pChan->sDecDstBuf.u32Read);
		SOCP_REG_WRITE(SOCP_REG_DECDEST_BUFRPTR(u32ChanID), uPAddr);
		spin_lock_irqsave(&lock, lock_flag);
		SOCP_REG_SETBITS(TfMaskReg, u32ChanID, 1, 0);
		spin_unlock_irqrestore(&lock, lock_flag);

		if (0 == u32ReadSize)
			g_stSocpDebugInfo.sSocpDebugDecDst.u32socp_read_doneZeroDecDstCnt[u32ChanID]++;
		else
			g_stSocpDebugInfo.sSocpDebugDecDst.u32socp_read_doneValidDecDstCnt[u32ChanID]++;

		g_stSocpDebugInfo.sSocpDebugDecDst.u32socp_read_doneDecDstSucCnt[u32ChanID]++;
	} else if (SOCP_CODER_DEST_CHAN == u32ChanType) {
		SOCP_ENCDST_CHAN_S *pChan;

		g_stSocpDebugInfo.sSocpDebugEncDst.u32socp_read_doneEncDstEtrCnt[u32ChanID]++;

		SOCP_CHECK_CHAN_ID(u32ChanID, SOCP_MAX_ENCDST_CHN);
		SOCP_CHECK_ENCDST_SET(u32ChanID);

		if (0 == u32ReadSize)
			g_stSocpDebugInfo.sSocpDebugEncDst.u32socp_read_doneZeroEncDstCnt[u32ChanID]++;
		else
			g_stSocpDebugInfo.sSocpDebugEncDst.u32socp_read_doneValidEncDstCnt[u32ChanID]++;

		pChan = &g_strSocpStat.sEncDstChan[u32ChanID];
		SOCP_REG_READ(SOCP_REG_ENCDEST_BUFWPTR(u32ChanID), uPAddr);
		pChan->sEncDstBuf.u32Write = (u32)SOCP_PHY_VIRT(uPAddr);
		SOCP_REG_READ(SOCP_REG_ENCDEST_BUFRPTR(u32ChanID), uPAddr);
		pChan->sEncDstBuf.u32Read = (u32)SOCP_PHY_VIRT(uPAddr);
		socp_get_data_buffer(&pChan->sEncDstBuf, &RwBuff);

		if (RwBuff.u32Size + RwBuff.u32RbSize < u32ReadSize) {
			pr_info("%s:enc dst too large read size!\n", __func__);
			pr_info("%s: enc dst write ptr 0x%x read ptr 0x%x\n",
					__func__, pChan->sEncDstBuf.u32Write,
					pChan->sEncDstBuf.u32Read);
			pr_info("%s:enc dst Size 0x%x RbSize 0x%x\n",
					__func__, RwBuff.u32Size, RwBuff.u32RbSize);
			pr_info("%s:enc dst ReadSize 0x%x DestChanID 0x%x\n",
					__func__, u32ReadSize, u32DestChanID);
			spin_lock_irqsave(&lock, lock_flag);
			SOCP_REG_SETBITS(SOCP_REG_ENC_MASK0, u32ChanID, 1, 0);
			spin_unlock_irqrestore(&lock, lock_flag);
			g_stSocpDebugInfo.sSocpDebugEncDst.u32socp_read_doneEncDstFailCnt[u32ChanID]++;
			return BSP_ERR_SOCP_INVALID_PARA;
		}

		socp_read_done(&pChan->sEncDstBuf, u32ReadSize);

		uPAddr = SOCP_VIRT_PHY(pChan->sEncDstBuf.u32Read);
		SOCP_REG_WRITE(SOCP_REG_ENCDEST_BUFRPTR(u32ChanID), uPAddr);
		spin_lock_irqsave(&lock, lock_flag);
		SOCP_REG_READ(SOCP_REG_ENC_MASK0, reg_value);
		reg_value = reg_value & (~(1 << u32ChanID));
		SOCP_REG_WRITE(SOCP_REG_ENC_MASK0, reg_value);
		SOCP_REG_READ(SOCP_REG_ENC_MASK2, reg_value);
		reg_value = reg_value & (~(1 << (u32ChanID+16)));
		SOCP_REG_WRITE(SOCP_REG_ENC_MASK2, reg_value);
		spin_unlock_irqrestore(&lock, lock_flag);
		g_stSocpDebugInfo.sSocpDebugEncDst.u32socp_read_doneEncDstSucCnt[u32ChanID]++;
	} else {
		pr_info("ReadDataDone: invalid chan type: 0x%x!\n",
				u32ChanType);
		return BSP_ERR_SOCP_INVALID_CHAN;
	}

	return BSP_OK;
}

s32 bsp_socp_set_bbp_enable(int bEnable)
{
	if (bEnable)
		BBP_REG_SETBITS(BBP_REG_CH_EN, 0, 1, 1);
	else
		BBP_REG_SETBITS(BBP_REG_CH_EN, 0, 1, 0);

	return BSP_OK;
}

s32 bsp_socp_set_bbp_ds_mode(SOCP_BBP_DS_MODE_E eDsMode)
{
	if (eDsMode >= SOCP_BBP_DS_MODE_BUTT) {
		pr_info("SetBbpDsMode: invalid DS mode!\n");
		return BSP_ERR_SOCP_INVALID_PARA;
	}

	BBP_REG_SETBITS(BBP_REG_DS_CFG, 31, 1, eDsMode);
	return BSP_OK;
}

s32 bsp_socp_enc_dst_buf_flush(void)
{
	return BSP_OK;
}


/* to do low power begin*/
void BSP_SOCP_DrxRestoreRegAppOnly(void)
{
	u32 i = 0;

	for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++) {
		SOCP_REG_READ(SOCP_REG_ENCDEST_BUFRPTR(i),
					  g_strSocpStat.sEncDstChan[i].sEncDstBuf.u32Read);
		SOCP_REG_READ(SOCP_REG_ENCDEST_BUFWPTR(i),
					  g_strSocpStat.sEncDstChan[i].sEncDstBuf.u32Write);
	}

	for (i = 0; i < SOCP_MAX_DECDST_CHN; i++) {
		SOCP_REG_READ(SOCP_REG_DECDEST_BUFRPTR(i),
					  g_strSocpStat.sDecDstChan[i].sDecDstBuf.u32Read);
		SOCP_REG_READ(SOCP_REG_DECDEST_BUFWPTR(i),
					  g_strSocpStat.sDecDstChan[i].sDecDstBuf.u32Write);
	}

	for (i = 0; i < SOCP_MAX_ENCSRC_CHN; i++) {
		SOCP_REG_READ(SOCP_REG_ENCSRC_BUFRPTR(i),
					  g_strSocpStat.sEncSrcChan[i].sEncSrcBuf.u32Read);
		SOCP_REG_READ(SOCP_REG_ENCSRC_BUFWPTR(i),
					  g_strSocpStat.sEncSrcChan[i].sEncSrcBuf.u32Write);

		SOCP_REG_READ(SOCP_REG_ENCSRC_RDQRPTR(i),
					  g_strSocpStat.sEncSrcChan[i].sRdBuf.u32Read);
		SOCP_REG_READ(SOCP_REG_ENCSRC_RDQWPTR(i),
					  g_strSocpStat.sEncSrcChan[i].sRdBuf.u32Write);
	}

	for (i = 0; i < SOCP_MAX_DECSRC_CHN; i++) {
		SOCP_REG_READ(SOCP_REG_DECSRC_BUFRPTR(i),
					  g_strSocpStat.sDecSrcChan[i].sDecSrcBuf.u32Read);
		SOCP_REG_READ(SOCP_REG_DECSRC_BUFWPTR(i),
					  g_strSocpStat.sDecSrcChan[i].sDecSrcBuf.u32Write);
	}
}

u32 BSP_SOCP_CanSleep(void)
{
	u32 i;
	u32 u32EncBusy, u32DecBusy;
	u32 u32BufAddr, u32WritePtr, u32ReadPtr;
	u32 u32IntFlag;

	for (i = 0; i < SOCP_MAX_ENCSRC_CHN; i++) {
		if ((i >= SOCP_CCORE_ENCSRC_CHN_BASE)
			&& (i <= (SOCP_CCORE_ENCSRC_CHN_BASE + SOCP_CCORE_ENCSRC_CHN_NUM)))
			continue;
		SOCP_REG_READ(SOCP_REG_ENCSRC_BUFADDR(i), u32BufAddr);
		if (0 != u32BufAddr) {
			SOCP_REG_READ(SOCP_REG_ENCSRC_BUFWPTR(i), u32WritePtr);
			SOCP_REG_READ(SOCP_REG_ENCSRC_BUFRPTR(i), u32ReadPtr);
			if (u32WritePtr != u32ReadPtr)
				return 1;
		}
	}

	for (i = 0; i < SOCP_MAX_ENCDST_CHN; i++) {
		SOCP_REG_READ(SOCP_REG_ENCDEST_BUFADDR(i), u32BufAddr);
		if (0 != u32BufAddr) {
			SOCP_REG_READ(SOCP_REG_ENCDEST_BUFWPTR(i), u32WritePtr);
			SOCP_REG_READ(SOCP_REG_ENCDEST_BUFRPTR(i), u32ReadPtr);
			if (u32WritePtr != u32ReadPtr)
				return 3;
		}
	}
	for (i = 0; i < SOCP_MAX_DECSRC_CHN; i++) {
		SOCP_REG_READ(SOCP_REG_DECSRC_BUFADDR(i), u32BufAddr);
		if (0 != u32BufAddr) {
			SOCP_REG_READ(SOCP_REG_DECSRC_BUFWPTR(i), u32WritePtr);
			SOCP_REG_READ(SOCP_REG_DECSRC_BUFRPTR(i), u32ReadPtr);
			if (u32WritePtr != u32ReadPtr)
				return 4;
		}
	}

	for (i = 0; i < SOCP_MAX_DECDST_CHN; i++) {
		SOCP_REG_READ(SOCP_REG_DECDEST_BUFADDR(i), u32BufAddr);
		if (0 != u32BufAddr) {
			SOCP_REG_READ(SOCP_REG_DECDEST_BUFWPTR(i), u32WritePtr);
			SOCP_REG_READ(SOCP_REG_DECDEST_BUFRPTR(i), u32ReadPtr);
			if (u32WritePtr != u32ReadPtr)
				return 5;
		}
	}

	SOCP_REG_READ(SOCP_REG_ENCSTAT, u32EncBusy);
	SOCP_REG_READ(SOCP_REG_DECSTAT, u32DecBusy);

	if ((0 != u32EncBusy) || (0 != u32DecBusy))
		return 6;

	SOCP_REG_READ(SOCP_REG_GBL_INTSTAT, u32IntFlag);
	if ((0 != u32IntFlag))
		return 7;

	return BSP_OK;
}

/* to do low power end*/

SOCP_STATE_ENUM_UINT32 bsp_socp_get_state(void)
{
	u32 reg_enc;
	u32 reg_dec;
	SOCP_REG_READ(SOCP_STATE_SC_ENC_OFFSET, reg_enc);
	SOCP_REG_READ(SOCP_STATE_SC_DEC_OFFSET, reg_dec);

	if (reg_enc == 0 && reg_dec == 0)
		return SOCP_IDLE;
	else
		return SOCP_BUSY;
}

static int hs_socp_remove(struct platform_device *pdev)
{
	pr_emerg("socp_exit!\n");
	return 0;
}

#ifdef CONFIG_OF
static const struct of_device_id hs_socp_of_match[] = {
	{.compatible = "hisilicon,socp",},
	{},
};

MODULE_DEVICE_TABLE(of, hs_socp_of_match);
#endif

#ifdef CONFIG_PM
static int hs_socp_suspend(struct device *dev)
{
#if 0
	struct platform_device *pdev = to_platform_device(dev);
	struct socp_dev *i_dev = platform_get_drvdata(pdev);

#endif
	pr_info("%s\n", __func__);
	return 0;
}

static int hs_socp_resume(struct device *dev)
{
#if 0
	struct platform_device *pdev = to_platform_device(dev);
	struct socp_dev *i_dev = platform_get_drvdata(pdev);

#endif
	pr_info("%s\n", __func__);
	return 0;
}
#endif

static SIMPLE_DEV_PM_OPS(hs_socp_dev_pm_ops, hs_socp_suspend, hs_socp_resume);

static struct platform_driver hs_socp_driver = {
	.probe = hs_socp_probe,
	.remove = hs_socp_remove,
	.driver = {
		.name = "socp",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(hs_socp_of_match),
		.pm = &hs_socp_dev_pm_ops,
	},
};

module_platform_driver(hs_socp_driver);

MODULE_DESCRIPTION("HS socp adapter");
MODULE_ALIAS("platform:socp");
MODULE_LICENSE("GPL");

