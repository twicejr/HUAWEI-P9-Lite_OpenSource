/******************************************************************************

                  版权所有 (C), 2001-2013, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMtaModemControl.c
  版 本 号   : 初稿
  作    者   : l00198894
  生成日期   : 2013年10月21日
  最近修改   :
  功能描述   : MTA模块处理Modem状态控制相关功能
  函数列表   :
  修改历史   :
  1.日    期   : 2013年10月21日
    作    者   : l00198894
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafMtaMain.h"
#include "TafMtaComm.h"
#include "TafMtaCtx.h"
#include "TafSdcCtx.h"
#include "TafSdcLib.h"
#include "MtaMtcInterface.h"
#include "PsRrmInterface.h"
#include "AtMtaInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*lint -e767 修改人: l00198894; */
#define    THIS_FILE_ID        PS_FILE_ID_TAF_MTA_MODEM_CONTROL_C
/*lint +e767 修改人: l00198894; */

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*****************************************************************************
 函 数 名  : TAF_MTA_RcvMtcPsTransferInd
 功能描述  : MTA模块收到MTC模块发的PS域迁移指示
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月21日
    作    者   : l00198894
    修改内容   : V9R1C50 SVLTE离网重选项目新增
*****************************************************************************/
VOS_VOID TAF_MTA_RcvMtcPsTransferInd(
    VOS_VOID                           *pMsg
)
{
    MTC_MTA_PS_TRANSFER_IND_STRU       *pstPsTransferIndMsg;                    /* 接收消息指针 */
    AT_APPCTRL_STRU                     stAppCtrl;
    MTA_AT_PS_TRANSFER_IND_STRU         stPsTransferInd;

    /* 初始化局部变量 */
    pstPsTransferIndMsg     = (MTC_MTA_PS_TRANSFER_IND_STRU*)pMsg;
    PS_MEM_SET(&stAppCtrl, 0, sizeof(AT_APPCTRL_STRU));
    PS_MEM_SET(&stPsTransferInd, 0, sizeof(MTA_AT_PS_TRANSFER_IND_STRU));

    /* 填写消息结构 */
    stPsTransferInd.ucCause = pstPsTransferIndMsg->ucCause;

    /* 填写事件客户端类型为广播事件 */
    stAppCtrl.usClientId    = MTA_CLIENTID_BROADCAST;

    /* 给AT模块发送ID_MTA_AT_PS_TRANSFER_IND消息 */
    TAF_MTA_SndAtMsg( &stAppCtrl,
                      ID_MTA_AT_PS_TRANSFER_IND,
                      sizeof(MTA_AT_PS_TRANSFER_IND_STRU),
                      (VOS_UINT8*)&stPsTransferInd );

    return;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_MTA_SndMipiClkInfoToAt
 功能描述  : MTA模块将^mipiclk上报给AT
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月04日
    作    者   : j00174725
    修改内容   : RF&LCD INTRUSION项目新增
*****************************************************************************/
VOS_VOID TAF_MTA_SndMipiClkInfoToAt(VOS_UINT16 usMipiClk)
{
    AT_APPCTRL_STRU                     stAppCtrl;
    MTA_AT_RF_LCD_MIPICLK_IND_STRU      stMipClkInd;
    TAF_MTA_RF_LCD_CTX_STRU            *pstMtaRfLcdCtxAddr;

    /* 初始化局部变量 */
    PS_MEM_SET(&stAppCtrl, 0, sizeof(AT_APPCTRL_STRU));
    PS_MEM_SET(&stMipClkInd, 0, sizeof(MTA_AT_RF_LCD_MIPICLK_IND_STRU));

    /* 获取MTA上下文中保存Rf&Lcd干扰规避上下文地址 */
    pstMtaRfLcdCtxAddr = TAF_MTA_GetRfLcdCtxAddr();

    /* 填写消息结构 */
    stMipClkInd.usMipiClk = usMipiClk;

    /* 填写事件客户端类型为广播事件 */
    stAppCtrl.usClientId    = MTA_CLIENTID_BROADCAST;

    /* 给AT模块发送ID_MTA_AT_PS_TRANSFER_IND消息 */
    TAF_MTA_SndAtMsg( &stAppCtrl,
                      ID_MTA_AT_MIPICLK_INFO_IND,
                      sizeof(MTA_AT_RF_LCD_MIPICLK_IND_STRU),
                      (VOS_UINT8*)&stMipClkInd );

    /* 保存上报的MipiClk值 */
    pstMtaRfLcdCtxAddr->usReportMipiClk= usMipiClk;

    if (0 != pstMtaRfLcdCtxAddr->usReportMipiClk)
    {
        /* 在上报的为有效值时，启动定时器 */
        (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_RF_LCD_MIPI_CLK_REPORT, pstMtaRfLcdCtxAddr->ulTimerInterVal);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_GetMipiClkRptCtl
 功能描述  : 获取MipiClk主动上报控制
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月04日
    作    者   : j00174725
    修改内容   : RF&LCD INTRUSION项目新增
*****************************************************************************/
VOS_UINT32 TAF_MTA_GetMipiClkRptCtl(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl      = VOS_NULL_PTR;
    VOS_UINT32                          ulChkCurcRptFlg;

    /* 判断当前主动上报是否关闭 */
    pstCurcRptCtrl  = TAF_SDC_GetCurcRptCtrl();
    ulChkCurcRptFlg = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_MIPICLK);

    return ulChkCurcRptFlg;

}


/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiMipiClkExpired
 功能描述  : MTA模块MipiClk主动上报命令超时处理函数
 输入参数  : pMsg    -- 超时消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月04日
    作    者   : j00174725
    修改内容   : RF&LCD INTRUSION项目新增
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiMipiClkExpired(VOS_VOID *pMsg)
{
    TAF_MTA_RF_LCD_CTX_STRU            *pstMtaRfLcdCtxAddr  = VOS_NULL_PTR;
    VOS_UINT32                          ulChkCurcRptFlg;

    /* 获取MTA上下文中保存Rf&Lcd干扰规避上下文地址 */
    pstMtaRfLcdCtxAddr = TAF_MTA_GetRfLcdCtxAddr();

    if(pstMtaRfLcdCtxAddr->usNewMipiClk == pstMtaRfLcdCtxAddr->usReportMipiClk)
    {
        return;
    }

    ulChkCurcRptFlg = TAF_MTA_GetMipiClkRptCtl();
    if (VOS_FALSE == ulChkCurcRptFlg)
    {
        return;
    }

    /* 上报mipiclk */
    TAF_MTA_SndMipiClkInfoToAt(pstMtaRfLcdCtxAddr->usNewMipiClk);

    return;

}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvMtcMipiClkInfoInd
 功能描述  : MTA模块收到MTC模块发的MipiClk上报指示
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月04日
    作    者   : j00174725
    修改内容   : RF&LCD INTRUSION项目新增
*****************************************************************************/
VOS_VOID TAF_MTA_RcvMtcMipiClkInfoInd(VOS_VOID *pMsg)
{
    MTC_MTA_MIPICLK_INFO_IND_STRU      *pstMipiClkIndMsg    = VOS_NULL_PTR;
    TAF_MTA_RF_LCD_CTX_STRU            *pstMtaRfLcdCtxAddr  = VOS_NULL_PTR;
    VOS_UINT32                          ulChkCurcRptFlg;
    TAF_MTA_TIMER_STATUS_ENUM_UINT8     enStatus;

    /* 获取MTA上下文中保存Rf&Lcd干扰规避上下文地址 */
    pstMtaRfLcdCtxAddr                  = TAF_MTA_GetRfLcdCtxAddr();

    /* 初始化局部变量 */
    pstMipiClkIndMsg                    = (MTC_MTA_MIPICLK_INFO_IND_STRU *)pMsg;

    /* 保存最新上报的mipiclk值 */
    pstMtaRfLcdCtxAddr->usNewMipiClk    = pstMipiClkIndMsg->usMipiCLk;

    /* 定时器是否在运行 */
    enStatus = TAF_MTA_GetTimerStatus(TI_TAF_MTA_RF_LCD_MIPI_CLK_REPORT);
    if (TAF_MTA_TIMER_STATUS_RUNING == enStatus)
    {
        return;
    }

    /* 新上报的MipiClk与之前上报的 mipiclk值比较 */
    if (pstMtaRfLcdCtxAddr->usNewMipiClk == pstMtaRfLcdCtxAddr->usReportMipiClk)
    {
        return;
    }

    /* 判断当前主动上报是否关闭 */
    ulChkCurcRptFlg = TAF_MTA_GetMipiClkRptCtl();
    if (VOS_FALSE == ulChkCurcRptFlg)
    {
        return;
    }

    /* 给AT模块发送消息 */
    TAF_MTA_SndMipiClkInfoToAt(pstMtaRfLcdCtxAddr->usNewMipiClk);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtQryMipiClkReq
 功能描述  : mta收到ID_AT_MTA_MIPI_CLK_REQ消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月04日
    作    者   : j00174725
    修改内容   : RF&LCD INTRUSION项目新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtQryMipiClkReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                    *pstAtMtaMsg         = VOS_NULL_PTR;
    TAF_MTA_RF_LCD_CTX_STRU            *pstMtaRfLcdCtx      = VOS_NULL_PTR;
    MTA_AT_RF_LCD_MIPICLK_CNF_STRU      stQryMipiCnf;
    TAF_MTA_TIMER_STATUS_ENUM_UINT8     enStatus;

    pstAtMtaMsg             = (AT_MTA_MSG_STRU *)pMsg;

    /* 获取MTA里Rf&Lcd上下文 */
    pstMtaRfLcdCtx          = TAF_MTA_GetRfLcdCtxAddr();

    /* 判断当前定时器状态 */
    enStatus = TAF_MTA_GetTimerStatus(TI_TAF_MTA_RF_LCD_MIPI_CLK_REPORT);
    if (TAF_MTA_TIMER_STATUS_RUNING == enStatus)
    {
        TAF_MTA_StopTimer(TI_TAF_MTA_RF_LCD_MIPI_CLK_REPORT);
    }

    /* 填充消息内容 */
    PS_MEM_SET(&stQryMipiCnf, 0x00, sizeof(stQryMipiCnf));
    stQryMipiCnf.usMipiClk      = pstMtaRfLcdCtx->usNewMipiClk;
    stQryMipiCnf.usResult       = VOS_OK;

    /* 如果该特性未开启，则给上层回复失败 */
    if (0 == pstMtaRfLcdCtx->usEnableBitMap)
    {
        stQryMipiCnf.usResult   = VOS_ERR;
    }
    else
    {
        /* 开启定时器 */
        (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_RF_LCD_MIPI_CLK_REPORT, pstMtaRfLcdCtx->ulTimerInterVal);

        /* 保存上报MIPICLK值 */
        pstMtaRfLcdCtx->usReportMipiClk = pstMtaRfLcdCtx->usNewMipiClk;
    }

    /* 给AT发送查询MIPICLK回复 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)&(pstAtMtaMsg->stAppCtrl),
                     ID_MTA_AT_MIPICLK_QRY_CNF,
                     sizeof(stQryMipiCnf),
                     (VOS_UINT8*)&stQryMipiCnf);

    return;
}


#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 函 数 名  : TAF_MTA_SndRrmProtectPsInd
 功能描述  : MTA向RRM发送ID_PS_RRM_PROTECT_PS_IND消息
 输入参数  : enRrmPsRatType - RRM PS RAT类型
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2013年3月25日
    作    者   : y00176023
    修改内容   : 支持AT^PSPROTECTMODE
*****************************************************************************/
VOS_UINT32 TAF_MTA_SndRrmProtectPsInd(VOS_VOID)
{
     VOS_UINT32                         ulResult;
     VOS_UINT32                         ulLength;
     MODEM_ID_ENUM_UINT16               enModemId;
     PS_RRM_PROTECT_PS_IND_STRU        *pstMtaRrmProtectPsInd = VOS_NULL_PTR;

     enModemId            = VOS_GetModemIDFromPid(UEPS_PID_MTA);

     if (enModemId == MODEM_ID_BUTT)
     {
        MTA_ERROR_LOG("TAF_MTA_SndRrmProtectPsInd: illegal modem id or rrm rat type!");
        return VOS_ERR;
     }
     /* 申请消息结构内存 */
     ulLength               = sizeof(PS_RRM_PROTECT_PS_IND_STRU) - VOS_MSG_HEAD_LENGTH;
     pstMtaRrmProtectPsInd  = (PS_RRM_PROTECT_PS_IND_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
     if (VOS_NULL_PTR == pstMtaRrmProtectPsInd)
     {
         MTA_ERROR_LOG("TAF_MTA_SndRrmProtectPsInd: Alloc msg fail!");
         return VOS_ERR;
     }

     /* 构造消息结构体 */
     pstMtaRrmProtectPsInd->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
     pstMtaRrmProtectPsInd->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
     pstMtaRrmProtectPsInd->stMsgHeader.ulReceiverPid     = UEPS_PID_RRM;
     pstMtaRrmProtectPsInd->stMsgHeader.ulMsgName         = ID_PS_RRM_PROTECT_PS_IND;
     pstMtaRrmProtectPsInd->enModemId                     = enModemId;

     PS_MEM_SET(pstMtaRrmProtectPsInd->aucReserved, 0x0, sizeof(pstMtaRrmProtectPsInd->aucReserved));

     /* 发送Protect消息到RRM */
     ulResult = PS_SEND_MSG(UEPS_PID_MTA, pstMtaRrmProtectPsInd);

     if (VOS_OK != ulResult)
     {
         MTA_ERROR_LOG("TAF_MTA_SndRrmProtectPsInd: Send msg fail!");
     }

     return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndRrmDeProtectPsInd
 功能描述  : MTA向RRM发送ID_PS_RRM_DEPROTECT_PS_IND消息
 输入参数  : enRrmPsRatType - RRM PS RAT类型
 输出参数  : 无
 返 回 值  : VOS_UINT32 - 发送结果
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2013年3月25日
    作    者   : y00176023
    修改内容   : 支持AT^PSPROTECTMODE
*****************************************************************************/
VOS_UINT32 TAF_MTA_SndRrmDeProtectPsInd(VOS_VOID)
{
     VOS_UINT32                         ulResult;
     VOS_UINT32                         ulLength;
     MODEM_ID_ENUM_UINT16               enModemId;
     PS_RRM_DEPROTECT_PS_IND_STRU      *pstMtaRrmDeProtectPsInd = VOS_NULL_PTR;

     enModemId            = VOS_GetModemIDFromPid(UEPS_PID_MTA);

     if (enModemId == MODEM_ID_BUTT)
     {
        MTA_ERROR_LOG("TAF_MTA_SndRrmDeProtectPsInd: illegal modem id or rrm rat type!");
        return VOS_ERR;
     }

     /* 申请消息结构内存 */
     ulLength              = sizeof(PS_RRM_DEPROTECT_PS_IND_STRU) - VOS_MSG_HEAD_LENGTH;
     pstMtaRrmDeProtectPsInd  = (PS_RRM_DEPROTECT_PS_IND_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
     if (VOS_NULL_PTR == pstMtaRrmDeProtectPsInd)
     {
         MTA_ERROR_LOG("TAF_MTA_SndDeRrmProtectPsInd: Alloc msg fail!");
         return VOS_ERR;
     }

     /* 构造消息结构体 */
     pstMtaRrmDeProtectPsInd->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
     pstMtaRrmDeProtectPsInd->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
     pstMtaRrmDeProtectPsInd->stMsgHeader.ulReceiverPid     = UEPS_PID_RRM;
     pstMtaRrmDeProtectPsInd->stMsgHeader.ulMsgName         = ID_PS_RRM_DEPROTECT_PS_IND;
     pstMtaRrmDeProtectPsInd->enModemId                     = enModemId;

     PS_MEM_SET(pstMtaRrmDeProtectPsInd->aucReserved, 0x0, sizeof(pstMtaRrmDeProtectPsInd->aucReserved));

     /* 发送DeProtect消息到RRM */
     ulResult = PS_SEND_MSG(UEPS_PID_MTA, pstMtaRrmDeProtectPsInd);

     if (VOS_OK != ulResult)
     {
         MTA_ERROR_LOG("TAF_MTA_SndRrmDeProtectPsInd: Send msg fail!");
     }

     return ulResult;

}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndRrmProtectPsType
 功能描述  : MTA向RRM发送ID_PS_RRM_DEPROTECT_PS_IND消息
 输入参数  : usRrmPsProtectType - RRM PS protect类型
 输出参数  : 无
 返 回 值  : VOS_UINT32 - 发送结果
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2013年4月3日
    作    者   : y00176023
    修改内容   : 支持AT^PSPROTECTMODE
*****************************************************************************/
VOS_UINT32 TAF_MTA_SndRrmPsProtectType(
    PS_BOOL_ENUM_UINT8                  usRrmPsProtectType
)
{
    if (PS_TRUE == usRrmPsProtectType)
    {
        TAF_MTA_SndRrmProtectPsInd();
    }
    else
    {
        TAF_MTA_SndRrmDeProtectPsInd();
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_MTA_SndAsPsProtectIndMsg
 功能描述  : MTA向接入层发送ID_MTA_RRC_PROTECT_PS_IND消息
 输入参数  : ulReceiverPid - 接收方pid
             ucProtectFlg  - 保护标志
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2013年3月25日
    作    者   : y00176023
    修改内容   : 支持AT^PSPROTECTMODE
*****************************************************************************/
VOS_UINT32 TAF_MTA_SndAsPsProtectIndMsg(
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT8                           ucProtectFlg
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulLength;
    MTA_RRC_PROTECT_PS_IND_STRU        *pstMtaAsPsProtectInd = VOS_NULL_PTR;

    /* 申请消息结构内存 */
    ulLength              = sizeof(MTA_RRC_PROTECT_PS_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaAsPsProtectInd  = (MTA_RRC_PROTECT_PS_IND_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
    if (VOS_NULL_PTR == pstMtaAsPsProtectInd)
    {
        MTA_ERROR_LOG("TAF_MTA_SndAsPsProtectIndMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    /* 构造消息结构体 */
    pstMtaAsPsProtectInd->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaAsPsProtectInd->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaAsPsProtectInd->stMsgHeader.ulReceiverPid     = ulReceiverPid;
    pstMtaAsPsProtectInd->stMsgHeader.ulMsgName         = ID_MTA_RRC_PROTECT_PS_IND;
    pstMtaAsPsProtectInd->enProtectFlg                  = ucProtectFlg;

    PS_MEM_SET(pstMtaAsPsProtectInd->aucRsv, 0x0, sizeof(pstMtaAsPsProtectInd->aucRsv));

    /* 发送消息到AS */
    ulResult = PS_SEND_MSG(UEPS_PID_MTA, pstMtaAsPsProtectInd);

    if (VOS_OK != ulResult)
    {
        MTA_ERROR_LOG("TAF_MTA_SndAsPsProtectIndMsg: Send msg fail!");
    }

    return ulResult;
}


/*****************************************************************************
 函 数 名  : TAF_MTA_SndAtSetPsProtectCnf
 功能描述  : MTA处理^PSPROTECTMODE消息后给AT模块回消息
 输入参数  : AT_MTA_MSG_STRU   *pstAtMtaReqMsg   AT给MTA发送的消息
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2013年3月25日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目新增函数
*****************************************************************************/
VOS_VOID TAF_MTA_SndAtSetPsProtectCnf(
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg,
    AT_MTA_MSG_TYPE_ENUM_UINT32         enErr
)
{
    MTA_AT_RRC_PROTECT_PS_CNF_STRU           stMtaAtPortectPSCnf;

    /* 发送结果给AT模块 */
    stMtaAtPortectPSCnf.enResult = enErr;

    TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                      ID_MTA_AT_RRC_PROTECT_PS_CNF,
                      sizeof(MTA_AT_RRC_PROTECT_PS_CNF_STRU),
                      (VOS_UINT8*)&stMtaAtPortectPSCnf );

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtPsProtectSetReq
 功能描述  : MTA模块收到AT发来的ID_AT_MTA_RRC_PROTECT_PS_REQ请求消息的处理函数
 输入参数  : pMsg   -- AT发送的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月25日
    作    者   : y00176023
    修改内容   : 新增^PSPROTECTMODE命令
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtPsProtectSetReq(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT32                                              i;
    PS_BOOL_ENUM_UINT8                                      ucPsProtectMode;
    AT_MTA_MSG_STRU                                        *pstAtMtaReqMsg     = VOS_NULL_PTR;
    TAF_SDC_PLATFORM_RAT_CAP_STRU                          *pstPlatformRatCap  = VOS_NULL_PTR;
    AT_MTA_RRC_PROTECT_PS_REQ_STRU                         *pstPsProtectMode   = VOS_NULL_PTR;


    pstPlatformRatCap = TAF_SDC_GetPlatformRatCap();
    pstAtMtaReqMsg    = (AT_MTA_MSG_STRU*)pMsg;
    pstPsProtectMode  = (AT_MTA_RRC_PROTECT_PS_REQ_STRU*)pstAtMtaReqMsg->aucContent;
    ucPsProtectMode   = pstPsProtectMode->enPsProtectFlg;

    /* 根据保护模式类型向RRM发送注册、去注册消息 */
    TAF_MTA_SndRrmPsProtectType(ucPsProtectMode);

    /* LTE是否在平台接入技术能力列表中 */
    for (i = 0 ; i < pstPlatformRatCap->ucRatNum; i++)
    {
        if (TAF_SDC_PLATFORM_RAT_GSM == pstPlatformRatCap->aenRatList[i])
        {
            /* 通知AS protect PS消息 */
            TAF_MTA_SndAsPsProtectIndMsg(UEPS_PID_GAS, ucPsProtectMode);
        }
 #if (FEATURE_ON == FEATURE_LTE)
        else if (TAF_SDC_PLATFORM_RAT_LTE == pstPlatformRatCap->aenRatList[i])
        {
            /* 通知AS protect PS消息 */
            TAF_MTA_SndAsPsProtectIndMsg(PS_PID_ERRC, ucPsProtectMode);
        }
#endif
        else if (TAF_SDC_PLATFORM_RAT_WCDMA == pstPlatformRatCap->aenRatList[i])
        {
            /* 通知AS protect PS消息 */
            TAF_MTA_SndAsPsProtectIndMsg(WUEPS_PID_WRR, ucPsProtectMode);
        }
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
        else if (TAF_SDC_PLATFORM_RAT_TDS == pstPlatformRatCap->aenRatList[i])
        {
            /* 通知AS protect PS消息 */
            TAF_MTA_SndAsPsProtectIndMsg(TPS_PID_RRC, ucPsProtectMode);
        }
#endif
        else
        {
            ;
        }
    }

    /*给AT发送成功*/
    TAF_MTA_SndAtSetPsProtectCnf(pstAtMtaReqMsg, MTA_AT_RESULT_NO_ERROR);
}

#endif

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


