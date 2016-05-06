/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaConnManagement.c
  Description     : 该C文件实现连接管理模块的初始化，内部消息的处理和发送，
                    提供外部调用的API
  History           :
     1.sunbing 49683      2013-06-19  Draft Enact


******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
/*lint -esym(766,*)*/
#include "ImsaConnManagement.h"
#include "ImsaPublic.h"
#include "ImsaEntity.h"
#include "ImsNicInterface.h"
#include "ImsaRegManagement.h"

/*#include "ImsaProcApsMsg.h"*/
#include "ImsaProcRnicMsg.h"
#include "ImsaProcAtMsg.h"


#if (VOS_WIN32 != VOS_OS_VER)
#if (VOS_VXWORKS == VOS_OS_VER)
#include <arpa/inet.h>
#else
#include "tcpip/public/tcpip_basetype.h"
#include "tcpip/public/tcpip_sock.h"
#endif
#endif


/*lint -e767*/
#define    THIS_FILE_ID      PS_FILE_ID_IMSACONNMANAGEMENT_C
#define    THIS_NAS_FILE_ID  NAS_FILE_ID_IMSACONNMANAGEMENT_C
/*lint +e767*/

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
VOS_CHAR                                g_acIpStringForSt_ipv4[IMSA_IPV4_ADDR_STRING_LEN + 1] = {0};
VOS_CHAR                                g_acIpStringForSt_ipv6[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
#if (FEATURE_ON == FEATURE_PTM)
IMSA_CN_CAUSE_TRANS_STRU                g_astImsaCnRejCauseMap[] =
{
    /*------------taf casue-----------------------------------imsa cause---------------------------*/
    {TAF_PS_CAUSE_SM_NW_OPERATOR_DETERMINED_BARRING,        IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_OPERATOR_DETERMINED_BARRING},
    {TAF_PS_CAUSE_SM_NW_MBMS_BC_INSUFFICIENT,               IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_MBMS_BC_INSUFFICIENT},
    {TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE,               IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE},
    {TAF_PS_CAUSE_SM_NW_INSUFFICIENT_RESOURCES,             IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_INSUFFICIENT_RESOURCES},
    {TAF_PS_CAUSE_SM_NW_MISSING_OR_UKNOWN_APN,              IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_MISSING_OR_UKNOWN_APN},
    {TAF_PS_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE,           IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE},
    {TAF_PS_CAUSE_SM_NW_USER_AUTHENTICATION_FAIL,           IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_USER_AUTHENTICATION_FAIL},
    {TAF_PS_CAUSE_SM_NW_ACTIVATION_REJECTED_BY_GGSN_SGW_OR_PGW, IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_ACTIVATION_REJECTED_BY_GGSN},
    {TAF_PS_CAUSE_SM_NW_ACTIVATION_REJECTED_UNSPECIFIED,    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_ACTIVATION_REJECTED_UNSPECIFIED},
    {TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_NOT_SUPPORTED,       IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SERVICE_OPTION_NOT_SUPPORTED},
    {TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED,   IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED},
    {TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER,      IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER},
    {TAF_PS_CAUSE_SM_NW_NSAPI_ALREADY_USED,                 IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_NSAPI_ALREADY_USED},
    {TAF_PS_CAUSE_SM_NW_REGULAR_DEACTIVATION,               IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_REGULAR_DEACTIVATION},
    {TAF_PS_CAUSE_SM_NW_QOS_NOT_ACCEPTED,                   IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_QOS_NOT_ACCEPTED},
    {TAF_PS_CAUSE_SM_NW_NETWORK_FAILURE,                    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_NETWORK_FAILURE},
    {TAF_PS_CAUSE_SM_NW_REACTIVATION_REQUESTED,             IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_REACTIVATION_REQUESTED},
    {TAF_PS_CAUSE_SM_NW_FEATURE_NOT_SUPPORT,                IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_FEATURE_NOT_SUPPORT},
    {TAF_PS_CAUSE_SM_NW_SEMANTIC_ERR_IN_TFT,                IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SEMANTIC_ERR_IN_TFT},
    {TAF_PS_CAUSE_SM_NW_SYNTACTIC_ERR_IN_TFT,               IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SYNTACTIC_ERR_IN_TFT},
    {TAF_PS_CAUSE_SM_NW_UKNOWN_PDP_CONTEXT,                 IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_UKNOWN_PDP_CONTEXT},
    {TAF_PS_CAUSE_SM_NW_SEMANTIC_ERR_IN_PACKET_FILTER,      IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SEMANTIC_ERR_IN_PACKET_FILTER},
    {TAF_PS_CAUSE_SM_NW_SYNCTACTIC_ERR_IN_PACKET_FILTER,    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SYNCTACTIC_ERR_IN_PACKET_FILTER},
    {TAF_PS_CAUSE_SM_NW_PDP_CONTEXT_WITHOUT_TFT_ACTIVATED,  IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_PDP_CONTEXT_WITHOUT_TFT_ACTIVATED},
    {TAF_PS_CAUSE_SM_NW_MULTICAST_GROUP_MEMBERHHSHIP_TIMEOUT,   IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_MULTICAST_GROUP_MEMBERHHSHIP_TIMEOUT},
    {TAF_PS_CAUSE_SM_NW_REQUEST_REJECTED_BCM_VIOLATION,     IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_REQUEST_REJECTED_BCM_VIOLATION},
    {TAF_PS_CAUSE_SM_NW_LAST_PDN_DISCONN_NOT_ALLOWED,       IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_LAST_PDN_DISCONN_NOT_ALLOWED},
    {TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED,         IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED},
    {TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED,         IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED},
    {TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED,   IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED},
    {TAF_PS_CAUSE_SM_NW_INFORMATION_NOT_RECEIVED,           IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_INFORMATION_NOT_RECEIVED},
    {TAF_PS_CAUSE_SM_NW_PDN_CONNECTION_DOES_NOT_EXIST,      IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_PDN_CONNECTION_DOES_NOT_EXIST},
    {TAF_PS_CAUSE_SM_NW_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED,   IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED},
    {TAF_PS_CAUSE_SM_NW_COLLISION_WITH_NW_INITIATED_REQUEST,     IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_COLLISION_WITH_NW_INITIATED_REQUEST},
    {TAF_PS_CAUSE_SM_NW_UNSUPPORTED_QCI_VALUE,              IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_UNSUPPORTED_QCI_VALUE},
    {TAF_PS_CAUSE_SM_NW_BEARER_HANDLING_NOT_SUPPORTED,      IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_BEARER_HANDLING_NOT_SUPPORTED},
    {TAF_PS_CAUSE_SM_NW_INVALID_TI,                         IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_INVALID_TI},
    {TAF_PS_CAUSE_SM_NW_SEMANTICALLY_INCORRECT_MESSAGE,     IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SEMANTICALLY_INCORRECT_MESSAGE},
    {TAF_PS_CAUSE_SM_NW_INVALID_MANDATORY_INFO,             IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_INVALID_MANDATORY_INFO},
    {TAF_PS_CAUSE_SM_NW_MSG_TYPE_NON_EXISTENT,              IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_MSG_TYPE_NON_EXISTENT},
    {TAF_PS_CAUSE_SM_NW_MSG_TYPE_NOT_COMPATIBLE,            IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_MSG_TYPE_NOT_COMPATIBLE},
    {TAF_PS_CAUSE_SM_NW_IE_NON_EXISTENT,                    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_IE_NON_EXISTENT},
    {TAF_PS_CAUSE_SM_NW_CONDITIONAL_IE_ERR,                 IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_CONDITIONAL_IE_ERR},
    {TAF_PS_CAUSE_SM_NW_MSG_NOT_COMPATIBLE,                 IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_MSG_NOT_COMPATIBLE},
    {TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED,           IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED},
    {TAF_PS_CAUSE_SM_NW_APN_RESTRICTION_INCOMPATIBLE,       IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_APN_RESTRICTION_INCOMPATIBLE}

};

static VOS_UINT32   g_astImsaCnRejCauseNum
        = sizeof(g_astImsaCnRejCauseMap)/sizeof(IMSA_CN_CAUSE_TRANS_STRU);
#endif

extern VOS_UINT32 IMSA_CONN_GetTimerLen
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_TIMER_ID_ENUM_UINT16           enTimerId
);
extern VOS_UINT32 IMSA_CONN_IsImsSdf
(
     const TAF_SDF_PARA_STRU            *pstSdfPara
);
extern VOS_UINT32 IMSA_CONN_IsPndTypeValid
(
     const TAF_SDF_PARA_STRU            *pstSdfPara
);
extern VOS_UINT32 IMSA_CONN_IsEmcSdf
(
     const TAF_SDF_PARA_STRU            *pstSdfPara
);
extern VOS_UINT32 IMSA_CONN_FindSipSignalDialPara
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    VOS_UINT32                          ulSdfNum,
    const TAF_SDF_PARA_STRU            *pstSdfPara,
    VOS_UINT32                         *pulIndex
);
extern VOS_VOID IMSA_CONN_SaveSelectedSdfPara
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    const TAF_SDF_PARA_STRU            *pstTafSdfPara
);
extern VOS_VOID IMSA_CONN_DeletePdpInfo2Reg
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    const IMSA_PDP_CNTXT_INFO_STRU     *pstPdpInfo
);
extern VOS_UINT32 IMSA_CONN_IsPdpIpvxInfoIncludeRegPara
(
    IMSA_IP_TYPE_ENUM_UINT8                 enIpType,
    VOS_CHAR                               *pcRegUeAddr,
    VOS_CHAR                               *pcRegPcscfAddr,
    const IMSA_PDP_CNTXT_INFO_STRU         *pstPdpInfo
);
extern VOS_UINT32 IMSA_CONN_IsPdpInfoIncludeRegPara
(
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    const IMSA_PDP_CNTXT_INFO_STRU         *pstPdpInfo
);
extern IMSA_FSM_PROC IMSA_FsmGetProcItem(VOS_UINT32 ulState, VOS_UINT32 ulEvt);
extern VOS_UINT32 IMSA_FsmRun(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID *pData);
extern VOS_VOID IMSA_RegResetRetryTimes
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType
);
extern VOS_VOID IMSA_RegConverterReg2Ims
(
    IMSA_REG_TYPE_ENUM_UINT8 enRegType,
    const VOS_CHAR *pucIpAddr,
    const VOS_CHAR *pacPcscfAddr,
    IMSA_IMS_INPUT_EVENT_STRU *pstImsaImsInputEvt
);
extern VOS_VOID IMSA_RegConfigIpAddress2Ims
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType,
    const VOS_CHAR                     *pcUeAddr,
    const VOS_CHAR                     *pacPcscfAddr
);
extern VOS_VOID IMSA_RegSendImsMsgDereg
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType,
    VOS_UINT32                          ulIsLocal
);
extern VOS_UINT32 IMSA_RegSendImsMsgReg
(
    IMSA_REG_TYPE_ENUM_UINT8 enRegType,
    const VOS_CHAR *pcUeAddr,
    const VOS_CHAR *pcPcscfAddr
);
extern VOS_UINT32 IMSA_RegSendIntraMsgRegInd
(
    IMSA_REG_TYPE_ENUM_UINT8 enRegType,
    IMSA_REG_RESULT_ENUM_UINT32 enResult,
    IMSA_RESULT_ACTION_ENUM_UINT32 enAction
);
extern VOS_UINT32 IMSA_RegSendIntraMsgDeregInd
(
    IMSA_REG_TYPE_ENUM_UINT8 enRegType,
    IMSA_REG_RESULT_ENUM_UINT32 enResult,
    IMSA_RESULT_ACTION_ENUM_UINT32 enAction
);
extern VOS_UINT32 IMSA_RegGetAddrByParamType
(
    IMSA_REG_TYPE_ENUM_UINT8 enRegType,
    IMSA_REG_ADDR_PARAM_ENUM_UINT32 enParamType,
    VOS_CHAR *pucUeAddr,
    VOS_CHAR *pucPcscfAddr
);
extern VOS_UINT32 IMSA_RegParseImsError
(
    const IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU  *pstOutputService,
    IMSA_IMS_OUTPUT_ERROR_STRU          *pstImsErrorInfo
);
extern VOS_UINT32 IMSA_RegCalculateRetryDelayTime
(
    VOS_UINT32                          ulMaxTime,
    VOS_UINT32                          ulBaseTime,
    VOS_UINT32                          ulConsecutiveFailures
);
extern VOS_UINT32 IMSA_RegCalculateRegFailureRetryIntervelTime
(
    VOS_UINT32                          ulRetryTimes,
    VOS_UINT32                          ulRetryAfter,
    VOS_UINT32                          ulIsReRegisteration
);
extern VOS_VOID IMSA_RegFsmProcRegisteringImsRegFailure305
(
    IMSA_REG_ENTITY_STRU               *pstEntity
);
extern VOS_VOID IMSA_RegInitRegWaitForRetryCommonProc
(
    IMSA_REG_ENTITY_STRU               *pstEntity,
    VOS_UINT32                          ulRetryAfter,
    VOS_UINT16                          usSipStatusCode
);
extern VOS_VOID IMSA_RegReRegWaitForRetryCommonProc
(
    IMSA_REG_ENTITY_STRU               *pstEntity,
    VOS_UINT32                          ulRetryAfter,
    VOS_UINT16                          usSipStatusCode
);
extern VOS_UINT32 IMSA_RegProcImsMsgState(const IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU  *pstOutputService);
extern IMSA_REG_ADDR_PAIR_STRU* IMSA_RegAddrPairCreate
(
    IMSA_IP_TYPE_ENUM_UINT8 enIpType,
    const VOS_CHAR *pacUeAddr,
    const VOS_CHAR *pacPcscfAddr
);
extern VOS_VOID IMSA_RegAddrPairDestroy(IMSA_REG_ADDR_PAIR_STRU *pstAddrPair);
extern IMSA_REG_ADDR_PAIR_STRU* IMSA_RegAddrPairListAdd
(
    IMSA_REG_ADDR_PAIR_STRU **ppstListHead,
    IMSA_REG_ADDR_PAIR_STRU *pstNode
);
extern VOS_VOID IMSA_RegAddrPairListDestroy(IMSA_REG_ADDR_PAIR_STRU *pstListHead);
extern VOS_UINT32 IMSA_RegAddrPairMgrUpdateWithNewPcscfAddr
(
    IMSA_REG_ADDR_PAIR_MGR_STRU *pstAddrPairMgr,
    IMSA_IP_TYPE_ENUM_UINT8 enIpType,
    const VOS_CHAR *pacPcscfAddr
);
extern VOS_UINT32 IMSA_RegAddrPairMgrUpdateWithNewUeAddr
(
    IMSA_REG_ADDR_PAIR_MGR_STRU *pstAddrPairMgr,
    IMSA_IP_TYPE_ENUM_UINT8 enIpType,
    const VOS_CHAR *pacUeAddr
);
extern VOS_VOID IMSA_RegGetAddrPairListHead
(
    IMSA_REG_TYPE_ENUM_UINT8            ulRegType,
    IMSA_IP_TYPE_ENUM_UINT8             enIpType,
    IMSA_REG_ADDR_PAIR_STRU          ***pppstListHead
);
extern VOS_VOID IMSA_RegAddrPairListClearAllUsedFlag(IMSA_REG_ADDR_PAIR_STRU *pstList);

extern VOS_UINT32 IMSA_CONN_PdnInfoNicConfig (IMS_NIC_PDN_INFO_CONFIG_STRU *pstConfigInfo);

extern VOS_VOID IMSA_CONN_DeleteEmcPdpInfo
(
    VOS_UINT8                               ucCid,
    VOS_UINT8                               ucRabId
);



extern VOS_VOID IMSA_CONN_PdnInfoNicDelete
(
    VOS_UINT8                           ucPdpId
);


extern VOS_VOID IMSA_CONN_ProcReEstablishConnSetupReq
(
    const IMSA_CONN_SETUP_REQ_STRU     *pstConnSetupReqMsg
);

extern VOS_UINT32 IMSA_CONN_FilterRegedPcscfInfo
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpContext
);

extern VOS_VOID IMSA_CONN_DeletePcscfInfo2Reg
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    const IMSA_PDP_CNTXT_INFO_STRU     *pstPdpInfo
);
extern VOS_VOID IMSA_CONN_ConfigPcscfInfo2Reg
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    const IMSA_PDP_CNTXT_INFO_STRU     *pstPdpInfo
);
extern VOS_VOID IMSA_CONN_DeleteOldPcscfInfoAndConfigNewPcscfInfo
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpContext,
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpContextOld
);



/*lint -e961*/
/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name  : IMSA_CONN_InitNicPdpInfo
 Description    : 初始化配置给NIC的PDP信息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.xiongxianghui 00253310      2014-04-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_ClearNicPdpInfo(VOS_VOID)
{
    IMSA_CONN_MANAGER_STRU  *pstConnManager  = IMSA_CONN_GetConnManagerAddr();

    IMSA_INFO_LOG("IMSA_CONN_ClearNicPdpInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ClearNicPdpInfo_ENUM, LNAS_ENTRY);

    IMSA_MEM_SET_S( pstConnManager->astNicPdpInfoArray,
                    sizeof(pstConnManager->astNicPdpInfoArray),
                    0,
                    sizeof(IMSA_CONN_NIC_PDP_INFO_STRU)*IMSA_CONN_MAX_NIC_PDP_NUM);
}

/*****************************************************************************
 Function Name  : IMSA_CONN_DeletePdpId2Nic
 Description    : IMSA_CONN_NIC_PDP_INFO_STRU中存储的承载号通知TTF删除
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.xiongxianghui 00253310      2014-04-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_DeletePdpId2Nic(VOS_VOID)
{
    IMSA_CONN_MANAGER_STRU  *pstConnManager  = IMSA_CONN_GetConnManagerAddr();
    VOS_UINT32              i                = 0;

    for (i = 0; i < IMSA_CONN_MAX_NIC_PDP_NUM; i++)
    {
        if (0 == pstConnManager->astNicPdpInfoArray[i].ucIsUsed)
        {
            continue;
        }

        IMSA_CONN_PdnInfoNicDelete(pstConnManager->astNicPdpInfoArray[i].ucPdpId);

        if (IMSA_FALSE == pstConnManager->astNicPdpInfoArray[i].ucIsEmc)
        {
            /* 同上海范晶确认，在删除C核虚拟网卡时，通知RNIC模块，删除虚拟网卡，
            同时给AT上报承载状态 */
            IMSA_SndMsgRnicPdnDeactInd(pstConnManager->astNicPdpInfoArray[i].ucPdpId);
            IMSA_SndMsgAtPdpDeactInd(pstConnManager->astNicPdpInfoArray[i].stPdpAddr.enIpType);
        }

    }
}


/*****************************************************************************
 Function Name  : IMSA_CONN_Init
 Description    : IMSA CONN模块的初始化
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_Init( VOS_VOID )
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn      = VOS_NULL_PTR;

    /* 初始化紧急连接 */
    pstEmcConn      = IMSA_CONN_GetEmcConnAddr();

    IMSA_MEM_SET_S(pstEmcConn, sizeof(IMSA_EMC_CONN_STRU), 0x0, sizeof(IMSA_EMC_CONN_STRU));

    pstEmcConn->enImsaConnStatus            = IMSA_CONN_STATUS_IDLE;
    pstEmcConn->enFirstReqPdnType           = IMSA_IP_TYPE_BUTT;
    pstEmcConn->enCurReqPdnType             = IMSA_IP_TYPE_BUTT;
    pstEmcConn->stProtectTimer.phTimer      = VOS_NULL_PTR;
    pstEmcConn->ucCurMaxOpid                = IMSA_CONN_EMC_CONN_MIN_OPID_VALUE;

    /* 初始化普通连接 */
    pstNormalConn   = IMSA_CONN_GetNormalConnAddr();

    IMSA_MEM_SET_S( pstNormalConn,
                    sizeof(IMSA_NORMAL_CONN_STRU),
                    0x0,
                    sizeof(IMSA_NORMAL_CONN_STRU));

    pstNormalConn->enImsaConnStatus         = IMSA_CONN_STATUS_IDLE;
    pstNormalConn->enFirstReqPdnType        = IMSA_IP_TYPE_BUTT;
    pstNormalConn->enCurReqPdnType          = IMSA_IP_TYPE_BUTT;
    pstNormalConn->stProtectTimer.phTimer   = VOS_NULL_PTR;
    pstNormalConn->ucCurMaxOpid             = IMSA_CONN_NORMAL_CONN_MIN_OPID_VALUE;

    /* 初始化存储配置给NIC的PDP信息 */
    IMSA_CONN_ClearNicPdpInfo();

    return ;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_PdnInfoNicDelete
 Description    : 删除NIC PDN信息
 Input          : ucPdpId---------------------承载号
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2014-01-24  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_PdnInfoNicDelete
(
    VOS_UINT8                           ucPdpId
)
{
    IMSA_INFO_LOG("before IMS_NIC_PdnInfoDel");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_PdnInfoNicDelete_ENUM, LNAS_ENTRY);

    (VOS_VOID)IMS_NIC_PdnInfoDel(ucPdpId, MODEM_ID_0);

    IMSA_INFO_LOG("after IMS_NIC_PdnInfoDel");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_PdnInfoNicDelete_ENUM, LNAS_LEAVE);
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ClearResource
 Description    : IMSA CONN模块的清除资源
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-23  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_ClearResource( VOS_VOID )
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn      = VOS_NULL_PTR;
    /* VOS_UINT32                          i               = 0; */

    /* 初始化紧急连接 */
    pstEmcConn      = IMSA_CONN_GetEmcConnAddr();

    /* 停止保护定时器 */
    IMSA_StopTimer(&pstEmcConn->stProtectTimer);

    pstEmcConn->enImsaConnStatus            = IMSA_CONN_STATUS_IDLE;
    pstEmcConn->enFirstReqPdnType           = IMSA_IP_TYPE_BUTT;
    pstEmcConn->enCurReqPdnType             = IMSA_IP_TYPE_BUTT;
    pstEmcConn->stProtectTimer.phTimer      = VOS_NULL_PTR;
    pstEmcConn->ucCurMaxOpid                = IMSA_CONN_EMC_CONN_MIN_OPID_VALUE;
    pstEmcConn->ucOpid                      = IMSA_NULL;

    IMSA_MEM_SET_S( &pstEmcConn->stSelSdfPara,
                    sizeof(IMSA_SEL_SDF_PARA_STRU),
                    0x0,
                    sizeof(IMSA_SEL_SDF_PARA_STRU));

    IMSA_MEM_SET_S( &pstEmcConn->stSipSignalPdp,
                    sizeof(IMSA_PDP_CNTXT_INFO_STRU),
                    0x0,
                    sizeof(IMSA_PDP_CNTXT_INFO_STRU));

    pstEmcConn->ulSipMediaPdpNum        = IMSA_NULL;
    IMSA_MEM_SET_S( pstEmcConn->astSipMediaPdpArray,
                    sizeof(pstEmcConn->astSipMediaPdpArray),
                    0x0,
                    sizeof(IMSA_PDP_CNTXT_INFO_STRU)*IMSA_CONN_MAX_EMC_SIP_MEDIA_PDP_NUM);

    /* 初始化普通连接 */
    pstNormalConn   = IMSA_CONN_GetNormalConnAddr();
    IMSA_StopTimer(&pstNormalConn->stProtectTimer);



    pstNormalConn->enImsaConnStatus         = IMSA_CONN_STATUS_IDLE;
    pstNormalConn->enFirstReqPdnType        = IMSA_IP_TYPE_BUTT;
    pstNormalConn->enCurReqPdnType          = IMSA_IP_TYPE_BUTT;
    pstNormalConn->stProtectTimer.phTimer   = VOS_NULL_PTR;
    pstNormalConn->ucCurMaxOpid             = IMSA_CONN_NORMAL_CONN_MIN_OPID_VALUE;
    pstNormalConn->ucOpid                   = IMSA_NULL;
    pstNormalConn->ulSipSignalPdpNum        = IMSA_NULL;

    IMSA_MEM_SET_S( pstNormalConn->astSipSignalPdpArray,
                    sizeof(pstNormalConn->astSipSignalPdpArray),
                    0x0,
                    sizeof(IMSA_PDP_CNTXT_INFO_STRU)*IMSA_CONN_MAX_NORMAL_SIP_SIGNAL_PDP_NUM);

    pstNormalConn->ulSipMediaPdpNum        = IMSA_NULL;
    IMSA_MEM_SET_S( pstNormalConn->astSipMediaPdpArray,
                    sizeof(pstNormalConn->astSipMediaPdpArray),
                    0x0,
                    sizeof(IMSA_PDP_CNTXT_INFO_STRU)*IMSA_CONN_MAX_NORMAL_SIP_MEDIA_PDP_NUM);

    /* 将NIC PDP INFO中存储的承载号通知TTF删除 */
    IMSA_CONN_DeletePdpId2Nic();

    /* 清除存储配置给NIC的PDP信息*/
    IMSA_CONN_ClearNicPdpInfo();

    /* 关机清连接模块资源后,需要通知CDS清除IMS承载信息, 解决问题如:IMS注册成功, 然后Modem关机并关闭VoLTE, 再次开机
       手动建立承载, 由于在关机时IMSA未通知CDS清除IMS承载信息, 从而导致再次开机建立的承载ID与关机前IMS 信令承载ID
       相同时误以为当前承载为IMS承载, 从而把数据把发给IMS, 从而导致数传不通*/
    IMSA_CONN_SndCdsSetImsBearerReq();

    return ;
}


/*****************************************************************************
 Function Name  : IMSA_CONN_AssignOpid
 Description    : IMSA CONN模块分配OPID
                  普通连接的OPID和紧急连接的OPID值位于不同区间，是为了使OPID值
                  翻转后普通连接的OPID和紧急连接的OPID值不产生干扰
 Input          : enConnType--------------连接类型
 Output         : pulOpid-----------------分配的OPID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-25  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_AssignOpid
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    VOS_UINT8                          *pucOpid
)
{
    VOS_UINT8                           ucOpid = IMSA_NULL;

    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        /*获取当前最大OPID*/
        ucOpid = IMSA_CONN_GetNormalConnCurMaxOpid();

        /*如果还未到最大值，直接加1*/
        if( ucOpid < IMSA_CONN_NORMAL_CONN_MAX_OPID_VALUE)
        {
            *pucOpid = ucOpid + 1;
        }
        else/*如果已经是最大值，从初值开始分配*/
        {
            (*pucOpid) = IMSA_CONN_NORMAL_CONN_MIN_OPID_VALUE;
        }

        IMSA_CONN_SetNormalConnCurMaxOpid(*pucOpid);

        IMSA_INFO_LOG1("IMSA_CONN_AssignOpid,normal,assin opid:", (*pucOpid));
        TLPS_PRINT2LAYER_INFO1(IMSA_CONN_AssignOpid_ENUM, IMSA_NORMAL_OPID, (*pucOpid));
    }
    else
    {
        /*获取当前最大OPID*/
        ucOpid = IMSA_CONN_GetEmcConnCurMaxOpid();

        /*如果还未到最大值，直接加1*/
        if( ucOpid < IMSA_CONN_EMC_CONN_MAX_OPID_VALUE)
        {
            *pucOpid = ucOpid + 1;
        }
        else/*如果已经是最大值，从初值开始分配*/
        {
            (*pucOpid) = IMSA_CONN_EMC_CONN_MIN_OPID_VALUE;
        }

        IMSA_CONN_SetEmcConnCurMaxOpid(*pucOpid);

        IMSA_INFO_LOG1("IMSA_CONN_AssignOpid,emc,assin opid:", (*pucOpid));
        TLPS_PRINT2LAYER_INFO1(IMSA_CONN_AssignOpid_ENUM, IMSA_EMERGENCY_OPID, (*pucOpid));
    }
}


