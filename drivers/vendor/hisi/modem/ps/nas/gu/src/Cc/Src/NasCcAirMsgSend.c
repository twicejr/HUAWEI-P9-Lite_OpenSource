/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasCcAirMsgSend.c
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年10月16日
  最近修改   : 2007年10月16日
  功能描述   : 发送空口消息
  函数列表   :
  修改历史   :
  1.日    期   : 2007年10月16日
    作    者   : 丁庆 49431
    修改内容   : 创建文件

  2.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级

  3.日    期   : 2010年8月4日
    作    者   : zhoujun /40661
    修改内容   : 支持UUS

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasCcInclude.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif


/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_NASCC_AIRMSGSEND_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*lint -save -e958 */

/*****************************************************************************
  2 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : NAS_CC_FillCauseIe
 功能描述  :
 输入参数  : enCauseVal - 原因值
 输出参数  : pstCauseIe - 填好的Cause IE
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_CC_FillCauseIe(
    NAS_CC_CAUSE_VALUE_ENUM_U32          enCauseVal,
    NAS_CC_IE_CAUSE_STRU                *pstCauseIe
)
{
    NAS_IE_SET_PRESENT(pstCauseIe);


    pstCauseIe->IsExist = VOS_TRUE;

    /* Set octet3 to 0xe0:
           Coding standard: GSM
           Location :       User
           No extended octet
    */
    NAS_IE_SET_OCTET(pstCauseIe, Octet3, 0xe0);

    pstCauseIe->Octet4.CauseValue = enCauseVal;
    pstCauseIe->Octet4.Ext = NAS_CC_IE_NO_EXT;

    NAS_IE_SET_LAST_OCTET_OFFSET(pstCauseIe, Octet4);
}


/*****************************************************************************
 函 数 名  : NAS_CC_SendConnectAck
 功能描述  : 发送Connect acknowladge消息
 输入参数  : ucTi - Transaction ID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2015年4月2日
    作    者   : w00316404
    修改内容   : clean coverity
*****************************************************************************/
VOS_VOID  NAS_CC_SendConnectAck(
    VOS_UINT8                           ucTi
)
{
    VOS_UINT8                           aucData[NAS_CC_MAX_AIR_MSG_LEN];
    VOS_UINT8                           ucLen;
    NAS_CC_MSG_CONNECT_ACK_STRU         stConn;

    ucLen = 0;
    
    PS_MEM_SET(&stConn, 0, sizeof(stConn));

    NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_CONNECT_ACK, &stConn.stHeader);

    NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&stConn, aucData, &ucLen);

    NAS_CC_SendMmccDataReq(ucTi, aucData, ucLen);
}


/*****************************************************************************
 函 数 名  : NAS_CC_SendDisconnect
 功能描述  : 发送Disconnect消息
 输入参数  : ucTi       - Transaction ID
              enCauseVal - 挂断的原因值
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_VOID  NAS_CC_SendDisconnect(
    VOS_UINT8                           ucTi,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCauseVal
)
{
    VOS_UINT8                           aucData[NAS_CC_MAX_AIR_MSG_LEN];
    VOS_UINT8                           ucLen;
    NAS_CC_MSG_DISCONNECT_MO_STRU       stDisc;
    NAS_CC_ENTITY_ID_T                  entityId;


    ucLen = 0;

    PS_MEM_SET(&stDisc, 0, sizeof(stDisc));

    NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_DISCONNECT, &stDisc.stHeader);
    NAS_CC_FillCauseIe(enCauseVal, &stDisc.stCause);

    entityId = NAS_CC_GetEntityByTi(ucTi);

    /* 判断UUS1是否激活 */
    NAS_CC_GetMsgUus1Info(entityId,NAS_CC_MSG_DISCONNECT,&stDisc.stUserUser);

    NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&stDisc, aucData, &ucLen);

    NAS_CC_SendMmccDataReq(ucTi, aucData, ucLen);
}


