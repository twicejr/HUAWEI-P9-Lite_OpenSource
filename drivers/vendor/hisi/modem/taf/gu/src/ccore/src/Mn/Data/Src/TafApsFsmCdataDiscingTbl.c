/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsFsmCdataDiscingTbl.c
  版 本 号   : 初稿
  作    者   : h00246512
  生成日期   : 2014年10月14日
  最近修改   :
  功能描述   : CdataDiscing状态机处理表
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月14日
    作    者   : h00246512
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafApsFsmCdataDiscingTbl.h"
#include  "taf_aps_ppp_pif.h"
#include  "TafApsFsmCdataDiscing.h"
#include  "TafApsApi.h"
#include  "TafApsTimerMgmt.h"
#include  "xcc_aps_pif.h"
#include  "TafApsSndInternalMsg.h"
#include  "hsm_aps_pif.h"
#include  "ehsm_aps_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_CDATA_DISCING_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* TAF APS状态机数组:CDATA DISCING 状态机名称*/
TAF_FSM_DESC_STRU                       g_stTafApsCdataDiscingFsmDesc;

/* TAF_APS_CDATA_DISCING_SUBSTA_INIT动作表 */
TAF_ACT_STRU   g_astTafApsCdataDiscingSubStaInitTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ENTER_DORMANT_IND,
                     TAF_APS_RcvPsCallEnterDormantInd_CdataDiscing_Init),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ,
                     TAF_APS_RcvApsInternEndCdmaCallReq_CdataDiscing_Init),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_CdataDiscing_Init),

    TAF_ACT_TBL_ITEM(MSPS_PID_PPPC,
                     ID_PPP_APS_DEACT_NTF,
                     TAF_APS_RcvPppDeactNtf_CdataDiscing_Init),

};

/* TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_DEACT_CNF 动作表 */
TAF_ACT_STRU   g_astTafApsCdataDiscingSubStaWaitHsmDecatCnfTbl[]   =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_HSM,
                     ID_HSM_APS_DISC_CNF,
                     TAF_APS_RcvHsmDiscCnf_CdataDiscing_WaitHsmDiscCnf),

    TAF_ACT_TBL_ITEM(UEPS_PID_HSM,
                     ID_HSM_APS_DISC_IND,
                     TAF_APS_RcvHsmDiscInd_CdataDiscing_WaitHsmDiscCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_CdataDiscing_WaitHsmDiscCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_DISCING,
                     TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitHsmDiscCnf),

};

/* TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_HANGUP_DATA_CALL_CNF 动作表 */
TAF_ACT_STRU   g_astTafApsCdataDiscingSubStaWaitXccHangUpDataCallCnfTbl[]   =
{

    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_HANGUP_DATA_CALL_CNF,
                     TAF_APS_RcvXccHangUpDataCnf_CdataDiscing_WaitXccHangUpDataCallCnf),

    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_DATA_CALL_DISC_IND,
                     TAF_APS_RcvXccDataCallDiscInd_CdataDiscing_WaitXccHangUpDataCallCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_CdataDiscing_WaitXccHangUpDataCallCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_DISCING,
                     TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitXccHangUpDataCallCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ,
                     TAF_APS_RcvPsInterEpdszidReOrigReq_CdataDiscing_WaitXccHangUpDataCallCnf),
};

/* TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF 动作表 */
TAF_ACT_STRU   g_astTafApsCdataDiscingSubStaWaitEhsmPdnDeactCnfTbl[]   =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_EHSM,
                     ID_EHSM_APS_PDN_DEACTIVATE_CNF,
                     TAF_APS_RcvEhsmPdnDeactCnf_CdataDiscing_WaitEhsmPdnDeactCnf),

    TAF_ACT_TBL_ITEM(UEPS_PID_EHSM,
                     ID_EHSM_APS_PDN_DEACTIVATE_IND,
                     TAF_APS_RcvEhsmPdnDeactInd_CdataDiscing_WaitEhsmPdnDeactCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_DISCING,
                     TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitEhsmPdnDeactCnf),

};

