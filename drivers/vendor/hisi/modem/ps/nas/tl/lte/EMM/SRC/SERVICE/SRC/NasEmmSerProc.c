/*******************************************************************************
  Copyright     : 2005-2007, Huawei Tech. Co., Ltd.
  File name     : EmmService.c
  Description   : EMM SERVICE REQUEST功能相关处理用源文件
  Function List :
    01.   Nas_Emm_RcvRabmReestReq
    02.   Nas_Emm_RcvRabmReestStopReq
    03.   Nas_Emm_RcvRrcPagingInd
    04.   Nas_Emm_RcvRrcRelInd
    05.   Nas_Emm_RcvMrrcRelInd
    06.   Nas_Emm_RcvDetachReq
    07.   Nas_Emm_RcvTAUReq
    08.   Nas_Emm_RcvTimer****Exp
    09.   Nas_Emm_RcvServiceRejectMsg
    10.   Nas_Emm_ServiceReqRejectCasue3
    11.   Nas_Emm_ServiceReqRejectCasue6
    12.   Nas_Emm_ServiceReqRejectCasue7
    13.   Nas_Emm_ServiceReqRejectCasue9
    14.   Nas_Emm_ServiceReqRejectCasue10
    15.   Nas_Emm_ServiceReqRejectCasue11
    16.   Nas_Emm_ServiceReqRejectCasue12
    17.   Nas_Emm_ServiceReqRejectCasue13
    18.   Nas_Emm_ServiceReqRejectCasue14
    19.   Nas_Emm_ServiceReqRejectCasue15
    20.   Nas_Emm_ServiceReqRejectTheOtherCause
    21.   Nas_Emm_ServiceReqAbnormal***
  History       :
    1.  Zhouyan 00125190  2008.09.09  新规作成
    2.  leili       00132387    2009.06.25   BJ9001269 收到系统消息后处理优化
*******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasEmmTauSerInclude.h"
#include  "NasLmmPubMPrint.h"
#include  "EmmTcInterface.h"
#include  "NasLmmPubMOm.h"
#include  "NasEmmAttDetInclude.h"
#if (FEATURE_LPP == FEATURE_ON)
#include    "NasEmmLppMsgProc.h"
#include    "EmmLppInterface.h"
#include    "NasEmmSsMsgProc.h"
#include    "NasEmmSerProc.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMSERVICEPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMSERVICEPROC_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
NAS_EMM_SER_CTRL_STRU                   g_stEmmSERCtrlTbl;
NAS_EMM_SER_ESM_MSG_BUF_STRU            g_stEmmEsmMsgBuf;

/* ESR流程发生切换,未发起TAU,重传ESR消息控制开关:规避小区切换后网侧不下发REL问题 */
VOS_UINT32                              g_ulNasEmmHoRetransEsrFlag = PS_FALSE;

/*******************************************************************************
  Function : NAS_EMM_SER_Init
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.17  新规作成
*******************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID NAS_EMM_SER_Init(VOS_VOID)
{
    NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_Init                   START INIT...");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_Init_ENUM,LNAS_BEGIN);

    NAS_LMM_MEM_SET_S(&g_stEmmSERCtrlTbl, sizeof(g_stEmmSERCtrlTbl), 0, sizeof(g_stEmmSERCtrlTbl));

    NAS_LMM_MEM_SET_S(&g_stEmmEsmMsgBuf, sizeof(g_stEmmEsmMsgBuf), 0, sizeof(g_stEmmEsmMsgBuf));

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SER_ClearResource
 Description     : UE去注册，释放SER模块所有资源
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-10-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SER_ClearResource( VOS_VOID )
{
    NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_ClearResource entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_ClearResource_ENUM,LNAS_ENTRY);

    /* 清空SER全局变量*/
    NAS_LMM_MEM_SET_S(&g_stEmmSERCtrlTbl, sizeof(g_stEmmSERCtrlTbl), 0, sizeof(g_stEmmSERCtrlTbl));

    /* 释放缓存的ESM消息*/
    NAS_EMM_SerClearEsmDataBuf();

    /* 清空接入Bar信息*/
    NAS_EMM_ClearBarResouce();

    /* 停止Service流程相关的所有定时器*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

    return;
}


VOS_VOID  NAS_EMM_FreeSerDyn( VOS_VOID )
{
    /* 释放SERVICE模块缓存的ESM的消息 */
    NAS_EMM_SerClearEsmDataBuf();

    return;
}



