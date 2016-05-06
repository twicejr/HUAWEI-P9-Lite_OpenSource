/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXsmsMtFsmMain.c
  版 本 号   : 初稿
  作    者   : C00299064
  生成日期   : 2014年10月31日
  功能描述   : 1X SMS(Short Message Service)状态机的状态表和ACT表
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月31日
    作    者   : C00299064
    修改内容   : 创建文件

  2.日    期   : 2014年11月11日
    作    者   : l00208516
    修改内容   : 修改
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafXsmsMtFsmMain.h"
#include  "TafXsmsMtFsmMainTbl.h"
#include  "xcc_sms_pif.h"
#include  "TafXsmsTimer.h"
#include  "TafXsmsCtx.h"
#include  "cas_1x_control_main_nas_pif.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_MT_FSM_MAIN_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* MT状态机状态全局变量 */
TAF_FSM_DESC_STRU                       g_stTafXsmsMtFsmDesc;

/* XSMS MT_IDLE下的事件处理表 */
TAF_ACT_STRU                            g_astTafXsmsMtIdleActTbl[] =
{
    /* 接收到DSCH_DATA_IND的处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_IND,
                      TAF_XSMS_RcvDataInd_MtIdle ),

    /* 接收到CSCH_DATA_IND的处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_CSCH_DATA_IND,
                      TAF_XSMS_RcvDataInd_MtIdle ),

    /* 收到Incoming call的处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_CSMS_INCOMING_CALL_IND,
                      TAF_XSMS_RcvIncomingCall_MtIdle ),

};


/* XSMS MT_WAITING_XCC_CALL_CONN的事件处理表 */
TAF_ACT_STRU                            g_astTafXsmsMtWaitXccConnActTbl[] =
{
    /* 等待CONN_IND超时处理*/
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MT_WAIT_CONN_IND,
                      TAF_XSMS_RcvCallConnTimeout_MtWaitXccCallConnCnf ),

    /* 收到了XCC_CONN_IND */
    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_CSMS_CALL_CONN_IND,
                      TAF_XSMS_RcvCallConnCnf_MtWaitXccCallConnCnf ),

    /* 收到ABORT消息 */
    /* 接收CAS发送traffic channel短信处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_IND,
                      TAF_XSMS_RcvDschDataInd_MtWaitCasDschDataInd ),

    /* 收到ABORT消息 */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SMS_ABORT_IND,
                      TAF_XSMS_RcvMtLinkAbort )

};

/* XSMS MT_WAITING_XCC_CNF的事件处理表 */
TAF_ACT_STRU                            g_astTafXsmsMtWaitXccAnsCallCnfActTbl[] =
{
    /* 等待XCC_CNF超时处理*/
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MT_WAIT_XCC_CNF,
                      TAF_XSMS_RcvAnsCallCnfTimeout_MtWaitXccAnsCallCnf ),

    /* 收到XCC_CNF */
    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_CSMS_ANSWER_CALL_CNF,
                      TAF_XSMS_RcvAnsCallCnf_MtWaitXccAnsCallCnf ),

    /* 接收CAS发送traffic channel短信处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_IND,
                      TAF_XSMS_RcvDschDataInd_MtWaitCasDschDataInd ),

    /* 收到ABORT消息 */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SMS_ABORT_IND,
                      TAF_XSMS_RcvMtLinkAbort )

};

/* XSMS MT_WAITING_XCC_SO_IND的事件处理表 */
TAF_ACT_STRU                            g_astTafXsmsMtWaitXccSoIndActTbl[] =
{
    /* 等待XCC_SO_IND超时处理*/
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MT_WAIT_XCC_SO_IND,
                      TAF_XSMS_RcvSoIndTimeout_MtWaitXccSoInd ),

    /* 收到XCC_SO_IND的处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_CSMS_SERVICE_CONNECT_IND,
                      TAF_XSMS_RcvSoInd_MtWaitXccSoInd ),

    /* 接收CAS发送traffic channel短信处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_IND,
                      TAF_XSMS_RcvDschDataInd_MtWaitCasDschDataInd ),

    /* 收到ABORT消息 */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SMS_ABORT_IND,
                      TAF_XSMS_RcvMtLinkAbort )

};

/* XSMS MT_WAITING_DSDH_DATA_IND状态下事件处理表 */
TAF_ACT_STRU                            g_astTafXsmsMtWaitingDSCHDataIndActTbl[] =
{
    /* 接收CAS发送traffic channel短信处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_IND,
                      TAF_XSMS_RcvDschDataInd_MtWaitCasDschDataInd ),


    /* 等待短信超时处理 */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MT_WAIT_DATA_IND,
                      TAF_XSMS_RcvDschDataIndTimeout_MtWaitCasDschDataInd ),


    /* 收到ABORT消息 */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SMS_ABORT_IND,
                      TAF_XSMS_RcvMtLinkAbort )

};

