/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : MM_CellProc3.c
  Description  : MM公共处理
  Function List:

  History:
   1.日    期   : 2009年09月23日
     作    者   : x00115505
     修改内容   : AT2D14632,开机注册失败，查询CREG返回1
  2.日    期   : 2009年11月03日
     作    者   : x00115505
     修改内容   : 问题单号：AT2D15222,接入阻塞还可以注册
  3.日    期   : 2009年11月09日
     作    者   : s46746
     修改内容   : 问题单号：AT2D15401,CS关机Detach保护时间太短，没有等到网络释放连接就超时主动释放了

  4.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级

  5.日    期   : 2010年3月23日
    作    者   : zhoujun /z40661
    修改内容   : AMR速率调整
  6.日    期   : 2010年5月3日
    作    者   : x00115505
    修改内容   : 问题单号：AT2D18886,MM处理WRR发过来的连接建立结果有误
  7.日    期   : 2010年11月22日
    作    者   : h44270
    修改内容   : DTS201011700067,没有处理系统消息，导致电话挂断后，没有发起LAU。
*******************************************************************************/

#include        "MM_Inc.h"
#include        "GmmMmInterface.h"
#include        "NasMmlCtx.h"
#include        "NasMmSndOm.h"


 /* Added by l00208543 for V9R1 STK升级, 2013-07-10, begin */
#include "NasStkInterface.h"
 /* Added by l00208543 for V9R1 STK升级, 2013-07-10, end */
/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-22, begin */
#include "NasMmEcall.h"
/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-22, end */
#include "NasUtranCtrlInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:luojian 107747;检视人:sunshaohua65952;原因:LOG方案设计需要*/
#define    THIS_FILE_ID        PS_FILE_ID_MM_CELLPROC3_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/
extern VOS_UINT8 GMM_IsGasCellReselect(VOS_VOID);

/*lint -save -e958 */

/*******************************************************************************
  MODULE   : Mm_Cell_S10_E66
  FUNCTION : 在MM CONNECTION ACTIVE状态下收到MMSS_REL_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-24  新版作成

     2.日    期   : 2011年7月14日
       作    者   : zhoujun 40661
       修改内容   : 更新MML_CTX中的业务存在状态
     3.日    期   : 2012年04月03日
       作    者   : l65478
       修改内容   : DTS2012032702913:在CS存在呼叫时收到SS的释放请求清除了CS连接标志
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E66(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    if (MM_FALSE == Mm_RcvSsRelReq(pRcvMsg))
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */

        /*lint -e701*/
        if ((MM_CONST_NUM_7 > g_MmSsRelReq.ulTi)
            && (MM_CONST_NUM_0 !=
            (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
            & (0x01 << g_MmSsRelReq.ulTi))))
        {                                                                       /* TI小于7并且该MM连接存在                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] &=
                ~(VOS_UINT32)(0x01 << g_MmSsRelReq.ulTi);                       /* 清除该标志位                             */
        }
        if ((MM_CONST_NUM_7 < g_MmSsRelReq.ulTi)
            && (MM_CONST_NUM_15 > g_MmSsRelReq.ulTi)
            && (MM_CONST_NUM_0 !=
            (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
            & (0x01 << (g_MmSsRelReq.ulTi - 8)))))
        {                                                                       /* TI小于7并且该MM连接存在                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] &=
                ~(VOS_UINT32)(0x01 << (g_MmSsRelReq.ulTi - 8));                 /* 清除该标志位                             */
        }
        if ((MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0])
          && (MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1])
          && (MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0])
          && (MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1])
          && (MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0])
          && (MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]))
        {                                                                       /* 没有MM连接存在                           */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* 进入空闲的状态                           */
            Mm_ComSaveProcAndCauseVal(MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);      /* MM连接流程                               */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E66:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */

            NAS_MML_SetCsServiceConnStatusFlg(VOS_FALSE);
        }


        /*lint +e701*/

    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S12_E66
  FUNCTION : 在WAIT FOR RR CONNECTION (MM CONNECTION)状态下收到MMSS_REL_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  s46746      06-11-21  Create for A32D07452
     2.日    期   :2013年8月13日
       作    者   :z00161729
       修改内容   :DTS2013081207431:mm挂起状态收到cc的t303超时abort消息，需要缓存，收到resume ind时再处理
     3.日    期   : 2014年5月22日
       作    者   : z00161729
       修改内容   : DTS2014050601476:L打电话重定向到g过程中电话挂断，mm缓存cc abort，g查询csfb状态是存在，lau结束后没有启动自主FR流程到L
     4.日    期   : 2014年6月13日
       作    者   : w00242748
       修改内容   : DSDS 新特性
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E66(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                       )
{
    if (MM_FALSE == Mm_RcvSsRelReq(pRcvMsg))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E66:WARNING: Rcv SS Rel Req error.");
    }
    else
    {
        if ( (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI == g_MmSsRelReq.ulTi )
          && (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg))
        {
            /* 终止的MM连接建立是正在建立的             */
            if (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat == NAS_MML_GetCurrNetRatType())
            {
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);

                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* 返回到接收到建立MM连接请求时的状态       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM连接流程                               */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E80:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */
            }
            else
            {
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            }

            Mm_TimerStop( MM_TIMER_PROTECT_SIGNALLING );
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* 清除正在建立的MM连接的标志               */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;

            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */

#if (FEATURE_ON == FEATURE_LTE)

            /* 当前存在补充业务的CSFB流程，则清空CSFB存在标志 */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
            }
#endif
        }
        else
        {
            if (( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
             && ( g_MmSsRelReq.ulTi == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;

#if (FEATURE_ON == FEATURE_LTE)
                /* 当前存在补充业务的CSFB流程，则清空CSFB存在标志 */
                if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
                {
                    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                }
#endif
            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();
        }

    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S24_E13
  FUNCTION : 在LOCATION UPDATE REJECTED状态下,收到MMCMM_NETWORK_DETACH_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇    2004.03.12  新版作成
     2.日    期   : 2014年4月2日
       作    者   : w00176964
       修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
*******************************************************************************/

VOS_VOID Mm_Cell_S24_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU       *pstNetWkDetachInd;
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    if (MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg))
    {
        return;
    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    g_MmGlobalInfo.ucProc = MM_NET_DETACH_PROC;                                 /* 记录当前的流程                           */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E13:INFO: MmServiceState is MM_NET_DETACH_PROC");

    if (GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType)
    {
        ;                                                                       /* 空处理                                   */
    }
    else if (GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType)
    {
        Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                  NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);                     /* 记录流程和原因值                         */
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
    }
    else
    {
        switch (pstNetWkDetachInd->ulDetachCause)
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                     (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);/* 记录流程和原因值                         */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E13:INFO: MmServiceState is MM_NO_IMSI");
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
            Mm_ComToNoImsiHandle();                                             /* 调用删除IMSI的公共处理                   */
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录前状态                               */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* 设置类似于B模式的全局量                  */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E13:INFO: MmLikeB is MM_TRUE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                     (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);/* 记录流程和原因值                         */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            break;
        default:
            break;
        }
    }

}

/*******************************************************************************
  Module:   Mm_Cell_S3_E14
  Function: 在MM IDLE NORMAL SERVICE状态下,
                收到GMMMM_GMM_ACTION_RESULT_IND的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.张志勇     2004.03.10  新版做成
      2.日    期   : 2011年7月26日
        作    者   : l00130025
        修改内容   : V7R1 PhaseII阶段调整，删除UserDelay标志，由MMC处理
      3.日    期   : 2011年11月22日
        作    者   : w00166186
        修改内容   : DTS2011111003960,PS业务建链不成功，原因值32位强制转换为8位出错
      4.日    期   : 2013年2月4日
        作    者   : w00176964
        修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
      5.日    期   : 2013年06月04日
        作    者   : s46746
        修改内容   : SS FDN&Call Control项目，PS被原因值12拒绝,CS注册状态需要更新为0
      6.日    期   : 2013年11月29日
        作    者   : w00242748
        修改内容   : DTS2013112612348:CS被拒原因值15后释放链接，回LIMIT SERVICE
                     PS被拒原因值12，此时不发起搜网。
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E14(VOS_VOID* pMsg)
{
    VOS_UINT8                                ucActionType = MM_NULL_PROC;
    GMMMM_GMM_ACTION_RESULT_IND_STRU        *pstGmmActionRstInd;
    VOS_UINT8                                ucState;

    ucState                             = g_MmGlobalInfo.ucState;

    if (MM_FALSE == Mm_RcvGmmGmmActionResultInd(pMsg))
    {
        return;
    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstGmmActionRstInd = (GMMMM_GMM_ACTION_RESULT_IND_STRU*)pMsg;

    if (GMMMM_ACTION_FAILURE == pstGmmActionRstInd->enActionResult)
    {
        switch (pstGmmActionRstInd->enGmmActionType)
        {
        case GMMMM_ACTION_RAU:
            ucActionType = MM_GMM_RAU_PROC;
            break;
        case GMMMM_ACTION_ATTACH:
            ucActionType = MM_GMM_ATTACH_PROC;
            break;
        case GMMMM_ACTION_SR:
            ucActionType = MM_GMM_SR_PROC;
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S3_E14:WARNING: ulGmmActionType Abnormal");
            break;
        }

        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, begin */
        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, end */
        {                                                                       /* 如果为A+I,且不是类似B或A+II处理的场合    */
            if (MM_GMM_SR_PROC == ucActionType)
            {
                Mm_ComGmmSrCauseHandle(pstGmmActionRstInd->enCause);   /* 调用SR过程原因值的公共处理               */
            }
        }
        else
        {                                                                       /* 如果为非A+I模式的场合                    */
            if (MM_NULL_PROC != ucActionType)
            {
                Mm_ComCauseHandleAllProc(ucActionType,
                                         pstGmmActionRstInd->enCause); /* 调用原因值的处理                         */

                if ( (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == pstGmmActionRstInd->enCause)
                  && ( (MM_IDLE_NORMAL_SERVICE == ucState)
                    || (MM_IDLE_ATTEMPTING_TO_UPDATE == ucState) ) )
                {
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                            MM_MMC_LU_RESULT_FAILURE,
                            NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS);
                }
            }
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S24_E14
  Function: 在LOCATION UPDATE REJECTED状态下,
                收到GMMMM_GMM_ACTION_RESULT_IND的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.10  新版做成
      2.日    期   : 2011年03月31日
        作    者   : c00173809
        修改内容   : 问题单号:DTS2011032802664,UE驻留VPLMN发起BG搜,驻留高优先级
                     网络,COMBINED RAU PS成功,CS拒绝原因15,没搜当前网络.
      3.日    期   : 2012年11月30日
        作    者   : l00167671
        修改内容   : 问题单号:dts2012112800374,W下CS域先被拒绝原因值15，PS域被拒
                     15后，MM进入NORMAL SERVICE状态
      4.日    期   : 2014年4月2日
        作    者   : w00176964
        修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
*******************************************************************************/

VOS_VOID Mm_Cell_S24_E14(VOS_VOID* pMsg)
{
    VOS_UINT8                               ucActionType = MM_NULL_PROC;
    GMMMM_GMM_ACTION_RESULT_IND_STRU       *pstGmmActionRstInd;
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    if (MM_FALSE == Mm_RcvGmmGmmActionResultInd(pMsg))
    {
        return;
    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstGmmActionRstInd = (GMMMM_GMM_ACTION_RESULT_IND_STRU*)pMsg;

    if (GMMMM_ACTION_FAILURE == pstGmmActionRstInd->enActionResult)
    {
        switch (pstGmmActionRstInd->enGmmActionType)
        {
        case GMMMM_ACTION_RAU:
            ucActionType = MM_GMM_RAU_PROC;
            break;
        case GMMMM_ACTION_ATTACH:
            ucActionType = MM_GMM_ATTACH_PROC;
            break;
        case GMMMM_ACTION_SR:
            ucActionType = MM_GMM_SR_PROC;
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S24_E14:WARNING: ulGmmActionType Abnormal");
            break;
        }
        if (MM_NULL_PROC != ucActionType)
        {
            switch (pstGmmActionRstInd->enCause)
            {
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
                Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
                Mm_TimerStop(MM_TIMER_T3210);                               /* 停止T3210                                */
                Mm_ComSaveProcAndCauseVal(ucActionType,
                                          (VOS_UINT8)pstGmmActionRstInd->enCause); /* 记录流程和原因值                         */
                g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;               /* 设置服务状态                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E14:INFO: MmServiceState is MM_NO_IMSI");
                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
                Mm_ComToNoImsiHandle();                                     /* 调用删除IMSI的公共处理                   */
                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E14:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
                if (MM_GMM_ATTACH_PROC == ucActionType)
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
                    Mm_TimerStop(MM_TIMER_T3210);                               /* 停止T3210                                */
                    Mm_ComSaveProcAndCauseVal(ucActionType,
                                       (VOS_UINT8)pstGmmActionRstInd->enCause);   /* 记录流程和原因值                         */
                    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;               /* 设置服务状态                             */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E14:INFO: MmServiceState is MM_NO_IMSI");
                    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
                    Mm_ComToNoImsiHandle();                                     /* 调用删除IMSI的公共处理                   */
                    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
                    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E14:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* 设置类似于B模式的全局量                  */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E14:INFO: MmLikeB is MM_TRUE");
                break;
            case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
                Mm_ComSaveProcAndCauseVal(ucActionType,
                                       (VOS_UINT8)pstGmmActionRstInd->enCause);   /* 记录流程和原因值                         */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E14:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                break;

            case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
                /* 在LOCATION UPDATE REJECTED状态下收到PS域拒绝原因值15时按照CS域被拒的原因值处理 */
                break;

            default:
                break;
            }
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S24_E16
  Function: 在LOCATION UPDATE REJECTED状态下,
                收到MMCMM_AUTHENTICATON_FAILURE_IND的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.12  新版做成
*******************************************************************************/

VOS_VOID Mm_Cell_S24_E16(VOS_VOID* pMsg)
{
    if (MM_FALSE == Mm_RcvGmmAuthFailInd(pMsg))
    {
        return;
    }

    Mm_ComSaveProcAndCauseVal(MM_AUTH_FAIL_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);            /* 记录流程和原因值                         */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                               /* 设置服务状态                             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E16:INFO: MmServiceState is MM_NO_IMSI");
    Mm_ComToNoImsiHandle();                                                     /* 调用删除IMSI的公共处理                   */
    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E16:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
}

/*******************************************************************************
  Module:   Mm_Cell_S25_E16
  Function: 在WAIT FOR RR CONNECTION (IMSI DETACH)状态下,
                            收到GMMMM_AUTHENTICATON_FAILURE_IND的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.12  新版做成
      2. 日    期   : 2007年08月19日
         作    者   : luojian id:60022475
         修改内容   : 根据问题单号：A32D12706
       3.日    期   : 2013年05月15日
         作    者   : s46746
         修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
*******************************************************************************/
VOS_VOID Mm_Cell_S25_E16(VOS_VOID* pMsg)
{
    if (MM_FALSE == Mm_RcvGmmAuthFailInd(pMsg))
    {
        return;
    }

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    Mm_ComToNoImsiHandle();

    Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
    Mm_ComSetMmState(IMSI_DETACH_INITIATED);


    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E16:NORMAL: STATUS is MM_STATE_NULL");
}
/*******************************************************************************
  Module:   Mm_Cell_S26_E16
  Function: 在IMSI DETACH INITIATED状态下,
                            收到GMMMM_AUTHENTICATON_FAILURE_IND的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.12  新版做成
*******************************************************************************/
VOS_VOID Mm_Cell_S26_E16(VOS_VOID* pMsg)
{
    if (MM_FALSE == Mm_RcvGmmAuthFailInd(pMsg))
    {
        return;
    }

    Mm_ComToNoImsiHandle();
}
/*******************************************************************************
  Module:   Mm_Cell_S3_E22
  Function: 在MM IDLE NORMAL SERVICE状态下,收到MMCMM_DETACH_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2004.03.12  新版做成
  2. 张志勇        2005.01.27  007037 for MM
  3.  日    期   : 2008年09月03日
      作    者   : l00130025
      修改内容   : 问题单号：AT2D05403,mm注册状态修改
  4.日    期   : 2011年7月26日
    作    者   : h44270
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  5.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  6. 日    期   : 2012年1月12日
     作    者   : w00166186
     修改内容   : DTS2011122704039:开机搜网后CS注册被拒#12,PS注册被拒#14，在ON
                   PLMN状态，服务域被设置为不支持MM需要将服务域不支持信息通知给MMC.
  7. 日    期   : 2012年3月15日
     作    者   : w00166186
     修改内容   : V7R1 C50 CSFB&PPAC&ETWS&ISR开发
   8.日    期   : 2013年2月4日
     作    者   : w00176964
     修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
   9.日    期   : 2013年05月15日
     作    者   : s46746
     修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
   10.日    期   : 2013年6月18日
     作    者   : w00167002
     修改内容  : SVLTE 和usim接口调整修改
   11.日    期   : 2013年11月11日
     作    者   : l65478
     修改内容  : DTS2013110800070:3方后台在搜网过程中下发了USSD业务,导致CS业务异常
  12.日    期   : 2014年6月13日
     作    者   : w00242748
     修改内容   : DSDS 新特性
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;



    /* 当前是否由GMM处理用户发起的detach */
    if ( VOS_TRUE == NAS_MM_IsNeedGmmProcUserDetach() )
    {
        g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;
        return;
    }

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        Mm_TimerStop(MM_TIMER_T3212);                                           /* 停止T3212                                */
        if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
        {
            if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
            {
                NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);                         /* 设置禁止注册CS域的标识                   */

                g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;              /* 设置服务状态                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E22:INFO: MmServiceState is MM_DETACHED");
                Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                                 NAS_MML_GetSimCsSecurityCksn());     /* 设置MM信息                               */

                /* 判断等待标志是否存在，如果存在则发送MMCGMM_DETACH CNF */
                if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                             & MM_WAIT_CS_DETACH))
                {
                    NAS_MM_SndMmcDetachCnf(MM_DETACHED);
                    /* 清除等待标志 */
                    g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
                }

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E22:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");

            }
            else
            {
                g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;          /* 设置DETACH类型                           */

                NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;

                Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);

                Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                        /* 填写消息,发送消息                        */

                Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                     /* 启动保护TIMER                            */

                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E22:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
                g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;                  /* 设置服务状态                             */
            }
        }
        else if (MM_STATUS_DETACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
        {
            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);                             /* 设置禁止注册CS域的标识                   */
            g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;                  /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E22:INFO: MmServiceState is MM_DETACHED");
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());         /* 设置MM信息                               */

            /* 判断等待标志是否存在，如果存在则发送MMCGMM_DETACH CNF */
            if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                         & MM_WAIT_CS_DETACH))
            {
                NAS_MM_SndMmcDetachCnf(MM_DETACHED);
                /* 清除等待标志 */
                g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
            }

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E22:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        }
        else
        {

        }
    }

}
/*******************************************************************************
  Module:   Mm_Cell_S4_E22
  Function: 在MM IDLE LIMITED SERVICE状态下,收到MMCMM_DETACH_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2004.03.12  新版做成
  2.  日    期   : 2008年09月03日
      作    者   : l00130025
      修改内容   : 问题单号：AT2D05403,mm注册状态修改
  3.日    期   : 2011年7月26日
    作    者   : h44270
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  4.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  5. 日    期   : 2012年1月12日
     作    者   : w00166186
     修改内容   : DTS2011122704039:开机搜网后CS注册被拒#12,PS注册被拒#14，在ON
                   PLMN状态，服务域被设置为不支持MM需要将服务域不支持信息通知给MMC.
  6. 日    期   : 2012年2月15日
     作    者   : w00166186
     修改内容   : CSFB&PPAC&ETWS&ISR 开发
  7.日    期   : 2012年12月25日
    作    者   : l00167671
    修改内容   : 问题单号DTS2012122509118，L下搜网打紧急呼时到W下搜到与上次注册相同的小区
                   先发起了LU
  8.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  9.日    期   : 2013年6月8日
    作    者   : w00167002
    修改内容   : V9R1_SVLTE:检视意见修改:nO CELL AVAILABLE状态时其实也不需要迁移状态
*******************************************************************************/
VOS_VOID Mm_Cell_S4_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*   pMmcDetachReq;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        Mm_TimerStop(MM_TIMER_T3212);                                           /* 停止T3212                                */
        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
        g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;                      /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E22:INFO: MmServiceState is MM_DETACHED");
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());             /* 设置MM信息                               */

        /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MM_DETACHED);
            /* 清除等待标志 */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);


        if ( MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState )
        {
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        }


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S4_E22:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
    }
}
/*****************************************************************************
 函 数 名  : Mm_Cell_S6_E22
 功能描述  : 在MM_IDLE_LOCATION_UPDATE_NEEDED状态收到DETACH REQ的处理
 输入参数  : VOS_VOID* pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月15日
   作    者   : w00166186
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Mm_Cell_S6_E22(VOS_VOID* pMsg)
{
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8                    enServiceStatus;

    enServiceStatus = NAS_MM_GetLauUptNeededCsSrvStatus();

    if ((VOS_FALSE == NAS_MML_GetCsRestrictRegisterFlg())
     || (MM_COM_SRVST_NORMAL_SERVICE == enServiceStatus))
    {
        Mm_Cell_S3_E22(pMsg);
    }
    else
    {
        Mm_Cell_S4_E22(pMsg);
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S8_E22
  Function: 在MM IDLE NO IMSI状态下,收到MMCMM_DETACH_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.12  新版做成
      2. 日    期   : 2012年1月12日
         作    者   : w00166186
         修改内容   : DTS2011122704039:开机搜网后CS注册被拒#12,PS注册被拒#14，在ON
                       PLMN状态，服务域被设置为不支持MM需要将服务域不支持信息通知给MMC.

      3.日    期   : 2013年6月21日
        作    者   : w00167002
        修改内容   : 如果当前卡无效，需要通知状态为NO IMSI
*******************************************************************************/
VOS_VOID Mm_Cell_S8_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*   pMmcDetachReq;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                           /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S8_E22:INFO: MmServiceState is MM_NO_IMSI");

        /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MM_NO_IMSI);
            /* 清除等待标志 */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }


        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

    }
}
/*******************************************************************************
  Module:   Mm_Cell_S9_E22
  Function: 在WAIT FOR OUTGOING MM CONNECTION状态下,收到MMCMM_DETACH_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.张志勇     2004.03.12  新版做成
  2.日    期   : 2008年09月03日
    作    者   : l00130025
    修改内容   : 问题单号：AT2D05403,mm注册状态修改
  3.日    期   : 2011年7月22日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  4.日    期   : 2011年7月26日
    作    者   : h44270
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  5.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  6. 日    期   : 2012年1月12日
     作    者   : w00166186
     修改内容   : DTS2011122704039:开机搜网后CS注册被拒#12,PS注册被拒#14，在ON
                   PLMN状态，服务域被设置为不支持MM需要将服务域不支持信息通知给MMC.
  7.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  8.日    期   : 2012年12月18日
    作    者   : l65478
    修改内容   : DTS2012121405450:释放连接原因值错误
  9.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
 10.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 11.日    期   : 2013年6月8日
    作    者   : w00167002
    修改内容   : V9R1_SVLTE:封装函数判别是否由GMM处理CS的DETACH。
 12.日    期   :2013年9月14日
    作    者   :z00161729
    修改内容  :DTS2013082903019:支持ss重发功能
 13.日    期   : 2014年6月13日
    作    者   : w00242748
    修改内容   : DSDS 新特性
 14.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;



    /* 当前是否由GMM处理用户发起的detach */
    if ( VOS_TRUE == NAS_MM_IsNeedGmmProcUserDetach() )
    {
        /* 停等待保护定时器 */
        Mm_TimerStop(MM_TIMER_T3218);

        /* 在鉴权过程中，则清除鉴权标志信息 */
        if ( MM_RCV_AUTH_CNF_FLG == (g_MmGlobalInfo.ucRcvAgentFlg & MM_RCV_AUTH_CNF_FLG) )
        {
            g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

            /* 停止保护定时器 */
            Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
        }

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

                Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
                Mm_ComSetMmState(IMSI_DETACH_PENDING);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E22:NORMAL: STATUS is IMSI_DETACH_PENDING");
        /* Deleted by s00217060 for K3V3 多模多天线特性, 2014-07-22, begin */
        /* Mm_SndMmcCmSvcInd在Mm_ComRelAllMmConn中上报 */
        /* Deleted by s00217060 for K3V3 多模多天线特性, 2014-07-22, end */

                if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
                {
                    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;
                }

        return;
    }

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        Mm_TimerStop(MM_TIMER_T3212);                                           /* 停止T3212                                */
        g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;                  /* 设置DETACH类型                           */

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        if ((MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
            || (MM_STATUS_ATTACHED !=
                        g_MmSubLyrShare.MmShare.ucCsAttachState))
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());         /* 设置MM信息                               */

            /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
            if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                         & MM_WAIT_CS_DETACH))
            {
                NAS_MM_SndMmcDetachCnf(MM_DETACHED);
                /* 清除等待标志 */
                g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
            }

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

            Mm_ComSaveProcAndCauseVal(MM_IMSI_DETACH, NAS_MML_REG_FAIL_CAUSE_NULL);       /* 记录流程和原因值                         */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E22:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动T3240                                */
        }
        else
        {
            NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));                  /* 填写MobileID                             */

            Mm_ComSetMmState(IMSI_DETACH_INITIATED);

            Mm_ComMsgImsiDetachIniSndOfDataReq(&Msg);                           /* 填写消息,发送消息                        */
            Mm_TimerStart(MM_TIMER_T3220);                                      /* 启动T3220                                */


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E22:NORMAL: STATUS is IMSI_DETACH_INITIATED");
        }

    }
}
/*******************************************************************************
  Module:   Mm_Cell_S12_E22
  Function: 在WAIT FOR RR CONNECTION (MM CONNECTION)状态下,收到MMCMM_DETACH_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2004.03.12  新版做成
  2.  张志勇     2005.01.27  007037 for MM
  3. 日    期   : 2008年09月03日
     作    者   : l00130025
     修改内容   : 问题单号：AT2D05403,mm注册状态修改
  4.日    期   : 2011年7月26日
    作    者   : h44270
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  5.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  6. 日    期   : 2012年1月12日
     作    者   : w00166186
     修改内容   : DTS2011122704039:开机搜网后CS注册被拒#12,PS注册被拒#14，在ON
                   PLMN状态，服务域被设置为不支持MM需要将服务域不支持信息通知给MMC.
  7.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
 8.日    期   : 2013年2月4日
   作    者   : w00176964
   修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
 9.日    期   : 2013年05月15日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
10.日    期   : 2013年6月5日
   作    者   : w00167002
   修改内容   : SVLTE:sunxibo检视意见修改，状态不是迁移到NO IMSI,迁移到LIMIT
                    SERVICE状态。
                2. 停止WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ状态的保护定时器;
                3. 如果当前的CS detach由GMM进行处理，则释放当前的链接，GMM收到GPRS
                   RESUME指示消息后，发起DETACH;
 11.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能
 12.日    期   : 2013年11月11日
    作    者   : l65478
    修改内容  : DTS2013110800070:3方后台在搜网过程中下发了USSD业务,导致CS业务异常
 13.日    期   : 2014年6月13日
    作    者   : w00242748
    修改内容   : DSDS 新特性
 14.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;


    /* 当前是否由GMM处理用户发起的detach */
    if ( VOS_TRUE == NAS_MM_IsNeedGmmProcUserDetach() )
    {
        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        }

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
        Mm_ComSetMmState(IMSI_DETACH_PENDING);

        /* Deleted by s00217060 for K3V3 多模多天线特性, 2014-07-22, begin */
        /* Mm_SndMmcCmSvcInd在Mm_ComRelAllMmConn中上报 */
        /* Deleted by s00217060 for K3V3 多模多天线特性, 2014-07-22, end */
        if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
        {
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;
        }

        return;
    }

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        Mm_TimerStop(MM_TIMER_T3212);                                           /* 停止T3212                                */
        if ((MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
            || (MM_STATUS_ATTACHED !=
                                g_MmSubLyrShare.MmShare.ucCsAttachState))
        {
            NAS_MM_LocalDetach();


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E22:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        }
        else
        {
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;              /* 设置DETACH类型                           */

            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

            if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
            {
                /* 继续等待建链结果 */
                return;
            }

            /* 停止WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ状态的保护定时器 */
            Mm_TimerStop(MM_TIMER_PROTECT_CC);

            NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;

            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);

            Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                            /* 填写消息,发送消息                        */

            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                         /* 启动保护TIMER                            */

            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E22:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S14_E22
  Function: 在WAIT FOR REESTABLISH（WAIT FOR EST_CNF）状态下,收到MMCMM_DETACH_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2004.03.12  新版做成
  2. 张志勇        2005.01.27  007037 for MM
  3. 日    期   : 2008年09月03日
     作    者   : l00130025
     修改内容   : 问题单号：AT2D05403,mm注册状态修改
  4.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  5. 日    期   : 2012年1月12日
     作    者   : w00166186
     修改内容   : DTS2011122704039:开机搜网后CS注册被拒#12,PS注册被拒#14，在ON
                   PLMN状态，服务域被设置为不支持MM需要将服务域不支持信息通知给MMC.
  6.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  7.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
  8.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态

  7.日    期   : 2013年6月5日
    作    者   : w00167002
    修改内容   : SVLTE:发起CS域的Detach,则需要启动保护定时器:SYSCFG触发的Detach的
                 保护时间为15s，cgcatt触发的Detach的时长为90s
                 2.sunxibo检视意见:Mm_Cell_S14_E22的状态当前没有信令链接，处理参考
                 Mm_Cell_S12_E22
                 3. 如果当前的CS detach由GMM进行处理，则释放当前的链接，GMM收到GPRS
                   RESUME指示消息后，发起DETACH;
  8.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能
  9.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;


    /* 当前是否由GMM处理用户发起的detach */
    if ( VOS_TRUE == NAS_MM_IsNeedGmmProcUserDetach() )
    {
        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        }

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
        Mm_ComSetMmState(IMSI_DETACH_PENDING);

        /* Deleted by s00217060 for K3V3 多模多天线特性, 2014-07-22, begin */
        /* Mm_SndMmcCmSvcInd在Mm_ComRelAllMmConn中上报 */
        /* Deleted by s00217060 for K3V3 多模多天线特性, 2014-07-22, end */

        if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
        {
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;
        }

        return;
    }

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {

        if ((MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
            || (MM_STATUS_ATTACHED !=
                         g_MmSubLyrShare.MmShare.ucCsAttachState))
        {
            NAS_MM_LocalDetach();

        }
        else
        {

            Mm_TimerStop(MM_TIMER_T3212);                                           /* 停止T3212                                */
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;                      /* 设置DETACH类型                           */

            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);


            /* 等建链成功后再发起IMSI DETACH */
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S0_E23
  Function: 在MM_NULL状态下,收到MMCMM_POWER_OFF_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2004.03.12  新版做成
  2. 日    期   : 2006年9月9日
     作    者   : sunxibo id:46746
     修改内容   : 根据问题单号：A32D05803
  3.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  4.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E23(VOS_VOID* pMsg)
{

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;
    }

    Mm_TimerStop(MM_TIMER_T3212);                                               /* 停止T3212                                */

    Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                     NAS_MML_GetSimCsSecurityCksn());                     /* 设置MM信息                               */

    Mm_SndMmcPowerOffCnf();                                                     /* 向MMC发送MMCMM_POWER_OFF_CNF             */

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);
    }

    Mm_ComSetMmState(MM_STATE_NULL);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E23:NORMAL: STATUS is MM_STATE_NULL");
}
/*******************************************************************************
  Module:   Mm_Cell_S3_E23
  Function: 在MM IDLE NORMAL SERVICE状态下,收到MMCMM_POWER_OFF_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2004.03.12  新版做成
  2.  张志勇        2005.01.27  007037 for MM
  3. 日    期   : 2006年9月9日
     作    者   : sunxibo id:46746
     修改内容   : 根据问题单号：A32D05803
  4. 日    期   : 2008年09月03日
     作    者   : l00130025
     修改内容   : 问题单号：AT2D05403,mm注册状态修改
  5.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整

  6.日    期   : 2012年2月23日
    作    者   : z40661
    修改内容   : 支持L模联合注册时，收到L模下发的关机请求无响应
  7.日    期   : 2012年3月15日
    作    者   : w00166186
    修改内容   : V7R1 C50 CSFB&PPAC&ETWS&ISR开发
  8.日    期   : 2012年9月07日
    作    者   : l00171473
    修改内容   : DTS2012081701006, 添加MM关机保护定时器
  9.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
 10.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 11.日    期   : 2014年6月13日
    作    者   : w00242748
    修改内容   : DSDS 新特性
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E23(VOS_VOID* pMsg)
{

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;

    }

#if (FEATURE_ON == FEATURE_LTE)

    /* 如果当前驻留LTE,则直接回复关机 */
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* 设置服务状态                             */
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* 设置MM信息                               */
        Mm_SndMmcPowerOffCnf();                                                 /* 向MMC发送MMCMM_POWER_OFF_CNF             */

        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E23:NORMAL: STATUS is MM_STATE_NULL");

        return;
    }
