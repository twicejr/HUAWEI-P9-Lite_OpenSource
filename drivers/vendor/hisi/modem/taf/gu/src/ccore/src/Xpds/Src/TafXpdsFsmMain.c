/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsFsmMain.c
  版 本 号   : 初稿
  作    者   : g00256031
  生成日期   : 2015年08月26日
  功能描述   : XPDS层一状态机事件处理函数
  函数列表   :
  修改历史   :
  1.日    期   : 2015年08月26日
    作    者   : g00256031
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXpdsCtx.h"
#include "TafXpdsFsmMain.h"
#include "TafXpdsSndAt.h"
#include "TafSdcCtx.h"
#include "TafXpdsSndXsms.h"
#include "TafXpdsSndCas.h"
#include "TafXpdsSndInternalMsg.h"
#include "TafXpdsMntn.h"
#include "TafXpdsCommFunc.h"
#include "TafXpdsFsmMainTbl.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XPDS_FSM_MAIN_C

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtGpsStartReq_Init
 功能描述  : XPDS处理^CAGPSSTART命令
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
VOS_UINT32 TAF_XPDS_RcvAtGpsStartReq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_GPS_START_REQ_STRU         *pstMsgStartReq;
    TAF_XPDS_CFG_INFO_STRU             *pstCagpsCfg;
    TAF_XPDS_CTRL_INFO_STRU            *pstCtrlInfo;
    XPDS_AT_RESULT_CNF_STRU             stStartCnf;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;

    /* 默认回复失败 */
    PS_MEM_SET(&stStartCnf, 0x0, sizeof(stStartCnf));
    stStartCnf.enResult = XPDS_AT_RESULT_ERROR;

    pstCagpsCfg = TAF_XPDS_GetAgpsCfg();
    pstCtrlInfo = TAF_XPDS_GetCtrlInfoAddr();

    pstMsgStartReq = (AT_XPDS_GPS_START_REQ_STRU *)(pstMsg);

    /* 参数不正确回复ABORT消息 */
    if (TAF_XPDS_INITIAL_BUTT > pstMsgStartReq->enAgpsType)
    {
        pstCagpsCfg->enAgpsType    = pstMsgStartReq->enAgpsType;

        stStartCnf.enResult = XPDS_AT_RESULT_NO_ERROR;

        if (TAF_XPDS_MSS_MODE != TAF_XPDS_GetAgpsFixMode())
        {
            /* 启动Reference Loction流程 */
            enSysMode = TAF_SDC_GetSysMode();

            TAF_XPDS_SndCasRefLocReq(enSysMode,
                                    XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_START);

            /* 保存启动时的模式 */
            pstCtrlInfo->enOrigSysMode = enSysMode;

            TAF_XPDS_SndOmGpsFixStartInd();
        }
    }

    TAF_XPDS_SndAtMsg(&pstMsgStartReq->stAppCtrl,
                      ID_XPDS_AT_GPS_START_CNF,
                      sizeof(stStartCnf),
                      (VOS_UINT8*)&stStartCnf);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtGpsCfgMpcAddrReq_Init
 功能描述  : XPDS处理^CAGPSCFGMPCADDR命令
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
VOS_UINT32 TAF_XPDS_RcvAtGpsCfgMpcAddrReq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_GPS_CFG_MPC_ADDR_REQ_STRU  *pstMsgMpcAddrReq;
    TAF_XPDS_CFG_INFO_STRU             *pstCagpsCfg;
    XPDS_AT_RESULT_CNF_STRU             stMpcAddrCnf;

    pstMsgMpcAddrReq = (AT_XPDS_GPS_CFG_MPC_ADDR_REQ_STRU *)(pstMsg);

    /* 获取全局变量地址 */
    pstCagpsCfg = TAF_XPDS_GetAgpsCfg();

    pstCagpsCfg->ulMpcAddr = pstMsgMpcAddrReq->ulIpAddr;

    pstCagpsCfg->ulMpcPort = pstMsgMpcAddrReq->usIpPort;

    /* 消息处理成功，给AT回复成功 */
    PS_MEM_SET(&stMpcAddrCnf, 0x0, sizeof(stMpcAddrCnf));

    stMpcAddrCnf.enResult = VOS_OK;

    TAF_XPDS_SndAtMsg(&pstMsgMpcAddrReq->stAppCtrl,
                     ID_XPDS_AT_GPS_CFG_MPC_ADDR_CNF,
                     sizeof(stMpcAddrCnf),
                     (VOS_UINT8*)&stMpcAddrCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtGpsCfgPdeAddrReq_Init
 功能描述  : XPDS处理^CAGPSCFGPDEADDR命令
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
VOS_UINT32 TAF_XPDS_RcvAtGpsCfgPdeAddrReq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_GPS_CFG_PDE_ADDR_REQ_STRU  *pstMsgPdeAddrReq;
    TAF_XPDS_CFG_INFO_STRU             *pstCagpsCfg;
    XPDS_AT_RESULT_CNF_STRU             stPdeAddrCnf;

    /* 局部变量初始化 */
    PS_MEM_SET(&stPdeAddrCnf, 0x0, sizeof(stPdeAddrCnf));
    stPdeAddrCnf.enResult = VOS_ERR;

    pstMsgPdeAddrReq = (AT_XPDS_GPS_CFG_PDE_ADDR_REQ_STRU *)(pstMsg);

    if (VOS_FALSE == pstMsgPdeAddrReq->ucAddrValid)
    {
        TAF_XPDS_SndAtMsg(&pstMsgPdeAddrReq->stAppCtrl,
                         ID_XPDS_AT_GPS_CFG_PDE_ADDR_CNF,
                         sizeof(stPdeAddrCnf),
                         (VOS_UINT8*)&stPdeAddrCnf);
        return VOS_TRUE;
    }

    /* 获取全局变量地址 */
    pstCagpsCfg = TAF_XPDS_GetAgpsCfg();

    /* IPV4 */
    if (0 == pstMsgPdeAddrReq->ucIPType)
    {
        pstCagpsCfg->ulPdeAddr = pstMsgPdeAddrReq->ulIp4Addr;
        pstCagpsCfg->ulPdePort = pstMsgPdeAddrReq->ulPortNum;

        stPdeAddrCnf.enResult = VOS_OK;
    }

    /* 消息处理完成，给AT回复结果 */
    TAF_XPDS_SndAtMsg(&pstMsgPdeAddrReq->stAppCtrl,
                     ID_XPDS_AT_GPS_CFG_PDE_ADDR_CNF,
                     sizeof(stPdeAddrCnf),
                     (VOS_UINT8*)&stPdeAddrCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtGpsCfgPositionModeReq_Init
 功能描述  : XPDS处理^CAGPSCFGPOSMODE命令
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
VOS_UINT32 TAF_XPDS_RcvAtGpsCfgPositionModeReq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_GPS_CFG_POSITION_MODE_REQ_STRU      *pstMsgCfgModeReq;
    TAF_XPDS_CFG_INFO_STRU                      *pstCagpsCfg;
    XPDS_AT_RESULT_CNF_STRU                      stCfgModeCnf;

    /* 局部变量初始化 */
    PS_MEM_SET(&stCfgModeCnf, 0x0, sizeof(stCfgModeCnf));
    stCfgModeCnf.enResult = VOS_ERR;

    pstMsgCfgModeReq = (AT_XPDS_GPS_CFG_POSITION_MODE_REQ_STRU *)(pstMsg);

    /* 保存与GPS交互通道的ClientId */
    TAF_XPDS_SetGpsClientId(pstMsgCfgModeReq->stAppCtrl.usClientId);

    /* 获取全局变量地址 */
    pstCagpsCfg = TAF_XPDS_GetAgpsCfg();

    if (TAF_XPDS_CALL_BUTT <= pstMsgCfgModeReq->enCallType)
    {
        /* 消息处理完成，给AT回复结果 */
        TAF_XPDS_SndAtMsg(&pstMsgCfgModeReq->stAppCtrl,
                         ID_XPDS_AT_GPS_CFG_MODE_CNF,
                         sizeof(stCfgModeCnf),
                         (VOS_UINT8*)&stCfgModeCnf);

        return VOS_TRUE;
    }

    pstCagpsCfg->enCallType = pstMsgCfgModeReq->enCallType;

    if ((TAF_XPDS_MSA_MODE  == pstMsgCfgModeReq->enFixMode)
     || (TAF_XPDS_MSB_MODE  == pstMsgCfgModeReq->enFixMode)
     || (TAF_XPDS_AFLT_MODE == pstMsgCfgModeReq->enFixMode))
    {
        pstCagpsCfg->enFixMode           = pstMsgCfgModeReq->enFixMode;

        /* 此定时器填0，和GPS协商好，后续流程都靠收到他们下发的伪距后，再开始后边定位结果上报流程 */
        pstCagpsCfg->ulPrecisionTimerLen = TI_TAF_XPDS_WAIT_GPS_PRECISION_PSEUDORANGE_INFO_DEFAULT_TIMER_LEN;
    }
    else
    {
        /* 消息处理完成，给AT回复结果 */
        TAF_XPDS_SndAtMsg(&pstMsgCfgModeReq->stAppCtrl,
                         ID_XPDS_AT_GPS_CFG_MODE_CNF,
                         sizeof(stCfgModeCnf),
                         (VOS_UINT8*)&stCfgModeCnf);

        return VOS_TRUE;
    }

    pstCagpsCfg->usFixNum           = pstMsgCfgModeReq->usFixNum;
    pstCagpsCfg->ulFixRateTime      = pstMsgCfgModeReq->ulFixRateTime;
    pstCagpsCfg->ulQosHaccuracy     = pstMsgCfgModeReq->ulQosHaccuracy;
    pstCagpsCfg->ulQosVaccuracy     = pstMsgCfgModeReq->ulQosVaccuracy;
    pstCagpsCfg->ulQosPerformance   = pstMsgCfgModeReq->ulQosPerformance;

    stCfgModeCnf.enResult = VOS_OK;

    /* 消息处理完成，给AT回复结果 */
    TAF_XPDS_SndAtMsg(&pstMsgCfgModeReq->stAppCtrl,
                     ID_XPDS_AT_GPS_CFG_MODE_CNF,
                     sizeof(stCfgModeCnf),
                     (VOS_UINT8*)&stCfgModeCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtGpsReplyNiReq_Init
 功能描述  : XPDS处理^CAGPSREPLYNIREQ命令
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
VOS_UINT32 TAF_XPDS_RcvAtGpsReplyNiReq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_GPS_REPLY_NI_RSP_STRU      *pstMsgReplyNiRsp;

    /* 局部变量初始化 */
    pstMsgReplyNiRsp = (AT_XPDS_GPS_REPLY_NI_RSP_STRU *)(pstMsg);

    /* 停止等待NI回复定时器 */
    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_GPS_ANSWER_NI_REQ_CNF);

    /* 保存与GPS交互通道的ClientId */
    TAF_XPDS_SetGpsClientId(pstMsgReplyNiRsp->stAppCtrl.usClientId);

    if (AT_XPDS_GPS_NI_REQ_REPLY_RESULT_ACCEPT == pstMsgReplyNiRsp->enReplyResult)
    {
        /* 下发给AGPS ^CAGPSSTARTREQ */
        TAF_XPDS_SndAtGpsStartReq(&pstMsgReplyNiRsp->stAppCtrl);
    }
    /* reject */
    else if (AT_XPDS_GPS_NI_REQ_REPLY_RESULT_REJECT == pstMsgReplyNiRsp->enReplyResult)
    {
        /* 需要回复给网侧reject */
        if (AT_XPDS_GPS_NI_REQ_REJECT_TYPE_TIMER_OUT == pstMsgReplyNiRsp->enRejReason)
        {
            (VOS_VOID)TAF_XPDS_SndXsmsRejNiPosReq(TAF_XPDS_REJ_POS_REASON_POP_UP_SCREEN_TIMER_OUT);
        }
        else
        {
            (VOS_VOID)TAF_XPDS_SndXsmsRejNiPosReq(TAF_XPDS_REJ_POS_REASON_USER_DENIED_REQ);
        }

        TAF_XPDS_SndOmGpsSignalMsgInd(NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_SMS_MPC_RL_REJ_POS_REQ);
    }
    else
    {
        ;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtGpsQryTimeInfoReq_Init
 功能描述  : XPDS收到AT发来的ID_AT_XPDS_SYNC_TIME_REQ消息处理函数
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
VOS_UINT32 TAF_XPDS_RcvAtGpsQryTimeInfoReq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_GPS_QRY_TIME_INFO_REQ_STRU *pstMsgQryTimeReq;
    TAF_XPDS_CTRL_INFO_STRU            *pstCtrlInfo = VOS_NULL_PTR;

    /* 局部变量初始化 */
    pstMsgQryTimeReq = (AT_XPDS_GPS_QRY_TIME_INFO_REQ_STRU *)pstMsg;

    pstCtrlInfo = TAF_XPDS_GetCtrlInfoAddr();

    pstCtrlInfo->enSyncTimeActionType = pstMsgQryTimeReq->enActionType;

    if (AT_XPDS_REPLY_SYNC_TIME_AND_ASSIST_DATA == pstCtrlInfo->enSyncTimeActionType)
    {

        if (TAF_XPDS_USER_PLANE == TAF_XPDS_GetAgpsCfg()->enCallType)
        {
            /* 将层一切换到定位状态 */
            TAF_XPDS_SetCurrFsmState(TAF_XPDS_L1_STA_POSITIONING);

            /* 启动用户面链路状态机 */
            TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_LINK_CTRL);

            /* 发送内部消息去建立MPC的Socket链路 */
            TAF_XPDS_SndInternalServerBindOperReq(TAF_XPDS_SERVER_BIND_OPER_OPEN_SOCKET,
                                                  TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET);
        }
        else
        {
            /* 将层一切换到定位状态 */
            TAF_XPDS_SetCurrFsmState(TAF_XPDS_L1_STA_POSITIONING);

            /* 启动用户面链路状态机 */
            TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_CP_LINK_CTRL);

            /* send ID_TAF_XPDS_XPDS_CP_LINK_START_REQ for starting the link proc */
            TAF_XPDS_SndControlPlaneLinkStart_CpLinkCtrl();

            TAF_XPDS_SndCasRefLocReq(TAF_XPDS_GetCtrlInfoAddr()->enOrigSysMode, XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_START);
        }

    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvCasPdeDataInd_Init
 功能描述  : XPDS收到AT发来的ID_AT_XPDS_SYNC_TIME_REQ消息处理函数
 输入参数  : pstMsg  -- 消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月10日
    作    者   : c00299064
    修改内容   : AGPS迭代1新增
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvCasPdeDataInd_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果当前收到控制面的DATA_IND 需要切换到POSING 的PDE状态 */

    TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU                *pstCasDataInd;

    pstCasDataInd = (TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU*)pstMsg;

    if (TAF_XPDS_CTRL_PLANE == pstCasDataInd->enCallType)
    {
        /* 給GPS 发送NICPSTART */
        if (TAF_XPDS_NI == TAF_XPDS_GetCgpsInitialType())
        {
            TAF_XPDS_SndAtGpsCpNiStart();
        }

        TAF_XPDS_SndCasRefLocReq(TAF_XPDS_GetCtrlInfoAddr()->enOrigSysMode, XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_START);

        TAF_XPDS_SetCurrFsmState(TAF_XPDS_L1_STA_POSITIONING);

        TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_CP_PDE_PROC);

        TAF_XPDS_SndInternalCpPdeProcStartReq();
    }

    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_CAS_DATA_IND_L1_POS);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvXccIncomingInd_Init
 功能描述  : XPDS收到XCC INCOMING CALL IND
 输入参数  : pstMsg  -- 消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月10日
    作    者   : c00299064
    修改内容   : AGPS迭代1新增
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXccIncomingInd_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_SetCurrFsmState(TAF_XPDS_L1_STA_POSITIONING);

    TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_CP_LINK_CTRL);

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtGpsPosInfoRsp_Pos
 功能描述  : XPDS处理ID_AT_XPDS_POS_INFO_RSP
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : x00314862
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtGpsPosInfoRsp_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_GPS_POS_INFO_RSP_STRU      *pstMsgPosInfoRsp;
    TAF_XPDS_CFG_INFO_STRU             *pstCagpsCfg;

    pstCagpsCfg        = TAF_XPDS_GetAgpsCfg();

    /* 局部变量初始化 */
    pstMsgPosInfoRsp = (AT_XPDS_GPS_POS_INFO_RSP_STRU*)(pstMsg);

    PS_MEM_CPY(&(TAF_XPDS_GetPublicDataAddr()->stCagpsPosInfo),
               &(pstMsgPosInfoRsp->stPosInfo),
               sizeof(AT_XPDS_GPS_POS_INFO_STRU));

    /* NI单次定位流程下需要上报给GPS停止 */
    if ((TAF_XPDS_NI == pstCagpsCfg->enAgpsType)
     && (1 == pstCagpsCfg->usFixNum))
    {
        TAF_XPDS_SndAtGpsCancelNiSession();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvCasPdeDataInd_Pos
 功能描述  :
 输入参数  : pstMsg  -- 消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月10日
    作    者   : c00299064
    修改内容   : AGPS迭代1新增
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvCasPdeDataInd_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果当前收到控制面的DATA_IND 需要切换到POSING 的PDE状态 */

    TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU                *pstCasDataInd;

    pstCasDataInd = (TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU*)pstMsg;

    if (TAF_XPDS_CTRL_PLANE == pstCasDataInd->enCallType)
    {
        /* 应当还需要判断是不是当前链路已经建好 */

        /* 給GPS 发送NICPSTART */
        if (TAF_XPDS_NI == TAF_XPDS_GetCgpsInitialType())
        {
            TAF_XPDS_SndAtGpsCpNiStart();
        }

        TAF_XPDS_SndCasRefLocReq(TAF_XPDS_GetCtrlInfoAddr()->enOrigSysMode, XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_START);

        TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_CP_PDE_PROC);

        TAF_XPDS_SndInternalCpPdeProcStartReq();
    }

    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_CAS_DATA_IND_L1_POS);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_ProcNiCancelPos
 功能描述  : 判断是否需要发送CANCEL给网侧
 输入参数  : enProcRslt  -- 处理结果值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月09日
    作    者   : g00256031
    修改内容   : AGPS迭代2新增
