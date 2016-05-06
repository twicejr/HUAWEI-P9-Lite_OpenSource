/******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : PsRegRpt.c
  Author       : g47350
  Version      : V300R001
  Date         : 2010-8-24
  Description  :
  Function List:
        ---
        ---
        ---
  History      :
  1. Date:2010-8-24
     Author: g47350
     Modification:Create

******************************************************************************/

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/******************************************************************************
   1 头文件包含
******************************************************************************/

#include "stddef.h"
#include "pamom.h"
#include "apminterface.h"
#include "hpaglobalvar.h"
#include "omprivate.h"
#include "sleepflow.h"
#include "PsCommonDef.h"
#include "TtfOamInterface.h"
#include "psregrpt.h"
#include "apmprocess.h"
#include "soc_interface.h"
#include "msp_diag_comm.h"
#if (FEATURE_GUC_BBP_TRIG == FEATURE_ON)
#include "bbp_dbg_trig_interface.h"
#include "bbp_sctrl_interface.h"
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/

/*lint -e767 修改人：甘兰47350；检视人：徐铖51137；原因简述：寄存器上报功能*/
#define    THIS_FILE_ID        PS_FILE_ID_PS_REG_RPT_C
/*lint +e767 修改人：甘兰47350；检视人：徐铖51137；原因简述：寄存器上报功能*/




/******************************************************************************
   2 外部函数和变量声明
******************************************************************************/

/******************************************************************************
   3 私有定义
******************************************************************************/

/******************************************************************************
   4 全局变量定义
******************************************************************************/
#if (FEATURE_GUC_BBP_TRIG == FEATURE_OFF)

PS_REG_RPT_CFG_STRU     g_astPsRegRptCfg[PS_REG_SYS_MODE_BUTT];

PS_REG_RPT_CFG_STRU     g_astPsRegRptTemp[PS_REG_SYS_MODE_BUTT];

PS_REG_REQ_ADDR_STRU    g_astPsRegReqAddr[PS_REG_SYS_MODE_BUTT];

PS_REG_RPT_VALUE_STRU   g_astPsRegRptBuf[PS_REG_RPT_RBUF_NUM];

PS_REG_RPT_IND_MSG      g_stPsRegRptINDMsg;

extern VOS_VOID SLEEP_DMACapRelease(VOS_VOID);

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
extern VOS_VOID I1_SLEEP_DMACapRelease(VOS_VOID);
#if (3 == MULTI_MODEM_NUMBER)
extern VOS_VOID I2_SLEEP_DMACapRelease(VOS_VOID);
#endif
#endif

VOS_UINT32              g_aulRegCaptureNum[PS_REG_SYS_MODE_BUTT] = {0};

VOS_UINT32              g_aulRegFullNum[PS_REG_SYS_MODE_BUTT] = {0};

VOS_INT32               g_lDMAChanID0;
VOS_INT32               g_lDMAChanID1;
VOS_INT32               g_lDMAChanID2;

VOS_SEM                 g_ulRegTransferSem;

VOS_UINT32              g_ulRptRegInitStatus; /* 抓寄存器使能状态 */
VOS_UINT32              g_ulRptRegDiffNum;    /* 抓寄存器差异上报次数 */

DMAREG_INFO_STRU        g_stDmaInfo = {0};

DMA_REG_TIME_STRU       g_stDmaTimeInfo = {0};

VOS_UINT32             *g_pstDmaDest[PS_REG_RPT_BUF_NUM][PS_REG_RPT_SEND_FREQUENCY];

BALONG_DMA_CB_S        *g_pstDmaNode[PS_REG_RPT_BUF_NUM][PS_REG_RPT_SEND_FREQUENCY][PS_REG_SYS_MODE_BUTT];

VOS_UINT32              g_ulSendMoud        = PS_REG_RPT_SEND_FREQUENCY;
VOS_UINT32              g_ulSendCount       = 1;

VOS_BOOL                g_bIsOmGetSliceFlag = VOS_FALSE;

PS_REG_RPT_CONTROL_STRU g_PsRegRptContrl;


VOS_UINT32              g_ulChan0IsCapture = VOS_FALSE;
VOS_UINT32              g_ulChan1IsCapture = VOS_FALSE;
VOS_UINT32              g_ulChan2IsCapture = VOS_FALSE;

VOS_UINT32              g_ulPsRegErrCount   = 0;
#endif

#if (FEATURE_GUC_BBP_TRIG == FEATURE_ON)

#ifndef REG_BIT_N
#define REG_BIT_N(num)                  (0x01 << (num))
#endif

PS_REG_BBPTRIG_CFG_INFO_STRU    g_stPsRegGUCBBPDbgState;

PS_REG_GUCBBP_TRIG_INFO_STRU    g_stPsRegGUCBBPTrigInfo;

VOS_UINT32                      g_ulPsRegGUCBBPDbgCfg1[PS_GUCBBP_CFG_REG_NUM1];

VOS_UINT32                      g_ulPsRegGUCBBPDbgCfg2[PS_GUCBBP_CFG_REG_NUM2];

VOS_UINT32                      g_ulPsRegGUCBBPDbgClkValue;

VOS_UINT32                      g_ulPsRegGUCBBPDbgSrstValue;

VOS_UINT32                      g_ulPsRegGUCBBPDbgSleepCount = 0;
#endif

/******************************************************************************
   5 函数实现
******************************************************************************/
#if (FEATURE_GUC_BBP_TRIG == FEATURE_OFF)

/*****************************************************************************
 函 数 名  : PsRegDmaInfoShow
 功能描述  : 显示可维可测信息函数
 输入参数  : VOS_VOID

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2014年8月9日
     作    者  : d00212987
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID PsRegDmaInfoShow(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    /*lint -e534*/
    vos_printf("\r\n DmaRegInfoShow:\r\n The Reg Capture Success Time is    %d", g_stDmaInfo.ulDmaSuccTime);
    vos_printf("\r\n The Dma ISR Success Time is        %d", g_stDmaInfo.ulDmaIsrSuccTime);
    vos_printf("\r\n The Dma ISR Time is                %d", g_stDmaInfo.ulDmaIsrTime);
    vos_printf("\r\n The Dma ISR Err Time is            %d", g_stDmaInfo.ulDmaIsrErrTime);
    vos_printf("\r\n The Dma Head Err Time is           %d", g_stDmaInfo.ulDmaHeadErrTime);
    vos_printf("\r\n The Dma Busy Time is               %d", g_stDmaInfo.ulDmaIdleErrTime);
    vos_printf("\r\n The Dma Start Err Time is          %d", g_stDmaInfo.ulDmaStartErrTime);
    vos_printf("\r\n The Dma Task Run Time is           %d", g_stDmaInfo.ulDmaTaskTime);
    vos_printf("\r\n The Last Dma Isr State is          %d", g_stDmaInfo.ulDmaIntState);
    vos_printf("\r\n The Max Data Isr Time is           %d", g_stDmaTimeInfo.ulIsrMaxTime);
    vos_printf("\r\n The Max Data Capture Time is       %d", g_stDmaTimeInfo.ulMaxTime);
    vos_printf("\r\n The Dma Start  Time is             %d", g_stDmaTimeInfo.ulDmaStartTime);
    vos_printf("\r\n The SmV Max  Time is               %d", g_stDmaTimeInfo.ulSmVMaxTime);
    vos_printf("\r\n The SmP Max  Time is               %d", g_stDmaTimeInfo.ulSmPMaxTime);
    vos_printf("\r\n The SmV To SmP Max Time is         %d", g_stDmaTimeInfo.ulSmVPTime);
    vos_printf("\r\n The Memcpy Max Time is             %d", g_stDmaTimeInfo.ulMemcpyMaxTime);
    vos_printf("\r\n The Socp Send Max Time is          %d", g_stDmaTimeInfo.ulSocpMaxTime);

    vos_printf("\r\n The Dma dest Idle Err Time is       %d", g_stDmaInfo.ulDmaDestIdleErrTime);
    vos_printf("\r\n The Dma dest Busy Err Time is       %d", g_stDmaInfo.ulDmaDestBusyErrTime);
    vos_printf("\r\n The Mem Dma Isr Time is            %d", g_stDmaInfo.ulMemDmaIsrTime);
    vos_printf("\r\n The Mem Dma Start Time is          %d", g_stDmaInfo.ulMemDmaStartTime);
    vos_printf("\r\n The Modem Error Time is          %d", g_stDmaInfo.ulModemErrTime);

    vos_printf("\r\n The Modem Call Diag Api Before     %d", g_stDmaInfo.ulDiagTransReportBeforTime);
    vos_printf("\r\n The Modem Call Diag Api After      %d", g_stDmaInfo.ulDiagTransReportAfterTime);

    vos_printf("\r\ng_PsRegRptContrl.bRptEnableStatus:%d", g_PsRegRptContrl.bRptEnableStatus);
    vos_printf("\r\ng_PsRegRptContrl.aulSendCount[0]WCDMA:%d", g_PsRegRptContrl.aulSendCount[0]);
    vos_printf("\r\ng_PsRegRptContrl.aulSendCount[1]GSM:%d", g_PsRegRptContrl.aulSendCount[1]);
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
    vos_printf("\r\ng_PsRegRptContrl.aulSendCount[2]GSM1:%d", g_PsRegRptContrl.aulSendCount[2]);

#if (3 == MULTI_MODEM_NUMBER)
    vos_printf("\r\ng_PsRegRptContrl.aulSendCount[3]GSM2:%d", g_PsRegRptContrl.aulSendCount[3]);
#endif

#endif
    vos_printf("\r\ng_PsRegRptContrl.ulSendBufIndex[2]:%d", g_PsRegRptContrl.ulSendBufIndex);

    for (i=0;i<PS_REG_RPT_BUF_NUM;i++)
    {
         for (j=0;j<PS_REG_RPT_SEND_FREQUENCY;j++)
         {

            vos_printf("\r\n g_PsRegRptContrl.aulDmaDestWriteStatus is:%d sysmode is:%d",
                        g_PsRegRptContrl.aulDmaDestWriteStatus[i][j],
                        g_PsRegRptContrl.aulDmaDestWriteSysMode[i][j]);
         }
    }

    vos_printf("\r\ng_PsRegRptContrl.aulDmaDestWriteIndex:%d", g_PsRegRptContrl.ulDmaDestWriteIndex);

    for (i=0; i<PS_REG_SYS_MODE_BUTT; i++)
    {
        vos_printf("\r\n g_astPsRegReqAddr[%d].ulCnt = %d", i, g_astPsRegReqAddr[i].ulCnt);
    }
    /*lint +e534*/

    return ;
}

/*****************************************************************************
 函 数 名  : PsRegGetSlice
 功能描述  : 统计时间功能
 输入参数  : NA

 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2014年8月9日
     作    者  : d00212987
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 PsRegGetSlice(VOS_VOID)
{
    if(VOS_TRUE == g_bIsOmGetSliceFlag)
    {
        return OM_GetSlice();
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PsRegSendDataSetHead
 功能描述  : 设置DmaDest对于消息头
 输入参数  : pDmaDest  : Edma DmaDest消息头起始地址
             ulSysMode : 对应模式

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2014年8月9日
     作    者  : d00212987
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID PsRegSendDataSetHead(PS_REG_RPT_IND_CONTENT_HEAD *pstRegRptIndContHead, VOS_UINT32 ulSysMode)
{
    /*根据不同模式填充发送和接收PID*/
    if (PS_REG_SYS_MODE_WCDMA == ulSysMode)
    {
        pstRegRptIndContHead->usModemId     = MODEM_ID_0;
        pstRegRptIndContHead->enRatMode     = PS_REG_RAT_WCDMA;
        pstRegRptIndContHead->usMsgName     = ID_OM_APP_W_REG_IND;


    }
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
    else if (PS_REG_SYS_MODE_GSM1 == ulSysMode)
    {
        pstRegRptIndContHead->usModemId     = MODEM_ID_1;
        pstRegRptIndContHead->enRatMode     = PS_REG_RAT_GSM;
        pstRegRptIndContHead->usMsgName     = ID_OM_APP_G_REG_IND;
    }
#if (3 == MULTI_MODEM_NUMBER)
    else if (PS_REG_SYS_MODE_GSM2 == ulSysMode)
    {
        pstRegRptIndContHead->usModemId     = MODEM_ID_2;
        pstRegRptIndContHead->enRatMode     = PS_REG_RAT_GSM;
        pstRegRptIndContHead->usMsgName     = ID_OM_APP_G_REG_IND;
    }
#endif

#endif
    else
    {
        pstRegRptIndContHead->usModemId     = MODEM_ID_0;
        pstRegRptIndContHead->enRatMode     = PS_REG_RAT_GSM;
        pstRegRptIndContHead->usMsgName     = ID_OM_APP_G_REG_IND;
    }

}

