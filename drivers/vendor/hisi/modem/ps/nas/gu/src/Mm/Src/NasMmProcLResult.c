/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmProcLResult.c
  版 本 号   : 初稿
  作    者   : zhoujun /40661
  生成日期   : 2011年03月14日
  最近修改   :
  功能描述   : MM收到L模注册结果的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2010年11月12日
    作    者   : zhoujun /40661
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "MM_Inc.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "PsTypeDef.h"
#include  "MmLmmInterface.h"
#include "NasCommDef.h"
#include "MM_Share.h"
#include "NasMmProcLResult.h"
#endif
#include "MM_Ext.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMPROCLRESULT_C

/*lint -save -e958 */

#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MM_ProcLmmRejCause3
 功能描述  : 处理来自LMM的卡无效的原因值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月28日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2011年11月3日
    作    者   : z00161729
    修改内容   : L下开机被拒原因值3情况，应该先更新mm服务状态再迁状态，因为前状态里会发attach cnf消息带的服务状态不对
  3.日    期   : 2014年8月12日
    作    者   : z00161729
    修改内容   : DTS2014081100327:L下卡无效需要设置imsi为无效，后续发起紧急呼叫cm service req中应该携带IMEI
*****************************************************************************/
VOS_VOID  NAS_MM_ProcLmmRejCause3( VOS_VOID )
{
    /* MM parameters update status U3 ROAMING NOT ALLOWED*/
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);

    /*delete TMSI, LAI and ciphering key sequence number */
    NAS_MM_DelLaiTmsiCK();

    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_IMSI_PRESENT;

    /* 更新服务状态 */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;

    /*MM state is MM_IDLE_NO_IMSI*/
    Mm_ComSetMmState(MM_IDLE_NO_IMSI);

    NAS_MML_SetSimCsRegStatus(VOS_FALSE);

}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcLmmAttachCause_Handling
 功能描述  : MM处理来自LMM的Attach 拒绝原因值
 输入参数  : ulRejectCause:拒绝原因值
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月14日
    作    者   : luokaihui / 00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年10月27日
    作    者   : s46746
    修改内容   : V7R1 PhaseIII,支持L模联合注册
  3.日    期   : 2013年03月06日
    作    者   : s00217060
    修改内容   : for V7R2_CR:增加原因值#35的处理
  4.日    期   : 2013年12月24日
    作    者   : w00242748
    修改内容   : DTS2013101106863:L下被拒原因值#35，只有在R10及其协议以上处理才与#11
                 原因值处理相同，否则当做OTHER CAUSE来处理。
*****************************************************************************/
VOS_VOID  NAS_MM_ProcLmmAttachCause_Handling(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enRejectCause
)
{
    NAS_MML_MS_3GPP_REL_STRU                               *pstMs3GppRel = VOS_NULL_PTR;
    NAS_LMM_CN_CAUSE_ENUM_UINT8                             enTmpCause;

    pstMs3GppRel = NAS_MML_GetMs3GppRel();
    enTmpCause   = enRejectCause;

    /* 当前原因值是#35且版本为R10版本，将原因值转定义成11，见协议3GPP 24.301 */
    if ( (NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN == enTmpCause)
      && (NAS_MML_3GPP_REL_R9 < pstMs3GppRel->enLteNasRelease) )
    {
        enTmpCause = NAS_EMM_CAUSE_PLMN_NOT_ALLOW;
    }

    switch ( enTmpCause )
    {
        case NAS_EMM_CAUSE_ILLEGAL_UE:
        case NAS_EMM_CAUSE_ILLEGAL_ME:
        case NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:
            NAS_MM_ProcLmmRejCause3();
            break;

        case NAS_EMM_CAUSE_PLMN_NOT_ALLOW:

            /*handle the MM parameters update status U3 ROAMING NOT ALLOWED*/
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);
            /*delete TMSI, LAI and ciphering key sequence numbe*/
            NAS_MM_DelLaiTmsiCK();

            /*reset location update attempt counter*/
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;

            /*迁入MM_IDLE_NO_CELL_AVAILABLE*/
            Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

            break;

        default :
            break;
    }

}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcLmmTauCause_Handling
 功能描述  : MM处理来自LMM的网络触发的TAU 拒绝原因值
 输入参数  : ulRejectCause:拒绝原因值
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月14日
    作    者   : luokaihui / 00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年10月27日
    作    者   : s46746
    修改内容   : V7R1 PhaseIII,支持L模联合注册
  3.日    期   : 2013年03月06日
    作    者   : s00217060
    修改内容   : for V7R2_CR:增加原因值#35的处理
  4.日    期   : 2013年12月24日
    作    者   : w00242748
    修改内容   : DTS2013101106863:L下被拒原因值#35，只有在R10及其协议以上处理才与#11
                 原因值处理相同，否则当做OTHER CAUSE来处理。
  5.日    期   : 2015年4月20日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_MM_ProcLmmTauCause_Handling(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enRejectCause
)
{
    NAS_MML_MS_3GPP_REL_STRU                               *pstMs3GppRel = VOS_NULL_PTR;
    NAS_LMM_CN_CAUSE_ENUM_UINT8                             enTmpCause;

    pstMs3GppRel = NAS_MML_GetMs3GppRel();
    enTmpCause   = enRejectCause;

    /* 当前原因值是#35且版本为R10版本，将原因值转定义成11，见协议3GPP 24.301 */
    if ( (NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN == enTmpCause)
      && (NAS_MML_3GPP_REL_R9 < pstMs3GppRel->enLteNasRelease) )
    {
        enTmpCause = NAS_EMM_CAUSE_PLMN_NOT_ALLOW;
    }

    switch ( enTmpCause )
    {
        case NAS_EMM_CAUSE_ILLEGAL_UE:
        case NAS_EMM_CAUSE_ILLEGAL_ME:
        case NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:
            /* 24301_CR1595R2_(Rel-11)_C1-124966,对应24301 5.5.3.2.5
               章节描述处理同#3和#6,由于gmm和mmc tau被拒#8原逻辑已按#3处理,没用协议版本控制，
               此处也不用协议版本控制 */
            NAS_MM_ProcLmmRejCause3();
            break;

        case NAS_EMM_CAUSE_PLMN_NOT_ALLOW:

            /*MM parameters update status U3 ROAMING NOT ALLOWED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);

            /*delete TMSI, LAI, ciphering key sequence number */
            NAS_MM_DelLaiTmsiCK();

            /*reset the location update attempt counter*/
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;

            /*迁入MM_IDLE_NO_CELL_AVAILABLE*/
            Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

            break;

        default :
            break;
    }

}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcLmmNwDetachIndCause_Handling
 功能描述  : MM处理来自LMM的网络触发的DETACH 拒绝原因值
 输入参数  : ulRejectCause:拒绝原因值
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月14日
    作    者   : luokaihui / 00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年10月27日
    作    者   : s46746
    修改内容   : V7R1 PhaseIII,支持L模联合注册

  3.日    期   : 2012年4月6日
    作    者   : z40661
    修改内容   : DTS2012032803448需要删除位置区信息
*****************************************************************************/
VOS_VOID  NAS_MM_ProcLmmNwDetachIndCause_Handling(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enRejectCause
)
{
    switch (enRejectCause)
    {
        

        case NAS_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS:
        case NAS_EMM_CAUSE_ILLEGAL_UE:
        case NAS_EMM_CAUSE_ILLEGAL_ME:
        case NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:
            NAS_MM_ProcLmmRejCause3();
            break;

        case NAS_EMM_CAUSE_PLMN_NOT_ALLOW:

            /*handle the MM parameters update status U3 ROAMING NOT ALLOWED*/
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);

            /*delete TMSI, LAI and ciphering key sequence number*/
            NAS_MM_DelLaiTmsiCK();

            /* 更新服务状态 */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

            /*MM state is MM_IDLE_NO_CELL_AVAILABLE*/
            Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

            g_MmSubLyrShare.MmShare.ucCsAttachState = MM_STATUS_DETACHED;

            break;

        case NAS_EMM_CAUSE_TA_NOT_ALLOW:
        case NAS_EMM_CAUSE_ROAM_NOT_ALLOW:
        case NAS_EMM_CAUSE_NO_SUITABL_CELL:

            /* ETSI TS 124 301
            5.5.2.3.2 Network initiated detach procedure completion by the UE
            If A/Gb mode or Iu mode is supported by the UE, the UE shall handle the GMM parameters GMM state, RAI,
            P-TMSI, P-TMSI signature, GPRS ciphering key sequence number, GPRS update status and GPRS attach
            attempt counter as specified in 3GPP TS 24.008 [13] for the case when a DETACH REQUEST is received with
            the GMM cause with the same value and with detach type set to "re-attach not required". If the UE is IMSI
            attached for non-EPS services, the UE shall in addition handle the MM parameters update status, TMSI, LAI,
            ciphering key sequence number and location update attempt counter as specified in 3GPP TS 24.008 [13] for the
            case when a DETACH REQUEST is received with the GMM cause with the same value and with detach type set
            to "re-attach not required".

            TS 24008
            4.7.4.2.2   Network initiated GPRS detach procedure completion by the MS
            # 12    (Location area not allowed);
            -   If the MS is IMSI attached, the MS shall set the update status to U3 ROAMING NOT ALLOWED, shall delete
            any TMSI, LAI and ciphering key sequence number and shall reset the location update attempt counter.
            The new MM state is MM IDLE.
            */

            /* 如果CS为已注册状态 */
            if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
            {
                /* Update Status置为NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED */
                NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);

                /* 删除TMSI, LAI and ciphering key sequence number */
                NAS_MM_DelLaiTmsiCK();

                /* reset location update attempt counter */
                g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;

                /* 更新服务状态 */
                g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

                /* 迁入MM_IDLE_LIMITED_SERVICE */
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

                g_MmSubLyrShare.MmShare.ucCsAttachState = MM_STATUS_DETACHED;
            }
            break;

        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW:
        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN:

            /* ETSI TS 124 301
            5.5.2.3.2 Network initiated detach procedure completion by the UE
            #7 (EPS services not allowed);
            A UE operating in CS/PS mode 1 or CS/PS mode 2 of operation is still IMSI attached for non-EPS services in
            the network. The UE operating in CS/PS mode 1 or CS/PS mode 2 of operation shall set the update status to U2
            NOT UPDATED

            #14 (EPS services not allowed in this PLMN)
            A UE operating in CS/PS mode 1 or CS/PS mode 2 of operation is still IMSI attached for non-EPS services and
            shall set the update status to U2 NOT UPDATED.
            */

            /* 如果CS为已注册状态 */
            if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
            {
                /* Update Status置为NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
                NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);


                /* 删除TMSI, LAI CKSN */
                NAS_MM_DelLaiTmsiCK();

                /* 刷新sim的cs loci 0x6F7E文件中相应参数 */
                NAS_MM_WriteLocaInCard();
            }
            break;

        default:

            /* 不处理 */

            break;
     }

     return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcLmmAttachRstInd
 功能描述  : MM在MM IDLE LIMITED SERVICE状态下处理来自EMM的Attach结果
 输入参数  : pstLmmAttachInd:消息首址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月14日
    作    者   : luokaihui / 00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年10月27日
    作    者   : s46746
    修改内容   : V7R1 PhaseIII,支持L模联合注册
  3.日    期   : 2012年1月8日
    作    者   : z00161729
    修改内容   : V7R1 PhaseIIV修改
  3.日    期   : 2012年1月2日
    作    者   : w00167002
    修改内容   : DTS2011102200381:L下注册被拒#12,LMM给MMC带的ATTACH及TAU
                 中的结果为MMC_LMM_ATT_RSLT_FORBID，MMC收到此结果后按照禁止网络
                 来处理而发起了搜网。