/*****************************************************************************
 Function Name  : IMSA_CONN_ProcConnSetupReq
 Description    : 根据OPID查找其关联的连接实体类型
 Input          : pstConnSetupReqMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-25  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_GetConnTypeByOpid
(
    VOS_UINT8                           ucOpid,
    IMSA_CONN_TYPE_ENUM_UINT32         *penConnType
)
{
    if (ucOpid == IMSA_CONN_GetNormalConnOpid())
    {
        *penConnType = IMSA_CONN_TYPE_NORMAL;
        return IMSA_SUCC;
    }

    if (ucOpid == IMSA_CONN_GetEmcConnOpid())
    {
        *penConnType = IMSA_CONN_TYPE_EMC;
        return IMSA_SUCC;
    }

    return IMSA_FAIL;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_GetSipSignalPdpState
 Description    : 获取SIP信令承载状态
 Input          : pstConnSetupReqMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-25  Draft Enact
*****************************************************************************/
IMSA_PDP_STATE_ENUM_UINT8 IMSA_CONN_GetSipSignalPdpState
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_IP_TYPE_ENUM_UINT8             enIpType
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn      = VOS_NULL_PTR;
    VOS_UINT32                          i               = IMSA_NULL;

    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        pstEmcConn  = IMSA_CONN_GetEmcConnAddr();

        if ((IMSA_PDP_STATE_ACTIVE == pstEmcConn->stSipSignalPdp.enPdpState)
            && (enIpType == pstEmcConn->stSipSignalPdp.stPdpAddr.enIpType))
        {
            return IMSA_PDP_STATE_ACTIVE;
        }

        return IMSA_PDP_STATE_INACTIVE;
    }

    pstNormalConn   = IMSA_CONN_GetNormalConnAddr();
    for (i = 0; i < pstNormalConn->ulSipSignalPdpNum; i++)
    {
        if ((IMSA_PDP_STATE_ACTIVE == pstNormalConn->astSipSignalPdpArray[i].enPdpState)
            && (enIpType == pstNormalConn->astSipSignalPdpArray[i].stPdpAddr.enIpType))
        {
            return IMSA_PDP_STATE_ACTIVE;
        }
    }

    return IMSA_PDP_STATE_INACTIVE;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_IsConnStatusEqual
 Description    : 判断连接状态是否与入参相同
 Input          : enConnType-------------连接类型
                  enTimerId--------------定时器类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-28  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_IsConnStatusEqual
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_CONN_STATUS_ENUM_UINT8         enImsaConnStatus
)
{
    IMSA_CONN_STATUS_ENUM_UINT8         enImsaConnStatusTmp = IMSA_CONN_STATUS_BUTT;

    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        enImsaConnStatusTmp = IMSA_CONN_GetNormalConnStatus();
    }
    else
    {
        enImsaConnStatusTmp = IMSA_CONN_GetEmcConnStatus();
    }

    if (enImsaConnStatus == enImsaConnStatusTmp)
    {
        return IMSA_TRUE;
    }
    else
    {
        return IMSA_FALSE;
    }
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ClearConnResource
 Description    : 清除连接资源
 Input          : enConnType-------------连接类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_ClearConnResource
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn      = VOS_NULL_PTR;

    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        pstEmcConn                      = IMSA_CONN_GetEmcConnAddr();

        IMSA_StopTimer(&pstEmcConn->stProtectTimer);
        pstEmcConn->enCurReqPdnType     = IMSA_IP_TYPE_BUTT;
        pstEmcConn->enFirstReqPdnType   = IMSA_IP_TYPE_BUTT;
        pstEmcConn->enImsaConnStatus    = IMSA_CONN_STATUS_IDLE;
        pstEmcConn->ucOpid              = IMSA_CONN_ILLEGAL_OPID;

        IMSA_MEM_SET_S(                 &pstEmcConn->stSelSdfPara,
                                        sizeof(IMSA_SEL_SDF_PARA_STRU),
                                        0x0,
                                        sizeof(IMSA_SEL_SDF_PARA_STRU));

        IMSA_MEM_SET_S(                 &pstEmcConn->stSipSignalPdp,
                                        sizeof(IMSA_PDP_CNTXT_INFO_STRU),
                                        0x0,
                                        sizeof(IMSA_PDP_CNTXT_INFO_STRU));

        pstEmcConn->ulSipMediaPdpNum    = 0;
        IMSA_MEM_SET_S(                 pstEmcConn->astSipMediaPdpArray,
                                        sizeof(pstEmcConn->astSipMediaPdpArray),
                                        0x0,
                                        sizeof(IMSA_PDP_CNTXT_INFO_STRU)*IMSA_CONN_MAX_EMC_SIP_MEDIA_PDP_NUM);

    }
    else
    {
        pstNormalConn = IMSA_CONN_GetNormalConnAddr();
        IMSA_StopTimer(&pstNormalConn->stProtectTimer);
        pstNormalConn->enCurReqPdnType  = IMSA_IP_TYPE_BUTT;
        pstNormalConn->enFirstReqPdnType= IMSA_IP_TYPE_BUTT;
        pstNormalConn->enImsaConnStatus = IMSA_CONN_STATUS_IDLE;
        pstNormalConn->ucOpid           = IMSA_CONN_ILLEGAL_OPID;

        IMSA_MEM_SET_S(                 &pstNormalConn->stSelSdfPara,
                                        sizeof(IMSA_SEL_SDF_PARA_STRU),
                                        0x0,
                                        sizeof(IMSA_SEL_SDF_PARA_STRU));
        pstNormalConn->ulSipSignalPdpNum= 0;
        IMSA_MEM_SET_S(                 pstNormalConn->astSipSignalPdpArray,
                                        sizeof(pstNormalConn->astSipSignalPdpArray),
                                        0x0,
                                        sizeof(IMSA_PDP_CNTXT_INFO_STRU)*IMSA_CONN_MAX_NORMAL_SIP_SIGNAL_PDP_NUM);
        pstNormalConn->ulSipMediaPdpNum = 0;
        IMSA_MEM_SET_S(                 pstNormalConn->astSipMediaPdpArray,
                                        sizeof(pstNormalConn->astSipMediaPdpArray),
                                        0x0,
                                        sizeof(IMSA_PDP_CNTXT_INFO_STRU)*IMSA_CONN_MAX_NORMAL_SIP_MEDIA_PDP_NUM);
    }
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ClearConnResourceExeptMedia
 Description    : 清除连接资源，但不清除媒体承载信息
 Input          : enConnType-------------连接类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2014-12-03  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_ClearConnResourceExeptMedia
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn      = VOS_NULL_PTR;

    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        pstEmcConn                      = IMSA_CONN_GetEmcConnAddr();

        IMSA_StopTimer(&pstEmcConn->stProtectTimer);
        pstEmcConn->enCurReqPdnType     = IMSA_IP_TYPE_BUTT;
        pstEmcConn->enFirstReqPdnType   = IMSA_IP_TYPE_BUTT;
        pstEmcConn->enImsaConnStatus    = IMSA_CONN_STATUS_IDLE;
        pstEmcConn->ucOpid              = IMSA_CONN_ILLEGAL_OPID;

        IMSA_MEM_SET_S(                 &pstEmcConn->stSelSdfPara,
                                        sizeof(IMSA_SEL_SDF_PARA_STRU),
                                        0x0,
                                        sizeof(IMSA_SEL_SDF_PARA_STRU));

        IMSA_MEM_SET_S(                 &pstEmcConn->stSipSignalPdp,
                                        sizeof(IMSA_PDP_CNTXT_INFO_STRU),
                                        0x0,
                                        sizeof(IMSA_PDP_CNTXT_INFO_STRU));
    }
    else
    {
        pstNormalConn = IMSA_CONN_GetNormalConnAddr();
        IMSA_StopTimer(&pstNormalConn->stProtectTimer);
        pstNormalConn->enCurReqPdnType  = IMSA_IP_TYPE_BUTT;
        pstNormalConn->enFirstReqPdnType= IMSA_IP_TYPE_BUTT;
        pstNormalConn->enImsaConnStatus = IMSA_CONN_STATUS_IDLE;
        pstNormalConn->ucOpid           = IMSA_CONN_ILLEGAL_OPID;

        IMSA_MEM_SET_S(                 &pstNormalConn->stSelSdfPara,
                                        sizeof(IMSA_SEL_SDF_PARA_STRU),
                                        0x0,
                                        sizeof(IMSA_SEL_SDF_PARA_STRU));
        pstNormalConn->ulSipSignalPdpNum= 0;
        IMSA_MEM_SET_S(                 pstNormalConn->astSipSignalPdpArray,
                                        sizeof(pstNormalConn->astSipSignalPdpArray),
                                        0x0,
                                        sizeof(IMSA_PDP_CNTXT_INFO_STRU)*IMSA_CONN_MAX_NORMAL_SIP_SIGNAL_PDP_NUM);
    }
}

/*****************************************************************************
 Function Name  : IMSA_CONN_HasActiveSipSignalPdp
 Description    : 判断连接是否有激活的SIP信令承载
 Input          : enConnType-------------连接类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-28  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_HasActiveSipSignalPdp
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn      = VOS_NULL_PTR;

    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        pstEmcConn  = IMSA_CONN_GetEmcConnAddr();

        if (IMSA_PDP_STATE_ACTIVE == pstEmcConn->stSipSignalPdp.enPdpState)
        {
            return IMSA_TRUE;
        }
        else
        {
            return IMSA_FALSE;
        }
    }
    else
    {
        pstNormalConn = IMSA_CONN_GetNormalConnAddr();

        if (0 != pstNormalConn->ulSipSignalPdpNum)
        {
            return IMSA_TRUE;
        }
        else
        {
            return IMSA_FALSE;
        }
    }
}
/*****************************************************************************
 Function Name  : IMSA_CONN_HasActiveVoicePdp
 Description    : 判断连接是否有激活的语音承载
 Input          : enConnType-------------连接类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181 2014-06-20  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_HasActiveVoicePdp
(
    VOS_VOID
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    VOS_UINT32                          ulSipMediaPdpNum = IMSA_NULL;
    IMSA_ENTITY_STRU                   *pstImsaEntity = IMSA_CtxGet();
    VOS_UINT32                          ulPfNum = IMSA_NULL;
    VOS_UINT16                          usImsMinPort;
    VOS_UINT16                          usImsMaxPort;

    pstNormalConn = IMSA_CONN_GetNormalConnAddr();

    usImsMinPort = pstImsaEntity->stImsaControlManager.stImsaConfigPara.stImsPortConfig.usImsMinPort;
    usImsMaxPort = pstImsaEntity->stImsaControlManager.stImsaConfigPara.stImsPortConfig.usImsMaxPort;

    for (ulSipMediaPdpNum = 0; ulSipMediaPdpNum < pstNormalConn->ulSipMediaPdpNum; ulSipMediaPdpNum ++)
    {
        for (ulPfNum = 0; ulPfNum < pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.ulPfNum; ulPfNum++)
        {
            /* 如果存在多个下行过滤器，只需要判断一个过滤器的本地端口 */
            if ((IMSA_OP_TRUE == pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.astTftInfo[ulPfNum].bitOpSingleLocalPort) &&
                (pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.astTftInfo[ulPfNum].usSingleLcPort >= usImsMinPort)&&
                (pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.astTftInfo[ulPfNum].usSingleLcPort <= usImsMaxPort))
            {
                return IMSA_TRUE;
            }

            if ((IMSA_OP_TRUE == pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.astTftInfo[ulPfNum].bitOpLocalPortRange) &&
                (pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.astTftInfo[ulPfNum].usLcPortLowLimit >= usImsMinPort) &&
                (pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.astTftInfo[ulPfNum].usLcPortHighLimit <= usImsMaxPort))
            {
                return IMSA_TRUE;
            }

            if (IMSA_VOICE_QCI == pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stEpsQos.ucQCI)
            {
                return IMSA_TRUE;
            }
        }
    }
    return IMSA_FALSE;
}
/*****************************************************************************
 Function Name  : IMSA_CONN_HasActiveVideoPdp
 Description    : 判断连接是否有激活的视频承载
 Input          : enConnType-------------连接类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181 2014-06-20  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_HasActiveVideoPdp
(
    VOS_VOID
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    VOS_UINT32                          ulSipMediaPdpNum = IMSA_NULL;
    IMSA_ENTITY_STRU                   *pstImsaEntity = IMSA_CtxGet();
    VOS_UINT32                          ulPfNum = IMSA_NULL;
    VOS_UINT16                          usImsMinPort;
    VOS_UINT16                          usImsMaxPort;

    pstNormalConn = IMSA_CONN_GetNormalConnAddr();

    usImsMinPort = pstImsaEntity->stImsaControlManager.stImsaConfigPara.stImsPortConfig.usImsMinPort;
    usImsMaxPort = pstImsaEntity->stImsaControlManager.stImsaConfigPara.stImsPortConfig.usImsMaxPort;

    for (ulSipMediaPdpNum = 0; ulSipMediaPdpNum < pstNormalConn->ulSipMediaPdpNum; ulSipMediaPdpNum ++)
    {
        for (ulPfNum = 0; ulPfNum < pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.ulPfNum; ulPfNum++)
        {
            if ((IMSA_OP_TRUE == pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.astTftInfo[ulPfNum].bitOpSingleLocalPort) &&
                ((pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.astTftInfo[ulPfNum].usSingleLcPort < usImsMinPort)  ||
                 (pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.astTftInfo[ulPfNum].usSingleLcPort > usImsMaxPort)))
            {
                return IMSA_TRUE;
            }

            if ((IMSA_OP_TRUE == pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.astTftInfo[ulPfNum].bitOpLocalPortRange) &&
                (pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.astTftInfo[ulPfNum].usLcPortLowLimit < usImsMinPort) &&
                (pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.astTftInfo[ulPfNum].usLcPortHighLimit > usImsMaxPort))
            {
                return IMSA_TRUE;
            }

            if (IMSA_VIDEO_QCI == pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stEpsQos.ucQCI)
            {
                return IMSA_TRUE;
            }
        }
    }
    return IMSA_FALSE;
}


/*****************************************************************************
 Function Name  : IMSA_CONN_GetPdpContextByPdpId
 Description    : 根据承载号获取承载上下文
 Input          : enConnType----------连接类型
                  ucPdpId-------------承载号
 Output         : penSipPdpType-------SIP承载类型指针
                  pstPdpContext-------PDP上下文指针的指针
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-06-29  Draft Enact
      2.lihong 00150010      2013-12-06  Moidfy:emc dedicated
*****************************************************************************/
VOS_UINT32 IMSA_CONN_GetPdpContextByPdpId
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    VOS_UINT8                           ucPdpId,
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32 *penSipPdpType,
    IMSA_PDP_CNTXT_INFO_STRU          **ppstPdpContext
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn      = VOS_NULL_PTR;
    VOS_UINT32                          i               = IMSA_NULL;

    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        pstEmcConn          = IMSA_CONN_GetEmcConnAddr();

        if ((IMSA_PDP_STATE_ACTIVE == pstEmcConn->stSipSignalPdp.enPdpState)
            && ((ucPdpId == pstEmcConn->stSipSignalPdp.ucPdpId)))
        {
            *ppstPdpContext = &pstEmcConn->stSipSignalPdp;
            *penSipPdpType  = IMSA_CONN_SIP_PDP_TYPE_SIGNAL;

            return IMSA_SUCC;
        }

        for (i = 0; i < pstEmcConn->ulSipMediaPdpNum; i++)
        {
            if ((ucPdpId == pstEmcConn->astSipMediaPdpArray[i].ucPdpId)
                && (IMSA_PDP_STATE_ACTIVE == pstEmcConn->astSipMediaPdpArray[i].enPdpState))
            {
                *ppstPdpContext = &pstEmcConn->astSipMediaPdpArray[i];
                *penSipPdpType  = IMSA_CONN_SIP_PDP_TYPE_MEDIA;
                return IMSA_SUCC;
            }
        }

        return IMSA_FAIL;
    }

    pstNormalConn = IMSA_CONN_GetNormalConnAddr();

    for (i = 0; i < pstNormalConn->ulSipSignalPdpNum; i++)
    {
        if ((ucPdpId == pstNormalConn->astSipSignalPdpArray[i].ucPdpId)
            && (IMSA_PDP_STATE_ACTIVE == pstNormalConn->astSipSignalPdpArray[i].enPdpState))
        {
            *ppstPdpContext = &pstNormalConn->astSipSignalPdpArray[i];
            *penSipPdpType  = IMSA_CONN_SIP_PDP_TYPE_SIGNAL;
            return IMSA_SUCC;
        }
    }

    for (i = 0; i < pstNormalConn->ulSipMediaPdpNum; i++)
    {
        if ((ucPdpId == pstNormalConn->astSipMediaPdpArray[i].ucPdpId)
            && (IMSA_PDP_STATE_ACTIVE == pstNormalConn->astSipMediaPdpArray[i].enPdpState))
        {
            *ppstPdpContext = &pstNormalConn->astSipMediaPdpArray[i];
            *penSipPdpType  = IMSA_CONN_SIP_PDP_TYPE_MEDIA;
            return IMSA_SUCC;
        }
    }

    return IMSA_FAIL;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_GetPdpContextByCid
 Description    : 根据CID获取承载上下文
 Input          : enConnType----------连接类型
                  ucCid---------------CID
 Output         : penSipPdpType-------SIP承载类型指针
                  pstPdpContext-------PDP上下文指针的指针
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-02  Draft Enact
      2.lihong 00150010      2013-12-06  Modify:Emc dedicated
*****************************************************************************/
VOS_UINT32 IMSA_CONN_GetPdpContextByCid
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    VOS_UINT8                           ucCid,
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32 *penSipPdpType,
    IMSA_PDP_CNTXT_INFO_STRU          **ppstPdpContext
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn      = VOS_NULL_PTR;
    VOS_UINT32                          i               = IMSA_NULL;

    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        pstEmcConn          = IMSA_CONN_GetEmcConnAddr();

        if ((IMSA_PDP_STATE_ACTIVE == pstEmcConn->stSipSignalPdp.enPdpState)
            && ((ucCid == pstEmcConn->stSipSignalPdp.ucCid)))
        {
            *ppstPdpContext = &pstEmcConn->stSipSignalPdp;
            *penSipPdpType  = IMSA_CONN_SIP_PDP_TYPE_SIGNAL;

            return IMSA_SUCC;
        }

        for (i = 0; i < pstEmcConn->ulSipMediaPdpNum; i++)
        {
            if ((ucCid == pstEmcConn->astSipMediaPdpArray[i].ucCid)
                && (IMSA_PDP_STATE_ACTIVE == pstEmcConn->astSipMediaPdpArray[i].enPdpState))
            {
                *ppstPdpContext = &pstEmcConn->astSipMediaPdpArray[i];
                *penSipPdpType  = IMSA_CONN_SIP_PDP_TYPE_MEDIA;
                return IMSA_SUCC;
            }
        }

        return IMSA_FAIL;
    }

    pstNormalConn = IMSA_CONN_GetNormalConnAddr();

    for (i = 0; i < pstNormalConn->ulSipSignalPdpNum; i++)
    {
        if ((ucCid == pstNormalConn->astSipSignalPdpArray[i].ucCid)
            && (IMSA_PDP_STATE_ACTIVE == pstNormalConn->astSipSignalPdpArray[i].enPdpState))
        {
            *ppstPdpContext = &pstNormalConn->astSipSignalPdpArray[i];
            *penSipPdpType  = IMSA_CONN_SIP_PDP_TYPE_SIGNAL;
            return IMSA_SUCC;
        }
    }

    for (i = 0; i < pstNormalConn->ulSipMediaPdpNum; i++)
    {
        if ((ucCid == pstNormalConn->astSipMediaPdpArray[i].ucCid)
            && (IMSA_PDP_STATE_ACTIVE == pstNormalConn->astSipMediaPdpArray[i].enPdpState))
        {
            *ppstPdpContext = &pstNormalConn->astSipMediaPdpArray[i];
            *penSipPdpType  = IMSA_CONN_SIP_PDP_TYPE_MEDIA;
            return IMSA_SUCC;
        }
    }

    return IMSA_FAIL;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_GetPdpContextByCidOrPdpId
 Description    : 根据CID或承载ID获取承载上下文
 Input          : pstPdpDeactivateInd----------去激活事件
 Output         : penSipPdpType----------------SIP承载类型指针
                  pstPdpContext----------------PDP上下文指针的指针
                  penConnType------------------连接类型
 Return Value   : VOS_UINT32

 History        :
      1.xiongxianghui 00150010      2015-01-06  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_GetPdpContextByCidOrPdpId
(
    VOS_UINT8                                   ucCid,
    VOS_UINT8                                   ucPdpId,
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32          *penSipPdpType,
    IMSA_PDP_CNTXT_INFO_STRU                    **ppstPdpContext,
    IMSA_CONN_TYPE_ENUM_UINT32                  *penConnType
)
{

    IMSA_INFO_LOG("IMSA_CONN_GetPdpContextByCidOrPdpId is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_GetPdpContextByCidOrPdpId_ENUM, LNAS_ENTRY);
    TLPS_PRINT2LAYER_INFO1(IMSA_CONN_ProcTafPsEvtPdpDeactivateInd_ENUM, IMSA_CID, ucCid);
    TLPS_PRINT2LAYER_INFO1(IMSA_CONN_ProcTafPsEvtPdpDeactivateInd_ENUM, IMSA_PDPID, ucPdpId);

    /* 通过CID获取普通承载上下文 */
    if (IMSA_SUCC == IMSA_CONN_GetPdpContextByCid(IMSA_CONN_TYPE_NORMAL,
                                                  ucCid,
                                                  penSipPdpType,
                                                  ppstPdpContext))
    {
        IMSA_INFO_LOG("IMSA_CONN_GetPdpContextByCidOrPdpId:get normal pdp context by cid!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_GetPdpContextByCidOrPdpId_ENUM, 1);
        *penConnType = IMSA_CONN_TYPE_NORMAL;
        return IMSA_SUCC;
    }

    /* 通过承载ID获取普通承载上下文 */
    if (IMSA_SUCC == IMSA_CONN_GetPdpContextByPdpId(IMSA_CONN_TYPE_NORMAL,
                                                    ucPdpId,
                                                    penSipPdpType,
                                                    ppstPdpContext))
    {
        IMSA_INFO_LOG("IMSA_CONN_GetPdpContextByCidOrPdpId:get normal pdp context by pdpid!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_GetPdpContextByCidOrPdpId_ENUM, 2);
        *penConnType = IMSA_CONN_TYPE_NORMAL;
        return IMSA_SUCC;
    }

    /* 通过CID获取紧急承载上下文 */
    if (IMSA_SUCC == IMSA_CONN_GetPdpContextByCid(IMSA_CONN_TYPE_EMC,
                                                  ucCid,
                                                  penSipPdpType,
                                                  ppstPdpContext))
    {
        IMSA_INFO_LOG("IMSA_CONN_GetPdpContextByCidOrPdpId:get emc pdp context by cid!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_GetPdpContextByCidOrPdpId_ENUM, 3);
        *penConnType = IMSA_CONN_TYPE_EMC;
        return IMSA_SUCC;
    }

    /* 通过承载ID获取紧急承载上下文 */
    if (IMSA_SUCC == IMSA_CONN_GetPdpContextByPdpId(IMSA_CONN_TYPE_EMC,
                                                    ucPdpId,
                                                    penSipPdpType,
                                                    ppstPdpContext))
    {
        IMSA_INFO_LOG("IMSA_CONN_GetPdpContextByCidOrPdpId:get emc pdp context by pdpid!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_GetPdpContextByCidOrPdpId_ENUM, 4);
        *penConnType = IMSA_CONN_TYPE_EMC;
        return IMSA_SUCC;
    }

    return IMSA_FAIL;
}


/*****************************************************************************
 Function Name  : IMSA_CONN_GetTimerLen
 Description    : 获取定时器时长
 Input          : enConnType-------------连接类型
                  enTimerId--------------定时器类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-28  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_GetTimerLen
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_TIMER_ID_ENUM_UINT16           enTimerId
)
{
    if (TI_IMSA_SIP_SIGAL_PDP_ORIG == enTimerId)
    {
        if (IMSA_CONN_TYPE_NORMAL == enConnType)
        {
            return TI_IMSA_NRM_SIP_SIGAL_PDP_ORIG_TIMER_LEN;
        }
        else
        {
            return TI_IMSA_EMC_SIP_SIGAL_PDP_ORIG_TIMER_LEN;
        }
    }

    if (TI_IMSA_SIP_SIGAL_PDP_END == enTimerId)
    {
        return TI_IMSA_SIP_SIGAL_PDP_END_TIMER_LEN;
    }

    if (TI_IMSA_WAIT_IPV6_INFO == enTimerId)
    {
        return TI_IMSA_WAIT_IPV6_INFO_TIMER_LEN;
    }

    return 0;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_StartTimer
 Description    : IMSA CONN模块启动定时器
 Input          : enConnType-------------连接类型
                  enTimerId--------------定时器类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_StartTimer
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_TIMER_ID_ENUM_UINT16           enTimerId
)
{
    VOS_UINT32                          ulTimerLen      = IMSA_NULL;
    IMSA_TIMER_STRU                    *pstProtectImer  = VOS_NULL_PTR;

    /* 获取定时器时长 */
    ulTimerLen                  = IMSA_CONN_GetTimerLen(enConnType, enTimerId);

    IMSA_INFO_LOG2("IMSA_CONN_StartTimer:enConnType:Timer Len:", enConnType, ulTimerLen);
    TLPS_PRINT2LAYER_INFO2(IMSA_CONN_StartTimer_ENUM, 1, enConnType, ulTimerLen);

    if (IMSA_CONN_TYPE_NORMAL   == enConnType)
    {
        pstProtectImer          = IMSA_CONN_GetNormalConnProtectTimerAddr();

    }
    else
    {
        pstProtectImer          = IMSA_CONN_GetEmcConnProtectTimerAddr();
    }

    /* 赋值定时器参数 */
    pstProtectImer->ulTimerLen  = ulTimerLen;
    pstProtectImer->usName      = enTimerId;
    pstProtectImer->usPara      = (VOS_UINT16)enConnType;
    pstProtectImer->ucMode      = VOS_RELTIMER_NOLOOP;

    IMSA_StartTimer(pstProtectImer);
}

/*****************************************************************************
 Function Name  : IMSA_CONN_StopTimer
 Description    : IMSA CONN模块关闭定时器
 Input          : enConnType-------------连接类型
                  enTimerId--------------定时器类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_StopTimer
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_TIMER_ID_ENUM_UINT16           enTimerId
)
{
    IMSA_TIMER_STRU                    *pstProtectImer  = VOS_NULL_PTR;

    if (IMSA_CONN_TYPE_NORMAL   == enConnType)
    {
        pstProtectImer          = IMSA_CONN_GetNormalConnProtectTimerAddr();

    }
    else
    {
        pstProtectImer          = IMSA_CONN_GetEmcConnProtectTimerAddr();
    }

    if (pstProtectImer->usName == enTimerId)
    {
        IMSA_StopTimer(pstProtectImer);
    }
}

/*****************************************************************************
 Function Name  : IMSA_CONN_SetConnStatus
 Description    : 设置连接状态
 Input          : enConnType-------------连接类型
                  enConnStatus-----------连接状态
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_SetConnStatus
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_CONN_STATUS_ENUM_UINT8         enConnStatus
)
{
    /* 获取连接原状态 */

    /* 打印连接类型 */

    /* 打印连接状态变更新信息 */

    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        IMSA_CONN_GetNormalConnStatus() = enConnStatus;
    }
    else
    {
        IMSA_CONN_GetEmcConnStatus()    = enConnStatus;
    }
}

/*****************************************************************************
 Function Name  : IMSA_CONN_SaveFirstReqPdnType
 Description    : 存储最初请求的PDN类型
 Input          : enConnType-------------连接类型
                  enIpType---------------请求的PDN类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_SaveFirstReqPdnType
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_IP_TYPE_ENUM_UINT8             enIpType
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn       = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn          = VOS_NULL_PTR;

    /* 获取PRIM PDP参数的格式 */
    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        pstNormalConn                   = IMSA_CONN_GetNormalConnAddr();
        pstNormalConn->enFirstReqPdnType= enIpType;
    }
    else
    {
        pstEmcConn                      = IMSA_CONN_GetEmcConnAddr();
        pstEmcConn->enFirstReqPdnType   = enIpType;
    }
}


/*****************************************************************************
 Function Name  : IMSA_CONN_SaveCurReqPdnType
 Description    : 存储当前请求的PDN类型
 Input          : enConnType-------------连接类型
                  enIpType---------------请求的PDN类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_SaveCurReqPdnType
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_IP_TYPE_ENUM_UINT8             enIpType
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn       = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn          = VOS_NULL_PTR;

    /* 获取PRIM PDP参数的格式 */
    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        pstNormalConn                   = IMSA_CONN_GetNormalConnAddr();
        pstNormalConn->enCurReqPdnType  = enIpType;
    }
    else
    {
        pstEmcConn                      = IMSA_CONN_GetEmcConnAddr();
        pstEmcConn->enCurReqPdnType     = enIpType;
    }
}

