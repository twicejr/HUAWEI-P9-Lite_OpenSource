/******************************************************************************

                  版权所有 (C), 2001-2013, 华为技术有限公司

 ******************************************************************************
  文 件 名      : ombbplog.c
  版 本 号      : 初稿
  作    者      : 蒋德彬 00174725
  生成日期      : 2012年11月16日
  最近修改      :
  功能描述      : BBP采数与可维可测相关函数实现
  函数列表      :
  修改历史      :
  1.日    期    : 2012年11月16日
    作    者    : 蒋德彬 00174725
    修改内容    : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "SOCPInterface.h"
#include "omprivate.h"
#include "ombbplog.h"
#include "SCMProc.h"
#include "BSP_SOCP_DRV.h"
#include "NvIdList.h"
#include "NVIM_Interface.h"
#include "bbp_wcdma_interface.h"
#include "bbp_comm_interface.h"
#include "bbp_gsm_interface.h"
#include "apmprocess.h"
#include "msp_diag_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif


/*lint -e767 修改人：蒋德彬 */
#define    THIS_FILE_ID        PS_FILE_ID_OM_BBP_LOG_C
/*lint +e767 修改人：蒋德彬 */

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* GU BBP 可维可测上报SOCP 通道配置参数 */
SCM_CODER_SRC_CFG_STRU                  g_astBbpDbgCoderSrcCfg[BBP_DBG_CODER_SRC_NUM]=
{
    {SCM_CHANNEL_UNINIT, SOCP_CODER_SRC_GUBBP1,   SOCP_CODER_DST_OM_IND,   SOCP_DATA_TYPE_1, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_3, BBP_DBG_CODER_SRC_SIZE, VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR},
    {SCM_CHANNEL_UNINIT, SOCP_CODER_SRC_GUBBP2,   SOCP_CODER_DST_OM_IND,   SOCP_DATA_TYPE_1, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_3, BBP_DBG_CODER_SRC_SIZE, VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR}
};

/* 记录BBP 可维可测上报初始化的调试信息 */
BBP_DBG_ERR_INFO_STRU                   g_stBbpDbgErrInfo;

/* 记录BBP 可维可测上报的全局信息 */
BBP_DBG_INFO_STRU                       g_stBbpDbgInfo;

/* 记录BBP 数采的调试信息 */
BBP_DUMP_ERR_INFO_STRU                  g_stBbpDumpErrInfo;

/* 记录BBP数采的全局信息 */
BBP_DUMP_INFO_STRU                      g_stBbpDumpInfo;

/* 保留信息地址，用于在数采中断中发送消息 */
MsgBlock*                               g_pstBbpDumpMsg         = VOS_NULL_PTR;

/* 保留信息地址，用于在可维可测中断中发送消息 */
MsgBlock*                               g_pstBbpDbgMsg          = VOS_NULL_PTR;

/* 保存EDMA循环链表头指针 */
BALONG_DMA_CB_S                        *g_pstBbpCycBufHead       = VOS_NULL_PTR;

/*控制BBP可维可测的计数信号量*/
VOS_SEM                                 g_ulBbpDbgSem = VOS_NULL;

/*****************************************************************************
 3  函数声明
*****************************************************************************/

/*****************************************************************************
 4 消息处理函数映射表
*****************************************************************************/


/*****************************************************************************
  5 函数实现
*****************************************************************************/
/*****************************************************************************
* 函 数 名  : Om_CheckDumpLen
*
* 功能描述  : 检查SDT下发的数采长度是否符合要求
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值  : 成功:BBP_DUMP_OK  失败:对应的错误码
  1.日    期   : 2012年11月13日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_UINT32 Om_CheckDumpLen(VOS_UINT32 ulLen)
{
    VOS_UINT32                          ulSizeTemp;

    /* 判断数采长度是否小于最小长度 */
    if (ulLen < BBP_DUMP_MIN_LEN)
    {
        return BBP_DUMP_MEM_SMALL;
    }

    /* 判断是否大于2G */
    if (ulLen > BBP_DUMP_MAX_LEN)
    {
        return BBP_DUMP_MEM_BIG;
    }

    /* 判断数采长度是否是32KB的整数倍 */
    ulSizeTemp = ulLen % BBP_DUMP_UNIT_LEN;
    if (0 != ulSizeTemp)
    {
        return BBP_DUMP_MEM_NOT_32KB;
    }

    return BBP_DUMP_OK;
}

/*****************************************************************************
* 函 数 名  : Om_SendEdmaErrToPc
*
* 功能描述  : CCPU OM收到EDMA错误消息后通知PC侧
*
* 输入参数  : pstAppToOmMsg : 消息包指针
*             usReturnPrimId: 消息回复ID
*
* 输出参数  : 无
*
* 返 回 值  : 成功:VOS_OK   失败:VOS_ERR
  1.日    期   : 2012年11月13日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_UINT32 Om_SendEdmaErrToPc(
    BBP_EDMA_ERR_STRU                  *pstEdmaErr,
    VOS_UINT16                          usReturnPrimId)
{
    DIAG_TRANS_IND_STRU                 stDiagTransMsg;

    stDiagTransMsg.ulModule = DIAG_GEN_MODULE_EX(DIAG_MODEM_0, DIAG_MODE_COMM, DIAG_MSG_TYPE_BBP);
    stDiagTransMsg.ulPid    = CCPU_PID_PAM_OM;
    stDiagTransMsg.ulMsgId  = usReturnPrimId;
    stDiagTransMsg.ulLength = sizeof(OM_APP_BBP_EDMA_ERR_ENUM_U16);
    stDiagTransMsg.pData    = (VOS_VOID *)&pstEdmaErr->enEdmaErr;

    /*lint -e534*/
    (VOS_VOID)DIAG_TransReport_Ex(&stDiagTransMsg);
    /*lint +e534*/
    return VOS_OK;
}


/*****************************************************************************
* 函 数 名  : Om_CloseBbpDump
*
* 功能描述  : 关闭BBP数采
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  :
  1.日    期   : 2012年11月13日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_VOID Om_CloseBbpDump(VOS_VOID)
{
    /* 清启动数据采集 */
    OM_BBP_REG_SETBITS(WBBP_DUMP_START_W_ADDR, 0, 1, 0x0);

    /* 软件强制停止数据采集 */
    OM_BBP_REG_SETBITS(WBBP_DUMP_STOP_W_ADDR, 0, 1, 0x1);
}

