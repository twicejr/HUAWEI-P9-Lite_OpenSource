/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : MM_Rcv.c
  Description  : MM接收原语处理
  Function List:
            1  : Mm_RcvMmcStartReq
            2  : Mm_RcvMmcPlmnSrchIni
            3  : Mm_RcvMmcPlmnUserSelReq
            4  : Mm_RcvMmcSysInfoInd
            5  : Mm_RcvGmmCombinedAttachIni
            6  : Mm_RcvGmmCombinedAttachAccept
            7  : NAS_MM_RcvGmmCombinedAttachRej
            8  : Mm_RcvGmmImsiDetechIni
            9  : Mm_RcvGmmImsiDetechComplete
            10 : NAS_MM_RcvGmmNetworkDetechInd
            11 : Mm_RcvGmmGmmActionResultInd
            12 : Mm_RcvGmmAuthFailInd
            13 : Mm_RcvGmmCombinedRauInitiation
            14 : Mm_RcvGmmCombinedRauAccepted
            15 : Mm_RcvGmmCombinedRauRejected
            16 : Mm_RcvMmcCoverageLostInd
            17 : Mm_RcvCcEstReq
            18 : Mm_RcvCcRelReq
            19 : Mm_RcvCcAbortReq
            20 : Mm_RcvCcDataReq
            21 : Mm_RcvCcReestReq
            22 : Mm_RcvRrcPagingInd
            23 : Mm_RcvRrcEstCnf
            24 : Mm_RcvRrcRelInd
            25 : Mm_RcvRrcSecurityInd
            26 : Mm_RcvRrcSyncInd
            27 : Mm_RcvRrcDataInd
            28 : NAS_MM_RcvGmmGprsDetechIni
            29 : Mm_RcvGmmGprsDetechCmpl
            30 : Mm_RcvAgntUsimAuthenticationCnf
            31 : Mm_RcvMmcDetachReq
            32 : Mm_RcvMmcPowerOffReq
            33 : Mm_RcvSsEstReq
            34 : Mm_RcvSsRelReq
            35 : Mm_RcvSsDataReq
            36 : Mm_RcvSmsEstReq
            37 : Mm_RcvSmsRelReq
            38 : Mm_RcvSmsDataReq
            39 : Mm_RcvCcPromptRej
            40 : Mm_RcvMmcAttachReq
            41 : Mm_RcvMmcModeChngReq
            42 : Mm_RcvGmmLuIni



  History:

   1.日    期   : 2009年09月04日
     作    者   : AT2D14129
     修改内容   : 问题单号:AT2D13779,ue在发起语音业务的过程中重选至RA、LA不同的小区，网络模式II->I,目标小区正常，新小区上业务必然失败
   2.日    期   : 2009年10月09日
     作    者   : s46746
     修改内容   : 问题单号:AT2D14994,CS域无核心网广播信息时，仍然发起周期性位置更新

  3.日    期   : 2010年3月16日
    作    者   : zhoujun /z40661
    修改内容   : AMR速率控制
  4.日    期   : 2010年12月7日
    作    者   : h44270
    修改内容   : 问题单号：DTS2010112702584, 之前注册失败，进入一个BAR的小区后再回到之前小区，未发起LAU
*******************************************************************************/

#include        "MM_Inc.h"
#include        "MmCcInterface.h"
#include        "GmmMmInterface.h"
/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-16, begin */
#include        "NasMmProcLResult.h"
/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-16, end */


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_MM_RCV_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/


#define NAS_MM_SYNC_INFO_CODEC_AMR      (0x05)
#define NAS_MM_SYNC_INFO_CODEC_AMR2     (0x06)
#define NAS_MM_SYNC_INFO_CODEC_AMRWB    (0x0a)


/*lint -save -e958 */

/***********************************************************************
 *  MODULE   : Mm_RcvMmcStartReq
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      2003.12.09  新版作成
 ************************************************************************/
VOS_UINT8 Mm_RcvMmcStartReq(
                       VOS_VOID            *pRcvMsg                             /* 收到的原语头指针                         */
                       )
{
    Mm_TimerStop(MM_TIMER_STOP_ALL);
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    return MM_TRUE;                                                             /* 返回检查结果                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvMmcPlmnSrchIni
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      03-12-09  新版作成
       2.  s46746     05-10-20  Modified for HSS 4100 V200R001
 ************************************************************************/
VOS_UINT8 Mm_RcvMmcPlmnSrchIni(
                       VOS_VOID            *pRcvMsg                             /* 收到的原语头指针                         */
                       )
{
    return MM_TRUE;                                                             /* 返回检查结果                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvMmcPlmnUserSelReq
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            ucRet    消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      03-12-09  新版作成
 ************************************************************************/
VOS_UINT8 Mm_RcvMmcPlmnUserSelReq(
                            VOS_VOID            *pRcvMsg                        /* 收到的原语头指针                         */
                            )
{
    return MM_TRUE;                                                             /* 返回检查结果                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvGmmCombinedAttachIni
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      03-12-09  新版作成
 ************************************************************************/
VOS_UINT8 Mm_RcvGmmCombinedAttachIni(
                                VOS_VOID            *pRcvMsg                    /* 收到的原语头指针                         */
                                )
{
    return MM_TRUE;                                                             /* 返回检查结果                             */
}


/***********************************************************************
 *  MODULE   : Mm_RcvGmmCombinedAttachAccept
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      03-12-09  新版作成
       2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvGmmCombinedAttachAccept(
                                    VOS_VOID            *pRcvMsg                /* 收到的原语头指针                         */
                                    )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* 返回值                                   */
    GMMMM_COMBINED_ATTACH_ACCEPTED_STRU     *pstMsg  = VOS_NULL_PTR;              /* 定义接收到的消息类型指针                 */

    pstMsg = (GMMMM_COMBINED_ATTACH_ACCEPTED_STRU *)pRcvMsg;                                                             /* 消息转换                                 */

    if ((MM_CONST_NUM_1 < pstMsg->enAttachResult)
        || ((GMMMM_ATTACH_RESLUT_PS_ONLY == pstMsg->enAttachResult)
            && ((NAS_MML_REG_FAIL_CAUSE_NULL != pstMsg->enCause)
            && (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR != pstMsg->enCause)
            && (NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE != pstMsg->enCause)
            && (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE != pstMsg->enCause)
            && (NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION != pstMsg->enCause)))
			|| (MM_CONST_NUM_5 < pstMsg->ulAttachAttCounter))
    {                                                                           /* 消息中的取值不合法                       */
        ucRet = MM_FALSE;                                                       /* 返回消息检查失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvGmmCombinedAttachAccept:WARNING: MMCMM_COMBINED_ATTACH_ACCEPTED CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* 消息中的取值合法，存储消息               */
        if (GMMMM_ATTACH_RESLUT_PS_ONLY == pstMsg->enAttachResult)
        {
            g_MmGlobalInfo.ucRejectCause = (VOS_UINT8)pstMsg->enCause;
        }
        else if (GMMMM_ATTACH_RESLUT_COMBINED == pstMsg->enAttachResult)
        {
            g_MmGlobalInfo.ucRejectCause = NAS_MML_REG_FAIL_CAUSE_NULL;
        }
        else
        {

        }
    }

    return ucRet;                                                               /* 返回检查结果                             */
}

/***********************************************************************
 *  MODULE   : NAS_MM_RcvGmmCombinedAttachRej
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      03-12-09  新版作成
       2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777
 ************************************************************************/
VOS_UINT8 NAS_MM_RcvGmmCombinedAttachRej(
                                VOS_VOID            *pRcvMsg                    /* 收到的原语头指针                         */
                                )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* 返回值                                   */
    GMMMM_COMBINED_ATTACH_REJECTED_STRU     *pMsg  = VOS_NULL_PTR;              /* 定义接收到的消息类型指针                 */

    pMsg = (GMMMM_COMBINED_ATTACH_REJECTED_STRU *)pRcvMsg;                      /* 消息转换                                 */

    if ((NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW != pMsg->enCause)
        && (NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN != pMsg->enCause))
    {
        g_MmGlobalInfo.ucRejectCause = (VOS_UINT8)pMsg->enCause;
    }

    return ucRet;                                                               /* 返回检查结果                             */
}



/***********************************************************************
 *  MODULE   : Mm_RcvGmmImsiDetechIni
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      03-12-09  新版作成
 ************************************************************************/
VOS_UINT8 Mm_RcvGmmImsiDetechIni(
                       VOS_VOID            *pRcvMsg                             /* 收到的原语头指针                         */
                       )
{
    return MM_TRUE;                                                             /* 返回检查结果                             */
}


/***********************************************************************
 *  MODULE   : Mm_RcvGmmImsiDetechComplete
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      03-12-09  新版作成
 ************************************************************************/