/*****************************************************************************
 Function Name  : IMSA_CONN_IsImsSdf
 Description    : 判断是否是IMS SDF
 Input          : pstSdfPara--------------------SDF指针
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-06-27  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_IsImsSdf
(
     const TAF_SDF_PARA_STRU            *pstSdfPara
)
{
    if (((IMSA_OP_TRUE == pstSdfPara->bitOpImCnSignalFlg)
       && (TAF_PDP_FOR_IM_CN_SIG_ONLY == pstSdfPara->enImCnSignalFlg))
       ||((IMSA_OP_TRUE == pstSdfPara->bitOpImsSuppFlg)
       && (IMSA_TRUE == pstSdfPara->ucImsSuppFlg)))
    {
        return IMSA_TRUE;
    }

    return IMSA_FALSE;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_IsPndTypeValid
 Description    : 判断pdn类型是否正确
 Input          : pstSdfPara--------------------SDF指针
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-06-27  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_IsPndTypeValid
(
     const TAF_SDF_PARA_STRU            *pstSdfPara
)
{
    if ((IMSA_OP_TRUE == pstSdfPara->bitOpPdnType)
       && (TAF_PDP_IPV4 <= pstSdfPara->enPdnType)
       && (TAF_PDP_IPV4V6 >= pstSdfPara->enPdnType))
    {
        return IMSA_TRUE;
    }

    return IMSA_FALSE;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_IsEmcSdf
 Description    : 判断是否是EMS SDF
 Input          : pstSdfPara--------------------SDF指针
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-06-27  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_IsEmcSdf
(
     const TAF_SDF_PARA_STRU            *pstSdfPara
)
{
    if ((IMSA_OP_TRUE == pstSdfPara->bitOpEmergencyInd)
       && (TAF_PDP_FOR_EMC == pstSdfPara->enEmergencyInd))
    {
        return IMSA_TRUE;
    }

    return IMSA_FALSE;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_FindSipSignalReStablishDialPara
 Description    : 获取SIP信令承载重建立时的拨号参数
 Input          : ucCid-------------------------CID
                  ulSdfNum----------------------SDF数
                  pstSdfPara--------------------SDF数组首地址
 Output         : pulIndex----------------------获取到的拨号参数的索引指针
 Return Value   : VOS_UINT32

 History        :
      1.wangchen 00209181   2014-3-12  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_FindSipSignalReStablishDialPara
(
    VOS_UINT8                           ucCid,
    VOS_UINT32                          ulSdfNum,
    const TAF_SDF_PARA_STRU            *pstSdfPara,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          i = IMSA_NULL;

    if (ulSdfNum == 0)
    {
        IMSA_ERR_LOG("IMSA_CONN_FindSipSignalReStablishDialPara:No Sdf!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_FindSipSignalReStablishDialPara_ENUM, 1);
        return IMSA_FAIL;
    }

    for (i = 0; i < ulSdfNum; i++)
    {
        if (ucCid == pstSdfPara[i].ucCid)
        {
            *pulIndex = i;

            return IMSA_SUCC;
        }
    }
    return IMSA_FAIL;
}


/*****************************************************************************
 Function Name  : IMSA_CONN_FindSipSignalDialPara
 Description    : 获取SIP信令承载拨号参数
 Input          : enConnType--------------------连接类型
                  ulSdfNum----------------------SDF数
                  pstSdfPara--------------------SDF数组首地址
 Output         : pulIndex----------------------获取到的拨号参数的索引指针
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-06-27  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_FindSipSignalDialPara
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    VOS_UINT32                          ulSdfNum,
    const TAF_SDF_PARA_STRU            *pstSdfPara,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          i = IMSA_NULL;

    if (ulSdfNum == 0)
    {
        IMSA_ERR_LOG("IMSA_CONN_FindSipSignalDialPara:No Sdf!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_FindSipSignalDialPara_ENUM, 1);
        return IMSA_FAIL;
    }

    /* 普通连接选择具有TAF_PDP_FOR_IMS_CN_SIG_ONLY标识，PDN类型和APN参数，
       且参数合法有效的CID；紧急连接选择具有TAF_PDP_FOR_IMS_CN_SIG_ONLY标识
       和TAF_PDP_FOR_EMC，PDN类型和APN参数，且参数合法有效的CID */
    for (i = 0; i < ulSdfNum; i++)
    {
        if (IMSA_OP_TRUE == pstSdfPara[i].bitOpLinkdCid)
        {
            continue;
        }

        if (IMSA_TRUE != IMSA_CONN_IsImsSdf(&pstSdfPara[i]))
        {
            continue;
        }

        if (IMSA_TRUE != IMSA_CONN_IsPndTypeValid(&pstSdfPara[i]))
        {
            continue;
        }

        if (IMSA_CONN_TYPE_EMC == enConnType)
        {
            if (IMSA_TRUE != IMSA_CONN_IsEmcSdf(&pstSdfPara[i]))
            {
                continue;
            }
        }
        else/* 如果是普通类型，则不选择有紧急标识的CID */
        {
            if (IMSA_OP_TRUE != pstSdfPara[i].bitOpApn)
            {
                continue;
            }

            if (IMSA_TRUE == IMSA_CONN_IsEmcSdf(&pstSdfPara[i]))
            {
                continue;
            }
        }

        *pulIndex = i;

        return IMSA_SUCC;
    }

    return IMSA_FAIL;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_SaveSelectedSdfPara
 Description    : 存储选中的SDF参数
 Input          : enConnType--------------------连接类型
 Output         : pstTafSdfPara-----------------TAF SDF参数指针
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-06-27  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_SaveSelectedSdfPara
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    const TAF_SDF_PARA_STRU            *pstTafSdfPara
)
{
    IMSA_SEL_SDF_PARA_STRU             *pstSelSdfPara = VOS_NULL_PTR;

    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        pstSelSdfPara = IMSA_CONN_GetEmcConnSelSdfParaAddr();
    }
    else
    {
        pstSelSdfPara = IMSA_CONN_GetNormalConnSelSdfParaAddr();
    }

    IMSA_MEM_SET_S( pstSelSdfPara,
                    sizeof(IMSA_SEL_SDF_PARA_STRU),
                    0x0,
                    sizeof(IMSA_SEL_SDF_PARA_STRU));

    pstSelSdfPara->ucCid                    = pstTafSdfPara->ucCid;

    pstSelSdfPara->bitOpLinkdCid            = pstTafSdfPara->bitOpLinkdCid;
    pstSelSdfPara->ucLinkdCid               = pstTafSdfPara->ucLinkdCid;

    pstSelSdfPara->bitOpPdnType             = pstTafSdfPara->bitOpPdnType;
    pstSelSdfPara->enPdnType                = pstTafSdfPara->enPdnType;

    pstSelSdfPara->bitOpApn = pstTafSdfPara->bitOpApn;
    IMSA_MEM_CPY_S( &pstSelSdfPara->stApnInfo,
                    sizeof(TAF_PDP_APN_STRU),
                    &pstTafSdfPara->stApnInfo,
                    sizeof(TAF_PDP_APN_STRU));

    pstSelSdfPara->bitOpGwAuthInfo = pstTafSdfPara->bitOpGwAuthInfo;
    IMSA_MEM_CPY_S( &pstSelSdfPara->stGwAuthInfo,
                    sizeof(TAF_GW_AUTH_STRU),
                    &pstTafSdfPara->stGwAuthInfo,
                    sizeof(TAF_GW_AUTH_STRU));

    pstSelSdfPara->bitOpEmergencyInd        = pstTafSdfPara->bitOpEmergencyInd;
    pstSelSdfPara->enEmergencyInd           = pstTafSdfPara->enEmergencyInd;

    pstSelSdfPara->bitOpIpv4AddrAllocType   = pstTafSdfPara->bitOpIpv4AddrAllocType;
    pstSelSdfPara->enIpv4AddrAllocType      = pstTafSdfPara->enIpv4AddrAllocType;

    pstSelSdfPara->bitOpPcscfDiscovery      = pstTafSdfPara->bitOpPcscfDiscovery;
    pstSelSdfPara->enPcscfDiscovery         = pstTafSdfPara->enPcscfDiscovery;

    pstSelSdfPara->bitOpImCnSignalFlg       = pstTafSdfPara->bitOpImCnSignalFlg;
    pstSelSdfPara->enImCnSignalFlg          = pstTafSdfPara->enImCnSignalFlg;

    pstSelSdfPara->bitOpImsSuppFlg          = pstTafSdfPara->bitOpImsSuppFlg;
    pstSelSdfPara->ucImsSuppFlg             = pstTafSdfPara->ucImsSuppFlg;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_GetPrimPdpCntFromSelSdfPara
 Description    : 将选择的SDF参数转化成PRIMARY PDP CONTEXT
 Input          : pstSelectedSdfPara---------------选择的SDF参数指针
 Output         : pstPdpPrimContextExt-------------PDP CONTEXT参数指针
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-27  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_GetPrimPdpCntFromSelSdfPara
(
    const IMSA_SEL_SDF_PARA_STRU       *pstSelectedSdfPara,
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt
)
{
    IMSA_MEM_SET_S(                     (VOS_VOID *)pstPdpPrimContextExt,
                                        sizeof(TAF_PDP_PRIM_CONTEXT_EXT_STRU),
                                        0x00,
                                        sizeof(TAF_PDP_PRIM_CONTEXT_EXT_STRU));

    pstPdpPrimContextExt->ucCid         = pstSelectedSdfPara->ucCid;
    pstPdpPrimContextExt->ucDefined     = 1;

    /* 赋值PDN TYPE */
    pstPdpPrimContextExt->bitOpPdpType  = pstSelectedSdfPara->bitOpPdnType;
    pstPdpPrimContextExt->enPdpType     = pstSelectedSdfPara->enPdnType;

    /* 赋值APN */
    pstPdpPrimContextExt->bitOpApn      = pstSelectedSdfPara->bitOpApn;
    IMSA_MEM_CPY_S(                     (VOS_CHAR*)pstPdpPrimContextExt->aucApn,
                                        sizeof(pstPdpPrimContextExt->aucApn),
                                        (VOS_CHAR*)pstSelectedSdfPara->stApnInfo.aucValue,
                                        pstSelectedSdfPara->stApnInfo.ucLength);

    /* 赋值Ipv4AddrAlloc */
    pstPdpPrimContextExt->bitOpIpv4AddrAlloc    = pstSelectedSdfPara->bitOpIpv4AddrAllocType;
    pstPdpPrimContextExt->enIpv4AddrAlloc       = pstSelectedSdfPara->enIpv4AddrAllocType;

    /* 赋值紧急标识 */
    pstPdpPrimContextExt->bitOpEmergencyInd     = pstSelectedSdfPara->bitOpEmergencyInd;
    pstPdpPrimContextExt->enEmergencyFlg        = pstSelectedSdfPara->enEmergencyInd;

    /* 赋值P-CSCF发现方式 */
    pstPdpPrimContextExt->bitOpPcscfDiscovery   = pstSelectedSdfPara->bitOpPcscfDiscovery;
    pstPdpPrimContextExt->enPcscfDiscovery      = pstSelectedSdfPara->enPcscfDiscovery;

    /* 赋值IMS标识 */
    pstPdpPrimContextExt->bitOpImCnSignalFlg    = pstSelectedSdfPara->bitOpImCnSignalFlg;
    pstPdpPrimContextExt->enImCnSignalFlg       = pstSelectedSdfPara->enImCnSignalFlg;
}


/*****************************************************************************
 Function Name  : IMSA_CONN_GetImsDailParaFromSelSdfPara
 Description    : 将选择的SDF参数转化成拨号参数格式
 Input          : pstSelectedSdfPara---------------选择的SDF参数指针
 Output         : pstDialParaInfo------------------拨号参数指针
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-27  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_GetImsDailParaFromSelSdfPara
(
    const IMSA_SEL_SDF_PARA_STRU       *pstSelectedSdfPara,
    TAF_PS_DIAL_PARA_STRU              *pstDialParaInfo
)
{
    IMSA_MEM_SET_S( pstDialParaInfo,
                    sizeof(TAF_PS_DIAL_PARA_STRU),
                    0,
                    sizeof(TAF_PS_DIAL_PARA_STRU));

    pstDialParaInfo->ucCid                  = pstSelectedSdfPara->ucCid;
    pstDialParaInfo->enPdpType              = pstSelectedSdfPara->enPdnType;

    /* 赋值APN信息 */
    if (IMSA_OP_TRUE == pstSelectedSdfPara->bitOpApn)
    {
        pstDialParaInfo->bitOpApn           = IMSA_OP_TRUE;

        /* 拨号APN参数没有长度字段，是因为是字符串格式，已在结尾加上'\0' */
        IMSA_MEM_CPY_S(                     pstDialParaInfo->aucApn,
                                            TAF_MAX_APN_LEN,
                                            pstSelectedSdfPara->stApnInfo.aucValue,
                                            pstSelectedSdfPara->stApnInfo.ucLength);
    }

    /* 赋值鉴权参数 */
    if (IMSA_OP_TRUE == pstSelectedSdfPara->bitOpGwAuthInfo)
    {
        pstDialParaInfo->bitOpAuthType      = IMSA_OP_TRUE;
        pstDialParaInfo->enAuthType         = pstSelectedSdfPara->stGwAuthInfo.enAuthType;

        if (pstSelectedSdfPara->stGwAuthInfo.ucUserNameLen != 0)
        {
            pstDialParaInfo->bitOpUserName  = IMSA_OP_TRUE;

            /* 拨号用户名参数没有长度字段，是因为是字符串格式，已在结尾加上'\0' */
            IMSA_MEM_CPY_S(                 pstDialParaInfo->aucUserName,
                                            TAF_MAX_GW_AUTH_USERNAME_LEN,
                                            pstSelectedSdfPara->stGwAuthInfo.aucUserName,
                                            pstSelectedSdfPara->stGwAuthInfo.ucUserNameLen);
        }

        if (pstSelectedSdfPara->stGwAuthInfo.ucPwdLen       != 0)
        {
            pstDialParaInfo->bitOpPassWord  = IMSA_OP_TRUE;

            /* 拨号密码参数没有长度字段，是因为是字符串格式，已在结尾加上'\0' */
            IMSA_MEM_CPY_S(                 pstDialParaInfo->aucPassWord,
                                            TAF_MAX_GW_AUTH_PASSWORD_LEN,
                                            pstSelectedSdfPara->stGwAuthInfo.aucPwd,
                                            pstSelectedSdfPara->stGwAuthInfo.ucPwdLen);
        }
    }

    if (IMSA_OP_TRUE == pstSelectedSdfPara->bitOpIpv4AddrAllocType)
    {
        pstDialParaInfo->bitOpIpv4AddrAlloc = IMSA_OP_TRUE;
        pstDialParaInfo->enIpv4AddrAlloc = pstSelectedSdfPara->enIpv4AddrAllocType;
    }

    if (IMSA_OP_TRUE == pstSelectedSdfPara->bitOpEmergencyInd)
    {
        pstDialParaInfo->bitOpEmergencyInd = IMSA_OP_TRUE;
        pstDialParaInfo->enEmergencyInd = pstSelectedSdfPara->enEmergencyInd;
    }

    if (IMSA_OP_TRUE == pstSelectedSdfPara->bitOpPcscfDiscovery)
    {
        pstDialParaInfo->bitOpPcscfDiscovery = IMSA_OP_TRUE;
        pstDialParaInfo->enPcscfDiscovery = pstSelectedSdfPara->enPcscfDiscovery;
    }

    if (IMSA_OP_TRUE == pstSelectedSdfPara->bitOpImCnSignalFlg)
    {
        pstDialParaInfo->bitOpImCnSignalFlg = IMSA_OP_TRUE;
        pstDialParaInfo->enImCnSignalFlg = pstSelectedSdfPara->enImCnSignalFlg;
    }

    pstDialParaInfo->bitOpReqType = IMSA_OP_FALSE;
    pstDialParaInfo->bitOpPdpDcomp = IMSA_OP_FALSE;
    pstDialParaInfo->bitOpPdpHcomp = IMSA_OP_FALSE;

}

/*****************************************************************************
 Function Name  : IMSA_CONN_ConvertIpAddress2String
 Description    : IMSA CONN模块将IP地址转成字符串格式
 Input          : enIpType------------------IP类型
                  pucSrc--------------------IP地址指针
 Output         : pcDst---------------------输出字符串指针
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_ConvertIpAddress2String
(
    IMSA_IP_TYPE_ENUM_UINT8             enIpType,
    const VOS_UINT8                    *pucSrc,
    VOS_CHAR                           *pcDst
)
{
#if (VOS_OS_VER != VOS_WIN32)
#if (VOS_OS_VER == VOS_VXWORKS)
/*lint -e718 -e746 -e40 */
    if (IMSA_IP_TYPE_IPV4 == enIpType)
    {
        inet_ntop(AF_INET, pucSrc , pcDst, 16);
    }
    else
    {
        inet_ntop(AF_INET6, pucSrc , pcDst, 46);
    }
/*lint +e718 +e746 +e40 */
#else
/*lint -e64*/
    if (IMSA_IP_TYPE_IPV4 == enIpType)
    {
        (VOS_VOID)vrp_inet_ntop(VRP_AF_INET, (const CHAR *)pucSrc , pcDst, 16);
    }
    else
    {
        (VOS_VOID)vrp_inet_ntop(VRP_AF_INET6, (const CHAR *)pucSrc , pcDst, 46);
    }
/*lint +e64*/
#endif
#else
    VOS_UINT8                           i = 0;

    if (IMSA_IP_TYPE_IPV4 == enIpType)
    {
        /* ST中的IPV6地址和IPV6类型的P-CSCF地址的最后一个字节必须是[0,9] */
        IMSA_MEM_CPY_S( pcDst,
                        (IMSA_IPV4_ADDR_STRING_LEN + 1),
                        g_acIpStringForSt_ipv4,
                        (IMSA_IPV4_ADDR_STRING_LEN + 1));
        i = strlen(g_acIpStringForSt_ipv4) - 1;
        pcDst[i] = pucSrc[3] + 0x30;
        /*g_acIpStringForSt_ipv4[i] ++ ;*/
    }
    else
    {
        /* ST中的IPV6地址和IPV6类型的P-CSCF地址的最后一个字节必须是大于等于16 */
        IMSA_MEM_CPY_S( pcDst,
                        (IMSA_IPV6_ADDR_STRING_LEN + 1),
                        g_acIpStringForSt_ipv6,
                        (IMSA_IPV6_ADDR_STRING_LEN + 1));

        i = strlen(g_acIpStringForSt_ipv6) - 1;
        pcDst[i] = (pucSrc[15] - 16) + 0x30;
        /*g_acIpStringForSt_ipv6[i] ++ ;*/
    }

#endif
}


/*****************************************************************************
 Function Name  : IMSA_CONN_FilterRegedPcscfInfo
 Description    : 用于过滤出已经注册的P-CSCF地址
 Input          : enConnType---------------------连接类型
                  pstPdpInfo---------------------PDP上下文指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.xiongxianghui 00253310      2015-09-02  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_FilterRegedPcscfInfo
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpContext
)
{
    VOS_CHAR                            acUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
    VOS_CHAR                            acRegUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
    VOS_CHAR                            acRegPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
    VOS_UINT32                          ulRslt          = IMSA_FAIL;

    IMSA_IP_TYPE_ENUM_UINT8             enIpType = IMSA_IP_TYPE_BUTT;

    ulRslt = IMSA_RegGetRegedPara(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                    acRegUeAddr,
                                    acRegPcscfAddr,
                                    &enIpType);

    /* 如果未获取到注册上的参数，则直接返回不包含 */
    if (IMSA_FAIL == ulRslt)
    {
        return IMSA_FALSE;
    }

    if ((IMSA_IP_TYPE_IPV4 == enIpType) || (IMSA_IP_TYPE_IPV4V6 == enIpType))
    {
        if (IMSA_OP_TRUE == pstPdpContext->stPdpIpv4Pcscf.bitOpPrimPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpContext->stPdpIpv4Pcscf.aucPrimPcscfAddr,
                                                acUeAddr);
            if (0 == VOS_StrCmp(acRegPcscfAddr, acUeAddr))
            {
                pstPdpContext->stPdpIpv4Pcscf.bitOpPrimPcscfAddr = IMSA_OP_FALSE;
                return IMSA_TRUE;
            }
        }

        if (IMSA_OP_TRUE == pstPdpContext->stPdpIpv4Pcscf.bitOpSecPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpContext->stPdpIpv4Pcscf.aucSecPcscfAddr,
                                                acUeAddr);
            if (0 == VOS_StrCmp(acRegPcscfAddr, acUeAddr))
            {
                pstPdpContext->stPdpIpv4Pcscf.bitOpSecPcscfAddr = IMSA_OP_FALSE;
                return IMSA_TRUE;
            }
        }

        if (IMSA_OP_TRUE == pstPdpContext->stPdpIpv4Pcscf.bitOpThiPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpContext->stPdpIpv4Pcscf.aucThiPcscfAddr,
                                                acUeAddr);
            if (0 == VOS_StrCmp(acRegPcscfAddr, acUeAddr))
            {
                pstPdpContext->stPdpIpv4Pcscf.bitOpThiPcscfAddr = IMSA_OP_FALSE;
                return IMSA_TRUE;
            }
        }
    }

    if ((IMSA_IP_TYPE_IPV6 == enIpType) || (IMSA_IP_TYPE_IPV4V6 == enIpType))
    {
        if (IMSA_OP_TRUE == pstPdpContext->stPdpIpv6Pcscf.bitOpPrimPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpContext->stPdpIpv6Pcscf.aucPrimPcscfAddr,
                                                acUeAddr);
            if (0 == VOS_StrCmp(acRegPcscfAddr, acUeAddr))
            {
                pstPdpContext->stPdpIpv6Pcscf.bitOpPrimPcscfAddr = IMSA_OP_FALSE;
                return IMSA_TRUE;
            }
        }

        if (IMSA_OP_TRUE == pstPdpContext->stPdpIpv6Pcscf.bitOpSecPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpContext->stPdpIpv6Pcscf.aucSecPcscfAddr,
                                                acUeAddr);
            if (0 == VOS_StrCmp(acRegPcscfAddr, acUeAddr))
            {
                pstPdpContext->stPdpIpv6Pcscf.bitOpSecPcscfAddr = IMSA_OP_FALSE;
                return IMSA_TRUE;
            }
        }

        if (IMSA_OP_TRUE == pstPdpContext->stPdpIpv6Pcscf.bitOpThiPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpContext->stPdpIpv6Pcscf.aucThiPcscfAddr,
                                                acUeAddr);
            if (0 == VOS_StrCmp(acRegPcscfAddr, acUeAddr))
            {
                pstPdpContext->stPdpIpv6Pcscf.bitOpThiPcscfAddr = IMSA_OP_FALSE;
                return IMSA_TRUE;
            }
        }
    }

    return IMSA_FALSE;
}
/*****************************************************************************
 Function Name  : IMSA_CONN_DeletePcscfInfo2Reg
 Description    : 删除REG模块中的PCSCF地址
 Input          : enConnType---------------------连接类型
                  pstPdpInfo---------------------PDP上下文指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.xiongxianghui 00253310      2015-09-02  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_DeletePcscfInfo2Reg
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    const IMSA_PDP_CNTXT_INFO_STRU     *pstPdpInfo
)
{
    VOS_CHAR                    acUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};

    if ((IMSA_IP_TYPE_IPV4 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {

        /* 删除IPV4 P-CSCF地址 */
        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpPrimPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpInfo->stPdpIpv4Pcscf.aucPrimPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrRmvPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV4,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpSecPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpInfo->stPdpIpv4Pcscf.aucSecPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrRmvPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV4,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpThiPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpInfo->stPdpIpv4Pcscf.aucThiPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrRmvPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV4,
                                                        acUeAddr);
        }
    }

    if ((IMSA_IP_TYPE_IPV6 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        /* 删除IPV6 P-CSCF地址 */
        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpPrimPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpIpv6Pcscf.aucPrimPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrRmvPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV6,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpSecPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpIpv6Pcscf.aucSecPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrRmvPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV6,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpThiPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpIpv6Pcscf.aucThiPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrRmvPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV6,
                                                        acUeAddr);
        }
    }
}
/*****************************************************************************
 Function Name  : IMSA_CONN_DeletePcscfInfo2Reg
 Description    : 给REG模块配置P-CSCF信息
 Input          : enConnType---------------------连接类型
                  pstPdpInfo---------------------PDP上下文指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.xiongxianghui 00253310      2015-09-02  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_ConfigPcscfInfo2Reg
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    const IMSA_PDP_CNTXT_INFO_STRU     *pstPdpInfo
)
{
    VOS_CHAR                    acUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};

    if ((IMSA_IP_TYPE_IPV4 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        /* 配置IPV4 P-CSCF地址 */
        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpPrimPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpInfo->stPdpIpv4Pcscf.aucPrimPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV4,
                                                        IMSA_PCSCF_SRC_TYPE_PDN,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpSecPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpInfo->stPdpIpv4Pcscf.aucSecPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV4,
                                                        IMSA_PCSCF_SRC_TYPE_PDN,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpThiPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpInfo->stPdpIpv4Pcscf.aucThiPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV4,
                                                        IMSA_PCSCF_SRC_TYPE_PDN,
                                                        acUeAddr);
        }

    }

    if ((IMSA_IP_TYPE_IPV6 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        /* 配置IPV6 P-CSCF地址 */
        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpPrimPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpIpv6Pcscf.aucPrimPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV6,
                                                        IMSA_PCSCF_SRC_TYPE_PDN,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpSecPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpIpv6Pcscf.aucSecPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV6,
                                                        IMSA_PCSCF_SRC_TYPE_PDN,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpThiPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpIpv6Pcscf.aucThiPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV6,
                                                        IMSA_PCSCF_SRC_TYPE_PDN,
                                                        acUeAddr);
        }

    }
}

/*****************************************************************************
 Function Name  : IMSA_CONN_DeleteOldPcscfInfoAndConfigNewPcscfInfo
 Description    : 将备份承载信息中未注册的地址对删除，
                  将修改承载信息中未注册的PCSCF地址配成地址对并保持
 Input          : enConnType---------------------连接类型
                  pstPdpContext------------------新的PDP上下文指针
                  pstPdpContextOld---------------备份的PDP上下文指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.xiongxianghui 00253310      2015-09-08  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_DeleteOldPcscfInfoAndConfigNewPcscfInfo
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpContext,
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpContextOld
)
{
    IMSA_PDP_CNTXT_INFO_STRU            *pstPdpContextOldTemp = VOS_NULL_PTR;
    IMSA_PDP_CNTXT_INFO_STRU            *pstPdpContextNewTemp = VOS_NULL_PTR;

    pstPdpContextOldTemp = IMSA_MEM_ALLOC(sizeof(IMSA_PDP_CNTXT_INFO_STRU));
    if (VOS_NULL_PTR == pstPdpContextOldTemp)
    {
        return;

    }

    pstPdpContextNewTemp = IMSA_MEM_ALLOC(sizeof(IMSA_PDP_CNTXT_INFO_STRU));
    if (VOS_NULL_PTR == pstPdpContextNewTemp)
    {
        IMSA_MEM_FREE(pstPdpContextOldTemp);
        return;
    }

    IMSA_MEM_SET_S( pstPdpContextOldTemp,
                    sizeof(IMSA_PDP_CNTXT_INFO_STRU),
                    0x0,
                    sizeof(IMSA_PDP_CNTXT_INFO_STRU));
    IMSA_MEM_SET_S( pstPdpContextNewTemp,
                    sizeof(IMSA_PDP_CNTXT_INFO_STRU),
                    0x0,
                    sizeof(IMSA_PDP_CNTXT_INFO_STRU));

    IMSA_MEM_CPY_S( pstPdpContextOldTemp,
                    sizeof(IMSA_PDP_CNTXT_INFO_STRU),
                    pstPdpContextOld,
                    sizeof(IMSA_PDP_CNTXT_INFO_STRU));
    IMSA_MEM_CPY_S( pstPdpContextNewTemp,
                    sizeof(IMSA_PDP_CNTXT_INFO_STRU),
                    pstPdpContext,
                    sizeof(IMSA_PDP_CNTXT_INFO_STRU));

    /* 从原有备份的承载信息中过滤出已注册的PCSCF地址，
       并将未注册的PCSCF地址删除 */
    if (IMSA_TRUE == IMSA_CONN_FilterRegedPcscfInfo(enConnType, pstPdpContextOldTemp))
    {
        IMSA_CONN_DeletePcscfInfo2Reg(enConnType, pstPdpContextOldTemp);
    }

    /* 从修改承载信息中过滤出和已注册的PCSCF地址相同的地址信息，
       并将其他PCSCF地址配成地址对 */
    if (IMSA_TRUE == IMSA_CONN_FilterRegedPcscfInfo(enConnType, pstPdpContextNewTemp))
    {
        IMSA_CONN_ConfigPcscfInfo2Reg(enConnType, pstPdpContextNewTemp);
    }

    IMSA_MEM_FREE(pstPdpContextOldTemp);
    IMSA_MEM_FREE(pstPdpContextNewTemp);

    return;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ProcPcscfInvalid
 Description    : 判断当前注册地址是否失效
 Input          : enConnType---------------------连接类型
                  pstPdpContext------------------修改后PDP上下文指针
                  pstPdpContextOld---------------原来PDN上下文指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181      2015-03-25  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_ProcPcscfInvalid
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpContext,
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpContextOld
)
{
    VOS_CHAR                            acRegUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
    VOS_CHAR                            acRegPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
    VOS_UINT32                          ulRslt   = IMSA_FAIL;
    IMSA_IP_TYPE_ENUM_UINT8             enIpType = IMSA_IP_TYPE_BUTT;

    /* 获取注册参数IP类型 */
    ulRslt = IMSA_RegGetRegedPara(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                    acRegUeAddr,
                                    acRegPcscfAddr,
                                    &enIpType);
    if (IMSA_FAIL == ulRslt)
    {
        return ;
    }

    if ((IMSA_IP_TYPE_IPV4V6 != pstPdpContext->stPdpAddr.enIpType) &&
        (enIpType != pstPdpContext->stPdpAddr.enIpType))
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcPcscfInvalid:IP TYPE NOT MATCH!");

        /* 注册参数IP类型与新的承载信息IP类型不一致，只生成新的地址对
           不需要在识别注册参数是否失效 */

        /* 调用REG模块删除修改承载的IP地址和P-CSCF地址 */
        IMSA_CONN_DeletePdpInfo2Reg(enConnType, pstPdpContextOld);

        /* 给REG模块配置地址对 */
        IMSA_CONN_ConfigPdpInfo2Reg(enConnType, pstPdpContext);
        return ;
    }

    /* 如果这注册参数IP类型与新的承载信息IP类型一致，需要识别注册参数是否失效 */
    if (IMSA_FALSE == IMSA_CONN_IsPdpInfoIncludeRegPara(enConnType, pstPdpContext))
    {
        /* 调用REG模块删除修改承载的IP地址和P-CSCF地址 */
        IMSA_CONN_DeletePdpInfo2Reg(enConnType, pstPdpContextOld);

        /* 给REG模块配置地址对 */
        IMSA_CONN_ConfigPdpInfo2Reg(enConnType, pstPdpContext);

        /* 给CONN模块发送MODIFY消息，类型为注册地址失效 */
        IMSA_CONN_SndConnRegPcscfInvalid(enConnType);
    }
    else
    {
        /* 注册参数没有失效，将备份承载信息中非注册参数的PCSCF删除，
           将新的承载信息中非注册参数的PCSCF配置成地址对 */
        IMSA_CONN_DeleteOldPcscfInfoAndConfigNewPcscfInfo(enConnType, pstPdpContext, pstPdpContextOld);
    }
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ConfigPdpInfo2Reg
 Description    : IMSA CONN模块配置承载信息给REG模块
 Input          : enConnType---------------------连接类型
                  pstPdpInfo---------------------PDP上下文指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_ConfigPdpInfo2Reg
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    const IMSA_PDP_CNTXT_INFO_STRU     *pstPdpInfo
)
{
    VOS_CHAR                    acUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
    VOS_UINT8                   aucTemp[IMSA_IPV6_PREFIX_LEN]           = {0};

    if ((IMSA_IP_TYPE_IPV4 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        /* 配置IPV4地址 */
        IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                            pstPdpInfo->stPdpAddr.aucIpV4Addr,
                                            acUeAddr);

        (VOS_VOID)IMSA_RegAddrPairMgrAddUeAddr( (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                IMSA_IP_TYPE_IPV4,
                                                acUeAddr);

        /* 配置IPV4 P-CSCF地址 */
        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpPrimPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpInfo->stPdpIpv4Pcscf.aucPrimPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV4,
                                                        IMSA_PCSCF_SRC_TYPE_PDN,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpSecPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpInfo->stPdpIpv4Pcscf.aucSecPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV4,
                                                        IMSA_PCSCF_SRC_TYPE_PDN,
                                                        acUeAddr);
        }
        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpThiPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpInfo->stPdpIpv4Pcscf.aucThiPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV4,
                                                        IMSA_PCSCF_SRC_TYPE_PDN,
                                                        acUeAddr);
        }
    }

    if ((IMSA_IP_TYPE_IPV6 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        /* 配置IPV6地址 */
        if (0 != IMSA_MEM_CMP(aucTemp, pstPdpInfo->stPdpAddr.aucIpV6Addr, IMSA_IPV6_PREFIX_LEN))
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpAddr.aucIpV6Addr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddUeAddr( (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                    IMSA_IP_TYPE_IPV6,
                                                    acUeAddr);
        }

        /* 配置IPV6 P-CSCF地址 */
        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpPrimPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpIpv6Pcscf.aucPrimPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV6,
                                                        IMSA_PCSCF_SRC_TYPE_PDN,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpSecPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpIpv6Pcscf.aucSecPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV6,
                                                        IMSA_PCSCF_SRC_TYPE_PDN,
                                                        acUeAddr);
        }
        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpThiPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpIpv6Pcscf.aucThiPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV6,
                                                        IMSA_PCSCF_SRC_TYPE_PDN,
                                                        acUeAddr);
        }
    }
}

