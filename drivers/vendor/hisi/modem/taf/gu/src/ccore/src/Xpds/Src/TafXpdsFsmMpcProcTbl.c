

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXpdsFsmMpcProcTbl.h"
#include "TafXpdsSndInternalMsg.h"
#include "TafXpdsFsmMpcProc.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XPDS_FSM_MPC_PROC_TBL_C

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* XPDS l2 MPC状态机状态全局变量 */
TAF_FSM_DESC_STRU                       g_stTafXpdsL2MpcProcFsmDesc;

/* XPDS l2 MPC INIT状态下的事件处理表 */
TAF_ACT_STRU                            g_astTafXpdsL2MpcProcInitActTbl[] =
{
    /* 收到XX命令的处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_MPC_PROC_START_REQ,
                      TAF_XPDS_RcvMpcOperationReqMsg_MpcProc_Init),

};

/* XPDS l2 MPC状态下的事件处理表 */
TAF_ACT_STRU g_astTafXpdsL2MpcProcWaitMpcStartPosRespActTbl[] =
{
    /* 收到定时器等待START POS 定时器的处理命令的处理 */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_MPC_START_POS_RSP,
                      TAF_XPDS_RcvTiStartPosRespExperied_MpcProc_WaitStartPosResp),


    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_RCV_MPC_START_POS_RESP,
                      TAF_XPDS_RcvMpcStartPosResp_MpcProc_WaitStartPosResp),


    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvXpdsAbortInd_MpcProc),

};

/* XPDS l2 MPC状态下的事件处理表 */
TAF_ACT_STRU g_astTafXpdsL2MpcProcWaitMpcPosReportRespActTbl[] =
{
    /* 收到XX命令的处理 */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_MPC_POS_REPORT_RSP,
                      TAF_XPDS_RcvTiPosReportExperied_MpcProc_WaitStartPosResp),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_RCV_MPC_POS_REPORT_RESP,
                      TAF_XPDS_RcvMpcPosReportResp_MpcProc_WaitPosReportResp),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvXpdsAbortInd_MpcProc),

};



/* XPDS L2 MPC状态机状态处理表 */
TAF_STA_STRU g_astTafXpdsL2MpcProcStaTbl[] =
{
    /*****************定义MPC INIT状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_XPDS_L2_MPC_PROC_STA_INIT,
                      g_astTafXpdsL2MpcProcInitActTbl ),

    /*****************定义MPC WAIT START POS RESP状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_XPDS_L2_MPC_PROC_STA_WAIT_START_POS_RESP,
                      g_astTafXpdsL2MpcProcWaitMpcStartPosRespActTbl ),

    /*****************定义MPC WAIT POS REPORT RESP状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_XPDS_L2_MPC_PROC_STA_WAIT_POS_REPORT_RESP,
                      g_astTafXpdsL2MpcProcWaitMpcPosReportRespActTbl ),

};

/*****************************************************************************
  3 函数定义
*****************************************************************************/

VOS_UINT32 TAF_XPDS_GetL2MpcProcStaTblSize( VOS_VOID )
{
    return (sizeof(g_astTafXpdsL2MpcProcStaTbl)/sizeof(TAF_STA_STRU));
}


TAF_STA_STRU* TAF_XPDS_GetL2MpcProcStaTblAddr( VOS_VOID )
{
    return (g_astTafXpdsL2MpcProcStaTbl);
}


TAF_FSM_DESC_STRU* TAF_XPDS_GetL2MpcProcFsmDescAddr( VOS_VOID )
{
    return (&g_stTafXpdsL2MpcProcFsmDesc);
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



