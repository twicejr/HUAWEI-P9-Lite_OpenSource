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



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include <product_config.h>
#include <mdrv.h>
#include <diag_mem.h>
#include "diag_msgbbp.h"
#include "msp_diag_comm.h"

#if(VOS_OS_VER == VOS_LINUX)
#include "diag_acore_common.h"
#endif

#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_MSGBBP_C


#if(VOS_OS_VER == VOS_LINUX)
DIAG_TRANS_HEADER_STRU g_stBbpTransHead = {{VOS_NULL, VOS_NULL}, 0};
DIAG_BBP_DS_ADDR_INFO_STRU g_stBbpDsAddrInfo={DIAG_BBP_DS_ENABLE,DDR_SOCP_SIZE,DDR_SOCP_ADDR};
#endif


DIAG_BBP_PROC_FUN_STRU g_DiagBbpFunc[] = {
    {diag_DrxSampleGetChnSizeProc        ,DIAG_CMD_DRX_SAMPLE_CHNSIZE_REQ       ,0},
#if ((VOS_OS_VER == VOS_VXWORKS)||(VOS_OS_VER == VOS_RTOSCK))
    {diag_DrxSampleGenProc               ,DIAG_CMD_DRX_SAMPLE_GEN_REQ           ,0},
    {diag_DrxSampleGetAddrProc           ,DIAG_CMD_DRX_SAMPLE_ADDR_REQ          ,0},
    {diag_DrxSampleGetVersionProc        ,DIAG_CMD_DRX_SAMPLE_GET_VERSION_REQ   ,0},
    {diag_DrxSampleAbleChnProc           ,DIAG_CMD_DRX_SAMPLE_ABLE_CHN_REQ      ,0},
#endif
};

#if ((VOS_OS_VER == VOS_VXWORKS)||(VOS_OS_VER == VOS_RTOSCK))

