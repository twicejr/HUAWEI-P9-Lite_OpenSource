

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "MM_Inc.h"
#include "MmGsmDifMsg.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_MM_GSMDIFMSG_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/



/*****************************************************************************
   2 全局变量定义
*****************************************************************************/

/*****************************************************************************
   3 函数实现
*****************************************************************************/



/*lint -save -e958 */


/*****************************************************************************
 Prototype      : MM_RcvGsmRrcPagingInd
 Description    : GSM 下 Paging 消息结构的处理
 Input          : pRcvMsg 收到的原语头指针
 Output         :
 Return Value   : MM_TRUE 消息接收成功
                  MM_FALSE 消息接收失败
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2005-08-19
    Author      : s46746
    Modification: Created function
*****************************************************************************/
VOS_UINT8 MM_RcvGsmRrcPagingInd(VOS_VOID *pRcvMsg)
{

    /* 返回值变量 */
    VOS_UINT8                           ucRet = MM_TRUE;

    /* 定义接收到的消息类型指针 */
    GRRMM_PAGING_IND_ST                *pMsg;

    /* 消息转换 */
    pMsg = (GRRMM_PAGING_IND_ST *)pRcvMsg;

    /* 对消息合法性检查 */
    if ((MM_CONST_NUM_1 < pMsg->ucPagingType)
        || (MM_CONST_NUM_2 < pMsg->ucMSIDType)) /* 消息中的取值不合法 */
    {
        /* 返回消息检查失败 */
        ucRet = MM_FALSE;

        /* 打印出错信息 */
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_RcvGsmRrcPagingInd: ERROR: Receive GRRMM_PAGING_IND error.");

    }
    else /* 消息合法 */
    {
        /* 存储消息中相关信息 */
        if ((GAS_TMSI == pMsg->ucMSIDType)
            || (GAS_PTMSI == pMsg->ucMSIDType)) /* 呼叫类型为 GAS_TMSI 或 GAS_PTMSI */
        {
            /* 设置全局呼叫类型为 MM_TMSI_PAGING */
            g_MmGlobalInfo.ucPagingRecordTypeId = MM_TMSI_PAGING;
        }
        else if (GAS_IMSI == pMsg->ucMSIDType) /* 呼叫类型为 GAS_IMSI */
        {
            /* 设置全局呼叫类型为 MM_IMSI_PAGING */
            g_MmGlobalInfo.ucPagingRecordTypeId = MM_IMSI_PAGING;
        }
        else
        {

        }
    }

    /* 返回检查结果 */
    return ucRet;
}

/* 4 GSM消息 GAS_RR_SYNC_IND 的实现 */
/* 修改 MAPS1000 中函数 Mm_RcvRrcSyncInd */
/*VOS_UINT8 Mm_RcvRrcSyncInd(void *pRcvMsg             收到的原语头指针 * ) */
/* 见文件 Mm_Rcv.c                                                            */