VOS_VOID NAS_EMM_SER_CompCnServiceReq(  LRRC_LNAS_MSG_STRU   *pNasMsg)
{
    VOS_UINT32                          ulIndex     = 0;
    VOS_UINT8                           ucKsiSn;
    VOS_UINT8                           ucKsi;
    VOS_UINT8                           ucSequenceNum;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO("NAS_EMM_SER_CompCnServiceReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_CompCnServiceReq_ENUM,LNAS_ENTRY);

    /* 清空将填充CN消息的空间 */
    /* NAS_LMM_MEM_SET(pNasMsg->aucNasMsg, 0, pNasMsg->ulNasMsgSize); */

    /* 填充 Security header type  +  Protocol discriminator */
    pNasMsg->aucNasMsg[ulIndex++]       = EMM_CN_SECURITY_HEADER_TYPE_SER_REQ;

    /* 计算 KsiSn*/
    ucKsi = NAS_EMM_SecuGetKSIValue();
    ucSequenceNum = (VOS_UINT8)NAS_EMM_SecuGetUlNasCountVAlue();
    ucSequenceNum = ucSequenceNum & EMM_TAUSER_LOW5_BITS;
    ucKsiSn = ((VOS_UINT8)(ucKsi << 5)) | ucSequenceNum;


    /* 填充 KSI and sequence number   */
    pNasMsg->aucNasMsg[ulIndex++]       = ucKsiSn;


    /* 填充 Message authentication code */
    /*这里只需要初始化为0，在完整性保护时会填充这两个字节*/
    pNasMsg->aucNasMsg[ulIndex++]       = 0;
    pNasMsg->aucNasMsg[ulIndex]         = 0;
    return;
}

/*lint -e669*/
/*******************************************************************************
  Module   : Nas_Emm_SendMrrcDataReq_ServiceReq
  Function : 收到EMM_ERABM_REEST_REQ原语后的处理
  Input    : VOS_VOID *pMsg     原语首地址
  Output   : 无
  NOTE     : 无
  Return   : VOS_UINT32
  History  :
    1.  Zhouyan 00125190  2008.09.09  新规作成
*******************************************************************************/
VOS_VOID    NAS_EMM_SER_SendMrrcDataReq_ServiceReq()
{
    NAS_EMM_MRRC_DATA_REQ_STRU          *pMrrcDataReqMsg    = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulDataReqMsgLenNoHeader;
    VOS_UINT32                          ulCnMsgLen;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_SER_SendMrrcDataReq_ServiceReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SendMrrcDataReq_ServiceReq_ENUM,LNAS_ENTRY);

    /* 计算NAS_MSG_STRU消息长度 */
    ulCnMsgLen                              = NAS_EMM_COUNT_CN_SER_REQ_LEN;
    ulDataReqMsgLenNoHeader                 = EMM_COUNT_DATA_REQ_LEN(ulCnMsgLen);

    /* 申请DOPRA消息 */
    pMrrcDataReqMsg = (VOS_VOID *)NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);

    if(NAS_EMM_NULL_PTR == pMrrcDataReqMsg)
    {
        return;
    }

    NAS_LMM_MEM_SET_S(pMrrcDataReqMsg, NAS_EMM_INTRA_MSG_MAX_SIZE, 0, NAS_EMM_INTRA_MSG_MAX_SIZE);

    /* 清除CSFB ABORT标识 */
    NAS_EMM_SER_SaveEmmSerCsfbAbortFlag(NAS_EMM_CSFB_ABORT_FLAG_INVALID);
    /* 填写MRRC_DATA_REQ 的DOPRA消息头 */
    EMM_COMP_MM_MSG_HEADER(pMrrcDataReqMsg, ulDataReqMsgLenNoHeader);

    /* 填写MRRC_DATA_REQ 的消息ID标识 */
    pMrrcDataReqMsg->ulMsgId                = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;

    /*填写建立原因*/
    switch(NAS_EMM_SER_GetEmmSERStartCause())
    {
        case NAS_EMM_SER_START_CAUSE_RRC_PAGING:
            pMrrcDataReqMsg->enEstCaue = LRRC_LNAS_EST_CAUSE_MT_ACCESS;
            pMrrcDataReqMsg->enCallType = LRRC_LNAS_CALL_TYPE_TERMINATING_CALL;
            NAS_LMM_SndOmSerStartTypeInfo(NAS_LMM_OM_SER_START_TYPE_RRC_PAGING);
            break;

        case NAS_EMM_SER_START_CAUSE_RABM_REEST:
            pMrrcDataReqMsg->enEstCaue = LRRC_LNAS_EST_CAUSE_MO_DATA;
            pMrrcDataReqMsg->enCallType = LRRC_LNAS_CALL_TYPE_ORIGINATING_CALL;
            NAS_LMM_SndOmSerStartTypeInfo(NAS_LMM_OM_SER_START_TYPE_RABM_REEST);
            break;

        case NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ:
            pMrrcDataReqMsg->enEstCaue = LRRC_LNAS_EST_CAUSE_MO_DATA;
            pMrrcDataReqMsg->enCallType = LRRC_LNAS_CALL_TYPE_ORIGINATING_CALL;
            NAS_LMM_SndOmSerStartTypeInfo(NAS_LMM_OM_SER_START_TYPE_ESM_DATA_REQ);
            break;

        case NAS_ESM_SER_START_CAUSE_UPLINK_PENDING:
            pMrrcDataReqMsg->enEstCaue = LRRC_LNAS_EST_CAUSE_MO_DATA;
            pMrrcDataReqMsg->enCallType = LRRC_LNAS_CALL_TYPE_ORIGINATING_CALL;
            NAS_LMM_SndOmSerStartTypeInfo(NAS_LMM_OM_SER_START_TYPE_UPLINK_PENDING);
            break;

        case NAS_EMM_SER_START_CAUSE_SMS_EST_REQ:
            pMrrcDataReqMsg->enEstCaue = LRRC_LNAS_EST_CAUSE_MO_DATA;
            pMrrcDataReqMsg->enCallType = LRRC_LNAS_CALL_TYPE_ORIGINATING_CALL;
            NAS_LMM_SndOmSerStartTypeInfo(NAS_LMM_OM_SER_START_TYPE_SMS_EST_REQ);
            break;

        #if (FEATURE_LPP == FEATURE_ON)
        case NAS_EMM_SER_START_CAUSE_LPP_EST_REQ:
            pMrrcDataReqMsg->enEstCaue = LRRC_LNAS_EST_CAUSE_MO_DATA;
            pMrrcDataReqMsg->enCallType = LRRC_LNAS_CALL_TYPE_ORIGINATING_CALL;
            NAS_LMM_SndOmSerStartTypeInfo(NAS_LMM_OM_SER_START_TYPE_LPP_EST_REQ);
            break;
        case NAS_EMM_SER_START_CAUSE_SS_EST_REQ:
            pMrrcDataReqMsg->enEstCaue = LRRC_LNAS_EST_CAUSE_MO_DATA;
            pMrrcDataReqMsg->enCallType = LRRC_LNAS_CALL_TYPE_ORIGINATING_CALL;
            NAS_LMM_SndOmSerStartTypeInfo(NAS_LMM_OM_SER_START_TYPE_SS_EST_REQ);
            break;
        #endif

        case NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC:
            pMrrcDataReqMsg->enEstCaue = LRRC_LNAS_EST_CAUSE_EMERGENCY_CALL;
            pMrrcDataReqMsg->enCallType = LRRC_LNAS_CALL_TYPE_EMERGENCY_CALL;
            NAS_LMM_SndOmSerStartTypeInfo(NAS_LMM_OM_SER_START_TYPE_ESM_DATA_REQ_EMC);
            break;

        case NAS_EMM_SER_START_CAUSE_RABM_REEST_EMC:
            pMrrcDataReqMsg->enEstCaue = LRRC_LNAS_EST_CAUSE_EMERGENCY_CALL;
            pMrrcDataReqMsg->enCallType = LRRC_LNAS_CALL_TYPE_EMERGENCY_CALL;
            NAS_LMM_SndOmSerStartTypeInfo(NAS_LMM_OM_SER_START_TYPE_RABM_REEST_EMC);
            break;

        default:
            NAS_EMM_SER_LOG_ERR("Nas_Emm_SER_SendMrrcDataReq_ServiceReq:StartCause ERR");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_SER_SendMrrcDataReq_ServiceReq_ENUM,LNAS_ERROR);
            break;
    }
    pMrrcDataReqMsg->enEmmMsgType       = NAS_EMM_MSG_SERVICE_REQ;

    /* 填写MRRC_DATA_REQ 的NAS消息长度标识 */
    pMrrcDataReqMsg->stNasMsg.ulNasMsgSize  = ulCnMsgLen;

    pMrrcDataReqMsg->enDataCnf              = LRRC_LMM_DATA_CNF_NEED;

    /* 构造MRRC_DATA_REQ 中的 NAS_MSG_STRU,即CN消息(Compose the msg of): SER_REQ */
    NAS_EMM_SER_CompCnServiceReq(               &(pMrrcDataReqMsg->stNasMsg));

    /*空口消息上报SER REQ*/
    NAS_LMM_SendOmtAirMsg(NAS_EMM_OMT_AIR_MSG_UP, NAS_EMM_SER_REQ,  (NAS_MSG_STRU*)&(pMrrcDataReqMsg->stNasMsg));

    /*关键事件上报SER REQ*/
    NAS_LMM_SendOmtKeyEvent(         EMM_OMT_KE_SER_REQ);
    /* 大数据: 更新SER发起次数 */
    NAS_LMM_AddSerCounter(NAS_LMM_OM_PCE_TIMES_TYPE_TOTAL);
    /* 发送消息(Send the msg of) MRRC_DATA_REQ(SER_REQ) */
    NAS_EMM_SndUplinkNasMsg((VOS_VOID*)pMrrcDataReqMsg);

    NAS_LMM_MEM_FREE(pMrrcDataReqMsg);
    /* 记录Ser Req发送时间 */
    NAS_EMM_SaveSerReqSndTimeStamp();
    return;
}
/*lint +e669*/