DIAG_DRX_SAMPLE_CHNSIZE_S g_DiagBbpChanSize[] = {
    {DRX_SAMPLE_BBP_DMA_LOG0_CHNSIZE,SOCP_CODER_SRC_BBP_LOG,0,BBP_LOG0_MEM_SIZE},
    {DRX_SAMPLE_BBP_DMA_LOG1_CHNSIZE,SOCP_CODER_SRC_BBP_BUS,0,BBP_LOG1_MEM_SIZE},
#ifdef CONFIG_HI3650_TLBBP_DS
    {DRX_SAMPLE_BBP_DMA_LOG2_CHNSIZE,SOCP_CODER_SRC_LBBP3,0,BBP_LOG2_MEM_SIZE},
    {DRX_SAMPLE_BBP_DMA_LOG3_CHNSIZE,SOCP_CODER_SRC_LBBP4,0,BBP_LOG3_MEM_SIZE},
    {DRX_SAMPLE_BBP_DMA_LOG4_CHNSIZE,SOCP_CODER_SRC_LBBP5,0,BBP_LOG4_MEM_SIZE},
    {DRX_SAMPLE_BBP_DMA_LOG5_CHNSIZE,SOCP_CODER_SRC_LBBP6,0,BBP_LOG5_MEM_SIZE},
    {DRX_SAMPLE_BBP_DMA_LOG6_CHNSIZE,SOCP_CODER_SRC_LBBP7,0,BBP_LOG6_MEM_SIZE},
    {DRX_SAMPLE_BBP_DMA_LOG7_CHNSIZE,SOCP_CODER_SRC_LBBP8,0,BBP_LOG7_MEM_SIZE},
#endif
    {DRX_SAMPLE_BBP_DMA_DATA_CHNSIZE,SOCP_CODER_SRC_BBP_DS,0,0},
};
VOS_UINT32 diag_DrxSampleGenProc(DIAG_FRAME_INFO_STRU *pData)
{
    DIAG_CMD_DRX_SAMPLE_REG_WR_REQ_STRU *psDrxSample = NULL;
	DIAG_CMD_DRX_SAMPLE_REG_WR_CNF_STRU stCnfDrxSample = {0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
	VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    VOS_UINT32 ulDataLen = 0;

	psDrxSample = (DIAG_CMD_DRX_SAMPLE_REG_WR_REQ_STRU*)((VOS_UINT8*)(pData->aucData)+sizeof(MSP_DIAG_DATA_REQ_STRU));

    ulDataLen = pData->ulMsgLen - sizeof(MSP_DIAG_DATA_REQ_STRU);

    stCnfDrxSample.ulRet = BSP_MailBox_ComMsgWrite(EN_MAILBOX_SERVICE_LTE_HS_DIAG, psDrxSample, ulDataLen, EN_MAILBOX_SLEEP_WAKEUP);
	if(stCnfDrxSample.ulRet != VOS_OK)
	{
        diag_printf("%s BSP_MailBox_ComMsgWrite failed  0x%x!\n",__FUNCTION__,ulRet);
		stCnfDrxSample.ulRet = ERR_MSP_FAILURE;
	}

    DIAG_MSG_COMMON_PROC(stDiagInfo,stCnfDrxSample,pData);
    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_BBP;

    ulRet = DIAG_MsgReport(&stDiagInfo,&stCnfDrxSample, sizeof(DIAG_CMD_DRX_SAMPLE_REG_WR_CNF_STRU));

    return ulRet;

}
/*****************************************************************************
 Function Name   : diag_DrxSampleGetAddrProc
 Description     : 低功耗数采获取基地址
 Input           :VOS_UINT8* pstReq
                VOS_UINT32 ulCmdSn
 Output          : None
 Return          : VOS_UINT32

 History         :

*****************************************************************************/
VOS_UINT32 diag_DrxSampleGetAddrProc(DIAG_FRAME_INFO_STRU *pData)
{
    DIAG_CMD_DRX_SAMPLE_GET_ADDR_REQ_STRU *psDrxSample = NULL;
	DIAG_CMD_DRX_SAMPLE_GET_ADDR_CNF_STRU stCnfDrxSample = {0};
	VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
	VOS_UINT32 ulAddrType 	= 0;

	psDrxSample = (DIAG_CMD_DRX_SAMPLE_GET_ADDR_REQ_STRU*)((VOS_UINT8*)(pData->aucData)+sizeof(MSP_DIAG_DATA_REQ_STRU));


	DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_BBP_SAMPLE,psDrxSample->eDiagDrxSampleAddr,0,0);

	ulAddrType = psDrxSample->eDiagDrxSampleAddr;

    stCnfDrxSample.ulDrxSampleType = ulAddrType;
	/* 获取对应的寄存器地址*/
	switch (ulAddrType)
	{
		case DRX_SAMPLE_BBP_DMA_BASE_ADDR:
			stCnfDrxSample.ulDrxSampleAddr = (VOS_UINT32)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_BBPDMA);
			/* add code here */
			break;
		case DRX_SAMPLE_BBP_DBG_BASE_ADDR:
			stCnfDrxSample.ulDrxSampleAddr = (VOS_UINT32)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_BBPDBG);
			/* add code here */
			break;
		case DRX_SAMPLE_BBP_SRC_BASE_ADDR:
			stCnfDrxSample.ulDrxSampleAddr = (VOS_UINT32)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_BBPSRC);
			/* add code here */
			break;
		case DRX_SAMPLE_POW_ONOFF_CLK_BASE_ADDR:
			stCnfDrxSample.ulDrxSampleAddr = (VOS_UINT32)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_SYSCTRL);
			/* add code here */
			break;
		case DRX_SAMPLE_SOCP_BASE_ADDR:
			stCnfDrxSample.ulDrxSampleAddr = (VOS_UINT32)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_SOCP);
			/* add code here */
			break;
		default:
			break;
	}

    stCnfDrxSample.ulRet = VOS_OK;

    DIAG_MSG_COMMON_PROC(stDiagInfo,stCnfDrxSample,pData);
    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_BBP;

    ulRet = DIAG_MsgReport(&stDiagInfo,&stCnfDrxSample, sizeof(DIAG_CMD_DRX_SAMPLE_GET_ADDR_CNF_STRU));

    return ulRet;
}


