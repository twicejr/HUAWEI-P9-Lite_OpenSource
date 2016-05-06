/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaFsmMainTbl.c
  版 本 号   : 初稿
  作    者   : W00176964
  生成日期   : 2013年7月9日
  最近修改   :
  功能描述   : TAF MMA Main状态机描述表文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年7月9日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "TafFsm.h"
#include "TafMmaFsmMainTbl.h"
#include "MmaAppLocal.h"
#include "TafMmaFsmMain.h"
#include "TafMmaSndInternalMsg.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_FSM_MAIN_TBL_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


TAF_FSM_DESC_STRU                       g_stTafMmaMainFsmDesc;


TAF_ACT_STRU   g_astTafMmaMainActTbl[]                      =
{
    /* OM的消息处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_SPY,
                      OAM_MMA_PHONE_MODE_SET_REQ,
                      TAF_MMA_RcvAppPhoneModeSetReq_Main),
    TAF_ACT_TBL_ITEM( CCPU_PID_CBT,
                      OAM_MMA_PHONE_MODE_SET_REQ,
                      TAF_MMA_RcvAppPhoneModeSetReq_Main),
    /* 内部消息的处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      MMA_MMA_INTER_POWER_INIT,
                      TAF_MMA_RcvMmaInterPowerInit_Main ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      MMA_MMA_INTER_USIM_STATUS_CHANGE_IND,
                      TAF_MMA_RcvMmaInterUsimStatusChangeInd_Main ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      MMA_MMA_PHONE_MODE_RSLT_IND,
                      TAF_MMA_RcvMmaPhoneModeRsltInd_Main),

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      MMA_MMA_SYS_CFG_RSLT_IND,
                      TAF_MMA_RcvMmaSysCfgRsltInd_Main),

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      MMA_MMA_SIM_LOCK_STATUS_CHANGE_IND,
                      TAF_MMA_RcvMmaSimlockStatusChangeInd_Main ),

#if (FEATURE_IMS == FEATURE_ON)
    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      MMA_MMA_IMS_SWITCH_RSLT_IND,
                      TAF_MMA_RcvMmaImsSwitchRsltInd_Main),
#endif

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      MMA_MMA_INTER_SYS_CFG_SET_REQ,
                      TAF_MMA_RcvMmaInterSysCfgSetReq_Main ),

    /* USIM的消息处理 */
    /* 和hujun确认，USIM不会再报这条消息，通过PIH上报卡状态 */

    TAF_ACT_TBL_ITEM( MAPS_PIH_PID,
                      USIMM_CARDSTATUS_IND,
                      TAF_MMA_RcvPihUsimStatusInd_Main),

    TAF_ACT_TBL_ITEM( MAPS_PIH_PID,
                      USIMM_STKREFRESH_IND,
                      TAF_MMA_RcvUsimRefreshIndMsg_Main),

    /* MSCC的消息处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_DETACH_IND,
                      Sta_DetachInd),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_PLMN_LIST_CNF,
                      Sta_PlmnListInd),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_PLMN_LIST_REJ,
                      Sta_PlmnListRej),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_PLMN_LIST_ABORT_CNF,
                      TAF_MMA_RcvPlmnListAbortCnf),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_SPEC_PLMN_SEARCH_ABORT_CNF,
                      TAF_MMA_RcvSpecPlmnSearchAbortCnf),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_PLMN_SPECIAL_SEL_CNF,
                      TAF_MMA_RcvMsccPlmnSpecialSelCnf),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_PLMN_RESEL_CNF,
                      TAF_MMA_RcvMsccPlmnReselCnf),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_PLMN_SPECIAL_SEL_REJ,
                      TAF_MMA_RcvMsccUserPlmnRej),

    /* Modified by w00167002 for L-C互操作项目, 2014-2-17, begin */

    /* CMMCA/AT的消息处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PHONE_MODE_SET_REQ,
                      TAF_MMA_RcvTafPhoneModeSetReq_Main),
    /* Modified by w00167002 for L-C互操作项目, 2014-2-17, end */

    /* Modified by w00167002 for L-C互操作项目, 2014-2-13, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_SYS_CFG_SET_REQ,
                      TAF_MMA_RcvSysCfgSetReq_Main),
    /* Modified by w00167002 for L-C互操作项目, 2014-2-13, end */

#if (FEATURE_ON == FEATURE_CSG)
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CSG_LIST_SEARCH_REQ,
                      TAF_MMA_RcvTafCsgListSearchReq_Main),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CSG_LIST_ABORT_REQ,
                      TAF_MMA_RcvTafCsgListAbortReq_Main),
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_CSG_LIST_SEARCH_CNF,
                      TAF_MMA_RcvMsccCsgListSearchCnf_Main),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_CSG_LIST_REJ,
                      TAF_MMA_RcvMsccCsgListRej_Main),


    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_CSG_LIST_ABORT_CNF,
                      TAF_MMA_RcvMsccCsgListAbortCnf_Main),
#endif
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PLMN_LIST_REQ,
                      TAF_MMA_RcvMmaPlmnListReq_Main),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PLMN_LIST_ABORT_REQ,
                      TAF_MMA_RcvPlmnListAbortReq_Main),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PLMN_SPECIAL_SEL_REQ,
                      TAF_MMA_RcvPlmnSpecialSelReq_Main),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PLMN_AUTO_RESEL_REQ,
                      TAF_MMA_RcvPlmnAutoReselReq_Main),


    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_ATTACH_REQ,
                      TAF_MMA_RcvAttachReq_Main),


    /* Modified by s00246516 for L-C互操作项目, 2014-02-14, Begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_DETACH_REQ,
                      TAF_MMA_RcvDetachReq_Main),
    /* Modified by s00246516 for L-C互操作项目, 2014-02-14, End */

#if (FEATURE_IMS == FEATURE_ON)
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_IMS_SWITCH_SET_REQ,
                      TAF_MMA_RcvTafImsSwitchSetReq_Main),
#endif
};

TAF_ACT_STRU   g_astTafMmaSysCfgActTbl[]                      =
{
    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      MMA_MMA_SYS_CFG_RSLT_IND,
                      TAF_MMA_RcvMmaSysCfgRsltInd_Main)
};

TAF_STA_STRU g_astTafMmaMainStaTbl[] =
{
    TAF_STA_TBL_ITEM( TAF_MMA_MAIN_STA_IDLE,
                      g_astTafMmaMainActTbl ),

    TAF_STA_TBL_ITEM( TAF_MMA_MAIN_STA_SYSCFG,
                      g_astTafMmaSysCfgActTbl ),
};

/*****************************************************************************
 函 数 名  : TAF_MMA_GetMainStaTblSize
 功能描述  : 获取MAIN状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:MAIN状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月9日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_GetMainStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astTafMmaMainStaTbl)/sizeof(TAF_STA_STRU));
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetMainFsmDescAddr
 功能描述  : 获取MAIN状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_FSM_DESC_STRU:指向MAIN状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月9日
    作    者   : W00176964
    修改内容   : 新生成函数

*****************************************************************************/
TAF_FSM_DESC_STRU * TAF_MMA_GetMainFsmDescAddr(VOS_VOID)
{
    return (&g_stTafMmaMainFsmDesc);
}

/*****************************************************************************
  3 函数实现
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

