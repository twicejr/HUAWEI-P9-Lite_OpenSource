/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaServiceManagement.c
  Description     : 该C文件实现服务管理模块的初始化，内部消息的处理和发送
  History           :
     1.sunbing 49683      2013-06-19  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "ImsaServiceManagement.h"
#include "ImsaEntity.h"
#include "ImsaPublic.h"
#include "ImsaInterface.h"
#include "ImsaProcMsccMsg.h"
#include "ImsaCallManagement.h"
#include "ImsaProcAtMsg.h"
#include "ImsaProcSpmMsg.h"
#include "ImsaProcSmsMsg.h"
#include "ImsaProcUssdMsg.h"
#include "ImsaImsAdaption.h"

#include "ImsaLmmInterface.h"

/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_IMSASERVICEMANAGEMENT_C
#define    THIS_NAS_FILE_ID      NAS_FILE_ID_IMSASERVICEMANAGEMENT_C
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
IMSA_SUBSCRIPTION_INFO_LIST_STRU    g_stSubcriptionInfoList = {0};              /**< 订阅信息列表 */

extern VOS_VOID IMSA_CONTROL_InitConfigPara( VOS_VOID );
extern VOS_VOID IMSA_CONTROL_InitNetworkInfo( VOS_VOID );
extern VOS_VOID IMSA_SRV_RatFormatTransform
(
    IMSA_CAMPED_RAT_TYPE_ENUM_UINT8    *penImsaRat,
    MSCC_IMSA_RAT_TYPE_ENUM_UINT8        enMmaRat
);
extern VOS_UINT32 IMSA_SRV_IsCurRatSupportEms( VOS_VOID );
extern VOS_UINT32 IMSA_SRV_IsNrmSrvIsimParaSatisfied( VOS_VOID );
extern IMSA_NRM_SRV_CON_SAT_STATUE_ENMUM_UINT32 IMSA_SRV_IsNrmSrvConditonSatisfied( VOS_VOID );
extern VOS_UINT32 IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied( VOS_VOID );
extern VOS_UINT32 IMSA_SRV_IsEmcSrvConditonSatisfied( VOS_VOID );
/*extern VOS_VOID IMSA_CMCCDeregProc();*/
extern IMSA_NORMAL_REG_STATUS_ENUM_UINT32 IMSA_SRV_GetRegStatusFromSrvStatus
(
    IMSA_SRV_STATUS_ENUM_UINT8          enSrvStatus
);
extern VOS_UINT32 IMSA_SRV_IsSrvStatusEqual
(
    IMSA_SRV_TYPE_ENUM_UINT8            enSrvType,
    IMSA_SRV_STATUS_ENUM_UINT8          enImsaSrvStatus
);
extern VOS_VOID IMSA_SRV_SndConnSetupReq
(
    VOS_UINT32                          ulReEstablishFlag,
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType
);

extern VOS_VOID IMSA_SRV_SndRegRegReq
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType,
    IMSA_REG_ADDR_PARAM_ENUM_UINT32     enAddrType
);

extern VOS_VOID IMSA_SRV_SndNrmRegStatusNotify
(
    const IMSA_SUBSCRIPTION_INFO_STRU  *pstSubsciptionInfo,
    IMSA_NORMAL_REG_STATUS_ENUM_UINT32  enNormalRegStatus
);
extern VOS_VOID IMSA_SRV_NrmRegStatusNotify
(
    IMSA_NORMAL_REG_STATUS_ENUM_UINT32  enNrmRegStatus
);

extern VOS_VOID IMSA_SRV_ProcConnSetupIndSucc
(
    const IMSA_CONN_SETUP_IND_STRU     *pstConnSetupIndMsg
);
extern VOS_VOID IMSA_SRV_ProcConnSetupIndFail
(
    const IMSA_CONN_SETUP_IND_STRU     *pstConnSetupIndMsg
);
extern VOS_VOID IMSA_SRV_ProcRegRegIndSucc
(
    const IMSA_REG_REG_IND_STRU        *pstRegRegIndMsg
);
extern VOS_VOID IMSA_SRV_ProcRegRegIndFail
(
    const IMSA_REG_REG_IND_STRU        *pstRegRegIndMsg
);
extern VOS_VOID IMSA_SRV_ProcEmcConnRelIndMsg
(
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType
);
extern VOS_VOID IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg( VOS_VOID );
extern VOS_VOID IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg
(
    const IMSA_CONN_MODIFY_IND_STRU    *pstConnModifyIndMsg
);
extern VOS_VOID IMSA_SRV_ProcTransToNotSupportEms( VOS_VOID );
extern VOS_VOID IMSA_SRV_UpdateRat
(
    MSCC_IMSA_RAT_TYPE_ENUM_UINT8        enRat,
    VOS_UINT32                         *pulIsNotfiyNrmNoSrv,
    VOS_UINT32                         *pulIsNotfiyEmcNoSrv
);
extern VOS_VOID IMSA_SRV_UpdateImsVoPsStatus
(
    MSCC_IMSA_IMS_VOPS_INDICATOR_ENUM_UINT8      enImsVoPsInd
);
extern VOS_VOID IMSA_SRV_UpdateEmsStatus
(
    MSCC_IMSA_EMS_INDICATOR_ENUM_UINT8           enEmsInd
);
extern VOS_UINT32 IMSA_IsImsVoiceContidionSatisfied( VOS_VOID );

extern VOS_VOID IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo
(
    IMSA_IMS_INPUT_SERVICE_REASON_ENUM_UINT32   enInputServeReason
);

extern VOS_VOID IMSA_SRV_RegConningStateProcRegDeregIndMsg
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType
);

extern VOS_UINT32 IMSA_SRV_GetImsVoiceCapability(MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8 *penImsVoiceCap);

extern VOS_VOID IMSA_SRV_SetImsRegForbidden
(
    IMSA_REG_TYPE_ENUM_UINT8       enRegType,
    IMSA_REG_RESULT_ENUM_UINT32    enResult
);

extern VOS_VOID IMSA_StartTempForbTimer(VOS_VOID);
extern VOS_UINT32 IMSA_IsTempForbTimerRunning(VOS_VOID);

/*****************************************************************************
  3 Function
*****************************************************************************/
/*lint -e961*/
/*****************************************************************************
 Function Name  : IMSA_CONTROL_InitConfigPara
 Description    : IMSA 总控模块初始化配置信息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONTROL_InitConfigPara( VOS_VOID )
{
    IMSA_CONFIG_PARA_STRU              *pstImsaConfigPara = VOS_NULL_PTR;

    pstImsaConfigPara = IMSA_GetConfigParaAddress();

    pstImsaConfigPara->ucGsmImsSupportFlag          = VOS_FALSE;
    pstImsaConfigPara->ucUtranImsSupportFlag        = VOS_FALSE;
    pstImsaConfigPara->ucLteImsSupportFlag          = VOS_FALSE;
    pstImsaConfigPara->ucGsmEmsSupportFlag          = VOS_FALSE;
    pstImsaConfigPara->ucUtranEmsSupportFlag        = VOS_FALSE;
    pstImsaConfigPara->ucLteEmsSupportFlag          = VOS_FALSE;
    pstImsaConfigPara->ucVoiceCallOnImsSupportFlag  = VOS_TRUE;
    pstImsaConfigPara->ucSmsOnImsSupportFlag        = VOS_TRUE;
    pstImsaConfigPara->ucNoCardEmcCallSupportFlag   = VOS_FALSE;
    pstImsaConfigPara->ucUeRelMediaPdpFLag          = VOS_FALSE;
    pstImsaConfigPara->ucImsLocDeregSigPdpRelFlag   = VOS_TRUE;
    pstImsaConfigPara->enVoiceDomain                = IMSA_VOICE_DOMAIN_IMS_PS_PREFERRED;
    pstImsaConfigPara->stCMCCCustomReq.ucCMCCCustomDeregFlag        = VOS_FALSE;
    pstImsaConfigPara->stCMCCCustomReq.ucCMCCCustomTcallFlag        = VOS_FALSE;
    pstImsaConfigPara->stCMCCCustomReq.ucCMCCCustomTqosFlag         = VOS_FALSE;
}

/*****************************************************************************
 Function Name  : IMSA_CONTROL_InitConfigPara
 Description    : IMSA 总控模块初始化配置信息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONTROL_InitNetworkInfo( VOS_VOID )
{
    IMSA_NETWORK_INFO_STRU             *pstImsaNetworkInfo = VOS_NULL_PTR;

    pstImsaNetworkInfo = IMSA_GetNetInfoAddress();

    pstImsaNetworkInfo->enImsaCampedRatType   = IMSA_CAMPED_RAT_TYPE_NULL;
    pstImsaNetworkInfo->enImsaImsVoPsStatus   = IMSA_IMS_VOPS_STATUS_BUTT;
    pstImsaNetworkInfo->enImsaEmsStatus       = IMSA_EMS_STAUTS_BUTT;
    pstImsaNetworkInfo->enImsaPsServiceStatus = IMSA_PS_SERVICE_STATUS_NO_SERVICE;
    pstImsaNetworkInfo->ucImsaRoamingFlg      = VOS_FALSE;
}


/*****************************************************************************
 Function Name  : IMSA_CONTROL_Init
 Description    : IMSA 总控模块的初始化
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONTROL_Init( VOS_VOID )
{
    IMSA_CONTROL_MANAGER_STRU          *pstImsaControlManager   = VOS_NULL_PTR;
    IMSA_SUBSCRIPTION_INFO_LIST_STRU   *pstSubcriptionInfoList  = VOS_NULL_PTR;

    pstSubcriptionInfoList  = IMSA_GetSubcriptionInfoListAddr();
    pstImsaControlManager   = IMSA_GetControlManagerAddress();

    IMSA_MEM_SET_S( pstImsaControlManager,
                    sizeof(IMSA_CONTROL_MANAGER_STRU),
                    0x0,
                    sizeof(IMSA_CONTROL_MANAGER_STRU));

    pstImsaControlManager->enImsaStatus                 = IMSA_STATUS_NULL;
    pstImsaControlManager->enImsaIsimStatus             = IMSA_ISIM_STATUS_ABSENT;

    /* 初始化保护定时器 */
    pstImsaControlManager->stProtectTimer.phTimer       = VOS_NULL_PTR;
    pstImsaControlManager->stProtectTimer.ucMode        = VOS_RELTIMER_NOLOOP;
    pstImsaControlManager->stProtectTimer.usName        = TI_IMSA_START_OR_STOP;
    pstImsaControlManager->stProtectTimer.ulTimerLen    = TI_IMSA_START_OR_STOP_TIMER_LEN;

    /* 初始化配置信息 */
    IMSA_CONTROL_InitConfigPara();

    /* 初始化网络信息 */
    IMSA_CONTROL_InitNetworkInfo();

    /* 初始化周期性尝试IMS服务定时器 */
    pstImsaControlManager->stPeriodImsSrvTryTimer.phTimer   = VOS_NULL_PTR;
    pstImsaControlManager->stPeriodImsSrvTryTimer.usName    = TI_IMSA_PERIOD_TRY_IMS_SRV;
    pstImsaControlManager->stPeriodImsSrvTryTimer.ucMode    = VOS_RELTIMER_NOLOOP;
    pstImsaControlManager->stPeriodImsSrvTryTimer.ulTimerLen= TI_IMSA_PERIOD_IMS_SRV_TRY_TIMER_LEN;
    pstImsaControlManager->stPeriodImsSrvTryTimer.usPara    = (VOS_UINT16)IMSA_SRV_TYPE_NORMAL;

    pstImsaControlManager->stTempForbiddenTimer.phTimer     = VOS_NULL_PTR;
    pstImsaControlManager->stTempForbiddenTimer.usName      = TI_IMSA_TEMP_FORBIDDEN_TIMER;
    pstImsaControlManager->stTempForbiddenTimer.ucMode      = VOS_RELTIMER_NOLOOP;
    pstImsaControlManager->stTempForbiddenTimer.ulTimerLen  = LMM_Get3402TimerLen();
    pstImsaControlManager->stTempForbiddenTimer.usPara      = (VOS_UINT16)IMSA_SRV_TYPE_NORMAL;

    /* delete PeriodImsEmcSrvTryTimer */

    pstImsaControlManager->enNrmSrvStatus   = IMSA_SRV_STATUS_IDLE_DEREG;
    pstImsaControlManager->enEmcSrvStatus   = IMSA_SRV_STATUS_IDLE_DEREG;

    pstImsaControlManager->enDeregCause     = IMSA_SRV_DEREG_CAUSE_BUTT;
    pstImsaControlManager->ucIsImsRegForbidden = IMSA_FALSE;
    /* 初始化上次普通注册状态 */
    pstSubcriptionInfoList->enLastNrmRegStatus  = IMSA_NORMAL_REG_STATUS_DEREG;

    /* 初始化上次普通AT注册状态 */
    pstSubcriptionInfoList->enLastNrmAtRegStatus  = IMSA_NORMAL_AT_REG_STATUS_DEREG;

    pstImsaControlManager->stGetSerProtectTimer.phTimer         = VOS_NULL_PTR;
    pstImsaControlManager->stGetSerProtectTimer.ucMode          = VOS_RELTIMER_NOLOOP;
    pstImsaControlManager->stGetSerProtectTimer.usName          = TI_IMSA_GET_SERVICE_PROTECT_TIMER;
    pstImsaControlManager->stGetSerProtectTimer.ulTimerLen      = TI_IMSA_GET_SERVICE_PROTECT_TIMER_LEN;

    pstImsaControlManager->stDeregSerProtectTimer.phTimer       = VOS_NULL_PTR;
    pstImsaControlManager->stDeregSerProtectTimer.ucMode        = VOS_RELTIMER_NOLOOP;
    pstImsaControlManager->stDeregSerProtectTimer.usName        = TI_IMSA_DEREG_SERVICE_PROTECT_TIMER;
    pstImsaControlManager->stDeregSerProtectTimer.ulTimerLen    = TI_IMSA_DEREG_SERVICE_PROTECT_TIMER_LEN;
    return ;
}

/*****************************************************************************
 Function Name  : IMSA_CONTROL_ClearResource
 Description    : IMSA 总控模块的清除资源
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-23  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONTROL_ClearResource( VOS_VOID )
{
    IMSA_CONTROL_MANAGER_STRU          *pstImsaControlManager   = VOS_NULL_PTR;
    IMSA_SUBSCRIPTION_INFO_LIST_STRU   *pstSubcriptionInfoList  = VOS_NULL_PTR;

    pstSubcriptionInfoList  = IMSA_GetSubcriptionInfoListAddr();
    pstImsaControlManager   = IMSA_GetControlManagerAddress();

    /* 如果注册状态发生变更，需要上报上层注册状态 */
    IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);
    IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_IDLE_DEREG);

    pstImsaControlManager->enImsaStatus                 = IMSA_STATUS_NULL;
    pstImsaControlManager->enIsImsSrvExist              = IMSA_SRV_CONN_STATUS_ISNOT_EXIST;
    pstImsaControlManager->enStopType                   = MSCC_IMSA_STOP_TYPE_BUTT;
    /* 停止保护定时器 */
    IMSA_StopTimer(&pstImsaControlManager->stProtectTimer);
    pstImsaControlManager->stProtectTimer.phTimer       = VOS_NULL_PTR;
    pstImsaControlManager->stProtectTimer.ucMode        = VOS_RELTIMER_NOLOOP;
    pstImsaControlManager->stProtectTimer.usName        = TI_IMSA_START_OR_STOP;
    pstImsaControlManager->stProtectTimer.ulTimerLen    = TI_IMSA_START_OR_STOP_TIMER_LEN;

    /* 初始化网络信息 */
    IMSA_CONTROL_InitNetworkInfo();

    /* 停止周期性尝试IMS服务定时器 */
    IMSA_StopTimer(&pstImsaControlManager->stPeriodImsSrvTryTimer);
    pstImsaControlManager->stPeriodImsSrvTryTimer.phTimer   = VOS_NULL_PTR;
    pstImsaControlManager->stPeriodImsSrvTryTimer.usName    = TI_IMSA_PERIOD_TRY_IMS_SRV;
    pstImsaControlManager->stPeriodImsSrvTryTimer.ucMode    = VOS_RELTIMER_NOLOOP;
    pstImsaControlManager->stPeriodImsSrvTryTimer.ulTimerLen= TI_IMSA_PERIOD_IMS_SRV_TRY_TIMER_LEN;
    pstImsaControlManager->stPeriodImsSrvTryTimer.usPara    = (VOS_UINT16)IMSA_SRV_TYPE_NORMAL;

    IMSA_StopTimer(&pstImsaControlManager->stTempForbiddenTimer);
    pstImsaControlManager->stTempForbiddenTimer.phTimer     = VOS_NULL_PTR;
    pstImsaControlManager->stTempForbiddenTimer.usName      = TI_IMSA_TEMP_FORBIDDEN_TIMER;
    pstImsaControlManager->stTempForbiddenTimer.ucMode      = VOS_RELTIMER_NOLOOP;
    pstImsaControlManager->stTempForbiddenTimer.ulTimerLen  = LMM_Get3402TimerLen();
    pstImsaControlManager->stTempForbiddenTimer.usPara      = (VOS_UINT16)IMSA_SRV_TYPE_NORMAL;

    /* delete PeriodImsEmcSrvTryTimer */

    pstImsaControlManager->enNrmSrvStatus   = IMSA_SRV_STATUS_IDLE_DEREG;
    pstImsaControlManager->enEmcSrvStatus   = IMSA_SRV_STATUS_IDLE_DEREG;

    pstImsaControlManager->enDeregCause     = IMSA_SRV_DEREG_CAUSE_BUTT;

    pstImsaControlManager->ucIsImsRegForbidden = IMSA_FALSE;

    IMSA_MEM_SET_S( &pstImsaControlManager->stImsaIntraMsgQueue,
                    sizeof(IMSA_INTRA_MSG_QUEUE_STRU),
                    0x0,
                    sizeof(IMSA_INTRA_MSG_QUEUE_STRU));

    /* 初始化上次普通注册状态 */
    pstSubcriptionInfoList->enLastNrmRegStatus  = IMSA_NORMAL_REG_STATUS_DEREG;

    /* 初始化上次普通AT注册状态 */
    pstSubcriptionInfoList->enLastNrmAtRegStatus  = IMSA_NORMAL_AT_REG_STATUS_DEREG;

    pstImsaControlManager->stImsaCommonInfo.stImsaUeId.bitOpImpi = IMSA_OP_FALSE;

    IMSA_MEM_SET_S( &pstImsaControlManager->stImsaCommonInfo.stImsaUeId.stImpi,
                    sizeof(IMSA_IMPI_STRU),
                    0,
                    IMSA_MAX_IMPI_LEN +1);


    pstImsaControlManager->stImsaCommonInfo.stImsaUeId.bitOpTImpu = IMSA_OP_FALSE;

    IMSA_MEM_SET_S( &pstImsaControlManager->stImsaCommonInfo.stImsaUeId.stTImpu,
                    sizeof(IMSA_TIMPU_STRU),
                    0,
                    IMSA_MAX_TIMPU_LEN+1);

    pstImsaControlManager->stImsaCommonInfo.bitOpHomeNetDomainName = IMSA_OP_FALSE;

    IMSA_MEM_SET_S( &pstImsaControlManager->stImsaCommonInfo.stHomeNetDomainName,
                    sizeof(IMSA_HOME_NET_DOMAIN_NAME_STRU),
                    0,
                    IMSA_MAX_HOME_NET_DOMAIN_NAME_LEN +1);


    pstImsaControlManager->ucIsCardLocked = IMSA_FALSE;

    return ;
}


/*****************************************************************************
 Function Name  : IMSA_SRV_RatFormatTransform
 Description    : 接入技术格式转换
 Input          : penImsaRat------------IMSA接入技术指针
                  enMmaRat--------------MMA接入技术
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-04  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_RatFormatTransform
(
    IMSA_CAMPED_RAT_TYPE_ENUM_UINT8    *penImsaRat,
    MSCC_IMSA_RAT_TYPE_ENUM_UINT8        enMmaRat
)
{
    if (MSCC_IMSA_RAT_TYPE_GSM == enMmaRat)
    {
        *penImsaRat = IMSA_CAMPED_RAT_TYPE_GSM;
    }
    else if (MSCC_IMSA_RAT_TYPE_UTRAN == enMmaRat)
    {
        *penImsaRat = IMSA_CAMPED_RAT_TYPE_UTRAN;
    }
    else if (MSCC_IMSA_RAT_TYPE_LTE == enMmaRat)
    {
        *penImsaRat = IMSA_CAMPED_RAT_TYPE_EUTRAN;
    }
    else
    {
        IMSA_WARN_LOG("IMSA_SRV_RatFormatTransform:illegal rat type");
        TLPS_PRINT2LAYER_WARNING(IMSA_SRV_RatFormatTransform_ENUM, LNAS_PARAM_INVALID);
        *penImsaRat = IMSA_CAMPED_RAT_TYPE_NULL;
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_IsCurRatSupportIms
 Description    : 当前接入技术是否支持IMS特性
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-04  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_SRV_IsCurRatSupportIms( VOS_VOID )
{
    IMSA_NETWORK_INFO_STRU             *pstImsaNwInfo       = VOS_NULL_PTR;
    IMSA_CONFIG_PARA_STRU              *pstImsaConfigPara   = VOS_NULL_PTR;

    pstImsaNwInfo       = IMSA_GetNetInfoAddress();
    pstImsaConfigPara   = IMSA_GetConfigParaAddress();

    if ((IMSA_CAMPED_RAT_TYPE_GSM == pstImsaNwInfo->enImsaCampedRatType)
        && (VOS_TRUE == pstImsaConfigPara->ucGsmImsSupportFlag))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsCurRatSupportIms:GSM support ims!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsCurRatSupportIms_ENUM, 1);
        return IMSA_TRUE;
    }

    if ((IMSA_CAMPED_RAT_TYPE_UTRAN == pstImsaNwInfo->enImsaCampedRatType)
        && (VOS_TRUE == pstImsaConfigPara->ucUtranImsSupportFlag))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsCurRatSupportIms:UNTRAN support ims!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsCurRatSupportIms_ENUM, 2);
        return IMSA_TRUE;
    }

    if ((IMSA_CAMPED_RAT_TYPE_EUTRAN == pstImsaNwInfo->enImsaCampedRatType)
        && (VOS_TRUE == pstImsaConfigPara->ucLteImsSupportFlag))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsCurRatSupportIms:LTE support ims!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsCurRatSupportIms_ENUM, 3);
        return IMSA_TRUE;
    }

    return IMSA_FALSE;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_IsCurRatSupportEms
 Description    : 当前接入技术是否支持EMS特性
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-05  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_SRV_IsCurRatSupportEms( VOS_VOID )
{
    IMSA_NETWORK_INFO_STRU             *pstImsaNwInfo       = VOS_NULL_PTR;
    IMSA_CONFIG_PARA_STRU              *pstImsaConfigPara   = VOS_NULL_PTR;

    pstImsaNwInfo       = IMSA_GetNetInfoAddress();
    pstImsaConfigPara   = IMSA_GetConfigParaAddress();

    if ((IMSA_CAMPED_RAT_TYPE_GSM == pstImsaNwInfo->enImsaCampedRatType)
        && (VOS_TRUE == pstImsaConfigPara->ucGsmEmsSupportFlag))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsCurRatSupportEms:GSM support Ems!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsCurRatSupportEms_ENUM, 1);
        return IMSA_TRUE;
    }

    if ((IMSA_CAMPED_RAT_TYPE_UTRAN == pstImsaNwInfo->enImsaCampedRatType)
        && (VOS_TRUE == pstImsaConfigPara->ucUtranEmsSupportFlag))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsCurRatSupportIms:UNTRAN support Ems!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsCurRatSupportEms_ENUM, 2);
        return IMSA_TRUE;
    }

    if ((IMSA_CAMPED_RAT_TYPE_EUTRAN == pstImsaNwInfo->enImsaCampedRatType)
        && (VOS_TRUE == pstImsaConfigPara->ucLteEmsSupportFlag))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsCurRatSupportIms:LTE support Ems!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsCurRatSupportEms_ENUM, 3);
        return IMSA_TRUE;
    }

    return IMSA_FALSE;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_IsNrmSrvIsimParaSatisfied
 Description    : 获取IMS普通服务的ISIM参数是否具备
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-04  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_SRV_IsNrmSrvIsimParaSatisfied( VOS_VOID )
{
    IMSA_COMMON_INFO_STRU              *pstImsaCommonInfo = VOS_NULL_PTR;
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    /* 判断USIM卡状态是否正常 */
    pstControlMagnaer                       = IMSA_GetControlManagerAddress();
    if (IMSA_PS_SIMM_INVALID == pstControlMagnaer->ucImsaUsimStatus)
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvIsimParaSatisfied:USIM not available!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvIsimParaSatisfied_ENUM, 1);
        return IMSA_FALSE;
    }

    if (IMSA_ISIM_STATUS_AVAILABLE != IMSA_GetIsimStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvIsimParaSatisfied:ISIM not available!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvIsimParaSatisfied_ENUM, 2);
        return IMSA_FALSE;
    }

    pstImsaCommonInfo = IMSA_GetCommonInfoAddress();
    if (IMSA_OP_TRUE != pstImsaCommonInfo->bitOpHomeNetDomainName)
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvIsimParaSatisfied:No home network domain name!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvIsimParaSatisfied_ENUM, 3);
        return IMSA_FALSE;
    }

    if (IMSA_OP_TRUE != pstImsaCommonInfo->stImsaUeId.bitOpImpi)
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvIsimParaSatisfied:No impi!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvIsimParaSatisfied_ENUM, 4);
        return IMSA_FALSE;
    }

    if (IMSA_OP_TRUE != pstImsaCommonInfo->stImsaUeId.bitOpTImpu)
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvIsimParaSatisfied:No temporary IMPU!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvIsimParaSatisfied_ENUM, 5);
        return IMSA_FALSE;
    }

    if (IMSA_TRUE == pstControlMagnaer->ucIsCardLocked)
    {
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvIsimParaSatisfied_ENUM, 6);
        return IMSA_FALSE;
    }

    return IMSA_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_IsNrmSrvConditonSatisfied
 Description    : 获取IMS普通服务的条件是否具备
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-04  Draft Enact
      2.wangchen 00209181    2015-06-23  Modify:volte
*****************************************************************************/
IMSA_NRM_SRV_CON_SAT_STATUE_ENMUM_UINT32 IMSA_SRV_IsNrmSrvConditonSatisfied( VOS_VOID )
{
    /* 当前接入技术支持IMS特性 */
    if (IMSA_FALSE == IMSA_SRV_IsCurRatSupportIms())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvConditonSatisfied:cur rat not support ims!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvConditonSatisfied_ENUM, 1);
        return IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_RAT_NOT_SUPPORT;
    }

    /* IMS语音不支持，则返回条件不满足 */
    if ((IMSA_VOICE_DOMAIN_CS_ONLY == IMSA_GetVoiceDomain())
            || (VOS_FALSE == IMSA_GetUeImsVoiceCap())
            || (IMSA_IMS_VOPS_STATUS_NOT_SUPPORT == IMSA_GetNwImsVoiceCap()))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvConditonSatisfied:voice not support!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvConditonSatisfied_ENUM, 2);
        return IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_VOICE_NOT_SUPPORT;
    }

    /* PS域服务状态为正常服务 */
    if (IMSA_PS_SERVICE_STATUS_NORMAL_SERVICE != IMSA_GetPsServiceStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvConditonSatisfied:Ps service not normal!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvConditonSatisfied_ENUM, 3);
        return IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_OTHERS;
    }


    /* 如果是在漫游网络下，且UE设置为不支持漫游网络下的注册，则直接退出，并且通知MMA VOICE不可用 */
    if ((VOS_TRUE == IMSA_GetNetInfoAddress()->ucImsaRoamingFlg) &&
        (VOS_TRUE == IMSA_GetConfigParaAddress()->ucRoamingImsNotSupportFlag))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvConditonSatisfied:Roaming and not support !");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvConditonSatisfied_ENUM, 4);
        return IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_ROAM_NOT_SUPPORT;
    }


    /* 卡状态为有效可用，且IMPI、IMPU，DOMAIN参数有效 */
    if (IMSA_TRUE != IMSA_SRV_IsNrmSrvIsimParaSatisfied())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvConditonSatisfied:ISIM PARA not satisfied!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvConditonSatisfied_ENUM, 5);
        return IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_USIM_NOT_SUPPORT;
    }

    /* IMS注册被禁止 */
    if (IMSA_TRUE == IMSA_GetIsImsRegForbidden())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvConditonSatisfied:IMS reg forbidden!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvConditonSatisfied_ENUM, 6);
        return IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_REG_FORBIDDEN;
    }

    /* Pnd临时被拒惩罚定时器运行时返回注册被拒 */
    if (VOS_TRUE == IMSA_IsTempForbTimerRunning())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvConditonSatisfied:Forb Timer Running!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvConditonSatisfied_ENUM, 7);
        return IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_REG_FORBIDDEN;
    }

    return IMSA_NRM_SRV_CON_SAT_STATUE_SUCC;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied
 Description    : 在NORMAL SERVICE发起紧急呼的条件是否具备
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-05  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied( VOS_VOID )
{
    IMSA_NETWORK_INFO_STRU             *pstImsaNwInfo       = VOS_NULL_PTR;

    pstImsaNwInfo       = IMSA_GetNetInfoAddress();

    /* 是否在HPLMN上 */
    if (VOS_TRUE == pstImsaNwInfo->ucImsaRoamingFlg)
    {
        IMSA_INFO_LOG("IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied:NOT HPLMN!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied_ENUM, 1);
        return IMSA_FALSE;
    }

    /* 正常服务是否已注册成功 */
    if (IMSA_SRV_STATUS_CONN_REG != IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied:normal service not reg!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied_ENUM, 2);
        return IMSA_FALSE;
    }

    /* 定义了紧急呼承载且网侧支持建紧急承载 */
    if ((IMSA_TRUE == IMSA_CONN_IsEmcPdpDefined())
        && (IMSA_EMS_STAUTS_SUPPORT == pstImsaNwInfo->enImsaEmsStatus))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied:defined emc pdp and nw support emc bearer!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied_ENUM, 3);

        return IMSA_FALSE;
    }

    return IMSA_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_IsEmcSrvConditonSatisfied
 Description    : 获取IMS紧急服务的条件是否具备
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-05  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_SRV_IsEmcSrvConditonSatisfied( VOS_VOID )
{
    IMSA_NETWORK_INFO_STRU             *pstImsaNwInfo       = VOS_NULL_PTR;
    IMSA_CONFIG_PARA_STRU              *pstImsaConfigPara   = VOS_NULL_PTR;

    pstImsaNwInfo       = IMSA_GetNetInfoAddress();
    pstImsaConfigPara   = IMSA_GetConfigParaAddress();

    /* 当前接入技术支持IMS特性 */
    if (IMSA_FALSE == IMSA_SRV_IsCurRatSupportIms())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsEmcSrvConditonSatisfied:cur rat not support ims!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsEmcSrvConditonSatisfied_ENUM, 1);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( IMSA_CALL_TYPE_EMC,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NONE,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_CUR_RAT_NOT_SUPPORT_IMS,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_FALSE;
    }

    /* 当前接入技术支持EMS特性 */
    if (IMSA_FALSE == IMSA_SRV_IsCurRatSupportEms())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsEmcSrvConditonSatisfied:cur rat not support Ems!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsEmcSrvConditonSatisfied_ENUM, 2);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( IMSA_CALL_TYPE_EMC,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NONE,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_CUR_RAT_NOT_SUPPORT_EMC_IMS,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_FALSE;
    }

    /* UE是否支持语音 */
    if (VOS_FALSE == IMSA_GetUeImsVoiceCap())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsEmcSrvConditonSatisfied:ue not support voice!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsEmcSrvConditonSatisfied_ENUM, 3);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( IMSA_CALL_TYPE_EMC,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NONE,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_UE_CAP_NOT_SUPPORT_VOICE_CALL,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_FALSE;
    }

    /* 能否在正常服务下打紧急呼 */
    if (IMSA_TRUE == IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsEmcSrvConditonSatisfied:can make emc call in normal service!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsEmcSrvConditonSatisfied_ENUM, 4);
        return IMSA_TRUE;
    }

    /* 能否打无卡紧急呼 */
    if ((IMSA_FALSE == IMSA_SRV_IsNrmSrvIsimParaSatisfied())
        && (VOS_FALSE == pstImsaConfigPara->ucNoCardEmcCallSupportFlag))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsEmcSrvConditonSatisfied:not support anonymous emc call!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsEmcSrvConditonSatisfied_ENUM, 5);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( IMSA_CALL_TYPE_EMC,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NONE,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_CANNOT_MAKE_NOCAR_EMC_CALL,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_FALSE;
    }

    /* 网侧是否支持建紧急承载 */
    if (IMSA_EMS_STAUTS_NOT_SUPPORT == pstImsaNwInfo->enImsaEmsStatus)
    {
        IMSA_INFO_LOG("IMSA_SRV_IsEmcSrvConditonSatisfied:nw not support emc bearer!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsEmcSrvConditonSatisfied_ENUM, 6);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( IMSA_CALL_TYPE_EMC,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NONE,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NW_NOT_SUPPORT_EMC_BEAR,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif

        return IMSA_FALSE;
    }

    return IMSA_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_GetRegStatusFromSrvStatus
 Description    : 根据服务状态，获取正常注册状态
 Input          : enSrvStatus-----------服务状态
 Output         : VOS_VOID
 Return Value   : IMSA_NORMAL_REG_STATUS_ENUM_UINT32

 History        :
      1.lihong 00150010      2013-06-28  Draft Enact
*****************************************************************************/
IMSA_NORMAL_REG_STATUS_ENUM_UINT32 IMSA_SRV_GetRegStatusFromSrvStatus
(
    IMSA_SRV_STATUS_ENUM_UINT8          enSrvStatus
)
{
    switch (enSrvStatus)
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:
        /* case IMSA_SRV_STATUS_CONNING_DEREG: */
        case IMSA_SRV_STATUS_RELEASING_DEREG:
        case IMSA_SRV_STATUS_CONN_DEREG:

            return IMSA_NORMAL_REG_STATUS_DEREG;

        case IMSA_SRV_STATUS_CONN_DEREGING:

            return IMSA_NORMAL_REG_STATUS_DEREGING;

        case IMSA_SRV_STATUS_CONN_REGING:
        case IMSA_SRV_STATUS_CONNING_DEREG:
        case IMSA_SRV_STATUS_CONNING_REG:
            return IMSA_NORMAL_REG_STATUS_REGING;

        default:

            return IMSA_NORMAL_REG_STATUS_REG;
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_GetAtRegStatusFromSrvStatus
 Description    : 根据服务状态，获取正常AT注册状态
 Input          : enSrvStatus-----------服务状态
 Output         : VOS_VOID
 Return Value   : IMSA_NORMAL_REG_STATUS_ENUM_UINT32

 History        :
      1.leili 00132387      2013-10-14  Draft Enact
*****************************************************************************/
IMSA_NORMAL_AT_REG_STATUS_ENUM_UINT32 IMSA_SRV_GetAtRegStatusFromSrvStatus
(
    IMSA_SRV_STATUS_ENUM_UINT8          enSrvStatus
)
{
    switch (enSrvStatus)
    {
        case IMSA_SRV_STATUS_CONNING_REG:
        case IMSA_SRV_STATUS_CONN_REG:

            return IMSA_NORMAL_AT_REG_STATUS_REG;

        default:

            return IMSA_NORMAL_AT_REG_STATUS_DEREG;
    }
}


/*****************************************************************************
 Function Name  : IMSA_SRV_IsSrvStatusEqual
 Description    : 判断服务状态是否与入参相同
 Input          : enConnType-------------连接类型
                  enTimerId--------------定时器类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-08  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_SRV_IsSrvStatusEqual
(
    IMSA_SRV_TYPE_ENUM_UINT8            enSrvType,
    IMSA_SRV_STATUS_ENUM_UINT8          enImsaSrvStatus
)
{
    IMSA_SRV_STATUS_ENUM_UINT8          enImsaSrvStatusTmp = IMSA_SRV_STATUS_BUTT;

    if (IMSA_SRV_TYPE_NORMAL == enSrvType)
    {
        enImsaSrvStatusTmp = IMSA_SRV_GetNormalSrvStatus();
    }
    else
    {
        enImsaSrvStatusTmp = IMSA_SRV_GetEmcSrvStatus();
    }

    if (enImsaSrvStatus == enImsaSrvStatusTmp)
    {
        return IMSA_TRUE;
    }
    else
    {
        return IMSA_FALSE;
    }
}


/*****************************************************************************
 Function Name  : IMSA_SRV_SndConnSetupReq
 Description    : 发送内部消息ID_IMSA_CONN_SETUP_REQ
 Input          : enConnType----------------连接类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-04  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_SndConnSetupReq
(
    VOS_UINT32                          ulReEstablishFlag,
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType
)
{
    IMSA_CONN_SETUP_REQ_STRU           *pstConnSetupReq     = VOS_NULL_PTR;
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_SndConnSetupReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_SndConnSetupReq_ENUM, LNAS_ENTRY);

    /*分配空间并检验分配是否成功*/
    pstConnSetupReq = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_CONN_SETUP_REQ_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstConnSetupReq)
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SRV_SndConnSetupReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SRV_SndConnSetupReq_ENUM, LNAS_NULL_PTR);
        return ;
    }

    pstControlMagnaer  = IMSA_GetControlManagerAddress();
    /* 如果要建立的是普通连接，则停止周期性尝试IMS普通服务定时器 */
    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        IMSA_StopTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
    }

    /* delete PeriodImsEmcSrvTryTimer */


    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstConnSetupReq),
                    IMSA_GET_MSG_LENGTH(pstConnSetupReq),
                    0,
                    IMSA_GET_MSG_LENGTH(pstConnSetupReq));

    /*填写消息头*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstConnSetupReq,
                                ID_IMSA_CONN_SETUP_REQ,
                                sizeof(IMSA_CONN_SETUP_REQ_STRU));

    /*填写消息内容*/
    pstConnSetupReq->ulReEstablishFlag  = ulReEstablishFlag;
    pstConnSetupReq->enConnType     = enConnType;

    /*调用消息发送函数 */
    IMSA_SEND_INTRA_MSG(pstConnSetupReq);
}

/*****************************************************************************
 Function Name  : IMSA_SRV_SndConnRelReq
 Description    : 发送内部消息ID_IMSA_CONN_REL_REQ
 Input          : enConnType----------------连接类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-08  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_SndConnRelReq
(
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType
)
{
    IMSA_CONN_REL_REQ_STRU             *pstConnRelReq       = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_SndConnRelReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_SndConnRelReq_ENUM, LNAS_ENTRY);

    /*分配空间并检验分配是否成功*/
    pstConnRelReq = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_CONN_REL_REQ_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstConnRelReq)
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SRV_SndConnSetupReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SRV_SndConnRelReq_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstConnRelReq),
                    IMSA_GET_MSG_LENGTH(pstConnRelReq),
                    0,
                    IMSA_GET_MSG_LENGTH(pstConnRelReq));

    /*填写消息头*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstConnRelReq,
                                ID_IMSA_CONN_REL_REQ,
                                sizeof(IMSA_CONN_REL_REQ_STRU));

    /*填写消息内容*/
    pstConnRelReq->enConnType       = enConnType;
    pstConnRelReq->enSipPdpType     = enSipPdpType;

    /*调用消息发送函数 */
    IMSA_SEND_INTRA_MSG(pstConnRelReq);
}


/*****************************************************************************
 Function Name  : IMSA_SRV_SndRegRegReq
 Description    : 发送内部消息ID_IMSA_REG_REG_REQ
 Input          : enRegType-----------------注册类型
                  enAddrType----------------使用的地址对类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-04  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_SndRegRegReq
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType,
    IMSA_REG_ADDR_PARAM_ENUM_UINT32     enAddrType
)
{
    IMSA_REG_REG_REQ_STRU              *pstRegRegReq        = VOS_NULL_PTR;
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_SndRegRegReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_SndRegRegReq_ENUM, LNAS_ENTRY);

    /*分配空间并检验分配是否成功*/
    pstRegRegReq = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_REG_REG_REQ_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstRegRegReq)
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SRV_SndRegRegReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SRV_SndRegRegReq_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /* 关闭周期性尝试IMS服务定时器 */
    pstControlMagnaer  = IMSA_GetControlManagerAddress();

    if (IMSA_REG_TYPE_NORMAL == enRegType)
    {
        IMSA_StopTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
    }

    /* delete PeriodImsEmcSrvTryTimer */

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstRegRegReq),
                    IMSA_GET_MSG_LENGTH(pstRegRegReq),
                    0,
                    IMSA_GET_MSG_LENGTH(pstRegRegReq));

    /*填写消息头*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstRegRegReq,
                                ID_IMSA_REG_REG_REQ,
                                sizeof(IMSA_REG_REG_REQ_STRU));

    /*填写消息内容*/
    pstRegRegReq->enRegType     = enRegType;
    pstRegRegReq->enAddrType    = enAddrType;

    /*调用消息发送函数 */
    IMSA_SEND_INTRA_MSG(pstRegRegReq);
}

/*****************************************************************************
 Function Name  : IMSA_SRV_SndNrmCallSrvStatusInd
 Description    : 发送内部消息ID_IMSA_NRM_CALL_SRV_STATUS_IND
 Input          : enServiceStatus-----------------通知CALL模块的普通服务状态
                  enNoSrvCause--------------------无服务时指示原因值
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_SndNrmCallSrvStatusInd
(
    IMSA_CALL_SERVICE_STATUS_ENUM_UINT32       enCallSrvStatus,
    IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32         enNoSrvCause
)
{
    IMSA_NRM_CALL_SRV_STATUS_IND_STRU    *pstNrmCallSrvStatusInd = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_SndNrmCallSrvStatusInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_SndNrmCallSrvStatusInd_ENUM, LNAS_ENTRY);

    /*分配空间并检验分配是否成功*/
    pstNrmCallSrvStatusInd = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_NRM_CALL_SRV_STATUS_IND_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstNrmCallSrvStatusInd)
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SRV_SndNrmCallSrvStatusInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SRV_SndNrmCallSrvStatusInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstNrmCallSrvStatusInd),
                    IMSA_GET_MSG_LENGTH(pstNrmCallSrvStatusInd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstNrmCallSrvStatusInd));

    /*填写消息头*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstNrmCallSrvStatusInd,
                                ID_IMSA_NRM_CALL_SRV_STATUS_IND,
                                sizeof(IMSA_NRM_CALL_SRV_STATUS_IND_STRU));

    /*填写消息内容*/
    pstNrmCallSrvStatusInd->enCallSrvStatus = enCallSrvStatus;
    pstNrmCallSrvStatusInd->enNoSrvCause    = enNoSrvCause;

    /*调用消息发送函数 */
    IMSA_SEND_INTRA_MSG(pstNrmCallSrvStatusInd);
}

/*****************************************************************************
 Function Name  : IMSA_SRV_SndEmcCallSrvStatusInd
 Description    : 发送内部消息ID_IMSA_EMC_CALL_SRV_STATUS_IND
 Input          : enServiceStatus-----------------通知CALL模块的紧急服务状态
                  enNoSrvCause--------------------无服务时指示原因值
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_SndEmcCallSrvStatusInd
(
    IMSA_CALL_SERVICE_STATUS_ENUM_UINT32       enCallSrvStatus,
    IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32         enNoSrvCause
)
{
    IMSA_EMC_CALL_SRV_STATUS_IND_STRU     *pstEmcCallSrvStatusInd = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_SndEmcCallSrvStatusInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_SndEmcCallSrvStatusInd_ENUM, LNAS_ENTRY);

    /*分配空间并检验分配是否成功*/
    pstEmcCallSrvStatusInd = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_EMC_CALL_SRV_STATUS_IND_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstEmcCallSrvStatusInd)
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SRV_SndEmcCallSrvStatusInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SRV_SndEmcCallSrvStatusInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstEmcCallSrvStatusInd),
                    IMSA_GET_MSG_LENGTH(pstEmcCallSrvStatusInd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstEmcCallSrvStatusInd));

    /*填写消息头*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstEmcCallSrvStatusInd,
                                ID_IMSA_EMC_CALL_SRV_STATUS_IND,
                                sizeof(IMSA_EMC_CALL_SRV_STATUS_IND_STRU));

    /*填写消息内容*/
    pstEmcCallSrvStatusInd->enCallSrvStatus = enCallSrvStatus;
    pstEmcCallSrvStatusInd->enNoSrvCause    = enNoSrvCause;

    /*调用消息发送函数 */
    IMSA_SEND_INTRA_MSG(pstEmcCallSrvStatusInd);
}

/*****************************************************************************
 Function Name  : IMSA_SRV_SndRegDeregReq
 Description    : 发送内部消息ID_IMSA_REG_DEREG_REQ
 Input          : enDeRegType-----------------去注册类型
                  ulLocalFlag-----------------本地去注册标识
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-05  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_SndRegDeregReq
(
    IMSA_REG_TYPE_ENUM_UINT8            enDeRegType,
    VOS_UINT32                          ulLocalFlag
)
{
    IMSA_REG_DEREG_REQ_STRU            *pstRegDeregReq  = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_SndRegDeregReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_SndRegDeregReq_ENUM, LNAS_ENTRY);

    /*分配空间并检验分配是否成功*/
    pstRegDeregReq = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_REG_DEREG_REQ_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstRegDeregReq)
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SRV_SndRegRegReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SRV_SndRegDeregReq_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstRegDeregReq),
                    IMSA_GET_MSG_LENGTH(pstRegDeregReq),
                    0,
                    IMSA_GET_MSG_LENGTH(pstRegDeregReq));

    /*填写消息头*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstRegDeregReq,
                                ID_IMSA_REG_DEREG_REQ,
                                sizeof(IMSA_REG_DEREG_REQ_STRU));

    /*填写消息内容*/
    pstRegDeregReq->enDeRegType   = enDeRegType;
    pstRegDeregReq->ulLocalFlag   = ulLocalFlag;

    /*调用消息发送函数 */
    IMSA_SEND_INTRA_MSG(pstRegDeregReq);
}

/*****************************************************************************
 Function Name  : IMSA_SRV_SndNrmRegStatusNotify
 Description    : 发送内部消息ID_IMSA_NORMAL_REG_STATUS_NOTIFY
 Input          : pstSubsciptionInfo-----------------订阅信息指针
                  enNormalRegStatus------------------普通注册状态
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_SndNrmRegStatusNotify
(
    const IMSA_SUBSCRIPTION_INFO_STRU  *pstSubsciptionInfo,
    IMSA_NORMAL_REG_STATUS_ENUM_UINT32  enNormalRegStatus
)
{
    IMSA_NORMAL_REG_STATUS_NOTIFY_STRU     *pstNrmRegStatusNotify = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_SndNrmRegStatusNotify is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_SndNrmRegStatusNotify_ENUM, LNAS_ENTRY);

    /*分配空间并检验分配是否成功*/
    pstNrmRegStatusNotify = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_NORMAL_REG_STATUS_NOTIFY_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstNrmRegStatusNotify)
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SRV_SndNrmRegStatusNotify:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SRV_SndNrmRegStatusNotify_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstNrmRegStatusNotify),
                    IMSA_GET_MSG_LENGTH(pstNrmRegStatusNotify),
                    0,
                    IMSA_GET_MSG_LENGTH(pstNrmRegStatusNotify));

    /*填写消息头*/
    pstNrmRegStatusNotify->ulMsgId          = ID_IMSA_NORMAL_REG_STATUS_NOTIFY;
    pstNrmRegStatusNotify->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstNrmRegStatusNotify->ulSenderPid      = PS_PID_IMSA;
    pstNrmRegStatusNotify->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstNrmRegStatusNotify->ulReceiverPid    = pstSubsciptionInfo->ulPid;

    /* 填写消息内容 */
    pstNrmRegStatusNotify->enNormalRegStatus= enNormalRegStatus;
    pstNrmRegStatusNotify->ulPara           = pstSubsciptionInfo->ulPara;
    pstNrmRegStatusNotify->ulSubscriptionId = pstSubsciptionInfo->ulSubscriptionId;

    /*调用消息发送函数 */
    IMSA_SND_MSG(pstNrmRegStatusNotify);
}

/*****************************************************************************
 Function Name  : IMSA_SRV_NrmRegStatusNotify
 Description    : 将最新的普通注册状态通知订阅模块
 Input          : enNrmRegStatus-------------普通注册状态
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_NrmRegStatusNotify
(
    IMSA_NORMAL_REG_STATUS_ENUM_UINT32  enNrmRegStatus
)
{
    VOS_UINT32                          i                       = IMSA_NULL;
    IMSA_SUBSCRIPTION_INFO_LIST_STRU   *pstSubcriptionInfoList  = VOS_NULL_PTR;
    IMSA_SUBSCRIPTION_INFO_STRU        *pstSubcriptionInfo      = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_NrmRegStatusNotify is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_NrmRegStatusNotify_ENUM, LNAS_ENTRY);

    pstSubcriptionInfoList  = IMSA_GetSubcriptionInfoListAddr();

    for (i = 0; i < pstSubcriptionInfoList->ulSubscriptionNum; i++)
    {
        pstSubcriptionInfo = &pstSubcriptionInfoList->astSubcriptionInfoArray[i];
        if (IMSA_SUBCRIBE_TYPE_NORMAL_REG == pstSubcriptionInfo->enType)
        {
            IMSA_SRV_SndNrmRegStatusNotify(pstSubcriptionInfo, enNrmRegStatus);
        }
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_GetImsVoiceCapability
 Description    : 取得IMS VOICE能力可用或不可用
 Input          : penImsVoiceCap-------------IMS VOICE能力
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.xiongxianghui 00253310      2015-04-13  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_SRV_GetImsVoiceCapability(MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8 *penImsVoiceCap)
{
    VOS_UINT32                    ulResult           = IMSA_FALSE;
    IMSA_CONTROL_MANAGER_STRU     *pstControlMagnaer = VOS_NULL_PTR;

    pstControlMagnaer  = IMSA_GetControlManagerAddress();

    switch(IMSA_SRV_GetNormalSrvStatus())
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:
            if (VOS_FALSE == IMSA_IsTimerRunning(&pstControlMagnaer->stPeriodImsSrvTryTimer))
            {
                *penImsVoiceCap = MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE;
                ulResult = IMSA_TRUE;
            }
            break;
        case IMSA_SRV_STATUS_CONN_REG:
            if (IMSA_TRUE == IMSA_IsImsVoiceContidionSatisfied())
            {
                *penImsVoiceCap = MSCC_IMSA_IMS_VOICE_CAP_AVAILABLE;
            }
            else
            {
                *penImsVoiceCap = MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE;
            }
            ulResult = IMSA_TRUE;
            break;
        case IMSA_SRV_STATUS_CONN_DEREG:
            *penImsVoiceCap = MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE;
            ulResult = IMSA_TRUE;
            break;

        default:
            break;
    }

    return ulResult;
}


/*****************************************************************************
 Function Name  : IMSA_SRV_SetServcieStatus
 Description    : 设置服务状态
 Input          : enSrvType-------------服务类型
                  enSrvStatus-----------服务状态
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_SetServcieStatus
(
    IMSA_SRV_TYPE_ENUM_UINT8            enSrvType,
    IMSA_SRV_STATUS_ENUM_UINT8          enSrvStatus
)
{
    IMSA_NORMAL_REG_STATUS_ENUM_UINT32  enNrmRegStatus = IMSA_NORMAL_REG_STATUS_BUTT;
    IMSA_NORMAL_AT_REG_STATUS_ENUM_UINT32 enNrmAtRegStatus = IMSA_NORMAL_AT_REG_STATUS_BUTT;
    MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8  enImsVoiceCap = MSCC_IMSA_IMS_VOICE_CAP_BUTT;

    /* 获取服务原状态 */

    /* 打印服务类型 */

    /* 打印服务状态变更新信息 */

    if (IMSA_SRV_TYPE_EMC == enSrvType)
    {
        IMSA_SRV_GetEmcSrvStatus() = enSrvStatus;

        /* 如果取得IMS VOICE能力，则上报IMS VOICE能力 */
        if (IMSA_TRUE == IMSA_SRV_GetImsVoiceCapability(&enImsVoiceCap))
        {
            IMSA_SndMsccMsgImsVoiceCapNotify(enImsVoiceCap, IMSA_CONN_IsExitPersistentBearer());
        }
        return ;
    }

    /* 根据服务状态，获取普通注册状态 */
    enNrmRegStatus = IMSA_SRV_GetRegStatusFromSrvStatus(enSrvStatus);

    /* 如果普通注册状态发生变更，则通知签约的模块最新的普通注册状态 */
    if (enNrmRegStatus != IMSA_GetLastNrmRegStatus())
    {
        IMSA_SRV_NrmRegStatusNotify(enNrmRegStatus);

        IMSA_SetLastNrmRegStatus(enNrmRegStatus);
    }

    /* 根据服务状态，获取普通AT注册状态 */
    enNrmAtRegStatus = IMSA_SRV_GetAtRegStatusFromSrvStatus(enSrvStatus);

    IMSA_INFO_LOG2("IMSA_SRV_SetServcieStatus:enNrmAtRegStatus = ,IMSA_GetLastNrmAtRegStatus()=",
                   enNrmAtRegStatus,IMSA_GetLastNrmAtRegStatus());
    TLPS_PRINT2LAYER_INFO2(IMSA_SRV_SetServcieStatus_ENUM, 1, enNrmAtRegStatus, IMSA_GetLastNrmAtRegStatus());

    /* 如果普通AT注册状态发生变更，则通知AT最新的普通AT注册状态 */
    if (enNrmAtRegStatus != IMSA_GetLastNrmAtRegStatus())
    {
        IMSA_SndMsgAtCireguInd(enNrmAtRegStatus);

        IMSA_SetLastNrmAtRegStatus(enNrmAtRegStatus);
    }

    IMSA_SRV_GetNormalSrvStatus() = enSrvStatus;

    if (IMSA_SRV_STATUS_CONN_REG != IMSA_SRV_GetNormalSrvStatus())
    {
        /* SRVCC异常(例如关机，DEREG REQ，状态迁离CONN+REG)，清缓存 */
        IMSA_SrvccAbormalClearBuff(IMSA_SRVCC_ABNORMAL_STATUS_CHANGE);

        IMSA_SMS_ClearResource();

        IMSA_USSD_ClearResource();
    }

    /* 如果取得IMS VOICE能力，则上报IMS VOICE能力 */
    if (IMSA_TRUE == IMSA_SRV_GetImsVoiceCapability(&enImsVoiceCap))
    {
        IMSA_SndMsccMsgImsVoiceCapNotify(enImsVoiceCap, IMSA_CONN_IsExitPersistentBearer());
    }

}
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcConnSetupIndSucc
 Description    : IMSA内部消息ID_IMSA_CONN_SETUP_IND处理函数，连接建立成功
 Input          : pstConnSetupIndMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-08  Draft Enact
      2.lihong 00150010      2013-12-06  Modify:emc dedicated
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcConnSetupIndSucc
(
    const IMSA_CONN_SETUP_IND_STRU     *pstConnSetupIndMsg
)
{
    IMSA_CONTROL_MANAGER_STRU              *pstImsaControlManager   = VOS_NULL_PTR;
    VOS_CHAR                                acUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
    VOS_CHAR                                acPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};

    IMSA_INFO_LOG("IMSA_SRV_ProcConnSetupIndSucc is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcConnSetupIndSucc_ENUM, LNAS_ENTRY);

    pstImsaControlManager = IMSA_GetControlManagerAddress();

    /* 给CALL的服务状态发生变更才通知CALL;如果当前接入技术不支持IMS，则是无服务；
       当前接入技术支持IMS时，则增加如下判断:
       CONN REG有服务，CONN DEREG看是否是无卡
    如果是无卡则是有服务，否则是无服务；其他都是无服务,CALL模块收到无服务需要释放
    CALL。*/

    if (IMSA_CONN_SIP_PDP_TYPE_MEDIA == pstConnSetupIndMsg->enSipPdpType)
    {
        /* 通知CALL模块服务已经具备 */
        IMSA_ProcCallResourceIsReady(pstConnSetupIndMsg->enConnType, pstConnSetupIndMsg->enMediaPdpType);
        return ;
    }

    if (IMSA_CONN_TYPE_NORMAL == pstConnSetupIndMsg->enConnType)
    {
        IMSA_UtilStrNCpy(acUeAddr, pstImsaControlManager->stNrmRegParaInfo.acUeAddr, IMSA_IPV6_ADDR_STRING_LEN);
        IMSA_UtilStrNCpy(acPcscfAddr, pstImsaControlManager->stNrmRegParaInfo.acPcscfAddr, IMSA_IPV6_ADDR_STRING_LEN);
    }
    else
    {
        IMSA_UtilStrNCpy(acUeAddr, pstImsaControlManager->stEmcRegParaInfo.acUeAddr, IMSA_IPV6_ADDR_STRING_LEN);
        IMSA_UtilStrNCpy(acPcscfAddr, pstImsaControlManager->stEmcRegParaInfo.acPcscfAddr, IMSA_IPV6_ADDR_STRING_LEN);
    }
    /* 如果当前处于REG+CONNING状态 */
    if (IMSA_TRUE == IMSA_SRV_IsSrvStatusEqual((IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType,
                                                    IMSA_SRV_STATUS_CONNING_REG))
    {
        /* CR刷新 Issue A+Issue B+Issue C+Issue D: When the PDP context used for SIP signalling (EPS bearer context
           used for SIP signalling) is deactivated by procedures not triggered by UE and either the network requests
           reactivation or the UE desires or is required to be registered, then the UE performs the same procedures
           as at initially ensuring the PDP context used for SIP signalling (EPS bearer context used for SIP signalling).
           If the operation is successful, then the UE performs a new initial registration. */
        /* 如果备份的注册参数有效，则使用当前地址注册 */
        if (IMSA_TRUE == IMSA_IsRegParaAvailable((IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType,
                                                  acUeAddr,
                                                  acPcscfAddr))
        {
            /* Current地址对在去激活信令承载时已经被清除, 所以此时需要重新置上 */
            (VOS_VOID)IMSA_SetCurrentPara(pstConnSetupIndMsg->enConnType, acUeAddr, acPcscfAddr);

            IMSA_SRV_SetServcieStatus((IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType, IMSA_SRV_STATUS_CONN_REGING);

            IMSA_SRV_SndRegDeregReq((IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType, IMSA_DEREG_LOCAL);

            IMSA_SRV_SndRegRegReq((IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType, IMSA_REG_ADDR_PARAM_SAME);
        }
        else
        /* 如果备份的注册参数无效，则将本地去注册，并且通知REG模块重新发起注册 */
        {
            IMSA_SRV_SetServcieStatus((IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType, IMSA_SRV_STATUS_CONN_REGING);

            IMSA_SRV_SndRegDeregReq((IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType, IMSA_DEREG_LOCAL);

            IMSA_SRV_SndRegRegReq((IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType, IMSA_REG_ADDR_PARAM_NEW);


        }

        /* 切离CONNING+REG态时，IMSA需要通知IMS允许发包 */
        if (IMSA_CONN_TYPE_NORMAL == pstConnSetupIndMsg->enConnType)
        {
            IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV);
        }
        else
        {
            IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_EMC_SRV);
        }

        return;
    }

    /* 信令承载激活成功分支 */

    /* 如果不在CONNING&DEREG态，则直接退出 */
    if (IMSA_TRUE != IMSA_SRV_IsSrvStatusEqual( (IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType,
                                                IMSA_SRV_STATUS_CONNING_DEREG))
    {
        IMSA_WARN_LOG("IMSA_SRV_ProcConnSetupIndSucc:SRV status is not conningdereg!");
        TLPS_PRINT2LAYER_WARNING(IMSA_SRV_ProcConnSetupIndSucc_ENUM, IMSA_STATE_ERROR);
        return ;
    }

    if (IMSA_CONN_TYPE_EMC == pstConnSetupIndMsg->enConnType)
    {
        /* 如果是无卡紧急呼，则转到CONN&DEREG态，不再发起注册，通知CALL紧急
           服务具备;否则转到CONN&REGING态，请求REG模块发起紧急注册 */
        if (IMSA_FALSE == IMSA_SRV_IsNrmSrvIsimParaSatisfied())
        {
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_CONN_DEREG);

            /* 无卡紧急呼无需紧急注册，因此通知CALL模块紧急呼叫服务具备 */
            IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NORMAL_SERVICE,
                                            IMSA_CALL_NO_SRV_CAUSE_BUTT);
        }
        else
        {
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_CONN_REGING);

            IMSA_SRV_SndRegRegReq(IMSA_REG_TYPE_EMC, IMSA_REG_ADDR_PARAM_NEW);
        }
    }
    else
    {
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_REGING);

        IMSA_SRV_SndRegRegReq(IMSA_REG_TYPE_NORMAL, IMSA_REG_ADDR_PARAM_NEW);
    }

    return ;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcConnSetupIndFail
 Description    : IMSA内部消息ID_IMSA_CONN_SETUP_IND处理函数，连接建立失败
 Input          : pstConnSetupIndMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-08  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcConnSetupIndFail
(
    const IMSA_CONN_SETUP_IND_STRU     *pstConnSetupIndMsg
)
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_ProcConnSetupIndFail is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcConnSetupIndFail_ENUM, LNAS_ENTRY);

    pstControlMagnaer  = IMSA_GetControlManagerAddress();

    if (IMSA_CONN_SIP_PDP_TYPE_MEDIA == pstConnSetupIndMsg->enSipPdpType)
    {
        IMSA_WARN_LOG("IMSA_SRV_ProcConnSetupIndFail:can not happen when nw initiate pdp activation!");
        TLPS_PRINT2LAYER_WARNING(IMSA_SRV_ProcConnSetupIndFail_ENUM, 2);
        return ;
    }

    /* 信令承载激活失败分支 */
    /* 重建立流程处于REG+CONNING状态 */
    if ((IMSA_CONN_TYPE_NORMAL == pstConnSetupIndMsg->enConnType)
        && (IMSA_TRUE == IMSA_SRV_IsSrvStatusEqual(IMSA_SRV_TYPE_NORMAL,
                                                   IMSA_SRV_STATUS_CONNING_REG)))
    {
        /* 本地去注册 */
        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

        if (IMSA_CONN_RESULT_FAIL_PERM_FORBIDDEN == pstConnSetupIndMsg->enResult)
        {
            /* 永久被拒标志置上 */
            IMSA_SetIsImsRegForbidden(IMSA_TRUE);
        }
        else if (IMSA_CONN_RESULT_FAIL_TEMP_FORBIDDEN == pstConnSetupIndMsg->enResult)
        {
            /* 启动临时被拒惩罚定时器 */
            IMSA_StartTempForbTimer();
        }
        else
        {
            /* 启动周期性尝试定时器 */
            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
        }

        #if (FEATURE_ON == FEATURE_DSDS)
        if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
        {
            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
            IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
        }
        #endif
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_NormInitDeregErrRecord(IMSA_ERR_LOG_INIT_DEREG_REASON_PDN_LOST);
        #endif
        return;
    }

    if ((IMSA_CONN_TYPE_EMC == pstConnSetupIndMsg->enConnType)
        && (IMSA_TRUE == IMSA_SRV_IsSrvStatusEqual(IMSA_SRV_TYPE_EMC,
                                                   IMSA_SRV_STATUS_CONNING_REG)))
    {
        /* 本地去注册 */
        IMSA_SRV_SndRegDeregReq(IMSA_SRV_TYPE_EMC, IMSA_DEREG_LOCAL);
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_IDLE_DEREG);

        return;
    }

    /* 如果不在CONNING&DEREG态，则直接退出 */
    if (IMSA_TRUE != IMSA_SRV_IsSrvStatusEqual( (IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType,
                                                IMSA_SRV_STATUS_CONNING_DEREG))
    {
        IMSA_WARN_LOG("IMSA_SRV_ProcConnSetupIndFail:SRV status is not conningdereg!");
        TLPS_PRINT2LAYER_WARNING(IMSA_SRV_ProcConnSetupIndFail_ENUM, IMSA_STATE_ERROR);
        return ;
    }

    if (IMSA_CONN_TYPE_EMC == pstConnSetupIndMsg->enConnType)
    {
        /* 状态转到IDLE&DEREG态，通知CALL紧急服务不具备 */
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_IDLE_DEREG);

        /* 通知CALL模块紧急呼叫服务进入无服务状态，促使CALL模块清除缓存的紧急呼 */
        IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                        IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);
    }
    else
    {
        if ((IMSA_CONN_RESULT_FAIL_TIMER_EXP == pstConnSetupIndMsg->enResult)
            || (IMSA_CONN_RESULT_FAIL_CONN_RELEASING == pstConnSetupIndMsg->enResult)
            || (IMSA_CONN_RESULT_FAIL_SAME_APN_OPERATING == pstConnSetupIndMsg->enResult))
        {
            /* 启动周期性尝试IMS服务定时器 */
            IMSA_INFO_LOG("IMSA_SRV_ProcConnSetupIndFail:start period ims service tyr timer!");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcConnSetupIndFail_ENUM, 4);
            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
        }

        if (IMSA_CONN_RESULT_FAIL_PERM_FORBIDDEN == pstConnSetupIndMsg->enResult)
        {
            /* 永久被拒标志置上 */
            IMSA_SetIsImsRegForbidden(IMSA_TRUE);
        }

        if (IMSA_CONN_RESULT_FAIL_TEMP_FORBIDDEN == pstConnSetupIndMsg->enResult)
        {
            /* 启动临时被拒惩罚定时器 */
            IMSA_StartTempForbTimer();
        }

        /* 状态转到IDLE&DEREG态，通知CALL紧急服务不具备，由于IMSA_SRV_SetServcieStatus
           中会用到周期性尝试IMS服务定时器的运行情况，且当前处于注册过程中，
           所以需要先启动定时器后转状态 */
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

        #if (FEATURE_ON == FEATURE_DSDS)
        if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
        {
            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
            IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
        }
        #endif
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcRegRegIndSucc
 Description    : IMSA内部消息ID_IMSA_REG_REG_IND处理函数，注册成功
 Input          : pstRegRegIndMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-08  Draft Enact
      2.wangchen 00209181    2015-11-20  Modify:dsds
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcRegRegIndSucc
(
    const IMSA_REG_REG_IND_STRU        *pstRegRegIndMsg
)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU              *pstImsaControlManager   = IMSA_GetControlManagerAddress();
    #endif

    IMSA_INFO_LOG("IMSA_SRV_ProcRegRegIndSucc is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcRegRegIndSucc_ENUM, LNAS_ENTRY);

    /* 如果是正常服务，则状态转到CONN&REG态，通知CALL模块正常服务具备 */
    if (IMSA_REG_TYPE_NORMAL == pstRegRegIndMsg->enRegType)
    {
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_REG);

        /* 通知CALL模块普通呼叫服务进入有服务状态 */
        IMSA_SRV_SndNrmCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NORMAL_SERVICE,
                                        IMSA_CALL_NO_SRV_CAUSE_BUTT);

        #if (FEATURE_ON == FEATURE_DSDS)
        if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
        {
            IMSA_StopTimer(&pstImsaControlManager->stGetSerProtectTimer);
            IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
        }
        #endif

    }
    else
    {
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_CONN_REG);

        /* 通知CALL模块紧急呼叫服务进入有服务状态 */
        IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NORMAL_SERVICE,
                                        IMSA_CALL_NO_SRV_CAUSE_BUTT);
    }

    return ;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_SetImsRegForbidden
 Description    : 设置IMS注册禁止标识
 Input          : enRegType--------------注册类型
                  enResult---------------注册结果
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.xiongxianghui 00253310      2015-11-26  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_SetImsRegForbidden
(
    IMSA_REG_TYPE_ENUM_UINT8       enRegType,
    IMSA_REG_RESULT_ENUM_UINT32    enResult
)
{
    if (IMSA_REG_TYPE_NORMAL == enRegType)
    {
        if (IMSA_REG_RESULT_FAIL_FORBIDDEN == enResult)
        {
            IMSA_SetIsImsRegForbidden(IMSA_TRUE);
        }
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcRegRegIndFail
 Description    : IMSA内部消息ID_IMSA_REG_REG_IND处理函数，注册失败
 Input          : pstRegRegIndMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-08  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcRegRegIndFail
(
    const IMSA_REG_REG_IND_STRU        *pstRegRegIndMsg
)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU              *pstImsaControlManager   = IMSA_GetControlManagerAddress();
    #endif

    IMSA_INFO_LOG("IMSA_SRV_ProcRegRegIndFail is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcRegRegIndFail_ENUM, LNAS_ENTRY);

    switch (pstRegRegIndMsg->enResultAction)
    {
        case IMSA_RESULT_ACTION_NULL:

            IMSA_SRV_SetImsRegForbidden(pstRegRegIndMsg->enRegType,pstRegRegIndMsg->enResult);

            if (IMSA_REG_TYPE_EMC == pstRegRegIndMsg->enRegType)
            {
                /* 通知CALL模块紧急呼叫服务进入无服务状态，促使CALL模块清除缓存的紧急呼 */
                IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                                IMSA_CALL_NO_SRV_CAUSE_REG_ERR);
            }
            else
            {
                /* 只有普通类型的需要申请资源去注册，紧急的不需要，也不需要修改资源类型 */
                /* 使用注册的资源 */
                #if (FEATURE_ON == FEATURE_DSDS)
                if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
                {
                    IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG, RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

                    /* 修改资源的触发目的*/
                    IMSA_StopTimer(&pstImsaControlManager->stGetSerProtectTimer);
                    IMSA_StartTimer(&pstImsaControlManager->stDeregSerProtectTimer);
                }
                #endif
            }

            IMSA_SRV_SndConnRelReq((IMSA_CONN_TYPE_ENUM_UINT32)pstRegRegIndMsg->enRegType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            /* 后续不再注册，则释放连接，状态转到RELEASING&DEREG态 */
            IMSA_SRV_SetServcieStatus(  (IMSA_SRV_TYPE_ENUM_UINT8)pstRegRegIndMsg->enRegType,
                                        IMSA_SRV_STATUS_RELEASING_DEREG);
            break;
        case IMSA_RESULT_ACTION_REG_WITH_FIRST_ADDR_PAIR:

            IMSA_SRV_SndRegRegReq(pstRegRegIndMsg->enRegType, IMSA_REG_ADDR_PARAM_NEW);
            break;
        case IMSA_RESULT_ACTION_REG_WITH_CURRENT_ADDR_PAIR:

            IMSA_SRV_SndRegRegReq(pstRegRegIndMsg->enRegType, IMSA_REG_ADDR_PARAM_SAME);
            break;
        case IMSA_RESULT_ACTION_REG_WITH_NEXT_ADDR_PAIR:

            IMSA_SRV_SndRegRegReq(pstRegRegIndMsg->enRegType, IMSA_REG_ADDR_PARAM_NEXT);
            break;
        case IMSA_RESULT_ACTION_REG_LOCAL_DEREG:
            IMSA_SRV_SetServcieStatus((IMSA_SRV_TYPE_ENUM_UINT8)pstRegRegIndMsg->enRegType,
                                       IMSA_SRV_STATUS_CONN_DEREG);

            /* 切离CONN&REG态，因此通知CALL呼叫服务进入无服务状态 */
            IMSA_SRV_SndCallSrvStatusInd((IMSA_SRV_TYPE_ENUM_UINT8)pstRegRegIndMsg->enRegType,
                                          IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                          IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);

            if (IMSA_REG_TYPE_NORMAL == pstRegRegIndMsg->enRegType)
            {
                #if (FEATURE_ON == FEATURE_DSDS)
                if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
                {
                    IMSA_StopTimer(&pstImsaControlManager->stGetSerProtectTimer);
                    IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
                }
                #endif
            }

            break;
        /* 只有普通类型的注册失败，才会进入该分支；注册失败，retry after超时，申请资源失败*/
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESULT_ACTION_REG_NORF:
            IMSA_SRV_SetServcieStatus((IMSA_SRV_TYPE_ENUM_UINT8)pstRegRegIndMsg->enRegType,
                                       IMSA_SRV_STATUS_CONN_DEREG);

            /* 切离CONN&REG态，因此通知CALL呼叫服务进入无服务状态 */
            IMSA_SRV_SndCallSrvStatusInd((IMSA_SRV_TYPE_ENUM_UINT8)pstRegRegIndMsg->enRegType,
                                          IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                          IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);

            IMSA_StopTimer(&pstImsaControlManager->stGetSerProtectTimer);

            /* 通知RRM模块，将注册任务挂到RRM队列中 */
            IMSA_DsdsProcResourceRegisterInd(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                             IMSA_RF_RES_APPLY_TRIGER_SRC_REG_RETRY_EXP,
                                             IMSA_REG_ADDR_PARAM_SAME);
            break;
        #endif
        default:

            IMSA_INFO_LOG("IMSA_SRV_ProcRegRegIndFail:illegal result action!");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcRegRegIndFail_ENUM, LNAS_PARAM_INVALID);

            if (IMSA_REG_TYPE_EMC == pstRegRegIndMsg->enRegType)
            {
                /* 通知CALL模块紧急呼叫服务进入无服务状态，促使CALL模块清除缓存的紧急呼 */
                IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                                IMSA_CALL_NO_SRV_CAUSE_REG_ERR);
            }
            else
            {
                #if (FEATURE_ON == FEATURE_DSDS)
                if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
                {
                    IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG, RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

                    /* 修改资源的触发目的*/
                    IMSA_StopTimer(&pstImsaControlManager->stGetSerProtectTimer);
                    IMSA_StartTimer(&pstImsaControlManager->stDeregSerProtectTimer);
                }
                #endif
            }

            /* 后续不再注册，则释放连接，状态转到RELEASING&DEREG态 */
            IMSA_SRV_SndConnRelReq((IMSA_CONN_TYPE_ENUM_UINT32)pstRegRegIndMsg->enRegType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            IMSA_SRV_SetServcieStatus(  (IMSA_SRV_TYPE_ENUM_UINT8)pstRegRegIndMsg->enRegType,
                                        IMSA_SRV_STATUS_RELEASING_DEREG);
            break;
    }
}


/*****************************************************************************
 Function Name  : IMSA_SRV_ProcRegRegIndMsg
 Description    : IMSA内部消息ID_IMSA_REG_REG_IND处理函数
 Input          : pstRegRegIndMsg------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-24  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcRegRegIndMsg
(
    const IMSA_REG_REG_IND_STRU        *pstRegRegIndMsg
)
{
    IMSA_INFO_LOG("IMSA_SRV_ProcRegRegIndMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcRegRegIndMsg_ENUM, LNAS_ENTRY);

    /* 如果不在CONN&REGING态，则直接退出 */
    if (IMSA_TRUE != IMSA_SRV_IsSrvStatusEqual(     (IMSA_SRV_TYPE_ENUM_UINT8)pstRegRegIndMsg->enRegType,
                                                    IMSA_SRV_STATUS_CONN_REGING))
    {
        IMSA_WARN_LOG("IMSA_SRV_ProcRegRegIndMsg:Not conn&reging state!");
        TLPS_PRINT2LAYER_WARNING(IMSA_SRV_ProcRegRegIndMsg_ENUM, IMSA_STATE_ERROR);

        return ;
    }

    if (IMSA_REG_RESULT_SUCCESS == pstRegRegIndMsg->enResult)
    {
        IMSA_SRV_ProcRegRegIndSucc(pstRegRegIndMsg);
    }
    else
    {
        IMSA_SRV_ProcRegRegIndFail(pstRegRegIndMsg);
    }
}
/*****************************************************************************
 Function Name  : IMSA_SRV_RegConningStateProcRegDeregIndMsg
 Description    : REG+CONNING状态下，IMSA内部消息ID_IMSA_REG_DEREG_IND处理函数
 Input          : enRegType--------------注册类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2014-3-18  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_RegConningStateProcRegDeregIndMsg
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType
)
{
    IMSA_CONTROL_MANAGER_STRU          *pstImsaControlManager   = VOS_NULL_PTR;

    pstImsaControlManager   = IMSA_GetControlManagerAddress();

    if (IMSA_REG_TYPE_NORMAL == enRegType)
    {
        /* 等周期性尝试定时器超时 */
        if (VOS_TRUE == IMSA_IsTimerRunning(&pstImsaControlManager->stPeriodImsSrvTryTimer))
        {
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_IDLE_DEREG);
        }
        else
        {
            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);

            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONNING_DEREG);
        }
        IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV);

        return;
    }
    /* 紧急注册 */
    if (IMSA_REG_TYPE_EMC == enRegType)
    {
        /* delete PeriodImsEmcSrvTryTimer */
        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

        IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_EMC,
                                    IMSA_SRV_STATUS_CONNING_DEREG);

        IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_EMC_SRV);

        return;
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcRegDeregIndWithNextAddr
 Description    : IMSA内部消息ID_IMSA_REG_DEREG_IND处理函数
 Input          : pstRegDeregIndMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-30  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcRegDeregIndWithAddr
(
    IMSA_SRV_TYPE_ENUM_UINT8            enSrvType,
    VOS_UINT32                          ulPara
)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = IMSA_GetControlManagerAddress();
    #endif

    IMSA_SRV_SetServcieStatus(  enSrvType,
                                IMSA_SRV_STATUS_CONN_REGING);

    /* 切离CONN&REG态，因此通知CALL呼叫服务进入无服务状态 */
    IMSA_SRV_SndCallSrvStatusInd( enSrvType,
                                  IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                  IMSA_CALL_NO_SRV_CAUSE_REG_ERR);

    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:
            /* 进行初始注册，使用第一个地址对，状态转到CONN&REGING态 */
            IMSA_SRV_SndRegRegReq(      enSrvType,
                                        ulPara);

            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            }
            #endif
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_WAIT_STATUS_IND:
            /* 上报voice不可用 */
            IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE,IMSA_CONN_IsExitPersistentBearer());
            break;

        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_REREGISTER_FAIL,
                                          ulPara,
                                          IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_REREGISTER_FAIL,
                                          ulPara,
                                          IMSA_FALSE);

            IMSA_SRV_SndRegRegReq(  enSrvType,
                                    ulPara);

            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            }

            break;

        case IMSA_RESOURCE_STATUS_APPLYING:
            break;
        #endif
        default:
            /* 进行初始注册，使用第一个地址对，状态转到CONN&REGING态 */
            IMSA_SRV_SndRegRegReq(      enSrvType,
                                        ulPara);

            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            }
            #endif
            break;
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcRegDeregIndWithNextAddr
 Description    : IMSA内部消息ID_IMSA_REG_DEREG_IND处理函数
 Input          : pstRegDeregIndMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-30  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcRegDeregIndActionNull
(
    IMSA_SRV_TYPE_ENUM_UINT8            enSrvType
)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = IMSA_GetControlManagerAddress();
    #endif

    IMSA_SRV_SetServcieStatus(  enSrvType,
                                IMSA_SRV_STATUS_RELEASING_DEREG);

    /* 切离CONN&REG态，因此通知CALL呼叫服务进入无服务状态 */
    IMSA_SRV_SndCallSrvStatusInd( enSrvType,
                                  IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                  IMSA_CALL_NO_SRV_CAUSE_REG_ERR);

    /* 如果是紧急类型的失败，则直接通知TAF器激活承载，状态迁移至IDLE+dEREG */
    if (IMSA_SRV_TYPE_EMC == enSrvType)
    {
        IMSA_SRV_SndConnRelReq(enSrvType,
                                IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        IMSA_SRV_SetServcieStatus(  enSrvType,
                                    IMSA_SRV_STATUS_IDLE_DEREG);

        return;
    }

    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
                IMSA_StartTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            }
            #endif
            IMSA_SRV_SndConnRelReq(enSrvType,
                                   IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          IMSA_FALSE,
                                          IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          IMSA_FALSE,
                                          IMSA_FALSE);

            IMSA_SRV_SndConnRelReq(enSrvType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
                IMSA_StartTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            }
            #endif
            break;

        case IMSA_RESOURCE_STATUS_APPLYING:
            /* 修改原因值 */
            IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                             RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            break;
        #endif
        default:
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
                IMSA_StartTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            }
            #endif
            IMSA_SRV_SndConnRelReq(enSrvType,
                                   IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            break;
    }
}
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcRegDeregIndWithNextAddr
 Description    : IMSA内部消息ID_IMSA_REG_DEREG_IND处理函数
 Input          : pstRegDeregIndMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-30  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcRegDeregIndConnDereging
(
    IMSA_SRV_TYPE_ENUM_UINT8            enSrvType
)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = IMSA_GetControlManagerAddress();
    #endif

    IMSA_SRV_SetServcieStatus(enSrvType,
                              IMSA_SRV_STATUS_RELEASING_DEREG);

    IMSA_SRV_SndCallSrvStatusInd(enSrvType,
                                IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                IMSA_CALL_NO_SRV_CAUSE_REG_ERR);

    /* 如果是紧急类型，则直接通知链接模块释放承载 */
    if (IMSA_SRV_TYPE_EMC == enSrvType)
    {
        IMSA_SRV_SndConnRelReq(enSrvType,
                                IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
        return;
    }

    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
         case IMSA_RESOURCE_STATUS_ACTIVE:
            IMSA_SRV_SndConnRelReq(enSrvType,
                                   IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            }
            #endif
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          IMSA_FALSE,
                                          IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:
            /* 暂时不会有该原因值 */
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          IMSA_FALSE,
                                          IMSA_FALSE);

            IMSA_SRV_SndConnRelReq(enSrvType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            }
            #endif
            break;

        case IMSA_RESOURCE_STATUS_APPLYING:
            /* 修改原因值 */
            IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                             RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            break;
        #endif
        default:
            IMSA_SRV_SndConnRelReq(enSrvType,
                                   IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            }
            #endif
            break;
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcRegDeregIndMsg
 Description    : IMSA内部消息ID_IMSA_REG_DEREG_IND处理函数
 Input          : pstRegDeregIndMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-24  Draft Enact
      2.wangchen 00209181    2015-11-30  Modify:volte dsds
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcRegDeregIndMsg
(
    const IMSA_REG_DEREG_IND_STRU      *pstRegDeregIndMsg
)
{
    IMSA_INFO_LOG("IMSA_SRV_ProcRegDeregIndMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcRegDeregIndMsg_ENUM, LNAS_ENTRY);

    /* 如果是CONN&DEREGING状态，则请求释放连接，状态转到RELEASING&DEREG态 */
    if (IMSA_TRUE == IMSA_SRV_IsSrvStatusEqual((    IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                                    IMSA_SRV_STATUS_CONN_DEREGING))
    {
        /* 目前只有MMA DEREG REG导致的去注册类型，后续增加了其他类型的去注册，
           此处需要增加考虑 */
        IMSA_SRV_ProcRegDeregIndConnDereging((    IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType);

        return ;
    }

    /* 如果是CONNING&REG状态，则本地去注册，状态修改为CONNING&DEREG状态 */
    if (((IMSA_REG_TYPE_NORMAL == pstRegDeregIndMsg->enRegType)
            && (IMSA_TRUE == IMSA_SRV_IsSrvStatusEqual(IMSA_SRV_TYPE_NORMAL,IMSA_SRV_STATUS_CONNING_REG)))
        ||((IMSA_REG_TYPE_EMC == pstRegDeregIndMsg->enRegType)
            && (IMSA_TRUE == IMSA_SRV_IsSrvStatusEqual(IMSA_SRV_TYPE_EMC,IMSA_SRV_STATUS_CONNING_REG))))
    {
        IMSA_SRV_RegConningStateProcRegDeregIndMsg(pstRegDeregIndMsg->enRegType);

        return;
    }

    if (IMSA_TRUE == IMSA_SRV_IsSrvStatusEqual((    IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                                    IMSA_SRV_STATUS_CONN_REG))
    {
        switch (pstRegDeregIndMsg->enResultAction)
        {
            case IMSA_RESULT_ACTION_NULL:


                IMSA_SRV_SetImsRegForbidden(pstRegDeregIndMsg->enRegType, pstRegDeregIndMsg->enResult);
                IMSA_SRV_ProcRegDeregIndActionNull((IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType);
                break;
            case IMSA_RESULT_ACTION_REG_WITH_FIRST_ADDR_PAIR:

                IMSA_SRV_ProcRegDeregIndWithAddr((IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType, IMSA_REG_ADDR_PARAM_NEW);

                break;
            case IMSA_RESULT_ACTION_REG_WITH_CURRENT_ADDR_PAIR:

                IMSA_SRV_ProcRegDeregIndWithAddr((IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                                   IMSA_REG_ADDR_PARAM_SAME);

                break;
            case IMSA_RESULT_ACTION_REG_WITH_NEXT_ADDR_PAIR:

                IMSA_SRV_ProcRegDeregIndWithAddr((IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                                   IMSA_REG_ADDR_PARAM_NEXT);

                break;
            case IMSA_RESULT_ACTION_REG_LOCAL_DEREG:
                IMSA_SRV_SetServcieStatus(  (IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                            IMSA_SRV_STATUS_CONN_DEREG);

                /* 切离CONN&REG态，因此通知CALL呼叫服务进入无服务状态 */
                IMSA_SRV_SndCallSrvStatusInd((IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                              IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                              IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);

                break;
            case IMSA_RESULT_ACTION_WAIT_RETRY_TIME_OUT:

                IMSA_SRV_SetServcieStatus(  (IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                            IMSA_SRV_STATUS_CONN_REGING);

                /* 切离CONN&REG态，因此通知CALL呼叫服务进入无服务状态 */
                IMSA_SRV_SndCallSrvStatusInd((IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                              IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                              IMSA_CALL_NO_SRV_CAUSE_REG_ERR);
                break;
            default:

                IMSA_INFO_LOG("IMSA_SRV_ProcRegDeregIndMsg:illegal result action!");
                TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcRegDeregIndMsg_ENUM, LNAS_PARAM_INVALID);

                IMSA_SRV_ProcRegDeregIndActionNull((IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType);

                break;
        }
    }

    return ;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcConnSetupIndMsg
 Description    : IMSA内部消息ID_IMSA_CONN_SETUP_IND处理函数
 Input          : pstConnSetupIndMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-05  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcConnSetupIndMsg
(
    const IMSA_CONN_SETUP_IND_STRU     *pstConnSetupIndMsg
)
{
    if (IMSA_CONN_RESULT_SUCCESS == pstConnSetupIndMsg->enResult)
    {
        IMSA_SRV_ProcConnSetupIndSucc(pstConnSetupIndMsg);
    }
    else
    {
        IMSA_SRV_ProcConnSetupIndFail(pstConnSetupIndMsg);
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcEmcConnRelIndMsg
 Description    : IMSA内部消息ID_IMSA_CONN_REL_IND处理函数,紧急连接
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-24  Draft Enact
      2.lihong 00150010      2013-12-06  Modify:Emc dedicated
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcEmcConnRelIndMsg
(
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType
)
{
    if (IMSA_CONN_SIP_PDP_TYPE_MEDIA == enSipPdpType)
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcEmcConnRelIndMsg:emc dedicated release!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcEmcConnRelIndMsg_ENUM, 1);

        /* 通知CALL模块媒体承载释放 */
        IMSA_ProcCallResourceIsNotReady(IMSA_CONN_TYPE_EMC);

        return ;
    }

    IMSA_INFO_LOG("IMSA_SRV_ProcEmcConnRelIndMsg:emc default release!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcEmcConnRelIndMsg_ENUM, 2);

    /* 紧急注册状态，收到网侧发送的释放SIP紧急承载后的处理 */
    if (IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetEmcSrvStatus())
    {
        /* delete PeriodImsEmcSrvTryTimer */
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_IDLE_DEREG);

        /* 通知IMSA本地去注册 */
        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

        /* 通知CALL模块紧急呼叫服务进入无服务状态，促使CALL模块清除缓存的紧急呼 */
        IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                        IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);

        return;
    }
    if (IMSA_SRV_STATUS_CONNING_REG == IMSA_SRV_GetEmcSrvStatus())
    {
        /* 切离CONNING+REG态时，IMSA需要通知IMS允许发包 */
        IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_EMC_SRV);

        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_IDLE_DEREG);

        /* 通知IMSA本地去注册 */
        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

        return;
    }

    /* 如果是以下三种状态，则通知REG模块本地去注册 */
    if (IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetEmcSrvStatus())
    {
        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

        /* 需要通知CALL模块紧急呼叫服务进入无服务状态，促使其释放缓存的紧急呼 */
        IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                        IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);
    }

    if (IMSA_SRV_STATUS_CONN_DEREGING == IMSA_SRV_GetEmcSrvStatus())
    {
        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

        /* 由于已经进行本地去注册，无需通知CALL模块呼叫服务状态进入无服务，
           否则本地去注册流程和释放CALL流程同时进行，容易出问题 */
    }

    IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_IDLE_DEREG);
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcConnRelIndMsg
 Description    : IMSA内部消息ID_IMSA_CONN_REL_IND处理函数
 Input          : pstConnRelIndMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-24  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg( VOS_VOID )
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, LNAS_ENTRY);

    /* 进入DETACHED态的连接释放(本地DETACH或者MT DETACH导致的)，IMSA不应该重建链路，
       而保持ATTACHED态的连接释放，IMSA应该重建链路，IMSA通过PS域服务状态是否是
       正常服务来区分，但为了避免系统的时序问题(即APS通知连接释放在前，MMA通知
       PS域服务状态在后)，导致了IMSA判定错误，IMSA不马上判断PS域服务状态，先启动
       周期性尝试IMS服务定时器，待定时器超时后再判定建立连接的条件是否具备 */
    pstControlMagnaer  = IMSA_GetControlManagerAddress();
    if (IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg:conn&reg!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_REGISTERED);

        /* SIP信令承载释放后，不再本地去注册，IP地址发生变更或者IMS周期性注册定时器超时后，
        重新发起IMS注册 */
        /* 需要通知IMS不允许发包 */
        IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_SUSPEND_NRM_SRV);

        /*IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);*/
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONNING_REG);

        /* 启动周期性尝试IMS服务定时器 */
        IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);

        /* 通知CALL模块普通呼叫服务进入无服务状态 */
        IMSA_SRV_SndNrmCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                        IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);

        return ;
    }

    if (IMSA_SRV_STATUS_CONNING_REG == IMSA_SRV_GetNormalSrvStatus())
    {
        /* 如果定时器没有再运行，则转到IDLE+DEREG状态，本地去注册 */
        if (IMSA_TRUE != IMSA_IsTimerRunning(&pstControlMagnaer->stPeriodImsSrvTryTimer))
        {
            /* 切离CONNING+REG态时，IMSA需要通知IMS允许发包 */
            IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV);

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

            /* 启动周期性尝试IMS服务定时器 */
            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);

            /* 需要释放资源 */
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
                IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            }
            #endif
        }
        return;
    }

    if (IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg:conn&reging!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_REGISTERING);

        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);

        /* 启动周期性尝试IMS服务定时器 */
        IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);

        /* 状态转到IDLE&DEREG态，由于IMSA_SRV_SetServcieStatus中会用到周期性
           尝试IMS服务定时器的运行情况，且当前在注册过程中，所以需要先启动定时器后转状态 */
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

        /* 由于已经进行本地去注册，无需通知CALL模块呼叫服务状态进入无服务，
           否则本地去注册流程和释放CALL流程同时进行，容易出问题 */

        #if (FEATURE_ON == FEATURE_DSDS)
        if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
        {
            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
            IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
        }
        #endif

        return ;
    }

    if (IMSA_SRV_STATUS_CONN_DEREG == IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg:conn&dereg!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_NOT_REGISTER);

        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

        /* 启动周期性尝试IMS服务定时器 */
        IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);

        #if (FEATURE_ON == FEATURE_DSDS)
        if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
        {
            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
            IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
        }
        #endif

        return ;
    }

    if ((IMSA_SRV_STATUS_RELEASING_DEREG == IMSA_SRV_GetNormalSrvStatus())
        || (IMSA_SRV_STATUS_CONNING_DEREG == IMSA_SRV_GetNormalSrvStatus()))
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg:releasing&dereg or conning&dereg!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_RELEASING);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_CONNECTING);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_NOT_REGISTER);

        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

        #if (FEATURE_ON == FEATURE_DSDS)
        if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
        {
            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
            IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
        }
        #endif

        return ;
    }

    if (IMSA_SRV_STATUS_CONN_DEREGING == IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg:conn&dereging!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_DEREGISTERING);

        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);

        #if (FEATURE_ON == FEATURE_DSDS)
        if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
        {
            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
            IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
        }
        #endif

        return ;
    }

    return ;
}


/*****************************************************************************
 Function Name  : IMSA_SRV_ProcConnRelIndMsg
 Description    : IMSA内部消息ID_IMSA_CONN_REL_IND处理函数
 Input          : pstConnRelIndMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-24  Draft Enact
      2.lihong 00150010      2013-12-06  Modify:Emc dedicated
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcConnRelIndMsg
(
    const IMSA_CONN_REL_IND_STRU       *pstConnRelIndMsg
)
{
    IMSA_INFO_LOG("IMSA_SRV_ProcConnRelIndMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcConnRelIndMsg_ENUM, LNAS_ENTRY);

    if (IMSA_CONN_TYPE_EMC == pstConnRelIndMsg->enConnType)
    {
        IMSA_SRV_ProcEmcConnRelIndMsg(pstConnRelIndMsg->enSipPdpType);

        return ;
    }

    /* 普通连接分支 */

    if (IMSA_CONN_SIP_PDP_TYPE_MEDIA == pstConnRelIndMsg->enSipPdpType)
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcConnRelIndMsg:normal media pdp release!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcConnRelIndMsg_ENUM, 2);

        /* 通知CALL模块媒体承载释放 */
        IMSA_ProcCallResourceIsNotReady(IMSA_CONN_TYPE_NORMAL);

        /* 通知MSCC，当前承载状态 */
        if (IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetNormalSrvStatus())
        {
            IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_AVAILABLE,IMSA_CONN_IsExitPersistentBearer());
        }

        /* 在IDLE+DEREG状态下不会收到媒体承载的释放消息，所以不需要判断 */

        /* 媒体承载被释放，网络不支持IMS VOICE,接入技术不支持IMS时，由网侧决定是否
        挂断电话，删除UE主动挂断电话的功能 */

    }
    else
    {
        IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg();
    }
}
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcNormalConnSignalBearerModifyIndConnReging
 Description    : IMSA内部消息ID_IMSA_CONN_MODIFY_IND处理函数
 Input          : pstConnModifyIndMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-12-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcNormalConnSignalBearerModifyIndConnReging