/*****************************************************************************
 Function Name   : NAS_EMM_CompCnExtendedSerReqMoNasMsg
 Description     : 组装EXTENDED SERVICE REQ消息
 Input           : pulIndex
 Output          : pucCnMsg
                   pulIndex
 Return          : VOS_VOID

 History         :
    1.lihong      2012-02-23  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_CompCnExtendedSerReqMoNasMsg
(
    VOS_UINT8                          *pucCnMsg,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulIndex      = NAS_EMM_NULL;
    VOS_UINT8                           ucKsi        = NAS_EMM_NULL;
    NAS_LMM_PUB_INFO_STRU              *pstEmmInfo   = VOS_NULL_PTR;
    VOS_UINT32                          ulIeLength          = 0;

    ulIndex                 = *pulIndex;
    pstEmmInfo              = NAS_LMM_GetEmmInfoAddr();

    /* 填充 Protocol Discriminator + Security header type*/
    pucCnMsg[ulIndex++]     = EMM_CN_MSG_PD_EMM;

    /* 填充 Detach request message identity */
    pucCnMsg[ulIndex++]     = NAS_EMM_CN_MT_EXT_SER_REQ;

    /* 填充service type */
    if (NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
    {
        pucCnMsg[ulIndex]   = MMC_LMM_SERVICE_MO_CSFB_1XCSFB;
    }
    else if (NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
    {
        pucCnMsg[ulIndex]   = MMC_LMM_SERVICR_MO_CSFB_1XCSFB_EMERGENCY;
    }
    else
    {
        pucCnMsg[ulIndex]   = MMC_LMM_SERVICR_MT_CSFB_1XCSFB;
    }

    /*填充KSIasme*/
    ucKsi = NAS_EMM_SecuGetKSIValue();
    pucCnMsg[ulIndex++]     |= (ucKsi & 0x0F)<<4;

    /*填充M-TSMI*/

    /* 填写LENGTH为5 */
    pucCnMsg[ulIndex++]     = 5;

    /*  填写TYPE OF IDENTITY，和EVEN/ODD标识，根据协议前4BIT为'1111' */
    pucCnMsg[ulIndex]       = NAS_EMM_TYPE_OF_IDENTITY_TMSI_PTMSI_MTMSI;/* [false alarm]:代码保证了不会越界 */
    pucCnMsg[ulIndex++]     |= NAS_EMM_HIGH_4_BIT;/* [false alarm]:代码保证了不会越界 */

    NAS_LMM_MEM_CPY_S(      &(pucCnMsg[ulIndex]),
                            sizeof(NAS_EMM_MTMSI_STRU),
                            &pstEmmInfo->stMmUeId.stGuti.stMTmsi,
                            sizeof(NAS_EMM_MTMSI_STRU));
    ulIndex                 += sizeof(NAS_EMM_MTMSI_STRU);

    /* 只有MT CSFB才填充CSFB RESPONSE */
    if (NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
    {
        pucCnMsg[ulIndex++] = NAS_EMM_EXTENDED_SER_REQ_CSFB_RSP_IEI | NAS_EMM_SER_GetEmmSerCsfbRsp();/* [false alarm]:代码保证了不会越界 */
    }

    /* 填充EPS bearer context status */
    NAS_EMM_EncodeEpsBearStatus(        &(pucCnMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    *pulIndex               = ulIndex;

    return;

}

/*******************************************************************************
  Module   : NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq
  Function : 发送EXTENDED SERVICE REQ消息
  Input    : VOS_VOID *pMsg     原语首地址
  Output   : 无
  NOTE     : 无
  Return   : VOS_UINT32
  History  :
    1.  lihong 00150010  2012.02.23  新规作成
*******************************************************************************/
VOS_VOID    NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq(VOS_VOID)
{
    NAS_EMM_MRRC_DATA_REQ_STRU         *pMrrcDataReqMsg         = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulDataReqMsgLenNoHeader = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex                 = NAS_EMM_NULL;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq_ENUM,LNAS_ENTRY);

    /*以最小消息长度，申请消息内存,主要是看是否队列有空间*/
    pMrrcDataReqMsg = (VOS_VOID *) NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);

    /*判断申请结果，若失败退出*/
    if (NAS_EMM_NULL_PTR == pMrrcDataReqMsg)
    {
        return;
    }

    /* 清除CSFB ABORT标识 */
    NAS_EMM_SER_SaveEmmSerCsfbAbortFlag(NAS_EMM_CSFB_ABORT_FLAG_INVALID);

    /*组装EXTENDED SERVICE REQ消息*/
    NAS_EMM_CompCnExtendedSerReqMoNasMsg(pMrrcDataReqMsg->stNasMsg.aucNasMsg, &ulIndex);

    /*内部消息长度计算*/
    ulDataReqMsgLenNoHeader = NAS_EMM_CountMrrcDataReqLen(ulIndex);

    if ( NAS_EMM_INTRA_MSG_MAX_SIZE < ulDataReqMsgLenNoHeader )
    {
        /* 打印错误信息 */
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq, Size error");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq_ENUM,LNAS_ERROR);
        NAS_LMM_MEM_FREE(pMrrcDataReqMsg);
        return ;
    }

    /*填充消息长度*/
    pMrrcDataReqMsg->stNasMsg.ulNasMsgSize = ulIndex;

    /*填充消息头*/
    EMM_COMP_MM_MSG_HEADER(pMrrcDataReqMsg, ulDataReqMsgLenNoHeader);

    /* 填写MRRC_DATA_REQ 的消息ID标识 */
    pMrrcDataReqMsg->ulMsgId            = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;
    /*填写建立原因*/
    switch(NAS_EMM_SER_GetEmmSERStartCause())
    {
        case NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ:
            pMrrcDataReqMsg->enEstCaue  = LRRC_LNAS_EST_CAUSE_MT_ACCESS;
            pMrrcDataReqMsg->enCallType = LRRC_LNAS_CALL_TYPE_TERMINATING_CALL;
            break;

        case NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ:
            pMrrcDataReqMsg->enEstCaue  = LRRC_LNAS_EST_CAUSE_MO_DATA;
            pMrrcDataReqMsg->enCallType = LRRC_LNAS_CALL_TYPE_MO_CSFB;
            break;

        case NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ:
            pMrrcDataReqMsg->enEstCaue  = LRRC_LNAS_EST_CAUSE_EMERGENCY_CALL;
            pMrrcDataReqMsg->enCallType = LRRC_LNAS_CALL_TYPE_EMERGENCY_CALL;
            break;

        default:
            NAS_EMM_SER_LOG_ERR("Nas_Emm_SER_SendMrrcDataReq_ServiceReq:StartCause ERR");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq_ENUM,LNAS_FUNCTION_LABEL1);
            break;
    }
    pMrrcDataReqMsg->enEmmMsgType       = NAS_EMM_MSG_EXTENDED_SERVICE_REQ;

    pMrrcDataReqMsg->enDataCnf          = LRRC_LMM_DATA_CNF_NEED;

    /*空口消息上报SER REQ*/
    NAS_LMM_SendOmtAirMsg(NAS_EMM_OMT_AIR_MSG_UP, NAS_EMM_EXTENDED_SER_REQ,  (NAS_MSG_STRU*)&(pMrrcDataReqMsg->stNasMsg));

    /*关键事件上报SER REQ*/
    NAS_LMM_SendOmtKeyEvent(            EMM_OMT_KE_EXTENDED_SER_REQ);

    /* 发送消息(Send the msg of) MRRC_DATA_REQ(SER_REQ) */
    NAS_EMM_SndUplinkNasMsg(             pMrrcDataReqMsg);

    NAS_LMM_MEM_FREE(pMrrcDataReqMsg);

    return;
}

/*******************************************************************************
  Module   :
  Function : Nas_Emm_SER_SendRrcDataReq_ESMdata
  Input    :
  Output   :
  NOTE     :向RRC转发ESM_DATA消息
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.09  新规作成
    2.  lihong00150010    2012-10-31  Modify:emgergency
    3.  lifuxin 00253982  2014-07-02  DSDS修改
*******************************************************************************/
VOS_VOID    NAS_EMM_SER_SendMrrcDataReq_ESMdata
(
    EMM_ESM_MSG_STRU                   *pstEsmMsg,
    VOS_UINT32                          ulEsmmmOpId
)
{
    VOS_UINT32                          ulMsgLenthNoHeader;
    NAS_EMM_MRRC_DATA_REQ_STRU          *pMrrcDataReqMsg    = NAS_EMM_NULL_PTR;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_SER_LOG1_INFO( "NAS_EMM_SER_SendMrrcDataReq_ESMdata is entered.", pstEsmMsg);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SER_SendMrrcDataReq_ESMdata_ENUM,LNAS_ENTRY,pstEsmMsg);

    /*申请消息*/
    pMrrcDataReqMsg = (VOS_VOID *)NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);
    if ( NAS_EMM_NULL_PTR == pMrrcDataReqMsg )
    {
        NAS_EMM_SER_LOG_ERR( "Nas_Emm_SER_SendMrrcDataReq_ESMdata: NAS_LMM_ALLOC_MSG err !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SER_SendMrrcDataReq_ESMdata_ENUM,LNAS_NULL_PTR);
        return;
    }

    ulMsgLenthNoHeader                  = NAS_EMM_CountMrrcDataReqLen(pstEsmMsg->ulEsmMsgSize);

    /* 拷贝消息 */
    pMrrcDataReqMsg->stNasMsg.ulNasMsgSize = pstEsmMsg->ulEsmMsgSize;

    NAS_LMM_MEM_CPY_S(                  (pMrrcDataReqMsg->stNasMsg.aucNasMsg),
                                        (pstEsmMsg->ulEsmMsgSize),
                                        (pstEsmMsg->aucEsmMsg),
                                        (pstEsmMsg->ulEsmMsgSize));
    /* 改写DOPRA消息头 */
    EMM_COMP_MM_MSG_HEADER(             (pMrrcDataReqMsg),
                                        ulMsgLenthNoHeader);

    /*改写消息ID*/
    pMrrcDataReqMsg->ulMsgId            = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;

    /*填写 EST CAUSE*/
    pMrrcDataReqMsg->enEstCaue          = LRRC_LNAS_EST_CAUSE_MO_DATA;
    pMrrcDataReqMsg->enCallType         = LRRC_LNAS_CALL_TYPE_ORIGINATING_CALL;
    pMrrcDataReqMsg->enEmmMsgType       = NAS_EMM_MSG_ESM;

    pMrrcDataReqMsg->ulEsmMmOpId        = ulEsmmmOpId;

    pMrrcDataReqMsg->enDataCnf          = LRRC_LMM_DATA_CNF_NEED;


    /* 向MRRC转发MMESM_DATA_REQ消息 */
    NAS_EMM_SndUplinkNasMsg(             pMrrcDataReqMsg);

    NAS_LMM_MEM_FREE(pMrrcDataReqMsg);
    return;
}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_SER_SendMrrcDataReq_Tcdata
  Input    : pMsg------------TC消息
  Output   :
  NOTE     : 向RRC转发TC_DATA_REQ消息
  Return   : VOS_VOID
  History  :
      1.lihong00150010      2009-10-16  Draft Enact
