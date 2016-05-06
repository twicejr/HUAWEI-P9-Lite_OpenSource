/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnMsgSendSms.c
  版 本 号   : 初稿
  作    者   : 周君 40661
  生成日期   : 2008年2月21日
  最近修改   :
  功能描述   : 实现MSG模块发送消息到nas层sms模块的函数接口
  函数列表   :
  修改历史   :
  1.日    期   : 2008年2月21日
    作    者   : 周君 40661
    修改内容   : 创建文件
  2.日    期   : 2009年3月23日
    作    者   : f62575
    修改内容   : AT2D08752, W接入方式下，信号较弱时连续发送多条短信会概率性出现发送操作失败；

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "MnMsgInclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_MNMSG_SENDSMS_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*lint -save -e958 */


/*****************************************************************************
  2 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : MN_MSG_SendSmsRpDataReq
 功能描述  : 发送Rp-Data数据到NAS层的SMS模块
 输入参数  : enSendDomain:Rp-Data的发送域
             pucSendMsg:发送数据的内容,具体为协议24011中RP-Data的内容
             ucSendLen:pucSendMsg的长度
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2013年7月10日
    作    者   : y00245242
    修改内容   : 增加SMS发送路由判断，决定SMS发送给IMS栈还是PS栈    
*****************************************************************************/
VOS_UINT32 MN_MSG_SendSmsRpDataReq(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enSendDomain,
    const VOS_UINT8                     *pucSendMsg ,
    VOS_UINT8                           ucSendLen,
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType    
)
{
    VOS_UINT32                          ulLen;
    SMT_SMR_DATA_STRU                   *pstSendMsg ;

    ulLen = ((ucSendLen + sizeof(MN_MSG_SEND_DOMAIN_ENUM_U8)) + sizeof(SMT_SMR_DATA_STRU)) - 4;
    pstSendMsg = (SMT_SMR_DATA_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,ulLen);
    if (VOS_NULL_PTR == pstSendMsg)
    {
        MN_WARN_LOG("MN_MSG_SendSmsRpDataReq:ERROR: VOS_AllocMsg fails");
        return VOS_ERR;
    }

/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-10, begin */
    pstSendMsg->ulSenderCpuId = VOS_LOCAL_CPUID;
    pstSendMsg->ulSenderPid = WUEPS_PID_TAF;
    pstSendMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSendMsg->ulDataLen = ucSendLen;
    pstSendMsg->aucData[0] = enSendDomain;
    if(0 != ucSendLen)
    {
        PS_MEM_CPY(&pstSendMsg->aucData[1] ,pucSendMsg,ucSendLen);
    }

#if (FEATURE_ON == FEATURE_IMS)
    if (TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP == enMsgSignallingType)
    {
        pstSendMsg->ulReceiverPid = PS_PID_IMSA;
        pstSendMsg->ulMsgName     = ID_MSG_IMSA_RP_DATA_REQ;
    }
    else
#endif    
    {
        pstSendMsg->ulReceiverPid = WUEPS_PID_SMS;
        pstSendMsg->ulMsgName = SMT_SMR_DATA_REQ;    
    }

    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_TAF, pstSendMsg ) )
    {
        MN_WARN_LOG( "MN_MSG_SendSmsRpDataReq:WARNING:SEND SMT_SMR_DATA_STRU msg FAIL!" );
        return VOS_ERR;
    }    
/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-10, end */

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : MN_MSG_SendSmsCpAckReq
 功能描述  : 发送CP-ACK数据到NAS层的SMS模块
 输入参数  : enSendDomain:Rp-Data的发送域
             pucSendMsg:发送数据的内容,具体为协议24011中RP-Data的内容
             ucSendLen:pucSendMsg的长度
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_SendSmsCpAckReq(VOS_VOID)
{
    SMT_SMR_DATA_STRU                   *pstSendMsg ;

    pstSendMsg = (SMT_SMR_DATA_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF, sizeof(SMT_SMR_DATA_STRU));
    if (VOS_NULL_PTR == pstSendMsg)
    {
        MN_WARN_LOG("MN_MSG_SendSmsRpDataReq:ERROR: VOS_AllocMsg fails");
        return;
    }
    PS_MEM_SET(pstSendMsg->aucData, 0x00, 4);
    pstSendMsg->ulSenderCpuId = VOS_LOCAL_CPUID;
    pstSendMsg->ulSenderPid = WUEPS_PID_TAF;
    pstSendMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSendMsg->ulReceiverPid = WUEPS_PID_SMS;
    pstSendMsg->ulMsgName = SMT_SMR_CP_ACK_REQ;
    pstSendMsg->ulDataLen = 0;

    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_SMS, pstSendMsg ) )
    {
        MN_WARN_LOG( "MN_MSG_SendSmsRpDataReq:WARNING:SEND SMT_SMR_DATA_STRU msg FAIL!" );
        return;
    }
    return;
}