/*****************************************************************************
 Function Name   : diag_DrxSampleCfgChnAddrProc
 Description     : 低功耗数采配置通道地址
 Input           :VOS_UINT8* pstReq
                VOS_UINT32 ulCmdSn
 Output          : None
 Return          : VOS_UINT32

 History         :

*****************************************************************************/
VOS_UINT32 diag_DrxSampleGetVersionProc(DIAG_FRAME_INFO_STRU *pData)
{
	DIAG_CMD_DRX_SAMPLE_GET_VERSION_CNF_STRU stCnfDrxSample;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
	VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
	VOS_INT32 value = ERR_MSP_SUCCESS;
    /* coverity[assign_zero] */
	va_list arglist = {0};

	/* config regs */
    /*lint -save -e539*/
    /* coverity[uninit_use_in_call] */
    value = VOS_nvsprintf((VOS_CHAR*)(stCnfDrxSample.ulProductName), DIAG_PRODUCT_VERSION_LENGTH, (VOS_CHAR *)PRODUCT_NAME, arglist);
    if(value < 0){}
    /* coverity[var_deref_model] */
	value = VOS_nvsprintf((VOS_CHAR*)(stCnfDrxSample.ulSolutiongName), DIAG_PRODUCT_VERSION_LENGTH, (VOS_CHAR *)PRODUCT_CFG_CHIP_SOLUTION_NAME, arglist);
    if(value < 0){}
    /*lint -restore*/
	/*打包回复给FW*/
    ulRet = ERR_MSP_SUCCESS;
	stCnfDrxSample.ulRet = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo,stCnfDrxSample,pData);
    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_BBP;

    ulRet = DIAG_MsgReport(&stDiagInfo,&stCnfDrxSample, sizeof(DIAG_CMD_DRX_SAMPLE_GET_VERSION_CNF_STRU));

    return ulRet;

}

/*****************************************************************************
 Function Name   : diag_DrxSampleAbleChnProc
 Description     : 数采处理
 Input           :VOS_UINT8* pstReq
                VOS_UINT32 ulCmdSn
 Output          : None
 Return          : VOS_UINT32

 History         :

*****************************************************************************/
VOS_UINT32 diag_DrxSampleAbleChnProc(DIAG_FRAME_INFO_STRU *pData)
{
	DIAG_CMD_DRX_SAMPLE_ABLE_CHN_REQ_STRU *psDrxSample = NULL;
	DIAG_CMD_DRX_SAMPLE_ABLE_CHN_CNF_STRU stCnfDrxSample = {0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
	VOS_UINT32 ulRet = ERR_MSP_SUCCESS;

	VOS_UINT32 ulChnAbleType = 0;

	psDrxSample = (DIAG_CMD_DRX_SAMPLE_ABLE_CHN_REQ_STRU*)((VOS_UINT8*)(pData->aucData)+sizeof(MSP_DIAG_DATA_REQ_STRU));

	/* 调用socp 通道使能函数打开通道或者关闭通道*/
	ulChnAbleType = psDrxSample->eDiagDrxSampleAbleChn;
	switch (ulChnAbleType)
	{
		case DRX_SAMPLE_SOCP_CHN_ENABLE:
			{
				if(VOS_OK != mdrv_socp_start(SOCP_CODER_SRC_BBP_DS))
				{
					diag_printf("%s: enable channel failed!\n",__FUNCTION__);
				}
			break;
			}
		case DRX_SAMPLE_SOCP_CHN_DISABLE:
			{
				if(VOS_OK != mdrv_socp_stop(SOCP_CODER_SRC_BBP_DS))
				{
					diag_printf("%s: disable channel failed!\n",__FUNCTION__);
				}
			break;
			}
		default:
			break;
	}

	stCnfDrxSample.ulRet = ulRet;

    DIAG_MSG_COMMON_PROC(stDiagInfo,stCnfDrxSample,pData);
    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_BBP;

    ulRet = DIAG_MsgReport(&stDiagInfo,&stCnfDrxSample, sizeof(DIAG_CMD_DRX_SAMPLE_ABLE_CHN_CNF_STRU));

    return ulRet;
}

/*****************************************************************************
 Function Name   : diag_AppTransBbpProc
 Description     : A核发过来的BBP诊断命令处理
 Input           : pMsgBlock    诊断命令请求的内容
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c64416      2014-11-18  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_AppTransBbpProc(MsgBlock* pMsgBlock)
{
    DIAG_BBP_MSG_A_TRANS_C_STRU *pstInfo;

    pstInfo = (DIAG_BBP_MSG_A_TRANS_C_STRU *)pMsgBlock;

    return diag_BbpMsgProc(&pstInfo->stInfo);
}

VOS_VOID diag_BbpInitSocpChan(VOS_VOID)
{
    int i = 0;
    int num = 0;

    num = (int)(sizeof(g_DiagBbpChanSize)/sizeof(g_DiagBbpChanSize[0]));

    for(i=0;i< num;i++)
    {
        /*数采通道需要单独初始化*/
        if(g_DiagBbpChanSize[i].ulChan != SOCP_CODER_SRC_BBP_DS)
        {
            (VOS_VOID)DRV_SOCP_INIT_LTE_BBP_LOG(g_DiagBbpChanSize[i].ulChan,\
                g_DiagBbpChanSize[i].ulAddr,g_DiagBbpChanSize[i].ulSize);
        }
    }
}