/*****************************************************************************
 函 数 名  : PsRegPackageSendData
 功能描述  : 打包需搬运寄存器数据
 输入参数  : pulOffset     : 相对于包头的偏移地址
             ulSendBufIndex: 当前发送区Buff编号

 输出参数  : pulTotalOffset : 相对于包头的偏移地址
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2014年8月9日
     作    者  : d00212987
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID PsRegPackageSendData(VOS_UINT32 *pulTotalOffset, VOS_UINT32 ulSendBufIndex)
{
    PS_REG_RPT_IND_CONTENT_HEAD        *pstRegRptIndContHead;
    VOS_UINT32                         *pulBitMap;
    VOS_UINT32                         *pstRegRptTemp;
    VOS_UINT32                         *pstPsRegRptValue;
    VOS_UINT32                          ulSendFrequencyLoop; /* 上报帧频 */
    VOS_UINT32                          ulRegRptCntLoop;
    VOS_UINT32                          ulSysMode;
    VOS_UINT32                          ulOffset      = 0;
    VOS_UINT32                          ulBitMapCount = 0;
    VOS_UINT32                          ulBitMapIndex;
    VOS_UINT32                          ulBitShift;
    VOS_UINT32                          ulRegValue;
    VOS_UINT32                          ulRealRptCnt  = 0;
    VOS_INT                             lLockLevel;

    /* 检测需上报帧 */
    for (ulSendFrequencyLoop=0; ulSendFrequencyLoop<PS_REG_RPT_SEND_FREQUENCY; ulSendFrequencyLoop++)
    {
        if (VOS_TRUE != g_PsRegRptContrl.aulDmaDestWriteStatus[ulSendBufIndex][ulSendFrequencyLoop])
        {
            g_stDmaInfo.ulDmaDestBusyErrTime++;
            continue;
        }

        ulSysMode = PsRegSysModeGet(ulSendBufIndex, ulSendFrequencyLoop);

        /* 取出EDMA缓存数据 */
        /*lint -e534*/
        mdrv_memcpy(g_astPsRegRptTemp[ulSysMode].aulRegValue,
                    g_pstDmaDest[ulSendBufIndex][ulSendFrequencyLoop],
                    PsRegNumberGet(ulSysMode) * sizeof(VOS_UINT32));
        /*lint +e534*/

        lLockLevel = VOS_SplIMP();
        g_PsRegRptContrl.aulDmaDestWriteStatus[ulSendBufIndex][ulSendFrequencyLoop] = VOS_FALSE;

        VOS_Splx(lLockLevel);

        /* 上报寄存器缓存地址 */
        pstRegRptTemp = g_astPsRegRptTemp[ulSysMode].aulRegValue;

        /* 拼包发送起始地址 */
        pstRegRptIndContHead = (PS_REG_RPT_IND_CONTENT_HEAD*)(g_stPsRegRptINDMsg.aucValue + ulOffset);

        ulOffset += sizeof(PS_REG_RPT_IND_CONTENT_HEAD);

        /* 计算BIT MAP长度 */
        ulBitMapCount = (g_astPsRegRptCfg[ulSysMode].ulCnt + 31) / 32;

        /* BitMap起始位置 */
        pulBitMap = (VOS_UINT32*)(g_stPsRegRptINDMsg.aucValue + ulOffset);

        ulOffset += ulBitMapCount * sizeof(VOS_UINT32);

        /* 上报寄存器值起始位置 */
        pstPsRegRptValue = (VOS_UINT32*)(g_stPsRegRptINDMsg.aucValue + ulOffset);

        /* 清除BITMAP */
        /*lint -e534*/
        VOS_MemSet(pulBitMap, 0, ulBitMapCount * sizeof(VOS_UINT32));
        /*lint +e534*/

        /* 寄存器差异上报，隔一段时间上报一帧全数据 */
        if (0 == (g_PsRegRptContrl.aulSendCount[ulSysMode] % g_ulRptRegDiffNum))
        {
            /* 完全上报:位图全部置1 */
            for (ulRegRptCntLoop = 0; ulRegRptCntLoop < PsRegNumberGet(ulSysMode); ulRegRptCntLoop++)
            {
                ulBitMapIndex             = PS_REG_RPT_GET_BITMAP_NUM(ulRegRptCntLoop);
                ulBitShift                = ulRegRptCntLoop & 0x1f;
                pulBitMap[ulBitMapIndex] |= ( 1U << ulBitShift ) ;
            }

            /* 拷贝到发送缓存 */
            /*lint -e534*/
            mdrv_memcpy(pstPsRegRptValue,
                          pstRegRptTemp,
                          PsRegNumberGet(ulSysMode) * sizeof(VOS_UINT32));

            /* 拷贝到比较缓存 */
            mdrv_memcpy(g_astPsRegRptCfg[ulSysMode].aulRegValue,
                        pstRegRptTemp,
                        PsRegNumberGet(ulSysMode) * sizeof(VOS_UINT32));
            /*lint +e534*/

            ulOffset += PsRegNumberGet(ulSysMode) * sizeof(VOS_UINT32);

            g_PsRegRptContrl.aulSendCount[ulSysMode] = 1;

            ulRealRptCnt = PsRegNumberGet(ulSysMode);
        }
        else
        {
            /* 差异上报 */
            ulRealRptCnt = 0;

            for (ulRegRptCntLoop = 0; ulRegRptCntLoop < PsRegNumberGet(ulSysMode); ulRegRptCntLoop++)
            {
                ulBitMapIndex       = PS_REG_RPT_GET_BITMAP_NUM(ulRegRptCntLoop);
                ulBitShift          = ulRegRptCntLoop & 0x1f;
                ulRegValue          = *(pstRegRptTemp + ulRegRptCntLoop);

                /* 仅打包变动寄存器，同时把变动位置置于位图中 */
                if ( g_astPsRegRptCfg[ulSysMode].aulRegValue[ulRegRptCntLoop] != ulRegValue )
                {
                    pstPsRegRptValue[ulRealRptCnt]                           = ulRegValue;
                    g_astPsRegRptCfg[ulSysMode].aulRegValue[ulRegRptCntLoop] = ulRegValue;
                    pulBitMap[ulBitMapIndex]                                |= ( 1U << ulBitShift ) ;
                    ulRealRptCnt++;
                }
            }

            g_PsRegRptContrl.aulSendCount[ulSysMode]++;

            ulOffset += ulRealRptCnt * sizeof(VOS_UINT32);
        }

        pstRegRptIndContHead->usCnt     = (VOS_UINT16)PsRegNumberGet(ulSysMode);
        pstRegRptIndContHead->ulLength  = ulBitMapCount * sizeof(VOS_UINT32) + ulRealRptCnt * sizeof(VOS_UINT32);

        /* 设置消息头 */
        PsRegSendDataSetHead(pstRegRptIndContHead, ulSysMode);

    }

    *pulTotalOffset += ulOffset;

    return ;
}
/*****************************************************************************
 函 数 名  : PsRegTransferTaskEntry
 功能描述  : 搬运寄存器Log到SCOP任务
 输入参数  : VOS_VOID

 输出参数  : 无
 返 回 值  : VOS_VOIDg
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2014年8月9日
     作    者  : d00212987
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID PsRegTransferTaskEntry(VOS_VOID)
{
    VOS_UINT32                          ulTotalOffset = 0;
    VOS_UINT32                          ulSendBufIndex;
    VOS_UINT32                          ulTime;
    VOS_UINT32                          ulStartTime;
    VOS_UINT32                          ulEndTime;
    VOS_INT                             lLockLevel;
    DIAG_TRANS_IND_STRU                 stDiagTransMsg;

#if (VOS_OS_VER == VOS_WIN32)
    VOS_UINT32                          i;
    for(i=0;i<1;i++)
#else
    for(;;)
#endif
    {
        ulStartTime = PsRegGetSlice();
        if (VOS_OK != VOS_SmP(g_ulRegTransferSem, 0))
        {
            /*lint -e534*/
            LogPrint("PsRegTransferTaskEntry: VOS_SmP Fail.\r\n");
            /*lint +e534*/
            continue;
        }

        ulEndTime = PsRegGetSlice();
        ulTime = ulEndTime - ulStartTime;
        if (ulTime > g_stDmaTimeInfo.ulSmPMaxTime)
        {
            g_stDmaTimeInfo.ulSmPMaxTime = ulTime;
        }

        ulTime = ulEndTime - g_stDmaTimeInfo.ulSmVTime;
        if (ulTime > g_stDmaTimeInfo.ulSmVPTime)
        {
            g_stDmaTimeInfo.ulSmVPTime = ulTime;
        }

        g_stDmaInfo.ulDmaTaskTime++;

        lLockLevel = VOS_SplIMP();
        /* 乒乓写标记切换 */
        ulSendBufIndex = g_PsRegRptContrl.ulSendBufIndex;
        g_PsRegRptContrl.ulDmaDestWriteIndex = 0;

        if (0 == g_PsRegRptContrl.ulSendBufIndex)
        {
            g_PsRegRptContrl.ulSendBufIndex      = 1;
        }
        else
        {
            g_PsRegRptContrl.ulSendBufIndex      = 0;
        }
        VOS_Splx(lLockLevel);

        ulStartTime = PsRegGetSlice();

        /* 发送数据包头长度 */
        ulTotalOffset = 0;

        /* 打包发送数据 */
        PsRegPackageSendData(&ulTotalOffset, ulSendBufIndex);

        ulEndTime = PsRegGetSlice();
        ulTime = ulEndTime - ulStartTime;
        if (ulTime > g_stDmaTimeInfo.ulMemcpyMaxTime)
        {
            g_stDmaTimeInfo.ulMemcpyMaxTime = ulTime;
        }

        /* 消息发走 */
        ulStartTime = PsRegGetSlice();

        stDiagTransMsg.ulModule = DIAG_GEN_MODULE_EX(DIAG_MODEM_0, DIAG_MODE_COMM, DIAG_MSG_TYPE_BBP);
        stDiagTransMsg.ulPid    = WUEPS_PID_REG;
        stDiagTransMsg.ulMsgId  = ID_OM_APP_REG_IND;
        stDiagTransMsg.ulLength = ulTotalOffset;
        stDiagTransMsg.pData    = (VOS_VOID *)&g_stPsRegRptINDMsg;

        g_stDmaInfo.ulDiagTransReportBeforTime++;

        /*lint -e534*/
        (VOS_VOID)DIAG_TransReport_Ex(&stDiagTransMsg);
        /*lint +e534*/

        g_stDmaInfo.ulDiagTransReportAfterTime++;

        ulEndTime = PsRegGetSlice();
        ulTime = ulEndTime - ulStartTime;
        if (ulTime > g_stDmaTimeInfo.ulSocpMaxTime)
        {
            g_stDmaTimeInfo.ulSocpMaxTime = ulTime;
        }

        ulTime = ulEndTime - g_stDmaTimeInfo.ulStartSlice;
        if (ulTime > g_stDmaTimeInfo.ulMaxTime)
        {
            g_stDmaTimeInfo.ulMaxTime = ulTime;
        }

    }
}

