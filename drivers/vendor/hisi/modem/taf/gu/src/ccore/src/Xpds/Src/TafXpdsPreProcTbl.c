/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsPreProcTbl.c
  版 本 号   : 初稿
  作    者   : C00299064
  生成日期   : 2015年08月21日
  功能描述   : 1X PDS预状态机的状态表和ACT表
  函数列表   :
  修改历史   :
  1.日    期   : 2015年08月21日
    作    者   : C00299064
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXpdsPreProcTbl.h"
#include "TafXpdsPreProc.h"
#include "TafXpdsXsmsInterface.h"
#include "cas_1x_control_main_nas_pif.h"
#include "TafXpdsFsmMainTbl.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XPDS_PRE_PROC_TBL_C


#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* XPDS 预处理状态机状态全局变量 */
TAF_FSM_DESC_STRU                       g_stTafXpdsPreProcFsmDesc;

/* XPDS pre proc状态下的事件处理表 */
TAF_ACT_STRU                            g_astTafXpdsPreProcActTbl[] =
{
    /* 收到MPC地址配置命令的处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_CFG_MPC_ADDR_REQ,
                      TAF_XPDS_RcvAtGpsCfgMpcAddrReq_PreProc),

    /* 收到PDE地址配置命令的处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_CFG_PDE_ADDR_REQ,
                      TAF_XPDS_RcvAtGpsCfgPdeAddrReq_PreProc),

    /* 收到模式配置请求命令的处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_CFG_POSITION_MODE_REQ,
                      TAF_XPDS_RcvAtGpsCfgPositionModeReq_PreProc),

    /* 收到服务器Bind Cnf的处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_AP_SERVER_BIND_STATUS_IND,
                      TAF_XPDS_RcvAtApServerBindStatusInd_PreProc),

    /* 收到开始定位请求命令的处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_START_REQ,
                      TAF_XPDS_RcvAtGpsStartReq_PreProc),

    /* 收到查询请求命令的处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_QRY_REFLOC_INFO_REQ,
                      TAF_XPDS_RcvAtGpsQryRefLocInfoReq_PreProc),

    /* 收到查询时间的请求命令的处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_QRY_TIME_INFO_REQ,
                      TAF_XPDS_RcvAtGpsQryTimeInfoReq_PreProc),

    /* 收到GPS打断AGPS会话 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_STOP_REQ,
                      TAF_XPDS_RcvAtGpsStopReq_PreProc ),

    /* 收到查询请求命令的处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCMEAS,
                      ID_CAS_XPDS_TIME_SYNC_IND,
                      TAF_XPDS_RcvCasTimeSyncInd_PreProc),

    /* 收到查询请求命令的处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_HRUP,
                      ID_CAS_XPDS_TIME_SYNC_IND,
                      TAF_XPDS_RcvCasTimeSyncInd_PreProc),

    /* 收到查询请求命令的处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCMEAS,
                      ID_CAS_XPDS_REF_LOC_IND,
                      TAF_XPDS_RcvCasRefLocInd_PreProc),

    /* 收到查询请求命令的处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_HRUP,
                      ID_CAS_XPDS_REF_LOC_IND,
                      TAF_XPDS_RcvCasRefLocInd_PreProc),

    /* 收到PDE数据包 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_AP_FORWARD_DATA_IND,
                      TAF_XPDS_RcvApForwardDataInd_PreProc),

    /* 收到XSMS DATA IND的处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_XSMS,
                      ID_XSMS_XPDS_RCV_IND,
                      TAF_XPDS_RcvXsmsRcvInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_IND,
                      TAF_XPDS_RcvCasDschDataInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_XPDS_REF_LOC_CNF,
                      TAF_XPDS_RcvCasRefLocCnf_PreProc),


    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PPM_COMPLETE_NI_QUALITY,
                      TAF_XPDS_RcvPpmTimerExpire_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_IS801_SESSION,
                      TAF_XPDS_RcvTiXpdsIs801SessionExpired_PreProc),

    /* 未收到NI回复，超时处理 */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_GPS_ANSWER_NI_REQ_CNF,
                      TAF_XPDS_RcvTiWaitGpsAnswerNiReqExpire_PreProc ),

    /* 收到GPS的定位结果处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_POS_INFO_RSP,
                      TAF_XPDS_RcvAtGpsPosInfoRsp_PreProc ),

    /* 收到仪器设置开始定位的处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_UTS_TEST_START_REQ,
                      TAF_XPDS_RcvAtUtsTestStartReq_PreProc),

    /* 收到仪器设置停止定位的处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_UTS_TEST_STOP_REQ,
                      TAF_XPDS_RcvAtUtsTestStopReq_PreProc),

    /* 收到OM开始定位的处理 */
    TAF_ACT_TBL_ITEM( MSP_PID_DIAG_APP_AGENT,
                      ID_OM_NAS_CDMA_START_GPS_FIX_REQ,
                      TAF_XPDS_RcvOmStartGpsFixReq_PreProc),

    /* 收到OM停止定位的处理 */
    TAF_ACT_TBL_ITEM( MSP_PID_DIAG_APP_AGENT,
                      ID_OM_NAS_CDMA_STOP_GPS_FIX_REQ,
                      TAF_XPDS_RcvOmStopGpsFixReq_PreProc),

};

/* 预处理的消息状态表 */
TAF_STA_STRU g_astTafXpdsPreStaTbl[] =
{
    TAF_STA_TBL_ITEM( TAF_XPDS_L1_STA_PREPROC,
                      g_astTafXpdsPreProcActTbl)
};


/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_XPDS_GetPreProcStaTblSize
 功能描述  : 获取XPDS pre proc状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : c00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XPDS_GetPreProcStaTblSize( VOS_VOID )
{
    return (sizeof(g_astTafXpdsPreStaTbl)/sizeof(TAF_STA_STRU));
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetMainStaTblAddr
 功能描述  : 获取XPDS main状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_STA_STRU:指向状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月21日
    作    者   : c00299064
    修改内容   : 新生成函数

*****************************************************************************/
TAF_STA_STRU* TAF_XPDS_GetPreProcStaTblAddr( VOS_VOID )
{
    return (g_astTafXpdsPreStaTbl);
}

/*****************************************************************************
 函 数 名  : TAF_XPDS_GetPreProcFsmDescAddr
 功能描述  : 获取XPDS pre proc状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_FSM_DESC_STRU:指向状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月21日
    作    者   : c00299064
    修改内容   : 新生成函数

*****************************************************************************/
TAF_FSM_DESC_STRU* TAF_XPDS_GetPreProcFsmDescAddr( VOS_VOID )
{
    return (&g_stTafXpdsPreProcFsmDesc);
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