/*****************************************************************************
 Function Name  : IMSA_CONN_DeletePdpInfo2Reg
 Description    : IMSA CONN模块删除REG模块中的承载信息
 Input          : enConnType---------------------连接类型
                  pstPdpInfo---------------------PDP上下文指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_DeletePdpInfo2Reg
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    const IMSA_PDP_CNTXT_INFO_STRU     *pstPdpInfo
)
{
    VOS_CHAR                    acUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};

    if ((IMSA_IP_TYPE_IPV4 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        /* 删除IPV4地址 */
        IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                            pstPdpInfo->stPdpAddr.aucIpV4Addr,
                                            acUeAddr);

        (VOS_VOID)IMSA_RegAddrPairMgrRmvUeAddr( (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                IMSA_IP_TYPE_IPV4,
                                                acUeAddr);

        /* 删除IPV4 P-CSCF地址 */
        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpPrimPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpInfo->stPdpIpv4Pcscf.aucPrimPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrRmvPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV4,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpSecPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpInfo->stPdpIpv4Pcscf.aucSecPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrRmvPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV4,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpThiPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpInfo->stPdpIpv4Pcscf.aucThiPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrRmvPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV4,
                                                        acUeAddr);
        }



    }

    if ((IMSA_IP_TYPE_IPV6 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        /* 删除IPV6地址 */
        IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                            pstPdpInfo->stPdpAddr.aucIpV6Addr,
                                            acUeAddr);

        (VOS_VOID)IMSA_RegAddrPairMgrRmvUeAddr( (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                IMSA_IP_TYPE_IPV6,
                                                acUeAddr);

        /* 删除IPV6 P-CSCF地址 */
        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpPrimPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpIpv6Pcscf.aucPrimPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrRmvPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV6,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpSecPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpIpv6Pcscf.aucSecPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrRmvPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV6,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpThiPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpIpv6Pcscf.aucThiPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrRmvPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV6,
                                                        acUeAddr);
        }
    }
}
/*****************************************************************************
 Function Name  : IMSA_CONN_PdnInfoNicConfig
 Description    : IMSA调用IMS_NIC_PdnInfoConfig API
                  pstPdpInfo---------------------PDP上下文指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2014-1-23  Draft Enact
*****************************************************************************/

VOS_UINT32 IMSA_CONN_PdnInfoNicConfig (IMS_NIC_PDN_INFO_CONFIG_STRU *pstConfigInfo)
{
    VOS_UINT32                          ulRslt                          = IMSA_FAIL;

    IMSA_INFO_LOG("IMSA_CONN_PdnInfoNicConfig enter");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_PdnInfoNicConfig_ENUM, LNAS_ENTRY);
    IMSA_INFO_LOG1("IMSA_CONN_PdnInfoNicConfig ,usSockMaxPort=:", pstConfigInfo->stSockPortInfo.usSockMaxPort);
    TLPS_PRINT2LAYER_INFO1(IMSA_CONN_PdnInfoNicConfig_ENUM, 1, pstConfigInfo->stSockPortInfo.usSockMaxPort);
    IMSA_INFO_LOG1("IMSA_CONN_PdnInfoNicConfig ,usSockMinPort=:", pstConfigInfo->stSockPortInfo.usSockMinPort);
    TLPS_PRINT2LAYER_INFO1(IMSA_CONN_PdnInfoNicConfig_ENUM, 2, pstConfigInfo->stSockPortInfo.usSockMinPort);

    ulRslt = IMS_NIC_PdnInfoConfig(pstConfigInfo);

    IMSA_INFO_LOG("IMSA_CONN_PdnInfoNicConfig leave");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_PdnInfoNicConfig_ENUM, LNAS_LEAVE);

    return ulRslt;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ConfigPdpIPv6Info2Bsp
 Description    : IMSA CONN模块配置承载IPV6信息给BSP
                  pstPdpInfo---------------------PDP上下文指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-20  Draft Enact
      2.lihong 00150010      2013-12-24  Modify:Ut and IMS same APN
*****************************************************************************/
VOS_VOID IMSA_CONN_ConfigPdpIPv6Info2Bsp
(
    const IMSA_PDP_CNTXT_INFO_STRU     *pstPdpInfo
)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo                    = {0};
    VOS_UINT32                          ulRslt                          = IMSA_FAIL;
    VOS_UINT8                           aucTemp[IMSA_IPV6_PREFIX_LEN]   = {0};
    IMSA_CONTROL_MANAGER_STRU          *pstControlManager               = VOS_NULL_PTR;

    if ((IMSA_IP_TYPE_IPV6 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        if (0 != IMSA_MEM_CMP(aucTemp, pstPdpInfo->stPdpAddr.aucIpV6Addr, IMSA_IPV6_PREFIX_LEN))
        {
            IMSA_MEM_SET_S( &stConfigInfo,
                            sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU),
                            0,
                            sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

            stConfigInfo.ucRabId     = pstPdpInfo->ucPdpId;
            stConfigInfo.enModemId   = MODEM_ID_0;

            /* 配置IPV6地址 */
            stConfigInfo.bitOpIpv6PdnInfo    = IMSA_OP_TRUE;
            stConfigInfo.stIpv6PdnInfo.ulBitPrefixLen = IMSA_IPV6_PREFIX_BIT_LEN;
            IMSA_MEM_CPY_S( stConfigInfo.stIpv6PdnInfo.aucIpV6Addr,
                            IMSA_IPV6_ADDR_LEN,
                            pstPdpInfo->stPdpAddr.aucIpV6Addr,
                            IMSA_IPV6_ADDR_LEN);

            /* 配置IPV6 DNS地址 */
            stConfigInfo.stIpv6PdnInfo.bitOpDnsPrim = pstPdpInfo->stPdpIpv6Dns.bitOpPriDns;
            IMSA_MEM_CPY_S( stConfigInfo.stIpv6PdnInfo.aucDnsPrimAddr,
                            IMSA_IPV6_ADDR_LEN,
                            pstPdpInfo->stPdpIpv6Dns.aucPriDns,
                            IMSA_IPV6_ADDR_LEN);

            stConfigInfo.stIpv6PdnInfo.bitOpDnsSec = pstPdpInfo->stPdpIpv6Dns.bitOpSecDns;
            IMSA_MEM_CPY_S( stConfigInfo.stIpv6PdnInfo.aucDnsSecAddr,
                            IMSA_IPV6_ADDR_LEN,
                            pstPdpInfo->stPdpIpv6Dns.aucSecDns,
                            IMSA_IPV6_ADDR_LEN);

            /* 配置IP栈端口号范围 */
            pstControlManager = IMSA_GetControlManagerAddress();
            stConfigInfo.bitOpSockPortInfo = IMSA_OP_TRUE;
            stConfigInfo.stSockPortInfo.usSockMinPort
                    = pstControlManager->stImsaConfigPara.stImsPortConfig.usImsMinPort;
            stConfigInfo.stSockPortInfo.usSockMaxPort
                    = pstControlManager->stImsaConfigPara.stImsPortConfig.usImsMaxPort;

            ulRslt = IMSA_CONN_PdnInfoNicConfig(&stConfigInfo);
            if (IMS_NIC_SUCC != ulRslt)
            {
                IMSA_ERR_LOG1("IMS_NIC_PdnInfoConfig failed,result:", ulRslt);
                TLPS_PRINT2LAYER_ERROR1(IMSA_CONN_ConfigPdpIPv6Info2Bsp_ENUM, IMSA_CALL_API_ERROR, ulRslt);
            }
        }
    }
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ConfigPdpInfo2Bsp
 Description    : IMSA CONN模块配置承载信息给BSP
                  pstPdpInfo---------------------PDP上下文指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-20  Draft Enact
      2.lihong 00150010      2013-12-24  Modify:Ut and IMS same APN
*****************************************************************************/
VOS_VOID IMSA_CONN_ConfigPdpInfo2Bsp
(
    const IMSA_PDP_CNTXT_INFO_STRU     *pstPdpInfo
)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConigInfo                     = {0};
    VOS_UINT32                          ulRslt                          = IMSA_FAIL;
    VOS_UINT8                           aucTemp[IMSA_IPV6_PREFIX_LEN]   = {0};
    IMSA_CONTROL_MANAGER_STRU          *pstControlManager               = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CONN_ConfigPdpInfo2Bsp is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ConfigPdpInfo2Bsp_ENUM, LNAS_ENTRY);

    IMSA_MEM_SET_S( &stConigInfo,
                    sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU),
                    0,
                    sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConigInfo.ucRabId     = pstPdpInfo->ucPdpId;
    stConigInfo.enModemId   = MODEM_ID_0;

    if ((IMSA_IP_TYPE_IPV4 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        /* 配置IPV4地址 */
        stConigInfo.bitOpIpv4PdnInfo    = IMSA_OP_TRUE;
        IMSA_MEM_CPY_S(   stConigInfo.stIpv4PdnInfo.aucIpV4Addr,
                        IMSA_IPV4_ADDR_LEN,
                        pstPdpInfo->stPdpAddr.aucIpV4Addr,
                        IMSA_IPV4_ADDR_LEN);

        /* 配置IPV4 DNS地址 */
        stConigInfo.stIpv4PdnInfo.bitOpDnsPrim = pstPdpInfo->stPdpIpv4Dns.bitOpPriDns;
        IMSA_MEM_CPY_S(   stConigInfo.stIpv4PdnInfo.aucDnsPrimAddr,
                        IMSA_IPV4_ADDR_LEN,
                        pstPdpInfo->stPdpIpv4Dns.aucPriDns,
                        IMSA_IPV4_ADDR_LEN);

        stConigInfo.stIpv4PdnInfo.bitOpDnsSec = pstPdpInfo->stPdpIpv4Dns.bitOpSecDns;
        IMSA_MEM_CPY_S(   stConigInfo.stIpv4PdnInfo.aucDnsSecAddr,
                        IMSA_IPV4_ADDR_LEN,
                        pstPdpInfo->stPdpIpv4Dns.aucSecDns,
                        IMSA_IPV4_ADDR_LEN);
    }

    if ((IMSA_IP_TYPE_IPV6 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        if (0 != IMSA_MEM_CMP(aucTemp, pstPdpInfo->stPdpAddr.aucIpV6Addr, IMSA_IPV6_PREFIX_LEN))
        {
            /* 配置IPV6地址 */
            stConigInfo.bitOpIpv6PdnInfo    = IMSA_OP_TRUE;
            stConigInfo.stIpv6PdnInfo.ulBitPrefixLen = IMSA_IPV6_PREFIX_BIT_LEN;
            IMSA_MEM_CPY_S( stConigInfo.stIpv6PdnInfo.aucIpV6Addr,
                            IMSA_IPV6_ADDR_LEN,
                            pstPdpInfo->stPdpAddr.aucIpV6Addr,
                            IMSA_IPV6_ADDR_LEN);

            /* 配置IPV6 DNS地址 */
            stConigInfo.stIpv6PdnInfo.bitOpDnsPrim = pstPdpInfo->stPdpIpv6Dns.bitOpPriDns;
            IMSA_MEM_CPY_S(   stConigInfo.stIpv6PdnInfo.aucDnsPrimAddr,
                            IMSA_IPV6_ADDR_LEN,
                            pstPdpInfo->stPdpIpv6Dns.aucPriDns,
                            IMSA_IPV6_ADDR_LEN);

            stConigInfo.stIpv6PdnInfo.bitOpDnsSec = pstPdpInfo->stPdpIpv6Dns.bitOpSecDns;
            IMSA_MEM_CPY_S(   stConigInfo.stIpv6PdnInfo.aucDnsSecAddr,
                            IMSA_IPV6_ADDR_LEN,
                            pstPdpInfo->stPdpIpv6Dns.aucSecDns,
                            IMSA_IPV6_ADDR_LEN);
        }
    }

    if ((IMSA_OP_TRUE == stConigInfo.bitOpIpv4PdnInfo)
        || (IMSA_OP_TRUE == stConigInfo.bitOpIpv6PdnInfo))
    {
        pstControlManager = IMSA_GetControlManagerAddress();
        stConigInfo.bitOpSockPortInfo = IMSA_OP_TRUE;
        stConigInfo.stSockPortInfo.usSockMinPort
                = pstControlManager->stImsaConfigPara.stImsPortConfig.usImsMinPort;
        stConigInfo.stSockPortInfo.usSockMaxPort
                = pstControlManager->stImsaConfigPara.stImsPortConfig.usImsMaxPort;

        ulRslt = IMSA_CONN_PdnInfoNicConfig(&stConigInfo);
        if (IMS_NIC_SUCC != ulRslt)
        {
            IMSA_ERR_LOG1("IMS_NIC_PdnInfoConfig failed,result:", ulRslt);
            TLPS_PRINT2LAYER_ERROR1(IMSA_CONN_ConfigPdpInfo2Bsp_ENUM, IMSA_CALL_API_ERROR, ulRslt);
        }
    }
}

/*****************************************************************************
 Function Name  : IMSA_CONN_SaveSipSignalPdpInfo
 Description    : IMSA CONN模块存储SIP信令承载信息
 Input          : pstPdpInfo---------------------PDP上下文指针
                  pstPdpActivateCnf--------------ACTIVATE CNF事件指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-25  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_SaveSipSignalPdpInfo
(
    IMSA_PDP_CNTXT_INFO_STRU                   *pstPdpInfo,
    const TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU    *pstPdpActivateCnf
)
{
    IMSA_CONTROL_MANAGER_STRU      *pstControlManager;
    pstControlManager               = IMSA_GetControlManagerAddress();

    pstPdpInfo->ucPdpId             = pstPdpActivateCnf->ucRabId;
    pstPdpInfo->enPdpState          = IMSA_PDP_STATE_ACTIVE;
    if (IMSA_OP_TRUE == pstPdpActivateCnf->bitOpLinkdRabId)
    {
        pstPdpInfo->enPdpType = IMSA_PDP_TYPE_DEDICATED;
    }
    else if ((IMSA_OP_TRUE == pstPdpActivateCnf->bitOpEmergencyInd) && (TAF_PDP_FOR_EMC == pstPdpActivateCnf->enEmergencyInd))
    {
        pstPdpInfo->enPdpType = IMSA_PDP_TYPE_EMERGENCY;
    }
    else
    {
        pstPdpInfo->enPdpType = IMSA_PDP_TYPE_DEFAULT;
    }
    pstPdpInfo->ucCid               = pstPdpActivateCnf->ucCid;

    /* 存储IP地址 */
    pstPdpInfo->bitOpPdpAddr        = pstPdpActivateCnf->bitOpPdpAddr;
    IMSA_MEM_CPY_S(                 &pstPdpInfo->stPdpAddr,
                                    sizeof(IMSA_IP_ADDRESS_STRU),
                                    &pstPdpActivateCnf->stPdpAddr,
                                    sizeof(IMSA_IP_ADDRESS_STRU));

    switch(pstControlManager->stPcscfDiscoveryPolicyInfo.enPcscfDiscoverPolicy)
    {
    case IMSA_PCSCF_DISCOVERY_POLICY_PCO:

        /* 通过PCO获取IPV4 P-CSCF */
        pstPdpInfo->stPdpIpv4Pcscf.bitOpPrimPcscfAddr = pstPdpActivateCnf->stPcscf.bitOpPrimPcscfAddr;
        pstPdpInfo->stPdpIpv4Pcscf.bitOpSecPcscfAddr = pstPdpActivateCnf->stPcscf.bitOpSecPcscfAddr;
        pstPdpInfo->stPdpIpv4Pcscf.bitOpThiPcscfAddr = pstPdpActivateCnf->stPcscf.bitOpThiPcscfAddr;

        IMSA_MEM_CPY_S(                 &pstPdpInfo->stPdpIpv4Pcscf.aucPrimPcscfAddr[0],
                                        IMSA_IPV4_ADDR_LEN,
                                        &pstPdpActivateCnf->stPcscf.aucPrimPcscfAddr[0],
                                        TAF_IPV4_ADDR_LEN);

        IMSA_MEM_CPY_S(                 &pstPdpInfo->stPdpIpv4Pcscf.aucSecPcscfAddr[0],
                                        IMSA_IPV4_ADDR_LEN,
                                        &pstPdpActivateCnf->stPcscf.aucSecPcscfAddr[0],
                                        TAF_IPV4_ADDR_LEN);

        IMSA_MEM_CPY_S(                 &pstPdpInfo->stPdpIpv4Pcscf.aucThiPcscfAddr[0],
                                        IMSA_IPV4_ADDR_LEN,
                                        &pstPdpActivateCnf->stPcscf.aucThiPcscfAddr[0],
                                        TAF_IPV4_ADDR_LEN);

        /* 通过PCO获取IPV6 P-CSCF */
        pstPdpInfo->stPdpIpv6Pcscf.bitOpPrimPcscfAddr = pstPdpActivateCnf->stIpv6Pcscf.bitOpPrimPcscfAddr;
        pstPdpInfo->stPdpIpv6Pcscf.bitOpSecPcscfAddr = pstPdpActivateCnf->stIpv6Pcscf.bitOpSecPcscfAddr;
        pstPdpInfo->stPdpIpv6Pcscf.bitOpThiPcscfAddr = pstPdpActivateCnf->stIpv6Pcscf.bitOpThiPcscfAddr;

        IMSA_MEM_CPY_S(                 &pstPdpInfo->stPdpIpv6Pcscf.aucPrimPcscfAddr[0],
                                        IMSA_IPV6_ADDR_LEN,
                                        &pstPdpActivateCnf->stIpv6Pcscf.aucPrimPcscfAddr[0],
                                        TAF_IPV6_ADDR_LEN);

        IMSA_MEM_CPY_S(                 &pstPdpInfo->stPdpIpv6Pcscf.aucSecPcscfAddr[0],
                                        IMSA_IPV6_ADDR_LEN,
                                        &pstPdpActivateCnf->stIpv6Pcscf.aucSecPcscfAddr[0],
                                        TAF_IPV6_ADDR_LEN);

        IMSA_MEM_CPY_S(                 &pstPdpInfo->stPdpIpv6Pcscf.aucThiPcscfAddr[0],
                                        IMSA_IPV6_ADDR_LEN,
                                        &pstPdpActivateCnf->stIpv6Pcscf.aucThiPcscfAddr[0],
                                        TAF_IPV6_ADDR_LEN);

        IMSA_INFO_LOG("IMSA_CONN_SaveSipSignalPdpInfo: IMSA_PCSCF_DISCOVERY_POLICY_PCO!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_SaveSipSignalPdpInfo_ENUM, 1);
        break;
    case IMSA_PCSCF_DISCOVERY_POLICY_NV:

        /* 通过NV配置获取IPV4 P-CSCF */
        pstPdpInfo->stPdpIpv4Pcscf.bitOpPrimPcscfAddr = pstControlManager->stPcscfDiscoveryPolicyInfo.stIpv4Pcscf.bitOpPrimPcscfAddr;
        pstPdpInfo->stPdpIpv4Pcscf.bitOpSecPcscfAddr = pstControlManager->stPcscfDiscoveryPolicyInfo.stIpv4Pcscf.bitOpSecPcscfAddr;


        IMSA_MEM_CPY_S(                 &pstPdpInfo->stPdpIpv4Pcscf.aucPrimPcscfAddr[0],
                                        IMSA_IPV4_ADDR_LEN,
                                        &pstControlManager->stPcscfDiscoveryPolicyInfo.stIpv4Pcscf.aucPrimPcscfAddr[0],
                                        TAF_IPV4_ADDR_LEN);

        IMSA_MEM_CPY_S(                 &pstPdpInfo->stPdpIpv4Pcscf.aucSecPcscfAddr[0],
                                        IMSA_IPV4_ADDR_LEN,
                                        &pstControlManager->stPcscfDiscoveryPolicyInfo.stIpv4Pcscf.aucSecPcscfAddr[0],
                                        TAF_IPV4_ADDR_LEN);

        /* 通过NV配置获取IPV6 P-CSCF */
        pstPdpInfo->stPdpIpv6Pcscf.bitOpPrimPcscfAddr = pstControlManager->stPcscfDiscoveryPolicyInfo.stIpv6Pcscf.bitOpPrimPcscfAddr;
        pstPdpInfo->stPdpIpv6Pcscf.bitOpSecPcscfAddr = pstControlManager->stPcscfDiscoveryPolicyInfo.stIpv6Pcscf.bitOpSecPcscfAddr;

        IMSA_MEM_CPY_S(                 &pstPdpInfo->stPdpIpv6Pcscf.aucPrimPcscfAddr[0],
                                        IMSA_IPV6_ADDR_LEN,
                                        &pstControlManager->stPcscfDiscoveryPolicyInfo.stIpv6Pcscf.aucPrimPcscfAddr[0],
                                        TAF_IPV6_ADDR_LEN);

        IMSA_MEM_CPY_S(                 &pstPdpInfo->stPdpIpv6Pcscf.aucSecPcscfAddr[0],
                                        IMSA_IPV6_ADDR_LEN,
                                        &pstControlManager->stPcscfDiscoveryPolicyInfo.stIpv6Pcscf.aucSecPcscfAddr[0],
                                        TAF_IPV6_ADDR_LEN);

        IMSA_INFO_LOG("IMSA_CONN_SaveSipSignalPdpInfo: IMSA_PCSCF_DISCOVERY_POLICY_NV!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_SaveSipSignalPdpInfo_ENUM, 2);
        break;
    default:
        IMSA_INFO_LOG("IMSA_CONN_SaveSipSignalPdpInfo:P-CSCF policy error!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_SaveSipSignalPdpInfo_ENUM, LNAS_ERROR);
        break;
    }

    /* 存储IPV4 DNS */
    IMSA_MEM_CPY_S(                 &pstPdpInfo->stPdpIpv4Dns,
                                    sizeof(IMSA_PDP_IPV4_DNS_STRU),
                                    &pstPdpActivateCnf->stDns,
                                    sizeof(IMSA_PDP_IPV4_DNS_STRU));

    /* 存储IPV6 DNS */
    IMSA_MEM_CPY_S(                 &pstPdpInfo->stPdpIpv6Dns,
                                    sizeof(IMSA_PDP_IPV6_DNS_STRU),
                                    &pstPdpActivateCnf->stIpv6Dns,
                                    sizeof(IMSA_PDP_IPV6_DNS_STRU));

    /* 存储EPS QOS */
    IMSA_MEM_CPY_S(                 &pstPdpInfo->stEpsQos,
                                    sizeof(IMSA_PDP_EPS_QOS_STRU),
                                    &pstPdpActivateCnf->stEpsQos,
                                    sizeof(IMSA_PDP_EPS_QOS_STRU));

}

/*****************************************************************************
 Function Name  : IMSA_CONN_SaveMediaPdpInfoWithSamePdpId
 Description    : IMSA CONN模块存储具有相同PdpId的SIP媒体承载信息
 Input          : enConnType---------------------连接类型
                  pstPdpActivateInd--------------ACTIVATE IND事件指针
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.xiongxianghui 00253310      2016-01-16  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_SaveMediaPdpInfoWithSamePdpId
(
    IMSA_CONN_TYPE_ENUM_UINT32                  enConnType,
    const TAF_PS_CALL_PDP_ACTIVATE_IND_STRU    *pstPdpActivateInd
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn       = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn          = VOS_NULL_PTR;
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpInfo          = VOS_NULL_PTR;
    VOS_UINT32                         i                    = IMSA_NULL;

    IMSA_INFO_LOG("IMSA_CONN_SaveMediaPdpInfoWithSamePdpId is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_SaveMediaPdpInfoWithSamePdpId_ENUM, LNAS_ENTRY);

    pstNormalConn                   = IMSA_CONN_GetNormalConnAddr();
    pstEmcConn                      = IMSA_CONN_GetEmcConnAddr();

    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        for (i = 0; i < pstNormalConn->ulSipMediaPdpNum; i++)
        {
            if ((IMSA_PDP_STATE_ACTIVE == pstNormalConn->astSipMediaPdpArray[i].enPdpState)
                && (pstNormalConn->astSipMediaPdpArray[i].ucPdpId == pstPdpActivateInd->ucRabId))
            {
                pstPdpInfo                  = &pstNormalConn->astSipMediaPdpArray[i];

                pstPdpInfo->ucPdpId             = pstPdpActivateInd->ucRabId;
                pstPdpInfo->enPdpState          = IMSA_PDP_STATE_ACTIVE;
                pstPdpInfo->enPdpType           = IMSA_PDP_TYPE_DEDICATED;
                pstPdpInfo->ucCid               = pstPdpActivateInd->ucCid;

                /* 存储关联的信令承载号 */
                pstPdpInfo->bitOpLinkedPdpId    = pstPdpActivateInd->bitOpLinkdRabId;
                pstPdpInfo->ucLinkedPdpId       = pstPdpActivateInd->ucLinkdRabId;

                pstPdpInfo->bitOpTft            = pstPdpActivateInd->bitOpTft;
                IMSA_MEM_CPY_S(                 &pstPdpInfo->stTft,
                                                sizeof(IMSA_PDP_TFT_INFO_STRU),
                                                &pstPdpActivateInd->stTft,
                                                sizeof(IMSA_PDP_TFT_INFO_STRU));

                if (IMSA_MAX_PF_NUM < pstPdpActivateInd->stTft.ulPfNum)
                {
                    pstPdpInfo->stTft.ulPfNum = IMSA_MAX_PF_NUM;
                }

                /* 存储EPS QOS */
                IMSA_MEM_CPY_S(                 &pstPdpInfo->stEpsQos,
                                                sizeof(IMSA_PDP_EPS_QOS_STRU),
                                                &pstPdpActivateInd->stEpsQos,
                                                sizeof(IMSA_PDP_EPS_QOS_STRU));

                IMSA_INFO_LOG("IMSA_CONN_SaveMediaPdpInfoWithSamePdpId:get NormalConn MediaInfo by same pdpid!");
                TLPS_PRINT2LAYER_INFO(IMSA_CONN_SaveMediaPdpInfoWithSamePdpId_ENUM, 1);

                return IMSA_SUCC;
            }
        }

        return IMSA_FAIL;
    }

    for (i = 0; i < pstEmcConn->ulSipMediaPdpNum; i++)
    {
        if ((IMSA_PDP_STATE_ACTIVE == pstEmcConn->astSipMediaPdpArray[i].enPdpState)
            && (pstEmcConn->astSipMediaPdpArray[i].ucPdpId == pstPdpActivateInd->ucRabId))
        {
            pstPdpInfo                  = &pstEmcConn->astSipMediaPdpArray[i];

            pstPdpInfo->ucPdpId             = pstPdpActivateInd->ucRabId;
            pstPdpInfo->enPdpState          = IMSA_PDP_STATE_ACTIVE;
            pstPdpInfo->enPdpType           = IMSA_PDP_TYPE_DEDICATED;
            pstPdpInfo->ucCid               = pstPdpActivateInd->ucCid;

            /* 存储关联的信令承载号 */
            pstPdpInfo->bitOpLinkedPdpId    = pstPdpActivateInd->bitOpLinkdRabId;
            pstPdpInfo->ucLinkedPdpId       = pstPdpActivateInd->ucLinkdRabId;

            pstPdpInfo->bitOpTft            = pstPdpActivateInd->bitOpTft;
            IMSA_MEM_CPY_S(                 &pstPdpInfo->stTft,
                                            sizeof(IMSA_PDP_TFT_INFO_STRU),
                                            &pstPdpActivateInd->stTft,
                                            sizeof(IMSA_PDP_TFT_INFO_STRU));

            if (IMSA_MAX_PF_NUM < pstPdpActivateInd->stTft.ulPfNum)
            {
                pstPdpInfo->stTft.ulPfNum = IMSA_MAX_PF_NUM;
            }

            /* 存储EPS QOS */
            IMSA_MEM_CPY_S(                 &pstPdpInfo->stEpsQos,
                                            sizeof(IMSA_PDP_EPS_QOS_STRU),
                                            &pstPdpActivateInd->stEpsQos,
                                            sizeof(IMSA_PDP_EPS_QOS_STRU));

            IMSA_INFO_LOG("IMSA_CONN_SaveMediaPdpInfoWithSamePdpId:get EmcConn MediaInfo by same pdpid!");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_SaveMediaPdpInfoWithSamePdpId_ENUM, 2);

            return IMSA_SUCC;
        }
    }

    return IMSA_FAIL;
}