*****************************************************************************/
VOS_VOID  NAS_MM_ProcLmmAttachRstInd(
    MMCMM_LMM_ATTACH_IND_STRU          *pstLmmAttachInd
)
{

    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause;

    enCnCause      = NAS_EMM_CAUSE_BUTT;

    if (VOS_TRUE == pstLmmAttachInd->bitOpCnCause)
    {
        enCnCause = pstLmmAttachInd->ucCnCause;
    }

    /* 迁入MM_IDLE_NO_CELL_AVAILABLE*/
    Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

    /* PS ONLY 只要处理FAIL情况 */
    switch (pstLmmAttachInd->ulAttachRslt)
    {
        case MMC_LMM_ATT_RSLT_CN_REJ:
            NAS_MM_ProcLmmAttachCause_Handling(enCnCause);
            break;

        case MMC_LMM_ATT_RSLT_AUTH_REJ:
            NAS_MM_ProcLmmAuthRstInd();
            break;

        case MMC_LMM_ATT_RSLT_SUCCESS:
        case MMC_LMM_ATT_RSLT_ACCESS_BAR:
        case MMC_LMM_ATT_RSLT_TIMER_EXP:
        case MMC_LMM_ATT_RSLT_FORBID_PLMN:
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS:
        case MMC_LMM_ATT_RSLT_FORBID_PLMN_FOR_GPRS:
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_ROAMING:
        case MMC_LMM_ATT_RSLT_FAILURE:
        case MMC_LMM_ATT_RSLT_ESM_FAILURE:
        case MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE:
        case MMC_LMM_ATT_RSLT_MT_DETACH_FAILURE:
        case MMC_LMM_ATT_RSLT_T3402_RUNNING:
        case MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW:
            /* 不处理 */
            break;

        default:

            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_ProcLmmAttachRstInd: unexpected attach rslt.");
            break;
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcLmmTauRstInd
 功能描述  : MM处理来自EMM的TAU结果
 输入参数  : pstMsg:消息首址
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月14日
    作    者   : luokaihui / 00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年10月27日
    作    者   : s46746
    修改内容   : V7R1 PhaseIII,支持L模联合注册
  3.日    期   : 2012年1月8日
    作    者   : z00161729
    修改内容   : V7R1 PhaseIV
  4.日    期   : 2012年2月9日
    作    者   : w00167002
    修改内容   : 增加LMM上报注册失败场景原因的处理
*****************************************************************************/
VOS_VOID  NAS_MM_ProcLmmTauRstInd(
    MMCMM_LMM_TAU_RESULT_IND_STRU      *pstTauInd
)
{
    /* # 3(Illegal MS),
    # 6(Illegal ME),
    If the MS is IMSI attached, the MS shall in addition set the update status
    to U3 ROAMING NOT ALLOWED, shall delete any TMSI, LAI and ciphering key
    sequence number. If the MS is operating in MS operation mode A and an RR
    connection exists, the MS shall abort the RR connection, unless an
    emergency call is ongoing. The SIM/USIM shall be considered as invalid
    also for non-GPRS services until switching off or the SIM/USIM is removed.
    */

    /* # 11(PLMN not allowed),
       # 12(Location area not allowed),
       # 13(Roaming not allowed in this location area),
       # 14(GPRS services not allowed in this PLMN),
       # 15((No Suitable Cells In Location Area)

       If no RR connection exists, the MS shall perform the following additional
       actions immediately. If the MS is operating in MS operation mode A and an
       RR connection exists, the MS shall perform these actions when the RR
       connection is subsequently released:
       -   If the MS is IMSI attached, the MS shall set the update status to
       U3 ROAMING NOT ALLOWED, shall delete any TMSI, LAI and ciphering key
       sequence number and shall reset the location update attempt counter.
       The new MM state is MM IDLE.
   */


    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause;

    enCnCause      = NAS_EMM_CAUSE_BUTT;

    if (VOS_TRUE == pstTauInd->bitOpCnCause)
    {
        enCnCause = pstTauInd->ucCnCause;
    }

    /*迁入MM_IDLE_NO_CELL_AVAILABLE;*/
    Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

    switch (pstTauInd->ulTauRst)
    {
        case MMC_LMM_TAU_RSLT_CN_REJ:
            NAS_MM_ProcLmmTauCause_Handling(enCnCause);
            break;

        case MMC_LMM_TAU_RSLT_AUTH_REJ:
            NAS_MM_ProcLmmAuthRstInd();
            break;

        case MMC_LMM_TAU_RSLT_SUCCESS:
        case MMC_LMM_TAU_RSLT_ACCESS_BARED:
        case MMC_LMM_TAU_RSLT_TIMER_EXP:
        case MMC_LMM_TAU_RSLT_FORBID_PLMN:
        case MMC_LMM_TAU_RSLT_FORBID_TA_FOR_RPOS:
        case MMC_LMM_TAU_RSLT_FORBID_TA_FOR_ROAMING:
        case MMC_LMM_TAU_RSLT_FORBID_PLMN_FOR_GPRS:
        case MMC_LMM_TAU_RSLT_FAILURE:
        case MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE:
        case MMC_LMM_TAU_RSLT_MT_DETACH_FAILURE:
        case MMC_LMM_TAU_RSLT_T3402_RUNNING:
            /* 不处理 */
            break;

        default:

            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_ProcLmmTauRstInd: unexpected attach rslt.");
            break;
    }

}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcLmmServiceRstIndInLimitedService
 功能描述  : MM处理来自LMM的Service rej结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月14日
    作    者   : luokaihui / 00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年10月27日
    作    者   : s46746
    修改内容   : V7R1 PhaseIII,支持L模联合注册
  3.日    期   : 2013年03月06日
    作    者   : s00217060
    修改内容   : for V7R2_CR:增加原因值#35的处理
  4.日    期   : 2013年12月24日
    作    者   : w00242748
    修改内容   : DTS2013101106863:L下被拒原因值#35，只有在R10及其协议以上处理才与#11
                 原因值处理相同，否则当做OTHER CAUSE来处理。
  5.日    期   : 2014年8月4日
    作    者   : w00167002
    修改内容   : DTS2014080407625:在L下注册成功后，业务被ACCESS BAR时,MM不进行状态迁移。
  6.日    期   : 2015年4月19日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID  NAS_MM_ProcLmmServiceRstInd(
    MMCMM_LMM_SERVICE_RESULT_IND_STRU  *pstLmmServiceInd
)
{
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause;
    NAS_MML_MS_3GPP_REL_STRU                               *pstMs3GppRel = VOS_NULL_PTR;

    pstMs3GppRel = NAS_MML_GetMs3GppRel();

    enCnCause      = NAS_EMM_CAUSE_BUTT;

    if (MMC_LMM_SERVICE_RSLT_CN_REJ == pstLmmServiceInd->ulServiceRst)
    {
        if (VOS_TRUE == pstLmmServiceInd->bitOpCnCause)
        {
            enCnCause = pstLmmServiceInd->ucCnCause;
        }

        /* 当前原因值是#35且版本为R10版本，将原因值转定义成11，见协议3GPP 24.301 */
        if ( (NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN == enCnCause)
          && (NAS_MML_3GPP_REL_R9 < pstMs3GppRel->enLteNasRelease) )
        {
            enCnCause = NAS_EMM_CAUSE_PLMN_NOT_ALLOW;
        }

        switch (enCnCause)
        {

            
            case NAS_EMM_CAUSE_ILLEGAL_UE:
            case NAS_EMM_CAUSE_ILLEGAL_ME:
                NAS_MM_ProcLmmRejCause3();
                break;

            case NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:
                /* 24301_CR1595R2_(Rel-11)_C1-124966，对应24301 5.6.1.5章节，
                   处理同#3,#6，该CR受协议版本控制 */
                if (NAS_MML_GetLte3gppRelVersion() >= NAS_MML_3GPP_REL_R11)
                {
                    NAS_MM_ProcLmmRejCause3();
                }
                break;

            case NAS_EMM_CAUSE_PLMN_NOT_ALLOW:

                /*set  the MM parameters update statu  U3 ROAMING NOT ALLOWED*/
                NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);

                /*delete TMSI, LAI, ciphering key sequence number*/
                NAS_MM_DelLaiTmsiCK();

                /*24301 set the location update attempt counter*/
                g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;

                /* 更新服务状态 */
                g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

                /*迁入 MM_IDLE_NO_CELL_AVAILABLE*/
                Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

                break;

            /* 24301_CR1254R3_(Rel-11)_C1-115100 ESR被拒18原因值的处理更新,
              24301 5.6.1.5 Service request procedure not accepted by the network
              The UE shall set the update status to U2 NOT UPDATED.该CR受协议版本控制 */
            case NAS_EMM_CAUSE_CS_DOMAIN_NOT_AVAILABLE:
                if (NAS_MML_GetLte3gppRelVersion() >= NAS_MML_3GPP_REL_R11)
                {
                    /* Update Status置为NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
                    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

                    /* 删除TMSI, LAI CKSN */
                    NAS_MM_DelLaiTmsiCK();

                    /* 迁入MM_IDLE_NO_CELL_AVAILABLE */
                    Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);
                }
                break;

           default:
               break;

        }
    }

    /* 在收到SERVICE REJ时不进行状态迁移 */

    else if (MMC_LMM_SERVICE_RSLT_AUTH_REJ == pstLmmServiceInd->ulServiceRst)
    {
        NAS_MM_ProcLmmAuthRstInd();
    }
    else
    {
    }

}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcLmmAuthRstIndInLimitedService
 功能描述  : MM处理来自LMM的签权失败结果
 输入参数  : pstMsg:消息首址
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月14日
    作    者   : luokaihui / 00167671
    修改内容   : 新生成函数
  2.日    期   : 2014年8月12日
    作    者   : z00161729
    修改内容   : DTS2014081100327:L下卡无效需要设置imsi为无效，后续发起紧急呼叫cm service req中应该携带IMEI
*****************************************************************************/
VOS_VOID  NAS_MM_ProcLmmAuthRstInd(VOS_VOID)
{
    /*handle the MM parameters update status U3 ROAMING NOT ALLOWED*/
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);

    /*delete TMSI, LAI and ciphering key sequence numbe*/
    NAS_MM_DelLaiTmsiCK();

    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_IMSI_PRESENT;

    /* 更新服务状态 */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;

    /*迁入MM_IDLE_NO_IMSI*/
    Mm_ComSetMmState(MM_IDLE_NO_IMSI);

    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
}

/*****************************************************************************
 函 数 名  : NAS_MM_ConvertLmmPlmnToNasPLMN
 功能描述  : 将Lmm中的3字节格式PLMN转换为MCC和MNC分开的格式
 输入参数  : pucLmmPlmn
 输出参数  : NAS_MML_PLMN_ID_STRU pstNasPlmn
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 修改历史     :
 1.日    期   : 2011年10月27日
   作    者   : s46746
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_MM_ConvertLmmPlmnToNasPLMN(
    VOS_UINT8                          *pucLmmPlmn,
    NAS_MML_PLMN_ID_STRU               *pstNasPlmn
)
{
    VOS_UINT32                          ulTempData;
    NAS_MML_PLMN_ID_STRU                stPlmn;

    /*
       PLMN BCD 编码 方式

       MCC digit 2,  MCC digit 1, ----OCTET 1
       MNC digit 3,  MCC digit 3, ----OCTET 2
       MNC digit 2,  MNC digit 1, ----OCTET 3
    */

    ulTempData = NAS_MML_OCTET_LOW_FOUR_BITS & pucLmmPlmn[0];
    stPlmn.ulMcc = ulTempData;
    ulTempData = (NAS_MML_OCTET_HIGH_FOUR_BITS & pucLmmPlmn[0]) >> NAS_MML_OCTET_MOVE_FOUR_BITS;
    stPlmn.ulMcc |= ulTempData << NAS_MML_OCTET_MOVE_EIGHT_BITS;

    ulTempData = NAS_MML_OCTET_LOW_FOUR_BITS & pucLmmPlmn[1];
    stPlmn.ulMcc |= ulTempData << NAS_MML_OCTET_MOVE_SIXTEEN_BITS;
    ulTempData = (NAS_MML_OCTET_HIGH_FOUR_BITS & pucLmmPlmn[1]) >> NAS_MML_OCTET_MOVE_FOUR_BITS;

    stPlmn.ulMnc = ulTempData << NAS_MML_OCTET_MOVE_SIXTEEN_BITS;
    ulTempData = NAS_MML_OCTET_LOW_FOUR_BITS & pucLmmPlmn[2];
    stPlmn.ulMnc |= ulTempData;
    ulTempData = (NAS_MML_OCTET_HIGH_FOUR_BITS & pucLmmPlmn[2]) >> NAS_MML_OCTET_MOVE_FOUR_BITS;
    stPlmn.ulMnc |= ulTempData << NAS_MML_OCTET_MOVE_EIGHT_BITS;

    *pstNasPlmn = stPlmn;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcLmmRejOtherCause
 功能描述  : 对LMM联合注册被拒other cause处理
 输入参数  : ulAttemptCounter:已经尝试次数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月27日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年11月9日
   作    者   : t00212959
   修改内容   : DTS2012110705279
 3.日    期   : 2014年8月11日
   作    者   : w00167002
   修改内容   : DTS2014080407625:在ATTEMPT TO UPDATE状态也尝试发起普通呼叫。
 4.日    期   : 2015年4月19日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
 5.日    期   : 2015年7月7日
    作    者   : s00217060
    修改内容   : DTS2015062700880修改:LTE下TAU失败小于5次时，更新状态为U2,但不删除TMSI,LAI,CKSN,EPLMN
