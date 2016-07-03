

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafApsApi.h"
#include "Taf_Aps.h"
#include "TafFsm.h"
#include "TafApsTimerMgmt.h"
#include "TafApsFsmCdataEsting.h"
#include "TafApsFsmCdataEstingTbl.h"
#include "TafApsSndInternalMsg.h"
#include "TafMmaInterface.h"
#include "TafApsFsmCdataHandOff.h"
#include "TafApsFsmCdataHandOffTbl.h"
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "taf_aps_ppp_pif.h"
#include "ApsCdsInterface.h"
#include "xcc_aps_pif.h"
#include "hsm_aps_pif.h"

#endif


#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif



/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_CDATA_HANDOFF_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/******************************************************************************
   2 外部函数变量声明
******************************************************************************/

/******************************************************************************
   3 私有定义
******************************************************************************/


/******************************************************************************
   4 全局变量定义
*****************************************************************************/
/* TAF APS状态机数组:CDATA HANDOFF 状态机名称*/
TAF_FSM_DESC_STRU                       g_stTafApsCdataHandOffFsmDesc;


/******************************************************************************
   5 函数实现
******************************************************************************/
/* TAF_APS_CDATA_HANDOFF_SUBSTA_INIT动作表 */
TAF_ACT_STRU   g_astTafApsCdataHandOffSubStaInitTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_1X_TO_HRPD_HANDOFF_REQ,
                     TAF_APS_RcvPsInter1XToHrpdHandOff_CdataHandOff_Init),

};

/* TAF_APS_CDATA_HANDOFF_SUBSTA_WAIT_HSM_HANDOFF_CNF动作表 */
TAF_ACT_STRU   g_astTafApsCdataHandOffSubStaWaitHsmHandOffCnfActTbl[]   =
{

    TAF_ACT_TBL_ITEM(UEPS_PID_HSM,
                     ID_HSM_APS_1X_TO_HRPD_HANDOFF_CNF,
                     TAF_APS_RcvHsmHandOffCnf_CdataHandOff_WaitHsmHandOffCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_1X_TO_HRPD_HANDOFF_TIMER,
                     TAF_APS_RcvTi1XToHrpdHandOffExpired_CdataHandOff_WaitHsmHandOffCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_CdataHandOff_WaitHsmHandOffCnf),

    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_INCOMING_CALL_IND,
                     TAF_APS_RcvXccIncomingCallInd_CdataHandOff_WaitHsmHandOffCnf),

};


TAF_STA_STRU g_astTafApsCdataHandOffStaTbl[] =
{
    /*****************定义TAF_APS_MS_ACTIVATING_SUBSTA_INIT状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_CDATA_HANDOFF_SUBSTA_INIT,
                      g_astTafApsCdataHandOffSubStaInitTbl ),

    /*****************定义TAF_APS_CDATA_HANDOFF_SUBSTA_WAIT_HSM_HANDOFF_CNF状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_CDATA_HANDOFF_SUBSTA_WAIT_HSM_HANDOFF_CNF,
                      g_astTafApsCdataHandOffSubStaWaitHsmHandOffCnfActTbl ),
};


VOS_UINT32 TAF_APS_GetCdataHandOffStaTblSize( VOS_VOID )
{
    return (sizeof(g_astTafApsCdataHandOffStaTbl)/sizeof(TAF_STA_STRU));
}


TAF_FSM_DESC_STRU * TAF_APS_GetCdataHandOffFsmDescAddr( VOS_VOID )
{
    return (&g_stTafApsCdataHandOffFsmDesc);
}



#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