(
    VOS_VOID
)
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = IMSA_GetControlManagerAddress();

    IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg:conn&reging!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_CONN);
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_REGISTERING);

    /* 如果是DSDS流程，则需要先申请资源 */
    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);

            IMSA_SRV_SndConnRelReq(IMSA_CONN_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_RELEASING_DEREG);
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
                IMSA_StartTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            }
            #endif

            /* 启动周期性尝试IMS服务定时器 */
            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_APPLYING:

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_RELEASING_DEREG);

            IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                             RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

            break;

        /* 以下三个状态应该都不会有 */
        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          IMSA_FALSE,
                                          IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_WAIT_STATUS_IND:

            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

            break;
        #endif
        default:
            break;
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcNormalConnSignalBearerModifyIndConnDereg
 Description    : IMSA内部消息ID_IMSA_CONN_MODIFY_IND处理函数
 Input          : pstConnModifyIndMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-12-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcNormalConnSignalBearerModifyIndConnDereg
(
    VOS_VOID
)
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = IMSA_GetControlManagerAddress();

    IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg:conn&reging!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_CONN);
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_REGISTERING);

    /* 如果是DSDS流程，则需要先申请资源 */
    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:

            IMSA_SRV_SndConnRelReq(IMSA_CONN_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_RELEASING_DEREG);

            /* 启动周期性尝试IMS服务定时器 */
            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
                IMSA_StartTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            }
            #endif

            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_APPLYING:

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_RELEASING_DEREG);

            IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                             RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

            /* 启动周期性尝试IMS服务定时器 */
            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);

            break;

        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          IMSA_FALSE,
                                          IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_WAIT_STATUS_IND:
            /* 有可能处于该状态，等待消息，重新发注册 */
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_RELEASING_DEREG);

            IMSA_DsdsSndRrmDeRegisterInd(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          IMSA_FALSE,
                                          IMSA_FALSE);

            /* 启动周期性尝试IMS服务定时器 */
            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

            break;
        #endif
        default:
            break;
    }
}
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcNormalConnSignalBearerModifyIndConnDereging
 Description    : IMSA内部消息ID_IMSA_CONN_MODIFY_IND处理函数
 Input          : pstConnModifyIndMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-12-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcNormalConnSignalBearerModifyIndConnDereging
(
    VOS_VOID
)
{
    IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg:conn&reging!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_CONN);
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_REGISTERING);

    /* 如果是DSDS流程，则需要先申请资源 */
    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);

            IMSA_SRV_SndConnRelReq(IMSA_CONN_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_RELEASING_DEREG);

            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_APPLYING:

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_RELEASING_DEREG);

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);

            break;
        /* 以下三个状态不应该有 */
        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          IMSA_FALSE,
                                          IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_WAIT_STATUS_IND:
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

            break;
        #endif
        default:
            break;
    }
}
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcNormalConnSignalBearerModifyIndConnDereging
 Description    : IMSA内部消息ID_IMSA_CONN_MODIFY_IND处理函数
 Input          : pstConnModifyIndMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-12-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcNormalConnSignalBearerModifyPcscfInvalid
(
    VOS_VOID
)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = IMSA_GetControlManagerAddress();
    #endif

    if ((IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetNormalSrvStatus()) ||
        (IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetNormalSrvStatus()))
    {
        switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
        {
            case IMSA_RESOURCE_STATUS_ACTIVE:

                IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_REGING);
                IMSA_SRV_SndRegDeregReq(IMSA_SRV_TYPE_NORMAL, IMSA_DEREG_LOCAL);
                IMSA_SRV_SndRegRegReq(IMSA_SRV_TYPE_NORMAL, IMSA_REG_ADDR_PARAM_NEW);

                #if (FEATURE_ON == FEATURE_DSDS)
                if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
                {
                    IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
                }
                #endif
                break;
            #if (FEATURE_ON == FEATURE_DSDS)
            case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

                IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                              IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                              VOS_FALSE,
                                              VOS_FALSE);

                IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_REGING);
                IMSA_SRV_SndRegDeregReq(IMSA_SRV_TYPE_NORMAL, IMSA_DEREG_LOCAL);
                IMSA_SRV_SndRegRegReq(IMSA_SRV_TYPE_NORMAL, IMSA_REG_ADDR_PARAM_NEW);

                if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
                {
                    IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
                }
                break;

            case  IMSA_RESOURCE_STATUS_NULL:

                IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                              IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                              IMSA_REG_ADDR_PARAM_NEW,
                                              VOS_FALSE);

                IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_REGING);
                IMSA_SRV_SndRegDeregReq(IMSA_SRV_TYPE_NORMAL, IMSA_DEREG_LOCAL);
                break;
            #endif
            default:
                #if (FEATURE_ON == FEATURE_DSDS)
                IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                                 RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
                #endif
                break;

        }
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcNormalConnSignalBearerModifyIndConnDereging
 Description    : IMSA内部消息ID_IMSA_CONN_MODIFY_IND处理函数
 Input          : pstConnModifyIndMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-12-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcNormalConnSignalBearerModifyRegParaInvalid
(
    VOS_VOID
)
{

    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = IMSA_GetControlManagerAddress();

    /* 如果在CONN&REGIN或者GCONN&REG态，则请求REG模块本地去注册，
       请求CONN模块释放连接，状态转到RELEASING&DEREG态，启动周期性尝试IMS
       服务定时器 */
    if (IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_SRV_ProcNormalConnSignalBearerModifyIndConnReging();
        return ;
    }

    if (IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg:conn&reg!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_REGISTERED);

        /* 需要通知IMS不允许发包 */
        IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_SUSPEND_NRM_SRV);

        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONNING_REG);

        /* 启动周期性尝试IMS服务定时器 */
        IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);

        return;
    }

    /* 如果在CONN&DEREGING态，则请求REG模块本地去注册，请求CONN模块释放连接，
       状态转到RELEASING&DEREG态 */
    if (IMSA_SRV_STATUS_CONN_DEREGING == IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg:conn&dereging!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_DEREGISTERING);

        IMSA_SRV_ProcNormalConnSignalBearerModifyIndConnDereging();
        return ;
    }

    /* 如果在CONN&DEREG态，则请求CONN模块释放连接，状态转到RELEASING&DEREG态,
       启动周期性尝试IMS服务定时器 */
    if (IMSA_SRV_STATUS_CONN_DEREG == IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg:conn&dereg!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_NOT_REGISTER);

        IMSA_SRV_ProcNormalConnSignalBearerModifyIndConnDereg();
        return ;
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcConnModifyIndMsg
 Description    : IMSA内部消息ID_IMSA_CONN_MODIFY_IND处理函数
 Input          : pstConnModifyIndMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-24  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg
(
    const IMSA_CONN_MODIFY_IND_STRU    *pstConnModifyIndMsg
)
{
    IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, LNAS_ENTRY);

    /* 如果不是注册参数无效，则直接退出 */
    if (IMSA_OP_TRUE != pstConnModifyIndMsg->bitOpModifyType)
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg:normal,not reg para invalid!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, 2);

        return ;
    }

    /* 如果紧急连接，且注册P-CSCF地址失效，则重新发起注册；否则直接退出  */
    if (IMSA_CONN_TYPE_EMC == pstConnModifyIndMsg->enConnType)
    {
        if (IMSA_CONN_MODIFY_TYPE_PCSCF_INVALID == pstConnModifyIndMsg->enModifyType)
        {
            /* 需要判断注册状态 */
            if ((IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetEmcSrvStatus()) ||
                (IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetEmcSrvStatus()))
            {
                IMSA_SRV_SetServcieStatus(IMSA_REG_TYPE_EMC, IMSA_SRV_STATUS_CONN_REGING);
                IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);
                IMSA_SRV_SndRegRegReq(IMSA_REG_TYPE_EMC, IMSA_REG_ADDR_PARAM_NEW);
            }
        }
        return ;
    }

    /* 注册参数失效 */
    if (IMSA_CONN_MODIFY_TYPE_REG_PARA_INVALID == pstConnModifyIndMsg->enModifyType)
    {
        IMSA_SRV_ProcNormalConnSignalBearerModifyRegParaInvalid();

    }
    else /* P-CSCF地址失效 */
    {
        IMSA_SRV_ProcNormalConnSignalBearerModifyPcscfInvalid();
    }
}


/*****************************************************************************
 Function Name  : IMSA_SRV_ProcConnModifyIndMsg
 Description    : IMSA内部消息ID_IMSA_CONN_MODIFY_IND处理函数
 Input          : pstConnModifyIndMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-24  Draft Enact
      2.lihong 00150010      2013-12-06  Modify
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcConnModifyIndMsg
(
    const IMSA_CONN_MODIFY_IND_STRU    *pstConnModifyIndMsg
)
{
    IMSA_INFO_LOG("IMSA_SRV_ProcConnModifyIndMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcConnModifyIndMsg_ENUM, LNAS_ENTRY);

    /* 如果是媒体承载修改，则通过CALL模块资源具备 */
    if (IMSA_CONN_SIP_PDP_TYPE_MEDIA == pstConnModifyIndMsg->enSipPdpType)
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcConnModifyIndMsg:no need notify CallModule!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcConnModifyIndMsg_ENUM, LNAS_ENTRY);
    }
    else
    {
        IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg(pstConnModifyIndMsg);
    }
}
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcCallRsltWithFirstAddr
 Description    : IMSA内部消息ID_IMSA_CALL_RESULT_ACTION_IND处理函数
 Input          : pstCallRsltActionIndMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcCallRsltWithFirstAddr
(
    const IMSA_CALL_RESULT_ACTION_IND_STRU *pstCallRsltActionIndMsg
)
{
    if (IMSA_CALL_TYPE_EMC != pstCallRsltActionIndMsg->enCallType)
    {
        IMSA_WARN_LOG("IMSA_SRV_ProcCallRsltActionIndMsg:normal srv,first addr pair can not happen!");
        TLPS_PRINT2LAYER_WARNING1(IMSA_SRV_ProcCallRsltActionIndMsg_ENUM, LNAS_PARAM_INVALID, 1);
        return ;
    }

    if (IMSA_SRV_STATUS_IDLE_DEREG != IMSA_SRV_GetEmcSrvStatus())
    {
        IMSA_WARN_LOG("IMSA_SRV_ProcCallRsltActionIndMsg:first addr pair,emc status is not IDLE&DEREG!");
        TLPS_PRINT2LAYER_WARNING1(IMSA_SRV_ProcCallRsltActionIndMsg_ENUM, IMSA_STATE_ERROR, 1);
        return ;
    }

    if (IMSA_RESOURCE_STATUS_ACTIVE == IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL))
    {
        IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                    IMSA_CONN_TYPE_EMC);

        IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_EMC,
                                    IMSA_SRV_STATUS_CONNING_DEREG);
    }
    #if (FEATURE_ON == FEATURE_DSDS)
    else if (IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF == IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL))
    {
        IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL,
                                      IMSA_RF_RES_APPLY_TRIGER_SRC_EMC_CALL,
                                      VOS_FALSE,
                                      VOS_FALSE);

        IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                    IMSA_CONN_TYPE_EMC);

        IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_EMC,
                                    IMSA_SRV_STATUS_CONNING_DEREG);
    }
    else
    {
        IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL,
                                      IMSA_RF_RES_APPLY_TRIGER_SRC_EMC_CALL,
                                      VOS_FALSE,
                                      VOS_FALSE);
    }
    #endif
    return;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcCallRsltWithNextAddr
 Description    : IMSA内部消息ID_IMSA_CALL_RESULT_ACTION_IND处理函数
 Input          : pstCallRsltActionIndMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcCallRsltWithNextAddr
(
    const IMSA_CALL_RESULT_ACTION_IND_STRU *pstCallRsltActionIndMsg
)
{
    if (IMSA_CALL_TYPE_EMC != pstCallRsltActionIndMsg->enCallType)
    {
        IMSA_WARN_LOG("IMSA_SRV_ProcCallRsltActionIndMsg:normal srv,next addr pair can not happen!");
        TLPS_PRINT2LAYER_WARNING1(IMSA_SRV_ProcCallRsltActionIndMsg_ENUM, LNAS_PARAM_INVALID, 2);
        return ;
    }

    if (IMSA_SRV_STATUS_CONN_REG != IMSA_SRV_GetEmcSrvStatus())
    {
        IMSA_WARN_LOG("IMSA_SRV_ProcCallRsltActionIndMsg:next addr pair,emc status is not CONN&REG!");
        TLPS_PRINT2LAYER_WARNING1(IMSA_SRV_ProcCallRsltActionIndMsg_ENUM, IMSA_STATE_ERROR, 2);
        return ;
    }

    /* 先本地去注册，在发起注册请求，状态转到CONN&REGING */
    IMSA_SRV_SndRegDeregReq(    IMSA_REG_TYPE_EMC,
                                IMSA_DEREG_LOCAL);

    IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_EMC,
                                IMSA_REG_ADDR_PARAM_NEXT);

    IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_EMC,
                                IMSA_SRV_STATUS_CONN_REGING);

    /* 由于CALL模块那还缓存着紧急呼，因此不能通知CALL模块无服务，否则会
       导致CALL模块清除缓存的紧急呼 */
    return;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcCallRsltWithNextAddr
 Description    : IMSA内部消息ID_IMSA_CALL_RESULT_ACTION_IND处理函数
 Input          : pstCallRsltActionIndMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcCallRsltRestoration
(
    const IMSA_CALL_RESULT_ACTION_IND_STRU *pstCallRsltActionIndMsg
)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = IMSA_GetControlManagerAddress();
    #endif

    if (IMSA_CALL_TYPE_EMC == pstCallRsltActionIndMsg->enCallType)
    {
        IMSA_WARN_LOG("IMSA_SRV_ProcCallRsltActionIndMsg:emc srv,restoration can not happen!");
        TLPS_PRINT2LAYER_WARNING1(IMSA_SRV_ProcCallRsltActionIndMsg_ENUM, LNAS_PARAM_INVALID, 3);
        return ;
    }

    if (IMSA_SRV_STATUS_CONN_REG != IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_WARN_LOG("IMSA_SRV_ProcCallRsltActionIndMsg:restoration,normal status is not CONN&REG!");
        TLPS_PRINT2LAYER_WARNING1(IMSA_SRV_ProcCallRsltActionIndMsg_ENUM, IMSA_STATE_ERROR, 3);
        return ;
    }

    if (IMSA_RESOURCE_STATUS_ACTIVE == IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        IMSA_SRV_SndRegDeregReq(    IMSA_REG_TYPE_NORMAL,
                                IMSA_DEREG_LOCAL);

        IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                    IMSA_REG_ADDR_PARAM_RESTORATION);

        IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                    IMSA_SRV_STATUS_CONN_REGING);

        #if (FEATURE_ON == FEATURE_DSDS)
        if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
        {
            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
        }
        #endif
    }
    #if (FEATURE_ON == FEATURE_DSDS)
    else if (IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF == IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                     IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                     IMSA_REG_ADDR_PARAM_RESTORATION,
                                     IMSA_FALSE);

        IMSA_SRV_SndRegDeregReq(    IMSA_REG_TYPE_NORMAL,
                                IMSA_DEREG_LOCAL);

        IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                    IMSA_REG_ADDR_PARAM_RESTORATION);

        IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                    IMSA_SRV_STATUS_CONN_REGING);

        if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
        {
            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
        }
    }
    else
    {
        IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                      IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                      IMSA_REG_ADDR_PARAM_RESTORATION,
                                      IMSA_FALSE);

        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL,
                                IMSA_DEREG_LOCAL);

        IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                    IMSA_SRV_STATUS_CONN_REGING);
    }
    #endif
    /* 由于已经通知注册模块进行本地去注册，因此无需通知CALL模块无服务，
       否则本地去注册流程和释放CALL流程同时进行，容易出问题 */
    return;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcCallRsltActionIndMsg
 Description    : IMSA内部消息ID_IMSA_CALL_RESULT_ACTION_IND处理函数
 Input          : pstCallRsltActionIndMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-24  Draft Enact
      2.wangchen 00209181    2014-06-19  Modify vtlte
      3.wangchen 00209181   2015-11-28   Modify:volte dsds
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcCallRsltActionIndMsg
(
    const IMSA_CALL_RESULT_ACTION_IND_STRU *pstCallRsltActionIndMsg
)
{
    IMSA_INFO_LOG("IMSA_SRV_ProcCallRsltActionIndMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcCallRsltActionIndMsg_ENUM, LNAS_ENTRY);

    switch (pstCallRsltActionIndMsg->enResultAction)
    {
        case IMSA_RESULT_ACTION_REG_WITH_FIRST_ADDR_PAIR:

            IMSA_SRV_ProcCallRsltWithFirstAddr(pstCallRsltActionIndMsg);
            break;
        case IMSA_RESULT_ACTION_REG_WITH_NEXT_ADDR_PAIR:

            IMSA_SRV_ProcCallRsltWithNextAddr(pstCallRsltActionIndMsg);
            break;
        case IMSA_RESULT_ACTION_REG_RESTORATION:

            IMSA_SRV_ProcCallRsltRestoration(pstCallRsltActionIndMsg);
            break;

        default:

            IMSA_WARN_LOG("IMSA_SRV_ProcCallRsltActionIndMsg:illegal result action!");
            TLPS_PRINT2LAYER_WARNING(IMSA_SRV_ProcCallRsltActionIndMsg_ENUM, LNAS_ERROR);

            break;
    }
}


/*****************************************************************************
 Function Name  : IMSA_SRV_ProcCallRsltActionIndMsg
 Description    : IMSA内部消息ID_IMSA_CALL_SRVCC_SUCC_IND处理函数
 Input          : IMSA_SRV_ProcCallSrvccSuccIndMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719      2015-12-24  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcCallSrvccSuccIndMsg
(
    const IMSA_CALL_SRVCC_SUCC_IND_STRU *pstCallSrvccSuccIndMsg
)
{
    IMSA_INFO_LOG("IMSA_SRV_ProcCallSrvccSuccIndMsg is entered!");

    (VOS_VOID)pstCallSrvccSuccIndMsg;

    /* 收到CALL模块发来的SRVCC成功信息后，通知TAF当前IMS处于未注册状态,
       TAF就不会再域选到IMS。
       电话挂断后，回到LTE会发TAU，MSCC会通知SERVICE_CHANGE_IND，此时
       IMSA判断之前通知过未注册状态，会再通知TAF当前为已注册状态，
       之后就可以正常域选到IMS了 */
    IMSA_SRV_NrmRegStatusNotify(IMSA_NORMAL_REG_STATUS_DEREG);

    IMSA_SetLastNrmRegStatus(IMSA_NORMAL_REG_STATUS_DEREG);
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcTransToNotSupportEms
 Description    : EMS转为不支持时的处理
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-10-11  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcTransToNotSupportEms( VOS_VOID )
{
    switch (IMSA_SRV_GetEmcSrvStatus())
    {
        case IMSA_SRV_STATUS_CONN_REG:

            IMSA_INFO_LOG("IMSA_SRV_ProcTransToNotSupportEms:conn&reg!");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcTransToNotSupportEms_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcTransToNotSupportEms_ENUM, IMSA_STATUS_REGISTERED);

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

            IMSA_SRV_SndConnRelReq( IMSA_CONN_TYPE_EMC,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_RELEASING_DEREG);

            break;

        case IMSA_SRV_STATUS_CONNING_DEREG:

            IMSA_INFO_LOG("IMSA_SRV_ProcTransToNotSupportEms:conning&dereg!");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcTransToNotSupportEms_ENUM, IMSA_STATUS_CONNECTING);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcTransToNotSupportEms_ENUM, IMSA_STATUS_NOT_REGISTER);

            IMSA_SRV_SndConnRelReq( IMSA_CONN_TYPE_EMC,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            /* 通知CALL模块紧急呼叫服务进入无服务状态，促使CALL模块清除缓存的紧急呼 */
            IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                            IMSA_CALL_NO_SRV_CAUSE_REG_ERR);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_RELEASING_DEREG);

            break;

        case IMSA_SRV_STATUS_CONN_DEREG:

            IMSA_INFO_LOG("IMSA_SRV_ProcTransToNotSupportEms:conn&dereg!");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcTransToNotSupportEms_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcTransToNotSupportEms_ENUM, IMSA_STATUS_NOT_REGISTER);

            IMSA_SRV_SndConnRelReq( IMSA_CONN_TYPE_EMC,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_RELEASING_DEREG);

            break;

        case IMSA_SRV_STATUS_CONN_REGING:

            IMSA_INFO_LOG("IMSA_SRV_ProcTransToNotSupportEms:conn&reging!");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcTransToNotSupportEms_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcTransToNotSupportEms_ENUM, IMSA_STATUS_REGISTERING);

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

            IMSA_SRV_SndConnRelReq( IMSA_CONN_TYPE_EMC,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            /* 通知CALL模块紧急呼叫服务进入无服务状态，促使CALL模块清除缓存的紧急呼 */
            IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                            IMSA_CALL_NO_SRV_CAUSE_REG_ERR);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_RELEASING_DEREG);

            break;

        default:
            break;
    }
}


