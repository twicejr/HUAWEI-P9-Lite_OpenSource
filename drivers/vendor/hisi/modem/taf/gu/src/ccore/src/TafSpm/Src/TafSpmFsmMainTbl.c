

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsTypeDef.h"
#include "TafSpmFsmMainTbl.h"
#include "Taf_Tafm_Remote.h"
#include "NasStkInterface.h"
#include "TafSpmSndInternalMsg.h"
#include "TafSpmFsmMain.h"
#if (FEATURE_IMS == FEATURE_ON)
#include "SpmImsaInterface.h"
#include "ImsaInterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_FSM_MAIN_TBL_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* 预处理状态机 */
TAF_FSM_DESC_STRU                       g_stTafSpmMainFsmDesc;


/**************************************************************************/
/*新增状态动作处理表 */
/**************************************************************************/

/* IDLE状态机处理的消息动作表 */
TAF_ACT_STRU        g_astTafSpmMainProcessActTbl[]   =
{
    /*  AT SS message */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_REGISTERSS_MSG,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_ERASESS_MSG,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_ACTIVATESS_MSG,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_DEACTIVATESS_MSG,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_INTERROGATESS_MSG,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_REGPWD_MSG,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_ERASECCENTRY_MSG,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_PROCESS_USS_MSG,
                      TAF_SPM_RcvAppReqMsg_Main ),


    /* STK SS message */
    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_USSD_REQ,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_REGISTERSS_REQ,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_ERASESS_REQ,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_ACTIVATESS_REQ,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_DEACTIVATESS_REQ,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_INTERROGATESS_REQ,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_REGPWD_REQ,
                      TAF_SPM_RcvAppReqMsg_Main ),

    /* AT CALL message */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_CALL_APP_ORIG_REQ,
                      TAF_SPM_RcvAppReqMsg_Main ),



    /* AT SMS message */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_MSG_MSGTYPE_SEND_RPDATA_FROMMEM,
                      TAF_SPM_RcvAppReqMsg_Main ),

    /* STK CALL message */
    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_CALL_CALLORIG_REQ,
                      TAF_SPM_RcvAppReqMsg_Main ),


    /* STK SMS message */
    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_MSG_SEND_REQ,
                      TAF_SPM_RcvAppReqMsg_Main ),

    /* TAF Internal message */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      TAF_SPM_INTERNAL_SERVICE_CTRL_RESULT_IND,
                      TAF_SPM_RcvSpmServiceCtrlResultInd_Main ),






#if (FEATURE_ON == FEATURE_IMS)
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_CALL_APP_ECONF_DIAL_REQ,
                      TAF_SPM_RcvAppReqMsg_Main ),
#endif


};

/* MAIN状态机处理的消息 状态表 */
TAF_STA_STRU        g_astTafSpmMainProcessFsmTbl[]   =
{
    TAF_STA_TBL_ITEM( TAF_SPM_MAIN_STA_IDLE,
                      g_astTafSpmMainProcessActTbl )
};


VOS_UINT32 TAF_SPM_GetMainProcessStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astTafSpmMainProcessFsmTbl)/sizeof(TAF_STA_STRU));
}


TAF_FSM_DESC_STRU * TAF_SPM_GetMainFsmDescAddr(VOS_VOID)
{
    return (&g_stTafSpmMainFsmDesc);
}









#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