#endif

    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
    {                                                                           /* 如果为A+I模式                            */
        if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
         && (MM_FALSE == g_MmGlobalInfo.ucLikeB)
         && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
        {


            Mm_TimerStart(MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT);

            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                /* 设置DETACH类型                           */
            return;                                                             /* 不是类似B或者A+II模式的场合              */
        }
    }
    Mm_TimerStop(MM_TIMER_T3212);                                               /* 停止T3212                                */

    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {

        if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
        {
            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                    /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E23:INFO: MmServiceState is MM_NO_IMSI");
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());             /* 设置MM信息                               */
            Mm_SndMmcPowerOffCnf();
            Mm_ComSetMmState(MM_STATE_NULL);

            MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E23:NORMAL: STATUS is MM_STATE_NULL");
        }
        else
        {
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                /* 设置DETACH类型                           */

            NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);

            Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                            /* 填写消息,发送消息                        */
            Mm_TimerStart(MM_TIMER_PROTECT_DETACH);



            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E23:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
        }

    }
    else if (MM_STATUS_DETACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E23:INFO: MmServiceState is MM_NO_SERVICE");
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* 设置MM信息                               */
        Mm_SndMmcPowerOffCnf();                                                 /* 向MMC发送MMCMM_POWER_OFF_CNF             */

        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);
        }

        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E23:NORMAL: STATUS is MM_STATE_NULL");

    }
    else
    {
    }
    return;
}
/*******************************************************************************
  Module:   Mm_Cell_S9_E23
  Function: 在WAIT FOR OUTGOING MM CONNECTION状态下,收到MMCMM_POWER_OFF_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2004.03.12  新版做成
  2. 日    期   : 2007年3月20日
     作    者   : s46746
     修改内容   : 问题单号：A32D09497
  3. 日    期   : 2007年08月19日
     作    者   : luojian id:60022475
     修改内容   : 根据问题单号：A32D12706
  4. 日    期   : 2008年09月03日
     作    者   : l00130025
     修改内容   : 问题单号：AT2D05403,mm注册状态修改
  5.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  6.日    期   : 2012年3月15日
    作    者   : w00166186
    修改内容   : V7R1 C50 CSFB&PPAC&ETWS&ISR开发
  8.日    期   : 2012年9月07日
    作    者   : l00171473
    修改内容   : DTS2012081701006, 添加MM关机保护定时器
  9.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
 10.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
 11.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 12.日    期   :2013年9月12日
    作    者   :z00161729
     修改内容  :DTS2013082903019:支持ss重发功能
 13.日    期   : 2014年6月13日
    作    者   : w00242748
    修改内容   : DSDS 新特性
 14.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E23(VOS_VOID* pMsg)
{

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;
    }
    Mm_TimerStop(MM_TIMER_STOP_ALL);

    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                        /* 设置DETACH类型                           */

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
    {                                                                           /* 如果为A+I模式                            */
        if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
         && (MM_FALSE == g_MmGlobalInfo.ucLikeB)
         && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
        {

            Mm_TimerStart(MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT);

            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.ucStaOfRcvXXEstReq;
            Mm_TimerStart(MM_TIMER_T3240);
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E23:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            return;                                                             /* 不是类似B或者A+II模式的场合              */
        }
    }

    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                    /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E23:INFO: MmServiceState is MM_NO_SERVICE");
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());             /* 设置MM信息                               */

            Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
            Mm_ComSetMmState(IMSI_DETACH_INITIATED);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E23:NORMAL: STATUS is MM_STATE_NULL");
        }
        else
        {
            NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

            Mm_ComSetMmState(IMSI_DETACH_INITIATED);
            Mm_ComMsgImsiDetachIniSndOfDataReq(&Msg);                           /* 填写消息,发送消息                        */
            Mm_TimerStart(MM_TIMER_T3220);                                      /* 启动T3220                                */
            Mm_TimerStart(MM_TIMER_PROTECT_DETACH);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E23:NORMAL: STATUS is IMSI_DETACH_INITIATED");
        }
    }
    else
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E23:INFO: MmServiceState is MM_NO_SERVICE");

        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* 设置MM信息                               */

        Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
        Mm_ComSetMmState(IMSI_DETACH_INITIATED);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E23:NORMAL: STATUS is MM_STATE_NULL");
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S12_E23
  Function: 在WAIT FOR RR CONNECTION (MM CONNECTION)状态下,收到MMCMM_POWER_OFF_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2004.03.12  新版做成
  2. 张志勇        2005.01.27  007037 for MM
  3. 日    期   : 2007年08月19日
     作    者   : luojian id:60022475
     修改内容   : 根据问题单号：A32D12706
  4. 日    期   : 2008年09月03日
     作    者   : l00130025
     修改内容   : 问题单号：AT2D05403,mm注册状态修改
  5.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  6.日    期   : 2012年3月15日
    作    者   : w00166186
    修改内容   : V7R1 C50 CSFB&PPAC&ETWS&ISR开发
  7.日    期   : 2012年9月07日
    作    者   : l00171473
    修改内容   : DTS2012081701006, 添加MM关机保护定时器
  8.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  9.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
 10.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 11.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能
 12.日    期   : 2014年6月13日
    作    者   : w00242748
    修改内容   : DSDS 新特性
 13.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E23(VOS_VOID* pMsg)
{

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;

    }

    if ( (VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
      && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
    {                                                                           /* 如果为A+I模式                            */
        if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
         && (MM_FALSE == g_MmGlobalInfo.ucLikeB)
         && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
        {

            Mm_TimerStart(MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT);

            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                /* 设置DETACH类型                           */
            return;                                                             /* 不是类似B或者A+II模式的场合              */
        }
    }

    Mm_TimerStop(MM_TIMER_STOP_ALL);
    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                        /* 设置DETACH类型                           */

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
        {
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                    /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E23:INFO: MmServiceState is MM_NO_SERVICE");
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());             /* 设置MM信息                               */

            Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
            Mm_ComSetMmState(IMSI_DETACH_INITIATED);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E23:NORMAL: STATUS is MM_STATE_NULL");
        }
        else
        {
            NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);
            Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                            /* 填写消息,发送消息                        */

            Mm_TimerStart(MM_TIMER_PROTECT_DETACH);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E23:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
        }
    }
    else
    {
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E23:INFO: MmServiceState is MM_NO_SERVICE");
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* 设置MM信息                               */

        Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
        Mm_ComSetMmState(IMSI_DETACH_INITIATED);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E23:NORMAL: STATUS is MM_STATE_NULL");
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S14_E23
  Function: 在WAIT FOR REESTABLISH（WAIT FOR EST_CNF）状态下,
            收到MMCMM_POWER_OFF_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2004.03.15  新版做成
  2. 张志勇        2005.01.27  007037 for MM
  3. 日    期   : 2007年3月20日
     作    者   : s46746
     修改内容   : 问题单号：A32D09497
  4. 日    期   : 2007年08月19日
     作    者   : luojian id:60022475
     修改内容   : 根据问题单号：A32D12706
  5. 日    期   : 2008年09月03日
     作    者   : l00130025
         修改内容   : 问题单号：AT2D05403,mm注册状态修改
  6.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  7.日    期   : 2012年3月15日
    作    者   : w00166186
    修改内容   : V7R1 C50 CSFB&PPAC&ETWS&ISR开发
  8.日    期   : 2012年9月07日
    作    者   : l00171473
    修改内容   : DTS2012081701006, 添加MM关机保护定时器
  9.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
 10.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
 11.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 12.日    期   :2013年9月12日
   作    者   :z00161729
   修改内容  :DTS2013082903019:支持ss重发功能
 13.日    期   : 2014年6月13日
    作    者   : w00242748
    修改内容   : DSDS 新特性
 14.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E23(VOS_VOID* pMsg)
{

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;
    }

    if ( (VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
      && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
    {                                                                           /* 如果为A+I模式                            */
        if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
         && (MM_FALSE == g_MmGlobalInfo.ucLikeB)
         && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
        {


            Mm_TimerStart(MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT);

            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                /* 设置DETACH类型                           */
            return;                                                             /* 不是类似B或者A+II模式的场合              */
        }
    }

    Mm_TimerStop(MM_TIMER_STOP_ALL);
    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                        /* 设置DETACH类型                           */

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                    /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S14_E23:INFO: MmServiceState is MM_NO_SERVICE");

            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());             /* 设置MM信息                               */

            Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
            Mm_ComSetMmState(IMSI_DETACH_INITIATED);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E23:NORMAL: STATUS is MM_STATE_NULL");
        }
        else
        {
            if (MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg)
            {
                NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

                Mm_ComSetMmState(IMSI_DETACH_INITIATED);

                Mm_ComMsgImsiDetachIniSndOfDataReq(&Msg);                       /* 填写消息,发送消息                        */
                Mm_TimerStart(MM_TIMER_T3220);                                  /* 启动保护定时器                           */
                Mm_TimerStart(MM_TIMER_PROTECT_DETACH);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E23:NORMAL: STATUS is IMSI_DETACH_INITIATED");
            }
            else
            {
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);

                NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
                Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);
                Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                        /* 填写消息,发送消息                        */

                Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E23:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
            }

        }
    }
    else
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S14_E23:INFO: MmServiceState is MM_NO_SERVICE");

        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* 设置MM信息                               */

        Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
        Mm_ComSetMmState(IMSI_DETACH_INITIATED);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E23:NORMAL: STATUS is MM_STATE_NULL");
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S22_E23
  Function: WAIT FOR RR CONNECTION (LOCATION UPDATING)状态下,收到MMCMM_POWER_OFF_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.日    期   : 2007年06月01日
        作    者   : luojian id:60022475
        修改内容   : 根据问题单A32D10964修改
*******************************************************************************/
VOS_VOID Mm_Cell_S22_E23(VOS_VOID* pMsg)
{

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;
    }

    g_MmGlobalInfo.ucDetachType = MM_DETACH_NEED_DELAY;                        /* 设置DETACH类型                           */
    Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
}
/*******************************************************************************
  Module:   Mm_Cell_S25_E23
  Function: 在WAIT FOR RR CONNECTION (IMSI DETACH)状态下,收到MMCMM_POWER_OFF_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.15  新版做成
*******************************************************************************/
VOS_VOID Mm_Cell_S25_E23(VOS_VOID* pMsg)
{

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;
    }

    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                        /* 设置DETACH类型                           */
}

/*****************************************************************************
 函 数 名  : NAS_MM_IsNeedStopT3213_EstCnf
 功能描述  : 判断是不是需要停止3213定时器的原因值
 输入参数  : RRC_NAS_EST_RESULT_ENUM_UINT32
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月25日
    作    者   : n00269697
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MM_IsNeedStopT3213_EstCnf(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult
)
{
    if ((RRC_EST_RANDOM_ACCESS_REJECT != ulResult)
     && (RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO != ulResult)
     && (RRC_EST_RJ_RA_FAIL != ulResult)
     && (RRC_EST_RJ_RA_FAIL_NO_VALID_INFO != ulResult))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S22_E32
  Function: 在WAIT FOR RR CONNECTION (LOCATION UPDATING)状态下,收到RRMM_EST_CNF的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2004.03.15  新版做成
  2.  张志勇     2005.01.27  007037 for MM
  3. 日    期   : 2006年11月22日
     作    者   : l60022475
     修改内容   : 问题单号：A32D07583
  4. 日    期   : 2007年08月03日
     作    者   : l65478
     修改内容   : 问题单号：A32D12650
  5. 日    期   : 2008年09月03日
     作    者   : l00130025
     修改内容   : 问题单号：AT2D05403,mm注册状态修改
  6.日    期   : 2008年11月22日
    作    者   : l65478
    修改内容   : 问题单号：AT2D06900,mm注册状态修改
  7.日    期   : 2009年08月25日
    作    者   : o00132663
    修改内容   : 问题单号：AT2D14020,MM LU过程中，建链失败，cause: RRC_EST_EST_CONN_FAIL，从规范来说，
                 并没有要求清空LAI及等效PLMN，如果清空了，会导致手动搜网模式下，MMC转发给GMM的系统消息
                 中将forbidden标志置位。
  8.日    期   : 2009年08月27日
    作    者   : o00132663
    修改内容   : 问题单号：AT2D14089,【正向质量】G下，LU建链失败，cause: RR_CONN_FAIL，T3211超时后未发起LU.
  9.日    期   : 2011年11月22日
    作    者   : z00161729
    修改内容  : 问题单号：DTS2010111602266,G下CS注册失败原因立即指派拒绝,MM在收到
                RRMM_AC_INFORMATION_CHANGE_IND T3122超时消息后反复尝试LU,导致PS反复挂起恢复,影响数传性能
  10.日    期   : 2011年01月27日
     作    者   : w00176964
     修改内容   : 问题单号：DTS2011012701891,Cs connfail 4次后，进入到LAI相同的不同小区，没有发起LAU
  11.日    期   : 2011年7月16日
     作    者   : h44270
     修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  12.日    期   : 2011年7月25日
     作    者   : h44270
     修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  13.日    期   : 2012年2月15日
     作    者   : w00166186
     修改内容   : CSFB&PPAC&ETWS&ISR 开发
  14.日    期   : 2012年11月20日
     作    者   : l65478
     修改内容   :DTS2012111901564:没有通知MMC注册结果，导致MMC异常发起搜网
  15.日    期   : 2013年05月15日
     作    者   : s46746
     修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  16.日    期   : 2013年6月11日
     作    者   : w00167002
     修改内容   : V9R1_SVLTE检视意见修改:在LAU建链的时候收到CS域的DETACH，则等到
                  收到建链结果后进行处理。如果建链成功，则直接向网侧发起DETACH,否则
                  直接本地DETACH.
  17.日    期   : 2013年08月07日
     作    者   : l65478
     修改内容   : 修改问题单DTS2013080502397,在重选到G下进行LU后,然后GAS指示重定向到W原来的小区时，如果Gs口不存在,需要发起联合RAU
  18.日    期   : 2013年6月11日
     作    者   : w00167002
     修改内容   : DTS2013080802492:立即指派拒绝不删除EPLMN.

  19.日    期   : 2013年8月22日
     作    者   : w00167002
     修改内容   : DTS2013081604476:w重选到G下后，被立即指派拒绝，GAS启动T3122
                  定时器，接着用户发起电话，NAS发起LAU,GAS由于T3122运行，直接回复
                  建联失败。MM启动了T3211,在这种场景下，NAS不需要启动T3211定时器。

                  TS24.008:4.4.4.9 Abnormal cases on the mobile station side
                  d)RR connection failure
                    The procedure is aborted and the mobile station proceeds as specified below.
                    In cases d) to h) (except in the case f.1) above and for repeated failures as defined in c) above the mobile station proceeds as follows. Timer T3210 is stopped if still running. The RR Connection is aborted in case of timer T3210 timeout. The attempt counter is incremented. The next actions depend on the Location Area Identities (stored and received from the BCCH of the current serving cell) and the value of the attempt counter.
                    -the update status is UPDATED, and the stored LAI is equal to the one received on the BCCH from the current serving cell and the attempt counter is smaller than 4:
                    The mobile station shall keep the update status to UPDATED, the MM IDLE sub-state after the RR connection release is NORMAL SERVICE. The mobile station shall memorize the location updating type used in the location updating procedure. It shall start timer T3211 when the RR connection is released. When timer T3211 expires the location updating procedure is triggered again with the memorized location updating type;

                    -either the update status is different from UPDATED, or the stored LAI is different from the
                    one received on the BCCH from the current serving cell, or the attempt counter is greater or
                    equal to 4:
                    When the RR connection is released the mobile station shall delete any LAI, TMSI, ciphering key
                    sequence number stored in the SIM/USIM, and list of equivalent PLMNs,
                    set the update status to NOT UPDATED and
                    enter the MM IDLE sub-state ATTEMPTING TO UPDATE
                    (see subclause 4.2.2.2 for the subsequent actions) or optionally the MM IDLE sub-state PLMN SEARCH (see subclause 4.2.1.2) in order to perform a PLMN selection according to 3GPP TS 23.122 [14]. If the attempt counter is smaller than 4, the mobile station shall

   20.日    期   : 2014年4月2日
      作    者   : w00176964
      修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
  21.日    期   : 2014年6月4日
     作    者   : w00167002
     修改内容   : DTS2014052603967:CS only，在A小区注册失败17后迁移到B小区，在B小区
                是禁止PLMN小区，MM迁移到LIMIT service状态，后续搜网到A小区网络后，
                发起了LAU.
                在LAU失败迁移到U2状态时候记录当前的LAI信息；在开机，用户发起CS/CS_PS
                DETACH时候或或者重新发起LAU时候则清除该LAI信息；
                在后续搜索到该小区后，在U2状态，如果当前的LAI在记录的LAI里面，则
                不发起LAU.
    22.日    期   : 2013年3月28日
       作    者   : y00176023
       修改内容   : DSDS GUNAS II项目:增加对RRC_EST_RJ_NO_RF的处理
    23.日    期   : 2014年8月14日
       作    者   : z00161729
       修改内容   : gas下lau建链失败原因值random access reject no valid information场景未按协议实现8s内不发起lau，t3213 4s超时就发起了lau

    24.日    期   : 2015年1月27日
       作    者   : w00167002
       修改内容   : DTS2015012305099:BETA出现手机被叫关机，当前手机状态为22，没有
                    问题LOG，进行正向质量分析。在迁移状态时候停保护定时器，否则不停。
	25.日    期   : 2015年3月17日
       作    者   : b00269685
       修改内容   : 增加对access bar的处理
    26.日    期   : 2015年3月16日
       作    者   : w00167002
       修改内容   : DTS2015030305199:建联失败后，启动T3212定时器，导致一个小时后才
                    LAU成功，用户体验差。修改为在RR建联失败后，启动T3212定时器时长
                   可由NV进行配置。
   27.日    期   : 2015年6月3日
      作    者   : z00161729
      修改内容   : 24008 23122 R11 CR升级项目修改
   28.日    期   : 2015年8月13日
      作    者   : l00289540
      修改内容   : User_Exp_Improve修改
*******************************************************************************/
VOS_VOID Mm_Cell_S22_E32(VOS_VOID* pMsg)
{
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
    RRMM_EST_CNF_STRU*                                      pRrcEstCnf;
    VOS_UINT8                                               ucTiValidFlg;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;
    MM_LAI_STRU                                            *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstCampLaiInfo  = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsGsmOnlyEstCnfRslt;
    VOS_UINT32                                  ulIsTestCard;

    ulIsTestCard    = NAS_USIMMAPI_IsTestCard();
    ucTiValidFlg = MM_TRUE;
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    if (MM_FALSE == Mm_RcvRrcEstCnf(pMsg))
    {
        return;
    }

    pRrcEstCnf = (RRMM_EST_CNF_STRU*)pMsg;



    NAS_MM_SetEstCnfResult(pRrcEstCnf->ulResult);


    /* 处理当前缓存的CS域去注册 */
    /* 24008_CR1201R1_(Rel-8)_C1-082683 24008 4.3.4章节描述:If a RR connection
       exists and the ATT flag indicates that no detach procedure is required,
       the MM sublayer will release locally any ongoing MM connections before
       releasing the RR connection. If a MM specific procedure is active,
       the release of the RR connection may be delayed until the MM specific
       procedure is complete. lau结束后连接释放时再做本地detach,如果lau建链失败则做本地detach */
    if (VOS_TRUE == NAS_MM_IsNeedProcBufferedCsDetach_RcvLauEstCnf(pRrcEstCnf->ulResult))
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        NAS_MM_RcvRrMmEstCnf_ExistCsDetachBuffer(pRrcEstCnf);

        return;
    }



    if (NAS_MM_IsNeedStopT3213_EstCnf(pRrcEstCnf->ulResult))
    {
        g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt = 0;
        Mm_TimerStop(MM_TIMER_T3213);                                           /* 停止随机接入失败的过程 */
    }

    if ((RRC_EST_SUCCESS != pRrcEstCnf->ulResult)
        && (RRC_EST_PRESENT != pRrcEstCnf->ulResult))
    {
        /*如果PS ONLY，则直接进入limit service*/
        if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
        {
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E32:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            Mm_ComCheckDelayMmConn(MM_FALSE);

            /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-22, begin */
#if (FEATURE_ON == FEATURE_ECALL)
            /* PS ONLY在ECALL ONLY模式下不设置CS不允许attach标记*/
            if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
            {
                return;
            }
#endif
            /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-22, end */

            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            return;
        }
    }

    switch(pRrcEstCnf->ulResult)
    {
    case RRC_EST_SUCCESS:
    case RRC_EST_PRESENT:

        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        if (RRC_EST_PRESENT == pRrcEstCnf->ulResult)
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S22_E32:WARNING: RR CONNECTION PRESENT!");
        }

        g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt = 0;
        Mm_TimerStart(MM_TIMER_T3210);                                          /* 启动保护定时器                           */
        g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_PRESENT;                 /* 设置信令连接已存在                       */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E32:INFO: MmCsSigConnFlg is MM_CS_SIG_CONN_PRESENT");
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ESTED);                            /* RR连接建立成功                           */
        Mm_ComSetMmState(LOCATION_UPDATING_INITIATED);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E32:NORMAL: STATUS is LOCATION_UPDATING_INITIATED");
        break;
    case RRC_EST_ESTING:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S22_E32:WARNING: RR CONNECTION ESTING!");
        break;

    case RRC_EST_RJ_CONGEST:
    case RRC_EST_RJ_UNSPEC:
    case RRC_EST_EST_CONN_FAIL:
    case RRC_EST_RJ_NOT_ALLOW:
    case RRC_EST_RJ_TIME_OUT:
    case RRC_EST_RJ_RA_RESOURCE_FAIL:
    case RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID:
    case RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL:
    case RRC_EST_RJ_AIRMSG_DECODE_ERR:
    case RRC_EST_RJ_FASTRETURN_LTE:
    case RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT:
    case RRC_EST_RJ_SNW:
    case RRC_EST_RANDOM_ACCESS_REJECT:
    case RRC_EST_RJ_RA_FAIL:
    case RRC_EST_RJ_RA_FAIL_NO_VALID_INFO:


    case RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO:

        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        /* 仅在2G网络下处理结果原因RRC_EST_RANDOM_ACCESS_REJECT */
        ulIsGsmOnlyEstCnfRslt = NAS_MM_IsGsmOnlyEstCnfRslt(pRrcEstCnf->ulResult);

        if ((NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
         && (VOS_TRUE == ulIsGsmOnlyEstCnfRslt))
        {
            g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt++;

            /* 最多允许两次连续的随机接入失败尝试 */
            if (g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt < MM_CONST_NUM_2)
            {
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
                Mm_TimerStop(MM_TIMER_T3213);
                Mm_TimerStart(MM_TIMER_T3213);                                  /* 启动T3213 */
                Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                break;
            }

            Mm_TimerStop(MM_TIMER_T3213);                                       /* 停止随机接入失败的过程 */
        }

        if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
        {
            g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;

            if ( (VOS_TRUE == ulIsTestCard)
              && ((RRC_EST_RANDOM_ACCESS_REJECT == pRrcEstCnf->ulResult)
               || (RRC_EST_RJ_RA_FAIL == pRrcEstCnf->ulResult)) )
            {
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
            }
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
        }

        NAS_MM_ProcLuAttemptCounter(pRrcEstCnf->ulResult);


        if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
        {
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ((VOS_FALSE == NAS_MML_IsCsLaiChanged())
                && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {                                                                   /* 如果LAI不变,且更新状态为U1的时候         */
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* 记录前状态                               */
                g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E32:INFO: MmServiceState is MM_NORMAL_SERVICE");


                NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                /* NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                              MM_MMC_LU_RESULT_FAILURE,
                                              NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL); */           /* 向MMC发送MMCMM_LU_RESULT_IND             */
                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);            /* 向MMC发送MMCMM_LU_RESULT_IND             */


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                Mm_ComNasInfoSav(MM_STATUS_ATTACHED,
                                 NAS_MML_GetSimCsSecurityCksn());
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E32:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                Mm_TimerStart(MM_TIMER_T3211);                                  /* 启动T3211                                */
                g_T3211Flag = 1;
            }
            else
            {
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E32:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");


                /* GSM下建联失败，则按照RR_CONNECTION_FAILURE处理, W下建联失败，处理流程不改变 */

                /* 在U2状态，保存当前的LAI信息 */
                pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
                pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

                pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
                pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
                pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, begin */
                NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                /* 进U2的公共处理 */
                Mm_ComToU2Handle();
                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, end */

                Mm_TimerStart(MM_TIMER_T3211);                                  /* 启动T3211                                */
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

            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, begin */
            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            /* 进U2的公共处理 */
            Mm_ComToU2Handle();
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, end */

            NAS_MM_StartT3212Timer(NAS_MM_ConvertLauEstCnfRsltToT3212StartScean(pRrcEstCnf->ulResult));
        }


        if ( VOS_FALSE == NAS_MM_NotifyBufferedServiceRRConnNotExist() )
        {
             Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                      /* RR连接不存在                             */

             NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        Mm_ComCheckDelayMmConn(MM_FALSE);
        break;
    case RRC_EST_REGISTER_ACCESS_BARRED:
    case RRC_EST_IMMEDIATE_ASSIGN_REJECT:
    case RRC_EST_ACCESS_BARRED:
        /* 仅在2G网络下处理结果原因RRC_EST_IMMEDIATE_ASSIGN_REJECT */
        if ( (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
          && (RRC_EST_IMMEDIATE_ASSIGN_REJECT == pRrcEstCnf->ulResult) )
        {
            break;
        }

        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt++;

        if ((RRC_EST_REGISTER_ACCESS_BARRED == pRrcEstCnf->ulResult)
         || (RRC_EST_ACCESS_BARRED          == pRrcEstCnf->ulResult))
        {
            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);                       /* 向MMC发送MMCMM_LU_RESULT_IND             */
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);                       /* 向MMC发送MMCMM_LU_RESULT_IND             */

            Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);
        }
        else
        {


            /* 立即指派拒绝不删除EPLMN */

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);                       /* 向MMC发送MMCMM_LU_RESULT_IND             */
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
        }

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E32:NORMAL: STATUS is MM_IDLE_LOCATION_UPDATE_NEEDED");

        if (MM_FALSE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {                                                                       /* 没有等待的CC触发的需要建立的MM连接       */
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                       /* RR连接建立失败                           */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
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

        NAS_MM_EndBufferedCSServiceExceptEmergencyCall_ImmediateAssignReject();

        Mm_ComCheckDelayMmConn(MM_FALSE);
        break;

    case RRC_EST_RJ_T3122_RUNNING :

        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

        NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);


        Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

        if ( VOS_FALSE == NAS_MM_NotifyBufferedServiceRRConnNotExist() )
        {
             Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                      /* RR连接不存在                             */
             NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        NAS_MM_EndBufferedCSServiceExceptEmergencyCall_ImmediateAssignReject();

        Mm_ComCheckDelayMmConn(MM_FALSE);

        break;


    case RRC_EST_RJ_NO_RF:
        NAS_MM_ProcLauEstCnfNoRf();
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S22_E32:WARNING:  Result Abnormal");
        break;
    }

    g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt = 0;

}
/*******************************************************************************
  Module:   Mm_Cell_S25_E32
  Function: 在WAIT FOR RR CONNECTION (IMSI DETACH)状态下,收到RRMM_EST_CNF的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2004.03.15  新版做成
  2.  张志勇     2005.01.27  006044 for MM
  3.  张志勇     2005.01.27  007037 for MM
  4. 日    期   : 2007年01月17日
     作    者   : luojian id:60022475
     修改内容   : 问题单号：A32D08396
  5. 日    期   : 2007年3月20日
     作    者   : s46746
     修改内容   : 问题单号：A32D09497
  6. 日    期   : 2007年9月29日
     作    者   : luojian id:107747
     修改内容   : 问题单号 A32D12966
  7. 日    期   : 2008年7月21日
     作    者   : luojian 00107747
     修改内容   : 问题单号：AT2D04201/AT2D04536
  8. 日    期   : 2008年09月03日
     作    者   : l00130025
     修改内容   : 问题单号：AT2D05403,mm注册状态修改
  9.日    期   : 2011年7月26日
    作    者   : h44270
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  10.日    期   : 2011年7月25日
     作    者   : h44270
     修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  11.日    期   : 2012年2月15日
     作    者   : w00166186
     修改内容   : CSFB&PPAC&ETWS&ISR 开发
  12.日    期   : 2012年12月11日
     作    者   : w00176964
     修改内容   : 删除设置小区禁止业务标记,统一由MMC收到系统消息和AC INFO CHANGE维护
  13.日    期   : 2013年05月15日
     作    者   : s46746
     修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  14.日    期   : 2013年08月15日
     作    者   : l65478
     修改内容   : DTS2013081404782MM连接释放后没有通知GMM CS业务结束
  15.日    期   : 2013年8月22日
     作    者   : w00167002
     修改内容   : DTS2013081604476:w重选到G下后，被立即指派拒绝，GAS启动T3122
                  定时器，接着用户发起电话，NAS发起LAU,GAS由于T3122运行，直接回复
                  建联失败。MM启动了T3211,在这种场景下，NAS不需要启动T3211定时器。
  16.日    期   : 2013年4月10日
     作    者   : y00176023
     修改内容   : DSDS GUNAS II项目:增加对RRC_EST_RJ_NO_RF的处理
  17.日    期   : 2014年8月14日
     作    者   : z00161729
     修改内容   : gas下lau建链失败原因值random access reject no valid information场景未按协议实现8s内不发起lau，t3213 4s超时就发起了lau


 18.日    期   : 2014年9月29日
    作    者   : w00167002
    修改内容   : DTS2014092501419:在进行DETACH时候，处理RRC_EST_OTHER_ACCESS_BARRED消息
 19.日    期   : 2015年7月22日
    作    者   : z00161729
    修改内容   : DTS2015060807763:ap通过cgcatt下发imsi detach，建链失败后mm
                 本地detach，回复detach cnf时应该带limit service而不是normal
                 service，at命令回复ok而不是error
*******************************************************************************/
VOS_VOID Mm_Cell_S25_E32(VOS_VOID* pMsg)
{
    RRMM_EST_CNF_STRU*      pRrcEstCnf;

    if (MM_FALSE == Mm_RcvRrcEstCnf(pMsg))
    {
        return;
    }

    pRrcEstCnf = (RRMM_EST_CNF_STRU*)pMsg;
    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

    NAS_MM_SetEstCnfResult(pRrcEstCnf->ulResult);

    switch(pRrcEstCnf->ulResult)
    {
    case RRC_EST_SUCCESS:
    case RRC_EST_PRESENT:
        if (RRC_EST_PRESENT == pRrcEstCnf->ulResult)
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S25_E32:WARNING: RR CONNECTION PRESENT!");
            return;
        }

        Mm_TimerStart(MM_TIMER_T3220);                                          /* 启动T3220                                */
        g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_PRESENT;                 /* 设置信令连接已存在                       */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S25_E32:INFO: MmCsSigConnFlg is MM_CS_SIG_CONN_PRESENT");
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ESTED);                            /* RR连接建立成功                           */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_EXIST);
        Mm_ComSetMmState(IMSI_DETACH_INITIATED);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E32:NORMAL: STATUS is IMSI_DETACH_INITIATED");
        break;
    case RRC_EST_ESTING:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S25_E32:WARNING: RR CONNECTION ESTING!");
        break;
    case RRC_EST_RJ_CONGEST:
    case RRC_EST_RJ_UNSPEC:
    case RRC_EST_REGISTER_ACCESS_BARRED:
    case RRC_EST_ACCESS_BARRED:

    case RRC_EST_OTHER_ACCESS_BARRED:

    case RRC_EST_EST_CONN_FAIL:
    case RRC_EST_RJ_NOT_ALLOW:
    case RRC_EST_RJ_TIME_OUT:
    case RRC_EST_RJ_RA_RESOURCE_FAIL:
    case RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID:
    case RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL:
    case RRC_EST_RJ_AIRMSG_DECODE_ERR:
    case RRC_EST_RJ_CELL_BAR:
    case RRC_EST_RJ_FASTRETURN_LTE:
    case RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT:
    case RRC_EST_RJ_SNW:

    case RRC_EST_RJ_NO_RF:

    case RRC_EST_RJ_T3122_RUNNING:

    case RRC_EST_RJ_INTER_RAT:
    case RRC_EST_IMMEDIATE_ASSIGN_REJECT:
    case RRC_EST_RANDOM_ACCESS_REJECT:
    case RRC_EST_RJ_RA_FAIL:
    case RRC_EST_RJ_RA_FAIL_NO_VALID_INFO:

    case RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO:

        Mm_TimerStop(MM_TIMER_PROTECT_DETACH);
        Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);

        /* 其他接入受限，设置标志位 */
        if (RRC_EST_REGISTER_ACCESS_BARRED  == pRrcEstCnf->ulResult)
        {
            NAS_MML_SetCsRestrictRegisterFlg(VOS_TRUE);
        }

        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-18, begin */
        /* 非紧急呼叫才设置限制注册和寻呼标记 */
        if  (((RRC_EST_ACCESS_BARRED  == pRrcEstCnf->ulResult)
           || (RRC_EST_RJ_CELL_BAR == pRrcEstCnf->ulResult))
          && (MMCC_EMERGENCY_CALL   !=  g_MmCcEstReq.ulCallType))
        {
            NAS_MML_SetCsRestrictPagingFlg(VOS_TRUE);
            NAS_MML_SetCsRestrictRegisterFlg(VOS_TRUE);
        }
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-18, end */


        if (MM_DETACH_CS_POWEROFF == g_MmGlobalInfo.ucDetachType)
        {
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());             /* 设置MM信息                               */
            Mm_SndMmcPowerOffCnf();                                             /* 向MMC发送MMCMM_POWER_OFF_CNF             */

            Mm_ComSetMmState(MM_STATE_NULL);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E32:NORMAL: STATUS is MM_STATE_NULL");
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
        }
        else
        {
            /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
            if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                         & MM_WAIT_CS_DETACH))
            {
                NAS_MM_SndMmcDetachCnf(MMC_MM_LIMITED_SERVICE);
                /* 清除等待标志 */
                g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
            }

            Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E32:NORMAL: STATUS is",g_MmGlobalInfo.ucState);
        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S25_E32:WARNING: Result Abnormal");
        break;
    }

}
/*****************************************************************************
 函 数 名  :  Mm_Cell_S22_E33
 功能描述  : 在WAIT FOR RR CONNECTION (LOCATION UPDATING)状态下
             收到RRMM_REL_IND的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2008年10月15日
   作    者   : x00115505
   修改内容   : 问题单AT2D06189

 2.日    期   : 2010年8月9日
   作    者   : 欧阳飞
   修改内容   : DTS2010080502211，建链过程中直接回复RRMM_REL_IND消息，MM未
                启动T3211重新发起LU.
 3.日    期   : 2011年7月16日
   作    者   : h44270
   修改内容   : V7R1 PhaseII阶段调整，注册结果简化
 4.日    期   : 2011年11月10日
   作    者   : w00167002
   修改内容   : 删除代码:g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
                 注册失败次数达到最大时，不清零，而是等到协议(24008: 4.4.4.5 Attempt Counter)
                 描述场景进行清零操作,否则如下场景存在问题:CS域注册失败4次，PS失败5次，MMC
                 依旧等待CS注册结果上报.原因是CS失败4次后，收到RRMM_REL_IND后，收到系统消息，
                 MM假流程中上报的系统消息的中Attemp Counter指示为0，MMC会继续等待CS注册结果的上报。
 5.日    期   : 2012年2月28日
   作    者   : w00176964
   修改内容   : DTS2012021405430:W下注册PS被拒15，CS注册未完成被网测释放RRC连接，
                后续在W下注册成功后，异常清除了LAC信息，导致在收到新的系统消息异
                常发起了LAU
 6.日    期   : 2012年11月14日
   作    者   : t00212959
   修改内容   : DTS2012111304815:TD下建链失败，直接回复rel_ind,MM的处理有误
  7.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
  8.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  9.日    期   : 2014年01月09日
    作    者   : l65478
    修改内容   : DTS2014010704608:第一次鉴权响应和网络发起的第二次鉴权请求冲突
 10.日    期   : 2014年4月2日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
 11.日    期   : 2014年6月4日
    作    者   : w00167002
    修改内容   : DTS2014052603967:CS only，在A小区注册失败17后迁移到B小区，在B小区
                是禁止PLMN小区，MM迁移到LIMIT service状态，后续搜网到A小区网络后，
                发起了LAU.
                在LAU失败迁移到U2状态时候记录当前的LAI信息；在开机，用户发起CS/CS_PS
                DETACH时候或或者重新发起LAU时候则清除该LAI信息；
                在后续搜索到该小区后，在U2状态，如果当前的LAI在记录的LAI里面，则
                不发起LAU.

 12.日    期   : 2015年3月16日
    作    者   : w00167002
    修改内容   : DTS2015030305199:建联失败后，启动T3212定时器，导致一个小时后才
                 LAU成功，用户体验差。修改为在RR建联失败后，启动T3212定时器时长
                 可由NV进行配置。
*****************************************************************************/
VOS_VOID Mm_Cell_S22_E33(VOS_VOID *pRcvMsg)
{
    VOS_UINT8                           ucValidFlg;
    RRMM_REL_IND_STRU                   *pMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucRst;
    MM_LAI_STRU                        *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstCampLaiInfo  = VOS_NULL_PTR;

    pMsg = (RRMM_REL_IND_STRU *)pRcvMsg;
    ucValidFlg = Mm_RcvRrcRelInd(pRcvMsg);

    if (MM_TRUE == ucValidFlg)
    {
        NAS_MM_ClearAuthInfo();

        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        ucRst = NAS_MM_RetryCurrentProcedureCheck(pMsg->ulRelCause,
                    pMsg->ulRrcConnStatus);
        if (VOS_TRUE == ucRst)
        {
            /* LAU在收到系统消息后再重新发起 */
            g_MmGlobalInfo.ucRetryLauFlg = VOS_TRUE;

            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
            return;
        }

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
        Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

        /* 当CS域正在建立CS域连接时,如果PS域主动要求释放正在建立的PS域连接,
           这种情况接入层会释放所有正在建立的连接,从而会影响到CS域的业务.
           为避免这种情况,规定这种情况下接入层给NAS发送的连接释放指示中的
           原因值定为RRC_REL_CAUSE_NAS_REL_SUCCESS,MM在收到该原因值的释放
           指示之后不认为流程失败,继续等待接入层重新上报系统消息,重新发起流程.*/
        if (RRC_REL_CAUSE_NAS_REL_SUCCESS == pMsg->ulRelCause)
        {
            g_MmGlobalInfo.ucConnRcvSysFlg = MM_TRUE;

            /* 处理缓存的LU流程 */
            if (MM_FALSE == Mm_ComChkLu())
            {
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S22_E33:WARNING: Mm_ComChkLu return MM_FALSE\n");
            }
        }
        else
        {

            /*如果PS ONLY，则直接进入limit service*/
            if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
            {
                 Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);

                 NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

                 Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
                 PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E33:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
                 Mm_ComCheckDelayMmConn(MM_FALSE);

                 /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-22, begin */
#if (FEATURE_ON == FEATURE_ECALL)
                /* PS ONLY在ECALL ONLY模式下不设置CS不允许attach标记*/
                if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
                {
                    return;
                }
#endif
                /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-22, end */
                NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
                return;
            }



            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
            {
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
            }


            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt++;

            if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
            {
                NAS_MM_ProcConnFailLauAttmptCntLess4_RcvRelInd(pMsg->ulRelCause);
            }
            else
            {
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E33:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

                /* 在U2状态，保存当前的LAI信息 */
                pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
                pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

                pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
                pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
                pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, begin */
                NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                /* 进U2的公共处理 */
                Mm_ComToU2Handle();
                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, end */


                /* T3212定时器启动处理 */
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_LAU_RRC_EST_REL_BY_AS);

            }

            NAS_MM_SndMmcRrConn_RcvRelInd();

            Mm_ComCheckDelayMmConn(MM_FALSE);
        }

        /* 需要清除MM保存的GMM的cause值 */
        Mm_ComProcCauseClear();
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S22_E33:WARNING: ulRelCause Abnormal");
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S23_E33
  Function: 在LOCATION UPDATING INITIATED状态下,收到RRMM_REL_IND的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2004.03.15  新版做成

  2.日    期   : 2006年4月14日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D03031
  3.日    期   : 2006年11月22日
    作    者   : luojian id:60022475
    修改内容   : 问题单号：A32D07583
  4.日    期   : 2007年3月5日
    作    者   : liurui id:40632
    修改内容   : 根据问题单号：A32D09094
  5.日    期   : 2010年8月24日
    作    者   : w00167002
    修改内容   : 根据问题单号：DTS2010081802144
  6.日    期   : 2011年7月16日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  7.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  8.日    期   : 2011年11月10日
    作    者   : w00167002
    修改内容   : 删除代码:g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
                 注册失败次数达到最大时，不清零，而是等到协议(24008: 4.4.4.5 Attempt Counter)
                 描述场景进行清零操作,否则如下场景存在问题:CS域注册失败4次，PS失败5次，MMC
                 依旧等待CS注册结果上报.原因是CS失败4次后，收到RRMM_REL_IND后，收到系统消息，
                 MM假流程中上报的系统消息的中Attemp Counter指示为0，MMC会继续等待CS注册结果的上报。
  9.日    期   : 2012年2月28日
    作    者   : w00176964
    修改内容   : DTS2012021405430:W下注册PS被拒15，CS注册未完成被网测释放RRC连接，
                 后续在W下注册成功后，异常清除了LAC信息，导致在收到新的系统消息异
                 常发起了LAU
 10.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 11.日    期   : 2014年01月09日
    作    者   : l65478
    修改内容   : DTS2014010704608:第一次鉴权响应和网络发起的第二次鉴权请求冲突
 12.日    期   : 2014年4月2日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
 13.日    期   : 2014年5月5日
    作    者   : w00167002
    修改内容   : dsds_ii:降圈复杂度，在REL:NO RF异常情况下，
                 处理同RRC_REL_CAUSE_OTHER_REASON
 14.日    期   : 2014年6月4日
    作    者   : w00167002
    修改内容   : DTS2014052603967:CS only，在A小区注册失败17后迁移到B小区，在B小区
                是禁止PLMN小区，MM迁移到LIMIT service状态，后续搜网到A小区网络后，
                发起了LAU.
                在LAU失败迁移到U2状态时候记录当前的LAI信息；在开机，用户发起CS/CS_PS
                DETACH时候或或者重新发起LAU时候则清除该LAI信息；
                在后续搜索到该小区后，在U2状态，如果当前的LAI在记录的LAI里面，则
                不发起LAU.
 15.日    期   : 2014年06月15日
    作    者   : s00217060
    修改内容   : DTS2014061003286:TD2G重选，G下RAU过程中，用户指定搜TD的网络，网络不回应数据业务accept
 16.日    期   : 2015年6月23日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
 17.日    期   :2016年1月9日
    作    者   :z00359541
    修改内容   :DTS2015111402223:增加小区是否支持CSMO标识