*******************************************************************************/
VOS_VOID    NAS_EMM_SER_SendMrrcDataReq_Tcdata
(
    EMM_ETC_DATA_REQ_STRU               *pMsg
)
{
    VOS_UINT32                          ulMsgLenthNoHeader;
    NAS_EMM_MRRC_DATA_REQ_STRU         *pMrrcDataReqMsg    = NAS_EMM_NULL_PTR;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_SER_LOG1_INFO( "NAS_EMM_SER_SendMrrcDataReq_Tcdata is entered.", pMsg);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SER_SendMrrcDataReq_Tcdata_ENUM,LNAS_ENTRY,pMsg);


    /*申请消息*/
    pMrrcDataReqMsg = (VOS_VOID *)NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);
    if ( NAS_EMM_NULL_PTR == pMrrcDataReqMsg )
    {
        NAS_EMM_SER_LOG_ERR( "NAS_EMM_SER_SendMrrcDataReq_Tcdata: NAS_LMM_ALLOC_MSG err !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SER_SendMrrcDataReq_Tcdata_ENUM,LNAS_NULL_PTR);
        return;
    }
    ulMsgLenthNoHeader                  = NAS_EMM_CountMrrcDataReqLen(pMsg->stTcMsg.ulTcMsgSize);

    /* 拷贝消息 */
    pMrrcDataReqMsg->stNasMsg.ulNasMsgSize = pMsg->stTcMsg.ulTcMsgSize;

    NAS_LMM_MEM_CPY_S(                  (pMrrcDataReqMsg->stNasMsg.aucNasMsg),
                                        (pMsg->stTcMsg.ulTcMsgSize),
                                        (pMsg->stTcMsg.aucTcMsg),
                                        (pMsg->stTcMsg.ulTcMsgSize));
    /* 改写DOPRA消息头 */
    EMM_COMP_MM_MSG_HEADER(             (pMrrcDataReqMsg),
                                        ulMsgLenthNoHeader);

    /*改写消息ID*/
    pMrrcDataReqMsg->ulMsgId            = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;

    /*填写 EST CAUSE*/
    pMrrcDataReqMsg->enEstCaue          = LRRC_LNAS_EST_CAUSE_MO_DATA;
    pMrrcDataReqMsg->enCallType         = LRRC_LNAS_CALL_TYPE_ORIGINATING_CALL;
    pMrrcDataReqMsg->enEmmMsgType       = NAS_EMM_MSG_TC;

    pMrrcDataReqMsg->enDataCnf          = LRRC_LMM_DATA_CNF_NOT_NEED;

    /* 向MRRC转发TC_DATA_REQ消息 */
    NAS_EMM_SndUplinkNasMsg(pMrrcDataReqMsg);

    NAS_LMM_MEM_FREE(pMrrcDataReqMsg);

    return;
}
/*******************************************************************************
  Module   :
  Function : NAS_EMM_SER_SendRabmReestInd
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.09  新规作成
*******************************************************************************/
VOS_VOID    NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_ENUM_UINT32
                                                                enRabmReestState)
{
    EMM_ERABM_REEST_IND_STRU             *pRabmReestIndMsg    = NAS_EMM_NULL_PTR;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_SER_SendRabmReestInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SendRabmReestInd_ENUM,LNAS_ENTRY);

    /* 申请DOPRA消息 */
    pRabmReestIndMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ERABM_REEST_IND_STRU));

    if(NAS_EMM_NULL_PTR == pRabmReestIndMsg)
    {
        return;
    }

    /* 填写EMM_ERABM_REEST_IND 的DOPRA消息头 */
    EMM_COMP_ERABM_MSG_HEADER(pRabmReestIndMsg, sizeof(EMM_ERABM_REEST_IND_STRU) -
                                        EMM_LEN_VOS_MSG_HEADER);

    /* 填写EMM_ERABM_REEST_IND 的消息ID标识 */
    pRabmReestIndMsg->ulMsgId           = ID_EMM_ERABM_REEST_IND;

    /* 构造EMM_ERABM_REEST_IND 中的重建状态 */
    pRabmReestIndMsg->enReEstState      = enRabmReestState;

    /* 发送消息(Send the msg of) EMM_ERABM_REEST_IND */
    NAS_LMM_SEND_MSG(                   pRabmReestIndMsg);

    return;

}