/*****************************************************************************
* 函 数 名  : Om_DumpEdmaCallBack
*
* 功能描述  : BBP 数采注册给EDMA 回调函数
*
* 输入参数  : ulFlag: 标识中断类型
*             ulChannelArg:暂不用
*
* 输出参数  : 无
*
* 返 回 值  : VOS_OK: 成功  VOS_ERR:失败
  1.日    期   : 2012年11月13日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_UINT32 Om_DumpEdmaCallBack(VOS_UINT32 ulChannelArg, VOS_UINT32 ulFlag)
{
    APP_BBP_DUMP_REQ_MSG_STRU          *pstPcMsg;
    BBP_EDMA_ERR_STRU                  *pstEdmaErr;

    /*lint -e534*/
    LogPrint("Om_DumpEdmaCallBack: Start\r\n");
    /*lint +e534*/

    /* 关闭数采 */
    /*lint -e522*/
    Om_CloseBbpDump();
    /*lint +e522*/

    if (VOS_NULL_PTR == g_pstBbpDumpMsg)
    {
        /*lint -e534*/
        LogPrint("Om_DumpEdmaCallBack: g_pstBbpDumpMsg is NULL\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    pstPcMsg = (APP_BBP_DUMP_REQ_MSG_STRU *)g_pstBbpDumpMsg;

    /* DMA传输完成中断 */
    if ( BALONG_DMA_INT_DONE == ulFlag)
    {
        g_stBbpDumpInfo.usDUMPDone++;
        /* 模拟工具发送消息通知结束数采 */
        pstPcMsg->ulMsgName = APP_OM_BBP_DUMP_END_REQ;
        pstPcMsg->ulSenderPid   = MSP_PID_DIAG_APP_AGENT;

        (VOS_VOID)VOS_SendMsg(CCPU_PID_PAM_OM, g_pstBbpDumpMsg);
    }
    else /* EDMA错误中断 */
    {
        pstEdmaErr = (BBP_EDMA_ERR_STRU *)pstPcMsg->aucValue;

        pstPcMsg->ulMsgName     = APP_OM_BBP_EDMA_ERR_REQ;
        pstPcMsg->ulSenderPid   = MSP_PID_DIAG_APP_AGENT;

        /* 标识是可维可测产生的EDMA错误中断 */
        pstEdmaErr->enEdmaErr   = OM_BBP_DUMP_EDMA_ERR;

        /* 模拟PC给UE发送消息 */
        (VOS_VOID)VOS_SendMsg(CCPU_PID_PAM_OM, g_pstBbpDumpMsg);
        g_stBbpDumpErrInfo.usEdmaErrCode = (VOS_UINT16)ulFlag;
    }

    g_stBbpDumpInfo.usDUMPStatus = OM_BBP_STOP;

    return VOS_OK;
}

/*****************************************************************************
* 函 数 名  : Om_BbpDumpEdmaInit
*
* 功能描述  : 初始化BBP 数采的EDMA通道
*
* 输入参数  : 无
*6
* 输出参数  : 无
*
* 返 回 值  : VOS_OK: 成功  VOS_ERR:失败
  1.日    期   : 2012年11月13日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_UINT32 Om_BbpDumpEdmaInit(VOS_VOID)
{
    VOS_INT                             lRet;
    OM_BBP_DUMP_ENABLE_STRU             stEnableFlag;

    stEnableFlag.ulEnable = OM_BBP_DUMP_DISABLE;

    /*读NV项*/
    if(NV_OK != NV_Read(en_NV_Item_BBP_DUMP_ENABLE,
        (VOS_VOID *)(&stEnableFlag), sizeof(OM_BBP_DUMP_ENABLE_STRU)))
    {
        /*lint -e534*/
        LogPrint("Om_BbpDumpEdmaInit: Read Nv Fail\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    /* 判断是否启动BBP数采 */
    if (OM_BBP_DUMP_DISABLE == stEnableFlag.ulEnable)
    {
        /*lint -e534*/
        LogPrint("Om_BbpDumpEdmaInit: Not Enable BBP DUMP\r\n");
        /*lint +e534*/
        return VOS_OK;
    }

    /*lint -e534*/
    VOS_MemSet(&g_stBbpDumpInfo,    0, sizeof(g_stBbpDumpInfo));
    VOS_MemSet(&g_stBbpDumpErrInfo, 0, sizeof(g_stBbpDumpErrInfo));
    /*lint +e534*/

    /* 调用DRV函数 初始化BBP DUMP使用的EDMA,并注册回调 */
    g_stBbpDumpInfo.lEdmaChanID = mdrv_edma_chan_init(EDMA_BBP_GRIF,
                                    (channel_isr)Om_DumpEdmaCallBack,
                                    VOS_NULL, BBP_DUMP_EDMA_INT);
    if (g_stBbpDumpInfo.lEdmaChanID < 0)
    {
        g_stBbpDumpErrInfo.usInitEdmaErr++;
        return VOS_ERR;
    }

    /* 调用DRV函数配置 EDMA , BBP数采的burst长宽为16 * 32bit */
    lRet = mdrv_edma_chan_config((VOS_UINT32)g_stBbpDumpInfo.lEdmaChanID, BALONG_DMA_P2M, EDMA_TRANS_WIDTH_32, EDMA_BUR_LEN_16);
    if (MDRV_OK != lRet)
    {
        g_stBbpDumpErrInfo.usConfigEdmaErr++;
        return VOS_ERR;
    }

    /* 申请一条保留消息，用于中断中发送 */
    g_pstBbpDumpMsg = (MsgBlock*)VOS_AllocMsg(CCPU_PID_PAM_OM, sizeof(APP_BBP_DUMP_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == g_pstBbpDumpMsg)
    {
        g_stBbpDumpErrInfo.usAllocMsgErr++;
        return VOS_ERR;
    }

    g_pstBbpDumpMsg->ulReceiverPid = CCPU_PID_PAM_OM;

    /* 标记该消息不用释放 */
    /*lint -e534*/
    VOS_ReserveMsg(CCPU_PID_PAM_OM, g_pstBbpDumpMsg);

    LogPrint("Om_BbpDumpEdmaInit: ok!\r\n");
    /*lint +e534*/

    return VOS_OK;

}

/*****************************************************************************
* 函 数 名  : Om_ConfigBbpDumpEdma
*
* 功能描述  : 配置BBP 数采EDMA
*
* 输入参数  : ulLen     : 数采长度
              ulPhyAddr : Dump物理地址
              ulPhySize : Dump大小长度
              enMode    : 模式
*
* 输出参数  : NA
*
* 返 回 值  : 成功:BBP_DUMP_OK  失败:对应的错误码
  1.日    期   : 2012年11月13日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_UINT32 Om_ConfigBbpDumpEdma(VOS_UINT32                ulLen,
                                VOS_UINT32                ulPhyAddr,
                                VOS_UINT32                ulPhySize,
                                OM_BBP_DUMP_MODE_ENUM_U32 enMode)
{
    VOS_INT                             lRet;
    VOS_UINT32                          ulLenByte;

    ulLenByte = ulLen * 1024;
    if(ulPhySize < ulLenByte)
    {
         /*lint -e534*/
         LogPrint1("Om_ConfigBbpDumpEdma: Size Small %d!\r\n", (VOS_INT)ulPhySize);
         /*lint +e534*/
         return BBP_DUMP_MEM_BIG;
    }

    lRet = mdrv_edma_chan_stop((VOS_UINT32)g_stBbpDumpInfo.lEdmaChanID);
    if(MDRV_ERROR == lRet)
    {
        g_stBbpDumpErrInfo.usStopEdmaErr++;
        /*lint -e534*/
        LogPrint("Om_ConfigBbpDumpEdma:Stop Edma Fail\r\n");
        /*lint +e534*/
        return BBP_DUMP_STOP_EDMA_ERR;
    }

#if 0
    if (OM_BBP_DUMP_MODE_W == enMode)
    {
#endif

#if (FEATURE_ON == FEATURE_OM_BBPLOG)
        /* 使能EDMA */
        LogPrint2("Om_ConfigBbpDumpEdma: Enable DMA Address 0x%x Size %d!\r\n", (VOS_INT)ulPhyAddr, (VOS_INT)ulLenByte);
        lRet = mdrv_edma_chan_async_start((VOS_UINT32)g_stBbpDumpInfo.lEdmaChanID, WBBP_DUMP_DMA_RDATA_W_ADDR,
                                           ulPhyAddr, ulLenByte);
#endif

#if 0
    }
    else
    {
        /* 使能EDMA */
        lRet = mdrv_edma_chan_async_start((VOS_UINT32)g_stBbpDumpInfo.lEdmaChanID, GBBP_CPU_GDUMP_FIFO_RD_ADDR_ADDR,
                                           ulPhyAddr, ulLenByte);
    }
#endif

    if (MDRV_OK != lRet)
    {
        g_stBbpDumpErrInfo.usStartEdmaErr++;
        /*lint -e534*/
        LogPrint("Om_ConfigBbpDumpEdma:Start Edma Fail\r\n");
        /*lint +e534*/
        return BBP_DUMP_START_EDMA_ERR;
    }

    return BBP_DUMP_OK;
}



/*****************************************************************************
* 函 数 名  : Om_CheckBbpDumpPara
*
* 功能描述  : Ccpu检查BBP数采参数是否正确
*
* 输入参数  : pstPcMsg : PC下发的配置数采消息
*
*
* 输出参数  : 无
*
* 返 回 值  : 成功:BBP_DUMP_OK/失败:返回对应错误码
  1.日    期   : 2012年11月13日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_UINT32 Om_CheckBbpDumpPara(APP_OM_BBP_DUMP_SET_STRU *pstPcMsg)
{
    VOS_UINT32                          ulResult;

    /* 判断下发的模式是否正确 */
    if (pstPcMsg->enMode >= OM_BBP_DUMP_MODE_BUTT)
    {
        return BBP_DUMP_MODE_ERR;
    }

        /* 检查长度是否符合要求 */
    ulResult = Om_CheckDumpLen(pstPcMsg->ulDataLen);
    if(ulResult != BBP_DUMP_OK)
    {
        /*lint -e534*/
        LogPrint("Om_ConfigBbpDumpEdma: Lenth err!\r\n");
        /*lint +e534*/
        return ulResult;
    }

    return BBP_DUMP_OK;
}

/*****************************************************************************
* 函 数 名  : Om_ConfigBbpDumpReg
*
* 功能描述  : 配置BBP数采寄存器
*
* 输入参数  : pstPcMsg : PC侧下发的配置信息
*
* 输出参数  : 无
*
* 返 回 值  : 无
  1.日    期   : 2012年11月13日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_VOID Om_ConfigBbpDumpReg(APP_OM_BBP_DUMP_SET_STRU *pstPcMsg)
{
#if (FEATURE_ON == FEATURE_OM_BBPLOG)
    /* VOS_UINT32                          ulSizeTemp; */

    /* keep lint happy */
    pstPcMsg = pstPcMsg;

    /* 配置BBP可维可测模式 */
    /*OM_BBP_REG_SETBITS(BBPCOMM_BBP_SYS_1CONTROL_ADDR, 0, 2, pstPcMsg->enMode);*/
    OM_BBP_REG_SETBITS(BBPCOMM_BBP_SYS_1CONTROL_ADDR, 0, 2, OM_BBP_DUMP_MODE_W);