*******************************************************************************/
VOS_VOID Mm_Cell_S23_E33(VOS_VOID* pMsg)
{
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, begin */
    RRMM_REL_IND_STRU*                                      pRrcRelInd;
    VOS_UINT8                                               ucTiValidFlg = MM_TRUE;
    VOS_UINT8                                               ucRrConnRelFlg = MM_TRUE;
    VOS_UINT8                                               ucRst;
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, end */
    if (MM_FALSE == Mm_RcvRrcRelInd(pMsg))
    {
        return;
    }

    pRrcRelInd = (RRMM_REL_IND_STRU*)pMsg;

    NAS_MM_ClearAuthInfo();

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    Mm_TimerStop(MM_TIMER_T3210);

    NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S23_E33: Rcv RR REL IND, Set CellNotSupportCsmoFlg to TRUE");
    NAS_MML_SetCellNotSupportCsmoFlg(VOS_TRUE);

    if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
    {
        /*迁移状态到limit service*/
        /*设置标志Attach not allow*/
        /*指示上层业务失败*/
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E33:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        Mm_ComCheckDelayMmConn(MM_FALSE);

        return;
    }

    ucRst = NAS_MM_RetryCurrentProcedureCheck(pRrcRelInd->ulRelCause,
                pRrcRelInd->ulRrcConnStatus);
    if (VOS_TRUE == ucRst)
    {
        /* LAU在收到系统消息后再重新发起 */
        g_MmGlobalInfo.ucRetryLauFlg = VOS_TRUE;
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                           /* RR连接不存在                             */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
        return;
    }


    NAS_MM_LocationUpdateAttemptCounter(NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);

    NAS_MM_UpdateLauRetryFlg_RcvRelInd(pRrcRelInd);



    ucRrConnRelFlg = Mm_ComRrConnRelChk();
    if (MM_TRUE == ucRrConnRelFlg)
    {
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                           /* RR连接不存在                             */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }
    else
    {
        ucTiValidFlg = Mm_ComTiChk();
        if (MM_FALSE == ucTiValidFlg)
        {
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                       /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }

    /* 需要清除MM保存的GMM的cause值 */
    Mm_ComProcCauseClear();

    /* 处理当前缓存的CS域去注册 */
    if ((VOS_FALSE  == NAS_MM_IsNeedGmmProcUserDetach())
     && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)))
    {
        /* 建链不成功，直接本地DETACH */
        NAS_MM_LocalDetach();
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S24_E33
  Function: 在LOCATION UPDATE REJECTED状态下,收到RRMM_REL_IND的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2004.03.15  新版做成
  2. 日    期   : 2008年7月11日
     作    者   : l0010747
     修改内容   : 问题单号:AT2D03814
  3.日    期   : 2011年11月10日
    作    者   : w00167002
    修改内容   : 删除代码:if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt >= MM_CONST_NUM_4)
                            {
                                g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
                            }
                 注册失败次数达到最大时，不清零，而是等到协议(24008: 4.4.4.5 Attempt Counter)
                 描述场景进行清零操作,否则如下场景存在问题:CS域注册失败4次，PS失败5次，MMC
                 依旧等待CS注册结果上报.原因是CS失败4次后，收到RRMM_REL_IND后，收到系统消息，
                 MM假流程中上报的系统消息的中Attemp Counter指示为0，MMC会继续等待CS注册结果的上报。
  4.日    期   :2014年01月09日
    作    者   :l65478
    修改内容  :DTS2014010704608:第一次鉴权响应和网络发起的第二次鉴权请求冲突
*******************************************************************************/
VOS_VOID Mm_Cell_S24_E33(VOS_VOID* pMsg)
{
    VOS_UINT8                   ucOldCsUpdateStatus;
    VOS_UINT8                   ucTempCsUpdateStatus;
    VOS_UINT8                   ucTiValidFlg = MM_TRUE;
    VOS_UINT8                   ucRrConnRelFlg = MM_TRUE;

    if (MM_FALSE == Mm_RcvRrcRelInd(pMsg))
    {
        return;
    }

    NAS_MM_ClearAuthInfo();

    Mm_TimerStop(MM_TIMER_T3240);                                               /* 停止T3240                                */


    ucOldCsUpdateStatus = NAS_MML_GetCsUpdateStatus();

    Mm_ComLuCauseHandle(g_MmGlobalInfo.usCauseVal);                             /* 调用原因值的公共处理                     */
    ucTempCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
    NAS_MML_SetCsUpdateStatus(ucOldCsUpdateStatus);

    NAS_MML_SetCsUpdateStatus(ucTempCsUpdateStatus);

    ucRrConnRelFlg = Mm_ComRrConnRelChk();

    if (MM_TRUE == ucRrConnRelFlg)
    {
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                           /* RR连接不存在                             */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }
    else
    {
        ucTiValidFlg = Mm_ComTiChk();
        if (MM_FALSE == ucTiValidFlg)
        {
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                       /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }

    Mm_ComCheckDelayDetach();
}
/*****************************************************************************
 函 数 名  : Mm_Cell_S25_E33
 功能描述  : 在WAIT FOR RR CONNECTION (IMSI DETACH)状态下
             收到RRMM_REL_IND的处理,此种情况认为AS异常,完成Detach流程
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月29日
    作    者   : luojian id:107747
    修改内容   : 新生成函数,根据问题单号 A32D12966
  2.日    期   : 2008年7月21日
    作    者   : luojian 00107747
    修改内容   : 问题单号：AT2D04201/AT2D04536
  3.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  4.日    期   : 2012年2月28日
    作    者   : w00176964
    修改内容   : DTS2012021405430:W下注册PS被拒15，CS注册未完成被网测释放RRC连接，
                 后续在W下注册成功后，异常清除了LAC信息，导致在收到新的系统消息异
                 常发起了LAU
  5.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  6.日    期   :2014年01月09日
    作    者   :l65478
    修改内容  :DTS2014010704608:第一次鉴权响应和网络发起的第二次鉴权请求冲突
  7.日    期   : 2015年7月22日
    作    者   : z00161729
    修改内容   : DTS2015060807763:ap通过cgcatt下发imsi detach，建链失败后mm
                本地detach，回复detach cnf时应该带limit service而不是normal service，
                at命令回复ok而不是error
*****************************************************************************/
VOS_VOID  Mm_Cell_S25_E33( VOS_VOID* pMsg )
{
    VOS_UINT8                           ucValidFlg;

    ucValidFlg = Mm_RcvRrcRelInd(pMsg);

    if (MM_TRUE == ucValidFlg)
    {
        NAS_MM_ClearAuthInfo();

        Mm_TimerStop(MM_TIMER_PROTECT_DETACH);
        Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);

        if (MM_DETACH_CS_POWEROFF == g_MmGlobalInfo.ucDetachType)
        {
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());
            Mm_SndMmcPowerOffCnf();
            Mm_ComSetMmState(MM_STATE_NULL);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E33:NORMAL: STATUS is MM_STATE_NULL");
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
        }
        else
        {
            /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
            if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                         & MM_WAIT_CS_DETACH))
            {
                NAS_MM_SndMmcDetachCnf(MMC_MM_LIMITED_SERVICE);

                /* 清除等待标志 */
                g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
            }

            Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E33:NORMAL: STATUS is",g_MmGlobalInfo.ucState);
        }

        /* 需要清除MM保存的GMM的cause值 */
        Mm_ComProcCauseClear();
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S25_E33:WARNING: ulRelCause Abnormal");
    }
    return;
}
/*******************************************************************************
  Module:   Mm_Cell_S26_E33
  Function: 在IMSI DETACH INITIATED状态下,收到RRMM_REL_IND的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2004.03.15  新版做成

  2.日    期   : 2006年5月27日
    作    者   : liuyang id:48197
    修改内容   : A32D04016
  3.日    期   : 2007年06月01日
    作    者   : luojian id:60022475
    修改内容   : 根据问题单A32D10964修改
  4.日    期   : 2007年01月05日
    作    者   : l60022475
    修改内容   : 根据问题单号：A32D12621
  5.日    期   : 2007年08月19日
    作    者   : luojian id:60022475
    修改内容   : 根据问题单号：A32D12706
  6.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  7.日    期   : 2011年7月26日
    作    者   : h44270
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  8.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  5. 日    期   : 2012年1月12日
     作    者   : w00166186
     修改内容   : DTS2011122704039:开机搜网后CS注册被拒#12,PS注册被拒#14，在ON
                   PLMN状态，服务域被设置为不支持MM需要将服务域不支持信息通知给MMC.
   6.日    期   : 2012年2月28日
     作    者   : w00176964
     修改内容   : DTS2012021405430:W下注册PS被拒15，CS注册未完成被网测释放RRC连接，
                  后续在W下注册成功后，异常清除了LAC信息，导致在收到新的系统消息异
                  常发起了LAU
   7.日    期   : 2013年05月15日
     作    者   : s46746
     修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
   8.日    期   :2014年01月09日
     作    者   :l65478
     修改内容  :DTS2014010704608:第一次鉴权响应和网络发起的第二次鉴权请求冲突

*******************************************************************************/
VOS_VOID Mm_Cell_S26_E33(VOS_VOID* pMsg)
{
    VOS_UINT8  ucTiValidFlg = MM_TRUE;
    VOS_UINT8  ucRrConnRelFlg = MM_TRUE;

    if (MM_FALSE == Mm_RcvRrcRelInd(pMsg))
    {
        return;
    }
    NAS_MM_ClearAuthInfo();

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    Mm_TimerStop(MM_TIMER_T3220);                                               /* 停止T3220                                */
    Mm_TimerStop(MM_TIMER_PROTECT_DETACH);

    switch(g_MmGlobalInfo.ucDetachType)
    {
    case MM_DETACH_CS_POWEROFF:
        Mm_TimerStop(MM_TIMER_STOP_ALL);
        Mm_ComSetMmState(MM_STATE_NULL);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S26_E33:NORMAL: STATUS is MM_STATE_NULL");
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());
        Mm_SndMmcPowerOffCnf();
        break;
    case MM_DETACH_CS_NORMAL:

        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                          NAS_MML_GetSimCsSecurityCksn());

        /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MM_DETACHED);
            /* 清除等待标志 */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S26_E33:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S26_E33:WARNING: Detach type Abnormal");
        break;
    }

    g_MmGlobalInfo.ucPowerOnFlg = MM_TRUE;

    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_IMSI_DETACH_IND,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    ucRrConnRelFlg = Mm_ComRrConnRelChk();
    if (MM_TRUE == ucRrConnRelFlg)
    {
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                           /* RR连接不存在                             */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }
    else
    {
        ucTiValidFlg = Mm_ComTiChk();
        if (MM_FALSE == ucTiValidFlg)
        {
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                       /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }

    /* 需要清除MM保存的GMM的cause值 */
    Mm_ComProcCauseClear();
}
/*******************************************************************************
  Module:   Mm_Cell_S23_E51
  Function: 在LOCATION UPDATING INITIATED状态下,接收到T3210溢出的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2004.03.15  新版做成
  2. 日    期   : 2008年7月11日
     作    者   : l0010747
     修改内容   : 问题单号:AT2D03814
  3. 日    期   : 2008年09月03日
     作    者   : l00130025
     修改内容   : 问题单号：AT2D05403,mm注册状态修改
  4.日    期   : 2011年7月16日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  5.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
*******************************************************************************/
VOS_VOID Mm_Cell_S23_E51(VOS_VOID* pMsg)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

    Mm_TimerStop(MM_TIMER_T3210);                                               /* 停止T3210                                */

    Mm_TimerStop(MM_TIMER_T3212);                                               /* 停止T3212                                */
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt++;

    Mm_ComSaveProcAndCauseVal(MM_LU_PROC, NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT);          /* 记录流程和原因值                         */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    Mm_TimerStart(MM_TIMER_T3240);                                              /* 启动T3240                                */
    Mm_ComSetMmState(LOCATION_UPDATE_REJECTED);
    if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
    {                                                                           /* 判断LU Counter是否小于4                  */
        enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
        if ((VOS_FALSE == NAS_MML_IsCsLaiChanged()) &&
            (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
        {                                                                       /* 判断LAI是否未改变,且更新状态为U1         */
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E46:INFO: MmServiceState is MM_NORMAL_SERVICE");

        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E46:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

        }
    }
    else
    {
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;              /* 设置服务状态                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E46:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
    }

    NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT);

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT);
    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E51:NORMAL: STATUS is LOCATION_UPDATE_REJECTED");
}
/*******************************************************************************
  Module:   Mm_Cell_S3_E52
  Function: 在MM IDLE NORMAL SERVICE状态下,接收到T3211溢出的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.15  新版做成
      2.日    期   : 2009年05月11日
        作    者   : h44270
        修改内容   : AT2D11661/AT2D11804,发起手动搜网打断LAU过程，导致搜网成功后发起两次LAU
      3.日    期   : 2012年2月11日
        作    者   : l00130025
        修改内容   : DTS2012020402238, GU->L->GU,CS支持且卡有效时，T3211超时后，LAU类型填写错误
      4.日    期   : 2015年1月5日
        作    者   : z00161729
        修改内容   : AT&T 支持DAM特性修改
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E52(VOS_VOID* pMsg)
{
    /* AT&T 测试用例GSM-BTR-1-0644和GSM-BTR-1-0650和GSM-BTR-1-0652
       和GSM-BTR-1-0656要求网络模式II，CS lau被拒#17，PS attach成功后，
       MM T3211定时器超时CS做lau被拒#17，要求PS需要做rau,该场景MM需要通知GMM做RAU*/
    if ((VOS_TRUE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
      && (MM_NET_MODE_II == g_MmGlobalInfo.ucNewNtMod))
    {
        NAS_MM_SndGmmT3211ExpiredNotify(g_MmMsgLuRjct.MmIeRejCause.ucRejCause);
    }

    if (g_MmGlobalInfo.LuInfo.ucLuType >= MM_IE_LUT_TYPE_BUTT)
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
    }

    Mm_ComLuOnly();                                                             /* 发送LU REQ                               */
}


VOS_VOID Mm_Cell_S9_E52(VOS_VOID* pMsg)
{
    Mm_TimerStart(MM_TIMER_T3211);
}
/*******************************************************************************
  Module:   Mm_Cell_S1_E53
  Function: 在MM IDLE NO CELL AVAILABLE状态下,接收到T3212溢出的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.15  新版做成
      2.  x51137  2006/4/14 A32D02955
      3.日    期   : 2012年07月02日
        作    者   : l65478
        修改内容   : DTS2012070206731, 手动搜网模式在出服务区后T3212超时重进服务区后没有发起LAU
      4.日    期   : 2013年2月4日
        作    者   : w00176964
        修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册

      5.日    期   : 2014年9月20日
        作    者   : w00167002
        修改内容   : DTS2014092400817:在A网络上注册被拒17达到最大次数后，启动T3212定时器
                     在周期搜网定时器超时后触发搜网，在搜网时候T3212超时，代码中没有
                     清除ATTEMPT COUNTER,导致后续只发起了一次LAU,后又启动了T3212.
                     GCF26.7.4.3.3失败。
      6.日    期   : 2015年1月5日
        作    者   : z00161729
        修改内容   : AT&T 支持DAM特性修改
*******************************************************************************/

VOS_VOID Mm_Cell_S1_E53(VOS_VOID* pMsg)
{
    Mm_TimerStop(MM_TIMER_T3212);                                               /* 停止T3212                                */

    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;

        if (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == NAS_MML_GetCsUpdateStatus())
        {
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
        }
        return;
    }

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, begin */
    if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, end */
    {
        if (MM_TRUE == g_MmGlobalInfo.ucLikeNetmode2)
        {
            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
        }

        if (MMCMM_NO_FORBIDDEN != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
        {
            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
        }
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;                      /* 设置T3212溢出的标识                      */
    }


    /* T3212定时器超时再ATTEMPT 2 UPDATE状态，需要清空COUNTER值 */
    if (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == NAS_MML_GetCsUpdateStatus())
    {
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S3_E53
  Function: 在MM IDLE NORMAL SERVICE状态下,接收到T3212溢出的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.15  新版做成
      2.  x51137  2006/4/14 A32D02955
      3.日    期   : 2007年05月11日
        作    者   : luojian id:60022475
        修改内容   : 问题单号:A32D10713
      4.日    期   : 2010年07月16日
        作    者   : l65478
        修改内容   : 问题单号:DTS2010070600029,网络模式I下,ATTACH失败后进行LU,T3212超时后执行LU用例失败
      5.日    期   : 2012年2月15日
        作    者   : w00166186
        修改内容   : CSFB&PPAC&ETWS&ISR 开发
      6.日    期   : 2013年2月4日
        作    者   : w00176964
        修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
      7.日    期   : 2013年12月6日
        作    者   : w00242748
        修改内容   : DTS2013120505497:G NMOI，PS联合RAU被拒#17 5次后LAU成功，T3212
                     应进行LAU；但DTS2010070600029这个单又需要在GCF测试时不进行LAU，
                     所以需要区分是GCF还是现网
      8.日    期   : 2015年1月5日
        作    者   : z00161729
        修改内容   : AT&T 支持DAM特性修改
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E53(VOS_VOID* pMsg)
{
    VOS_UINT8                    ucPsRestrictionFlg;

    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();
    Mm_TimerStop(MM_TIMER_T3212);                                               /* 停止T3212                                */

    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
        return;
    }

    /* 网络模式I下，如果GMM已经注册或者正在进行注册，T3212不处理。
    GCF44.2.1.2.8 */
    /* 此处加测试卡判断是为了在GCF测试时，不进行LAU；但现网中仍需要发起LAU */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        if ( (VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
          && (MM_NET_MODE_I    == g_MmGlobalInfo.ucNtMod))
        {
            if (VOS_TRUE == NAS_GMM_IsRegisteredOrRegistering())
            {
                return;
            }
        }
    }

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, begin */
    if ((VOS_TRUE  == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
     && (VOS_FALSE == ucPsRestrictionFlg))
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, end */
    {
        if (MM_TRUE == g_MmGlobalInfo.ucLikeNetmode2)
        {
             g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;
             g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
             Mm_ComLuOnly();
        }
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;           /* 设置LU类型                               */
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
        Mm_ComLuOnly();                                                         /* 发送LU REQ                               */
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S5_E53
  Function: 在MM IDLE ATTEMPTING TO UPDATE状态下,接收到T3212溢出的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.15  新版做成
      2.  x51137  2006/4/14 A32D02955
      3.日    期   : 2010年11月21日
        作    者   : z00161729
        修改内容   : 问题单号：DTS2010111602266:G下CS注册失败原因立即指派拒绝,MM在收到
                     RRMM_AC_INFORMATION_CHANGE_IND T3122超时消息后反复尝试LU,导致PS反复挂起恢复,影响数传性能
      4.日    期   : 2011年11月10日
        作    者   : w00167002
        修改内容   : The attempt counter is reset in case of service state
                      ATTEMPTING to UPDATE, expiry of timer T3212;
                      见协议(24008: 4.4.4.5 Attempt Counter)
      5.日    期   : 2012年2月15日
        作    者   : w00166186
        修改内容   : CSFB&PPAC&ETWS&ISR 开发
      6.日    期   : 2013年2月4日
        作    者   : w00176964
        修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
      7.日    期   : 2015年1月5日
        作    者   : z00161729
        修改内容   : AT&T 支持DAM特性修改
*******************************************************************************/
VOS_VOID Mm_Cell_S5_E53(VOS_VOID* pMsg)
{
    VOS_UINT8                    ucPsRestrictionFlg;

    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();

    Mm_TimerStop(MM_TIMER_T3212);                                               /* 停止T3212                                */

    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
        return;
    }

    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, begin */
    if ((VOS_TRUE  == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
     && (VOS_FALSE == ucPsRestrictionFlg))
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, end */
    {
        if (MM_TRUE == g_MmGlobalInfo.ucLikeNetmode2)
        {
             g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;              /* 设置LU类型                               */
             Mm_ComLuOnly();
        }
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;                   /* 设置LU类型                               */
        Mm_ComLuOnly();                                                         /* 发送LU REQ                               */
    }

    g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt = 0;

}

/*******************************************************************************
  Module:   Mm_Cell_S6_E54
  Function: 在MM_IDLE_LOCATION_UPDATE_NEEDED状态下,
            接收到T3213溢出的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  l40632  2006.04.20 create
      2.日    期   : 2009年08月6日
        作    者   : l65478
        修改内容   : 问题单号：AT2D13610，测试GCF用例26.7.4.3.1失败，原因是在重选到原来的小区后发起了LAU
      3.日    期   : 2014年8月14日
        作    者   : z00161729
        修改内容   : gas下lau建链失败原因值random access reject no valid information场景未按协议实现8s内不发起lau，t3213 4s超时就发起了lau
      4.日    期   : 2015年8月13日
        作    者   : l00289540
        修改内容   : User_Exp_Improve修改
*******************************************************************************/
VOS_VOID Mm_Cell_S6_E54(VOS_VOID* pMsg)
{
    RRC_NAS_EST_RESULT_ENUM_UINT32      enEstCnfResult;

    enEstCnfResult = NAS_MM_GetEstCnfResult();

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        /* 24008 4.4.4.9中描述:
        c)  Random access failure (A/Gb mode only)
        Timer T3213 is started. When it expires the procedure is attempted again if still necessary.
        NOTE 1: As specified in 3GPP TS 45.008 [34], a cell reselection then takes place, with return to
        the cell inhibited for 5 seconds if there is at least one other suitable cell. Typically the
        selection process will take the mobile station back to the cell where the random access failed
        after 5 seconds.
        If at the expiry of timer T3213 a new cell has not been selected due to the lack of
        valid information (see 3GPP TS 45.008 [34]), the mobile station may as an option delay
        the repeated attempt for up to 8 seconds to allow cell re-selection to take place.
        In this case the procedure is attempted as soon as a new cell has been selected or
        the mobile station has concluded that no other cell can be selected.
        */
        if((VOS_TRUE == GMM_IsGasCellReselect())
        || (RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO == enEstCnfResult)
        || (RRC_EST_RJ_RA_FAIL_NO_VALID_INFO           == enEstCnfResult))
        {
            if(g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt < MM_CONST_NUM_2)
            {
                Mm_TimerStart(MM_TIMER_T3213);
            }
            else
            {
                Mm_TimerStart(MM_TIMER_T3211);
            }
        }
        else
        {
            Mm_ComLuOnly();
            g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt++;
        }

        if ( (RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO == enEstCnfResult)
          || (RRC_EST_RJ_RA_FAIL_NO_VALID_INFO           == enEstCnfResult) )
        {
            NAS_MM_SetEstCnfResult(RRC_NAS_EST_RESULT_BUTT);
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S26_E58
  Function: 在IMSI DETACH INITIATED状态下,接收到T3220溢出的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2004.03.15  新版做成
  2. 日    期   : 2007年08月19日
     作    者   : luojian id:60022475
     修改内容   : 根据问题单号：A32D12706
  3. 日    期   : 2008年09月03日
     作    者   : l00130025
     修改内容   : 问题单号：AT2D05403,mm注册状态修改
  4.日    期   : 2011年7月26日
    作    者   : h44270
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  5.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  6. 日    期   : 2012年1月12日
     作    者   : w00166186
     修改内容   : DTS2011122704039:开机搜网后CS注册被拒#12,PS注册被拒#14，在ON
                   PLMN状态，服务域被设置为不支持MM需要将服务域不支持信息通知给MMC.

  6.日    期   : 2012年11月16日
    作    者   : z40661
    修改内容   : DTS2012111403885,T3220定时器超时,未通知接入层释放连接
  7.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
*******************************************************************************/
VOS_VOID Mm_Cell_S26_E58(VOS_VOID* pMsg)
{
    VOS_UINT8  ucTiValidFlg = MM_TRUE;
    VOS_UINT8  ucRrConnRelFlg = MM_TRUE;

    Mm_TimerStop(MM_TIMER_T3220);                                               /* 停止T3220                                */
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    switch(g_MmGlobalInfo.ucDetachType)
    {
    case MM_DETACH_CS_POWEROFF:
        Mm_TimerStop(MM_TIMER_STOP_ALL);
        Mm_ComSetMmState(MM_STATE_NULL);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S26_E58:NORMAL: STATUS is MM_STATE_NULL");
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());
        Mm_SndMmcPowerOffCnf();
        break;
    case MM_DETACH_CS_NORMAL:
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());

        /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MM_DETACHED);
            /* 清除等待标志 */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S26_E58:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S26_E58:WARNING: Detach type Abnormal");
        break;
    }

    g_MmGlobalInfo.ucPowerOnFlg = MM_TRUE;

    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_IMSI_DETACH_IND,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    ucRrConnRelFlg = Mm_ComRrConnRelChk();
    if (MM_TRUE == ucRrConnRelFlg)
    {
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                           /* RR连接不存在                             */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }
    else
    {
        ucTiValidFlg = Mm_ComTiChk();
        if (MM_FALSE == ucTiValidFlg)
        {
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                       /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
}

/*******************************************************************************
  Module:   Mm_Cell_S24_E60
  Function: 在LOCATION UPDATE REJECTED状态下,接收到T3240溢出的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.15  新版做成
*******************************************************************************/
VOS_VOID Mm_Cell_S24_E60(VOS_VOID* pMsg)
{
    Mm_T3240Expire();
}

/*****************************************************************************
 函 数 名  : Mm_Cell_S23_E45
 功能描述  : 在LOCATION UPDATING INITIATED状态下,
            收到RRMM_DATA_IND(LOCATION UPDATING ACCEPT)的处理
 输入参数  : VOS_VOID* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.张志勇     2004.03.15  新版做成

  2.日    期   : 2010年8月18日
    作    者   : 欧阳飞
    修改内容   : DTS2010081702506,Normal LAU成功后，36秒后又发起了周期性LAU
  3.日    期   : 2010年9月8日
    作    者   : 王毛/00166186
    修改内容   : DTS2010081902050
  4.日    期   : 2010年9月30日
    作    者   : 欧阳飞 00132663
    修改内容   : 根据问题单号DTS2010092902368,TMSI只在等效PLMN内有效
  5.日    期   : 2010年11月28日
    作    者   : z00161729
    修改内容  : DTS2010112604710:周期性LAU accpet消息中如果LAI信息改变且合法，需更新相应全局变量的值
  6.日    期   : 2011年7月16日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  7.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  8.日    期   : 2011年10月8日
    作    者   : z00161729
    修改内容   : V7R1 PHASEII EPLMN/RPLMN在MM/GMM维护修改
  9.日    期   : 2012年03月17日
    作    者   : s46746
    修改内容   : DTS2012030705720:RAI和网络模式发生改变,需要进行LAU流程
 10.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
 11.日    期   : 2012年3月6日
    作    者   : z00161729
    修改内容   : V7R1 C50 支持ISR修改
 12.日    期   : 2012年3月27日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发 ENERGENCY CALL
 13.日    期   : 2012年10月12日
    作    者   : s00217060
    修改内容   : DTS2012082204735:LAU不带紧急呼列表时,上次RAU中的紧急呼号码仍然有效
 14.日    期   : 2012年09月21日
    作    者   : z00161729
    修改内容   : DTS2012090706407 :法电lau accept中携带与系统消息中不同的non broadcast lai时需要出发lau
 15.日    期   : 2012年10月26日
    作    者   : W00176964
    修改内容   : DTS2012090303157:更新EPLMN有效标记
 16.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
 17.日    期   : 2013年4月22日
    作    者   : w00176964
    修改内容   : DTS2013032507710:follow ON标记存在时增加MM的服务状态上报
 18.日    期   : 2013年4月26日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mmc接口调整
 19.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 20.日    期   : 2013年07月5日
    作    者  : w00176964
    修改内容  : DTS2013062503351:LAU成功时更新当前的RAC信息
 21.日    期   : 2014年2月18日
    作    者   : l00215384
    修改内容   : DTS2014021006453，注册成功后鉴权拒绝计数清零
 22.日    期   : 2014年4月2日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai和CurLai替换成MML中的
 23.日    期   : 2015年6月5日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID Mm_Cell_S23_E45(VOS_VOID* pMsg)
{
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
    MM_LAI_STRU                                             stCurLai;
    NAS_MML_LAI_STRU                                       *pstCurrCampLai = VOS_NULL_PTR;
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT8                                               ucLacChangeFlg;
    NAS_MML_LAI_STRU                                       *pstCsSuccLai = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEplmnAddr = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stTempEplmnAddr;
    NAS_MML_IGNORE_AUTH_REJ_INFO_STRU      *pstAuthRejInfo;
    NAS_MML_EMERGENCY_NUM_LIST_STRU                        *pstEmergencyNumList;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulDeactiveIsrFlg;
    NAS_MML_RPLMN_CFG_INFO_STRU                            *pstRplmnCfgInfo;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();
#endif

    pstCsSuccLai    = NAS_MML_GetCsLastSuccLai();

    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
    pstCurrCampLai = NAS_MML_GetCurrCampLai();

    PS_MEM_SET(&stCurLai, 0x0 ,sizeof(stCurLai));
    NAS_MM_ConvertMmlLaiFormatToMMFormat(pstCurrCampLai, &stCurLai);
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    pstEmergencyNumList     = NAS_MML_GetEmergencyNumList();

    ucLacChangeFlg                              = VOS_FALSE;
    g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;


    PS_MEM_SET(&stTempEplmnAddr, 0x00, sizeof(stTempEplmnAddr));

    if (MM_TRUE == g_MmMsgLuAccpt.ucEmcFlg)
    {
        /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-26, begin */
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
        pstEmergencyNumList->ulMcc = NAS_MML_GetCurrCampPlmnId()->ulMcc;
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

        Mm_SndCcEmergencyNumberList(pstEmergencyNumList);
        /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-26, end */
    }

    else if (0 != pstEmergencyNumList->ucEmergencyNumber)
    {
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
        /* 消息中包不含紧急呼列表但之前存储了紧急呼列表,如果不是同一个国家的mcc则，删除之前存储的紧急呼叫列表
        24008_CR2107R1_(Rel-11)_C1-121605 24008 4.4.4.6、4.7.3.1.3、4.7.5.1.3描述如下:
        The emergency number(s) received in the Emergency Number List IE are valid only
        in networks with in.the same MCCcountry as in  the cell on which this IE
        is received.*/
        if (VOS_FALSE == NAS_MML_ComparePlmnMcc(pstEmergencyNumList->ulMcc, pstCurrCampLai->stPlmnId.ulMcc))
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
        {
            pstEmergencyNumList->ulMcc = 0xFFFFFFFF;

            for (i = 0; i < pstEmergencyNumList->ucEmergencyNumber; i++)
            {
                pstEmergencyNumList->aucEmergencyList[i].ucCategory = 0xFF;

                for (j = 0; j < NAS_MML_EMERGENCY_NUM_MAX_LEN; j++)
                {
                    pstEmergencyNumList->aucEmergencyList[i].aucEmcNum[j] = 0xFF;
                }
            }

            pstEmergencyNumList->ucEmergencyNumber = 0;
        }

        Mm_SndCcEmergencyNumberList(pstEmergencyNumList);
    }
    else
    {
    }

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
    if (VOS_FALSE ==  MM_ComCmpLai(g_MmMsgLuAccpt.MmIeLAI.IeLai, stCurLai))
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S23_E45:WARNING: LU ACCEPTED LAI ERROR!");
        ucLacChangeFlg = VOS_TRUE;
    }

    g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;


    g_MmGlobalInfo.ucRejectCause = NAS_MML_REG_FAIL_CAUSE_NULL;
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    Mm_TimerStop(MM_TIMER_T3210);

    /* 停止T3212定时器，并回复为配置的默认时长 */
    Mm_TimerStop(MM_TIMER_T3212);

    NAS_MM_SetNetworkT3212RandLen(MM_CONST_NUM_0);


    pstAuthRejInfo = NAS_MML_GetAuthRejInfo();
    pstAuthRejInfo->ucHplmnCsAuthRejCounter = 0;
    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;                        /* 设置服务状态                             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E45:INFO: MmServiceState is MM_NORMAL_SERVICE");
    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_TYPE_BUTT;
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    /* 记录注册成功的RAC，用于网络模式改变,比较RAI是否发生改变 */
    g_MmGlobalInfo.MsCsInfo.ucOldRac
        = NAS_MML_GetCurrCampRac();

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
    pstCsSuccLai->stPlmnId.ulMcc = pstCurrCampLai->stPlmnId.ulMcc;
    pstCsSuccLai->stPlmnId.ulMnc = pstCurrCampLai->stPlmnId.ulMnc;
    pstCsSuccLai->aucLac[0]      = pstCurrCampLai->aucLac[0];
    pstCsSuccLai->aucLac[1]      = pstCurrCampLai->aucLac[1];
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    pstCsSuccLai->ucRac = g_MmGlobalInfo.MsCsInfo.ucOldRac;

    /* 网络下发的non broadcase lai与系统消息的不同且合法，需要更新last success lai，连接释放后需要触发lau */
    if ((VOS_TRUE == ucLacChangeFlg)
     && (MM_INVALID_LAI != g_MmMsgLuAccpt.MmIeLAI.IeLai.ulLac))
    {
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
        pstCsSuccLai->stPlmnId.ulMcc                  = g_MmMsgLuAccpt.MmIeLAI.IeLai.PlmnId.ulMcc;
        pstCsSuccLai->stPlmnId.ulMnc                  = g_MmMsgLuAccpt.MmIeLAI.IeLai.PlmnId.ulMnc;
        pstCsSuccLai->aucLac[0]                       = (g_MmMsgLuAccpt.MmIeLAI.IeLai.ulLac >> 8) & (0x00FF);
        pstCsSuccLai->aucLac[1]                       = (g_MmMsgLuAccpt.MmIeLAI.IeLai.ulLac) & (0x00FF);

        PS_MEM_CPY(pstCurrCampLai, pstCsSuccLai, sizeof(NAS_MML_LAI_STRU));
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
        g_MmGlobalInfo.ucLauAcceptContainDiffNbLaiFlg = VOS_TRUE;
    }

    if (MM_TRUE == g_MmMsgLuAccpt.ucMobileIDFlg)
    {
        if (MM_MS_ID_IMSI_PRESENT ==
            (g_MmMsgLuAccpt.MmIeMobileId.MobileID.ucMsIdFlg
                                         & MM_MS_ID_IMSI_PRESENT))
        {                                                                       /* 如果存在IMSI                             */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                    ~MM_MS_ID_TMSI_PRESENT;     /* 设置TMSI无效                             */
            NAS_MML_InitUeIdTmsiInvalid();
        }
        else if (MM_MS_ID_TMSI_PRESENT ==
            (g_MmMsgLuAccpt.MmIeMobileId.MobileID.ucMsIdFlg
                                            & MM_MS_ID_TMSI_PRESENT))
        {
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |= MM_MS_ID_TMSI_PRESENT;/* 设置TMSI有效                             */

            PS_MEM_CPY(NAS_MML_GetUeIdTmsi(),
                       g_MmMsgLuAccpt.MmIeMobileId.MobileID.aucTmsi,
                       NAS_MML_MAX_TMSI_LEN);

            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMcc = NAS_MML_GetCsLastSuccMcc();
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMnc = NAS_MML_GetCsLastSuccMnc();
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            Mm_ComMsgTmsiRelocCpltSnd();                                        /* 向网侧发送TMSI REALLOCATION COMPLETE     */
        }
        else
        {
        }
    }

    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_UPDATED);                  /* 设置更新状态                             */
    Mm_ComNasInfoSav(
                     MM_STATUS_ATTACHED,
                     NAS_MML_GetSimCsSecurityCksn()
                     );                                                         /* 通知RRC,MM的Attach状态                   */
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
    }
    else
    {
        Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
    }


    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    /* 回复MMCMM_ATTACH_CNF的操作,清除等待ATTACH结果标志位 */
    if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                            & MM_WAIT_CS_ATTACH))
    {
        NAS_MM_SndMmcAttachCnf();
    }
    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;



    /* LAU成功，更新EPLMN/RPLMN */

    /* 从网侧下发的EPLMN列表中删除无效 、禁止和不允许漫游的网络 */
    if ( MM_TRUE == g_MmMsgLuAccpt.ucPlmnListFlg )
    {
        g_MmMsgLuAccpt.MmIePlmnList.ucPlmnNum = (VOS_UINT8)NAS_MML_DelInvalidPlmnFromList((VOS_UINT32)g_MmMsgLuAccpt.MmIePlmnList.ucPlmnNum,
                                           (NAS_MML_PLMN_ID_STRU *)g_MmMsgLuAccpt.MmIePlmnList.aPlmnId);

        g_MmMsgLuAccpt.MmIePlmnList.ucPlmnNum = (VOS_UINT8)NAS_MML_DelForbPlmnInList((VOS_UINT32)g_MmMsgLuAccpt.MmIePlmnList.ucPlmnNum,
                                           (NAS_MML_PLMN_ID_STRU *)g_MmMsgLuAccpt.MmIePlmnList.aPlmnId);

        /* 生成EPlmn信息列表  */
        NAS_MM_GenerateEPlmnInfo(g_MmMsgLuAccpt.MmIePlmnList.ucPlmnNum,
                                 g_MmMsgLuAccpt.MmIePlmnList.aPlmnId,
                                 &stTempEplmnAddr);
    }
    else
    {
        stTempEplmnAddr.ucEquPlmnNum = 0x1;
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
        stTempEplmnAddr.astEquPlmnAddr[0].ulMcc = NAS_MML_GetCurrCampPlmnId()->ulMcc;
        stTempEplmnAddr.astEquPlmnAddr[0].ulMnc = NAS_MML_GetCurrCampPlmnId()->ulMnc;
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
    }

    pstEplmnAddr = NAS_MML_GetEquPlmnList();


    /* 将EPLMN保存到MML全局变量 */
    PS_MEM_CPY(pstEplmnAddr, &stTempEplmnAddr, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MML_SetEplmnValidFlg(VOS_TRUE);

    /* 将EPLMN更新到NV中 */
    NAS_MM_WriteEplmnNvim(pstEplmnAddr);


    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
    if (VOS_TRUE == NAS_MM_IsGURplmnChanged(NAS_MML_GetCurrCampPlmnId(), NAS_MML_GetCurrNetRatType()))
    {
        /* 保存RPlmn信息到全局变量中 */
        NAS_MML_UpdateGURplmn(NAS_MML_GetCurrCampPlmnId(), NAS_MML_GetCurrNetRatType());

        NAS_MM_WriteRplmnWithRatNvim(NAS_MML_GetRplmnCfg());
    }
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                MM_MMC_LU_RESULT_SUCCESS,
                                NAS_MML_REG_FAIL_CAUSE_NULL);
    NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                             NAS_MML_REG_FAIL_CAUSE_NULL);
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_LAU_ACCEPT,
                              NAS_MML_REG_FAIL_CAUSE_NULL);

    Mm_ComSaveProcAndCauseVal(MM_LU_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);                   /* 记录流程和原因值                         */

    if (MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg)
    {
        g_MmGlobalInfo.ucPowerOnFlg = MM_FALSE;
    }


    g_MmSubLyrShare.MmShare.ucSpecProFlg = MM_UPDATED_SPECIFIC_PROCEDURE;

    if (MM_TRUE == g_MmMsgLuAccpt.ucFollowOFlg)
    {                                                                           /* 如存在Follow On流程                      */
        Mm_ComFollowOnProc();                                                   /* 调用Follow On的公共处理                  */
    }
    else
    {
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E45:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
        Mm_TimerStart(MM_TIMER_T3240);                                          /* 停止T3240                                */
    }