*****************************************************************************/
VOS_VOID NAS_MM_ProcLmmRejOtherCause(
    VOS_UINT32                          ulAttemptCounter,
    VOS_UINT32                          ulLmmBitOpAtmpCnt
)
{
    /* ETSI TS 124 301 R11
    5.5.3.3.6 Abnormal cases in the UE

    -   If the tracking area updating attempt counter is less than 5,
    the UE shall set the update status to U2 NOT UPDATED,
    but shall not delete any LAI, TMSI, ciphering key sequence number and list of equivalent PLMNs;
    or
    -   if the tracking area updating attempt counter is equal to 5,
    the UE shall delete any LAI, TMSI, ciphering key sequence number and list of equivalent PLMNs
    and set the update status to U2 NOT UPDATED.

    A UE operating in CS/PS mode 1 of operation shall select GERAN or UTRAN radio access technology
    and proceed with appropriate MM or GMM specific procedures.
    */

    /* 尝试次数无效，更新为限制驻留*/
    if ( VOS_FALSE == ulLmmBitOpAtmpCnt)
    {
        /* 更新服务状态 */
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

        /* 迁入MM_IDLE_LIMITED_SERVICE */
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

        return;
    }

    if (ulAttemptCounter < MM_EMM_MAX_ATTEMPT_COUNTER)
    {
        /* 24301_CR1374_(Rel-11)_C1-120820 联合TAU失败，被拒原因值为other cause，
           尝试次数小于5时，MM  UPDATE STATUS需要更新为U2 NOT UPDATED,
           24301 5.5.3.3.6章节描述:
           If the tracking area updating attempt counter is less than 5,
           the UE shall set the update status to U2 NOT UPDATED,
           but shall not delete any LAI, TMSI, ciphering key sequence number and list of equivalent PLMNs;
           该CR不受协议版本控制 */

        /* Update Status置为NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

        /* 迁入MM_IDLE_ATTEMPTING_TO_UPDATE:下次联合attach或联合tau时，LMM会通知MM，MM再迁到LOCATION_UPDATING_PENDING */
        Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
    }
    else
    {
        /* Update Status置为NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

        /* 删除TMSI, LAI CKSN */
        NAS_MM_DelLaiTmsiCK();

        /* 更新服务状态 */
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;

        /* 迁入MM_IDLE_ATTEMPTING_TO_UPDATE */
        Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

        NAS_MM_ProcBufferedCsfbService();
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcLmmCombinedAttachCause
 功能描述  : 对LMM联合注册被拒原因值处理
 输入参数  : ulRejectCause:LMM的Combinedined Attach拒绝原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月27日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年11月10日
   作    者   : t00212959
   修改内容   : DTS2012110705279
 3.日    期   : 2013年03月06日
   作    者   : s00217060
   修改内容   : for V7R2_CR:增加原因值#35的处理
 4.日    期   : 2013年12月24日
   作    者   : w00242748
   修改内容   : DTS2013101106863:L下被拒原因值#35，只有在R10及其协议以上处理才与#11
                 原因值处理相同，否则当做OTHER CAUSE来处理。
 5.日    期   : 2015年4月19日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID  NAS_MM_ProcLmmCombinedAttachCause(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enRejectCause,
    VOS_UINT32                          ulAttemptCounter,
    VOS_UINT32                          ulLmmBitOpAtmpCnt
)
{
    NAS_MML_MS_3GPP_REL_STRU                               *pstMs3GppRel = VOS_NULL_PTR;
    NAS_LMM_CN_CAUSE_ENUM_UINT8                             enTmpCause;

    pstMs3GppRel = NAS_MML_GetMs3GppRel();
    enTmpCause   = enRejectCause;

    /* 当前原因值是#35且版本为R10版本，将原因值转定义成11，见协议3GPP 24.301 */
    if ( (NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN == enTmpCause)
      && (NAS_MML_3GPP_REL_R9 < pstMs3GppRel->enLteNasRelease) )
    {
        enTmpCause = NAS_EMM_CAUSE_PLMN_NOT_ALLOW;
    }

    switch ( enTmpCause )
    {
        case NAS_EMM_CAUSE_ILLEGAL_UE:
        case NAS_EMM_CAUSE_ILLEGAL_ME:
        case NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:

            /* ETSI TS 124 301
            5.5.1.3.5 Combined attach not accepted by the network
            #3 (Illegal UE);
            #6 (Illegal ME); or
            #8 (EPS services and non-EPS services not allowed);
            If A/Gb mode or Iu mode is supported by the UE, the UE shall in addition handle the MM parameters update
            status, TMSI, LAI and ciphering key sequence number, and the GMM parameters GMM state, GPRS update
            status, P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number as specified in
            3GPP TS 24.008 [13] for the case when the combined attach procedure is rejected with the GMM cause with the
            same value.

            TS 24008
            4.7.3.2.4   Combined GPRS attach not accepted by the network
            # 3     (Illegal MS);
            # 6     (Illegal ME), or
            # 8     (GPRS services and non-GPRS services not allowed);

            The MS shall set the update status to U3 ROAMING NOT ALLOWED, shall delete any TMSI, LAI
            and ciphering key sequence number. The SIM/USIM shall be considered as invalid for GPRS
            and non-GPRS services until switching off or the SIM/USIM is removed.
            */

            /* 调用NAS_MM_ProcLmmRejCause3进行处理 */
            NAS_MM_ProcLmmRejCause3();
            break;

        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW:
        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN:

            /* 24301_CR1423_(Rel-11)_C1-121278 CS PS MODE1或CS PS MODE2联合attach或
               周期性TAU被拒原因值为7和14时，MM  UPDATE STATUS需要更新为U2,
               对应24301 5.5.1.3.5章节描述:
               #7: A UE, which is already IMSI attached for non-EPS services,
                   is still IMSI attached for non-EPS services in the network and
                   shall set the update status to U2 NOT UPDATED.
               #14: A UE operating in CS/PS mode 1 or CS/PS mode 2 of operation,
                    which is already IMSI attached for non-EPS services in the network,
                    is still IMSI attached for non-EPS services in the networkand shall
                    set the update status to U2 NOT UPDATED. 该CR不受协议版本控制 */

            /* Update Status置为NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

            /* 删除TMSI, LAI CKSN */
            NAS_MM_DelLaiTmsiCK();


            break;



        case NAS_EMM_CAUSE_PLMN_NOT_ALLOW:
        case NAS_EMM_CAUSE_TA_NOT_ALLOW:
        case NAS_EMM_CAUSE_ROAM_NOT_ALLOW:
        case NAS_EMM_CAUSE_NO_SUITABL_CELL:

            /* ETSI TS 124 301
            5.5.1.3.5 Combined attach not accepted by the network
            #11 (PLMN not allowed);
            #12 (Tracking area not allowed);
            #13 (Roaming not allowed in this tracking area);
            #15 (No suitable cells in tracking area);
            If A/Gb mode or Iu mode is supported by the UE, the UE shall in addition handle the MM parameters update
            status, TMSI, LAI, ciphering key sequence number and location update attempt counter, and the GMM
            parameters GMM state, GPRS update status, P-TMSI, P-TMSI signature, RAI, GPRS ciphering key sequence
            number and GPRS attach attempt counter as specified in 3GPP TS 24.008 [13] for the case when the combined
            attach procedure is rejected with the GMM cause with the same value and no RR connection exists.

            TS 24008
            4.7.3.2.4   Combined GPRS attach not accepted by the network
            # 11    (PLMN not allowed);
            The MS shall set the update status to U3 ROAMING NOT ALLOWED, reset the location update attempt counter and
            shall delete any TMSI, LAI and ciphering key sequence number. The new MM state is MM IDLE.
            */

            /* Update Status置为NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);

            /* 删除TMSI, LAI and ciphering key sequence number */
            NAS_MM_DelLaiTmsiCK();

            /* reset location update attempt counter */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;

            /* 更新服务状态 */
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

            /* 迁入MM_IDLE_LIMITED_SERVICE */
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

            break;

        default :

            NAS_MM_ProcLmmRejOtherCause(ulAttemptCounter, ulLmmBitOpAtmpCnt);

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcLmmCombinedTauCause
 功能描述  : 对LMM联合RAU被拒原因值处理
 输入参数  : ulRejectCause:LMM的Combinedined RAU拒绝原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月27日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2012年4月6日
   作    者   : z40661
   修改内容   : DTS2012032803448，删除LAI信息
 3.日    期   : 2012年11月10日
   作    者   : t00212959
   修改内容   : DTS2012110705279
 4.日    期   : 2013年03月06日
   作    者   : s00217060
   修改内容   : for V7R2_CR:增加原因值#40,#35的处理
 5.日    期   : 2013年12月24日
   作    者   : w00242748
   修改内容   : DTS2013101106863:L下被拒原因值#35，只有在R10及其协议以上处理才与#11
                原因值处理相同，否则当做OTHER CAUSE来处理。

*****************************************************************************/
VOS_VOID  NAS_MM_ProcLmmCombinedTauCause(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enRejectCause,
    VOS_UINT32                          ulAttemptCounter,
    VOS_UINT32                          ulLmmBitOpAtmpCnt
)
{
    NAS_MML_MS_3GPP_REL_STRU                               *pstMs3GppRel = VOS_NULL_PTR;
    NAS_LMM_CN_CAUSE_ENUM_UINT8                             enTmpCause;

    pstMs3GppRel = NAS_MML_GetMs3GppRel();
    enTmpCause   = enRejectCause;

    /* 版本为R10版本及以后版本，当前原因值是#35将原因值转定义成#11，见协议3GPP
    24.301 5.5.3.3.5 */
    /* 版本为R10版本及以后版本，当前原因值是#40将原因值转定义成#10，见协议3GPP
    24.301 5.5.3.3.5 */
    if (NAS_MML_3GPP_REL_R9 < pstMs3GppRel->enLteNasRelease)
    {
        if (NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN == enTmpCause)
        {
            enTmpCause = NAS_EMM_CAUSE_PLMN_NOT_ALLOW;
        }

    }

    switch ( enTmpCause )
    {
        case NAS_EMM_CAUSE_ILLEGAL_UE:
        case NAS_EMM_CAUSE_ILLEGAL_ME:
        case NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:

            /* ETSI TS 124 301
            5.5.3.3.5 Combined tracking area updating procedure not accepted by the network
            #3 (Illegal UE);
            #6 (Illegal ME); or
            #8 (EPS services and non-EPS services not allowed);
            If A/Gb mode or Iu mode is supported by the UE, the UE shall handle the MM parameters update status, TMSI,
            LAI and ciphering key sequence number, and the GMM parameters GMM state, GPRS update status, P-TMSI,
            P-TMSI signature, RAI and GPRS ciphering key sequence number as specified in 3GPP TS 24.008 [13] for the
            case when the combined routing area updating procedure is rejected with the GMM cause with the same value.

            TS 24008
            4.7.3.2.4   Combined GPRS attach not accepted by the network
            # 3     (Illegal MS);
            # 6     (Illegal ME), or
            # 8     (GPRS services and non-GPRS services not allowed);

            The MS shall set the GPRS update status to GU3 ROAMING NOT ALLOWED and the update status to U3 ROAMING NOT ALLOWED
            (and shall store it according to subclause 4.1.3.2) and enter the state GMM-DEREGISTERED. Furthermore,
            it shall delete any P-TMSI, P-TMSI signature, TMSI, RAI, LAI, ciphering key sequence number and
            GPRS ciphering key sequence number and shall consider the SIM/USIM as invalid for GPRS and non GPRS services
            until switching off or the SIM/USIM is removed.
            */

            /* 调用NAS_MM_ProcLmmRejCause3进行处理 */
            NAS_MM_ProcLmmRejCause3();
            break;

        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW:

            /* ETSI TS 124 301
            5.5.3.3.5 Combined tracking area updating procedure not accepted by the network
            #7 (EPS services not allowed);
            A UE in CS/PS mode 1 or CS/PS mode 2 of operation is still IMSI attached for non-EPS services. The UE shall
            set the update status to U2 NOT UPDATED
            */

            /* Update Status置为NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

            /* 删除TMSI, LAI CKSN */
            NAS_MM_DelLaiTmsiCK();

            /* 刷新sim的cs loci 0x6F7E文件中相应参数 */
            NAS_MM_WriteLocaInCard();

            break;

        case NAS_EMM_CAUSE_MS_ID_CANNOT_BE_DERIVED_BY_NW:
        case NAS_EMM_CAUSE_EPS_IMPLICITLY_DETACHED:
        case NAS_EMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED:

            /* ETSI TS 124 301
            5.5.3.3.5 Combined tracking area updating procedure not accepted by the network
            #9 (UE identity cannot be derived by the network);
                The UE shall set the EPS update status to EU2 NOT UPDATED (and shall store it according to subclause 5.1.3.3)
                and shall delete any GUTI, last visited registered TAI, TAI List and eKSI.
                The UE shall delete the list of equivalent PLMNs and enter the state EMM-DEREGISTERED.
                Subsequently, the UE shall automatically initiate the attach procedure.
                If A/Gb mode or Iu mode is supported by the UE, the UE shall in addition handle the GMM parameters GMM state, GPRS update status, P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number
                as specified in 3GPP TS 24.008 [13] for the case when the combined routing area updating procedure is rejected with the GMM cause with the same value.
                A UE in CS/PS mode 1 or CS/PS mode 2 of operation is still IMSI attached for non-EPS services.
                The UE shall set the update status to U2 NOT UPDATED.
            #10 (Implicitly detached);
            #40 (No EPS bearer context activated);
                UE shall delete the list of equivalent PLMNs and deactivate all the EPS bearer contexts locally, if any,
                and shall enter the state EMM-DEREGISTERED.NORMAL-SERVICE. The UE shall then perform the attach procedure.
                If A/Gb mode or Iu mode is supported by the UE, the UE shall in addition handle the GMM state as specified in 3GPP TS 24.008 [13] for the case
                when the combined routing area updating procedure is rejected with the GMM cause value #10 "Implicitly detached".
                A UE in CS/PS mode 1 or CS/PS mode 2 of operation is still IMSI attached for non-EPS services.
                The UE shall set the update status to U2 NOT UPDATED.
            */

            /* Update Status置为NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

            /* 删除TMSI, LAI CKSN */
            NAS_MM_DelLaiTmsiCK();

            /* 刷新sim的cs loci 0x6F7E文件中相应参数 */
            NAS_MM_WriteLocaInCard();

            break;

        case NAS_EMM_CAUSE_PLMN_NOT_ALLOW:
        case NAS_EMM_CAUSE_TA_NOT_ALLOW:

            /* ETSI TS 124 301
            5.5.3.3.5 Combined tracking area updating procedure not accepted by the network
            #11 (PLMN not allowed);
            #12 (Tracking area not allowed);
            If A/Gb mode or Iu mode is supported by the UE, the UE shall handle the MM parameters update status, TMSI,
            LAI, ciphering key sequence number and the location update attempt counter, and the GMM parameters GMM
            state, GPRS update status, P-TMSI, P-TMSI signature, RAI, GPRS ciphering key sequence number and routing
            area updating attempt counter as specified in 3GPP TS 24.008 [13] for the case when the combined routing area
            updating procedure is rejected with the GMM cause with the same value.

            TS 24008
            4.7.5.2.4   Combined routing area updating not accepted by the network
            # 11    (PLMN not allowed);
            The MS shall set the GPRS update status to GU3 ROAMING NOT ALLOWED and the update status to U3 ROAMING NOT ALLOWED
            (and shall store it according to subclause 4.1.3.2) and enter the state GMM-DEREGISTERED. Furthermore,
            it shall delete any P-TMSI, P-TMSI signature, TMSI, RAI, LAI, ciphering key sequence number GPRS ciphering key sequence
            number, and reset the routing area updating attempt counter and the location update attempt counter.
            */

            /* Update Status置为NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);

            /* 删除TMSI, LAI and ciphering key sequence number */
            NAS_MM_DelLaiTmsiCK();

            /* reset location update attempt counter */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;

            /* 更新服务状态 */
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

            /* 迁入MM_IDLE_LIMITED_SERVICE */
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

            break;

        case NAS_EMM_CAUSE_ROAM_NOT_ALLOW:
        case NAS_EMM_CAUSE_NO_SUITABL_CELL:

            /* ETSI TS 124 301
            5.5.3.3.5 Combined tracking area updating procedure not accepted by the network
            #13 (Roaming not allowed in this tracking area);
            #15 (No suitable cells in tracking area);
            If A/Gb mode or Iu mode is supported by the UE, the UE shall handle the MM parameters update status and the
            location update attempt counter, and the GMM parameters GMM state, GPRS update status and routing area
            updating attempt counter as specified in 3GPP TS 24.008 [13] for the case when the combined routing area
            updating procedure is rejected with the GMM cause with the same value.

            TS 24008
            4.7.5.2.4   Combined routing area updating not accepted by the network
            # 13    (Roaming not allowed in this location area)
            The MS shall in addition set the update status to U3 ROAMING NOT ALLOWED and shall reset the location update
            attempt counter. The new MM state is MM IDLE.
            */

            /* Update Status置为NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);

            /* 刷新sim的cs loci 0x6F7E文件中相应参数 */
            NAS_MM_WriteLocaInCard();

            /* reset location update attempt counter */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;

            /* 更新服务状态 */
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

            /* 迁入MM_IDLE_LIMITED_SERVICE */
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

            break;


        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN:

            /* ETSI TS 124 301
            5.5.3.3.5 Combined tracking area updating procedure not accepted by the network
            #14 (EPS services not allowed in this PLMN);
            The UE operating in CS/PS mode 1 or CS/PS mode 2 of operation is still IMSI attached for non-EPS services
            and shall set the update status to U2 NOT UPDATED.
            */

            /* Update Status置为NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

            /* 删除TMSI, LAI CKSN */
            NAS_MM_DelLaiTmsiCK();

            /* 刷新sim的cs loci 0x6F7E文件中相应参数 */
            NAS_MM_WriteLocaInCard();

            break;

        default :

            /* 调用NAS_MM_ProcLmmRejOtherCause进行处理 */
            NAS_MM_ProcLmmRejOtherCause(ulAttemptCounter,ulLmmBitOpAtmpCnt);

            break;
    }

    return;
}

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-1-15, begin */
/*****************************************************************************
 函 数 名  : NAS_MM_ProcLmmEpsOnlySuccCsRejOtherCause
 功能描述  : 对LMM联合注册EPS单域成功CS被拒other cause处理
 输入参数  : ulAttemptCounter:已经尝试次数
             ulLmmBitOpAtmpCnt:PS尝试次数OP项
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年1月15日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年8月11日
   作    者   : w00167002
   修改内容   : DTS2014080407625:在ATTEMPT TO UPDATE状态也尝试发起普通呼叫。
*****************************************************************************/
VOS_VOID NAS_MM_ProcLmmEpsOnlySuccCsRejOtherCause(
    VOS_UINT32                          ulAttemptCounter,
    VOS_UINT32                          ulLmmBitOpAtmpCnt
)
{
    /* 24301
    Other  EMM cause values and the case that no EMM cause IE was received are considered as abnormal cases.
    The combined tracking area updating procedure shall be considered as failed for non-EPS services.
    The behaviour of the UE in those cases is specified in subclause 5.5.3.3.6.
    */

    /* 尝试次数无效，更新为限制驻留*/
    if (VOS_FALSE == ulLmmBitOpAtmpCnt)
    {
        /* 更新服务状态 */
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

        /* 迁入MM_IDLE_LIMITED_SERVICE */
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

        return;
    }

    if (ulAttemptCounter < MM_EMM_MAX_ATTEMPT_COUNTER )
    {
        if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
        {
            /* 更新服务状态 */
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

            /* 迁入MM_IDLE_NORMAL_SERVICE */
            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
        }
        else
        {
            /* Update Status置为NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

            /* 删除TMSI, LAI CKSN */
            NAS_MM_DelLaiTmsiCK();


            /* 更新服务状态 */
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;


            /* 迁入MM_IDLE_ATTEMPTING_TO_UPDATE */
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

            NAS_MM_ProcBufferedCsfbService();
        }
    }
    else
    {
        /* GCF test LTE case 9.2.1.2.3,T3402超时后发起TAU REQ(combine ta la updating with IMSI attach,
          携带TMSI status(无有效TMSI)),仪器上报不匹配，期望UE不携带TMSI status */

        /* 更新服务状态 */
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;

        /* 迁入MM_IDLE_ATTEMPTING_TO_UPDATE */
        Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

        NAS_MM_ProcBufferedCsfbService();
    }

    return;
}

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-1-15, end */


/*****************************************************************************
 函 数 名  : NAS_MM_ProcLmmCombinedAttachOnlyEpsSucc
 功能描述  : 对LMM联合注册仅EPS成功的处理
 输入参数  : pstMsg:LMM的Combinedined Attach结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月27日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2012年4月6日
   作    者   : z40661
   修改内容   : DTS2012032803448，删除LAI信息
 3.日    期   : 2013年3月1日
   作    者   : t00212959
   修改内容   : DTS2013030106126
 4.日    期   : 2013年3月1日
   作    者   : w00167002
   修改内容   : DTS2013092306637: GCF test LTE case 9.2.1.2.3,T3402超时后发起TAU REQ(combine ta la updating with IMSI attach,
                  携带TMSI status(无有效TMSI)),仪器上报不匹配，期望UE不携带TMSI status
                发现人:youqingyang 00187523，产品线单号:DTS2013080508333.
 5.日    期   : 2014年01月10日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseIII项目
 6.日    期   : 2014年8月12日
   作    者   : z00161729
   修改内容   : L下卡无效需要设置imsi为无效，后续发起紧急呼叫cm service req中应该携带IMEI
 7.日    期   : 2014年8月11日
   作    者   : w00167002
   修改内容   : DTS2014080407625:在ATTEMPT TO UPDATE状态也尝试发起普通呼叫。
*****************************************************************************/
VOS_VOID NAS_MM_ProcLmmCombinedAttachOnlyEpsSucc(
    MMCMM_LMM_ATTACH_IND_STRU          *pstLmmCombinedAttachInd
)
{
    VOS_UINT32                          ulAttemptCount;

    ulAttemptCount = 0x0;

    /* 如果消息中bitOpCnCause指示不携带ucCnCause,打印异常后返回 */
    if (VOS_FALSE == pstLmmCombinedAttachInd->bitOpCnCause)
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_ProcLmmCombinedAttachOnlyEpsSucc: there is no cn cause.");

        return;
    }

    if ( VOS_TRUE == pstLmmCombinedAttachInd->bitOpAtmpCnt)
    {
        ulAttemptCount = pstLmmCombinedAttachInd->ulAttemptCount;
    }

    /* 根据网络下发的Detach类型分别处理 */
    switch (pstLmmCombinedAttachInd->ucCnCause)
    {
        case NAS_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS:

            /* ETSI TS 124 301:
               5.5.1.3.4.3 Combined attach successful for EPS services only
               #2 (IMSI unknown in HSS)
               The UE shall set the update status to U3 ROAMING NOT ALLOWED and shall delete any TMSI, LAI and ciphering key sequence number.
               The UE shall enter state EMM-REGISTERED.NORMAL-SERVICE. The new MM state is MM IDLE.
               The USIM shall be considered as invalid for non-EPS services until switching off or the UICC containing the USIM is removed.
            */

            /* Update Status置为NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);

            /* 删除TMSI, LAI and ciphering key sequence number */
            NAS_MM_DelLaiTmsiCK();

            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_IMSI_PRESENT;

            /* 更新服务状态 */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;

            /* 状态置为MM_IDLE_NO_IMSI */
            Mm_ComSetMmState(MM_IDLE_NO_IMSI);

            /* 设置CS域卡无效 */
            NAS_MML_SetSimCsRegStatus(VOS_FALSE);

            break;

        case NAS_EMM_CAUSE_MSC_TEMPORARILY_NOT_REACHABLE:
        case NAS_EMM_CAUSE_NETWORKFAILURE:
        case NAS_EMM_CAUSE_CONGESTION:
            if (ulAttemptCount < MM_EMM_MAX_ATTEMPT_COUNTER )
            {
                if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
                {
                    /* 更新服务状态 */
                    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

                    /* 迁入MM_IDLE_NORMAL_SERVICE */
                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                }
                else
                {
                    /* Update Status置为NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
                    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

                    /* 删除TMSI, LAI CKSN */
                    NAS_MM_DelLaiTmsiCK();


                    /* 更新服务状态 */
                    g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;


                    /* 迁入MM_IDLE_ATTEMPTING_TO_UPDATE */
                    Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

                    NAS_MM_ProcBufferedCsfbService();
                }
            }
            else
            {

                /* GCF test LTE case 9.2.1.2.3,T3402超时后发起TAU REQ(combine ta la updating with IMSI attach,
                  携带TMSI status(无有效TMSI)),仪器上报不匹配，期望UE不携带TMSI status */


                /* 更新服务状态 */
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;

                /* 迁入MM_IDLE_ATTEMPTING_TO_UPDATE */
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

                NAS_MM_ProcBufferedCsfbService();
            }
            break;

        case NAS_EMM_CAUSE_CS_DOMAIN_NOT_AVAILABLE:

            /* ETSI TS 124 301:
               5.5.1.3.4.3 Combined attach successful for EPS services only
               #18 (CS domain not available)
               The UE shall set the update status to U2 NOT UPDATED.
            */

            /* Update Status置为NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

            /* 删除TMSI, LAI CKSN */
            NAS_MM_DelLaiTmsiCK();

            /* 刷新sim的cs loci 0x6F7E文件中相应参数 */
            NAS_MM_WriteLocaInCard();

            /* 更新服务状态 */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

            /* 状态置为MM_IDLE_NO_CELL_AVAILABLE */
            Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

            break;

        default:

            /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2014-1-15, begin */
            NAS_MM_ProcLmmEpsOnlySuccCsRejOtherCause(ulAttemptCount, pstLmmCombinedAttachInd->bitOpAtmpCnt);
            /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2014-1-15, end */

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcLmmCombinedAttachSucc
 功能描述  : 对LMM联合注册成功的处理
 输入参数  : pstMsg:LMM的Combinedined Attach结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月27日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年02月07日
   作    者   : W00176964
   修改内容   : DTS2012020703446:UE从L模重选到W，W下发起LAU未携带新的TMSI
 3.日    期   : 2012年04月27日
   作    者   : w00176964
   修改内容   : GUL BG项目调整
 4.日    期   : 2012年9月4日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改,如果csfb标志已置上无需再处理缓存，等L注册结果状态发起紧急呼叫，L
                会先上报注册结果再上报lmm service result ind，此时无需再调用NAS_MM_RcvCcEstReq_CSFB
 5.日    期   : 2013年12月11日
   作    者   : w00242748
   修改内容   : DTS2013120905612:L到G异系统失败回退到L时，收到resume ind时，
                下发SS业务，此时缓存该SS业务，当收到L的TAU结果后，不应执行
                该缓存的SS业务
 6.日    期   : 2014年4月2日
   作    者   : w00176964
   修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
 7.日    期   : 2014年8月11日
   作    者   : w00167002
   修改内容   : DTS2014080407625:函数封装。
*****************************************************************************/
VOS_VOID NAS_MM_ProcLmmCombinedAttachSucc(
    MMCMM_LMM_ATTACH_IND_STRU          *pstLmmCombinedAttachInd
)
{
    NAS_MML_LAI_STRU                   *pstCsSuccLai = VOS_NULL_PTR;
    VOS_UINT8                          *pucTmsi      = VOS_NULL_PTR;

    pstCsSuccLai    = NAS_MML_GetCsLastSuccLai();
    pucTmsi         = NAS_MML_GetUeIdTmsi();

    /* ETSI TS 124 301:
    5.5.1.3.4.2 Combined attach successful
    The UE, receiving an ATTACH ACCEPT message, stores the received location area identification, stops timer T3410,
    resets the location update attempt counter and sets the update status to U1 UPDATED. If the message contains an IMSI,
    the UE is not allocated any TMSI, and shall delete any TMSI accordingly. If the message contains a TMSI, the UE shall
    use this TMSI as the new temporary identity. The UE shall delete its old TMSI and shall store the new TMSI. If neither
    a TMSI nor an IMSI has been included by the network in the ATTACH ACCEPT message, the old TMSI, if any
    available, shall be kept.
    */

    /* 更新CS域最后一次注册成功的LAI信息 */
    if (VOS_TRUE == pstLmmCombinedAttachInd->bitOpLai)
    {
        /* 保存到MML上次成功LAI全局变量中 */
        NAS_MM_ConvertLmmPlmnToNasPLMN(pstLmmCombinedAttachInd->stLai.stPlmnId.aucPlmnId, &(pstCsSuccLai->stPlmnId));

        pstCsSuccLai->aucLac[0] = pstLmmCombinedAttachInd->stLai.stLac.ucLac;
        pstCsSuccLai->aucLac[1] = pstLmmCombinedAttachInd->stLai.stLac.ucLacCnt;

        pstCsSuccLai->ucRac = NAS_MML_RAC_INVALID;

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */
    }

    /* resets the location update attempt counter and sets the update status to U1 UPDATED */
    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_UPDATED);

    /* 若ATTACH ACCEPT消息中分配了新的TMSI，则刷新TMSI,若存在IMSI，则删除TMSI */
    if (VOS_TRUE == pstLmmCombinedAttachInd->bitOpMsIdentity)
    {
        /*
        8   7   6   5             4           3   2   1
        Length of mobile identity contents                           octet 1

        Identity digit 1   | odd/even indic | Type of identity       octet 2
        Identity digit p+1 | Identity digit p                        octet 3*

        Type of identity (octet 2)
        Bits
        3 2 1
        0 0 1   IMSI
        0 1 0   IMEI
        0 1 1   IMEISV
        1 0 0   TMSI/P-TMSI/M-TMSI
        1 0 1   TMGI and optional MBMS Session Identity
        0 0 0   No Identity (note 1)

        If the mobile identity is the TMSI/P-TMSI/M-TMSI then bits 5 to 8 of octet 3 are coded as "1111"
        and bit 8 of octet4 is the most significant bit and bit 1 of the last octet the least significant bit.
        The coding of the TMSI/P-TMSI is left open for each administration.
        */

        if (MM_IE_MI_ID_TYPE_IMSI == (pstLmmCombinedAttachInd->stMsIdentity.aucMsIdentity[1] & 0x7))
        {
            /* 设置TMSI无效 */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;
            NAS_MML_InitUeIdTmsiInvalid();
        }
        else if (MM_IE_MI_ID_TYPE_TMSI == (pstLmmCombinedAttachInd->stMsIdentity.aucMsIdentity[1] & 0x7))
        {
            /* 设置TMSI */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |= MM_MS_ID_TMSI_PRESENT;

            pucTmsi[0] = pstLmmCombinedAttachInd->stMsIdentity.aucMsIdentity[2];
            pucTmsi[1] = pstLmmCombinedAttachInd->stMsIdentity.aucMsIdentity[3];
            pucTmsi[2] = pstLmmCombinedAttachInd->stMsIdentity.aucMsIdentity[4];
            pucTmsi[3] = pstLmmCombinedAttachInd->stMsIdentity.aucMsIdentity[5];

            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMcc = pstCsSuccLai->stPlmnId.ulMcc;
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMnc = pstCsSuccLai->stPlmnId.ulMnc;
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */
        }
        else
        {
        }
    }

    /* 刷新sim的cs loci 0x6F7E文件中相应参数 */
    NAS_MM_WriteLocaInCard();

    /* 更新CS域已注册全局变量 */
    g_MmSubLyrShare.MmShare.ucCsAttachState = MM_STATUS_ATTACHED;

    /* 设置Power on变量为False */
    g_MmGlobalInfo.ucPowerOnFlg = MM_FALSE;

    /* 更新服务状态 */
    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

    /* 迁移状态到MM_IDLE_NORMAL_SERVICE */
    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

    /* 处理MM的CC缓存 */
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-9-5, begin */

    NAS_MM_ProcBufferedCsfbService();


    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcLmmCombinedAttachFail
 功能描述  : 对LMM联合注册失败的处理
 输入参数  : pstLmmCombinedAttachInd:LMM的Combinedined Attach结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月27日
   作    者   : s46746
   修改内容   : 新生成函数

  2.日    期   : 2012年1月5日
    作    者   : w00167002
    修改内容   : DTS2011102200381:增加L模给MM模块发送的未跟网侧进行注册的消息
                  的处理。
 3.日    期   : 2012年04月27日
   作    者   : w00176964
   修改内容   : GUL BG项目调整
 4.日    期   : 2012年9月4日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改
 5.日    期   : 2012年9月24日
   作    者   : z00161729
   修改内容   : DTS2012081802253:收到L attach失败不应清除mm缓存，后续条件满足mm需尝试发起呼叫
 6.日    期   : 2014年8月11日
   作    者   : w00167002
   修改内容   : DTS2014080407625:在ATTEMPT TO UPDATE状态也尝试发起普通呼叫。
*****************************************************************************/
VOS_VOID NAS_MM_ProcLmmCombinedAttachFail(
    MMCMM_LMM_ATTACH_IND_STRU          *pstLmmCombinedAttachInd
)
{
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause;
    VOS_UINT32                          ulAttemptCount;

    enCnCause      = NAS_EMM_CAUSE_BUTT;
    ulAttemptCount = 0x0;

    if (VOS_TRUE == pstLmmCombinedAttachInd->bitOpCnCause)
    {
        if ((VOS_FALSE == pstLmmCombinedAttachInd->bitOpCnRslt)
         || (MMC_LMM_ATT_CN_RSLT_EPS_ONLY != pstLmmCombinedAttachInd->ulCnRslt))
        {
            enCnCause = pstLmmCombinedAttachInd->ucCnCause;
        }
    }

    if ( VOS_TRUE == pstLmmCombinedAttachInd->bitOpAtmpCnt)
    {
        ulAttemptCount = pstLmmCombinedAttachInd->ulAttemptCount;
    }

    switch (pstLmmCombinedAttachInd->ulAttachRslt)
    {
        /* 网侧明确拒绝 */
        case MMC_LMM_ATT_RSLT_CN_REJ:
            NAS_MM_ProcLmmCombinedAttachCause(enCnCause, ulAttemptCount, pstLmmCombinedAttachInd->bitOpAtmpCnt);
            break;

        /* 鉴权被拒 */
        case MMC_LMM_ATT_RSLT_AUTH_REJ:
            NAS_MM_ProcLmmAuthRstInd();
            break;

        /* 接入被 Barred */
        case MMC_LMM_ATT_RSLT_ACCESS_BAR:

            /* 更新服务状态 */
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

            /* 状态迁移到MM_IDLE_LOCATION_UPDATE_NEEDED */
            Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);

            NAS_MM_ProcBufferedCsfbService();

            break;

        /* 网侧无响应 */
        case MMC_LMM_ATT_RSLT_TIMER_EXP:

            NAS_MM_ProcLmmRejOtherCause(ulAttemptCount,pstLmmCombinedAttachInd->bitOpAtmpCnt);
            break;


        /* 禁止信息不触发ATTACH */
        case MMC_LMM_ATT_RSLT_FORBID_PLMN:
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS:
        case MMC_LMM_ATT_RSLT_FORBID_PLMN_FOR_GPRS:
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_ROAMING:
        case MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW:
        case MMC_LMM_ATT_RSLT_ESM_FAILURE:
        case MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE:
        case MMC_LMM_ATT_RSLT_MT_DETACH_FAILURE:
        case MMC_LMM_ATT_RSLT_T3402_RUNNING:

            /* 更新服务状态 */
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

            /* 状态迁移到MM_IDLE_LIMITED_SERVICE */
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

            break;

        /* 其他ATTACH未指定原因的失败 */
        case MMC_LMM_ATT_RSLT_FAILURE:

            NAS_MM_ProcLmmRejOtherCause(ulAttemptCount,pstLmmCombinedAttachInd->bitOpAtmpCnt);

            break;

        default:

            /* 异常打印 */
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_ProcLmmCombinedAttachFail: unexpected attach rslt.");
            break;
    }



    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcLmmCombinedTauOnlyEpsSucc
 功能描述  : 对LMM联合TAU仅EPS成功的处理
 输入参数  : pstCombinedTauInd:LMM的Combinedined TAU结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月27日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2012年4月6日
   作    者   : z40661
   修改内容   : DTS2012032803448，删除LAI信息
 3.日    期   : 2013年3月1日
   作    者   : t00212959
   修改内容   : DTS2013030106126
4.日    期   : 2013年9月23日
   作    者   : w00167002
   修改内容   : DTS2013092306637: GCF test LTE case 9.2.1.2.3,T3402超时后发起TAU REQ(combine ta la updating with IMSI attach,
                  携带TMSI status(无有效TMSI)),仪器上报不匹配，期望UE不携带TMSI status
                发现人:youqingyang 00187523，产品线单号:DTS2013080508333.
 5.日    期   : 2014年01月10日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseIII项目

 6.日    期   : 2014年8月11日
   作    者   : w00167002
   修改内容   : DTS2014080407625:在ATTEMPT TO UPDATE状态也尝试发起普通呼叫。
*****************************************************************************/
VOS_VOID NAS_MM_ProcLmmCombinedTauOnlyEpsSucc(
    MMCMM_LMM_TAU_RESULT_IND_STRU      *pstCombinedTauInd
)
{
    VOS_UINT32                          ulAttemptCount;

    ulAttemptCount = 0x0;

    /* 该函数只在ulTauRst为成功才调用,如果消息中bitOpCnCause指示不携带ucCnCause,ulTauRst为cnrej,因此打印异常后返回 */
    if (VOS_FALSE == pstCombinedTauInd->bitOpCnCause)
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_ProcLmmCombinedTauOnlyEpsSucc: there is no cn cause.");

        return;
    }

    if ( VOS_TRUE == pstCombinedTauInd->bitOpAtmpCnt)
    {
        ulAttemptCount = pstCombinedTauInd->ulAttemptCount;
    }

    /* 根据网络下发的Detach类型分别处理 */
    switch (pstCombinedTauInd->ucCnCause)
    {
        case NAS_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS:

            /*ETSI TS 124 301:
            5.5.3.3.4.3 Combined tracking area updating successful for EPS services only
            #2 (IMSI unknown in HSS)
            The UE shall stop T3430 if still running and shall reset the tracking area updating attempt counter. The UE
            shall set the update status to U3 ROAMING NOT ALLOWED and shall delete any TMSI, LAI and ciphering
            key sequence number. The UE shall enter state EMM-REGISTERED.NORMAL-SERVICE. The new MM
            state is MM IDLE. The USIM shall be considered as invalid for non-EPS services until switching off or the
            UICC containing the USIM is removed.
            */

            /* Update Status置为NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);

            /* 删除TMSI, LAI and ciphering key sequence number */
            NAS_MM_DelLaiTmsiCK();

            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_IMSI_PRESENT;

            /* 更新服务状态 */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;

            /* 状态置为MM_IDLE_NO_IMSI */
            Mm_ComSetMmState(MM_IDLE_NO_IMSI);

            /* 设置CS域卡无效 */
            NAS_MML_SetSimCsRegStatus(VOS_FALSE);

            break;

        case NAS_EMM_CAUSE_MSC_TEMPORARILY_NOT_REACHABLE:
        case NAS_EMM_CAUSE_NETWORKFAILURE:
        case NAS_EMM_CAUSE_CONGESTION:
            if (ulAttemptCount < MM_EMM_MAX_ATTEMPT_COUNTER )
            {
                if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
                {
                    /* 更新服务状态 */
                    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

                    /* 迁入MM_IDLE_NORMAL_SERVICE */
                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                }
                else
                {
                    /* Update Status置为NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
                    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

                    /* 删除TMSI, LAI CKSN */
                    NAS_MM_DelLaiTmsiCK();


                    /* 更新服务状态 */
                    g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;


                    /* 迁入MM_IDLE_ATTEMPTING_TO_UPDATE */
                    Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

                    NAS_MM_ProcBufferedCsfbService();
                }
            }
            else
            {

                /* GCF test LTE case 9.2.1.2.3,T3402超时后发起TAU REQ(combine ta la updating with IMSI attach,
                  携带TMSI status(无有效TMSI)),仪器上报不匹配，期望UE不携带TMSI status */



                /* 更新服务状态 */
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;

                /* 迁入MM_IDLE_ATTEMPTING_TO_UPDATE */
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

                NAS_MM_ProcBufferedCsfbService();
            }
            break;

        case NAS_EMM_CAUSE_CS_DOMAIN_NOT_AVAILABLE:

            /*ETSI TS 124 301:
            5.5.3.3.4.3 Combined tracking area updating successful for EPS services only
            #18 (CS domain not available)
            The UE shall set the update status to U2 NOT UPDATED.
            */

            /* Update Status置为NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

            /* 删除TMSI, LAI CKSN */
            NAS_MM_DelLaiTmsiCK();

            /* 刷新sim的cs loci 0x6F7E文件中相应参数 */
            NAS_MM_WriteLocaInCard();

            /* 更新服务状态 */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

            /* 状态置为MM_IDLE_NO_CELL_AVAILABLE */
            Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

            break;

        default:

            /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2014-1-15, begin */
            NAS_MM_ProcLmmEpsOnlySuccCsRejOtherCause(ulAttemptCount, pstCombinedTauInd->bitOpAtmpCnt);
            /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2014-1-15, end */

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcLmmCombinedTauSucc
 功能描述  : 对LMM联合TAU成功的处理
 输入参数  : pstCombinedTauInd:LMM的Combinedined TAU结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月27日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年02月07日
   作    者   : W00176964
   修改内容   : DTS2012020703446:UE从L模重选到W，W下发起LAU未携带新的TMSI
 3.日    期   : 2012年04月27日
   作    者   : w00176964
   修改内容   : GUL BG项目调整
 4.日    期   : 2012年9月4日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改,如果csfb标志已置上无需再处理缓存，等L注册结果状态发起紧急呼叫，L
                会先上报注册结果再上报lmm service result ind，此时无需再调用NAS_MM_RcvCcEstReq_CSFB
 5.日    期   : 2013年12月11日
   作    者   : w00242748
   修改内容   : DTS2013120905612:L到G异系统失败回退到L时，收到resume ind时，
                下发SS业务，此时缓存该SS业务，当收到L的TAU结果后，不应执行
                该缓存的SS业务
 6.日    期   : 2014年4月2日
   作    者   : w00176964
   修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
 7.日    期   : 2014年8月11日
   作    者   : w00167002
   修改内容   : DTS2014080407625:函数封装。
*****************************************************************************/
VOS_VOID NAS_MM_ProcLmmCombinedTauSucc(
    MMCMM_LMM_TAU_RESULT_IND_STRU      *pstCombinedTauInd
)
{
    NAS_MML_LAI_STRU                   *pstCsSuccLai = VOS_NULL_PTR;
    VOS_UINT8                          *pucTmsi      = VOS_NULL_PTR;

    pstCsSuccLai    = NAS_MML_GetCsLastSuccLai();
    pucTmsi         = NAS_MML_GetUeIdTmsi();

    /* ETSI TS 124 301:
    5.5.3.3.4.2 Combined tracking area updating successful
    The UE, receiving a TRACKING AREA UPDATE ACCEPT message, stores the received location area identification,
    resets the location update attempt counter, sets the update status to U1 UPDATED and enters MM state MM IDLE.
    How to handle the old TMSI stored in the UE depends on the mobile identity included in the TRACKING AREA
    UPDATE ACCEPT message.
    - If the TRACKING AREA UPDATE ACCEPT message contains an IMSI, the UE is not allocated any TMSI,
    and shall delete any old TMSI accordingly.
    - If the TRACKING AREA UPDATE ACCEPT message contains a TMSI, the UE shall use this TMSI as new
    temporary identity. The UE shall delete its old TMSI and shall store the new TMSI. In this case, a TRACKING
    AREA UPDATE COMPLETE message is returned to the network to confirm the received TMSI.
    - If neither a TMSI nor an IMSI has been included by the network in the TRACKING AREA UPDATE ACCEPT
    message, the old TMSI, if any is available, shall be kept.
    */

    /* 更新CS域最后一次注册成功的LAI信息 */
    if (VOS_TRUE == pstCombinedTauInd->bitOpLai)
    {
        /* 保存到MML上次成功LAI全局变量中 */
        NAS_MM_ConvertLmmPlmnToNasPLMN(pstCombinedTauInd->stLai.stPlmnId.aucPlmnId, &(pstCsSuccLai->stPlmnId));

        pstCsSuccLai->aucLac[0] = pstCombinedTauInd->stLai.stLac.ucLac;
        pstCsSuccLai->aucLac[1] = pstCombinedTauInd->stLai.stLac.ucLacCnt;

        pstCsSuccLai->ucRac = NAS_MML_RAC_INVALID;

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */
    }

    /* resets the location update attempt counter and sets the update status to U1 UPDATED */
    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_UPDATED);

    /* 若ATTACH ACCEPT消息中分配了新的TMSI，则刷新TMSI,若存在IMSI，则删除TMSI */
    if (VOS_TRUE == pstCombinedTauInd->bitOpMsIdentity)
    {
        /* 北研修改aucMsIdentity的长度为9，从TLV格式变为LV格式 */
        /*
        8   7   6   5             4           3   2   1
        Length of mobile identity contents                           octet 1

        Identity digit 1   | odd/even indic | Type of identity       octet 2
        Identity digit p+1 | Identity digit p                        octet 3*

        Type of identity (octet 2)
        Bits
        3 2 1
        0 0 1   IMSI
        0 1 0   IMEI
        0 1 1   IMEISV
        1 0 0   TMSI/P-TMSI/M-TMSI
        1 0 1   TMGI and optional MBMS Session Identity
        0 0 0   No Identity (note 1)

        If the mobile identity is the TMSI/P-TMSI/M-TMSI then bits 5 to 8 of octet 3 are coded as "1111"
        and bit 8 of octet4 is the most significant bit and bit 1 of the last octet the least significant bit.
        The coding of the TMSI/P-TMSI is left open for each administration.
        */

        if (MM_IE_MI_ID_TYPE_IMSI == (pstCombinedTauInd->stMsIdentity.aucMsIdentity[1] & 0x7))
        {
            /* 设置TMSI无效 */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;
            NAS_MML_InitUeIdTmsiInvalid();
        }
        else if (MM_IE_MI_ID_TYPE_TMSI == (pstCombinedTauInd->stMsIdentity.aucMsIdentity[1] & 0x7))
        {
            /* 设置TMSI */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |= MM_MS_ID_TMSI_PRESENT;

            pucTmsi[0] = pstCombinedTauInd->stMsIdentity.aucMsIdentity[2];
            pucTmsi[1] = pstCombinedTauInd->stMsIdentity.aucMsIdentity[3];
            pucTmsi[2] = pstCombinedTauInd->stMsIdentity.aucMsIdentity[4];
            pucTmsi[3] = pstCombinedTauInd->stMsIdentity.aucMsIdentity[5];

            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMcc = pstCsSuccLai->stPlmnId.ulMcc;
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMnc = pstCsSuccLai->stPlmnId.ulMnc;
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */
        }
        else
        {
        }
    }

    /* 刷新sim的cs loci 0x6F7E文件中相应参数 */
    NAS_MM_WriteLocaInCard();

    /* 更新CS域已注册全局变量 */
    g_MmSubLyrShare.MmShare.ucCsAttachState = MM_STATUS_ATTACHED;

    /* 设置Power on变量为False */
    g_MmGlobalInfo.ucPowerOnFlg = MM_FALSE;

    /* 更新服务状态 */
    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

    /* 迁移状态到MM_IDLE_NORMAL_SERVICE */
    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);


    NAS_MM_ProcBufferedCsfbService();


    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcLmmCombinedTauFail
 功能描述  : 对LMM联合TAU失败的处理
 输入参数  : pstCombinedTauInd:LMM的Combinedined TAU结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月27日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年1月8日
   作    者   : z00161729
   修改内容   : V7R1 phaseIV修改
 3.日    期   : 2011年12月29日
   作    者   : w00167002
   修改内容   : DTS2011102200381:L下注册被拒#12,LMM给MMC带的TAU
                 中的结果为MMC_LMM_TAU_RSLT_FORBID_PLMNS，MMC收到此结果后按照禁止网络
                 来处理而发起了搜网。
                  修改内容:将L模带过来的假流程值转换为NAS内部的假流程值
 4.日    期   : 2012年3月14日
   作    者   : z00161729
   修改内容   : 支持ISR修改
 5.日    期   : 2012年11月10日
   作    者   : t00212959
   修改内容   : DTS2012110705279
 6.日    期   : 2014年8月11日
   作    者   : w00167002
   修改内容   : DTS2014080407625:在ATTEMPT TO UPDATE状态也尝试发起普通呼叫。
*****************************************************************************/
VOS_VOID NAS_MM_ProcLmmCombinedTauFail(
    MMCMM_LMM_TAU_RESULT_IND_STRU      *pstCombinedTauInd
)
{
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause;
    VOS_UINT32                          ulAttemptCounter;

    enCnCause        = NAS_EMM_CAUSE_BUTT;
    ulAttemptCounter = 0x0;

    if (VOS_TRUE == pstCombinedTauInd->bitOpCnCause)
    {
        if ((VOS_FALSE == pstCombinedTauInd->bitOpCnRst)
         || ((MMC_LMM_TA_UPDATED != pstCombinedTauInd->ulCnRst)
          && (MMC_LMM_TA_UPDATED_ISR_ACTIVATED != pstCombinedTauInd->ulCnRst)))
        {
            enCnCause = pstCombinedTauInd->ucCnCause;
        }
    }

    if (VOS_TRUE == pstCombinedTauInd->bitOpAtmpCnt)
    {
        ulAttemptCounter = pstCombinedTauInd->ulAttemptCount;
    }

    switch (pstCombinedTauInd->ulTauRst)
    {
        /* 网侧明确拒绝 */
        case MMC_LMM_TAU_RSLT_CN_REJ:

            NAS_MM_ProcLmmCombinedTauCause(enCnCause, ulAttemptCounter, pstCombinedTauInd->bitOpAtmpCnt);
            break;

        /* 鉴权被拒 */
        case MMC_LMM_TAU_RSLT_AUTH_REJ:

            NAS_MM_ProcLmmAuthRstInd();
            break;

        /* 接入被 Barred */
        case MMC_LMM_TAU_RSLT_ACCESS_BARED:

            /* 更新服务状态 */
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

            /* 状态迁移到MM_IDLE_LOCATION_UPDATE_NEEDED */
            Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);

            NAS_MM_ProcBufferedCsfbService();

            break;

        /* 网侧无响应 */
        case MMC_LMM_TAU_RSLT_TIMER_EXP:

            NAS_MM_ProcLmmRejOtherCause(ulAttemptCounter,pstCombinedTauInd->bitOpAtmpCnt);

            break;

        /* 禁止信息不触发ATTACH */
        case MMC_LMM_TAU_RSLT_FORBID_PLMN:
        case MMC_LMM_TAU_RSLT_FORBID_TA_FOR_RPOS:
        case MMC_LMM_TAU_RSLT_FORBID_PLMN_FOR_GPRS:
        case MMC_LMM_TAU_RSLT_FORBID_TA_FOR_ROAMING:
        case MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE:
        case MMC_LMM_TAU_RSLT_MT_DETACH_FAILURE:
        case MMC_LMM_TAU_RSLT_T3402_RUNNING:

            /* 更新服务状态 */
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

            /* 状态迁移到MM_IDLE_LIMITED_SERVICE */
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

            break;

        /* 其他ATTACH未指定原因的失败 */
        case MMC_LMM_TAU_RSLT_FAILURE:

            NAS_MM_ProcLmmRejOtherCause(ulAttemptCounter,pstCombinedTauInd->bitOpAtmpCnt);

            break;

        default:

            /* 异常打印 */
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_ProcLmmCombinedTauFail: unexpected attach rslt.");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcLmmCombinedTauInd
 功能描述  : 接收到Lmm Combinedined Tau结果处理
 输入参数  : pstCombinedTauInd:LMM的Combinedined Tau结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月27日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年5月26日
   作    者   : w00176964
   修改内容   : GUL BG项目调整
 3.日    期   : 2012年9月4日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改,如果csfb标志已置上无需再处理缓存，等L注册结果状态发起紧急呼叫，L
                会先上报注册结果再上报lmm service result ind，此时无需再调用NAS_MM_RcvCcEstReq_CSFB
 4.日    期   : 2013年12月11日
   作    者   : w00242748
   修改内容   : DTS2013120905612:L到G异系统失败回退到L时，收到resume ind时，
                下发SS业务，此时缓存该SS业务，当收到L的TAU结果后，不应执行
                该缓存的SS业务
 15.日    期   :2014年4月2日
    作    者   :w00242748
    修改内容   :DTS2014040310584:LTE下未与网络交互的ATTACH/TAU，不停止T3211/T3212/T3213;
                只有与网络交互后，才将T3211/T3212/T3213停止。
 16.日    期   : 2014年5月14日
    作    者   : w00242748
    修改内容   : DTS2014051206381:枚举值使用不对
 17.日    期   :2014年7月7日
    作    者   :s00217060
    修改内容   :收到LTE的系统消息，如果cellstatus是normal，停T3211/T3212/T3213,不以bitOpCnRslt作为是否和网络交互的依据
 18.日    期   : 2014年8月11日
    作    者   : w00167002
    修改内容   : DTS2014080407625:函数封装。
 19.日    期   : 2015年7月24日
    作    者   : z00161729
    修改内容   : DTS2015060903490：周期性tau eps成功携带cs被拒原因值mm不处理
*****************************************************************************/
VOS_VOID NAS_MM_ProcLmmCombinedTauInd(
    MMCMM_LMM_TAU_RESULT_IND_STRU      *pstCombinedTauInd
)
{
    /* 如果bitOpCnRslt指示不携带网络响应的结果ulCnRslt, 表示下面两种情况
       1)联合TAU被网络拒绝或者失败
       2)当前接收到系统消息后不需要发起TAU或者不能发起TAU,LMM直接回复的TAU结果 */
    if (VOS_FALSE == pstCombinedTauInd->bitOpCnRst)
    {
        if (MMC_LMM_TAU_RSLT_SUCCESS == pstCombinedTauInd->ulTauRst)
        {
            /* 更新服务状态 */
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

            /* 迁移状态到MM_IDLE_NORMAL_SERVICE */
            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

            /* L下收到系统消息不发起注册的情况,假流程成功时需要处理MM的CC缓存 */
            /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-9-5, begin */

            NAS_MM_ProcBufferedCsfbService();

        }
        else
        {
            /* 联合TAU失败 */
            NAS_MM_ProcLmmCombinedTauFail(pstCombinedTauInd);
        }

        return;
    }



    /* 如果是联合TAU仅EPS成功 */
    if ((MMC_LMM_TA_UPDATED == pstCombinedTauInd->ulCnRst)
     || (MMC_LMM_TA_UPDATED_ISR_ACTIVATED == pstCombinedTauInd->ulCnRst))
    {
        /* 如果TauRslt为成功 */
        if (MMC_LMM_TAU_RSLT_SUCCESS == pstCombinedTauInd->ulTauRst)
        {
            /* 周期性tau eps only成功，cs被拒带原因值场景不处理，不更新mm状态 */
            if (MMC_LMM_CS_PS_PERIODIC_UPDATING != pstCombinedTauInd->ulReqType)
            {
                /* 表明EPS成功而且网络携带的cause为#2、#18、#16、#17或#22 */
                NAS_MM_ProcLmmCombinedTauOnlyEpsSucc(pstCombinedTauInd);
            }
        }
        else
        {
            /* 网络响应的结果是其它原因或者无原因,此时当作联合注册失败处理 */
            NAS_MM_ProcLmmCombinedTauFail(pstCombinedTauInd);
        }
    }
    else if ((MMC_LMM_COMBINED_TA_LA_UPDATED == pstCombinedTauInd->ulCnRst)
          || (MMC_LMM_COMBINED_TA_LA_UPDATED_ISR_ACTIVATED == pstCombinedTauInd->ulCnRst))
    {
        /* 如果是联合TAU成功 */
        if (MMC_LMM_TAU_RSLT_SUCCESS == pstCombinedTauInd->ulTauRst)
        {
            NAS_MM_ProcLmmCombinedTauSucc(pstCombinedTauInd);
        }
        else
        {
            /* 联合TAU失败 */
            NAS_MM_ProcLmmCombinedTauFail(pstCombinedTauInd);
        }
    }
    else
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_ProcLmmCombinedTauInd: request COMBINED_EPS_IMSI tau, unexpected cn rslt.");
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_RcvLmmAttachInd
 功能描述  : 接收到Lmm Attach结果处理
 输入参数  : pstMsg:LMM的注册结果
 输出参数  : 无
 返 回 值  : 该消息对应的MM事件
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月27日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年5月26日
   作    者   : w00176964
   修改内容   : GUL BG项目调整
 3.日    期   : 2013年4月1日
    作    者   : w00167002
    修改内容   : DTS2013032708183:L下注册成功，用户设置CGATT=0，到W下搜网,在
                  搜网过程中，用户设置CGATT=1。结果UE在L下搜网注册成功，MM/GMM
                  没有回复ATTACH CNF,导致AT通道一致被阻塞，GCF9.2.2.1.8用例测试失败。
 4.日    期   :2014年4月2日
   作    者   :w00242748
   修改内容   :DTS2014040310584:LTE下未与网络交互的ATTACH/TAU，不停止T3211/T3212/T3213;
               只有与网络交互后，才将T3211/T3212/T3213停止。
 5.日    期   :2014年7月7日
   作    者   :s00217060
   修改内容   :收到LTE的系统消息，如果cellstatus是normal，停T3211/T3212/T3213,不以bitOpCnRslt作为是否和网络交互的依据
*****************************************************************************/
VOS_UINT8 NAS_MM_RcvLmmAttachInd(
    struct MsgCB                       *pstMsg
)
{
    MMCMM_LMM_ATTACH_IND_STRU          *pstLmmAttachInd = VOS_NULL_PTR;

    pstLmmAttachInd = (MMCMM_LMM_ATTACH_IND_STRU *)pstMsg;

    /* 如果是单独EPS注册 */
    if (MMC_LMM_ATT_TYPE_EPS_ONLY == pstLmmAttachInd->ulReqType)
    {
        NAS_MM_ProcLmmAttachRstInd(pstLmmAttachInd);
    }
    else if (MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI == pstLmmAttachInd->ulReqType)
    {
        /* 如果bitOpCnRslt指示不携带网络响应的结果ulCnRslt,表示
           1)联合Attach被网络拒绝或者失败
           2)当前未注册而且接收到系统消息后不需要发起注册或者不能发起注册,LMM直接回复的Attach结果 */
        if (VOS_FALSE == pstLmmAttachInd->bitOpCnRslt)
        {
            NAS_MM_ProcLmmCombinedAttachFail(pstLmmAttachInd);


            /* 回复MMCMM_ATTACH_CNF的操作,清除等待ATTACH结果标志位 */
            if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                                    & MM_WAIT_CS_ATTACH))
            {
                NAS_MM_SndMmcAttachCnf();
            }

            g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;

            return MM_EVENT_ID_INVALID;
        }


        /* 如果网络响应的结果是联合注册仅EPS成功 */
        if (MMC_LMM_ATT_CN_RSLT_EPS_ONLY == pstLmmAttachInd->ulCnRslt)
        {
            /* 如果AttachRslt为成功 */
            if (MMC_LMM_ATT_RSLT_SUCCESS == pstLmmAttachInd->ulAttachRslt)
            {
                /* 表明EPS成功而且网络携带的cause为#2、#18、#16、#17或#22 */
                NAS_MM_ProcLmmCombinedAttachOnlyEpsSucc(pstLmmAttachInd);
            }
            else
            {
                /* 网络响应的结果是其它原因或者无原因,此时当作联合注册失败处理 */
                NAS_MM_ProcLmmCombinedAttachFail(pstLmmAttachInd);
            }
        }
        else if (MMC_LMM_ATT_CN_RSLT_COMBINED_EPS_IMSI == pstLmmAttachInd->ulCnRslt)
        {
            /* 如果网络响应的结果是联合注册成功 */
            if (MMC_LMM_ATT_RSLT_SUCCESS == pstLmmAttachInd->ulAttachRslt)
            {
                NAS_MM_ProcLmmCombinedAttachSucc(pstLmmAttachInd);
            }
            else
            {
                /* 网络响应的结果是联合注册失败 */
                NAS_MM_ProcLmmCombinedAttachFail(pstLmmAttachInd);
            }
        }
        else
        {
            /* 异常打印 */
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_RcvLmmAttachInd: request COMBINED_EPS_IMSI attach, unexpected cn rslt.");
        }
    }
    else
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_RcvLmmAttachInd: unexpected request attach type.");
    }


    /* 回复MMCMM_ATTACH_CNF的操作,清除等待ATTACH结果标志位 */
    if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                            & MM_WAIT_CS_ATTACH))
    {
        NAS_MM_SndMmcAttachCnf();
    }

    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;

    return MM_EVENT_ID_INVALID;
}

/*****************************************************************************
 函 数 名  : NAS_MM_RcvLmmTauInd
 功能描述  : 接收到Lmm Tau结果处理
 输入参数  : pstMsg:LMM的Tau结果
 输出参数  : 无
 返 回 值  : 该消息对应的MM事件
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月27日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年12月28日
   作    者   : z00161729
   修改内容   : V7R1 phaseIV修改周期性tau处理

*****************************************************************************/
VOS_UINT8 NAS_MM_RcvLmmTauInd(
    struct MsgCB                       *pstMsg
)
{
    MMCMM_LMM_TAU_RESULT_IND_STRU      *pstLmmTauInd = VOS_NULL_PTR;

    pstLmmTauInd = (MMCMM_LMM_TAU_RESULT_IND_STRU *)pstMsg;

    switch (pstLmmTauInd->ulReqType)
    {
        case MMC_LMM_TA_UPDATING:
        case MMC_LMM_PS_PERIODIC_UPDATING:

            /* 单独EPS更新 */
            NAS_MM_ProcLmmTauRstInd(pstLmmTauInd);
            break;

        case MMC_LMM_COMBINED_TA_LA_UPDATING:
        case MMC_LMM_COMBINED_TA_LA_WITH_IMSI:
        case MMC_LMM_CS_PS_PERIODIC_UPDATING:

            /* 调用NAS_MM_ProcLmmCombinedTauInd处理联合TAU */
            NAS_MM_ProcLmmCombinedTauInd(pstLmmTauInd);
            break;

        default:

            /* 异常打印 */
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_RcvLmmTauInd: unexpected request tau type.");
            break;
    }

    return MM_EVENT_ID_INVALID;
}

/*****************************************************************************
 函 数 名  : NAS_MM_RcvLmmMTDetachInd
 功能描述  : 接收到Lmm 网络发起的Detach处理
 输入参数  : pstMsg:LMM的Detach结果
 输出参数  : 无
 返 回 值  : 该消息对应的MM事件
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月27日
   作    者   : s46746
   修改内容   : 新生成函数

  2.日    期   : 2012年4月6日
    作    者   : z40661
    修改内容   : DTS2012032803448，删除LAI信息

  3.日    期   : 2012年8月24日
    作    者   : z40661
    修改内容   : DTS2012081702937,MM模块回复关机时间比较长
*****************************************************************************/
VOS_UINT8 NAS_MM_RcvLmmMTDetachInd(
    struct MsgCB                       *pstMsg
)
{
    MMCMM_LMM_MT_DETACH_IND_STRU       *pstLmmDetachInd = VOS_NULL_PTR;

    pstLmmDetachInd = (MMCMM_LMM_MT_DETACH_IND_STRU *)pstMsg;

    if (MMC_LMM_DETACH_LOCAL == pstLmmDetachInd->ulDetachType)
    {
        /* 不处理返回 */
        if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
        {
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        }
        return MM_EVENT_ID_INVALID;
    }

    /* 如果bitOpCnReqType指示不携带网络下发的Detach类型,打印异常后返回 */
    if (VOS_FALSE == pstLmmDetachInd->bitOpCnReqType)
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_RcvLmmMTDetachInd: detach type is MMC_LMM_DETACH_MT, but have no cn req type.");

        return MM_EVENT_ID_INVALID;
    }

    /* 根据网络下发的Detach类型分别处理 */
    switch (pstLmmDetachInd->ulCnReqType)
    {
        case MMC_LMM_MT_DET_REATTACH_NOT_REQUIRED:

            /* ETSI TS 124 301
            5.5.2.3.2 Network initiated detach procedure completion by the UE
            If the UE is attached for EPS and non-EPS services, then the UE shall set the update status to U2 NOT UPDATED if:
            - the Detach type IE indicates "re-attach required"; or
            - the Detach type IE indicates "re-attach not required" and no EMM cause IE is included.
            */

            if ((MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
             && (VOS_FALSE == pstLmmDetachInd->bitOpCnCause))
            {
                /* Update Status置为NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
                NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

                /* 删除TMSI, LAI CKSN */
                NAS_MM_DelLaiTmsiCK();

                /* 刷新sim的cs loci 0x6F7E文件中相应参数 */
                NAS_MM_WriteLocaInCard();
            }

            if (VOS_TRUE == pstLmmDetachInd->bitOpCnCause)
            {
                /* 调用NAS_MM_ProcLmmNwDetachIndCause_Handling */
                NAS_MM_ProcLmmNwDetachIndCause_Handling(pstLmmDetachInd->ucCnCause);
            }
            break;

        case MMC_LMM_MT_DET_REATTACH_REQUIRED:

            /* ETSI TS 124 301
            5.5.2.3.2 Network initiated detach procedure completion by the UE
            If the UE is attached for EPS and non-EPS services, then the UE shall set the update status to U2 NOT UPDATED if:
            - the Detach type IE indicates "re-attach required"; or
            - the Detach type IE indicates "re-attach not required" and no EMM cause IE is included.

            If the detach type indicates "IMSI detach" or "re-attach required", then the UE shall ignore the EMM cause IE if
            received.
            */

            if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
            {
                /* Update Status置为NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
                NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

                /* 删除TMSI, LAI CKSN */
                NAS_MM_DelLaiTmsiCK();

                /* 刷新sim的cs loci 0x6F7E文件中相应参数 */
                NAS_MM_WriteLocaInCard();
            }
            break;

        case MMC_LMM_MT_DET_IMSI:

            /* ETSI TS 124 301
            5.5.2.3.2 Network initiated detach procedure completion by the UE
            When receiving the DETACH REQUEST message and the detach type indicates "IMSI detach", the UE shall not
            deactivate the EPS bearer context(s) including the default EPS bearer context. The UE shall set the MM update status to
            U2 NOT UPDATED. A UE may send a DETACH ACCEPT message to the network, and shall re-attach to non-EPS
            services by performing the combined tracking area updating procedure according to subclause 5.5.3.3, sending a
            TRACKING AREA UPDATE REQUEST message with EPS update type IE indicating "combined TA/LA updating
            with IMSI attach".

            If the detach type indicates "IMSI detach" or "re-attach required", then the UE shall ignore the EMM cause IE if
            received.
            */

            /* Update Status置为NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

            /* 删除TMSI, LAI CKSN */
            NAS_MM_DelLaiTmsiCK();

            /* 刷新sim的cs loci 0x6F7E文件中相应参数 */
            NAS_MM_WriteLocaInCard();

            /* 更新CS域注册全局变量为未注册 */
            g_MmSubLyrShare.MmShare.ucCsAttachState = MM_STATUS_DETACHED;

            break;

        default:

            /* 异常打印 */
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_RcvLmmMTDetachInd: detach type is MMC_LMM_DETACH_MT, unexpected cn req type.");
            break;
    }

    return MM_EVENT_ID_INVALID;
}

/*****************************************************************************
 函 数 名  : NAS_MM_RcvLmmMoDetachInd
 功能描述  : 接收到Lmm UE发起的Detach处理
 输入参数  : pstMsg:LMM的UE Detach结果
 输出参数  : 无
 返 回 值  : 该消息对应的MM事件
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月01日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MM_RcvLmmMoDetachInd(
    struct MsgCB                       *pstMsg
)
{
    MMCMM_LMM_MO_DETACH_IND_STRU       *pstLmmDetachInd = VOS_NULL_PTR;

    pstLmmDetachInd = (MMCMM_LMM_MO_DETACH_IND_STRU *)pstMsg;

    switch (pstLmmDetachInd->ulDetachRslt)
    {
        case  MMC_LMM_DETACH_RSLT_SUCCESS:

            /* 更新CS域注册全局变量为未注册 */
            g_MmSubLyrShare.MmShare.ucCsAttachState = MM_STATUS_DETACHED;

            /* 更新服务状态 */
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

            /* 迁移状态到MM_IDLE_NO_CELL_AVAILABLE */
            Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

            break;

        case  MMC_LMM_DETACH_RSLT_AUTH_REJ:

            NAS_MM_ProcLmmAuthRstInd();

            break;

        default:

            /* 异常打印 */
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_RcvLmmMoDetachInd: , unexpected detach result!");

            break;
    }

    return MM_EVENT_ID_INVALID;
}

