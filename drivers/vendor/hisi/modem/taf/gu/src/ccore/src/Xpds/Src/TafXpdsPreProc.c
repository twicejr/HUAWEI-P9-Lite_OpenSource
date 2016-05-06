/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsPreProc.c
  版 本 号   : 初稿
  作    者   : g00256031
  生成日期   : 2015年08月26日
  功能描述   : XPDS预状态机事件处理函数
  函数列表   :
  修改历史   :
  1.日    期   : 2015年08月26日
    作    者   : g00256031
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXpdsPreProc.h"
#include "TafXpdsCtx.h"
#include "TafSdcCtx.h"
#include "TafXpdsSndAt.h"
#include "TafXpdsMntn.h"
#include "TafXpdsDecode.h"
#include "TafXpdsSndInternalMsg.h"
#include "TafXpdsSndCas.h"
#include "TafXpdsXsmsInterface.h"
#include "TafXpdsSndXsms.h"
#include "TafXpdsFsmPdeProc.h"
#include "TafXpdsFsmMainTbl.h"
#include "TafXpdsCommFunc.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XPDS_PRE_PROC_C

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
TAF_XPDS_DOWN_DATA_CTRL_STRU g_stTafXpdsDownCtrlPreProc = {0};


/*****************************************************************************
  3 函数定义
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtGpsStartReq_PreProc
 功能描述  : 预处理^CAGPSSTART命令
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtGpsStartReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_GPS_START_REQ_STRU         *pstMsgStartReq;
    XPDS_AT_RESULT_CNF_STRU             stStartCnf;
    VOS_UINT32                          ulCurState;

    ulCurState = TAF_XPDS_GetFsmTopState();

    /* 当前在初始化状态则交给初始化状态机处理 */
    if ((TAF_XPDS_FSM_L1_MAIN == TAF_XPDS_GetCurrFsmId())
     && (TAF_XPDS_L1_STA_INIT == ulCurState))
    {
        return VOS_FALSE;
    }

    /* 局部变量初始化 */
    pstMsgStartReq  = (AT_XPDS_GPS_START_REQ_STRU *)pstMsg;

    /* 默认回复失败 */
    PS_MEM_SET(&stStartCnf, 0x0, sizeof(stStartCnf));
    stStartCnf.enResult = XPDS_AT_RESULT_ERROR;

    TAF_XPDS_SndAtMsg(&pstMsgStartReq->stAppCtrl,
                      ID_XPDS_AT_GPS_START_CNF,
                      sizeof(stStartCnf),
                      (VOS_UINT8*)&stStartCnf);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtGpsCfgMpcAddrReq_PreProc
 功能描述  : 预处理^CAGPSCFGMPCADDR命令
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtGpsCfgMpcAddrReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_GPS_CFG_MPC_ADDR_REQ_STRU  *pstMsgCfgMpcAddReq;
    XPDS_AT_RESULT_CNF_STRU             stMpcAddrCnf;
    VOS_UINT32                          ulCurState;

    ulCurState = TAF_XPDS_GetFsmTopState();

    /* 当前在初始化状态则交给初始化状态机处理 */
    if ((TAF_XPDS_FSM_L1_MAIN == TAF_XPDS_GetCurrFsmId())
     && (TAF_XPDS_L1_STA_INIT == ulCurState))
    {
        return VOS_FALSE;
    }

    /* 局部变量初始化 */
    pstMsgCfgMpcAddReq  = (AT_XPDS_GPS_CFG_MPC_ADDR_REQ_STRU *)pstMsg;

    /* 消息处理成功，给AT回复成功 */
    PS_MEM_SET(&stMpcAddrCnf, 0x0, sizeof(stMpcAddrCnf));
    stMpcAddrCnf.enResult = XPDS_AT_RESULT_ERROR;

    TAF_XPDS_SndAtMsg(&pstMsgCfgMpcAddReq->stAppCtrl,
                     ID_XPDS_AT_GPS_CFG_MPC_ADDR_CNF,
                     sizeof(stMpcAddrCnf),
                     (VOS_UINT8*)&stMpcAddrCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtGpsCfgPdeAddrReq_PreProc
 功能描述  : 预处理^CAGPSCFGPDEADDR命令
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtGpsCfgPdeAddrReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_GPS_CFG_PDE_ADDR_REQ_STRU  *pstAMsgCfgPdeAddrReq;
    XPDS_AT_RESULT_CNF_STRU             stPdeAddrCnf;
    VOS_UINT32                          ulCurState;

    ulCurState = TAF_XPDS_GetFsmTopState();

    /* 当前在初始化状态则交给初始化状态机处理 */
    if ((TAF_XPDS_FSM_L1_MAIN == TAF_XPDS_GetCurrFsmId())
     && (TAF_XPDS_L1_STA_INIT == ulCurState))
    {
        return VOS_FALSE;
    }

    /* 局部变量初始化 */
    pstAMsgCfgPdeAddrReq  = (AT_XPDS_GPS_CFG_PDE_ADDR_REQ_STRU *)pstMsg;

    PS_MEM_SET(&stPdeAddrCnf, 0x0, sizeof(stPdeAddrCnf));
    stPdeAddrCnf.enResult = XPDS_AT_RESULT_ERROR;

    /* 消息处理完成，给AT回复结果 */
    TAF_XPDS_SndAtMsg(&pstAMsgCfgPdeAddrReq->stAppCtrl,
                     ID_XPDS_AT_GPS_CFG_PDE_ADDR_CNF,
                     sizeof(stPdeAddrCnf),
                     (VOS_UINT8*)&stPdeAddrCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtGpsCfgPositionModeReq_PreProc
 功能描述  : 预处理^CAGPSCFGPOSMODE命令
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtGpsCfgPositionModeReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_GPS_CFG_POSITION_MODE_REQ_STRU                 *pstMsgCfgPosModeReq;
    XPDS_AT_RESULT_CNF_STRU                                 stCfgModeCnf;
    VOS_UINT32                                              ulCurState;

    ulCurState = TAF_XPDS_GetFsmTopState();

    /* 当前在初始化状态则交给初始化状态机处理 */
    if ((TAF_XPDS_FSM_L1_MAIN == TAF_XPDS_GetCurrFsmId())
     && (TAF_XPDS_L1_STA_INIT == ulCurState))
    {
        return VOS_FALSE;
    }

    /* 局部变量初始化 */
    PS_MEM_SET(&stCfgModeCnf, 0x0, sizeof(stCfgModeCnf));
    stCfgModeCnf.enResult = XPDS_AT_RESULT_ERROR;

    pstMsgCfgPosModeReq  = (AT_XPDS_GPS_CFG_POSITION_MODE_REQ_STRU* )pstMsg;

    /* 消息处理完成，给AT回复结果 */
    TAF_XPDS_SndAtMsg(&pstMsgCfgPosModeReq->stAppCtrl,
                     ID_XPDS_AT_GPS_CFG_MODE_CNF,
                     sizeof(stCfgModeCnf),
                     (VOS_UINT8*)&stCfgModeCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtGpsQryRefLocInfoReq_PreProc
 功能描述  : 预处理^CAGPSCFGPOSMODE命令
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtGpsQryRefLocInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_GPS_QRY_REFLOC_INFO_REQ_STRU                   *pstMsgQryRefLocReq;
    XPDS_AT_GPS_REFLOC_INFO_STRU                            stXpdsAtRefloc;
    TAF_SDC_1X_SYS_INFO_STRU                               *pst1XSys;
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enSysMode;

    /* 局部变量初始化 */
    pstMsgQryRefLocReq  = (AT_XPDS_GPS_QRY_REFLOC_INFO_REQ_STRU*)pstMsg;

    PS_MEM_SET(&stXpdsAtRefloc, 0, sizeof(XPDS_AT_GPS_REFLOC_INFO_STRU));
    stXpdsAtRefloc.ucValidRefLoc = 0; /* 0: Not valid */

    enSysMode = TAF_SDC_GetSysMode();

    if ((TAF_SDC_SYS_MODE_CDMA_1X == enSysMode)
     || (TAF_SDC_SYS_MODE_HYBRID == enSysMode))
    {
        /* 2: Valid Time Zone and BS Location. */
        stXpdsAtRefloc.ucValidRefLoc = 2;

        pst1XSys = TAF_SDC_Get1xSysInfo();

        stXpdsAtRefloc.usSid       = (VOS_UINT16)pst1XSys->lSid;
        stXpdsAtRefloc.usNid       = (VOS_UINT16)pst1XSys->lNid;
        stXpdsAtRefloc.usBsid      = (VOS_UINT16)pst1XSys->stBaseStationInfo.usBaseId;

        /* stReflocCnf.ulTzLat, stReflocCnf.ulTzLong目前设置为0 */
        stXpdsAtRefloc.ulTzLat     = 0;
        stXpdsAtRefloc.ulTzLong    = 0;

        stXpdsAtRefloc.ulBslat     = (VOS_UINT32)pst1XSys->stBaseStationInfo.lBaseLatitude;
        stXpdsAtRefloc.ulBslong    = (VOS_UINT32)pst1XSys->stBaseStationInfo.lBaseLongitude;
    }

    TAF_XPDS_SndAtGpsReflocInfoCnf(&(pstMsgQryRefLocReq->stAppCtrl), &stXpdsAtRefloc);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtGpsQryTimeInfoReq_PreProc
 功能描述  : 预处理收到AT发来的ID_AT_XPDS_SYNC_TIME_REQ消息处理函数
 输入参数  : pstMsg  -- 消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月10日
    作    者   : d00212987
    修改内容   : AGPS迭代1新增
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtGpsQryTimeInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_GPS_QRY_TIME_INFO_REQ_STRU *pstMsgQryTimeReq;
    AT_XPDS_REPLY_SYNC_TIME_ENUM_UINT8  enSyncTimeActionType;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;
    VOS_UINT32                          ulCurState;

    /* 局部变量初始化 */
    pstMsgQryTimeReq  = (AT_XPDS_GPS_QRY_TIME_INFO_REQ_STRU *)pstMsg;

    enSyncTimeActionType = pstMsgQryTimeReq->enActionType;

    ulCurState = TAF_XPDS_GetFsmTopState();

    /* 保存交互通道的ClientId */
    TAF_XPDS_SetGpsClientId(pstMsgQryTimeReq->stAppCtrl.usClientId);

    /* 当前在初始化状态则交给初始化状态机处理 */
    if ((TAF_XPDS_FSM_L1_MAIN == TAF_XPDS_GetCurrFsmId())
     && (TAF_XPDS_L1_STA_INIT == ulCurState)
     && (AT_XPDS_REPLY_SYNC_TIME_AND_ASSIST_DATA == enSyncTimeActionType))
    {
        return VOS_FALSE;
    }

    if ((AT_XPDS_REPLY_SYNC_TIME_INFO            == enSyncTimeActionType)
     || (AT_XPDS_REPLY_SYNC_TIME_AND_ASSIST_DATA == enSyncTimeActionType))
    {
        enSysMode = TAF_SDC_GetSysMode();

        TAF_XPDS_SndCasSyncTimeReq(enSysMode);

        return VOS_TRUE;
    }

    if (AT_XPDS_REPLY_FORCE_SYNC_TIME == enSyncTimeActionType)
    {
        /* 管脚虚焊检测，强制触发脉冲，获取synctime */
        TAF_XPDS_SndCasSyncTimeReq(TAF_SDC_SYS_MODE_BUTT);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtApServerBindStatusInd_PreProc
 功能描述  : 预处理状态收到AP发送而来的服务器Bind Cnf的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月8日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtApServerBindStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU *pstMsgBindStatusInd;

    pstMsgBindStatusInd = (AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU *)pstMsg;

    if (TAF_XPDS_FSM_LINK_CTRL == TAF_XPDS_GetCurrFsmId())
    {
        /* 需要进入建链状态机进一步处理 */
        return VOS_FALSE;
    }

    if (AT_XPDS_SERVER_MODE_MPC == pstMsgBindStatusInd->enServerMode)
    {
        /* 更新MPC当前链路状态 */
        TAF_XPDS_SetMpcServerStatus(pstMsgBindStatusInd->enBindStatus);

        /* MPC数据交互状态机中，收到Server异常断链的处理 */
        if ((TAF_XPDS_FSM_MPC_PROC == TAF_XPDS_GetCurrFsmId())
         && (AT_XPDS_SERVER_BIND_STATUS_IDLE == pstMsgBindStatusInd->enBindStatus))
        {
            TAF_XPDS_SndInternalAbnormalAbortAgpsSessionInd(TAF_XPDS_PROC_RSLT_UP_MPC_DISCONNECT);
        }
    }

    if (AT_XPDS_SERVER_MODE_PDE == pstMsgBindStatusInd->enServerMode)
    {
        /* 更新PDE当前链路状态 */
        TAF_XPDS_SetPdeServerStatus(pstMsgBindStatusInd->enBindStatus);

        /* PDE数据交互状态机中，收到Server异常断链的处理 */
        if ((TAF_XPDS_FSM_PDE_PROC == TAF_XPDS_GetCurrFsmId())
         && (AT_XPDS_SERVER_BIND_STATUS_IDLE == pstMsgBindStatusInd->enBindStatus))
        {
            TAF_XPDS_SndInternalAbnormalAbortAgpsSessionInd(TAF_XPDS_PROC_RSLT_UP_PDE_DISCONNECT);
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtGpsStopReq_PreProc
 功能描述  : 收到用户Stop Agps流程的预处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月9日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtGpsStopReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_SndInternalAbnormalAbortAgpsSessionInd(TAF_XPDS_PROC_RSLT_AT_STOP);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvCasTimeSyncInd_PreProc
 功能描述  : XPDS收到Cas获取Sync Timer结果
 输入参数  : pMsg : CAS上报sync time结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月10日
    作    者   : d00212987
    修改内容   : AGPS迭代1新增
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvCasTimeSyncInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_XPDS_TIME_SYNC_IND_STRU        *pstRcvSyncTime = VOS_NULL_PTR;

    pstRcvSyncTime = (CAS_XPDS_TIME_SYNC_IND_STRU*)pstMsg;

    TAF_XPDS_SndAtGpsTimeSyncInfo(pstRcvSyncTime);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvCasRefLocInd
 功能描述  : XPDS收到CAS获取位置信息通知
 输入参数  : pMsg : CAS上报参考位置IND消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月10日
    作    者   : d00212987
    修改内容   : AGPS迭代1新增
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvCasRefLocInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_XPDS_REF_LOC_IND_STRU                         *pstRefLocInd;
    TAF_XPDS_CAS_RPT_PILOT_BUFF_STRU                  *pstCasRptPilotBuff;
    TAF_XPDS_REVLINK_RSP_PILOT_PHASE_MEAS_STRU        *pstProvPp;
    VOS_UINT8                                          ucPilotStrgth;
    VOS_UINT32                                         ulIndex = 0;
    VOS_UINT32                                         ulTempCount = 0;
    VOS_UINT16                                         i;

    pstProvPp = &(TAF_XPDS_GetPublicDataAddr()->stPilotInfo);

    pstCasRptPilotBuff = &(pstProvPp->stCasRptPilotBuff);

    /* 存储上报pilot参数 */
    pstRefLocInd = (CAS_XPDS_REF_LOC_IND_STRU*)pstMsg;

    if (XPDS_CAS_MAX_NEIGHBOR_NUM < pstRefLocInd->usPilotNum)
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvCasRefLocInd_PreProc: PilotNum > 50!");

        pstRefLocInd->usPilotNum   = XPDS_CAS_MAX_NEIGHBOR_NUM;
    }

    /* 存除pilot外变量 */
    pstProvPp->ulTimeRefMS          = pstRefLocInd->ulMsRefTime;
    pstProvPp->sMobSysTOffst        = pstRefLocInd->sMsSysTimeOffset;
    pstProvPp->usRefPn              = pstRefLocInd->usRefPN;

    pstProvPp->ucRefPilotStrgth     = TAF_XPDS_FormatPnStrength(pstRefLocInd->sRefPnStrength);

    pstProvPp->ucBandClass          = (VOS_UINT8)pstRefLocInd->usBandClass;
    pstProvPp->usCdmaFreq           = pstRefLocInd->usCdmaFreq;

    pstProvPp->usBaseId             = TAF_SDC_Get1xBaseId();
    pstProvPp->usSID                = (VOS_UINT16)TAF_SDC_Get1xSid();
    pstProvPp->usNID                = (VOS_UINT16)TAF_SDC_Get1xNid();

    /* CAS上报是1/8精度 */
    pstProvPp->ucTotalRxPow         = TAF_XPDS_FormatServFreqRssi(pstRefLocInd->sServFreqRssi);

    pstProvPp->ucNumOfPilotP        = (VOS_UINT8)pstRefLocInd->usPilotNum;

    /* 按照协议该字段的取值在1/16下是-512到511.9375,超出此范围设置无效 */
    if ((-8192 > pstProvPp->sMobSysTOffst) || (8191 < pstProvPp->sMobSysTOffst))
    {
        pstProvPp->ucOffsetIncl = 0; /* 设置该值无效 */
    }
    else
    {
        pstProvPp->ucOffsetIncl = 1;
    }

    /* 存储pilot measure */
    for (i=0; i<pstRefLocInd->usPilotNum; i++)
    {
#if 0
        if (   ( 0 != pstRefLocInd->stPilotMeasInfo[i].usPilotPN)
            && ( 8 != pstRefLocInd->stPilotMeasInfo[i].usPilotPN)
            && ( 16 != pstRefLocInd->stPilotMeasInfo[i].usPilotPN)
            )
        {
            continue;
        }
#endif
        ucPilotStrgth = TAF_XPDS_FormatPnStrength(pstRefLocInd->stPilotMeasInfo[i].sPnStrength);

        /* 把最后一次上报前10个能量强度最强的作为上报参考计算值 */
        if (TAF_XPDS_RL_PHASE_PILREC_MAX > ulTempCount)
        {
            pstProvPp->astPilotRec[ulTempCount].ucPilotStrgth  = ucPilotStrgth;
            pstProvPp->astPilotRec[ulTempCount].usPilotPN      = pstRefLocInd->stPilotMeasInfo[i].usPilotPN;
            pstProvPp->astPilotRec[ulTempCount].ulPilotPnPhase = pstRefLocInd->stPilotMeasInfo[i].ulPnPhase;

            ulTempCount++;
        }

        /* 只存放CAS最后上报的4s数据 */
        ulIndex = pstCasRptPilotBuff->ulPilotMeasNum % TAF_XPDS_PILOT_MEAS_BUFF_MAX;

        /* 加入全局变量中 */
        pstCasRptPilotBuff->astPilotMeasInfo[ulIndex].usPilotPN   = pstRefLocInd->stPilotMeasInfo[i].usPilotPN;
        pstCasRptPilotBuff->astPilotMeasInfo[ulIndex].sPnStrength = ucPilotStrgth;
        pstCasRptPilotBuff->astPilotMeasInfo[ulIndex].ulPnPhase   = pstRefLocInd->stPilotMeasInfo[i].ulPnPhase;

        pstCasRptPilotBuff->ulPilotMeasNum++;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_CheckForwardData_PreProc
 功能描述  : 检查MPC/PDE下行数据
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : C00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_CheckForwardData_PreProc(
    AT_XPDS_AP_FORWARD_DATA_IND_STRU   *pstDownDataInd
)
{
    TAF_XPDS_UP_LINK_STATUS_ENUM_UINT8  enCurUpLinkStatus;

    enCurUpLinkStatus = TAF_XPDS_GetUpLinkStatus();

    if (AT_XPDS_SERVER_MODE_MPC == pstDownDataInd->enServerMode)
    {
        if ((TAF_XPDS_UP_LINK_MPC_CONNECTED == enCurUpLinkStatus)
         || (TAF_XPDS_UP_LINK_MPC_PDE_BOTH_CONNECTED == enCurUpLinkStatus))
        {
            return VOS_OK;
        }
    }

    if (AT_XPDS_SERVER_MODE_PDE == pstDownDataInd->enServerMode)
    {
        if ((TAF_XPDS_UP_LINK_PDE_CONNECTED == enCurUpLinkStatus)
         || (TAF_XPDS_UP_LINK_MPC_PDE_BOTH_CONNECTED == enCurUpLinkStatus))
        {
            return VOS_OK;
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvApForwardDataInd_PreProc
 功能描述  : XPDS处理ID_AT_XPDS_AP_FORWARD_DATA_IND消息
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvApForwardDataInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_AP_FORWARD_DATA_IND_STRU   *pstMsgFwdDataInd;

    pstMsgFwdDataInd  = (AT_XPDS_AP_FORWARD_DATA_IND_STRU*)(pstMsg);

    if (VOS_OK != TAF_XPDS_CheckForwardData_PreProc(pstMsgFwdDataInd))
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvApForwardDataInd_PreProc : TAF_XPDS_CheckForwardData_PreProc error");

        return VOS_TRUE;
    }

    if (1 == pstMsgFwdDataInd->ulCurNum)
    {
        if (VOS_NULL_PTR != g_stTafXpdsDownCtrlPreProc.pucData)
        {
            (VOS_VOID)PS_MEM_FREE(UEPS_PID_XPDS, g_stTafXpdsDownCtrlPreProc.pucData);
        }

        (VOS_VOID)PS_MEM_SET(&g_stTafXpdsDownCtrlPreProc, 0, sizeof(g_stTafXpdsDownCtrlPreProc));

        g_stTafXpdsDownCtrlPreProc.pucData = (VOS_UINT8*)PS_MEM_ALLOC(UEPS_PID_XPDS,
                                                                      TAF_XPDS_ATDOWN_MAX_LEN);

        g_stTafXpdsDownCtrlPreProc.ulTotalNum = pstMsgFwdDataInd->ulTotalNum;
    }

    if ((pstMsgFwdDataInd->ulCurNum != g_stTafXpdsDownCtrlPreProc.ulCurIndex + 1)
      ||(pstMsgFwdDataInd->ulDataLen + g_stTafXpdsDownCtrlPreProc.ulTotalLen >= TAF_XPDS_ATDOWN_MAX_LEN)
      ||(g_stTafXpdsDownCtrlPreProc.ulTotalNum != pstMsgFwdDataInd->ulTotalNum))
    {
        if (VOS_NULL_PTR != g_stTafXpdsDownCtrlPreProc.pucData)
        {
            (VOS_VOID)PS_MEM_FREE(UEPS_PID_XPDS, g_stTafXpdsDownCtrlPreProc.pucData);
        }

        (VOS_VOID)PS_MEM_SET(&g_stTafXpdsDownCtrlPreProc, 0, sizeof(g_stTafXpdsDownCtrlPreProc));

        return VOS_TRUE;
    }

    (VOS_VOID)PS_MEM_CPY(&g_stTafXpdsDownCtrlPreProc.pucData[g_stTafXpdsDownCtrlPreProc.ulTotalLen],
                         pstMsgFwdDataInd->aucData,
                         pstMsgFwdDataInd->ulDataLen);

    g_stTafXpdsDownCtrlPreProc.ulCurIndex = pstMsgFwdDataInd->ulCurNum;

    g_stTafXpdsDownCtrlPreProc.ulTotalLen += pstMsgFwdDataInd->ulDataLen;

    if (pstMsgFwdDataInd->ulCurNum != pstMsgFwdDataInd->ulTotalNum)
    {
        return VOS_TRUE;
    }

    if (AT_XPDS_SERVER_MODE_MPC == pstMsgFwdDataInd->enServerMode)
    {
        /* MPC 内容处理 */
        TAF_XPDS_ProcForwardMpcMsg_PreProc(g_stTafXpdsDownCtrlPreProc.pucData,
                                           g_stTafXpdsDownCtrlPreProc.ulTotalLen);
    }

    if (AT_XPDS_SERVER_MODE_PDE == pstMsgFwdDataInd->enServerMode)
    {
        /* PDE 内容处理 */
        TAF_XPDS_ProcForwardPdeMsg_PreProc(g_stTafXpdsDownCtrlPreProc.pucData,
                                           g_stTafXpdsDownCtrlPreProc.ulTotalLen);
    }

    (VOS_VOID)PS_MEM_FREE(UEPS_PID_XPDS, g_stTafXpdsDownCtrlPreProc.pucData);

    (VOS_VOID)PS_MEM_SET(&g_stTafXpdsDownCtrlPreProc, 0, sizeof(g_stTafXpdsDownCtrlPreProc));

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_ProcForwardMpcMsg_PreProc
 功能描述  :
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : C00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_ProcForwardMpcMsg_PreProc(
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulDataLen
)
{
    switch (pucData[1])
    {
        case TAF_XPDS_MPC_MS_START_POS_RSP:
            TAF_XPDS_RcvAtMpcStartPosRespHandle_PreProc(ulDataLen, pucData);

            TAF_XPDS_SndOmGpsSignalMsgInd(NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_TCP_MPC_FL_START_POS_RSP);

            break;

        case TAF_XPDS_MPC_MS_POS_REPORT_RSP:
            TAF_XPDS_RcvAtMpcPosReportRspHandle_PreProc(ulDataLen, pucData);

            TAF_XPDS_SndOmGpsSignalMsgInd(NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_TCP_MPC_FL_POS_REPORT_RSP);

            break;

        default:
            XPDS_ERROR_LOG("TAF_XPDS_RcvAtMpcMsgHandle:err msg type");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtMpcStartPosRespHandle
 功能描述  : XPDS处理MPC命令
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : C00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_RcvAtMpcStartPosRespHandle_PreProc(
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucData
)
{
    TAF_XPDS_MPC_START_POS_RSP_STRU     stStartPosRsp;

    PS_MEM_SET(&stStartPosRsp, 0, sizeof(TAF_XPDS_MPC_START_POS_RSP_STRU));

    if (VOS_ERR == TAF_XPDS_DecodeMpcStartPosRsp(ulDataLen,
                                                 pucData,
                                                 &stStartPosRsp))
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvAtMpcStartPosRespHandle:TAF_XPDS_DecodeMpcStartPosRsp err");
        return;
    }

    /* 信息存储 */
    PS_MEM_CPY(&(TAF_XPDS_GetMpcCtxAddr()->stStartPosRsp),
               &(stStartPosRsp),
               sizeof(stStartPosRsp));

    TAF_XPDS_SndInternalMpcStartPosResp(&stStartPosRsp);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtMpPosReportRspHandle
 功能描述  : XPDS处理MPC命令
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : C00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_RcvAtMpcPosReportRspHandle_PreProc(
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucData
)
{
    TAF_XPDS_MPC_POS_REPORT_RSP_STRU    stPosReportRsp;

    PS_MEM_SET(&stPosReportRsp, 0, sizeof(TAF_XPDS_MPC_POS_REPORT_RSP_STRU));

    if (VOS_ERR == TAF_XPDS_DecodeMpcPosReportRsp(ulDataLen,
                                                  pucData,
                                                  &stPosReportRsp))
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvAtMpcPosReportRspHandle:TAF_XPDS_DecodeMpcStartPosRsp err");
        return;
    }

    /* 信息存储 */
    PS_MEM_CPY(&(TAF_XPDS_GetMpcCtxAddr()->stPosReportRsp),
               &stPosReportRsp,
               sizeof(stPosReportRsp));

    /* 消息处理 在迭代2处理 */

    TAF_XPDS_SndInternalMpcPosReportResp(&stPosReportRsp);

    return;
}



/*****************************************************************************
 函 数 名  : TAF_XPDS_ProcForwardPdeMsg_PreProc
 功能描述  : Process Forward Msg from PDE
 输入参数  : VOS_UINT8                          *pucMsgBuf
             VOS_UINT32                          ulTotLength
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_ProcForwardPdeMsg_PreProc(
    VOS_UINT8                          *pucMsgBuf,
    VOS_UINT32                          ulTotLength
)
{
    VOS_UINT32                          ulPdeDataMask;

    ulPdeDataMask = 0;

    if (TAF_XPDS_USER_PLANE == TAF_XPDS_GetAgpsCfg()->enCallType)
    {
        /* Decode User Plane Forward Pde Msg */
        if (VOS_OK != TAF_XPDS_DecodeForwardPdeData(pucMsgBuf, ulTotLength, &ulPdeDataMask))
        {
            return;
        }
    }
    else
    {
        /* Decode Control Plane Forward Pde Msg */
        if (VOS_OK != TAF_XPDS_DecodeOnePdeMsg(pucMsgBuf, &ulPdeDataMask))
        {
            return;
        }
    }

    TAF_XPDS_MNTN_TraceForwardMsgInfoIndMsg(ulPdeDataMask);

    /* EPH和ALM数据的组包在预处理中处理，在收到所有的分包之后，发送数据指示消息 */
    if (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_EPH
            == (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_EPH & ulPdeDataMask))
    {
        TAF_XPDS_ProcEphData_PreProc();

        ulPdeDataMask &= ~TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_EPH;
    }

    if (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_ALM
            == (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_ALM & ulPdeDataMask))
    {
        TAF_XPDS_ProcAlmData_PreProc();

        ulPdeDataMask &= ~TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_ALM;
    }

    if (0 != ulPdeDataMask)
    {
        TAF_XPDS_SndInternalForwardPdeDataInd(ulPdeDataMask ,TAF_XPDS_GetAgpsCfg()->enCallType);
    }

    return;

}


/*****************************************************************************
 函 数 名  : TAF_XPDS_ProcEphData_PreProc
 功能描述  : 处理从PDE服务器接收到的EPH数据
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : y00174758
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_ProcEphData_PreProc(VOS_VOID)
{
    VOS_UINT32                                              ulPdeDataMask;
    TAF_XPDS_FWDLINK_RSP_GPS_EPH_STRU                      *pstProvEph = VOS_NULL_PTR;

    pstProvEph = &(TAF_XPDS_GetPdePublicData()->stProvGpsEph);

    /* 收到所有PART之后发送EPH数据内部消息 */
    if (pstProvEph->ucPartNum == pstProvEph->ucTotalParts)
    {
        ulPdeDataMask = TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_EPH;

        TAF_XPDS_SndInternalForwardPdeDataInd(ulPdeDataMask , TAF_XPDS_GetAgpsCfg()->enCallType);
    }
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_ProcAlmData_PreProc
 功能描述  : 处理从PDE服务器接收到的ALM数据
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : y00174758
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_ProcAlmData_PreProc(VOS_VOID)
{
    VOS_UINT32                                              ulPdeDataMask;
    TAF_XPDS_FWDLINK_RSP_GPS_ALM_STRU                      *pstProvAlm = VOS_NULL_PTR;

    pstProvAlm = &(TAF_XPDS_GetPdePublicData()->stProvGpsAlm);

    /* 收到所有PART之后发送ALM数据内部消息 */
    if (pstProvAlm->ucPartNum == pstProvAlm->ucTotalParts)
    {
        ulPdeDataMask = TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_ALM;

        TAF_XPDS_SndInternalForwardPdeDataInd(ulPdeDataMask ,TAF_XPDS_GetAgpsCfg()->enCallType);
    }
}



/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvXsmsRcvInd_PreProc
 功能描述  : 预处理状态收到XSMS消息处理函数
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 已处理
             VOS_FALSE - 未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : c00299064
    修改内容   : 新生成函数
  2.日    期   : 2015年9月6日
    作    者   : y00174758
    修改内容   : AGPS迭代2: 判断MPC下发短信的版本
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXsmsRcvInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XSMS_XPDS_REV_IND_STRU                             *pstXsmsRcvInd;
    TAF_XPDS_RCV_XSMS_MSG_STRU                              stXsmsMsg;
    VOS_UINT32                                              ulCurrFsmId;
    VOS_UINT32                                              ulCurState;
    TAF_XPDS_XSMS_MSG_DECODE_RSLT_ENUM_UINT8                enDecodeRslt;

    pstXsmsRcvInd           = (TAF_XSMS_XPDS_REV_IND_STRU*)pstMsg;

    PS_MEM_SET(&stXsmsMsg, 0, sizeof(TAF_XPDS_RCV_XSMS_MSG_STRU));

    if (ID_XSMS_XPDS_RCV_IND == pstXsmsRcvInd->enMsgName)
    {

        /* 解码网侧发过来的消息 */
        enDecodeRslt = TAF_XPDS_DecodeXsmsRcvMsg(pstXsmsRcvInd->usDataLen,
                                                 pstXsmsRcvInd->aucData,
                                                 &stXsmsMsg);

        if (TAF_XPDS_XSMS_MSG_DECODE_RSLT_ERROR == enDecodeRslt)
        {
            XPDS_ERROR_LOG("TAF_XPDS_RcvXsmsRcvInd_PreProc:TAF_XPDS_DecodeXsmsRcvMsg error");
            return VOS_TRUE;
        }

        /* 保存短信源地址 */
        PS_MEM_CPY(&(TAF_XPDS_GetMpcCtxAddr()->stXsmsAddr),
                   &pstXsmsRcvInd->stXsmsAddr,
                   sizeof(TAF_XSMS_ADDR_STRU));

        /*
           中国电信需求：
           LBS-05004  [必选]   基于 SMS的 MPC到终端的消息类型
           3）当终端收到一个"Version"域不为'00000010'的"65001"MT 短消息时，终端应按以下原则进行处理：
           如果终端没有处于定位会话中，终端应回复一个基于 MO SMS 的 Reject Positioning Request 消息，
           该消息指示终端不支持所接收到的协议版本，并通过 MO SMS中的"Version"域表明终端只支持协议版本00000010。
           如果终端正处于一个定位会话中，终端应简单忽略该 MT SMS。
        */

        if (TAF_XPDS_XSMS_MSG_DECODE_RSLT_UNSUPPORTED_VERSION == enDecodeRslt)
        {
            ulCurrFsmId = TAF_XPDS_GetCurrFsmId();
            ulCurState  = TAF_XPDS_GetFsmTopState();

            if ((TAF_XPDS_FSM_L1_MAIN == ulCurrFsmId)
             && (TAF_XPDS_L1_STA_INIT == ulCurState))
            {
                TAF_XPDS_SndXsmsRejNiPosReq(TAF_XPDS_REJ_POS_REASON_VERSION_NOT_SUPPORT);

                TAF_XPDS_SndOmGpsSignalMsgInd(NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_SMS_MPC_RL_REJ_POS_REQ);
            }

            return VOS_TRUE;
        }


        /* 处理XSMS消息 */
        if (VOS_ERR == TAF_XPDS_ProcXsmsMsg_PreProc(&stXsmsMsg))
        {
            XPDS_ERROR_LOG("TAF_XPDS_RcvXsmsRcvInd_PreProc:TAF_XPDS_XsmsMsgProc error");
        }

    }
    return VOS_TRUE;
}


/****************************************************************************
 函 数 名  : TAF_XPDS_ProcXsmsMsg
 功能描述  : 处理来自XSMS模块的消息
 输入参数  :
 输出参数  : 无
 返 回 值  : TAF_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月17日
    作    者   : C00299064
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32  TAF_XPDS_ProcXsmsMsg_PreProc(
    TAF_XPDS_RCV_XSMS_MSG_STRU         *pstXsmsMsg
)
{
    VOS_UINT32                          ulRet;

    switch (pstXsmsMsg->enMsgChoice)
    {
        case TAF_XPDS_RCV_XSMS_MSG_TYPE_NI_POS_REQ:

            ulRet = TAF_XPDS_XsmsNiPosReqHandle_PreProc(&pstXsmsMsg->stXsmsMsgUnion.stPosReq);

            break;

        case TAF_XPDS_RCV_XSMS_MSG_TYPE_CANCEL_NI_TRACK:

            ulRet = TAF_XPDS_XsmsCancelPosHandle_PreProc(&pstXsmsMsg->stXsmsMsgUnion.stCancelNI);

            break;

        case TAF_XPDS_RCV_XSMS_MSG_TYPE_REFRESH_MR_TRACK:

            ulRet = TAF_XPDS_XsmsRefreshMrSessionHandle_PreProc(&pstXsmsMsg->stXsmsMsgUnion.stRefreshMR);

            break;

        default:
            XPDS_ERROR_LOG("TAF_XPDS_XsmsMsgProc:wrong msg type");
            return VOS_ERR;
    }

    return ulRet;

}

/*****************************************************************************
 函 数 名  : TAF_XPDS_XsmsNiPosReqHandle
 功能描述  : 处理来自XSMS模块的消息
 输入参数  : pstXsmsMsg
 输出参数  : 无
 返 回 值  : TAF_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月17日
    作    者   : C00299064
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32  TAF_XPDS_XsmsNiPosReqHandle_PreProc(
    TAF_XPDS_RCV_XSMS_POS_REQ_STRU     *pstXsmsMsg
)
{
    VOS_UINT32                          ulCurState;

    ulCurState = TAF_XPDS_GetFsmTopState();

    /* 如果当前已经有其他的定位实例，直接发送REJ IND */
    if ((TAF_XPDS_FSM_L1_MAIN == TAF_XPDS_GetCurrFsmId())
     && (TAF_XPDS_L1_STA_INIT == ulCurState))
    {
        /* 请求消息存在控制全局变量中  */
        PS_MEM_CPY(&(TAF_XPDS_GetMpcCtxAddr()->stXsmsPosReq),
                   pstXsmsMsg,
                   sizeof(TAF_XPDS_RCV_XSMS_POS_REQ_STRU));

        TAF_XPDS_SndAtGpsNiSessionInd(pstXsmsMsg);

        /* 启动等待NI回复定时器 */
        TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_GPS_ANSWER_NI_REQ_CNF,
                            TI_TAF_XPDS_WAIT_GPS_ANSWER_NI_REQ_CNF_TIMER_LEN);
    }
    else
    {
        TAF_XPDS_SndXsmsRejNiPosReq(TAF_XPDS_REJ_POS_REASON_IS801_IN_PROCESS);

        TAF_XPDS_SndOmGpsSignalMsgInd(NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_SMS_MPC_RL_REJ_POS_REQ);
    }
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_XsmsCancelPosHandle
 功能描述  : 处理来自XSMS模块的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : TAF_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月17日
    作    者   : C00299064
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32  TAF_XPDS_XsmsCancelPosHandle_PreProc(
    TAF_XPDS_RCV_CANCEL_NI_TRACK_STRU *pstXsmsMsg
)
{
    if (pstXsmsMsg->ucCorrlationId == TAF_XPDS_GetMpcCtxAddr()->stXsmsPosReq.ucCorrelationId)
    {
        if (TAF_XPDS_NI == TAF_XPDS_GetCgpsInitialType())
        {
            TAF_XPDS_SndInternalAbnormalAbortAgpsSessionInd(TAF_XPDS_PROC_RSLT_XSMS_NI_CANCEL);
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_XsmsRefreshMrSessionHandle
 功能描述  : 处理来自XSMS模块的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : TAF_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月17日
    作    者   : C00299064
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32  TAF_XPDS_XsmsRefreshMrSessionHandle_PreProc(
    TAF_XPDS_RCV_REFRESH_MR_TRACK_STRU    *pstXsmsMsg
)
{
    if (TAF_XPDS_SI != TAF_XPDS_GetCgpsInitialType())
    {
        XPDS_WARNING_LOG("TAF_XPDS_XsmsRefreshMrSessionHandle, current Initial Type is not SI mode ");

        return VOS_OK;
    }

    if (TAF_XPDS_REJ_MR_TRACK_CAUSE_CODE_CANCEL == pstXsmsMsg->enCauseCode)
    {
        TAF_XPDS_SndInternalAbnormalAbortAgpsSessionInd(TAF_XPDS_PROC_RSLT_XSMS_SI_CANCEL);
    }
    else if (TAF_XPDS_REJ_MR_TRACK_CAUSE_CODE_LONG_TIME_INACTIVE == pstXsmsMsg->enCauseCode)
    {
        TAF_XPDS_SndInternalAbnormalAbortAgpsSessionInd(TAF_XPDS_PROC_RSLT_XSMS_SI_LONGINACTIVE);
    }
    else if (TAF_XPDS_REJ_MR_TRACK_CAUSE_CODE_PDE_HANDOFF == pstXsmsMsg->enCauseCode)
    {
        TAF_XPDS_SndInternalAbnormalAbortAgpsSessionInd(TAF_XPDS_PROC_RSLT_XSMS_SI_REFRESH);
    }
    else
    {
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvTiXpdsIs801SessionExpired_PreProc
 功能描述  : Is801定时器超时，转换为内部Abort场景
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月9日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvTiXpdsIs801SessionExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_SndInternalAbnormalAbortAgpsSessionInd(TAF_XPDS_PROC_RSLT_IS801_TIMEOUT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvTiWaitGpsAnswerNiReqExpire_PreProc
 功能描述  : 等待回复NI请求超时的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月6日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvTiWaitGpsAnswerNiReqExpire_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    (VOS_VOID)TAF_XPDS_SndXsmsRejNiPosReq(TAF_XPDS_REJ_POS_REASON_POP_UP_SCREEN_TIMER_OUT);

    TAF_XPDS_SndOmGpsSignalMsgInd(NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_SMS_MPC_RL_REJ_POS_REQ);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvCasDataInd_PreProc
 功能描述  : 预处理状态收到CAS DATA IND消息处理函数
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 已处理
             VOS_FALSE - 未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvCasDschDataInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd;
    TAF_XPDS_DATA_BURST_MSG_STRU        stDbmMsg;

    PS_MEM_SET(&stDbmMsg, 0, sizeof(TAF_XPDS_DATA_BURST_MSG_STRU));

    pstDschDataInd       = (CAS_CNAS_1X_DSCH_DATA_IND_STRU*)pstMsg;

    if (VOS_ERR == TAF_XPDS_DecodeDataBurstMsg(&stDbmMsg,
                                               pstDschDataInd->aucMsgData))
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvCasDschDataInd_PreProc : TAF_XPDS_DecodeDataBurstMsg ERR");

        return VOS_TRUE;
    }

    /* CP 默认只有NI CP MSA流程 */
    TAF_XPDS_GetAgpsCfg()->enCallType   = TAF_XPDS_CTRL_PLANE;
    TAF_XPDS_GetAgpsCfg()->enAgpsType   = TAF_XPDS_NI;
    TAF_XPDS_GetAgpsCfg()->enFixMode    = TAF_XPDS_MSA_MODE;

    TAF_XPDS_ProcForwardPdeMsg_PreProc(stDbmMsg.aucData, stDbmMsg.ucNumFields);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvCasRefLocCnf_PreProc
 功能描述  : 预处理状态收到CAS DATA IND消息处理函数
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 已处理
             VOS_FALSE - 未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvCasRefLocCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_XPDS_REF_LOC_CNF_STRU          *pstRefLocCnf;

    pstRefLocCnf  = (CAS_XPDS_REF_LOC_CNF_STRU*)pstMsg;

    if (VOS_OK == pstRefLocCnf->enResult)
    {
        TAF_XPDS_GetPublicDataAddr()->stPilotInfo.usRefPn = pstRefLocCnf->usRefPn;
    }

    return VOS_TRUE;
}




VOS_UINT32 TAF_XPDS_RcvPpmTimerExpire_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_SetPpmTimerExpireFlag(VOS_TRUE);

    TAF_XPDS_SndInternalPpmCompleteMsg();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtUtsTestStartReq_PreProc
 功能描述  : XPDS处理ID_AT_XPDS_UTS_TEST_START_REQ
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月16日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtUtsTestStartReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_MSG_STRU                   *pstAtXpdsMsg;
    VOS_UINT32                          ulDataLen;

    pstAtXpdsMsg = (AT_XPDS_MSG_STRU *)pstMsg;

    /* 保存UTS通道号 */
    TAF_XPDS_SetUtsClientId(pstAtXpdsMsg->stAppCtrl.usClientId);

    ulDataLen = pstAtXpdsMsg->ulLength - sizeof(VOS_UINT32) - sizeof(AT_APPCTRL_STRU);

    TAF_XPDS_SndAtGpsUtsTestStartReq(ulDataLen, pstAtXpdsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtGpsPosInfoRsp_PreProc
 功能描述  : XPDS处理ID_AT_XPDS_GPS_POS_INFO_RSP
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月16日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtGpsPosInfoRsp_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_GPS_POS_INFO_RSP_STRU      *pstMsgPosInfoRsp;

    /* 局部变量初始化 */
    pstMsgPosInfoRsp = (AT_XPDS_GPS_POS_INFO_RSP_STRU*)(pstMsg);

    PS_MEM_CPY(&(TAF_XPDS_GetPublicDataAddr()->stCagpsPosInfo),
               &(pstMsgPosInfoRsp->stPosInfo),
               sizeof(AT_XPDS_GPS_POS_INFO_STRU));

    TAF_XPDS_SndAtUtsGpsPosInfo();

    if (VOS_TRUE == TAF_XPDS_GetOmTestFlag())
    {
        TAF_XPDS_SndOmGpsFixRsltInd(NAS_OM_CDMA_GPS_FIX_RSLT_SUCCESS);
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtUtsTestStopReq_PreProc
 功能描述  : XPDS处理ID_AT_XPDS_UTS_TEST_STOP_REQ
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月24日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtUtsTestStopReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_MSG_STRU                   *pstAtXpdsMsg;
    VOS_UINT32                          ulDataLen;

    pstAtXpdsMsg = (AT_XPDS_MSG_STRU *)pstMsg;

    ulDataLen = pstAtXpdsMsg->ulLength - sizeof(VOS_UINT32) - sizeof(AT_APPCTRL_STRU);

    TAF_XPDS_SndAtGpsUtsTestStopReq(ulDataLen, pstAtXpdsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvOmStartGpsFixReq_PreProc
 功能描述  : XPDS处理ID_OM_NAS_CDMA_START_GPS_FIX_REQ
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月16日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvOmStartGpsFixReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    OM_NAS_CDMA_START_GPS_FIX_REQ_STRU *pstMsgStartReq;
    TAF_XPDS_FIX_MODE_ENUM_UINT8        enXpdsFixMode;
    TAF_XPDS_GPS_START_MODE_ENUM_UINT8  enXpdsStartMode;

    pstMsgStartReq = (OM_NAS_CDMA_START_GPS_FIX_REQ_STRU *)pstMsg;

    TAF_XPDS_SetOmTestFlag(VOS_TRUE);

    TAF_XPDS_SndOmStartGpsFixCnf(pstMsgStartReq);

    if (NAS_OM_CDMA_GPS_FIX_MODE_MONITOR == pstMsgStartReq->enFixMode)
    {
        return VOS_TRUE;
    }

    enXpdsFixMode    = TAF_XPDS_ConvertOmGpsFixModeToXpdsGpsFixMode(pstMsgStartReq->enFixMode);
    enXpdsStartMode  = TAF_XPDS_ConvertOmGpsStartModeToXpdsStartMode(pstMsgStartReq->enStartMode);

    TAF_XPDS_SndAtOmGpsTestStartReq(enXpdsFixMode, enXpdsStartMode);

    if (TAF_XPDS_MSS_MODE == enXpdsFixMode)
    {
        TAF_XPDS_SetAgpsFixMode(TAF_XPDS_MSS_MODE);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvOmStopGpsPosFix_PreProc
 功能描述  : XPDS处理ID_OM_NAS_CDMA_STOP_GPS_FIX_REQ
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月16日
    作    者   : y00174758
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvOmStopGpsFixReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_SndOmStopGpsFixCnf((OM_NAS_CDMA_STOP_GPS_FIX_REQ_STRU *)pstMsg);

    TAF_XPDS_SndAtOmGpsTestStopReq();

    TAF_XPDS_SetOmTestFlag(VOS_FALSE);

    if (TAF_XPDS_MSS_MODE == TAF_XPDS_GetAgpsFixMode())
    {
        TAF_XPDS_InitPosCtx();
    }

    return VOS_TRUE;
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


