

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafFsm.h"
#include "TafXpdsCtx.h"
#include "TafXpdsFsmCpPdeProc.h"
#include "TafXpdsFsmPdeProcComm.h"
#include "TafXpdsSndInternalMsg.h"
#include "TafXpdsFsmCpPdeProcTbl.h"
#include "cas_1x_control_main_nas_pif.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XPDS_CP_FSM_PDE_PROC_TBL_C

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* XPDS l2 PDE状态机状态全局变量 */
TAF_FSM_DESC_STRU                       g_stTafXpdsCpL2PdeProcFsmDesc;



/* XPDS L2 PDE状态机 STA_INIT 状态下的事件处理表 */
TAF_ACT_STRU    g_astTafXpdsCpL2PdeProcInitActTbl[] =
{

    /* 收到ID_TAF_XPDS_XPDS_PDE_PROC_START_REQ命令的处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_CP_PDE_PROC_START_REQ,
                      TAF_XPDS_RcvXpdsCpPdeProcStart_CpL2Pde_Init),

};

/* XPDS l2 PDE wait for CAS CNF */
TAF_ACT_STRU                            g_astTafXpdsCpL2PdeProcStaMsbWaitCasCnfActTbl[] =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_CNF,
                      TAF_XPDS_RcvXpdsCpMsbModeRecieveCasCnf),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_CAS_CNF,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde)

};

/* XPDS l2 PDE wait for PDE response indicating both EPHI and ALM completely recieved */
TAF_ACT_STRU                            g_astTafXpdsCpL2PdeProcStaMsbWaitPdeRspActTbl[] =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND,
                      TAF_XPDS_RcvXpdsCpMsbModeRecievePdeResp),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_ALM_EPHI_RESP,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde)

};

TAF_ACT_STRU                            g_astTafXpdsCpL2PdeProcStaMsaWaitPrmReqActTbl[] =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND,
                      TAF_XPDS_RcvXpdsCpMsaModeRecievePrmReq_NI),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PRM_REQ_AFTER_PPM,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde)

};

/* XPDS l2 PDE wait for GPS location response */
TAF_ACT_STRU                            g_astTafXpdsCpL2PdeProcStaMsbWaitGpsLocRspActTbl[] =
{
    /* 收到XX命令的处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_POS_INFO_RSP,
                      TAF_XPDS_RcvXpdsCpMsbModeRecieveGpsLocResp),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_GPS_LOC_RESP,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde)

};
/* XPDS l2 PDE wait at stop after GPS location response */
TAF_ACT_STRU                            g_astTafXpdsCpL2PdeProcStaMsbWaitGpsStopActTbl[] =
{

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_GPS_LOC_RESP,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout)

};



/* CP MSB XPDS l2 PDE wait for CAS CNF */
TAF_ACT_STRU    g_astTafXpdsCpL2PdeProcStaMsaWaitCasCnfAfterPpmActTbl[] =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_CNF,
                      TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterPPM),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_PPM,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde)

};

TAF_ACT_STRU    g_astTafXpdsCpL2PdeProcStaMsaWaitCasCnfAfterPpmNIActTbl[] =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_CNF,
                      TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterPPM_NI),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_PPM,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde),

};

TAF_ACT_STRU    g_astTafXpdsCpL2PdeProcStaMsaWaitCasCnfAfterAquiAssisNIActTbl[] =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_CNF,
                      TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterAquiAssis_NI),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_AQUI_ASSI,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PRM_COMPLETE_NI_QUALITY,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),


};

TAF_ACT_STRU    g_astTafXpdsCpL2PdeProcStaMsaWaitCasCnfAfterMsInfoActTbl[] =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_CNF,
                      TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterMsInfo),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_PPM,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde),

};

TAF_ACT_STRU    g_astTafXpdsCpL2PdeProcStaMsaWaitCasCnfAfterLocRespActTbl[] =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_CNF,
                      TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterReqLocRsp),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_REQ_LOC_RSP,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

    TAF_ACT_TBL_ITEM(UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde),

};

TAF_ACT_STRU    g_astTafXpdsCpL2PdeProcStaMsaWaitPpmCompleteNIActTbl[] =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_PPM_COMPLETE_NI,
                      TAF_XPDS_RcvXpdsCpMsaModePPMComplete_NI),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde),

};