VOS_UINT8 Mm_RcvGmmImsiDetechComplete(
                       VOS_VOID            *pRcvMsg                             /* 收到的原语头指针                         */
                       )
{
    return MM_TRUE;                                                             /* 返回检查结果                             */
}


/***********************************************************************
 *  MODULE   : NAS_MM_RcvGmmNetworkDetechInd
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      03-12-09  新版作成
       2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777
 ************************************************************************/
VOS_UINT8 NAS_MM_RcvGmmNetworkDetechInd(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* 返回值                                   */
    GMMMM_NETWORK_DETACH_IND_STRU           *pstMsg  = VOS_NULL_PTR;              /* 定义接收到的消息类型指针                 */

    pstMsg = (GMMMM_NETWORK_DETACH_IND_STRU *)pRcvMsg;                            /* 消息转换                                 */

    /*如果是网侧发起的IMSI detach，MM上报NAS_OM_EVENT_IMSI_DETACH_IND事件*/
    if (GMMMM_NET_DETACH_IMSI == pstMsg->enDetachType)
    {
        NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_IMSI_DETACH_IND,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
    }

    if ((GMMMM_NET_DETACH_IMSI != pstMsg->enDetachType)
        && (GMMMM_NET_DETACH_NOATTACH != pstMsg->enDetachType)
        && (GMMMM_NET_DETACH_REATTACH != pstMsg->enDetachType))
    {                                                                           /* 消息中的取值不合法                       */
        ucRet = MM_FALSE;                                                       /* 返回消息检查失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_RcvGmmNetworkDetechInd:WARNING: MMCMM_NETWORK_DETACH_IND CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* 消息中的取值合法，存储消息               */
        ucRet = MM_TRUE;
        if ((NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW != pstMsg->ulDetachCause)
            && (NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN != pstMsg->ulDetachCause))
        {
            g_MmGlobalInfo.ucRejectCause = (VOS_UINT8)pstMsg->ulDetachCause;
        }
    }

    return ucRet;                                                               /* 返回检查结果                             */
}


/***********************************************************************
 *  MODULE   : Mm_RcvGmmGmmActionResultInd
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      03-12-09  新版作成
       2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvGmmGmmActionResultInd(
                       VOS_VOID            *pRcvMsg                             /* 收到的原语头指针                         */
                       )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* 返回值                                   */
    GMMMM_GMM_ACTION_RESULT_IND_STRU        *pstMsg  = VOS_NULL_PTR;              /* 定义接收到的消息类型指针                 */

    pstMsg = (GMMMM_GMM_ACTION_RESULT_IND_STRU *)pRcvMsg;                                                             /* 消息转换                                 */

    if ((MM_CONST_NUM_3 < pstMsg->enGmmActionType))
    {                                                                           /* 消息中的取值不合法                       */
        ucRet = MM_FALSE;                                                       /* 返回消息检查失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvGmmGmmActionResultInd:WARNING: MMCMM_GMM_ACTION_RESULT_IND CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* 消息中的取值合法，存储消息               */
        ucRet = MM_TRUE;
        if ((NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW != pstMsg->enCause)
            && (NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN != pstMsg->enCause))
        {
            g_MmGlobalInfo.ucRejectCause = (VOS_UINT8)pstMsg->enCause;
        }
    }

    return ucRet;                                                               /* 返回检查结果                             */
}


/***********************************************************************
 *  MODULE   : Mm_RcvGmmAuthFailInd
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      03-12-09  新版作成
 ************************************************************************/
VOS_UINT8 Mm_RcvGmmAuthFailInd(
                       VOS_VOID            *pRcvMsg                             /* 收到的原语头指针                         */
                       )
{
    return MM_TRUE;                                                             /* 返回检查结果                             */
}


/***********************************************************************
 *  MODULE   : Mm_RcvGmmCombinedRauInitiation
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      03-12-09  新版作成
 ************************************************************************/
VOS_UINT8 Mm_RcvGmmCombinedRauInitiation(
                       VOS_VOID            *pRcvMsg                             /* 收到的原语头指针                         */
                       )
{
    return MM_TRUE;                                                             /* 返回检查结果                             */
}


/***********************************************************************
 *  MODULE   : Mm_RcvGmmCombinedRauAccepted
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      03-12-09  新版作成
       2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvGmmCombinedRauAccepted(
                       VOS_VOID            *pRcvMsg                             /* 收到的原语头指针                         */
                       )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* 返回值                                   */
    GMMMM_COMBINED_RAU_ACCEPTED_STRU        *pstMsg  = VOS_NULL_PTR;              /* 定义接收到的消息类型指针                 */

    pstMsg = (GMMMM_COMBINED_RAU_ACCEPTED_STRU *)pRcvMsg;                         /* 消息转换                                 */

    if (GMMMM_RAU_RESULT_PS_ONLY == pstMsg->enRauResult)
    {
        g_MmGlobalInfo.ucRejectCause = (VOS_UINT8)pstMsg->enCause;
    }
    else if (GMMMM_RAU_RESULT_COMBINED == pstMsg->enRauResult)
    {
        g_MmGlobalInfo.ucRejectCause = NAS_MML_REG_FAIL_CAUSE_NULL;
    }
    else
    {

    }
    return ucRet;                                                               /* 返回检查结果                             */
}


/***********************************************************************
 *  MODULE   : Mm_RcvGmmCombinedRauRejected
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      03-12-09  新版作成
       2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvGmmCombinedRauRejected(
                       VOS_VOID            *pRcvMsg                             /* 收到的原语头指针                         */
                       )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* 返回值                                   */
    GMMMM_COMBINED_RAU_REJECTED_STRU        *pstMsg  = VOS_NULL_PTR;              /* 定义接收到的消息类型指针                 */

    pstMsg = (GMMMM_COMBINED_RAU_REJECTED_STRU *)pRcvMsg;                                                             /* 消息转换                                 */

    if ((NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW != pstMsg->enCause)
        && (NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN != pstMsg->enCause))
    {
        g_MmGlobalInfo.ucRejectCause = (VOS_UINT8)pstMsg->enCause;
    }

    return ucRet;                                                               /* 返回检查结果                             */
}



/***********************************************************************
 *  MODULE   : Mm_RcvMmcCoverageLostInd
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      03-12-09  新版作成
 ************************************************************************/
VOS_UINT8 Mm_RcvMmcCoverageLostInd(
                       VOS_VOID            *pRcvMsg                             /* 收到的原语头指针                         */
                       )
{
    g_MmGlobalInfo.ucSysInfoFlg = MM_FALSE;

    return MM_TRUE;                                                             /* 返回检查结果                             */
}


/***********************************************************************
 *  MODULE   : Mm_RcvCcEstReq
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      03-12-09  新版作成
       2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777

  2.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级
 ************************************************************************/
VOS_UINT8 Mm_RcvCcEstReq(
                       VOS_VOID            *pRcvMsg                             /* 收到的原语头指针                         */
                       )
{
    VOS_UINT8                           ucRet;                             /* 返回值                                   */
    MMCC_EST_REQ_STRU                  *pMsg;                              /* 定义接收到的消息类型指针                 */

    pMsg        = (MMCC_EST_REQ_STRU *)pRcvMsg;                                                             /* 消息转换                                 */
    ucRet       = MM_TRUE;

    if ( ( MM_CONST_NUM_0 == pMsg->ulCallType )
      || ( MM_CONST_NUM_2 < pMsg->ulCallType )
      || ( MM_CONST_NUM_7 < pMsg->ulCallPri )
      || ( MMCC_CALL_MODE_OTHER < pMsg->ulCallMode ) )
    {                                                                           /* 消息中的取值不合法                       */
        ucRet = MM_FALSE;                                                       /* 返回消息检查失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvCcEstReq:WARNING: MMCC_EST_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* 消息中的取值合法，存储消息               */
        g_MmCcEstReq.ulCallPri       = pMsg->ulCallPri;
        g_MmCcEstReq.ulCallType      = pMsg->ulCallType;
        g_MmCcEstReq.ulTransactionId = pMsg->ulTransactionId;
        g_MmCcEstReq.ulCallMode = pMsg->ulCallMode;
        if (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType)
        {                                                                       /* 建立紧急呼叫                             */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg =
                MM_TRUE;          /* 设置是紧急呼叫的标志                     */

            NAS_MML_SetCsEmergencyServiceFlg( VOS_TRUE );
        }
        else
        {                                                                       /* 建立正常呼叫                             */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg =
                MM_FALSE;         /* 设置是正常呼叫的标志                     */

            NAS_MML_SetCsEmergencyServiceFlg( VOS_FALSE );
        }

        /* 复位呼叫重建次数 */
        g_MmGlobalInfo.ucCallRetryCount = 0;

        NAS_MM_UpdateCallStatus_RcvCcEstReq(pMsg);
    }

    return ucRet;                                                               /* 返回检查结果                             */
}