#if (FEATURE_ON == FEATURE_LTE)
    ulDeactiveIsrFlg = NAS_MM_IsNeedDeactiveIsrAfterLau();
    if (VOS_TRUE == ulDeactiveIsrFlg)
    {
        /* 去激活ISR,更新TIN值为P-TMSI */
        NAS_MM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pstRplmnCfgInfo->aucLastImsi);
        NAS_MML_SetT3423Status(NAS_MML_TIMER_STOP);
        NAS_MML_SetT3412Status(NAS_MML_TIMER_STOP);
    }
#endif

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-11, begin */

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-11, end */
}

/* Added by l00208543 for V9R1 STK升级, 2013-07-09, begin */

/*****************************************************************************
 函 数 名  : NAS_MM_ConvertMmLuTypeToStkLuType
 功能描述  : 进行类型转换:LAU_TYPE_ENUM_UINT8->NAS_STK_UPDATE_TYPE_ENUM_UINT8
 输入参数  : LAU_TYPE_ENUM_UINT8 enMmLuType MM层的LAU TYPE
 输出参数  :
 返 回 值  : PS_STK_UPDATE_TYPE_ENUM_UINT8 上报给STK的LAU TYPE
 调用函数  : NAS_MM_SndStkLauRej
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月22日
    作    者   : l00208543
    修改内容   : V9R1 STK升级，新增函数

*****************************************************************************/
NAS_STK_UPDATE_TYPE_ENUM_UINT8 NAS_MM_ConvertMmLuTypeToStkLuType (LAU_TYPE_ENUM_UINT8 enMmLuType)
{
    switch (enMmLuType)
    {
        case MM_IE_LUT_NORMAL_LU:
             return NAS_STK_LUT_NORMAL_LU;

        case MM_IE_LUT_PERIODIC_UPDATING:
             return NAS_STK_LUT_PERIODIC_UPDATING;

        case MM_IE_LUT_IMSI_ATTACH:
             return NAS_STK_LUT_IMSI_ATTACH;

        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_ConvertMmLuTypeToStkLuType:WARNING: The input in invalid");
            return NAS_STK_UPDATE_TYPE_ENUM_BUTT;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MM_ConvertMmRatTypeToStkRatType
 功能描述  : 进行RAT类型转换:NAS_MML_NET_RAT_TYPE_ENUM_UINT8->TAF_MMA_RAT_TYPE_ENUM_UINT8
 输入参数  : NAS_MML_NET_RAT_TYPE_ENUM_UINT8 enMmRatType MM层的RAT TYPE
 输出参数  : 无
 返 回 值  : TAF_PH_RAT_TYPE_ENUM_UINT8上报给STK的RAT TYPE
 调用函数  : NAS_MM_SndStkLauRej
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月22日
    作    者   : l00208543
    修改内容   : V9R1 STK升级，新增函数

  2.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
TAF_MMA_RAT_TYPE_ENUM_UINT8 NAS_MM_ConvertMmRatTypeToStkRatType (NAS_MML_NET_RAT_TYPE_ENUM_UINT8 enMmRatType)
{
    switch (enMmRatType)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
             return TAF_MMA_RAT_GSM;

        case NAS_MML_NET_RAT_TYPE_WCDMA:
             return TAF_MMA_RAT_WCDMA;

        case NAS_MML_NET_RAT_TYPE_LTE:
             return TAF_MMA_RAT_LTE;

        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_ConvertMmRatTypeToStkRatType:WARNING: The input in invalid");
            return TAF_MMA_RAT_BUTT;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MM_SndStkLauRej
 功能描述  : MM上报STK Network Rejection Event
 输入参数  : ucCause   拒绝的原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  : Mm_Cell_S23_E46
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月9日
    作    者   : l00208543
    修改内容   : V9R1 STK升级，新增函数

*****************************************************************************/
VOS_VOID NAS_MM_SndStkLauRej(VOS_UINT8 ucCause)
{
    NAS_STK_NETWORK_REJECTION_EVENT_STRU                   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;
    NAS_MML_LAI_STRU                                       *pstLai = VOS_NULL_PTR;

    /* 申请内存 */
    ulLength = sizeof(NAS_STK_NETWORK_REJECTION_EVENT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (NAS_STK_NETWORK_REJECTION_EVENT_STRU *)PS_ALLOC_MSG(WUEPS_PID_MM, ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        MM_ERR_LOG("NAS_MM_ReportStkLauRej: Alloc Msg");
        return;
    }

    PS_MEM_SET(&(pstMsg->stNetworkRejectionEvent), 0, sizeof(NAS_STK_NETWORK_REJECTION_EVENT_INFO_STRU));

    /* 填写新消息内容 */
    pstMsg->ulReceiverPid   = NAS_GetOamReceivePid(MAPS_STK_PID);

    pstLai      =  NAS_MML_GetCurrCampLai();
    pstMsg->stNetworkRejectionEvent.uRejectInfo.stLacInfo.stCurPlmnID.Mcc = pstLai->stPlmnId.ulMcc;
    pstMsg->stNetworkRejectionEvent.uRejectInfo.stLacInfo.stCurPlmnID.Mnc = pstLai->stPlmnId.ulMnc;
    pstMsg->stNetworkRejectionEvent.uRejectInfo.stLacInfo.usLac           = (pstLai->aucLac[0] << 8) | (pstLai->aucLac[1]);

    pstMsg->stNetworkRejectionEvent.enRejType                             = NAS_STK_LAU_REJECT;

    pstMsg->stNetworkRejectionEvent.enRat                                 = NAS_MM_ConvertMmRatTypeToStkRatType(pstLai->enCampPlmnNetRat);

    pstMsg->stNetworkRejectionEvent.ucCauseCode                           = ucCause;

    pstMsg->stNetworkRejectionEvent.enUpdateAttachType                    = NAS_MM_ConvertMmLuTypeToStkLuType(NAS_MM_GetLuType());

    pstMsg->ulMsgName                                                     = ID_NAS_STK_NETWORK_REJECTION_EVENT;

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MM, pstMsg))
    {
        MM_ERR_LOG("NAS_MM_SndStkLauRej: PS_SEND_MSG ERROR");
    }

    return;
}
/* Added by l00208543 for V9R1 STK升级, 2013-07-09, end */

/*******************************************************************************
  Module:   Mm_Cell_S23_E46
  Function: 在LOCATION UPDATING INITIATED状态下,
            接收到RRMM_DATA_IND(LOCATION UPDATING REJECT)的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2004.03.15  新版做成
  2. 日    期   : 2007年3月5日
     作    者   : liurui id:40632
     修改内容   : 根据问题单号：A32D09094
  3. 日    期   : 2008年7月11日
     作    者   : l0010747
     修改内容   : 问题单号:AT2D03814
  4. 日    期   : 2008年8月13日
     作    者   : l0010747
     修改内容   : 问题单号:AT2D04996/AT2D05037
  5. 日    期   : 2008年09月03日
     作    者   : l00130025
     修改内容   : 问题单号：AT2D05403,mm注册状态修改
  6. 日    期   : 2009年01月22日
     作    者   : l65478
     修改内容   : 问题单号：AT2D08462,MM支持了协议版本REL-6，GSM模式下GCF测试为REL-4，在原因值为95,96,97,99,111时，GCF测试无法通过

  7.日    期   : 2010年11月18日
    作    者   : zhoujun /40661
    修改内容   : 问题单DTS2010111601893,收到拒绝原因值为102-110的
                 处理应该和原因值111的处理一致
  8.日    期   : 2011年01月14日
    作    者   : w00176964
    修改内容   : 问题单DTS2011011301553,[V3R1B067][漫游专题]UE正常驻留W，改为
                手动搜网，G下LAU被拒，原因值为11#,改为自动搜网后驻留到原W下
                小区，此时为发起LAU/RAU，接受不到paging
  9.日    期   : 2011年7月16日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  10.日    期   : 2011年7月25日
     作    者   : z00161729
     修改内容   : V7R1 PhaseII阶段全局变量调整
  11.日    期   : 2012年3月6日
     作    者   : z00161729
     修改内容   : 支持ISR特性修改
  12.日    期   : 2013年05月15日
     作    者   : s46746
     修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  13.日    期   : 2013年07月13日
     作    者   : l00208543
     修改内容   : 增加NAS_MM_ReportStkLauRej的上报，向STK上报reject消息
  14.日    期   : 2014年5月21日
     作    者   : w00167002
     修改内容   : DTS2014051602857:在SOR打开时候，如果CS注册失败达到4次，则等周期
                搜网定时器超时发起LIST搜网，如果当前仅有原有网络，则发起LAU,否则
                触发MM发起LAU;如果LIST搜后，发现有其他网络，则发起其他网络的搜网注册。
                MM删除对SOR的特殊处理。
*******************************************************************************/
VOS_VOID Mm_Cell_S23_E46(VOS_VOID* pMsg)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulT3423StatusChgNeedRegFlg;
    VOS_UINT32                                              ulT3412StatusChgNeedRegFlg;
#endif

    g_MmGlobalInfo.ucRejectCause = g_MmMsgLuRjct.MmIeRejCause.ucRejCause;
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
    Mm_TimerStop(MM_TIMER_T3210);                                               /* 停止T3210                                */
    Mm_TimerStop(MM_TIMER_T3212);                                               /* 停止T3212                                */
    Mm_ComSaveProcAndCauseVal(MM_LU_PROC,
                              g_MmMsgLuRjct.MmIeRejCause.ucRejCause);           /* 记录流程和原因值                         */

    /* Added by l00208543 for V9R1 STK升级, 2013-07-11, begin */
    NAS_MM_SndStkLauRej(g_MmMsgLuRjct.MmIeRejCause.ucRejCause);
    /* Added by l00208543 for V9R1 STK升级, 2013-07-11, end */

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_LAU_REJECT,
                              g_MmMsgLuRjct.MmIeRejCause.ucRejCause);

    switch(g_MmMsgLuRjct.MmIeRejCause.ucRejCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;
        /* 设置CS域卡无效。一定要在收到拒绝原因值时处理，
           因为GMM处理GMM消息时会判断此标志 */
        NAS_MML_SetSimCsRegStatus(VOS_FALSE);
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;
        g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;
        break;
    default:
        if ((g_MmMsgLuRjct.MmIeRejCause.ucRejCause
            <= NAS_MML_REG_FAIL_CAUSE_RETRY_UPON_ENTRY_CELL_MAX)
         && (g_MmMsgLuRjct.MmIeRejCause.ucRejCause
            >= NAS_MML_REG_FAIL_CAUSE_RETRY_UPON_ENTRY_CELL_MIN))
        {
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
            g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt++;
        }
#if (PS_UE_REL_VER >= PS_PTL_VER_R6)
            /*
            Upon reception of the cause codes # 95, # 96, # 97, # 99 and # 111 the MS
            should set the attempt counter to 4.
            */
        if (   (NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG == g_MmMsgLuRjct.MmIeRejCause.ucRejCause)
            || (NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF == g_MmMsgLuRjct.MmIeRejCause.ucRejCause)
            || (NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE == g_MmMsgLuRjct.MmIeRejCause.ucRejCause)
            || (NAS_MML_REG_FAIL_CAUSE_IE_NONEXIST_NOTIMPLEMENTED == g_MmMsgLuRjct.MmIeRejCause.ucRejCause)
            || ( (g_MmMsgLuRjct.MmIeRejCause.ucRejCause > NAS_MML_REG_FAIL_CAUSE_MSG_NOT_COMPATIBLE )
              && (g_MmMsgLuRjct.MmIeRejCause.ucRejCause <= NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR) )
            )
        {
            /* now only WAS and WTTF support REL-6 */
            /* WCDMA/GSM都修改为4次:
                3GPP 24008 4.4.4.9 Abnormal cases on the mobile station side:
                g)Location updating reject, other causes than those treated in subclause 4.4.4.7,
                and cases of MM cause values #22 and #25, if considered as abnormal cases according to subclause 4.4.4.7
                Upon reception of the cause codes #22, # 95, # 96, # 97, # 99 and # 111 the MS should set the attempt counter to 4.
            */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_4;
        }
#endif

        /* 不需要继续尝试时，把次数修改为4次 */
        if (VOS_FALSE == NAS_MM_IsLauRejNeedRetry(g_MmMsgLuRjct.MmIeRejCause.ucRejCause))
        {
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_4;
        }


        if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
        {                                                                       /* 判断LU Counter是否小于4                  */
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
              && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {                                                                   /* 判断LAI是否未改变,且更新状态为U1         */
                g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E46:INFO: MmServiceState is MM_NORMAL_SERVICE");

            }
            else
            {
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E46:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            }
        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* 设置服务状态                             */

            /* Steering of Roaming 特性 */
            /* SOR 特性: 4次搜网失败,重新搜网后，如果仍驻留在被拒绝的网络，终端需要再尝试一次注册 */



            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E46:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
        }
        break;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* 3GPP 23401 4.3.5.6 Idle mode signalling reduction function描述去激活ISR场景：
       After a LAU procedure if the UE has CS fallback and/or SMS over SGs activated.*/
    ulT3423StatusChgNeedRegFlg = NAS_MM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                         NAS_MML_GetTinType(), NAS_MML_GetT3423Status());

    if (VOS_TRUE == ulT3423StatusChgNeedRegFlg)
    {
        NAS_MML_SetT3423Status(NAS_MML_TIMER_STOP);
    }

    ulT3412StatusChgNeedRegFlg = NAS_MM_IsT3412ExpiredNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                         NAS_MML_GetTinType(), NAS_MML_GetT3412Status());

    if (VOS_TRUE == ulT3412StatusChgNeedRegFlg)
    {
        NAS_MML_SetT3412Status(NAS_MML_TIMER_STOP);
    }
#endif
    NAS_MM_UpdateEquPlmnInfo(g_MmGlobalInfo.usCauseVal);

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                MM_MMC_LU_RESULT_FAILURE,
                                g_MmGlobalInfo.usCauseVal);
    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             g_MmGlobalInfo.usCauseVal);
    Mm_ComSetMmState(LOCATION_UPDATE_REJECTED);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E46:NORMAL: STATUS is LOCATION_UPDATE_REJECTED");
    Mm_TimerStart(MM_TIMER_T3240);                                              /* 停止T3240                                */
}

/*******************************************************************************
  Module:   Mm_Cell_S0_E2
  Function: 在MM VOS_NULL_PTR state状态下,
            接收到MMCMM_ATTACH_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  x51137     2006.04.11  新版做成
      2.日    期   : 2011年07月18日
        作    者   : w00166186
        修改内容   : V7R1 PHASE II ATTACH/DETACH调整
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E2(VOS_VOID* pMsg)
{
    VOS_UINT8   ucRet;

    ucRet = Mm_RcvMmcAttachReq(pMsg);
    if ( MM_FALSE == ucRet )
    {
    }
    else
    {
        g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;
    }

    /* 回复MMCMM_ATTACH_CNF的操作,清除等待ATTACH结果标志位 */
    if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                            & MM_WAIT_CS_ATTACH))
    {
        NAS_MM_SndMmcAttachCnf();
    }
    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;
}
/*******************************************************************************
  Module:   Mm_Cell_S1_E2
  Function: 在MM IDLE NO CELL AVAILABLE状态下,
            接收到MMCMM_ATTACH_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.20  新版做成
      2.日    期   : 2011年07月18日
        作    者   : w00166186
        修改内容   : V7R1 PHASE II ATTACH/DETACH调整
      3.日    期   : 2012年12月25日
        作    者   : l00167671
        修改内容   : 问题单号DTS2012122509118，L下搜网打紧急呼时到W下搜到与上次注册相同的小区
                     先发起了LU
      4.日    期   : 2013年1月22日
        作    者   : W00176964
        修改内容   : DTS2013012105162:MM在某些状态不需要上报服务状态给MMC
*******************************************************************************/
VOS_VOID Mm_Cell_S1_E2(VOS_VOID* pMsg)
{
    VOS_UINT8                           ucRet;

    ucRet = Mm_RcvMmcAttachReq( pMsg );
    if (MM_FALSE == ucRet)
    {
    }
    else
    {

        /*在以下状态需要直接回复结果*/
        if (( MM_IDLE_NO_CELL_AVAILABLE == g_MmGlobalInfo.ucState )
            || ( MM_IDLE_LOCATION_UPDATE_NEEDED == g_MmGlobalInfo.ucState )
            || ( MM_IDLE_NO_IMSI == g_MmGlobalInfo.ucState )
#if (!defined(__PS_WIN32_RECUR__)) && ( VOS_WIN32 != VOS_OS_VER )
            || ( MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState )
#endif
            )
        {
            /* 回复MMCMM_ATTACH_CNF的操作,清除等待ATTACH结果标志位 */
            if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                                    & MM_WAIT_CS_ATTACH))
            {
                NAS_MM_SndMmcAttachCnf();
            }
            g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;

            /* 删除原来此处服务状态上报*/
        }
        else
        {
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S4_E2
  Function: 在MM IDLE LIMITED SERVICE状态下,
            接收到MMCMM_ATTACH_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2004.03.20  新版做成
  2.日    期   : 2010年12月24日
    作    者   : 欧阳飞
    修改内容   : 问题单DTS2010122402276，网络模式I，用户进行联合去注册后，再
                 发起CS注册，失败
  3.日    期   : 2011年7月16日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  4.日    期   : 2011年07月18日
    作    者   : w00166186
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  5.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  6.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发

  7.日    期   : 2012年9月27日
    作    者   : z40661
    修改内容   : DTS2012082705793,网络模式I下，PS域access bar时,用户发起attach cs域，未进行注册
  8.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
  9.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 10.日    期   : 2015年3月20日
    作    者   : w00167002
    修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                 进行封装。
*******************************************************************************/
VOS_VOID Mm_Cell_S4_E2(VOS_VOID* pMsg)
{
    VOS_UINT8   ucRet;

    MMCMM_ATTACH_REQ_STRU                      *pRcvMsg             = VOS_NULL_PTR;
    VOS_UINT8                                   ucPsAttachAllow;
    VOS_UINT8                                   ucSimPsRegStatus;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;
    VOS_UINT8                                   ucPsRestrictRegisterFlg;

    ucPsAttachAllow  = NAS_MML_GetPsAttachAllowFlg();
    ucSimPsRegStatus = NAS_MML_GetSimPsRegStatus();

    ucPsRestrictRegisterFlg = NAS_MML_GetPsRestrictRegisterFlg();

    pRcvMsg = (MMCMM_ATTACH_REQ_STRU*)pMsg;

    ucRet = Mm_RcvMmcAttachReq(pMsg);
    if (MM_FALSE == ucRet)
    {
    }
    else
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
         && (MM_FALSE == g_MmGlobalInfo.ucLikeB)
         && (VOS_TRUE == ucSimPsRegStatus)
         && (VOS_FALSE == ucPsRestrictRegisterFlg)
         && ((VOS_TRUE == ucPsAttachAllow)
          || (MMC_MM_ATTACH_TYPE_GPRS_IMSI == pRcvMsg->enAttachType)))
        {                                                                       /* 网络模式I                                */
        }
        else
        {                                                                       /* 网络模式II                               */
            if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
            {
                if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
                {
                    /*当前小区被bar时，直接回复MMCMM_ATTACH_CNF,清除等待ATTACH结果标志位 */
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_FAILURE,
                                                NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);           /* 向MMC发送MMCMM_LU_RESULT_IND             */
                    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                             NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);           /* 向MMC发送MMCMM_LU_RESULT_IND             */

                    Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);


                    return;
                }

                enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
                if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
                  && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
                {                                                               /* 如果LAI不变,更新状态为U1                 */
                    if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
                    {
                        Mm_ComNasInfoSav(
                                         MM_STATUS_ATTACHED,
                                         NAS_MML_GetSimCsSecurityCksn()
                                         );
                        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;    /* 设置服务状态                             */
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E2:INFO: MmServiceState is MM_NORMAL_SERVICE");

                        /* 当前如果update状态是U1状态，直接回复MMCMM_ATTACH_CNF,清除等待ATTACH结果标志位 */

                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_SUCCESS,
                                                    NAS_MML_REG_FAIL_CAUSE_NULL);                /* 向MMC发送MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);                /* 向MMC发送MMCMM_LU_RESULT_IND             */
                        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);


                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S4_E2:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    }
                    else
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH; /* 设置LU类型                               */

                        Mm_ComLuOnly();                                         /* 发送LU REQ                               */
                    }
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* 设置LU类型                               */

                    Mm_ComLuOnly();                                         /* 发送LU REQ                               */
                }
            }
        }

    }
}

/*******************************************************************************
  Module:   Mm_Cell_S19_E2
  Function: 在WAIT FOR ATTACH状态下,
            接收到MMCMM_ATTACH_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2004.03.20  新版做成
  2.  s46746  2005.11.23  修改
  3.  s46746  2006-08-03  根据问题单A32D03975修改
  4.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  5.日    期   : 2011年07月18日
    作    者   : w00166186
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  6.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  7.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
  8.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  9.日    期   : 2015年3月20日
    作    者   : w00167002
    修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                 进行封装。
*******************************************************************************/
VOS_VOID Mm_Cell_S19_E2(VOS_VOID* pMsg)
{
    VOS_UINT8                                   ucRet;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

    ucRet = Mm_RcvMmcAttachReq(pMsg);

    if (MM_FALSE == ucRet)
    {
    }
    else
    {
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, begin */
        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, end */
        {                                                                       /* 网络模式I                                */
            ;
        }
        else
        {                                                                       /* 网络模式II                               */
            if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
            {
                enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
                if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
                  && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
                {                                                               /* 如果LAI不变,更新状态为U1                 */
                    if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
                    {
                        Mm_ComNasInfoSav(
                                         MM_STATUS_ATTACHED,
                                         NAS_MML_GetSimCsSecurityCksn()
                                         );
                        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;    /* 设置服务状态                             */
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S19_E2:INFO: MmServiceState is MM_NORMAL_SERVICE");
                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_SUCCESS,
                                                    NAS_MML_REG_FAIL_CAUSE_NULL);                /* 向MMC发送MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);                /* 向MMC发送MMCMM_LU_RESULT_IND             */
                        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);


                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S19_E2:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    }
                    else
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH; /* 设置LU类型                               */
                        Mm_ComLuOnly();                                         /* 发送LU REQ                               */
                    }
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* 设置LU类型                               */
                    Mm_ComLuOnly();                                         /* 发送LU REQ                               */
                }
            }
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S1_E20
  Function: 在MM IDLE NO CELL AVAILABLE状态下,
            接收到MMCMM_ MODE_CHANGE_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2004.03.20  新版做成
  2.日    期   : 2014年05月22日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目调整
*******************************************************************************/
VOS_VOID Mm_Cell_S1_E20(VOS_VOID* pMsg)
{
    VOS_UINT8                    ucRet;
    MMCMM_MODE_CHANGE_REQ_STRU  *pRcvMsg;

    ucRet = Mm_RcvMmcModeChngReq(pMsg);

    if ( MM_FALSE == ucRet )
    {
    }
    else
    {
        pRcvMsg = (MMCMM_MODE_CHANGE_REQ_STRU*)pMsg;
        switch (pRcvMsg->enMsMode)
        {
        case NAS_MML_MS_MODE_PS_CS:                                                     /* A模式的场合                              */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            break;
        case NAS_MML_MS_MODE_PS_ONLY:                                                    /* CG模式的场合                             */
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-22, begin */
#if (FEATURE_ON == FEATURE_ECALL)
            /* ecall only模式配置为PS ONLY不影响CS的attach标记 */
            if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
            {
                return;
            }
#endif
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-22, end */

            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            break;
        case NAS_MML_MS_MODE_CS_ONLY:                                                    /* CC模式的场合                             */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            break;
        case NAS_MML_MS_MODE_NULL:
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S1_E20:WARNING: MsMode Abnormal");
            break;
        }
    }
}

/* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-1, begin */

/* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-1, end */

