/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSpmFsmMainTbl.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2013年5月8日
  最近修改   :
  功能描述   : TafSpmFsmMainTbl.C文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年5月8日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

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
/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-9-23, begin */
#include "ImsaInterface.h"
/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-9-23, end */
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

    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-17, begin */
    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-17, end */

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

    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-23, begin */
    /* AT CALL message */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_CALL_APP_ORIG_REQ,
                      TAF_SPM_RcvAppReqMsg_Main ),

    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-17, begin */
    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-17, end */


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

    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-17, begin */
    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-17, end */

    /* STK SMS message */
    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_MSG_SEND_REQ,
                      TAF_SPM_RcvAppReqMsg_Main ),
    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-23, end */

    /* TAF Internal message */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      TAF_SPM_INTERNAL_SERVICE_CTRL_RESULT_IND,
                      TAF_SPM_RcvSpmServiceCtrlResultInd_Main ),



    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-14, begin */
    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-14, end */


    /* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-09, end */

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

/*****************************************************************************
 函 数 名  : TAF_SPM_GetMainProcessStaTblSize
 功能描述  : 获取SPM模块主处理状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:适配层主处理状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月7日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SPM_GetMainProcessStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astTafSpmMainProcessFsmTbl)/sizeof(TAF_STA_STRU));
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetMainFsmDescAddr
 功能描述  : 获取SPM模块主处理状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向SPM主处理状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月7日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
TAF_FSM_DESC_STRU * TAF_SPM_GetMainFsmDescAddr(VOS_VOID)
{
    return (&g_stTafSpmMainFsmDesc);
}









#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