/*****************************************************************************
 Prototype      : MM_RcvGsmRrcSyncInd
 Description    : GSM 下 sync 消息结构的处理
 Input          : pRcvMsg  收到的原语头指针
 Output         :
 Return Value   : MM_TRUE 消息接收成功
                  MM_FALSE 消息接收失败
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2005-08-19
    Author      : s46746
    Modification: Created function
*****************************************************************************/
VOS_UINT8 MM_RcvGsmRrcSyncInd(VOS_VOID *pRcvMsg)
{

    /* 返回值变量 */
    VOS_UINT8                           ucRet = MM_TRUE;

    /* 定义接收到的消息类型指针 */
    GAS_RR_SYNC_IND_ST                 *pMsg;

    /* 消息转换 */
    pMsg = (GAS_RR_SYNC_IND_ST *)pRcvMsg;

    /* 对同步信息的分析处理 */
    if (RR_SYN_CIPH == pMsg->ucSynCause) /* 加密已经启动 */
    {
        g_RrMmSyncInd.ulRabCnt                              = MM_CONST_NUM_0;

        g_MmGlobalInfo.CsSecutityInfo.ucSecurityType        = RR_SYN_CIPH;

        /*g_MmGlobalInfo.CsSecutityInfo.ucSecutityFlg         = RRC_CIPHER_START;*/

        /* 依据 ucSynValue 设置全局加密算法 */
        g_MmGlobalInfo.ucCsCipherAlgor                      = pMsg->ucSynValue;
    }
#if 0
    else if (RR_SYN_TCH == pMsg->ucSynCause) /* 业务通道已经指定 */
    {
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_NORMAL,
                    "MM_RcvGsmRrcSyncInd: NORMAL: Sync channal mode res.");

        g_MmGlobalInfo.CsSecutityInfo.ucSecurityType        = RR_SYN_TCH;
    }
    else if (RR_SYN_TCH_MODIFY == pMsg->ucSynCause) /* 业务通道模式修改 */
    {
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_NORMAL,
                    "MM_RcvGsmRrcSyncInd: NORMAL: Sync channal mode change.");

        g_MmGlobalInfo.CsSecutityInfo.ucSecurityType        = RR_SYN_TCH_MODIFY;
    }
    else if ((RR_SYN_GSM_GSM_HANDOVER == pMsg->ucSynCause)
          || (RR_SYN_WCDMA_GSM_HANDOVER == pMsg->ucSynCause))
    {
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_NORMAL,
                    "MM_RcvGsmRrcSyncInd: NORMAL: Sync channal mode change.");

        g_MmGlobalInfo.CsSecutityInfo.ucSecurityType        = RR_SYN_TCH_MODIFY;
    }
    else /* 错误情况 */
    {
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_RcvGsmRrcSyncInd: ERROR: Sync cause is unexpected!");

        ucRet = MM_FALSE;
    }

    if ((MM_FALSE != ucRet) && (RR_SYN_CIPH != pMsg->ucSynCause))
    {
        g_RrMmSyncInd.ulRabCnt                     = MM_CONST_NUM_1;
        g_RrMmSyncInd.NasSyncInfo[0].ulRabId       = MM_CONST_NUM_1;
        g_RrMmSyncInd.NasSyncInfo[0].ulCnDomainId  = RRC_NAS_CS_DOMAIN;
        /* 与MMCC_SYNC_IND消息中原因值保持一致 */
        g_RrMmSyncInd.NasSyncInfo[0].ulReason      = (VOS_UINT32)(pMsg->ucSynCause - 1);
        g_RrMmSyncInd.ulChannelMode                = (VOS_UINT32)pMsg->ucSynValue;
        g_RrMmSyncInd.ulTchRate                    = (VOS_UINT32)pMsg->ucTchRate;

        /* 是否是消息中的同步原因，存在疑问 */
        g_RrMmSyncInd.NasSyncInfo[0].ulRabSyncInfo = MM_CONST_NUM_1;
    }
#endif

    /* 返回结果 */
    return ucRet;
}



VOS_UINT32 MM_SupplementNsdInfo(VOS_UINT8 *pData)
{
    VOS_UINT8 ucPd;

    ucPd = pData[0] & MM_IE_PD_MASK;
    if ((MM_IE_PD_MM_MSG == ucPd) || (MM_IE_PD_CALL_CONTROL == ucPd)
       || (MM_IE_PD_NON_CALL_RLT_SS_MSG == ucPd))
    {
        pData[1] |= (VOS_UINT8)(g_stMmNsd.ucNsd << 6);
        return MM_TRUE;
    }

    return MM_FALSE;
}


VOS_INT32 MM_WasRrDataReq(VOS_UINT8 ucCnDomain, VOS_UINT8 ucPriority,
                          VOS_UINT32 ulSize, VOS_INT8 *pData)
{

    VOS_INT32                           lRet;
    VOS_UINT32                          ulRet = MM_FALSE;

    if (VOS_NULL_PTR != pData)
    {
        ulRet = MM_SupplementNsdInfo((VOS_UINT8 *)pData);
    }

    lRet = As_RrDataReq(ucCnDomain, ucPriority, ulSize, pData);

    if ((MM_TRUE == ulRet) && (MM_TRUE == lRet))
    {
        g_stMmNsd.ucNsd ++;
        g_stMmNsd.ucNsd = g_stMmNsd.ucNsd % g_stMmNsd.ucNsdMod;
    }

    return lRet;
}