/*******************************************************************************
  Module:   Mm_Cell_S22_E1
  Function: 在WAIT FOR RR CONNECTION (LOCATION UPDATING)状态下,
            接收到MMCMM_START_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2004.03.20  新版做成
  2.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  3.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  4.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  5.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能
  6.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S22_E1(VOS_VOID* pMsg)
{
    VOS_UINT8   ucRet;

    ucRet = Mm_RcvMmcStartReq(pMsg);
    if (MM_TRUE != ucRet)
    {
    }
    else
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E1:NORMAL: STATUS is MM_STATE_NULL");

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());
        Mm_ComInit();                                                           /* 全局变量初始化                           */
        Mm_ComStart();                                                          /* 调用收到MMCMM_START_REQ的公共处理        */
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S9_E2
  Function: 在WAIT FOR OUTGOING MM CONNECTION状态下,
            接收到MMCMM_ATTACH_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.20  新版做成
      2.  搜6746     2006.08.03  根据问题单A32D03975修改
      3.日    期   : 2011年07月18日
        作    者   : w00166186
        修改内容   : V7R1 PHASE II ATTACH/DETACH调整
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E2(VOS_VOID* pMsg)
{
    VOS_UINT8                                               ucRet;

    ucRet = Mm_RcvMmcAttachReq(pMsg);
    if (MM_TRUE != ucRet)
    {
    }
    else
    {
        /* 回复MMCMM_ATTACH_CNF的操作,清除等待ATTACH结果标志位 */
        if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                                & MM_WAIT_CS_ATTACH))
        {
            NAS_MM_SndMmcAttachCnf();
        }
        g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S3_E12
  Function: 在MM IDLE NORMAL SERVICE状态下,
            接收到GMMMM_GPRS_DETACH_COMPLETED的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.20  新版做成
      2. 日    期   : 2009年06月09日
         作    者   : l00130025
         修改内容   : 问题单AT2D12278,NMO I，GPRS Detach后，MS没有发起LAU（IMSI ATTACH），CS进行呼叫被拒,原因为IMSI unkown in VLR
      3. 日    期   : 2012年11月07日
         作    者   : l65478
         修改内容   : DTS2012110503477,设置成CS ONLY后MM没有发起LU
       4.日    期   : 2013年2月4日
         作    者   : w00176964
         修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
       2.日    期   : 2015年3月20日
         作    者   : w00167002
         修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                      进行封装。
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E12(VOS_VOID* pMsg)
{
    VOS_UINT8   ucRet;

    ucRet = Mm_RcvGmmGprsDetechCmpl(pMsg);
    if (MM_TRUE != ucRet)
    {
    }
    else
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
        {                                                                       /* 网络模式为I,且用户模式为A的场合          */
            if ((MM_TRUE == g_MmGlobalInfo.ucLikeB)
               || (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
            {                                                                   /* 类似于B模式的场合                        */
                ;
            }
            else
            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E12:INFO: MmLikeB is MM_TRUE");

                if (MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState)
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
                    Mm_ComLuOnly();
                }
                else
                {
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S4_E12
  Function: 在MM IDLE LIMITED SERVICE状态下,
            接收到GMMMM_GPRS_DETACH_COMPLETED的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.20  新版做成

  1.日    期   : 2012年9月7日
    作    者   : z40661
    修改内容   : DTS2012081605654,网络模式I下，RAU被#9拒绝后,MM未进行LAU

  2.日    期   : 2012年12月7日
    作    者   : w00167002
    修改内容   : DTS2012120608772:CS域打电话时候，用户设置PS detach，PS DETACH
                 成功后，用户无法挂断电话。由于打电话时候，MM处于MM CONNECTION
                 ACTIVE状态，此时收到PS detach，将状态迁移到IDLE NORMAL SERVICE了，
                 导致不处理CC给MM的链接释放请求消息，导致异常。
  3.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
  4.日    期   : 2015年3月20日
    作    者   : w00167002
    修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                 进行封装。
*******************************************************************************/
VOS_VOID Mm_Cell_S4_E12(VOS_VOID* pMsg)
{
    VOS_UINT8   ucRet;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8  enUpdateStatus;

    VOS_UINT32                          ulCurrMMState;

    ulCurrMMState  = Mm_GetState();

    enUpdateStatus = NAS_MML_GetCsUpdateStatus();

    ucRet = Mm_RcvGmmGprsDetechCmpl(pMsg);
    if (MM_TRUE != ucRet)
    {
    }
    else
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
        {                                                                       /* 网络模式为I,且用户模式为A的场合          */
            if ((MM_TRUE == g_MmGlobalInfo.ucLikeB)
               || (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
            {                                                                   /* 类似于B模式的场合                        */
                ;
            }
            else
            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* 设置为类似B模式                          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E12:INFO: MmLikeB is MM_TRUE");
            }


            if ( (VOS_TRUE               == NAS_MM_IsCsEnableLau())
              && (MM_IDLE_LIMITED_SERVICE == ulCurrMMState) )
            {

                /* 位置区没有改变,不需要进行 */
                if ( (VOS_TRUE == NAS_MML_IsCsLaiChanged())
                  || (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == enUpdateStatus))
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
                    Mm_ComLuOnly();
                }
                else
                {

                    g_MmGlobalInfo.ucLikeB = MM_TRUE;
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E12:INFO: MmLikeB is MM_TRUE");
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                }
            }

        }
    }
}


/*****************************************************************************
 函 数 名  : Mm_Cell_S17_E12
 功能描述  : 在LOCATION UPDATING PENDING状态下,
             接收到GMMMM_GPRS_DETACH_COMPLETED的处理
 输入参数  : VOS_VOID                           *pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2015年3月20日
    作    者   : w00167002
    修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                 进行封装。
*****************************************************************************/
VOS_VOID Mm_Cell_S17_E12(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8   ucRet;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8  enUpdateStatus;

    enUpdateStatus = NAS_MML_GetCsUpdateStatus();

    ucRet = Mm_RcvGmmGprsDetechCmpl(pMsg);
    if (MM_TRUE != ucRet)
    {
    }
    else
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
        {                                                                       /* 网络模式为I,且用户模式为A的场合          */
            if ((MM_TRUE == g_MmGlobalInfo.ucLikeB)
               || (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
            {                                                                   /* 类似于B模式的场合                        */
                ;
            }
            else
            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* 设置为类似B模式                          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E12:INFO: MmLikeB is MM_TRUE");
            }


            if ( VOS_TRUE == NAS_MM_IsCsEnableLau() )
            {
                /* 位置区没有改变,不需要进行 */
                if ( (VOS_TRUE == NAS_MML_IsCsLaiChanged())
                  || (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == enUpdateStatus))
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
                    Mm_ComLuOnly();
                }
                else
                {

                    g_MmGlobalInfo.ucLikeB = MM_TRUE;
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E12:INFO: MmLikeB is MM_TRUE");
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                }
            }

        }
    }
}


/*******************************************************************************
  Module:   Mm_Cell_S0_E20
  Function: 在MM_NULL状态下,
            接收到MMCMM_ MODE_CHANGE_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.张志勇     2004.03.20  新版做成
  2.x51137  2006/4/14 A32D02955
  3.日    期   : 2008年8月21日
    作    者   : l00130025
    修改内容   : 问题单号:At2D05016,MM注册状态修改
  4.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  5.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  6.日    期   : 2014年05月22日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目调整
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E20(VOS_VOID* pMsg)
{
    VOS_UINT8                        ucRet;
    MMCMM_MODE_CHANGE_REQ_STRU      *pModChgReq = VOS_NULL_PTR;

    ucRet = Mm_RcvMmcModeChngReq(pMsg);

    if (MM_TRUE != ucRet)
    {
    }
    else
    {
         g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;

        if (VOS_TRUE == NAS_MML_GetSimPresentStatus())
        {                                                                       /* SIM存在的场合                            */
            NAS_MML_SetSimCsRegStatus(VOS_TRUE);
        }
        else
        {                                                                       /* SIM不存在的场合                          */
            NAS_MML_SetSimCsRegStatus(VOS_FALSE);
        }

        pModChgReq = (MMCMM_MODE_CHANGE_REQ_STRU*)pMsg;
        switch (pModChgReq->enMsMode)
        {
        case NAS_MML_MS_MODE_PS_CS:                                                     /* A模式的场合                              */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录原状态                               */
            if (MM_TRUE == g_MmGlobalInfo.ucSysInfoFlg)
            {                                                                   /* 存在缓存系统信息的场合                   */
                if (VOS_TRUE != NAS_MML_GetSimCsRegStatus())
                {                                                               /* SIM无效的场合                            */
                    Mm_ComSetMmState(MM_IDLE_NO_IMSI);


                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E20:NORMAL: STATUS is MM_IDLE_NO_IMSI");
                }
                else
                {
                    Mm_ComSetMmState(MM_WAIT_FOR_ATTACH);


                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E20:NORMAL: STATUS is MM_WAIT_FOR_ATTACH");
                }
            }
            else
            {
                Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E20:NORMAL: STATUS is MM_IDLE_NO_CELL_AVAILABLE");
            }
            break;
        case NAS_MML_MS_MODE_PS_ONLY:                                                    /* CG模式的场合                             */
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-22, begin */
#if (FEATURE_ON == FEATURE_ECALL)
            /* ecall only模式配置为PS ONLY不影响CS的attach标记 */
            if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
            {
                return;
            }
#endif
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-22, end */

            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            break;
        case NAS_MML_MS_MODE_CS_ONLY:                                                    /* CC模式的场合                             */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录原状态                               */
            if (MM_TRUE == g_MmGlobalInfo.ucSysInfoFlg)
            {
                if (VOS_TRUE != NAS_MML_GetSimCsRegStatus())
                {                                                               /* SIM无效的场合                            */
                    Mm_ComSetMmState(MM_IDLE_NO_IMSI);


                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E20:NORMAL: STATUS is MM_IDLE_NO_IMSI");
                }
                else
                {
                    Mm_ComSetMmState(MM_WAIT_FOR_ATTACH);


                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E20:NORMAL: STATUS is MM_WAIT_FOR_ATTACH");
                }
            }
            else
            {
                Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E20:NORMAL: STATUS is MM_IDLE_NO_CELL_AVAILABLE");
            }
            break;
        default:
            break;
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S3_E20
  Function: 在MM IDLE NORMAL SERVICE状态下,
            接收到MMCMM_ MODE_CHANGE_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.20  新版做成
      2.  日    期   : 2009年01月20日
          作    者   : l00130025
          修改内容   : 问题单号:AT2D08378,当服务域改变时,MM/GMM没有对UE的mode进行改变;GMM在RAU过程中收到Detach请求时,直接返回,没有处理
      3.  日    期   : 2014年05月22日
          作    者   : w00176964
          修改内容   : V3R3C60_eCall项目调整
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E20(VOS_VOID* pMsg)
{
    VOS_UINT8                        ucRet;
    MMCMM_MODE_CHANGE_REQ_STRU      *pModChgReq = VOS_NULL_PTR;

    ucRet = Mm_RcvMmcModeChngReq(pMsg);

    if (MM_TRUE != ucRet)
    {
    }
    else
    {
        pModChgReq = (MMCMM_MODE_CHANGE_REQ_STRU*)pMsg;
        switch (pModChgReq->enMsMode)
        {
        case NAS_MML_MS_MODE_PS_CS:                                                     /* A模式的场合                              */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            if (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
            {                                                                   /* 网络模式为I的场合                        */
                if (MM_TIMER_STOP != gstMmTimer[MM_TIMER_T3212].ucTimerStatus)
                {
                    Mm_TimerStop(MM_TIMER_T3212);                               /* 停T3212                                  */
                }
            }
            break;
        case NAS_MML_MS_MODE_PS_ONLY:                                                    /* CG模式的场合                             */
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-22, begin */
#if (FEATURE_ON == FEATURE_ECALL)
            /* ecall only模式配置为PS ONLY不影响CS的attach标记 */
            if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
            {
                return;
            }
#endif
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-22, end */

            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S3_E20:WARNING: MsMode Abnormal");
            break;
        case NAS_MML_MS_MODE_CS_ONLY:                                                    /* CC模式的场合                             */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S3_E20:WARNING: MsMode Abnormal");
            break;
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S3_E20
  Function: 在WAIT FOR OUTGOING MM CONNECTION状态下,
            接收到MMCMM_ MODE_CHANGE_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.20  新版做成
      2.  日    期   : 2009年01月20日
          作    者   : l00130025
          修改内容   : 问题单号:AT2D08378,当服务域改变时,MM/GMM没有对UE的mode进行改变;GMM在RAU过程中收到Detach请求时,直接返回,没有处理
      3.  日    期   : 2014年05月22日
          作    者   : w00176964
          修改内容   : V3R3C60_eCall项目调整
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E20(VOS_VOID* pMsg)
{
    VOS_UINT8                        ucRet;
    MMCMM_MODE_CHANGE_REQ_STRU      *pModChgReq = VOS_NULL_PTR;

    ucRet = Mm_RcvMmcModeChngReq(pMsg);

    if ( MM_TRUE != ucRet )
    {
    }
    else
    {
        pModChgReq = (MMCMM_MODE_CHANGE_REQ_STRU*)pMsg;
        switch (pModChgReq->enMsMode)
        {
        case NAS_MML_MS_MODE_PS_CS:                                                     /* A模式的场合                              */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            if (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
            {                                                                   /* 网络模式为I的场合                        */
                if (MM_TRUE == g_MmGlobalInfo.ucLikeB)
                {
                    g_MmGlobalInfo.ucLikeB = MM_FALSE;
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E20:INFO: MmLikeB is MM_FALSE");
                }
            }
            break;
        case NAS_MML_MS_MODE_PS_ONLY:                                                    /* CG模式的场合                             */
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-22, begin */
#if (FEATURE_ON == FEATURE_ECALL)
            /* ecall only模式配置为PS ONLY不影响CS的attach标记 */
            if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
            {
                return;
            }
#endif
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-22, end */

            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S9_E20:WARNING: MsMode Abnormal");
            break;
        case NAS_MML_MS_MODE_CS_ONLY:                                                    /* CC模式的场合                             */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S9_E20:WARNING: MsMode Abnormal");
            break;
        }
    }
}
/*******************************************************************************
  MODULE   : Mm_Cell_S11_E27
  FUNCTION : 在wait for network command状态下收到MMCC_DATA_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-04-09    新版作成
     2.  s46746     05-11-24    修改
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E27(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    MMCC_DATA_REQ_STRU      *pMmCcDataReq;

    pMmCcDataReq = (MMCC_DATA_REQ_STRU*)pRcvMsg;

    if (MM_FALSE == Mm_RcvCcDataReq(pRcvMsg))
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ((pMmCcDataReq->ulTransactionId <= 15)
            && (MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg))
        {                                                                       /* TIO 等于111并且有CS域信令连接            */
            Mm_SndRrDataReq(pMmCcDataReq->SendCcMsg.ulCcMsgSize,
                            &pMmCcDataReq->SendCcMsg.aucCcMsg[0],
                            RRC_NAS_MSG_PRIORTY_HIGH);                          /* 将CC的消息传送下去                       */
        }
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S14_E50
  FUNCTION : 在WAIT FOR REESTABLISH(WAIT FOR EST_CNF)状态下
             收到RRMM_DATA_IND( CM Message)的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-04-09    新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E50(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8   ucTI = 0;                                                       /* CC消息中的TI                             */
    RRMM_DATA_IND_STRU *pRrDataInd = (RRMM_DATA_IND_STRU *) pRcvMsg;            /* 消息RRMM_DATA_IND的结构体指针            */
    VOS_UINT8   *pucCMMsg = VOS_NULL_PTR;                                       /* 指针类型转换                             */
    VOS_UINT8   *pucBakCMMsg = VOS_NULL_PTR;

    Mm_TimerStop(MM_TIMER_T3212);                                               /* 停T3212                                  */

    pucCMMsg = (VOS_UINT8 *)MM_MEM_ALLOC(VOS_MEMPOOL_INDEX_MM,
                            pRrDataInd->RcvNasMsg.ulNasMsgSize,
                            WUEPS_MEM_NO_WAIT);                                 /* 申请内存                                 */
    if (VOS_NULL_PTR == pucCMMsg)
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S14_E50:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }
    pucBakCMMsg = pucCMMsg;
    PS_MEM_SET(pucCMMsg, 0,
               sizeof(VOS_UINT8) * pRrDataInd->RcvNasMsg.ulNasMsgSize);         /* 初始化内存                               */

    PS_MEM_CPY (pucCMMsg,
                &(pRrDataInd->RcvNasMsg.aucNasMsg[0]),
                pRrDataInd->RcvNasMsg.ulNasMsgSize);                            /* 得到消息内容                             */
    ucTI = (VOS_UINT8)(((pucCMMsg[0] & 0xf0) >> 4));                            /* 得到CC消息中的TI                         */
    if (((MM_CONST_NUM_7 == ucTI) || (MM_CONST_NUM_15 == ucTI))
        && (MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg))
    {                                                                           /* TIO = 111                                */
        Mm_SndCcEstInd (ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg);    /* 向CC发送MMCC_EST_IND                     */
    }
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg);                            /* 释放申请的消息                           */

    return;
}
/*******************************************************************************
  Module:   Mm_Cell_S22_E5
  Function: 在WAIT FOR RR CONNECTION (LOCATION UPDATING)状态下,
            收到MMCMM_SYS_INFO_IND的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.    张志勇     2004.04.13  新版做成
  2.  张志勇        2005.01.27  007037 for MM
  3.日    期   : 2006年10月6日
    作    者   : s46746
    修改内容   : 问题单号：A32D05960
  4.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  5.日    期   : 2012年03月17日
    作    者   : s46746
    修改内容   : DTS2012030705720:RAI和网络模式发生改变,需要进行LAU流程
  6.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  7.日    期   : 2013年12月5日
    作    者   : w00167002
    修改内容   : DTS2013113006231:W下，开机在LAC1上注册成功，重选到LAC2上，CS注册成功
                  PS注册被拒#13,重选回LAC1上，注册成功。丢网后任意小区驻留在LAC2
                  上，不发起注册，重选回LAC1上，检测不发起注册。
                  修改为在收到系统消息时候，不进行UPDATE状态的更新
  8.日    期   : 2014年04月1日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目:系统消息处理优化
*******************************************************************************/
VOS_VOID Mm_Cell_S22_E5(VOS_VOID* pMsg)
{

    VOS_UINT8  ucTiValidFlg = MM_TRUE;

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-1, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-1, end */

    if ((MMCMM_NO_FORBIDDEN !=
         g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
        && (MMCMM_FORBIDDEN_PLMN_FOR_GPRS !=
            g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

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
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }
    else
    {
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S23_E5
  Function: 在LOCATION UPDATING INITIATED状态下, 收到MMCMM_SYS_INFO_IND的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2004.04.13  新版做成
  2.日    期   : 2006年10月6日
    作    者   : s46746
    修改内容   : 问题单号：A32D05960
  3.日    期   : 2008年7月11日
    作    者   : l0010747
    修改内容   : 问题单号:AT2D03814
  4.日    期   : 2008年09月03日
    作    者   : l00130025
    修改内容   : 问题单号：AT2D05403,mm注册状态修改
  5.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  6.日    期   : 2012年03月17日
    作    者   : s46746
    修改内容   : DTS2012030705720:RAI和网络模式发生改变,需要进行LAU流程
  7.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  8.日    期   : 2014年04月1日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目:系统消息处理优化
*******************************************************************************/
VOS_VOID Mm_Cell_S23_E5(VOS_VOID* pMsg)
{
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-1, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-1, end */

    if ((MMCMM_NO_FORBIDDEN !=
         g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
        && (MMCMM_FORBIDDEN_PLMN_FOR_GPRS !=
            g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        Mm_TimerStop(MM_TIMER_T3210);                                           /* 停T3210                                  */
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* 向RRC发送RRMM_REL_REQ(CS域)              */
        if (MMCMM_FORBIDDEN_PLMN ==
            (MMCMM_FORBIDDEN_PLMN &
                g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            Mm_ComSaveProcAndCauseVal(MM_LU_PROC, NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN); /* 记录流程和原因值                         */
        }
        else if (MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS
            == (MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS
                & g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
            )
        {
            Mm_ComSaveProcAndCauseVal(MM_LU_PROC, NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS);   /* 记录流程和原因值                         */
        }
        else
        {
            Mm_ComSaveProcAndCauseVal(MM_LU_PROC, NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM); /* 记录流程和原因值                         */
        }
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 记录前状态                               */
        Mm_ComSetMmState(LOCATION_UPDATE_REJECTED);

        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

        NAS_MM_UpdateEquPlmnInfo(g_MmGlobalInfo.usCauseVal);

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    g_MmGlobalInfo.usCauseVal);
        NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                 g_MmGlobalInfo.usCauseVal);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E5:NORMAL: STATUS is LOCATION_UPDATE_REJECTED");
        Mm_TimerStart(MM_TIMER_T3240);                                          /* 启动TIMER3240                            */
    }
    else
    {
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;
    }
}

/* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-1, begin */

/* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-1, end */

/*******************************************************************************
  Module:   Mm_Cell_S23_E22
  Function: 在LOCATION UPDATING INITIATED状态下,
            收到MMCMM_DETACH_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇    2005.01.31  新版做成
  2.日    期   : 2008年7月21日
    作    者   : luojian 00107747
    修改内容   : 问题单号：AT2D04201/AT2D04536
  3.日    期   : 2011年7月26日
    作    者   : h44270
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整

  3.日    期   : 2013年6月5日
    作    者   : w00167002
    修改内容   : 如果当前RR链接存在，则直接在当前的RR链路上发起CS域的去注册；
                 否则重新建立RR链接；
                 在鉴权过程中，则清除鉴权标志信息；
  4.日    期   : 2013年6月24日
    作    者   : w00167002
    修改内容   : 设置DETACH类型，否则在收到REL时候，不回复MMC的DETACH CNF
  5.日    期   : 2014年6月13日
    作    者   : w00242748
    修改内容   : DSDS 新特性
  6.日    期   : 2015年6月3日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID Mm_Cell_S23_E22(VOS_VOID* pMsg)
{
    MM_MSG_IMSI_DETACH_IND_STRU         stMsg;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }


    /* 在LAU时候，如果当前信令链接已建立好了，则直接发送DETACH REQ到网侧 */
    if (MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg)
    {
        /* 24008_CR1201R1_(Rel-8)_C1-082683 24008 4.3.4章节描述:If a RR connection
           exists and the ATT flag indicates that no detach procedure is required,
           the MM sublayer will release locally any ongoing MM connections before
           releasing the RR connection. If a MM specific procedure is active,
           the release of the RR connection may be delayed until the MM specific
           procedure is complete.*/
        if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
        {
            return;
        }

        /* 在鉴权过程中，则清除鉴权标志信息 */
        if ( MM_RCV_AUTH_CNF_FLG == (g_MmGlobalInfo.ucRcvAgentFlg & MM_RCV_AUTH_CNF_FLG) )
        {
            g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

            /* 停止保护定时器 */
            Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
        }


        /* 设置DETACH类型，否则在收到REL时候，不回复MMC的DETACH CNF */
        g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;

        /* 如果CS域信令连接存在                     */
        /* 停止LAU的保护定时器T3210 */
        Mm_TimerStop(MM_TIMER_T3210);
        NAS_MM_FillMobileID(&(stMsg.MmIeMobileId.MobileID));

        Mm_ComSetMmState(IMSI_DETACH_INITIATED);
        Mm_ComMsgImsiDetachIniSndOfDataReq(&stMsg);                             /* 填写消息,发送消息                        */
        Mm_TimerStart(MM_TIMER_T3220);                                          /* 启动T3220                                */
    }

    /* 如果当前信令尚未建立好，则等收到EST_CNF后进行DETACH的处理  */

    return;

}
/*******************************************************************************
  Module:   Mm_Cell_S24_E22
  Function: 在LOCATION UPDATE REJECTED状态下,
            收到MMCMM_DETACH_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇    2005.01.31  新版做成
  2. 日    期   : 2008年09月03日
     作    者   : l00130025
     修改内容   : 问题单号：AT2D05403,mm注册状态修改
  3.日    期   : 2011年7月26日
    作    者   : h44270
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  4.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
  5.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  6.日    期   : 2013年6月8日
    作    者   : w00167002
    修改内容   : V9R1_SVLTE:如果注册结果导致卡无效，则返回
                 检视意见修改:删除是否由GMM处理用户detach统一归类
  7.日    期   : 2013年6月24日
    作    者   : w00167002
    修改内容   : 设置DETACH类型，否则在收到REL时候，不回复MMC的DETACH CNF
  8.日    期   : 2014年6月13日
    作    者   : w00242748
    修改内容   : DSDS 新特性
*******************************************************************************/
VOS_VOID Mm_Cell_S24_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;
    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = ( MMCMM_DETACH_REQ_STRU* )pMsg;



    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        Mm_TimerStop(MM_TIMER_T3212);                                           /* 停止T3212                                */

        /* 如果注册结果导致卡无效，则返回  */
        if ( VOS_FALSE == NAS_MML_GetSimCsRegStatus() )
        {
            NAS_MM_LocalDetach();
            return;
        }

        if ((MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
            || (MM_STATUS_ATTACHED !=
                            g_MmSubLyrShare.MmShare.ucCsAttachState))
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            Mm_ComSaveProcAndCauseVal(MM_IMSI_DETACH, NAS_MML_REG_FAIL_CAUSE_NULL);       /* 记录流程和原因值                         */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E22:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动T3240                                */
        }
        else
        {
            NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));


            /* 设置DETACH类型，否则在收到REL时候，不回复MMC的DETACH CNF */
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;

            Mm_ComSetMmState(IMSI_DETACH_INITIATED);
            Mm_ComMsgImsiDetachIniSndOfDataReq(&Msg);                           /* 填写消息,发送消息                        */
            Mm_TimerStart(MM_TIMER_T3220);                                      /* 启动T3220                                */

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E22:NORMAL: STATUS is IMSI_DETACH_INITIATED");
        }
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S6_E53
  Function: 在MM IDLE LOCATION UPDATE NEEDED状态下,接收到T3212溢出的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.05.08  新版做成
      2.日    期   : 2015年1月5日
        作    者   : z00161729
        修改内容   : AT&T 支持DAM特性修改
*******************************************************************************/
VOS_VOID Mm_Cell_S6_E53(VOS_VOID* pMsg)
{
    Mm_TimerStop(MM_TIMER_T3212);                                               /* 停止T3212                                */

    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
        return;
    }

    if (MM_IDLE_LOCATION_UPDATE_NEEDED == g_MmGlobalInfo.ucState)
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S0_E14
  Function: 在MM NULL状态下,接收到GMMMM_GMM_ACTION_RESULT_IND的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.05.08  新版做成
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E14(VOS_VOID* pMsg)
{
    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S0_E13
  Function: 在MM NULL状态下,接收到GMMMM_NETWORK_DETACH_IND的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.05.08  新版做成
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E13(VOS_VOID* pMsg)
{
    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

}
/*******************************************************************************
  Module:   Mm_Cell_S4_E13
  Function: 在MM IDLE LIMITED SERVICE状态下收到GMMMM_NETWORK_DETACH_IND的处理
  Input:    VOS_VOID *pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2005.01.13  003018 for MM
  2.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整

  3.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
*******************************************************************************/
VOS_VOID Mm_Cell_S4_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU       *pstNetWkDetachInd = VOS_NULL_PTR;

    if (MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg))
    {
        return;
    }
    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }
    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    if (GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType)
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
        {                                                                       /* 如果为A+I模式                            */
            if (MM_FALSE == g_MmGlobalInfo.ucLikeB)
            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* 设置类似于B模式                          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E13:INFO: MmLikeB is MM_TRUE");
            }
        }
    }
    else if (GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType)
    {
    }
    else
    {
        switch(pstNetWkDetachInd->ulDetachCause)
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_ComNetDetachCauseHandle(
                (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
             && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
            {                                                                   /* 如果为A+I模式                            */
                if (MM_FALSE == g_MmGlobalInfo.ucLikeB)
                {
                    g_MmGlobalInfo.ucLikeB = MM_TRUE;                           /* 设置类似于B模式                          */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E13:INFO: MmLikeB is MM_TRUE");
                }
            }
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            MM_CKSN_INVALID
                            );
            Mm_ComDelLai();
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_TMSI_PRESENT;
            NAS_MML_InitUeIdTmsiInvalid();
            break;
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            break;
        default:
            break;
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S5_E13
  Function: 在MM IDLE ATTEMPT TO UPDATE状态下收到GMMMM_NETWORK_DETACH_IND的处理
  Input:    VOS_VOID *pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2005.01.13  003018 for MM
      2. 日    期   : 2008年8月23日
         作    者   : l00130025
         修改内容   : 问题单号:At2D05016,MM注册状态修改

      3. 日    期   : 2013年2月4日
         作    者   : w00176964
         修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
       4.日    期   : 2013年05月15日
         作    者   : s46746
         修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
      5.日    期   : 2015年3月20日
        作    者   : w00167002
        修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                     进行封装。
*******************************************************************************/
VOS_VOID Mm_Cell_S5_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU      *pstNetWkDetachInd;
    VOS_UINT8                           ucOldUpdateSts;
    VOS_UINT8                           ucTempUpdateSts;

    if (MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg))
    {
        return;
    }

    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    if (GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType)
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
        {                                                                       /* 如果为A+I模式                            */
            if (MM_FALSE == g_MmGlobalInfo.ucLikeB)
            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* 设置类似于B模式                          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S5_E13:INFO: MmLikeB is MM_TRUE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            }
        }
    }
    else if (GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType)
    {
    }
    else
    {
        switch(pstNetWkDetachInd->ulDetachCause)
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_ComNetDetachCauseHandle(
                (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
             && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
            {                                                                   /* 如果为A+I模式                            */
                if (MM_FALSE == g_MmGlobalInfo.ucLikeB)
                {
                    g_MmGlobalInfo.ucLikeB = MM_TRUE;                           /* 设置类似于B模式                          */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S5_E13:INFO: MmLikeB is MM_TRUE");
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S5_E13:INFO: MmServiceState is MM_LIMITED_SERVICE");
            ucOldUpdateSts = NAS_MML_GetCsUpdateStatus();
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);          /* 设置更新状态                             */
            ucTempUpdateSts = NAS_MML_GetCsUpdateStatus();
            NAS_MML_SetCsUpdateStatus(ucOldUpdateSts);
            NAS_MML_SetCsUpdateStatus(ucTempUpdateSts);
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S5_E13:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            break;
        default:
            break;
        }
    }
}

/* add by 张志勇    2005-1-31 for MM 003018 end */
/*******************************************************************************
  Module:   Mm_Cell_S6_E24
  Function: 在MM IDLE LOCATION UPDATE NEEDED状态下,接收到MMCC_EST_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.05.19  新版做成
      2.  s46746  2005-11-15  修改
      3.  日    期   : 2011年10月27日
          作    者   : s46746
          修改内容   : V7R1 PhaseIII,支持L模联合注册
      4.日    期   : 2012年2月15日
        作    者   : w00166186
        修改内容   : CSFB&PPAC&ETWS&ISR 开发
      5.日    期   : 2012年8月13日
        作    者   : z00161729
        修改内容   : DCM定制需求和遗留问题修改,支持L紧急呼叫修改
      6.日    期   : 2012年9月25日
        作    者   : z00161729
        修改内容   : DTS2012071907985:cs被bar，mm收到cc的建链请求应回复rel ind而不是等t303超时
      7.日    期   : 2012年10月29日
        作    者   : z00161729
        修改内容   : DTS2012083102536:支持cc呼叫重建
      8.日    期   : 2012年12月11日
        作    者   : w00176964
        修改内容   : 修改 NAS_MML_GetCsRestrictNormalServiceFlg函数名
      9.日    期   : 2012年12月21日
        作    者   : L00171473
        修改内容   : DTS2012122007141:L单模时收到呼叫请求直接向CC回复失败
      10.日    期   :2013年9月12日
         作    者   :z00161729
         修改内容   :DTS2013082903019:支持ss重发功能
      11.日    期   : 2014年8月4日
         作    者   : w00167002
         修改内容   : DTS2014080407625:在L下注册成功后ACCESS BAR,MM状态迁移到LOCATION
                      UPDATE NEEDED,此时用户发起电话失败。
      12.日    期   :2014年9月24日
         作    者   :s00217060
         修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID    Mm_Cell_S6_E24( VOS_VOID* pMsg)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

#endif

    if ( MM_FALSE == Mm_RcvCcEstReq(pMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {
#if (FEATURE_ON == FEATURE_LTE)

        /* 如果当前为L单模则直接回复CC失败 */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);                        /* 通知CC建立失败                           */
            return;
        }

        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, begin */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {

            /* NAS修改不拦截电话 */


            NAS_MM_RcvCcEstReq_CSFB();
            return;
        }
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, end */
#endif

        /* 非紧急呼，当前小区主叫业务受限则不处理 */
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            /* 通知CC建立失败 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);
            return;
        }

        if ( (MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
            ||(MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId))
        {
            /* TI不合法                                 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                              /* 通知CC建立失败                           */
        }
        else
        {                                                                       /* TI合法                                   */
            if ( MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType )
            {                                                                   /* 是紧急呼叫                               */
                g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;     /* 记录收到建立请求时的状态                 */

                NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
            }
            else
            {
                if (MM_COM_SRVST_NORMAL_SERVICE == NAS_MM_GetLauUptNeededCsSrvStatus())
                {
                    g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;

                    /* TI合法  */
                    NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
                }
                else
                {
                    if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                    {
                        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);                                  /* 通知CC建立失败                           */
                    }
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;

                    /* GU下location update needed状态收到cc的est_req,NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR */
                    /* MM在unbar to bar或者LMM报access bar的时候才会迁到location update needed状态 */
                    Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);
                }
            }
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S6_E62
  Function: 在MM IDLE LOCATION UPDATE NEEDED状态下,接收到MMSMS_EST_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.05.19  新版做成
      2.日    期   : 2012年2月15日
        作    者   : w00166186
        修改内容   : CSFB&PPAC&ETWS&ISR 开发
      3.日    期   : 2012年12月11日
        作    者   : w00176964
        修改内容   : 修改 NAS_MML_GetCsRestrictNormalServiceFlg函数名
      4.日    期   :2013年9月12日
        作    者   :z00161729
        修改内容  :DTS2013082903019:支持ss重发功能
      5.日    期   :2014年9月24日
        作    者   :s00217060
        修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID    Mm_Cell_S6_E62( VOS_VOID* pMsg)
{
    MM_MSG_CM_SVC_REQ_STRU              stCmSvcReq;
    VOS_UINT16                          usMsgSize = 0;
    VOS_UINT8                          *pucCmSvcReq = 0;

    if ( MM_FALSE == Mm_RcvSmsEstReq(pMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {
        /* 当前小区主叫业务受限则不处理 */
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
        {
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi,
                            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);            /* 通知SMS建立失败                           */
            return;
        }

        if (MM_COM_SRVST_NORMAL_SERVICE == NAS_MM_GetLauUptNeededCsSrvStatus())
        {
            g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;             /* 记录收到建立请求时的状态                 */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
                = MM_TRUE;

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId
                = g_MmSmsEstReq.ulTi;

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallType
                = 0;

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallPri
                = 0;

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat
                = NAS_MML_GetCurrNetRatType();

            /* 填充CM SERVICE REQUEST结构体 */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SMS, MM_FALSE, &stCmSvcReq);

            /* 填充CM SERVICE REQUEST 消息 */
            pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &stCmSvcReq, &usMsgSize );
            if ( VOS_NULL_PTR == pucCmSvcReq )
            {
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S6_E62:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
                return;
            }
            else
            {
                Mm_SndRrEstReq( RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL,
                   MM_FALSE,
                   usMsgSize, pucCmSvcReq );
                MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq );
            }

            /* 记录正在建立的MM连接的TI和PD */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                = (VOS_UINT8)g_MmSmsEstReq.ulTi;
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_SMS_MSG;

            /* 启动保护定时器 */
            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);

            /* 通知MMC/GMM，CS域的业务已经启动 */
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);

            /* 记录状态 */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E62:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");

            /* 设置业务存在标志 */
            NAS_MM_UpdateCsServiceBufferStatusFlg();
            NAS_MM_UpdateCsServiceConnStatusFlg();
        }
        else
        {
            /* GU下location update needed状态收到sms的est_req,NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR */
            /* MM在access bar或者LMM报access bar的时候才会迁到location update needed状态 */
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi,
                            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);                                /* 通知SMS建立失败                           */
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S6_E65
  Function: 在MM IDLE LOCATION UPDATE NEEDED状态下,接收到MMSS_EST_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.05.19  新版做成
      2. 日    期   : 2007年07月31日
         作    者   : luojian id:60022475
         修改内容   : 问题单号:A32D12640
      3. 日    期   : 2012年2月15日
         作    者   : w00166186
         修改内容   : CSFB&PPAC&ETWS&ISR 开发
      4. 日    期   : 2012年2月15日
         作    者   : w00166186
         修改内容   : CSFB&PPAC&ETWS&ISR 开发
      5.日    期   : 2012年12月11日
        作    者   : w00176964
        修改内容   : 修改 NAS_MML_GetCsRestrictNormalServiceFlg函数名
      6.日    期   :2013年9月12日
        作    者   :z00161729
        修改内容  :DTS2013082903019:支持ss重发功能
      7.日    期   : 2014年8月4日
        作    者   : w00167002
        修改内容   : DTS2014080407625:在L下注册成功后ACCESS BAR,MM状态迁移到LOCATION
                      UPDATE NEEDED,此时用户发起电话失败。 NAS修改不作屏蔽。
      8.日    期   :2014年9月24日
        作    者   :s00217060
        修改内容   :for cs_err_log
*******************************************************************************/