/*****************************************************************************
 函 数 名  : MN_MSG_SendSmsRpReportReq
 功能描述  : 发送Rp-Report数据到NAS层的SMS模块
 输入参数  : pSendMsg:发送数据的内容,具体为协议24011中RP-ACK或RP-ERROR的内容
             ucSendLen:发送数据的长度
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2013年7月10日
    作    者   : y00245242
    修改内容   : 增加SMS发送路由判断，决定SMS发送给IMS栈还是PS栈
*****************************************************************************/
VOS_UINT32 MN_MSG_SendSmsRpReportReq(
    const VOS_UINT8                    *pucSendMsg ,
    VOS_UINT8                           ucSendLen,
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType
)
{
    VOS_UINT32                          ulLen ;
    SMT_SMR_DATA_STRU                   *pstSendMsg;

    ulLen = (sizeof(SMT_SMR_DATA_STRU) - 4) + ucSendLen ;
    pstSendMsg = (SMT_SMR_DATA_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,ulLen);
    if (VOS_NULL_PTR == pstSendMsg)
    {
        MN_WARN_LOG("MN_MSG_SendSmsRpReportReq:ERROR: VOS_AllocMsg fails");
        return VOS_ERR;
    }
    pstSendMsg->ulSenderCpuId = VOS_LOCAL_CPUID;
    pstSendMsg->ulSenderPid = WUEPS_PID_TAF;
    pstSendMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
 
/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-10, begin */
#if (FEATURE_ON == FEATURE_IMS)    
    if (TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP == enMsgSignallingType)
    {
        pstSendMsg->ulReceiverPid = PS_PID_IMSA;
        pstSendMsg->ulMsgName = ID_MSG_IMSA_REPORT_REQ;
    }
    else
#endif    
    {
        pstSendMsg->ulReceiverPid = WUEPS_PID_SMS;
        pstSendMsg->ulMsgName = SMT_SMR_REPORT_REQ;
    }
/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-10, end */

    pstSendMsg->ulDataLen = ucSendLen;
    PS_MEM_CPY(pstSendMsg->aucData ,pucSendMsg,ucSendLen);

/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-10, begin */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_TAF, pstSendMsg ) )
/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-10, end */
    {
        MN_WARN_LOG( "MN_MSG_SendSmsRpReportReq:WARNING:SEND SMT_SMR_DATA_STRU msg FAIL!" );
        return VOS_ERR;
    }
    return VOS_OK;
}