/*****************************************************************************
 函 数 名  : PsRegDmaIsr
 功能描述  : Dma搬运完成后中断响应函数
 输入参数  : ulChannelarg:通道号，返回调用者传入参数
             ulIntState:  标识中断类型

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2014年8月9日
     作    者  : d00212987
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID PsRegDmaIsr(VOS_UINT32 ulChannelarg, VOS_UINT32 ulIntState)
{
    VOS_UINT32              ulStartTime;

    g_stDmaInfo.ulDmaIsrTime++;
    g_stDmaInfo.ulDmaIntState = ulIntState;

    if (EDMA_BBP_GRIF == ulChannelarg)
    {
        g_ulChan0IsCapture  = VOS_FALSE;
        SLEEP_DMACapRelease();
    }
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
    else if (EDMA_BBP_DBG == ulChannelarg)
    {
        g_ulChan1IsCapture  = VOS_FALSE;
        I1_SLEEP_DMACapRelease();
    }

#if (3 == MULTI_MODEM_NUMBER)
    else if (EDMA_MEMORY_DSP_6 == ulChannelarg)
    {
        g_ulChan2IsCapture  = VOS_FALSE;
        I2_SLEEP_DMACapRelease();
    }
#endif

#endif
    else
    {
        g_stDmaInfo.ulChan1ArgErrTime++;
    }

    if (BALONG_DMA_INT_DONE == ulIntState)
    {
        ulStartTime = PsRegGetSlice() - g_stDmaTimeInfo.ulStartSlice;

        if (ulStartTime > g_stDmaTimeInfo.ulIsrMaxTime)
        {
            g_stDmaTimeInfo.ulIsrMaxTime = ulStartTime;
        }

        if (g_ulSendCount >= g_ulSendMoud)
        {
            /*lint -e534*/
            VOS_SmV(g_ulRegTransferSem);
            /*lint +e534*/
            g_ulSendCount = 1;
        }
        else
        {
            g_ulSendCount++;
        }

        /*lint -e534*/
        /* VOS_SmV(g_ulRegTransferSem);*/
        /*lint +e534*/

        g_stDmaTimeInfo.ulSmVTime = PsRegGetSlice();
        g_stDmaInfo.ulDmaIsrSuccTime++;

    }
    else
    {
        g_stDmaInfo.ulDmaIsrErrTime++;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PsRegDmaGetFirstNode
 功能描述  : 获取Dma头节点配置函数
 输入参数  : psttemp   : EDMA链表控制块起始地址
             pstDmaNode: 待配置EDMA链表控制块起始地址

 输出参数  : psttemp   : EDMA链表控制块起始地址
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2014年8月9日
     作    者  : d00212987
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID PsRegDmaGetFirstNode(BALONG_DMA_CB_S *psttemp, BALONG_DMA_CB_S *pstDmaNode)
{
    /* g_pstDmaDestTemp = pstDmaNode->des_addr;*/
    /*用第一个节点填充通道的链表控制块起始地址*/
    psttemp->lli        = pstDmaNode->lli;
    psttemp->config     = pstDmaNode->config & 0xFFFFFFFE;
    psttemp->src_addr   = pstDmaNode->src_addr;  /*物理地址*/
    psttemp->des_addr   = pstDmaNode->des_addr;  /*物理地址*/
    psttemp->cnt0       = pstDmaNode->cnt0;
    psttemp->bindx      = 0;
    psttemp->cindx      = 0;
    psttemp->cnt1       = 0;

/* mask */
/*
    ulRegVal = *(volatile VOS_UINT32 *)0xFF032058;
    ulRegVal &= 0x7FFF;
    *(volatile VOS_UINT32 *)0xFF032058 = ulRegVal;
*/

}

/*****************************************************************************
 函 数 名  : PsRegDmaSetDmaNode
 功能描述  : Dma节点配置函数
 输入参数  : ulSysMode:系统模式W/G

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2014年8月9日
     作    者  : d00212987
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 PsRegDmaSetDmaNode(BALONG_DMA_CB_S *psttemp, VOS_UINT32 ulSysMode)
{
    VOS_UINT32                          ulRest = VOS_OK;
    VOS_INT                             lLockLevel;

    switch(g_PsRegRptContrl.ulDmaDestWriteIndex)
    {
        case 0: /* 第一帧 */
            if (VOS_FALSE != g_PsRegRptContrl.aulDmaDestWriteStatus[g_PsRegRptContrl.ulSendBufIndex][0])
            {
                /* 丢弃 */
                g_stDmaInfo.ulDmaDestIdleErrTime++;
                ulRest = VOS_ERR;
                break;
            }

            /* EDMA链表控制块起始地址 */
            PsRegDmaGetFirstNode(psttemp, g_pstDmaNode[g_PsRegRptContrl.ulSendBufIndex][0][ulSysMode]);

            lLockLevel = VOS_SplIMP();
            g_PsRegRptContrl.aulDmaDestWriteSysMode[g_PsRegRptContrl.ulSendBufIndex][0] = ulSysMode;
            g_PsRegRptContrl.aulDmaDestWriteStatus[g_PsRegRptContrl.ulSendBufIndex][0] = VOS_TRUE;
            g_PsRegRptContrl.ulDmaDestWriteIndex++;
            VOS_Splx(lLockLevel);

            break;

        case 1:/* 第二帧 */
            if (VOS_FALSE != g_PsRegRptContrl.aulDmaDestWriteStatus[g_PsRegRptContrl.ulSendBufIndex][1])
            {
                /* 丢弃 */
                g_stDmaInfo.ulDmaDestIdleErrTime++;
                ulRest = VOS_ERR;
                break;
            }

            /* EDMA链表控制块起始地址 */
            PsRegDmaGetFirstNode(psttemp, g_pstDmaNode[g_PsRegRptContrl.ulSendBufIndex][1][ulSysMode]);

            lLockLevel = VOS_SplIMP();
            g_PsRegRptContrl.aulDmaDestWriteSysMode[g_PsRegRptContrl.ulSendBufIndex][1] = ulSysMode;
            g_PsRegRptContrl.aulDmaDestWriteStatus[g_PsRegRptContrl.ulSendBufIndex][1] = VOS_TRUE;
            g_PsRegRptContrl.ulDmaDestWriteIndex++;
            VOS_Splx(lLockLevel);
            break;

        default:/* 第三帧 */
            /* EDMA链表控制块起始地址 */
            if (VOS_FALSE != g_PsRegRptContrl.aulDmaDestWriteStatus[g_PsRegRptContrl.ulSendBufIndex][2])
            {
                /* 丢弃 */
                g_stDmaInfo.ulDmaDestIdleErrTime++;
                ulRest = VOS_ERR;
                break;
            }

            /* EDMA链表控制块起始地址 */
            PsRegDmaGetFirstNode(psttemp, g_pstDmaNode[g_PsRegRptContrl.ulSendBufIndex][2][ulSysMode]);
            lLockLevel = VOS_SplIMP();
            g_PsRegRptContrl.aulDmaDestWriteSysMode[g_PsRegRptContrl.ulSendBufIndex][2] = ulSysMode;
            g_PsRegRptContrl.aulDmaDestWriteStatus[g_PsRegRptContrl.ulSendBufIndex][2] = VOS_TRUE;
            g_PsRegRptContrl.ulDmaDestWriteIndex = 0;
            VOS_Splx(lLockLevel);
            break;
    }

    return ulRest;

}

/*****************************************************************************
 函 数 名  : PsRegGetDmaCaptureStatus
 功能描述  : Dma搬运状态
 输入参数  : enModemId:modem0/1

 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2014年8月9日
     作    者  : d00212987
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 PsRegGetDmaCaptureStatus(MODEM_ID_ENUM_UINT16 enModemId)
{
    if (MODEM_ID_0 == enModemId)
    {
        return g_ulChan0IsCapture;
    }
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    else if (MODEM_ID_1 == enModemId)
    {
        return g_ulChan1IsCapture;
    }

#if (3 == MULTI_MODEM_NUMBER)
    else if (MODEM_ID_2 == enModemId)
    {
        return g_ulChan2IsCapture;
    }
#endif

#endif
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : PsRegSetDmaCaptureBusy
 功能描述  : Dma搬运状态
 输入参数  : lDMAChanID

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2014年8月9日
     作    者  : d00212987
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID PsRegSetDmaCaptureBusy(VOS_INT32 lDMAChanID)
{
    /* 防止BBP下电 */
    if (g_lDMAChanID0 == lDMAChanID)
    {
        g_ulChan0IsCapture  = VOS_TRUE;
    }
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
#if (3 == MULTI_MODEM_NUMBER)
    else if (g_lDMAChanID2 == lDMAChanID)
    {
        g_ulChan2IsCapture  = VOS_TRUE;
    }
#endif
    else
    {
        g_ulChan1IsCapture  = VOS_TRUE;
    }
#endif

    return;
}

/*****************************************************************************
 函 数 名  : PsRegSetDmaCaptureIdle
 功能描述  : Dma搬运状态
 输入参数  : lDMAChanID

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2014年8月9日
     作    者  : d00212987
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID PsRegSetDmaCaptureIdle(VOS_INT32 lDMAChanID)
{
    if (g_lDMAChanID0 == lDMAChanID)
    {
        g_ulChan0IsCapture  = VOS_FALSE;

        SLEEP_DMACapRelease();
    }
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )

#if (3 == MULTI_MODEM_NUMBER)
    if (g_lDMAChanID2 == lDMAChanID)
    {
        g_ulChan2IsCapture  = VOS_FALSE;

        I2_SLEEP_DMACapRelease();
    }

#endif
    else
    {
        g_ulChan1IsCapture  = VOS_FALSE;

        I1_SLEEP_DMACapRelease();
    }
#endif

    return;
}

/*****************************************************************************
 函 数 名  : PsRegDmaCapture
 功能描述  : Dma节点配置函数
 输入参数  : ulSysMode:系统模式W/G

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2014年8月9日
     作    者  : d00212987
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID PsRegDmaCapture(VOS_UINT32 ulSysMode)
{
    BALONG_DMA_CB_S                    *psttemp;
    VOS_INT32                           lDMAChanID;
    VOS_UINT32                          ulRest;

    if ((PS_REG_SYS_MODE_GSM == ulSysMode)||(PS_REG_SYS_MODE_WCDMA== ulSysMode))
    {
        lDMAChanID = g_lDMAChanID0;
        g_PsRegRptContrl.bEdma0StartStatus = VOS_TRUE;
    }
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
    else if(PS_REG_SYS_MODE_GSM1 == ulSysMode)
    {
        lDMAChanID = g_lDMAChanID1;
        g_PsRegRptContrl.bEdma1StartStatus = VOS_TRUE;
    }
#if (3 == MULTI_MODEM_NUMBER)
    else if(PS_REG_SYS_MODE_GSM2 == ulSysMode)
    {
        lDMAChanID = g_lDMAChanID2;
        g_PsRegRptContrl.bEdma2StartStatus = VOS_TRUE;
    }
#endif
#endif
    else
    {
        g_stDmaInfo.ulModemErrTime++;
        return;
    }

    if (VOS_TRUE != mdrv_edma_chan_is_idle((VOS_UINT32)lDMAChanID))
    {
        g_stDmaInfo.ulDmaIdleErrTime++;
        return;
    }

    /* 获取通道的链表控制块起始地址 */
    psttemp = mdrv_edma_chan_get_lli_addr((VOS_UINT32)lDMAChanID);

    if (VOS_NULL_PTR == psttemp)
    {
        g_stDmaInfo.ulDmaHeadErrTime++;
        return;
    }

    ulRest = PsRegDmaSetDmaNode(psttemp, ulSysMode);
    if (VOS_OK != ulRest)
    {
        return;
    }

    /* 置DMA通道状态为忙 */
    PsRegSetDmaCaptureBusy(lDMAChanID);
    if (mdrv_edma_chan_lli_async_start((VOS_UINT32)lDMAChanID))
    {
        /* 置DMA通道状态为闲 */
        PsRegSetDmaCaptureIdle(lDMAChanID);
        g_stDmaInfo.ulDmaStartErrTime++;
        return ;
    }

    /* 测试EDMA搬运寄存器值正确性 */
#if 0
    /*读取寄存器*/
    for (ulRest = 0; ulRest < g_astPsRegReqAddr[ulSysMode].ulCnt; ulRest++)
    {
        g_astPsRegRptCfgTemp[ulSysMode].aulRegValue[ulRest] = *((volatile VOS_UINT32*)(g_astPsRegReqAddr[ulSysMode].aulRegAddr[ulRest]));
    }
    g_astPsRegRptCfgTemp[ulSysMode].ulCnt = g_astPsRegReqAddr[ulSysMode].ulCnt;
#endif

    g_stDmaInfo.ulDmaSuccTime++;

    return ;
}

/*****************************************************************************
 函 数 名  : PsRegDmaNodeInit
 功能描述  : Dma节点初始化函数
 输入参数  : pRcvMsg:工具下发消息，包含寄存器个数、地址等信息

 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2014年8月9日
     作    者  : d00212987
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 PsRegDmaNodeInit(APP_OM_REG_START_MODE_STRU *pRcvMsg)
{
    BALONG_DMA_CB_S                    *psttemp;
    VOS_UINT32                         *pStDmaDest;
    BALONG_DMA_REQ_E                    enDmaID = EDMA_BBP_GRIF;
    VOS_UINT32                          ulBufNumLoop;        /* Buff数量 */
    VOS_UINT32                          ulSendFrequencyLoop; /* 上报帧频 */
    VOS_UINT32                          ulDmaNodeCount;
    VOS_UINT32                          i;

    if ((PS_REG_SYS_MODE_GSM == pRcvMsg->enSysMode)||(PS_REG_SYS_MODE_WCDMA == pRcvMsg->enSysMode))
    {
        enDmaID = EDMA_BBP_GRIF;
    }
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )

#if (3 == MULTI_MODEM_NUMBER)
    else if (PS_REG_SYS_MODE_GSM2 == pRcvMsg->enSysMode)
    {
        enDmaID = EDMA_MEMORY_DSP_6;
    }
#endif
    else
    {
        enDmaID = EDMA_BBP_DBG;
    }