VOS_VOID    Mm_Cell_S6_E65( VOS_VOID* pMsg)
{
    MM_MSG_CM_SVC_REQ_STRU              stCmSvcReq;
    VOS_UINT16                          usMsgSize = 0;
    VOS_UINT8                          *pucCmSvcReq = 0;

    if ( MM_FALSE == Mm_RcvSsEstReq(pMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {
        /* 当前小区主叫业务受限则不处理 */
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

#if (FEATURE_ON == FEATURE_LTE)
        /* 如果当前驻留LTE,则直接发起 */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            NAS_MM_RcvSsEstReq_CSFB();

            return;
        }
#endif

        if (MM_COM_SRVST_NORMAL_SERVICE == NAS_MM_GetLauUptNeededCsSrvStatus())
        {
            g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;             /* 记录收到建立请求时的状态                 */

           /* 正常服务发起建链 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
                = MM_TRUE;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId
                = g_MmSsEstReq.ulTi;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallType
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallPri
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat = NAS_MML_GetCurrNetRatType();

            /* 填充CM SERVICE REQUEST结构体 */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SS_ACT, MM_FALSE, &stCmSvcReq);

            /* 填充CM SERVICE REQUEST 消息 */
            pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &stCmSvcReq, &usMsgSize );
            if (VOS_NULL_PTR == pucCmSvcReq)
            {
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S6_E65:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
                return;
            }
            else
            {
                Mm_SndRrEstReq(RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL,
                   MM_FALSE, usMsgSize, pucCmSvcReq);
                MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq);
            }

            /* 记录正在建立的MM连接的TI和PD */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI = (VOS_UINT8)g_MmSsEstReq.ulTi;
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_NON_CALL_RLT_SS_MSG;

            /* 启动保护定时器 */
            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);

            /* 通知MMC，CS域的业务已经启动              */
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);

            /* 记录状态 */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E65:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        }
        else
        {
            /* ==>A32D12640 */
            /* GU下location update needed状态收到ss的est_req,NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR */
            /* MM在access bar或者LMM报access bar的时候才会迁到location update needed状态 */
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S5_E24
  Function: 在MM IDLE ATTEMPTING TO UPDATE状态下,接收到MMCC_EST_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.05.19  新版做成
      2.  日    期   : 2011年10月27日
          作    者   : s46746
          修改内容   : V7R1 PhaseIII,支持L模联合注册
      3. 日    期   : 2012年2月15日
         作    者   : w00166186
         修改内容   : CSFB&PPAC&ETWS&ISR 开发
      4. 日    期   : 2012年8月14日
         作    者   : z00161729
         修改内容   : DCM定制需求和遗留问题修改,支持L紧急呼叫修改
      5.日    期   : 2012年9月25日
        作    者   : z00161729
        修改内容   : DTS2012071907985:cs被bar，mm收到cc的建链请求应回复rel ind而不是等t303超时
      6.日    期   : 2012年10月29日
        作    者   : z00161729
        修改内容   : DTS2012083102536:支持cc呼叫重建
      7.日    期   : 2012年12月11日
        作    者   : w00176964
        修改内容   : 修改 NAS_MML_GetCsRestrictNormalServiceFlg函数名
      8.日    期   : 2012年12月21日
        作    者   : L00171473
        修改内容   : DTS2012122007141:L单模时收到呼叫请求直接向CC回复失败
      9.日    期   : 2013年2月4日
        作    者   : w00176964
        修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
      10.日    期   :2013年9月12日
         作    者   :z00161729
         修改内容   :DTS2013082903019:支持ss重发功能

      11.日    期   : 2014年8月11日
         作    者   : w00167002
         修改内容   : DTS2014080407625:在ATTEMPT TO UPDATE状态也尝试发起普通呼叫。
      12.日    期   :2014年9月24日
         作    者   :s00217060
         修改内容   :for cs_err_log
      13.日    期   : 2015年1月5日
         作    者   : z00161729
         修改内容   : AT&T 支持DAM特性修改
*******************************************************************************/
VOS_VOID    Mm_Cell_S5_E24( VOS_VOID* pMsg)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

#endif

    if ( MM_FALSE == Mm_RcvCcEstReq(pMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {
#if (FEATURE_ON == FEATURE_LTE)


        /* 如果当前为L单模则直接回复CC失败 */
        /* 如果当前为L单模则直接回复CC失败 */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);                        /* 通知CC建立失败                           */
            return;
        }

        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, begin */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            /* 如果当前驻留LTE,则也尝试发起普通呼叫 */

            NAS_MM_RcvCcEstReq_CSFB();
            return;
        }
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, end */
#endif

        /* 非紧急呼，当前小区主叫业务受限则不处理 */
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            /* 通知CC建立失败 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        g_MmGlobalInfo.ucStaOfRcvXXEstReq =
            g_MmGlobalInfo.ucState;                                             /* 记录收到建立请求时的状态                 */

        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, begin */
        if (VOS_FALSE == NAS_MM_IsCcTiValid())
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, end */
        {
            /* TI不合法                                 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                              /* 通知CC建立失败                           */
        }
        else
        {                                                                       /* TI合法                                   */
            if ( MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType )
            {                                                                   /* 是紧急呼叫                               */
                NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
            }
            else
            {
                /* 不是紧急呼叫                             */
                if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                {
                    /* 已经存在一个保留的MM连接建立请求         */
                    Mm_SndCcRelInd(
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST );                     /* 通知CC建立失败                           */

                    return;
                }

                if (VOS_TRUE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
                {
                    /* 不触发重拨的原因值 */
                    Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);
                    return;
                }

                /* 缓存消息 */
                NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);

                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, begin */
                if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, end */
                {
                    NAS_MM_SndGmmRegisterInit();                                    /* 通知GMM进行注册                          */
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
                    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
                    Mm_ComLuOnly();                                             /* LU REQ                                   */
                }
            }
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S0_E22
  Function: 在MM NULL状态下,收到MMCMM_DETACH_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2004.05.28  新版做成
  2.日    期   : 2011年7月26日
    作    者   : h44270
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  3.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  4. 日    期   : 2012年1月12日
     作    者   : w00166186
     修改内容   : DTS2011122704039:开机搜网后CS注册被拒#12,PS注册被拒#14，在ON
                   PLMN状态，服务域被设置为不支持MM需要将服务域不支持信息通知给MMC.
  5.日    期   : 2013年6月13日
    作    者   : w00167002
    修改内容   : V9R1_SVLTE:非NULL状态下才迁移到LIMIT SERVICE状态
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*   pMmcDetachReq;

    if ( MM_FALSE == Mm_RcvMmcDetachReq(pMsg) )
    {
        return;
    }

    pMmcDetachReq = ( MMCMM_DETACH_REQ_STRU* )pMsg;

    if ( MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType )
    {
        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S0_E22:INFO: MmServiceState is MM_NO_SERVICE");
        Mm_ComNasInfoSav(
                         MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* 设置MM信息                               */
        switch ( pMmcDetachReq->enDetachType )
        {
        case MMC_MM_CS_DETACH:
        case MMC_MM_PS_CS_DETACH:
            /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
            if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                         & MM_WAIT_CS_DETACH))
            {
                NAS_MM_SndMmcDetachCnf(MM_DETACHED);

                g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
            }

            if ( MM_STATE_NULL != Mm_GetState() )
            {
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            }

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S0_E22:WARNING: Detach Cause Abnormal");
            break;
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S0_E59
  Function: 在MM NULL状态下,收到T3230溢出的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.05.28  新版做成
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E59(VOS_VOID* pMsg)
{
    Mm_TimerStop(MM_TIMER_T3230);                                               /* 停止TIMER3230                            */
}
/*******************************************************************************
  Module:   Mm_Cell_S0_E60
  Function: 在MM NULL状态下,收到T3240溢出的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.05.31  新版做成
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E60(VOS_VOID* pMsg)
{
    Mm_TimerStop(MM_TIMER_T3240);                                               /* 停止TIMER3230                            */
}
/*******************************************************************************
  Module:   Mm_Cell_S11_E36
  Function: 在WAIT FOR NETWORK COMMAND状态下,收到AUTHENTICATION REQUEST的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.05.31  新版做成
      2.日    期   : 2013年7月23日
        作    者   : w00167002
        修改内容   : DTS2013072205858:2g rf 13.2用例测试异常。
                      收到寻呼时候，网侧不下发SETUP,测试底层性能指标。
                      T3240超时后，释放了当前链接，导致用例测试失败。
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E36(VOS_VOID* pMsg)
{
    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_AUTH_REQ,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
    Mm_TimerStop( MM_TIMER_T3212 );                                             /* 停T3212                                  */


    /* WaitForNetworkCommand状态重启T3240 */
    NAS_MM_RestartT3240_WaitForNetworkCommand();

    Mm_ComAuthenRcvAuthenReq();
}
/*******************************************************************************
  Module:   Mm_Cell_S11_E37
  Function: 在WAIT FOR NETWORK COMMAND状态下,收到AUTHENTICATION REJECT的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.张志勇     2004.05.31  新版做成
  2.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  3.日    期   : 2015年6月8日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E37(VOS_VOID* pMsg)
{
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    Mm_TimerStop( MM_TIMER_T3212 );                                             /* 停T3212                                  */

    Mm_TimerStop( MM_TIMER_T3240 );                                             /* 停T3240                                  */

    Mm_TimerStart( MM_TIMER_T3240 );                                            /* 启动T3240                                */

    /* 24008_CR1942R3_(Rel-11)_C1-114725 24008 4.3.2.5章节描述如下:
    If the AUTHENTICATION REJECT message is received in any other state the mobile station shall
    abort any MM specific, MM connection establishment or call re-establishment procedure,
    stop any of the timers T3210, or T3230, T3214 or T3216 (if they were running),
    release all MM connections (if any), start timer T3240 and enter the state WAIT FOR NETWORK COMMAND,
    expecting the release of the RR connection. */
    Mm_TimerStop(MM_TIMER_T3214);
    Mm_TimerStop(MM_TIMER_T3216);


    Mm_ComAuthenRcvAuthenRej();                                                 /* 收到AUTHEN REJ的处理                     */

    NAS_MM_SndGmmAuthFailInd();
    NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);

    /* 判断等待标志是否存在，如果存在则发送MMCGMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                 & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MMC_MM_NO_IMSI);
        /* 清除等待标志 */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_AUTH_REJECT,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
}

/*******************************************************************************
  Module:   Mm_Cell_S11_E38
  Function: 在WAIT FOR NETWORK COMMAND状态下,收到IDENTITY REQUEST的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.05.31  新版做成
      2.日    期   : 2013年7月23日
        作    者   : w00167002
        修改内容   : DTS2013072205858:2g rf 13.2用例测试异常。
                  收到寻呼时候，网侧不下发SETUP,测试底层性能指标。
                  T3240超时后，释放了当前链接，导致用例测试失败。
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E38(VOS_VOID* pMsg)
{
    Mm_TimerStop( MM_TIMER_T3212 );                                             /* 停T3212                                  */


    /* WaitForNetworkCommand状态重启T3240 */
    NAS_MM_RestartT3240_WaitForNetworkCommand();

    Mm_ComIdentity();                                                           /* IDENTITY过程的处理                       */

    return;
}
/*******************************************************************************
  Module:   Mm_Cell_S11_E39
  Function: 在WAIT FOR NETWORK COMMAND状态下,收到TMSI REALLOCATION COMMAND的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.05.31  新版做成
      2.日    期   : 2013年7月23日
        作    者   : w00167002
        修改内容   : DTS2013072205858:2g rf 13.2用例测试异常。
                  收到寻呼时候，网侧不下发SETUP,测试底层性能指标。
                  T3240超时后，释放了当前链接，导致用例测试失败。
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E39(VOS_VOID* pMsg)
{
    Mm_TimerStop( MM_TIMER_T3212 );                                             /* 停T3212                                  */


    /* WaitForNetworkCommand状态重启T3240 */
    NAS_MM_RestartT3240_WaitForNetworkCommand();

    Mm_ComTmsiReloc();
    return;
}

/*******************************************************************************
  Module:   Mm_Cell_S11_E43
  Function: 在WAIT FOR NETWORK COMMAND状态下,收到MM INFORMATION的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.05.31  新版做成
      2.日    期   : 2013年7月23日
        作    者   : w00167002
        修改内容   : DTS2013072205858:2g rf 13.2用例测试异常。
                      收到寻呼时候，网侧不下发SETUP,测试底层性能指标。
                    T3240超时后，释放了当前链接，导致用例测试失败。
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E43(VOS_VOID* pMsg)
{
    Mm_TimerStop( MM_TIMER_T3212 );                                             /* 停T3212                                  */


    /* WaitForNetworkCommand状态重启T3240 */
    NAS_MM_RestartT3240_WaitForNetworkCommand();

    Mm_ComInfo();                                                               /* MM INFO过程的处理                        */
    return;
}

/*******************************************************************************
  Module:   Mm_Cell_S11_E44
  Function: 在WAIT FOR NETWORK COMMAND状态下,收到MM STATUS的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.05.31  新版做成
      2.日    期   : 2013年7月23日
        作    者   : w00167002
        修改内容   : DTS2013072205858:2g rf 13.2用例测试异常。
                      收到寻呼时候，网侧不下发SETUP,测试底层性能指标。
                    T3240超时后，释放了当前链接，导致用例测试失败。
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E44(VOS_VOID* pMsg)
{
    Mm_TimerStop( MM_TIMER_T3212 );                                             /* 停T3212                                  */


    /* WaitForNetworkCommand状态重启T3240 */
    NAS_MM_RestartT3240_WaitForNetworkCommand();

    return;
}

/*******************************************************************************
  Module:   Mm_Cell_S11_E47
  Function: 在WAIT FOR NETWORK COMMAND状态下,收到CM SERVICE PROMPT的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.05.31  新版做成
      2.  张志勇     2005.01.27  007037 for MM
      3.  日    期   : 2012年8月10日
          作    者   : L00171473
          修改内容   : DTS2012082204471, TQE清理
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E47(VOS_VOID* pMsg)
{
    MM_MSG_MM_STATUS_STRU          MsgMmStatus;                                 /* MM STATUS 消息结构体                     */
    VOS_UINT8                      aucClassmark2[4];


    PS_MEM_SET(aucClassmark2, 0x00, sizeof(aucClassmark2));


    MM_Fill_IE_ClassMark2(aucClassmark2);

    if (MM_STATUS_DETACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        return;
    }
    Mm_TimerStop( MM_TIMER_T3240 );                                             /* 停TIMER3240                              */

    if ( MM_CONST_NUM_0 == ( aucClassmark2[3] & 0x04 ) )
    {                                                                           /* 不支持CCBS                               */
        MsgMmStatus.MmIeRjctCause.ucRejCause =
            NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE;                            /* Msg type non-existent or not implemented */
        Mm_ComMsgMmStatusSnd( &MsgMmStatus );                                   /* 填充并发送 MM STATUS 消息                */
    }
    else
    {                                                                           /* 支持CCBS                                 */
        Mm_SndCcPromptInd();                                                    /* 向CC发送MMCC_PROMPT_IND                  */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(PROCESS_CM_SERVICE_PROMPT);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E47:NORMAL: STATUS is PROCESS_CM_SERVICE_PROMPT");
        Mm_TimerStart(MM_TIMER_PROTECT_CCBS);
    }

    return;
}

/*******************************************************************************
  Module:   Mm_Cell_S5_E62
  Function: 在MM IDLE ATTEMPTING TO UPDATE状态下,收到MMSMS_EST_REQ的处理
            收到MMSMS_EST_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.06.08  新版做成
      2.  日    期   : 2011年10月27日
          作    者   : s46746
          修改内容   : V7R1 PhaseIII,支持L模联合注册
        3.日    期   : 2012年2月15日
          作    者   : w00166186
          修改内容   : CSFB&PPAC&ETWS&ISR 开发
        4.日    期   : 2012年12月11日
          作    者   : w00176964
          修改内容   : 修改 NAS_MML_GetCsRestrictNormalServiceFlg函数名
        5.日    期   : 2013年2月4日
          作    者   : w00176964
          修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
        6.日    期   :2013年9月12日
          作    者   :z00161729
          修改内容   :DTS2013082903019:支持ss重发功能
        7.日    期   :2014年9月24日
          作    者   :s00217060
          修改内容   :for cs_err_log
        8.日    期   : 2015年1月5日
          作    者   : z00161729
          修改内容   : AT&T 支持DAM特性修改
*******************************************************************************/
VOS_VOID    Mm_Cell_S5_E62( VOS_VOID*pMsg )
{


    if ( MM_FALSE == Mm_RcvSmsEstReq(pMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* 当前小区主叫业务受限则不处理 */
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
        {
            Mm_SndSmsRelInd( g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);/* 通知SMS建立失败                          */
            return;
        }

#if (FEATURE_ON == FEATURE_LTE)

        /* 如果当前驻留LTE,则直接回复SMS失败 */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);/* 通知SMS建立失败                          */

            return;
        }
#endif
        if ( ( MM_CONST_NUM_8 > g_MmSmsEstReq.ulTi )
            || ( MM_CONST_NUM_14 < g_MmSmsEstReq.ulTi ) )
        {                                                                       /* TI不合法                                 */
            Mm_SndSmsRelInd( g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);/* 通知SMS建立失败                          */
            return;
        }
        if (VOS_TRUE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
        {
            /* 不触发重拨的原因值 */
            Mm_SndSmsRelInd( g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);
            return;
        }

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
            = MM_TRUE;
        NAS_MML_SetCsServiceBufferStatusFlg(VOS_TRUE);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                RcvXXEstReq.ulTransactionId
            = g_MmSmsEstReq.ulTi;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallType
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallPri
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat = NAS_MML_GetCurrNetRatType();

        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
        {
            NAS_MM_SndGmmRegisterInit();                                        /* 通知GMM进行注册                          */
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* 设置LU类型                               */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
            Mm_ComLuOnly();                                                 /* LU REQ                                   */
        }
    }


    return;
}

/*******************************************************************************
  Module:   Mm_Cell_S5_E65
  Function: 在MM IDLE ATTEMPTING TO UPDATE状态下,收到MMSS_EST_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.06.08  新版做成
      2.  日    期   : 2011年10月27日
          作    者   : s46746
          修改内容   : V7R1 PhaseIII,支持L模联合注册
      3. 日    期   : 2012年2月15日
         作    者   : w00166186
         修改内容   : CSFB&PPAC&ETWS&ISR 开发
       4.日    期   : 2012年12月11日
         作    者   : w00176964
         修改内容   : 修改 NAS_MML_GetCsRestrictNormalServiceFlg函数名
       5.日    期   : 2013年2月4日
         作    者   : w00176964
         修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
       6.日    期   :2013年9月12日
         作    者   :z00161729
         修改内容  :DTS2013082903019:支持ss重发功能
       7.日    期   : 2014年8月11日
         作    者   : w00167002
         修改内容   : DTS2014080407625:在ATTEMPT TO UPDATE状态也尝试发起普通呼叫。
       8.日    期   :2014年9月24日
         作    者   :s00217060
         修改内容   :for cs_err_log
       9.日    期   : 2015年1月5日
         作    者   : z00161729
         修改内容   : AT&T 支持DAM特性修改
*******************************************************************************/
VOS_VOID    Mm_Cell_S5_E65( VOS_VOID*pMsg )
{
    if ( MM_FALSE == Mm_RcvSsEstReq(pMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* 当前小区主叫业务受限则不处理 */
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

#if (FEATURE_ON == FEATURE_LTE)
        /* 如果当前驻留LTE,则直接回复SS失败 */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {

            /* 在ATTEMPT TO UPDATE状态尝试发起补充业务 */
            NAS_MM_RcvSsEstReq_CSFB();

            return;
        }
#endif
        if ( ( MM_CONST_NUM_8 > g_MmSsEstReq.ulTi )
            || ( MM_CONST_NUM_14 < g_MmSsEstReq.ulTi ) )
        {                                                                       /* TI不合法                                 */
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);

            return;
        }
        if (VOS_TRUE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);
            return;
        }

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
            = MM_TRUE;
        NAS_MML_SetCsServiceBufferStatusFlg(VOS_TRUE);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ulTransactionId
            = g_MmSsEstReq.ulTi;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallType
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallPri
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat = NAS_MML_GetCurrNetRatType();

        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
        {
            NAS_MM_SndGmmRegisterInit();                                        /* 通知GMM进行注册                          */
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* 设置LU类型                               */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
            Mm_ComLuOnly();                                                 /* LU REQ                                   */
        }
    }

    return;
}

/*******************************************************************************
  Module:   Mm_Cell_S22_E24
  Function: 在WAIT FOR RR CONNECTION (LOCATION UPDATING)状态下,收到MMCC_EST_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.06.08  新版做成
      2.  日    期   : 2011年10月27日
          作    者   : s46746
          修改内容   : V7R1 PhaseIII,支持L模联合注册
      3. 日    期   : 2012年2月15日
         作    者   : w00166186
         修改内容   : CSFB&PPAC&ETWS&ISR 开发
      4. 日    期   : 2012年6月9日
         作    者   : z00161729
         修改内容   : DTS2012060705413:V7R1C50 GUL背景搜修改，L下收到系统消息mm迁到location update pending状态
                      未缓存cc呼叫请求
      5.日    期   : 2012年8月14日
        作    者   : z00161729
        修改内容   : DCM定制需求和遗留问题修改,紧急呼叫修改
      6.日    期   : 2012年10月29日
        作    者   : z00161729
        修改内容   : DTS2012083102536:支持cc呼叫重建
      7.日    期   : 2012年12月11日
        作    者   : w00176964
        修改内容   : 修改 NAS_MML_GetCsRestrictNormalServiceFlg函数名
      8.日    期   : 2012年12月21日
        作    者   : L00171473
        修改内容   : DTS2012122007141:L单模时收到呼叫请求直接向CC回复失败
      9.日    期   :2014年9月24日
        作    者   :s00217060
        修改内容   :for cs_err_log
      10.日    期   : 2015年5月6日
         作    者   : z00161729
         修改内容   : 24301 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID    Mm_Cell_S22_E24( VOS_VOID*pMsg )
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

#endif

    if ( MM_FALSE == Mm_RcvCcEstReq(pMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
#if (FEATURE_ON == FEATURE_LTE)
        /* 如果当前为L单模则直接回复CC失败 */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);                              /* 通知CC建立失败                           */
            return;
        }

        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, begin */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            if (LOCATION_UPDATING_PENDING != g_MmGlobalInfo.ucState)
            {
                /* 异常保护:LTE下不会迁移到这几个状态 */
                Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                               NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);                              /* 通知CC建立失败                           */

                return;
            }

            /* 如果当前驻留LTE,MM LOCATION_UPDATING_PENDING状态收到紧急呼叫或普通呼叫需要给LMM
               发起ID_MM_LMM_CSFB_SERVICE_START_NOTIFY，tau注册被拒#17 1次，mm会迁到location update pending */
            NAS_MM_RcvCcEstReq_CSFB();
            return;


            /* DTS2012060705413如果当前驻留LTE,MM LOCATION_UPDATING_PENDING状态收到普通呼叫需要缓存，
               但不给LMM发起ID_MM_LMM_CSFB_SERVICE_START_NOTIFY*/
        }
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, end */
#endif
        /* 非紧急呼，当前小区主叫业务受限则不处理 */
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);                              /* 通知CC建立失败                           */

            return;
        }


        if ( (MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
            ||(MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId))
        {
            /* TI不合法                                 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                              /* 通知CC建立失败                           */
        }
        else
        {                                                                       /* TI合法                                   */
            if ( ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                || ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
                || ( MM_TRUE ==
               g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
                )
            {
                /* 已经存在一个保留的MM连接建立请求         */
                Mm_SndCcRelInd(
                    g_MmCcEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                        /* 通知CC建立失败                           */
            }
            else
            {
                /* 缓存消息 */
                NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);
            }
        }
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S11_E40
  FUNCTION : 在WAIT FOR NETWORK COMMAND 状态下收到
                RRMM_DATA_IND(CM SERVICE ACCEPT)的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-08    新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E40(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    MM_MSG_MM_STATUS_STRU          MsgMmStatus;                                 /* MM STATUS 消息结构体                     */


    MsgMmStatus.MmIeRjctCause.ucRejCause =
        NAS_MML_REG_FAIL_CAUSE_MSG_TYPE_NOT_COMPATIBLE;                                   /* Service option not supported             */
    Mm_ComMsgMmStatusSnd( &MsgMmStatus );                                       /* 填充并发送 MM STATUS 消息                */

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S1_E24
  FUNCTION : 在MM IDLE NO CELL AVAILABLE状态下收到MMCC_EST_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   2004.06.15 新规作成
     4.  张志勇        2005.01.27  007037 for MM
     5.  日    期   : 2011年10月27日
         作    者   : s46746
         修改内容   : V7R1 PhaseIII,支持L模联合注册
     6.  日    期   : 2012年8月13日
         作    者   : z00161729
         修改内容   : DCM定制需求和遗留问题修改,支持L下紧急呼叫
     7.日    期   : 2012年10月29日
       作    者   : z00161729
       修改内容   : DTS2012083102536:支持cc呼叫重建
     8 .日    期   : 2012年12月21日
        作    者   : L00171473
        修改内容   : DTS2012122007141:L单模时收到呼叫请求直接向CC回复失败
     9.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
    10.日    期   : 2014年12月29日
       作    者   : z00161729
       修改内容   : DSDS业务重拨时no rf未触发搜网导致业务失败，
                    mm在no cell available状态no rf时给mmc发送cm service ind触发搜网
    11.日    期   : 2015年8月3日
       作    者   : n00269697
       修改内容   : DTS2015072802941，如果当前驻留LTE，普通呼叫跟紧急呼叫一样，
                    尝试CSFB
*******************************************************************************/
VOS_VOID Mm_Cell_S1_E24(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

#endif


    if ( MM_FALSE == Mm_RcvCcEstReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
#if (FEATURE_ON == FEATURE_LTE)

        /* 如果当前为L单模则直接回复CC失败 */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);                              /* 通知CC建立失败                           */
            return;
        }

        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, begin */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {


            NAS_MM_RcvCcEstReq_CSFB();
            return;
        }
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, end */
#endif

        /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, begin */
        /* 当前no rf时收到业务请求，mm需要通知mmc先触发搜网，普通呼叫需要卡有效，缓存业务请求 */
        if (VOS_TRUE == NAS_MM_IsCcServiceNeedTriggerPlmnSearch())
        /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, end */
        {
            /*缓存该服务请求 */
            NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
            return;
        }

        if ( MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                               NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);        /* 通知CC建立失败                           */
        }
        else
        {
            if ( MM_LIMITED_SERVICE == g_MmGlobalInfo.ucMmServiceState )
            {
                if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                {
                    /* 已经存在一个保留的MM连接建立请求         */
                    Mm_SndCcRelInd(
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST );                     /* 通知CC建立失败                           */

                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
                }

                g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;                                     /* 记录收到建立请求时的状态                 */
                if ( (MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
                    ||(MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId))
                {
                    /* TI不合法                                 */
                    Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                      /* 通知CC建立失败                           */
                }
                else
                {
                    NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
                }
            }
            else
            {
                Mm_SndCcRelInd(
                        g_MmCcEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);                     /* 通知CC建立失败                           */
            }
        }
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E71
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下收到TCMM_TEST_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   2004.06.18 新规作成
*******************************************************************************/

VOS_VOID Mm_Cell_S9_E71(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    TCMM_TEST_REQ_STRU           *pTcmmTestReq;

    pTcmmTestReq = ( TCMM_TEST_REQ_STRU* )pRcvMsg;

    /*WUEPS_TRACE(MM_LOG_LEVEL_4, "ulMode = %d \r",pTcmmTestReq->ulMode);       */

    if ( TC_RB_TEST_ACTIVE == pTcmmTestReq->ulMode )
    {
        Mm_TimerPause(MM_TIMER_STOP_ALL);                                       /* 暂停所有Timer                            */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 原状态迁移                               */
        Mm_ComSetMmState(TEST_CONTROL_ACTIVE);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /*    " \nMM:STATUS is  TEST_CONTROL_ACTIVE\r " );                      */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E71:NORMAL: STATUS is TEST_CONTROL_ACTIVE");
    }

}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E72
  FUNCTION : 在TEST_CONTROL_ACTIVE状态下收到TCMM_DATA_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   2004.06.18 新规作成
*******************************************************************************/

VOS_VOID Mm_Cell_S31_E72(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    TCMM_DATA_REQ_STRU          *pTcmmDataReq;

    pTcmmDataReq = ( TCMM_DATA_REQ_STRU* )pRcvMsg;

    /*WUEPS_TRACE(MM_LOG_LEVEL_4, "SendTcMsg = %d \r",pTcmmDataReq->SendTcMsg.ulTcMsgSize); */

    Mm_SndRrDataReq(
                pTcmmDataReq->SendTcMsg.ulTcMsgSize,
                &pTcmmDataReq->SendTcMsg.aucTcMsg[0],
                RRC_NAS_MSG_PRIORTY_HIGH);                                      /* 将TC的消息传送下去                       */
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E73
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下收到RRMM_DATA_IND(TC MSG)的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   2004.06.18 新规作成

  1.日    期   : 2012年9月21日
    作    者   : z40661
    修改内容   : DTS2012092702799 支持AGPS时，上报TC消息后续TC模块无EST_REQ请求，导致T3240定时器未停止
                 超时后链接释放
*******************************************************************************/

VOS_VOID Mm_Cell_S9_E73(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    RRMM_DATA_IND_STRU          *pRrmmDataInd;

    pRrmmDataInd = ( RRMM_DATA_IND_STRU* )pRcvMsg;


    Mm_TimerStop( MM_TIMER_T3240 );                                             /* 停TIMER3240                              */

    Mm_SndTcDataInd(
                pRrmmDataInd->RcvNasMsg.ulNasMsgSize,
                pRrmmDataInd->RcvNasMsg.aucNasMsg);
}

/*******************************************************************************
  MODULE   : Mm_Cell_S31_E71
  FUNCTION : 在TEST_CONTROL_ACTIVE状态下收到TCMM_TEST_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   2004.06.18 新规作成
     2.  日    期   : 2008年09月03日
         作    者   : l00130025
         修改内容   : 问题单号：AT2D05487,mm注册状态修改
       3.日    期   : 2013年05月15日
         作    者   : s46746
         修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
       4.日    期   : 2013年9月12日
         作    者   : w00242748
         修改内容   : DTS2013090308589:MM处于重建状态时，收到CC REL REQ请求，迁回
                      原状态(IDLE NORMAL SERVICE)，未启动T3212定时器，导致搜网重回
                      G下原小区时做LAU
       5.日    期   : 2015年3月20日
         作    者   : w00167002
         修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                      进行封装。
*******************************************************************************/

VOS_VOID Mm_Cell_S31_E71(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    TCMM_TEST_REQ_STRU          *pTcmmTestReq;

    pTcmmTestReq = ( TCMM_TEST_REQ_STRU* )pRcvMsg;

    /*WUEPS_TRACE(MM_LOG_LEVEL_4, "ulMode = %d \r",pTcmmTestReq->ulMode);       */

    if ( TC_RB_TEST_DEACTIVE == pTcmmTestReq->ulMode )
    {
        Mm_TimerResume(MM_TIMER_STOP_ALL);
        if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
        {
            Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
        }
        else
        {
            switch ( g_MmGlobalInfo.ucMmServiceState )
            {
            case MM_NORMAL_SERVICE:
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                  */
                /*    " \nMM:STATUS is  MM_IDLE_NORMAL_SERVICE\r " );           */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E71:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                break;
            case MM_LIMITED_SERVICE:
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
                /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                  */
                /*    " \nMM:STATUS is  MM_IDLE_LIMITED_SERVICE\r " );          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E71:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
                break;
            case MM_ATTEMPTING_TO_UPDATE:
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E71:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");


                if (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
                {
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }

                break;
            case MM_NO_IMSI:
                Mm_ComSetMmState(MM_IDLE_NO_IMSI);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E71:NORMAL: STATUS is MM_IDLE_NO_IMSI");
                break;
            case MM_DETACHED:
                Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
                /*WUEPS_TRACE(MM_LOG_LEVEL_1,                                   */
                /*    "\nMM:ucState = %d\r", g_MmGlobalInfo.ucState);           */
                PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E71:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
                break;
            default:
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S31_E71:WARNING: g_MmGlobalInfo.ucMmServiceState Abnormal");
                break;
            }
        }
    }

}

/*******************************************************************************
  MODULE   : Mm_Cell_S31_E33
  FUNCTION : 在TEST_CONTROL_ACTIVE状态下收到RRMM_REL_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   2004.06.18 新规作成
     2.  日    期   : 2008年12月26日
         作    者   : o00132663
         修改内容   : 问题单AT2D07880,环回测试时，T3240没有及时停止。
     3.  日    期   : 2011年10月11日
         作    者   : l00171473
         修改内容   : V7R1 phase II, TC环回调整
*******************************************************************************/

VOS_VOID Mm_Cell_S31_E33(
    VOS_VOID                           *pRcvMsg                                 /* 接收消息的头地址                         */
)
{
    /*WUEPS_TRACE(MM_LOG_LEVEL_4, "RRMM_REL_IND = %d \r",RRMM_REL_IND);         */

    Mm_TimerStop( MM_TIMER_T3240 );

    g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_ABSENT;
    Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                             /* RR连接不存在                             */
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

    /* TC状态下收到接入层连接释放消息时，向TC发送TCMM_RR_REL_IND */
    NAS_MM_SndTcRrRelInd();
}


/*******************************************************************************
  MODULE   : Mm_Cell_S0_E21
  FUNCTION : 在NULL状态下收到MMCMM_COVERAGE_LOST_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   2005.01.06 新规作成
*******************************************************************************/

VOS_VOID Mm_Cell_S0_E21(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    if ( MM_FALSE == Mm_RcvMmcCoverageLostInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */                                                        /* 调用异常处理                             */
    }

}


/*******************************************************************************
  MODULE   : Mm_Cell_S3_E34
  FUNCTION : 在MM IDLE NORMAL SERVICE状态下收到RRMM_SECURITY_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   2005.01.06 新规作成
*******************************************************************************/

VOS_VOID Mm_Cell_S3_E34(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    if ( MM_FALSE == Mm_RcvRrcSecurityInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */                                                      /* 调用异常处理                             */
    }

}



/*******************************************************************************
  MODULE   : Mm_Cell_S25_E24
  FUNCTION : 在WAIT FOR RR CONNECTION (IMSI DETACH)状态下收到MMCC_EST_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇        2005.01.27  006045 for MM
     2.日    期   : 2012年10月29日
       作    者   : z00161729
       修改内容   : DTS2012083102536:支持cc呼叫重建
     3.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S25_E24(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    if ( MM_FALSE == Mm_RcvCcEstReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */                                                        /* 调用异常处理                             */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        Mm_SndCcRelInd(
                        g_MmCcEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH );                 /* 通知CC建立失败                           */
    }
    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S22_E13
  FUNCTION : 在WAIT FOR RR CONNECTION (LOCATION UPDATING)状态下收到
                GMMMM_NETWORK_DETACH_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.张志勇    2005.01.27 新规作成
  2.日    期   : 2011年7月22日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  3.日    期   : 2014年4月2日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
*******************************************************************************/
VOS_VOID Mm_Cell_S22_E13(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    GMMMM_NETWORK_DETACH_IND_STRU       *pstNetWkDetachInd;
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    if ( MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT( 0 ); */

        return;
    }

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pRcvMsg;

    g_MmGlobalInfo.ucProc = MM_NET_DETACH_PROC;                                 /* 记录当前的流程                           */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                              */
    /*    " \nMM:MmServiceState is MM_NET_DETACH_PROC \r " );                   */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E13:INFO: MmServiceState is MM_NET_DETACH_PROC");
    if ( GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType )
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
        /* Mm_SndRrRelReq(); */                                                 /* 向RRC发送RRMM_REL_REQ(CS域)              */
        /* Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);  */                         /* 通知MMC，CS域的业务已经停止              */
        Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                                    NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);   /* 记录流程和原因值                         */
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;              /* 设置服务状态                             */
        /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                          */
        /*    " \nMM:MmServiceState is MM_ATTEMPTING_TO_UPDATE \r " );          */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E13:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
        Mm_ComToU2Handle();                                                     /* 调用MM进U2的处理                         */
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);


    }
    else
    {
        switch ( pstNetWkDetachInd->ulDetachCause )
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
            Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                  /* 向RRC发送RRMM_REL_REQ(CS域)              */
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                            /* 通知MMC，CS域的业务已经停止              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            /* Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd->ulDetachCause); */ /* 调用DETACH过程的原因值处理               */
            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* 类似于B模式的全局量                      */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmLikeB is MM_TRUE \r " );    */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E13:INFO: MmLikeB is MM_TRUE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
            Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                  /* 向RRC发送RRMM_REL_REQ(CS域)              */
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                            /* 通知MMC，CS域的业务已经停止              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW);
            /* Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd->ulDetachCause); */ /* 调用DETACH过程的原因值处理               */
            break;
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
            {
                Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
                Mm_ComNetDetachCauseHandle(
                    (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);                              /* 向RRC发送RRMM_REL_REQ(CS域)              */
                Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                        /* 通知MMC，CS域的业务已经停止              */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                NAS_MM_UpdateEquPlmnInfo(pstNetWkDetachInd->ulDetachCause);

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            pstNetWkDetachInd->ulDetachCause);
                /* Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd
                ->ulDetachCause); */                                            /* 调用DETACH过程的原因值处理               */
            }
            break;
        default:
            break;
        }
    }
}