/* TAF_APS_CDATA_DISCING_SUBSTA_SUSPEND 动作表 */
TAF_ACT_STRU   g_astTafApsCdataDiscingSubStaSuspendTbl[]   =
{

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvPsInterSrvStaChangeInd_CdataDiscing_Suspend),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_DISCING,
                     TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_Suspend),

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_ESM_SM_EPS_BEARER_INFO_IND,
                     TAF_APS_RcvEsmSmEpsBearerInfoInd_CdataDiscing_Suspend),

    TAF_ACT_TBL_ITEM(UEPS_PID_EHSM,
                     ID_EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND,
                     TAF_APS_RcvEhsmApsLteHandoverToEhrpdInd_CdataDiscing_Suspend),

};


/* TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF 动作表 */
TAF_ACT_STRU   g_astTafApsCdataDiscingSubStaWaitPppDeactCnfTbl[]   =
{

    TAF_ACT_TBL_ITEM(MSPS_PID_PPPC,
                     ID_PPP_APS_DEACT_CNF,
                     TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitPppDeactCnf),

    TAF_ACT_TBL_ITEM(MSPS_PID_PPPC,
                     ID_PPP_APS_DEACT_NTF,
                     TAF_APS_RcvPppDeactInd_CdataDiscing_WaitPppDeactCnf),

    TAF_ACT_TBL_ITEM(MSPS_PID_PPPC,
                     ID_PPP_APS_RECONN_IND,
                     TAF_APS_RcvPppReConnInd_CdataDiscing_WaitPppDeactCnf),

    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_DATA_CALL_DISC_IND,
                     TAF_APS_RcvXccDataCallDiscInd_CdataDiscing_WaitPppDeactCnf),

    TAF_ACT_TBL_ITEM(UEPS_PID_HSM,
                     ID_HSM_APS_DISC_IND,
                     TAF_APS_RcvHsmDiscInd_CdataDiscing_WaitPppDeactCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF,
                     TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitPppDeactCnf),
};

/* TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_ORIG_CNF 动作表 */
TAF_ACT_STRU   g_astTafApsCdataDiscingSubStaWaitXccOrigCnfTbl[]   =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_ORIG_DATA_CALL_CNF,
                     TAF_APS_RcvXccOrigDataCallCnf_CdataDiscing_WaitXccOrigCnf),

    TAF_ACT_TBL_ITEM(MSPS_PID_PPPC,
                     ID_PPP_APS_DEACT_CNF,
                     TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitXccOrigCnf),

    TAF_ACT_TBL_ITEM(MSPS_PID_PPPC,
                     ID_PPP_APS_DEACT_NTF,
                     TAF_APS_RcvPppDeactInd_CdataDiscing_WaitXccOrigCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF,
                     TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitXccOrigCnf),

};

/* TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_ORIG_CNF 动作表 */
TAF_ACT_STRU   g_astTafApsCdataDiscingSubStaWaitHsmOrigCnfTbl[]   =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_HSM,
                     ID_HSM_APS_ORIG_CNF,
                     TAF_APS_RcvHsmOrigCnf_CdataDiscing_WaitHsmOrigCnf),

    TAF_ACT_TBL_ITEM(MSPS_PID_PPPC,
                     ID_PPP_APS_DEACT_CNF,
                     TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitHsmOrigCnf),

    TAF_ACT_TBL_ITEM(MSPS_PID_PPPC,
                     ID_PPP_APS_DEACT_NTF,
                     TAF_APS_RcvPppDeactInd_CdataDiscing_WaitHsmOrigCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF,
                     TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitHsmOrigCnf),

};

/* TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_SO_CONNECTED 动作表 */
TAF_ACT_STRU   g_astTafApsCdataDiscingSubStaWaitXccSoConnectedTbl[]   =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_DATA_SERVICE_CONNECT_IND,
                     TAF_APS_RcvXccDataServiceConnInd_CdataDiscing_WaitXccSoConnected),

    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_DATA_CALL_DISC_IND,
                     TAF_APS_RcvXccDataCallDiscInd_CdataDiscing_WaitXccSoConnected),

    TAF_ACT_TBL_ITEM(MSPS_PID_PPPC,
                     ID_PPP_APS_DEACT_CNF,
                     TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitXccSoConnected),

    TAF_ACT_TBL_ITEM(MSPS_PID_PPPC,
                     ID_PPP_APS_DEACT_NTF,
                     TAF_APS_RcvPppDeactInd_CdataDiscing_WaitXccSoConnected),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF,
                     TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitXccSoConnected),
};

/* TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL 动作表 */
TAF_ACT_STRU   g_astTafApsCdataDiscingSubStaWaitIntervalRedialTbl[]   =
{
    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL,
                     TAF_APS_RcvTiRedialIntervalExpired_CdataDiscing_WaitRedial),

    TAF_ACT_TBL_ITEM(MSPS_PID_PPPC,
                     ID_PPP_APS_DEACT_CNF,
                     TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitRedial),

    TAF_ACT_TBL_ITEM(MSPS_PID_PPPC,
                     ID_PPP_APS_DEACT_NTF,
                     TAF_APS_RcvPppDeactInd_CdataDiscing_WaitRedial),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF,
                     TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitRedial),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvPsInterSrvStaChangeInd_CdataDiscing_WaitRedial),
};

TAF_STA_STRU g_astTafApsCdataDiscingStaTbl[] =
{

    TAF_STA_TBL_ITEM( TAF_APS_CDATA_DISCING_SUBSTA_INIT,
                      g_astTafApsCdataDiscingSubStaInitTbl ),

    TAF_STA_TBL_ITEM( TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_DISC_CNF,
                      g_astTafApsCdataDiscingSubStaWaitHsmDecatCnfTbl ),

    TAF_STA_TBL_ITEM( TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_HANGUP_DATA_CALL_CNF,
                      g_astTafApsCdataDiscingSubStaWaitXccHangUpDataCallCnfTbl ),

    TAF_STA_TBL_ITEM( TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF,
                      g_astTafApsCdataDiscingSubStaWaitEhsmPdnDeactCnfTbl ),

    TAF_STA_TBL_ITEM( TAF_APS_CDATA_DISCING_SUBSTA_SUSPEND,
                      g_astTafApsCdataDiscingSubStaSuspendTbl ),

    TAF_STA_TBL_ITEM( TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF,
                      g_astTafApsCdataDiscingSubStaWaitPppDeactCnfTbl ),

    TAF_STA_TBL_ITEM( TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_ORIG_CNF,
                      g_astTafApsCdataDiscingSubStaWaitXccOrigCnfTbl ),

    TAF_STA_TBL_ITEM( TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_ORIG_CNF,
                      g_astTafApsCdataDiscingSubStaWaitHsmOrigCnfTbl ),

    TAF_STA_TBL_ITEM( TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_SO_CONNECTED,
                      g_astTafApsCdataDiscingSubStaWaitXccSoConnectedTbl ),

    TAF_STA_TBL_ITEM( TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL,
                      g_astTafApsCdataDiscingSubStaWaitIntervalRedialTbl ),


};


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_APS_GetCdataDiscingStaTblSize
 功能描述  : 获取CDATA DISCING状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月14日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_GetCdataDiscingStaTblSize( VOS_VOID )
{
    return (sizeof(g_astTafApsCdataDiscingStaTbl)/sizeof(TAF_STA_STRU));
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetCdataDiscingFsmDescAddr
 功能描述  : 获取CDTA DISCING状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_FSM_DESC_STRU:指向状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月14日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
TAF_FSM_DESC_STRU * TAF_APS_GetCdataDiscingFsmDescAddr( VOS_VOID )
{
    return (&g_stTafApsCdataDiscingFsmDesc);
}







#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