#endif

    for (ulBufNumLoop=0; ulBufNumLoop<PS_REG_RPT_BUF_NUM; ulBufNumLoop++)
    {
        for (ulSendFrequencyLoop = 0; ulSendFrequencyLoop < PS_REG_RPT_SEND_FREQUENCY; ulSendFrequencyLoop++)
        {
            /* 寄存器目的起始地址 */
            pStDmaDest = g_pstDmaDest[ulBufNumLoop][ulSendFrequencyLoop];

            /*填充链表节点*/
            psttemp   = g_pstDmaNode[ulBufNumLoop][ulSendFrequencyLoop][pRcvMsg->enSysMode];

            ulDmaNodeCount = 1;

            for (i = 0; i < pRcvMsg->ulRegNum; i++)
            {
                /* 链表头尾处理 */
                if ((0 == i)||(i == pRcvMsg->ulRegNum -1))
                {
                    psttemp->lli        = mdrv_edma_set_lli((VOS_UINT32)g_pstDmaNode[ulBufNumLoop][ulSendFrequencyLoop][pRcvMsg->enSysMode] + ulDmaNodeCount * sizeof(BALONG_DMA_CB_S), ((i < pRcvMsg->ulRegNum - 1)?0:1));
                    psttemp->config     = mdrv_edma_set_config(enDmaID, BALONG_DMA_M2M, EDMA_TRANS_WIDTH_32, EDMA_BUR_LEN_16);
                    psttemp->src_addr   = pRcvMsg->aulRegAddr[i];            /* 源物理地址 */
                    psttemp->des_addr   = (VOS_UINT32)(pStDmaDest + i);      /* 目的物理地址 */
                    psttemp->cnt0       = sizeof(VOS_UINT32);
                    psttemp->bindx      = 0;
                    psttemp->cindx      = 0;
                    psttemp->cnt1       = 0;

                    psttemp++;
                    ulDmaNodeCount++;
                    continue;
                }

                /* 如果地址连续 */
                if (pRcvMsg->aulRegAddr[i-1] + sizeof(VOS_UINT32) == pRcvMsg->aulRegAddr[i])
                {
                    (psttemp-1)->cnt0       += sizeof(VOS_UINT32);
                }
                else
                {
                    psttemp->lli        = mdrv_edma_set_lli((VOS_UINT32)g_pstDmaNode[ulBufNumLoop][ulSendFrequencyLoop][pRcvMsg->enSysMode] + ulDmaNodeCount * sizeof(BALONG_DMA_CB_S), ((i < pRcvMsg->ulRegNum - 1)?0:1));
                    psttemp->config     = mdrv_edma_set_config(enDmaID, BALONG_DMA_M2M, EDMA_TRANS_WIDTH_32, EDMA_BUR_LEN_16);
                    psttemp->src_addr   = pRcvMsg->aulRegAddr[i];               /* 源物理地址 */
                    psttemp->des_addr   = (VOS_UINT32)(pStDmaDest + i);         /* 目的物理地址 */
                    psttemp->cnt0       = sizeof(VOS_UINT32);
                    psttemp->bindx      = 0;
                    psttemp->cindx      = 0;
                    psttemp->cnt1       = 0;

                    psttemp++;
                    ulDmaNodeCount++;
                }
            }
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PsRegDmaUnCacheMemAlloc
 功能描述  : 寄存器上报所需缓存申请
 输入参数  : VOS_VOID

 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2014年8月9日
     作    者  : d00212987
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 PsRegDmaUnCacheMemAlloc(VOS_VOID)
{
    VOS_UINT_PTR                        ulAddr;
    VOS_UINT32                          ulBufNumLoop;        /* Buff数量 */
    VOS_UINT32                          ulSysModeLoop;       /* Sys Mode数量 */
    VOS_UINT32                          ulSendFrequencyLoop; /* 上报帧频 */

    /* [PS_REG_RPT_BUF_NUM][PS_REG_RPT_SEND_FREQUENCY][PS_REG_SYS_MODE_BUTT] */
    /* Buff数量 */
    for (ulBufNumLoop=0; ulBufNumLoop<PS_REG_RPT_BUF_NUM; ulBufNumLoop++)
    {
        /* 上报帧频 */
        for (ulSendFrequencyLoop=0; ulSendFrequencyLoop<PS_REG_RPT_SEND_FREQUENCY; ulSendFrequencyLoop++)
        {
            /* DMA 目的空间 */
            g_pstDmaDest[ulBufNumLoop][ulSendFrequencyLoop] = (VOS_UINT32 *)VOS_UnCacheMemAlloc(PS_REG_RPT_DMA_DEST_BUFFER + 0x100, &ulAddr);

            if (VOS_NULL_PTR == g_pstDmaDest[ulBufNumLoop][ulSendFrequencyLoop])
            {
                /*lint -e534*/
                vos_printf("\r\nPsRegDmaInit: fail to malloc memory for g_pstDmaDest[%d][%d]!\r\n",
                            ulBufNumLoop, ulSendFrequencyLoop);
                /*lint +e534*/
                return VOS_ERR;
            }

            /* Sys Mode数量 */
            for (ulSysModeLoop=0; ulSysModeLoop<PS_REG_SYS_MODE_BUTT; ulSysModeLoop++)
            {
                /* DMA搬运节点空间 */
                g_pstDmaNode[ulBufNumLoop][ulSendFrequencyLoop][ulSysModeLoop] = (BALONG_DMA_CB_S *)VOS_UnCacheMemAlloc(PS_REG_RPT_MAX_NUM * sizeof(BALONG_DMA_CB_S), &ulAddr);

                if (VOS_NULL_PTR == g_pstDmaNode[ulBufNumLoop][ulSendFrequencyLoop][ulSysModeLoop])
                {
                    /*lint -e534*/
                    vos_printf("\r\nPsRegDmaNodeInit: malloc memory fail at g_pstDmaNode[%d][%d][%d]!\r\n",
                                ulBufNumLoop, ulSendFrequencyLoop, ulSysModeLoop);
                    /*lint +e534*/
                    return VOS_ERR;
                }
            }
        }
    }

    return VOS_OK;
  }

/*****************************************************************************
 函 数 名  : PsRegDmaInit
 功能描述  :
 输入参数  : VOS_VOID

 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2014年8月9日
     作    者  : d00212987
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 PsRegDmaInit(VOS_VOID)
{
    /* Dma 所需内存申请 */
    if(VOS_OK != PsRegDmaUnCacheMemAlloc())
    {
        /*lint -e534*/
        vos_printf("\r\nPsRegDmaInit: alloc memery fail !\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    /* 初始化通道 REGDMA_CHANNEL_REQ */
    g_lDMAChanID0 = mdrv_edma_chan_init(EDMA_BBP_GRIF, (channel_isr)PsRegDmaIsr,
                                          EDMA_BBP_GRIF, (BALONG_DMA_INT_DONE | BALONG_DMA_INT_TRANSFER_ERR));
    if (g_lDMAChanID0 < 0)
    {
        /*lint -e534*/
        vos_printf("\r\nPsRegDmaInit: fail to init edma0 channel, phy channel is 0x%x\r\n", g_lDMAChanID0);
        /*lint +e534*/
        return VOS_ERR;
    }

/* 当前Austin上GRIF和DEG通道不能复用，副卡当前寄存器捕获暂不打开 */
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
    /* 初始化通道 REGDMA_CHANNEL_REQ */
    g_lDMAChanID1 = mdrv_edma_chan_init(EDMA_BBP_DBG, (channel_isr)PsRegDmaIsr,
                                          EDMA_BBP_DBG, (BALONG_DMA_INT_DONE | BALONG_DMA_INT_TRANSFER_ERR));
    if (g_lDMAChanID1 < 0)
    {
        /*lint -e534*/
        vos_printf("\r\nPsRegDmaInit: fail to init edma1 channel, phy channel is 0x%x\r\n", g_lDMAChanID1);
        /*lint +e534*/
        return VOS_ERR;
    }

#if (3 == MULTI_MODEM_NUMBER)
    g_lDMAChanID2 = mdrv_edma_chan_init(EDMA_MEMORY_DSP_6, (channel_isr)PsRegDmaIsr,
                                          EDMA_MEMORY_DSP_6, (BALONG_DMA_INT_DONE | BALONG_DMA_INT_TRANSFER_ERR));
    if (g_lDMAChanID2 < 0)
    {
        /*lint -e534*/
        vos_printf("\r\nPsRegDmaInit: fail to init edma2 channel, phy channel is 0x%x\r\n", g_lDMAChanID2);
        /*lint +e534*/
        return VOS_ERR;
    }
#endif

#endif

    return VOS_OK;
}

/******************************************************************************
 Prototype      : PsRegCapture
 Description    : 完成寄存器的捕获
 Input          : ulSysMode:系统模式W/G/G1

 Output         :
 Return Value   :

 History        : ---
  1.Date        : 2010-8-24
    Author      : g47350
    Modification: Created function
******************************************************************************/
VOS_VOID PsRegCapture(VOS_UINT32 ulSysMode)
{
    PS_REG_SYS_MODE_ENUM_UINT32         enSysMode;
    PS_REG_RPT_CFG_STRU                *pstPsRegRptCfg;
    VOS_UINT32                          ulTimeStart;
    VOS_UINT32                          ulTimeEnd;
    VOS_UINT32                          ulTime;

    if (VOS_FALSE == g_PsRegRptContrl.bRptEnableStatus)
    {
        return;
    }

    /*定义不同需要进行转换*/
    enSysMode       = ulSysMode;
    pstPsRegRptCfg  = &g_astPsRegRptCfg[enSysMode];

    /*判断当前捕获寄存器的个数*/
    if (0 == pstPsRegRptCfg->ulCnt)
    {
        return;
    }

    ulTimeStart = PsRegGetSlice();
    g_stDmaTimeInfo.ulStartSlice = ulTimeStart;

    PsRegDmaCapture(ulSysMode);

    ulTimeEnd = PsRegGetSlice();
    ulTime = ulTimeEnd - ulTimeStart;
    if (ulTime > g_stDmaTimeInfo.ulDmaStartTime)
    {
        g_stDmaTimeInfo.ulDmaStartTime = ulTime;
    }

    return;
}

/******************************************************************************
 Prototype      : PsRegNumberGet
 Description    : 获取捕获寄存器的个数
 Input          : enSysMode - 指示配置的模式
 Output         : VOID
 Return Value   : VOS_UINT32- 寄存器个数

 History        : ---
  1.Date        : 2010-8-24
    Author      : g47350
    Modification: Created function
******************************************************************************/
VOS_UINT32 PsRegNumberGet(PS_REG_SYS_MODE_ENUM_UINT32 enSysMode)
{
    return g_astPsRegRptCfg[enSysMode].ulCnt;
}

/******************************************************************************
 Prototype      : PsRegSysModeGet
 Description    : 获取捕获寄存器的个数
 Input          : enSysMode - 指示配置的模式
 Output         : VOID
 Return Value   : VOS_UINT32- 寄存器个数

 History        : ---
  1.Date        : 2010-8-24
    Author      : g47350
    Modification: Created function
******************************************************************************/
VOS_UINT32 PsRegSysModeGet(VOS_UINT32 ulSendBufIndex, VOS_UINT32 ulSendFrequency)
{
    return g_PsRegRptContrl.aulDmaDestWriteSysMode[ulSendBufIndex][ulSendFrequency];
}

/******************************************************************************
 Prototype      : PsRegsInfoAddrGet
 Description    : 返回保存寄存器数组的地址
 Input          : enSysMode - 指示配置的模式
 Output         : VOID
 Return Value   : VOS_VOID* - 寄存器数组地址

 History        : ---
  1.Date        : 2010-8-24
    Author      : g47350
    Modification: Created function
******************************************************************************/
VOS_VOID* PsRegsInfoAddrGet(PS_REG_SYS_MODE_ENUM_UINT32 enSysMode)
{
    return (VOS_VOID*)(g_astPsRegRptCfg[enSysMode].aulRegValue);
}

/******************************************************************************
 Prototype      : PsRegInit
 Description    : 全局变量初始化
 Input          : VOID
 Output         : VOID
 Return Value   : VOS_UINT32

 History        : ---
  1.Date        : 2010-8-24
    Author      : g47350
    Modification: Created function
******************************************************************************/
VOS_UINT32 PsRegInit(VOS_VOID)
{
    OM_BBP_DUMP_ENABLE_STRU             stEnableFlag;
    VOS_UINT32                           ulRet;

    /*lint -e534*/
    VOS_MemSet(&g_stPsRegRptINDMsg,  0, sizeof(g_stPsRegRptINDMsg));
    VOS_MemSet(g_astPsRegRptCfg,        0, sizeof(g_astPsRegRptCfg));
    VOS_MemSet(g_astPsRegRptBuf,        0, sizeof(g_astPsRegRptBuf));

    VOS_MemSet(&g_PsRegRptContrl,        0, sizeof(g_PsRegRptContrl));
    /*lint +e534*/

    g_ulRptRegInitStatus = VOS_FALSE;

    /* 读取NV项判断功能是否开启 */
    if (NV_OK != NV_Read(en_NV_Item_BBP_DUMP_ENABLE,
                         (VOS_VOID *)(&stEnableFlag),
                         sizeof(OM_BBP_DUMP_ENABLE_STRU)))
    {
        /*lint -e534*/
        LogPrint("PsRegInit: Read Nv Fail\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    /* 判断是否启动BBP数采:抓寄存器和BBP数采只开其一 */
    if (VOS_TRUE == stEnableFlag.ulEnable)
    {
        /*lint -e534*/
        LogPrint("PsRegInit: BBP Enable \r\n");
        /*lint +e534*/
        return VOS_OK;
    }

    /* EDMA初始化 */
    ulRet = PsRegDmaInit();
    if (VOS_OK != ulRet)
    {
        /*lint -e534*/
        LogPrint("PsRegInit: Dma Init fail \r\n");
        /*lint +e534*/
        return ulRet;
    }

    g_ulRptRegDiffNum    = PS_REG_RPT_DIFF_NUM; /* 差异上报次数初始化 */
    g_ulRptRegInitStatus = VOS_TRUE;

    return VOS_OK;
}

/******************************************************************************
 Prototype      : PsRegSndOmAppRegModCnf
 Description    : 回复给PC侧工具消息
 Input          : usTransPrimId - 回复消息原语
                  ulResult      - 执行结果
                  pPara         - 回复内容

 Output         : VOID
 Return Value   : VOID

 History        : ---
  1.Date        : 2010-8-24
    Author      : g47350
    Modification: Created function
******************************************************************************/
VOS_VOID PsRegSndOmAppRegModCnf(
    VOS_UINT16                          usTransPrimId,
    VOS_UINT32                          ulResult,
    OM_APP_REG_START_CNF_STRU          *pstOmAppRegCnf)
{
    OM_APP_TRANS_CNF_STRU              *pstAppTransCnf;
    OM_APP_REG_MODE_NUM_STRU           *pstAppModeNum;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          i;
    VOS_UINT32                          ulTotalLen;
    DIAG_TRANS_IND_STRU                 stDiagTransMsg;

    if ((PS_SUCC == ulResult) && (0 != pstOmAppRegCnf->ulSysModeNum))
    {
        /* 需要把工具配置成功的寄存器地址返回给工具 */

        /* 消息头长度 */
        ulDataLen   = offsetof(OM_APP_REG_START_CNF_STRU,aucAddr) +
                      pstOmAppRegCnf->ulSysModeNum * offsetof(OM_APP_REG_MODE_NUM_STRU,aucAddr);

        /* 寄存器地址长度 */
        for (i=0; i<PS_REG_SYS_MODE_BUTT; i++)
        {
            ulDataLen += g_astPsRegReqAddr[i].ulCnt * sizeof(VOS_UINT32);
        }
    }
    else
    {
        ulDataLen  = sizeof(OM_APP_REG_START_CNF_STRU);
    }

    pstAppTransCnf = (OM_APP_TRANS_CNF_STRU *)VOS_MemAlloc(WUEPS_PID_REG, DYNAMIC_MEM_PT,
                                       offsetof(OM_APP_TRANS_CNF_STRU, aucPara[0]) + ulDataLen);
    if (VOS_NULL_PTR == pstAppTransCnf)
    {
        PS_LOG(WUEPS_PID_REG, 0, LOG_LEVEL_ERROR, "Error: Alloc msg ID_OM_APP_REG_ADD_CNF fail!");
        return;
    }

    /* 下一字节至包尾的长度，单位为Byte */
    ulTotalLen = (offsetof(OM_APP_TRANS_CNF_STRU, aucPara[0]) + ulDataLen);

    pstOmAppRegCnf->ulErrCode = ulResult;

    /*lint -e419 -e416 -e534 */
    VOS_MemCpy((VOS_VOID*)pstAppTransCnf->aucPara, (VOS_VOID*)pstOmAppRegCnf, offsetof(OM_APP_REG_START_CNF_STRU,aucAddr));
    /*lint +e419 +e416 +e534 */

    ulDataLen = offsetof(OM_APP_REG_START_CNF_STRU,aucAddr);
    /*将当前捕获的寄存器地址拷贝到发送数据中*/
    if ((PS_SUCC == ulResult) && (0 != pstOmAppRegCnf->ulSysModeNum))
    {
        for (i=0; i<PS_REG_SYS_MODE_BUTT; i++)
        {
            pstAppModeNum = (OM_APP_REG_MODE_NUM_STRU*)(pstAppTransCnf->aucPara + ulDataLen);

            if (0 !=g_astPsRegReqAddr[i].ulCnt)
            {
                pstAppModeNum->enSysMode = i;
                pstAppModeNum->ulRegNum  = g_astPsRegReqAddr[i].ulCnt;
                /*lint -e419 -e416 -e534 */
                VOS_MemCpy((VOS_VOID*)pstAppModeNum->aucAddr,
                           (VOS_VOID*)g_astPsRegReqAddr[i].aulRegAddr,
                           pstAppModeNum->ulRegNum * sizeof(VOS_UINT32));
                /*lint +e419 +e416 +e534 */

                ulDataLen += pstAppModeNum->ulRegNum * sizeof(VOS_UINT32) + offsetof(OM_APP_REG_MODE_NUM_STRU,aucAddr);
            }
        }
    }

    stDiagTransMsg.ulModule = DIAG_GEN_MODULE_EX(DIAG_MODEM_0, DIAG_MODE_COMM, DIAG_MSG_TYPE_BBP);
    stDiagTransMsg.ulPid    = WUEPS_PID_REG;
    stDiagTransMsg.ulMsgId  = usTransPrimId;
    stDiagTransMsg.ulLength = ulTotalLen;
    stDiagTransMsg.pData    = (VOS_VOID *)pstAppTransCnf;

    if (VOS_OK != DIAG_TransReport_Ex(&stDiagTransMsg))
    {
        PS_LOG(WUEPS_PID_REG, 0, LOG_LEVEL_ERROR, "Error: Send msg ID_OM_APP_REG_ADD_CNF fail!");
    }
    else
    {
        PS_LOG(WUEPS_PID_REG, 0, LOG_LEVEL_INFO, "Info: Send msg ID_OM_APP_REG_ADD_CNF success!");
    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_REG, pstAppTransCnf);
    /*lint +e534*/

    return ;
}


/*****************************************************************************
 函 数 名  : PsRegRcvAppOmRegDiffSetNumReq
 功能描述  : 设置差异上报次数，达到该次数后需上报一帧全的
 输入参数  : pRcvMsg: 工具下发消息

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2014年8月9日
     作    者  : d00212987
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID PsRegRcvAppOmRegDiffSetNumReq(VOS_VOID* pRcvMsg)
{
    OM_APP_REG_START_CNF_STRU           stOmAppRegCnf;
    OM_REG_RPT_DIFF_STRU               *pRegRptDiff;

    (VOS_VOID)VOS_MemSet(&stOmAppRegCnf, 0, sizeof(OM_APP_REG_START_CNF_STRU));

    PsRegDmaInfoShow();

    /* 回复工具初始值 */
    stOmAppRegCnf.ulSysModeNum = 0;

    /* 抓寄存器使能 */
    if (VOS_TRUE != g_ulRptRegInitStatus)
    {
        /*lint -e534*/
        LogPrint("\r\nPsRegRcvAppOmRegDiffSetNumReq:Reg not Init!");
        /*lint +e534*/
        PsRegSndOmAppRegModCnf(ID_APP_OM_REG_DIFF_CNF, PS_REG_RPT_NOT_ENABLE, &stOmAppRegCnf);
        return ;
    }

    pRegRptDiff = (OM_REG_RPT_DIFF_STRU*)pRcvMsg;

    g_ulRptRegDiffNum = pRegRptDiff->ulRptDiffNum;

    PsRegSndOmAppRegModCnf(ID_APP_OM_REG_DIFF_CNF, PS_REG_OK, &stOmAppRegCnf);

    return;
}

/******************************************************************************
 Prototype      : PsRegRcvAppOmRegStopReq
 Description    : 停止寄存器上报消息处理函数
 Input          : pRcvMsg - 消息体

 Output         : VOID
 Return Value   : VOID

 History        : ---
  1.Date        : 2010-8-24
    Author      : g47350
    Modification: Created function
******************************************************************************/
VOS_VOID PsRegRcvAppOmRegStopReq(VOS_VOID* pRcvMsg)
{
    OM_REG_RPT_STOP_STRU               *pMsg = (OM_REG_RPT_STOP_STRU*)pRcvMsg;
    OM_APP_REG_START_CNF_STRU           stOmAppRegCnf;
    VOS_INT                             lLockLevel;
    VOS_INT                             lRet;

    (VOS_VOID)VOS_MemSet(&stOmAppRegCnf, 0, sizeof(OM_APP_REG_START_CNF_STRU));

    /* 回复工具初始值 */
    stOmAppRegCnf.ulSysModeNum = 0;

    /* 抓寄存器使能 */
    if (VOS_TRUE != g_ulRptRegInitStatus)
    {
        /*lint -e534*/
        LogPrint("\r\nPsRegRcvAppOmRegStartReq:Reg not Init!");
        /*lint +e534*/
        PsRegSndOmAppRegModCnf(ID_APP_OM_REG_STOP_CNF, PS_REG_RPT_NOT_ENABLE, &stOmAppRegCnf);
        return;
    }

    /* 参数检查 */
    if (PS_REG_SYS_MODE_BUTT <= pMsg->enSysMode)
    {
        /*lint -e534*/
        LogPrint("\r\nPsRegRcvAppOmRegStartReq:Req mode num err!\r\n");
        /*lint +e534*/
        PsRegSndOmAppRegModCnf(ID_APP_OM_REG_STOP_CNF, PS_REG_MODE_NUM_ERR, &stOmAppRegCnf);
        return ;
    }

    lLockLevel = VOS_SplIMP();
    /*lint -e534*/
    VOS_MemSet(g_astPsRegRptCfg, 0, sizeof(g_astPsRegRptCfg));
    /*lint +e534*/
    VOS_Splx(lLockLevel);

    /*寄存器上报功能已经处于关闭状态，则打印信息*/
    if (VOS_FALSE == g_PsRegRptContrl.bRptEnableStatus)
    {
        /*lint -e534*/
        LogPrint("\r\nPsRegRcvAppOmRegStopReq:RegRptStart Function has been stoped!");
        /*lint +e534*/
        PsRegSndOmAppRegModCnf(ID_APP_OM_REG_STOP_CNF, PS_REG_STOP_ERR, &stOmAppRegCnf);
        return;
    }

    if (VOS_TRUE == g_PsRegRptContrl.bEdma0StartStatus)
    {
        /* 停止EDMA0 */
        lRet = mdrv_edma_chan_stop((VOS_UINT32)g_lDMAChanID0);
        if (MDRV_ERROR == lRet)
        {
            /*lint -e534*/
            LogPrint("\r\nPsRegRcvAppOmRegStopReq:Edma0 stop fail!");
            /*lint +e534*/
            PsRegSndOmAppRegModCnf(ID_APP_OM_REG_STOP_CNF, PS_REG_STOP_DAM_FAIL, &stOmAppRegCnf);
            return ;
        }
    }

#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
    if (VOS_TRUE == g_PsRegRptContrl.bEdma1StartStatus)
    {
        lRet = mdrv_edma_chan_stop((VOS_UINT32)g_lDMAChanID1);
        if (MDRV_ERROR == lRet)
        {
            /*lint -e534*/
            LogPrint("\r\nPsRegRcvAppOmRegStopReq:Edma1 stop fail!");
            /*lint +e534*/
            PsRegSndOmAppRegModCnf(ID_APP_OM_REG_STOP_CNF, PS_REG_STOP_DAM_FAIL, &stOmAppRegCnf);
            return ;
        }
    }

#if (3 == MULTI_MODEM_NUMBER)
    if (VOS_TRUE == g_PsRegRptContrl.bEdma2StartStatus)
    {
        lRet = mdrv_edma_chan_stop((VOS_UINT32)g_lDMAChanID2);
        if (MDRV_ERROR == lRet)
        {
            /*lint -e534*/
            LogPrint("\r\nPsRegRcvAppOmRegStopReq:Edma2 stop fail!");
            /*lint +e534*/
            PsRegSndOmAppRegModCnf(ID_APP_OM_REG_STOP_CNF, PS_REG_STOP_DAM_FAIL, &stOmAppRegCnf);
            return ;
        }
    }
#endif
#endif

    /* 清空上报控制状态 */
    /*lint -e534*/
    VOS_MemSet(&g_PsRegRptContrl, 0, sizeof(g_PsRegRptContrl));
    /*lint +e534*/

    PsRegSndOmAppRegModCnf(ID_APP_OM_REG_STOP_CNF, PS_REG_OK, &stOmAppRegCnf);

    return;
}

/*****************************************************************************
 函 数 名  : PsRegAddrCheck
 功能描述  : 寄存器地址检测
 输入参数  : PS_REG_SYS_MODE_ENUM_UINT32 enSysMode
             VOS_UINT32 ulAddr
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2014年9月19日
     作    者  : s00207770
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 PsRegAddrCheck(PS_REG_SYS_MODE_ENUM_UINT32 enSysMode, VOS_UINT32 ulAddr)
{
    VOS_UINT32                          ulRegBase = 0;
    VOS_UINT32                          ulRegComm = (SOC_BBP_COMM_BASE_ADDR & 0xFFF00000);

    if (PS_REG_SYS_MODE_WCDMA == enSysMode)
    {
        ulRegBase  = (SOC_BBP_WCDMA_BASE_ADDR & 0xFFF00000);
    }
    else if (PS_REG_SYS_MODE_GSM == enSysMode)
    {
        ulRegBase  = (SOC_BBP_GSM_BASE_ADDR & 0xFFFF0000);
    }
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
    else if (PS_REG_SYS_MODE_GSM1 == enSysMode)
    {
        ulRegBase  = (SOC_BBP_GSM1_BASE_ADDR & 0xFFFF0000);
    }

#if (3 == MULTI_MODEM_NUMBER)
    else if (PS_REG_SYS_MODE_GSM2 == enSysMode)
    {
        ulRegBase  = (SOC_BBP_GSM_BASE_ADDR & 0xFFFF0000);
    }
#endif

#endif
    else
    {
        ulRegBase  = 0;
    }

    if (ulRegComm == (ulAddr & 0xFFF00000))
    {
        return VOS_OK;
    }

    if (PS_REG_SYS_MODE_WCDMA == enSysMode)
    {
        if (ulRegBase != (ulAddr & 0xFFF00000))
        {
            g_ulPsRegErrCount++;
            return VOS_ERR;
        }
    }
    else
    {
        if (ulRegBase != (ulAddr & 0xFFFF0000))
        {
            g_ulPsRegErrCount++;
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PsRegRcvAppMsgCheck
 功能描述  : 收到工具下发消息检查
 输入参数  : pRcvMsg: 工具下发消息

 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2014年8月9日
     作    者  : d00212987
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 PsRegRcvAppMsgCheck(APP_OM_REG_START_MODE_STRU *pRcvMsg)
{
    VOS_UINT32                          ulRegNumLoop;

    /*配置模式检查*/
    if (PS_REG_SYS_MODE_BUTT <= pRcvMsg->enSysMode)
    {
        /*lint -e534*/
        LogPrint1("PsRegRcvAppMsgCheck:Config system mode is %d wrong!!\r\n",
                (VOS_INT32)pRcvMsg->enSysMode);
        /*lint +e534*/
        return PS_REG_MODE_ERR;
    }

    /*寄存器个数检查*/
    if (0 == pRcvMsg->ulRegNum)
    {
        /*lint -e534*/
        LogPrint("PsRegRcvAppMsgCheck:Regist Number Error:0!");
        /*lint +e534*/
        return PS_REG_NUM_ZERO;
    }

    if ((PS_REG_SYS_MODE_WCDMA == pRcvMsg->enSysMode) && (PS_REG_RPT_MAX_NUM < pRcvMsg->ulRegNum))
    {
        /*lint -e534*/
        LogPrint1("PsRegRcvAppMsgCheck:Reg wcdma Number %d  Error!", (VOS_INT32)pRcvMsg->ulRegNum);
        /*lint +e534*/
        return PS_W_REG_NUM_TOO_LARGE;
    }

    if ((PS_REG_SYS_MODE_GSM == pRcvMsg->enSysMode) && (PS_REG_RPT_G_MAX_NUM < pRcvMsg->ulRegNum))
    {
        /*lint -e534*/
        LogPrint1("PsRegRcvAppMsgCheck:Reg gsm Number %d  Error!", (VOS_INT32)pRcvMsg->ulRegNum);
        /*lint +e534*/
        return PS_G_REG_NUM_TOO_LARGE;
    }

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    if ((PS_REG_SYS_MODE_GSM1 == pRcvMsg->enSysMode) && (PS_REG_RPT_G_MAX_NUM < pRcvMsg->ulRegNum))
    {
        /*lint -e534*/
        LogPrint1("PsRegRcvAppMsgCheck:Regist gsm1 Number %d  Error!", (VOS_INT32)pRcvMsg->ulRegNum);
        /*lint +e534*/
        return PS_G1_REG_NUM_TOO_LARGE;
    }

#if (3 == MULTI_MODEM_NUMBER)
    if ((PS_REG_SYS_MODE_GSM2 == pRcvMsg->enSysMode) && (PS_REG_RPT_G_MAX_NUM < pRcvMsg->ulRegNum))
    {
        /*lint -e534*/
        LogPrint1("PsRegRcvAppMsgCheck:Regist gsm2 Number %d  Error!", (VOS_INT32)pRcvMsg->ulRegNum);
        /*lint +e534*/
        return PS_G2_REG_NUM_TOO_LARGE;
    }
#endif

#endif

    /* 非四字节对齐的地址不能上报 */
    if (0 != (pRcvMsg->aulRegAddr[0]&HPA_ARM_ALIGNMENT))
    {
        /*lint -e534*/
        LogPrint1("PsRegRcvAppMsgCheck:no align! %d", (VOS_INT32)pRcvMsg->aulRegAddr[0]);
        /*lint +e534*/
        return PS_REG_ALIGN_ERR;
    }

    if (VOS_ERR == PsRegAddrCheck(pRcvMsg->enSysMode, pRcvMsg->aulRegAddr[0]))
    {
        /*lint -e534*/
        LogPrint1("PsRegRcvAppMsgCheck:Invalid Address! %d", (VOS_INT32)pRcvMsg->aulRegAddr[0]);
        /*lint +e534*/
        return PS_REG_ADDR_NOT_MATCH_MODE;
    }

    for (ulRegNumLoop = 1; ulRegNumLoop < pRcvMsg->ulRegNum; ulRegNumLoop++)
    {
        /* 字节对其检查 */
        /*lint -e661*/
        if (0 != (pRcvMsg->aulRegAddr[ulRegNumLoop]&HPA_ARM_ALIGNMENT))
        {
            /*lint -e534*/
            LogPrint2("PsRegRcvAppMsgCheck:no align! %d %d", (VOS_INT32)pRcvMsg->aulRegAddr[ulRegNumLoop],(VOS_INT32)ulRegNumLoop);
            /*lint +e534*/
            return PS_REG_ALIGN_ERR;
        }

        /* 寄存器排序简单检查 */
        if (pRcvMsg->aulRegAddr[ulRegNumLoop - 1] >= pRcvMsg->aulRegAddr[ulRegNumLoop])
        {
            /*lint -e534*/
            LogPrint2("PsRegRcvAppMsgCheck: no order! %d %d", (VOS_INT32)pRcvMsg->aulRegAddr[ulRegNumLoop],(VOS_INT32)ulRegNumLoop);
            /*lint +e534*/
            return PS_REG_QUEUE_ERR;
        }

        if (VOS_ERR == PsRegAddrCheck(pRcvMsg->enSysMode, pRcvMsg->aulRegAddr[ulRegNumLoop]))
        {
            /*lint -e534*/
            LogPrint2("PsRegRcvAppMsgCheck:Invalid Address! %d %d", (VOS_INT32)pRcvMsg->aulRegAddr[ulRegNumLoop],(VOS_INT32)ulRegNumLoop);
            /*lint +e534*/
            return PS_REG_ADDR_NOT_MATCH_MODE;
        }
        /*lint +e661*/
    }

    return VOS_OK;
}

/******************************************************************************
 Prototype      : PsRegRcvAppOmRegConfig
 Description    : 收到寄存器配置消息
                  备注:由工具保证不重复下发相同寄存器地址
 Input          : pRcvMsg - 消息体

 Output         : VOID
 Return Value   : VOS_UINT32

 History        : ---
  1.Date        : 2010-8-24
    Author      : g47350
    Modification: Created function
******************************************************************************/
VOS_UINT32 PsRegRcvAppOmRegConfig(VOS_VOID* pMsg)
{
    APP_OM_REG_START_MODE_STRU         *pRcvMsg;
    VOS_UINT32                          ulRest;

    pRcvMsg = (APP_OM_REG_START_MODE_STRU*)pMsg;

    /* 参数检查 */
    ulRest = PsRegRcvAppMsgCheck(pRcvMsg);
    if (VOS_OK != ulRest)
    {
        /*lint -e534*/
        LogPrint("PsRegRcvAppOmRegStartReq:Reg Start Req para err!\r\n");
        /*lint +e534*/
        return ulRest;
    }

    /* DMA节点配置 */
    if (VOS_OK != PsRegDmaNodeInit(pRcvMsg))
    {
        /*lint -e534*/
        LogPrint("PsRegRcvAppOmRegStartReq:Edma stop fail!");
        /*lint +e534*/
        return PS_REG_RPT_DMA_INIT_FAIL;
    }

    g_astPsRegRptCfg[pRcvMsg->enSysMode].ulCnt  = pRcvMsg->ulRegNum;

    /* 缓存工具下发寄存器上报地址 */
    /*lint -e534*/
    VOS_MemCpy(g_astPsRegReqAddr[pRcvMsg->enSysMode].aulRegAddr,
               pRcvMsg->aulRegAddr,
               (pRcvMsg->ulRegNum)*sizeof(VOS_UINT32));/* [false alarm]:Buffer overflow误判  */
    /*lint +e534*/

    g_astPsRegReqAddr[pRcvMsg->enSysMode].ulCnt = pRcvMsg->ulRegNum;

    return VOS_OK;

}

/******************************************************************************
 Prototype      : PsRegRcvAppOmRegStartReq
 Description    : 添加寄存器地址消息处理函数
                  备注:由工具保证不重复下发相同寄存器地址
 Input          : pRcvMsg - 消息体

 Output         : VOID
 Return Value   : VOID

 History        : ---
  1.Date        : 2010-8-24
    Author      : g47350
    Modification: Created function
******************************************************************************/
VOS_VOID PsRegRcvAppOmRegStartReq(VOS_VOID* pMsg)
{
    APP_OM_REG_START_REQ_STRU          *pRcvMsgHead = (APP_OM_REG_START_REQ_STRU*)pMsg;
    OM_APP_REG_START_CNF_STRU           stOmAppRegCnf;
    APP_OM_REG_START_MODE_STRU         *pRcvMsg;
    VOS_UINT32                          ulMsgLen = 0;
    VOS_UINT32                          ulRest;
    VOS_UINT32                          i;

    (VOS_VOID)VOS_MemSet(&stOmAppRegCnf, 0, sizeof(OM_APP_REG_START_CNF_STRU));

    /* 回复工具初始值 */
    stOmAppRegCnf.ulSysModeNum = 0;

    /* 抓寄存器使能 */
    if (VOS_TRUE != g_ulRptRegInitStatus)
    {
        /*lint -e534*/
        LogPrint("\r\nPsRegRcvAppOmRegStartReq:Reg not Init!");
        /*lint +e534*/
        PsRegSndOmAppRegModCnf(ID_APP_OM_REG_START_CNF, PS_REG_RPT_NOT_ENABLE, &stOmAppRegCnf);
        return;
    }

    /* 判断上报状态 */
    if (VOS_FALSE != g_PsRegRptContrl.bRptEnableStatus)
    {
        /*lint -e534*/
        LogPrint("\r\nPsRegRcvAppOmRegStartReq:Rpt Status is not Stop!");
        /*lint +e534*/
        PsRegSndOmAppRegModCnf(ID_APP_OM_REG_START_CNF, PS_REG_STOP_ERR, &stOmAppRegCnf);
        return;
    }

    /* 参数检查 */
    if (PS_REG_SYS_MODE_BUTT < pRcvMsgHead->ulSysModeNum)
    {
        /*lint -e534*/
        LogPrint1("\r\nPsRegRcvAppOmRegStartReq:Req mode num err is %d!", (VOS_INT)pRcvMsgHead->ulSysModeNum);
        /*lint +e534*/
        PsRegSndOmAppRegModCnf(ID_APP_OM_REG_START_CNF, PS_REG_MODE_NUM_ERR, &stOmAppRegCnf);
        return;
    }

    /* 消息长度检查 */
    if (sizeof(APP_OM_REG_START_MODE_STRU) > pRcvMsgHead->ulValueLenth)
    {
        /*lint -e534*/
        LogPrint("\r\nPsRegRcvAppOmRegStartReq:Req Msg len err!\r\n");
        /*lint +e534*/
        PsRegSndOmAppRegModCnf(ID_APP_OM_REG_START_CNF, PS_REG_MSG_LEN_ERR, &stOmAppRegCnf);
        return;
    }


    /* 清空工具下发请求上报地址 */
    /*lint -e534*/
    VOS_MemSet(g_astPsRegReqAddr, 0, sizeof(g_astPsRegReqAddr));
    /*lint +e534*/

    /* 工具下发配置 */
    for (i=0; i< pRcvMsgHead->ulSysModeNum; i++)
    {
        /* 取出每包消息 */
        pRcvMsg = (APP_OM_REG_START_MODE_STRU*)(pRcvMsgHead->aucValue + ulMsgLen);

        /* 消息包偏移 */
        ulMsgLen += pRcvMsg->ulLenth + sizeof(VOS_UINT32);

        ulRest = PsRegRcvAppOmRegConfig((VOS_VOID*)pRcvMsg);
        if(VOS_OK != ulRest)
        {
            PsRegSndOmAppRegModCnf(ID_APP_OM_REG_START_CNF, ulRest, &stOmAppRegCnf);
            return ;
        }
    }

    /* 恢复寄存器上报 */
    g_PsRegRptContrl.bRptEnableStatus = VOS_TRUE;

    /* 给工具回复消息 */
    stOmAppRegCnf.ulSysModeNum = pRcvMsgHead->ulSysModeNum;
    stOmAppRegCnf.ulWbbpAddr   = (VOS_UINT32)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_WBBP);
    stOmAppRegCnf.ulGbbpAddr   = (VOS_UINT32)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_GBBP);
    PsRegSndOmAppRegModCnf(ID_APP_OM_REG_START_CNF, PS_REG_OK, &stOmAppRegCnf);

    return;
}
#endif

#if (FEATURE_GUC_BBP_TRIG == FEATURE_ON)
/*****************************************************************************
 函 数 名  : PsRegSndGUCBBPDbgRegCnf
 功能描述  : 回复工具维测信息
 输入参数  : VOS_UINT16                     usTransPrimId
             VOS_UINT32                     ulResult,
             APP_OM_GUC_REGLIST_CNF_STRU   *pstOmAppRegCnf
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月22日
    作    者   : S00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PsRegSndGUCBBPDbgRegCnf(
    VOS_UINT16                          usTransPrimId,
    VOS_UINT32                          ulResult,
    VOS_VOID                           *pstOmAppRegCnf)
{
    APP_OM_GUC_REGLIST_CNF_STRU        *pstAppTransCnf;
    VOS_UINT32                          ulTotalLen;
    DIAG_TRANS_IND_STRU                 stDiagTransMsg;

    ulTotalLen = PS_GUCBBP_TRIG_NUM + 2 * sizeof(VOS_UINT32);
    pstAppTransCnf = (APP_OM_GUC_REGLIST_CNF_STRU *)VOS_MemAlloc(WUEPS_PID_REG, DYNAMIC_MEM_PT,
                                      ulTotalLen);
    if (VOS_NULL_PTR == pstAppTransCnf)
    {
        PS_LOG(WUEPS_PID_REG, 0, LOG_LEVEL_ERROR, "Error: Alloc msg ID_APP_OM_REGLIST_CFG_CNF fail!");
        return;
    }

    pstAppTransCnf->ulErrCode = ulResult;
    /*lint -e534 -e419*/
    VOS_MemCpy((VOS_VOID*)pstAppTransCnf->aucAddr, (VOS_VOID*)pstOmAppRegCnf, PS_GUCBBP_TRIG_NUM + sizeof(VOS_UINT32));
    /*lint +e534 +e419*/

    stDiagTransMsg.ulModule = DIAG_GEN_MODULE_EX(DIAG_MODEM_0, DIAG_MODE_COMM, DIAG_MSG_TYPE_BBP);
    stDiagTransMsg.ulPid    = WUEPS_PID_REG;
    stDiagTransMsg.ulMsgId  = usTransPrimId;
    stDiagTransMsg.ulLength = ulTotalLen;
    stDiagTransMsg.pData    = (VOS_VOID *)pstAppTransCnf;

    if (VOS_OK != DIAG_TransReport_Ex(&stDiagTransMsg))
    {
        PS_LOG(WUEPS_PID_REG, 0, LOG_LEVEL_ERROR, "Error: Send msg ID_APP_OM_REGLIST_CFG_CNF fail!");
    }
    else
    {
        PS_LOG(WUEPS_PID_REG, 0, LOG_LEVEL_INFO, "Info: Send msg ID_APP_OM_REGLIST_CFG_CNF success!");
    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_REG, pstAppTransCnf);
    /*lint +e534*/

    return ;
}