/*******************************************************************************
  Module   : SR
  Function : NAS_EMM_SER_AbnormalOver
  Input    :
  Output   :
  NOTE     : SR流程终止处理
  Return   :
  History  :
    1.  sunbing     49683    2011.12.09  修改
    2.  lihong      00150010 2012.02.24  修改
    3.  leixiantiao 00258641 2015-07-09  fix DTS2015062509266
*******************************************************************************/
VOS_VOID NAS_EMM_SER_AbnormalOver(VOS_VOID)
{
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_AbnormalOver is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_AbnormalOver_ENUM,LNAS_ENTRY);

    /*停止T3417定时器*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

    /*停止T3440定时器*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

    /*停止T3417ext定时器*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

    /*如果SR流程是由于SMS触发，需要回复SMS建链失败，并且清除SR的发起原因，*/
    if(NAS_EMM_SER_START_CAUSE_SMS_EST_REQ == NAS_EMM_SER_GetSerStartCause())
    {
        /* SER异常的原因值上报暂时报LMM_SMS_ERR_CAUSE_OTHERS，
           以后可能要根据相应的原因值进行具体细分处理，上报准确的原因值
           此处作为遗留问题 */
        NAS_LMM_SndLmmSmsErrInd(LMM_SMS_ERR_CAUSE_OTHERS);
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
    }

    #if (FEATURE_LPP == FEATURE_ON)
    if(NAS_EMM_SER_START_CAUSE_LPP_EST_REQ == NAS_EMM_SER_GetSerStartCause())
    {
        NAS_EMM_SendLppEstCnf(LMM_LPP_EST_RESULT_FAIL_SERVICE_FAIL);
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
    }

    if(NAS_EMM_SER_START_CAUSE_SS_EST_REQ == NAS_EMM_SER_GetSerStartCause())
    {
        NAS_LMM_SndLmmLcsEstCnf( LMM_LCS_EST_RSLT_FAIL_SERVICE_FAIL,
                                NAS_EMM_SER_GetSsOrLppOpid());
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
    }
    #endif


    if (VOS_TRUE != NAS_EMM_SER_IsCsfbProcedure())
    {
        /*Inform RABM that SER fail*/
         NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_FAIL);
    }
    else
    {
        /* 停止ESR流程,通知LRRC CSFB流程终止,LRRC收到该消息后,若等待网侧释放定时器启动时,停止定时器 */
        NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_END);
    }

    /*清空ESM_DATA缓存*/
    NAS_EMM_SerClearEsmDataBuf();

    return;
}


VOS_UINT32    NAS_EMM_SER_CHKFSMStateMsgp(
                                    NAS_EMM_MAIN_STATE_ENUM_UINT16  stMS,
                                    NAS_EMM_SUB_STATE_ENUM_UINT16   stSS,
                                    VOS_VOID   *pMsgStru)
{

    NAS_EMM_SER_LOG1_INFO( "NAS_EMM_SER_CHKFSMStateMsgp is entered.", pMsgStru);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SER_CHKFSMStateMsgp_ENUM,LNAS_ENTRY,pMsgStru);

    if(NAS_EMM_CHK_STAT_INVALID(stMS, stSS))
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMState: STATE ERR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SER_CHKFSMStateMsgp_ENUM,LNAS_ERROR);
        return NAS_EMM_FAIL;
    }

    if ( NAS_EMM_NULL_PTR == pMsgStru )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKMsgp: pMsgStru is NULL_PTR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SER_CHKFSMStateMsgp_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    return NAS_EMM_SUCC;
}




VOS_VOID  NAS_EMM_MmcSendSerResultIndRej
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8       ucCnCause
)
{
    LMM_MMC_SERVICE_RESULT_IND_STRU     *pstRsltInd = NAS_EMM_NULL_PTR;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO(               "NAS_EMM_MmcSendSerResultIndRej is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendSerResultIndRej_ENUM,LNAS_ENTRY);

    /* 申请MMC内部消息 */
    pstRsltInd  = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_SERVICE_RESULT_IND_STRU));

    if(NAS_EMM_NULL_PTR                 == pstRsltInd)
    {
        NAS_EMM_SER_LOG_ERR(            "NAS_EMM_SER_SendMmcActionResultReq: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendSerResultIndRej_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_MEM_SET_S(  pstRsltInd,
                        sizeof(LMM_MMC_SERVICE_RESULT_IND_STRU),
                        0,
                        sizeof(LMM_MMC_SERVICE_RESULT_IND_STRU));

    /* 填充给RRC的DOPRA头 */
    EMM_PUBU_COMP_MMC_MSG_HEADER(            pstRsltInd,
                                        sizeof(LMM_MMC_SERVICE_RESULT_IND_STRU) -
                                        EMM_LEN_VOS_MSG_HEADER);
    /*填充OPID*/


    /* 填充消息ID */
    pstRsltInd->ulMsgId                 = ID_LMM_MMC_SERVICE_RESULT_IND;

    /* 填充消息内容----SERVCIE结果 */
    pstRsltInd->ulServiceRst            = MMC_LMM_SERVICE_RSLT_CN_REJ;

    /*填充消息内容----拒绝原因值*/
    pstRsltInd->bitOpCnCause            = NAS_EMM_BIT_SLCT;
    pstRsltInd->ucCnCause               = ucCnCause;

    /* 如果SERVICE超时失败次数达最大，需要设置达到最大次数，以便MMC收到
       时判断disable LTE, CSFB场景不会报，因为CSFB场景CService计数不会加1 */
    if(NAS_EMM_GetEmmInfoDamParaCserviceCnt() >= NAS_EMM_GetEmmInfoDamParaCserviceMax())
    {
        pstRsltInd->ucIsReachMaxTimes = VOS_TRUE;
    }
    else
    {
        pstRsltInd->ucIsReachMaxTimes = VOS_FALSE;
    }


    /* 发送LMM_MMC_SERVICE_RESULT_IND消息 */
    NAS_LMM_SendLmmMmcMsg(             pstRsltInd);

    return;
}



