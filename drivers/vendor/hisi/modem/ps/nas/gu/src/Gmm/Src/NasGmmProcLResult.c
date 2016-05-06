/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasGmmProcLResult.c
  版 本 号   : 初稿
  作    者   : zhoujun /40661
  生成日期   : 2011年03月14日
  最近修改   :
  功能描述   : GMM收到L模注册结果的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2010年11月12日
    作    者   : zhoujun /40661
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "product_config.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#include "PsTypeDef.h"
#include "GmmExt.h"
#include "NasMmSublayerDef.h"
#include "NasGmmProcLResult.h"
#include "NasMmcSndLmm.h"
#endif
#include "GmmInc.h"
#include "NasGmmSndOm.h"
#include "GmmCasGlobal.h"

#define    THIS_FILE_ID        PS_FILE_ID_GMM_PROC_LRESULT_C


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -save -e958 */

#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_GMM_RcvLmmAttachRegFailOtherCause
 功能描述  : GMM处理来自LMM的ATTACH失败other cause拒绝原因值
 输入参数  : ulAttemptCount - attempt counter值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月19日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_GMM_RcvLmmAttachRegFailOtherCause(
    VOS_UINT32                          ulAttemptCount
)
{
    /*  3GPP TS 24.301 V9.5.0 (2010-12) 5.5.1.2.6中写道:

        d)  ATTACH REJECT, other EMM cause values than those treated
            in subclause 5.5.1.2.5
            Upon reception of the EMM cause #19, "ESM failure",
            the UE may set the attach attempt counter to 5.
            Upon reception of the EMM causes #95, #96, #97, #99 and #111
            the UE should set the attach attempt counter to 5.
            The UE shall proceed as described below.

        If A/Gb mode or Iu mode is supported by the UE,
        the UE shall in addition handle the GMM parameters GMM state,
        GPRS update status, P-TMSI, P-TMSI signature, RAI and GPRS
        ciphering key sequence number as specified in 3GPP TS 24.008 [13]
        for the abnormal case when a normal attach procedure fails
        and the attach attempt counter is equal to 5.
    */
    if (5 <= ulAttemptCount)
    {

        /*set the GPRS update status to GU2 NOT UPDATED*/
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);

        /*delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
        Gmm_DelPsLocInfoUpdateUsim();


        /*迁入GMM_DEREGISTERED_NORMAL_SERVICE;*/
        Gmm_ComStaChg(GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvLmmTauRegFailOtherCause
 功能描述  : GMM处理来自LMM的tau失败other cause拒绝原因值
 输入参数  : ulAttemptCount  - attempt counter值
             enTaiInListFlag - Tai是否在TAI LIST列表中
             enEmmUpStat     - EMM update status
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月19日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_GMM_RcvLmmTauRegFailOtherCause(
    VOS_UINT32                                              ulAttemptCount,
    MMC_LMM_TAI_IN_LIST_FLAG_ENUM_UINT8                     enTaiInListFlag,
    MMC_LMM_EPS_UPDATE_STATUS_ENUM_UINT8                    enEmmUpStat
)
{
    if (VOS_TRUE == NAS_GMM_IsNeedUpdatePsUpdateStatus(ulAttemptCount,
                                       enTaiInListFlag, enEmmUpStat))
    {
        /* GPRS update status GU2 NOT UPDATED */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }

        /* GMM state GMM_REGISTERED_ATTEMPTING_TO_UPDATE*/
        Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE);
    }

    if (5 <= ulAttemptCount)
    {
        /* GMM state GMM_REGISTERED_ATTEMPTING_TO_UPDATE*/
        Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE);

        /*GPRS update status GU2 NOT UPDATED*/
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);


        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }


        /*reset routing area updating attempt counter*/
        g_GmmRauCtrl.ucRauAttmptCnt                     = 0;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvLmmAttachRegFailCause42SevereNetworkFailure
 功能描述  : GMM处理来自LMM的ATTACH失败42拒绝原因值
 输入参数  : ulAttemptCount - attempt counter值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月19日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_GMM_RcvLmmAttachRegFailCause42SevereNetworkFailure(
    VOS_UINT32                          ulAttemptCount
)
{
    /* 如果协议版本小于R11按other cause处理，否则按24301_CR1473R2_(Rel-11)_C1-123386
    CR处理24301 5.5.1.3.5和5.5.1.2.5章节描述:
       If A/Gb mode or Iu mode is supported by the UE, the UE shall in addition
    set the GMM state to GMM-DEREGISTERED, GPRS update status to GU2 NOT UPDATED,
    and shall delete the P-TMSI, P-TMSI signature, RAI and GPRS ciphering key
    sequence number. 该CR受协议版本控制 */
    if (NAS_MML_3GPP_REL_R11 > NAS_MML_GetLte3gppRelVersion())
    {
        NAS_GMM_RcvLmmAttachRegFailOtherCause(ulAttemptCount);
        return;
    }

    /* set the GPRS update status to GU2 NOT UPDATED*/
    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);

    /* delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
    Gmm_DelPsLocInfoUpdateUsim();

    /* 迁入GMM-DEREGISTERED.LIMITSERVICE*/
    Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvLmmTauRegFailCause42SevereNetworkFailure
 功能描述  : GMM处理来自LMM的TAU失败42拒绝原因值
 输入参数  : ulAttemptCount  - attempt counter值
             enTaiInListFlag - TAI是否在TAI list中
             enEmmUpStat     - EMM update status
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月19日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_GMM_RcvLmmTauRegFailCause42SevereNetworkFailure(
    VOS_UINT32                                              ulAttemptCount,
    MMC_LMM_TAI_IN_LIST_FLAG_ENUM_UINT8                     enTaiInListFlag,
    MMC_LMM_EPS_UPDATE_STATUS_ENUM_UINT8                    enEmmUpStat
)
{
    /* 如果协议版本小于R11按other cause处理，否则按24301_CR1473R2_(Rel-11)_C1-123386
    CR处理24301 5.5.3.2.5和5.5.3.3.5章节描述:
       If A/Gb mode or Iu mode is supported by the UE, the UE shall in addition
    set the GMM state to GMM-DEREGISTERED, GPRS update status to GU2 NOT UPDATED,
    and shall delete the P-TMSI, P-TMSI signature, RAI and GPRS ciphering key
    sequence number. 该CR受协议版本控制  */
    if (NAS_MML_3GPP_REL_R11 > NAS_MML_GetLte3gppRelVersion())
    {
        NAS_GMM_RcvLmmTauRegFailOtherCause(ulAttemptCount, enTaiInListFlag, enEmmUpStat);
        return;
    }

    /* set the GPRS update status to GU2 NOT UPDATED*/
    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);

    /* delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
    Gmm_DelPsLocInfoUpdateUsim();

    /* 迁入GMM-DEREGISTERED.LIMITSERVICE*/
    Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
    return;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_RcvLmmAttachCause_Handling
 功能描述  : GMM处理来自LMM的ATTACH拒绝原因值
 输入参数  : enCnCause
             ulAttemptCount
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : luokaihui / 00167671
    修改内容   : 新生成函数

 2.日    期   : 2011年8月8日
   作    者   : luokaihui / 00167671
   修改内容   : 问题单号DTS20110716005544,GPRS UPDATE STATUS需要先设置
 3.日    期   : 2011年10月27日
   作    者   : s46746
   修改内容   : V7R1 PhaseIII,支持L模联合注册

 4.日    期   : 2011年12月1日
   作    者   : zhoujun /40661
   修改内容   : DTS2011101103567
 5.日    期   : 2013年03月06日
   作    者   : s00217060
   修改内容   : for V7R2_CR:增加原因值#35的处理
 6.日    期   : 2013年12月24日
   作    者   : w00242748
   修改内容   : DTS2013101106863:L下被拒原因值#35，只有在R10及其协议以上处理才与#11
                原因值处理相同，否则当做OTHER CAUSE来处理。
 7.日    期   : 2015年4月19日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_GMM_RcvLmmAttachCause_Handling(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause,
    VOS_UINT32                          ulAttemptCount
)
{
    NAS_MML_MS_3GPP_REL_STRU                               *pstMs3GppRel = VOS_NULL_PTR;
    NAS_LMM_CN_CAUSE_ENUM_UINT8                             enTmpCause;

    pstMs3GppRel = NAS_MML_GetMs3GppRel();
    enTmpCause   = enCnCause;

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
        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW:
        case NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:
            NAS_GMM_ProcLmmRejCause3();

            break;

        case NAS_EMM_CAUSE_PLMN_NOT_ALLOW:
        case NAS_EMM_CAUSE_TA_NOT_ALLOW:
        case NAS_EMM_CAUSE_ROAM_NOT_ALLOW:
        case NAS_EMM_CAUSE_NO_SUITABL_CELL:
        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN:


            /*set the GPRS update status to GU3 ROAMING NOT ALLOWED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);

            /*delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
            Gmm_DelPsLocInfoUpdateUsim();


            /*迁入GMM-DEREGISTERED.LIMITSERVICE;*/
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);

            /*reset the GPRS attach attempt counter*/
            g_GmmAttachCtrl.ucAttachAttmptCnt               = 0;

            break;

        /* 4.7.3.1.4	GPRS attach not accepted by the network */
        case NAS_EMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG:

            /*set the GPRS update status to GU3 ROAMING NOT ALLOWED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);

            /*迁入GMM-DEREGISTERED.LIMITSERVICE;*/
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);


            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }

            /*reset the GPRS attach attempt counter*/
            g_GmmAttachCtrl.ucAttachAttmptCnt               = 0;


            break;

        case NAS_EMM_CAUSE_SERVER_NETWORK_FAILURE:
            NAS_GMM_RcvLmmAttachRegFailCause42SevereNetworkFailure(ulAttemptCount);
            break;

        /* OTHERS原因值处理 */
        default:
            NAS_GMM_RcvLmmAttachRegFailOtherCause(ulAttemptCount);
            break;
    }

    return ;

}