/*****************************************************************************
 函 数 名  : PsRegRcvGUCBBPDbgRegSetReq
 功能描述  : 配置GUB BBP Dbg寄存器列表
 输入参数  : MsgBlock *pRcvMsg
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月22日
    作    者   : S00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  PsRegRcvGUCBBPDbgRegSetReq( MsgBlock *pRcvMsg )
{
    APP_OM_GUC_REGLIST_REQ_STRU        *pRcvMsgHead = (APP_OM_GUC_REGLIST_REQ_STRU*)pRcvMsg;
    APP_OM_GUC_REGLIST_INFO_STRU       *pRegListInfo;
    VOS_UINT32                          ulIndex = 0;
    VOS_UINT32                          ulRegValue;
    VOS_UINT32                          ulRegNum = 0;
    MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_BUTT;
    PS_REG_BBP_TRIG_MODE_ENUM_UINT16    enMode = PS_REG_BBP_TRIG_MODE_BUTT;
    VOS_UINT32                          ulAddr = 0;
    VOS_UINT32                          ulLen = 0;
    VOS_UINT32                          i,j;
    VOS_UINT32                          ulBBPListBaseAddr = DBG_TRIG_TRACE_ADDR_RAM_ADDR;

    /* 配置CLK */
    HPA_Write32RegMask(BBPSCTRL_COM_CLK_EN_ADDR,    (VOS_UINT32)REG_BIT_N(15));
    HPA_Write32RegMask(BBPSCTRL_COM_SRST_DIS_ADDR,  (VOS_UINT32)REG_BIT_N(15));

    /* 消息长度检查 */
    pRegListInfo = (APP_OM_GUC_REGLIST_INFO_STRU *)pRcvMsgHead->aucValue;

    /* 根据reg list构建寄存器列表 */
    for (ulIndex = 0; ulIndex < pRegListInfo->ulRegNum; ulIndex++)
    {
        ulRegValue  = pRegListInfo->aulRegAddr[ulIndex];

        switch(ulRegValue)
        {
            case PS_GUCBBP_TRIG_HEAD:
                ulIndex++;
                /*lint -e661*/
                ulRegValue  = pRegListInfo->aulRegAddr[ulIndex];
                /*lint +e661*/

                enModemId   = ulRegValue >> 16;
                enMode      = ulRegValue & 0x0000FFFF;

                if ((MODEM_ID_BUTT <= enModemId)
                    || (PS_REG_BBP_TRIG_MODE_BUTT <= enMode))
                {
                    PsRegSndGUCBBPDbgRegCnf(ID_APP_OM_REGLIST_CFG_CNF, PS_REG_REGLIST_ERR, pRcvMsgHead->aucValue);

                    return;
                }

                ulRegNum    = 0;

                g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[enModemId][enMode].ulGUCBBPTrigEnable   = VOS_TRUE;
                break;

            case PS_GUCBBP_TRIG_END:

                if ((MODEM_ID_BUTT <= enModemId)
                    || (PS_REG_BBP_TRIG_MODE_BUTT <= enMode))
                {
                    PsRegSndGUCBBPDbgRegCnf(ID_APP_OM_REGLIST_CFG_CNF, PS_REG_REGLIST_ERR, pRcvMsgHead->aucValue);

                    return;
                }

                g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[enModemId][enMode].ulGUCBBPTrigNumber   = ulRegNum;

                enModemId   = MODEM_ID_BUTT;
                enMode      = PS_REG_BBP_TRIG_MODE_BUTT;

                ulRegNum    = 0xFFFFFFFF;
                break;

            default:
                if ((MODEM_ID_BUTT <= enModemId)
                    || (PS_REG_BBP_TRIG_MODE_BUTT <= enMode)
                    || (0xFFFFFFFF == ulRegNum))
                {
                    PsRegSndGUCBBPDbgRegCnf(ID_APP_OM_REGLIST_CFG_CNF, PS_REG_REGLIST_ERR, pRcvMsgHead->aucValue);

                    return;
                }
                else
                {
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[enModemId][enMode].ulGUCBBPTrigList[ulRegNum] = ulRegValue;
                    ulRegNum++;
                }
                break;
        }

    }

    for (i = 0; i < MODEM_ID_BUTT; i++)
    {
        for (j = 0; j < PS_REG_BBP_TRIG_MODE_BUTT; j++)
        {
            if (VOS_TRUE == g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[i][j].ulGUCBBPTrigEnable)
            {
                /* 将该模式的寄存器信息配置到BBP TRACE RAM中 */
                for (ulRegNum = 0; ulRegNum < g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[i][j].ulGUCBBPTrigNumber; ulRegNum++)
                {
                    HPA_Write32Reg(ulBBPListBaseAddr, g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[i][j].ulGUCBBPTrigList[ulRegNum]);
                    ulBBPListBaseAddr += 4;
                }

                /* 配置模式的CFG寄存器内容，包含GUC模式基地址信息，功能使能 */
                ulRegValue  = ((g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[i][j].ulGUCBBPTrigBaseAddr >> 12 ) & 0x000FFF00);
                HPA_Write32Reg(g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[i][j].ulGUCBBPTrigCFGReg, ulRegValue | 0x1);

                /* 配置模式的INFO寄存器内容，包含BBP TRACE RAM基地址信息，功能使能 */
                ulAddr  &= 0x1FF;
                ulLen   = (g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[i][j].ulGUCBBPTrigNumber << 12) & 0x1FF000;

                HPA_Write32Reg(g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[i][j].ulGUCBBPTrigInfoReg, ulAddr | ulLen);

                ulAddr  += (sizeof(VOS_UINT32)*g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[i][j].ulGUCBBPTrigNumber);
            }
        }
    }

    PsRegSndGUCBBPDbgRegCnf(ID_APP_OM_REGLIST_CFG_CNF, PS_REG_OK, pRcvMsgHead->aucValue);

    return;
}