/*****************************************************************************
 Function Name  : IMSA_CONN_SaveMediaPdpInfoWithSameQci
 Description    : IMSA CONN模块存储具有相同QCI的SIP媒体承载信息
 Input          : enConnType---------------------连接类型
                  pstPdpActivateInd--------------ACTIVATE IND事件指针
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.xiongxianghui 00253310      2016-01-16  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_SaveMediaPdpInfoWithSameQci
(
    IMSA_CONN_TYPE_ENUM_UINT32                  enConnType,
    const TAF_PS_CALL_PDP_ACTIVATE_IND_STRU    *pstPdpActivateInd
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn       = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn          = VOS_NULL_PTR;
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpInfo          = VOS_NULL_PTR;
    VOS_UINT32                         i                    = IMSA_NULL;

    IMSA_INFO_LOG("IMSA_CONN_SaveMediaPdpInfoWithSameQci is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_SaveMediaPdpInfoWithSameQci_ENUM, LNAS_ENTRY);

    pstNormalConn                   = IMSA_CONN_GetNormalConnAddr();
    pstEmcConn                      = IMSA_CONN_GetEmcConnAddr();

    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        for (i = 0; i < pstNormalConn->ulSipMediaPdpNum; i++)
        {
            if ((IMSA_PDP_STATE_ACTIVE == pstNormalConn->astSipMediaPdpArray[i].enPdpState)
                && (pstNormalConn->astSipMediaPdpArray[i].stEpsQos.ucQCI == pstPdpActivateInd->stEpsQos.ucQCI))
            {
                pstPdpInfo                  = &pstNormalConn->astSipMediaPdpArray[i];

                pstPdpInfo->ucPdpId             = pstPdpActivateInd->ucRabId;
                pstPdpInfo->enPdpState          = IMSA_PDP_STATE_ACTIVE;
                pstPdpInfo->enPdpType           = IMSA_PDP_TYPE_DEDICATED;
                pstPdpInfo->ucCid               = pstPdpActivateInd->ucCid;

                /* 存储关联的信令承载号 */
                pstPdpInfo->bitOpLinkedPdpId    = pstPdpActivateInd->bitOpLinkdRabId;
                pstPdpInfo->ucLinkedPdpId       = pstPdpActivateInd->ucLinkdRabId;

                pstPdpInfo->bitOpTft            = pstPdpActivateInd->bitOpTft;
                IMSA_MEM_CPY_S(                 &pstPdpInfo->stTft,
                                                sizeof(IMSA_PDP_TFT_INFO_STRU),
                                                &pstPdpActivateInd->stTft,
                                                sizeof(IMSA_PDP_TFT_INFO_STRU));

                if (IMSA_MAX_PF_NUM < pstPdpActivateInd->stTft.ulPfNum)
                {
                    pstPdpInfo->stTft.ulPfNum = IMSA_MAX_PF_NUM;
                }

                /* 存储EPS QOS */
                IMSA_MEM_CPY_S(                 &pstPdpInfo->stEpsQos,
                                                sizeof(IMSA_PDP_EPS_QOS_STRU),
                                                &pstPdpActivateInd->stEpsQos,
                                                sizeof(IMSA_PDP_EPS_QOS_STRU));

                IMSA_INFO_LOG("IMSA_CONN_SaveMediaPdpInfoWithSameQci:get NormalConn MediaInfo by same Qci!");
                TLPS_PRINT2LAYER_INFO(IMSA_CONN_SaveMediaPdpInfoWithSameQci_ENUM, 1);

                return IMSA_SUCC;
            }
        }

        return IMSA_FAIL;
    }

    for (i = 0; i < pstEmcConn->ulSipMediaPdpNum; i++)
    {
        if ((IMSA_PDP_STATE_ACTIVE == pstEmcConn->astSipMediaPdpArray[i].enPdpState)
            && (pstEmcConn->astSipMediaPdpArray[i].stEpsQos.ucQCI == pstPdpActivateInd->stEpsQos.ucQCI))
        {
            pstPdpInfo                  = &pstEmcConn->astSipMediaPdpArray[i];

            pstPdpInfo->ucPdpId             = pstPdpActivateInd->ucRabId;
            pstPdpInfo->enPdpState          = IMSA_PDP_STATE_ACTIVE;
            pstPdpInfo->enPdpType           = IMSA_PDP_TYPE_DEDICATED;
            pstPdpInfo->ucCid               = pstPdpActivateInd->ucCid;

            /* 存储关联的信令承载号 */
            pstPdpInfo->bitOpLinkedPdpId    = pstPdpActivateInd->bitOpLinkdRabId;
            pstPdpInfo->ucLinkedPdpId       = pstPdpActivateInd->ucLinkdRabId;

            pstPdpInfo->bitOpTft            = pstPdpActivateInd->bitOpTft;
            IMSA_MEM_CPY_S(                 &pstPdpInfo->stTft,
                                            sizeof(IMSA_PDP_TFT_INFO_STRU),
                                            &pstPdpActivateInd->stTft,
                                            sizeof(IMSA_PDP_TFT_INFO_STRU));

            if (IMSA_MAX_PF_NUM < pstPdpActivateInd->stTft.ulPfNum)
            {
                pstPdpInfo->stTft.ulPfNum = IMSA_MAX_PF_NUM;
            }

            /* 存储EPS QOS */
            IMSA_MEM_CPY_S(                 &pstPdpInfo->stEpsQos,
                                            sizeof(IMSA_PDP_EPS_QOS_STRU),
                                            &pstPdpActivateInd->stEpsQos,
                                            sizeof(IMSA_PDP_EPS_QOS_STRU));

            IMSA_INFO_LOG("IMSA_CONN_SaveMediaPdpInfoWithSameQci:get EmcConn MediaInfo by same Qci!");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_SaveMediaPdpInfoWithSameQci_ENUM, 2);

            return IMSA_SUCC;
        }
    }

    return IMSA_FAIL;
}



/*****************************************************************************
 Function Name  : IMSA_CONN_SaveSipMediaPdpInfo
 Description    : IMSA CONN模块存储SIP媒体承载信息
 Input          : pstPdpActivateInd--------------ACTIVATE IND事件指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-29  Draft Enact
      2.lihong 00150010      2013-12-06  Modify:emc dedicated
*****************************************************************************/
VOS_VOID IMSA_CONN_SaveSipMediaPdpInfo
(
    IMSA_CONN_TYPE_ENUM_UINT32                  enConnType,
    const TAF_PS_CALL_PDP_ACTIVATE_IND_STRU    *pstPdpActivateInd
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn       = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn          = VOS_NULL_PTR;
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpInfo          = VOS_NULL_PTR;

    pstNormalConn                   = IMSA_CONN_GetNormalConnAddr();
    pstEmcConn                      = IMSA_CONN_GetEmcConnAddr();

    /* 判断承载ID是否相同，如果相同，直接替换 */
    if (IMSA_SUCC == IMSA_CONN_SaveMediaPdpInfoWithSamePdpId(enConnType, pstPdpActivateInd))
    {
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_SaveSipMediaPdpInfo_ENUM, 1);
        return;
    }

    /* 如果普通媒体承载个数达到最大，则替换相同QCI的媒体承载 */
    if((IMSA_CONN_TYPE_NORMAL == enConnType)
       &&(IMSA_CONN_MAX_NORMAL_SIP_MEDIA_PDP_NUM <= pstNormalConn->ulSipMediaPdpNum))
    {
        IMSA_CONN_SaveMediaPdpInfoWithSameQci(enConnType, pstPdpActivateInd);
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_SaveSipMediaPdpInfo_ENUM, 2);

        return;
    }

    /* 如果紧急媒体承载个数达到最大，则替换相同QCI的媒体承载 */
    if((IMSA_CONN_TYPE_EMC == enConnType)
       &&(IMSA_CONN_MAX_EMC_SIP_MEDIA_PDP_NUM <= pstEmcConn->ulSipMediaPdpNum))
    {
        IMSA_CONN_SaveMediaPdpInfoWithSameQci(enConnType, pstPdpActivateInd);
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_SaveSipMediaPdpInfo_ENUM, 3);

        return;
    }

    IMSA_INFO_LOG("IMSA_CONN_SaveSipMediaPdpInfo_ENUM is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_SaveSipMediaPdpInfo_ENUM, LNAS_ENTRY);


    if (IMSA_CONN_TYPE_NORMAL       == enConnType)
    {
        pstPdpInfo                  = &pstNormalConn->astSipMediaPdpArray[pstNormalConn->ulSipMediaPdpNum];
        pstNormalConn->ulSipMediaPdpNum++;
    }
    else
    {
        pstPdpInfo                  = &pstEmcConn->astSipMediaPdpArray[pstEmcConn->ulSipMediaPdpNum];
        pstEmcConn->ulSipMediaPdpNum++;
    }

    pstPdpInfo->ucPdpId             = pstPdpActivateInd->ucRabId;
    pstPdpInfo->enPdpState          = IMSA_PDP_STATE_ACTIVE;
    pstPdpInfo->enPdpType           = IMSA_PDP_TYPE_DEDICATED;
    pstPdpInfo->ucCid               = pstPdpActivateInd->ucCid;

    /* 存储关联的信令承载号 */
    pstPdpInfo->bitOpLinkedPdpId    = pstPdpActivateInd->bitOpLinkdRabId;
    pstPdpInfo->ucLinkedPdpId       = pstPdpActivateInd->ucLinkdRabId;

    pstPdpInfo->bitOpTft            = pstPdpActivateInd->bitOpTft;
    IMSA_MEM_CPY_S(                 &pstPdpInfo->stTft,
                                    sizeof(IMSA_PDP_TFT_INFO_STRU),
                                    &pstPdpActivateInd->stTft,
                                    sizeof(IMSA_PDP_TFT_INFO_STRU));

    if (IMSA_MAX_PF_NUM < pstPdpActivateInd->stTft.ulPfNum)
    {
        pstPdpInfo->stTft.ulPfNum = IMSA_MAX_PF_NUM;
    }

    /* 存储EPS QOS */
    IMSA_MEM_CPY_S(                 &pstPdpInfo->stEpsQos,
                                    sizeof(IMSA_PDP_EPS_QOS_STRU),
                                    &pstPdpActivateInd->stEpsQos,
                                    sizeof(IMSA_PDP_EPS_QOS_STRU));

}

/*****************************************************************************
 Function Name  : IMSA_CONN_ModifySipPdpInfo
 Description    : IMSA CONN模块修改SIP承载信息
 Input          : enSipPdpType-----------------SIP承载类型
                  pstPdpModifyInd--------------MODIFY IND事件指针
 Output         : pstPdpInfo-------------------PDP上下文指针
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_ModifySipPdpInfo
(
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32          enSipPdpType,
    IMSA_PDP_CNTXT_INFO_STRU                   *pstPdpInfo,
    const TAF_PS_CALL_PDP_MODIFY_IND_STRU      *pstPdpModifyInd
)
{

    /* 存储EPS QOS */
    IMSA_MEM_CPY_S(     &pstPdpInfo->stEpsQos,
                        sizeof(IMSA_PDP_EPS_QOS_STRU),
                        &pstPdpModifyInd->stEpsQos,
                        sizeof(IMSA_PDP_EPS_QOS_STRU));
    if (IMSA_CONN_SIP_PDP_TYPE_SIGNAL == enSipPdpType)
    {
        /* 存储IPV4 P-CSCF */
        IMSA_MEM_CPY_S( &pstPdpInfo->stPdpIpv4Pcscf,
                        sizeof(IMSA_PDP_IPV4_PCSCF_STRU),
                        &pstPdpModifyInd->stPcscf,
                        sizeof(IMSA_PDP_IPV4_PCSCF_STRU));

        /* 存储IPV4 DNS */
        IMSA_MEM_CPY_S( &pstPdpInfo->stPdpIpv4Dns,
                        sizeof(IMSA_PDP_IPV4_DNS_STRU),
                        &pstPdpModifyInd->stDns,
                        sizeof(IMSA_PDP_IPV4_DNS_STRU));

        /* 存储IPV6 P-CSCF */
        IMSA_MEM_CPY_S( &pstPdpInfo->stPdpIpv6Pcscf,
                        sizeof(IMSA_PDP_IPV6_PCSCF_STRU),
                        &pstPdpModifyInd->stIpv6Pcscf,
                        sizeof(IMSA_PDP_IPV6_PCSCF_STRU));

        /* 存储IPV6 DNS */
        IMSA_MEM_CPY_S( &pstPdpInfo->stPdpIpv6Dns,
                        sizeof(IMSA_PDP_IPV6_DNS_STRU),
                        &pstPdpModifyInd->stIpv6Dns,
                        sizeof(IMSA_PDP_IPV6_DNS_STRU));
    }
    else if(IMSA_CONN_SIP_PDP_TYPE_MEDIA == enSipPdpType)/* 媒体承载的情况下，更新TFT信息 */
    {
        pstPdpInfo->bitOpTft            = pstPdpModifyInd->bitOpTft;
        IMSA_MEM_CPY_S(                 &pstPdpInfo->stTft,
                                        sizeof(IMSA_PDP_TFT_INFO_STRU),
                                        &pstPdpModifyInd->stTft,
                                        sizeof(IMSA_PDP_TFT_INFO_STRU));

        if (IMSA_MAX_PF_NUM < pstPdpModifyInd->stTft.ulPfNum)
        {
            pstPdpInfo->stTft.ulPfNum = IMSA_MAX_PF_NUM;
        }
    }
    else
    {
    }
}
/*****************************************************************************
 Function Name  : IMSA_CONN_IsImsBearNeedSetToCds
 Description    : IMSA CONN模块判断当前激活的承载是否需要配置给CDS
 Input          : pEvtInfo--------------事件信息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2014-06-21  Draft Enact
      2.wangchen 00209181   2015-03-18  Modify:volte
*****************************************************************************/
VOS_UINT32 IMSA_CONN_IsVoiceMediaPdpType
(
    IMSA_PDP_TFT_INFO_STRU              *pstTft,
    VOS_UINT8                           ucQCI
)
{
    VOS_UINT32                          ulPfNum             = IMSA_NULL;
    VOS_UINT16                          usImsMinPort        = IMSA_NULL;
    VOS_UINT16                          usImsMaxPort        = IMSA_NULL;
    IMSA_CONTROL_MANAGER_STRU          *pstControlManager   = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CONN_IsVoiceMediaPdpType is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_IsVoiceMediaPdpType_ENUM, LNAS_ENTRY);

    if (VOS_NULL_PTR == pstTft)
    {
        return IMSA_TRUE;
    }

    /*分配空间并检验分配是否成功*/
    pstControlManager = IMSA_GetControlManagerAddress();
    usImsMinPort = pstControlManager->stImsaConfigPara.stImsPortConfig.usImsMinPort;
    usImsMaxPort = pstControlManager->stImsaConfigPara.stImsPortConfig.usImsMaxPort;

    /* 视频包需要走A核，所以不需要配置给CDS；通过TFT的端口信息来区分承载是否是视频承载 */
    /* 如果承载有多个过滤器，仅需要判断一个本地端口就可以，网侧不会给一个过滤器分配C核端口，
    另一个分配A核端口 */
    if (0 == pstTft->ulPfNum)
    {
        return IMSA_TRUE;
    }
    for (ulPfNum = 0; ulPfNum < pstTft->ulPfNum; ulPfNum ++ )
    {
        if ((IMSA_OP_TRUE == pstTft->astTftInfo[ulPfNum].bitOpSingleLocalPort) &&
            (pstTft->astTftInfo[ulPfNum].usSingleLcPort >= usImsMinPort) &&
            (pstTft->astTftInfo[ulPfNum].usSingleLcPort <= usImsMaxPort))
        {
            return IMSA_TRUE;
        }

        if ((IMSA_OP_TRUE == pstTft->astTftInfo[ulPfNum].bitOpLocalPortRange) &&
            (pstTft->astTftInfo[ulPfNum].usLcPortLowLimit >= usImsMinPort) &&
            (pstTft->astTftInfo[ulPfNum].usLcPortHighLimit <= usImsMaxPort))
        {
            return IMSA_TRUE;
        }

        /* 如果不携带本地端口号，也不携带本地端口号范围，则通过QCI判断当前是不是语音承载 */
        if (IMSA_VOICE_QCI == ucQCI)
        {
            return IMSA_TRUE;
        }
    }

    return IMSA_FALSE;
}


/*****************************************************************************
 Function Name  : IMSA_CONN_SaveIpv6Info
 Description    : IMSA CONN模块存储APS上报的IPV6信息
 Input          : pstIpv6InfoInd-----------------IPV6 INFO IND事件指针
 Output         : pstPdpInfo---------------------PDP上下文指针
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_SaveIpv6Info
(
    IMSA_PDP_CNTXT_INFO_STRU                   *pstPdpInfo,
    const TAF_PS_IPV6_INFO_IND_STRU            *pstIpv6InfoInd
)
{
    /* 23.401要求3GPP的IPV6前缀必须是64位
       IPv6 Stateless Address autoconfiguration specified in RFC 4862 [18] is
       the basic mechanism to allocate /64 IPv6 prefix to the UE. */

    /* 29.061要求网侧分配的IPV6前缀是无限长的，因此无需考虑IPV6前缀的有效期
       AdvValidLifetime
           Shall have a value giving Prefixes infinite lifetime, i.e. 0xFFFFFFFF.
           The assigned prefix remains Preferred until PDP Context/Bearer Deactivation.
       AdvPreferredLifetime
           Shall have a value giving Prefixes infinite lifetime, i.e. 0xFFFFFFFF.
           The assigned prefix remains Preferred until PDP Context/Bearer Deactivation.
       */
    IMSA_MEM_CPY_S( pstPdpInfo->stPdpAddr.aucIpV6Addr,
                    IMSA_IPV6_PREFIX_LEN,
                    pstIpv6InfoInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                    IMSA_IPV6_PREFIX_LEN);
}

/*****************************************************************************
 Function Name  : IMSA_CONN_IsPdpIpv4InfoIncludeRegPara
 Description    : 判断IPV4类型承载是否包含注册信息
 Input          :
                  pcRegUeAddr---------------注册IP地址指针
                  pcRegPcscfAddr------------注册P-CSCF地址指针
                  pstPdpInfo----------------PDP上下文指针
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.wangchen 00209181    2015-03-21  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_IsPdpIpv4InfoIncludeRegPara
(
    VOS_CHAR                               *pcRegUeAddr,
    VOS_CHAR                               *pcRegPcscfAddr,
    const IMSA_PDP_CNTXT_INFO_STRU         *pstPdpInfo
)
{
    VOS_CHAR                            acPdpUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
    VOS_CHAR                            acPdpPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};

    IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                        pstPdpInfo->stPdpAddr.aucIpV4Addr,
                                        acPdpUeAddr);

    if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpPrimPcscfAddr)
    {
        IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                            pstPdpInfo->stPdpIpv4Pcscf.aucPrimPcscfAddr,
                                            acPdpPcscfAddr);

        /* 比较地址对 */
        if ((0 == VOS_StrCmp(pcRegUeAddr, acPdpUeAddr))
            && (0 == VOS_StrCmp(pcRegPcscfAddr, acPdpPcscfAddr)))
        {
            return IMSA_TRUE;
        }
    }

    if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpSecPcscfAddr)
    {
        IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                            pstPdpInfo->stPdpIpv4Pcscf.aucSecPcscfAddr,
                                            acPdpPcscfAddr);

        /* 比较地址对 */
        if ((0 == VOS_StrCmp(pcRegUeAddr, acPdpUeAddr))
            && (0 == VOS_StrCmp(pcRegPcscfAddr, acPdpPcscfAddr)))
        {
            return IMSA_TRUE;
        }
    }

    if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpThiPcscfAddr)
    {
        IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                            pstPdpInfo->stPdpIpv4Pcscf.aucThiPcscfAddr,
                                            acPdpPcscfAddr);

        /* 比较地址对 */
        if ((0 == VOS_StrCmp(pcRegUeAddr, acPdpUeAddr))
            && (0 == VOS_StrCmp(pcRegPcscfAddr, acPdpPcscfAddr)))
        {
            return IMSA_TRUE;
        }
    }

    return IMSA_FALSE;
}
/*****************************************************************************
 Function Name  : IMSA_CONN_IsPdpIpv6InfoIncludeRegPara
 Description    : 判断IPV6类型承载是否包含注册信息
 Input          :
                  pcRegUeAddr---------------注册IP地址指针
                  pcRegPcscfAddr------------注册P-CSCF地址指针
                  pstPdpInfo----------------PDP上下文指针
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.wangchen 00209181    2015-03-21  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_IsPdpIpv6InfoIncludeRegPara
(
    VOS_CHAR                               *pcRegUeAddr,
    VOS_CHAR                               *pcRegPcscfAddr,
    const IMSA_PDP_CNTXT_INFO_STRU         *pstPdpInfo
)
{
    VOS_CHAR                            acPdpUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
    VOS_CHAR                            acPdpPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};

    IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                            pstPdpInfo->stPdpAddr.aucIpV6Addr,
                                            acPdpUeAddr);

    if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpPrimPcscfAddr)
    {
        IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                            pstPdpInfo->stPdpIpv6Pcscf.aucPrimPcscfAddr,
                                            acPdpPcscfAddr);

        /* 比较地址对 */
        if ((0 == VOS_StrCmp(pcRegUeAddr, acPdpUeAddr))
            && (0 == VOS_StrCmp(pcRegPcscfAddr, acPdpPcscfAddr)))
        {
            return IMSA_TRUE;
        }
    }

    if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpSecPcscfAddr)
    {
        IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                            pstPdpInfo->stPdpIpv6Pcscf.aucSecPcscfAddr,
                                            acPdpPcscfAddr);

        /* 比较地址对 */
        if ((0 == VOS_StrCmp(pcRegUeAddr, acPdpUeAddr))
            && (0 == VOS_StrCmp(pcRegPcscfAddr, acPdpPcscfAddr)))
        {
            return IMSA_TRUE;
        }
    }
    if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpThiPcscfAddr)
    {
        IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                            pstPdpInfo->stPdpIpv6Pcscf.aucThiPcscfAddr,
                                            acPdpPcscfAddr);

        /* 比较地址对 */
        if ((0 == VOS_StrCmp(pcRegUeAddr, acPdpUeAddr))
            && (0 == VOS_StrCmp(pcRegPcscfAddr, acPdpPcscfAddr)))
        {
            return IMSA_TRUE;
        }
    }

    return IMSA_FALSE;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_IsPdpIpvxInfoIncludeRegPara
 Description    : 判断IPV4类型承载或者IPV6承载类型是否包含注册信息
 Input          : enIpType------------------ip类型
                  pcRegUeAddr---------------注册IP地址指针
                  pcRegPcscfAddr------------注册P-CSCF地址指针
                  pstPdpInfo----------------PDP上下文指针
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-17  Draft Enact
      2.wangchen 00209181    2015-03-21  Modify:volte
*****************************************************************************/
VOS_UINT32 IMSA_CONN_IsPdpIpvxInfoIncludeRegPara
(
    IMSA_IP_TYPE_ENUM_UINT8                 enIpType,
    VOS_CHAR                               *pcRegUeAddr,
    VOS_CHAR                               *pcRegPcscfAddr,
    const IMSA_PDP_CNTXT_INFO_STRU         *pstPdpInfo
)
{
    VOS_UINT32                          ulResult = IMSA_FALSE;

    if (IMSA_IP_TYPE_IPV4 == enIpType)
    {
        ulResult = IMSA_CONN_IsPdpIpv4InfoIncludeRegPara(pcRegUeAddr, pcRegPcscfAddr, pstPdpInfo);
        return ulResult;
    }
    else
    {
        ulResult = IMSA_CONN_IsPdpIpv6InfoIncludeRegPara(pcRegUeAddr, pcRegPcscfAddr, pstPdpInfo);
        return ulResult;
    }

}


