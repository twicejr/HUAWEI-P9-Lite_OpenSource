/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEmmPubUEntry.c
    Description :
    History     :
      1.  hanlufeng 41410  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEmmPubUEntry.h"
#include    "NasLmmPubMOm.h"
#include    "NasLmmPubMTimer.h"
#include    "NasEmmMrrcPubInterface.h"
#include    "NasEmmAttDetInterface.h"
#include    "NasLmmPubMPrint.h"
#include    "NasEmmAttachCnMsgProcess.h"
#include    "NasEmmPlmnInterface.h"
#include    "NasEmmTAUProc.h"
#include    "NasEmmSmsInterface.h"
#include    "NasEmmSerProc.h"
#include    "NasEmmcPublic.h"

#include    "ImsaIntraInterface.h"
#if (FEATURE_LPP == FEATURE_ON)
#include    "EmmLppInterface.h"
#include    "NasEmmSsMsgProc.h"
#include    "NasEmmLppMsgProc.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMPUBUENTRY_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMPUBUENTRY_C
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

/* CN消息码流解码后的结构体，消息太长，不适合作函数的局部变量 */
NAS_EMM_CN_MSG_STRU                     g_stCnDecodeMsgStru;

/*****************************************************************************
  3 Function
*****************************************************************************/


/*****************************************************************************
 Function Name  : NAS_EMM_MsgProcessInFsm
 Discription    : EMM 消息进状态机处理
 Input          : 并行状态机ID 消息指针 事件类型
                  pOsaOrCnStruMsg:
                        当消息类型为ID_RRC_MM_DATA_IND,该指针指向解码后的CN消息结构
                        当其他消息类型时，指向从DOPRA收到的消息结构
 Output         : None
 Return         :该消息是否处理
 History:
                  hanlufeng 41410  Draft Enact
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_UINT32 NAS_EMM_MsgProcessInFsm(     MsgBlock           *pMsg,
                                        VOS_UINT32          ulEventType)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulMsgId;
    VOS_VOID                            *pOsaOrCnStruMsg;    /* 传给EMM状态机处理的消息结构的指针 */


    pOsaOrCnStruMsg                     = (VOS_VOID *)pMsg;


    /* EMM 预处理, 若预处理成功,则不再进入EMM主状态机处理 */
    ulRet                               = NAS_EMM_MsgPreProcess( ulEventType, pMsg );
    /* 获取消息ID */
    NAS_LMM_GetNameFromMsg(ulMsgId, pMsg);

    /* 如果没有预处理,进入EMM状态机处理 */
    if ( (NAS_LMM_MSG_DISCARD == ulRet ) )
    {

        if(ID_LRRC_LMM_DATA_IND == ulMsgId)
        {   /* 是CN消息，则进行 CN码流解码 */

            /* 传给EMM状态机处理的消息结构的指针 指向解码后的结构体 */
            pOsaOrCnStruMsg         = &(g_stCnDecodeMsgStru.uCnMsgStru);
        }

        /*如果是内部空口消息转发，直接取空口消息的解码结果*/
        if(ID_NAS_LMM_INTRA_DATA_IND == ulMsgId)
        {
            pOsaOrCnStruMsg         = &(g_stCnDecodeMsgStru.uCnMsgStru);
        }

        /* 然后进入EMM 的状态机处理 */
        ulRet = NAS_LMM_MsgProcessInFsm( NAS_LMM_PARALLEL_FSM_EMM,
                                        pOsaOrCnStruMsg,
                                        ulMsgId,
                                        ulEventType);
    }

    return ulRet;
}


/*****************************************************************************
 Function Name  :NAS_EMM_MsgPreProcess
 Discription    :
 Input          :
 Output         : None
 Return         : 该消息是否被处理
 History:
      1.  hanlufeng 41410  Draft Enact
      2.  zhengjunyan 00148421 2010-12-29 Mod:ID_EMM_ERABM_REL_REQ功能修改，
                                          不做为严重异常处理
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsgPreProcess(  NAS_EMM_EVENT_TYPE_ENUM_UINT32      ulEt,
                                    MsgBlock                           *pMsg )
{
    VOS_UINT32                          ulRet;
    LRRC_LMM_DATA_IND_STRU               *pstTmpRcvMsg       = NAS_EMM_NULL_PTR;
    VOS_UINT8                          *pRcvMsg            = NAS_EMM_NULL_PTR;
    VOS_UINT8                           ucPD               = NAS_EMM_NULL;
    VOS_UINT8                           ucAirMsg           = NAS_EMM_NULL;
    VOS_UINT8                           ucKeyEvent         = NAS_EMM_NULL;
    NAS_LMM_FSM_STATE_STRU              *pstFsmCtx          = NAS_LMM_NULL_PTR;

    ulRet = NAS_LMM_MSG_DISCARD;

    /*结构化消息，取出消息体*/
    pstTmpRcvMsg = (LRRC_LMM_DATA_IND_STRU*)pMsg;
    pRcvMsg      = pstTmpRcvMsg->stNasMsg.aucNasMsg;

    if(ID_LRRC_LMM_DATA_IND == pstTmpRcvMsg->enMsgId)
    {
        /*取出PD*/
        ucPD = pRcvMsg[NAS_EMM_NULL]& EMM_CN_MSG_PDMASK;

        /* 如果是ESM消息直接上报ESM */
        if  (EMM_CN_MSG_PD_ESM == ucPD)
        {
            /* 转发给ESM消息 */
            NAS_EMM_EsmSendDataInd((NAS_EMM_CN_MSGCON_STRU *)&(pstTmpRcvMsg->stNasMsg));
            return  NAS_LMM_MSG_HANDLED;
        }
        /* 如果是TC消息直接上报TC */
        if  (EMM_CN_MSG_PD_TC == ucPD)
        {
            /* 转发给TC消息 */
            NAS_EMM_TcSendDataInd((NAS_EMM_CN_MSGCON_STRU *)&(pstTmpRcvMsg->stNasMsg));
            return  NAS_LMM_MSG_HANDLED;
        }

        /*空口消息上报*/
        if(EMM_CN_MSG_PD_EMM == ucPD)
        {
            NAS_LMM_FindAirMsgId(pRcvMsg[NAS_LMM_CN_MSG_MT_POS], &ucAirMsg, &ucKeyEvent);
            /* 判断该空口消息中是否含有短信内容，若含有，则不勾这条消息 */
            if (NAS_EMM_NO == NAS_LMM_IsMsgContainsSMS(pstTmpRcvMsg->stNasMsg.ulNasMsgSize, &pstTmpRcvMsg->stNasMsg.aucNasMsg[0]))
            {
                NAS_LMM_SendOmtAirMsg(NAS_EMM_OMT_AIR_MSG_DOWN,
                                            ucAirMsg,
                                            (NAS_MSG_STRU*)&(pstTmpRcvMsg->stNasMsg));
            }

            if (NAS_EMM_NULL != ucKeyEvent)
            {
                NAS_LMM_SendOmtKeyEvent(ucKeyEvent);
            }

            NAS_LMM_MEM_SET_S(&g_stCnDecodeMsgStru, sizeof(NAS_EMM_CN_MSG_STRU), 0, sizeof(NAS_EMM_CN_MSG_STRU));

            ulRet = NAS_EMM_DecodeCnMsg(pMsg, &g_stCnDecodeMsgStru);

            if(NAS_EMM_FAIL == ulRet )
            {/* 若解码出错,打印报警 */

                NAS_LMM_PUBM_LOG1_ERR("NAS_EMM_MsgProcessInFsm, ulEventType = ", ulEt);
                TLPS_PRINT2LAYER_ERROR1(NAS_EMM_MsgPreProcess_ENUM,LNAS_FAIL,ulEt);

                /*发送EMM STATUS, 接收到不识别的消息 */
                NAS_EMM_SendMsgEmmStatus( NAS_LMM_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE );
                return NAS_LMM_MSG_HANDLED;
            }

            /* 对EMM INFO 和 EMM STATUS 进行处理 */
            ulRet = NAS_EMM_PreProcMsgDataInd();
            return  ulRet;

        }

        ulRet                       = NAS_LMM_MSG_DISCARD;
    }

    /* SM异常消息的处理*/
    if(ID_EMM_ESM_REL_REQ == pstTmpRcvMsg->enMsgId)
    {

        /* 获取状态机地址,用于取状态 */
        pstFsmCtx = NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM);

        switch(pstFsmCtx->enMainState)
        {
            case EMM_MS_REG:
            case EMM_MS_REG_INIT:
            case EMM_MS_TAU_INIT:
            case EMM_MS_SER_INIT:
                 NAS_EMM_SmRabmAbnarmalProc();
                 break;
            default:
                 NAS_LMM_PUBM_LOG1_INFO("current MS discard abnormal MSG=========>>>>",
                                        pstTmpRcvMsg->enMsgId);
                 TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsgPreProcess_ENUM,LNAS_FUNCTION_LABEL1,pstTmpRcvMsg->enMsgId);
                 break;
        }
        ulRet                           = NAS_LMM_MSG_HANDLED;
    }

    return  ulRet;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SmRabmAbnarmalProc
 Description     : 向SM发送ID_EMM_ESM_STATUS_IND,清空资源，EMM，MMC状态机转换
                   到准备搜网的状态，发送内部搜网请求
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.qilili 00145085      2009-1-17  Draft Enact
    2.X00148705            2009-09-23 直接向RRC发 REL_REQ消息
    3.l00132387            2011-06-03 修改收到ESM/ERABM异常的处理
