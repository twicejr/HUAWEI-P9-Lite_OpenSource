
#include  "PsTypeDef.h"
#include  "PsCommonDef.h"
#include  "Nasrrcinterface.h"
#include  "NasPdcpInterface.h"
#include  "asnasapi.h"


#include "TTFMem.h"
#include "NasRlcInterface.h"
#include "NasUtranCtrlInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_ASN_ASAPI_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/
extern VOS_UINT8  NAS_GetRbTxMode(VOS_UINT32 ulDomain, VOS_INT8    cRbId);

/*lint -save -e958 */


VOS_INT32 NAS_PsDomainTcDataReq(
    VOS_UINT8                           ucRbId,
    VOS_UINT32                          ulDataBitLen,
    TTF_MEM_ST                         *pstDataMem
)
{
    RABM_PDCP_TC_DATA_REQ_STRU *pMsg;
    VOS_UINT32                  ulRet;

    if (WUE_RLC_MODE_BUTT == NAS_GetRbTxMode(RRC_NAS_PS_DOMAIN, (VOS_INT8)ucRbId))
    {
        return AS_RB_NO_EXIST;
    }

    pMsg = (RABM_PDCP_TC_DATA_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
        WUEPS_PID_RABM,sizeof(RABM_PDCP_TC_DATA_REQ_STRU));
    if( VOS_NULL_PTR == pMsg )
    {
        return AS_NO_MEMORY;
    }

    PS_MEM_SET((VOS_INT8*)pMsg + VOS_MSG_HEAD_LENGTH,0,
         sizeof(RABM_PDCP_TC_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pMsg->ulSenderPid     = WUEPS_PID_RABM;
    pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->ulReceiverPid   = WUEPS_PID_PDCP;
    pMsg->ulLength        = sizeof(RABM_PDCP_TC_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pMsg->enMsgName       = ID_RABM_PDCP_TC_DATA_REQ;
    pMsg->ucRbId          = ucRbId;
    pMsg->pstDataMem      = pstDataMem;
    pMsg->ulDataBitLen    = ulDataBitLen;

    if (VOS_NULL_PTR == pMsg->pstDataMem)
    {
        /*释放消息结构体*/
        PS_FREE_MSG(WUEPS_PID_RABM, pMsg);

        return AS_NO_MEMORY;
    }

    ulRet = PS_SEND_MSG(WUEPS_PID_RABM, pMsg);
    if ( VOS_OK != ulRet )
    {
        PS_NAS_LOG(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_ERROR,
                "NAS_PsDomainTcDataReq, Error, call PS_SEND_MSG fail\n");
    }
    return AS_SUCCESS;
}


VOS_INT32 NAS_CsDomainDataReq(
                       VOS_INT8   cRbId,
                       VOS_UINT32 ulDataLength,
                       VOS_UINT8  *pucData
                       )
{
    RABM_RLC_TM_DATA_REQ_STRU *pTmMsg;
    RABM_RLC_UM_DATA_REQ_STRU *pUmMsg;
    RABM_RLC_AM_DATA_REQ_STRU *pAmMsg;
    VOS_UINT32 ulLenOct;
    VOS_UINT8   ucRbMode;
    VOS_VOID *pMsg;
    TTF_MEM_ST *pData;

    ucRbMode = NAS_GetRbTxMode(RRC_NAS_CS_DOMAIN, cRbId);

    switch(ucRbMode)
    {
    case WUE_RLC_TM_MODE:
        pTmMsg = (RABM_RLC_TM_DATA_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                 WUEPS_PID_RABM,sizeof(RABM_RLC_TM_DATA_REQ_STRU));
        if( VOS_NULL == pTmMsg )
        {
            PS_NAS_LOG(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_ERROR,
                "NAS_CsDomainDataReq, Error, call PS_ALLOC_MSG_WITH_HEADER_LEN fail\n");

            return AS_NO_MEMORY;
        }
        PS_MEM_SET((VOS_INT8*)pTmMsg + VOS_MSG_HEAD_LENGTH,0,
                sizeof(RABM_RLC_TM_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

        pTmMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pTmMsg->ulSenderPid     = WUEPS_PID_RABM;
        pTmMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;

        pTmMsg->ulReceiverPid   = WUEPS_PID_RLC;

        pTmMsg->ulLength        = sizeof(RABM_RLC_TM_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

        pTmMsg->enMsgName       = ID_RABM_RLC_TM_DATA_REQ;
        pTmMsg->ucRbId          = (VOS_UINT8)cRbId;
        pTmMsg->usDataBitLen    = (VOS_UINT16)ulDataLength;

        ulLenOct = (ulDataLength + 7)/ 8;
        pData = TTF_MemBlkCopyAlloc(WUEPS_PID_RABM, TTF_MEM_POOL_ID_UL_RLC_SDU, pucData, (VOS_UINT16)ulLenOct);
        if ( VOS_NULL_PTR == pData )
        {
            /*释放消息内存:*/
            PS_FREE_MSG(WUEPS_PID_RABM, pTmMsg);
            PS_NAS_LOG(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_ERROR,
                    "NAS_CsDomainDataReq, Error, call TTF_MemCopyAlloc fail\n");

            return AS_NO_MEMORY;
        }

        pTmMsg->pstDataMem = pData;

        pMsg = (VOS_VOID *)pTmMsg;
        break;
    case WUE_RLC_UM_MODE:
        if(0 != (ulDataLength % 8))
        {
            PS_NAS_LOG(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_ERROR,
                "NAS_CsDomainDataReq, Error, 配置的RLC UL SDU长度不是整字节\n");

            return AS_DATA_LENGTH_ERR;
        }

        pUmMsg = (RABM_RLC_UM_DATA_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_RABM,sizeof(RABM_RLC_UM_DATA_REQ_STRU));
        if( VOS_NULL == pUmMsg )
        {
            PS_NAS_LOG(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_ERROR,
                "NAS_CsDomainDataReq, Error, call PS_ALLOC_MSG_WITH_HEADER_LEN fail\n");

            return AS_NO_MEMORY;
        }
        PS_MEM_SET((VOS_INT8*)pUmMsg + VOS_MSG_HEAD_LENGTH,0,
                            sizeof(RABM_RLC_UM_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

        pUmMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pUmMsg->ulSenderPid     = WUEPS_PID_RABM;
        pUmMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;

        pUmMsg->ulReceiverPid   = WUEPS_PID_RLC;

        pUmMsg->ulLength        = sizeof(RABM_RLC_UM_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

        pUmMsg->enMsgName       = ID_RABM_RLC_UM_DATA_REQ;
        pUmMsg->ucRbId          = (VOS_UINT8)cRbId;
        /* 此成员为TD新加的, GU这边没用这个成员, 所以可以不使用TD的宏 */
        pUmMsg->usDataBitLen    = (VOS_UINT16)ulDataLength;
        ulLenOct = ulDataLength / 8;
        pData = TTF_MemBlkCopyAlloc(WUEPS_PID_RABM, TTF_MEM_POOL_ID_UL_RLC_SDU, pucData, (VOS_UINT16)ulLenOct);
        if ( VOS_NULL_PTR == pData )
        {
            /*释放消息内存:*/
            PS_FREE_MSG(WUEPS_PID_RABM, pUmMsg);
            PS_NAS_LOG(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_ERROR,
                    "NAS_CsDomainDataReq, Error, call TTF_MemCopyAlloc fail\n");

            return AS_NO_MEMORY;
        }

        pUmMsg->pstDataMem = pData;

        pMsg = (VOS_VOID *)pUmMsg;

        break;
    case WUE_RLC_AM_MODE:
        ulLenOct = (ulDataLength + 7) / 8;

        pAmMsg = (RABM_RLC_AM_DATA_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                    WUEPS_PID_RABM,sizeof(RABM_RLC_AM_DATA_REQ_STRU));
        if( VOS_NULL == pAmMsg )
        {
            PS_NAS_LOG(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_ERROR,
                "NAS_CsDomainDataReq, Error, call PS_ALLOC_MSG_WITH_HEADER_LEN fail\n");

            return AS_NO_MEMORY;
        }
        PS_MEM_SET((VOS_INT8*)pAmMsg + VOS_MSG_HEAD_LENGTH,0,
                    sizeof(RABM_RLC_AM_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH);


        pAmMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pAmMsg->ulSenderPid     = WUEPS_PID_RABM;
        pAmMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;

        pAmMsg->ulReceiverPid   = WUEPS_PID_RLC;

        pAmMsg->ulLength        = sizeof(RABM_RLC_AM_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

        pAmMsg->enMsgName       = ID_RABM_RLC_AM_DATA_REQ;
        pAmMsg->ucRbId          = (VOS_UINT8)cRbId;
        /* 此成员为TD新加的, GU这边没用这个成员, 所以可以不使用TD的宏 */
        pAmMsg->usDataBitLen    = (VOS_UINT16)ulDataLength;

        pData = TTF_MemBlkCopyAlloc(WUEPS_PID_RABM, TTF_MEM_POOL_ID_UL_RLC_SDU, pucData, (VOS_UINT16)ulLenOct);
        if ( VOS_NULL_PTR == pData )
        {
            /*释放消息内存:*/
            PS_FREE_MSG(WUEPS_PID_RABM, pAmMsg);
            PS_NAS_LOG(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_ERROR,
                    "NAS_CsDomainDataReq, Error, call TTF_MemCopyAlloc fail\n");

            return AS_NO_MEMORY;
        }

        pAmMsg->pstDataMem = pData;

        pMsg = (VOS_VOID *)pAmMsg;

        break;
    case WUE_RLC_MODE_BUTT:
        PS_NAS_LOG(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
                "NAS_CsDomainDataReq, Error, No Rlc Rb exist\n");
        return AS_RB_NO_EXIST;
    default:
        PS_NAS_LOG(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
                "NAS_CsDomainDataReq, Error, Rb Tx Mode error!\n");
        return AS_RB_NO_EXIST;
    }

    if ( VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_RABM, (struct MsgCB **)&pMsg) )
    {
        /*发送消息失败，释放申请的零拷贝内存*/
        TTF_MemFree(WUEPS_PID_RABM, pData);
        return AS_SEND_FAILED;
    }
    return AS_SUCCESS;
}




VOS_INT32 As_RrDataReq(
               VOS_UINT8    ucCnDomain,                                                    /* CN DOMAIN                                 */
               VOS_UINT8    ucPriority,                                                    /* 信令数据优先级                            */
               VOS_UINT32    ulSize,                                                        /* 信令数据长度                              */
               VOS_INT8     *pData                                                         /* 信令数据指针                              */
               )
{
    RRMM_DATA_REQ_STRU*         pMsg = VOS_NULL;                                           /* 定义原语类型指针                          */
    VOS_UINT32                       ulTmpSize;

    ulTmpSize = ulSize;
    if(ulTmpSize < 4)
    {
        ulTmpSize = 4;
    }

    if(RRC_NAS_CS_DOMAIN == ucCnDomain)
    {
        pMsg = (RRMM_DATA_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                WUEPS_PID_MM,(sizeof(RRMM_DATA_REQ_STRU) + ulTmpSize) - 4);
    }
    else
    {
        pMsg = (RRMM_DATA_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                WUEPS_PID_GMM,(sizeof(RRMM_DATA_REQ_STRU) + ulTmpSize) - 4);
    }
    if( VOS_NULL == pMsg )
    {                                                                                  /* 内存申请失败                              */
        return AS_VOS_ERR;                                                             /* 返回                                      */
    }
    PS_MEM_SET((VOS_INT8*)pMsg + VOS_MSG_HEAD_LENGTH,0,
         ((sizeof(RRMM_DATA_REQ_STRU) + ulTmpSize) - 4) - VOS_MSG_HEAD_LENGTH);
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_WRR;
    pMsg->MsgHeader.ulMsgName = RRMM_DATA_REQ;                                         /* 消息名称                                  */

    pMsg->ulCnDomainId = ucCnDomain;
    pMsg->ulPriorityInd = ucPriority;
    pMsg->SendNasMsg.ulNasMsgSize = ulSize;
    if(VOS_NULL_PTR != pData)
    {
        PS_MEM_CPY(pMsg->SendNasMsg.aucNasMsg,pData,ulSize);
    }

    if (RRC_NAS_CS_DOMAIN == ucCnDomain)
    {
        pMsg->MsgHeader.ulSenderPid = WUEPS_PID_MM;
    }
    else
    {
        pMsg->MsgHeader.ulSenderPid = WUEPS_PID_GMM;
    }

    if (VOS_OK != NAS_UTRANCTRL_SndAsMsg(pMsg->MsgHeader.ulSenderPid, (struct MsgCB **)&pMsg))
    {
        return AS_SEND_FAILED;
    }

    return AS_SUCCESS;
}

VOS_INT32 As_RrEstReq(
    VOS_UINT32                          ulOpId,
    VOS_UINT8                           ucCnDomain,
    VOS_UINT32                          ulEstCause,
    VOS_UINT32                          ulCallType,
    IDNNS_STRU                          *pIdnnsInfo,
    RRC_PLMN_ID_STRU                    *pstPlmnId,
    VOS_UINT32                          ulSize,
    VOS_INT8                            *pFisrstMsg
)
{
    RRMM_EST_REQ_STRU*               pMsg = VOS_NULL;                                           /* 定义原语类型指针                          */
    VOS_UINT32                       ulTmpSize;

    ulTmpSize = ulSize;
    if (ulTmpSize < 4)
    {
        ulTmpSize = 4;
    }

    if (RRC_NAS_CS_DOMAIN == ucCnDomain)
    {
        pMsg = (RRMM_EST_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                WUEPS_PID_MM,(sizeof(RRMM_EST_REQ_STRU) + ulTmpSize) - 4);
    }
    else
    {
        pMsg = (RRMM_EST_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                WUEPS_PID_GMM,(sizeof(RRMM_EST_REQ_STRU) + ulTmpSize) - 4);
    }
    if (VOS_NULL == pMsg)
    {                                                                                  /* 内存申请失败                              */
        return AS_VOS_ERR;                                                             /* 返回                                      */
    }
    PS_MEM_SET((VOS_INT8*)pMsg + VOS_MSG_HEAD_LENGTH,0,
         ((sizeof(RRMM_EST_REQ_STRU) + ulTmpSize) - 4) - VOS_MSG_HEAD_LENGTH);
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_WRR;
    pMsg->MsgHeader.ulMsgName = RRMM_EST_REQ;                                          /* 消息名称                                  */

    pMsg->ulOpId = ulOpId;
    pMsg->ulCnDomainId = ucCnDomain;
    pMsg->ulEstCause = ulEstCause;

    /*enCallType数据域3000接口新增，2000接入层不使用，暂时在这里赋默认值，
    日后该数据域由CC指定，As_RrEstReq函数增加一个参数*/
    pMsg->enCallType = ulCallType;

    pMsg->ulIdnnsType = pIdnnsInfo->ucIdnnsType;
    pMsg->enSplmnSameRplmn = pIdnnsInfo->ucEnterPara;

    PS_MEM_CPY(&pMsg->stPlmnId, pstPlmnId, sizeof(RRC_PLMN_ID_STRU));

    pMsg->FisrtNasMsg.ulNasMsgSize = ulSize;
    if (VOS_NULL_PTR != pFisrstMsg)
    {
        PS_MEM_CPY(pMsg->FisrtNasMsg.aucNasMsg,pFisrstMsg,ulSize);
    }
    else
    {
        PS_MEM_SET(pMsg->FisrtNasMsg.aucNasMsg, 0x00, 4);
    }

    if (RRC_NAS_CS_DOMAIN == ucCnDomain)
    {
        pMsg->MsgHeader.ulSenderPid = WUEPS_PID_MM;
    }
    else
    {
        pMsg->MsgHeader.ulSenderPid = WUEPS_PID_GMM;
    }

    if (VOS_OK != NAS_UTRANCTRL_SndAsMsg(pMsg->MsgHeader.ulSenderPid, (struct MsgCB **)&pMsg))
    {
        return AS_SEND_FAILED;
    }

    return AS_SUCCESS;
}

VOS_INT32 As_RrRelReq(
               VOS_UINT8    ucCnDomain,
               RRC_CELL_BAR_ENUM_UINT32 enBarValidFlg
               )
{
    RRMM_REL_REQ_STRU*          pMsg = VOS_NULL;                                           /* 定义原语类型指针                          */

    if(RRC_NAS_CS_DOMAIN == ucCnDomain)
    {
        pMsg = (RRMM_REL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        WUEPS_PID_MM,sizeof(RRMM_REL_REQ_STRU));
    }
    else
    {
        pMsg = (RRMM_REL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        WUEPS_PID_GMM,sizeof(RRMM_REL_REQ_STRU));
    }
    if( VOS_NULL == pMsg )
    {                                                                                  /* 内存申请失败                              */
        return AS_VOS_ERR;                                                             /* 返回                                      */
    }
    PS_MEM_SET((VOS_INT8*)pMsg + VOS_MSG_HEAD_LENGTH,0,
                        sizeof(RRMM_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_WRR;
    pMsg->MsgHeader.ulMsgName = RRMM_REL_REQ;                                          /* 消息名称                                  */
    pMsg->ulCnDomainId = ucCnDomain;
    pMsg->enBarValidFlg = enBarValidFlg;

    if (RRC_NAS_CS_DOMAIN == ucCnDomain)
    {
        pMsg->MsgHeader.ulSenderPid = WUEPS_PID_MM;
    }
    else
    {
        pMsg->MsgHeader.ulSenderPid = WUEPS_PID_GMM;
    }

    if (VOS_OK != NAS_UTRANCTRL_SndAsMsg(pMsg->MsgHeader.ulSenderPid, (struct MsgCB **)&pMsg))
    {
        return AS_SEND_FAILED;
    }

    return AS_SUCCESS;
}


VOS_INT32 As_RabInfoRsp(
                VOS_UINT32               ulResult,
                RAB_RSP_INFO_STRU   *pRabInfo
                )
{
    VOS_UINT8                   i;
    RRRABM_RAB_RSP_STRU*    pMsg = VOS_NULL;                                               /* 定义原语类型指针                          */

    pMsg = (RRRABM_RAB_RSP_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                WUEPS_PID_RABM,sizeof(RRRABM_RAB_RSP_STRU));
    if( VOS_NULL == pMsg )
    {                                                                                  /* 内存申请失败                              */
        return AS_VOS_ERR;                                                             /* 返回                                      */
    }
    PS_MEM_SET((VOS_INT8*)pMsg + VOS_MSG_HEAD_LENGTH,0,
         sizeof(RRRABM_RAB_RSP_STRU) - VOS_MSG_HEAD_LENGTH);
    pMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_WRR;
    pMsg->MsgHeader.ulMsgName = RRRABM_RAB_RSP;                                        /* 消息名称                                  */

    pMsg->ulOpId = pRabInfo->ulOpId;
    if(AS_RAB_RSP_OK == ulResult)
    {
        pMsg->ulRabCnt = pRabInfo->ulRabCnt;
        for(i = 0;i < pRabInfo->ulRabCnt;i++)
        {
            pMsg->aRabInfo[i].enCnDomainId     = pRabInfo->aRabInfo[i].ulCnDomainId;
            pMsg->aRabInfo[i].ulRabId          = pRabInfo->aRabInfo[i].ulRabId;
            pMsg->aRabInfo[i].ulPppValid       = pRabInfo->aRabInfo[i].ulPppValid;
            pMsg->aRabInfo[i].ulDeliveryErrSdu = pRabInfo->aRabInfo[i].ulDeliveryErrSdu;
        }
    }
    else
    {
        pMsg->ulRabCnt = 0;
    }

    if ( VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_RABM, (struct MsgCB **)&pMsg))
    {                                                                                  /* 发送失败                                  */
        return AS_VOS_ERR;                                                             /* 返回                                      */
    }
    return AS_SUCCESS;
}

VOS_INT32 As_RabQosUpdate(
                  QOS_INFO_STRU     *pQosInfo
                  )
{
    VOS_UINT8                           i;
    RRRABM_QOS_UPDATE_REQ_STRU*     pMsg = VOS_NULL;                                       /* 定义原语类型指针                          */

    pMsg = (RRRABM_QOS_UPDATE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                WUEPS_PID_RABM,sizeof(RRRABM_QOS_UPDATE_REQ_STRU));
    if( VOS_NULL == pMsg )
    {                                                                                  /* 内存申请失败                              */
        return AS_VOS_ERR;                                                             /* 返回                                      */
    }
    PS_MEM_SET((VOS_INT8*)pMsg + VOS_MSG_HEAD_LENGTH,0,
         sizeof(RRRABM_QOS_UPDATE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    pMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_WRR;
    pMsg->MsgHeader.ulMsgName = RRRABM_QOS_UPDATE_REQ;                                 /* 消息名称                                  */

    pMsg->ulRabCnt = pQosInfo->ulRabCnt;
    for(i = 0;i < pQosInfo->ulRabCnt;i++)
    {
        pMsg->aRab[i].enCnDomainId     = pQosInfo->aRab[i].ulCnDomainId;
        pMsg->aRab[i].ulRabId          = pQosInfo->aRab[i].ulRabId;
        pMsg->aRab[i].ulPppValid       = pQosInfo->aRab[i].ulPppValid;
        pMsg->aRab[i].ulDeliveryErrSdu = pQosInfo->aRab[i].ulDeliveryErrSdu;
    }

    if( VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_RABM, (struct MsgCB **)&pMsg))
    {                                                                                  /* 发送失败                                  */
        return AS_VOS_ERR;                                                             /* 返回                                      */
    }
    return AS_SUCCESS;
}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