/*****************************************************************************
 函 数 名  : NAS_MM_RcvLmmServiceRsltInd
 功能描述  : 接收到Lmm服务结果处理
 输入参数  : pstMsg:LMM的服务结果
 输出参数  : 无
 返 回 值  : 该消息对应的MM事件
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月27日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MM_RcvLmmServiceRsltInd(
    struct MsgCB                       *pstMsg
)
{
    MMCMM_LMM_SERVICE_RESULT_IND_STRU  *pstLmmServiceInd = VOS_NULL_PTR;

    pstLmmServiceInd = (MMCMM_LMM_SERVICE_RESULT_IND_STRU *)pstMsg;

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_TRAG_NW_SEARCH_FOR_RCV_LMM_SRV_RST,
                              pstLmmServiceInd->ulServiceRst);


    NAS_MM_ProcLmmServiceRstInd(pstLmmServiceInd);

    return MM_EVENT_ID_INVALID;

}

/*****************************************************************************
 函 数 名  : NAS_MM_RcvLmmSysInfoInd
 功能描述  : 接收到Lmm系统消息处理
 输入参数  : pstMsg:LMM的系统消息
 输出参数  : 无
 返 回 值  : 该消息对应的MM事件
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月27日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月28日
   作    者   : W00166186
   修改内容   : DTS2012042602593,MM没有保存当前驻留的PLMN，导致后续判断出错
 3.日    期   : 2012年03月01日
   作    者   : w00167002
   修改内容   : V7R1C50 CSFB&PPAC&ETWS&ISR:在L下发起CSFB时候，若还未到GU下时
                 候，收到L的系统消息，则不能清楚CSFB缓存
  3.日    期   : 2012年4月28日
   作    者   : W00166186
   修改内容   : DTS2012042602593,MM没有保存当前驻留的PLMN，导致后续判断出错
 4.日    期   : 2012年05月21日
   作    者   :  z40661
   修改内容   :  DTS2012052308001:从L重选到G后反复进行LAU
 5.日    期   : 2012年07月23日
   作    者   : s00217060
   修改内容   : for V7R1C50 sync lmm cs state
 6.日    期   : 2012年8月30日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改DTS2012083007778
 7.日    期   : 2012年10月30日
   作    者   : z00161729
   修改内容  : DTS2012083102536支持呼叫重发功能
 8.日    期   : 2012年11月24日
   作    者   : l00167671
   修改内容   : DTS201212400547
 9.日    期   : 2012年12月15日
   作    者   : l65478
   修改内容   : DTS2012120508936:在发起紧急呼叫时需要disable LTE
 10.日    期   : 2012年12月27日
   作    者   : t00212959
   修改内容   : DTS2012122607665:紧急呼需要不用受是否支持CSFB的NV控制
11.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
 12.日    期   : 2013年05月16日
   作    者   :  l65478
   修改内容   : DTS2013051408660: 通知SMS连接建立失败时TI使用错误
 13.日    期   :2013年9月12日
   作    者   :z00161729
   修改内容   :DTS2013082903019:支持ss重发功能

 14.日    期   :2013年10月20日
    作    者   :z00234330
    修改内容   :DTS2013111903821:MM回复的ti不正确,导致上层业务没有触发重发操作。
 15.日    期   :2014年4月2日
    作    者   :w00242748
    修改内容   :DTS2014040310584:LTE下未与网络交互的ATTACH/TAU，不停止T3211/T3212/T3213;
                只有与网络交互后，才将T3211/T3212/T3213停止。
 16.日   期    : 2014-04-15
    作   者    : w00176964
    修改内容   : V3R3C60_eCall项目调整:驻留信息的更新下移到MM模块
 17.日    期   :2014年7月7日
    作    者   :s00217060
    修改内容   :收到LTE的系统消息，如果cellstatus是normal，停T3211/T3212/T3213,不以bitOpCnRslt作为是否和网络交互的依据
 18.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
 19.日    期   : 2014年11月29日
    作    者   : w00167002
    修改内容   : DTS2014092806342
 20.日    期   : 2015年1月5日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
 21.日    期   : 2015年5月27日
    作    者   : b00269685
    修改内容   : LAC变化则清除3213count
*****************************************************************************/
VOS_UINT8 NAS_MM_RcvLmmSysInfoInd(
    struct MsgCB                       *pstMsg
)
{
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-16, begin */
    VOS_UINT8                           aucTimerId[3];

    VOS_UINT32                          ulEmergencyCallFlg;
    MMC_MM_LTE_SYS_INFO_IND_STRU       *pstLmmSysInfo = VOS_NULL_PTR;
    ulEmergencyCallFlg = MM_CS_SERV_NONE_EXIST;

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-16, end */


    g_MmGlobalInfo.ucLikeB = MM_FALSE;

    g_MmGlobalInfo.enPreRatType = NAS_MML_NET_RAT_TYPE_LTE;

    /* 在L下发起CSFB时候，若还未到GU下时候，收到L的系统消息，则不能清楚CSFB缓存 */

    pstLmmSysInfo = (MMC_MM_LTE_SYS_INFO_IND_STRU*)pstMsg;

    aucTimerId[0] = MM_TIMER_T3211;
    aucTimerId[1] = MM_TIMER_T3212;
    aucTimerId[2] = MM_TIMER_T3213;


    /* 如果小区状态为normal,LMM后面会发起注册，停止所有的定时器
       如果小区状态为anycell,LMM后面不会发起注册，不需要停T3211/T3212/T3213，否则后面再回到GU,可能会多做一次LAU */
    if (MMC_LMM_CELL_STATUS_NORMAL == pstLmmSysInfo->stLteSysInfo.enCellStatusInd)
    {
        g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt = 0;
        if (VOS_FALSE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
        {
            /* 停止除了CSFB MT保护定时器以外的其他定时器 */
            aucTimerId[0] = MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE;
            NAS_MM_TimerStopExceptSpecialTimers(1, aucTimerId);
        }
        else
        {
            /* 停止除了T3212以外的其他定时器 */
            aucTimerId[0] = MM_TIMER_T3212;
            NAS_MM_TimerStopExceptSpecialTimers(1, aucTimerId);
        }
    }
    else
    {
        NAS_MM_TimerStopExceptSpecialTimers(3, aucTimerId);
    }

    /* 记录状态为CSFB MT已收到LTE的系统消息 */
    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_LTE_SYS_INFO_RECEIVED,
                              NAS_MML_REG_FAIL_CAUSE_NULL);

    /* PS ONLY表示不支持联合注册 */
    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        /* CS域不支持，清除缓存 */
        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);

        MM_RelMsgBuf();

        if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
        {
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;

            /* 状态迁移到MM_IDLE_NO_IMSI */
            Mm_ComSetMmState(MM_IDLE_NO_IMSI);

            return MM_EVENT_ID_INVALID;
        }

        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

        /* 状态迁移到MM_IDLE_NO_CELL_AVAILABLE */
        Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);


        return MM_EVENT_ID_INVALID;
    }

    if (MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState)
    {
        /* 如果支持CSFB 或者是紧急呼叫*/
        ulEmergencyCallFlg = Mm_ComJudgeCsServExist();

        if ((NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == NAS_MML_GetLteCsServiceCfg())
         || (MM_CS_SERV_EMERGENCY_CALL_EXIST == ulEmergencyCallFlg))
        {
            /* 不清除CC SS的缓存 */
            if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
            {
                Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();

            NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            /* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
            NAS_MML_SetRelCauseCsfbHighPrioFlg(VOS_FALSE);
            /* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

            /* Modified by z00161729 for DCM定制需求和遗留问题DTS2012083007778, 2012-8-30, begin */
            /* 缓存的是紧急呼叫，发起csfb流程，不等注册 */
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg)
             && (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg))
            {
                NAS_MM_RcvCcEstReq_CSFB();
            }
            else
            {
                /* IDLE PLMN SERACH状态收到LMM的系统消息，上次网络指示CSFB支持，本次还未发起注册，回复CS域暂时无服务 */
                Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);
            }
            /* Modified by z00161729 for DCM定制需求和遗留问题DTS2012083007778, 2012-8-30, end */
        }
        else
        {
            /* IDLE PLMN SERACH状态收到LMM的系统消息，网络指示CSFB不支持 */
            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);
        }

        MM_RelMsgBuf();

        if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
        {
            /* 状态迁移到MM_IDLE_NO_IMSI */
            Mm_ComSetMmState(MM_IDLE_NO_IMSI);
            return MM_EVENT_ID_INVALID;
        }

        /* 状态迁移到LOCATION_UPDATING_PENDING,等待LMM的注册结果 */
        Mm_ComSetMmState(LOCATION_UPDATING_PENDING);
    }

    return MM_EVENT_ID_INVALID;

}