/*****************************************************************************
 Function Name  : IMSA_CONN_IsRegPara
 Description    : 判断是否是注册使用的参数
 Input          : enConnType----------------连接类型
                  pstPdpInfo----------------PDP上下文指针
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-17  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_IsPdpInfoIncludeRegPara
(
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    const IMSA_PDP_CNTXT_INFO_STRU         *pstPdpInfo
)
{
    VOS_CHAR                            acRegUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
    VOS_CHAR                            acRegPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
    VOS_UINT32                          ulRslt          = IMSA_FAIL;

    IMSA_IP_TYPE_ENUM_UINT8             enIpType = IMSA_IP_TYPE_BUTT;

    ulRslt = IMSA_RegGetRegedPara(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                    acRegUeAddr,
                                    acRegPcscfAddr,
                                    &enIpType);

    /* 如果未获取到注册上的参数，则直接返回不包含 */
    if (IMSA_FAIL == ulRslt)
    {
        return IMSA_FALSE;
    }

    if (IMSA_IP_TYPE_BUTT != enIpType)
    {
        if ((IMSA_IP_TYPE_IPV4V6 != pstPdpInfo->stPdpAddr.enIpType) && (enIpType != pstPdpInfo->stPdpAddr.enIpType))
        {
            return IMSA_FALSE;
        }
    }

    if ((IMSA_IP_TYPE_IPV4 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        if (IMSA_TRUE == IMSA_CONN_IsPdpIpvxInfoIncludeRegPara( IMSA_IP_TYPE_IPV4,
                                                                acRegUeAddr,
                                                                acRegPcscfAddr,
                                                                pstPdpInfo))
        {
            return IMSA_TRUE;
        }
    }

    if ((IMSA_IP_TYPE_IPV6 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        if (IMSA_TRUE == IMSA_CONN_IsPdpIpvxInfoIncludeRegPara( IMSA_IP_TYPE_IPV6,
                                                                acRegUeAddr,
                                                                acRegPcscfAddr,
                                                                pstPdpInfo))
        {
            return IMSA_TRUE;
        }
    }

    return IMSA_FALSE;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_DeleteEmcPdpInfo
 Description    : 删除紧急承载信息
 Input          : ucCid---------------------CID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2014-01-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_DeleteEmcPdpInfo
(
    VOS_UINT8                               ucCid,
    VOS_UINT8                               ucRabId
)
{
    IMSA_EMC_CONN_STRU                 *pstEmcConn      = VOS_NULL_PTR;
    VOS_UINT32                          i               = IMSA_NULL;

    pstEmcConn  = IMSA_CONN_GetEmcConnAddr();

    if ((IMSA_PDP_STATE_ACTIVE == pstEmcConn->stSipSignalPdp.enPdpState)
        &&((ucCid == pstEmcConn->stSipSignalPdp.ucCid)
        || (ucRabId == pstEmcConn->stSipSignalPdp.ucPdpId)))
    {
        if ((IMSA_IP_TYPE_IPV6 == pstEmcConn->stSipSignalPdp.stPdpAddr.enIpType) ||
            (IMSA_IP_TYPE_IPV4V6 == pstEmcConn->stSipSignalPdp.stPdpAddr.enIpType))
        {
            /* 停止等待IPV6参数定时器 */
            IMSA_CONN_StopTimer(IMSA_CONN_TYPE_EMC, TI_IMSA_WAIT_IPV6_INFO);
        }

        /* 调用REG模块删除IP地址和P-CSCF地址 */
        IMSA_CONN_DeletePdpInfo2Reg(IMSA_CONN_TYPE_EMC, &pstEmcConn->stSipSignalPdp);

        IMSA_MEM_SET_S(     &pstEmcConn->stSipSignalPdp,
                            sizeof(IMSA_PDP_CNTXT_INFO_STRU),
                            0x0,
                            sizeof(IMSA_PDP_CNTXT_INFO_STRU));

        /* 通知CDS下行过滤承载 */
        IMSA_CONN_SndCdsSetImsBearerReq();

        return ;
    }

    /* 查找普通媒体承载，并删除 */
    for (i = 0; i < pstEmcConn->ulSipMediaPdpNum; i++)
    {
        if ((IMSA_PDP_STATE_ACTIVE == pstEmcConn->astSipMediaPdpArray[i].enPdpState)
            &&((ucCid == pstEmcConn->astSipMediaPdpArray[i].ucCid)
            || (ucRabId == pstEmcConn->astSipMediaPdpArray[i].ucPdpId)))
        {
            if (i < (IMSA_CONN_MAX_EMC_SIP_MEDIA_PDP_NUM - 1))
            {
                IMSA_MEM_CPY_S( &pstEmcConn->astSipMediaPdpArray[i],
                                sizeof(IMSA_PDP_CNTXT_INFO_STRU)*((IMSA_CONN_MAX_EMC_SIP_MEDIA_PDP_NUM-1)-i),
                                &pstEmcConn->astSipMediaPdpArray[i+1],
                                sizeof(IMSA_PDP_CNTXT_INFO_STRU)*((IMSA_CONN_MAX_EMC_SIP_MEDIA_PDP_NUM-1)-i));
            }

            IMSA_MEM_SET_S(     &pstEmcConn->astSipMediaPdpArray[IMSA_CONN_MAX_EMC_SIP_MEDIA_PDP_NUM-1],
                                sizeof(IMSA_PDP_CNTXT_INFO_STRU),
                                0x0,
                                sizeof(IMSA_PDP_CNTXT_INFO_STRU));

            pstEmcConn->ulSipMediaPdpNum--;

            /* 通知CDS下行过滤承载 */
            IMSA_CONN_SndCdsSetImsBearerReq();

            return ;
        }
    }

    return ;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_DeletePdpInfo
 Description    : 删除承载信息
 Input          : enConnType----------------连接类型
                  ucCid---------------------CID
 Output         : pulRegParaInvalid---------注册参数失效标识指针,0表示失效，1表示有效
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-02  Draft Enact
      2.lihong 00150010      2013-12-06  Modify:Emc dedicated
*****************************************************************************/
VOS_VOID IMSA_CONN_DeletePdpInfo
(
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    VOS_UINT8                               ucCid,
    VOS_UINT8                               ucRabId,
    VOS_UINT32                             *pulRegParaValid
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    /* IMSA_EMC_CONN_STRU                 *pstEmcConn      = VOS_NULL_PTR; */
    VOS_UINT32                          i               = IMSA_NULL;

    *pulRegParaValid = IMSA_CONN_REG_PARA_VALID;

    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        IMSA_INFO_LOG("IMSA_CONN_DeletePdpInfo:delete emc pdp!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_DeletePdpInfo_ENUM, IMSA_EMERGENCY);

        IMSA_CONN_DeleteEmcPdpInfo(ucCid, ucRabId);

        return ;
    }

    pstNormalConn = IMSA_CONN_GetNormalConnAddr();

    /* 查找普通信令承载，并删除 */
    for (i = 0; i < pstNormalConn->ulSipSignalPdpNum; i++)
    {
        if ((IMSA_PDP_STATE_ACTIVE == pstNormalConn->astSipSignalPdpArray[i].enPdpState)
            &&((ucCid == pstNormalConn->astSipSignalPdpArray[i].ucCid)
            || (ucRabId == pstNormalConn->astSipSignalPdpArray[i].ucPdpId)))
        {
            if ((IMSA_IP_TYPE_IPV6 == pstNormalConn->astSipSignalPdpArray[i].stPdpAddr.enIpType) ||
                (IMSA_IP_TYPE_IPV4V6 == pstNormalConn->astSipSignalPdpArray[i].stPdpAddr.enIpType))
            {
                /* 停止等待IPV6参数定时器 */
                IMSA_CONN_StopTimer(IMSA_CONN_TYPE_NORMAL, TI_IMSA_WAIT_IPV6_INFO);
            }

            /* 识别注册参数是否失效 */
            if (IMSA_TRUE == IMSA_CONN_IsPdpInfoIncludeRegPara( IMSA_CONN_TYPE_NORMAL,
                                                                &pstNormalConn->astSipSignalPdpArray[i]))
            {
                *pulRegParaValid = IMSA_CONN_REG_PARA_INVALID;
            }

            /* 调用REG模块删除IP地址和P-CSCF地址 */
            IMSA_CONN_DeletePdpInfo2Reg(IMSA_CONN_TYPE_NORMAL, &pstNormalConn->astSipSignalPdpArray[i]);

            if (i < (IMSA_CONN_MAX_NORMAL_SIP_SIGNAL_PDP_NUM - 1))
            {
                IMSA_MEM_CPY_S( &pstNormalConn->astSipSignalPdpArray[i],
                                sizeof(IMSA_PDP_CNTXT_INFO_STRU)*((IMSA_CONN_MAX_NORMAL_SIP_SIGNAL_PDP_NUM-1)-i),
                                &pstNormalConn->astSipSignalPdpArray[i+1],
                                sizeof(IMSA_PDP_CNTXT_INFO_STRU)*((IMSA_CONN_MAX_NORMAL_SIP_SIGNAL_PDP_NUM-1)-i));
            }

            IMSA_MEM_SET_S( &pstNormalConn->astSipSignalPdpArray[IMSA_CONN_MAX_NORMAL_SIP_SIGNAL_PDP_NUM-1],
                            sizeof(IMSA_PDP_CNTXT_INFO_STRU),
                            0x0,
                            sizeof(IMSA_PDP_CNTXT_INFO_STRU));

            pstNormalConn->ulSipSignalPdpNum--;

            /* 通知CDS下行过滤承载 */
            IMSA_CONN_SndCdsSetImsBearerReq();

            return ;
        }
    }

    /* 查找普通媒体承载，并删除 */
    for (i = 0; i < pstNormalConn->ulSipMediaPdpNum; i++)
    {
        if ((IMSA_PDP_STATE_ACTIVE == pstNormalConn->astSipMediaPdpArray[i].enPdpState)
            &&((ucCid == pstNormalConn->astSipMediaPdpArray[i].ucCid)
            || (ucRabId == pstNormalConn->astSipMediaPdpArray[i].ucPdpId)))
        {
            if (i < (IMSA_CONN_MAX_NORMAL_SIP_MEDIA_PDP_NUM - 1))
            {
                IMSA_MEM_CPY_S( &pstNormalConn->astSipMediaPdpArray[i],
                                sizeof(IMSA_PDP_CNTXT_INFO_STRU)*((IMSA_CONN_MAX_NORMAL_SIP_MEDIA_PDP_NUM-1)-i),
                                &pstNormalConn->astSipMediaPdpArray[i+1],
                                sizeof(IMSA_PDP_CNTXT_INFO_STRU)*((IMSA_CONN_MAX_NORMAL_SIP_MEDIA_PDP_NUM-1)-i));
            }

            IMSA_MEM_SET_S(     &pstNormalConn->astSipMediaPdpArray[IMSA_CONN_MAX_NORMAL_SIP_MEDIA_PDP_NUM-1],
                                sizeof(IMSA_PDP_CNTXT_INFO_STRU),
                                0x0,
                                sizeof(IMSA_PDP_CNTXT_INFO_STRU));

            pstNormalConn->ulSipMediaPdpNum--;

            /* 通知CDS下行过滤承载 */
            IMSA_CONN_SndCdsSetImsBearerReq();

            return ;
        }
    }

    return ;
}
/*****************************************************************************
 Function Name  : IMSA_CONN_IsExitPersistentBearer
 Description    : 判断是否存在普通媒体承载或者紧急信令承载
 Input          :
 Output         :
 Return Value   : VOS_UINT32

 History        :
      1.wangchen 00209181   2014-09-30  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_IsExitPersistentBearer
(
    VOS_VOID
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                  *pstEmclConn   = VOS_NULL_PTR;
    VOS_UINT32                          i               = IMSA_NULL;

    IMSA_INFO_LOG("IMSA_CONN_IsExitPersistentBearer:enter!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_IsExitPersistentBearer_ENUM, LNAS_ENTRY);


    pstNormalConn = IMSA_CONN_GetNormalConnAddr();
    pstEmclConn = IMSA_CONN_GetEmcConnAddr();

    /* 查找普通媒体承载，并删除 */
    for (i = 0; i < pstNormalConn->ulSipMediaPdpNum; i++)
    {
        if (IMSA_PDP_STATE_ACTIVE == pstNormalConn->astSipMediaPdpArray[i].enPdpState)
        {
            return IMSA_TRUE;
        }
    }

    if (IMSA_PDP_STATE_ACTIVE == pstEmclConn->stSipSignalPdp.enPdpType)
    {
        return IMSA_TRUE;
    }

    return IMSA_FALSE;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_SndConnSetupInd
 Description    : 发送IMSA内部消息ID_IMSA_CONN_SETUP_IND
 Input          : enResult------------------连接建立结果
                  enConnType----------------连接类型
                  enSipPdpType--------------SIP承载类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-27  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_SndConnSetupInd
(
    IMSA_CONN_RESULT_ENUM_UINT32            enResult,
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType
)
{
    IMSA_CONN_SETUP_IND_STRU           *pstConnSetupInd  = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CONN_SndConnSetupInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_SndConnSetupInd_ENUM, LNAS_ENTRY);

    /*分配空间并检验分配是否成功*/
    pstConnSetupInd = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_CONN_SETUP_IND_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstConnSetupInd)
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_CONN_SndConnSetupInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_SndConnSetupInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstConnSetupInd),
                    IMSA_GET_MSG_LENGTH(pstConnSetupInd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstConnSetupInd));

    /*填写消息头*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstConnSetupInd,
                                ID_IMSA_CONN_SETUP_IND,
                                sizeof(IMSA_CONN_SETUP_IND_STRU));

    /*填写响应结果*/
    pstConnSetupInd->enResult       = enResult;
    pstConnSetupInd->enConnType     = enConnType;
    pstConnSetupInd->enSipPdpType   = enSipPdpType;

    /*调用消息发送函数 */
    IMSA_SEND_INTRA_MSG(pstConnSetupInd);
}
/*****************************************************************************
 Function Name  : IMSA_CONN_SndConnMediaSetupInd
 Description    : 发送IMSA内部消息ID_IMSA_CONN_SETUP_IND
 Input          : enResult------------------连接建立结果
                  enConnType----------------连接类型
                  enSipPdpType--------------SIP承载类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-03-17  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_SndConnMediaSetupInd
(
    IMSA_CONN_RESULT_ENUM_UINT32            enResult,
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    IMSA_CONN_MEDIA_PDP_TYPE_ENUM_UINT32    enMediaPdpType
)
{
    IMSA_CONN_SETUP_IND_STRU           *pstConnSetupInd  = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CONN_SndConnMediaSetupInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_SndConnMediaSetupInd_ENUM, LNAS_ENTRY);

    /*分配空间并检验分配是否成功*/
    pstConnSetupInd = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_CONN_SETUP_IND_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstConnSetupInd)
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_CONN_SndConnSetupInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_SndConnMediaSetupInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstConnSetupInd),
                    IMSA_GET_MSG_LENGTH(pstConnSetupInd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstConnSetupInd));

    /*填写消息头*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstConnSetupInd,
                                ID_IMSA_CONN_SETUP_IND,
                                sizeof(IMSA_CONN_SETUP_IND_STRU));

    /*填写响应结果*/
    pstConnSetupInd->enResult       = enResult;
    pstConnSetupInd->enConnType     = enConnType;
    pstConnSetupInd->enSipPdpType   = IMSA_CONN_SIP_PDP_TYPE_MEDIA;
    pstConnSetupInd->enMediaPdpType = enMediaPdpType;

    /*调用消息发送函数 */
    IMSA_SEND_INTRA_MSG(pstConnSetupInd);
}

/*****************************************************************************
 Function Name  : IMSA_CONN_SndConnModifyInd
 Description    : 发送IMSA内部消息ID_IMSA_CONN_MODIFY_IND，通知SERVICE媒体承载修改
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-01  Draft Enact
      2.lihong 00150010      2013-12-06  Modify:Emc dedicated
      3.wangchen 00209181    2015-03-19  Modify:volte
*****************************************************************************/
VOS_VOID IMSA_CONN_SndConnMediaPdpModifyInd
(
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    IMSA_CONN_MEDIA_PDP_TYPE_ENUM_UINT32    enMeiadModifyType
)
{
    IMSA_CONN_MODIFY_IND_STRU           *pstConnModifyInd  = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CONN_SndConnMediaPdpModifyInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_SndConnMediaPdpModifyInd_ENUM, LNAS_ENTRY);

    /*分配空间并检验分配是否成功*/
    pstConnModifyInd = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_CONN_MODIFY_IND_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstConnModifyInd)
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_CONN_SndConnMediaPdpModifyInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_SndConnMediaPdpModifyInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstConnModifyInd),
                    IMSA_GET_MSG_LENGTH(pstConnModifyInd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstConnModifyInd));

    /*填写消息头*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstConnModifyInd,
                                ID_IMSA_CONN_MODIFY_IND,
                                sizeof(IMSA_CONN_MODIFY_IND_STRU));

    /*填写响应结果*/
    pstConnModifyInd->enConnType    = enConnType;
    pstConnModifyInd->enSipPdpType  = IMSA_CONN_SIP_PDP_TYPE_MEDIA;

    pstConnModifyInd->bitOpMediaModifyType = IMSA_OP_TRUE;
    pstConnModifyInd->enMediaPdpType  = enMeiadModifyType;

    /*调用消息发送函数 */
    IMSA_SEND_INTRA_MSG(pstConnModifyInd);
}

/*****************************************************************************
 Function Name  : IMSA_CONN_SndConnRegParaInvalid
 Description    : 发送IMSA内部消息ID_IMSA_CONN_MODIFY_IND，通知SERVICE注册参数无效
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-02  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_SndConnRegParaInvalid( VOS_VOID )
{
    IMSA_CONN_MODIFY_IND_STRU           *pstConnModifyInd  = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CONN_SndConnRegParaInvalid is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_SndConnRegParaInvalid_ENUM, LNAS_ENTRY);

    /*分配空间并检验分配是否成功*/
    pstConnModifyInd = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_CONN_MODIFY_IND_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstConnModifyInd)
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_CONN_SndConnMediaPdpModifyInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_SndConnRegParaInvalid_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstConnModifyInd),
                    IMSA_GET_MSG_LENGTH(pstConnModifyInd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstConnModifyInd));

    /*填写消息头*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstConnModifyInd,
                                ID_IMSA_CONN_MODIFY_IND,
                                sizeof(IMSA_CONN_MODIFY_IND_STRU));

    /*填写响应结果*/
    pstConnModifyInd->enConnType            = IMSA_CONN_TYPE_NORMAL;
    pstConnModifyInd->enSipPdpType          = IMSA_CONN_SIP_PDP_TYPE_SIGNAL;
    pstConnModifyInd->bitOpModifyType       = IMSA_OP_TRUE;
    pstConnModifyInd->enModifyType          = IMSA_CONN_MODIFY_TYPE_REG_PARA_INVALID;

    /*调用消息发送函数 */
    IMSA_SEND_INTRA_MSG(pstConnModifyInd);
}

/*****************************************************************************
 Function Name  : IMSA_CONN_SndConnRegPcscfInvalid
 Description    : 发送IMSA内部消息ID_IMSA_CONN_MODIFY_IND，通知SERVICE注册参数无效
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181      2015-03-25  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_SndConnRegPcscfInvalid( IMSA_CONN_TYPE_ENUM_UINT32 enConnType )
{
    IMSA_CONN_MODIFY_IND_STRU           *pstConnModifyInd  = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CONN_SndConnRegParaInvalid is entered!");

    /*分配空间并检验分配是否成功*/
    pstConnModifyInd = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_CONN_MODIFY_IND_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstConnModifyInd)
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_CONN_SndConnMediaPdpModifyInd:ERROR:Alloc Msg fail!");
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstConnModifyInd),
                    IMSA_GET_MSG_LENGTH(pstConnModifyInd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstConnModifyInd));

    /*填写消息头*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstConnModifyInd, ID_IMSA_CONN_MODIFY_IND, sizeof(IMSA_CONN_MODIFY_IND_STRU));

    /*填写响应结果*/
    pstConnModifyInd->enConnType            = enConnType;
    pstConnModifyInd->enSipPdpType          = IMSA_CONN_SIP_PDP_TYPE_SIGNAL;
    pstConnModifyInd->bitOpModifyType       = IMSA_OP_TRUE;
    pstConnModifyInd->enModifyType          = IMSA_CONN_MODIFY_TYPE_PCSCF_INVALID;

    /* 调用消息发送函数 */
    IMSA_SEND_INTRA_MSG(pstConnModifyInd);

}


/*****************************************************************************
 Function Name  : IMSA_CONN_SndConnRelInd
 Description    : 发送IMSA内部消息ID_IMSA_CONN_REL_IND
 Input          : enConnType----------------连接类型
                  enSipPdpType--------------SIP承载类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_SndConnRelInd
(
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType
)
{
    IMSA_CONN_REL_IND_STRU             *pstConnRelInd  = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CONN_SndConnRelInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_SndConnRelInd_ENUM, LNAS_ENTRY);

    /*分配空间并检验分配是否成功*/
    pstConnRelInd = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_CONN_REL_IND_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstConnRelInd)
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_CONN_SndConnRelInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_SndConnRelInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstConnRelInd),
                    IMSA_GET_MSG_LENGTH(pstConnRelInd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstConnRelInd));

    /*填写消息头*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstConnRelInd,
                                ID_IMSA_CONN_REL_IND,
                                sizeof(IMSA_CONN_REL_IND_STRU));

    /*填写响应结果*/
    pstConnRelInd->enConnType     = enConnType;
    pstConnRelInd->enSipPdpType   = enSipPdpType;

    /*调用消息发送函数 */
    IMSA_SEND_INTRA_MSG(pstConnRelInd);
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ProcReEstablishConnSetupReq
 Description    : IMSA内部消息ID_IMSA_CONN_SETUP_REQ(re-establish类型)处理函数
 Input          : pstConnSetupReqMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2014-3-6  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_ProcReEstablishConnSetupReq