VOS_INT32 MM_GasRrDataReq(VOS_UINT8 ucCnDomain, VOS_UINT8 ucPriority,
                          VOS_UINT32 ulSize, VOS_INT8 *pData)
{
    /* 定义调用VOS发送函数的返回值               */
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulTmp = MM_FALSE;

    /* 定义数据长度                              */
    VOS_UINT32                          ulTmpSize;

    /* 定义原语类型指针                          */
    RRMM_DATA_REQ_STRU                 *pMsg;

    /* 从形参中获得数据长度                      */
    ulTmpSize       = ulSize;
    /* 最少发送四个字节数据                      */
    if (ulTmpSize < 4)
    {
        ulTmpSize   = 4;
    }

    /* PS 域数据请求                             */
    if (RRC_NAS_PS_DOMAIN == ucCnDomain)
    {
        /* 打印出错信息 */
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_GasRrDataReq: ERROR: Ps data req.");

        /* 返回                                  */
        return MM_FALSE;
    }

    /* CS 域数据请求                             */
    /* 申请内存空间                              */
    pMsg = (RRMM_DATA_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                       (sizeof(RRMM_DATA_REQ_STRU) + ulTmpSize) - 4);

    /* 申请内存失败                              */
    if (VOS_NULL_PTR == pMsg)
    {
        /* 打印出错信息 */
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_GasRrDataReq: ERROR: Alloc memory fail.");

        /* 返回                                  */
        return MM_FALSE;
    }

    /* 填充消息头                                */
    pMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid       = UEPS_PID_GAS;
    pMsg->MsgHeader.ulMsgName           = RRMM_DATA_REQ;

    /* CN 域                                     */
    pMsg->ulCnDomainId                  = ucCnDomain;
    /* 优先级                                    */
    pMsg->ulPriorityInd                 = ucPriority;
    /* 数据长度                                  */
    pMsg->SendNasMsg.ulNasMsgSize       = ulSize;
    /* 将数据拷贝到消息中                        */

    if (VOS_NULL_PTR != pData)
    {
        PS_MEM_CPY(pMsg->SendNasMsg.aucNasMsg, pData, ulSize);
        ulTmp = MM_SupplementNsdInfo(pMsg->SendNasMsg.aucNasMsg);
    }

    /* 发送消息                                  */
    ulRet = PS_SEND_MSG(WUEPS_PID_MM, pMsg);
    /* 发送失败                                  */
    if (VOS_OK != ulRet)
    {
        /* 打印出错信息 */
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_GasRrDataReq: ERROR: Send Msg fail.");

        /* 返回                                  */
        return MM_FALSE;
    }

    if (MM_TRUE == ulTmp)
    {
        g_stMmNsd.ucNsd ++;
        g_stMmNsd.ucNsd = g_stMmNsd.ucNsd % g_stMmNsd.ucNsdMod;
    }

    /* 返回                                      */
    return MM_TRUE;
}


VOS_INT32 MM_WasRrEstReq(VOS_UINT32 ulOpId, VOS_UINT8 ucCnDomain,
                         VOS_UINT32 ulEstCause, IDNNS_STRU *pIdnnsInfo, RRC_PLMN_ID_STRU *pstPlmnId,
                         VOS_UINT32 ulSize, VOS_INT8 *pFisrstMsg)
{
    VOS_INT32                           lRet;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulCallType;

    g_stMmNsd.ucNsd = MM_NSD_INITAL_VALUE;

    ulRet = MM_FALSE;
    if (VOS_NULL_PTR != pFisrstMsg)
    {
        ulRet = MM_SupplementNsdInfo((VOS_UINT8 *)pFisrstMsg);
    }

    if ( ( RRC_EST_CAUSE_ORIGIN_CONVERSAT_CALL == ulEstCause )
      || ( RRC_EST_CAUSE_CALL_RE_ESTABLISH == ulEstCause ))
    {
        ulCallType = g_MmCcEstReq.ulCallMode;
    }
    else if (( RRC_EST_CAUSE_REGISTRATION == ulEstCause )
          || ( RRC_EST_CAUSE_DETACH == ulEstCause ))
    {
        ulCallType = RRC_NAS_CALL_TYPE_OTHER;
    }
    else
    {
        ulCallType = RRC_NAS_CALL_TYPE_SPEECH;
    }

    lRet = As_RrEstReq(ulOpId, ucCnDomain, ulEstCause,ulCallType, pIdnnsInfo, pstPlmnId, ulSize, pFisrstMsg);

    if ((MM_TRUE == ulRet) && (MM_TRUE == lRet))
    {
        g_stMmNsd.ucNsd ++;
    }

    return lRet;
}