/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-10, begin */
/*****************************************************************************
 函 数 名  : MN_MSG_SendSmsSmmaReq
 功能描述  : 发送SMMA消息到NAS层的SMS模块
 输入参数  : enSendDomain:Rp-Data的发送域
             pSendMsg:发送数据的内容,具体为协议24011中RP-Data的内容
             ucSendLen:pucSendMsg的长度
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2012年12月28日
    作    者   : 傅映君/f62575
    修改内容   : DTS2012122406218, 短信正向质量发现问题: 短信发送流程部分
  3.日    期   : 2013年7月3日
    作    者   : y00245242
    修改内容   : 增加SMS发送路由判断，决定SMS发送给IMS栈还是PS栈    
*****************************************************************************/
VOS_UINT32 MN_MSG_SendSmsSmmaReq(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enSendDomain,
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType
)
{
    SMT_SMR_SMMA_STRU                   *pstSmaMsg;

    pstSmaMsg = (SMT_SMR_SMMA_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,sizeof(SMT_SMR_SMMA_STRU));
    if (VOS_NULL_PTR == pstSmaMsg)
    {
        MN_WARN_LOG("MN_MSG_SendSmsSmmaReq:ERROR: VOS_AllocMsg fails");
        return VOS_ERR;
    }
    pstSmaMsg->ulSenderCpuId = VOS_LOCAL_CPUID;
    pstSmaMsg->ulSenderPid = WUEPS_PID_TAF;
    pstSmaMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSmaMsg->ucSendDomain = enSendDomain;
    pstSmaMsg->ucAbortFlg = SMT_SMR_ABORT_FLG_NO_EXIST;
    PS_MEM_SET(pstSmaMsg->aucReserve1, 0, sizeof(pstSmaMsg->aucReserve1));
    
    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, begin */
#if (FEATURE_ON == FEATURE_IMS)    
    if (TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP == enMsgSignallingType)
    {
        pstSmaMsg->ulReceiverPid = PS_PID_IMSA;
        pstSmaMsg->ulMsgName = ID_MSG_IMSA_SMMA_REQ; 
    }
    else
#endif    
    {
        pstSmaMsg->ulReceiverPid = WUEPS_PID_SMS;
        pstSmaMsg->ulMsgName = SMT_SMR_SMMA_REQ; 
    }

    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_TAF, pstSmaMsg ) )
    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, end */
    {
        MN_WARN_LOG( "MN_MSG_SendSmsSmmaReq:WARNING:SEND SMT_SMR_SMMA_STRU msg FAIL!" );
        return VOS_ERR;
    }
    return VOS_OK;
}
/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-10, end */

/*****************************************************************************
 函 数 名  : MN_MSG_EncodeRpData
 功能描述  : 根据24011中Rp-Data的结构构造一条Rp-Data的字节流
 输入参数  : stRpData:24011中Rp-Data的结构
 输出参数  : pucRpduContent:Rp-Data的字节流的内容
             pucRpduLen:Rp-Data的字节流的长度
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_MSG_EncodeRpData(
    const MN_MSG_RP_DATA_STRU           *pstRpData,
    VOS_UINT8                           *pucRpduContent,
    VOS_UINT8                           *pucRpduLen
)
{
    VOS_UINT32                          ulPos = 0;

    *pucRpduContent = pstRpData->ucRpMsgType;
    ulPos = sizeof(pstRpData->ucRpMsgType);
    *(pucRpduContent + ulPos) = pstRpData->ucRpMr;
    ulPos += sizeof(pstRpData->ucRpMr);
    /*RP Originator Address 大于 1个字节*/
    if (pstRpData->stOrgAddr.ucBcdLen > 0)
    {
        *(pucRpduContent + ulPos) = pstRpData->stOrgAddr.ucBcdLen + 1;
        ulPos += sizeof(pstRpData->stOrgAddr.ucBcdLen);
        *(pucRpduContent + ulPos) = pstRpData->stOrgAddr.addrType;
        ulPos += sizeof(pstRpData->stOrgAddr.addrType);
        PS_MEM_CPY(pucRpduContent + ulPos,pstRpData->stOrgAddr.aucBcdNum,pstRpData->stOrgAddr.ucBcdLen);
        ulPos += pstRpData->stOrgAddr.ucBcdLen;
    }
    else
    {
        *(pucRpduContent + ulPos) = pstRpData->stOrgAddr.ucBcdLen;
        ulPos += sizeof(pstRpData->stOrgAddr.ucBcdLen);
    }

    /*RP Destination Address 大于 1个字节*/
    if (pstRpData->stDestAddr.ucBcdLen > 0)
    {
        *(pucRpduContent + ulPos) = pstRpData->stDestAddr.ucBcdLen + 1;
        ulPos += sizeof(pstRpData->stDestAddr.ucBcdLen);
        *(pucRpduContent + ulPos) = pstRpData->stDestAddr.addrType;
        ulPos += sizeof(pstRpData->stDestAddr.addrType);
        PS_MEM_CPY(pucRpduContent + ulPos,pstRpData->stDestAddr.aucBcdNum,pstRpData->stDestAddr.ucBcdLen);
        ulPos += pstRpData->stDestAddr.ucBcdLen;
    }
    else
    {
        *(pucRpduContent + ulPos) = pstRpData->stDestAddr.ucBcdLen;
        ulPos += sizeof(pstRpData->stDestAddr.ucBcdLen);
    }

    *(pucRpduContent + ulPos) = pstRpData->ucRpUserDataLen;
    ulPos += sizeof(pstRpData->ucRpUserDataLen);
    PS_MEM_CPY(pucRpduContent + ulPos,pstRpData->aucRpUserData,pstRpData->ucRpUserDataLen);
    ulPos += pstRpData->ucRpUserDataLen;

    *pucRpduLen = (VOS_UINT8)ulPos;
}