/*****************************************************************************
 Function Name  : IMSA_SRV_UpdateRat
 Description    : 更新接入技术
 Input          : enRat------------------接入技术
 Output         : pulIsNotfiyNrmNoSrv----是否通知正常服务无服务
                  pulIsNotfiyEmcNoSrv----是否通知紧急服务无服务
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-10-11  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_UpdateRat
(
    MSCC_IMSA_RAT_TYPE_ENUM_UINT8        enRat,
    VOS_UINT32                         *pulIsNotfiyNrmNoSrv,
    VOS_UINT32                         *pulIsNotfiyEmcNoSrv
)
{
    IMSA_NETWORK_INFO_STRU             *pstNwInfo           = VOS_NULL_PTR;
    IMSA_CAMPED_RAT_TYPE_ENUM_UINT8     enCampedRatTypeTmp  = IMSA_CAMPED_RAT_TYPE_BUTT;
    IMSA_CALL_MANAGER_STRU              *pstImsaCallCtx   = VOS_NULL_PTR;

    pstImsaCallCtx   = IMSA_CallCtxGet();
    pstNwInfo = IMSA_GetNetInfoAddress();

    *pulIsNotfiyNrmNoSrv = IMSA_FALSE;
    *pulIsNotfiyEmcNoSrv = IMSA_FALSE;

    IMSA_SRV_RatFormatTransform(    &enCampedRatTypeTmp,
                                    enRat);

    /* 如果接入未变更，则直接返回 */
    if (pstNwInfo->enImsaCampedRatType == enCampedRatTypeTmp)
    {
        return ;
    }

    /* 从GU变换到L，且当前有呼叫存在，且通知LRRC开启HIFI同步 */
    if ((enCampedRatTypeTmp == IMSA_CAMPED_RAT_TYPE_EUTRAN)
        && (VOS_TRUE == IMSA_IsCallConnExist()))
    {
        IMSA_SndLRrcHifiSyncSwtichInd(IMSA_TRUE);
    }

    pstNwInfo->enImsaCampedRatType = enCampedRatTypeTmp;

    /*异系统变换后需要停止BACK-OFF定时器*/
    IMSA_StopTimer(&pstImsaCallCtx->stBackOffTxTimer);
    IMSA_StopTimer(&pstImsaCallCtx->stBackOffTyTimer);

    /* 如果接入技术发生变更，且目的接入不支持IMS，且SRVCC标识为FALSE，则指示
       IMSA CALL子模块无服务，原因值填为非SRVCC异系统 */
    if ((IMSA_FALSE == IMSA_SRV_IsCurRatSupportIms())
        && (IMSA_FALSE == IMSA_CallGetSrvccFlag()))
    {
        *pulIsNotfiyNrmNoSrv = IMSA_TRUE;

    }

    /* 如果接入技术发生变更，且目的接入不支持EMS，则指示IMSA REG子模块本地紧急
       去注册（如果存在IMS紧急注册）或者通知IMSA CONN子模块释放紧急连接（
       如果只存在IMS紧急连接，不存在IMS紧急注册） */
    if (IMSA_FALSE == IMSA_SRV_IsCurRatSupportEms())
    {
        *pulIsNotfiyEmcNoSrv = IMSA_TRUE;


    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_UpdateImsVoPsStatus
 Description    : 更新网侧是否支持IMS VOICE标识
 Input          : enImsVoPsInd------------------IMS VOICE标识
                  ulIsNotfiyNrmNoSrv------------是否通知正常服务无服务
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-10-11  Draft Enact
      2.wangchen 00209181    2013-10-12  Modify
*****************************************************************************/
VOS_VOID IMSA_SRV_UpdateImsVoPsStatus
(
    MSCC_IMSA_IMS_VOPS_INDICATOR_ENUM_UINT8      enImsVoPsInd
)
{
    IMSA_NETWORK_INFO_STRU             *pstNwInfo           = VOS_NULL_PTR;

    pstNwInfo = IMSA_GetNetInfoAddress();

    if (pstNwInfo->enImsaImsVoPsStatus != enImsVoPsInd)
    {
        pstNwInfo->enImsaImsVoPsStatus          = enImsVoPsInd;

        IMSA_SndMsgAtCirepiInd(enImsVoPsInd);

    }
    IMSA_ConfigNetCapInfo2Ims();

}

/*****************************************************************************
 Function Name  : IMSA_SRV_UpdateEmsStatus
 Description    : 更新网侧是否支持EMS标识
 Input          : enEmsInd----------------------EMS标识
                  ulIsNotfiyEmcNoSrv------------是否通知紧急服务无服务
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-10-11  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_UpdateEmsStatus
(
    MSCC_IMSA_EMS_INDICATOR_ENUM_UINT8           enEmsInd
)
{
    IMSA_NETWORK_INFO_STRU             *pstNwInfo           = VOS_NULL_PTR;

    pstNwInfo = IMSA_GetNetInfoAddress();

    pstNwInfo->enImsaEmsStatus = enEmsInd;

}


/*****************************************************************************
 Function Name  : IMSA_SRV_ProcWhenRoamNotSatisfiedConnReging
 Description    : 处理漫游网络去注册流程的函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-30  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcWhenRoamNotSatisfiedConnReging(VOS_VOID)
{
    IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_DEREGING);

    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_NOT_LOCAL);
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          VOS_FALSE,
                                          VOS_FALSE);

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_NOT_LOCAL);
            break;

        case IMSA_RESOURCE_STATUS_NULL:

            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          VOS_FALSE,
                                          VOS_FALSE);

            //IMSA_DsdsSaveMoSmsMsg(pstRpDataReq);
            break;
        #endif
        default:
            #if (FEATURE_ON == FEATURE_DSDS)
            IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                             RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            #endif
            break;

    }
}
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcWhenRoamNotSatisfiedConnReging
 Description    : 处理漫游网络去注册流程的函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-30  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcWhenRoamNotSatisfiedConningDeReg(VOS_VOID)
{

    IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_RELEASING_DEREG);

    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:

            IMSA_SRV_SndConnRelReq(IMSA_SRV_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          VOS_FALSE,
                                          VOS_FALSE);

            IMSA_SRV_SndConnRelReq(IMSA_SRV_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            break;

        case  IMSA_RESOURCE_STATUS_NULL:

            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          VOS_FALSE,
                                          VOS_FALSE);

            //IMSA_DsdsSaveMoSmsMsg(pstRpDataReq);
            break;
        #endif
        default:
            #if (FEATURE_ON == FEATURE_DSDS)
            IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                             RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            #endif
            break;

    }

}
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcWhenRoamNotSatisfiedConnReg
 Description    : 处理漫游网络去注册流程的函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-30  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcWhenRoamNotSatisfiedConnReg(VOS_VOID)
{

    IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_DEREGING);

    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_NOT_LOCAL);
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          VOS_FALSE,
                                          VOS_FALSE);

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_NOT_LOCAL);
            break;

        case  IMSA_RESOURCE_STATUS_NULL:

            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          VOS_FALSE,
                                          VOS_FALSE);

            //IMSA_DsdsSaveMoSmsMsg(pstRpDataReq);
            break;
        #endif
        default:
            /* */
            break;

    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcWhenRoamNotSatisfied
 Description    : 处理漫游网络去注册流程的函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-07-02  Draft Enact
      2.zhaochen 00308719   2015-08-25  Modify for VoLTE
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcWhenRoamNotSatisfied(VOS_VOID)
{
    IMSA_SRV_STATUS_ENUM_UINT8          enNrmSrvStatus      = IMSA_SRV_STATUS_BUTT;

    enNrmSrvStatus = IMSA_SRV_GetNormalSrvStatus();

    /* 如果当前有IMS业务存在，则需要等业务结束后，才能发起去注册 */
    if (VOS_TRUE == IMSA_IsImsExist())
    {
        return;
    }
    /* 如果当前普通服务支持漫游，则不处理 */
    if (IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_ROAM_NOT_SUPPORT != IMSA_SRV_IsNrmSrvConditonSatisfied())
    {
        return;
    }

    /* 根据当前服务状态进行不同处理 */
    switch (enNrmSrvStatus)
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:
            /* 通知MMA IMS VOICE  不可用 */
            /* 其他几种场景不满足IMS注册条件时，MMA自己能够识别，直接认为IMS voice不可用， 不需要IMSA
            通知；但是漫游网络下，且不支持IMS注册，MMA是无法识别的，所以需要IMSA主动通知一下 */
            IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE,IMSA_CONN_IsExitPersistentBearer());

            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_NotInitRegErrRecord();
            #endif
            break;
        case IMSA_SRV_STATUS_CONN_REGING:
            IMSA_SRV_ProcWhenRoamNotSatisfiedConnReging();
            break;

        case IMSA_SRV_STATUS_CONNING_DEREG:
        case IMSA_SRV_STATUS_CONN_DEREG:
            IMSA_SRV_ProcWhenRoamNotSatisfiedConningDeReg();
            break;

        case IMSA_SRV_STATUS_CONNING_REG:
            /* 需要通知IMS允许其发包，通知发起本地注册 */
            IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV);
            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

            /*释放资源 */
            #if (FEATURE_ON == FEATURE_DSDS)
            IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            #endif
            break;

        case IMSA_SRV_STATUS_CONN_REG:
            IMSA_SRV_ProcWhenRoamNotSatisfiedConnReg();
            break;

        default:
            /* 释放资源 */
            #if (FEATURE_ON == FEATURE_DSDS)
            IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            #endif
            break;
    }

}
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcNrmSrvConditionSatisfiedResult
 Description    : MMA服务变更消息处理函数
 Input          : pstServiceChangeInd-----------SERVICE CHANGE IND消息
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-30  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_SRV_PreProcNrmSrvConSatStatus
(
    IMSA_NRM_SRV_CON_SAT_STATUE_ENMUM_UINT32    enImsaSrvStatue
)
{
    switch(enImsaSrvStatue)
    {
        case IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_RAT_NOT_SUPPORT:
            IMSA_CMCCDeregProc();
            break;

        case IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_USIM_NOT_SUPPORT:
            /* 其他几种场景不满足IMS注册条件时，MMA自己能够识别，直接认为IMS voice不可用， 不需要IMSA
            通知；但是卡无效的场景，MMA是无法识别的，所以需要IMSA主动通知一下 */
            IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE,IMSA_CONN_IsExitPersistentBearer());
        #if (FEATURE_ON == FEATURE_PTM)
            IMSA_NotInitRegErrRecord();
        #endif
            break;

        case IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_ROAM_NOT_SUPPORT:
            /* 需要根据当前的服务状态，判断是直接通知VOICE不可用，还是发起去注册 */
            IMSA_CommonDeregProc();
            break;

        case IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_VOICE_NOT_SUPPORT:
            /* 中移动定制需求，如果IMS语音不支持，则发起去注册 */
            IMSA_CMCCDeregProc();
            break;

        case IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_OTHERS:
            /* IMS语音不支持或者PS域服务状态不为NORMAL SERVICE时，无特殊处理 */
        #if (FEATURE_ON == FEATURE_PTM)
            IMSA_NotInitRegErrRecord();
        #endif
            break;
        case IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_REG_FORBIDDEN:
            IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE,IMSA_CONN_IsExitPersistentBearer());
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_NotInitRegErrRecord();
            #endif
            break;

        default:
            return IMSA_TRUE;
    }

    return IMSA_FALSE;
}
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcServiceChangeIndIdleDereg
 Description    : MMA服务变更消息处理函数
 Input          : pstServiceChangeInd-----------SERVICE CHANGE IND消息
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181    2015-12-07  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcServiceChangeIndIdleDereg
(
    VOS_VOID
)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU                  *pstControlMagnaer   = VOS_NULL_PTR;

    pstControlMagnaer                       = IMSA_GetControlManagerAddress();
    #endif

    switch(IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                          IMSA_FALSE,
                                          IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                          IMSA_FALSE,
                                          IMSA_FALSE);

            /* 请求连接模块建立连接，将状态转到IMSA_SERVICE_STATUS_CONNING_DEREG */
            IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                        IMSA_CONN_TYPE_NORMAL);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONNING_DEREG);
            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            break;
        #endif
        case IMSA_RESOURCE_STATUS_ACTIVE:

            /* 请求连接模块建立连接，将状态转到IMSA_SERVICE_STATUS_CONNING_DEREG */
            IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                        IMSA_CONN_TYPE_NORMAL);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONNING_DEREG);

            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            }
            #endif
            break;
        default:
            break;
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcServiceChangeIndIdleDereg
 Description    : MMA服务变更消息处理函数
 Input          : pstServiceChangeInd-----------SERVICE CHANGE IND消息
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181    2015-12-07  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcServiceChangeIndConnDereging
(
    VOS_VOID
)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU                  *pstControlMagnaer   = VOS_NULL_PTR;

    pstControlMagnaer                       = IMSA_GetControlManagerAddress();
    #endif

    switch(IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                          IMSA_FALSE,
                                          IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                          IMSA_FALSE,
                                          IMSA_FALSE);

            IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE,IMSA_CONN_IsExitPersistentBearer());

            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONN_REGING);

            IMSA_SRV_SndRegDeregReq(    IMSA_REG_TYPE_NORMAL,
                                        IMSA_DEREG_LOCAL);

            IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                        IMSA_REG_ADDR_PARAM_NEW);

            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            }
            break;
        case IMSA_RESOURCE_STATUS_APPLYING:
            /* 修改触发源为获取服务 */
            IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                             RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            break;
        #endif
        case IMSA_RESOURCE_STATUS_ACTIVE:

            IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE,IMSA_CONN_IsExitPersistentBearer());

            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONN_REGING);

            IMSA_SRV_SndRegDeregReq(    IMSA_REG_TYPE_NORMAL,
                                        IMSA_DEREG_LOCAL);

            IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                        IMSA_REG_ADDR_PARAM_NEW);

            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                /* 修改触发源为获取服务 */
                IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                                 RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

                IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
                IMSA_StopTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            }
            #endif
            break;

        default:
            break;
    }
}
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcServiceChangeIndIdleDereg
 Description    : MMA服务变更消息处理函数
 Input          : pstServiceChangeInd-----------SERVICE CHANGE IND消息
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181    2015-12-07  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcServiceChangeIndConnDereg
(
    VOS_VOID
)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU                  *pstControlMagnaer   = VOS_NULL_PTR;

    pstControlMagnaer                       = IMSA_GetControlManagerAddress();
    #endif

    switch(IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                          IMSA_REG_ADDR_PARAM_NEW,
                                          IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                          IMSA_REG_ADDR_PARAM_NEW,
                                          IMSA_FALSE);

            /* 请求注册模块发起注册，将状态转到IMSA_SERVICE_STATUS_CONN_REGING */
            IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                        IMSA_REG_ADDR_PARAM_NEW);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONN_REGING);

            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            break;
        #endif
        case IMSA_RESOURCE_STATUS_ACTIVE:

            /* 请求注册模块发起注册，将状态转到IMSA_SERVICE_STATUS_CONN_REGING */
            IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                        IMSA_REG_ADDR_PARAM_NEW);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONN_REGING);
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            }
            #endif
            break;
        default:
            break;
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcServiceChangeInd
 Description    : MMA服务变更消息处理函数
 Input          : pstServiceChangeInd-----------SERVICE CHANGE IND消息
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-04  Draft Enact
      2.wangchen 00209181    2015-11-18  Modify:volte dsds
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcServiceChangeInd
(
    const MSCC_IMSA_SERVICE_CHANGE_IND_STRU     *pstServiceChangeInd
)
{
    IMSA_NETWORK_INFO_STRU                     *pstNwInfo           = VOS_NULL_PTR;
    IMSA_CONTROL_MANAGER_STRU                  *pstControlMagnaer   = VOS_NULL_PTR;
    IMSA_SRV_STATUS_ENUM_UINT8                  enNrmSrvStatus      = IMSA_SRV_STATUS_BUTT;
    VOS_UINT32                                  ulIsNotfiyNrmNoSrv  = IMSA_FALSE;
    VOS_UINT32                                  ulIsNotfiyEmcNoSrv  = IMSA_FALSE;
    IMSA_NRM_SRV_CON_SAT_STATUE_ENMUM_UINT32    enImsaSrvStatue     = IMSA_NRM_SRV_CON_SAT_STATUE_BUTT;

    IMSA_INFO_LOG("IMSA_SRV_ProcServiceChangeInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcServiceChangeInd_ENUM, LNAS_ENTRY);

    /* 存储SERVICE CHANGE IND消息中携带的参数 */
    pstNwInfo                               = IMSA_GetNetInfoAddress();
    pstControlMagnaer                       = IMSA_GetControlManagerAddress();

    pstNwInfo->enImsaPsServiceStatus        = pstServiceChangeInd->enPsServiceStatus;
    /* 之前的漫游标记是通过CAMP_INFO_CHANGE_IND发过来的，但是并不准确，需要SERVICE_CHANGE_IND来通知给IMSA
       新增一个比特位bitRoamingValid，当该比特位为1时，代表漫游标志有效。此时IMSA更新本地维护的漫游状态。*/
    if (VOS_TRUE == pstServiceChangeInd->bitRoamingValid)
    {
        pstNwInfo->ucImsaRoamingFlg             = pstServiceChangeInd->ucRoamingFlg;
    }

    pstControlMagnaer->ucImsaUsimStatus     = pstServiceChangeInd->ucPsSimValid;

    /* 接入技术更新 */
    IMSA_SRV_UpdateRat(pstServiceChangeInd->enRat, &ulIsNotfiyNrmNoSrv, &ulIsNotfiyEmcNoSrv);

    /* 只有是正常服务时，才更新网络支持IMS和EMS指示 */
    if (MSCC_IMSA_NORMAL_SERVICE == pstServiceChangeInd->enPsServiceStatus)
    {
        IMSA_SRV_UpdateImsVoPsStatus(pstServiceChangeInd->enImsVoPsInd);
        IMSA_SRV_UpdateEmsStatus(pstServiceChangeInd->enEmsInd);
    }

    enNrmSrvStatus = IMSA_SRV_GetNormalSrvStatus();

    /* 进入此分支，说明上次给TAF报的注册状态是未注册，目前只有在SRVCC快速挂断场景中会出现这种情况。 */
    if ((IMSA_SRV_STATUS_CONN_REG == enNrmSrvStatus) && (IMSA_NORMAL_REG_STATUS_REG != IMSA_GetLastNrmRegStatus()))
    {
        IMSA_SRV_NrmRegStatusNotify(IMSA_NORMAL_REG_STATUS_REG);

        IMSA_SetLastNrmRegStatus(IMSA_NORMAL_REG_STATUS_REG);
    }

    enImsaSrvStatue = IMSA_SRV_IsNrmSrvConditonSatisfied();

    if (VOS_FALSE== IMSA_SRV_PreProcNrmSrvConSatStatus(enImsaSrvStatue))
    {
        return;
    }


    /* 根据当前服务状态进行不同处理 */
    switch (enNrmSrvStatus)
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:

            /* 请求连接模块建立连接，将状态转到IMSA_SERVICE_STATUS_CONNING_DEREG */
            IMSA_SRV_ProcServiceChangeIndIdleDereg();
            break;

        case IMSA_SRV_STATUS_RELEASING_DEREG:

            /* 启动周期性尝试IMS服务定时器 */
            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
            break;

        case IMSA_SRV_STATUS_CONN_DEREGING:

            IMSA_SRV_ProcServiceChangeIndConnDereging();

            break;

        case IMSA_SRV_STATUS_CONN_DEREG:

            IMSA_SRV_ProcServiceChangeIndConnDereg();
            break;
        case IMSA_SRV_STATUS_CONNING_DEREG:
        case IMSA_SRV_STATUS_CONN_REGING:
        case IMSA_SRV_STATUS_CONNING_REG:
            /*这三个状态等注册完成后上报IMS voice能力*/
            break;
        default:
            /*IMSA不发起注册，需上报IMS voice能力*/
            if (IMSA_TRUE == IMSA_IsImsVoiceContidionSatisfied())
            {
                IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_AVAILABLE,IMSA_CONN_IsExitPersistentBearer());
            }
            else
            {
                IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE,IMSA_CONN_IsExitPersistentBearer());
            }

            break;
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcCampInfoChangeInd
 Description    : MMA漫游信息变更消息处理函数
 Input          : pstRoamingChangeInd-----------ROAMING CHANGE IND消息
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-27  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcCampInfoChangeInd
(
    const MSCC_IMSA_CAMP_INFO_CHANGE_IND_STRU     *pstCampInfoChangeInd
)
{
    IMSA_NETWORK_INFO_STRU             *pstNwInfo           = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_ProcCampInfoChangeInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcCampInfoChangeInd_ENUM, LNAS_ENTRY);

    /* 存储SERVICE CHANGE IND消息中携带的参数 */
    pstNwInfo                       = IMSA_GetNetInfoAddress();

    pstNwInfo->enAccessType         = pstCampInfoChangeInd->enAccessType;
    pstNwInfo->usLac                = pstCampInfoChangeInd->usLac;
    pstNwInfo->usTac                = pstCampInfoChangeInd->usTac;
    IMSA_MEM_CPY_S(                 &pstNwInfo->stPlmnId,
                                    sizeof(MSCC_IMSA_PLMN_ID_STRU),
                                    &pstCampInfoChangeInd->stPlmnId,
                                    sizeof(MSCC_IMSA_PLMN_ID_STRU));
    pstNwInfo->ulCellId             = pstCampInfoChangeInd->ulCellId;

    /* 配置CGI信息给IMS */
    IMSA_ConfigCgi2Ims();
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcVoiceDomainChangeInd
 Description    : MMA VOICE DOMAIN信息变更消息处理函数
 Input          : pstVoiceDomainChangeInd-----------VOICE DOMAIN CHANGE IND消息
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-02-26  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcVoiceDomainChangeInd
(
    const MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND_STRU     *pstVoiceDomainChangeInd
)
{
    IMSA_CONTROL_MANAGER_STRU      *pstControlManager;

    IMSA_INFO_LOG("IMSA_SRV_ProcVoiceDomainChangeInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcVoiceDomainChangeInd_ENUM, LNAS_ENTRY);

    pstControlManager = IMSA_GetControlManagerAddress();

    /* 存储VOICE DOMAIN CHANGE IND消息中携带的参数 */
    pstControlManager->stImsaConfigPara.enVoiceDomain = (IMSA_VOICE_DOMAIN_ENUM_UINT32)pstVoiceDomainChangeInd->enVoiceDomain;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcDeregReq()
 Description    : IMSA SERVICE模块处理DEREG请求
 Input          : enDeregCause----------去注册类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-05  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcDeregReq
(
    IMSA_SRV_DEREG_CAUSE_ENUM_UINT32    enDeregCause
)
{
    /* 保存去注册原因值 */
    IMSA_SetDeregCause(enDeregCause);

    /* 如果紧急服务已注册成功或者正在注册，则通知注册模块进行本地去注册 */
    if (IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetEmcSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcDeregReq:emc,conn&reging!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_EMERGENCY);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_REGISTERING);

        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_CONN_DEREG);

        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

        /* 通知CALL模块紧急呼叫服务进入无服务状态，促使CALL模块清除缓存的紧急呼 */
        IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                        IMSA_CALL_NO_SRV_CAUSE_REG_ERR);
    }

    if (IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetEmcSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcDeregReq:emc,conn&reg!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_EMERGENCY);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_REGISTERED);

        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_CONN_DEREG);

        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

        /* 由于已经进行本地去注册，无需再通知CALL模块紧急呼叫进入无服务状态，
           否则本地去注册流程和CALL释放流程同时进行，容易出问题 */
    }

    if (IMSA_SRV_STATUS_CONNING_DEREG == IMSA_SRV_GetEmcSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcDeregReq:emc,conning&dereg!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_EMERGENCY);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_CONNECTING);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_NOT_REGISTER);

        /* 通知CALL模块紧急呼叫服务进入无服务状态，促使CALL模块清除缓存的紧急呼 */
        IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                        IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);
    }

    /* 如果普通服务已注册成功或者正在注册，则通知注册模块进行去注册 */
    if ((IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetNormalSrvStatus())
        || (IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetNormalSrvStatus()))
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcDeregReq:dereg normal service!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_NORMAL);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_REGISTERING);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_REGISTERED);

        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_DEREGING);

        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_NOT_LOCAL);

        /* 由于已经进行去注册，无需再通知CALL模块普通呼叫进入无服务状态，
           否则去注册流程和CALL释放流程同时进行，容易出问题 */
        return ;
    }

    if (IMSA_SRV_STATUS_CONN_DEREGING == IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcDeregReq:wait for dereg result!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, 1);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_DEREGISTERING);
        return ;
    }

    IMSA_INFO_LOG("IMSA_SRV_ProcDeregReq:already dereg!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_NOT_REGISTER);

    IMSA_SndMsccMsgDeregCnf();
    return ;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcReceivedUsimReadfileCnf()
 Description    : USIM文件读取完成,发起初始注册
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719   2016-01-25  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcReceivedUsimReadfileCnf(VOS_VOID)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    pstControlMagnaer                       = IMSA_GetControlManagerAddress();
    #endif

    /* 如果状态不是IDLE_DEREG或当期不满足发起注册的条件，则返回 */
    if (IMSA_NRM_SRV_CON_SAT_STATUE_SUCC != IMSA_SRV_IsNrmSrvConditonSatisfied()
     || IMSA_SRV_STATUS_IDLE_DEREG != IMSA_SRV_GetNormalSrvStatus())
    {
        return;
    }

    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:
            IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                        IMSA_CONN_TYPE_NORMAL);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONNING_DEREG);
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_NOT_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            }
            #endif
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                       IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                       IMSA_FALSE,
                                       IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

           IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                       IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                       IMSA_FALSE,
                                       IMSA_FALSE);

            IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                    IMSA_CONN_TYPE_NORMAL);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONNING_DEREG);

            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            break;
        #endif
        default:
            break;
    }
    return;
}