VOS_BOOL ulChanEnableStat = FALSE;
VOS_VOID diag_BbpEnableSocpChan(VOS_VOID)
{
    int i = 0;
    int num = 0;
    /*lint -save -e539*/
    if(TRUE == ulChanEnableStat)
    {
        return ;
    }

    num = (int)(sizeof(g_DiagBbpChanSize)/sizeof(g_DiagBbpChanSize[0]));

    for(i = 0;i <num;i++)
    {
        /*数采通道使能需要由dsp模块完成*/
        if(g_DiagBbpChanSize[i].ulChan != SOCP_CODER_SRC_BBP_DS)
        {
            DRV_SOCP_ENABLE_LTE_BBP_DSP(g_DiagBbpChanSize[i].ulChan);
        }
    }

    /*lint -restore*/
    ulChanEnableStat = TRUE;
}

VOS_VOID diag_BbpShowDebugInfo(VOS_VOID)
{
    VOS_UINT32 i = 0;

    for(i=0;i<sizeof(g_DiagBbpFunc)/sizeof(DIAG_BBP_PROC_FUN_STRU);i++)
    {
        diag_printf("Command ID :0x%x ,Ops Num %d\n",g_DiagBbpFunc[i].ulCmdId,g_DiagBbpFunc[i].ulReserve);
    }
}
#endif



