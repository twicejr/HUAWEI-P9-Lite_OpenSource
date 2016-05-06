/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsFsmPdeProc.c
  版 本 号   : 初稿
  作    者   : y00174758
  生成日期   : 2015年08月24日
  功能描述   : PDE状态机事件处理函数
  函数列表   :
  修改历史   :
  1.日    期   : 2015年08月24日
    作    者   : y00174758
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXpdsCtx.h"
#include "TafXpdsSndInternalMsg.h"
#include "TafXpdsFsmPdeProc.h"
#include "TafXpdsFsmPdeProcComm.h"
#include "TafXpdsMntn.h"
#include "TafXpdsSndAt.h"
#include "TafXpdsSndCas.h"
#include "TafXpdsSndXsms.h"
#include "TafXpdsCommFunc.h"
#include "TafXpdsFsmPdeProcTbl.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XPDS_FSM_PDE_PROC_C

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 Global variable
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvXpdsPdeProcStartReq_L2Pde_Init
 功能描述  : INIT状态收到ID_TAF_XPDS_XPDS_PDE_PROC_START_REQ消息处理函数
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 已处理
             VOS_FALSE - 未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : y00174758
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsPdeProcStartReq_L2Pde_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_PDE_PROC_START_REQ_STRU                  *pstPdeProcStartReq = VOS_NULL_PTR;
    TAF_XPDS_ENCODE_RL_INFO_STRU                            stEncodeRlInfo;

    PS_MEM_SET(&stEncodeRlInfo, 0x00, sizeof(TAF_XPDS_ENCODE_RL_INFO_STRU));

    pstPdeProcStartReq = (TAF_XPDS_XPDS_PDE_PROC_START_REQ_STRU *)pstMsg;

    TAF_XPDS_MNTN_TraceSessionBeginIndMsg();

    switch (pstPdeProcStartReq->enFixMode)
    {
        case TAF_XPDS_MSA_MODE:
        case TAF_XPDS_AFLT_MODE:
            TAF_XPDS_InitPdePublicDataPdeInit();

            TAF_XPDS_SndPdeStartDeliverData_L2Pde();

            /* 计算方差 */
            TAF_XPDS_UpdatePpmInGlobal();

            stEncodeRlInfo.aucReqType[0] = TAF_XPDS_RL_MSGTYPE_REQ_GPS_ACQ_ASSIST;
            stEncodeRlInfo.ucNumOfReq    = 1;
            stEncodeRlInfo.aucRspType[0] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_MS_INFO;
            stEncodeRlInfo.aucRspType[1] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_PILPHASE_MEAS;
            stEncodeRlInfo.ucNumOfResp   = 2;

            (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_PDE_ASSIST_DATA_CNF, TI_TAF_XPDS_WAIT_PDE_CNF_TIMER_LEN);

            TAF_XPDS_SndPdeReverseMsg_L2Pde(&stEncodeRlInfo, TAF_XPDS_USER_PLANE);

            TAF_XPDS_SetCurrFsmState(TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_PDE_ASSIST_INFO);

            break;

        case TAF_XPDS_MSB_MODE:
            TAF_XPDS_InitPdePublicDataPdeInit();

            TAF_XPDS_SndPdeStartDeliverData_L2Pde();

            /* 计算方差 */
            TAF_XPDS_UpdatePpmInGlobal();

            stEncodeRlInfo.aucReqType[0] = TAF_XPDS_RL_MSGTYPE_REQ_LOC_RSP;
            stEncodeRlInfo.aucReqType[1] = TAF_XPDS_RL_MSGTYPE_REQ_GPS_ALM;
            stEncodeRlInfo.aucReqType[2] = TAF_XPDS_RL_MSGTYPE_REQ_GPS_EPH;
            stEncodeRlInfo.ucNumOfReq    = 3;

            stEncodeRlInfo.aucRspType[0] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_MS_INFO;
            stEncodeRlInfo.aucRspType[1] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_PILPHASE_MEAS;
            stEncodeRlInfo.ucNumOfResp   = 2;

            TAF_XPDS_SndPdeReverseMsg_L2Pde(&stEncodeRlInfo, TAF_XPDS_USER_PLANE);

            /* 状态迁移到: TAF_XPDS_L2_PDE_PROC_STA_MSB_WAIT_PDE_DATA */
            TAF_XPDS_SetCurrFsmState(TAF_XPDS_L2_PDE_PROC_STA_MSB_WAIT_PDE_DATA);

            /* 启动保护定时器 */
            (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_PDE_MSB_DATA,
                                          TI_TAF_XPDS_WAIT_PDE_MSB_DATA_TIMER_LEN);

            break;

        default:
            XPDS_WARNING_LOG("TAF_XPDS_RcvXpdsPdeProcStartReq_L2Pde_Init: wrong agps fix mode!");
            break;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvXpdsForwardPdeDataInd_L2Pde_MsaWaitPdeAssistInfo
 功能描述  : MSA_WAIT_PDE_ASSIST_INFO状态收到ID_TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND消息处理函数
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 已处理
             VOS_FALSE - 未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : x00314862
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsForwardPdeDataInd_L2Pde_MsaWaitPdeAssistInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU                *pstPdeDataInd = VOS_NULL_PTR;
    NV_XPDS_FEATURE_CONTROL_STRU                            stNvXpdsCtrl;
    VOS_UINT32                                              ulSiPseuTimerLen;
    VOS_UINT32                                              ulNiPseuTimerLen;

    pstPdeDataInd = (TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU *)pstMsg;

    /* 如果PDE消息中下发的数据中包含reject消息，结束定位流程，退出L2 PDE状态机 */
    if ((TAF_XPDS_RCV_PDE_DATA_MASK_RSP_REJECT)
     == (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_REJECT & pstPdeDataInd->ulDataMask))
    {
        TAF_XPDS_SndInternalPdeProcRsltInd(TAF_XPDS_PROC_RSLT_PDE_REJECT);

        TAF_XPDS_ProcQuitL2Pde_L2Pde();

        return VOS_TRUE;
    }

    TAF_XPDS_ProcReqFromPde_L2Pde(pstPdeDataInd->ulDataMask, TAF_XPDS_USER_PLANE);

    /* 判断是否包含Assist Info */
    if ((TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_ACQ_ASSIST)
     == (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_ACQ_ASSIST & pstPdeDataInd->ulDataMask))
    {
        /* 处理Assit Info */
        TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_PDE_ASSIST_DATA_CNF);

        /* before send acq assist to gps ,trace assist ctx first */
        TAF_XPDS_MNTN_TraceAssistDataCtxIndMsg();

        /* send assist data to gps, 从GPS获取伪距信息  */
        TAF_XPDS_SndAtGpsAcqAssistData();

        /* 精度测试定时器长度不为0时候才启动，否则不启动 */
        if (0 != TAF_XPDS_GetAgpsCfg()->ulPrecisionTimerLen)
        {
            TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_GPS_PRECISION_PSEUDORANGE_INFO,
                                TAF_XPDS_GetAgpsCfg()->ulPrecisionTimerLen);
        }
        /* Quality定时器也没有被启动，则启动一个保护定时器*/
        else if (TAF_XPDS_TIMER_STATUS_STOP == TAF_XPDS_GetTimerStatus(TI_TAF_XPDS_WAIT_RSP_PDE_PSEUDORANGE_REQ_QUALITY))
        {
            ulSiPseuTimerLen = TI_TAF_XPDS_WAIT_GPS_PSEUDORANGE_CNF_TIMER_LEN_SI;
            ulNiPseuTimerLen = TI_TAF_XPDS_WAIT_GPS_PSEUDORANGE_CNF_TIMER_LEN_NI;

            PS_MEM_SET(&stNvXpdsCtrl, 0, sizeof(NV_XPDS_FEATURE_CONTROL_STRU));

            if (NV_OK == NV_Read(en_NV_Item_Xpds_Feature_Ctrl_Cfg, &stNvXpdsCtrl, sizeof(NV_XPDS_FEATURE_CONTROL_STRU)))
            {
                if (0 != stNvXpdsCtrl.ucSiWaitGpsPseudoCnfTimeLen)
                {
                    ulSiPseuTimerLen = stNvXpdsCtrl.ucSiWaitGpsPseudoCnfTimeLen * TIMER_S_TO_MS_1000;
                }

                if (0 != stNvXpdsCtrl.ucNiWaitGpsPseudoCnfTimeLen)
                {
                    ulNiPseuTimerLen = stNvXpdsCtrl.ucNiWaitGpsPseudoCnfTimeLen * TIMER_S_TO_MS_1000;
                }
            }

            if (TAF_XPDS_NI == TAF_XPDS_GetCgpsInitialType())
            {
                TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_GPS_PSEUDORANGE_CNF, ulNiPseuTimerLen);
            }
            else
            {
                TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_GPS_PSEUDORANGE_CNF, ulSiPseuTimerLen);
            }
        }
        else
        {
        }

        /* 状态迁移到: TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_GPS_PSEUDO_INFO */
        TAF_XPDS_SetCurrFsmState(TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_GPS_PSEUDO_INFO);
    }
    else
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvXpdsForwardPdeDataInd_L2Pde_MsaWaitPdeAssistInfo: no assist info rsp...");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvXpdsForwardPdeDataIndExpired_L2Pde_MsaWaitPdeAssistInfo
 功能描述  : MSA_WAIT_PDE_ASSIST_INFO状态收到定时器超时消息处理函数
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 已处理
             VOS_FALSE - 未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : y00174758
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvTiXpdsForwardPdeDataIndExpired_L2Pde_MsaWaitPdeAssistInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_SndInternalPdeProcRsltInd(TAF_XPDS_PDE_PROC_RSLT_TIMER_OUT);

    TAF_XPDS_ProcQuitL2Pde_L2Pde();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvXpdsForwardPdeDataInd_L2Pde_MsaWaitGpsPseudoInfo
 功能描述  : MSA_WAIT_GPS_PSEUDO_INFO状态收到ID_TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND消息处理函数
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 已处理
             VOS_FALSE - 未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月09日
    作    者   : y00174758
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsForwardPdeDataInd_L2Pde_MsaWaitGpsPseudoInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU                *pstPdeDataInd = VOS_NULL_PTR;

    pstPdeDataInd = (TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU *)pstMsg;

    /* 如果PDE消息中下发的数据中包含reject消息，结束定位流程，退出L2 PDE状态机 */
    if ((TAF_XPDS_RCV_PDE_DATA_MASK_RSP_REJECT)
     == (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_REJECT & pstPdeDataInd->ulDataMask))
    {
        TAF_XPDS_SndInternalPdeProcRsltInd(TAF_XPDS_PROC_RSLT_PDE_REJECT);

        TAF_XPDS_ProcQuitL2Pde_L2Pde();
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtGpsPrmInfoRsp_L2Pde_MsaWaitGpsPseudoInfo
 功能描述  : MSA_WAIT_GPS_PSEUDO_INFO状态收到ID_AT_XPDS_GPS_PRM_INFO_RSP消息处理函数
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 已处理
             VOS_FALSE - 未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : x00314862
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtGpsPrmInfoRsp_L2Pde_MsaWaitGpsPseudoInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_GPS_PRM_INFO_RSP_STRU                          *pstMsgPrmInfoRsp;
    TAF_XPDS_REVLINK_RSP_PSEU_RANGE_MEAS_STRU              *pstPseuMeas;
    TAF_XPDS_REVLINK_RSP_PILOT_PHASE_MEAS_STRU             *pstPilotMeas;
    TAF_XPDS_ENCODE_RL_INFO_STRU                            stEncodeRlInfo;
    VOS_UINT8                                               ucLoopCount;

    /* 局部变量初始化 */
    PS_MEM_SET(&stEncodeRlInfo, 0x00, sizeof(TAF_XPDS_ENCODE_RL_INFO_STRU));

    pstMsgPrmInfoRsp = (AT_XPDS_GPS_PRM_INFO_RSP_STRU*)(pstMsg);

    /* 消息无效 */
    if (VOS_FALSE == pstMsgPrmInfoRsp->ucPrmValid)
    {
        return VOS_TRUE;
    }

    pstPseuMeas  = &(TAF_XPDS_GetPdePublicData()->stRspPrmInfo);
    pstPilotMeas = &(TAF_XPDS_GetPublicDataAddr()->stPilotInfo);

    PS_MEM_SET(pstPseuMeas, 0, sizeof(TAF_XPDS_REVLINK_RSP_PSEU_RANGE_MEAS_STRU));

    pstPseuMeas->ucPartNum    = 0;
    pstPseuMeas->ucTotalparts = 0;

    if ((pstMsgPrmInfoRsp->ucMeasNum > 0)
     && (pstMsgPrmInfoRsp->ucMeasNum <= TAF_MSG_CDMA_MAX_SV_NUM))
    {
        pstPseuMeas->ucNumOfPS    = pstMsgPrmInfoRsp->ucMeasNum - 1;  /* 协议规定发送给网侧时减1 */
    }

    pstPseuMeas->ulTimeRef    = pstMsgPrmInfoRsp->ulMeasTow % 14400000; /* 4小时单位 */
    pstPseuMeas->ucTimeRefSrc = 1;    /* 01 GPS time reference */

    /* 从全局变量中获得使用的值 */
    pstPseuMeas->ucOffsetIncl       = 1;
    pstPseuMeas->usRefPN            = pstPilotMeas->usRefPn;
    pstPseuMeas->sMobileSysOffset   = pstPilotMeas->sMobSysTOffst;

    for (ucLoopCount = 0; ucLoopCount < pstMsgPrmInfoRsp->ucMeasNum; ucLoopCount++)
    {
        pstPseuMeas->astPsuedoInfo[ucLoopCount].ucSvPRNNum      = pstMsgPrmInfoRsp->astMseasData[ucLoopCount].ucSvId;
        pstPseuMeas->astPsuedoInfo[ucLoopCount].ucSvCNO         = pstMsgPrmInfoRsp->astMseasData[ucLoopCount].ucSvCn0;
        pstPseuMeas->astPsuedoInfo[ucLoopCount].sPsDoppler      = pstMsgPrmInfoRsp->astMseasData[ucLoopCount].sPsDopp;
        pstPseuMeas->astPsuedoInfo[ucLoopCount].usSvCodePhWh    = pstMsgPrmInfoRsp->astMseasData[ucLoopCount].usSvCodePhWhole;
        pstPseuMeas->astPsuedoInfo[ucLoopCount].usSvCodePhFr    = pstMsgPrmInfoRsp->astMseasData[ucLoopCount].usSvCodePhFract;
        pstPseuMeas->astPsuedoInfo[ucLoopCount].ucMulPathInd    = pstMsgPrmInfoRsp->astMseasData[ucLoopCount].ucMulpathInd;
        pstPseuMeas->astPsuedoInfo[ucLoopCount].ucPsRangeRmsEr  = pstMsgPrmInfoRsp->astMseasData[ucLoopCount].ucPsRmsErr;
    }

    TAF_XPDS_GetPdePublicData()->ucIsReceivedGpsPrmInfo = VOS_TRUE;

    if (TAF_XPDS_TIMER_STATUS_RUNING != TAF_XPDS_GetTimerStatus(TI_TAF_XPDS_WAIT_GPS_PRECISION_PSEUDORANGE_INFO))
    {
        TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_RSP_PDE_PSEUDORANGE_REQ_QUALITY);

        TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_GPS_PSEUDORANGE_CNF);

        /* 计算方差 */
        TAF_XPDS_UpdatePpmInGlobal();

        /* 回复给网络侧数据 */
        stEncodeRlInfo.aucReqType[0] = TAF_XPDS_RL_MSGTYPE_REQ_LOC_RSP;
        stEncodeRlInfo.ucNumOfReq    = 1;

        stEncodeRlInfo.aucRspType[0] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_PILPHASE_MEAS;
        stEncodeRlInfo.aucRspType[1] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_PSUEDORANG_MEAS;
        stEncodeRlInfo.ucNumOfResp   = 2;

        /* Before send msg to PDE, hook current Pseu Range Ctx info */
        TAF_XPDS_MNTN_TracePseuRangeInfoCtxIndMsg();

        TAF_XPDS_SndPdeReverseMsg_L2Pde(&stEncodeRlInfo, TAF_XPDS_USER_PLANE);

        (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_PDE_LOCATION_INFO_CNF, TI_TAF_XPDS_WAIT_PDE_CNF_TIMER_LEN);

        /* 状态迁移到: TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_PDE_LOC_RESP */
        TAF_XPDS_SetCurrFsmState(TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_PDE_LOC_RSP);

    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvAtPrmInfoRspExpired_L2Pde_MsaWaitGpsPseudoInfo
 功能描述  : MSA_WAIT_GPS_PSEUDO_INFO状态收到定时器超时消息处理函数
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 已处理
             VOS_FALSE - 未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : x00314862
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvTiPrmInfoRspExpired_L2Pde_MsaWaitGpsPseudoInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
     /* 发送导频相位测量信息、伪距信息到PDE服务器 */
    TAF_XPDS_REVLINK_RSP_PSEU_RANGE_MEAS_STRU              *pstPseuMeas;
    TAF_XPDS_REVLINK_RSP_PILOT_PHASE_MEAS_STRU             *pstPilotMeas;
    TAF_XPDS_ENCODE_RL_INFO_STRU                            stEncodeRlInfo;

    /* 局部变量初始化 */
    PS_MEM_SET(&stEncodeRlInfo, 0x00, sizeof(TAF_XPDS_ENCODE_RL_INFO_STRU));
    pstPseuMeas  = &(TAF_XPDS_GetPdePublicData()->stRspPrmInfo);
    pstPilotMeas = &(TAF_XPDS_GetPublicDataAddr()->stPilotInfo);

    /* 从全局变量中获得使用的值 */
    pstPseuMeas->ucOffsetIncl       = 1;
    pstPseuMeas->usRefPN            = pstPilotMeas->usRefPn;
    pstPseuMeas->sMobileSysOffset   = pstPilotMeas->sMobSysTOffst;

     /* 计算方差 */
    TAF_XPDS_UpdatePpmInGlobal();

    /* 回复给网络侧数据 */
    stEncodeRlInfo.aucReqType[0] = TAF_XPDS_RL_MSGTYPE_REQ_LOC_RSP;
    stEncodeRlInfo.ucNumOfReq    = 1;

    stEncodeRlInfo.aucRspType[0] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_PILPHASE_MEAS;
    stEncodeRlInfo.ucNumOfResp   = 1;

    if (VOS_TRUE == TAF_XPDS_GetPdePublicData()->ucIsReceivedGpsPrmInfo)
    {
        stEncodeRlInfo.aucRspType[1] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_PSUEDORANG_MEAS;
        stEncodeRlInfo.ucNumOfResp   = 2;
    }

    /* Before send msg to PDE, hook current Pseu Range Ctx info */
    TAF_XPDS_MNTN_TracePseuRangeInfoCtxIndMsg();

    TAF_XPDS_SndPdeReverseMsg_L2Pde(&stEncodeRlInfo, TAF_XPDS_USER_PLANE);

    (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_PDE_LOCATION_INFO_CNF, TI_TAF_XPDS_WAIT_PDE_CNF_TIMER_LEN);

    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_GPS_PRECISION_PSEUDORANGE_INFO);

    /* 状态迁移到: TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_PDE_LOC_RESP */
    TAF_XPDS_SetCurrFsmState(TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_PDE_LOC_RSP);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvTiWaitGpsPrecisionPseudoRangeExpired_L2Pde_MsaWaitGpsPseudoInfo
 功能描述  : MSA_WAIT_GPS_PSEUDO_INFO状态收到定时器超时消息处理函数
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 已处理
             VOS_FALSE - 未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : x00314862
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvTiWaitGpsPrecisionPseudoRangeExpired_L2Pde_MsaWaitGpsPseudoInfo(
    VOS_UINT32                           ulEventType,
    struct MsgCB                        *pstMsg
)
{
    TAF_XPDS_REVLINK_RSP_PSEU_RANGE_MEAS_STRU              *pstPseuMeas;
    TAF_XPDS_REVLINK_RSP_PILOT_PHASE_MEAS_STRU             *pstPilotMeas;
    TAF_XPDS_ENCODE_RL_INFO_STRU                            stEncodeRlInfo;

    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_RSP_PDE_PSEUDORANGE_REQ_QUALITY);

    /* 局部变量初始化 */
    PS_MEM_SET(&stEncodeRlInfo, 0x00, sizeof(TAF_XPDS_ENCODE_RL_INFO_STRU));
    pstPseuMeas  = &(TAF_XPDS_GetPdePublicData()->stRspPrmInfo);
    pstPilotMeas = &(TAF_XPDS_GetPublicDataAddr()->stPilotInfo);


    /* 从全局变量中获得使用的值 */
    pstPseuMeas->ucOffsetIncl       = 1;
    pstPseuMeas->usRefPN            = pstPilotMeas->usRefPn;
    pstPseuMeas->sMobileSysOffset   = pstPilotMeas->sMobSysTOffst;

    /* 计算方差 */
    TAF_XPDS_UpdatePpmInGlobal();

    /* 回复给网络侧数据 */
    stEncodeRlInfo.aucReqType[0] = TAF_XPDS_RL_MSGTYPE_REQ_LOC_RSP;
    stEncodeRlInfo.ucNumOfReq    = 1;

    stEncodeRlInfo.aucRspType[0] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_PILPHASE_MEAS;
    stEncodeRlInfo.ucNumOfResp   = 1;

    if (VOS_TRUE == TAF_XPDS_GetPdePublicData()->ucIsReceivedGpsPrmInfo)
    {
        stEncodeRlInfo.aucRspType[1] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_PSUEDORANG_MEAS;
        stEncodeRlInfo.ucNumOfResp   = 2;
    }

    /* Before send msg to PDE, hook current Pseu Range Ctx info */
    TAF_XPDS_MNTN_TracePseuRangeInfoCtxIndMsg();

    TAF_XPDS_SndPdeReverseMsg_L2Pde(&stEncodeRlInfo, TAF_XPDS_USER_PLANE);

    (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_PDE_LOCATION_INFO_CNF, TI_TAF_XPDS_WAIT_PDE_CNF_TIMER_LEN);

    /* 状态迁移到: TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_PDE_LOC_RESP */
    TAF_XPDS_SetCurrFsmState(TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_PDE_LOC_RSP);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvTiWaitGpsPseudoRangeCnfExpired_L2Pde_MsaWaitGpsPseudoInfo
 功能描述  : MSA_WAIT_GPS_PSEUDO_INFO状态收到定时器超时消息处理函数
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 已处理
             VOS_FALSE - 未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : x00314862
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvTiWaitGpsPseudoRangeCnfExpired_L2Pde_MsaWaitGpsPseudoInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_REVLINK_RSP_PSEU_RANGE_MEAS_STRU              *pstPseuMeas;
    TAF_XPDS_REVLINK_RSP_PILOT_PHASE_MEAS_STRU             *pstPilotMeas;
    TAF_XPDS_ENCODE_RL_INFO_STRU                            stEncodeRlInfo;

    /* 局部变量初始化 */
    PS_MEM_SET(&stEncodeRlInfo, 0x00, sizeof(TAF_XPDS_ENCODE_RL_INFO_STRU));
    pstPseuMeas  = &(TAF_XPDS_GetPdePublicData()->stRspPrmInfo);
    pstPilotMeas = &(TAF_XPDS_GetPublicDataAddr()->stPilotInfo);


    /* 从全局变量中获得使用的值 */
    pstPseuMeas->ucOffsetIncl       = 1;
    pstPseuMeas->usRefPN            = pstPilotMeas->usRefPn;
    pstPseuMeas->sMobileSysOffset   = pstPilotMeas->sMobSysTOffst;

    /* 计算方差 */
    TAF_XPDS_UpdatePpmInGlobal();

    /* 回复给网络侧数据 */
    stEncodeRlInfo.aucReqType[0] = TAF_XPDS_RL_MSGTYPE_REQ_LOC_RSP;
    stEncodeRlInfo.ucNumOfReq    = 1;

    stEncodeRlInfo.aucRspType[0] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_PILPHASE_MEAS;
    stEncodeRlInfo.ucNumOfResp   = 1;

    /* Before send msg to PDE, hook current Pseu Range Ctx info */
    TAF_XPDS_MNTN_TracePseuRangeInfoCtxIndMsg();

    TAF_XPDS_SndPdeReverseMsg_L2Pde(&stEncodeRlInfo, TAF_XPDS_USER_PLANE);

    (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_PDE_LOCATION_INFO_CNF, TI_TAF_XPDS_WAIT_PDE_CNF_TIMER_LEN);

    /* 状态迁移到: TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_PDE_LOC_RESP */
    TAF_XPDS_SetCurrFsmState(TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_PDE_LOC_RSP);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvXpdsForwardPdeDataInd_L2Pde_MsaWaitPdeLocRespInfo
 功能描述  : MSA_WAIT_PDE_LOC_RSP状态收到ID_TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND消息处理函数
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 已处理
             VOS_FALSE - 未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : y00174758
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsForwardPdeDataInd_L2Pde_MsaWaitPdeLocRespInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU                *pstPdeDataInd = VOS_NULL_PTR;

    pstPdeDataInd = (TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU *)pstMsg;

    /* 如果PDE消息中下发的数据中包含reject消息，结束定位流程，退出L2 PDE状态机 */
    if (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_REJECT
            == (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_REJECT & pstPdeDataInd->ulDataMask))
    {
        TAF_XPDS_SndInternalPdeProcRsltInd(TAF_XPDS_PROC_RSLT_PDE_REJECT);

        TAF_XPDS_ProcQuitL2Pde_L2Pde();

        return VOS_TRUE;
    }

    TAF_XPDS_ProcReqFromPde_L2Pde(pstPdeDataInd->ulDataMask, TAF_XPDS_USER_PLANE);

    /* 判断是否包含Assist Info */
    if (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_LOC_RSP & pstPdeDataInd->ulDataMask)
    {

        TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_PDE_LOCATION_INFO_CNF);

        /* before send locationg to gps , trace locationg ctx first */
        TAF_XPDS_MNTN_TraceLocationInfoCtxIndMsg();

        TAF_XPDS_ProcPdeLocationRsp_L2Pde();

        /* send internal result cnf msg to main FSM */
        TAF_XPDS_SndInternalPdeProcRsltInd(TAF_XPDS_PROC_RSLT_SUCC);

        TAF_XPDS_ProcQuitL2Pde_L2Pde();
    }
    else
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvXpdsForwardPdeDataInd_L2Pde_MsaWaitPdeLocRespInfo: no location rsp...");
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvXpdsForwardPdeDataIndExpired_L2Pde_MsaWaitLocRespInfo
 功能描述  : MSA_WAIT_PDE_LOC_RSP状态收到定时器超时消息处理函数
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 已处理
             VOS_FALSE - 未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : x00314862
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvTiXpdsForwardPdeDataIndExpired_L2Pde_MsaWaitPdeLocRespInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_SndInternalPdeProcRsltInd(TAF_XPDS_PDE_PROC_RSLT_TIMER_OUT);

    TAF_XPDS_ProcQuitL2Pde_L2Pde();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvXpdsForwardPdeDataInd_L2Pde_MsbWaitPdeData
 功能描述  : MSB_WAIT_PDE_DATA状态收到ID_TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND消息处理函数
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 已处理
             VOS_FALSE - 未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : y00174758
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsForwardPdeDataInd_L2Pde_MsbWaitPdeData(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU                *pstPdeDataInd = VOS_NULL_PTR;

    pstPdeDataInd = (TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU *)pstMsg;

    /* 如果PDE消息中下发的数据中包含reject消息，结束定位流程，退出L2 PDE状态机 */
    if (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_REJECT
            == (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_REJECT & pstPdeDataInd->ulDataMask))
    {
        TAF_XPDS_SndInternalPdeProcRsltInd(TAF_XPDS_PROC_RSLT_PDE_REJECT);

        TAF_XPDS_ProcQuitL2Pde_L2Pde();

        return VOS_TRUE;
    }

    /* 判断是否包含EPH数据 */
    if (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_EPH
            == (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_EPH & pstPdeDataInd->ulDataMask))
    {
        /* 处理EPH数据 */
        TAF_XPDS_ProcEphData_L2Pde_MsbWaitPdeData();
    }

    /* 判断是否包含ALM数据 */
    if (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_ALM
            == (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_ALM & pstPdeDataInd->ulDataMask))
    {
        /* 处理ALM数据 */
        TAF_XPDS_ProcAlmData_L2Pde_MsbWaitPdeData();
    }

    if (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_LOC_RSP
            == (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_LOC_RSP & pstPdeDataInd->ulDataMask))
    {
        TAF_XPDS_SndAtGpsPositionInfo();
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvTiWaitPdeMsbDataExpired_L2Pde_MsbWaitPdeData
 功能描述  : MSB_WAIT_PDE_DATA状态收到等待MSB数据的定时器超时处理
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 已处理
             VOS_FALSE - 未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月27日
    作    者   : y00174758
    修改内容   : AGPS迭代2新增
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvTiWaitPdeMsbDataExpired_L2Pde_MsbWaitPdeData(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_FWDLINK_RSP_GPS_EPH_STRU  *pstProvEph = VOS_NULL_PTR;
    TAF_XPDS_FWDLINK_RSP_GPS_ALM_STRU  *pstProvAlm = VOS_NULL_PTR;

    pstProvEph = &(TAF_XPDS_GetPdePublicData()->stProvGpsEph);
    pstProvAlm = &(TAF_XPDS_GetPdePublicData()->stProvGpsAlm);

    /* 如果EPH、ALM数据包的数目均为0，认为数据无效，返回超时；
       否则认为数据有效，返回成功
    */
    if ((0 == pstProvEph->ucNumOfSvP) && (0 == pstProvAlm->ucNumOfSvP))
    {
        TAF_XPDS_SndInternalPdeProcRsltInd(TAF_XPDS_PDE_PROC_RSLT_TIMER_OUT);
    }
    else
    {
        /* 如果没有向GPS发过EPH数据，则发送 */
        if (VOS_FALSE == TAF_XPDS_GetGpsEphDataFinishedFlag())
        {
            if (VOS_TRUE == TAF_XPDS_GetRespGpsIonInEphimFlag())
            {
                TAF_XPDS_SndAtGpsIonInfo();
                TAF_XPDS_SetRespGpsIonInEphimFlag(VOS_FALSE);
            }

            TAF_XPDS_SndAtGpsEphInfo();
        }

        /* 如果没有向GPS发过ALM数据，则发送 */
        if (VOS_FALSE == TAF_XPDS_GetGpsAlmDataFinishedFlag())
        {
            TAF_XPDS_SndAtGpsAlmInfo();
        }

        TAF_XPDS_SndInternalPdeProcRsltInd(TAF_XPDS_PROC_RSLT_SUCC);
    }

    TAF_XPDS_ProcQuitL2Pde_L2Pde();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_RcvXpdsAbnormalAbortSessionInd_L2Pde_MsbWaitPdeData
 功能描述  : MSB_WAIT_PDE_DATA状态收到等待ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND
             消息的处理
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 已处理
             VOS_FALSE - 未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月09日
    作    者   : y00174758
    修改内容   : AGPS迭代2新增
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsAbnormalAbortSessionInd_L2Pde(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU *pstAbortIndMsg;

    pstAbortIndMsg = (TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU *)(pstMsg);

    switch (pstAbortIndMsg->enAbortScene)
    {
        case TAF_XPDS_PROC_RSLT_AT_STOP:
        case TAF_XPDS_PROC_RSLT_XSMS_NI_CANCEL:
        case TAF_XPDS_PROC_RSLT_XSMS_SI_CANCEL:
        case TAF_XPDS_PROC_RSLT_XSMS_SI_REFRESH:
        case TAF_XPDS_PROC_RSLT_XSMS_SI_LONGINACTIVE:
        case TAF_XPDS_PROC_RSLT_UP_PDE_DISCONNECT:
        case TAF_XPDS_PROC_RSLT_IS801_TIMEOUT:
            TAF_XPDS_SndInternalPdeProcRsltInd(pstAbortIndMsg->enAbortScene);

            TAF_XPDS_ProcQuitL2Pde_L2Pde();
            break;

        default:
            break;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_ProcReqFromPde_L2Pde
 功能描述  : 处理PDE来的请求消息
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 已处理
             VOS_FALSE - 未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : x00314862
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_ProcReqFromPde_L2Pde
(
    VOS_UINT32                          ulDataMask,
    TAF_XPDS_CALL_TYPE_ENUM_UINT8       enCallType
)
{
    TAF_XPDS_ENCODE_RL_INFO_STRU        stEncodeRlInfo;
    VOS_UINT32                          ulTimerLen;

    /* in order to provide psuedo range measurement, first need to request for aquisition asssitance request to PDE */
    if ((TAF_XPDS_RCV_PDE_DATA_MASK_REQ_PSEURANGE_MEAS)
     == (TAF_XPDS_RCV_PDE_DATA_MASK_REQ_PSEURANGE_MEAS & ulDataMask))
    {
        PS_MEM_SET(&stEncodeRlInfo, 0x00, sizeof(TAF_XPDS_ENCODE_RL_INFO_STRU));

        stEncodeRlInfo.aucReqType[0] = TAF_XPDS_RL_MSGTYPE_REQ_GPS_ACQ_ASSIST;
        stEncodeRlInfo.ucNumOfReq    = 1;

        TAF_XPDS_SndPdeReverseMsg_L2Pde(&stEncodeRlInfo, enCallType);

        (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_PDE_ASSIST_DATA_CNF, TI_TAF_XPDS_WAIT_PDE_CNF_TIMER_LEN);

        ulTimerLen = TAF_XPDS_GetPrmTimerLimitLen();

        if (0 != ulTimerLen)
        {
            (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_RSP_PDE_PSEUDORANGE_REQ_QUALITY, ulTimerLen);
        }
    }

    if ((TAF_XPDS_RCV_PDE_DATA_MASK_REQ_MS_INFO)
     == (TAF_XPDS_RCV_PDE_DATA_MASK_REQ_MS_INFO & ulDataMask))
    {
        PS_MEM_SET(&stEncodeRlInfo, 0x00, sizeof(TAF_XPDS_ENCODE_RL_INFO_STRU));

        stEncodeRlInfo.aucRspType[0] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_MS_INFO;
        stEncodeRlInfo.ucNumOfResp   = 1;

        TAF_XPDS_SndPdeReverseMsg_L2Pde(&stEncodeRlInfo, enCallType);
    }

    if ((TAF_XPDS_RCV_PDE_DATA_MASK_REQ_PILOT_PHASE_MEAS)
     == (TAF_XPDS_RCV_PDE_DATA_MASK_REQ_PILOT_PHASE_MEAS & ulDataMask))
    {
        TAF_XPDS_UpdatePpmInGlobal();

        PS_MEM_SET(&stEncodeRlInfo, 0x00, sizeof(TAF_XPDS_ENCODE_RL_INFO_STRU));

        stEncodeRlInfo.aucRspType[0] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_PILPHASE_MEAS;
        stEncodeRlInfo.ucNumOfResp   = 1;

        TAF_XPDS_SndPdeReverseMsg_L2Pde(&stEncodeRlInfo, enCallType);

    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_ProcPdeLocationRsp_L2Pde
 功能描述  : 收到PDE回复的Location info，需要发送给GPS
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月25日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_ProcPdeLocationRsp_L2Pde(VOS_VOID)
{
    TAF_XPDS_FIX_MODE_ENUM_UINT8        enFixMode;

    enFixMode = TAF_XPDS_GetAgpsFixMode();

    /* Get Location INfo From GPS, And need to send to GPS */
    TAF_XPDS_SndAtGpsPositionInfo();

    /* MSA AfLT流程中，位置信息计算是在PDE, 获取位置信息后，可以断开PDE的链路 */
    if ((TAF_XPDS_MSA_MODE  == enFixMode)
     || (TAF_XPDS_AFLT_MODE == enFixMode))
    {
        if (TAF_XPDS_PDE_SESSION_STATUS_ENDED != TAF_XPDS_GetPdeSessionStatus())
        {
           /* if ucSessStart's value equals 0, means that MS don't receive End Indication From PDE, So MS Can send end Frist  */
            TAF_XPDS_SndAtApPdeSessionEndMsg();

            TAF_XPDS_SetPdeSessionStatus(TAF_XPDS_PDE_SESSION_STATUS_ENDED);

            TAF_XPDS_MNTN_TraceSessionEndIndMsg();
        }
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XPDS_ProcEphData_L2Pde_MsbWaitPdeData
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
VOS_VOID TAF_XPDS_ProcEphData_L2Pde_MsbWaitPdeData(VOS_VOID)
{
    if (VOS_TRUE == TAF_XPDS_GetRespGpsIonInEphimFlag())
    {
        TAF_XPDS_SndAtGpsIonInfo();
        TAF_XPDS_SetRespGpsIonInEphimFlag(VOS_FALSE);
    }

    TAF_XPDS_SndAtGpsEphInfo();

    /* 如果所有ALM数据包已接收完成，定位成功，退出PDE L2状态机；
       否则把EPH数据完成标志设置成TRUE，等待ALM数据包完成
    */
    if (VOS_TRUE == TAF_XPDS_GetGpsAlmDataFinishedFlag())
    {
        TAF_XPDS_SndInternalPdeProcRsltInd(TAF_XPDS_PROC_RSLT_SUCC);

        TAF_XPDS_ProcQuitL2Pde_L2Pde();
    }
    else
    {
        TAF_XPDS_SetGpsEphDataFinishedFlag(VOS_TRUE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_ProcAlmData_L2Pde_MsbWaitPdeData
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
VOS_VOID TAF_XPDS_ProcAlmData_L2Pde_MsbWaitPdeData(VOS_VOID)
{
    TAF_XPDS_SndAtGpsAlmInfo();

    /* 如果所有EPH数据包已接收完成，定位成功，退出PDE L2状态机；
       否则把ALM数据完成标志设置成TRUE，等待EPH数据包完成
    */
    if (VOS_TRUE == TAF_XPDS_GetGpsEphDataFinishedFlag())
    {
        TAF_XPDS_SndInternalPdeProcRsltInd(TAF_XPDS_PROC_RSLT_SUCC);

        TAF_XPDS_ProcQuitL2Pde_L2Pde();
    }
    else
    {
        TAF_XPDS_SetGpsAlmDataFinishedFlag(VOS_TRUE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_ProcQuitL2Pde_L2Pde
 功能描述  : 退出L2 PDE状态机处理
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
VOS_VOID TAF_XPDS_ProcQuitL2Pde_L2Pde(VOS_VOID)
{
    /* 如果PDE没有下发SS_SEND消息，向PDE发送SS_SEND消息 */
    if (TAF_XPDS_PDE_SESSION_STATUS_ENDED != TAF_XPDS_GetPdeSessionStatus())
    {
        TAF_XPDS_SndAtApPdeSessionEndMsg();

        TAF_XPDS_SetPdeSessionStatus(TAF_XPDS_PDE_SESSION_STATUS_ENDED);
    }

    TAF_XPDS_StopAllL2PdeTimer_L2Pde();

    TAF_XPDS_IncreaseSessTagInRsvPdMsgHeader();

    TAF_XPDS_InitPdePublicDataPdeInit();

    TAF_XPDS_QuitFsmL2();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndPdeStartDeliverData_L2Pde
 功能描述  : MS send start delive data to PDE server
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月23日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SndPdeStartDeliverData_L2Pde(VOS_VOID)
{
    VOS_UINT8                          *pucEncodeBuf       = VOS_NULL_PTR;
    TAF_XPDS_START_DELV_DATA_STRU       stStartDelvData;
    VOS_UINT32                          ulMsgBufLen;

    pucEncodeBuf  = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_XPDS, TAF_XPDS_MAX_PDM_MSG_BUF_LEN);

    if (VOS_NULL_PTR == pucEncodeBuf)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndPdeStartDeliverData_L2Pde, malloc failed");

        return;
    }

    PS_MEM_SET(pucEncodeBuf, 0x00, TAF_XPDS_MAX_PDM_MSG_BUF_LEN);

    PS_MEM_SET(&stStartDelvData, 0x00, sizeof(TAF_XPDS_START_DELV_DATA_STRU));

    stStartDelvData.ucMSIDType = TAF_XPDS_MSID_TYPE;
    stStartDelvData.ucMSIDLen  = TAF_XPDS_MSID_DATA_LEN_IN_BYTE;
    stStartDelvData.ucLength   = TAF_XPDS_START_DELIVERY_DATA_LEN_IN_BYTE;

    TAF_XPDS_GetMsIdRecFromCard(stStartDelvData.stMsIdRec.aucMsIdRec);

    ulMsgBufLen = 0;

    TAF_XPDS_MNTN_TraceReverseStartDeliverData(&stStartDelvData);

    TAF_XPDS_EncodeStartDeliverData(&stStartDelvData, pucEncodeBuf, &ulMsgBufLen);

    /* in control plane send data burst message */
    if (TAF_XPDS_CTRL_PLANE == TAF_XPDS_GetAgpsCfg()->enCallType)
    {
        TAF_XPDS_SndCasDataBurstMsg(pucEncodeBuf, ulMsgBufLen);
    }
    else
    {
        TAF_XPDS_SndAtApReverseData(AT_XPDS_SERVER_MODE_PDE, pucEncodeBuf, ulMsgBufLen);
    }

    PS_MEM_FREE(UEPS_PID_XPDS, pucEncodeBuf);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_SndPdeReverseMsg_L2Pde
 功能描述  : 构造码流后，发送给网络侧的PDE
 输入参数  : TAF_XPDS_ENCODE_RL_INFO_STRU       *pstEncodeRlInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XPDS_SndPdeReverseMsg_L2Pde(
    TAF_XPDS_ENCODE_RL_INFO_STRU       *pstEncodeRlInfo,
    TAF_XPDS_CALL_TYPE_ENUM_UINT8       enCallType
)
{
    VOS_UINT8                          *pucEncodeBuf;
    VOS_UINT32                          ulEncodeBufLength;

    /* allocate memory for the message */
    pucEncodeBuf  = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_XPDS, TAF_XPDS_MAX_PDM_MSG_BUF_LEN);

    if (VOS_NULL_PTR == pucEncodeBuf)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndPdeReverseMsg_L2Pde, malloc failed");
        return;
    }

    PS_MEM_SET(pucEncodeBuf, 0x00, TAF_XPDS_MAX_PDM_MSG_BUF_LEN);

    ulEncodeBufLength = 0;

    TAF_XPDS_MNTN_TraceReverseMsgInfoIndMsg(pstEncodeRlInfo);

    TAF_XPDS_EncodeReverseMsg(pstEncodeRlInfo, pucEncodeBuf, &ulEncodeBufLength);

    /* in control plane send data burst message */
    if (TAF_XPDS_CTRL_PLANE == enCallType)
    {
        TAF_XPDS_SndCasDataBurstMsg(pucEncodeBuf, ulEncodeBufLength);
    }
    else
    {
        TAF_XPDS_SndAtApReverseData(AT_XPDS_SERVER_MODE_PDE, pucEncodeBuf, ulEncodeBufLength);
    }

    PS_MEM_FREE(UEPS_PID_XPDS, pucEncodeBuf);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_StopAllL2PdeTimer_L2Pde
 功能描述  : 停止所有PDE状态机的定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月8日
    作    者   : y00174758
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XPDS_StopAllL2PdeTimer_L2Pde(VOS_VOID)
{
    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_RSP_PDE_PSEUDORANGE_REQ_QUALITY);
    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_GPS_PRECISION_PSEUDORANGE_INFO);
    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_GPS_PSEUDORANGE_CNF);
    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_PDE_ASSIST_DATA_CNF);
    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_PDE_LOCATION_INFO_CNF);
    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_PDE_MSB_DATA);

    return;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */








