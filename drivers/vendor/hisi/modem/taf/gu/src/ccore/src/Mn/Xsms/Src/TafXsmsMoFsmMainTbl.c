/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXsmsMoFsmMain.c
  版 本 号   : 初稿
  作    者   : C00299064
  生成日期   : 2014年11月07日
  功能描述   : 1X SMS(Short Message Service)状态机的状态表和ACT表
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月31日
    作    者   : C00299064
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "siapppb.h"
#include "TafXsmsCtx.h"
#include "xcc_sms_pif.h"
#include "TafXsmsTimer.h"
#include "TafXsmsMoFsmMain.h"
#include "TafAppXsmsInterface.h"
#include "TafXsmsMoFsmMainTbl.h"
#include "MmaXsmsInterface.h"
#include "TafXsmsStkInterface.h"
#include "TafXpdsXsmsInterface.h"
#include "taf_xcall_xsms_pif.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_MO_FSM_MAIN_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* Mo状态机状态全局变量 */
TAF_FSM_DESC_STRU                       g_stTafXsmsMoFsmDesc;

/* XSMS Mo_IDLE下的事件处理表 */
TAF_ACT_STRU                            g_astTafXsmsMoIdleActTbl[] =
{
    /* 收到AT 发送命令的处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_XSMS,
                      TAF_XSMS_APP_MSG_TYPE_SEND_REQ,
                      TAF_XSMS_RcvAtSendReqProc_MoIdle),

    /* 收到STK的发送请求 */
    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      ID_STK_XSMS_SEND_SMS_REQ,
                      TAF_XSMS_RcvStkSendReqProc_MoIdle ),

    /* 收到MTA 发送命令的处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_XPDS_XSMS_SEND_REQ,
                      TAF_XSMS_RcvXpdsSendReqProc_MoIdle),

    /* 收到XCALL 发送命令的处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_XCALL_XSMS_KMC_MSG_SEND_REQ,
                      TAF_XSMS_RcvXcallDataReq_MoIdle),
};

/* XSMS MoWaitFdnCnf 的事件处理表 */
TAF_ACT_STRU                            g_astTafXsmsMoWaitFdnCnfActTbl[] =
{
    /* 等待FDN_CNF超时处理*/
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MO_WAIT_FDN_CNF,
                      VOS_NULL_PTR ),

    /* 收到了FDN_CNF */
    TAF_ACT_TBL_ITEM( MAPS_PB_PID,
                      SI_PB_EVENT_FDNCHECK_CNF,
                      VOS_NULL_PTR )/* FDN 以后实现 */
};

/* XSMS Mo_WAIT_CC_CNF的事件处理表 */
TAF_ACT_STRU                            g_astTafXsmsMoWaitCcCNFActTbl[] =
{
    /* 等待CC_CNF超时处理*/
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MO_WAIT_CC_CNF,
                      VOS_NULL_PTR  ),

    /* 收到CC_CNF */
    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      USIMM_STKENVELOPE_CNF,
                      VOS_NULL_PTR ), /* SMS Call Control 以后实现 */

};

/* XSMS MO_WAITING_XCC_ORIG_CALL_CNF的事件处理表 */
TAF_ACT_STRU                            g_astTafXsmsMoWaitXccCallCnfActTbl[] =
{
    /* 等待XCC_ORIG_CALL_CNF超时处理*/
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MO_WAIT_XCC_CALL_CNF,
                      TAF_XSMS_RcvXccCallCnfTimeOut_MoWaitXccCallCnf),

    /* 收到XCC_ORIG_CALL_CNF的处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_CSMS_ORIG_SMS_CALL_CNF,
                      TAF_XSMS_RcvXccOrigCallCnf_MoWaitXccOrigCallCnf),

    /* 收到延迟重建信道超时的处理 */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MO_RELINK,
                      TAF_XSMS_RcvRelinkTimeOut_MoWaitXccOrigCallCnf ),


    /* 收到重定向完成的消息 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_XSMS_SERVICE_STATUS_IND,
                      TAF_XSMS_RcvMmaServiceStatus_MoWaitXccOrigCallCnf ),

};

/* XSMS Mo_WAITING_XCC_SO_IND的事件处理表 */
TAF_ACT_STRU                            g_astTafXsmsMoWaitXccSoIndActTbl[] =
{
    /* 等待XCC_SO_IND超时处理*/
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MO_WAIT_XCC_SO_IND,
                      TAF_XSMS_RcvXccSoIndTimeOut_MoWaitXccSoInd ),

    /* 收到XCC_SO_IND的处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_CSMS_SERVICE_CONNECT_IND,
                      TAF_XSMS_RcvXccSoInd_MoWaitXccSoInd),

    /* 收到ABORT消息 */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SMS_ABORT_IND,
                      TAF_XSMS_RcvMoLinkAbort_MoWaitSoInd )

};
/* XSMS MO_WAITING_AS_CNF状态下事件处理表 */
TAF_ACT_STRU                            g_astTafXsmsMoWaitAsCnfActTbl[] =
{
    /* 收到接入层AS_CNF */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_CNF,
                      TAF_XSMS_RcvDschDataCnf_MoWaitAsCnf),

    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_CSCH_DATA_CNF,
                      TAF_XSMS_RcvCschDataCnf_MoWaitAsCnf),

    /* 等待接入层AS_CNF超时处理 */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MO_WAIT_AS_CNF,
                      TAF_XSMS_RcvAsCnfTimeout_MoWaitAsCnf),


    /* 延迟重新发送的定时器超时 */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MO_RESEND,
                      TAF_XSMS_RcvResendTimeOut_MoWaitAsCnf),

    /* 收到ABORT消息 */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SMS_ABORT_IND,
                      TAF_XSMS_RcvMoLinkAbort_MoWaitAsCnf ),

    /* 收到TL_ACK处理 *//* 注意回AS-ACK*/
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_IND,
                      TAF_XSMS_RcvDschTlACK_MoWaitTlACK ),

    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_CSCH_DATA_IND,
                      TAF_XSMS_RcvCschTlACK_MoWaitTlACK ),
};

