/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXccFsmMainTbl.c
  版 本 号   : 初稿
  作    者   : y00213812
  生成日期   : 2014年07月03日
  功能描述   : XCC L1主状态机table表
  函数列表   :
  修改历史   :
  1.日    期   : 2014年07月03日
    作    者   : y00213812
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "xsd_xcc_pif.h"
#include "CnasXccFsmMain.h"
#include "CnasXccFsmMainTbl.h"
#include "xcc_xcall_pif.h"
#include "cas_1x_control_main_nas_pif.h"
#include "cas_1x_trchctrl_proc_nas_pif.h"
#include "CnasXccSndInternalMsg.h"
#include "CnasXccTimer.h"
#include "xcc_aps_pif.h"
#include "xcc_sms_pif.h"
#include  "xcc_xpds_pif.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_FSM_MAIN_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* CNAS XCC 主状态机 */
NAS_FSM_DESC_STRU                       g_stCnasXccMainFsmDesc;


/* XCC L1 IDLE状态下事件处理表 */
NAS_ACT_STRU g_stCnasXccIdleActTbl[] =
{
    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_ORIG_CALL_REQ,
                     CNAS_XCC_RcvOrigCallReq_L1Main_Idle),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_ORIG_DATA_CALL_REQ,
                     CNAS_XCC_RcvOrigDataCallReq_L1Main_Idle),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSMS,
                     ID_CSMS_XCC_ORIG_SMS_CALL_REQ,
                     CNAS_XCC_RcvOrigCsmsCallReq_L1Main_Idle),
    NAS_ACT_TBL_ITEM(UEPS_PID_XPDS,
                     ID_XPDS_XCC_ORIG_AGPS_CALL_REQ,
                     CNAS_XCC_RcvOrigAgpsCallReq_L1Main_Idle),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_PAGING_IND,
                     CNAS_XCC_RcvPagingInd_L1Main_Idle)
};

/* XCC L1 MO CALLING状态下事件处理表 */
NAS_ACT_STRU g_stCnasXccMoCallingActTbl[] =
{
    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_MO_CALLING_RSLT_CNF,
                     CNAS_XCC_RcvMoCallingRsltCnf_L1Main_MoCalling),
};

/* XCC L1 MT CALLING状态下事件处理表 */
NAS_ACT_STRU g_stCnasXccMtCallingActTbl[] =
{
    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_MT_CALLING_RSLT_CNF,
                     CNAS_XCC_RcvMtCallingRsltCnf_L1Main_MtCalling)
};

/* XCC L1 ENDING状态下事件处理表 */
NAS_ACT_STRU g_stCnasXccEndingActTbl[] =
{
    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_TERMINATE_IND,
                     CNAS_XCC_RcvAsCallTerminateInd_L1Main_Ending),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_DSCH_DATA_IND,
                     CNAS_XCC_RcvAsDschDataInd_L1Main_Ending),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING,
                     CNAS_XCC_RcvTiProtectPowerDown_L1Main_Ending),


    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_POWER_DOWN_IND,
                     CNAS_XCC_RcvXccPowerDownInd_L1Main_Ending),
};

/* XCC L1 CONVERSATION状态下事件处理表 */
NAS_ACT_STRU g_stCnasXccConversationActTbl[] =
{
    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_TERMINATE_IND,
                     CNAS_XCC_RcvAsCallTerminateInd_L1Main_Conversation),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_REL_IND,
                     CNAS_XCC_RcvAsCallRelInd_L1Main_Conversation),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_HANGUP_CALL_REQ,
                     CNAS_XCC_RcvXcallHandupCallReq_L1Main_Conversation),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_HANGUP_DATA_CALL_REQ,
                     CNAS_XCC_RcvApsHangupDataCallReq_L1Main_Conversation),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSMS,
                     ID_CSMS_XCC_END_SMS_CALL_REQ,
                     CNAS_XCC_RcvCsmsEndSmsCallReq_L1Main_Conversation),
    NAS_ACT_TBL_ITEM(UEPS_PID_XPDS,
                     ID_XPDS_XCC_END_AGPS_CALL_REQ,
                     CNAS_XCC_RcvXpdsEndAgpsCallReq_L1Main_Conversation),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_DSCH_DATA_IND,
                     CNAS_XCC_RcvAsDschDataInd_L1Main_Conversation),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_UPDATE_CALL_INFO_IND,
                     CNAS_XCC_RcvAsUpdateCallInfoInd_L1Main_Conversation),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_POWER_DOWN_IND,
                     CNAS_XCC_RcvXccPowerDownInd_L1Main_Conversation),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_ABORT_REQ,
                     CNAS_XCC_RcvXccAbortReq_L1Main_Conversation),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_NDSS_REDIAL_IND,
                     CNAS_XCC_RcvXccNdssRedialInd_L1Main_Conversation),
};

/* XCC L1 主状态机状态处理表 */
NAS_STA_STRU g_astCnasXccL1MainStaTbl[] =
{

    NAS_STA_TBL_ITEM( CNAS_XCC_L1_STA_IDLE,
                      g_stCnasXccIdleActTbl ),

    NAS_STA_TBL_ITEM( CNAS_XCC_L1_STA_MT_CALLING,
                      g_stCnasXccMtCallingActTbl ),

    NAS_STA_TBL_ITEM( CNAS_XCC_L1_STA_MO_CALLING,
                      g_stCnasXccMoCallingActTbl ),

    NAS_STA_TBL_ITEM( CNAS_XCC_L1_STA_ENDING,
                      g_stCnasXccEndingActTbl ),

    NAS_STA_TBL_ITEM( CNAS_XCC_L1_STA_CONVERSATION,
                      g_stCnasXccConversationActTbl ),
};


/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/


/*****************************************************************************
 函 数 名  : CNAS_XCC_GetL1MainStaTblSize
 功能描述  : 获取1X XCC主状态机状态表大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回XCC主状态机状态表size
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年07月23日
   作    者   : y00213812
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_GetL1MainStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasXccL1MainStaTbl)/sizeof(NAS_STA_STRU));
}

/*****************************************************************************
 函 数 名  : NAS_XCC_GetMainFsmDescAddr
 功能描述  : 获取MAIN状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向MAIN状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月03日
    作    者   : y00213812
    修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU * CNAS_XCC_GetMainFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasXccMainFsmDesc);
}

/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