#if 0
    if (OM_BBP_DUMP_MODE_W == pstPcMsg->enMode)
    {
#endif
        /* 先强制关闭BBP数采 */
        OM_BBP_REG_SETBITS(WBBP_DUMP_STOP_W_ADDR, 0, 1, 0x1);

        /* 采数模块总使能，并控制时钟门控，无论哪种模式采数，首先要配置此信号有效 */
        OM_BBP_REG_SETBITS(WBBP_DUMP_EN_W_ADDR, 0, 1, 0x1);

        /* 开启BBP门控时钟寄存器 */
        OM_BBP_REG_SETBITS(WBBP_DUMP_CLKGATE_BYPASS_W_ADDR, 0, 3, 0x07);

        /*采数使能 */
        OM_BBP_WRITE_REG(WBBP_WT_DBG_EN_ADDR, 1);

        /* FIFO清零信号 */
        OM_BBP_REG_SETBITS(WBBP_DUMP_FIFO_CLR_W_ADDR, 0, 1, 0x1);

        /* PC侧下发的数采长度以KB为单位，但配置需要配置32bit的整数倍 */
        /*ulSizeTemp = (pstPcMsg->ulDataLen * 1024) / 4;*/

        /* 采集数据的长度，即需要采集的32bit数据个数 */
        OM_BBP_WRITE_REG(WBBP_DUMP_DATA_LENGTH_W_ADDR, 0);

        /* BBP 选择空口数据的采样位置 */
        OM_BBP_WRITE_REG(WBBP_DBG_AGC_DATA_SEL_ADDR, 0x100);

        /* BBP 采数起始位置 */
        OM_BBP_WRITE_REG(WBBP_DUMP_START_TIME_W_ADDR, 0xffffffff);

        /* 水线深度 */ /* 按照 BBP 建议不配置 */
        /*OM_BBP_REG_SETBITS(WBBP_DUMP_FIFO_WATERMARKER_W_ADDR, 0, 3, 0);)*/

        /* 清数据采集停止寄存器 */
        OM_BBP_REG_SETBITS(WBBP_DUMP_STOP_W_ADDR, 0, 1, 0x0);

        /* 软件启动数据采集 */
        OM_BBP_REG_SETBITS(WBBP_DUMP_START_W_ADDR, 0, 1, 0x1);
#if 0
    }
    else
    {
        /* 先强制关闭BBP数采 */
        OM_BBP_REG_SETBITS(GBBP_CPU_GDUMP_RECV_CONFIG_ADDR, 8, 1, 0x1);

        /* CPU配置异步FIFO清零信号 */
        OM_BBP_REG_SETBITS(GBBP_CPU_GDUMP_RECV_CONFIG_ADDR, 16, 1, 0x1);

        /* FIFO水线深度选择,采样数据源选择,采数模块配置类型选择 */
        OM_BBP_WRITE_REG(GBBP_CPU_GDUMP_GEN_CONFIG_ADDR, pstPcMsg->ulGenConfig);

        /* 选择使用CPU配置接口 */
        OM_BBP_REG_SETBITS(GBBP_CPU_GDUMP_GEN_CONFIG_ADDR, 8, 1, 0x1);

        /* 采数模块总使能 */
        OM_BBP_REG_SETBITS(GBBP_CPU_GDUMP_GEN_CONFIG_ADDR, 31, 1, 0x1);

        /* PC侧下发的数采长度以KB为单位，但配置需要配置32bit的整数倍 */
        ulSizeTemp = (pstPcMsg->ulDataLen * 1024) / 4;

        /* 采集数据的长度，即需要采集的32bit数据个数 */
        OM_BBP_WRITE_REG(GBBP_CPU_GDUMP_LEN_CONFIG_ADDR, ulSizeTemp);

        /* 配启动时刻采数模式下，采数起始位置 */
        OM_BBP_WRITE_REG(GBBP_CPU_GDUMP_SAM_LOW_TIMING_ADDR, pstPcMsg->ulStartLowTimeG);

        /* 可配启动时刻采数模式下，采数起始位置*/
        OM_BBP_WRITE_REG(GBBP_CPU_GDUMP_SAM_HIGH_TIMING_ADDR, pstPcMsg->ulStartHiTimeG);

        /* 启动G 模数采 */
        OM_BBP_REG_SETBITS(GBBP_CPU_GDUMP_RECV_CONFIG_ADDR, 0, 1, 0x1);
    }
#endif

#endif

    /*lint -e534*/
    LogPrint("Om_ConfigBbpDumpReg: config BBP success\r\n");
    /*lint +e534*/
}

/*****************************************************************************
 函 数 名  : Om_SendQueryDumpMsg
 功能描述  : CCpu查询Dump信息
 输入参数  : NA

 输出参数  : NA

 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2014年10月08日
    作    者   : d00212987
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_UINT32 Om_SendQueryDumpMsg(VOS_VOID)
{
    BBP_DUMP_MSG_STRU                  *pstBbpDumpMsg;

    /* 申请消息发送给ACPU，查询DRV Dump信息 */
    pstBbpDumpMsg = (BBP_DUMP_MSG_STRU*)VOS_AllocMsg(CCPU_PID_PAM_OM,
                            sizeof(BBP_DUMP_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 分配消息失败 */
    if (VOS_NULL_PTR == pstBbpDumpMsg)
    {
        g_stBbpDumpErrInfo.usAllocMsgErr++;
        /*lint -e534*/
        LogPrint("Om_SendQueryDumpMsg:alloc msg fail: %d!\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    pstBbpDumpMsg->ulReceiverPid  = ACPU_PID_PAM_OM;
    pstBbpDumpMsg->usPrimId       = BBP_QUERY_DUMP_INFO_REQ;

    return VOS_SendMsg(CCPU_PID_PAM_OM, pstBbpDumpMsg);

}

/*****************************************************************************
 函 数 名  : Om_BbpDumpAddrQueryMsgProc
 功能描述  : ACpu回复查询Dump内存信息后处理函数
 输入参数  : pMsg:来自Acpu回复查询DUMP消息
 输出参数  : NA

 返 回 值  : VOS_VOID

 修改历史      :
  1.日    期   : 2015年08月05日
    作    者   : h00300778
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_VOID Om_BbpDumpAddrQueryMsgProc(MsgBlock *pMsg)
{
    BBP_DUMP_MSG_STRU                  *pstBbpDumpMsg;

    pstBbpDumpMsg = (BBP_DUMP_MSG_STRU *)pMsg;

    /* 可维可测 */
    g_stBbpDumpInfo.ulPhyAddr = pstBbpDumpMsg->stDumpDdrInfo.ulPhyAddr;
    g_stBbpDumpInfo.ulPhySize = pstBbpDumpMsg->stDumpDdrInfo.ulPhySize;

    return;
}

/*****************************************************************************
 函 数 名  : Om_ConfigBbpDumpProc
 功能描述  : CCpu查询Dump内存信息后处理函数
 输入参数  : pMsg:来自Acpu回复查询DUMP消息
             pstPcMsg:工具下发的配置消息

 输出参数  : NA

 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2014年10月08日
    作    者   : d00212987
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_UINT32 Om_ConfigBbpDumpProc(APP_OM_BBP_DUMP_SET_STRU      *pstPcMsg)
{
    BBP_DUMP_GET_FIX_DDR_ADDR           stBbpDumpFixDdr;
    VOS_UINT32                          ulRet;

    stBbpDumpFixDdr.ulPhyAddr = g_stBbpDumpInfo.ulPhyAddr;
    stBbpDumpFixDdr.ulPhySize = g_stBbpDumpInfo.ulPhySize;

    /* 如果查询到的地址或大小为0，结束配置EDMA */
    if ((VOS_NULL == stBbpDumpFixDdr.ulPhyAddr) || (0 == stBbpDumpFixDdr.ulPhySize))
    {
        /*lint -e534*/
        LogPrint("Om_ConfigBbpDumpProc: DRV not alloc dump memory\r\n");
        /*lint +e534*/
        return BBP_DUMP_DISABLE;
    }

    /* ulRet       = Om_ConfigBbpDumpEdma(pstPcMsg->ulDataLen,
                                       stBbpDumpFixDdr.ulPhyAddr,
                                       stBbpDumpFixDdr.ulPhySize,
                                       pstPcMsg->enMode);*/
    ulRet       = Om_ConfigBbpDumpEdma(((stBbpDumpFixDdr.ulPhySize)/1024),
                                       stBbpDumpFixDdr.ulPhyAddr,
                                       stBbpDumpFixDdr.ulPhySize,
                                       OM_BBP_DUMP_MODE_W);
    if(BBP_DUMP_OK != ulRet)
    {
        /*lint -e534*/
        LogPrint("Om_ConfigBbpDumpProc:Config Edma fail!\r\n");
        /*lint +e534*/
        return ulRet;
    }

    /*配置BBP寄存器 */
    Om_ConfigBbpDumpReg(pstPcMsg);

    /* 置BBP 开始采数标志 */
    g_stBbpDumpInfo.usDUMPStatus = OM_BBP_START;
    /*g_stBbpDumpInfo.usDUMPMode   = (VOS_UINT16)pstPcMsg->enMode;*/
    g_stBbpDumpInfo.usDUMPMode   = (VOS_UINT16)OM_BBP_DUMP_MODE_W;

    return BBP_DUMP_OK;
}

/*****************************************************************************
* 函 数 名  : Om_ConfigBbpDump
*
* 功能描述  : 配置BBP数采
*
* 输入参数  : pstAppToOmMsg : 消息包指针
*             usReturnPrimId: 回复消息ID
*
* 输出参数  : 无
*
* 返 回 值  : VOS_OK: 成功  VOS_ERR:失败
  1.日    期   : 2012年11月13日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_UINT32 Om_ConfigBbpDump(
    APP_OM_BBP_DUMP_SET_STRU           *pstPcMsg)
{
    OM_BBP_DUMP_ENABLE_STRU             stEnableFlag;
    VOS_UINT32                          ulRet;

    stEnableFlag.ulEnable = OM_BBP_DUMP_DISABLE;

    /*读NV项*/
    if (NV_OK != NV_Read(en_NV_Item_BBP_DUMP_ENABLE,
                         (VOS_VOID *)(&stEnableFlag),
                         sizeof(OM_BBP_DUMP_ENABLE_STRU)))
    {
        /*lint -e534*/
        LogPrint("Om_ConfigBbpDump: Read Nv Fail\r\n");
        /*lint +e534*/

        return BBP_DUMP_READ_NV_ERR;
    }

    /* 判断是否使能BBP数采 */
    if (OM_BBP_DUMP_DISABLE == stEnableFlag.ulEnable)
    {
        /*lint -e534*/
        LogPrint("Om_ConfigBbpDump: Not Enable BBP DUMP\r\n");
        /*lint +e534*/

        return BBP_DUMP_DISABLE;
    }

#if 0
    /* 检查参数是否正确 */
    ulRet = Om_CheckBbpDumpPara(pstPcMsg);
    if (BBP_DUMP_OK != ulRet)
    {
        /*lint -e534*/
        LogPrint1("Om_ConfigBbpDump:para err: %d!\r\n",(VOS_INT)ulRet);
        /*lint +e534*/

        return ulRet;
    }
#endif

    ulRet = Om_ConfigBbpDumpProc(pstPcMsg);

    if(BBP_DUMP_OK != ulRet)
    {
        /*lint -e534*/
        LogPrint("Om_ConfigBbpDump:Om_ConfigBbpDumpProc fail!\r\n");
        /*lint +e534*/

        return ulRet;
    }

    return BBP_DUMP_OK;
}

