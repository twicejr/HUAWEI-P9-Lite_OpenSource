/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Aps_DealApiFlowMsgPara.c
  版 本 号   : 初稿
  作    者   : anhuiqing / 00165503
  生成日期   : 2011年09月30日
  最近修改   :
  功能描述   :
  函数列表   :

  修改历史   :
  1.日    期   : 2011年03月30日
    作    者   : anhuiqing / 00165503
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "Taf_Aps.h"
#include "MnApsComm.h"
#include "NasMmlCtx.h"
#include "TafApsSndAds.h"
#if ( FEATURE_ON == FEATURE_LTE )
#include "v_lib.h"
#endif
#include "TafMd5.h"
#include "TafApsCtx.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsComFunc.h"
#include "TafLog.h"
#include "TafSdcLib.h"
#include "AtPppInterface.h"
#include "TafAppPpp.h"
#include "TafApsMntn.h"
#include "TafApsSndCds.h"
#include "TafApsSndInternalMsg.h"
#include "NasStkInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/


#define    THIS_FILE_ID        PS_FILE_ID_TAF_APSDEALAPIFLOWMSGPARA_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_APS_SndPsEvt
 功能描述  : 发送PS域事件
 输入参数  : ulTaskId                   - 目标任务ID(PID)
             ulEvtId                    - 事件ID
             pData                      - 事件数据内容(不包含消息头)
             ulLength                   - 事件数据长度
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年12月24日
    作    者   : z00220246
    修改内容   : DSDA Phase II

  3.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换，改为pData携带TaskId
*****************************************************************************/
VOS_UINT32 TAF_APS_SndPsEvt(
    VOS_UINT32                          ulEvtId,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult = VOS_OK;
    TAF_PS_EVT_STRU                    *pstMsg   = VOS_NULL_PTR;
    TAF_CTRL_STRU                      *pstCtrl  = VOS_NULL_PTR;

    /* 构造事件消息: PS域事件消息结构见TAF_PS_EVT_STRU */
    pstMsg = (TAF_PS_EVT_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                    WUEPS_PID_TAF,
                    sizeof(MSG_HEADER_STRU) + sizeof(VOS_UINT32) + ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_ERR;
    }

    /* 调用TAF_APS_SndPsEvt发消息的消息结构头都是TAF_CTRL_STRU */
    pstCtrl = (TAF_CTRL_STRU *)pData;

    pstCtrl->usClientId = MN_GetRealClientId(pstCtrl->usClientId, WUEPS_PID_TAF);

    /* 填写事件消息头 */
    pstMsg->stHeader.ulReceiverPid = pstCtrl->ulModuleId;
    pstMsg->stHeader.ulMsgName     = MN_CALLBACK_PS_CALL;

    /* 填写事件ID */
    pstMsg->ulEvtId                = ulEvtId;

    /* 填写事件内容 */
    PS_MEM_CPY(pstMsg->aucContent, pData, ulLength);

    /* 发送消息 */
    ulResult = PS_SEND_MSG(WUEPS_PID_TAF, pstMsg);
    if (VOS_OK != ulResult)
    {
        MN_ERR_LOG1("TAF_APS_SndPsEvt: Send message failed. <EvtId>",
                    (VOS_INT32)ulEvtId);
        return VOS_ERR;
    }

    /* 消息勾包 */
    TAF_APS_TraceApsEvt(ulEvtId, ulLength, (VOS_UINT8 *)pData);

    return VOS_OK;
}

/*****************************************************************************
 Prototype      : TAF_APS_SndPdpActivateCnf
 Description    :
 Input          :
 Output         :
 Return Value   :
 Date Accessed  :
 Date Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.Date        : 2006-07-06
    Author      : L47619
    Modification: 根据问题单修改:A32D04774

  3.Date        : 2007-11-09
    Author      : L47619
    Modification: 根据问题单修改:A32D13403

  4.日    期   : 2011年04月23日
    作    者   : L00171473
    修改内容   : for V7R1 porting, 设置NBNS和GateWay

  5.日    期   : 2012年1月2日
    作    者   : A00165503
    修改内容   : PS Project: 增加P-CSCF事件的上报

  6.日    期   : 2012年1月27日
    作    者   : h44270
    修改内容   : PS融合项目，删除冗余代码和全局变量

  7.日    期   : 2012年11月13日
    作    者   : A00165503
    修改内容   : DTS2012111205973: LTE默认缺省承载IP类型IPv4v6, 用户拨号IP类
                 型IPv4 only或IPv6 only, 缺省承载IP类型被错误的修改为用户拨
                 号IP类型
  8.日    期   : 2012年12月26日
    作    者   : m00217266
    修改内容   : DSDA C核项目(删除冗余代码)
  9.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，结构名称修改
 10.日    期   : 2014年06月16日
    作    者   : f00179208
    修改内容   : VTLTE项目,消息使用动态申请并添加TFT信息
*****************************************************************************/
VOS_VOID TAF_APS_SndPdpActivateCnf(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
)
{
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPdpActCnfEvt;


    pstPdpActCnfEvt = (TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                      sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    /* 申请消息失败 */
    if (VOS_NULL_PTR == pstPdpActCnfEvt)
    {
        /* 系统异常打印, 直接返回 */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndPdpActivateCnf: PS_MEM_ALLOC Error!");
        return;
    }

    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    PS_MEM_SET(pstPdpActCnfEvt, 0, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    pstPdpActCnfEvt->ucCid = ucCid;

    TAF_APS_SetPsCallEvtCtrl(ucPdpId, pstPdpActCnfEvt->ucCid, &pstPdpActCnfEvt->stCtrl);

    TAF_APS_FillEvtPdpType(&pstPdpActCnfEvt->stPdpAddr.enPdpType, ucPdpId, ucCid);
    if (VOS_OK == Aps_SetEvtAddr(ucPdpId, &pstPdpActCnfEvt->stPdpAddr))
    {
        pstPdpActCnfEvt->bitOpPdpAddr        = VOS_TRUE;
    }

    pstPdpActCnfEvt->ucRabId = g_PdpEntity[ucPdpId].ucNsapi;

    if (VOS_OK == Aps_SetEvtApn(ucPdpId, &pstPdpActCnfEvt->stApn))
    {
        pstPdpActCnfEvt->bitOpApn = VOS_TRUE;
    }

    /* UMTS QOS */
    if (VOS_TRUE == g_PdpEntity[ucPdpId].PdpQosFlag)
    {
        pstPdpActCnfEvt->bitOpUmtsQos = VOS_TRUE;
        Aps_3GQos2AppQos(&g_PdpEntity[ucPdpId].PdpQos, &pstPdpActCnfEvt->stUmtsQos);
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* EPS QOS */
    if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpEpsQos)
    {
        pstPdpActCnfEvt->bitOpEpsQos  = VOS_TRUE;
        pstPdpActCnfEvt->stEpsQos     = g_PdpEntity[ucPdpId].stEpsQos;
    }

    if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpPf)
    {
        pstPdpActCnfEvt->bitOpTft = VOS_TRUE;
        TAF_APS_SetEvtTftInfo(ucPdpId, &pstPdpActCnfEvt->stTft);
    }
#endif

    if (APS_PDP_ACT_SEC == g_PdpEntity[ucPdpId].ActType)
    {
        pstPdpActCnfEvt->bitOpLinkdRabId  = VOS_TRUE;
        pstPdpActCnfEvt->ucLinkdRabId     = g_PdpEntity[ucPdpId].ucLinkedNsapi;
    }

    if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpImCnSigalFlag)
    {
        pstPdpActCnfEvt->bitOpImCnSignalFlg   = VOS_TRUE;
        pstPdpActCnfEvt->enImCnSignalFlg      = g_PdpEntity[ucPdpId].enImCnSignalFlg;
    }

    pstPdpActCnfEvt->bitOpEmergencyInd    = VOS_TRUE;
    pstPdpActCnfEvt->enEmergencyInd       = g_PdpEntity[ucPdpId].enEmergencyFlg;

    Aps_SetEvtDns(ucPdpId, &pstPdpActCnfEvt->stDns, &pstPdpActCnfEvt->stIpv6Dns);
    MN_APS_SetEvtNbns(ucPdpId, &pstPdpActCnfEvt->stNbns);
    MN_APS_SetEvtGateWay(ucPdpId, pstPdpActCnfEvt);
    TAF_APS_SetEvtPcscf(ucPdpId, &pstPdpActCnfEvt->stPcscf, &pstPdpActCnfEvt->stIpv6Pcscf);


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* CDMA模式下如果用户下发IPV4V6拨号，当前只支持IPV4/IPV6通知用户不支持双栈 */
    TAF_APS_AddCauseForCdataDoalStackDailNotSuport(pstPdpActCnfEvt, ucPdpId, ucCid);


#endif

    /* Added by m00217266 for L-C互操作项目, 2014-1-23, begin */
    /* 通知ADS PDP状态，当module为imsa不需要通知ADS PDP状态 */
    TAF_APS_NotifyAdsWhenPdpAvtivated(pstPdpActCnfEvt);
    /* Added by m00217266 for L-C互操作项目, 2014-1-23, end */


#if (FEATURE_ON == FEATURE_IPV6)
    /* 更新为实体中记录的原因值 */
    MN_APS_SET_EVT_SM_CAUSE(pstPdpActCnfEvt, ucPdpId);
#endif

    /*调用TAF提供的事件上报函数 */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF,
                     pstPdpActCnfEvt,
                     sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    /* 释放内存 */
    PS_MEM_FREE(WUEPS_PID_TAF, pstPdpActCnfEvt);

    APS_NORM_LOG("APS->APP ACT_CNF MSG ");


    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndPdpActivateRej
 功能描述  : 上报PS域呼叫拒绝事件
 输入参数  : ucPdpId --- 实体索引
             enCause --- 错误码
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月8日
    作    者   : Y00213812
    修改内容   : 新生成函数

  2.日    期   : 2014年5月15日
    作    者   : A00165503
    修改内容   : DTS2014051501929: 填写PS域呼叫拒绝事件的IP类型
*****************************************************************************/
VOS_VOID TAF_APS_SndPdpActivateRej(
    VOS_UINT8                           ucPdpId,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stPdpActRejEvt;

    PS_MEM_SET(&stPdpActRejEvt, 0, sizeof(TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU));

   /* 如果不是APP主动发起的激活,或手动应答发起激活,上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ */
    if ( (APS_APP_INIT_ACT != g_PdpEntity[ucPdpId].PdpProcTrack.ucHowToInitAct)
        && (APS_APP_MANUL_ACT != g_PdpEntity[ucPdpId].PdpProcTrack.ucHowToInitAct))
    {
        /* APS自动发起的激活,则不上报 */
        return;
    }

    stPdpActRejEvt.ucCid     = g_PdpEntity[ucPdpId].stClientInfo.ucCid;

    TAF_APS_SetPsCallEvtCtrl(ucPdpId, stPdpActRejEvt.ucCid, &stPdpActRejEvt.stCtrl);

    stPdpActRejEvt.enPdpType = TAF_APS_GetPdpEntDialPdpType(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    stPdpActRejEvt.enCause   = enCause;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ,
                     &stPdpActRejEvt,
                     sizeof(TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU));

#if (FEATURE_ON == FEATURE_PTM)
    /* 记录PS拨号异常log */
    TAF_APS_PsCallFailErrRecord(enCause);
#endif



    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndPdpActivateInd
 功能描述  : 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_IND
 输入参数  : ucPdpId        -实体ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目新增
  2.日    期   : 2014年06月16日
    作    者   : f00179208
    修改内容   : VTLTE项目,消息使用动态申请并添加TFT信息
*****************************************************************************/
VOS_VOID TAF_APS_SndPdpActivateInd(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
)
{
    TAF_PS_CALL_PDP_ACTIVATE_IND_STRU  *pstPdpActIndEvt;

    pstPdpActIndEvt = (TAF_PS_CALL_PDP_ACTIVATE_IND_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                      sizeof(TAF_PS_CALL_PDP_ACTIVATE_IND_STRU));

    /* 申请消息失败 */
    if (VOS_NULL_PTR == pstPdpActIndEvt)
    {
        /* 系统异常打印, 直接返回 */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndPdpActivateInd: PS_MEM_ALLOC Error!");
        return;
    }

    /* 初始化 */
    PS_MEM_SET(pstPdpActIndEvt, 0, sizeof(TAF_PS_CALL_PDP_ACTIVATE_IND_STRU));

    /* 消息头 */
    TAF_APS_SetPsCallEvtCtrl(ucPdpId, ucCid, &pstPdpActIndEvt->stCtrl);

    pstPdpActIndEvt->ucCid = ucCid;

    /* PDP类型和地址 */
    pstPdpActIndEvt->stPdpAddr.enPdpType = TAF_APS_ConvertPdpType(g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum);
    if (VOS_OK == Aps_SetEvtAddr(ucPdpId, &pstPdpActIndEvt->stPdpAddr))
    {
        pstPdpActIndEvt->bitOpPdpAddr        = VOS_TRUE;
    }

    /* RBAID */
    pstPdpActIndEvt->ucRabId = g_PdpEntity[ucPdpId].ucNsapi;

    /* 设置APN */
    if (VOS_OK == Aps_SetEvtApn(ucPdpId, &pstPdpActIndEvt->stApn))
    {
        pstPdpActIndEvt->bitOpApn = VOS_TRUE;
    }

    /* UMTS QOS */
    if (VOS_TRUE == g_PdpEntity[ucPdpId].PdpQosFlag)
    {
        pstPdpActIndEvt->bitOpUmtsQos = VOS_TRUE;
        Aps_3GQos2AppQos(&g_PdpEntity[ucPdpId].PdpQos, &pstPdpActIndEvt->stUmtsQos);
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* EPS QOS */
    if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpEpsQos)
    {
        pstPdpActIndEvt->bitOpEpsQos  = VOS_TRUE;
        pstPdpActIndEvt->stEpsQos     = g_PdpEntity[ucPdpId].stEpsQos;
    }

    if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpPf)
    {
        pstPdpActIndEvt->bitOpTft = VOS_TRUE;
        TAF_APS_SetEvtTftInfo(ucPdpId, &pstPdpActIndEvt->stTft);
    }
#endif

    if (APS_PDP_ACT_SEC == g_PdpEntity[ucPdpId].ActType)
    {
        pstPdpActIndEvt->bitOpLinkdRabId  = VOS_TRUE;
        pstPdpActIndEvt->ucLinkdRabId     = g_PdpEntity[ucPdpId].ucLinkedNsapi;
    }

    if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpImCnSigalFlag)
    {
        pstPdpActIndEvt->bitOpImCnSignalFlg   = VOS_TRUE;
        pstPdpActIndEvt->enImCnSignalFlg      = g_PdpEntity[ucPdpId].enImCnSignalFlg;
    }

    pstPdpActIndEvt->bitOpEmergencyInd    = VOS_TRUE;
    pstPdpActIndEvt->enEmergencyInd       = g_PdpEntity[ucPdpId].enEmergencyFlg;

    /* DNS */
    Aps_SetEvtDns(ucPdpId, &pstPdpActIndEvt->stDns, &pstPdpActIndEvt->stIpv6Dns);

    /* NBNS */
    MN_APS_SetEvtNbns(ucPdpId, &pstPdpActIndEvt->stNbns);

    /* GATE WAY */
    MN_APS_SetEvtGateWay(ucPdpId, pstPdpActIndEvt);

    /* P-CSCF */
    TAF_APS_SetEvtPcscf(ucPdpId, &pstPdpActIndEvt->stPcscf, &pstPdpActIndEvt->stIpv6Pcscf);

#if (FEATURE_ON == FEATURE_IPV6)
    MN_APS_SET_EVT_SM_CAUSE(pstPdpActIndEvt, ucPdpId);
#endif

    /* 发送ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_IND给IMSA */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_IND,
                     pstPdpActIndEvt,
                     sizeof(TAF_PS_CALL_PDP_ACTIVATE_IND_STRU));

    /* 释放内存 */
    PS_MEM_FREE(WUEPS_PID_TAF, pstPdpActIndEvt);

    APS_NORM_LOG("APS->APP ACT_IND MSG ");
    return;
}


/*****************************************************************************
 Prototype      : TAF_APS_SndPdpManageInd
 Description    :
 Input          :
 Output         :
 Return Value   :
 Date Accessed  :
 Date Update    :
 Calls          : Aps_PdpActIndManualAns
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
  2.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : PS融合项目修改 :增加返回值，将拒绝网络请求移到状态机中处理
  3.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换，增加PID，使用ID_EVT_TAF_PS_CALL_PDP_MANAGE_IND
*****************************************************************************/
VOS_UINT32 TAF_APS_SndPdpManageInd(
    VOS_UINT8                           ucPdpId,
    SMREG_PDP_ACTIVATE_IND_STRU        *pStActInd
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT16                          ClientId;
    TAF_PS_CALL_PDP_MANAGE_IND_STRU     stPdpManageIndEvt;

    ClientId                            = TAF_CLIENTID_BROADCAST;

    /*clean "stPdpActIndEvt" */
    PS_MEM_SET(&stPdpManageIndEvt, 0, sizeof(TAF_PS_CALL_PDP_MANAGE_IND_STRU));

    /*把SM传来的信息填入PDP表项中,手动应答时要读取这些信息:ADDR, APN*/
    /*ADDR信息分解为ADDRTYPE和ADDR两个信息*/
    ulRet   = Aps_DetachSmAddrStru(     &pStActInd->stOfferPdpAddr,
                                        &g_PdpEntity[ucPdpId].PdpAddr   );
    if ( TAF_APS_FAIL == ulRet)
    {
        APS_WARN_LOG("ERROR! Getting PpdAddr of ACT_IND fail ! Aps_PdpActInd()");
        return TAF_APS_FAIL;
    }
    g_PdpEntity[ucPdpId].PdpAddrFlag    = VOS_TRUE;

    /*APN*/
    if ( pStActInd->bitOpAcsPointName)
    {
        g_PdpEntity[ucPdpId].PdpApnFlag = VOS_TRUE;
        Aps_DetachSmApn(&pStActInd->stAcsPointName, &g_PdpEntity[ucPdpId].PdpApn);
    }

    /* GU模式下，手动应答由AT完成 */
    stPdpManageIndEvt.stCtrl.ulModuleId    = WUEPS_PID_AT;
    stPdpManageIndEvt.stCtrl.usClientId    = ClientId;

    /*上报给APP，OpId就是此PDP激活的标识,该OpId等于120 + ucPdpId*/
    stPdpManageIndEvt.stCtrl.ucOpId        = APS_MT_DIFF_VALU + ucPdpId;

    if (VOS_OK == Aps_SetEvtAddr(ucPdpId, &stPdpManageIndEvt.stPdpAddr))
    {
        stPdpManageIndEvt.bitOpPdpAddr     = VOS_TRUE;
    }

    if (VOS_OK == Aps_SetEvtApn(ucPdpId, &stPdpManageIndEvt.stApn))
    {
        stPdpManageIndEvt.bitOpApn = VOS_TRUE;
    }

    /* 填充PDP类型 */

    stPdpManageIndEvt.stPdpAddr.enPdpType = TAF_APS_ConvertPdpType(g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum);

    /* 记录将网络发起PDP激活的类型，用于answer后上报结果 */
    TAF_APS_SetPdpEntDialPdpType(ucPdpId,
                                g_PdpEntity[ucPdpId].stClientInfo.ucCid,
                                stPdpManageIndEvt.stPdpAddr.enPdpType);


    /* 上报TAFM */
    APS_NORM_LOG("APS->APP  ID_EVT_TAF_PS_CALL_PDP_MANAGE_IND");
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_PDP_MANAGE_IND,
                     &stPdpManageIndEvt,
                     sizeof(TAF_PS_CALL_PDP_MANAGE_IND_STRU));


    return TAF_APS_SUCC;
}


/*****************************************************************************
 Prototype      : TAF_APS_SndPdpModifyCnf
 Description    :
 Input          :
 Output         :
 Return Value   :
 Date Accessed  :
 Date Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.日    期   : 2012年11月13日
    作    者   : A00165503
    修改内容   : DTS2012111205973: LTE默认缺省承载IP类型IPv4v6, 用户拨号IP类
                 型IPv4 only或IPv6 only, 缺省承载IP类型被错误的修改为用户拨
                 号IP类型

  3.日    期   : 2012年12月26日
    作    者   : m00217266
    修改内容   : DSDA C核项目(删除冗余代码)

  4.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，结构变更

  5.日    期   : 2014年5月15日
    作    者   : A00165503
    修改内容   : DTS2014051501929: 填写PS域修改拒绝事件的RABID
  6.日    期   : 2014年06月16日
    作    者   : f00179208
    修改内容   : VTLTE项目,消息使用动态申请并添加TFT信息
*****************************************************************************/
VOS_VOID TAF_APS_SndPdpModifyCnf(VOS_UINT8 ucPdpId)
{
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU        *pstPdpMdfCnfEvt;

    pstPdpMdfCnfEvt = (TAF_PS_CALL_PDP_MODIFY_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                      sizeof(TAF_PS_CALL_PDP_MODIFY_CNF_STRU));

    /* 申请消息失败 */
    if (VOS_NULL_PTR == pstPdpMdfCnfEvt)
    {
        /* 系统异常打印, 直接返回 */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndPdpModifyCnf: PS_MEM_ALLOC Error!");
        return;
    }

    PS_MEM_SET(pstPdpMdfCnfEvt, 0, sizeof(TAF_PS_CALL_PDP_MODIFY_CNF_STRU));

    pstPdpMdfCnfEvt->ucCid = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    TAF_APS_GetPdpEntModDialInfo(ucPdpId, &pstPdpMdfCnfEvt->stCtrl);

    pstPdpMdfCnfEvt->ucRabId = g_PdpEntity[ucPdpId].ucNsapi;

    /* 更新UMTS QOS */
    if (VOS_FALSE != g_PdpEntity[ucPdpId].PdpQosFlag)
    {
        pstPdpMdfCnfEvt->bitOpUmtsQos = TAF_USED;
        Aps_3GQos2AppQos(&g_PdpEntity[ucPdpId].PdpQos, &pstPdpMdfCnfEvt->stUmtsQos);
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* EPS QOS */
    if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpEpsQos)
    {
        pstPdpMdfCnfEvt->bitOpEpsQos  = VOS_TRUE;
        pstPdpMdfCnfEvt->stEpsQos     = g_PdpEntity[ucPdpId].stEpsQos;
    }

    if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpPf)
    {
        pstPdpMdfCnfEvt->bitOpTft = VOS_TRUE;
        TAF_APS_SetEvtTftInfo(ucPdpId, &pstPdpMdfCnfEvt->stTft);
    }
#endif

    Aps_SetEvtDns(ucPdpId, &pstPdpMdfCnfEvt->stDns, &pstPdpMdfCnfEvt->stIpv6Dns);
    MN_APS_SetEvtNbns(ucPdpId, &pstPdpMdfCnfEvt->stNbns);
    TAF_APS_SetEvtPcscf(ucPdpId, &pstPdpMdfCnfEvt->stPcscf, &pstPdpMdfCnfEvt->stIpv6Pcscf);

    /* Added by m00217266 for L-C互操作项目, 2014-1-23, begin */
    /* 通知ADS PDP状态 */
    TAF_APS_NotifyAdsWhenPdpModify(pstPdpMdfCnfEvt);
    /* Added by m00217266 for L-C互操作项目, 2014-1-23, end */

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_PDP_MODIFY_CNF,
                     pstPdpMdfCnfEvt,
                     sizeof(TAF_PS_CALL_PDP_MODIFY_CNF_STRU));

    /* 释放内存 */
    PS_MEM_FREE(WUEPS_PID_TAF, pstPdpMdfCnfEvt);

    return;
}

/*****************************************************************************
 Prototype      : TAF_APS_SndPdpModifyInd
 Description    : UE接受网络的修改指示,需要向APP上报修改后的信息
 Input          :
 Output         :
 Return Value   :
 Date Accessed  :
 Date Update    :
 Calls          :
 Called By      : Aps_PdpMdfIndQosSatisfy
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.日    期   : 2012年11月13日
    作    者   : A00165503
    修改内容   : DTS2012111205973: LTE默认缺省承载IP类型IPv4v6, 用户拨号IP类
                 型IPv4 only或IPv6 only, 缺省承载IP类型被错误的修改为用户拨
                 号IP类型
  3.日    期   : 2012年12月26日
    作    者   : m00217266
    修改内容   : DSDA C核项目(删除冗余代码)
  4.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
  5.日    期   : 2014年06月16日
    作    者   : f00179208
    修改内容   : VTLTE项目,消息使用动态申请并添加TFT信息
*****************************************************************************/
VOS_VOID TAF_APS_SndPdpModifyInd(
    VOS_UINT8                           ucPdpId
)
{
    TAF_PS_CALL_PDP_MODIFY_IND_STRU    *pstPdpMdfIndEvt;
    VOS_UINT8                           i;
    TAF_APS_BITCID_INFO_STRU            stCid;

    pstPdpMdfIndEvt = (TAF_PS_CALL_PDP_MODIFY_IND_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                      sizeof(TAF_PS_CALL_PDP_MODIFY_IND_STRU));

    /* 申请消息失败 */
    if (VOS_NULL_PTR == pstPdpMdfIndEvt)
    {
        /* 系统异常打印, 直接返回 */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndPdpModifyInd: PS_MEM_ALLOC Error!");
        return;
    }

    PS_MEM_SET(&stCid, 0, sizeof(TAF_APS_BITCID_INFO_STRU));
    PS_MEM_SET(pstPdpMdfIndEvt, 0, sizeof(TAF_PS_CALL_PDP_MODIFY_IND_STRU));

    pstPdpMdfIndEvt->ucRabId = g_PdpEntity[ucPdpId].ucNsapi;

    if (VOS_FALSE != g_PdpEntity[ucPdpId].PdpQosFlag)
    {
        pstPdpMdfIndEvt->bitOpUmtsQos = TAF_USED;
        Aps_3GQos2AppQos(&g_PdpEntity[ucPdpId].PdpQos, &pstPdpMdfIndEvt->stUmtsQos);
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* EPS QOS */
    if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpEpsQos)
    {
        pstPdpMdfIndEvt->bitOpEpsQos  = VOS_TRUE;
        pstPdpMdfIndEvt->stEpsQos     = g_PdpEntity[ucPdpId].stEpsQos;
    }

    if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpPf)
    {
        pstPdpMdfIndEvt->bitOpTft = VOS_TRUE;
        TAF_APS_SetEvtTftInfo(ucPdpId, &pstPdpMdfIndEvt->stTft);
    }
#endif

    Aps_SetEvtDns(ucPdpId, &pstPdpMdfIndEvt->stDns, &pstPdpMdfIndEvt->stIpv6Dns);

    MN_APS_SetEvtNbns(ucPdpId, &pstPdpMdfIndEvt->stNbns);

    TAF_APS_SetEvtPcscf(ucPdpId, &pstPdpMdfIndEvt->stPcscf, &pstPdpMdfIndEvt->stIpv6Pcscf);


    /* 存在APN共用时，向所有用户主动上报MODIFY */
    /* 获取当前所有使用该实体的用户 */
    TAF_APS_GetPdpEntBitCidInfo(ucPdpId, &stCid);

    for (i = 0; i < stCid.ulNum; i++)
    {
        pstPdpMdfIndEvt->ucCid = stCid.aucCid[i];

        TAF_APS_SetPsCallEvtCtrl(ucPdpId, pstPdpMdfIndEvt->ucCid, &pstPdpMdfIndEvt->stCtrl);

        /* Added by m00217266 for L-C互操作项目, 2014-1-23, begin */
        /* 通知ADS PDP状态 */
        TAF_APS_NotifyAdsWhenPdpModify(pstPdpMdfIndEvt);
        /* Added by m00217266 for L-C互操作项目, 2014-1-23, end */

        APS_NORM_LOG("APS->APP  ID_EVT_TAF_PS_CALL_PDP_MODIFY_IND");
        (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_PDP_MODIFY_IND,
                         pstPdpMdfIndEvt,
                         sizeof(TAF_PS_CALL_PDP_MODIFY_IND_STRU));
    }

    /* 释放内存 */
    PS_MEM_FREE(WUEPS_PID_TAF, pstPdpMdfIndEvt);

    return;
}


/*****************************************************************************
 Prototype      : TAF_APS_SndPdpModifyRej()
 Description    : 上报APP拒绝修改事件,
 Input          : ucPdpId,
                  RejCause
 Output         : NO
 Return Value   : NO
 Data Accessed  : NO
 Data Update    : NO
 Calls          : Aps_ClearAppEvent()
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : 韩鲁峰
    Modification: Created function
  2.日    期   : 2010年12月24日
    作    者   : lijun 00171473
    修改内容   : DTS2010121603672 CGCMOD打桩修改QOS失败时ERROR错误回到应用
  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
  4.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换

*****************************************************************************/
VOS_VOID    TAF_APS_SndPdpModifyRej   (
    VOS_UINT8                               ucPdpId,
    TAF_PS_CAUSE_ENUM_UINT32                enCause
)
{
    TAF_PS_CALL_PDP_MODIFY_REJ_STRU     stPdpMdfRejEvt;

    PS_MEM_SET(&stPdpMdfRejEvt, 0, sizeof(TAF_PS_CALL_PDP_MODIFY_REJ_STRU));

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    stPdpMdfRejEvt.ucCid = g_PdpEntity[ucPdpId].stClientInfo.ucCid;

    TAF_APS_GetPdpEntModDialInfo(ucPdpId, &stPdpMdfRejEvt.stCtrl);

    /* 网侧发起的MODIFY超时或被拒，不上报 */
    if (0 == stPdpMdfRejEvt.stCtrl.ulModuleId)
    {
        return;
    }

    stPdpMdfRejEvt.enCause        = enCause;

    /*调用TAFM提供的事件上报函数 */
    APS_NORM_LOG("APS->APP ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ");
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ,
                     &stPdpMdfRejEvt,
                     sizeof(TAF_PS_CALL_PDP_MODIFY_REJ_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */
    return;
}


/*****************************************************************************
 Prototype      : TAF_APS_SndPdpDeActivateCnf
 Description    : 3G中收到SM的DEACT_CNF,2G中收到SNDCP的DEACT_RSP后,此函数上报
                  APP去激活结束
 Input          :
 Output         :
 Return Value   :
 Date Accessed  :
 Date Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.日    期   : 2012年1月27日
    作    者   : h44270
    修改内容   : PS融合项目，删除冗余代码和全局变量

  3.日    期   : 2012年11月13日
    作    者   : A00165503
    修改内容   : DTS2012111205973: LTE默认缺省承载IP类型IPv4v6, 用户拨号IP类
                 型IPv4 only或IPv6 only, 缺省承载IP类型被错误的修改为用户拨
                 号IP类型
  4.日    期   : 2012年11月20日
    作    者   : Y00213812
    修改内容   : DTS2012111907501: PDP Deactive时上报原因值TAF_PS_CAUSE_SUCCESS
  5.日    期   : 2012年12月26日
    作    者   : m00217266
    修改内容   : DSDA C核项目(删除冗余代码)
  6.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
*****************************************************************************/
VOS_VOID    TAF_APS_SndPdpDeActivateCnf(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
)
{
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stPdpDeActCnfEvt;

    PS_MEM_SET(&stPdpDeActCnfEvt, 0, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));

    stPdpDeActCnfEvt.ucCid = ucCid;

    TAF_APS_SetPsCallEvtCtrl(ucPdpId, stPdpDeActCnfEvt.ucCid, &stPdpDeActCnfEvt.stCtrl);

    TAF_APS_FillEvtPdpType(&stPdpDeActCnfEvt.enPdpType, ucPdpId, ucCid);

    stPdpDeActCnfEvt.ucRabId = g_PdpEntity[ucPdpId].ucNsapi;

    stPdpDeActCnfEvt.enCause = TAF_PS_CAUSE_SUCCESS;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)



    /* 给CDS发送ID_APS_CDS_CDATA_FREE_BUFF_DATA_IND消息 */
    TAF_APS_SndCdsFreeBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));

#endif

    /* Added by m00217266 for L-C互操作项目, 2014-1-23, begin */
    /* 通知ADS PDP状态 */
    TAF_APS_NotifyAdsWhenPdpDeactivated(&stPdpDeActCnfEvt);
    /* Added by m00217266 for L-C互操作项目, 2014-1-23, end */



    APS_NORM_LOG("APS->APP  ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF");
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF,
                    &stPdpDeActCnfEvt,
                    sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_DISCONNECTED);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndPdpDeActivateInd
 功能描述  : 因为出现异常事件，导致PDP被异常去激活,此函数上报，故其中的
             TEARDOWN不填。
 输入参数  : VOS_UINT8                          ucPdpId
            TAF_PS_CAUSE_ENUM_UINT32            enCause
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年xx月xx日
    作    者   : xxx
    修改内容   : 新生成函数

  2.日    期   : 2010年12月30日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2010122903388，网侧下发DEACTIVATE PDP CONTEXT
                 REQUEST，原因值为#39，AT上报错误

  3.日    期   : 2012年1月27日
    作    者   : h44270
    修改内容   : PS融合项目，删除冗余代码和全局变量

  4.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容    : 修改PS域错误码上报

  5.日    期   : 2012年11月13日
    作    者   : A00165503
    修改内容   : DTS2012111205973: LTE默认缺省承载IP类型IPv4v6, 用户拨号IP类
                 型IPv4 only或IPv6 only, 缺省承载IP类型被错误的修改为用户拨
                 号IP类型
  6.日    期   : 2012年12月26日
    作    者   : m00217266
    修改内容   : DSDA C核项目(删除冗余代码)

  7.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
*****************************************************************************/
VOS_VOID    TAF_APS_SndPdpDeActivateInd(
    VOS_UINT8                           ucPdpId,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU stPdpDeActIndEvt;
    VOS_UINT8                           i;
    TAF_APS_BITCID_INFO_STRU                     stCid;

    PS_MEM_SET(&stCid, 0, sizeof(TAF_APS_BITCID_INFO_STRU));
    PS_MEM_SET(&stPdpDeActIndEvt, 0, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU));

    stPdpDeActIndEvt.ucRabId = g_PdpEntity[ucPdpId].ucNsapi;
    stPdpDeActIndEvt.enCause = enCause;

    /* 获取当前所有使用该实体的用户 */
    TAF_APS_GetPdpEntBitCidInfo(ucPdpId, &stCid);

    for (i = 0; i < stCid.ulNum; i++)
    {
        stPdpDeActIndEvt.ucCid = stCid.aucCid[i];
        TAF_APS_FillEvtPdpType(&stPdpDeActIndEvt.enPdpType, ucPdpId, stPdpDeActIndEvt.ucCid);
        TAF_APS_SetPsCallEvtCtrl(ucPdpId, stPdpDeActIndEvt.ucCid, &stPdpDeActIndEvt.stCtrl);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)



        /* 给CDS发送ID_APS_CDS_CDATA_FREE_BUFF_DATA_IND消息 */
        TAF_APS_SndCdsFreeBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));

#endif

        /* Added by m00217266 for L-C互操作项目, 2014-1-23, begin */
        /* 通知ADS PDP状态 */
        TAF_APS_NotifyAdsWhenPdpDeactivated(&stPdpDeActIndEvt);
        /* Added by m00217266 for L-C互操作项目, 2014-1-23, end */



        APS_NORM_LOG("APS->APP  ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND");
        (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND,
                         &stPdpDeActIndEvt,
                         sizeof(TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU));

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_DISCONNECTED);
#endif
    }
    return;
}


/*****************************************************************************
 函 数 名  : TAF_APS_SndPdpDisconnectInd
 功能描述  : 发送ID_EVT_TAF_PS_CALL_PDP_DISCONNECT_IND消息
 输入参数  : VOS_UINT8 ucPdpId
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月29日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，增加PID记录到实体

*****************************************************************************/
VOS_VOID TAF_APS_SndPdpDisconnectInd(VOS_UINT8 ucPdpId)
{
    TAF_CTRL_STRU                       stCtrl;
    VOS_UINT8                           ucCid;

    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    ucCid = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    stCtrl.usClientId = TAF_APS_GetPdpEntClientId(ucPdpId, ucCid);
    if (TAF_APS_INVALID_CLIENTID == stCtrl.usClientId)
    {
        stCtrl.usClientId = TAF_CLIENTID_BROADCAST;
    }

    stCtrl.ulModuleId = TAF_APS_GetPdpEntModuleId(ucPdpId, ucCid);
    stCtrl.ucOpId     = TAF_APS_GetPdpEntOpId(ucPdpId, ucCid);
    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_PDP_DISCONNECT_IND,
                                &stCtrl,
                                sizeof(TAF_CTRL_STRU));

    return;
}

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : TAF_APS_SndIpv6RaInfoNotifyInd
 功能描述  : 上报ID_EVT_TAF_PS_IPV6_INFO_IND事件
 输入参数  : pstCtrl                 - APP控制头
             ucCid                      - CID
             ucRabId                    - RAB ID
             pstIpv6RaInfo              - IPv6 RA参数信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月2日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年6月30日
    作    者   : A00165503
    修改内容   : DTS2012062900707: IPv6拨号成功, 应用获取IPv6地址前缀异常
*****************************************************************************/
VOS_VOID TAF_APS_SndIpv6RaInfoNotifyInd(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucRabId,
    TAF_PDP_IPV6_RA_INFO_STRU          *pstIpv6RaInfo
)
{
    TAF_PS_IPV6_INFO_IND_STRU           stIpv6RaInfoNotifyInd;

    stIpv6RaInfoNotifyInd.stCtrl        = *pstCtrl;
    stIpv6RaInfoNotifyInd.ucCid         = ucCid;
    stIpv6RaInfoNotifyInd.ucRabId       = ucRabId;
    stIpv6RaInfoNotifyInd.stIpv6RaInfo  = *pstIpv6RaInfo;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_PDP_IPV6_INFO_IND,
                               &stIpv6RaInfoNotifyInd,
                               sizeof(TAF_PS_IPV6_INFO_IND_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_APS_SndCallOrigCnf
 功能描述  :
 输入参数  : TAF_CTRL_STRU                    *pstCtrl
             VOS_UINT8                           ucCid,
             TAF_PS_CAUSE_ENUM_UINT32            enCause
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2012年6月28日
    作    者   : l60609
    修改内容   : AT&T&DCM:PDP激活受限处理
  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
  4.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : C50 IPv6 项目

*****************************************************************************/
VOS_VOID TAF_APS_SndCallOrigCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT8                           ucCid,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    TAF_PS_CALL_ORIG_CNF_STRU           stCallOrigCnf;

    PS_MEM_SET(&stCallOrigCnf, 0x00, sizeof(TAF_PS_CALL_ORIG_CNF_STRU));

    /* 填写事件内容 */
    stCallOrigCnf.stCtrl    = *pstCtrl;
    stCallOrigCnf.ucCid     = ucCid;
    stCallOrigCnf.enCause   = enCause;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    /* 发送事件 */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_ORIG_CNF,
                                &stCallOrigCnf,
                                sizeof(TAF_PS_CALL_ORIG_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */
#if (FEATURE_ON == FEATURE_PTM)
    /* 记录PS拨号异常log */
    TAF_APS_PsCallFailErrRecord(enCause);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndCallEndCnf
 功能描述  :
 输入参数  : pstCtrl
             ucErrCode
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : C50 IPv6 项目

*****************************************************************************/
VOS_VOID TAF_APS_SndCallEndCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT8                           ucCid,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    TAF_PS_CALL_END_CNF_STRU            stCallEndCnf;

    PS_MEM_SET(&stCallEndCnf, 0, sizeof(TAF_PS_CALL_END_CNF_STRU));

    /* 填写事件内容 */
    stCallEndCnf.stCtrl         = *pstCtrl;
    stCallEndCnf.ucCid          = ucCid;

    stCallEndCnf.enCause        = enCause;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    /* 发送事件 */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_END_CNF,
                                &stCallEndCnf,
                                sizeof(TAF_PS_CALL_END_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndCallModifyCnf
 功能描述  :
 输入参数  : pstCtrl
             ucErrCode
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndCallModifyCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    TAF_PS_CALL_MODIFY_CNF_STRU         stCallModifyCnf;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    PS_MEM_SET(&stCallModifyCnf, 0, sizeof(TAF_PS_CALL_MODIFY_CNF_STRU));

    /* 填写事件内容 */
    stCallModifyCnf.stCtrl  = *pstCtrl;
    stCallModifyCnf.enCause = enCause;

    /* 发送事件 */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_MODIFY_CNF,
                                &stCallModifyCnf,
                                sizeof(TAF_PS_CALL_MODIFY_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndCallAnswerCnf
 功能描述  :
 输入参数  : pstCtrl
             ucErrCode
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndCallAnswerCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucErrCode
)
{
    TAF_PS_CALL_ANSWER_CNF_STRU         stCallAnswerCnf;

    PS_MEM_SET(&stCallAnswerCnf, 0, sizeof(TAF_PS_CALL_ANSWER_CNF_STRU));

    /* 填写事件内容 */
    stCallAnswerCnf.stCtrl          = *pstCtrl;
    stCallAnswerCnf.ucCid           = ucCid;

    if ( TAF_ERR_NO_ERROR != ucErrCode )
    {
        if (TAF_ERR_AT_CONNECT == ucErrCode)
        {
            stCallAnswerCnf.enCause = ucErrCode;
        }
        else
        {
            stCallAnswerCnf.enCause = TAF_ERR_ERROR;
        }
    }
    else
    {
        stCallAnswerCnf.enCause = ucErrCode;
    }

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    /* 发送事件 */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_ANSWER_CNF,
                                &stCallAnswerCnf,
                                sizeof(TAF_PS_CALL_ANSWER_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndCallHangupCnf
 功能描述  :
 输入参数  : pstCtrl
             ucErrCode
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndCallHangupCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT8                           ucErrCode
)
{
    TAF_PS_CALL_HANGUP_CNF_STRU         stCallHangupCnf;

    PS_MEM_SET(&stCallHangupCnf, 0, sizeof(TAF_PS_CALL_HANGUP_CNF_STRU));

    /* 填写事件内容 */
    stCallHangupCnf.stCtrl       = *pstCtrl;

    if ( TAF_ERR_NO_ERROR != ucErrCode )
    {
        stCallHangupCnf.enCause = TAF_ERR_ERROR;
    }
    else
    {
        stCallHangupCnf.enCause = ucErrCode;
    }

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    /* 发送事件 */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_HANGUP_CNF,
                                &stCallHangupCnf,
                                sizeof(TAF_PS_CALL_HANGUP_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndSetPdpCtxStateCnf
 功能描述  :
 输入参数  : pstCtrl
            enCause                 原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2011年12月29日
    作    者   : A00165503
    修改内容   : PS Project: 修改函数名称, 匹配当前操作

  3.日    期   : 2012年6月28日
    作    者   : l60609
    修改内容   : AT&T&DCM:PDP激活受限处理

  4.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_VOID TAF_APS_SndSetPdpCtxStateCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    TAF_PS_SET_PDP_STATE_CNF_STRU       stSetPdpStateCnf;

    PS_MEM_SET(&stSetPdpStateCnf, 0x00, sizeof(TAF_PS_SET_PDP_STATE_CNF_STRU));

    /* 填写事件内容 */
    stSetPdpStateCnf.stCtrl             = *pstCtrl;
    stSetPdpStateCnf.enCause            = enCause;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    /* 发送事件 */
   (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_PDP_CONTEXT_STATE_CNF,
                                &stSetPdpStateCnf,
                                sizeof(TAF_PS_SET_PDP_STATE_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndGetPdpStateCnf
 功能描述  :
 输入参数  : VOS_VOID                           *pData
             VOS_UINT32                          ulLength
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_SndGetPdpStateCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_PDP_CONTEXT_STATE_CNF,
                                pData,
                                ulLength);
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndSetPrimPdpCtxInfoCnf
 功能描述  :
 输入参数  : TAF_CTRL_STRU                    *pstCtrl
             VOS_UINT32                          ulErrCode
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_APS_SndSetPrimPdpCtxInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_CNF_STRU   stSetPdpCtxInfoCnf;

    stSetPdpCtxInfoCnf.stCtrl       = *pstCtrl;
    stSetPdpCtxInfoCnf.enCause      = ulErrCode;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_CNF,
                                &stSetPdpCtxInfoCnf,
                                sizeof(TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndGetPrimPdpCtxInfoCnf
 功能描述  :
 输入参数  : VOS_VOID                           *pData
             VOS_UINT32                          ulLength
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_SndGetPrimPdpCtxInfoCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF,
                                pData,
                                ulLength);
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndSetSecPdpCtxInfoCnf
 功能描述  :
 输入参数  : TAF_CTRL_STRU                    *pstCtrl
             VOS_UINT32                          ulErrCode
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_APS_SndSetSecPdpCtxInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    TAF_PS_SET_SEC_PDP_CONTEXT_INFO_CNF_STRU    stSetPdpCtxInfoCnf;

    stSetPdpCtxInfoCnf.stCtrl    = *pstCtrl;
    stSetPdpCtxInfoCnf.enCause  = ulErrCode;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_SEC_PDP_CONTEXT_INFO_CNF,
                                &stSetPdpCtxInfoCnf,
                                sizeof(TAF_PS_SET_SEC_PDP_CONTEXT_INFO_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndGetSecPdpCtxInfoCnf
 功能描述  :
 输入参数  : VOS_VOID                           *pData
             VOS_UINT32                          ulLength
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_SndGetSecPdpCtxInfoCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF,
                                pData,
                                ulLength);
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndSetTftInfoCnf
 功能描述  :
 输入参数  : TAF_CTRL_STRU                    *pstCtrl
             VOS_UINT32                          ulErrCode
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_APS_SndSetTftInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    TAF_PS_SET_TFT_INFO_CNF_STRU        stSetTftInfoCnf;

    stSetTftInfoCnf.stCtrl      = *pstCtrl;
    stSetTftInfoCnf.enCause = ulErrCode;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_TFT_INFO_CNF,
                                &stSetTftInfoCnf,
                                sizeof(TAF_PS_SET_TFT_INFO_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndGetTftInfoCnf
 功能描述  :
 输入参数  : VOS_VOID                           *pData
             VOS_UINT32                          ulLength
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_SndGetTftInfoCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_TFT_INFO_CNF,
                                pData,
                                ulLength);
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndSetUmtsQosInfoCnf
 功能描述  :
 输入参数  : TAF_CTRL_STRU                    *pstCtrl
             VOS_UINT32                          ulErrCode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_SndSetUmtsQosInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_SET_UMTS_QOS_INFO_CNF_STRU   stSetUmtsQosInfoCnf;

    stSetUmtsQosInfoCnf.stCtrl  = *pstCtrl;
    stSetUmtsQosInfoCnf.enCause = ulErrCode;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_UMTS_QOS_INFO_CNF,
                                &stSetUmtsQosInfoCnf,
                                sizeof(TAF_PS_SET_UMTS_QOS_INFO_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndGetUmtsQosInfoCnf
 功能描述  :
 输入参数  : VOS_VOID                           *pData
             VOS_UINT32                          ulLength
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_SndGetUmtsQosInfoCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_UMTS_QOS_INFO_CNF,
                                pData,
                                ulLength);
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndSetUmtsQosMinInfoCnf
 功能描述  :
 输入参数  : TAF_CTRL_STRU                    *pstCtrl
             VOS_UINT32                          ulErrCode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_SndSetUmtsQosMinInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_SET_UMTS_QOS_MIN_INFO_CNF_STRU   stSetUmtsQosMinInfoCnf;

    stSetUmtsQosMinInfoCnf.stCtrl       = *pstCtrl;
    stSetUmtsQosMinInfoCnf.enCause  = ulErrCode;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_UMTS_QOS_MIN_INFO_CNF,
                                &stSetUmtsQosMinInfoCnf,
                                sizeof(TAF_PS_SET_UMTS_QOS_MIN_INFO_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndGetUmtsQosMinInfoCnf
 功能描述  :
 输入参数  : VOS_VOID                           *pData
             VOS_UINT32                          ulLength
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_SndGetUmtsQosMinInfoCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_UMTS_QOS_MIN_INFO_CNF,
                                pData,
                                ulLength);
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndGetDynamicUmtsQosInfoCnf
 功能描述  :
 输入参数  : VOS_VOID                           *pData
             VOS_UINT32                          ulLength
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_SndGetDynamicUmtsQosInfoCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_CNF,
                                pData,
                                ulLength);
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndGetPdpIpAddrInfoCnf
 功能描述  :
 输入参数  : VOS_VOID                           *pData
             VOS_UINT32                          ulLength
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_SndGetPdpIpAddrInfoCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_PDP_IP_ADDR_INFO_CNF,
                                pData,
                                ulLength);
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndSetAnsModeInfoCnf
 功能描述  :
 输入参数  : TAF_CTRL_STRU                      *pstCtrl
             VOS_UINT32                          ulErrCode
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_APS_SndSetAnsModeInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    TAF_PS_SET_ANSWER_MODE_INFO_CNF_STRU    stSetAnsModeInfoCnf;

    stSetAnsModeInfoCnf.stCtrl      = *pstCtrl;
    stSetAnsModeInfoCnf.enCause = ulErrCode;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_ANSWER_MODE_INFO_CNF,
                                &stSetAnsModeInfoCnf,
                                sizeof(TAF_PS_SET_ANSWER_MODE_INFO_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndGetAnsModeInfoCnf
 功能描述  :
 输入参数  : TAF_CTRL_STRU                      *pstCtrl
             VOS_UINT32                          ulErrCode
             VOS_UINT32                          ulAnsMode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_SndGetAnsModeInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode,
    VOS_UINT32                          ulAnsMode
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_GET_ANSWER_MODE_INFO_CNF_STRU    stGetAnsModeInfoCnf;

    stGetAnsModeInfoCnf.stCtrl      = *pstCtrl;
    stGetAnsModeInfoCnf.enCause = ulErrCode;
    stGetAnsModeInfoCnf.ulAnsMode   = ulAnsMode;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_ANSWER_MODE_INFO_CNF,
                                &stGetAnsModeInfoCnf,
                                sizeof(TAF_PS_GET_ANSWER_MODE_INFO_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end  */

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndGetDynamicPrimPdpCtxInfoCnf
 功能描述  :
 输入参数  : TAF_CTRL_STRU                      *pstCtrl
             VOS_UINT32                          ulErrCode
             VOS_UINT32                          ulCidNum
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : C00184452
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_SndGetDynamicPrimPdpCtxInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode,
    VOS_UINT32                          ulCidNum
)
{
    VOS_UINT32                                          ulResult;
    TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU   stGetDynamicPdpCtxInfoCnf;

    stGetDynamicPdpCtxInfoCnf.stCtrl        = *pstCtrl;
    stGetDynamicPdpCtxInfoCnf.enCause       = ulErrCode;
    stGetDynamicPdpCtxInfoCnf.ulCidNum      = ulCidNum;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF,
                                &stGetDynamicPdpCtxInfoCnf,
                                sizeof(TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndGetDynamicSecPdpCtxInfoCnf
 功能描述  :
 输入参数  : TAF_CTRL_STRU                      *pstCtrl
             VOS_UINT32                          ulErrCode
             VOS_UINT32                          ulCidNum
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : C00184452
    修改内容   : 新生成函数

 2.日    期   : 2011年12月25日
   作    者   : l00198894
   修改内容   : 修改发送给AT消息ID

*****************************************************************************/
VOS_VOID  TAF_APS_SndGetDynamicSecPdpCtxInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode,
    VOS_UINT32                          ulCidNum
)
{
    TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF_STRU    stGetDynamicPdpCtxInfoCnf;

    stGetDynamicPdpCtxInfoCnf.stCtrl        = *pstCtrl;
    stGetDynamicPdpCtxInfoCnf.enCause       = ulErrCode;
    stGetDynamicPdpCtxInfoCnf.ulCidNum      = ulCidNum;


    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF,
                                &stGetDynamicPdpCtxInfoCnf,
                                sizeof(TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndGetDynamicTftInfoCnf
 功能描述  :
 输入参数  : TAF_CTRL_STRU                      *pstCtrl
             VOS_UINT32                          ulErrCode
             VOS_UINT32                          ulCidNum
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : C00184452
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_SndGetDynamicTftInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode,
    VOS_UINT32                          ulCidNum
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_GET_DYNAMIC_TFT_INFO_CNF_STRU    stGetDynamicTftInfoCnf;

    stGetDynamicTftInfoCnf.stCtrl       = *pstCtrl;
    stGetDynamicTftInfoCnf.enCause      = ulErrCode;
    stGetDynamicTftInfoCnf.ulCidNum     = ulCidNum;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DYNAMIC_TFT_INFO_CNF,
                                &stGetDynamicTftInfoCnf,
                                sizeof(TAF_PS_GET_DYNAMIC_TFT_INFO_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndDsFlowRptInd
 功能描述  :
 输入参数  : TAF_CTRL_STRU                      *pstCtrl
             VOS_UINT32                          ulErrCode
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2011年10月16日
    作    者   : 欧阳飞 00132663
    修改内容   : PS Project: 修改流量上报结构体
  3.日    期   : 2013年4月3日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核

*****************************************************************************/
VOS_VOID  TAF_APS_SndDsFlowRptInd(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode,
    TAF_DSFLOW_REPORT_STRU             *pstDsFlowRptInfo
)
{
    TAF_PS_REPORT_DSFLOW_IND_STRU       stReportDsFlowInd;
    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    VOS_UINT32                              ulChkCurcRptFlg;
    VOS_UINT32                              ulChkUnsolicitedRptFlg;
    TAF_SDC_CURC_RPT_CTRL_STRU             *pstCurcRptCtrl          = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU      *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;

    pstCurcRptCtrl              = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl       = TAF_SDC_GetUnsolicitedRptCtrl();
    ulChkCurcRptFlg             = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                    TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                    TAF_SDC_RPT_CMD_DSFLOWRPT);

    ulChkUnsolicitedRptFlg      = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                                    TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                                    TAF_SDC_RPT_CMD_DSFLOWRPT);

    /* 判断主动上报是否打开 */
    if ( (VOS_FALSE == ulChkUnsolicitedRptFlg)
      || (VOS_FALSE == ulChkCurcRptFlg) )
    {
        return;
    }
    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

    stReportDsFlowInd.stCtrl            = *pstCtrl;
    stReportDsFlowInd.enCause           = ulErrCode;
    stReportDsFlowInd.stDsFlowRptInfo   = *pstDsFlowRptInfo;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_REPORT_DSFLOW_IND,
                                &stReportDsFlowInd,
                                sizeof(TAF_PS_REPORT_DSFLOW_IND_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndClearDsFlowCnf
 功能描述  :
 输入参数  : TAF_CTRL_STRU                      *pstCtrl
             VOS_UINT32                          ulErrCode
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_APS_SndClearDsFlowCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    TAF_PS_CLEAR_DSFLOW_CNF_STRU        stClearDsFlowCnf;

    stClearDsFlowCnf.stCtrl         = *pstCtrl;
    stClearDsFlowCnf.enCause        = ulErrCode;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CLEAR_DSFLOW_CNF,
                               &stClearDsFlowCnf,
                               sizeof(TAF_PS_CLEAR_DSFLOW_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndConfigDsFlowRptCnf
 功能描述  :
 输入参数  : TAF_CTRL_STRU                      *pstCtrl
             VOS_UINT32                          ulErrCode
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_APS_SndConfigDsFlowRptCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    TAF_PS_CONFIG_DSFLOW_RPT_CNF_STRU   stClearDsFlowCnf;

    stClearDsFlowCnf.stCtrl         = *pstCtrl;
    stClearDsFlowCnf.enCause        = ulErrCode;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CONFIG_DSFLOW_RPT_CNF,
                               &stClearDsFlowCnf,
                               sizeof(TAF_PS_CONFIG_DSFLOW_RPT_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndSetAuthDataInfoCnf
 功能描述  :
 输入参数  : TAF_CTRL_STRU                      *pstCtrl
             VOS_UINT32                          ulErrCode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月19日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_SndSetAuthDataInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    VOS_UINT32                                 ulResult;
    TAF_PS_SET_AUTHDATA_INFO_CNF_STRU          stSetAuthDataInfoCnf;

    stSetAuthDataInfoCnf.stCtrl         = *pstCtrl;
    stSetAuthDataInfoCnf.enCause        = ulErrCode;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_AUTHDATA_INFO_CNF,
                                &stSetAuthDataInfoCnf,
                                sizeof(TAF_PS_SET_AUTHDATA_INFO_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndGetAuthDataInfoCnf
 功能描述  :
 输入参数  : VOS_VOID                           *pData
             VOS_UINT32                          ulLength
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_SndGetAuthDataInfoCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_AUTHDATA_INFO_CNF,
                                pData,
                                ulLength);
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndSetPdpDnsInfoCnf
 功能描述  :
 输入参数  : TAF_CTRL_STRU                      *pstCtrl
             VOS_UINT32                          ulErrCode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月19日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_SndSetPdpDnsInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_SET_PDP_DNS_INFO_CNF_STRU        stSetPdpDnsInfoCnf;

    stSetPdpDnsInfoCnf.stCtrl           = *pstCtrl;
    stSetPdpDnsInfoCnf.enCause          = ulErrCode;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_PDP_DNS_INFO_CNF,
                                &stSetPdpDnsInfoCnf,
                                sizeof(TAF_PS_SET_PDP_DNS_INFO_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndGetPdpDnsInfoCnf
 功能描述  :
 输入参数  : VOS_VOID                           *pData
             VOS_UINT32                          ulLength
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_SndGetPdpDnsInfoCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_PDP_DNS_INFO_CNF,
                                pData,
                                ulLength);
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndGetGprsActiveTypeCnf
 功能描述  :
 输入参数  : VOS_VOID                           *pData
             VOS_UINT32                          ulLength
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_SndGetGprsActiveTypeCnf(
    TAF_CTRL_STRU                       *pstCtrl,
    VOS_UINT32                          ulErrCode,
    TAF_CID_GPRS_ACTIVE_TYPE_STRU      *pstCidGprsActiveType
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_GET_D_GPRS_ACTIVE_TYPE_CNF_STRU  stGetGprsActiveTypeCnf;

    stGetGprsActiveTypeCnf.stCtrl               = *pstCtrl;
    stGetGprsActiveTypeCnf.enCause              = ulErrCode;
    stGetGprsActiveTypeCnf.stCidGprsActiveType  = *pstCidGprsActiveType;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_D_GPRS_ACTIVE_TYPE_CNF,
                               &stGetGprsActiveTypeCnf,
                               sizeof(TAF_PS_GET_D_GPRS_ACTIVE_TYPE_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndPppDialOrigCnf
 功能描述  :
 输入参数  : TAF_CTRL_STRU                      *pstCtrl
            TAF_PS_CAUSE_ENUM_UINT32            enCause
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2011年12月22日
    作    者   : A00165503
    修改内容   : PS Project: 修改错误码类型

  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_VOID TAF_APS_SndPppDialOrigCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    TAF_PS_PPP_DIAL_ORIG_CNF_STRU       stPppDialOrigCnf;

    PS_MEM_SET(&stPppDialOrigCnf, 0x00, sizeof(TAF_PS_PPP_DIAL_ORIG_CNF_STRU));

    /* 填写事件内容 */
    stPppDialOrigCnf.stCtrl             = *pstCtrl;
    stPppDialOrigCnf.enCause            = enCause;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    /* 发送事件 */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_PPP_DIAL_ORIG_CNF,
                               &stPppDialOrigCnf,
                               sizeof(TAF_PS_PPP_DIAL_ORIG_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

#if (FEATURE_ON == FEATURE_PTM)
    /* 记录PS拨号异常log */
    TAF_APS_PsCallFailErrRecord(enCause);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndGetDsFlowInfoCnf
 功能描述  :
 输入参数  : TAF_CTRL_STRU                      *pstCtrl
             VOS_UINT32                          ulErrCode
             TAF_DSFLOW_QUERY_INFO_STRU         *pstDsFlowQueryInfo
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月20日
    作    者   : C00184452
    修改内容   : 新生成函数

  2.日    期   : 2011年10月16日
    作    者   : 欧阳飞 00132663
    修改内容   : PS Project: 修改流量上报结构体

*****************************************************************************/
/* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
VOS_VOID  TAF_APS_SndGetDsFlowInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode,
    TAF_DSFLOW_QUERY_INFO_STRU         *pstDsFlowQryInfo
)
/* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
{
    TAF_PS_GET_DSFLOW_INFO_CNF_STRU    stGetDsFlowInfoCnf;

    stGetDsFlowInfoCnf.stCtrl       = *pstCtrl;
    stGetDsFlowInfoCnf.enCause      =  ulErrCode;
    stGetDsFlowInfoCnf.stQueryInfo  = *pstDsFlowQryInfo;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DSFLOW_INFO_CNF,
                                &stGetDsFlowInfoCnf,
                                sizeof(TAF_PS_GET_DSFLOW_INFO_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndSetCgeqosCnf
 功能描述  :
 输入参数  : TAF_CTRL_STRU                      *pstCtrl
             VOS_UINT32                          ulErrCode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : C00184452
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_APS_SndSetCgeqosCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    TAF_PS_SET_EPS_QOS_INFO_CNF_STRU            stSetCgeqosCnf;

    stSetCgeqosCnf.stCtrl   = *pstCtrl;
    stSetCgeqosCnf.enCause  = ulErrCode;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_EPS_QOS_INFO_CNF,
                                &stSetCgeqosCnf,
                                sizeof(TAF_PS_SET_EPS_QOS_INFO_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndGetCgeqosCnf
 功能描述  :
 输入参数  : VOS_VOID                           *pData
             VOS_UINT32                          ulLength
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : C00184452
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_SndGetCgeqosCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_EPS_QOS_INFO_CNF,
                               pData,
                               ulLength);
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndGetCgeqosrdpCnf
 功能描述  :
 输入参数  : VOS_VOID                           *pData
             VOS_UINT32                          ulLength
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月16日
    作    者   : C00184452
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_APS_SndGetCgeqosrdpCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF_STRU    stGetCgeqosCnf;

    (VOS_VOID)VOS_MemSet(&stGetCgeqosCnf, 0, sizeof(TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF_STRU));

    stGetCgeqosCnf.stCtrl               = *pstCtrl;
    stGetCgeqosCnf.enCause              = ulErrCode;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF,
                                &stGetCgeqosCnf,
                                sizeof(TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndSetDialModeCnf
 功能描述  :
 输入参数  : TAF_CTRL_STRU                      *pstCtrl,
             VOS_UINT32                          ulErrCode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月02日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_SndSetDialModeCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          enCause
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_CDATA_DIAL_MODE_CNF_STRU     stSetDialModeCnf;

    PS_MEM_SET(&stSetDialModeCnf, 0x00, sizeof(TAF_PS_CDATA_DIAL_MODE_CNF_STRU));

    stSetDialModeCnf.stCtrl     = *pstCtrl;
    stSetDialModeCnf.enCause    = enCause;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_CDMA_DIAL_MODE_CNF,
                                &stSetDialModeCnf,
                                sizeof(TAF_PS_CDATA_DIAL_MODE_CNF_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndGetCgmtuValueCnf
 功能描述  : TAF Aps Snd CGMTU Qry Cnf Back
 输入参数  : TAF_CTRL_STRU                      *pstCtrl
             VOS_UINT32                          ulMtuValue
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月29日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_SndGetCgmtuValueCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulMtuValue
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_GET_CGMTU_VALUE_CNF_STRU     stCgmtuValueCnf;

    PS_MEM_SET(&stCgmtuValueCnf, 0x00, sizeof(TAF_PS_GET_CGMTU_VALUE_CNF_STRU));

    stCgmtuValueCnf.stCtrl     = *pstCtrl;
    stCgmtuValueCnf.ulMtuValue = ulMtuValue;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_CGMTU_VALUE_CNF,
                                &stCgmtuValueCnf,
                                sizeof(TAF_PS_GET_CGMTU_VALUE_CNF_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndCgmtuValueChangeInd
 功能描述  : TAF APS Snd Cgmtu Value Change Ind Msg to AT
 输入参数  : VOS_UINT32                          ulMtuValue
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月29日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_SndCgmtuValueChangeInd(
    VOS_UINT32                          ulMtuValue
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_CGMTU_VALUE_CHG_IND_STRU     stCgmtuValueChgInd;

    PS_MEM_SET(&stCgmtuValueChgInd, 0x00, sizeof(TAF_PS_CGMTU_VALUE_CHG_IND_STRU));

    stCgmtuValueChgInd.stCtrl.ulModuleId   = WUEPS_PID_AT;
    stCgmtuValueChgInd.stCtrl.usClientId   = MN_CLIENT_ID_BROADCAST;
    stCgmtuValueChgInd.stCtrl.ucOpId       = 0;
    stCgmtuValueChgInd.ulMtuValue          = ulMtuValue;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CGMTU_VALUE_CHG_IND,
                                &stCgmtuValueChgInd,
                                sizeof(TAF_PS_CGMTU_VALUE_CHG_IND_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndSetApDsFlowRptCfgCnf
 功能描述  : 发送ID_EVT_TAF_PS_SET_APDSFLOW_RPT_CFG_CNF事件
 输入参数  : pstCtrl --- 控制头
             enCause --- 错误码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月2日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_APS_SndSetApDsFlowRptCfgCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    TAF_PS_SET_APDSFLOW_RPT_CFG_CNF_STRU    stSetRptCfgCnf;

    stSetRptCfgCnf.stCtrl  = *pstCtrl;
    stSetRptCfgCnf.enCause = enCause;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_APDSFLOW_RPT_CFG_CNF,
                                &stSetRptCfgCnf,
                                sizeof(TAF_PS_SET_APDSFLOW_RPT_CFG_CNF_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndGetApDsFlowRptCfgCnf
 功能描述  : 发送ID_EVT_TAF_PS_GET_APDSFLOW_RPT_CFG_CNF事件
 输入参数  : pstCtrl   --- 控制头
             enCause   --- 错误码
             pstRptCfg --- 配置信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月2日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_APS_SndGetApDsFlowRptCfgCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_PS_CAUSE_ENUM_UINT32            enCause,
    TAF_APDSFLOW_RPT_CFG_STRU          *pstRptCfg
)
{
    TAF_PS_GET_APDSFLOW_RPT_CFG_CNF_STRU    stGetRptCfgCnf;

    stGetRptCfgCnf.stCtrl   = *pstCtrl;
    stGetRptCfgCnf.enCause  = enCause;
    stGetRptCfgCnf.stRptCfg = *pstRptCfg;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_APDSFLOW_RPT_CFG_CNF,
                                &stGetRptCfgCnf,
                                sizeof(TAF_PS_GET_APDSFLOW_RPT_CFG_CNF_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndApDsFlowRptInd
 功能描述  : 发送ID_EVT_TAF_PS_APDSFLOW_REPORT_IND事件
 输入参数  : pstCtrl    --- 控制头
             enCause    --- 错误码
             pstRptInfo --- 流量信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月2日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_APS_SndApDsFlowRptInd(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_APDSFLOW_REPORT_STRU           *pstRptInfo
)
{
    TAF_PS_APDSFLOW_REPORT_IND_STRU     stRptInd;

    stRptInd.stCtrl            = *pstCtrl;
    stRptInd.stApDsFlowRptInfo = *pstRptInfo;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_APDSFLOW_REPORT_IND,
                                &stRptInd,
                                sizeof(TAF_PS_APDSFLOW_REPORT_IND_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndSetDsFlowNvWriteCfgCnf
 功能描述  : 发送ID_EVT_TAF_PS_SET_DSFLOW_NV_WRITE_CFG_CNF事件
 输入参数  : pstCtrl --- 控制头
             enCause --- 错误码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月12日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_APS_SndSetDsFlowNvWriteCfgCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    TAF_PS_SET_DSFLOW_NV_WRITE_CFG_CNF_STRU stSetNvWriteCfgCnf;

    stSetNvWriteCfgCnf.stCtrl  = *pstCtrl;
    stSetNvWriteCfgCnf.enCause = enCause;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_DSFLOW_NV_WRITE_CFG_CNF,
                                &stSetNvWriteCfgCnf,
                                sizeof(TAF_PS_SET_DSFLOW_NV_WRITE_CFG_CNF_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndGetDsFlowNvWriteCfgCnf
 功能描述  : 发送ID_EVT_TAF_PS_GET_DSFLOW_NV_WRITE_CFG_CNF事件
 输入参数  : pstCtrl       --- 控制头
             enCause       --- 错误码
             pstNvWriteCfg --- 配置信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月12日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_APS_SndGetDsFlowNvWriteCfgCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_PS_CAUSE_ENUM_UINT32            enCause,
    TAF_DSFLOW_NV_WRITE_CFG_STRU       *pstNvWriteCfg
)
{
    TAF_PS_GET_DSFLOW_NV_WRITE_CFG_CNF_STRU stGetNvWriteCfgCnf;

    stGetNvWriteCfgCnf.stCtrl      = *pstCtrl;
    stGetNvWriteCfgCnf.enCause     = enCause;
    stGetNvWriteCfgCnf.stNvWriteCfg = *pstNvWriteCfg;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DSFLOW_NV_WRITE_CFG_CNF,
                                &stGetNvWriteCfgCnf,
                                sizeof(TAF_PS_GET_DSFLOW_NV_WRITE_CFG_CNF_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndStkPsCallEvent
 功能描述  : 发送当前PS呼叫状态给STK
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月20日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndStkPsCallEvent(VOS_VOID)
{
    NAS_STK_PS_CALLINFO_EVENT_STRU     *pstMsg          = VOS_NULL_PTR;
    TAF_APS_PDP_ENTITY_FSM_CTX_STRU    *pstPdpEntFsmCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstMsg = (NAS_STK_PS_CALLINFO_EVENT_STRU *)TAF_APS_ALLOC_MSG_WITH_HDR(
                            sizeof(NAS_STK_PS_CALLINFO_EVENT_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndStkPsCallEvent: alloc message fail!");
        return;
    }

    /* 清空消息内容 */
    PS_MEM_SET(TAF_APS_GET_MSG_ENTITY(pstMsg), 0x00, TAF_APS_GET_MSG_LENGTH(pstMsg));

    /* 填写消息头 */
    TAF_APS_CFG_STK_MSG_HDR(pstMsg, ID_NAS_STK_PS_CALLINFO_EVENT);

    /* 填写消息内容 */
    pstMsg->bPsCallExist = VOS_FALSE;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        pstPdpEntFsmCtx = TAF_APS_GetApsEntityFsmCtxAddr(ucPdpId);
        if (VOS_TRUE == pstPdpEntFsmCtx->ucCallActiveFlg)
        {
            pstMsg->bPsCallExist = VOS_TRUE;
            break;
        }
    }

    /* 发送消息 */
    TAF_APS_SEND_MSG(pstMsg);
    return;
}

/*****************************************************************************
 函 数 名  : MN_APS_BuildDefinedCtxList
 功能描述  :
 输入参数  : aucCidList[]
             *pulCidNum
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年1月9日
    作    者   : l00198894
    修改内容   : PS Project, 融合CID最大值

*****************************************************************************/
VOS_UINT32 MN_APS_ValidateCidList(
    VOS_UINT8                       aucCidList[],
    VOS_UINT32                     *pulCidNum
)
{
    VOS_UINT32                          i;

    /* 初始化 */
    *pulCidNum  = 0;

    /* 检查CID列表是否全0 */
    for ( i = 1; i <= TAF_MAX_CID; i++ )
    {
        if ( VOS_TRUE == aucCidList[i] )
        {
            (*pulCidNum)++;
        }
    }

    /* CID数量为0, 则CID列表无效 */
    if ( 0 == (*pulCidNum) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : MN_APS_BuildCidProcList
 功能描述  : 生成需要处理的CID列表, 用于QOS, AUTH等信息, 不用于PDP上下文
 输入参数  : aucCidList[]               - CID列表, 包含L模的CID
 输出参数  : aucCidProcList[]           - 需要GU模处理的CID列表
             pulCidNum                  - CID数量
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月23日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年1月9日
    作    者   : l00198894
    修改内容   : PS Project, 融合CID最大值

*****************************************************************************/
VOS_UINT32 MN_APS_BuildCidProcList(
    VOS_UINT8                           aucCidList[],
    VOS_UINT8                           aucCidProcList[]
)
{
    VOS_UINT32                          ulCidNum;

    /* 初始化 */
    ulCidNum = 0;

    /* 检查CID列表是否有效 */
    if ( VOS_FALSE == MN_APS_ValidateCidList(aucCidList,
                                             &ulCidNum) )
    {
        PS_MEM_SET(aucCidProcList, 0x01, (TAF_MAX_CID + 1));
    }
    else
    {
        PS_MEM_CPY(aucCidProcList, aucCidList, (TAF_MAX_CID + 1));
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : MN_APS_RandomBytes
 功能描述  : 生成随机数
 输入参数  : VOS_UINT8                           *pucBuf
             VOS_UINT16                           usLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月19日
    作    者   : A00165503
    修改内容   : AT Project: 移植AT_RandomBytes函数, 修改函数名称

*****************************************************************************/
VOS_VOID MN_APS_RandomBytes(
    VOS_UINT8                           *pucBuf,
    VOS_UINT16                           usLen
)
{
    VOS_UINT16 usLoop;

    for (usLoop = 0; usLoop < usLen; ++usLoop)
    {
        pucBuf[usLoop] = (TAF_UINT8)VOS_Rand(0xff);
    }

    return;
}

/*****************************************************************************
 函 数 名  : MN_APS_CtrlGetAuthType
 功能描述  : 根据用户
 输入参数  : PPP_AUTH_TYPE_ENUM_UINT8            enAuthType
 输出参数  : 无
 返 回 值  : PPP_AUTH_TYPE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : A00165503
    修改内容   : AT Project: 移植AT_CtrlGetAuthType函数, 修改函数名称

*****************************************************************************/
PPP_AUTH_TYPE_ENUM_UINT8 MN_APS_CtrlGetAuthType(
    PPP_AUTH_TYPE_ENUM_UINT8            enAuthType
)
{
    /* 不支持MS_CHAPV2, 默认使用CHAP */
    if ( PPP_MS_CHAPV2_AUTH_TYPE == enAuthType )
    {
        return PPP_CHAP_AUTH_TYPE;
    }
    else
    {
        return enAuthType;
    }
}

/*lint -e438 -e830*/
/*****************************************************************************
 函 数 名  : MN_APS_CtrlMakePCOPapAuthInfo
 功能描述  :
 输入参数  : PPP_REQ_CONFIG_INFO_STRU           *pstPppReqCfgInfo
             VOS_UINT8                          *pucUserName
             VOS_UINT16                          usUserNameLen
             VOS_UINT8                          *pucPassWord
             VOS_UINT16                          usPassWordLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : A00165503
    修改内容   : AT Project: 移植AT_CtrlMakePCOPapAuthInfo函数, 修改函数名称

*****************************************************************************/
VOS_UINT32 MN_APS_CtrlMakePCOPapAuthInfo(
    PPP_REQ_CONFIG_INFO_STRU           *pstPppReqCfgInfo,
    VOS_UINT8                          *pucUserName,
    VOS_UINT16                          usUserNameLen,
    VOS_UINT8                          *pucPassWord,
    VOS_UINT16                          usPassWordLen
)
{
    TAF_PPP_FRAME_HEAD_STRU            *pstPppHead;
    VOS_UINT8                          *pucPapFrame;
    VOS_UINT8                          *pucBuff;
    VOS_UINT16                          usPapLen;

    pstPppReqCfgInfo->stAuth.AuthContent.PapContent.usPapReqLen = 0;
    pstPppReqCfgInfo->stAuth.AuthContent.PapContent.pPapReq     = VOS_NULL_PTR;

    /* 计算PAP帧总长度*/
    usPapLen = sizeof(TAF_PPP_FRAME_HEAD_STRU) + sizeof(VOS_UINT8) + usUserNameLen
                        + sizeof(VOS_UINT8) + usPassWordLen;

    /* 申请内存*/
    pucPapFrame = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_TAF, usPapLen);
    if (VOS_NULL_PTR == pucPapFrame)
    {
        MN_ERR_LOG("MN_APS_CtrlMakePCOPapAuthInfo:  ERROR : PS_MEM_ALLOC Error!");
        return VOS_ERR;
    }

    /* 填写头部*/
    pstPppHead              = (TAF_PPP_FRAME_HEAD_STRU*)pucPapFrame;
    pstPppHead->ucCode      = TAF_PPP_CODE_REQ;
    pstPppHead->ucId        = TAF_PPP_DEF_ID;
    pstPppHead->usLength    = TAF_HTONS(usPapLen);

    pucBuff  = (VOS_UINT8*)(pstPppHead + 1);
/*lint -e961*/
    /* 填写用户名长度 + 用户名*/
    *(pucBuff ++) = (VOS_UINT8)usUserNameLen;
    if (0 != usUserNameLen)
    {
        PS_MEM_CPY(pucBuff, pucUserName, usUserNameLen);
        pucBuff += usUserNameLen;
    }

    /* 填写密码长度 + 用户名*/
    *(pucBuff ++) = (VOS_UINT8)usPassWordLen;
    if (0 != usPassWordLen)
    {
        PS_MEM_CPY(pucBuff, pucPassWord, usPassWordLen);
        pucBuff += usPassWordLen;
    }
/*lint +e961*/

    pstPppReqCfgInfo->stAuth.AuthContent.PapContent.usPapReqLen = usPapLen;
    pstPppReqCfgInfo->stAuth.AuthContent.PapContent.pPapReq     = pucPapFrame;

    return VOS_OK;
}
/*lint +e438 +e830*/


/*****************************************************************************
 函 数 名  : MN_APS_CtrlMakePCOChapAuthInfo
 功能描述  :
 输入参数  : PPP_REQ_CONFIG_INFO_STRU            *pstPppReqCfgInfo
             VOS_UINT8                           *pucUserName
             VOS_UINT16                           usUserNameLen
             VOS_UINT8                           *pucPassWord
             VOS_UINT16                           usPassWordLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : A00165503
    修改内容   : AT Project: 移植AT_CtrlMakePCOChapAuthInfo函数, 修改函数名称

*****************************************************************************/
VOS_UINT32 MN_APS_CtrlMakePCOChapAuthInfo(
    PPP_REQ_CONFIG_INFO_STRU           *pstPppReqCfgInfo,
    VOS_UINT8                          *pucUserName,
    VOS_UINT16                          usUserNameLen,
    VOS_UINT8                          *pucPassWord,
    VOS_UINT16                          usPassWordLen
)
{
    VOS_UINT16                          usChallengeLength   = 0;
    VOS_UINT16                          usResponseLength    = 0;
    VOS_UINT8                           ucId                = TAF_PPP_DEF_ID;
    VOS_UINT8                           aucChapSrvName[]    = {'h','u','a','w','e','i','.','c','o','m'};  /* CHAP Challenge中的用户名,10 byte,无需'\0'结尾*/
    VOS_UINT8                          *pucChallengeFrame  = VOS_NULL_PTR;
    VOS_UINT8                          *pucChallenge       = VOS_NULL_PTR;
    VOS_UINT8                          *pucResponseFrame   = VOS_NULL_PTR;
    VOS_UINT8                          *pucBuff            = VOS_NULL_PTR;
    TAF_PPP_FRAME_HEAD_STRU            *pstPppHead         = VOS_NULL_PTR;
    TAF_MSG_DIGEST_FIVE_CTX             stCtx;

    pstPppReqCfgInfo->stAuth.AuthContent.ChapContent.pChapChallenge = VOS_NULL_PTR;
    pstPppReqCfgInfo->stAuth.AuthContent.ChapContent.pChapResponse  = VOS_NULL_PTR;
    pstPppReqCfgInfo->stAuth.AuthContent.ChapContent.usChapChallengeLen = 0;
    pstPppReqCfgInfo->stAuth.AuthContent.ChapContent.usChapResponseLen  = 0;

    /* 计算challenge总长度*/
    usChallengeLength = sizeof(TAF_PPP_FRAME_HEAD_STRU) + sizeof(VOS_UINT8)
                        + TAF_AP_PPP_CHAP_CHALLENGE_LEN + sizeof(aucChapSrvName);

    /* 计算response总长度*/
    usResponseLength = sizeof(TAF_PPP_FRAME_HEAD_STRU) + sizeof(VOS_UINT8)
                        + TAF_AP_PPP_CHAP_RESPONSE_LEN + usUserNameLen;

    /* 申请challenge内存*/
    pucChallengeFrame = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_TAF, usChallengeLength);
    if (VOS_NULL_PTR == pucChallengeFrame)
    {
        MN_ERR_LOG("MN_APS_CtrlMakePCOChapAuthInfo: PS_MEM_ALLOC Error!");
        return VOS_ERR;
    }

    /* 申请response内存*/
    pucResponseFrame = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_TAF, usResponseLength);
    if (VOS_NULL_PTR == pucResponseFrame)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pucChallengeFrame);
        MN_ERR_LOG("MN_APS_CtrlMakePCOChapAuthInfo: PS_MEM_ALLOC Error!");
        return VOS_ERR;
    }

    PS_MEM_SET(pucChallengeFrame, 0, usChallengeLength);
    PS_MEM_SET(pucResponseFrame, 0, usResponseLength);

   /* 生成challenge*/
    pstPppHead              = (TAF_PPP_FRAME_HEAD_STRU *)pucChallengeFrame;
    pstPppHead->ucCode      = TAF_AP_PPP_CODE_CHALLENGE;
    pstPppHead->ucId        = ucId;
    pstPppHead->usLength    = TAF_HTONS(usChallengeLength);

    pucBuff         = pucChallengeFrame + sizeof(TAF_PPP_FRAME_HEAD_STRU);

/*lint -e961*/
    /*length*/
    *(pucBuff ++)   = TAF_AP_PPP_CHAP_CHALLENGE_LEN;
    pucChallenge    = pucBuff;

    /*random challenge*/
    MN_APS_RandomBytes(pucBuff, TAF_AP_PPP_CHAP_CHALLENGE_LEN);
    pucBuff        += TAF_AP_PPP_CHAP_CHALLENGE_LEN;

    /*name*/
    PS_MEM_CPY(pucBuff, aucChapSrvName, sizeof(aucChapSrvName));

    /* 生成challenge*/
    pstPppHead              = (TAF_PPP_FRAME_HEAD_STRU *)pucResponseFrame;
    pstPppHead->ucCode      = TAF_AP_PPP_CODE_RESPONSE;
    pstPppHead->ucId        = ucId;
    pstPppHead->usLength    = TAF_HTONS(usResponseLength);

    pucBuff         = pucResponseFrame + sizeof(TAF_PPP_FRAME_HEAD_STRU);

    /*length*/
    *(pucBuff ++)   = TAF_AP_PPP_CHAP_RESPONSE_LEN;
/*lint +e961*/
    TAF_InitMsgDigestFiveCtxt(&stCtx);
    TAF_UpdateMsgDigestFiveCtxt(&stCtx, &ucId, 1);
    TAF_UpdateMsgDigestFiveCtxt(&stCtx, pucPassWord, usPassWordLen);
    TAF_UpdateMsgDigestFiveCtxt(&stCtx, pucChallenge, TAF_AP_PPP_CHAP_CHALLENGE_LEN);

    /*response*/
    TAF_EndMsgDigestFive(pucBuff, &stCtx);

    pucBuff += TAF_AP_PPP_CHAP_RESPONSE_LEN;
    if (0 != usUserNameLen)
    {

        /*name*/
        PS_MEM_CPY(pucBuff, pucUserName, usUserNameLen);
    }

    pstPppReqCfgInfo->stAuth.AuthContent.ChapContent.pChapChallenge     = pucChallengeFrame;
    pstPppReqCfgInfo->stAuth.AuthContent.ChapContent.usChapChallengeLen = usChallengeLength;
    pstPppReqCfgInfo->stAuth.AuthContent.ChapContent.pChapResponse      = pucResponseFrame;
    pstPppReqCfgInfo->stAuth.AuthContent.ChapContent.usChapResponseLen  = usResponseLength;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : MN_APS_CtrlFreePCOContext
 功能描述  : 释放鉴权信息
 输入参数  : PPP_REQ_CONFIG_INFO_STRU           *pstPppReqCfgInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : A00165503
    修改内容   : AT Project: 移植AT_CtrlFreePCOContext函数, 修改函数名称

*****************************************************************************/
VOS_VOID MN_APS_CtrlFreePCOContext(
    PPP_REQ_CONFIG_INFO_STRU           *pstPppReqCfgInfo
)
{
    if ( PPP_PAP_AUTH_TYPE == pstPppReqCfgInfo->stAuth.ucAuthType )
    {
        if ( VOS_NULL_PTR != pstPppReqCfgInfo->stAuth.AuthContent.PapContent.pPapReq )
        {
            PS_MEM_FREE(WUEPS_PID_TAF, pstPppReqCfgInfo->stAuth.AuthContent.PapContent.pPapReq );
        }
    }

    if ( PPP_CHAP_AUTH_TYPE == pstPppReqCfgInfo->stAuth.ucAuthType )
    {
        if ( VOS_NULL_PTR != pstPppReqCfgInfo->stAuth.AuthContent.ChapContent.pChapChallenge )
        {
            PS_MEM_FREE(WUEPS_PID_TAF, pstPppReqCfgInfo->stAuth.AuthContent.ChapContent.pChapChallenge);
        }

        if ( VOS_NULL_PTR != pstPppReqCfgInfo->stAuth.AuthContent.ChapContent.pChapResponse )
        {
            PS_MEM_FREE(WUEPS_PID_TAF, pstPppReqCfgInfo->stAuth.AuthContent.ChapContent.pChapResponse);
        }
    }

    if ( VOS_NULL_PTR != pstPppReqCfgInfo->stIPCP.pIpcp )
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstPppReqCfgInfo->stIPCP.pIpcp);
    }

    return;
}

/*****************************************************************************
 函 数 名  : MN_APS_RcvCallOrigReq
 功能描述  : 处理ID_MN_PS_CALL_ORIG_REQ消息
 输入参数  : ucPdpId      --- APS实体索引
             pstDialParam --- 拨号参数
 输出参数  : 无
 返 回 值  : TAF_PS_CAUSE_ENUM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年5月30日
    作    者   : A00165503
    修改内容   : DTS2012052901004: 拨号请求中无用户名, 不需要填写鉴权信息

  3.日    期   : 2014年5月16日
    作    者   : A00165503
    修改内容   : DTS2014050703206: 调整呼叫发起流程实现, 与CID上下文参数解耦

  4.日    期   : 2015年12月21日
    作    者   : w00316404
    修改内容   : DTS2015113004973: GU下携带P-CSCF标志位，直接返回拒绝
*****************************************************************************/
TAF_PS_CAUSE_ENUM_UINT32 MN_APS_RcvCallOrigReq(
    VOS_UINT8                           ucPdpId,
    TAF_PS_DIAL_PARA_STRU              *pstDialParam
)
{
    PPP_REQ_CONFIG_INFO_STRU            stPppConfigInfo;
    TAF_PDP_ADDR_STRU                   stPdpAddr;
    TAF_PDP_APN_STRU                    stApn;
    VOS_UINT32                          ulAuthMakeRslt;
    TAF_PS_CAUSE_ENUM_UINT32            enRet;

    ulAuthMakeRslt = VOS_OK;
    enRet          = TAF_PS_CAUSE_SUCCESS;

    PS_MEM_SET(&stPppConfigInfo, 0x00, sizeof(PPP_REQ_CONFIG_INFO_STRU));
    PS_MEM_SET(&stPdpAddr, 0x00, sizeof(TAF_PDP_ADDR_STRU));
    PS_MEM_SET(&stApn, 0x00, sizeof(TAF_PDP_APN_STRU));

#if (FEATURE_IMS == FEATURE_ON)
    if ( VOS_TRUE == pstDialParam->bitOpPcscfDiscovery )
    {
        return TAF_PS_CAUSE_UNSUPPORT_PCSCF;
    }
#endif

    stPdpAddr.enPdpType = pstDialParam->enPdpType;

    if ( (VOS_TRUE == pstDialParam->bitOpIpAddr)
      && (TAF_PDP_IPV4 == pstDialParam->stPdpAddr.enPdpType) )
    {
        PS_MEM_CPY(stPdpAddr.aucIpv4Addr, pstDialParam->stPdpAddr.aucIpv4Addr, TAF_IPV4_ADDR_LEN);
    }

    if (VOS_TRUE == pstDialParam->bitOpApn)
    {
        stApn.ucLength = (VOS_UINT8)VOS_StrLen((VOS_CHAR *)pstDialParam->aucApn);
        PS_MEM_CPY(stApn.aucValue, pstDialParam->aucApn, TAF_MAX_APN_LEN);

/* Added by zhuli for K3V3VSIM项目, 2014-10-16, begin */
        PIH_GetVsimAPN(TAF_MAX_APN_LEN, stApn.aucValue, &stApn.ucLength);
/* Added by zhuli for K3V3VSIM项目, 2014-10-16, end */
    }

    /* 获取鉴权类型 */
    if ( (VOS_FALSE == pstDialParam->bitOpAuthType)
      || (VOS_FALSE == pstDialParam->bitOpUserName) )
    {
        stPppConfigInfo.stAuth.ucAuthType = PPP_NO_AUTH_TYPE;
    }
    else
    {
        stPppConfigInfo.stAuth.ucAuthType = MN_APS_CtrlGetAuthType(pstDialParam->enAuthType);
    }

    /* 根据鉴权类型生成鉴权信息 */
    if (PPP_PAP_AUTH_TYPE == stPppConfigInfo.stAuth.ucAuthType)
    {
        ulAuthMakeRslt = MN_APS_CtrlMakePCOPapAuthInfo(
                                &stPppConfigInfo,
                                pstDialParam->aucUserName,
                                (VOS_UINT16)VOS_StrLen((VOS_CHAR *)(pstDialParam->aucUserName)),
                                pstDialParam->aucPassWord,
                                (VOS_UINT16)VOS_StrLen((VOS_CHAR *)(pstDialParam->aucPassWord)));
    }
    else if (PPP_CHAP_AUTH_TYPE == stPppConfigInfo.stAuth.ucAuthType)
    {
        ulAuthMakeRslt = MN_APS_CtrlMakePCOChapAuthInfo(
                                &stPppConfigInfo,
                                pstDialParam->aucUserName,
                                (VOS_UINT16)VOS_StrLen((VOS_CHAR *)(pstDialParam->aucUserName)),
                                pstDialParam->aucPassWord,
                                (VOS_UINT16)VOS_StrLen((VOS_CHAR *)(pstDialParam->aucPassWord)));
    }
    else
    {
        ulAuthMakeRslt = VOS_OK;
    }

    if (VOS_OK != ulAuthMakeRslt)
    {
        stPppConfigInfo.stAuth.ucAuthType = PPP_NO_AUTH_TYPE;
    }

    enRet = TAF_APS_PsCallForDial(ucPdpId,
                                  &stPdpAddr,
                                  &stApn,
                                  &stPppConfigInfo);

    /* 释放生成的鉴权信息 */
    MN_APS_CtrlFreePCOContext(&stPppConfigInfo);

    return enRet;
}

/*****************************************************************************
 函 数 名  : MN_APS_RcvCallModifyReq
 功能描述  : 处理ID_MN_PS_CALL_MODIFY_REQ消息
 输入参数  : ucPdpId                    - APS实体索引
             pstCallOrigReq             - 修改PDP参数
 输出参数  : 无
 返 回 值  : VOS_UINT32                 - 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2011年12月23日
    作    者   : A00165503
    修改内容   : PS Project: 修改PDP修改处理逻辑

*****************************************************************************/
VOS_UINT32 MN_APS_RcvCallModifyReq(
    VOS_UINT8                           ucPdpId,
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq,
    VOS_UINT8                          *pucErrCode
)
{
    /* 初始化 */
    *pucErrCode                         = TAF_ERR_NO_ERROR;

    /* 修改PS CALL参数: QOS等 */
    Aps_PsCallModify(pstCallModifyReq->stCtrl.usClientId,
                     pstCallModifyReq->stCtrl.ucOpId,
                     ucPdpId,
                     pucErrCode);
    if (TAF_ERR_NO_ERROR != *pucErrCode)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetPdpStateReq
 功能描述  : 处理ID_TAF_PS_GET_PDP_CONTEXT_STATE_REQ消息
 输入参数  : pMsgData                   - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetPdpCtxStateReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulErrCode;
    VOS_UINT32                          ulPdpStateLen;
    VOS_UINT32                          ulCidNum;
    TAF_PS_GET_PDP_STATE_CNF_STRU       stPdpStateNullCnf;
    TAF_PS_GET_PDP_STATE_CNF_STRU      *pstGetPdpStateCnf;
    TAF_PS_GET_PDP_STATE_REQ_STRU      *pstGetPdpStateReq;

    /* 初始化 */
    ulResult            = VOS_OK;
    ulErrCode           = TAF_PARA_OK;
    ulPdpStateLen       = 0;
    ulCidNum            = 0;
    pstGetPdpStateCnf   = VOS_NULL_PTR;
    pstGetPdpStateReq   = (TAF_PS_GET_PDP_STATE_REQ_STRU*)pMsgData;

    /* 计算事件内容长度 */
    ulPdpStateLen       = sizeof(TAF_PS_GET_PDP_STATE_CNF_STRU)
                                + ((TAF_MAX_CID + 1) * sizeof(TAF_CID_STATE_STRU));

    /* 申请内存 */
    pstGetPdpStateCnf   = (TAF_PS_GET_PDP_STATE_CNF_STRU*)PS_MEM_ALLOC(
                                    WUEPS_PID_TAF,
                                    ulPdpStateLen);

    /* 申请消息失败 */
    if ( VOS_NULL_PTR == pstGetPdpStateCnf )
    {
        MN_ERR_LOG("MN_APS_RcvGetUmtsQosInfoReq:  ERROR : PS_MEM_ALLOC Error!");

        stPdpStateNullCnf.stCtrl    = pstGetPdpStateReq->stCtrl;
        stPdpStateNullCnf.ulCidNum  = 0;
        stPdpStateNullCnf.enCause   = TAF_PARA_OK;

        return TAF_APS_SndGetPdpStateCnf(&stPdpStateNullCnf,
                                        sizeof(TAF_PS_GET_PDP_STATE_CNF_STRU));
    }

    /* 填写事件内容 */
    for ( ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++ )
    {
        PS_MEM_SET(&(pstGetPdpStateCnf->astCidStateInfo[ulCidNum]),
                   0x00, sizeof(TAF_CID_STATE_STRU));

        /* 获取指定CID对应的PDP上下文的状态 */
        Aps_QueState(ucIndex,
                     &(pstGetPdpStateCnf->astCidStateInfo[ulCidNum]),
                     &ulErrCode);

        if ( TAF_PARA_OK == ulErrCode )
        {
            ulCidNum++;
        }
    }

    /* 填写事件控制头 */
    pstGetPdpStateCnf->stCtrl   = pstGetPdpStateReq->stCtrl;
    pstGetPdpStateCnf->ulCidNum = ulCidNum;
    pstGetPdpStateCnf->enCause  = TAF_PS_CAUSE_SUCCESS;

    /* 返回处理结果 */
    ulResult = TAF_APS_SndGetPdpStateCnf(pstGetPdpStateCnf,
                                        ulPdpStateLen);

    /* 释放用于存放PDP上下文状态的内存参数的内存 */
    PS_MEM_FREE(WUEPS_PID_TAF, pstGetPdpStateCnf);

    return ulResult;
}

/*****************************************************************************
 函 数 名  : MN_APS_RcvSetPrimPdpCtxInfoReq
 功能描述  : 处理ID_TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ消息
 输入参数  : pMsgData                   - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年6月15日
    作    者   : m00217266
    修改内容   : 停止暂停PDP激活定时器(AT&T定制，PDP激活限制)

*****************************************************************************/
VOS_VOID MN_APS_RcvSetPrimPdpCtxInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                                  ulErrCode;
    TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU  *pstSetPdpCtxInfoReq;

    /* 初始化 */
    ulErrCode           = TAF_PARA_OK;
    pstSetPdpCtxInfoReq = (TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU*)pMsgData;


    /* PDP激活受限特性打开，暂停激活定时器正在运行 */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_PDP_ACT_LIMIT_PDP_ID))
    {
        TAF_APS_RcvSetPrimPdpCtxInfoReq_PdpActLimit(pstSetPdpCtxInfoReq);
    }


    /* 设置Primary PDP上下文 */
    Aps_DefPsPdpContext(pstSetPdpCtxInfoReq->stCtrl.usClientId,
                        pstSetPdpCtxInfoReq->stCtrl.ucOpId,
                        &(pstSetPdpCtxInfoReq->stPdpContextInfo),
                        &ulErrCode);


    /* 返回处理结果 */
    TAF_APS_SndSetPrimPdpCtxInfoCnf(&(pstSetPdpCtxInfoReq->stCtrl),
                                              ulErrCode);

    return;
}

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetPrimPdpCtxInfoReq
 功能描述  : 处理ID_TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ消息
 输入参数  : pMsgData                   - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年5月26日
    作    者   : A00165503
    修改内容   : DTS2012052404203: +CGDCONT命令增加对<CID 0>的支持
*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetPrimPdpCtxInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT8                                   ucIndex;
    VOS_UINT32                                  ulResult;
    VOS_UINT32                                  ulErrCode;
    VOS_UINT32                                  ulPdpCtxInfoLen;
    VOS_UINT32                                  ulCidNum;
    TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ_STRU  *pstGetPdpCtxInfoReq;
    TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF_STRU  *pstGetPdpCtxInfoCnf;

    /* 初始化 */
    ulResult            = VOS_OK;
    ulErrCode           = TAF_PARA_OK;
    ulPdpCtxInfoLen     = 0;
    ulCidNum            = 0;
    pstGetPdpCtxInfoReq = (TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ_STRU*)pMsgData;
    pstGetPdpCtxInfoCnf = VOS_NULL_PTR;

    /* 计算事件内容长度 */
    ulPdpCtxInfoLen     = sizeof(TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF_STRU)
                            + ((TAF_MAX_CID + 1) * sizeof(TAF_PRI_PDP_QUERY_INFO_STRU));

    /* 申请内存 */
    pstGetPdpCtxInfoCnf = (TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                WUEPS_PID_TAF,
                                ulPdpCtxInfoLen);

    /* 申请消息失败 */
    if ( VOS_NULL_PTR == pstGetPdpCtxInfoCnf )
    {
        MN_ERR_LOG("MN_APS_RcvGetPrimPdpCtxInfoReq:  ERROR : PS_MEM_ALLOC Error!");
        return VOS_ERR;
    }

    /* 填写事件内容 */
#if (FEATURE_ON == FEATURE_LTE)
    for (ucIndex = 0; ucIndex <= TAF_MAX_CID; ucIndex++)
#else
    for (ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++)
#endif
    {
        PS_MEM_SET(&(pstGetPdpCtxInfoCnf->astPdpContextQueryInfo[ulCidNum]),
                   0x00, sizeof(TAF_PRI_PDP_QUERY_INFO_STRU));

        /* 获取Primary PDP上下文信息 */
        Aps_QuePri(ucIndex, &(pstGetPdpCtxInfoCnf->astPdpContextQueryInfo[ulCidNum]), &ulErrCode);

        if ( TAF_PARA_OK == ulErrCode )
        {
            ulCidNum++;
        }
    }

    /* 填写事件控制头 */
    pstGetPdpCtxInfoCnf->stCtrl      = pstGetPdpCtxInfoReq->stCtrl;
    pstGetPdpCtxInfoCnf->ulCidNum    = ulCidNum;
    pstGetPdpCtxInfoCnf->enCause     = TAF_PARA_OK;

    /* 返回处理结果 */
    ulResult =  TAF_APS_SndGetPrimPdpCtxInfoCnf(pstGetPdpCtxInfoCnf,
                                               ulPdpCtxInfoLen);

    /* 释放用于存放PDP上下文参数的内存 */
    PS_MEM_FREE(WUEPS_PID_TAF, pstGetPdpCtxInfoCnf);

    return ulResult;
}

/*****************************************************************************
 函 数 名  : MN_APS_RcvSetSecPdpCtxInfoReq
 功能描述  : 处理ID_TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ消息
 输入参数  : pMsgData                   - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_APS_RcvSetSecPdpCtxInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                                  ulErrCode;
    TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU   *pstSetPdpCtxInfoReq;

    /* 初始化 */
    ulErrCode           = TAF_PARA_OK;
    pstSetPdpCtxInfoReq = (TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU*)pMsgData;

    /* 设置Secondary PDP上下文 */
    Aps_DefPsSecPdpContext(pstSetPdpCtxInfoReq->stCtrl.usClientId,
                           pstSetPdpCtxInfoReq->stCtrl.ucOpId,
                           &(pstSetPdpCtxInfoReq->stPdpContextInfo),
                           &ulErrCode);

    /* 返回处理结果 */
    TAF_APS_SndSetSecPdpCtxInfoCnf(&(pstSetPdpCtxInfoReq->stCtrl),
                                             ulErrCode);

    return;
}

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetSecPdpCtxInfoReq
 功能描述  : 处理ID_TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ消息
 输入参数  : pMsgData                   - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_APS_RcvGetSecPdpCtxInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT8                                   ucIndex;
    VOS_UINT32                                  ucErrCode;
    VOS_UINT32                                  ulPdpCtxInfoLen;
    VOS_UINT32                                  ulCidNum;
    TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ_STRU   *pstGetPdpCtxInfoReq;
    TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF_STRU   *pstGetPdpCtxInfoCnf;

    /* 初始化 */
    ucErrCode           = TAF_PARA_OK;
    ulPdpCtxInfoLen     = 0;
    ulCidNum            = 0;
    pstGetPdpCtxInfoReq = (TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ_STRU*)pMsgData;
    pstGetPdpCtxInfoCnf = VOS_NULL_PTR;

    /* 计算事件内容长度 */
    ulPdpCtxInfoLen     = sizeof(TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF_STRU)
                            + ((TAF_MAX_CID + 1) * sizeof(TAF_PDP_SEC_CONTEXT_STRU));

    /* 申请内存 */
    pstGetPdpCtxInfoCnf = (TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                WUEPS_PID_TAF,
                                ulPdpCtxInfoLen);

    /* 申请消息失败 */
    if ( VOS_NULL_PTR == pstGetPdpCtxInfoCnf )
    {
        MN_ERR_LOG("MN_APS_RcvGetSecPdpCtxInfoReq:  ERROR : PS_MEM_ALLOC Error!");
        return;
    }

    /* 填写事件内容 */
    for ( ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++ )
    {
        PS_MEM_SET(&(pstGetPdpCtxInfoCnf->astPdpContextQueryInfo[ulCidNum]),
                   0x00, sizeof(TAF_PDP_SEC_CONTEXT_STRU));

        /* 获取Secondary PDP上下文信息 */
        Aps_QueSec(ucIndex, &(pstGetPdpCtxInfoCnf->astPdpContextQueryInfo[ulCidNum]), &ucErrCode);

        if ( TAF_PARA_OK == ucErrCode )
        {
            ulCidNum++;
        }
    }

    /* 填写事件控制头 */
    pstGetPdpCtxInfoCnf->stCtrl   = pstGetPdpCtxInfoReq->stCtrl;
    pstGetPdpCtxInfoCnf->ulCidNum = ulCidNum;
    pstGetPdpCtxInfoCnf->enCause  = TAF_PARA_OK;

    /* 返回处理结果 */
    (VOS_VOID)TAF_APS_SndGetSecPdpCtxInfoCnf(pstGetPdpCtxInfoCnf,
                                             ulPdpCtxInfoLen);

    /* 释放用于存放PDP上下文参数的内存 */
    PS_MEM_FREE(WUEPS_PID_TAF, pstGetPdpCtxInfoCnf);

    return;
}

/*****************************************************************************
 函 数 名  : MN_APS_RcvSetTftInfoReq
 功能描述  : 处理ID_TAF_PS_SET_PDP_TFT_INFO_REQ消息
 输入参数  : pMsgData                   - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_APS_RcvSetTftInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                          ulErrCode;
    TAF_PS_SET_TFT_INFO_REQ_STRU       *pstSetTftInfoReq;

    /* 初始化 */
    ulErrCode           = TAF_PARA_OK;
    pstSetTftInfoReq    = (TAF_PS_SET_TFT_INFO_REQ_STRU*)pMsgData;

    /* 设置TFT参数 */
    TAF_APS_SetTftInfo(&(pstSetTftInfoReq->stTftInfo), &ulErrCode);

    /* 返回处理结果 */
    TAF_APS_SndSetTftInfoCnf(&(pstSetTftInfoReq->stCtrl),
                                       ulErrCode);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetRptTftInfoCidNum
 功能描述  : 返回PDP TABLE中设置了TFT参数并上报的CID个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8                  CID个数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年01月28日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_APS_GetRptTftInfoCidNum(VOS_VOID)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCidNum;

    /* 变量初始化 */
    ucIndex         = 0;
    ucCidNum        = 0;

    /* 循环遍历g_TafCidTab, 获取有效TFT参数的CID个数 */
    for (ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++)
    {
        if (TAF_USED == g_TafCidTab[ucIndex].ucPfTabFlag)
        {
            ucCidNum++;
        }
    }

    return ucCidNum;
}

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetTftInfoReq
 功能描述  : 处理ID_TAF_PS_GET_PDP_TFT_INFO_REQ消息
 输入参数  : pMsgData                   - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年01月28日
    作    者   : l00198894
    修改内容   : 根据设置了TFT参数的CID个数申请内存

*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetTftInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulTftInfoLen;
    VOS_UINT32                          ulCidNum;
    TAF_PS_GET_TFT_INFO_REQ_STRU       *pstGetTftInfoReq;
    TAF_PS_GET_TFT_INFO_CNF_STRU       *pstGetTftInfoCnf;

    /* 初始化 */
    ulResult            = VOS_OK;
    ulTftInfoLen        = 0;
    ulCidNum            = 0;
    pstGetTftInfoReq    = (TAF_PS_GET_TFT_INFO_REQ_STRU*)pMsgData;
    pstGetTftInfoCnf    = VOS_NULL_PTR;

    /* 获取有TFT参数的CID的个数 */
    ulCidNum            = TAF_APS_GetRptTftInfoCidNum();

    /* 计算事件内容长度 */
    ulTftInfoLen        = sizeof(TAF_PS_GET_TFT_INFO_CNF_STRU)
                            + (ulCidNum * sizeof(TAF_TFT_QUREY_INFO_STRU));

    /* 申请内存 */
    pstGetTftInfoCnf    = (TAF_PS_GET_TFT_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                WUEPS_PID_TAF,
                                ulTftInfoLen);

    /* 申请消息失败 */
    if ( VOS_NULL_PTR == pstGetTftInfoCnf )
    {
        MN_ERR_LOG("MN_APS_RcvGetPrimPdpCtxInfoReq: PS_MEM_ALLOC Error!");
        return VOS_ERR;
    }

    PS_MEM_SET(pstGetTftInfoCnf, 0x00, ulTftInfoLen);
    ulCidNum            = 0;

    /* 填写事件内容 */
    for ( ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++ )
    {
        /* 该CID上下文对TFT参数没有定义 */
        if ( TAF_FREE == g_TafCidTab[ucIndex].ucPfTabFlag)
        {
            continue;
        }

        /* 填写Tft Qry Param */
        TAF_APS_FillTftQryParam(ucIndex,
                              &(pstGetTftInfoCnf->astTftQueryInfo[ulCidNum]));

        ulCidNum++;
    }

    /* 填写事件控制头 */
    pstGetTftInfoCnf->stCtrl    = pstGetTftInfoReq->stCtrl;
    pstGetTftInfoCnf->ulCidNum  = ulCidNum;
    pstGetTftInfoCnf->enCause   = TAF_PARA_OK;

    /* 返回处理结果 */
    ulResult =  TAF_APS_SndGetTftInfoCnf(pstGetTftInfoCnf,
                                        ulTftInfoLen);

    /* 释放申请用于存放TFT参数的内存 */
    PS_MEM_FREE(WUEPS_PID_TAF, pstGetTftInfoCnf);

    return ulResult;
}

/*****************************************************************************
 函 数 名  : MN_APS_RcvSetUmtsQosInfoReq
 功能描述  : 处理ID_TAF_PS_SET_PDP_UMTS_QOS_INFO_REQ消息
 输入参数  : pMsgData                   - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_APS_RcvSetUmtsQosInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                          ulErrCode;
    TAF_PS_SET_UMTS_QOS_INFO_REQ_STRU  *pstSetUmtsQosInfoReq;

    /* 初始化 */
    ulErrCode               = TAF_PARA_OK;
    pstSetUmtsQosInfoReq    = (TAF_PS_SET_UMTS_QOS_INFO_REQ_STRU*)pMsgData;

    /* 设置UMTS QOS参数 */
    Aps_DefPs3gReqQos(pstSetUmtsQosInfoReq->stCtrl.usClientId,
                      pstSetUmtsQosInfoReq->stCtrl.ucOpId,
                      &(pstSetUmtsQosInfoReq->stUmtsQosInfo),
                      &ulErrCode);

    /* 返回处理结果 */
    (VOS_VOID)TAF_APS_SndSetUmtsQosInfoCnf(&(pstSetUmtsQosInfoReq->stCtrl),
                                           ulErrCode);

    return;
}

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetUmtsQosInfoReq
 功能描述  : 处理ID_TAF_PS_GET_PDP_UMTS_QOS_INFO_REQ消息
 输入参数  : pMsgData                   - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_APS_RcvGetUmtsQosInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulErrCode;
    VOS_UINT32                          ulUmtsQosInfoLen;
    VOS_UINT32                          ulCidNum;
    TAF_PS_GET_UMTS_QOS_INFO_REQ_STRU  *pstGetUmtsQosInfoReq;
    TAF_PS_GET_UMTS_QOS_INFO_CNF_STRU  *pstGetUmtsQosInfoCnf;

    /* 初始化 */
    ulErrCode               = TAF_PARA_OK;
    ulUmtsQosInfoLen        = 0;
    ulCidNum                = 0;
    pstGetUmtsQosInfoReq    = (TAF_PS_GET_UMTS_QOS_INFO_REQ_STRU*)pMsgData;
    pstGetUmtsQosInfoCnf    = VOS_NULL_PTR;

    /* 计算事件内容长度 */
    ulUmtsQosInfoLen        = sizeof(TAF_PS_GET_UMTS_QOS_INFO_CNF_STRU)
                                + ((TAF_MAX_CID + 1) * sizeof(TAF_UMTS_QOS_QUERY_INFO_STRU));

    /* 申请内存 */
    pstGetUmtsQosInfoCnf    = (TAF_PS_GET_UMTS_QOS_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                    WUEPS_PID_TAF,
                                    ulUmtsQosInfoLen);

    /* 申请消息失败 */
    if ( VOS_NULL_PTR == pstGetUmtsQosInfoCnf )
    {
        MN_ERR_LOG("MN_APS_RcvGetUmtsQosInfoReq:  ERROR : PS_MEM_ALLOC Error!");
        return;
    }

    /* 填写事件内容 */
    for ( ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++ )
    {
        PS_MEM_SET(&(pstGetUmtsQosInfoCnf->astUmtsQosQueryInfo[ulCidNum]),
                   0x00, sizeof(TAF_UMTS_QOS_QUERY_INFO_STRU));

        /* 获取CID对应的UMTS QOS参数 */
        MN_APS_GetUtmsQosInfo(ucIndex,
                              &(pstGetUmtsQosInfoCnf->astUmtsQosQueryInfo[ulCidNum]),
                              &ulErrCode);

        if ( TAF_PARA_OK == ulErrCode )
        {
            ulCidNum++;
        }
    }

    /* 填写事件控制头 */
    pstGetUmtsQosInfoCnf->stCtrl    = pstGetUmtsQosInfoReq->stCtrl;
    pstGetUmtsQosInfoCnf->ulCidNum  = ulCidNum;
    pstGetUmtsQosInfoCnf->enCause   = TAF_PARA_OK;

    /* 返回处理结果 */
    (VOS_VOID)TAF_APS_SndGetUmtsQosInfoCnf(pstGetUmtsQosInfoCnf,
                                           ulUmtsQosInfoLen);

    /* 释放用于存放UMTS QOS参数的内存 */
    PS_MEM_FREE(WUEPS_PID_TAF, pstGetUmtsQosInfoCnf);

    return;
}


/*****************************************************************************
 函 数 名  : MN_APS_RcvSetUmtsQosMinInfoReq
 功能描述  : 处理ID_TAF_PS_SET_PDP_UMTS_QOS_MIN_INFO_REQ消息
 输入参数  : pMsgData                   - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_APS_RcvSetUmtsQosMinInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                              ulErrCode;
    TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU  *pstSetUmtsQosMinInfoReq;

    /* 初始化 */
    ulErrCode               = TAF_PARA_OK;
    pstSetUmtsQosMinInfoReq = (TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU*)pMsgData;

    /* 设置UMTS MIN QOS参数 */
    Aps_DefPs3gMinAcceptQos(pstSetUmtsQosMinInfoReq->stCtrl.usClientId,
                            pstSetUmtsQosMinInfoReq->stCtrl.ucOpId,
                            &(pstSetUmtsQosMinInfoReq->stUmtsQosMinInfo),
                            &ulErrCode);

    /* 返回处理结果 */
    (VOS_VOID)TAF_APS_SndSetUmtsQosMinInfoCnf(&(pstSetUmtsQosMinInfoReq->stCtrl),
                                              ulErrCode);

    return;
}

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetUmtsQosMinInfoReq
 功能描述  : 处理ID_TAF_PS_GET_PDP_UMTS_QOS_MIN_INFO_REQ消息
 输入参数  : pMsgData                   - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_APS_RcvGetUmtsQosMinInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulErrCode;
    VOS_UINT32                              ulUmtsQosMinInfoLen;
    VOS_UINT32                              ulCidNum;
    TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ_STRU  *pstGetUmtsQosMinInfoReq;
    TAF_PS_GET_UMTS_QOS_MIN_INFO_CNF_STRU  *pstGetUmtsQosMinInfoCnf;

    /* 初始化 */
    ulErrCode               = TAF_PARA_OK;
    ulUmtsQosMinInfoLen     = 0;
    ulCidNum                = 0;
    pstGetUmtsQosMinInfoReq = (TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ_STRU*)pMsgData;
    pstGetUmtsQosMinInfoCnf = VOS_NULL_PTR;

    /* 计算事件内容长度 */
    ulUmtsQosMinInfoLen     = sizeof(TAF_PS_GET_UMTS_QOS_MIN_INFO_CNF_STRU)
                                + ((TAF_MAX_CID + 1) * sizeof(TAF_UMTS_QOS_QUERY_INFO_STRU));

    /* 申请内存 */
    pstGetUmtsQosMinInfoCnf = (TAF_PS_GET_UMTS_QOS_MIN_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                    WUEPS_PID_TAF,
                                    ulUmtsQosMinInfoLen);

    /* 申请消息失败 */
    if ( VOS_NULL_PTR == pstGetUmtsQosMinInfoCnf )
    {
        MN_ERR_LOG("MN_APS_RcvGetUmtsQosMinInfoReq: PS_MEM_ALLOC Error!");
        return;
    }

    /* 填写事件内容 */
    for ( ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++ )
    {
        PS_MEM_SET(&(pstGetUmtsQosMinInfoCnf->astUmtsQosQueryInfo[ulCidNum]),
                   0x00, sizeof(TAF_UMTS_QOS_QUERY_INFO_STRU));

        /* 获取CID对应的UMTS MIN QOS参数 */
        MN_APS_GetUtmsQosMinInfo(ucIndex,
                                 &(pstGetUmtsQosMinInfoCnf->astUmtsQosQueryInfo[ulCidNum]),
                                 &ulErrCode);

        if ( TAF_PARA_OK == ulErrCode )
        {
            ulCidNum++;
        }
    }

    /* 填写事件控制头 */
    pstGetUmtsQosMinInfoCnf->stCtrl     = pstGetUmtsQosMinInfoReq->stCtrl;
    pstGetUmtsQosMinInfoCnf->ulCidNum   = ulCidNum;
    pstGetUmtsQosMinInfoCnf->enCause    = TAF_PARA_OK;

    /* 返回处理结果 */
    (VOS_VOID)TAF_APS_SndGetUmtsQosMinInfoCnf(pstGetUmtsQosMinInfoCnf,
                                              ulUmtsQosMinInfoLen);

    PS_MEM_FREE(WUEPS_PID_TAF, pstGetUmtsQosMinInfoCnf);

    return;
}

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetDynamicUmtsQosInfoReq
 功能描述  : 处理ID_TAF_PS_GET_DYNAMIC_PDP_UMTS_QOS_INFO_REQ消息
 输入参数  : pMsgData                   - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_APS_RcvGetDynamicUmtsQosInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT8                                   ucIndex;
    VOS_UINT8                                   aucCidProcList[TAF_MAX_CID + 1];
    VOS_UINT32                                  ulErrCode;
    VOS_UINT32                                  ulCidNum;
    VOS_UINT32                                  ulDynamicUmtsQosInfoLen;
    TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ_STRU  *pstDynamicUmtsQosInfoReq;
    TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_CNF_STRU  *pstDynamicUmtsQosInfoCnf;

    /* 初始化 */
    ulErrCode                = TAF_PARA_OK;
    ulDynamicUmtsQosInfoLen  = 0;
    ulCidNum                 = 0;
    pstDynamicUmtsQosInfoReq = (TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ_STRU*)pMsgData;
    pstDynamicUmtsQosInfoCnf = VOS_NULL_PTR;

    /* 生成CID处理列表 */
    PS_MEM_SET(aucCidProcList, 0x00, (TAF_MAX_CID + 1));
    if ( VOS_ERR == MN_APS_BuildCidProcList(pstDynamicUmtsQosInfoReq->stCidListInfo.aucCid,
                                            aucCidProcList) )
    {
        MN_WARN_LOG("MN_APS_RcvGetDynamicUmtsQosInfoReq: Invalid CID list!");
    }

    /* 计算事件内容长度 */
    ulDynamicUmtsQosInfoLen  = sizeof(TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_CNF_STRU)
                                + ((TAF_MAX_CID + 1) * sizeof(TAF_UMTS_QOS_QUERY_INFO_STRU));

    /* 申请内存 */
    pstDynamicUmtsQosInfoCnf = (TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                    WUEPS_PID_TAF,
                                    ulDynamicUmtsQosInfoLen);

    /* 申请消息失败 */
    if ( VOS_NULL_PTR == pstDynamicUmtsQosInfoCnf )
    {
        MN_ERR_LOG("MN_APS_RcvGetDynamicUmtsQosInfoReq: PS_MEM_ALLOC Error!");
        return;
    }

    /* 填写事件内容 */
    for ( ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++ )
    {
        if ( VOS_TRUE == aucCidProcList[ucIndex] )
        {
            PS_MEM_SET(&(pstDynamicUmtsQosInfoCnf->astUmtsQosQueryInfo[ulCidNum]),
                       0x00, sizeof(TAF_UMTS_QOS_QUERY_INFO_STRU));

            /* 获取CID对应的UMTS QOS信息 */
            Aps_QueQosNeg(ucIndex,
                          &(pstDynamicUmtsQosInfoCnf->astUmtsQosQueryInfo[ulCidNum]),
                          &ulErrCode);

            if ( TAF_PARA_OK == ulErrCode )
            {
                ulCidNum++;
            }
        }
    }

    /* 填写事件控制头 */
    pstDynamicUmtsQosInfoCnf->stCtrl    = pstDynamicUmtsQosInfoReq->stCtrl;
    pstDynamicUmtsQosInfoCnf->ulCidNum  = ulCidNum;
    pstDynamicUmtsQosInfoCnf->enCause   = TAF_PARA_OK;

    /* 返回处理结果 */
    if ( VOS_OK != TAF_APS_SndGetDynamicUmtsQosInfoCnf(pstDynamicUmtsQosInfoCnf,
                                                  ulDynamicUmtsQosInfoLen) )
    {
        MN_WARN_LOG("MN_APS_RcvGetDynamicUmtsQosInfoReq: TAF_APS_SndGetDynamicUmtsQosInfoCnf ERROR!");
    }

    /* 释放申请用于存放UMTS QOS参数的内存 */
    PS_MEM_FREE(WUEPS_PID_TAF, pstDynamicUmtsQosInfoCnf);

    return;
}

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetPdpIpAddrInfoReq
 功能描述  : 处理ID_TAF_PS_GET_PDP_ADDR_INFO_REQ消息
 输入参数  : pMsgData                   - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetPdpIpAddrInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT8                                   ucIndex;
    VOS_UINT8                                   aucCidProcList[TAF_MAX_CID + 1];
    VOS_UINT32                                  ulResult;
    VOS_UINT32                                  ulErrCode;
    VOS_UINT32                                  ulPdpIpAddrInfoLen;
    VOS_UINT32                                  ulCidNum;
    TAF_PS_GET_PDP_IP_ADDR_INFO_REQ_STRU       *pstPdpIpAddrInfoReq;
    TAF_PS_GET_PDP_IP_ADDR_INFO_CNF_STRU       *pstPdpIpAddrInfoCnf;

    /* 初始化 */
    ulResult            = VOS_OK;
    ulErrCode           = TAF_PARA_OK;
    ulPdpIpAddrInfoLen  = 0;
    ulCidNum            = 0;
    pstPdpIpAddrInfoReq = (TAF_PS_GET_PDP_IP_ADDR_INFO_REQ_STRU*)pMsgData;
    pstPdpIpAddrInfoCnf = VOS_NULL_PTR;

    /* 生成CID处理列表 */
    PS_MEM_SET(aucCidProcList, 0x00, (TAF_MAX_CID + 1));
    if ( VOS_ERR == MN_APS_BuildCidProcList(pstPdpIpAddrInfoReq->stCidListInfo.aucCid,
                                            aucCidProcList) )
    {
        MN_WARN_LOG("MN_APS_RcvGetPdpIpAddrInfoReq: Invalid CID list!");
    }

    /* 计算事件内容长度 */
    ulPdpIpAddrInfoLen  = sizeof(TAF_PS_GET_PDP_IP_ADDR_INFO_CNF_STRU)
                            + ((TAF_MAX_CID + 1) * sizeof(TAF_PDP_ADDR_QUERY_INFO_STRU));

    /* 申请内存 */
    pstPdpIpAddrInfoCnf = (TAF_PS_GET_PDP_IP_ADDR_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                    WUEPS_PID_TAF,
                                    ulPdpIpAddrInfoLen);

    /* 申请消息失败 */
    if ( VOS_NULL_PTR == pstPdpIpAddrInfoCnf )
    {
        MN_ERR_LOG("MN_APS_RcvGetPdpIpAddrInfoReq: PS_MEM_ALLOC Error!");
        return VOS_ERR;
    }

    /* 填写事件内容 */
    for ( ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++ )
    {
        if ( VOS_TRUE == aucCidProcList[ucIndex] )
        {
            PS_MEM_SET(&(pstPdpIpAddrInfoCnf->astPdpAddrQueryInfo[ulCidNum]),
                       0x00, sizeof(TAF_PDP_ADDR_QUERY_INFO_STRU));

            /* 获取CID对应的IP地址信息 */
            Aps_QueRealIpAddr(ucIndex,
                              &(pstPdpIpAddrInfoCnf->astPdpAddrQueryInfo[ulCidNum]),
                              &ulErrCode);

            if ( TAF_PARA_OK == ulErrCode )
            {
                ulCidNum++;
            }
        }
    }

    /* 填写事件控制头 */
    pstPdpIpAddrInfoCnf->stCtrl     = pstPdpIpAddrInfoReq->stCtrl;
    pstPdpIpAddrInfoCnf->ulCidNum   = ulCidNum;
    pstPdpIpAddrInfoCnf->enCause    = TAF_PARA_OK;

    /* 返回处理结果 */
    ulResult = TAF_APS_SndGetPdpIpAddrInfoCnf(pstPdpIpAddrInfoCnf,
                                             ulPdpIpAddrInfoLen);

    /* 释放用于存放IP地址信息的内存 */
    PS_MEM_FREE(WUEPS_PID_TAF, pstPdpIpAddrInfoCnf);

    return ulResult;
}

/*****************************************************************************
 函 数 名  : MN_APS_RcvSetAnsModeInfoReq
 功能描述  : 处理ID_TAF_PS_SET_ANSWER_MODE_INFO_REQ消息
 输入参数  : pMsgData                   - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_APS_RcvSetAnsModeInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                              ulErrCode;
    TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU   *pstSetAnsModeInfoReq;

    /* 初始化 */
    ulErrCode            = TAF_PARA_OK;
    pstSetAnsModeInfoReq = (TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU*)pMsgData;

    /* 检查应答模式是否合法 */
    if ( (TAF_PDP_ANSWER_MODE_MANUAL == pstSetAnsModeInfoReq->ulAnsMode)
      || (TAF_PDP_ANSWER_MODE_AUTO   == pstSetAnsModeInfoReq->ulAnsMode) )
    {
        /* 设置应答模式 */
        Aps_SetPsAnsMode(pstSetAnsModeInfoReq->stCtrl.usClientId,
                         pstSetAnsModeInfoReq->stCtrl.ucOpId,
                         (TAF_PDP_ANSWER_MODE_ENUM_UINT8)pstSetAnsModeInfoReq->ulAnsMode,
                         &ulErrCode);
    }
    else
    {
        ulErrCode       = TAF_PARA_SET_ERROR;
    }

    /* 返回处理结果 */
    TAF_APS_SndSetAnsModeInfoCnf(&(pstSetAnsModeInfoReq->stCtrl),
                                           ulErrCode);

    return;
}

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetAnsModeInfoReq
 功能描述  : 处理ID_TAF_PS_GET_ANSWER_MODE_INFO_REQ消息
 输入参数  : pMsgData                   - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_APS_RcvGetAnsModeInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                              ulResult;
    VOS_UINT32                              ulErrCode;
    VOS_UINT32                              ulAnsMode;
    TAF_PS_GET_ANSWER_MODE_INFO_REQ_STRU   *pstGetAnsModeInfoReq;

    /* 初始化 */
    ulResult             = VOS_OK;
    ulErrCode            = TAF_PARA_OK;
    pstGetAnsModeInfoReq = (TAF_PS_GET_ANSWER_MODE_INFO_REQ_STRU*)pMsgData;

    /* 获取应答模式 */
    ulAnsMode            = g_PsAnsMode.enAnsMode;

    /* 返回处理结果 */
    ulResult = TAF_APS_SndGetAnsModeInfoCnf(&(pstGetAnsModeInfoReq->stCtrl),
                                           ulErrCode,
                                           ulAnsMode);

    MN_INFO_LOG1("MN_APS_RcvGetAnsModeInfoReq: TAF_APS_SndGetAnsModeInfoCnf Result:", (VOS_INT)ulResult);

    return;
}

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetDynamicPrimPdpCtxInfoReq
 功能描述  : 处理ID_TAF_PS_GET_DYNAMIC_PRI_PDP_CONTEXT_INFO_REQ消息
 输入参数  : pMsgData                   - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetDynamicPrimPdpCtxInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                                          ulResult;
    VOS_UINT32                                          ulErrCode;
    VOS_UINT32                                          ulCidNum;
    TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU  *pstGetDynamicPdpCtxInfoReq;

    /* 初始化 */
    ulResult                    = VOS_OK;
    ulErrCode                   = TAF_PARA_OK;
    ulCidNum                    = 0;
    pstGetDynamicPdpCtxInfoReq  = (TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU*)pMsgData;

    /* GU模未实现该命令, 直接返回OK */

    /* 返回处理结果 */
    ulResult = TAF_APS_SndGetDynamicPrimPdpCtxInfoCnf(&(pstGetDynamicPdpCtxInfoReq->stCtrl),
                                                     ulErrCode,
                                                     ulCidNum);

    return ulResult;
}

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetDynamicSecPdpCtxInfoReq
 功能描述  : 处理ID_TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ消息
 输入参数  : pMsgData                   - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetDynamicSecPdpCtxInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                                          ulResult;
    VOS_UINT32                                          ulErrCode;
    VOS_UINT32                                          ulCidNum;
    TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ_STRU   *pstGetDynamicPdpCtxInfoReq;

    /* 初始化 */
    ulResult                    = VOS_OK;
    ulErrCode                   = TAF_PARA_OK;
    ulCidNum                    = 0;
    pstGetDynamicPdpCtxInfoReq  = (TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ_STRU*)pMsgData;

    /* GU模未实现该命令, 直接返回OK */

    /* 返回处理结果 */
    ulResult = TAF_APS_SndGetDynamicPrimPdpCtxInfoCnf(&(pstGetDynamicPdpCtxInfoReq->stCtrl),
                                                     ulErrCode,
                                                     ulCidNum);

    return ulResult;
}

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetDynamicTftInfoReq
 功能描述  : 处理ID_TAF_PS_GET_DYNAMIC_PDP_TFT_INFO_REQ消息
 输入参数  : pMsgData                   - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetDynamicTftInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                              ulResult;
    VOS_UINT32                              ulErrCode;
    VOS_UINT32                              ulCidNum;
    TAF_PS_GET_DYNAMIC_TFT_INFO_REQ_STRU   *pstGetDynamicTftInfoReq;

    /* 初始化 */
    ulResult                = VOS_OK;
    ulErrCode               = TAF_PARA_OK;
    ulCidNum                = 0;
    pstGetDynamicTftInfoReq = (TAF_PS_GET_DYNAMIC_TFT_INFO_REQ_STRU*)pMsgData;

    /* GU模未实现该命令, 直接返回OK */

    /* 返回处理结果 */
    ulResult = TAF_APS_SndGetDynamicTftInfoCnf(&(pstGetDynamicTftInfoReq->stCtrl),
                                                     ulErrCode,
                                                     ulCidNum);

    return ulResult;
}

/*****************************************************************************
 函 数 名  : MN_APS_RcvSetPdpDnsInfoReq
 功能描述  : 处理ID_TAF_PS_SET_PDP_DNS_INFO_REQ消息
 输入参数  : pMsgData                   - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_APS_RcvSetPdpDnsInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulErrCode;
    TAF_PS_SET_PDP_DNS_INFO_REQ_STRU   *pstSetDnsInfoReq;

    /* 初始化 */
    ulResult          = VOS_OK;
    ulErrCode         = TAF_PARA_OK;
    pstSetDnsInfoReq  = (TAF_PS_SET_PDP_DNS_INFO_REQ_STRU*)pMsgData;

    /* 设置PDP DNS信息 */
    Aps_DefPsDns(pstSetDnsInfoReq->stCtrl.usClientId,
                 pstSetDnsInfoReq->stCtrl.ucOpId,
                 &(pstSetDnsInfoReq->stPdpDnsInfo),
                 &ulErrCode);

    ulResult = TAF_APS_SndSetPdpDnsInfoCnf(&(pstSetDnsInfoReq->stCtrl),
                                          ulErrCode);

    return ulResult;
}

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetPdpDnsInfoReq
 功能描述  : 处理ID_TAF_PS_GET_PDP_DNS_INFO_REQ消息
 输入参数  : pMsgData                   - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetPdpDnsInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulErrCode;
    VOS_UINT32                          ulPdpDnsInfoLen;
    VOS_UINT32                          ulCidNum;
    TAF_PS_GET_PDP_DNS_INFO_REQ_STRU   *pstGetPdpDnsInfoReq;
    TAF_PS_GET_PDP_DNS_INFO_CNF_STRU   *pstGetPdpDnsInfoCnf;

    /* 初始化 */
    ulResult            = VOS_OK;
    ulErrCode           = TAF_PARA_OK;
    ulPdpDnsInfoLen     = 0;
    ulCidNum            = 0;
    pstGetPdpDnsInfoReq = (TAF_PS_GET_PDP_DNS_INFO_REQ_STRU*)pMsgData;
    pstGetPdpDnsInfoCnf = VOS_NULL_PTR;

    /* 计算事件内容长度 */
    ulPdpDnsInfoLen     = sizeof(TAF_PS_GET_PDP_DNS_INFO_CNF_STRU)
                                + ((TAF_MAX_CID + 1) * sizeof(TAF_AUTH_QUERY_INFO_STRU));

    /* 申请内存 */
    pstGetPdpDnsInfoCnf = (TAF_PS_GET_PDP_DNS_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                    WUEPS_PID_TAF,
                                    ulPdpDnsInfoLen);

    /* 申请消息失败 */
    if ( VOS_NULL_PTR == pstGetPdpDnsInfoCnf )
    {
        MN_ERR_LOG("MN_APS_RcvGetUmtsQosInfoReq: PS_MEM_ALLOC Error!");
        return VOS_ERR;
    }

    /* 填写事件内容 */
    for ( ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++ )
    {
        PS_MEM_SET(&(pstGetPdpDnsInfoCnf->astPdpDnsQueryInfo[ulCidNum]),
                   0x00, sizeof(TAF_DNS_QUERY_INFO_STRU));

        /* 获取CID对应的PDP DNS信息 */
        Aps_QueDns(ucIndex,
                   &(pstGetPdpDnsInfoCnf->astPdpDnsQueryInfo[ulCidNum]),
                   &ulErrCode);

        if ( TAF_PARA_OK == ulErrCode )
        {
            ulCidNum++;
        }
    }

    /* 填写事件控制头 */
    pstGetPdpDnsInfoCnf->stCtrl     = pstGetPdpDnsInfoReq->stCtrl;
    pstGetPdpDnsInfoCnf->ulCidNum   = ulCidNum;
    pstGetPdpDnsInfoCnf->enCause    = TAF_PARA_OK;

    /* 返回处理结果 */
    ulResult = TAF_APS_SndGetPdpDnsInfoCnf(pstGetPdpDnsInfoCnf,
                                          ulPdpDnsInfoLen);

    /* 释放申请用于存放PDP DNS参数的内存 */
    PS_MEM_FREE(WUEPS_PID_TAF, pstGetPdpDnsInfoCnf);

    return ulResult;
}

/*****************************************************************************
 函 数 名  : MN_APS_RcvConfigNbnsFunctionReq
 功能描述  : 处理ID_MN_PS_CONFIG_NBNS_FUNCTION_REQ消息
 输入参数  : pMsgData                   - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_APS_RcvConfigNbnsFunctionReq(
    VOS_VOID                           *pMsgData
)
{
    TAF_PS_CONFIG_NBNS_FUNCTION_REQ_STRU   *pstConfigNbnsFunReq;

    /* 初始化 */
    pstConfigNbnsFunReq = (TAF_PS_CONFIG_NBNS_FUNCTION_REQ_STRU*)pMsgData;

    /* 更新WINS配置 */
    Aps_UpdateWinsConfig((VOS_UINT8)pstConfigNbnsFunReq->ulEnabled);

    return;
}

/* Deleted by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
/* Deleted by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */


/*****************************************************************************
 函 数 名  : MN_APS_RcvSetAuthDataInfoReq
 功能描述  : 处理ID_TAF_PS_SET_AUTHDATA_INFO_REQ消息
 输入参数  : pMsgData                   - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_APS_RcvSetAuthDataInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                          ulErrCode;
    TAF_PS_SET_AUTHDATA_INFO_REQ_STRU  *pstAuthDataReq;

    /* 初始化 */
    ulErrCode       = TAF_PARA_OK;
    pstAuthDataReq  = (TAF_PS_SET_AUTHDATA_INFO_REQ_STRU*)pMsgData;

    /* 设置AUTHDATA参数(NDIS) */
    Aps_DefNdisAuthdata(pstAuthDataReq->stCtrl.usClientId,
                        pstAuthDataReq->stCtrl.ucOpId,
                        &(pstAuthDataReq->stAuthDataInfo),
                        &ulErrCode);

    /* 返回处理结果 */
    if (VOS_OK != TAF_APS_SndSetAuthDataInfoCnf(&(pstAuthDataReq->stCtrl),
                                            ulErrCode))
    {
        MN_ERR_LOG("MN_APS_RcvGetAuthDataInfoReq: TAF_APS_SndGetAuthDataInfoCnf Error!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetAuthDataInfoReq
 功能描述  : 处理ID_TAF_PS_GET_AUTHDATA_INFO_REQ消息
 输入参数  : pMsgData                   - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2013年12月25日
    作    者   : A00165503
    修改内容   : DTS2013122403650: ^AUTHDATA命令支持CID0
*****************************************************************************/
VOS_VOID MN_APS_RcvGetAuthDataInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulErrCode;
    VOS_UINT32                          ulAuthDataInfoLen;
    VOS_UINT32                          ulCidNum;
    TAF_PS_GET_AUTHDATA_INFO_REQ_STRU  *pstGetAuthDataInfoReq;
    TAF_PS_GET_AUTHDATA_INFO_CNF_STRU  *pstGetAuthDataInfoCnf;

    /* 初始化 */
    ulErrCode               = TAF_PARA_OK;
    ulAuthDataInfoLen       = 0;
    ulCidNum                = 0;
    pstGetAuthDataInfoReq   = (TAF_PS_GET_AUTHDATA_INFO_REQ_STRU*)pMsgData;
    pstGetAuthDataInfoCnf   = VOS_NULL_PTR;

    /* 计算事件内容长度 */
    ulAuthDataInfoLen        = sizeof(TAF_PS_GET_AUTHDATA_INFO_CNF_STRU)
                                + ((TAF_MAX_CID + 1) * sizeof(TAF_AUTHDATA_QUERY_INFO_STRU));

    /* 申请内存 */
    pstGetAuthDataInfoCnf    = (TAF_PS_GET_AUTHDATA_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                    WUEPS_PID_TAF,
                                    ulAuthDataInfoLen);

    /* 申请消息失败 */
    if ( VOS_NULL_PTR == pstGetAuthDataInfoCnf )
    {
        MN_ERR_LOG("MN_APS_RcvGetAuthDataInfoReq: PS_MEM_ALLOC Error!");
        return;
    }

    /* 填写事件内容 */
    for ( ucIndex = 0; ucIndex <= TAF_MAX_CID; ucIndex++ )
    {
        PS_MEM_SET(&(pstGetAuthDataInfoCnf->astAuthDataQueryInfo[ulCidNum]),
                   0x00, sizeof(TAF_AUTHDATA_QUERY_INFO_STRU));

        /* 获取UTHDATA参数(NDIS) */
        Aps_QueAuthdata(ucIndex,
                        &(pstGetAuthDataInfoCnf->astAuthDataQueryInfo[ulCidNum]),
                        &ulErrCode);

        if ( TAF_PARA_OK == ulErrCode )
        {
            ulCidNum++;
        }
    }

    /* 填写事件控制头 */
    pstGetAuthDataInfoCnf->stCtrl       = pstGetAuthDataInfoReq->stCtrl;
    pstGetAuthDataInfoCnf->ulCidNum     = ulCidNum;
    pstGetAuthDataInfoCnf->enCause      = TAF_PARA_OK;

    /* 返回处理结果 */
    if (VOS_OK != TAF_APS_SndGetAuthDataInfoCnf(pstGetAuthDataInfoCnf,
                                            ulAuthDataInfoLen))
    {
        MN_ERR_LOG("MN_APS_RcvGetAuthDataInfoReq: TAF_APS_SndGetAuthDataInfoCnf Error!");
    }

    /* 释放申请用于存放AUTHDATA参数的内存 */
    PS_MEM_FREE(WUEPS_PID_TAF, pstGetAuthDataInfoCnf);

    return;
}

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetGprsActiveTypeReq
 功能描述  : 处理ID_MSG_TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ消息
 输入参数  : pMsgData                   - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetGprsActiveTypeReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                              ulResult;
    VOS_UINT32                              ulErrCode;
    TAF_PDP_TYPE_ENUM_UINT8                 enPdpType;
    TAF_CID_GPRS_ACTIVE_TYPE_STRU           stCidGprsActiveType;
    TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU *pstGetGprsActiveTypeReq;

    /* 初始化 */
    ulResult                  = VOS_OK;
    ulErrCode                 = TAF_PARA_OK;
    pstGetGprsActiveTypeReq   = (TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU*)pMsgData;

    /* 获取GPRS激活类型 */
    PS_MEM_SET(&stCidGprsActiveType, 0x00, sizeof(TAF_CID_GPRS_ACTIVE_TYPE_STRU));
    stCidGprsActiveType.ucCid = pstGetGprsActiveTypeReq->stAtdPara.ucCid;

    enPdpType = Taf_GetCidType(pstGetGprsActiveTypeReq->stAtdPara.ucCid);

    if ( TAF_PDP_TYPE_BUTT != enPdpType )
    {
        /* L2p存在 */
        if ( VOS_TRUE == pstGetGprsActiveTypeReq->stAtdPara.bitOpL2p )
        {
            if ( TAF_L2P_PPP == pstGetGprsActiveTypeReq->stAtdPara.enL2p )
            {
                /* L2P为PPP */
                switch ( enPdpType )
                {
                    case TAF_PDP_IPV4:
                        /* IP类型,进行IP激活，TE中未启动PPP，MT中不启动PPP */
                        stCidGprsActiveType.enActiveType = TAF_IP_ACTIVE_TE_PPP_MT_PPP_TYPE;
                        break;

                #if (FEATURE_ON == FEATURE_IPV6)
                    case TAF_PDP_IPV6:
                    case TAF_PDP_IPV4V6:
                        /* IP类型,进行IP激活，TE中未启动PPP，MT中不启动PPP */
                        stCidGprsActiveType.enActiveType = TAF_IP_ACTIVE_TE_PPP_MT_PPP_TYPE;
                        break;
                #endif

                    default:
                        ulErrCode = TAF_PARA_UNSPECIFIED_ERROR;
                        break;
                }
            }
            else
            {
                /* L2P为NULL */
                switch ( enPdpType )
                {
                    case TAF_PDP_IPV4:
                        /* IP类型,进行IP激活，TE中未启动PPP，MT中不启动PPP */
                        stCidGprsActiveType.enActiveType = TAF_IP_ACTIVE_TE_NOT_PPP_MT_NOT_PPP_TYPE;
                        break;

                #if (FEATURE_ON == FEATURE_IPV6)
                    case TAF_PDP_IPV6:
                    case TAF_PDP_IPV4V6:
                        /* IP类型,进行IP激活，TE中未启动PPP，MT中不启动PPP */
                        stCidGprsActiveType.enActiveType = TAF_IP_ACTIVE_TE_NOT_PPP_MT_NOT_PPP_TYPE;
                        break;
                #endif

                    case TAF_PDP_PPP:
                        /* PPP类型,进行PPP激活，TE中启动了PPP，MT中不启动PPP */
                        stCidGprsActiveType.enActiveType = TAF_PPP_ACTIVE_TE_PPP_MT_NOT_PPP_TYPE;
                        break;

                    default:
                        ulErrCode = TAF_PARA_UNSPECIFIED_ERROR;
                        break;
                }
            }
        }
        else
        {
            /* L2p不存在 */
            switch (enPdpType)
            {
                case TAF_PDP_IPV4:
                    /* IP类型,进行IP激活，TE中启动了PPP，MT中启动PPP */
                    stCidGprsActiveType.enActiveType = TAF_IP_ACTIVE_TE_PPP_MT_PPP_TYPE;
                    break;

            #if (FEATURE_ON == FEATURE_IPV6)
                case TAF_PDP_IPV6:
                case TAF_PDP_IPV4V6:
                    /* IP类型,进行IP激活，TE中启动了PPP，MT中启动PPP */
                    stCidGprsActiveType.enActiveType = TAF_IP_ACTIVE_TE_PPP_MT_PPP_TYPE;
                    break;
            #endif

                case TAF_PDP_PPP:
                    /* PPP类型,进行PPP激活，TE中启动了PPP，MT中不启动PPP */
                    stCidGprsActiveType.enActiveType = TAF_PPP_ACTIVE_TE_PPP_MT_NOT_PPP_TYPE;
                    break;

                default:
                    ulErrCode = TAF_PARA_UNSPECIFIED_ERROR;
                    break;
            }
        }
    }
    else
    {
        ulErrCode = TAF_PARA_UNSPECIFIED_ERROR;
    }

    ulResult = TAF_APS_SndGetGprsActiveTypeCnf(&(pstGetGprsActiveTypeReq->stCtrl),
                                              ulErrCode,
                                              &stCidGprsActiveType);

    return ulResult;
}

/*****************************************************************************
 函 数 名  : MN_APS_PppCovertConfigInfo
 功能描述  : 将PPP模块激活请求的参数转换为NAS的拨号参数.
             PPP模块发送给AT的AUTH参数和IPCP参数为数组结构; NAS PDP激活时的AUTH
             参数和IPCP参数为指针结构。

 输入参数  : PPP_REQ_CONFIG_INFO_STRU           *pstPppReqConfigInfo
             AT_PPP_REQ_CONFIG_INFO_STRU        *pstPppAtReqConfigInfo
             pstPppAtReqConfigInfo: 为来自PPP模块的AUTH和IPCP成员为数组的参数
             pstPppReqConfigInfo: 为NAS PDP激活时AUTH和IPCP为指针的参数

 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月29日
    作    者   : L00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_APS_PppCovertConfigInfo(
    PPP_REQ_CONFIG_INFO_STRU           *pstPppReqConfigInfo,
    TAF_PPP_REQ_CONFIG_INFO_STRU       *pstPppAtReqConfigInfo
)
{
    TAF_PPP_REQ_AUTH_CONFIG_INFO_STRU  *pstPppActAuth;
    VOS_UINT16                          usPapLen;
    VOS_UINT8                          *pucPapBuf;
    VOS_UINT16                          usChallengeLen;
    VOS_UINT16                          usResponseLen;
    VOS_UINT8                          *pucChallengeBuf;
    VOS_UINT8                          *pucResponseBuf;
    VOS_UINT16                          usIpcpLen;
    VOS_UINT8                          *pucIpcpBuf;

    pstPppActAuth   = VOS_NULL_PTR;
    usPapLen        = 0;
    pucPapBuf       = VOS_NULL_PTR;
    usChallengeLen  = 0;
    usResponseLen   = 0;
    pucChallengeBuf = VOS_NULL_PTR;
    pucResponseBuf  = VOS_NULL_PTR;
    usIpcpLen       = 0;
    pucIpcpBuf      = VOS_NULL_PTR;

    if (VOS_NULL_PTR == pstPppReqConfigInfo)
    {
        MN_ERR_LOG("MN_APS_PppCovertConfigInfo: pstPppReqConfigInfo NULL_PTR!");
        return VOS_ERR;
    }

    /* 目标结构初始化 */
    PS_MEM_SET(pstPppReqConfigInfo, 0x00, sizeof(PPP_REQ_CONFIG_INFO_STRU));


    /* 获取AUTH数据的指针 */
    pstPppActAuth = &(pstPppAtReqConfigInfo->stAuth);

    /* 获取认证类型 */
    pstPppReqConfigInfo->stAuth.ucAuthType = pstPppActAuth->enAuthType;

    if (PPP_PAP_AUTH_TYPE == pstPppActAuth->enAuthType)
    {
        /* 获取pap req参数的长度 */
        usPapLen = pstPppActAuth->enAuthContent.stPapContent.usPapReqLen;

        pucPapBuf = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_TAF, usPapLen);
        if (VOS_NULL_PTR == pucPapBuf)
        {
            MN_ERR_LOG("MN_APS_PppCovertConfigInfo:  ERROR : PS_MEM_ALLOC Error!");
            return VOS_ERR;
        }

        /* pap req参数从数组复制到指针中 */
        PS_MEM_CPY(pucPapBuf, pstPppActAuth->enAuthContent.stPapContent.aucPapReqBuf,
                   usPapLen);

        pstPppReqConfigInfo->stAuth.AuthContent.PapContent.usPapReqLen = usPapLen;
        pstPppReqConfigInfo->stAuth.AuthContent.PapContent.pPapReq     = pucPapBuf;
    }
    else if (PPP_CHAP_AUTH_TYPE == pstPppActAuth->enAuthType)
    {
        /* 获取ChapChallenge参数和ChapResponse参数的长度 */
        usChallengeLen = pstPppActAuth->enAuthContent.stChapContent.usChapChallengeLen;
        usResponseLen  = pstPppActAuth->enAuthContent.stChapContent.usChapResponseLen;

        pucChallengeBuf = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_TAF, usChallengeLen);
        if (VOS_NULL_PTR == pucChallengeBuf)
        {
            MN_ERR_LOG("MN_APS_PppCovertConfigInfo:  ERROR : PS_MEM_ALLOC Error!");
            return VOS_ERR;
        }

        /* ChapChallenge参数从数组复制到指针中 */
        PS_MEM_CPY(pucChallengeBuf, pstPppActAuth->enAuthContent.stChapContent.aucChapChallengeBuf,
                   usChallengeLen);

        pucResponseBuf = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_TAF, usResponseLen);
        if (VOS_NULL_PTR == pucResponseBuf)
        {
            MN_ERR_LOG("MN_APS_PppCovertConfigInfo:  ERROR : PS_MEM_ALLOC Error!");

            /* 释放上面已分配的内存 */
            PS_MEM_FREE(WUEPS_PID_TAF, pucChallengeBuf);
            return VOS_ERR;
        }

        /* ChapResponse参数从数组中复制到指针中 */
        PS_MEM_CPY(pucResponseBuf, pstPppActAuth->enAuthContent.stChapContent.aucChapResponseBuf,
                   usResponseLen);

        pstPppReqConfigInfo->stAuth.AuthContent.ChapContent.usChapChallengeLen = usChallengeLen;
        pstPppReqConfigInfo->stAuth.AuthContent.ChapContent.usChapResponseLen  = usResponseLen;
        pstPppReqConfigInfo->stAuth.AuthContent.ChapContent.pChapChallenge     = pucChallengeBuf;
        pstPppReqConfigInfo->stAuth.AuthContent.ChapContent.pChapResponse      = pucResponseBuf;

    }
    else
    {
    }

    /*  获取IPCP参数长度  */
    usIpcpLen = pstPppAtReqConfigInfo->stIPCP.usIpcpLen;
    if (usIpcpLen > 0)
    {
        pucIpcpBuf = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_TAF, usIpcpLen);
        if (VOS_NULL_PTR == pucIpcpBuf)
        {
            MN_ERR_LOG("MN_APS_PppCovertConfigInfo:  ERROR : PS_MEM_ALLOC Error!");

            /* 释放上面已分配的内存 */
            if ( VOS_NULL_PTR != pucPapBuf )
            {
                PS_MEM_FREE(WUEPS_PID_TAF, pucPapBuf);
            }
            if ( VOS_NULL_PTR != pucChallengeBuf )
            {
                PS_MEM_FREE(WUEPS_PID_TAF, pucChallengeBuf);
            }
            if ( VOS_NULL_PTR != pucResponseBuf )
            {
                PS_MEM_FREE(WUEPS_PID_TAF, pucResponseBuf);
            }
            return VOS_ERR;
        }

        /* 将数组中数据复制到指针结构中 */
        PS_MEM_CPY(pucIpcpBuf, pstPppAtReqConfigInfo->stIPCP.aucIpcp,
                   usIpcpLen);

        pstPppReqConfigInfo->stIPCP.usIpcpLen = usIpcpLen;
        pstPppReqConfigInfo->stIPCP.pIpcp     = pucIpcpBuf;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : MN_APS_RcvPppDialOrigReq
 功能描述  : 处理ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息
 输入参数  : ucPdpId            - APS实体索引
             pstPppDialParaInfo - PPP拨号参数
 输出参数  : 无
 返 回 值  : TAF_PS_CAUSE_ENUM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年10月30日
    作    者   : f00179208
    修改内容   : DTS2012102901833:PPP拨号后导致内存泄露

  3.日    期   : 2014年5月16日
    作    者   : A00165503
    修改内容   : DTS2014050703206: 调整PPP拨号流程实现
*****************************************************************************/
TAF_PS_CAUSE_ENUM_UINT32 MN_APS_RcvPppDialOrigReq(
    VOS_UINT8                           ucPdpId,
    TAF_PPP_DIAL_PARA_STRU             *pstPppDialParaInfo
)
{
    PPP_REQ_CONFIG_INFO_STRU            stPppConfigInfo;
    TAF_PDP_ADDR_STRU                   stPdpAddr;
    TAF_PDP_APN_STRU                    stApn;
    TAF_PS_CAUSE_ENUM_UINT32            enRet;
    VOS_UINT8                           ucCid;

    enRet = TAF_PS_CAUSE_SUCCESS;
    ucCid = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    PS_MEM_SET(&stPppConfigInfo, 0x00, sizeof(PPP_REQ_CONFIG_INFO_STRU));
    PS_MEM_SET(&stPdpAddr, 0x00, sizeof(TAF_PDP_ADDR_STRU));
    PS_MEM_SET(&stApn, 0x00, sizeof(TAF_PDP_APN_STRU));

    if (TAF_PDP_PPP != TAF_APS_GetTafCidInfoPdpType(ucCid))
    {
        /* 转换鉴权参数 */
        if (VOS_OK == MN_APS_PppCovertConfigInfo(&stPppConfigInfo,
                                                 &pstPppDialParaInfo->stPppReqConfigInfo))
        {
            if (TAF_PS_PARA_VALID == Taf_PsCallForDialParaCheck(&stPppConfigInfo))
            {
                stPdpAddr.enPdpType = TAF_PDP_IPV4;
                if (TAF_PDP_IPV4 == TAF_APS_GetTafCidInfoPdpType(ucCid))
                {
                    PS_MEM_CPY(stPdpAddr.aucIpv4Addr,
                               TAF_APS_GetTafCidInfoPdpIpv4Addr(ucCid),
                               TAF_IPV4_ADDR_LEN);
                }

                stApn.ucLength = TAF_APS_GetTafCidInfoApnLen(ucCid);;
                PS_MEM_CPY(stApn.aucValue,
                           TAF_APS_GetTafCidInfoApnData(ucCid),
                           TAF_MAX_APN_LEN);

                enRet = TAF_APS_PsCallForDial(ucPdpId,
                                              &stPdpAddr,
                                              &stApn,
                                              &stPppConfigInfo);
            }
            else
            {
                MN_WARN_LOG("MN_APS_RcvPppDialOrigReq: Check PPP config info failed!");
                enRet = TAF_PS_CAUSE_INVALID_PARAMETER;
            }
        }
        else
        {
            enRet = TAF_PS_CAUSE_UNKNOWN;
        }

        /* 释放生成的鉴权信息 */
        MN_APS_CtrlFreePCOContext(&stPppConfigInfo);
    }
    else
    {
        enRet = TAF_APS_PsCallOrig(ucPdpId);
    }

    return enRet;
}

/*****************************************************************************
 Prototype      : TAF_APS_PsCallOrig()
 Description    : PDP激活.该函数接收API输入的参数，根据这些参数和PDP全局变量
                  数据表中的参数判断应该发起激活还是二次激活，然后将该参数和
                  PDP全局变量数据表中的参数适配成Aps_PdpMdfReq()函数要求的接
                  口参数,然后调用函数Aps_PdpMdfReq(),发起激活或二次激活;
 Input          : ucPdpId
 Output         : pucError,若函数执行失败，此参数输出出错的错误类型
 Return Value   :
 Data Access    : g_PdpEntity
 Data update    :
 Calls          : Aps_ActJudgePriOrSecAct()
                  Aps_PdpActReq()
                  Aps_PdpSecActReq()
 Called By      : TAFM
 History        : ---
  1.Date        : 2005-
    Author      : 韩鲁峰
    Modification: Created function

  2.日    期   : 2014年5月16日
    作    者   : A00165503
    修改内容   : DTS2014050703206: 调整呼叫发起流程实现, 与CID上下文参数解耦
*****************************************************************************/
TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_PsCallOrig(VOS_UINT8 ucPdpId)
{
    VOS_UINT8                           ucCid;

    /*初始化*/
    ucCid = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /*CID定义了,则按定义的参数进行激活*/
    return Aps_PsCallOrigNormCid(ucCid, ucPdpId);
}

/*****************************************************************************
 Prototype      : Aps_ActJudgePriOrSecAct()
 Description    : APP主动发起激活时，用此函数根据该CID的PDP全局数据表中的定义,
                  决定发起主激活还是二次激活.
                  主叫发起二次激活,则主激活必须已经得到了ADDR、APN参数，即主激活
                  必须不能处于INACTIVE状态.但这个主状态的检查不在此函数中进行了，
                  而在二次激活的函数中检查。

                  有两种情况，
                  1.当前没有激活任何PDP，但AT发起的激活要求激活全
                  部CID，此时,定义的主PDP没有问题，可以激活,但定义的二次PDP的主
                  PDP此时还没有激活，发二次激活的话，核心网肯定拒绝，所以对这种
                  情况下的定义的二次PDP，就拒绝激活;因为此时用户也知道某些二次
                  激活的主激活还没有激活，不能激活二次激活.
                  2.当前激活了部分PDP，AT要求发起某个二次PDP的激活,就检查该PDP
                  的主PDP是否已经激活,激活了，就正常发起二次激活,此时核心网能够
                  正确处理二次激活;若该二次激活的主PDP没有激活,则该定义的二次PDP
                  不能发起二次激活;
 Input          :
 Output         : pucResult,  #define APS_PRI_ACT         1 - 主激活,
                              #define APS_SEC_ACT         2 - 二次激活,
                  pucPriPdpId,如果是二次激活,此指针指向的PdpId被赋值为主激活的
                  PdpId,[0,6][8,14];如果是主激活,此指针指向的PdpId被赋值为0xFF
                              #define   APS_INVALID_PDPID   0xFF
 Return Value   :
 Data Accessed  : PDP全局数据表g_TafCidTab[TAF_MAX_CID + 1];
 Data Updated   :
 Calls          :
 Called By      : TAF_APS_PsCallOrig()
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID  Aps_ActJudgePriOrSecAct (
    VOS_UINT8                           ucCid,
    VOS_UINT8                          *pucResult
)
{
    /*在此函数外部检查该CID是否定义过*/
    if ( 0 == ucCid)
    {
        /*主叫主激活*/
        *pucResult                      = APS_PRI_ACT;
        return;
    }

    if( APS_PDP_TABLE_PARA_INVALID      == g_TafCidTab[ucCid].ucPriCidFlag )
    {
        /*主叫主激活*/
        *pucResult                      = APS_PRI_ACT;
    }
    else
    {
        /*二次激活*/
        *pucResult                      = APS_SEC_ACT;
    }
    return ;
}

/*****************************************************************************
 函 数 名  : TAF_APS_FillPapParam
 功能描述  : 填充PS域呼叫的PAP鉴权参数, 用户名和密码长度合法性由调用者保证
 输入参数  : pucUserName   - 用户名信息
             usUserNameLen - 用户名长度
             pucPassWord   - 密码信息
             usPassWordLen - 密码长度
 输出参数  : pstAuthParam  - 鉴权信息
 返 回 值  : VOS_OK        - 成功
             VOS_ERR       - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月18日
    作    者   : l00198894
    修改内容   : DTS2012121709304: 修改+CGACT拨号命令鉴权类型配置命令为^AUTHDATA
*****************************************************************************/
VOS_UINT32 TAF_APS_FillPapParam(
    TAF_PDP_PCO_AUTH_STRU              *pstAuthParam,
    VOS_UINT8                          *pucUserName,
    VOS_UINT16                          usUserNameLen,
    VOS_UINT8                          *pucPassWord,
    VOS_UINT16                          usPassWordLen
)
{
    /* 设置鉴权类型 */
    pstAuthParam->AuthType = TAF_PCO_AUTH_PAP;

    pstAuthParam->AuthContent.stPap.aucUserName[0] = (VOS_UINT8)usUserNameLen;

    PS_MEM_CPY(&pstAuthParam->AuthContent.stPap.aucUserName[1],
               pucUserName,
               usUserNameLen + 1);

    pstAuthParam->AuthContent.stPap.aucPassword[0] = (VOS_UINT8)usPassWordLen;

    PS_MEM_CPY(&pstAuthParam->AuthContent.stPap.aucPassword[1],
               pucPassWord,
               usPassWordLen + 1);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_APS_FillChapParam
 功能描述  : 生成并填充PS域呼叫的CHAP鉴权参数, 用户名和密码长度合法性由调用
             者保证
 输入参数  : pucUserName   - 用户名信息
             usUserNameLen - 用户名长度
             pucPassWord   - 密码信息
             usPassWordLen - 密码长度
 输出参数  : pstAuthParam  - 鉴权信息
 返 回 值  : VOS_OK        - 成功
             VOS_ERR       - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月18日
    作    者   : l00198894
    修改内容   : DTS2012121709304: 修改+CGACT拨号命令鉴权类型配置命令为^AUTHDATA
*****************************************************************************/
VOS_UINT32 TAF_APS_FillChapParam(
    TAF_PDP_PCO_AUTH_STRU              *pstAuthParam,
    VOS_UINT8                          *pucUserName,
    VOS_UINT16                          usUserNameLen,
    VOS_UINT8                          *pucPassWord,
    VOS_UINT16                          usPassWordLen
)
{
    TAF_PSCALL_FOR_DIAL_EXT_STRU        stPsDilaParam;
    PPP_REQ_CONFIG_INFO_STRU            stPppConfigInfo;

    PS_MEM_SET(&stPppConfigInfo, 0, sizeof(stPppConfigInfo));
    PS_MEM_SET(&stPsDilaParam, 0, sizeof(stPsDilaParam));

    /* 根据鉴权类型生成鉴权信息 */
    stPppConfigInfo.stAuth.ucAuthType = PPP_CHAP_AUTH_TYPE;

    if (VOS_OK != MN_APS_CtrlMakePCOChapAuthInfo(&stPppConfigInfo,
                                                 pucUserName,
                                                 usUserNameLen,
                                                 pucPassWord,
                                                 usPassWordLen))
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_FillChapParam: Generate challenge param failed.\n");
        return VOS_ERR;
    }

    /* 从IPCP的码流中拆出REQ的AUTH信息码流, 并填到stPsDilaParam中 */
    if (TAF_APS_FAIL == Aps_GetAuthInfo(&stPppConfigInfo, &stPsDilaParam))
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_FillChapParam: Get auth info failed.\n");
        return VOS_ERR;
    }

    /* 若输入了鉴权信息, 则使用输入的鉴权信息*/
    Aps_CopyAuthToActReqPara(&stPsDilaParam.AuthPara,
                             pstAuthParam);

    /* 释放生成的鉴权信息 */
    MN_APS_CtrlFreePCOContext(&stPppConfigInfo);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_APS_FillAuthParamFromProfile
 功能描述  : 根据Profile信息填充PS域呼叫鉴权参数
 输入参数  : pstAuthParam       - 鉴权参数
             pstAuthProfileInfo - 鉴权Profile信息
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月18日
    作    者   : l00198894
    修改内容   : DTS2012121709304: 修改+CGACT拨号命令鉴权类型配置命令为^AUTHDATA
*****************************************************************************/
VOS_UINT32 TAF_APS_FillAuthParamFromProfile(
    TAF_PDP_PCO_AUTH_STRU              *pstAuthParam,
    TAF_NDIS_AUTHDATA_TABLE_STRU       *pstAuthProfileInfo
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usUserNameLen;
    VOS_UINT16                          usPassWordLen;

    /* 计算用户名和密码长度 */
    usUserNameLen = (VOS_UINT16)VOS_StrLen((VOS_CHAR *)pstAuthProfileInfo->stAuthData.aucUsername);
    usPassWordLen = (VOS_UINT16)VOS_StrLen((VOS_CHAR *)pstAuthProfileInfo->stAuthData.aucPassword);

    /* 检查用户名和密码的长度是否合法 */
    if ( (usUserNameLen > TAF_MAX_USERNAME_LEN)
      || (usPassWordLen > TAF_MAX_PASSCODE_LEN) )
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_FillAuthParamFromProfile: Username or password is too long.\n");
        return VOS_ERR;
    }

    if ((VOS_FALSE != pstAuthProfileInfo->ucUsed) && (0 != usUserNameLen))
    {
        switch (pstAuthProfileInfo->stAuthData.enAuthType)
        {
            case TAF_PDP_AUTH_TYPE_PAP:
                ulRslt = TAF_APS_FillPapParam(pstAuthParam,
                                              pstAuthProfileInfo->stAuthData.aucUsername,
                                              usUserNameLen,
                                              pstAuthProfileInfo->stAuthData.aucPassword,
                                              usPassWordLen);
                break;

            case TAF_PDP_AUTH_TYPE_CHAP:
            case TAF_PDP_AUTH_TYPE_PAP_OR_CHAP:
                ulRslt = TAF_APS_FillChapParam(pstAuthParam,
                                               pstAuthProfileInfo->stAuthData.aucUsername,
                                               usUserNameLen,
                                               pstAuthProfileInfo->stAuthData.aucPassword,
                                               usPassWordLen);
                break;

            default:
                ulRslt = VOS_ERR;
                break;
        }
    }
    else
    {
        ulRslt = VOS_ERR;
    }

    return ulRslt;
}

/*****************************************************************************
 Prototype      : Aps_PackApsActReqPara
 Description    : 构造并输出函数Aps_PdpActReq()需要的输入参数;对应V100R001中的
                  Taf_FillApsPdp(),有所修改.
 Input          : ucCid
                  ucPdpId
 Output         : pApsActReq
 Return Value   :
 Data Accessed  : PDP全局数据表g_TafCidTab[TAF_MAX_CID + 1];
 Data Updated   :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
  2.日    期   : 2012年12月18日
    作    者   : l00198894
    修改内容   : DTS2012121709304: 修改+CGACT拨号命令鉴权类型配置命令为^AUTHDATA
*****************************************************************************/
VOS_UINT32  Aps_PackApsActReqPara (
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPdpId,
    APS_PDP_ACT_REQ_ST                 *pApsActReq
)
{
    TAF_PDP_TABLE_STRU                 *pTafPdp;

    TAF_NDIS_AUTHDATA_TABLE_STRU       *pstAuthProfileInfo;

    /*入口参数检查;*/
    if ( VOS_NULL == pApsActReq )
    {
        APS_WARN_LOG("VOS_NULL == pApsActReq ");
        return  TAF_APS_FAIL;
    }

    pstAuthProfileInfo              = &g_ApsNdisAuthdataTab[ucCid];

    pTafPdp                         = &g_TafCidTab[ucCid];

    pApsActReq->OP_APN              = VOS_FALSE;
    pApsActReq->OP_AUTH             = VOS_FALSE;
    pApsActReq->OP_DNS              = VOS_FALSE;
    pApsActReq->OP_NBNS             = VOS_FALSE;
    pApsActReq->OP_Sapi             = VOS_FALSE;
    pApsActReq->Op_Xid_DCmp         = VOS_FALSE;
    pApsActReq->Op_Xid_PCmp         = VOS_FALSE;
    pApsActReq->OP_SPARE            = VOS_FALSE;
    pApsActReq->ucPdpId             = ucPdpId;

    /*V200专用*/
    pApsActReq->OP_Sapi             = VOS_TRUE;
    pApsActReq->ucSapi              = APS_SAPI_INIT;

    if ( 0 == ucCid )
    {
        /*动态IPV4类型*/
        Aps_CopyAddrToActReqPara(   pTafPdp->CidTab.stPdpAddr.aucIpv4Addr,
                                    pApsActReq  );
    }
    else
    {
        /*处理ucPdpType,aucIpAddr*/
        switch(pTafPdp->CidTab.stPdpAddr.enPdpType)
        {
            /*PPP类型*/
            case TAF_PDP_PPP:
                pApsActReq->ucPdpType   = APS_ADDR_PPP;
                break;

            case TAF_PDP_IPV4:
                Aps_CopyAddrToActReqPara( pTafPdp->CidTab.stPdpAddr.aucIpv4Addr,
                                          pApsActReq  );
                break;

#if (FEATURE_ON == FEATURE_IPV6)
            case TAF_PDP_IPV6:
                pApsActReq->ucPdpType   = MN_APS_ADDR_IPV6;
                break;

            case TAF_PDP_IPV4V6:
                pApsActReq->ucPdpType   = MN_APS_ADDR_IPV4V6;
                break;
#endif

            default:
                APS_WARN_LOG("TAF_APS_GetPsReqPdp:PdpType is error.\r");
                return TAF_APS_FAIL;
        }
    }


    /*AUTH*/
    if ( 0 != ucCid )
    {
        if ( APS_ADDR_PPP != pApsActReq->ucPdpType )
        {
            if (VOS_OK == TAF_APS_FillAuthParamFromProfile(&pApsActReq->PdpAuth,
                                                           pstAuthProfileInfo))
            {
                pApsActReq->OP_AUTH = VOS_TRUE;
            }
            else
            {
                /*不鉴权*/
                pApsActReq->PdpAuth.AuthType = TAF_PCO_NOT_AUTH;
                PS_MEM_SET(&pApsActReq->PdpAuth.AuthContent, 0, sizeof(pApsActReq->PdpAuth.AuthContent));
            }
        }
    }

    /*aucApn*/
    if ( 0 != ucCid )
    {
        pApsActReq->OP_APN = 1;
        Taf_LenStr2Apn(&(pTafPdp->CidTab.stApn), pApsActReq->aucApn);
    }

    /*处理Qos*/
    Taf_FillQos(pTafPdp, &pApsActReq->ReqQos);

    /*处理XID*/
    Aps_FillXid(pTafPdp, pApsActReq);

    /*处理DNS*/
    Aps_FillDns(pTafPdp, pApsActReq);

    /*填充完毕，直接返回成功*/
    return TAF_APS_SUCC;

}

/*****************************************************************************
 Prototype      : Aps_CopyAuthToActReqPara
 Description    :
 Input          : pAuthTab
 Output         : pApsAuth
 Return Value   :
 Data Accessed  :
 Data Updated   :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID  Aps_CopyAuthToActReqPara(
    CONST TAF_PDP_PCO_AUTH_STRU        *pAuthTab,
    TAF_PDP_PCO_AUTH_STRU              *pActReqParaAuth
)
{
    /*拷贝用户名和密码*/
    PS_MEM_CPY(pActReqParaAuth, pAuthTab, sizeof(TAF_PDP_PCO_AUTH_STRU));
    return;
}

/*****************************************************************************
 Prototype      : Aps_CopyAddrToActReqPara
 Description    :
 Input          : pucIpAddr
 Output         : pApsActReq
 Return Value   :
 Data Accessed  :
 Data Updated   :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，结构替换
*****************************************************************************/
VOS_VOID  Aps_CopyAddrToActReqPara(
    CONST VOS_UINT8                    *pucIpAddr,
    APS_PDP_ACT_REQ_ST                 *pApsActReq
)
{
    /*静态IP，拷贝IP地址,目前静态IP地址只支持IPV4，最多拷贝4个字节*/
    PS_MEM_CPY(pApsActReq->aucIpAddr, pucIpAddr, TAF_IPV4_ADDR_LEN);

    if (  (0 == pApsActReq->aucIpAddr[0])
       && (0 == pApsActReq->aucIpAddr[1])
       && (0 == pApsActReq->aucIpAddr[2])
       && (0 == pApsActReq->aucIpAddr[3]) )
    {
        /*动态IP*/
        pApsActReq->ucPdpType   = APS_ADDR_DYNAMIC_IPV4;
    }
    else
    {
        /*静态IP*/
        pApsActReq->ucPdpType   = APS_ADDR_STATIC_IPV4;
    }

    return;
}

/*****************************************************************************
 函 数 名  : Aps_PsCallOrigNormCid
 功能描述  : 当PDP数据表已经定义，并且CID=[1,11]时调用此函数进行激活
 输入参数  : ucCid
             ucPdpId
 输出参数  : 无
 返 回 值  : TAF_PS_CAUSE_ENUM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005
    作    者   : ---
    修改内容   : 新生成函数

  2.日    期   : 2014年5月16日
    作    者   : A00165503
    修改内容   : DTS2014050703206: 调整函数返回值为PS域错误码
*****************************************************************************/
TAF_PS_CAUSE_ENUM_UINT32 Aps_PsCallOrigNormCid(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPdpId
)
{
    VOS_UINT32                          ulReturn;
    VOS_UINT8                           ucPriSecAct;
    APS_PDP_ACT_REQ_ST                  stApsActReq;
    APS_PDP_SEC_ACT_REQ_ST              stApsSecActReq;                           /*该变量的初始化在函数
                                                                                 Aps_PackApsSecActReqPara中完成                                                                             */
    ulReturn                            = TAF_SUCCESS;
    ucPriSecAct                         = APS_PRI_ACT;

    PS_MEM_SET(&stApsActReq, 0, sizeof(APS_PDP_ACT_REQ_ST));
    PS_MEM_SET(&stApsSecActReq, 0, sizeof(APS_PDP_SEC_ACT_REQ_ST));

    /*判断主激活还是二次激活*/
    Aps_ActJudgePriOrSecAct( ucCid, &ucPriSecAct);

    /*主激活*/
    if ( APS_PRI_ACT == ucPriSecAct )
    {
        /*打包激活所需参数*/
        ulReturn = Aps_PackApsActReqPara( ucCid, ucPdpId, &stApsActReq );
        if ( TAF_APS_FAIL == ulReturn )
        {
            APS_WARN_LOG("JudgePriOrSecAct err ");
            return TAF_PS_CAUSE_UNKNOWN;
        }

        /*激活*/
        ulReturn = Aps_PdpActReq( &stApsActReq );
        if ( TAF_APS_SUCC != ulReturn )
        {
            APS_WARN_LOG("Aps_PdpActReq err ");
            return TAF_PS_CAUSE_UNKNOWN;
        }
    }
    else  /*二次激活*/
    {
        /*打包二次激活所需参数*/
        ulReturn = Aps_PackApsSecActReqPara( ucCid, ucPdpId, &stApsSecActReq );
        if ( TAF_APS_FAIL == ulReturn )
        {
            APS_WARN_LOG("Aps_PackApsSecActReqPara err ");
            return TAF_PS_CAUSE_UNKNOWN;
        }

        /*二次激活*/
        ulReturn = Aps_PdpSecActReq( &stApsSecActReq );
        if ( TAF_APS_SUCC != ulReturn )
        {
            APS_WARN_LOG("Aps_PdpSecActReq err ");
            return TAF_PS_CAUSE_UNKNOWN;
        }
    }

    return TAF_PS_CAUSE_SUCCESS;
}



/*****************************************************************************
 函 数 名  : TAF_APS_PsCallForDial
 功能描述  : 发起PS域呼叫
 输入参数  : ucPdpId          --- APS实体索引
             pstApn           --- APN信息
             pstPppConfigInfo --- PPP配置信息
 输出参数  : 无
 返 回 值  : TAF_PS_CAUSE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月16日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_PsCallForDial(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_ADDR_STRU                  *pstPdpAddr,
    TAF_PDP_APN_STRU                   *pstApn,
    PPP_REQ_CONFIG_INFO_STRU           *pstPppConfigInfo
)
{
    TAF_PSCALL_FOR_DIAL_EXT_STRU        stDialParamExt;
    APS_PDP_ACT_REQ_ST                  stPdpActReq;
    VOS_UINT32                          ulReturn;

    PS_MEM_SET(&stDialParamExt, 0x00, sizeof(TAF_PSCALL_FOR_DIAL_EXT_STRU));
    PS_MEM_SET(&stPdpActReq, 0x00, sizeof(APS_PDP_ACT_REQ_ST));

    /* 构造呼叫参数: CID, PDP类型和APN信息 */
    stDialParamExt.ucCid   = TAF_APS_GetPdpEntCurrCid(ucPdpId);;
    stDialParamExt.PdpType = pstPdpAddr->enPdpType;

    PS_MEM_CPY(&(stDialParamExt.stApn), pstApn, sizeof(TAF_PDP_APN_STRU));
    PS_MEM_CPY(stDialParamExt.aucPdpAddr, pstPdpAddr->aucIpv4Addr, TAF_IPV4_ADDR_LEN);

    /* 从IPCP的码流中拆出REQ的IPCP信息码流, 并填到stDialParamExt中 */
    Aps_GetIpcpInfo(pstPppConfigInfo, &stDialParamExt);

    /* 从IPCP的码流中拆出REQ的AUTH信息码流, 并填到stPdpActReq中 */
    if (TAF_APS_FAIL == Aps_GetAuthInfo(pstPppConfigInfo, &stDialParamExt))
    {
        return TAF_PS_CAUSE_INVALID_PARAMETER;
    }

    /* 构造函数Aps_PdpActReq()需要的输入参数APS_PDP_ACT_REQ_ST */
    ulReturn = Aps_PackDialActReqPara(ucPdpId, &stDialParamExt, &stPdpActReq);
    if (ulReturn == TAF_APS_FAIL)
    {
        return TAF_PS_CAUSE_UNKNOWN;
    }

    /* 发起激活 */
    ulReturn = Aps_PdpActReq(&stPdpActReq);
    if (TAF_APS_FAIL == ulReturn)
    {
        return TAF_PS_CAUSE_UNKNOWN;
    }

    return TAF_PS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Prototype      : Aps_GetIpcpInfo()
 Description    :
 Input          : pPsCallDialPara
 Output         : pPsCallDial
 Return Value   :
 Data Accessed  :
 Data Updated   :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，结构替换

  3.日    期   : 2014年5月16日
    作    者   : A00165503
    修改内容   : DTS2014050703206: 去除IPCP报文中IP地址的提取
*****************************************************************************/
VOS_VOID Aps_GetIpcpInfo(
    PPP_REQ_CONFIG_INFO_STRU           *pPsDialPara,
    TAF_PSCALL_FOR_DIAL_EXT_STRU       *pApsDialReqPara
)
{
    APS_PCO_IPCP_PPP_ST                 IpcpPPP;
    APS_PCO_PPP_ST                      OnePppIpcp;
    APS_PPP_ID_ST                       OnePppId;

    APS_PDP_DNS_ST                      ApsDns;
    APS_PDP_NBNS_ST                     ApsNbns;
#if 0
    VOS_UINT8                           aucIpAddr[TAF_IPV4_ADDR_LEN];
#endif

    /*处理DNS标识*/
    pApsDialReqPara->OP_Dns                 = VOS_FALSE;
    pApsDialReqPara->Dns.bitOpPrimDnsAddr   = VOS_FALSE;
    pApsDialReqPara->Dns.bitOpSecDnsAddr    = VOS_FALSE;

    ApsDns.OP_PriDns                        = VOS_FALSE;
    ApsDns.OP_SecDns                        = VOS_FALSE;
    ApsDns.OP_Spare                         = VOS_FALSE;

    /*处理NBNS标识*/
    pApsDialReqPara->OP_Nbns                = VOS_FALSE;
    pApsDialReqPara->Nbns.bitOpPrimNbnsAddr = VOS_FALSE;
    pApsDialReqPara->Nbns.bitOpSecNbnsAddr  = VOS_FALSE;

    ApsNbns.OP_PriNbns                      = VOS_FALSE;
    ApsNbns.OP_SecNbns                      = VOS_FALSE;
    ApsNbns.OP_Spare                        = VOS_FALSE;

#if 0
    aucIpAddr[0]                            = 0;
    aucIpAddr[1]                            = 0;
    aucIpAddr[2]                            = 0;
    aucIpAddr[3]                            = 0;
#endif

    /*有IPCP码流，则向下操作*/
    IpcpPPP.usLen                           = pPsDialPara->stIPCP.usIpcpLen;
    IpcpPPP.pProtIdCont                     = pPsDialPara->stIPCP.pIpcp;

    if (0 == IpcpPPP.usLen)
    {
        return;
    }

    if ( TAF_APS_SUCC == Aps_CheckOutPcoOneIpcp(&IpcpPPP,
                                            APS_PPP_CODE_REQ,
                                            &OnePppIpcp))
    {
#if 0
        /*找出REQ码流中的IPADDR*/
        if ( TAF_APS_SUCC ==  Aps_CheckOutOneIpcpOneId(
                                        &OnePppIpcp,
                                        APS_PPP_IP_ADDR_ID,
                                        &OnePppId))
        {   /*成功则解析IP ADDR信息*/
            Aps_PPPAddr2ApsAddr(        (APS_PCO_PPP_ST*)&OnePppId,
                                        aucIpAddr);

            PS_MEM_CPY(pApsDialReqPara->aucPdpAddr, aucIpAddr, TAF_IPV4_ADDR_LEN);
        }
#endif

        /*找出REQ码流中的主DNS,填到输出变量中*/
        if ( TAF_APS_SUCC == Aps_CheckOutOneIpcpOneId(
                                        &OnePppIpcp,
                                        APS_PPP_PRI_DNS_ID,
                                        &OnePppId))
        {
            Aps_PPPDns2ApsDns(          (APS_PCO_PPP_ST*)&OnePppId,
                                        &ApsDns);
        }

        /*从REQ信息中拆出副DNS信息,填到输出变量中*/
        if ( TAF_APS_SUCC == Aps_CheckOutOneIpcpOneId(
                                        &OnePppIpcp,
                                        APS_PPP_SEC_DNS_ID,
                                        &OnePppId))
        {
            Aps_PPPDns2ApsDns(          (APS_PCO_PPP_ST*)&OnePppId,
                                        &ApsDns);
        }

        /*找出REQ码流中的主NBNS,填到输出变量中*/
        if ( TAF_APS_SUCC == Aps_CheckOutOneIpcpOneId(
                                        &OnePppIpcp,
                                        APS_PPP_PRI_NBNS_ID,
                                        &OnePppId))
        {
            Aps_PPPNbns2ApsNbns(          (APS_PCO_PPP_ST*)&OnePppId,
                                          &ApsNbns);
        }

        /*从REQ信息中拆出副NBNS信息,填到输出变量中*/
        if ( TAF_APS_SUCC == Aps_CheckOutOneIpcpOneId(
                                        &OnePppIpcp,
                                        APS_PPP_SEC_NBNS_ID,
                                        &OnePppId))
        {
            Aps_PPPNbns2ApsNbns(          (APS_PCO_PPP_ST*)&OnePppId,
                                          &ApsNbns);
        }
    }


    /*主DNS*/
    if (ApsDns.OP_PriDns)
    {
        /*处理DNS标识*/
        pApsDialReqPara->OP_Dns                 = VOS_TRUE;

        pApsDialReqPara->Dns.bitOpPrimDnsAddr   = VOS_TRUE;
        PS_MEM_CPY(pApsDialReqPara->Dns.aucPrimDnsAddr,
                   ApsDns.aucPriDns,
                   TAF_IPV4_ADDR_LEN);
    }
    else
    {
        pApsDialReqPara->Dns.bitOpPrimDnsAddr   = VOS_FALSE;
    }

    /*副DNS*/
    if (ApsDns.OP_SecDns)
    {
        /*处理DNS标识*/
        pApsDialReqPara->OP_Dns                 = VOS_TRUE;

        pApsDialReqPara->Dns.bitOpSecDnsAddr    = VOS_TRUE;
        PS_MEM_CPY(pApsDialReqPara->Dns.aucSecDnsAddr,
                   ApsDns.aucSecDns,
                   TAF_IPV4_ADDR_LEN);
    }
    else
    {
        pApsDialReqPara->Dns.bitOpSecDnsAddr    = VOS_FALSE;
    }

    /*主NBNS*/
    if (ApsNbns.OP_PriNbns)
    {
        /*处理NBNS标识*/
        pApsDialReqPara->OP_Nbns                = VOS_TRUE;

        pApsDialReqPara->Nbns.bitOpPrimNbnsAddr = VOS_TRUE;

        PS_MEM_CPY(pApsDialReqPara->Nbns.aucPrimNbnsAddr,
                   ApsNbns.aucPriNbns,
                   TAF_IPV4_ADDR_LEN);
    }
    else
    {
        pApsDialReqPara->Nbns.bitOpPrimNbnsAddr = VOS_FALSE;
    }

    /*副NBNS*/
    if (ApsNbns.OP_SecNbns)
    {
        /*处理NBNS标识*/
        pApsDialReqPara->OP_Nbns                = VOS_TRUE;

        pApsDialReqPara->Nbns.bitOpSecNbnsAddr  = VOS_TRUE;
        PS_MEM_CPY(pApsDialReqPara->Nbns.aucSecNbnsAddr,
                   ApsNbns.aucSecNbns,
                   TAF_IPV4_ADDR_LEN);
    }
    else
    {
        pApsDialReqPara->Nbns.bitOpSecNbnsAddr  = VOS_FALSE;
    }

    return;
}

/*****************************************************************************
 Prototype      : Aps_GetAuthInfo()
 Description    :
 Input          : pPsCallDialPara
 Output         : pPsCallDial
 Return Value   :
 Data Accessed  :
 Data Updated   :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  Aps_GetAuthInfo(            PPP_REQ_CONFIG_INFO_STRU   *pPsDialPara,
                                        TAF_PSCALL_FOR_DIAL_EXT_STRU *pApsDialReqPara)
{
    APS_PPP_ID_ST                       OnePppId;
    VOS_UINT8                           ucLoc = 0;
    TAF_PDP_PCO_AUTH_STRU               *pApsAuth;

    pApsAuth                            = &pApsDialReqPara->AuthPara;

    pApsDialReqPara->OP_Auth            = VOS_FALSE;
    pApsDialReqPara->AuthPara.AuthType  = TAF_PCO_NOT_AUTH;
    PS_MEM_SET(&pApsDialReqPara->AuthPara.AuthContent, 0, sizeof(pApsDialReqPara->AuthPara.AuthContent));

    if (PPP_PAP_AUTH_TYPE == pPsDialPara->stAuth.ucAuthType)
    {
        pApsDialReqPara->OP_Auth            = VOS_TRUE;
        pApsDialReqPara->AuthPara.AuthType  = TAF_PCO_AUTH_PAP;

        OnePppId.usLen                      = pPsDialPara->stAuth.AuthContent.PapContent.usPapReqLen;
        OnePppId.pProtIdCont                = pPsDialPara->stAuth.AuthContent.PapContent.pPapReq;

        /*鉴权的长度为0,则退出*/
        if (0 == OnePppId.usLen)
        {
            return  TAF_APS_SUCC;
        }

        ucLoc   += 4;                       /*跳过CODE1字节,Identifier1字节,长度2字节中的2个字节*/

        /*处理UserName*/
        if (OnePppId.pProtIdCont[ucLoc] > TAF_MAX_USERNAME_LEN)
        {
            return  TAF_APS_FAIL;
        }
        else
        {
        /*lint -e961*/
            pApsAuth->AuthContent.stPap.aucUserName[0]        = OnePppId.pProtIdCont[ucLoc++];
        /*lint +e961*/

            /*有UserName*/
            if (0 != pApsAuth->AuthContent.stPap.aucUserName[0])
            {
                PS_MEM_CPY(                 &pApsAuth->AuthContent.stPap.aucUserName[1],
                                            &OnePppId.pProtIdCont[ucLoc],
                                            pApsAuth->AuthContent.stPap.aucUserName[0]);
            }

            ucLoc += pApsAuth->AuthContent.stPap.aucUserName[0];              /*跳过USERNAME*/
        }

        /*处理PassWord*/
        if (OnePppId.pProtIdCont[ucLoc] > TAF_MAX_PASSCODE_LEN)
        {
            return  TAF_APS_FAIL;
        }
        else
        {
            /*lint -e961*/
            pApsAuth->AuthContent.stPap.aucPassword[0]        = OnePppId.pProtIdCont[ucLoc++];
            /*lint +e961*/
            PS_MEM_CPY(                     &pApsAuth->AuthContent.stPap.aucPassword[1],
                                            &OnePppId.pProtIdCont[ucLoc],
                                            pApsAuth->AuthContent.stPap.aucPassword[0]);
        }
    }
    else if(PPP_CHAP_AUTH_TYPE == pPsDialPara->stAuth.ucAuthType)
    {
        /*目前的实现中，必然要有challenge和response报文*/
        if ( (0 == pPsDialPara->stAuth.AuthContent.ChapContent.usChapChallengeLen)
             || (0 == pPsDialPara->stAuth.AuthContent.ChapContent.usChapResponseLen) )
        {
            return TAF_APS_FAIL;
        }

        pApsDialReqPara->OP_Auth            = VOS_TRUE;
        pApsDialReqPara->AuthPara.AuthType  = TAF_PCO_AUTH_CHAP;

        /*拷贝challenge 报文*/
        if ( TAF_PCO_CONTENT_MAX_LEN < pPsDialPara->stAuth.AuthContent.ChapContent.usChapChallengeLen )
        {
            pApsDialReqPara->AuthPara.AuthContent.stChap.aucChallenge[0] = TAF_PCO_CONTENT_MAX_LEN;
        }
        else
        {
            pApsDialReqPara->AuthPara.AuthContent.stChap.aucChallenge[0]
                   = (VOS_UINT8)pPsDialPara->stAuth.AuthContent.ChapContent.usChapChallengeLen;
        }

        PS_MEM_CPY( &pApsDialReqPara->AuthPara.AuthContent.stChap.aucChallenge[1],
                    pPsDialPara->stAuth.AuthContent.ChapContent.pChapChallenge,
                    pApsDialReqPara->AuthPara.AuthContent.stChap.aucChallenge[0]);

        /*拷贝response 报文*/
        if ( TAF_PCO_CONTENT_MAX_LEN < pPsDialPara->stAuth.AuthContent.ChapContent.usChapResponseLen )
        {
            pApsDialReqPara->AuthPara.AuthContent.stChap.aucResponse[0] = TAF_PCO_CONTENT_MAX_LEN;
        }
        else
        {
            pApsDialReqPara->AuthPara.AuthContent.stChap.aucResponse[0]
                   = (VOS_UINT8)pPsDialPara->stAuth.AuthContent.ChapContent.usChapResponseLen;
        }

        PS_MEM_CPY( &pApsDialReqPara->AuthPara.AuthContent.stChap.aucResponse[1],
                    pPsDialPara->stAuth.AuthContent.ChapContent.pChapResponse,
                    pApsDialReqPara->AuthPara.AuthContent.stChap.aucResponse[0]);
    }
    else
    {
        /*不鉴权*/
    }

    return  TAF_APS_SUCC;

}

/*****************************************************************************
 Prototype      : Aps_PackDialActReqPara()
 Description    : 拨号激活指定CID时,调用此函数构造激活函数Aps_PdpActReq()
                  所需要的激活输入参数.此函数适用于指定了CID的情况
 Input          : ucCid,
                  ucPdpId,
                  pPsCallDialPara,
 Output         : pAPS_PDP_ACT_REQ_ST
 Return Value   :
 Data Accessed  :
 Data Updated   :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005
    Author      : hanlufeng
    Modification: Created function

  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，结构替换

  3.日    期   : 2014年5月16日
    作    者   : A00165503
    修改内容   : DTS2014050703206: 调整呼叫发起流程实现, 与CID上下文参数解耦
*****************************************************************************/
VOS_UINT32  Aps_PackDialActReqPara(
    VOS_UINT8                           ucPdpId,
    TAF_PSCALL_FOR_DIAL_EXT_STRU       *pPsCallDial,
    APS_PDP_ACT_REQ_ST                 *pApsActReq
)
{
    TAF_PDP_TABLE_STRU                 *pTafPdp;

    pTafPdp                     = &g_TafCidTab[pPsCallDial->ucCid];

    /*SAPI*/
    pApsActReq->OP_Sapi         = VOS_TRUE;
    pApsActReq->ucSapi          = APS_SAPI_INIT;

    pApsActReq->ucPdpId         = ucPdpId;

    /*如果输入了PDP类型,填PDP类型和地址*/
    if (TAF_PDP_IPV4 == pPsCallDial->PdpType)
    {
        Aps_CopyAddrToActReqPara(pPsCallDial->aucPdpAddr,
                                 pApsActReq);
    }
#if (FEATURE_ON == FEATURE_IPV6)
    else if (TAF_PDP_IPV6 == pPsCallDial->PdpType)
    {
        /* IPV6类型的PDP激活请求, 不填写静态IP地址 */
        pApsActReq->ucPdpType   = MN_APS_ADDR_IPV6;
    }
    else if (TAF_PDP_IPV4V6 == pPsCallDial->PdpType)
    {
        /* IPV4V6类型的PDP激活请求, 不填写静态IP地址 */
        pApsActReq->ucPdpType   = MN_APS_ADDR_IPV4V6;
    }
#endif
    else
    {
        /*如果输入的是PPP类型*/
        pApsActReq->ucPdpType   = APS_ADDR_PPP;
    }

    /*处理aucApn*/
    pApsActReq->OP_APN          = VOS_TRUE;
    Taf_LenStr2Apn(&(pPsCallDial->stApn), pApsActReq->aucApn);

    /*处理ucUserAuthOrNot,aucUserName,aucPassword*/
    if (APS_ADDR_PPP != pApsActReq->ucPdpType)
    {
        if (VOS_TRUE == pPsCallDial->OP_Auth )
        {
            /*若输入了鉴权信息,则使用输入的鉴权信息*/
            pApsActReq->OP_AUTH = VOS_TRUE;
            Aps_CopyAuthToActReqPara(&(pPsCallDial->AuthPara),
                                     &(pApsActReq->PdpAuth));
        }
        else
        {
            /*不鉴权*/
            pApsActReq->OP_AUTH = VOS_FALSE;
        }
    }
    else
    {
        /*PPP型PDP不鉴权*/
        pApsActReq->OP_AUTH     = VOS_FALSE;
    }

    /*处理Qos*/
    Taf_FillQos(pTafPdp, &pApsActReq->ReqQos);

    /*处理XID*/
    Aps_FillXid(pTafPdp, pApsActReq);

    /*处理PdpDns*/
    if (APS_ADDR_PPP != pApsActReq->ucPdpType)
    {
        if (VOS_TRUE == pPsCallDial->OP_Dns)
        {
            /*如果输入了DNS,就使用输入的DNS*/
            pApsActReq->OP_DNS  = VOS_TRUE;
            pApsActReq->PdpDns  = pPsCallDial->Dns;
        }
        else
        {
            /*如果没有输入了DNS,就使用表中定义的DNS*/
            Aps_FillDns(pTafPdp, pApsActReq);
        }
    }
    else
    {
        /*PPP型PDP无DNS*/
        pApsActReq->OP_DNS      = VOS_FALSE;
    }

    /*处理PdpNbns*/
    if (APS_ADDR_PPP != pApsActReq->ucPdpType)
    {
        if (VOS_TRUE == pPsCallDial->OP_Nbns)
        {
            /*如果输入了NBNS,就使用输入的NBNS*/
            pApsActReq->OP_NBNS = VOS_TRUE;
            pApsActReq->PdpNbns = pPsCallDial->Nbns;
        }
        else
        {
            /*如果没有输入NBNS,就不使用NBNS*/
            pApsActReq->OP_NBNS = VOS_FALSE;
        }
    }
    else
    {
        /*PPP型PDP无DNS*/
        pApsActReq->OP_NBNS     = VOS_FALSE;
    }

    /*填充完毕，直接返回成功*/
    return  TAF_APS_SUCC;
}

/*****************************************************************************
 函 数 名  : Taf_FillQos_Set_MaximSduSize
 功能描述  : 解析Maximum SDU size (Taf_FillQos降圈复杂度)
 输入参数  : pTafPdp
 输出参数  : pApsQos
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  Taf_FillQos_Set_MaximSduSize(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    
    if (pTafPdp->QosTab.usMaxSduSize <= APS_APP_QOS_MAXSDUSIZE_1500OCTS)
    {
        pApsQos->ucMaximSduSize
            = (VOS_UINT8)(pTafPdp->QosTab.usMaxSduSize / APS_3GPP_QOS_MAXSDUSIZE_GRANUL_10);
    }
    else
    {
        if (APS_APP_QOS_MAXSDUSIZE_1502OCTS == pTafPdp->QosTab.usMaxSduSize)
        {
            pApsQos->ucMaximSduSize = APS_3GPP_QOS_MAXSDUSIZE_1502OCTS;
        }
        else
        {
            if (APS_APP_QOS_MAXSDUSIZE_1510OCTS == pTafPdp->QosTab.usMaxSduSize)
            {
                pApsQos->ucMaximSduSize = APS_3GPP_QOS_MAXSDUSIZE_1510OCTS;
            }
            else
            {
                if (APS_APP_QOS_MAXSDUSIZE_1520OCTS == pTafPdp->QosTab.usMaxSduSize)
                {
                    pApsQos->ucMaximSduSize = APS_3GPP_QOS_MAXSDUSIZE_1520OCTS;
                }
                else
                {
                    pApsQos->ucMaximSduSize = APS_3GPP_QOS_MAXSDUSIZE_SUB;
                }
            }
        }
    }

}

/*****************************************************************************
 函 数 名  : Taf_FillQos_Set_MaxBitRateForUp
 功能描述  : 解析Maximum bit rate for uplink (Taf_FillQos降圈复杂度)
 输入参数  : pTafPdp
 输出参数  : pApsQos
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  Taf_FillQos_Set_MaxBitRateForUp(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    /*  Maximum bit rate for uplink, octet 8:
        In MS to network direction:
        0 0 0 0 0 0 0 0 Subscribed maximum bit rate for uplink
        In network to MS direction:
        0 0 0 0 0 0 0 0 Reserved

        In MS to network direction and in network to MS direction:
        0 0 0 0 0 0 0 1 The maximum bit rate is binary coded in 8 bits, using a granularity of 1 kbps
        0 0 1 1 1 1 1 1 giving a range of values from 1 kbps to 63 kbps in 1 kbps increments.

        0 1 0 0 0 0 0 0 The maximum bit rate is 64 kbps + ((the binary coded value in 8 bits -01000000) * 8 kbps)
        0 1 1 1 1 1 1 1 giving a range of values from 64 kbps to 568 kbps in 8 kbps increments.

        1 0 0 0 0 0 0 0 The maximum bit rate is 576 kbps + ((the binary coded value in 8 bits -10000000) * 64 kbps)
        1 1 1 1 1 1 1 0 giving a range of values from 576 kbps to 8640 kbps in 64 kbps increments.

        1 1 1 1 1 1 1 1 0kbps


        Maximum bit rate for uplink (extended), octet 17
        Bits
        8 7 6 5 4 3 2 1
        In MS to network direction and in network to MS direction:
        0 0 0 0 0 0 0 0 Use the value indicated by the Maximum bit rate for uplink in octet 8.

                        For all other values: Ignore the value indicated by the Maximum bit rate for uplink in octet 8
                        and use the following value:
        0 0 0 0 0 0 0 1 The maximum bit rate is 8600 kbps + ((the binary coded value in 8 bits) * 100 kbps),
        0 1 0 0 1 0 1 0 giving a range of values from 8700 kbps to 16000 kbps in 100 kbps increments.

        0 1 0 0 1 0 1 1 The maximum bit rate is 16 Mbps + ((the binary coded value in 8 bits - 01001010) * 1 Mbps),
        1 0 1 1 1 0 1 0 giving a range of values from 17 Mbps to 128 Mbps in 1 Mbps increments.

        1 0 1 1 1 0 1 1 The maximum bit rate is 128 Mbps + ((the binary coded value in 8 bits - 10111010) * 2 Mbps),
        1 1 1 1 1 0 1 0 giving a range of values from 130 Mbps to 256 Mbps in 2 Mbps increments.

        The network shall map all other values not explicitly defined onto one of the values defined in this version of the protocol.
        The network shall return a negotiated value which is explicitly defined in this version of the protocol
    */

    #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
    pApsQos->ucMaxBitRateForUpExt = 0;
    #endif

    if (pTafPdp->QosTab.ulMaxBitUl <= 63)
    {
        pApsQos->ucMaxBitRateForUp   = (VOS_UINT8)pTafPdp->QosTab.ulMaxBitUl;
    }
    else
    {
        if (pTafPdp->QosTab.ulMaxBitUl <= 568)
        {
            pApsQos->ucMaxBitRateForUp = (VOS_UINT8)(((pTafPdp->QosTab.ulMaxBitUl - 64) / 8) + 64);
        }
        else
        {
            if (pTafPdp->QosTab.ulMaxBitUl < 576)
            {
                pApsQos->ucMaxBitRateForUp = 127;  /*0 1 1 1 1 1 1 1*/
            }
            else
            {
                if (pTafPdp->QosTab.ulMaxBitUl <= 8640)
                {
                    pApsQos->ucMaxBitRateForUp = (VOS_UINT8)(((pTafPdp->QosTab.ulMaxBitUl - 576) / 64) + 128);
                }
                else
                {
                    #if(PS_UE_REL_VER < PS_PTL_VER_R7)
                    pApsQos->ucMaxBitRateForUp = 254;  /*1 1 1 1 1 1 1 0*/
                    #else
                    /* If the sending entity wants to indicate a Maximum bit rate for uplink
                          higher than 8640 kbps, it shall set octet 8 to "11111110",
                          i.e. 8640 kbps, and shall encode the value for the Maximum bit rate in octet 17 */
                    if (pTafPdp->QosTab.ulMaxBitUl < 8700)
                    {
                        pApsQos->ucMaxBitRateForUp = 254;  /*1 1 1 1 1 1 1 0*/
                    }
                    else
                    {
                        pApsQos->ucMaxBitRateForUp = 254;
                        if (pTafPdp->QosTab.ulMaxBitUl <= 16000)
                        {
                            pApsQos->ucMaxBitRateForUpExt
                                = (VOS_UINT8)((pTafPdp->QosTab.ulMaxBitUl - 8600) / 100);
                        }
                        else if (pTafPdp->QosTab.ulMaxBitUl <= 128000)
                        {
                            pApsQos->ucMaxBitRateForUpExt
                                = (VOS_UINT8)(((pTafPdp->QosTab.ulMaxBitUl - 16000) / 1000) + 74);
                        }
                        else if (pTafPdp->QosTab.ulMaxBitUl <= 256000)
                        {
                            pApsQos->ucMaxBitRateForUpExt
                                = (VOS_UINT8)(((pTafPdp->QosTab.ulMaxBitUl - 128000) / 2000) + 186);
                        }
                        else
                        {
                            pApsQos->ucMaxBitRateForUpExt = 250;  /*1 1 1 1 1 0 1 0*/
                        }
                    }
                    #endif
                }
            }
        }
    }

}

/*****************************************************************************
 函 数 名  : Taf_FillQos_Set_MaxBitRateForDown
 功能描述  : 解析Maximum bit rate for downlink (Taf_FillQos降圈复杂度)
 输入参数  : pTafPdp
 输出参数  : pApsQos
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  Taf_FillQos_Set_MaxBitRateForDown(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    #if(PS_UE_REL_VER >= PS_PTL_VER_R5)
    pApsQos->ucMaxBitRateForDownExt = 0;
    #endif

    if (pTafPdp->QosTab.ulMaxBitDl <= 63)
    {
        pApsQos->ucMaxBitRateForDown   = (VOS_UINT8)pTafPdp->QosTab.ulMaxBitDl;
    }
    else
    {
        if (pTafPdp->QosTab.ulMaxBitDl <= 568)
        {
            pApsQos->ucMaxBitRateForDown = (VOS_UINT8)(((pTafPdp->QosTab.ulMaxBitDl - 64) / 8) + 64);
        }
        else
        {
            if (pTafPdp->QosTab.ulMaxBitDl < 576)
            {
                pApsQos->ucMaxBitRateForDown = 127;  /*0 1 1 1 1 1 1 1*/
            }
            else
            {
                if (pTafPdp->QosTab.ulMaxBitDl <= 8640)
                {
                    pApsQos->ucMaxBitRateForDown = (VOS_UINT8)(((pTafPdp->QosTab.ulMaxBitDl - 576) / 64) + 128);
                }
                else
                {
                    #if(PS_UE_REL_VER < PS_PTL_VER_R5)
                    pApsQos->ucMaxBitRateForDown = 254;  /*1 1 1 1 1 1 1 0*/
                    #else
                    /* If the sending entity wants to indicate a Maximum bit rate for downlink */
                    /* higher than 8640 kbps, it shall set octet 9 to "11111110", i.e. 8640 kbps, */
                    /* and shall encode the value for the Maximum bit rate in octet 15. */
                    if (pTafPdp->QosTab.ulMaxBitDl < 8700)
                    {
                        pApsQos->ucMaxBitRateForDown = 254;  /*1 1 1 1 1 1 1 0*/
                    }
                    else
                    {
                        pApsQos->ucMaxBitRateForDown = 254;

                        if (pTafPdp->QosTab.ulMaxBitDl <= 16000)
                        {
                            pApsQos->ucMaxBitRateForDownExt
                                = (VOS_UINT8)((pTafPdp->QosTab.ulMaxBitDl - 8600) / 100);
                        }
                        #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
                        else if (pTafPdp->QosTab.ulMaxBitDl <= 128000)
                        {
                            pApsQos->ucMaxBitRateForDownExt
                                = (VOS_UINT8)(((pTafPdp->QosTab.ulMaxBitDl - 16000) / 1000) + 74);
                        }
                        else if (pTafPdp->QosTab.ulMaxBitDl <= 256000)
                        {
                            pApsQos->ucMaxBitRateForDownExt
                                = (VOS_UINT8)(((pTafPdp->QosTab.ulMaxBitDl - 128000) / 2000) + 186);
                        }
                        #endif
                        else
                        {
                            #if(PS_UE_REL_VER < PS_PTL_VER_R7)
                            pApsQos->ucMaxBitRateForDownExt = 74;   /*0 1 0 0 1 0 1 0*/
                            #else
                            pApsQos->ucMaxBitRateForDownExt = 250;  /*1 1 1 1 1 0 1 0*/
                            #endif
                        }
                    }
                    #endif
                }
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : Taf_FillQos_Set_TransDelay
 功能描述  : 解析Transfer delay (Taf_FillQos降圈复杂度)
 输入参数  : pTafPdp
 输出参数  : pApsQos
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  Taf_FillQos_Set_TransDelay(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    /*
    In MS to network direction:
    0 0 0 0 0 0     Subscribed transfer delay
    In network to MS direction:
    0 0 0 0 0 0     Reserved
    In MS to network direction and in network to MS direction:

    0 0 0 0 0 1     The Transfer delay is binary coded in 6 bits, using a granularity of 10 ms
    0 0 1 1 1 1     giving a range of values from 10 ms to 150 ms in 10 ms increments

    0 1 0 0 0 0     The transfer delay is 200 ms + ((the binary coded value in 6 bits - 010000) * 50 ms)
    0 1 1 1 1 1     giving a range of values from 200 ms to 950 ms in 50ms increments

    1 0 0 0 0 0     The transfer delay is 1000 ms + ((the binary coded value in 6 bits - 100000) * 100 ms)
    1 1 1 1 1 0     giving a range of values from 1000 ms to 4000 ms in 100ms increments

    1 1 1 1 1 1     Reserved
    */
    if (pTafPdp->QosTab.usTransDelay <= 150)
    {
        pApsQos->ucTransDelay = (VOS_UINT8)(pTafPdp->QosTab.usTransDelay / 10);
    }
    else
    {
        if (pTafPdp->QosTab.usTransDelay < 200)
        {
            pApsQos->ucTransDelay = 15;
        }
        else
        {
            if (pTafPdp->QosTab.usTransDelay <= 950)
            {

                pApsQos->ucTransDelay = (VOS_UINT8)(((pTafPdp->QosTab.usTransDelay - 200) / 50) + 16);
            }
            else
            {
                if (pTafPdp->QosTab.usTransDelay < 1000)
                {
                    pApsQos->ucTransDelay = 31;
                }
                else
                {
                    if (pTafPdp->QosTab.usTransDelay <= 4000)
                    {
                        pApsQos->ucTransDelay = (VOS_UINT8)(((pTafPdp->QosTab.usTransDelay - 1000) / 100) + 32);
                    }
                    else
                    {
                        pApsQos->ucTransDelay = 62;
                    }
                }

            }
        }
    }

}

/*****************************************************************************
 函 数 名  : Taf_FillQos_Set_GuarantBitRateForUp
 功能描述  : 解析Guaranteed bit rate for uplink(Taf_FillQos降圈复杂度)
 输入参数  : pTafPdp
 输出参数  : pApsQos
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  Taf_FillQos_Set_GuarantBitRateForUp(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    /* Guaranteed bit rate for uplink, octet 12:
        In MS to network direction:
        0 0 0 0 0 0 0 0 Subscribed Guaranteed bit rate for uplink
        In network to MS direction:
        0 0 0 0 0 0 0 0 Reserved

        In MS to network direction and in network to MS direction:
        0 0 0 0 0 0 0 1 The Guaranteed bit rate is binary coded in 8 bits, using a granularity of 1 kbps
        0 0 1 1 1 1 1 1 giving a range of values from 1 kbps to 63 kbps in 1 kbps increments.

        0 1 0 0 0 0 0 0 The Guaranteed bit rate is 64 kbps + ((the binary coded value in 8 bits -01000000) * 8 kbps)
        0 1 1 1 1 1 1 1 giving a range of values from 64 kbps to 568 kbps in 8 kbps increments.

        1 0 0 0 0 0 0 0 The Guaranteed bit rate is 576 kbps + ((the binary coded value in 8 bits -10000000) * 64 kbps)
        1 1 1 1 1 1 1 0 giving a range of values from 576 kbps to 8640 kbps in 64 kbps increments.

        1 1 1 1 1 1 1 1 0kbps

        Guaranteed bit rate for uplink (extended), octet 17
        Bits
        8 7 6 5 4 3 2 1
        In MS to network direction and in network to MS direction:
        0 0 0 0 0 0 0 0 Use the value indicated by the Guaranteed bit rate for uplink in octet 12.

                        For all other values: Ignore the value indicated by the Guaranteed bit rate for uplink in octet 12
                        and use the following value:
        0 0 0 0 0 0 0 1 The Guaranteed bit rate is 8600 kbps + ((the binary coded value in 8 bits) * 100 kbps),
        0 1 0 0 1 0 1 0 giving a range of values from 8700 kbps to 16000 kbps in 100 kbps increments.

        0 1 0 0 1 0 1 1 The Guaranteed bit rate is 16 Mbps + ((the binary coded value in 8 bits - 01001010) * 1 Mbps),
        1 0 1 1 1 0 1 0 giving a range of values from 17 Mbps to 128 Mbps in 1 Mbps increments.

        1 0 1 1 1 0 1 1 The Guaranteed bit rate is 128 Mbps + ((the binary coded value in 8 bits - 10111010) * 2 Mbps),
        1 1 1 1 1 0 1 0 giving a range of values from 130 Mbps to 256 Mbps in 2 Mbps increments.

        The network shall map all other values not explicitly defined onto one of the values defined in this version of the protocol.
        The network shall return a negotiated value which is explicitly defined in this version of the protocol

    */

    #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
    pApsQos->ucGuarantBitRateForUpExt = 0;
    #endif

    if (pTafPdp->QosTab.ulGuarantBitUl <= 63)
    {
        pApsQos->ucGuarantBitRateForUp   = (VOS_UINT8)pTafPdp->QosTab.ulGuarantBitUl;
    }
    else
    {
        if (pTafPdp->QosTab.ulGuarantBitUl <= 568)
        {
            pApsQos->ucGuarantBitRateForUp = (VOS_UINT8)(((pTafPdp->QosTab.ulGuarantBitUl - 64) / 8) + 64);
        }
        else
        {
            if (pTafPdp->QosTab.ulGuarantBitUl < 576)
            {
                pApsQos->ucGuarantBitRateForUp = 127;  /*0 1 1 1 1 1 1 1*/
            }
            else
            {
                if (pTafPdp->QosTab.ulGuarantBitUl <= 8640)
                {
                    pApsQos->ucGuarantBitRateForUp = (VOS_UINT8)(((pTafPdp->QosTab.ulGuarantBitUl - 576) / 64) + 128);
                }
                else
                {
                    #if(PS_UE_REL_VER < PS_PTL_VER_R7)
                    pApsQos->ucGuarantBitRateForUp = 254;  /*1 1 1 1 1 1 1 0*/
                    #else
                    /* If the sending entity wants to indicate a Guaranteed bit rate for uplink
                          higher than 8640 kbps, it shall set octet 8 to "11111110",
                          i.e. 8640 kbps, and shall encode the value for the Guaranteed bit rate in octet 18 */
                    if (pTafPdp->QosTab.ulGuarantBitUl < 8700)
                    {
                        pApsQos->ucGuarantBitRateForUp = 254;  /*1 1 1 1 1 1 1 0*/
                    }
                    else
                    {
                        pApsQos->ucGuarantBitRateForUp = 254;
                        if (pTafPdp->QosTab.ulGuarantBitUl <= 16000)
                        {
                            pApsQos->ucGuarantBitRateForUpExt
                                = (VOS_UINT8)((pTafPdp->QosTab.ulGuarantBitUl - 8600) / 100);
                        }
                        else if (pTafPdp->QosTab.ulGuarantBitUl <= 128000)
                        {
                            pApsQos->ucGuarantBitRateForUpExt
                                = (VOS_UINT8)(((pTafPdp->QosTab.ulGuarantBitUl - 16000) / 1000) + 74);
                        }
                        else if (pTafPdp->QosTab.ulGuarantBitUl <= 256000)
                        {
                            pApsQos->ucGuarantBitRateForUpExt
                                = (VOS_UINT8)(((pTafPdp->QosTab.ulGuarantBitUl - 128000) / 2000) + 186);
                        }
                        else
                        {
                            pApsQos->ucGuarantBitRateForUpExt = 250;  /*1 1 1 1 1 0 1 0*/
                        }
                    }
                    #endif
                }
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : Taf_FillQos_Set_GuarantBitRateForDown
 功能描述  : 解析Guaranteed bit rate for downlink(Taf_FillQos降圈复杂度)
 输入参数  : pTafPdp
 输出参数  : pApsQos
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  Taf_FillQos_Set_GuarantBitRateForDown(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    #if(PS_UE_REL_VER >= PS_PTL_VER_R5)
    pApsQos->ucGuarantBitRateForDownExt = 0;
    #endif

    if (pTafPdp->QosTab.ulGuarantBitDl <= 63)
    {
        pApsQos->ucGuarantBitRateForDown   = (VOS_UINT8)pTafPdp->QosTab.ulGuarantBitDl;
    }
    else
    {
        if (pTafPdp->QosTab.ulGuarantBitDl <= 568)
        {
            pApsQos->ucGuarantBitRateForDown = (VOS_UINT8)(((pTafPdp->QosTab.ulGuarantBitDl - 64) / 8) + 64);
        }
        else
        {
            if (pTafPdp->QosTab.ulGuarantBitDl < 576)
            {
                pApsQos->ucGuarantBitRateForDown = 127;  /*0 1 1 1 1 1 1 1*/
            }
            else
            {
                if (pTafPdp->QosTab.ulGuarantBitDl <= 8640)
                {
                    pApsQos->ucGuarantBitRateForDown = (VOS_UINT8)(((pTafPdp->QosTab.ulGuarantBitDl - 576) / 64) + 128);
                }
                else
                {
                    #if(PS_UE_REL_VER < PS_PTL_VER_R5)
                    pApsQos->ucGuarantBitRateForDown = 254;  /*1 1 1 1 1 1 1 0*/
                    #else
                    /* If the sending entity wants to indicate a Guaranteed bit rate for downlink */
                    /* higher than 8640 kbps, it shall set octet 9 to "11111110", i.e. 8640 kbps, */
                    /* and shall encode the value for the Guaranteed bit rate in octet 16. */
                    if (pTafPdp->QosTab.ulGuarantBitDl < 8700)
                    {
                        pApsQos->ucGuarantBitRateForDown = 254;  /*1 1 1 1 1 1 1 0*/
                    }
                    else
                    {
                        pApsQos->ucGuarantBitRateForDown = 254;

                        if (pTafPdp->QosTab.ulGuarantBitDl <= 16000)
                        {
                            pApsQos->ucGuarantBitRateForDownExt
                                = (VOS_UINT8)((pTafPdp->QosTab.ulGuarantBitDl - 8600) / 100);
                        }
                        #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
                        else if (pTafPdp->QosTab.ulGuarantBitDl <= 128000)
                        {
                            pApsQos->ucGuarantBitRateForDownExt
                                = (VOS_UINT8)(((pTafPdp->QosTab.ulGuarantBitDl - 16000) / 1000) + 74);
                        }
                        else if (pTafPdp->QosTab.ulGuarantBitDl <= 256000)
                        {
                            pApsQos->ucGuarantBitRateForDownExt
                                = (VOS_UINT8)(((pTafPdp->QosTab.ulGuarantBitDl - 128000) / 2000) + 186);
                        }
                        #endif
                        else
                        {
                            #if(PS_UE_REL_VER < PS_PTL_VER_R7)
                            pApsQos->ucGuarantBitRateForDownExt = 74;   /*0 1 0 0 1 0 1 0*/
                            #else
                            pApsQos->ucGuarantBitRateForDownExt = 250;  /*1 1 1 1 1 0 1 0*/
                            #endif
                        }
                    }
                    #endif
                }
            }
        }
    }

}

/*****************************************************************************
 函 数 名  : Taf_FillQos_Set_DelayClass
 功能描述  : 解析Delay class(Taf_FillQos降圈复杂度)
 输入参数  : pTafPdp
 输出参数  : pApsQos
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  Taf_FillQos_Set_DelayClass(
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    switch(pApsQos->ucTrafficClass)
    {
        case    APS_QOS_TRAFFIC_CLASS_CONVERSATIONAL    :
        case    APS_QOS_TRAFFIC_CLASS_STREAMING     :
            pApsQos->ucDelayClass           = 1;
            break;

        case    APS_QOS_TRAFFIC_CLASS_INTERACTIVE   :
            switch(pApsQos->ucTraffHandlPrior)
            {
                case    APS_QOS_TRAFFF_HANDL_PRIOR_1    :
                    pApsQos->ucDelayClass   = 1;
                    break;

                case    APS_QOS_TRAFFF_HANDL_PRIOR_2    :
                    pApsQos->ucDelayClass   = 2;
                    break;

                case    APS_QOS_TRAFFF_HANDL_PRIOR_3    :
                    pApsQos->ucDelayClass   = 3;
                    break;

                default :
                    pApsQos->ucDelayClass   = 0;
                    break;
            }
            break;

        case    APS_QOS_TRAFFIC_CLASS_BACKGROUND    :
            pApsQos->ucDelayClass           = 4;
            break;

        default :
            pApsQos->ucDelayClass           = 0;
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : Taf_FillQos_Set_ReliabClass
 功能描述  : 解析Reliable class(Taf_FillQos降圈复杂度)
 输入参数  : pTafPdp
 输出参数  : pApsQos
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  Taf_FillQos_Set_ReliabClass(
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    switch(pApsQos->ucSduErrRatio)
    {
        case    APS_QOS_SDU_ERR_RATIO_1EM5  :
        case    APS_QOS_SDU_ERR_RATIO_1EM6  :
        case    APS_QOS_SDU_ERR_RATIO_1EM10 :
            pApsQos->ucReliabClass          = 2;
            break;

        case    APS_QOS_SDU_ERR_RATIO_1EM4  :
            pApsQos->ucReliabClass          = 3;
            break;

        case    APS_QOS_SDU_ERR_RATIO_1EM2  :
        case    APS_QOS_SDU_ERR_RATIO_7EM3  :
        case    APS_QOS_SDU_ERR_RATIO_1EM3  :
            if ( pApsQos->ucResidualBer >= APS_QOS_RESIDUAL_BER_1EM4)
            {
                pApsQos->ucReliabClass      = 4;
            }
            else
            {
                pApsQos->ucReliabClass      = 5;
            }
            break;

        default:
            pApsQos->ucReliabClass          = 0;
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : Taf_FillQos_Set_PeakThrough
 功能描述  : 解析Peak Throughput(Taf_FillQos降圈复杂度)
 输入参数  : pTafPdp
 输出参数  : pApsQos
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  Taf_FillQos_Set_PeakThrough(
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    if ( pApsQos->ucMaxBitRateForUp == APS_QOS_MAX_BITRATE_SUBSCRIBE)
    {
        pApsQos->ucPeakThrough              = 0;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_16KBPS )
    {
        pApsQos->ucPeakThrough              = 1;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_32KBPS )
    {
        pApsQos->ucPeakThrough              = 2;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_64KBPS )
    {
        pApsQos->ucPeakThrough              = 3;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_128KBPS )
    {
        pApsQos->ucPeakThrough              = 4;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_256KBPS )
    {
        pApsQos->ucPeakThrough              = 5;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_512KBPS )
    {
        pApsQos->ucPeakThrough              = 6;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_1024KBPS )
    {
        pApsQos->ucPeakThrough              = 7;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_2048KBPS )
    {
        pApsQos->ucPeakThrough              = 8;
    }
    else if ( pApsQos->ucMaxBitRateForUp == APS_QOS_MAX_BITRATE_0KBPS )
    {
        pApsQos->ucPeakThrough              = 1;
    }
    else
    {
        pApsQos->ucPeakThrough              = 9;
    }

    return;
}

/*****************************************************************************
 函 数 名  : Taf_FillQos_Set_SrcStatisticsDescriptor
 功能描述  : 解析Source Statistics Descriptor(Taf_FillQos降圈复杂度)
 输入参数  : pstTafPdp  --指向的值不会改变，指向const的指针
 输出参数  : pstApsQos
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月7日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  Taf_FillQos_Set_SrcStatisticsDescriptor(
    const TAF_PDP_TABLE_STRU            *pstTafPdp,
    APS_PDP_QOS_STRU                    *pstApsQos
)
{
    if ((APS_3GPP_QOS_TRAFFIC_CLASS_INTERACTIVE     != pstApsQos->ucTrafficClass)
     && (APS_3GPP_QOS_TRAFFIC_CLASS_BACKGROUND      != pstApsQos->ucTrafficClass))
    {
        pstApsQos->ucSrcStatisticsDescriptor  = pstTafPdp->QosTab.ucSrcStatisticsDescriptor;
    }
    else
    {
        pstApsQos->ucSrcStatisticsDescriptor  = 0;    /*目前默认填写为0*/
    }

    return;
}

/*****************************************************************************
 函 数 名  : Taf_FillQos_Set_SignallingIndication
 功能描述  : 解析Signalling Indication(Taf_FillQos降圈复杂度)
 输入参数  : pTafPdp    --指向的值不会改变，指向const的指针
 输出参数  : pApsQos
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月7日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  Taf_FillQos_Set_SignallingIndication(
    const TAF_PDP_TABLE_STRU            *pstTafPdp,
    APS_PDP_QOS_STRU                    *pstApsQos
)
{
    if ( (APS_3GPP_QOS_TRAFFIC_CLASS_CONVERSATIONAL  != pstApsQos->ucTrafficClass)
      && (APS_3GPP_QOS_TRAFFIC_CLASS_STREAMING       != pstApsQos->ucTrafficClass)
      && (APS_3GPP_QOS_TRAFFIC_CLASS_BACKGROUND      != pstApsQos->ucTrafficClass))
    {
        pstApsQos->ucSignallingIndication     = pstTafPdp->QosTab.ucSignallingIndication;

        if ( 1 == pstApsQos->ucSignallingIndication)
        {
            pstApsQos->ucTraffHandlPrior      = 1;
        }
    }
    else
    {
        pstApsQos->ucSignallingIndication     = 0;    /*目前默认填写为0*/
    }

    return;
}


/*****************************************************************************
 函 数 名  : Taf_FillQos_QosTab_Used
 功能描述  : Taf_FillQos降复杂度 :  QOS 表有效的处理
 输入参数  : pTafPdp
 输出参数  : pApsQos
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数
  2.日    期   : 2015年4月7日
    作    者   : w00316404
    修改内容   : M project A characeristic AT part

*****************************************************************************/
VOS_VOID  Taf_FillQos_QosTab_Used(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    /*前5项是APP/AT不能设置的，直接赋值为由网络决定*/
    /*这5项的赋值放在QOS赋值的最后进行赋值*/
    /*
    pApsQos->ucDelayClass            = 0;   / *0: Subscribed value* /
    pApsQos->ucReliabClass           = 0;   / *0: subscribed value* /
    pApsQos->ucPeakThrough           = 0;   / *0: Subscribed value* /
    pApsQos->ucPrecedenceClass       = 0;   / *0: Subscribed value* /
    pApsQos->ucMeanThrough           = 0;   / *0: Subscribed value* /
    */

    /*AT协议中取值含义与24008中定义不相同，在此做转化 */
    /*
    In MS to network direction:
    0 0 0       Subscribed traffic class
    In network to MS direction:
    0 0 0       Reserved
    In MS to network direction and in network to MS direction:
    0 0 1       Conversational class
    0 1 0       Streaming class
    0 1 1       Interactive class
    1 0 0       Background class
    1 1 1       Reserved
    */
    if (pTafPdp->QosTab.ucTrafficClass >= APS_APP_QOS_TRAFFICCLASS_TOP)
    {
        pApsQos->ucTrafficClass = APS_3GPP_QOS_TRAFFIC_CLASS_SUBSCRIBE;
    }
    else
    {
        pApsQos->ucTrafficClass
            = pTafPdp->QosTab.ucTrafficClass
              + APS_TRAFFICCLASS_APP3GPP_DIFF_VAL;
    }

    /*
    In MS to network direction:
    0 0     Subscribed delivery order
    In network to MS direction:
    0 0     Reserved
    In MS to network direction and in network to MS direction:
    0 1     With delivery order ('yes')
    1 0     Without delivery order ('no')
    1 1     Reserved
    */
    if (pTafPdp->QosTab.ucDeliverOrder <= APS_APP_QOS_DELIVERORDER_TOP)
    {
        pApsQos->ucDeliverOrder
            = APS_DELIVERORDER_APP3GPP_DIFF_VAL
              - pTafPdp->QosTab.ucDeliverOrder;
    }
    else
    {
        pApsQos->ucDeliverOrder = APS_3GPP_QOS_DELIVERORDER_SUB;
    }

    /*
    In MS to network direction:
    0 0 0       Subscribed delivery of erroneous SDUs
    In network to MS direction:
    0 0 0       Reserved
    In MS to network direction and in network to MS direction:
    0 0 1       No detect ('-')
    0 1 0       Erroneous SDUs are delivered ('yes')
    0 1 1       Erroneous SDUs are not delivered ('no')
    1 1 1       Reserved
    */
    if (pTafPdp->QosTab.ucDeliverErrSdu <= APS_APP_QOS_DELIVER_ERRSDU_TOP)
    {
        pApsQos->ucDeliverOfErrSdu
            = APS_DELIVEROFERRSDU_APP3GPP_DIFF_VAL
              - pTafPdp->QosTab.ucDeliverErrSdu;
    }
    else
    {
        pApsQos->ucDeliverOfErrSdu = APS_3GPP_QOS_DELIVER_ERRSDU_SUB;
    }

    Taf_FillQos_Set_MaximSduSize(pTafPdp, pApsQos);

    Taf_FillQos_Set_MaxBitRateForUp(pTafPdp, pApsQos);

    Taf_FillQos_Set_MaxBitRateForDown(pTafPdp, pApsQos);

    /*
    In network to MS direction:
    0 0 0 0     Reserved
    In MS to network direction and in network to MS direction:
    The Residual BER value consists of 4 bits. The range is from 5*10-2 to 6*10-8.
    0 0 0 1     5*10-2
    0 0 1 0     1*10-2
    0 0 1 1     5*10-3
    0 1 0 0     4*10-3
    0 1 0 1     1*10-3
    0 1 1 0     1*10-4
    0 1 1 1     1*10-5
    1 0 0 0     1*10-6
    1 0 0 1     6*10-8
    1 1 1 1     Reserved
    */
    pApsQos->ucResidualBer           = pTafPdp->QosTab.ucResidualBer;

    /*
    In MS to network direction:
    0 0 0 0     Subscribed SDU error ratio
    In network to MS direction:
    0 0 0 0     Reserved
    In MS to network direction and in network to MS direction:
    The SDU error ratio value consists of 4 bits. The range is is from 1*10-1 to 1*10-6.
    0 0 0 1     1*10-2
    0 0 1 0     7*10-3
    0 0 1 1     1*10-3
    0 1 0 0     1*10-4
    0 1 0 1     1*10-5
    0 1 1 0     1*10-6
    0 1 1 1     1*10-1
    1 1 1 1     Reserved
    */
    pApsQos->ucSduErrRatio           = pTafPdp->QosTab.ucSduErrRatio;

    Taf_FillQos_Set_TransDelay(pTafPdp, pApsQos);

    /*
    In MS to network direction:
    0 0     Subscribed traffic handling priority
    In network to MS direction:
    0 0     Reserved
    In MS to network direction and in network to MS direction:
    0 1     Priority level 1
    1 0     Priority level 2
    1 1     Priority level 3
    */
    pApsQos->ucTraffHandlPrior       = pTafPdp->QosTab.ucTraffHandlePrior;

    Taf_FillQos_Set_GuarantBitRateForUp(pTafPdp, pApsQos);

    Taf_FillQos_Set_GuarantBitRateForDown(pTafPdp, pApsQos);

    #if(PS_UE_REL_VER >= PS_PTL_VER_R5)
    Taf_FillQos_Set_SrcStatisticsDescriptor(pTafPdp, pApsQos);
    Taf_FillQos_Set_SignallingIndication(pTafPdp, pApsQos);
    #endif

    return;
}

/*****************************************************************************
 Function:       Taf_FillQos
 Description:    根据Qos表中APP设定的值，转化为24008中定义的值.完全继承V100R001
 Calls:
 Data Accessed:
 Data Updated:
 Input:          pTafPdp - TAF CID表中的PDP信息
 Output:         pApsQos - APS需要的Qos取值
 Return:
 Others:
******************************************************************************/
VOS_VOID  Taf_FillQos(  TAF_PDP_TABLE_STRU         *pTafPdp,
                        APS_PDP_QOS_STRU           *pApsQos   )
{

    if (TAF_USED == pTafPdp->ucQosTabFlag)
    {   /*Qos表有效*/
        Taf_FillQos_QosTab_Used(pTafPdp, pApsQos);
    }
    else
    {   /*Qos表无效，置为网络决定取值*/
        /*
        pApsQos->ucDelayClass               = 0;    / *0: Subscribed value* /
        pApsQos->ucReliabClass              = 0;    / *0: Subscribed value* /
        pApsQos->ucPeakThrough              = 0;    / *0: Subscribed value* /
        pApsQos->ucPrecedenceClass          = 0;    / *0: Subscribed value* /
        pApsQos->ucMeanThrough              = 0;    / *0: Subscribed value* /
        */
        pApsQos->ucTrafficClass             = 0;    /*0: Subscribed value*/
        pApsQos->ucDeliverOrder             = 0;    /*0: Subscribed value*/
        pApsQos->ucDeliverOfErrSdu          = 0;    /*0: Subscribed value*/
        pApsQos->ucMaximSduSize             = 0;    /*0: Subscribed value*/
        pApsQos->ucMaxBitRateForUp          = 0;    /*0: Subscribed value*/
        pApsQos->ucMaxBitRateForDown        = 0;    /*0: Subscribed value*/
        pApsQos->ucResidualBer              = 0;    /*0: Subscribed value*/
        pApsQos->ucSduErrRatio              = 0;    /*0: Subscribed value*/
        pApsQos->ucTransDelay               = 0;    /*0: Subscribed value*/
        pApsQos->ucTraffHandlPrior          = 0;    /*0: Subscribed value*/
        pApsQos->ucGuarantBitRateForUp      = 0;    /*0: Subscribed value*/
        pApsQos->ucGuarantBitRateForDown    = 0;    /*0: Subscribed value*/
        #if(PS_UE_REL_VER >= PS_PTL_VER_R5)
        pApsQos->ucSrcStatisticsDescriptor  = 0;    /*0: unknown*/
        pApsQos->ucSignallingIndication     = 0;    /*0: Not optimised for signalling traffic*/
        pApsQos->ucMaxBitRateForDownExt     = 0;
        pApsQos->ucGuarantBitRateForDownExt = 0;
        #endif
        #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
        pApsQos->ucMaxBitRateForUpExt       = 0;
        pApsQos->ucGuarantBitRateForUpExt   = 0;
        #endif
    }

    /*根据Traffic class确定DelayClass */
    Taf_FillQos_Set_DelayClass(pApsQos);

    /*根据SDU error ratio和Residual bit error ratio确定ucReliabClass*/
    Taf_FillQos_Set_ReliabClass(pApsQos);

    /*根据Maximum bitrate确定ucPeakThrough*/
    Taf_FillQos_Set_PeakThrough(pApsQos);

    /*As the allocation/retention priority attribute is not available in the UE
    (see 6.4.4.1) the UE shall set the R97/98 precedence class attribute to the
    value "subscribed"*/
    pApsQos->ucPrecedenceClass              = 0;

    /*Mean throughput*/
    pApsQos->ucMeanThrough                  = g_ucMeanThrough;

    return;
}

/*****************************************************************************
 函 数 名  : Taf_FillMinQos_Set_MaximSduSize
 功能描述  : 解析maximum SDU size(Taf_FillMinQos降圈复杂度)
 输入参数  : pTafPdp
 输出参数  : pApsQos
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  Taf_FillMinQos_Set_MaximSduSize(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    
    if (pTafPdp->MinQosTab.usMaxSduSize <= 1500)
    {
        pApsQos->ucMaximSduSize      = (VOS_UINT8)(pTafPdp->MinQosTab.usMaxSduSize / 10);
    }
    else
    {
        if (1502 == pTafPdp->MinQosTab.usMaxSduSize)
        {
            pApsQos->ucMaximSduSize = 151;
        }
        else
        {
            if (1510 == pTafPdp->MinQosTab.usMaxSduSize)
            {
                pApsQos->ucMaximSduSize = 152;
            }
            else
            {
                if (1520 == pTafPdp->MinQosTab.usMaxSduSize)
                {
                    pApsQos->ucMaximSduSize = 153;
                }
                else
                {
                    pApsQos->ucMaximSduSize = 0;
                }
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : Taf_FillMinQos_Set_MaxBitRateForUp
 功能描述  : 解析maximum bit rate for uplink(Taf_FillMinQos降圈复杂度)
 输入参数  : pTafPdp
 输出参数  : pApsQos
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  Taf_FillMinQos_Set_MaxBitRateForUp(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    /*  In MS to network direction:
        0 0 0 0 0 0 0 0 Subscribed maximum bit rate for uplink
        In network to MS direction:
        0 0 0 0 0 0 0 0 Reserved

        In MS to network direction and in network to MS direction:
        0 0 0 0 0 0 0 1 The maximum bit rate is binary coded in 8 bits, using a granularity of 1 kbps
        0 0 1 1 1 1 1 1 giving a range of values from 1 kbps to 63 kbps in 1 kbps increments.

        0 1 0 0 0 0 0 0 The maximum bit rate is 64 kbps + ((the binary coded value in 8 bits -01000000) * 8 kbps)
        0 1 1 1 1 1 1 1 giving a range of values from 64 kbps to 568 kbps in 8 kbps increments.

        1 0 0 0 0 0 0 0 The maximum bit rate is 576 kbps + ((the binary coded value in 8 bits -10000000) * 64 kbps)
        1 1 1 1 1 1 1 0 giving a range of values from 576 kbps to 8640 kbps in 64 kbps increments.

        1 1 1 1 1 1 1 1 0kbps


        Maximum bit rate for uplink (extended), octet 17
        Bits
        8 7 6 5 4 3 2 1
        In MS to network direction and in network to MS direction:
        0 0 0 0 0 0 0 0 Use the value indicated by the Maximum bit rate for uplink in octet 8.

                        For all other values: Ignore the value indicated by the Maximum bit rate for uplink in octet 8
                        and use the following value:
        0 0 0 0 0 0 0 1 The maximum bit rate is 8600 kbps + ((the binary coded value in 8 bits) * 100 kbps),
        0 1 0 0 1 0 1 0 giving a range of values from 8700 kbps to 16000 kbps in 100 kbps increments.

        0 1 0 0 1 0 1 1 The maximum bit rate is 16 Mbps + ((the binary coded value in 8 bits - 01001010) * 1 Mbps),
        1 0 1 1 1 0 1 0 giving a range of values from 17 Mbps to 128 Mbps in 1 Mbps increments.

        1 0 1 1 1 0 1 1 The maximum bit rate is 128 Mbps + ((the binary coded value in 8 bits - 10111010) * 2 Mbps),
        1 1 1 1 1 0 1 0 giving a range of values from 130 Mbps to 256 Mbps in 2 Mbps increments.

        The network shall map all other values not explicitly defined onto one of the values defined in this version of the protocol.
        The network shall return a negotiated value which is explicitly defined in this version of the protocol

    */

    #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
    pApsQos->ucMaxBitRateForUpExt = 0;
    #endif

    if (pTafPdp->MinQosTab.ulMaxBitUl <= 63)
    {
        pApsQos->ucMaxBitRateForUp   = (VOS_UINT8)pTafPdp->MinQosTab.ulMaxBitUl;
    }
    else
    {
        if (pTafPdp->MinQosTab.ulMaxBitUl <= 568)
        {
            pApsQos->ucMaxBitRateForUp = (VOS_UINT8)(((pTafPdp->MinQosTab.ulMaxBitUl - 64) / 8) + 64);
        }
        else
        {
            if (pTafPdp->MinQosTab.ulMaxBitUl < 576)
            {
                pApsQos->ucMaxBitRateForUp = 127;  /*0 1 1 1 1 1 1 1*/
            }
            else
            {
                if (pTafPdp->MinQosTab.ulMaxBitUl <= 8640)
                {
                    pApsQos->ucMaxBitRateForUp = (VOS_UINT8)(((pTafPdp->MinQosTab.ulMaxBitUl - 576) / 64) + 128);
                }
                else
                {
                    #if(PS_UE_REL_VER < PS_PTL_VER_R7)
                    pApsQos->ucMaxBitRateForUp = 254;  /*1 1 1 1 1 1 1 0*/
                    #else
                    /* If the sending entity wants to indicate a Maximum bit rate for uplink
                          higher than 8640 kbps, it shall set octet 8 to "11111110",
                          i.e. 8640 kbps, and shall encode the value for the Maximum bit rate in octet 17 */
                    if (pTafPdp->MinQosTab.ulMaxBitUl < 8700)
                    {
                        pApsQos->ucMaxBitRateForUp = 254;  /*1 1 1 1 1 1 1 0*/
                    }
                    else
                    {
                        pApsQos->ucMaxBitRateForUp = 254;
                        if (pTafPdp->MinQosTab.ulMaxBitUl <= 16000)
                        {
                            pApsQos->ucMaxBitRateForUpExt
                                = (VOS_UINT8)((pTafPdp->MinQosTab.ulMaxBitUl - 8600) / 100);
                        }
                        else if (pTafPdp->MinQosTab.ulMaxBitUl <= 128000)
                        {
                            pApsQos->ucMaxBitRateForUpExt
                                = (VOS_UINT8)(((pTafPdp->MinQosTab.ulMaxBitUl - 16000) / 1000) + 74);
                        }
                        else if (pTafPdp->MinQosTab.ulMaxBitUl <= 256000)
                        {
                            pApsQos->ucMaxBitRateForUpExt
                                = (VOS_UINT8)(((pTafPdp->MinQosTab.ulMaxBitUl - 128000) / 2000) + 186);
                        }
                        else
                        {
                            pApsQos->ucMaxBitRateForUpExt = 250;  /*1 1 1 1 1 0 1 0*/
                        }
                    }
                    #endif
                }
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : Taf_FillMinQos_Set_MaxBitRateForDown
 功能描述  : 解析maximum bit rate for downlink(Taf_FillMinQos降圈复杂度)
 输入参数  : pTafPdp
 输出参数  : pApsQos
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  Taf_FillMinQos_Set_MaxBitRateForDown(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    #if(PS_UE_REL_VER >= PS_PTL_VER_R5)
    pApsQos->ucMaxBitRateForDownExt = 0;
    #endif

    if (pTafPdp->MinQosTab.ulMaxBitDl <= 63)
    {
        pApsQos->ucMaxBitRateForDown   = (VOS_UINT8)pTafPdp->MinQosTab.ulMaxBitDl;
    }
    else
    {
        if (pTafPdp->MinQosTab.ulMaxBitDl <= 568)
        {
            pApsQos->ucMaxBitRateForDown = (VOS_UINT8)(((pTafPdp->MinQosTab.ulMaxBitDl - 64) / 8) + 64);
        }
        else
        {
            if (pTafPdp->MinQosTab.ulMaxBitDl < 576)
            {
                pApsQos->ucMaxBitRateForDown = 127;  /*0 1 1 1 1 1 1 1*/
            }
            else
            {
                if (pTafPdp->MinQosTab.ulMaxBitDl <= 8640)
                {
                    pApsQos->ucMaxBitRateForDown = (VOS_UINT8)(((pTafPdp->MinQosTab.ulMaxBitDl - 576) / 64) + 128);
                }
                else
                {
                    #if(PS_UE_REL_VER < PS_PTL_VER_R5)
                    pApsQos->ucMaxBitRateForDown = 254;  /*1 1 1 1 1 1 1 0*/
                    #else
                    if (pTafPdp->MinQosTab.ulMaxBitDl < 8700)
                    {
                        pApsQos->ucMaxBitRateForDown = 254;  /*1 1 1 1 1 1 1 0*/
                    }
                    else
                    {
                        pApsQos->ucMaxBitRateForDown = 254;

                        if (pTafPdp->MinQosTab.ulMaxBitDl <= 16000)
                        {
                            pApsQos->ucMaxBitRateForDownExt
                                = (VOS_UINT8)((pTafPdp->MinQosTab.ulMaxBitDl - 8600) / 100);
                        }
                        #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
                        else if (pTafPdp->MinQosTab.ulMaxBitDl <= 128000)
                        {
                            pApsQos->ucMaxBitRateForDownExt
                                = (VOS_UINT8)(((pTafPdp->MinQosTab.ulMaxBitDl - 16000) / 1000) + 74);
                        }
                        else if (pTafPdp->MinQosTab.ulMaxBitDl <= 256000)
                        {
                            pApsQos->ucMaxBitRateForDownExt
                                = (VOS_UINT8)(((pTafPdp->MinQosTab.ulMaxBitDl - 128000) / 2000) + 186);
                        }
                        #endif
                        else
                        {
                            #if(PS_UE_REL_VER < PS_PTL_VER_R7)
                            pApsQos->ucMaxBitRateForDownExt = 74;   /*0 1 0 0 1 0 1 0*/
                            #else
                            pApsQos->ucMaxBitRateForDownExt = 250;  /*1 1 1 1 1 0 1 0*/
                            #endif
                        }
                    }
                    #endif
                }
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : Taf_FillMinQos_Set_TransDelay
 功能描述  : 解析transfer delay(Taf_FillMinQos降圈复杂度)
 输入参数  : pTafPdp
 输出参数  : pApsQos
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  Taf_FillMinQos_Set_TransDelay(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    /*
    In MS to network direction:
    0 0 0 0 0 0     Subscribed transfer delay
    In network to MS direction:
    0 0 0 0 0 0     Reserved
    In MS to network direction and in network to MS direction:

    0 0 0 0 0 1     The Transfer delay is binary coded in 6 bits, using a granularity of 10 ms
    0 0 1 1 1 1     giving a range of values from 10 ms to 150 ms in 10 ms increments

    0 1 0 0 0 0     The transfer delay is 200 ms + ((the binary coded value in 6 bits - 010000) * 50 ms)
    0 1 1 1 1 1     giving a range of values from 200 ms to 950 ms in 50ms increments

    1 0 0 0 0 0     The transfer delay is 1000 ms + ((the binary coded value in 6 bits - 100000) * 100 ms)
    1 1 1 1 1 0     giving a range of values from 1000 ms to 4000 ms in 100ms increments

    1 1 1 1 1 1     Reserved
    */
    if (pTafPdp->MinQosTab.usTransDelay <= 150)
    {
        pApsQos->ucTransDelay = (VOS_UINT8)(pTafPdp->MinQosTab.usTransDelay / 10);
    }
    else
    {
        if (pTafPdp->MinQosTab.usTransDelay < 200)
        {
            pApsQos->ucTransDelay = 15;
        }
        else
        {
            if (pTafPdp->MinQosTab.usTransDelay <= 950)
            {
                pApsQos->ucTransDelay = (VOS_UINT8)(((pTafPdp->MinQosTab.usTransDelay - 200) / 50) + 16);
            }
            else
            {
                if (pTafPdp->MinQosTab.usTransDelay < 1000)
                {
                    pApsQos->ucTransDelay = 31;
                }
                else
                {
                    if (pTafPdp->MinQosTab.usTransDelay <= 4000)
                    {
                        pApsQos->ucTransDelay = (VOS_UINT8)(((pTafPdp->MinQosTab.usTransDelay - 1000) / 100) + 32);
                    }
                    else
                    {
                        pApsQos->ucTransDelay = 62;
                    }
                }

            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : Taf_FillMinQos_Set_GuarantBitRateForUp
 功能描述  : 解析Guaranteed bit rate for uplink(Taf_FillMinQos降圈复杂度)
 输入参数  : pTafPdp
 输出参数  : pApsQos
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  Taf_FillMinQos_Set_GuarantBitRateForUp(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    /* Guaranteed bit rate for uplink, octet 12:
        In MS to network direction:
        0 0 0 0 0 0 0 0 Subscribed Guaranteed bit rate for uplink
        In network to MS direction:
        0 0 0 0 0 0 0 0 Reserved

        In MS to network direction and in network to MS direction:
        0 0 0 0 0 0 0 1 The Guaranteed bit rate is binary coded in 8 bits, using a granularity of 1 kbps
        0 0 1 1 1 1 1 1 giving a range of values from 1 kbps to 63 kbps in 1 kbps increments.

        0 1 0 0 0 0 0 0 The Guaranteed bit rate is 64 kbps + ((the binary coded value in 8 bits -01000000) * 8 kbps)
        0 1 1 1 1 1 1 1 giving a range of values from 64 kbps to 568 kbps in 8 kbps increments.

        1 0 0 0 0 0 0 0 The Guaranteed bit rate is 576 kbps + ((the binary coded value in 8 bits -10000000) * 64 kbps)
        1 1 1 1 1 1 1 0 giving a range of values from 576 kbps to 8640 kbps in 64 kbps increments.

        1 1 1 1 1 1 1 1 0kbps

        Guaranteed bit rate for uplink (extended), octet 17
        Bits
        8 7 6 5 4 3 2 1
        In MS to network direction and in network to MS direction:
        0 0 0 0 0 0 0 0 Use the value indicated by the Guaranteed bit rate for uplink in octet 12.

                        For all other values: Ignore the value indicated by the Guaranteed bit rate for uplink in octet 12
                        and use the following value:
        0 0 0 0 0 0 0 1 The Guaranteed bit rate is 8600 kbps + ((the binary coded value in 8 bits) * 100 kbps),
        0 1 0 0 1 0 1 0 giving a range of values from 8700 kbps to 16000 kbps in 100 kbps increments.

        0 1 0 0 1 0 1 1 The Guaranteed bit rate is 16 Mbps + ((the binary coded value in 8 bits - 01001010) * 1 Mbps),
        1 0 1 1 1 0 1 0 giving a range of values from 17 Mbps to 128 Mbps in 1 Mbps increments.

        1 0 1 1 1 0 1 1 The Guaranteed bit rate is 128 Mbps + ((the binary coded value in 8 bits - 10111010) * 2 Mbps),
        1 1 1 1 1 0 1 0 giving a range of values from 130 Mbps to 256 Mbps in 2 Mbps increments.

        The network shall map all other values not explicitly defined onto one of the values defined in this version of the protocol.
        The network shall return a negotiated value which is explicitly defined in this version of the protocol

    */

    #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
    pApsQos->ucGuarantBitRateForUpExt = 0;
    #endif

    if (pTafPdp->MinQosTab.ulGuarantBitUl <= 63)
    {
        pApsQos->ucGuarantBitRateForUp   = (VOS_UINT8)pTafPdp->MinQosTab.ulGuarantBitUl;
    }
    else
    {
        if (pTafPdp->MinQosTab.ulGuarantBitUl <= 568)
        {
            pApsQos->ucGuarantBitRateForUp = (VOS_UINT8)(((pTafPdp->MinQosTab.ulGuarantBitUl - 64) / 8) + 64);
        }
        else
        {
            if (pTafPdp->MinQosTab.ulGuarantBitUl < 576)
            {
                pApsQos->ucGuarantBitRateForUp = 127;  /*0 1 1 1 1 1 1 1*/
            }
            else
            {
                if (pTafPdp->MinQosTab.ulGuarantBitUl <= 8640)
                {
                    pApsQos->ucGuarantBitRateForUp = (VOS_UINT8)(((pTafPdp->MinQosTab.ulGuarantBitUl - 576) / 64) + 128);
                }
                else
                {
                    #if(PS_UE_REL_VER < PS_PTL_VER_R7)
                    pApsQos->ucGuarantBitRateForUp = 254;  /*1 1 1 1 1 1 1 0*/
                    #else
                    /* If the sending entity wants to indicate a Guaranteed bit rate for uplink
                          higher than 8640 kbps, it shall set octet 8 to "11111110",
                          i.e. 8640 kbps, and shall encode the value for the Guaranteed bit rate in octet 18 */
                    if (pTafPdp->MinQosTab.ulGuarantBitUl < 8700)
                    {
                        pApsQos->ucGuarantBitRateForUp = 254;  /*1 1 1 1 1 1 1 0*/
                    }
                    else
                    {
                        pApsQos->ucGuarantBitRateForUp = 254;
                        if (pTafPdp->MinQosTab.ulGuarantBitUl <= 16000)
                        {
                            pApsQos->ucGuarantBitRateForUpExt
                                = (VOS_UINT8)((pTafPdp->MinQosTab.ulGuarantBitUl - 8600) / 100);
                        }
                        else if (pTafPdp->MinQosTab.ulGuarantBitUl <= 128000)
                        {
                            pApsQos->ucGuarantBitRateForUpExt
                                = (VOS_UINT8)(((pTafPdp->MinQosTab.ulGuarantBitUl - 16000) / 1000) + 74);
                        }
                        else if (pTafPdp->MinQosTab.ulGuarantBitUl <= 256000)
                        {
                            pApsQos->ucGuarantBitRateForUpExt
                                = (VOS_UINT8)(((pTafPdp->MinQosTab.ulGuarantBitUl - 128000) / 2000) + 186);
                        }
                        else
                        {
                            pApsQos->ucGuarantBitRateForUpExt = 250;  /*1 1 1 1 1 0 1 0*/
                        }
                    }
                    #endif
                }
            }
        }
    }

}

/*****************************************************************************
 函 数 名  : Taf_FillMinQos_Set_GuarantBitRateForDown
 功能描述  : 解析Guaranteed bit rate for downlink(Taf_FillMinQos降圈复杂度)
 输入参数  : pTafPdp
 输出参数  : pApsQos
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  Taf_FillMinQos_Set_GuarantBitRateForDown(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    #if(PS_UE_REL_VER >= PS_PTL_VER_R5)
    pApsQos->ucGuarantBitRateForDownExt = 0;
    #endif

    if (pTafPdp->MinQosTab.ulGuarantBitDl <= 63)
    {
        pApsQos->ucGuarantBitRateForDown   = (VOS_UINT8)pTafPdp->MinQosTab.ulGuarantBitDl;
    }
    else
    {
        if (pTafPdp->MinQosTab.ulGuarantBitDl <= 568)
        {
            pApsQos->ucGuarantBitRateForDown = (VOS_UINT8)(((pTafPdp->MinQosTab.ulGuarantBitDl - 64) / 8) + 64);
        }
        else
        {
            if (pTafPdp->MinQosTab.ulGuarantBitDl < 576)
            {
                pApsQos->ucGuarantBitRateForDown = 127;  /*0 1 1 1 1 1 1 1*/
            }
            else
            {
                if (pTafPdp->MinQosTab.ulGuarantBitDl <= 8640)
                {
                    pApsQos->ucGuarantBitRateForDown = (VOS_UINT8)(((pTafPdp->MinQosTab.ulGuarantBitDl - 576) / 64) + 128);
                }
                else
                {
                    #if(PS_UE_REL_VER < PS_PTL_VER_R5)
                    pApsQos->ucGuarantBitRateForDown = 254;  /*1 1 1 1 1 1 1 0*/
                    #else
                    if (pTafPdp->MinQosTab.ulGuarantBitDl < 8700)
                    {
                        pApsQos->ucGuarantBitRateForDown = 254;  /*1 1 1 1 1 1 1 0*/
                    }
                    else
                    {
                        pApsQos->ucGuarantBitRateForDown = 254;

                        if (pTafPdp->MinQosTab.ulGuarantBitDl <= 16000)
                        {
                            pApsQos->ucGuarantBitRateForDownExt
                                = (VOS_UINT8)((pTafPdp->MinQosTab.ulGuarantBitDl - 8600) / 100);
                        }
                        #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
                        else if (pTafPdp->MinQosTab.ulGuarantBitDl <= 128000)
                        {
                            pApsQos->ucGuarantBitRateForDownExt
                                = (VOS_UINT8)(((pTafPdp->MinQosTab.ulGuarantBitDl - 16000) / 1000) + 74);
                        }
                        else if (pTafPdp->MinQosTab.ulGuarantBitDl <= 256000)
                        {
                            pApsQos->ucGuarantBitRateForDownExt
                                = (VOS_UINT8)(((pTafPdp->MinQosTab.ulGuarantBitDl - 128000) / 2000) + 186);
                        }
                        #endif
                        else
                        {
                            #if(PS_UE_REL_VER < PS_PTL_VER_R7)
                            pApsQos->ucGuarantBitRateForDownExt = 74;   /*0 1 0 0 1 0 1 0*/
                            #else
                            pApsQos->ucGuarantBitRateForDownExt = 250;  /*1 1 1 1 1 0 1 0*/
                            #endif
                        }
                    }
                    #endif
                }
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : Taf_FillMinQos_Set_DelayClass
 功能描述  : 解析Delay class(Taf_FillMinQos降圈复杂度)
 输入参数  : pTafPdp
 输出参数  : pApsQos
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  Taf_FillMinQos_Set_DelayClass(
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    /*根据Traffic class确定DelayClass */
    switch(pApsQos->ucTrafficClass)
    {
        case    APS_QOS_TRAFFIC_CLASS_CONVERSATIONAL    :
        case    APS_QOS_TRAFFIC_CLASS_STREAMING     :
            pApsQos->ucDelayClass           = 1;
            break;

        case    APS_QOS_TRAFFIC_CLASS_INTERACTIVE   :
            switch(pApsQos->ucTraffHandlPrior)
            {
                case    APS_QOS_TRAFFF_HANDL_PRIOR_1    :
                    pApsQos->ucDelayClass   = 1;
                    break;

                case    APS_QOS_TRAFFF_HANDL_PRIOR_2    :
                    pApsQos->ucDelayClass   = 2;
                    break;

                case    APS_QOS_TRAFFF_HANDL_PRIOR_3    :
                    pApsQos->ucDelayClass   = 3;
                    break;

                default :
                    pApsQos->ucDelayClass   = 0;
                    break;
            }
            break;

        case    APS_QOS_TRAFFIC_CLASS_BACKGROUND    :
            pApsQos->ucDelayClass           = 4;
            break;

        default :
            pApsQos->ucDelayClass           = 0;
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : Taf_FillMinQos_Set_ReliabClass
 功能描述  : 解析Reliable Class(Taf_FillMinQos降圈复杂度)
 输入参数  : pTafPdp
 输出参数  : pApsQos
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  Taf_FillMinQos_Set_ReliabClass(
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    switch(pApsQos->ucSduErrRatio)
    {
        case    APS_QOS_SDU_ERR_RATIO_1EM5  :
        case    APS_QOS_SDU_ERR_RATIO_1EM6  :
        case    APS_QOS_SDU_ERR_RATIO_1EM10 :
            pApsQos->ucReliabClass          = 2;
            break;

        case    APS_QOS_SDU_ERR_RATIO_1EM4  :
            pApsQos->ucReliabClass          = 3;
            break;

        case    APS_QOS_SDU_ERR_RATIO_1EM2  :
        case    APS_QOS_SDU_ERR_RATIO_7EM3  :
        case    APS_QOS_SDU_ERR_RATIO_1EM3  :
            if ( pApsQos->ucResidualBer >= APS_QOS_RESIDUAL_BER_1EM4)
            {
                pApsQos->ucReliabClass      = 4;
            }
            else
            {
                pApsQos->ucReliabClass      = 5;
            }
            break;

        default:
            pApsQos->ucReliabClass          = 0;
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : Taf_FillMinQos_Set_PeakThrough
 功能描述  : 解析Peak throughput(Taf_FillMinQos降圈复杂度)
 输入参数  : pTafPdp
 输出参数  : pApsQos
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  Taf_FillMinQos_Set_PeakThrough(
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    if ( pApsQos->ucMaxBitRateForUp == APS_QOS_MAX_BITRATE_SUBSCRIBE)
    {
        pApsQos->ucPeakThrough              = 0;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_16KBPS )
    {
        pApsQos->ucPeakThrough              = 1;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_32KBPS )
    {
        pApsQos->ucPeakThrough              = 2;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_64KBPS )
    {
        pApsQos->ucPeakThrough              = 3;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_128KBPS )
    {
        pApsQos->ucPeakThrough              = 4;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_256KBPS )
    {
        pApsQos->ucPeakThrough              = 5;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_512KBPS )
    {
        pApsQos->ucPeakThrough              = 6;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_1024KBPS )
    {
        pApsQos->ucPeakThrough              = 7;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_2048KBPS )
    {
        pApsQos->ucPeakThrough              = 8;
    }
    else if ( pApsQos->ucMaxBitRateForUp == APS_QOS_MAX_BITRATE_0KBPS )
    {
        pApsQos->ucPeakThrough              = 1;
    }
    else
    {
        pApsQos->ucPeakThrough              = 9;
    }

    return;
}

/*****************************************************************************
 函 数 名  : Taf_FillMinQos_Set_SrcStatisticsDescriptor
 功能描述  : 解析Source Statistics Descriptor(Taf_FillMinQos降圈复杂度)
 输入参数  : pTafPdp    --指向的值不会改变，指向const的指针
 输出参数  : pApsQos
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月7日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  Taf_FillMinQos_Set_SrcStatisticsDescriptor(
    const TAF_PDP_TABLE_STRU            *pstTafPdp,
    APS_PDP_QOS_STRU                    *pstApsQos
)
{
    if ( (APS_3GPP_QOS_TRAFFIC_CLASS_INTERACTIVE    != pstApsQos->ucTrafficClass)
      && (APS_3GPP_QOS_TRAFFIC_CLASS_BACKGROUND     != pstApsQos->ucTrafficClass))
    {
        pstApsQos->ucSrcStatisticsDescriptor  = pstTafPdp->MinQosTab.ucSrcStatisticsDescriptor;
    }
    else
    {
        pstApsQos->ucSrcStatisticsDescriptor  = 0;    /*目前默认填写为0*/
    }

    return;
}

/*****************************************************************************
 函 数 名  : Taf_FillMinQos_Set_SignallingIndication
 功能描述  : 解析Signalling Indication(Taf_FillMinQos降圈复杂度)
 输入参数  : pTafPdp    --指向的值不会改变，指向const的指针
 输出参数  : pApsQos
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月7日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  Taf_FillMinQos_Set_SignallingIndication(
    const TAF_PDP_TABLE_STRU            *pstTafPdp,
    APS_PDP_QOS_STRU                    *pstApsQos
)
{
    if ( (APS_3GPP_QOS_TRAFFIC_CLASS_CONVERSATIONAL     != pstApsQos->ucTrafficClass)
      && (APS_3GPP_QOS_TRAFFIC_CLASS_STREAMING          != pstApsQos->ucTrafficClass)
      && (APS_3GPP_QOS_TRAFFIC_CLASS_BACKGROUND         != pstApsQos->ucTrafficClass))
    {
        pstApsQos->ucSignallingIndication     = pstTafPdp->MinQosTab.ucSignallingIndication;

        if ( 1 == pstApsQos->ucSignallingIndication)
        {
            pstApsQos->ucTraffHandlPrior      = 1;
        }
    }
    else
    {
        pstApsQos->ucSignallingIndication     = 0;    /*目前默认填写为0*/
    }

    return;
}


/*****************************************************************************
 函 数 名  : Taf_FillMinQos
 功能描述  : 根据Qos表中APP设定的值，转化为24008中定义的值.完全继承V100R001
 输入参数  : pTafPdp
 输出参数  : pApsQos
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数
  2.日    期   : 2015年4月7日
    作    者   : w00316404
    修改内容   : M project A characeristic AT part

*****************************************************************************/
VOS_VOID  Taf_FillMinQos(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    /*AT协议中取值含义与24008中定义不相同，在此做转化 */
    /*
    In MS to network direction:
    0 0 0       Subscribed traffic class
    In network to MS direction:
    0 0 0       Reserved
    In MS to network direction and in network to MS direction:
    0 0 1       Conversational class
    0 1 0       Streaming class
    0 1 1       Interactive class
    1 0 0       Background class
    1 1 1       Reserved
    */
    if (pTafPdp->MinQosTab.ucTrafficClass >= 4)
    {
        pApsQos->ucTrafficClass = 0;
    }
    else
    {
        pApsQos->ucTrafficClass = pTafPdp->MinQosTab.ucTrafficClass + 1;
    }

    /*
    In MS to network direction:
    0 0     Subscribed delivery order
    In network to MS direction:
    0 0     Reserved
    In MS to network direction and in network to MS direction:
    0 1     With delivery order ('yes')
    1 0     Without delivery order ('no')
    1 1     Reserved
    */
    if (pTafPdp->MinQosTab.ucDeliverOrder <= 2)
    {
        pApsQos->ucDeliverOrder = 2 - pTafPdp->MinQosTab.ucDeliverOrder;
    }
    else
    {
        pApsQos->ucDeliverOrder = 0;
    }

    /*
    In MS to network direction:
    0 0 0       Subscribed delivery of erroneous SDUs
    In network to MS direction:
    0 0 0       Reserved
    In MS to network direction and in network to MS direction:
    0 0 1       No detect ('-')
    0 1 0       Erroneous SDUs are delivered ('yes')
    0 1 1       Erroneous SDUs are not delivered ('no')
    1 1 1       Reserved
    */
    if (pTafPdp->MinQosTab.ucDeliverErrSdu <= 3)
    {
        pApsQos->ucDeliverOfErrSdu = 3 - pTafPdp->MinQosTab.ucDeliverErrSdu;
    }
    else
    {
        pApsQos->ucDeliverOfErrSdu = 0;
    }

    Taf_FillMinQos_Set_MaximSduSize(pTafPdp, pApsQos);

    Taf_FillMinQos_Set_MaxBitRateForUp(pTafPdp, pApsQos);

    Taf_FillMinQos_Set_MaxBitRateForDown(pTafPdp, pApsQos);

    /*
    In network to MS direction:
    0 0 0 0     Reserved
    In MS to network direction and in network to MS direction:
    The Residual BER value consists of 4 bits. The range is from 5*10-2 to 6*10-8.
    0 0 0 1     5*10-2
    0 0 1 0     1*10-2
    0 0 1 1     5*10-3
    0 1 0 0     4*10-3
    0 1 0 1     1*10-3
    0 1 1 0     1*10-4
    0 1 1 1     1*10-5
    1 0 0 0     1*10-6
    1 0 0 1     6*10-8
    1 1 1 1     Reserved
    */
    pApsQos->ucResidualBer           = pTafPdp->MinQosTab.ucResidualBer;

    /*
    In MS to network direction:
    0 0 0 0     Subscribed SDU error ratio
    In network to MS direction:
    0 0 0 0     Reserved
    In MS to network direction and in network to MS direction:
    The SDU error ratio value consists of 4 bits. The range is is from 1*10-1 to 1*10-6.
    0 0 0 1     1*10-2
    0 0 1 0     7*10-3
    0 0 1 1     1*10-3
    0 1 0 0     1*10-4
    0 1 0 1     1*10-5
    0 1 1 0     1*10-6
    0 1 1 1     1*10-1
    1 1 1 1     Reserved
    */
    pApsQos->ucSduErrRatio           = pTafPdp->MinQosTab.ucSduErrRatio;

    Taf_FillMinQos_Set_TransDelay(pTafPdp, pApsQos);

    /*
    In MS to network direction:
    0 0     Subscribed traffic handling priority
    In network to MS direction:
    0 0     Reserved
    In MS to network direction and in network to MS direction:
    0 1     Priority level 1
    1 0     Priority level 2
    1 1     Priority level 3
    */
    pApsQos->ucTraffHandlPrior       = pTafPdp->MinQosTab.ucTraffHandlePrior;

    Taf_FillMinQos_Set_GuarantBitRateForUp(pTafPdp, pApsQos);

    Taf_FillMinQos_Set_GuarantBitRateForDown(pTafPdp, pApsQos);

    Taf_FillMinQos_Set_DelayClass(pApsQos);

    /*根据SDU error ratio和Residual bit error ratio确定ucReliabClass*/
    Taf_FillMinQos_Set_ReliabClass(pApsQos);

    /*根据Maximum bitrate确定ucPeakThrough*/
    Taf_FillMinQos_Set_PeakThrough(pApsQos);

    /*As the allocation/retention priority attribute is not available in the UE
    (see 6.4.4.1) the UE shall set the R97/98 precedence class attribute to the
    value "subscribed"*/
    pApsQos->ucPrecedenceClass              = 0;

    /*Mean throughput class Always set to 31*/
    pApsQos->ucMeanThrough                  = 31;

    #if(PS_UE_REL_VER >= PS_PTL_VER_R5)
    Taf_FillMinQos_Set_SrcStatisticsDescriptor(pTafPdp, pApsQos);
    Taf_FillMinQos_Set_SignallingIndication(pTafPdp, pApsQos);
    #endif

    return;
}

/******************************************************************************
 Function:       Taf_LenStr2Apn
 Description:    将字符串格式的APN转化为协议定义的APN格式.完全继承V100R001
 Calls:          Taf_LenStr2Apn
 Data Accessed:
 Data Updated:
 Input:          pucStr - 字符串格式的Apn
 Output:         pucApn - 协议定义的APN
 Return:
 Others:
  1.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，使用APN结构作为入参
******************************************************************************/
VOS_VOID Taf_LenStr2Apn(
    CONST TAF_PDP_APN_STRU              *pstApn,
    VOS_UINT8                           *pucApn
)
{
    VOS_UINT8 i, j = 0;
    VOS_UINT8 ucLenPosition = 1;
    if (0 == pstApn->ucLength)
    {   /*APN长度为0，直接长度赋值返回*/
        pucApn[0] = 0;
        return;
    }

    for (i = 1; (i <= pstApn->ucLength) && (i <= TAF_MAX_APN_LEN); i++)
    {   /*从第1个有效字符开始检查*/
        if (pstApn->aucValue[i - 1] != '.')
        {   /*如果是有效字符，将其拷贝*/
            pucApn[i + 1] = pstApn->aucValue[i - 1];
            j++;  /*有效字符数增1*/
        }
        else
        {   /*如果字符是'.'，填充.号前有效字符的总数*/
            pucApn[ucLenPosition] = j;
            j = 0;  /*开始下一个有效字符段的长度累计*/
            ucLenPosition = i + 1; /*下一段有效字符长度填充位置*/
        }
    }
    pucApn[ucLenPosition] = j; /*填充最后一段有效字符的长度*/
    pucApn[0] = i;  /*填充整个APN的长度*/
    return;
}

/******************************************************************************
 Function:       Taf_LenStr2IpAddr
 Description:    将字符串格式的IP地址转化为SM协议IP地址格式.完全继承V100R001
 Calls:
 Data Accessed:
 Data Updated:
 Input:          pucStr - 字符串格式的IP地址
 Output:         pucIpAddr - SM协议定义的IP地址
 Return:         无
 Others:
******************************************************************************/
VOS_VOID Taf_LenStr2IpAddr(CONST VOS_UINT8* pucStr, VOS_UINT8 *pucIpAddr)
{
    VOS_UINT8 i, j = 0;
    VOS_UINT8 ucValue = 0;

    if (0 == pucStr[0])
    {   /*ADDR长度为0，直接长度赋值返回*/
        pucIpAddr[0] = 0;
        pucIpAddr[1] = 0;
        pucIpAddr[2] = 0;
        pucIpAddr[3] = 0;
        return;
    }

    if (pucStr[1] == '.')
    {   /*如果第1个有效字符是'.'，IP地址是非法的*/
        return;
    }
    for (i = 1; (i <= pucStr[0]) && (i < TAF_MAX_IPV4_ADDR_STR_LEN); i++)
    {   /*从第1个有效字符开始检查*/
        if (((pucStr[i] < 0x30) || (pucStr[i] > 0x39)) && (pucStr[i] != '.'))
        {   /*超出'0'-'9'的字符非法*/
            return;
        }
        if (pucStr[i] != '.')
        {   /*如果是有效字符，转化为数字*/
            if (((ucValue * 10) + (pucStr[i] - 0x30)) <= 255)
            {   /*字符串转化为有效IP段位值*/
                ucValue = (VOS_UINT8)((ucValue * 10) + (pucStr[i] - 0x30));
            }
            else
            {   /*超过255出错*/
                return;
            }
        }
        else
        {   /*如果字符是'.'，前一位段值已经计算出来*/
            if (j <= 3)
            {   /*本版本只支持IPV4地址*/
                pucIpAddr[j] = ucValue;
                ucValue = 0;
                j++;  /*开始下一个有效字符段的长度累计*/
            }
            else
            {   /*超出4个IP位段，非法*/
                return;
            }
        }
    }
    if (j == 3)
    {
        pucIpAddr[j] = ucValue;
        return;
    }
    else
    {
        return;
    }
}

/*****************************************************************************
 Prototype      : Aps_PackApsSecActReqPara
 Description    : 构造并输出函数Aps_PdpSecActReq()需要的输入参数;
 Input          : ucCid:该二次激活的cid
                  ucPdpId:该二次激活的PdpId
 Output         : pApsSecActReq
 Return Value   :
 Data Accessed  : g_TafCidTab[]
 Data Updated   :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  Aps_PackApsSecActReqPara (
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPdpId,
    APS_PDP_SEC_ACT_REQ_ST             *pApsSecActReq
)
{
    TAF_PDP_TABLE_STRU                 *pTafPdp;
    VOS_UINT32                          ulReturn;

    pTafPdp                                     = VOS_NULL;
    ulReturn                                    = TAF_APS_SUCC;

    pTafPdp                                     = &g_TafCidTab[ucCid];

    pApsSecActReq->OP_Sapi                      = TAF_FREE;
    pApsSecActReq->Op_Xid_DCmp                  = VOS_FALSE;
    pApsSecActReq->Op_Xid_PCmp                  = VOS_FALSE;
    pApsSecActReq->Op_Tft                       = TAF_FREE;
    pApsSecActReq->Op_Spare                     = TAF_FREE;

    pApsSecActReq->Tft.OP_SourcePort            = TAF_FREE;
    pApsSecActReq->Tft.OP_DestPort              = TAF_FREE;
    pApsSecActReq->Tft.OP_SourceIpAddrAndMask   = TAF_FREE;
    pApsSecActReq->Tft.OP_ProtocolId            = TAF_FREE;
    pApsSecActReq->Tft.OP_ulSecuParaIndex       = TAF_FREE;
    pApsSecActReq->Tft.OP_ucTypeOfService       = TAF_FREE;
    pApsSecActReq->Tft.OP_Spare                 = TAF_FREE;

    /*SAPI*/
    pApsSecActReq->OP_Sapi                      = TAF_USED;
    pApsSecActReq->ucSapi                       = APS_SAPI_INIT;
    pApsSecActReq->ucPdpId                      = ucPdpId;

    /*获取主PdpId*/
    pApsSecActReq->ucPriPdpId           = TAF_APS_GetPdpIdByCid(g_TafCidTab[ucCid].ucPriCid);
    if ( TAF_APS_INVALID_PDPID == pApsSecActReq->ucPriPdpId)
    {
        /*没有找到主PDP*/
        APS_WARN_LOG("not find pri PDP !");
        return  TAF_APS_FAIL;
    }

    /*处理Qos*/
    Taf_FillQos( pTafPdp, &pApsSecActReq->Qos );

    /*处理TFT*/
    if ( TAF_FREE == g_TafCidTab[ucCid].ucPfTabFlag )
    {
        /*if(PDP全局数据表中该CID的PDP没有定义TFT)*/
        pApsSecActReq->Op_Tft                       = TAF_FREE;
    }
    else
    {
        pApsSecActReq->Op_Tft                       = TAF_USED;
        ulReturn = Aps_FillTft( pTafPdp, &pApsSecActReq->Tft );
        if ( TAF_APS_SUCC != ulReturn )
        {
            return TAF_APS_FAIL;
        }
    }

    /*处理XID*/
    Aps_FillSecXid(pTafPdp, pApsSecActReq);

    /*填充完毕，直接返回成功*/
    return TAF_SUCCESS;

}

/*****************************************************************************
 Prototype      : Aps_FillSecXid
 Description    : 打包APS_PDP_ACT_REQ_ST型变量时，向该变量中填充XID参数时使用。
 Input          : ucCid
                  ucPdpId
 Output         : pApsActReq
 Return Value   :
 Data Accessed  :
 Data Updated   :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID    Aps_FillSecXid(         TAF_PDP_TABLE_STRU         *pTafPdp,
                                    APS_PDP_SEC_ACT_REQ_ST     *pApsSecActReq  )
{

    pApsSecActReq->Op_Xid_DCmp             = VOS_FALSE;
    pApsSecActReq->Op_Xid_PCmp             = VOS_FALSE;

    switch(pTafPdp->CidTab.enPdpDcomp)
    {
        case    TAF_PDP_D_COMP_OFF  :
            break;

        case    TAF_PDP_D_COMP_ON   :
            pApsSecActReq->Op_Xid_DCmp     = VOS_TRUE;
            pApsSecActReq->ucDCmprAlgrth   = SN_V42_ALGRTH;
            break;

        case    TAF_PDP_D_COMP_V42  :
            pApsSecActReq->Op_Xid_DCmp     = VOS_TRUE;
            pApsSecActReq->ucDCmprAlgrth   = SN_V42_ALGRTH;
            break;

        default    :
            APS_WARN_LOG("PdpDcomp ERR !");
            break;
    }


    switch(pTafPdp->CidTab.enPdpHcomp)
    {
        case    TAF_PDP_H_COMP_OFF  :
            break;

        case    TAF_PDP_H_COMP_ON   :
            pApsSecActReq->Op_Xid_PCmp     = VOS_TRUE;
            pApsSecActReq->ucPCmprAlgrth   = SN_2507_ALGRTH;
            break;

        case    TAF_PDP_H_COMP_RFC1144  :
            pApsSecActReq->Op_Xid_PCmp     = VOS_TRUE;
            pApsSecActReq->ucPCmprAlgrth   = SN_1144_ALGRTH;
            break;

        case    TAF_PDP_H_COMP_RFC2507  :
            pApsSecActReq->Op_Xid_PCmp     = VOS_TRUE;
            pApsSecActReq->ucPCmprAlgrth   = SN_2507_ALGRTH;
            break;

        default    :
            APS_WARN_LOG("PdpHcomp ERR !");
            break;
    }

    return;

}

/*****************************************************************************
 Prototype      : Aps_FillTft
 Description    : 构造并输出函数Aps_PdpSecActReq()需要的输入参数TFT;
 Input          : ucCid:该二次激活的cid
                  ucPdpId:该二次激活的PdpId
 Output         : pApsSecActReq
 Return Value   :
 Data Accessed  : g_TafCidTab[]
 Data Updated   :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  Aps_FillTft( TAF_PDP_TABLE_STRU              *pTafPdp,
                         APS_PDP_TFT_ST                  *pApsTft )
{
    /* TODO: 李紫剑 */
#if 0
    pApsTft->ucPacketFilterId               = pTafPdp->astTftTab[0].ucPacketFilterId;
    pApsTft->ucPrecedence                   = pTafPdp->astTftTab[0].ucPrecedence;

    if ( VOS_TRUE  == pTafPdp->astTftTab[0].OP_HighSourcePort)
    {
        pApsTft->OP_SourcePort          = VOS_TRUE;
        pApsTft->usSrcPortHighLimit     = pTafPdp->astTftTab[0].usHighSourcePort;
        pApsTft->usSrcPortLowLimit      = pTafPdp->astTftTab[0].usLowSourcePort;
    }

    if ( VOS_TRUE  == pTafPdp->astTftTab[0].OP_HighDestPort)
    {
        pApsTft->OP_DestPort        = VOS_TRUE;
        pApsTft->usDstPortHighLimit = pTafPdp->astTftTab[0].usHighDestPort;
        pApsTft->usDstPortLowLimit  = pTafPdp->astTftTab[0].usLowDestPort;
    }

    if ( VOS_TRUE  == pTafPdp->astTftTab[0].OP_SourceIpAddr)
    {
        pApsTft->OP_SourceIpAddrAndMask     = VOS_TRUE;
        if ( TAF_SUCCESS != Taf_LenStr2IpAddr( pTafPdp->astTftTab[0].aucSourceIpAddr,
                                            pApsTft->aucSrcIpAddress ) )
        {
            return  TAF_APS_FAIL;
        }
        if ( TAF_SUCCESS != Taf_LenStr2IpAddr( pTafPdp->astTftTab[0].aucSourceIpMask,
                                            pApsTft->aucSrcIpMask ) )
        {
            return  TAF_APS_FAIL;
        }
    }

    if ( VOS_TRUE  == pTafPdp->astTftTab[0].OP_ProtocolId)
    {
        pApsTft->OP_ProtocolId              = VOS_TRUE;
        pApsTft->ucProtocolId               = pTafPdp->astTftTab.ucProtocolId;
    }

    if ( VOS_TRUE  == pTafPdp->astTftTab[0].OP_ulSecuParaIndex)
    {
        pApsTft->OP_ulSecuParaIndex         = VOS_TRUE;
        pApsTft->ulSecuParaIndex            = pTafPdp->astTftTab[0].ulSecuParaIndex; /*SPI*/
    }

    if ( VOS_TRUE  == pTafPdp->astTftTab[0].OP_ucTypeOfService)
    {
        pApsTft->OP_ucTypeOfService         = VOS_TRUE;
        pApsTft->ucTypeOfService            = pTafPdp->astTftTab[0].ucTypeOfService;  /*TOS*/
        pApsTft->ucTypeOfServiceMask        = pTafPdp->astTftTab[0].ucTypeOfServiceMask;    /*TOS Mask*/
    }
#endif
    return  TAF_APS_SUCC;
}


/*****************************************************************************
 Prototype      : Aps_PackApsActReqPara
 Description    : 构造并输出函数Aps_PdpActReq()需要的输入参数;对应V100R001中的
                  Taf_FillApsPdp(),有所修改.
 Input          : ucCid
                  ucPdpId
 Output         : pApsActReq
 Return Value   :
 Data Accessed  : PDP全局数据表g_TafCidTab[TAF_MAX_CID + 1];
 Data Updated   :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID  Aps_MakeAnsActReq (
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPdpId,
    APS_PDP_ACT_REQ_ST                 *pApsActReq
)
{
    TAF_NDIS_AUTHDATA_TABLE_STRU       *pApsNdisAuthdata;
    TAF_PDP_TABLE_STRU                 *pTafPdp;
    VOS_UINT8                           ucAuthDataUsernameLen;
    VOS_UINT8                           ucAuthDataPasswordLen;

    pApsNdisAuthdata                = &g_ApsNdisAuthdataTab[ucCid];
    pTafPdp                         = &g_TafCidTab[ucCid];
    ucAuthDataUsernameLen           = 0;
    ucAuthDataPasswordLen           = 0;


    pApsActReq->OP_APN              = VOS_FALSE;
    pApsActReq->OP_AUTH             = VOS_FALSE;
    pApsActReq->OP_DNS              = VOS_FALSE;
    pApsActReq->OP_NBNS             = VOS_FALSE;
    pApsActReq->OP_Sapi             = VOS_FALSE;
    pApsActReq->Op_Xid_DCmp         = VOS_FALSE;
    pApsActReq->Op_Xid_PCmp         = VOS_FALSE;
    pApsActReq->OP_SPARE            = VOS_FALSE;

    pApsActReq->ucPdpId             = ucPdpId;

    /*SAPI*/
    pApsActReq->OP_Sapi             = VOS_TRUE;
    pApsActReq->ucSapi              = APS_SAPI_INIT;

    /*V100专用*/
    if ( VOS_TRUE == pApsNdisAuthdata->ucUsed)
    {   /*鉴权*/

        pApsActReq->OP_AUTH          = VOS_TRUE;
        pApsActReq->PdpAuth.AuthType = TAF_PCO_AUTH_PAP;

        ucAuthDataUsernameLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pApsNdisAuthdata->stAuthData.aucUsername);
        ucAuthDataPasswordLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pApsNdisAuthdata->stAuthData.aucPassword);

        if (ucAuthDataUsernameLen > TAF_MAX_USERNAME_LEN)
        {
            ucAuthDataUsernameLen = TAF_MAX_USERNAME_LEN;
            APS_WARN_LOG("Aps_PackApsActReqPara:Len of UserName is over 99 bytes.\r");
        }

        if (ucAuthDataPasswordLen > TAF_MAX_PASSCODE_LEN)
        {
            ucAuthDataPasswordLen = TAF_MAX_PASSCODE_LEN;
            APS_WARN_LOG("Aps_PackApsActReqPara:Len of Password is over 99 bytes.\r");
        }

        pApsActReq->PdpAuth.AuthContent.stPap.aucUserName[0] = ucAuthDataUsernameLen;
        pApsActReq->PdpAuth.AuthContent.stPap.aucPassword[0] = ucAuthDataPasswordLen;

        PS_MEM_CPY(   &pApsActReq->PdpAuth.AuthContent.stPap.aucUserName[1],
                      pApsNdisAuthdata->stAuthData.aucUsername,
                      ucAuthDataUsernameLen);

        PS_MEM_CPY(   &pApsActReq->PdpAuth.AuthContent.stPap.aucPassword[1],
                      pApsNdisAuthdata->stAuthData.aucPassword,
                      ucAuthDataPasswordLen);
    }
    else
    {
        /*不鉴权*/
        pApsActReq->PdpAuth.AuthType    = TAF_PCO_NOT_AUTH;
        PS_MEM_SET(&pApsActReq->PdpAuth.AuthContent, 0, sizeof(pApsActReq->PdpAuth.AuthContent));
    }

    /*网络激活时以网络携带的地址类型和地址内容为准*/
    pApsActReq->ucPdpType    = g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum;
    pApsActReq->aucIpAddr[0] = g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr[0];
    pApsActReq->aucIpAddr[1] = g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr[1];
    pApsActReq->aucIpAddr[2] = g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr[2];
    pApsActReq->aucIpAddr[3] = g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr[3];

    /*若网络发来了APN,网络激活时以网络携带的APN内容为准*/
    if ((VOS_TRUE == g_PdpEntity[ucPdpId].PdpApnFlag)
     && (0 != g_PdpEntity[ucPdpId].PdpApn.ucLength))
    {
        pApsActReq->OP_APN          = VOS_TRUE;
        if (g_PdpEntity[ucPdpId].PdpApn.ucLength > TAF_MAX_APN_LEN)
        {
            g_PdpEntity[ucPdpId].PdpApn.ucLength = TAF_MAX_APN_LEN;
        }
        pApsActReq->aucApn[0] = g_PdpEntity[ucPdpId].PdpApn.ucLength;
        PS_MEM_CPY(                 &pApsActReq->aucApn[1],
                                    g_PdpEntity[ucPdpId].PdpApn.aucValue,
                                    pApsActReq->aucApn[0]);
    }
    else
    {
        /*否则以PDP数据表中的数据为准*/
        if (VOS_TRUE == pTafPdp->ucUsed)
        {
            /*处理aucApn*/
            Taf_LenStr2Apn(&(pTafPdp->CidTab.stApn), pApsActReq->aucApn);
            if ( 0 != pApsActReq->aucApn[0])
            {
                pApsActReq->OP_APN      = VOS_TRUE;
            }
        }
    }

    /*处理Qos*/
    if (pTafPdp->ucQosTabFlag)
    {
        Taf_FillQos(pTafPdp, &pApsActReq->ReqQos);
    }
    else
    {   /*没有定义QOS，则填网络决定*/
        Taf_FillQos(&g_TafCidTab[0], &pApsActReq->ReqQos);
    }

    /*处理XID*/
    Aps_FillXid(pTafPdp, pApsActReq);

    g_PdpEntity[ucPdpId].PdpProcTrack.ucHowToInitAct = APS_APP_MANUL_ACT;

    /*填充完毕，直接返回成功*/
    return ;

}

/*****************************************************************************
 Prototype      : Aps_FillXid
 Description    : 打包APS_PDP_ACT_REQ_ST型变量时，向该变量中填充XID参数时使用。
 Input          : ucCid
                  ucPdpId
 Output         : pApsActReq
 Return Value   :
 Data Accessed  :
 Data Updated   :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID    Aps_FillXid(        TAF_PDP_TABLE_STRU         *pTafPdp,
                                APS_PDP_ACT_REQ_ST         *pApsActReq  )
{

    pApsActReq->Op_Xid_DCmp             = VOS_FALSE;
    pApsActReq->Op_Xid_PCmp             = VOS_FALSE;

    switch(pTafPdp->CidTab.enPdpDcomp)
    {
        case    TAF_PDP_D_COMP_OFF  :
            break;

        case    TAF_PDP_D_COMP_ON   :
            pApsActReq->Op_Xid_DCmp     = VOS_TRUE;
            pApsActReq->ucDCmprAlgrth   = SN_V42_ALGRTH;
            break;

        case    TAF_PDP_D_COMP_V42  :
            pApsActReq->Op_Xid_DCmp     = VOS_TRUE;
            pApsActReq->ucDCmprAlgrth   = SN_V42_ALGRTH;
            break;

        default    :
            APS_WARN_LOG("PdpDcomp ERR !");
            break;
    }


    switch(pTafPdp->CidTab.enPdpHcomp)
    {
        case    TAF_PDP_H_COMP_OFF  :
            break;

        case    TAF_PDP_H_COMP_ON   :
            pApsActReq->Op_Xid_PCmp     = VOS_TRUE;
            pApsActReq->ucPCmprAlgrth   = SN_2507_ALGRTH;
            break;

        case    TAF_PDP_H_COMP_RFC1144  :
            pApsActReq->Op_Xid_PCmp     = VOS_TRUE;
            pApsActReq->ucPCmprAlgrth   = SN_1144_ALGRTH;
            break;

        case    TAF_PDP_H_COMP_RFC2507  :
            pApsActReq->Op_Xid_PCmp     = VOS_TRUE;
            pApsActReq->ucPCmprAlgrth   = SN_2507_ALGRTH;
            break;

        default    :
            APS_WARN_LOG("PdpHcomp ERR !");
            break;
    }

    return;

}


/*****************************************************************************
 Prototype      : Aps_FillDns
 Description    : 打包APS_PDP_ACT_REQ_ST型变量时，向该变量中填充DNS参数时使用。
 Input          : ucCid
                  ucPdpId
 Output         : pApsActReq
 Return Value   :
 Data Accessed  :
 Data Updated   :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID    Aps_FillDns(                TAF_PDP_TABLE_STRU *pTafPdp,
                                        APS_PDP_ACT_REQ_ST *pApsActReq  )
{
    if (pTafPdp->ucDnsFlag)
    {
        pApsActReq->OP_DNS              = VOS_TRUE;
        pApsActReq->PdpDns              = pTafPdp->DnsTab;
    }
    else
    {
        pApsActReq->OP_DNS              = VOS_FALSE;
        pApsActReq->PdpDns.bitOpPrimDnsAddr    = VOS_FALSE;
        pApsActReq->PdpDns.bitOpSecDnsAddr    = VOS_FALSE;
    }

    return;
}

/*****************************************************************************
 函 数 名  : Aps_PackApsMdfReqPara
 功能描述  : 构造并输出函数Aps_PsCallModify()需要的输入参数
 输入参数  : VOS_UINT8                           ucCid
             VOS_UINT8                           ucPdpId
             APS_PDP_MDF_REQ_ST                 *pApsMdfReq
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年xx月xx日
    作    者   : xxx
    修改内容   : 新生成函数

  2.日    期   : 2006年03月03日
    作    者   : H41410
    修改内容   : 问题单号: A32D02345

  3.日    期   : 2010年12月15日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2010120605160，W单模下PDP激活后，修改为双模，
                 重选到G下数传无法恢复

*****************************************************************************/
VOS_UINT32 Aps_PackApsMdfReqPara (
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPdpId,
    APS_PDP_MDF_REQ_ST                 *pApsMdfReq
)
{
    VOS_UINT32                          ulReturn;

    ulReturn                        = TAF_APS_SUCC;

    pApsMdfReq->Op_Qos              = TAF_FREE;
    pApsMdfReq->Op_Tft              = TAF_FREE;

    pApsMdfReq->Tft.OP_SourcePort          = TAF_FREE;
    pApsMdfReq->Tft.OP_DestPort            = TAF_FREE;
    pApsMdfReq->Tft.OP_SourceIpAddrAndMask = TAF_FREE;
    pApsMdfReq->Tft.OP_ProtocolId          = TAF_FREE;
    pApsMdfReq->Tft.OP_ulSecuParaIndex     = TAF_FREE;
    pApsMdfReq->Tft.OP_ucTypeOfService     = TAF_FREE;
    pApsMdfReq->Tft.OP_Spare               = TAF_FREE;

    pApsMdfReq->OP_Sapi              = TAF_FREE;
    pApsMdfReq->Op_Spare             = TAF_FREE;


    pApsMdfReq->ucPdpId             = ucPdpId;

    /*fill SAPI*/
    pApsMdfReq->OP_Sapi             = VOS_TRUE;
    pApsMdfReq->ucSapi              = APS_SAPI_INIT;

    /*fill Qos*/
    if ( TAF_USED == g_TafCidTab[ucCid].ucQosTabFlag)
    {
        pApsMdfReq->Op_Qos          = VOS_TRUE;
        Taf_FillQos(&g_TafCidTab[ucCid], &pApsMdfReq->Qos);
    }

    /*fill Tft*/
    if ( TAF_USED == g_TafCidTab[ucCid].ucPfTabFlag)
    {
        pApsMdfReq->Op_Tft          = VOS_TRUE;
        ulReturn = Aps_FillTft(     &g_TafCidTab[ucCid],
                                    &pApsMdfReq->Tft);
        if ( TAF_APS_FAIL == ulReturn )
        {
            APS_WARN_LOG("Aps_FillTft ERR");
            return TAF_APS_FAIL;
        }
    }

    return  TAF_APS_SUCC;
}



/*****************************************************************************
 Prototype      : Aps_PsCallModify()
 Description    : PDP修改.该函数接收API输入的参数，将该参数适配成Aps_PdpMdfReq()
                  函数要求的接口参数,然后调用函数Aps_PdpMdfReq();基本继承V100R001
                  中Taf_PsCallProc()中case TAF_MSG_CGCMOD的代码.
 Input          : ucCid取值[1,11]和OxFF,当取值0xFF时，标识修改所有的CID
 Output         : NO
 Return Value   :
 Calls          : Aps_PackApsMdfReqPara()
                  Aps_PdpMdfReq()
 Called By      : TAFM
 History        : ---
  1.Date        : 2005-
    Author      : 韩鲁峰
    Modification: Created function

  2.日    期   : 2011年12月22日
    作    者   : A00165503
    修改内容   : PS Project: 修改PDP修改处理逻辑

*****************************************************************************/
VOS_VOID Aps_PsCallModify(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                          *pucError
)
{
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulResult;
    APS_PDP_MDF_REQ_ST                  ApsMdfReq;

    ulResult                            = TAF_APS_SUCC;
    ucCid                               = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /* 初始化 */
    *pucError       = TAF_ERR_NO_ERROR;
    ucCid           = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    PS_MEM_SET(&ApsMdfReq, 0x00, sizeof(ApsMdfReq));

    ulResult        = Aps_PackApsMdfReqPara(ucCid, ucPdpId, &ApsMdfReq);
    if (TAF_APS_FAIL == ulResult)
    {
       *pucError    = TAF_ERR_UNSPECIFIED_ERROR;
    }
    else
    {
        ulResult    = Aps_PdpMdfReq(&ApsMdfReq);
        if (TAF_APS_FAIL == ulResult)
        {
            APS_WARN_LOG("Aps_PdpMdfReq err ");
            *pucError = TAF_ERR_UNSPECIFIED_ERROR;
        }
    }

    return;
}

/*****************************************************************************
 Prototype      : Aps_PsCallEnd()
 Description    : PDP去激活.该函数接收API输入的参数，将该参数适配成Aps_PdpDeActReq()
                  函数要求的接口参数,然后调用函数Aps_PdpDeActReq();
 Input          : SM_TAF_CAUSE_ENUM_UINT16            enCause,
                  VOS_UINT8                           ucPdpId,
                  VOS_UINT8                          *pucError
 Output         : pucError
 Return Value   :
 Calls          : Aps_AppDeactReq()
                  TAF_APS_SndCidInactiveEvt
 Called By      : TAFM
 History        : ---
  1.Date        : 2005-
    Author      : 韩鲁峰
    Modification: Created function
*****************************************************************************/
VOS_VOID Aps_PsCallEnd(
    SM_TAF_CAUSE_ENUM_UINT16            enCause,
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                          *pucError
)
{
    VOS_UINT32                          ulResult;

    /* 初始化 */
    ulResult                            = VOS_OK;
    *pucError                           = TAF_ERR_NO_ERROR;

    /* 发起PDP去激活, 根据返回值填写错误码 */
    ulResult    = Aps_AppDeactReq(ucPdpId, enCause);
    if (VOS_OK != ulResult)
    {
        *pucError   = TAF_ERR_ERROR;
    }

    return;
}

/*****************************************************************************
 Prototype      : TAF_APS_SndCidInactiveEvt()
 Description    : 当某CID没有激活时，使用此函数上报CID去激活成功
 Input          :
 Output         : NO
 Return Value   : NO
 Data Accessed  : NO
 Data Update    : NO
 Calls          : Aps_ClearAppEvent()
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : 韩鲁峰
    Modification: Created function
  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，结构替换
*****************************************************************************/
VOS_VOID    TAF_APS_SndCidInactiveEvt(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT8                           ucCid )
{
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU  stCidDeActCnfEvt;

    PS_MEM_SET(&stCidDeActCnfEvt, 0, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));

    stCidDeActCnfEvt.stCtrl = *pstCtrl;
    stCidDeActCnfEvt.ucCid  = ucCid;

    /*调用TAFM提供的事件上报函数 */
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF,
                     &stCidDeActCnfEvt,
                     sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));

    APS_NORM_LOG("APS->APP ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF");
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */
    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_FindCidForDial
 功能描述  : 查找空闲的CID, 用于拨号
 输入参数  : entityState --- PDP实体状态
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月11日
    作    者   : s62952
    修改内容   : 新生成函数

  2.日    期   : 2012年01月01日
    作    者   : h44270
    修改内容   : PS Project: 修改判断当前APS实体状态的方式，删除middle pdp id的概念

  3.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : C50 IPv6 项目

  4.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，C核同步获取未使用的CID

*****************************************************************************/
#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT8 TAF_APS_FindCidForDial(VOS_UINT32  ulAppPid)
{
    VOS_UINT8                   ucPdpId;
    VOS_UINT8                   ucCid;
    TAF_APS_STA_ENUM_UINT32     enState;
    VOS_UINT8                   ucloop;
    VOS_UINT8                   ucValid;

    ucValid = VOS_FALSE;

    /* 来自于AT的拨号，CID获取从[12, 20]区间获取; 来自于IMSA的从[20->12]反向获取 */
    for (ucloop = 0; ucloop <= (APS_PDP_MAX_CID - APS_PDP_RESELECT_CID); ucloop++)
    {
#if (FEATURE_IMS == FEATURE_ON)
        if (PS_PID_IMSA == ulAppPid)
        {
            ucCid = APS_PDP_MAX_CID - ucloop;
        }
        else
#endif
        {
            ucCid = APS_PDP_RESELECT_CID + ucloop;
        }

        /* 遍历所有的PDP实体, 检查是否有非IDLE态的PDP正在使用该CID */
        for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
        {
            enState = TAF_APS_GetPdpIdMainFsmState(ucPdpId);
            if ((VOS_TRUE == TAF_APS_IsPdpEntBitCidMaskExit(ucPdpId, ucCid))
             && (TAF_APS_STA_INACTIVE != enState) )
            {
                break;
            }
        }

        if (ucPdpId >= TAF_APS_MAX_PDPID)
        {
            ucValid = VOS_TRUE;
            break;
        }
    }

    /* 检查CID是否有效 */
    if (VOS_TRUE != ucValid)
    {
        ucCid = TAF_INVALID_CID;
    }

    return ucCid;
}
#else
VOS_UINT8 TAF_APS_FindCidForDial(VOS_UINT32  ulAppPid)
{
    VOS_UINT8                   ucPdpId;
    VOS_UINT8                   ucCid;
    TAF_APS_STA_ENUM_UINT32     enState;
    VOS_UINT8                   ucValid;

    ucValid = VOS_FALSE;

    /* 获取cid */
    for (ucCid = TAF_MAX_CID; ucCid >= 1; ucCid--)
    {
        /* 遍历所有的PDP实体, 检查是否有非IDLE态的PDP正在使用该CID */
        for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
        {
            enState = TAF_APS_GetPdpIdMainFsmState(ucPdpId);
            if ((VOS_TRUE == TAF_APS_IsPdpEntBitCidMaskExit(ucPdpId, ucCid))
             && (TAF_APS_STA_INACTIVE != enState) )
            {
                break;
            }
        }

        if (ucPdpId >= TAF_APS_MAX_PDPID)
        {
            ucValid = VOS_TRUE;
            break;
        }
    }

    /* 检查CID是否有效 */
    if (VOS_TRUE != ucValid)
    {
        ucCid = TAF_INVALID_CID;
    }

    return ucCid;
}
#endif /* (FEATURE_ON == FEATURE_LTE) */


/*****************************************************************************
 函 数 名  : MN_APS_SetPdpContext
 功能描述  : 定义, 修改, 删除PDP CONTEXT, 包括对两个数据结构的操作, FLASH中
             PDP数据表和全局变量数据表.
 输入参数  : usClientId --- 识别某个应用程序
             ucOpId     --- 识别某个应用程序中的某次呼叫
             pstPdpPara --- 指向PDP CONTEXT主结构的指针;
                            没有PDP CONTEXT主结构参数IE，表示删除PDP CONTEXT;
                            有PDP CONTEXT主结构参数IE，表示定义或修改PDP CONTEXT,
                            已经定义了PDP CONTEXT则为修改，否则，为定义。
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月15日
    作    者   : s62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_APS_SetPdpContext(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt
)
{
    VOS_UINT32                          ulResult;

    ulResult                            = VOS_OK;

    if ( (VOS_NULL_PTR == pstPdpPrimContextExt)
      || (!TAF_PS_CID_VALID(pstPdpPrimContextExt->ucCid)) )
    {
        APS_WARN_LOG("Aps_DefPsPdpContext input para err!");
        return VOS_ERR;
    }

    /*将对应的项暂时保存到临时变量g_TmpPdpTab中*/
    g_TmpPdpTab = g_TafCidTab[pstPdpPrimContextExt->ucCid];

    /*根据pPara判断是否是删除PDP_PRI参数*/
    if (APS_PDPPRI_DELETE(pstPdpPrimContextExt))
    {
        /*删除PDP_PRI定义*/

        /*根据终端的要求，如果该指定删除的CID不处于APS_PDP_INACTIVE状态，
          则禁止做删除操作*/
        if (VOS_TRUE == Taf_CheckActCid(pstPdpPrimContextExt->ucCid))
        {
            MN_WARN_LOG("MN_APS_SetPdpContext: WARNING: Can't delete the Context of \
                         the CID which is not in APS_PDP_INACTIVE state!");
            return VOS_ERR;
        }

        /*如果该项的PDP_PRI参数子项已经定义*/
        if (VOS_TRUE == g_TmpPdpTab.ucUsed)
        {
            /*清除PDP的定义标识*/
            g_TafCidTab[pstPdpPrimContextExt->ucCid].ucUsed        = VOS_FALSE;

            /*该PDP可能是二次PDP，清除二次PDP的主PDP标识*/
            g_TafCidTab[pstPdpPrimContextExt->ucCid].ucPriCidFlag  = VOS_FALSE;
        }
        else
        {
            /*若本来就没有定义,则直接上报删除成功*/
            return VOS_OK;
        }
    }
    else
    {
        /*定义或者修改PDP_PRI参数*/
        ulResult = Aps_ChngPdpPri(pstPdpPrimContextExt, pstPdpPrimContextExt->ucCid);
        if (VOS_ERR == ulResult)
        {
            /*如果修改失败*/
            MN_WARN_LOG("MN_APS_SetPdpContext: WARNING: Aps_ChngPdpPri ERR!");
            g_TafCidTab[pstPdpPrimContextExt->ucCid] = g_TmpPdpTab;

            return VOS_ERR;
        }

        /*如果原来是二次PDP，则进行标识操作和必要参数的设置*/
        if (VOS_TRUE == g_TafCidTab[pstPdpPrimContextExt->ucCid].ucPriCidFlag)
        {
            g_TafCidTab[pstPdpPrimContextExt->ucCid].ucPriCidFlag  = VOS_FALSE;
        }

        /*AT或APP定义PdpPri参数时,对于没有输入的参数，用此函数进行缺省定义。*/
        Aps_DefPdpPri(pstPdpPrimContextExt, pstPdpPrimContextExt->ucCid);
    }

    ulResult = Aps_NvimAct(pstPdpPrimContextExt->ucCid);
    if (VOS_OK != ulResult)
    {
        /*操作NVIM失败，恢复原值*/
        MN_WARN_LOG("MN_APS_SetPdpContext: WARNING: NVIM ACT ERR!");
        g_TafCidTab[pstPdpPrimContextExt->ucCid] = g_TmpPdpTab;

        return VOS_ERR;
    }
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : MN_APS_SetPdpCidPara
 功能描述  : 设置PDP上下文
 输入参数  : VOS_UINT16                          usClientId
             TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月9日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年1月19日
    作    者   : H44270
    修改内容   : 删除多余的APN、IPV4转换，不需要将字符串转换为没有字符串结束符的参数形式
  3.日    期   : 2012年6月15日
    作    者   : m00217266
    修改内容   : 停止暂停PDP激活定时器(AT&T定制，PDP激活限制)

*****************************************************************************/
VOS_UINT32 MN_APS_SetPdpCidPara(
    VOS_UINT16                          usClientId,
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt
)
{
    TAF_PDP_PRIM_CONTEXT_EXT_STRU       stPdpPrimContextExt;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stPdpPrimContextExt, 0x00, sizeof(TAF_PDP_PRIM_CONTEXT_EXT_STRU));

    /*参数检查*/
    if (VOS_NULL == pstPdpPrimContextExt)
    {
        MN_ERR_LOG("MN_APS_SetPdpCidPara:the point pstPdpPrimContextExt is null");
        return VOS_ERR;
    }

    stPdpPrimContextExt = *pstPdpPrimContextExt;


    /* PDP激活受限特性打开，暂停激活定时器正在运行 */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_PDP_ACT_LIMIT_PDP_ID))
    {
        TAF_APS_RcvSetCidPara_PdpActLimit(&stPdpPrimContextExt);
    }


    ulResult = MN_APS_SetPdpContext(usClientId, 0, &stPdpPrimContextExt);

    return ulResult;
}

/*****************************************************************************
 函 数 名  : MN_APS_GetPdpCidPara
 功能描述  : 获取PDP CID表信息
 输入参数  : pstPdpCidInfo --- PDP CID表信息
             ucCid         --- CID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月9日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_APS_GetPdpCidPara(
    TAF_PDP_PRIM_CONTEXT_STRU                   *pstPdpCidInfo,
    VOS_UINT8                           ucCid
)
{
    TAF_PDP_TABLE_STRU                 *pstTafCidInfo;

    pstTafCidInfo = TAF_APS_GetTafCidInfoAddr(ucCid);

    if ((0 == ucCid) || (ucCid > TAF_MAX_CID))
    {
        MN_ERR_LOG("MN_APS_GetPdpCidPara: CID is invalid.");
        return VOS_ERR;
    }

    if (VOS_TRUE != pstTafCidInfo->ucUsed)
    {
        MN_ERR_LOG("MN_APS_GetPdpCidPara: CID tab is not defined.");
        PS_MEM_SET(pstPdpCidInfo, 0x00, sizeof(TAF_PDP_PRIM_CONTEXT_STRU));
    }
    else
    {
        *pstPdpCidInfo = pstTafCidInfo->CidTab;
    }

    return VOS_OK;
}

/*****************************************************************************
 Prototype      : Taf_GetCidType
 Description    : AT命令解释器调用此函数查看某CID定义的PDP类型.
 Input          : ucCid
 Output         : NO
 Return Value   : TAF_CIDTYPE_FAIL  0       输入的CID没有定义PDP,或CID不合法
                  TAF_PDP_IPV4      1       IPV4
                  TAF_PDP_PPP       4       PPP
 Data Accessed  :
 Data Updated   :
 Calls          :
 Called By      : ATC
 History        : ---
  1.Date        : 2005-
    Author      : hanlufeng
    Modification: Created function
  2.Date        : 2006-06-05
    Author      : L47619
    Modification: Modify for PN:A32D04462

  3.日    期   : 2011年10月23日
    作    者   : A00165503
    修改内容   : AT Project: 修改非法的PDP类型值为TAF_PDP_TYPE_BUTT(0xFF)

*****************************************************************************/
TAF_PDP_TYPE_ENUM_UINT8 Taf_GetCidType(VOS_UINT8 ucCid)
{
    if ( ucCid > TAF_MAX_CID )
    {
        return  TAF_PDP_TYPE_BUTT;
    }

    if ( 0 == ucCid )
    {
        return  TAF_PDP_IPV4;
    }

    if (VOS_TRUE != g_TafCidTab[ucCid].ucUsed)
    {
        /*没有定义*/
        return  TAF_PDP_TYPE_BUTT;
    }
    else
    {
        switch(g_TafCidTab[ucCid].CidTab.stPdpAddr.enPdpType)
        {
            case TAF_PDP_PPP:
            case TAF_PDP_IPV4:
#if (FEATURE_ON == FEATURE_IPV6)
            case TAF_PDP_IPV6:
            case TAF_PDP_IPV4V6:
#endif
                return  g_TafCidTab[ucCid].CidTab.stPdpAddr.enPdpType;

            default:
                return TAF_PDP_TYPE_BUTT;
        }
    }
}

/*****************************************************************************
 Prototype      : Taf_PsCallForDialParaCheck
 Description    :
 Input          : pPsDialPara
 Output         :
 Return Value   : TAF_PS_PARA_VALID、TAF_PS_PARA_INVALID
 Date Accessed  :
 Date Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT8   Taf_PsCallForDialParaCheck( PPP_REQ_CONFIG_INFO_STRU *pPsDialPara)
{
    if (TAF_NULL_PTR == pPsDialPara)
    {
        APS_NORM_LOG(" pPsDialPara is null !");
        return  TAF_PS_PARA_INVALID;
    }

    /*检查认证报文的合法性*/
    if ( PPP_PAP_AUTH_TYPE == pPsDialPara->stAuth.ucAuthType )
    {
        if ( (0 != pPsDialPara->stAuth.AuthContent.PapContent.usPapReqLen)
              && (TAF_NULL_PTR == pPsDialPara->stAuth.AuthContent.PapContent.pPapReq) )
        {
            APS_NORM_LOG(" pPsDialPara->stAuth.AuthContent.PapContent.pPapReq is null !");
            return  TAF_PS_PARA_INVALID;
        }
    }
    else if ( PPP_CHAP_AUTH_TYPE == pPsDialPara->stAuth.ucAuthType )
    {
        if ( (0 != pPsDialPara->stAuth.AuthContent.ChapContent.usChapChallengeLen)
              && (TAF_NULL_PTR == pPsDialPara->stAuth.AuthContent.ChapContent.pChapChallenge) )
        {
            APS_NORM_LOG(" pPsDialPara->stAuth.AuthContent.ChapContent.pChapChallenge is null !");
            return  TAF_PS_PARA_INVALID;
        }

        if ( (0 != pPsDialPara->stAuth.AuthContent.ChapContent.usChapResponseLen)
              && (TAF_NULL_PTR == pPsDialPara->stAuth.AuthContent.ChapContent.pChapResponse) )
        {
            APS_NORM_LOG(" pPsDialPara->stAuth.AuthContent.ChapContent.pChapResponse is null !");
            return  TAF_PS_PARA_INVALID;
        }
    }
    else if ( PPP_NO_AUTH_TYPE == pPsDialPara->stAuth.ucAuthType )
    {
        /*不鉴权*/
    }
    else
    {
        APS_NORM_LOG(" pPsDialPara->stAuth.ucAuthType is abnormal!");
        return  TAF_PS_PARA_INVALID;
    }

    /*检查IPCP报文的合法性*/
    if ( (0 != pPsDialPara->stIPCP.usIpcpLen ) && (TAF_NULL_PTR == pPsDialPara->stIPCP.pIpcp) )
    {
        APS_NORM_LOG(" pPsDialPara->stIPCP.pIpcp is null!");
        return  TAF_PS_PARA_INVALID;
    }


    if ( PPP_PAP_AUTH_TYPE == pPsDialPara->stAuth.ucAuthType )
    {
        if ( pPsDialPara->stAuth.AuthContent.PapContent.usPapReqLen
             > ( TAF_MAX_USERNAME_LEN + TAF_MAX_PASSCODE_LEN + TAF_PPP_HEADER_LEN) )
        {
            APS_NORM_LOG(" usPapReqLen is too long !");
            return  TAF_PS_PARA_INVALID;
        }
    }

    if( pPsDialPara->stIPCP.usIpcpLen > TAF_PPP_IPCP_MAX_LEN )
    {
        APS_NORM_LOG(" IPCP Lenth is too long!");
        return  TAF_PS_PARA_INVALID;
    }

    return  TAF_PS_PARA_VALID;
}
/* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */

#if(FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 函 数 名  : TAF_APS_SndGetLtecsInfoCnf
 功能描述  :
 输入参数  : TAF_CTRL_STRU                    *pstCtrl
             VOS_UINT32                          ulErrCode
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月19日
    作    者   : w00182550
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_APS_SndGetLtecsInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    TAF_PS_LTECS_CNF_STRU           stGetLtecsInfoCnf;

    stGetLtecsInfoCnf.stCtrl        = *pstCtrl;
    stGetLtecsInfoCnf.enCause       = ulErrCode;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_LTECS_INFO_CNF,
                               &stGetLtecsInfoCnf,
                               sizeof(TAF_PS_LTECS_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndGetCemodeInfoCnf
 功能描述  :
 输入参数  : TAF_CTRL_STRU                      *pstCtrl
             VOS_UINT32                          ulErrCode
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月19日
    作    者   : w00182550
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_APS_SndGetCemodeInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    TAF_PS_CEMODE_CNF_STRU              stGetCemodeInfoCnf;

    stGetCemodeInfoCnf.stCtrl           = *pstCtrl;
    stGetCemodeInfoCnf.enCause          = ulErrCode;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CEMODE_INFO_CNF,
                                &stGetCemodeInfoCnf,
                                sizeof(TAF_PS_CEMODE_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return;
}

VOS_VOID  TAF_APS_SndSetPdprofInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    TAF_PS_SET_PDP_PROF_INFO_CNF_STRU   stSetPdprofInfoCnf;

    stSetPdprofInfoCnf.stCtrl   = *pstCtrl;
    stSetPdprofInfoCnf.enCause  = ulErrCode;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_PDP_PROF_INFO_CNF,
                                &stSetPdprofInfoCnf,
                                sizeof(TAF_PS_SET_PDP_PROF_INFO_CNF_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return;
}
#endif

/* Add by w00199382 for V7代码同步, 2012-04-07, End   */


/*****************************************************************************
 函 数 名  : TAF_APS_IsApnChanged
 功能描述  : 比较指定CID的APN是否改变
 输入参数  : VOS_UINT8                           ucCid
             VOS_UINT32                          ulOpApn
             VOS_UINT8                          *pucApn
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月14日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目,修改APN结构

*****************************************************************************/
VOS_UINT32 TAF_APS_IsApnChanged(
    VOS_UINT8                           ucCid,
    VOS_UINT32                          ulOpApn,
    VOS_UINT8                          *pucApn
)
{
    VOS_UINT8                           aucNewApn[TAF_MAX_APN_LEN + 1];
    VOS_UINT8                           ucApnChangeFlg;

    ucApnChangeFlg = VOS_FALSE;

    /* 定义或修改APN */
    if (VOS_TRUE == ulOpApn)
    {
        /* 没有定义旧的APN*/
        if (VOS_FALSE == g_TafCidTab[ucCid].ucUsed)
        {
            ucApnChangeFlg = VOS_TRUE;
        }
        else
        {
            /* 获取新的APN */
            Aps_Str2LenStr(TAF_MAX_APN_LEN, pucApn, aucNewApn);


            /* 比较APN的长度是否改变，第一个字节表示长度 */
            if (aucNewApn[0] != TAF_APS_GetTafCidInfoApnLen(ucCid))
            {
                ucApnChangeFlg = VOS_TRUE;
            }
            else
            {
                /* 比较APN内容是否改变 */
                if (PS_MEM_CMP(TAF_APS_GetTafCidInfoApnData(ucCid), &aucNewApn[1], aucNewApn[0]))
                {
                    ucApnChangeFlg = VOS_TRUE;
                }
            }
        }
    }
    /* 删除APN */
    else
    {
        /* 存在定义旧的APN*/
        if ((VOS_TRUE == g_TafCidTab[ucCid].ucUsed)
         && (0 != TAF_APS_GetTafCidInfoApnLen(ucCid)))
        {
            ucApnChangeFlg = VOS_TRUE;
        }
    }

    return ucApnChangeFlg;
}
/*****************************************************************************
 函 数 名  : TAF_APS_RcvSetCidPara_PdpActLimit
 功能描述  : PDP激活受限特性打开，暂停激活定时器正在运行，修改APN的处理
 输入参数  : TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月21日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_RcvSetCidPara_PdpActLimit(
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt
)
{
    VOS_UINT32                          ulApnChangeFlg;

    ulApnChangeFlg = TAF_APS_IsApnChanged(pstPdpPrimContextExt->ucCid,
                                          pstPdpPrimContextExt->bitOpApn,
                                          pstPdpPrimContextExt->aucApn);

    if (VOS_TRUE == ulApnChangeFlg)
    {
        /* APN改变，停止暂停激活定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_PDP_ACT_LIMIT_PDP_ID);
    }

    return ;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSetPrimPdpCtxInfoReq_PdpActLimit
 功能描述  : PDP激活受限特性打开，暂停激活定时器正在运行，修改APN的处理
 输入参数  : TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU    *pstSetPdpCtxInfoReq
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月21日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_RcvSetPrimPdpCtxInfoReq_PdpActLimit(
    TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU    *pstSetPdpCtxInfoReq
)
{
    VOS_UINT32                          ulApnChangeFlg;

    ulApnChangeFlg = TAF_APS_IsApnChanged(pstSetPdpCtxInfoReq->stPdpContextInfo.ucCid,
                                          pstSetPdpCtxInfoReq->stPdpContextInfo.ucDefined,
                                          pstSetPdpCtxInfoReq->stPdpContextInfo.aucApn);

    if (VOS_TRUE == ulApnChangeFlg)
    {
        /* APN改变，停止暂停激活定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_PDP_ACT_LIMIT_PDP_ID);
    }

    return ;
}


/* Deleted by wx270776 for OM融合, 2015-7-24, begin */

/* Deleted by wx270776 for OM融合, 2015-7-24, end */

/*****************************************************************************
 函 数 名  : TAF_APS_SndDsFlowOMRptInd
 功能描述  : 将流量信息通过消息ID_NAS_OM_DSFLOW_RPT_IND主动上报到OM
 输入参数  : pstDsFlowRptInfo   --流量信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月09日
    作    者   : l00198894
    修改内容   : Probe路测工具对接项目新增

  2.日    期   : 2015年7月09日
    作    者   : wx270776
    修改内容   : OM融合
*****************************************************************************/
VOS_VOID TAF_APS_SndDsFlowOMRptInd(
    TAF_DSFLOW_REPORT_STRU             *pstDsFlowRptInfo
)
{
    /* Modified by wx270776 for OM融合, 2015-7-10, begin */
    NAS_OM_DSFLOW_RPT_IND_STRU          stDsflowRptInd;
    DIAG_TRANS_IND_STRU                 stSendOMDsFlowRptInd;
    VOS_UINT32                          ulRet;


    /* 初始化 */
    PS_MEM_SET(&stSendOMDsFlowRptInd, 0, sizeof(DIAG_TRANS_IND_STRU));

    PS_MEM_SET(&stDsflowRptInd, 0, sizeof(NAS_OM_DSFLOW_RPT_IND_STRU));

    stDsflowRptInd.usPrimId             = ID_NAS_OM_DSFLOW_RPT_IND;
    stDsflowRptInd.usToolsId            = 0;
    stDsflowRptInd.ulCurrentSendRate    = pstDsFlowRptInfo->ulCurrentSendRate;
    stDsflowRptInd.ulCurrentReceiveRate = pstDsFlowRptInfo->ulCurrentReceiveRate;
    stDsflowRptInd.ulDSLinkTime         = pstDsFlowRptInfo->stCurrentFlowInfo.ulDSLinkTime;
    stDsflowRptInd.ulDSSendFluxLow      = pstDsFlowRptInfo->stCurrentFlowInfo.ulDSSendFluxLow;
    stDsflowRptInd.ulDSSendFluxHigh     = pstDsFlowRptInfo->stCurrentFlowInfo.ulDSSendFluxHigh;
    stDsflowRptInd.ulDSReceiveFluxLow   = pstDsFlowRptInfo->stCurrentFlowInfo.ulDSReceiveFluxLow;
    stDsflowRptInd.ulDSReceiveFluxHigh  = pstDsFlowRptInfo->stCurrentFlowInfo.ulDSReceiveFluxHigh;

    /* 填写消息结构 */
    stSendOMDsFlowRptInd.ulModule     = DIAG_GEN_MODULE(VOS_GetModemIDFromPid(WUEPS_PID_TAF), DIAG_MODE_UMTS);
    stSendOMDsFlowRptInd.ulPid        = WUEPS_PID_TAF;
    stSendOMDsFlowRptInd.ulMsgId      = ID_NAS_OM_DSFLOW_RPT_IND;
    stSendOMDsFlowRptInd.ulLength     = sizeof(NAS_OM_DSFLOW_RPT_IND_STRU);
    stSendOMDsFlowRptInd.pData        = &stDsflowRptInd;

    /* 发送消息 */
    ulRet = DIAG_TransReport(&stSendOMDsFlowRptInd);
    if (VOS_OK != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_SndDsFlowOMRptInd: DIAG_TransReport Failed!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_FindCidForAns
 功能描述  : 查找空闲的CID, 用于应答
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月05日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_APS_FindCidForAns(VOS_VOID)
{
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
    TAF_APS_STA_ENUM_UINT32             enState;

    /* CID获取在LTE支持时, 从[21, 31]区间获取; 否则从[31, 21]反向获取 */
#if(FEATURE_ON == FEATURE_LTE)
    for (ucCid = APS_PDP_MAX_CID + 1; ucCid <= TAF_MAX_CID; ucCid++)
#else
    for (ucCid = TAF_MAX_CID; ucCid >= APS_PDP_MIN_CID; ucCid--)
#endif
    {
        /* 遍历所有的PDP实体, 检查是否有非IDLE态的PDP正在使用该CID */
        for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
        {
            enState = TAF_APS_GetPdpIdMainFsmState(ucPdpId);

            if ((VOS_TRUE == TAF_APS_IsPdpEntBitCidMaskExit(ucPdpId, ucCid))
             && (TAF_APS_STA_INACTIVE != enState))
            {
                break;
            }
        }

        if (ucPdpId >= TAF_APS_MAX_PDPID)
        {
            break;
        }
    }

    /* 检查CID是否有效 */
#if(FEATURE_ON == FEATURE_LTE)
    if (ucCid > TAF_MAX_CID)
#else
    if (ucCid < APS_PDP_MIN_CID)
#endif
    {
        ucCid = TAF_INVALID_CID;
    }

    return ucCid;
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetIpTypeAnsExtIpcpPara
 功能描述  : 生成应答IP类型网侧PDP激活的激活请求IPCP参数
 输入参数  : APS_PDP_ACT_REQ_ST                 *pstApsActReq
             TAF_PSCALL_FOR_DIAL_EXT_STRU         *pstApsDialReqPara
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月9日
    作    者   : #
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_GetIpTypeAnsExtIpcpPara(
    APS_PDP_ACT_REQ_ST                 *pstApsActReq,
    TAF_PSCALL_FOR_DIAL_EXT_STRU         *pstApsDialReqPara
)
{
    /*处理PdpDns*/
    if (APS_ADDR_PPP != pstApsActReq->ucPdpType)
    {
        if (VOS_TRUE == pstApsDialReqPara->OP_Dns)
        {
            /*如果输入了DNS,就使用输入的DNS*/
            pstApsActReq->OP_DNS          = VOS_TRUE;
            pstApsActReq->PdpDns          = pstApsDialReqPara->Dns;
        }
    }

    /*处理PdpNbns*/
    if (APS_ADDR_PPP != pstApsActReq->ucPdpType)
    {
        if (VOS_TRUE == pstApsDialReqPara->OP_Nbns)
        {
            /*如果输入了NBNS,就使用输入的NBNS*/
            pstApsActReq->OP_NBNS          = VOS_TRUE;
            pstApsActReq->PdpNbns          = pstApsDialReqPara->Nbns;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetIpTypeAnsExtAuthPara
 功能描述  : 生成应答IP类型网侧PDP激活的激活请求AUTH参数
 输入参数  : APS_PDP_ACT_REQ_ST                 *pstApsActReq
             TAF_PSCALL_FOR_DIAL_EXT_STRU         *pstApsDialReqPara
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月9日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_GetIpTypeAnsExtAuthPara(
    APS_PDP_ACT_REQ_ST                 *pstApsActReq,
    TAF_PSCALL_FOR_DIAL_EXT_STRU         *pstApsDialReqPara
)
{
    /* 处理ucUserAuthOrNot,aucUserName,aucPassword */
    if ((VOS_TRUE == pstApsDialReqPara->OP_Auth )
     && (APS_ADDR_PPP != pstApsActReq->ucPdpType))
    {
        /* 若输入了鉴权信息,则使用输入的鉴权信息 */
        pstApsActReq->OP_AUTH = VOS_TRUE;
        Aps_CopyAuthToActReqPara(&(pstApsDialReqPara->AuthPara),
                                 &(pstApsActReq->PdpAuth));
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_MakeIpTypeAnsExtActReq
 功能描述  : 生成应答IP类型网侧PDP激活的激活请求参数
 输入参数  : VOS_UINT8                           ucPdpId
             TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq
             APS_PDP_ACT_REQ_ST                 *pApsActReq
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月9日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_MakeIpTypeAnsExtActReq(
    VOS_UINT8                           ucPdpId,
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq,
    APS_PDP_ACT_REQ_ST                 *pstApsActReq
)
{
    PPP_REQ_CONFIG_INFO_STRU            stPppConfigInfo;
    TAF_PSCALL_FOR_DIAL_EXT_STRU        stApsDialReqPara;

    PS_MEM_SET(&stApsDialReqPara, 0x00, sizeof(TAF_PSCALL_FOR_DIAL_EXT_STRU));

    pstApsActReq->OP_APN              = VOS_FALSE;
    pstApsActReq->OP_AUTH             = VOS_FALSE;
    pstApsActReq->OP_DNS              = VOS_FALSE;
    pstApsActReq->OP_NBNS             = VOS_FALSE;
    pstApsActReq->OP_Sapi             = VOS_FALSE;
    pstApsActReq->Op_Xid_DCmp         = VOS_FALSE;
    pstApsActReq->Op_Xid_PCmp         = VOS_FALSE;
    pstApsActReq->OP_SPARE            = VOS_FALSE;

    pstApsActReq->ucPdpId             = ucPdpId;

    /* SAPI */
    pstApsActReq->OP_Sapi             = VOS_TRUE;
    pstApsActReq->ucSapi              = APS_SAPI_INIT;

    /* 默认不鉴权 */
    pstApsActReq->PdpAuth.AuthType    = TAF_PCO_NOT_AUTH;

    /* 网络激活时以网络携带的地址类型和地址内容为准 */
    pstApsActReq->ucPdpType    = g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum;
    pstApsActReq->aucIpAddr[0] = g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr[0];
    pstApsActReq->aucIpAddr[1] = g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr[1];
    pstApsActReq->aucIpAddr[2] = g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr[2];
    pstApsActReq->aucIpAddr[3] = g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr[3];

    /* 网络激活时以网络携带的APN内容为准 */
    if ((VOS_TRUE == g_PdpEntity[ucPdpId].PdpApnFlag)
     && (0 != g_PdpEntity[ucPdpId].PdpApn.ucLength))
    {
        pstApsActReq->OP_APN = VOS_TRUE;

        if (g_PdpEntity[ucPdpId].PdpApn.ucLength > TAF_MAX_APN_LEN)
        {
            g_PdpEntity[ucPdpId].PdpApn.ucLength = TAF_MAX_APN_LEN;
        }

        pstApsActReq->aucApn[0] = g_PdpEntity[ucPdpId].PdpApn.ucLength;

        PS_MEM_CPY(&pstApsActReq->aucApn[1],
                   g_PdpEntity[ucPdpId].PdpApn.aucValue,
                   pstApsActReq->aucApn[0]);
    }

    /*没有定义QOS，则填网络决定*/
    Taf_FillQos(&g_TafCidTab[0], &pstApsActReq->ReqQos);

    /* 生成AUTH/IPCP */
    PS_MEM_SET(&stPppConfigInfo, 0x00, sizeof(PPP_REQ_CONFIG_INFO_STRU));

    if (VOS_OK == MN_APS_PppCovertConfigInfo(&stPppConfigInfo,
                                             &pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo))
    {
        if (TAF_PS_PARA_VALID == Taf_PsCallForDialParaCheck(&stPppConfigInfo))
        {
            /*从IPCP的码流中拆出REQ的IPCP信息码流,并填到 ApsDilaPara中*/
            Aps_GetIpcpInfo(&stPppConfigInfo, &stApsDialReqPara);

            TAF_APS_GetIpTypeAnsExtIpcpPara(pstApsActReq, &stApsDialReqPara);

            /*从IPCP的码流中拆出REQ的AUTH信息码流,并填到 ApsDilaPara中*/
            if (TAF_APS_SUCC == Aps_GetAuthInfo(&stPppConfigInfo, &stApsDialReqPara))
            {
               TAF_APS_GetIpTypeAnsExtAuthPara(pstApsActReq, &stApsDialReqPara);
            }
        }

        /* 释放生成的鉴权信息 */
        MN_APS_CtrlFreePCOContext(&stPppConfigInfo);
    }

    /*填充完毕，直接返回成功*/
    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetPdpCidQosPara
 功能描述  : 获取指定CID的QOS参数
 输入参数  : TAF_PS_PDP_QOS_PARA_STRU           *pstQosPara
             VOS_UINT8                           ucCid
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月29日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_GetPdpCidQosPara(
    TAF_PS_PDP_QOS_QUERY_PARA_STRU     *pstQosPara,
    VOS_UINT8                           ucCid
)
{
    TAF_UMTS_QOS_QUERY_INFO_STRU        stQosPara;
    TAF_UMTS_QOS_QUERY_INFO_STRU        stMinQosPara;
    VOS_UINT32                          ulErrCode;

    PS_MEM_SET(&stQosPara, 0, sizeof(TAF_UMTS_QOS_QUERY_INFO_STRU));
    PS_MEM_SET(&stMinQosPara, 0, sizeof(TAF_UMTS_QOS_QUERY_INFO_STRU));

    /* 参数有效性检查 */
    if ((0 == ucCid) || (ucCid > TAF_MAX_CID))
    {
        MN_ERR_LOG("TAF_APS_GetPdpCidQosPara: CID is invalid.");
        return VOS_ERR;
    }

    /* 获取QOS参数 */
    MN_APS_GetUtmsQosInfo(ucCid, &stQosPara, &ulErrCode);

    if (TAF_PARA_OK == ulErrCode)
    {
        pstQosPara->ucQosFlag = VOS_TRUE;
        PS_MEM_CPY(&(pstQosPara->stQos), &(stQosPara.stQosInfo), sizeof(TAF_UMTS_QOS_STRU));
    }

    MN_APS_GetUtmsQosMinInfo(ucCid, &stMinQosPara, &ulErrCode);

    if (TAF_PARA_OK == ulErrCode)
    {
        pstQosPara->ucMinQosFlag = VOS_TRUE;
        PS_MEM_CPY(&(pstQosPara->stMinQos), &(stMinQosPara.stQosInfo), sizeof(TAF_UMTS_QOS_STRU));
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SetPdpCidQosPara
 功能描述  : 设置指定CID的QOS参数
 输入参数  : TAF_PS_PDP_QOS_SET_PARA_STRU       *pstQosPara
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月29日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_SetPdpCidQosPara(
    TAF_PS_PDP_QOS_SET_PARA_STRU       *pstQosPara
)
{
    VOS_UINT32                          ulErrCode;

    ulErrCode = TAF_PARA_OK;

    Aps_DefPs3gReqQos(0, 0, &(pstQosPara->stQos), &ulErrCode);

    if (TAF_PARA_OK != ulErrCode)
    {
        return VOS_ERR;
    }

    Aps_DefPs3gMinAcceptQos(0, 0, &(pstQosPara->stMinQos), &ulErrCode);

    if (TAF_PARA_OK != ulErrCode)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


#if (FEATURE_IMS == FEATURE_ON)
/*****************************************************************************
 函 数 名  : TAF_APS_SndImsaSrvccCancelNotify
 功能描述  : APS发送消息给IMSA通知SRVCC CANCEL
 输入参数  : enNotificationIndicator
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月18日
    作    者   : Y00213812
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_APS_SndImsaSrvccCancelNotify(
    TAF_SRVCC_CANCEL_NOTIFY_ENUM_UINT32   enNotificationIndicator
)
{
    TAF_SRVCC_CANCEL_NOTIFY_IND_STRU    stApsNotiInd;

    /* 初始化消息 */
    PS_MEM_SET(&stApsNotiInd,
               0x00,
               sizeof(TAF_SRVCC_CANCEL_NOTIFY_IND_STRU));

    /* 填写消息头 */
    stApsNotiInd.stCtrl.ulModuleId          = PS_PID_IMSA;

    /* 填写事件内容 */
    stApsNotiInd.enNotificationIndicator    = enNotificationIndicator;

    /* 发送事件 */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SRVCC_CANCEL_NOTIFY_IND,
                     &stApsNotiInd,
                     sizeof(TAF_SRVCC_CANCEL_NOTIFY_IND_STRU));

    return;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_APS_SndSetCqosPriCnf
 功能描述  : 返回AT^CQOSPRI的AT命令执行结果，上报AT
 输入参数  : TAF_CTRL_STRU                    *pstCtrl,
             VOS_UINT32                        ulErrCode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月22日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_SndSetCqosPriCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT32                        ulErrCode
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_SET_CQOS_PRI_CNF_STRU        stSetCqosPriCnf;

    stSetCqosPriCnf.stCtrl = *pstCtrl;
    stSetCqosPriCnf.ulRslt = ulErrCode;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_CQOS_PRI_CNF,
                                &stSetCqosPriCnf,
                                sizeof(TAF_PS_SET_CQOS_PRI_CNF_STRU));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndSetPktCdataInactivityTimerLenCnf
 功能描述  : 返回AT+CTA的AT命令执行结果，上报AT
 输入参数  : TAF_CTRL_STRU                    *pstCtrl,
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月21日
    作    者   : c00299063
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_SndSetPktCdataInactivityTimerLenCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_SET_CTA_INFO_CNF_STRU        stGetPktCdataInactivityTimeLenCnf;

    stGetPktCdataInactivityTimeLenCnf.stCtrl = *pstCtrl;
    stGetPktCdataInactivityTimeLenCnf.ulRslt = ulErrCode;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_CTA_INFO_CNF,
                                &stGetPktCdataInactivityTimeLenCnf,
                                sizeof(stGetPktCdataInactivityTimeLenCnf));

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndGetPktCdataInactivityTimerLenCnf
 功能描述  : 返回AT+CTA的AT命令执行结果，上报AT
 输入参数  : TAF_CTRL_STRU                    *pstCtrl,
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月21日
    作    者   : c00299063
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_SndGetPktCdataInactivityTimerLenCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT8                           ucTimeLen,
    VOS_UINT32                          ulErrCode
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_GET_CTA_INFO_CNF_STRU        stGetPktCdataInactivityTimeLenCnf ;

    stGetPktCdataInactivityTimeLenCnf.stCtrl                     = *pstCtrl;
    stGetPktCdataInactivityTimeLenCnf.ucPktCdataInactivityTmrLen = ucTimeLen;
    stGetPktCdataInactivityTimeLenCnf.ulRslt                     = ulErrCode;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_CTA_INFO_CNF,
                                &stGetPktCdataInactivityTimeLenCnf,
                                sizeof(stGetPktCdataInactivityTimeLenCnf));

    return ulResult;
}

/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