/* XSMS MT_WAITING_WRITE_UIM_CNF状态下事件处理表 */
TAF_ACT_STRU                            g_astTafXsmsMtWaitingWriteUimCnfActTbl[] =
{
    /* UIM卡写卡结果处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_UPDATEFILE_CNF,
                      TAF_XSMS_RcvWriteUimCnf_MtWaitWriteUimCnf ),

    /* UIM卡写卡超时处理 */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MT_WAIT_WRITE_UIM_CNF,
                      TAF_XSMS_RcvWriteUimCnfTimeout_MtWaitWriteUimCnf ),

};

/* XSMS MT_WAITING_READ_UIM_CNF状态下事件处理表 */
TAF_ACT_STRU                            g_astTafXsmsMtWaitingReadUimCnfActTbl[] =
{
    /* UIM卡读卡结果处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_READFILE_CNF,
                      TAF_XSMS_RcvReadUimCnf_MtWaitReadUimCnf ),

    /* UIM卡读卡超时处理 */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MT_WAIT_READ_UIM_CNF,
                      TAF_XSMS_RcvReadUimCnfTimeout_MtWaitReadUimCnf ),

};

/* XSMS MT_WAITING_AS_CNF状态下事件处理表 */
TAF_ACT_STRU                            g_astTafXsmsMtWaitingAsCnfActTbl[] =
{
    /* 接收CAS发送L2 ACK处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_CNF,
                      TAF_XSMS_RcvDschDataCnf_MtWaitCasDataCnf ),

    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_CSCH_DATA_CNF,
                      TAF_XSMS_RcvCschDataCnf_MtWaitCasDataCnf ),

    /* 等待CAS发送L2 ACK超时处理 */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MT_WAIT_AS_CNF,
                      TAF_XSMS_RcvCasCnfTimeout_MtWaitCasDataCnf ),

    /* 重发定时器超时 */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MT_RESEND,
                      TAF_XSMS_MtResend ),
    /* 收到ABORT消息 */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SMS_ABORT_IND,
                      TAF_XSMS_RcvMtLinkAbort_MtWaitCasCnf)
};



/* XSMS MT_WAITING_END_CALL_CNF状态下事件处理表 */
TAF_ACT_STRU                            g_astTafXsmsMtWaitingXccDisconnectActTbl[] =
{
    /* 接收XCC发送拆除信道结果处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_CSMS_END_SMS_CALL_CNF,
                      TAF_XSMS_RcvEndCallCnf_MtWaitEndCallCnf ),

    /* 等待XCC发送拆除信道结果超时处理 */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MT_WAIT_CALL_END,
                      TAF_XSMS_RcvEndCallCnfTimeout_MtWaitEndCallCnf ),

};


/* Xsms MT状态机状态处理表 */
TAF_STA_STRU                            g_astTafXsmsMtStaTbl[] =
{
    /*****************定义MT_IDLE_STATE状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MT_IDLE_STATE,
                      g_astTafXsmsMtIdleActTbl ),

    /*****************定义MT_WAITING_XCC_CALL_CONN**********************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MT_WAITING_XCC_CALL_CONN_STATE,
                      g_astTafXsmsMtWaitXccConnActTbl ),

    /*****************定义MT_WAITING_XCC_CNF状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MT_WAITING_XCC_CALL_CNF_STATE,
                      g_astTafXsmsMtWaitXccAnsCallCnfActTbl ),

    /*****************定义MT_WAITING_XCC_SO状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MT_WAITING_XCC_SO_IND_STATE,
                      g_astTafXsmsMtWaitXccSoIndActTbl),

    /*****************定义MT_WAITING_DSCH_DATA_IND状态转移表****************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MT_WAITING_DSCH_DATA_IND_STATE,
                      g_astTafXsmsMtWaitingDSCHDataIndActTbl ),

    /*****************定义MT_WAITING_WRITE_UIM_CNF状态转移表****************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MT_WAITING_UIM_WRITE_CNF_STATE,
                      g_astTafXsmsMtWaitingWriteUimCnfActTbl ),

    /*****************定义MT_WAITING_READ_UIM_CNF状态转移表*****************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MT_WAITING_UIM_READ_CNF_STATE,
                      g_astTafXsmsMtWaitingReadUimCnfActTbl ),

    /*****************定义MT_WAITING_AS_CNF状态转移表***********************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MT_WAITING_AS_CNF_STATE,
                      g_astTafXsmsMtWaitingAsCnfActTbl ),

    /*****************定义MT_WAITING_END_CALL_CNF状态转移表***********************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MT_WAITING_XCC_DISCONNECT_STATE,
                      g_astTafXsmsMtWaitingXccDisconnectActTbl ),
};
/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_XSMS_GetMtFsmTblNum
 功能描述  : 注册MT的状态机里面STATE表的个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月19日
    作    者   : l00208516
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_GetMtFsmTblNum(VOS_VOID)
{
    return (sizeof(g_astTafXsmsMtStaTbl)/sizeof(TAF_STA_STRU));
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