/*****************************************************************************
* 函 数 名  : Om_EndBbpDump
*
* 功能描述  : CCPU OM收到DUMP EDMA 回调函数发来的消息，需要关闭EDMA,
*             并发送消息到ACPU OM
*
* 输入参数  : pstAppToOmMsg : 消息包指针
*             usReturnPrimId: 消息回复ID
*
* 输出参数  : 无
*
* 返 回 值  : 无
  1.日    期   : 2012年11月13日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_UINT32 Om_EndBbpDump(VOS_VOID)
{
    VOS_UINT32                          ulRslt;
    DIAG_TRANS_IND_STRU                 stDiagTransMsg;

    /* 调用DRV函数关闭EDMA,如果关闭EDMA失败，对全局没有影响，所以不用返回 */
    if (MDRV_ERROR == mdrv_edma_chan_stop((VOS_UINT32)g_stBbpDumpInfo.lEdmaChanID))
    {
        /*lint -e534*/
        LogPrint1("Om_EndBbpDump: Close EDMA: %d  fail\r\n", g_stBbpDumpInfo.lEdmaChanID);
        /*lint +e534*/
        g_stBbpDumpErrInfo.usCloseEdmaErr++;
    }

    /*lint -e534*/
    LogPrint("Om_EndBbpDump:Send Msg To PC\r\n");
    /*lint +e534*/

    ulRslt = BBP_DUMP_END;

    stDiagTransMsg.ulModule = DIAG_GEN_MODULE_EX(DIAG_MODEM_0, DIAG_MODE_COMM, DIAG_MSG_TYPE_BBP);
    stDiagTransMsg.ulPid    = CCPU_PID_PAM_OM;
    stDiagTransMsg.ulMsgId  = OM_APP_BBP_DUMP_END_CNF;
    stDiagTransMsg.ulLength = sizeof(ulRslt);
    stDiagTransMsg.pData    = (VOS_VOID *)&ulRslt;

    /*lint -e534*/
    (VOS_VOID)DIAG_TransReport_Ex(&stDiagTransMsg);

    return VOS_OK;
}

/*****************************************************************************
* 函 数 名  : Om_EndBbpDbg
*
* 功能描述  : 写寄存器结束BBP可维可测
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  :  无
  1.日    期   : 2012年11月13日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_VOID Om_EndBbpDbg(VOS_VOID)
{
#if 0 /*defined (CHIP_BB_HI6210) 6210芯片代码，暂时保留*/
    VOS_INT                             lRet;

    if ( OM_BBP_DBG_START == g_stBbpDbgInfo.ulBbpDbgStatus)
    {
        /* 清DBG打开信号 */
        OM_BBP_REG_SETBITS(WBBP_BBP_DBG_START_ADDR, 0, 1, 0x0);

        /* DBG停止信号 */
        OM_BBP_REG_SETBITS(WBBP_BBP_DBG_STOP_ADDR, 0, 1, 0x1);

        lRet = mdrv_edma_chan_stop((VOS_UINT32)g_stBbpDbgInfo.lBbpEdmaChanID);
        if (MDRV_ERROR == lRet)
        {
            /*lint -e534*/
            LogPrint1("Om_EndBbpDbg: Close EDMA: %d  fail\r\n", g_stBbpDbgInfo.lBbpEdmaChanID);
            /*lint +e534*/
            g_stBbpDbgErrInfo.usStopEdmaErrNum++;
        }

        OM_BBP_READ_REG(g_stBbpDbgInfo.ulIndexValue,WBBP_DDR_BIT_CNT_ADDR);

        g_stBbpDbgInfo.ulBbpDbgStatus = OM_BBP_DBG_STOP;
    }
#endif

    return;
}

/*****************************************************************************
* 函 数 名  : Om_CheckBbpDbgPara
*
* 功能描述  : 检查BBP可维可测参数是否正确
*
* 输入参数  : pstPcMsg : PC下发的配置可维可测信息
*
*
* 输出参数  : 无
*
* 返 回 值  : 成功:BBP_DUMP_OK/失败:返回对应错误码
  1.日    期   : 2012年11月13日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_UINT32 Om_CheckBbpDbgPara(APP_OM_BBP_DBG_SET_W_STRU *pstPcMsg)
{
    /* 判断BBP接口选择信号是否正确 */
    if (pstPcMsg->enBBPIfSel >= BBP_IF_SEL_BUTT)
    {
        return BBP_DBG_IF_SEL_ERR;
    }

    /* 判断时钟选择信息是否正确 */
    if (pstPcMsg->enClkInSel >= BBP_DBG_CLK_IN_SEL_BUTT)
    {
        return BBP_DBG_CLK_IN_SEL_ERR;
    }

    /* 判断下发的模式是否正确 */
    if (pstPcMsg->enMode >= OM_BBP_DUMP_MODE_BUTT)
    {
        return BBP_DBG_MODE_ERR;
    }

    if ((pstPcMsg->ulMaskAddrEnd0 > MAX_BBP_OFFSET_ADDR )
        || (pstPcMsg->ulMaskAddrEnd1 > MAX_BBP_OFFSET_ADDR)
        || (pstPcMsg->ulMaskAddrEnd2 > MAX_BBP_OFFSET_ADDR)
        || (pstPcMsg->ulMaskAddrEnd3 > MAX_BBP_OFFSET_ADDR))
    {
        return BBP_DBG_ADDR_ERR;
    }

    /* 判断地址范围是否正确 */
    if ((pstPcMsg->ulMaskAddrStart0 > pstPcMsg->ulMaskAddrEnd0)
        || (pstPcMsg->ulMaskAddrStart1 > pstPcMsg->ulMaskAddrEnd1)
        || (pstPcMsg->ulMaskAddrStart2 > pstPcMsg->ulMaskAddrEnd2)
        || (pstPcMsg->ulMaskAddrStart3 > pstPcMsg->ulMaskAddrEnd3))
    {
        return BBP_DBG_ADDR_ERR;
    }

    return BBP_DBG_OK;
}

/*****************************************************************************
* 函 数 名  : Om_EnableDBGEdma
*
* 功能描述  : 使能可维可测EDMA使能
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 成功:BBP_DBG_OK  失败:对应错误码
  1.日    期   : 2012年11月13日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_UINT32 Om_EnableDBGEdma(VOS_VOID)
{
    VOS_INT                             lRet;

    /* 关闭EDMA */
    lRet = mdrv_edma_chan_stop((VOS_UINT32)g_stBbpDbgInfo.lBbpEdmaChanID);
    if(MDRV_ERROR == lRet)
    {
        g_stBbpDbgErrInfo.usStopEdmaErrNum++;;
        return BBP_DBG_STOP_EDMA_ERR;
    }

    /* 调用DRV 函数使能EDMA*/
    lRet = mdrv_edma_chan_lli_async_start((VOS_UINT32)g_stBbpDbgInfo.lBbpEdmaChanID);
    if (MDRV_OK != lRet)
    {
        g_stBbpDbgErrInfo.usStartEdmaErrNum++;
        return BBP_DBG_ENABLE_EDMA_ERR;
    }

    return BBP_DBG_OK;

}