*****************************************************************************/
VOS_VOID    NAS_EMM_SmRabmAbnarmalProc( VOS_VOID )
{

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_SmRabmAbnarmalProc is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SmRabmAbnarmalProc_ENUM,LNAS_ENTRY);

    /* 复位处理*/
    NAS_EMM_SendMmcErrInd(NAS_EMM_REBOOT_TYPE_ESM_ABNORMAL);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_PUB_SendMmcStartReq
 Description     : 向MMC发送MMC_EMM_START_REQ消息
 Input           : None
 Output          : None
 Return          :

 History         :
    1.qilili00145085     2009-01-23 Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_PUB_SendMmcStartReq( VOS_UINT32 encause  )
{
    EMMC_EMM_START_REQ_STRU              *pstMmcStartReqMsg;
    VOS_UINT32                          ulMsgLengthNoHeader;
    VOS_UINT32                          ulSendResult;

    /* 计算EMM要发给内部其它模块的内部消息长度, 不包含VOS头 */
    ulMsgLengthNoHeader = NAS_EMM_PUB_INTRAMSG_LENGTH_NO_HEADER(EMMC_EMM_START_REQ_STRU);

    /* 获取内部消息地址 */
    pstMmcStartReqMsg = (VOS_VOID *) NAS_LMM_GetSendIntraMsgBuffAddr(ulMsgLengthNoHeader);
    if (NAS_EMM_NULL_PTR == pstMmcStartReqMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_PLMN_SendMmcStartReq: GET INTRAMSG ADDR ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_PUB_SendMmcStartReq_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    /* 打包内部消息头 */
    NAS_EMM_COMP_INTRA_MSG_HEADER((pstMmcStartReqMsg), ulMsgLengthNoHeader);

    /* 填充内部消息ID */
    pstMmcStartReqMsg ->enMsgId         = ID_EMMC_EMM_START_REQ;

    /* 填充消息体 */
    pstMmcStartReqMsg->enCause          = encause;

    /* 向MMC发送MMC_EMM_START_REQ内部消息 */
    NAS_EMM_SEND_INTRA_MSG(             pstMmcStartReqMsg);
    ulSendResult =                      NAS_EMM_OK;
    return ulSendResult;
}


VOS_VOID    NAS_EMM_PUB_SendEsmStatusInd
(
    VOS_UINT32  ulATTACHStatus
)
{
    EMM_ESM_STATUS_IND_STRU                *pstsmstatusInd = NAS_EMM_NULL_PTR;

    /* 打印进入该函数*/
    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_PUB_SendEsmStatusInd is entered.", ulATTACHStatus);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PUB_SendEsmStatusInd_ENUM,LNAS_ENTRY,ulATTACHStatus);

    /* 申请DOPRA消息 */
    pstsmstatusInd  = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_STATUS_IND_STRU));

    if(NAS_EMM_NULL_PTR == pstsmstatusInd)
    {
        return;
    }

    /* 填充给ESM的DOPRA头 */
    NAS_EMM_COMP_ESM_MSG_HEADER(pstsmstatusInd, sizeof(EMM_ESM_STATUS_IND_STRU) -
                                        NAS_EMM_LEN_VOS_MSG_HEADER);

    /* 填充消息ID */
    pstsmstatusInd->ulMsgId             = ID_EMM_ESM_STATUS_IND;

    /* 填充消息内容 -- stATTACHStatus */
    pstsmstatusInd->enEMMStatus         = ulATTACHStatus;

    /*clear global:EpsContextStatusChange*/
    if(ulATTACHStatus == EMM_ESM_ATTACH_STATUS_DETACHED)
    {
        NAS_EMM_GetEpsContextStatusChange() = NAS_EMM_EPS_BEARER_STATUS_NOCHANGE;
    }

    /* 发送DOPRA消息 */
    NAS_LMM_SEND_MSG(pstsmstatusInd);

    return;

}