/*****************************************************************************
 函 数 名  : PsRegGUCBBPDbgIsAwake
 功能描述  : 查询当前模式是否醒着
 输入参数  : MODEM_ID_ENUM_UINT16 enModemId
             VOS_RATMODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月22日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PsRegGUCBBPDbgIsAwake(PS_REG_BBP_TRIG_MODE_ENUM_UINT16    enPsRegType)
{
    VOS_RATMODE_ENUM_UINT32   enMode = VOS_RATMODE_WCDMA;

    switch (enPsRegType)
    {
        case PS_REG_BBP_TRIG_MODE_GSM:
            enMode = VOS_RATMODE_GSM;
            break;

        case PS_REG_BBP_TRIG_MODE_WCDMA:
            enMode = VOS_RATMODE_WCDMA;
            break;

        case PS_REG_BBP_TRIG_MODE_CDMA:
            enMode = VOS_RATMODE_1X;
            break;

        default:
            return VOS_FALSE;
    }

    return SLEEP_IsAwake(enMode);
}

/*****************************************************************************
 函 数 名  : PsRegRcvGUCBBPDbgStartReq
 功能描述  : 使能GUB BBP Dbg功能
 输入参数  : MsgBlock *pRcvMsg
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月22日
    作    者   : S00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  PsRegRcvGUCBBPDbgStartReq( MsgBlock *pRcvMsg )
{
    APP_OM_BBPTRIG_CFG_REQ_STRU        *pRcvMsgHead = (APP_OM_BBPTRIG_CFG_REQ_STRU*)pRcvMsg;
    PS_REG_BBPTRIG_CFG_INFO_STRU       *pstInfo;
    VOS_UINT32                          i;
    VOS_UINT16                          j;

    /* 确认寄存器列表模式 */
    pstInfo = (PS_REG_BBPTRIG_CFG_INFO_STRU *)pRcvMsgHead->aucValue;

    for (i = 0; i < MODEM_ID_BUTT; i++)
    {
        for (j = 0; j < PS_REG_BBP_TRIG_MODE_BUTT; j++)
        {
            g_stPsRegGUCBBPDbgState.aulValue[i][j]  = pstInfo->aulValue[i][j];

            if (VOS_TRUE == g_stPsRegGUCBBPDbgState.aulValue[i][j])
            {
                /* 确认当前模式是上电态，则使能寄存器捕获功能 */
                if (VOS_TRUE == PsRegGUCBBPDbgIsAwake(j))
                {
                    HPA_Write32RegMask(g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[i][j].ulGUCBBPTrigCFGReg, 0x10);
                }
                else
                {
                    g_ulPsRegGUCBBPDbgSleepCount++;
                }
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PsRegGUCBBPDbgGetState
 功能描述  : 查询当前模式是否打开BBP Dbg功能
 输入参数  : MODEM_ID_ENUM_UINT16 enModemId
             VOS_RATMODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月22日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PsRegGUCBBPDbgGetState( MODEM_ID_ENUM_UINT16 enModemId, VOS_RATMODE_ENUM_UINT32 enMode )
{
    PS_REG_BBP_TRIG_MODE_ENUM_UINT16    enPsRegType;

    if (enModemId >= MODEM_ID_BUTT || enMode >= VOS_RATMODE_BUTT)
    {
        return VOS_ERR;
    }

    switch (enMode)
    {
        case VOS_RATMODE_GSM:
            enPsRegType = PS_REG_BBP_TRIG_MODE_GSM;
            break;
        case VOS_RATMODE_WCDMA:
            enPsRegType = PS_REG_BBP_TRIG_MODE_WCDMA;
            break;
        case VOS_RATMODE_1X:
        case VOS_RATMODE_HRPD:
            /*需要投票*/
            enPsRegType = PS_REG_BBP_TRIG_MODE_CDMA;
            break;
        default:
            return VOS_ERR;
    }

    return g_stPsRegGUCBBPDbgState.aulValue[enModemId][enPsRegType];
}

/*****************************************************************************
 函 数 名  : PsRegGUCBBPDbgEnable
 功能描述  : 使能当前模式是否打开BBP Dbg功能
 输入参数  : MODEM_ID_ENUM_UINT16 enModemId
             VOS_RATMODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月22日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PsRegGUCBBPDbgEnable(MODEM_ID_ENUM_UINT16 enModemId, VOS_RATMODE_ENUM_UINT32 enMode)
{
    PS_REG_BBP_TRIG_MODE_ENUM_UINT16    enPsRegType;

    if (enModemId >= MODEM_ID_BUTT || enMode >= VOS_RATMODE_BUTT)
    {
        return;
    }

    switch (enMode)
    {
        case VOS_RATMODE_GSM:
            enPsRegType = PS_REG_BBP_TRIG_MODE_GSM;
            break;
        case VOS_RATMODE_WCDMA:
            enPsRegType = PS_REG_BBP_TRIG_MODE_WCDMA;
            break;
        case VOS_RATMODE_1X:
        case VOS_RATMODE_HRPD:
            /*需要投票*/
            enPsRegType = PS_REG_BBP_TRIG_MODE_CDMA;
            break;
        default:
            return;
    }

    if (VOS_TRUE == g_stPsRegGUCBBPDbgState.aulValue[enModemId][enPsRegType])
    {
        HPA_Write32RegMask(g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[enModemId][enPsRegType].ulGUCBBPTrigCFGReg, 0x10);
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PsRegGUCBBPDbgDisable
 功能描述  : 去使能当前模式是否打开BBP Dbg功能
 输入参数  : MODEM_ID_ENUM_UINT16 enModemId
             VOS_RATMODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月22日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PsRegGUCBBPDbgDisable(MODEM_ID_ENUM_UINT16 enModemId, VOS_RATMODE_ENUM_UINT32 enMode)
{
    PS_REG_BBP_TRIG_MODE_ENUM_UINT16    enPsRegType;

    if (enModemId >= MODEM_ID_BUTT || enMode >= VOS_RATMODE_BUTT)
    {
        return;
    }

    switch (enMode)
    {
        case VOS_RATMODE_GSM:
            enPsRegType = PS_REG_BBP_TRIG_MODE_GSM;
            break;
        case VOS_RATMODE_WCDMA:
            enPsRegType = PS_REG_BBP_TRIG_MODE_WCDMA;
            break;
        case VOS_RATMODE_1X:
        case VOS_RATMODE_HRPD:
            /*需要投票*/
            enPsRegType = PS_REG_BBP_TRIG_MODE_CDMA;
            break;
        default:
            return;
    }

    if (VOS_TRUE == g_stPsRegGUCBBPDbgState.aulValue[enModemId][enPsRegType])
    {
        HPA_Clear32RegMask(g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[enModemId][enPsRegType].ulGUCBBPTrigCFGReg, 0x10);
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PsRegGUCBBPDbgBackup
 功能描述  : 下电时对SRAM进行备份
 输入参数  : MODEM_ID_ENUM_UINT16 enModemId
             VOS_RATMODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月22日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PsRegGUCBBPDbgBackup(MODEM_ID_ENUM_UINT16 enModemId, VOS_RATMODE_ENUM_UINT32 enMode)
{
    VOS_UINT32                          ulBBPListCfgReg1Addr = DBG_TRIG_W1_CONFIG1_ADDR;
    VOS_UINT32                          ulBBPListCfgReg2Addr = DBG_TRIG_OVERTIME_CLR_ADDR;
    VOS_UINT32                          ulRegNum = 0;

    /* 备份CLK */
    g_ulPsRegGUCBBPDbgClkValue  = HPA_Read32Reg(BBPSCTRL_COM_CLK_STATUS_ADDR);
    g_ulPsRegGUCBBPDbgSrstValue = HPA_Read32Reg(BBPSCTRL_COM_SRST_STATUS_ADDR);

    /* 备份CFG */
    for (ulRegNum = 0; ulRegNum < PS_GUCBBP_CFG_REG_NUM1; ulRegNum++)
    {
        g_ulPsRegGUCBBPDbgCfg1[ulRegNum] = HPA_Read32Reg(ulBBPListCfgReg1Addr);
        ulBBPListCfgReg1Addr += 4;
    }

    for (ulRegNum = 0; ulRegNum < PS_GUCBBP_CFG_REG_NUM2; ulRegNum++)
    {
        g_ulPsRegGUCBBPDbgCfg2[ulRegNum] = HPA_Read32Reg(ulBBPListCfgReg2Addr);
        ulBBPListCfgReg2Addr += 4;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PsRegGUCBBPDbgBackup
 功能描述  : PsRegGUCBBPDbgRestore
 输入参数  : MODEM_ID_ENUM_UINT16 enModemId
             VOS_RATMODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月22日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PsRegGUCBBPDbgRestore(MODEM_ID_ENUM_UINT16 enModemId, VOS_RATMODE_ENUM_UINT32 enMode)
{
    VOS_UINT32                          ulBBPListBaseAddr    = DBG_TRIG_TRACE_ADDR_RAM_ADDR;
    VOS_UINT32                          ulBBPListCfgReg1Addr = DBG_TRIG_W1_CONFIG1_ADDR;
    VOS_UINT32                          ulBBPListCfgReg2Addr = DBG_TRIG_OVERTIME_CLR_ADDR;
    VOS_UINT32                          ulRegNum = 0;
    VOS_UINT32                          i,j;

    /* 恢复CLK */
    HPA_Write32RegMask(BBPSCTRL_COM_CLK_EN_ADDR,    g_ulPsRegGUCBBPDbgClkValue & (VOS_UINT32)REG_BIT_N(15));
    HPA_Write32RegMask(BBPSCTRL_COM_SRST_DIS_ADDR,  ~(g_ulPsRegGUCBBPDbgSrstValue & (VOS_UINT32)REG_BIT_N(15)) & (VOS_UINT32)REG_BIT_N(15));

    /* 恢复CFG */
    for (ulRegNum = 0; ulRegNum < PS_GUCBBP_CFG_REG_NUM1; ulRegNum++)
    {
        HPA_Write32Reg(ulBBPListCfgReg1Addr, g_ulPsRegGUCBBPDbgCfg1[ulRegNum]);
        ulBBPListCfgReg1Addr += 4;
    }

    for (ulRegNum = 0; ulRegNum < PS_GUCBBP_CFG_REG_NUM2; ulRegNum++)
    {
        HPA_Write32Reg(ulBBPListCfgReg2Addr, g_ulPsRegGUCBBPDbgCfg2[ulRegNum]);
        ulBBPListCfgReg2Addr += 4;
    }

    /* 恢复SRAM */
    for (i = 0; i < MODEM_ID_BUTT; i++)
    {
        for (j = 0; j < PS_REG_BBP_TRIG_MODE_BUTT; j++)
        {
            if (VOS_TRUE == g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[i][j].ulGUCBBPTrigEnable)
            {
                /* 将该模式的寄存器信息配置到BBP TRACE RAM中 */
                for (ulRegNum = 0; ulRegNum < g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[i][j].ulGUCBBPTrigNumber; ulRegNum++)
                {
                    HPA_Write32Reg(ulBBPListBaseAddr, g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[i][j].ulGUCBBPTrigList[ulRegNum]);
                    ulBBPListBaseAddr += 4;
                }
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PsRegGUCBBPInit
 功能描述  : GUC BBP TRIG功能初始化配置
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月26日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PsRegGUCBBPInit( VOS_VOID )
{
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigEnable      = VOS_FALSE;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigNumber      = 0;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigCFGReg      = DBG_TRIG_W1_CONFIG1_ADDR;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigInfoReg     = DBG_TRIG_W1_CONFIG2_ADDR;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigBaseAddr    = SOC_BBP_WCDMA_BASE_ADDR;

    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigEnable        = VOS_FALSE;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigNumber        = 0;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigCFGReg        = DBG_TRIG_G1_CONFIG1_ADDR;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigInfoReg       = DBG_TRIG_G1_CONFIG2_ADDR;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigBaseAddr      = SOC_BBP_GSM0_BASE_ADDR;

    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigEnable       = VOS_FALSE;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigNumber       = 0;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigCFGReg       = DBG_TRIG_C1_CONFIG1_ADDR;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigInfoReg      = DBG_TRIG_C1_CONFIG2_ADDR;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigBaseAddr     = SOC_BBP_CDMA_BASE_ADDR;

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )

    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigEnable      = VOS_FALSE;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigNumber      = 0;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigCFGReg      = DBG_TRIG_W2_CONFIG1_ADDR;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigInfoReg     = DBG_TRIG_W2_CONFIG2_ADDR;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigBaseAddr    = 0;

    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigEnable        = VOS_FALSE;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigNumber        = 0;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigCFGReg        = DBG_TRIG_G2_CONFIG1_ADDR;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigInfoReg       = DBG_TRIG_G2_CONFIG2_ADDR;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigBaseAddr      = SOC_BBP_GSM1_BASE_ADDR;

    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigEnable       = VOS_FALSE;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigNumber       = 0;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigCFGReg       = DBG_TRIG_C2_CONFIG1_ADDR;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigInfoReg      = DBG_TRIG_C2_CONFIG2_ADDR;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigBaseAddr     = 0;

#endif

    (VOS_VOID)mdrv_pm_register_sleep_ops((VOS_UINT8*)"PsRegGUCBBPTrig", (PWC_SLEEP_FUNCPTR)PsRegGUCBBPDbgBackup, (PWC_SLEEP_FUNCPTR)PsRegGUCBBPDbgRestore);

    return;
}

VOS_VOID PsRegGUCBBPShowTrigInfo(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("\r\nThe DBG_TRIG_W1_CONFIG1_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigCFGReg      );
    vos_printf("\r\nThe DBG_TRIG_W1_CONFIG2_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigInfoReg     );
    vos_printf("\r\nThe SOC_BBP_WCDMA1_BASE_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigBaseAddr    );

    vos_printf("\r\nThe DBG_TRIG_G1_CONFIG1_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigCFGReg        );
    vos_printf("\r\nThe DBG_TRIG_G1_CONFIG2_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigInfoReg       );
    vos_printf("\r\nThe SOC_BBP_GSM1_BASE_ADDR           is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigBaseAddr      );

    vos_printf("\r\nThe DBG_TRIG_C1_CONFIG1_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigCFGReg       );
    vos_printf("\r\nThe DBG_TRIG_C1_CONFIG2_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigInfoReg      );
    vos_printf("\r\nThe SOC_BBP_CDMA1_BASE_ADDR          is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigBaseAddr     );

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )

    vos_printf("\r\nThe DBG_TRIG_W2_CONFIG1_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigCFGReg      );
    vos_printf("\r\nThe DBG_TRIG_W2_CONFIG2_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigInfoReg     );
    vos_printf("\r\nThe SOC_BBP_WCDMA2_BASE_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigBaseAddr    );

     vos_printf("\r\nThe DBG_TRIG_G2_CONFIG1_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigCFGReg        );
    vos_printf("\r\nThe DBG_TRIG_G2_CONFIG2_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigInfoReg       );
    vos_printf("\r\nThe SOC_BBP_GSM2_BASE_ADDR           is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigBaseAddr      );

    vos_printf("\r\nThe DBG_TRIG_C2_CONFIG1_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigCFGReg       );
    vos_printf("\r\nThe DBG_TRIG_C2_CONFIG2_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigInfoReg      );
    vos_printf("\r\nThe SOC_BBP_CDMA2_BASE_ADDR          is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigBaseAddr     );

#endif
    /*lint +e534*/
}
#endif

/******************************************************************************
 Prototype      : Reg_MsgProc
 Description    : 寄存器功能消息处理函数
 Input          : pRcvMsg - 消息体

 Output         : VOID
 Return Value   : VOID

 History        : ---
  1.Date        : 2010-8-24
    Author      : g47350
    Modification: Created function
******************************************************************************/
VOS_VOID  Reg_MsgProc(MsgBlock *pRcvMsg)
{
    APP_OM_REG_REQ_MSG_STRU            *pstMsg;

    pstMsg = (APP_OM_REG_REQ_MSG_STRU *)pRcvMsg;

    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_2, pstMsg->ulSenderPid, WUEPS_PID_REG, pstMsg->ulMsgId);

    switch (pstMsg->ulMsgId)
    {
#if (FEATURE_GUC_BBP_TRIG == FEATURE_OFF)
        case ID_APP_OM_REG_START_REQ:
            Reg_CnfMsgProc(pstMsg, ID_APP_OM_REG_START_REQ);
            PsRegRcvAppOmRegStartReq(pRcvMsg);
            break;

        case ID_APP_OM_REG_DIFF_REQ:
            Reg_CnfMsgProc(pstMsg, ID_APP_OM_REG_DIFF_REQ);
            PsRegRcvAppOmRegDiffSetNumReq(pRcvMsg);
            break;

        case ID_APP_OM_REG_STOP_REQ:
            Reg_CnfMsgProc(pstMsg, ID_APP_OM_REG_STOP_REQ);
            PsRegRcvAppOmRegStopReq(pRcvMsg);
            break;
#endif

#if (FEATURE_GUC_BBP_TRIG == FEATURE_ON)
        case ID_APP_OM_REGLIST_CFG_REQ:;
            Reg_CnfMsgProc(pstMsg, ID_APP_OM_REGLIST_CFG_REQ);
            PsRegRcvGUCBBPDbgRegSetReq(pRcvMsg);
            break;

        case ID_APP_OM_BBPTRIG_CFG_REQ:
            Reg_CnfMsgProc(pstMsg, ID_APP_OM_BBPTRIG_CFG_REQ);
            PsRegRcvGUCBBPDbgStartReq(pRcvMsg);
            break;
#endif

        default: /* 无效的消息ID */
            PS_LOG2(WUEPS_PID_REG, 0, LOG_LEVEL_WARNING, "not expected msg! ulSenderPid<1>,enMsgName<2>",(VOS_INT32)(pRcvMsg->ulSenderPid),(VOS_INT32)(*((VOS_UINT32 *)((VOS_UINT8 *)(pRcvMsg) + VOS_MSG_HEAD_LENGTH))));
            break;
    }

    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_2);
}

/******************************************************************************
 Prototype      : Reg_CnfMsgProc
 Description    : 寄存器功能消息回复处理函数
 Input          : pstRcvMsg - 消息体
                  ulMsgId - 消息ID

 Output         : VOID
 Return Value   : VOID

 History        : ---
  1.Date        : 2015-6-19
    Author      : h00300778
    Modification: Created function
******************************************************************************/
VOS_VOID Reg_CnfMsgProc(
    APP_OM_REG_REQ_MSG_STRU            *pstRcvMsg,
    VOS_UINT32                          ulMsgId)
{
    APP_OM_REG_CNF_MSG_STRU            *pstCnfMsg;

    pstCnfMsg = (APP_OM_REG_CNF_MSG_STRU *)VOS_AllocMsg(WUEPS_PID_REG, sizeof(APP_OM_REG_CNF_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstCnfMsg)
    {
        return;
    }

    /* PC侧透明消息下发的参数原样带回 */
    pstCnfMsg->usOriginalId = pstRcvMsg->usOriginalId;
    pstCnfMsg->usTerminalId = pstRcvMsg->usTerminalId;
    pstCnfMsg->ulTimeStamp  = pstRcvMsg->ulTimeStamp;
    pstCnfMsg->ulSN         = pstRcvMsg->ulSN;

    /* 填充消息内容 */
    pstCnfMsg->ulReceiverPid= MSP_PID_DIAG_APP_AGENT;
    pstCnfMsg->ulMsgId      = ulMsgId;
    pstCnfMsg->ulRslt       = VOS_OK;

    /*lint -e534*/
    VOS_SendMsg(WUEPS_PID_REG, pstCnfMsg);
    /*lint +e534*/

    return;
}

/******************************************************************************
 Prototype      : WuepsRegPidInit
 Description    : 寄存器功能PID初始化函数
 Input          : pRcvMsg - 消息体

 Output         : VOID
 Return Value   : VOID

 History        : ---
  1.Date        : 2010-8-24
    Author      : g47350
    Modification: Created function
******************************************************************************/
VOS_UINT32 WuepsRegPidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
#if (FEATURE_GUC_BBP_TRIG == FEATURE_OFF)
            if ( VOS_OK != PsRegInit())
            {
                /*lint -e534*/
                vos_printf("WuepsRegPidInit: PsRegInit fail");
                /*lint +e534*/

                return VOS_ERR;
            }

            if ( VOS_OK != VOS_SmCCreate( "REG", 0, VOS_SEMA4_PRIOR | VOS_SEMA4_INVERSION_SAFE, &g_ulRegTransferSem))
            {
                /*lint -e534*/
                vos_printf("WuepsRegPidInit: creat g_ulRegTransferSem Err");
                /*lint +e534*/

                return VOS_ERR;
            }
#endif

#if (FEATURE_GUC_BBP_TRIG == FEATURE_ON)
            PsRegGUCBBPInit();
#endif
            break;

        default:
            break;
    }

    return VOS_OK;
}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