/*****************************************************************************
 函 数 名  : NAS_MM_RcvLmmCombinedStartNotifyReq
 功能描述  : 接收到Lmm LMM_MM_ COMBINED_START_NOTIFY_REQ消息的处理
 输入参数  : pstMsg - LMM的LMM_MM_ COMBINED_START_NOTIFY_REQ消息内容
 输出参数  : 无
 返 回 值  : 该消息对应的MM事件
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年11月30日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MM_RcvLmmCombinedStartNotifyReq(
    VOS_VOID                           *pstMsg
)
{
    LMM_MM_COMBINED_START_NOTIFY_REQ_STRU                   *pstCombinedNotifyReqMsg;

    pstCombinedNotifyReqMsg = (LMM_MM_COMBINED_START_NOTIFY_REQ_STRU *)pstMsg;

    if ((MM_LMM_COMBINED_ATTACH == pstCombinedNotifyReqMsg->enCombinedType)
     || (MM_LMM_COMBINED_TAU == pstCombinedNotifyReqMsg->enCombinedType))
    {
        /* MM收到后将状态转为MM LOCATION UPDATING PENDING */
        Mm_ComSetMmState(LOCATION_UPDATING_PENDING);
    }

    if (MM_LMM_COMBINED_DETACH == pstCombinedNotifyReqMsg->enCombinedType)
    {
        /* MM收到后将状态转为MM IMSI DETACH PENDING */
        Mm_ComSetMmState(IMSI_DETACH_PENDING);

    }

    return MM_EVENT_ID_INVALID;
}