#if (FEATURE_LPP == FEATURE_ON)
/*****************************************************************************
 Function Name   : NAS_LMM_SndLmmLppDataInd
 Description     : 向LPP发送ID_LMM_LPP_DATA_IND
 Input           :
 Output          :
 Return          : 处理结果
 History         :
    lifuxin 00253982 2015-07-17  新开发
*****************************************************************************/
VOS_VOID NAS_LMM_SndLmmLppDataInd
(
    NAS_EMM_ADDITIONAL_INFOR_STRU               *pstAdditionalInfo,
    NAS_EMM_GENERIC_MESSAGE_CONTAINER_STRU      *pstContainer
)
{
    LMM_LPP_DATA_IND_STRU                  *pLmmLppDataInd      = NAS_EMM_NULL_PTR;
    VOS_UINT32                              ulTmpLength         = 0;

    NAS_EMM_PUBU_LOG_NORM("NAS_LMM_SndLmmLppDataInd enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_SndLmmLppDataInd_ENUM, LNAS_LPP_Func_Enter);

    if( 0 == pstContainer->usMsgLen)
    {
        return ;
    }
    else if(pstContainer->usMsgLen > NAS_EMM_4BYTES_LEN)
    {
        ulTmpLength = pstContainer->usMsgLen - NAS_EMM_4BYTES_LEN ;
        pLmmLppDataInd = (VOS_VOID*)NAS_LMM_ALLOC_MSG(sizeof(LMM_LPP_DATA_IND_STRU) + ulTmpLength);
    }
    else/*如果长度小于NAS_EMM_4BYTES_LEN，分配的空间等于NAS_EMM_4BYTES_LEN*/
    {
        ulTmpLength = 0;
        pLmmLppDataInd = (VOS_VOID*)NAS_LMM_ALLOC_MSG(sizeof(LMM_LPP_DATA_IND_STRU));
    }

    /*判断申请结果，若失败退出*/
    if (NAS_EMM_NULL_PTR == pLmmLppDataInd)
    {
        return ;
    }

    /*构造ID_LMM_LPP_DATA_IND消息*/
    /*填充消息头*/
    NAS_EMM_LPP_MSG_HEADER(pLmmLppDataInd,
                           ((sizeof(LMM_LPP_DATA_IND_STRU) + ulTmpLength) - NAS_EMM_LEN_VOS_MSG_HEADER));

    /*填充消息ID*/
    pLmmLppDataInd->ulMsgId = ID_LMM_LPP_DATA_IND;

    /*填充消息内容*/
    /*填充sessionId*/
    NAS_LMM_MEM_CPY_S(  &(pLmmLppDataInd->ulSessionId),
                        sizeof(pLmmLppDataInd->ulSessionId),
                        pstAdditionalInfo->aucMsg,
                        pstAdditionalInfo->ucMsgLen);

    /*填充LPP空口码流*/
    pLmmLppDataInd->stLppMsg.ulLppMsgSize = pstContainer->usMsgLen;
    NAS_LMM_MEM_CPY_S(  pLmmLppDataInd->stLppMsg.aucLppMsg,
                        pLmmLppDataInd->stLppMsg.ulLppMsgSize,
                        pstContainer->aucMsg,
                        pLmmLppDataInd->stLppMsg.ulLppMsgSize);

    /*向LPP发送ID_LMM_LPP_DATA_IND消息*/
    NAS_LMM_SEND_MSG(pLmmLppDataInd);

    return;
}
#endif

/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgDlNasGenericTransport
 Description     : LMM收到downlink generic transport消息的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lifuxin    00253982      2015-07-25  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgDlNasGenericTransport( NAS_EMM_CN_MSG_STRU_UNION  * pCnMsg )
{
#if (FEATURE_LPP == FEATURE_ON)
    NAS_EMM_CN_DOWNLINK_GENERIC_NAS_TRANSPORT_STRU *pTmpRcvMsg          = NAS_EMM_NULL_PTR;

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_PreProcMsgDlNasGenericTransport is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgDlNasGenericTransport_ENUM, LNAS_LPP_Func_Enter);

    pTmpRcvMsg = (NAS_EMM_CN_DOWNLINK_GENERIC_NAS_TRANSPORT_STRU*)pCnMsg;

    if (NAS_EMM_GENERIC_CONTAINER_TYPE_LPP == pTmpRcvMsg->ucContainerType)
    {
        if (NAS_EMM_BIT_SLCT != pTmpRcvMsg->bitOpAdditionalInfo)
        {
            NAS_EMM_PUBU_LOG_WARN("NAS_EMM_PreProcMsgDlNasGenericTransport: LPP MSG no additional info");
            TLPS_PRINT2LAYER_WARNING(NAS_EMM_PreProcMsgDlNasGenericTransport_ENUM, LNAS_LPP_NoAdditionInfo);

            return NAS_LMM_MSG_HANDLED;
        }

        NAS_LMM_SndLmmLppDataInd(&(pTmpRcvMsg->stAdditionalInfo),
                                 &(pTmpRcvMsg->stContainer));
    }

    if (NAS_EMM_GENERIC_CONTAINER_TYPE_LCS == pTmpRcvMsg->ucContainerType)
    {
        NAS_LMM_SndLcsDataInd(&(pTmpRcvMsg->stContainer));
    }

    return NAS_LMM_MSG_HANDLED;
#else
    NAS_EMM_PUBU_LOG_WARN("NAS_EMM_PreProcMsgDlNasGenericTransport:LPP FEATURE NOT SUPPORT");
    TLPS_PRINT2LAYER_WARNING(NAS_EMM_PreProcMsgDlNasGenericTransport_ENUM, LNAS_LPP_LppFeatureNotSupport);
    return NAS_LMM_MSG_HANDLED;
#endif
}


/*lint -e826 */

VOS_UINT32  NAS_EMM_PreProcMsgDataInd( VOS_VOID )
{
    VOS_UINT32                           ulRet;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_PreProcMsgDataInd enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgDataInd_ENUM,LNAS_ENTRY);

    /*根据消息类型进入不同的处理函数，如果不是EmmInformation或者EmmStatus消息就进入状态机*/
    if (NAS_EMM_CN_MT_EMM_INFO == g_stCnDecodeMsgStru.ulCnMsgType)
    {
        ulRet = NAS_EMM_PreProcMsgEmmInfo(&(g_stCnDecodeMsgStru.uCnMsgStru));
    }
    else if (NAS_EMM_CN_MT_EMM_STATUS == g_stCnDecodeMsgStru.ulCnMsgType)
    {
        ulRet = NAS_EMM_PreProcMsgEmmStatus(&(g_stCnDecodeMsgStru.uCnMsgStru));
    }
    else if (NAS_EMM_CN_MT_DOWNLINK_NAS_TRANSPORT == g_stCnDecodeMsgStru.ulCnMsgType)
    {
        ulRet = NAS_EMM_PreProcMsgDlNasTransport(&(g_stCnDecodeMsgStru.uCnMsgStru));
    }
    else if (NAS_EMM_CN_CS_SER_NOTIFICATION == g_stCnDecodeMsgStru.ulCnMsgType)
    {
        ulRet = NAS_EMM_PreProcMsgCsSerNotification(&(g_stCnDecodeMsgStru.uCnMsgStru));
    }
    #if (FEATURE_LPP == FEATURE_ON)
    else if (NAS_EMM_CN_MT_DOWNLINK_GENERIC_NAS_TRANSPORT == g_stCnDecodeMsgStru.ulCnMsgType)
    {
        ulRet = NAS_EMM_PreProcMsgDlNasGenericTransport(&(g_stCnDecodeMsgStru.uCnMsgStru));
    }
    #endif
    else
    {
        ulRet = NAS_LMM_MSG_DISCARD;
    }

    return ulRet;
}