/*****************************************************************************
 函 数 名  : NAS_GMM_ProcLmmTauCause_Handling
 功能描述  : GMM处理来自LMM的TAU拒绝原因值
 输入参数  : enCnCause
             ulAttemptCount
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : luokaihui / 00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年10月27日
    作    者   : s46746
    修改内容   : V7R1 PhaseIII,支持L模联合注册

  3.日    期   : 2011年12月1日
    作    者   : zhoujun /40661
    修改内容   : DTS2011101103567
  4.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 PhaseIV
  5.日    期   : 2012年06月08日
    作    者   : L65478
    修改内容   : DTS2012060805375:在#13,#15时到GU下发起的RAU类型错误
  6.日    期   : 2013年03月06日
    作    者   : s00217060
    修改内容   : for V7R2_CR:增加原因值#40,#35的处理
  7.日    期   : 2013年12月24日
    作    者   : w00242748
    修改内容   : DTS2013101106863:L下被拒原因值#35，只有在R10及其协议以上处理才与#11
                 原因值处理相同，否则当做OTHER CAUSE来处理。
  8.日    期   : 2015年4月19日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_GMM_RcvLmmTauCause_Handling(
    NAS_LMM_CN_CAUSE_ENUM_UINT8                             enCnCause,
    VOS_UINT32                                              ulAttemptCount,
    MMC_LMM_TAI_IN_LIST_FLAG_ENUM_UINT8                     enTaiInListFlag,
    MMC_LMM_EPS_UPDATE_STATUS_ENUM_UINT8                    enEmmUpStat
)
{
    NAS_MML_MS_3GPP_REL_STRU                               *pstMs3GppRel = VOS_NULL_PTR;
    NAS_LMM_CN_CAUSE_ENUM_UINT8                             enTmpCause;

    pstMs3GppRel = NAS_MML_GetMs3GppRel();
    enTmpCause   = enCnCause;

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
        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW:
        case NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:
            NAS_GMM_ProcLmmRejCause3();
            break;

        case NAS_EMM_CAUSE_MS_ID_CANNOT_BE_DERIVED_BY_NW:
            /* GMM state GMM_DEREGISTERED_NORMAL_SERVICE*/
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

            /*GPRS update status GU2 NOT UPDATED,*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);

            /*delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
            Gmm_DelPsLocInfoUpdateUsim();

            break;

        case NAS_EMM_CAUSE_EPS_IMPLICITLY_DETACHED:
        case NAS_EMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED:

            /* GMM state GMM_DEREGISTERED_NORMAL_SERVICE*/
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

            break;

        case NAS_EMM_CAUSE_PLMN_NOT_ALLOW:
        case NAS_EMM_CAUSE_TA_NOT_ALLOW:
        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN:

            /* GMM state GMM_REGISTERED_LIMITED_SERVICE*/
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);

            /*GPRS update status GU3 ROAMING NOT ALLOWED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);

            /*delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
            Gmm_DelPsLocInfoUpdateUsim();

            /*reset routing area updating attempt counter*/
            g_GmmRauCtrl.ucRauAttmptCnt                     = 0;

            break;

        case NAS_EMM_CAUSE_ROAM_NOT_ALLOW:
        case NAS_EMM_CAUSE_NO_SUITABL_CELL:
        case NAS_EMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG:

            /* GMM state GMM_REGISTERED_LIMITED_SERVICE*/
            Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);

            /*GPRS update status GU3 ROAMING NOT ALLOWED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);


            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }


            /*reset routing area updating attempt counter*/
            g_GmmRauCtrl.ucRauAttmptCnt                     = 0;

            /* 参考24.008 4.7.5.2.4,#13,#15应该发起combined rau with IMSI attach */
            if (NAS_EMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG != enCnCause)
            {
                g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;
            }
            break;

        case NAS_EMM_CAUSE_SERVER_NETWORK_FAILURE:
            NAS_GMM_RcvLmmTauRegFailCause42SevereNetworkFailure(ulAttemptCount, enTaiInListFlag, enEmmUpStat );
            break;

        default :
            NAS_GMM_RcvLmmTauRegFailOtherCause(ulAttemptCount, enTaiInListFlag, enEmmUpStat);
            break;

        }


        return ;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvLmmNwInitDetachIndCause_Handling
 功能描述  : GMM处理来自LMM的网络触发的DETACH 拒绝原因值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : luokaihui / 00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年8月8日
    作    者   : luokaihui / 00167671
    修改内容   : 问题单号DTS20110716005544,GPRS UPDATE STATUS需要先设置
  3.日    期   : 2011年10月27日
    作    者   : s46746
    修改内容   : V7R1 PhaseIII,支持L模联合注册

  4.日    期   : 2011年12月1日
    作    者   : zhoujun /40661
    修改内容   : DTS2011101103567

  5.日    期   : 2012年04月11日
    作    者   : l65478
    修改内容   : DTS2012032005828网络detach原因值#2时,不应该改变GMM的状态
  5.日    期   : 2013年8月26日
    作    者   : w00242748
    修改内容   : DTS2013071808373编译告警清理
*****************************************************************************/
VOS_VOID  NAS_GMM_RcvLmmNwInitDetachIndCause_Handling(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause
)
{
    switch (enCnCause)
    {
        case NAS_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS:
            break;
        case NAS_EMM_CAUSE_ILLEGAL_UE:
        case NAS_EMM_CAUSE_ILLEGAL_ME:
        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW:
        case NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:
            NAS_GMM_ProcLmmRejCause3();
            break;

        case NAS_EMM_CAUSE_PLMN_NOT_ALLOW:

            /*set the GPRS update status to GU3 ROAMING NOT ALLOWED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);

            /*delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
            Gmm_DelPsLocInfoUpdateUsim();


            /*迁入GMM-DEREGISTERED.LIMITSERVICE;*/
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);

            /*reset the GPRS attach attempt counter*/
            g_GmmAttachCtrl.ucAttachAttmptCnt               = 0;

            break;

        case NAS_EMM_CAUSE_TA_NOT_ALLOW:
        case NAS_EMM_CAUSE_ROAM_NOT_ALLOW:
        case NAS_EMM_CAUSE_NO_SUITABL_CELL:

            /*reset the GPRS attach attempt counter*/
            g_GmmAttachCtrl.ucAttachAttmptCnt               = 0;


            /*set the GPRS update status to GU3 ROAMING NOT ALLOWED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);

            /*delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
            Gmm_DelPsLocInfoUpdateUsim();


            /*迁入GMM-DEREGISTERED.LIMITED-SERVIC*/
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);

            break;

        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN:


            /*set the GPRS update status to GU3 ROAMING NOT ALLOWED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);

            /*delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
            Gmm_DelPsLocInfoUpdateUsim();


            /*reset the GPRS attach attempt counter*/
            g_GmmAttachCtrl.ucAttachAttmptCnt               = 0;


            /*迁入GMM_DEREGISTERED_LIMITED_SERVICE*/
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);

            break;
        /*case NAS_MML_REG_FAIL_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG:*/
        case NAS_EMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG:
            /*reset the GPRS attach attempt counter*/
            g_GmmAttachCtrl.ucAttachAttmptCnt               = 0;

            /*set the GPRS update status to GU3 ROAMING NOT ALLOWED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);


            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }


            /*迁入GMM_DEREGISTERED_LIMITED_SERVICE*/
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);

            break;

     default:

            /*set the GPRS update status to GU2 NOT UPDATED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);

            /*delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
            Gmm_DelPsLocInfoUpdateUsim();


            /*迁入GMM_DEREGISTERED_NORMAL_SERVICE*/
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

         break;
    }

    return ;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvLmmServiceCause_Handling
 功能描述  : GMM处理来自LMM的网络触发的DETACH 拒绝原因值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : luokaihui / 00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年8月8日
    作    者   : luokaihui / 00167671
    修改内容   : 问题单号DTS20110716005544,GPRS UPDATE STATUS需要先设置
  3.日    期   : 2011年10月27日
    作    者   : s46746
    修改内容   : V7R1 PhaseIII,支持L模联合注册

  4.日    期   : 2011年12月1日
    作    者   : zhoujun /40661
    修改内容   : DTS2011101103567
  5.日    期   : 2013年03月06日
    作    者   : s00217060
    修改内容   : for V7R2_CR:增加原因值#40,#35的处理
  6.日    期   : 2013年12月24日
    作    者   : w00242748
    修改内容   : DTS2013101106863:L下被拒原因值#35，只有在R10及其协议以上处理才与#11
                 原因值处理相同，否则当做OTHER CAUSE来处理。
  7.日    期   : 2015年4月20日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID  NAS_GMM_RcvLmmServiceCause_Handling(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause
)
{
    NAS_MML_MS_3GPP_REL_STRU                               *pstMs3GppRel = VOS_NULL_PTR;
    NAS_LMM_CN_CAUSE_ENUM_UINT8                             enTmpCause;

    pstMs3GppRel = NAS_MML_GetMs3GppRel();
    enTmpCause   = enCnCause;

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

        if (NAS_EMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED == enTmpCause)
        {
            enTmpCause = NAS_EMM_CAUSE_EPS_IMPLICITLY_DETACHED;
        }
    }

    switch ( enTmpCause )
    {
        case NAS_EMM_CAUSE_ILLEGAL_UE:
        case NAS_EMM_CAUSE_ILLEGAL_ME:
        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW:
            NAS_GMM_ProcLmmRejCause3();

            break;

        case NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:
            /* 24301_CR1595R2_(Rel-11)_C1-124966，对应24301 5.6.1.5章节，
               处理同#3,#6，该CR受协议版本控制 */
            if (NAS_MML_GetLte3gppRelVersion() >= NAS_MML_3GPP_REL_R11)
            {
                NAS_GMM_ProcLmmRejCause3();
            }
            break;

        case NAS_EMM_CAUSE_PLMN_NOT_ALLOW:
        case NAS_EMM_CAUSE_TA_NOT_ALLOW:


            /*set the GPRS update status to GU3 ROAMING NOT ALLOWED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);

            /*delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
            Gmm_DelPsLocInfoUpdateUsim();

            /*GMM state is GMM_DEREGISTERED_LIMITED_SERVICE*/
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);

            break;

        case NAS_EMM_CAUSE_MS_ID_CANNOT_BE_DERIVED_BY_NW:


            /*set the GPRS update status to GU2 NOT UPDATED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);
            /*delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
            Gmm_DelPsLocInfoUpdateUsim();

            /*enter the state GMM_DEREGISTERED_NORMAL_SERVICE*/
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

            break;

        case NAS_EMM_CAUSE_EPS_IMPLICITLY_DETACHED:

            /*change to state GMM-DEREGISTERED.NORMAL-SERVICE*/
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

            break;

        case NAS_EMM_CAUSE_ROAM_NOT_ALLOW:
        case NAS_EMM_CAUSE_NO_SUITABL_CELL:
        case NAS_EMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG:

           /*set the GPRS update status to GU3 ROAMING NOT ALLOWED */
           NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);


           if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
           {
               Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
           }
           else
           {
               Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
           }



           /*change to state GMM-REGISTERED.LIMITED-SERVICE.*/
           Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);

           break;

        /* 如果协议版本小于R11不处理，否则按24301_CR1473R2_(Rel-11)_C1-123386
          CR处理24301 5.6.1.5章节描述:
              #42:The UE shall set the EPS update status to EU2 NOT UPDATED, and shall delete any GUTI,
          last visited registered TAI, eKSI, and list of equivalent PLMNs. The UE shall start an implementation
          specific timer, setting its value to 2 times the value of T as defined in 3GPP TS 23.122 [6].
          While this timer is running, the UE shall not consider the PLMN + RAT combination that provided this reject cause,
          a candidate for PLMN selection. The UE then enters state EMM-DEREGISTERED.PLMN-SEARCH in order to perform a
          PLMN selection according to 3GPP TS 23.122 [6].
             If A/Gb mode or Iu mode is supported by the UE, the UE shall in addition set
          the GMM state to GMM-DEREGISTERED, GPRS update status to GU2 NOT UPDATED, and shall
          delete the P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number.
          该CR受协议版本控制 */
        case NAS_EMM_CAUSE_SERVER_NETWORK_FAILURE:
            if (NAS_MML_GetLte3gppRelVersion() >= NAS_MML_3GPP_REL_R11)
            {
                /* set the GPRS update status to GU2 NOT UPDATED*/
                NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);

                /* delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
                Gmm_DelPsLocInfoUpdateUsim();

                /* 迁入GMM-DEREGISTERED.LIMITSERVICE*/
                Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
            }
            break;

       default:
           break;

    }

    return ;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvLmmAttachResult
 功能描述  : GMM处理来自LMM的注册结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : luokaihui / 00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年8月8日
    作    者   : luokaihui / 00167671
    修改内容   : 问题单号DTS20110716005544,GPRS UPDATE STATUS需要先设置
  3.日    期   : 2011年08月06日
    作    者   : luokaihui / 00167671
    修改内容   : 问题单号DTS2011080400637,未处理LMM的NAS_MM_REG_RESULT_FAILURE消息
  4.日    期   : 2011年10月19日
    作    者   : w00167002
    修改内容   : V7R1 PHASEII:L下注册成功，但是GMM上报服务状态错误
  5.日    期   : 2011年11月26日
    作    者   : l00167671
    修改内容   : 问题单号DTS2011112606777, L切换到W，RAU过程不回复网侧的鉴权请求
  6.日    期   : 2011年10月27日
    作    者   : s46746
    修改内容   : V7R1 PhaseIII,支持L模联合注册
  7.日    期   : 2011年11月8日
    作    者   : w00176964
    修改内容   : V7R1 PhaseIII,支持L模联合注册:GMM迁移状态到register状态时需要更新ATTACH标记态
  8.日    期   : 2011年11月28日
    作    者   : w00167002
    修改内容   : DTS2011112606777:L下数传切换到w模后，由于GMM当前的状态不对，
                 导致鉴权失败,鉴权失败函数见Gmm_RcvAuthenAndCipherRequestMsg_Preprocess
  9.日    期   : 2011年12月12日
    作    者   : w00176964
    修改内容   : V7R1 PhaseIV,联合注册BBIT:L下不需要GMM回复attach CNF