/***********************************************************************
 *  MODULE   : Mm_RcvCcRelReq
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      03-12-09  新版作成
       2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvCcRelReq(
                       VOS_VOID            *pRcvMsg                             /* 收到的原语头指针                         */
                       )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* 返回值                                   */
    MMCC_REL_REQ_STRU                       *pMsg  = VOS_NULL_PTR;              /* 定义接收到的消息类型指针                 */

    pMsg = (MMCC_REL_REQ_STRU *)pRcvMsg;                                                             /* 消息转换                                 */

    if (((MMCC_RELEASE_ALL != pMsg->ulReleaseType)
        && (MMCC_RELEASE_SPECIFIC != pMsg->ulReleaseType))
        || ((MMCC_RELEASE_SPECIFIC == pMsg->ulReleaseType)
            && (MM_CONST_NUM_14 < pMsg->ulTransactionId)))
    {                                                                           /* 消息中的取值不合法                       */
        ucRet = MM_FALSE;                                                       /* 返回消息检查失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvCcRelReq:WARNING: MMCC_REL_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* 消息中的取值合法，存储消息               */
        g_MmCcRelReq.ulReleaseType   = pMsg->ulReleaseType;
        g_MmCcRelReq.ulTransactionId = pMsg->ulTransactionId;
    }

    return ucRet;                                                               /* 返回检查结果                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvCcAbortReq
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇    2003.12.11    新版作成
       2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvCcAbortReq(
                       VOS_VOID            *pRcvMsg                             /* 收到的原语头指针                         */
                       )
{
    VOS_UINT8                                     ucRet = MM_TRUE;              /* 返回值                                   */
    MMCC_ABORT_REQ_STRU                          *pMsg  = VOS_NULL_PTR;         /* 定义接收到的消息类型指针                 */

    pMsg = (MMCC_ABORT_REQ_STRU *)pRcvMsg;

    if ((pMsg->ulTransactionId > 14) || (pMsg->ulTransactionId < 8))
    {                                                                           /* 消息中的取值不合法                       */
        ucRet = MM_FALSE;                                                       /* 返回消息检查失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvCcAbortReq:WARNING: MMCC_ABORT_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* 消息中的取值合法，存储消息               */
        g_MmCcAbortReq.ulTransactionId = pMsg->ulTransactionId;

        /* CC中止呼叫，设置不需要进行重试 */
        g_MmGlobalInfo.ucCallRetryCount = MM_CALL_RETRY_MAX_TIMES;
    }

    return ucRet;                                                               /* 返回检查结果                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvCcDataReq
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇    2003.12.11  新版作成
       2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvCcDataReq(
                   VOS_VOID            *pRcvMsg                                 /* 收到的原语头指针                         */
                   )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* 返回值                                   */
    MMCC_DATA_REQ_STRU                      *pMsg  = VOS_NULL_PTR;              /* 定义接收到的消息类型指针                 */

    pMsg = (MMCC_DATA_REQ_STRU *)pRcvMsg;                                                             /* 消息转换                                 */

    if (MM_CONST_NUM_15 < pMsg->ulTransactionId)
    {                                                                           /* 消息中的取值不合法                       */
        ucRet = MM_FALSE;                                                       /* 返回消息检查失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvCcDataReq:WARNING: MMCC_DATA_REQ CHECK PRIMITIVE ERROR!");
    }
    return ucRet;                                                               /* 返回检查结果                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvCcReestReq
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇    2003.12.11  新版作成
       2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvCcReestReq(
                        VOS_VOID             *pRcvMsg                           /* 收到的原语头指针                         */
                        )
{
    VOS_UINT8                                 ucRet = MM_TRUE;                  /* 返回值                                   */
    MMCC_REEST_REQ_STRU                      *pMsg  = VOS_NULL_PTR;             /* 定义接收到的消息类型指针                 */

    pMsg = (MMCC_REEST_REQ_STRU *)pRcvMsg;                                                             /* 消息转换                                 */

    if ((MM_CONST_NUM_14 < pMsg->ulTransactionId)
        || (MM_CONST_NUM_7 == pMsg->ulTransactionId))
    {                                                                           /* 消息中的取值不合法                       */
        ucRet = MM_FALSE;                                                       /* 返回消息检查失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvCcReestReq:WARNING: MMCC_REEST_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* 消息中的取值合法，存储消息               */
        g_MmCcReestReq.ulTransactionId  = pMsg->ulTransactionId;
    }

    return ucRet;                                                               /* 返回检查结果                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvRrcPagingInd
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇    2003.12.11    新版作成
       2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvRrcPagingInd(
                        VOS_VOID             *pRcvMsg                           /* 收到的原语头指针                         */
                        )
{
    VOS_UINT8                                 ucRet = MM_TRUE;                  /* 返回值                                   */
    RRMM_PAGING_IND_STRU                     *pMsg  = VOS_NULL_PTR;             /* 定义接收到的消息类型指针                 */

    MSG_HEADER_STRU                          *pMsgHeader;

    pMsgHeader = (MSG_HEADER_STRU*)pRcvMsg;

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        /* 判断是否为 GSM 的寻呼消息 */
        if (UEPS_PID_GAS != pMsgHeader->ulSenderPid)
        {
            NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                    "Mm_RcvRrcPagingInd: WARNING: Receive WAS Page Ind in GSM!");

            return MM_FALSE;
        }

        /* 调用函数 MM_RcvGsmRrcPagingInd 处理 */
        ucRet = MM_RcvGsmRrcPagingInd(pRcvMsg);

        return ucRet;
    }
    else
    {
        /* 判断是否为 WCDMA 的寻呼消息 */
        if (WUEPS_PID_WRR != pMsgHeader->ulSenderPid)
        {
            NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                    "Mm_RcvRrcPagingInd: WARNING: Receive GSM Page Ind in WCDMA!");

            return MM_FALSE;
        }
    }

    pMsg = (RRMM_PAGING_IND_STRU *)pRcvMsg;                                                             /* 消息转换                                 */

    if ((RRC_NAS_CS_DOMAIN != pMsg->ulCnDomainId)
        || (MM_CONST_NUM_1 < pMsg->ulPagingType)
        || (MM_CONST_NUM_6 < pMsg->ulPagingCause)
        || (MM_CONST_NUM_4 < pMsg->ulPagingUeId))
    {                                                                           /* 消息中的取值不合法                       */
        ucRet = MM_FALSE;                                                       /* 返回消息检查失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvRrcPagingInd:WARNING: RRMM_PAGING_IND CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* 消息中的取值合法，存储消息               */
        g_MmGlobalInfo.ucPagingCause = (VOS_UINT8)pMsg->ulPagingCause;          /* 设置寻呼原因值                           */

        if ((RRC_P_TMSI_GSM_MAP == pMsg->ulPagingUeId)
            || (RRC_TMSI_GSM_MAP_P_TMSI == pMsg->ulPagingUeId))
        {
            g_MmGlobalInfo.ucPagingRecordTypeId = MM_TMSI_PAGING;
        }
        else if (RRC_IMSI_GSM_MAP == pMsg->ulPagingUeId)
        {
            g_MmGlobalInfo.ucPagingRecordTypeId = MM_IMSI_PAGING;
        }
        else
        {
            ucRet = MM_FALSE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvRrcPagingInd:WARNING: RRMM_PAGING_IND CHECK PRIMITIVE ERROR!");
        }
    }

    return ucRet;                                                               /* 返回检查结果                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvRrcEstCnf
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇    2003.12.11  新版作成
       2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777

       3.日    期   : 2011年7月14日
         作    者   : zhoujun 40661
         修改内容   : 更新MML_CTX中的链接存在状态
       4.日    期   : 2011年7月28日
         作    者   : sunxibo 46746
         修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
       5.日    期   : 2012年7月14日
         作    者   : l65478
         修改内容   : DTS2012071303294在连接建立失败时没有清除CS连接标志
       6,.日    期   : 2012年11月29日
         作    者   : l65478
         修改内容   : DTS2012112602789:CSFB标志没有清除
       7.日    期   : 2013年3月30日
         作    者   : l00167671
         修改内容   : 主动上报AT命令控制下移至C核
       8.日    期   : 2014年6月13日
         作    者   : w00242748
         修改内容   : DSDS 新特性
       9.日    期   : 2014年8月14日
         作    者   : z00161729
         修改内容   : gas下lau建链失败原因值random access reject no valid information场景未按协议实现8s内不发起lau，t3213 4s超时就发起了lau
      10.日    期   :2014年9月24日
         作    者   :s00217060
         修改内容   :for cs_err_log
      11.日    期   : 2014年11月8日
         作    者   : w00167002
         修改内容   : DTS2014110605230:在W下也可能收到拒绝RRC_EST_RANDOM_ACCESS_REJECT。
                      在L下电话感到G后，lau建联失败17，也清楚了CSFB，后续收到系统
                      消息，没有发起LAU.期望不清楚,继续CSFB流程。
 ************************************************************************/