VOS_VOID  NAS_EMM_MmcSendSerResultIndOtherType
(
    MMC_LMM_SERVICE_RSLT_ENUM_UINT32    ulSerRslt
)
{
    LMM_MMC_SERVICE_RESULT_IND_STRU     *pstRsltInd = NAS_EMM_NULL_PTR;

    /* 打印进入该函数*/
    NAS_EMM_SER_LOG_INFO("NAS_EMM_MmcSendSerResultIndOtherType is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendSerResultIndOtherType_ENUM,LNAS_ENTRY);

    /* 申请MMC内部消息*/
    pstRsltInd  = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_SERVICE_RESULT_IND_STRU));

    if(NAS_EMM_NULL_PTR                 == pstRsltInd)
    {
        NAS_EMM_SER_LOG_ERR("NAS_EMM_MmcSendSerResultIndOtherType: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendSerResultIndOtherType_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_MEM_SET_S(  pstRsltInd,
                        sizeof(LMM_MMC_SERVICE_RESULT_IND_STRU),
                        0,
                        sizeof(LMM_MMC_SERVICE_RESULT_IND_STRU));

    /* 填充给RRC的DOPRA头 */
    EMM_PUBU_COMP_MMC_MSG_HEADER(       pstRsltInd,
                                        sizeof(LMM_MMC_SERVICE_RESULT_IND_STRU) -
                                        EMM_LEN_VOS_MSG_HEADER);
    /*填充OPID*/


    /* 填充消息ID */
    pstRsltInd->ulMsgId                 = ID_LMM_MMC_SERVICE_RESULT_IND;

    /* 填充消息内容----SERVCIE结果 */
    if ((MMC_LMM_SERVICE_RSLT_FAILURE== ulSerRslt) ||
        (MMC_LMM_SERVICE_RSLT_ACCESS_BARED == ulSerRslt) ||
        (MMC_LMM_SERVICE_RSLT_AUTH_REJ == ulSerRslt))
    {

        NAS_EMM_SER_LOG1_NORM("NAS_EMM_MmcSendSerResultIndOtherType: ulSerRslt = ",
                                ulSerRslt);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MmcSendSerResultIndOtherType_ENUM,LNAS_EMM_SER_RST,
                                ulSerRslt);
        pstRsltInd->ulServiceRst            = ulSerRslt;
    }
    else
    {
        NAS_EMM_SER_LOG_WARN("NAS_EMM_MmcSendSerResultIndOtherType: ulSerRslt is err! ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MmcSendSerResultIndOtherType_ENUM,LNAS_ERROR);
    }


    /* 发送LMM_MMC_SERVICE_RESULT_IND消息 */
    NAS_LMM_SendLmmMmcMsg(             pstRsltInd);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MmcSendSerResultIndT3417Exp
 Description     : 因AT&T定制需求新增发送SERVICE结果为定时器超时给MMC，
                   CSFB或PS的SERVICE超时都调用这个
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151      2015-01-04      Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_MmcSendSerResultIndT3417Exp(VOS_VOID)
{
    LMM_MMC_SERVICE_RESULT_IND_STRU     *pstRsltInd = NAS_EMM_NULL_PTR;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO("NAS_EMM_MmcSendSerResultIndT3417Exp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendSerResultIndT3417Exp_ENUM,LNAS_ENTRY);

    /* 申请MMC内部消息 */
    pstRsltInd  = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_SERVICE_RESULT_IND_STRU));

    if(NAS_EMM_NULL_PTR == pstRsltInd)
    {
        NAS_EMM_SER_LOG_ERR("NAS_EMM_MmcSendSerResultIndT3417Exp: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendSerResultIndT3417Exp_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_MEM_SET_S(  pstRsltInd,
                        sizeof(LMM_MMC_SERVICE_RESULT_IND_STRU),
                        0,
                        sizeof(LMM_MMC_SERVICE_RESULT_IND_STRU));

    /* 填充给RRC的DOPRA头 */
    EMM_PUBU_COMP_MMC_MSG_HEADER(pstRsltInd,
                                  sizeof(LMM_MMC_SERVICE_RESULT_IND_STRU) -
                                  EMM_LEN_VOS_MSG_HEADER);
    /*填充OPID*/

    /* 填充消息ID */
    pstRsltInd->ulMsgId               = ID_LMM_MMC_SERVICE_RESULT_IND;

    /* SERVCIE结果 */
    pstRsltInd->ulServiceRst          = MMC_LMM_SERVICE_RSLT_TIMER_EXP;

    /* 拒绝原因值不填 */
    pstRsltInd->bitOpCnCause          = NAS_EMM_BIT_NO_SLCT;

    /* 如果SERVICE超时失败次数达最大，需要设置达到最大次数，以便MMC收到时判断disable LTE */
    if(NAS_EMM_GetEmmInfoDamParaCserviceCnt() >= NAS_EMM_GetEmmInfoDamParaCserviceMax())
    {
        pstRsltInd->ucIsReachMaxTimes = VOS_TRUE;
    }
    else
    {
        pstRsltInd->ucIsReachMaxTimes = VOS_FALSE;
    }


    /* 发送LMM_MMC_SERVICE_RESULT_IND消息 */
    NAS_LMM_SendLmmMmcMsg(             pstRsltInd);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SER_GetSerStartCause
 Description     : 获取当前SER触发的原因，以函数的形式提供给SER之外的其他模
                   块使用
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-02-17  Draft Enact

*****************************************************************************/
NAS_EMM_SER_START_CAUSE_ENUM_UINT8  NAS_EMM_SER_GetSerStartCause(
                                        VOS_VOID)
{
    return NAS_EMM_SER_GetEmmSERStartCause();
}

/*****************************************************************************
 Function Name   : NAS_EMM_SER_IsCsfbProcedure
 Description     : 判断是否为CSFB流程

 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010      2011-02-25  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_SER_IsCsfbProcedure( VOS_VOID )
{
    if ((NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
        || (NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
        || (NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause()))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SER_IsCsfbProcedure
 Description     : 判断是否为MO CSFB流程

 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010      2011-02-25  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_SER_IsMoCsfbProcedure( VOS_VOID )
{
    if (NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_VOID  NAS_EMM_MmSendCsfbSerPaingInd
(
    NAS_EMM_MT_CSFB_TYPE_ENUM_UINT8     enMtCsfbType,
    const NAS_EMM_CN_CS_SER_NOTIFICAIOTN_STRU *pstCsSerNotification,
    LRRC_LNAS_PAGING_UE_ID_ENUM_UINT32 enPagingUeId
)
{
    LMM_MM_CSFB_SERVICE_PAGING_IND_STRU   *pstMmCsfbSerPaingInd = VOS_NULL_PTR;

    /* 申请DOPRA消息 */
    pstMmCsfbSerPaingInd = (VOS_VOID *) NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MM_CSFB_SERVICE_PAGING_IND_STRU));
    if (NAS_LMM_NULL_PTR == pstMmCsfbSerPaingInd)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_EMM_SER_LOG_ERR("NAS_EMM_MmSendCsfbSerPaingInd: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmSendCsfbSerPaingInd_ENUM,LNAS_NULL_PTR);
        return ;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstMmCsfbSerPaingInd,
                        sizeof(LMM_MM_CSFB_SERVICE_PAGING_IND_STRU),
                        0,
                        sizeof(LMM_MM_CSFB_SERVICE_PAGING_IND_STRU));

    /* 打包VOS消息头 */
    EMM_PUBU_COMP_MM_MSG_HEADER((pstMmCsfbSerPaingInd),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MM_CSFB_SERVICE_PAGING_IND_STRU));

    /* 填充消息ID */
    pstMmCsfbSerPaingInd->ulMsgId    = ID_LMM_MM_CSFB_SERVICE_PAGING_IND;

    /* 填充消息体 */
    pstMmCsfbSerPaingInd->ulOpId     = NAS_EMM_OPID_MM;

    if (NAS_EMM_MT_CSFB_TYPE_CS_SER_NOTIFICATION == enMtCsfbType)
    {
        /* 填充CLI */
        pstMmCsfbSerPaingInd->bitOpCli = pstCsSerNotification->bitOpCli;
        pstMmCsfbSerPaingInd->ucCliLength = pstCsSerNotification->ucCliLength;
        NAS_LMM_MEM_CPY_S(  pstMmCsfbSerPaingInd->aucCliValue,
                            NAS_EMM_CLI_MAX_LEN,
                            pstCsSerNotification->aucCliValue,
                            pstCsSerNotification->ucCliLength);

        /* 填充SS CODE */
        pstMmCsfbSerPaingInd->bitOpSsCodeValue = pstCsSerNotification->bitOpSsCode;
        pstMmCsfbSerPaingInd->ucSsCodeValue = pstCsSerNotification->ucSsCodeValue;
        if (0 == pstCsSerNotification->ucPagingIdenity)
        {
            pstMmCsfbSerPaingInd->enPagingUeId = LMM_MM_PAGING_IND_UE_ID_IMSI;
        }
        else
        {
            pstMmCsfbSerPaingInd->enPagingUeId = LMM_MM_PAGING_IND_UE_ID_TMSI;
        }

    }
    else
    {
        if(LRRC_LNAS_S_TMSI_LTE == enPagingUeId)
        {
            pstMmCsfbSerPaingInd->enPagingUeId = LMM_MM_PAGING_IND_UE_ID_S_TMSI;
        }
        else if(LRRC_LNAS_IMSI_LTE == enPagingUeId)
        {
            pstMmCsfbSerPaingInd->enPagingUeId = LMM_MM_PAGING_IND_UE_ID_IMSI;
        }
        else
        {

        }
    }

    /* 发送DOPRA消息 */
    NAS_LMM_SendLmmMmcMsg((VOS_VOID*)pstMmCsfbSerPaingInd);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MmSendCsfbSerEndInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010      2012-02-23  Draft Enact
    2.sunjitan 00193151    2014-10-11  Mod: CSFB ERR LOG上报