10.日    期   : 2012年1月8日
    作    者   : z00161729
    修改内容   : V7R1 PhaseIV修改
  11.日    期   : 2011年12月29日
    作    者   : w00167002
    修改内容   : DTS2011102200381:L下注册被拒#12,LMM给MMC带的TAU
                 中的结果为MMC_LMM_TAU_RSLT_FORBID_PLMNS，MMC收到此结果后按照禁止网络
                 来处理而发起了搜网。
                 GMM在收到LMM上报的假流程消息时，若在DEREGISTER状态，则此时
                 迁移到GMM_DEREGISTERED_LIMITED_SERVICE，否则迁移到GMM_REGISTERED_LIMITED_SERVICE.
  12.日    期   : 2012年06月08日
     作    者   : L65478
     修改内容   : DTS2012060805375:在#13,#15时到GU下发起的RAU类型错误
  13.日    期   : 2012年06月20日
     作    者   : L65478
     修改内容   : DTS2012062007677:GCF 6.2.2.1失败,从L重选到W需要发起combined RAU

  14.日    期   : 2013年4月1日
    作    者   : w00167002
    修改内容   : DTS2013032708183:L下注册成功，用户设置CGATT=0，到W下搜网,在
                  搜网过程中，用户设置CGATT=1。结果UE在L下搜网注册成功，MM/GMM
                  没有回复ATTACH CNF,导致AT通道一致被阻塞，GCF9.2.2.1.8用例测试失败。
  15.日    期   : 2014年12月17日
     作    者   : b00269685
     修改内容   : 在Attach成功后停止3314定时器
  16.日    期   : 2015年4月19日
     作    者   : z00161729
     修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID  NAS_GMM_RcvLmmAttachResult(
    VOS_VOID                           *pstMsg
)
{
    MMCGMM_LMM_ATTACH_IND_STRU         *pstLmmAttachMsg;
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause;
    VOS_UINT32                          ulAttemptCount;

    enCnCause      = NAS_EMM_CAUSE_BUTT;
    ulAttemptCount = 0x0;

    pstLmmAttachMsg = (MMCGMM_LMM_ATTACH_IND_STRU *)pstMsg;

    if (VOS_TRUE == pstLmmAttachMsg->bitOpCnCause)
    {
        enCnCause = pstLmmAttachMsg->ucCnCause;
    }

    if (VOS_TRUE == pstLmmAttachMsg->bitOpAtmpCnt)
    {
        ulAttemptCount = pstLmmAttachMsg->ulAttemptCount;
    }

    if (MMC_LMM_ATT_RSLT_SUCCESS == pstLmmAttachMsg->ulAttachRslt)
    {
        /* 迁入GMM-REGISTERED.NO-CELL-AVAILABLE*/



        /* 更新当前GMM的状态为ATTACHED,否则由L模下数传时切换到W模后做RAU
           会导致鉴权失败 */
        Gmm_ComStaChg(GMM_REGISTERED_NO_CELL_AVAILABLE);

        /* 根据GCF要求,在L下联合注册成功后在GU下应该发起COMBINED RAU
           注意: 根据23.060,在SGs接口建立时,需要删除Gs接口,此处的实现和协议不一致 */

        if (VOS_TRUE == pstLmmAttachMsg->bitOpCnRslt)
        {
            g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;

            if (MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI == pstLmmAttachMsg->ulReqType)
            {
                g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_TRUE;
            }
        }
        

        /* 4.7.2.1.2 Handling of READY timer in the MS in Iu mode and S1 mode
           The READY timer is not applicable for Iu mode and S1 mode.
           Upon completion of a successful GPRS attach or routing area updating
           procedure in Iu mode, the MS may stop the READY timer, if running.
           Upon completion of a successful EPS attach or tracking area updating
           procedure, the MS may stop the READY timer, if running. */
        Gmm_TimerStop(GMM_TIMER_T3314);
        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;

        /* 24301_CR1258_(Rel-11)_C1-114316 L下ATTACH成功，GMM迁到GMM-REGISTERED.NO-CELL-AVAILABLE时，
          应该清除attach attempt counter 24301 5.1.4章节描述:
          If the UE performs a successful attach or combined attach procedure
          in S1 mode, it shall enter substates GMM-REGISTERED.NO-CELL-AVAILABLE
          and EMM-REGISTERED.NORMAL-SERVICE. The UE resets the attach attempt
          counter and the GPRS attach attempt counter (see 3GPP TS 24.008 [13]).
          该CR受协议版本控制 */
          g_GmmAttachCtrl.ucAttachAttmptCnt = 0;

#if ( VOS_WIN32 == VOS_OS_VER )
        NAS_GMM_SndTinTypeToMmc(NAS_MML_TIN_TYPE_GUTI);
#endif
    }
    else if (MMC_LMM_ATT_RSLT_ACCESS_BAR == pstLmmAttachMsg->ulAttachRslt)
    {
        /*迁入GMM-DEREGISTERED.ATTACH-NEEDED*/
        Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
    }
    else if (MMC_LMM_ATT_RSLT_CN_REJ == pstLmmAttachMsg->ulAttachRslt)
    {
        NAS_GMM_RcvLmmAttachCause_Handling(enCnCause, ulAttemptCount);
    }

    else if ( (MMC_LMM_ATT_RSLT_TIMER_EXP ==  pstLmmAttachMsg->ulAttachRslt)
           || (MMC_LMM_ATT_RSLT_FAILURE == pstLmmAttachMsg->ulAttachRslt) )

    {
        if (5 <= ulAttemptCount)
        {
            /*set the GPRS update status to GU2 NOT UPDATED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);

            Gmm_DelPsLocInfoUpdateUsim();

            /*迁入GMM_DEREGISTERED_NORMAL_SERVICE;*/
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
        }
    }
    else if ( MMC_LMM_ATT_RSLT_AUTH_REJ ==  pstLmmAttachMsg->ulAttachRslt)
    {
        NAS_GMM_RcvLmmAuthResult(pstMsg);
    }
    else if ( (MMC_LMM_ATT_RSLT_FORBID_PLMN           ==  pstLmmAttachMsg->ulAttachRslt)
           || (MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS    ==  pstLmmAttachMsg->ulAttachRslt)
           || (MMC_LMM_ATT_RSLT_FORBID_PLMN_FOR_GPRS  ==  pstLmmAttachMsg->ulAttachRslt)
           || (MMC_LMM_ATT_RSLT_FORBID_TA_FOR_ROAMING ==  pstLmmAttachMsg->ulAttachRslt) )
    {
        /* GMM在DEREGISTER状态，则此时迁移到GMM_DEREGISTERED_LIMITED_SERVICE */
        if ( VOS_TRUE == NAS_GMM_IsDeregisterState(g_GmmGlobalCtrl.ucState) )
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
        }
        else
        {
            Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);
        }
    }
    else if ((MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW == pstLmmAttachMsg->ulAttachRslt)
          || (MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE == pstLmmAttachMsg->ulAttachRslt)
          || (MMC_LMM_ATT_RSLT_MT_DETACH_FAILURE == pstLmmAttachMsg->ulAttachRslt)
          || (MMC_LMM_ATT_RSLT_T3402_RUNNING == pstLmmAttachMsg->ulAttachRslt)
          || (MMC_LMM_ATT_RSLT_ESM_FAILURE == pstLmmAttachMsg->ulAttachRslt))
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
    }
    else
    {
    }


    /* 判断等待标志是否存在，如果存在则发送MMCGMM_ATTACH CNF,防止AT口一直被CGATT命令阻塞 */
    if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                             & GMM_WAIT_PS_ATTACH))
    {
        NAS_GMM_SndMmcAttachCnf();

        /* 清除Attach cnf回复标志 */
        g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
    }

    return ;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsNeedUpdatePsUpdateStatus
 功能描述  : 判断是否需要更新GPRS UPDATE STATUS
 输入参数  : ulAttemptCount  - 尝试次数
             enTaiInListFlag - TAI是否在TAI列表标志
             enEmmUpStat     - EPS update status
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要更新PS update status
             VOS_FALSE:不需要更新PS update status
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年03月28日
    作    者   : l65478
    修改内容   : DTS2012032002585,从W->L->W，回到W后没有发起RAU

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedUpdatePsUpdateStatus(
    VOS_UINT32                                              ulAttemptCount,
    MMC_LMM_TAI_IN_LIST_FLAG_ENUM_UINT8                     enTaiInListFlag,
    MMC_LMM_EPS_UPDATE_STATUS_ENUM_UINT8                    enEmmUpStat
)
{
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    /* 24301协议:
       If the tracking area updating attempt counter is less than 5,
       and the TAI of the current serving cell is not included in the TAI list
       or the EPS update status is different to EU1 UPDATED:
       If A/Gb mode or Iu mode is supported by the UE, the UE shall in addition
       handle the GPRS update status as specified in 3GPP TS 24.008 [13]
       for the abnormal case when a normal or periodic routing area updating
       procedure fails and the routing area updating attempt counter is less
       than 5 and the GPRS update status is different from GU1 UPDATED.
       24008协议:
       If the routing area updating attempt counter is less than 5, and the
       stored RAI is different to the RAI of the current serving cell or the
       GPRS update status is different to GU1 UPDATED:
       the MS shall start timer T3311, shall set the GPRS update status to GU2
       NOT UPDATED and changes state to GMM-REGISTERED.ATTEMPTING-TO-UPDATE. */
    enTinType = NAS_MML_GetTinType();

    if ((ulAttemptCount != 0)
     && (ulAttemptCount < GMM_ATTACH_RAU_ATTEMPT_MAX_CNT)
     && ((MMC_LMM_TAI_NOT_IN_TAI_LIST == enTaiInListFlag)
     || (MMC_LMM_EPS_UPDATE_STATUS_UPDATED != enEmmUpStat)
     || (NAS_MML_TIN_TYPE_PTMSI == enTinType)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
/*****************************************************************************
 函 数 名  : NAS_GMM_ProcLmmTauResult
 功能描述  : GMM处理来自LMM的TAU结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : luokaihui / 00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年08月06日
    作    者   : luokaihui / 00167671
    修改内容   : 问题单号DTS2011080400637,未处理LMM的NAS_MM_REG_RESULT_FAILURE消息
  3.日    期   : 2011年10月19日
    作    者   : w00167002
    修改内容   : V7R1 PHASEII:L下注册成功，但是GMM上报服务状态错误
  4.日    期   : 2011年10月27日
    作    者   : s46746
    修改内容   : V7R1 PhaseIII,支持L模联合注册
  5.日    期   : 2011年11月8日
    作    者   : w00176964
    修改内容   : V7R1 PhaseIII,支持L模联合注册:GMM迁移状态到register状态时需要更新ATTACH标记
  6.日    期   : 2011年11月30日
    作    者   : z00161729
    修改内容   : V7R1 PhaseIV修改
  7.日    期   : 2012年06月08日
    作    者   : L65478
    修改内容   : DTS2012060805375:在#13,#15时到GU下发起的RAU类型错误
  8.日    期   : 2012年06月20日
    作    者   : L65478
    修改内容   : DTS2012062007677:GCF 6.2.2.1失败,从L重选到W需要发起combined RAU
  9.日    期   : 2014年12月17日
    作    者   : b00269685
    修改内容   : 在Tau成功后停止3314定时器
*****************************************************************************/
VOS_VOID NAS_GMM_RcvLmmTauResult(
    VOS_VOID                           *pstMsg

)
{
    MMCGMM_LMM_TAU_RESULT_IND_STRU                         *pstLmmTauMsg;
    NAS_LMM_CN_CAUSE_ENUM_UINT8                             enCnCause;
    VOS_UINT32                                              ulAttemptCount;

    MMC_LMM_TAI_IN_LIST_FLAG_ENUM_UINT8                     enTaiInListFlag;
    MMC_LMM_EPS_UPDATE_STATUS_ENUM_UINT8                    enEmmUpStat;

    enCnCause       = NAS_EMM_CAUSE_BUTT;
    ulAttemptCount  = 0x0;
    enTaiInListFlag = MMC_LMM_TAI_IN_LIST_FLAG_BUTT;
    enEmmUpStat     = MMC_LMM_EPS_UPDATE_STATUS_BUTT;

    pstLmmTauMsg = (MMCMM_LMM_TAU_RESULT_IND_STRU *)pstMsg;


    if (VOS_TRUE == pstLmmTauMsg->bitOpCnCause)
    {
        enCnCause = pstLmmTauMsg->ucCnCause;
    }

    if (VOS_TRUE == pstLmmTauMsg->bitOpAtmpCnt)
    {
        ulAttemptCount = pstLmmTauMsg->ulAttemptCount;
    }

    if (VOS_TRUE == pstLmmTauMsg->bitOpTaiInListFlag)
    {
        enTaiInListFlag = pstLmmTauMsg->enTaiInListFlag;
    }

    if (VOS_TRUE == pstLmmTauMsg->bitOpEpsUpdateStuts)
    {
        enEmmUpStat = pstLmmTauMsg->enEmmUpStat;
    }

    if (MMC_LMM_TAU_RSLT_SUCCESS == pstLmmTauMsg->ulTauRst)
    {
        /*迁入GMM-REGISTERED.NO-CELL-AVAILABLE;*/

        Gmm_ComStaChg(GMM_REGISTERED_NO_CELL_AVAILABLE);

        /* 根据GCF要求,在L下联合注册成功后在GU下应该发起COMBINED RAU
           注意: 根据23.060,在SGs接口建立时,需要删除Gs接口,此处的实现和协议不一致 */

        if (VOS_TRUE == pstLmmTauMsg->bitOpCnRst)
        {
            g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;

            if ( (MMC_LMM_COMBINED_TA_LA_UPDATING  == pstLmmTauMsg->ulReqType)
              || (MMC_LMM_COMBINED_TA_LA_WITH_IMSI == pstLmmTauMsg->ulReqType)
              || (MMC_LMM_CS_PS_PERIODIC_UPDATING  == pstLmmTauMsg->ulReqType) )
            {
                g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_TRUE;
            }
        }
        

        /* 4.7.2.1.2 Handling of READY timer in the MS in Iu mode and S1 mode
           The READY timer is not applicable for Iu mode and S1 mode.
           Upon completion of a successful GPRS attach or routing area updating
           procedure in Iu mode, the MS may stop the READY timer, if running.
           Upon completion of a successful EPS attach or tracking area updating
           procedure, the MS may stop the READY timer, if running. */
        Gmm_TimerStop(GMM_TIMER_T3314);
        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
    }
    else if (MMC_LMM_TAU_RSLT_ACCESS_BARED == pstLmmTauMsg->ulTauRst)
    {
        /* 迁入GMM_REGISTERED_UPDATE_NEEDED; */
        Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);
    }
    else if (MMC_LMM_TAU_RSLT_CN_REJ == pstLmmTauMsg->ulTauRst)
    {
        NAS_GMM_RcvLmmTauCause_Handling(enCnCause, ulAttemptCount, enTaiInListFlag, enEmmUpStat);
    }

    else if ( (MMC_LMM_TAU_RSLT_TIMER_EXP ==  pstLmmTauMsg->ulTauRst)
           || (MMC_LMM_TAU_RSLT_FAILURE == pstLmmTauMsg->ulTauRst) )

    {
        if (5 <= ulAttemptCount)
        {
            /*GPRS update status GU2 NOT UPDATED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);

            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }

            /* GMM state GMM_REGISTERED_ATTEMPTING_TO_UPDATE*/
            Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE);

            /*routing area updating attempt counter*/
            g_GmmRauCtrl.ucRauAttmptCnt = 0;
        }
        else
        {
            if (VOS_TRUE == NAS_GMM_IsNeedUpdatePsUpdateStatus(ulAttemptCount,
                                               enTaiInListFlag, enEmmUpStat))
            {
                /* GPRS update status GU2 NOT UPDATED */
                NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);

                if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
                {
                    Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
                }
                else
                {
                    Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
                }

                /* GMM state GMM_REGISTERED_ATTEMPTING_TO_UPDATE*/
                Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE);
            }
        }
    }
    else if ( MMC_LMM_TAU_RSLT_AUTH_REJ ==  pstLmmTauMsg->ulTauRst)
    {
        NAS_GMM_RcvLmmAuthResult(pstMsg);
    }

    else if ( (MMC_LMM_TAU_RSLT_FORBID_PLMN           ==  pstLmmTauMsg->ulTauRst)
           || (MMC_LMM_TAU_RSLT_FORBID_TA_FOR_RPOS    == pstLmmTauMsg->ulTauRst)
           || (MMC_LMM_TAU_RSLT_FORBID_PLMN_FOR_GPRS  == pstLmmTauMsg->ulTauRst)
           || (MMC_LMM_TAU_RSLT_FORBID_TA_FOR_ROAMING == pstLmmTauMsg->ulTauRst) )
    {
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);
    }
    else if ((MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE == pstLmmTauMsg->ulTauRst)
          || (MMC_LMM_TAU_RSLT_MT_DETACH_FAILURE == pstLmmTauMsg->ulTauRst)
          || (MMC_LMM_TAU_RSLT_T3402_RUNNING == pstLmmTauMsg->ulTauRst))
    {
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);
    }
    else
    {
    }

    return ;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvLmmMtDetachInd
 功能描述  : GMM处理来自LMM的Detach结果
 输入参数  : pstMsg:Detach消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月28日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2011年12月7日
    作    者   : w00176964
    修改内容   : V7R1 PhaseIV 调整:LMM的local detach指示单独增加消息进行处理
  3.日    期   : 2012年9月07日
    作    者   : l00171473
    修改内容   : DTS2012081701006, 添加GMM状态的可维可测消息