/*****************************************************************************
 函 数 名  : NAS_CC_SendRelease
 功能描述  : 发送Release消息
 输入参数  : ucTi          - Transaction ID
             bCausePresent - 是否在release消息中携带原因
             enCauseVal    - 挂断的原因值
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_VOID  NAS_CC_SendRelease(
    VOS_UINT8                           ucTi,
    VOS_BOOL                            bCausePresent,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCauseVal,
    VOS_BOOL                            bCause2Present,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause2Val
)
{
    VOS_UINT8                           aucData[NAS_CC_MAX_AIR_MSG_LEN];
    VOS_UINT8                           ucLen;
    NAS_CC_MSG_RELEASE_MO_STRU          stRel;
    NAS_CC_ENTITY_ID_T                  entityId;


    ucLen = 0;
    PS_MEM_SET(&stRel, 0, sizeof(stRel));

    NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_RELEASE, &stRel.stHeader);
    if (bCausePresent)
    {
        NAS_CC_FillCauseIe(enCauseVal, &stRel.stCause);
    }

    if (bCause2Present)
    {
        NAS_CC_FillCauseIe(enCause2Val, &stRel.stCause2);
    }

    entityId = NAS_CC_GetEntityByTi(ucTi);

    /* 判断UUS1是否激活 */
    NAS_CC_GetMsgUus1Info(entityId,NAS_CC_MSG_RELEASE,&stRel.stUserUser);

    NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&stRel, aucData, &ucLen);

    NAS_CC_SendMmccDataReq(ucTi, aucData, ucLen);
}


/*****************************************************************************
 函 数 名  : NAS_CC_SendReleaseComplete
 功能描述  : 发送release complete消息
 输入参数  : ucTi          - Transaction ID
              bCausePresent - 是否在release complete消息中携带原因
              enCauseVal    - 挂断的原因值
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_VOID  NAS_CC_SendReleaseComplete(
    VOS_UINT8                           ucTi,
    VOS_BOOL                            bCausePresent,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCauseVal
)
{
    VOS_UINT8                           aucData[NAS_CC_MAX_AIR_MSG_LEN];
    VOS_UINT8                           ucLen;
    NAS_CC_MSG_RELEASE_COMPLETE_MO_STRU stRelCom;
    NAS_CC_ENTITY_ID_T                  entityId;


    ucLen = 0;
    PS_MEM_SET(&stRelCom, 0, sizeof(stRelCom));

    NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_RELEASE_COMPLETE, &stRelCom.stHeader);
    if (bCausePresent)
    {
        NAS_CC_FillCauseIe(enCauseVal, &stRelCom.stCause);
    }

    entityId = NAS_CC_GetEntityByTi(ucTi);

    /* 获取激活信息 */
    NAS_CC_GetMsgUus1Info(entityId,NAS_CC_MSG_RELEASE_COMPLETE,&stRelCom.stUserUser);

    NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&stRelCom, aucData, &ucLen);

    NAS_CC_SendMmccDataReq(ucTi, aucData, ucLen);
}