/*****************************************************************************
 函 数 名  : NAS_MM_RcvLmmCsfbServiceEndInd
 功能描述  : 接收到Lmm ID_LMM_MM_CSFB_SERVICE_END_IND消息的处理
 输入参数  : pstMsg - LMM的ID_LMM_MM_CSFB_SERVICE_END_IND消息内容
 输出参数  : 无
 返 回 值  : 该消息对应的MM事件:MM_EVENT_ID_INVALID,表示此消息处理结束
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年02月14日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   :2014年10月07日
   作    者   :s00217060
   修改内容   :cs_err_log原因值上报

*****************************************************************************/
VOS_UINT8 NAS_MM_RcvLmmCsfbServiceEndInd(
    VOS_VOID                           *pstMsg
)
{
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCsfbServiceStatus;
    LMM_MM_CSFB_SERVICE_END_IND_STRU                       *pstCsfbEndInd   = VOS_NULL_PTR;
    NAS_MMCM_REL_CAUSE_ENUM_UINT32                          enRelCause;

    enCsfbServiceStatus  = NAS_MML_GetCsfbServiceStatus();
    pstCsfbEndInd        = (LMM_MM_CSFB_SERVICE_END_IND_STRU *)pstMsg;
    enRelCause           = NAS_MM_ConvertCsfbSrvRsltToMmCcRelCause(pstCsfbEndInd);

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_END_IND_RECEIVED,
                              enRelCause);