VOS_UINT8 Mm_RcvRrcEstCnf(
                        VOS_VOID            *pRcvMsg                            /* 收到的原语头指针                         */
                        )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* 返回值                                   */
    RRMM_EST_CNF_STRU                       *pMsg  = VOS_NULL_PTR;              /* 定义接收到的消息类型指针                 */
    NAS_MML_CONN_STATUS_INFO_STRU           *pstConnStatus;
    VOS_UINT32                               ulIsGsmOnlyEstCnfRslt;

    pstConnStatus       = NAS_MML_GetConnStatus();

    pMsg = (RRMM_EST_CNF_STRU *)pRcvMsg;                                                             /* 消息转换                                 */

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {                                                                           /* 当前在 GSM 网中                          */
        if (UEPS_PID_GAS != pMsg->MsgHeader.ulSenderPid)
        {
            NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                    "Mm_RcvRrcEstCnf: WARNING: Receive WAS message in GSM.");
            return MM_FALSE;
        }
    }
    else
    {
        if (WUEPS_PID_WRR != pMsg->MsgHeader.ulSenderPid)
        {
            NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                    "Mm_RcvRrcEstCnf: WARNING: Receive GAS message in WCDMA.");
            return MM_FALSE;
        }
    }

    if (RRC_NAS_CS_DOMAIN != pMsg->ulCnDomainId)
    {                                                                           /* 不是CS域消息                             */
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                "Mm_RcvRrcEstCnf: WARNING: Not receive CS domain message.");
        return MM_FALSE;
    }

    if (g_MmGlobalInfo.ucRrEstReqOpid != pMsg->ulOpId)
    {                                                                           /* OP ID不相等                              */
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                "Mm_RcvRrcEstCnf: WARNING: OPID is wrong.");
        return MM_FALSE;
    }

    if (   (RRC_EST_SUCCESS == pMsg->ulResult)
        || (RRC_EST_PRESENT == pMsg->ulResult))
    {
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_EXIST);

        /* 24.008, 4.4.4.9, case f1, CR1099 update:
          更新RRC链路状态 */
        pstConnStatus->ucCsSigConnStatusFlg     = VOS_TRUE;
        pstConnStatus->ucRrcStatusFlg           = VOS_TRUE;

        NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_EST_SUCCESSED,
                                  pMsg->ulResult);
    }
    else
    {
        /* 建链失败，清除MM 链路控制变量 */
        NAS_MM_ClearMmLinkCtrlStru();

        NAS_MML_SetCsSigConnStatusFlg(VOS_FALSE);

        NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_EST_FAILED,
                                  pMsg->ulResult);

        /* 在LU过程中,random access rej时,需要再发起一次LU建链过程,在第二次建链失败时,清除CSFB标志
           其它原因值直接清除CSFB标志*/
#if (FEATURE_ON == FEATURE_LTE)
        ulIsGsmOnlyEstCnfRslt = NAS_MM_IsGsmOnlyEstCnfRslt(pMsg->ulResult);

        if ((NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
          && (VOS_TRUE == ulIsGsmOnlyEstCnfRslt)
          && ((g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt < MM_CONST_NUM_1)
           || ((WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING != g_MmGlobalInfo.ucState)
            && (g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt >= MM_CONST_NUM_1))))

        {
            return ucRet;
        }

        NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

        NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

        /* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
        NAS_MML_SetRelCauseCsfbHighPrioFlg(VOS_FALSE);
        /* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
#endif

    }

    return ucRet;                                                               /* 返回检查结果                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvRrcRelInd
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇    2003.12.11    新版作成
       2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777
       3.日    期  : 2007年03月01日
         作    者  : luojian id:60022475
         修改内容  : MAPS3000接口修改
       4.日    期   : 2008年12月9日
         作    者   : l00130025
         修改内容   : 问题单号：AT2D07328,有链接存在时，SYSCFG被缓存，后丢网，SYSCFG消息被清除
       5.日    期   : 2011年3月3日
         作    者   : z00161729
         修改内容   : DTS2011021201997:PS、CS完整性保护是否开启由GMM和MM分开维护,MMC不再维护

       6.日    期   : 2011年7月14日
         作    者   : zhoujun 40661
         修改内容   : 更新MML_CTX中的全局变量
       7.日    期   : 2012年2月15日
         作    者   : z00161729
         修改内容   : V7R1C50 支持CSFB特性修改
                       1.若当前是CSFB的被叫，则收到RRMM_REL_IND可认为被叫结束
          TS23.272 7.3 When the MSC receives a LA Update Request, it shall check
          for pending terminating CS calls and, if the "CSMT" flag is set,
          maintain the CS signalling connection after the Location Area Update
          procedure for pending terminating CS calls.
      8.日    期   : 2013年3月30日
        作    者   : l00167671
        修改内容   : 主动上报AT命令控制下移至C核
      9.日    期   : 2014年6月13日
        作    者   : w00242748
        修改内容   : DSDS 新特性
 ************************************************************************/
VOS_UINT8 Mm_RcvRrcRelInd(
    VOS_VOID                           *pRcvMsg                            /* 收到的原语头指针                         */
)
{
    VOS_UINT8                           ucRet = MM_TRUE;                  /* 返回值                                   */
    RRMM_REL_IND_STRU                  *pMsg  = VOS_NULL_PTR;             /* 定义接收到的消息类型指针                 */
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus;

    pstConnStatus   = NAS_MML_GetConnStatus();

    pMsg = (RRMM_REL_IND_STRU *)pRcvMsg;                                                             /* 消息转换                                 */

    if ((RRC_NAS_CS_DOMAIN != pMsg->ulCnDomainId)
        || (MM_CONST_NUM_1 < pMsg->ulRrcConnStatus)
        || (RRC_REL_CAUSE_BUTT <= pMsg->ulRelCause))
    {                                                                           /* 消息中的取值不合法                       */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvRrcRelInd:WARNING: RRMM_REL_IND CHECK PRIMITIVE ERROR!");
        return MM_FALSE;
    }

    /* 链路释放，清除MM 链路控制变量，并更新CS 信令连接状态 */
    pstConnStatus->ucCsSigConnStatusFlg = VOS_FALSE;
    if (RRC_RRC_CONN_STATUS_ABSENT == pMsg->ulRrcConnStatus)
    {
        pstConnStatus->ucRrcStatusFlg   = VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* 若当前存在CSFB标志，则清除CSFB标志 */
    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {

        /* 如果CSFB MT保护定时器超时状态下，收到网络的REL后，认为是CSFB MT的异常 */
        if (NAS_ERR_LOG_CSFB_MT_STATE_CSFB_MT_PROTECT_TI_TIME_OUT == NAS_MML_GetCsfbMtCurrState())
        {
            NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_CSFB_MT_TI_TIME_OUT_RCV_REL_IND,
                                      pMsg->ulRelCause);

#if (FEATURE_ON == FEATURE_PTM)
            NAS_MM_CsfbMtFailRecord();
#endif
        }
        else
        {
            NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_RRC_REL_IND_RECEIVED,
                                      pMsg->ulRelCause);
        }


        NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

        NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

        /* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
        NAS_MML_SetRelCauseCsfbHighPrioFlg(VOS_FALSE);
        /* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
    }
#endif

    /* 链路释放后，原有链路上GAS上报的Gas_RR_CHAN_IND消息失效 */
    g_MmGlobalInfo.ucGasRrChanIndMsgValidFlg = VOS_FALSE;

    NAS_MM_SndCcRrcConnectRelInd();

    /* 以下状态在判断是否需要重试流程后再清除MM链路控制变量 */
    if (   (WAIT_FOR_OUTGOING_MM_CONNECTION != g_MmGlobalInfo.ucState)
        && (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING != g_MmGlobalInfo.ucState)
        && (LOCATION_UPDATING_INITIATED != g_MmGlobalInfo.ucState))
    {
        NAS_MM_ClearMmLinkCtrlStru();
    }

    g_MmSubLyrShare.MmShare.ucCsIntegrityProtect  = NAS_MML_RRC_INTEGRITY_PROTECT_DEACTIVE;

    g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_ABSENT;
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_RcvRrcRelInd:INFO: MmCsSigConnFlg is MM_CS_SIG_CONN_ABSENT");

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        MM_SndMmcRrRelInd(pMsg->ulRelCause);
    }
    return ucRet;                                                               /* 返回检查结果                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvRrcSecurityInd
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *  1.  张志勇    2003.12.11  新版作成
    2.  张志勇 2005.04.15  MM_Review_HW_BUG_038对应
    3.日    期  : 2006年12月4日
      作    者  : luojian id:60022475
      修改内容  : 问题单号:A32D07777
    4.日    期   : 2011年3月3日
      作    者   : z00161729
      修改内容   : DTS2011021201997:PS、CS完整性保护是否开启由GMM和MM分开维护,MMC不再维护
    5.日    期   : 2011年7月27日
      作    者   : h44270
      修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
 ************************************************************************/
VOS_UINT8 Mm_RcvRrcSecurityInd(
                           VOS_VOID            *pRcvMsg                         /* 收到的原语头指针                         */
                           )
{
    VOS_UINT8                                 ucRet = MM_TRUE;                  /* 返回值                                   */
    RRMM_SECURITY_IND_STRU                   *pMsg  = VOS_NULL_PTR;             /* 定义接收到的消息类型指针                 */

    pMsg = (RRMM_SECURITY_IND_STRU *)pRcvMsg;                                                             /* 消息转换                                 */

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        /* 判断是否为 GSM 的同步指示消息 */
        if (UEPS_PID_GAS!= pMsg->MsgHeader.ulSenderPid)
        {
            NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                    "Mm_RcvRrcSecurityInd: WARNING: Receive WAS Security Ind in GSM!");

            return MM_FALSE;
        }

        ucRet = MM_RcvGsmRrcSyncInd(pRcvMsg);

        return ucRet;

    }
    else
    {
        /* 判断是否为 WCDMA 的同步指示消息 */
        if (WUEPS_PID_WRR != pMsg->MsgHeader.ulSenderPid)
        {
            NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                    "Mm_RcvRrcSecurityInd: WARNING: Receive GAS Sync in WCDMA!");

            return MM_FALSE;
        }
    }

    if (RRC_SECURITY_MOBI_MSG < pMsg->ulRptMode)
    {                                                                           /* 消息中的取值不合法                       */
        ucRet = MM_FALSE;                                                       /* 返回消息检查失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvRrcSecurityInd:WARNING: RRMM_SECURITY_IND CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* 消息中的取值合法，存储消息               */

        g_MmGlobalInfo.stMmLinkCtrl.ucSmcOrFirstNasMsgRcvdFlg = VOS_TRUE;       /* 当前CS信令链路已收到SMC消息 */

        g_MmGlobalInfo.CsSecutityInfo.ucSecurityType = (VOS_UINT8)pMsg->ulRptMode;

        if ((RRC_SECURITY_DEL_CS_KEY == pMsg->ulRptMode)
            || (RRC_SECURITY_DEL_CS_PS_KEY == pMsg->ulRptMode))
        {
            NAS_MML_InitCsSecurityUmtsCkInvalid();
            NAS_MML_InitCsSecurityUmtsIkInvalid();

            NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);
        }
        else
        {
            if ( RRC_SECURITY_CS_SMC_RCV == pMsg->ulRptMode )
            {
                g_MmSubLyrShare.MmShare.ucCsIntegrityProtect = NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE;
                Mm_TimerStop(MM_TIMER_T3218);                                   /* 停T3218                                  */
                Mm_ComDelRandRes();                                             /* 删除RAND和RES                            */
            }
            #if 0
            else if(RRC_SECURITY_CS_SMC_CMPL == pMsg->ulRptMode)
            {
                g_MmGlobalInfo.CsSecutityInfo.ucSecutityFlg =
                    (VOS_UINT8)pMsg->ulCsCipherStatus;                              /* 设置加密是否启动                         */
              /*  if ( RRC_INTEG_PROTECT_NOCHG != pMsg->ulIntegCmd ) */
                if ( RRC_INTEG_PROTECT_CS_START == pMsg->ulIntegCmd )
                {                                                               /* 完整性保护状态改变                       */
                    g_MmGlobalInfo.CsSecutityInfo.ucIntegFlg =
                                                    MM_INTEG_PROTECT_START;     /* 完整性保护启动                           */
                }
            }
            #endif
        }
        #if 0
        if (RRC_CIPHER_START == g_MmGlobalInfo.CsSecutityInfo.ucSecutityFlg)
        {
            if ( RRC_NAS_CIPHER_ALGO_UEA0 == pMsg->ulCsCipherAlgor )
            {
                g_MmGlobalInfo.ucCsCipherAlgor = NAS_MM_CIPHER_ALGO_UEA0;
            }
            else if ( RRC_NAS_CIPHER_ALGO_UEA1 == pMsg->ulCsCipherAlgor )
            {
                g_MmGlobalInfo.ucCsCipherAlgor = NAS_MM_CIPHER_ALGO_UEA1;
            }
            else
            {

            }
        }
        #endif
    }

    return ucRet;                                                               /* 返回检查结果                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvRrcSyncInd
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇    2003.12.11  新版作成
       2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777
       3.日    期  : 2008年12月2日
         作    者  : s62952
         修改内容  : 根据问题单A32D07110修改

  3.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级

  4.日    期   : 2010年3月18日
    作    者   : zhoujun /z40661
    修改内容   : AMR速率调整

  5.日    期   : 2012年2月9日
    作    者   : z40661
    修改内容   : 支持AMR-WB功能
 ************************************************************************/
