
#include        "MM_Inc.h"
#include        "stdlib.h"
#include        "GmmMmInterface.h"
#include        "NasMmSndOm.h"

#include "NasNvInterface.h"
#include "TafNvInterface.h"

#include "NasMmEcall.h"

#include "MmCmInterface.h"
#include "MmCcInterface.h"
#include "MmSsInterface.h"

#include "NasUtranCtrlInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

extern MM_SUSPEND_MSG_BUF_ST gstMmSuspendMsgQue;
extern MM_TIMER_ST  gstMmTimerSuspend;

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:luojian 107747;检视人:sunshaohua65952;原因:LOG方案设计需要*/
#define    THIS_FILE_ID        PS_FILE_ID_MM_COM_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/

/*****************************************************************************
   2 变量定义
*****************************************************************************/
RRC_TO_MMCC_REL_CAUSE_STRU g_astRrcToMmCcRelCause[] =
{
    {RRC_REL_CAUSE_RR_NORM_EVENT             ,  NAS_MMCM_REL_CAUSE_RR_REL_NORMAL_EVENT},
    {RRC_REL_CAUSE_RR_UNSPEC                 ,  NAS_MMCM_REL_CAUSE_RR_REL_NORMAL_UNSPECIFIED},
    {RRC_REL_CAUSE_RR_PRE_EMPT_REL           ,  NAS_MMCM_REL_CAUSE_RR_REL_PREEMPTIVE_RELEASE},
    {RRC_REL_CAUSE_RR_CONGEST                ,  NAS_MMCM_REL_CAUSE_RR_REL_CONGESTION},
    {RRC_REL_CAUSE_RR_RE_EST_REJ             ,  NAS_MMCM_REL_CAUSE_RR_REL_REEST_REJ},
    {RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST   ,  NAS_MMCM_REL_CAUSE_RR_REL_DIRECTED_SIGNAL_CONN_REEST},
    {RRC_REL_CAUSE_RR_USER_INACT             ,  NAS_MMCM_REL_CAUSE_RR_REL_USER_INACTIVE},
    {RRC_REL_CAUSE_UTRAN_RELEASE             ,  NAS_MMCM_REL_CAUSE_RR_REL_UTRAN_RELEASE},
    {RRC_REL_CAUSE_NAS_REL_SUCCESS           ,  NAS_MMCM_REL_CAUSE_RR_REL_NAS_REL_REQ},
    {RRC_REL_CAUSE_NAS_REL_ABSENT            ,  NAS_MMCM_REL_CAUSE_RR_REL_NAS_REL_REQ},
    {RRC_REL_CAUSE_NAS_ABORT                 ,  NAS_MMCM_REL_CAUSE_RR_REL_NAS_REL_REQ},
    {RRC_REL_CAUSE_NAS_STOP_SETUP            ,  NAS_MMCM_REL_CAUSE_RR_REL_NAS_REL_REQ},
    {RRC_REL_CAUSE_CONN_FAIL                 ,  NAS_MMCM_REL_CAUSE_RR_REL_CONN_FAIL},
    {RRC_REL_CAUSE_NAS_DATA_ABSENT           ,  NAS_MMCM_REL_CAUSE_RR_REL_NAS_DATA_ABSENT},
    {RRC_REL_CAUSE_RRC_ERROR                 ,  NAS_MMCM_REL_CAUSE_RR_REL_RRC_ERROR},
    {RRC_REL_CAUSE_RL_FAILURE                ,  NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE},
    {RRC_REL_CAUSE_GAS_TIMEOUT               ,  NAS_MMCM_REL_CAUSE_RR_REL_NORMAL_UNSPECIFIED},
    {RRC_REL_CAUSE_OTHER_REASON              ,  NAS_MMCM_REL_CAUSE_RR_REL_OTHER_REASON},
    {RRC_REL_CAUSE_NO_RF                     ,  NAS_MMCM_REL_CAUSE_RR_REL_NO_RF},
    {RRC_REL_CAUSE_RLC_ERROR                 ,  NAS_MMCM_REL_CAUSE_RR_REL_RLC_ERR_OR},
    {RRC_REL_CAUSE_CELL_UPDATE_FAIL          ,  NAS_MMCM_REL_CAUSE_RR_REL_CELL_UP_DATE_FAIL},
    {RRC_REL_CAUSE_T314_EXPIRED              ,  NAS_MMCM_REL_CAUSE_RR_REL_T314_EXPIRED},
    {RRC_REL_CAUSE_W_RL_FAIL                 ,  NAS_MMCM_REL_CAUSE_RR_REL_W_RL_FAIL},

    {RRC_REL_CAUSE_G_RL_FAIL                 ,  NAS_MMCM_REL_CAUSE_RR_REL_G_RL_FAIL},
};

EST_RSLT_TO_MMCC_REL_CAUSE_STRU g_astEstRsltToMmCcRelCause[] =
{
    {RRC_EST_SUCCESS                            ,   (VOS_UINT32)NAS_MMCM_REL_CAUSE_BUTT},
    {RRC_EST_PRESENT                            ,   (VOS_UINT32)NAS_MMCM_REL_CAUSE_BUTT},
    {RRC_EST_ESTING                             ,   (VOS_UINT32)NAS_MMCM_REL_CAUSE_BUTT},
    {RRC_EST_DELING                             ,   (VOS_UINT32)NAS_MMCM_REL_CAUSE_BUTT},
    {RRC_EST_RJ_CONGEST                         ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_CONGESTION},
    {RRC_EST_RJ_UNSPEC                          ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_UNSPECIFIED},
    {RRC_EST_ACCESS_BARRED                      ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_ACCESS_BAR},
    {RRC_EST_EST_CONN_FAIL                      ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_EST_CONN_FAIL},
    {RRC_EST_RJ_INTER_RAT                       ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_RJ_INTER_RAT},
    {RRC_EST_IMMEDIATE_ASSIGN_REJECT            ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_IMMEDIATE_ASSIGN_REJECT},
    {RRC_EST_RANDOM_ACCESS_REJECT               ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_RANDOM_ACCESS_REJECT},
    {RRC_EST_PAGING_ACCESS_BARRED               ,   (VOS_UINT32)NAS_MMCM_REL_CAUSE_BUTT},
    {RRC_EST_REGISTER_ACCESS_BARRED             ,   (VOS_UINT32)NAS_MMCM_REL_CAUSE_BUTT},
    {RRC_EST_OTHER_ACCESS_BARRED                ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_ACCESS_BAR},
    {RRC_EST_RJ_T3122_RUNNING                   ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_T3122_RUNING},
    {RRC_EST_RJ_NO_RF                           ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_NO_RF},
    {RRC_EST_RJ_SNW                             ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_LOW_LEVEL_SEARCHING_NETWORK},
    {RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_NO_VALID_INFO},
    {RRC_EST_RJ_RA_FAIL                         ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_RANDOM_ACCESS_SEND_FAIL},
    {RRC_EST_RJ_NOT_ALLOW                       ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_UE_NOT_ALLOW},
    {RRC_EST_RJ_TIME_OUT                        ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_TIME_OUT},
    {RRC_EST_RJ_RA_RESOURCE_FAIL                ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_NO_RANDOM_ACCESS_RESOURCE},
    {RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID        ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_INVALID_IMMEDIATE_ASSIGNED_MSG},
    {RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL    ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_ACTIVE_PHYSICAL_CHANNEL_FAIL},
    {RRC_EST_RJ_AIRMSG_DECODE_ERR               ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_AIR_MSG_DECODE_ERROR},
    {RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT       ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_CURRENT_PROTOCOL_NOT_SUPPORT},
    {RRC_EST_RJ_INVALID_UE_STATE                ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_INVALID_UE_STATE},
    {RRC_EST_RJ_CELL_BAR                        ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_CELL_BARRED},
    {RRC_EST_RJ_FASTRETURN_LTE                  ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_FAST_RETURN_TO_LTE},
    {RRC_EST_RJ_RA_FAIL_NO_VALID_INFO           ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_RA_FAIL_NO_VALID_INFO},
};


NAS_MM_LAU_EST_CNF_TO_T3212_START_SCENE_STRU g_astLauEstCnfRsltToT3212StartScene[] =
{
    {RRC_EST_SUCCESS                            ,   NAS_MM_T3212_START_SCENE_BUTT},
    {RRC_EST_PRESENT                            ,   NAS_MM_T3212_START_SCENE_BUTT},
    {RRC_EST_ESTING                             ,   NAS_MM_T3212_START_SCENE_BUTT},
    {RRC_EST_DELING                             ,   NAS_MM_T3212_START_SCENE_BUTT},
    {RRC_EST_RJ_CONGEST                         ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_UNSPEC                          ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_ACCESS_BARRED                      ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_FAIL_CELL_BAR},
    {RRC_EST_EST_CONN_FAIL                      ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_INTER_RAT                       ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_IMMEDIATE_ASSIGN_REJECT            ,   NAS_MM_T3212_START_SCENE_BUTT},
    {RRC_EST_RANDOM_ACCESS_REJECT               ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_PAGING_ACCESS_BARRED               ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_FAIL_CELL_BAR},
    {RRC_EST_REGISTER_ACCESS_BARRED             ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_FAIL_CELL_BAR},
    {RRC_EST_OTHER_ACCESS_BARRED                ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_FAIL_CELL_BAR},
    {RRC_EST_RJ_T3122_RUNNING                   ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_NO_RF                           ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_SNW                             ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_RA_FAIL                         ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_NOT_ALLOW                       ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_TIME_OUT                        ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_RA_RESOURCE_FAIL                ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID        ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL    ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_AIRMSG_DECODE_ERR               ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT       ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_INVALID_UE_STATE                ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_CELL_BAR                        ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_FAIL_CELL_BAR},
    {RRC_EST_RJ_FASTRETURN_LTE                  ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_RA_FAIL_NO_VALID_INFO           ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
};

NAS_MM_T3212_START_SCENE_CFG_TBL_STRU g_astNasMmT3212StartSceneCfgTbl[] =
{
    /* 当前BIT位,    配置控制场景 */
    {0,             NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},            /* BIT0控制: LAU建联时候失败启动T3212场景 */
    {1,             NAS_MM_T3212_START_SCENE_LAU_RRC_EST_REL_BY_AS},            /* BIT1控制: LAU建联时候被REL启动T3212场景 */
};
#if (FEATURE_ON == FEATURE_LTE)
CSFB_RSLT_TO_MMCC_REL_CAUSE_STRU g_astCsfbRsltToMmCcRelCause[] =
{
    {MM_LMM_CSFB_SERVICE_RSLT_FAILURE                           ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_LMM_LOCAL_FAIL},
    {MM_LMM_CSFB_SERVICE_RSLT_AUTH_REJ                          ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_AUTH_REJ},
    {MM_LMM_CSFB_SERVICE_RSLT_T3417EXT_TIME_OUT                 ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_T3417_TIME_OUT},
    {MM_LMM_CSFB_SERVICE_RSLT_MMC_DETACH_FAIL                   ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_APP_DETACH_SERVICE},
    {MM_LMM_CSFB_SERVICE_RSLT_CN_DETACH_FAIL                    ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_CN_DETACH_SERVICE},
    {MM_LMM_CSFB_SERVICE_RSLT_VERIFY_CSFB_FAIL_FOR_OTHERS       ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_FOR_OTHERS},
    {MM_LMM_CSFB_SERVICE_RSLT_VERIFY_CSFB_FAIL_FOR_EMM_STATE    ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_FOR_EMM_STATE},
    {MM_LMM_CSFB_SERVICE_RSLT_TAU_COLLISION_RSLT_SMS_ONLY       ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_SMS_ONLY},
    {MM_LMM_CSFB_SERVICE_RSLT_TAU_COLLISION_RSLT_PS_ONLY        ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_PS_ONLY},
    {MM_LMM_CSFB_SERVICE_RSLT_TAU_COLLISION_RSLT_ABNORMAL       ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_TAU_COLL_ABNORMAL},
};
#endif
/*lint -save -e958 */


VOS_VOID Mm_ComNasInfoSav (
                       VOS_UINT8    ucAttachState,
                       VOS_UINT8    ucCksnFlg
                       )
{
    /* 更新CS注册状态 */
    if ( g_MmSubLyrShare.MmShare.ucCsAttachState != ucAttachState )
    {
        g_MmSubLyrShare.MmShare.ucCsAttachState = ucAttachState;
        Mm_SndRrNasInfoChgReq(MM_NAS_INFO_ATTACH_FLG);
        if ((g_MmGlobalInfo.usCauseVal != NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE)
          &&(g_MmGlobalInfo.usCauseVal != NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT)
          &&(g_MmGlobalInfo.usCauseVal != NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL)
          &&(g_MmGlobalInfo.usCauseVal != NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL)
          &&(g_MmGlobalInfo.usCauseVal != NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED))
        {
            Mm_SndSmsRegStsInd( g_MmSubLyrShare.MmShare.ucCsAttachState );
        }
    }
    else
    {
        if ((g_MmGlobalInfo.usCauseVal == NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE)
          ||(g_MmGlobalInfo.usCauseVal == NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT)
          ||(g_MmGlobalInfo.usCauseVal == NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL)
          ||(g_MmGlobalInfo.usCauseVal == NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL)
          ||(g_MmGlobalInfo.usCauseVal == NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED))
        {

            Mm_SndSmsRegStsInd(MM_STATUS_ATTACHED);
        }
    }


    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);
    }


    /* 更新CS域安全数据 */
    if ( NAS_MML_GetSimCsSecurityCksn() != ucCksnFlg )
    {
        NAS_MML_SetSimCsSecurityCksn(ucCksnFlg);
        if ( MM_CKSN_INVALID == NAS_MML_GetSimCsSecurityCksn() )
        {
            NAS_MML_InitCsSecurityUmtsCkInvalid();
            NAS_MML_InitCsSecurityUmtsIkInvalid();

            Mm_SndRrNasInfoChgReq(MM_NAS_INFO_DEL_KEY_FLG);
        }
        else
        {
            if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            {
                Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SK_FLG);
            }
        }
    }
    return;                                                                     /* 返回                                     */
}



/*******************************************************************************
  Module:   Mm_ComRandJudge
  Function: 判断RAND是否变化
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   MM_TRUE     RAND变化
            MM_FALSE    RAND不变化
  History:
      1.  张志勇     2003.12.10  新版做成
*******************************************************************************/

VOS_UINT8 Mm_ComRandJudge()
{
    VOS_UINT8                       i;
    VOS_UINT8                   ucRet = MM_FALSE;

    for ( i = 0; i < 16; i++ )
    {
        if ( g_MmGlobalInfo.AuthenCtrlInfo.aucCurRand[i] !=
            g_MmGlobalInfo.AuthenCtrlInfo.aucOldRand[i] )
        {
            ucRet = MM_TRUE;
            break;
        }
    }
    return ucRet;

}

/*******************************************************************************
  Module:   Mm_ComUpdateUsimFileReq
  Function: 更新卡文件
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:
  History:
      1.  hezhijun     2015.02.17  新版做成
*******************************************************************************/
VOS_VOID Mm_ComUpdateUsimFileReq(
    VOS_VOID
)
{
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
    }
    else
    {
        Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
    }

    return;
}


/*******************************************************************************
  Module:   Mm_ComSvcStaJudge
  Function: 判断服务状态是否改变
  Input:    VOS_UINT8 ucSvcStatus
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.16  新版做成
*******************************************************************************/

VOS_VOID Mm_ComSvcStaJudge(VOS_UINT8 ucSvcStatus)
{
    if ( ucSvcStatus != g_MmGlobalInfo.ucMmServiceState )
    {
        g_MmGlobalInfo.ucMmServiceState = ucSvcStatus;
    }
}



VOS_VOID Mm_ComRelAllMmConn(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause
)
{
    VOS_UINT8                                               i;

    VOS_UINT8                                               ucCsSrvFlg;

    ucCsSrvFlg  = VOS_FALSE;


    for ( i = 0; i < 7; i++ )
    {
        /*lint -e701*/
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            aucMMConnExtFlg[0] & (0x01 << i) ) )
        {
            ucCsSrvFlg  = VOS_TRUE;

            /* 存在CC建立的MM连接                       */
            Mm_SndCcRelInd(i, enMmCcRelCause);
        }
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            aucMMConnExtFlg[1] & (0x01 << i) ) )
        {
            ucCsSrvFlg  = VOS_TRUE;

            /* 存在CC建立的MM连接                       */
            Mm_SndCcRelInd(i + 8, enMmCcRelCause);
        }
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            aucMMConnReestFlg[0] & (0x01 << i) ) )
        {
            ucCsSrvFlg  = VOS_TRUE;

            /* 存在CC重建立的MM连接                     */
            Mm_SndCcRelInd(i, enMmCcRelCause);
        }
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            aucMMConnReestFlg[1] & (0x01 << i) ) )
        {
            ucCsSrvFlg  = VOS_TRUE;

            /* 存在CC重建立的MM连接                     */
            Mm_SndCcRelInd(i + 8, enMmCcRelCause);
        }
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            aucMMConnExtFlg[0] & (0x01 << i) ) )
        {

            ucCsSrvFlg  = VOS_TRUE;

            /* 存在SS建立的MM连接                       */
            Mm_SndSsRelInd(i, enMmCcRelCause);
        }
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            aucMMConnExtFlg[1] & (0x01 << i) ) )
        {
            ucCsSrvFlg  = VOS_TRUE;

            /* 存在SS建立的MM连接                       */
            Mm_SndSsRelInd(i + 8, enMmCcRelCause);
        }
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            aucMMConnExtFlg[0] & (0x01 << i) ) )
        {
            ucCsSrvFlg  = VOS_TRUE;

            /* 存在SMS建立的MM连接                      */
            Mm_SndSmsRelInd(i , enMmCcRelCause );
        }
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            aucMMConnExtFlg[1] & (0x01 << i) ) )
        {
            ucCsSrvFlg  = VOS_TRUE;

            /* 存在SMS建立的MM连接                      */
            Mm_SndSmsRelInd(i + 8, enMmCcRelCause );
        }

        /*lint +e701*/
    }


    if ( NO_MM_CONN_ESTING != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI )
    {

        ucCsSrvFlg  = VOS_TRUE;

        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                       enMmCcRelCause);


        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
    }

    if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
    {
        ucCsSrvFlg  = VOS_TRUE;

        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                       enMmCcRelCause);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
    }

    if ( NO_MM_CONN_ESTING != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI )
    {
        ucCsSrvFlg  = VOS_TRUE;

        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI,
                        enMmCcRelCause);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;
    }

    if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
    {
        ucCsSrvFlg  = VOS_TRUE;

        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                        enMmCcRelCause);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;
    }



    if ( NO_MM_CONN_ESTING != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI )
    {
        ucCsSrvFlg  = VOS_TRUE;

        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                        enMmCcRelCause);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
    }

    if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
    {
        ucCsSrvFlg  = VOS_TRUE;

        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                        enMmCcRelCause);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
    }

    /* 将MM连接存在标志设置成没有 */
    g_MmGlobalInfo.ucMMConnEstingPD  = NO_MM_CONN_ESTING;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI       = NO_MM_CONN_ESTING;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI       = NO_MM_CONN_ESTING;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI      = NO_MM_CONN_ESTING;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]     = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]     = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]     = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]     = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]    = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]    = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0]   = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]   = 0;

    NAS_MML_SetCsServiceConnStatusFlg(VOS_FALSE);

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    /* CSFB结束 */

    NAS_MML_SetRelCauseCsfbHighPrioFlg(VOS_FALSE);

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
#endif

    NAS_MML_SetCsEmergencyServiceFlg(VOS_FALSE);

    /* 之前有CS业务存在，释放链接时通知MMC */
    if (VOS_TRUE == ucCsSrvFlg)
    {
        Mm_SndMmcCmSvcInd(VOS_FALSE);
    }

}

VOS_VOID Mm_ComRelAllMmConnExcEmergencyCall(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause
)
{
    VOS_UINT8               i;

    /*lint -e701*/
    for (i = 0; i < 7; i++)
    {
        /* 以下判断仅针对只支持一个CC呼叫的情况，当支持多个CC呼叫功能时，
           并不能判断哪一个呼叫是紧急呼 */
        if ((0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            aucMMConnExtFlg[0] & (0x01 << i)))
            && (MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucEstingCallTypeFlg))
        {
            /* 存在CC重建立的MM连接 */
            Mm_SndCcRelInd(i, enMmCcRelCause);
        }
        /* 以下判断仅针对只支持一个CC呼叫的情况，当支持多个CC呼叫功能时，
           并不能判断哪一个呼叫是紧急呼 */
        if ((0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            aucMMConnExtFlg[1] & (0x01 << i)))
            && (MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucEstingCallTypeFlg))
        {
            /* 存在CC建立的MM连接并且不是紧急呼         */
            Mm_SndCcRelInd(i + 8, enMmCcRelCause);
        }
        /* 以下判断仅针对只支持一个CC呼叫的情况，当支持多个CC呼叫功能时，
           并不能判断哪一个呼叫是紧急呼 */
        if ((0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            aucMMConnReestFlg[0] & (0x01 << i)))
            && (MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucEstingCallTypeFlg))
        {
            /* 存在CC重建立的MM连接                     */
            Mm_SndCcRelInd(i, enMmCcRelCause);
        }
        /* 以下判断仅针对只支持一个CC呼叫的情况，当支持多个CC呼叫功能时，
           并不能判断哪一个呼叫是紧急呼 */
        if ((0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            aucMMConnReestFlg[1] & (0x01 << i)))
            && (MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucEstingCallTypeFlg))
        {
            /* 存在CC重建立的MM连接                     */
            Mm_SndCcRelInd(i + 8, enMmCcRelCause);
        }
        if (0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            aucMMConnExtFlg[0] & (0x01 << i)))
        {                                                                       /* 存在SS建立的MM连接                       */
            Mm_SndSsRelInd(i, enMmCcRelCause);
        }
        if (0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            aucMMConnExtFlg[1] & (0x01 << i)))
        {                                                                       /* 存在SS建立的MM连接                       */
            Mm_SndSsRelInd(i + 8, enMmCcRelCause);
        }
        if (0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            aucMMConnExtFlg[0] & (0x01 << i)))
        {                                                                       /* 存在SMS建立的MM连接                      */
            Mm_SndSmsRelInd(i , enMmCcRelCause);
        }
        if (0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            aucMMConnExtFlg[1] & (0x01 << i)))
        {                                                                       /* 存在SMS建立的MM连接                      */
            Mm_SndSmsRelInd(i + 8, enMmCcRelCause);
        }
    }

    /*lint +e701*/

    /* 以下判断仅针对只支持一个CC呼叫的情况，当支持多个CC呼叫功能时，
       并不能判断哪一个呼叫是紧急呼 */
    if ((NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI)
        && (MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
        ucEstingCallTypeFlg))
    {
        /* 正在建立MM连接且不是紧急呼的MM连接       */
        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                       ucMMConnEstingTI,
                       enMmCcRelCause);
    }
    if (NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI)
    {
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                       ucMMConnEstingTI, enMmCcRelCause);
    }
    if (NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI)
    {
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                        ucMMConnEstingTI,
                        enMmCcRelCause);
    }
    /* 以下判断仅针对只支持一个CC呼叫的情况，当支持多个CC呼叫功能时，
       并不能判断哪一个呼叫是紧急呼 */
    if ((MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        && (MMCC_EMERGENCY_CALL != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
        RcvXXEstReq.ulCallType))
    {
        /* 有缓存的MM连接建立请求                   */
        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                       RcvXXEstReq.ulTransactionId,
                       enMmCcRelCause);                       /* 指示缓存的MM连接建立失败                 */

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
            = MM_FALSE;                                                         /* 清除缓存标志                             */
    }
    if (MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
    {                                                                           /* 有缓存的MM连接建立请求                   */
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                        RcvXXEstReq.ulTransactionId,
                        enMmCcRelCause);                        /* 指示缓存的MM连接建立失败                 */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
            = MM_FALSE;                                                         /* 清除缓存标志                             */
    }
    if (MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
    {                                                                           /* 有缓存的MM连接建立请求                   */
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                       RcvXXEstReq.ulTransactionId, enMmCcRelCause);

        /* 指示缓存的MM连接建立失败                 */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
            = MM_FALSE;                                                         /* 清除缓存标志                             */
    }


    /* 以下判断仅针对只支持一个CC呼叫的情况，当支持多个CC呼叫功能时，
       并不能判断哪一个呼叫是紧急呼 */
    if (MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucEstingCallTypeFlg)
    {
        g_MmGlobalInfo.ucMMConnEstingPD = NO_MM_CONN_ESTING;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
            NO_MM_CONN_ESTING;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0] = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1] = 0;
    }
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
        NO_MM_CONN_ESTING;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
        NO_MM_CONN_ESTING;

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]  = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]  = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] = 0;

    if ( ( MM_CONST_NUM_0 ==
      g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] )
      && ( MM_CONST_NUM_0 ==
      g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] ))
    {
        NAS_MML_SetCsServiceConnStatusFlg(VOS_FALSE);
    }

}



VOS_VOID Mm_ComRejectCause11(VOS_UINT8 ucType)
{


    if (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
    {
        /* 注册被12拒绝不用尝试呼叫重发 */
        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_LA);
    }
    else
    {
        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_OTHER);
    }

    g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;                       /* 设置服务状态                             */

    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);                  /* 设置更新状态                             */

    switch(ucType)
    {
    case MM_ATTACH:
    case MM_RAU:
    case MM_NET_DETACH:
    case MM_SERVICE_REQ:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        MM_CKSN_INVALID
                        );                                                      /* 设置MM信息                               */
        Mm_ComDelLai();                                                         /* 删除LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

        NAS_MML_InitUeIdTmsiInvalid();

        Mm_ComUpdateUsimFileReq();

        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComRejectCause11:WARNING: Type Abnormal");
        break;
    }

    if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                                       /* 向RRC发送RRMM_REL_REQ(CS域)              */
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                                                MM_IDLE_LIMITED_SERVICE;        /* 设置释放RR连接时候进入的状态             */
        Mm_TimerStart(MM_TIMER_T3240);
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRejectCause11:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
    }
    else
    {
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRejectCause11:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
    }
}





VOS_VOID Mm_ComRejectCause13(VOS_UINT8 ucType)
{


    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_OTHER);

    g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;                       /* 设置服务状态                             */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                              */
    /*" \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );                       */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComRejectCause13:INFO: MmServiceState is MM_LIMITED_SERVICE");

    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);                  /* 设置更新状态                             */

    switch(ucType)
    {
    case MM_ATTACH:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        MM_CKSN_INVALID
                        );                                                      /* 设置MM信息                               */
        Mm_ComDelLai();                                                         /* 删除LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

        NAS_MML_InitUeIdTmsiInvalid();

        Mm_ComUpdateUsimFileReq();

        break;
    case MM_RAU:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );                                                      /* 设置MM信息                               */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {/* 3G USIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        }
        else
        {/* 2G SIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        }

        break;
    case MM_NET_DETACH:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        MM_CKSN_INVALID
                        );                                                      /* 设置MM信息                               */
        Mm_ComDelLai();                                                         /* 删除LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

        NAS_MML_InitUeIdTmsiInvalid();

        if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
        }
        else
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
        }

        break;
    case MM_SERVICE_REQ:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );                                                      /* 设置MM信息                               */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {/* 3G USIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        }
        else
        {/* 2G SIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        }

        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComRejectCause13:WARNING: Type Abnormal");
        break;
    }

    if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* 向RRC发送RRMM_REL_REQ(CS域)              */
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                                                MM_IDLE_LIMITED_SERVICE;        /* 设置释放RR连接时候进入的状态             */
        Mm_TimerStart(MM_TIMER_T3240);
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRejectCause13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
    }
    else
    {
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRejectCause13:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
    }
}



VOS_VOID Mm_ComRejectCause15(VOS_UINT8 ucType)
{


    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_OTHER);

    g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;                       /* 设置服务状态                             */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                              */
    /*" \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );                       */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComRejectCause15:INFO: MmServiceState is MM_LIMITED_SERVICE");

    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);                  /* 设置更新状态                             */

    switch(ucType)
    {
    case MM_ATTACH:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        MM_CKSN_INVALID
                        );                                                      /* 设置MM信息                               */
        Mm_ComDelLai();                                                         /* 删除LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

        NAS_MML_InitUeIdTmsiInvalid();
        /* Mm_SndAgentUsimUpdateFileReq(MM_READ_CKIK_FILE_ID); */                    /* 更新SIM卡更新状态                        */
        Mm_ComUpdateUsimFileReq();

        break;
    case MM_RAU:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );                                                      /* 设置MM信息                               */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {/* 3G USIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        }
        else
        {/* 2G SIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        }

        break;
    case MM_NET_DETACH:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        MM_CKSN_INVALID
                        );                                                      /* 设置MM信息                               */
        Mm_ComDelLai();                                                         /* 删除LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

        NAS_MML_InitUeIdTmsiInvalid();
        /* Mm_SndAgentUsimUpdateFileReq(MM_READ_CKIK_FILE_ID);*/                     /* 更新SIM卡更新状态                        */
        if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
        }
        else
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
        }

        break;
    case MM_SERVICE_REQ:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );                                                      /* 设置MM信息                               */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {/* 3G USIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        }
        else
        {/* 2G SIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        }

        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComRejectCause15:WARNING: Type Abnormal");
        break;
    }


    if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* 向RRC发送RRMM_REL_REQ(CS域)              */
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                                                MM_IDLE_LIMITED_SERVICE;        /* 设置释放RR连接时候进入的状态             */
        Mm_TimerStart(MM_TIMER_T3240);
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /*" \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );                     */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRejectCause15:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
    }
    else
    {
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /*" \nMM:STATUS is  MM_IDLE_LIMITED_SERVICE\r " );                      */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRejectCause15:NORMAL: STATUS is  MM_IDLE_LIMITED_SERVICE");
    }
}



VOS_VOID Mm_ComAuthenRcvAuthenRej()
{
    VOS_UINT32                          ulRet;

    ulRet = PS_USIM_SERVICE_NOT_AVAILIABLE;

    Mm_TimerStop(MM_TIMER_T3210);
    Mm_TimerStop(MM_TIMER_T3230);

    Mm_ComRelAllMmConnExcEmergencyCall(NAS_MMCM_REL_CAUSE_RR_REL_AUTH_REJ);

    Mm_ComSaveProcAndCauseVal(MM_AUTH_FAIL_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);            /* 记录流程和原因值                         */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                               /* 设置服务状态                             */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmServiceState is MM_NO_IMSI \r " );  */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComAuthenRcvAuthenRej:INFO: MmServiceState is MM_NO_IMSI");
    g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt = 0;
    g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause = MM_AUTHEN_NO_CAUSE;
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);                  /* 设置更新状态                             */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    Mm_ComNasInfoSav(MM_STATUS_DETACHED, MM_CKSN_INVALID);
    Mm_ComDelLai();                                                             /* 删除LAI                                  */
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;
    NAS_MML_InitUeIdTmsiInvalid();
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                            ~MM_MS_ID_IMSI_PRESENT;
    /* Mm_SndAgentUsimUpdateFileReq(MM_READ_CKIK_FILE_ID);*/                     /* 更新SIM卡更新状态                        */
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);                     /* 更新SIM卡更新状态                        */
    }
    else
    {
        Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);                     /* 更新SIM卡更新状态                        */

        /* DCM MM-18-01-22 要求更新CS:4F20文件，PS更新4F52文件 */
        ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_GSM_ACCESS_IN_USIM);

        if (PS_USIM_SERVICE_AVAILIABLE == ulRet)
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKC_ID);
        }
    }

    Mm_TimerStop(MM_TIMER_T3218);                                               /* 停T3218                                  */
    Mm_ComDelRandRes();                                                         /* 删除RAND和RES                            */

    if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
    {
        Mm_TimerStart(MM_TIMER_T3240);
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComAuthenRcvAuthenRej:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
    }
    else
    {
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComAuthenRcvAuthenRej:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        Mm_ComProcCauseClear();
        /* A32D10964 ==> */
        if (MM_DETACH_NEED_DELAY == g_MmGlobalInfo.ucDetachType)
        {
            Mm_TimerStop(MM_TIMER_PROTECT_DETACH);
            g_MmGlobalInfo.ucDetachType = MM_DETACH_TYPE_BUTT;
            Mm_Cell_S0_E23(VOS_NULL_PTR);
        }
        /* <== A32D10964 */
    }
}




VOS_VOID Mm_ComTmsiReloc()
{
    NAS_MML_LAI_STRU                   *pstCsSuccLai;
    NAS_MML_LAI_STRU                   *pstCurrCampLai = VOS_NULL_PTR;

    pstCurrCampLai = NAS_MML_GetCurrCampLai();

    pstCsSuccLai    = NAS_MML_GetCsLastSuccLai(  );


    pstCsSuccLai->stPlmnId.ulMcc
        = g_MmMsgTmsiReallocCmd.MmIeLAI.IeLai.PlmnId.ulMcc;
    pstCsSuccLai->stPlmnId.ulMnc
        = g_MmMsgTmsiReallocCmd.MmIeLAI.IeLai.PlmnId.ulMnc;
    pstCsSuccLai->aucLac[0] = (g_MmMsgTmsiReallocCmd.MmIeLAI.IeLai.ulLac >> 8) & (0x00FF);
    pstCsSuccLai->aucLac[1] = (g_MmMsgTmsiReallocCmd.MmIeLAI.IeLai.ulLac) & (0x00FF);

    PS_MEM_CPY(pstCurrCampLai, pstCsSuccLai, sizeof(NAS_MML_LAI_STRU));

    if ( MM_MS_ID_IMSI_PRESENT ==
        ( g_MmMsgTmsiReallocCmd.MmIeMobileId.MobileID.ucMsIdFlg &
                                                    MM_MS_ID_IMSI_PRESENT ) )
    {
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_TMSI_PRESENT;         /* 设置TMSI无效                             */

        NAS_MML_InitUeIdTmsiInvalid();

        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |= MM_MS_ID_IMSI_PRESENT;    /* 设置IMSI有效                             */

        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {/* 3G USIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        }
        else
        {/* 2G SIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        }

    }
    else
    {
        if ( MM_MS_ID_TMSI_PRESENT ==

                    ( g_MmMsgTmsiReallocCmd.MmIeMobileId.MobileID.ucMsIdFlg &
                                                MM_MS_ID_TMSI_PRESENT ) )
        {
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |= MM_MS_ID_TMSI_PRESENT;
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMcc = NAS_MML_GetCsLastSuccMcc();
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMnc = NAS_MML_GetCsLastSuccMnc();

            PS_MEM_CPY(NAS_MML_GetUeIdTmsi(),
                       g_MmMsgTmsiReallocCmd.MmIeMobileId.MobileID.aucTmsi,
                       NAS_MML_MAX_TMSI_LEN);
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {/* 3G USIM */
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            }
            else
            {/* 2G SIM */
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            }

        }

    }
    Mm_ComMsgTmsiRelocCpltSnd();                                                /* 发送TMSI REALLOCATION COMPLETE           */
}



VOS_VOID Mm_ComInfo()
{

    Mm_SndMmcInfoInd();
}

/*******************************************************************************
  Module:   Mm_ComIdentity
  Function: IDENTITY过程的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.10  新版做成
*******************************************************************************/

VOS_VOID Mm_ComIdentity()
{
    MM_MSG_ID_RSP_STRU    Msg;

    NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

    switch( g_MmMsgIdReq.MmIeIdType.ucIDType )
    {
    case MM_IE_MI_ID_TYPE_IMSI:
        if ( 0 != ( g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg
            & MM_MS_ID_IMSI_PRESENT ) )
        {
            Msg.MmIeMobileId.MobileID.ucMsIdFlg = MM_MS_ID_IMSI_PRESENT;
        }
        else
        {
            Msg.MmIeMobileId.MobileID.ucMsIdFlg = MM_MS_ID_ABSENT;
        }
        break;
    case MM_IE_MI_ID_TYPE_IMEI:
        Msg.MmIeMobileId.MobileID.ucMsIdFlg = MM_MS_ID_IMEI_PRESENT;
        break;
    case MM_IE_MI_ID_TYPE_IMEISV:
        Msg.MmIeMobileId.MobileID.ucMsIdFlg = MM_MS_ID_IMEISV_PRESENT;
        break;
    case MM_IE_MI_ID_TYPE_TMSI:
        if ( 0 != ( g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg
            & MM_MS_ID_TMSI_PRESENT ) )
        {
            Msg.MmIeMobileId.MobileID.ucMsIdFlg = MM_MS_ID_TMSI_PRESENT;
        }
        else
        {
            Msg.MmIeMobileId.MobileID.ucMsIdFlg = MM_MS_ID_ABSENT;
        }
        break;
    default:
        break;
    }
    Mm_ComMsgIdRspSnd(&Msg);                                                    /* IDENTITY RESPONSE消息                    */

#if (FEATURE_ON == FEATURE_PTM)
    NAS_MM_IDResInfoRecord(g_MmMsgIdReq.MmIeIdType.ucIDType);
#endif

}



VOS_VOID Mm_ComAbortCause6()
{


    Mm_ComRelAllMmConnExcEmergencyCall(NAS_MMCM_REL_CAUSE_CM_SRV_REJ_ILLEGAL_ME);

    Mm_ComSaveProcAndCauseVal(MM_MM_NET_ABORT, NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME);        /* 记录流程和原因值                         */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                               /* 设置服务状态                             */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmServiceState is MM_NO_IMSI \r " );  */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComAbortCause6:INFO: MmServiceState is MM_NO_IMSI");

    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);                  /* 设置更新状态                             */

    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    Mm_ComNasInfoSav(MM_STATUS_DETACHED, MM_CKSN_INVALID);
    Mm_ComDelLai();                                                             /* 删除LAI                                  */
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

    NAS_MML_InitUeIdTmsiInvalid();

    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                            ~MM_MS_ID_IMSI_PRESENT;

    Mm_ComUpdateUsimFileReq();


    g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_NO_IMSI;                   /* 设置释放RR连接时候进入的状态             */
    Mm_TimerStart(MM_TIMER_T3240);
    /* Mm_SndMmcCmSvcRejInd(NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME); */
    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComAbortCause6:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
}



VOS_VOID Mm_ComAbortCause17()
{
    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_CM_SRV_REJ_NETWORK_FAILURE);

    Mm_ComSaveProcAndCauseVal(MM_MM_NET_ABORT, NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE);   /* 记录流程和原因值                         */
    g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_NORMAL_SERVICE;            /* 设置释放RR连接时候进入的状态             */
    Mm_TimerStart(MM_TIMER_T3240);
    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
    /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                              */
    /*" \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );                         */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComAbortCause17:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
}

/*******************************************************************************
  Module:   Mm_ComT3214orT3216Expired
  Function: T3214或者T3216溢出的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.12  新版做成
******************************************************************************/

VOS_VOID Mm_ComT3214orT3216Expired()
{
    Mm_ComAuthMsRej();


}

/*******************************************************************************
  Module:   Mm_ComDelRandRes
  Function: 删除RAND和RES的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  李  彬   2004.01.07   新版做成
      2.  张志勇   2004.10.25   数据存储结构变更对应
*******************************************************************************/

VOS_VOID Mm_ComDelRandRes()
{
    VOS_UINT8                   i;

    g_MmGlobalInfo.AuthenCtrlInfo.ucResFlg = MM_AUTHEN_RES_ABSENT;

    g_MmGlobalInfo.AuthenCtrlInfo.ucSresFlg = MM_AUTHEN_RES_ABSENT;

    /* g_MmGlobalInfo.AuthenCtrlInfo.ulRes = 0; */
    PS_MEM_SET(g_MmGlobalInfo.AuthenCtrlInfo.aucRes, 0, 4);
    g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength = 0;
    /* g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[0] = 0;
       g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[1] = 0;
       g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[2] = 0; */
    PS_MEM_SET(g_MmGlobalInfo.AuthenCtrlInfo.aucExtRes, 0, 12);
    g_MmGlobalInfo.AuthenCtrlInfo.ucRandFlg = MM_AUTHEN_RAND_ABSENT;
    for ( i = 0; i < 16; i ++ )
    {
        g_MmGlobalInfo.AuthenCtrlInfo.aucCurRand[i] = 0;
        g_MmGlobalInfo.AuthenCtrlInfo.aucOldRand[i] = 0;
    }
}

/*******************************************************************************
  Module:   Mm_ComT3218Expired
  Function: T3218溢出的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.12  新版做成
*******************************************************************************/

VOS_VOID Mm_ComT3218Expired()
{
    Mm_TimerStop(MM_TIMER_T3218);
    Mm_ComDelRandRes();

}



VOS_VOID Mm_ComAuthenNoAutn()
{
    MM_MSG_AUTHENTICATION_FAIL_STRU     Msg;
    VOS_INT8                            cVersion;
    VOS_UINT8                           ucAuthFailFlg;

    ucAuthFailFlg   = VOS_FALSE;
    cVersion        = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_CS);

    Msg.MmIeRejCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_GSM_AUT_UNACCEPTABLE;

    Mm_ComMsgAuthFailSnd(&Msg);                                                 /* 发送AUTHENTICATION FAILURE消息           */
    NAS_MM_SndMmcSimAuthFailInfo(NAS_MML_SIM_AUTH_FAIL_GSM_AUT_UNACCEPTABLE);

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_AUTH_FAIL,
                              NAS_MML_REG_FAIL_CAUSE_GSM_AUT_UNACCEPTABLE);

    Mm_TimerStop(MM_TIMER_T3218);                                               /* 停T3218                                  */
    Mm_ComDelRandRes();                                                         /* 删除RAND和RES                            */

    g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt++;

    /* R6版本以后连续三次鉴权失败UE可以认为鉴权失败 */
    if ((PS_PTL_VER_R6  <= cVersion)
     && (MM_CONST_NUM_3 == g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt))
    {
        ucAuthFailFlg = VOS_TRUE;
    }

    /* 此处实现原来参考R5协议连续两次鉴权失败UE可以认为鉴权失败 */
    if ((PS_PTL_VER_R5  >= cVersion)
     && ((MM_CONST_NUM_3   == g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt)
      || (MM_MAC_CODE_FAIL == g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause)))
    {
        ucAuthFailFlg = VOS_TRUE;
    }

    if (VOS_TRUE == ucAuthFailFlg)
    {

        Mm_ComAuthMsRej();

    }
    else
    {
        g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause = MM_MAC_CODE_FAIL;       /* 设置上一次的错误信息                     */
        Mm_TimerStart(MM_TIMER_T3214);
    }
}



VOS_VOID Mm_ComAuthenRcvAuthenReq()
{
    VOS_UINT8                           i;
    MM_MSG_AUTHENTICATION_RSP_STRU      Msg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType   = NAS_MML_GetCurrNetRatType();

    /* 增加 SIM 卡鉴权和 USIM 卡在 GSM 下鉴权 */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus()) /* 卡不存在 */
    {
        NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_WARNING,
                    "Mm_ComAuthenRcvAuthenReq: WARNING: Sim is invalid!");

        /* 此条消息被丢弃, 不作处理，直接返回 */
        return;
    }
    /* 为 SIM 卡或者在 USIM 卡在 GSM 网中的 GSM 鉴权 */
    else if ((NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
          || ((MM_IE_AUTN_ABSENT == g_MmMsgAuthReq.ucAutnFlg)
          && (NAS_MML_NET_RAT_TYPE_GSM == enRatType)))
    {

        MM_GsmAuthProc();

        return;
    }
    else
    {

    }
    /* USIM 卡在 UMTS 网中鉴权，或 USIM 卡在 GSM 网中的 UMTS 鉴权按下面进行处理 */


    if (VOS_TRUE != NAS_MML_GetSimCsRegStatus())
    {                                                                           /* MS不支持UMTS ALGO                        */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComAuthenRcvAuthenReq:WARNING: Not support UMTS ALGO");
        return;
    }
    PS_MEM_SET(&Msg,0,sizeof(MM_MSG_AUTHENTICATION_RSP_STRU));
    Mm_TimerStop(MM_TIMER_T3214);
    Mm_TimerStop(MM_TIMER_T3216);
    PS_MEM_CPY(
                g_MmGlobalInfo.AuthenCtrlInfo.aucCurRand,
                g_MmMsgAuthReq.MmIeRAND.aucRandValue,
                16 * sizeof(VOS_UINT8)
                );

    /* 做3G鉴权，清除2G鉴权标记 */
    NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_FALSE);

    if ( MM_IE_AUTN_PRESENT == g_MmMsgAuthReq.ucAutnFlg )
    {                                                                           /* AUTN存在的场合                           */
        g_MmGlobalInfo.AuthenCtrlInfo.ucAutnLen
            = g_MmMsgAuthReq.MmIeAUTN.ucAutnLen;
        for ( i = 0; i < g_MmMsgAuthReq.MmIeAUTN.ucAutnLen; i++ )
        {
            g_MmGlobalInfo.AuthenCtrlInfo.aucAutn[i]
                = g_MmMsgAuthReq.MmIeAUTN.aucAutn[i];
        }
        if ( MM_AUTHEN_RAND_ABSENT ==  g_MmGlobalInfo.AuthenCtrlInfo.ucRandFlg )
        {
            PS_MEM_CPY(
                        g_MmGlobalInfo.AuthenCtrlInfo.aucOldRand,
                        g_MmGlobalInfo.AuthenCtrlInfo.aucCurRand,
                        16 * sizeof(VOS_UINT8)
                        );
            g_MmGlobalInfo.AuthenCtrlInfo.ucRandFlg = MM_AUTHEN_RAND_PRESENT;   /* 设置RAND存在标识                         */
            /*A32D07740==>*/
            g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat   = MM_AUTHEN_RAND_REPEAT;
            g_MmGlobalInfo.AuthenCtrlInfo.ucLastAuthType = AUTHENTICATION_REQ_UMTS_CHALLENGE;
            /*<==A32D07740*/
            Mm_SndAgentUsimAuthenReq();                                         /* 发送AGENT_USIM_AUTHENTICATION_REQ        */
            Mm_TimerStart(MM_TIMER_PROTECT_AGENT);                              /* 启动保护TIMER                            */
            /* Mm_TimerStart(MM_TIMER_PROTECT); */
        }
        else
        {
            if ( ( MM_FALSE == Mm_ComRandJudge() ) )
            {                                                                   /* RAND相同                                 */
                /* 前两次 RAND 是否相同 */
                if (MM_AUTHEN_RAND_DIFFER == g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat)
                {
                    /* 本次 RAND 与上次相同 */
                    g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat = MM_AUTHEN_RAND_REPEAT;

                    Mm_SndAgentUsimAuthenReq();                                 /* 发送AGENT_USIM_AUTHENTICATION_REQ        */

                    g_MmGlobalInfo.AuthenCtrlInfo.ucLastAuthType = AUTHENTICATION_REQ_UMTS_CHALLENGE;

                    Mm_TimerStart(MM_TIMER_PROTECT_AGENT);                      /* 启动保护TIMER                            */
                }
                /* 前两次 RAND 相同而且 RES 存在，本次鉴权类型与上次相同 */
                else if ((MM_AUTHEN_RES_PRESENT == g_MmGlobalInfo.AuthenCtrlInfo.ucResFlg)
                    && (AUTHENTICATION_REQ_UMTS_CHALLENGE == g_MmGlobalInfo.AuthenCtrlInfo.ucLastAuthType))
                /* if ( MM_AUTHEN_RES_PRESENT ==
                                g_MmGlobalInfo.AuthenCtrlInfo.ucResFlg ) */
                {                                                               /* RES存在的场合                            */

                    /* Msg.MmIeAuthRspPara.aucSgnfcntRES[0] =  */
                    /*    (VOS_UINT8)(g_MmGlobalInfo.AuthenCtrlInfo.ulRes & 0xFF);  */
                    /* Msg.MmIeAuthRspPara.aucSgnfcntRES[1] = */
                    /* (VOS_UINT8)( ( g_MmGlobalInfo.AuthenCtrlInfo.ulRes >> 8 )    */
                    /*                                                & 0xFF);  */
                    /* Msg.MmIeAuthRspPara.aucSgnfcntRES[2] =                   */
                    /* (VOS_UINT8)( ( g_MmGlobalInfo.AuthenCtrlInfo.ulRes >> 16 )   */
                    /*                                                 & 0xFF); */
                    /* Msg.MmIeAuthRspPara.aucSgnfcntRES[3] =                   */
                    /* (VOS_UINT8)( ( g_MmGlobalInfo.AuthenCtrlInfo.ulRes >> 24 )   */
                    /*                                                 & 0xFF); */
                    PS_MEM_CPY(Msg.MmIeAuthRspPara.aucSgnfcntRES,
                                g_MmGlobalInfo.AuthenCtrlInfo.aucRes, 4);
                    if ( MM_CONST_NUM_0 !=
                            g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength )
                    {
                        Msg.ucAutnRspParaExtFlg = MM_IE_AUTN_EXT_PRESENT;
                        Msg.MmIeAuthRspParaExt.ucLength =
                        (VOS_UINT8)(g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength);
                        /* for ( i = 0; i < 4; i ++ )                    */
                        /* {                                              */
                        /*     Msg.MmIeAuthRspParaExt.aucRES[i] =          */
                        /* (VOS_UINT8)((g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[0] >>  */
                        /*                                 ( i * 8 ) ) & 0xFF);  */
                        /*     Msg.MmIeAuthRspParaExt.aucRES[i + 4] =    */
                        /* (VOS_UINT8)((g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[1] >>  */
                        /*                                 ( i * 8 ) ) & 0xFF);  */
                        /*     Msg.MmIeAuthRspParaExt.aucRES[i + 8] =          */
                        /* (VOS_UINT8)((g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[2] >>  */
                        /*                                 ( i * 8 ) ) & 0xFF);   */
                        /* }                                                  */
                        PS_MEM_CPY(Msg.MmIeAuthRspParaExt.aucRES,
                                  g_MmGlobalInfo.AuthenCtrlInfo.aucExtRes, 12);
                    }

                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComAuthenRcvAuthenReq: Send Auth Rsp");
                    NAS_MML_SetSimCsSecurityCksn(g_MmMsgAuthReq.MmIeCKSN.ucCksn);
                    
                    Mm_ComMsgAuthRspSnd(&Msg);                                  /* 发送AUTHENTICATION RESPONSE(RES)         */
                }
                else
                {                                                               /* RES不存在的场合                          */
                    /* Res 是否存在的标志变量在鉴权成功后设置 */
                    /*g_MmGlobalInfo.AuthenCtrlInfo.ucResFlg =
                                                        MM_AUTHEN_RES_PRESENT;*/  /* 设置RES存在的标识                        */

                    Mm_SndAgentUsimAuthenReq();                                 /* 发送AGENT_USIM_AUTHENTICATION_REQ        */

                    g_MmGlobalInfo.AuthenCtrlInfo.ucLastAuthType = AUTHENTICATION_REQ_UMTS_CHALLENGE;

                    Mm_TimerStart(MM_TIMER_PROTECT_AGENT);                      /* 启动保护TIMER                            */
                    /* Mm_TimerStart(MM_TIMER_PROTECT); */
                }
            }
            else
            {                                                                   /* RAND不相同的场合                         */
                PS_MEM_CPY(
                        g_MmGlobalInfo.AuthenCtrlInfo.aucOldRand,
                        g_MmGlobalInfo.AuthenCtrlInfo.aucCurRand,
                        16 * sizeof(VOS_UINT8)
                        );

                /* 本次 RAND 与上次不同，需要清除RES存在标志 */
                g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat   = MM_AUTHEN_RAND_REPEAT;
                g_MmGlobalInfo.AuthenCtrlInfo.ucLastAuthType = AUTHENTICATION_REQ_UMTS_CHALLENGE;
                g_MmGlobalInfo.AuthenCtrlInfo.ucResFlg       = MM_AUTHEN_RES_ABSENT;
                g_MmGlobalInfo.AuthenCtrlInfo.ucSresFlg      = MM_AUTHEN_RES_ABSENT;

                Mm_SndAgentUsimAuthenReq();
                Mm_TimerStart(MM_TIMER_PROTECT_AGENT);
            }
        }
    }
    else
    {
        Mm_ComAuthenNoAutn();
    }
}



VOS_VOID Mm_ComAuthenRcvUsimCnfSuccess()
{
    /* VOS_UINT8                               i;*/
    MM_MSG_AUTHENTICATION_RSP_STRU    Msg;

    VOS_UINT32                          ulRet;

    ulRet = PS_USIM_SERVICE_NOT_AVAILIABLE;

    if ( ( WAIT_FOR_OUTGOING_MM_CONNECTION == g_MmGlobalInfo.ucState ) ||
        ( WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION ==
                                            g_MmGlobalInfo.ucState ) )
    {                                                                           /* 为T3230运行的状态的场合                  */
        Mm_TimerStart(MM_TIMER_T3230);                                          /* 启动T3230                                */
    }
    if ( LOCATION_UPDATING_INITIATED == g_MmGlobalInfo.ucState )
    {
        Mm_TimerStart(MM_TIMER_T3210);                                          /* 启动T3210                                */
    }
    if ( IMSI_DETACH_INITIATED == g_MmGlobalInfo.ucState )
    {
        Mm_TimerStart(MM_TIMER_T3220);                                          /* 启动T3220                                */
    }
    g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt = 0;
    g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause = MM_AUTHEN_NO_CAUSE;


    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {

        /* 调用函数 Mm_SndAgentUsimUpdateFileReq 更新 KC、CKSN */
        Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);
    }
    else /* USIM 卡 */
    {
        /* 更新 USIM 卡 CK IK CKSN */
        Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);

        /* DCM MM-18-01-22 要求更新CS:4F20文件，PS更新4F52文件 */
        ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_GSM_ACCESS_IN_USIM);

        if (PS_USIM_SERVICE_AVAILIABLE == ulRet)
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKC_ID);
        }
    }

    /* 向 AS 发送RRMM_NAS_INFO_CHANGE_REQ */
    Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SK_FLG);

    /* 连续两次 RAND 相同，要起定时器保护 Res、RAND 有效性 */
    if (MM_AUTHEN_RAND_REPEAT == g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat)
    {
        Mm_TimerStop(MM_TIMER_T3218);                                           /* 停止T3218                                */
        Mm_TimerStart(MM_TIMER_T3218);                                          /* 启动T3218                                */
    }


    /*if ( MM_AUTHEN_RES_ABSENT == g_MmGlobalInfo.AuthenCtrlInfo.ucResFlg )*/
    /*{*/
    /*    Mm_SndAgentUsimUpdateFileReq(MM_READ_CKIK_FILE_ID); */                    /* 更新SIM卡CK IK CKSN                      */
    /*    Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SK_FLG);   */                           /* 向RRC发送RRMM_NAS_INFO_CHANGE_REQ        */
    /*}*/
    /*else*/
    /*{*/
    /*    Mm_SndAgentUsimUpdateFileReq(MM_READ_CKIK_FILE_ID);  */                   /* 更新SIM卡CK IK CKSN                      */
    /*    Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SK_FLG);  */                            /* 向RRC发送RRMM_NAS_INFO_CHANGE_REQ        */
    /*     */
    /*    Mm_TimerStop(MM_TIMER_T3218);  */                                         /* 停止T3218                                */
    /*    Mm_TimerStart(MM_TIMER_T3218);  */                                        /* 启动T3218                                */
    /*}                                                                                                                       */

    /* Msg.MmIeAuthRspPara.aucSgnfcntRES[0] =   */
    /*     (VOS_UINT8)(g_MmGlobalInfo.AuthenCtrlInfo.ulRes & 0x000000FF);  */
    /* Msg.MmIeAuthRspPara.aucSgnfcntRES[1] =   */
    /*     (VOS_UINT8)(( g_MmGlobalInfo.AuthenCtrlInfo.ulRes >> 8 ) & 0x000000FF);  */
    /* Msg.MmIeAuthRspPara.aucSgnfcntRES[2] =   */
    /*     (VOS_UINT8)(( g_MmGlobalInfo.AuthenCtrlInfo.ulRes >> 16 ) & 0x000000FF); */
    /* Msg.MmIeAuthRspPara.aucSgnfcntRES[3] = */
    /*     (VOS_UINT8)(( g_MmGlobalInfo.AuthenCtrlInfo.ulRes >> 24 ) & 0x000000FF); */

    PS_MEM_SET(&Msg, 0x0, sizeof(MM_MSG_AUTHENTICATION_RSP_STRU));

    PS_MEM_CPY(Msg.MmIeAuthRspPara.aucSgnfcntRES,
                g_MmGlobalInfo.AuthenCtrlInfo.aucRes, 4);
    if ( MM_CONST_NUM_0 != g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength )
    {
        Msg.ucAutnRspParaExtFlg = MM_IE_AUTN_EXT_PRESENT;
        Msg.MmIeAuthRspParaExt.ucLength =
            (VOS_UINT8)(g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength);
        /* for ( i = 0; i < 4; i ++ )   */
        /* {              */
        /*     Msg.MmIeAuthRspParaExt.aucRES[i] =   */
        /*     (VOS_UINT8)( (g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[0] >>   */
        /*                                             ( i * 8 ) ) & 0x000000FF); */
        /*     Msg.MmIeAuthRspParaExt.aucRES[i + 4] =    */
        /*    (VOS_UINT8)(( g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[1] >>   */
        /*                                            ( i * 8 ) ) & 0x000000FF);*/
        /*    Msg.MmIeAuthRspParaExt.aucRES[i + 8] =   */
        /*    (VOS_UINT8)(( g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[2] >>   */
        /*                                            ( i * 8 ) ) & 0x000000FF);*/
        /* }        */
        PS_MEM_CPY(Msg.MmIeAuthRspParaExt.aucRES,
                    g_MmGlobalInfo.AuthenCtrlInfo.aucExtRes, 12);
    }
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComAuthenRcvUsimCnfSuccess: Return Auth Succ");
    Mm_ComMsgAuthRspSnd(&Msg);                                                  /* 发送AUTHENTICATION RESPONSE(RES)         */

}



VOS_VOID Mm_ComAuthenRcvUsimCnfFail()
{
    MM_MSG_AUTHENTICATION_FAIL_STRU     Msg;
    VOS_INT8                            cVersion;
    VOS_UINT8                           ucAuthFailFlg;

    ucAuthFailFlg   = VOS_FALSE;
    cVersion        = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_CS);

    Mm_TimerStop(MM_TIMER_T3230);                                               /* 停止T3230                                */
    Mm_TimerStop(MM_TIMER_T3220);                                               /* 停止T3220                                */
    Mm_TimerStop(MM_TIMER_T3210);                                               /* 停止T3210                                */
    Mm_TimerStop(MM_TIMER_T3218);                                               /* 停T3218                                  */
    Mm_ComDelRandRes();                                                         /* 删除RAND和RES                            */

    if ( AGENT_AUTH_FAIL_MAC_CODE == g_AgentUsimAuthCnf.ucFailureCause )
    {                                                                           /* 失败的类型为MAC CODE FAIL的场合          */
        Msg.MmIeRejCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_MAC_FAILURE;
        Mm_ComMsgAuthFailSnd(&Msg);                                             /* 发送AUTHENTICATION FAILURE               */

        /* 3GPP.24008 The MS shall deem that the network has failed the authentication check and behave
        as described in subclause 4.3.2.6.1, if any of the following occurs:
        -the timer T3216 expires;
        -the MS detects any combination of the authentication failures: "MAC failure", "invalid SQN",
        and "GSM authentication unacceptable", during three consecutive authentication challenges.
        The authentication challenges shall be considered as consecutive only, if the authentication
        challenges causing the second and third authentication failure are received by the MS, while
        the timer T3214 or T3216 started after the previous authentication failure is running. */
        g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt ++;

        /* R6版本以后连续三次鉴权失败UE可以认为鉴权失败 */
        if ((PS_PTL_VER_R6  <= cVersion)
         && (MM_CONST_NUM_3 == g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt))
        {
            ucAuthFailFlg = VOS_TRUE;
        }

        /* 此处实现原来参考R5协议连续两次鉴权失败UE可以认为鉴权失败 */
        if ((PS_PTL_VER_R5  >= cVersion)
         && ((MM_CONST_NUM_3   == g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt)
          || (MM_MAC_CODE_FAIL == g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause)))
        {
            ucAuthFailFlg = VOS_TRUE;
        }

        if (VOS_TRUE == ucAuthFailFlg)
        {
            Mm_ComAuthMsRej();

        }
        else
        {
            g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause = MM_MAC_CODE_FAIL;
            Mm_TimerStart(MM_TIMER_T3214);
        }
    }
    /* else */
    else if (AGENT_AUTH_FAIL_SQN == g_AgentUsimAuthCnf.ucFailureCause)
    {
        Msg.MmIeRejCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_SYNCH_FAILURE;
        Msg.MmIeAuthFailPara.ucLength =
             g_MmGlobalInfo.AuthenCtrlInfo.ucFailParaLength;

        PS_MEM_CPY(Msg.MmIeAuthFailPara.aucAuthFailPara,
                    g_MmGlobalInfo.AuthenCtrlInfo.aucFailPara, 14);
        Mm_ComMsgAuthFailSnd(&Msg);                                             /* 发送AUTHENTICATION FAILURE               */
        g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt ++;

        /* R6版本以后连续三次鉴权失败UE可以认为鉴权失败 */
        if ((PS_PTL_VER_R6  <= cVersion)
         && (MM_CONST_NUM_3 == g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt))
        {
            ucAuthFailFlg = VOS_TRUE;
        }

        if ((PS_PTL_VER_R5          >= cVersion)
         && ((MM_CONST_NUM_3        == g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt)
          || (MM_SQN_FAIL           == g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause)))
        {
            ucAuthFailFlg = VOS_TRUE;
        }

        if (VOS_TRUE == ucAuthFailFlg)
        {
            Mm_ComAuthMsRej();

        }
        else
        {
            g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause = MM_SQN_FAIL;
            Mm_TimerStart(MM_TIMER_T3216);
        }
    }
    else
    {
        /* 异常处理 */
        Msg.MmIeRejCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR;
        Mm_ComMsgAuthFailSnd(&Msg);

        MM_WARN_LOG(
                   " \nMM:UMTS AUTH RESULT IS NOT EXPECTED!\r " );

    }

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_AUTH_FAIL,
                              Msg.MmIeRejCause.ucRejCause);

}


/*******************************************************************************
  Module:   Mm_ComAuthenRcvUsimCnf
  Function: 收到USIM发来的AGENT_USIM_AUTHENTICATION_CNF的处理
  Input:    VOS_VOID*   pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.10  新版做成
      2.  张志勇     2005.01.27  007037 for MM
*******************************************************************************/

VOS_VOID Mm_ComAuthenRcvUsimCnf()
{
    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);                                       /* 停止保护TIMER                            */
    /* Mm_TimerStop(MM_TIMER_PROTECT); */
    if ( AGENT_AUTH_RST_SUCCESS == g_AgentUsimAuthCnf.ucCheckRst )
    {                                                                           /* USIM的结果是否成功                       */
        Mm_ComAuthenRcvUsimCnfSuccess();
    }
    else
    {
        Mm_ComAuthenRcvUsimCnfFail();
    }
}



VOS_VOID Mm_ComRejectCause4()
{
    g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;                  /* 设置服务状态                             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComRejectCause4:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

    g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;

    Mm_ComNasInfoSav(
                    MM_STATUS_DETACHED,
                    MM_CKSN_INVALID
                    );
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;       /* 清除标志位                               */

    NAS_MML_InitUeIdTmsiInvalid();

    Mm_ComDelLai();                                                             /* 删除LAI                                  */
    Mm_ComUpdateUsimFileReq();


    g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_ATTEMPTING_TO_UPDATE;      /* 设置释放RR连接时候进入的状态             */
    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
    Mm_TimerStart(MM_TIMER_T3240);
    Mm_ComSaveProcAndCauseVal(
                                MM_MM_CONN_PROC,
                                NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR
                             );                                                 /* 记录流程和原因值                         */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRejectCause4:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
}



VOS_VOID Mm_ComRejectCause6()
{
    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_CM_SRV_REJ_ILLEGAL_ME);

    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                               /* 设置服务状态                             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComRejectCause6:INFO: MmServiceState is MM_NO_IMSI");
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);                  /* 设置更新状态                             */

    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;       /* 清除标志位                               */

    NAS_MML_InitUeIdTmsiInvalid();

    Mm_ComDelLai();                                                             /* 删除LAI                                  */
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                            ~MM_MS_ID_IMSI_PRESENT;
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    Mm_ComNasInfoSav(MM_STATUS_DETACHED, MM_CKSN_INVALID);

    Mm_ComUpdateUsimFileReq();

    g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_NO_IMSI;                   /* 设置释放RR连接时候进入的状态             */
    Mm_TimerStart(MM_TIMER_T3240);
    Mm_ComSaveProcAndCauseVal(
                                MM_MM_CONN_PROC,
                                NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME
                             );                                                 /* 记录流程和原因值                         */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRejectCause6:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
}

/***********************************************************************
 *  MODULE   : Mm_T3240Expire
 *  FUNCTION : T3240溢出
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      03-12-11      新版作成
       2.  s46746     05-11-24      修改
 ************************************************************************/
VOS_VOID Mm_T3240Expire(
                        VOS_VOID
                    )
{
    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    Mm_TimerStop(MM_TIMER_T3240);
    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                       /* 记录迁移之前的状态                       */

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_T3240_TIMEOUT,
                              NAS_MML_REG_FAIL_CAUSE_NULL);

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    /*Mm_SndRrAbortReq(RRC_ABORT_CS_SIGN_CONN); */                                  /* 向RRC发送RRMM_ABORT_REQ(CS域)            */

    /* if ( MM_LU_PROC != g_MmGlobalInfo.ucProc ) */
    /* {                            */                                          /* 如果不是LU流程                           */
    /*     Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);  */                         /* 通知MMC，CS域的业务已经停止              */
    /* } */
    Mm_TimerStart(MM_TIMER_T3240);
    return;
}


VOS_VOID Mm_T3230Expire(
                        VOS_VOID
                    )
 {
    VOS_UINT8   i = 0;                                                              /* 循环计数变量                             */

    Mm_TimerStop(MM_TIMER_T3230);

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);

    if ( WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF != g_MmGlobalInfo.ucState )
    {                                                                           /* 不是重建过程                             */
        switch ( g_MmGlobalInfo.ucMMConnEstingPD )
        {                                                                       /* 确定是哪个PD建立的MM连接                 */
        case MM_IE_PD_CALL_CONTROL:

            /* CC要求建立的MM连接                       */
            Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                ucMMConnEstingTI, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_T3230_TIMER_OUT);            /* 通知CC,MM连接建立失败                    */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI
                = NO_MM_CONN_ESTING;                                            /* 清除正在建立MM连接的标志                 */
            break;
        case MM_IE_PD_NON_CALL_RLT_SS_MSG:                                      /* SS要求建立的MM连接                       */
            Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_T3230_TIMER_OUT);

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI
                = NO_MM_CONN_ESTING;                                            /* 清除正在建立MM连接的标志                 */
            break;
        case MM_IE_PD_SMS_MSG:                                                  /* SMS要求建立的MM连接                      */
            Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                ucMMConnEstingTI, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_T3230_TIMER_OUT);              /* 通知SMS,MM连接建立失败                   */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                = NO_MM_CONN_ESTING;                                            /* 清除正在建立MM连接的标志                 */
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_T3230Expire:WARNING: g_MmGlobalInfo.ucMMConnEstingPD Abnormal");
            break;
        }
    }
    g_MmGlobalInfo.ucMMConnEstingPD = NO_MM_CONN_ESTING;                        /* 设置没有正在建立的连接                   */
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
        NO_MM_CONN_ESTING;                                                      /* 清除正在建立的MM连接的标志               */
    if ( ( MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] )
        && ( MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] )
        && ( MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] )
        && ( MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] )
        && ( MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] )
        && ( MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] ) )
    {                                                                           /* 没有MM连接存在                           */
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
            g_MmGlobalInfo.ucStaOfRcvXXEstReq;                                  /* 记录要进入的状态                         */
        Mm_ComSaveProcAndCauseVal(
                                MM_MM_CONN_PROC,
                                NAS_MML_REG_FAIL_CAUSE_NULL
                             );                                                 /* 记录流程和原因值                         */

        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );                 */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_T3230Expire:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
        Mm_TimerStart( MM_TIMER_T3240 );                                        /* 启动TIMER3240                            */
    }
    else if ( WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF ==
        g_MmGlobalInfo.ucState )
    {                                                                           /* 重建过程                                 */
        for ( i = 0; i < MM_CONST_NUM_7; i++ )
        {                                                                       /* 重建的MM连接                             */
            /*lint -e701*/
            if ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                & ( 0x01 << i ) ) )
            {
                /* 该TI的MM连接失效                         */
                Mm_SndCcRelInd( i, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_T3230_TIMER_OUT);           /* 通知CC,MM连接建立失败                    */
            }
            if ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                & ( 0x01 << i ) ) )
            {
                /* 该TI的MM连接失效                         */
                Mm_SndCcRelInd( ( i + 8 ),
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_T3230_TIMER_OUT);                          /* 通知CC,MM连接建立失败                    */
            }
            /*lint +e701*/
        }
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] = 0;    /* 清除标志位                               */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] = 0;    /* 清除标志位                               */
        Mm_ComSaveProcAndCauseVal(
                                MM_MM_CONN_PROC,
                                NAS_MML_REG_FAIL_CAUSE_NULL
                             );                                                 /* 记录流程和原因值                         */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /* " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );                    */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_T3230Expire:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
            g_MmGlobalInfo.ucStaOfRcvXXEstReq;                                  /* WAIT_FOR_NETWORK_COMMAND之后进入的状态   */
        Mm_TimerStart( MM_TIMER_T3240 );                                        /* 启动TIMER3240                            */
    }
    else
    {                                                                           /* 不是重建并且不是建立第一条MM连接         */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /* " \nMM:STATUS is  MM_CONNECTION_ACTIVE\r " );                        */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_T3230Expire:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn( MM_FALSE );                                     /* 检查是否有保留的需要建立的MM连接         */
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();


    return;
}


VOS_VOID Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE_CC_EST_Exist(VOS_UINT8   ucLUFlg)
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                               /* 要发送的CM SERVICE REQ消息               */
    VOS_UINT16                  usMsgSize = 0;                          /* 消息长度,以字节为单位                    */
    VOS_UINT8                  *pucCmSvcReq = 0;                        /* 要发送的CM SERVICE REQ消息指针           */

    g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;     /* 记录收到建立请求时的状态                 */
    g_MmCcEstReq.ulCallType           = g_MmGlobalInfo.
        ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType;       /* 设置呼叫类型                             */
    g_MmCcEstReq.ulTransactionId      = g_MmGlobalInfo.
        ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId;  /* 设置呼叫TI                               */
    if ( MMCC_MO_NORMAL_CALL ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.
        ulCallType )
    {                                                               /* 正常呼叫                                 */
        Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_MO_CALL_EST,
            MM_FALSE, &CmSvcReq);                                   /* 填充CM SERVICE REQUEST结构体             */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
        ucEstingCallTypeFlg = MM_FALSE;                             /* 正常呼叫                                 */
    }
    else
    {                                                               /* 紧急呼叫                                 */
        Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_EMG_CALL_EST,
            MM_FALSE, &CmSvcReq);                                   /* 填充CM SERVICE REQUEST结构体             */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
        ucEstingCallTypeFlg = MM_TRUE;                              /* 紧急呼叫                                 */
    }
    pucCmSvcReq =
        Mm_ComMsgCmSvcReqOfRrEstReq( &CmSvcReq, &usMsgSize );       /* 填充CM SERVICE REQUEST 消息              */
    if ( VOS_NULL_PTR == pucCmSvcReq )
    {                                                               /* 消息制作失败                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComCheckDelayMmConn:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
        return;                                                     /* 返回                                     */
    }
    else
    {                                                               /* 消息制作成功                             */
        if ( MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType )
        {                                                           /* 正常呼叫                                 */
            Mm_SndRrEstReq( RRC_EST_CAUSE_ORIGIN_CONVERSAT_CALL,
                MM_FALSE,
                usMsgSize, pucCmSvcReq );                           /* 发送消息                                 */
        }
        else
        {                                                           /* 紧急呼叫                                 */
            Mm_SndRrEstReq( RRC_EST_CAUSE_EMERGENCY_CALL, MM_FALSE,
                usMsgSize, pucCmSvcReq );                           /* 发送消息                                 */
        }
        MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq );             /* 释放CM SERVICE REQUEST 消息结构体        */
        if ( MM_TRUE == ucLUFlg )
        {
            /* 是LU后调用该函数                         */
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                    /* 通知MMC，CS域的业务已经启动              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        }
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucMMConnEstingTI =
            (VOS_UINT8)g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            RcvXXEstReq.ulTransactionId;                            /* 记录正在建立的MM连接                     */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucRat = NAS_MML_GetCurrNetRatType();
        g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_CALL_CONTROL;    /* 记录正在建立的MM连接的PD                 */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;       /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComCheckDelayMmConn:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                 /* 启动保护TIMER                            */
    }

    return;
}


VOS_VOID Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE_SS_EST_Exist(VOS_VOID)
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                               /* 要发送的CM SERVICE REQ消息               */
    VOS_UINT16                  usMsgSize = 0;                          /* 消息长度,以字节为单位                    */
    VOS_UINT8                  *pucCmSvcReq = 0;                        /* 要发送的CM SERVICE REQ消息指针           */

    g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;     /* 记录收到建立请求时的状态                 */
    if ( ( MM_CONST_NUM_8 >
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.
        ulTransactionId )
        || ( MM_CONST_NUM_14 <
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.
        ulTransactionId ) )
    {                                                               /* TI不合法                                 */
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
    }
    else
    {
        Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SS_ACT, MM_FALSE,
            &CmSvcReq);                                             /* 填充CM SERVICE REQUEST结构体             */
        pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &CmSvcReq,
            &usMsgSize );                                           /* 填充CM SERVICE REQUEST 消息              */
        if ( VOS_NULL_PTR == pucCmSvcReq )
        {                                                           /* 消息制作失败                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComCheckDelayMmConn:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
            return;                                                 /* 返回                                     */
        }
        else
        {                                                           /* 消息制作成功                             */
            Mm_SndRrEstReq(
                RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL,
                MM_FALSE, usMsgSize, pucCmSvcReq );                 /* 发送消息                                 */
            MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq );         /* 释放CM SERVICE REQUEST 消息结构体        */
        }
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            ucMMConnEstingTI =
            (VOS_UINT8)g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            RcvXXEstReq.ulTransactionId;                            /* 记录正在建立的MM连接的TI                 */
        g_MmGlobalInfo.ucMMConnEstingPD =
            MM_IE_PD_NON_CALL_RLT_SS_MSG;                           /* 记录正在建立的MM连接的PD                 */
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                 /* 启动保护TIMER                            */

        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                        /* 通知MMC，CS域的业务已经启动              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;         /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComCheckDelayMmConn:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
    }

    return;
}


VOS_VOID Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE_SMS_EST_Exist(VOS_VOID)
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                               /* 要发送的CM SERVICE REQ消息               */
    VOS_UINT16                  usMsgSize = 0;                          /* 消息长度,以字节为单位                    */
    VOS_UINT8                  *pucCmSvcReq = 0;                        /* 要发送的CM SERVICE REQ消息指针           */

    g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;
    if ( ( MM_CONST_NUM_8 >
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
        ulTransactionId )
        || ( MM_CONST_NUM_14 <
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
        ulTransactionId ) )
    {                                                               /* TI不合法                                 */
        Mm_SndSmsRelInd( g_MmGlobalInfo.
            ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
            ulTransactionId,
            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                        /* 通知SMS建立失败                          */
    }
    else
    {                                                               /* TI合法                                   */
        Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SMS, MM_FALSE,
            &CmSvcReq);                                             /* 填充CM SERVICE REQUEST结构体             */
        pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &CmSvcReq,
            &usMsgSize );                                           /* 填充CM SERVICE REQUEST 消息              */
        if ( VOS_NULL_PTR == pucCmSvcReq )
        {                                                           /* 消息制作失败                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, ":WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
            return;                                                 /* 返回                                     */
        }
        else
        {                                                           /* 消息制作成功                             */
            Mm_SndRrEstReq(
               RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL,
               MM_FALSE,
               usMsgSize, pucCmSvcReq );                            /* 发送消息                                 */
            MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq );          /* 释放CM SERVICE REQUEST 消息结构体        */
        }
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            ucMMConnEstingTI =
            (VOS_UINT8)g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            RcvXXEstReq.ulTransactionId;                            /* 记录正在建立的MM连接的TI                 */
        g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_SMS_MSG;         /* 记录正在建立的MM连接的PD                 */
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                 /* 启动保护TIMER                            */

        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                        /* 通知MMC，CS域的业务已经启动              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;         /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComCheckDelayMmConn:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
    }

    return;
}


VOS_VOID Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE(VOS_UINT8   ucLUFlg)
{
    RRMM_PAGING_IND_STRU                stWPagingMsg;
    GRRMM_PAGING_IND_ST                 stGPagingMsg;

    if ( MM_TRUE ==
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
    {                                                                   /* 有等待的CC触发的需要建立的MM连接         */
        Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE_CC_EST_Exist(ucLUFlg);
    }
    else if ( MM_TRUE ==
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
    {
        Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE_SS_EST_Exist();
    }
    else if ( MM_TRUE ==
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
    {
        Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE_SMS_EST_Exist();
    }
    else if (MM_PAGING_PLMNSRCH_TRUE == g_MmSubLyrShare.MmShare.ucPagingPlmnSrch)
    {
        g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;
        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            Mm_MakeGPagingInd(&stGPagingMsg);
            /*lint -e961*/
            gaMmStateTable[30][g_MmGlobalInfo.ucState](&stGPagingMsg);
            /*lint +e961*/
        }
        else
        {
            Mm_MakeWPagingInd(&stWPagingMsg);
            /*lint -e961*/
            gaMmStateTable[30][g_MmGlobalInfo.ucState](&stWPagingMsg);
            /*lint +e961*/
        }
    }
    else
    {                                                                   /* 没有等待的CC要求建立的MM连接             */
        if ( MM_FALSE == ucLUFlg )
        {
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                    /* 通知MMC，CS域的业务已经停止              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        if ((VOS_TRUE == NAS_MM_IsDisableGprsCombineAttach())
         && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus))
        {
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();
    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}


VOS_VOID Mm_ComCheckDelayMmConn_MM_IDLE_ATTEMPTING_TO_UPDATE(VOS_UINT8   ucLUFlg)
{
    MM_MSG_CM_SVC_REQ_STRU   CmSvcReq;                                              /* 要发送的CM SERVICE REQ消息               */
    VOS_UINT16               usMsgSize = 0;                                         /* 消息长度,以字节为单位                    */
    VOS_UINT8               *pucCmSvcReq = 0;                                       /* 要发送的CM SERVICE REQ消息指针           */

    RRMM_PAGING_IND_STRU     stWPagingMsg;
    GRRMM_PAGING_IND_ST      stGPagingMsg;

    if ( MM_TRUE ==
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
    {                                                                   /* 由等待的CC触发的需要建立的MM连接         */
        if ( MMCC_EMERGENCY_CALL ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.
            ulCallType )
        {                                                               /* 是紧急呼叫                               */
            g_MmCcEstReq.ulCallType           = g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType;   /* 设置呼叫类型                             */
            g_MmCcEstReq.ulTransactionId      = g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.
                ulTransactionId;                                        /* 设置呼叫TI                               */
            g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState; /* 记录收到建立请求时的状态                 */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_EMG_CALL_EST,
                MM_FALSE, &CmSvcReq);                                   /* 填充CM SERVICE REQUEST结构体             */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucEstingCallTypeFlg = MM_TRUE;                              /* 紧急呼叫                                 */
            pucCmSvcReq =
                Mm_ComMsgCmSvcReqOfRrEstReq( &CmSvcReq, &usMsgSize );   /* 填充CM SERVICE REQUEST 消息              */
            if ( VOS_NULL_PTR == pucCmSvcReq )
            {                                                           /* 消息制作失败                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComCheckDelayMmConn:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
                return;                                                 /* 返回                                     */
            }
            else
            {                                                           /* 消息制作成功                             */
                if ( MM_TRUE == ucLUFlg )
                {                                                       /* 是LU后调用该函数                         */
                    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                /* 通知MMC，CS域的业务已经启动              */
                    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
                }
                Mm_SndRrEstReq( RRC_EST_CAUSE_EMERGENCY_CALL, MM_FALSE,
                    usMsgSize, pucCmSvcReq );                           /* 发送消息                                 */
                Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);             /* 启动保护TIMER                            */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    ucMMConnEstingTI =
                    (VOS_UINT8)g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    RcvXXEstReq.ulTransactionId;                        /* 记录正在建立的MM连接                     */
                g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_CALL_CONTROL;/* 记录正在建立的MM连接的PD                 */
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;   /* 记录迁移之前的状态                       */
                Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComCheckDelayMmConn:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
            }
        }
        else
        {
            /* 是正常呼叫                               */
            Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_ATTEMPTING_TO_UPDATE);                      /* 通知CC指定建立的MM连接建立失败           */

            if ( MM_FALSE == ucLUFlg )
            {
                Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                /* 通知MMC，CS域的业务已经停止              */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
        }
    }
    else if ( MM_TRUE ==
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
    {
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_ATTEMPTING_TO_UPDATE);
    }
    else if ( MM_TRUE ==
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
    {
        Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_ATTEMPTING_TO_UPDATE);                        /* 通知SMS建立失败                          */
    }
    else if (MM_PAGING_PLMNSRCH_TRUE == g_MmSubLyrShare.MmShare.ucPagingPlmnSrch)
    {
        g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;
        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            Mm_MakeGPagingInd(&stGPagingMsg);
            /*lint -e961*/
            gaMmStateTable[30][g_MmGlobalInfo.ucState](&stGPagingMsg);
            /*lint +e961*/
        }
        else
        {
            Mm_MakeWPagingInd(&stWPagingMsg);
            /*lint -e961*/
            gaMmStateTable[30][g_MmGlobalInfo.ucState](&stWPagingMsg);
            /*lint +e961*/
        }
    }
    else
    {                                                                   /* 没有等待的CC要求建立的MM连接             */
        if ( MM_FALSE == ucLUFlg )
        {
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                    /* 通知MMC，CS域的业务已经停止              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        if ((VOS_TRUE == NAS_MM_IsDisableGprsCombineAttach())
         && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
         && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3213].ucTimerStatus))
        {
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
    }

    return;
}


VOS_VOID Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE_CC_EST_Exist(VOS_VOID)
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                                       /* 要发送的CM SERVICE REQ消息               */

    PS_MEM_SET(&CmSvcReq, 0x00, sizeof(CmSvcReq));

    g_MmCcEstReq.ulCallType           = g_MmGlobalInfo.
        ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType;       /* 设置呼叫类型                             */
    g_MmCcEstReq.ulTransactionId      = g_MmGlobalInfo.
        ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId;  /* 设置呼叫TI                               */
    /*lint -e701*/
    if ( ( MM_TRUE == Mm_ComJudgeLimitSvc( ) )
        ||( MM_CONST_NUM_0 !=
        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
        aucMMConnExtFlg[1] & ( 0x01 <<
        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.
        ulTransactionId - 8 ) ) ) )
        )
    {
        /* 要求建立的MM连接已经存在或受限服务状态   */
        Mm_SndCcRelInd( g_MmGlobalInfo.
            ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.
            ulTransactionId,
            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                      /* 通知CC指定建立的MM连接建立失败           */
    }
    /*lint +e701*/
    else
    {                                                               /* 要求建立的MM连接不存在                   */
        /* ==>A32D12640 */
        /*
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;
        */
                                                                    /* 记录收到建立请求时的状态                 */
        if ( MMCC_MO_NORMAL_CALL ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            RcvXXEstReq.ulCallType )
        {                                                           /* 主叫正常呼叫                             */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_MO_CALL_EST,
                MM_FALSE, &CmSvcReq);                               /* 填充CM SERVICE REQUEST结构体             */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucEstingCallTypeFlg = MM_FALSE;                         /* 正常呼叫                                 */
        }
        else if ( MMCC_EMERGENCY_CALL ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            RcvXXEstReq.ulCallType )
        {                                                           /* 主叫紧急呼叫                             */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_EMG_CALL_EST,
                MM_FALSE, &CmSvcReq);                               /* 填充CM SERVICE REQUEST结构体             */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                ucEstingCallTypeFlg = MM_TRUE;                      /* 紧急呼叫                                 */
        }
        else
        {
        }
        Mm_ComMsgCmSvcReqSnd(&CmSvcReq);                            /* 向网侧发送建立MM连接的请求               */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucMMConnEstingTI = (VOS_UINT8)g_MmGlobalInfo.
            ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq
            .ulTransactionId;                                       /* 记录正在建立的MM连接                     */
        g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_CALL_CONTROL;    /* 记录正在建立的MM连接的PD                 */
        Mm_TimerStart(MM_TIMER_T3230);                              /* 启动TIMER3230                            */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;         /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComCheckDelayMmConn:NORMAL: STATUS is WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
    }

    return;
}


VOS_VOID Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE_SS_EST_Exist(VOS_VOID)
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                                       /* 要发送的CM SERVICE REQ消息               */

    if ( ( MM_TRUE == Mm_ComJudgeLimitSvc( ) )
        ||(8 > g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                    .RcvXXEstReq.ulTransactionId)
        ||(14 < g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                    .RcvXXEstReq.ulTransactionId)
        )
    {
        /* TI不合法或受限服务状态   */

        /* 通知SS指定建立的MM连接建立失败           */
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
    }
    /*lint -e701*/
    else if (MM_CONST_NUM_0 !=
            ( (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1])
              &( 0x01 << ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                    .RcvXXEstReq.ulTransactionId - 8 ) ) ))
    /*lint +e701*/
    {
        /* 要求建立的MM连接已经存在                 */

        /* 记录收到建立请求时的状态                 */
        /* ==>A32D12640 */
        /*
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;
        */
        /* 该MM连接建立成功                         */
        Mm_SndSsEstCnf(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                    .RcvXXEstReq.ulTransactionId,MMSS_EST_SUCCESS);
    }
    else
    {
        /* 填充CM SERVICE REQUEST结构体             */
        Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SS_ACT, MM_FALSE, &CmSvcReq);
        /* 向网侧发送建立MM连接的请求               */
        Mm_ComMsgCmSvcReqSnd( &CmSvcReq );
        /* 记录正在建立的MM连接的TI                 */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
            (VOS_UINT8)(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                    .RcvXXEstReq.ulTransactionId);
        /* 记录正在建立的MM连接的PD                 */
        g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_NON_CALL_RLT_SS_MSG;
        /* 启动TIMER3230                            */
        Mm_TimerStart(MM_TIMER_T3230);
        /* 记录迁移之前的状态                       */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
        /* 状态迁移                                 */
        Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComCheckDelayMmConn:NORMAL: STATUS is WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
    }

    return;
}


VOS_VOID Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE_SMS_EST_Exist(VOS_VOID)
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                                       /* 要发送的CM SERVICE REQ消息               */

    if ( ( MM_TRUE == Mm_ComJudgeLimitSvc( ) )
        ||(8 > g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                    .RcvXXEstReq.ulTransactionId)
        ||(14 < g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                    .RcvXXEstReq.ulTransactionId)
        )
    {
        /* TI不合法或受限服务状态   */

        /* 通知SMS指定建立的MM连接建立失败           */
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                    .RcvXXEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
    }
    /*lint -e701*/
    else if (MM_CONST_NUM_0 !=
            ( (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1])
              &( 0x01 << ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                    .RcvXXEstReq.ulTransactionId - 8 ) ) ))
    /*lint +e701*/
    {
        /* 要求建立的MM连接已经存在                 */

        /* 记录收到建立请求时的状态                 */
        /* ==>A32D12640 */
        /*
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;
        */
        /* 该MM连接建立成功                         */
        Mm_SndSmsEstCnf(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                    .RcvXXEstReq.ulTransactionId);
    }
    else
    {
        /* 填充CM SERVICE REQUEST结构体             */
        Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SMS, MM_FALSE, &CmSvcReq);
        /* 向网侧发送建立MM连接的请求               */
        Mm_ComMsgCmSvcReqSnd( &CmSvcReq );
        /* 记录正在建立的MM连接的TI                 */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
            (VOS_UINT8)(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                    .RcvXXEstReq.ulTransactionId);
        /* 记录正在建立的MM连接的PD                 */
        g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_SMS_MSG;
        /* 启动TIMER3230                            */
        Mm_TimerStart(MM_TIMER_T3230);
        /* 记录迁移之前的状态                       */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
        /* 状态迁移                                 */
        Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComCheckDelayMmConn:NORMAL: STATUS is WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE
 *  FUNCTION : Mm_ComCheckDelayMmConn函数降复杂度: MM_CONNECTION_ACTIVE 状态处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
 ************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE(VOS_VOID)
{
    if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
    {                                                                   /* 有等待的CC触发的需要建立的MM连接         */
        Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE_CC_EST_Exist();
    }
    else if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
    {
        /* 有等待的SS触发的需要建立的MM连接         */
        Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE_SS_EST_Exist();
    }
    else if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
    {
        /* 有等待的SMS触发的需要建立的MM连接         */
        Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE_SMS_EST_Exist();
    }
    else
    {
    }

    return;
}


VOS_VOID Mm_ComCheckDelayMmConn_OtherStateHandling_CC(
    VOS_UINT8                           ucLUFlg
)
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                                       /* 要发送的CM SERVICE REQ消息               */
    VOS_UINT16                  usMsgSize = 0;                                  /* 消息长度,以字节为单位                    */
    VOS_UINT8                  *pucCmSvcReq = 0;                                /* 要发送的CM SERVICE REQ消息指针           */

    if ( MMCC_EMERGENCY_CALL ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
        RcvXXEstReq.ulCallType )
    {                                                               /* 是紧急呼叫                               */
        g_MmCcEstReq.ulCallType           = g_MmGlobalInfo.
            ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType;   /* 设置呼叫类型                             */
        g_MmCcEstReq.ulTransactionId      = g_MmGlobalInfo.
            ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.
            ulTransactionId;                                        /* 设置呼叫TI                               */
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState; /* 记录收到建立请求时的状态                 */
        Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_EMG_CALL_EST,
            MM_FALSE, &CmSvcReq);                                   /* 填充CM SERVICE REQUEST结构体             */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucEstingCallTypeFlg = MM_TRUE;                          /* 紧急呼叫                                 */
        pucCmSvcReq =
            Mm_ComMsgCmSvcReqOfRrEstReq( &CmSvcReq, &usMsgSize );   /* 填充CM SERVICE REQUEST 消息              */
        if ( VOS_NULL_PTR == pucCmSvcReq )
        {                                                           /* 消息制作失败                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComCheckDelayMmConn:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
            return;                                                 /* 返回                                     */
        }
        else
        {                                                           /* 消息制作成功                             */
            if ( MM_TRUE == ucLUFlg )
            {                                                       /* 是LU后调用该函数                         */
                Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                /* 通知MMC，CS域的业务已经启动              */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
            }
            Mm_SndRrEstReq( RRC_EST_CAUSE_EMERGENCY_CALL, MM_FALSE,
                usMsgSize, pucCmSvcReq );                           /* 发送消息                                 */
            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);             /* 启动保护TIMER                            */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                ucMMConnEstingTI =
                (VOS_UINT8)g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                RcvXXEstReq.ulTransactionId;                        /* 记录正在建立的MM连接                     */
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_CALL_CONTROL;/* 记录正在建立的MM连接的PD                 */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;   /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComCheckDelayMmConn:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        }
    }
    else
    {
        if ( MM_IDLE_NO_IMSI == g_MmGlobalInfo.ucState )
        {
            /* 是正常呼叫                               */
            Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);                      /* 通知CC指定建立的MM连接建立失败           */
        }
        else if ((MM_IDLE_LIMITED_SERVICE == g_MmGlobalInfo.ucState)
              && (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW != g_MmGlobalInfo.usCauseVal))
        {
            /* 不是由于被拒原因值12引起的限制服务状态可以尝试呼叫重发*/
            Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);
        }
        else if (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
        {
            Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_LA);
        }
        else
        {
            Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                      NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);                      /* 通知CC指定建立的MM连接建立失败           */
        }

        if ( MM_FALSE == ucLUFlg )
        {
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                /* 通知MMC，CS域的业务已经停止              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
    }
}


VOS_VOID Mm_ComCheckDelayMmConn_OtherStateHandling_SS(VOS_VOID)
{
    if ((MM_IDLE_LIMITED_SERVICE == g_MmGlobalInfo.ucState)
          && (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW != g_MmGlobalInfo.usCauseVal))
    {
        /* 不是由于被拒原因值12引起的限制服务状态可以尝试ss重发 */
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);
    }
    else if (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
    {
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_LA);
    }
    else
    {
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);
    }

}


VOS_VOID Mm_ComCheckDelayMmConn_OtherStateHandling_SMS(VOS_VOID)
{
    if ((MM_IDLE_LIMITED_SERVICE == g_MmGlobalInfo.ucState)
          && (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW != g_MmGlobalInfo.usCauseVal))
    {
        /* 不是由于被拒原因值12引起的限制服务状态可以尝试ss重发 */
        Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);
    }
    else if (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
    {
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_LA);
    }
    else
    {
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);
    }

}


VOS_VOID Mm_ComCheckDelayMmConn_Other_State_Handling(VOS_UINT8   ucLUFlg)
{
    RRMM_PAGING_IND_STRU        stWPagingMsg;
    GRRMM_PAGING_IND_ST         stGPagingMsg;

    if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
    {
        Mm_ComCheckDelayMmConn_OtherStateHandling_CC(ucLUFlg);
    }
    else if ( MM_TRUE ==
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
    {
        Mm_ComCheckDelayMmConn_OtherStateHandling_SS();
    }
    else if ( MM_TRUE ==
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
    {
        Mm_ComCheckDelayMmConn_OtherStateHandling_SMS();
    }
    else if (MM_PAGING_PLMNSRCH_TRUE == g_MmSubLyrShare.MmShare.ucPagingPlmnSrch)
    {
        g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;
        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            Mm_MakeGPagingInd(&stGPagingMsg);
            /*lint -e961*/
            gaMmStateTable[30][g_MmGlobalInfo.ucState](&stGPagingMsg);
            /*lint +e961*/
        }
        else
        {
            Mm_MakeWPagingInd(&stWPagingMsg);
            /*lint -e961*/
            gaMmStateTable[30][g_MmGlobalInfo.ucState](&stWPagingMsg);
            /*lint +e961*/
        }
    }
    else
    {                                                                   /* 没有等待的CC要求建立的MM连接             */
        if ( MM_FALSE == ucLUFlg )
        {
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                    /* 通知MMC，CS域的业务已经停止              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
    }

    return;
}



VOS_VOID Mm_ComCheckDelayMmConn(
                            VOS_UINT8   ucLUFlg                                     /* 是否是LU结束后调用的该函数               */
                    )
{
    if ( ((MM_CONST_NUM_8 >
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.
        ulTransactionId ) ||(MM_CONST_NUM_14 <
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.
        ulTransactionId )) && (MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg) )
    {
        /* TI不合法                                 */
        Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);        /* 通知CC建立失败                           */
    }
    else
    {                                                                           /* TI合法                                   */
        switch ( g_MmGlobalInfo.ucState )
        {                                                                       /* 当前状态                                 */
        case MM_IDLE_NORMAL_SERVICE:
            Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE(ucLUFlg);
            break;
        case MM_IDLE_ATTEMPTING_TO_UPDATE:
            Mm_ComCheckDelayMmConn_MM_IDLE_ATTEMPTING_TO_UPDATE(ucLUFlg);
            break;
        case MM_IDLE_LIMITED_SERVICE:
        case MM_IDLE_NO_IMSI:
            Mm_ComCheckDelayMmConn_Other_State_Handling(ucLUFlg);
            break;
        case MM_IDLE_LOCATION_UPDATE_NEEDED:
            if (MM_COM_SRVST_NORMAL_SERVICE == NAS_MM_GetLauUptNeededCsSrvStatus())
            {
                Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE(ucLUFlg);
            }
            else
            {
                Mm_ComCheckDelayMmConn_Other_State_Handling(ucLUFlg);
            }
            break;
        case MM_CONNECTION_ACTIVE:
            Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE();
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComCheckDelayMmConn:WARNING: g_MmGlobalInfo.ucState Abnormal");
            break;
        }
    }

    g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;

    return;
}

VOS_UINT8 Mm_ComRrConnRelChk()
{
    if ( ( ( MM_MM_CONN_PROC != g_MmGlobalInfo.ucProc ) ||
        ( NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR !=
        g_MmGlobalInfo.usCauseVal ) )
        && (  MM_FALSE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
        && (  MM_FALSE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
        && (  MM_FALSE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg ))
    {                                                                           /* 原因值不是4或者流程不是MM连接没有缓存    */
        return MM_TRUE;
    }
    else
    {
        if (( MM_MM_CONN_PROC == g_MmGlobalInfo.ucProc ) &&
        ( NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR ==  g_MmGlobalInfo.usCauseVal )
        && (  MM_FALSE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
        && (  MM_FALSE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
        && (  MM_FALSE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg ))
        {                                                                       /* 没有缓存                                 */
            if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
            {                                                                   /* 判断是否为A+I模式                        */
                return MM_TRUE;
            }
        }
    }
    return MM_FALSE;
}
/***********************************************************************
 *  MODULE   : Mm_ComTiChk
 *  FUNCTION : TI的合法性检查
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇     2005.01.31  新版作成
       2.  张志勇  2005.03.09  MM_Review_HW_BUG_027对应
 ************************************************************************/
VOS_UINT8 Mm_ComTiChk()
{
    if ( ((MM_CONST_NUM_8 >
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                RcvXXEstReq.ulTransactionId )
        ||(MM_CONST_NUM_14 <
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                RcvXXEstReq.ulTransactionId ))
        && (MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg) )
    {                                                                           /* TI不合法                                 */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
                                                                    = MM_FALSE;

        NAS_MM_UpdateCsServiceBufferStatusFlg();
        return MM_FALSE;
    }
    if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                    .RcvXXEstReq.ucFlg )
    {
        if ( ( MM_CONST_NUM_8 >
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.
            ulTransactionId )
            || ( MM_CONST_NUM_14 <
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.
            ulTransactionId ) )
        {                                                                       /* TI不合法                                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                      .RcvXXEstReq.ucFlg = MM_FALSE;

            NAS_MM_UpdateCsServiceBufferStatusFlg();
            return MM_FALSE;
        }
    }
    if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                    .RcvXXEstReq.ucFlg )
    {
        if ( ( MM_CONST_NUM_8 >
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
            ulTransactionId )
            || ( MM_CONST_NUM_14 <
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
            ulTransactionId ) )
        {                                                                       /* TI不合法                                 */
            /*return MM_FALSE;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                       .RcvXXEstReq.ucFlg = MM_FALSE; */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                .RcvXXEstReq.ucFlg = MM_FALSE;

            NAS_MM_UpdateCsServiceBufferStatusFlg();
            return MM_FALSE;
        }
    }

    return MM_TRUE;
}

VOS_VOID Mm_ComSigRelForDelayMmConnRej()
{
    switch ( g_MmGlobalInfo.ucState )
    {                                                                           /* 当前状态                                 */
    case MM_IDLE_NORMAL_SERVICE:
        break;
    case MM_CONNECTION_ACTIVE:
        break;
    case MM_IDLE_ATTEMPTING_TO_UPDATE:
    case MM_IDLE_LIMITED_SERVICE:
    case MM_IDLE_LOCATION_UPDATE_NEEDED:
    case MM_IDLE_NO_IMSI:
        if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
        {                                                                       /* 由等待的CC触发的需要建立的MM连接         */
            if ( MMCC_EMERGENCY_CALL ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                RcvXXEstReq.ulCallType )
            {                                                                   /* 是紧急呼叫                               */
                Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
            else
            {                                                                   /* 是正常呼叫                               */
                Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
        }
        else if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {

        }
        break;
    default:
        break;
    }
    return;
}


VOS_VOID  NAS_MM_FillMobileID(
    MM_MOBILE_ID_STRU                  *pstMobileID
)
{
    VOS_UINT8                          *pucIMSI;

    pstMobileID->ucMsIdFlg = g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg;

    PS_MEM_CPY(pstMobileID->aucImei,
               g_MmGlobalInfo.MsCsInfo.MobileId.aucImei,
               sizeof(pstMobileID->aucImei));

    PS_MEM_CPY(pstMobileID->aucImeisv,
               g_MmGlobalInfo.MsCsInfo.MobileId.aucImeisv,
               sizeof(pstMobileID->aucImeisv));

    PS_MEM_CPY(pstMobileID->aucTmsi,
               NAS_MML_GetUeIdTmsi(),
               sizeof(pstMobileID->aucTmsi));

    pucIMSI = NAS_MML_GetSimImsi();

    pstMobileID->Imsi.ucLength = pucIMSI[0];

    PS_MEM_CPY(pstMobileID->Imsi.aucImsi,
               pucIMSI + 1,
               sizeof(pstMobileID->Imsi.aucImsi));


    return;
}



VOS_VOID Mm_ComLuOnly()
{
    MM_MSG_LU_REQ_STRU     Msg;

    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;
    NAS_MML_SIM_TYPE_ENUM_UINT8         ucSimType;
    VOS_UINT32                          ulCsLastSucLac;

    VOS_UINT32                          ulUsimDoneGsmCsAuthFlg;

    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;

    pstRplmnCfgInfo   = NAS_MML_GetRplmnCfg();

    ulCsLastSucLac = NAS_MML_GetCsLastSuccLac();

    pstMsCapability = NAS_MML_GetMsCapability();
    ucSimType       = NAS_MML_GetSimType();

    ulUsimDoneGsmCsAuthFlg              = NAS_MML_IsNeedClearCsCksn_UsimDoneGsmCsAuth();


    /* 发起LAU前清除重试标志位 */
    g_MmGlobalInfo.ucRetryLauFlg = VOS_FALSE;

    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        return;
    }
    if ( VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
    {
        if (VOS_TRUE == NAS_MM_IsNeedDeactiveIsrLauInit())
        {
            /* 去激活ISR,更新TIN值为P-TMSI */
            NAS_MM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pstRplmnCfgInfo->aucLastImsi);
            NAS_MML_SetT3423Status(NAS_MML_TIMER_STOP);
            NAS_MML_SetT3412Status(NAS_MML_TIMER_STOP);
        }

        Mm_TimerStop(MM_TIMER_T3211);
        Mm_TimerStop(MM_TIMER_T3213);

        /* 4.4.4.1 Location updating initiation by the mobile station
           Any timer used for triggering the location updating procedure
           (e.g. T3211, T3212) is stopped if running. */
        Mm_TimerStop(MM_TIMER_T3212);



        Msg.MmIeLuType.ucLUT =
            g_MmGlobalInfo.LuInfo.ucLuType & MM_IE_LU_TYPE_LUT_MASK;            /* 设置LU TYPE                              */
        if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
        {                                                                       /* 有保留的MM连接                           */
            if ( ( MM_CONST_NUM_7 > g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId ) ||
                ( ( MM_CONST_NUM_7 < g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId ) &&
                ( MM_CONST_NUM_15 > g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId ) ) )
            {                                                                   /* TI合法                                   */
                Msg.MmIeLuType.ucFOR = MM_IE_LU_TYPE_FOR_MASK;                          /* 设置FOR                                  */
            }
            else
            {
                /* TI不合法, 通知CC建立失败 */
                Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    RcvXXEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg =
                    MM_FALSE;                                                   /* 设置没有缓存的MM连接                     */
                Msg.MmIeLuType.ucFOR = MM_CONST_NUM_0;                          /* 设置FOR                                  */
            }
        }
        else if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
        {                                                                       /* 有保留的MM连接                           */
            if ( ( MM_CONST_NUM_7 > g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId ) ||
                ( ( MM_CONST_NUM_7 < g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId ) &&
                ( MM_CONST_NUM_15 > g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId ) ) )
            {                                                                   /* TI合法                                   */
                Msg.MmIeLuType.ucFOR = MM_IE_LU_TYPE_FOR_MASK;                          /* 设置FOR                                  */
            }
            else
            {                                                                   /* TI不合法                                 */
                Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                               NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg =
                    MM_FALSE;                                                   /* 设置没有缓存的MM连接                     */
                Msg.MmIeLuType.ucFOR = MM_CONST_NUM_0;                          /* 设置FOR                                  */
            }
        }
        else if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
        {                                                                       /* 有保留的MM连接                           */
            if ( ( MM_CONST_NUM_7 > g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId ) ||
                ( ( MM_CONST_NUM_7 < g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId ) &&
                ( MM_CONST_NUM_15 > g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId ) ) )
            {                                                                   /* TI合法                                   */
                Msg.MmIeLuType.ucFOR = MM_IE_LU_TYPE_FOR_MASK;                          /* 设置FOR                                  */
            }
            else
            {                                                                   /* TI不合法                                 */
                Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                    RcvXXEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                            /* 通知CC建立失败                           */

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
                    ucFlg = MM_FALSE;                                           /* 设置没有缓存的MM连接                     */
                Msg.MmIeLuType.ucFOR = MM_CONST_NUM_0;                          /* 设置FOR                                  */
            }
        }
        else
        {                                                                       /* 没有保留的MM连接                         */
            Msg.MmIeLuType.ucFOR = MM_CONST_NUM_0;                              /* 设置FOR                                  */
        }

        /* SIM卡在W下进行CS 注册时，如果当前LAI无效，将CKSN也置为无效 */
        if ( ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
           && (NAS_MML_SIM_TYPE_SIM       == ucSimType)
           && ((MM_INVALID_LAI            == ulCsLastSucLac)
            || (0x0                       == ulCsLastSucLac)))
          || (VOS_TRUE                    == ulUsimDoneGsmCsAuthFlg) )
        {
            NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);

            NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_FALSE);
        }

        Msg.MmIeCksn.ucCksn = NAS_MML_GetSimCsSecurityCksn();             /* 设置CKSN                                 */
        Msg.MmIeLAI.IeLai.PlmnId.ulMcc = NAS_MML_GetCsLastSuccMcc();
        Msg.MmIeLAI.IeLai.PlmnId.ulMnc = NAS_MML_GetCsLastSuccMnc();
        Msg.MmIeLAI.IeLai.ulLac        = NAS_MML_GetCsLastSuccLac();

        NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

        if ( MM_CONST_NUM_0 != pstMsCapability->aucClassmark2[0] )
        {
            Msg.ucMsClsMskFrUMTSFlg = MM_TRUE;                                  /* 设置ClassMark For UMTS存在               */
            MM_Fill_IE_ClassMark2(Msg.MmIeMsClsMskFrUMTS.aucClassmark2);
        }
        else
        {
            Msg.ucMsClsMskFrUMTSFlg = MM_FALSE;                                 /* 设置ClassMark For UMTS不存在             */
        }


        /* 发起LAU时候清除ATTEMPT UPDATE LAI信息 */
        NAS_MM_InitLaiInfo(NAS_MM_GetAttemptUpdateLaiInfo());

        g_MmMsgLuRjct.MmIeRejCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_NULL;

        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;

        g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt = 0;

        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING);

        Mm_ComMsgLuReqSndOfEstReq(&Msg);                                        /* 发送消息                                 */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                             /* 启动保护TIMER                            */

        g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;

        NAS_MML_SetDelayedCsfbLauFlg(VOS_FALSE);



        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComLuOnly:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING");

        NAS_EventReport(WUEPS_PID_MM,NAS_OM_EVENT_LOCATION_UPDATE_REQ,
                        &g_MmGlobalInfo.LuInfo.ucLuType,NAS_OM_EVENT_LAU_REQ_LEN);
    }
}


VOS_VOID Mm_ComInit ()
{

    VOS_UINT8                           i;
    VOS_UINT32                          ulHoWaitSysinfoTimeLen;
    ulHoWaitSysinfoTimeLen = NAS_MML_GetHoWaitSysinfoTimerLen();

    PS_MEM_SET( &gstMmTimer[0], 0, ( MM_TIMER_MAX * sizeof( MM_TIMER_STRU ) ) );/* 初始化                                   */

    PS_MEM_SET( &g_MmGlobalInfo, 0, sizeof( MM_GLOBAL_CTRL_STRU ) );           /* 初始化                                   */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

    PS_MEM_SET(&gstMmSuspendMsgQue, 0, sizeof(MM_SUSPEND_MSG_BUF_ST));        /* 初始化                                   */
    PS_MEM_SET(&gstMmTimerSuspend, 0, sizeof(MM_TIMER_ST));                   /* 初始化                                   */

    g_MmMsgLuAccpt.MmIePlmnList.ucPlmnNum = 0;

    gstMmTimerSuspend.ulTimerLength     = MM_TIMER_PROTECT_SUSPEND_VALUE;

    PS_MEM_SET(&g_MmMsgLuAccpt, 0, sizeof(MM_MSG_LU_ACCPT_STRU));
    PS_MEM_SET(&g_MmMsgMmInfo, 0, sizeof(MM_MSG_MM_INFO_STRU));

    PS_MEM_SET(&g_AgentUsimAuthCnf, 0, sizeof(MM_USIM_AUTHENTICATION_CNF_STRU));

    g_MmSubLyrShare.MmShare.ucCsAttachState = MM_STATUS_DETACHED;

    g_MmGlobalInfo.ucSysInfoFlg =  MM_FALSE;

    g_MmSubLyrShare.MmShare.ucSpecProFlg =  MM_NOT_UPDATED_SPECIFIC_PROCEDURE;

    g_MmGlobalInfo.ucConnRcvSysFlg = MM_FALSE;

    g_MmGlobalInfo.ucFollowOnFlg         = MM_NO_FOLLOW_ON;
    g_MmGlobalInfo.ucCsSigConnFlg        = MM_CS_SIG_CONN_ABSENT;

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComInit:INFO: MmCsSigConnFlg is MM_CS_SIG_CONN_ABSENT");
    g_MmGlobalInfo.AuthenCtrlInfo.ucRandFlg = MM_AUTHEN_RAND_ABSENT;

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI   =
        NO_MM_CONN_ESTING;                                                      /* 没有正在建立的MM连接                     */
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg  =
        MM_FALSE;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI   =
        NO_MM_CONN_ESTING;                                                      /* 没有正在建立的MM连接                     */
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg  =
        MM_FALSE;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI  =
        NO_MM_CONN_ESTING;                                                      /* 没有正在建立的MM连接                     */
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg =
        MM_FALSE;
    g_MmGlobalInfo.ucMMConnEstingPD                                 =
        NO_MM_CONN_ESTING;

    g_NasMmImportFunc.SigConnCtrl.RrEstReqFunc = MM_WasRrEstReq;
    g_NasMmImportFunc.SigConnCtrl.RrRelReqFunc = As_RrRelReq;
    g_NasMmImportFunc.SigDataTransfer.RrDataReqFunc = MM_WasRrDataReq;

    g_NasMmImportFunc.ucFuncEnvironment             = NAS_MML_NET_RAT_TYPE_WCDMA;
    g_stMmNsd.ucNsdMod = MM_NSD_MOD_R99_ONWARDS;

    g_MmGlobalInfo.ucLikeB = MM_FALSE;
    g_MmGlobalInfo.ucAttDelay = MM_FALSE;

    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;
    g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
    g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;

    g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt = 0;

    g_MmGlobalInfo.ucCsCipherAlgor = NAS_MM_CIPHER_ALGO_NOPRESENT;
    g_MmSubLyrShare.MmShare.ucCsSpecificFlg = MM_SPECIFIC_OFF;

    g_MmGlobalInfo.ucPowerOnFlg = MM_TRUE;

    for ( i = 0; i < MM_TIMER_MAX; i++ )
    {
        gstMmTimer[i].ucTimerStatus = MM_TIMER_STOP;

        /* 将定时器修改为非循环定时器 */
        gstMmTimer[i].ucMode        = VOS_RELTIMER_NOLOOP;
    }

    /* 初始化TIMER的时长 */
    gstMmTimer[MM_TIMER_T3210].ulTimerLen = MM_TIMER_T3210_VALUE;
    gstMmTimer[MM_TIMER_T3211].ulTimerLen = MM_TIMER_T3211_VALUE;
    gstMmTimer[MM_TIMER_T3213].ulTimerLen = MM_TIMER_T3213_VALUE;
    gstMmTimer[MM_TIMER_T3214].ulTimerLen = MM_TIMER_T3214_VALUE;
    gstMmTimer[MM_TIMER_T3216].ulTimerLen = MM_TIMER_T3216_VALUE;
    gstMmTimer[MM_TIMER_T3218].ulTimerLen = MM_TIMER_T3218_VALUE;
    gstMmTimer[MM_TIMER_T3220].ulTimerLen = MM_TIMER_T3220_VALUE;

    gstMmTimer[MM_TIMER_T3230].ulTimerLen = MM_TIMER_T3230_VALUE;

    gstMmTimer[MM_TIMER_T3240].ulTimerLen = MM_TIMER_T3240_VALUE;
    gstMmTimer[MM_TIMER_PROTECT_AGENT].ulTimerLen =
                                    MM_TIMER_PROTECT_AGENT_VALUE;
    gstMmTimer[MM_TIMER_PROTECT_DETACH].ulTimerLen =
                                    MM_TIMER_PROTECT_DETACH_VALUE;
    gstMmTimer[MM_TIMER_PROTECT_SIGNALLING].ulTimerLen
                                     = MM_TIMER_PROTECT_W_SIGNALLING_VALUE;

    gstMmTimer[MM_TIMER_PROTECT_CC].ulTimerLen = MM_TIMER_PROTECT_CC_VALUE;
    gstMmTimer[MM_TIMER_PROTECT_CCBS].ulTimerLen = MM_TIMER_PROTECT_CCBS_VALUE;
    gstMmTimer[MM_TIMER_DELAY_LU_GSM].ulTimerLen = MM_TIMER_DELAY_LU_GSM_VALUE;
    gstMmTimer[MM_TIMER_DELAY_CS_SERVICE_GSM].ulTimerLen = MM_TIMER_DELAY_CS_SERVICE_GSM_VALUE;

    gstMmTimer[MM_TIMER_WAIT_CONNECT_REL].ulTimerLen = MM_TIMER_WAIT_CONNECT_REL_VALUE;

    gstMmTimer[MM_TIMER_NORMAL_CSFB_HO_WAIT_SYSINFO].ulTimerLen = ulHoWaitSysinfoTimeLen;

    gstMmTimer[MM_TIMER_EMERGENCY_CSFB_HO_WAIT_SYSINFO].ulTimerLen = ulHoWaitSysinfoTimeLen;

    gstMmTimer[MM_TIMER_CS_HO_WAIT_SYSINFO].ulTimerLen = ulHoWaitSysinfoTimeLen;


    gstMmTimer[MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT].ulTimerLen = NAS_MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT_LEN_VALUE;

    gstMmTimer[MM_TIMER_WAIT_GET_HO_SECU_INFO_CNF].ulTimerLen = MM_TIMER_WAIT_GET_HO_SECU_INFO_CNF_LEN_VALUE;

    gstMmTimer[MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE].ulTimerLen = (VOS_UINT32)(NAS_MML_GetProtectMtCsfbPagingProcedureLen() * 1000);

#if (FEATURE_ON == FEATURE_ECALL)
    gstMmTimer[MM_TIMER_T3242].ulTimerLen = MM_TIMER_T3242_VALUE;
    gstMmTimer[MM_TIMER_T3243].ulTimerLen = MM_TIMER_T3243_VALUE;
#endif

    g_MmSubLyrShare.MmShare.ucCsAttachState = MM_STATUS_DETACHED;


    g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;
    g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat              = MM_AUTHEN_RAND_DIFFER;
    g_MmGlobalInfo.AuthenCtrlInfo.ucLastAuthType            = MM_CONST_NUM_2;

    g_T3211Flag = 0;
    g_MmGlobalInfo.ucMmServiceState = MMC_MM_NO_SERVICE;

    g_MmSubLyrShare.MmShare.ucCsIntegrityProtect        = NAS_MML_RRC_INTEGRITY_PROTECT_DEACTIVE;


    g_MmSubLyrShare.MmShare.MmSuspendEvent              = MM_EVENT_ID_INVALID;


    /* 初始化为无延迟的LAU标志 */
    NAS_MML_SetDelayedCsfbLauFlg(VOS_FALSE);

    g_MmGlobalInfo.enPreRatType                         = NAS_MML_NET_RAT_TYPE_BUTT;

    g_MmGlobalInfo.ucLauAcceptContainDiffNbLaiFlg  = VOS_FALSE;

    NAS_MM_SetEstCnfResult(RRC_NAS_EST_RESULT_BUTT);

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MM_SetSrvccFlg(VOS_FALSE);

    NAS_MM_SetRcvSrvccCallInfoFlg(VOS_FALSE);
#endif

    NAS_MM_InitLaiInfo(NAS_MM_GetAttemptUpdateLaiInfo());

    NAS_MML_InitOldCampLai(NAS_MM_GetAllocT3212ValueLaiInfo());
    NAS_MM_SetNetworkT3212ValueType(NAS_MM_T3212_VALUE_TYPE_BUTT);

    NAS_MM_InitT3212Counter();

    g_MmMsgCmSvcRjct.ucIsCmSrvRejCongestionWithT3246    = VOS_FALSE;

    return;                                                                     /* 返回                                     */
}


VOS_VOID    Mm_Nop(VOS_VOID* pMsg)
{
}


VOS_VOID Mm_ComStart(
                 VOS_VOID
                 )
{

    VOS_UINT8                           i;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;
    VOS_UINT8                           ulInvalidCnt;
    VOS_UINT8                          *pucTmpTmsi;

    /*根据卡状态信息，更新CS的Sim卡状态*/
    if (VOS_TRUE == NAS_MML_GetSimPresentStatus())
    {
        NAS_MML_SetSimCsRegStatus(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    }


    if (VOS_TRUE == NAS_MML_GetSimCsRegStatus())
    {                                                                           /* SIM有效                                  */
        /* IMSI */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg
           |= MM_MS_ID_IMSI_PRESENT;                                            /* 置Mobile ID存在标志                      */



        /* 根据当前存储的TMSI是否有效，设定是否存在TMSI */
        ulInvalidCnt = 0;
        pucTmpTmsi = NAS_MML_GetUeIdTmsi();
        for (i = 0; i < NAS_MML_MAX_PTMSI_LEN; i++)
        {
            if (NAS_MML_TMSI_INVALID == pucTmpTmsi[i])
            {
                ulInvalidCnt++;
            }
        }

        if ( ulInvalidCnt < NAS_MML_MAX_PTMSI_LEN )
        {
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg
                |= MM_MS_ID_TMSI_PRESENT;

        }


        /* 保存分配当前TMSI的网络ID */
        if ( MM_MS_ID_TMSI_PRESENT ==
              (MM_MS_ID_TMSI_PRESENT & g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg) )
        {
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMcc = NAS_MML_GetCsLastSuccMcc();
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMnc = NAS_MML_GetCsLastSuccMnc();
        }
    }

    /* IMEI(SV) */
    pstMsCapability = NAS_MML_GetMsCapability();
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |= MM_MS_ID_IMEI_PRESENT;
    g_MmGlobalInfo.MsCsInfo.MobileId.aucImei[0]
       = (VOS_UINT8)((pstMsCapability->aucImeisv[0] << 4) | 0x0f);

    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |= MM_MS_ID_IMEISV_PRESENT;
    g_MmGlobalInfo.MsCsInfo.MobileId.aucImeisv[0]
       = g_MmGlobalInfo.MsCsInfo.MobileId.aucImei[0];

    for (i = MM_CONST_NUM_1; i < MM_CONST_NUM_8; i++ )
    {                                                                           /* 存储IMEI                                 */
        g_MmGlobalInfo.MsCsInfo.MobileId.aucImei[i]
           = (VOS_UINT8)((pstMsCapability->aucImeisv[2*i]<<4)
                       | pstMsCapability->aucImeisv[(2*i)-1]);
        g_MmGlobalInfo.MsCsInfo.MobileId.aucImeisv[i]
           = g_MmGlobalInfo.MsCsInfo.MobileId.aucImei[i];
    }
    g_MmGlobalInfo.MsCsInfo.MobileId.aucImei[7] &= 0x0f;
    g_MmGlobalInfo.MsCsInfo.MobileId.aucImeisv[8]
       = (VOS_UINT8)( pstMsCapability->aucImeisv[NV_ITEM_IMEI_SIZE-1]
                   & 0x0f);
    g_MmGlobalInfo.MsCsInfo.MobileId.aucImeisv[8] |= 0xf0;




    /* 为了防止使用测试号段避过IMSI的检查，使得能够使用TMSI进行注册，需要
       进行防卡贴的判定，在NV项激活的情况下，特殊号段TMSI置为无效
    */
    if (VOS_TRUE == NAS_PreventTestImsiRegFlg())
    {
        NAS_MML_InitUeIdTmsiInvalid();

        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;
    }


    Mm_SndMmcStartCnf();
}




VOS_VOID Mm_ComToU2Handle()
{
    /* g_MmSubLyrShare.MmShare.ucUpdateSts = MM_UPDATE_STATUS_NOT_UPDATED; */
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);
    Mm_ComNasInfoSav(
                    MM_STATUS_DETACHED,
                    MM_CKSN_INVALID
                    );                                                          /* 设置MM信息                               */
    Mm_ComDelLai();                                                             /* 删除LAI                                  */
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

    NAS_MML_InitUeIdTmsiInvalid();

    /* Mm_SndAgentUsimUpdateFileReq(MM_READ_CKIK_FILE_ID); */                    /* 更新SIM卡更新状态                        */
    Mm_ComUpdateUsimFileReq();


    Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

    g_MmGlobalInfo.ucPowerOnFlg = MM_FALSE;

    /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                              */
    /*" \nMM:STATUS is  MM_IDLE_ATTEMPTING_TO_UPDATE\r " );                     */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComToU2Handle:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
}




VOS_VOID Mm_ComLuCauseHandle(VOS_UINT16 usCause)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;
    MM_LAI_STRU                                            *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstCampLaiInfo  = VOS_NULL_PTR;

    g_MmGlobalInfo.usCauseVal   = usCause;                            /* 记录原因值                               */
    switch(usCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:

        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComLuCauseHandle:INFO: MmServiceState is MM_NO_IMSI");

        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);              /* 设置更新状态                             */
        NAS_MML_SetSimCsRegStatus(VOS_FALSE);
        Mm_ComNasInfoSav(MM_STATUS_DETACHED, MM_CKSN_INVALID);
        Mm_ComDelLai();                                                         /* 删除LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

        NAS_MML_InitUeIdTmsiInvalid();

        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_IMSI_PRESENT;
        Mm_ComUpdateUsimFileReq();


        Mm_ComSetMmState(MM_IDLE_NO_IMSI);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComLuCauseHandle:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComLuCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");

        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;                   /* 设置LU COUNTER为0                        */
        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);              /* 设置更新状态                             */
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        MM_CKSN_INVALID
                        );                                                      /* 设置MM信息                               */
        Mm_ComDelLai();                                                         /* 删除LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;   /* 设置TMIS不存在                           */

        NAS_MML_InitUeIdTmsiInvalid();

        if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
        }
        else
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
        }

        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComLuCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        break;
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComLuCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");

        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;                   /* 设置LU COUNTER为0                        */
        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);              /* 设置更新状态                             */
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );                                                      /* 设置MM信息                               */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {/* 3G USIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        }
        else
        {/* 2G SIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        }


        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComLuCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        break;
    default:
        if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
        {                                                                       /* 判断LU Counter是否小于4                  */
            enCsUpdateStatus    = NAS_MML_GetCsUpdateStatus();
            if ( ( VOS_FALSE == NAS_MML_IsCsLaiChanged() )
              && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus) )
            {                                                                   /* 判断LAI是否未改变,且更新状态为U1         */
                g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComLuCauseHandle:INFO: MmServiceState is MM_NORMAL_SERVICE");

                Mm_ComNasInfoSav(
                                 MM_STATUS_ATTACHED,
                                 NAS_MML_GetSimCsSecurityCksn()
                                 );
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComLuCauseHandle:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                Mm_TimerStart(MM_TIMER_T3211);                                  /* 启动T3211                                */
            }
            else
            {
                if ( ( usCause >=
                    MM_IE_REJ_CAUSE_RETRY_UPON_ENTRY_INTO_NEW_CELL_LOW ) &&
                    ( usCause <=
                    MM_IE_REJ_CAUSE_RETRY_UPON_ENTRY_INTO_NEW_CELL_UP ) )
                {                                                               /* 判断原因值是否在retry范围内              */
                    g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;                 /* 设置ucRetryFlg为MM_TRUE                  */
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;                /* 设置ucRetryFlg为MM_FALSE                 */
                }

                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComLuCauseHandle:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");


                /* 在U2状态，保存当前的LAI信息 */
                pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
                pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

                pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
                pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
                pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

                Mm_ComToU2Handle();
                Mm_TimerStart(MM_TIMER_T3211);                                  /* 启动T3211                                */
            }
        }
        else
        {
            if ( ( usCause >
                MM_IE_REJ_CAUSE_RETRY_UPON_ENTRY_INTO_NEW_CELL_LOW ) &&
                ( usCause <
                MM_IE_REJ_CAUSE_RETRY_UPON_ENTRY_INTO_NEW_CELL_UP ) )
            {                                                                   /* 判断原因值是否在retry范围内              */
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;                     /* 设置ucRetryFlg为MM_TRUE                  */
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;                    /* 设置ucRetryFlg为MM_FALSE                 */
            }
            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_TYPE_BUTT;
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* 设置服务状态                             */

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComLuCauseHandle:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");


            /* 在U2状态，保存当前的LAI信息 */
            pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
            pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

            pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
            pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
            pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

            Mm_ComToU2Handle();



            /* SOR特性由MMC触发MM发起LAU */
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);



            /*A32D10964==>*/
            if (MM_DETACH_NEED_DELAY == g_MmGlobalInfo.ucDetachType)
            {
                Mm_TimerStop(MM_TIMER_PROTECT_DETACH);
                g_MmGlobalInfo.ucDetachType = MM_DETACH_TYPE_BUTT;
                Mm_Cell_S0_E23(VOS_NULL_PTR);
            }
            /*<==A32D10964*/
        }
        break;
    }

    g_MmGlobalInfo.ucProc     = MM_NULL_PROC;
    Mm_ComCheckDelayMmConn( MM_FALSE );
    g_MmGlobalInfo.usCauseVal = NAS_MML_REG_FAIL_CAUSE_NULL;
}



VOS_VOID Mm_ComGmmAttachCauseHandle(VOS_UINT16 usCause)
{


    switch(usCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        /* 参考24.008：
           If the MS is IMSI attached, the MS shall in addition
           set the update status to U3 ROAMING NOT ALLOWED,
           shall delete any TMSI, LAI and ciphering key sequence number.
           If the MS is operating in MS operation mode A and an RR connection exists,
           the MS shall abort the RR connection, unless an emergency call is ongoing.
           The SIM/USIM shall be considered as invalid also for non-GPRS services
           until switching off or the SIM/USIM is removed */
        /*if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )*/
        {
            g_MmGlobalInfo.ucProc       = MM_GMM_ATTACH_PROC;
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_GMM_ATTACH_PROC \r " );               */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmAttachCauseHandle:INFO: MmServiceState is MM_GMM_ATTACH_PROC");
            g_MmGlobalInfo.usCauseVal   = usCause;
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* 设置服务状态                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /* " \nMM:MmServiceState is MM_NO_IMSI \r " );                      */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmAttachCauseHandle:INFO: MmServiceState is MM_NO_IMSI");

            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);          /* 设置更新状态                             */
            NAS_MML_SetSimCsRegStatus(VOS_FALSE);
            Mm_ComNasInfoSav(
                             MM_STATUS_DETACHED,
                             MM_CKSN_INVALID
                             );
            Mm_ComDelLai();                                                     /* 删除LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_TMSI_PRESENT;

            NAS_MML_InitUeIdTmsiInvalid();

            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                    ~MM_MS_ID_IMSI_PRESENT;

            Mm_ComUpdateUsimFileReq();


            Mm_ComSetMmState(MM_IDLE_NO_IMSI);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmAttachCauseHandle:NORMAL: STATUS is MM_IDLE_NO_IMSI");
            Mm_ComProcCauseClear();
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        g_MmGlobalInfo.ucProc       = MM_GMM_ATTACH_PROC;
        /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                          */
        /*" \nMM:MmServiceState is MM_GMM_ATTACH_PROC \r " );                   */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmAttachCauseHandle:INFO: MmServiceState is MM_GMM_ATTACH_PROC");
        g_MmGlobalInfo.usCauseVal   = usCause;
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                           /* 设置服务状态                             */
        /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmServiceState is MM_NO_IMSI \r " );  */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmAttachCauseHandle:INFO: MmServiceState is MM_NO_IMSI");

        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);              /* 设置更新状态                             */
        NAS_MML_SetSimCsRegStatus(VOS_FALSE);
        Mm_ComNasInfoSav(MM_STATUS_DETACHED, MM_CKSN_INVALID);
        Mm_ComDelLai();                                                         /* 删除LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

        NAS_MML_InitUeIdTmsiInvalid();

        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_IMSI_PRESENT;

        if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
        }
        else
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
        }


        Mm_ComSetMmState(MM_IDLE_NO_IMSI);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmAttachCauseHandle:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        Mm_ComProcCauseClear();
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        /*if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )*/
        {
            g_MmGlobalInfo.ucProc       = MM_GMM_ATTACH_PROC;
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /* " \nMM:MmServiceState is MM_GMM_ATTACH_PROC \r " );              */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmAttachCauseHandle:INFO: MmServiceState is MM_GMM_ATTACH_PROC");
            g_MmGlobalInfo.usCauseVal   = usCause;
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* 设置服务状态                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );               */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmAttachCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");

            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;               /* 设置LU COUNTER为0                        */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);          /* 设置更新状态                             */
            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            MM_CKSN_INVALID
                            );                                                  /* 设置MM信息                               */
            Mm_ComDelLai();                                                     /* 删除LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_TMSI_PRESENT;         /* 设置TMIS不存在                           */

            NAS_MM_UpdateEquPlmnInfo(usCause);

            NAS_MML_InitUeIdTmsiInvalid();

            if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
            }



            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmAttachCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            Mm_ComProcCauseClear();

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == usCause)
            {
                Mm_TimerStop(MM_TIMER_T3212);
            }
        }
        break;
    default:
        break;
    }
}



VOS_VOID Mm_ComGmmRauCauseHandle(VOS_UINT16 usCause)
{


    switch(usCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        /* 参考24.008：
           If the MS is IMSI attached, the MS shall in addition
           set the update status to U3 ROAMING NOT ALLOWED,
           shall delete any TMSI, LAI and ciphering key sequence number.
           If the MS is operating in MS operation mode A and an RR connection exists,
           the MS shall abort the RR connection, unless an emergency call is ongoing.
           The SIM/USIM shall be considered as invalid also for non-GPRS services
           until switching off or the SIM/USIM is removed */
        /*if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )*/
        {
            g_MmGlobalInfo.ucProc       = MM_GMM_RAU_PROC;
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_GMM_RAU_PROC \r " );                  */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmRauCauseHandle:INFO: MmServiceState is MM_GMM_RAU_PROC");
            g_MmGlobalInfo.usCauseVal   = usCause;
            g_MmGlobalInfo.usCauseVal   = usCause;                                /* 记录原因值                               */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* 设置服务状态                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_NO_IMSI \r " );                       */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmRauCauseHandle:INFO: MmServiceState is MM_NO_IMSI");

            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);          /* 设置更新状态                             */

            Mm_ComNasInfoSav(
                             MM_STATUS_DETACHED,
                             MM_CKSN_INVALID
                             );
            Mm_ComDelLai();                                                     /* 删除LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_TMSI_PRESENT;

            NAS_MML_InitUeIdTmsiInvalid();

            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                    ~MM_MS_ID_IMSI_PRESENT;

            Mm_ComUpdateUsimFileReq();



            NAS_MML_SetSimCsRegStatus(VOS_FALSE);

            Mm_ComSetMmState(MM_IDLE_NO_IMSI);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmRauCauseHandle:NORMAL: STATUS is MM_IDLE_NO_IMSI");
            Mm_ComProcCauseClear();
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
        {
            g_MmGlobalInfo.ucProc       = MM_GMM_RAU_PROC;
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_GMM_RAU_PROC \r " );                  */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmRauCauseHandle:INFO: MmServiceState is MM_GMM_RAU_PROC");
            g_MmGlobalInfo.usCauseVal   = usCause;
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* 设置服务状态                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /* " \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );              */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmRauCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");

            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;               /* 设置LU COUNTER为0                        */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);          /* 设置更新状态                             */
            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            MM_CKSN_INVALID
                            );                                                  /* 设置MM信息                               */
            Mm_ComDelLai();                                                     /* 删除LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_TMSI_PRESENT;         /* 设置TMIS不存在                           */

            NAS_MM_UpdateEquPlmnInfo(usCause);

            NAS_MML_InitUeIdTmsiInvalid();

            if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
            }



            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmRauCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            Mm_ComProcCauseClear();

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == usCause)
            {
                Mm_TimerStop(MM_TIMER_T3212);
            }
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        /*if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )*/
        {
            g_MmGlobalInfo.ucProc       = MM_GMM_RAU_PROC;
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_GMM_RAU_PROC \r " );                  */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmRauCauseHandle:INFO: MmServiceState is MM_GMM_RAU_PROC");
            g_MmGlobalInfo.usCauseVal   = usCause;
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* 设置服务状态                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );               */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmRauCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");

            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;               /* 设置LU COUNTER为0                        */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);          /* 设置更新状态                             */
            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            NAS_MML_GetSimCsSecurityCksn()
                            );                                                  /* 设置MM信息                               */


            NAS_MM_UpdateEquPlmnInfo(usCause);

            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);             /* 更新SIM卡更新状态                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);              /* 更新SIM卡更新状态                        */
            }


            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmRauCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            Mm_ComProcCauseClear();
        }
        break;
    default:
        break;
    }
}


VOS_VOID NAS_MM_ProcGmmSeriveRejCause3(VOS_UINT16 usCause)
{
    g_MmGlobalInfo.ucProc       = MM_GMM_SR_PROC;

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmServiceState is MM_GMM_SR_PROC");
    g_MmGlobalInfo.usCauseVal   = usCause;
    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                           /* 设置服务状态                             */

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmServiceState is MM_NO_IMSI");

    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);              /* 设置更新状态                             */

    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    Mm_ComNasInfoSav(
                     MM_STATUS_DETACHED,
                     MM_CKSN_INVALID
                     );                                                     /* 向RRC发送RRMM_NAS_INFO_CHANGE_REQ        */
    Mm_ComDelLai();                                                         /* 删除LAI                                  */
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                        ~MM_MS_ID_TMSI_PRESENT;             /* 设置TMSI不存在                           */

    NAS_MML_InitUeIdTmsiInvalid();

    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                            ~MM_MS_ID_IMSI_PRESENT;         /* 设置IMSI不存在                           */

    Mm_ComUpdateUsimFileReq();


    Mm_ComSetMmState(MM_IDLE_NO_IMSI);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmSrCauseHandle:NORMAL: STATUS is MM_IDLE_NO_IMSI");
    Mm_ComProcCauseClear();

    return;

}



VOS_VOID Mm_ComGmmSrCauseHandle(VOS_UINT16 usCause)
{


    switch(usCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        NAS_MM_ProcGmmSeriveRejCause3(usCause);
        break;

    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
    
        NAS_MM_ProcGmmSeriveRejCause3(usCause);
        break;


    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
        {                                                                       /* 如果为A+I模式                            */
            if ( (MM_FALSE == g_MmGlobalInfo.ucLikeB)
             && ((MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucState)
                || ((MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState)
                   && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus))))

            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* 设置类似B模式                            */
                /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmLikeB is MM_TRUE \r " );*/
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmLikeB is MM_TRUE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            }
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        g_MmGlobalInfo.ucProc       = MM_GMM_SR_PROC;
        /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                          */
        /*" \nMM:MmServiceState is MM_GMM_SR_PROC \r " );                       */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmServiceState is MM_GMM_SR_PROC");
        g_MmGlobalInfo.usCauseVal   = usCause;
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;                   /* 设置服务状态                             */
        /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                          */
        /*" \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );                   */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");

        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);              /* 设置更新状态                             */
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        MM_CKSN_INVALID
                        );                                                      /* 设置MM信息                               */
        Mm_ComDelLai();                                                         /* 删除LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                            ~MM_MS_ID_TMSI_PRESENT;             /* 设置TMIS不存在                           */

        NAS_MML_InitUeIdTmsiInvalid();

        if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
        }
        else
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
        }


        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmSrCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        Mm_ComProcCauseClear();

        Mm_TimerStop(MM_TIMER_T3212);

        break;
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
        {
            g_MmGlobalInfo.ucProc       = MM_GMM_SR_PROC;
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_GMM_SR_PROC \r " );                   */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmServiceState is MM_GMM_SR_PROC");
            g_MmGlobalInfo.usCauseVal   = usCause;
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* 设置服务状态                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );               */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");

            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;               /* 设置LU COUNTER为0                        */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);          /* 设置更新状态                             */
            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            MM_CKSN_INVALID
                            );                                                  /* 设置MM信息                               */
            Mm_ComDelLai();                                                     /* 删除LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_TMSI_PRESENT;         /* 设置TMIS不存在                           */

            NAS_MML_InitUeIdTmsiInvalid();

            if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
            }


            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmSrCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            Mm_ComProcCauseClear();
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
        {
            g_MmGlobalInfo.ucProc       = MM_GMM_SR_PROC;
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /* " \nMM:MmServiceState is MM_GMM_SR_PROC \r " );                  */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmServiceState is MM_GMM_SR_PROC");
            g_MmGlobalInfo.usCauseVal   = usCause;
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* 设置服务状态                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /* " \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );              */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");

            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;               /* 设置LU COUNTER为0                        */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);          /* 设置更新状态                             */
            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            NAS_MML_GetSimCsSecurityCksn()
                            );                                                  /* 设置MM信息                               */


            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);             /* 更新SIM卡更新状态                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);              /* 更新SIM卡更新状态                        */
            }


            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmSrCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            Mm_ComProcCauseClear();
        }
        break;
    default:
        break;
    }
}


VOS_UINT32 NAS_MM_IsNeedStartT3212RcvGmmDetachInd( VOS_VOID )
{
    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
     && ((MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucState)
       || ((MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState)
        && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus))))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}




VOS_VOID Mm_ComNetDetachCauseHandle(VOS_UINT16 usCause)
{


    switch(usCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        g_MmGlobalInfo.ucProc       = MM_NET_DETACH_PROC;
        /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                          */
        /*" \nMM:MmServiceState is MM_NET_DETACH_PROC \r " );                   */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComNetDetachCauseHandle:INFO: MmServiceState is MM_NET_DETACH_PROC");
        g_MmGlobalInfo.usCauseVal   = usCause;
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                           /* 设置服务状态                             */
        /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmServiceState is MM_NO_IMSI \r " );  */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComNetDetachCauseHandle:INFO: MmServiceState is MM_NO_IMSI");

        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);              /* 设置更新状态                             */

        NAS_MML_SetSimCsRegStatus(VOS_FALSE);
        Mm_ComNasInfoSav(
                         MM_STATUS_DETACHED,
                         MM_CKSN_INVALID
                         );                                                     /* 向RRC发送RRMM_NAS_INFO_CHANGE_REQ        */
        Mm_ComDelLai();                                                         /* 删除LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                            ~MM_MS_ID_TMSI_PRESENT;             /* 设置TMSI不存在                           */

        NAS_MML_InitUeIdTmsiInvalid();

        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_IMSI_PRESENT;         /* 设置IMSI不存在                           */

        Mm_ComUpdateUsimFileReq();


        Mm_ComSetMmState(MM_IDLE_NO_IMSI);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComNetDetachCauseHandle:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        Mm_ComProcCauseClear();
        break;

        /*24008_CR2243R2_(Rel-11)_C1-124176 24008  4.7.4.2.2章节描述如下:
        If the MS is attached for GPRS and non-GPRS services and the network operates in network operation mode I,
        then if in the MS the timer T3212 is not already running, the timer T3212 shall be
        set to its initial value and restarted if:
        -   the detach type IE indicates "re-attach required";
        -   the detach type IE indicates "re-attach not required" and no cause code is included; or
        -   the detach type IE indicates "re-attach not required" and the cause code is #7 "GPRS services not allowed"
            or #14 "GPRS services not allowed in this PLMN". */
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
    case NAS_MML_REG_FAIL_CAUSE_NULL:
        if (VOS_TRUE == NAS_MM_IsNeedStartT3212RcvGmmDetachInd())
        {
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* 设置类似于B模式                          */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmLikeB is MM_TRUE \r " );*/
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComNetDetachCauseHandle:INFO: MmLikeB is MM_TRUE");
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
        /* g_MmGlobalInfo.ucProc       = MM_NET_DETACH_PROC;    */
        /* g_MmGlobalInfo.usCauseVal   = ucCause;               */
        /* g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE; */              /* 设置服务状态                             */
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        g_MmGlobalInfo.ucProc       = MM_NET_DETACH_PROC;
        /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                          */
        /*" \nMM:MmServiceState is MM_NET_DETACH_PROC \r " );                   */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComNetDetachCauseHandle:INFO: MmServiceState is MM_NET_DETACH_PROC");
        g_MmGlobalInfo.usCauseVal   = usCause;
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;                   /* 设置服务状态                             */
        /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                          */
        /*" \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );                   */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComNetDetachCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");

        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);              /* 设置更新状态                             */
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        MM_CKSN_INVALID
                        );                                                      /* 设置MM信息                               */
        Mm_ComDelLai();                                                         /* 删除LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                            ~MM_MS_ID_TMSI_PRESENT;             /* 设置TMIS不存在                           */

        NAS_MML_InitUeIdTmsiInvalid();

        if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
        }
        else
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
        }


        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComNetDetachCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        Mm_ComProcCauseClear();
        Mm_TimerStop(MM_TIMER_T3212);
        break;
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
        {
            g_MmGlobalInfo.ucProc       = MM_NET_DETACH_PROC;
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_NET_DETACH_PROC \r " );               */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComNetDetachCauseHandle:INFO: MmServiceState is MM_NET_DETACH_PROC");
            g_MmGlobalInfo.usCauseVal   = usCause;
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* 设置服务状态                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );               */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComNetDetachCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");

            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;               /* 设置LU COUNTER为0                        */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);          /* 设置更新状态                             */
            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            MM_CKSN_INVALID
                            );                                                  /* 设置MM信息                               */
            Mm_ComDelLai();                                                     /* 删除LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_TMSI_PRESENT;         /* 设置TMIS不存在                           */

            NAS_MML_InitUeIdTmsiInvalid();

            if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
            }


            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComNetDetachCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            Mm_ComProcCauseClear();
        }
        break;



    default:
        break;
    }
}

/***********************************************************************
 *  MODULE   : Mm_ComCauseHandleAllProc
 *  FUNCTION : MM对原因值的处理
 *  INPUT    : VOS_UINT8   ucProcType                当前流程的类型
 *             VOS_UINT8   ucCause                   流程收到的原因值
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇    04-03-10  新版作成,二期添加
 *     2.
 ************************************************************************/

VOS_VOID Mm_ComCauseHandleAllProc(
                              VOS_UINT8   ucProcType,
                              VOS_UINT16  usCause
                              )
{
    switch(ucProcType)
    {
    case MM_LU_PROC:
        Mm_ComLuCauseHandle(usCause);
        break;
    case MM_GMM_ATTACH_PROC:
        Mm_ComGmmAttachCauseHandle(usCause);
        break;
    case MM_GMM_RAU_PROC:
        Mm_ComGmmRauCauseHandle(usCause);
        break;
    case MM_GMM_SR_PROC:
        Mm_ComGmmSrCauseHandle(usCause);
        break;
    case MM_NET_DETACH_PROC:
        Mm_ComNetDetachCauseHandle(usCause);
        break;
    default:
        break;
    }
}

VOS_VOID NAS_MM_DelLaiTmsiCK(VOS_VOID)
{
    /* 删除全局变量中的LAI */
    Mm_ComDelLai();

    /* 删除全局变量中的TMSI */
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg              &= ~MM_MS_ID_TMSI_PRESENT;
    NAS_MML_InitUeIdTmsiInvalid();

    /* 删除SIM卡中的LAI、IMSI */
    NAS_MM_WriteLocaInCard();

    NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);

    /* 根据SIM卡类型决定当前需要删除KC还是CKIK*/
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        NAS_MM_WriteKCInCard();
    }
    else
    {
        NAS_MM_WriteCkIkInCard();
    }
}



VOS_VOID Mm_ComToNoImsiHandle()
{
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);                  /* 设置更新状态                             */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    Mm_ComNasInfoSav(MM_STATUS_DETACHED, MM_CKSN_INVALID);
    Mm_ComDelLai();                                                             /* 删除LAI                                  */
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;
    NAS_MML_InitUeIdTmsiInvalid();
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                            ~MM_MS_ID_IMSI_PRESENT;

    Mm_ComUpdateUsimFileReq();

}


VOS_VOID  NAS_MM_RcvSysInfoPsRestrictRegLaiNoChangeU1(VOS_VOID)
{
    /* 如果LAI不变,更新状态为U1                 */
    if ( MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg )
    {
        Mm_ComNasInfoSav(
                         MM_STATUS_ATTACHED,
                         NAS_MML_GetSimCsSecurityCksn()
                         );

        if ( MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg )
        {
            if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            {
                Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SK_FLG);
            }

            NAS_MM_NotifyAsInfoChgReq();

            g_MmGlobalInfo.ucPowerOnFlg = MM_FALSE;
        }

        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;/* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComRcvSysHandle:INFO: MmServiceState is MM_NORMAL_SERVICE");


        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_SUCCESS,
                                    NAS_MML_REG_FAIL_CAUSE_NULL);            /* 向MMC发送MMCMM_LU_RESULT_IND             */

        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                 NAS_MML_REG_FAIL_CAUSE_NULL);            /* 向MMC发送MMCMM_LU_RESULT_IND             */
        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRcvSysHandle:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
    }
    else
    {
        if ( MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg )
        {
            NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(MM_FALSE, MM_IE_LUT_IMSI_ATTACH);
        }
        else
        {
            Mm_ComNasInfoSav(
                     MM_STATUS_ATTACHED,
                     NAS_MML_GetSimCsSecurityCksn()
                     );
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;                              /* 设置服务状态                             */

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComRcvSysHandle:INFO: MmServiceState is MM_NORMAL_SERVICE");


            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_SUCCESS,
                                        NAS_MML_REG_FAIL_CAUSE_NULL);            /* 向MMC发送MMCMM_LU_RESULT_IND             */
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);            /* 向MMC发送MMCMM_LU_RESULT_IND             */

            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRcvSysHandle:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
    }

    return;
}




VOS_VOID    Mm_ComSysInfoHandleWithLaiNoChange(VOS_UINT8     ucUserSpecificSearchFlg)
{
    VOS_UINT32                          ulLaiChangeFlag;
    VOS_UINT32                          ulIsTestCard;

    ulIsTestCard    = NAS_USIMMAPI_IsTestCard();
    ulLaiChangeFlag =  NAS_MML_IsCsLaiChanged();

    if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
    {
        /* 如果LAI不变,更新状态为U1                 */
        if ( MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg )
        {
            if ( MM_TRUE ==
                g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
            {
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_PERIODIC_UPDATING);
            }
            else
            {
                Mm_ComNasInfoSav(
                                 MM_STATUS_ATTACHED,
                                 NAS_MML_GetSimCsSecurityCksn()
                                 );

                if ( MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg )
                {
                    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
                    {
                        Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SK_FLG);
                    }

                    NAS_MM_NotifyAsInfoChgReq();

                    g_MmGlobalInfo.ucPowerOnFlg = MM_FALSE;
                }

                g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;/* 设置服务状态                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComRcvSysHandle:INFO: MmServiceState is MM_NORMAL_SERVICE");


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);            /* 向MMC发送MMCMM_LU_RESULT_IND             */

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);            /* 向MMC发送MMCMM_LU_RESULT_IND             */

                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRcvSysHandle:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                if ( (MM_TIMER_RUNNING != gstMmTimer[MM_TIMER_T3213].ucTimerStatus)
                  || (VOS_TRUE == ulIsTestCard) )
                {
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
        }
        else
        {
            if ( MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg )
            {
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_IMSI_ATTACH);
            }
            else if ( MM_TRUE ==
                g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
            {
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_PERIODIC_UPDATING);
            }
            /* 由于发起LAU的时候停止了T3212，因此如果T3212没有运行，表示前面已经发起过 */
            else if ((MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
                  && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3212].ucTimerStatus)
                  && (0x0 != gstMmTimer[MM_TIMER_T3212].ulTimerLen)
                  && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3213].ucTimerStatus))
            {
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
            }
            else
            {
                Mm_ComNasInfoSav(
                         MM_STATUS_ATTACHED,
                         NAS_MML_GetSimCsSecurityCksn()
                         );
                g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;                              /* 设置服务状态                             */

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComRcvSysHandle:INFO: MmServiceState is MM_NORMAL_SERVICE");


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);            /* 向MMC发送MMCMM_LU_RESULT_IND             */
                NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);            /* 向MMC发送MMCMM_LU_RESULT_IND             */


                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRcvSysHandle:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");

                if ( (MM_TIMER_RUNNING != gstMmTimer[MM_TIMER_T3213].ucTimerStatus)
                  || (VOS_TRUE == ulIsTestCard) )
                {
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
        }
    }
    else if ( (1 == ucUserSpecificSearchFlg)                        /* 用户发起的指定搜网，且当前不在U1，即使位置区不变，也发起注册 */
            ||(MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg))             /* 刚开机，位置区不变，也发起注册 */
    {
        /* 搜网状态，在手动搜网时候，则清除ATTMPTCNT */
        if ( MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState )
        {
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
        }

        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
    }
    else
    {   /* MM 状态迁回到搜网前的状态 */
        /* 在非U1状态并且周期注册定时器没有运行时,要进行一次LU过程 */
        if ((MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
         && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3212].ucTimerStatus)
         && (0x0 != gstMmTimer[MM_TIMER_T3212].ulTimerLen))
        {
            /* 在NOT UPDATED状态，MM应该发起的是NORMAL LU */
            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;
           NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
        }
        else if (MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState)
        {
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);


            /* 如果T3212在运行且T3211不在运行，则通知MMC当前T3212在运行,否则继续等待T3211超时注册处理 */
            if ( (MM_TIMER_STOP     == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
              && (MM_TIMER_RUNNING  == gstMmTimer[MM_TIMER_T3212].ucTimerStatus) )
            {
                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_T3212_RUNNING);
            }
            else
            {
                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);/* 向MMC发送MMCMM_LU_RESULT_IND,使MMC迁移状态 */

            }

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);              /* 向MMC发送MMCMM_LU_RESULT_IND,使MMC迁移状态 */
        }
        else
        {

        }
    }
}




VOS_VOID Mm_ComRcvSysHandle(VOS_UINT8     ucUserSpecificSearchFlg)
{
    VOS_UINT32                          ulLaiChangeFlag;
    MM_LAI_STRU                         stCurLai;
    NAS_MML_LAI_STRU                   *pstCurrCampLai = VOS_NULL_PTR;

    ulLaiChangeFlag =  NAS_MML_IsCsLaiChanged();


#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MM_RcvSysInfoSurpportLte_PreProc())
    {
        return;
    }
#endif

    pstCurrCampLai = NAS_MML_GetCurrCampLai();

    PS_MEM_SET(&stCurLai, 0x0 ,sizeof(stCurLai));
    NAS_MM_ConvertMmlLaiFormatToMMFormat(pstCurrCampLai, &stCurLai);

    /* 在前状态是attempt tO update时,和上一次驻留的LAI相比较;
       在前状态是limit service时,和上次成功驻留的LAI相比较 */
    if (MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState)
    {
        if (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == NAS_MML_GetCsUpdateStatus())
        {
            if (VOS_FALSE == NAS_MM_IsSameLaiInfo(NAS_MM_GetAttemptUpdateLaiInfo(),
                                                   &stCurLai))

            {
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
                return;
            }
        }
        else if (MM_IDLE_LIMITED_SERVICE == g_MmGlobalInfo.ucNotCampONPreState)
        {
            if (VOS_TRUE == ulLaiChangeFlag)
            {
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
                return;
            }
        }
        else
        {
        }
    }

    if ( g_MmGlobalInfo.ucNtMod == g_MmGlobalInfo.ucNewNtMod )
    {
        if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
        {
            if (VOS_TRUE == NAS_MML_IsCsLaiChanged())
            {
                Mm_TimerStop(MM_TIMER_T3213);
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
            }
            else
            {
                Mm_ComSysInfoHandleWithLaiNoChange(ucUserSpecificSearchFlg);
            }
        }
        else if (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == NAS_MML_GetCsUpdateStatus())
        {
             /* 如果在NOT UPDATE时候，当前LAI不再ATTEMPT LAI中，则发起LAU */
            if (VOS_FALSE == NAS_MM_IsSameLaiInfo(NAS_MM_GetAttemptUpdateLaiInfo(), &stCurLai))
            {
                /* 发送LU REQ */
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
            }
            else
            {
                /* LA 没发生改变 */
                Mm_ComSysInfoHandleWithLaiNoChange(ucUserSpecificSearchFlg);
            }
        }
        else
        {
            NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
        }
    }
    else
    {
        Mm_ComNetModeChange();
    }
}


/*******************************************************************************
  MODULE   : Mm_ComMmConnExist
  FUNCTION : 判断是否有MM连接存在
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_UINT8             ucResult         是否有MM连接存在的结果
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-11  新版作成
*******************************************************************************/
VOS_UINT8 Mm_ComMmConnExist(
                        VOS_VOID
                    )
{
    VOS_UINT8           ucResult = MM_FALSE;                                        /* 是否有MM连接存在的结果                   */
    VOS_UINT8           i        = 0;                                               /* 循环变量                                 */

    for ( i = 0; i < MM_CONN_CM_ENTITY_NUM; i++)
    {                                                                           /* 遍历CM实体个数                           */
        if ( ( MM_CONST_NUM_0 !=
            g_MmGlobalInfo.ConnCtrlInfo[i].aucMMConnExtFlg[0] )
            || ( MM_CONST_NUM_0 !=
            g_MmGlobalInfo.ConnCtrlInfo[i].aucMMConnExtFlg[1] ) )
        {                                                                       /* 有存在的MM连接                           */
            ucResult = MM_TRUE;                                                 /* 返回值设置成有MM连接存在                 */
        }
    }

    return ucResult;
}


/*******************************************************************************
  MODULE   : Mm_ComSaveProcAndCauseVal
  FUNCTION : 存储流程和原因值
  INPUT    : VOS_UINT8             ucProc          流程
             VOS_UINT8             ucCauseVal      原因值
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-15  新版作成
*******************************************************************************/
VOS_VOID Mm_ComSaveProcAndCauseVal(
                                VOS_UINT8             ucProc,
                                VOS_UINT16            usCauseVal
                                )
{
    if ( ( MM_NULL_PROC == g_MmGlobalInfo.ucProc )
        && ( NAS_MML_REG_FAIL_CAUSE_NULL == g_MmGlobalInfo.usCauseVal ) )
    {
        g_MmGlobalInfo.usCauseVal   = usCauseVal;
        g_MmGlobalInfo.ucProc       = ucProc;
    }
    else
    {
        if ( ( MM_NULL_PROC != ucProc )
            && ( NAS_MML_REG_FAIL_CAUSE_NULL != usCauseVal ) )
        {
            g_MmGlobalInfo.usCauseVal   = usCauseVal;
            g_MmGlobalInfo.ucProc       = ucProc;
        }
        else
        {
            if ( MM_AUTH_FAIL_PROC == ucProc )
            {
                g_MmGlobalInfo.usCauseVal   = usCauseVal;
                g_MmGlobalInfo.ucProc       = ucProc;
            }
        }
    }
    return;
}

/*******************************************************************************
  MODULE   : Mm_ComJudgeLimitSvc
  FUNCTION : 判断是否是受限服务状态
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_UINT8             ucResult         是否是受限服务
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-15  新版作成
     2.
*******************************************************************************/
VOS_UINT8 Mm_ComJudgeLimitSvc(
                         VOS_VOID
                         )
{
    VOS_UINT8             ucResult = MM_FALSE;                                      /* 是否是受限服务                           */
    if ( ( MM_LIMITED_SERVICE == g_MmGlobalInfo.ucMmServiceState )
        || ( MM_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucMmServiceState )
        || ( MM_NO_IMSI == g_MmGlobalInfo.ucMmServiceState ) )
    {                                                                           /* 是受限服务                               */
        ucResult = MM_TRUE;                                                     /* 设置是受限服务                           */
    }

    return ucResult;                                                            /* 返回                                     */
}


VOS_VOID Mm_ComFillInCMSncReq(
                            VOS_UINT8                       ucCMSvcType,
                            VOS_UINT8                       ucPrioLeveFlg,
                            MM_MSG_CM_SVC_REQ_STRU      *CmSvcReq
                            )
{
    if (VOS_TRUE == NAS_MML_IsNeedClearCsCksn_UsimDoneGsmCsAuth())
    {
        NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);
        NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_FALSE);
    }
    
    CmSvcReq->MmIeCKSN.ucCksn = NAS_MML_GetSimCsSecurityCksn();           /* 存储CKSN                                 */
    CmSvcReq->MmIeCmSvcType.ucCMSvcType = ucCMSvcType;                          /* Supplementary service activation         */
    NAS_MM_FillMobileID(&(CmSvcReq->MmIeMobileId.MobileID));
    CmSvcReq->ucPrioLeveFlg = ucPrioLeveFlg;                                    /* 没有优先级                               */

    return;
}

VOS_VOID Mm_ComFollowOnProc(
                        VOS_VOID
                        )
{
    MM_MSG_CM_SVC_REQ_STRU              CmSvcReq;                               /* 要发送的CM SERVICE REQ消息               */
    VOS_UINT8                           ucCmSvsType;
    VOS_UINT8                           ucPdType;
    NAS_MM_CONN_CTRL_ENUM_UINT8         i;

    /* 局部变量初始化 */
    ucCmSvsType = 0xFF;
    ucPdType    = 0xFF;
    i           = MM_CONN_CTRL_CC;

    /* 有缓存的合法的CC业务的处理 */
    if (  ( MM_CONST_NUM_7 <
       g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId)
       && ( MM_CONST_NUM_15 >
       g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId)
       && ( MM_TRUE ==
       g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg ) )
    {                                                                           /* 有等待的CC触发的需要建立的MM连接         */
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_NORMAL_SERVICE;             /* 记录收到建立请求时的状态                 */
        if ( MMCC_MO_NORMAL_CALL ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType)
        {                                                                       /* 正常呼叫                                 */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_MO_CALL_EST,
                MM_FALSE, &CmSvcReq);                                           /* 填充CM SERVICE REQUEST结构体             */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg
                = MM_FALSE;                                                     /* 正常呼叫                                 */
            NAS_MML_SetCsEmergencyServiceFlg( VOS_FALSE);
        }
        else
        {                                                                       /* 紧急呼叫                                 */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_EMG_CALL_EST,
                MM_FALSE, &CmSvcReq);                                           /* 填充CM SERVICE REQUEST结构体             */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg
                = MM_TRUE;                                                      /* 紧急呼叫                                 */
            NAS_MML_SetCsEmergencyServiceFlg( VOS_TRUE );
        }
        Mm_ComMsgCmSvcReqSnd(&CmSvcReq);                                        /* 向网侧发送建立MM连接的请求               */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
            (VOS_UINT8)g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            RcvXXEstReq.ulTransactionId;                                        /* 记录正在建立的MM连接                     */
        g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_CALL_CONTROL;                /* 记录正在建立的MM连接的PD                 */
        g_MmGlobalInfo.ucPreState   = WAIT_FOR_RR_CONNECTION_MM_CONNECTION;     /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_OUTGOING_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComFollowOnProc:NORMAL: STATUS is WAIT_FOR_OUTGOING_MM_CONNECTION");
        Mm_TimerStart(MM_TIMER_T3230);                                          /* 启动TIMER3230                            */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;  /* 清除存在缓存的MM连接建立请求的标志       */

        /* 通知MMC当前CS业务已经建立 */
        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);

        /* 更新CS业务连接状态 */
        NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);

        return;
    }

    /* 有缓存的不合法的CC业务的处理 */
    if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
    {
        /* 有等待的CC要求建立的MM连接,TI不合法      */
        Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);   /* 通知CC建立失败  */

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;  /* 清除存在缓存的MM连接建立请求的标志       */

    }

    /* 循环处理CM缓存业务 */
    for ( i = 0 ; i < MM_CONN_CTRL_BUTT; i++ )
    {
        if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[i].RcvXXEstReq.ucFlg )
        {
            if (  ( MM_CONST_NUM_7 <  g_MmGlobalInfo.ConnCtrlInfo[i].RcvXXEstReq.ulTransactionId)
               && ( MM_CONST_NUM_15 > g_MmGlobalInfo.ConnCtrlInfo[i].RcvXXEstReq.ulTransactionId) )
            {
                if ( MM_CONN_CTRL_SS == i )
                {
                    ucCmSvsType = MM_IE_CM_SVC_TYPE_SS_ACT;
                    ucPdType    = MM_IE_PD_NON_CALL_RLT_SS_MSG;
                }
                else if ( MM_CONN_CTRL_SMS == i )
                {
                    ucCmSvsType = MM_IE_CM_SVC_TYPE_SMS;
                    ucPdType    = MM_IE_PD_SMS_MSG;
                }
                else
                {
                    /* 非SS/SMS消息，则异常处理 */
                    break;
                }


                g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_NORMAL_SERVICE;         /* 记录收到建立请求时的状态                 */
                Mm_ComFillInCMSncReq(ucCmSvsType,
                    MM_FALSE, &CmSvcReq);                                           /* 填充CM SERVICE REQUEST结构体             */
                Mm_ComMsgCmSvcReqSnd(&CmSvcReq);                                    /* 向网侧发送建立MM连接的请求               */

                g_MmGlobalInfo.ConnCtrlInfo[i].ucMMConnEstingTI =
                (VOS_UINT8)g_MmGlobalInfo.ConnCtrlInfo[i].RcvXXEstReq.ulTransactionId;                                        /* 记录正在建立的MM连接                     */
                g_MmGlobalInfo.ucMMConnEstingPD = ucPdType;                         /* 记录正在建立的MM连接的PD                 */
                g_MmGlobalInfo.ucPreState   = WAIT_FOR_RR_CONNECTION_MM_CONNECTION; /* 记录迁移之前的状态                       */
                Mm_ComSetMmState(WAIT_FOR_OUTGOING_MM_CONNECTION);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComFollowOnProc:NORMAL: STATUS is WAIT_FOR_OUTGOING_MM_CONNECTION");
                Mm_TimerStart(MM_TIMER_T3230);                                      /* 启动TIMER3230                            */

                /* 清除存在缓存的MM连接建立请求的标志 */
                g_MmGlobalInfo.ConnCtrlInfo[i].RcvXXEstReq.ucFlg = MM_FALSE;

                /* 通知MMC当前CS业务已经建立 */
                Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);

                /* 更新CS业务连接状态 */
                NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);

                /* 处理CM 缓存结束 */
                return;
            }

            /* 有缓存的非法的CM业务的处理 */
            if ( MM_CONN_CTRL_SS == i )
            {
                Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[i].RcvXXEstReq.ulTransactionId,
                               NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
            }
            else if ( MM_CONN_CTRL_SMS == i )
            {
                Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[i].
                    RcvXXEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                        /* 通知SMS建立失败                          */
            }
            else
            {
            }

            /* 清除存在缓存的MM连接建立请求的标志 */
            g_MmGlobalInfo.ConnCtrlInfo[i].RcvXXEstReq.ucFlg = MM_FALSE;

        }

    }

    /* 如果当前没有缓存或者缓存的消息TI非法，则进行状态迁移 */
    g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_NORMAL_SERVICE;        /* 进入空闲的状态                           */
    Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );        /* MM连接流程                               */
    g_MmGlobalInfo.ucPreState   = LOCATION_UPDATING_INITIATED;              /* 记录迁移之前的状态                       */
    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComFollowOnProc:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
    Mm_TimerStart(MM_TIMER_T3240);

    return;
}

/*******************************************************************************
  MODULE   : Mm_ComChkAttDelay
  FUNCTION : 检查是否有保留的ATTACH
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-15  新版作成
     2.
*******************************************************************************/
VOS_VOID Mm_ComChkAttDelay( )
{
    if ( MM_TRUE == g_MmGlobalInfo.ucAttDelay )
    {
        if ( ( MM_IDLE_LIMITED_SERVICE == g_MmGlobalInfo.ucState )
            && ( MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState )
            )
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
            Mm_ComLuOnly();
        }
        g_MmGlobalInfo.ucAttDelay = MM_FALSE;
    }
}


VOS_VOID Mm_ComProcCauseProcess_Handling_LU_PROC(VOS_VOID)
{
    if ( NAS_MML_REG_FAIL_CAUSE_NULL == g_MmGlobalInfo.usCauseVal )
    {
        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_LU_PROC:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");

        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);

        if (MM_DETACH_NEED_DELAY == g_MmGlobalInfo.ucDetachType)
        {
            Mm_TimerStop(MM_TIMER_PROTECT_DETACH);
            g_MmGlobalInfo.ucDetachType = MM_DETACH_TYPE_BUTT;
            Mm_Cell_S3_E23(VOS_NULL_PTR);
        }
    }
    else
    {
        Mm_ComLuCauseHandle(g_MmGlobalInfo.usCauseVal);                     /* 调用原因值的处理                         */
    }

    return;
}


VOS_VOID Mm_ComProcCauseProcess_Handling_MM_GMM_ATTACH_PROC(VOS_VOID)
{
    switch ( g_MmGlobalInfo.usCauseVal )
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_GMM_ATTACH_PROC:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_GMM_ATTACH_PROC:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        Mm_ComGmmAttachCauseHandle(g_MmGlobalInfo.usCauseVal);              /* 调用原因值的处理                         */
        break;
    default:
        break;
    }

    return;
}


VOS_VOID Mm_ComProcCauseProcess_Handling_GMM_RAU_PROC(VOS_VOID)
{
    switch ( g_MmGlobalInfo.usCauseVal )
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_GMM_RAU_PROC:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        Mm_ComGmmRauCauseHandle(g_MmGlobalInfo.usCauseVal);                 /* 调用原因值的处理                         */
        break;
    default:
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComProcCauseProcess_Handling_MM_GMM_SR_PROC
 *  FUNCTION : Mm_ComProcCauseProcess函数降复杂度: MM_GMM_SR_PROC处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
 ************************************************************************/
VOS_VOID Mm_ComProcCauseProcess_Handling_MM_GMM_SR_PROC(VOS_VOID)
{
    switch ( g_MmGlobalInfo.usCauseVal )
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        /* 参考4.5.1.1 */
        Mm_ComLuCauseHandle(g_MmGlobalInfo.usCauseVal);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_GMM_SR_PROC:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        Mm_ComGmmSrCauseHandle(g_MmGlobalInfo.usCauseVal);                  /* 调用原因值的处理                         */
        break;
    default:
        break;
    }

    return;
}


VOS_VOID Mm_ComProcCauseProcess_Handling_MM_NET_DETACH_PROC(VOS_VOID)
{


    switch ( g_MmGlobalInfo.usCauseVal )
    {
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_NET_DETACH_PROC:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        Mm_ComNetDetachCauseHandle(g_MmGlobalInfo.usCauseVal);              /* 调用原因值的处理                         */
        break;
    case NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI:
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComProcCauseProcess_Handling_MM_NET_DETACH_PROC:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

        Mm_ComToU2Handle();

        if (VOS_TRUE == NAS_MM_IsDisableGprsCombineAttach())
        {
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
        break;
    default:
        break;
    }

    return;
}


VOS_VOID Mm_ComProcCauseProcess_Handling_MM_MM_CONN_PROC(VOS_VOID)
{
    VOS_UINT8                           ucPsSimStatus;

    ucPsSimStatus = NAS_MML_GetSimPsRegStatus();

    switch ( g_MmGlobalInfo.usCauseVal )
    {
    case NAS_MML_REG_FAIL_CAUSE_NULL:
        Mm_ComSetMmState(g_MmGlobalInfo.ucStaAfterWaitForNwkCmd);
        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_MM_CONN_PROC:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
        break;
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR:

        /* 当前CS有效，LAI没有禁止 */
        if ( (VOS_TRUE == NAS_MML_GetSimCsRegStatus())
          && (( MMCMM_NO_FORBIDDEN == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg )
           || ( MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg )))
        {
            /*
            24.008 4.5.1.1 CM SERVICE REJECT Process: If cause value #4
            is received, If subsequently the RR connection is released
            or aborted, this will force the mobile station to initiate
            a normal location updating.
            */
            if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
             && (VOS_TRUE == ucPsSimStatus)
             && (MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
            {                                                               /* 判断是否为A+I模式                        */
                /* MM收到CM Service Reject消息时已经通知GMM,GMM在收到
                CM_SERVICE_IND消息指示无CS服务时发起 COMBINED_RALAU_WITH_IMSI_ATTACH*/
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_MM_CONN_PROC:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
                Mm_ComLuOnly();                                             /* LU REQ                                   */
            }
        }
        else
        {
            /* 释放当前连接 */
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);

            /* 转到连接建立前的状态 */
            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_MM_CONN_PROC:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    default:
        break;
    }

    return;
}


VOS_VOID Mm_ComProcCauseProcess_Handling_MM_MM_NET_ABORT(VOS_VOID)
{
    switch ( g_MmGlobalInfo.usCauseVal )
    {
    case NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE:
        switch ( g_MmGlobalInfo.ucMmServiceState )
        {
        case MM_NORMAL_SERVICE:
            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_MM_NET_ABORT:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
            break;
        case MM_LIMITED_SERVICE:
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_MM_NET_ABORT:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            break;
        case MM_ATTEMPTING_TO_UPDATE:
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_MM_NET_ABORT:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
            break;
        case MM_NO_IMSI:
            Mm_ComSetMmState(MM_IDLE_NO_IMSI);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_MM_NET_ABORT:NORMAL: STATUS is MM_IDLE_NO_IMSI");
            break;
        default:
            break;
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_MM_NET_ABORT:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    default:
        break;
    }

    return;
}


VOS_VOID Mm_ComProcCauseProcess_Handling_MM_IMSI_DETACH(VOS_VOID)
{
    Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_IMSI_DETACH:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
    return;
}


VOS_VOID Mm_ComProcCauseProcess( )
{
    switch ( g_MmGlobalInfo.ucProc )
    {
    case MM_NULL_PROC:
        break;
    case MM_LU_PROC:
        Mm_ComProcCauseProcess_Handling_LU_PROC();
        break;
    case MM_GMM_ATTACH_PROC:
        Mm_ComProcCauseProcess_Handling_MM_GMM_ATTACH_PROC();
        break;
    case MM_GMM_RAU_PROC:
        Mm_ComProcCauseProcess_Handling_GMM_RAU_PROC();
        break;
    case MM_COMB_ATTACH_PROC:
        break;
    case MM_COMB_RAU_PROC:
        break;
    case MM_GMM_SR_PROC:
        Mm_ComProcCauseProcess_Handling_MM_GMM_SR_PROC();
        break;
    case MM_NET_DETACH_PROC:
        Mm_ComProcCauseProcess_Handling_MM_NET_DETACH_PROC();
        break;
    case MM_AUTH_FAIL_PROC:
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    case MM_MM_CONN_PROC:
        Mm_ComProcCauseProcess_Handling_MM_MM_CONN_PROC();
        break;
    case MM_MM_NET_ABORT:
        Mm_ComProcCauseProcess_Handling_MM_MM_NET_ABORT();
        break;
    case MM_IMSI_DETACH:
        Mm_ComProcCauseProcess_Handling_MM_IMSI_DETACH();
        break;
    case MM_MM_MS_AUTH_FAIL_PROC:

        Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);

        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess:NORMAL: STATUS is ",g_MmGlobalInfo.ucState);
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComProcCauseProcess:WARNING: ucProc Abnormal");
        break;
    }
    Mm_ComProcCauseClear();
}



VOS_VOID Mm_ComDelLai()
{
    NAS_MML_LAI_STRU                   *pstCsSuccLai;

    pstCsSuccLai    = NAS_MML_GetCsLastSuccLai(  );

    pstCsSuccLai->aucLac[0] = NAS_MML_LAC_LOW_BYTE_INVALID;
    pstCsSuccLai->aucLac[1] = NAS_MML_LAC_HIGH_BYTE_INVALID;



    pstCsSuccLai->ucRac = NAS_MML_RAC_INVALID;
}

/*******************************************************************************
  MODULE   : Mm_ComProcCauseClear
  FUNCTION : 清除原因值和流程
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1. 张志勇   2004.04.26 新规作成
*******************************************************************************/

VOS_VOID Mm_ComProcCauseClear()
{
    g_MmGlobalInfo.ucProc       = MM_NULL_PROC;                                 /* 设置流程                                 */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmServiceState is MM_NULL_PROC \r " );*/
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComProcCauseClear:INFO: MmServiceState is MM_NULL_PROC");
    g_MmGlobalInfo.usCauseVal   = NAS_MML_REG_FAIL_CAUSE_NULL;                            /* 记录原因值                               */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:mmCauseVal is NAS_MML_REG_FAIL_CAUSE_NULL \r " );*/
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComProcCauseClear:INFO: mmCauseVal is NAS_MML_REG_FAIL_CAUSE_NULL");
}


VOS_UINT8    Mm_ComChkLu( )
{
    VOS_UINT8                           ucRet = MM_FALSE;

    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;


    /* 取得当前的链接信息 */
    pstConnStatus = NAS_MML_GetConnStatus();

    if (VOS_TRUE != pstConnStatus->ucRrcStatusFlg)
    {
        return MM_FALSE;
    }

    ucRet = NAS_MM_ProcessLuAfterCsConnectNotExist();

    return ucRet;
}



/*******************************************************************************
  Module:   Mm_TimerPause
  Function: MM使用定时器暂停
  Input:    VOS_UINT8       ucTimerId   Timer ID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2005.01.25  新版做成
*******************************************************************************/
VOS_VOID Mm_TimerPause( VOS_UINT8   ucTimerId )
{
    VOS_UINT8   i;

    if ( MM_TIMER_STOP_ALL == ucTimerId )
    {
        for ( i = 0; i < MM_TIMER_MAX; i++ )
        {
            if ( MM_TIMER_RUNNING == gstMmTimer[i].ucTimerStatus )
            {
                if( VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                    Mm_StopRelTimer(WUEPS_PID_MM, i, &gstMmTimer[i].hTimer))
                {                                                               /* 暂停失败：已经暂停或Timer不存在          */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerPause:WARNING: TIMER STOP ERROR!");
                }

                gstMmTimer[i].ucTimerStatus = MM_TIMER_PAUSE;
            }
        }
    }
    else
    {
        if ( MM_TIMER_RUNNING == gstMmTimer[ucTimerId].ucTimerStatus)
        {                                                                       /* 该timer已经启动                          */

            if ( VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                Mm_StopRelTimer(WUEPS_PID_MM, ucTimerId, &gstMmTimer[ucTimerId].hTimer) )
            {                                                                   /* 暂停失败                                 */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerPause:WARNING: TIMER STOP ERROR!");
            }

            gstMmTimer[ucTimerId].ucTimerStatus = MM_TIMER_PAUSE;                /* 清Timer的启动标志                        */
        }
    }
}

/*******************************************************************************
  Module:   Mm_TimerResume
  Function: MM使用定时器恢复
  Input:    VOS_UINT8       ucTimerId   Timer ID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2005.01.25  新版做成
*******************************************************************************/
VOS_VOID Mm_TimerResume( VOS_UINT8   ucTimerId )
{
    VOS_UINT8   i;

    if ( MM_TIMER_STOP_ALL == ucTimerId )
    {
        for ( i = 0; i < MM_TIMER_MAX; i++ )
        {
            if ( MM_TIMER_PAUSE == gstMmTimer[i].ucTimerStatus )
            {




                if( VOS_OK != Mm_StartRelTimer(
                                           &gstMmTimer[i].hTimer,     /* 存放TIMER ID的地址                       */
                                           WUEPS_PID_MM,
                                           gstMmTimer[i].ulTimerLen,         /* 时长                                     */
                                           (VOS_UINT32)i,            /* 消息队列的ID                             */
                                           gstMmTimer[i].ulParam,               /* 消息地址                                 */
                                           gstMmTimer[i].ucMode          /* 消息优先级                               */
                                           ))
                {                                                               /* 恢复失败：已经恢复或Timer不存在          */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_TimerResume:ERROR: TIMER START ERROR!");
                }

                gstMmTimer[i].ucTimerStatus = MM_TIMER_RUNNING;
            }
        }
    }
    else
    {
        if ( MM_TIMER_PAUSE == gstMmTimer[ucTimerId].ucTimerStatus)
        {                                                                       /* 该timer已经启动                          */






            if ( VOS_OK != Mm_StartRelTimer(
                                           &gstMmTimer[ucTimerId].hTimer,     /* 存放TIMER ID的地址                       */
                                           WUEPS_PID_MM,
                                           gstMmTimer[ucTimerId].ulTimerLen,         /* 时长                                     */
                                           (VOS_UINT32)ucTimerId,            /* 消息队列的ID                             */
                                           gstMmTimer[ucTimerId].ulParam,               /* 消息地址                                 */
                                           gstMmTimer[ucTimerId].ucMode          /* 消息优先级                               */
                                           ) )
            {                                                                   /* 暂停失败                                 */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_TimerResume:ERROR: TIMER START ERROR!");
            }

            gstMmTimer[ucTimerId].ucTimerStatus = MM_TIMER_RUNNING;              /* 清Timer的启动标志                        */
        }
    }
}



VOS_VOID Mm_ComT3212(VOS_UINT32  ulT3212Timer)
{
    VOS_UINT32                          ulTemp;
    VOS_UINT32                          ulTemp1;
    VOS_UINT32                          ulTempRemain;

    switch ( g_MmGlobalInfo.ucState )
    {
    case MM_STATE_NULL:
    case MM_IDLE_NO_CELL_AVAILABLE:
    case MM_IDLE_LIMITED_SERVICE:
    case MM_IDLE_PLMN_SEARCH:
    case MM_IDLE_PLMN_SEARCH_NORMAL_SERVICE:

        gstMmTimer[MM_TIMER_T3212].ulTimerLen = ulT3212Timer;                    /* T3212时长的赋值                          */

        break;


    default:
        gstMmTimer[MM_TIMER_T3212].ulTimerLen = ulT3212Timer;                    /* T3212时长的赋值                          */

        if ( MM_TIMER_RUNNING == gstMmTimer[MM_TIMER_T3212].ucTimerStatus )
        {                                                                       /* 如果T3212正在运行中                      */
            ulTemp1 = ulT3212Timer;


            ulTempRemain = MM_CONST_NUM_0;

            if (VOS_NULL_PTR != gstMmTimer[MM_TIMER_T3212].hTimer)
            {
                /* hTimer 为空时，说明此定时器已超时或停止,不为空时，才取其剩余长度 */
                if (VOS_OK != VOS_GetRelTmRemainTime(&(gstMmTimer[MM_TIMER_T3212].hTimer), &ulTempRemain))
                {
                    ulTempRemain = MM_CONST_NUM_0;
                }
            }

            ulTemp = ulTempRemain * MM_TIMER_TICK;


            if ( VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                    Mm_StopRelTimer(WUEPS_PID_MM, MM_TIMER_T3212, &gstMmTimer[MM_TIMER_T3212].hTimer ) )
            {                                                                   /* 暂停失败                                 */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComT3212:WARNING: TIMER STOP FAILURE!");
            }

            if ( MM_CONST_NUM_0 == ( ulTemp%ulTemp1 ) )
            {
                ulTemp = 1000;
            }
            else
            {
                ulTemp = (VOS_UINT32)ulTemp%ulTemp1;
            }
            if (VOS_OK != Mm_StartRelTimer(
                                           &gstMmTimer[MM_TIMER_T3212].hTimer,     /* 存放TIMER ID的地址                       */
                                           WUEPS_PID_MM,
                                           ulTemp,         /* 时长                                     */
                                           MM_TIMER_T3212,            /* 消息队列的ID                             */
                                           gstMmTimer[MM_TIMER_T3212].ulParam,               /* 消息地址                                 */
                                           gstMmTimer[MM_TIMER_T3212].ucMode          /* 消息优先级                               */
                                           ) )
            {                                                                   /* 启动失败：已经恢复或Timer不存在          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComT3212:WARNING: TIMER START FAILURE!");
            }


        }
        else
        {
            ulTemp1 = ulT3212Timer;

            /* 随机种子 */
            VOS_SetSeed(VOS_GetTick());

            NAS_MM_SetNetworkT3212RandLen(VOS_Rand(ulTemp1));

        }
        break;
    }

}


VOS_UINT32  NAS_MM_QryTimerStatus(VOS_UINT8 ucTimerId)
{

    if ( MM_TIMER_STOP  != gstMmTimer[ucTimerId].ucTimerStatus )
    {
        return MM_TIMER_RUNNING;
    }
    else
    {
        return MM_TIMER_STOP;
    }

}

/*******************************************************************************
  Module:   Mm_TimerStart
  Function: MM使用定时器启动
  Input:    VOS_UINT8       ucTimerId   Timer ID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2005.01.25  新版做成
*******************************************************************************/
VOS_VOID Mm_TimerStart( VOS_UINT8   ucTimerId )
{
    VOS_UINT32 ulResult;

    if ( MM_TIMER_STOP ==  gstMmTimer[ucTimerId].ucTimerStatus )
    {
        if ( MM_TIMER_T3212 == ucTimerId )
        {                                                                       /* 如果为T3212                              */
            if ( MM_CONST_NUM_0 != gstMmTimer[ucTimerId].ulTimerLen )
            {
                if ( MM_CONST_NUM_0 != NAS_MM_GetNetworkT3212RandLen())
                {
                    ulResult = Mm_StartRelTimer(
                                           &gstMmTimer[ucTimerId].hTimer,     /* 存放TIMER ID的地址                       */
                                           WUEPS_PID_MM,
                                           NAS_MM_GetNetworkT3212RandLen(),         /* 时长                                     */
                                           MM_TIMER_T3212,            /* 消息队列的ID                             */
                                           gstMmTimer[ucTimerId].ulParam,               /* 消息地址                                 */
                                           gstMmTimer[ucTimerId].ucMode          /* 消息优先级                               */
                                           );                                   /* 创建支持消息的定时器                     */
                    if ( VOS_OK != ulResult )
                    {                                                           /* 创建失败                                 */
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerStart:WARNING: TIMER CREATE FAILURE!");
                        return;
                    }

                    NAS_MM_SetNetworkT3212RandLen(MM_CONST_NUM_0);
                }
                else
                {
                    ulResult = Mm_StartRelTimer(
                                           &gstMmTimer[ucTimerId].hTimer,     /* 存放TIMER ID的地址                       */
                                           WUEPS_PID_MM,
                                           gstMmTimer[ucTimerId].ulTimerLen,         /* 时长                                     */
                                           MM_TIMER_T3212,            /* 消息队列的ID                             */
                                           gstMmTimer[ucTimerId].ulParam,               /* 消息地址                                 */
                                           gstMmTimer[ucTimerId].ucMode          /* 消息优先级                               */
                                           );                                                /* 创建支持消息的定时器                     */
                    if ( VOS_OK != ulResult )
                    {                                                           /* 创建失败                                 */
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerStart:WARNING: TIMER CREATE FAILURE!");
                        return;
                    }

                }

                gstMmTimer[ucTimerId].ucTimerStatus = MM_TIMER_RUNNING;          /* 置Timer的启动标志                        */
                /*WUEPS_TRACE(MM_LOG_LEVEL_6,"\nMM StartTimer: %d\r",ucTimerId);*/
                PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_TimerStart:INFO: StartTimer: ", ucTimerId);
            }
        }
        else
        {
            if (MM_TIMER_PROTECT_SIGNALLING  == ucTimerId)
            {
                if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
                {
                    gstMmTimer[MM_TIMER_PROTECT_SIGNALLING].ulTimerLen = MM_TIMER_PROTECT_G_SIGNALLING_VALUE;
                }
                else
                {
                    gstMmTimer[MM_TIMER_PROTECT_SIGNALLING].ulTimerLen = MM_TIMER_PROTECT_W_SIGNALLING_VALUE;
                }
            }
            ulResult = Mm_StartRelTimer(  &gstMmTimer[ucTimerId].hTimer,     /* 存放TIMER ID的地址                       */
                                           WUEPS_PID_MM,
                                           gstMmTimer[ucTimerId].ulTimerLen,         /* 时长                                     */
                                           (VOS_UINT32)ucTimerId,                       /* 消息队列的ID                             */
                                           gstMmTimer[ucTimerId].ulParam,               /* 消息地址                                 */
                                           gstMmTimer[ucTimerId].ucMode          /* 消息优先级                               */
                                           );                                             /* 创建支持消息的定时器                     */
            if ( VOS_OK != ulResult )                        /* 创建失败                                 */
            {
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerStart:WARNING: TIMER CREATE FAILURE!");
                return;
            }
            gstMmTimer[ucTimerId].ucTimerStatus = MM_TIMER_RUNNING;              /* 置Timer的启动标志                        */
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_TimerStart:INFO: StartTimer: ", ucTimerId);
        }
    }

}

VOS_UINT32 NAS_MM_IsTimerIdInTimerList(
    VOS_UINT8                           ucTimerId,
    VOS_UINT8                           ucTimerNum,
    VOS_UINT8                          *pucTimer
)
{
    VOS_UINT8                           ucIndex;

    for ( ucIndex = 0 ; ucIndex < ucTimerNum; ucIndex++ )
    {
        if ( ucTimerId == *(pucTimer + ucIndex) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_VOID NAS_MM_TimerStopExceptSpecialTimers(
    VOS_UINT8                           ucTimerNum,
    VOS_UINT8                          *pucTimer
)
{
    VOS_UINT8                           i;

    for ( i = 0; i < MM_TIMER_MAX; i++ )
    {
        if ( VOS_TRUE == NAS_MM_IsTimerIdInTimerList(i, ucTimerNum, pucTimer) )
        {
            continue;
        }


        if ( MM_TIMER_STOP != gstMmTimer[i].ucTimerStatus )
        {
            if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
            Mm_StopRelTimer(WUEPS_PID_MM, i, &gstMmTimer[i].hTimer))
            {                                                               /* 停止失败：已经停止或Timer不存在          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerStop:WARNING: TIMER STOP FAILURE!");
            }

            if (MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE == i)
            {
                NAS_MML_SetCsfbMtPagingTimerStatus(NAS_MML_MT_CSFB_PAGING_TIMER_STOP);
            }

            gstMmTimer[i].ucTimerStatus = MM_TIMER_STOP;

            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_TimerStop:INFO: StopTimer: ", i);
        }
    }
}



VOS_VOID Mm_TimerStop( VOS_UINT8   ucTimerId )
{
    VOS_UINT8   i;

    if ( MM_TIMER_STOP_ALL == ucTimerId )
    {
        /* 直接将CSFB 的保护定时器状态置为stop */
        NAS_MML_SetCsfbMtPagingTimerStatus(NAS_MML_MT_CSFB_PAGING_TIMER_STOP);

        for ( i = 0; i < MM_TIMER_MAX; i++ )
        {
            if ( MM_TIMER_STOP != gstMmTimer[i].ucTimerStatus )
            {
                if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                Mm_StopRelTimer(WUEPS_PID_MM, i, &gstMmTimer[i].hTimer))
                {                                                               /* 停止失败：已经停止或Timer不存在          */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerStop:WARNING: TIMER STOP FAILURE!");
                }

                gstMmTimer[i].ucTimerStatus = MM_TIMER_STOP;
                PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_TimerStop:INFO: StopTimer: ", i);
            }
        }
    }
    else if ( ucTimerId < MM_TIMER_MAX )
    {
        if ( MM_TIMER_STOP != gstMmTimer[ucTimerId].ucTimerStatus )
        {
            if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                    Mm_StopRelTimer(WUEPS_PID_MM, ucTimerId, &gstMmTimer[ucTimerId].hTimer))
            {                                                                   /* 停止失败：已经停止或Timer不存在          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerStop:WARNING: TIMER STOP FAILURE!");
            }

            gstMmTimer[ucTimerId].ucTimerStatus = MM_TIMER_STOP;
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_TimerStop:INFO: StopTimer: ", ucTimerId);
        }
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerStop:WARNING: TIMER ID ERROR!");
    }

}

VOS_VOID Mm_ComAuthMsRej()
{
    g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt = 0;
    g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause = MM_AUTHEN_NO_CAUSE;
    Mm_TimerStop(MM_TIMER_T3214);
    Mm_TimerStop(MM_TIMER_T3216);

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);


    Mm_SndRrRelReq(RRC_CELL_BARRED);
    switch(g_MmGlobalInfo.ucState)
    {
    case WAIT_FOR_OUTGOING_MM_CONNECTION:
        Mm_TimerStart(MM_TIMER_T3230);
        break;
    case MM_CONNECTION_ACTIVE:
    case WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION:
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                          */
        /* " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );    */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComAuthMsRej:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
        Mm_TimerStart(MM_TIMER_T3240);
        Mm_ComSaveProcAndCauseVal(
                                  MM_MM_MS_AUTH_FAIL_PROC,
                                  NAS_MML_REG_FAIL_CAUSE_NULL);
        break;
    case WAIT_FOR_NETWORK_COMMAND:
        break;
    case LOCATION_UPDATING_INITIATED:
        Mm_TimerStart(MM_TIMER_T3210);
        break;
    case LOCATION_UPDATE_REJECTED:
        break;
    case IMSI_DETACH_INITIATED:
        Mm_TimerStart(MM_TIMER_T3220);
        break;
    case PROCESS_CM_SERVICE_PROMPT:
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                          */
        /* " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );    */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComAuthMsRej:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
        Mm_TimerStart(MM_TIMER_T3240);
        Mm_ComSaveProcAndCauseVal(
                                  MM_MM_MS_AUTH_FAIL_PROC,
                                  NAS_MML_REG_FAIL_CAUSE_NULL);
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComAuthMsRej:WARNING: g_MmGlobalInfo.ucState Abnormal");
        break;
    }
}



VOS_UINT8 Mm_ComTempIdJudge()
{
    VOS_UINT8 ucRet = MM_TRUE;

    if ( ( MM_MS_ID_TMSI_PRESENT ==
        ( g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg
/*                                & MM_MS_ID_IMSI_PRESENT ) ) && */
                                & MM_MS_ID_TMSI_PRESENT ) ) &&
         ( MM_MS_ID_TMSI_PRESENT ==
        ( g_MmMsgLuAccpt.MmIeMobileId.MobileID.ucMsIdFlg
/*                                & MM_MS_ID_IMSI_PRESENT ) ) ) */
                                & MM_MS_ID_TMSI_PRESENT ) ) )
    {
        if ( 0 == VOS_MemCmp(NAS_MML_GetUeIdTmsi(), g_MmMsgLuAccpt.MmIeMobileId.MobileID.aucTmsi, NAS_MML_MAX_TMSI_LEN))
        {
            ucRet = MM_FALSE;
        }

    }
    return ucRet;
}

VOS_VOID Mm_Com_UsimAuthenticationCnfChgFormat(
                               USIMM_AUTHENTICATION_CNF_STRU *pUsimMsg
                               )
{
    VOS_UINT8                           i = 0;
    VOS_UINT8*                          pPointer;
    VOS_UINT8                           ucCause;
    USIMM_TELECOM_AUTH_CNF_STRU        *pstTELECnf = VOS_NULL_PTR;

    pstTELECnf = &(pUsimMsg->uCnfData.stTELECnf);

    /* UMTS AUTH SUCCESS or GSM AUTH SUCCESS */
    if ((USIMM_AUTH_UMTS_SUCCESS == pUsimMsg->enResult)
     || (USIMM_AUTH_GSM_SUCCESS == pUsimMsg->enResult))
    {
        NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_AUTH_SUCCESS,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        g_AgentUsimAuthCnf.ucCheckRst = AGENT_AUTH_RST_SUCCESS;

        pPointer = pstTELECnf->aucAuthRes;

        if (pPointer[0] <= 4)
        {
            for ( i = 0; i < pPointer[0]; i++)
            {
                g_AgentUsimAuthCnf.aucResponse[i] = pPointer[i+1];
            }
            for ( ;i < 4; i++ )
            {
                g_AgentUsimAuthCnf.aucResponse[i] = 0xFF;
            }

            g_AgentUsimAuthCnf.ucExtRspLength = 0x0;
        }
        else
        {
            for ( i = 0; i < 4; i++)
            {
                g_AgentUsimAuthCnf.aucResponse[i] = pPointer[i+1];
            }

            if ( pPointer[0] > 16 )
            {
                g_AgentUsimAuthCnf.ucExtRspLength = 12;
            }
            else
            {
                g_AgentUsimAuthCnf.ucExtRspLength = pPointer[0] - 4;
            }

            for (i=0; i<g_AgentUsimAuthCnf.ucExtRspLength; i++)
            {
                g_AgentUsimAuthCnf.aucExtResponse[i] = pPointer[i+5];
            }
        }

        if (MM_ZERO == pstTELECnf->aucGsmKc[0]) /* 鉴权结果不包含 KC */
        {
            g_AgentUsimAuthCnf.ucKcLength = 0;
        }
        else /* 鉴权结果包含 KC, 读取 KC 值 */
        {
            for (i=0; i<8; i++)
            {
                /* skip the first length byte */
                g_AgentUsimAuthCnf.aucKc[i] = pstTELECnf->aucGsmKc[i+1];
            }

            /* get KC length from the first byte */
            g_AgentUsimAuthCnf.ucKcLength   = pstTELECnf->aucGsmKc[0];
        }

        for (i=0; i<16; i++)
        {
            /* skip the first length byte */
            g_AgentUsimAuthCnf.aucCipheringKey[i] = pstTELECnf->aucCK[i+1];

            /* skip the first length byte */
            g_AgentUsimAuthCnf.aucIntegrityKey[i] = pstTELECnf->aucIK[i+1];
        }
    }
    else if (USIMM_AUTH_MAC_FAILURE == pUsimMsg->enResult)
    {
        g_AgentUsimAuthCnf.ucCheckRst = AGENT_AUTH_RST_FAILURE;
        g_AgentUsimAuthCnf.ucFailureCause = AGENT_AUTH_FAIL_MAC_CODE;
        ucCause = NAS_OM_MM_CAUSE_MAC_FAILURE;
        NAS_MM_SndMmcSimAuthFailInfo(NAS_MML_SIM_AUTH_FAIL_MAC_FAILURE);
    }
    else if (USIMM_AUTH_SYNC_FAILURE == pUsimMsg->enResult)
    {
        g_AgentUsimAuthCnf.ucFailParaLength = 14;

        pPointer = pstTELECnf->aucAuts;
        if ( pstTELECnf->aucAuts[0] > 14 )
        {
            for ( i = 0; i < g_AgentUsimAuthCnf.ucFailParaLength; i++)
            {
                g_AgentUsimAuthCnf.aucFailPara[i] = pPointer[i+1];
            }
        }
        else
        {
            for ( i = 0; i < pstTELECnf->aucAuts[0]; i++)
            {
                g_AgentUsimAuthCnf.aucFailPara[i] = pPointer[i+1];
            }
            if ( pstTELECnf->aucAuts[0] < 14 )
            {
                for ( ;i < 14; i++ )
                {
                    g_AgentUsimAuthCnf.aucFailPara[i] = 0xFF;
                }
            }
        }

        g_AgentUsimAuthCnf.ucCheckRst = AGENT_AUTH_RST_FAILURE;
        g_AgentUsimAuthCnf.ucFailureCause = AGENT_AUTH_FAIL_SQN;
        ucCause = NAS_OM_MM_CAUSE_SYNCH_FAILURE;
        NAS_MM_SndMmcSimAuthFailInfo(NAS_MML_SIM_AUTH_FAIL_SYNC_FAILURE);
    }
    else if (USIMM_AUTH_GSM_OTHER_FAILURE == pUsimMsg->enResult) /* GSM AUTH FAILURE */
    {
        g_AgentUsimAuthCnf.ucCheckRst     = AGENT_AUTH_RST_FAILURE;
        g_AgentUsimAuthCnf.ucFailureCause = USIM_GAS_AUTH_FAIL;
        ucCause = NAS_OM_MM_CAUSE_AUT_GSM_OTHER_FAILURE;
        NAS_MM_SndMmcSimAuthFailInfo(NAS_MML_SIM_AUTH_FAIL_GSM_OTHER_FAILURE);
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Com_UsimAuthenticationCnfChgFormat:WARNING: ucResult Abnormal");
        /* WUEPS_ASSERT(0); */
        g_AgentUsimAuthCnf.ucCheckRst     = AGENT_AUTH_RST_FAILURE;
        g_AgentUsimAuthCnf.ucFailureCause = USIM_AUTH_FAIL_UNKNOWN;
        ucCause = NAS_OM_MM_CAUSE_AUT_UMTS_OTHER_FAILURE;
        NAS_MM_SndMmcSimAuthFailInfo(NAS_MML_SIM_AUTH_FAIL_UMTS_OTHER_FAILURE);
        NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_AUTH_FAILURE,
                        &ucCause, NAS_OM_EVENT_AUTH_FAIL_LEN);
        return ;
    }

    if(AGENT_AUTH_RST_FAILURE == g_AgentUsimAuthCnf.ucCheckRst)
    {
        NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_AUTH_FAILURE,
                        &ucCause, NAS_OM_EVENT_AUTH_FAIL_LEN);
    }
}


VOS_VOID Mm_ComNetModeChange()
{
    VOS_UINT8                               ucProcessLu;

    VOS_UINT32                          ulLaiChangeFlag;

    ulLaiChangeFlag =  NAS_MML_IsCsLaiChanged();

    ucProcessLu     = MM_TRUE;

    if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
    {
        if ( MM_TRUE
         == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
        {
            g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

            NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_PERIODIC_UPDATING);
            return;
        }

        if (VOS_FALSE == NAS_MM_IsLauNeeded_NetModeChange())
        {
            ucProcessLu = MM_FALSE;   /*收到系统消息只是小区的网络模式改变无需发起LU*/


            Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);



            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_SUCCESS,
                                        NAS_MML_REG_FAIL_CAUSE_NULL);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);


            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
             if ((MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
               && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3212].ucTimerStatus)
               && (0x0 != gstMmTimer[MM_TIMER_T3212].ulTimerLen))
             {

                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
             }

            g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        }
    }
    else if (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == NAS_MML_GetCsUpdateStatus())
    {
        if (VOS_FALSE == NAS_MM_IsLauNeeded_NetModeChange())
        {
            ucProcessLu = MM_FALSE;   /*收到系统消息只是小区的网络模式改变无需发起LU*/

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);

            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);


        }
    }
    else
    {
    }

    if (MM_TRUE == ucProcessLu)
    {
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);

    }

}

/*******************************************************************************
  Module   : MM_Update_Revision_Level
  Function : 更新空口消息中的ClassMark IE 的 revision level参数
  Input    : classmark 的第一个字节
  Output   : 无
  NOTE     : 无
  Return   : 无。
  History  :
    1. 欧阳飞  2009.06.19  新规作成
*******************************************************************************/
VOS_VOID MM_Update_Revision_Level(VOS_UINT8 *pucClassMark)
{
    VOS_INT8                    cVersion;
    VOS_UINT8                   ucRevisionLevel;

    cVersion = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_CS);

    /* R99以前版本，上报 revision level 为 GSM PHASE 2*/
    if(PS_PTL_VER_PRE_R99 == cVersion)
    {
        ucRevisionLevel = MM_CLASSMARK_REVISION_LEVEL_GSM_PH2;
    }
    else
    {
        ucRevisionLevel = MM_CLASSMARK_REVISION_LEVEL_R99_OR_LATER;
    }

    *pucClassMark &= 0x9f;
    *pucClassMark |= (VOS_UINT8)(ucRevisionLevel << 5);

    return;
}


VOS_VOID MM_Fill_IE_ClassMark1(
                               VOS_UINT8 *pucClassMark1                           /* 填写ClassMark1 IE的首地址                */
                              )
{
    GSM_BAND_SET_UN                     unSysCfgSetGsmBand;

    VOS_UINT8                           ucBandNum;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;
    NAS_MML_MS_BAND_INFO_STRU          *pstUserSetBand  = VOS_NULL_PTR;
    NAS_MML_MS_BAND_INFO_STRU          *pstCurrBand     = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRat;

    enCurrNetRat    = NAS_MML_GetCurrNetRatType();
    pstMsCapability = NAS_MML_GetMsCapability();
    pstUserSetBand  = NAS_MML_GetMsSupportBand();
    pstCurrBand     = NAS_MML_GetCurrBandInfo();
    *pucClassMark1 = pstMsCapability->ucClassmark1;

    NAS_MML_Update_Revision_Level(pucClassMark1);

    if ( VOS_FALSE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_GSM))
    {

        /* W only */
        /* bi8 ES IND => 0, A5/1 => 1, RF power capability => 111 */
        *pucClassMark1 &= 0xE0;
        *pucClassMark1 |= 0x0F;
    }
    else
    {
        /*获取当前的小区网络频段*/
        unSysCfgSetGsmBand.ulBand = pstCurrBand->unGsmBand.ulBand;
        if ( (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrNetRat)
#if (FEATURE_ON == FEATURE_LTE)
              || (NAS_MML_NET_RAT_TYPE_LTE == enCurrNetRat)
#endif
           )
        {
            unSysCfgSetGsmBand.ulBand = pstUserSetBand->unGsmBand.ulBand;
        }

        /*根据当前驻留的频段填写RF power capability*/

        if ((VOS_TRUE == unSysCfgSetGsmBand.stBitBand.BandGsm1800)
         || (VOS_TRUE == unSysCfgSetGsmBand.stBitBand.BandGsm1900))
        {
           /*power class 1*/
            *pucClassMark1 &= ~MM_CLASSMARK_RF_POWER_CAP_MASK;
            *pucClassMark1 |= MM_CLASSMARK_RF_POWER_CAP_CLASS1;
        }
        else /* 其它频段 */
        {
            /*power class 4*/
            *pucClassMark1 &= ~MM_CLASSMARK_RF_POWER_CAP_MASK;
            *pucClassMark1 |= MM_CLASSMARK_RF_POWER_CAP_CLASS4;
        }

        /* 如果当前网络驻留在W下,且用户设置为多频段的处理 */
        if ( (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrNetRat)
#if (FEATURE_ON == FEATURE_LTE)
              || (NAS_MML_NET_RAT_TYPE_LTE == enCurrNetRat)
#endif
           )
        {
            /* 获取用户设置的可在小区内驻留的频段 */
            NAS_MML_GetSupportBandNum(unSysCfgSetGsmBand.ulBand, &ucBandNum);

            /*如果支持多频段或者不支持任何频段，设置RF power capability => 111*/
            if ((ucBandNum > 1) || (0 == ucBandNum))
            {
                *pucClassMark1 |= MM_CLASSMARK_RF_POWER_CAP_MASK;
            }
        }
    }
    return;
}



VOS_VOID NAS_MM_GetSupportBandNum(VOS_UINT32 ulBand, VOS_UINT8 *pucBandNum)
{
    /* ucIndicator用来进行移位指示 */
    VOS_UINT8                           ucIndicator;

    /* ucTotalLen表示用来参数usBand的总bit位数 */
    VOS_UINT8                           ucTotalLen;

    /* ucBandNum用来记录bit值为1的个数，并作为函数的返回值 */
    *pucBandNum = 0;
    ucIndicator = 0;
    ucTotalLen  = sizeof(ulBand) * 8;

    /* 通过循环移位计算ulBand中的bit值为1的总个数，并保存到ucBandNum中 */
    while (ucIndicator < ucTotalLen)
    {
        if ((ulBand>>ucIndicator) & 0x01)
        {
            (*pucBandNum)++;
        }

        ucIndicator++;
    }

    return;
}


VOS_VOID MM_Fill_IE_ClassMark2(
    VOS_UINT8                          *pClassMark2                           /* 填写ClassMark2 IE的首地址                */
)
{
    NAS_MML_Fill_IE_ClassMark2(pClassMark2);

    return;
}


MMCC_CHANNEL_MODE_ENUM_U32 MM_ComGetChanMode(NAS_RR_CHANNEL_MODE_ENUM_U8 enChanMode)
{
    MMCC_CHANNEL_MODE_ENUM_U32   enMmCcChanMode;

    switch(enChanMode)
    {
    case RR_CHAN_MOD_SINGAL_ONLY:
        enMmCcChanMode = MMCC_CHAN_MOD_SIG_ONLY;
        break;
    case RR_CHAN_MOD_FR:
        enMmCcChanMode = MMCC_CHAN_MOD_FR;
        break;
    case RR_CHAN_MOD_EFR:
        enMmCcChanMode = MMCC_CHAN_MOD_EFR;
        break;
    case RR_CHAN_MOD_AFS:
        enMmCcChanMode = MMCC_CHAN_MOD_AMR;
        break;
    case RR_CHAN_MOD_CSD_2400:
        enMmCcChanMode = MMCC_CHAN_MOD_DATA_2400;
        break;
    case RR_CHAN_MOD_CSD_4800:
        enMmCcChanMode = MMCC_CHAN_MOD_DATA_4800;
        break;
    case RR_CHAN_MOD_CSD_9600:
        enMmCcChanMode = MMCC_CHAN_MOD_DATA_9600;
        break;
    case RR_NAS_DATA_CSD_14400:
        enMmCcChanMode = MMCC_CHAN_MOD_DATA_14400;
        break;
    case RR_CHAN_MOD_HR:
        enMmCcChanMode = MMCC_CHAN_MOD_HR;
        break;
    case RR_CHAN_MOD_AHR:
        enMmCcChanMode = MMCC_CHAN_MOD_AHR;
        break;
    case RR_CHAN_MOD_H24:
        enMmCcChanMode = MMCC_CHAN_MOD_SIG_ONLY;
        break;
    case RR_CHAN_MOD_H48:
        enMmCcChanMode = MMCC_CHAN_MOD_SIG_ONLY;
        break;

    case RR_CHAN_MOD_WFS:
        enMmCcChanMode = MMCC_CHAN_MOD_AMRWB;
        break;

    default :
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                            "MM_ComGetChanMode:  Receive GAS_RR_CHAN_MOD_IND, parameter is error.");
        enMmCcChanMode = MMCC_CHAN_MOD_SIG_ONLY;
        break;
    }

    return enMmCcChanMode;
}


VOS_VOID Mm_ComSetMmState(NAS_MM_STATE_ENUM_UINT8 ulState)
{


#if (FEATURE_ON == FEATURE_DSDS)
    NAS_MM_NotifySessionAccordingStateChg(g_MmGlobalInfo.ucState, ulState);
#endif

    if (( VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
     && (MM_IDLE_NORMAL_SERVICE == ulState))
    {
        g_MmGlobalInfo.ucState = MM_IDLE_LIMITED_SERVICE;
        g_MmSubLyrShare.MmShare.ucCsAttachState = MM_STATUS_DETACHED;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComSetMmState:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
    }
    else
    {
        g_MmGlobalInfo.ucState = ulState;
    }

    NAS_MM_LogMmStateInfo(g_MmGlobalInfo.ucState);

    switch(ulState)
    {
        case MM_STATE_NULL:
        case MM_IDLE_NORMAL_SERVICE:
        case MM_IDLE_LIMITED_SERVICE:
        case MM_IDLE_ATTEMPTING_TO_UPDATE:
        case MM_IDLE_LOCATION_UPDATE_NEEDED:
        case MM_IDLE_NO_IMSI:
        case MM_IDLE_NO_CELL_AVAILABLE:
            /* 回复MMCMM_ATTACH_CNF的操作,清除等待ATTACH结果标志位 */
            if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                                    & MM_WAIT_CS_ATTACH))
            {
                NAS_MM_SndMmcAttachCnf();
            }
            g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;


            break;

        case MM_CONNECTION_ACTIVE:
            /* 停止定时器 */
            Mm_TimerStop(MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE);

            NAS_MML_SetCsfbMtPagingTimerStatus(NAS_MML_MT_CSFB_PAGING_TIMER_STOP);

            /* 通知接入层TRANSACTION状态 */
            NAS_MM_SndTransactionStatusNotify(RRMM_TRANSACTION_CONNECTION_EST_SUCC);

            NAS_MM_ClearErrorLogInfo();

            /* 与收到call status nty(succ)/ss status nty(succ)处理相同 */
            NAS_MM_UpdateCallStatus_RcvCallStatusNty(MNCC_CALL_STATUS_SETUP_SUCC);
            NAS_MM_UpdateSsStatus_RcvSsStatusNty(SSA_SS_STATUS_SETUP_SUCC);

            break;

        default:
            break;
    }


    return;
}


VOS_VOID MM_LocalEndAllCalls(VOS_VOID)
{
    Mm_RcvRrmmRelInd();
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    return;
}

VOS_VOID Mm_GetServiceStatus(VOS_UINT32 *pulCsServiceStatus, VOS_UINT32 *pulCsCause)
{
    *pulCsServiceStatus = g_MmGlobalInfo.ucMmServiceState;
    *pulCsCause = g_MmGlobalInfo.usCauseVal;
}


VOS_VOID Mm_ComCheckDelayDetach()
{
    MM_MSG_IMSI_DETACH_IND_STRU     Msg;
#if (FEATURE_ON == FEATURE_ECALL)
    NAS_MML_CALL_MODE_ENUM_UINT8        enCallMode;

    enCallMode   = NAS_MML_GetCallMode();
#endif
    if ((NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
#if (FEATURE_ON == FEATURE_ECALL)
     && (NAS_MML_ECALL_ONLY != enCallMode)
#endif
       )
    {
        Mm_TimerStop(MM_TIMER_T3212);

        if (MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucState)
        {
            /*Detach CS*/
            if ((MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
            && ((GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)))
            {
                Mm_SndMmcDeRegisterInit();
            }
            else if (MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg)
            {
                g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;

                NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
                Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);

                Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                        /* 填写消息,发送消息                        */

                Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                     /* 启动保护TIMER                            */


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                "Mm_ComCheckDelayDetach:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
                g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;
            }
            else
            {
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
                g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                "Mm_ComCheckDelayDetach:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");

            }
        }
        else if ((MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState)
              || (MM_IDLE_LOCATION_UPDATE_NEEDED == g_MmGlobalInfo.ucState))
        {
            Mm_TimerStop(MM_TIMER_T3211);
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                   "Mm_ComCheckDelayDetach:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");

        }
        else
        {
        }

        /*设置attach not allow 标志*/
        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
    }

    if ((VOS_FALSE  == NAS_MM_IsNeedGmmProcUserDetach())
     && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)))
    {
        NAS_MM_LocalDetach();
    }
}


VOS_UINT32 Mm_ComJudgeCsServExist(VOS_VOID)
{
    VOS_UINT32                          ulRet = MM_CS_SERV_NONE_EXIST;

    if(  ( MM_CONST_NUM_7 <
       g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId)
       && ( MM_CONST_NUM_15 >
       g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId)
       && ( MM_TRUE ==
       g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg ) )
    {
        if ( MMCC_EMERGENCY_CALL ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType)
        {
            ulRet = MM_CS_SERV_EMERGENCY_CALL_EXIST;
        }
        else
        {
            ulRet = MM_CS_SERV_NORMAL_CALL_EXIST;
        }
    }

    else if ( MM_TRUE ==
         g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
    {
        ulRet = MM_CS_SERV_SS_EXIST;
    }

    else if ( MM_TRUE ==
         g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
    {
        ulRet = MM_CS_SERV_SMS_EXIST;
    }
    else if (MM_PAGING_PLMNSRCH_TRUE == g_MmSubLyrShare.MmShare.ucPagingPlmnSrch)
    {
        ulRet = MM_CS_SERV_MT_EXIST;
    }
    else
    {
        ;
    }

    return ulRet;
}





VOS_UINT32 NAS_MM_IsExistBufferService(VOS_VOID)
{
    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
    {
        return VOS_TRUE;
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
    {
        return VOS_TRUE;
    }
    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT8  MM_GetSignalingStatus(VOS_VOID)
{
    /* 因为MMC和MM间信令连接信息的通知是采用异步消息，所以在发起PLMN搜索前需要判断MM的当前状态。
    在注册或者去注册过程中,不允许发起搜网 */
    if((WAIT_FOR_RR_CONNECTION_MM_CONNECTION == g_MmGlobalInfo.ucState)
        || (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == g_MmGlobalInfo.ucState)
        || (WAIT_FOR_RR_CONNECTION_IMSI_DETACH == g_MmGlobalInfo.ucState)
        || (WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ == g_MmGlobalInfo.ucState)
        || (WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF == g_MmGlobalInfo.ucState))
    {
        return MMC_MM_SIGNALING_STATUS_PRESENT;
    }
    else if (VOS_TRUE == NAS_MM_IsExistBufferService())
    {
        return MMC_MM_SIGNALING_STATUS_PRESENT;
    }
    else
    {
        return MMC_MM_SIGNALING_STATUS_ABSENT;
    }
}


VOS_UINT8  NAS_MM_CheckIfMmIsEstablishRRConnection()
{
    /* 因为MMC和MM间信令连接信息的通知是采用异步消息，所以在发起PLMN搜索前需要判断MM的当前状态。
    在注册或者去注册过程中,不允许发起搜网 */
    if( (WAIT_FOR_RR_CONNECTION_MM_CONNECTION == g_MmGlobalInfo.ucState)
     || (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == g_MmGlobalInfo.ucState)
     || (WAIT_FOR_RR_CONNECTION_IMSI_DETACH == g_MmGlobalInfo.ucState)
     || (WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ == g_MmGlobalInfo.ucState)
     || (WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF == g_MmGlobalInfo.ucState))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
/* 废弃函数 */


VOS_UINT8 NAS_MM_RetryCurrentProcedureCheck(
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause,
    RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus
)
{
    /*24.008, 4.4.4.9 f1/4.5.1.2 a1:
      a.1) RR connection failure in Iu mode (i.e. RRC connection release) with,
      for example, cause "Normal", "User inactivity" or "Directed signalling
      connection re-establishment" (see 3GPP TS 25.331 [32c] and 3GPP TS 44.118
      [111])
      The MM connection establishment procedure shall be initiated again, if
      the following conditions apply:
      i) The original MM connection establishment was initiated over an existing
      RRC connection; and
      ii) No SECURITY MODE COMMAND message and no Non-Access Stratum (NAS) mess-
      ages relating to the CS signalling connection (e.g. CS authentication
      procedures, see subclause 4.3.2), were received after the CM SERVICE REQU-
      EST message was transmitted.
      NOTE 1:  The RRC connection release cause that triggers the re-initiation
      of the MM connection establishment procedure is implementation specific.*/

    VOS_UINT8                           ucRst;

    ucRst = VOS_FALSE;

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        if (   (RRC_RRC_CONN_STATUS_ABSENT == ulRrcConnStatus)
            && (VOS_TRUE == g_MmGlobalInfo.stMmLinkCtrl.ucExistedRrcConn)
            && (VOS_FALSE
                    == g_MmGlobalInfo.stMmLinkCtrl.ucSmcOrFirstNasMsgRcvdFlg)
            && (g_MmGlobalInfo.ucProc
                    == g_MmGlobalInfo.stMmLinkCtrl.ucCurrentProc))
        {
            if ( (RRC_REL_CAUSE_RR_NORM_EVENT           == ulRelCause)
              || (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST == ulRelCause)
              || (RRC_REL_CAUSE_RR_USER_INACT           == ulRelCause)
              || (RRC_REL_CAUSE_CELL_UPDATE_FAIL        == ulRelCause)
              || (RRC_REL_CAUSE_T314_EXPIRED            == ulRelCause) )
            {
                ucRst = VOS_TRUE;
            }
        }
    }

    /* 判断完毕后，清除MM链路控制变量 */
    NAS_MM_ClearMmLinkCtrlStru();

    return ucRst;
}


VOS_UINT8 NAS_MM_IsRrRelCauseNeedRetryLau(
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause
)
{
    VOS_UINT8                           ucRst;

    ucRst = VOS_FALSE;  /* [false alarm]:ucRst作为初始化值 */

    switch ( ulRelCause )
    {
        case RRC_REL_CAUSE_RR_UNSPEC :
        case RRC_REL_CAUSE_NAS_DATA_ABSENT :
        case RRC_REL_CAUSE_RRC_ERROR :
        case RRC_REL_CAUSE_RL_FAILURE :
        case RRC_REL_CAUSE_OTHER_REASON :
        case RRC_REL_CAUSE_NO_RF :
        case RRC_REL_CAUSE_RLC_ERROR:
        case RRC_REL_CAUSE_W_RL_FAIL:

        case RRC_REL_CAUSE_G_RL_FAIL:

            ucRst = VOS_FALSE;
            break;

        default:
            ucRst = VOS_TRUE;
            break;
    }

    return ucRst;
}




VOS_VOID NAS_MM_RetryMmConnectionProc(
    VOS_UINT8                           ucMMConnEstingPD
)
{
    NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl;

    switch (ucMMConnEstingPD)
    {
        case MM_IE_PD_CALL_CONTROL:
            ucMmConnCtrl = MM_CONN_CTRL_CC;
            break;
        case MM_IE_PD_NON_CALL_RLT_SS_MSG:
            ucMmConnCtrl = MM_CONN_CTRL_SS;
            break;
        case MM_IE_PD_SMS_MSG:
            ucMmConnCtrl = MM_CONN_CTRL_SMS;
            break;
        default:
            ucMmConnCtrl = MM_CONN_CTRL_BUTT;
            NAS_WARNING_LOG1(WUEPS_PID_MM, "NAS_MM_RetryMmConnectionProc: unexpected ucMMConnEstingPD received: ", ucMMConnEstingPD);
            break;
    }

    if (MM_CONN_CTRL_BUTT != ucMmConnCtrl)
    {
        NAS_MM_EstMmConnection(ucMmConnCtrl);
    }

    return;
}


VOS_VOID NAS_MM_GetPDFromConnCtrlEnum(
    NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl,
    VOS_UINT8                           *pucMMConnEstingPD
)
{
    switch (ucMmConnCtrl)
    {
        case MM_CONN_CTRL_CC:
            *pucMMConnEstingPD = MM_IE_PD_CALL_CONTROL;
            break;
        case MM_CONN_CTRL_SS:
            *pucMMConnEstingPD = MM_IE_PD_NON_CALL_RLT_SS_MSG;
            break;
        case MM_CONN_CTRL_SMS:
            *pucMMConnEstingPD = MM_IE_PD_SMS_MSG;
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_GetPDFromConnCtrlEnum: unexpected ucMmConnCtrl.");
            break;
    }

    return;
}



VOS_VOID NAS_MM_EstMmConnection(
    NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl
)
{
    MM_MSG_CM_SVC_REQ_STRU              stCmSvcReq;
    VOS_UINT16                          usMsgSize;
    VOS_UINT8                           *pucCmSvcReq;
    VOS_UINT8                           ucCMSvcType;
    VOS_UINT32                          ulRrcEstCause;

    /* 缓存消息，在连接建立过程中如果发生重选，如果LU改变，在LU结束后可以进行重传 */
    NAS_MM_UpdateConnCtrlInfo(ucMmConnCtrl);

    NAS_MM_GetCMSvcType(ucMmConnCtrl, &ucCMSvcType);

    /* 填充CM SERVICE REQUEST结构体             */
    Mm_ComFillInCMSncReq(ucCMSvcType, MM_FALSE, &stCmSvcReq);

    /* 填充CM SERVICE REQUEST 消息              */
    pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq(&stCmSvcReq, &usMsgSize);
    if (VOS_NULL_PTR == pucCmSvcReq)
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_EstMmConnection:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
        return;
    }
    else
    {
        NAS_MM_GetRrcEstCause(ucMmConnCtrl, &ulRrcEstCause);

        Mm_SndRrEstReq(ulRrcEstCause, MM_FALSE, usMsgSize, pucCmSvcReq);

        MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq);
    }

    NAS_MM_GetPDFromConnCtrlEnum(ucMmConnCtrl, &g_MmGlobalInfo.ucMMConnEstingPD);

    /* 启动保护TIMER                            */
    Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);
    /* 通知MMC，CS域的业务已经启动              */
    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
    Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
    NAS_NORMAL_LOG(WUEPS_PID_MM, "NAS_MM_EstMmConnection:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");

    return;
}


VOS_UINT32 NAS_MM_IsCcServiceNeedTriggerPlmnSearch(VOS_VOID)
{
    VOS_UINT8                           ucSimCsRegStatus;

    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

    /* 紧急呼叫时需要触发搜网 */
    if (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType)
    {
        return VOS_TRUE;
    }

    /* 普通呼叫且卡有效no rf时需要触发搜网 */
    if ((VOS_FALSE == NAS_MML_GetRfAvailFlg())
     && (VOS_TRUE == ucSimCsRegStatus)
     && (MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_VOID NAS_MM_UpdateConnCtrlInfo(
    NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl
)
{
    g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ucFlg = MM_TRUE;
    g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].ucRat = NAS_MML_GetCurrNetRatType();
    NAS_MML_SetCsServiceBufferStatusFlg(VOS_TRUE);

    switch (ucMmConnCtrl)
    {
        case MM_CONN_CTRL_CC:
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulCallPri
                = g_MmCcEstReq.ulCallPri;
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulCallType
                = g_MmCcEstReq.ulCallType;
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulTransactionId
                = g_MmCcEstReq.ulTransactionId;
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulCallMode
                = g_MmCcEstReq.ulCallMode;

            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].ucMMConnEstingTI
                = (VOS_UINT8)g_MmCcEstReq.ulTransactionId;

            if (MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType)
            {
                g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].ucEstingCallTypeFlg
                    = MM_FALSE;
            }
            else
            {
                g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].ucEstingCallTypeFlg
                    = MM_TRUE;
            }
            break;

        case MM_CONN_CTRL_SS:
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulCallPri
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulCallType
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulTransactionId
                = g_MmSsEstReq.ulTi;

            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].ucMMConnEstingTI
                = (VOS_UINT8)g_MmSsEstReq.ulTi;

            break;

        case MM_CONN_CTRL_SMS:
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulCallPri
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulCallType
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulTransactionId
                = g_MmSmsEstReq.ulTi;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                = (VOS_UINT8)g_MmSmsEstReq.ulTi;
            break;

        default:
            break;
    }

    return;
}



VOS_VOID NAS_MM_GetCMSvcType(
    NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl,
    VOS_UINT8                           *pucCmSrvType
)
{
    switch (ucMmConnCtrl)
    {
        case MM_CONN_CTRL_CC:
            if (MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType)
            {
                *pucCmSrvType = MM_IE_CM_SVC_TYPE_MO_CALL_EST;
            }
            else
            {
                *pucCmSrvType = MM_IE_CM_SVC_TYPE_EMG_CALL_EST;
            }
            break;

        case MM_CONN_CTRL_SS:
            *pucCmSrvType = MM_IE_CM_SVC_TYPE_SS_ACT;
            break;

        case MM_CONN_CTRL_SMS:
            *pucCmSrvType = MM_IE_CM_SVC_TYPE_SMS;
            break;

        default:
            *pucCmSrvType = 0;
            break;
    }

    return;
}



VOS_VOID NAS_MM_GetRrcEstCause(
    NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl,
    VOS_UINT32                          *pulRrcEstCause
)
{
    switch (ucMmConnCtrl)
    {
        case MM_CONN_CTRL_CC:
            if (MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType)
            {
                *pulRrcEstCause = RRC_EST_CAUSE_ORIGIN_CONVERSAT_CALL;
            }
            else
            {
                *pulRrcEstCause = RRC_EST_CAUSE_EMERGENCY_CALL;
            }
            break;

        case MM_CONN_CTRL_SS:
            *pulRrcEstCause = RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL;
            break;

        case MM_CONN_CTRL_SMS:
            *pulRrcEstCause = RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL;
            break;

        default:
            *pulRrcEstCause = RRC_EST_CAUSE_ORIGIN_CONVERSAT_CALL;
            break;
    }

    return;
}



VOS_VOID NAS_MM_UpdateMmLinkCtrlStru(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU       *pstConnStatus;

    pstConnStatus   = NAS_MML_GetConnStatus();

    g_MmGlobalInfo.stMmLinkCtrl.ucCurrentProc = g_MmGlobalInfo.ucProc;
    g_MmGlobalInfo.stMmLinkCtrl.ucSmcOrFirstNasMsgRcvdFlg = VOS_FALSE;

    /* 检查当前流程是否在已建立的RRC连接上发起 */
    if (VOS_FALSE == pstConnStatus->ucRrcStatusFlg)
    {
        g_MmGlobalInfo.stMmLinkCtrl.ucExistedRrcConn = VOS_FALSE;
    }
    else
    {
        g_MmGlobalInfo.stMmLinkCtrl.ucExistedRrcConn = VOS_TRUE;
    }

    return;
}



VOS_VOID NAS_MM_ClearMmLinkCtrlStru( VOS_VOID )
{
    g_MmGlobalInfo.stMmLinkCtrl.ucCurrentProc = MM_NULL_PROC;
    g_MmGlobalInfo.stMmLinkCtrl.ucExistedRrcConn = VOS_FALSE;
    g_MmGlobalInfo.stMmLinkCtrl.ucSmcOrFirstNasMsgRcvdFlg = VOS_FALSE;
}


VOS_VOID NAS_MM_ClearConnCtrlInfo(VOS_UINT8 ucMMConnEstingPD)
{
    if(MM_IE_PD_CALL_CONTROL == ucMMConnEstingPD)
    {
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
            = MM_FALSE;
    }
    else if(MM_IE_PD_SMS_MSG == ucMMConnEstingPD)
    {
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
            = MM_FALSE;
    }
    else if(MM_IE_PD_NON_CALL_RLT_SS_MSG == ucMMConnEstingPD)
    {
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
            = MM_FALSE;
    }
    else
    {
    }

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}


VOS_VOID NAS_MM_ClearConnCtrlInfoExcEmgCall(VOS_UINT8 ucMMConnEstingPD)
{
    if ((MM_IE_PD_CALL_CONTROL == ucMMConnEstingPD)
     && (MMCC_EMERGENCY_CALL != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType))
    {
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
        NAS_MML_SetCsServiceBufferStatusFlg(VOS_FALSE);
        return;
    }

    if (MM_IE_PD_SMS_MSG == ucMMConnEstingPD)
    {
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
        NAS_MML_SetCsServiceBufferStatusFlg(VOS_FALSE);
        return;
    }

    if (MM_IE_PD_NON_CALL_RLT_SS_MSG == ucMMConnEstingPD)
    {
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;
        NAS_MML_SetCsServiceBufferStatusFlg(VOS_FALSE);
    }

    return;
}


VOS_VOID NAS_MM_ProcEstCnfSuccessCauseAtState12(VOS_VOID)
{
    VOS_UINT32                          ulIsTestCard;
    VOS_UINT8                           ucSupportCsServiceFlg;                  /* 是否支持cs语音业务包括普通语音和vp业务，VOS_TRUE:支持cs语音业务；VOS_FALSE:不支持cs语音业务*/

    ulIsTestCard          = NAS_USIMMAPI_IsTestCard();
    ucSupportCsServiceFlg = NAS_MML_GetSupportCsServiceFLg();

    NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    if ( (NO_MM_CONN_ESTING != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI)
       ||(NO_MM_CONN_ESTING != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI)
       ||(NO_MM_CONN_ESTING != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI))
    {
        Mm_TimerStart(MM_TIMER_T3230);
        Mm_ComSetMmState(WAIT_FOR_OUTGOING_MM_CONNECTION);

        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);

        NAS_NORMAL_LOG(WUEPS_PID_MM, "NAS_MM_ProcEstCnfSuccessCauseAtState12:NORMAL: STATUS is  WAIT_FOR_OUTGOING_MM_CONNECTION");
    }
    else
    {
        /* 由网侧寻呼引起的连接建立                 */
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.ucStaOfRcvXXEstReq;
        Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        NAS_NORMAL_LOG(WUEPS_PID_MM, "NAS_MM_ProcEstCnfSuccessCauseAtState12:NORMAL: STATUS is  WAIT_FOR_NETWORK_COMMAND");

        NAS_MM_SetCsfbMtLauFlg(VOS_FALSE);

        if ( (VOS_TRUE  == ulIsTestCard)
          && (VOS_FALSE == ucSupportCsServiceFlg) )
        {
            gstMmTimer[MM_TIMER_T3240].ulTimerLen = MM_TIMER_MAX_VALUE;
            Mm_TimerStart( MM_TIMER_T3240 );
            gstMmTimer[MM_TIMER_T3240].ulTimerLen = MM_TIMER_T3240_VALUE;
        }
        else
        {
            /*A32D12629==>在此期间可能发起频率重定义，时间为50秒，因此增加定时器长度*/
            gstMmTimer[MM_TIMER_T3240].ulTimerLen += 50000;
            Mm_TimerStart( MM_TIMER_T3240 );
            gstMmTimer[MM_TIMER_T3240].ulTimerLen -= 50000;
        }
        /*<==A32D12629*/
    }

    g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_PRESENT;
    NAS_INFO_LOG(WUEPS_PID_MM, "NAS_MM_ProcEstCnfSuccessCauseAtState12:INFO: MmCsSigConnFlg is MM_CS_SIG_CONN_PRESENT");
    Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ESTED );
    return;
}


VOS_VOID NAS_MM_InformCmLayerEstFail(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult
)
{
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause;

    enMmCcRelCause  = NAS_MM_ConvertEstCnfRsltToMmCcRelCause(ulResult);

    if ( NO_MM_CONN_ESTING != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI )
    {
        /* CC发起的RR连接的建立, 通知CC建立失败             */
        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                        enMmCcRelCause);

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI = NO_MM_CONN_ESTING;
    }
    else if ( NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI )
    {
        /* SS发起的RR连接的建立 ，通知SS,MM连接建立失败      */
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI,
                       enMmCcRelCause);

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI = NO_MM_CONN_ESTING;
    }
    else if ( NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI )
    {
        /* SMS发起的RR连接的建立 ,通知SMS,MM连接建立失败      */
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                       enMmCcRelCause);

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI = NO_MM_CONN_ESTING;
    }
    else
    {
        /* 没有正在建立的MM连接，即被叫             */
    }


    return;
}


VOS_VOID NAS_MM_ProcEstCnfOtherFailCauseAtState12(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult
)
{
    VOS_UINT8               ucTiValidFlg;
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause;

    NAS_MM_InformCmLayerEstFail(ulResult);

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
    Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
    NAS_NORMAL_LOG1(WUEPS_PID_MM, "NAS_MM_ProcEstCnfOtherFailCauseAtState12:NORMAL: ucState = ",
                    g_MmGlobalInfo.ucState);

    enMmCcRelCause  = NAS_MM_ConvertEstCnfRsltToMmCcRelCause(ulResult);

    /* 因为函数Mm_ComChkLu有是否当前在连接态的判断,所以在连接建立失败时,
       不能直接调用此函数,而要调用NAS_MM_CheckLuAfterCsConnectRelease进行处理 */
    if ( MM_FALSE == NAS_MM_ProcessLuAfterCsConnectNotExist() )
    {
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
         || (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
         || (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg))
        {
            ucTiValidFlg = Mm_ComTiChk();
            if ( MM_FALSE == ucTiValidFlg )
            {
                Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );         /* RR连接不存在                             */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
            else
            {
                Mm_ComSigRelForDelayMmConnRej();
            }
        }
        else
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );             /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

            /* 删除CHR错误的记录点CS PAGING FAIL */
        }
        Mm_ComCheckDelayMmConn( MM_FALSE );

        Mm_ComCheckDelayDetach();
    }
    else
    {
        if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {                                                               /* 有等待的CC触发的需要建立的MM连接         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                           enMmCcRelCause);
        }
        else if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
        {                                                               /* 有等待的CC触发的需要建立的MM连接         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                           enMmCcRelCause);
        }
        else if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
        {                                                               /* 有等待的CC触发的需要建立的MM连接         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                           enMmCcRelCause);
        }
        else
        {
            /* 删除CHR错误的记录点CS PAGING FAIL */
            ;
        }
    }

    if ( g_T3211Flag )
    {
        Mm_TimerStart(MM_TIMER_T3211);
        g_T3211Flag = 0;
    }

    return;
}



VOS_VOID NAS_MM_ProcEstCnfCauseAtState12(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult
)
{
    switch (ulResult)
    {
        case RRC_EST_SUCCESS:
        case RRC_EST_PRESENT:
            NAS_MM_ProcEstCnfSuccessCauseAtState12();
            break;
        case RRC_EST_RJ_CONGEST:                                                /* RRC Connection Reject: Congestion        */
        case RRC_EST_RJ_UNSPEC:                                                 /* RRC Connection Reject: Unspecified       */
        case RRC_EST_EST_CONN_FAIL:                                             /* RR connection establish failure          */
        case RRC_EST_RJ_NOT_ALLOW:
        case RRC_EST_RJ_TIME_OUT:
        case RRC_EST_RJ_RA_RESOURCE_FAIL:
        case RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID:
        case RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL:
        case RRC_EST_RJ_AIRMSG_DECODE_ERR:
        case RRC_EST_RJ_FASTRETURN_LTE:
        case RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT:
        case RRC_EST_RJ_SNW:
        case RRC_EST_RJ_NO_RF:                                                     /* RR Connection failed because of no rf */
        case RRC_EST_RJ_T3122_RUNNING:
        case RRC_EST_RJ_INTER_RAT:
        case RRC_EST_IMMEDIATE_ASSIGN_REJECT:
        case RRC_EST_RANDOM_ACCESS_REJECT:
        case RRC_EST_RJ_RA_FAIL:
        case RRC_EST_RJ_RA_FAIL_NO_VALID_INFO:

        case RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO:

            NAS_MM_ProcEstCnfOtherFailCauseAtState12(ulResult);

            break;
        case RRC_EST_OTHER_ACCESS_BARRED:
            /* 主要接入受限，设置标志位 */
            NAS_MM_ProcEstCnfOtherFailCauseAtState12(ulResult);

            break;
        case RRC_EST_PAGING_ACCESS_BARRED:
            /* 主要接入受限，设置标志位 */
            NAS_MML_SetPsRestrictPagingFlg(VOS_TRUE);

            NAS_MM_ProcEstCnfOtherFailCauseAtState12(ulResult);
            break;
        case RRC_EST_ACCESS_BARRED:
        case RRC_EST_RJ_CELL_BAR:
            /* 非紧急呼叫才设置限制注册和寻呼标记 */
            if (MMCC_EMERGENCY_CALL !=  g_MmCcEstReq.ulCallType)
            {
                /* 接入受限，设置标志位 */
                NAS_MML_SetCsRestrictPagingFlg(VOS_TRUE);
                NAS_MML_SetCsRestrictRegisterFlg(VOS_TRUE);
            }

            NAS_MM_ProcEstCnfOtherFailCauseAtState12(ulResult);
            break;
        case RRC_EST_ESTING:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E32:WARNING: RR CONNECTION ESTING !");
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E32:WARNING: ulResult Abnormal");
            break;
    }
}




MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeFullNameForNetworkIe(
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT16                          *pusIndex,
    VOS_UINT8                           *pucEventId,
    VOS_UINT8                           *pucLongNetWorkNameExist
)
{
    VOS_UINT16                          usIndex;
    MM_DECODE_RESULT_ENUM_U32           ulRst;
    VOS_UINT16                          usIeLen;
    NAS_MML_OPERATOR_NAME_INFO_STRU    *pstCurrOperatorName = VOS_NULL_PTR;

    pstCurrOperatorName = NAS_MML_GetOperatorNameInfo();

    usIndex = *pusIndex;
    ulRst   = MM_DECODE_SUCCESS;

    if ( usMsgSize < (usIndex + MM_IE_TL_LENGTH))
    {
        usIndex = usMsgSize;
    }
    else
    {
        usIeLen = pucRcvMsg[usIndex + MM_IE_TAG_LENGTH];

        if ( 0 == usIeLen )
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeFullNameForNetworkIe:WARNING: NETWORK NAME SIZE ERROR!");
            *pucEventId = MM_EVENT_ID_STATUS_95;
            ulRst       = MM_DECODE_END;

        }
        else if ( usMsgSize < (usIndex + usIeLen + MM_IE_TL_LENGTH) )
        {
            usIndex = usMsgSize;
        }
        else
        {
            if ( VOS_FALSE == MM_IeChkNtwkNam( &pucRcvMsg[usIndex + MM_IE_TAG_LENGTH] ) )
            {
                NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeFullNameForNetworkIe:WARNING: NETWORK NAME ERROR!");
                *pucEventId = MM_EVENT_ID_STATUS_95;
                ulRst       = MM_DECODE_END;
            }
            else
            {
                PS_MEM_SET(pstCurrOperatorName->aucOperatorNameLong, 0, NAS_MML_MAX_OPER_LONG_NAME_LEN);
                if (NAS_MML_MAX_OPER_LONG_NAME_LEN >= (pucRcvMsg[usIndex + MM_IE_TAG_LENGTH] + 1))
                {
                    PS_MEM_CPY(pstCurrOperatorName->aucOperatorNameLong, (VOS_UINT8 *)&pucRcvMsg[usIndex + MM_IE_TAG_LENGTH], pucRcvMsg[usIndex + MM_IE_TAG_LENGTH] + 1);
                }
                else
                {
                    PS_MEM_CPY(pstCurrOperatorName->aucOperatorNameLong, (VOS_UINT8 *)&pucRcvMsg[usIndex + MM_IE_TAG_LENGTH], NAS_MML_MAX_OPER_LONG_NAME_LEN);
                }
            }

            usIndex = usIndex + usIeLen + MM_IE_TL_LENGTH;
        }
    }

    *pusIndex = usIndex;

    return ulRst;
}


MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeShortNameForNetworkIe(
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT16                          *pusIndex,
    VOS_UINT8                           *pucEventId,
    VOS_UINT8                           *pucShortNetWorkNameExist
)
{
    VOS_UINT16                          usIndex;
    MM_DECODE_RESULT_ENUM_U32           ulRst;
    VOS_UINT16                          usIeLen;
    NAS_MML_OPERATOR_NAME_INFO_STRU    *pstCurrOperatorName = VOS_NULL_PTR;

    pstCurrOperatorName = NAS_MML_GetOperatorNameInfo();

    usIndex = *pusIndex;
    ulRst   = MM_DECODE_SUCCESS;

    if ( usMsgSize < (usIndex + MM_IE_TL_LENGTH))
    {
        usIndex = usMsgSize;
    }
    else
    {
        usIeLen = pucRcvMsg[usIndex + MM_IE_TAG_LENGTH];

        if ( 0 == usIeLen )
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeShortNameForNetworkIe:WARNING: NETWORK NAME SIZE ERROR!");
            *pucEventId = MM_EVENT_ID_STATUS_95;
            ulRst       = MM_DECODE_END;
        }
        else if ( usMsgSize < (usIndex + usIeLen + MM_IE_TL_LENGTH) )
        {
            usIndex = usMsgSize;
        }
        else
        {
            if ( VOS_FALSE == MM_IeChkNtwkNam( &pucRcvMsg[usIndex + MM_IE_TAG_LENGTH] ) )
            {
                NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeShortNameForNetworkIe:WARNING: NETWORK NAME ERROR!");
                *pucEventId = MM_EVENT_ID_STATUS_95;
                ulRst       = MM_DECODE_END;
            }
            else
            {
                PS_MEM_SET(pstCurrOperatorName->aucOperatorNameShort, 0, NAS_MML_MAX_OPER_SHORT_NAME_LEN);
                if (NAS_MML_MAX_OPER_SHORT_NAME_LEN >= (pucRcvMsg[usIndex + MM_IE_TAG_LENGTH] + 1))
                {
                    PS_MEM_CPY(pstCurrOperatorName->aucOperatorNameShort, (VOS_UINT8 *)&pucRcvMsg[usIndex + MM_IE_TAG_LENGTH], pucRcvMsg[usIndex + MM_IE_TAG_LENGTH] + 1);
                }
                else
                {
                    PS_MEM_CPY(pstCurrOperatorName->aucOperatorNameShort, (VOS_UINT8 *)&pucRcvMsg[usIndex + MM_IE_TAG_LENGTH], NAS_MML_MAX_OPER_SHORT_NAME_LEN);
                }
            }

            usIndex = usIndex + usIeLen + MM_IE_TL_LENGTH;
        }
    }

    *pusIndex = usIndex;

    return ulRst;
}


MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeLocalTimeZoneIe(
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT16                          *pusIndex,
    VOS_UINT8                           *pucEventId
)
{
    VOS_UINT16                          usIndex;
    MM_DECODE_RESULT_ENUM_U32           ulRst;

    usIndex = *pusIndex;
    ulRst   = MM_DECODE_SUCCESS;

    if ( usMsgSize < (usIndex + MM_IE_TL_LENGTH) )
    {
        usIndex = usMsgSize;
    }
    else
    {
        if ( VOS_FALSE == MM_IeChkTimZone(&pucRcvMsg[usIndex + MM_IE_TAG_LENGTH]))
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeLocalTimeZoneIe:WARNING: Local Time Zone Value ERROR!");
            *pucEventId = MM_EVENT_ID_STATUS_95;
            ulRst       = MM_DECODE_END;
        }
        usIndex = usIndex + MM_IE_LOCAL_TIME_ZONE_LEN;
    }

    *pusIndex = usIndex;

    return ulRst;
}


MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeUniversalTimeAndLocalTimeZoneIe(
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT16                          *pusIndex,
    VOS_UINT8                           *pucEventId
)
{
    VOS_UINT16                          usIndex;
    MM_DECODE_RESULT_ENUM_U32           ulRst;

    usIndex = *pusIndex;
    ulRst   = MM_DECODE_SUCCESS;

    if ( usMsgSize < (usIndex + MM_IE_UNIVERSAL_TIME_AND_LOCAL_TIME_ZONE_LEN) )
    {
        usIndex = usMsgSize;
    }
    else
    {
        if ( VOS_FALSE == MM_IeChkTimAndTimZone(&pucRcvMsg[usIndex + MM_IE_TAG_LENGTH]))
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeUniversalTimeAndLocalTimeZoneIe:WARNING: Universal Time and Zone value error!");
        }
        usIndex = usIndex + MM_IE_UNIVERSAL_TIME_AND_LOCAL_TIME_ZONE_LEN;
    }

    *pusIndex = usIndex;

    return ulRst;
}


MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeLocalizedServiceAreaIe(
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT16                          *pusIndex,
    VOS_UINT8                           *pucEventId
)
{
    VOS_UINT16                          usIndex;
    MM_DECODE_RESULT_ENUM_U32           ulRst;
    VOS_UINT16                          usIeLen;

    usIndex = *pusIndex;
    ulRst   = MM_DECODE_SUCCESS;

    if ( usMsgSize < (usIndex + MM_IE_TL_LENGTH) )
    {
        usIndex = usMsgSize;
    }
    else
    {
        usIeLen = pucRcvMsg[usIndex + MM_IE_TAG_LENGTH];

        if (usIeLen > MM_IE_LSA_IDENTITY_VALUE_MAX_LEN)
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeLocalizedServiceAreaIe:WARNING: LSA ID SIZE ERROR!");
            *pucEventId = MM_EVENT_ID_STATUS_95;
            ulRst       = MM_DECODE_END;
        }
        if ( usMsgSize < (usIndex + usIeLen + MM_IE_TL_LENGTH) )
        {
            usIndex = usMsgSize;
        }
        else
        {
            if ( VOS_FALSE == MM_IeChkLsaIdtfr( &pucRcvMsg[usIndex + MM_IE_TAG_LENGTH] ))
            {
                NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeLocalizedServiceAreaIe:WARNING: LSA ID ERROR!");
                *pucEventId = MM_EVENT_ID_STATUS_95;
                ulRst       = MM_DECODE_END;
            }
            usIndex = usIndex + usIeLen + MM_IE_TL_LENGTH;
        }
    }

    *pusIndex = usIndex;

    return ulRst;
}


MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeNetworkDaylightSavingTimeIe(
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT16                          *pusIndex,
    VOS_UINT8                           *pucEventId
)
{
    VOS_UINT16                          usIndex;
    MM_DECODE_RESULT_ENUM_U32           ulRst;
    VOS_UINT16                          usIeLen;

    usIndex = *pusIndex;
    ulRst   = MM_DECODE_SUCCESS;

    if ( usMsgSize < (usIndex + MM_IE_NETWORK_DAYLIGHT_SAVING_TIME_LEN) )
    {
        usIndex = usMsgSize;
    }
    else
    {
        usIeLen = pucRcvMsg[usIndex + MM_IE_TAG_LENGTH];
        if ( MM_IE_NETWORK_DAYLIGHT_SAVING_TIME_VALUE_LEN !=  usIeLen)
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeNetworkDaylightSavingTimeIe:WARNING: DAYLIGHT SAVING TIME SIZE ERROR!");
            *pucEventId = MM_EVENT_ID_STATUS_95;
            ulRst       = MM_DECODE_END;
        }

        if ( MM_FALSE == MM_IeChkDayLightSavTim( &pucRcvMsg[usIndex + 1]))
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeNetworkDaylightSavingTimeIe:WARNING: DAYLIGHT SAVING TIME ERROR!");
            *pucEventId = MM_EVENT_ID_STATUS_95;
            ulRst       = MM_DECODE_END;
        }
        usIndex = usIndex + MM_IE_NETWORK_DAYLIGHT_SAVING_TIME_LEN;
    }

    *pusIndex = usIndex;

    return ulRst;
}


VOS_UINT32  NAS_MM_IsInRegisterProcedure(VOS_VOID)
{
    /* 判断当前是否在注册过程中 */
    if((WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == g_MmGlobalInfo.ucState)
        || (LOCATION_UPDATING_INITIATED == g_MmGlobalInfo.ucState))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


VOS_BOOL NAS_MM_NeedSendEPlmnConnFail()
{
    if ( (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
      && (1 == g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt) )
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}


VOS_UINT32  NAS_MM_IsPLmnIdInEplmnList (
    MM_PLMN_ID_STRU                    *pstPlmnId
)
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnList = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstEplmnList    =   NAS_MML_GetEquPlmnList();
    for ( i = 0 ; i < pstEplmnList->ucEquPlmnNum; i++ )
    {
        if ( ( pstPlmnId->ulMcc == pstEplmnList->astEquPlmnAddr[i].ulMcc)
          && ( pstPlmnId->ulMnc == pstEplmnList->astEquPlmnAddr[i].ulMnc))
        {
            return VOS_TRUE;
        }
    }


    return VOS_FALSE;
}




VOS_VOID NAS_MM_ConvertToMmcServiceStatus(
    VOS_UINT8                           ucMmServiceStatus,
    VOS_UINT32                         *pCsServiceStatus
)
{
    switch(ucMmServiceStatus)
    {
        case MM_NORMAL_SERVICE:
            *pCsServiceStatus = MM_COM_SRVST_NORMAL_SERVICE;
            break;
        case MM_LIMITED_SERVICE:
            *pCsServiceStatus = MM_COM_SRVST_LIMITED_SERVICE;
            break;
        case MM_NO_IMSI:
            *pCsServiceStatus = MM_COM_SRVST_NO_IMSI;
            break;
        case MM_NO_SERVICE:
            *pCsServiceStatus = MM_COM_SRVST_NO_SERVICE;
            break;
        case MM_LIMIT_REGION_SERVICE:
            *pCsServiceStatus = MM_COM_SRVST_LIMITED_SERVICE_REGION;
            break;
        case MM_ATTEMPTING_TO_UPDATE:
            *pCsServiceStatus = MM_COM_SRVST_NO_CHANGE;
            break;
        case MM_DETACHED:
            *pCsServiceStatus = MM_COM_SRVST_LIMITED_SERVICE;
            break;
        case MM_DISABLE:
            *pCsServiceStatus = MM_COM_SRVST_LIMITED_SERVICE;
            break;
        default:
            break;
    }

    return;
}


VOS_VOID NAS_MM_HandleGmmCauseValAsLuAccept()
{
    if ((MM_GMM_ATTACH_PROC == g_MmGlobalInfo.ucProc)
     || (MM_GMM_RAU_PROC == g_MmGlobalInfo.ucProc))
    {
        if ((NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
         || (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW  == g_MmGlobalInfo.usCauseVal)
         || (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
         || (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL == g_MmGlobalInfo.usCauseVal))
        {
            Mm_ComProcCauseClear();
        }
    }

    return;
}


VOS_VOID NAS_MM_UpdateCsServiceConnStatusFlg(VOS_VOID)
{
    if ( ( MM_CONST_NUM_0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] )
      && ( MM_CONST_NUM_0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] )
      && ( MM_CONST_NUM_0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] )
      && ( MM_CONST_NUM_0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] )
      && ( MM_CONST_NUM_0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] )
      && ( MM_CONST_NUM_0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]))
    {
        NAS_MML_SetCsServiceConnStatusFlg(VOS_FALSE);
    }

    if ( ( MM_CONST_NUM_0 != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] )
      || ( MM_CONST_NUM_0 != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] )
      || ( MM_CONST_NUM_0 != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] )
      || ( MM_CONST_NUM_0 != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] )
      || ( MM_CONST_NUM_0 != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] )
      || ( MM_CONST_NUM_0 != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]))
    {
        NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);
    }

    return;
}


VOS_VOID NAS_MM_UpdateCsServiceBufferStatusFlg(VOS_VOID)
{
    if ( ( MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
      && ( MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
      && ( MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg ) )
    {
        NAS_MML_SetCsServiceBufferStatusFlg(VOS_FALSE);
    }

    if ( ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
      || ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
      || ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg ) )
    {
        NAS_MML_SetCsServiceBufferStatusFlg(VOS_TRUE);
    }

    return;
}


VOS_VOID NAS_MM_SetLikeBFlg(VOS_VOID)
{
    if ((MMCMM_NO_FORBIDDEN == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
     || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* 设置类似于B模式的全局量                  */
    }
}


VOS_VOID NAS_MM_WriteRplmnWithRatNvim(
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo
)
{
    NAS_NVIM_RPLMN_WITH_RAT_STRU    stRplmn;

    stRplmn.ucLastRplmnRat          = (VOS_UINT8)pstRplmnCfgInfo->enLastRplmnRat;
    stRplmn.stGRplmn.ulMcc          = pstRplmnCfgInfo->stGRplmnInNV.ulMcc;
    stRplmn.stGRplmn.ulMnc          = pstRplmnCfgInfo->stGRplmnInNV.ulMnc;
    stRplmn.stWRplmn.ulMcc          = pstRplmnCfgInfo->stWRplmnInNV.ulMcc;
    stRplmn.stWRplmn.ulMnc          = pstRplmnCfgInfo->stWRplmnInNV.ulMnc;
    stRplmn.ucLastRplmnRatEnableFlg = pstRplmnCfgInfo->ucLastRplmnRatFlg;

    if(NV_OK != NV_Write(en_NV_Item_RPlmnWithRat, &stRplmn, sizeof(NAS_NVIM_RPLMN_WITH_RAT_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_WriteRplmnWithRatNvim(): en_NV_Item_RPlmnWithRat Error");
    }

    return;
}


VOS_UINT32 NAS_MM_IsGURplmnChanged(
    NAS_MML_PLMN_ID_STRU               *pstRPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat
)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulGRplmnCompareRslt;
    VOS_UINT32                          ulWRplmnCompareRslt;

    /* 默认RPlmn比较结果未发生改变 */
    ulGRplmnCompareRslt = VOS_TRUE;
    ulWRplmnCompareRslt = VOS_TRUE;

    /* 用于获取RPLMN的定制需求信息 */
    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    /* 判断全局变量中的LastRPLMN的接入技术是否发生改变 */
    if (enCurrRat != NAS_MML_GetLastRplmnRat())
    {
        /* RPlmn信息发生了改变，返回VOS_TRUE */
        return VOS_TRUE;
    }

    /* 判断全局变量中的双RPLMN是否支持 */
    if (VOS_FALSE == pstRplmnCfgInfo->ucMultiRATRplmnFlg)
    {
        ulGRplmnCompareRslt = NAS_MML_CompareBcchPlmnwithSimPlmn(pstRPlmnId,
                                                 &pstRplmnCfgInfo->stGRplmnInNV);

        ulWRplmnCompareRslt = NAS_MML_CompareBcchPlmnwithSimPlmn(pstRPlmnId,
                                                 &pstRplmnCfgInfo->stWRplmnInNV);
    }
    else
    {
        /* 支持双RPLMN, 则只判断对应接入技术的RPLMN */
        if (NAS_MML_NET_RAT_TYPE_GSM == enCurrRat)
        {
            ulGRplmnCompareRslt = NAS_MML_CompareBcchPlmnwithSimPlmn(pstRPlmnId,
                                                     &pstRplmnCfgInfo->stGRplmnInNV);
        }
        else if (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRat)
        {
            ulWRplmnCompareRslt = NAS_MML_CompareBcchPlmnwithSimPlmn(pstRPlmnId,
                                                     &pstRplmnCfgInfo->stWRplmnInNV);
        }
        else
        {
            ;
        }
    }

    /* RPlmn比较结果，VOS_FALSE表示发生了改变 */
    if ((VOS_FALSE == ulGRplmnCompareRslt)
     || (VOS_FALSE == ulWRplmnCompareRslt))
    {
        /* RPlmn信息发生了改变，返回VOS_TRUE */
        return VOS_TRUE;
    }

    /* RPlmn信息未发生改变，返回VOS_FALSE */
    return VOS_FALSE;

}




VOS_VOID NAS_MM_GenerateEPlmnInfo(
    VOS_UINT32                          ulLauAcceptPlmnNum,
    MM_PLMN_ID_STRU                    *pstLauAcceptPlmnList,
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
)
{
    VOS_UINT32                          i;
    NAS_MML_PLMN_ID_STRU               *pstPlmnId       = VOS_NULL_PTR;

    /* 检测网侧的Eplmn个数不大于15个 */
    if (ulLauAcceptPlmnNum > NAS_MML_MAX_NETWORK_EQUPLMN_NUM)
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_GenerateEPlmnInfo:NETWORK EPlmn NUMBER > 15");
        ulLauAcceptPlmnNum = NAS_MML_MAX_NETWORK_EQUPLMN_NUM;
    }

    /* 先添加当前驻留的plmn信息到EPlmn列表中 */
    pstPlmnId    = NAS_MML_GetCurrCampPlmnId();
    pstEquPlmnInfo->astEquPlmnAddr[0].ulMcc = pstPlmnId->ulMcc;
    pstEquPlmnInfo->astEquPlmnAddr[0].ulMnc = pstPlmnId->ulMnc;
    pstEquPlmnInfo->ucEquPlmnNum = 1;

    /* 添加网侧的EPlmn，EPLMN信息从第一个位置开始记录 */
    for ( i = 0; i < ulLauAcceptPlmnNum; i++ )
    {
        pstEquPlmnInfo->astEquPlmnAddr[1 + i].ulMcc = pstLauAcceptPlmnList[i].ulMcc;
        pstEquPlmnInfo->astEquPlmnAddr[1 + i].ulMnc = pstLauAcceptPlmnList[i].ulMnc;
        pstEquPlmnInfo->ucEquPlmnNum += 1;
    }

    /* 从EPLMN列表中删除无效 、禁止和不允许漫游的网络 */
    pstEquPlmnInfo->ucEquPlmnNum = (VOS_UINT8)NAS_MML_DelInvalidPlmnFromList(pstEquPlmnInfo->ucEquPlmnNum,
                                            pstEquPlmnInfo->astEquPlmnAddr);
    pstEquPlmnInfo->ucEquPlmnNum = (VOS_UINT8)NAS_MML_DelForbPlmnInList(pstEquPlmnInfo->ucEquPlmnNum,
                                            pstEquPlmnInfo->astEquPlmnAddr);

    return ;
}



VOS_VOID NAS_MM_ConvertMmlPlmnIdToNvimEquPlmn(
    NAS_MML_PLMN_ID_STRU               *pstMmlPlmnId,
    NVIM_PLMN_VALUE_STRU               *pstNvimPlmnId
)
{
    /* 转化MCC */
    pstNvimPlmnId->ucMcc[0] = (VOS_UINT8)(pstMmlPlmnId->ulMcc & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMcc[1] = (VOS_UINT8)((pstMmlPlmnId->ulMcc >> 8) & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMcc[2] = (VOS_UINT8)((pstMmlPlmnId->ulMcc >> 16) & NAS_MML_OCTET_LOW_FOUR_BITS);

    /* 转化MNC */
    pstNvimPlmnId->ucMnc[0] = (VOS_UINT8)(pstMmlPlmnId->ulMnc & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMnc[1] = (VOS_UINT8)((pstMmlPlmnId->ulMnc >> 8) & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMnc[2] = (VOS_UINT8)((pstMmlPlmnId->ulMnc >> 16) & NAS_MML_OCTET_LOW_FOUR_BITS);
}


VOS_VOID NAS_MM_ConvertMmlEquListToNvimEquPlmnList(
    NAS_MML_EQUPLMN_INFO_STRU          *pstMmlEPlmnList,
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNvimEPlmnList
)
{
    VOS_UINT8                           i;

    pstNvimEPlmnList->ucCount = pstMmlEPlmnList->ucEquPlmnNum;

    if (pstNvimEPlmnList->ucCount > NVIM_MAX_EPLMN_NUM)
    {
        pstNvimEPlmnList->ucCount = NVIM_MAX_EPLMN_NUM;
    }

    for (i = 0; i < pstNvimEPlmnList->ucCount; i++)
    {
        NAS_MM_ConvertMmlPlmnIdToNvimEquPlmn(&(pstMmlEPlmnList->astEquPlmnAddr[i]),
                                              &(pstNvimEPlmnList->struPlmnList[i]));

    }

    return;
}


VOS_UINT32 NAS_MM_IsInNvEplmnList(
    NVIM_PLMN_VALUE_STRU               *pstPlmnId,
    VOS_UINT8                           ucPlmnNum,
    NVIM_PLMN_VALUE_STRU               *pstPlmnIdList
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < ucPlmnNum ; i++ )
    {
        if ( (pstPlmnId->ucMcc[0] == pstPlmnIdList[i].ucMcc[0])
          && (pstPlmnId->ucMcc[1] == pstPlmnIdList[i].ucMcc[1])
          && (pstPlmnId->ucMcc[2] == pstPlmnIdList[i].ucMcc[2])
          && (pstPlmnId->ucMnc[0] == pstPlmnIdList[i].ucMnc[0])
          && (pstPlmnId->ucMnc[1] == pstPlmnIdList[i].ucMnc[1])
          && (pstPlmnId->ucMnc[2] == pstPlmnIdList[i].ucMnc[2]) )
        {
            return VOS_TRUE;
        }
    }
    return VOS_FALSE;
}


VOS_UINT32 NAS_MM_IsNvimEPlmnListEqual(
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNvimEPlmnList1,
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNvimEPlmnList2
)
{
    VOS_UINT32                          i;

    if (pstNvimEPlmnList1->ucCount != pstNvimEPlmnList2->ucCount)
    {
        return VOS_FALSE;
    }

    /* Eplmn个数大于0,但Rplmn不同时，EplmnList不相同 */
    if (pstNvimEPlmnList1->ucCount > 0)
    {
        if (VOS_FALSE == NAS_MM_IsInNvEplmnList(&(pstNvimEPlmnList1->struPlmnList[0]),
                                                 1,
                                                 pstNvimEPlmnList2->struPlmnList))
        {
            return VOS_FALSE;
        }
    }
    else
    {
        return VOS_TRUE;
    }

    /* 其它Eplmn没有进行排序且有重复数据，需要对比2个列表才能确定相同 */
    for ( i = 1 ; i < pstNvimEPlmnList1->ucCount ; i++ )
    {
        if (VOS_FALSE == NAS_MM_IsInNvEplmnList(&(pstNvimEPlmnList1->struPlmnList[i]),
                                                 pstNvimEPlmnList2->ucCount,
                                                 pstNvimEPlmnList2->struPlmnList))
        {
            return VOS_FALSE;
        }
    }

    for ( i = 1 ; i < pstNvimEPlmnList2->ucCount ; i++ )
    {
        if (VOS_FALSE == NAS_MM_IsInNvEplmnList(&(pstNvimEPlmnList2->struPlmnList[i]),
                                                 pstNvimEPlmnList1->ucCount,
                                                 pstNvimEPlmnList1->struPlmnList))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}


VOS_VOID NAS_MM_DeleteEPlmnList()
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEPlmnList    = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmnId = VOS_NULL_PTR;

    pstEPlmnList = NAS_MML_GetEquPlmnList();

    NAS_MML_InitEquPlmnInfo(pstEPlmnList);

    /* 清除NV中保存的EPLMN */
    NAS_MM_WriteEplmnNvim( pstEPlmnList );

    /*将当前网络添加Eplmn列表*/
    pstCurrPlmnId = NAS_MML_GetCurrCampPlmnId();

    pstEPlmnList->astEquPlmnAddr[0].ulMcc = pstCurrPlmnId->ulMcc;
    pstEPlmnList->astEquPlmnAddr[0].ulMnc = pstCurrPlmnId->ulMnc;

    pstEPlmnList->ucEquPlmnNum = 1;


    return;
}


VOS_VOID NAS_MM_WriteEplmnNvim(
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnAddr
)
{

    VOS_UINT32                          ulUpdateNvFlag;
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNewNvEquPlmnList = VOS_NULL_PTR;
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstOldNvEquPlmnList = VOS_NULL_PTR;

    ulUpdateNvFlag  = VOS_FALSE;

    pstNewNvEquPlmnList = (NVIM_EQUIVALENT_PLMN_LIST_STRU*)PS_MEM_ALLOC(
                                                      WUEPS_PID_MM,
                                                      sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU));

    if (VOS_NULL_PTR == pstNewNvEquPlmnList)
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_WriteEplmnNvim:ERROR: Memory Alloc Error");
        return;
    }

    pstOldNvEquPlmnList = (NVIM_EQUIVALENT_PLMN_LIST_STRU*)PS_MEM_ALLOC(
                                                        WUEPS_PID_MM,
                                                        sizeof (NVIM_EQUIVALENT_PLMN_LIST_STRU));

    if (VOS_NULL_PTR == pstOldNvEquPlmnList)
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_WriteEplmnNvim:ERROR: Memory Alloc Error");
        PS_MEM_FREE(WUEPS_PID_MM, pstNewNvEquPlmnList);
        return;
    }

    PS_MEM_SET(pstNewNvEquPlmnList, 0, sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU));
    PS_MEM_SET(pstOldNvEquPlmnList, 0, sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU));

    NAS_MM_ConvertMmlEquListToNvimEquPlmnList(pstEplmnAddr,
                                              pstNewNvEquPlmnList);

    /* 读取NV中EPLMN信息 */
    if ( NV_OK == NV_Read(en_NV_Item_EquivalentPlmn,
                         pstOldNvEquPlmnList, sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU)) )
    {
        if (VOS_FALSE == NAS_MM_IsNvimEPlmnListEqual(pstNewNvEquPlmnList,
                                                     pstOldNvEquPlmnList))
        {
            ulUpdateNvFlag = VOS_TRUE;
        }
    }
    else
    {
        ulUpdateNvFlag = VOS_TRUE;
    }

    if ( VOS_TRUE == ulUpdateNvFlag )
    {
        if (NV_OK != NV_Write(en_NV_Item_EquivalentPlmn,
                              pstNewNvEquPlmnList,
                              sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU)))
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_WriteEplmnNvim:WARNING: en_NV_Item_EquivalentPlmn Error");
        }
    }

    PS_MEM_FREE(WUEPS_PID_MM, pstNewNvEquPlmnList);
    PS_MEM_FREE(WUEPS_PID_MM, pstOldNvEquPlmnList);

}


VOS_VOID NAS_MM_UpdateEquPlmnInfo(
    VOS_UINT32                          ulCause
)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;

    enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();

    /* 如果LAU失败，需要判断是否删除EPLMN */
    switch (ulCause)
    {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_AUTH_REJ:

            NAS_MM_DeleteEPlmnList();

            break;

        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        case NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED:
        case NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT:
        case NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN:
        case NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS:
        case NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM:
        case NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI:
        case NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT:

            break;

        default:
           /* 其他原因值，如果LAU attempt acounter超过Roam broker特性注册失败的次数，需要清除EPLMN */
           if ((VOS_TRUE == NAS_MML_IsCsLaiChanged())
            || (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt >= MM_CONST_NUM_4)
            || (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED != enCsUpdateStatus))
            {
                NAS_MM_DeleteEPlmnList();

            }
           break;

    }

    return;
}


VOS_VOID NAS_MM_CsSimValid(VOS_BOOL *pbCsSimValid)
{
    if (VOS_TRUE == NAS_MML_GetSimCsRegStatus())
    {
        *pbCsSimValid = VOS_TRUE;
    }
    else
    {
        *pbCsSimValid = VOS_FALSE;
    }

    return;
}


VOS_VOID NAS_MM_CsCellBar(VOS_BOOL *pbCsCellBar)
{
    if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
    {
        *pbCsCellBar = VOS_TRUE;
    }
    else
    {
        *pbCsCellBar = VOS_FALSE;
    }

    return;
}


NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8 NAS_MM_GetLauUptNeededCsSrvStatus(VOS_VOID)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

    enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();

    /* 当前LAI和上次注册成功LAI相同，且更新状态为U1 */
    if((VOS_FALSE == NAS_MML_IsCsLaiChanged())
    && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus)
    && ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState ))
    {
        return MM_COM_SRVST_NORMAL_SERVICE;
    }
    else
    {
        return MM_COM_SRVST_LIMITED_SERVICE;
    }
}


VOS_VOID  NAS_MM_ProcCsAcChgRegisterNetModeIIUpdated()
{
    /* 如果LAI不变,更新状态为U1 */
    if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
    {
        if (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg)
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;       /* 设置LU类型                               */
            Mm_ComLuOnly();
        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;                /* 设置服务状态                             */
            Mm_ComNasInfoSav(MM_STATUS_ATTACHED,
                             NAS_MML_GetSimCsSecurityCksn());
            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
    }
    else
    {
        /* 当前是上电开机 */
        if (MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg)
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH;             /* 设置LU类型                               */
            Mm_ComLuOnly();                                                     /* 发送LU REQ                               */
        }
        else if (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg)
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;       /* 设置LU类型                               */
            Mm_ComLuOnly();                                                     /* 发送LU REQ                               */
        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;                /* 设置服务状态                             */
            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);


            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
    }
}

VOS_VOID NAS_MM_ProcCsAcChgRegisterNetModeIINotUpdated(VOS_VOID)
{
    if (MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg)                                 /* 刚开机，位置区不变，也发起注册 */
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;                   /* 设置LU类型                               */
        Mm_ComLuOnly();                                                         /* 发送LU REQ                               */
        return;
    }


    /* 在非U1状态并且周期注册定时器没有运行时,要进行一次LU过程 */
    if ((MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
     && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3212].ucTimerStatus)
     && (0x0 != gstMmTimer[MM_TIMER_T3212].ulTimerLen))
    {
        if (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg)
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
        }

        Mm_ComLuOnly();
    }
    else
    {
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;                /* 设置服务状态                             */
        Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
    }
}


VOS_VOID NAS_MM_ProcCsAcChgRegisterNetModeII(VOS_VOID)
{
    /* LAI发生改变 */
    if (VOS_TRUE == NAS_MML_IsCsLaiChanged())
    {
        Mm_TimerStop(MM_TIMER_T3213);
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;                   /* 设置LU类型                               */
        Mm_ComLuOnly();                                                         /* 发送LU REQ                               */
    }
    else
    {
        if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
        {
            /* 当前CS UPDATE状态为U1 */
            NAS_MM_ProcCsAcChgRegisterNetModeIIUpdated();
        }
        else
        {
            NAS_MM_ProcCsAcChgRegisterNetModeIINotUpdated();
        }
    }
}


VOS_VOID NAS_MM_UpdateMmStateCsRegRestrictBarToUnbar(VOS_VOID)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

    enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();

    if (MM_IDLE_NO_IMSI == g_MmGlobalInfo.ucStaOfRcvXXEstReq)
    {
        return;
    }

    /* 当前CS卡无效 */
    if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
    {
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_NO_IMSI;
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_NO_IMSI;
        g_MmGlobalInfo.ucMmServiceState   = MM_LIMITED_SERVICE;
        return;
    }

    /* 用户设置不支持CS */
    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_LIMITED_SERVICE;
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_LIMITED_SERVICE;

        g_MmGlobalInfo.ucMmServiceState   = MM_LIMITED_SERVICE;
        return;
    }

    /* 当前网络在禁止列表中 */
    if ((MMCMM_NO_FORBIDDEN != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
     && (MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_LIMITED_SERVICE;
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_LIMITED_SERVICE;

        g_MmGlobalInfo.ucMmServiceState   = MM_LIMITED_SERVICE;
        return;
    }

    /* 当前CS ATTACH状态，LAI没有改变，更新状态为U1 */
    if ((VOS_FALSE == NAS_MML_IsCsLaiChanged())
     && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus)
     && ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState ))
    {
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_NORMAL_SERVICE;
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_NORMAL_SERVICE;

        g_MmGlobalInfo.ucMmServiceState   = MM_NORMAL_SERVICE;
    }
    else
    {
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_LIMITED_SERVICE;
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_NORMAL_SERVICE;

        g_MmGlobalInfo.ucMmServiceState   = MM_LIMITED_SERVICE;
    }
}




VOS_VOID NAS_MM_ProcEccNumList_RcvSysinfo(
    VOS_UINT32                          ulMcc
)
{
    NAS_MML_EMERGENCY_NUM_LIST_STRU    *pstEmergencyNumList = VOS_NULL_PTR;
    NAS_MML_EMERGENCY_NUM_LIST_STRU     EmcNumLst;
    NAS_MML_PLMN_ID_STRU               *pstCurPlmnId        = VOS_NULL_PTR;

    pstCurPlmnId  = NAS_MML_GetCurrCampPlmnId();

    pstEmergencyNumList = NAS_MML_GetEmergencyNumList();

    /* 消息中包不含紧急呼列表但之前存储了紧急呼列表,如果不是同一个国家的mcc则，删除之前存储的紧急呼叫列表
    24008_CR2107R1_(Rel-11)_C1-121605 24008 4.4.4.6、4.7.3.1.3、4.7.5.1.3描述如下:
    The emergency number(s) received in the Emergency Number List IE are valid only
    in networks with in.the same MCCcountry as in  the cell on which this IE
    is received.*/
    if (VOS_FALSE == NAS_MML_ComparePlmnMcc(ulMcc, pstCurPlmnId->ulMcc))
    {                                                                       /* 新小区的MCC与上次驻留小区的MCC不同       */
        if (VOS_TRUE == NAS_MML_ComparePlmnMcc(ulMcc, pstEmergencyNumList->ulMcc))
        {
            Mm_SndCcEmergencyNumberList(pstEmergencyNumList);               /* 通知CC紧急呼号码 */
        }
        else
        {
            EmcNumLst.ulMcc             = ulMcc;
            EmcNumLst.ucEmergencyNumber = 0;

            PS_MEM_SET(EmcNumLst.aucEmergencyList, 0xFF, NAS_MML_EMERGENCY_NUM_LIST_MAX_RECORDS);
            Mm_SndCcEmergencyNumberList(&EmcNumLst);                            /* 通知CC紧急呼号码无效                     */
        }
    }

    return;
}


#if (FEATURE_LTE == FEATURE_ON)


VOS_UINT32  NAS_MM_IsLauNeededLaiNoChange_LInterSys(VOS_VOID)
{
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg;

    VOS_UINT8                                               ucLauForceFlg;
    VOS_UINT8                                               ucImsVoiceAvailFlg;

    enLteCsServiceCfg   = NAS_MML_GetLteCsServiceCfg();

    /**
     * 如果不是从 L 异系统变换 则不进行后续判断
     */
    if (NAS_MML_NET_RAT_TYPE_LTE != g_MmGlobalInfo.enPreRatType)
    {
        return VOS_FALSE;
    }

    /* 如果CS业务配置为SMS over SGs，而且TIN类型为"GUTI" */
    if ((NAS_MML_TIN_TYPE_GUTI == NAS_MML_GetTinType())
     && ((NAS_MML_LTE_SUPPORT_SMS_OVER_SGS_ONLY == enLteCsServiceCfg)
      || (NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == enLteCsServiceCfg)))
    {
        return VOS_TRUE;
    }

    /**
     * 新增场景：如果UE支持IMS（读取Nv且语音优选域不是CS ONLY)
     * 且控制从L到GU下即使LAI没有改变也需要进行LAU的Nv项打开，
     * 只要无CSFB服务，则需要进行LAU
     */
    /**
     * VDF的标书要求支持IMS voice的终端在从L异系统变换到GU后，无条件进行一次LAU,原文如下：
     * The LTE terminal supporting Voice over IMS (GSMA IR.92),
     * shall always issue a Location Update following a RAT change.
     * With terminal in IDLE mode a LAU is performed.
     * If a call is initiated under CS network,
     * all the procedures currently in use today shall be applicable.
     * For example, when a terminal that initially registers on 2G roams into LTE coverage,
     * then roams back into 2G under the same LAC that it previously registered,
     * will it always send a LU towards the MSC.
     */

    ucLauForceFlg = NAS_MML_GetImsVoiceInterSysLauEnableFlg();
    ucImsVoiceAvailFlg = NAS_MML_GetImsVoiceAvailFlg();

    if ((VOS_TRUE == ucLauForceFlg)
     && (VOS_TRUE == ucImsVoiceAvailFlg))
    {
        return VOS_TRUE;
    }

    if ((VOS_TRUE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
     && (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg))
    {
        return VOS_TRUE;
    }

    /* 23122_CR0122R1_(Rel-8)_C1-083459 23122 4.5.2章节描述如下:
    -The MS detects that it has entered a registration area that has the same identity
    as the one stored in the MS, while being in the ROAMING NOT ALLOWED update state,
    and the LAI or the PLMN identity is not contained in any of the lists of "forbidden LAs for roaming",
    "forbidden LAs for regional provision of service", "forbidden PLMNs for GPRS service"
    or "forbidden PLMNs" respectively. */
    if (NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED == NAS_MML_GetCsUpdateStatus())
    {
        return VOS_TRUE;
    }

    /* TS 24301 5.5.3.3.6章节描述如下:
     * 3)otherwise, the abnormal cases specified in subclause 5.5.3.2.6 apply with the following modification.
     *   If the tracking area updating attempt counter is incremented according to subclause 5.5.3.2.6 the next actions depend on
     *   the value of the tracking area updating attempt counter.
     *   - If the tracking area updating attempt counter is less than 5, the UE shall set the update status to U2 NOT UPDATED,
     *     but shall not delete any LAI, TMSI, ciphering key sequence number and list of equivalent PLMNs;
     *
     * TS 23122 4.5.2章节描述如下:
     * - the MS changes cell while the update status is "NOT UPDATED";(for MS capable of GPRS and non-GPRS services when at least
     *   one of both update statuses is "NOT UPDATED")
     */

    if (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == NAS_MML_GetCsUpdateStatus())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MM_IsT3412ExpiredNeedRegist(
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg,
    NAS_MML_TIN_TYPE_ENUM_UINT8                             enTinType,
    NAS_MML_TIMER_INFO_ENUM_UINT8                           enT3412Status
)
{
     /* 3GPP 24.008中4.4.1  Location updating procedure章节描述如下：
        The normal location updating procedure shall also be started if the MS is
        configured to use CS fallback and SMS over SGs, or SMS over SGs only,
        and the TIN indicates "RAT-related TMSI",
        - when the periodic tracking area update timer T3412 expires and the
        network operates in network operation mode II or III
    */
    if ((NAS_MML_TIMER_EXP == enT3412Status)
     && ((NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == enLteCsServiceCfg)
      || (NAS_MML_LTE_SUPPORT_SMS_OVER_SGS_ONLY == enLteCsServiceCfg))
     && (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MM_IsT3423StatusChangeNeedRegist(
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg,
    NAS_MML_TIN_TYPE_ENUM_UINT8                             enTinType,
    NAS_MML_TIMER_INFO_ENUM_UINT8                           enT3423Status
)
{
      /* 3GPP 24.008中4.4.1  Location updating procedure章节描述如下：
       The normal location updating procedure shall also be started when the MS,
       configured to use CS fallback and SMS over SGs, or SMS over SGs only,
       enters a GERAN or UTRAN cell in network operation mode II or III and the
       E-UTRAN deactivate ISR timer T3423 has expired.

       The normal location updating procedure shall also be started if the MS is
       configured to use CS fallback and SMS over SGs, or SMS over SGs only,
       and the TIN indicates "RAT-related TMSI",
       -   when the MS enters a GERAN or UTRAN cell in network operation mode II
       or III and the E-UTRAN deactivate ISR timer T3423 is running.
    */
    if (((NAS_MML_TIMER_START == enT3423Status)
      || (NAS_MML_TIMER_EXP == enT3423Status))
     && ((NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == enLteCsServiceCfg)
      || (NAS_MML_LTE_SUPPORT_SMS_OVER_SGS_ONLY == enLteCsServiceCfg))
     && (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_VOID  NAS_MM_WriteTinInfoNvim(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType,
    VOS_UINT8                          *pucImsi
)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;

    NAS_NVIM_TIN_INFO_STRU              stTinInfo;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    /*
        The following EMM parameter shall be stored in a non-volatile memory in the
        ME together with the IMSI from the USIM:
        -   TIN.
        This EMM parameter can only be used if the IMSI from the USIM matches the
        IMSI stored in the non-volatile memory of the ME; else the UE shall delete
        the EMM parameter.
    */

    if (pstRplmnCfgInfo->enTinType != enTinType)
    {
        /* 先更新MML的参数 */
        pstRplmnCfgInfo->enTinType  = enTinType;
        PS_MEM_CPY(pstRplmnCfgInfo->aucLastImsi, pucImsi, sizeof(pstRplmnCfgInfo->aucLastImsi));

        /* 再更新NVIM中的参数 */
        stTinInfo.ucTinType        = pstRplmnCfgInfo->enTinType;
        PS_MEM_CPY(stTinInfo.aucImsi, pstRplmnCfgInfo->aucLastImsi, sizeof(stTinInfo.aucImsi));
        PS_MEM_SET(stTinInfo.aucReserve, 0, sizeof(stTinInfo.aucReserve));

        /* 保存在NVIM中 */
        if (NV_OK != NV_Write (en_NV_Item_TIN_INFO,
                               &stTinInfo,
                               sizeof(stTinInfo)))
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_WriteTinInfoNvim:Write NV Failed");
        }

        /* 可维可测，勾消息 */
        NAS_MM_LogTinTypeInfo(enTinType);
    }
}


VOS_VOID NAS_MM_LogTinTypeInfo(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType
)
{
    NAS_MM_LOG_TIN_INFO_STRU           *pstTinTypeInfo = VOS_NULL_PTR;

    pstTinTypeInfo = (NAS_MM_LOG_TIN_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MM,
                             sizeof(NAS_MM_LOG_TIN_INFO_STRU));

    if ( VOS_NULL_PTR == pstTinTypeInfo )
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_LogTinTypeInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstTinTypeInfo->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstTinTypeInfo->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstTinTypeInfo->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstTinTypeInfo->stMsgHeader.ulReceiverPid   = WUEPS_PID_MM;
    pstTinTypeInfo->stMsgHeader.ulLength        = sizeof(NAS_MM_LOG_TIN_INFO_STRU) - VOS_MSG_HEAD_LENGTH;;
    pstTinTypeInfo->stMsgHeader.ulMsgName       = NAS_MM_LOG_TIN_TYPE_INFO_IND;

    pstTinTypeInfo->enTinType = enTinType;

    DIAG_TraceReport(pstTinTypeInfo);

    PS_MEM_FREE(WUEPS_PID_MM, pstTinTypeInfo);

    return;
}


VOS_UINT32 NAS_MM_IsNeedDeactiveIsrLauInit(VOS_VOID)
{
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg;
    NAS_MML_TIN_TYPE_ENUM_UINT8                             enTinType;
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus;
    VOS_INT8                                                cVersion;


    cVersion       = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_CS);
    enLteCapStatus = NAS_MML_GetLteCapabilityStatus();

    /* 24008_CR1902R1_(Rel-11)_C1-113481-c1-113200-tin 24008 4.4.4.1描述如下:
    If the mobile station is configured to use CS fallback and SMS over SGs, or SMS over SGs only,
    and TIN indicates "RAT-related TMSI" the mobile station shall set the TIN to "P-TMSI"
    unless the mobile station had already received the EMM cause #18 during a combined
    attach procedure (see subclause 5.5.1.3.4.3 of 3GPP TS 24.301 [120]) or a combined
    tracking area updating procedure (see subclause 5.5.3.3.4.3 of 3GPP TS 24.301 [120])
    on the same PLMN, but not disabled the E-UTRAN capability.*/
    enTinType         = NAS_MML_GetTinType();
    enLteCsServiceCfg = NAS_MML_GetLteCsServiceCfg();

    if (((NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == enLteCsServiceCfg)
       || (NAS_MML_LTE_SUPPORT_SMS_OVER_SGS_ONLY == enLteCsServiceCfg))
     && (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType)
     && (cVersion >= PS_PTL_VER_R11))
    {
        if ((VOS_TRUE == NAS_MML_IsPlmnIdInCsDomainUnAvailPlmnList(NAS_MML_GetCurrCampPlmnId()))
         && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapStatus)
         && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapStatus))
        {
            return VOS_FALSE;
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_MM_IsNeedDeactiveIsrAfterLau(VOS_VOID)
{
    VOS_UINT32                                             ulT3423StatusChgNeedRegFlg;
    VOS_UINT32                                             ulT3412StatusChgNeedRegFlg;

    /* 3GPP 23401 4.3.5.6 Idle mode signalling reduction function描述去激活ISR场景：
       After a LAU procedure if the UE has CS fallback and/or SMS over SGs activated.*/
    ulT3423StatusChgNeedRegFlg = NAS_MM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                         NAS_MML_GetTinType(), NAS_MML_GetT3423Status());

    ulT3412StatusChgNeedRegFlg = NAS_MM_IsT3412ExpiredNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                         NAS_MML_GetTinType(), NAS_MML_GetT3412Status());

    if ((VOS_TRUE == ulT3423StatusChgNeedRegFlg)
     || (VOS_TRUE == ulT3412StatusChgNeedRegFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MM_RcvSysInfoSurpportLte_PreProc(VOS_VOID)
{
    VOS_UINT32                          ulT3423StatusChgNeedRegFlg;

    VOS_UINT32                          ulLaiChangeFlag;
    LAU_TYPE_ENUM_UINT8                 enLauType;

    ulLaiChangeFlag = NAS_MML_IsCsLaiChanged();
    enLauType       = MM_IE_LUT_TYPE_BUTT;

    /* 调整定时器名称 */
    if ( MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_NORMAL_CSFB_HO_WAIT_SYSINFO) )
    {
        Mm_TimerStop(MM_TIMER_NORMAL_CSFB_HO_WAIT_SYSINFO);
    }

    if ( MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_EMERGENCY_CSFB_HO_WAIT_SYSINFO) )
    {
        Mm_TimerStop(MM_TIMER_EMERGENCY_CSFB_HO_WAIT_SYSINFO);
    }

    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        /* 记录状态为CSFB MT已收到系统消息 */
        NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_GU_SYS_INFO_RECEIVED,
                                  NAS_MML_REG_FAIL_CAUSE_NULL);

        NAS_MM_RcvSysInfo_CSFB();

        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        return VOS_TRUE;
    }

    if ( VOS_TRUE == NAS_MML_GetDelayedCsfbLauFlg() )
    {
        /* CSFB流程从L异系统变换到GU,网络模式II,LAI未改变时先做业务，
           记录需要等业务结束后做LAU */
        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);

        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        return VOS_TRUE;
    }

    /* 如果CS业务配置为SMS over SGs或CSFB和短信都支持，而且TIN类型为"GUTI"
       3GPP 24008 4.4.1:
       indicating to the network that the MS, configured to use CS fallback and
       SMS over SGs, or SMS over SGs only, has entered a GERAN or UTRAN cell
       in NMO II or III, after intersystem change from S1 mode to Iu
       or A/Gb mode, the TIN indicates "GUTI" and the location area of
       the current cell is the same as the stored location area; */

    if (VOS_TRUE == NAS_MM_IsLauNeededLaiNoChange_LInterSys())
    {
        /* 发起LAU流程 有紧急呼先进行紧急呼*/
        enLauType = NAS_MM_GetLuType();
        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, enLauType);



        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        return VOS_TRUE;
    }

    /* 3GPP 24.008中4.4.1   Location updating procedure章节描述:
       The normal location updating procedure shall also be started if
       the MS is configured to use CS fallback and SMS over SGs,
       or SMS over SGs only, and the TIN indicates "RAT-related TMSI",
       when the MS enters a GERAN or UTRAN cell in network operation
       mode II or III and the E-UTRAN deactivate ISR timer T3423 is running.
       The normal location updating procedure shall also be started when
       the MS, configured to use CS fallback and SMS over SGs, or SMS over
       SGs only, enters a GERAN or UTRAN cell in network operation mode
       II or III and the E-UTRAN deactivate ISR timer T3423 has expired*/
    ulT3423StatusChgNeedRegFlg = NAS_MM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                           NAS_MML_GetTinType(), NAS_MML_GetT3423Status());

    if (VOS_TRUE == ulT3423StatusChgNeedRegFlg)
    {
        /* 发起LAU流程 有紧急呼先进行紧急呼*/
        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_PERIODIC_UPDATING);


        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#endif

VOS_UINT8 NAS_MM_GetLuType(VOS_VOID)
{
    if ( VOS_TRUE == NAS_MML_IsCsLaiChanged() )
    {
        return MM_IE_LUT_NORMAL_LU;
    }
    else if((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
         && (MM_TRUE     == g_MmGlobalInfo.ucPowerOnFlg)
         && (MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg))
    {
        return MM_IE_LUT_IMSI_ATTACH;
    }
    else if ( MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
    {
        return MM_IE_LUT_PERIODIC_UPDATING;
    }
    else
    {
        return MM_IE_LUT_NORMAL_LU;
    }
}


VOS_VOID  NAS_MM_LogMmStateInfo(
    NAS_MM_STATE_ENUM_UINT8             ucMmState
)
{
    NAS_MM_LOG_STATE_INFO_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_MM_LOG_STATE_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MM,
                                         sizeof(NAS_MM_LOG_STATE_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_LogMmStateInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(NAS_MM_LOG_STATE_INFO_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MM_LOG_STATE_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = MMOM_LOG_STATE_INFO_IND;
    pstMsg->enMmState                   = ucMmState;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MM, pstMsg);

    return;
}


VOS_UINT32 NAS_MM_IsCcTiValid(VOS_VOID)
{
    if ((MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
      ||(MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_VOID NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(
    VOS_UINT32                          ulLaiChangeFlag,
    VOS_UINT8                           ucLuType
)
{
    VOS_UINT32                          ulCsfbEmgCallLaiChgLauFirstFlg;
    VOS_UINT32                          ulCsRestrictRegFlg;

    VOS_UINT32                          ulEmergencyCallFlg;

    ulEmergencyCallFlg             = Mm_ComJudgeCsServExist();

    ulCsRestrictRegFlg             = NAS_MML_GetCsRestrictRegisterFlg();
    ulCsfbEmgCallLaiChgLauFirstFlg = NAS_MML_GetCsfbEmgCallLaiChgLauFirstFlg();

    if (VOS_FALSE == ulLaiChangeFlag)
    {
        /* LAI未改变且存在缓存的紧急呼叫则先进行紧急呼叫，呼叫结束后再做lau */
        if (MM_CS_SERV_EMERGENCY_CALL_EXIST == ulEmergencyCallFlg)
        {
#if (FEATURE_LTE == FEATURE_ON)
            /* 记录delay lau标识，呼叫结束后收到系统消息需要做lau */
            NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);
#endif

            /* 不禁止CS并且LAI不改变时，在连接释放后需要进行LU */
            if ((MMCMM_NO_FORBIDDEN == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
             || ((MMCMM_NO_FORBIDDEN != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
                &&(MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)))
            {
                if ((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED != NAS_MML_GetCsUpdateStatus())
                 && ((MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
                  && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3212].ucTimerStatus)
                  && (0x0 != gstMmTimer[MM_TIMER_T3212].ulTimerLen)))
                {
                    NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);
                }
            }
            g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB();/* 记录收到建立请求时的状态                 */

            /* 紧急呼叫的时候,等待进行LAU后上报注册结果,后面会进行delay的LAU流程
               正常呼叫的时候,可以上报假流程注册成功 */

            Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());

            NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
            return;
        }

        /* 无缓存的紧急呼叫直接进行lau */
        g_MmGlobalInfo.LuInfo.ucLuType = ucLuType;
        Mm_ComLuOnly();
        return;
    }

    /* 存在缓存的紧急呼叫lai改变先进行紧急呼叫结束后再做lau nv开启 */
    if (((VOS_FALSE == ulCsfbEmgCallLaiChgLauFirstFlg)
      || ((VOS_TRUE == ulCsfbEmgCallLaiChgLauFirstFlg)
       && (VOS_TRUE == ulCsRestrictRegFlg)))
     && (MM_CS_SERV_EMERGENCY_CALL_EXIST == ulEmergencyCallFlg))
    {
#if (FEATURE_LTE == FEATURE_ON)
         /* 记录delay lau标识，呼叫结束后收到系统消息需要做lau */
        NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);
#endif
        /* 不禁止CS并且LAI不改变时，在连接释放后需要进行LU */
        if ((MMCMM_NO_FORBIDDEN == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
         || ((MMCMM_NO_FORBIDDEN != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
            &&(MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)))
        {
            NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);
        }
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB();/* 记录收到建立请求时的状态                 */

        /* 紧急呼叫的时候,等待进行LAU后上报注册结果,后面会进行delay的LAU流程
           正常呼叫的时候,可以上报假流程注册成功 */

        Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());

        NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);

        return;
    }

    /* 无缓存的紧急呼叫直接进行lau */
    g_MmGlobalInfo.LuInfo.ucLuType = ucLuType;
    Mm_ComLuOnly();
    return;
}



VOS_UINT32  NAS_MM_IsCsEnableLau( VOS_VOID )
{

    /* CS域的卡无效,不需要进行 */
    if ( VOS_FALSE == NAS_MML_GetSimCsRegStatus()  )
    {
        return VOS_FALSE;
    }

    /* CS域不允许aTTach,不需要进行 */
    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        return VOS_FALSE;
    }

    /* CS域接入受限,不需要进行 */
    if ( VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        return VOS_FALSE;
    }

    /* 当前是禁止网络,不需要进行 */
    if ((MMCMM_NO_FORBIDDEN !=g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        return VOS_FALSE;
    }

    /* T3211定时器运行,不需要进行 */
    if (MM_TIMER_RUNNING == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
    {
        return VOS_FALSE;
    }


    return VOS_TRUE;
}



VOS_UINT32  NAS_MM_IsNeedLauCsSigRel( VOS_VOID )
{
    /* 调用此函数前,如果需要判断信令连接状态,需要由调用此函数的上级函数保证 */

    if ( (VOS_TRUE == NAS_MML_IsCsLaiChanged())
      && ((MM_TRUE == g_MmGlobalInfo.ucConnRcvSysFlg)
       || (VOS_TRUE == g_MmGlobalInfo.ucLauAcceptContainDiffNbLaiFlg)) )
    {
        return VOS_TRUE;
    }

#if (FEATURE_LTE == FEATURE_ON)

    if (VOS_TRUE == NAS_MML_GetDelayedCsfbLauFlg())
    {
        return VOS_TRUE;
    }
#endif

    return VOS_FALSE;
}

VOS_UINT32  NAS_MM_IsAbleRecover_EstCnfFailResult(
    RRC_NAS_EST_RESULT_ENUM_UINT32      enEstResult
)
{
    /* RRC_EST_RJ_CELL_BAR不可恢复 */
    if ((RRC_EST_IMMEDIATE_ASSIGN_REJECT == enEstResult)
     || (RRC_EST_ACCESS_BARRED           == enEstResult)
     || (RRC_EST_OTHER_ACCESS_BARRED     == enEstResult)
     || (RRC_EST_RJ_T3122_RUNNING        == enEstResult)
     || (RRC_EST_RJ_CELL_BAR             == enEstResult))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32  NAS_MM_IsNeedCmServiceRetry_RelIndResult(
    RRC_REL_CAUSE_ENUM_UINT32           enRelCause
)
{
    return VOS_TRUE;
}

VOS_VOID NAS_MM_ProcConnFailLauAttmptCntLess4_RcvRelInd(
    RRC_REL_CAUSE_ENUM_UINT32                   enRelCauses
)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;
    VOS_UINT8                                               ucGsmEstConnFailFlg = MM_FALSE;
    MM_LAI_STRU                                            *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstCampLaiInfo  = VOS_NULL_PTR;

    if ( (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
     && (RRC_REL_CAUSE_CONN_FAIL   == enRelCauses))
    {
        ucGsmEstConnFailFlg = MM_TRUE;
    }

    enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
    if ((VOS_FALSE == NAS_MML_IsCsLaiChanged())
      && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
    {                                                                   /* 如果LAI不变,且更新状态为U1的时候         */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* 记录前状态                               */
        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;
        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_ProcConnFailLauAttmptCntLess4_RcvRelInd:INFO: MmServiceState is MM_NORMAL_SERVICE");

        if (MM_FALSE == ucGsmEstConnFailFlg)
        {
            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);            /* 向MMC发送MMCMM_LU_RESULT_IND             */

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);            /* 向MMC发送MMCMM_LU_RESULT_IND             */

        }

        Mm_ComNasInfoSav(MM_STATUS_ATTACHED,
                         NAS_MML_GetSimCsSecurityCksn());
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_ProcConnFailLauAttmptCntLess4_RcvRelInd: STATUS is MM_IDLE_NORMAL_SERVICE");
        Mm_TimerStart(MM_TIMER_T3211);                                  /* 启动T3211                                */
        g_T3211Flag = 1;
    }
    else
    {
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_ProcConnFailLauAttmptCntLess4_RcvRelInd: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

        if (MM_FALSE == ucGsmEstConnFailFlg)
        {
            /* 在U2状态，保存当前的LAI信息 */
            pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
            pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

            pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
            pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
            pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            /* 进U2的公共处理 */
            Mm_ComToU2Handle();
        }
        else
        {
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
        }

        Mm_TimerStart(MM_TIMER_T3211);                                  /* 启动T3211                                */
    }

}



VOS_VOID NAS_MM_SndMmcRrConn_RcvRelInd(VOS_VOID)
{
    VOS_UINT8                           ucTiValidFlg = MM_TRUE;

    if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                      .RcvXXEstReq.ucFlg)
     ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                      .RcvXXEstReq.ucFlg)
     ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                      .RcvXXEstReq.ucFlg))
    {
        ucTiValidFlg = Mm_ComTiChk();
        if (MM_FALSE == ucTiValidFlg)
        {
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                   /* RR连接不存在                             */

            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }
    }
    else
    {
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                      /* RR连接不存在                             */

        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }

}






VOS_VOID NAS_MM_LocalDetach_MmInterRatChange(VOS_VOID)
{
    Mm_TimerStop(MM_TIMER_STOP_ALL);

    /* 通知GMM当前CS域已本地DETACH超时处理 */
    NAS_MM_SndGmmCsLocalDetachInd();

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
    Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                     NAS_MML_GetSimCsSecurityCksn());                           /* 设置MM信息                               */

    /* 设置服务状态为DETACHED */
    g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;

    /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                 & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MM_DETACHED);
        /* 清除等待标志 */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

    /* 备份全局变量在CS域进行本地detach后需要进行删除 */
    if ( ( MMC_SUSPEND_CAUSE_CELLCHANGE == g_MmGlobalInfo.stSuspendShare.ucSuspendCause )
      && ( MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucSuspendPreState ) )
    {
        NAS_MM_InitCcoFallbackCtx();
    }

    /* 由于mm迁移了状态,3212在挂起状态未停止,此时需要停止 */
    Mm_TimerStop(MM_TIMER_T3212);

    if (MM_IDLE_NO_IMSI == g_MmGlobalInfo.ucSuspendPreState)
    {
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;
        g_MmGlobalInfo.ucSuspendPreState = MM_IDLE_NO_IMSI;
        g_MmGlobalInfo.ucPreState = MM_IDLE_NO_IMSI;
    }
    else
    {
        g_MmGlobalInfo.ucSuspendPreState = MM_IDLE_LIMITED_SERVICE;
        g_MmGlobalInfo.ucPreState = MM_IDLE_LIMITED_SERVICE;
        g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;
    }

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    g_MmGlobalInfo.stBackupShare.ucState                    = g_MmGlobalInfo.ucSuspendPreState;

    g_MmGlobalInfo.stBackupShare.ucPreState                 = g_MmGlobalInfo.ucSuspendPreState;

    g_MmGlobalInfo.stBackupShare.enMmServiceState           = g_MmGlobalInfo.ucMmServiceState;

    return;
}


VOS_VOID NAS_MM_LocalDetach_MmNoImsi(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    pstConnStatus = NAS_MML_GetConnStatus();

    /* 本地去注册通用操作 */
    Mm_TimerStop(MM_TIMER_STOP_ALL);

    /* 通知GMM当前CS域已本地DETACH超时处理 */
    NAS_MM_SndGmmCsLocalDetachInd();

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);

    /* 建链不成功，直接本地DETACH */
    Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                     NAS_MML_GetSimCsSecurityCksn());

    /* 设置服务状态为DETACHED */
    g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;

    /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MM_NO_IMSI);

        /* 清除等待标志 */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

    /* 通知MMC当前卡无效 */
    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

    /* 如果当前有信令链接，则释放链接 */
    if ( VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg )
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    }


    return;
}


VOS_VOID NAS_MM_RcvMmTimerProtectCsDetachExpired(VOS_VOID)
{
    NAS_MM_LocalDetach();

    return;

}


VOS_VOID NAS_MM_LocalDetach(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;
    VOS_UINT32                          ulMmState;

    pstConnStatus = NAS_MML_GetConnStatus();
    ulMmState     = Mm_GetState();

    /* 本地状态处理 */
    switch ( ulMmState )
    {
        case MM_INTER_RAT_CHANGE :

            /* 异系统时候的本地去注册处理，处理完毕直接返回 */
            NAS_MM_LocalDetach_MmInterRatChange();
            return;

        case MM_IDLE_NO_IMSI :

            /* NO IMSI的本地去注册处理，处理完毕直接返回 */
            NAS_MM_LocalDetach_MmNoImsi();
            return;

#if (FEATURE_ON == FEATURE_ECALL)
        case MM_IDLE_ECALL_INACTIVE:

            NAS_MM_ProcMmcMmDetachReq_MmIdleECallInactive();
            return;
#endif

        /* 不进行状态迁移的处理 */
        case MM_STATE_NULL :
            break;

        default:
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            break;
    }

    /* 本地去注册通用操作 */
    Mm_TimerStop(MM_TIMER_STOP_ALL);

    /* 通知GMM当前CS域已本地DETACH超时处理 */
    NAS_MM_SndGmmCsLocalDetachInd();

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);

    /* 建链不成功，直接本地DETACH */
    Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                     NAS_MML_GetSimCsSecurityCksn());

    /* 设置服务状态为DETACHED */
    g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;

    /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MM_DETACHED);

        /* 清除等待标志 */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

    /* 通知MMC当前服务域不支持 */
    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    /* 如果当前有信令链接，则释放链接 */
    if ( VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg )
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    }

    return;

}


VOS_VOID NAS_MM_StartDetachProtectingTimer(
    MMCMM_DETACH_REQ_STRU              *pstMsg
)
{
    /* Detach流程保护定时器时长 */
    VOS_UINT32                          ulDetachTimerVal;

    /* MM的CS域Detach保护定时器运行状态 */
    VOS_UINT32                          ulCsDetachTimerStatus;

    if (MMC_MM_DETACH_REASON_USER_DETACH == pstMsg->enDetachReason)
    {
        /* 用户触发的DETACH的时长: 90s */
        ulDetachTimerVal = NAS_MM_TIMER_PROTECT_DETACH_NOT_BY_SYSCFG_VALUE;
    }
    else
    {
        /* 如果当前是SYSCFG或服务域触发的DETACH,则设置保护定时器的时长为26s */
        ulDetachTimerVal = NAS_MM_TIMER_PROTECT_DETACH_BY_SYSCFG_VALUE;
    }

    /* 获取MM的Detach保护定时器运行状态 */
    ulCsDetachTimerStatus = NAS_MM_QryTimerStatus(MM_TIMER_PROTECT_CS_DETACH);

    /* 如果MM的CS域Detach保护定时器在运行，则不启动CS域Detach保护定时器 */
    if ( MM_TIMER_RUNNING == ulCsDetachTimerStatus )
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_StartDetachProtectingTimer:WARN:TIMER HAS BEEN STARTED ALREADY");
        Mm_TimerStop(MM_TIMER_PROTECT_CS_DETACH);
    }

    /* 设置MM的CS域Detach保护定时器时长 */
    gstMmTimer[MM_TIMER_PROTECT_CS_DETACH].ulTimerLen = ulDetachTimerVal;

    /* 启动MM的CS域detach保护定时器 */
    Mm_TimerStart(MM_TIMER_PROTECT_CS_DETACH);

    return;
}



VOS_VOID NAS_MM_RcvRrMmEstCnf_ExistCsDetachBuffer(
    RRMM_EST_CNF_STRU                  *pRrcEstCnf
)
{
    MM_MSG_IMSI_DETACH_IND_STRU         stMsg;

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

    NAS_NORMAL_LOG(WUEPS_PID_MM, "NAS_MM_RcvRrMmEstCnf_ExistCsDetachBuffer: Release all MM connection");
    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    /* 如果当前建链成功，且有缓存用户发起的IMSI detach请求，则直接发起去注册 */
    if ( (RRC_EST_SUCCESS == pRrcEstCnf->ulResult)
      || (RRC_EST_PRESENT == pRrcEstCnf->ulResult))
    {

        /* 设置DETACH类型，否则在收到REL时候，不回复MMC的DETACH CNF */
        g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;

        g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt = 0;
        g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_PRESENT;             /* 设置信令连接已存在                       */
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ESTED);                        /* RR连接建立成功                           */

        /* 填写消息,发送IMSI detach消息 */
        NAS_MM_FillMobileID(&(stMsg.MmIeMobileId.MobileID));

        Mm_ComSetMmState(IMSI_DETACH_INITIATED);

        Mm_ComMsgImsiDetachIniSndOfDataReq(&stMsg);
        Mm_TimerStart(MM_TIMER_T3220);                                      /* 启动T3220                                */


        return;
    }

    /* MM进行本地DETACH */
    NAS_MM_LocalDetach();

    return;

}



VOS_UINT32 NAS_MM_IsNeedGmmProcUserDetach(VOS_VOID)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo       = VOS_NULL_PTR;
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo    = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    /* 获取当前网络模式 */
    pstCampInfo       = NAS_MML_GetCurrCampPlmnInfo();

    /* 获取当前的网络信息 */
    pstNetWorkInfo    =  NAS_MML_GetNetworkInfo();

    ulRet             = VOS_FALSE;


    /* 非网络模式I下，不用GMM处理用户发起的detach */
    if ( NAS_MML_NET_MODE_I != pstCampInfo->enNetworkMode )
    {
        return VOS_FALSE;
    }

    /* PS域不准许注册，不用GMM处理用户发起的detach */
    if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
    {
        return VOS_FALSE;
    }

    /* PS域注册首限，不用GMM处理用户发起的detach */
    if ( VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg() )
    {
        return VOS_FALSE;
    }

    /* PS 卡无效，不用GMM处理用户发起的detach */
    if ( VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }

    /* 当前小区是否支持GPRS */
    if ( VOS_FALSE == pstNetWorkInfo->stPsDomainInfo.ucPsSupportFlg )
    {
        return VOS_FALSE;
    }

    /* 当前小区是否在FORB GPRS PLMN里面 */

    ulRet = NAS_MML_IsSimPlmnIdInDestBcchPlmnList( &(pstCampInfo->stLai.stPlmnId),
                                           pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                           pstForbidPlmnInfo->astForbGprsPlmnList );
    if ( VOS_TRUE == ulRet )
    {
        return VOS_FALSE;
    }

    /* MM已处于ATTACHED状态，但当前GS接口不存在 */
    if ( (VOS_FALSE          == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
      && (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState) )
    {
        return VOS_FALSE;
    }

    /* 否则用户发起的CS域的DETACH，可由GMM进行处理 */
    return VOS_TRUE;

}



VOS_UINT32 NAS_MM_IsLauNeeded_NetModeChange(VOS_VOID)
{
    /* LAI改变，需要触发LAU */
    if (VOS_TRUE == NAS_MML_IsCsLaiChanged())
    {
        return VOS_TRUE;
    }

    /* LAI/RAC都没改变 */
    if (g_MmGlobalInfo.MsCsInfo.ucOldRac == NAS_MML_GetCurrCampRac())
    {
        return VOS_FALSE;
    }

    /* 开机W下联合注册但PS ONLY成功，后模式改变为II，也需要LAU */
    if ( (MM_ATT_NEED  == g_MmGlobalInfo.ucAttFlg)
      && (MM_TRUE      == g_MmGlobalInfo.ucPowerOnFlg) )
    {
        return VOS_TRUE;
    }

    /* I->II, GS口存在，需要LAU */
    if ( (VOS_FALSE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
      && (VOS_TRUE  == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg) )
    {
        return VOS_TRUE;
    }

    /* 其他不需要触发LAU  */
    return VOS_FALSE;
}




VOS_UINT32 NAS_MM_IsEmergencyCallEndTrigLau(VOS_VOID)
{
    VOS_UINT8                           ucEmergencyServiceFlg;
    VOS_UINT8                           ucCsAttachAllowFlg;
    VOS_UINT8                           ucSimCsRegStatus;                       /* SIM卡CS域的注册结果导致的卡是否有效VOS_TRUE:CS域的卡有效,VOS_FALSE:CS域的卡无效*/
    VOS_UINT8                           ucRestrictRegister;                     /*是否限制注册 */

    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo         = VOS_NULL_PTR;
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus       = VOS_NULL_PTR;

    pstConnStatus         = NAS_MML_GetConnStatus();
    pstCampInfo           = NAS_MML_GetCurrCampPlmnInfo();
    ucEmergencyServiceFlg = NAS_MML_GetCsEmergencyServiceFlg();
    ucCsAttachAllowFlg    = NAS_MML_GetCsAttachAllowFlg();
    ucSimCsRegStatus      = NAS_MML_GetSimCsRegStatus();
    ucRestrictRegister    = NAS_MML_GetCsRestrictRegisterFlg();

    /* CS未注册下，紧急呼过程中收到attach cs请求先回复attach结果，紧急呼结束链接释放后，
       判断如果当前有PS业务，需要发起LAU */
    if ( (VOS_TRUE            == pstConnStatus->ucRrcStatusFlg)
      && (VOS_TRUE            == ucEmergencyServiceFlg)
      && (MM_STATUS_DETACHED  == g_MmSubLyrShare.MmShare.ucCsAttachState)
      && (VOS_TRUE            == ucCsAttachAllowFlg)
      && (VOS_TRUE            == ucSimCsRegStatus)
      && (VOS_FALSE           == ucRestrictRegister)
      && (MM_TIMER_RUNNING    != gstMmTimer[MM_TIMER_T3212].ucTimerStatus )
      && (MM_TIMER_RUNNING    != gstMmTimer[MM_TIMER_T3211].ucTimerStatus )
      && (NAS_MML_NET_MODE_II  == pstCampInfo->enNetworkMode)
      && ((MMCMM_NO_FORBIDDEN            == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
       || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)))
    {
        return VOS_TRUE;
    }


    return VOS_FALSE;

}


VOS_VOID NAS_MM_RelEstingMmConn(
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause
)
{
        NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause;

        enMmCcRelCause  = NAS_MM_ConvertRrcRelCauseToMmCcRelCause(ulRelCause);

    if ( NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI )
    {
        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                       enMmCcRelCause);            /* 通知CC,MM连接建立失败                    */


        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
            NO_MM_CONN_ESTING;                                          /* 清除正在建立的MM连接的标志               */
    }

    if ( NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI )
    {                                                                   /* 是SS正在建立的MM连接                     */
        Mm_SndSsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI,
                        enMmCcRelCause);


        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
            NO_MM_CONN_ESTING;                                          /* 清除正在建立的MM连接的标志               */
    }

    if ( NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI )
    {                                                                   /* 是SMS正在建立的MM连接                    */
        Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                        enMmCcRelCause);                                          /* 通知SS,MM连接建立失败                    */


        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
            NO_MM_CONN_ESTING;                                          /* 清除正在建立的MM连接的标志               */
    }

    return;

}


VOS_VOID NAS_MM_RelBufferedServiceEstReq(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause
)
{
    if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
    {                                                                           /* 有等待的CC触发的需要建立的MM连接         */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                RcvXXEstReq.ucFlg
            = MM_FALSE;

        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
             enMmCcRelCause);                          /* 通知CC建立失败                           */
    }
    if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                    RcvXXEstReq.ucFlg )
    {                                                                           /* 有等待的SMS触发的需要建立的MM连接         */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                RcvXXEstReq.ucFlg = MM_FALSE;
        Mm_SndSmsRelInd(
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
            .RcvXXEstReq.ulTransactionId,
            enMmCcRelCause);
    }
    if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                RcvXXEstReq.ucFlg )
    {                                                                           /* 有等待的SS触发的需要建立的MM连接         */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                RcvXXEstReq.ucFlg = MM_FALSE;

        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                       enMmCcRelCause);
    }

    return;

}



VOS_VOID NAS_MM_RelBufferedServiceEstReqExceptEmergencyCall(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause
)
{
    if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
     && (MMCC_MO_NORMAL_CALL == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType))
    {
        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
             enMmCcRelCause);
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
    {
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
            enMmCcRelCause);
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
    {
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                       enMmCcRelCause);
    }

    return;

}




VOS_UINT32 NAS_MM_NotifyBufferedServiceRRConnNotExist(VOS_VOID)
{
    VOS_UINT8                           ucTiValidFlg;

    if ( (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                  .RcvXXEstReq.ucFlg)
      || (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                  .RcvXXEstReq.ucFlg)
      || (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                  .RcvXXEstReq.ucFlg))
    {
        ucTiValidFlg = Mm_ComTiChk();
        if ( MM_FALSE == ucTiValidFlg )
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );         /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;

}




VOS_UINT32 NAS_MM_IsDisableGprsCombineAttach(VOS_VOID)
{

    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo       = VOS_NULL_PTR;
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo    = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    /* 获取当前网络模式 */
    pstCampInfo       = NAS_MML_GetCurrCampPlmnInfo();

    /* 获取当前的网络信息 */
    pstNetWorkInfo    =  NAS_MML_GetNetworkInfo();

    ulRet             = VOS_FALSE;

    /* CS域注册受限，MM不需要做LAU */
    if ( VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg() )
    {
        return VOS_FALSE;
    }


    /* 非网络模式I下，MM需要自己做LAU */
    if ( NAS_MML_NET_MODE_I != pstCampInfo->enNetworkMode )
    {
        return VOS_TRUE;
    }

    /* PS域不准许注册，MM需要自己做LAU */
    if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
    {
        return VOS_TRUE;
    }

    /* PS域注册首限，MM需要自己做LAU */
    if ( VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg() )
    {
        return VOS_TRUE;
    }

    /* PS 卡无效，不用GMM处理用户发起的detach */
    if ( VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_TRUE;
    }

    /* 当前小区是否支持GPRS */
    if ( VOS_FALSE == pstNetWorkInfo->stPsDomainInfo.ucPsSupportFlg )
    {
        return VOS_TRUE;
    }

    /* 当前小区是否在FORB GPRS PLMN里面 */
    ulRet = NAS_MML_IsSimPlmnIdInDestBcchPlmnList( &(pstCampInfo->stLai.stPlmnId),
                                           pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                           pstForbidPlmnInfo->astForbGprsPlmnList );
    if ( VOS_TRUE == ulRet )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_VOID NAS_MM_RestartT3240_WaitForNetworkCommand(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus       = VOS_NULL_PTR;
    VOS_UINT32                          ulIsTestCard;
    VOS_UINT8                           ucSupportCsServiceFlg;                  /* 是否支持cs语音业务包括普通语音和vp业务，VOS_TRUE:支持cs语音业务；VOS_FALSE:不支持cs语音业务*/
    VOS_UINT8                           ucCsServiceConnStatusFlg;

    pstConnStatus            = NAS_MML_GetConnStatus();
    ulIsTestCard             = NAS_USIMMAPI_IsTestCard();
    ucSupportCsServiceFlg    = NAS_MML_GetSupportCsServiceFLg();
    ucCsServiceConnStatusFlg = pstConnStatus->ucCsServiceConnStatusFlg;

    /* 停T3240 */
    Mm_TimerStop( MM_TIMER_T3240 );

    /* 当前测试卡，当前设置为不支持CS业务，当前有CS业务，则设置T3240最大值 */
    if ( (VOS_TRUE  == ulIsTestCard)
      && (VOS_FALSE == ucSupportCsServiceFlg)
      && (VOS_TRUE  == ucCsServiceConnStatusFlg) )
    {
        gstMmTimer[MM_TIMER_T3240].ulTimerLen = MM_TIMER_MAX_VALUE;
        Mm_TimerStart( MM_TIMER_T3240 );
        gstMmTimer[MM_TIMER_T3240].ulTimerLen = MM_TIMER_T3240_VALUE;
    }
    else
    {
        Mm_TimerStart( MM_TIMER_T3240 );                                        /* 启动T3240                                  */
    }

}

VOS_VOID NAS_MM_ResumeMmStateToPreState_LocationUpdatingPending(VOS_VOID)
{
    VOS_UINT8                           ucPreMmState;

    ucPreMmState  = g_MmGlobalInfo.ucPreState;

    /* CS卡无效的状态迁移 */
    if ( VOS_FALSE == NAS_MML_GetSimCsRegStatus() )
    {
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);

        return;
    }

    /* CS不准许注册的状态迁移 */
    if ( VOS_FALSE == NAS_MML_GetCsAttachAllowFlg() )
    {
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

        return;
    }

    /* 当前禁止注册的状态迁移 */
    if ( (MMCMM_NO_FORBIDDEN            != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
      && (MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg) )
    {
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

        return;
    }

    /* CS域受限的状态迁移 */
    if ( VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg() )
    {
        Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);

        return;
    }

    /* MM先前是MM_IDLE_NORMAL_SERVICE状态，则更新当前状态为MM_IDLE_NORMAL_SERVICE */
    if ( MM_IDLE_NORMAL_SERVICE == ucPreMmState )
    {
        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

        return;
    }

    /* MM先前是MM_IDLE_ATTEMPTING_TO_UPDATE状态，则更新当前状态为MM_IDLE_ATTEMPTING_TO_UPDATE */
    if ( MM_IDLE_ATTEMPTING_TO_UPDATE == ucPreMmState )
    {
        Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

        return;
    }

    /* 统一迁移到MM_IDLE_ATTEMPTING_TO_UPDATE状态 */
    Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

}




VOS_VOID NAS_MM_EndBufferedCSServiceExceptEmergencyCall_ImmediateAssignReject()
{
    /* 根据缓存业务的类型，获取相应的函数指针以及TransActionId */
    if ( (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
      && (MMCC_MO_NORMAL_CALL == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType) )
    {
        Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_IMMEDIATE_ASSIGN_REJECT);
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
    {
        Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_IMMEDIATE_ASSIGN_REJECT);
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
    {
        Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_IMMEDIATE_ASSIGN_REJECT);
    }

    /* 通知MMC，CS域的业务已经停止 */
    Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

    return;
}


VOS_UINT32  NAS_MM_ProcessLuAfterCsConnectNotExist_NetModeI( VOS_VOID )
{
    VOS_UINT8                           ucRet;

    ucRet = MM_FALSE;

    if ( MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac )
    {                                                               /* RAC为0的场合                             */
        g_MmGlobalInfo.ucLikeB = MM_TRUE;                           /* 设置类似于B模式的全局量                  */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComChkLu:INFO: MmLikeB is MM_TRUE");
        if ( ( MMCMM_NO_FORBIDDEN !=
            g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg ) &&
            ( MMCMM_FORBIDDEN_PLMN_FOR_GPRS !=
            g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg ) )
        {
            if ( MMCMM_FORBIDDEN_PLMN
                == (MMCMM_FORBIDDEN_PLMN &
                g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
                )
            {
                g_MmGlobalInfo.ucMmServiceState =
                    MM_LIMITED_SERVICE;                             /* 设置服务状态                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_CheckLuAfterCsConnectNotExist:INFO: MmServiceState is MM_LIMITED_SERVICE");
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN);
                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_CheckLuAfterCsConnectNotExist:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            }
            else if ( MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS
                == (MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS
                    & g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
                )
            {
                g_MmGlobalInfo.ucMmServiceState =
                    MM_LIMITED_SERVICE;                             /* 设置服务状态                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_CheckLuAfterCsConnectNotExist:INFO: MmServiceState is MM_LIMITED_SERVICE");

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW);

                 Mm_ComLuCauseHandle(NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW);
            }
            else
            {
                g_MmGlobalInfo.ucMmServiceState =
                    MM_LIMITED_SERVICE;                             /* 设置服务状态                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_CheckLuAfterCsConnectNotExist:INFO: MmServiceState is MM_LIMITED_SERVICE");

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW);

                Mm_ComLuCauseHandle(NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW);
            }
        }
        else
        {
           g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;    /* 设置LU类型                               */
           Mm_ComLuOnly();                                          /* LU REQ                                   */
           ucRet = MM_TRUE;
        }
    }

    return ucRet;
}


VOS_UINT32  NAS_MM_ProcessLuAfterCsConnectNotExist_OhterNetMode( VOS_VOID )
{                                                                   /* 非A+I模式                                */
    VOS_UINT8                           ucRet;

    ucRet = MM_FALSE;

    if ( ( MMCMM_NO_FORBIDDEN !=
        g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg ) &&
        ( MMCMM_FORBIDDEN_PLMN_FOR_GPRS !=
        g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg ) )
    {                                                               /* 如果没有CS域禁止的信息                   */
        if ( MMCMM_FORBIDDEN_PLMN == ( MMCMM_FORBIDDEN_PLMN &
            g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg) )
        {
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;   /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_CheckLuAfterCsConnectNotExist:INFO: MmServiceState is MM_LIMITED_SERVICE");
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN);
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_CheckLuAfterCsConnectNotExist:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        }
        else if ( MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS
            == ( MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS
                & g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg ) )
        {
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;   /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_CheckLuAfterCsConnectNotExist:INFO: MmServiceState is MM_LIMITED_SERVICE");

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW);

            Mm_ComLuCauseHandle(NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW);
        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;   /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_CheckLuAfterCsConnectNotExist:INFO: MmServiceState is MM_LIMITED_SERVICE");

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW);

            Mm_ComLuCauseHandle(NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW);
        }
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
        Mm_ComLuOnly();                                             /* 发送LU REQ                               */
        ucRet = MM_TRUE;
    }

    return ucRet;
}


VOS_UINT32  NAS_MM_ProcessLuAfterCsConnectNotExist_T3212Expire(
    VOS_UINT8                           ucPsRestrictionFlg
)
{
    VOS_UINT8                           ucRet;

    ucRet = MM_FALSE;

    switch ( g_MmGlobalInfo.ucState )
    {
    case MM_IDLE_NORMAL_SERVICE:
        ucRet = MM_TRUE;

        if((VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
            && (VOS_TRUE == ucPsRestrictionFlg))
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;               /* 设置LU类型                               */
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;       /* 设置LU类型                               */
        }

        Mm_ComLuOnly();                                                     /* 发送LU REQ                               */
        break;
    case MM_IDLE_ATTEMPTING_TO_UPDATE:
        ucRet = MM_TRUE;
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;               /* 设置LU类型                               */
        Mm_ComLuOnly();                                                     /* 发送LU REQ                               */
        break;
    default:
        break;
    }

    return ucRet;
}


VOS_UINT32  NAS_MM_ProcessLuAfterCsConnectNotExist_RrcExist( VOS_VOID )
{
    VOS_UINT8                           ucRet;
    VOS_UINT8                           ucFlg;

    ucRet = MM_FALSE;
    ucFlg = MM_FALSE;

    g_MmGlobalInfo.ucConnRcvSysFlg = MM_FALSE;

    g_MmGlobalInfo.ucLauAcceptContainDiffNbLaiFlg = VOS_FALSE;

    switch ( g_MmGlobalInfo.ucState )
    {
    case MM_IDLE_NORMAL_SERVICE:
    case MM_IDLE_ATTEMPTING_TO_UPDATE:
    case MM_IDLE_LIMITED_SERVICE:
    case WAIT_FOR_RR_CONNECTION_MM_CONNECTION:
        ucFlg = MM_TRUE;
        break;
    default:
        break;
    }
    if ( MM_TRUE == ucFlg )
    {
        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
        {                                                                   /* 如果为A+I,且不是类似B或A+II处理的场合    */
            ucRet = (VOS_UINT8)NAS_MM_ProcessLuAfterCsConnectNotExist_NetModeI();
        }
        else
        {
            ucRet = (VOS_UINT8)NAS_MM_ProcessLuAfterCsConnectNotExist_OhterNetMode();
        }
    }

    return ucRet;
}




VOS_UINT8 NAS_MM_ProcessLuAfterCsConnectNotExist(VOS_VOID)
{
    VOS_UINT8                           ucRet;
    VOS_UINT8                           ucFlg;
    VOS_UINT8                           ucPsRestrictionFlg;

    ucRet = MM_FALSE;
    ucFlg = MM_FALSE;
    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();


    if ( g_MmGlobalInfo.ucNtMod != g_MmGlobalInfo.ucNewNtMod )
    {
        if ( ( MMCMM_FORBIDDEN_PLMN == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg )
          || ( MMCMM_FORBIDDEN_LA_FOR_ROAM == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg )
          || ( MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg ))
        {
            return ucRet;
        }

        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;
        switch ( g_MmGlobalInfo.ucState )
        {
        case MM_IDLE_NORMAL_SERVICE:
        case MM_IDLE_ATTEMPTING_TO_UPDATE:
        case MM_IDLE_LIMITED_SERVICE:
            ucFlg = MM_TRUE;
            break;
        default:
            break;
        }
        if  ( MM_NET_MODE_II == g_MmGlobalInfo.ucNtMod )
        {
            if (MM_TRUE == ucFlg)
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* 设置LU类型                               */
                Mm_ComLuOnly();                                                 /* LU REQ                                   */
                ucRet = MM_TRUE;
                return ucRet;
            }
        }
    }

    if (VOS_TRUE == NAS_MM_IsNeedLauCsSigRel())
    {
        ucRet = (VOS_UINT8)NAS_MM_ProcessLuAfterCsConnectNotExist_RrcExist();
    }
    else if ( MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
    {
        ucRet = (VOS_UINT8)NAS_MM_ProcessLuAfterCsConnectNotExist_T3212Expire(ucPsRestrictionFlg);
    }
    else
    {

    }

    return ucRet;
}


VOS_VOID  NAS_MM_LogAuthInfo(
    VOS_UINT8                           ucRcvOpId,
    VOS_UINT8                           ucExpectOpId
)
{
    NAS_MM_LOG_AUTH_INFO_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_MM_LOG_AUTH_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MM,
                                         sizeof(NAS_MM_LOG_AUTH_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_LogAuthInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(NAS_MM_LOG_AUTH_INFO_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MM_LOG_AUTH_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = MMOM_LOG_AUTH_INFO_IND;
    pstMsg->ucExpectOpId                = ucExpectOpId;
    pstMsg->ucRcvOpId                   = ucRcvOpId;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MM, pstMsg);

    return;
}



VOS_VOID  NAS_MM_LogMmCtxInfo(VOS_VOID)
{
    MMOM_LOG_CTX_INFO_STRU             *pstMsg = VOS_NULL_PTR;

    pstMsg = (MMOM_LOG_CTX_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MM,
                                         sizeof(MMOM_LOG_CTX_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_LogMmCtxInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(MMOM_LOG_CTX_INFO_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(MMOM_LOG_CTX_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = MMOM_LOG_CTX_INFO_IND;

    pstMsg->stMmGlobalInfo.ConnCtrlInfo_CC_RcvXXEstReq_ucFlg  = g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg;
    pstMsg->stMmGlobalInfo.ConnCtrlInfo_SMS_RcvXXEstReq_ucFlg = g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg;
    pstMsg->stMmGlobalInfo.ConnCtrlInfo_SS_RcvXXEstReq_ucFlg  = g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg;
    pstMsg->stMmGlobalInfo.enPreRatType                       = g_MmGlobalInfo.enPreRatType;
    pstMsg->stMmGlobalInfo.LuInfo_ucT3212ExpiredFlg           = g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg;
    pstMsg->stMmGlobalInfo.MsCsInfo_ucOldRac                  = g_MmGlobalInfo.MsCsInfo.ucOldRac;
    pstMsg->stMmGlobalInfo.stDetachInfo_enDetachType          = g_MmGlobalInfo.stDetachInfo.enDetachType;
    pstMsg->stMmGlobalInfo.ucAttFlg                           = g_MmGlobalInfo.ucAttFlg;
    pstMsg->stMmGlobalInfo.ucLikeB                            = g_MmGlobalInfo.ucLikeB;
    pstMsg->stMmGlobalInfo.ucMmServiceState                   = g_MmGlobalInfo.ucMmServiceState;
    pstMsg->stMmGlobalInfo.ucNotCampONPreState                = g_MmGlobalInfo.ucNotCampONPreState;
    pstMsg->stMmGlobalInfo.ucNtMod                            = g_MmGlobalInfo.ucNtMod;
    pstMsg->stMmGlobalInfo.ucPowerOnFlg                       = g_MmGlobalInfo.ucPowerOnFlg;
    pstMsg->stMmGlobalInfo.ucPreState                         = g_MmGlobalInfo.ucPreState;
    pstMsg->stMmGlobalInfo.usRac                              = g_MmGlobalInfo.usRac;

#if (FEATURE_ON == FEATURE_ECALL)
    pstMsg->stMmlCtxInfo.enCallMode                           = NAS_MML_GetCallMode();
#else
    pstMsg->stMmlCtxInfo.enCallMode                           = NAS_MML_CALL_MODE_BUTT;
#endif
    pstMsg->stMmlCtxInfo.enCsfbServiceStatus                  = NAS_MML_GetCsfbServiceStatus();
    pstMsg->stMmlCtxInfo.enCsUpdateStatus                     = NAS_MML_GetCsUpdateStatus();
    pstMsg->stMmlCtxInfo.enT3423Status                        = NAS_MML_GetT3423Status();
    PS_MEM_CPY(&pstMsg->stMmlCtxInfo.stAttemptUpdateLaiInfo, NAS_MM_GetAttemptUpdateLaiInfo(), sizeof(pstMsg->stMmlCtxInfo.stAttemptUpdateLaiInfo));
    PS_MEM_CPY(&pstMsg->stMmlCtxInfo.stCsLastSuccLai, NAS_MML_GetCsLastSuccLai(), sizeof(pstMsg->stMmlCtxInfo.stCsLastSuccLai));
    PS_MEM_CPY(&pstMsg->stMmlCtxInfo.stCurrCampLai, NAS_MML_GetCurrCampLai(), sizeof(pstMsg->stMmlCtxInfo.stCurrCampLai));
    pstMsg->stMmlCtxInfo.ucCsSecurityCksn                     = NAS_MML_GetSimCsSecurityCksn();
    pstMsg->stMmlCtxInfo.ucImsVoiceAvailFlg                   = NAS_MML_GetImsVoiceAvailFlg();
    pstMsg->stMmlCtxInfo.ucImsVoiceInterSysLauEnableFlg       = NAS_MML_GetImsVoiceInterSysLauEnableFlg();
    pstMsg->stMmlCtxInfo.ucStaOfRcvXXEstReqCsfb               = NAS_MM_GetStaOfRcvXXEstReq_CSFB();

    pstMsg->stMmTimerInfo.ucT3211TimerStatus                  = gstMmTimer[MM_TIMER_T3211].ucTimerStatus;
    pstMsg->stMmTimerInfo.ucT3212TimerStatus                  = gstMmTimer[MM_TIMER_T3212].ucTimerStatus;
    pstMsg->stMmTimerInfo.ucT3213TimerStatus                  = gstMmTimer[MM_TIMER_T3213].ucTimerStatus;
    pstMsg->stMmTimerInfo.ucT3242TimerStatus                  = gstMmTimer[MM_TIMER_T3242].ucTimerStatus;
    pstMsg->stMmTimerInfo.ucT3243TimerStatus                  = gstMmTimer[MM_TIMER_T3243].ucTimerStatus;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MM, pstMsg);

    return;
}

RRC_NAS_EST_RESULT_ENUM_UINT32 NAS_MM_GetEstCnfResult(VOS_VOID)
{
    return g_MmGlobalInfo.enEstCnfResult;
}


VOS_VOID NAS_MM_SetEstCnfResult(RRC_NAS_EST_RESULT_ENUM_UINT32 enEstCnfResult)
{
    g_MmGlobalInfo.enEstCnfResult = enEstCnfResult;
}



VOS_UINT32 NAS_MM_GetTransactionEnqSenderPid(VOS_VOID)
{
    return g_MmGlobalInfo.ulTransactionEnqSenderPid;
}


VOS_VOID NAS_MM_SetTransactionEnqSenderPid(
    VOS_UINT32                          ulSenderPid
)
{
    g_MmGlobalInfo.ulTransactionEnqSenderPid = ulSenderPid;

    return;
}



VOS_UINT32 NAS_MM_IsNeedProcBufferedCsDetach_RcvLauEstCnf(
    RRC_NAS_EST_RESULT_ENUM_UINT32      enEstCnfResult
)
{
    /* 24008_CR1201R1_(Rel-8)_C1-082683 24008 4.3.4章节描述:If a RR connection
        exists and the ATT flag indicates that no detach procedure is required,
        the MM sublayer will release locally any ongoing MM connections before
        releasing the RR connection. If a MM specific procedure is active,
        the release of the RR connection may be delayed until the MM specific
        procedure is complete. lau结束后连接释放时再做本地detach,如果lau建链失败则做本地detach */
    if (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH))
    {
        if ((RRC_EST_SUCCESS != enEstCnfResult)
         && (RRC_EST_PRESENT !=enEstCnfResult))
        {
            return VOS_TRUE;
        }

        if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
        {
            return VOS_FALSE;
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_VOID  NAS_MM_ClearAuthInfo(VOS_VOID)
{
    g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt = 0;
    g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause   = MM_AUTHEN_NO_CAUSE;

    g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat      = MM_AUTHEN_RAND_DIFFER;

    /* 24.008 4.3.2.2
    The RAND and RES values stored in the mobile station shall be deleted and timer T3218, if running, shall be stopped:
    -   if the mobile station enters the MM state MM IDLE or NULL.
    */
    Mm_TimerStop(MM_TIMER_T3218);

    Mm_ComDelRandRes();

    if (MM_RCV_AUTH_CNF_FLG == (MM_RCV_AUTH_CNF_FLG & g_MmGlobalInfo.ucRcvAgentFlg))
    {
        g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

        Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
    }

    if ((VOS_TRUE == NAS_MML_GetNwIgnoreAuthFailCfg())
     && (MM_TIMER_RUNNING == gstMmTimer[MM_TIMER_T3216].ucTimerStatus))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_ClearAuthInfo: Clear CKSN and Stop T3216");
        NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);
        Mm_TimerStop(MM_TIMER_T3216);
    }

    return;
}



VOS_VOID NAS_MM_RcvProtectingMtCsfbPagingProcedureExpired(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulRcvPid;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;

    ulRet            = VOS_ERR;
    enCurrNetRatType = NAS_MML_GetCurrNetRatType();

    NAS_MM_SetCsfbMtLauFlg(VOS_FALSE);

    NAS_MML_SetCsfbMtPagingTimerStatus(NAS_MML_MT_CSFB_PAGING_TIMER_STOP);


    if (MM_INTER_RAT_CHANGE == Mm_GetState())
    {
        if ( (NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST == NAS_MML_GetCsfbServiceStatus())
          && (NAS_MML_NET_RAT_TYPE_LTE             == enCurrNetRatType) )
        {
            NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            /* 通知L CSFB 流程终止 */
            NAS_MM_SndLmmCsfbServiceAbortNotify();
        }
    }

    /* 通知接入层TRANSACTION状态 */
    ulRet = NAS_MM_GetRrcPidFromCurrRatType(&ulRcvPid);
    if (VOS_OK == ulRet)
    {
        NAS_MM_SndRrcTransactionStatusNotify(ulRcvPid, RRMM_TRANSACTION_FAIL);
    }

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_CSFB_MT_PROTECT_TI_TIME_OUT,
                              NAS_MML_REG_FAIL_CAUSE_NULL);

#if (FEATURE_ON == FEATURE_PTM)
    /* 如果CS信令链接不存在，则记录CSFB MT异常 */
    if (VOS_FALSE == NAS_MML_GetCsSigConnStatusFlg())
    {
        NAS_MM_CsfbMtFailRecord();
    }
#endif

    /* 如果MMC正在搜网时业务结束，通知MMC停止搜GU，重新从LTE开始搜网;如果MMC处于ON PLMN启高优先级接入技术BG搜定时器 */
    NAS_MM_SndMmcPlmnSearchInd(MM_MMC_PLMN_SEARCH_TYPE_CSFB_END);

    return;
}



#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_MM_RcvMmTimerGetHoSecuInfoCnfExpired(VOS_VOID)
{
    if ((NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
     && (MM_INTER_RAT_CHANGE      == g_MmGlobalInfo.ucState))
    {
        /* 向MMC回复挂起rsp */
        NAS_MM_SndMmcSuspendRsp();
    }

    return;
}


VOS_UINT8 NAS_MM_GetSrvccFlg(VOS_VOID)
{
    return g_MmGlobalInfo.ucSrvccFlg;
}


VOS_VOID NAS_MM_SetSrvccFlg(
    VOS_UINT8                           ucFlg
)
{
    g_MmGlobalInfo.ucSrvccFlg = ucFlg;
}



VOS_UINT8 NAS_MM_GetRcvSrvccCallInfoFlg(VOS_VOID)
{
    return g_MmGlobalInfo.ucRcvSrvccCallInfoFlg;
}


VOS_VOID NAS_MM_SetRcvSrvccCallInfoFlg(
    VOS_UINT8                           ucFlg
)
{
    g_MmGlobalInfo.ucRcvSrvccCallInfoFlg = ucFlg;
}


VOS_VOID NAS_MM_ConvertToLmmSrvccStatus(
    NAS_MMCC_SRVCC_STATUS_ENUM_UINT32   enSrvccStatus,
    MM_LMM_SRVCC_STATUS_ENUM_UINT32    *penMmlSrvccStatus
)
{
    switch(enSrvccStatus)
    {
        case NAS_MMCC_SRVCC_STATUS_START:
            *penMmlSrvccStatus = MM_LMM_SRVCC_STATUS_START;
            break;
        case NAS_MMCC_SRVCC_STATUS_SUCCESS:
            *penMmlSrvccStatus = MM_LMM_SRVCC_STATUS_SUCC;
            break;
        case NAS_MMCC_SRVCC_STATUS_FAIL:
            *penMmlSrvccStatus = MM_LMM_SRVCC_STATUS_FAIL;
            break;
        default:
            *penMmlSrvccStatus = MM_LMM_SRVCC_STATUS_BUTT;
            break;
    }

    return;
}



VOS_UINT8 NAS_MM_IsNeedSetCsmtFlg(VOS_VOID)
{
    VOS_UINT8                           ucCsfbMtFlg;

    ucCsfbMtFlg = NAS_MM_GetCsfbMtLauFlg();

    /* 存在CSMT标志，则需要携带CSMT标志 */
    if ( (NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST == NAS_MML_GetCsfbServiceStatus())
      || (VOS_TRUE                             == ucCsfbMtFlg) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT8 NAS_MM_IsNeedSetCsmoFlg(VOS_VOID)
{
    VOS_UINT8                           ucCsmoSupportedFlg;
    VOS_UINT8                           ucCellNotSupportCsmoFlg;
    VOS_UINT8                           ucCsfbMoSetupFlg;

    ucCsmoSupportedFlg      = NAS_MML_GetCsmoSupportedFlg();
    ucCellNotSupportCsmoFlg = NAS_MML_GetCellNotSupportCsmoFlg();
    ucCsfbMoSetupFlg        = NAS_MML_GetCsfbMoSetupFlg();

    NAS_NORMAL_LOG3(WUEPS_PID_MM,
        "NAS_MM_IsNeedSetCsmoFlg: ucCsmoSupportedFlg, ucCellNotSupportCsmoFlg, ucCsfbMoSetupFlg",
        ucCsmoSupportedFlg, ucCellNotSupportCsmoFlg, ucCsfbMoSetupFlg);

    /* 当前配置支持CSMO，且当前存在CSMO业务 */
    if ((VOS_TRUE == ucCsmoSupportedFlg)
     && (VOS_FALSE == ucCellNotSupportCsmoFlg)
     && (VOS_TRUE == ucCsfbMoSetupFlg))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MM, "NAS_MM_IsNeedSetCsmoFlg: Need to set CSMO");
        return VOS_TRUE;
    }

    /* 否则不携带CSMO 标志 */
    return VOS_FALSE;
}



VOS_VOID NAS_MM_SetCsfbAdditionalUpdateParameters(
    VOS_UINT8                           ucCsmtFlg,
    VOS_UINT8                           ucCsmoFlg,
    VOS_UINT16                         *pusMsgSize,
    VOS_UINT8                          *pucSndMsg
)
{
    VOS_UINT16                          usIdx;

    usIdx       = *pusMsgSize;

    /* 同时携带CSMT/CSMO标志 */
    if ( (VOS_TRUE == ucCsmtFlg)
      && (VOS_TRUE == ucCsmoFlg) )
    {
        /* 设置CS fallback mobile terminating call */
        pucSndMsg[usIdx]    = MM_IE_CSFB_CSMT_FLAG_EXIST;

        /* 设置CS fallback mobile originating call */
        pucSndMsg[usIdx]    |= MM_IE_CSFB_CSMO_FLAG_EXIST;

        /* 设置ADDITIONAL UPDATE PARAMETERS IEI */
        pucSndMsg[usIdx]    |= MM_IEI_ADDITIONAL_UPDATE_PARAMETERS;

        /* 消息长度增加 */
        (*pusMsgSize) ++;

        return;
    }

    /* 携带CSMT标志 */
    if (VOS_TRUE == ucCsmtFlg)
    {
        /* 设置CS fallback mobile terminating call */
        pucSndMsg[usIdx]    = MM_IE_CSFB_CSMT_FLAG_EXIST;

        /* 设置ADDITIONAL UPDATE PARAMETERS IEI */
        pucSndMsg[usIdx]    |= MM_IEI_ADDITIONAL_UPDATE_PARAMETERS;

        /* 消息长度增加 */
        (*pusMsgSize) ++;

        return;
    }

    /* 携带CSMO标志 */
    if (VOS_TRUE == ucCsmoFlg)
    {
        /* 设置CS fallback mobile originating call */
        pucSndMsg[usIdx]    = MM_IE_CSFB_CSMO_FLAG_EXIST;

        /* 设置ADDITIONAL UPDATE PARAMETERS IEI */
        pucSndMsg[usIdx]    |= MM_IEI_ADDITIONAL_UPDATE_PARAMETERS;

        /* 消息长度增加 */
        (*pusMsgSize) ++;

        return;
    }

    /* 不需要携带CSMT/CSMO标志 */
    return;
}



#endif


VOS_UINT32 NAS_MM_IsNeedSetMsNetworkFeatureSupportIELauReq(VOS_VOID)
{
    VOS_UINT8                          ucIsNeedSetCsmoFlg;
    VOS_UINT8                          ucIsNeedSetCsmtFlg;

    ucIsNeedSetCsmoFlg = NAS_MM_IsNeedSetCsmoFlg();
    ucIsNeedSetCsmtFlg = NAS_MM_IsNeedSetCsmtFlg();


    /* 24008_CR1821R6_(Rel-10)_C1-113736-was-3626-24008-a30 9.2.15章节描述如下:
    9.2.15.6    MS network feature support
    This IE shall be included if the MS supports extended periodic timer T3212 and
    the Additional update parameters IE is not included. */
    if ((PS_PTL_VER_R11 <= NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_CS))
     && (VOS_FALSE == ucIsNeedSetCsmoFlg)
     && (VOS_FALSE == ucIsNeedSetCsmtFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_VOID NAS_MM_SetMsNetworkFeatureSupportIE(
    VOS_UINT16                         *pusMsgSize,
    VOS_UINT8                          *pucSndMsg
)
{
    VOS_UINT16                          usIdx;

    usIdx  = *pusMsgSize;

    /* 24008_CR1821R6_(Rel-10)_C1-113736-was-3626-24008-a30 9.2.15章节描述如下:
    9.2.15.6    MS network feature support
    This IE shall be included if the MS supports extended periodic timer T3212 and
    the Additional update parameters IE is not included. */
    pucSndMsg[usIdx]    = MM_IE_MS_SUPPORT_EXTEND_PERIODIC_TIMER_IN_THIS_DOMAIN;

    /* 设置MS NETWORK FEATURE SUPPORT IEI */
    pucSndMsg[usIdx]    |= MM_IEI_MS_NETWORK_FEATURE_SUPPORT;

    /* 消息长度增加 */
    (*pusMsgSize) ++;

    return;
}



VOS_UINT8 NAS_MM_GetCsfbMtLauFlg(VOS_VOID)
{
    return g_MmGlobalInfo.LuInfo.ucCsfbMtLauFlg;
}


VOS_VOID NAS_MM_SetCsfbMtLauFlg(
    VOS_UINT8                           ucFlg
)
{
    g_MmGlobalInfo.LuInfo.ucCsfbMtLauFlg = ucFlg;
}








VOS_UINT32 Mm_IsMultiSrvCollisionAllow(NAS_MM_CONN_CTRL_ENUM_UINT8  ucMmConnCtrl)
{
    if ((WAIT_FOR_RR_CONNECTION_MM_CONNECTION == g_MmGlobalInfo.ucState)
     || (WAIT_FOR_OUTGOING_MM_CONNECTION      == g_MmGlobalInfo.ucState)
     || (WAIT_FOR_NETWORK_COMMAND             == g_MmGlobalInfo.ucState))
    {
        /* 当前有一个被叫业务正在进行 */
        if (MM_MT_PAGING == g_MmGlobalInfo.ucPagingType)
        {
            if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            {
                /* 当前网络如果为GSM，拒绝当前的MO呼叫业务请求，原因: GSM业务请求在业务链接建立阶段，
                 * 无法知道当前的业务类型
                 */
                if (MM_CONN_CTRL_CC == ucMmConnCtrl)
                {
                    return VOS_FALSE;
                }

                return VOS_TRUE;
            }
            else
            {
                if ((MM_CONN_CTRL_CC                                 == ucMmConnCtrl)
                 && (RRC_PAGE_CAUSE_TERMINAT_CONVERSAT_CALL          == g_MmGlobalInfo.ucPagingCause))
                {
                    /* 如果当前MO业务请求为呼叫业务且MT业务请求也是呼叫，拒绝当前的MO业务 */
                    return VOS_FALSE;
                }
                else
                {
                    /* 其他场景,允许当前业务发起 */
                    return VOS_TRUE;
                }
            }
        }

        /* 下面是为了规避多个MO业务请求同时到来时的处理流程
         *
         * 注: 未来高版本，可以考虑根据T3246定时器方式来处理(Ref: section 4.5.1.1/4.5.1.2
         *     in 24.008 version 10.6.1)
         */
        if (WAIT_FOR_NETWORK_COMMAND != g_MmGlobalInfo.ucState)
        {
            if ((MM_IE_PD_NON_CALL_RLT_SS_MSG == g_MmGlobalInfo.ucMMConnEstingPD)
             && (MM_CONN_CTRL_CC              == ucMmConnCtrl))
            {
                /* 当前一个MO SS业务请求正在建立，如果收到呼叫业务请求，拒绝当前呼叫业务请求 */
                return VOS_FALSE;
            }
            else if ((MM_IE_PD_CALL_CONTROL   == g_MmGlobalInfo.ucMMConnEstingPD)
                  && (MM_CONN_CTRL_SS         == ucMmConnCtrl))
            {
                /* 当前一个MO 呼叫业务请求正在建立，如果收到补充业务请求，拒绝当前补充业务请求 */
                return VOS_FALSE;
            }
            else
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_TRUE;
}




VOS_VOID NAS_MM_ProcMmcMmSysInfoInd_CsAttachNotAllow( VOS_VOID )
{
    g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

    if ((VOS_TRUE           == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I      == g_MmGlobalInfo.ucNtMod)
     && (MM_UNSUPPORT_GPRS  == g_MmGlobalInfo.usRac))
    {
        g_MmGlobalInfo.ucLikeB = MM_TRUE;
    }

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_GU_SYS_INFO_RECEIVED,
                              NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             NAS_MML_REG_FAIL_CAUSE_NULL);


    Mm_DealWithBuffMsg();

    return;
}



VOS_UINT32 NAS_MM_IsCsForbidden( VOS_VOID )
{
    if ((MMCMM_NO_FORBIDDEN            == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
     || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT8 NAS_MM_IsCsNotSupport(
    VOS_VOID                           *pRcvMsg
)
{
    MMCMM_SYS_INFO_IND_STRU            *pstWSysInfoInd = VOS_NULL_PTR;                    /* 定义接收到的消息类型指针                 */

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        pstWSysInfoInd = (MMCMM_SYS_INFO_IND_STRU *)pRcvMsg;                                                      /* 消息转换                                */

        if ((0 == pstWSysInfoInd->ucCsInfoSize)
         && (MMC_MM_SYS_INFO_TYPE_SYS == pstWSysInfoInd->enSysInfoType))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_VOID NAS_MM_ProcMmcMmSysInfoInd_CsRegisterRestrict( VOS_VOID )
{
    Mm_TimerStop(MM_TIMER_T3210);
    Mm_TimerStop(MM_TIMER_T3211);

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_GU_SYS_INFO_RECEIVED,
                              NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);

    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);

    Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);

    NAS_MM_RcvSysInfoAccessBar_ProcBufferedCsService();

    return;
}


VOS_VOID NAS_MM_ConvertMmlLaiFormatToMMFormat(
    NAS_MML_LAI_STRU                   *pstSrcLai,
    MM_LAI_STRU                        *pstDstLai
)
{
    pstDstLai->PlmnId.ulMcc = pstSrcLai->stPlmnId.ulMcc;
    pstDstLai->PlmnId.ulMnc = pstSrcLai->stPlmnId.ulMnc;

    pstDstLai->ulLac        = (pstSrcLai->aucLac[0]<< 8) & 0xFF00;
    pstDstLai->ulLac        |= pstSrcLai->aucLac[1];

    return;
}



VOS_UINT8 NAS_MM_CheckMmcMmSysInfoIE(
    VOS_VOID                           *pRcvMsg
)
{
    MMCMM_SYS_INFO_IND_STRU            *pstWSysInfoInd = VOS_NULL_PTR;
    MMCMM_GSM_SYS_INFO_IND_ST          *pstGSysInfoInd = VOS_NULL_PTR;

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        pstGSysInfoInd = (MMCMM_GSM_SYS_INFO_IND_ST *)pRcvMsg;

        /* 判断是否为 GSM 的系统信息指示消息 */
        if (MMCMM_GSM_SYS_INFO_IND != pstGSysInfoInd->MsgHeader.ulMsgName)
        {
            return VOS_FALSE;
        }

        return VOS_TRUE;
    }

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        pstWSysInfoInd = (MMCMM_SYS_INFO_IND_STRU *)pRcvMsg;

        /* 判断是否为 WCDMA 的系统信息指示消息 */
        if (MMCMM_SYS_INFO_IND != pstWSysInfoInd->MsgHeader.ulMsgName)
        {
            return VOS_FALSE;
        }

        if ((MM_CONST_NUM_8 < pstWSysInfoInd->ucCnCommonSize)
         || (MM_CONST_NUM_8 < pstWSysInfoInd->ucCsInfoSize))
        {                                                                           /* 消息中的取值不合法                       */
            return VOS_FALSE;                                                       /* 返回消息检查失败                         */
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_VOID NAS_MM_UpdateT3212Value_RcvLauAccept(
    VOS_UINT8                            ucMsgTimerValue
)
{
    VOS_UINT8                            ucTimerUnit;                                                   /* 定义临时变量存储时长单位                 */
    VOS_UINT8                            ucTimerValue;                                                   /* 定义临时变量存储时长                     */

    ucTimerUnit     = 0;
    ucTimerValue    = 0;
    ucTimerUnit     = (VOS_UINT8)(ucMsgTimerValue >> NAS_MML_OCTET_MOVE_FIVE_BITS);
    ucTimerValue    = (VOS_UINT8)(ucMsgTimerValue & NAS_MML_OCTET_LOW_FIVE_BITS);

    /* 24008 10.5.163a章节描述如下:
    GPRS Timer 3 value (octet 3)
    Bits 5 to 1 represent the binary coded timer value.
    Bits 6 to 8 defines the timer value unit for the GPRS timer as follows:
    Bits
    8 7 6
    0 0 0 value is incremented in multiples of 10 minutes
    0 0 1 value is incremented in multiples of 1 hour
    0 1 0 value is incremented in multiples of 10 hours
    0 1 1 value is incremented in multiples of 2 seconds
    1 0 0 value is incremented in multiples of 30 seconds
    1 0 1 value is incremented in multiples of 1 minute
    1 1 1 value indicates that the timer is deactivated.

    Other values shall be interpreted as multiples of 1 hour in this version of the protocol.
    */
    switch (ucTimerUnit)
    {
        case 0:
            /* 10分钟 */
            NAS_MM_SetNetworkAllocT3212Len(ucTimerValue * 10 * 60 * 1000);
            break;

        case 1:
            /* 1小时 */
            NAS_MM_SetNetworkAllocT3212Len(ucTimerValue * 60 * 60 * 1000);
            break;

        case 2:
            /* 10小时 */
            NAS_MM_SetNetworkAllocT3212Len(ucTimerValue * 10 * 60 * 60 * 1000);
            break;

        case 3:
            /* 2秒 */
            NAS_MM_SetNetworkAllocT3212Len(ucTimerValue * 2 * 1000);
            break;

        case 4:
            /* 30秒 */
            NAS_MM_SetNetworkAllocT3212Len(ucTimerValue * 30 * 1000);
            break;

        case 5:
            /* 1分钟 */
            NAS_MM_SetNetworkAllocT3212Len(ucTimerValue * 60 * 1000);
            break;

        case 7:
            /* timer is deactivated */
            NAS_MM_SetNetworkAllocT3212Len(0);
            break;

        default:
            /* 1小时 */
            NAS_MM_SetNetworkAllocT3212Len(ucTimerValue * 60 * 60 * 1000);
            break;
    }

    return;
}


VOS_UINT32 NAS_MM_IsNeedUpdateT3212Value_RcvGuSysInfo(VOS_VOID)
{
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo  = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstAllocT3212ValueLaiInfo = VOS_NULL_PTR;

    pstAllocT3212ValueLaiInfo  = NAS_MM_GetAllocT3212ValueLaiInfo();
    pstNetWorkInfo             = NAS_MML_GetNetworkInfo();

    /* 如果协议版本小于R11,返回需要根据系统消息更新T3212定时器时长 */
    if (PS_PTL_VER_R11 > NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_CS))
    {
        return VOS_TRUE;
    }

    /* 如果之前下发T3212定时器时长的网络接入技术与当前驻留网络的接入技术不同，返回需要更新T3212时长 */
    if (pstAllocT3212ValueLaiInfo->enCampPlmnNetRat != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* 如果之前下发T3212定时器时长的网络与当前驻留的网络lai不同，则返回需要更新T3212时长 */
    if (VOS_FALSE == NAS_MML_CompareLai(&pstNetWorkInfo->stCampPlmnInfo.stLai, pstAllocT3212ValueLaiInfo))
    {
        return VOS_TRUE;
    }

    /* 之前下发T3212时长的网络lai与当前驻留网络lai相同，且之前网络不是通过lau accept下发的，则返回需要更新T3212时长 */
    if (NAS_MM_T3212_VALUE_TYPE_NONE_BROADCAST != NAS_MM_GetNetworkT3212ValueType())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_VOID NAS_MM_UpdateT3212Value_RcvGuSysInfo(
    VOS_UINT8                           ucLRTimerT3212
)
{
    VOS_UINT32                          ulT3212Value;

    /* 从收到的消息结构中获取新的 T3212 定时长度 */
    ulT3212Value    = ucLRTimerT3212 * MM_T3212_UNIT_TRANSFORM;     /* 6分钟->毫秒 */

    if (ulT3212Value > MM_TIMER_T3212_MAX_VALUE)
    {
        ulT3212Value = MM_TIMER_T3212_MAX_VALUE;
    }

    /* 对定时长度分析处理 */
    if ((MM_CONST_NUM_0 == ulT3212Value)
     || (MM_CONST_NUM_0 == gstMmTimer[MM_TIMER_T3212].ulTimerLen))                /* 为零 */
    {
        /* 设置 T3212 定时长度为无效值 */
        gstMmTimer[MM_TIMER_T3212].ulTimerLen = ulT3212Value;
        Mm_TimerStop(MM_TIMER_T3212);
    }
    else /* 正常值 */
    {
        if (gstMmTimer[MM_TIMER_T3212].ulTimerLen != ulT3212Value)
        {
            Mm_ComT3212(ulT3212Value);
        }
    }

    return;
}


VOS_VOID NAS_MM_UpdateNetModeInfo_RcvGuSysInfo(
    VOS_UINT8                           ucNetworkOperationMode
)
{
    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        if (ucNetworkOperationMode < MM_CONST_NUM_4)
        {
            /* 网络模式信息有效 */
            if (MM_CONST_NUM_0 != ucNetworkOperationMode)
            {
                /* 获取 ucNewNtMod 值 */
                g_MmGlobalInfo.ucNewNtMod = ucNetworkOperationMode;
            }
            else
            {
                g_MmGlobalInfo.ucNewNtMod = MM_NET_MODE_II;
            }
        }
    }
    else
    {
        g_MmGlobalInfo.ucNewNtMod = ucNetworkOperationMode;

        /* 如果当前的网络被bar，那么直接刷新一下网络模式*/
        if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
        {
             g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;
        }
    }

    /* 如果当前网络模式未知,设置为新获取网络模式 */
    if (MM_CONST_NUM_0 == g_MmGlobalInfo.ucNtMod)
    {
        g_MmGlobalInfo.ucNtMod      = g_MmGlobalInfo.ucNewNtMod;
    }

    return;
}




VOS_VOID NAS_MM_UpdateNetworkInfo_GasSysInfo(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT8                           ucSimPsRegStatus;
    VOS_UINT8                           ucPsAttachAllow;
    MMCMM_GSM_SYS_INFO_IND_ST          *pstSysInfoInd     = VOS_NULL_PTR;

    NAS_MML_LAI_STRU                   *pstAllocT3212ValueLaiInfo = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstCurrCampLaiInfo = VOS_NULL_PTR;

    pstAllocT3212ValueLaiInfo = NAS_MM_GetAllocT3212ValueLaiInfo();
    pstCurrCampLaiInfo         = NAS_MML_GetCurrCampLai();

    pstSysInfoInd = (MMCMM_GSM_SYS_INFO_IND_ST *)pRcvMsg;

    g_MmGlobalInfo.ucSysInfoFlg             = MM_TRUE;
    g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg  = pstSysInfoInd->ulForbiddenFlg;

    /* 收到系统消息默认小区ID不改变 */
    g_MmGlobalInfo.MsCsInfo.ucCellChgFlg = MM_FALSE;

    if (pstSysInfoInd->ulCellId != g_MmGlobalInfo.MsCsInfo.ulCellId)
    {
        g_MmGlobalInfo.MsCsInfo.ulCellId = pstSysInfoInd->ulCellId;
        g_MmGlobalInfo.MsCsInfo.ucCellChgFlg = MM_TRUE;
    }

    /* 处理紧急呼列表 */
    NAS_MM_ProcEccNumList_RcvSysinfo(pstSysInfoInd->stPlmnId.ulMcc);

    if (VOS_TRUE == NAS_MM_IsNeedUpdateT3212Value_RcvGuSysInfo())
    {
        NAS_MM_UpdateT3212Value_RcvGuSysInfo(pstSysInfoInd->ucLRTimerT3212);

        pstAllocT3212ValueLaiInfo->stPlmnId.ulMcc   = pstCurrCampLaiInfo->stPlmnId.ulMcc;
        pstAllocT3212ValueLaiInfo->stPlmnId.ulMnc   = pstCurrCampLaiInfo->stPlmnId.ulMnc;
        pstAllocT3212ValueLaiInfo->aucLac[0]        = pstCurrCampLaiInfo->aucLac[0];
        pstAllocT3212ValueLaiInfo->aucLac[1]        = pstCurrCampLaiInfo->aucLac[1];
        pstAllocT3212ValueLaiInfo->enCampPlmnNetRat = pstCurrCampLaiInfo->enCampPlmnNetRat;
        NAS_MM_SetNetworkT3212ValueType(NAS_MM_T3212_VALUE_TYPE_BROADCAST);
    }

    /* 默认收到系统消息允许attach */
    g_MmGlobalInfo.ucAttFlg         = MM_ATT_NEED;

    /* 依据消息中 Att 内容，设置全局 Att 标志 */
    if (MM_CONST_NUM_0 == pstSysInfoInd->ucAttachDetach)
    {
        g_MmGlobalInfo.ucAttFlg     = MM_ATT_NOT_NEED;
    }

    /* GPRS不支持 */
    if (MM_CONST_NUM_0 == pstSysInfoInd->ucGprsSupportInd)
    {
        g_MmGlobalInfo.usRac            = MM_UNSUPPORT_GPRS;
        g_MmGlobalInfo.ucNtMod          = MM_NET_MODE_INVALID;
        g_MmGlobalInfo.ucNewNtMod       = MM_NET_MODE_INVALID;
    }
    else
    {
        /* RAI发生改变 */
        if ((VOS_TRUE             == NAS_MML_IsCampLaiInfoChanged())
         || (g_MmGlobalInfo.usRac != pstSysInfoInd->ucRac))
        {
            if (MM_TRUE == g_MmGlobalInfo.ucLikeNetmode2)
            {
                g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;
                Mm_TimerStop( MM_TIMER_T3211 );
                Mm_TimerStop( MM_TIMER_T3212 );
            }

            /* 更改 LikeB 标志 */
            g_MmGlobalInfo.ucLikeB = MM_FALSE;
        }

        g_MmGlobalInfo.usRac  = (VOS_UINT16)pstSysInfoInd->ucRac;

        NAS_MM_UpdateNetModeInfo_RcvGuSysInfo(pstSysInfoInd->ucNetworkOperationMode);

        ucSimPsRegStatus    = NAS_MML_GetSimPsRegStatus();
        ucPsAttachAllow     = NAS_MML_GetPsAttachAllowFlg();

        if ((MM_NET_MODE_I == g_MmGlobalInfo.ucNewNtMod)
         && ((VOS_FALSE    == ucSimPsRegStatus)
          || (VOS_FALSE    == ucPsAttachAllow)))
        {
            g_MmGlobalInfo.ucLikeB = MM_TRUE;
        }
    }

    /* 收到G下的系统消息默认NSD MOD为R99的 */
    g_stMmNsd.ucNsdMod = MM_NSD_MOD_R99_ONWARDS;

    if (GRRMM_MSC_RELEASE98_OR_OLDER == pstSysInfoInd->ucMsrRelease)
    {
        g_stMmNsd.ucNsdMod = MM_NSD_MOD_R98_OR_OLDER;
    }

    return;
}



VOS_VOID NAS_MM_UpdateNetworkInfo_WasSysInfo(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT8                           ucSimPsRegStatus;
    VOS_UINT8                           ucPsAttachAllow;
    MMCMM_SYS_INFO_IND_STRU            *pstSysInfoInd = VOS_NULL_PTR;

    NAS_MML_LAI_STRU                   *pstAllocT3212ValueLaiInfo = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstCurrCampLaiInfo = VOS_NULL_PTR;

    pstAllocT3212ValueLaiInfo  = NAS_MM_GetAllocT3212ValueLaiInfo();
    pstCurrCampLaiInfo         = NAS_MML_GetCurrCampLai();

    pstSysInfoInd = (MMCMM_SYS_INFO_IND_STRU *)pRcvMsg;

    if (RRC_NAS_SYS_MSK_CS_DRX == (RRC_NAS_SYS_MSK_CS_DRX & pstSysInfoInd->ulMask))
    {
        g_MmGlobalInfo.MsCsInfo.ucCsDrxLen = (VOS_UINT8)pstSysInfoInd->ulCsDrxLength;
    }

    if (RRC_NAS_SYS_MSK_CSPS_INFO == (RRC_NAS_SYS_MSK_CSPS_INFO & pstSysInfoInd->ulMask))
    {
        /* W下PS不支持 */
        if (0 == pstSysInfoInd->ucPsInfoSize)
        {
            if (MMC_MM_SYS_INFO_TYPE_SYS == pstSysInfoInd->enSysInfoType)
            {
                g_MmGlobalInfo.usRac      = MM_UNSUPPORT_GPRS;
                g_MmGlobalInfo.ucNtMod    = MM_NET_MODE_INVALID;
                g_MmGlobalInfo.ucNewNtMod = MM_NET_MODE_INVALID;
            }
        }
        else
        {
            /* RAI发生改变 */
            if ((VOS_TRUE             == NAS_MML_IsCampLaiInfoChanged())
             || (g_MmGlobalInfo.usRac != pstSysInfoInd->ucRac))
            {
                if (MM_TRUE == g_MmGlobalInfo.ucLikeNetmode2)
                {
                    g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;
                    Mm_TimerStop( MM_TIMER_T3211 );
                    Mm_TimerStop( MM_TIMER_T3212 );
                }

                g_MmGlobalInfo.ucLikeB = MM_FALSE;
            }

            g_MmGlobalInfo.usRac  = (VOS_UINT16)pstSysInfoInd->ucRac;

            /* 更新网络模式信息 */
            NAS_MM_UpdateNetModeInfo_RcvGuSysInfo(pstSysInfoInd->ucNetworkOperationMode);

            ucSimPsRegStatus    = NAS_MML_GetSimPsRegStatus();
            ucPsAttachAllow     = NAS_MML_GetPsAttachAllowFlg();

            if ((MM_NET_MODE_I == g_MmGlobalInfo.ucNewNtMod)
             && ((VOS_FALSE    == ucSimPsRegStatus)
              || (VOS_FALSE    == ucPsAttachAllow)))
            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;
            }
        }

        if (0 != pstSysInfoInd->ucCsInfoSize)
        {
            if (VOS_TRUE == NAS_MM_IsNeedUpdateT3212Value_RcvGuSysInfo())
            {
                NAS_MM_UpdateT3212Value_RcvGuSysInfo(pstSysInfoInd->ucLRTimerT3212);

                pstAllocT3212ValueLaiInfo->stPlmnId.ulMcc   = pstCurrCampLaiInfo->stPlmnId.ulMcc;
                pstAllocT3212ValueLaiInfo->stPlmnId.ulMnc   = pstCurrCampLaiInfo->stPlmnId.ulMnc;
                pstAllocT3212ValueLaiInfo->aucLac[0]        = pstCurrCampLaiInfo->aucLac[0];
                pstAllocT3212ValueLaiInfo->aucLac[1]        = pstCurrCampLaiInfo->aucLac[1];
                pstAllocT3212ValueLaiInfo->enCampPlmnNetRat = pstCurrCampLaiInfo->enCampPlmnNetRat;
                NAS_MM_SetNetworkT3212ValueType(NAS_MM_T3212_VALUE_TYPE_BROADCAST);
            }

            /* 收到系统消息默认允许attach */
            g_MmGlobalInfo.ucAttFlg = MM_ATT_NEED;

            if (MM_CONST_NUM_0 == pstSysInfoInd->ucAttachDetach)
            {
                g_MmGlobalInfo.ucAttFlg = MM_ATT_NOT_NEED;
            }
        }
    }

    /* 处理紧急呼列表 */
    NAS_MM_ProcEccNumList_RcvSysinfo(pstSysInfoInd->PlmnId.ulMcc);

    g_MmGlobalInfo.ucSysInfoFlg = MM_TRUE;
    g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg = pstSysInfoInd->ulForbiddenFlg;

    /* 收到系统消息默认小区ID不改变 */
    g_MmGlobalInfo.MsCsInfo.ucCellChgFlg = MM_FALSE;

    if (pstSysInfoInd->ulCellId != g_MmGlobalInfo.MsCsInfo.ulCellId)
    {
        g_MmGlobalInfo.MsCsInfo.ulCellId     = pstSysInfoInd->ulCellId;
        g_MmGlobalInfo.MsCsInfo.ucCellChgFlg = MM_TRUE;
    }

    return;
}



VOS_UINT8 NAS_MM_IsNeedClearAttemptCounter( VOS_VOID )
{
    /* 根据24.008 4.4.4.5 The attempt counter is reset when:
        in case of service state ATTEMPTING to UPDATE，
        a MS detects that a new location area is entered */
    if ((MM_IDLE_PLMN_SEARCH           == g_MmGlobalInfo.ucState)
     && ((MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucPreState)
      || (MM_IDLE_NO_CELL_AVAILABLE    == g_MmGlobalInfo.ucPreState)))
    {
        if (VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_VOID NAS_MM_SndMmcForbidenRslt(VOS_VOID)
{
    if (MMCMM_FORBIDDEN_PLMN == (MMCMM_FORBIDDEN_PLMN & g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                MM_MMC_LU_RESULT_FAILURE,
                NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN);
    }
    else if (MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS == (MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS & g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
            MM_MMC_LU_RESULT_FAILURE,
            NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS);
    }
    else
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                            MM_MMC_LU_RESULT_FAILURE,
                            NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM);
    }
}




VOS_UINT8 NAS_MM_IsClassAAndNmoIMode(
    VOS_UINT8                               ucCurNtMod
)
{
    if ((VOS_TRUE      == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == ucCurNtMod)
     && (MM_FALSE      == g_MmGlobalInfo.ucLikeB))
    {
       return VOS_TRUE;
    }

    return VOS_FALSE;
}







MM_LAI_STRU *NAS_MM_GetAttemptUpdateLaiInfo(VOS_VOID)
{
    return &(g_MmGlobalInfo.MsCsInfo.stAttemptToUpdateLai);
}


VOS_VOID NAS_MM_InitLaiInfo(
    MM_LAI_STRU                        *pstLai
)
{
    pstLai->PlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstLai->PlmnId.ulMnc = NAS_MML_INVALID_MNC;
    pstLai->ulLac        = MM_INVALID_LAI;

    return;
}


VOS_UINT32 NAS_MM_IsSameLaiInfo(
    MM_LAI_STRU                        *pstCurrLai,
    MM_LAI_STRU                        *pstOldLai
)
{
    if ( pstCurrLai->PlmnId.ulMcc != pstOldLai->PlmnId.ulMcc )
    {
        return VOS_FALSE;
    }

    if ( pstCurrLai->PlmnId.ulMnc != pstOldLai->PlmnId.ulMnc )
    {
        return VOS_FALSE;
    }

    if ( pstCurrLai->ulLac != pstOldLai->ulLac)
    {
        return VOS_FALSE;
    }


    return VOS_TRUE;
}




VOS_VOID NAS_MM_LocationUpdateAttemptCounter(
    VOS_UINT32                          ulMmCause
)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8  enCsUpdateStatus;
    MM_LAI_STRU                                *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                           *pstCampLaiInfo  = VOS_NULL_PTR;

    /* 次数加1 */
    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt++;

    if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
    {
        enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
        if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
         &&  (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
        {
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

            NAS_MM_UpdateEquPlmnInfo(ulMmCause);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        ulMmCause);                    /* 向MMC发送MMCMM_LU_RESULT_IND             */
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     ulMmCause);                    /* 向MMC发送MMCMM_LU_RESULT_IND             */
            Mm_ComNasInfoSav(MM_STATUS_ATTACHED,
                             NAS_MML_GetSimCsSecurityCksn());
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录前状态                               */
            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
            Mm_TimerStop(MM_TIMER_T3211);
            Mm_TimerStart(MM_TIMER_T3211);                                      /* 启动T3211                                */


        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;


            /* 在U2状态，保存当前的LAI信息 */
            pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
            pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

            pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
            pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
            pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

            NAS_MM_UpdateEquPlmnInfo(ulMmCause);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        ulMmCause);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     ulMmCause);

            /* 进U2的公共处理 */
            Mm_ComToU2Handle();

            Mm_TimerStop(MM_TIMER_T3211);
            Mm_TimerStart(MM_TIMER_T3211);                                      /* 启动T3211                                */
        }
    }
    else
    {
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;

        /* 在U2状态，保存当前的LAI信息 */
        pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
        pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

        pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
        pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
        pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

        NAS_MM_UpdateEquPlmnInfo(ulMmCause);

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    ulMmCause);

        NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                 ulMmCause);

        /* 进U2的公共处理 */
        Mm_ComToU2Handle();

        Mm_TimerStop(MM_TIMER_T3212);                                           /* T3212先进行停止                                */

        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);

    }
}


VOS_VOID NAS_MM_UpdateLauRetryFlg_RcvRelInd(
    RRMM_REL_IND_STRU                  *pRrcRelInd
)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

    enCsUpdateStatus    = NAS_MML_GetCsUpdateStatus();

    /* ucLuAttmptCnt是加1之后的次数 */
    if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
    {
        if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
         &&  (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
        {
            g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
        }
        else
        {
            if (VOS_FALSE == NAS_MM_IsRrRelCauseNeedRetryLau(pRrcRelInd->ulRelCause))
            {
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;
            }
        }
    }
    else
    {
        if (VOS_FALSE == NAS_MM_IsRrRelCauseNeedRetryLau(pRrcRelInd->ulRelCause))
        {
            g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;
        }
    }
}



NAS_MM_NETWORK_T3212_VALUE_TYPE_ENUM_UINT8 NAS_MM_GetNetworkT3212ValueType(VOS_VOID)
{
    return g_MmGlobalInfo.stT3212Info.enNetworkT3212ValueType;
}


VOS_VOID NAS_MM_SetNetworkT3212ValueType(
    NAS_MM_NETWORK_T3212_VALUE_TYPE_ENUM_UINT8              enT3212ValueType
)
{
    g_MmGlobalInfo.stT3212Info.enNetworkT3212ValueType = enT3212ValueType;
    return;
}


NAS_MML_LAI_STRU *NAS_MM_GetAllocT3212ValueLaiInfo(VOS_VOID)
{
    return (&g_MmGlobalInfo.stT3212Info.stAllocT3212ValueLaiInfo);
}




VOS_UINT32 NAS_MM_GetNetworkAllocT3212Len(VOS_VOID)
{
    return gstMmTimer[MM_TIMER_T3212].ulTimerLen;
}


VOS_VOID  NAS_MM_SetNetworkAllocT3212Len(
    VOS_UINT32                          ulNetworkAllocT3212Len
)
{
    gstMmTimer[MM_TIMER_T3212].ulTimerLen = ulNetworkAllocT3212Len;
}


VOS_VOID  NAS_MM_LogT3212Info(VOS_VOID)
{
    NAS_MM_LOG_T3212_INFO_STRU         *pstMsg = VOS_NULL_PTR;

    NAS_MML_LAI_STRU                   *pstAllocT3212ValueLaiInfo = VOS_NULL_PTR;

    pstAllocT3212ValueLaiInfo = NAS_MM_GetAllocT3212ValueLaiInfo();

    pstMsg = (NAS_MM_LOG_T3212_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MM,
                                         sizeof(NAS_MM_LOG_T3212_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_LogT3212Info:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(NAS_MM_LOG_T3212_INFO_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MM_LOG_T3212_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = MMOM_LOG_T3212_INFO_IND;

    /* NV中定制的T3212信息 */
    PS_MEM_CPY( &(pstMsg->stMmlT3212NvCfgInfo), NAS_MML_GetT3212TimerInfo(), sizeof(NAS_MML_T3212_TIMER_INFO_CONFIG_STRU));

    /* 当前使用NV的T3212时长的计数 */
    pstMsg->ulT3212Count                = NAS_MM_GetT3212StartCount();

    /* 网络分配的T3212定时器时长 */
    pstMsg->ulNetworkT3212Len           = NAS_MM_GetNetworkAllocT3212Len();

    /* 网络分配的T3212定时器时长 */
    pstMsg->ulNetworkRandT3212Len       = NAS_MM_GetNetworkT3212RandLen();

    PS_MEM_CPY(&pstMsg->stAllocT3212ValueLaiInfo, pstAllocT3212ValueLaiInfo, sizeof(pstMsg->stAllocT3212ValueLaiInfo));
    pstMsg->enT3212ValueType = NAS_MM_GetNetworkT3212ValueType();

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MM, pstMsg);

    return;
}



VOS_VOID NAS_MM_StartT3212Timer(
    NAS_MM_T3212_START_SCENE_ENUM_UINT32                    enT3212StartScene
)
{
    VOS_UINT32                          ulCurrT3212Len;
    NAS_MM_T3212_LEN_TYPE_ENUM_UINT8    enCurrT3212LenType;
    VOS_UINT32                          ulResult;

    enCurrT3212LenType = NAS_MM_T3212_LEN_TYPE_NETWORK_ALLOC_LEN;

    /* 如果当前T3212定时器不是停止状态，则不需要处理 */
    if (MM_TIMER_STOP != gstMmTimer[MM_TIMER_T3212].ucTimerStatus )
    {
        return;
    }

    /* 可维可测勾T3212相关信息包 */
    NAS_MM_LogT3212Info();

    /* 在启动T3212时候需要设置时长: NV配置的时长或者原有的时长 */
    ulCurrT3212Len = NAS_MM_GetT3212StartSceneTimerLen(enT3212StartScene, &enCurrT3212LenType);

    /* 如果当前的T3212时长为0，则不需要启动 */
    if (0 == ulCurrT3212Len)
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_StartT3212Timer:WARNING: Currt3212 TIMER LEN IS ZERO !");

        return;
    }

    /* 启动T3212  Mm_TimerStart(MM_TIMER_T3212); */
    ulResult = Mm_StartRelTimer(
                               &gstMmTimer[MM_TIMER_T3212].hTimer,              /* 存放TIMER ID的地址 */
                               WUEPS_PID_MM,
                               ulCurrT3212Len,                                  /* 时长 */
                               MM_TIMER_T3212,                                  /* 消息队列的ID */
                               gstMmTimer[MM_TIMER_T3212].ulParam,              /* 消息地址 */
                               gstMmTimer[MM_TIMER_T3212].ucMode                /* 消息优先级 */
                               );                                               /* 创建支持消息的定时器 */

    /* 启动失败，则退出 */
    if ( VOS_OK != ulResult )
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_StartT3212Timer:WARNING: TIMER CREATE FAILURE!");
        return;
    }

    /* 设置当前定时器运行标志 */
    gstMmTimer[MM_TIMER_T3212].ucTimerStatus = MM_TIMER_RUNNING;

    if (NAS_MM_T3212_LEN_TYPE_NV_DEFINED == enCurrT3212LenType)
    {
        /* 如果当前需要用NV中的定时器时长，则T3212启动累计加1 */
        NAS_MM_IncreaseT3212Counter();
    }
    else if (NAS_MM_T3212_LEN_TYPE_NETWORK_ALLOC_RANDOM_LEN == enCurrT3212LenType)
    {
        /* 初始化全局变量的值 */
        NAS_MM_SetNetworkT3212RandLen(0);
    }
    else
    {
    }

    /* T3212正常启动后，重置T3212计数 */
    if (NAS_MM_T3212_START_SCENE_NORMAL_START == enT3212StartScene)
    {
        NAS_MM_InitT3212Counter();
    }

    return;

}


VOS_VOID NAS_MM_IncreaseT3212Counter(VOS_VOID)
{
    /* 达到最大值就不增加  */
    if (g_MmGlobalInfo.stT3212Info.ulUseNvT3212StartLenCount >= NAS_MM_T3212_START_SCENE_COUNTER_MAX_VALUE )
    {
        return;
    }

    g_MmGlobalInfo.stT3212Info.ulUseNvT3212StartLenCount++;

    return;
}


VOS_VOID NAS_MM_InitT3212Counter(VOS_VOID)
{
    g_MmGlobalInfo.stT3212Info.ulUseNvT3212StartLenCount = 0;

    return;
}


VOS_UINT32 NAS_MM_GetT3212StartCount(VOS_VOID)
{
    return g_MmGlobalInfo.stT3212Info.ulUseNvT3212StartLenCount;
}


VOS_UINT32 NAS_MM_GetNetworkT3212RandLen(VOS_VOID)
{
    return g_MmGlobalInfo.stT3212Info.ulNetworkT3212RandLen;
}


VOS_VOID  NAS_MM_SetNetworkT3212RandLen(
    VOS_UINT32                          ulCurrT3212Len
)
{
    g_MmGlobalInfo.stT3212Info.ulNetworkT3212RandLen = ulCurrT3212Len;
}


VOS_UINT32 NAS_MM_IsNeedUseTheNvimT3212TimerLen(
    NAS_MM_T3212_START_SCENE_ENUM_UINT32                    enT3212StartScene
)
{
    NAS_MML_T3212_TIMER_INFO_CONFIG_STRU                   *pstT3212Info        = VOS_NULL_PTR;
    VOS_UINT32                                              ulT3212StartSceneCtrlBitIndex;
    VOS_UINT32                                              ulT3212StartCount;

    pstT3212Info                    = NAS_MML_GetT3212TimerInfo();
    ulT3212StartCount               = NAS_MM_GetT3212StartCount();
    ulT3212StartSceneCtrlBitIndex   = NAS_MML_T3212_START_SCEAN_INVALID_BIT_INDEX;

    /* 判断当前是测试卡，不需要从NVIM中配置的T3212定时器时长值 */
    if (VOS_TRUE == USIMM_IsTestCard())
    {
        return VOS_FALSE;
    }

    /* NV未激活时候，则不使用NVIM中的值  */
    if (VOS_FALSE == pstT3212Info->ulT3212NvActiveFlg)
    {
        return VOS_FALSE;
    }

    /* 判断当前T3212失败的COUNTER已经超过第二阶段了，则不需要从NVIM中获取T3212定时器的时长 */
    if (ulT3212StartCount >= (pstT3212Info->ulT3212Phase1Count + pstT3212Info->ulT3212Phase2Count))
    {
        return VOS_FALSE;
    }

    /* 从表中获取当前场景对应的控制BIT索引 */
    ulT3212StartSceneCtrlBitIndex = NAS_MM_MapT3212StartSceneToCtrlBitIndex(enT3212StartScene);

    /* 判断当前T3212启动场景NVIM配置是否使能，TRUE为使能，FALSE为不使能 */
    if (VOS_TRUE == NAS_MM_GetT3212StartSceneCtrlBitIndexValue(ulT3212StartSceneCtrlBitIndex))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_MM_MapT3212StartSceneToCtrlBitIndex(
    NAS_MM_T3212_START_SCENE_ENUM_UINT32                    enT3212StartScene
)
{
    NAS_MM_T3212_START_SCENE_CFG_TBL_STRU                  *pstT3212StartSceanCtrlTblPtr = VOS_NULL_PTR;
    VOS_UINT32                                              ulT3212StartSceanCtrlBitIndex;
    VOS_UINT32                                              i;

    pstT3212StartSceanCtrlTblPtr = NAS_MM_GET_T3212_START_SCENE_CFG_TBL_PTR();

    /* 默认为非法INDEX */
    ulT3212StartSceanCtrlBitIndex = NAS_MML_T3212_START_SCEAN_INVALID_BIT_INDEX;

    /* 从表中获取当前场景对应的控制BIT索引 */
    for (i = 0; i < NAS_MM_GET_T3212_START_SCENE_CFG_TBL_SIZE(); i++)
    {
        /* 根据配置表,获取当前场景的控制BIT位索引 */
        if (enT3212StartScene == pstT3212StartSceanCtrlTblPtr[i].enT3212StartScene)
        {
            ulT3212StartSceanCtrlBitIndex = pstT3212StartSceanCtrlTblPtr[i].ulT3212StartSceneCtrlBitIndex;

            break;
        }
    }

    return ulT3212StartSceanCtrlBitIndex;

}



VOS_UINT32 NAS_MM_GetT3212StartSceneCtrlBitIndexValue(
    VOS_UINT32                          ulT3212StartSceneCtrlBitIndex
)
{
    NAS_MML_T3212_TIMER_INFO_CONFIG_STRU                   *pstT3212Info        = VOS_NULL_PTR;

    pstT3212Info = NAS_MML_GetT3212TimerInfo();

    /* 当前索引非法 */
    if (ulT3212StartSceneCtrlBitIndex >= NAS_MML_T3212_START_SCEAN_INVALID_BIT_INDEX)
    {
        return VOS_FALSE;
    }

    /* 使用控制字节1:bit0~bit31 */
    if (ulT3212StartSceneCtrlBitIndex <= NAS_MML_T3212_START_SCEAN_MASK1_MAX_BIT_INDEX)
    {
        /* 根据NV中是否使能BIT值为1则使能，为0则不使能 */
        if (NAS_MML_T3212_START_SCENE_VALID_BIT_INDEX_VALUE == ((pstT3212Info->ulT3212StartSceneCtrlBitMask >> ulT3212StartSceneCtrlBitIndex) & NAS_MML_T3212_START_SCENE_VALID_BIT_INDEX_VALUE))
        {
            return VOS_TRUE;
        }
    }
    else
    {
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MM_GetT3212StartSceneTimerLen(
    NAS_MM_T3212_START_SCENE_ENUM_UINT32                    enT3212StartScene,
    NAS_MM_T3212_LEN_TYPE_ENUM_UINT8                       *penT3212LenType
)
{
    NAS_MML_T3212_TIMER_INFO_CONFIG_STRU                   *pstT3212Info        = VOS_NULL_PTR;
    VOS_UINT32                                              ulT3212StartCount;
    VOS_UINT32                                              ulNetworkAllocT3212Len;
    VOS_UINT32                                              ulNetworkT3212RandLen;

    pstT3212Info                    = NAS_MML_GetT3212TimerInfo();
    ulT3212StartCount               = NAS_MM_GetT3212StartCount();
    ulNetworkAllocT3212Len          = NAS_MM_GetNetworkAllocT3212Len();
    ulNetworkT3212RandLen           = NAS_MM_GetNetworkT3212RandLen();
    *penT3212LenType                = NAS_MM_T3212_LEN_TYPE_NETWORK_ALLOC_LEN;

    /* 判断当前是否从NV中获取配置的T3212定时器时长 */
    if (VOS_TRUE == NAS_MM_IsNeedUseTheNvimT3212TimerLen(enT3212StartScene))
    {
        *penT3212LenType = NAS_MM_T3212_LEN_TYPE_NV_DEFINED;

        /* 如果T3212失败次数小于第一阶段，则使用第一阶段的时长，否则用第二阶段的时长 */
        if (ulT3212StartCount < pstT3212Info->ulT3212Phase1Count)
        {
            return pstT3212Info->ulT3212Phase1TimeLen;
        }

        return pstT3212Info->ulT3212Phase2TimeLen;
    }

    /* 取网络分配的T3212 RAND定时器时长  */
    if ( (MM_CONST_NUM_0 != ulNetworkT3212RandLen)
      && (MM_CONST_NUM_0 != ulNetworkAllocT3212Len) )
    {
        *penT3212LenType = NAS_MM_T3212_LEN_TYPE_NETWORK_ALLOC_RANDOM_LEN;

        /* 如果网络下发新的T3212时长，当前T3212没有在运行，则取不大于网络下发时长的随机值 */
        return ulNetworkT3212RandLen;
    }

    /* 取网络下发的T3212时长 */
    return ulNetworkAllocT3212Len;
}

#if (FEATURE_ON == FEATURE_LTE)
#if (FEATURE_ON == FEATURE_DSDS)

VOS_VOID  NAS_MM_ConvertCsfbServiceStatusToRrcSessionType(
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCsfbServiceStatus,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8                        *penRrcSessionType
)
{
    switch (enCsfbServiceStatus)
    {
        case NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CSFB;
            break;

        case NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CSFB;
            break;

        case NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MO_EMERGENCY_CSFB;
            break;

        case NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MT_CSFB;
            break;

        default:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_BUTT;
            break;
    }

    return;
}
#endif


VOS_VOID NAS_MM_ProcCsfbServiceStatusChange(
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCurStatus,
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enTargetStatus
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;


    /* 如果传入BUTT值，默认认为不存在，一般禁止传入BUTT */
    if ( NAS_MML_CSFB_SERVICE_STATUS_BUTT == enCurStatus )
    {
        enCurStatus = NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST;
    }

    if ( NAS_MML_CSFB_SERVICE_STATUS_BUTT == enTargetStatus )
    {
        enTargetStatus = NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST;
    }

    /* CSFB标志从无到有，发送申请资源通知 */
    if ( (NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST == enCurStatus)
      && (NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST != enTargetStatus) )
    {
        NAS_MM_ConvertCsfbServiceStatusToRrcSessionType(enTargetStatus, &enRrcSessionType);

        /* 释放申请资源 */
        NAS_MM_SndBeginSessionNotify(enRrcSessionType);
    }

    /* CSFB标志从有到无，发送释放资源通知 */
    if ( (NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST != enCurStatus)
      && (NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST == enTargetStatus) )
    {
        NAS_MM_ConvertCsfbServiceStatusToRrcSessionType(enCurStatus, &enRrcSessionType);

        /* 释放申请资源 */
        NAS_MM_SndEndSessionNotify(enRrcSessionType);
    }
#endif

    return;
}
#endif


NAS_MMCM_REL_CAUSE_ENUM_UINT32 NAS_MM_ConvertRrcRelCauseToMmCcRelCause(
    RRC_REL_CAUSE_ENUM_UINT32           enRrcRelCause
)
{
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enRelCause;
    VOS_UINT32                          i;

    enRelCause  = NAS_MMCM_REL_CAUSE_RR_REL_OTHER_REASON;

    for (i = 0; i < (sizeof(g_astRrcToMmCcRelCause) / sizeof(g_astRrcToMmCcRelCause[0])); i++)
    {
        if (enRrcRelCause == g_astRrcToMmCcRelCause[i].enRrcRelCause)
        {
            enRelCause = g_astRrcToMmCcRelCause[i].enMmCcRelCause;
        }
    }

    return enRelCause;
}


NAS_MMCM_REL_CAUSE_ENUM_UINT32 NAS_MM_ConvertEstCnfRsltToMmCcRelCause(
    RRC_NAS_EST_RESULT_ENUM_UINT32     enEstCnfRslt
)
{
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enRelCause;
    VOS_UINT32                          i;

    enRelCause  = NAS_MMCM_REL_CAUSE_RR_REL_OTHER_REASON;

    for (i = 0; i < (sizeof(g_astEstRsltToMmCcRelCause) / sizeof(g_astEstRsltToMmCcRelCause[0])); i++)
    {
        if (enEstCnfRslt == g_astEstRsltToMmCcRelCause[i].enEstRslt)
        {
            enRelCause = g_astEstRsltToMmCcRelCause[i].enMmCcRelCause;
        }
    }

    return enRelCause;
}



NAS_MM_T3212_START_SCENE_ENUM_UINT32 NAS_MM_ConvertLauEstCnfRsltToT3212StartScean(
    RRC_NAS_EST_RESULT_ENUM_UINT32      enEstCnfRslt
)
{
    VOS_UINT32                                              i;
    NAS_MM_T3212_START_SCENE_ENUM_UINT32                    enT3212StartScene;

    enT3212StartScene  = NAS_MM_T3212_START_SCENE_BUTT;

    for (i = 0; i < (sizeof(g_astLauEstCnfRsltToT3212StartScene) / sizeof(g_astLauEstCnfRsltToT3212StartScene[0])); i++)
    {
        if (enEstCnfRslt == g_astLauEstCnfRsltToT3212StartScene[i].enEstRslt)
        {
            enT3212StartScene = g_astLauEstCnfRsltToT3212StartScene[i].enT3212StartScene;
            break;
        }
    }

    return enT3212StartScene;
}


#if   (FEATURE_ON == FEATURE_LTE)

NAS_MMCM_REL_CAUSE_ENUM_UINT32 NAS_MM_ConvertCsfbSrvRsltToMmCcRelCause(
    LMM_MM_CSFB_SERVICE_END_IND_STRU   *pstCsfbEndInd
)
{
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enRelCause;
    VOS_UINT32                          i;

    enRelCause  = (VOS_UINT32)NAS_MMCM_REL_CAUSE_BUTT;

    /* CSFB service rej */
    if (MM_LMM_CSFB_SERVICE_RSLT_CN_REJ == pstCsfbEndInd->enCsfbSrvRslt)
    {
        enRelCause  = (pstCsfbEndInd->ulCnCause) + NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_BEGIN;
    }
    /* 以下为CSFB LMM Error */
    else
    {
        for (i = 0; i < (sizeof(g_astCsfbRsltToMmCcRelCause) / sizeof(g_astCsfbRsltToMmCcRelCause[0])); i++)
        {
            if (pstCsfbEndInd->enCsfbSrvRslt    == g_astCsfbRsltToMmCcRelCause[i].enCsfbRslt)
            {
                enRelCause = g_astCsfbRsltToMmCcRelCause[i].enMmCcRelCause;
            }
        }
    }

    return enRelCause;
}
#endif


VOS_UINT32 NAS_MM_IsGsmOnlyEstCnfRslt(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult
)
{
    if ((RRC_EST_RANDOM_ACCESS_REJECT == ulResult)
     || (RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO == ulResult)
     || (RRC_EST_RJ_RA_FAIL == ulResult)
     || (RRC_EST_RJ_RA_FAIL_NO_VALID_INFO == ulResult))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


VOS_UINT8 NAS_MM_IsHoBetweenGU(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSrcRatType,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRatType,
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause
)
 {
    /* 异系统失败，返回FALSE */
    if (enSrcRatType == enDestRatType)
    {
        return VOS_FALSE;
    }

    /* 异系统前后的接入技术是LTE，返回FALSE */
#if (FEATURE_ON == FEATURE_LTE)
    if ( (NAS_MML_NET_RAT_TYPE_LTE == enSrcRatType)
      || (NAS_MML_NET_RAT_TYPE_LTE == enDestRatType) )
    {
        return VOS_FALSE;
    }
#endif

    /* 挂起原因值不是handover，返回FALSE */
    if (MMC_SUSPEND_CAUSE_HANDOVER != enSuspendCause)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_VOID NAS_MM_StartHoWaitSysInfoTimer(
    VOS_UINT8                           ucTimerId
)
{
    /* 定时器先停再启,定时器时长可NV配置 */
    Mm_TimerStop(MM_TIMER_NORMAL_CSFB_HO_WAIT_SYSINFO);
    Mm_TimerStop(MM_TIMER_EMERGENCY_CSFB_HO_WAIT_SYSINFO);
    Mm_TimerStop(MM_TIMER_CS_HO_WAIT_SYSINFO);

    /* 启动HO等系统消息的定时器 */
    Mm_TimerStart(ucTimerId);

    return;
}


#if (FEATURE_ON == FEATURE_PTM)

VOS_VOID NAS_MM_RecordCsPagingFail_WaitForRrConnection(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult
)
{
    /* 建链结果是RRC_EST_SUCCESS或者RRC_EST_PRESENT，不需要记录 */
    if ((RRC_EST_SUCCESS == ulResult)
     || (RRC_EST_PRESENT == ulResult))
    {
        return;
    }

    /* 如果在CSFB MT的过程中则不需要记录CS PAGING FAIL */
    if (NAS_ERR_LOG_CSFB_MT_STATE_NULL != NAS_MML_GetCsfbMtCurrState())
    {
        return;
    }

    if ((MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
     && (MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
     && (MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg))
    {
        /* CS PAGING链路建立失败的异常记录 */
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_EST_FAIL);
    }

    return;
}


VOS_VOID NAS_MM_ParseErrLogCsPagingInfo(
    VOS_VOID                           *pRcvMsg
)
{
    RRMM_PAGING_IND_STRU               *pstWPagingMsg = VOS_NULL_PTR;
    GRRMM_PAGING_IND_ST                *pstGPagingMsg = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    if (VOS_NULL_PTR == pRcvMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_ParseErrLogCsPagingInfo(): parameter is NULL pointer.");
        return;
    }

    enRatType = NAS_MML_GetCurrNetRatType();

    if (NAS_MML_NET_RAT_TYPE_GSM == enRatType)
    {
        pstGPagingMsg = (GRRMM_PAGING_IND_ST *)pRcvMsg;

        NAS_MML_SetErrLogGMsIdType(pstGPagingMsg->ucMSIDType);
        NAS_MML_SetErrLogGPagingType(pstGPagingMsg->ucPagingType);
    }
    else if (NAS_MML_NET_RAT_TYPE_WCDMA == enRatType)
    {
        pstWPagingMsg = (RRMM_PAGING_IND_STRU *)pRcvMsg;

        NAS_MML_SetErrLogWCnDomainId(pstWPagingMsg->ulCnDomainId);
        NAS_MML_SetErrLogWPagingType(pstWPagingMsg->ulPagingType);
        NAS_MML_SetErrLogWPagingCause(pstWPagingMsg->ulPagingCause);
        NAS_MML_SetErrLogWPagingUeId(pstWPagingMsg->ulPagingUeId);
    }
    else
    {
        ;
    }

    return;
}

#endif


VOS_VOID NAS_MM_RecordErrorLogInfo(
    NAS_ERR_LOG_BASE_STATE_ENUM_U32     enBaseState,
    VOS_UINT32                          ulCause
)
{
    VOS_UINT32                          ulTimerStatus;
    NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32  enCsfbMtState;

    ulTimerStatus = NAS_MM_QryTimerStatus(MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE);

    /* 如果在CSFB MT的流程中，则记录相关的CSFB MT的信息 */
    if ((MM_TIMER_RUNNING                                       == ulTimerStatus)
     || (NAS_ERR_LOG_BASE_STATE_CSFB_MT_PROTECT_TI_TIME_OUT     == enBaseState)
     || (NAS_ERR_LOG_BASE_STATE_CSFB_MT_TI_TIME_OUT_RCV_REL_IND == enBaseState))
    {
        enCsfbMtState = NAS_MNTN_ConvertBaseStateToCsfbMtState(enBaseState);

        NAS_MM_FillCsfbMtInfo(enCsfbMtState, ulCause);
    }

    /* 需要记录其他业务场景的信息，添加到下面 */

    return;
}


VOS_VOID NAS_MM_ClearErrorLogInfo(VOS_VOID)
{
    NAS_MML_InitCsfbMtInfo();

    return;
}


VOS_VOID NAS_MM_FillCsfbMtInfo(
    NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32  enCsfbMtState,
    VOS_UINT32                          ulCause
)
{
    NAS_MML_ERRLOG_CSFB_MT_INFO_STRU       *pstCsfbMtInfo   = VOS_NULL_PTR;
    NAS_MNTN_POSITION_INFO_STRU            *pstPositionInfo = VOS_NULL_PTR;
    NAS_ERR_LOG_CSFB_MT_STATE_INFO_STRU    *pstStateInfo    = VOS_NULL_PTR;
    VOS_UINT32                              ulPositionNum;
    VOS_UINT32                              ulStateNum;

    pstCsfbMtInfo       = NAS_MML_GetCsfbMtInfoAddr();

    /* 不是对应的状态，则不记录信息 */
    if (enCsfbMtState > NAS_ERR_LOG_CSFB_MT_CALL_CAUSE_BUTT)
    {
        return;
    }

    NAS_MML_SetCsfbMtCurrState(enCsfbMtState);

    ulPositionNum = NAS_MML_GetCsfbMtRecordPositionNum();
    ulStateNum    = NAS_MML_GetCsfbMtRecordStateNum();

    /* 收到LMM的paging ind状态，需要将当前L的位置区信息记录下来，
       收到系统消息的状态，需要保存相关的位置区信息，
       超过记录的最大个数后就不再记录 */
    if ((NAS_ERR_LOG_CSFB_MT_STATE_GU_SYS_INFO_RECEIVED     == enCsfbMtState)
     || (NAS_ERR_LOG_CSFB_MT_STATE_LTE_SYS_INFO_RECEIVED    == enCsfbMtState)
     || (NAS_ERR_LOG_CSFB_MT_STATE_LMM_CS_PAGING_RECEIVED   == enCsfbMtState))
    {
        if (ulPositionNum < NAS_ERR_LOG_MAX_POSITION_RECORD_NUM)
        {
            pstPositionInfo = &(pstCsfbMtInfo->astPositionInfo[ulPositionNum]);

            NAS_MNTN_OutputPositionInfo(pstPositionInfo);
        }

        NAS_MML_AddCsfbMtRecordPositionNum();
    }

    /* 更新相应的状态信息，超过记录的最大个数后就不再记录 */
    if (ulStateNum < NAS_ERR_LOG_MAX_CSFB_MT_STATE_RECORD_NUM)
    {
        pstStateInfo = &(pstCsfbMtInfo->astStateInfo[ulStateNum]);
        pstStateInfo->enCsfbMtState = enCsfbMtState;
        pstStateInfo->ulMmState     = Mm_GetState();
        pstStateInfo->ulCause       = ulCause;
        pstStateInfo->ulTick        = VOS_GetTick();
    }

    NAS_MML_AddCsfbMtRecordStateNum();

    return;
}


VOS_UINT32 NAS_MM_GetRrcPidFromCurrRatType(
    VOS_UINT32                         *pulPid
)
{
    VOS_UINT32                          ulRet;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;

    /* 初始化 */
    enCurrNetRatType = NAS_MML_GetCurrNetRatType();

    switch(enCurrNetRatType)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
            *pulPid = UEPS_PID_GAS;
            ulRet   = VOS_OK;
            break;

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            *pulPid = WUEPS_PID_WRR;
            ulRet   = VOS_OK;
            break;

        default:
            ulRet   = VOS_ERR;
            break;
    }

    return ulRet;
}


VOS_UINT8 NAS_MM_IsLauRejNeedRetry(
    VOS_UINT8                           ucCause
)
{
    NAS_MML_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU     *pstLauRejCfg = VOS_NULL_PTR;
    VOS_UINT8                                               ucIsCurCauseInNvCauseList;
    VOS_UINT32                                              i;

    pstLauRejCfg                = NAS_MML_GetLauRejNoRetryWhenCmSrvExistCfgInfo();
    ucIsCurCauseInNvCauseList   = VOS_FALSE;

    /* 测试卡时需要继续尝试 */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_TRUE;
    }

    /* 查找当前原因值是否在NV配置的原因值列表中 */
    for (i=0; i < pstLauRejCfg->ucLauRejCauseNum; i++)
    {
        if (ucCause == pstLauRejCfg->aucLauRejCause[i])
        {
            ucIsCurCauseInNvCauseList   = VOS_TRUE;
            break;
        }
    }


    /* 如果业务存在时，并且原因值在NV列表中，并且尝试次数已经达到NV中配置的次数，不需要继续尝试 */
    if ((VOS_TRUE == NAS_MML_GetCmServiceSetupFlg())
     && (VOS_TRUE == ucIsCurCauseInNvCauseList)
     && (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt >= pstLauRejCfg->ucLauRejTimes))
    {
        return VOS_FALSE;
    }

    /* 如果是漫游网络被拒不需要尝试的NV激活，不需要再尝试 */
    if (VOS_TRUE == NAS_MML_IsRoamingRejectNoRetryFlgActived(ucCause))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;

}


VOS_VOID NAS_MM_ConvertCallStatusToTransactionStatus(
    MMCC_CALL_STATUS_ENUM_UINT8         enCallStatus,
    RRMM_TRANSACTION_STATUS_ENUM_UINT8 *penTransStatus
)
{
    *penTransStatus = RRMM_TRANSACTION_FAIL;

    if (MNCC_CALL_STATUS_SETUP_SUCC == enCallStatus)
    {
        *penTransStatus = RRMM_TRANSACTION_CONNECTION_EST_SUCC;
    }

    return;
}


VOS_VOID NAS_MM_UpdateCallStatus_RcvCcEstReq(
    MMCC_EST_REQ_STRU                   *pstEstReq
)
{
    /* 第一次发起呼叫(不是重拨时),先默认为gu下的呼叫，
       如果后续是发给LMM的，在给LMM发送csfb start时会更新该标志
    */

    if (VOS_FALSE == pstEstReq->ucRedialFlg)
    {

        NAS_NORMAL_LOG(WUEPS_PID_MM,
        "NAS_MM_UpdateCallStatus_RcvCcEstReq: Not Redail call, Set CellNotSupportCsmoFlg to FALSE");
        NAS_MML_SetCellNotSupportCsmoFlg(VOS_FALSE);

        if (MMCC_EMERGENCY_CALL == pstEstReq->ulCallType)
        {
            NAS_MML_SetMoCallStatus(NAS_MML_MO_EMC_CALL_SETUP_START);
        }
        else
        {
            NAS_MML_SetMoCallStatus(NAS_MML_MO_NORMAL_CALL_SETUP_START);
        }

    }

    return;
}


VOS_VOID NAS_MM_UpdateCallStatus_RcvCallStatusNty(
    MMCC_CALL_STATUS_ENUM_UINT8         enCallStatus
)
{
    NAS_MML_MO_CALL_STATUS_ENUM_UINT8   enOldMoCallStatus;

    enOldMoCallStatus   = NAS_MML_GetMoCallStatus();

    /* 更新主叫标志 */
    switch (enOldMoCallStatus)
    {
        case NAS_MML_CSFB_MO_NORMAL_CALL_SETUP_START:
            if (MNCC_CALL_STATUS_SETUP_SUCC == enCallStatus)
            {
                NAS_MML_SetMoCallStatus(NAS_MML_CSFB_MO_NORMAL_CALL_SETUP_SUCC);
            }
            else
            {
                NAS_MML_SetMoCallStatus(NAS_MML_CSFB_MO_NORMAL_CALL_SETUP_FAIL);
            }
            break;

        case NAS_MML_CSFB_MO_EMC_CALL_SETUP_START:
            if (MNCC_CALL_STATUS_SETUP_SUCC == enCallStatus)
            {
                NAS_MML_SetMoCallStatus(NAS_MML_CSFB_MO_EMC_CALL_SETUP_SUCC);
            }
            else
            {
                NAS_MML_SetMoCallStatus(NAS_MML_CSFB_MO_EMC_CALL_SETUP_FAIL);
            }
            break;

        case NAS_MML_MO_NORMAL_CALL_SETUP_START:
            if (MNCC_CALL_STATUS_SETUP_SUCC == enCallStatus)
            {
                NAS_MML_SetMoCallStatus(NAS_MML_MO_NORMAL_CALL_SETUP_SUCC);
            }
            else
            {
                NAS_MML_SetMoCallStatus(NAS_MML_MO_NORMAL_CALL_SETUP_FAIL);
            }
            break;

        case NAS_MML_MO_EMC_CALL_SETUP_START:
            if (MNCC_CALL_STATUS_SETUP_SUCC == enCallStatus)
            {
                NAS_MML_SetMoCallStatus(NAS_MML_MO_EMC_CALL_SETUP_SUCC);
            }
            else
            {
                NAS_MML_SetMoCallStatus(NAS_MML_MO_EMC_CALL_SETUP_FAIL);
            }
            break;

        default:
            break;
    }

    return;

}


VOS_VOID NAS_MM_UpdateSsStatus_RcvSsStatusNty(
    MMSS_STATUS_ENUM_UINT8              enSsStatus
)
{

    NAS_MML_MO_SS_STATUS_ENUM_UINT8     enOldMoSsStatus;

    enOldMoSsStatus = NAS_MML_GetMoSsStatus();

    /* 更新MO标志 */
    switch (enOldMoSsStatus)
    {
        case NAS_MML_CSFB_MO_SS_SETUP_START:
            if (SSA_SS_STATUS_SETUP_SUCC == enSsStatus)
            {
                NAS_MML_SetMoSsStatus(NAS_MML_CSFB_MO_SS_SETUP_SUCC);
            }
            else
            {
                NAS_MML_SetMoSsStatus(NAS_MML_CSFB_MO_SS_SETUP_FAIL);
            }
            break;

        case NAS_MML_MO_NORMAL_SS_SETUP_START:
            if (SSA_SS_STATUS_SETUP_SUCC == enSsStatus)
            {
                NAS_MML_SetMoSsStatus(NAS_MML_MO_NORMAL_SS_SETUP_SUCC);
            }
            else
            {
                NAS_MML_SetMoSsStatus(NAS_MML_MO_NORMAL_SS_SETUP_FAIL);
            }
            break;

        default:
            break;
    }

    return;
}


VOS_VOID NAS_MM_ConvertSsStatusToTransactionStatus(
    MMSS_STATUS_ENUM_UINT8              enSsStatus,
    RRMM_TRANSACTION_STATUS_ENUM_UINT8 *penTransStatus
)
{
    *penTransStatus = RRMM_TRANSACTION_FAIL;

    if (SSA_SS_STATUS_SETUP_SUCC == enSsStatus)
    {
        *penTransStatus = RRMM_TRANSACTION_CONNECTION_EST_SUCC;
    }

    return;
}


VOS_UINT32 NAS_MM_IsNeedLauFirst_CsfbMoEmcExist(VOS_VOID)
{
    VOS_UINT32                          ulLaiChangeFlag;
    VOS_UINT32                          ulCsRestrictRegFlg;

    ulLaiChangeFlag     = NAS_MML_IsCsLaiChanged();
    ulCsRestrictRegFlg  = NAS_MML_GetCsRestrictRegisterFlg();

    /* 满足以下条件时，CSFB MO EMC需要先做LAU，再处理紧急呼:
        1. 紧急呼叫csfb到gu后LAI改变先进行lau的NV项打开
        2. LAI发生变化
        3. CS域不受限
    */

    if ((VOS_TRUE == NAS_MML_GetCsfbEmgCallLaiChgLauFirstFlg())
     && (VOS_TRUE == ulLaiChangeFlag)
     && (VOS_FALSE == ulCsRestrictRegFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_VOID NAS_MM_SndMmcCsRegResultInd_CsfbMoEmcExist(VOS_VOID)
{
    VOS_UINT32                          ulLaiChangeFlag;
    VOS_UINT32                          ulCsRestrictRegFlg;

    ulLaiChangeFlag     = NAS_MML_IsCsLaiChanged();
    ulCsRestrictRegFlg  = NAS_MML_GetCsRestrictRegisterFlg();

    /* 紧急呼CSFB到GU,需要做LAU时，不上报CS域注册状态，等注册结束时上报真实的注册状态 */
    if (VOS_TRUE == NAS_MM_IsNeedLauFirst_CsfbMoEmcExist())
    {
        return;
    }

    /* CS域受限直接上报注册结果为access bar */
    if (VOS_TRUE == ulCsRestrictRegFlg)
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);

    }
    /* LAI未发生改变时，update status状态是updated，可以直接报注册成功，因为该LAI是last succ lai */
    else if ((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
          && (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
          && (VOS_FALSE == ulLaiChangeFlag))
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_SUCCESS,
                                    NAS_MML_REG_FAIL_CAUSE_NULL);

    }
    /* NV项定制导致的不做LAU，上报注册结果为异系统成功，MMC会报之前的CS域服务状态和注册状态 */
    else if (VOS_FALSE == NAS_MML_GetCsfbEmgCallLaiChgLauFirstFlg())
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_SUCCESS,
                                    NAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC);

    }
    else
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_SUCCESS,
                                    NAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC);
    }

    return;
}



VOS_VOID NAS_MM_ProcT3213AttemptCounter(
    VOS_UINT32                          ulT3213Status
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRat;
    VOS_UINT32                          ucIsCampLaiChange;

    enCurrNetRat = NAS_MML_GetCurrNetRatType();
    ucIsCampLaiChange = NAS_MML_IsCampLaiInfoChanged();

    /* GSM下T3213运行时，如果LAI改变，发起Lau后MM的状态变为WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING，此时增加T3213 Attempt Counter */
    if ((NAS_MML_NET_RAT_TYPE_GSM                 == enCurrNetRat)
     && (VOS_TRUE                                 == ucIsCampLaiChange)
     && (MM_TIMER_RUNNING                         == ulT3213Status)
     && (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == g_MmGlobalInfo.ucState))
    {
        g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt++;
    }

    return;
}


VOS_VOID NAS_MM_ProcLuAttemptCounter(RRC_NAS_EST_RESULT_ENUM_UINT32 enEstResult)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRat;
    VOS_UINT8                           ucTrigLauOnceFlg;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;

    enCurrUtranMode           = NAS_UTRANCTRL_GetCurrUtranMode();
    enCurrNetRat              = NAS_MML_GetCurrNetRatType();
    ucTrigLauOnceFlg          = NAS_MML_GetPsRegFailMaxTimesTrigLauOnceFlg();

    if ((NAS_MML_NET_RAT_TYPE_WCDMA == enCurrNetRat)
     && (VOS_TRUE == ucTrigLauOnceFlg)
     && (MM_CONST_NUM_5 == g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt))
    {
        if ((RRC_EST_RANDOM_ACCESS_REJECT == enEstResult)
         && (NAS_UTRANCTRL_UTRAN_MODE_FDD == enCurrUtranMode))
        {
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_4;
            return;
        }

        if ((RRC_EST_RJ_TIME_OUT == enEstResult)
         && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enCurrUtranMode))
        {
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_4;
            return;
        }
    }

    /* NO_RF时不累加 */
    if (RRC_EST_RJ_NO_RF != enEstResult)
    {
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt++;
    }

    return;
}



VOS_VOID NAS_MM_ComProcPsRandomAccessFailCnt(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enRegFailCause,
    VOS_UINT32                          ulRegAttemptCounter
)
{
    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        if (NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL_RANDOM_ACCESS_REJECT != enRegFailCause)
        {
            g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt = 0;
        }
        else
        {
            /* RAI改变时，GMM模块会重置Rau/Attach Attempt Counter，此时也需要重置ucPsEstCnfFailCnt
            *  但是，重置的时候没有通知MM模块，之后发起Rau/Attach，如果建链失败则ulRegCounter为1，
            *  此时，同步更新全局变量ucPsEstCnfFailCnt的值为1
            */
            if (MM_CONST_NUM_1 == ulRegAttemptCounter)
            {
                g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt = MM_CONST_NUM_1;
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt++;
            }
        }
    }

    return;
}


VOS_VOID NAS_MM_ProcLauEstCnfNoRf(VOS_VOID)
{
    MM_LAI_STRU                                            *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstCampLaiInfo  = VOS_NULL_PTR;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
    }

    NAS_MM_ProcLuAttemptCounter(RRC_EST_RJ_NO_RF);

    if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
    {
        enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
        if ((VOS_FALSE == NAS_MML_IsCsLaiChanged())
            && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
        {                                                                       /* 如果LAI不变,且更新状态为U1的时候         */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录前状态                               */
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;
            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E32:INFO: MmServiceState is MM_NORMAL_SERVICE");

            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);  /* 向MMC发送MMCMM_LU_RESULT_IND             */

            Mm_ComNasInfoSav(MM_STATUS_ATTACHED,
                             NAS_MML_GetSimCsSecurityCksn());
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E32:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
            Mm_TimerStart(MM_TIMER_T3211);                                      /* 启动T3211                                */
            g_T3211Flag = 1;
        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E32:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            /* 在U2状态，保存当前的LAI信息 */
            pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
            pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

            pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
            pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
            pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            /* 进U2的公共处理 */
            Mm_ComToU2Handle();

            Mm_TimerStart(MM_TIMER_T3211);                                      /* 启动T3211                                */
        }
    }
    else
    {
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E32:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

        /* 在U2状态，保存当前的LAI信息 */
        pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
        pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

        pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
        pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
        pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

        NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

        NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

        /* 进U2的公共处理 */
        Mm_ComToU2Handle();

        NAS_MM_StartT3212Timer(NAS_MM_ConvertLauEstCnfRsltToT3212StartScean(RRC_EST_RJ_NO_RF));
    }

    if ( VOS_FALSE == NAS_MM_NotifyBufferedServiceRRConnNotExist() )
    {
         Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                          /* RR连接不存在                             */

         NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }

    Mm_ComCheckDelayMmConn(MM_FALSE);

    return;
}



VOS_VOID NAS_MM_ConvertToMmlSessionType(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8   enMmSessionType,
    NAS_MML_SESSION_TYPE_ENUM_UINT8  *penMmlSessionType
)
{
    switch(enMmSessionType)
    {
        case RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CALL:
            *penMmlSessionType = NAS_MML_SESSION_TYPE_CS_MO_NORMAL_CALL;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MO_EMERGENCY_CALL:
            *penMmlSessionType = NAS_MML_SESSION_TYPE_CS_MO_EMERGENCY_CALL;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MO_SS:
            *penMmlSessionType = NAS_MML_SESSION_TYPE_CS_MO_SS;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MO_SMS:
            *penMmlSessionType = NAS_MML_SESSION_TYPE_CS_MO_SMS;
            break;

        default:
            *penMmlSessionType = NAS_MML_SESSION_TYPE_BUTT;
            break;
    }

    return;
}


NAS_MMCM_REL_CAUSE_ENUM_UINT32 NAS_MM_GetMmCmRelCause(VOS_VOID)
{
    NAS_MMCM_REL_CAUSE_ENUM_UINT32         enRelCause;

    switch(g_MmGlobalInfo.ucState)
    {
        case IMSI_DETACH_PENDING:
            enRelCause = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH;
            break;

        case MM_IDLE_PLMN_SEARCH:
            enRelCause = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_SEARCHING_NETWORK;
            break;

        case MM_IDLE_ATTEMPTING_TO_UPDATE:
            enRelCause = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_ATTEMPTING_TO_UPDATE;
            break;

        case LOCATION_UPDATING_PENDING:
            enRelCause = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_ATTEMPTING_TO_UPDATE;
            break;

        case MM_WAIT_FOR_ATTACH:
            enRelCause = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_ATTEMPTING_TO_UPDATE;
            break;

        case MM_INTER_RAT_CHANGE:
            enRelCause = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_INTER_RAT_SYSTEM_CHANGE;
            break;

        case MM_IDLE_LIMITED_SERVICE:
            enRelCause = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE;
            break;

        case MM_STATE_NULL:
            enRelCause = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH;
            break;

        case MM_IDLE_NO_IMSI:
            enRelCause = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH;
            break;

        case MM_IDLE_NO_CELL_AVAILABLE:
            enRelCause = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE;
            break;

        case WAIT_FOR_RR_CONNECTION_IMSI_DETACH:
            enRelCause = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH;
            break;

        case IMSI_DETACH_INITIATED:
            enRelCause = NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH;
            break;

        default:
            enRelCause = (VOS_UINT32)NAS_MMCM_REL_CAUSE_BUTT;
            break;
    }

    return enRelCause;
}

/*lint -restore */


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