*****************************************************************************/
VOS_VOID  NAS_GMM_RcvLmmMtDetachInd(
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_LMM_MT_DETACH_IND_STRU      *pstLmmDetachMsg;
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause;

    enCnCause       = NAS_EMM_CAUSE_BUTT;

    pstLmmDetachMsg = (MMCGMM_LMM_MT_DETACH_IND_STRU *)pstMsg;

    if (VOS_TRUE == pstLmmDetachMsg->bitOpCnCause)
    {
        enCnCause = pstLmmDetachMsg->ucCnCause;
    }

    /* 如果bitOpCnReqType指示不携带网络下发的Detach类型,打印异常后返回 */
    if (0 == pstLmmDetachMsg->bitOpCnReqType)
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvLmmMtDetachInd: Detach type is not exist.");

        return;
    }

    /* 根据网络下发的Detach类型分别处理 */
    switch (pstLmmDetachMsg->ulCnReqType)
    {
        case MMC_LMM_MT_DET_REATTACH_NOT_REQUIRED:

            /* 根据网络携带的原因值处理 */
            NAS_GMM_RcvLmmNwInitDetachIndCause_Handling(enCnCause);

            break;

        case MMC_LMM_MT_DET_REATTACH_REQUIRED:

            /* 状态迁移GMM_DEREGISTERED_NO_CELL_AVAILABLE */
            g_GmmGlobalCtrl.ucState = GMM_DEREGISTERED_NO_CELL_AVAILABLE;

            NAS_GMM_LogGmmStateInfo(g_GmmGlobalCtrl.ucState);

            break;

        case MMC_LMM_MT_DET_IMSI:

            /* 不处理 */

            break;

        default:

            /* 异常打印 */
            NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvLmmMtDetachInd: Detach type requested by cn is unexpected.");

            break;
    }

    return ;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvLmmMoDetachInd
 功能描述  : 接收到Lmm UE发起的Detach处理
 输入参数  : pstMsg:LMM的UE Detach结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月01日
   作    者   : w00176964
   修改内容   : 新生成函数

  2.日    期   : 2014年3月10日
    作    者   : A00165503
    修改内容   : DTS2014030708580: GMM注册过程中搜LTE, 上层发下发PS域去附着
                 请求, LTE本地去附着后, GMM需要清除业务标识
*****************************************************************************/
VOS_VOID NAS_GMM_RcvLmmMoDetachInd(
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_LMM_MO_DETACH_IND_STRU      *pstLmmDetachMsg = VOS_NULL_PTR;

    pstLmmDetachMsg = (MMCGMM_LMM_MO_DETACH_IND_STRU *)pstMsg;

    switch (pstLmmDetachMsg->ulDetachRslt)
    {
        case  MMC_LMM_DETACH_RSLT_SUCCESS:

            if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
            {
                Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_PS_DETACH);
            }

            g_GmmAttachCtrl.ucSmCnfFlg    = GMM_FALSE;
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

            Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);

            break;

        case MMC_LMM_DETACH_RSLT_AUTH_REJ:

            NAS_GMM_RcvLmmAuthResult(pstMsg);

            break;

        default:

            /* 异常打印 */
            NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvLmmMoDetachInd: Detach result by cn is unexpected.");

            break;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_RcvLmmLocalDetachInd
 功能描述  : 接收到Lmm的local Detach ind处理
 输入参数  : pstMsg:LMM的local Detach结果
 输出参数  : 无
 返 回 值  : 该消息对应的GMM事件
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月07日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_RcvLmmLocalDetachInd(
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_LMM_LOCAL_DETACH_IND_STRU   *pstLmmDetachInd = VOS_NULL_PTR;

    pstLmmDetachInd = (MMCGMM_LMM_LOCAL_DETACH_IND_STRU *)pstMsg;

    /* local detach op项关闭 */
    if ( VOS_FALSE == pstLmmDetachInd->bitOpLocDetType)
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvLmmLocalDetachInd: Invalid local detach type!");

        return;
    }

    switch (pstLmmDetachInd->ulLocDetType)
    {
        /* If A/Gb mode or Iu mode is supported by the UE, the UE shall in addition
           handle the GMM parameters GMM state, GPRS update status, P-TMSI, P-TMSI
           signature, RAI, and GPRS ciphering key sequence number as specified in
           3GPP TS 24.008 [13] for the case when a paging for GPRS services using
           IMSI is received.*/
        case  MMC_LMM_L_LOCAL_DETACH_IMSI_PAGING:

            /* 更新状态变为GU2  */
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);

            Gmm_DelPsLocInfoUpdateUsim();

            /* 调用状态的公共处理 */
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

            break;

        case  MMC_LMM_L_LOCAL_DETACH_OTHERS:

            /* 调用状态的公共处理 */
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);

            break;

        default:

            /* 异常打印 */
            NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvLmmLocalDetachInd: Unexpected local detach type!");

            break;
    }

    return;
}