VOS_UINT8 Mm_RcvRrcSyncInd(
                       VOS_VOID            *pRcvMsg
                       )
{
    VOS_UINT8                                 ucRet = MM_TRUE;                  /* 返回值                                   */
    VOS_UINT8                                 i;
    RRMM_SYNC_IND_STRU                       *pMsg  = VOS_NULL_PTR;             /* 定义接收到的消息类型指针                 */
    pMsg = (RRMM_SYNC_IND_STRU *)pRcvMsg;                                                             /* 消息转换                                 */

    if  (RRC_NAS_MAX_RAB_SETUP < pMsg->ulRabCnt)
    {                                                                           /* 消息中的取值不合法                       */
        ucRet = MM_FALSE;                                                       /* 返回消息检查失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvRrcSyncInd:WARNING: RRMM_SYNC_IND CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* 消息中的取值合法，存储消息               */
        PS_MEM_SET(&g_RrMmSyncInd,0,sizeof(g_RrMmSyncInd));

        g_RrMmSyncInd.ulRabCnt = pMsg->ulRabCnt;

        for (i=0; i < pMsg->ulRabCnt; i++)
        {
            g_RrMmSyncInd.NasSyncInfo[i].ulRabId       = pMsg->NasSyncInfo[i].ulRabId;
            g_RrMmSyncInd.NasSyncInfo[i].ulCnDomainId  = pMsg->NasSyncInfo[i].ulCnDomainId;
            g_RrMmSyncInd.NasSyncInfo[i].ulRabSyncInfo = (VOS_UINT32)(pMsg->NasSyncInfo[i].ucRabSyncInfo);
        }

        /* 此处Amr no change发送到CC时会转换成release，CC新开发代码中需要修改 */
        g_RrMmSyncInd.ulReason      = pMsg->enAmrModeCfgType + 4;

        if ( g_RrMmSyncInd.ulRabCnt > 0 )
        {
            if (NAS_MM_SYNC_INFO_CODEC_AMR == (pMsg->NasSyncInfo[0].ucRabSyncInfo))
            {
                g_RrMmSyncInd.ulChannelMode = MMCC_CHAN_MOD_AMR;
            }
            else if ( NAS_MM_SYNC_INFO_CODEC_AMR2 == (pMsg->NasSyncInfo[0].ucRabSyncInfo) )
            {
                g_RrMmSyncInd.ulChannelMode = MMCC_CHAN_MOD_AMR2;
            }
            else if ( NAS_MM_SYNC_INFO_CODEC_AMRWB == (pMsg->NasSyncInfo[0].ucRabSyncInfo) )
            {
                g_RrMmSyncInd.ulChannelMode = MMCC_CHAN_MOD_AMRWB;
            }
            else
            {
                g_RrMmSyncInd.ulChannelMode = MMCC_CHAN_MOD_AMR2;
            }

        }
        else
        {
            g_RrMmSyncInd.ulChannelMode = MMCC_CHAN_MOD_AMR2;
        }
    }

    return ucRet;                                                               /* 返回检查结果                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvRrcDataInd
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇    2003.12.12  新版作成
 ************************************************************************/
VOS_UINT8 Mm_RcvRrcDataInd(
                       VOS_VOID            *pRcvMsg                             /* 收到的原语头指针                         */
                       )
{
    VOS_UINT8                               ucRet = MM_TRUE;                    /* 返回值                                   */

    return ucRet;                                                               /* 返回检查结果                             */
}

/***********************************************************************
 *  MODULE   : NAS_MM_RcvGmmGprsDetechIni
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇    2003.12.12  新版作成
       2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777
 ************************************************************************/
VOS_UINT8 NAS_MM_RcvGmmGprsDetechIni(
                             VOS_VOID            *pRcvMsg                       /* 收到的原语头指针                         */
                            )
{
    VOS_UINT8                                 ucRet = MM_TRUE;                  /* 返回值                                   */
    GMMMM_GPRS_DETACH_INITIATION_STRU        *pstMsg  = VOS_NULL_PTR;             /* 定义接收到的消息类型指针                 */

    pstMsg = (GMMMM_GPRS_DETACH_INITIATION_STRU *)pRcvMsg;                                                             /* 消息转换                                 */

    if ((GMMMM_COMBINED_DETACH_NORMAL != pstMsg->enDetachType)
        && (GMMMM_GPRS_DETACH_NORMAL != pstMsg->enDetachType))
    {                                                                           /* 消息中的取值不合法                       */
        ucRet = MM_FALSE;                                                       /* 返回消息检查失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_RcvGmmGprsDetechIni:WARNING: MMCMM_GPRS_DETACH_INITIATION CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* 消息中的取值合法，存储消息               */
        ucRet = MM_TRUE;
    }

    return ucRet;                                                               /* 返回检查结果                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvGmmGprsDetechCmpl
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇    2003.12.12  新版作成
 ************************************************************************/
VOS_UINT8 Mm_RcvGmmGprsDetechCmpl(
                          VOS_VOID            *pRcvMsg                          /* 收到的原语头指针                         */
                          )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* 返回值                                   */

    return ucRet;                                                               /* 返回检查结果                             */
}




/*******************************************************************************
  Module:   Mm_RcvAgntUsimAuthenticationCnf
  Function: 接收 AGENT_USIM_AUTHENTICATION_CNF 公共处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   MM_TRUE,成功 MM_FALSE,失败
  History:
      1. 张志勇  2003.12.15  新版做成
      2. 张志勇  2003.10.23  AGENT接口变更对应

      3.日    期  : 2013年7月22日
        作    者  : y00245242
        修改内容  : VoIP开发，适配新的USIM接口
      4.日    期   : 2014年4月175日
        作    者   : s00246516
        修改内容   : DTS2014041700472:使用2G SIM卡，PAD形态上出现鉴权被网络拒绝
      5.日    期   : 2014年10月20日
        作    者   : w00167002
        修改内容   : DTS2014102000868:在鉴权成功后才更新CKSN
*******************************************************************************/
VOS_UINT8   Mm_RcvAgntUsimAuthenticationCnf(
                                         VOS_VOID     *pMsg                     /* 当前处理的消息                           */
                                        )
{
    VOS_UINT8                               ucRet = MM_TRUE;                    /* 返回结果初始化为成功                     */

    if (MM_RCV_AUTH_CNF_FLG
        != (MM_RCV_AUTH_CNF_FLG & g_MmGlobalInfo.ucRcvAgentFlg))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvAgntUsimAuthenticationCnf:WARNING: g_MmGlobalInfo.ucRcvAgentFlg Abnormal");
        return MM_FALSE;
    }
    else
    {
        g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    }

    Mm_Com_UsimAuthenticationCnfChgFormat((USIMM_AUTHENTICATION_CNF_STRU *)pMsg);

    if (AGENT_AUTH_RST_SUCCESS == g_AgentUsimAuthCnf.ucCheckRst)
    {
        NAS_MML_SetSimCsSecurityUmtsCk(g_AgentUsimAuthCnf.aucCipheringKey);
        NAS_MML_SetSimCsSecurityUmtsIk(g_AgentUsimAuthCnf.aucIntegrityKey);

        NAS_MML_SetSimCsSecurityCksn(g_MmMsgAuthReq.MmIeCKSN.ucCksn);

        PS_MEM_CPY(g_MmGlobalInfo.AuthenCtrlInfo.aucRes,
                    g_AgentUsimAuthCnf.aucResponse, 4);

        /* 设置 RES 存在标志 */
        g_MmGlobalInfo.AuthenCtrlInfo.ucResFlg = MM_AUTHEN_RES_PRESENT;

        if (MM_CONST_NUM_0 == g_AgentUsimAuthCnf.ucKcLength)                    /* g_AgentUsimAuthCnf.ucKcLength 为零 */
        {
            /* 调用函数 NAS_MML_SecContext3GTO2G 求的 KC */
            NAS_MML_SecContext3GTO2G(NAS_MML_GetSimCsSecurityUmtsIk(),
                                     NAS_MML_GetSimCsSecurityUmtsCk(),
                                     NAS_MML_GetSimCsSecurityGsmKc());

        }
        else
        {
            /* 将 KC 保存到全局变量 */
            NAS_MML_SetSimCsSecurityGsmKc(g_AgentUsimAuthCnf.aucKc);

        }

        if (0 != g_AgentUsimAuthCnf.ucExtRspLength)
        {
            g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength =
                               g_AgentUsimAuthCnf.ucExtRspLength;
            if (MM_MAX_RES_EXT_LEN <
                g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength)
            {
                 g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength = MM_MAX_RES_EXT_LEN;
            }
            PS_MEM_CPY(g_MmGlobalInfo.AuthenCtrlInfo.aucExtRes,
                        g_AgentUsimAuthCnf.aucExtResponse,
                        g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength);          /* 保存Extern RES                           */
        }
        else
        {
            g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength = 0;
        }
    }
    else
    {
        if (AGENT_AUTH_FAIL_SQN == g_AgentUsimAuthCnf.ucFailureCause)
        {
            g_MmGlobalInfo.AuthenCtrlInfo.ucFailParaLength =
                g_AgentUsimAuthCnf.ucFailParaLength;
            if (0 != g_MmGlobalInfo.AuthenCtrlInfo.ucFailParaLength)
            {
                if (14 < g_MmGlobalInfo.AuthenCtrlInfo.ucFailParaLength)
                {
                    g_MmGlobalInfo.AuthenCtrlInfo.ucFailParaLength = 14;
                }
                PS_MEM_CPY(g_MmGlobalInfo.AuthenCtrlInfo.aucFailPara,
                            g_AgentUsimAuthCnf.aucFailPara,
                            g_MmGlobalInfo.AuthenCtrlInfo.ucFailParaLength);
            }
        }
    }

    return ucRet;
}