/*****************************************************************************
 Function Name  : IMSA_StartImsNormalService
 Description    : 控制管理模块提供给呼叫模块的API, Call模块在打普通电话时调用
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32
                  返回结果是0，表示Control可以提供正常服务，Call可以直接打电话
                  返回结果是1，表示不能提供正常服务，打正常电话失败

 History        :
      1.lihong 00150010      2013-07-05  Draft Enact
      2.wangchen 00209181   2015-08-17 Modify:CHR
*****************************************************************************/
VOS_UINT32 IMSA_StartImsNormalService
(
    IMSA_CALL_TYPE_ENUM_UINT8               enCallType
)
{
    /* 如果当前已经有一路电话，说明下面的条件都已经判断过一次了。
       对于服务状态和涉及NV的标志，在有呼叫时是不可能改变的；
       对于网侧的状态，由于当前已经有一路电话，即使网侧能力发生改变，
       IMSA也不会发起去注册流程，故界面显示仍然是VoLTE可用。
       故只需要对呼叫类型进行判断，其他条件不做判断 */
    if ((IMSA_CALL_TYPE_VOICE == enCallType)
        && (VOS_FALSE == IMSA_GetUeImsVoiceCap()))
    {
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( enCallType,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_UE_CAP_NOT_SUPPORT_VOICE_CALL,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NONE,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;
    }

    if ((IMSA_CALL_TYPE_VIDEO == enCallType)
        && (VOS_FALSE == IMSA_GetUeImsVideoCap()))
    {
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( enCallType,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_UE_CAP_NOT_SUPPORT_VIDEO_CALL,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NONE,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;
    }

    if (VOS_TRUE == IMSA_IsCallConnExist())
    {
        return IMSA_START_SRV_RESULT_CAN_MAKE_CALL;
    }

    if (IMSA_SRV_STATUS_CONN_REG != IMSA_SRV_GetNormalSrvStatus())
    {
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( enCallType,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NORM_SER_NOT_CONN_REG,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NONE,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;
    }

    if (IMSA_VOICE_DOMAIN_CS_ONLY == IMSA_GetVoiceDomain())
    {
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( enCallType,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_VOICE_DOMAIN_CS_ONLY,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NONE,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;
    }

    if (IMSA_IMS_VOPS_STATUS_NOT_SUPPORT == IMSA_GetNwImsVoiceCap())
    {
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( enCallType,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_IMS_VOPS_STATUS_NOT_SUPPORT,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NONE,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;
    }

    return IMSA_START_SRV_RESULT_CAN_MAKE_CALL;
}

/*****************************************************************************
 Function Name  : IMSA_StartImsNormalService
 Description    : 控制管理模块提供给呼叫模块的API, Call模块在打紧急电话时调用
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32
                  返回结果是0，表示Control可以提供紧急服务，Call可以直接打电话
                  返回结果是1，表示不能提供紧急服务，打紧急电话失败
                  返回结果是2，表示暂时不能提供紧急服务，正在建立紧急服务，Call模块需要缓存电话

 History        :
      1.wangchen 00209181    2015-11-28  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_StartImsEmergServiceAbilityCheck
(
    IMSA_EMC_CALL_TYPE_ENUM_UINT32     *penEmcCallType
)
{
    IMSA_SRV_STATUS_ENUM_UINT8          enEmcSrvStatus      = IMSA_SRV_STATUS_BUTT;

    IMSA_INFO_LOG("IMSA_StartImsEmergService is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, LNAS_ENTRY);


    /* 判断获取紧急IMS服务的条件是否具备，如果不具备，则返回不能打紧急呼 */
    if (IMSA_TRUE != IMSA_SRV_IsEmcSrvConditonSatisfied())
    {
        IMSA_INFO_LOG("IMSA_StartImsEmergService:EMC service condition not satisfied!");
        TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, 1);
        return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;
    }

    /* 如果可以在正常服务上发起紧急呼，则直接返回能打紧急呼 */
    if (IMSA_TRUE == IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied())
    {
        IMSA_INFO_LOG("IMSA_StartImsEmergService:can make emc call in normal service!");
        TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, 2);
        *penEmcCallType = IMSA_EMC_CALL_TYPE_IN_NORMAL_SRV;
        return IMSA_START_SRV_RESULT_CAN_MAKE_CALL;
    }

    enEmcSrvStatus      = IMSA_SRV_GetEmcSrvStatus();

    /* 根据当前服务状态进行不同处理 */
    switch (enEmcSrvStatus)
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:

            break;

        case IMSA_SRV_STATUS_RELEASING_DEREG:

            return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;

        case IMSA_SRV_STATUS_CONN_DEREG:

            /*  如果是无卡紧急呼，则直接返回能打紧急呼 */
            if (IMSA_FALSE == IMSA_SRV_IsNrmSrvIsimParaSatisfied())
            {
                IMSA_INFO_LOG("IMSA_StartImsEmergService:can make anonymous emc call in conn dereg!");
                TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, IMSA_STATUS_CONN);
                TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, IMSA_STATUS_NOT_REGISTER);
                *penEmcCallType = IMSA_EMC_CALL_TYPE_NO_CARD;
                return IMSA_START_SRV_RESULT_CAN_MAKE_CALL;
            }

            break;

        case IMSA_SRV_STATUS_CONN_REG:

            *penEmcCallType = IMSA_EMC_CALL_TYPE_EMC_CONN_EMC_REG;
            return IMSA_START_SRV_RESULT_CAN_MAKE_CALL;

        default:
            break;
    }


    if (IMSA_FALSE == IMSA_SRV_IsNrmSrvIsimParaSatisfied())
    {
        *penEmcCallType = IMSA_EMC_CALL_TYPE_NO_CARD;
    }
    else
    {
        *penEmcCallType = IMSA_EMC_CALL_TYPE_EMC_CONN_EMC_REG;
    }


    return IMSA_START_SRV_RESULT_BUFFER_CALL_WAIT_INDICATION;
}
/*****************************************************************************
 Function Name  : IMSA_StartImsNormalService
 Description    : 控制管理模块提供给呼叫模块的API, Call模块在打紧急电话时调用
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32
                  返回结果是0，表示Control可以提供紧急服务，Call可以直接打电话
                  返回结果是1，表示不能提供紧急服务，打紧急电话失败
                  返回结果是2，表示暂时不能提供紧急服务，正在建立紧急服务，Call模块需要缓存电话

 History        :
      1.lihong 00150010      2013-07-05  Draft Enact
      2.wangchen 00209181    2015-11-23  Modify:volte dsds
*****************************************************************************/
VOS_VOID IMSA_StartImsEmcService
(
    VOS_VOID
)
{
    IMSA_SRV_STATUS_ENUM_UINT8          enEmcSrvStatus      = IMSA_SRV_STATUS_BUTT;

    enEmcSrvStatus      = IMSA_SRV_GetEmcSrvStatus();

    /* 根据当前服务状态进行不同处理 */
    switch (enEmcSrvStatus)
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:

            /* 请求连接模块建立连接，将状态转到IMSA_SERVICE_STATUS_CONNING_DEREG */
            IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                        IMSA_CONN_TYPE_EMC);
            IMSA_SRV_SetServcieStatus(  IMSA_CONN_TYPE_EMC,
                                        IMSA_SRV_STATUS_CONNING_DEREG);
            break;

        case IMSA_SRV_STATUS_CONN_DEREG:

            /* 请求注册模块发起注册，将状态转到IMSA_SERVICE_STATUS_CONN_REGING */
            IMSA_SRV_SndRegRegReq(      IMSA_CONN_TYPE_EMC,
                                        IMSA_REG_ADDR_PARAM_NEW);
            IMSA_SRV_SetServcieStatus(  IMSA_CONN_TYPE_EMC,
                                        IMSA_SRV_STATUS_CONN_REGING);
            break;


        default:
            break;
    }

    return;
}


/*****************************************************************************
 Function Name  : IMSA_StartImsNormalService
 Description    : 控制管理模块提供给呼叫模块的API, Call模块在打紧急电话时调用
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32
                  返回结果是0，表示Control可以提供紧急服务，Call可以直接打电话
                  返回结果是1，表示不能提供紧急服务，打紧急电话失败
                  返回结果是2，表示暂时不能提供紧急服务，正在建立紧急服务，Call模块需要缓存电话

 History        :
      1.lihong 00150010      2013-07-05  Draft Enact
      2.wangchen 00209181    2015-11-23  Modify:volte dsds
*****************************************************************************/
VOS_UINT32 IMSA_StartImsEmergService
(
    IMSA_EMC_CALL_TYPE_ENUM_UINT32     *penEmcCallType
)
{
    IMSA_SRV_STATUS_ENUM_UINT8          enEmcSrvStatus      = IMSA_SRV_STATUS_BUTT;

    IMSA_INFO_LOG("IMSA_StartImsEmergService is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, LNAS_ENTRY);

    /* 判断获取紧急IMS服务的条件是否具备，如果不具备，则返回不能打紧急呼 */
    if (IMSA_TRUE != IMSA_SRV_IsEmcSrvConditonSatisfied())
    {
        IMSA_INFO_LOG("IMSA_StartImsEmergService:EMC service condition not satisfied!");
        TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, 1);
        return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;
    }

    /* 如果可以在正常服务上发起紧急呼，则直接返回能打紧急呼 */
    if (IMSA_TRUE == IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied())
    {
        IMSA_INFO_LOG("IMSA_StartImsEmergService:can make emc call in normal service!");
        TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, 2);
        *penEmcCallType = IMSA_EMC_CALL_TYPE_IN_NORMAL_SRV;
        return IMSA_START_SRV_RESULT_CAN_MAKE_CALL;
    }

    enEmcSrvStatus      = IMSA_SRV_GetEmcSrvStatus();

    /* 根据当前服务状态进行不同处理 */
    switch (enEmcSrvStatus)
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:

            /* 请求连接模块建立连接，将状态转到IMSA_SERVICE_STATUS_CONNING_DEREG */
            IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                        IMSA_CONN_TYPE_EMC);
            IMSA_SRV_SetServcieStatus(  IMSA_CONN_TYPE_EMC,
                                        IMSA_SRV_STATUS_CONNING_DEREG);
            break;

        case IMSA_SRV_STATUS_RELEASING_DEREG:

            /* 暂时先实现成不允许打紧急呼，到CS域尝试，后续可以根据用户需求调整为
               启动定时器等链路释放完成之后再建立紧急连接 */
            IMSA_INFO_LOG("IMSA_StartImsEmergService:can not make emc call as in releasing&dereg state!");
            TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, IMSA_STATUS_RELEASING);
            TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, IMSA_STATUS_NOT_REGISTER);

            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_EmcCallErrRecord(  IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_EMC_REG_FAIL,
                                    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_SERVICE_STATUS_ERROR,
                                    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NONE,
                                    VOS_FALSE,
                                    VOS_FALSE,
                                    IMSA_ERR_LOG_CALL_STATUS_IDLE);
            #endif

            return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;

        case IMSA_SRV_STATUS_CONN_DEREG:

            /*  如果是无卡紧急呼，则直接返回能打紧急呼 */
            if (IMSA_FALSE == IMSA_SRV_IsNrmSrvIsimParaSatisfied())
            {
                IMSA_INFO_LOG("IMSA_StartImsEmergService:can make anonymous emc call in conn dereg!");
                TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, IMSA_STATUS_CONN);
                TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, IMSA_STATUS_NOT_REGISTER);
                *penEmcCallType = IMSA_EMC_CALL_TYPE_NO_CARD;
                return IMSA_START_SRV_RESULT_CAN_MAKE_CALL;
            }

            /* 请求注册模块发起注册，将状态转到IMSA_SERVICE_STATUS_CONN_REGING */
            IMSA_SRV_SndRegRegReq(      IMSA_CONN_TYPE_EMC,
                                        IMSA_REG_ADDR_PARAM_NEW);
            IMSA_SRV_SetServcieStatus(  IMSA_CONN_TYPE_EMC,
                                        IMSA_SRV_STATUS_CONN_REGING);
            break;

        case IMSA_SRV_STATUS_CONN_REG:

            IMSA_INFO_LOG("IMSA_StartImsEmergService:can make emc call in conn reg!");
            TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, IMSA_STATUS_REGISTERED);
            *penEmcCallType = IMSA_EMC_CALL_TYPE_EMC_CONN_EMC_REG;
            return IMSA_START_SRV_RESULT_CAN_MAKE_CALL;

        default:
            break;
    }


    if (IMSA_FALSE == IMSA_SRV_IsNrmSrvIsimParaSatisfied())
    {
        *penEmcCallType = IMSA_EMC_CALL_TYPE_NO_CARD;
    }
    else
    {
        *penEmcCallType = IMSA_EMC_CALL_TYPE_EMC_CONN_EMC_REG;
    }


    return IMSA_START_SRV_RESULT_BUFFER_CALL_WAIT_INDICATION;
}
/*****************************************************************************
 Function Name  : IMSA_ProcTimerMsgPeriodTryImsSrvExpIdleDereg()
 Description    : 周期性尝试IMS服务定时器超时,发起初始注册
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcTimerMsgPeriodTryImsSrvExpIdleDereg(VOS_VOID)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    pstControlMagnaer                       = IMSA_GetControlManagerAddress();
    #endif

    if (IMSA_NRM_SRV_CON_SAT_STATUE_SUCC != IMSA_SRV_IsNrmSrvConditonSatisfied())
    {
        return;
    }

    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:
            IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                        IMSA_CONN_TYPE_NORMAL);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONNING_DEREG);
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_NOT_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            }
            #endif
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                       IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                       IMSA_FALSE,
                                       IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

           IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                       IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                       IMSA_FALSE,
                                       IMSA_FALSE);

            IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                    IMSA_CONN_TYPE_NORMAL);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONNING_DEREG);

            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            break;
        #endif
        default:
            break;
    }
    return;
}

/*****************************************************************************
 Function Name  : IMSA_ProcTimerMsgPeriodTryImsSrvExpConnDereg()
 Description    : 周期性尝试IMS服务定时器超时,发起初始注册
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcTimerMsgPeriodTryImsSrvExpConnDereg(VOS_VOID)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;
    #endif
    IMSA_NRM_SRV_CON_SAT_STATUE_ENMUM_UINT32    enSrvRst    = IMSA_NRM_SRV_CON_SAT_STATUE_BUTT;

    #if (FEATURE_ON == FEATURE_DSDS)
    pstControlMagnaer                       = IMSA_GetControlManagerAddress();
    #endif
    enSrvRst                                = IMSA_SRV_IsNrmSrvConditonSatisfied();

    if (IMSA_NRM_SRV_CON_SAT_STATUE_SUCC != enSrvRst)
    {
        return;
    }

    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:
            IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                    IMSA_REG_ADDR_PARAM_NEXT);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONN_REGING);
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            }
            #endif
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                       IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                       IMSA_REG_ADDR_PARAM_NEXT,
                                       IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

           IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                       IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                       IMSA_REG_ADDR_PARAM_NEXT,
                                       IMSA_FALSE);

            IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                        IMSA_REG_ADDR_PARAM_NEXT);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONN_REGING);

            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            break;
        #endif
        default:
            break;
    }

}
/*****************************************************************************
 Function Name  : IMSA_ProcTimerMsgPeriodTryImsSrvExpConnDereg()
 Description    : 周期性尝试IMS服务定时器超时,发起初始注册
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcTimerMsgPeriodTryImsSrvExpConningReg(VOS_VOID)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;
    #endif
    IMSA_NRM_SRV_CON_SAT_STATUE_ENMUM_UINT32    enSrvStatus = IMSA_NRM_SRV_CON_SAT_STATUE_BUTT;

    #if (FEATURE_ON == FEATURE_DSDS)
    pstControlMagnaer                   = IMSA_GetControlManagerAddress();
    #endif
    enSrvStatus                         = IMSA_SRV_IsNrmSrvConditonSatisfied();


    if (IMSA_NRM_SRV_CON_SAT_STATUE_SUCC != enSrvStatus)
    {
        IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV);

        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_NormInitDeregErrRecord(IMSA_ERR_LOG_INIT_DEREG_REASON_PDN_LOST);
        #endif
        return;
    }

    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:
            IMSA_SRV_SndConnSetupReq(   IMSA_TRUE,
                                        IMSA_CONN_TYPE_NORMAL);

            /* 启动注册时长保护定时器 */
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            }
            #endif
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                       IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                       IMSA_FALSE,
                                       IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

           IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                       IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                       IMSA_FALSE,
                                       IMSA_FALSE);

            IMSA_SRV_SndConnSetupReq(   IMSA_TRUE,
                                        IMSA_CONN_TYPE_NORMAL);

            /* 启动注册时长保护定时器 */
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            }
            #endif
            break;
        #endif
        default:
            break;
    }

}

/*****************************************************************************
 Function Name  : IMSA_ProcTimerMsgPeriodTryImsSrvExp()
 Description    : 周期性尝试IMS服务定时器超时处理
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcTimerMsgPeriodTryImsSrvExp(const VOS_VOID *pRcvMsg )
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;
    (void)pRcvMsg;

    IMSA_INFO_LOG("IMSA_ProcTimerMsgPeriodTryImsSrvExp is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, LNAS_ENTRY);

    pstControlMagnaer  = IMSA_GetControlManagerAddress();

    switch (IMSA_SRV_GetNormalSrvStatus())
    {
        case IMSA_SRV_STATUS_CONNING_DEREG:

            IMSA_INFO_LOG("IMSA_ProcTimerMsgPeriodTryImsSrvExp:conning&dereg or conn&reging!");
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_CONNECTING);
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_NOT_REGISTER);

            IMSA_StopTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
            break;

        case IMSA_SRV_STATUS_RELEASING_DEREG:

            IMSA_INFO_LOG("IMSA_ProcTimerMsgPeriodTryImsSrvExp:releasing&dereg!");
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_RELEASING);
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_NOT_REGISTER);

            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
            break;

        case IMSA_SRV_STATUS_IDLE_DEREG:

            IMSA_INFO_LOG("IMSA_ProcTimerMsgPeriodTryImsSrvExp:idle&dereg!");
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_IDLE);
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_NOT_REGISTER);

            IMSA_ProcTimerMsgPeriodTryImsSrvExpIdleDereg();

            break;
        case IMSA_SRV_STATUS_CONN_DEREG:

            IMSA_INFO_LOG("IMSA_ProcTimerMsgPeriodTryImsSrvExp:conn&dereg!");
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_NOT_REGISTER);

            IMSA_ProcTimerMsgPeriodTryImsSrvExpConnDereg();

            break;
        case IMSA_SRV_STATUS_CONNING_REG:

            IMSA_INFO_LOG("IMSA_ProcTimerMsgPeriodTryImsSrvExp:conning&reg!");
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_CONNECTING);
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_REGISTERED);
            IMSA_ProcTimerMsgPeriodTryImsSrvExpConningReg();

            break;
        default:
            IMSA_INFO_LOG("IMSA_ProcTimerMsgPeriodTryImsSrvExp:other states!");
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, 1);
            break;
    }
}

/* delete PeriodImsEmcSrvTryTimer */

/*****************************************************************************
 Function Name  : IMSA_AddSubscription()
 Description    : IMSA对外提供的注册订阅接口
 Input          : ulPid---------------订阅者的PID
                  enType--------------订阅内容类型
                  ulPara--------------会在内容更新消息中携带的参数
 Output         : pulSubscriptionId---订阅ID指针
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-10  Draft Enact
*****************************************************************************/
VOS_UINT32  IMSA_AddSubscription
(
    VOS_UINT32                          ulPid,
    IMSA_SUBCRIBE_TYPE_ENUM_UINT8       enType,
    VOS_UINT32                          ulPara,
    VOS_UINT32                         *pulSubscriptionId
)
{
    IMSA_SUBSCRIPTION_INFO_STRU        *pstSubcriptionInfo      = VOS_NULL_PTR;
    IMSA_SUBSCRIPTION_INFO_LIST_STRU   *pstSubcriptionInfoList  = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_AddSubscription is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_AddSubscription_ENUM, LNAS_ENTRY);

    pstSubcriptionInfoList  = IMSA_GetSubcriptionInfoListAddr();

    /* 判断是否已经存满，如果是，则返回失败 */
    if (pstSubcriptionInfoList->ulSubscriptionNum >= IMSA_MAX_SUBSCRIPTION_NUM)
    {
        IMSA_WARN_LOG("IMSA_AddSubscription:can not save more!");
        TLPS_PRINT2LAYER_INFO(IMSA_AddSubscription_ENUM, 1);
        return IMSA_FAIL;
    }

    /* 订阅内容是否合法 */
    if (enType >= IMSA_SUBCRIBE_TYPE_BUTT)
    {
        IMSA_WARN_LOG("IMSA_AddSubscription:type illegal!");
        TLPS_PRINT2LAYER_INFO(IMSA_AddSubscription_ENUM, LNAS_PARAM_INVALID);
        return IMSA_FAIL;
    }

    /* 判断输入指针是否合法 */
    if (pulSubscriptionId == VOS_NULL_PTR)
    {
        IMSA_WARN_LOG("IMSA_AddSubscription:null pointer!");
        TLPS_PRINT2LAYER_INFO(IMSA_AddSubscription_ENUM, LNAS_NULL_PTR);
        return IMSA_FAIL;
    }

    /* 存储签约信息 */
    pstSubcriptionInfo = &pstSubcriptionInfoList->astSubcriptionInfoArray[pstSubcriptionInfoList->ulSubscriptionNum];
    pstSubcriptionInfo->ulPid               = ulPid;
    pstSubcriptionInfo->enType              = enType;
    pstSubcriptionInfo->ulPara              = ulPara;
    pstSubcriptionInfo->ulSubscriptionId    = pstSubcriptionInfoList->ulMaxSubscriptionId;
    *pulSubscriptionId                      = pstSubcriptionInfoList->ulMaxSubscriptionId;
    pstSubcriptionInfoList->ulMaxSubscriptionId++;
    pstSubcriptionInfoList->ulSubscriptionNum++;

    return IMSA_SUCC;
}