/*****************************************************************************
 函 数 名  : NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ
 功能描述  : GMM 在REG正常服务状态收到MMC转发的timer info notify的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年3月05日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2012年11月25日
   作    者   : l65478
   修改内容   : DTS2012112606482,GCF 9.2.3.3.2测试失败

*****************************************************************************/
VOS_VOID NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ(VOS_VOID)
{

    /* 3GPP 24.008中4.7.5.2.1 :when the MS is configured to use CS fallback and SMS over SGs,
       or SMS over SGs only, the TIN indicates "RAT-related TMSI" and the periodic tracking
       area update timer T3412 expires;
    */

    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        g_GmmRauCtrl.ucPeriodicRauFlg = GMM_TRUE;
        if (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
        {
            g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_COMBINED;
			/* reference to 24.008 4.7.5.2.1 Combined routing area updating procedure initiation
			   when the MS which is configured to use CS fallback and
			   SMS over SGs, or SMS over SGs only, enters a GERAN or
			   UTRAN cell and the E-UTRAN deactivate ISR timer T3423 has expired */
            NAS_GMM_SndRoutingAreaUpdateReq(GMM_COMBINED_RALA_UPDATING);
        }
        else
        {
            g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_WITH_IMSI_ATTACH;
            NAS_GMM_SndRoutingAreaUpdateReq(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
        }
        return;
    }

    /* CS域允许attach */
    if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
    {
        g_GmmRauCtrl.ucPeriodicRauFlg = GMM_TRUE;
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_WITH_IMSI_ATTACH;
        NAS_GMM_SndRoutingAreaUpdateReq(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_RcvLmmTimerInfoNotify_RegLimitServ
 功能描述  : GMM 在GMM_REGISTERED_NO_CELL_AVAILABLE和GMM_REGISTERED_6LIMITED_SERVICE
             状态收到MMC转发的T3412超时的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年3月05日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2013年2月4日
   作    者   : w00176964
   修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册

*****************************************************************************/
VOS_VOID NAS_GMM_RcvLmmTimerInfoNotify_RegLimitServ(VOS_VOID)
{
    if ((GMM_TRUE == g_GmmGlobalCtrl.SysInfo.ucSysValidFlg)
     && (GMM_FALSE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg))
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3412OrT3423_EXPIRED);
        }
    }
    else
    {
    }
    return;

}


/*****************************************************************************
 函 数 名  : NAS_GMM_RcvLmmTimerStateNotify
 功能描述  : 接收到Lmm的timer info notify处理
 输入参数  : pstMsg - LMM的timer info notify结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年3月01日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_RcvLmmTimerStateNotify(
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulT3412ExpNeedRegFlg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;
    VOS_UINT32                          ulIsAbleCombineRauFlg;

    ulIsAbleCombineRauFlg = NAS_GMM_IsAbleCombinedRau_TimerStatusChg();
    enCurrNetRatType      = NAS_MML_GetCurrNetRatType();
    ulT3412ExpNeedRegFlg  = NAS_GMM_IsT3412ExpiredNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                          NAS_MML_GetTinType(), NAS_MML_GetT3412Status());

    /* 收到L T3412超时消息 */
    if ((NAS_MML_NET_RAT_TYPE_LTE != enCurrNetRatType)
     && (VOS_TRUE == ulT3412ExpNeedRegFlg)
     && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
    {
        switch (g_GmmGlobalCtrl.ucState)
        {
            case GMM_REGISTERED_LIMITED_SERVICE:
            case GMM_REGISTERED_NO_CELL_AVAILABLE:
                NAS_GMM_RcvLmmTimerInfoNotify_RegLimitServ();
                break;

            case GMM_REGISTERED_NORMAL_SERVICE:
            case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
                if (VOS_TRUE == ulIsAbleCombineRauFlg)
                {
                    NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
                }
                break;

            default :
                NAS_INFO_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvLmmTimerInfoNotify: Invalid state");
                break;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMmcEmergencyNumList
 功能描述  : 接收到Mmc的emergency num list ind处理
 输入参数  : pstMsg - MMC从LMM传过来的的emergency num list结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年5月22日
   作    者   : b00269685
   修改内容   : DTS2014050604659新生成函数
 2.日    期   : 2014年6月25日
   作    者   : s00217060
   修改内容   : DTS2014062011040:紧急呼中的MCC用的是上次成功的MCC

*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcEmergencyNumList(
    struct MsgCB                                           *pRcvMsg
)
{
    MMCGMM_EMERGENCY_NUM_LIST_IND_STRU                     *pstMsg = VOS_NULL_PTR;
    NAS_MML_EMERGENCY_NUM_LIST_STRU                         stEmergencyList;

    pstMsg = (MMCGMM_EMERGENCY_NUM_LIST_IND_STRU *)pRcvMsg;
    PS_MEM_SET(&stEmergencyList, 0, sizeof(NAS_MML_EMERGENCY_NUM_LIST_STRU));

    /* if EMC list is existence, update EMC list and send EMC list to CC */
    if (VOS_TRUE == pstMsg->ucOpEmcNumList)
    {
        if (pstMsg->ucEmergencyNumAmount > MMC_GMM_EMERGENCY_NUM_LIST_MAX_RECORDS)
        {
            stEmergencyList.ucEmergencyNumber = MMC_GMM_EMERGENCY_NUM_LIST_MAX_RECORDS;
        }
        else
        {
            stEmergencyList.ucEmergencyNumber = pstMsg->ucEmergencyNumAmount;
        }

        /* get PLMN MCC */
        stEmergencyList.ulMcc  = NAS_MML_GetCurrCampPlmnId()->ulMcc;

        PS_MEM_CPY((VOS_UINT8 *)&(stEmergencyList.aucEmergencyList[0]),
                   (VOS_UINT8 *)&(pstMsg->astEmergencyNumList[0]),
                   sizeof(LMM_MMC_EMERGENCY_NUM_STRU) * (stEmergencyList.ucEmergencyNumber));

        /* update EMC list to MML data base */
        NAS_MML_SetEmergencyNumList(&stEmergencyList);

        /* send EMC list to CC */
        Gmm_SndCcEmergencyNumberList(&stEmergencyList);
    }
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvLmmServiceResult
 功能描述  : GMM处理来自LMM的注册结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : luokaihui / 00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年10月27日
    作    者   : s46746
    修改内容   : V7R1 PhaseIII,支持L模联合注册
*****************************************************************************/
VOS_VOID  NAS_GMM_RcvLmmServiceResult(
    VOS_VOID                           *pstMsg

)
{

    MMCGMM_LMM_SERVICE_RESULT_IND_STRU *pstLmmServiceRsltMsg;
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause;

    enCnCause       = NAS_EMM_CAUSE_BUTT;

    pstLmmServiceRsltMsg = (MMCGMM_LMM_SERVICE_RESULT_IND_STRU *)pstMsg;

    if (VOS_TRUE == pstLmmServiceRsltMsg->bitOpCnCause)
    {
        enCnCause = pstLmmServiceRsltMsg->ucCnCause;
    }

    if (MMC_LMM_SERVICE_RSLT_CN_REJ == pstLmmServiceRsltMsg->ulServiceRst)
    {
        NAS_GMM_RcvLmmServiceCause_Handling(enCnCause);
    }
    else if (MMC_LMM_SERVICE_RSLT_ACCESS_BARED == pstLmmServiceRsltMsg->ulServiceRst)
    {
        Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);
    }
    else if ( MMC_LMM_SERVICE_RSLT_AUTH_REJ ==  pstLmmServiceRsltMsg->ulServiceRst)
    {
        NAS_GMM_RcvLmmAuthResult(pstMsg);
    }
    else
    {

    }

    return ;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvLmmAuthResult
 功能描述  : GMM处理来自LMM的鉴权失败
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : luokaihui / 00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年8月8日
    作    者   : luokaihui / 00167671
    修改内容   : 问题单号DTS20110716005544,GPRS UPDATE STATUS需要先设置
*****************************************************************************/
VOS_VOID  NAS_GMM_RcvLmmAuthResult(
    VOS_VOID                           *pstMsg
)
{
    /*set the GPRS update status to GU3 ROAMING NOT ALLOWED*/
    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);

    /* 设置PS域卡无效*/
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    /*delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
    Gmm_DelPsLocInfoUpdateUsim();

    /*迁入GMM-DEREGISTERED.NOIMSI;*/
    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);

    /* 清除UEID中的IMSI标志位 */
    NAS_GMM_ClearIMSIOfUeID();

    return ;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_MapPtmsiFromGUTI
 功能描述  : 从L模的GUTI获取到PTMST信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_ERR: 从L模获取GUTI失败
             VOS_OK : 从L模获取GUTI成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : W00167002
    修改内容   : 新生成函数

  2.日    期   : 2011年7月27日
    作    者   : l00167671
    修改内容   : P-TMSI 映射错误,单号DTS2011072204749
  3.日    期   : 2012年3月21日
    作    者   : z40661
    修改内容   : DTS2011110201060:L重选到W，被网络拒绝#9后携带的PTMSI不正确
  4.日    期   : 2012年12月28日
    作    者   : s46746
    修改内容   : DSDA GUNAS C CORE项目，重新封装LMM提供的接口函数

*****************************************************************************/
VOS_UINT32  NAS_GMM_MapPtmsiFromGUTI( VOS_VOID )
{
     /*GUTI STRUC
     23.003  2.8.2.1.2
     E UTRAN <M-TMSI> maps as follows:
     -   6 bits of the E UTRAN <M-TMSI> starting at bit 29 and down to bit 24 are mapped into bit 29 and down to bit 24 of the GERAN/UTRAN <P TMSI>;
     -   16 bits of the E UTRAN <M-TMSI> starting at bit 15 and down to bit 0 are mapped into bit 15 and down to bit 0 of the GERAN/UTRAN <P TMSI>;
     E UTRAN <MME Code> maps to GERAN/UTRAN <RAC> and is also copied into the 8 most significant bits of the NRI field within the P TMSI;

    和23.003  2.8.2.0
    P TMSI shall be of 32 bits length where the two topmost bits are reserved and always set to 11. */

    /*
    -----------------------------------------------------------------------------
    | oct10  | oct 9  | oct8   |   oct7     | oct 6       | oct5        |  oct4       |   oct3      |oct2        | oct1          |
    -----------------------------------------------------------------------------
    |        MCC  |     MNC     |  MMEGI | MMEGI  |  MMEC  |  MTMSI   |  MTMSI  | MTMSI  | MTMSI     |
    -----------------------------------------------------------------------------
    |                                        |                                   |\                |\  |           /                /                                /
    |                                        |                                   |     \           |   \            /                /                                /
    |                                        |                                   |         \       |   |  \        /                /                                /
    |                                        |                                   |              \  |   |     \     /                /                                /
    |                                        |                                   |                  \   |           \                  /                               /
    |                                        |                                   |                 |   \            /\                /                               /
    |                                        |                                   |                 |   |   \      /      \           /                               /
    |                                        |                                   |                 |   |        \  /         \       /                               /
    |                                        |                                   |                 |   |          \/             \   /                               /
    ----------------------------------------------------------------------------
    |      MCC    |    MNC     |   LAC     |   LAC      |    RAC    |  PTMSI   |  PTMSI   | PTMSI  | PTMSI     |
    -----------------------------------------------------------------------------
    | oct10  | oct 9  | oct8   |   oct7     | oct 6       |  oct5       |   oct4      |   oct3       | oct2      |  oct1         |
     -----------------------------------------------------------------------------
     LAI,RAI,PTMSI STRUC
    */

    NAS_LMM_INFO_STRU                   stLmmInfo;
    NAS_LMM_GUTI_STRU                  *pstGutiInfo = VOS_NULL_PTR;
    VOS_UINT8                           aucPtmsi[NAS_MML_MAX_PTMSI_LEN];


    /* 公共接口函数Nas_GetLteInfo获取L变量中的GUTI */
    pstGutiInfo                         = &(stLmmInfo.u.stGuti);

    if ( VOS_FALSE ==  NAS_GMM_GetLteGutiValid())
    {
        return VOS_ERR;
    }


    /* GUTI无效直接返回VOS_ERR */
    if ( VOS_TRUE != NAS_GMM_GetLteInfo( NAS_LMM_GUTI, &stLmmInfo ) )
    {
        return VOS_ERR;
    }

    aucPtmsi[0]                         = ( pstGutiInfo->stMTmsi.ucMTmsi & 0x3f ) | 0xc0 ;
    aucPtmsi[1]                         = pstGutiInfo->stMmeCode.ucMmeCode;
    aucPtmsi[2]                         = pstGutiInfo->stMTmsi.ucMTmsiCnt2;
    aucPtmsi[3]                         = pstGutiInfo->stMTmsi.ucMTmsiCnt3;

    /* 将PTMSI拷贝到全局变量中去 */
    PS_MEM_CPY(NAS_GMM_GetMappedPtmsiAddr(), aucPtmsi, NAS_MML_MAX_PTMSI_LEN);


    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_MapRaiFromGUTI
 功能描述  : 从L模的GUTI获取到RAI等信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :VOS_ERR: 从L模获取GUTI失败
            VOS_OK : 从L模获取GUTI成功

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2012年3月21日
    作    者   : z40661
    修改内容   : DTS2011110201060:L重选到W，被网络拒绝#9后携带的PTMSI不正确
  3.日    期   : 2012年12月28日
    作    者   : s46746
    修改内容   : DSDA GUNAS C CORE项目，重新封装LMM提供的接口函数

*****************************************************************************/
VOS_UINT32  NAS_GMM_MapRaiFromGUTI( VOS_VOID )
{
    /*23.003  2.8.2.1.2
    E UTRAN <MCC> maps to GERAN/UTRAN <MCC>
    E UTRAN <MNC> maps to GERAN/UTRAN <MNC>
    E UTRAN <MME Group ID> maps to GERAN/UTRAN <LAC>
    E UTRAN <MME Code> maps to GERAN/UTRAN <RAC> and is also copied into the 8 most significant bits of the NRI field within the P TMSI;
    */
    /*GUTI STRUC
       -----------------------------------------------------------------------------
       | oct10  | oct 9  | oct8   |   oct7     | oct 6       | oct5        |  oct4       |   oct3      |oct2        | oct1
       -----------------------------------------------------------------------------
       |        MCC  |     MNC     |  MMEGI | MMEGI  |  MMEC  |  MTMSI   |  MTMSI  | MTMSI  | MTMSI
       -----------------------------------------------------------------------------
       |                                        |                                   |\                |\  |           |                |
       |                                        |                                   |     \           |   \            |                |
       |                                        |                                   |         \       |   |  \        |                |
       |                                        |                                   |              \  |   |     \    |                 |
       |                                        |                                   |                  \   |           \                 |
       |                                        |                                   |                 |   \            | \              |
       |                                        |                                   |                 |   |     \     |     \          |
       |                                        |                                   |                 |   |        \   |         \     |
       |                                        |                                   |                 |  |          \  |            \  |
       -----------------------------------------------------------------------------
       |      MCC    |    MNC     |   LAC     |   LAC      |    RAC     |  PTMSI  |  PTMSI   | PTMSI  | PTMSI
       -----------------------------------------------------------------------------
       | oct10  | oct 9  | oct8   |   oct7     | oct 6       |  oct5       |   oct4      |   oct3       | oct2      |  oct1
        -----------------------------------------------------------------------------
        LAI,RAI,PTMSI STRUC
       */

    NAS_LMM_INFO_STRU                   stLmmInfo;
    NAS_LMM_GUTI_STRU                  *pstGutiInfo = VOS_NULL_PTR;
    GMM_RAI_STRU                        stRai;

    if ( VOS_FALSE ==  NAS_GMM_GetLteGutiValid())
    {
        return VOS_ERR;
    }


    /* 公共接口函数Nas_GetLteInfo获取L变量中的GUTI */
    /* GUTI无效直接返回VOS_ERR */
    if ( VOS_TRUE != NAS_GMM_GetLteInfo( NAS_LMM_GUTI, &stLmmInfo ) )
    {
        return VOS_ERR;
    }

    pstGutiInfo                         = &(stLmmInfo.u.stGuti);

    /* 获取PLMN信息 */
    NAS_GMM_ConvertLmmPlmnToGmmPlmnId( &(pstGutiInfo->stPlmnId), &(stRai.Lai.PlmnId) );

    /* 获取LAC信息 */
    stRai.Lai.aucLac[0]                 = pstGutiInfo->stMmeGroupId.ucGroupId;
    stRai.Lai.aucLac[1]                 = pstGutiInfo->stMmeGroupId.ucGroupIdCnt;

    /* 获取RAC信息 */
    stRai.ucRac                         = pstGutiInfo->stMmeCode.ucMmeCode;

    /* rai写入全局变量 */
    NAS_GMM_SetMappedRai(stRai);
    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_MapLaiFromGUTI
 功能描述  : 从L模的GUTI获取到LAI等信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_ERR: 从L模获取GUTI失败
             VOS_OK : 从L模获取GUTI成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2012年3月21日
    作    者   : z40661
    修改内容   : DTS2011110201060:L重选到W，被网络拒绝#9后携带的PTMSI不正确
  3.日    期   : 2012年12月28日
    作    者   : s46746
    修改内容   : DSDA GUNAS C CORE项目，重新封装LMM提供的接口函数

*****************************************************************************/
VOS_UINT32  NAS_GMM_MapLaiFromGUTI( VOS_VOID )
{
    /*23.003  2.8.2.1.2
    E UTRAN <MCC> maps to GERAN/UTRAN <MCC>
    E UTRAN <MNC> maps to GERAN/UTRAN <MNC>
    E UTRAN <MME Group ID> maps to GERAN/UTRAN <LAC>
    E UTRAN <MME Code> maps to GERAN/UTRAN <RAC> and is also copied into the 8 most significant bits of the NRI field within the P TMSI;
    */

    /*GUTI STRUC
       -----------------------------------------------------------------------------
       | oct10  | oct 9  | oct8   |   oct7     | oct 6       | oct5        |  oct4       |   oct3      |oct2        | oct1
       -----------------------------------------------------------------------------
       |        MCC  |     MNC     |  MMEGI | MMEGI  |  MMEC  |  MTMSI   |  MTMSI  | MTMSI  | MTMSI
       -----------------------------------------------------------------------------
       |                                        |                                   |\                |\  |           |                |
       |                                        |                                   |     \           |   \            |                |
       |                                        |                                   |         \       |   |  \        |                |
       |                                        |                                   |              \  |   |     \    |                 |
       |                                        |                                   |                  \   |           \                 |
       |                                        |                                   |                 |   \            | \              |
       |                                        |                                   |                 |   |     \     |     \          |
       |                                        |                                   |                 |   |        \   |         \     |
       |                                        |                                   |                 |  |          \  |            \  |
       -----------------------------------------------------------------------------
       |      MCC    |    MNC     |   LAC     |   LAC      |    RAC     |  PTMSI  |  PTMSI   | PTMSI  | PTMSI
       -----------------------------------------------------------------------------
       | oct10  | oct 9  | oct8   |   oct7     | oct 6       |  oct5       |   oct4      |   oct3       | oct2      |  oct1
        -----------------------------------------------------------------------------
        LAI,RAI,PTMSI STRUC
       */

    NAS_LMM_INFO_STRU                   stLmmInfo;
    NAS_LMM_GUTI_STRU                  *pstGutiInfo = VOS_NULL_PTR;
    GMM_LAI_STRU                        stLai;

    if ( VOS_FALSE ==  NAS_GMM_GetLteGutiValid())
    {
        return VOS_ERR;
    }

    /* 公共接口函数Nas_GetLteInfo获取L变量中的GUTI */
    /* GUTI无效直接返回VOS_ERR */
    if ( VOS_TRUE != NAS_GMM_GetLteInfo( NAS_LMM_GUTI, &stLmmInfo ) )
    {
        return VOS_ERR;
    }

    pstGutiInfo                         = &(stLmmInfo.u.stGuti);

    /* 获取PLMN信息 */
    NAS_GMM_ConvertLmmPlmnToGmmPlmnId( &(pstGutiInfo->stPlmnId), &(stLai.PlmnId) );

    /* 获取LAC信息 */
    stLai.aucLac[0]                     = pstGutiInfo->stMmeGroupId.ucGroupId;
    stLai.aucLac[1]                     = pstGutiInfo->stMmeGroupId.ucGroupIdCnt;


    /* Lai写入全局变量 */
    NAS_GMM_SetMappedLai(stLai);

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : NAS_GMM_MapPtmsiSignFromGUTI
 功能描述  : 从L模的GUTI,NAS TOKEN获取到PTMSI signature等信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_ERR: 从L模获取GUTI失败
             VOS_OK : 从L模获取GUTI成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : W00167002
    修改内容   : 新生成函数

  2.日    期   : 2011年7月27日
    作    者   : l00167671
    修改内容   : P-TMSI SIGNATURE映射错误,单号DTS2011072204749
  3.日    期   : 2012年3月21日
    作    者   : z40661
    修改内容   : DTS2011110201060:L重选到W，被网络拒绝#9后携带的PTMSI不正确
  4.日    期   : 2012年12月28日
    作    者   : s46746
    修改内容   : DSDA GUNAS C CORE项目，重新封装LMM提供的接口函数

*****************************************************************************/
VOS_UINT32  NAS_GMM_MapPtmsiSignFromGUTIAndNasToken( VOS_VOID )
{
    /* 23.003  2.8.2.1.2
    E UTRAN <M-TMSI> maps as follows:
    -   6 bits of the E UTRAN <M-TMSI> starting at bit 29 and down to bit 24 are mapped into bit 29 and down to bit 24 of the GERAN/UTRAN <P TMSI>;
    -   16 bits of the E UTRAN <M-TMSI> starting at bit 15 and down to bit 0 are mapped into bit 15 and down to bit 0 of the GERAN/UTRAN <P TMSI>;
    -   and the remaining 8 bits of the E UTRAN <M-TMSI> are mapped into the 8 MBS bits of the <P-TMSI signature> field.
    The remaining 2 octets of the <P-TMSI signature> shall be filled according to subclause 9.1.1 in 3GPP TS.33.401 [89].
    和33.401  9.1.1
    The x bits available in the P-TMSI signature field (at minimum 16 bits) shall be filled with the truncated NAS-token, which is defined as the x least significant bits of the NAS-token.*/

    NAS_LMM_INFO_STRU                   stLmmInfo;
    VOS_UINT8                          *pucPtmsiSignature = VOS_NULL_PTR;
    VOS_UINT8                          *pucNasToken       = VOS_NULL_PTR;
    NAS_LMM_GUTI_STRU                  *pstGutiInfo       = VOS_NULL_PTR;

    pucPtmsiSignature                   = NAS_GMM_GetMappedPtmsiSignAddr();
    pucNasToken                         = NAS_GMM_GetNasTokenAddr();

    if ( VOS_FALSE ==  NAS_GMM_GetLteGutiValid())
    {
        return VOS_ERR;
    }

    /* 公共接口函数Nas_GetLteInfo获取L变量中的GUTI */
    /* GUTI无效直接返回VOS_ERR */
    if ( VOS_TRUE != NAS_GMM_GetLteInfo( NAS_LMM_GUTI, &stLmmInfo ) )
    {
        return VOS_ERR;
    }

    pstGutiInfo                         = &(stLmmInfo.u.stGuti);

    pucPtmsiSignature[0]                = pstGutiInfo->stMTmsi.ucMTmsiCnt1;
    pucPtmsiSignature[1]                = pucNasToken[NAS_GMM_LMM_TOKEN_LEN-2];
    pucPtmsiSignature[2]                = pucNasToken[NAS_GMM_LMM_TOKEN_LEN-1];

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsGutiInfoValid
 功能描述  : 检测Guti信息是否有效
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: 从L模获取GUTI失败
             VOS_FALSE : 从L模获取GUTI成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月01日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsGutiInfoValid( VOS_VOID )
{
    NAS_LMM_INFO_STRU                   stLmmInfo;

    if ( VOS_FALSE ==  NAS_GMM_GetLteGutiValid())
    {
        return VOS_FALSE;
    }

    /* 公共接口函数Nas_GetLteInfo获取L变量中的GUTI */
    /* GUTI无效直接返回VOS_FALSE */
    if ( VOS_TRUE != NAS_GMM_GetLteInfo( NAS_LMM_GUTI, &stLmmInfo ) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_GetGUSecContextFromEpsSecContextInHandOver
 功能描述  : L切换到GU下从EPS Security Context上下文转换为UMTS Security Context
 输入参数  : LMM_GMM_HO_SECU_INFO_CNF_STRU消息的首地址
 输出参数  : 无
 返 回 值  : VOS_ERR: 从L模获取安全信息失败
              VOS_OK : 从L模获取安全信息成功
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月17日
   作    者   : h4270
   修改内容   : 新生成函数

 2.日    期   : 2013年10月18日
   作    者   : z00234330
   修改内容   : dts2013101800405
 3.日    期   : 2014年11月01日
   作    者   : s00217060
   修改内容   : DTS2014101700891:REGISTER_PLMN_SRCH状态收到LTE的安全上下文回复发起注册
 4.日    期   : 2015年2月6日
   作    者   : h00313353
   修改内容   : USIMM卡接口调整
*****************************************************************************/
VOS_VOID NAS_GMM_GetGUSecContextFromEpsSecContextInHandOver(
    struct MsgCB                       *pstMsg
)
{
    LMM_GMM_HO_SECU_INFO_CNF_STRU      *pstHandOverMsg  = VOS_NULL_PTR;
    VOS_UINT8                          *pucNasToken     = VOS_NULL_PTR;
    VOS_UINT8                          *pucDestBuffer   = VOS_NULL_PTR;
    VOS_VOID                           *pucSrcBuffer    = VOS_NULL_PTR;

    VOS_UINT8                           ucCksn;
    VOS_UINT32                          ulCount;

    ulCount                             = 0;
    pstHandOverMsg                      = ( LMM_GMM_HO_SECU_INFO_CNF_STRU * )pstMsg;
    pucNasToken                         = NAS_GMM_GetNasTokenAddr();

    /*LMM未生成映射的UMTS安全上下文,须将NAS TOKEN置成0，GPRSCKSN置成无效值，见24008:4.7.3.1.1
    If a current EPS security does not exist, the MS shall set the truncated NAS token included in the P-TMSI signature to all zeros
    and the GPRS ciphering key sequence number to "No key is available"
    */
    if ( ( LMM_GMM_SECU_INFO_RSLT_FAIL      == pstHandOverMsg->enRslt )
      || ( 0 == pstHandOverMsg->bitOpSecuCntxt ) )
    {
        /* GUTI有效并且获取GUTI成功时，将NAS TOKEN置成0，GPRS CKSN置成无效值
           否则就使用本地的，不从LTE映射 */
        if (VOS_TRUE == NAS_GMM_IsGutiInfoValid())
        {
            PS_MEM_SET( pucNasToken, 0, LMM_GMM_NAS_TOKEN_LEN );
            NAS_MML_SetSimPsSecurityCksn(NAS_MML_CKSN_INVALID);
        }

        return;
    }

    NAS_MML_SetUsimDoneGsmPsAuthFlg(VOS_FALSE);

    /* 从LMM获取aucCk信息 */
    pucDestBuffer                   = NAS_MML_GetSimPsSecurityUmtsCk();
    pucSrcBuffer                    = pstHandOverMsg->stHoUmtsSecuCntxt.aucUmtsCk;
    ulCount                         = LMM_GMM_CK_LEN;
    PS_MEM_CPY(pucDestBuffer, pucSrcBuffer, ulCount);

    /* 从LMM获取aucIk信息 */
    pucDestBuffer                   = NAS_MML_GetSimPsSecurityUmtsIk();
    pucSrcBuffer                    = pstHandOverMsg->stHoUmtsSecuCntxt.aucUmtsIk;
    ulCount                         = LMM_GMM_IK_LEN;
    PS_MEM_CPY(pucDestBuffer, pucSrcBuffer, ulCount);

    /* 从LMM获取ucCksn信息 */
    ucCksn                          = (VOS_UINT8) pstHandOverMsg->stHoUmtsSecuCntxt.KSI;
    NAS_MML_SetSimPsSecurityCksn(ucCksn);


    /*根据CK,IK用C3算法计算Kc*/
    NAS_MML_SecContext3GTO2G(NAS_MML_GetSimPsSecurityUmtsIk(),
                             NAS_MML_GetSimPsSecurityUmtsCk(),
                             NAS_MML_GetSimPsSecurityGsmKc());

    /*将UMTSSecurityContext的CK,IK,KSI,Kc,GprsCKSN保存到USIM;保存CK,IK,Kc值到SIM中 */
    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYSPS_ID);      /* 更新SIM中的CKSN,Ck,IK*/
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKCGPRS_ID);      /* 更新SIM中的GSM CKSN,Kc*/
    }
    else
    {/* 2G SIM */
        Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKCGPRS_ID);   /* 更新SIM中的GSM CKSN,Kc*/
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_GetUmtsSecurityContextFromEpsSecurityContext
 功能描述  : L重选到GU下从EPS Security Context上下文转换为UMTS Security Context
 输入参数  : LMM_GMM_RESEL_SECU_INFO_CNF_STRU消息的首地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月11日
   作    者   : W00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
 3.日    期   : 2011年12月2日
   作    者   : s46746
   修改内容   : 从L异系统改变到GU后，没有指派加密密钥到GU接入层
 4.日    期   : 2012年03月20日
   作    者   : l00130025
   修改内容   : DTS2012030105247,NAS只在网侧实际发起鉴权时,通知W SecurityKey，其它情况下由WAS调用对应接口获取

 5.日    期   : 2013年10月18日
   作    者   : z00234330
   修改内容   : dts2013101800405
 6.日    期   : 2014年11月01日
   作    者   : s00217060
   修改内容   : DTS2014101700891:REGISTER_PLMN_SRCH状态收到LTE的安全上下文回复发起注册
*****************************************************************************/
VOS_VOID NAS_GMM_GetGUSecContextFromEpsSecContextInReselect(
    struct MsgCB                       *pstMsg
)
{
    LMM_GMM_RESEL_SECU_INFO_CNF_STRU   *pstReselMsg     = VOS_NULL_PTR;
    VOS_UINT8                          *pucNasToken     = VOS_NULL_PTR;
    VOS_UINT8                          *pucDestBuffer   = VOS_NULL_PTR;
    VOS_VOID                           *pucSrcBuffer    = VOS_NULL_PTR;

    VOS_UINT8                           ucCksn;
    VOS_UINT32                          ulCount;

    ulCount                             = 0;
    pstReselMsg                         = ( LMM_GMM_RESEL_SECU_INFO_CNF_STRU * )pstMsg;
    pucNasToken                         = NAS_GMM_GetNasTokenAddr();

    /*LMM未生成映射的UMTS安全上下文,须将NAS TOKEN置成0，GPRSCKSN置成无效值，见24008:4.7.3.1.1
    If a current EPS security does not exist, the MS shall set the truncated NAS token included in the P-TMSI signature to all zeros
    and the GPRS ciphering key sequence number to "No key is available"
    */
    if ( ( LMM_GMM_SECU_INFO_RSLT_FAIL      == pstReselMsg->enRslt )
      || ( 0 == pstReselMsg->bitOpSecuInfo ) )
    {
        /* GUTI有效并且获取GUTI成功时，将NAS TOKEN置成0，GPRS CKSN置成无效值
           否则就使用本地的，不从LTE映射 */
        if (VOS_TRUE == NAS_GMM_IsGutiInfoValid())
        {
            PS_MEM_SET( pucNasToken, 0, LMM_GMM_NAS_TOKEN_LEN );
            NAS_MML_SetSimPsSecurityCksn(NAS_MML_CKSN_INVALID);
        }

        return;
    }

    NAS_MML_SetUsimDoneGsmPsAuthFlg(VOS_FALSE);

    /* 从LMM获取aucCk信息 */
    pucDestBuffer                   = NAS_MML_GetSimPsSecurityUmtsCk();
    pucSrcBuffer                    = pstReselMsg->stReselSecuInfo.stUmtsSecuContext.aucUmtsCk;
    ulCount                         = LMM_GMM_CK_LEN;
    PS_MEM_CPY(pucDestBuffer, pucSrcBuffer, ulCount);

    /* 从LMM获取aucIk信息 */
    pucDestBuffer                   = NAS_MML_GetSimPsSecurityUmtsIk();
    pucSrcBuffer                    = pstReselMsg->stReselSecuInfo.stUmtsSecuContext.aucUmtsIk;
    ulCount                         = LMM_GMM_IK_LEN;
    PS_MEM_CPY(pucDestBuffer, pucSrcBuffer, ulCount);

    /* 从LMM获取ucCksn信息 */
    ucCksn                          = (VOS_UINT8) pstReselMsg->stReselSecuInfo.stUmtsSecuContext.KSI;
    NAS_MML_SetSimPsSecurityCksn(ucCksn);

    /* 从LMM获取aucNasToken信息 */
    pucDestBuffer                   = NAS_GMM_GetNasTokenAddr();
    pucSrcBuffer                    = pstReselMsg->stReselSecuInfo.aucNasToken;
    ulCount                         = LMM_GMM_NAS_TOKEN_LEN;
    PS_MEM_CPY(pucDestBuffer, pucSrcBuffer, ulCount);

    /*根据CK,IK用C3算法计算Kc*/
    NAS_MML_SecContext3GTO2G(NAS_MML_GetSimPsSecurityUmtsIk(),
                             NAS_MML_GetSimPsSecurityUmtsCk(),
                             NAS_MML_GetSimPsSecurityGsmKc());

    /*将UMTSSecurityContext的CK,IK,KSI,Kc,GprsCKSN保存到USIM;保存CK,IK,Kc值到SIM中 */
    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYSPS_ID);        /* 更新SIM中的CKSN,Ck,IK*/
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKCGPRS_ID);   /* 更新SIM中的GSM CKSN,Kc*/
    }
    else
    {/* 2G SIM */
        Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKCGPRS_ID);   /* 更新SIM中的GSM CKSN,Kc*/
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_GetPtmsiInfo
 功能描述  : 获取GU的PTMSI的值
 输入参数  : 无
 输出参数  : pstPtmsi:GU PTMSI的值
 返 回 值  : VOS_OK:当前PTMSI参数有效
              VOS_ERR:当前PTMSI参数无效
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月23日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_GMM_GetPtmsiInfo(
    NAS_GUMM_PTMSI_STRU                 *pstPtmsi
)
{
    VOS_UINT8                           *pucSrcBuffer  = VOS_NULL_PTR;
    VOS_UINT32                           ulCount;
    VOS_UINT32                           i;

    /* 获取GUNAS侧的PTMSI信息 */
    pucSrcBuffer                = NAS_MML_GetUeIdPtmsi();
    ulCount                     = NAS_MML_MAX_PTMSI_LEN;
    PS_MEM_CPY( pstPtmsi->aucPtmsi, pucSrcBuffer, ulCount );

    for ( i = 0 ; i < ulCount ; i++ )
    {
        if ( GMM_PTMSI_INVALID != pstPtmsi->aucPtmsi[i] )
        {
            break;
        }
    }

    /* PTMSI值全为0xFF */
    if ( i >= ulCount )
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_GetPtmsiSignature
 功能描述  : 获取GU的PTMSI Signature的值
 输入参数  : 无
 输出参数  : pstPtmsi:GU PTMSI的值
 返 回 值  : VOS_OK:当前PTMSI Signature参数有效
              VOS_ERR:当前PTMSI Signature参数无效
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月23日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_GMM_GetPtmsiSignature(
    NAS_GUMM_PTMSI_SIGNATURE_STRU       *pstPtmsiSignature
)
{
    VOS_UINT8                           *pucSrcBuffer  = VOS_NULL_PTR;
    VOS_UINT32                           ulCount;
    VOS_UINT32                           i;

    pucSrcBuffer                = NAS_MML_GetUeIdPtmsiSignature();
    ulCount                     = NAS_MML_MAX_PTMSI_SIGNATURE_LEN;
    PS_MEM_CPY( pstPtmsiSignature->aucPtmsiSign, pucSrcBuffer, ulCount );

    for ( i = 0 ; i < ulCount ; i++ )
    {
        if ( GMM_PTMSI_SIGNATURE_INVALID != pstPtmsiSignature->aucPtmsiSign[i] )
        {
            break;
        }
    }

    /* PTMSI值全为0xFF */
    if ( i >= ulCount )
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_GetGuInfo
 功能描述  : 获取到GUNAS侧相关信息，提供给LMM使用
 输入参数  : NAS_GUMM_INFO_TYPE_ENUM_UINT32       ulInfoType
 输出参数  : NAS_GUMM_INFO_STRU                  *pstGuInfo
 返 回 值  : VOS_OK:获取GU侧相关信息成功
              VOS_ERR:获取GU侧相关信息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : W00167002
    修改内容   : 新生成函数

*****************************************************************************/
MMC_LMM_RESULT_ID_ENUM_UINT32  Nas_GetGuInfo(
    NAS_GUMM_INFO_TYPE_ENUM_UINT32      ulInfoType,
    NAS_GUMM_INFO_STRU                 *pstGuInfo
)
{
    /* 申明拷贝的源地址,目的地址以及拷贝的字节长度 */
    VOS_UINT32                           ulRet;

    ulRet                               = VOS_OK;

    PS_MEM_SET( pstGuInfo, 0, sizeof( NAS_GUMM_INFO_STRU ) );

    switch (ulInfoType)
    {
        case NAS_GUMM_PTMSI:
            /* 获取GUNAS侧的PTMSI信息 */
            ulRet = NAS_GMM_GetPtmsiInfo(&(pstGuInfo->u.stPtmsi));
            break;

        case NAS_GUMM_PTMSI_SIGNATURE:
            /* 获取GUNAS侧的PTMSI_SIGNATURE信息 */
            ulRet = NAS_GMM_GetPtmsiSignature(&(pstGuInfo->u.stPtmsiSignature));
            break;

        case NAS_GUMM_LAI:
            /* pstGuInfo->u.stLai = 全局变量.stLai;*/
            /* 获取GUNAS侧的LAI信息 */
            ulRet = NAS_GMM_GetLaiInfo( &(pstGuInfo->u.stLai) );
            break;

        case NAS_GUMM_RAI:
            /* 获取GUNAS侧的RAI信息 */
            ulRet = NAS_GMM_GetRaiInfo( &(pstGuInfo->u.stRAI));
            break;

        case NAS_GUMM_UMTS_SECU_PARA:
            /* 从GU NAS拷贝安全参数给LMM */
            ulRet = NAS_GMM_GetGuSecuInfo( &(pstGuInfo->u.stSecuContext) );
            break;

        case NAS_GUMM_TMSI_STATUS:
            /* 从GU NAS获取TMSI有效性信息 */
            NAS_GMM_GetTmsiStatusInfo( &(pstGuInfo->u.ulTmsiStatus) );
            break;

        default:
            break;
    }

    if ( VOS_OK != ulRet )
    {
        return MMC_LMM_FAIL;
    }

    return MMC_LMM_SUCC;
}

/*****************************************************************************
 函 数 名  : Nas_GetGuSecuInfo
 功能描述  : 从GU NAS获取LAI有效性信息
 输入参数  : 无
 输出参数  : MMC_LMM_LAI_STRU                    *stLai
 返 回 值  : VOS_OK:当前LAI参数有效
              VOS_ERR:当前LAI参数无效
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月8日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年12月13日
    作    者   : w00176964
    修改内容   : 问题单DTS2011121303813修改:联合attach、TAU成功后，LMM向GU NAS获取的LAI信息为CS域保存的LAI信息

*****************************************************************************/
VOS_UINT32  NAS_GMM_GetLaiInfo(
    MMC_LMM_LAI_STRU                    *pstLai
)
{
    /* 获取GUNAS侧的LAI信息 */
    NAS_MML_PLMN_ID_STRU                stGUNasPlmn;
    NAS_MML_LAI_STRU                   *pstCsSuccLai = VOS_NULL_PTR;

    pstCsSuccLai    = NAS_MML_GetCsLastSuccLai( );

    PS_MEM_SET( &stGUNasPlmn, 0, sizeof( NAS_MML_PLMN_ID_STRU ) );

    /* 先判断LAI是否有效, */
    if ( ( NAS_MML_LAC_LOW_BYTE_INVALID == pstCsSuccLai->aucLac[0])
      && ( NAS_MML_LAC_HIGH_BYTE_INVALID == pstCsSuccLai->aucLac[1]))
    {
        return VOS_ERR;
    }

    /* 将MM的PLMN id转换为LMM格式的PLMN id */
    NAS_MML_ConvertNasPlmnToLMMFormat(&(pstLai->stPlmnId), &(pstCsSuccLai->stPlmnId));

    /* 填充LAC值 */
    pstLai->stLac.ucLac                  = pstCsSuccLai->aucLac[0];
    pstLai->stLac.ucLacCnt               = pstCsSuccLai->aucLac[1];

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_GetRaiInfo
 功能描述  : 从GU NAS获取RAI有效性信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK:当前RAI参数有效
              VOS_ERR:当前RAI参数无效
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月19日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数
  2.日    期   : 2012年2月6日
    作    者   : w00176964
    修改内容   : DTS2012011804122:UE从U模切换到L模，TAU被拒.

*****************************************************************************/
VOS_UINT32  NAS_GMM_GetRaiInfo(
    MMC_LMM_RAI_STRU                   *pstRai
)
{
    NAS_MML_RAI_STRU                   *pstRaiInfo = VOS_NULL_PTR;

    /* 获取GUNAS侧的LAI信息 */
    NAS_MML_PLMN_ID_STRU                stGUNasPlmn;

    PS_MEM_SET( &stGUNasPlmn, 0, sizeof( NAS_MML_PLMN_ID_STRU ) );

    pstRaiInfo  = NAS_MML_GetPsLastSuccRai();

    /* 先判断LAI是否有效, */
    if ( ( NAS_MML_LAC_LOW_BYTE_INVALID == pstRaiInfo->stLai.aucLac[0])
      && ( NAS_MML_LAC_HIGH_BYTE_INVALID == pstRaiInfo->stLai.aucLac[1]))
    {
        return VOS_ERR;
    }

    /* 将GMM的PLMN id转换为LMM格式的PLMN id */
    NAS_MML_ConvertNasPlmnToLMMFormat(&(pstRai->stLai.stPlmnId), &(pstRaiInfo->stLai.stPlmnId));

    /* 填充LAC值 */
    pstRai->stLai.stLac.ucLac                  = pstRaiInfo->stLai.aucLac[0];
    pstRai->stLai.stLac.ucLacCnt               = pstRaiInfo->stLai.aucLac[1];


    /* 获取RAC的值 */
    pstRai->ucRac   = pstRaiInfo->ucRac;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : Nas_GetGuSecuInfo
 功能描述  : 从GU NAS获取TMSI有效性信息
 输入参数  : 无
 输出参数  : MMC_LMM_TMSI_STATUS_TYPE_ENUM_UINT32 *ulTmsiStatus
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月8日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2012年06月09日
    作    者   : L65478
    修改内容   : DTS2012060801488:在注册成功时,指定搜索一个禁止的PLMN,TMSI状态错误

*****************************************************************************/
VOS_VOID  NAS_GMM_GetTmsiStatusInfo(
    MMC_LMM_TMSI_STATUS_TYPE_ENUM_UINT32 *ulTmsiStatus
)
{
    VOS_UINT8                           ucMsIdFlg;

    ucMsIdFlg                           = NAS_MM_GetMsIdFlg();

    /* TMSI是否存在性检查 */
    if ( MM_MS_ID_TMSI_PRESENT == ( MM_MS_ID_TMSI_PRESENT & ucMsIdFlg ) )
    {
        *ulTmsiStatus               = MMC_LMM_TMSI_STATUS_VALID;
        return ;
    }

    *ulTmsiStatus                       = MMC_LMM_TMSI_STATUS_INVALID;

    return ;
}


/*****************************************************************************
 函 数 名  : Nas_GetGuSecuInfo
 功能描述  : 从GU NAS拷贝安全参数给LMM
 输入参数  : 无
 输出参数  : NAS_GUMM_UMTS_CONTEXT_STRU          *stSecuContext
 返 回 值  : VOS_OK:当前安全参数有效
              VOS_ERR:当前安全参数无效
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月8日
    作    者   : W00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_GMM_GetGuSecuInfo(
    NAS_GUMM_UMTS_CONTEXT_STRU         *pstSecuContext
)
{
    /* 申明拷贝的源地址,目的地址以及拷贝的字节长度 */
    VOS_UINT8                          *pucDestBuffer = VOS_NULL_PTR;
    VOS_UINT8                          *pucSrcBuffer  = VOS_NULL_PTR;
    VOS_UINT32                          ulCount;
    VOS_UINT32                          i;

    ulCount                             = 0;
    PS_MEM_SET( pstSecuContext, 0, sizeof( NAS_GUMM_UMTS_CONTEXT_STRU ) );

    /* 获取GUNAS侧的ucKSI信息 */
    pstSecuContext->ucKSI               = NAS_MML_GetSimPsSecurityCksn();
    if ( NAS_MML_CKSN_INVALID == pstSecuContext->ucKSI )
    {
        return VOS_ERR;
    }

    /* 获取GUNAS侧的aucCK信息 */
    pucDestBuffer                       = pstSecuContext->aucCK;
    pucSrcBuffer                        = NAS_MML_GetSimPsSecurityUmtsCk();
    ulCount                             = LMM_GMM_CK_LEN;
    PS_MEM_CPY( pucDestBuffer, pucSrcBuffer, ulCount );
    for ( i = 0 ; i < LMM_GMM_CK_LEN ; i++ )
    {
        if ( pucDestBuffer[i]  != GMM_CK_INVALID )
        {
            break;
        }
    }
    if ( i >= LMM_GMM_CK_LEN )
    {
        return VOS_ERR;
    }


    /* 获取GUNAS侧的aucIK信息 */
    pucDestBuffer                       = (VOS_UINT8*)pstSecuContext->aucIK;
    pucSrcBuffer                        = NAS_MML_GetSimPsSecurityUmtsIk();
    ulCount                             = LMM_GMM_IK_LEN;
    PS_MEM_CPY( pucDestBuffer, pucSrcBuffer, ulCount );
    for ( i = 0 ; i < LMM_GMM_IK_LEN ; i++ )
    {
        if ( pucDestBuffer[i]  != GMM_IK_INVALID )
        {
            break;
        }
    }
    if ( i >= LMM_GMM_IK_LEN )
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_ConvertLmmPlmnToGmmPlmn
 功能描述  : 将L模的PLMN转换为GMM的plmn形式
 输入参数  : MMC_LMM_PLMN_ID_STRU                 stLmmPlmn
 输出参数  : GMM_PLMN_ID_STRU                    *pstGmmPlmn
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : W00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_ConvertLmmPlmnToGmmPlmnId(
    MMC_LMM_PLMN_ID_STRU                *pstLmmPlmn,
    GMM_PLMN_ID_STRU                    *pstGmmPlmn
)
{
    /* 将LMM的国家号转换为GMM的国家号形式 */
    pstGmmPlmn->aucMccDigit[0]          = (pstLmmPlmn->aucPlmnId[0]) & 0x0F;
    pstGmmPlmn->aucMccDigit[1]          = (pstLmmPlmn->aucPlmnId[0]) >> 4;
    pstGmmPlmn->aucMccDigit[2]          = (pstLmmPlmn->aucPlmnId[1]) & 0x0F;

    /* 将LMM的网络号转换为GMM的网络号形式 */
    pstGmmPlmn->aucMncDigit[0]          = (pstLmmPlmn->aucPlmnId[2]) & 0x0F;
    pstGmmPlmn->aucMncDigit[1]          = (pstLmmPlmn->aucPlmnId[2]) >> 4;
    pstGmmPlmn->aucMncDigit[2]          = (pstLmmPlmn->aucPlmnId[1]) >> 4;

    /* 判断网络号的位数并赋值 */
    pstGmmPlmn->ucMncCnt                = 3;

    if ( 0x0F == pstGmmPlmn->aucMncDigit[2] )
    {
        pstGmmPlmn->ucMncCnt            = 2;
    }

    return ;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_ProcLmmRejCause3
 功能描述  : GMM收到LMM的注册结果是卡无效的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月27日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2011年8月8日
    作    者   : luokaihui / 00167671
    修改内容   : 问题单号DTS20110716005544,GPRS UPDATE STATUS需要先设置

*****************************************************************************/
VOS_VOID  NAS_GMM_ProcLmmRejCause3( VOS_VOID )
{
    

    

    /*set the GPRS update status to GU3 ROAMING NOT ALLOWED*/
    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);

    /* 设置GMM的卡无效 */
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    /*delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
    Gmm_DelPsLocInfoUpdateUsim();

    /*迁入GMM-DEREGISTERED.NOIMSI;*/
    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);


    /* 清除相关标志 */
    NAS_GMM_ClearIMSIOfUeID();
}


/*****************************************************************************
 函 数 名  : NAS_GMM_LogGutiInfo
 功能描述  : 通过Trace显示从同步接口获取的GUTI相关信息
 输入参数  : NAS_LMM_GUTI_STRU                    stGutiMsg
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_LogGutiInfo(
    NAS_LMM_GUTI_STRU                  *pstGuti
)
{
    NAS_GMM_LOG_GUTI_INFO_STRU         *pstGutiMsg = VOS_NULL_PTR;

    pstGutiMsg = (NAS_GMM_LOG_GUTI_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                             sizeof(NAS_GMM_LOG_GUTI_INFO_STRU));
    if ( VOS_NULL_PTR == pstGutiMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_LogGutiInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstGutiMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstGutiMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstGutiMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    pstGutiMsg->stMsgHeader.ulLength        = sizeof(pstGutiMsg->stGutiMsg) + 4;
    pstGutiMsg->stMsgHeader.ulMsgName       = NAS_GMM_LOG_GUTI_INFO_IND;

    PS_MEM_CPY(&(pstGutiMsg->stGutiMsg), pstGuti, sizeof(NAS_LMM_GUTI_STRU));

    DIAG_TraceReport(pstGutiMsg);

    PS_MEM_FREE(WUEPS_PID_GMM, pstGutiMsg);

    return;
}
/*lint -restore */

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