/***********************************************************************
 *  MODULE   : Mm_RcvMmcDetachReq
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *  1.  张志勇    2004.03.12  新版作成
    2.日    期  : 2006年12月4日
      作    者  : luojian id:60022475
      修改内容  : 问题单号:A32D07777
    3.日    期   : 2011年7月26日
      作    者   : h44270
      修改内容   : V7R1 PHASE II ATTACH/DETACH调整
************************************************************************/
VOS_UINT8 Mm_RcvMmcDetachReq(
                         VOS_VOID            *pRcvMsg                           /* 收到的原语头指针                         */
                         )
{
    VOS_UINT8                                 ucRet = MM_TRUE;                  /* 返回值                                   */
    MMCMM_DETACH_REQ_STRU                    *pMsg  = VOS_NULL_PTR;             /* 定义接收到的消息类型指针                 */

    pMsg = (MMCMM_DETACH_REQ_STRU *)pRcvMsg;                                                             /* 消息转换                                 */

    if ((MMC_MM_PS_DETACH       != pMsg->enDetachType)
        && (MMC_MM_CS_DETACH    != pMsg->enDetachType)
        && (MMC_MM_PS_CS_DETACH != pMsg->enDetachType))
    {                                                                           /* 消息中的取值不合法                       */
        ucRet = MM_FALSE;                                                       /* 返回消息检查失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvMmcDetachReq:WARNING: MMCMM_DETACH_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* 消息中的取值合法，存储消息               */
        ucRet = MM_TRUE;
    }

    return ucRet;                                                               /* 返回检查结果                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvMmcPowerOffReq
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇    2004.03.12  新版作成
       2.日    期   : 2006年9月9日
         作    者   : sunxibo id:46746
         修改内容   : 根据问题单号：A32D05803
       3.日    期   : 2012年3月27日
         作    者   : w00166186
         修改内容   : CSFB&PPAC&ETWS&ISR 开发 ENERGENCY CALL
 ************************************************************************/
VOS_UINT8 Mm_RcvMmcPowerOffReq(
                         VOS_VOID            *pRcvMsg                           /* 收到的原语头指针                         */
                         )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* 返回值                                   */
    VOS_UINT8                                i;
    NAS_MML_EMERGENCY_NUM_LIST_STRU         *pstEmergencyNumList;
    pstEmergencyNumList     = NAS_MML_GetEmergencyNumList();

    Mm_TimerStop(MM_TIMER_STOP_ALL);

    pstEmergencyNumList->ulMcc = 0xFFFFFFFF;

    for (i = 0; i < pstEmergencyNumList->ucEmergencyNumber; i++)
    {
        PS_MEM_SET(&pstEmergencyNumList->aucEmergencyList[i],
                    0xFF,
                    sizeof(NAS_MML_EMERGENCY_NUM_STRU));
    }

    pstEmergencyNumList->ucEmergencyNumber = 0;


    return ucRet;                                                               /* 返回检查结果                             */
}
/***********************************************************************
 *  MODULE   : Mm_RcvSsEstReq
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      04-03-09  新版作成
 *     2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvSsEstReq(
                       VOS_VOID            *pRcvMsg                             /* 收到的原语头指针                         */
                       )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* 返回值                                   */
    MMSS_EST_REQ_STRU                       *pMsg  = VOS_NULL_PTR;              /* 定义接收到的消息类型指针                 */
    pMsg = (MMSS_EST_REQ_STRU *)pRcvMsg;                                                             /* 消息转换                                 */

    if (MM_CONST_NUM_15 < pMsg->ulTi)
    {                                                                           /* 消息中的取值不合法                       */
        ucRet = MM_FALSE;                                                       /* 返回消息检查失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvSsEstReq:WARNING: MMSS_EST_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* 消息中的取值合法，存储消息               */
        g_MmSsEstReq.ulTi = pMsg->ulTi;

        /* 第一次发起ss业务(不是重拨时),先默认为gu下的业务，
           如果后续是发给LMM的，在给LMM发送csfb start时会更新该标志
        */
        if (VOS_FALSE == pMsg->ucRedialFlg)
        {
            NAS_NORMAL_LOG(WUEPS_PID_MM,
            "Mm_RcvSsEstReq: Not Redail SS, Set CellNotSupportCsmoFlg to FALSE");
            NAS_MML_SetCellNotSupportCsmoFlg(VOS_FALSE);

            NAS_MML_SetMoSsStatus(NAS_MML_MO_NORMAL_SS_SETUP_START);
        }
    }

    return ucRet;                                                               /* 返回检查结果                             */
}