/*****************************************************************************
* 函 数 名  : Om_ConfigBbpDbgReg
*
* 功能描述  : 配置BBP 可维可测寄器
*
* 输入参数  : pstPcMsg : 配置信息
*
* 输出参数  : 无
*
* 返 回 值  : 成功:BBP_DBG_OK  失败:对应错误码
  1.日    期   : 2012年11月13日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_UINT32 Om_ConfigBbpDbgReg(APP_OM_BBP_DBG_SET_W_STRU *pstPcMsg)
{
#if 0 /*defined (CHIP_BB_HI6210) 6210芯片代码，暂时保留*/
    VOS_UINT32                          ulValue;
    VOS_UINT32                          ulResult;

    /* 检查PC侧下发的配置信息是否正确 */
    ulResult = Om_CheckBbpDbgPara(pstPcMsg);
    if (BBP_DBG_OK != ulResult)
    {
        return ulResult;
    }

    /* DBG上报使能，1表示打开上报功能，0表示关闭上报功能。完成时钟门控 */
    OM_BBP_REG_SETBITS(WBBP_BBP_DBG_EN_ADDR, 0, 1, 0x1);

    /* 时钟bypass使能 */
    OM_BBP_REG_SETBITS(WBBP_BBP_DBG_BYPASS_ADDR, 0, 10, 0x3FF);

    /* 先强制关闭可维可测打开信号 */
    OM_BBP_REG_SETBITS(WBBP_BBP_DBG_STOP_ADDR, 0, 1, 0x1);

    /* 配置BBP可维可测模式 */
    OM_BBP_REG_SETBITS(BBPCOMM_BBP_SYS_1CONTROL_ADDR, 0, 2, pstPcMsg->enMode);

    /* 清FIFO */
    OM_BBP_REG_SETBITS(WBBP_DBG_FLOW_CLR_ADDR, 0, 9, 0x1FF);
    OM_BBP_REG_SETBITS(WBBP_DBG_FLOW_CLR_ADDR, 16, 1, 0x1);

    /* BBP接口选择信号 */
    OM_BBP_REG_SETBITS(WBBP_BBP_IF_SEL_ADDR, 0, 2, pstPcMsg->enBBPIfSel);

    /* DDR中DBG空间大小，2Kbyte为单位。如配置为8表示DBG空间为8个2Kbyte */
    OM_BBP_REG_SETBITS(WBBP_DBG_DDR_2K_NO_ADDR, 0, 4, 0x01);

    /* 可维可测输入时钟选择 */
    OM_BBP_REG_SETBITS(WBBP_DBG_CLK_IN_SEL_ADDR, 0, 2, pstPcMsg->enClkInSel);

    /* 软件配置的包头中reserve信息 */
    OM_BBP_REG_SETBITS(WBBP_DBG_HEAD_SERVE_ADDR, 0, 4, OM_TOOL_GUBBP_ID);

    /* 使用时间戳选择 */
    ulValue     = pstPcMsg->ulTimeSel & 0x7F;
    OM_BBP_REG_SETBITS(WBBP_DBG_TIMING_SEL_ADDR, 0, 6, ulValue);

    /* 屏蔽地址配置  */
    ulValue     = pstPcMsg->ulMaskAddrStart0 & MAX_BBP_OFFSET_ADDR;
    OM_BBP_REG_SETBITS(WBBP_MASK_ADDR0_START_ADDR, 0, 20, ulValue);

    ulValue     = pstPcMsg->ulMaskAddrStart1 & MAX_BBP_OFFSET_ADDR;
    OM_BBP_REG_SETBITS(WBBP_MASK_ADDR1_START_ADDR, 0, 20, ulValue);

    ulValue     = pstPcMsg->ulMaskAddrStart2 & MAX_BBP_OFFSET_ADDR;
    OM_BBP_REG_SETBITS(WBBP_MASK_ADDR2_START_ADDR, 0, 20, ulValue);

    ulValue     = pstPcMsg->ulMaskAddrStart3 & MAX_BBP_OFFSET_ADDR;
    OM_BBP_REG_SETBITS(WBBP_MASK_ADDR3_START_ADDR, 0, 20, ulValue);

    ulValue     = pstPcMsg->ulMaskAddrEnd0 & MAX_BBP_OFFSET_ADDR;
    OM_BBP_REG_SETBITS(WBBP_MASK_ADDR0_END_ADDR, 0, 20, ulValue);

    ulValue     = pstPcMsg->ulMaskAddrEnd1 & MAX_BBP_OFFSET_ADDR;
    OM_BBP_REG_SETBITS(WBBP_MASK_ADDR1_END_ADDR, 0, 20, ulValue);

    ulValue     = pstPcMsg->ulMaskAddrEnd2 & MAX_BBP_OFFSET_ADDR;
    OM_BBP_REG_SETBITS(WBBP_MASK_ADDR2_END_ADDR, 0, 20, ulValue);

    ulValue     = pstPcMsg->ulMaskAddrEnd3 & MAX_BBP_OFFSET_ADDR;
    OM_BBP_REG_SETBITS(WBBP_MASK_ADDR3_END_ADDR, 0, 20, ulValue);

    /* 可维可测 FIFO水线选择 */
    ulValue     = pstPcMsg->enFifoWater & 0x7;
    OM_BBP_REG_SETBITS(WBBP_DBG_FIFO_WATERMARKER_ADDR, 0, 3, ulValue);

    /* 可维可测上报信息开关，1表示上报相应信息，0表示不上报相应信息 */
    ulValue     = pstPcMsg->ulDbgSwitch & 0x1F;
    OM_BBP_REG_SETBITS(WBBP_BBP_DBG_SWITCH_ADDR, 0, 5, ulValue);

    /* 清可维可测停止信号 */
    OM_BBP_REG_SETBITS(WBBP_BBP_DBG_STOP_ADDR, 0, 1, 0x0);

    /* 可维可测打开信号 */
    OM_BBP_REG_SETBITS(WBBP_BBP_DBG_START_ADDR, 0, 1, 0x1);

    /*lint -e534*/
    LogPrint("Om_ConfigBbpDbgReg: Config Reg success\r\n");
    /*lint +e534*/
#endif

    return BBP_DBG_OK;
}

/*****************************************************************************
* 函 数 名  : Om_ConfigBbpDbg
*
* 功能描述  : 配置BBP 可维可测上报
*
* 输入参数  : pstAppToOmMsg : 消息包指针
*             usReturnPrimId: 回复消息ID
*
* 输出参数  : 无
*
* 返 回 值  : VOS_OK: 成功  VOS_ERR:失败
  1.日    期   : 2012年11月13日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_UINT32 Om_ConfigBbpDbg(
    APP_OM_BBP_DBG_SET_W_STRU          *pstPcMsg)
{
    VOS_UINT32                          ulRet;

    /* 检查初始化EDMA和SOCP是否成功 */
    if (BBP_DBG_OK != g_stBbpDbgInfo.ulBbpErrCode)
    {
        return g_stBbpDbgInfo.ulBbpErrCode;
    }

    /* 工具下发停止 BBP寄存器上报 */
    if (OM_BBP_STOP == pstPcMsg->enStatus)
    {
        /*lint -e522*/
        Om_EndBbpDbg();
        /*lint +e522*/

        return BBP_DBG_OK;
    }

    /* 使能 EDMA */
    ulRet = Om_EnableDBGEdma();
    if(BBP_DBG_OK != ulRet)
    {
        /*lint -e534*/
        LogPrint1("Om_ConfigBbpDbg: Enable EDMA Fail %d\r\n", (VOS_INT)ulRet);
        /*lint +e534*/

        return ulRet;
    }

    /* 配置BBP寄存器 */
    ulRet = Om_ConfigBbpDbgReg(pstPcMsg);
    if(BBP_DBG_OK != ulRet)
    {
        /*lint -e534*/
        LogPrint1("Om_ConfigBbpDbg: Config Reg Fail %d\r\n", (VOS_INT)ulRet);
        /*lint +e534*/

        return ulRet;
    }

    g_stBbpDbgInfo.ulBbpDbgStatus  = OM_BBP_DBG_START;

    return BBP_DBG_OK;
}