TAF_ACT_STRU    g_astTafXpdsCpL2PdeProcStaMsaWaitProvPdeAssistInfoActTble[] =
{
    /* 收到ID_TAF_XPDS_XPDS_RECEIVE_PDE_DATA_IND命令的处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND,
                      TAF_XPDS_RcvXpdsForwardPdeDataInd_CpL2Pde_MsaWaitPdeAssistInfo),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_PDE_ASSIST_DATA_CNF,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PRM_COMPLETE_NI_QUALITY,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

};

TAF_ACT_STRU    g_astTafXpdsCpL2PdeProcStaMsaWaitGpsPseudoInfoActTbl[] =
{
    /* 收到ID_AT_XPDS_PRM_INFO_RSP命令的处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_PRM_INFO_RSP,
                      TAF_XPDS_RcvAtGpsPrmInfoRsp_CpL2Pde_MsaWaitGpsPseudoInfo),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PRM_COMPLETE_NI_QUALITY,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde),
};

TAF_ACT_STRU    g_astTafXpdsCpL2PdeProcStaMsaWaitPdeLocRspActTbl[] =
{
    /* 收到XX命令的处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND,
                      TAF_XPDS_RcvXpdsForwardPdeDataInd_CpL2Pde_MsaWaitPdeLocRespInfo),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_PDE_LOCATION_INFO_CNF,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde),

};


/* XPDS CP L2 PDE状态机状态处理表 */
TAF_STA_STRU                            g_astTafXpdsCpL2PdeProcStaTbl[] =
{
    /*****************定义MPC INIT状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_XPDS_CP_L2_PDE_PROC_STA_INIT,
                      g_astTafXpdsCpL2PdeProcInitActTbl ),


    TAF_STA_TBL_ITEM( TAF_XPDS_CP_L2_PDE_PROC_STA_MSB_WAIT_CAS_CNF,
                      g_astTafXpdsCpL2PdeProcStaMsbWaitCasCnfActTbl ),

    TAF_STA_TBL_ITEM( TAF_XPDS_CP_L2_PDE_PROC_STA_MSB_WAIT_PDE_EPHI_ALM_RESP,
                      g_astTafXpdsCpL2PdeProcStaMsbWaitPdeRspActTbl ),

    TAF_STA_TBL_ITEM( TAF_XPDS_CP_L2_PDE_PROC_STA_MSB_WAIT_GPS_LOC_RESP,
                      g_astTafXpdsCpL2PdeProcStaMsbWaitGpsLocRspActTbl ),

    TAF_STA_TBL_ITEM( TAF_XPDS_CP_L2_PDE_PROC_STA_MSB_WAIT_AT_GPS_STOP,
                      g_astTafXpdsCpL2PdeProcStaMsbWaitGpsStopActTbl ),




    TAF_STA_TBL_ITEM(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_CAS_CNF_AFTER_PPM,
                     g_astTafXpdsCpL2PdeProcStaMsaWaitCasCnfAfterPpmActTbl),

    TAF_STA_TBL_ITEM(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_PDE_ASSIST_INFO,
                     g_astTafXpdsCpL2PdeProcStaMsaWaitProvPdeAssistInfoActTble),

    TAF_STA_TBL_ITEM(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_GPS_PSEUDO_INFO,
                     g_astTafXpdsCpL2PdeProcStaMsaWaitGpsPseudoInfoActTbl ),

    TAF_STA_TBL_ITEM(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_CAS_CNF_AFTER_REQ_LOC_RSP,
                     g_astTafXpdsCpL2PdeProcStaMsaWaitCasCnfAfterLocRespActTbl ),

    TAF_STA_TBL_ITEM( TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_PDE_LOC_RSP,
                     g_astTafXpdsCpL2PdeProcStaMsaWaitPdeLocRspActTbl ),

    TAF_STA_TBL_ITEM(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_CAS_CNF_AFTER_MS_INFO,
                     g_astTafXpdsCpL2PdeProcStaMsaWaitCasCnfAfterMsInfoActTbl),

    TAF_STA_TBL_ITEM(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_CAS_CNF_AFTER_PPM_NI,
                     g_astTafXpdsCpL2PdeProcStaMsaWaitCasCnfAfterPpmNIActTbl),

    TAF_STA_TBL_ITEM(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_CAS_CNF_AFTER_AQUI_ASSIS_NI,
                     g_astTafXpdsCpL2PdeProcStaMsaWaitCasCnfAfterAquiAssisNIActTbl),

    TAF_STA_TBL_ITEM(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_PRM_REQ_NI,
                     g_astTafXpdsCpL2PdeProcStaMsaWaitPrmReqActTbl),

    TAF_STA_TBL_ITEM(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_PPM_COMPLETE_NI,
                     g_astTafXpdsCpL2PdeProcStaMsaWaitPpmCompleteNIActTbl),




};

/*****************************************************************************
  3 函数定义
*****************************************************************************/

VOS_UINT32 TAF_XPDS_GetCpL2PdeProcStaTblSize( VOS_VOID )
{
    return (sizeof(g_astTafXpdsCpL2PdeProcStaTbl)/sizeof(TAF_STA_STRU));
}


TAF_STA_STRU* TAF_XPDS_GetCpL2PdeProcStaTblAddr( VOS_VOID )
{
    return (g_astTafXpdsCpL2PdeProcStaTbl);
}


TAF_FSM_DESC_STRU* TAF_XPDS_GetCpL2PdeProcFsmDescAddr( VOS_VOID )
{
    return (&g_stTafXpdsCpL2PdeProcFsmDesc);
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