/***********************************************************************
 *  MODULE   : Mm_RcvSsRelReq
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      04-03-09  新版作成
 *     2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvSsRelReq(
                       VOS_VOID            *pRcvMsg                             /* 收到的原语头指针                         */
                       )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* 返回值                                   */
    MMSS_REL_REQ_STRU                       *pMsg  = VOS_NULL_PTR;              /* 定义接收到的消息类型指针                 */

    pMsg = (MMSS_REL_REQ_STRU *)pRcvMsg;                                                             /* 消息转换                                 */

    if ((MM_CONST_NUM_14 < pMsg->ulTi)
        || (MM_CONST_NUM_7 == pMsg->ulTi))
    {                                                                           /* 消息中的取值不合法                       */
        ucRet = MM_FALSE;                                                       /* 返回消息检查失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvSsRelReq:WARNING: MMSS_REL_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* 消息中的取值合法，存储消息               */
        g_MmSsRelReq.ulTi = pMsg->ulTi;
    }

    return ucRet;                                                               /* 返回检查结果                             */
}


/***********************************************************************
 *  MODULE   : Mm_RcvSsDataReq
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      04-03-09  新版作成
 *     2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvSsDataReq(
                   VOS_VOID            *pRcvMsg                                 /* 收到的原语头指针                         */
                   )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* 返回值                                   */
    MMSS_DATA_REQ_STRU                      *pMsg  = VOS_NULL_PTR;              /* 定义接收到的消息类型指针                 */

    pMsg = (MMSS_DATA_REQ_STRU *)pRcvMsg;                                                             /* 消息转换                                 */

    if (MM_CONST_NUM_15 < pMsg->ulTi)
    {                                                                           /* 消息中的取值不合法                       */
        ucRet = MM_FALSE;                                                       /* 返回消息检查失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvSsDataReq:WARNING: MMSS_DATA_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* 消息中的取值合法，存储消息               */

    }

    return ucRet;                                                               /* 返回检查结果                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvSmsEstReq
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      04-03-09  新版作成
 *     2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvSmsEstReq(
                       VOS_VOID            *pRcvMsg                             /* 收到的原语头指针                         */
                       )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* 返回值                                   */
    MMSMS_EST_REQ_STRU                      *pMsg  = VOS_NULL_PTR;              /* 定义接收到的消息类型指针                 */

    pMsg = (MMSMS_EST_REQ_STRU *)pRcvMsg;                                                             /* 消息转换                                 */

    if (MM_CONST_NUM_15 < pMsg->ulTi)
    {                                                                           /* 消息中的取值不合法                       */
        ucRet = MM_FALSE;                                                       /* 返回消息检查失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvSmsEstReq:WARNING: MMSMS_EST_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* 消息中的取值合法，存储消息               */
        g_MmSmsEstReq.ulEstCause = pMsg->ulEstCause;
        g_MmSmsEstReq.ulTi       = pMsg->ulTi;
    }

    g_MmGlobalInfo.ucPagingType = MM_MO_PAGING;

    return ucRet;                                                               /* 返回检查结果                             */
}


/***********************************************************************
 *  MODULE   : Mm_RcvSmsRelReq
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      04-03-09  新版作成
 *     2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvSmsRelReq(
                       VOS_VOID            *pRcvMsg                             /* 收到的原语头指针                         */
                       )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* 返回值                                   */
    MMSMS_REL_REQ_STRU                      *pMsg  = VOS_NULL_PTR;              /* 定义接收到的消息类型指针                 */

    pMsg = (MMSMS_REL_REQ_STRU *)pRcvMsg;                                                             /* 消息转换                                 */

    if ((MM_CONST_NUM_14 < pMsg->ulTi)
        || (MM_CONST_NUM_7 == pMsg->ulTi))
    {                                                                           /* 消息中的取值不合法                       */
        ucRet = MM_FALSE;                                                       /* 返回消息检查失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvSmsRelReq:WARNING: MMSMS_REL_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* 消息中的取值合法，存储消息               */
        g_MmSmsRelReq.ulTi = pMsg->ulTi;
    }

    return ucRet;                                                               /* 返回检查结果                             */
}