#if (FEATURE_ON == FEATURE_PTM)
    /* 记录CSFB MT异常 */
    NAS_MM_CsfbMtFailRecord();
#endif

    /* 异系统重回LTE后，则认为CSFB流程结束 */
    NAS_MM_EndCsfbFlow(enCsfbServiceStatus, enRelCause);

    return MM_EVENT_ID_INVALID;
}

/*****************************************************************************
 函 数 名  : NAS_MM_RcvLmmCsPagingInd
 功能描述  : 接收到Lmm ID_LMM_MM_CS_PAGING_IND消息的处理
 输入参数  : pstMsg - LMM的ID_LMM_MM_CS_PAGING_IND消息内容
 输出参数  : 无
 返 回 值  : MM_EVENT_ID_INVALID,表示此消息处理结束
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年02月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2012年10月10日
   作    者   : z00161729
   修改内容  : DTS2012101101736:mt csfb,paging response中mobile identity type与PAGING REQUEST message消息中不一致
 3.日    期   : 2014年6月13日
   作    者   : w00242748
   修改内容   : DSDS 新特性
 4.日    期   : 2014年11月06日
   作    者   : s00217060
   修改内容   : DTS2014110608091,IMS电话时不处理cs域的paging ind
 5.日    期   : 2015年10月16日
   作    者   : j00174725
   修改内容   : DTS2015101603066
*****************************************************************************/
VOS_UINT8 NAS_MM_RcvLmmCsPagingInd(
    VOS_VOID                           *pstMsg
)
{
    LMM_MM_CSFB_SERVICE_PAGING_IND_STRU *pstCsfbPaingIndMsg = VOS_NULL_PTR;

    pstCsfbPaingIndMsg = (LMM_MM_CSFB_SERVICE_PAGING_IND_STRU *)pstMsg;

    /* IMS电话时不处理cs域的paging ind */
    if (VOS_TRUE   == NAS_MML_GetImsCallFlg())
    {
        return MM_EVENT_ID_INVALID;
    }

    if (LMM_MM_PAGING_IND_UE_ID_TMSI == pstCsfbPaingIndMsg->enPagingUeId)
    {
        g_MmGlobalInfo.ucPagingRecordTypeId = MM_TMSI_PAGING;
    }
    else if (LMM_MM_PAGING_IND_UE_ID_S_TMSI == pstCsfbPaingIndMsg->enPagingUeId)
    {
        g_MmGlobalInfo.ucPagingRecordTypeId = MM_STMSI_PAGING;
    }
    else
    {
        g_MmGlobalInfo.ucPagingRecordTypeId = MM_IMSI_PAGING;
    }


    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST);

    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST);

    /* 向L发送CSFB流程开始请求,CSFB是否可以发起的判断由LMM负责，如果不允许发起,
       L会回复LMM_MM_CSFB_SERVICE_END_IND */
    NAS_MM_SndLmmCsfbServiceStartNotify();

    if (NAS_MML_MT_CSFB_PAGING_TIMER_RUNNING == NAS_MML_GetCsfbMtPagingTimerStatus())
    {
        Mm_TimerStop(MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE);
    }

    Mm_TimerStart(MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE);

    NAS_MML_SetCsfbMtPagingTimerStatus(NAS_MML_MT_CSFB_PAGING_TIMER_RUNNING);

    NAS_MM_ClearErrorLogInfo();

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_LMM_CS_PAGING_RECEIVED,
                              NAS_MML_REG_FAIL_CAUSE_NULL);


   return MM_EVENT_ID_INVALID;
}