VOS_INT32 MM_GasRrEstReq(VOS_UINT32 ulOpId, VOS_UINT8 ucCnDomain,
                         VOS_UINT32 ulEstCause, IDNNS_STRU *pIdnnsInfo, RRC_PLMN_ID_STRU *pstPlmnId,
                         VOS_UINT32 ulSize, VOS_INT8 *pFisrstMsg)
{
    /* 定义调用VOS发送函数的返回值               */
    VOS_UINT32                          ulRet;

    /* 定义原语类型指针                          */
    RRMM_EST_REQ_STRU                  *pMsg;

    /* 定义数据长度                              */
    VOS_UINT32                          ulTmpSize;

    /* 从形参中获得数据长度                      */
    ulTmpSize = ulSize;
    /* 最少发送四个字节数据                      */
    if (ulTmpSize < 4)
    {
        ulTmpSize = 4;
    }

    /* PS 域数据请求                             */
    if (RRC_NAS_PS_DOMAIN == ucCnDomain)
    {
        /* 打印出错信息 */
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_GasRrEstReq: ERROR: Ps data req.");

        /* 返回                                  */
        return MM_FALSE;
    }

    /* 申请内存空间                              */
    pMsg = (RRMM_EST_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                       (sizeof(RRMM_EST_REQ_STRU) + ulTmpSize) - 4);
    if ( VOS_NULL_PTR == pMsg )
    {
        /* 打印出错信息 */
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_GasRrEstReq: ERROR: Alloc memory fail.");

        /* 返回                                  */
        return MM_FALSE;
    }

    /* 填充消息头                                */
    pMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid       = UEPS_PID_GAS;
    pMsg->MsgHeader.ulMsgName           = RRMM_EST_REQ;

    /* 操作标识                                  */
    pMsg->ulOpId                        = ulOpId;
    /* CN 域                                     */
    pMsg->ulCnDomainId                  = ucCnDomain;
    /* 建立原因                                  */
    pMsg->ulEstCause                    = ulEstCause;
    pMsg->enCallType                    = RRC_NAS_CALL_TYPE_SPEECH;
    /* IDDN参数,GAS不使用，保持接口一致 */
    pMsg->ulIdnnsType                   = pIdnnsInfo->ucIdnnsType;
    pMsg->enSplmnSameRplmn              = pIdnnsInfo->ucEnterPara;

    PS_MEM_CPY(&pMsg->stPlmnId, pstPlmnId, sizeof(RRC_PLMN_ID_STRU));

    /* NAS 第一条消息长度                        */
    pMsg->FisrtNasMsg.ulNasMsgSize      = ulSize;
    /* 将数据拷贝到消息中                        */
    if (VOS_NULL_PTR != pFisrstMsg)
    {
        PS_MEM_CPY(pMsg->FisrtNasMsg.aucNasMsg, pFisrstMsg, ulSize);
    }
    else
    {
        PS_MEM_SET(pMsg->FisrtNasMsg.aucNasMsg, 0x00, 4);
    }

    /* 调用函数发送消息                          */
    ulRet = PS_SEND_MSG(WUEPS_PID_MM, pMsg);
    /* 发送失败                                  */
    if (VOS_OK != ulRet)
    {
        /* 打印出错信息 */
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_GasRrEstReq: ERROR: Send Msg fail.");

        return MM_FALSE;
    }

    g_stMmNsd.ucNsd = MM_NSD_INITAL_VALUE;

    if (VOS_NULL_PTR != pFisrstMsg)
    {
        g_stMmNsd.ucNsd ++;
    }

    /* 成功返回                                  */
    return MM_TRUE;
}


