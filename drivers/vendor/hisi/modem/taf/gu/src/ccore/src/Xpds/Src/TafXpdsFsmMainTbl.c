

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXpdsFsmMainTbl.h"
#include "TafXpdsFsmMain.h"
#include "TafXpdsSndInternalMsg.h"
#include "xcc_xpds_pif.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XPDS_FSM_MAIN_TBL_C

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* XPDS状态机状态全局变量 */
TAF_FSM_DESC_STRU                       g_stTafXpdsMainFsmDesc;

/* XPDS L1 INIT状态下的事件处理表 */
TAF_ACT_STRU                            g_astTafXpdsL1InitActTbl[] =
{
    /* 收到MPC地址配置命令的处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_CFG_MPC_ADDR_REQ,
                      TAF_XPDS_RcvAtGpsCfgMpcAddrReq_Init ),

    /* 收到PDE地址配置命令的处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_CFG_PDE_ADDR_REQ,
                      TAF_XPDS_RcvAtGpsCfgPdeAddrReq_Init ),

    /* 收到NI回复命令的处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_REPLY_NI_REQ,
                      TAF_XPDS_RcvAtGpsReplyNiReq_Init ),

    /* 收到模式配置请求命令的处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_CFG_POSITION_MODE_REQ,
                      TAF_XPDS_RcvAtGpsCfgPositionModeReq_Init ),

    /* 收到开始定位请求命令的处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_START_REQ,
                      TAF_XPDS_RcvAtGpsStartReq_Init ),

    /* 收到查询时间的请求命令的处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_QRY_TIME_INFO_REQ,
                      TAF_XPDS_RcvAtGpsQryTimeInfoReq_Init ),

    /* 收到命令的处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND,
                      TAF_XPDS_RcvCasPdeDataInd_Init ),

    /* 收到命令的处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_XPDS_INCOMING_CALL_IND,
                      TAF_XPDS_RcvXccIncomingInd_Init ),
};

/* XPDS L1 positioning状态下的事件处理表 */
TAF_ACT_STRU                            g_astTafXpdsL1PositioningActTbl[] =
{
    /* 收到链路的结果处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_UP_LINK_CTRL_CNF,
                      TAF_XPDS_RcvXpdsBindServerCnf_Pos ),

    /* 收到MPC的结果处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_MPC_PROC_RSLT_IND,
                      TAF_XPDS_RcvXpdsMpcProcRsltInd_Pos ),

    /* 收到PDE的结果处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_PDE_PROC_RSLT_IND,
                      TAF_XPDS_RcvXpdsPdeProcRsltInd_Pos ),

    /* 收到GPS的定位结果处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_POS_INFO_RSP,
                      TAF_XPDS_RcvAtGpsPosInfoRsp_Pos ),

    /* 接收GPS发来的STOP处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvXpdsAbnormalAbortAgpsSessionInd_Pos ),

    /* 接收跟踪定位定时器超时处理 */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_NI_POS_REPORT_INTERNAL,
                      TAF_XPDS_RcvTiPosReportExpired_Pos ),

    /* 收到命令的处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND,
                      TAF_XPDS_RcvCasPdeDataInd_Pos ),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_CP_LINK_RESULT_IND,
                      TAF_XPDS_RcvCpXpdsLinkProcRsltInd_Pos ),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_CP_PDE_PROC_RSLT_IND,
                      TAF_XPDS_RcvCpXpdsPdeProcRsltInd_Pos ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_CAS_DATA_IND_L1_POS,
                      TAF_XPDS_RcvTiDataIndWaitExpired_Pos ),
};


/* XPDS L1状态机状态处理表 */
TAF_STA_STRU                            g_astTafXpdsL1MainStaTbl[] =
{
    /*****************定义L1 INIT状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_XPDS_L1_STA_INIT,
                      g_astTafXpdsL1InitActTbl ),

    /*****************定义L1 POSING状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_XPDS_L1_STA_POSITIONING,
                      g_astTafXpdsL1PositioningActTbl ),
};

/*****************************************************************************
  3 函数定义
*****************************************************************************/

VOS_UINT32 TAF_XPDS_GetMainStaTblSize( VOS_VOID )
{
    return (sizeof(g_astTafXpdsL1MainStaTbl)/sizeof(TAF_STA_STRU));
}


TAF_STA_STRU* TAF_XPDS_GetMainStaTblAddr( VOS_VOID )
{
    return (g_astTafXpdsL1MainStaTbl);
}


TAF_FSM_DESC_STRU* TAF_XPDS_GetMainFsmDescAddr( VOS_VOID )
{
    return (&g_stTafXpdsMainFsmDesc);
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