VOS_UINT32  NAS_EMM_PreProcMsgEmmInfo( NAS_EMM_CN_MSG_STRU_UNION  * pCnMsg )
{
    NAS_EMM_INFO_STRU                   *pstEmmInfo;
    NAS_EMM_CN_EMM_INFO_STRU            *pstTmpRcvMsg       = NAS_EMM_NULL_PTR;
    VOS_UINT8                           ucCount = 0;

    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_PreProcMsgEmmInfo enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgEmmInfo_ENUM,LNAS_ENTRY);

    pstTmpRcvMsg               = (NAS_EMM_CN_EMM_INFO_STRU*)pCnMsg;
    pstEmmInfo                 = NAS_LMM_GetEmmInfoNasEmmInfoListAddr();

    NAS_LMM_MEM_SET_S(pstEmmInfo, sizeof(NAS_EMM_INFO_STRU), 0, sizeof(NAS_EMM_INFO_STRU));

    /* 上报网络时间和网络名称，只要能收到，就可以上报给AT，对流程没有影响，可以不做限制；
    而且未注册时，网络也不会有下行消息下发*/
    if(NAS_EMM_BIT_SLCT == pstTmpRcvMsg->bitOpFullName)
    {
        pstEmmInfo->bitOpFullName           = NAS_EMM_BIT_SLCT;

        NAS_LMM_MEM_CPY_S(                 pstEmmInfo->aucOperatorNameLong,
                                           MMC_LMM_MAX_OPER_LONG_NAME_LEN,
                                           pstTmpRcvMsg->aucOperatorNameLong,
                                           MMC_LMM_MAX_OPER_LONG_NAME_LEN);

        ucCount++;
    }

    if(NAS_EMM_BIT_SLCT == pstTmpRcvMsg->bitOpShortName)
    {
        pstEmmInfo->bitOpShortName          = NAS_EMM_BIT_SLCT;

        NAS_LMM_MEM_CPY_S(                 pstEmmInfo->aucOperatorNameShort,
                                           MMC_LMM_MAX_OPER_SHORT_NAME_LEN,
                                           pstTmpRcvMsg->aucOperatorNameShort,
                                           MMC_LMM_MAX_OPER_SHORT_NAME_LEN);

        ucCount++;
    }

    if(NAS_EMM_BIT_SLCT == pstTmpRcvMsg->bitOpLocTimeZone)
    {
        pstEmmInfo->bitOpLocTimeZone        = NAS_EMM_BIT_SLCT;

        NAS_LMM_MEM_CPY_S(                 &(pstEmmInfo->stLocTimeZone),
                                           sizeof(NAS_EMM_CN_TIMEZONE_STRU),
                                           &(pstTmpRcvMsg->stLocTimeZone),
                                           sizeof(NAS_EMM_CN_TIMEZONE_STRU));

        ucCount++;
    }

    if(NAS_EMM_BIT_SLCT == pstTmpRcvMsg->bitOpUniTimeLocTimeZone)
    {
        pstEmmInfo->bitOpUniTimeLocTimeZone = NAS_EMM_BIT_SLCT;

        NAS_LMM_MEM_CPY_S(                 &(pstEmmInfo->stTimeZoneAndTime),
                                           sizeof(NAS_EMM_CN_TIMEZONE_UNITIME_STRU),
                                           &(pstTmpRcvMsg->stTimeZoneAndTime),
                                           sizeof(NAS_EMM_CN_TIMEZONE_UNITIME_STRU));

    ucCount++;
    }

    if(NAS_EMM_BIT_SLCT == pstTmpRcvMsg->bitOpDaylightTime)
    {
        pstEmmInfo->bitOpDaylightTime       = NAS_EMM_BIT_SLCT;

        NAS_LMM_MEM_CPY_S(                 &(pstEmmInfo->enDaylightSavingTime),
                                           sizeof(NAS_LMM_DAYLIGHT_SAVE_TIME_ENUM_UINT8),
                                           &(pstTmpRcvMsg->enDaylightSavingTime),
                                           sizeof(NAS_LMM_DAYLIGHT_SAVE_TIME_ENUM_UINT8));

        ucCount++;
    }
    if(0 != ucCount)
    {
        NAS_EMM_SendMmcEmmInfoInd(pstEmmInfo);
    }
    return NAS_LMM_MSG_HANDLED;
}
/*lint +e826 */

VOS_UINT32  NAS_EMM_PreProcMsgEmmStatus( NAS_EMM_CN_MSG_STRU_UNION  * pCnMsg )
{
    NAS_EMM_CN_EMM_STATU_STRU           *pstTmpRcvMsg       = NAS_EMM_NULL_PTR;

    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_PreProcMsgEmmStatus enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgEmmStatus_ENUM,LNAS_ENTRY);

    /*结构化消息，取出消息体*/
    pstTmpRcvMsg                 = (NAS_EMM_CN_EMM_STATU_STRU *)pCnMsg;

    NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_PreProcMsgEmmStatus: EMM ERROR CAUSE ",pstTmpRcvMsg->ucEmmCause);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgEmmStatus_ENUM,LNAS_CAUSE_NUMBER,pstTmpRcvMsg->ucEmmCause);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgDlNasTransport
 Description     : 预处理解码后的下行NAS透传消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunbing 49683      2011-11-22  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgDlNasTransport( NAS_EMM_CN_MSG_STRU_UNION  * pCnMsg )
{
    NAS_EMM_CN_DOWNLINK_NAS_TRANSPORT_STRU *pTmpRcvMsg          = NAS_EMM_NULL_PTR;

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_PreProcMsgDlNasTransport is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgDlNasTransport_ENUM,LNAS_ENTRY);

    pTmpRcvMsg = (NAS_EMM_CN_DOWNLINK_NAS_TRANSPORT_STRU*)pCnMsg;

    NAS_LMM_SndLmmSmsDataInd(pTmpRcvMsg->aucDownlinkNasTransportMsg,
                             pTmpRcvMsg->ucDownlinkNasTransportLen);

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_ProcMsgCsSerNotification
 Description     : 直接处理下行CS SERVICE NOTIFCATION消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151    2015-07-09   Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_ProcMsgCsSerNotification(
    NAS_EMM_CN_CS_SER_NOTIFICAIOTN_STRU          *pstCsSerNotification
)
{
    /* 进入该分支的肯定是MT类型的CSFB */
    if (NAS_EMM_FAIL == NAS_EMM_SER_VerifyMtCsfb())
    {
        /* 设置UE拒绝CSFB */
        NAS_EMM_SER_SaveEmmSerCsfbRsp(NAS_EMM_CSFB_RSP_REJECTED_BY_UE);
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ);

        /* 发送EXTENDED SERVICE REQ消息，通知网侧CSFB不能发起 */
        NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();
    }
    else
    {
        /* 给MM模块发送MM_MM_CSFB_SERVICE_PAGING_IND消息 */
        NAS_EMM_MmSendCsfbSerPaingInd(NAS_EMM_MT_CSFB_TYPE_CS_SER_NOTIFICATION,
                                        pstCsSerNotification,
                                        LRRC_PAGE_UE_ID_BUTT);
    }

    return;
}



/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgCsSerNotification
 Description     : 预处理解码后的下行CS SERVICE NOTIFCATION消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010      2012-02-23  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgCsSerNotification
(
    NAS_EMM_CN_MSG_STRU_UNION           *pCnMsg
)
{
    VOS_UINT32                           ulCurEmmStat = NAS_EMM_NULL;
    NAS_EMM_CN_CS_SER_NOTIFICAIOTN_STRU *pstCsSerNotification = VOS_NULL_PTR;

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_PreProcMsgCsSerNotification is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgCsSerNotification_ENUM,LNAS_ENTRY);

    pstCsSerNotification = (NAS_EMM_CN_CS_SER_NOTIFICAIOTN_STRU *)pCnMsg;

    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT, NAS_EMM_CUR_SUB_STAT);

    /* 如果是释放过程中，直接处理掉(降圈复杂度) */
    if ((NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
      ||(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440)))
    {
        NAS_EMM_ProcMsgCsSerNotification(pstCsSerNotification);
        return NAS_LMM_MSG_HANDLED;
    }

    switch(ulCurEmmStat)
    {
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,       EMM_SS_REG_NORMAL_SERVICE)         :
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_AUTH_INIT, EMM_SS_AUTH_WAIT_CN_AUTH)          :
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_TAU_INIT,  EMM_SS_TAU_WAIT_CN_TAU_CNF)        :
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,       EMM_SS_REG_ATTEMPTING_TO_UPDATE)   :
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,       EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM):

                NAS_EMM_ProcMsgCsSerNotification(pstCsSerNotification);
                break;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT,  EMM_SS_SER_WAIT_CN_SER_CNF):

                /* 处于主叫过程中，收到被叫，则直接丢弃，被叫过程中收到
                CS SERVICE NOTIFICATION消息可能是重发，需要重新发起ESR */
                if ((NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ != NAS_EMM_SER_GetEmmSERStartCause())
                    && (NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ != NAS_EMM_SER_GetEmmSERStartCause()))
                {
                    NAS_EMM_ProcMsgCsSerNotification(pstCsSerNotification);
                }
                break;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,        EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG_INIT, EMM_SS_DETACH_WAIT_CN_DETACH_CNF):

                /* 设置UE拒绝CSFB */
                NAS_EMM_SER_SaveEmmSerCsfbRsp(NAS_EMM_CSFB_RSP_REJECTED_BY_UE);
                NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ);

                /* 发送EXTENDED SERVICE REQ消息，通知网侧CSFB不能发起 */
                NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();
                break;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT,  EMM_SS_ATTACH_WAIT_RRC_DATA_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT,  EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF):

                /* 给MM模块发送MM_MM_CSFB_SERVICE_PAGING_IND消息 */
                NAS_EMM_MmSendCsfbSerPaingInd(NAS_EMM_MT_CSFB_TYPE_CS_SER_NOTIFICATION,
                                              pstCsSerNotification,
                                              LRRC_PAGE_UE_ID_BUTT);
                break;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,       EMM_SS_REG_LIMITED_SERVICE)     :

                /* 如果有IMS电话，通知网侧不能发起CSFB，否则向MM发PAGING IND */
                #if (FEATURE_ON == FEATURE_IMS)
                if (VOS_TRUE == IMSA_IsCallConnExist())
                {
                    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_PreProcMsgCsSerNotification:IMS call is going!");
                    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgCsSerNotification_ENUM, LNAS_FUNCTION_LABEL1);

                    /* 设置UE拒绝CSFB */
                    NAS_EMM_SER_SaveEmmSerCsfbRsp(NAS_EMM_CSFB_RSP_REJECTED_BY_UE);
                    NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ);

                    /* 发送EXTENDED SERVICE REQ消息，通知网侧CSFB不能发起 */
                    NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();
                }
                else
                #endif
                {
                    NAS_EMM_ProcMsgCsSerNotification(pstCsSerNotification);
                }
                break;

        default :
                #if (FEATURE_PTM == FEATURE_ON)
                NAS_EMM_PagingErrRecord(EMM_OM_ERRLOG_PAGING_CS,EMM_OM_LMM_PAGING_FAIL_CAUSE_ABNORMAL_STATUS);
                #endif
                NAS_EMM_PUBU_LOG_NORM("NAS_EMM_PreProcMsgCsSerNotification:Illegal state!");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgCsSerNotification_ENUM, LNAS_ERROR);
                break;
    }

    return NAS_LMM_MSG_HANDLED;
}

/*lint -e669*/

VOS_VOID  NAS_EMM_SendMsgEmmStatus( VOS_UINT8 ucRes )
{
    NAS_EMM_MRRC_DATA_REQ_STRU         *pIntraMsg;
    VOS_UINT32                          ulDataReqMsgLenNoHeader;
    NAS_MSG_STRU                       *pstNasMsg;
    VOS_UINT32                          ulIndex             =0;

    NAS_EMM_ATTACH_LOG_INFO("Enter NAS_EMM_SendMsgEmmStatus,Status MSG LEN");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendMsgEmmStatus_ENUM,LNAS_ENTRY);

    /*申请消息内存*/
    pIntraMsg = (VOS_VOID *) NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);

    /*判断申请结果，若失败退出*/
    if (NAS_EMM_NULL_PTR == pIntraMsg)
    {
        return;
    }

    NAS_LMM_MEM_SET_S(pIntraMsg, NAS_EMM_INTRA_MSG_MAX_SIZE, 0, NAS_EMM_INTRA_MSG_MAX_SIZE);

    /*构造EmmStatus消息*/
    NAS_EMM_CompCnEmmStatus(            &(pIntraMsg->stNasMsg),&ulIndex,ucRes);

    ulDataReqMsgLenNoHeader             = NAS_EMM_CountMrrcDataReqLen(ulIndex);

    if ( NAS_EMM_INTRA_MSG_MAX_SIZE < ulDataReqMsgLenNoHeader )
    {
        /* 打印错误信息 */
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_SendMsgEmmStatus, Size error");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendMsgEmmStatus_ENUM,LNAS_ERROR);
        NAS_LMM_MEM_FREE(pIntraMsg);
        return ;
    }

    /*填充消息头*/
    NAS_EMM_INTRA_MSG_HEADER(pIntraMsg, ulDataReqMsgLenNoHeader);

    /*填充消息ID*/
    pIntraMsg->ulMsgId                  = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;

    /*填充消息内容*/
    pIntraMsg->enEstCaue                = LRRC_LNAS_EST_CAUSE_MO_SIGNALLING;
    pIntraMsg->enCallType               = LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING;
    pIntraMsg->enEmmMsgType             = NAS_EMM_NAS_STATUS;

    pIntraMsg->enDataCnf                = LRRC_LMM_DATA_CNF_NOT_NEED;

    /*填充消息长度*/
    pIntraMsg->stNasMsg.ulNasMsgSize    = ulIndex;

    /*向OM发送空口消息ATTACH COMPLETE*/
    pstNasMsg = (NAS_MSG_STRU *)(&(pIntraMsg->stNasMsg));
    NAS_LMM_SendOmtAirMsg(NAS_EMM_OMT_AIR_MSG_UP, NAS_EMM_STATUS, pstNasMsg);

    /*向MRRC发送消息*/
    NAS_EMM_SndUplinkNasMsg(             pIntraMsg);

    NAS_LMM_MEM_FREE(pIntraMsg);
    return;
}
/*lint +e669*/