*****************************************************************************/
VOS_VOID  NAS_EMM_MmSendCsfbSerEndInd
(
    MM_LMM_CSFB_SERVICE_RSLT_ENUM_UINT32     enCsfbSrvRslt,
    NAS_EMM_CN_CAUSE_ENUM_UINT8              ucEMMCnCause
)
{
    LMM_MM_CSFB_SERVICE_END_IND_STRU   *pstMmCsfbSerEndInd = VOS_NULL_PTR;

    /* 如果已经收到ABORT消息，则不用通知MM终止CSFB流程 */
    if (NAS_EMM_CSFB_ABORT_FLAG_VALID == NAS_EMM_SER_GetEmmSerCsfbAbortFlag())
    {
        NAS_EMM_SER_LOG_WARN("NAS_EMM_MmSendCsfbSerEndInd:CSFB is already aborted!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MmSendCsfbSerEndInd_ENUM,LNAS_FUNCTION_LABEL1);
        return ;
    }

    /* 申请DOPRA消息 */
    pstMmCsfbSerEndInd = (VOS_VOID *) NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MM_CSFB_SERVICE_END_IND_STRU));
    if (NAS_LMM_NULL_PTR == pstMmCsfbSerEndInd)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_EMM_SER_LOG_ERR("NAS_EMM_MmSendCsfbSerEndInd: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmSendCsfbSerEndInd_ENUM,LNAS_NULL_PTR);
        return ;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstMmCsfbSerEndInd,
                        sizeof(LMM_MM_CSFB_SERVICE_END_IND_STRU),
                        0,
                        sizeof(LMM_MM_CSFB_SERVICE_END_IND_STRU));

    /* 打包VOS消息头 */
    EMM_PUBU_COMP_MM_MSG_HEADER((pstMmCsfbSerEndInd),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MM_CSFB_SERVICE_END_IND_STRU));

    /* 填充消息ID */
    pstMmCsfbSerEndInd->ulMsgId    = ID_LMM_MM_CSFB_SERVICE_END_IND;

    /* 填充消息体 */
    pstMmCsfbSerEndInd->ulOpId     = NAS_EMM_OPID_MM;

    pstMmCsfbSerEndInd->enCsfbSrvRslt = enCsfbSrvRslt;

    /* s00193151 add 2014-10-11: DTS2014102701776 for csfb err log 上报 */
    pstMmCsfbSerEndInd->ulCnCause = ucEMMCnCause;

    /* 发送DOPRA消息 */
    NAS_LMM_SendLmmMmcMsg((VOS_VOID*)pstMmCsfbSerEndInd);

    return;
}
/*lint +e961*/
/*lint +e960*/
/*****************************************************************************
 Function Name   : NAS_EMM_RestartSerProcedural
 Description     : 重启SERVICE流程
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         : wangchen  00209181   2013-03-30  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_RestartSerProcedural(VOS_VOID)
{
    /* 重启SERVICE流程 */
    switch (NAS_EMM_SER_GetEmmSERStartCause())
    {
        case NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ:
        case NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ:
        case NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ:

            /*停止T3417定时器*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

            /*停止T3440定时器*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

            /*停止T3417ext定时器*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

            /*启动定时器3417*/
            NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

            /*转换EMM状态机MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
            NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

            /*组合并发送MRRC_DATA_REQ(SERVICE_REQ)*/
            NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();
            break;

        default :

            /*停止T3417定时器*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

            /*停止T3440定时器*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

            /*停止T3417ext定时器*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

            /*启动定时器3417*/
            NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

            /*转换EMM状态机MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
            NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417);

            /*组合并发送MRRC_DATA_REQ(SERVICE_REQ)*/
            NAS_EMM_SER_SendMrrcDataReq_ServiceReq();
            break;
    }

    return ;
}


/*****************************************************************************
 Function Name   : NAS_EMM_EmcPndReqSerAbnormalCommProc
 Description     : 紧急类型的PDN连接建立引起的SERVICE异常的公共处理
 Input           : ucSs---------------------子状态
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010      2012-12-31  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_EmcPndReqSerAbnormalCommProc
(
    NAS_EMM_SUB_STATE_ENUM_UINT16       ucSs
)
{
    NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);

    /* 本地DETACH释放资源:动态内存、赋初值 */
    NAS_LMM_DeregReleaseResource();

    /*向MMC发送本地LMM_MMC_DETACH_IND消息*/
    NAS_EMM_MmcSendDetIndLocal( MMC_LMM_L_LOCAL_DETACH_OTHERS);

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_OTHER);
    #endif

    /* 记录ATTACH触发原因值 */
    NAS_EMM_GLO_AD_GetAttCau() = EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER;

    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                ucSs,
                                TI_NAS_EMM_STATE_NO_TIMER);
}

/*******************************************************************************
  Function : NAS_EMM_ExtSerReqReTranProc
  Input    : ulOpid
  Output   : NONE
  NOTE     : Ext Ser Req重传处理(目前NO RF或者HO导致Ext Ser Req上行直传发送失败,在收到系统消息后需要重传)
  Return   : NONE
  History  :
    1.leixianitao 00258641       2015-2-4      新规作成
*******************************************************************************/
VOS_VOID NAS_EMM_ExtSerReqRetranProc(VOS_UINT32 ulOpid)
{
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData;
    VOS_UINT32                          ulIndex = 0;
    NAS_EMM_MRRC_DATA_REQ_STRU          *pMrrcDataMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRrcMmDataReqMsgLen;

    pEmmMrrcMgmtData = NAS_EMM_FindMsgInDataReqBuffer(ulOpid);
    if(VOS_NULL_PTR == pEmmMrrcMgmtData)
    {
        return;
    }
    ulRrcMmDataReqMsgLen = (sizeof(NAS_EMM_MRRC_DATA_REQ_STRU)+
                                   pEmmMrrcMgmtData->ulNasMsgLength) -
                                   NAS_EMM_4BYTES_LEN;

    /* 申请消息内存*/
    pMrrcDataMsg = (NAS_EMM_MRRC_DATA_REQ_STRU *)(VOS_VOID*)NAS_LMM_MEM_ALLOC(ulRrcMmDataReqMsgLen);
    if(VOS_NULL_PTR == pMrrcDataMsg)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_ProcHoWaitSysInfoBufferMsg: Mem Alloc Fail");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_ExtSerReqRetranProc_ENUM,LNAS_FUNCTION_LABEL1);
        return;
    }

    /* 重发EXTENDED SERVICE REQ消息 */
    pMrrcDataMsg->enDataCnf = LRRC_LMM_DATA_CNF_NEED;

    pMrrcDataMsg->enEmmMsgType = NAS_EMM_MSG_EXTENDED_SERVICE_REQ;
    pMrrcDataMsg->ulMsgId = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;
    pMrrcDataMsg->ulEsmMmOpId = pEmmMrrcMgmtData->ulEsmMmOpId;

    /*组装EXTENDED SERVICE REQ消息*/
    NAS_EMM_CompCnExtendedSerReqMoNasMsg(pMrrcDataMsg->stNasMsg.aucNasMsg, &ulIndex);

    pMrrcDataMsg->stNasMsg.ulNasMsgSize = ulIndex;

    NAS_EMM_SndUplinkNasMsg(pMrrcDataMsg);
     /*释放所申请内存 */
    NAS_LMM_MEM_FREE(pMrrcDataMsg);
}