/***********************************************************************
 *  MODULE   : Mm_RcvSmsDataReq
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      04-03-09  新版作成
 *     2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvSmsDataReq(
                   VOS_VOID            *pRcvMsg                                 /* 收到的原语头指针                         */
                   )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* 返回值                                   */
    MMSMS_DATA_REQ_STRU                     *pMsg  = VOS_NULL_PTR;              /* 定义接收到的消息类型指针                 */

    pMsg = (MMSMS_DATA_REQ_STRU *)pRcvMsg;                                                             /* 消息转换                                 */

    if (MM_CONST_NUM_15 < pMsg->ulTi)
    {                                                                           /* 消息中的取值不合法                       */
        ucRet = MM_FALSE;                                                       /* 返回消息检查失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvSmsDataReq:WARNING: MMSMS_DATA_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* 消息中的取值合法，存储消息               */

    }

    return ucRet;                                                               /* 返回检查结果                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvCcPromptRej
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      04-03-10  新版作成
       2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvCcPromptRej(
                       VOS_VOID            *pRcvMsg                             /* 收到的原语头指针                         */
                       )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* 返回值                                   */
    MMCC_PROMPT_REJ_STRU                    *pMsg  = VOS_NULL_PTR;              /* 定义接收到的消息类型指针                 */

    pMsg = (MMCC_PROMPT_REJ_STRU *)pRcvMsg;                                                             /* 消息转换                                 */

    g_MmCcPromptRej.ulRefuseCause = pMsg->ulRefuseCause;

    return ucRet;                                                               /* 返回检查结果                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvMmcAttachReq
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *  1.  张志勇      04-03-10  新版作成
    2.日    期  : 2006年12月4日
      作    者  : luojian id:60022475
      修改内容  : 问题单号:A32D07777
    3.日    期   : 2011年7月25日
      作    者   : h44270
      修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
    4.日    期   : 2013年2月4日
      作    者   : w00176964
      修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
************************************************************************/
VOS_UINT8 Mm_RcvMmcAttachReq(
                       VOS_VOID            *pRcvMsg                             /* 收到的原语头指针                         */
                       )
{
    VOS_UINT8                           ucRet = MM_TRUE;                   /* 返回值                                   */
    MMCMM_ATTACH_REQ_STRU              *pMsg  = VOS_NULL_PTR;              /* 定义接收到的消息类型指针                 */

    VOS_UINT8                           ucSimPsRegStatus;
    VOS_UINT8                           ucPsAttachAllow;

    ucSimPsRegStatus = NAS_MML_GetSimPsRegStatus();
    ucPsAttachAllow  = NAS_MML_GetPsAttachAllowFlg();

    pMsg = (MMCMM_ATTACH_REQ_STRU*)pRcvMsg;                                     /* 消息转换                                 */

    if ((MMC_MM_ATTACH_TYPE_GPRS != pMsg->enAttachType)
        && (MMC_MM_ATTACH_TYPE_IMSI != pMsg->enAttachType)
        && (MMC_MM_ATTACH_TYPE_GPRS_IMSI != pMsg->enAttachType))
    {                                                                           /* 消息中的取值不合法                       */
        ucRet = MM_FALSE;                                                       /* 返回消息检查失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvMmcAttachReq:WARNING: MMCMM_ATTACH_REQ CHECK PRIMITIVE ERROR!");
    }

    if (MM_TRUE == g_MmGlobalInfo.ucSysInfoFlg)
    {
        if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
        {
            if ((VOS_TRUE == ucSimPsRegStatus)
                && (MM_UNSUPPORT_GPRS != g_MmGlobalInfo.usRac))
            {
                if((VOS_TRUE == ucPsAttachAllow)
                || (MMC_MM_ATTACH_TYPE_GPRS_IMSI == pMsg->enAttachType))
                {
                    g_MmGlobalInfo.ucLikeB = MM_FALSE;
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_RcvMmcAttachReq:INFO: MmLikeB is MM_FALSE");
                }
            }
        }
    }

    return ucRet;                                                               /* 返回检查结果                             */
}



/***********************************************************************
 *  MODULE   : Mm_RcvMmcRelReq
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
       2.日    期  : 2008年12月7日
         作    者  : l00130025
         修改内容  : 问题单号:AT2D07018,SYSCFG执行时间过长
 ************************************************************************/
VOS_UINT8 Mm_RcvMmcRelReq(
                       VOS_VOID            *pRcvMsg                             /* 收到的原语头指针                         */
                       )
{
    return MM_TRUE;                                                                   /* 返回检查结果                             */
}
/***********************************************************************
 *  MODULE   : Mm_RcvMmcModeChngReq
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      04-03-10  新版作成
       2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvMmcModeChngReq(
                       VOS_VOID            *pRcvMsg                             /* 收到的原语头指针                         */
                       )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* 返回值                                   */
    MMCMM_MODE_CHANGE_REQ_STRU              *pMsg  = VOS_NULL_PTR;              /* 定义接收到的消息类型指针                 */
    pMsg = (MMCMM_MODE_CHANGE_REQ_STRU*)pRcvMsg;                                /* 消息转换                                 */

    if ( (NAS_MML_MS_MODE_NULL != pMsg->enMsMode)
      && (NAS_MML_MS_MODE_PS_CS != pMsg->enMsMode)
      && (NAS_MML_MS_MODE_PS_ONLY != pMsg->enMsMode)
      && (NAS_MML_MS_MODE_CS_ONLY != pMsg->enMsMode) )
    {                                                                           /* 消息中的取值不合法                       */
        ucRet = MM_FALSE;                                                       /* 返回消息检查失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvMmcModeChngReq:WARNING: MMCMM_MODE_CHANGE_REQ CHECK PRIMITIVE ERROR!");
    }
    return ucRet;                                                               /* 返回检查结果                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvGmmLuIni
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇     04-03-25  新版作成
 *     2.  张志勇     2005.01.27  007005 for MM
       3.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777
       4.日    期  : 2012年3月29日
         作    者  : z00161729
         修改内容  : 支持ISR特性修改
       3.日    期   : 2012年5月7日
         作    者   : l00171473
         修改内容   : DTS2012050204913, 做保护,L模下不处理超时消息
 ************************************************************************/
VOS_UINT8 Mm_RcvGmmLuIni(
                       VOS_VOID            *pRcvMsg                             /* 收到的原语头指针                         */
                       )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* 返回值                                   */
    GMMMM_LU_INITIATION_STRU                *pstMsg  = VOS_NULL_PTR;              /* 定义接收到的消息类型指针                 */

    pstMsg = (GMMMM_LU_INITIATION_STRU*)pRcvMsg;                                  /* 消息转换                                 */

#if (FEATURE_ON == FEATURE_LTE)
    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        return MM_FALSE;
    }
#endif

    if ((GMMMM_NO_TIMER_EXPIRED != pstMsg->enTimerExpiredFlg)
     && (GMMMM_T3312_EXPIRED != pstMsg->enTimerExpiredFlg)
     && (GMMMM_T3311_EXPIRED != pstMsg->enTimerExpiredFlg)
     && (GMMMM_T3302_EXPIRED != pstMsg->enTimerExpiredFlg)
     && (GMMMM_T3330_EXPIRED != pstMsg->enTimerExpiredFlg)
     && (GMMMM_T3412OrT3423_EXPIRED != pstMsg->enTimerExpiredFlg))
    {                                                                           /* 消息中的取值不合法                       */
        ucRet = MM_FALSE;                                                       /* 返回消息检查失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvGmmLuIni:WARNING: MMCMM_LU_INITIATION CHECK PRIMITIVE ERROR!");
    }
    return ucRet;                                                               /* 返回检查结果                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvRrcAcInfoChgInd
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇     04-03-25  新版作成
 *     2.  张志勇        2005.01.07  007005 for MM
       3.日    期   : 2012年12月27日
         作    者   : s00217060
         修改内容   : for DSDA GUNAS C CORE:如果USIM卡GSM禁止接入，直接返回MM_FALSE
 ************************************************************************/
VOS_UINT8 Mm_RcvRrcAcInfoChgInd(
                            VOS_VOID            *pRcvMsg                        /* 收到的原语头指针                         */
                            )
{
    /* USIM卡禁止GSM接入时，不允许注册和寻呼业务,此处直接返回MM_FALSE，
       防止Mm_Cell_S6_E74中再设置成注册和寻呼不受限 */
    if (VOS_TRUE == NAS_MML_GetGsmForbidFlg())
    {
        return MM_FALSE;
    }
    return MM_TRUE;                                                             /* 返回检查结果                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvMmAgentInquire
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇     2005.01.28  Agent对应
 ************************************************************************/
VOS_UINT8 Mm_RcvMmAgentInquire(
                            VOS_VOID            *pRcvMsg                        /* 收到的原语头指针                         */
                            )
{
    /*Mm_SndAgentInfo();*/
    return MM_TRUE;                                                             /* 返回检查结果                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvSsAbortReq
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇   2005.02.01    新版作成
       2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvSsAbortReq(
                       VOS_VOID            *pRcvMsg                             /* 收到的原语头指针                         */
                       )
{
    VOS_UINT8                                ucRet = MM_TRUE;                   /* 返回值                                   */
    MMSS_ABORT_REQ_STRU                     *pMsg  = VOS_NULL_PTR;              /* 定义接收到的消息类型指针                 */
    pMsg = (MMSS_ABORT_REQ_STRU *)pRcvMsg;                                      /* 消息转换                                 */

    if ((pMsg->ulTransactionId > 14) || (pMsg->ulTransactionId < 8))
    {                                                                           /* 消息中的取值不合法                       */
        ucRet = MM_FALSE;                                                       /* 返回消息检查失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvSsAbortReq:WARNING: MMSS_ABORT_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* 消息中的取值合法，存储消息               */
        g_MmSsAbortReq.ulTransactionId = pMsg->ulTransactionId;
    }

    return ucRet;                                                               /* 返回检查结果                             */
}

/***********************************************************************
 *  MODULE   : Mm_RcvSmsAbortReq
 *  FUNCTION : 消息检查
 *  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8            消息检查结果
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇   2005.02.01    新版作成
       2.日    期  : 2006年12月4日
         作    者  : luojian id:60022475
         修改内容  : 问题单号:A32D07777
 ************************************************************************/
VOS_UINT8 Mm_RcvSmsAbortReq(
                       VOS_VOID            *pRcvMsg                             /* 收到的原语头指针                         */
                       )
{
    VOS_UINT8                                 ucRet = MM_TRUE;                  /* 返回值                                   */
    MMSMS_ABORT_REQ_STRU                     *pMsg  = VOS_NULL_PTR;             /* 定义接收到的消息类型指针                 */

    pMsg = (MMSMS_ABORT_REQ_STRU *)pRcvMsg;                                     /* 消息转换                                 */

    if ((pMsg->ulTransactionId > 14) || (pMsg->ulTransactionId < 8))
    {                                                                           /* 消息中的取值不合法                       */
        ucRet = MM_FALSE;                                                       /* 返回消息检查失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_RcvSmsAbortReq:WARNING: MMSMS_ABORT_REQ CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* 消息中的取值合法，存储消息               */
        g_MmSmsAbortReq.ulTransactionId = pMsg->ulTransactionId;
    }

    return ucRet;                                                               /* 返回检查结果                             */
}
/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