(
    const IMSA_CONN_SETUP_REQ_STRU     *pstConnSetupReqMsg
)
{
    IMSA_CONN_STATUS_ENUM_UINT8         enConnStatus        = IMSA_CONN_STATUS_BUTT;
    TAF_SDF_PARA_QUERY_INFO_STRU       *pstSdfQueryInfo     = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt              = IMSA_FAIL;
    /* TAF_PS_DIAL_PARA_STRU              *pstDialParaInfo     = VOS_NULL_PTR; */
    VOS_UINT8                           ucOpid              = IMSA_NULL;
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType          = pstConnSetupReqMsg->enConnType;
    VOS_UINT32                          ulFoundIndex        = IMSA_NULL;
    /* IMSA_SEL_SDF_PARA_STRU             *pstSelectedSdfPara  = VOS_NULL_PTR; */
    IMSA_CONTROL_MANAGER_STRU          *pstImsaControlManager   = VOS_NULL_PTR;
    VOS_UINT8                           ucCid               = IMSA_FAIL;
    IMSA_IP_TYPE_ENUM_UINT8             enIpType            = IMSA_FAIL;

    IMSA_INFO_LOG("IMSA_CONN_ProcReEstablishConnSetupReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcReEstablishConnSetupReq_ENUM, LNAS_ENTRY);

    pstImsaControlManager   = IMSA_GetControlManagerAddress();

    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        enConnStatus = IMSA_CONN_GetNormalConnStatus();

        ucCid= pstImsaControlManager->stNrmRegParaInfo.ucCid;

        enIpType = pstImsaControlManager->stNrmRegParaInfo.enIpType;
    }
    else
    {
        enConnStatus = IMSA_CONN_GetEmcConnStatus();

        ucCid= pstImsaControlManager->stEmcRegParaInfo.ucCid;

        enIpType = pstImsaControlManager->stEmcRegParaInfo.enIpType;
    }

    /* 如果在CONNING态，则丢弃 */
    if (IMSA_CONN_STATUS_CONNING == enConnStatus)
    {
        return ;
    }

    /* 如果在RELEASING态，则直接回复连接建立失败，原因值为IMSA_CONN_RESULT_FAIL_CONN_RELEASING */
    if (IMSA_CONN_STATUS_RELEASING == enConnStatus)
    {
        IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_FAIL_CONN_RELEASING,
                                    enConnType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        return ;
    }

    pstSdfQueryInfo = IMSA_MEM_ALLOC(sizeof(TAF_SDF_PARA_QUERY_INFO_STRU));

    if (VOS_NULL_PTR == pstSdfQueryInfo)
    {
        /*打印不合法信息*/
        IMSA_ERR_LOG("IMSA_CONN_ProcReEstablishConnSetupReq:ERROR: Mem alloc fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_ProcReEstablishConnSetupReq_ENUM, LNAS_NULL_PTR);

        IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_FAIL_OHTERS,
                                    enConnType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        return;
    }

    /* 获取所有NV项中的SDF配置信息 */
    IMSA_CONN_AssignOpid(enConnType, &ucOpid);
    ulRslt = TAF_PS_GetCidSdfParaInfo(PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid, pstSdfQueryInfo);
    if (VOS_OK != ulRslt)
    {
        /*打印不合法信息*/
        IMSA_ERR_LOG("IMSA_CONN_ProcReEstablishConnSetupReq:TAF_PS_GetCidSdfParaInfo fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_ProcReEstablishConnSetupReq_ENUM, IMSA_CALL_API_ERROR);

        IMSA_MEM_FREE(pstSdfQueryInfo);

        /* 如果获取SDF信息失败，且存在其他PDN的情况下，直接返回成功，SERVICE模块可以判断
        出IP地址发生变化，会本地去注册，然后再重新发起注册 */
        if (IMSA_TRUE == IMSA_CONN_HasActiveSipSignalPdp(enConnType))
        {
            IMSA_CONN_SetupConnSucc(enConnType);

        }
        else
        {
            IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_FAIL_OHTERS,
                                        enConnType,
                                        IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
        }
        return;
    }
    ulRslt = IMSA_CONN_FindSipSignalDialPara(   enConnType,
                                                pstSdfQueryInfo->ulSdfNum,
                                                pstSdfQueryInfo->astSdfPara,
                                                &ulFoundIndex);

    if (IMSA_FAIL == ulRslt)
    {
        /*打印不合法信息*/
        IMSA_ERR_LOG("IMSA_CONN_ProcReEstablishConnSetupReq:ERROR: Err Para!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_ProcReEstablishConnSetupReq_ENUM, 1);

        IMSA_MEM_FREE(pstSdfQueryInfo);

        IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_FAIL_PARA_ERR,
                                    enConnType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);


        return;
    }

    /* 查找拨号参数，如果是IPV4V6类型，且当前无激活承载，则直接发起链接请求 */
    if (TAF_PDP_IPV4V6 == pstSdfQueryInfo->astSdfPara[ulFoundIndex].enPdnType)
    {
        if (IMSA_FALSE == IMSA_CONN_HasActiveSipSignalPdp(enConnType))
        {
            enIpType = IMSA_IP_TYPE_IPV4V6;
        }
        /* 如果是V4V6类型，且当前有其他激活的承载，则需要判断CID和备份的CID是否相同，如果相同，则
       直接用当前的CID发起链接请求；否则，需要重新获取未使用的CID，重新发起拨号请求 */
        else if (ucCid != pstSdfQueryInfo->astSdfPara[ulFoundIndex].ucCid)
        {
            /* 查找一个未激活的CID进行激活 */
            IMSA_CONN_AssignOpid(enConnType, &ucOpid);

            if (VOS_OK != TAF_PS_GetUnusedCid(PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid, &ucCid))
            {
                IMSA_WARN_LOG("IMSA_CONN_ProcReEstablishConnSetupReq:get cid failed!");
                IMSA_MEM_FREE(pstSdfQueryInfo);

                TLPS_PRINT2LAYER_ERROR(IMSA_CONN_ProcReEstablishConnSetupReq_ENUM, LNAS_FUNCTION_LABEL2);

                IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_FAIL_PARA_ERR,
                                            enConnType,
                                            IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
                return ;
            }

        }
    }


    /* 将PDN类型修改为备份的PDN类型 */
    pstSdfQueryInfo->astSdfPara[ulFoundIndex].enPdnType = enIpType;

    /* 存储选择的SDF参数 */
    IMSA_CONN_SaveSelectedSdfPara(  enConnType,
                                    &pstSdfQueryInfo->astSdfPara[ulFoundIndex]);

    IMSA_MEM_FREE(pstSdfQueryInfo);

    /* pstSelectedSdfPara = IMSA_CONN_GetNormalConnSelSdfParaAddr(); */


    ulRslt = IMSA_CONN_SipSignalPdpActOrig(enConnType,
                                           ucCid,
                                           enIpType);

    if (IMSA_FAIL== ulRslt)
    {
        /* 如果拨号失败，且存在其他PDN的情况下，直接返回成功，SERVICE模块可以判断
        出IP地址发生变化，会本地去注册，然后再重新发起注册 */
        if (IMSA_TRUE == IMSA_CONN_HasActiveSipSignalPdp(enConnType))
        {
            IMSA_CONN_SetupConnSucc(enConnType);

        }
        else
        {
            IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_FAIL_OHTERS,
                                        enConnType,
                                        IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
        }
        return;
    }

    /* 连接状态转到CONNING状态 */
    IMSA_CONN_SetConnStatus(enConnType, IMSA_CONN_STATUS_CONNING);

    /* 存储最初请求的PDN类型为备份PDN类型 */
    IMSA_CONN_SaveFirstReqPdnType(enConnType, enIpType);

}

/*****************************************************************************
 Function Name  : IMSA_CONN_ProcConnSetupReq
 Description    : IMSA内部消息ID_IMSA_CONN_SETUP_REQ处理函数
 Input          : pstConnSetupReqMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-25  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_ProcConnSetupReq
(
    const IMSA_CONN_SETUP_REQ_STRU     *pstConnSetupReqMsg
)
{
    IMSA_CONN_STATUS_ENUM_UINT8         enConnStatus        = IMSA_CONN_STATUS_BUTT;
    TAF_SDF_PARA_QUERY_INFO_STRU       *pstSdfQueryInfo     = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt              = IMSA_FAIL;
    TAF_PS_DIAL_PARA_STRU              *pstDialParaInfo     = VOS_NULL_PTR;
    VOS_UINT8                           ucOpid              = IMSA_NULL;
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType          = pstConnSetupReqMsg->enConnType;
    VOS_UINT32                          ulFoundIndex        = IMSA_NULL;
    IMSA_SEL_SDF_PARA_STRU             *pstSelectedSdfPara  = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CONN_ProcConnSetupReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcConnSetupReq_ENUM, LNAS_ENTRY);

    if (IMSA_TRUE == pstConnSetupReqMsg->ulReEstablishFlag)
    {
        IMSA_CONN_ProcReEstablishConnSetupReq(pstConnSetupReqMsg);
        return;
    }

    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        enConnStatus = IMSA_CONN_GetNormalConnStatus();
    }
    else
    {
        enConnStatus = IMSA_CONN_GetEmcConnStatus();
    }

    /* 如果在CONN态，则直接返回连接建立成功 */
    if (IMSA_CONN_STATUS_CONN == enConnStatus)
    {
        IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_SUCCESS,
                                    enConnType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        return ;
    }

    /* 如果在CONNING态，则丢弃 */
    if (IMSA_CONN_STATUS_CONNING == enConnStatus)
    {
        return ;
    }

    /* 如果在RELEASING态，则直接回复连接建立失败，原因值为IMSA_CONN_RESULT_FAIL_CONN_RELEASING */
    if (IMSA_CONN_STATUS_RELEASING == enConnStatus)
    {
        IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_FAIL_CONN_RELEASING,
                                    enConnType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_PdnRejErrRecord(IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_CONN_RELEASING);

        /* 暂时先不删除旧的CHR，因为产品线对新增的CHR还未增加解析，等产品线新增后，
        再将原来的删除 */
        IMSA_PdnConnFailErrLogRecord(   enConnType,
                                        IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_IMSA_CONN_RELEASING,
                                        IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NONE,
                                        IMSA_ERR_LOG_EMC_REG_FAIL_REASON_SERVICE_STATUS_ERROR);
        #endif
        return ;
    }

    /* 如果在IDLE态，则发起连接建立流程 */

    pstSdfQueryInfo = IMSA_MEM_ALLOC(sizeof(TAF_SDF_PARA_QUERY_INFO_STRU));

    if (VOS_NULL_PTR == pstSdfQueryInfo)
    {
        /*打印不合法信息*/
        IMSA_ERR_LOG("IMSA_CONN_ProcNormalConnSetupReq:ERROR: Mem alloc fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_ProcConnSetupReq_ENUM, LNAS_NULL_PTR);

        IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_FAIL_OHTERS,
                                    enConnType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_PdnRejErrRecord(IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_OTHERS);
        #endif
        return;
    }

    /* 获取所有NV项中的SDF配置信息 */
    IMSA_CONN_AssignOpid(enConnType, &ucOpid);
    ulRslt = TAF_PS_GetCidSdfParaInfo(PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid, pstSdfQueryInfo);
    if (VOS_OK != ulRslt)
    {
        /*打印不合法信息*/
        IMSA_ERR_LOG("IMSA_CONN_ProcNormalConnSetupReq:TAF_PS_GetCidSdfParaInfo fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_ProcConnSetupReq_ENUM, IMSA_CALL_API_ERROR);

        IMSA_MEM_FREE(pstSdfQueryInfo);

        IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_FAIL_OHTERS,
                                    enConnType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_PdnRejErrRecord(IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_OTHERS);
        #endif

        return;
    }

    ulRslt = IMSA_CONN_FindSipSignalDialPara(   enConnType,
                                                pstSdfQueryInfo->ulSdfNum,
                                                pstSdfQueryInfo->astSdfPara,
                                                &ulFoundIndex);

    if (IMSA_FAIL == ulRslt)
    {
        /*打印不合法信息*/
        IMSA_ERR_LOG("IMSA_CONN_ProcNormalConnSetupReq:ERROR: Err Para!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_ProcConnSetupReq_ENUM, LNAS_PARAM_INVALID);

        IMSA_MEM_FREE(pstSdfQueryInfo);

        IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_FAIL_PARA_ERR,
                                    enConnType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_PdnRejErrRecord(IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_PARA_ERR);
        /* 暂时先不删除旧的CHR，因为产品线对新增的CHR还未增加解析，等产品线新增后，
        再将原来的删除 */
        IMSA_PdnConnFailErrLogRecord(   enConnType,
                                        IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_NO_IMS_PDP_CONTXT,
                                        IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NONE,
                                        IMSA_ERR_LOG_EMC_REG_FAIL_REASON_NO_EMC_PDP_CONTEXT);
        #endif

        return;
    }

    /* 存储选择的SDF参数 */
    IMSA_CONN_SaveSelectedSdfPara(  enConnType,
                                    &pstSdfQueryInfo->astSdfPara[ulFoundIndex]);

    IMSA_MEM_FREE(pstSdfQueryInfo);

    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        pstSelectedSdfPara = IMSA_CONN_GetNormalConnSelSdfParaAddr();
    }
    else
    {
        pstSelectedSdfPara = IMSA_CONN_GetEmcConnSelSdfParaAddr();
    }

    pstDialParaInfo = IMSA_MEM_ALLOC(sizeof(TAF_PS_DIAL_PARA_STRU));

    if (VOS_NULL_PTR == pstDialParaInfo)
    {
        /*打印不合法信息*/
        IMSA_ERR_LOG("IMSA_CONN_ProcNormalConnSetupReq:TAF_PS_DIAL_PARA_STRU ERROR: Mem alloc fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_ProcConnSetupReq_ENUM, LNAS_NULL_PTR);

        IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_FAIL_OHTERS,
                                    enConnType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_PdnRejErrRecord(IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_OTHERS);
        #endif

        return;
    }

    /* 将选择的SDF参数转化成拨号参数格式 */
    IMSA_CONN_GetImsDailParaFromSelSdfPara( pstSelectedSdfPara,
                                            pstDialParaInfo);


    /* 产生OPID并存储 */
    IMSA_CONN_AssignOpid(enConnType, &ucOpid);
    IMSA_CONN_SetOpid(enConnType, ucOpid);

    /* 调用API接口TAF_PS_CallOrig请求APS建立IMS信令承载 */
    if (VOS_OK == TAF_PS_CallOrig(PS_PID_IMSA,IMSA_CLIENT_ID, ucOpid, pstDialParaInfo))
    {
        /* 启动IMS拨号定时器 */
        IMSA_CONN_StartTimer(enConnType, TI_IMSA_SIP_SIGAL_PDP_ORIG);

        /* 连接状态转到CONNING状态 */
        IMSA_CONN_SetConnStatus(enConnType, IMSA_CONN_STATUS_CONNING);

        /* 存储最初拨号请求的PDN类型 */
        IMSA_CONN_SaveFirstReqPdnType(enConnType, pstDialParaInfo->enPdpType);

        /* 存储当前拨号请求的PDN类型 */
        IMSA_CONN_SaveCurReqPdnType(enConnType, pstDialParaInfo->enPdpType);

        IMSA_INFO_LOG1("global enFirstReqPdnType:", IMSA_CONN_GetNormalConnFirstReqPdnType());
        TLPS_PRINT2LAYER_INFO1(IMSA_CONN_ProcConnSetupReq_ENUM, 1, IMSA_CONN_GetNormalConnFirstReqPdnType());
    }
    else
    {
        /*打印不合法信息*/
        IMSA_ERR_LOG("IMSA_CONN_ProcConnSetupReq:TAF_PS_CallOrig fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_ProcConnSetupReq_ENUM, IMSA_CALL_API_ERROR);

        IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_FAIL_OHTERS,
                                    enConnType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_PdnRejErrRecord(IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_OTHERS);
        #endif

    }

    IMSA_MEM_FREE(pstDialParaInfo);
}

/*****************************************************************************
 Function Name  : IMSA_CONN_RequestApsRelConn
 Description    : 请求APS释放连接
 Input          : enConnType-------------连接类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_RequestApsRelConn
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn      = VOS_NULL_PTR;
    VOS_UINT8                           ucOpid          = IMSA_NULL;

    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        pstEmcConn      = IMSA_CONN_GetEmcConnAddr();

        /* 如果在CONNING态，则请求释放正在建立的信令承载和已经激活的信令承载 */
        if (IMSA_CONN_STATUS_CONNING == pstEmcConn->enImsaConnStatus)
        {
            /* 产生OPID并存储 */
            IMSA_CONN_AssignOpid(enConnType, &ucOpid);

            if (VOS_OK != TAF_PS_CallEnd(   PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid,
                                            pstEmcConn->stSelSdfPara.ucCid))
            {
                IMSA_WARN_LOG("IMSA_CONN_RequestApsRelConn:EMC,conninig,CallEnd failed!");
                TLPS_PRINT2LAYER_WARNING(IMSA_CONN_RequestApsRelConn_ENUM, LNAS_FAIL);
            }

            IMSA_CONN_ClearConnResource(IMSA_CONN_TYPE_EMC);

            /* 通知SERVICE模块连接释放 */
            IMSA_CONN_SndConnRelInd(IMSA_CONN_TYPE_EMC, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            return ;
        }

        /* 产生OPID并存储 */
        IMSA_CONN_AssignOpid(enConnType, &ucOpid);
        /*lint -e774*/
        IMSA_CONN_SetOpid(enConnType, ucOpid);
        /*lint +e774*/



        if (VOS_OK != TAF_PS_CallEnd(   PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid,
                                        (VOS_UINT8)pstEmcConn->stSipSignalPdp.ucCid))
        {
            IMSA_WARN_LOG("IMSA_CONN_RequestApsRelConn:EMC,conn,CallEnd failed!");
            TLPS_PRINT2LAYER_WARNING(IMSA_CONN_RequestApsRelConn_ENUM, LNAS_FAIL);

            IMSA_CONN_ClearConnResource(IMSA_CONN_TYPE_EMC);

            IMSA_CONN_SndCdsSetImsBearerReq();

            /* 通知SERVICE模块连接释放 */
            IMSA_CONN_SndConnRelInd(IMSA_CONN_TYPE_EMC, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            return ;
        }

        /* 启动IMSA去拨号定时器 */
        IMSA_CONN_StartTimer(IMSA_CONN_TYPE_EMC, TI_IMSA_SIP_SIGAL_PDP_END);

        /* 设置连接状态为去连接中 */
        IMSA_CONN_SetConnStatus(IMSA_CONN_TYPE_EMC, IMSA_CONN_STATUS_RELEASING);
        return ;
    }

    pstNormalConn   = IMSA_CONN_GetNormalConnAddr();

    /* 如果在CONNING态，则请求释放正在建立的信令承载和已经激活的信令承载 */
    if (IMSA_CONN_STATUS_CONNING == pstNormalConn->enImsaConnStatus)
    {
        /* 产生OPID并存储 */
        IMSA_CONN_AssignOpid(enConnType, &ucOpid);

        if (VOS_OK != TAF_PS_CallEnd(   PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid,
                                        pstNormalConn->stSelSdfPara.ucCid))
        {
            IMSA_WARN_LOG("IMSA_CONN_RequestApsRelConn:normal,conninig,CallEnd failed!");
            TLPS_PRINT2LAYER_WARNING(IMSA_CONN_RequestApsRelConn_ENUM, LNAS_FAIL);
        }
    }

    if (0 == pstNormalConn->ulSipSignalPdpNum)
    {
        IMSA_WARN_LOG("IMSA_CONN_RequestApsRelConn:normal,conning,no active pdp!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_RequestApsRelConn_ENUM, IMSA_NO_ACTIVE_PDP);

        IMSA_CONN_ClearConnResource(IMSA_CONN_TYPE_NORMAL);

        /* 通知SERVICE模块连接释放 */
        IMSA_CONN_SndConnRelInd(IMSA_CONN_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
        return ;
    }

    /* 产生OPID并存储 */
    IMSA_CONN_AssignOpid(enConnType, &ucOpid);
    IMSA_CONN_SetNormalConnOpid(ucOpid);

    if (VOS_OK != TAF_PS_CallEnd(   PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid,
                                    pstNormalConn->astSipSignalPdpArray[0].ucCid))
    {
        IMSA_WARN_LOG("IMSA_CONN_RequestApsRelConn:normal,CallEnd failed!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_RequestApsRelConn_ENUM, IMSA_CALL_API_ERROR);

        IMSA_CONN_ClearConnResource(IMSA_CONN_TYPE_NORMAL);

        IMSA_CONN_SndCdsSetImsBearerReq();

        /* 通知SERVICE模块连接释放 */
        IMSA_CONN_SndConnRelInd(IMSA_CONN_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        return ;
    }

    /* 启动IMSA去拨号定时器 */
    IMSA_CONN_StartTimer(IMSA_CONN_TYPE_NORMAL, TI_IMSA_SIP_SIGAL_PDP_END);

    /* 设置连接状态为去连接中 */
    IMSA_CONN_SetConnStatus(IMSA_CONN_TYPE_NORMAL, IMSA_CONN_STATUS_RELEASING);

    return ;
}


/*****************************************************************************
 Function Name  : IMSA_CONN_ProcConnRelReq
 Description    : IMSA内部消息ID_IMSA_CONN_REL_REQ处理函数
 Input          : pstConnRelReqMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_ProcConnRelReq
(
    const IMSA_CONN_REL_REQ_STRU       *pstConnRelReqMsg
)
{
    IMSA_CONN_STATUS_ENUM_UINT8         enConnStatus        = IMSA_CONN_STATUS_BUTT;
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType          = pstConnRelReqMsg->enConnType;

    IMSA_INFO_LOG("IMSA_CONN_ProcConnRelReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcConnRelReq_ENUM, LNAS_ENTRY);

    if (IMSA_CONN_SIP_PDP_TYPE_MEDIA == pstConnRelReqMsg->enSipPdpType)
    {
        IMSA_ERR_LOG("IMSA_CONN_ProcConnRelReq:Not support release media type pdp!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_ProcConnRelReq_ENUM, IMSA_NOT_SUPPORT);
        return ;
    }

    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        enConnStatus = IMSA_CONN_GetNormalConnStatus();
    }
    else
    {
        enConnStatus = IMSA_CONN_GetEmcConnStatus();
    }

    /* 如果在IDLE态，则直接返回连接释放成功 */
    if (IMSA_CONN_STATUS_IDLE == enConnStatus)
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcConnRelReq: idle!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcConnRelReq_ENUM, IMSA_STATUS_IDLE);

        IMSA_CONN_SndConnRelInd(  enConnType,
                                  IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        return ;
    }

    /* 如果在RELEASING态，则丢弃 */
    if (IMSA_CONN_STATUS_RELEASING == enConnStatus)
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcConnRelReq: releasing!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcConnRelReq_ENUM, IMSA_STATUS_RELEASING);
        return ;
    }

    /* 停止IMS拨号定时器 */
    IMSA_CONN_StopTimer(enConnType, TI_IMSA_SIP_SIGAL_PDP_ORIG);

    /* 停止等待IPV6参数定时器 */
    IMSA_CONN_StopTimer(enConnType, TI_IMSA_WAIT_IPV6_INFO);

    /* 启动IMS去拨号定时器 */
    IMSA_CONN_StartTimer(enConnType, TI_IMSA_SIP_SIGAL_PDP_END);

    /* 请求APS释放连接 */
    IMSA_CONN_RequestApsRelConn(enConnType);

    return ;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_IsEmcPdpDefined
 Description    : 判断是否定义了紧急PDP NV项
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-05  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_IsEmcPdpDefined( VOS_VOID )
{
    VOS_UINT32                          ulRslt              = IMSA_FAIL;
    TAF_SDF_PARA_QUERY_INFO_STRU       *pstSdfQueryInfo     = VOS_NULL_PTR;
    VOS_UINT8                           ucOpid              = IMSA_NULL;
    VOS_UINT32                          ulFoundIndex        = IMSA_NULL;

    pstSdfQueryInfo = IMSA_MEM_ALLOC(sizeof(TAF_SDF_PARA_QUERY_INFO_STRU));

    if (VOS_NULL_PTR == pstSdfQueryInfo)
    {
        /*打印不合法信息*/
        IMSA_ERR_LOG("IMSA_CONN_IsEmcPdpDefined:ERROR: Mem alloc fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_IsEmcPdpDefined_ENUM, LNAS_NULL_PTR);

        return IMSA_FALSE;
    }

    /* 获取所有NV项中的SDF配置信息 */
    IMSA_CONN_AssignOpid(IMSA_CONN_TYPE_EMC, &ucOpid);
    ulRslt = TAF_PS_GetCidSdfParaInfo(PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid, pstSdfQueryInfo);
    if (VOS_OK != ulRslt)
    {
        IMSA_INFO_LOG("IMSA_CONN_IsEmcPdpDefined:TAF_PS_GetCidSdfParaInfo failed!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_IsEmcPdpDefined_ENUM, IMSA_CALL_API_ERROR);

        IMSA_MEM_FREE(pstSdfQueryInfo);

        return IMSA_FALSE;
    }

    ulRslt = IMSA_CONN_FindSipSignalDialPara(   IMSA_CONN_TYPE_EMC,
                                                pstSdfQueryInfo->ulSdfNum,
                                                pstSdfQueryInfo->astSdfPara,
                                                &ulFoundIndex);

    IMSA_MEM_FREE(pstSdfQueryInfo);

    if (IMSA_FAIL == ulRslt)
    {
        IMSA_INFO_LOG("IMSA_CONN_IsEmcPdpDefined:not define emc pdp!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_IsEmcPdpDefined_ENUM, 1);

        return IMSA_FALSE;
    }

    return IMSA_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_IsEqualToSelectedCid
 Description    : 是否CID是否与选择的流程中的CIDxiangtong
 Input          : enConnType--------------连接类型
                  ucCid-------------------CID
 Output         : VOS_VOID
 Return Value   : ucCid

 History        :
      1.lihong 00150010      2013-08-26  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_IsEqualToSelectedCid
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    VOS_UINT8                           ucCid
)
{
    IMSA_SEL_SDF_PARA_STRU             *pstSelSdfPara = VOS_NULL_PTR;

    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        pstSelSdfPara = IMSA_CONN_GetNormalConnSelSdfParaAddr();
    }
    else
    {
        pstSelSdfPara = IMSA_CONN_GetEmcConnSelSdfParaAddr();
    }

    if (ucCid == pstSelSdfPara->ucCid)
    {
        return IMSA_TRUE;
    }
    else
    {
        return IMSA_FALSE;
    }
}


VOS_VOID IMSA_CONN_PrintNrmConnState( VOS_VOID )
{
    switch (IMSA_CONN_GetNormalConnStatus())
    {
        case IMSA_CONN_STATUS_IDLE:
            IMSA_INFO_LOG("Current Normal Conn State: IDLE");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_PrintNrmConnState_ENUM, IMSA_STATUS_IDLE);
            break;
        case IMSA_CONN_STATUS_CONNING:
            IMSA_INFO_LOG("Current Normal Conn State: CONNING");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_PrintNrmConnState_ENUM, IMSA_STATUS_CONNECTING);
            break;
        case IMSA_CONN_STATUS_RELEASING:
            IMSA_INFO_LOG("Current Normal Conn State: RELEASING");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_PrintNrmConnState_ENUM, IMSA_STATUS_RELEASING);
            break;
        case IMSA_CONN_STATUS_CONN:
            IMSA_INFO_LOG("Current Normal Conn State: CONN");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_PrintNrmConnState_ENUM, IMSA_STATUS_CONN);
            break;
        default:
            IMSA_INFO_LOG("Current Normal Conn State: UNKNOWN");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_PrintNrmConnState_ENUM, IMSA_STATUS_UNKNOWN);
            break;
    }
}


VOS_VOID IMSA_CONN_PrintEmcConnState( VOS_VOID )
{
    switch (IMSA_CONN_GetEmcConnStatus())
    {
        case IMSA_CONN_STATUS_IDLE:
            IMSA_INFO_LOG("Current Emc Conn State: IDLE");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_PrintEmcConnState_ENUM, IMSA_STATUS_IDLE);
            break;
        case IMSA_CONN_STATUS_CONNING:
            IMSA_INFO_LOG("Current Emc Conn State: CONNING");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_PrintEmcConnState_ENUM, IMSA_STATUS_CONNECTING);
            break;
        case IMSA_CONN_STATUS_RELEASING:
            IMSA_INFO_LOG("Current Emc Conn State: RELEASING");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_PrintEmcConnState_ENUM, IMSA_STATUS_RELEASING);
            break;
        case IMSA_CONN_STATUS_CONN:
            IMSA_INFO_LOG("Current Emc Conn State: CONN");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_PrintEmcConnState_ENUM, IMSA_STATUS_CONN);
            break;
        default:
            IMSA_INFO_LOG("Current Emc Conn State: UNKNOWN");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_PrintEmcConnState_ENUM, IMSA_STATUS_UNKNOWN);
            break;
    }
}

/*****************************************************************************
 Function Name   : IMSA_CONN_PrintNicPdpInfo
 Description     : 打印NIC PDP INFO存储结构中的信息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CONN_PrintNicPdpInfo(VOS_VOID)
{
    IMSA_CONN_MANAGER_STRU  *pstConnManager  = IMSA_CONN_GetConnManagerAddr();
    IMSA_PRINT_NIC_PDP_INFO_STRU     *pstMsgNicInfo;

    pstMsgNicInfo = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_PRINT_NIC_PDP_INFO_STRU));
    if (VOS_NULL_PTR == pstMsgNicInfo)
    {
        IMSA_ERR_LOG("IMSA_CONN_PrintNicPdpInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_PrintNicPdpInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstMsgNicInfo),
                    IMSA_GET_MSG_LENGTH(pstMsgNicInfo),
                    0,
                    IMSA_GET_MSG_LENGTH(pstMsgNicInfo));

    IMSA_WRITE_INTRA_MSG_HEAD(  pstMsgNicInfo,
                                ID_IMSA_NIC_PDP_INFO_IND,
                                sizeof(IMSA_PRINT_NIC_PDP_INFO_STRU));

    IMSA_MEM_CPY_S( pstMsgNicInfo->astNicPdpInfoArray,
                    sizeof(IMSA_CONN_NIC_PDP_INFO_STRU)*IMSA_CONN_MAX_NIC_PDP_NUM,
                    pstConnManager->astNicPdpInfoArray,
                    sizeof(IMSA_CONN_NIC_PDP_INFO_STRU)*IMSA_CONN_MAX_NIC_PDP_NUM);

    IMSA_INFO_LOG("IMSA_CONN_PrintNicPdpInfo: show nic pdp info.");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_PrintNicPdpInfo_ENUM, 1);

    (VOS_VOID)LTE_MsgHook(pstMsgNicInfo);

    IMSA_FREE_MSG(pstMsgNicInfo);
}


/*****************************************************************************
 Function Name   : IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo
 Description     : 判断存在于NIC PDP INFO中的IPV4，是否存在于最新承载信息中的IP地址

 Input           : pstNicPdpInfo-----------配置给虚拟网卡的承载信息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_UINT32 IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo(const IMSA_CONN_NIC_PDP_INFO_STRU *pstNicPdpInfo)
{
    IMSA_EMC_CONN_STRU       *pstEmcConn      = VOS_NULL_PTR;
    IMSA_NORMAL_CONN_STRU    *pstNormalConn   = VOS_NULL_PTR;
    VOS_UINT32               i                = 0;

    IMSA_INFO_LOG("IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo_ENUM, LNAS_ENTRY);

    pstEmcConn = IMSA_CONN_GetEmcConnAddr();

    if (0 == IMSA_MEM_CMP(pstNicPdpInfo->stPdpAddr.aucIpV4Addr, pstEmcConn->stSipSignalPdp.stPdpAddr.aucIpV4Addr, IMSA_IPV4_ADDR_LEN))
    {
        IMSA_INFO_LOG("IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo: IPV4 exist in EmcPdpInfo!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo_ENUM, 1);

        return IMSA_TRUE;
    }

    IMSA_INFO_LOG("IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo: IPV4 not exist in EmcPdpInfo!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo_ENUM, 2);

    pstNormalConn = IMSA_CONN_GetNormalConnAddr();

    for (i = 0; i < pstNormalConn->ulSipSignalPdpNum; i++)
    {
        if ( 0 == IMSA_MEM_CMP(pstNicPdpInfo->stPdpAddr.aucIpV4Addr, pstNormalConn->astSipSignalPdpArray[i].stPdpAddr.aucIpV4Addr, IMSA_IPV4_ADDR_LEN))
        {
            IMSA_INFO_LOG("IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo: IPV4 exist in NormalPdpInfo!");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo_ENUM, 3);

            return IMSA_TRUE;
        }
    }

    IMSA_INFO_LOG("IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo: IPV4 not exist in NormalPdpInfo!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo_ENUM, 4);

    return IMSA_FALSE;
}

/*****************************************************************************
 Function Name   : IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo
 Description     : 判断存在于NIC PDP INFO中的IPV6，是否存在于最新承载信息中的IP地址

 Input           : pstNicPdpInfo-----------配置给虚拟网卡的承载信息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_UINT32 IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo(const IMSA_CONN_NIC_PDP_INFO_STRU *pstNicPdpInfo)
{
    IMSA_EMC_CONN_STRU       *pstEmcConn      = VOS_NULL_PTR;
    IMSA_NORMAL_CONN_STRU    *pstNormalConn   = VOS_NULL_PTR;
    VOS_UINT32               i                = 0;

    IMSA_INFO_LOG("IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo_ENUM, LNAS_ENTRY);

    pstEmcConn = IMSA_CONN_GetEmcConnAddr();

    if (0 == IMSA_MEM_CMP(pstNicPdpInfo->stPdpAddr.aucIpV6Addr, pstEmcConn->stSipSignalPdp.stPdpAddr.aucIpV6Addr, IMSA_IPV6_ADDR_LEN))
    {
        IMSA_INFO_LOG("IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo: IPV6 exist in EmcPdpInfo!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo_ENUM, 1);

        return IMSA_TRUE;
    }

    IMSA_INFO_LOG("IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo: IPV6 not exist in EmcPdpInfo!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo_ENUM, 2);

    pstNormalConn = IMSA_CONN_GetNormalConnAddr();

    for (i = 0; i < pstNormalConn->ulSipSignalPdpNum; i++)
    {
        if ( 0 == IMSA_MEM_CMP(pstNicPdpInfo->stPdpAddr.aucIpV6Addr, pstNormalConn->astSipSignalPdpArray[i].stPdpAddr.aucIpV6Addr, IMSA_IPV6_ADDR_LEN))
        {
            IMSA_INFO_LOG("IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo: IPV6 exist in NormalPdpInfo!");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo_ENUM, 3);

            return IMSA_TRUE;
        }
    }

    IMSA_INFO_LOG("IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo: IPV6 not exist in NormalPdpInfo!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo_ENUM, 4);

    return IMSA_FALSE;
}


/*****************************************************************************
 Function Name   : IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo
 Description     : 用于识别存在于NIC PDP INFO中，但不存在于最新承载信息中的IP地址，
                   将其从NIC PDP INFO中删除，并通知TTF删除
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo(VOS_VOID)
{
    IMSA_CONN_MANAGER_STRU  *pstConnManager  = IMSA_CONN_GetConnManagerAddr();
    VOS_UINT32               ulRst           = IMSA_TRUE;
    VOS_UINT32               i               = 0;

    IMSA_INFO_LOG("IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo_ENUM, LNAS_ENTRY);

    for (i = 0; i < IMSA_CONN_MAX_NIC_PDP_NUM; i++)
    {
        if (0 == pstConnManager->astNicPdpInfoArray[i].ucIsUsed)
        {
            continue;
        }

        switch(pstConnManager->astNicPdpInfoArray[i].stPdpAddr.enIpType)
        {
        case IMSA_IP_TYPE_IPV4:
            if (IMSA_FALSE == IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo(&pstConnManager->astNicPdpInfoArray[i]))
            {
                IMSA_INFO_LOG("IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo: IPV4 not exist in PdpInfo!");
                TLPS_PRINT2LAYER_INFO(IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo_ENUM, IMSA_IPV4);

                ulRst = IMSA_FALSE;
            }

            break;
        case IMSA_IP_TYPE_IPV6:
            if (IMSA_FALSE == IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo(&pstConnManager->astNicPdpInfoArray[i]))
            {
                IMSA_INFO_LOG("IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo: IPV6 not exist in PdpInfo!");
                TLPS_PRINT2LAYER_INFO(IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo_ENUM, IMSA_IPV6);

                ulRst = IMSA_FALSE;
            }

            break;
        case IMSA_IP_TYPE_IPV4V6:
            if (IMSA_FALSE == IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo(&pstConnManager->astNicPdpInfoArray[i]) ||
                IMSA_FALSE == IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo(&pstConnManager->astNicPdpInfoArray[i]))
            {
                IMSA_INFO_LOG("IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo: IPV4V6 not exist in PdpInfo!");
                TLPS_PRINT2LAYER_INFO(IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo_ENUM, IMSA_IPV4V6);

                ulRst = IMSA_FALSE;
            }

            break;
        default:
            IMSA_INFO_LOG("IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo: IP tpye error!");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo_ENUM, IMSA_IP_TYPE_ERROR);
            break;
        }

        if (IMSA_FALSE == ulRst)
        {
            /* 防止紧急注册时，普通连接正在重建的场景或者普通注册时，
               紧急连接正在重建的场景，因此在CONNING+REG状态不能删*/
            if (IMSA_FALSE == IMSA_SRV_IsConningRegState(pstConnManager->astNicPdpInfoArray[i].ucIsEmc))
            {
                IMSA_INFO_LOG("IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo: NIC delete pdp info!");
                TLPS_PRINT2LAYER_INFO(IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo_ENUM, 1);
                IMSA_CONN_PdnInfoNicDelete(pstConnManager->astNicPdpInfoArray[i].ucPdpId);

                /* 同上海范晶确认，在删除C核虚拟网卡时，通知RNIC模块，删除虚拟网卡，
                同时给AT上报承载状态 */
                if (IMSA_FALSE == pstConnManager->astNicPdpInfoArray[i].ucIsEmc)
                {
                    IMSA_SndMsgRnicPdnDeactInd(pstConnManager->astNicPdpInfoArray[i].ucPdpId);
                    IMSA_SndMsgAtPdpDeactInd(pstConnManager->astNicPdpInfoArray[i].stPdpAddr.enIpType);
                }

                IMSA_MEM_SET_S( &pstConnManager->astNicPdpInfoArray[i],
                                sizeof(IMSA_CONN_NIC_PDP_INFO_STRU ),
                                0,
                                sizeof(IMSA_CONN_NIC_PDP_INFO_STRU ));

                pstConnManager->astNicPdpInfoArray[i].ucIsUsed = 0;
            }

            ulRst = IMSA_TRUE;
        }
    }
}

