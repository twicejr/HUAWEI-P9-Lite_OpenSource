/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaProcTimerMsg.c
  Description     : 该C文件实现Timer超时消息处理
  History           :
     1.sunbing 49683      2013-06-19  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "ImsaProcTimerMsg.h"
#include "ImsaPublic.h"
#include "PsCommonDef.h"
#include "ImsaRegManagement.h"
#include "ImsaCallManagement.h"
#include "ImsaConnManagement.h"
#include "ImsaServiceManagement.h"
#include "ImsaProcMsccMsg.h"
#include "ImsaProcApsMsg.h"
#include "ImsaMain.h"
#include "ImsaProcSmsMsg.h"
#include "ImsaProcUssdMsg.h"
#include "ImsaDsDsPublic.h"
/*lint -e767*/
#define    THIS_FILE_ID       PS_FILE_ID_IMSAPROCTIMERMSG_C
#define    THIS_NAS_FILE_ID   NAS_FILE_ID_IMSAPROCTIMERMSG_C
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
const IMSA_TIMER_EVT_FUNC_TBL_STRU    g_astImsaTimerEvtFuncTbl[] =
{
    /* PS CALL */
    {TI_IMSA_START_OR_STOP,
        IMSA_ProcTimerMsgWaitD2ImsStartOrStopCnfExp},
    {TI_IMSA_PERIOD_TRY_IMS_SRV,
        IMSA_ProcTimerMsgPeriodTryImsSrvExp},
    {TI_IMSA_TEMP_FORBIDDEN_TIMER,
        IMSA_ProcTimerMsgTempForbTimerExp},
    /* delete PeriodImsEmcSrvTryTimer */
    {TI_IMSA_SIP_SIGAL_PDP_ORIG,
        IMSA_CONN_ProcTimerMsgSipSignalPdpOrigExp},
    {TI_IMSA_SIP_SIGAL_PDP_END,
        IMSA_CONN_ProcTimerMsgSipSignalPdpEndExp},
    {TI_IMSA_WAIT_IPV6_INFO,
        IMSA_CONN_ProcTimerMsgWaitIpv6InfoExp},
    {TI_IMSA_REG_PROTECT,
        IMSA_RegProcTimeoutProtect},
    {TI_IMSA_REG_RETRY,
        IMSA_RegProcTimeoutRetry},
    {TI_IMSA_REG_PERIOD_TRY,
        IMSA_RegProcTimeoutRetry},
    {TI_IMSA_CALL_PROTECT,
        IMSA_CallProcTimeoutProtect},
    {TI_IMSA_CALL_RES_READY,
        IMSA_CallProcTimeoutResReady},
    {TI_IMSA_CALL_DTMF_DURATION,
        IMSA_CallProcTimeoutDtmfDuration},
    {TI_IMSA_CALL_DTMF_PROTECT,
        IMSA_CallProcTimeoutDtmfProtect},
    {TI_IMSA_CALL_REDIAL_MAX_TIME,
        IMSA_CallProcTimeoutRedialMaxTime},
    {TI_IMSA_CALL_REDIAL_INTERVEL,
        IMSA_CallProcTimeoutRedialIntervel},
    {TI_IMSA_CALL_NORMAL_TCALL,
        IMSA_CallProcTimeoutTCall},
    {TI_IMSA_CALL_EMC_TCALL,
        IMSA_CallProcTimeoutEmcTCall},
    {TI_IMSA_SMS_TR1M,
        IMSA_SMS_ProcTimerMsgTr1m},
    {TI_IMSA_SMS_TR2M,
        IMSA_SMS_ProcTimerMsgTr2m},
    {TI_IMSA_SMS_TRAM,
        IMSA_SMS_ProcTimerMsgTram},
    {TI_IMSA_BACK_OFF_TX,
        VOS_NULL_PTR},
    {TI_IMSA_BACK_OFF_TY,
        VOS_NULL_PTR},
    {TI_IMSA_USSD_WAIT_NET_RSP,
        IMSA_USSD_ProcTimerMsgWaitNetRsp},
    {TI_IMSA_USSD_WAIT_APP_RSP,
        IMSA_USSD_ProcTimerMsgWaitAppRsp},

    #if (FEATURE_ON == FEATURE_DSDS)
    {TI_IMSA_GET_SERVICE_WAIT_RF_RESOURCE_TIMER,
        IMSA_DsdsProcRegResourceTimerExp},
    {TI_IMSA_MO_CALL_WAIT_RF_RESOURCE_TIMER,
        IMSA_DsdsProcMoCallResourceTimerExp},
    {TI_IMSA_MT_CALL_WAIT_RF_RESOURCE_TIMER,
        IMSA_DsdsProcMtCallResourceTimerExp},
    {TI_IMSA_EMC_CALL_WAIT_RF_RESOURCE_TIMER,
        IMSA_DsdsProcEmcCallResourceTimerExp},
    {TI_IMSA_MO_SMS_WAIT_RF_RESOURCE_TIMER,
        IMSA_DsdsProcMoSmsResourceTimerExp},
    {TI_IMSA_MT_SMS_WAIT_RF_RESOURCE_TIMER,
        IMSA_DsdsProcMtSmsResourceTimerExp},
    {TI_IMSA_GET_SERVICE_PROTECT_TIMER,
        IMSA_SRV_ProcGetSrvTimerExp},
    {TI_IMSA_DEREG_SERVICE_PROTECT_TIMER,
        IMSA_SRV_ProcDeregSrvTimerExp},
    {TI_IMSA_RF_OCCUPIED_DELAY_PROC_TIMER,
        IMSA_DsdsProcOccupyDelayTimerExp},
    {TI_IMSA_POWER_OFF_WAIT_RF_RESOURCE_TIMER,
        IMSA_ProcTimerMsgWaitPowerOffRfExp},
    #endif
};