/*****************************************************************************
 Function Name	 : diag_DrxSampleGetChnSizeProc
 Description	 : 低功耗数采获取通道大小
 Input			 :VOS_UINT8* pstReq
				VOS_UINT32 ulCmdSn
 Output 		 : None
 Return 		 : VOS_UINT32

 History		 :

*****************************************************************************/
VOS_UINT32 diag_DrxSampleGetChnSizeProc(DIAG_FRAME_INFO_STRU *pData)
{
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_BBP_DS_ADDR_INFO_STRU  *psDrxDsInfo = NULL;
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    DIAG_CMD_DRX_SAMPLE_GET_CHNSIZE_CNF_STRU stCnfDrxSample = {0};

#if (VOS_OS_VER == VOS_LINUX)
    VOS_UINT32 ulLen;
    DIAG_BBP_MSG_A_TRANS_C_STRU *pstInfo;

    /*AP在发送给CP命令时，需要把数采地址空间信息一起发送过去*/
    ulLen = sizeof(DIAG_BBP_MSG_A_TRANS_C_STRU)-VOS_MSG_HEAD_LENGTH + pData->ulMsgLen+sizeof(DIAG_BBP_DS_ADDR_INFO_STRU);
    
    pstInfo = (DIAG_BBP_MSG_A_TRANS_C_STRU*)VOS_AllocMsg(MSP_PID_DIAG_APP_AGENT, ulLen);
    if(VOS_NULL == pstInfo)
    {
        ulRet = ERR_MSP_MALLOC_FAILUE;
        goto DIAG_ERROR;
    }
    pstInfo->ulReceiverPid  = MSP_PID_DIAG_AGENT;
    pstInfo->ulSenderPid    = MSP_PID_DIAG_APP_AGENT;
    pstInfo->ulMsgId        = DIAG_MSG_BBP_A_TRANS_C_REQ;
    
    ulLen = sizeof(DIAG_FRAME_INFO_STRU)+pData->ulMsgLen;
    (VOS_VOID)VOS_MemCpy(&pstInfo->stInfo, pData, ulLen);
    
    psDrxDsInfo = (DIAG_BBP_DS_ADDR_INFO_STRU*)((VOS_UINT8*)pstInfo+sizeof(DIAG_BBP_MSG_A_TRANS_C_STRU)+pData->ulMsgLen);
    psDrxDsInfo->ulAddr     = g_stBbpDsAddrInfo.ulAddr;
    psDrxDsInfo->ulSize     = g_stBbpDsAddrInfo.ulSize;
    psDrxDsInfo->ulenable   = g_stBbpDsAddrInfo.ulenable;

    ulRet = VOS_SendMsg(MSP_PID_DIAG_APP_AGENT, pstInfo);
    if(ulRet)
    {
        goto DIAG_ERROR;
    }

    return ulRet;
DIAG_ERROR:
#endif

#if ((VOS_OS_VER == VOS_VXWORKS)||(VOS_OS_VER == VOS_RTOSCK))
    DIAG_CMD_DRX_SAMPLE_GET_CHNSIZE_REQ_STRU *psDrxSample = NULL;
    VOS_UINT32 ulAddrType = 0;
    int num = 0;
    int i = 0;

	psDrxSample = (DIAG_CMD_DRX_SAMPLE_GET_CHNSIZE_REQ_STRU*)((VOS_UINT8*)(pData->aucData)+sizeof(MSP_DIAG_DATA_REQ_STRU));
    psDrxDsInfo = (DIAG_BBP_DS_ADDR_INFO_STRU*)((VOS_UINT8*)pData+sizeof(DIAG_FRAME_INFO_STRU)+pData->ulMsgLen);

	DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_BBP_SAMPLE,psDrxSample->eDiagDrxSampleChnSize,0,0);

	ulAddrType  = psDrxSample->eDiagDrxSampleChnSize;
    num = (int)(sizeof(g_DiagBbpChanSize)/sizeof(g_DiagBbpChanSize[0]));
    (VOS_VOID)VOS_MemSet(&stCnfDrxSample,0,sizeof(stCnfDrxSample));

    for(i = 0; i < num; i++)
    {
        if(ulAddrType == g_DiagBbpChanSize[i].ulChanEnum)
        {
            if(g_DiagBbpChanSize[i].ulChan != SOCP_CODER_SRC_BBP_DS)
            {
                stCnfDrxSample.ulChnAddr = g_DiagBbpChanSize[i].ulAddr;
                stCnfDrxSample.ulChnSize = g_DiagBbpChanSize[i].ulSize;
            }
            else
            {
                if((DIAG_BBP_DS_ENABLE == psDrxDsInfo->ulenable)&&(!g_DiagBbpChanSize[i].ulAddr))
                {
                    g_DiagBbpChanSize[i].ulAddr = (VOS_UINT32)psDrxDsInfo->ulAddr;
                    g_DiagBbpChanSize[i].ulSize = psDrxDsInfo->ulSize;
                    (VOS_VOID)DRV_SOCP_INIT_LTE_BBP_DS(g_DiagBbpChanSize[i].ulChan,\
                        g_DiagBbpChanSize[i].ulAddr,g_DiagBbpChanSize[i].ulSize);
                }
                
                stCnfDrxSample.ulChnAddr = g_DiagBbpChanSize[i].ulAddr;
                stCnfDrxSample.ulChnSize = g_DiagBbpChanSize[i].ulSize;
                
                diag_printf("BBP chan base addr :0x%x, base size: 0x%x; SOCP base addr :0x%x, base size: 0x%x.\n", 
                    g_DiagBbpChanSize[i].ulAddr, g_DiagBbpChanSize[i].ulSize, DDR_SOCP_ADDR, DDR_SOCP_SIZE);
            }
        }
    }
    stCnfDrxSample.ulChnType = ulAddrType;