/*******************************************************************************
  MODULE   : Mm_Cell_S23_E13
  FUNCTION : 在LOCATION UPDATING INITIATED状态下收到
                GMMMM_NETWORK_DETACH_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇  2005.01.27 新规作成
     2.  日    期   : 2008年09月03日
         作    者   : l00130025
         修改内容   : 问题单号：AT2D05403,mm注册状态修改
     3.  日    期   : 2013年05月15日
         作    者   : s46746
         修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
     4.  日    期   : 2014年4月2日
         作    者   : w00176964
         修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
     5.  日    期   : 2015年3月20日
         作    者   : w00167002
         修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                      进行封装。
*******************************************************************************/

VOS_VOID Mm_Cell_S23_E13(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    GMMMM_NETWORK_DETACH_IND_STRU       *pstNetWkDetachInd;
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    if ( MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */

        return;
    }

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pRcvMsg;

    if ( GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType )
    {
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
    }
    else if ( GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType )
    {
        Mm_TimerStop(MM_TIMER_T3210);                                           /* 停止T3210                                */
        Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                                    NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);   /* 记录流程和原因值                         */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 记录前状态                               */
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
        Mm_TimerStart(MM_TIMER_T3240);                                          /* 启动TIMER3240                            */
    }
    else
    {
        switch ( pstNetWkDetachInd->ulDetachCause )
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_T3210);                                       /* 停止T3210                                */
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);   /* 记录流程和原因值                         */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* 设置服务状态                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*    " \nMM:MmServiceState is MM_NO_IMSI \r " );                   */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E13:INFO: MmServiceState is MM_NO_IMSI");
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
            Mm_ComToNoImsiHandle();                                             /* 调用删除IMSI的公共处理                   */
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录前状态                               */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */
            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* 类似于B模式的全局量                      */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmLikeB is MM_TRUE \r " );    */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E13:INFO: MmLikeB is MM_TRUE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            Mm_TimerStop(MM_TIMER_T3210);                                       /* 停止T3210                                */
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);   /* 记录流程和原因值                         */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录前状态                               */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */
            NAS_MM_UpdateEquPlmnInfo(pstNetWkDetachInd->ulDetachCause);
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        pstNetWkDetachInd->ulDetachCause);
            break;
        case NAS_MML_REG_FAIL_CAUSE_NULL:
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            break;
        default:
            break;
        }
    }
}

/*******************************************************************************
  MODULE   : Mm_Cell_S0_E16
  FUNCTION : 在NULL状态下收到GMMMM_AUTHENTICATON_FAILURE_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.  张志勇   2005.01.27 新规作成
  2.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
*******************************************************************************/

VOS_VOID Mm_Cell_S0_E16(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )

{
    if ( MM_FALSE == Mm_RcvGmmAuthFailInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0);  */                                                      /* 调用异常处理                             */
        return;
    }

    NAS_MML_SetSimCsRegStatus(VOS_FALSE);


    Mm_ComDelLai();                                                            /* 删除LAI     */
    NAS_MML_InitUeIdTmsiInvalid();
    NAS_MML_SetSimCsSecurityCksn(NAS_MML_CKSN_INVALID);


}

/*******************************************************************************
  MODULE   : Mm_Cell_S0_E33
  FUNCTION : 在NULL状态下收到RRMM_REL_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇        2005.01.10  003020 for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E33(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    if ( MM_FALSE == Mm_RcvRrcRelInd(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */

        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }
    return;
}

/*****************************************************************************
 函 数 名  :  Mm_Cell_S2_E33
 功能描述  : 在MM IDLE PLMN SEARCH状态下
             收到RRMM_REL_IND的处理,此种情况认为AS异常,释放掉所有的MM连接
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2007年9月29日
   作    者   : luojian id:107747
   修改内容   : 新生成函数,根据问题单号 A32D12966
 2.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
 3.日    期   : 2012年2月28日
   作    者   : w00176964
   修改内容   : DTS2012021405430:W下注册PS被拒15，CS注册未完成被网测释放RRC连接，
                后续在W下注册成功后，异常清除了LAC信息，导致在收到新的系统消息异
                常发起了LAU
 4.日    期   : 2012年10月29日
   作    者   : z00161729
   修改内容   : DTS2012083102536:支持cc呼叫重建
 5.日    期   :2013年9月12日
   作    者   :z00161729
   修改内容  :DTS2013082903019:支持ss重发功能
 6.日    期   :2014年9月24日
   作    者   :s00217060
   修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID Mm_Cell_S2_E33(VOS_VOID *pRcvMsg )
{
    VOS_UINT8                           ucValidFlg;

    ucValidFlg                          = Mm_RcvRrcRelInd(pRcvMsg);
    if ( MM_TRUE == ucValidFlg )
    {
        Mm_TimerStop(MM_TIMER_WAIT_CONNECT_REL);

        /* 通知MMC连接不存在 */
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        /* 释放所有MM连接,正在建的MM连接 */
        /* IDLE PLMN SERCH、wait for attach、imsi detach pending等状态收到rel ind，
           底层有异常，CS域应该未注册成功，释放所有的MM连接，不重拨 */
        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);


        /* 需要清除MM保存的GMM的cause值 */
        Mm_ComProcCauseClear();
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S2_E33:WARNING: ulRelCause Abnormal");
    }
}


/*******************************************************************************
  Module:   Mm_Cell_S26_E37
  Function: 在IMSI DETACH INITIATED状态下,
                            收到RRMM_DATA_IND(AUTHENTICATION REJECT)的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.张志勇     2005.01.27  003025 for MM
  2.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  3.日    期   : 2011年7月26日
    作    者   : h44270
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  4.日    期   : 2015年6月8日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*******************************************************************************/

VOS_VOID Mm_Cell_S26_E37(VOS_VOID* pMsg)
{
    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    Mm_ComToNoImsiHandle();
    Mm_TimerStop(MM_TIMER_T3218);                                               /* 停T3218                                  */
    Mm_ComDelRandRes();                                                         /* 删除RAND和RES                            */

    /* 24008_CR1942R3_(Rel-11)_C1-114725 24008 4.3.2.5章节描述如下:
    If the AUTHENTICATION REJECT message is received in any other state the mobile station shall
    abort any MM specific, MM connection establishment or call re-establishment procedure,
    stop any of the timers T3210, or T3230, T3214 or T3216 (if they were running),
    release all MM connections (if any), start timer T3240 and enter the state WAIT FOR NETWORK COMMAND,
    expecting the release of the RR connection. */
    Mm_TimerStop(MM_TIMER_T3214);
    Mm_TimerStop(MM_TIMER_T3216);

    NAS_MM_SndGmmAuthFailInd();
    NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);


    /* 判断DETACH等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                 & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MMC_MM_NO_IMSI);
        /* 清除等待标志 */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

}

/*******************************************************************************
  MODULE   : Mm_Cell_S17_E22
  FUNCTION : 在LOCATION UPDATING PENDING状态下收到MMCMM_DETACH_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.  张志勇   2005.01.07 新规作成
  2.日    期   : 2011年7月26日
    作    者   : h44270
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  3.日    期   : 2012年01月12日
    作    者   : l65478
    修改内容   : 问题单号：DTS2012010602762:SYSCFG设置成支持CS ONLY后
                 PS仍然显示正常服务
*******************************************************************************/

VOS_VOID Mm_Cell_S17_E22(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )

{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;

    if ( MM_FALSE == Mm_RcvMmcDetachReq(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0);  */                                                      /* 调用异常处理                             */

        return;
    }

    pMmcDetachReq = ( MMCMM_DETACH_REQ_STRU* )pRcvMsg;

    if ( MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType )
    {
        /* 在联合RAU过程中，收到DETACH_REQ 消息，GMM不会发起 DETACH过程，MM需要设置标志位 */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_CS_DETACH;
    }
}

/*******************************************************************************
  MODULE   : Mm_Cell_S17_E23
  FUNCTION : 在LOCATION UPDATING PENDING状态下收到MMCMM_POWER_OFF_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   2005.01.07 新规作成

  1.日    期   : 2012年8月24日
    作    者   : z40661
    修改内容   : DTS2012081702937
    2.日    期   : 2012年9月07日
      作    者   : l00171473
      修改内容   : DTS2012081701006, 添加MM关机保护定时器
    3.日    期   : 2013年05月15日
      作    者   : s46746
      修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
    4.日    期   : 2014年04月03日
      作    者   : w00176964
      修改内容   : V3R3C60_eCall项目调整
*******************************************************************************/

VOS_VOID Mm_Cell_S17_E23(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )

{
    if ( MM_FALSE == Mm_RcvMmcPowerOffReq(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */                                                       /* 调用异常处理                             */

        return;
    }

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-7, begin */
#if (FEATURE_ON == FEATURE_LTE)

    /* 如果当前驻留LTE,则直接回复关机 */
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        Mm_SndMmcPowerOffCnf();                                                     /* 向MMC发送MMCMM_POWER_OFF_CNF             */
        Mm_ComSetMmState(MM_NULL);

        return;
    }
#endif

    if (MM_STATUS_DETACHED
            == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        Mm_SndMmcPowerOffCnf();                                                     /* 向MMC发送MMCMM_POWER_OFF_CNF             */

        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-8, begin */
        Mm_ComSetMmState(MM_NULL);
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-8, end */
    }
    else
    {

        Mm_TimerStart(MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT);
    }
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-7, end */


    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                        /* 设置DETACH类型                           */
}

/*******************************************************************************
  MODULE   : Mm_Cell_S25_E76
  FUNCTION : 在WAIT FOR RR CONNECTION (IMSI DETACH)状态下MM_TIMER_PROTECT_DETACH溢出
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.  张志勇        2005.01.27  007037 for MM
  2.  日    期   : 2007年3月20日
      作    者   : s46746
      修改内容   : 问题单号：A32D09497
  3. 日    期   : 2007年06月01日
     作    者   : luojian id:60022475
     修改内容   : 根据问题单A32D10964修改
  4.日    期   : 2008年7月21日
    作    者   : luojian 00107747
    修改内容   : 问题单号：AT2D04201/AT2D04536
  5.日    期   : 2011年7月26日
    作    者   : h44270
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  6.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  7.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  8.日    期   : 2015年7月22日
    作    者   : z00161729
    修改内容   : DTS2015060807763:ap通过cgcatt下发imsi detach，建链失败后mm
                本地detach，回复detach cnf时应该带limit service而不是normal service，
                at命令回复ok而不是error
*******************************************************************************/
VOS_VOID Mm_Cell_S25_E76(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    /*A32D10964==>*/
    MM_MSG_IMSI_DETACH_IND_STRU     Msg;
    if ((MM_DETACH_NEED_DELAY == g_MmGlobalInfo.ucDetachType)
      && (MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg))
    {
        NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));
        Mm_ComMsgImsiDetachIniSndOfDataReq(&Msg);
    }
    /*<==A32D10964*/
    switch(g_MmGlobalInfo.ucDetachType)
    {
        case MM_DETACH_CS_POWEROFF:
        /*A32D10964==>*/
        case MM_DETACH_NEED_DELAY:
        /*<==A32D10964*/
            Mm_ComNasInfoSav(
                             MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());                     /* 设置MM信息                               */

            Mm_SndMmcPowerOffCnf();                                                     /* 向MMC发送MMCMM_POWER_OFF_CNF             */

            Mm_ComSetMmState(MM_STATE_NULL);
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E76:NORMAL: STATUS is  MM_STATE_NULL");
            Mm_TimerStop(MM_TIMER_STOP_ALL);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            {
                MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);
            }

            break;
        case MM_DETACH_CS_NORMAL:
            /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
            if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                         & MM_WAIT_CS_DETACH))
            {
                NAS_MM_SndMmcDetachCnf(MMC_MM_LIMITED_SERVICE);

                /* 清除等待标志 */
                g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
            }
            Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E76:NORMAL: STATUS is",g_MmGlobalInfo.ucState);
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S25_E76:WARNING: Detach type is unexpect.");
            break;

    }
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E75
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下MM_TIMER_PROTECT_AGENT溢出
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇        2005.01.27  007037 for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E75(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    /* WUEPS_ASSERT(0); */
}
/*******************************************************************************
  MODULE   : Mm_Cell_S12_E77
  FUNCTION : 在WAIT FOR RR CONNECTION (MM CONNECTION)状态下MM_TIMER_PROTECT_SIGNALLING溢出
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇        2005.01.27  007037 for MM
     2.  s46746     2006.01.21  根据问题单A32D01682修改

  2.日    期   : 2012年3月2日
    作    者   : z40661
    修改内容   : DTS2012021703361，等待GAS、WAS建链定时器超时后的处理
  3.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  2.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能
  3.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E77(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    /* WUEPS_ASSERT(0); */
    VOS_UINT8 ucCause;
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E77:WARNING: Wait for RRMM_EST_CNF expired");

    if (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == g_MmGlobalInfo.ucState)
    {
        ucCause = NAS_OM_MM_CAUSE_RR_CONN_EST_FAIL;
        NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_LOCATION_UPDATE_FAILURE,
                        &ucCause, NAS_OM_EVENT_LAU_FAIL_LEN);
    }

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;              /* 记录迁移之前的状态                       */


    if (NO_MM_CONN_ESTING !=
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI)
    {
        /* CC发起的RR连接的建立                     */
        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucMMConnEstingTI,
            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);                          /* 通知CC建立失败                           */

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
            NO_MM_CONN_ESTING;

        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E77:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
    }
    else if (NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI)
    {                                                                   /* SS发起的RR连接的建立                     */
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
            NO_MM_CONN_ESTING;

        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E77:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
    }
    else if (NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI)
    {                                                                   /* SMS发起的RR连接的建立                    */
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            ucMMConnEstingTI, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);          /* 通知SMS,MM连接建立失败                   */

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
            NO_MM_CONN_ESTING;

        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E77:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
    }
    else
    {                                                                   /* 没有正在建立的MM连接，即被叫             */

#if (FEATURE_ON == FEATURE_PTM)
        /* 收到CS PAGING后连接建立超时的异常记录 */
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_EST_TIMEOUT);
#endif

        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E77:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
    }

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM连接流程                               */
    g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.ucStaOfRcvXXEstReq;
    Mm_TimerStart(MM_TIMER_T3240);
    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E77:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");

    /* 需要进行LU，则释放缓存的业务 */
    if (MM_TRUE == Mm_ComChkLu())
    {
        if (MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {                                                               /* 有等待的CC触发的需要建立的MM连接         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);                          /* 通知CC建立失败                           */
        }

        if (MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                        RcvXXEstReq.ucFlg )
        {                                                               /* 有等待的CC触发的需要建立的MM连接         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                    RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndSmsRelInd(
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                .RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);
        }
        if (MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                    RcvXXEstReq.ucFlg )
        {                                                               /* 有等待的CC触发的需要建立的MM连接         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                    RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);
        }

    }


}

/*******************************************************************************
  MODULE   : Mm_Cell_S22_E77
  FUNCTION : 在WAIT FOR RR CONNECTION (MM CONNECTION)状态下MM_TIMER_PROTECT_SIGNALLING溢出
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
*******************************************************************************/
VOS_VOID Mm_Cell_S22_E77(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    Mm_RcvRrmmEstCnf();
}
/*******************************************************************************
  MODULE   : Mm_Cell_S14_E77
  FUNCTION : 在WAIT FOR REESTABLISH(WAIT FOR EST_CNF)状态下MM_TIMER_PROTECT_SIGNALLING溢出
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  s46746     2006.04.17  Create

     2.日    期   : 2011年7月14日
       作    者   : zhoujun 40661
       修改内容   : 更新MML_CTX中的业务存在状态

     3.日    期   : 2012年10月29日
       作    者   : z00161729
       修改内容   : DTS2012083102536:支持cc呼叫重建
     4.日    期   :2013年9月12日
       作    者   :z00161729
       修改内容   :DTS2013082903019:支持ss重发功能
     5.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E77(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8 i;
    VOS_UINT8 ucTiValidFlg;

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S14_E77:WARNING: MM_TIMER_PROTECT_SIGNALLING expire at WAIT FOR REESTABLISH(WAIT FOR EST_CNF).");


    /*lint -e701*/
    for (i = 0; i < MM_CONST_NUM_7; i++)
    {                                                                   /* 重建的MM连接                             */
        if ( MM_CONST_NUM_0 !=
        (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
            & ( 0x01 << i ) ) )
        {
            /* 该TI的MM连接正在等待重建                 */
            Mm_SndCcRelInd( i, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);       /* 通知CC,MM连接重建失败                    */
        }
        if ( MM_CONST_NUM_0 !=
        (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
            & ( 0x01 << i ) ) )
        {
            /* 该TI的MM连接正在等待重建                 */
            Mm_SndCcRelInd( ( i + 8 ),NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);/* 通知CC,MM连接重建失败                    */

        }
    }

    /*lint +e701*/

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
        = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
        = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */
    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
    Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
    PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E77:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

    if ( MM_FALSE == Mm_ComChkLu() )
    {

        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
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
        }
        else
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );             /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        Mm_ComCheckDelayMmConn( MM_FALSE );
    }
    else
    {
        if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
        {                                                               /* 有等待的CC触发的需要建立的MM连接         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                            RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);                          /* 通知CC建立失败                           */
        }

        if ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                        RcvXXEstReq.ucFlg )
        {                                                               /* 有等待的CC触发的需要建立的MM连接         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                    RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_SndSmsRelInd(
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                .RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);
        }
        if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                    RcvXXEstReq.ucFlg )
        {                                                               /* 有等待的CC触发的需要建立的MM连接         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                    RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);

        }

    }

    NAS_MM_UpdateCsServiceConnStatusFlg();


}


/*******************************************************************************
  MODULE   : Mm_Cell_S6_E74
  FUNCTION : 在MM IDLE LOCATION UPDATE NEEDED状态下收到RRMM_AC_INFORMATION_CHANGE_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇       2005.01.10  004005 for MM
     2.  日    期   : 2008年09月03日
         作    者   : l00130025
         修改内容   : 问题单号：AT2D05403,mm注册状态修改
     3.  日    期   : 2010年12月05日
         作    者   : o00132663
         修改内容   : 问题单号：DTS2010120400767,W下，CS被bar，PS UNBAR,网络模式II，PDP激活连接后
                      用户手动将CS改为不bar,MM未发起LAU。
       4.日    期   : 2012年2月15日
         作    者   : w00166186
         修改内容   : CSFB&PPAC&ETWS&ISR 开发
       5.日    期   : 2012年12月11日
         作    者   : w00176964
         修改内容   : 更新小区禁止正常业务标记
       6.日    期   : 2013年2月4日
         作    者   : w00176964
         修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
       7.日    期   : 2013年05月15日
         作    者   : s46746
         修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
       8.日    期   : 2015年3月20日
         作    者   : w00167002
         修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                      进行封装。
*******************************************************************************/
VOS_VOID Mm_Cell_S6_E74(VOS_VOID *pRcvMsg)
{
    RRMM_AC_INFO_CHANGE_IND_STRU               *pRrMmAcInfoChgInd;
    VOS_UINT8                                   ucPsRestrictionFlg;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();

    pRrMmAcInfoChgInd = (RRMM_AC_INFO_CHANGE_IND_STRU*)pRcvMsg;

    if ( MM_FALSE == Mm_RcvRrcAcInfoChgInd(pRcvMsg) )
    {
        return;
    }
    if (( RRC_NAS_AC_NOT_BAR == pRrMmAcInfoChgInd->ulAcChangeInd)
     || ( RRC_NAS_T3122_EXPIRE == pRrMmAcInfoChgInd->ulAcChangeInd) )
    {
        if (RRC_NAS_AC_NOT_BAR == pRrMmAcInfoChgInd->ulAcChangeInd)
        {
            NAS_MML_SetCsRestrictRegisterFlg(VOS_FALSE);
            NAS_MML_SetCsRestrictPagingFlg(VOS_FALSE);
            /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
            NAS_MML_SetCsRestrictNormalServiceFlg(VOS_FALSE);
            /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
        }

        if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
         && (VOS_FALSE == ucPsRestrictionFlg))
        {
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录前状态                               */
            Mm_ComSetMmState(MM_WAIT_FOR_ATTACH);

            NAS_MM_SndGmmRegisterInit();
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S6_E74:NORMAL: STATUS is MM_WAIT_FOR_ATTACH");
        }
        else
        {
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if (( VOS_FALSE == NAS_MML_IsCsLaiChanged() )
             && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus) )
            {                                                                   /* 如果LAI不变,更新状态为U1                 */
                if ( MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
                {
                    g_MmGlobalInfo.LuInfo.ucLuType =
                                    MM_IE_LUT_PERIODIC_UPDATING;                /* 设置LU类型                               */
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
                }
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* 设置LU类型                               */
            }

            if ((g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt < MM_CONST_NUM_4)
             || (RRC_NAS_AC_NOT_BAR == pRrMmAcInfoChgInd->ulAcChangeInd))
            {
                Mm_ComLuOnly();                                                 /* 发送LU REQ                               */
            }

            if (g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt >= MM_CONST_NUM_4)
            {
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            }
        }
    }
}

/*******************************************************************************
  MODULE   : Mm_Cell_S0_E24
  FUNCTION : 在NULL状态下收到MMCC_EST_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇        2005.01.08  001030 for MM
     2.日    期   : 2012年10月29日
       作    者   : z00161729
       修改内容   : DTS2012083102536:支持cc呼叫重建
     3.日    期   :2013年9月12日
       作    者   :z00161729
       修改内容   :DTS2013082903019:支持ss重发功能
     4.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E24(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    if ( MM_FALSE == Mm_RcvCcEstReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */                                                     /* 调用异常处理                             */
        return;
    }
    else
    {
        /* 消息检查结果成功                         */
        Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);                      /* 通知CC建立失败                           */
    }
    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S10_E40
  FUNCTION : 在MM CONNECTION ACTIVE状态下收到RRMM_REL_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇        2005.01.11  Status for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E40(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    MM_MSG_MM_STATUS_STRU    Msg;

    Msg.MmIeRjctCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_MSG_TYPE_NOT_COMPATIBLE;

    Mm_ComMsgMmStatusSnd(&Msg);
}

/*******************************************************************************
  Module:   Mm_Cell_S31_E1
  Function: 在TEST_CONTROL_ACTIVE状态下,收到MMCMM_START_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2005.01.27  新版作成
  2.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  3.日    期   : 2012年8月29日
    作    者   : l00171473
    修改内容   : DTS2012081701006, TC状态开机时不发送REL_REQ
  4.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  5.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  6.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容  :DTS2013082903019:支持ss重发功能
  7.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/

VOS_VOID Mm_Cell_S31_E1(VOS_VOID* pMsg)
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {


        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */
        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-8, begin */

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-8, end */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E1:NORMAL: STATUS is MM_STATE_NULL");

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        Mm_ComNasInfoSav(
                MM_STATUS_DETACHED,
                NAS_MML_GetSimCsSecurityCksn()
                );
        Mm_ComInit();                                                           /* 全局变量初始化                           */
        Mm_ComStart();                                                          /* 调用收到MMCMM_START_REQ的公共处理        */
    }
    else
    {
        /* WUEPS_ASSERT(0); */
    }
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module:   Mm_Cell_S0_E78
  Function: 在MM NULL状态下,收到MM_AGENT_INQUIRE的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2005.01.28  新版作成
      2. 日    期   : 2007年01月26日
         作    者   : h44270
         修改内容   : 问题单号：A32D08575,该问题属于演示性质,后续还要修改
*******************************************************************************/

VOS_VOID Mm_Cell_S0_E78(VOS_VOID* pMsg)
{
#if 0
    PS_OM_MSG_HEAD_STRU *pNewMsg;
    pNewMsg = (PS_OM_MSG_HEAD_STRU *)pMsg;

    switch (pNewMsg->ulMsgID)
    {
        case AGENT_MM_INQUIRE:
            Mm_RcvMmAgentInquire(pMsg);
            break;
        case MM_TRANS_STATUS_INFO_REQ:
            Mm_SndAgentTransInfo(pNewMsg);
            break;
        default:
            break;
    }
#endif
}
/*******************************************************************************
  Module:   Mm_Cell_S31_E23
  Function: 在TEST_CONTROL_ACTIVE状态下,收到MMCMM_POWER_OFF_REQ的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2005.01.28  新规做成
  2. 日    期   : 2007年3月20日
     作    者   : s46746
     修改内容   : 问题单号：A32D09497
  3. 日    期   : 2007年08月19日
     作    者   : luojian id:60022475
     修改内容   : 根据问题单号：A32D12706
  4. 日    期   : 2008年09月03日
     作    者   : l00130025
     修改内容   : 问题单号：AT2D05403,mm注册状态修改
  5.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  6.日    期   : 2012年3月15日
    作    者   : w00166186
    修改内容   : V7R1 C50 CSFB&PPAC&ETWS&ISR开发
  7.日    期   : 2012年9月07日
    作    者   : l00171473
    修改内容   : DTS2012081701006, 添加MM关机保护定时器
  8.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  9.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
 10.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 11.日    期   :2013年9月12日
   作    者   :z00161729
   修改内容  :DTS2013082903019:支持ss重发功能
 12.日    期   : 2014年6月13日
   作    者   : w00242748
   修改内容   : DSDS 新特性
 13.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/

VOS_VOID Mm_Cell_S31_E23(VOS_VOID* pMsg)
{

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if ( MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg) )
    {
        return;
    }


    /* TC状态下收到关机请求时，主动发起REL_REQ */
    if ( g_MmGlobalInfo.ucCsSigConnFlg == MM_CS_SIG_CONN_PRESENT )
    {
        NAS_MM_SndTcRrRelInd();

        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    }


    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
    {                                                                           /* 如果为A+I模式                            */
        if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
         && (MM_FALSE == g_MmGlobalInfo.ucLikeB)
         && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
        {

            Mm_TimerStart(MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT);
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                /* 设置DETACH类型                           */
            return;                                                             /* 不是类似B或者A+II模式的场合              */
        }
    }
    Mm_TimerStop(MM_TIMER_STOP_ALL);
    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                        /* 设置DETACH类型                           */

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
    {
        if ( MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg )
        {
            if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
            {
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                /* ==>A32D12706 */
                Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
                Mm_ComSetMmState(IMSI_DETACH_INITIATED);
                /* <==A32D12706 */
            }
            else
            {
                MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);
                Mm_SndMmcPowerOffCnf();
                Mm_ComSetMmState(MM_STATE_NULL);

            }
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                    /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S31_E23:INFO: MmServiceState is MM_NO_SERVICE");
            Mm_ComNasInfoSav(
                             MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());             /* 设置MM信息                               */


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E23:NORMAL: STATUS is MM_STATE_NULL");
        }
        else
        {
            if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
            {
                NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

                Mm_ComSetMmState(IMSI_DETACH_INITIATED);

                Mm_ComMsgImsiDetachIniSndOfDataReq(&Msg);                       /* 填写消息,发送消息                        */
                Mm_TimerStart(MM_TIMER_T3220);                                  /* 启动保护定时器                           */
                Mm_TimerStart(MM_TIMER_PROTECT_DETACH);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E23:NORMAL: STATUS is IMSI_DETACH_INITIATED");
            }
            else
            {
                NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
                Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);

                Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                        /* 填写消息,发送消息                        */
                Mm_TimerStart(MM_TIMER_PROTECT_DETACH);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E23:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
            }

        }
    }
    else
    {
        if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        }
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S31_E23:INFO: MmServiceState is MM_NO_SERVICE");
        Mm_ComNasInfoSav(
                         MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* 设置MM信息                               */
        Mm_SndMmcPowerOffCnf();
        Mm_ComSetMmState(MM_STATE_NULL);
        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);
        }

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E23:NORMAL: STATUS is MM_STATE_NULL");
    }
}

/*******************************************************************************
  MODULE   : Mm_Cell_S12_E79
  FUNCTION : 在WAIT FOR RR CONNECTION (MM CONNECTION)状态下MM_TIMER_PROTECT_CC溢出
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇        2005.01.28  新规做成
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E79(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

}

/*******************************************************************************
  MODULE   : Mm_Cell_S13_E79
  FUNCTION : 在WAIT FOR REESTABLISH(WAIT FOR REEST REQ)状态下MM_TIMER_PROTECT_CC溢出
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  s46746        2006.04.17  Create
     2.日    期   : 2012年10月29日
       作    者   : z00161729
       修改内容   : DTS2012083102536:支持cc呼叫重建
     3.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S13_E79(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8 ucTiValidFlg;

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S13_E79:WARNING: MM_TIMER_PROTECT_CC expire at WAIT FOR REESTABLISH(WAIT FOR REEST REQ).");

    Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
    PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S13_E79:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

    Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR连接不存在                             */
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    Mm_ComProcCauseProcess();

    if ( MM_FALSE == Mm_ComChkLu() )
    {
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                      .RcvXXEstReq.ucFlg))
        {
            ucTiValidFlg = Mm_ComTiChk();
            if ( MM_FALSE == ucTiValidFlg )
            {
                Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );     /* RR连接不存在                             */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
            else
            {
                Mm_ComSigRelForDelayMmConnRej();
            }
        }
        Mm_ComCheckDelayMmConn( MM_FALSE );
    }
    else
    {
        if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                    RcvXXEstReq.ucFlg )
        {                                                           /* 有等待的CC触发的需要建立的MM连接         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                    RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndCcRelInd(
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT);                      /* 通知CC建立失败                           */
        }
        if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                    RcvXXEstReq.ucFlg )
        {                                                           /* 有等待的CC触发的需要建立的MM连接         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                    RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_SndSmsRelInd(
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                .RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT);
        }
        if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                    RcvXXEstReq.ucFlg )
        {                                                           /* 有等待的CC触发的需要建立的MM连接         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                    RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT);
        }
    }

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT);
}


/*******************************************************************************
  MODULE   : Mm_Cell_S9_E15
  FUNCTION : 在WAIT_FOR_OUTGOING_MM_CONNECTION状态下GMMMM_LU_INITIATION溢出
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇        2005.01.28  新规做成
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E15(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    GMMMM_LU_INITIATION_STRU    *pstMmcLuIni;

    if ( MM_FALSE == Mm_RcvGmmLuIni(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */                                                      /* 异常错误处理                             */
        return;
    }

    pstMmcLuIni = ( GMMMM_LU_INITIATION_STRU* )pRcvMsg;

    if ( GMMMM_T3312_EXPIRED == pstMmcLuIni->enTimerExpiredFlg )
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S9_E5
  Function: 在WAIT_FOR_OUTGOING_MM_CONNECTION状态下,
            接收到MMCMM_SYS_INFO_IND的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2005.02.01  新版做成
      2.  日    期   : 2006年10月6日
          作    者   : s46746
          修改内容   : 问题单号：A32D05960
      3.  日    期   : 2009年05月25日
          作    者   : l65478
          修改内容   : 问题单:AT2D10870,在MM连接建立过程中发生LAI改变,没有发起LU,导致呼叫失败
      4.  日    期   : 2009年8月25日
          作    者   : 欧阳飞 00132663
          修改内容   : AT2D14050,【NAS R6协议升级测试】驻留后系统消息改变，指示DSAC PS域被BAR，
                       拨打普通电话,通话期间T3312超时，释放后发起了错误的周期性LAU。
      5.  日    期   : 2010年10月11日
          作    者   : w00166186
          修改内容   : DTS2010093000095,通话过程LAI改变，通话结束后第一次LAU总是失败。
      6.  日    期   : 2010年11月22日
          作    者   : h44270
          修改内容   : DTS201011700067,没有处理系统消息，导致电话挂断后，没有发起LAU。
      7.  日    期   : 2013年2月4日
          作    者   : w00176964
          修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
      8.  日    期   : 2014年04月1日
          作    者   : w00176964
          修改内容   : V3R3C60_eCall项目:系统消息处理优化
*******************************************************************************/