/* XSMS MO_WAITING_TL_ACK状态下事件处理表 */
TAF_ACT_STRU                            g_astTafXsmsMoWaitTlAckActTbl[] =
{
    /* 收到TL_ACK处理 *//* 注意回AS-ACK*/
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_IND,
                      TAF_XSMS_RcvDschTlACK_MoWaitTlACK ),

    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_CSCH_DATA_IND,
                      TAF_XSMS_RcvCschTlACK_MoWaitTlACK ),

    /* MO_WAITING_TL_ACK超时处理 */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MO_WAIT_TL_ACK,
                      TAF_XSMS_RcvTlAckTimeOut_MoWaitTlACK),


    /* 收到ABORT消息 */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SMS_ABORT_IND,
                      TAF_XSMS_RcvMoLinkAbort_MoWaitTlAck )

};

/* XSMS MO_WAITING_XCC_END_CALL_CNF 状态下事件处理表 */
TAF_ACT_STRU                            g_astTafXsmsMoWaitCallEndActTbl[] =
{
    /* 接收XCC 断链成功处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_CSMS_END_SMS_CALL_CNF,
                      TAF_XSMS_RcvEndCallCnf_MoWaitEndCallCnf),

    /* 等待断链超时处理 */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MO_WAIT_END_CALL,
                      TAF_XSMS_RcvEndCallCnfTimeout_MoWaitEndCallCnf),

        /* 接收链路断开的处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SMS_ABORT_IND,
                      TAF_XSMS_RcvSmsAbortInd_MoWaitLinkAbort),

};


/* XSMS MO_WAITING_XCC_END_CALL_CNF 状态下事件处理表 */
TAF_ACT_STRU                            g_astTafXsmsMoWaitCasAbortIndActTbl[] =
{
    /* 接收链路断开的处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SMS_ABORT_IND,
                      TAF_XSMS_RcvSmsAbortInd_MoWaitLinkAbort),

    /* 等待断链超时处理 */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MO_WAIT_SMS_ABORT,
                      TAF_XSMS_RcvSmsAbortInd_MoWaitLinkAbort),

};


/* Xsms Mo状态机状态处理表 */
TAF_STA_STRU                            g_astTafXsmsMoStaTbl[] =
{
    /*****************定义Mo_IDLE_STATE状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MO_IDLE_STATE,
                      g_astTafXsmsMoIdleActTbl ),

    /*****************定义MO_WAITING_FDN_CNF**********************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MO_WAITING_FDN_CNF,
                      g_astTafXsmsMoWaitFdnCnfActTbl ),

    /*****************定义MO_WAITING_CC_CNF状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MO_WAITING_CC_CNF,
                      g_astTafXsmsMoWaitCcCNFActTbl ),

    /*****************定义MO_WAITING_XCC_ORIG_CALL_CNF,状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MO_WAITING_XCC_ORIG_CALL_CNF,
                      g_astTafXsmsMoWaitXccCallCnfActTbl),

    /*****************定义MO_WAITING_XCC_SO_IND状态转移表****************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MO_WAITING_XCC_SO_IND,
                      g_astTafXsmsMoWaitXccSoIndActTbl ),

    /*****************定义MO_WAITING_AS_CNF状态转移表****************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MO_WAITING_AS_CNF,
                      g_astTafXsmsMoWaitAsCnfActTbl),

    /*****************定义MO_WAITING_TL_ACK状态转移表*****************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MO_WAITING_TL_ACK,
                      g_astTafXsmsMoWaitTlAckActTbl ),

    /*****************定义MO_WAITING_XCC_END_CALL_CNF状态转移表***********************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MO_WAITING_XCC_END_CALL_CNF,
                      g_astTafXsmsMoWaitCallEndActTbl ),


    /*****************定义MO_WAITING_CAS_SMS_ABORT_IND状态转移表***********************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MO_WAITING_CAS_SMS_ABORT_IND,
                      g_astTafXsmsMoWaitCasAbortIndActTbl ),

};

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_XSMS_GetMoFsmTblNum
 功能描述  : 注册MO的状态机里面STATE表的个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_GetMoFsmTblNum(VOS_VOID)
{
    return (sizeof(g_astTafXsmsMoStaTbl)/sizeof(TAF_STA_STRU));
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