/*****************************************************************************
* 函 数 名  : Om_BbpDbgAllocCycBuf
*
* 功能描述  : 分配 GU BBP 可维可测使用的循环buff
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : VOS_OK: 成功  VOS_ERR:失败
  1.日    期   : 2012年11月13日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_UINT32 Om_BbpDbgAllocCycBuf(VOS_VOID)
{
#if 0 /*defined (CHIP_BB_HI6210) 6210芯片代码，暂时保留*/
    VOS_UINT32                          i;
    VOS_UINT32                          ulVirBufAddr;
    VOS_UINT_PTR                        ulPhyBufAddr;
    BALONG_DMA_CB_S                    *pstCycBuf;
    BALONG_DMA_CB_S                    *pstCycBufTemp;

    /* 申请空间 */
    ulVirBufAddr = (VOS_UINT32)VOS_UnCacheMemAlloc(BBP_DBG_TOTAL_MEM_LENTH, &ulPhyBufAddr);
    if (VOS_NULL == ulVirBufAddr)
    {
        /*lint -e534*/
        LogPrint("Om_BbpDbgAllocMem: Alloc Mem err!\r\n");
        /*lint +e534*/
        g_stBbpDbgErrInfo.usAllocErr++;
        g_stBbpDbgInfo.ulBbpErrCode = BBP_DBG_ALLOC_ERR;
        return VOS_ERR;
    }

    g_stBbpDbgInfo.ulPhyAddr = ulPhyBufAddr;

    /* 配置SOCP通道编码源通道的物理地址和虚地址 */
    for (i = 0; i < BBP_DBG_CODER_SRC_NUM; i++)
    {
        g_astBbpDbgCoderSrcCfg[i].pucSrcBuf = (VOS_UINT8*)ulVirBufAddr + BBP_DBG_CODER_SRC_SIZE * i;
        g_astBbpDbgCoderSrcCfg[i].pucSrcPHY = (VOS_UINT8*)ulPhyBufAddr + BBP_DBG_CODER_SRC_SIZE * i;
    }


    /* 为保证256bit对齐，多分配32 byte */
    pstCycBuf = (BALONG_DMA_CB_S*)VOS_MemAlloc(CCPU_PID_PAM_OM, DYNAMIC_MEM_PT,
                        (BBP_DBG_CODER_SRC_NUM * BBP_DBG_NODE_NUM * sizeof(BALONG_DMA_CB_S) + 32));
    if (VOS_NULL_PTR == pstCycBuf)
    {
        g_stBbpDbgErrInfo.usAllocCycErr++;
        g_stBbpDbgInfo.ulBbpErrCode = BBP_DBG_ALLOC_CYC_ERR;
        /*lint -e534*/
        LogPrint("Om_BbpDbgAllocCycBuf: alloc BALONG_DMA_CB_S fail\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    /* 256 bit对齐 */
    pstCycBuf =(BALONG_DMA_CB_S*)(((VOS_UINT32)pstCycBuf + 31)  & ~ 31);

    pstCycBufTemp = (BALONG_DMA_CB_S*)pstCycBuf;
    g_pstBbpCycBufHead = pstCycBuf;

    /* 构成循环链表 */
    for (i = 0; i < BBP_DBG_CODER_SRC_NUM * BBP_DBG_NODE_NUM; i++)
    {
        pstCycBufTemp->cnt0     = BBP_DBG_NODE_SIZE;
        pstCycBufTemp->cnt1     = 0;
        pstCycBufTemp->bindx    = 0;
        pstCycBufTemp->cindx    = 0;
        pstCycBufTemp->src_addr = (VOS_UINT32)WBBP_BBP_DBG_RDATA_ADDR;
        pstCycBufTemp->des_addr = ulPhyBufAddr
                                    + BBP_DBG_NODE_SIZE
                                    * ((i%BBP_DBG_CODER_SRC_NUM) * BBP_DBG_NODE_NUM
                                    + (i / BBP_DBG_CODER_SRC_NUM));
        pstCycBufTemp->config   = mdrv_edma_set_config(EDMA_BBP_DBG, BALONG_DMA_P2M, EDMA_TRANS_WIDTH_32, EDMA_BUR_LEN_16);
        if(0 == pstCycBufTemp->config)
        {
            /*lint -e534*/
            LogPrint("Om_BbpDbgAllocCycBuf: Config EDMA fail\r\n");
            /*lint +e534*/
            g_stBbpDbgErrInfo.usConfigEdmaErr++;
            g_stBbpDbgInfo.ulBbpErrCode = BBP_DBG_CONFIG_EDMA_ERR;
            return VOS_ERR;
        }

        /* 如果是最后一个结点，退出 */
        if ((BBP_DBG_CODER_SRC_NUM * BBP_DBG_NODE_NUM - 1) == i)
        {
            break;
        }
        pstCycBufTemp->lli = (((VOS_UINT32)(pstCycBufTemp + 1)) & 0xFFFFFFE0) | 0x02;
        pstCycBufTemp++;
    }

    pstCycBufTemp->lli = (((VOS_UINT32)g_pstBbpCycBufHead) & 0xFFFFFFE0) | 0x02;

    /* 第一个结点，需将config的bit0 置为0 */
    pstCycBufTemp = g_pstBbpCycBufHead;
    pstCycBufTemp->config &= 0xFFFFFFFE;

#endif

    return VOS_OK;

}

/*****************************************************************************
* 函 数 名  : Om_BbpDbgEdmaCallBack
*
* 功能描述  : 在BBP 可维可测时注册给EDMA的回调函数
*
* 输入参数  : ulFlag:中断类型
*             ulChannelArg:暂不用
*
* 输出参数  : 无
*
* 返 回 值  : VOS_OK: 成功  VOS_ERR:失败
  1.日    期   : 2012年11月13日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
    说    明   : 此函数在低软的中断上下文中调用
*****************************************************************************/
VOS_UINT32 Om_BbpDbgEdmaCallBack(VOS_UINT32 ulChannelArg, VOS_UINT32 ulFlag)
{
#if 0 /*defined (CHIP_BB_HI6210) 6210芯片代码，暂时保留*/
    APP_BBP_DUMP_REQ_MSG_STRU          *pstPcMsg;
    BBP_EDMA_ERR_STRU                  *pstEdmaErr;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulDbgSwitchValue;

    /* DMA传输完成中断 */
    if (BALONG_DMA_INT_LLT_DONE == ulFlag)
    {
        ulIndex = g_stBbpDbgInfo.ulBbpEdmaCallBackNum% 8;
        g_stBbpDbgInfo.ulLastAddr = (VOS_UINT32)(g_stBbpDbgInfo.ulPhyAddr
                + BBP_DBG_NODE_SIZE * ((ulIndex % BBP_DBG_CODER_SRC_NUM) * BBP_DBG_NODE_NUM
                + (ulIndex / BBP_DBG_CODER_SRC_NUM)));
        if(BBP_DBG_MAGIC_SIGN != *((VOS_UINT32*)g_stBbpDbgInfo.ulLastAddr))
        {
            *((VOS_UINT32*)g_stBbpDbgInfo.ulLastAddr) = (VOS_UINT32)BBP_DBG_MAGIC_SIGN;
            *(((VOS_UINT32*)g_stBbpDbgInfo.ulLastAddr) + 1) = (VOS_UINT32)BBP_DBG_PACKAGE_LENTH;
            *(((VOS_UINT32*)g_stBbpDbgInfo.ulLastAddr) + 2) = (VOS_UINT32)BBP_DBG_ERR_PACKAGE_SIGN;

            /* 停止可给可维可测 */
            OM_BBP_REG_SETBITS(WBBP_BBP_DBG_STOP_ADDR, 0, 1, 0x1);
            OM_BBP_READ_REG(ulDbgSwitchValue,WBBP_BBP_DBG_SWITCH_ADDR);

            /* 清FIFO */
            OM_BBP_REG_SETBITS(WBBP_DBG_FLOW_CLR_ADDR, 0, 9, 0x1FF);
            OM_BBP_REG_SETBITS(WBBP_DBG_FLOW_CLR_ADDR, 16, 1, 0x1);

            /* BBP需要一个电平转换才能清掉FIFO */
            OM_BBP_WRITE_REG(WBBP_BBP_DBG_SWITCH_ADDR,ulDbgSwitchValue);

            /* 查询BBP总包数 */
            OM_BBP_READ_REG(g_stBbpDbgInfo.ulIndexValue,WBBP_DDR_BIT_CNT_ADDR);

            /* 重新启动EDMA */
            /*lint -e534*/
            Om_EnableDBGEdma();
            /*lint +e534*/

            /* 重新开启可维可测 */
            OM_BBP_REG_SETBITS(WBBP_BBP_DBG_START_ADDR, 0, 1, 0x1);

            g_stBbpDbgInfo.ulFlowNum++;

        }

        /*lint -e534*/
        VOS_SmV(g_ulBbpDbgSem);
        /*lint +e534*/
        g_stBbpDbgInfo.ulBbpEdmaCallBackNum++;
    }
    /* EDMA错误中断 */
    else
    {
        if (VOS_NULL_PTR == g_pstBbpDbgMsg)
        {
            return VOS_ERR;
        }

        pstPcMsg = (APP_BBP_DUMP_REQ_MSG_STRU *)g_pstBbpDbgMsg;
        pstPcMsg->ulMsgName  = APP_OM_BBP_EDMA_ERR_REQ;
        pstPcMsg->ulSenderPid= MSP_PID_DIAG_APP_AGENT;

        /* 标识是可维可测产生的EDMA错误中断 */
        pstEdmaErr = (BBP_EDMA_ERR_STRU *)pstPcMsg->aucValue;
        pstEdmaErr->enEdmaErr = OM_BBP_DBG_EDMA_ERR;

        /* 模拟PC通过MSP_PID_DIAG_APP_AGENT给CCPU_PID_PAM_OM发送消息 */
        (VOS_VOID)VOS_SendMsg(CCPU_PID_PAM_OM, g_pstBbpDbgMsg);

        g_stBbpDbgErrInfo.usEdmaErrCode = (VOS_UINT16)ulFlag;
    }
#endif

    return VOS_OK;

}


/*****************************************************************************
* 函 数 名  : Om_BbpDbgChanInit
*
* 功能描述  : 可维可测上报初始化
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 无
  1.日    期   : 2012年11月13日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_VOID Om_BbpDbgChanInit(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;
    SOCP_CODER_SRC_CHAN_S               stChannel;   /* 通道的属性信息 */
    BALONG_DMA_CB_S                    *pstConfigAddr;
    OM_BBP_DUMP_ENABLE_STRU             stEnableFlag;

    /* 初始化全局变量 */
    /*lint -e534*/
    VOS_MemSet(&g_stBbpDbgErrInfo,  0, sizeof(g_stBbpDbgErrInfo));
    VOS_MemSet(&g_stBbpDbgInfo,     0, sizeof(g_stBbpDbgInfo));
    /*lint +e534*/

    /* 置可维可测状态标志 */
    g_stBbpDbgInfo.ulBbpDbgStatus = OM_BBP_DBG_STOP;

    /*创建信号量*/
    if ( VOS_OK != VOS_SmCCreate("BbpD", 0, VOS_SEMA4_FIFO, &g_ulBbpDbgSem))
    {
        g_stBbpDbgErrInfo.usCreateSemErr++;
        g_stBbpDbgInfo.ulBbpErrCode = BBP_DBG_CREATE_SEM_ERR;
        /*lint -e534*/
        LogPrint("Om_BbpDbgChanInit: VOS_SmCCreate Fail\r\n");
        /*lint +e534*/
        return;
    }

    stEnableFlag.ulEnable = OM_BBP_DUMP_DISABLE;

    /*读NV项*/
    if(NV_OK != NV_Read(en_NV_Item_BBP_DUMP_ENABLE,
        (VOS_VOID *)(&stEnableFlag), sizeof(OM_BBP_DUMP_ENABLE_STRU)))
    {
        /*lint -e534*/
        LogPrint("Om_BbpDbgChanInit: Read Nv Fail\r\n");
        /*lint +e534*/
        return;
    }

    /* 判断是否启动BBP可维可测 */
    if (OM_BBP_DUMP_DISABLE == stEnableFlag.ulEnable)
    {
        /*lint -e534*/
        LogPrint("Om_BbpDbgChanInit: Not Enable BBP DUMP\r\n");
        /*lint +e534*/
        return;
    }

    /*初始化BBP 可维可测使用的EDMA通道 */
    g_stBbpDbgInfo.lBbpEdmaChanID = mdrv_edma_chan_init(EDMA_BBP_DBG,
                                    (channel_isr)Om_BbpDbgEdmaCallBack,
                                    VOS_NULL, BBP_DBG_EDMA_INT);
    if (g_stBbpDbgInfo.lBbpEdmaChanID < MDRV_OK)
    {
        g_stBbpDbgErrInfo.usInitEdmaErr++;
        g_stBbpDbgInfo.ulBbpErrCode = BBP_DBG_INIT_EDMA_ERR;
        return;
    }

    /* 申请空间，形成循环链表 */
    ulRet =  Om_BbpDbgAllocCycBuf();
    if (VOS_ERR == ulRet)
    {
        /*lint -e534*/
        LogPrint("Om_BbpDbgChanInit: Alloc Mem Error\r\n");
        /*lint +e534*/
        return ;
    }

    /* 获取可维可测EDMA通道循环链表配置地址 */
    pstConfigAddr = mdrv_edma_chan_get_lli_addr((VOS_UINT32)g_stBbpDbgInfo.lBbpEdmaChanID);
    if (VOS_NULL_PTR == pstConfigAddr)
    {
        g_stBbpDbgErrInfo.usGetConAddrErr++;
        g_stBbpDbgInfo.ulBbpErrCode = BBP_DBG_GET_CONFIGADD_ERR;
        /*lint -e534*/
        LogPrint("Om_BbpDbgChanInit: get lli config add fail\r\n");
        /*lint +e534*/
        return ;
    }

    /* 将配置信息写入EDMA配置地址 */
    /*lint -e534*/
    VOS_MemCpy(pstConfigAddr, g_pstBbpCycBufHead, sizeof(BALONG_DMA_CB_S));
    /*lint +e534*/

    for (i = 0; i < BBP_DBG_CODER_SRC_NUM; i++)
    {
        /*lint -e534*/
        VOS_MemSet(&stChannel, 0, sizeof(stChannel));
        /*lint +e534*/
        stChannel.u32DestChanID = g_astBbpDbgCoderSrcCfg[i].enDstCHID;   /*  目标通道ID */
        stChannel.eDataType     = g_astBbpDbgCoderSrcCfg[i].enDataType;           /*  数据类型，指明数据封装协议，用于复用多平台 */
        stChannel.eMode         = g_astBbpDbgCoderSrcCfg[i].enCHMode;             /*  通道数据模式 */
        stChannel.ePriority     = g_astBbpDbgCoderSrcCfg[i].enCHLevel;            /*  通道优先级 */
        stChannel.u32BypassEn   = SOCP_HDLC_ENABLE;                               /*  通道bypass使能 */
        stChannel.eDataTypeEn   = SOCP_DATA_TYPE_EN;                              /*  数据类型使能位 */
        stChannel.eDebugEn      = SOCP_ENC_DEBUG_DIS;                             /*  调试位使能 */

        stChannel.sCoderSetSrcBuf.pucInputStart  = g_astBbpDbgCoderSrcCfg[i].pucSrcPHY;                               /*  输入通道起始地址 */
        stChannel.sCoderSetSrcBuf.pucInputEnd    = (g_astBbpDbgCoderSrcCfg[i].pucSrcPHY + g_astBbpDbgCoderSrcCfg[i].ulSrcBufLen)-1;   /*  输入通道结束地址 */

        /* 配置通道 */
        if (VOS_OK != mdrv_socp_corder_set_src_chan(g_astBbpDbgCoderSrcCfg[i].enChannelID, &stChannel))
        {
            g_astBbpDbgCoderSrcCfg[i].enInitState = SCM_CHANNEL_CFG_FAIL;/* 记录通道开启配置错误 */
            g_stBbpDbgErrInfo.usInitSocpErr++;
            g_stBbpDbgInfo.ulBbpErrCode = BBP_DBG_INIT_SOCP_ERR;

            return;
        }

        /* 使能通道 */
        if(VOS_OK != mdrv_socp_start(g_astBbpDbgCoderSrcCfg[i].enChannelID))
        {
            g_astBbpDbgCoderSrcCfg[i].enInitState = SCM_CHANNEL_START_FAIL;  /* 记录通道开启错误 */
            g_stBbpDbgErrInfo.usStartSocpErr++;
            g_stBbpDbgInfo.ulBbpErrCode = BBP_DBG_START_SOCP_ERR;

            return;
        }

        g_astBbpDbgCoderSrcCfg[i].enInitState = SCM_CHANNEL_INIT_SUCC; /* 记录通道初始化配置信息 */
    }

    /* 申请一条保留消息，用于中断中发送 */
    g_pstBbpDbgMsg = (MsgBlock*)VOS_AllocMsg(CCPU_PID_PAM_OM, sizeof(APP_BBP_DUMP_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == g_pstBbpDbgMsg)
    {
        g_stBbpDumpErrInfo.usAllocMsgErr++;
        g_stBbpDbgInfo.ulBbpErrCode = BBP_DBG_ALLOC_MSG_ERR;
        return;
    }

    g_pstBbpDbgMsg->ulReceiverPid = CCPU_PID_PAM_OM;

    /* 标记该消息不用释放 */
    /*lint -e534*/
    VOS_ReserveMsg(CCPU_PID_PAM_OM, g_pstBbpDbgMsg);
    /*lint +e534*/
    return ;
}

/*****************************************************************************
* 函 数 名  : Om_BbpDbgSelfTask
*
* 功能描述  : OM BBP可维可测的自处理任务
*
* 输入参数  : pRspPacket : 消息包指针
*             pRspFuncPtr: 暂不用
*
* 输出参数  : 无
*
* 返 回 值  : 无
  1.日    期   : 2012年11月13日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_VOID Om_BbpDbgSelfTask(unsigned long ulPara1, unsigned long ulPara2,
                  unsigned long ulPara3, unsigned long ulPara4)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulRet;
    SOCP_BUFFER_RW_STRU                 stRwBuf;

#if (VOS_WIN32 == VOS_OS_VER)
    VOS_UINT32                          i;
    for (i = 0;i < 1; i++)
#else

    for (;;)
#endif
    {
        if(VOS_OK != VOS_SmP(g_ulBbpDbgSem, 0))
        {
            continue;
        }

        /* 计算这次中断应该处理的通道 */
        ulIndex = g_stBbpDbgInfo.ulBbpSelfTaskNum & (BBP_DBG_CODER_SRC_NUM -1);

        /* 获取通道的编码源空间 */
        if (VOS_OK != mdrv_socp_get_write_buff(g_astBbpDbgCoderSrcCfg[ulIndex].enChannelID, &stRwBuf))
        {
            g_stBbpDbgErrInfo.astBbpDbgSocpInfo[ulIndex].ulGetWriteBuffErr++;
            continue;
        }

        /* 判断空间是否足够 */
        if ((stRwBuf.u32RbSize + stRwBuf.u32Size) < BBP_DBG_NODE_SIZE)
        {
            g_stBbpDbgErrInfo.astBbpDbgSocpInfo[ulIndex].ulBuffNotEnough++;
            g_stBbpDbgErrInfo.astBbpDbgSocpInfo[ulIndex].ulWriteBufSize = stRwBuf.u32RbSize + stRwBuf.u32Size;
            continue;
        }

        /*lint -e732*/
        ulRet = mdrv_socp_write_done(g_astBbpDbgCoderSrcCfg[ulIndex].enChannelID, BBP_DBG_NODE_SIZE );
        /*lint +e732*/
        if (VOS_OK != ulRet)
        {
            g_stBbpDbgErrInfo.astBbpDbgSocpInfo[ulIndex].ulWriteDoneErr++;

            continue;
        }

        g_stBbpDbgErrInfo.astBbpDbgSocpInfo[ulIndex].ulWriteDoneOk++;

        /* 回调次数加 1 */
        g_stBbpDbgInfo.ulBbpSelfTaskNum++;

    }
}