/*****************************************************************************
 函 数 名  : MN_MSG_EncodeRpAck
 功能描述  : 根据24011中Rp-ACK的结构构造一条Rp-ACK的字节流
 输入参数  : pstRpAck:24011中Rp-ACK的结构
 输出参数  : pucRpduContent:Rp-ACK的字节流的内容
             pucRpduLen:Rp-ACK的字节流的长度
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_MSG_EncodeRpAck(
    const MN_MSG_RP_ACK_STRU            *pstRpAck,
    VOS_UINT8                           *pucRpduContent,
    VOS_UINT8                           *pucRpduLen
)
{
    VOS_UINT32                          ulPos = 0;

    *pucRpduContent = pstRpAck->ucRpMsgType;
    ulPos = sizeof(pstRpAck->ucRpMsgType);
    *(pucRpduContent + ulPos) = pstRpAck->ucRpMr;
    ulPos += sizeof(pstRpAck->ucRpMr);

    /*存在RP User Data*/
    if (VOS_TRUE == pstRpAck->bRpUserDataExist)
    {
       *(pucRpduContent + ulPos) = pstRpAck->ucRpUserDataIei;
       ulPos += sizeof(pstRpAck->ucRpUserDataIei);
       *(pucRpduContent + ulPos) = pstRpAck->ucRpUserDataLen;
       ulPos += sizeof(pstRpAck->ucRpUserDataLen);
       PS_MEM_CPY(pucRpduContent + ulPos,pstRpAck->aucRpUserData,pstRpAck->ucRpUserDataLen);
       ulPos += pstRpAck->ucRpUserDataLen;
    }
    *pucRpduLen = (VOS_UINT8)ulPos;
}

/*****************************************************************************
 函 数 名  : MN_MSG_EncodeRpErr
 功能描述  : 根据24011中Rp-Error的结构构造一条Rp-Error的字节流
 输入参数  : pstRpErr:24011中Rp-Error的结构
 输出参数  : pucRpduContent:Rp-Error的字节流的内容
             pucRpduLen:Rp-Error的字节流的长度
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_MSG_EncodeRpErr(
    const MN_MSG_RP_ERR_STRU            *pstRpErr,
    VOS_UINT8                           *pucRpduContent,
    VOS_UINT8                           *pucRpduLen
)
{
    VOS_UINT32                          ulPos = 0;

    *pucRpduContent = pstRpErr->ucRpMsgType;
    ulPos = sizeof(pstRpErr->ucRpMsgType);
    *(pucRpduContent + ulPos) = pstRpErr->ucRpMr;
    ulPos += sizeof(pstRpErr->ucRpMr);
    *(pucRpduContent + ulPos) = pstRpErr->ucRpCauseLen;
    ulPos += sizeof(pstRpErr->ucRpCauseLen);
    *(pucRpduContent + ulPos) = pstRpErr->stRpCause.enRpCause;
    ulPos += sizeof(pstRpErr->stRpCause.enRpCause);
    /*Rp-Cause中存在Diagnostics Field*/
    if (VOS_TRUE == pstRpErr->stRpCause.bDiagnosticsExist)
    {
        *(pucRpduContent + ulPos) = pstRpErr->stRpCause.ucDiagnostics;
        ulPos += sizeof(pstRpErr->stRpCause.ucDiagnostics);
    }
    /*存在RP User Data*/
    if (VOS_TRUE == pstRpErr->bRpUserDataExist)
    {
       *(pucRpduContent + ulPos) = pstRpErr->ucRpUserDataIei;
       ulPos += sizeof(pstRpErr->ucRpUserDataIei);
       *(pucRpduContent + ulPos) = pstRpErr->ucRpUserDataLen;
       ulPos += sizeof(pstRpErr->ucRpUserDataLen);
       PS_MEM_CPY(pucRpduContent + ulPos,pstRpErr->aucRpUserData,pstRpErr->ucRpUserDataLen);
       ulPos += pstRpErr->ucRpUserDataLen;
    }
    *pucRpduLen = (VOS_UINT8)ulPos;
}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