*****************************************************************************/
VOS_VOID TAF_XPDS_ProcNiCancelPos(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enProcRslt
)
{
    TAF_XPDS_CANCEL_REASON_ENUM_UINT8   enCancelReason;

    /* NI流程中需要通过短信上报Cancel */
    if (TAF_XPDS_NI != TAF_XPDS_GetCgpsInitialType())
    {
        return;
    }

    enCancelReason = TAF_XPDS_FindCancelReasonByRslt(enProcRslt);

    if (TAF_XPDS_CANCEL_REASON_BUTT != enCancelReason)
    {
        TAF_XPDS_SndXsmsCancelPosNotify(enCancelReason);

        TAF_XPDS_SndOmGpsSignalMsgInd(NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_SMS_MPC_RL_CANCEL_POS_NTF);

        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_ProcAtGpsStopReq
 功能描述  : 处理AT发来STOP消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月09日
    作    者   : g00256031
    修改内容   : AGPS迭代2新增
*****************************************************************************/
VOS_VOID TAF_XPDS_ProcAtGpsStopReq(VOS_VOID)
{
    TAF_XPDS_UP_LINK_STATUS_ENUM_UINT8  enLinkStatus;
    NAS_OM_CDMA_GPS_FIX_RSLT_ENUM_UINT8 enOmFixRslt;

    enLinkStatus = TAF_XPDS_GetUpLinkStatus();

    if (TAF_XPDS_UP_LINK_NOT_EXISTED != enLinkStatus)
    {
        TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_LINK_CTRL);

        /* 发送内部消息断开链路 */
        TAF_XPDS_SndInternalServerBindOperReq(TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET,
                                              TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET);
    }
    else
    {
        /* 通知AP切APN操作 */
        TAF_XPDS_SndAtApCloseCagpsDataCall();

        TAF_XPDS_SndCasRefLocReq(TAF_XPDS_GetCtrlInfoAddr()->enOrigSysMode,
            XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_STOP);

        /* 返回OK */
        TAF_XPDS_SndAtGpsStopCnf();

        if (VOS_TRUE == TAF_XPDS_GetOmTestFlag())
        {
            if (VOS_TRUE == TAF_XPDS_GetOmTestAbortFlag())
            {
                /* 如果被PDE拒绝，等待GPS继续定位的结果 */
                if (TAF_XPDS_PROC_RSLT_PDE_REJECT != TAF_XPDS_GetOmTestPdeProcRslt())
                {
                    enOmFixRslt = TAF_XPDS_GetOmFixRslt();

                    TAF_XPDS_SndOmGpsFixRsltInd(enOmFixRslt);
                }

                TAF_XPDS_SetOmTestPdeProcRslt(TAF_XPDS_PROC_RSLT_BUTT);

                TAF_XPDS_SetOmTestAbortFlag(VOS_FALSE);
            }
        }

        TAF_XPDS_StopAllTimer();

        /* 初始化定位相关全局变量 */
        TAF_XPDS_InitPosCtx();

        /* 将状态切到Init态 */
        TAF_XPDS_SetCurrFsmState(TAF_XPDS_L1_STA_INIT);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_ProcServerBindRsltSucc_NoLink
 功能描述  : 链路回复成功并且没有链路存在的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月10日
    作    者   : g00256031
    修改内容   : AGPS迭代2新增
*****************************************************************************/
VOS_VOID TAF_XPDS_ProcServerBindRsltSucc_NoLink(VOS_VOID)
{
    TAF_XPDS_CFG_INFO_STRU             *pstAgpsConfig;
    NAS_OM_CDMA_GPS_FIX_RSLT_ENUM_UINT8 enOmFixRslt;

    pstAgpsConfig = TAF_XPDS_GetAgpsCfg();

    if (TAF_XPDS_NI == pstAgpsConfig->enAgpsType)
    {
        /* 当前为多次定位的情况 */
        if (1 < pstAgpsConfig->usFixNum)
        {
            if (TAF_XPDS_GetCtrlInfoAddr()->usCurFixNum < pstAgpsConfig->usFixNum)
            {
                //启动周期定位定时器
                TAF_XPDS_StartTimer(TI_TAF_XPDS_NI_POS_REPORT_INTERNAL,
                                    TAF_XPDS_GetAgpsCfg()->ulFixRateTime);

                return;
            }

            /* 正常结束NI Track Session */
            TAF_XPDS_SndAtGpsCancelNiSession();
        }
        else
        {
            if (TAF_XPDS_MSB_MODE != TAF_XPDS_GetAgpsFixMode())
            {
                /* 正常结束NI Track Session */
                TAF_XPDS_SndAtGpsCancelNiSession();
            }
        }
    }

    /* 当为异常断链时需要完成如下操作 */
    if (TAF_XPDS_PROC_RSLT_SUCC != TAF_XPDS_GetPosProcRslt())
    {
        /* 通知AP切APN操作 */
        TAF_XPDS_SndAtApCloseCagpsDataCall();

        TAF_XPDS_SndAtGpsStopCnf();

        if (VOS_TRUE == TAF_XPDS_GetOmTestFlag())
        {
            if (VOS_TRUE == TAF_XPDS_GetOmTestAbortFlag())
            {
                /* 如果被PDE拒绝，等待GPS继续定位的结果 */
                if (TAF_XPDS_PROC_RSLT_PDE_REJECT != TAF_XPDS_GetOmTestPdeProcRslt())
                {
                    enOmFixRslt = TAF_XPDS_GetOmFixRslt();

                    TAF_XPDS_SndOmGpsFixRsltInd(enOmFixRslt);
                }

                TAF_XPDS_SetOmTestPdeProcRslt(TAF_XPDS_PROC_RSLT_BUTT);

                TAF_XPDS_SetOmTestAbortFlag(VOS_FALSE);
            }
        }

        TAF_XPDS_SndCasRefLocReq(TAF_XPDS_GetCtrlInfoAddr()->enOrigSysMode,
                                 XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_STOP);

        TAF_XPDS_StopAllTimer();

        /* 初始化定位相关全局变量 */
        TAF_XPDS_InitPosCtx();

        /* 将状态切到Init态 */
        TAF_XPDS_SetCurrFsmState(TAF_XPDS_L1_STA_INIT);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_ProcServerBindRsltSucc
 功能描述  : 链路回复成功后的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月10日
    作    者   : g00256031
    修改内容   : AGPS迭代2新增
*****************************************************************************/
VOS_VOID TAF_XPDS_ProcServerBindRsltSucc(VOS_VOID)
{
    TAF_XPDS_UP_LINK_STATUS_ENUM_UINT8  enLinkStatus;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;

    enLinkStatus  = TAF_XPDS_GetUpLinkStatus();

    /* MPC连接成功，启动MPC状态机 */
    if (TAF_XPDS_UP_LINK_MPC_CONNECTED == enLinkStatus)
    {
        /* 判断当前是否需要查询TIME */
        if (AT_XPDS_REPLY_SYNC_TIME_AND_ASSIST_DATA == TAF_XPDS_GetCtrlInfoAddr()->enSyncTimeActionType)
        {
            enSysMode = TAF_SDC_GetSysMode();

            TAF_XPDS_SndCasSyncTimeReq(enSysMode);

            TAF_XPDS_GetCtrlInfoAddr()->enSyncTimeActionType = AT_XPDS_REPLY_SYNC_TIME_INFO;
        }

        /* 期间只要MPC建链成功，该值需要置为0 */
        TAF_XPDS_GetCtrlInfoAddr()->ucPosReportFailNum = 0;

        if (VOS_FALSE == TAF_XPDS_GetCtrlInfoAddr()->ucIsMpcAuthSucc)
        {
            TAF_XPDS_SndInternalStartMpcProcess(TAF_XPDS_MPC_OPER_START_POS_REQ);
        }
        else
        {
            TAF_XPDS_SndInternalStartMpcProcess(TAF_XPDS_MPC_OPER_POS_REPORT);
        }

        TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_MPC_PROC);

        return;
    }

    /* PDE连接成功，启动PDE状态机 */
    if (TAF_XPDS_UP_LINK_PDE_CONNECTED == enLinkStatus)
    {
        TAF_XPDS_SndInternalPdeProcStartReq(TAF_XPDS_GetAgpsFixMode());

        TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_PDE_PROC);

        return;
    }

    /* MPC和PDE都断开，需要给GPS回复OK指示 */
    if (TAF_XPDS_UP_LINK_NOT_EXISTED == enLinkStatus)
    {
        TAF_XPDS_ProcServerBindRsltSucc_NoLink();
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_ProcTrackingMpcConnectFail
 功能描述  : 跟踪型定位下MPC建链失败的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_ERR - 执行失败，需要继续处理后面流程
             VOS_OK  - 执行成功，可直接返回
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月10日
    作    者   : g00256031
    修改内容   : AGPS迭代2新增
*****************************************************************************/
VOS_UINT32 TAF_XPDS_ProcTrackingMpcConnectFail(VOS_VOID)
{
    TAF_XPDS_CFG_INFO_STRU             *pstAgpsConfig;

    pstAgpsConfig = TAF_XPDS_GetAgpsCfg();

    if ((VOS_TRUE != TAF_XPDS_GetCtrlInfoAddr()->ucIsMpcAuthSucc)
     || (TAF_XPDS_NI != pstAgpsConfig->enAgpsType))
    {
        return VOS_ERR;
    }

    /* 第三方定位需要上报Position report,如果多次连接MPC均失败，则abort异常 */
    TAF_XPDS_GetCtrlInfoAddr()->ucPosReportFailNum++;

    if (TAF_XPDS_MPC_REPORT_FAIL_MAX_TIMES == TAF_XPDS_GetCtrlInfoAddr()->ucPosReportFailNum)
    {
        XPDS_WARNING_LOG("Failed to send pos report to MPC, and reach max times...");

        return VOS_ERR;
    }

    TAF_XPDS_GetCtrlInfoAddr()->usCurFixNum++;

    if (TAF_XPDS_GetCtrlInfoAddr()->usCurFixNum == pstAgpsConfig->usFixNum)
    {
        XPDS_WARNING_LOG("The time of positioning reach max times...");

        return VOS_ERR;
    }

    TAF_XPDS_SetPosProcRslt(TAF_XPDS_PROC_RSLT_SUCC);

    //连接MPC失败 同样启动周期定位定时器
    TAF_XPDS_StartTimer(TI_TAF_XPDS_NI_POS_REPORT_INTERNAL,
                        pstAgpsConfig->ulFixRateTime);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RestartPosProc
 功能描述  : 重启整个定位流程
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月15日
    作    者   : g00256031
    修改内容   : AGPS迭代1新增
*****************************************************************************/
VOS_VOID TAF_XPDS_RestartPosProc(VOS_VOID)
{
    TAF_XPDS_SetPosProcRslt(TAF_XPDS_PROC_RSLT_SUCC);

    /* 缓存消息处理
      * 重新发起跟踪定位流程
      */
    TAF_XPDS_GetCtrlInfoAddr()->ucIsMpcAuthSucc = VOS_FALSE;
    TAF_XPDS_GetCtrlInfoAddr()->ucPosReportFailNum = 0;
    TAF_XPDS_GetCtrlInfoAddr()->usCurFixNum = 0;

    /* 发送内部消息去建立MPC的Socket链路 */
    TAF_XPDS_SndInternalServerBindOperReq(TAF_XPDS_SERVER_BIND_OPER_OPEN_SOCKET,
                                          TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET);

    TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_LINK_CTRL);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvXpdsBindServerCnf_Pos
 功能描述  : 用户面建链结果处理
 输入参数  : pstMsg  -- 消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月10日
    作    者   : d00212987
    修改内容   : AGPS迭代1新增
  2.日    期   : 2015年09月08日
    作    者   : x00314862
    修改内容   : 新增跟踪定位逻辑处理
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsBindServerCnf_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_UP_LINK_CTRL_CNF_STRU    *pstBindCnf;

    /* 判断链路结果 */
    pstBindCnf = (TAF_XPDS_XPDS_UP_LINK_CTRL_CNF_STRU*)pstMsg;

    /* 假如之前已经出错，则不更新结果值 */
    if (TAF_XPDS_PROC_RSLT_SUCC == TAF_XPDS_GetPosProcRslt())
    {
        TAF_XPDS_SetPosProcRslt(pstBindCnf->enRslt);
    }

    /* 处理L2 UP link 回复Succ的情况 */
    if (TAF_XPDS_PROC_RSLT_SUCC == pstBindCnf->enRslt)
    {
        TAF_XPDS_ProcServerBindRsltSucc();

        return VOS_TRUE;
    }

    /* PDE地址发生变化需要重启定位流程 */
    if ((TAF_XPDS_PROC_RSLT_XSMS_SI_REFRESH == pstBindCnf->enRslt)
     || (TAF_XPDS_PROC_RSLT_XSMS_SI_LONGINACTIVE == pstBindCnf->enRslt))
    {
        TAF_XPDS_RestartPosProc();

        return VOS_TRUE;
    }

    /***********************************************************/
    /*         如下处理均是L2回复失败异常的处理                */
    /***********************************************************/

    /* 如果是单次定位，PDE连接失败，停止IS 801 session定时器 */
    TAF_XPDS_StopTimer(TI_TAF_XPDS_IS801_SESSION);

    if (TAF_XPDS_PROC_RSLT_UP_MPC_DISCONNECT == pstBindCnf->enRslt)
    {
        if (VOS_OK == TAF_XPDS_ProcTrackingMpcConnectFail())
        {
            return VOS_TRUE;
        }
    }

    /* 通过结果值发送Cancel给Xsms */
    TAF_XPDS_ProcNiCancelPos(pstBindCnf->enRslt);

    if (TAF_XPDS_PROC_RSLT_AT_STOP == pstBindCnf->enRslt)
    {
        TAF_XPDS_ProcAtGpsStopReq();

        return VOS_TRUE;
    }

    /* 通知GPS异常 */
    TAF_XPDS_SndAtGpsAbortPosInd(XPDS_AT_ABORT_POS_REASON_ENUM_DATA_LINK_ERR);

    if (VOS_TRUE == TAF_XPDS_GetOmTestFlag())
    {
        TAF_XPDS_SetOmTestAbortFlag(VOS_TRUE);

        if (TAF_XPDS_PROC_RSLT_UP_MPC_DISCONNECT == pstBindCnf->enRslt)
        {
            TAF_XPDS_SetOmFixRslt(NAS_OM_CDMA_GPS_FIX_RSLT_FAIL_MPC);
        }
        else
        {
            TAF_XPDS_SetOmFixRslt(NAS_OM_CDMA_GPS_FIX_RSLT_FAIL_OTHER);
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_ProcMpcRsltSucc
 功能描述  : MPC交互数据成功之后的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : g00261581
    修改内容   : 新生成函数
  2.日    期   : 2015年9月8日
    作    者   : x00314862
    修改内容   : 修改pos report成功的处理逻辑

*****************************************************************************/
VOS_VOID TAF_XPDS_ProcMpcRsltSucc(VOS_VOID)
{
    if (VOS_FALSE == TAF_XPDS_GetCtrlInfoAddr()->ucIsMpcAuthSucc)
    {
        /* MPC鉴权成功，更新全局变量值 */
        TAF_XPDS_GetCtrlInfoAddr()->ucIsMpcAuthSucc = VOS_TRUE;

        /* MPC鉴权成功之后，下一步的操作必须是与PDE交互，获取辅助数据，所以需要打开PDE的链路 */
        TAF_XPDS_SndInternalServerBindOperReq(TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET,
                                              TAF_XPDS_SERVER_BIND_OPER_OPEN_SOCKET);

        TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_LINK_CTRL);
    }
    else
    {
        /* Postion report成功上报MPC，此时需要断开MPC链路 */
        TAF_XPDS_SndInternalServerBindOperReq(TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET,
                                              TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET);

        TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_LINK_CTRL);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvXpdsMpcProcRsltInd_Pos
 功能描述  : XPDS收到AT发来的ID_AT_XPDS_SYNC_TIME_REQ消息处理函数
 输入参数  : pstMsg  -- 消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月10日
    作    者   : d00212987
    修改内容   : AGPS迭代1新增
  2.日    期   : 2015年09月02日
    作    者   : x00314862
    修改内容   : AGPS迭代1新增
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsMpcProcRsltInd_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_INT_MPC_PROC_RSLT_IND_STRU    *pstMpcProcRlst;

    pstMpcProcRlst = (TAF_XPDS_XPDS_INT_MPC_PROC_RSLT_IND_STRU*)pstMsg;

    TAF_XPDS_SetPosProcRslt(pstMpcProcRlst->enMpcOperRslt);

    /* MPC交互成功 */
    if (TAF_XPDS_PROC_RSLT_SUCC == pstMpcProcRlst->enMpcOperRslt)
    {
        TAF_XPDS_ProcMpcRsltSucc();

        return VOS_TRUE;
    }

    /* PDE地址发生变化需要重启定位流程 */
    if ((TAF_XPDS_PROC_RSLT_XSMS_SI_REFRESH == pstMpcProcRlst->enMpcOperRslt)
     || (TAF_XPDS_PROC_RSLT_XSMS_SI_LONGINACTIVE == pstMpcProcRlst->enMpcOperRslt))
    {
        TAF_XPDS_RestartPosProc();

        return VOS_TRUE;
    }

    /* 通过结果值发送Cancel给Xsms */
    TAF_XPDS_ProcNiCancelPos(pstMpcProcRlst->enMpcOperRslt);

    if (TAF_XPDS_PROC_RSLT_AT_STOP == pstMpcProcRlst->enMpcOperRslt)
    {
        TAF_XPDS_ProcAtGpsStopReq();

        return VOS_TRUE;
    }

    /* 通知GPS异常 */
    TAF_XPDS_SndAtGpsAbortPosInd(XPDS_AT_ABORT_POS_REASON_ENUM_NETWORK_NO_RSP);

    if (VOS_TRUE == TAF_XPDS_GetOmTestFlag())
    {
        TAF_XPDS_SetOmTestAbortFlag(VOS_TRUE);

        TAF_XPDS_SetOmFixRslt(NAS_OM_CDMA_GPS_FIX_RSLT_FAIL_MPC);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvTiPosReportExpired_Pos
 功能描述  : 定时上报Position Report定时器超时的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvTiPosReportExpired_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* MSB需要打开MPC Server去Report Position */
    if (TAF_XPDS_MSB_MODE == TAF_XPDS_GetAgpsFixMode())
    {
        TAF_XPDS_SndInternalServerBindOperReq(TAF_XPDS_SERVER_BIND_OPER_OPEN_SOCKET,
                                              TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET);
    }
    else
    {
        /* MSA or AFLT需要打开PDE重新去获取位置信息  */
        TAF_XPDS_SndInternalServerBindOperReq(TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET,
                                              TAF_XPDS_SERVER_BIND_OPER_OPEN_SOCKET);
    }

    TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_LINK_CTRL);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvXpdsPdeProcRsltInd_Pos
 功能描述  : 处理PDE结果
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
VOS_UINT32 TAF_XPDS_RcvXpdsPdeProcRsltInd_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_PDE_PROC_RSLT_IND_STRU       *pstPdeProcRlst;
    TAF_XPDS_CFG_INFO_STRU                     *pstCagpsCfg;

    pstCagpsCfg    = TAF_XPDS_GetAgpsCfg();
    pstPdeProcRlst = (TAF_XPDS_XPDS_PDE_PROC_RSLT_IND_STRU*)pstMsg;

    TAF_XPDS_SetPosProcRslt(pstPdeProcRlst->enRslt);

    /* PDE返回之后，停止IS 801 session定时器 */
    TAF_XPDS_StopTimer(TI_TAF_XPDS_IS801_SESSION);

    if (TAF_XPDS_PROC_RSLT_SUCC == pstPdeProcRlst->enRslt)
    {
        /* 如果是NI跟踪型定位，需要断开PDE,连接MPC服务器 */
        if ((TAF_XPDS_NI == pstCagpsCfg->enAgpsType)
         && (pstCagpsCfg->usFixNum > 1))
        {
            TAF_XPDS_SndInternalServerBindOperReq(TAF_XPDS_SERVER_BIND_OPER_OPEN_SOCKET,
                                                  TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET);

            TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_LINK_CTRL);
        }
        /* AGPS辅助定位流程可以结束 */
        else
        {
            TAF_XPDS_SndInternalServerBindOperReq(TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET,
                                                  TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET);

            TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_LINK_CTRL);
        }

        return VOS_TRUE;
    }

    /* PDE地址发生变化需要重启定位流程 */
    if ((TAF_XPDS_PROC_RSLT_XSMS_SI_REFRESH == pstPdeProcRlst->enRslt)
     || (TAF_XPDS_PROC_RSLT_XSMS_SI_LONGINACTIVE == pstPdeProcRlst->enRslt))
    {
        TAF_XPDS_RestartPosProc();

        return VOS_TRUE;
    }

    /* 通过结果值发送Cancel给Xsms */
    TAF_XPDS_ProcNiCancelPos(pstPdeProcRlst->enRslt);

    if (TAF_XPDS_PROC_RSLT_AT_STOP == pstPdeProcRlst->enRslt)
    {
        TAF_XPDS_ProcAtGpsStopReq();

        return VOS_TRUE;
    }

    /* 通知GPS异常 */
    TAF_XPDS_SndAtGpsAbortPosInd(XPDS_AT_ABORT_POS_REASON_ENUM_NETWORK_NO_RSP);

    if (VOS_TRUE == TAF_XPDS_GetOmTestFlag())
    {
        TAF_XPDS_SetOmTestAbortFlag(VOS_TRUE);

        TAF_XPDS_SetOmTestPdeProcRslt(pstPdeProcRlst->enRslt);

        if (TAF_XPDS_PROC_RSLT_PDE_REJECT != pstPdeProcRlst->enRslt)
        {
            TAF_XPDS_SetOmFixRslt(NAS_OM_CDMA_GPS_FIX_RSLT_FAIL_OTHER);
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvXpdsAbnormalAbortAgpsSessionInd_Pos
 功能描述  : 层一状态机接收到Abort消息的处理
 输入参数  : pstMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsAbnormalAbortAgpsSessionInd_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU *pstAbortMsg;
    TAF_XPDS_CFG_INFO_STRU                                 *pstCagpsCfg;
    VOS_UINT16                                              usCurFixNum;

    pstCagpsCfg = TAF_XPDS_GetAgpsCfg();

    pstAbortMsg = (TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU*)pstMsg;

    /* 只有在正常流程结束后才处理 */
    if (TAF_XPDS_PROC_RSLT_SUCC == TAF_XPDS_GetPosProcRslt())
    {
        TAF_XPDS_SetPosProcRslt(pstAbortMsg->enAbortScene);

        usCurFixNum = TAF_XPDS_GetCtrlInfoAddr()->usCurFixNum;

        /* 假如当前为跟踪型定位则需要通知GPS中断定位流程 */
        if ((1 < pstCagpsCfg->usFixNum)
         && (pstCagpsCfg->usFixNum > usCurFixNum))
        {
            /* 通过结果值发送Cancel给Xsms */
            TAF_XPDS_ProcNiCancelPos(pstAbortMsg->enAbortScene);

            /* 其他异常场景需要通知GPS */
            if (TAF_XPDS_PROC_RSLT_AT_STOP != pstAbortMsg->enAbortScene)
            {
                /* 通知GPS异常 */
                TAF_XPDS_SndAtGpsAbortPosInd(XPDS_AT_ABORT_POS_REASON_ENUM_NETWORK_NO_RSP);

                if (VOS_TRUE == TAF_XPDS_GetOmTestFlag())
                {
                    TAF_XPDS_SetOmTestAbortFlag(VOS_TRUE);

                    TAF_XPDS_SetOmFixRslt(NAS_OM_CDMA_GPS_FIX_RSLT_FAIL_OTHER);
                }
            }
        }
    }

    /* 假如为GPS发来的STOP消息需要单独进行处理 */
    if (TAF_XPDS_PROC_RSLT_AT_STOP == pstAbortMsg->enAbortScene)
    {
        TAF_XPDS_ProcAtGpsStopReq();
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_XPDS_RcvCpXpdsPdeProcRsltInd_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_PDE_PROC_RSLT_IND_STRU       *pstPdeProcRlst;

    pstPdeProcRlst = (TAF_XPDS_XPDS_PDE_PROC_RSLT_IND_STRU*)pstMsg;

    TAF_XPDS_SetPosProcRslt(pstPdeProcRlst->enRslt);

    /* send the GPS Cp stop */
    if (TAF_XPDS_NI == TAF_XPDS_GetCgpsInitialType())
    {
        TAF_XPDS_SndAtGpsCpNiStop();
    }

    TAF_XPDS_SndCasRefLocReq(TAF_XPDS_GetCtrlInfoAddr()->enOrigSysMode,
                         XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_STOP);

    TAF_XPDS_StopAllTimer();

    /* 初始化定位相关全局变量 */
    TAF_XPDS_InitPosCtx();

    TAF_XPDS_SetCurrFsmState(TAF_XPDS_L1_STA_INIT);

    return VOS_TRUE;

}


VOS_UINT32 TAF_XPDS_RcvCpXpdsLinkProcRsltInd_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_CP_LINK_PROC_RSLT_IND_STRU   *pstCpLinkRslt;

    pstCpLinkRslt = (TAF_XPDS_XPDS_CP_LINK_PROC_RSLT_IND_STRU *)pstMsg;

    switch (pstCpLinkRslt->enRslt)
    {
        case TAF_XPDS_PROC_RSLT_SUCC:
            if (TAF_XPDS_SI == TAF_XPDS_GetAgpsCfg()->enAgpsType)
            {
                TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_CP_PDE_PROC);
                TAF_XPDS_SndInternalCpPdeProcStartReq();
            }
            else
            {
                /* start the timer for wait data ind */
                TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_CAS_DATA_IND_L1_POS,
                                    TI_TAF_XPDS_WAIT_CAS_DATA_IND_L1_POS_TIMER_LEN);
            }
            break;

        case TAF_XPDS_PDE_PROC_RSLT_FAIL:
        case TAF_XPDS_PDE_PROC_RSLT_TIMER_OUT:

            TAF_XPDS_SndCasRefLocReq(TAF_XPDS_GetCtrlInfoAddr()->enOrigSysMode,
                                     XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_STOP);

            TAF_XPDS_StopAllTimer();

            /* 初始化定位相关全局变量 */
            TAF_XPDS_InitPosCtx();

            TAF_XPDS_SetCurrFsmState(TAF_XPDS_L1_STA_INIT);

            break;

        default:
            XPDS_ERROR_LOG("TAF_XPDS_RcvCpXpdsLinkProcRsltInd_Pos: Incorrect parameter.");
            break;
    }

    return VOS_TRUE;

}


VOS_UINT32 TAF_XPDS_RcvTiDataIndWaitExpired_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_XPDS_SndCasRefLocReq(TAF_XPDS_GetCtrlInfoAddr()->enOrigSysMode,
                             XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_STOP);

    TAF_XPDS_StopAllTimer();

    TAF_XPDS_InitPosCtx();

    TAF_XPDS_SetCurrFsmState(TAF_XPDS_L1_STA_INIT);

    return VOS_TRUE;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