VOS_VOID Mm_Cell_S9_E5(VOS_VOID* pMsg)
{
    MMCMM_SYS_INFO_IND_STRU            *pstSysInfoMsg;

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-1, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-1, end */

    g_MmGlobalInfo.ucConnRcvSysFlg = MM_TRUE;

    /* G下在该状态收到系统消息在预处理丢弃，因此只会在W下收到该消息 */
    pstSysInfoMsg   = (MMCMM_SYS_INFO_IND_STRU*)pMsg;

    /* 如果当前CS注册变为受限，需要重新设置建链前状态 */
    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        if (MM_IDLE_NO_IMSI != g_MmGlobalInfo.ucStaOfRcvXXEstReq)
        {
            g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_LOCATION_UPDATE_NEEDED;
        }
    }

    /* 如果当前CS注册变为不受限，需要重新设置建链前状态 */
    if (VOS_TRUE == pstSysInfoMsg->ucCsChanged2UnBarFlg)
    {
        NAS_MM_UpdateMmStateCsRegRestrictBarToUnbar();
    }
    /* MM处于通话中，PS域bar，期间T3312超时，GMM会通知MM，此时MM会将T3212超时标志
       置位TRUE,此后如果PS又从bar转为不bar, MM需要将T3212超时标志清除掉。
       否则，当通话结束时，Mm_ComChkLu函数 检测到该标志位后，会发起不期望的LU过程。 */
    if (  (VOS_TRUE == pstSysInfoMsg->ucPsChanged2UnBarFlg)
        &&(MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg ))
    {
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, begin */
        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, end */
        {
            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;
        }
    }

    if (VOS_TRUE == pstSysInfoMsg->ucCsChanged2UnBarFlg)
    {
        NAS_MM_UpdateMmStateCsRegRestrictBarToUnbar();
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S12_E5
  Function: 在WAIT_FOR_RR_CONNECTION_MM_CONNECTION状态下,
            接收到MMCMM_SYS_INFO_IND的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.z40661     2009.07.23  新版做成
  2.日    期   : 2009年08月07日
    作    者   : o00132663
    修改内容   : 问题单:AT2D13560,在MM连接建立过程中发生LAI改变,没有发起LU,导致呼叫失败
  3.日    期   : 2010年05月14日
    作    者   : l65478
    修改内容   : 问题单号:AT2D19292,MM在寻呼建立连接时，收到系统信息，把状态迁到NORMAL状态，导致GCF失败
  4.日    期   : 2011年7月22日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  5.日    期   : 2011年05月13日
    作    者   : f00179208
    修改内容   : 问题单号：DTS201104300028，出服务区拨打紧急呼，释放紧急呼后MM异常重启了T3212
  6.日    期   : 2011年03月18日
    作    者   : c00173809
    修改内容   : 问题单号：DTSs2011031600590，在无H3G信号区域,紧急呼概率不成功
  7.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
  8.日    期   : 2012年10月22日
    作    者   : t00212959
    修改内容   : DTS2012101907218:NAS向接入层发送LAU请求时，Establishment cause按照协议写为Registration
  9.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
 10.日    期   : 2013年7月21日
    作    者   : w00242748
    修改内容   : DTS2013071802235:拨号过程中，异系统切换到G，位置区变化，进行LAU后，重新发送拨号请求
 11.日    期   : 2013年08月15日
    作    者   : l65478
    修改内容   : DTS2013081404782MM业务结束后没有通知GMM CS业务结束
 12.日    期   : 2013年09月03日
    作    者   : l65478
    修改内容   : DTS2013041602825:CSFB连接建立失败后没有发起LU
 13.日    期   :2013年9月23日
    作    者   :w00242748
    修改内容   :DTS2013091407626:W下UE被叫，未收到网侧建联CNF前，发生重定向到G后，未发起LAU
 14.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能
 15.日    期   : 2013年12月5日
    作    者   : w00167002
    修改内容   : DTS2013113006231:W下，开机在LAC1上注册成功，重选到LAC2上，CS注册成功
                  PS注册被拒#13,重选回LAC1上，注册成功。丢网后任意小区驻留在LAC2
                  上，不发起注册，重选回LAC1上，检测不发起注册。
                  修改为在收到系统消息时候，不进行UPDATE状态的更新。

                  删除函数Mm_ComIsLaiForbidden，复用封装函数NAS_MM_ProcNoGprsForbidenFlg_RcvSysInfoInd
 16.日    期   : 2014年04月1日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目:系统消息处理优化
 17.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
 18.日    期   :2015年5月21日
    作    者   :b00269685
    修改内容   :若LAI变化缓存一下paging
*******************************************************************************/

VOS_VOID Mm_Cell_S12_E5(VOS_VOID* pMsg)
{
    VOS_UINT8                           ucLaiChange;
    VOS_UINT32                          ulCsServExist;

    VOS_UINT32                          ulCsfbEmgCallLaiChgLauFirstFlg;

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-1, begin */
    ucLaiChange    = NAS_MML_IsCsLaiChanged();
    ulCsServExist  = Mm_ComJudgeCsServExist();
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-1, end */

    /* 如果当前CS注册变为受限，需要重新设置建链前状态 */
    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        if (MM_IDLE_NO_IMSI != g_MmGlobalInfo.ucStaOfRcvXXEstReq)
        {
            g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_LOCATION_UPDATE_NEEDED;
        }
    }

    /* 如果当前CS注册变为不受限，需要重新设置建链前状态 */
    if (NAS_MML_RESTRICTION_BAR_TO_UNBAR == NAS_MML_GetCsRegisterBarToUnBarFlg())
    {
        NAS_MM_UpdateMmStateCsRegRestrictBarToUnbar();
    }

    /* 驻留受限网络，且当前无紧急呼，返回 */
    if (MM_CS_SERV_EMERGENCY_CALL_EXIST == ulCsServExist)
    {

        g_MmGlobalInfo.ucConnRcvSysFlg = MM_TRUE;

        /* 正常驻留，出服务区，拨打紧急呼，在建链过程中紧急驻留到受限小区，状态未刷新，导致T3212被异常
           停止，并且紧急呼结束后错误上报正常服务状态 */
        if ( (MMCMM_NO_FORBIDDEN != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
          && (MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg) )
        {
            if (MM_IDLE_NO_IMSI != g_MmGlobalInfo.ucStaOfRcvXXEstReq)
            {
                g_MmGlobalInfo.ucMmServiceState   = MM_LIMITED_SERVICE;
                g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_LIMITED_SERVICE;
            }

            return;
        }

        ulCsfbEmgCallLaiChgLauFirstFlg = NAS_MML_GetCsfbEmgCallLaiChgLauFirstFlg();

        if ((VOS_FALSE == NAS_MML_GetCsRestrictRegisterFlg())
         && (VOS_TRUE == ucLaiChange)
         && (VOS_TRUE == ulCsfbEmgCallLaiChgLauFirstFlg))
        {
            g_MmGlobalInfo.ucPendingLu  = VOS_TRUE;
            g_MmGlobalInfo.ucConnRcvSysFlg = MM_TRUE;

            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);
        }

        return;
    }

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-17, begin */
    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-17, end */
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_LA);

        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
    }
    else
    {
        /* 无异系统切换，正常业务建链过程中发生位置区改变 */
        if ((VOS_FALSE == NAS_MML_GetCsRestrictRegisterFlg())
         && (VOS_TRUE == ucLaiChange))
        {
            g_MmGlobalInfo.ucPendingLu  = VOS_TRUE;
            g_MmGlobalInfo.ucConnRcvSysFlg = MM_TRUE;

            g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_TRUE;

            /* 释放连接，在连接释放后，首先进行LU/RAU，然后继续处理呼叫消息 */
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);
            return;
        }

        /* 如果cs update状态是U0,LAI未发生变化，上报注册结果
           对应场景: LAU过程中(LOCATION UPDATING INITIATED状态)收到业务请求，缓存
           未收到LAU accept，直接rel ind，MM迁到idle normal service状态，处理缓存的业务请求
           业务建链过程中(WAIT FOR RR CONNECTION (MM CONNECTION)状态)收到系统消息，补报注册成功
           否则在电话过程中，界面会显示无服务或限制服务 */
        if ((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
         && (VOS_FALSE == ucLaiChange)
         && (MM_NORMAL_SERVICE == g_MmGlobalInfo.ucMmServiceState))
        {
            /* 向MMC发送MMCMM_LU_RESULT_IND */
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_SUCCESS,
                                        NAS_MML_REG_FAIL_CAUSE_LOCAL_NULL);

            /* 向GMM发送MMGMM_LU_RESULT_IND */
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_LOCAL_NULL);
        }
    }
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S10_E50
  FUNCTION : 在MM_CONNECTION_ACTIVE状态下
             收到RRMM_DATA_IND( CM Message)的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      2005.02.02  新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E50(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8   ucTI = 0;                                                           /* CC消息中的TI                             */
    RRMM_DATA_IND_STRU *pRrDataInd = ( RRMM_DATA_IND_STRU *) pRcvMsg;           /* 消息RRMM_DATA_IND的结构体指针            */
    VOS_UINT8   *pucCMMsg = VOS_NULL_PTR;                                                   /* 指针类型转换                             */
    VOS_UINT8   *pucBakCMMsg = VOS_NULL_PTR;

    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* 停T3212                                  */
    }

    pucCMMsg = (VOS_UINT8 *)MM_MEM_ALLOC(
                           VOS_MEMPOOL_INDEX_MM,
                           pRrDataInd->RcvNasMsg.ulNasMsgSize,
                           WUEPS_MEM_NO_WAIT);                                  /* 申请内存                                 */
    if( VOS_NULL_PTR == pucCMMsg )
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S10_E50:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }

    /*lint -e701*/
    pucBakCMMsg = pucCMMsg;
    PS_MEM_SET(pucCMMsg, 0,
        sizeof( VOS_UINT8 ) * pRrDataInd->RcvNasMsg.ulNasMsgSize );                 /* 初始化内存                               */
    PS_MEM_CPY (pucCMMsg, & ( pRrDataInd->RcvNasMsg.aucNasMsg[0] ),
        pRrDataInd->RcvNasMsg.ulNasMsgSize );                                   /* 得到消息内容                             */
    ucTI = ( VOS_UINT8 )( ( ( pucCMMsg[0] & 0xf0 ) >> 4 ) );                        /* 得到CC消息中的TI                         */
    if ( ( MM_CONST_NUM_7 == ucTI ) || ( MM_CONST_NUM_15 == ucTI ) )
    {                                                                           /* TIO = 111                                */
        Mm_SndCcEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg );  /* 向CC发送MMCC_EST_IND                     */
    }
    if ( MM_CONST_NUM_7 > ucTI )
    {                                                                           /* 网侧建立的MM连接                         */
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
            & ( 0x01 << ucTI ) ) )
        {                                                                       /* 该连接存在                               */
            Mm_SndCcDataInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* 向CC发送MMCC_DATA_IND                    */
        }
        else
        {                                                                       /* 该连接不存在                             */
            Mm_SndCcEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* 向CC发送MMCC_EST_IND                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] |=
                ( VOS_UINT8 )( 0x01 << ucTI );                                      /* 设置已经存在的MM连接的标志位             */
            Mm_ComCheckDelayMmConn( MM_FALSE );
        }
    }
    else if ( ( MM_CONST_NUM_7 < ucTI ) && ( MM_CONST_NUM_15 > ucTI ) )
    {                                                                           /* CC建立的MM连接                           */
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
            & ( 0x01 << ( ucTI - 8 ) ) ) )
        {                                                                       /* 该连接存在                               */
            Mm_SndCcDataInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
                pucCMMsg );                                                     /* 向CC发送MMCC_DATA_IND                    */
        }
        else
        {                                                                       /* 该连接不存在                             */
            Mm_SndCcEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* 向CC发送MMCC_EST_IND                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] |=
                ( VOS_UINT8 )( 0x01 << ( ucTI - 8 ) );                              /* 设置已经存在的MM连接的标志位             */
            Mm_ComCheckDelayMmConn( MM_FALSE );
        }
    }
    else
    {

    }


    /*lint +e701*/

    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg );                                /* 释放申请的消息                           */

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S5_E80
  FUNCTION : 在MM IDLE ATTEMPTING TO UPDATE,WAIT FOR NETWORK COMMAND状态下收到
             MMSS_ABORT_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
       1.日    期   : 2007年3月9日
         作    者   : luojian id:60022475
         修改内容   : 根据问题单A32D09099创建
       2.日    期   : 2012年2月29日
         作    者   : w00167002
         修改内容   : V7R1C50 支持CSFB特性修改:
                      当前存在补充业务的CSFB流程，则清空CSFB存在标志
       3.日    期   : 2014年6月13日
         作    者   : w00242748
         修改内容   : DSDS 新特性
       4.日    期   : 2014年9月23日
         作    者   : z00161729
         修改内容   : DTS2014092302846:L下拨打电话搜网到w下被#12拒绝的小区，电话失败后重选回l，mm会给cc多发一次mmcc rel ind
       5.日    期   : 2016年2月2日
         作    者   : z00359541
         修改内容   : DTS2016011809099:不需要发送CSFB ABORT消息打断状态机，CSFB结束后收到SS STARTUS NOTIFY消息时会打断
*******************************************************************************/
VOS_VOID Mm_Cell_S5_E80(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSsAbortReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
        ;
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                      .RcvXXEstReq.ucFlg)
         && (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo
                .ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId))
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                             .RcvXXEstReq.ucFlg = MM_FALSE;

            if (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI)
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI = NO_MM_CONN_ESTING;
            }

#if (FEATURE_ON == FEATURE_LTE)

            /* 当前存在补充业务的CSFB流程，则清空CSFB存在标志 */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
                {
                    /* 通知L CSFB 流程终止 */
                    NAS_MM_SndLmmCsfbServiceAbortNotify();
                }

            }
#endif
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }
    return;
}

/*****************************************************************************
 函 数 名  : Mm_Cell_S32_E80
 功能描述  : 在MM_INTER_RAT_CHANGE状态收到ss abort req消息处理
 输入参数  : pRcvMsg - 收到的原语头指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月22日
    作    者   : z00161729
    修改内容   : DTS2014050601476:L打电话重定向到g过程中电话挂断，mm缓存cc abort，g查询csfb状态是存在，lau结束后没有启动自主FR流程到L
  2.日    期   : 2014年6月13日
    作    者   : w00242748
    修改内容   : DSDS 新特性
*****************************************************************************/
VOS_VOID Mm_Cell_S32_E80(
    VOS_VOID                           *pRcvMsg
)
{
    if (WAIT_FOR_OUTGOING_MM_CONNECTION == g_MmGlobalInfo.ucSuspendPreState)
    {
        Mm_Cell_S32_DataTransfer(pRcvMsg);
        return;
    }

    if ( MM_FALSE == Mm_RcvSsAbortReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
        ;
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                      .RcvXXEstReq.ucFlg)
         && (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo
                .ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId))
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                             .RcvXXEstReq.ucFlg = MM_FALSE;

            NAS_MM_SndRrMmServiceAbortNotify(WUEPS_PID_WRR);
            NAS_MM_SndRrMmServiceAbortNotify(UEPS_PID_GAS);

#if (FEATURE_ON == FEATURE_LTE)

            /* 当前存在补充业务的CSFB流程，则清空CSFB存在标志 */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
                {
                    /* 通知L CSFB 流程终止 */
                    NAS_MM_SndLmmCsfbServiceAbortNotify();
                }
            }
#endif
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }
    return;
}




/*******************************************************************************
  MODULE   : Mm_Cell_S9_E80
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下收到MMSS_ABORT_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   05-02-01  新版作成
     2.日    期   : 2012年2月29日
       作    者   : w00167002
       修改内容   : V7R1C50 支持CSFB特性修改:
                      当前存在补充业务的CSFB流程，则清空CSFB存在标志
     3.日    期   : 2014年7月7日
       作    者   : w00242748
       修改内容   : DSDS III新特性
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E80(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSsAbortReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI ==
            g_MmSsAbortReq.ulTransactionId )
        {                                                                       /* 终止的MM连接建立是正在建立的             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* 停T3230                                  */
            Mm_ComMsgCmSvcAbortSnd();
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* 清除正在建立的MM连接的标志               */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* 返回到接收到建立MM连接请求时的状态       */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM连接流程                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                      */
            /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E80:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */

#if (FEATURE_ON == FEATURE_LTE)

            /* 当前存在补充业务的CSFB流程，则清空CSFB存在标志 */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
            }
#endif
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;

#if (FEATURE_ON == FEATURE_LTE)

                /* 当前存在补充业务的CSFB流程，则清空CSFB存在标志 */
                if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
                {
                    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                }
#endif

            }
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S5_E81
  FUNCTION : 在MM IDLE ATTEMPTING TO UPDATE,WAIT FOR NETWORK COMMAND状态下收到
             MMSMS_ABORT_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
      1. 日    期   : 2007年3月9日
         作    者   : luojian id:60022475
         修改内容   : 根据问题单A32D09099创建
*******************************************************************************/
VOS_VOID Mm_Cell_S5_E81(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSmsAbortReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
        ;
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
          && (g_MmSmsAbortReq.ulTransactionId == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId) )
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E81
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下收到MMSMS_ABORT_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   05-02-01  新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E81(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSmsAbortReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI ==
            g_MmSmsAbortReq.ulTransactionId )
        {                                                                       /* 终止的MM连接建立是正在建立的             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* 停T3230                                  */
            Mm_ComMsgCmSvcAbortSnd();
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* 清除正在建立的MM连接的标志               */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* 返回到接收到建立MM连接请求时的状态       */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM连接流程                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                      */
            /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E81:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAN");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();
        }
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S10_E80
  FUNCTION : 在MM CONNECTION ACTIVE状态下收到MMSS_ABORT_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   05-02-01  新版作成

     2.日    期   : 2011年7月14日
       作    者   : zhoujun 40661
       修改内容   : 更新MML_CTX中的业务存在状态
     3.日    期   : 2012年2月29日
       作    者   : w00167002
       修改内容   : V7R1C50 支持CSFB特性修改:
                     当前存在补充业务的CSFB流程，则清空CSFB存在标志
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E80(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSsAbortReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */

        /*lint -e701*/

        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
        /*    & (0x01 << ( g_MmCcAbortReq.ulTransactionId - 8 )))) */
            & (0x01 << ( g_MmSsAbortReq.ulTransactionId - 8 ))))
        {                                                                       /* 终止的MM连接建立是正在建立的             */
            if ( ( ( 0x01 << ( g_MmSsAbortReq.ulTransactionId - 8 ) ) ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] )
                &&(0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] ) )
            {
                Mm_ComMsgCmSvcAbortSnd();
                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                               g_MmGlobalInfo.ucStaOfRcvXXEstReq;               /* 返回到接收到建立MM连接请求时的状态       */
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM连接流程                               */
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;           /* 记录迁移之前的状态                       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                  */
                /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );         */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E80:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                  /* 启动TIMER3240                            */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] = 0;
            }
            else
            {
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM连接流程                               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
                    &= ~(VOS_UINT32)(0x01 << ( g_MmSsAbortReq.ulTransactionId - 8 ));
            }

#if (FEATURE_ON == FEATURE_LTE)

            /* 当前存在补充业务的CSFB流程，则清空CSFB存在标志 */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
            }
#endif

        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;

#if (FEATURE_ON == FEATURE_LTE)

                /* 当前存在补充业务的CSFB流程，则清空CSFB存在标志 */
                if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
                {
                    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                }
#endif

            }
        }

        /*lint +e701*/

    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S10_E81
  FUNCTION : 在MM CONNECTION ACTIVE状态下收到MMSMS_ABORT_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   05-02-01  新版作成

     2.日    期   : 2011年7月14日
       作    者   : zhoujun 40661
       修改内容   : 更新MML_CTX中的业务存在状态
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E81(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSmsAbortReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /*lint -e701*/

        if ( 0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
            & ( 0x01 << ( g_MmCcAbortReq.ulTransactionId - 8 ) ) ) )
        {                                                                       /* 终止的MM连接建立是正在建立的             */
            if ( ( ( 0x01 << ( g_MmSmsAbortReq.ulTransactionId - 8 ) ) ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] )
                &&(0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] ) )
            {
                Mm_ComMsgCmSvcAbortSnd();
                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                               g_MmGlobalInfo.ucStaOfRcvXXEstReq;               /* 返回到接收到建立MM连接请求时的状态       */
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM连接流程                               */
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;           /* 记录迁移之前的状态                       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                  */
                /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );         */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E81:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                  /* 启动TIMER3240                            */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                    aucMMConnExtFlg[1] = 0;
            }
            else
            {
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM连接流程                               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
                &= ~(VOS_UINT32)(0x01 << ( g_MmSmsAbortReq.ulTransactionId - 8 ));
            }
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmSmsAbortReq.ulTransactionId ==
             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
                                                            ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }
        }

        /*lint +e701*/

    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S12_E80
  FUNCTION : 在WAIT FOR RR CONNECTION (MM CONNECTION)状态下收到MMSS_ABORT_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   05-02-01  新版作成
     2.日    期   : 2012年2月29日
       作    者   : w00167002
       修改内容   : V7R1C50 支持CSFB特性修改:
                     当前存在补充业务的CSFB流程，则清空CSFB存在标志
     3.日    期   :2013年8月13日
       作    者   :z00161729
       修改内容   :DTS2013081207431:mm挂起状态收到cc的t303超时abort消息，需要缓存，收到resume ind时再处理
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E80(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSsAbortReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI ==
            g_MmSsAbortReq.ulTransactionId )
        {
            /* 终止的MM连接建立是正在建立的             */
            if (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat == NAS_MML_GetCurrNetRatType())
            {
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);

                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                    g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* 返回到接收到建立MM连接请求时的状态       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM连接流程                               */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E80:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */
            }
            else
            {
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            }

            Mm_TimerStop( MM_TIMER_PROTECT_SIGNALLING );
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* 清除正在建立的MM连接的标志               */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;

            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */


#if (FEATURE_ON == FEATURE_LTE)

            /* 当前存在补充业务的CSFB流程，则清空CSFB存在标志 */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
            }
#endif
        }
        else
        {
            if ( ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                          .RcvXXEstReq.ucFlg )
             && ( g_MmSsAbortReq.ulTransactionId ==
             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.
                                                        ulTransactionId ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;

#if (FEATURE_ON == FEATURE_LTE)

                /* 当前存在补充业务的CSFB流程，则清空CSFB存在标志 */
                if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
                {
                    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                }
#endif

            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();
        }
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S12_E81
  FUNCTION : 在WAIT FOR RR CONNECTION (MM CONNECTION)状态下收到MMSMS_ABORT_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   05-02-01  新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E81(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSmsAbortReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI ==
            g_MmSmsAbortReq.ulTransactionId )
        {                                                                       /* 终止的MM连接建立是正在建立的             */
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            Mm_TimerStop( MM_TIMER_PROTECT_SIGNALLING );
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* 清除正在建立的MM连接的标志               */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* 返回到接收到建立MM连接请求时的状态       */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM连接流程                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                      */
            /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E81:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */
        }
        else
        {
            if ( ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                          .RcvXXEstReq.ucFlg )
             && ( g_MmSsAbortReq.ulTransactionId ==
             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
                                                            ulTransactionId ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();
        }
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S16_E80
  FUNCTION : 在WAIT FOR ADDITIONAL OUTGOING MM CONNECTION状态下
             收到MMSS_ABORT_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   05-02-01  新版作成
     2.日    期   : 2012年2月29日
       作    者   : w00167002
       修改内容   : V7R1C50 支持CSFB特性修改:
                     当前存在补充业务的CSFB流程，则清空CSFB存在标志
*******************************************************************************/
VOS_VOID Mm_Cell_S16_E80(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSsAbortReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI ==
            g_MmSsAbortReq.ulTransactionId )
        {                                                                       /* 终止的MM连接建立是正在建立的             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* 停T3230                                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* 清除正在建立的MM连接的标志               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                      */
            /*    " \nMM:STATUS is  MM_CONNECTION_ACTIVE\r " );                 */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E80:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* 检查是否有保留的需要建立的MM连接         */

#if (FEATURE_ON == FEATURE_LTE)

            /* 当前存在补充业务的CSFB流程，则清空CSFB存在标志 */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
            }
#endif
        }
        else
        {
            if ( ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                          .RcvXXEstReq.ucFlg )
             && ( g_MmSsAbortReq.ulTransactionId ==
             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.
                                                        ulTransactionId ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;

#if (FEATURE_ON == FEATURE_LTE)

                /* 当前存在补充业务的CSFB流程，则清空CSFB存在标志 */
                if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
                {
                    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                }
#endif
            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();
        }
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S16_E81
  FUNCTION : 在WAIT FOR ADDITIONAL OUTGOING MM CONNECTION状态下
             收到MMSMS_ABORT_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   05-02-01  新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S16_E81(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSmsAbortReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI ==
            g_MmSmsAbortReq.ulTransactionId )
        {                                                                       /* 终止的MM连接建立是正在建立的             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* 停T3230                                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* 清除正在建立的MM连接的标志               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                      */
            /*    " \nMM:STATUS is  MM_CONNECTION_ACTIVE\r " );                 */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E81:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* 检查是否有保留的需要建立的MM连接         */
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();
        }
    }

    return;
}


/*******************************************************************************
  MODULE   : Mm_Cell_S16_E66
  FUNCTION : 在WAIT FOR ADDITIONAL OUTGOING MM CONNECTION状态下收到MMSS_REL_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇    2005.03.28  新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S16_E66(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    if ( MM_FALSE == Mm_RcvSsRelReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /*lint -e701*/
        if ( ( MM_CONST_NUM_7 > g_MmSsRelReq.ulTi ) &&
            ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
            & ( 0x01 << g_MmSsRelReq.ulTi ) ) ) )
        {                                                                       /* TI小于7并且该MM连接存在                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] &=
                ~(VOS_UINT32)( 0x01 << g_MmSsRelReq.ulTi );                          /* 清除该标志位                             */
        }
        if ( ( MM_CONST_NUM_7 < g_MmSsRelReq.ulTi ) &&
            ( MM_CONST_NUM_15 > g_MmSsRelReq.ulTi ) &&
            ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
            & ( 0x01 << ( g_MmSsRelReq.ulTi - 8 ) ) ) ) )
        {                                                                       /* TI小于7并且该MM连接存在                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] &=
                ~(VOS_UINT32)( 0x01 << ( g_MmSsRelReq.ulTi - 8 ) );                  /* 清除该标志位                             */
        }
        if ( ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
                && ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                RcvXXEstReq.ulTransactionId == g_MmSsRelReq.ulTi ) )
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
                = MM_FALSE;                                                     /* 设置不存在缓存的MM连接 */
        }
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
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]) )
        {                                                                       /* 没有MM连接存在                           */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_OUTGOING_MM_CONNECTION);
            /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                      */
            /*    " \nMM:STATUS is  WAIT_FOR_OUTGOING_MM_CONNECTION\r " );      */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E66:NORMAL: STATUS is WAIT_FOR_OUTGOING_MM_CONNECTION");
        }

        NAS_MM_UpdateCsServiceConnStatusFlg();

        NAS_MM_UpdateCsServiceBufferStatusFlg();

        /*lint +e701*/
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S27_E82
  FUNCTION : 在PROCESS CM SERVICE PROMPT状态下
             收到MM_TIMER_PROTECT_CCBS EXPIRED的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇    2005.04.14  新版作成
     2.
*******************************************************************************/
VOS_VOID Mm_Cell_S27_E82(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    MM_MSG_MM_STATUS_STRU          MsgMmStatus;                                 /* MM STATUS 消息结构体                     */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MM_TIMER_PROTECT_CCBS EXPIRED\r " );  */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S27_E82:INFO: MM_TIMER_PROTECT_CCBS EXPIRED");
    MsgMmStatus.MmIeRjctCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_SERV_OPT_OUT_OF_ORDER;  /* Service option temporarily out of order  */
    Mm_ComMsgMmStatusSnd( &MsgMmStatus );                                       /* 填充并发送 MM STATUS 消息                */

    if ( MM_FALSE == Mm_ComMmConnExist( ) )
    {                                                                           /* 没有存在的MM连接 */
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.
            ucStaOfRcvXXEstReq;                                                 /* 进入空闲的状态                           */
        Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );        /* MM连接流程                               */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );                 */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S27_E82:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
        Mm_TimerStart(MM_TIMER_T3240);                                          /* 启动TIMER3240                            */
    }
    else
    {                                                                           /* 有存在的MM连接 */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /*    " \nMM:STATUS is  MM_CONNECTION_ACTIVE\r " );                     */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S27_E82:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
    }
}



/* Mm_Cell_S27_E33_Handling_REL_CAUSE_NOT_RL_FAILURE不再使用，删除 */


/* 删除S27E33 */



/*****************************************************************************
 Prototype      : Mm_Cell_S9_E83
 Description    : 在状态下WAIT FOR OUTGOING MM CONNECTION
                  收到GRRMM_EST_SAPI3_CNF的处理
 Input          : *pRcvMsg  收到的原语头指针
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-10-22
    Author      : sxbo
    Modification: Created function

  2.日    期   : 2011年7月14日
    作    者   : zhoujun 40661
    修改内容   : 更新MML_CTX中的业务存在状态

  3.日    期   : 2013年5月16日
    作    者   : w00167002
    修改内容   : DTS2013051408623:发短信建立时候，用户发起电话，缓存电话发起时，
                 PD被清除，导致电话发起失败。
  4.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容  :DTS2013082903019:支持ss重发功能
  5.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID Mm_Cell_S9_E83(VOS_VOID *pRcvMsg)
{
    GRRMM_EST_SAPI3_CNF_ST             *pstEstSapi3Cnf;

    NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_NORMAL,
                    "Mm_Cell_S9_E83:STATE: WAIT_FOR_OUTGOING_MM_CONNECTION Receive GRRMM_EST_SAPI3_CNF.");

    /* 消息检查 */
    if (MM_IE_PD_SMS_MSG != g_MmGlobalInfo.ucMMConnEstingPD)
    {
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                    "Mm_Cell_S9_E83: WARNING: Receive GRRMM_EST_SAPI3_CNF error.");

        return;
    }

    /* 消息检查结果成功 */
    pstEstSapi3Cnf = (GRRMM_EST_SAPI3_CNF_ST*)pRcvMsg;

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);  /* 停止保护TIMER */

    if (MM_EST_SAPI3_SUCCESS == pstEstSapi3Cnf->ucResult)
    {
        /* 该MM连接建立成功 */
        Mm_SndSmsEstCnf(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI);
        /*lint -e701*/
        /* TI 小于7 */
        if (MM_CONST_NUM_7 >
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI)
        {
            /* 设置MM连接存在标志 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]   |=
                (VOS_UINT8)(0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI);
        }
        else /*TI大于7 */
        {
            /* 设置 MM 连接存在标志 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]   |=
                (VOS_UINT8)(0x01 << (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI - 8 ) );
        }
        /*lint +e701*/
        g_MmGlobalInfo.ucPreState       = g_MmGlobalInfo.ucState;  /* 记录迁移之前的状态               */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E83:NORMAL: STATUS is MM_CONNECTION_ACTIVE");

        g_MmGlobalInfo.ucMMConnEstingPD     = NO_MM_CONN_ESTING;       /* 设置没有正在建立的连接           */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                                            = NO_MM_CONN_ESTING;
        Mm_ComCheckDelayMmConn(MM_FALSE);                          /* 检查是否有保留的需要建立的MM连接 */

        NAS_MM_UpdateCsServiceConnStatusFlg();

        return;
    }
    else /* SAPI3 建立失败 */
    {
        /* 通知 SMS, MM 连接建立失败 */
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_EST_SAPI3_FAIL);

        Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);

        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "Mm_Cell_S9_E83: ERROR: SAPI3 est fail.");
    }

    g_MmGlobalInfo.ucMMConnEstingPD     = NO_MM_CONN_ESTING;       /* 设置没有正在建立的连接           */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                                        = NO_MM_CONN_ESTING;

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}
/*****************************************************************************
 Prototype      : Mm_Cell_S9_E86
 Description    : 在状态下WAIT FOR OUTGOING MM CONNECTION
                  收到GRRMM_EST_SAPI3_CNF的处理
 Input          : *pRcvMsg  收到的原语头指针
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-10-22
    Author      : sxbo
    Modification: Created function
 2.日    期  : 2008年12月2日
   作    者  : s62952
   修改内容  : 根据问题单A32D07110修改

  3.日    期   : 2010年3月23日
    作    者   : zhoujun /z40661
    修改内容   : AMR速率调整
*****************************************************************************/
VOS_VOID Mm_Cell_S6_E86(VOS_VOID *pRcvMsg)
{
    GAS_RR_CHAN_MOD_IND_ST   *pChanMod;
    MMCC_CHANNEL_MODE_ENUM_U32        enMmCcChanMode;

    pChanMod = (GAS_RR_CHAN_MOD_IND_ST *)pRcvMsg;

    /* 对于GSM，以下参数忽略，初始化为默认值 */
    g_RrMmSyncInd.ulRabCnt = 1;
    g_RrMmSyncInd.NasSyncInfo[0].ulRabId = 0;
    g_RrMmSyncInd.NasSyncInfo[0].ulCnDomainId = 0;
    g_RrMmSyncInd.ulReason = MMCC_GSM_RES_ASSIGNED;
    g_RrMmSyncInd.NasSyncInfo[0].ulRabSyncInfo = 0;

    enMmCcChanMode = MM_ComGetChanMode(pChanMod->enChanMod);
    if(MMCC_CHAN_MOD_SIG_ONLY == enMmCcChanMode)
    {
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                        "Mm_Cell_S6_E86:  Receive GAS_RR_CHAN_MOD_IND, parameter is error.");
    }

    g_RrMmSyncInd.ulChannelMode = enMmCcChanMode;

    g_MmGlobalInfo.ucGasRrChanIndMsgValidFlg = VOS_TRUE;

    Mm_SndCcSyncInd();
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcInterRatReselInLuProcedure
 功能描述  : 在进行LU的过程中，发生系统间重选的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月25日
    作    者   : l65478
    修改内容   : 新生成函数
  2.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  3.日    期   : 2014年4月2日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的

  4.日    期   : 2014年6月4日
    作    者   : w00167002
    修改内容   : DTS2014052603967:CS only，在A小区注册失败17后迁移到B小区，在B小区
                是禁止PLMN小区，MM迁移到LIMIT service状态，后续搜网到A小区网络后，
                发起了LAU.
                在LAU失败迁移到U2状态时候记录当前的LAI信息；在开机，用户发起CS/CS_PS
                DETACH时候或或者重新发起LAU时候则清除该LAI信息；
                在后续搜索到该小区后，在U2状态，如果当前的LAI在记录的LAI里面，则
                不发起LAU.删除不用的全局变量.
  5.日    期   : 2015年3月20日
    作    者   : w00167002
    修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                 进行封装。
  6.日    期   : 2015年6月23日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_MM_ProcInterRatReselInLuProcedure(VOS_VOID)
{
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, begin */
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, end */
    MM_LAI_STRU                                            *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstCampLaiInfo  = VOS_NULL_PTR;

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    Mm_TimerStop(MM_TIMER_T3210);

    if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
    {
        /*迁移状态到limit service*/
        /*设置标志Attach not allow*/
        /*指示上层业务失败*/
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E33:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        Mm_ComCheckDelayMmConn(MM_FALSE);

        return;
    }

    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt++;

    if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
    {
        enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
        if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
         &&  (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
        {
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_ProcInterRatReselInLuProcedure:INFO: MmServiceState is MM_NORMAL_SERVICE");

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);                    /* 向MMC发送MMCMM_LU_RESULT_IND             */
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);                    /* 向MMC发送MMCMM_LU_RESULT_IND             */
            Mm_ComNasInfoSav(MM_STATUS_ATTACHED,
                             NAS_MML_GetSimCsSecurityCksn());
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录前状态                               */
            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_ProcInterRatReselInLuProcedure:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
            Mm_TimerStop(MM_TIMER_T3211);
            Mm_TimerStart(MM_TIMER_T3211);                                      /* 启动T3211                                */

            g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;

        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_ProcInterRatReselInLuProcedure:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, begin */
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);

            /* 进U2的公共处理 */
            Mm_ComToU2Handle();
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, end */

            Mm_TimerStop(MM_TIMER_T3211);
            Mm_TimerStart(MM_TIMER_T3211);                                      /* 启动T3211                                */
        }
    }
    else
    {
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_ProcInterRatReselInLuProcedure:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

        /* 在U2状态，保存当前的LAI信息 */
        pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
        pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

        pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
        pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
        pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, begin */
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);

        NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);

        /* 进U2的公共处理 */
        Mm_ComToU2Handle();
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, end */

        Mm_TimerStop(MM_TIMER_T3212);                                           /* T3212先进行停止                                */
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
    }

    NAS_MM_ProcDelayService();

    if ((VOS_FALSE  == NAS_MM_IsNeedGmmProcUserDetach())
     && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)))
    {
        NAS_MM_LocalDetach();
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcDelayService
 功能描述  : 处理缓存的MM业务
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月25日
    作    者   : l65478
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_ProcDelayService(VOS_VOID)
{
    VOS_UINT8                                   ucRrConnRelFlg;
    VOS_UINT8                                   ucTiValidFlg;

    ucRrConnRelFlg = Mm_ComRrConnRelChk();
    if (MM_TRUE == ucRrConnRelFlg)
    {
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                           /* RR连接不存在                             */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }
    else
    {
        ucTiValidFlg = Mm_ComTiChk();
        if (MM_FALSE == ucTiValidFlg)
        {
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                       /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : Mm_Cell_S2_E15
 功能描述  : mm在idle limite service/idle plmn search/no cell available状态收到GMMMM_LU_INITIATION的处理
 输入参数  : pRcvMsg - 消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月13日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Mm_Cell_S2_E15(
    VOS_VOID                           *pRcvMsg
)
{
    GMMMM_LU_INITIATION_STRU           *pstMmcLuIni = VOS_NULL_PTR;

    if (MM_FALSE == Mm_RcvGmmLuIni(pRcvMsg))
    {
        return;
    }

    pstMmcLuIni = ( GMMMM_LU_INITIATION_STRU* )pRcvMsg;

    if ( GMMMM_T3312_EXPIRED == pstMmcLuIni->enTimerExpiredFlg )
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
    }
}



/*****************************************************************************
 函 数 名  : Mm_Cell_S3_E54
 功能描述  : mm在MM IDLE NORMAL SERVICE 状态收到T3213定时器超时的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月26日
    作    者   : j00174725
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Mm_Cell_S3_E54(VOS_VOID* pMsg)
{
    VOS_UINT32                          ulIsTestCard;

    ulIsTestCard    = NAS_USIMMAPI_IsTestCard();
    if (VOS_TRUE == ulIsTestCard)
    {
        return;
    }

    /* LTE下不能发起LAU */
    if (NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType())
    {
        /* 发起LAU */
        Mm_ComLuOnly();
    }

    return;
}

/*lint -restore */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