VOS_INT32 MM_GasRrRelReq(VOS_UINT8 ucCnDomain,RRC_CELL_BAR_ENUM_UINT32 enBarValidFlg)
{
    /* 定义调用VOS发送函数的返回值               */
    VOS_UINT32                          ulRet;

    /* 定义原语类型指针                          */
    RRMM_REL_REQ_STRU                  *pMsg;

    /* PS 域数据请求                             */
    if (RRC_NAS_PS_DOMAIN == ucCnDomain)
    {
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_GasRrRelReq: ERROR: Ps release RR connect req.");

        /* 返回                                  */
        return MM_FALSE;
    }

    /* 申请内存空间                              */
    pMsg = (RRMM_REL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                       sizeof(RRMM_REL_REQ_STRU));
    if (VOS_NULL_PTR == pMsg)
    {
        /* 打印出错信息 */
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_GasRrRelReq: ERROR: Alloc memory fail.");

        /* 返回                                  */
        return MM_FALSE;
    }

    /* 填充消息头                                */
    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = UEPS_PID_GAS;
    pMsg->MsgHeader.ulMsgName           = RRMM_REL_REQ;

    /* CN 域                                     */
    pMsg->ulCnDomainId                  = ucCnDomain;
    /* 当前小区或激活集小区阻塞标志 */
    pMsg->enBarValidFlg                 = enBarValidFlg;
    /* 调用函数发送消息                          */
    ulRet = PS_SEND_MSG(WUEPS_PID_MM, pMsg);
    /* 发送失败                                  */
    if (VOS_OK != ulRet)
    {
        /* 打印出错信息 */
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_GasRrRelReq: ERROR: Send Msg fail.");

        /* 返回                                  */
        return MM_FALSE;
    }

    /* 成功返回                                  */
    return MM_TRUE;
}


/* 6.MM 实体提供给 GAS 获取安全信息的API函数 */


VOS_VOID MM_GetSecurityInfo(MM_CSPS_INFO_ST *pCsInfo)
{
    VOS_UINT8                          *pucImsi = VOS_NULL_PTR;

    if (VOS_NULL_PTR == pCsInfo)
    {
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_GetSecurityInfo: ERROR: Para check error!");

        return;
    }

    /* 将全局结构中相应信息拷贝到结构 pCsInfo 中 */
    /* 初始化结构中 InfoMask 变量 */
    pCsInfo->ucInfoMask = 0x0;

    if (VOS_FALSE == NAS_MML_GetSimPresentStatus()) /* 卡不存在 */
    {
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_INFO,
                    "MM_GetSecurityInfo: INFO: SIM is not present!");

        return;
    }

    /* 拷贝 Ck、Ik 和 Kc */
    pCsInfo->ucInfoMask |= 0x1F;
    PS_MEM_CPY(pCsInfo->aucCk, NAS_MML_GetSimCsSecurityUmtsCk(), NAS_MML_UMTS_CK_LEN);

    PS_MEM_CPY(pCsInfo->aucIk, NAS_MML_GetSimCsSecurityUmtsIk(), NAS_MML_UMTS_IK_LEN);

    PS_MEM_CPY(pCsInfo->aucKc, NAS_MML_GetSimCsSecurityGsmKc(), NAS_MML_GSM_KC_LEN);

    /* 获取 IMSI */
    pucImsi = NAS_MML_GetSimImsi();
    PS_MEM_CPY(pCsInfo->aucImsi, pucImsi + 1, RRC_NAS_IMSI_MAX_LEN);

    pCsInfo->ucCksn = NAS_MML_GetSimCsSecurityCksn();
    if ( MM_MS_ID_TMSI_PRESENT & g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg )
    {
        pCsInfo->ucInfoMask |= MM_SECURITY_P_TMSI_MASK;

        PS_MEM_CPY(pCsInfo->aucPTMSI,
                   NAS_MML_GetUeIdTmsi(),
                   NAS_MML_MAX_TMSI_LEN);
    }

    return;
}


/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