/*****************************************************************************
* 函 数 名  : Om_CcpuBbpLogConfigMsgProc
*
* 功能描述  : 根据PC侧下发的透明消息进行BBP DUMP处理
*
* 输入参数  : pRcvMsg : 消息包指针
* *
* 输出参数  : 无
*
* 返 回 值  : 无
  1.日    期   : 2015年06月17日
    作    者   : H00300778
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_VOID Om_CcpuBbpLogConfigMsgProc(MsgBlock *pRcvMsg)
{
    APP_BBP_DUMP_REQ_MSG_STRU          *pstAppToOmMsg;
    VOS_UINT32                          ulRslt;

    pstAppToOmMsg = (APP_BBP_DUMP_REQ_MSG_STRU *)pRcvMsg;

    switch (pstAppToOmMsg->ulMsgName)
    {
        case APP_OM_BBP_DUMP_SET_REQ:
            ulRslt =  Om_ConfigBbpDump((APP_OM_BBP_DUMP_SET_STRU *)(pstAppToOmMsg->aucValue));

            /* 收到透明消息的处理结构要通过VOS消息给PC侧回复 */
            Om_CcpuBbpLogConfigCnf(pstAppToOmMsg, APP_OM_BBP_DUMP_SET_REQ, ulRslt);

            break;

        case APP_OM_BBP_DBG_SET_REQ:

            ulRslt =  Om_ConfigBbpDbg((APP_OM_BBP_DBG_SET_W_STRU *)(pstAppToOmMsg->aucValue));

            /* 收到透明消息的处理结构要通过VOS消息给PC侧回复 */
            Om_CcpuBbpLogConfigCnf(pstAppToOmMsg, APP_OM_BBP_DBG_SET_REQ, ulRslt);

            break;

        /* 下面两条消息不是透明消息，只是模拟的消息 */
        case APP_OM_BBP_DUMP_END_REQ:
            /*lint -e534*/
            Om_EndBbpDump();
            /*lint +e534*/
            break;

        case APP_OM_BBP_EDMA_ERR_REQ:
            /*lint -e534*/
            Om_SendEdmaErrToPc((BBP_EDMA_ERR_STRU *)(pstAppToOmMsg->aucValue), OM_APP_BBP_EDMA_ERR_CNF);
            /*lint +e534*/
            break;

        default:
            /* 收到透明消息的处理结构要通过VOS消息给PC侧回复 */
            Om_CcpuBbpLogConfigCnf(pstAppToOmMsg, pstAppToOmMsg->ulMsgName, VOS_ERR);

            break;
    }
}

/*****************************************************************************
* 函 数 名  : Om_CcpuBbpLogConfigCnf
*
* 功能描述  : 根据PC侧下发的透明消息进行回复处理
*
* 输入参数  : pstAppToOmMsg : PC侧消息包指针
* *
* 输出参数  : 无
*
* 返 回 值  : 无
  1.日    期   : 2015年06月17日
    作    者   : H00300778
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_VOID Om_CcpuBbpLogConfigCnf(
    APP_BBP_DUMP_REQ_MSG_STRU              *pstAppToOmMsg,
    VOS_UINT32                              ulMsgName,
    VOS_UINT32                              ulRslt)
{
    APP_BBP_DUMP_CNF_MSG_STRU          *pstOmtoAppMsg;

    pstOmtoAppMsg = (APP_BBP_DUMP_CNF_MSG_STRU *)VOS_AllocMsg(CCPU_PID_PAM_OM, sizeof(APP_BBP_DUMP_CNF_MSG_STRU));

    if (VOS_NULL_PTR == pstOmtoAppMsg)
    {
        return;
    }

    /* PC侧透明消息下发的参数原样带回 */
    pstOmtoAppMsg->usOriginalId = pstAppToOmMsg->usOriginalId;
    pstOmtoAppMsg->usTerminalId = pstAppToOmMsg->usTerminalId;
    pstOmtoAppMsg->ulTimeStamp  = pstAppToOmMsg->ulTimeStamp;
    pstOmtoAppMsg->ulSN         = pstAppToOmMsg->ulSN;

    /* 填充消息内容 */
    pstOmtoAppMsg->ulReceiverPid= MSP_PID_DIAG_APP_AGENT;
    pstOmtoAppMsg->ulMsgName    = ulMsgName;
    pstOmtoAppMsg->ulRslt       = ulRslt;

    /*lint -e534*/
    VOS_SendMsg(CCPU_PID_PAM_OM, pstOmtoAppMsg);
    /*lint +e534*/

    return;
}