/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-15, begin */

/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-15, end */

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-22, begin */
/*****************************************************************************
 函 数 名  : NAS_MM_RcvLmmHoSecuInfoCnf
 功能描述  : 接收到Lmm ID_LMM_MM_HO_SECU_INFO_CNF消息的处理
 输入参数  : pstMsg - LMM的ID_LMM_MM_HO_SECU_INFO_CNF消息内容
 输出参数  : 无
 返 回 值  : MM_EVENT_ID_INVALID,表示此消息处理结束
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年09月22日
   作    者   : w00176964
   修改内容   : 新生成函数
  2.日    期   : 2016年1月20日
    作    者   : c00318887
    修改内容   : DTS2015123110917: usim卡在GSM下做2G鉴权后，csfb到3G下鉴权错误
*****************************************************************************/
VOS_UINT8 NAS_MM_RcvLmmHoSecuInfoCnf(
    VOS_VOID                           *pstMsg
)
{
    LMM_MM_HO_SECU_INFO_CNF_STRU       *pstHoSecuInfo   = VOS_NULL_PTR;
    VOS_UINT8                          *pucDestBuffer   = VOS_NULL_PTR;
    VOS_VOID                           *pucSrcBuffer    = VOS_NULL_PTR;
    VOS_UINT32                          ulCount;
    VOS_UINT8                           ucCksn;

    pstHoSecuInfo = (LMM_MM_HO_SECU_INFO_CNF_STRU *)pstMsg;

    /* 停止定时器 */
    Mm_TimerStop(MM_TIMER_WAIT_GET_HO_SECU_INFO_CNF);

    /* 获取LMM的安全上下文失败时，仍然使用原来的安全上下文 */
    if (MM_LMM_SECU_INFO_RSLT_SUCC != pstHoSecuInfo->enRslt)
    {
        if ((NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
         && (MM_INTER_RAT_CHANGE      == g_MmGlobalInfo.ucState))
        {
            /* 向MMC回复挂起rsp */
            NAS_MM_SndMmcSuspendRsp();
        }

        return MM_EVENT_ID_INVALID;
    }

    NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_FALSE);
    
    /* 从LMM获取aucCk信息 */
    pucDestBuffer                   = NAS_MML_GetSimCsSecurityUmtsCk();
    pucSrcBuffer                    = pstHoSecuInfo->stHoSecuCntxt.aucCk;
    ulCount                         = MM_LMM_CK_LEN;
    PS_MEM_CPY(pucDestBuffer, pucSrcBuffer, ulCount);

    /* 从LMM获取aucIk信息 */
    pucDestBuffer                   = NAS_MML_GetSimCsSecurityUmtsIk();
    pucSrcBuffer                    = pstHoSecuInfo->stHoSecuCntxt.aucIk;
    ulCount                         = MM_LMM_IK_LEN;
    PS_MEM_CPY(pucDestBuffer, pucSrcBuffer, ulCount);

    /* 从LMM获取ucCksn信息 */
    ucCksn                          = (VOS_UINT8) pstHoSecuInfo->stHoSecuCntxt.ulKSI;
    NAS_MML_SetSimCsSecurityCksn(ucCksn);

    /*根据CK,IK用C3算法计算Kc*/
    NAS_MML_SecContext3GTO2G(NAS_MML_GetSimCsSecurityUmtsIk(),
                             NAS_MML_GetSimCsSecurityUmtsCk(),
                             NAS_MML_GetSimCsSecurityGsmKc());

    if ((NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
     && (MM_INTER_RAT_CHANGE      == g_MmGlobalInfo.ucState))
    {
        /* 向MMC回复挂起rsp */
        NAS_MM_SndMmcSuspendRsp();
    }

    return MM_EVENT_ID_INVALID;
}


/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-22, end */


/*****************************************************************************
 函 数 名  : NAS_MM_ProcBufferedCsfbService
 功能描述  : 收到LMM的注册结果后，尝试处理缓存业务
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年09月22日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_ProcBufferedCsfbService(VOS_VOID)
{
    /* 处理MM的CC缓存 */
    if ((VOS_FALSE == NAS_MML_IsCsfbServiceStatusExist())
     && (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg))
    {
        NAS_MM_RcvCcEstReq_CSFB();
    }

    /* 处理MM的SS缓存 */
    if ((VOS_FALSE == NAS_MML_IsCsfbServiceStatusExist())
     && (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg))
    {
        NAS_MM_RcvSsEstReq_CSFB();
    }

    return ;
}


/*lint -restore */


#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