/*****************************************************************************
 Function Name   : NAS_EMM_SER_CServiceCountProc
 Description     : AT&T美国需求对SERVICE异常失败计数的处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151      2015-01-04  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_SER_CServiceCountProc(VOS_VOID)
{
    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO("NAS_EMM_SER_CServiceCountProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_CServiceCountProc_ENUM,LNAS_ENTRY);

    if(NAS_EMM_YES != NAS_EMM_IsDamConfitionSatisfied())
    {
         return;
    }

    if(VOS_FALSE != NAS_EMM_SER_IsCsfbProcedure())
    {
        return;
    }

    NAS_EMM_GetEmmInfoDamParaCserviceCnt()++;

    /* 输出操作之后的参数到OM */
    NAS_LMM_SndOmDamPara();

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcHoRetransESRMsg
 Description     : 针对网络侧缺陷所写函数
                   UE发送ESR消息,并且搜到网络发送成功消息的响应,此时发送X2接口的切换
                   UE切换成功后,MME应该重新触发eNB发送CSFB流程,因为网络异常,CSFB流程没有发起来
                   UE未收到重定向GU的异系统流程,导致T3417ext超时
                   优化为:UE识别该场景,重新发送一次ESR,触发网络发起CSFB流程
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing 00265702      2015-06-13  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_ProcHoRetransESRMsg(VOS_VOID)
{
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulIndex = 0;

    /* 当前不是CSFB流程,或者重传ESR消息NV未打开,或者是测试卡,
        或者当前不存在用户名RB,或者当前用户已经挂断电话, 则退出当前函数 */
    if ((VOS_TRUE != NAS_EMM_SER_IsCsfbProcedure())
         ||(PS_SUCC == LPS_OM_IsTestMode())
         ||(PS_FALSE == g_ulNasEmmHoRetransEsrFlag)
         ||(NAS_EMM_CONN_DATA != NAS_EMM_GetConnState())
         ||(NAS_EMM_CSFB_ABORT_FLAG_VALID == NAS_EMM_SER_GetEmmSerCsfbAbortFlag()))
    {
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProcHoRetransESRMsg_ENUM, LNAS_FUNCTION_LABEL1, g_ulNasEmmHoRetransEsrFlag);
        NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ProcHoRetransESRMsg g_ulNasEmmHoRetransEsrFlag = ", g_ulNasEmmHoRetransEsrFlag);
        return;
    }

    /* 未发送成功消息个数合法性检查 */
    if ( g_ulSaveMsgNum > NAS_LMM_RRC_SAVE_MSG_MAX_NUM )
    {
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProcHoRetransESRMsg_ENUM, LNAS_FUNCTION_LABEL2, g_ulSaveMsgNum);
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_ProcHoRetransESRMsg: g_ulSaveMsgNum is error");
        g_ulSaveMsgNum = NAS_LMM_RRC_SAVE_MSG_MAX_NUM;
    }
    pEmmMrrcMgmtData                    = NAS_EMM_GET_MRRC_MGMT_DATA_ADDR();
    /* 查找缓存记录,是否有未发送成功的ESR消息 */
    while((ulIndex < g_ulSaveMsgNum))
    {
        if ( NAS_EMM_MSG_EXTENDED_SERVICE_REQ == pEmmMrrcMgmtData->enLastMsgId )
        {
            TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProcHoRetransESRMsg_ENUM, LNAS_FUNCTION_LABEL3, ulIndex);
            NAS_EMM_PUBU_LOG_WARN("NAS_EMM_ProcHoRetransESRMsg: ESR MSG is exit");
            break;
        }

        pEmmMrrcMgmtData++;

        ulIndex ++;
    }

    /* 未找到缓存的ESR,且T3417ext在运行,则重传ESR */
    if ((ulIndex == g_ulSaveMsgNum)
        &&(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_SERVICE_T3417_EXT)))
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_ProcHoRetransESRMsg: RetransESR");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcHoRetransESRMsg_ENUM, LNAS_FUNCTION_LABEL4);
        NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();

        #if (FEATURE_ON == FEATURE_PTM)
        NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_ESR_RESEND_FOR_HO);
        #endif
    }

    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_SndLrrcLmmCsfbNotify
 Description     : CSFB优化:LMM通知LRRC CSFB 启动和结束,LRRC用于判断是否是CSFB流程
                   解决网侧不下发重定向释放的问题
 Input           : enCsfbStatus
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leixiantiao 00258641      2015-07-07  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_ENUM_UINT16 enCsfbStatus)
{
    LRRC_LMM_CSFB_NOTIFY_STRU           *pstLrrcCsfbNotifyMsg;

    /* INIT主要用于EXT空口发送过程中发生重建,直接主动释放搜网去GU,建链过程不可能发生重建,
       所以IDLE态不需要通知RRC INIT(空口发送成功后LMM会通知LRRC CSFB START) */
    if((LRRC_LNAS_CSFB_STATUS_INIT == enCsfbStatus)
        &&((NAS_EMM_CONN_SIG != NAS_EMM_GetConnState())
            && (NAS_EMM_CONN_DATA != NAS_EMM_GetConnState())))
    {
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SndLrrcLmmCsfbNotify_ENUM, LNAS_EMM_NOT_CONN_STATUS);
        NAS_EMM_PUBU_LOG_INFO(" NAS_EMM_SndLrrcLmmCsfbNotify Not Notfiy Csfb Init ");
        return;
    }
    /* 申请DOPRA消息 */
    pstLrrcCsfbNotifyMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(LRRC_LMM_SUSPEND_RSP_STRU));
    if (NAS_LMM_NULL_PTR == pstLrrcCsfbNotifyMsg)
    {
        return ;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstLrrcCsfbNotifyMsg,
                        sizeof(LRRC_LMM_SUSPEND_RSP_STRU),
                        0,
                        sizeof(LRRC_LMM_SUSPEND_RSP_STRU));

    /* 打包VOS消息头 */
    NAS_EMM_SET_RRC_MSG_HEADER((pstLrrcCsfbNotifyMsg),
            NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LRRC_LMM_CSFB_NOTIFY_STRU));

    /* 填充消息ID */
    pstLrrcCsfbNotifyMsg->enMsgId       = ID_LRRC_LMM_CSFB_NOTIFY;
    pstLrrcCsfbNotifyMsg->enCsfbStatus  = enCsfbStatus;

    /* 发送DOPRA消息 */
    NAS_LMM_SEND_MSG(pstLrrcCsfbNotifyMsg);

    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_SER_TbackoffProc
 Description     : AT&T美国需求对SERVICE异常失败补偿定时器的处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yanglei 00307272      2015-12-10  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_SER_TbackoffProc(VOS_VOID)
{

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO("NAS_EMM_SER_TbackoffProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_TbackoffProc_ENUM,LNAS_ENTRY);

    if(NAS_EMM_YES != NAS_EMM_IsDamConfitionSatisfied())
    {
         return;
    }

    if(VOS_FALSE != NAS_EMM_SER_IsCsfbProcedure())
    {
        return;
    }

    if(NAS_EMM_GetEmmInfoDamParaCserviceCnt() >= NAS_EMM_GetEmmInfoDamParaCserviceMax())
    {
        if(NAS_LMM_FAIL == NAS_EMM_CheckMutiModeSupport())
        {
            /* 将T3402长度赋值给Tbackoff */
            NAS_LMM_ModifyPtlTimer(TI_NAS_EMM_PTL_SER_BACKOFF_TIMER,NAS_EMM_GetEmmInfoDamParaT3402Len());

            /* 启动Tbackoff定时器 */
            NAS_LMM_StartPtlTimer( TI_NAS_EMM_PTL_SER_BACKOFF_TIMER);
            NAS_EMM_GetEmmInfoDamParaCserviceCnt() = 0;
        }
    }

    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_IsSerConditionSatisfied
 Description     : AT&T美国需求 判断SERVICE能否发起的定时器
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yanglei 00307272      2015-12-10  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_IsSerConditionSatisfied(VOS_VOID)
{


    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO("NAS_EMM_IsSerConditionSatisfied is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_IsSerConditionSatisfied_ENUM,LNAS_ENTRY);

    if( NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_SER_BACKOFF_TIMER))
    {

            NAS_EMM_SER_LOG_INFO("NAS_EMM_IsSerConditionSatisfied not satisfied.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_IsSerConditionSatisfied_ENUM,LNAS_FAIL);

            return NAS_EMM_NO;
    }


    return NAS_EMM_YES;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