VOS_VOID   NAS_EMM_CompCnEmmStatus( LRRC_LNAS_MSG_STRU    *pEmmStatus,
                                                  VOS_UINT32          *pulIndex,
                                                  VOS_UINT8            ucEmmCause)
{
    VOS_UINT32                          ulIndex             = *pulIndex;

    /*清空填充CN消息的空间*/
    /* NAS_LMM_MEM_SET(pEmmStatus->aucNasMsg, 0, pEmmStatus->ulNasMsgSize); */

    /* 填充 Protocol Discriminator + Security header type */
    pEmmStatus->aucNasMsg[ulIndex++]       = EMM_CN_MSG_PD_EMM;

    /* 填充  message identity */
    pEmmStatus->aucNasMsg[ulIndex++]       = NAS_EMM_CN_MT_EMM_STATUS;

    /*填充Status Cause */
    pEmmStatus->aucNasMsg[ulIndex++]       = ucEmmCause;

    *pulIndex                              = ulIndex;

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_JudgeFirstBufMsgCanBeProc
 Description     : 判断当前缓存的第一个消息能否被当前状态处理，若能处理，
                   则缓存消息出队，并准备处理下一条消息，若不能处理，则消息继续
                   缓存，此队列中缓存的消息都不处理
                   该函数调用各需要缓存消息的模块提供判断函数

                    TAU SERVICE: 以下消息需要缓存,在进入稳态后处理相应消息:
                        Nas_Emm_MsTauInitMsgRabmReestReq
                        Nas_Emm_MsTauInitMsgRrcPagingInd
                        Nas_Emm_MsTauInitMsgEsmdataReq
                        Nas_Emm_MsSerInitMsgRrcPagingInd
                        Nas_Emm_MsRrcESTInitSsWaitCNESTCnfMsgEsmDataReq

                    ATTACH DETACH:
                        在DEREG的某些状态下需要缓存ATTACH REQUEST，只有进入主
                        状态DEREG，子状态NORMAL_SERVICE下处理、
                        在DEREG的PLMN_SEARCH状态下收到T3402定时器超时消息，缓存
                        改消息，进入DEREG的NORMAL_SERVICED下处理

 Input           : ulEt : 下一条将要处理的消息的事件类型
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2008-10-11  Draft Enact

*****************************************************************************/

/*****************************************************************************
 Function Name   : NAS_LMM_PreProcMmcDisableReq
 Description     : 收到MMC Disable LTE的命令的处理

 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan      2011-11-7  Draft Enact
    2.sunjitan 00193151   2012-05-24 增加清除Resume触发和类型记录信息
    3.houzhiyuan 00285180   2015-01-05 LTE #14拒绝优化:DTS2015010401946

*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcMmcDisableReq( MsgBlock  *pMsg )
{
    /* 注册/服务状态上报上移MMC，删除注册/服务状态相关代码 */
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcMmcDisableReq Enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcDisableReq_ENUM,LNAS_ENTRY);

    /* 检查如果不是IDLE态，则直接丢弃*/
    if (NAS_EMM_NO == NAS_LMM_IsRrcConnectStatusIdle())
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_PreProcMmcDisableReq:NOT IDLE.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_PreProcMmcDisableReq_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_HANDLED;
    }
    /* 注册/服务状态上报上移MMC，删除注册/服务状态相关代码 */
    /* 记录LTE接入技术为DISABLE态*/
    NAS_EMM_SetLteEnableSta(            NAS_LMM_LTE_DISABLED);

    /* 清空T3412Exp标志*/
    NAS_LMM_SetEmmInfoT3412ExpCtrl(    NAS_EMM_T3412_EXP_NO);
    /*NAS_LMM_SetEmmInfoUpdateMmFlag(NAS_EMM_UPDATE_MM_FLAG_INVALID);*/

    /*清空DrxNetCapability标志*/
    NAS_LMM_SetEmmInfoDrxNetCapChange(NAS_EMM_NO);

    /*清空RRC删除原因标识*/
    NAS_LMM_SetEmmInfoTriggerTauRrcRel(NAS_EMM_TRIGGER_TAU_RRC_REL_NO);

    /* 清除GU发起过LAU或者联合RAU标识*/
    NAS_LMM_SetEmmInfoLauOrComRauFlag(NAS_EMM_LAU_OR_COMBINED_RAU_NOT_HAPPENED);
    NAS_LMM_SetEmmInfoSrvccFlag(NAS_EMM_SRVCC_NOT_HAPPENED);
    /*清空 EPS 承载上下文变更标志*/
    NAS_EMM_SetEpsContextStatusChange(NAS_EMM_EPS_BEARER_STATUS_NOCHANGE);
    NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_NO);

    /* 清除VOICE DOMAIN发生变化的标识 */
    NAS_EMM_SetVoiceDomainChange(NAS_EMM_NO);
    NAS_LMM_SetEmmInfoLaiChangeFlag(VOS_FALSE);
    NAS_LMM_SetEmmInfoCsEmcConneExitFlag(VOS_FALSE);
    /* 清除异系统变换触发和类型记录信息 */
    NAS_EMM_ClearResumeInfo();

    NAS_LMM_SetEmmInfoPsState(GMM_LMM_GPRS_NOT_SUSPENSION);

    /* 注册/服务状态上报上移MMC，删除注册/服务状态相关代码 */

    NAS_EMM_ClrAllUlDataReqBufferMsg();


    /*参考协议24301，5.5.3.3.4.2，  5.5.3.3.4.3，
      5.5.1.3.4.2，当前设置位语音中心&IMS不可用， 如果
      TAU 5次都是eps only成功，此时会disable LTE，此时
      需要停止定时器3402，否则回到L的时候不会立即发起TAU
    */
    /*NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3402);*/
    /* 如果之前TAU或ATTACH结果为EPS ONLY且原因值为16/17/22，并且UE操作模式为CSPS1，
    而启动的3402定时器，则需要将该定时器停掉 */
    if (VOS_TRUE == NAS_LMM_IsNeedStop3402Timer())
    {
        NAS_LMM_Stop3402Timer();
    }

    /* 美国AT&T定制需求: disable LTE清除CService计数 */
    NAS_EMM_GetEmmInfoDamParaCserviceCnt() = 0;

    /* 通知LRRC当前LTE被disable */
    NAS_LMM_SendRrcDisableLteNotify();
    /* 大数据: 清除异系统TAU标志，该标志在异系统TAU时置上 */
    NAS_EMM_SetOmInterTauFlag(NAS_EMM_NO);

    /*清除TAU_REQ发送失败原因是LRRC释放标识*/
    NAS_LMM_SetTauReqSndFailFlag(PS_FALSE);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PreProcMmcEnableReq
 Description     : 收到MMC Enable LTE的命令的处理

 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan      2011-11-9  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcMmcEnableReq( MsgBlock  *pMsg )
{
    (void)pMsg;
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcMmcEnableReq Enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcEnableReq_ENUM,LNAS_ENTRY);

    /* 记录LTE接入技术为ENABLE态*/
    NAS_EMM_SetLteEnableSta(            NAS_LMM_LTE_ENABLED);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_IsBearIsrActBefore
 Description     : 判断该承载是否为ISR激活前建立
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2012-2-28  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_IsBearIsrActBefore
(
    VOS_UINT32      ulEpsId
)
{
    VOS_UINT32                              ulRslt;
    #ifndef __PS_WIN32_RECUR__
    ulRslt = NAS_MML_IsPsBearerExistBeforeIsrAct((VOS_UINT8)ulEpsId);

    NAS_LMM_PUBM_LOG1_INFO("NAS_EMM_IsBearIsrActBefore:ulRslt = ",ulRslt);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_IsBearIsrActBefore_ENUM,LNAS_FUNCTION_LABEL1,ulRslt);

    NAS_LMM_LogIsBearIsrActBeforeInfo(ulRslt);

    #else
    ulRslt = Stub_NAS_MML_IsPsBearerExistBeforeIsrAct();
    #endif

    if (VOS_TRUE == ulRslt)
    {
        return NAS_EMM_SUCC;
    }
    else
    {
        return NAS_EMM_FAIL;
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_IsBearIsrActAfter
 Description     : 判断该承载是否为ISR激活后建立
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2012-2-28  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_IsBearIsrActAfter(VOS_VOID)
{
    VOS_UINT32                          ulRslt;
    #ifndef __PS_WIN32_RECUR__
    ulRslt = NAS_MML_IsPsBearerAfterIsrActExist();

    NAS_LMM_LogIsBearIsrActAfterInfo(ulRslt);

    NAS_LMM_PUBM_LOG1_INFO("NAS_EMM_IsBearIsrActAfter:ulRslt = ",ulRslt);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_IsBearIsrActAfter_ENUM,LNAS_FUNCTION_LABEL1,ulRslt);
    #else
    ulRslt = Stub_NAS_MML_IsPsBearerAfterIsrActExist();
    #endif
    if (VOS_TRUE == ulRslt)
    {
        return NAS_EMM_SUCC;
    }
    else
    {
        return NAS_EMM_FAIL;
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_UpdateBearISRFlag
 Description     : 判断该承载是否为ISR激活前建立
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2012-2-28  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_UpdateBearISRFlag(NAS_MML_PS_BEARER_CONTEXT_STRU  *pstBearerCtx)
{
     VOS_UINT32                          i = NAS_EMM_NULL;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_UpdateBearISRFlag Enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateBearISRFlag_ENUM,LNAS_ENTRY);

    if (NAS_EMM_NULL_PTR == pstBearerCtx)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_UpdateBearISRFlag:Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_UpdateBearISRFlag_ENUM,LNAS_NULL_PTR);
        return;
    }

    for (i = 0; i < EMM_ESM_MAX_EPS_BEARER_NUM; i++)
    {
        pstBearerCtx[i].enPsBearerIsrFlg = NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT;
    }
    return;
}