/*****************************************************************************
* 函 数 名  : Om_BbpDbgShow
*
* 功能描述  : 查询可维可测的全局信息
*
* 输入参数  :
*
* 输出参数  : 无
*
* 返 回 值  : 无
  1.日    期   : 2012年11月13日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_VOID Om_BbpDbgShow(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("可维可测EDMA通道号:             %d\r\n",g_stBbpDbgInfo.lBbpEdmaChanID);
    vos_printf("BBP可维可测EDMA 完成回调次数:   %d\r\n",g_stBbpDbgInfo.ulBbpEdmaCallBackNum);
    vos_printf("自处理任务处理的次数:           %d\r\n", g_stBbpDbgInfo.ulBbpSelfTaskNum);
    vos_printf("BBP可维可测初始化错误码:        %d\r\n",g_stBbpDbgInfo.ulBbpErrCode);
    vos_printf("溢出包数:                       0x%x\r\n", g_stBbpDbgInfo.ulFlowNum);
    vos_printf("分配内存的物理地址 :            0x%x\r\n",g_stBbpDbgInfo.ulPhyAddr);
    vos_printf("BBP中发出的2K数据的数量:        0x%x\r\n",g_stBbpDbgInfo.ulIndexValue);
    vos_printf("前一次数采地址 g_ulUpAddr:      0x%x\r\n", g_stBbpDbgInfo.ulLastAddr);
    /*lint +e534*/
}

/*****************************************************************************
* 函 数 名  : Om_BbpDbgErrShow
*
* 功能描述  : 查询可维可测的错误信息
*
* 输入参数  :
*
* 输出参数  : 无
*
* 返 回 值  : 无
  1.日    期   : 2012年11月13日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_VOID Om_BbpDbgErrShow(VOS_VOID)
{
    VOS_UINT32                          i;
    /*lint -e534*/
    vos_printf("内存分配失败次数:       %d \r\n",g_stBbpDbgErrInfo.usAllocErr);
    vos_printf("SOCP初始化失败次数:     %d \r\n",g_stBbpDbgErrInfo.usInitSocpErr);
    vos_printf("启动SOCP失败次数:       %d \r\n",g_stBbpDbgErrInfo.usStartSocpErr);
    vos_printf("初始化EDMA失败次数:     %d \r\n",g_stBbpDbgErrInfo.usInitEdmaErr);
    vos_printf("配置EDMA失败次数:       %d \r\n",g_stBbpDbgErrInfo.usConfigEdmaErr);
    vos_printf("EDMA失败回调次数:       %d \r\n",g_stBbpDbgErrInfo.usEdmaErrCode);
    vos_printf("启动EDMA失败的次数:     %d \r\n",g_stBbpDbgErrInfo.usStartEdmaErrNum);
    vos_printf("关闭EDMA失败的次数:     %d \r\n",g_stBbpDbgErrInfo.usStopEdmaErrNum);
    vos_printf("分配循环链表节点失败:   %d \r\n",g_stBbpDbgErrInfo.usAllocCycErr);
    vos_printf("获取EDMA配置址失败:     %d \r\n",g_stBbpDbgErrInfo.usGetConAddrErr);
    vos_printf("创建信号量失败:         %d \r\n",g_stBbpDbgErrInfo.usCreateSemErr);
    /*lint +e534*/
    for (i = 0;i < BBP_DBG_CODER_SRC_NUM; i++)
    {
        /*lint -e534*/
        vos_printf("通道[%d]编码源空间不够的次数:    %d\r\n",i,g_stBbpDbgErrInfo.astBbpDbgSocpInfo[i].ulBuffNotEnough);
        vos_printf("通道[%d]编码源空间大小:          %d\r\n",i,g_stBbpDbgErrInfo.astBbpDbgSocpInfo[i].ulWriteBufSize);
        vos_printf("通道[%d]获取写buffer失败的次数:  %d\r\n",i,g_stBbpDbgErrInfo.astBbpDbgSocpInfo[i].ulGetWriteBuffErr);
        vos_printf("通道[%d]WriteDone失败次数:       %d\r\n",i,g_stBbpDbgErrInfo.astBbpDbgSocpInfo[i].ulWriteDoneErr);
        vos_printf("通道[%d]WriteDone成功次数:       %d\r\n",i,g_stBbpDbgErrInfo.astBbpDbgSocpInfo[i].ulWriteDoneOk);
        /*lint +e534*/
    }
}

/*****************************************************************************
* 函 数 名  : Om_BbpDumpShow
*
* 功能描述  : 打印循环链表
*
* 输入参数  :
*
* 输出参数  : 无
*
* 返 回 值  : 无
  1.日    期   : 2012年11月13日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_VOID Om_BbpDumpShow(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("分配消息空间失败:   %d\r\n", g_stBbpDumpErrInfo.usAllocMsgErr);
    vos_printf("关闭EDMA失败:       %d\r\n", g_stBbpDumpErrInfo.usCloseEdmaErr);
    vos_printf("配置EDMA失败:       %d\r\n", g_stBbpDumpErrInfo.usConfigEdmaErr);
    vos_printf("错误中断类型 :      %d\r\n", g_stBbpDumpErrInfo.usEdmaErrCode);
    vos_printf("初始化EDMA失败 :    %d\r\n", g_stBbpDumpErrInfo.usInitEdmaErr);
    vos_printf("启动EDMA失败:       %d\r\n", g_stBbpDumpErrInfo.usStartEdmaErr);
    vos_printf("停止EDMA失败:       %d\r\n", g_stBbpDumpErrInfo.usStopEdmaErr);

    vos_printf("数采EDMA通道号:     %d\r\n", g_stBbpDumpInfo.lEdmaChanID);
    vos_printf("数采状态:           %d\r\n", g_stBbpDumpInfo.usDUMPStatus);
    vos_printf("数采EDMA完成回调:   %d\r\n", g_stBbpDumpInfo.usDUMPDone);
    vos_printf("数采模式:           %d\r\n", g_stBbpDumpInfo.usDUMPMode);
    vos_printf("物理DUMP地址:       %d\r\n", g_stBbpDumpInfo.ulPhyAddr);
    vos_printf("物理DUMP大小:       %d\r\n", g_stBbpDumpInfo.ulPhySize);
    /*lint +e534*/
}

/*****************************************************************************
* 函 数 名  : Om_BbpDbgCycShow
*
* 功能描述  :
*
* 输入参数  :
*
* 输出参数  : 无
*
* 返 回 值  : 无
  1.日    期   : 2012年11月13日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_VOID Om_BbpDbgCycShow(VOS_VOID)
{
#if 0 /*defined (CHIP_BB_HI6210) 6210芯片代码，暂时保留*/
    VOS_UINT32                          i;
    BALONG_DMA_CB_S                    *pstCycBufTemp;

    pstCycBufTemp = g_pstBbpCycBufHead;

    /* 构成循环链表 */
    for (i = 0; i < BBP_DBG_CODER_SRC_NUM * BBP_DBG_NODE_NUM; i++)
    {
        /*lint -e534*/
        vos_printf("Node[%d]lli :       0x%x\r\n",i,pstCycBufTemp->lli);/* [false alarm]: 屏蔽Fortify 错误 */
        vos_printf("Node[%d]bindx :     0x%x\r\n",i,pstCycBufTemp->bindx);/* [false alarm]: 屏蔽Fortify 错误 */
        vos_printf("Node[%d]cindx :     0x%x\r\n",i,pstCycBufTemp->cindx);/* [false alarm]: 屏蔽Fortify 错误 */
        vos_printf("Node[%d]cnt1 :      0x%x\r\n",i,pstCycBufTemp->cnt1);/* [false alarm]: 屏蔽Fortify 错误 */
        vos_printf("Node[%d]cnt0 :      0x%x\r\n",i,pstCycBufTemp->cnt0);/* [false alarm]: 屏蔽Fortify 错误 */
        vos_printf("Node[%d]src_addr :  0x%x\r\n",i,pstCycBufTemp->src_addr);/* [false alarm]: 屏蔽Fortify 错误 */
        vos_printf("Node[%d]des_addr :  0x%x\r\n",i,pstCycBufTemp->des_addr);/* [false alarm]: 屏蔽Fortify 错误 */
        vos_printf("Node[%d]config :    0x%x\r\n",i,pstCycBufTemp->config);/* [false alarm]: 屏蔽Fortify 错误 */
        /*lint +e534*/
        pstCycBufTemp++;
    }
#endif
}

/*****************************************************************************
* 函 数 名  : Om_BbpBaseAddrShow
*
* 功能描述  :
*
* 输入参数  :
*
* 输出参数  : 无
*
* 返 回 值  : 无
  1.日    期   : 2012年11月13日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_VOID Om_BbpBaseAddrShow(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("GBBP_BASE_ADDR:          0x%x\r\n",SOC_BBP_GSM_ON_BASE_ADDR);
    vos_printf("WBBP_BASE_ADDR:          0x%x\r\n",WBBP_BASE_ADDR);
    vos_printf("SOC_BBP_COMM_BASE_ADDR:  0x%x\r\n",SOC_BBP_COMM_BASE_ADDR);
    vos_printf("SOC_BBP_WCDMA_BASE_ADDR: 0x%x\r\n",SOC_BBP_WCDMA_BASE_ADDR);
    /*lint +e534*/
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