/*****************************************************************************
 函 数 名  : NAS_CC_SendStartDtmf
 功能描述  : 发送Start Dtmf消息
 输入参数  : ucTi  - Transaction ID
             ucKey - 要发送的DTMF字符
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月15日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_VOID  NAS_CC_SendStartDtmf(
    VOS_UINT8                           ucTi,
    VOS_UINT8                           ucKey
)
{
    VOS_UINT8                           aucData[NAS_CC_MAX_AIR_MSG_LEN];
    VOS_UINT8                           ucLen;
    NAS_CC_MSG_START_DTMF_STRU          stStartDtmf;


    ucLen = 0;
    PS_MEM_SET(&stStartDtmf, 0, sizeof(stStartDtmf));

    NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_START_DTMF, &stStartDtmf.stHeader);
    stStartDtmf.stKeypadFacility.IsExist = VOS_TRUE;
    stStartDtmf.stKeypadFacility.KeypadInfo = ucKey;

    NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&stStartDtmf, aucData, &ucLen);

    NAS_CC_SendMmccDataReq(ucTi, aucData, ucLen);
}


/*****************************************************************************
 函 数 名  : NAS_CC_SendStopDtmf
 功能描述  : 发送Stop Dtmf消息
 输入参数  : ucTi  - Transaction ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月15日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_VOID  NAS_CC_SendStopDtmf(
    VOS_UINT8                           ucTi
)
{
    VOS_UINT8                           aucData[NAS_CC_MAX_AIR_MSG_LEN];
    VOS_UINT8                           ucLen;
    NAS_CC_MSG_STOP_DTMF_STRU           stStopDtmf;


    ucLen = 0;

    PS_MEM_SET(&stStopDtmf, 0, sizeof(stStopDtmf));

    NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_STOP_DTMF, &stStopDtmf.stHeader);

    NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&stStopDtmf, aucData, &ucLen);

    NAS_CC_SendMmccDataReq(ucTi, aucData, ucLen);
}



/*****************************************************************************
 函 数 名  : NAS_CC_SendStatus
 功能描述  : 发送status消息
 输入参数  : ucTi          - Transaction ID
             enCauseVal    - 发送status的原因
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_VOID  NAS_CC_SendStatus(
    VOS_UINT8                           ucTi,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCauseVal
)
{
    VOS_UINT8                           aucData[NAS_CC_MAX_AIR_MSG_LEN];
    VOS_UINT8                           ucLen;
    NAS_CC_MSG_STATUS_STRU              stStatus;

    NAS_CC_CALL_STATE_ENUM_U8           enCallState;
    NAS_CC_HOLD_AUX_STATE_ENUM_U8       enHoldState;
    NAS_CC_MPTY_AUX_STATE_ENUM_U8       enMptyState;

    NAS_CC_ENTITY_ID_T  entityId = NAS_CC_GetEntityByTi(ucTi);

    ucLen = 0;

    if (entityId != NAS_CC_INVALID_ENTITY_ID)
    {
        enCallState = NAS_CC_GetCallState(entityId);
        enHoldState = NAS_CC_GetHoldAuxState(entityId);
        enMptyState = NAS_CC_GetMptyAuxState(entityId);
    }
    else
    {
        enCallState = NAS_CC_CALL_STATE_U0;
        enHoldState = NAS_CC_HOLD_AUX_S_IDLE;
        enMptyState = NAS_CC_MPTY_AUX_S_IDLE;
    }

    PS_MEM_SET(&stStatus, 0, sizeof(stStatus));

    NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_STATUS, &stStatus.stHeader);
    stStatus.stCallState.IsExist = VOS_TRUE;
    stStatus.stCallState.CodingStd = NAS_CC_CODING_GSM;
    stStatus.stCallState.CallState = enCallState;

    /*
    [9.3.27.1 Auxiliary states]
    The information element is included if and only if the call state is "active"
    or "mobile originating modify" and any auxiliary state is different from "idle".
    */
    if (((NAS_CC_CALL_STATE_U10 == enCallState)
       || (NAS_CC_CALL_STATE_U26 == enCallState))
     && ((NAS_CC_HOLD_AUX_S_IDLE != enHoldState)
       || (NAS_CC_MPTY_AUX_S_IDLE != enMptyState)))
    {
        stStatus.stAuxState.IsExist = VOS_TRUE;
        stStatus.stAuxState.HoldAuxState = enHoldState;
        stStatus.stAuxState.MptyAuxState = enMptyState;
        stStatus.stAuxState.Ext = NAS_CC_IE_NO_EXT;
    }

    NAS_CC_FillCauseIe(enCauseVal, &stStatus.stCause);

    NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&stStatus, aucData, &ucLen);

    NAS_CC_SendMmccDataReq(ucTi, aucData, ucLen);
}

/*****************************************************************************
 函 数 名  : NAS_CC_SendMmccStartCcReq
 功能描述  : 发送start cc消息
 输入参数  : ucTi - Transaction ID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009-12-25
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
 VOS_VOID NAS_CC_SendMmccStartCcReq(
             VOS_UINT8                           ucTi
)
{
    NAS_CC_MSG_START_CC_STRU            stStartCc;
    VOS_UINT8                           aucData[NAS_CC_MAX_AIR_MSG_LEN];
    VOS_UINT8                           ucLen;


    ucLen = 0;
    PS_MEM_SET(&stStartCc,0,sizeof(stStartCc));

    /* 填写start cc 消息头 */
    NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_START_CC, &stStartCc.stHeader);

    /* 编码start cc消息 */
    NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&stStartCc,aucData,&ucLen);

    /* 发送MMCC_START_CC原语将消息发往网络 */
    NAS_CC_SendMmccStartCc(ucTi, aucData, ucLen);

}

/*lint -restore */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