/*****************************************************************************
 Function Name   : IMSA_CONN_Ipv4PdpAddrIsExistInNicPdpInfo
 Description     : 判断承载信息中的IPV4，是否存在于NIC PDP INFO存储结构中

 Input           : pstPdpAddr---------------承载信息中的IP信息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_UINT32 IMSA_CONN_Ipv4PdpAddrIsExistInNicPdpInfo(const IMSA_IP_ADDRESS_STRU *pstPdpAddr)
{
    IMSA_CONN_MANAGER_STRU  *pstConnManager  = IMSA_CONN_GetConnManagerAddr();
    VOS_UINT32               i               = 0;

    for (i = 0; i < IMSA_CONN_MAX_NIC_PDP_NUM; i++)
    {
        if (0 == pstConnManager->astNicPdpInfoArray[i].ucIsUsed)
        {
            continue;
        }

        if ( 0 == IMSA_MEM_CMP(pstPdpAddr->aucIpV4Addr, pstConnManager->astNicPdpInfoArray[i].stPdpAddr.aucIpV4Addr, IMSA_IPV4_ADDR_LEN))
        {
            IMSA_INFO_LOG("IMSA_CONN_Ipv4PdpAddrIsExistInNicPdpInfo: IPV4 exist in NicPdpInfo!");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv4PdpAddrIsExistInNicPdpInfo_ENUM, IMSA_EXISTED);
            return IMSA_TRUE;
        }
    }

    IMSA_INFO_LOG("IMSA_CONN_Ipv4PdpAddrIsExistInNicPdpInfo: IPV4 not exist in NicPdpInfo!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv4PdpAddrIsExistInNicPdpInfo_ENUM, 2);

    return IMSA_FALSE;
}

/*****************************************************************************
 Function Name   : IMSA_CONN_Ipv6PdpAddrIsExistInNicPdpInfo
 Description     : 判断承载信息中的IPV6，是否存在于NIC PDP INFO存储结构中

 Input           : pstPdpAddr---------------承载信息中的IP信息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_UINT32 IMSA_CONN_Ipv6PdpAddrIsExistInNicPdpInfo(const IMSA_IP_ADDRESS_STRU *pstPdpAddr)
{
    IMSA_CONN_MANAGER_STRU  *pstConnManager    = IMSA_CONN_GetConnManagerAddr();
    VOS_UINT32               i                 = 0;

    for (i = 0; i < IMSA_CONN_MAX_NIC_PDP_NUM; i++)
    {
        if (0 == pstConnManager->astNicPdpInfoArray[i].ucIsUsed)
        {
            continue;
        }

        if ( 0 == IMSA_MEM_CMP(pstPdpAddr->aucIpV6Addr, pstConnManager->astNicPdpInfoArray[i].stPdpAddr.aucIpV6Addr, IMSA_IPV6_ADDR_LEN))
        {
            IMSA_INFO_LOG("IMSA_CONN_Ipv6PdpAddrIsExistInNicPdpInfo: IPV6 exist in NicPdpInfo!");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv6PdpAddrIsExistInNicPdpInfo_ENUM, IMSA_EXISTED);
            return IMSA_TRUE;
        }
    }

    IMSA_INFO_LOG("IMSA_CONN_Ipv6PdpAddrIsExistInNicPdpInfo: IPV6 not exist in NicPdpInfo!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv6PdpAddrIsExistInNicPdpInfo_ENUM, 2);

    return IMSA_FALSE;
}

/*****************************************************************************
 Function Name   : IMSA_CONN_PdpIdIsExistInNicPdpInfo
 Description     : 判断承载信息中的PDP ID，是否存在于NIC PDP INFO存储结构中

 Input           : pstPdpAddr-----------承载信息中的IP信息
 Output          : pulArrayIndex--------PDP ID存在于astNicPdpInfoArray结构中的索引
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_UINT32 IMSA_CONN_PdpIdIsExistInNicPdpInfo(VOS_UINT8 ucPdpId, VOS_UINT32 *pulArrayIndex)
{
    IMSA_CONN_MANAGER_STRU  *pstConnManager    = IMSA_CONN_GetConnManagerAddr();
    VOS_UINT32               i                 = 0;

    for (i = 0; i < IMSA_CONN_MAX_NIC_PDP_NUM; i++)
    {
        if (0 == pstConnManager->astNicPdpInfoArray[i].ucIsUsed)
        {
            continue;
        }

        if (ucPdpId == pstConnManager->astNicPdpInfoArray[i].ucPdpId)
        {
            IMSA_INFO_LOG("IMSA_CONN_PdpIdIsExistInNicPdpInfo: PdpId exist in NicPdpInfo!");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_PdpIdIsExistInNicPdpInfo_ENUM, IMSA_EXISTED);
            *pulArrayIndex = i;
            return IMSA_TRUE;
        }
    }

    IMSA_INFO_LOG("IMSA_CONN_PdpIdIsExistInNicPdpInfo: PdpId not exist in NicPdpInfo!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_PdpIdIsExistInNicPdpInfo_ENUM, 2);

    return IMSA_FALSE;
}


/*****************************************************************************
 Function Name   : IMSA_CONN_InquireNotUsedInNicPdpInfo
 Description     : 查询ucIsUsed为0的NIC PDP记录
 Input           : None
 Output          : pulArrayIndex------------ucIsUsed为0的astNicPdpInfoArray的索引
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_UINT32 IMSA_CONN_InquireNotUsedInNicPdpInfo(VOS_UINT32 *pulArrayIndex)
{
    IMSA_CONN_MANAGER_STRU  *pstConnManager  = IMSA_CONN_GetConnManagerAddr();
    VOS_UINT32               i               = 0;

    for (i = 0; i < IMSA_CONN_MAX_NIC_PDP_NUM; i++)
    {
        if (0 == pstConnManager->astNicPdpInfoArray[i].ucIsUsed)
        {
            IMSA_INFO_LOG("IMSA_CONN_InquireNotUsedInNicPdpInfo: inquire succ!");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_InquireNotUsedInNicPdpInfo_ENUM, LNAS_SUCC);
            *pulArrayIndex = i;
            return  IMSA_TRUE;
        }
    }
    IMSA_INFO_LOG("IMSA_CONN_InquireNotUsedInNicPdpInfo: inquire fail!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_InquireNotUsedInNicPdpInfo_ENUM, LNAS_FAIL);

    return IMSA_FALSE;
}

/*****************************************************************************
 Function Name   : IMSA_CONN_SaveNicPdpInfo
 Description     : 承载信息保存到NIC PDP INFO存储结构中
 Input           : ucPdpId--------------------被保存的PDP ID
                   ucIsEmc--------------------是否为紧急
                   pulArrayIndex--------------保存到NIC PDP INFO结构中的索引
                   pstPdpAddr-----------------被保存的PDP INFO
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CONN_SaveNicPdpInfo(VOS_UINT8 ucPdpId,        VOS_UINT8 ucIsEmc, \
                                            VOS_UINT32 ulArrayIndex, const IMSA_IP_ADDRESS_STRU *pstPdpAddr)
{
    IMSA_CONN_MANAGER_STRU  *pstConnManager  = IMSA_CONN_GetConnManagerAddr();

    IMSA_INFO_LOG("IMSA_CONN_SaveNicPdpInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_SaveNicPdpInfo_ENUM, LNAS_ENTRY);

    IMSA_MEM_CPY_S(&pstConnManager->astNicPdpInfoArray[ulArrayIndex].stPdpAddr,
                    sizeof(IMSA_IP_ADDRESS_STRU),
                    pstPdpAddr,
                    sizeof(IMSA_IP_ADDRESS_STRU));
    pstConnManager->astNicPdpInfoArray[ulArrayIndex].ucIsUsed = 1;
    pstConnManager->astNicPdpInfoArray[ulArrayIndex].ucIsEmc = ucIsEmc;
    pstConnManager->astNicPdpInfoArray[ulArrayIndex].ucPdpId = ucPdpId;
}

/*****************************************************************************
 Function Name   : IMSA_CONN_AddNormalPdpInfo2NicPdpInfo
 Description     : 判断IPV4信令承载信息是否存在于NIC PDP INFO中，
                   如果不存在，添加到NIC PDP INFO中，并配置给TTF
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CONN_ProcIPV4PdpInfoForNic(VOS_UINT8 ucIsEmc, IMSA_PDP_CNTXT_INFO_STRU *pstPdpCntxtInfo)
{
    IMSA_IP_ADDRESS_STRU     *pstImsaIpAddr   = VOS_NULL_PTR;
    VOS_UINT32               ulArrayIndex     = 0;
    VOS_UINT8                ucPdpId          = 0;

    IMSA_INFO_LOG("IMSA_CONN_ProcIPV4PdpInfoForNic is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcIPV4PdpInfoForNic_ENUM, LNAS_ENTRY);

    pstImsaIpAddr = &pstPdpCntxtInfo->stPdpAddr;
    ucPdpId       = pstPdpCntxtInfo->ucPdpId;

    if (IMSA_FALSE == IMSA_CONN_Ipv4PdpAddrIsExistInNicPdpInfo(pstImsaIpAddr))
    {
        if (IMSA_TRUE == IMSA_CONN_InquireNotUsedInNicPdpInfo(&ulArrayIndex))
        {
            IMSA_CONN_SaveNicPdpInfo(ucPdpId, ucIsEmc, ulArrayIndex, pstImsaIpAddr);

            IMSA_CONN_ConfigPdpInfo2Bsp(pstPdpCntxtInfo);
            /* 同上海范晶确认，在绑定C核虚拟网卡时，通知RNIC模块，绑定虚拟网卡，
            同时给AT上报承载状态 */
            if (VOS_FALSE == ucIsEmc)
            {
                IMSA_SndMsgRnicPdnActInd(pstPdpCntxtInfo);
                IMSA_SndMsgAtPdpActInd(pstPdpCntxtInfo);
            }
        }
        else
        {
            IMSA_INFO_LOG("IMSA_CONN_ProcIPV4PdpInfoForNic: Inquire notUsed for ipv4 fail!");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcIPV4PdpInfoForNic_ENUM, LNAS_FAIL);
        }
    }
}

/*****************************************************************************
 Function Name   : IMSA_CONN_ProcIPV6PdpInfoForNic
 Description     : 判断IPV6信令承载信息是否存在于NIC PDP INFO中，
                   如果不存在，添加到NIC PDP INFO中，并配置给TTF
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CONN_ProcIPV6PdpInfoForNic(VOS_UINT8 ucIsEmc, IMSA_PDP_CNTXT_INFO_STRU *pstPdpCntxtInfo)
{
    IMSA_IP_ADDRESS_STRU     *pstImsaIpAddr   = VOS_NULL_PTR;
    VOS_UINT32               ulArrayIndex     = 0;
    VOS_UINT8                ucPdpId          = 0;
    VOS_UINT8                aucTemp[IMSA_IPV6_PREFIX_LEN]   = {0};

    IMSA_INFO_LOG("IMSA_CONN_ProcIPV6PdpInfoForNic is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcIPV6PdpInfoForNic_ENUM, LNAS_ENTRY);

    pstImsaIpAddr = &pstPdpCntxtInfo->stPdpAddr;
    ucPdpId       = pstPdpCntxtInfo->ucPdpId;

    if (0 == IMSA_MEM_CMP(aucTemp, pstImsaIpAddr->aucIpV6Addr, IMSA_IPV6_PREFIX_LEN))
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcIPV6PdpInfoForNic: IPV6 prefix is 0!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcIPV6PdpInfoForNic_ENUM, LNAS_PARAM_INVALID);
    }
    else
    {
        if (IMSA_FALSE == IMSA_CONN_Ipv6PdpAddrIsExistInNicPdpInfo(pstImsaIpAddr))
        {
            if (IMSA_TRUE == IMSA_CONN_InquireNotUsedInNicPdpInfo(&ulArrayIndex))
            {
                IMSA_CONN_SaveNicPdpInfo(ucPdpId, ucIsEmc, ulArrayIndex, pstImsaIpAddr);

                IMSA_CONN_ConfigPdpInfo2Bsp(pstPdpCntxtInfo);
                /* 同上海范晶确认，在绑定C核虚拟网卡时，通知RNIC模块，绑定虚拟网卡，
                同时给AT上报承载状态 */
                if (VOS_FALSE == ucIsEmc)
                {
                    IMSA_SndMsgRnicPdnActInd(pstPdpCntxtInfo);
                    IMSA_SndMsgAtPdpActInd(pstPdpCntxtInfo);
                }
            }
            else
            {
                IMSA_INFO_LOG("IMSA_CONN_ProcIPV6PdpInfoForNic: Inquire notUsed for ipv6 fail!");
                TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcIPV6PdpInfoForNic_ENUM, LNAS_FAIL);
            }
        }
    }
}

/*****************************************************************************
 Function Name   : IMSA_CONN_ProcIPV4V6PdpInfoForNic
 Description     : 判断IPV4V6信令承载信息是否存在于NIC PDP INFO中，
                   如果不存在，添加到NIC PDP INFO中，并配置给TTF
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CONN_ProcIPV4V6PdpInfoForNic(VOS_UINT8 ucIsEmc, IMSA_PDP_CNTXT_INFO_STRU *pstPdpCntxtInfo)
{
    IMSA_CONN_MANAGER_STRU   *pstConnManager  = IMSA_CONN_GetConnManagerAddr();
    IMSA_IP_ADDRESS_STRU     *pstImsaIpAddr   = VOS_NULL_PTR;
    VOS_UINT32               ulArrayIndex     = 0;
    VOS_UINT8                ucPdpId          = 0;
    VOS_UINT8                aucTemp[IMSA_IPV6_PREFIX_LEN]   = {0};

    IMSA_INFO_LOG("IMSA_CONN_ProcIPV4V6PdpInfoForNic is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcIPV4V6PdpInfoForNic_ENUM, LNAS_ENTRY);

    pstImsaIpAddr = &pstPdpCntxtInfo->stPdpAddr;
    ucPdpId       = pstPdpCntxtInfo->ucPdpId;

    /* if (0 == IMSA_MEM_CMP(aucTemp, pstImsaIpAddr->aucIpV6Addr, IMSA_IPV6_PREFIX_LEN))
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcIPV4V6PdpInfoForNic: IPV6 prefix is 0, !");
        return;
    } */

    if ((IMSA_TRUE == IMSA_CONN_Ipv4PdpAddrIsExistInNicPdpInfo(pstImsaIpAddr)) &&
        (IMSA_TRUE == IMSA_CONN_Ipv6PdpAddrIsExistInNicPdpInfo(pstImsaIpAddr)))
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcIPV4V6PdpInfoForNic: IPV4V6 exist in PdpInfo!");
        return;
    }

    if (IMSA_TRUE == IMSA_CONN_PdpIdIsExistInNicPdpInfo(ucPdpId, &ulArrayIndex))
    {
        IMSA_CONN_PdnInfoNicDelete(ucPdpId);

        IMSA_CONN_SaveNicPdpInfo(ucPdpId, ucIsEmc, ulArrayIndex, pstImsaIpAddr);

        if (0 == IMSA_MEM_CMP(aucTemp, pstConnManager->astNicPdpInfoArray[ulArrayIndex].stPdpAddr.aucIpV6Addr, IMSA_IPV6_PREFIX_LEN))
        {
            pstConnManager->astNicPdpInfoArray[ulArrayIndex].stPdpAddr.enIpType = IMSA_IP_TYPE_IPV4;
        }

        IMSA_CONN_ConfigPdpInfo2Bsp(pstPdpCntxtInfo);
        /* 同上海范晶确认，在绑定C核虚拟网卡时，通知RNIC模块，绑定虚拟网卡，
        同时给AT上报承载状态 */
        if (VOS_FALSE == ucIsEmc)
        {
            IMSA_SndMsgRnicPdnActInd(pstPdpCntxtInfo);
            IMSA_SndMsgAtPdpActInd(pstPdpCntxtInfo);
        }
    }
    else
    {
        if (IMSA_TRUE == IMSA_CONN_InquireNotUsedInNicPdpInfo(&ulArrayIndex))
        {
            IMSA_CONN_SaveNicPdpInfo(ucPdpId, ucIsEmc, ulArrayIndex, pstImsaIpAddr);

            if (0 == IMSA_MEM_CMP(aucTemp, pstConnManager->astNicPdpInfoArray[ulArrayIndex].stPdpAddr.aucIpV6Addr, IMSA_IPV6_PREFIX_LEN))
            {
                pstConnManager->astNicPdpInfoArray[ulArrayIndex].stPdpAddr.enIpType = IMSA_IP_TYPE_IPV4;
            }

            IMSA_CONN_ConfigPdpInfo2Bsp(pstPdpCntxtInfo);
            /* 同上海范晶确认，在绑定C核虚拟网卡时，通知RNIC模块，绑定虚拟网卡，
            同时给AT上报承载状态 */
            if (VOS_FALSE == ucIsEmc)
            {
                IMSA_SndMsgRnicPdnActInd(pstPdpCntxtInfo);
                IMSA_SndMsgAtPdpActInd(pstPdpCntxtInfo);
            }
        }
        else
        {
            IMSA_INFO_LOG("IMSA_CONN_ProcIPV4V6PdpInfoForNic: Inquire notUsed for ipv6 fail!");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcIPV4V6PdpInfoForNic_ENUM, LNAS_FAIL);
        }
    }

    return;
}


/*****************************************************************************
 Function Name   : IMSA_CONN_AddNormalPdpInfo2NicPdpInfo
 Description     : 存在于最新普通信令承载信息中，但不存在于NIC PDP INFO中的IP地址，
                   添加到NIC PDP INFO中，并配置给TTF
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CONN_AddNormalPdpInfo2NicPdpInfo(VOS_VOID)
{
    IMSA_NORMAL_CONN_STRU    *pstNormalConn   = VOS_NULL_PTR;
    VOS_UINT32               i                = 0;

    IMSA_INFO_LOG("IMSA_CONN_AddNormalPdpInfo2NicPdpInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_AddNormalPdpInfo2NicPdpInfo_ENUM, LNAS_ENTRY);

    pstNormalConn = IMSA_CONN_GetNormalConnAddr();

    for (i = 0; i < pstNormalConn->ulSipSignalPdpNum; i ++ )
    {
        switch(pstNormalConn->astSipSignalPdpArray[i].stPdpAddr.enIpType)
        {
        case IMSA_IP_TYPE_IPV4:
            IMSA_CONN_ProcIPV4PdpInfoForNic(0, &pstNormalConn->astSipSignalPdpArray[i]);
            break;
        case IMSA_IP_TYPE_IPV6:
            IMSA_CONN_ProcIPV6PdpInfoForNic(0, &pstNormalConn->astSipSignalPdpArray[i]);
            break;
        case IMSA_IP_TYPE_IPV4V6:
            IMSA_CONN_ProcIPV4V6PdpInfoForNic(0, &pstNormalConn->astSipSignalPdpArray[i]);
            break;
        default:
            IMSA_INFO_LOG("IMSA_CONN_AddNormalPdpInfo2NicPdpInfo: enIpType error!");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_AddNormalPdpInfo2NicPdpInfo_ENUM, LNAS_PARAM_INVALID);
            break;
        }
    }
}

/*****************************************************************************
 Function Name   : IMSA_CONN_AddEmcPdpInfo2NicPdpInfo
 Description     : 存在于最新紧急信令承载信息中，但不存在于NIC PDP INFO中的IP地址，
                   添加到NIC PDP INFO中，并配置给TTF
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CONN_AddEmcPdpInfo2NicPdpInfo(VOS_VOID)
{
    IMSA_EMC_CONN_STRU       *pstEmcConn      = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CONN_AddEmcPdpInfo2NicPdpInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_AddEmcPdpInfo2NicPdpInfo_ENUM, LNAS_ENTRY);

    pstEmcConn = IMSA_CONN_GetEmcConnAddr();

    switch(pstEmcConn->stSipSignalPdp.stPdpAddr.enIpType)
    {
    case IMSA_IP_TYPE_IPV4:
        IMSA_CONN_ProcIPV4PdpInfoForNic(1, &pstEmcConn->stSipSignalPdp);
        break;
    case IMSA_IP_TYPE_IPV6:
        IMSA_CONN_ProcIPV6PdpInfoForNic(1, &pstEmcConn->stSipSignalPdp);
        break;
    case IMSA_IP_TYPE_IPV4V6:
        IMSA_CONN_ProcIPV4V6PdpInfoForNic(1, &pstEmcConn->stSipSignalPdp);
        break;
    default:
        IMSA_INFO_LOG("IMSA_CONN_AddEmcPdpInfo2NicPdpInfo: enIpType error!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_AddEmcPdpInfo2NicPdpInfo_ENUM, LNAS_PARAM_INVALID);
        break;
    }
}

/*****************************************************************************
 Function Name   : IMSA_CONN_AddPdpInfo2NicPdpInfo
 Description     : 用于识别存在于最新承载信息中，但不存在于NIC PDP INFO中的IP地址，
                   添加到NIC PDP INFO中，并配置给TTF
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CONN_AddPdpInfo2NicPdpInfo(VOS_VOID)
{
    IMSA_INFO_LOG("IMSA_CONN_AddPdpInfo2NicPdpInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_AddPdpInfo2NicPdpInfo_ENUM, LNAS_ENTRY);

    /* 识别存在于最新普通信令承载信息中，但不存在于NIC PDP INFO中的IP地址，
       添加到NIC PDP INFO中，并配置给TTF */
    if (IMSA_SRV_STATUS_CONNING_REG != IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_CONN_AddNormalPdpInfo2NicPdpInfo();
    }

    /* 识别存在于最新紧急信令承载信息中，但不存在于NIC PDP INFO中的IP地址，
       添加到NIC PDP INFO中，并配置给TTF */
    if (IMSA_SRV_STATUS_CONNING_REG != IMSA_SRV_GetEmcSrvStatus())
    {
        IMSA_CONN_AddEmcPdpInfo2NicPdpInfo();
    }
}


/*****************************************************************************
 Function Name   : IMSA_CONN_UpdateNicPdpInfo
 Description     : 更新存储配置给NIC的PDP信息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CONN_UpdateNicPdpInfo( VOS_VOID )
{

    IMSA_INFO_LOG("IMSA_CONN_UpdateNicPdpInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_UpdateNicPdpInfo_ENUM, LNAS_ENTRY);
    /* 将更新前的NIC PDP信息上传到HIDS上显示 */
    IMSA_CONN_PrintNicPdpInfo();

    /* 识别存在于NIC PDP INFO中，但不存在于最新承载信息中的IP地址，
       将其从NIC PDP INFO中删除，并通知TTF删除 */
    IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo();

    /* 识别存在于最新承载信息中，但不存在于NIC PDP INFO中的IP地址，
       添加到NIC PDP INFO中，并配置给TTF */
    IMSA_CONN_AddPdpInfo2NicPdpInfo ();

    /* 将更新后的NIC PDP信息上传到HIDS上显示 */
    IMSA_CONN_PrintNicPdpInfo();
}

/*****************************************************************************
 Function Name   : IMSA_CONN_UpdateNicPdpInfo
 Description     : 更新存储配置给NIC的PDP信息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CONN_SetupConnFail
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_CONN_RESULT_ENUM_UINT32        enResult,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    #if (FEATURE_ON == FEATURE_PTM)
    IMSA_ERR_LOG_PDNREJ_CAUSE_ENUM_UINT32   enPdnConnRejCause = IMSA_ERR_LOG_PDNREJ_CAUSE_BUTT;
    #endif

    /* 更新连接状态为IDLE */
    IMSA_CONN_SetConnStatus(enConnType, IMSA_CONN_STATUS_IDLE);

    /* 清除连接实体信息 */
    IMSA_CONN_ClearConnResource(enConnType);

    IMSA_CONN_SndConnSetupInd(  enResult,
                                enConnType,
                                IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

    #if (FEATURE_ON == FEATURE_PTM)
    enPdnConnRejCause = IMSA_PDN_InterRejCauseProc(enResult, enCause);
    IMSA_PdnRejErrRecord(enPdnConnRejCause);
    #endif
}
#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 Function Name   :  IMSA_PDN_CnRejCauseProc
 Description     :  将TAF上报的拒绝原因转换成对应的网侧拒绝原因值
 Input           :  enCause 表示TAF上报的拒绝原因值

 Output          :  输出一个网侧拒绝原因值
 Return          :

 History         :
    1.wangchen 　00209181 2015-01-08 新增文件

*****************************************************************************/
IMSA_ERR_LOG_PDNREJ_CAUSE_ENUM_UINT32  IMSA_PDN_CnRejCauseProc
(
    TAF_PS_CAUSE_ENUM_UINT32 enCause
)
{
    IMSA_ERR_LOG_PDNREJ_CAUSE_ENUM_UINT32   enImsaCnCause = IMSA_ERR_LOG_PDNREJ_CAUSE_BUTT;
    VOS_UINT32 i;

    for(i = 0; i < g_astImsaCnRejCauseNum; i++)
    {
        if(enCause == g_astImsaCnRejCauseMap[i].enCause)
        {
            enImsaCnCause = g_astImsaCnRejCauseMap[i].enImsaCnRejCause;
            break;
        }
    }
    if(g_astImsaCnRejCauseNum == i)
    {
        enImsaCnCause = IMSA_ERR_LOG_PDNREJ_CAUSE_BUTT;
    }

    return enImsaCnCause;
}
/*****************************************************************************
 Function Name   :  IMSA_PDN_CnRejCauseProc
 Description     :  将TAF上报的拒绝原因转换成对应的网侧拒绝原因值
 Input           :  enCause 表示TAF上报的拒绝原因值

 Output          :  输出一个网侧拒绝原因值
 Return          :

 History         :
    1.wangchen 　00209181 2015-01-08 新增文件

*****************************************************************************/
IMSA_ERR_LOG_PDNREJ_CAUSE_ENUM_UINT32  IMSA_PDN_InterRejCauseProc
(
    IMSA_CONN_RESULT_ENUM_UINT32    enResult,
    TAF_PS_CAUSE_ENUM_UINT32        enCause
)
{
    IMSA_ERR_LOG_PDNREJ_CAUSE_ENUM_UINT32   enImsaCnCause = IMSA_ERR_LOG_PDNREJ_CAUSE_BUTT;

    switch(enResult)
    {
        case IMSA_CONN_RESULT_FAIL_PARA_ERR:
            enImsaCnCause = IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_PARA_ERR;
            break;

        case IMSA_CONN_RESULT_FAIL_TIMER_EXP:
            enImsaCnCause = IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_TIMER_EXP;
            break;

        case IMSA_CONN_RESULT_FAIL_CN_REJ:
            enImsaCnCause = IMSA_PDN_CnRejCauseProc(enCause);
            break;

        case IMSA_CONN_RESULT_FAIL_CONN_RELEASING:
            enImsaCnCause = IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_CONN_RELEASING;
            break;

        case IMSA_CONN_RESULT_FAIL_PDP_ACTIVATE_LIMIT:
            enImsaCnCause = IMSA_ERR_LOG_PDNREJ_CAUSE_PDP_ACTIVATE_LIMIT;
            break;

        case IMSA_CONN_RESULT_FAIL_SAME_APN_OPERATING:
            enImsaCnCause = IMSA_ERR_LOG_PDNREJ_CAUSE_SAME_APN_OPERATING;
            break;

        case IMSA_CONN_RESULT_FAIL_OHTERS:
            enImsaCnCause = IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_OTHERS;
            break;

        default:
            break;
    }
    return enImsaCnCause;
}

/*****************************************************************************
 Function Name   :  IMSA_PDN_CnRejCauseProc
 Description     :  将TAF上报的拒绝原因转换成对应的网侧拒绝原因值
 Input           :  enCause 表示TAF上报的拒绝原因值

 Output          :  输出一个网侧拒绝原因值
 Return          :

 History         :
    1.wangchen 　00209181 2015-01-08 新增文件

*****************************************************************************/
IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_ENUM_UINT32  IMSA_Norm_PDN_RejCauseProc
(
    IMSA_CONN_RESULT_ENUM_UINT32    enResult
)
{
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_ENUM_UINT32   enImsaCnCause = IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_BUTT;

    switch(enResult)
    {
        case IMSA_CONN_RESULT_FAIL_PARA_ERR:
            enImsaCnCause = IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_IMSA_PARA_ERR;
            break;

        case IMSA_CONN_RESULT_FAIL_TIMER_EXP:
            enImsaCnCause = IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_IMSA_TIMER_EXP;
            break;

        case IMSA_CONN_RESULT_FAIL_CN_REJ:
            enImsaCnCause = IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_NW_REJ;
            break;

        case IMSA_CONN_RESULT_FAIL_CONN_RELEASING:
            enImsaCnCause = IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_IMSA_CONN_RELEASING;
            break;

        case IMSA_CONN_RESULT_FAIL_PDP_ACTIVATE_LIMIT:
            enImsaCnCause = IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_PDP_ACTIVATE_LIMIT;
            break;

        case IMSA_CONN_RESULT_FAIL_SAME_APN_OPERATING:
            enImsaCnCause = IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_SAME_APN_OPERATING;
            break;

        case IMSA_CONN_RESULT_FAIL_OHTERS:
            enImsaCnCause = IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_IMSA_OTHERS;
            break;

        default:
            break;
    }
    return enImsaCnCause;
}


#endif

/*lint +e961*/

#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/*lint +esym(766,*)*/
/* end of ImsaConnManagement.c */