#endif
	stCnfDrxSample.ulRet = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo,stCnfDrxSample,pData);
    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_BBP;

    ulRet = DIAG_MsgReport(&stDiagInfo,&stCnfDrxSample, sizeof(DIAG_CMD_DRX_SAMPLE_GET_CHNSIZE_CNF_STRU));

    return ulRet;
}


/*****************************************************************************
 Function Name   : diag_BbpMsgProc
 Description     : MSP bbp部分消息处理函数
 Input           : None
 Output          : None
 Return          : None
 History         :

*****************************************************************************/
VOS_UINT32 diag_BbpMsgProc(DIAG_FRAME_INFO_STRU *pData)
{
    VOS_UINT32 ulRet = ERR_MSP_INVALID_PARAMETER ;
    DIAG_CMD_DRX_SAMPLE_COMM_CNF_STRU stCnfDrxSample;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    VOS_UINT32 i = 0;
#if (VOS_OS_VER == VOS_LINUX)
    VOS_UINT32 ulLen;
    DIAG_BBP_MSG_A_TRANS_C_STRU *pstInfo;
#endif
    if(DIAG_MSG_TYPE_BBP != pData->stID.pri4b)
    {
        diag_printf("%s Rcv Error Msg Id 0x%x\n",__FUNCTION__,pData->ulCmdId);
        return ulRet;
    }

    for(i = 0; i< sizeof(g_DiagBbpFunc)/sizeof(g_DiagBbpFunc[0]);i++)
    {
        if(g_DiagBbpFunc[i].ulCmdId == pData->ulCmdId)
        {
            g_DiagBbpFunc[i].ulReserve ++;
            ulRet = g_DiagBbpFunc[i].pFunc(pData);
            return ulRet;
        }
    }

#if (VOS_OS_VER == VOS_LINUX)

    /* GU的BBP命令采用透传处理机制 */
    if((DIAG_MODE_GSM == pData->stID.mode4b) || (DIAG_MODE_UMTS == pData->stID.mode4b))
    {
        return diag_TransReqProcEntry(pData, &g_stBbpTransHead);
    }

    /*AP在发送给CP命令时，需要把数采地址空间信息一起发送过去*/
    ulLen = sizeof(DIAG_BBP_MSG_A_TRANS_C_STRU)-VOS_MSG_HEAD_LENGTH + pData->ulMsgLen;
    pstInfo = (DIAG_BBP_MSG_A_TRANS_C_STRU*)VOS_AllocMsg(MSP_PID_DIAG_APP_AGENT, ulLen);
    if(VOS_NULL == pstInfo)
    {
        ulRet = ERR_MSP_MALLOC_FAILUE;
        goto DIAG_ERROR;
    }
    pstInfo->ulReceiverPid = MSP_PID_DIAG_AGENT;
    pstInfo->ulSenderPid   = MSP_PID_DIAG_APP_AGENT;
    pstInfo->ulMsgId       = DIAG_MSG_BBP_A_TRANS_C_REQ;
    ulLen = sizeof(DIAG_FRAME_INFO_STRU)+pData->ulMsgLen;
    (VOS_VOID)VOS_MemCpy(&pstInfo->stInfo, pData, ulLen);

    ulRet = VOS_SendMsg(MSP_PID_DIAG_APP_AGENT, pstInfo);
    if(ulRet)
    {
        goto DIAG_ERROR;
    }

    return ulRet;

DIAG_ERROR:
#endif

    stCnfDrxSample.ulRet = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo,stCnfDrxSample,pData);
    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_BBP;

    ulRet = DIAG_MsgReport(&stDiagInfo,&stCnfDrxSample, sizeof(DIAG_CMD_DRX_SAMPLE_ABLE_CHN_CNF_STRU));

    return ulRet;
}