VOS_UINT32  NAS_EMM_PreProcMsgEsmBearModifyReq
(
    MsgBlock *          pMsg
)
{
    EMM_ESM_BEARER_MODIFY_REQ_STRU      *pstBearModReq = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulMatchRslt;
    NAS_MML_PS_BEARER_CONTEXT_STRU      *pstPsBearerCtx = NAS_EMM_NULL_PTR;
    MMC_LMM_TIN_TYPE_ENUM_UINT32        ulTinType;
    ulTinType = NAS_EMM_GetTinType();

    pstBearModReq = (VOS_VOID*)pMsg;

    ulMatchRslt = NAS_EMM_IsBearIsrActBefore(pstBearModReq->ulEpsId);

    NAS_LMM_PUBM_LOG3_INFO("NAS_EMM_PreProcMsgEsmBearStatusReq:NAS_EMM_GetCurLteState()=,\
          NAS_EMM_GetTinType()= , NAS_EMM_IsBearIsrActBefore()= ",
          NAS_EMM_GetCurLteState(),
          ulTinType,
          ulMatchRslt);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgEsmBearModifyReq_ENUM,LNAS_FUNCTION_LABEL1,NAS_EMM_GetCurLteState());
    /* coverity[unchecked_value] */
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_PreProcMsgEsmBearModifyReq_ENUM,LNAS_FUNCTION_LABEL2,
          ulTinType,
          ulMatchRslt);
    if(NAS_LMM_CUR_LTE_SUSPEND == NAS_EMM_GetCurLteState())
    {

        return NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcMsgEsmBearStatusReq: GET MML PS BEARER INFO:");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgEsmBearModifyReq_ENUM,LNAS_FUNCTION_LABEL3);
    pstPsBearerCtx = NAS_EMM_GetPsBearerCtx();

    if ((MMC_LMM_TIN_RAT_RELATED_TMSI == ulTinType) &&
        (NAS_EMM_SUCC == ulMatchRslt))
    {
        /*更新TIN值为GUTI*/
        NAS_EMM_SetTinType(MMC_LMM_TIN_GUTI);
        /*更新所有承载的ISR标识为ISR激活前*/
        NAS_EMM_UpdateBearISRFlag(pstPsBearerCtx);
        NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcMsgEsmBearStatusReq: UPDATE MML PS BEARER INFO:");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgEsmBearModifyReq_ENUM,LNAS_FUNCTION_LABEL4);

    }

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgT3412Exp
 Description     : T3412超时处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387    2012-2-28  Draft Enact
    2.lihong00150010    2012-12-18 Modify:Emergency

*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgT3412Exp(MsgBlock *          pMsg )
{
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32           ulForbdInfo;
    NAS_MM_TA_STRU                                stTa;
    VOS_UINT32                                    ulSendResult;

    (void)pMsg;
    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_PreProcMsgT3412Exp enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgT3412Exp_ENUM,LNAS_ENTRY);

    /*通知GU模t3412超时*/
    NAS_EMM_SendTimerStateNotify(TI_NAS_EMM_PTL_T3412, LMM_MMC_TIMER_EXP);

    /*
    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(   NAS_EMM_CUR_MAIN_STAT,
                                                NAS_EMM_CUR_SUB_STAT);
    */

    /*当前的状态是NAS_EMM_CONN_ESTING，则说明正在建链过程中收到了周期性TAU超时
      设置超时标记，该标记该如何处理呢?两种情况:
      1. 在TAU或者service流程中，建链成功，TAU, SERVCIE成功会清该标示，不再发起周期TAU
      2. 在TAU或者service流程中，如果建链失败，则转到相应的状态之后，等待RRC重新驻留，
      上报系统消息之后，发起TAU之前会判断该标识，确定是否要发起周期TAU
    */
    if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        /*设置周期TAU定时器标示*/
        NAS_LMM_SetEmmInfoT3412ExpCtrl(NAS_EMM_T3412_EXP_YES_OTHER_STATE);
        return NAS_LMM_MSG_HANDLED;
    }

    /* 如果注册状态不为紧急注册，则需要进入状态机进行处理 */
    if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
    {
        return NAS_LMM_MSG_DISCARD;
    }

    /* 如果是紧急注册，本地DETACH */
    NAS_EMM_EsmSendStatResult(  EMM_ESM_ATTACH_STATUS_DETACHED);

    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_NORMAL_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /* 本地DETACH释放资源:动态内存、赋初值 */
    NAS_LMM_DeregReleaseResource();

    /*向MMC发送本地LMM_MMC_DETACH_IND消息*/
    NAS_EMM_MmcSendDetIndLocal( MMC_LMM_L_LOCAL_DETACH_OTHERS);

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_OTHER);
    #endif

    /* 获取小区是否被禁标识和TA信息 */
    NAS_EMMC_GetCurrentForbInfo(&ulForbdInfo);
    NAS_EMMC_GetCurrentTa(&stTa);

    /* 如果小区被禁或者服务不正常，则返回 */
    if ((EMMC_EMM_NO_FORBIDDEN != ulForbdInfo)
        || (VOS_TRUE != NAS_LMM_IsCellStatusNormal((MMC_LMM_PLMN_ID_STRU*)(&(stTa.stPlmnId)), &stTa)))
    {
        return NAS_LMM_MSG_HANDLED;
    }

    /* 发起ATTACH流程 */
    ulSendResult = NAS_EMM_SendIntraAttachReq();
    if (NAS_EMM_PLMN_ERR == ulSendResult)
    {
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_PreProcMsgT3412Exp : Send IntraMsg Failure!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_PreProcMsgT3412Exp_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_LMM_MSG_HANDLED;
    }

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgT3423Exp
 Description     : T3412超时处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387    2012-2-28  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgT3423Exp(MsgBlock *          pMsg )
{
    NAS_MML_PS_BEARER_CONTEXT_STRU      *pstPsBearerCtx = NAS_EMM_NULL_PTR;
    (void)pMsg;
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcMsgT3423Exp is entry");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgT3423Exp_ENUM,LNAS_ENTRY);
    pstPsBearerCtx = NAS_EMM_GetPsBearerCtx();

    /*通知GU模t3423超时*/
    NAS_EMM_SendTimerStateNotify(TI_NAS_EMM_PTL_T3423, LMM_MMC_TIMER_EXP);



    if (MMC_LMM_TIN_RAT_RELATED_TMSI == NAS_EMM_GetTinType())
    {
        /*更新TIN值为P-TMSI*/
        NAS_EMM_SetTinType(MMC_LMM_TIN_P_TMSI);
        /*更新承载ISR标识*/
        NAS_EMM_UpdateBearISRFlag(pstPsBearerCtx);
        NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcMsgT3423Exp: UPDATE MML PS BEARER INFO:");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgT3423Exp_ENUM,LNAS_FUNCTION_LABEL2);

    }



    /*不需要进入状态机处理*/
    return NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgGmmTimerStateNotifyMsg
 Description     : 记录T3312定时器状态
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387    2013-1-29  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgGmmTimerStateNotifyMsg(MsgBlock *    pMsg )
{

    GMM_LMM_TIMER_STATE_NOTIFY_STRU     *pstTimerState;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcMsgGmmTimerStateNotifyMsg is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgGmmTimerStateNotifyMsg_ENUM,LNAS_ENTRY);

    pstTimerState = (VOS_VOID*)pMsg;

    if (NAS_EMM_BIT_SLCT == pstTimerState->bitOpT3312)
    {
        NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_PreProcMsgGmmTimerStateNotifyMsg: enT3312State =",
                            pstTimerState->enT3312State);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgGmmTimerStateNotifyMsg_ENUM,LNAS_FUNCTION_LABEL1,
                            pstTimerState->enT3312State);
        NAS_EMM_SetEmmInfoT3312State(pstTimerState->enT3312State);
    }

    return NAS_LMM_MSG_HANDLED;
}