/*****************************************************************************
 Function Name  : IMSA_DeleteSubscription()
 Description    : IMSA对外提供的取消订阅接口
 Input          : ulSubscriberId---------------订阅ID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-10  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_DeleteSubscription
(
    VOS_UINT32                  ulSubscriptionId
)
{
    VOS_UINT32                          i                       = IMSA_NULL;
    IMSA_SUBSCRIPTION_INFO_LIST_STRU   *pstSubcriptionInfoList  = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_DeleteSubscription is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_DeleteSubscription_ENUM, LNAS_ENTRY);

    pstSubcriptionInfoList  = IMSA_GetSubcriptionInfoListAddr();

    for (i = 0; i < pstSubcriptionInfoList->ulSubscriptionNum; i++)
    {
        if (ulSubscriptionId == pstSubcriptionInfoList->astSubcriptionInfoArray[i].ulSubscriptionId)
        {
            IMSA_MEM_CPY_S( &pstSubcriptionInfoList->astSubcriptionInfoArray[i],
                            sizeof(IMSA_SUBSCRIPTION_INFO_STRU)*((pstSubcriptionInfoList->ulSubscriptionNum - 1) - i),
                            &pstSubcriptionInfoList->astSubcriptionInfoArray[i+1],
                            sizeof(IMSA_SUBSCRIPTION_INFO_STRU)*((pstSubcriptionInfoList->ulSubscriptionNum - 1) - i));

            pstSubcriptionInfoList->ulSubscriptionNum--;
            return IMSA_SUCC;
        }
    }

    return IMSA_SUCC;
}


VOS_VOID IMSA_SRV_PrintNrmSrvState( VOS_VOID )
{
    switch (IMSA_SRV_GetNormalSrvStatus())
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:
            IMSA_INFO_LOG("Current Normal Service State: IDLE+DEREG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_IDLE);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_SRV_STATUS_CONNING_DEREG:
            IMSA_INFO_LOG("Current Normal Service State: CONNING+DEREG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_CONNECTING);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_SRV_STATUS_CONNING_REG:
            IMSA_INFO_LOG("Current Normal Service State: CONNING+REG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_CONNECTING);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_REGISTERED);
            break;
        case IMSA_SRV_STATUS_RELEASING_DEREG:
            IMSA_INFO_LOG("Current Normal Service State: RELEASING+DEREG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_RELEASING);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_SRV_STATUS_CONN_DEREG:
            IMSA_INFO_LOG("Current Normal Service State: CONN+DEREG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_SRV_STATUS_CONN_REGING:
            IMSA_INFO_LOG("Current Normal Service State: CONN+REGING");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_REGISTERING);
            break;
        case IMSA_SRV_STATUS_CONN_DEREGING:
            IMSA_INFO_LOG("Current Normal Service State: CONN+DEREGING");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_DEREGISTERING);
            break;
        case IMSA_SRV_STATUS_CONN_REG:
            IMSA_INFO_LOG("Current Normal Service State: CONN+REG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_REGISTERED);
            break;
        default:
            IMSA_INFO_LOG("Current Normal Service State: UNKNOWN");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_UNKNOWN);
            break;
    }
}


VOS_VOID IMSA_SRV_PrintEmcSrvState( VOS_VOID )
{
    switch (IMSA_SRV_GetEmcSrvStatus())
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:
            IMSA_INFO_LOG("Current Emc Service State: IDLE+DEREG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_IDLE);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_SRV_STATUS_CONNING_DEREG:
            IMSA_INFO_LOG("Current Emc Service State: CONNING+DEREG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_CONNECTING);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_SRV_STATUS_CONNING_REG:
            IMSA_INFO_LOG("Current Emc Service State: CONNING+REG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_CONNECTING);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_REGISTERED);
            break;
        case IMSA_SRV_STATUS_RELEASING_DEREG:
            IMSA_INFO_LOG("Current Emc Service State: RELEASING+DEREG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_RELEASING);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_SRV_STATUS_CONN_DEREG:
            IMSA_INFO_LOG("Current Emc Service State: CONN+DEREG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_SRV_STATUS_CONN_REGING:
            IMSA_INFO_LOG("Current Emc Service State: CONN+REGING");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_REGISTERING);
            break;
        case IMSA_SRV_STATUS_CONN_DEREGING:
            IMSA_INFO_LOG("Current Emc Service State: CONN+DEREGING");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_DEREGISTERING);
            break;
        case IMSA_SRV_STATUS_CONN_REG:
            IMSA_INFO_LOG("Current Emc Service State: CONN+REG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_REGISTERED);
            break;
        default:
            IMSA_INFO_LOG("Current Emc Service State: UNKNOWN");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_UNKNOWN);
            break;
    }
}

/*****************************************************************************
 Function Name   : IMSA_SRV_IsConningRegState
 Description     :
 Input           : ucIsEmc---------1:紧急， 0:普通
 Output          : None
 Return          : VOS_INT32

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_UINT32 IMSA_SRV_IsConningRegState(VOS_UINT8 ucIsEmc)
{
    IMSA_SRV_STATUS_ENUM_UINT8          enImsaSrvStatus = IMSA_SRV_STATUS_BUTT;

    if (1 == ucIsEmc)
    {
        enImsaSrvStatus = IMSA_SRV_GetEmcSrvStatus();
    }
    else
    {
        enImsaSrvStatus = IMSA_SRV_GetNormalSrvStatus();
    }

    if (IMSA_SRV_STATUS_CONNING_REG != enImsaSrvStatus)
    {
        return IMSA_FALSE;
    }

    return IMSA_TRUE;
}
/*****************************************************************************
 Function Name   : IMSA_CMCCDeregProcConnRegOrReging
 Description     : 中国移动定制需求，条件满足时发起IMS去注册
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen 00209181    2015-12-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CMCCDeregProcConnRegOrReging(VOS_VOID)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU                  *pstControlMagnaer   = VOS_NULL_PTR;

    pstControlMagnaer                       = IMSA_GetControlManagerAddress();
    #endif

    IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_DEREGING);

    /* 如果有定时器在运行，是否需要停止定时器? */
    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:
            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_NOT_LOCAL);
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
                IMSA_StartTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            }
            #endif
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          VOS_FALSE,
                                          VOS_FALSE);

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_NOT_LOCAL);

            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
            IMSA_StartTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            break;

        case  IMSA_RESOURCE_STATUS_NULL:

            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          VOS_FALSE,
                                          VOS_FALSE);

            //IMSA_DsdsSaveMoSmsMsg(pstRpDataReq);
            break;
        #endif
        default:
            #if (FEATURE_ON == FEATURE_DSDS)
            IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                             RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            #endif
            break;

    }


    #if (FEATURE_ON == FEATURE_PTM)
    /* 记录发起去注册的原因值 */
    IMSA_NormInitDeregErrRecord(IMSA_ERR_LOG_INIT_DEREG_REASON_RAT_OR_VOICE_NOT_SUPPORT);
    #endif
}
/*****************************************************************************
 Function Name   : IMSA_CMCCDeregProcConnRegOrReging
 Description     : 中国移动定制需求，条件满足时发起IMS去注册
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen 00209181    2015-12-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CMCCDeregProcConnOrConningDereg(VOS_VOID)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU                  *pstControlMagnaer   = VOS_NULL_PTR;

    pstControlMagnaer                       = IMSA_GetControlManagerAddress();
    #endif

    IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_RELEASING_DEREG);

    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:
            IMSA_SRV_SndConnRelReq(IMSA_SRV_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
                IMSA_StartTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            }
            #endif
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          VOS_FALSE,
                                          VOS_FALSE);

            IMSA_SRV_SndConnRelReq(IMSA_SRV_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
                IMSA_StartTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            }
            break;

        case  IMSA_RESOURCE_STATUS_NULL:

            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          VOS_FALSE,
                                          VOS_FALSE);

            //IMSA_DsdsSaveMoSmsMsg(pstRpDataReq);
            break;
        #endif
        default:
            #if (FEATURE_ON == FEATURE_DSDS)
            IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                             RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            #endif
            break;

    }

    #if (FEATURE_ON == FEATURE_PTM)
    IMSA_NormInitDeregErrRecord(IMSA_ERR_LOG_INIT_DEREG_REASON_RAT_OR_VOICE_NOT_SUPPORT);
    #endif
}

/*****************************************************************************
 Function Name   : IMSA_CMCCDeregProc
 Description     : 中国移动定制需求，条件满足时发起IMS去注册
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.mengchao 00277840    2014-08-20  Draft Enact
    2.wangchen 00209181    2015-06-23  Modify:CONNING_REG
*****************************************************************************/
VOS_VOID IMSA_CMCCDeregProc(VOS_VOID)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU                  *pstControlMagnaer   = VOS_NULL_PTR;

    pstControlMagnaer                       = IMSA_GetControlManagerAddress();
    #endif

    if (VOS_FALSE == IMSA_GetConfigParaAddress()->stCMCCCustomReq.ucCMCCCustomDeregFlag)
    {
        IMSA_INFO_LOG("CMCC Custom Dereg Flag is false.");
        TLPS_PRINT2LAYER_INFO(IMSA_CMCCDeregProc_ENUM, 1);
        return;
    }

    if (MSCC_IMSA_IMS_VOPS_SUPPORT == IMSA_GetNetInfoAddress()->enImsaImsVoPsStatus)
    {
        IMSA_INFO_LOG("VoPS support.");
        TLPS_PRINT2LAYER_INFO(IMSA_CMCCDeregProc_ENUM, 2);
        return;
    }


    if(VOS_TRUE == IMSA_IsImsExist())
    {
        IMSA_INFO_LOG("IMS call/sms/ss running. will dereg later.");
        TLPS_PRINT2LAYER_INFO(IMSA_CMCCDeregProc_ENUM, 3);
        return;
    }




    IMSA_INFO_LOG1("IMSA_CMCCDeregProc: Service status: ", IMSA_SRV_GetNormalSrvStatus());
    TLPS_PRINT2LAYER_INFO1(IMSA_CMCCDeregProc_ENUM, 4, IMSA_SRV_GetNormalSrvStatus());
    switch(IMSA_SRV_GetNormalSrvStatus())
    {
        case IMSA_SRV_STATUS_CONN_REGING:
        case IMSA_SRV_STATUS_CONN_REG:

            IMSA_CMCCDeregProcConnRegOrReging();

            break;
        case IMSA_SRV_STATUS_CONNING_DEREG:
        case IMSA_SRV_STATUS_CONN_DEREG:

            IMSA_CMCCDeregProcConnOrConningDereg();
            break;

        case IMSA_SRV_STATUS_CONNING_REG:
            /* 需要通知IMS允许其发包，通知发起本地注册 */
            IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV);
            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

            /* 释放资源 */
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
                IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
            }
            #endif
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_NormInitDeregErrRecord(IMSA_ERR_LOG_INIT_DEREG_REASON_RAT_OR_VOICE_NOT_SUPPORT);
            #endif
            break;
        case IMSA_SRV_STATUS_IDLE_DEREG:

            /* 如果该状态下，有在申请注册资源，且原因值为获取普通服务，则释放资源 */
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            }
            #endif
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_NotInitRegErrRecord();
            #endif
            break;
        default:
            break;
    }
}
/*****************************************************************************
 Function Name   : IMSA_CommonDeregProc
 Description     : 漫游和中移动定制需求通用去注册流程
 Input           : VOS_VOID
 Output          : VOS_VOID
 Return          : VOS_VOID

 History         :
    1.zhaochen 00308719    2015-08-26  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CommonDeregProc(VOS_VOID)
{

    IMSA_CMCCDeregProc();
    IMSA_SRV_ProcWhenRoamNotSatisfied();

    return;
}

/*****************************************************************************
 Function Name  : IMSA_IsStopImsEmcService
 Description    : 根据紧急服务状态，判断是否停止紧急服务
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.xiongxianghui 00253310      2015-09-01  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_IsImsEmcServiceEstablishSucc(VOS_VOID)
{
    VOS_UINT32    ulResult = IMSA_FALSE;

    IMSA_INFO_LOG("IMSA_IsStopImsEmcService is enter!");

    if ((IMSA_SRV_STATUS_CONNING_DEREG == IMSA_SRV_GetEmcSrvStatus()) ||
        (IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetEmcSrvStatus()))
    {
        ulResult = IMSA_FALSE;
    }
    else if (IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetEmcSrvStatus())
    {
        ulResult = IMSA_TRUE;
    }
    else
    {
        IMSA_INFO_LOG("IMSA_IsStopImsEmcService:other status!");
    }


    return ulResult;
}

/*****************************************************************************
 Function Name  : IMSA_StopImsEmcService
 Description    : CONNING+DEREG和CONN+REGING停止紧急服务
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.xiongxianghui 00253310      2015-09-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_StopImsEmcService(VOS_VOID)
{
    IMSA_INFO_LOG("IMSA_StopImsEmcService is enter!");

    switch(IMSA_SRV_GetEmcSrvStatus())
    {
        case IMSA_SRV_STATUS_CONNING_DEREG:
            IMSA_INFO_LOG("IMSA_SRV_ProcEmcTcallTimerExp:CONNING_DEREG!");

            IMSA_SRV_SndConnRelReq(IMSA_CONN_TYPE_EMC,
                                   IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            /* 状态转到RELEASE+DEREG态，通知CALL紧急服务不具备 */
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC,
                                      IMSA_SRV_STATUS_RELEASING_DEREG);

            /* 通知CALL模块紧急呼叫服务进入无服务状态，促使CALL模块清除缓存的紧急呼 */
            IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                            IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);

            break;
        case IMSA_SRV_STATUS_CONN_REGING:
            IMSA_INFO_LOG("IMSA_SRV_ProcEmcTcallTimerExp:CONN_REGING!");

            /* 需要本地去注册 */
            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_CONN_DEREGING);
            break;
        default:
            IMSA_INFO_LOG("IMSA_StopImsEmcService:other status!");
            break;
    }

}
#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcVoiceDomainChangeInd
 Description    : MMA VOICE DOMAIN信息变更消息处理函数
 Input          : pstVoiceDomainChangeInd-----------VOICE DOMAIN CHANGE IND消息
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-02-26  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_SRV_IsNotNeedNwDereg
(
    VOS_VOID
)
{
    IMSA_CONTROL_MANAGER_STRU      *pstControlManager;

    IMSA_INFO_LOG("IMSA_SRV_ProcVoiceDomainChangeInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcVoiceDomainChangeInd_ENUM, LNAS_ENTRY);

    pstControlManager = IMSA_GetControlManagerAddress();

    if (IMSA_SRV_STATUS_IDLE_DEREG == IMSA_SRV_GetNormalSrvStatus())
    {
        return IMSA_TRUE;
    }

    if (IMSA_SRV_STATUS_CONNING_REG == IMSA_SRV_GetNormalSrvStatus())
    {
        /* 需要通知IMS 允许发包，然后本地去注册 */
        IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV);

        IMSA_StopTimer(&pstControlManager->stPeriodImsSrvTryTimer);

        IMSA_SRV_SndRegDeregReq(    IMSA_REG_TYPE_NORMAL,
                                    IMSA_DEREG_LOCAL);

        return IMSA_TRUE;
    }

    return IMSA_FALSE;
}
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcVoiceDomainChangeInd
 Description    : MMA VOICE DOMAIN信息变更消息处理函数
 Input          : pstVoiceDomainChangeInd-----------VOICE DOMAIN CHANGE IND消息
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-02-26  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcStopMsgWhenNoRf
(
    VOS_VOID
)
{
    IMSA_INFO_LOG("IMSA_SRV_ProcVoiceDomainChangeInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcVoiceDomainChangeInd_ENUM, LNAS_ENTRY);

    switch(IMSA_SRV_GetNormalSrvStatus())
    {
        /* 仅需要通知IMS本地去注册即可，承载是否需要删除,在收到IMS关机相应后，根据关机
        类型决定是否要通知APS删除 */
        case IMSA_SRV_STATUS_CONN_REGING:
        case IMSA_SRV_STATUS_CONN_DEREGING:
        case IMSA_SRV_STATUS_CONN_REG:

            IMSA_RegNotifyImsLocalDereg();
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : IMSA_SRV_ProcRegResourceApplyCnf
 功能描述  : DSDS申请注册资源成功后的处理
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月18日
    作    者   : W00209181
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 IMSA_SRV_ProcGetNormSevResourceApplyCnf
(
    IMSA_REG_ADDR_PARAM_ENUM_UINT32     enAddrType
)
{
    IMSA_SRV_STATUS_ENUM_UINT8          enNrmSrvStatus      = IMSA_SRV_STATUS_BUTT;
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    enNrmSrvStatus = IMSA_SRV_GetNormalSrvStatus();
    pstControlMagnaer = IMSA_GetControlManagerAddress();

    if (IMSA_NRM_SRV_CON_SAT_STATUE_SUCC != IMSA_SRV_IsNrmSrvConditonSatisfied())
    {
        return IMSA_FALSE;
    }

    /* 根据当前服务状态进行不同处理 */
    switch (enNrmSrvStatus)
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:

            /* 请求连接模块建立连接，将状态转到IMSA_SERVICE_STATUS_CONNING_DEREG */
            IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                        IMSA_CONN_TYPE_NORMAL);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONNING_DEREG);

            /* 启动注册时长保护定时器 */
            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);

            break;

        case IMSA_SRV_STATUS_CONN_DEREG:
            /* 如果当前状态为ACTIVE，则直接发起注册 */
            /* 请求注册模块发起注册，将状态转到IMSA_SERVICE_STATUS_CONN_REGING */
            IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                        enAddrType);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONN_REGING);

            /* 启动注册时长保护定时器 */
            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            break;

        case IMSA_SRV_STATUS_CONNING_REG:
            /* 请求连接模块建立连接 */
            IMSA_SRV_SndConnSetupReq(   IMSA_TRUE,
                                        IMSA_CONN_TYPE_NORMAL);

            /* 启动注册时长保护定时器 */
            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            break;

        default:
            /* 打印状态 */
            return IMSA_FALSE;
    }
    return IMSA_TRUE;
}
/*****************************************************************************
 函 数 名  : IMSA_SRV_ProcRegResourceApplyCnf
 功能描述  : DSDS申请注册资源成功后的处理
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月18日
    作    者   : W00209181
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 IMSA_SRV_ProcPeriodRegResourceApplyCnf
(
    IMSA_REG_ADDR_PARAM_ENUM_UINT32     enAddrType
)
{
    IMSA_SRV_STATUS_ENUM_UINT8          enNrmSrvStatus      = IMSA_SRV_STATUS_BUTT;
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    enNrmSrvStatus = IMSA_SRV_GetNormalSrvStatus();
    pstControlMagnaer = IMSA_GetControlManagerAddress();

    if (IMSA_NRM_SRV_CON_SAT_STATUE_SUCC != IMSA_SRV_IsNrmSrvConditonSatisfied())
    {
        return IMSA_FALSE;
    }

    /* 根据当前服务状态进行不同处理 */
    switch (enNrmSrvStatus)
    {
        case IMSA_SRV_STATUS_CONN_REGING:
            /* 如果当前状态为ACTIVE，则直接发起注册 */
            /* 请求注册模块发起注册，将状态转到IMSA_SERVICE_STATUS_CONN_REGING */
            IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                        enAddrType);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONN_REGING);

            /* 启动注册时长保护定时器 */
            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            break;

        default:
            /* 打印状态 */
            return IMSA_FALSE;
    }
    return IMSA_TRUE;
}

/*****************************************************************************
 函 数 名  : IMSA_SRV_ProcRegResourceApplyCnf
 功能描述  : DSDS申请注册资源成功后的处理
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月18日
    作    者   : W00209181
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  IMSA_SRV_ProcGetNorServiceResourceApplyExp
(
    VOS_VOID
)
{
    switch (IMSA_SRV_GetNormalSrvStatus())
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:
        case IMSA_SRV_STATUS_CONN_DEREG:

            IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE, IMSA_CONN_IsExitPersistentBearer());
            break;
        case IMSA_SRV_STATUS_CONNING_REG:

            IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV);

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);
            break;

        case IMSA_SRV_STATUS_CONN_REGING:

            //IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE, IMSA_CONN_IsExitPersistentBearer());
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_DEREG);
            break;

        default:
            break;
    }
}


VOS_UINT32 IMSA_SRV_ProcPeriodRegResourceApplyExp
(
    VOS_VOID
)
{
    switch (IMSA_SRV_GetNormalSrvStatus())
    {
        case IMSA_SRV_STATUS_CONN_REGING:
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONN_DEREG);

            break;

        case IMSA_SRV_STATUS_CONNING_REG:

            IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV);

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

            break;

        default:
            /* 打印状态 */
            return IMSA_FALSE;
    }
    return IMSA_TRUE;
}

/*****************************************************************************
 函 数 名  : IMSA_SRV_ProcRegResourceApplyCnf
 功能描述  : DSDS申请注册资源成功后的处理
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月18日
    作    者   : W00209181
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 IMSA_SRV_ProcDeRegResourceApplyCnf
(
    VOS_VOID
)
{
    IMSA_CONTROL_MANAGER_STRU                  *pstControlMagnaer   = VOS_NULL_PTR;

    pstControlMagnaer                       = IMSA_GetControlManagerAddress();

    switch(IMSA_SRV_GetNormalSrvStatus())
    {
        case IMSA_SRV_STATUS_CONN_DEREGING:
            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_NOT_LOCAL);
            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            //IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_DEREGING);
            break;

        case IMSA_SRV_STATUS_RELEASING_DEREG:
            IMSA_SRV_SndConnRelReq(IMSA_SRV_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            break;

        default:
            return IMSA_FALSE;
    }
    return IMSA_TRUE;
}
/*****************************************************************************
 函 数 名  : IMSA_SRV_ProcRegResourceApplyCnf
 功能描述  : DSDS申请注册资源成功后的处理
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月18日
    作    者   : W00209181
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 IMSA_SRV_ProcDeRegResourceApplyTimerExp
(
    VOS_VOID
)
{
    IMSA_CONTROL_MANAGER_STRU                  *pstControlMagnaer   = VOS_NULL_PTR;

    pstControlMagnaer                       = IMSA_GetControlManagerAddress();

    switch(IMSA_SRV_GetNormalSrvStatus())
    {
        case IMSA_SRV_STATUS_CONN_DEREGING:
            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);
            IMSA_SRV_SndConnRelReq(IMSA_SRV_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);
            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
            return IMSA_TRUE;

        case IMSA_SRV_STATUS_RELEASING_DEREG:


            IMSA_SRV_SndConnRelReq(IMSA_SRV_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);
            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
            break;

        default:
            break;
    }
    return IMSA_FALSE;
}


/*****************************************************************************
 函 数 名  : IMSA_SRV_ProcRegResourceApplyTimerExp
 功能描述  : DSDS申请注册资源定时器超时
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月18日
    作    者   : W00209181
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcGetSrvTimerExp
(
    const VOS_VOID                     *pMsg
)
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_ProcGetSrvTimerExp:enter!");

    pstControlMagnaer  = IMSA_GetControlManagerAddress();

    switch(IMSA_SRV_GetNormalSrvStatus())
    {
        case IMSA_SRV_STATUS_CONN_REGING:

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_DEREG);

            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);

            /* 启动周期尝试定时器 */
            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);

            break;

        case IMSA_SRV_STATUS_CONNING_DEREG:
            IMSA_SRV_SndConnRelReq(IMSA_SRV_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);

            /* 启动周期尝试定时器 */
            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);

            break;

        default:
            break;
    }
    if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
    {
        IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
    }
    return;

}

/*****************************************************************************
 函 数 名  : IMSA_SRV_ProcRegResourceApplyTimerExp
 功能描述  : DSDS申请注册资源定时器超时
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月18日
    作    者   : W00209181
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcDeregSrvTimerExp
(
    const VOS_VOID                     *pMsg
)
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_ProcDeregSrvTimerExp:enter!");

    pstControlMagnaer  = IMSA_GetControlManagerAddress();

    switch(IMSA_SRV_GetNormalSrvStatus())
    {
        case IMSA_SRV_STATUS_CONN_DEREGING:

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);
            IMSA_SRV_SndConnRelReq(IMSA_SRV_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);

            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            }
            break;

        case IMSA_SRV_STATUS_RELEASING_DEREG:

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);

            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            }
            break;

        default:
            break;
    }
    return;

}

#endif

/*****************************************************************************
 Function Name  : IMSA_StartTempForbTimer
 Description    : 启动TI_IMSA_TEMP_FORBIDDEN_TIMER定时器
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.leixiantiao 00258641      2015-12-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_StartTempForbTimer(VOS_VOID)
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    pstControlMagnaer  = IMSA_GetControlManagerAddress();

    /* 修改定时器时长 */
    pstControlMagnaer->stTempForbiddenTimer.ulTimerLen = LMM_Get3402TimerLen();

    /* 启动定时器 */
    IMSA_StartTimer(&pstControlMagnaer->stTempForbiddenTimer);
}

/*****************************************************************************
 Function Name  : IMSA_IsTempForbTimerRunning
 Description    : 判断TI_IMSA_TEMP_FORBIDDEN_TIMER定时器是否启动
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_FALSE--------定时器未启动
                  VOS_TRUE---------定时器正在运行

 History        :
      1.leixiantiao 00258641      2015-12-10  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_IsTempForbTimerRunning(VOS_VOID)
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt              = VOS_FALSE;

    pstControlMagnaer  = IMSA_GetControlManagerAddress();

    ulRslt = IMSA_IsTimerRunning(&pstControlMagnaer->stTempForbiddenTimer);

    return ulRslt;
}

/*****************************************************************************
 Function Name  : IMSA_ProcTimerMsgTempForbTimerExp
 Description    : TI_IMSA_TEMP_FORBIDDEN_TIMER定时器超时处理
 Input          : pRcvMsg----------定时器超时消息
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.leixiantiao 00258641      2015-12-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcTimerMsgTempForbTimerExp(const VOS_VOID *pRcvMsg )
{
    IMSA_SRV_STATUS_ENUM_UINT8          enNrmSrvStatus;

    enNrmSrvStatus = IMSA_SRV_GetNormalSrvStatus();

    /* 该定时器超时时, 若当前处于IMSA_SRV_STATUS_IDLE_DEREG态, 则发起CONN建立流程 */
    if (IMSA_SRV_STATUS_IDLE_DEREG == enNrmSrvStatus)
    {
        IMSA_ProcTimerMsgPeriodTryImsSrvExpIdleDereg();
    }

    return;
}

/*lint +e961*/

#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaServiceManagement.c */