const VOS_UINT32 g_ulImsaTimerEvtFuncTblSize  = sizeof(g_astImsaTimerEvtFuncTbl) / sizeof(g_astImsaTimerEvtFuncTbl[0]);


/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name  : IMSA_ProcTimerMsgWaitStartOrStopResultExp()
 Description    : 等待IMS开机或者关机结果超时
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-24  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcTimerMsgWaitD2ImsStartOrStopCnfExp(const VOS_VOID *pRcvMsg)
{
    IMSA_CONTROL_MANAGER_STRU *pstControlManager;

    (void)pRcvMsg;
    IMSA_NORM_LOG("IMSA_ProcTimerMsgWaitD2ImsStartOrStopCnfExp: Enter!");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgWaitD2ImsStartOrStopCnfExp_ENUM, LNAS_ENTRY);

    pstControlManager = IMSA_GetControlManagerAddress();

    /*关机流程*/
    if(pstControlManager->enImsaStatus == IMSA_STATUS_STOPING)
    {
        /*清除资源*/
        IMSA_ClearResource();

        /*进入等待开机状态*/
        pstControlManager->enImsaStatus = IMSA_STATUS_NULL;

        IMSA_SndMsccMsgStopCnf();
    }
    else if(pstControlManager->enImsaStatus == IMSA_STATUS_STARTING)
    {
        /*进入开机状态*/
        pstControlManager->enImsaStatus = IMSA_STATUS_STARTED;

        IMSA_SndMsccMsgStartCnf();

        /* 给IMS配置UE能力 */
        IMSA_ConfigUeCapabilityInfo2Ims();

        if ((IMSA_OP_TRUE == pstControlManager->stImsaCommonInfo.stImsaUeId.bitOpImpi)
            && (IMSA_OP_TRUE == pstControlManager->stImsaCommonInfo.stImsaUeId.bitOpTImpu)
            && (IMSA_OP_TRUE == pstControlManager->stImsaCommonInfo.bitOpHomeNetDomainName))
        {
            /* config account info to ims */
            IMSA_ConfigAccoutInfo2Ims(IMSA_REG_TYPE_NORMAL);

            /* config account info to ims */
            IMSA_ConfigAccoutInfo2Ims(IMSA_REG_TYPE_EMC);
        }

        /* set imei */
        IMSA_ConfigImei2Ims();

        /* set retry time */
        IMSA_ConfigTimerLength2Ims();

        /* 给IMS配置SIP信息 */
        IMSA_ConfigSipInfo2Ims();

        IMSA_ConfigVoipInfo2Ims();

        IMSA_ConfigCodeInfo2Ims();

        IMSA_ConfigSsConfInfo2Ims();

        IMSA_ConfigSecurityInfo2Ims();

        IMSA_ConfigMediaParmInfo2Ims();

        IMSA_ConfigNvUeCapabilityInfo2Ims();
    }
    else
    {
        IMSA_WARN_LOG("IMSA_ProcTimerMsgWaitD2ImsStartOrStopCnfExp: err stat!");
        TLPS_PRINT2LAYER_WARNING(IMSA_ProcTimerMsgWaitD2ImsStartOrStopCnfExp_ENUM, IMSA_STATE_ERROR);
    }

}


/*****************************************************************************
 Function Name  : IMSA_TimerMsgDistr()
 Description    : TIMER消息分发函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-20  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_TimerMsgDistr(const REL_TIMER_MSG *pRcvMsg )
{
    IMSA_TIMER_ID_ENUM_UINT16           enTimerName;
    VOS_UINT32                          i           = IMSA_NULL;
    IMSA_TIMER_EVT_FUNC                 pTimerEvtFunc  = VOS_NULL_PTR;

    enTimerName = (VOS_UINT16)PS_GET_REL_TIMER_NAME(pRcvMsg);

    /* 在事件处理表中查找处理函数 */
    for ( i = 0; i < g_ulImsaTimerEvtFuncTblSize; i++ )
    {
        if ( enTimerName == g_astImsaTimerEvtFuncTbl[i].ulEvtId )
        {
            /* 事件ID匹配 */
            pTimerEvtFunc = g_astImsaTimerEvtFuncTbl[i].pTimerEvtFunc;
            break;
        }
    }

    /* 如果处理函数存在则调用 */
    if ( VOS_NULL_PTR != pTimerEvtFunc )
    {
        (*pTimerEvtFunc)(pRcvMsg);
    }
    else
    {
        /*lint -e961*/
        IMSA_ERR_LOG1("IMSA_TimerMsgDistr: Unexpected event received! <enTimerName>",
            enTimerName);
        TLPS_PRINT2LAYER_INFO1(IMSA_TimerMsgDistr_ENUM, LNAS_FAIL, enTimerName);
        /*lint +e961*/

    }

    return;

}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaProcTimerMsg.c */