/*****************************************************************************
 Function Name   : diag_BbpMsgInit
 Description     : MSP bbp部分初始化
 Input           : None
 Output          : None
 Return          : None
 History         :

*****************************************************************************/
VOS_VOID diag_BbpMsgInit(VOS_VOID)
{
#if ((VOS_OS_VER == VOS_VXWORKS)||(VOS_OS_VER == VOS_RTOSCK))
    int i = 0;
    int num=0;
    VOS_UINT_PTR ulRealPtr = 0;
    VOS_VOID* ulVirtAddr = VOS_NULL;

    num = (int)sizeof(g_DiagBbpChanSize)/sizeof(g_DiagBbpChanSize[0]);

    for(i=0;i<num;i++)
    {
        if((!g_DiagBbpChanSize[i].ulAddr) && (g_DiagBbpChanSize[i].ulSize) && (g_DiagBbpChanSize[i].ulChan != SOCP_CODER_SRC_BBP_DS))
        {
            ulVirtAddr= VOS_UnCacheMemAlloc(g_DiagBbpChanSize[i].ulSize,&ulRealPtr);
            if(VOS_NULL != ulVirtAddr)
            {
                g_DiagBbpChanSize[i].ulAddr = ulRealPtr;
                ulVirtAddr = VOS_NULL;
                ulRealPtr  = 0;
            }
        }
    }

    diag_BbpInitSocpChan();
#else

    VOS_UINT32 ulRet;

    /* 创建节点保护信号量, Diag Trans Bbp */
    ulRet = VOS_SmBCreate("DTB", 1, VOS_SEMA4_FIFO,&g_stBbpTransHead.TransSem);
    if(VOS_OK != ulRet)
    {
        diag_printf("diag_BbpMsgInit VOS_SmBCreate failed.\n");
    }

    /* 初始化请求链表 */
    blist_head_init(&g_stBbpTransHead.TransHead);

    /*注册message消息回调*/
    DIAG_MsgProcReg(DIAG_MSG_TYPE_BBP,diag_BbpMsgProc);
#endif
    return;
}
#if(VOS_OS_VER == VOS_LINUX)
/*lint -save -e102 -e10 -e2 -e40 -e533 -e31 -e830 -e522 -e718 -e746 -e702 -e565   -e64 -e23 -e63 -e26 -e578 -e132*/
extern unsigned long simple_strtoul(const char *cp, char **endp, unsigned int base);
/*****************************************************************************
* 函 数 名  : socp_logbuffer_sizeparse
*
* 功能描述  : 在代码编译阶段将CMD LINE中的BUFFER大小参数解析出来
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/
static int __init diag_BbpDrxDdrEnable(char *pucChar)
{
    u32      flag;

    flag = (u32)simple_strtoul(pucChar, NULL, 0);
    if(flag)
    {
        g_stBbpDsAddrInfo.ulenable  = DIAG_BBP_DS_ENABLE;
        g_stBbpDsAddrInfo.ulAddr    = DDR_SOCP_ADDR;
        g_stBbpDsAddrInfo.ulSize    = DDR_SOCP_SIZE;
        printk(KERN_ERR"[%s] enable!\n",__FUNCTION__);
        printk(KERN_ERR"base addr :0x%x,base size: 0x%x\n",DDR_SOCP_ADDR,DDR_SOCP_SIZE);
    }
    else
    {
        g_stBbpDsAddrInfo.ulenable  = 0;
        g_stBbpDsAddrInfo.ulAddr    = 0;
        g_stBbpDsAddrInfo.ulSize    = 0;
        printk(KERN_ERR"[%s] not enable!\n",__FUNCTION__);
    }
    return 0;
}

early_param("modem_socp_enable",diag_BbpDrxDdrEnable);
/*lint -restore*/
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