#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 Function Name   : NAS_LMM_PreProcDsdsBeginSessionNotify
 Description     : 处理来自MMC/MM/GMM/ESM模块发送的业务通知开始消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c00134407    2014-7-9  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcDsdsBeginSessionNotify(MsgBlock *          pMsg)
{
    VOS_UINT32    ulSenderPid;
    VOS_UINT32    ulIndex = 0;
    MM_SESSION_TYPE_ENUM_UINT32  enInputSessionType;
    MM_SESSION_TYPE_ENUM_UINT32  enOutputSessionType = LRRC_LNAS_SESSION_TYPE_BUTT;
    LRRC_LMM_BEGIN_SESSION_NOTIFY_STRU *pSessionMsg;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcDsdsBeginSessionNotify Enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcDsdsBeginSessionNotify_ENUM,LNAS_ENTRY);

    pSessionMsg = (VOS_VOID*)pMsg;

    /*获取发送的pid信息*/
    ulSenderPid = pSessionMsg->ulSenderPid;

    /*获取输入消息中携带的session type*/
    enInputSessionType = pSessionMsg->enSessionType;

    /*将输入的session type映射为本地的session type*/
    for(ulIndex=0;ulIndex<g_astDsdsCvtSessionTypeTblLen;ulIndex++)
    {
        if((ulSenderPid == g_astDsdsCvtSessionTypeTbl[ulIndex].ulSenderPid)
            && (enInputSessionType == g_astDsdsCvtSessionTypeTbl[ulIndex].enInputSessionType))
        {
            enOutputSessionType = g_astDsdsCvtSessionTypeTbl[ulIndex].enOutputSessionType;
            g_astDsdsInputNotifyMsgNum[ulIndex].ulBeginMsgCnt++;
            /*DSDS接收消息勾包出来*/
            NAS_LMM_SndOmDsdsPreProcMsgInfo(NAS_LMM_DSDS_MSG_TYPE_BEGIN,ulIndex);
            break;
        }
    }

    /*组装业务通知开始消息发送给LRRC模块*/
    if(LRRC_LNAS_SESSION_TYPE_BUTT != enOutputSessionType)
    {
        NAS_LMM_SendRrcDsdsBeginNotify((LRRC_LNAS_SESSION_TYPE_ENUM_UINT8)enOutputSessionType);
    }

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PreProcDsdsEndSessionNotify
 Description     : 处理来自MMC/MM/GMM/ESM模块发送的业务通知结束消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c00134407    2014-7-9  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcDsdsEndSessionNotify(MsgBlock *          pMsg)
{
    VOS_UINT32    ulSenderPid;
    VOS_UINT32    ulIndex = 0;
    MM_SESSION_TYPE_ENUM_UINT32  enInputSessionType;
    MM_SESSION_TYPE_ENUM_UINT32  enOutputSessionType = LRRC_LNAS_SESSION_TYPE_BUTT;
    LRRC_LMM_BEGIN_SESSION_NOTIFY_STRU *pSessionMsg;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcDsdsBeginSessionNotify Enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcDsdsEndSessionNotify_ENUM,LNAS_ENTRY);

    pSessionMsg = (VOS_VOID*)pMsg;

    /*获取发送的pid信息*/
    ulSenderPid = pSessionMsg->ulSenderPid;

    /*获取输入消息中携带的session type*/
    enInputSessionType = pSessionMsg->enSessionType;

    /*将输入的session type映射为本地的session type*/
    for(ulIndex=0;ulIndex<g_astDsdsCvtSessionTypeTblLen;ulIndex++)
    {
        if((ulSenderPid == g_astDsdsCvtSessionTypeTbl[ulIndex].ulSenderPid)
            && (enInputSessionType == g_astDsdsCvtSessionTypeTbl[ulIndex].enInputSessionType))
        {
            enOutputSessionType = g_astDsdsCvtSessionTypeTbl[ulIndex].enOutputSessionType;
            g_astDsdsInputNotifyMsgNum[ulIndex].ulEndMsgCnt++;
            /*DSDS接收消息勾包出来*/
            NAS_LMM_SndOmDsdsPreProcMsgInfo(NAS_LMM_DSDS_MSG_TYPE_END,ulIndex);
            break;
        }
    }

    /*组装业务通知结束消息发送给LRRC模块*/
    if(LRRC_LNAS_SESSION_TYPE_BUTT != enOutputSessionType)
    {
        NAS_LMM_SendRrcDsdsEndNotify((LRRC_LNAS_SESSION_TYPE_ENUM_UINT8)enOutputSessionType);
    }

    return NAS_LMM_MSG_HANDLED;
}
#endif

/*lint +e961*/
/*lint +e960*/
#if(VOS_WIN32 == VOS_OS_VER)
/*单板上暂时不导出*/

VOS_VOID    NAS_EMM_PUB_SendEsmExportCtx(VOS_VOID)
{
    EMM_ESM_EXPORT_CTX_IND_STRU                *pstEsmExportCtx = NAS_EMM_NULL_PTR;

    /* 打印进入该函数*/
    vos_printf("NAS_EMM_PUB_SendEsmExportCtx is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PUB_SendEsmExportCtx_ENUM,LNAS_ENTRY);

    /* 申请DOPRA消息 */
    pstEsmExportCtx  = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_EXPORT_CTX_IND_STRU));

    if(NAS_EMM_NULL_PTR == pstEsmExportCtx)
    {
        return;
    }

    /* 填充给ESM的DOPRA头 */
    NAS_EMM_COMP_ESM_MSG_HEADER(pstEsmExportCtx, sizeof(EMM_ESM_EXPORT_CTX_IND_STRU) -
                                        NAS_EMM_LEN_VOS_MSG_HEADER);

    /* 填充消息ID */
    pstEsmExportCtx->ulMsgId             = ID_EMM_ESM_REPLAY_EXPORT_CTX_IND;

    /* 填充消息内容  */



    /* 发送DOPRA消息 */
    NAS_LMM_SEND_MSG(pstEsmExportCtx);

    return;

}


/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgReplay
 Description     : HSO的连接消息处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387    2013-4-1  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgReplay(MsgBlock *          pMsg )
{
    (void)pMsg;

    vos_printf("NAS_EMM_PreProcMsgReplay is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgReplay_ENUM,LNAS_ENTRY);

    /*导出EMM模块全局变量*/
    (void)NAS_EMM_ExportContextData();


    /*给ESM发送NAS_REPLAY_ESM_EXPORT_CTX_IND消息导出ESM/ERABM的全局变量*/
    NAS_EMM_PUB_SendEsmExportCtx();

    /*不需要进入状态机处理*/
    return NAS_LMM_MSG_HANDLED;
}
#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of 子系统+模块+文件名.c */
