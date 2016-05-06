/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcProcRegRslt.c
  版 本 号   : 初稿
  作    者   : z40661
  生成日期   : 2010年5月9日
  最近修改   :
  功能描述   : 注册公共处理函数
  函数列表   :
  修改历史   :
  1.日    期   : 2011年05月9日
    作    者   : z40661
    修改内容   : 创建文件
  2.日    期   : 2011年7月22日
    作    者   : l00130025
    修改内容   : PhaseII修改

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasMmlCtx.h"
#include "NasMmlLib.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndGmm.h"
#include "NasMmcSndMm.h"
#include "NasMmcSndLmm.h"
#include "NasMmSublayerDef.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcSndMscc.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcCtx.h"
#include "NVIM_Interface.h"
#include "NasMmcProcUsim.h"
#include "NasMmcProcNvim.h"
#include "NasMmcProcRegRslt.h"
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
/* 删除ExtAppMmcInterface.h*/
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */
#include "NasMmcComFunc.h"
#include "NasMmcSndOm.h"
#include "NVIM_Interface.h"

#include "NasUsimmApi.h"

#include "NasMmcPlmnSelectionStrategy.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_PROC_REG_RSLT_C

/*****************************************************************************
  2 全局变量
*****************************************************************************/

/* 在NasMmcProcRegRslt.c文件中处理注册结果表中，主要是通过CAUSE来进行处理，
   然而仅根据此信息来处理注册结果是不完备的，譬如需要知道Attemp Counter信息，
   现在将处理注册结果的消息保存在本地的全局变量里面，这样在处理注册结果时候，
   可获得所有的注册结果信息，这样函数处理能力得到了极大的扩张，注册结果处理函数
   本身的架构得到稳定  */
NAS_MMC_REG_RSLT_CTX_STRU               gstRegRsltCtx;


/* CS注册被拒原因值的协议处理,处理规则为:协议中明确规定的原因值，以及这些规定的原因值
   所映射出来的对应原因值，则在表中进行显式的处理; 否则将进入异常分支进行处理 */
NAS_MMC_REG_FAIL_PROC_ENTITY             gastMmcProcCsRegFailCause[] =
{
    {NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR,                      NAS_MMC_ProcCsRegFailCause2ImsiUnknownInHlr},
    {NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS,                               NAS_MMC_ProcCsRegFailCause3IllegalMs},
    {NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME,                               NAS_MMC_ProcCsRegFailCause6IllegalMe},
    {NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW,                           NAS_MMC_ProcCsRegFailCause11PlmnNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW,                             NAS_MMC_ProcCsRegFailCause12LaNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW,                           NAS_MMC_ProcCsRegFailCause13RoamNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL,                          NAS_MMC_ProcCsRegFailCause15NoSuitableCell},

    {NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE,                          NAS_MMC_ProcCsRegFailCause17NetWorkFailure},

    /* Upon reception of the cause codes # 95, # 96, # 97, # 99 and # 111 the MS should set the attempt counter to 4.*/
    {NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG,               NAS_MMC_ProcCsRegFailCause95SemanticallyIncorrectMsg},
    {NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF,                    NAS_MMC_ProcCsRegFailCause96InvalidMandatoryInf},
    {NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE,               NAS_MMC_ProcCsRegFailCause97MsgNonExistNotImplement},
    {NAS_MML_REG_FAIL_CAUSE_IE_NONEXIST_NOTIMPLEMENTED,               NAS_MMC_ProcCsRegFailCause99IeNonExistNotImplement},
    {NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR,                           NAS_MMC_ProcCsRegFailCause111ProtocolError},

    {NAS_MML_REG_FAIL_CAUSE_AUTH_REJ,                                 NAS_MMC_ProcCsRegFailCause256AuthRej},
    {NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED,                            NAS_MMC_ProcCsRegFailCause257AccessBarrd},
    {NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT,                            NAS_MMC_ProcCsRegFailCause301TimerTimeOut},
    {NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL,                         NAS_MMC_ProcCsRegFailCause302RrConnEstFail},
    {NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL,                             NAS_MMC_ProcCsRegFailCause303RrConnFail},

    {NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE,                              NAS_MMC_ProcCsRegFailCause401OtherCause},
    {NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT,                NAS_MMC_ProcCsRegFailCause402MsCfgDomainNotSupport},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN,                           NAS_MMC_ProcCsRegFailCause403ForbiddenPlmn},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS,            NAS_MMC_ProcCsRegFailCause404ForbiddenLaForRegPrvsSvs},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM,                    NAS_MMC_ProcCsRegFailCause405ForbiddenLaForRoam},
    {NAS_MML_REG_FAIL_CAUSE_SIM_INVALID,                              NAS_MMC_ProcCsRegFailCause407SimInvalid},
    {NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI,                               NAS_MMC_ProcCsRegFailCause408NetDetachImsi},
    {NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT,          NAS_MMC_ProcCsRegFailCause409ServingCellDomainNotSupport},

    {NAS_MML_REG_FAIL_CAUSE_DELAY_CS_IN_TRANS_LAU,                    NAS_MMC_ProcCsRegFailCause416DealyCsInTransLau},

    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-30, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    {NAS_MML_REG_FAIL_CAUSE_ECALL_INACTIVE,                          NAS_MMC_ProcCsRegFailCause417ECallInactive},
#endif
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-30, end */

    {NAS_MML_REG_FAIL_CAUSE_T3212_RUNNING,                            NAS_MMC_ProcCsRegFailCause418T3212Running},

    {NAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC,                    NAS_MMC_ProcCsRegFailCause419InterRatChangeSucc},
};

/* PS注册被拒原因值的协议处理,处理规则为:协议中明确规定的原因值，以及这些规定的原因值
   所映射出来的对应原因值，则在表中进行显式的处理; 否则将进入异常分支进行处理 */
NAS_MMC_REG_FAIL_PROC_ENTITY             gastMmcProcPsRegFailCause[] =
{
    {NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS,                               NAS_MMC_ProcPsRegFailCause3IllegalMs},
    {NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME,                               NAS_MMC_ProcPsRegFailCause6IllegalMe},
    {NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW,                      NAS_MMC_ProcPsRegFailCause7GprsServNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW,    NAS_MMC_ProcPsRegFailCause8GprsAndNonGprsNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED,                        NAS_MMC_ProcPsRegFailCause9MsIdNotDerived},
    {NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED,                        NAS_MMC_ProcPsRegFailCause10ImplicitDetached},
    {NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW,                           NAS_MMC_ProcPsRegFailCause11PlmnNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW,                             NAS_MMC_ProcPsRegFailCause12LaNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW,                           NAS_MMC_ProcPsRegFailCause13RoamNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN,              NAS_MMC_ProcPsRegFailCause14GprsNotAllowInThisPlmn},
    {NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL,                          NAS_MMC_ProcPsRegFailCause15NoSuitableCell},
    {NAS_MML_REG_FAIL_CAUSE_NO_PDP_CONTEXT_ACT,                       NAS_MMC_ProcPsRegFailCause40NoPdpContextActived},

    /* Upon reception of the cause codes # 95, # 96, # 97, # 99 and # 111 the MS should set the GPRS attach attempt counter to 5.*/
    {NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG,               NAS_MMC_ProcPsRegFailCause95SemanticallyIncorrectMsg},
    {NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF,                    NAS_MMC_ProcPsRegFailCause96InvalidMandatoryInf},
    {NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE,               NAS_MMC_ProcPsRegFailCause97MsgNonExistNotImplement},
    {NAS_MML_REG_FAIL_CAUSE_IE_NONEXIST_NOTIMPLEMENTED,               NAS_MMC_ProcPsRegFailCause99IeNonExistNotImplement},
    {NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR,                           NAS_MMC_ProcPsRegFailCause111ProtocolError},

    {NAS_MML_REG_FAIL_CAUSE_AUTH_REJ,                                 NAS_MMC_ProcPsRegFailCause256AuthRej},
    {NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED,                            NAS_MMC_ProcPsRegFailCause257AccessBarrd},
    {NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT,                            NAS_MMC_ProcPsRegFailCause301TimerTimeOut},
    {NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL,                         NAS_MMC_ProcPsRegFailCause302RrConnEstFail},
    {NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL,                             NAS_MMC_ProcPsRegFailCause303RrConnFail},

    {NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE,                              NAS_MMC_ProcPsRegFailCause401OtherCause},
    {NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT,                NAS_MMC_ProcPsRegFailCause402MsCfgDomainNotSupport},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN,                           NAS_MMC_ProcPsRegFailCause403ForbiddenPlmn},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS,            NAS_MMC_ProcPsRegFailCause404ForbiddenLaForRegPrvsSvs},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM,                    NAS_MMC_ProcPsRegFailCause405ForbiddenLaForRoam},

    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS,                  NAS_MMC_ProcPsRegFailCause406ForbiddenPlmnForGprs},
    {NAS_MML_REG_FAIL_CAUSE_SIM_INVALID,                              NAS_MMC_ProcPsRegFailCause407SimInvalid},
    {NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI,                               NAS_MMC_ProcPsRegFailCause408NetDetachImsi},
    {NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT,          NAS_MMC_ProcPsRegFailCause409ServingCellDomainNotSupport},
    {NAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC,                    NAS_MMC_ProcPsRegFailCause419InterRatChangeSucc},
};
#if   (FEATURE_ON == FEATURE_LTE)

/* EPS注册被拒原因值的协议处理,处理规则为:协议中明确规定的原因值，以及这些规定的原因值
   所映射出来的对应原因值，则在表中进行显式的处理; 否则将进入异常分支进行处理 */

/* Eps 联合attach两个域被拒原因值的协议处理 */
NAS_MMC_COMBINED_EPS_REG_REJ_PROC_ENTITY             gastMmcProcCombinedAttachEpsRegFailCause[] =
{
    {NAS_EMM_CAUSE_ILLEGAL_UE,                                        NAS_MMC_ProcCombinedEpsRegFailCause3IllegalMs},
    {NAS_EMM_CAUSE_ILLEGAL_ME,                                        NAS_MMC_ProcCombinedEpsRegFailCause6IllegalMe},
    {NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW,                                NAS_MMC_ProcCombinedEpsRegFailCause7EpsServNotAllow},
    {NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW,               NAS_MMC_ProcCombinedEpsRegFailCause8GprsAndNonGprsNotAllow},
    {NAS_EMM_CAUSE_PLMN_NOT_ALLOW,                                    NAS_MMC_ProcCombinedEpsRegFailCause11PlmnNotAllow},
    {NAS_EMM_CAUSE_TA_NOT_ALLOW,                                      NAS_MMC_ProcCombinedEpsRegFailCause12TaNotAllow},
    {NAS_EMM_CAUSE_ROAM_NOT_ALLOW,                                    NAS_MMC_ProcCombinedEpsRegFailCause13RoamNotAllow},
    {NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN,                        NAS_MMC_ProcCombinedEpsRegFailCause14GprsNotAllowInThisPlmn},
    {NAS_EMM_CAUSE_NO_SUITABL_CELL,                                   NAS_MMC_ProcCombinedEpsRegFailCause15NoSuitableCell},

    {NAS_EMM_CAUSE_ESM_FAILURE,                                       NAS_MMC_ProcCombinedEpsRegFailCause19EsmFailure},
    {NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN,       NAS_MMC_ProcCombinedEpsRegFailCause35ReqServOptNotAuthorizedInThisPlmn},

    {NAS_MML_REG_FAIL_CAUSE_SEVERE_NETWORK_FAILURE,                   NAS_MMC_ProcCombinedEpsRegFailCause42SevereNetworkFailure},

    {NAS_MML_REG_FAIL_CAUSE_AUTH_REJ,                                 NAS_MMC_ProcCombinedEpsRegFailCause256AuthRej},
    {NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED,                            NAS_MMC_ProcCombinedEpsRegFailCause257AccessBarrd},
    {NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT,                            NAS_MMC_ProcCombinedEpsRegFailCause301TimerTimeOut},
    {NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE,                              NAS_MMC_ProcCombinedEpsRegFailCause401OtherCause},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN,                           NAS_MMC_ProcCombinedEpsRegFailCause403ForbiddenPlmn},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS,            NAS_MMC_ProcCombinedEpsRegFailCause404ForbiddenTaForRegPrvsSvs},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM,                    NAS_MMC_ProcCombinedEpsRegFailCause405ForbiddenLaForRoam},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS,                  NAS_MMC_ProcCombinedEpsRegFailCause406ForbiddenPlmnForGprs},
    {NAS_MML_REG_FAIL_CAUSE_PS_ATTACH_NOT_ALLOW,                      NAS_MMC_ProcCombinedEpsRegFailCausePsAttachNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_ESM_BEAR_FAILURE,                         NAS_MMC_ProcCombinedEpsRegFailCauseEpsBearerEstFail},
    {NAS_MML_REG_FAIL_CAUSE_MO_DETACH_FAILURE,                        NAS_MMC_ProcCombinedEpsRegFailCauseMoDetach},
    {NAS_MML_REG_FAIL_CAUSE_MT_DETACH_FAILURE,                        NAS_MMC_ProcCombinedEpsRegFailCauseMtDetach},
    {NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_FAIL,                   NAS_MMC_ProcCombinedEpsRegFailCauseT3402Running},
};

/* Eps 联合tau两个域被拒原因值的协议处理 */
NAS_MMC_COMBINED_EPS_REG_REJ_PROC_ENTITY             gastMmcProcCombinedTauEpsRegFailCause[] =
{
    {NAS_EMM_CAUSE_ILLEGAL_UE,                                        NAS_MMC_ProcCombinedEpsRegFailCause3IllegalMs},
    {NAS_EMM_CAUSE_ILLEGAL_ME,                                        NAS_MMC_ProcCombinedEpsRegFailCause6IllegalMe},
    {NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW,                                NAS_MMC_ProcCombinedEpsRegFailCause7EpsServNotAllow},
    {NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW,               NAS_MMC_ProcCombinedEpsRegFailCause8GprsAndNonGprsNotAllow},
    {NAS_EMM_CAUSE_MS_ID_CANNOT_BE_DERIVED_BY_NW,                     NAS_MMC_ProcCombinedEpsRegFailCause9MsidCannotDerivedByNw},
    {NAS_EMM_CAUSE_EPS_IMPLICITLY_DETACHED,                           NAS_MMC_ProcCombinedEpsRegFailCause10ImplicitlyDetached},
    {NAS_EMM_CAUSE_PLMN_NOT_ALLOW,                                    NAS_MMC_ProcCombinedEpsRegFailCause11PlmnNotAllow},
    {NAS_EMM_CAUSE_TA_NOT_ALLOW,                                      NAS_MMC_ProcCombinedEpsRegFailCause12TaNotAllow},
    {NAS_EMM_CAUSE_ROAM_NOT_ALLOW,                                    NAS_MMC_ProcCombinedEpsRegFailCause13RoamNotAllow},
    {NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN,                        NAS_MMC_ProcCombinedEpsRegFailCause14GprsNotAllowInThisPlmn},
    {NAS_EMM_CAUSE_NO_SUITABL_CELL,                                   NAS_MMC_ProcCombinedEpsRegFailCause15NoSuitableCell},
    {NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN,       NAS_MMC_ProcCombinedEpsRegFailCause35ReqServOptNotAuthorizedInThisPlmn},

    {NAS_EMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED,                   NAS_MMC_ProcCombinedEpsRegFailCause40NoEpsBearerActived},

    {NAS_MML_REG_FAIL_CAUSE_SEVERE_NETWORK_FAILURE,                  NAS_MMC_ProcCombinedEpsRegFailCause42SevereNetworkFailure},


    {NAS_MML_REG_FAIL_CAUSE_AUTH_REJ,                                 NAS_MMC_ProcCombinedEpsRegFailCause256AuthRej},
    {NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED,                            NAS_MMC_ProcCombinedEpsRegFailCause257AccessBarrd},
    {NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE,                              NAS_MMC_ProcCombinedEpsRegFailCause401OtherCause},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN,                           NAS_MMC_ProcCombinedEpsRegFailCause403ForbiddenPlmn},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS,            NAS_MMC_ProcCombinedEpsRegFailCause404ForbiddenTaForRegPrvsSvs},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM,                    NAS_MMC_ProcCombinedEpsRegFailCause405ForbiddenLaForRoam},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS,                  NAS_MMC_ProcCombinedEpsRegFailCause406ForbiddenPlmnForGprs},

    {NAS_MML_REG_FAIL_CAUSE_ESM_BEAR_FAILURE,                         NAS_MMC_ProcCombinedEpsRegFailCauseEpsBearerEstFail},
    {NAS_MML_REG_FAIL_CAUSE_MO_DETACH_FAILURE,                        NAS_MMC_ProcCombinedEpsRegFailCauseMoDetach},
    {NAS_MML_REG_FAIL_CAUSE_MT_DETACH_FAILURE,                        NAS_MMC_ProcCombinedEpsRegFailCauseMtDetach},
    {NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_FAIL,                   NAS_MMC_ProcCombinedEpsRegFailCauseT3402Running},
};


/* Eps 联合注册Ps域成功，CS域被拒原因值的协议处理 */
NAS_MMC_REG_FAIL_PROC_ENTITY                        gastMmcProcCombinedEpsRegOnlyEpsSuccCause[] =
{
    {NAS_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS,                               NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause2ImsiUnknownInHss},
    {NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE,                          NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause16MscNotReachable},
    {NAS_EMM_CAUSE_NETWORKFAILURE,                                    NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause17NetworkFailure},
    {NAS_EMM_CAUSE_CS_DOMAIN_NOT_AVAILABLE,                           NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause18CsDomainNotAvailable},
    {NAS_EMM_CAUSE_CONGESTION,                                        NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause22Congestion},
};


/* Eps 注册被拒原因值的协议处理 */
NAS_MMC_REG_FAIL_PROC_ENTITY             gastMmcProcEpsAttachRegFailCause[] =
{
    {NAS_EMM_CAUSE_ILLEGAL_UE,                                        NAS_MMC_ProcEpsAttachRegFailCause3IllegalMs},
    {NAS_EMM_CAUSE_ILLEGAL_ME,                                        NAS_MMC_ProcEpsAttachRegFailCause6IllegalMe},
    {NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW,                                NAS_MMC_ProcEpsAttachRegFailCause7EpsServNotAllow},
    {NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW,               NAS_MMC_ProcEpsAttachRegFailCause8GprsAndNonGprsNotAllow},
    {NAS_EMM_CAUSE_PLMN_NOT_ALLOW,                                    NAS_MMC_ProcEpsAttachRegFailCause11PlmnNotAllow},
    {NAS_EMM_CAUSE_TA_NOT_ALLOW,                                      NAS_MMC_ProcEpsAttachRegFailCause12TaNotAllow},
    {NAS_EMM_CAUSE_ROAM_NOT_ALLOW,                                    NAS_MMC_ProcEpsAttachRegFailCause13RoamNotAllow},
    {NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN,                        NAS_MMC_ProcEpsAttachRegFailCause14GprsNotAllowInThisPlmn},
    {NAS_EMM_CAUSE_NO_SUITABL_CELL,                                   NAS_MMC_ProcEpsAttachRegFailCause15NoSuitableCell},
    {NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN,       NAS_MMC_ProcEpsAttachRegFailCause35ReqServOptNotAuthorizedInThisPlmn},

    {NAS_MML_REG_FAIL_CAUSE_SEVERE_NETWORK_FAILURE,                   NAS_MMC_ProcEpsAttachRegFailCause42SevereNetworkFailure},

    {NAS_MML_REG_FAIL_CAUSE_AUTH_REJ,                                 NAS_MMC_ProcEpsAttachRegFailCause256AuthRej},
    {NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED,                            NAS_MMC_ProcEpsAttachRegFailCause257AccessBarrd},
    {NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT,                            NAS_MMC_ProcEpsAttachRegFailCause301TimerTimeOut},
    {NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE,                              NAS_MMC_ProcEpsAttachRegFailCause401OtherCause},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN,                           NAS_MMC_ProcEpsAttachRegFailCause403ForbiddenPlmn},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS,            NAS_MMC_ProcEpsAttachRegFailCause404ForbiddenTaForRegPrvsSvs},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM,                    NAS_MMC_ProcEpsAttachRegFailCause405ForbiddenLaForRoam},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS,                  NAS_MMC_ProcEpsAttachRegFailCause406ForbiddenPlmnForGprs},
    {NAS_MML_REG_FAIL_CAUSE_PS_ATTACH_NOT_ALLOW,                      NAS_MMC_ProcEpsAttachRegFailCausePsAttachNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_ESM_BEAR_FAILURE,                         NAS_MMC_ProcEpsAttachRegFailCauseEpsBearerEstFail},
    {NAS_MML_REG_FAIL_CAUSE_MO_DETACH_FAILURE,                        NAS_MMC_ProcEpsAttachRegFailCauseMoDetach},
    {NAS_MML_REG_FAIL_CAUSE_MT_DETACH_FAILURE,                        NAS_MMC_ProcEpsAttachRegFailCauseMtDetach},
    {NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_FAIL,                   NAS_MMC_ProcEpsAttachRegFailCauseT3402Running},
};




/* Eps TAU被拒原因值的协议处理 */
NAS_MMC_REG_FAIL_PROC_ENTITY             gastMmcProcEpsTauRegFailCause[] =
{
    {NAS_EMM_CAUSE_ILLEGAL_UE,                                        NAS_MMC_ProcEpsTauRegFailCause3IllegalMs},
    {NAS_EMM_CAUSE_ILLEGAL_ME,                                        NAS_MMC_ProcEpsTauRegFailCause6IllegalMe},
    {NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW,                                NAS_MMC_ProcEpsTauRegFailCause7EpsServNotAllow},
    {NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW,               NAS_MMC_ProcEpsTauRegFailCause8GprsAndNonGprsNotAllow},

    {NAS_EMM_CAUSE_MS_ID_CANNOT_BE_DERIVED_BY_NW,                     NAS_MMC_ProcEpsTauRegFailCause9MsIdCannotBeDerivedByNW},
    {NAS_EMM_CAUSE_EPS_IMPLICITLY_DETACHED,                           NAS_MMC_ProcEpsTauRegFailCause10EpsImplicitlyDetached},

    {NAS_EMM_CAUSE_PLMN_NOT_ALLOW,                                    NAS_MMC_ProcEpsTauRegFailCause11PlmnNotAllow},
    {NAS_EMM_CAUSE_TA_NOT_ALLOW,                                      NAS_MMC_ProcEpsTauRegFailCause12TaNotAllow},
    {NAS_EMM_CAUSE_ROAM_NOT_ALLOW,                                    NAS_MMC_ProcEpsTauRegFailCause13RoamNotAllow},
    {NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN,                        NAS_MMC_ProcEpsTauRegFailCause14GprsNotAllowInThisPlmn},
    {NAS_EMM_CAUSE_NO_SUITABL_CELL,                                   NAS_MMC_ProcEpsTauRegFailCause15NoSuitableCell},
    {NAS_EMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED,                   NAS_MMC_ProcEpsTauRegFailCause40NoEpsBearerActived},
    {NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN,       NAS_MMC_ProcEpsTauRegFailCause35ReqServOptNotAuthorizedInThisPlmn},

    {NAS_MML_REG_FAIL_CAUSE_SEVERE_NETWORK_FAILURE,                   NAS_MMC_ProcEpsTauRegFailCause42SevereNetworkFailure},

    {NAS_MML_REG_FAIL_CAUSE_AUTH_REJ,                                 NAS_MMC_ProcEpsTauRegFailCause256AuthRej},
    {NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED,                            NAS_MMC_ProcEpsTauRegFailCause257AccessBarrd},
    {NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT,                            NAS_MMC_ProcEpsTauRegFailCause301TimerTimeOut},
    {NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE,                              NAS_MMC_ProcEpsTauRegFailCause401OtherCause},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN,                           NAS_MMC_ProcEpsTauRegFailCause403ForbiddenPlmn},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS,            NAS_MMC_ProcEpsTauRegFailCause404ForbiddenTaForRegPrvsSvs},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM,                    NAS_MMC_ProcEpsTauRegFailCause405ForbiddenLaForRoam},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS,                  NAS_MMC_ProcEpsTauRegFailCause406ForbiddenPlmnForGprs},
    {NAS_MML_REG_FAIL_CAUSE_MO_DETACH_FAILURE,                        NAS_MMC_ProcEpsTauRegFailCauseMoDetach},
    {NAS_MML_REG_FAIL_CAUSE_MT_DETACH_FAILURE,                        NAS_MMC_ProcEpsTauRegFailCauseMtDetach},
    {NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_FAIL,                   NAS_MMC_ProcEpsTauRegFailCauseT3402Running},
};



/* Eps 网侧detach被拒原因值的协议处理 */
NAS_MMC_EPS_DETACH_CAUSE_PROC_ENTITY                gastMmcProcEpsDetachCause[] =
{
    {NAS_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS,                               NAS_MMC_ProcEpsDetachCause2ImsiUnknowInHss},
    {NAS_EMM_CAUSE_ILLEGAL_UE,                                        NAS_MMC_ProcEpsDetachCause3IllegalMs},
    {NAS_EMM_CAUSE_ILLEGAL_ME,                                        NAS_MMC_ProcEpsDetachCause6IllegalMe},
    {NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW,                                NAS_MMC_ProcEpsDetachCause7EpsServNotAllow},
    {NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW,               NAS_MMC_ProcEpsDetachCause8GprsAndNonGprsNotAllow},
    {NAS_EMM_CAUSE_PLMN_NOT_ALLOW,                                    NAS_MMC_ProcEpsDetachCause11PlmnNotAllow},
    {NAS_EMM_CAUSE_TA_NOT_ALLOW,                                      NAS_MMC_ProcEpsDetachCause12TaNotAllow},
    {NAS_EMM_CAUSE_ROAM_NOT_ALLOW,                                    NAS_MMC_ProcEpsDetachCause13RoamNotAllow},
    {NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN,                        NAS_MMC_ProcEpsDetachCause14GprsNotAllowInThisPlmn},
    {NAS_EMM_CAUSE_NO_SUITABL_CELL,                                   NAS_MMC_ProcEpsDetachCause15NoSuitableCell},
};

/* Eps SR被拒原因值的协议处理 */
NAS_MMC_REG_FAIL_PROC_ENTITY            gastMmcProcEpsServiceRequestFailCause[] =
{
    {NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS,                                         NAS_MMC_ProcEpsServiceRequestFailCause3IllegalMs},
    {NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME,                                         NAS_MMC_ProcEpsServiceRequestFailCause6IllegalMe},
    {NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW,                                NAS_MMC_ProcEpsServiceRequestFailCause7EpsServNotAllow},

    {NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW,              NAS_MMC_ProcEpsServiceRequestFailCause8GprsAndNonGprsNotAllow},

    {NAS_EMM_CAUSE_MS_ID_CANNOT_BE_DERIVED_BY_NW,                               NAS_MMC_ProcEpsServiceRequestFailCause9MsIdCannotBeDerivedByNW},
    {NAS_EMM_CAUSE_EPS_IMPLICITLY_DETACHED,                                     NAS_MMC_ProcEpsServiceRequestFailCause10EpsImplicitlyDetached},

    {NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW,                                     NAS_MMC_ProcEpsServiceRequestFailCause11PlmnNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW,                                       NAS_MMC_ProcEpsServiceRequestFailCause12TaNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW,                                     NAS_MMC_ProcEpsServiceRequestFailCause13RoamNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN,                        NAS_MMC_ProcEpsServiceRequestFailCause14GprsNotAllowInThisPlmn},
    {NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL,                                    NAS_MMC_ProcEpsServiceRequestFailCause15NoSuitableCell},
    {NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN,                 NAS_MMC_ProcEpsServiceRequestFailCause35ReqServOptNotAuthorizedInThisPlmn},

    {NAS_EMM_CAUSE_CS_DOMAIN_NOT_AVAILABLE,                                     NAS_MMC_ProcEpsServiceRequestFailCause18CsDomainNotAvailable},
    {NAS_EMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG,                                 NAS_MMC_ProcEpsServiceRequestFailCause25NotAuthorizedForThisCsg},
    {NAS_EMM_CAUSE_CS_DOMAIN_TEMP_NOT_AVAILABLE,                                NAS_MMC_ProcEpsServiceRequestFailCause39CsDomainTempNotAvailable},

    {NAS_MML_REG_FAIL_CAUSE_NO_PDP_CONTEXT_ACT,                                 NAS_MMC_ProcEpsServiceRequestFailCause40NoEpsBearerActived},

    {NAS_MML_REG_FAIL_CAUSE_SEVERE_NETWORK_FAILURE,                             NAS_MMC_ProcEpsServiceRequestFailCause42SevereNetworkFailure},

    {NAS_MML_REG_FAIL_CAUSE_AUTH_REJ,                                           NAS_MMC_ProcEpsServiceRequestFailCause256AuthRej},
    {NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED,                                      NAS_MMC_ProcEpsServiceRequestFailCause257AccessBarrd},
};


#endif

NAS_MMC_ADDITIONAL_ACTION_PRIORITY_PAIR gastAdditionalActionPrioArr[] =
{
    {NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL,                           0},
    {NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION,                         1},
    {NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN,      2},
    {NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION,                         3},
    {NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT,                       4},
    {NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON,                         5},
    {NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED,                          6},
    {NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION,                7},
    {NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON,                        8},
    {NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL,                  9},
    {NAS_MMC_ADDITIONAL_ACTION_BUTT,                                   10}
};

NAS_MMC_LMM_ATTACH_CL_REG_STATUS_PRIORITY_PAIR gastLmmAttaClRegStatPrio[] =
{
    {MMC_LMM_CL_REG_STATUS_ATTACH_NOT_SEND,                            1},
    {MMC_LMM_CL_REG_STATUS_ATTACH_SEND_WAIT_CN_RSP,                    2},
    {MMC_LMM_CL_REG_STATUS_ATTACH_RCV_CN_REJ,                          3},
    {MMC_LMM_CL_REG_STATUS_ATTACH_RCV_CN_ACP,                          4},
    {MMC_LMM_CL_REG_STATUS_ATTACH_T3410_EXP,                           5},
    {MMC_LMM_CL_REG_STATUS_ATTACH_CMP_SEND,                            6},
    {MMC_LMM_CL_REG_STATUS_BUTT,                                       0}
};

/*****************************************************************************
  3 宏定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : NAS_MMC_GetRegRsltCtxAddr
 功能描述  : 更新当前的注册结果消息的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_REG_RSLT_CTX_STRU:返回注册结果结构体信息的地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月20日
    作    者   : w00167002
    修改内容   : 新增函数
*****************************************************************************/
NAS_MMC_REG_RSLT_CTX_STRU* NAS_MMC_GetRegRsltCtxAddr(VOS_VOID)
{
    return &(gstRegRsltCtx);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SaveRegRsltCtx
 功能描述  : 更新当前的注册结果消息类型和消息指针
 输入参数  : enRegRsltType:当前的注册结果消息类型
              pRegRsltCtx  :当前的注册结果消息指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月20日
    作    者   : w00167002
    修改内容   : 新增函数
  2.日    期   : 2012年3月5日
    作    者   : w00167002
    修改内容   : V7R1C50 CSFB调整:增加LMM 上报的service结果的保存
  3.日    期   : 2012年07月05日
    作    者   : s46746
    修改内容   : For CS/PS mode 1，记录EPS的AttemptCounter
  4.日    期   : 2014年5月6日
    作    者   : z00161729
    修改内容   : DTS2014050602850:l下联合注册eps成功，cs注册被#18拒绝，disable lte到gu下搜网注册成功，后指定搜l cs注册被#18拒绝的网络，l发起eps单域注册成功，mmc没有disable lte
*****************************************************************************/
VOS_VOID  NAS_MMC_SaveRegRsltCtx(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType,
    VOS_VOID                           *pRegRsltIndMsg
)
{
    NAS_MMC_REG_RSLT_CTX_STRU          *pstRegRsltCtx = VOS_NULL_PTR;
    pstRegRsltCtx   = NAS_MMC_GetRegRsltCtxAddr();

    /* 更新当前的注册结果消息类型 */
    pstRegRsltCtx->enRegRsltType = enRegRsltType;

    pstRegRsltCtx->ucIsLteRegTypeEpsOnly = VOS_FALSE;

    /* 根据消息类型来 */
    switch ( enRegRsltType )
    {
        case MM_MMC_CS_REG_RESULT_IND :
            pstRegRsltCtx->unRegRsltCtx.pstCsRegRsltInd = (MMMMC_CS_REG_RESULT_IND_STRU*)pRegRsltIndMsg;
            break;

        case GMM_MMC_PS_REG_RESULT_IND :
            pstRegRsltCtx->unRegRsltCtx.pstPsRegRsltInd = (GMMMMC_PS_REG_RESULT_IND_STRU*)pRegRsltIndMsg;
            break;

        case GMM_MMC_PS_SERVICE_RESULT_IND :
            pstRegRsltCtx->unRegRsltCtx.pstServiceRsltIndMsg = (GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU*)pRegRsltIndMsg;
            break;

        case GMM_MMC_PS_NETWORK_DETACH_IND :
            pstRegRsltCtx->unRegRsltCtx.pstDetachIndMsg      = (MMCGMM_NETWORK_DETACH_IND_STRU*)pRegRsltIndMsg;
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case LMM_MMC_ATTACH_IND :
            pstRegRsltCtx->unRegRsltCtx.pstLmmAttachIndMsg = (LMM_MMC_ATTACH_IND_STRU*)pRegRsltIndMsg;

            if (MMC_LMM_ATT_TYPE_EPS_ONLY == pstRegRsltCtx->unRegRsltCtx.pstLmmAttachIndMsg->ulReqType)
            {
                pstRegRsltCtx->ucIsLteRegTypeEpsOnly = VOS_TRUE;
            }

            NAS_MMC_SaveEpsAttachAttemptCounter((LMM_MMC_ATTACH_IND_STRU*)pRegRsltIndMsg);

            break;

        case LMM_MMC_TAU_RESULT_IND :
            pstRegRsltCtx->unRegRsltCtx.pstLmmTauIndMsg = (LMM_MMC_TAU_RESULT_IND_STRU*)pRegRsltIndMsg;

            if ((MMC_LMM_TA_UPDATING == pstRegRsltCtx->unRegRsltCtx.pstLmmTauIndMsg->ulReqType)
             || (MMC_LMM_PS_PERIODIC_UPDATING == pstRegRsltCtx->unRegRsltCtx.pstLmmTauIndMsg->ulReqType))
            {
                pstRegRsltCtx->ucIsLteRegTypeEpsOnly = VOS_TRUE;
            }

            NAS_MMC_SaveEpsTauAttemptCounter((LMM_MMC_TAU_RESULT_IND_STRU*)pRegRsltIndMsg);

            break;

        case LMM_MMC_DETACH_IND :
            pstRegRsltCtx->unRegRsltCtx.pstLmmDetachMsg = (LMM_MMC_DETACH_IND_STRU*)pRegRsltIndMsg;
            break;

        case LMM_MMC_SERVICE_RESULT_IND :
            pstRegRsltCtx->unRegRsltCtx.pstLmmServiceIndMsg = (LMM_MMC_SERVICE_RESULT_IND_STRU*)pRegRsltIndMsg;
            break;


#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SaveRegRsltCtx: UNEXPECTED MSG TYPE!");
            break;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetRegRsltType
 功能描述  : 更新当前的注册结果消息类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8:返回注册结果消息的类型
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月20日
    作    者   : w00167002
    修改内容   : 新增函数
*****************************************************************************/
NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8 NAS_MMC_GetRegRsltType(VOS_VOID)
{
    return gstRegRsltCtx.enRegRsltType;
}

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-1-4, begin */

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-1-4, end */


/*****************************************************************************
 函 数 名  : NAS_MMC_GetRegRsltAttemptCounter
 功能描述  : 取得注册结果消息中的AttemptCounter的值
 输入参数  : enRegRsltType:当前的注册结果消息类型
 输出参数  : 无
 返 回 值  : 返回AttemptCounter的值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月20日
    作    者   : w00167002
    修改内容   : 新增函数
  2.日    期   : 2012年07月05日
    作    者   : s46746
    修改内容   : For CS/PS mode 1，记录EPS的AttemptCounter
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetRegRsltAttemptCounter(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType
)
{
    NAS_MMC_REG_RSLT_CTX_STRU          *pstRegRsltCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulAttempCounter;

    /* Attempt Counter 初始化为0 */
    ulAttempCounter = 0;
    pstRegRsltCtx   = NAS_MMC_GetRegRsltCtxAddr();

    switch ( enRegRsltType )
    {
        case MM_MMC_CS_REG_RESULT_IND :

            /* 获取CS注册结果消息中的Attempt Counter的值 */
            ulAttempCounter = pstRegRsltCtx->unRegRsltCtx.pstCsRegRsltInd->ulLuAttemptCnt;
            break;

        case GMM_MMC_PS_REG_RESULT_IND :

            /* 获取PS注册结果消息中的Attempt Counter的值 */
            ulAttempCounter = pstRegRsltCtx->unRegRsltCtx.pstPsRegRsltInd->ulRegCounter;
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case LMM_MMC_ATTACH_IND :

            /* 获取lmm ATTACH注册结果消息中的Attempt Counter的值 */
            ulAttempCounter = pstRegRsltCtx->ucEpsAttemptCounter;

            break;

        case LMM_MMC_TAU_RESULT_IND :

            /* 获取lmm TAU注册结果消息中的Attempt Counter的值 */
            ulAttempCounter = pstRegRsltCtx->ucEpsAttemptCounter;

            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRegRsltAttemptCounter: UNEXPECTED MSG TYPE!");
            break;
    }

    return ulAttempCounter;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailImsiUnnownInHlr
 功能描述  : Cs Cause2的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年10月15日
    作    者   : s00217060
    修改内容   : for DTS2012082308686:Cs注册失败原因值为2,3,6,256时，需要重新Enable Lte
  3.日    期   : 2013年01月23日
    作    者   : s00217060
    修改内容   : 问题单: DTS2013012106172,Enable Lte时停止定时器TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
  4.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  5.日    期   : 2014年4月29日
    作    者   : s00261364
    修改内容   : ecall项目修改服务状态上报
  6.日    期   : 2015年1月5日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause2ImsiUnknownInHlr(VOS_VOID)
{
#if   (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulDisablteRoamFlg;

    ulDisablteRoamFlg = NAS_MML_GetDisableLteRoamFlg();
#endif

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);

#if   (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MMC_IsNeedEnableLte_CsRegFailCause2ImsiUnknownInHlr())
    {
        /* 如果由于禁止LTE国际漫游导致的disable LTE，再未回到国内之前此时也不通知enable LTE */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
         && (VOS_FALSE == ulDisablteRoamFlg))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* 更新disable LTE能力标记 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }
#endif

    return NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause3IllegalMs
 功能描述  : Cs Cause3的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause3IllegalMs(VOS_VOID)
{
    /* 按原因值2进行处理 */
    return NAS_MMC_ProcCsRegFailCause2ImsiUnknownInHlr();
}
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause6IllegalMe
 功能描述  : Cs Cause6的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause6IllegalMe(VOS_VOID)
{
    /* 按原因值2进行处理 */
    return NAS_MMC_ProcCsRegFailCause2ImsiUnknownInHlr();
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause11PlmnNotAllow
 功能描述  : Cs Cause11的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV修改合并原NAS_MMC_HPLMN_REG_REJ_STRU和NAS_MMC_PLMN_REG_INFO_STRU
  3.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目
  4.日    期   : 2012年11月29日
    作    者   : W00176964
    修改内容   : DTS2012112902395,BVT测试,hplmn被拒#11后后续需要继续注册
  5.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  6.日    期   : 2014年4月18日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:增加服务状态上报的处理
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause11PlmnNotAllow(VOS_VOID)
{
    VOS_UINT8                           ucRejDomain;
    NAS_MML_MS_CFG_INFO_STRU           *pstMsCfg;
    NAS_MML_PLMN_ID_STRU               *pstCurPlmnId;

    pstCurPlmnId = NAS_MML_GetCurrCampPlmnId();

    /* 添加禁止网络信息,有更新时，向Usim更新文件 */
    if (VOS_TRUE == NAS_MML_AddForbPlmn(pstCurPlmnId))
    {
        NAS_MMC_SndUsimUpdateForbPlmnReq();
    }

    /* Added by s00261364 for V3R360_eCall项目, 2014-4-18, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-18, end */

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    if ( VOS_FALSE == NAS_MML_GetHplmnRegisterCtrlFlg())
    {
        /* 非E5版本才做如下处理，E5版本要求能在HPLMN上反复发起注册 */

        if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(NAS_MML_GetCurrCampPlmnId()))
        {
            /* 根据注册结果更新注册信息表 */
            NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(),
                          NAS_MMC_REG_DOMAIN_CS, NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW);

            pstMsCfg = NAS_MML_GetMsCfgInfo();

            if ((NAS_MML_MS_MODE_PS_CS == pstMsCfg->stMsSysCfgInfo.enMsMode))
            {
                NAS_MMC_GetHplmnRejDomainInfo(&ucRejDomain);

                if (NAS_MMC_REG_DOMAIN_PS_CS != ucRejDomain)
                {
                    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

                    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
                }
            }
        }
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

}
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause12LaNotAllow
 功能描述  : Cs Cause12的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  3.日    期   : 2014年04月30日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:更新服务状态

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause12LaNotAllow(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8          enPsAdditionalAction;

    /*添加禁止网络信息*/
    NAS_MML_AddForbRegLa(NAS_MML_GetCurrCampLai());

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_FORBID_LA_TIMER, TI_NAS_MMC_FORBID_LA_TIMER_LEN);

    /* Added by s00261364 for V3R360_eCall项目, 2014-4-30, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE_REGION);
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-30, end */

    /* 有业务时，需要触发一次搜网:由于状态已更新为registered，再搜网时会跳过该RAT下的这个网络 */
    if (VOS_TRUE == NAS_MMC_IsNeedLauRejTrigPlmnSearch(NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    enPsAdditionalAction = NAS_MMC_GetPsAdditionalAction();
    if ((NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL != enPsAdditionalAction)
     && (NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION != enPsAdditionalAction)
     && (NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN != enPsAdditionalAction))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    else
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }

    return NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause13RoamNotAllow
 功能描述  : Cs Cause13的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : l00130025
   修改内容   : 新生成函数
 2.日    期   : 2011年11月12日
   作    者   : w00167002
   修改内容   : DTS2011110907180:NAS_MML_AddForbRoamLa函数调整的修改
 3.日    期   : 2014年04月30日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:增加服务状态上报处理

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause13RoamNotAllow(VOS_VOID)
{
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU                stForbRoamLaInfo;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                        *pstForbPlmnInfo = VOS_NULL_PTR;

    /* 非用户指定搜网，从全局变量中获取FORBIDEN ROAMING LAS信息 */
    pstForbPlmnInfo                  = NAS_MML_GetForbidPlmnInfo();
    stForbRoamLaInfo.ucForbRoamLaNum = pstForbPlmnInfo->ucForbRoamLaNum;
    PS_MEM_CPY( stForbRoamLaInfo.astForbRomLaList,
                pstForbPlmnInfo->astForbRomLaList,
                sizeof(pstForbPlmnInfo->astForbRomLaList) );

    /* 添加禁止网络信息到全局变量的禁止漫游LA变量里去 */
    NAS_MML_AddForbRoamLa( NAS_MML_GetCurrCampLai(),
                           &stForbRoamLaInfo );
    pstForbPlmnInfo->ucForbRoamLaNum = stForbRoamLaInfo.ucForbRoamLaNum;
    PS_MEM_CPY( pstForbPlmnInfo->astForbRomLaList,
                stForbRoamLaInfo.astForbRomLaList,
                sizeof(pstForbPlmnInfo->astForbRomLaList));

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_FORBID_LA_TIMER, TI_NAS_MMC_FORBID_LA_TIMER_LEN);

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-30, begin */

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-30, end */
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-30, begin */
    /* 上报对应的CS服务状态MSCC_MMC_SERVICE_STATUS_NO_SERVICE */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-30, end */

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause15NoSuitableCell
 功能描述  : Cs Cause15的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : l00130025
   修改内容   : 新生成函数
 2.日    期   : 2011年11月12日
   作    者   : w00167002
   修改内容   : DTS2011110907180:当前若为选网状态机，则添加禁止网络信息
                 到选网状态机的禁止漫游LA变量里去
 3.日    期   : 2014年4月8日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:更新CSPS服务状态
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause15NoSuitableCell(VOS_VOID)
{

    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU                stForbRoamLaInfo;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                        *pstForbPlmnInfo = VOS_NULL_PTR;

    /* 非用户指定搜网，从全局变量中获取FORBIDEN ROAMING LAS信息 */
    pstForbPlmnInfo                  = NAS_MML_GetForbidPlmnInfo();
    stForbRoamLaInfo.ucForbRoamLaNum = pstForbPlmnInfo->ucForbRoamLaNum;
    PS_MEM_CPY( stForbRoamLaInfo.astForbRomLaList,
                pstForbPlmnInfo->astForbRomLaList,
                sizeof(pstForbPlmnInfo->astForbRomLaList) );

    /* 添加禁止网络信息到全局变量的禁止漫游LA变量里去 */
    NAS_MML_AddForbRoamLa( NAS_MML_GetCurrCampLai(), &stForbRoamLaInfo );
    pstForbPlmnInfo->ucForbRoamLaNum = stForbRoamLaInfo.ucForbRoamLaNum;
    PS_MEM_CPY( pstForbPlmnInfo->astForbRomLaList,
                stForbRoamLaInfo.astForbRomLaList,
                sizeof(pstForbPlmnInfo->astForbRomLaList));


    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_FORBID_LA_TIMER, TI_NAS_MMC_FORBID_LA_TIMER_LEN);

    /* 更新服务状态 */
    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-10, begin */

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-10, end */

    /* Added by s00261364 for V3R360_eCall项目, 2014-4-30, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-30, end */

    return NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause17NetWorkFailure
 功能描述  : Cs 17#原因值的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月11日
   作    者   : w00166186
   修改内容   : AT&T&DCM项目
 2.日    期   : 2014年4月29日
   作    者   : s00261364
   修改内容   : ecall项目修改服务状态上报
 3.日    期   : 2014年5月21日
    作    者   : w00167002
    修改内容   : DTS2014051602857:在SOR打开时候，如果CS注册失败达到4次，则等周期
                搜网定时器超时发起LIST搜网，如果当前仅有原有网络，则发起LAU,否则
                触发MM发起LAU;如果LIST搜后，发现有其他网络，则发起其他网络的搜网注册。
                手动选网时候，返回LIMIT CAMP ON,不再发起选网。

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause17NetWorkFailure(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8    enAction;
    VOS_UINT8                               ucRegFailMaxCnt;
    VOS_UINT32                              ulAttemptCnt;
    VOS_UINT8                               ulLaiSameFlg;
    NAS_MML_CAMP_PLMN_INFO_STRU            *pstCampInfo     = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                       *pstLastSuccLai  = VOS_NULL_PTR;

    pstCampInfo    = NAS_MML_GetCurrCampPlmnInfo();
    pstLastSuccLai = NAS_MML_GetCsLastSuccLai();

    enAction        = NAS_MMC_ADDITIONAL_ACTION_BUTT;

    ucRegFailMaxCnt = NAS_MML_MAX_CS_REG_FAIL_CNT;

    /* 若roaming broker特性开启，则使用ROAMING BROKER保存的失败个数，当此特性
       未打开时，使用的值为NAS_MML_MAX_CS_REG_FAIL_CNT */
    if ( VOS_TRUE == NAS_MML_GetRoamBrokerActiveFlag() )
    {
        ucRegFailMaxCnt = NAS_MML_GetRoamBrokerRegisterFailCnt();
    }

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(MM_MMC_CS_REG_RESULT_IND);

    /* 定制开关打开 */
    if (VOS_TRUE == NAS_MML_GetRegFailNetWorkFailureCustomFlag())
    {
        ulLaiSameFlg = NAS_MML_CompareLai(&(pstCampInfo->stLai), pstLastSuccLai);

        /* 当前驻留的LAI不是上次成功驻留的LAI，CS UPDATE状态不是U1，或者ATTEMPCNT达到最大值需要触发搜网 */
        if ((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED != NAS_MML_GetCsUpdateStatus())
         || (VOS_FALSE == ulLaiSameFlg)
         || (ulAttemptCnt >= ucRegFailMaxCnt))
        {
            /* Added by s00261364 for V3R360_eCall项目, 2014-4-30, begin */
            NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
            /* Added by s00261364 for V3R360_eCall项目, 2014-4-30, end */

            return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        }
    }

    if (ulAttemptCnt < ucRegFailMaxCnt)
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcCsRegFailCause17AttemptCounterMaxTimes();
    }

    return enAction;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause95SemanticallyIncorrectMsg
 功能描述  : Cs Cause95的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月12日
   作    者   : w00167002
   修改内容   : DTS2011122006209:拒绝原因值95的处理

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause95SemanticallyIncorrectMsg(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    /* 取得当前的注册结果类型  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_CS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause96InvalidMandatoryInf
 功能描述  : Cs Cause96的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月12日
   作    者   : w00167002
   修改内容   : DTS2011122006209:拒绝原因值96的处理

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause96InvalidMandatoryInf(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;

    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    /* 取得当前的注册结果类型  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_CS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause97MsgNonExistNotImplement
 功能描述  : Cs Cause97的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月12日
   作    者   : w00167002
   修改内容   : DTS2011122006209:拒绝原因值97的处理

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause97MsgNonExistNotImplement(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    /* 取得当前的注册结果类型  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_CS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause99IeNonExistNotImplement
 功能描述  : Cs Cause99的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月12日
   作    者   : w00167002
   修改内容   : DTS2011122006209:拒绝原因值99的处理

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause99IeNonExistNotImplement(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    /* 取得当前的注册结果类型  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_CS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause111ProtocolError
 功能描述  : Cs Cause111的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月12日
   作    者   : w00167002
   修改内容   : DTS2011122006209:拒绝原因值111的处理

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause111ProtocolError(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    /* 取得当前的注册结果类型  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_CS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}




/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause256AuthRej
 功能描述  : Cs Reg Auth rej的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年2月3日
    作    者   : w00167002
    修改内容   : DTS2011122704039:在注册失败原因值的函数命名中增加原因值，
                  保持函数命名的一致性。
  3.日    期   : 2012年10月15日
    作    者   : s00217060
    修改内容   : for DTS2012082308686:Cs注册失败原因值为2,3,6,256时，需要重新Enable Lte
  4.日    期   : 2013年01月23日
    作    者   : s00217060
    修改内容   : 问题单: DTS2013012106172,Enable Lte时停止定时器TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
  5.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  6.日    期   : 2014年4月29日
    作    者   : s00261364
    修改内容   : ecall项目修改服务状态上报
  7.日    期   : 2015年1月5日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause256AuthRej(VOS_VOID)
{
#if   (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulDisablteRoamFlg;

    ulDisablteRoamFlg = NAS_MML_GetDisableLteRoamFlg();
#endif

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);

#if   (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MMC_IsNeedEnableLte_CsRegFailCause256AuthRej())
    {
        /* 如果由于禁止LTE国际漫游导致的disable LTE，再未回到国内之前此时也不通知enable LTE */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
         && (VOS_FALSE == ulDisablteRoamFlg))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* 更新disable LTE能力标记 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }
#endif

    return NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause257AccessBarrd
 功能描述  : Cs AccessBarrd的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数

  2.日    期   : 2012年2月3日
    作    者   : w00167002
    修改内容   : DTS2011122704039:在注册失败原因值的函数命名中增加原因值，
                  保持函数命名的一致性。
 3.日    期   : 2012年3月10日
   作    者   : w00166186
   修改内容   : CSFB&PPAC&ETWS&ISR 开发
 4.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 5.日    期   : 2013年10月15日
   作    者   : s00190137
   修改内容   : 特性开关打开且非HPLMN/RPLMN接入禁止时需要触发PLMN搜网
 6.日    期   : 2014年04月8日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc
  7.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : DTS2015082002854: 漫游标记不准
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause257AccessBarrd(VOS_VOID)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;
    NAS_MML_CAMP_PLMN_INFO_STRU                *pstCampInfo     = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                           *pstLastSuccLai  = VOS_NULL_PTR;

    enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
    pstCampInfo      = NAS_MML_GetCurrCampPlmnInfo();
    pstLastSuccLai   = NAS_MML_GetCsLastSuccLai();

    /* 当前LAI和上次注册成功LAI相同，且更新状态为U1 */
    if ((VOS_TRUE == NAS_MML_CompareLai(&(pstCampInfo->stLai), pstLastSuccLai))
     && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus)
     && (MM_STATUS_ATTACHED == (NAS_MMC_GetMmCtx())->ucCsAttachState))
    {
        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_NORMAL_SERVICE);
    }
    else
    {
        /* Added by s00261364 for V3R360_eCall项目, 2014-4-4, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
        /* Added by s00261364 for V3R360_eCall项目, 2014-4-4, end */
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }

    /*特性开关打开且非HPLMN/RPLMN接入禁止时需要触发PLMN搜网*/
    if (VOS_TRUE == NAS_MMC_IsAccBarPlmnSearch())
    {
        return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    }
    else
    {
        return NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED;
    }

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause301TimerTimeOut
 功能描述  : Cs Cause:NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT 的处理
 输入参数  :
             VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月18日
   作    者   : w00167002
   修改内容   : 新生成函数。
 2.日    期   : 2012年6月11日
   作    者   : w00166186
   修改内容   : AT&T&DCM项目
 3.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 4.日    期   : 2014年04月30日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause301TimerTimeOut(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;


    /* 取得当前的注册结果类型  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_CS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_GetSingleDomainFailAction(NAS_MML_REG_DOMAIN_CS, NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT);

        if (NAS_MMC_ADDITIONAL_ACTION_BUTT != enAction)
        {
            enPrioAdditionalAction = NAS_MMC_GetPsAdditionalAction();
            enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enAction, enPrioAdditionalAction);

            /* Modified by s00261364 for V3R360_eCall项目, 2014-4-30, begin */
            NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);

            if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
            {
                NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            }
            else
            {
                NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
            }
            /* Modified by s00261364 for V3R360_eCall项目, 2014-4-30, end */


            return enAction;
        }
        else
        {
            enAction = NAS_MMC_ProcCsRegFailAttemptCounterMaxTimes();
        }
    }

    return enAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause302RrConnEstFail
 功能描述  : Cs Cause:NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL 的处理
 输入参数  :
             VOS_UINT32                          ulAttemptCnt
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月18日
   作    者   : w00167002
   修改内容   : 新生成函数。
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause302RrConnEstFail(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    /* 取得当前的注册结果类型  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_CS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause303RrConnFail
 功能描述  : Cs Cause:NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL的处理
 输入参数  : VOS_UINT32                          ulAttemptCnt
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月18日
   作    者   : w00167002
   修改内容   : 新生成函数。
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause303RrConnFail(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    /* 取得当前的注册结果类型  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_CS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause401OtherCause
 功能描述  : Cs Other Cause的处理
 输入参数  :
             VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : l00130025
   修改内容   : 新生成函数
                 1)  attemptCount < MaxCount时，返回NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT
                 2)  attemptCount >= MaxCount时，无定制需求，要等待另外一个域的注册结果,返回NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION
                 3)  attemptCount >= MaxCount时，有对MaxCount的定制（Roaming Broker,cause<111）或单域的搜网请求（VDF的 Steer of  roaming或DT的定制需求），
                     返回NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION

 2.日    期   : 2011年11月18日
   作    者   : w00167002
   修改内容   : DTS2011111603330:若当前的LAI发生改变，即使失败次数未达到
                最大次数,也更新为限制服务状态。

 3.日    期   : 2011年11月24日
   作    者   : w00167002
   修改内容   : DTS20111112105560:roamingbroker 特性开启，将最大失败次数设置为1，
                建链接异常释放一次就发起了搜网，实际应该是注册失败原因值小于
                111时，才发起搜网。

 4.日    期   : 2012年1月3日
   作    者   : w00167002
   修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网.
                 NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE时，返回NAS_MMC_ADDITIONAL_ACTION_BUTT
                 ,表示MMC不需要写入当前CS的ADDITIONAL ACTION值。
 5.日    期   : 2012年2月3日
   作    者   : w00167002
   修改内容   : DTS2011122704039:在注册失败原因值的函数命名中增加原因值，
                 保持函数命名的一致性。
 6.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 7.日    期   : 2014年04月8日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause401OtherCause(VOS_VOID)
{
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* 取得当前的注册结果类型  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt >= NAS_MML_MAX_CS_REG_FAIL_CNT)
    {
        /* 获取CS和PS的additon action，取高优先级的判断是否需要搜网，
           如果不需要更新CS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        enPsAdditionalAction   = NAS_MMC_GetPsAdditionalAction();
        enCsAdditionalAction   = NAS_MMC_GetCsAdditionalAction();

        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-30, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);

        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }
        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-30, end */
    }

    /* 返回NAS_MMC_ADDITIONAL_ACTION_BUTT，表示无效的AdditionalAction值 */
    return NAS_MMC_ADDITIONAL_ACTION_BUTT;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause402MsCfgDomainNotSupport
 功能描述  : 假流程:Cs/only,当前配置CS only
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数

  2.日    期   : 2012年1月13日
    作    者   : w00167002
    修改内容   : DTS2011122006209:当前在ONPLMN时，若收到结果为CS域不支持，
                  则需要判断1)PS域是否是LIMIT_CAMP_ON 2)AVAILABLE定时器未启动
                             3)PS域准许发起注册,则MMC需要发起搜网
                  对应场景举例:
                  在选网状态机中当前驻留的网络一个域被拒12，一个域#14后，
                  在ON PLMN状态受限驻留，此时用户将注册被拒#12的域DETACH后，
                  由于CS域此时是LIMITED_CAMP_ON，故不发起搜网，而实际需要发起搜网.
  2.日    期   : 2012年2月3日
    作    者   : w00167002
    修改内容   : DTS2011122704039:在注册失败原因值的函数命名中增加原因值，
                  保持函数命名的一致性。

  4.日    期   : 2012年4月18日
    作    者   : z40661
    修改内容   : DTS2012032204099,CC模式后，设置CG模式，MMC发起了搜网
  5.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
  6.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  7.日    期   : 2013年11月30日
    作    者   : z00161729
    修改内容   : DTS2013112809149:9230 nv项设置禁止接入技术为w和g，手动搜网模式驻留g的23002成功，
                syscfg设置w only，anycell驻留24005，会反复触发w下anycell搜网
  8.日    期   : 2014年04月8日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause402MsCfgDomainNotSupport(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_TIMER_STATUS_ENUM_U8                            enAvailableTimerStatus;
    VOS_UINT8                                               ucPsAttachAllow;
    VOS_UINT32                                              ulRlst;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo = VOS_NULL_PTR;


    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    enFsmId                = NAS_MMC_GetCurrFsmId();
    if (NAS_FSM_BUTT <= enFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    enAvailableTimerStatus = NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER);
    ucPsAttachAllow        = NAS_MML_GetPsAttachAllowFlg();

    /* 当前在ONPLMN,PLMN_LIST时，若收到结果为CS域不支持，则需要判断此时是否需要发起搜网，
       1)PS域是LIMIT_CAMP_ON 2)AVAILABLE定时器未启动 3)PS域准许发起注册,则MMC需要发起搜网
    */
    if ( (NAS_MMC_FSM_L1_MAIN   == enFsmId)
      || (NAS_MMC_FSM_PLMN_LIST == enFsmId) )
    {
        if (VOS_FALSE == NAS_MMC_IsNeedPlmnSearch_RegLocalFailCause())
        {
            return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
        }

        pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();
        /* 在forbid plmn for gprs列表中 */
        ulRlst = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(NAS_MML_GetCurrCampPlmnId(),
                                              pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                              pstForbidPlmnInfo->astForbGprsPlmnList);
        if ( (VOS_TRUE                  == ucPsAttachAllow)
          && (VOS_TRUE                  == ulRlst)
          && (NAS_MMC_TIMER_STATUS_STOP == enAvailableTimerStatus) )
        {
            return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
        }
    }

    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedPlmnSearch_RegLocalFailCause
 功能描述  : 判断未和网络交互注册失败原因值403-409/access bar是否需要搜网
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要搜网
             VOS_FALSE - 无需搜网
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月30日
    作    者   : z00161729
    修改内容   : DTS2013112809149:9230 nv项设置禁止接入技术为w和g，手动搜网模式驻留g的23002成功，
                 syscfg设置w only，anycell驻留24005，会反复触发w下anycell搜网
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedPlmnSearch_RegLocalFailCause( VOS_VOID )
{
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmn     = VOS_NULL_PTR;
    VOS_UINT32                                              ulGsmOnlyFlg;
    VOS_UINT32                                              ulGsmForbFlg;
    VOS_UINT32                                              ulUserSpecPlmnForbPlmnFlag;

    ulGsmOnlyFlg                = NAS_MML_IsGsmOnlyMode(NAS_MML_GetMsPrioRatList());
    ulGsmForbFlg                = NAS_MML_GetGsmForbidFlg();
    pstUserSpecPlmn             = NAS_MMC_GetUserSpecPlmnId();

    /* 1.USIM卡禁止GSM并且用户设置GSM only，返回VOS_FALSE,无需搜网 */
    if ((VOS_TRUE == ulGsmForbFlg)
     && (VOS_TRUE == ulGsmOnlyFlg) )
    {
        return VOS_FALSE;
    }

    /* 2.如果UE配置的网络制式都被禁止，无需搜网 */
    if (VOS_TRUE == NAS_MML_IsAllMsRatInForbiddenList())
    {
        return VOS_FALSE;
    }

    /* 3.卡无效，无需搜网 */
    if ( VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        return VOS_FALSE;
    }

    /* 当前为手动模式且用户指定的网络在禁止网络列表中，无需搜网 */
    ulUserSpecPlmnForbPlmnFlag    = NAS_MML_IsPlmnIdInForbidPlmnList( &(pstUserSpecPlmn->stPlmnId) );
    if ( (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
       && (VOS_TRUE == ulUserSpecPlmnForbPlmnFlag))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCauseForbiddenPlmn
 功能描述  : 假流程:Cs 11号原因值被拒或当前非手动指定网络
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月12日
    作    者   : l00130025
    修改内容   : 新生成函数

  2.日    期   : 2012年1月4日
    作    者   : w00167002
    修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网.
                  在主框架中L1MAIN/PLMN LIST中判断当前原因值为非UE主动发起注册
                  原因值，则更新为NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON。现将
                  此判断放到各个子函数中来判断。
  3.日    期   : 2012年2月3日
    作    者   : w00167002
    修改内容   : DTS2011122704039:在注册失败原因值的函数命名中增加原因值，
                  保持函数命名的一致性。
  4.日    期   : 2013年11月30日
    作    者   : z00161729
    修改内容   : DTS2013112809149:9230 nv项设置禁止接入技术为w和g，手动搜网模式驻留g的23002成功，syscfg设置w only，anycell驻留24005，会反复触发w下anycell搜网
  5.日    期   : 2014年04月8日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause403ForbiddenPlmn(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_TIMER_STATUS_ENUM_U8                            enAvailableTimerStatus;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmn     = VOS_NULL_PTR;
    VOS_UINT32                                              ulUserSpecPlmnFlag;
    NAS_MML_PLMN_ID_STRU                                   *pstCurPlmnId        = VOS_NULL_PTR;

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    enAvailableTimerStatus = NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER);

    enFsmId = NAS_MMC_GetCurrFsmId();
    switch ( enFsmId )
    {
        case NAS_MMC_FSM_L1_MAIN :
        case NAS_MMC_FSM_PLMN_LIST :

            if (VOS_FALSE == NAS_MMC_IsNeedPlmnSearch_RegLocalFailCause())
            {
                return NAS_MMC_ADDITIONAL_ACTION_BUTT;
            }

            /* 默认返回NAS_MMC_ADDITIONAL_ACTION_BUTT，表示无效的AdditionalAction值 */
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;

            /* 在如下场景需要搜网:手动模式下，当前Plmn不是用户指定的PLMN,且当前PLMN不在EPlmn列表里，
               Available定时器未启动，则认为当前plmn 已经失效了，需要进行搜网 */

            /* 手动模式判断当前网络是否是用户指定的网络 */
            pstCurPlmnId       = NAS_MML_GetCurrCampPlmnId();
            pstUserSpecPlmn    = NAS_MMC_GetUserSpecPlmnId();
            ulUserSpecPlmnFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurPlmnId,
                                                        &(pstUserSpecPlmn->stPlmnId));

            /* 手动模式下，当前Plmn不是用户指定的PLMN,且当前PLMN不在EPlmn列表里，
               则认为当前plmn 已经失效了，Available 定时器未启动，需要进行搜网 */
            if ( (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
              && (VOS_FALSE                          == ulUserSpecPlmnFlag)
              && (NAS_MMC_TIMER_STATUS_STOP          == enAvailableTimerStatus) )
            {
                enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
            }

            break;

        /* 需要触发搜网 */
        default:
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
            break;
    }

    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
    /* 只有在下一步需要搜网时，才报状态2上去；不需要搜网时报状态0 */
    if (NAS_MMC_ADDITIONAL_ACTION_BUTT == enAdditionalAction)
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    else
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    return enAdditionalAction;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause404ForbiddenLaForRegPrvsSvs
 功能描述  : Cs Cause404:NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月3日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause404ForbiddenLaForRegPrvsSvs(VOS_VOID)
{
    /* 跟注册被拒原因#12的处理一样 */
    return NAS_MMC_ProcCsRegFailCause12LaNotAllow();
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause405ForbiddenLaForRoam
 功能描述  : 假流程:Cs 13或15号原因值被拒
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月12日
    作    者   : l00130025
    修改内容   : 新生成函数

  2.日    期   : 2011年12月21日
    作    者   : w00167002
    修改内容   : DTS2011102100710:注册被拒原因值#13，#15时，都会加入FORB ROAM
                  LA信息列表里，增加被拒原因值的存储，用以区分在LAI上拒绝的原因
                 值。MMC在收到MM/GMM上报拒绝原因值#13,#15的假流程消息时，MMC触发
                 不同的搜网策略。
  3.日    期   : 2012年1月4日
    作    者   : w00167002
    修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网.
                     在主框架中L1MAIN/PLMN LIST中判断当前原因值为非UE主动发起注册
                     原因值，则更新为NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON。现将
                     此判断放到各个子函数中来判断。
  4.日    期   : 2012年2月3日
    作    者   : w00167002
    修改内容   : DTS2011122704039:在注册失败原因值的函数命名中增加原因值，
                  保持函数命名的一致性。
  5.日    期   : 2014年04月8日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause405ForbiddenLaForRoam(VOS_VOID)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause;                              /* 存储注册区CS域被拒信息 */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause;                              /* 存储注册区PS域被拒信息 */

    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */


    /* 当前在ONPLMN或者PLMN LIST状态机，此时处于限制驻留态，在未跟网侧真实发生交互的情况下，
       不更新当前AdditionalAction值 */
    enFsmId = NAS_MMC_GetCurrFsmId();
    if ( (NAS_MMC_FSM_L1_MAIN == enFsmId)
      || (NAS_MMC_FSM_PLMN_LIST == enFsmId) )
    {
        /* 返回NAS_MMC_ADDITIONAL_ACTION_BUTT，表示无效的AdditionalAction值,MMC
           不更新无效AdditionalAction值 */
        return NAS_MMC_ADDITIONAL_ACTION_BUTT;
    }


    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    /* 当前不在在ONPLMN或者PLMN LIST状态机，需处理拒绝原因值，返回不同的搜网策略 */

    /* 原因值初始化为#13,若发生异常，则进行常规的搜网 */
    enCsCause = NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW;
    enPsCause = NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW;

    NAS_MMC_GetDomainRegStatusInRegInfoList( NAS_MML_GetCurrCampPlmnId(),
                                             NAS_MML_GetCurrNetRatType(),
                                             &enCsCause,
                                             &enPsCause );

    /* 若CS域或者PS域有一个域的原因值为#13,则进行常规的搜网 */
    if ( (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW == enCsCause)
      || (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW == enPsCause))
    {
        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    /* 否则按照拒绝原因值#15的搜网策略进行搜网 */
    return NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;


}
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause407SimInvalid
 功能描述  : 假流程:当前CS域卡无效
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月5日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年2月3日
    作    者   : w00167002
    修改内容   : DTS2011122704039:在注册失败原因值的函数命名中增加原因值，
                  保持函数命名的一致性。
  3.日    期   : 2012年3月1日
    作    者   : z40661
    修改内容   : DTS2012022401628：多次切换无声音
  4.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
                  保持函数命名的一致性。
  5.日    期   : 2014年04月8日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause407SimInvalid(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    /* 更新服务状态 */
    NAS_MMC_SetCsServiceStatus(NAS_MMC_LIMITED_SERVICE);

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    /* 卡存在表示肯定是注册被拒过 */
    if (VOS_TRUE == NAS_MML_GetSimPresentStatus())
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    }
    else
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }


    enFsmId = NAS_MMC_GetCurrFsmId();
    if ( (NAS_MMC_FSM_L1_MAIN == enFsmId)
      || (NAS_MMC_FSM_PLMN_LIST == enFsmId) )
    {
        /* 返回NAS_MMC_ADDITIONAL_ACTION_BUTT，表示无效的AdditionalAction值,MMC
           不更新无效AdditionalAction值 */
        return NAS_MMC_ADDITIONAL_ACTION_BUTT;
    }

    return NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause408NetDetachImsi
 功能描述  : Cs注册失败原因:NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年01月16日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 3.日    期   : 2014年04月8日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause408NetDetachImsi(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* Added by s00261364 for V3R360_eCall项目, 2014-4-8, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-8, end */

    /* 获取CSPS addition,如果不需要发起搜网则更新CS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    enPsAdditionalAction   = NAS_MMC_GetPsAdditionalAction();
    enCsAdditionalAction   = NAS_MMC_GetCsAdditionalAction();

    enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);
    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
    else
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    /* 返回NAS_MMC_ADDITIONAL_ACTION_BUTT，表示无效的AdditionalAction值,
       MMC不更新无效AdditionalAction值*/
    return NAS_MMC_ADDITIONAL_ACTION_BUTT;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause409ServingCellDomainNotSupport
 功能描述  : 假流程:当前小区不支持CS域
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数

  2.日    期   : 2012年1月4日
    作    者   : w00167002
    修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网.
                  在主框架中L1MAIN/PLMN LIST中判断当前原因值为非UE主动发起注册
                  原因值，则更新为NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON。现将
                  此判断放到各个子函数中来判断。
  3.日    期   : 2012年2月3日
    作    者   : w00167002
    修改内容   : DTS2011122704039:在注册失败原因值的函数命名中增加原因值，
                  保持函数命名的一致性。
  4.日    期   : 2013年1月31日
    作    者   : t00212959
    修改内容   : DTS2013012909238:手动模式下，单模，一个域注册被#11拒绝，一个域不支持，会循环不停的进行anycell搜网，被拒。

  5.日    期   : 2013年4月1日
    作    者   : w00167002
    修改内容   : DTS2013032701683:无卡开机，系统消息指示PS域不支持，MMC发起循环搜网
  6.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  7.日    期   : 2013年11月30日
    作    者   : z00161729
    修改内容   : DTS2013112809149:9230 nv项设置禁止接入技术为w和g，手动搜网模式驻留g的23002成功，
                 syscfg设置w only，anycell驻留24005，会反复触发w下anycell搜网
  8.日    期   : 2014年04月8日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:服务状态上报到mmc
  9.日    期   : 2015年11月24日
    作    者   : w00167002
    修改内容   : DTS2015112405788:在海外测试,如果当前开机CS/PS是无服务，则不上报到
                 MMA，而MMA需要收起CS/PS的服务状态，才给stk下发LOCATION STATUS NTF
                 消息；卡收不到此消息，则不进行IMSI切换。
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause409ServingCellDomainNotSupport(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_TIMER_STATUS_ENUM_U8                            enAvailableTimerStatus;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, begin */
    /* 更新服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, end */

    enFsmId                = NAS_MMC_GetCurrFsmId();
    enAvailableTimerStatus = NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER);

    /* 当前在ONPLMN时，若收到结果为CS域不支持，则需要判断此时是否需要发起搜网，
       1)PS域是LIMIT_CAMP_ON 2)AVAILABLE定时器未启动 3)PS域准许发起注册,则MMC需要发起搜网
    */
    if ( (NAS_MMC_FSM_L1_MAIN   == enFsmId)
      || (NAS_MMC_FSM_PLMN_LIST == enFsmId) )
    {
        if (VOS_FALSE == NAS_MMC_IsNeedPlmnSearch_RegLocalFailCause())
        {
            return NAS_MMC_ADDITIONAL_ACTION_BUTT;
        }

        if (NAS_MMC_TIMER_STATUS_RUNING               == enAvailableTimerStatus)
        {
            return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
        }


        /* 在L1 MAIN时候，如果当前是无卡，则PS返回不需要搜网 */
        if ( VOS_FALSE == NAS_MML_GetSimPresentStatus() )
        {
            /* 返回NAS_MMC_ADDITIONAL_ACTION_BUTT，表示无效的AdditionalAction值,MMC
                不更新无效AdditionalAction值 */
            return NAS_MMC_ADDITIONAL_ACTION_BUTT;
        }
    }


    enPrioAdditionalAction = NAS_MMC_GetPsAdditionalAction();
    enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION, enPrioAdditionalAction);
    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-30, begin */
    else
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-30, end */

    return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause416DealyCsInTransLau
 功能描述  : Cs 异常原因值的处理
 输入参数  :
             VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年1月17日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause416DealyCsInTransLau(VOS_VOID)
{
    return NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause418T3212Running
 功能描述  : Eps T3402定时器正在运行的后续处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月4日
    作    者   : w00167002
    修改内容   : DTS2014052603967:CS only，在A小区注册失败17后迁移到B小区，在B小区
                是禁止PLMN小区，MM迁移到LIMIT service状态，后续搜网到A小区网络后，
                发起了LAU.
                在LAU失败迁移到U2状态时候记录当前的LAI信息；在开机，用户发起CS/CS_PS
                DETACH时候或或者重新发起LAU时候则清除该LAI信息；
                在后续搜索到该小区后，在U2状态，如果当前的LAI在记录的LAI里面，则
                不发起LAU.

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause418T3212Running(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;
    VOS_UINT8                                               ucSingleDomainSrchFlag;

    enFsmId                = NAS_MMC_GetCurrFsmId();

    /* 更新服务状态 */
    NAS_MMC_SetCsServiceStatus(NAS_MMC_LIMITED_SERVICE);

    /* 通知TAF当前的服务状态 */
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE);

    /* 取得当前的CS/PS域的ADDITIONAL ACTION值 */
    enCsAdditionalAction   = NAS_MMC_GetCsAdditionalAction();
    enPsAdditionalAction   = NAS_MMC_GetPsAdditionalAction();

    /* 在选网状态机需要获取当前的CS域的ADDITIONAL ACTION值 */
    if ( (NAS_MMC_FSM_PLMN_SELECTION == enFsmId)
      || (NAS_MMC_FSM_BG_PLMN_SEARCH == enFsmId) )
    {
        /* 单域搜网定制标识 */
        ucSingleDomainSrchFlag = NAS_MML_GetDtSingleDomainPlmnSearchFlag();

        /* 最大次数失败被拒是否立即触发搜网，VDF定制打开或DT单域搜网定制打开时搜网；不打开时，等待PS的注册结果 */
        if ((VOS_TRUE == NAS_MML_GetCsRejSearchSupportFlg())
         || (VOS_TRUE == ucSingleDomainSrchFlag))
        {
            enCsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        }
        else
        {
            enCsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
        }
    }

    enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);
    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }

    return enCsAdditionalAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause419HoSucc
 功能描述  : 注册假流程，切换之后无系统消息的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月13日
    作    者   : s00217060
    修改内容   : Service_State_Optimize_PhaseI:切换流程无系统消息的处理
  2.日    期   : 2015年7月13日
    作    者   : s00217060
    修改内容   : DTS2015070907463:原因值扩展，函数名修改
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause419InterRatChangeSucc(VOS_VOID)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo     = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    enRat               = NAS_MML_GetCurrNetRatType();
    pstCampPlmnInfo     = NAS_MML_GetCurrCampPlmnInfo();

    /* 如果当前主模和驻留信息里的接入技术相同，MMC已经收到接入层上报的系统消息，不用构造系统消息 */
    /* pstCampPlmnInfo->enNetRatType在收到RESUME_IND时更新，pstCampPlmnInfo->stLai.enCampPlmnNetRat在收到系统消息时更新 */
    if (enRat != pstCampPlmnInfo->stLai.enCampPlmnNetRat)
    {
        /* 更新CampPlmnInfo中的Rat值 */
        pstCampPlmnInfo->stLai.enCampPlmnNetRat     = enRat;

        /* 系统子模式用缺省值,切换结束，肯定有主模的，enRat不可能是BUTT */
        if (NAS_MML_NET_RAT_TYPE_GSM == enRat)
        {
            pstCampPlmnInfo->enSysSubMode   = NAS_MML_RRC_SYS_SUBMODE_EDGE;
        }
        else if (NAS_MML_NET_RAT_TYPE_WCDMA == enRat)
        {
            pstCampPlmnInfo->enSysSubMode   = NAS_MML_RRC_SYS_SUBMODE_WCDMA;
        }
        else
        {
            pstCampPlmnInfo->enSysSubMode   = NAS_MML_RRC_SYS_SUBMODE_LTE;
        }

        /* 构造系统消息 */
        NAS_MMC_SndMsccSysInfo();
    }

    /* 通知TAF当前的注册状态 */
    NAS_MMC_ChangeCsRegState(NAS_MML_GetCsRegStatus());

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_GetCsServiceStatus());

    /* 返回值并不记录到全局变量，暂定为BUTT，不影响原来的流程 */
    return NAS_MMC_ADDITIONAL_ACTION_BUTT;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause421HoWaitSysinfoTimeout
 功能描述  : 注册假流程，切换之后无系统消息的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :

  1.日    期   : 2016年1月28日
    作    者   : w00167002
    修改内容   : 在IMS电话后SRVCC到G,没有系统消息，但下发了TMSI充分配，更新当前的RAT
                 为GSM;因判断RAT没有改变，没有给MSCC上报系统消息，导致界面一直显示为
                 4G.
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause421HoWaitSysinfoTimeout(VOS_VOID)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo     = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    enRat               = NAS_MML_GetCurrNetRatType();
    pstCampPlmnInfo     = NAS_MML_GetCurrCampPlmnInfo();

    /* 更新CampPlmnInfo中的Rat值 */
    pstCampPlmnInfo->stLai.enCampPlmnNetRat     = enRat;

    /* 系统子模式用缺省值,切换结束，肯定有主模的，enRat不可能是BUTT */
    if (NAS_MML_NET_RAT_TYPE_GSM == enRat)
    {
        pstCampPlmnInfo->enSysSubMode   = NAS_MML_RRC_SYS_SUBMODE_EDGE;
    }
    else if (NAS_MML_NET_RAT_TYPE_WCDMA == enRat)
    {
        pstCampPlmnInfo->enSysSubMode   = NAS_MML_RRC_SYS_SUBMODE_WCDMA;
    }
    else
    {
        pstCampPlmnInfo->enSysSubMode   = NAS_MML_RRC_SYS_SUBMODE_LTE;
    }

    /* 构造系统消息 */
    NAS_MMC_SndMsccSysInfo();

    /* 通知TAF当前的注册状态 */
    NAS_MMC_ChangeCsRegState(NAS_MML_GetCsRegStatus());

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_GetCsServiceStatus());

    /* 返回值并不记录到全局变量，暂定为BUTT，不影响原来的流程 */
    return NAS_MMC_ADDITIONAL_ACTION_BUTT;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCauseAbnormalCause
 功能描述  : Cs 异常原因值的处理
 输入参数  :
             VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年1月17日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCauseAbnormalCause(
    VOS_UINT16                          usCause,
    VOS_UINT32                          ulAttemptCnt
)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT8                                               ucRegFailMaxCnt;

    /* 初始化CS域Attempt Counter尝试注册失败的最大次数为4 */
    ucRegFailMaxCnt = NAS_MML_MAX_CS_REG_FAIL_CNT;

    /* 若roaming broker特性开启，则使用ROAMING BROKER保存的失败个数，当此特性
       未打开时，使用的值为NAS_MML_MAX_CS_REG_FAIL_CNT */
    if ( VOS_TRUE == NAS_MML_GetRoamBrokerActiveFlag() )
    {
        ucRegFailMaxCnt = NAS_MML_GetRoamBrokerRegisterFailCnt();
    }

    if (ulAttemptCnt < ucRegFailMaxCnt)
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailAttemptCounterMaxTimes
 功能描述  : Cs注册失败最大次数的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月18日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 3.日    期   : 2014年04月8日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc
 4.日    期   : 2015年9月23日
   作    者   : z00359541
   修改内容   : CS注册失败加入禁止LA列表特性打开时，需触发指定搜网。
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailAttemptCounterMaxTimes(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT8                                               ucSingleDomainSrchFlag;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    NAS_MMC_REG_RSLT_CTX_STRU                               *pstRegRsltCtx              = VOS_NULL_PTR;

    pstRegRsltCtx   = NAS_MMC_GetRegRsltCtxAddr();

    /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, begin */
    /* 更新服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, end */

    /* 单域搜网定制标识 */
    ucSingleDomainSrchFlag = NAS_MML_GetDtSingleDomainPlmnSearchFlag();

    /* 最大次数失败被拒是否立即触发搜网，VDF定制打开或DT单域搜网定制打开时搜网；不打开时，等待PS的注册结果 */
    if ((VOS_TRUE == NAS_MML_GetCsRejSearchSupportFlg())
     || (VOS_TRUE == ucSingleDomainSrchFlag))
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }
    /* 有业务时，NV定制是否需要立即触发搜网 */
    else if ((VOS_TRUE == NAS_MMC_IsNeedLauRejTrigPlmnSearch(pstRegRsltCtx->unRegRsltCtx.pstCsRegRsltInd->enRegFailCause)))
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }
    /* CS注册失败加入禁止LA特性打开 */
    else if (VOS_TRUE == NAS_MMC_IsFailCauseInCustomizedForbLaCfgList(pstRegRsltCtx->unRegRsltCtx.pstCsRegRsltInd->enRegFailCause))
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }
    else
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    }

    enPrioAdditionalAction = NAS_MMC_GetPsAdditionalAction();
    enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enAction, enPrioAdditionalAction);
    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
    else
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */


    return enAction;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause17AttemptCounterMaxTimes
 功能描述  : Cs注册失败最大次数的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月18日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 3.日    期   : 2014年5月21日
   作    者   : w00167002
   修改内容   : DTS2014051602857新增:在SOR打开时候，如果CS注册失败达到4次，则等周期
                搜网定时器超时发起LIST搜网，如果当前仅有原有网络，则发起LAU,否则
                触发MM发起LAU;如果LIST搜后，发现有其他网络，则发起其他网络的搜网注册。
                手动选网时候，返回LIMIT CAMP ON,不再发起选网。
 4.日    期   : 2015年9月23日
   作    者   : z00359541
   修改内容   : CS注册失败加入禁止LA列表特性打开时，需触发指定搜网。
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause17AttemptCounterMaxTimes(VOS_VOID)
{
    NAS_MML_SOR_ADDITIONAL_LAU_STRU                        *pstAdditionalLau            = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCampInfo                 = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT8                                               ucSingleDomainSrchFlag;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    VOS_UINT8                                               ucRegFailMaxCnt;
    VOS_UINT32                                              ulAttemptCnt;

    ucRegFailMaxCnt = NAS_MML_MAX_CS_REG_FAIL_CNT;

    /* 若roaming broker特性开启，则使用ROAMING BROKER保存的失败个数，当此特性
       未打开时，使用的值为NAS_MML_MAX_CS_REG_FAIL_CNT */
    if ( VOS_TRUE == NAS_MML_GetRoamBrokerActiveFlag() )
    {
        ucRegFailMaxCnt = NAS_MML_GetRoamBrokerRegisterFailCnt();
    }

    ulAttemptCnt        = NAS_MMC_GetRegRsltAttemptCounter(MM_MMC_CS_REG_RESULT_IND);

    pstAdditionalLau    = NAS_MML_GetSorAdditionalLauCtx();
    pstCampInfo         = NAS_MML_GetCurrCampPlmnInfo();

    /* 更新服务状态 */
    NAS_MMC_SetCsServiceStatus(NAS_MMC_LIMITED_SERVICE);

    /* 通知TAF当前的服务状态 */
    /* Added by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE);
    /* Added by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/

    /* 单域搜网定制标识 */
    ucSingleDomainSrchFlag = NAS_MML_GetDtSingleDomainPlmnSearchFlag();

    /* 最大次数失败被拒是否立即触发搜网，VDF定制打开时搜网；不打开时，等待PS的注册结果 */
    if (VOS_TRUE == NAS_MML_GetCsRejSearchSupportFlg())
    {

        /* SOR手动选网模式，则限制驻留 */
        if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
        {
            enAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
        }

        /* 如果SOR特性定制打开，当前COUNTER达到最大次数，则设置additional LAU信息 */
        else if ( ulAttemptCnt == ucRegFailMaxCnt )
        {
            pstAdditionalLau->ucAdditionalLauFlag = VOS_TRUE;
            PS_MEM_CPY(&(pstAdditionalLau->stLai), &(pstCampInfo->stLai), sizeof(NAS_MML_LAI_STRU));

            enAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        }
        else
        {
            if (VOS_TRUE == NAS_MMC_IsFailCauseInCustomizedForbLaCfgList(NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE))
            {
                enAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
            }
            else if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER))
            {
                enAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
            }
            else
            {
                enAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
            }

        }
    }

    /* DT单域搜网定制打开时搜网；不打开时，等待PS的注册结果 */
    else if (VOS_TRUE == ucSingleDomainSrchFlag)
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }
    /* 有业务时，NV定制打开，需要立即触发搜网 */
    else if (VOS_TRUE == NAS_MMC_IsNeedLauRejTrigPlmnSearch(NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE))
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }
    /* CS注册失败加入禁止LA特性打开且失败原因值已配置 */
    else if (VOS_TRUE == NAS_MMC_IsFailCauseInCustomizedForbLaCfgList(NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE))
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }
    else
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    }

    enPrioAdditionalAction = NAS_MMC_GetPsAdditionalAction();
    enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enAction, enPrioAdditionalAction);
    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }

    return enAction;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailAttemptCounterMaxTimes
 功能描述  : Cs注册失败最大次数的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月18日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2014年3月29日
   作    者   : z00161729
   修改内容   : DTS2014032200128:g下cs only cs域上报的服务状态为限制服务，注册状态上报为驻留home网络，导致界面显示正常但发短信失败
 3.日    期   : 2014年04月8日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc

 4.日    期   : 2014年10月22日
   作    者   : w00167002
   修改内容   : DTS2014101305830:在PLMN改变时候，更新服务状态。
                俄罗斯外场测试:在25002网络的4G上注册成功后，重定向到G下，联合RAU
                失败(ps/cs cause:303),立即更新的服务状态，用户体验不好。第二次RAU
                就成功了。
                关于状态显示优化的功能，SE有进行系统的优化设计方案，当前只针对问题场景
                进行简易优化修改。
 5.日    期   : 2014年11月28日
   作    者   : w00281933
   修改内容   : 服务状态显示优化PhaseI

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailAttemptCounterLessThanMaxTimes(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEplmnInfo        = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmn     = VOS_NULL_PTR;
    VOS_UINT32                                              ulInEplmnListFlag;
    VOS_UINT32                                              ulUserSpecPlmnFlag;
    NAS_MML_PLMN_ID_STRU                                   *pstCurPlmnId        = VOS_NULL_PTR;

    NAS_MML_REG_STATUS_ENUM_UINT8                           enCsRegStatus;

    enCsRegStatus = NAS_MML_GetCsRegStatus();

    /* 默认设置当前继续等待注册结果 */
    enAction      = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;


    if(NAS_MMC_NORMAL_SERVICE != NAS_MMC_GetCurrCsService())
    {
        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, begin */
        /* 更新服务状态 */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, end */

        /* 如果之前注册成功，需要将注册状态设置为0 */
        if ((NAS_MML_REG_REGISTERED_HOME_NETWORK == enCsRegStatus)
         || (NAS_MML_REG_REGISTERED_ROAM == enCsRegStatus))
        {
            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
    }

    /* 自动模式返回NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT */
    if ( NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode() )
    {
        return enAction;
    }

    /* 手动模式判断当前网络是否是用户指定的网络 */
    pstCurPlmnId       = NAS_MML_GetCurrCampPlmnId();
    pstUserSpecPlmn    = NAS_MMC_GetUserSpecPlmnId();
    ulUserSpecPlmnFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurPlmnId,
                                                &(pstUserSpecPlmn->stPlmnId));

    /* 判断当前网络是否在EPlmn列表里 */
    pstEplmnInfo       = NAS_MML_GetEquPlmnList();

    ulInEplmnListFlag  = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstCurPlmnId,
                                              pstEplmnInfo->ucEquPlmnNum,
                                              pstEplmnInfo->astEquPlmnAddr);

    /* 手动模式下，当前Plmn不是用户指定的PLMN,且当前PLMN不在EPlmn列表里，
       则认为当前plmn 已经失效了，需要进行搜网 */
    if ( (VOS_FALSE == ulUserSpecPlmnFlag)
      && (VOS_FALSE == ulInEplmnListFlag) )
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    }

    return enAction;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause3IllegalMs
 功能描述  : Ps Cause3的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2011年12月20日
    作    者   : h44270
    修改内容   : 卡无效时，通知APS挂起
  3.日    期   : 2012年10月15日
    作    者   : s00217060
    修改内容   : for DTS2012082308686:Ps注册失败原因值#3,#6,#8,#256，需要重新Enable Lte
  4.日    期   : 2013年01月23日
    作    者   : s00217060
    修改内容   : 问题单: DTS2013012106172,Enable Lte时停止定时器TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
  5.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  6.日    期   : 2014年4月29日
    作    者   : s00261364
    修改内容   : ecall项目修改服务状态上报
  7.日    期   : 2015年1月5日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause3IllegalMs(VOS_VOID)
{
#if   (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulDisablteRoamFlg;

    ulDisablteRoamFlg = NAS_MML_GetDisableLteRoamFlg();
#endif

    /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, begin */
    /* 更新服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, end */

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,VOS_FALSE);

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);

#if   (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MMC_IsNeedEnableLte_PsRegFailCause3IllegalMs())
    {
        /* 如果由于禁止LTE国际漫游导致的disable LTE，再未回到国内之前此时也不通知enable LTE */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
         && (VOS_FALSE == ulDisablteRoamFlg))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* 更新disable LTE能力标记 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }
#endif

    return NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;

}
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause6IllegalMe
 功能描述  : Ps Cause6的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause6IllegalMe(VOS_VOID)
{
    /* 按PsCause6 处理 */
    return NAS_MMC_ProcPsRegFailCause3IllegalMs();
}
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause7GprsServNotAllow
 功能描述  : Ps Cause7的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数

 2.日    期   : 2011年10月26日
   作    者   : w00176964
   修改内容   : V7R1 Phase III调整:联合注册修改

 3.日    期   : 2011年12月01日
   作    者   : w00176964
   修改内容   : V7R1 Phase IV调整:disable/enable 调整

 4.日    期   : 2011年12月20日
   作    者   : h44270
   修改内容   : 卡无效时，通知APS挂起
 5.日    期   : 2012年3月17日
   作    者   : w00176964
   修改内容   : DTS2012031900095 V7R1 C30 SBM&EM定制需求:增加LTE国家漫游功能定制
 6.日    期   : 2012年07月02日
   作    者   : s46746
   修改内容   : For CS/PS mode 1，调整Disable/Enable L,按场景区分函数
 7.日    期   : 2012年7月27日
   作    者   : s00217060
   修改内容   : for CS/PS mode 1,带Disable LTE原因值
 8.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 9.日    期   : 2014年4月29日
   作    者   : s00261364
   修改内容   : ecall项目修改服务状态上报
 10.日    期   : 2015年1月5日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause7GprsServNotAllow(VOS_VOID)
{
    /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, begin */
    /* 更新服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, end */

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,VOS_FALSE);

    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);

#if (FEATURE_ON == FEATURE_LTE)

    /* 判断是否需要disable LTE */
    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_PsFailCause7PsServNotAllow())
    {
        /* 如果漫游导致的disable已经通知了GU接入层,此时不需要再重复通知 */
        if (VOS_FALSE == NAS_MML_GetDisableLteRoamFlg())
        {
            NAS_MMC_SndDisableLteNotify(MMC_LMM_DISABLE_LTE_REASON_PS_USIM_INVALID);

            /* 记录disable lte时驻留的网络信息 */
            NAS_MMC_SetDisabledLtePlmnId(NAS_MML_GetCurrCampPlmnId());
        }

        /* 更新disable LTE能力标记 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS);

        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_PS_USIM_INVALID);
    }
#endif
    return NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause8GprsAndNonGprsNotAllow
 功能描述  : Ps Cause8的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2011年12月20日
    作    者   : h44270
    修改内容   : 卡无效时，通知APS挂起
  3.日    期   : 2012年10月15日
    作    者   : s00217060
    修改内容   : for DTS2012082308686:Ps注册失败原因值#3,#6,#8,#256，需要重新Enable Lte
  4.日    期   : 2013年01月23日
    作    者   : s00217060
    修改内容   : 问题单: DTS2013012106172,Enable Lte时停止定时器TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
  5.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  6.日    期   : 2014年4月29日
    作    者   : s00261364
    修改内容   : ecall项目修改服务状态上报
  7.日    期   : 2015年1月5日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause8GprsAndNonGprsNotAllow(VOS_VOID)
{
#if   (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulDisablteRoamFlg;

    ulDisablteRoamFlg = NAS_MML_GetDisableLteRoamFlg();
#endif

    /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, begin */
    /* 更新服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, end */

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,VOS_FALSE);

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);

#if   (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MMC_IsNeedEnableLte_PsRegFailCause8GprsAndNonGprsNotAllow())
    {
        /* 如果由于禁止LTE国际漫游导致的disable LTE，再未回到国内之前此时也不通知enable LTE */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
         && (VOS_FALSE == ulDisablteRoamFlg))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* 更新disable LTE能力标记 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }
#endif

    return NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause9MsIdNotDerived
 功能描述  : ps Cause:9的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  3.日    期   : 2013年07月16日
    作    者   : w00242748
    修改内容   : 修改手动搜网导致死循环
  4.日    期   : 2014年04月8日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause9MsIdNotDerived(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8                  ucPlmnSelMode;

    /* 手动模式且需要attach的情况下，不需要删除EPlmn，自动模式或者不需要
    ATTACH的时候，需要删除EPLMN。此处修改不符合协议规范，修改为了用户体验。
    避免手动模式EPLMN被删除时，避免出现手动搜网RAU被拒触发死循环。
    此处修改配合NAS_GMM_DeleteEPlmnList解决手动搜网被拒，导致死循环问题。*/
    ucPlmnSelMode = NAS_MMC_GetPlmnSelectionMode();

    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == ucPlmnSelMode))
    {
        NAS_MML_SetEplmnValidFlg(VOS_TRUE);
    }

    /* 取得当前的注册结果类型  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    /* 当前在GMM上报的NET WORK DETACH IND消息，则返回LIMIT_CAMP_ON */
    if ( GMM_MMC_PS_NETWORK_DETACH_IND == enRegRsltType)
    {
        /* 获取CS addition,并与NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON比较，
           如果不需要发起搜网则更新PS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON, enPrioAdditionalAction);

        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-8, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }
        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-8, end */

        return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    /* 根据注册结果上报的Attempt Counter是否达到最大次数分别进行处理 */
    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause10ImplicitDetached
 功能描述  : ps Cause:10的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  3.日    期   : 2013年07月16日
    作    者   : w00242748
    修改内容   : 修改手动搜网被拒死循环
  4.日    期   : 2014年04月8日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause10ImplicitDetached(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8                  ucPlmnSelMode;

    /* 手动模式且需要attach的情况下，不需要删除EPlmn，自动模式或者不需要
    ATTACH的时候，需要删除EPLMN。此处修改不符合协议规范，修改为了用户体验。
    避免手动模式EPLMN被删除时，避免出现手动搜网RAU被拒触发死循环。
    此处修改配合NAS_GMM_DeleteEPlmnList解决手动搜网被拒，导致死循环问题。*/
    ucPlmnSelMode = NAS_MMC_GetPlmnSelectionMode();

    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == ucPlmnSelMode))
    {
        NAS_MML_SetEplmnValidFlg(VOS_TRUE);
    }

    /* 取得当前的注册结果类型  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    /* 当前在GMM上报的NET WORK DETACH IND消息，则返回LIMIT_CAMP_ON */
    if ( GMM_MMC_PS_NETWORK_DETACH_IND == enRegRsltType)
    {
        /* 获取CS addition,并与NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON比较，
           如果不需要发起搜网则更新PS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON, enPrioAdditionalAction);

        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-8, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }
        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-8, end */


        return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    /* 根据注册结果上报的Attempt Counter是否达到最大次数分别进行处理 */
    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause11PlmnNotAllow
 功能描述  : Ps Cause11的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV修改合并原NAS_MMC_HPLMN_REG_REJ_STRU和NAS_MMC_PLMN_REG_INFO_STRU
  3.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目
  4.日    期   : 2012年07月19日
    作    者   : l65478
    修改内容   : DTS2012071805908,在HOME PLMN注册失败#11后发起了搜网,不满足EM需求
  5.日    期   : 2012年11月29日
    作    者   : W00176964
    修改内容   : DTS2012112902395,BVT测试,hplmn被拒#11后后续需要继续注册
  6.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  7.日    期   : 2014年04月8日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause11PlmnNotAllow(VOS_VOID)
{
    VOS_UINT8                           ucRejDomain;
    NAS_MML_MS_CFG_INFO_STRU           *pstMsCfg;
    NAS_MML_PLMN_ID_STRU               *pstCurPlmnId;

    pstCurPlmnId = NAS_MML_GetCurrCampPlmnId();

    pstMsCfg = NAS_MML_GetMsCfgInfo();

    /* 添加禁止网络信息,有更新时，向Usim更新文件 */
    if (VOS_TRUE == NAS_MML_AddForbPlmn(pstCurPlmnId))
    {
        NAS_MMC_SndUsimUpdateForbPlmnReq();
    }

    /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, begin */
    /* 更新服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, end */

    /* 驻留在非HOME PLMN上时，注册拒绝#11时进行搜网 */
    if (VOS_FALSE == NAS_MML_ComparePlmnIdWithHplmn(pstCurPlmnId))
    {
        /* 根据注册结果更新注册信息表 */
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(),
                 NAS_MMC_REG_DOMAIN_PS, NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW);

        /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    if ( VOS_FALSE == NAS_MML_GetHplmnRegisterCtrlFlg())
    {
        /* 非E5版本才做如下处理，E5版本要求能在HPLMN上反复发起注册 */
        /* 根据注册结果更新注册信息表 */
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(),
                 NAS_MMC_REG_DOMAIN_PS, NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW);


        if ((NAS_MML_MS_MODE_PS_CS == pstMsCfg->stMsSysCfgInfo.enMsMode))
        {
            NAS_MMC_GetHplmnRejDomainInfo(&ucRejDomain);

            if (NAS_MMC_REG_DOMAIN_PS_CS != ucRejDomain)
            {
                NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

                return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
            }
        }

    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */
    else
    {
        /* EM定制需求:1、PS ONLY；2、当前是W；3、被网络拒#11时,
           需要在HOME PLMN继续进行注册 */
        if ((NAS_MML_NET_RAT_TYPE_WCDMA ==  NAS_MML_GetCurrNetRatType())
         && (NAS_MML_MS_MODE_PS_ONLY == pstMsCfg->stMsSysCfgInfo.enMsMode))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

            return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
        }
    }

    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause12LaNotAllow
 功能描述  : Ps Cause12的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  3.日    期   : 2014年04月8日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause12LaNotAllow(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8          enCsAdditionalAction;

    /*添加禁止网络信息*/
    NAS_MML_AddForbRegLa(NAS_MML_GetCurrCampLai());

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_FORBID_LA_TIMER, TI_NAS_MMC_FORBID_LA_TIMER_LEN);

    /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, begin */
    /* 更新服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE_REGION);
    /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, end */

    enCsAdditionalAction = NAS_MMC_GetCsAdditionalAction();
    if ((NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL != enCsAdditionalAction)
     && (NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION != enCsAdditionalAction)
     && (NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN != enCsAdditionalAction))
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
    else
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    return NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause13RoamNotAllow
 功能描述  : Ps Cause13的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : l00130025
   修改内容   : 新生成函数
 2.日    期   : 2011年11月12日
   作    者   : w00167002
   修改内容   : DTS2011110907180:NAS_MML_AddForbRoamLa函数调整的修改
 3.日    期   : 2014年04月8日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause13RoamNotAllow(VOS_VOID)
{
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU                stForbRoamLaInfo;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                        *pstForbPlmnInfo = VOS_NULL_PTR;

    /* 非用户指定搜网，从全局变量中获取FORBIDEN ROAMING LAS信息 */
    pstForbPlmnInfo                  = NAS_MML_GetForbidPlmnInfo();
    stForbRoamLaInfo.ucForbRoamLaNum = pstForbPlmnInfo->ucForbRoamLaNum;
    PS_MEM_CPY( stForbRoamLaInfo.astForbRomLaList,
                pstForbPlmnInfo->astForbRomLaList,
                sizeof(pstForbPlmnInfo->astForbRomLaList) );

    /* 添加禁止网络信息到全局变量的禁止漫游LA变量里去 */
    NAS_MML_AddForbRoamLa( NAS_MML_GetCurrCampLai(),
                           &stForbRoamLaInfo );
    pstForbPlmnInfo->ucForbRoamLaNum = stForbRoamLaInfo.ucForbRoamLaNum;
    PS_MEM_CPY( pstForbPlmnInfo->astForbRomLaList,
                stForbRoamLaInfo.astForbRomLaList,
                sizeof(pstForbPlmnInfo->astForbRomLaList));

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_FORBID_LA_TIMER, TI_NAS_MMC_FORBID_LA_TIMER_LEN);

    /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, begin */
    /* 更新服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, end */

    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

}
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause14GprsNotAllowInThisPlmn
 功能描述  : Ps Cause8的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数
  3.日    期   : 2012年6月20日
    作    者   : w00166186
    修改内容   : AT&T&DCM项目
  4.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  5.日    期   : 2014年04月8日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause14GprsNotAllowInThisPlmn(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* 添加禁止GPRS PLMN 信息 */
    NAS_MML_AddForbGprsPlmn(NAS_MML_GetCurrCampPlmnId());

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-30, begin */

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-30, end */
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-30, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-30, end */

    /* 如果有定制的#14的动作，返回NV中定制的动作 */
    enAction = NAS_MMC_GetSingleDomainFailAction(NAS_MML_REG_DOMAIN_PS, NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN);

    if (NAS_MMC_ADDITIONAL_ACTION_BUTT == enAction)
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    }

    /* 获取CS addition,并与enAction比较，如果不需要发起搜网则更新PS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
    enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enAction, enPrioAdditionalAction);
    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-30, begin */
    else
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-30, end */


    return enAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause15NoSuitableCell
 功能描述  : Ps Cause13的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : l00130025
   修改内容   : 新生成函数
 2.日    期   : 2011年11月12日
   作    者   : w00167002
   修改内容   : DTS2011110907180:当前若为选网状态机，则添加禁止网络信息
                 到禁止漫游LA变量里去
 3.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
 4.日    期   : 2014年04月8日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause15NoSuitableCell(VOS_VOID)
{
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU                stForbRoamLaInfo;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                        *pstForbPlmnInfo = VOS_NULL_PTR;

    /* 非用户指定搜网，从全局变量中获取FORBIDEN ROAMING LAS信息 */
    pstForbPlmnInfo                  = NAS_MML_GetForbidPlmnInfo();
    stForbRoamLaInfo.ucForbRoamLaNum = pstForbPlmnInfo->ucForbRoamLaNum;
    PS_MEM_CPY( stForbRoamLaInfo.astForbRomLaList,
                pstForbPlmnInfo->astForbRomLaList,
                sizeof(pstForbPlmnInfo->astForbRomLaList) );

    /* 添加禁止网络信息到全局变量的禁止漫游LA变量里去 */
    NAS_MML_AddForbRoamLa( NAS_MML_GetCurrCampLai(),
                           &stForbRoamLaInfo );
    pstForbPlmnInfo->ucForbRoamLaNum = stForbRoamLaInfo.ucForbRoamLaNum;
    PS_MEM_CPY( pstForbPlmnInfo->astForbRomLaList,
                stForbRoamLaInfo.astForbRomLaList,
                sizeof(pstForbPlmnInfo->astForbRomLaList));


    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_FORBID_LA_TIMER, TI_NAS_MMC_FORBID_LA_TIMER_LEN);

    /* 更新服务状态 */
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-8, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-8, end */

    return NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;

}
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause40NoPdpContextActived
 功能描述  : Ps Cause40的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause40NoPdpContextActived(VOS_VOID)
{
    return NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause95SemanticallyIncorrectMsg
 功能描述  : Ps Cause95的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月12日
   作    者   : w00167002
   修改内容   : DTS2011122006209:拒绝原因值95的处理
 2.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 3.日    期   : 2014年04月8日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause95SemanticallyIncorrectMsg(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* 取得当前的注册结果类型  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    /* 当前在GMM上报的PS SERVICE REG RSLT IND消息，则返回NORMAL_CAMP_ON */
    if ( GMM_MMC_PS_SERVICE_RESULT_IND ==  enRegRsltType)
    {
        return NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
    }

    /* 当前在GMM上报的NET WORK DETACH IND消息，则返回LIMIT_CAMP_ON */
    if ( GMM_MMC_PS_NETWORK_DETACH_IND ==  enRegRsltType)
    {
        /* 获取CS addition,并与NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON比较，
           如果不需要发起搜网则更新PS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON, enPrioAdditionalAction);

        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-8, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }
        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-8, end */

        return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause96InvalidMandatoryInf
 功能描述  : Ps Cause96的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月12日
   作    者   : w00167002
   修改内容   : DTS2011122006209:拒绝原因值96的处理
 2.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 3.日    期   : 2014年04月8日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause96InvalidMandatoryInf(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* 取得当前的注册结果类型  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    /* 当前在GMM上报的PS SERVICE REG RSLT IND消息，则返回NORMAL_CAMP_ON */
    if ( GMM_MMC_PS_SERVICE_RESULT_IND ==  enRegRsltType)
    {
        return NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
    }

    /* 当前在GMM上报的NET WORK DETACH IND消息，则返回LIMIT_CAMP_ON */
    if ( GMM_MMC_PS_NETWORK_DETACH_IND ==  enRegRsltType)
    {
        /* 获取CS addition,并与NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON比较，
           如果不需要发起搜网则更新PS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON, enPrioAdditionalAction);

        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-8, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }
        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-8, end */


        return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause97MsgNonExistNotImplement
 功能描述  : Ps Cause97的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月12日
   作    者   : w00167002
   修改内容   : DTS2011122006209:拒绝原因值97的处理
 2.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 3.日    期   : 2014年04月8日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause97MsgNonExistNotImplement(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* 取得当前的注册结果类型  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    /* 当前在GMM上报的PS SERVICE REG RSLT IND消息，则返回NORMAL_CAMP_ON */
    if ( GMM_MMC_PS_SERVICE_RESULT_IND ==  enRegRsltType)
    {
        return NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
    }

    /* 当前在GMM上报的NET WORK DETACH IND消息，则返回LIMIT_CAMP_ON */
    if ( GMM_MMC_PS_NETWORK_DETACH_IND ==  enRegRsltType)
    {
        /* 获取CS addition,并与NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON比较，
           如果不需要发起搜网则更新PS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON, enPrioAdditionalAction);

        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-8, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }
        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-8, end */


        return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause99IeNonExistNotImplement
 功能描述  : Ps Cause99的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月12日
   作    者   : w00167002
   修改内容   : DTS2011122006209:拒绝原因值99的处理
 2.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 3.日    期   : 2014年04月8日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause99IeNonExistNotImplement(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* 取得当前的注册结果类型  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    /* 当前在GMM上报的PS SERVICE REG RSLT IND消息，则返回NORMAL_CAMP_ON */
    if ( GMM_MMC_PS_SERVICE_RESULT_IND ==  enRegRsltType)
    {
        return NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
    }

    /* 当前在GMM上报的NET WORK DETACH IND消息，则返回LIMIT_CAMP_ON */
    if ( GMM_MMC_PS_NETWORK_DETACH_IND ==  enRegRsltType)
    {
        /* 获取CS addition,并与NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON比较，
           如果不需要发起搜网则更新PS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON, enPrioAdditionalAction);

        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-8, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }
        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-8, end */


        return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause111ProtocolError
 功能描述  : Ps Cause111的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月12日
   作    者   : w00167002
   修改内容   : DTS2011122006209:拒绝原因值111的处理
 2.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 3.日    期   : 2014年04月8日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause111ProtocolError(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* 取得当前的注册结果类型  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    /* 当前在GMM上报的PS SERVICE REG RSLT IND消息，则返回NORMAL_CAMP_ON */
    if ( GMM_MMC_PS_SERVICE_RESULT_IND == enRegRsltType)
    {
        return NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
    }

    /* 当前在GMM上报的NET WORK DETACH IND消息，则返回LIMIT_CAMP_ON */
    if ( GMM_MMC_PS_NETWORK_DETACH_IND == enRegRsltType)
    {
        /* 获取CS addition,并与NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON比较，
           如果不需要发起搜网则更新PS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON, enPrioAdditionalAction);

        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-8, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }
        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-8, end */


        return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause256AuthRej
 功能描述  : Ps Reg Auth rej的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年2月3日
    作    者   : w00167002
    修改内容   : DTS2011122704039:在注册失败原因值的函数命名中增加原因值，
                  保持函数命名的一致性。
  3.日    期   : 2012年10月15日
    作    者   : s00217060
    修改内容   : for DTS2012082308686:Ps注册失败原因值为3,6,8,256时，需要重新Enable Lte
  4.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  5.日    期   : 2013年01月23日
    作    者   : s00217060
    修改内容   : 问题单: DTS2013012106172,Enable Lte时停止定时器TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
  6.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  7.日    期   : 2014年4月29日
    作    者   : s00261364
    修改内容   : ecall项目修改服务状态上报
  8.日    期   : 2015年1月5日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause256AuthRej(VOS_VOID)
{
#if   (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulDisablteRoamFlg;

    ulDisablteRoamFlg = NAS_MML_GetDisableLteRoamFlg();
#endif

    /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, begin */
    /* 更新服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, end */

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);

#if   (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MMC_IsNeedEnableLte_PsRegFailCause256AuthRej())
    {
        /* 如果由于禁止LTE国际漫游导致的disable LTE，再未回到国内之前此时也不通知enable LTE */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
         && (VOS_FALSE == ulDisablteRoamFlg))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* 更新disable LTE能力标记 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }
#endif

    return NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause257AccessBarrd
 功能描述  : Ps AccessBarrd的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年2月3日
    作    者   : w00167002
    修改内容   : DTS2011122704039:在注册失败原因值的函数命名中增加原因值，
                  保持函数命名的一致性。
  3.日    期   : 2012年3月10日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
  4.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  5.日    期   : 2013年10月15日
    作    者   : s00190137
    修改内容   : 特性开关打开且非HPLMN/RPLMN接入禁止时需要触发PLMN搜网
  6.日    期   : 2014年04月8日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:服务状态上报到mmc
  7.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : DTS2015082002854: 漫游标记不准
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause257AccessBarrd(VOS_VOID)
{
    NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8    enPsUpdateStatus;

    enPsUpdateStatus = NAS_MML_GetPsUpdateStatus();

    /* 如果当前RAI和上次成功注册的RAI相同，UPDATE状态为U1，且已注册为1或5，
       否则为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    if ((VOS_FALSE == NAS_MML_IsRaiChanged())
     && (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == enPsUpdateStatus)
     && (GMM_STATUS_ATTACHED == (NAS_MMC_GetGmmCtx())->ucAttachSta))
    {
        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);
    }
    else
    {

        /* Added by s00261364 for V3R360_eCall项目, 2014-4-8, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
        /* Added by s00261364 for V3R360_eCall项目, 2014-4-8, end */
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }

    /*特性开关打开且非HPLMN/RPLMN接入禁止时需要触发PLMN搜网*/
    if (VOS_TRUE == NAS_MMC_IsAccBarPlmnSearch())
    {
        return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    }
    else
    {
        return NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED;
    }
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause301TimerTimeOut
 功能描述  : ps Cause:NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT 的处理
 输入参数  :
             VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月18日
   作    者   : w00167002
   修改内容   : 新生成函数。
 2.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 3.日    期   : 2014年04月4日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause301TimerTimeOut(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* 取得当前的注册结果类型  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    /* 当前在GMM上报的PS SERVICE REG RSLT IND消息，则返回NORMAL_CAMP_ON */
    if ( GMM_MMC_PS_SERVICE_RESULT_IND == enRegRsltType)
    {
        return NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
    }

    /* 当前在GMM上报的NET WORK DETACH IND消息，则返回LIMIT_CAMP_ON */
    if ( GMM_MMC_PS_NETWORK_DETACH_IND == enRegRsltType)
    {
        /* 获取CS addition,并与NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON比较，
           如果不需要发起搜网则更新PS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON, enPrioAdditionalAction);

        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }
        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, end */


        return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause302RrConnEstFail
 功能描述  : Ps Cause:NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL 的处理
 输入参数  :
             VOS_UINT32                          ulAttemptCnt
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月18日
   作    者   : w00167002
   修改内容   : 新生成函数。
 2.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 3.日    期   : 2014年04月4日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause302RrConnEstFail(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* 取得当前的注册结果类型  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    /* 当前在GMM上报的PS SERVICE REG RSLT IND消息，则返回NORMAL_CAMP_ON */
    if ( GMM_MMC_PS_SERVICE_RESULT_IND == enRegRsltType)
    {
        return NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
    }

    /* 当前在GMM上报的NET WORK DETACH IND消息，则返回LIMIT_CAMP_ON */
    if ( GMM_MMC_PS_NETWORK_DETACH_IND == enRegRsltType)
    {
        /* 获取CS addition,并与NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON比较，
           如果不需要发起搜网则更新PS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON, enPrioAdditionalAction);

        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }
        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, end */



        return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause303RrConnFail
 功能描述  : Ps Cause:NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL的处理
 输入参数  : VOS_UINT32                          ulAttemptCnt
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月18日
   作    者   : w00167002
   修改内容   : 新生成函数。
 2.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 3.日    期   : 2014年04月4日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause303RrConnFail(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;

    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* 取得当前的注册结果类型  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    /* 当前在GMM上报的PS SERVICE REG RSLT IND消息，则返回NORMAL_CAMP_ON */
    if ( GMM_MMC_PS_SERVICE_RESULT_IND == enRegRsltType)
    {
        return NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
    }

    /* 当前在GMM上报的NET WORK DETACH IND消息，则返回LIMIT_CAMP_ON */
    if ( GMM_MMC_PS_NETWORK_DETACH_IND == enRegRsltType)
    {
        /* 获取CS addition,并与NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON比较，
           如果不需要发起搜网则更新PS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON, enPrioAdditionalAction);

        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }
        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, end */


        return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause401OtherCause
 功能描述  : OtherCause的处理
 输入参数  : VOS_UINT16                          usCause,
              VOS_UINT32                          ulAttemptCnt
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : l00130025
   修改内容   : 新生成函数
                1)  attemptCount < MaxCount时，返回NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT
                2)  attemptCount >= MaxCount时，无定制需求，要等待另外一个域的注册结果,返回NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION
                3)  attemptCount >= MaxCount时，有单域的搜网定制（DT的定制需求），返回NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION

 2.日    期   : 2011年11月18日
   作    者   : w00167002
   修改内容   : DTS2011111603330:若当前的RAI发生改变，即使失败次数未达到
                最大次数,也更新为限制服务状态。
 3.日    期   : 2012年1月3日
   作    者   : w00167002
   修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网.
                NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE时，返回NAS_MMC_ADDITIONAL_ACTION_BUTT,
                表示MMC不需要写入当前CS的ADDITIONAL ACTION值。
 4.日    期   : 2012年2月3日
   作    者   : w00167002
   修改内容   : DTS2011122704039:在注册失败原因值的函数命名中增加原因值，
                 保持函数命名的一致性。
 5.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态

 6.日    期   : 2014年04月4日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause401OtherCause(VOS_VOID)
{
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* 取得当前的注册结果类型  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt  = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    /* 获取CS和PS的additon action，取高优先级的判断是否需要搜网，
       如果不需要发起搜网且Ps counter已经达到最大
       则更新PS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    if (ulAttemptCnt >= NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        enPsAdditionalAction   = NAS_MMC_GetPsAdditionalAction();
        enCsAdditionalAction   = NAS_MMC_GetCsAdditionalAction();

        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }
        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-4, end */

    }

    /* 返回NAS_MMC_ADDITIONAL_ACTION_BUTT，表示无效的AdditionalAction值 */
    return NAS_MMC_ADDITIONAL_ACTION_BUTT;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause402MsCfgDomainNotSupport
 功能描述  : 假流程:Ps/only,当前配置PS only
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数

  2.日    期   : 2012年1月13日
    作    者   : w00167002
    修改内容   : DTS2011122006209:当前在ONPLMN时，若收到结果为PS域不支持，
                  则需要判断1)CS域是否是LIMIT_CAMP_ON 2)AVAILABLE定时器未启动
                             3)CS域准许发起注册,则MMC需要发起搜网
                  对应场景举例:
                  在选网状态机中当前驻留的网络一个域被拒12，一个域#14后，
                  在ON PLMN状态受限驻留，此时用户将注册被拒#12的域DETACH后，
                  由于CS域此时是LIMITED_CAMP_ON，故不发起搜网，而实际需要进行搜网.
  3.日    期   : 2012年2月3日
    作    者   : w00167002
    修改内容   : DTS2011122704039:在注册失败原因值的函数命名中增加原因值，
                  保持函数命名的一致性。
  4.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  5.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  6.日    期   : 2013年11月30日
    作    者   : z00161729
    修改内容   : DTS2013112809149:9230 nv项设置禁止接入技术为w和g，手动搜网模式驻留g的23002成功，
                 syscfg设置w only，anycell驻留24005，会反复触发w下anycell搜网

  7.日    期   : 2014年04月4日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause402MsCfgDomainNotSupport(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_TIMER_STATUS_ENUM_U8                            enAvailableTimerStatus;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    VOS_UINT8                                               ucCsAttachAllow;

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);


    /* 当前在ONPLMN时，若收到结果为PS域不支持，则需要判断是否需要搜网:
       1)CS域是否是LIMIT_CAMP_ON 2)AVAILABLE定时器未启动 3)CS域准许发起注册,则MMC需要发起搜网
    */
    enFsmId                = NAS_MMC_GetCurrFsmId();
    enCsAdditionalAction   = NAS_MMC_GetCsRegAdditionalAction_L1Main();
    enAvailableTimerStatus = NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER);
    ucCsAttachAllow        = NAS_MML_GetCsAttachAllowFlg();

    if ( (NAS_MMC_FSM_L1_MAIN   == enFsmId)
      || (NAS_MMC_FSM_PLMN_LIST == enFsmId) )
    {
        if (VOS_FALSE == NAS_MMC_IsNeedPlmnSearch_RegLocalFailCause())
        {
            return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
        }

        if ( (VOS_TRUE                                  == ucCsAttachAllow)
          && (NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON == enCsAdditionalAction)
          && (NAS_MMC_TIMER_STATUS_STOP                 == enAvailableTimerStatus) )
        {
            return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
        }
    }

    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause403ForbiddenPlmn
 功能描述  : Ps 回复当前驻留在禁止网络的后续处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月12日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年1月4日
    作    者   : w00167002
    修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网.
                在主框架中L1MAIN/PLMN LIST中判断当前原因值为非UE主动发起注册
                原因值，则更新为NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON。现将
                此判断放到各个子函数中来判断。
  3.日    期   : 2012年2月3日
    作    者   : w00167002
    修改内容   : DTS2011122704039:在注册失败原因值的函数命名中增加原因值，
                  保持函数命名的一致性。
  4.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  5.日    期   : 2013年11月30日
    作    者   : z00161729
    修改内容   : DTS2013112809149:9230 nv项设置禁止接入技术为w和g，手动搜网模式驻留
                 g的23002成功，syscfg设置w only，anycell驻留24005，会反复触发w下anycell搜网

  6.日    期   : 2014年04月4日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause403ForbiddenPlmn(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_TIMER_STATUS_ENUM_U8                            enAvailableTimerStatus;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmn     = VOS_NULL_PTR;
    VOS_UINT32                                              ulUserSpecPlmnFlag;
    NAS_MML_PLMN_ID_STRU                                   *pstCurPlmnId        = VOS_NULL_PTR;

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    /* 手动模式判断当前网络是否是用户指定的网络 */
    pstCurPlmnId       = NAS_MML_GetCurrCampPlmnId();
    pstUserSpecPlmn    = NAS_MMC_GetUserSpecPlmnId();
    ulUserSpecPlmnFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurPlmnId,
                                                &(pstUserSpecPlmn->stPlmnId));

    enFsmId = NAS_MMC_GetCurrFsmId();

    switch ( enFsmId )
    {
        case NAS_MMC_FSM_L1_MAIN :
        case NAS_MMC_FSM_PLMN_LIST :

            if (VOS_FALSE == NAS_MMC_IsNeedPlmnSearch_RegLocalFailCause())
            {
                return NAS_MMC_ADDITIONAL_ACTION_BUTT;
            }

            /* 默认返回NAS_MMC_ADDITIONAL_ACTION_BUTT，表示无效的AdditionalAction值 */
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;

            /* 在如下场景需要搜网:手动模式下，当前Plmn不是用户指定的PLMN,且当前PLMN不在EPlmn列表里，
               Available定时器未启动，则认为当前plmn 已经失效了，需要进行搜网 */

            /* 手动模式判断当前网络是否是用户指定的网络 */
            pstCurPlmnId       = NAS_MML_GetCurrCampPlmnId();
            pstUserSpecPlmn    = NAS_MMC_GetUserSpecPlmnId();
            ulUserSpecPlmnFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurPlmnId,
                                                        &(pstUserSpecPlmn->stPlmnId));

            enAvailableTimerStatus = NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER);

            /* 手动模式下，当前Plmn不是用户指定的PLMN,且当前PLMN不在EPlmn列表里，
               则认为当前plmn 已经失效了，Available 定时器未启动，需要进行搜网 */
            if ( (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
              && (VOS_FALSE                          == ulUserSpecPlmnFlag)
              && (NAS_MMC_TIMER_STATUS_STOP          == enAvailableTimerStatus) )
            {
                enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
            }
            break;

        /* 否则需要进行搜网 */
        default:
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
            break;
    }

    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
    /* 只有在下一步需要搜网时，才报状态2上去；不需要搜网时报状态0 */
    if (NAS_MMC_ADDITIONAL_ACTION_BUTT == enAdditionalAction)
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    else
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    return enAdditionalAction;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause404ForbiddenLaForRegPrvsSvs
 功能描述  : Ps Cause404:NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月3日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause404ForbiddenLaForRegPrvsSvs(VOS_VOID)
{
    /* 跟注册被拒原因#12的处理一样 */
    return NAS_MMC_ProcPsRegFailCause12LaNotAllow();
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause405ForbiddenLaForRoam
 功能描述  : 假流程:Ps 13或15号原因值被拒
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月12日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2011年12月21日
    作    者   : w00167002
    修改内容   : DTS2011102100710:注册被拒原因值#13，#15时，都会加入FORB ROAM
                  LA信息列表里，增加被拒原因值的存储，用以区分在LAI上拒绝的原因
                 值。MMC在收到MM/GMM上报拒绝原因值#13,#15的假流程消息时，MMC触发
                 不同的搜网策略。
  3.日    期   : 2012年1月4日
    作    者   : w00167002
    修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网.
                在主框架中L1MAIN/PLMN LIST中判断当前原因值为非UE主动发起注册
                原因值，则更新为NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON。现将
                此判断放到各个子函数中来判断。
  4.日    期   : 2012年2月3日
    作    者   : w00167002
    修改内容   : DTS2011122704039:在注册失败原因值的函数命名中增加原因值，
                  保持函数命名的一致性。
  5.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核

  6.日    期   : 2014年04月4日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause405ForbiddenLaForRoam(VOS_VOID)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause;                              /* 存储注册区CS域被拒信息 */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause;                              /* 存储注册区PS域被拒信息 */

    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */


    /* 当前在ONPLMN或者PLMN LIST状态机，此时处于限制驻留态，在未跟网侧真实发生交互的情况下，
       不更新当前AdditionalAction值 */
    enFsmId = NAS_MMC_GetCurrFsmId();

    if ( (NAS_MMC_FSM_L1_MAIN   == enFsmId)
      || (NAS_MMC_FSM_PLMN_LIST == enFsmId) )
    {
        /* 返回NAS_MMC_ADDITIONAL_ACTION_BUTT，表示无效的AdditionalAction值,MMC
           不更新无效AdditionalAction值 */
        return NAS_MMC_ADDITIONAL_ACTION_BUTT;
    }

    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    /* 当前不在在ONPLMN或者PLMN LIST状态机，需处理拒绝原因值，返回不同的搜网策略 */

    /* 原因值初始化为#13,若发生异常，则进行常规的搜网 */
    enCsCause = NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW;
    enPsCause = NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW;

    NAS_MMC_GetDomainRegStatusInRegInfoList( NAS_MML_GetCurrCampPlmnId(),
                                             NAS_MML_GetCurrNetRatType(),
                                             &enCsCause,
                                             &enPsCause );

    /* 若CS域或者PS域有一个域的原因值为#13,则进行常规的搜网 */
    if ( (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW == enCsCause)
      || (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW == enPsCause))
    {
        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    /* 否则按照拒绝原因值#15的搜网策略进行搜网 */
    return NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;


}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause406ForbiddenPlmnForGprs
 功能描述  : Ps Cause NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月4日
    作    者   : w00167002
    修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网.
                在主框架中L1MAIN/PLMN LIST中判断当前原因值为非UE主动发起注册
                原因值，则更新为NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON。现将
                此判断放到各个子函数中来判断。
  2.日    期   : 2012年2月3日
    作    者   : w00167002
    修改内容   : DTS2011122704039:在注册失败原因值的函数命名中增加原因值，
                  保持函数命名的一致性。
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  4.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态

  5.日    期   : 2014年04月4日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:服务状态上报到mmc
  6.日    期   : 2015年1月14日
    作    者   : b00269685
    修改内容   : 如果有定制的#14的动作，返回NV中定制的动作
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause406ForbiddenPlmnForGprs(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enFailAction;

    /* 添加禁止GPRS PLMN 信息 */
    NAS_MML_AddForbGprsPlmn(NAS_MML_GetCurrCampPlmnId());

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    /* 如果有定制的#14的动作，返回NV中定制的动作 */
    enFailAction = NAS_MMC_GetSingleDomainFailAction(NAS_MML_REG_DOMAIN_PS,
                                                           NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN);
    enFsmId = NAS_MMC_GetCurrFsmId();

    switch ( enFsmId )
    {
        /* 当前在ONPLMN,不更改当前的ADDITIONAL ACTION的值 */
        case NAS_MMC_FSM_L1_MAIN :
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
            break;

        /* 当前在PLMN LIST,不更改当前的ADDITIONAL ACTION的值*/
        case NAS_MMC_FSM_PLMN_LIST :
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
            break;

        /* 否则需要进行可选的搜网 */
        default:
            if (NAS_MMC_ADDITIONAL_ACTION_BUTT == enFailAction)
            {
                enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
            }
            else
            {
                enAdditionalAction = enFailAction;
            }
            break;
    }

    /* 获取CS addition,如果不需要发起搜网则更新PS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
    enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enAdditionalAction, enPrioAdditionalAction);
    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
    else
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    return enAdditionalAction;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause407SimInvalid
 功能描述  : 假流程:当前PS域卡无效
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年1月4日
    作    者   : w00167002
    修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网.
                在主框架中L1MAIN/PLMN LIST中判断当前原因值为非UE主动发起注册
                原因值，则更新为NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON。现将
                此判断放到各个子函数中来判断。

  3.日    期   : 2012年3月1日
    作    者   : z40661
    修改内容   : DTS2012022401628：多次切换无声音
  4.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  5.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  6.日    期   : 2014年4月29日
    作    者   : s00261364
    修改内容   : ecall项目修改服务状态上报
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause407SimInvalid(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    /* 卡存在表示肯定是注册被拒过 */
    if (VOS_TRUE == NAS_MML_GetSimPresentStatus())
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    }
    else
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }


    enFsmId = NAS_MMC_GetCurrFsmId();
    if ( (NAS_MMC_FSM_L1_MAIN == enFsmId)
      || (NAS_MMC_FSM_PLMN_LIST == enFsmId) )
    {
        /* 返回NAS_MMC_ADDITIONAL_ACTION_BUTT，表示无效的AdditionalAction值,MMC
           不更新无效AdditionalAction值 */
        return NAS_MMC_ADDITIONAL_ACTION_BUTT;
    }

    return NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause408NetDetachImsi
 功能描述  : Cs注册失败原因:NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年01月16日
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause408NetDetachImsi(VOS_VOID)
{
    /* 返回无效ACTION值:NAS_MMC_ADDITIONAL_ACTION_BUTT,不更改当前的ADDITIONAL ACTION的值*/
    return NAS_MMC_ADDITIONAL_ACTION_BUTT;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause409ServingCellDomainNotSupport
 功能描述  : 假流程:当前小区不支持PS域
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年1月4日
    作    者   : w00167002
    修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网.
                在主框架中L1MAIN/PLMN LIST中判断当前原因值为非UE主动发起注册
                原因值，则更新为NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON。现将
                此判断放到各个子函数中来判断。
  3.日    期   : 2013年1月31日
    作    者   : t00212959
    修改内容   : DTS2013012909238:手动模式下，单模，一个域注册被#11拒绝，一个域不支持，会循环不停的进行anycell搜网，被拒。
  4.日    期   : 2013年4月1日
    作    者   : w00167002
    修改内容   : DTS2013032701683:无卡开机，系统消息指示PS域不支持，MMC发起循环搜网
  5.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  6.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  7.日    期   : 2013年11月30日
    作    者   : z00161729
    修改内容   : DTS2013112809149:9230 nv项设置禁止接入技术为w和g，手动搜网模式驻留g的23002成功，
                 syscfg设置w only，anycell驻留24005，会反复触发w下anycell搜网
  8.日    期   : 2014年04月4日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:服务状态上报到mmc
  9.日    期   : 2014年5月21日
    作    者   : w00167002
    修改内容   : DTS2014051602857:在SOR打开时候，如果CS注册失败达到4次，则等周期
                搜网定时器超时发起LIST搜网，如果当前仅有原有网络，则发起LAU,否则
                触发MM发起LAU;如果LIST搜后，发现有其他网络，则发起其他网络的搜网注册。
                手动选网时候，返回LIMIT CAMP ON,不再发起选网。
  10.日    期   : 2015年11月24日
     作    者   : w00167002
     修改内容   : DTS2015112405788:在海外测试,如果当前开机CS/PS是无服务，则不上报到
                  MMA，而MMA需要收起CS/PS的服务状态，才给stk下发LOCATION STATUS NTF
                  消息；卡收不到此消息，则不进行IMSI切换。
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause409ServingCellDomainNotSupport(VOS_VOID)
{

    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_TIMER_STATUS_ENUM_U8                            enAvailableTimerStatus;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    /* 更新服务状态 */
    /* Modified by s00261364 for V3R360_eCall项目, 2014-4-10, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by s00261364 for V3R360_eCall项目, 2014-4-10, end */

    enFsmId                = NAS_MMC_GetCurrFsmId();
    enAvailableTimerStatus = NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER);

    if ( (NAS_MMC_FSM_L1_MAIN   == enFsmId)
      || (NAS_MMC_FSM_PLMN_LIST == enFsmId) )
    {
        if (VOS_FALSE == NAS_MMC_IsNeedPlmnSearch_RegLocalFailCause())
        {
            return NAS_MMC_ADDITIONAL_ACTION_BUTT;
        }

        /* 当前AVAILABLE定时器在运行，限制驻留 */
        if ( NAS_MMC_TIMER_STATUS_RUNING               == enAvailableTimerStatus )
        {
            return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
        }


        /* 在L1 MAIN时候，如果当前是无卡，则PS返回不需要搜网 */
        if ( VOS_FALSE == NAS_MML_GetSimPresentStatus() )
        {
            /* 返回NAS_MMC_ADDITIONAL_ACTION_BUTT，表示无效的AdditionalAction值,MMC
                不更新无效AdditionalAction值 */
            return NAS_MMC_ADDITIONAL_ACTION_BUTT;
        }
    }



    enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

    /* SOR打开手动模式搜网时候，返回LIMIT CAMP ON */
    if (VOS_TRUE == NAS_MML_GetCsRejSearchSupportFlg())
    {
        if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
        {
            enAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
        }
    }

    /* 获取CS addition,并与NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION比较，
       如果不需要发起搜网则更新PS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();

    enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enAction, enPrioAdditionalAction);

    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
    else
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    return enAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause419HoSucc
 功能描述  : 注册假流程，切换之后无系统消息的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月13日
    作    者   : s00217060
    修改内容   : Service_State_Optimize_PhaseI:切换流程无系统消息的处理
  2.日    期   : 2015年7月13日
    作    者   : s00217060
    修改内容   : DTS2015070907463:原因值扩展，修改函数名

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause419InterRatChangeSucc(VOS_VOID)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo     = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    enRat               = NAS_MML_GetCurrNetRatType();
    pstCampPlmnInfo     = NAS_MML_GetCurrCampPlmnInfo();

    /* 如果当前主模和驻留信息里的接入技术相同，MMC已经收到接入层上报的系统消息，不用构造系统消息 */
    /* pstCampPlmnInfo->enNetRatType在收到RESUME_IND时更新，pstCampPlmnInfo->stLai.enCampPlmnNetRat在收到系统消息时更新 */
    if (enRat != pstCampPlmnInfo->stLai.enCampPlmnNetRat)
    {
        /* 更新CampPlmnInfo中的Rat值 */
        pstCampPlmnInfo->stLai.enCampPlmnNetRat     = enRat;

        /* 系统子模式用缺省值,切换结束，肯定有主模的，enRat不可能是BUTT */
        if (NAS_MML_NET_RAT_TYPE_GSM == enRat)
        {
            pstCampPlmnInfo->enSysSubMode   = NAS_MML_RRC_SYS_SUBMODE_EDGE;
        }
        else if (NAS_MML_NET_RAT_TYPE_WCDMA == enRat)
        {
            pstCampPlmnInfo->enSysSubMode   = NAS_MML_RRC_SYS_SUBMODE_WCDMA;
        }
        else
        {
            pstCampPlmnInfo->enSysSubMode   = NAS_MML_RRC_SYS_SUBMODE_LTE;
        }

        /* 构造系统消息 */
        NAS_MMC_SndMsccSysInfo();
    }

    /* 通知TAF当前的注册状态 */
    NAS_MMC_ChangePsRegState(NAS_MML_GetPsRegStatus());

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_GetPsServiceStatus());

    /* 返回值并不记录到全局变量，暂定为BUTT，不影响原来的流程 */
    return NAS_MMC_ADDITIONAL_ACTION_BUTT;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCauseAbnormalCause
 功能描述  : Ps 异常原因值的处理
 输入参数  :
             VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年1月17日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCauseAbnormalCause(
    VOS_UINT16                          usCause,
    VOS_UINT32                          ulAttemptCnt
)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;

    /* 注册失败Attempt Counter未达到最大次数 */
    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        /* 注册失败Attempt Counter达到或超过最大次数的处理 */
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes
 功能描述  : Ps注册失败最大次数的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月18日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
 3.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 4.日    期   : 2014年04月4日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc
 5.日    期   : 2014年5月21日
   作    者   : w00167002
   修改内容   : DTS2014051602857:在SOR打开时候，如果CS注册失败达到4次，则等周期
                搜网定时器超时发起LIST搜网，如果当前仅有原有网络，则发起LAU,否则
                触发MM发起LAU;如果LIST搜后，发现有其他网络，则发起其他网络的搜网注册。
                手动选网时候，返回LIMIT CAMP ON,不再发起选网。
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT8                                               ucSingleDomainSrchFlag;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8                  enSelectionMode;

    enSelectionMode = NAS_MMC_GetPlmnSelectionMode();
    /* 更新服务状态 */
    /* Modified by s00261364 for V3R360_eCall项目, 2014-4-10, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by s00261364 for V3R360_eCall项目, 2014-4-10, end */

    /* 单域搜网定制标识 */
    ucSingleDomainSrchFlag = NAS_MML_GetDtSingleDomainPlmnSearchFlag();


    enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

    /* SOR打开手动模式搜网时候，返回LIMIT CAMP ON */
    if ( (VOS_TRUE == NAS_MML_GetCsRejSearchSupportFlg())
      && (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == enSelectionMode) )
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }
    /* 最大次数失败被拒是否立即触发搜网，DT单域搜网定制打开时搜网; 不打开时，等待PS的注册结果 */
    else if (VOS_TRUE == ucSingleDomainSrchFlag)
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }
    else
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    }

    /* 获取CS addition,并与enAction比较，
       如果不需要发起搜网则更新PS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
    enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enAction, enPrioAdditionalAction);
    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
    else
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    return enAction;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes
 功能描述  : Ps注册失败Attempt未达到最大次数的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月18日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2014年3月29日
   作    者   : z00161729
   修改内容   : DTS2014032200128:g下cs only cs域上报的服务状态为限制服务，注册状态上报为驻留home网络，导致界面显示正常但发短信失败
 3.日    期   : 2014年04月4日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc
 4.日    期   : 2014年10月22日
   作    者   : w00167002
   修改内容   : DTS2014101305830:在PLMN改变时候，更新服务状态。
                俄罗斯外场测试:在25002网络的4G上注册成功后，重定向到G下，联合RAU
                失败(ps/cs cause:303),立即更新的服务状态，用户体验不好。第二次RAU
                就成功了。
                关于状态显示优化的功能，SE有进行系统的优化设计方案，当前只针对问题场景
                进行简易优化修改。
 5.日    期   : 2014年11月27日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseI项目修改
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEplmnInfo        = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmn     = VOS_NULL_PTR;
    VOS_UINT32                                              ulInEplmnListFlag;
    VOS_UINT32                                              ulUserSpecPlmnFlag;
    NAS_MML_PLMN_ID_STRU                                   *pstCurPlmnId        = VOS_NULL_PTR;


    NAS_MML_REG_STATUS_ENUM_UINT8       enPsRegStatus;

    enPsRegStatus = NAS_MML_GetPsRegStatus();

    /* 默认设置当前继续等待注册结果 */
    enAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;





    if (NAS_MMC_NORMAL_SERVICE != NAS_MMC_GetCurrPsService())
    {
        /* 更新服务状态 */
        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-10, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
        /* Modified by s00261364 for V3R360_eCall项目, 2014-4-10, end */

        /* 如果ps之前注册成功，位置区改变，注册未达到最大次数，需要将注册状态设置为0 */
        if ((NAS_MML_REG_REGISTERED_HOME_NETWORK == enPsRegStatus)
         || (NAS_MML_REG_REGISTERED_ROAM == enPsRegStatus))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
    }

    /* 自动模式时，直接返回NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT*/
    if ( NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode() )
    {
        return enAction;
    }

    /* 判断当前网络是否是用户指定的网络 */
    pstCurPlmnId       = NAS_MML_GetCurrCampPlmnId();
    pstUserSpecPlmn    = NAS_MMC_GetUserSpecPlmnId();
    ulUserSpecPlmnFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurPlmnId,
                                                &(pstUserSpecPlmn->stPlmnId));

    /* 判断当前网络是否在EPlmn列表里 */
    pstEplmnInfo       = NAS_MML_GetEquPlmnList();

    ulInEplmnListFlag  = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstCurPlmnId,
                                              pstEplmnInfo->ucEquPlmnNum,
                                              pstEplmnInfo->astEquPlmnAddr);

    /* 手动模式下，当前Plmn不是用户指定的PLMN,且当前PLMN不在EPlmn列表里，
       则认为当前plmn 已经失效了，需要进行搜网 */
    if ( (VOS_FALSE == ulUserSpecPlmnFlag)
      && (VOS_FALSE == ulInEplmnListFlag) )
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    }

    return enAction;
}

#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCause3IllegalMs
 功能描述  : 联合注册Combined attach not accepted by the network或者
             Combined TAU not accepted by the network，Eps Cause3的处理
 输入参数  : 无
 输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
             penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月25日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2011年12月17日
    作    者   : w00176964
    修改内容   : V7R1 PhaseIV 调整:注册原因值的处理
  3.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  4.日    期   : 2012年09月15日
    作    者   : z00161729
    修改内容   : DTS2012090708320：MMC收到L的注册结果，ps cs卡是否有效状态需要更新，原来由gmm更新存在时序问题
  5.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  6.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  7.日    期   : 2014年5月5日
    作    者   : w00242748
    修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                 注册状态的上报。
  8.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                 mmc收到COMBINED TAU REJ(#3/6/8),上报注册状态和服务状态
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause3IllegalMs(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* 更新服务状态 */

    /* 设置cs ps卡状态为无效 */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,VOS_FALSE);

    /* 通知TAF当前的服务状态 */

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    /*mmc收到COMBINED TAU/ATTACH REJ(#3/6/8),上报注册状态和服务状态*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS,NAS_MMC_LIMITED_SERVICE);

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCause6IllegalMe
 功能描述  : 联合注册Combined attach not accepted by the network或者
             Combined TAU not accepted by the network，Eps Cause6的处理
 输入参数  : 无
 输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
             penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月25日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause6IllegalMe(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    NAS_MMC_ProcCombinedEpsRegFailCause3IllegalMs(penPsRegAdditionalAction, penCsRegAdditionalAction);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCause7EpsServNotAllow
  功能描述  : 联合注册Combined attach not accepted by the network或者
             Combined TAU not accepted by the network，Eps Cause7的处理
 输入参数  : 无
 输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
             penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月25日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2011年11月30日
    作    者   : w00176964
    修改内容   : V7R1 Phase IV调整:disable/enable 调整
  3.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  4.日    期   : 2012年07月02日
    作    者   : s46746
    修改内容   : For CS/PS mode 1，调整Disable/Enable L,按场景区分函数
  5.日    期   : 2012年7月27日
    作    者   : s00217060
    修改内容   : For CS/PS mode 1,带Disable LTE原因值
  6.日    期   : 2012年09月15日
    作    者   : z00161729
    修改内容  : DTS2012090708320：MMC收到L的注册结果，ps cs卡是否有效状态需要更新，原来由gmm更新存在时序问题
  7.日    期   : 2014年4月29日
    作    者   : s00261364
    修改内容   : ecall项目修改服务状态上报
  8.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                   mmc收到COMBINED TAU REJ(#7),上报注册状态和服务状态

*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause7EpsServNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstRatOrder;

    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    pstRatOrder     = NAS_MML_GetMsPrioRatList();

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,VOS_FALSE);

    /* 设置ps卡状态为无效 */
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    /*紧接着就发起搜网，CS的注册状态就不上报了*/

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, begin */
    /* 更新服务状态 */
    /* Modified by s00261364 for V3R360_eCall项目, 2014-4-29, begin */
    /* 此处不能删，如果删除之后，MMA模块就无法知道是PS域限制服务是因为PS域卡无效导致的。 */
    /* Modified by s00261364 for V3R360_eCall项目, 2014-4-29, end */
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, end */

    /*mmc收到COMBINED TAU REJ(#7),上报注册状态和服务状态,*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS,NAS_MMC_LIMITED_SERVICE);

    /* 判断是否需要disable L */
    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_PsFailCause7PsServNotAllow())
    {
        /* 记录本地disable LTE标记 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_PS_USIM_INVALID);
    }

    /* 如果是L单模被拒原因值7，需要anycell搜网,多模情况需要搜网 */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(pstRatOrder))
    {
        *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
    }
    else
    {
        *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCause8GprsAndNonGprsNotAllow
 功能描述  : 联合注册Combined attach not accepted by the network或者
             Combined TAU not accepted by the network，Eps Cause8的处理
 输入参数  : 无
 输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
             penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月25日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause8GprsAndNonGprsNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    NAS_MMC_ProcCombinedEpsRegFailCause3IllegalMs(penPsRegAdditionalAction, penCsRegAdditionalAction);
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCause9MsidCannotDerivedByNw
 功能描述  : 联合注册Eps Cause9的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月25日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  3.日    期   : 2015年11月19日
    作    者   : c00318887
    修改内容   : DTS2015111701196,ims没注册
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause9MsidCannotDerivedByNw(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCause10ImplicitlyDetached
 功能描述  : 联合注册Eps Cause10的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月25日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  3.日    期   : 2015年11月19日
    作    者   : c00318887
    修改内容   : DTS2015111701196,ims没注册
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause10ImplicitlyDetached(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }
}

/*****************************************************************************
函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCause11PlmnNotAllow
功能描述  : 联合注册Combined attach not accepted by the network或者
            Combined TAU not accepted by the network，Eps Cause11的处理
输入参数  : 无
输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
            penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2011年10月25日
  作    者   : z00161729
  修改内容   : 新生成函数
2.日    期   : 2011年12月17日
  作    者   : w00176964
  修改内容   : V7R1 PhaseIV 调整:注册原因值的处理
3.日    期   : 2012年03月15日
  作    者   : l00130025
  修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
4.日    期   : 2013年3月30日
  作    者   : l00167671
  修改内容   : 主动上报AT命令控制下移至C核
5.日    期   : 2014年5月5日
  作    者   : w00242748
  修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
               注册状态的上报。
6.日    期   : 2015年4月19日
  作    者   : z00161729
  修改内容   : 24301 R11 CR升级项目修改
6.日    期   : 2015年7月1日
  作    者   : c00318887
  修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致

*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause11PlmnNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    NAS_MML_PLMN_ID_STRU               *pstCurPlmnId = VOS_NULL_PTR;

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    pstCurPlmnId = NAS_MML_GetCurrCampPlmnId();

    /* 添加禁止网络信息,有更新时，向Usim更新文件 */
    if (VOS_TRUE == NAS_MMC_IsNeedAddForbPlmn_TauRsltFailCause11PlmnNotAllow())
    {
        if (VOS_TRUE == NAS_MML_AddForbPlmn(pstCurPlmnId))
        {
            NAS_MMC_SndUsimUpdateForbPlmnReq();
        }
    }

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return;
}

/*****************************************************************************
函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCause12TaNotAllow
功能描述  : 联合注册Combined attach not accepted by the network或者
            Combined TAU not accepted by the network，Eps Cause12的处理
输入参数  : 无
输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
            penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2011年10月25日
  作    者   : z00161729
  修改内容   : 新生成函数
2.日    期   : 2011年12月17日
  作    者   : w00176964
  修改内容   : V7R1 PhaseIV 调整:注册原因值的处理
3.日    期   : 2013年3月30日
  作    者   : l00167671
  修改内容   : 主动上报AT命令控制下移至C核
4.日    期   : 2013年05月08日
  作    者   : s46746
  修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
5.日    期   : 2014年5月5日
  作    者   : w00242748
  修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
               注册状态的上报。
6.日    期   : 2015年02月11日
  作    者   : l00305157
  修改内容   : Service_State_Optimize_PhaseII 项目修改
                 mmc收到COMBINED TAU REJ(#12),上报注册状态和服务状态
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause12TaNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION;

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */
    /*mmc收到COMBINED TAU REJ(#12),上报注册状态和服务状态*/
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS,NAS_MMC_LIMITED_SERVICE_REGION);

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
    }
}

/*****************************************************************************
函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCause406ForbiddenPlmnForGprs
功能描述  : 联合注册Combined attach not accepted by the network或者
            Combined TAU not accepted by the network，Eps Cause14的处理
输入参数  : 无
输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
            penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2012年1月4日
  作    者   : w00167002
  修改内容   : 新生成函数
                DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网.
                在主框架中L1MAIN/PLMN LIST中判断当前原因值为非UE主动发起注册
                原因值，在未跟网侧真实发生交互的情况下，不需要进行可选的搜网，
                则更新为NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON。
2.日    期   : 2012年11月15日
  作    者   : w00176964
  修改内容   : DTS2012111404729:cause为14不应该更新服务状态为有区域的限制服务,应该更新为限制服务
3.日    期   : 2013年3月30日
  作    者   : l00167671
  修改内容   : 主动上报AT命令控制下移至C核
4.日    期   : 2014年5月5日
  作    者   : w00242748
  修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
               注册状态的上报。
5.日    期   : 2015年7月1日
  作    者   : c00318887
  修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause406ForbiddenPlmnForGprs(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    /* 当前在ONPLMN或者PLMN LIST状态机，在未跟网侧真实发生交互的情况下，
       返回NAS_MMC_ADDITIONAL_ACTION_BUTT，表示无效的AdditionalAction值，MMC不更新当前ADDITIONAL ACTION的值 */
    enFsmId = NAS_MMC_GetCurrFsmId();

    if ( (NAS_MMC_FSM_L1_MAIN   == enFsmId)
      || (NAS_MMC_FSM_PLMN_LIST == enFsmId) )
    {
        if (NAS_MML_REG_REGISTERED_HOME_NETWORK == NAS_MML_GetPsRegStatus())
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;

        if (NAS_MMC_FSM_L1_MAIN == enFsmId)
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_BUTT);
        }

        return ;
    }
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    /* 当前不在在ONPLMN或者PLMN LIST状态机，需处理拒绝原因值，返回可选的搜网策略 */
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
}


/*****************************************************************************
函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCause13RoamNotAllow
功能描述  : 联合注册Combined attach not accepted by the network或者
            Combined TAU not accepted by the network，Eps Cause12的处理
输入参数  : 无
输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
            penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2011年10月25日
  作    者   : z00161729
  修改内容   : 新生成函数
2.日    期   : 2011年12月17日
  作    者   : w00176964
  修改内容   : V7R1 PhaseIV 调整:注册原因值的处理
3.日    期   : 2012年03月15日
  作    者   : l00130025
  修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
4.日    期   : 2013年3月30日
  作    者   : l00167671
  修改内容   : 主动上报AT命令控制下移至C核
5.日    期   : 2014年5月5日
  作    者   : w00242748
  修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
               注册状态的上报。
6.日    期   : 2015年7月1日
  作    者   : c00318887
  修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause13RoamNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }
}

/*****************************************************************************
函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCause14GprsNotAllowInThisPlmn
功能描述  : 联合注册Combined attach not accepted by the network或者
            Combined TAU not accepted by the network，Eps Cause14的处理
输入参数  : 无
输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
            penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
返 回 值  : 无

调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2011年10月25日
  作    者   : z00161729
  修改内容   : 新生成函数
2.日    期   : 2011年12月17日
  作    者   : w00176964
  修改内容   : V7R1 PhaseIV 调整:注册原因值的处理
3.日    期   : 2013年3月30日
  作    者   : l00167671
  修改内容   : 主动上报AT命令控制下移至C核
4.日    期   : 2014年5月5日
  作    者   : w00242748
  修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
               注册状态的上报
5.日    期   : 2015年1月5日
  作    者   : h00285180
  修改内容   : LTE #14拒绝优化:DTS2015010401946
6.日    期   : 2015年4月19日
  作    者   : z00161729
  修改内容   : 24301 R11 CR升级项目修改
7.日    期   : 2015年7月1日
  作    者   : c00318887
  修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
8.日    期   : 2015年8月13日
  作    者   : l00289540
  修改内容   : User_Exp_Improve

*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause14GprsNotAllowInThisPlmn(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    VOS_UINT8                           ucAllowPsRegWhenEpsRejByCause14;

    ucAllowPsRegWhenEpsRejByCause14     = NAS_MML_GetEpsRejByCause14InVplmnAllowPsRegFlg();

    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));
    /* 添加禁止GPRS PLMN 信息 */
    if (VOS_TRUE == NAS_MMC_IsNeedAddForbGprsPlmn_TauRsltFailCause14GprsNotAllowInThisPlmn())
    {
        if ((VOS_TRUE   == NAS_MMC_IsRoam())
         && (VOS_TRUE   == ucAllowPsRegWhenEpsRejByCause14))
        {
            PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
            stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

            NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                NAS_MML_MAX_TIME_SLICE,
                MMC_LMM_DISABLE_LTE_REASON_BUTT);
        }
        else
        {
            NAS_MML_AddForbGprsPlmn(NAS_MML_GetCurrCampPlmnId());
        }
    }

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    /* 24301_CR1422R1_(Rel-11)_C1-121612 对应24301 5.5.3.3.5和5.5.1.3.5章节:
       A UE operating in CS/PS mode 1 of operation and supporting A/Gb or Iu mode
    may perform a PLMN selection according to 3GPP TS 23.122 [6].
       A UE operating in CS/PS mode 1 of operation and supporting S1 mode only,
    or operating in CS/PS mode 2 of operation shall delete the list of
    equivalent PLMNs and shall perform a PLMN selection according to 3GPP TS 23.122 [6].
    该CR受协议版本控制 */
    if (VOS_TRUE == NAS_MMC_IsNeedDeleteEplmn_CombinedRegRsltFailCause14GprsNotAllowInThisPlmn())
    {
        /* 删除EPLMN */
        NAS_MMC_DeleteEPlmnList();
    }

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_LteRejCause14())
    {
        /* 需要Disable L全局变量 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);
        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_REJ_CAUSE_14);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetLteRejCause14EnableLteTimerLen());

        *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        return;
    }

    /* 24301_CR1499R3_(Rel-11)_C1-123437/ 24301_CR1520R1_(Rel-11)_C1-123939(rev
       of C1-123532)_24.301_Avoid to reselect E-UTRAN for #14/C1-141971拒绝原因
       值14时DISABLE LTE的处理更新,对应24301 5.5.1.3.5和5.5.3.2.5章节描述:
       #14: UE operating in CS/PS mode 1 of operation and supporting A/Gb mode or
            Iu mode may select GERAN or UTRAN radio access technology and proceed
            with the appropriate MM specific procedure according to the MM service state.
            In this case, the UE shall disable the E-UTRA capability (see subclause 4.5)
       该CR受协议版本控制 */
    if ( VOS_TRUE == NAS_MMC_IsNeedDisableL_CombinedAttRsltFailCause14GprsNotAllowInThisPlmn() )
    {
        /* 需要Disable L全局变量 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_REJ_CAUSE_14);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetCsPsMode1EnableLteTimerLen());

        PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
        stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

        if (VOS_TRUE == NAS_MML_IsNeedAddDamPlmnInDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
        {
            NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                          NAS_MML_GetDamDisabledPlmnWithForbiddenPeriodTimeSlice(&stPlmnWithRat),
                                                          MMC_LMM_DISABLE_LTE_REASON_LTE_REJ_CAUSE_14);
        }

        *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        return;
    }

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return;
}

/*****************************************************************************
函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCause15NoSuitableCell
功能描述  : 联合注册Combined attach not accepted by the network或者
            Combined TAU not accepted by the network，Eps Cause15的处理
输入参数  : 无
输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
            penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
返 回 值  : 无

调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2011年10月25日
  作    者   : z00161729
  修改内容   : 新生成函数

2.日    期   : 2011年12月17日
  作    者   : w00176964
  修改内容   : V7R1 PhaseIV 调整:注册原因值的处理
3.日    期   : 2013年3月30日
  作    者   : l00167671
  修改内容   : 主动上报AT命令控制下移至C核
4.日    期   : 2014年5月5日
  作    者   : w00242748
  修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
               注册状态的上报。
5.日    期   : 2015年7月1日
  作    者   : c00318887
  修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause15NoSuitableCell(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
     /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */
     NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
     NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
     NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;


    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCause19EsmFailure
 功能描述  : 联合EPS注册被拒原因: NAS_EMM_CAUSE_ESM_FAILURE的处理
 输入参数  : 无
 输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
              penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月6日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  3.日    期   : 2012年06月07日
    作    者   : s00217060
    修改内容   : #401，尝试次数达到5次，需要Disable L
  5.日    期   : 2012年7月27日
    作    者   : s00217060
    修改内容   : For CS/PS mode 1,带Disable LTE原因值
  6.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  7.日    期   : 2013年6月3日
    作    者   : z00161729
    修改内容   : SVLTE 修改
  8.日    期   : 2014年01月10日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseIII项目
  9.日    期   : 2014年5月5日
    作    者   : w00242748
    修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                 注册状态的上报。
  10.日    期   : 2015年1月15日
     作    者   : z00161729
     修改内容   : AT&T 支持DAM特性修改
  11.日    期   : 2015年4月22日
     作    者   : z00161729
     修改内容   : 24301 R11 CR升级项目修改
  11.日    期   : 2015年7月1日
     作    者   : c00318887
     修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致

*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause19EsmFailure(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    VOS_UINT32                          ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType;

    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    enRegRsltType = NAS_MMC_GetRegRsltType();

    /* 取得Attempt Counter的值 */
    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    /* cs ps域均注册失败,当前不在在ONPLMN或者PLMN LIST状态机，需根据AttemptCounter
       来返回不同的ADDITIONAL ACTION值 */
    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        /* 联合EPS注册失败Attempt未达到最大次数的处理的处理 */
        NAS_MMC_ProcCombinedEpsRegFailAttemptCouterLessThanMaxTimes(penPsRegAdditionalAction,
                                                                    penCsRegAdditionalAction);
    }
    else
    {
        /* 删除EPLMN */
        NAS_MMC_DeleteEPlmnList();

        /* 更新服务状态 */

        /* 通知TAF当前的服务状态 */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

        if ( VOS_TRUE == NAS_MMC_IsNeedDisableL_CombinedRegRsltFailMaxTimes() )
        {
            /* 需要Disable L全局变量 */
            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

            /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-18, begin */
            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
            /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-18, end */

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetCsPsMode1EnableLteTimerLen());

            PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
            stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

            if (VOS_TRUE == NAS_MML_IsNeedAddDamPlmnInDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
            {
                NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                              NAS_MML_GetDamDisabledPlmnWithForbiddenPeriodTimeSlice(&stPlmnWithRat),
                                                              MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
            }

            *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
            *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        }
        else
        {
            *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
            *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
        }

        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCause35RequestedServiceOptionNotAuthorizedInThisPlmn
 功能描述  : 联合注册Eps Cause35的处理
 输入参数  : VOS_VOID
 输出参数  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月6日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年12月24日
    作    者   : w00242748
    修改内容   : DTS2013101106863:L下被拒原因值#35，只有在R10及其协议以上处理才与#11
                 原因值处理相同，否则当做OTHER CAUSE来处理。
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause35ReqServOptNotAuthorizedInThisPlmn(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    NAS_MML_MS_3GPP_REL_STRU                               *pstMs3GppRel = VOS_NULL_PTR;

    pstMs3GppRel = NAS_MML_GetMs3GppRel();
    if ( NAS_MML_3GPP_REL_R9 >= pstMs3GppRel->enLteNasRelease )
    {
        NAS_MMC_ProcCombinedEpsRegFailCauseAbnormalCause(penPsRegAdditionalAction, penCsRegAdditionalAction);
    }
    else
    {
        NAS_MMC_ProcCombinedEpsRegFailCause11PlmnNotAllow(penPsRegAdditionalAction, penCsRegAdditionalAction);
    }

    return;
}


/*****************************************************************************
函 数 名  : NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause16MscNotReachable
功能描述  : 联合注册Combined attach successful for EPS services only或者
            Combined TAU successful for EPS services only，Eps Cause16的处理
输入参数  : 无
输出参数  : 无
返 回 值  : 收到注册结果后，协议要求的cs域的additional动作类型
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2011年10月25日
  作    者   : z00161729
  修改内容   : 新生成函数
2.日    期   : 2012年5月24日
  作    者   : w00166186
  修改内容   : DTS2012052203028,L下出服务区重入服务区，尝试注册5次后，等待注册结果定时器超时后复位
3.日    期   : 2012年06月02日
  作    者   : s00217060
  修改内容   : CS/PS mode 1时，Disable L模, 返回值为NAS_MMC_ADDITIONAL_PLMN_SELECTION
4.日    期   : 2012年7月27日
  作    者   : s00217060
  修改内容   : For CS/PS mode 1,带Disable LTE原因值
5.日    期   : 2013年05月08日
  作    者   : s46746
  修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
6.日    期   : 2013年6月3日
  作    者   : z00161729
  修改内容   : SVLTE 修改
7.日    期   : 2013年12月10日
  作    者   : w00176964
  修改内容   : VoLTE_PhaseIII 项目:修改Disable L模的逻辑
8.日    期   : 2014年3月29日
  作    者   : z00161729
  修改内容   : DTS2014032200128:g下cs only cs域上报的服务状态为限制服务，注册状态上报为驻留home网络，导致界面显示正常但发短信失败

9.日    期   : 2014年5月5日
  作    者   : w00242748
  修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
               注册状态的上报。
10.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 项目修改
                对于EMM的COMBINED TAU/ATTACH(eps only,  cause!=#2/#18)成功，上报CS/PS注册状态和服务状态
 11.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : DTS2015082002854: 漫游标记不准
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause16MscNotReachable(VOS_VOID)
 {
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;


    /* 取得当前的注册结果类型  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    /*对于EMM的COMBINED TAU/ATTACH(eps only,  cause!=#2/#18)成功，上报CS/PS注册状态和服务状态*/
    NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);


    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-12, begin */
    /*
    1)  attemptCount < MaxCount时，返回NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT
    2)  attemptCount >= MaxCount时，返回NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION
    */

    /* ps域注册成功，cs域注册失败 */
    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {

        /* 与GU保持一致,通过判断服务状态来决定是否更新注册状态和服务状态，*/
        if (NAS_MMC_NORMAL_SERVICE != NAS_MMC_GetCurrCsService())
        {
             /* 更新注册状态为0 */
             NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
             NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
        }

        return NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
    }
    else
    {
        /* 更新服务状态 */

        /* 通知TAF当前的服务状态 */
        /*对于EMM的COMBINED TAU(eps only,  cause!=#2/#18)成功,且达到最大次数，上报CS/PS注册状态和服务状态*/
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);

        return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    }
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-12, end */


}

/*****************************************************************************
函 数 名  : NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause17NetworkFailure
功能描述  : 联合注册Combined attach successful for EPS services only或者
            Combined TAU successful for EPS services only，Eps Cause17的处理
输入参数  : 无
输出参数  : 无
返 回 值  : 收到注册结果后，协议要求的cs域的additional动作类型
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2011年10月25日
作    者   : z00161729
修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause17NetworkFailure(VOS_VOID)
{
    return NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause16MscNotReachable();
}


/*****************************************************************************
函 数 名  : NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause22Congestion
功能描述  : 联合注册Combined attach successful for EPS services only或者
            Combined TAU successful for EPS services only，Eps Cause22的处理
输入参数  : 无
输出参数  : 无
返 回 值  : 收到注册结果后，协议要求的cs域的additional动作类型
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2011年10月25日
  作    者   : z00161729
  修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause22Congestion(VOS_VOID)
{
    return NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause16MscNotReachable();
}

/*****************************************************************************
函 数 名  : NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause18CsDomainNotAvailable
功能描述  : 联合注册Combined attach successful for EPS services only或者
            Combined TAU successful for EPS services only，Eps Cause18的处理
输入参数  : 无
输出参数  : 无
返 回 值  : 收到注册结果后，协议要求的cs域的additional动作类型
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2011年10月25日
  作    者   : z00161729
  修改内容   : 新生成函数
2.日    期   : 2012年06月07日
  作    者   : s00217060
  修改内容   : CS/PS mode 1时，Disable L模, 返回值为NAS_MMC_ADDITIONAL_PLMN_SELECTION
3.日    期   : 2012年7月27日
  作    者   : s00217060
  修改内容   : For CS/PS mode 1,带Disable LTE原因值
4.日    期   : 2013年3月30日
  作    者   : l00167671
  修改内容   : 主动上报AT命令控制下移至C核
5.日    期   : 2013年05月08日
  作    者   : s46746
  修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
6.日    期   : 2013年12月10日
  作    者   : w00176964
  修改内容   : VoLTE_PhaseIII 项目:修改Disable L模的逻辑
7.日    期   : 2015年02月11日
  作    者   : l00305157
  修改内容   : Service_State_Optimize_PhaseII 项目修改
               对于EMM的COMBINED TAU/ATTACH(eps only,  cause=#18)成功，上报CS/PS注册状态和服务状态
  8.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : DTS2015082002854: 漫游标记不准
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause18CsDomainNotAvailable(VOS_VOID)
{
    /* 删除LTE上报服务状态和注册状态的接口*/

    /* 通知TAF当前的服务状态 */


    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-12, begin */
    /* 通知TAF当前的服务状态 */
    /* Added by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    /* 删除LTE上报服务状态和注册状态的接口*/


    /*对于EMM的COMBINED TAU/ATTACH(eps only,  cause=#18)成功，上报CS/PS注册状态和服务状态*/
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);

    NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);

    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-12, end */

}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause2ImsiUnknownInHss
 功能描述  : 联合注册Combined attach successful for EPS services only或者
             Combined TAU successful for EPS services only，Eps Cause2的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 收到注册结果后，协议要求的cs域的additional动作类型
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月25日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年09月15日
    作    者   : z00161729
    修改内容   : DTS2012090708320：MMC收到L的注册结果，ps cs卡是否有效状态需要更新，原来由gmm更新存在时序问题
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  4.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  5.日    期   : 2014年5月5日
    作    者   : w00242748
    修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                 注册状态的上报。
  6.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                 对于EMM的COMBINED TAU/ATTACH(eps only,  cause=#2)成功，上报CS/PS注册状态和服务状态
  7.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : DTS2015082002854: 漫游标记不准
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause2ImsiUnknownInHss(VOS_VOID)
{

    /* 删除LTE上报服务状态和注册状态的接口*/


    /* 设置cs卡状态为无效 */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);

    /* 删除LTE上报服务状态和注册状态的接口*/

    /*对于EMM的COMBINED TAU/ATTACH(eps only,  cause=#2)成功，上报CS/PS注册状态和服务状态*/
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);

    NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);

    return NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
}


/*****************************************************************************
函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCause257AccessBarrd
功能描述  : Eps Cause access bar的处理
输入参数  : VOS_VOID
输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
            penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2011年10月25日
  作    者   : z00161729
  修改内容   : 新生成函数
2.日    期   : 2011年12月17日
  作    者   : w00176964
  修改内容   : V7R1 PhaseIV 调整:注册原因值的处理
3.日    期   : 2012年1月4日
  作    者   : w00167002
  修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网.
                在主框架中L1MAIN/PLMN LIST中判断当前原因值为非UE主动发起注册
                原因值，则更新为NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON。现将
                此判断放到各个子函数中来判断。
4.日    期   : 2013年3月30日
  作    者   : l00167671
  修改内容   : 主动上报AT命令控制下移至C核
5.日    期   : 2013年05月08日
  作    者   : s46746
  修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
6.日    期   : 2013年10月15日
  作    者   : s00190137
  修改内容   : 特性开关打开且非HPLMN/RPLMN接入禁止时需要触发PLMN搜网
7.日    期   : 2014年5月5日
  作    者   : w00242748
  修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
               注册状态的上报。

8.日    期   : 2015年1月23日
  作    者   : w00167002
  修改内容   : DTS2015020309124:via控制L下搜网注册时候，L下ACCESS BAR，后续
                选网结束后，L自己触发了注册。VIA无法配合，MODEM进行配合修改。
                修改为在注册状态收到ACCESS BAR后，继续等待L的注册结果。
9.日    期   : 2015年02月11日
  作    者   : l00305157
  修改内容   : Service_State_Optimize_PhaseII 项目修改
               MMC收到LMM ATTACH结果中，携带ACCESS BAR场景，
                       服务状态:CS域上报NAS_MMC_NO_SERVICE，PS域上报NAS_MMC_LIMITED_SERVICE, CS域和PS域注册状态上报0。
               MMC收到LMM TAU结果中，携带ACCESS BAR场景，
                       CS域和PS域服务状态,CS域和PS域注册状态不改变
 10.日    期   : 2015年11月24日
   作    者   : w00167002
   修改内容   : DTS2015112405788:在海外测试,如果当前开机CS/PS是无服务，则不上报到
                MMA，而MMA需要收起CS/PS的服务状态，才给stk下发LOCATION STATUS NTF
                消息；卡收不到此消息，则不进行IMSI切换。
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause257AccessBarrd(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_REG_RSLT_CTX_STRU          *pstRegRsltCtx = VOS_NULL_PTR;

    /* 获取当前的注册结果消息类型 */
    pstRegRsltCtx   = NAS_MMC_GetRegRsltCtxAddr();

    enFsmId         = NAS_MMC_GetCurrFsmId();

    if (NAS_FSM_BUTT <= enFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }


     /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    /* 更新服务状态 */


    if (LMM_MMC_ATTACH_IND  == pstRegRsltCtx->enRegRsltType)
    {
        /*MMC收到LMM ATTACH结果中，携带ACCESS BAR场景，
        服务状态:CS域上报NAS_MMC_NO_SERVICE，PS域上报NAS_MMC_LIMITED_SERVICE, CS域和PS域注册状态上报0*/
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS,NAS_MMC_LIMITED_SERVICE);

        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS,NAS_MMC_LIMITED_SERVICE);
    }
    else
    {
    }



    /*特性开关打开且非HPLMN/RPLMN接入禁止时需要触发PLMN搜网*/

    if (VOS_TRUE == NAS_MMC_IsAccBarPlmnSearch())
    {
        *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }

        return;
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }

    /* 当前CL互操作时如果ACCEESBARRED,则继续等待注册结果，否则后续解BAR,L发起注册，VIA无法配合 */
    if ( (NAS_MMC_REG_CONTROL_BY_3GPP2_CBP  == NAS_MMC_GetRegCtrl())
      && (NAS_MMC_FSM_PLMN_SELECTION        == enFsmId) )
    {
        *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;

        return;
    }

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED;
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED;

    return;


}

/*****************************************************************************
函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCauseAuthRej
功能描述  : Eps Cause auth rej的处理
输入参数  : VOS_VOID
输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
            penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2011年10月25日
  作    者   : z00161729
  修改内容   : 新生成函数
2.日    期   : 2011年12月17日
  作    者   : w00176964
  修改内容   : V7R1 PhaseIV 调整:注册原因值的处理
3.日    期   : 2012年03月15日
  作    者   : l00130025
  修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
4.日    期   : 2012年09月15日
  作    者   : z00161729
  修改内容   : DTS2012090708320：MMC收到L的注册结果，ps cs卡是否有效状态需要更新，原来由gmm更新存在时序问题
5.日    期   : 2013年3月30日
  作    者   : l00167671
  修改内容   : 主动上报AT命令控制下移至C核
6.日    期   : 2013年05月08日
  作    者   : s46746
  修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
7.日    期   : 2014年5月5日
  作    者   : w00242748
  修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
               注册状态的上报。
8.日    期   : 2015年02月11日
  作    者   : l00305157
  修改内容   : Service_State_Optimize_PhaseII 项目修改
               在COMBINEDTAU过程中，mmc收到鉴权拒绝,上报注册状态和服务状态
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause256AuthRej(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* 更新服务状态 */

    /* 设置cs ps卡状态为无效 */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);

    /*在COMBINEDTAU过程中，mmc收到鉴权拒绝,上报注册状态和服务状态*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);


    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;

    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCause301TimerTimeOut
 功能描述  : ps Cause:NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT 的处理
 输入参数  :
             VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月18日
   作    者   : w00167002
   修改内容   : 新生成函数。
 2.日    期   : 2012年03月15日
   作    者   : l00130025
   修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
 3.日    期   : 2012年06月07日
   作    者   : s00217060
   修改内容   : #301，尝试次数达到5次，需要Disable L
 4.日    期   : 2012年7月27日
   作    者   : s00217060
   修改内容   : For CS/PS mode 1,带Disable LTE原因值
 5.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
 6.日    期   : 2013年6月3日
   作    者   : z00161729
   修改内容   : SVLTE 修改
 7.日    期   : 2014年5月5日
   作    者   : w00242748
   修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                注册状态的上报。
 8.日    期   : 2015年1月15日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改
 9.日    期   : 2015年4月22日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
 9.日    期   : 2015年7月1日
   作    者   : c00318887
   修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致

*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause301TimerTimeOut(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction
)
{
    VOS_UINT32                          ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType;

    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    /* 取得当前的注册结果消息类型 */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType );

    /* cs ps域均注册失败,当前不在在ONPLMN或者PLMN LIST状态机，需根据AttemptCounter
       来返回不同的ADDITIONAL ACTION值 */
    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        /* EPS联合注册失败Attempt Counter未达到最大失败次数的处理 */
        NAS_MMC_ProcCombinedEpsRegFailAttemptCouterLessThanMaxTimes(penPsRegAdditionalAction,
                                                                    penCsRegAdditionalAction);
    }
    else
    {
        /* 删除EPLMN */
        NAS_MMC_DeleteEPlmnList();

        /* 更新服务状态 */

        /* 通知TAF当前的服务状态 */

        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

        if ( VOS_TRUE == NAS_MMC_IsNeedDisableL_CombinedRegRsltFailMaxTimes() )
        {
            /* 需要Disable L全局变量 */
            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

            /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-18, begin */
            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
            /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-18, end */

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetCsPsMode1EnableLteTimerLen());

            PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
            stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

            if (VOS_TRUE == NAS_MML_IsNeedAddDamPlmnInDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
            {
                NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                              NAS_MML_GetDamDisabledPlmnWithForbiddenPeriodTimeSlice(&stPlmnWithRat),
                                                              MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);

            }

            *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
            *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        }
        else
        {
            *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
            *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
        }

        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }
    }
    return;
}

/*****************************************************************************
函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCause403ForbiddenPlmn
功能描述  : Eps Cause forbidden plmn的处理
输入参数  : VOS_VOID
输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
            penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2011年10月25日
  作    者   : z00161729
  修改内容   : 新生成函数

2.日    期   : 2011年12月17日
  作    者   : w00176964
  修改内容   : V7R1 PhaseIV 调整:注册原因值的处理

3.日    期   : 2012年1月4日
  作    者   : w00167002
  修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网.
                在主框架中L1MAIN/PLMN LIST中判断当前原因值为非UE主动发起注册
                原因值，则更新为NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON。现将
                此判断放到各个子函数中来判断。
4.日    期   : 2013年3月30日
  作    者   : l00167671
  修改内容   : 主动上报AT命令控制下移至C核
5.日    期   : 2014年5月5日
  作    者   : w00242748
  修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
               注册状态的上报。
6.日    期   : 2015年7月1日
  作    者   : c00318887
  修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause403ForbiddenPlmn(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);

    /* 当前在ONPLMN或者PLMN LIST状态机，则返回当为NAS_MMC_ADDITIONAL_ACTION_BUTT */
    enFsmId = NAS_MMC_GetCurrFsmId();

    if ( (NAS_MMC_FSM_L1_MAIN   == enFsmId)
      || (NAS_MMC_FSM_PLMN_LIST == enFsmId) )
    {
        if (NAS_MML_REG_REGISTERED_HOME_NETWORK == NAS_MML_GetPsRegStatus())
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;

        if (NAS_MMC_FSM_L1_MAIN == enFsmId)
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_BUTT);
        }

        return ;
    }
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    /* 当前不在在ONPLMN或者PLMN LIST状态机，则需进行搜网 */
    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
}

/*****************************************************************************
函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCause404ForbiddenTaForRegPrvsSvs
功能描述  : 联合注册Combined attach not accepted by the network或者
            Combined TAU not accepted by the network，Eps MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS 的处理
输入参数  : 无
输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
            penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :

1.日    期   : 2012年2月4日
  作    者   : w00167002
  修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause404ForbiddenTaForRegPrvsSvs(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    /* 跟联合注册失败原因值#12的处理一致 */
    NAS_MMC_ProcCombinedEpsRegFailCause12TaNotAllow(penPsRegAdditionalAction,
                                                    penCsRegAdditionalAction);
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCause405ForbiddenLaForRoam
 功能描述  : 假流程:Ps 13或15号原因值被拒
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION :拒绝原因值#13的搜网策略
             NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN:拒绝原因值#15的搜网策略

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月29日
    作    者   : w00167002
    修改内容   : 新生成函数
                 DTS2011102200381:L下注册被拒#12,LMM给MMC带的TAU
                 中的结果为MMC_LMM_TAU_RSLT_FORBID_PLMNS，MMC收到此结果后按照禁止网络
                 来处理而发起了搜网。
                 MMC区分当前是#13还是#15，而进行不同的搜网动作。
 2.日    期   : 2012年1月4日
   作    者   : w00167002
   修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网.
                  在主框架中L1MAIN/PLMN LIST中判断当前原因值为非UE主动发起注册
                  原因值，则更新为NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON。现将
                  此判断放到各个子函数中来判断。
 3.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
 4.日    期   : 2014年5月5日
   作    者   : w00242748
   修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                注册状态的上报。
 5.日    期   : 2015年7月1日
   作    者   : c00318887
   修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause405ForbiddenLaForRoam(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction
)
{
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause;                              /* 存储注册区CS域被拒信息 */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause;                              /* 存储注册区PS域被拒信息 */

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);

    /* 当前在ONPLMN或者PLMN LIST状态机，在未跟网侧真实发生交互的情况下，
       返回NAS_MMC_ADDITIONAL_ACTION_BUTT，表示无效的AdditionalAction值，MMC不更新当前ADDITIONAL ACTION的值 */
    enFsmId = NAS_MMC_GetCurrFsmId();

    if ( (NAS_MMC_FSM_L1_MAIN   == enFsmId)
      || (NAS_MMC_FSM_PLMN_LIST == enFsmId) )
    {
        if (NAS_MML_REG_REGISTERED_HOME_NETWORK == NAS_MML_GetPsRegStatus())
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;

        if (NAS_MMC_FSM_L1_MAIN == enFsmId)
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_BUTT);
        }

        return ;
    }

    /* 当前不在在ONPLMN或者PLMN LIST状态机，需处理拒绝原因值，返回不同的搜网策略 */

    /* 原因值初始化为#13,若发生异常，则按照#13进行常规的搜网 */
    enCsCause = NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW;
    enPsCause = NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW;

    NAS_MMC_GetDomainRegStatusInRegInfoList( NAS_MML_GetCurrCampPlmnId(),
                                             NAS_MML_GetCurrNetRatType(),
                                             &enCsCause,
                                             &enPsCause );
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    /* 若CS域或者PS域有一个域的原因值为#13,则进行常规的搜网 */
    if ( (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW == enCsCause)
      || (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW == enPsCause))
    {
        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        return ;
    }

    /* 否则按照拒绝原因值#15的搜网策略进行搜网 */
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;
    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;

    return;
}
/*****************************************************************************
函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCausePsAttachNotAllow
功能描述  : Eps Cause ps attach not allow的处理
输入参数  : VOS_VOID
输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
            penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2011年12月25日
  作    者   : z00161729
  修改内容   : 新生成函数
2.日    期   : 2013年3月30日
  作    者   : l00167671
  修改内容   : 主动上报AT命令控制下移至C核
3.日    期   : 2014年5月5日
  作    者   : w00242748
  修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
               注册状态的上报。
4.日    期   : 2015年7月1日
  作    者   : c00318887
  修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCausePsAttachNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
    }
}

/*****************************************************************************
函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCause40NoEpsBearerActived
功能描述  : Eps Cause 40的处理
输入参数  : VOS_VOID
输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
            penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2011年1月8日
  作    者   : z00161729
  修改内容   : 新生成函数
2.日    期   : 2012年03月15日
  作    者   : l00130025
  修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  3.日    期   : 2015年11月19日
    作    者   : c00318887
    修改内容   : DTS2015111701196,ims没注册
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause40NoEpsBearerActived(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }

    return;
}

/*****************************************************************************
函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCauseEpsBearerEstFail
功能描述  : Eps Cause ESM承载建立失败的处理
输入参数  : VOS_VOID
输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
            penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2011年1月8日
  作    者   : z00161729
  修改内容   : 新生成函数
2.日    期   : 2013年3月30日
  作    者   : l00167671
  修改内容   : 主动上报AT命令控制下移至C核
3.日    期   : 2014年5月5日
  作    者   : w00242748
  修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
               注册状态的上报。
4.日    期   : 2015年7月1日
  作    者   : c00318887
  修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCauseEpsBearerEstFail(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return;
}

/*****************************************************************************
函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCauseMoDetach
功能描述  : Eps Cause Mo detach的处理
输入参数  : VOS_VOID
输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
            penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2011年1月8日
  作    者   : z00161729
  修改内容   : 新生成函数
2.日    期   : 2012年06月27日
  作    者   : s46746
  修改内容   : For CS/PS mode 1，整理注册过程中用户进行Detach操作
3.日    期   : 2013年3月30日
  作    者   : l00167671
  修改内容   : 主动上报AT命令控制下移至C核
4.日    期   : 2014年5月5日
  作    者   : w00242748
  修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
               注册状态的上报。
5.日    期   : 2014年07月26日
  作    者   : s00217060
  修改内容   : DTS2014051501744:TAU过程中用户detach,LMM会给MMC回MO_DETACH_FAILURE,
               MMC收到该TAU结果会触发搜网，搜网前要求主动释放链接，导致detach_req发不上去
6.日    期   : 2015年7月1日
  作    者   : c00318887
  修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCauseMoDetach(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

    /* attach/tau过程中用户detach,LMM会给MMC回MO_DETACH_FAILURE,
       MMC收到该attach/tau结果会触发搜网，搜网前要求主动释放链接，导致detach_req发不上去
       所以此处修改为限制驻留 */
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;


    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }

    return;
}


/*****************************************************************************
函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCauseMtDetach
功能描述  : Eps Cause Mt detach的处理
输入参数  : VOS_VOID
输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
            penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2011年1月8日
  作    者   : z00161729
  修改内容   : 新生成函数
2.日    期   : 2013年3月30日
  作    者   : l00167671
  修改内容   : 主动上报AT命令控制下移至C核
3.日    期   : 2014年5月5日
  作    者   : w00242748
  修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
               注册状态的上报。
4.日    期   : 2015年7月1日
  作    者   : c00318887
  修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCauseMtDetach(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCause42SevereNetworkFailure
 功能描述  : 联合注册Eps Cause #42的处理
 输入参数  : VOS_VOID
 输出参数  : penPsRegAdditionalAction - ps域additional action
             penCsRegAdditionalAction - cs域additional action
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月19日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause42SevereNetworkFailure(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    NAS_MML_3GPP_REL_ENUM_UINT8        enLteRelVersion;
    NAS_MML_PLMN_WITH_RAT_STRU         stPlmnWithRat;

    enLteRelVersion = NAS_MML_GetLte3gppRelVersion();
    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));

    /* 协议版本小于R11按other cause处理 */
    if ( NAS_MML_3GPP_REL_R11 > enLteRelVersion)
    {
        NAS_MMC_ProcCombinedEpsRegFailCauseAbnormalCause(penPsRegAdditionalAction, penCsRegAdditionalAction);
        return;
    }

    /* 24301_CR1473R2_(Rel-11)_C1-123386 MMC增加ATTACH、TAU和SERVICE REQUEST过程中被拒原因值42的处理
    24301 5.5.1.3.5和5.5.3.3.5章节描述:
       The UE shall set the EPS update status to EU2 NOT UPDATED, and shall delete
    any GUTI, last visited registered TAI, eKSI, and list of equivalent PLMNs,
    and set the attach attempt counter to 5. The UE shall start an implementation
    specific timer, setting its value to 2 times the value of T as defined in 3GPP
    TS 23.122 [6]. While this timer is running, the UE shall not consider the
    PLMN + RAT combination that provided this reject cause, a candidate for PLMN
    selection. The UE then enters state EMM-DEREGISTERED.PLMN-SEARCH in order to
    perform a PLMN selection according to 3GPP TS 23.122 [6].
        If A/Gb mode or Iu mode is supported by the UE, the UE shall in addition
    set the GMM state to GMM-DEREGISTERED, GPRS update status to GU2 NOT UPDATED,
    and shall delete the P-TMSI, P-TMSI signature, RAI and GPRS ciphering key
    sequence number. 该CR受协议版本控制 */
    PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
    stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

    /* 将被拒#42的网络加入禁止接入技术网络列表中，禁止时间为2*T,触发搜网 */
    NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                  NAS_MML_GetDisabledPlmnRejCause42ForbiddenTimeSlice(),
                                                  MMC_LMM_DISABLE_LTE_REASON_BUTT);

    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return;
}


/*****************************************************************************
函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCauseT3402Running
功能描述  : Eps Cause T3402定时器在运行的处理
输入参数  : VOS_VOID
输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
            penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2011年1月8日
  作    者   : z00161729
  修改内容   : 新生成函数
2.日    期   : 2013年1月31日
  作    者   : t00212959
  修改内容   : DTS2013012909238:anycell搜网，3402在运行，不等available超时，就又发起了搜网。
3.日    期   : 2013年3月30日
  作    者   : l00167671
  修改内容   : 主动上报AT命令控制下移至C核
4.日    期   : 2014年5月5日
  作    者   : w00242748
  修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
               注册状态的上报。
5.日    期   : 2015年7月1日
  作    者   : c00318887
  修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCauseT3402Running(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_TIMER_STATUS_ENUM_U8                            enAvailableTimerStatus;

    enFsmId                = NAS_MMC_GetCurrFsmId();
    enAvailableTimerStatus = NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER);


    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    /* 当前在ONPLMN时，AVAILABLE定时器未启动,则MMC需要发起搜网*/
    if ( NAS_MMC_FSM_L1_MAIN   == enFsmId)
    {
        if (NAS_MMC_TIMER_STATUS_RUNING == enAvailableTimerStatus)
        {
            *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
            *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);

            return;
        }

        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    return;
}


/*****************************************************************************
函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCauseT3402RunningEpsOnlySucc
功能描述  : Eps Cause T3402定时器在运行且PS normal service的处理
输入参数  : enRegRsltType - 当前的注册结果消息类型
            pstLmmTauIndMsg - LMM_MMC_TAU_RESULT_IND消息指针
输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
            penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
  1.日    期   : 2015年11月30日
    作    者   : c00318887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCauseT3402RunningEpsOnlySucc(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType,
    LMM_MMC_TAU_RESULT_IND_STRU                            *pstLmmTauIndMsg,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction
)
{
    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_EPS_ONLY_ATTACH);

    NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
    NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_NORMAL_CAMP_ON);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsAttachRegFailCause3IllegalMs
 功能描述  : Eps Cause3的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月7日
    作    者   : l00130025
    修改内容   : 新生成函数

  2.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : DTS2011121307570: MMC没有维护LMM的EPLMN信息，现在统一调整
                  ATTACH/TAU/DETACH/SERVICE中被拒时EPLMN的维护。
  3.日    期   : 2011年12月30日
    作    者   : l65478
    修改内容   : 在迁到L模时,不立刻把CS设置成可选搜网,而是等待PS注册结果时
                 根据具体的原因值再设置

  4.日    期   : 2012年2月15日
    作    者   : z40661
    修改内容   : DTS2011121405203_PC测试发现问题,支持gUL多模时,L下被#3拒绝,到GU下指定搜网
  5.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  6.日    期   : 2012年09月15日
    作    者   : z00161729
    修改内容  : DTS2012090708320：MMC收到L的注册结果，ps cs卡是否有效状态需要更新，原来由gmm更新存在时序问题
  7.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  8.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  9.日    期   : 2014年4月29日
    作    者   : s00261364
    修改内容   : ecall项目修改服务状态上报
 10.日    期   : 2014年5月5日
    作    者   : w00242748
    修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                 注册状态的上报。
 11.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause3IllegalMs(VOS_VOID)
{

    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* 更新服务状态 */

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,VOS_FALSE);

    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, begin */
    /* 先更新全局变量,便于发送消息时全局变量时最新的 */
    /* 设置cs ps卡状态为无效 */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    /* 通知TAF当前的服务状态 */
    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, end */

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);

    /*更新PS域注册状态，并上报服务状态*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }


    /* modified by z40661 for DTS2011121405203_PC测试发现问题, 2012-02-15, begin */
    return NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;

    /* modified by l65478 for DTS2011121405203_PC测试发现问题, 2012-02-15, end */

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsAttachRegFailCause6IllegalMe
 功能描述  : Eps Cause6的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月7日
    作    者   : l00130025
    修改内容   : 新生成函数

  2.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : DTS2011121307570: MMC没有维护LMM的EPLMN信息，现在统一调整
                  ATTACH/TAU/DETACH/SERVICE中被拒时EPLMN的维护。

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause6IllegalMe(VOS_VOID)
{

    return NAS_MMC_ProcEpsAttachRegFailCause3IllegalMs();

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsAttachRegFailCause7EpsServNotAllow
 功能描述  : Eps Cause7的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数

  2.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : DTS2011121307570: MMC没有维护LMM的EPLMN信息，现在统一调整
                  ATTACH/TAU/DETACH/SERVICE中被拒时EPLMN的维护。

  3.日    期   : 2011年12月30日
    作    者   : l65478
    修改内容   : 在迁到L模时,不立刻把CS设置成可选搜网,而是等待PS注册结果时
                 根据具体的原因值再设置
  4.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环

  5.日    期   : 2012年4月4日
    作    者   : z40661
    修改内容   : 问题单号DTS2012032803448，PS oNLY时，需要在L模下进行ANYCELL
                 搜网。
  6.日    期   : 2012年7月4日
    作    者   : s46746
    修改内容   : for V7R1 cS/PS mode 1, 原因值#7时，需要设置Disable LTE全局变量
  7.日    期   : 2012年7月27日
    作    者   : s00217060
    修改内容   : For CS/PS mode 1,带Disable LTE原因值
  8.日    期   : 2012年09月15日
    作    者   : z00161729
    修改内容   : DTS2012090708320：MMC收到L的注册结果，ps cs卡是否有效状态需要更新，原来由gmm更新存在时序问题
  9.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
 10.日    期   : 2014年4月29日
    作    者   : s00261364
    修改内容   : ecall项目修改服务状态上报
 11.日    期   : 2014年5月5日
    作    者   : w00242748
    修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                 注册状态的上报。
 12.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause7EpsServNotAllow(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatOrder;
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;

    pstRatOrder     = NAS_MML_GetMsPrioRatList();


    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* 更新服务状态 */

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,VOS_FALSE);

    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, begin */
    /* 设置ps卡状态为无效 */
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);


    /*MMC接收到LMM模块注册结果(EPS ONLY)，casue=#7, 更新PS域注册状态，并上报服务状态*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);


    /* 通知TAF当前的服务状态 */
    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, end */

    /* 判断是否需要disable L */
    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_PsFailCause7PsServNotAllow())
    {
        /* 记录本地disable LTE标记 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_PS_USIM_INVALID);
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }

    /* 如果是L单模被拒原因值7，需要anycell搜网,多模情况需要搜网 */
    /* L模下PS ONLY时也需要进行anycell搜网 */
    enMsMode    =    NAS_MML_GetMsMode();
    if ( (VOS_TRUE == NAS_MML_IsLteOnlyMode(pstRatOrder))
      || (NAS_MML_MS_MODE_PS_ONLY == enMsMode))
    {
        return NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
    }
    else
    {
        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsAttachRegFailCause8GprsAndNonGprsNotAllow
 功能描述  : Eps Cause8的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月7日
    作    者   : l00130025
    修改内容   : 新生成函数

  2.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : DTS2011121307570: MMC没有维护LMM的EPLMN信息，现在统一调整
                  ATTACH/TAU/DETACH/SERVICE中被拒时EPLMN的维护。

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause8GprsAndNonGprsNotAllow(VOS_VOID)
{

    return NAS_MMC_ProcEpsAttachRegFailCause3IllegalMs();

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsAttachRegFailCause11PlmnNotAllow
 功能描述  : Eps Cause11的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年08月05日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  4.日    期   : 2014年5月5日
    作    者   : w00242748
    修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                 注册状态的上报。
  5.日    期   : 2015年7月1日
    作    者   : c00318887
    修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause11PlmnNotAllow(VOS_VOID)
{
    NAS_MML_PLMN_ID_STRU               *pstCurPlmnId;

    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    pstCurPlmnId = NAS_MML_GetCurrCampPlmnId();

    /* 添加禁止网络信息,有更新时，向Usim更新文件 */
    if (VOS_TRUE == NAS_MML_AddForbPlmn(pstCurPlmnId))
    {
        NAS_MMC_SndUsimUpdateForbPlmnReq();
    }

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsAttachRegFailCause12TaNotAllow
 功能描述  : Eps Cause12的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月7日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  3.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  4.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause12TaNotAllow(VOS_VOID)
{
    VOS_UINT8                           ucSimCsRegStatus;

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    /*MMC接收到LMM模块注册结果(EPS ONLY)，casue=#12, 更新PS域注册状态为0，并上报服务状态2*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE_REGION);

    /* 如果CS允许注册而且CS卡有效则更改CS注册状态为NAS_MMC_LIMITED_SERVICE_REGION */
    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (VOS_TRUE == ucSimCsRegStatus))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE_REGION);

    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
    }

    return NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsAttachRegFailCause13RoamNotAllow
 功能描述  : Eps Cause13的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月7日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  4.日    期   : 2014年5月5日
    作    者   : w00242748
    修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                 注册状态的上报。
  5.日    期   : 2015年7月1日
    作    者   : c00318887
    修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause13RoamNotAllow(VOS_VOID)
{
    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsAttachRegFailCause14GprsNotAllowInThisPlmn
 功能描述  : EPs Cause14的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月7日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  3.日    期   : 2014年5月5日
    作    者   : w00242748
    修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                 注册状态的上报。
  4.日    期   : 2015年1月5日
    作    者   : h00285180
    修改内容   : LTE #14拒绝优化:DTS2015010401946
  5.日    期   : 2015年4月19日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
  6.日    期   : 2015年7月1日
    作    者   : c00318887
    修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
  7.日    期   : 2015年8月13日
    作    者   : l00289540
    修改内容   : User_Exp_Improve

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause14GprsNotAllowInThisPlmn(VOS_VOID)
{

    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;
    VOS_UINT8                           ucEpsRejBy14AllowPsRegFlg;

    ucEpsRejBy14AllowPsRegFlg = NAS_MML_GetEpsRejByCause14InVplmnAllowPsRegFlg();

    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));

    if ((VOS_TRUE   == NAS_MMC_IsRoam())
     && (VOS_TRUE   == ucEpsRejBy14AllowPsRegFlg))
    {
        PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
        stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

        NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
            NAS_MML_MAX_TIME_SLICE,
            MMC_LMM_DISABLE_LTE_REASON_BUTT);
    }
    else
    {
        /* 添加禁止GPRS PLMN 信息 */
        NAS_MML_AddForbGprsPlmn(NAS_MML_GetCurrCampPlmnId());
    }
    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    /* 24301_CR1422R1_(Rel-11)_C1-121612 对应24301 5.5.1.2.5章节:
    #14(EPS services not allowed in this PLMN);
        The UE shall set the EPS update status to EU3 ROAMING NOT ALLOWED
        (and shall store it according to subclause 5.1.3.3) and shall delete any
        GUTI, last visited registered TAI and eKSI. Additionally, the UE shall
        delete the list of equivalent PLMNs and reset the attach attempt counter
        该CR受协议版本控制 */
    if (NAS_MML_GetLte3gppRelVersion() >= NAS_MML_3GPP_REL_R11)
    {
        /* 删除EPLMN */
        NAS_MMC_DeleteEPlmnList();
    }

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_LteRejCause14())
    {
        /* 需要Disable L全局变量 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);
        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_REJ_CAUSE_14);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetLteRejCause14EnableLteTimerLen());

        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsAttachRegFailCause15NoSuitableCell
 功能描述  : Eps Cause15的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月7日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  3.日    期   : 2014年5月5日
    作    者   : w00242748
    修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                 注册状态的上报。
  4.日    期   : 2015年7月1日
    作    者   : c00318887
    修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause15NoSuitableCell(VOS_VOID)
{
    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsAttachRegFailCause35RequestedServiceOptionNotAuthorizedInThisPlmn
 功能描述  : Eps Cause35的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年03月06日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年12月24日
    作    者   : w00242748
    修改内容   : DTS2013101106863:L下被拒原因值#35，只有在R10及其协议以上处理才与#11
                 原因值处理相同，否则当做OTHER CAUSE来处理。
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause35ReqServOptNotAuthorizedInThisPlmn(VOS_VOID)
{
    NAS_MML_MS_3GPP_REL_STRU           *pstMs3GppRel = VOS_NULL_PTR;
    NAS_MMC_REG_RSLT_CTX_STRU          *pstRegRsltCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulAttemptCnt;

    pstRegRsltCtx   = NAS_MMC_GetRegRsltCtxAddr();
    pstMs3GppRel    = NAS_MML_GetMs3GppRel();

    if ( NAS_MML_3GPP_REL_R9 >= pstMs3GppRel->enLteNasRelease )
    {
        /* 取得Attempt Counter的值 */
        ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(pstRegRsltCtx->enRegRsltType);
        return NAS_MMC_ProcEpsRegFailCauseAbnormalCause(NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN, ulAttemptCnt);
    }
    else
    {
        return NAS_MMC_ProcEpsAttachRegFailCause11PlmnNotAllow();
    }
}



/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsAttachRegFailCause256AuthRej
 功能描述  : Eps Reg Auth rej的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月7日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年2月3日
    作    者   : w00167002
    修改内容   : DTS2011122704039:在注册失败原因值的函数命名中增加原因值，
                  保持函数命名的一致性。
  3.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  4.日    期   : 2012年09月15日
    作    者   : z00161729
    修改内容   : DTS2012090708320：MMC收到L的注册结果，ps cs卡是否有效状态需要更新，原来由gmm更新存在时序问题
  5.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  6.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  7.日    期   : 2014年4月29日
    作    者   : s00261364
    修改内容   : ecall项目修改服务状态上报
  8.日    期   : 2014年5月5日
    作    者   : w00242748
    修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                 注册状态的上报。
  9.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause256AuthRej(VOS_VOID)
{
    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* 更新服务状态 */

    /* 设置cs ps卡状态为无效 */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);

    /* 通知TAF当前的服务状态 */

    /*MMC接收到LMM模块注册结果attach(EPS ONLY)，鉴权被拒，更新PS域注册状态，并上报服务状态*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsAttachRegFailCause257AccessBarrd
 功能描述  : Eps AccessBarrd的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月7日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年2月3日
    作    者   : w00167002
    修改内容   : DTS2011122704039:在注册失败原因值的函数命名中增加原因值，
                  保持函数命名的一致性。
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  4.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  5.日    期   : 2013年10月15日
    作    者   : s00190137
    修改内容   : 特性开关打开且非HPLMN/RPLMN接入禁止时需要触发PLMN搜网

  6.日    期   : 2015年1月23日
    作    者   : w00167002
    修改内容   : DTS2015020309124:via控制L下搜网注册时候，L下ACCESS BAR，后续
                选网结束后，L自己触发了注册。VIA无法配合，MODEM进行配合修改。
                修改为在注册状态收到ACCESS BAR后，继续等待L的注册结果。
  7.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
               MMC收到LMM ATTACH结果中，携带ACCESS BAR场景，
                       服务状态:CS域上报NAS_MMC_NO_SERVICE，PS域上报NAS_MMC_LIMITED_SERVICE, CS域和PS域注册状态上报0。
               MMC收到LMM TAU结果中，携带ACCESS BAR场景，
                       CS域和PS域服务状态,CS域和PS域注册状态不改变

  8.日    期   : 2015年11月24日
    作    者   : w00167002
    修改内容   : DTS2015112405788:在海外测试,如果当前开机CS/PS是无服务，则不上报到
                 MMA，而MMA需要收起CS/PS的服务状态，才给stk下发LOCATION STATUS NTF
                 消息；卡收不到此消息，则不进行IMSI切换。

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause257AccessBarrd(VOS_VOID)
{
    VOS_UINT8                           ucSimCsRegStatus;

    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    enFsmId         = NAS_MMC_GetCurrFsmId();

    if (NAS_FSM_BUTT <= enFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */
    /* 如果CS允许注册而且CS卡有效则更改CS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (VOS_TRUE == ucSimCsRegStatus))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS,NAS_MMC_LIMITED_SERVICE);
    }
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS,NAS_MMC_LIMITED_SERVICE);

    /*特性开关打开且非HPLMN/RPLMN接入禁止时需要触发PLMN搜网*/
    if (VOS_TRUE == NAS_MMC_IsAccBarPlmnSearch())
    {
        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }

        return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }


    /* 当前CL互操作时如果ACCEESBARRED,则继续等待注册结果，否则后续解BAR,L发起注册，VIA无法配合 */
    if ( (NAS_MMC_REG_CONTROL_BY_3GPP2_CBP  == NAS_MMC_GetRegCtrl())
      && (NAS_MMC_FSM_PLMN_SELECTION        == enFsmId) )
    {
        return NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
    }

    return NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED;

}
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsAttachRegFailCause301TimerTimeOut
 功能描述  : Eps Reg Auth rej的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2012年2月3日
    作    者   : w00167002
    修改内容   : DTS2011122704039:在注册失败原因值的函数命名中增加原因值，
                  保持函数命名的一致性。
  3.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  4.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  5.日    期   : 2015年7月1日
    作    者   : c00318887
    修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause301TimerTimeOut(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    /* 取得当前的注册结果消息类型 */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType );

    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        /* AttemptCounter未达到最大次数的处理 */
        NAS_MMC_ProcEpsRegFailAttemptCouterLessThanMaxTimes(&enAction);
    }
    else
    {
        /* 删除EPLMN */
        NAS_MMC_DeleteEPlmnList();

        /* 更新服务状态 */

        /* 通知TAF当前的服务状态 */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

        enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }
    }

    return enAction;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsAttachRegFailCause401OtherCause
 功能描述  : Eps Reg Auth rej的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : 新生成函数
  3.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  4.日    期   : 2012年06月07日
   作    者   : s00217060
   修改内容   : For CS/PS mode 1，联合Attach,other cause,并且尝试5次，设置需要Disable L
  5.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  6.日    期   : 2015年7月1日
    作    者   : c00318887
    修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause401OtherCause(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    /* 取得当前的注册结果消息类型 */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType );

    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        /* AttemptCounter未达到最大次数的处理 */
        NAS_MMC_ProcEpsRegFailAttemptCouterLessThanMaxTimes(&enAction);
    }
    else
    {
        /* 删除EPLMN */
        NAS_MMC_DeleteEPlmnList();

        /* 更新服务状态 */

        /* 通知TAF当前的服务状态 */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

        enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }
    }

    return enAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsAttachRegFailCause403ForbiddenPlmn
 功能描述  : Eps 回复当前驻留在禁止网络的后续处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月12日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年1月4日
    作    者   : w00167002
    修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网.
                  在主框架中L1MAIN/PLMN LIST中判断当前原因值为非UE主动发起注册
                  原因值，则更新为NAS_MMC_ADDITIONAL_ACTION_BUTT。
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  4.日    期   : 2015年7月1日
    作    者   : c00318887
    修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause403ForbiddenPlmn(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

    enFsmId = NAS_MMC_GetCurrFsmId();

    switch ( enFsmId )
    {
        /* 返回NAS_MMC_ADDITIONAL_ACTION_BUTT，表示无效的AdditionalAction值，
            MMC不更新当前ADDITIONAL ACTION的值 */
        case NAS_MMC_FSM_L1_MAIN :
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
            if (NAS_MML_REG_REGISTERED_HOME_NETWORK == NAS_MML_GetPsRegStatus())
            {
                NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            }

            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_BUTT);

            break;

        case NAS_MMC_FSM_PLMN_LIST :
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
            if (NAS_MML_REG_REGISTERED_HOME_NETWORK == NAS_MML_GetPsRegStatus())
            {
                NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            }
            break;

        /* 否则需要进行搜网 */
        default:
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
            break;
    }

    return enAdditionalAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsAttachRegFailCause404ForbiddenTaForRegPrvsSvs
 功能描述  : Eps被拒原因值:MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS的后续处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause404ForbiddenTaForRegPrvsSvs(VOS_VOID)
{
    /* 跟拒绝原因值#12的处理保持一致 */
    return NAS_MMC_ProcEpsAttachRegFailCause12TaNotAllow();
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsAttachRegFailCause405ForbiddenLaForRoam
 功能描述  : 假流程:Ps 13或15号原因值被拒
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION :拒绝原因值#13的搜网策略
             NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN:拒绝原因值#15的搜网策略
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月29日
    作    者   : w00167002
    修改内容   : 新生成函数
                 DTS2011102200381:L下注册被拒#12,LMM给MMC带的TAU
                 中的结果为MMC_LMM_TAU_RSLT_FORBID_PLMNS，MMC收到此结果后按照禁止网络
                 来处理而发起了搜网。
                 MMC区分当前是#13还是#15，而进行不同的搜网动作。
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause405ForbiddenLaForRoam(VOS_VOID)
{
    /* 跟tau状态的处理一致 */
    return NAS_MMC_ProcEpsTauRegFailCause405ForbiddenLaForRoam();
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsAttachRegFailCause406ForbiddenPlmnForGprs
 功能描述  : EPs Cause14的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月7日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年1月4日
    作    者   : w00167002
    修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网.
                  在主框架中L1MAIN/PLMN LIST中判断当前原因值为非UE主动发起注册
                  原因值，则更新为NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON。现将
                  此判断放到各个子函数中来判断。
   3.日    期   : 2013年3月30日
     作    者   : l00167671
     修改内容   : 主动上报AT命令控制下移至C核
   4.日    期   : 2015年7月1日
     作    者   : c00318887
     修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause406ForbiddenPlmnForGprs(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    /* 添加禁止GPRS PLMN 信息 */
    NAS_MML_AddForbGprsPlmn(NAS_MML_GetCurrCampPlmnId());

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

    enFsmId = NAS_MMC_GetCurrFsmId();

    switch ( enFsmId )
    {
        /* 当前在ONPLMN,返回NAS_MMC_ADDITIONAL_ACTION_BUTT，表示无效的AdditionalAction
            值，MMC不更新当前ADDITIONAL ACTION的值 */
        case NAS_MMC_FSM_L1_MAIN :
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
            if (NAS_MML_REG_REGISTERED_HOME_NETWORK == NAS_MML_GetPsRegStatus())
            {
                NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            }

            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_BUTT);

            break;

        case NAS_MMC_FSM_PLMN_LIST :
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;

            if (NAS_MML_REG_REGISTERED_HOME_NETWORK == NAS_MML_GetPsRegStatus())
            {
                NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            }

            break;

        /* 否则需要进行可选的搜网 */
        default:
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
            break;
    }

    return enAdditionalAction;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsAttachRegFailCausePsAttachNotAllow
 功能描述  : Eps 回复当前PS不允许注册的后续处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月27日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  3.日    期   : 2015年7月1日
    作    者   : c00318887
    修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCausePsAttachNotAllow(VOS_VOID)
{
    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
    }


    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsAttachRegFailCauseEpsBearerEstFail
 功能描述  : Eps 回复EPS承载建立失败的后续处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月08日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  3.日    期   : 2015年7月1日
    作    者   : c00318887
    修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCauseEpsBearerEstFail(VOS_VOID)
{
    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }


    return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
}

 /*****************************************************************************
  函 数 名  : NAS_MMC_ProcEpsAttachRegFailCauseMoDetach
  功能描述  : Eps Mo detach的后续处理
  输入参数  : VOS_VOID
  输出参数  : 无
  返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
  调用函数  :
  被调函数  :

  修改历史      :
   1.日    期   : 2012年1月08日
     作    者   : z00161729
     修改内容   : 新生成函数
   2.日    期   : 2013年3月30日
     作    者   : l00167671
     修改内容   : 主动上报AT命令控制下移至C核
   3.日    期   : 2014年07月26日
     作    者   : s00217060
     修改内容   : DTS2014051501744:TAU过程中用户detach,LMM会给MMC回MO_DETACH_FAILURE,
                  MMC收到该TAU结果会触发搜网，搜网前要求主动释放链接，导致detach_req发不上去
   4.日    期   : 2015年7月1日
     作    者   : c00318887
     修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
 *****************************************************************************/
 NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCauseMoDetach(VOS_VOID)
 {
    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }


    /* attach过程中用户detach,LMM会给MMC回MO_DETACH_FAILURE,
       MMC收到该attach结果会触发搜网，搜网前要求主动释放链接，导致detach_req发不上去
       所以此处修改为限制驻留 */
    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
 }

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsAttachRegFailCauseMtDetach
 功能描述  : Eps Mt detach的后续处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月08日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  3.日    期   : 2015年7月1日
    作    者   : c00318887
    修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCauseMtDetach(VOS_VOID)
{
    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsAttachRegFailCause42SevereNetworkFailure
 功能描述  : eps only attach被拒#42 severe network failure的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月19日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause42SevereNetworkFailure(VOS_VOID)
{
    NAS_MMC_REG_RSLT_CTX_STRU          *pstRegRsltCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulAttemptCnt;
    NAS_MML_3GPP_REL_ENUM_UINT8         enLteRelVersion;
    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    enLteRelVersion = NAS_MML_GetLte3gppRelVersion();
    pstRegRsltCtx   = NAS_MMC_GetRegRsltCtxAddr();
    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));

    /* 协议版本小于R11按other cause处理 */
    if ( NAS_MML_3GPP_REL_R11 > enLteRelVersion )
    {
        /* 取得Attempt Counter的值 */
        ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(pstRegRsltCtx->enRegRsltType);
        return NAS_MMC_ProcEpsRegFailCauseAbnormalCause(NAS_MML_REG_FAIL_CAUSE_SEVERE_NETWORK_FAILURE, ulAttemptCnt);
    }

    /* 24301_CR1473R2_(Rel-11)_C1-123386 MMC增加ATTACH、TAU和SERVICE REQUEST过程中被拒原因值42的处理
      24301 5.5.1.2.5章节描述:
      The UE shall set the EPS update status to EU2 NOT UPDATED, and shall delete
    any GUTI, last visited registered TAI, eKSI, and list of equivalent PLMNs,
    and set the attach attempt counter to 5. The UE shall start an implementation
    specific timer setting its value to 2 times the value of T as defined in
    3GPP TS 23.122 [6]. While this timer is running, the UE shall not consider
    the PLMN + RAT combination that provided this reject cause a candidate
    for PLMN selection. The UE then enters state EMM-DEREGISTERED.PLMN-SEARCH
    in order to perform a PLMN selection according to 3GPP TS 23.122 [6].
      If A/Gb mode or Iu mode is supported by the UE, the UE shall in addition
    set the GMM state to GMM-DEREGISTERED, GPRS update status to GU2 NOT UPDATED,
    and shall delete the P-TMSI, P-TMSI signature, RAI and GPRS ciphering key
    sequence number. 该CR受协议版本控制 */
    PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
    stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

    /* 将被拒#42的网络加入禁止接入技术网络列表中，禁止时间为2*T,触发搜网 */
    NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                   NAS_MML_GetDisabledPlmnRejCause42ForbiddenTimeSlice(),
                                                   MMC_LMM_DISABLE_LTE_REASON_BUTT);

    NAS_MMC_DeleteEPlmnList();

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsAttachRegFailCauseT3402Running
 功能描述  : Eps T3402定时器正在运行的后续处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月08日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2013年1月31日
    作    者   : t00212959
    修改内容   : DTS2013012909238:anycell搜网，3402在运行，不等available超时，就又发起了搜网。
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  4.日    期   : 2015年7月1日
    作    者   : c00318887
    修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCauseT3402Running(VOS_VOID)
{

    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_TIMER_STATUS_ENUM_U8                            enAvailableTimerStatus;

    enFsmId                = NAS_MMC_GetCurrFsmId();
    enAvailableTimerStatus = NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER);

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

    /* 当前在ONPLMN时，AVAILABLE定时器未启动,则MMC需要发起搜网*/
    if ( NAS_MMC_FSM_L1_MAIN   == enFsmId)
    {
        if (NAS_MMC_TIMER_STATUS_RUNING == enAvailableTimerStatus)
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

            return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
        }

        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
}




/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsTauRegFailCause3IllegalMs
 功能描述  : Eps Cause3的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月7日
    作    者   : l00130025
    修改内容   : 新生成函数

  2.日    期   : 2011年12月30日
    作    者   : l65478
    修改内容   : 在迁到L模时,不立刻把CS设置成可选搜网,而是等待PS注册结果时
                 根据具体的原因值再设置

  3.日    期   : 2012年2月15日
    作    者   : z40661
    修改内容   : DTS2011121405203_PC测试发现问题,支持gUL多模时,L下被#3拒绝,到GU下指定搜网
  4.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  5.日    期   : 2012年09月15日
    作    者   : z00161729
    修改内容   : DTS2012090708320：MMC收到L的注册结果，ps cs卡是否有效状态需要更新，原来由gmm更新存在时序问题
  6.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  7.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  8.日    期   : 2014年4月29日
    作    者   : s00261364
    修改内容   : ecall项目修改服务状态上报
  9.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause3IllegalMs(VOS_VOID)
{
    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* 更新服务状态 */

    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, begin */
    /* 先更新全局变量,便于发送消息时获取到的全局变量是最新的 */
    /* 设置cs ps卡状态为无效 */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    /* 通知TAF当前的服务状态 */
    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, end */

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);

    /*更新PS域注册状态，并上报服务状态*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,VOS_FALSE);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }

    /* modified by z40661 for DTS2011121405203_PC测试发现问题, 2012-02-15, begin */
    return NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;
    /* modified by z40661 for DTS2011121405203_PC测试发现问题, 2012-02-15, begin */

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsTauRegFailCause6IllegalMe
 功能描述  : Eps Cause6的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月7日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause6IllegalMe(VOS_VOID)
{
    return NAS_MMC_ProcEpsTauRegFailCause3IllegalMs();
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCauseCause7EpsServNotAllow
 功能描述  : Eps Cause7的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数

  2.日    期   : 2011年12月30日
    作    者   : l65478
    修改内容   : 在迁到L模时,不立刻把CS设置成可选搜网,而是等待PS注册结果时
                 根据具体的原因值再设置
  3.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环

  4.日    期   : 2012年4月4日
    作    者   : z40661
    修改内容   : 问题单号DTS2012032803448，PS oNLY时，需要在L模下进行ANYCELL搜网。

  5.日    期   : 2012年7月4日
    作    者   : s46746
    修改内容   : for V7R1 cS/PS mode 1, 原因值#7时，需要设置Disable LTE全局变量
  6.日    期   : 2012年7月27日
    作    者   : s00217060
    修改内容   : For CS/PS mode 1,带Disable LTE原因值
  7.日    期   : 2012年09月15日
    作    者   : z00161729
    修改内容   : DTS2012090708320：MMC收到L的注册结果，ps cs卡是否有效状态需要更新，原来由gmm更新存在时序问题
  8.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  9.日    期   : 2014年4月29日
    作    者   : s00261364
    修改内容   : ecall项目修改服务状态上报
 10.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause7EpsServNotAllow(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatOrder;
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;

    pstRatOrder     = NAS_MML_GetMsPrioRatList();

    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* 更新服务状态 */

    /* 设置ps卡状态为无效 */
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);
    /*MMC接收到LMM模块注册结果(EPS ONLY)，casue=#7, 更新PS域注册状态，并上报服务状态*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

    /* 通知TAF当前的服务状态 */

    /* 判断是否需要disable L */
    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_PsFailCause7PsServNotAllow())
    {
        /* 记录本地disable LTE标记 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_PS_USIM_INVALID);
    }

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,VOS_FALSE);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }

    enMsMode    =    NAS_MML_GetMsMode();
    if ( (VOS_TRUE == NAS_MML_IsLteOnlyMode(pstRatOrder))
      || (NAS_MML_MS_MODE_PS_ONLY == enMsMode))
    {
        return NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
    }
    else
    {
        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsAttachRegFailCause8GprsAndNonGprsNotAllow
 功能描述  : Eps Cause8的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 新生成函数
                增加对CASUE 8的处理，
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause8GprsAndNonGprsNotAllow(VOS_VOID)
{
    return NAS_MMC_ProcEpsTauRegFailCause3IllegalMs();
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsTauRegFailCause9MsIdCannotBeDerivedByNW
 功能描述  : Eps Cause9的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  4.日    期   : 2015年11月19日
    作    者   : c00318887
    修改内容   : DTS2015111701196,ims没注册
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause9MsIdCannotBeDerivedByNW(VOS_VOID)
{
    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }

    return NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsTauRegFailCause10EpsImplicitlyDetached
 功能描述  : Eps Cause9的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  4.日    期   : 2015年11月19日
    作    者   : c00318887
    修改内容   : DTS2015111701196,ims没注册
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause10EpsImplicitlyDetached(VOS_VOID)
{
    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }

    return NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsTauRegFailCause11PlmnNotAllow
 功能描述  : Eps Cause11的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年08月05日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  4.日    期   : 2015年4月19日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
  4.日    期   : 2015年7月1日
    作    者   : c00318887
    修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause11PlmnNotAllow(VOS_VOID)
{
    NAS_MML_PLMN_ID_STRU               *pstCurPlmnId;

    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    pstCurPlmnId = NAS_MML_GetCurrCampPlmnId();

    /* 添加禁止网络信息,有更新时，向Usim更新文件 */
    if (VOS_TRUE == NAS_MMC_IsNeedAddForbPlmn_TauRsltFailCause11PlmnNotAllow())
    {
        if (VOS_TRUE == NAS_MML_AddForbPlmn(pstCurPlmnId))
        {
            NAS_MMC_SndUsimUpdateForbPlmnReq();
        }
    }

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsTauRegFailCause12TaNotAllow
 功能描述  : Eps Cause12的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月7日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  3.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  4.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause12TaNotAllow(VOS_VOID)
{
    VOS_UINT8                           ucSimCsRegStatus;

    /* 更新服务状态 */

    /*MMC接收到LMM模块注册结果(EPS ONLY)，casue=#12, 更新PS域注册状态为0，并上报服务状态2*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE_REGION);

    /* 通知TAF当前的服务状态 */
    /* 如果CS允许注册而且CS卡有效则更改CS注册状态为NAS_MMC_LIMITED_SERVICE_REGION */
    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (VOS_TRUE == ucSimCsRegStatus))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE_REGION);
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
    }

    return NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsTauRegFailCause13RoamNotAllow
 功能描述  : Eps Cause13的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月7日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  4.日    期   : 2015年7月1日
    作    者   : c00318887
    修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause13RoamNotAllow(VOS_VOID)
{
    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsTauRegFailCause14GprsNotAllowInThisPlmn
 功能描述  : EPs Cause14的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月7日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  3.日    期   : 2015年1月5日
    作    者   : h00285180
    修改内容   : LTE #14拒绝优化:DTS2015010401946
  4.日    期   : 2015年4月19日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
  4.日    期   : 2015年7月1日
    作    者   : c00318887
    修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
  5.日    期   : 2015年8月13日
    作    者   : l00289540
    修改内容   : User_Exp_Improve修改

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause14GprsNotAllowInThisPlmn(VOS_VOID)
{
    NAS_MML_3GPP_REL_ENUM_UINT8         enLteRelVersion;

    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;
    VOS_UINT8                           ucEpsRejBy14AllowPsRegFlg;
    ucEpsRejBy14AllowPsRegFlg = NAS_MML_GetEpsRejByCause14InVplmnAllowPsRegFlg();
    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));

    enLteRelVersion = NAS_MML_GetLte3gppRelVersion();

    if (VOS_TRUE == NAS_MMC_IsNeedAddForbGprsPlmn_TauRsltFailCause14GprsNotAllowInThisPlmn())
    {
        if ((VOS_TRUE   == NAS_MMC_IsRoam())
         && (VOS_TRUE   == ucEpsRejBy14AllowPsRegFlg))
        {
            PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
            stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

            NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                NAS_MML_MAX_TIME_SLICE,
                MMC_LMM_DISABLE_LTE_REASON_BUTT);
        }
        else
        {
            /* 添加禁止GPRS PLMN 信息 */
            NAS_MML_AddForbGprsPlmn(NAS_MML_GetCurrCampPlmnId());
        }
    }

    /* 24301_CR1422R1_(Rel-11)_C1-121612 对应24301 5.5.3.2.5章节:
     #14:
      If the EPS update type is "TA updating", or the EPS update type is
      "periodic updating" and the UE is in PS mode 1 or PS mode 2 of operation,
      the UE shall perform a PLMN selection according to 3GPP TS 23.122 [6]. In
      this case, the UE supporting S1 mode only shall delete the list of equivalent
      PLMNs before performing the procedure. 该CR受协议版本控制  */
    if ((VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
      && (enLteRelVersion >= NAS_MML_3GPP_REL_R11))
    {
        /* 删除EPLMN */
        NAS_MMC_DeleteEPlmnList();
    }
    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_LteRejCause14())
    {
        /* 需要Disable L全局变量 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);
        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_REJ_CAUSE_14);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetLteRejCause14EnableLteTimerLen());

        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsTauRegFailCause15NoSuitableCell
 功能描述  : Eps Cause15的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月7日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  3.日    期   : 2015年7月1日
    作    者   : c00318887
    修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause15NoSuitableCell(VOS_VOID)
{
    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;
}




/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsTauRegFailCause40NoEpsBearerActived
 功能描述  : Eps Cause40的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年1月11日
    作    者   : w00176964
    修改内容   : V7R1 PhaseIV BBIT测试调整
  3.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  4.日    期   : 2015年11月19日
    作    者   : c00318887
    修改内容   : DTS2015111701196,ims没注册
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause40NoEpsBearerActived(VOS_VOID)
{
    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }

    return NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsTauRegFailCause42SevereNetworkFailure
 功能描述  : Eps tau Cause42的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月19日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause42SevereNetworkFailure(VOS_VOID)
{
    NAS_MMC_REG_RSLT_CTX_STRU          *pstRegRsltCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulAttemptCnt;
    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    pstRegRsltCtx   = NAS_MMC_GetRegRsltCtxAddr();
    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));

    /* 协议版本小于R11按other cause处理 */
    if ( NAS_MML_3GPP_REL_R11 > NAS_MML_GetLte3gppRelVersion())
    {
        /* 取得Attempt Counter的值 */
        ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(pstRegRsltCtx->enRegRsltType);
        return NAS_MMC_ProcEpsRegFailCauseAbnormalCause(NAS_EMM_CAUSE_SERVER_NETWORK_FAILURE, ulAttemptCnt);
    }

    /* 24301_CR1473R2_(Rel-11)_C1-123386 MMC增加ATTACH、TAU和SERVICE REQUEST过程中被拒原因值42的处理
      24301 5.5.3.2.5章节描述:
       The UE shall set the EPS update status to EU2 NOT UPDATED, and shall delete
    any GUTI, last visited registered TAI, eKSI, and list of equivalent PLMNs,
    and set the attach attempt counter to 5. The UE shall start an implementation
    specific timer setting its value to 2 times the value of T as defined in
    3GPP TS 23.122 [6]. While this timer is running, the UE shall not consider
    the PLMN + RAT combination that provided this reject cause a candidate
    for PLMN selection. The UE then enters state EMM-DEREGISTERED.PLMN-SEARCH
    in order to perform a PLMN selection according to 3GPP TS 23.122 [6].
       If A/Gb mode or Iu mode is supported by the UE, the UE shall in addition
    set the GMM state to GMM-DEREGISTERED, GPRS update status to GU2 NOT UPDATED,
    and shall delete the P-TMSI, P-TMSI signature, RAI and GPRS ciphering key
    sequence number. 该CR受协议版本控制 */
    PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
    stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

    /* 将被拒#42的网络加入禁止接入技术网络列表中，禁止时间为2*T,触发搜网 */
    NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                   NAS_MML_GetDisabledPlmnRejCause42ForbiddenTimeSlice(),
                                                   MMC_LMM_DISABLE_LTE_REASON_BUTT);


    NAS_MMC_DeleteEPlmnList();

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

}



/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsTauRegFailCause35RequestedServiceOptionNotAuthorizedInThisPlmn
 功能描述  : Eps Cause35的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月6日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年12月24日
    作    者   : w00242748
    修改内容   : DTS2013101106863:L下被拒原因值#35，只有在R10及其协议以上处理才与#11
                 原因值处理相同，否则当做OTHER CAUSE来处理。
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause35ReqServOptNotAuthorizedInThisPlmn(VOS_VOID)
{
    NAS_MML_MS_3GPP_REL_STRU           *pstMs3GppRel = VOS_NULL_PTR;
    NAS_MMC_REG_RSLT_CTX_STRU          *pstRegRsltCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulAttemptCnt;

    pstRegRsltCtx   = NAS_MMC_GetRegRsltCtxAddr();
    pstMs3GppRel    = NAS_MML_GetMs3GppRel();

    if ( NAS_MML_3GPP_REL_R9 >= pstMs3GppRel->enLteNasRelease )
    {
        /* 取得Attempt Counter的值 */
        ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(pstRegRsltCtx->enRegRsltType);
        return NAS_MMC_ProcEpsRegFailCauseAbnormalCause(NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN, ulAttemptCnt);
    }
    else
    {
        return NAS_MMC_ProcEpsTauRegFailCause11PlmnNotAllow();
    }

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsTauRegFailCause256AuthRej
 功能描述  : Eps Reg Auth rej的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月7日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  3.日    期   : 2012年09月15日
    作    者   : z00161729
    修改内容   : DTS2012090708320：MMC收到L的注册结果，ps cs卡是否有效状态需要更新，原来由gmm更新存在时序问题
  4.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  5.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  6.日    期   : 2014年4月29日
    作    者   : s00261364
    修改内容   : ecall项目修改服务状态上报
  7.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause256AuthRej(VOS_VOID)
{
    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* 更新服务状态 */

    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, begin */
    /* 设置cs ps卡状态为无效 */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    /* 通知TAF当前的服务状态 */
    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, end */

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);

    /*MMC接收到LMM模块注册结果(EPS ONLY)，鉴权被拒，更新PS域注册状态，并上报服务状态*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsTauRegFailCause257AccessBarrd
 功能描述  : Eps AccessBarrd的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月7日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年1月4日
    作    者   : w00167002
    修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网.
                  在主框架中L1MAIN/PLMN LIST中判断当前原因值为非UE主动发起注册
                  原因值，则更新为NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON。现将
                  此判断放到各个子函数中来判断。
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  4.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  5.日    期   : 2013年10月15日
    作    者   : s00190137
    修改内容   : 特性开关打开且非HPLMN/RPLMN接入禁止时需要触发PLMN搜网
  6.日    期   : 2015年1月23日
    作    者   : w00167002
    修改内容   : DTS2015020309124:via控制L下搜网注册时候，L下ACCESS BAR，后续
                选网结束后，L自己触发了注册。VIA无法配合，MODEM进行配合修改。
                修改为在注册状态收到ACCESS BAR后，继续等待L的注册结果。
  7.日    期   : 2015年7月1日
    作    者   : c00318887
    修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause257AccessBarrd(VOS_VOID)
{
    VOS_UINT8                           ucSimCsRegStatus;

    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;

    enFsmId         = NAS_MMC_GetCurrFsmId();

    if (NAS_FSM_BUTT <= enFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */
    /* 如果CS允许注册而且CS卡有效则更改CS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (VOS_TRUE == ucSimCsRegStatus))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    /*特性开关打开且非HPLMN/RPLMN接入禁止时需要触发PLMN搜网*/
    if (VOS_TRUE == NAS_MMC_IsAccBarPlmnSearch())
    {
        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }

        return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }

    /* 当前CL互操作时如果ACCEESBARRED,则继续等待注册结果，否则后续解BAR,L发起注册，VIA无法配合 */
    if ( (NAS_MMC_REG_CONTROL_BY_3GPP2_CBP  == NAS_MMC_GetRegCtrl())
      && (NAS_MMC_FSM_PLMN_SELECTION        == enFsmId) )
    {
        return NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
    }

    return NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsTauRegFailCause301TimerTimeOut
 功能描述  : Eps Reg Timer Out的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  4.日    期   : 2015年7月1日
    作    者   : c00318887
    修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause301TimerTimeOut(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    /* 取得当前的注册结果消息类型 */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType );

    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        /* AttemptCounter未达到最大次数的处理 */
        NAS_MMC_ProcEpsRegFailAttemptCouterLessThanMaxTimes(&enAction);
    }
    else
    {
        /* 删除EPLMN */
        NAS_MMC_DeleteEPlmnList();

        /* 更新服务状态 */

        /* 通知TAF当前的服务状态 */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

        enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }
    }

    return enAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsTauRegFailCause401OtherCause
 功能描述  : Eps Reg Auth rej的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  4.日    期   : 2015年7月1日
    作    者   : c00318887
    修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause401OtherCause(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    /* 取得当前的注册结果消息类型 */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType );
    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        /* AttemptCounter未达到最大次数的处理 */
        NAS_MMC_ProcEpsRegFailAttemptCouterLessThanMaxTimes(&enAction);
    }
    else
    {
        /* 删除EPLMN */
        NAS_MMC_DeleteEPlmnList();

        /* 更新服务状态 */

        /* 通知TAF当前的服务状态 */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

        enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }
    }

    return enAction;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsTauRegFailCause403ForbiddenPlmn
 功能描述  : Eps 回复当前驻留在禁止网络的后续处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月12日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause403ForbiddenPlmn(VOS_VOID)
{
    return NAS_MMC_ProcEpsAttachRegFailCause403ForbiddenPlmn();
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsTauRegFailCause404ForbiddenTaForRegPrvsSvs
 功能描述  : Eps被拒原因值:MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS的后续处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause404ForbiddenTaForRegPrvsSvs(VOS_VOID)
{
    /* 跟拒绝原因值#12的处理保持一致 */
    return NAS_MMC_ProcEpsTauRegFailCause12TaNotAllow();
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsTauRegFailCause405ForbiddenLaForRoam
 功能描述  : 假流程:Ps 13或15号原因值被拒
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION :拒绝原因值#13的搜网策略
             NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN:拒绝原因值#15的搜网策略

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月29日
    作    者   : w00167002
    修改内容   : 新生成函数
                 DTS2011102200381:L下注册被拒#12,LMM给MMC带的TAU
                 中的结果为MMC_LMM_TAU_RSLT_FORBID_PLMNS，MMC收到此结果后按照禁止网络
                 来处理而发起了搜网。
                 MMC区分当前是#13还是#15，而进行不同的搜网动作。
  2.日    期   : 2012年1月4日
    作    者   : w00167002
    修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网.
                  在主框架中L1MAIN/PLMN LIST中判断当前原因值为非UE主动发起注册
                  原因值，则更新为NAS_MMC_ADDITIONAL_ACTION_BUTT。
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  4.日    期   : 2015年7月1日
    作    者   : c00318887
    修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause405ForbiddenLaForRoam(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause;                              /* 存储注册区CS域被拒信息 */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause;                              /* 存储注册区PS域被拒信息 */

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

    /* 当前在ONPLMN或者PLMN LIST状态机，则返回当为NAS_MMC_ADDITIONAL_ACTION_BUTT */
    enFsmId = NAS_MMC_GetCurrFsmId();

    if ( (NAS_MMC_FSM_L1_MAIN   == enFsmId)
      || (NAS_MMC_FSM_PLMN_LIST == enFsmId) )
    {
        if (NAS_MML_REG_REGISTERED_HOME_NETWORK == NAS_MML_GetPsRegStatus())
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }

        if (NAS_MMC_FSM_L1_MAIN == enFsmId)
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_BUTT);
        }

        return NAS_MMC_ADDITIONAL_ACTION_BUTT;
    }
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    /* 当前不在在ONPLMN或者PLMN LIST状态机，需处理拒绝原因值，返回不同的搜网策略 */

    /* 原因值初始化为#13,若发生异常，则按照#13进行常规的搜网 */
    enCsCause = NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW;
    enPsCause = NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW;

    NAS_MMC_GetDomainRegStatusInRegInfoList( NAS_MML_GetCurrCampPlmnId(),
                                             NAS_MML_GetCurrNetRatType(),
                                             &enCsCause,
                                             &enPsCause );

    /* 若CS域或者PS域有一个域的原因值为#13,则进行常规的搜网 */
    if ( (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW == enCsCause)
      || (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW == enPsCause))
    {
        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    /* 否则按照拒绝原因值#15的搜网策略进行搜网 */
    return NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsTauRegFailCause406ForbiddenPlmnForGprs
 功能描述  : EPs Cause14的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月7日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年1月4日
    作    者   : w00167002
    修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网.
                  在主框架中L1MAIN/PLMN LIST中判断当前原因值为非UE主动发起注册
                  原因值，则更新为NAS_MMC_ADDITIONAL_ACTION_BUTT。
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  4.日    期   : 2015年7月1日
    作    者   : c00318887
    修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause406ForbiddenPlmnForGprs(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    /* 添加禁止GPRS PLMN 信息 */
    NAS_MML_AddForbGprsPlmn(NAS_MML_GetCurrCampPlmnId());

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

    enFsmId = NAS_MMC_GetCurrFsmId();

    switch ( enFsmId )
    {
        /* 返回NAS_MMC_ADDITIONAL_ACTION_BUTT，表示无效的AdditionalAction值，
            MMC不更新当前ADDITIONAL ACTION的值 */
        case NAS_MMC_FSM_L1_MAIN :
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;

            if (NAS_MML_REG_REGISTERED_HOME_NETWORK == NAS_MML_GetPsRegStatus())
            {
                NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            }

            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_BUTT);

            break;

        case NAS_MMC_FSM_PLMN_LIST :
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
            if (NAS_MML_REG_REGISTERED_HOME_NETWORK == NAS_MML_GetPsRegStatus())
            {
                NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            }

            break;

        /* 否则需要进行可选的搜网 */
        default:
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

            break;
    }

    return enAdditionalAction;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsTauRegFailCauseMoDetach
 功能描述  : Eps Mo detach的后续处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年01月08日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  3.日    期   : 2014年07月26日
    作    者   : s00217060
    修改内容   : DTS2014051501744:TAU过程中用户detach,LMM会给MMC回MO_DETACH_FAILURE,
                 MMC收到该TAU结果会触发搜网，搜网前要求主动释放链接，导致detach_req发不上去
  4.日    期   : 2015年7月1日
    作    者   : c00318887
    修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCauseMoDetach(VOS_VOID)
{
    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }

    /* TAU过程中用户detach,LMM会给MMC回MO_DETACH_FAILURE,
       MMC收到该TAU结果会触发搜网，搜网前要求主动释放链接，导致detach_req发不上去
       所以此处修改为限制驻留 */
    /* 3GPP 24301 Selection 5.5.3.2.6 Abnormal cases in the UE
    m)  Mobile originated detach required
        The tracking area updating procedure shall be aborted, and the UE initiated detach procedure shall be performed.
    */
    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsTauRegFailCauseMtDetach
 功能描述  : Eps mt detach的后续处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年01月08日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  3.日    期   : 2015年7月1日
    作    者   : c00318887
    修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCauseMtDetach(VOS_VOID)
{
    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsTauRegFailCauseT3402Running
 功能描述  : Eps T3402定时器正在运行的后续处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年01月08日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2013年1月31日
    作    者   : t00212959
    修改内容   : DTS2013012909238:anycell搜网，3402在运行，不等available超时，就又发起了搜网。
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  4.日    期   : 2015年7月1日
    作    者   : c00318887
    修改内容   : DTS2015061003127:L 下服务状态上报和GU不一致
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCauseT3402Running(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_TIMER_STATUS_ENUM_U8                            enAvailableTimerStatus;

    enFsmId                = NAS_MMC_GetCurrFsmId();
    enAvailableTimerStatus = NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER);

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    /* 当前在ONPLMN时，AVAILABLE定时器未启动,则MMC需要发起搜网*/
    if ( NAS_MMC_FSM_L1_MAIN   == enFsmId)
    {
        if (NAS_MMC_TIMER_STATUS_RUNING == enAvailableTimerStatus)
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
        }
    }
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
}




/* 网侧detach EPS的cause值处理 */
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsDetachCause2ImsiUnknowInHss
 功能描述  : Eps detach Cause2的处理
 输入参数  : VOS_VOID
 输出参数  : penCsAddition
             penPsAddition
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月1日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年11月19日
    作    者   : w00176964
    修改内容   : V7R1 Phase III调整:联合注册ST修改
  3.日    期   : 2012年09月15日
    作    者   : z00161729
    修改内容   : DTS2012090708320：MMC收到L的注册结果，ps cs卡是否有效状态需要更新，原来由gmm更新存在时序问题
  4.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  5.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  6.日    期   : 2014年4月29日
    作    者   : s00261364
    修改内容   : ecall项目修改服务状态上报
  7.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                 mmc收到EPS网络去注册(#2,NO_REATTACH),上报注册状态和服务状态
*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsDetachCause2ImsiUnknowInHss(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction
)
{

    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, begin */
    /* 设置cs卡状态为无效 */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);

    /* 通知TAF当前的服务状态 */
    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, end */

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    /*mmc收到EPS网络去注册(#2,NO_REATTACH),上报注册状态和服务状态*/
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);

    *penCsRegAdditionalAction  = NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
    *penPsRegAdditionalAction  = NAS_MMC_ADDITIONAL_ACTION_BUTT;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsDetachCause3IllegalMs
 功能描述  : Eps detach Cause3的处理
 输入参数  : VOS_VOID
 输出参数  : penCsAddition
             penPsAddition
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月1日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年11月19日
    作    者   : w00176964
    修改内容   : V7R1 Phase III调整:联合注册ST修改

  3.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  4.日    期   : 2012年09月15日
    作    者   : z00161729
    修改内容   : DTS2012090708320：MMC收到L的注册结果，ps cs卡是否有效状态需要更新，原来由gmm更新存在时序问题
  5.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  6.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  7.日    期   : 2014年4月29日
    作    者   : s00261364
    修改内容   : ecall项目修改服务状态上报

  8.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                  mmc收到eps 网络去注册(#3/6/8),上报注册状态和服务状态
*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsDetachCause3IllegalMs(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* 更新服务状态 */

    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, begin */
    /* 设置cs ps卡状态为无效 */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    /* 通知TAF当前的服务状态 */
    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, end */

    /*mmc收到eps 网络去注册(#3/6/8),上报注册状态和服务状态*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    if(VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    }

    *penCsAddition  = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    *penPsAddition  = NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsDetachCause6IllegalMe
 功能描述  : Eps detach Cause6的处理
 输入参数  : VOS_VOID
 输出参数  : penCsAddition
             penPsAddition
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月1日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年11月19日
    作    者   : w00176964
    修改内容   : V7R1 Phase III调整:联合注册ST修改

*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsDetachCause6IllegalMe(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    NAS_MMC_ProcEpsDetachCause3IllegalMs(penCsAddition, penPsAddition);
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsDetachCause7EpsServNotAllow
 功能描述  : Eps detach Cause7的处理
 输入参数  : VOS_VOID
 输出参数  : penCsAddition
             penPsAddition
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月1日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年11月19日
    作    者   : w00176964
    修改内容   : V7R1 Phase III调整:联合注册ST修改
  3.日    期   : 2011年11月30日
    作    者   : w00176964
    修改内容   : V7R1 Phase IV调整:disable/enable 调整
  4.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环

  5.日    期   : 2012年4月4日
    作    者   : z40661
    修改内容   : 问题单号DTS2012032803448，PS oNLY时，需要在L模下进行ANYCELL
               搜网。
  6.日    期   : 2012年07月02日
    作    者   : s46746
    修改内容   : For CS/PS mode 1，调整Disable/Enable L,按场景区分函数
  7.日    期   : 2012年7月27日
    作    者   : s00217060
    修改内容   : For CS/PS mode 1,带Disable LTE原因值
  8.日    期   : 2012年09月15日
    作    者   : z00161729
    修改内容   : DTS2012090708320：MMC收到L的注册结果，ps cs卡是否有效状态需要更新，原来由gmm更新存在时序问题

  9.日    期   : 2012年9月25日
    作    者   : z40661
    修改内容   : DTS2012082006273
 10.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
 11.日    期   : 2014年4月29日
    作    者   : s00261364
    修改内容   : ecall项目修改服务状态上报
 12 日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                 mmc收到eps 网络去注册(#7),上报注册状态和服务状态,
                 上报PS域注册状态为3，CS、PS域限制服务，如果不需要搜网，则上报CS域注册状态为0，需要搜网，参考搜网流程状态上报
*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsDetachCause7EpsServNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                     *pstRatOrder;
    NAS_MML_MS_MODE_ENUM_UINT8                      enMsMode;

    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    pstRatOrder     = NAS_MML_GetMsPrioRatList();

    /* 更新服务状态 */

    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, begin */
    /* 设置ps卡状态为无效 */
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    /* 通知TAF当前的服务状态 */
    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, end */

    /* 判断是否需要disable L */
    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_PsFailCause7PsServNotAllow())
    {
        /* 记录本地disable LTE标记 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_PS_USIM_INVALID);
    }


    /*mmc收到eps 网络去注册(#7),上报注册状态和服务状态,
       上报PS域注册状态为3，CS、PS域限制服务，如果不需要搜网，则上报CS域注册状态为0，需要搜网，参考搜网流程状态上报*/
     /*由于紧接着就发起搜网，cs的注册状态就不上报了*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);



    /* 如果是L单模被拒原因值7，需要anycell搜网,多模情况需要搜网 */
    enMsMode    =    NAS_MML_GetMsMode();
    if ( (VOS_TRUE == NAS_MML_IsLteOnlyMode(pstRatOrder))
      || (NAS_MML_MS_MODE_PS_ONLY == enMsMode))
    {
        *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
        *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
    }
    else
    {
        *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
        *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsDetachCause8GprsAndNonGprsNotAllow
 功能描述  : Eps detach Cause8的处理
 输入参数  : VOS_VOID
 输出参数  : penCsAddition
             penPsAddition
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月1日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年11月19日
    作    者   : w00176964
    修改内容   : V7R1 Phase III调整:联合注册ST修改
  3.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : DTS2011121307570: MMC没有维护LMM的EPLMN信息，现在统一调整
                  ATTACH/TAU/DETACH/SERVICE中被拒时EPLMN的维护。
  4.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  5.日    期   : 2012年09月15日
    作    者   : z00161729
    修改内容   : DTS2012090708320：MMC收到L的注册结果，ps cs卡是否有效状态需要更新，原来由gmm更新存在时序问题
  6.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  7.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  8.日    期   : 2014年4月29日
    作    者   : s00261364
    修改内容   : ecall项目修改服务状态上报
  9.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                  mmc收到eps 网络去注册(#3/6/8),上报注册状态和服务状态
*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsDetachCause8GprsAndNonGprsNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* 更新服务状态 */

    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, begin */
    /* 设置cs ps卡状态为无效 */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    /* 通知TAF当前的服务状态 */
    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, end */

    /*mmc收到eps网络去注册(#3/6/8),上报注册状态和服务状态*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    if(VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    }

    *penCsAddition  = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    *penPsAddition  = NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsDetachCause11PlmnNotAllow
 功能描述  : Eps detach Cause11的处理
 输入参数  : VOS_VOID
 输出参数  : penCsAddition
             penPsAddition
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月1日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年11月19日
    作    者   : w00176964
    修改内容   : V7R1 Phase III调整:联合注册ST修改

*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsDetachCause11PlmnNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    *penCsAddition  = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    *penPsAddition  = NAS_MMC_ProcEpsAttachRegFailCause11PlmnNotAllow();
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsDetachCause12TaNotAllow
 功能描述  : Eps detach Cause12的处理
 输入参数  : VOS_VOID
 输出参数  : penCsAddition
             penPsAddition
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月1日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年11月19日
    作    者   : w00176964
    修改内容   : V7R1 Phase III调整:联合注册ST修改
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  4.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  5.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsDetachCause12TaNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    VOS_UINT8                           ucSimCsRegStatus;

    *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_BUTT;

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    /*mmc收到eps 网络去注册(#12),上报注册状态和服务状态*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE_REGION);

    /* 如果CS允许注册而且CS卡有效则更改CS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (VOS_TRUE == ucSimCsRegStatus))
    {
        /*mmc收到eps 网络去注册(#12),上报注册状态和服务状态*/
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE_REGION);
    }

    *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsDetachCause13RoamNotAllow
 功能描述  : Eps detach Cause14的处理
 输入参数  : VOS_VOID
 输出参数  : penCsAddition
             penPsAddition
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月1日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年11月19日
    作    者   : w00176964
    修改内容   : V7R1 Phase III调整:联合注册ST修改
  3.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  4.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
    作    者   : l00305157
    修改内容   : DTS2015061003127
*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsDetachCause13RoamNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{

    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    *penCsAddition  = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    *penPsAddition  = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsDetachCause14GprsNotAllowInThisPlmn
 功能描述  : Eps detach Cause14的处理
 输入参数  : VOS_VOID
 输出参数  : penCsAddition
             penPsAddition
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月1日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年11月19日
    作    者   : w00176964
    修改内容   : V7R1 Phase III调整:联合注册ST修改

  3.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : DTS2011121307570: MMC没有维护LMM的EPLMN信息，现在统一调整
                  ATTACH/TAU/DETACH/SERVICE中被拒时EPLMN的维护。

  4.日    期   : 2011年11月19日
    作    者   : L65478
    修改内容   : DTS2012111402255:网络detach cause #14没有发起搜网
  5.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  6.日    期   : 2015年1月5日
    作    者   : h00285180
    修改内容   : LTE #14拒绝优化:DTS2015010401946
  7.日    期   : 2015年4月19日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
  7.日    期   : 2015年07月03日
    作    者   : l00305157
    修改内容   : DTS2015061003127

*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsDetachCause14GprsNotAllowInThisPlmn(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                             stPlmnWithRat;

    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));

    /* 添加禁止GPRS PLMN 信息 */
    NAS_MML_AddForbGprsPlmn(NAS_MML_GetCurrCampPlmnId());

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    if (VOS_TRUE == NAS_MMC_IsNeedDeleteEplmn_EpsDetachCause14GprsNotAllowInThisPlmn())
    {
        NAS_MMC_DeleteEPlmnList();
    }

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_LteRejCause14())
    {
        /* 需要Disable L全局变量 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);
        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_REJ_CAUSE_14);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetLteRejCause14EnableLteTimerLen());

        *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        return;
    }

    /* 24301_CR1499R3_(Rel-11)_C1-123437/ 24301_CR1520R1_(Rel-11)_C1-123939(rev
       of C1-123532)_24.301_Avoid to reselect E-UTRAN for #14/C1-141971拒绝原因
       值14时DISABLE LTE的处理更新,对应24301 5.5.2.3.2章节描述:
       #14: UE operating in CS/PS mode 1 of operation and supporting A/Gb mode or
            Iu mode may select GERAN or UTRAN radio access technology and proceed
            with the appropriate MM specific procedure according to the MM service state.
            In this case, the UE shall disable the E-UTRA capability (see subclause 4.5)*/
    if ( VOS_TRUE == NAS_MMC_IsNeedDisableL_EpsDetachCause14GprsNotAllowInThisPlmn() )
    {
        /* 需要Disable L全局变量 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_REJ_CAUSE_14);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetCsPsMode1EnableLteTimerLen());

        PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
        stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

        if (VOS_TRUE == NAS_MML_IsNeedAddDamPlmnInDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
        {
            NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                          NAS_MML_GetDamDisabledPlmnWithForbiddenPeriodTimeSlice(&stPlmnWithRat),
                                                          MMC_LMM_DISABLE_LTE_REASON_LTE_REJ_CAUSE_14);
        }

        *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
         return;
    }


    *penCsAddition  = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    *penPsAddition  = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;


    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsDetachCause15NoSuitableCell
 功能描述  : Eps detach Cause15的处理
 输入参数  : VOS_VOID
 输出参数  : penCsAddition
             penPsAddition
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月1日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年11月19日
    作    者   : w00176964
    修改内容   : V7R1 Phase III调整:联合注册ST修改
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  4.日    期   : 2015年07月03日
    作    者   : l00305157
    修改内容   : DTS2015061003127
*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsDetachCause15NoSuitableCell(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    *penCsAddition  = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    *penPsAddition  = NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsDetachCauseAbnormalCause
 功能描述  : EPS detach OtherCause的处理
 输入参数  : 无
 输出参数  : penCsAddition
             penPsAddition
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月1日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年11月19日
    作    者   : w00176964
    修改内容   : V7R1 Phase III调整:联合注册ST修改
  3.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : DTS2011122704039:更改函数名。
  4.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  5.日    期   : 2012年07月03日
    作    者   : s46746
    修改内容   : For CS/PS mode 1，选网状态机中联合注册仅EPS成功，之后接收到
                  detach，其它原因值，没有退状态机
  6.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsDetachCauseAbnormalCause(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_BUTT;

    *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
    }

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsServiceRequestFailCause3IllegalMs
 功能描述  : EpsServiceRequestFail Cause3的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : 新生成函数

  2.日    期   : 2011年12月30日
    作    者   : l65478
    修改内容   : 在迁到L模时,不立刻把CS设置成可选搜网,而是等待PS注册结果时
                 根据具体的原因值再设置

  3.日    期   : 2012年2月15日
    作    者   : z40661
    修改内容   : DTS2011121405203_PC测试发现问题,支持gUL多模时,L下被#3拒绝,到GU下指定搜网
  4.日    期   : 2012年09月15日
    作    者   : z00161729
    修改内容  : DTS2012090708320：MMC收到L的注册结果，ps cs卡是否有效状态需要更新，原来由gmm更新存在时序问题
  5.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  6.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  7.日    期   : 2014年4月29日
    作    者   : s00261364
    修改内容   : ecall项目修改服务状态上报
  8.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                 对于LMM Service Reject结果上报(cause=#3)，上报CS/PS注册状态和服务状态
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause3IllegalMs(VOS_VOID)
{
    /* 更新服务状态 */

    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, begin */
    /* 设置cs ps卡状态为无效 */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    /* 通知TAF当前的服务状态 */
    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, end */

    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);



    /*对于LMM Service Reject结果上报(cause=#3)，上报CS/PS注册状态和服务状态*/
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }


    /* modified by z40661 for DTS2011121405203_PC测试发现问题, 2012-02-15, begin */
    return NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;
    /* modified by z40661 for DTS2011121405203_PC测试发现问题, 2012-02-15, end */

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsServiceRequestFailCause6IllegalMe
 功能描述  : EpsServiceRequestFail Cause6的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause6IllegalMe(VOS_VOID)
{
    return NAS_MMC_ProcEpsServiceRequestFailCause3IllegalMs();
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFailCauseCause7EpsServiceRequestFailServNotAllow
 功能描述  : EpsServiceRequestFail Cause7的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00167002
    修改内容   : 新生成函数

  2.日    期   : 2011年12月30日
    作    者   : l65478
    修改内容   : 在迁到L模时,不立刻把CS设置成可选搜网,而是等待PS注册结果时
                 根据具体的原因值再设置

  3.日    期   : 2011年12月16日
    作    者   : w00176964
    修改内容   : V7R1 PhaseIV调整:增加disable LTE逻辑

  4.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  5.日    期   : 2012年07月02日
    作    者   : s46746
    修改内容   : For CS/PS mode 1，调整Disable/Enable L,按场景区分函数
  6.日    期   : 2012年7月27日
    作    者   : s00217060
    修改内容   : For CS/PS mode 1,带Disable LTE原因值
  7.日    期   : 2012年09月15日
    作    者   : z00161729
    修改内容   : DTS2012090708320：MMC收到L的注册结果，ps cs卡是否有效状态需要更新，原来由gmm更新存在时序问
  8.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  9.日    期   : 2014年4月29日
    作    者   : s00261364
    修改内容   : ecall项目修改服务状态上报
 10.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                 对于LMM Service Reject结果上报(cause=#7)，上报CS/PS注册状态和服务状态
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause7EpsServNotAllow(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstRatOrder;

    pstRatOrder     = NAS_MML_GetMsPrioRatList();


    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* 更新服务状态 */

    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, begin */
    /* 设置ps卡状态为无效 */
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);
     /*对于LMM Service Reject结果上报(cause=#7)，上报注册状态和服务状态*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);


    /* 通知TAF当前的服务状态 */
    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, end */

    /* 判断是否需要disable L */
    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_PsFailCause7PsServNotAllow())
    {
        /* 记录本地disable LTE标记 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_PS_USIM_INVALID);
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }

    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(pstRatOrder))
    {
        return NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
    }
    else
    {
        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

}



/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsServiceRequestFailCause9MsIdCannotBeDerivedByNW
 功能描述  : EpsServiceRequestFail Cause9的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  3.日    期   : 2015年11月19日
    作    者   : c00318887
    修改内容   : DTS2015111701196,ims没注册
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause9MsIdCannotBeDerivedByNW(VOS_VOID)
{
    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }

    return NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsServiceRequestFailCause10EpsServiceRequestFailImplicitlyDetached
 功能描述  : EpsServiceRequestFail Cause9的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  3.日    期   : 2015年11月19日
    作    者   : c00318887
    修改内容   : DTS2015111701196,ims没注册
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause10EpsImplicitlyDetached(VOS_VOID)
{
    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }

    return NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsServiceRequestFailCause11PlmnNotAllow
 功能描述  : EpsServiceRequestFail Cause11的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年08月05日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  3.日    期   : 2015年07月03日
    作    者   : l00305157
    修改内容   : DTS2015061003127 新生成函数
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause11PlmnNotAllow(VOS_VOID)
{
    NAS_MML_PLMN_ID_STRU               *pstCurPlmnId;

    pstCurPlmnId = NAS_MML_GetCurrCampPlmnId();

    /* 添加禁止网络信息,有更新时，向Usim更新文件 */
    if (VOS_TRUE == NAS_MML_AddForbPlmn(pstCurPlmnId))
    {
        NAS_MMC_SndUsimUpdateForbPlmnReq();
    }

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsServiceRequestFailCause12TaNotAllow
 功能描述  : EpsServiceRequestFail Cause12的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  3.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  9.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                 对于LMM Service Reject结果上报(cause=#12)，上报CS/PS注册状态和服务状态
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause12TaNotAllow(VOS_VOID)
{
    VOS_UINT8                           ucSimCsRegStatus;

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */



    /*对于LMM Service Reject结果上报(cause=#12)，上报CS/PS注册状态和服务状态*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE_REGION);
    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (VOS_TRUE == ucSimCsRegStatus))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE_REGION);
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
    }

    return NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsServiceRequestFailCause13RoamNotAllow
 功能描述  : EpsServiceRequestFail Cause13的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  3.日    期   : 2015年07月03日
    作    者   : l00305157
    修改内容   : DTS2015061003127
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause13RoamNotAllow(VOS_VOID)
{
    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsServiceRequestFailCause14GprsNotAllowInThisPlmn
 功能描述  : EpsServiceRequestFail Cause14的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2012年2月22日
    作    者   : h00202780
    修改内容   : V7R1C50 CSFB&PPAC&ETWS&ISR调整
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause14GprsNotAllowInThisPlmn(VOS_VOID)
{
    /* 添加禁止GPRS PLMN 信息 */
    NAS_MML_AddForbGprsPlmn(NAS_MML_GetCurrCampPlmnId());

    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsServiceRequestFailCause15NoSuitableCell
 功能描述  : EpsServiceRequestFail Cause15的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  3.日    期   : 2015年07月03日
    作    者   : l00305157
    修改内容   : DTS2015061003127
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause15NoSuitableCell(VOS_VOID)
{
    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;
}

/*****************************************************************************
函 数 名  : NAS_MMC_IsNeedDisableL_RegFailCause16AttmptCntMaxTimes
功能描述  : 注册被拒#16达最大次数是否需要disable lte
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_TRUE  - 需要Disable L
            VOS_FALSE - 不需要Disable L
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015年4月20日
  作    者   : z00161729
  修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_RegFailCause16AttmptCntMaxTimes(VOS_VOID)
{
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;

    enLUeMode        = NAS_MML_GetLteUeOperationMode();

    /* 当前LTE单模,返回不需要disable lte */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    /* 不是CS/PS mode 1或IMS VOICE可用 */
    if ((VOS_TRUE                               == NAS_MML_GetImsVoiceAvailFlg())
     || (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1  != enLUeMode))
    {
        return VOS_FALSE;
    }

    /* 协议版本小于R11,返回需要disable lte */
    if (NAS_MML_GetLte3gppRelVersion() < NAS_MML_3GPP_REL_R11)
    {
        return VOS_TRUE;
    }

    if (NAS_MML_PERSISTENT_BEARER_STATE_NOT_EXIST == NAS_MML_GetPersistentBearerState())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
函 数 名  : NAS_MMC_IsNeedDisableL_RegFailCause17AttmptCntMaxTimes
功能描述  : 注册被拒#17达最大次数是否需要disable lte
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_TRUE  - 需要Disable L
            VOS_FALSE - 不需要Disable L
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015年4月20日
  作    者   : z00161729
  修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_RegFailCause17AttmptCntMaxTimes(VOS_VOID)
{
    return NAS_MMC_IsNeedDisableL_RegFailCause16AttmptCntMaxTimes();
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsServiceRequestFailCause8GprsAndNonGprsNotAllow
 功能描述  : Eps ServiceRequestFail Cause8的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月19日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause8GprsAndNonGprsNotAllow(VOS_VOID)
{
    /* 协议版本小于R11按other cause处理 */
    if ( NAS_MML_3GPP_REL_R11 > NAS_MML_GetLte3gppRelVersion())
    {
        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
        }

       return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }

    /* 24301_CR1595R2_(Rel-11)_C1-124966 MMC增加普通和周期性TAU被拒以及SERVICE REQUEST被拒，
       原因值为8的处理,对应24301 5.6.1.5章节描述:
       #8:The UE shall set the EPS update status to EU3 ROAMING NOT ALLOWED (and
          shall store it according to subclause 5.1.3.3) and shall delete any GUTI,
          last visited registered TAI, TAI list and eKSI. The UE shall consider
          the USIM as invalid for EPS services until switching off or the UICC
          containing the USIM is removed. The UE shall enter the state EMM-DEREGISTERED.
       该CR受协议版本控制 */
    return NAS_MMC_ProcEpsServiceRequestFailCause3IllegalMs();
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsServiceRequestFailCause42SevereNetworkFailure
 功能描述  : EpsServiceRequestFail Cause42的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
1.日    期   : 2015年4月19日
  作    者   : z00161729
  修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause42SevereNetworkFailure(VOS_VOID)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));

    /* 协议版本小于R11按other cause处理 */
    if ( NAS_MML_3GPP_REL_R11 > NAS_MML_GetLte3gppRelVersion())
    {
        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
        }

       return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }

    /* 24301_CR1473R2_(Rel-11)_C1-123386 MMC增加ATTACH、TAU和SERVICE REQUEST过程中被拒原因值42的处理
      24301 5.6.1.5章节描述:
      The UE shall set the EPS update status to EU2 NOT UPDATED, and shall delete
    any GUTI, last visited registered TAI, eKSI, and list of equivalent PLMNs.
    The UE shall start an implementation specific timer, setting its value to 2
    times the value of T as defined in 3GPP TS 23.122 [6]. While this timer is
    running, the UE shall not consider the PLMN + RAT combination that provided
    this reject cause, a candidate for PLMN selection. The UE then enters state
    EMM-DEREGISTERED.PLMN-SEARCH in order to perform a PLMN selection according
    to 3GPP TS 23.122 [6].
       If A/Gb mode or Iu mode is supported by the UE, the UE shall in addition
    set the GMM state to GMM-DEREGISTERED, GPRS update status to GU2 NOT UPDATED,
    and shall delete the P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number.
    该CR受协议版本控制 */
    PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
    stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

    /* 将被拒#42的网络加入禁止接入技术网络列表中，禁止时间为2*T,触发搜网 */
    NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                  NAS_MML_GetDisabledPlmnRejCause42ForbiddenTimeSlice(),
                                                  MMC_LMM_DISABLE_LTE_REASON_BUTT);

    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsServiceRequestFailCause35RequestedServiceOptionNotAuthorizedInThisPlmn
 功能描述  : EpsServiceRequestFail Cause35的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年03月06日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年12月24日
    作    者   : w00242748
    修改内容   : DTS2013101106863:L下被拒原因值#35，只有在R10及其协议以上处理才与#11
                 原因值处理相同，否则当做OTHER CAUSE来处理。

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause35ReqServOptNotAuthorizedInThisPlmn(VOS_VOID)
{
    NAS_MML_MS_3GPP_REL_STRU           *pstMs3GppRel = VOS_NULL_PTR;

    pstMs3GppRel    = NAS_MML_GetMs3GppRel();

    if ( NAS_MML_3GPP_REL_R9 >= pstMs3GppRel->enLteNasRelease )
    {
        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
        }

       return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }
    else
    {
        return NAS_MMC_ProcEpsServiceRequestFailCause11PlmnNotAllow();
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsServiceRequestFailCause257AccessBarrd
 功能描述  : EpsServiceRequestFail AccessBarrd的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2012年2月3日
    作    者   : w00167002
    修改内容   : DTS2011122704039:在注册失败原因值的函数命名中增加原因值，
                  保持函数命名的一致性。
  3.日    期   : 2012年2月16日
    作    者   : h00202780
    修改内容   : V7R1C50 CSFB&PPAC&ETWS&ISR调整
                   CSFB过程中，收到LMM上报的service被拒，有以下几种场景需要重选回GU下，进行语音的尝试：
                接入被禁或者NAS的信令被网络拒绝
                协议原文：3GPP 24.301,5.6.1.6章节, Abnormal cases in the UE :

                1)Access barred because of access class barring or NAS signalling connection establishment rejected by the network
                    If the service request was initiated for CS fallback, the UE shall select GERAN or UTRAN radio access technology. The UE then proceeds with appropriate MM and CC specific procedures. The EMM sublayer shall not indicate the abort of the service request procedure to the MM sublayer。

                2)底层链路失败（Lower layer failure before the service request procedure is completed (see subclause 5.6.1.4) or before SERVICE REJECT message is received）。

                3)收到Service Reject消息，被拒原因值非24.301的5.6.1.5中定义 other
                    EMM cause values than those treated in subclause 5.6.1.5(原因值为#3，
                    #6，#7，#9，#10，#11，#12，#13，#15，#18，#25，#39)
  7.日    期   : 2012年06月13日
    作    者   : s46746
    修改内容   : For CS/PS mode 1，修改服务请求接入禁止的处理

  8.日    期   : 2012年7月25日
    作    者   : z00161729
    修改内容   : DTS2012072506927:MMC收到LMM 的service result ind指示access bar时
                 不应更新服务状态为限制服务，应该由L上报正常服务状态
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause257AccessBarrd(VOS_VOID)
{


    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_BUTT);
    }

    /* service request被接入禁止并不代表不能进行TAU的接入 */
    return NAS_MMC_ADDITIONAL_ACTION_BUTT;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsServiceRequestFailCause256AuthRej
 功能描述  : EpsServiceRequestFail Reg Auth rej的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : 新生成函数

  2.日    期   : 2012年2月3日
    作    者   : w00167002
    修改内容   : DTS2011122704039:在注册失败原因值的函数命名中增加原因值，
                  保持函数命名的一致性。
  3.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  4.日    期   : 2012年09月15日
    作    者   : z00161729
    修改内容  : DTS2012090708320：MMC收到L的注册结果，ps cs卡是否有效状态需要更新，原来由gmm更新存在时序问题
  5.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  6.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  7.日    期   : 2014年4月29日
    作    者   : s00261364
    修改内容   : ecall项目修改服务状态上报
  8.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                 对于LMM Service Reject过程中，鉴权被拒绝，上报注册状态和服务状态
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause256AuthRej(VOS_VOID)
{
    /* 删除EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* 更新服务状态 */

    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, begin */
    /* 设置cs ps卡状态为无效 */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    /* 通知TAF当前的服务状态 */
    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, end */



    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);



    /*对于LMM Service Reject过程中，鉴权被拒绝，上报注册状态和服务状态*/
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsServiceRequestFailCauseCsDomainNotAvailable
 功能描述  : CsDomainNotAvailable的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月16日
    作    者   : h00202780
    修改内容   : 新生成函数
  2.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  3.日    期   : 2015年4月18日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
  3.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                 LMM Service Reject结果上报(cause=#18),
                 不上报CS域注册状态和服务状态，待后续TAU或ATTCH过程中在根据收到的网络结果进行上报
  5.日    期   : 2015年9月6日
    作    者   : z00359541
    修改内容   : DTS2015081407087: 接口调整，删除bitOpReqType项
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause18CsDomainNotAvailable(VOS_VOID)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));

    /* LMM Service Reject结果上报(cause=#18)*/
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);


    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_ServiceReqFailCause18CsDomainNotAvailable())
    {
        /* 需要Disable L全局变量 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

        /* 紧急呼叫启动定时器时长与普通呼叫不同，disable lte原因值也不同 */
        if (NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST == NAS_MML_GetCsfbServiceStatus())
        {
            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_EMERGENCY_CALL);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetCsfbEmgCallEnableLteTimerLen());
        }
        else
        {
            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetCsPsMode1EnableLteTimerLen());
        }

        PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
        stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

        if (VOS_TRUE == NAS_MML_IsNeedAddDamPlmnInDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
        {
            NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                          NAS_MML_GetDamDisabledPlmnWithForbiddenPeriodTimeSlice(&stPlmnWithRat),
                                                          MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
        }

        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_NORMAL_CAMP_ON);
    }

    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsServiceRequestFailCauseNotAuthorizedForThisCsg
 功能描述  : NotAuthorizedForThisCsg的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012年2月16日
    作    者   : h00202780
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause25NotAuthorizedForThisCsg(VOS_VOID)
{
    /* 更新服务状态 */
    NAS_MMC_SetCsServiceStatus(NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_SetPsServiceStatus(NAS_MMC_LIMITED_SERVICE);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
    }

    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsServiceRequestFailCauseCsDomainTempNotAvailable
 功能描述  : CsDomainTempNotAvailable的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012年2月16日
    作    者   : h00202780
    修改内容   : 新生成函数
  2.日    期   : 2014年4月8日
    作    者   : B00269685
    修改内容   : CSFB失败原因值#39不更新CS服务和注册状态，否则导致AP不再下发呼叫请求
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause39CsDomainTempNotAvailable(VOS_VOID)
{

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
    }

    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsServiceRequestFailCause40NoEpsBearerActived
 功能描述  : EpsServiceRequestFail Cause40的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2012年1月11日
    作    者   : w00176964
    修改内容   : V7R1 PhaseIV BBIT调整
  3.日    期   : 2012年2月22日
    作    者   : h00202780
    修改内容   : V7R1C50 CSFB&PPAC&ETWS&ISR调整
                CSFB过程中，收到LMM上报的service被拒，有以下几种场景需要重选回GU下，进行语音的尝试：
                接入被禁或者NAS的信令被网络拒绝
                协议原文：3GPP 24.301,5.6.1.6章节, Abnormal cases in the UE :

                1)Access barred because of access class barring or NAS signalling connection establishment rejected by the network
                    If the service request was initiated for CS fallback, the UE shall select GERAN or UTRAN radio access technology. The UE then proceeds with appropriate MM and CC specific procedures. The EMM sublayer shall not indicate the abort of the service request procedure to the MM sublayer。

                2)底层链路失败（Lower layer failure before the service request procedure is completed (see subclause 5.6.1.4) or before SERVICE REJECT message is received）。

                3)收到Service Reject消息，被拒原因值非24.301的5.6.1.5中定义 other
                    EMM cause values than those treated in subclause 5.6.1.5(原因值为#3，
                    #6，#7，#9，#10，#11，#12，#13，#15，#18，#25，#39)
  4.日    期   : 2013年12月25日
    作    者   : f62575
    修改内容   : DTS2013101106863:L下被拒原因值#40，只有在R10及其协议以上处理才与#10
                 原因值处理相同，否则当做OTHER CAUSE来处理。
  5.日    期   : 2015年11月19日
    作    者   : c00318887
    修改内容   : DTS2015111701196,ims没注册
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause40NoEpsBearerActived(VOS_VOID)
{
    NAS_MML_MS_3GPP_REL_STRU           *pstMs3GppRel = VOS_NULL_PTR;

    pstMs3GppRel = NAS_MML_GetMs3GppRel();
    /* 版本为R10版本及以后版本，当前原因值是#40将原因值转定义成#10，见协议3GPP
    24.301 5.5.3.3.5 */
    if (NAS_MML_3GPP_REL_R9 >= pstMs3GppRel->enLteNasRelease)
    {
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
        }

        return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }
    else
    {
        if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
        {
            return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        }

        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
        }

        return NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
    }
}




#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailForbLaWithValidPeriod
 功能描述  : Cs注册被拒禁止LA有效时长的处理
 输入参数  : NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enRegFailCause,
              NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8    enAction
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月23日
   作    者   : z00359541
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCsRegFailForbLaWithValidPeriod(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enRegFailCause,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8    enAction
)
{
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU   *pstForbLaWithValidPeriodCfg = VOS_NULL_PTR;
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_STRU         stForbLaWithValidPeriodCfgInfo;
    VOS_UINT32                                              ulAttempcnt;

    pstForbLaWithValidPeriodCfg                             = NAS_MML_GetForbLaWithValidPeriodCfg();
    stForbLaWithValidPeriodCfgInfo.usRegFailCause           = enRegFailCause;
    stForbLaWithValidPeriodCfgInfo.usForbLaValidPeriodLen   = NAS_MML_GetForbLaWithValidPeriodTimerLen(enRegFailCause, pstForbLaWithValidPeriodCfg);
    stForbLaWithValidPeriodCfgInfo.usPunishTimeLen          = NAS_MML_GetCustomizedForbLaPunishTimeLen(enRegFailCause, pstForbLaWithValidPeriodCfg);
    ulAttempcnt                                             = NAS_MMC_GetRegRsltAttemptCounter(MM_MMC_CS_REG_RESULT_IND);

    /* 注册失败原因值不再定制列表中，不需要处理 */
    if (VOS_FALSE == NAS_MMC_IsFailCauseInCustomizedForbLaCfgList(enRegFailCause))
    {
        return;
    }

    /* 当前是否需要搜网 */
    if (NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION == enAction)
    {
        /* 拒绝原因值为17且SOR特性打开且尝试次数不大于4次，不需要加入禁止LA列表 */
        if ( (VOS_TRUE                               == NAS_MML_GetCsRejSearchSupportFlg())
          && (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == enRegFailCause)
          && (NAS_MML_MAX_CS_REG_FAIL_CNT            == ulAttempcnt) )
        {
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcCsRegFailForbLaWithValidPeriod(): SOR ON, Don't add to Customized Forb La since attempt cnt is 4");
            return;
        }

        if (VOS_TRUE == NAS_MML_AddCsRegFailLaIntoForbLaListWithValidPeriod(&stForbLaWithValidPeriodCfgInfo))
        {
            /* 启动定时器 */
            NAS_MML_StartCustomizedForbLaTimer();
        }
    }
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFail
 功能描述  : Cs注册被拒的处理
 输入参数  : VOS_UINT16                          usCause,
              VOS_UINT32                          ulAttemptCnt
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : l00130025
   修改内容   : 新生成函数

 2.日    期   : 2012年2月4日
   作    者   : w00167002
   修改内容   : 修改函数参数，增加保存注册结果指针到当前文件的全局变量中，
                 便于在处理注册结果中的函数中使用注册结果的所有信息。
 3.日    期   : 2013年8月15日
   作    者   : l00208543
   修改内容   : 网络拒绝原因值主动上报
 4.日    期   : 2014年01月10日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseIII项目
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFail(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType,
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRsltInd
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulTblSize;
    NAS_MMC_PROC_REG_FAIL_FUNC_PTR      pRegFailProcFunc = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAction;

    /* 保存注册结果消息 */
    NAS_MMC_SaveRegRsltCtx(enRegRsltType, pstCsRegRsltInd);

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */

    /* AT^REJINFO主动上报，将REJINFO上报给MSCC 非联合注册的时候才上报 */
    if (VOS_FALSE == pstCsRegRsltInd->ucIsComBined)
    {
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS, VOS_FALSE, pstCsRegRsltInd->enRegFailCause);
    }

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */

#if (FEATURE_ON == FEATURE_PTM)
    /* 记录CS注册失败异常log */
    NAS_MMC_CsRegErrRecord(pstCsRegRsltInd);
#endif

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_CS_REG_FAIL);

    ulTblSize = sizeof(gastMmcProcCsRegFailCause)/sizeof(gastMmcProcCsRegFailCause[0]);

    /*在CS注册原因表gastMmcProcCsRegFailCause中，查找对应的处理函数*/
    for ( i = 0 ; i < ulTblSize; i++ )
    {
        if (pstCsRegRsltInd->enRegFailCause == gastMmcProcCsRegFailCause[i].enRegCause)
        {
            pRegFailProcFunc = gastMmcProcCsRegFailCause[i].pRegFailProcFunc;

            break;
        }

    }

    /*找到后，调用对应的处理,并返回对应的后续处理时*/
    if (VOS_NULL_PTR != pRegFailProcFunc)
    {
        enAction = pRegFailProcFunc();

    }
    /*没有找到时，按照CS Other Cause处理*/
    else
    {
        enAction = NAS_MMC_ProcCsRegFailCauseAbnormalCause(pstCsRegRsltInd->enRegFailCause,
                                                   pstCsRegRsltInd->ulLuAttemptCnt);
    }

    NAS_MMC_ProcCsRegFailForbLaWithValidPeriod(pstCsRegRsltInd->enRegFailCause, enAction);

    return enAction;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegFail
 功能描述  : Ps注册被拒的处理
 输入参数  : VOS_UINT16                          usCause,
              VOS_UINT32                          ulAttemptCnt
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2013年8月15日
    作    者   : l00208543
    修改内容   : 网络拒绝原因值主动上报
  3.日    期   : 2014年01月10日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseIII项目
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFail(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType,
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRsltInd
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulTblSize;
    NAS_MMC_PROC_REG_FAIL_FUNC_PTR      pRegFailProcFunc = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAction;

    /* 保存注册结果消息 */
    NAS_MMC_SaveRegRsltCtx(enRegRsltType, pstPsRegRsltInd);

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */

    /* AT^REJINFO主动上报，将REJINFO上报给MSCC */
    if (GMM_MMC_REG_DOMAIN_PS_CS == pstPsRegRsltInd->enRsltDomain)
    {
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_FALSE, pstPsRegRsltInd->enRegFailCause);
    }
    else
    {
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_FALSE, pstPsRegRsltInd->enRegFailCause);
    }

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */

#if (FEATURE_ON == FEATURE_PTM)
    /* 记录PS注册失败异常log */
    NAS_MMC_PsRegErrRecord(pstPsRegRsltInd);
#endif

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_PS_REG_FAIL);

    ulTblSize = sizeof(gastMmcProcPsRegFailCause)/sizeof(gastMmcProcPsRegFailCause[0]);

    /*在PS注册原因表gastMmcProcPsRegFailCause中，查找对应的处理函数*/
    for ( i = 0 ; i < ulTblSize; i++ )
    {
        if (pstPsRegRsltInd->enRegFailCause == gastMmcProcPsRegFailCause[i].enRegCause)
        {
            pRegFailProcFunc = gastMmcProcPsRegFailCause[i].pRegFailProcFunc;

            break;
        }
    }

    /*找到后，调用对应的处理,并返回对应的后续处理时*/
    if (VOS_NULL_PTR != pRegFailProcFunc)
    {
        enAction = pRegFailProcFunc();

    }
    /*没有找到时，按照PS Other Cause处理*/
    else
    {
        enAction = NAS_MMC_ProcPsRegFailCauseAbnormalCause(pstPsRegRsltInd->enRegFailCause,
                                                           pstPsRegRsltInd->ulRegCounter);
    }

    return enAction;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsServiceRegFail
 功能描述  : Ps业务被拒的处理
 输入参数  : VOS_UINT16                          usCause,
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月5日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : 修改函数参数，增加保存注册结果指针到当前文件的全局变量中，
                 便于在处理注册结果中的函数中使用注册结果的所有信息。
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsServiceRegFail(
    GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU                 *pstServiceRsltInd
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulTblSize;
    NAS_MMC_PROC_REG_FAIL_FUNC_PTR      pRegFailProcFunc = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAction;

    /* 保存注册结果消息 */
    NAS_MMC_SaveRegRsltCtx(GMM_MMC_PS_SERVICE_RESULT_IND, pstServiceRsltInd);

#if (FEATURE_ON == FEATURE_PTM)
    /* 记录PS注册失败异常log */
    NAS_MMC_PsServiceRegErrRecord(pstServiceRsltInd);
#endif

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_PS_SERVICE_REG_FAIL);

    ulTblSize = sizeof(gastMmcProcPsRegFailCause)/sizeof(gastMmcProcPsRegFailCause[0]);

    /*在PS注册原因表gastMmcProcPsRegFailCause中，查找对应的处理函数*/
    for ( i = 0 ; i < ulTblSize; i++ )
    {
        if (pstServiceRsltInd->enRegFailCause == gastMmcProcPsRegFailCause[i].enRegCause)
        {
            pRegFailProcFunc = gastMmcProcPsRegFailCause[i].pRegFailProcFunc;

            break;
        }

    }
    /*找到后，调用对应的处理,并返回对应的后续处理时*/
    if (VOS_NULL_PTR != pRegFailProcFunc)
    {
        enAction = pRegFailProcFunc();

    }
    /*没有找到时，受限驻留*/
    else
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
    }

    return enAction;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcGmmNetworkDetachInd
 功能描述  : 处理GMM的网侧DETACH消息
 输入参数  : pstDetachMsg GMM的网侧detach消息
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月05日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  3.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态

  4.日    期   : 2013年7月1日
    作    者   : w00167002
    修改内容   : SVLTE STC:GMM联合注册成功后，网侧发起imsi DETACH，此时注册状态为
                 NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH，服务状态为NORMAL SERVICE ;
                 修改为如果当前是IMSI detach,则不处理；
  5.日    期   : 2014年04月4日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:服务状态上报到mmc
  6.日    期   : 2014年11月29日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseI项目修改

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcGmmNetworkDetachInd(
    MMCGMM_NETWORK_DETACH_IND_STRU     *pstDetachMsg
)
{

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-28, begin */

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-28, end */
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAction;
    VOS_UINT32                          i;
    VOS_UINT32                          ulTblSize;
    NAS_MMC_PROC_REG_FAIL_FUNC_PTR      pRegFailProcFunc = VOS_NULL_PTR;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* 保存注册结果消息 */
    NAS_MMC_SaveRegRsltCtx(GMM_MMC_PS_NETWORK_DETACH_IND, pstDetachMsg);

    enAction            = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    ulTblSize           = sizeof(gastMmcProcPsRegFailCause)/sizeof(gastMmcProcPsRegFailCause[0]);

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-29, begin */

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_GUT_NW_DETACH);

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-29, end */
    /* 向TAF发送PS域的服务状态 */
    /* Added by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, begin*/
    NAS_MMC_SndMsccDetachInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstDetachMsg->ulDetachType,
    /* Added by l00167671 for 主动上报AT命令控制下移至C核 , 2013-04-01, end*/
                            pstDetachMsg->ulDetachCause);

    if (NAS_MMC_GMM_NT_DETACH_NOATTACH == pstDetachMsg->ulDetachType)
    {
        /*在Eps注册原因表gastMmcProcEpsRegFailCause中，查找对应的处理函数*/
        for ( i = 0 ; i < ulTblSize; i++ )
        {
            if (pstDetachMsg->ulDetachCause == gastMmcProcPsRegFailCause[i].enRegCause)
            {
                pRegFailProcFunc = gastMmcProcPsRegFailCause[i].pRegFailProcFunc;

                break;
            }

        }

        /*找到后，调用对应的处理,并返回对应的后续处理时*/
        if (VOS_NULL_PTR != pRegFailProcFunc)
        {
            enAction = pRegFailProcFunc();
        }
        else
        {
            /* 获取CS addition,并与NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON比较，
               如果不需要发起搜网则更新PS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
            enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
            enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON, enPrioAdditionalAction);
            if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
            {

                /* Added by s00261364 for V3R360_eCall项目, 2014-4-4, begin */
                NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
                /* Added by s00261364 for V3R360_eCall项目, 2014-4-4, end */
                NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            }

            enAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
        }
    }

    else if ( NAS_MMC_GMM_NT_DETACH_IMSI == pstDetachMsg->ulDetachType )
    {
        return NAS_MMC_ADDITIONAL_ACTION_BUTT;
    }

    else
    {
        /*当为REATTACH类型的时候，不上报注册状态和服务状态，*/
        enAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
    }

    return enAction;

}

#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCauseAbnormalCause
 功能描述  : 联合EPS OtherCause的处理
 输入参数  : VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
             penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月25日
    作    者   : z00161729
    修改内容   : 新生成函数
                 1)  attemptCount < MaxCount时，返回NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT
                 2)  attemptCount >= MaxCount时，返回NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION

  2.日    期   : 2012年1月3日
    作    者   : w00167002
    修改内容   : DTS2011122006209/DTS2011122704039:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网.
                1): 非UE主动发起注册的原因值(如注册被拒cause为260),此时若是在
                    OnPlmn/PlmnList下,不需要进行可选的搜网则返回为
                    NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON

                2):增加如下场景的考虑:手动模式下，当前Plmn不是用户指定的PLMN,
                且当前PLMN不在EPlmn列表里，则需要返回可选的搜网策略。
  3.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  4.日    期   : 2012年06月02日
    作    者   : s00217060
    修改内容   : For CS/PS mode 1,联合注册失败，需要Disable L
  5.日    期   : 2012年7月27日
    作    者   : s00217060
    修改内容   : For CS/PS mode 1,带Disable LTE原因值
  6.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  7.日    期   : 2013年6月3日
    作    者   : z00161729
    修改内容   : SVLTE 修改
  8.日    期   : 2014年01月10日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseIII项目
  9.日    期   : 2015年1月15日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
 10.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCauseAbnormalCause(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    VOS_UINT32                          ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType;

    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    /* 取得当前的注册结果消息类型 */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    /* 取得Attempt Counter的值 */
    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    /* cs ps域均注册失败,当前不在在ONPLMN或者PLMN LIST状态机，需根据AttemptCounter
       来返回不同的ADDITIONAL ACTION值 */
    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        /* 联合EPS注册失败Attempt未达到最大次数的处理的处理 */
        NAS_MMC_ProcCombinedEpsRegFailAttemptCouterLessThanMaxTimes(penPsRegAdditionalAction,
                                                                    penCsRegAdditionalAction);
    }
    else
    {
        /* 删除EPLMN */
        NAS_MMC_DeleteEPlmnList();

        /* 更新服务状态 */

        /* 通知TAF当前的服务状态 */

        if ( VOS_TRUE == NAS_MMC_IsNeedDisableL_CombinedRegRsltFailMaxTimes() )
        {
            /* 需要Disable L全局变量 */
            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

            /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-18, begin */
            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
            /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-18, end */

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetCsPsMode1EnableLteTimerLen());

            PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
            stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

            if (VOS_TRUE == NAS_MML_IsNeedAddDamPlmnInDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
            {
                NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                              NAS_MML_GetDamDisabledPlmnWithForbiddenPeriodTimeSlice(&stPlmnWithRat),
                                                              MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
            }

            *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
            *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        }
        else
        {
            *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
            *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
        }

        /*针对增加内部列表搜网时，也要上报状态，参考NAS_MMC_RcvLmmMmcTauResultInd_OnPlmn()中的流程增加内部列表搜网*/
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(*penCsRegAdditionalAction))
        {
            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }


        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCombinedEpsRegFailCause401OtherCause
 功能描述  : 联合EPS OtherCause的处理
 输入参数  : VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
             penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月25日
    作    者   : z00161729
    修改内容   : 新生成函数
                 1)  attemptCount < MaxCount时，返回NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT
                 2)  attemptCount >= MaxCount时，返回NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION

  2.日    期   : 2012年1月3日
    作    者   : w00167002
    修改内容   : DTS2011122006209/DTS2011122704039:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网.
                1): 非UE主动发起注册的原因值(如注册被拒cause为260),此时若是在
                    OnPlmn/PlmnList下,不需要进行可选的搜网则返回为
                    NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON

                2):增加如下场景的考虑:手动模式下，当前Plmn不是用户指定的PLMN,
                且当前PLMN不在EPlmn列表里，则需要返回可选的搜网策略。
  3.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  4.日    期   : 2012年06月07日
    作    者   : s00217060
    修改内容   : #401，尝试次数达到5次，需要Disable L
  5.日    期   : 2012年7月27日
    作    者   : s00217060
    修改内容   : For CS/PS mode 1,带Disable LTE原因值
  6.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  7.日    期   : 2013年6月3日
    作    者   : z00161729
    修改内容   : SVLTE 修改
  8.日    期   : 2014年01月10日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseIII项目
  9.日    期   : 2015年1月15日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
  10.日    期   : 2015年4月22日
     作    者   : z00161729
     修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause401OtherCause(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    VOS_UINT32                          ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType;

    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    /* 取得当前的注册类型 */
    enRegRsltType = NAS_MMC_GetRegRsltType();
    ulAttemptCnt  = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    /* cs ps域均注册失败,当前不在在ONPLMN或者PLMN LIST状态机，需根据AttemptCounter
       来返回不同的ADDITIONAL ACTION值 */
    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        NAS_MMC_ProcCombinedEpsRegFailAttemptCouterLessThanMaxTimes(penPsRegAdditionalAction,
                                                                    penCsRegAdditionalAction);
    }
    else
    {
        /* 删除EPLMN */
        NAS_MMC_DeleteEPlmnList();

        /* 更新服务状态 */

        /* 通知TAF当前的服务状态 */

        if ( VOS_TRUE == NAS_MMC_IsNeedDisableL_CombinedRegRsltFailMaxTimes() )
        {
            /* 需要Disable L全局变量 */
            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

            /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-18, begin */
            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
            /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-18, end */

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetCsPsMode1EnableLteTimerLen());

            PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
            stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

            if (VOS_TRUE == NAS_MML_IsNeedAddDamPlmnInDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
            {
                NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                               NAS_MML_GetDamDisabledPlmnWithForbiddenPeriodTimeSlice(&stPlmnWithRat),
                                                               MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
            }

            *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
            *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        }
        else
        {
            *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
            *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
        }
        /*针对增加内部列表搜网时，也要上报状态，参考NAS_MMC_RcvLmmMmcTauResultInd_OnPlmn()中的流程增加内部列表搜网*/
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(*penCsRegAdditionalAction))
        {
            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }

        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }
    }
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCombinedEpsRegFailAttemptCouterLessThanMaxTimes
 功能描述  : 联合EPS注册失败Attempt未达到最大次数的处理的处理
 输入参数  : 无
 输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
              penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : 新生成函数
  8.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                 mmc收到COMBINED ATU錜EJ(#3/6/8),上报注册状态和服务状态
                 MMC接收到LMM模块注册结果COMBINED TAU REJ(other casue),未达到最大次数的处理 更新PS域注册状态，并上报服务状态
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailAttemptCouterLessThanMaxTimes(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction
)
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnInfo        = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn     = VOS_NULL_PTR;
    VOS_UINT32                          ulInEplmnListFlag;
    VOS_UINT32                          ulUserSpecPlmnFlag;

    /* 判断当前网络是否是用户指定的网络 */
    pstUserSpecPlmn    = NAS_MMC_GetUserSpecPlmnId();
    ulUserSpecPlmnFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(NAS_MML_GetCurrCampPlmnId(),
                                                &(pstUserSpecPlmn->stPlmnId));

    /* 判断当前网络是否在EPlmn列表里 */
    pstEplmnInfo       = NAS_MML_GetEquPlmnList();

    ulInEplmnListFlag  = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(NAS_MML_GetCurrCampPlmnId(),
                                              pstEplmnInfo->ucEquPlmnNum,
                                              pstEplmnInfo->astEquPlmnAddr);

    /* 手动模式下，当前Plmn不是用户指定的PLMN,且当前PLMN不在EPlmn列表里，
       则认为当前plmn是NOT ALLOWED，需要进行搜网 */
    if ( (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
      && (VOS_FALSE                          == ulUserSpecPlmnFlag)
      && (VOS_FALSE                          == ulInEplmnListFlag) )
    {
        *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }

        return ;
    }

    /* 与GU保持一致,通过判断服务状态来决定是否更新注册状态和服务状态，*/
    if (NAS_MMC_NORMAL_SERVICE != NAS_MMC_GetCurrCsService())
    {
         NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
         NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS,NAS_MMC_LIMITED_SERVICE);
    }
    if (NAS_MMC_NORMAL_SERVICE != NAS_MMC_GetCurrPsService())
    {
         NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
         NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS,NAS_MMC_LIMITED_SERVICE);
    }
    /* 否则mmc继续等待注册结果 */
    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCauseAbnormalCause
 功能描述  : 联合EPS OtherCause的处理
 输入参数  : VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 输出参数  : penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月25日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  4.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  5.日    期   : 2014年01月11日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseIII 项目修改

  6.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                对于EMM的COMBINED TAU(eps only, other cause)成功，上报CS/PS注册状态和服务状态
  7.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : DTS2015082002854: 漫游标记不准
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCauseAbnormalCause(
    VOS_UINT16                                               usCause,
    VOS_UINT32                                               ulAttemptCnt,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    /*
    1)  attemptCount < MaxCount时，返回NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT
    2)  attemptCount >= MaxCount时，返回NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION
    */

    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-1-11, begin */
    /* 按照最新协议,other cause也认为EPS注册成功,因此更新服务状态 */
    NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-1-11, end */

    /* ps域注册成功，cs域注册失败 */
    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        /* 与GU保持一致,通过判断服务状态来决定是否更新注册状态和服务状态，*/
        if (NAS_MMC_NORMAL_SERVICE != NAS_MMC_GetCurrCsService())
        {
             /* 更新注册状态为0 */
             NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
             NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
        }
        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
    }
    else
    {
        /* 删除EPLMN */
        NAS_MMC_DeleteEPlmnList();

        /* 更新服务状态 */

        /* 通知TAF当前的服务状态 */

        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        /*对于EMM的COMBINED TAU/ATTACH(eps only,  other cause)成功,且达到最大次数，上报CS/PS注册状态和服务状态*/
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);

        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

    }

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCombinedAttachEpsRegFail
 功能描述  : 联合Eps attach被拒的处理
 输入参数  : VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 输出参数  : penPsRegAdditionalAction - 收到注册attach结果后，协议要求的ps域的additional动作类型
             penCsRegAdditionalAction - 收到注册attach结果后，协议要求的cs域的additional动作类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月25日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2011年12月13日
    作    者   : z00161729
    修改内容   : DTS2011121302231:attach被拒#9/#10按协议应该按other cause处理
  3.日    期   : 2011年1月5日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV修改
  4.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : DTS2011122704039:将注册结果类型以及注册消息传递给处理注册结果
                  函数，扩展注册结果函数的处理能力。
  5.日    期   : 2013年8月15日
    作    者   : l00208543
    修改内容   : 将网络拒绝原因值上报
  6.日    期   : 2014年01月10日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseIII项目
  7.日    期   : 2015年10月23日
    作    者   : l00289540
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 修改
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedAttachEpsRegFail(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType,
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulTblSize;
    NAS_MMC_PROC_COMBINED_EPS_REG_FAIL_FUNC_PTR             pRegFailProcFunc = VOS_NULL_PTR;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegRsltCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause;

    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    pstDPlmnNPlmnCfgInfo  = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    /* 保存注册结果消息 */
    NAS_MMC_SaveRegRsltCtx(enRegRsltType, pstLmmAttachIndMsg);

    /* 从联合注册结果消息中取得拒绝原因值 */
    NAS_MMC_ConverLmmCombinedAttachRsltToMMLCause(pstLmmAttachIndMsg,
                                          &enPsRegRsltCause, &enCsRegRsltCause);

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
    NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_FALSE, enPsRegRsltCause);
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_COMBINE_EPS_REG_ATTACH_FAIL);

    ulTblSize = sizeof(gastMmcProcCombinedAttachEpsRegFailCause)/sizeof(gastMmcProcCombinedAttachEpsRegFailCause[0]);

    /* 在联合Eps注册原因表gastMmcProcCombinedAttachEpsRegFailCause中，查找对应的处理函数 */
    for ( i = 0 ; i < ulTblSize; i++ )
    {
        if (enPsRegRsltCause == gastMmcProcCombinedAttachEpsRegFailCause[i].enRegCause)
        {
            pRegFailProcFunc = gastMmcProcCombinedAttachEpsRegFailCause[i].pCombinedEpsRegFailProcFunc;
            break;
        }

    }

    /*找到后，调用对应的处理,并返回对应的后续处理时*/
    if (VOS_NULL_PTR != pRegFailProcFunc)
    {
        pRegFailProcFunc(penPsRegAdditionalAction, penCsRegAdditionalAction);

    }
    /*没有找到时，按照PS Other Cause处理*/
    else
    {
        NAS_MMC_ProcCombinedEpsRegFailCauseAbnormalCause(penPsRegAdditionalAction,
                                                         penCsRegAdditionalAction);
    }

    if (VOS_TRUE == NAS_MML_IsNetworkRegFailCause(enPsRegRsltCause))
    {
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_EPS, enPsRegRsltCause);
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS, enPsRegRsltCause);

        /* 更新DPLMN NPLMN列表 */
        if (VOS_TRUE == NAS_MMC_IsRoam())
        {
            NAS_MMC_UpdateDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_PS_CS, NAS_MMC_MAX_CFG_NPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList);
            NAS_MMC_DeleteDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_PS_CS, &pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList);
            NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(pstDPlmnNPlmnCfgInfo);
            NAS_MMC_LogDplmnNplmnList();
        }
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCombinedTauEpsRegFail
 功能描述  : 联合Eps tau被拒的处理
 输入参数  : VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 输出参数  : penPsRegAdditionalAction - 收到注册tau结果后，协议要求的ps域的additional动作类型
             penCsRegAdditionalAction - 收到注册tau结果后，协议要求的cs域的additional动作类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月13日
    作    者   : z00161729
    修改内容   : DTS2011121302231:attach被拒#9/#10按协议应该按other cause处理
  2.日    期   : 2011年1月7日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV修改
  3.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : DTS2011122704039:将注册结果类型以及注册消息传递给处理注册结果
                  函数，扩展注册结果函数的处理能力。
  4.日    期   : 2013年8月15日
    作    者   : l00208543
    修改内容   : 将网络拒绝原因值上报
  5.日    期   : 2014年01月10日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseIII项目
  6.日    期   : 2014年11月3日
    作    者   : z00161729
    修改内容   : 开机漫游搜网项目修改
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedTauEpsRegFail(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType,
    LMM_MMC_TAU_RESULT_IND_STRU                            *pstLmmTauIndMsg,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulTblSize;
    NAS_MMC_PROC_COMBINED_EPS_REG_FAIL_FUNC_PTR             pRegFailProcFunc = VOS_NULL_PTR;

    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegRsltCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause;

    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    pstDPlmnNPlmnCfgInfo  = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    /* 保存注册结果消息 */
    NAS_MMC_SaveRegRsltCtx(enRegRsltType, pstLmmTauIndMsg);

    /* 从联合注册结果消息中取得拒绝原因值 */
    NAS_MMC_ConverLmmCombinedTauRsltToMMLCause(pstLmmTauIndMsg,
                                          &enPsRegRsltCause, &enCsRegRsltCause);

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
    NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_FALSE, enPsRegRsltCause);
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_COMBINE_EPS_REG_TAU_FAIL);

    ulTblSize = sizeof(gastMmcProcCombinedTauEpsRegFailCause)/sizeof(gastMmcProcCombinedTauEpsRegFailCause[0]);

    /* 在联合Eps注册原因表gastMmcProcCombinedTauEpsRegFailCause中，查找对应的处理函数 */
    for ( i = 0 ; i < ulTblSize; i++ )
    {
        if (enPsRegRsltCause == gastMmcProcCombinedTauEpsRegFailCause[i].enRegCause)
        {
            pRegFailProcFunc = gastMmcProcCombinedTauEpsRegFailCause[i].pCombinedEpsRegFailProcFunc;
            break;
        }

    }

    /*找到后，调用对应的处理,并返回对应的后续处理时*/
    if (VOS_NULL_PTR != pRegFailProcFunc)
    {
        pRegFailProcFunc(penPsRegAdditionalAction, penCsRegAdditionalAction);

    }
    /*没有找到时，按照PS Other Cause处理*/
    else
    {
        NAS_MMC_ProcCombinedEpsRegFailCauseAbnormalCause(penPsRegAdditionalAction,
                                                         penCsRegAdditionalAction);
    }

    if (VOS_TRUE == NAS_MML_IsNetworkRegFailCause(enPsRegRsltCause))
    {
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_EPS, enPsRegRsltCause);
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS, enPsRegRsltCause);

        /* 更新DPLMN NPLMN列表 */
        if (VOS_TRUE == NAS_MMC_IsRoam())
        {
            NAS_MMC_UpdateDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_PS_CS, NAS_MMC_MAX_CFG_NPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList);
            NAS_MMC_DeleteDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_PS_CS, &pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList);
            NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(pstDPlmnNPlmnCfgInfo);

            NAS_MMC_LogDplmnNplmnList();
        }
    }

    return;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCombinedEpsRegCsFail
 功能描述  : 联合Eps注册only eps成功的处理
 输入参数  : VOS_UINT16                             usCause,
             VOS_UINT32                             ulAttemptCnt
 输出参数  : penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月25日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年1月8日
    作    者   : z00161729
    修改内容   : V7R1 phase IV修改
  3.日    期   : 2014年11月3日
    作    者   : z00161729
    修改内容   : 开机漫游搜网项目修改
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegOnlyEpsSucc(
    VOS_UINT16                                              usCause,
    VOS_UINT32                                              ulAttemptCnt,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulTblSize;
    NAS_MMC_PROC_REG_FAIL_FUNC_PTR                          pRegFailProcFunc = VOS_NULL_PTR;

    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    pstDPlmnNPlmnCfgInfo  = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_COMBINE_EPS_REG_ONLY_EPS_SUCC);

    ulTblSize = sizeof(gastMmcProcCombinedEpsRegOnlyEpsSuccCause)/sizeof(gastMmcProcCombinedEpsRegOnlyEpsSuccCause[0]);

    /* 在联合Eps注册原因表gastMmcProcCombinedEpsRegOnlyEpsSuccCause中，查找对应的处理函数 */
    for ( i = 0 ; i < ulTblSize; i++ )
    {
        if (usCause == gastMmcProcCombinedEpsRegOnlyEpsSuccCause[i].enRegCause)
        {
            pRegFailProcFunc = gastMmcProcCombinedEpsRegOnlyEpsSuccCause[i].pRegFailProcFunc;
            break;
        }

    }

    /*找到后，调用对应的处理,并返回对应的后续处理时*/
    if (VOS_NULL_PTR != pRegFailProcFunc)
    {
        *penCsRegAdditionalAction = pRegFailProcFunc();

    }
    /*没有找到时，按照PS Other Cause处理*/
    else
    {
        NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCauseAbnormalCause(usCause, ulAttemptCnt,
                                                             penCsRegAdditionalAction);
    }

    NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_EPS, NAS_MML_REG_FAIL_CAUSE_NULL);
    if (VOS_TRUE == NAS_MML_IsNetworkRegFailCause(usCause))
    {
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS, usCause);

        /* 更新DPLMN NPLMN列表 */
        if (VOS_TRUE == NAS_MMC_IsRoam())
        {
            NAS_MMC_UpdateDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, NAS_MMC_MAX_CFG_NPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList);
            NAS_MMC_DeleteDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, &pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList);
            NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(pstDPlmnNPlmnCfgInfo);

            NAS_MMC_LogDplmnNplmnList();
        }
    }

    return;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsRegFailCauseAbnormalCause
 功能描述  : EPS OtherCause的处理
 输入参数  : VOS_UINT16                          usCause,
              VOS_UINT32                          ulAttemptCnt
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月5日
    作    者   : l00130025
    修改内容   : 新生成函数
                  1)  attemptCount < MaxCount时，返回NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT
                  2)  attemptCount >= MaxCount时，返回NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION

  2.日    期   : 2012年1月3日
    作    者   : w00167002
    修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网.
               1): 非UE主动发起注册的原因值(如注册被拒cause为260),此时若是在
                   OnPlmn/PlmnList下,不需要进行可选的搜网则返回为
                   NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON

               2):增加如下场景的考虑:手动模式下，当前Plmn不是用户指定的PLMN,
               且当前PLMN不在EPlmn列表里，则需要返回可选的搜网策略。
  3.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  4.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  5.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsRegFailCauseAbnormalCause(
    VOS_UINT16                          usCause,
    VOS_UINT32                          ulAttemptCnt
)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enPrioAdditionalAction;

    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        /* AttemptCounter未达到最大次数的处理 */
        NAS_MMC_ProcEpsRegFailAttemptCouterLessThanMaxTimes(&enAction);
    }
    else
    {
        /* 删除EPLMN */
        NAS_MMC_DeleteEPlmnList();

        /* 更新服务状态 */

        /* 通知TAF当前的服务状态 */

        enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

        enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enAction,enPrioAdditionalAction);
        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }

        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }
    }

    return enAction;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsRegFailAttemptCouterLessThanMaxTimes
 功能描述  : EPS注册失败Attempt未达到最大次数的处理的处理
 输入参数  : 无
 输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsRegFailAttemptCouterLessThanMaxTimes(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction
)
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnInfo        = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn     = VOS_NULL_PTR;
    VOS_UINT32                          ulInEplmnListFlag;
    VOS_UINT32                          ulUserSpecPlmnFlag;

    /* 判断当前网络是否是用户指定的网络 */
    pstUserSpecPlmn    = NAS_MMC_GetUserSpecPlmnId();
    ulUserSpecPlmnFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(NAS_MML_GetCurrCampPlmnId(),
                                                &(pstUserSpecPlmn->stPlmnId));

    /* 判断当前网络是否在EPlmn列表里 */
    pstEplmnInfo       = NAS_MML_GetEquPlmnList();

    ulInEplmnListFlag  = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(NAS_MML_GetCurrCampPlmnId(),
                                              pstEplmnInfo->ucEquPlmnNum,
                                              pstEplmnInfo->astEquPlmnAddr);

    /* 手动模式下，当前Plmn不是用户指定的PLMN,且当前PLMN不在EPlmn列表里，
       则认为当前plmn是NOT ALLOWED，需要进行搜网 */
    if ( (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
      && (VOS_FALSE                          == ulUserSpecPlmnFlag)
      && (VOS_FALSE                          == ulInEplmnListFlag) )
    {
        *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
        return ;
    }
    /* 与GU保持一致,通过判断服务状态来决定是否更新注册状态和服务状态，*/
    if (NAS_MMC_NORMAL_SERVICE != NAS_MMC_GetCurrPsService())
    {
        /*MMC接收到LMM模块注册结果(EPS ONLY),未达到最大次数的处理 更新PS域注册状态为0，并上报服务状态2*/
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }

    /* 否则mmc继续等待注册结果 */
    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsAttachRegFail
 功能描述  : Eps注册被拒的处理
 输入参数  : VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : l00130025
    修改内容   : 新生成函数

  2.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : DTS2011121307570: MMC没有维护LMM的EPLMN信息，现在统一调整
                  ATTACH/TAU/DETACH/SERVICE中被拒时EPLMN的维护。
                  将函数名由NAS_MMC_ProcEpsRegFail更改为NAS_MMC_ProcEpsAttachRegFail
                  调用ATTACH的注册原因值表进行处理。
  3.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV修改合并原NAS_MMC_HPLMN_REG_REJ_STRU和NAS_MMC_PLMN_REG_INFO_STRU
  4.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : DTS2011122704039:将注册结果类型以及注册消息传递给处理注册结果
                  函数，扩展注册结果函数的处理能力。
  5.日    期   : 2013年8月15日
    作    者   : l00208543
    修改内容   : 将网络拒绝原因值进行上报
  6.日    期   : 2014年01月10日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseIII项目
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFail(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType,
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulTblSize;
    NAS_MMC_PROC_REG_FAIL_FUNC_PTR      pRegFailProcFunc = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAction;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enRegRsltCause;
    VOS_UINT32                                              ulAttemptCnt;

    /* 保存注册结果消息 */
    NAS_MMC_SaveRegRsltCtx(enRegRsltType, pstLmmAttachIndMsg);

    /* 将LMM的注册失败原因值转换为MM格式的原因值 */
    NAS_MMC_ConverLmmAttachRsltToMMLCause(pstLmmAttachIndMsg, &enRegRsltCause);

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
    NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_FALSE, enRegRsltCause);
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_EPS_REG_ATTACH_FAIL);

    ulTblSize = sizeof(gastMmcProcEpsAttachRegFailCause)/sizeof(gastMmcProcEpsAttachRegFailCause[0]);

    /*在Eps注册原因表gastMmcProcEpsRegFailCause中，查找对应的处理函数*/
    for ( i = 0 ; i < ulTblSize; i++ )
    {
        if (enRegRsltCause == gastMmcProcEpsAttachRegFailCause[i].enRegCause)
        {
            pRegFailProcFunc = gastMmcProcEpsAttachRegFailCause[i].pRegFailProcFunc;

            break;
        }

    }

    /*找到后，调用对应的处理,并返回对应的后续处理时*/
    if (VOS_NULL_PTR != pRegFailProcFunc)
    {
        enAction = pRegFailProcFunc();

    }
    /*没有找到时，按照PS Other Cause处理*/
    else
    {
        /* 取得Attempt Counter的值 */
        ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);
        enAction = NAS_MMC_ProcEpsRegFailCauseAbnormalCause(enRegRsltCause, ulAttemptCnt);
    }


    if (VOS_TRUE == NAS_MML_IsNetworkRegFailCause(enRegRsltCause))
    {
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_EPS, enRegRsltCause);
    }
    return enAction;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsTauRegFail
 功能描述  : Eps注册被拒的处理
 输入参数  : VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : 新增函数
                  DTS2011121307570: MMC没有维护LMM的EPLMN信息，现在统一调整
                  ATTACH/TAU/DETACH/SERVICE中被拒时EPLMN的维护。
                  将函数名由NAS_MMC_ProcEpsRegFail更改为NAS_MMC_ProcEpsTauRegFail
                  调用ATTACH的注册原因值表进行处理。
  2.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV修改合并原NAS_MMC_HPLMN_REG_REJ_STRU和NAS_MMC_PLMN_REG_INFO_STRU
  3.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : DTS2011122704039:将注册结果类型以及注册消息传递给处理注册结果
                  函数，扩展注册结果函数的处理能力。
  4.日    期   : 2013年8月15日
    作    者   : l00208543
    修改内容   : 将网络拒绝原因值进行上报
  5.日    期   : 2014年01月10日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseIII项目
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFail(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType,
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulTblSize;
    NAS_MMC_PROC_REG_FAIL_FUNC_PTR                          pRegFailProcFunc = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enRegRsltCause;
    VOS_UINT32                                              ulAttemptCnt;

    /* 保存注册结果消息 */
    NAS_MMC_SaveRegRsltCtx(enRegRsltType, pstLmmTauIndMsg);
    NAS_MMC_ConverTauResultToMMLCause(pstLmmTauIndMsg, &enRegRsltCause);

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
    NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_FALSE, enRegRsltCause);
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_EPS_REG_TAU_FAIL);

    ulTblSize = sizeof(gastMmcProcEpsTauRegFailCause)/sizeof(gastMmcProcEpsTauRegFailCause[0]);

    /*在Eps注册原因表gastMmcProcEpsRegFailCause中，查找对应的处理函数*/
    for ( i = 0 ; i < ulTblSize; i++ )
    {
        if (enRegRsltCause == gastMmcProcEpsTauRegFailCause[i].enRegCause)
        {
            pRegFailProcFunc = gastMmcProcEpsTauRegFailCause[i].pRegFailProcFunc;

            break;
        }

    }

    /*找到后，调用对应的处理,并返回对应的后续处理时*/
    if (VOS_NULL_PTR != pRegFailProcFunc)
    {
        enAction = pRegFailProcFunc();

    }
    /*没有找到时，按照EPS Abnormal Cause处理*/
    else
    {
        /* 取得Attempt Counter的值 */
        ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);
        enAction     = NAS_MMC_ProcEpsRegFailCauseAbnormalCause(enRegRsltCause, ulAttemptCnt);
    }

    if (VOS_TRUE == NAS_MML_IsNetworkRegFailCause(enRegRsltCause))
    {
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_EPS, enRegRsltCause);
    }

    return enAction;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEpsDetachCause
 功能描述  : Eps detach被拒的处理
 输入参数  : enRegRsltType:注册结果类型
              pstDetachMsg: detach消息
 输出参数  : penCsAddition
             penPsAddition
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月4日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年11月19日
    作    者   : w00176964
    修改内容   : 联合注册ST修改

  3.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : DTS2011122704039:将注册结果类型以及注册消息传递给处理注册结果
                  函数，扩展注册结果函数的处理能力。
*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsDetachCause(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType,
    LMM_MMC_DETACH_IND_STRU                                *pstDetachMsg,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulTblSize;
    NAS_MMC_PROC_EPS_DETACH_CAUSE_FUNC_PTR                  pRegFailProcFunc = VOS_NULL_PTR;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enRegRsltCause;

    /* 保存注册结果消息 */
    NAS_MMC_SaveRegRsltCtx(enRegRsltType, pstDetachMsg);

    /* 不带CAUSE值与OTHER CAUSE处理一致 */
    if ( VOS_FALSE == pstDetachMsg->bitOpCnCause )
    {
        enRegRsltCause = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
    }
    else
    {
        NAS_MMC_ConvertLmmCauseToMmCause((VOS_UINT8)pstDetachMsg->ucCnCause,
                                                &enRegRsltCause);
    }

    ulTblSize           = sizeof(gastMmcProcEpsDetachCause)/sizeof(gastMmcProcEpsDetachCause[0]);

    /*在Eps注册原因表gastMmcProcEpsDetachCause中，查找对应的处理函数*/
    for ( i = 0 ; i < ulTblSize; i++ )
    {
        if (enRegRsltCause == gastMmcProcEpsDetachCause[i].enRegCause)
        {
            pRegFailProcFunc = gastMmcProcEpsDetachCause[i].pEpsDetachCauseProcFunc;

            break;
        }
    }

    /*找到后，调用对应的处理,并返回对应的后续处理时*/
    if (VOS_NULL_PTR != pRegFailProcFunc)
    {
        pRegFailProcFunc(penCsAddition, penPsAddition);
    }
    else
    {
        NAS_MMC_ProcEpsDetachCauseAbnormalCause(penCsAddition, penPsAddition);
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmDetachInd
 功能描述  : 处理LMM DETACH消息
 输入参数  : pstDetachMsg
 输出参数  : penCsAddition CS域的后续动作
             penPsAddition PS域的后续动作
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月29日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年10月26日
    作    者   : w00176964
    修改内容   : V7R1 Phase III调整:联合注册修改

  3.日    期   : 2011年11月19日
    作    者   : w00176964
    修改内容   : V7R1 Phase III调整:联合注册ST修改

  4.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : DTS2011121307570:MMC未处理LMM的ATTACH/TAU/SERVICE/DETACH的EPLMN
                  信息;通知MM/GMM的消息未更新V7R1_PHASEIV的调用函数
  5.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : DTS2011122704039:将去注册结果类型以及注册消息传递给处理去注册结果
                  函数，扩展去注册结果函数的处理能力。
  6.日    期   : 2012年05月28日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 C50 CS/PS mode 1
  7.日    期   : 2012年8月21日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改DTS2012090401249
  8.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  9.日    期   : 2013年12月14日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseIII项目

 10.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                     mmc收到网络去注册,服务状态和注册状态的处理
*****************************************************************************/
VOS_VOID NAS_MMC_ProcLmmDetachInd(
    LMM_MMC_DETACH_IND_STRU                                *pstDetachMsg,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    MMC_LMM_MT_DETACH_TYPE_ENUM_UINT32                      enCnReqType;

    enCnReqType         = MMC_LMM_MT_DETACH_TYPE_BUTT;

   *penCsAddition       = NAS_MMC_ADDITIONAL_ACTION_BUTT;
   *penPsAddition       = NAS_MMC_ADDITIONAL_ACTION_BUTT;

   /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-17, begin */
   /* MMC_LMM_DETACH_LOCAL在预处理已完成，这里删除 */
   /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-17, end */


    /* 网侧响应的detach结果OP项关闭 */
    if ( VOS_TRUE == pstDetachMsg->bitOpCnReqType)
    {
        enCnReqType = pstDetachMsg->ulCnReqType;
    }

    /* 网侧触发的DETACH流程，通过DETACH类型中MMC_LMM_DETACH_MT通知MMC，
    且携带相应的网侧DETACH请求类型和原因值 */
    switch (enCnReqType)
    {
        case MMC_LMM_MT_DET_REATTACH_NOT_REQUIRED:

            NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_LTE_NW_DETACH);

            NAS_MMC_ProcEpsDetachCause(LMM_MMC_DETACH_IND, pstDetachMsg,
                                       penCsAddition, penPsAddition);

            /* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-14, begin */
            /* 清除紧急PDN连接标志,暂不用通知EPLMN因为各状态收到detach结果的时候需要通知EPLMN */
            NAS_MML_SetEmcPdpStatusFlg(VOS_FALSE);

            /* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-14, end */


            /* 向GMM和MM转发注册结果消息 */
            NAS_MMC_SndMmLmmMtDetachInd(pstDetachMsg);

            NAS_MMC_SndGmmLmmMtDetachInd(pstDetachMsg);

            break;

        case MMC_LMM_MT_DET_REATTACH_REQUIRED:

            *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;

            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);

            NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_LTE_NW_DETACH);
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

            /* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-14, begin */
            /* 清除紧急PDN连接标志,暂不用通知EPLMN因为各状态收到detach结果的时候需要通知EPLMN */
            NAS_MML_SetEmcPdpStatusFlg(VOS_FALSE);
            /* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-14, end */

            /* 向GMM和MM转发注册结果消息 */
            NAS_MMC_SndMmLmmMtDetachInd(pstDetachMsg);

            NAS_MMC_SndGmmLmmMtDetachInd(pstDetachMsg);

            break;
        case MMC_LMM_MT_DET_IMSI:

            NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_LTE_NW_DETACH);

            /* 向MM转发注册结果消息 */
            NAS_MMC_SndMmLmmMtDetachInd(pstDetachMsg);

            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

            /*mmc收到CS域的网络去注册,上报注册状态和服务状态*/
            NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);

            break;

        default:

            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmDetachInd:Unexpected detach cn req type!");
            break;
    }


    return;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmServiceRsltInd
 功能描述  : 处理LMM的service result IND消息
 输入参数  : pstSerRsltMsg LMM的service result 消息
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月29日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年10月26日
    作    者   : w00176964
    修改内容   : V7R1 Phase III调整:联合注册修改
  3.日    期   : 2011年11月30日
    作    者   : w00176964
    修改内容   : V7R1 Phase IV调整:disable/enable 调整
  4.日    期   : 2012年3月5日
    作    者   : w00167002
    修改内容   : V7R1C50 CSFB调整:增加LMM 上报的service结果的保存
  5.日    期   : 2013年01月11日
    作    者   : l00167671
    修改内容   : DTS2013011107287,L下紧急呼，SR被拒18，紧急呼失败，一直不能发起
  6.日    期   : 2015年1月6日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
  7.日    期   : 2015年4月22日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcLmmServiceRsltInd(
    LMM_MMC_SERVICE_RESULT_IND_STRU    *pstSerRsltMsg
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulTblSize;
    NAS_MMC_PROC_REG_FAIL_FUNC_PTR      pRegFailProcFunc = VOS_NULL_PTR;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAction;

    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    /* LMM的SERVICE流程结果通过此原语通知MMC。结构中的bit域来表示该项是否有效。
     SERVICE流程成功，不需通知MMC；
     SERVICE流程被网侧拒绝，通过SERVICE结果中MMC_LMM_SERVICE_RSLT_FAILURE通知MMC，并携带相应的原因值。
     如果UE触发EXTENDED SERVICE流程，需携带SERVICE类型。
     注：SERIVE类型暂时不使用 */

    /* 保存LMM上报的SERVICE结果消息 */
    NAS_MMC_SaveRegRsltCtx(LMM_MMC_SERVICE_RESULT_IND, pstSerRsltMsg);

    ulTblSize = sizeof(gastMmcProcEpsServiceRequestFailCause)/sizeof(gastMmcProcEpsServiceRequestFailCause[0]);
    NAS_MMC_ConverLmmServiceRsltToMMLCause(pstSerRsltMsg,&enRegRsltCause);

    /* 通知MM/GMM */
    NAS_MMC_SndMmLmmSerResultnd(pstSerRsltMsg);
    NAS_MMC_SndGmmLmmSerResultnd(pstSerRsltMsg);

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_EPS_SERVICE_REQ_FAIL);

    /*在Eps注册原因表gastMmcProcEpsRegFailCause中，查找对应的处理函数*/
    for ( i = 0 ; i < ulTblSize; i++ )
    {
        if (enRegRsltCause == gastMmcProcEpsServiceRequestFailCause[i].enRegCause)
        {
            pRegFailProcFunc = gastMmcProcEpsServiceRequestFailCause[i].pRegFailProcFunc;

            break;
        }

    }

    /*找到后，调用对应的处理,并返回对应的后续处理时*/
    if (VOS_NULL_PTR != pRegFailProcFunc)
    {
        enAction = pRegFailProcFunc();
    }
    else
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

        enRegRsltCause = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
    }

    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_ServiceRsltFail(enRegRsltCause, pstSerRsltMsg->ucIsReachMaxTimes))
    {
        /* 需要Disable L全局变量 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetCsPsMode1EnableLteTimerLen());

        PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
        stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

        if (VOS_TRUE == NAS_MML_IsNeedAddDamPlmnInDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
        {
            NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                          NAS_MML_GetDamDisabledPlmnWithForbiddenPeriodTimeSlice(&stPlmnWithRat),
                                                          MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
        }

        enAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    if( VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist() )
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION ;
    }

    return enAction;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltEpsOnlySucc
 功能描述  : Lmm combined tau EPS成功注册,CS注册失败的处理函数
 输入参数  : pstLmmTauIndMsg  - LMM_MMC_TAU_RESULT_IND_STRU消息的首地址
             enCsRegRsltCause - cs域被拒原因值
 输出参数  : penCsAddition    - CS域的后续动作
             penPsAddition    - PS域的后续动作
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月8日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年3月5日
    作    者   : w00167002
    修改内容   : V7R1C50 CSFB调整:增加注册结果的保存
  3.日    期   : 2012年12月6日
    作    者   : s00217060
    修改内容   : DTS2012120410842:不仅是指定搜网注册成功，其他情况注册成功时，也需要删除ForbPlmn,ForbLa,ForbGprs等信息
  4.日    期   : 2013年8月15日
    作    者   : l00208543
    修改内容   : 收到网络的拒绝原因值后进行主动上报
  5.日    期   : 2014年01月10日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseIII项目
  6.日    期   : 2015年4月18日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltEpsOnlySucc(
    LMM_MMC_TAU_RESULT_IND_STRU                            *pstLmmTauIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    VOS_UINT32                          ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU               *pstLmmEquPlmnList = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU           stLEplmnInfo;

    NAS_MMC_SaveRegRsltCtx(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg);

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
    /* AT^REJINFO主动上报，将REJINFO上报给MSCC */
    NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
    NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS, VOS_FALSE, enCsRegRsltCause);
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */

    /* eps域注册成功，cs域注册失败 */
    *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

    /* 注册成功并且ATTACH_IND消息中不带LAI时，需要删除ForbPlmn,ForbGprs等信息 */
    NAS_MMC_DelForbInfo_LmmAttRsltSucc(VOS_NULL_PTR, VOS_FALSE);

    /* 注册成功时，清除GEO PLMN，下次再搜网时，可以直接搜RPLMN */
    NAS_MMC_InitGeoPlmn();

    /* 更新EPLMN,联合注册成功或EPS only成功网侧均可能带EPLMN */
    if ( VOS_TRUE == pstLmmTauIndMsg->bitOpEplmn)
    {
        ulEquPlmnNum        = pstLmmTauIndMsg->stEplmnList.ulPlmnNum;
        pstLmmEquPlmnList   = pstLmmTauIndMsg->stEplmnList.astEplmnList;

        /* 将LMM的PLMN ID格式转换为GU的格式 */
        NAS_MMC_ConvertLmmPlmnToGUNasPlmn(ulEquPlmnNum, pstLmmEquPlmnList, (stLEplmnInfo.astEquPlmnAddr));
        NAS_MML_SaveEquPlmnList(ulEquPlmnNum, stLEplmnInfo.astEquPlmnAddr);

        NAS_MMC_WriteEplmnNvim();
    }

    NAS_MMC_UpdateGURegRlstRPlmnIdInNV();

    NAS_MMC_ProcCombinedEpsRegOnlyEpsSucc(enCsRegRsltCause, pstLmmTauIndMsg->ulAttemptCount,
                                          penCsAddition);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_NORMAL_CAMP_ON);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltCsEpsSucc
 功能描述  : Lmm combined tau EPS和cs和网侧交互成功注册结果的处理函数
 输入参数  : pstLmmTauIndMsg - LMM_MMC_TAU_RESULT_IND_STRU消息的首地址
 输出参数  : penCsAddition CS域的后续动作
             penPsAddition PS域的后续动作
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月8日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年3月5日
    作    者   : w00167002
    修改内容   : V7R1C50 CSFB调整:增加注册结果的保存
  3.日    期   : 2012年6月2日
    作    者   : s00217060
    修改内容   : For CS/PS mode 1,联合TAU成功时，需要Disable L
  4.日    期   : 2012年6月4日
    作    者   : l00171473
    修改内容   : DTS2012053003921, 用户手动指定网络的注册状态标志清理
  5.日    期   : 2012年7月27日
    作    者   : s00217060
    修改内容   : For CS/PS mode 1,带Disable LTE原因值
  6.日    期   : 2012年12月6日
    作    者   : s00217060
    修改内容   : DTS2012120410842:不仅是指定搜网注册成功，其他情况注册成功时，也需要删除ForbPlmn,ForbLa,ForbGprs等信息
  7.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  8.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  9.日    期   : 2013年12月10日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseIII 项目:修改Disable L模的逻辑
 10.日    期   : 2014年7月14日
    作    者   : b00269685
    修改内容   : 漫游搜网优化项目修改
 11.日    期   : 2015年3月23日
    作    者   : b00269685
    修改内容   : 先更新EPLMN再更新注册状态
 12.日    期   : 2015年4月18日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
 13.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改，
                 对于EMM的COMBINED TAU成功，增加PS域注册状态的上报
 14.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : DTS2015082002854: 漫游标记不准
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltCsEpsSucc(
    LMM_MMC_TAU_RESULT_IND_STRU                            *pstLmmTauIndMsg,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    VOS_UINT32                          ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU               *pstLmmEquPlmnList = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU           stLEplmnInfo;

    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    pstDPlmnNPlmnCfgInfo  = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    NAS_MMC_SaveRegRsltCtx(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg);

     *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
     *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

     /* 根据注册结果更新注册信息表 */
     NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_EPS, NAS_MML_REG_FAIL_CAUSE_NULL);
     NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS, NAS_MML_REG_FAIL_CAUSE_NULL);

    /* 更新EPLMN,联合注册成功或EPS only成功网侧均可能带EPLMN */
    if ( VOS_TRUE == pstLmmTauIndMsg->bitOpEplmn)
    {
        ulEquPlmnNum        = pstLmmTauIndMsg->stEplmnList.ulPlmnNum;
        pstLmmEquPlmnList   = pstLmmTauIndMsg->stEplmnList.astEplmnList;

        /* 将LMM的PLMN ID格式转换为GU的格式 */
        NAS_MMC_ConvertLmmPlmnToGUNasPlmn(ulEquPlmnNum, pstLmmEquPlmnList, (stLEplmnInfo.astEquPlmnAddr));
        NAS_MML_SaveEquPlmnList(ulEquPlmnNum, stLEplmnInfo.astEquPlmnAddr);

        NAS_MMC_WriteEplmnNvim();
    }

    /* 更新DPLMN NPLMN列表 */
    if (VOS_TRUE == NAS_MMC_IsRoam())
    {
        NAS_MMC_UpdateDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_PS_CS, NAS_MMC_MAX_CFG_DPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList);
        NAS_MMC_DeleteDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_PS_CS, &pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList);
        NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(pstDPlmnNPlmnCfgInfo);

        NAS_MMC_LogDplmnNplmnList();
    }

    /* 注册成功时，清除GEO PLMN，下次再搜网时，可以直接搜RPLMN */
    NAS_MMC_InitGeoPlmn();


     /* TAU成功并且带LAI时，需要删除ForbPlmn,ForbLa,ForbGprs等信息 */
     if (VOS_TRUE == pstLmmTauIndMsg->bitOpLai)
     {
         NAS_MMC_DelForbInfo_LmmAttRsltSucc(&(pstLmmTauIndMsg->stLai), VOS_FALSE);
     }
     else
     {
         /* TAU成功并且不带LAI时，需要删除ForbPlmn,ForbGprs等信息 */
         NAS_MMC_DelForbInfo_LmmAttRsltSucc(VOS_NULL_PTR, VOS_FALSE);
     }


    NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NORMAL_SERVICE);

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-12, begin */
    *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

    NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-12, end */


    NAS_MMC_UpdateGURegRlstRPlmnIdInNV();

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmCombinedAttachInd_AttRsltCsEpsSucc
 功能描述  : Lmm combined attach EPS和cs和网侧交互成功注册结果的处理函数
 输入参数  : pstLmmAttachIndMsg - ID_LMM_MMC_ATTACH_IND消息的首地址
 输出参数  : penCsAddition CS域的后续动作
             penPsAddition PS域的后续动作
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月8日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年3月5日
    作    者   : w00167002
    修改内容   : V7R1C50 CSFB调整:增加注册结果的保存
  3.日    期   : 2012年6月1日
    作    者   : s00217060
    修改内容   : 调整:CS/PS mode 1联合Attach成功时，需要Disable L
                  CsAddition为NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
  4.日    期   : 2012年6月4日
    作    者   : l00171473
    修改内容   : DTS2012053003921, 用户手动指定网络的注册状态标志清理
  5.日    期   : 2012年7月27日
    作    者   : s00217060
    修改内容   : For CS/PS mode 1,带Disable LTE原因值
  6.日    期   : 2012年12月6日
    作    者   : s00217060
    修改内容   : DTS2012120410842:不仅是指定搜网注册成功，其他情况注册成功时，也需要删除ForbPlmn,ForbLa,ForbGprs等信息
  7.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  8.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  9.日    期   : 2013年12月10日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseIII 项目:修改Disable L模的逻辑
  10.日    期   : 2014年11月3日
     作    者   : z00161729
     修改内容   : 开机漫游搜网项目修改
  11.日    期   : 2015年3月23日
     作    者   : b00269685
     修改内容   : 先写EPLMN再更新注册状态
  12.日    期   : 2015年4月18日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
 13.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                 对于EMM的COMBINED ATTACH成功，增加PS域注册状态的上报
 14.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : DTS2015082002854: 漫游标记不准
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmCombinedAttachInd_AttRsltCsEpsSucc(
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    VOS_UINT32                          ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU               *pstLmmEquPlmnList = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU           stLEplmnInfo;

    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    pstDPlmnNPlmnCfgInfo  = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    NAS_MMC_SaveRegRsltCtx(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg);

    *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;


    /* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2014-1-10, begin */

    /* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2014-1-10, end */

    if (VOS_TRUE == pstLmmAttachIndMsg->bitOpLai)
    {
        /* 注册成功并且ATTACH_IND消息中带LAI时，需要删除ForbPlmn,ForbLa,ForbGprs等信息 */
        NAS_MMC_DelForbInfo_LmmAttRsltSucc(&(pstLmmAttachIndMsg->stLai), NAS_MMC_IsEpsEmergencyAttachType(pstLmmAttachIndMsg->ulReqType));
    }
    else
    {
        /* 注册成功并且ATTACH_IND消息中不带LAI时，需要删除ForbPlmn,ForbGprs等信息 */
        NAS_MMC_DelForbInfo_LmmAttRsltSucc(VOS_NULL_PTR, NAS_MMC_IsEpsEmergencyAttachType(pstLmmAttachIndMsg->ulReqType));
    }

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-12, begin */
    *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-12, end */


    /* 更新EPLMN，联合注册成功或EPS only成功网侧均可能带EPLMN */
    if (VOS_TRUE == pstLmmAttachIndMsg->bitOpEplmn)
    {
        ulEquPlmnNum        = pstLmmAttachIndMsg->stEplmnList.ulPlmnNum;
        pstLmmEquPlmnList   = pstLmmAttachIndMsg->stEplmnList.astEplmnList;

        /* 将LMM的PLMN ID格式转换为GU的格式 */
        NAS_MMC_ConvertLmmPlmnToGUNasPlmn(ulEquPlmnNum, pstLmmEquPlmnList, (stLEplmnInfo.astEquPlmnAddr));
        NAS_MML_SaveEquPlmnList(ulEquPlmnNum, stLEplmnInfo.astEquPlmnAddr);

        NAS_MMC_WriteEplmnNvim();
    }

    NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NORMAL_SERVICE);


    /* 根据注册结果更新注册信息表 */
    NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_EPS, NAS_MML_REG_FAIL_CAUSE_NULL);
    NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS, NAS_MML_REG_FAIL_CAUSE_NULL);

    /* 更新DPLMN NPLMN列表 */
    if (VOS_TRUE == NAS_MMC_IsRoam())
    {
        NAS_MMC_UpdateDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_PS_CS, NAS_MMC_MAX_CFG_DPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList);
        NAS_MMC_DeleteDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_PS_CS, &pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList);
        NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(pstDPlmnNPlmnCfgInfo);

        NAS_MMC_LogDplmnNplmnList();
    }

    /* 注册成功时，清除GEO PLMN，下次再搜网时，可以直接搜RPLMN */
    NAS_MMC_InitGeoPlmn();

    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
    NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */


    NAS_MMC_UpdateGURegRlstRPlmnIdInNV();
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmCombinedAttachInd_AttRsltEpsOnlySucc
 功能描述  : Lmm combined attach EPS成功注册,CS注册失败的处理函数
 输入参数  : pstLmmAttachIndMsg - ID_LMM_MMC_ATTACH_IND消息的首地址
             enCsRegRsltCause -  cs域被拒原因值
 输出参数  : penCsAddition    - CS域的后续动作
             penPsAddition    - PS域的后续动作
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月8日
    作    者   : z00161729
    修改内容   : V7R1 phase IV新生成函数
  2.日    期   : 2012年3月5日
    作    者   : w00167002
    修改内容   : V7R1C50 CSFB调整:增加注册结果的保存
  3.日    期   : 2012年12月6日
    作    者   : s00217060
    修改内容   : DTS2012120410842:不仅是指定搜网注册成功，其他情况注册成功时，也需要删除ForbPlmn,ForbLa,ForbGprs等信息
  4.日    期   : 2013年8月15日
    作    者   : l00208543
    修改内容   : 收到网络的拒绝原因值后进行主动上报
  5.日    期   : 2014年01月10日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseIII项目
  6.日    期   : 2015年4月18日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmCombinedAttachInd_AttRsltEpsOnlySucc(
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    VOS_UINT32                          ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU               *pstLmmEquPlmnList = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU           stLEplmnInfo;

    NAS_MMC_SaveRegRsltCtx(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg);

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
    /* AT^REJINFO主动上报，将REJINFO上报给MSCC */
    NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
    NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS, VOS_FALSE, enCsRegRsltCause);
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */

    /* EPS域注册成功，cs域注册失败 */
    *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

    /* 注册成功并且ATTACH_IND消息中不带LAI时，需要删除ForbPlmn,ForbGprs等信息 */
    NAS_MMC_DelForbInfo_LmmAttRsltSucc(VOS_NULL_PTR, NAS_MMC_IsEpsEmergencyAttachType(pstLmmAttachIndMsg->ulReqType));

    /* 注册成功时，清除GEO PLMN，下次再搜网时，可以直接搜RPLMN */
    NAS_MMC_InitGeoPlmn();

    /* 更新EPLMN，联合注册成功或EPS only成功网侧均可能带EPLMN */
    if ( VOS_TRUE == pstLmmAttachIndMsg->bitOpEplmn)
    {
        ulEquPlmnNum        = pstLmmAttachIndMsg->stEplmnList.ulPlmnNum;
        pstLmmEquPlmnList   = pstLmmAttachIndMsg->stEplmnList.astEplmnList;

        /* 将LMM的PLMN ID格式转换为GU的格式 */
        NAS_MMC_ConvertLmmPlmnToGUNasPlmn(ulEquPlmnNum, pstLmmEquPlmnList, (stLEplmnInfo.astEquPlmnAddr));
        NAS_MML_SaveEquPlmnList(ulEquPlmnNum, stLEplmnInfo.astEquPlmnAddr);

        NAS_MMC_WriteEplmnNvim();
    }

    NAS_MMC_UpdateGURegRlstRPlmnIdInNV();

    NAS_MMC_ProcCombinedEpsRegOnlyEpsSucc(enCsRegRsltCause, pstLmmAttachIndMsg->ulAttemptCount,
                                          penCsAddition);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_NORMAL_CAMP_ON);
    }

    return;
}




/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmCombinedAttachInd_AttRsltSucc
 功能描述  : Lmm combined attach EPS和CS成功注册的处理函数
 输入参数  : pstLmmAttachIndMsg - ID_LMM_MMC_ATTACH_IND消息的首地址
             enCsRegRsltCause -  cs域被拒原因值
 输出参数  : penCsAddition    - CS域的后续动作
             penPsAddition    - PS域的后续动作
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月8日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年6月4日
    作    者   : l00171473
    修改内容   : DTS2012053003921, 用户手动指定网络的注册状态标志清理
  3.日    期   : 2012年6月8日
    作    者   : l00130025
    修改内容   : DTS2012060702423:Anycell驻留后，注册成功时，没有通知通知APS/CDS消息，无法数传
  4.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  5.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  6.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
  7.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : DTS2015082002854: 漫游标记不准
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmCombinedAttachInd_AttRsltSucc(
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    if (VOS_TRUE == pstLmmAttachIndMsg->bitOpCnRslt)
    {
        if (MMC_LMM_ATT_CN_RSLT_COMBINED_EPS_IMSI == pstLmmAttachIndMsg->ulCnRslt)
        {
            NAS_MMC_ProcLmmCombinedAttachInd_AttRsltCsEpsSucc(pstLmmAttachIndMsg,
                          penCsAddition, penPsAddition);
        }
        else if (MMC_LMM_ATT_CN_RSLT_EPS_ONLY == pstLmmAttachIndMsg->ulCnRslt)
        {
            NAS_MMC_ProcLmmCombinedAttachInd_AttRsltEpsOnlySucc(pstLmmAttachIndMsg,enCsRegRsltCause,
                          penCsAddition, penPsAddition);

        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmCombinedAttachInd_AttRsltSucc:Unexpected cn result!");
        }
    }
    else
    {
        /* 假流程注册成功上报正常服务返回 */
        *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
        *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NORMAL_SERVICE);

        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_NORMAL_CAMP_ON);
    }

    NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());


    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltSucc
 功能描述  : Lmm TAU result结果为MMC_LMM_TAU_RSLT_SUCCESS的处理函数
 输入参数  : ID_LMM_MMC_TAU_RESULT_IND消息的首地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月07日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年6月4日
    作    者   : l00171473
    修改内容   : DTS2012053003921, 用户手动指定网络的注册状态标志清理
  3.日    期   : 2012年6月8日
    作    者   : l00130025
    修改内容   : DTS2012060702423:Anycell驻留后，注册成功时，没有通知通知APS/CDS消息，无法数传
  4.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  5.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  6.日    期   : 2013年3月30日
    作    者   : w00176964
    修改内容   : DTS2013030802929,周期性RAU需要通知LMM
  7.日    期   : 2014年01月10日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseIII项目
  8.日    期   : 2015年05月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
  9.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : DTS2015082002854: 漫游标记不准
*****************************************************************************/
VOS_VOID NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltSucc(
    LMM_MMC_TAU_RESULT_IND_STRU                            *pstLmmTauIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    if (VOS_TRUE == pstLmmTauIndMsg->bitOpCnRst)
    {
        /* CS+PS的周期性TAU时,不论是否携带CS CAUSE值,都认为联合注册成功 */
        if ((MMC_LMM_COMBINED_TA_LA_UPDATED == pstLmmTauIndMsg->ulCnRst)
         || (MMC_LMM_COMBINED_TA_LA_UPDATED_ISR_ACTIVATED == pstLmmTauIndMsg->ulCnRst)
         || (MMC_LMM_CS_PS_PERIODIC_UPDATING == pstLmmTauIndMsg->ulReqType))
        {
            /* 和网侧交互EPS和CS均注册成功 */
            NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltCsEpsSucc(pstLmmTauIndMsg,
                          penCsAddition, penPsAddition);
        }
        else if ((MMC_LMM_TA_UPDATED == pstLmmTauIndMsg->ulCnRst)
              || (MMC_LMM_TA_UPDATED_ISR_ACTIVATED == pstLmmTauIndMsg->ulCnRst))
        {
            /* 与网侧交互EPS成功CS失败，且原因值为协议24301 5.5.3.3.4.3章节所列 */
            NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltEpsOnlySucc(pstLmmTauIndMsg,enCsRegRsltCause,
                          penCsAddition, penPsAddition);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltSucc:Unexpected cn result!");
        }
    }
    else
    {
        /* 假流程注册成功上报正常服务返回 */
        *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
        *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NORMAL_SERVICE);

         /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
         NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
         /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_NORMAL_CAMP_ON);
    }

    NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());


    return;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmCombinedTauResult
 功能描述  : Lmm TAU result的处理函数
 输入参数  : pstLmmTauIndMsg          -  ID_LMM_MMC_TAU_RESULT_IND消息内容
             enCsRegRsltCause - cs域被拒原因值
 输出参数  : penPsRegAdditionalAction - 收到注册tau结果后，协议要求的ps域的additional动作类型
             penCsRegAdditionalAction - 收到注册tau结果后，协议要求的cs域的additional动作类型
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月07日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年5月7日
    作    者   : w00166186
    修改内容   : DTS20120050302236:手动搜网指定的网络在禁止列表中，注册成功后，
                 没有向LMM发送等效PLMN
  3.日    期   : 2012年5月10日
    作    者   : l65478
    修改内容   : DTS2012050500988:CS注册成功时,不能删除forbid PLMN for GPRS信息
  4.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_VOID NAS_MMC_ProcLmmCombinedTauResult(
    LMM_MMC_TAU_RESULT_IND_STRU                            *pstLmmTauIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction
)
{
    switch (pstLmmTauIndMsg->ulTauRst)
{
    case MMC_LMM_TAU_RSLT_SUCCESS:
        NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltSucc(pstLmmTauIndMsg,
                   enCsRegRsltCause, penCsRegAdditionalAction, penPsRegAdditionalAction);

        break;

    case MMC_LMM_TAU_RSLT_FAILURE:
        if (VOS_FALSE == pstLmmTauIndMsg->bitOpAtmpCnt)
        {
            if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
            {
                /* LNAS后续还有注册尝试流程-这里继续等待下 */
                NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
            }

            *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
            *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;


            /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
            NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_FALSE, NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
            /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */
        }
        else
        {
            /* EPS和CS注册均失败 */
            NAS_MMC_ProcCombinedTauEpsRegFail(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg,
                                          penPsRegAdditionalAction, penCsRegAdditionalAction);
        }
        break;

    case MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE:
    case MMC_LMM_TAU_RSLT_MT_DETACH_FAILURE:
    case MMC_LMM_TAU_RSLT_T3402_RUNNING:
    case MMC_LMM_TAU_RSLT_TIMER_EXP:
    case MMC_LMM_TAU_RSLT_ACCESS_BARED:
    case MMC_LMM_TAU_RSLT_FORBID_PLMN:
    case MMC_LMM_TAU_RSLT_FORBID_TA_FOR_RPOS:
    case MMC_LMM_TAU_RSLT_FORBID_PLMN_FOR_GPRS:
    case MMC_LMM_TAU_RSLT_FORBID_TA_FOR_ROAMING:
    case MMC_LMM_TAU_RSLT_AUTH_REJ:
        /* EPS和CS注册均失败 */
        NAS_MMC_ProcCombinedTauEpsRegFail(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg,
                                      penPsRegAdditionalAction, penCsRegAdditionalAction);
        break;

    case MMC_LMM_TAU_RSLT_CN_REJ:
        if ((VOS_TRUE == pstLmmTauIndMsg->bitOpCnRst)
         && ((MMC_LMM_TA_UPDATED == pstLmmTauIndMsg->ulCnRst)
          || (MMC_LMM_TA_UPDATED_ISR_ACTIVATED == pstLmmTauIndMsg->ulCnRst)))
        {
            /* 当TAU请求类型为联合，网侧相应的TAU结果类型为TA UPDATED，
               且原因值不为协议24301 5.5.3.3.4.3章节所列或者没有携带原因值，
               则LMM通过TAU结果中MMC_LMM_TAU_RSLT_CN_REJ通知MMC，且携带相应
               的TAU请求类型、网侧响应的TAU结果类型、原因值，并携带处理该原
               因后的tau attempt counter值 */
            NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltEpsOnlySucc(pstLmmTauIndMsg,enCsRegRsltCause,
                              penCsRegAdditionalAction, penPsRegAdditionalAction);

        }
        else
        {
            /* EPS和CS注册均失败 */
            NAS_MMC_ProcCombinedTauEpsRegFail(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg,
                                          penPsRegAdditionalAction, penCsRegAdditionalAction);
        }
        break;

    case MMC_LMM_TAU_RSLT_T3402_RUNNING_EPS_ONLY_SUCC:
        NAS_MMC_ProcCombinedEpsRegFailCauseT3402RunningEpsOnlySucc(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg,
                                          penPsRegAdditionalAction, penCsRegAdditionalAction);
        break;

    default:

        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmCombinedTauResult:Unexpected tau result!");
        *penPsRegAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_L1Main();
        *penCsRegAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_L1Main();
        break;
    }

    return;
}

#endif
/*****************************************************************************
 函 数 名  : NAS_MMC_GetAdditionalActionPrioValue
 功能描述  : 获取AdditonalAction对应的优先级
 输入参数  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAction,
             VOS_UINT8                          *pucPrioValue
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月22日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_GetAdditionalActionPrioValue(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAction,
    VOS_UINT8                           *pucPrioValue
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulTblSize;

    ulTblSize = sizeof(gastAdditionalActionPrioArr)/sizeof(gastAdditionalActionPrioArr[0]);

    for  ( i = 0 ; i < ulTblSize ; i++ )
    {
        if (enAction == gastAdditionalActionPrioArr[i].enAdditionalAction)
        {
           *pucPrioValue = gastAdditionalActionPrioArr[i].ucPriority;
            return;
        }
    }

    /* 未查找到则返回BUTT对齐的优先级 */
    *pucPrioValue = gastAdditionalActionPrioArr[NAS_MMC_ADDITIONAL_ACTION_BUTT].ucPriority;

}
/*****************************************************************************
 函 数 名  : NAS_MMC_GetPrioAddtionalAction
 功能描述  : 获取当前优先的AdditonalAction
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月22日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8  NAS_MMC_GetPrioAddtionalAction(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enPsAdditionalAction
)
{
    VOS_UINT8                           ucCsPriority;
    VOS_UINT8                           ucPsPriority;


    NAS_MMC_GetAdditionalActionPrioValue(enCsAdditionalAction, &ucCsPriority);
    NAS_MMC_GetAdditionalActionPrioValue(enPsAdditionalAction, &ucPsPriority);

    /* 权值越小，优先级越高 */
    if (ucCsPriority < ucPsPriority)
    {
        return enCsAdditionalAction;
    }
    else
    {
        return enPsAdditionalAction;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsAdditionalActionTrigerPlmnSrch
 功能描述  : AdditionalAction是否会触发搜网
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: 需要触发搜网
             VOS_FALSE: 不需要触发搜网
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月27日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsAdditionalActionTrigerPlmnSrch(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAdditionalAction
)
{
    switch (enAdditionalAction)
    {
        case NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL:
        case NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION :
        case NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL :
        case NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN :
        case NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION:
            return VOS_TRUE;

        default:

            return VOS_FALSE;
    }

}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPsAdditionalAction
 功能描述  : 获取PS的AdditionalAction
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8,PS的AdditionalAction
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetPsAdditionalAction(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;

    /* 获取当前状态机ID，更据状态机调用不同状态机的获取PS AdditionalAction函数 */
    enFsmId                = NAS_MMC_GetCurrFsmId();
    if (NAS_FSM_BUTT <= enFsmId)
    {
        NAS_ERROR_LOG1(WUEPS_PID_MMC, "NAS_MMC_GetPsAdditionalAction,ERROR:FsmId Error", enFsmId);

        return NAS_MMC_ADDITIONAL_ACTION_BUTT;
    }

    if (NAS_MMC_FSM_L1_MAIN == enFsmId)
    {
        return NAS_MMC_GetPsRegAdditionalAction_L1Main();
    }
    else if (NAS_MMC_FSM_PLMN_LIST == enFsmId)
    {
        return NAS_MMC_GetPsRegAdditionalAction_PlmnList();
    }
    else if (NAS_MMC_FSM_BG_PLMN_SEARCH == enFsmId)
    {
        return NAS_MMC_GetPsRegAdditionalAction_BgPlmnSearch();
    }
    else if (NAS_MMC_FSM_PLMN_SELECTION == enFsmId)
    {
        return NAS_MMC_GetPsRegAdditionalAction_PlmnSelection();
    }
    else
    {
        NAS_WARNING_LOG1(WUEPS_PID_MMC, "NAS_MMC_GetPsAdditionalAction,WARNING:This Fsm not have Ps Additon", enFsmId);
    }

    return NAS_MMC_ADDITIONAL_ACTION_BUTT;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetCsAdditionalAction
 功能描述  : 获取CS的AdditionalAction
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8,CS的AdditionalAction
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCsAdditionalAction(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;

    /* 获取当前状态机ID，更据状态机调用不同状态机的获取CS AdditionalAction函数 */
    enFsmId                = NAS_MMC_GetCurrFsmId();
    if (NAS_FSM_BUTT <= enFsmId)
    {
        NAS_ERROR_LOG1(WUEPS_PID_MMC, "NAS_MMC_GetCsAdditionalAction,ERROR:FsmId Error", enFsmId);

        return NAS_MMC_ADDITIONAL_ACTION_BUTT;
    }

    if (NAS_MMC_FSM_L1_MAIN == enFsmId)
    {
        return NAS_MMC_GetCsRegAdditionalAction_L1Main();
    }
    else if (NAS_MMC_FSM_PLMN_LIST == enFsmId)
    {
        return NAS_MMC_GetCsRegAdditionalAction_PlmnList();
    }
    else if (NAS_MMC_FSM_BG_PLMN_SEARCH == enFsmId)
    {
        return NAS_MMC_GetCsRegAdditionalAction_BgPlmnSearch();
    }
    else if (NAS_MMC_FSM_PLMN_SELECTION == enFsmId)
    {
        return NAS_MMC_GetCsRegAdditionalAction_PlmnSelection();
    }
    else
    {
        NAS_WARNING_LOG1(WUEPS_PID_MMC, "NAS_MMC_GetCsAdditionalAction,WARNING:This Fsm not have Cs Additon", enFsmId);
    }

    return NAS_MMC_ADDITIONAL_ACTION_BUTT;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetLmmAttaClRegStatPrioValue
 功能描述  : 获取当前优先的lmm attach cl 注册状态
 输入参数  : MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8  enLmmAttachClReqStatus
             VOS_UINT8                          *pucPrioValue
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月22日
    作    者   : wx270776
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetLmmAttaClRegStatPrioValue(
    MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8  enLmmAttachClReqStatus
)
{

    VOS_UINT32                          i;
    VOS_UINT32                          ulTblSize;
    VOS_UINT32                          ulPrioValue;

    ulPrioValue = gastLmmAttaClRegStatPrio[MMC_LMM_CL_REG_STATUS_BUTT].ucPriority;

    ulTblSize = sizeof(gastLmmAttaClRegStatPrio)/sizeof(gastLmmAttaClRegStatPrio[0]);

    for  ( i = 0 ; i < ulTblSize ; i++ )
    {
        if (enLmmAttachClReqStatus == gastLmmAttaClRegStatPrio[i].enLmmAttachClReqStatus)
        {
            ulPrioValue = gastLmmAttaClRegStatPrio[i].ucPriority;

            return ulPrioValue;
        }
    }

    return ulPrioValue;
}

#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertLmmCauseToMmCause
 功能描述  : 将MM的注册结果转换为EMM的注册结果,由于需要明确告诉EMM是否是网络
              拒绝还是其他原因拒绝
 输入参数  : enCnCause:MM注册结果
 输出参数  : penProtolCause:协议中规定的结果
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_ConvertLmmCauseToMmCause(
    NAS_LMM_CN_CAUSE_ENUM_UINT8          enLmmCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  *penMmCnCause
)
{
    *penMmCnCause = (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)enLmmCause;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConverLmmCombinedAttachRsltToMMLCause
 功能描述  : 将LmmAttach的联合注册结果转换为对应的ps cause值和cs cause值
 输入参数  : pstLmmAttachIndMsg - 联合attach消息内容
 输出参数  : penPsRegRsltCause  - ps域注册原因值
             penCsRegRsltCause  - cs域注册原因值
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月25日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年1月8日
    作    者   : z00161729
    修改内容   : V7R1 phase IV修改
  3.日    期   : 2012年1月2日
    作    者   : w00167002
    修改内容   : DTS2011102200381:L下注册被拒#12,LMM给MMC带的ATTACH及TAU
                 中的结果为MMC_LMM_ATT_RSLT_FORBID，MMC收到此结果后按照禁止网络
                 来处理而发起了搜网。

*****************************************************************************/
VOS_VOID NAS_MMC_ConverLmmCombinedAttachRsltToMMLCause(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penPsRegRsltCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penCsRegRsltCause
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 enPsCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 enCsCause;
    MMC_LMM_ATTACH_CN_RSLT_ENUM_UINT32 ulAttachCnRslt;

    enPsCause      = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
    enCsCause      = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
    ulAttachCnRslt = MMC_LMM_ATT_CN_RSLT_BUTT;

    if (VOS_TRUE == pstLmmAttachIndMsg->bitOpCnRslt)
    {
        ulAttachCnRslt = pstLmmAttachIndMsg->ulCnRslt;
    }

    switch (pstLmmAttachIndMsg->ulAttachRslt)
    {
        case MMC_LMM_ATT_RSLT_SUCCESS:
            if (MMC_LMM_ATT_CN_RSLT_COMBINED_EPS_IMSI == ulAttachCnRslt)
            {
                /* 联合注册cs ps域均注册成功 */
                enPsCause = NAS_MML_REG_FAIL_CAUSE_NULL;
                enCsCause = NAS_MML_REG_FAIL_CAUSE_NULL;
                break;
            }
            if (MMC_LMM_ATT_CN_RSLT_EPS_ONLY == ulAttachCnRslt)
            {
                /* 联合注册ps域注册成功，cs域注册失败 */
                enPsCause = NAS_MML_REG_FAIL_CAUSE_NULL;
                NAS_MMC_ConvertLmmCauseToMmCause((VOS_UINT8)pstLmmAttachIndMsg->ucCnCause, &enCsCause);
                break;
            }

            NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_ConverLmmCombinedAttachRsltToMMLCause: attach ind cnRslt value is invalid");
            break;

        case MMC_LMM_ATT_RSLT_CN_REJ:
            if (MMC_LMM_ATT_CN_RSLT_EPS_ONLY == ulAttachCnRslt)
            {
                enPsCause = NAS_MML_REG_FAIL_CAUSE_NULL;
                if (VOS_TRUE == pstLmmAttachIndMsg->bitOpCnCause)
                {
                    NAS_MMC_ConvertLmmCauseToMmCause((VOS_UINT8)pstLmmAttachIndMsg->ucCnCause, &enCsCause);
                }
                break;
            }

            if (VOS_TRUE == pstLmmAttachIndMsg->bitOpCnCause)
            {
                NAS_MMC_ConvertLmmCauseToMmCause((VOS_UINT8)pstLmmAttachIndMsg->ucCnCause, &enPsCause);
                enCsCause = enPsCause;
            }
            break;

        case MMC_LMM_ATT_RSLT_ACCESS_BAR:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;
            break;

        case MMC_LMM_ATT_RSLT_TIMER_EXP :
            enPsCause = NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT;
            break;

        case MMC_LMM_ATT_RSLT_AUTH_REJ :
            enPsCause = NAS_MML_REG_FAIL_CAUSE_AUTH_REJ;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_AUTH_REJ;
            break;

        case MMC_LMM_ATT_RSLT_FAILURE:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
            break;

        case MMC_LMM_ATT_RSLT_FORBID_PLMN:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN;
            break;

        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS;
            break;

        case MMC_LMM_ATT_RSLT_FORBID_PLMN_FOR_GPRS:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS;
            break;

        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_ROAMING:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM;
            break;
        case MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_PS_ATTACH_NOT_ALLOW;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_PS_ATTACH_NOT_ALLOW;
            break;

        case MMC_LMM_ATT_RSLT_ESM_FAILURE:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_ESM_BEAR_FAILURE;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_ESM_BEAR_FAILURE;
            break;

        case MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_MO_DETACH_FAILURE;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_MO_DETACH_FAILURE;
            break;

        case MMC_LMM_ATT_RSLT_MT_DETACH_FAILURE:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_MT_DETACH_FAILURE;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_MT_DETACH_FAILURE;
            break;

        case MMC_LMM_ATT_RSLT_T3402_RUNNING:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_FAIL;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_FAIL;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ConverLmmCombinedAttachRsltToMMLCause: attach ind ulAttachRslt invalid");
            break;
    }

    *penPsRegRsltCause = enPsCause;
    *penCsRegRsltCause = enCsCause;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConverLmmCombinedTauRsltToMMLCause
 功能描述  : 将Lmmtau的联合注册结果转换为对应的ps cause值和cs cause值
 输入参数  : pstLmmTauResultInd - 联合tau消息内容
 输出参数  : penPsRegRsltCause  - ps注册原因值
             penCsRegRsltCause  - cs注册原因值
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月27日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年1月8日
    作    者   : z00161729
    修改内容   : V7R1 phase IV修改
 3.日    期   : 2012年1月2日
   作    者   : w00167002
   修改内容   : DTS2011102200381:L下注册被拒#12,LMM给MMC带的ATTACH及TAU
                中的结果为MMC_LMM_ATT_RSLT_FORBID，MMC收到此结果后按照禁止网络
                来处理而发起了搜网。
 4.日    期   : 2012年5月11日
   作    者   : w00166186
   修改内容   : DTS2012051006163:高优先级被指定搜VPLMN打断，搜网成功，但AT返回失败。

*****************************************************************************/
VOS_VOID NAS_MMC_ConverLmmCombinedTauRsltToMMLCause(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauResultInd,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penPsRegRsltCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penCsRegRsltCause
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause;
    MMC_LMM_TAU_CN_RSLT_ENUM_UINT32     ulTauCnRst;

    enPsCause  = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
    enCsCause  = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
    ulTauCnRst = MMC_LMM_TAU_CN_RSLT_BUTT;

    if (VOS_TRUE == pstLmmTauResultInd->bitOpCnRst)
    {
        ulTauCnRst = pstLmmTauResultInd->ulCnRst;
    }

    switch (pstLmmTauResultInd->ulTauRst)
    {
        case MMC_LMM_TAU_RSLT_SUCCESS:

            enPsCause = NAS_MML_REG_FAIL_CAUSE_NULL;

            if ( (MMC_LMM_COMBINED_TA_LA_UPDATED == ulTauCnRst)
              || (MMC_LMM_COMBINED_TA_LA_UPDATED_ISR_ACTIVATED == ulTauCnRst))
            {
                /* 联合注册cs ps域均注册成功 */
                enCsCause = NAS_MML_REG_FAIL_CAUSE_NULL;
                break;
            }

            if (((MMC_LMM_TA_UPDATED == ulTauCnRst)
              || (MMC_LMM_TA_UPDATED_ISR_ACTIVATED == ulTauCnRst))
             && (VOS_TRUE == pstLmmTauResultInd->bitOpCnCause) )
            {
                /* 联合注册ps域注册成功，cs域注册失败 */
                NAS_MMC_ConvertLmmCauseToMmCause((VOS_UINT8)pstLmmTauResultInd->ucCnCause, &enCsCause);
                break;
            }

            NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_ConverLmmCombinedTauRsltToMMLCause: tau cnRslt value is invalid");
            break;

        case MMC_LMM_TAU_RSLT_CN_REJ:
            if ((MMC_LMM_TA_UPDATED == ulTauCnRst)
             || (MMC_LMM_TA_UPDATED_ISR_ACTIVATED == ulTauCnRst))
            {
                enPsCause = NAS_MML_REG_FAIL_CAUSE_NULL;
                if (VOS_TRUE == pstLmmTauResultInd->bitOpCnCause)
                {
                    NAS_MMC_ConvertLmmCauseToMmCause((VOS_UINT8)pstLmmTauResultInd->ucCnCause, &enCsCause);
                }
                break;
            }

            if (VOS_TRUE == pstLmmTauResultInd->bitOpCnCause)
            {
                NAS_MMC_ConvertLmmCauseToMmCause((VOS_UINT8)pstLmmTauResultInd->ucCnCause, &enPsCause);
                enCsCause = enPsCause;
            }
            break;

        case MMC_LMM_TAU_RSLT_ACCESS_BARED:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;
            break;

        case MMC_LMM_TAU_RSLT_TIMER_EXP :
            enPsCause = NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT;
            break;

        case MMC_LMM_TAU_RSLT_AUTH_REJ :
            enPsCause = NAS_MML_REG_FAIL_CAUSE_AUTH_REJ;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_AUTH_REJ;
            break;

        case MMC_LMM_TAU_RSLT_FAILURE:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
            break;

        case MMC_LMM_TAU_RSLT_FORBID_PLMN:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN;
            break;

        case MMC_LMM_TAU_RSLT_FORBID_TA_FOR_RPOS:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS;
            break;

        case MMC_LMM_TAU_RSLT_FORBID_PLMN_FOR_GPRS:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS;
            break;

        case MMC_LMM_TAU_RSLT_FORBID_TA_FOR_ROAMING:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM;
            break;
        case  MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_MO_DETACH_FAILURE;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_MO_DETACH_FAILURE;
            break;

        case  MMC_LMM_TAU_RSLT_MT_DETACH_FAILURE:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_MT_DETACH_FAILURE;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_MT_DETACH_FAILURE;
            break;

        case MMC_LMM_TAU_RSLT_T3402_RUNNING:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_FAIL;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_FAIL;
            break;

        case MMC_LMM_TAU_RSLT_T3402_RUNNING_EPS_ONLY_SUCC:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_ONLY_SUCC;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_ONLY_SUCC;
            break;

        default:
            break;
    }

    *penPsRegRsltCause = enPsCause;
    *penCsRegRsltCause = enCsCause;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConverLmmAttachRsltToMMLCause
 功能描述  : 将LmmAttach的对应结果转换为对应的Cause值
 输入参数  : pstLmmAttachIndMsg
 输出参数  : penRegRsltCause
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月24日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV调整:EPS单域注册假流程调整
  3.日    期   : 2011年12月28日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV增加新的attach result
  4.日    期   : 2011年12月29日
    作    者   : w00167002
    修改内容   : DTS2011102200381:L下注册被拒#12,LMM给MMC带的TAU
                 中的结果为MMC_LMM_TAU_RSLT_FORBID_PLMNS，MMC收到此结果后按照禁止网络
                 来处理而发起了搜网。
                  修改内容:将L模带过来的假流程值转换为NAS内部的假流程值

  5.日    期   : 2012年09月27日
    作    者   : z00161729
    修改内容   : DTS2012090303562:搜网状态机等L注册结果收到丢网消息获取下一个网络失败退状态机后又发起非法随机网络搜网

*****************************************************************************/
VOS_VOID NAS_MMC_ConverLmmAttachRsltToMMLCause(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penRegRsltCause
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 enCause;

    enCause  = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;

    switch (pstLmmAttachIndMsg->ulAttachRslt)
    {
        case MMC_LMM_ATT_RSLT_SUCCESS:
            enCause = NAS_MML_REG_FAIL_CAUSE_NULL;
            break;

        case MMC_LMM_ATT_RSLT_CN_REJ:

            if (VOS_TRUE == pstLmmAttachIndMsg->bitOpCnCause)
            {
                NAS_MMC_ConvertLmmCauseToMmCause((VOS_UINT8)pstLmmAttachIndMsg->ucCnCause,
                                                                &enCause);
            }

            break;

        case MMC_LMM_ATT_RSLT_ACCESS_BAR:
            enCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;
            break;

        case MMC_LMM_ATT_RSLT_TIMER_EXP :
            enCause = NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT;
            break;

        case MMC_LMM_ATT_RSLT_AUTH_REJ :
            enCause = NAS_MML_REG_FAIL_CAUSE_AUTH_REJ;
            break;

        case MMC_LMM_ATT_RSLT_FAILURE:
            enCause = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
            break;


        /* L下假流程被拒原因值#11场景 */
        case MMC_LMM_ATT_RSLT_FORBID_PLMN:
            enCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN;
            break;

        /* L下假流程被拒原因值#12场景 */
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS:
            enCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS;
            break;

        /* L下假流程被拒原因值#14场景 */
        case MMC_LMM_ATT_RSLT_FORBID_PLMN_FOR_GPRS:
            enCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS;
            break;

        /* L下假流程被拒原因值#13 #15场景 */
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_ROAMING:
            enCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM;
            break;

        case MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW:
            enCause = NAS_MML_REG_FAIL_CAUSE_PS_ATTACH_NOT_ALLOW;
            break;

        case MMC_LMM_ATT_RSLT_ESM_FAILURE:
            enCause = NAS_MML_REG_FAIL_CAUSE_ESM_BEAR_FAILURE;
            break;

        case MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE:
            enCause = NAS_MML_REG_FAIL_CAUSE_MO_DETACH_FAILURE;
            break;

        case MMC_LMM_ATT_RSLT_MT_DETACH_FAILURE:
            enCause = NAS_MML_REG_FAIL_CAUSE_MT_DETACH_FAILURE;
            break;

        case MMC_LMM_ATT_RSLT_T3402_RUNNING:
            enCause = NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_FAIL;
            break;

        default:
            break;
    }

    *penRegRsltCause = enCause;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConverLmmServiceRsltToMMLCause
 功能描述  : 将pstLmmSerRsltIndMsg的对应结果转换为对应的Cause值
 输入参数  : pstLmmSerRsltIndMsg
 输出参数  : penRegRsltCause
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月29日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年12月17日
    作    者   : w00176964
    修改内容   : V7R1 PhaseIV调整:获取cause值先检查OP项
  3.日    期   : 2015年1月5日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改

*****************************************************************************/
VOS_VOID NAS_MMC_ConverLmmServiceRsltToMMLCause(
    LMM_MMC_SERVICE_RESULT_IND_STRU    *pstLmmSerRsltIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penRegRsltCause
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 enCause;

    enCause  = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;

    switch (pstLmmSerRsltIndMsg->ulServiceRst)
    {
        case MMC_LMM_SERVICE_RSLT_CN_REJ:

            if ( VOS_TRUE == pstLmmSerRsltIndMsg->bitOpCnCause)
            {
                NAS_MMC_ConvertLmmCauseToMmCause((VOS_UINT8)pstLmmSerRsltIndMsg->ucCnCause,
                                                                    &enCause);
            }

            break;

        case MMC_LMM_SERVICE_RSLT_ACCESS_BARED:
            enCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;
            break;

        case MMC_LMM_SERVICE_RSLT_AUTH_REJ :
            enCause = NAS_MML_REG_FAIL_CAUSE_AUTH_REJ;
            break;

        case MMC_LMM_SERVICE_RSLT_FAILURE:
            enCause = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
            break;

        case MMC_LMM_SERVICE_RSLT_TIMER_EXP:
            enCause = NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT;

        default:
            break;
    }

    *penRegRsltCause = enCause;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConverTauResultToMMLCause
 功能描述  : 将LmmAttach的对应结果转换为对应的Cause值
 输入参数  : pstLmmTauIndMsg
 输出参数  : penRegRsltCause
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月24日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV调整:EPS单域注册假流程调整
  3.日    期   : 2011年12月29日
    作    者   : w00167002
    修改内容   : DTS2011102200381:L下注册被拒#12,LMM给MMC带的TAU
                 中的结果为MMC_LMM_TAU_RSLT_FORBID_PLMNS，MMC收到此结果后按照禁止网络
                 来处理而发起了搜网。
                  修改内容:将L模带过来的假流程值转换为NAS内部的假流程值
  4.日    期   : 2012年7月9日
    作    者   : z00161729
    修改内容  : GUL 背景搜修改
*****************************************************************************/
VOS_VOID NAS_MMC_ConverTauResultToMMLCause(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penRegRsltCause
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;

    enCause  = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;

    switch (pstLmmTauIndMsg->ulTauRst)
    {
        case MMC_LMM_TAU_RSLT_SUCCESS:
            enCause = NAS_MML_REG_FAIL_CAUSE_NULL;
            break;

        case MMC_LMM_TAU_RSLT_CN_REJ:

            if (VOS_TRUE == pstLmmTauIndMsg->bitOpCnCause)
            {
                NAS_MMC_ConvertLmmCauseToMmCause((VOS_UINT8)pstLmmTauIndMsg->ucCnCause,
                                                                &enCause);
            }

            break;

        case MMC_LMM_TAU_RSLT_ACCESS_BARED:
            enCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;
            break;

        case MMC_LMM_TAU_RSLT_TIMER_EXP :
            enCause = NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT;
            break;

        case MMC_LMM_TAU_RSLT_AUTH_REJ :
            enCause = NAS_MML_REG_FAIL_CAUSE_AUTH_REJ;
            break;

        case MMC_LMM_TAU_RSLT_FAILURE:
            enCause = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
            break;


        /* L下假流程被拒原因值#11场景 */
        case MMC_LMM_TAU_RSLT_FORBID_PLMN:
            enCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN;
            break;

        /* L下假流程被拒原因值#12场景 */
        case MMC_LMM_TAU_RSLT_FORBID_TA_FOR_RPOS:
            enCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS;
            break;

        /* L下假流程被拒原因值#14场景 */
        case MMC_LMM_TAU_RSLT_FORBID_PLMN_FOR_GPRS:
            enCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS;
            break;

        /* L下假流程被拒原因值#13 #15场景 */
        case MMC_LMM_TAU_RSLT_FORBID_TA_FOR_ROAMING:
            enCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM;
            break;


        case  MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE:
            enCause = NAS_MML_REG_FAIL_CAUSE_MO_DETACH_FAILURE;
            break;

        case  MMC_LMM_TAU_RSLT_MT_DETACH_FAILURE:
            enCause = NAS_MML_REG_FAIL_CAUSE_MT_DETACH_FAILURE;
            break;

        case MMC_LMM_TAU_RSLT_T3402_RUNNING:
            enCause = NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_FAIL;
            break;


        case MMC_LMM_TAU_RSLT_T3402_RUNNING_EPS_ONLY_SUCC:
            enCause = NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_ONLY_SUCC;
            break;

        default:
            break;
    }

    *penRegRsltCause = enCause;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertLmmAttachReqType
 功能描述  : 联合EPS OtherCause的处理
 输入参数  : VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 输出参数  : penPsRegAdditionalAction - 收到注册结果后，协议要求的ps域的additional动作类型
             penCsRegAdditionalAction - 收到注册结果后，协议要求的cs域的additional动作类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月25日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
MMC_LMM_ATTACH_TYPE_ENUM_UINT32 NAS_MMC_ConvertLmmAttachReqType(
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enUeOperationMode
)
{
    if ((NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_2 == enUeOperationMode)
     || (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 == enUeOperationMode))
    {
        return MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI;
    }
    else if ((NAS_MML_LTE_UE_OPERATION_MODE_PS_2 == enUeOperationMode)
          || (NAS_MML_LTE_UE_OPERATION_MODE_PS_1 == enUeOperationMode))
    {
        return MMC_LMM_ATT_TYPE_EPS_ONLY;
    }
    else
    {
        return MMC_LMM_ATT_TYPE_BUTT;
    }

}



/*******************************************************************************
 函 数 名  : NAS_MMC_ConvertGmmRegDomainToMmcDomain
 功能描述  : 将GMM的注册域转化为MMC的格式
 输入参数  : enRegDomain GMM的注册域
 输出参数  : penMmcRegDomain MMC的注册域
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月30日
   作    者   : l00130025
   修改内容   : DTS2012032307791,发给LMM注册结果,CombineReg时需要区分结果域

*******************************************************************************/
VOS_VOID NAS_MMC_ConvertGmmRegDomainToMmcDomain(
    GMM_MMC_REG_DOMAIN_ENUM_UINT32      enRegDomain,
    NAS_MMC_REG_DOMAIN_ENUM_UINT8      *penMmcRegDomain
)
{
    if (GMM_MMC_REG_DOMAIN_PS_CS == enRegDomain)
    {
        *penMmcRegDomain = NAS_MMC_REG_DOMAIN_PS_CS;
    }
    else
    {
        *penMmcRegDomain =  NAS_MMC_REG_DOMAIN_PS;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedDisableL_CombinedAttRsltFailMaxTimes
 功能描述  : 联合注册失败需要Disable L
 输入参数  : 无
 输出参数  : 无
 返回值    : VOS_TRUE   需要Disable L
              VOS_FALSE  不需要Disable L
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月02日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2014年01月10日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseIII项目
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_CombinedRegRsltFailMaxTimes()
{
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;

    enLUeMode        = NAS_MML_GetLteUeOperationMode();

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
    /* 不是CS/PS mode 1 */
    if (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 != enLUeMode)
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */
    {
        return VOS_FALSE;
    }

    /* LTE only */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedDisableL_CombinedAttRsltFailCause14GprsNotAllowInThisPlmn
 功能描述  : 判断联合注册失败#14需要Disable L
 输入参数  : 无
 输出参数  : 无
 返回值    : VOS_TRUE   需要Disable L
             VOS_FALSE  不需要Disable L
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月19日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_CombinedAttRsltFailCause14GprsNotAllowInThisPlmn(VOS_VOID)
{
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;

    enLUeMode        = NAS_MML_GetLteUeOperationMode();

    /* 协议版本小于R11不disable lte */
    if (NAS_MML_GetLte3gppRelVersion() < NAS_MML_3GPP_REL_R11)
    {
        return VOS_FALSE;
    }

    /* 不是CS/PS mode 1 */
    if (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 != enLUeMode)
    {
        return VOS_FALSE;
    }

    /* LTE only */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedAddForbGprsPlmn_TauRsltFailCause14GprsNotAllowInThisPlmn
 功能描述  : L下注册失败被拒#14判断是否需要加入禁止gprs网络列表
 输入参数  : 无
 输出参数  : 无
 返回值    : VOS_TRUE - 需要加入禁止gprs网络列表
             VOS_FALSE- 不需要加入禁止gprs网络列表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月19日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedAddForbGprsPlmn_TauRsltFailCause14GprsNotAllowInThisPlmn(VOS_VOID)
{
    VOS_UINT8                           ucEpsSrvConnStatusFlag;
    NAS_MML_SUIT_PLMN_LIST_STRU        *pstSuitPlmnList = VOS_NULL_PTR;
    NAS_MMC_REG_RSLT_CTX_STRU          *pstRegRsltCtx = VOS_NULL_PTR;

    ucEpsSrvConnStatusFlag = NAS_MML_GetEpsServiceConnStatusFlg();
    pstSuitPlmnList        = NAS_MML_GetSuitPlmnList();
    pstRegRsltCtx          = NAS_MMC_GetRegRsltCtxAddr();

    /* 协议版本小于R11需要返回VOS_TRUE */
    if (NAS_MML_GetLte3gppRelVersion() < NAS_MML_3GPP_REL_R11)
    {
        return VOS_TRUE;
    }

    /* 24301_CR1528R1_(Rel-11)_C1-124123共享网络，连接态发起TAU，被拒绝后，MMC不更新被禁PLMN列表
       对应24301 5.5.3.1章节描述:
       In a shared network, if TRACKING AREA UPDATE REJECT is received as a response
    to a tracking area update procedure initiated in EMM-CONNECTED mode, the UE
    need not update forbidden lists.该CR受协议版本控制 */

    /* 仅对tau流程 */
    if ((LMM_MMC_TAU_RESULT_IND == pstRegRsltCtx->enRegRsltType)
     && (pstSuitPlmnList->ucSuitPlmnNum > 1)
     && (VOS_TRUE == ucEpsSrvConnStatusFlag))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedDeleteEplmn_CombinedRegRsltFailCause14GprsNotAllowInThisPlmn
 功能描述  : L下注册失败被拒#14判断是否需要删除等效plmn
 输入参数  : 无
 输出参数  : 无
 返回值    : VOS_TRUE - 需要删除eplmn
             VOS_FALSE- 不需要删除eplmn
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月19日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDeleteEplmn_CombinedRegRsltFailCause14GprsNotAllowInThisPlmn(VOS_VOID)
{
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;

    enLUeMode  = NAS_MML_GetLteUeOperationMode();

    /* 协议版本小于R11,不需要删除eplmn，返回VOS_FALSE */
    if (NAS_MML_GetLte3gppRelVersion() < NAS_MML_3GPP_REL_R11)
    {
        return VOS_FALSE;
    }

    /* 24301_CR1422R1_(Rel-11)_C1-121612 对应24301 5.5.3.3.5和5.5.1.3.5章节:
         A UE operating in CS/PS mode 1 of operation and supporting A/Gb or Iu mode
      may perform a PLMN selection according to 3GPP TS 23.122 [6].
         A UE operating in CS/PS mode 1 of operation and supporting S1 mode only,
      or operating in CS/PS mode 2 of operation shall delete the list of
      equivalent PLMNs and shall perform a PLMN selection according to 3GPP TS 23.122 [6].
      该CR受协议版本控制 */
    if (((VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
       && (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 == enLUeMode))
      || (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_2 == enLUeMode))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedDeleteEplmn_EpsDetachCause14GprsNotAllowInThisPlmn
 功能描述  : L下网络detach ind被拒#14判断是否需要删除等效plmn
 输入参数  : 无
 输出参数  : 无
 返回值    : VOS_TRUE - 需要删除eplmn
             VOS_FALSE- 不需要删除eplmn
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月19日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDeleteEplmn_EpsDetachCause14GprsNotAllowInThisPlmn(VOS_VOID)
{
    /* 24301_CR1422R1_(Rel-11)_C1-121612 对应24301 5.5.2.3.2章节:
         A UE operating in CS/PS mode 1 of operation and supporting A/Gb or Iu mode
      may perform a PLMN selection according to 3GPP TS 23.122 [6].
         A UE operating in CS/PS mode 1 of operation and supporting S1 mode only,
      or operating in CS/PS mode 2 of operation shall delete the list of
      equivalent PLMNs and shall perform a PLMN selection according to 3GPP TS 23.122 [6].
      该CR受协议版本控制 */
    return NAS_MMC_IsNeedDeleteEplmn_CombinedRegRsltFailCause14GprsNotAllowInThisPlmn();

}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedAddForbPlmn_TauRsltFailCause11PlmnNotAllow
 功能描述  : L下注册失败被拒#11判断是否需要加入禁止网络列表
 输入参数  : 无
 输出参数  : 无
 返回值    : VOS_TRUE - 需要加入禁止网络列表
             VOS_FALSE- 不需要加入禁止网络列表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月19日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedAddForbPlmn_TauRsltFailCause11PlmnNotAllow(VOS_VOID)
{
    VOS_UINT8                           ucEpsSrvConnStatusFlag;
    NAS_MML_SUIT_PLMN_LIST_STRU        *pstSuitPlmnList = VOS_NULL_PTR;

    ucEpsSrvConnStatusFlag = NAS_MML_GetEpsServiceConnStatusFlg();
    pstSuitPlmnList        = NAS_MML_GetSuitPlmnList();

    /* 协议版本小于R11需要返回VOS_TRUE */
    if (NAS_MML_GetLte3gppRelVersion() < NAS_MML_3GPP_REL_R11)
    {
        return VOS_TRUE;
    }

    /* 24301_CR1528R1_(Rel-11)_C1-124123共享网络，连接态发起TAU，被拒绝后，MMC不更新被禁PLMN列表
       对应24301 5.5.3.1章节描述:
       In a shared network, if TRACKING AREA UPDATE REJECT is received as a response
    to a tracking area update procedure initiated in EMM-CONNECTED mode, the UE
    need not update forbidden lists. 该CR受协议版本控制 */
    /*pstSuitPlmnList->ucSuitPlmnNum个数大于1表示存在共享网络 */
    if ((pstSuitPlmnList->ucSuitPlmnNum > 1)
     && (VOS_TRUE == ucEpsSrvConnStatusFlag))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedDisableL_EpsDetachCause14GprsNotAllowInThisPlmn
 功能描述  : 判断网络detach ind被拒#14是否需要Disable L
 输入参数  : 无
 输出参数  : 无
 返回值    : VOS_TRUE   需要Disable L
             VOS_FALSE  不需要Disable L
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月19日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_EpsDetachCause14GprsNotAllowInThisPlmn(VOS_VOID)
{
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;

    enLUeMode        = NAS_MML_GetLteUeOperationMode();

    /* 协议版本小于R11不disable lte */
    if (NAS_MML_GetLte3gppRelVersion() < NAS_MML_3GPP_REL_R11)
    {
        return VOS_FALSE;
    }

    /* 不是CS/PS mode 1 */
    if (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 != enLUeMode)
    {
        return VOS_FALSE;
    }

    /* LTE only */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedDisableL_CombinedRegRsltSucc
 功能描述  : 判断联合Attch或联合TAU成功时是否需要Disable L
 输入参数  :
 输出参数  :
 返 回 值  : VOS_TRUE  需要Disable L
              VOS_FALSE 不需要Disable L
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月1日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2015年4月19日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_CombinedRegRsltSucc()
{

    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_CombinedRegSuccAdditionUpdateRslt(NAS_MML_GetAdditionUpdateRslt()))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
函 数 名  : NAS_MMC_IsNeedDisableL_RegRsltAdditionUpdateRslt
功能描述  : cs ps mode1,ims not available,注册结果additional update result IE指示
            "SMS only" or "CS Fallback not preferred" 是否需要disable lte
输入参数  : enAdditionUpdateRslt - addition update result信息
输出参数  : 无
返 回 值  : VOS_TRUE  - 需要Disable L
            VOS_FALSE - 不需要Disable L
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015年4月19日
  作    者   : z00161729
  修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_CombinedRegSuccAdditionUpdateRslt(
    NAS_MML_ADDITION_UPDATE_RSLT_INFO_ENUM_UINT8            enAdditionUpdateRslt
)
{
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;
    VOS_UINT8                                               ucAdditionUpdRsltSupportCsfbFlag;
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg;
    NAS_MML_VOICE_DOMAIN_PREFERENCE_ENUM_UINT8              enVoiceDomain;

    enLUeMode                        = NAS_MML_GetLteUeOperationMode();
    ucAdditionUpdRsltSupportCsfbFlag = VOS_TRUE;
    enLteCsServiceCfg                = NAS_MML_GetLteCsServiceCfg();
    enVoiceDomain                    = NAS_MML_GetVoiceDomainPreference();

    /* 不是CS/PS mode 1 */
    if (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 != enLUeMode)
    {
        return VOS_FALSE;
    }

    /* LTE only */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == NAS_MML_GetImsVoiceAvailFlg())
    {
        return VOS_FALSE;
    }

    if ((NAS_MML_ADDITION_UPDATE_RSLT_SMS_ONLY == enAdditionUpdateRslt)
     || (NAS_MML_ADDITION_UPDATE_RSLT_CSFB_NOT_PREFERRED == enAdditionUpdateRslt))
    {
        ucAdditionUpdRsltSupportCsfbFlag = VOS_FALSE;
    }

    /* Additional Update Result IE消息中指示SMS Only或CSFB Not Preferred
      24301_CR1289R1_(Rel-11)_C1-115106 rev of c1-114768 domain selection
      clarification  CS PS MODE1且IMS voice not available时，
      attach accept或tau accept消息中携带的Additional update result IE值为
      SMS ONLY或CSFB NOT PREFERRED时DISABLE LTE的条件增加UE是否配置了CSFB能力
      对应24301 5.5.1.3.4.2和5.5.3.3.4.2章节,该CR不用协议版本控制 */
    if ((VOS_FALSE == ucAdditionUpdRsltSupportCsfbFlag)
     && (NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == enLteCsServiceCfg)
     && (enVoiceDomain != NAS_MML_IMS_PS_VOICE_ONLY))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
函 数 名  : NAS_MMC_IsNeedDisableL_RegFailCause22AttmptCntMaxTimes
功能描述  : 注册被拒#22达最大次数是否需要disable lte
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_TRUE   - 需要Disable L
            VOS_FALSE - 不需要Disable L
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015年1月15日
  作    者   : z00161729
  修改内容   : AT&T 支持DAM特性修改
2.日    期   : 2015年4月20日
  作    者   : z00161729
  修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_RegFailCause22AttmptCntMaxTimes(VOS_VOID)
{
    VOS_UINT32                                              ulIsPlmnInSupportDamPlmnInfo;
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;
    NAS_MML_3GPP_REL_ENUM_UINT8                             enLteRelVersion;

    ulIsPlmnInSupportDamPlmnInfo = VOS_FALSE;
    enLUeMode                    = NAS_MML_GetLteUeOperationMode();
    enLteRelVersion              = NAS_MML_GetLte3gppRelVersion();

    /* 当前LTE单模,返回不需要disable lte */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    /* 不是CS/PS mode 1或IMS VOICE可用 */
    if ((VOS_TRUE                               == NAS_MML_GetImsVoiceAvailFlg())
     || (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1  != enLUeMode))
    {
        return VOS_FALSE;
    }

    /* ATT的卡如果注册被拒#22达最大次数的网络在支持DAM特性网络列表中则disable lte，
       否则无需disable lte;
       非ATT的卡注册被拒#22达最大次数如果协议版本小于R11需要disable lte，
       大于R11无需disable lte*/
    ulIsPlmnInSupportDamPlmnInfo = NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId());

    if (VOS_FALSE == NAS_MML_IsImsiHplmnInDamImsiPlmnList())
    {
        /* 24301_CR1485R2_(Rel-11)_C1-123380 对应24301 5.5.1.3.4.3和5.5.3.3.4.3章节描述:
           #22:The UE shall stop timer T3430 if still running. The tracking area updating
         attempt counter shall be set to 5. The UE shall start timer T3402, shall set
         the EPS update status to EU1 UPDATED, and shall enter state EMM-REGISTERED.ATTEMPTING-TO-UPDATE-MM.
         该CR受协议版本控制 */

        if (enLteRelVersion < NAS_MML_3GPP_REL_R11)
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }

    if (VOS_TRUE == ulIsPlmnInSupportDamPlmnInfo)
    {
        return VOS_TRUE;
    }

    if (enLteRelVersion < NAS_MML_3GPP_REL_R11)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
函 数 名  : NAS_MMC_IsNeedDisableL_CombinedAttRsltOnlyEpsSucc
功能描述  : 联合注册Combined attach successful for EPS services only或者
            Combined TAU successful for EPS services only，需要Disable L
输入参数  : enCsRegRsltCause
输出参数  :
返 回 值  : VOS_TRUE   需要Disable L
             VOS_FALSE 不需要Disable L
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2012年06月02日
  作    者   : s00217060
  修改内容   : 新生成函数
2.日    期   : 2015年1月5日
  作    者   : z00161729
  修改内容   : AT&T 支持DAM特性修改
3.日    期   : 2015年4月20日
  作    者   : z00161729
  修改内容   : 24301 R11 CR升级项目修改
4.日    期   : 2015年6月19日
  作    者   : z00161729
  修改内容   : 24008 23122 R11 CR升级项目修改

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_CombinedRegRsltOnlyEpsSucc(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause
)
{
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;

    enLUeMode        = NAS_MML_GetLteUeOperationMode();

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
    /* 不是CS/PS mode 1 */
    if (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 != enLUeMode)
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */
    {
        return VOS_FALSE;
    }


    /* LTE only */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    /* enCsRegRsltCause为#16,#17,#22,other cause && NAS_MMC_GetRegRsltAttemptCounter达到5次 */
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, begin */
    if ((NAS_MML_MAX_PS_REG_FAIL_CNT                == NAS_MMC_GetRegRsltAttemptCounter(NAS_MMC_GetRegRsltType()))
     && (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR != enCsRegRsltCause))
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, end */
    {
        /* 24301_CR1884R4_(Rel-11)_C1-140658-C1-140643-C1-140393-C1-140368-C1-140004-24301-b90-TA-IMSVoPS-EPS-only
          TAU ACCEPT，EPS ONLY成功，被拒原因值为16,17，CS/PS1，DIABLE LTE的条件增加
          persistent EPS bearer是否存在，对应24301 5.5.3.3.4.3章节:
      #16 and #17:a UE operating in CS/PS mode 1 of operation with "IMS voice not available"
          and with a persistent EPS bearer context shall wait until the radio bearer
          associated with the persistent EPS bearer context has been released. When
          the radio bearer associated with the persistent EPS bearer context has been
          released and the UE is registered for EPS services only, operating in CS/PS
          mode 1 of operation with "IMS voice not available", then the UE shall attempt
          to select GERAN or UTRAN radio access technology and proceed with appropriate
          MM or GMM specific procedures and disable the E-UTRA capability (see subclause 4.5).
          该CR受协议版本控制 */
        if (NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE == enCsRegRsltCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause16AttmptCntMaxTimes();
        }

        if (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == enCsRegRsltCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause17AttmptCntMaxTimes();
        }

        if (NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION == enCsRegRsltCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause22AttmptCntMaxTimes();
        }

        return VOS_TRUE;
    }

    /* 联合注册失败时,不会加到#18列表中,当other cause处理,需要5次之后Disable LTE,
       用原因值判断不准确,会错误地在被拒1次之后就Disable LTE */
    /* 在#18列表中 */
    if (VOS_TRUE == NAS_MML_IsPlmnIdInCsDomainUnAvailPlmnList(NAS_MML_GetCurrCampPlmnId()))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
函 数 名  : NAS_MMC_IsNeedDisableL_ServiceReqFailCause18CsDomainNotAvailable
功能描述  : 收到lmm的service result ind被拒原因值18是否需要disable lte
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_TRUE  - 需要Disable L
            VOS_FALSE - 不需要Disable L
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015年4月19日
  作    者   : z00161729
  修改内容   : 24301 R11 CR升级项目修改
2.日    期   : 2015年9月6日
  作    者   : z00359541
  修改内容   : DTS2015081407087: 接口调整，删除bitOpReqType项
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_ServiceReqFailCause18CsDomainNotAvailable(VOS_VOID)
{
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;
    NAS_MMC_REG_RSLT_CTX_STRU                              *pstRegRsltCtx = VOS_NULL_PTR;

    pstRegRsltCtx         = NAS_MMC_GetRegRsltCtxAddr();
    enLUeMode             = NAS_MML_GetLteUeOperationMode();

    /* 24301_CR1254R3_(Rel-11)_C1-115100 ESR被拒18原因值的处理更新
       The UE shall set the update status to U2 NOT UPDATED.If the UE is in CS/PS
       mode 1 of operation with "IMS voice not available" and the request was
       related to CS fallback, the UE shall attempt to select GERAN or UTRAN radio
       access technology rather than E-UTRAN for the selected PLMN or equivalent
       PLMN. The UE shall disable the E-UTRA capability (see subclause 4.5).
       If the UE is in the EMM-CONNECTED mode, the UE shall locally release the
       established NAS signalling connection and enter the EMM-IDLE mode before
       selecting GERAN or UTRAN radio access technology. 该CR不受协议版本控制 */

    /* 不是CS/PS mode 1 */
    if (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 != enLUeMode)
    {
        return VOS_FALSE;
    }

    /* LTE only */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    /* service 请求类型无效，不是csfb流程，返回VOS_FALSE */
    if ((VOS_FALSE == NAS_MML_IsCsfbServiceStatusExist())
     && (LMM_MMC_SERVICE_RESULT_IND == pstRegRsltCtx->enRegRsltType))
    {
        return VOS_FALSE;
    }


    /* 测试卡按协议disable lte，非测试卡为了提高用户体验，先不disable lte，电话结束
    后fast return回lte，lte会做联合注册，如果再次被#18拒绝再disable lte，多给LTE一次机会，
    参见DTS2015051901235问题单方案*/
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
函 数 名  : NAS_MMC_IsNeedDisableL_ServiceRsltFail
功能描述  : 收到lmm的service result ind消息判断是否需要disable lte
输入参数  : enRegRsltCause    - 注册被拒原因值
            ucIsReachMaxTimes - 是否达到最大次数标识
输出参数  :
返 回 值  : VOS_TRUE   需要Disable L
            VOS_FALSE 不需要Disable L
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015年1月5日
  作    者   : z00161729
  修改内容   : AT&T 支持DAM特性修改

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_ServiceRsltFail(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enRegRsltCause,
    VOS_UINT8                           ucIsReachMaxTimes
)
{
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;

    enLUeMode             = NAS_MML_GetLteUeOperationMode();

    /* 不是CS/PS mode 1 */
    if (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 != enLUeMode)
    {
        return VOS_FALSE;
    }

    /* LTE only */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    /* DAM特性不生效，则返回VOS_FALSE */
    if (VOS_FALSE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == ucIsReachMaxTimes)
    {
        return VOS_FALSE;
    }


    /* 失败原因值为#22达最大次数时需要disable lte */
    if (NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION == enRegRsltCause)
    {
        return VOS_TRUE;
    }

    /* 失败原因值不为24.301 5.6.1.5章节定义的原因值达最大次数时需要disable lte */
    if (NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE == enRegRsltCause)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedDisableL_EpsOnlyRegSucc
 功能描述  : 单域EPS成功，且PLMN在#18列表中时，需要 Disable L
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_FALSE:不需要 Disable L
              VOS_TRUE: 需要 Disable L
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年06月02日
   作    者   : s00217060
   修改内容   : 新生成函数
 2.日    期   : 2014年01月10日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseIII项目
 3.日    期   : 2015年6月19日
   作    者   : z00161729
   修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/

VOS_UINT32 NAS_MMC_IsNeedDisableL_EpsOnlyRegSucc()
{
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;
    VOS_UINT8                                               ucSimCsRegStatus;

    enLUeMode        = NAS_MML_GetLteUeOperationMode();
    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

    /* CS不允许注册或CS卡无效 */
    if ((VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
     || (VOS_FALSE == ucSimCsRegStatus))
    {
        return VOS_FALSE;
    }

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
    /* 不是CS/PS mode 1 */
    if (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 != enLUeMode)
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */
    {
        return VOS_FALSE;
    }


    /* LTE only */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    /* NAS_MMC_GetRegRsltAttemptCounter达到5次,表示之前联合注册仅EPS成功,T3402未超时 */
    if (NAS_MML_MAX_PS_REG_FAIL_CNT == NAS_MMC_GetRegRsltAttemptCounter(NAS_MMC_GetRegRsltType()))
    {
        return VOS_TRUE;
    }

    /* 在#18列表中 */
    if (VOS_TRUE == NAS_MML_IsPlmnIdInCsDomainUnAvailPlmnList(NAS_MML_GetCurrCampPlmnId()))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsCsPsMode1NeedPeriodSearchGU
 功能描述  : 判断是否需要周期性搜索GU网络
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要周期性搜索GU网络
             VOS_FALSE:不需要周期性搜索GU网络
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年06月20日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2014年01月10日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseIII项目
 3.日    期   : 2015年1月14日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改
 4.日    期   : 2015年4月20日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
 5.日    期   : 2015年6月19日
   作    者   : z00161729
   修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsCsPsMode1NeedPeriodSearchGU(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstRatOrder = VOS_NULL_PTR;
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;
    NAS_MML_ADDITION_UPDATE_RSLT_INFO_ENUM_UINT8            enAdditionUpdateRslt;

    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause;

    enPsRegCause            = NAS_MML_REG_FAIL_CAUSE_NULL;
    enCsRegCause            = NAS_MML_REG_FAIL_CAUSE_NULL;

    pstRatOrder          = NAS_MML_GetMsPrioRatList();
    enLUeMode            = NAS_MML_GetLteUeOperationMode();
    enAdditionUpdateRslt = NAS_MML_GetAdditionUpdateRslt();

    /* 当前LTE单模 */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(pstRatOrder))
    {
        return VOS_FALSE;
    }

    /* 当前接入技术为GU */
    if (NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType())
    {
        return VOS_FALSE;
    }

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
    /* 不是CS/PS mode 1或IMS VOICE可用 */
    if ((VOS_TRUE                               == NAS_MML_GetImsVoiceAvailFlg())
     || (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1  != enLUeMode))
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */
    {
        return VOS_FALSE;
    }

    /* Additional Update Result IE消息中指示SMS Only或CSFB Not Preferred */
    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_CombinedRegSuccAdditionUpdateRslt(enAdditionUpdateRslt))
    {
        return VOS_TRUE;
    }

    /* NAS_MMC_GetRegRsltAttemptCounter为5 */
    if (NAS_MML_MAX_PS_REG_FAIL_CNT == NAS_MMC_GetRegRsltAttemptCounter(NAS_MMC_GetRegRsltType()))
    {
        /* 获取之前注册失败的原因值 */
        NAS_MMC_GetDomainRegStatusInRegInfoList(NAS_MML_GetCurrCampPlmnId(),
                                                NAS_MML_NET_RAT_TYPE_LTE,
                                               &enCsRegCause,
                                               &enPsRegCause);

        if (NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION == enCsRegCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause22AttmptCntMaxTimes();
        }


        /* 24301_CR1884R4_(Rel-11)_C1-140658-C1-140643-C1-140393-C1-140368-C1-140004-24301-b90-TA-IMSVoPS-EPS-only
          TAU ACCEPT，EPS ONLY成功，被拒原因值为16,17，CS/PS1，DIABLE LTE的条件增加
          persistent EPS bearer是否存在，对应24301 5.5.3.3.4.3章节:
             #16 and #17:a UE operating in CS/PS mode 1 of operation with "IMS voice not available"
          and with a persistent EPS bearer context shall wait until the radio bearer
          associated with the persistent EPS bearer context has been released. When
          the radio bearer associated with the persistent EPS bearer context has been
          released and the UE is registered for EPS services only, operating in CS/PS
          mode 1 of operation with "IMS voice not available", then the UE shall attempt
          to select GERAN or UTRAN radio access technology and proceed with appropriate
          MM or GMM specific procedures and disable the E-UTRA capability (see subclause 4.5).
          该CR受协议版本控制 */
        if (NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE == enCsRegCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause16AttmptCntMaxTimes();
        }

        if (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == enCsRegCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause17AttmptCntMaxTimes();
        }

        return VOS_TRUE;
    }

    /* 在#18列表中 */
    if (VOS_TRUE == NAS_MML_IsPlmnIdInCsDomainUnAvailPlmnList(NAS_MML_GetCurrCampPlmnId()))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedDisableL_PsFailCause7PsServNotAllow
 功能描述  : PS(包含EPS和GPRS/PS)被原因值#7拒绝(包含Detach/Reg/Service)后
             判断是否需要disable LTE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_FALSE:不需要 Disable L
              VOS_TRUE: 需要 Disable L
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年07月02日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年09月12日
   作    者   : z00161729
   修改内容   : DTS2012082702662：disable或enable lte不再判断当前syscfg是否支持L
 3.日    期   : 2012年12月28日
   作    者   : s46746
   修改内容   : DSDA GUNAS C CORE项目，增加平台是否支持LTE判断
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_PsFailCause7PsServNotAllow(VOS_VOID)
{
    VOS_UINT8                                               ucSimCsRegStatus;

    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

    /* CS不允许注册或CS卡无效 */
    if ((VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
     || (VOS_FALSE == ucSimCsRegStatus))
    {
        return VOS_FALSE;
    }

    /* 如果已经disable 不需要再disable LTE */
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
    {
        return VOS_FALSE;
    }

    /* disable 或enable lte不再判断syscfg是否支持L */

    /* 平台不支持LTE时不需要disable LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* LTE only */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsEutranNotAllowedNeedDisableL
 功能描述  : PS(包含EPS和GPRS/PS)被原因值#7拒绝(包含Detach/Reg/Service)后
             判断是否需要disable LTE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_FALSE:不需要 Disable L
             VOS_TRUE: 需要 Disable L
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年04月22日
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsEutranNotAllowedNeedDisableL(VOS_VOID)
{

    /* 如果已经disable 不需要再disable LTE */
    if (VOS_TRUE == NAS_MML_IsLteCapabilityDisabled(NAS_MML_GetLteCapabilityStatus(), NAS_MML_GetDisableLteRoamFlg()))
    {
        return VOS_FALSE;
    }

    /* LTE only */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedDisableL_LteRejCause14
 功能描述  : LTE #14拒绝后，判断是否需要disable LTE
 输入参数  : 无
 输出参数  : 无
 返回值    : VOS_TRUE   需要Disable L
             VOS_FALSE  不需要Disable L
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月05日
    作    者   : h00285180
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_LteRejCause14(VOS_VOID)
{
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmn;

    if (VOS_FALSE == NAS_MML_GetLteRejCause14Flg())
    {
        /* 功能未开启 */
        return VOS_FALSE;
    }

    pstCurrPlmn = NAS_MML_GetCurrCampPlmnId();
    if (VOS_FALSE ==  NAS_MML_ComparePlmnIdWithHplmn(pstCurrPlmn))
    {
        /* VPLMN不执行#14拒绝优化 */
        return VOS_FALSE;
    }

    /* LTE only */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedEnableLte_CsRegFailCause2ImsiUnknownInHlr
 功能描述  : 判断Cs注册失败#2时，是否需要Enable Lte
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_FALSE:不需要 Enable Lte
              VOS_TRUE: 需要 Enable Lte
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年10月15日
   作    者   : s00217060
   修改内容   : 新生成函数
 2.日    期   : 2012年11月10日
   作    者   : s00217060
   修改内容   : DTS2012102902559：USIM卡时，才需要Enable Lte;SIM卡时不需要
 3.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_CsRegFailCause2ImsiUnknownInHlr(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* 在满足如下条件后，MMC需要重新enable LTE：
    (1)本地disable LTE的标记为真
    (2)Cs注册失败原因值#2，#3，#6
    (3)PS卡无效或USIM卡 */

    /* 获取LTE的使能状态 */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
    enSimType              = NAS_MML_GetSimType();

    /* 如果开机时已经根据en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config的配置禁止了LTE，则返回VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    /* 如果之前没有disable LTE,不需要enable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* PS卡无效或USIM卡,需要Enable Lte */
    if ( (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
      || (NAS_MML_SIM_TYPE_USIM == enSimType) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedEnableLte_CsRegFailCause256AuthRej
 功能描述  : 判断Cs注册失败时，是否需要Enable Lte
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_FALSE:不需要 Enable Lte
              VOS_TRUE: 需要 Enable Lte
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年10月15日
   作    者   : s00217060
   修改内容   : 新生成函数
 2.日    期   : 2012年11月10日
   作    者   : s00217060
   修改内容   : DTS2012102902559：USIM卡时，才需要Enable Lte;SIM卡时不需要
 3.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_CsRegFailCause256AuthRej(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* 在满足如下条件后，MMC需要重新enable LTE：
    (1)本地disable LTE的标记为真
    (2)Cs注册失败原因值#256
    (3)PS卡无效或USIM卡 */

    /* 获取LTE的使能状态 */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
    enSimType              = NAS_MML_GetSimType();

    /* 如果开机时已经根据en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config的配置禁止了LTE，则返回VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }


    /* 如果之前没有disable LTE,不需要enable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* PS卡无效或USIM卡,需要Enable Lte */
    if ( (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
      || (NAS_MML_SIM_TYPE_USIM == enSimType) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedEnableLte_PsRegFailCause256AuthRej
 功能描述  : 判断Ps注册失败时，是否需要Enable Lte
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_FALSE:不需要 Enable Lte
              VOS_TRUE: 需要 Enable Lte
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年10月15日
   作    者   : s00217060
   修改内容   : 新生成函数
 2.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
 3.日    期   : 2013年2月28日
   作    者   : w00176964
   修改内容   : DTS2014030100833:调整SIM卡disable和enable lTE逻辑
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_PsRegFailCause256AuthRej(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;

    /* 在满足如下条件后，MMC需要重新enable LTE：
    (1)本地disable LTE的标记为真
    (2)Cs或者Ps注册失败原因值#256 */

    /* 获取LTE的使能状态 */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    /* 如果开机时已经根据en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config的配置禁止了LTE，则返回VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    /* 是SIM卡,不需要Enable Lte */
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        return VOS_FALSE;
    }

    /* 如果之前已经disable LTE,需要enable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapabilityStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapabilityStatus))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedEnableLte_PsRegFailCause3IllegalMs
 功能描述  : 判断Ps注册失败时，是否需要Enable Lte
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_FALSE:不需要 Enable Lte
              VOS_TRUE: 需要 Enable Lte
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年10月15日
   作    者   : s00217060
   修改内容   : 新生成函数
 2.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
 3.日    期   : 2013年2月28日
   作    者   : w00176964
   修改内容   : DTS2014030100833:调整SIM卡disable和enable lTE逻辑
s*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_PsRegFailCause3IllegalMs(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;

    /* 在满足如下条件后，MMC需要重新enable LTE：
    (1)本地disable LTE的标记为真
    (2)Ps注册失败原因值#3 */

    /* 获取LTE的使能状态 */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    /* 如果开机时已经根据en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config的配置禁止了LTE，则返回VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    /* 是SIM卡,不需要Enable Lte */
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        return VOS_FALSE;
    }

    /* 如果之前已经disable LTE,需要enable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapabilityStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapabilityStatus))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedEnableLte_PsRegFailCause8GprsAndNonGprsNotAllow
 功能描述  : 判断Ps注册失败时，是否需要Enable Lte
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_FALSE:不需要 Enable Lte
              VOS_TRUE: 需要 Enable Lte
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年10月15日
   作    者   : s00217060
   修改内容   : 新生成函数
 2.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
 3.日    期   : 2013年2月28日
   作    者   : w00176964
   修改内容   : DTS2014030100833:调整SIM卡disable和enable lTE逻辑
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_PsRegFailCause8GprsAndNonGprsNotAllow(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;

    /* 在满足如下条件后，MMC需要重新enable LTE：
    (1)本地disable LTE的标记为真
    (2)Ps注册失败原因值#8 */

    /* 获取LTE的使能状态 */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    /* 如果开机时已经根据en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config的配置禁止了LTE，则返回VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    /* 是SIM卡,不需要Enable Lte */
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        return VOS_FALSE;
    }

    /* 如果之前已经disable LTE,需要enable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapabilityStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapabilityStatus))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedEnableLte_CmServiceRejectInd
 功能描述  : 收到CM_SERVICE_REJECT_IND指示的预处理
 输入参数  : ulEventType:消息类型
              pstMsg:CM_SERVICE_REJECT_IND消息
 输出参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要重新Enable Lte
              VOS_FALSE:不需要重新Enable Lte
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012年10月15日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2012年11月10日
    作    者   : s00217060
    修改内容   : DTS2012102902559：USIM卡时，才需要Enable Lte;SIM卡时不需要
  3.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 根据卡类型禁止网络制式
  4.日    期   : 2013年2月28日
    作    者   : w00176964
    修改内容   : DTS2014030100833:调整SIM卡disable和enable lTE逻辑
*****************************************************************************/
VOS_UINT32  NAS_MMC_IsNeedEnableLte_CmServiceRejectInd(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCmServiceRejCause
)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* 在满足如下条件后，MMC需要重新enable LTE：
    (1)本地disable LTE的标记为真
    (2)Cm Service被拒原因值#6
    (3)PS卡无效或USIM卡 */

    /* 获取LTE的使能状态 */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
    enSimType              = NAS_MML_GetSimType();

    /* 如果开机时已经根据en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config的配置禁止了LTE，则返回VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }


    /* 如果之前没有disable LTE,不需要enable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* 是SIM卡,不需要Enable Lte */
    if (NAS_MML_SIM_TYPE_SIM == enSimType)
    {
        return VOS_FALSE;
    }


    /* Cm Service被拒原因值#6，需要enable LTE */
    if (NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME == enCmServiceRejCause)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedEnableLte_MmAbortInd
 功能描述  : 判断收到MM_ABORT_IND消息是否需要Enable Lte
 输入参数  : ulEventType:消息类型
              pstMsg:MM_ABORT_IND消息
 输出参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要重新Enable Lte
              VOS_FALSE:不需要重新Enable Lte
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012年10月15日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2012年11月10日
    作    者   : s00217060
    修改内容   : DTS2012102902559：USIM卡时，才需要Enable Lte;SIM卡时不需要
  3.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 根据卡类型禁止网络制式
  4.日    期   : 2013年2月28日
    作    者   : w00176964
    修改内容   : DTS2014030100833:调整SIM卡disable和enable lTE逻辑
*****************************************************************************/
VOS_UINT32  NAS_MMC_IsNeedEnableLte_MmAbortInd(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enAbortCause
)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* 在满足如下条件后，MMC需要重新enable LTE：
    (1)本地disable LTE的标记为真
    (2)Mm Abort原因值#6
    (3)PS卡无效或USIM卡 */

    /* 获取LTE的使能状态 */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
    enSimType              = NAS_MML_GetSimType();

    /* 如果开机时已经根据en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config的配置禁止了LTE，则返回VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    /* 如果之前未disable LTE，不需要enable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* 是SIM卡,不需要Enable Lte */
    if (NAS_MML_SIM_TYPE_SIM == enSimType)
    {
        return VOS_FALSE;
    }


    /* Mm Abort原因值#6，需要enable LTE */
    if (NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME == enAbortCause)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedEnableLte_EnableLteTimerExp
 功能描述  : 判断收到TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER消息是否需要Enable Lte
 输入参数  : VOID
 输出参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要重新Enable Lte
             VOS_FALSE:不需要重新Enable Lte
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012年12月15日
    作    者   : L65478
    修改内容   : 新生成函数
  2.日    期   : 2013年6月3日
    作    者   : z00161729
    修改内容   : SVLTE 修改
  3.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 根据卡类型禁止网络制式
  4.日    期   : 2014年01月10日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseIII项目
  5.日    期   : 2015年01月5日
    作    者   : h00285180
    修改内容   : LTE #14拒绝优化:DTS2015010401946

  6.日    期   : 2015年4月18日
    作    者   : w00167002
    修改内容   : DTS2015032709270:在拒绝15触发的DISABLE LTE时，也会启动ENABLE定时器。

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsNeedEnableLte_EnableLteTimerExp(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32                  enDisableLteReason;

    enDisableLteReason = NAS_MML_GetDisableLteReason();

    /* 在满足如下条件后，MMC需要重新enable LTE：
    (1)本地disable LTE的标记为真
    (2)disable LTE原因值EM或VOICE NOT SUPPORT
    (3)PS卡无效或USIM卡 */

    /* 获取LTE的使能状态 */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
    enSimType              = NAS_MML_GetSimType();

    /* 如果开机时已经根据en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config的配置禁止了LTE，则返回VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    /* 如果之前未disable LTE，不需要enable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* PS卡有效且是SIM卡,不需要Enable Lte */
    if ( (VOS_TRUE == NAS_MML_GetSimPsRegStatus())
      && (NAS_MML_SIM_TYPE_SIM == enSimType) )
    {
        return VOS_FALSE;
    }

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-18, begin */
    /* disable LTE原因为EMC或IMS VOICE不可用或LTE #14拒绝优化，需要enable LTE */
    if ((MMC_LMM_DISABLE_LTE_REASON_EMERGENCY_CALL          == enDisableLteReason)
     || (MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE == enDisableLteReason)
     || (MMC_LMM_DISABLE_LTE_REASON_LTE_REJ_CAUSE_14        == enDisableLteReason)
     || (MMC_LMM_DISABLE_LTE_REASON_LMM_NOTIFY_EUTRAN_NOT_ALLOW == enDisableLteReason))
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-18, end */
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_SaveEpsAttachAttemptCounter
 功能描述  : 保持EPS Attach结果消息中的Attempt Counter
 输入参数  : pstEpsAttachIndMsg:Attach结果消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年07月05日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SaveEpsAttachAttemptCounter(
    LMM_MMC_ATTACH_IND_STRU            *pstEpsAttachIndMsg
)
{
    NAS_MMC_REG_RSLT_CTX_STRU          *pstRegRsltCtx = VOS_NULL_PTR;
    pstRegRsltCtx   = NAS_MMC_GetRegRsltCtxAddr();

    /* 与LMM模块确认，如果Attach结果为CN REJ、MT_DETACH_FAILURE、MO_DETACH_FAILURE
       或者成功且携带了Cn Rslt，则如果消息中携带了ulAttemptCount更新，否则清除
       如果是其它结果，则如果消息中携带了ulAttemptCount更新，否则不更新 */
    if ((MMC_LMM_ATT_RSLT_CN_REJ == pstEpsAttachIndMsg->ulAttachRslt)
     || (MMC_LMM_ATT_RSLT_MT_DETACH_FAILURE == pstEpsAttachIndMsg->ulAttachRslt)
     || (MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE == pstEpsAttachIndMsg->ulAttachRslt)
     || ((MMC_LMM_ATT_RSLT_SUCCESS == pstEpsAttachIndMsg->ulAttachRslt)
      && (VOS_TRUE == pstEpsAttachIndMsg->bitOpCnRslt)))
    {
        if (VOS_TRUE == pstEpsAttachIndMsg->bitOpAtmpCnt)
        {
            pstRegRsltCtx->ucEpsAttemptCounter = (VOS_UINT8)pstEpsAttachIndMsg->ulAttemptCount;
        }
        else
        {
            pstRegRsltCtx->ucEpsAttemptCounter = 0x0;
        }
    }
    else
    {
        if (VOS_TRUE == pstEpsAttachIndMsg->bitOpAtmpCnt)
        {
            pstRegRsltCtx->ucEpsAttemptCounter = (VOS_UINT8)pstEpsAttachIndMsg->ulAttemptCount;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SaveEpsTauAttemptCounter
 功能描述  : 保持EPS TAU结果消息中的Attempt Counter
 输入参数  : pstEpsTauIndMsg:TAU结果消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年07月05日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SaveEpsTauAttemptCounter(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstEpsTauIndMsg
)
{
    NAS_MMC_REG_RSLT_CTX_STRU          *pstRegRsltCtx = VOS_NULL_PTR;
    pstRegRsltCtx   = NAS_MMC_GetRegRsltCtxAddr();

    /* 与LMM模块确认，如果TAU结果为CN REJ、MT_DETACH_FAILURE、MO_DETACH_FAILURE
       或者成功且携带了Cn Rslt，则如果消息中携带了ulAttemptCount更新，否则清除
       如果是其它结果，则如果消息中携带了ulAttemptCount更新，否则不更新 */
    if ((MMC_LMM_TAU_RSLT_CN_REJ == pstEpsTauIndMsg->ulTauRst)
     || (MMC_LMM_TAU_RSLT_MT_DETACH_FAILURE == pstEpsTauIndMsg->ulTauRst)
     || (MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE == pstEpsTauIndMsg->ulTauRst)
     || ((MMC_LMM_TAU_RSLT_SUCCESS == pstEpsTauIndMsg->ulTauRst)
      && (VOS_TRUE == pstEpsTauIndMsg->bitOpCnRst)))
    {
        if (VOS_TRUE == pstEpsTauIndMsg->bitOpAtmpCnt)
        {
            pstRegRsltCtx->ucEpsAttemptCounter = (VOS_UINT8)pstEpsTauIndMsg->ulAttemptCount;
        }
        else
        {
            pstRegRsltCtx->ucEpsAttemptCounter = 0x0;
        }
    }
    else
    {
        if (VOS_TRUE == pstEpsTauIndMsg->bitOpAtmpCnt)
        {
            pstRegRsltCtx->ucEpsAttemptCounter = (VOS_UINT8)pstEpsTauIndMsg->ulAttemptCount;
        }
    }

    return;
}

/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-13, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcEmcPdpRelease_DetachPs
 功能描述  : 根据紧急PDN连接状态处理PS的DETACH
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月17日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ProcEmcPdpRelease_DetachPs( VOS_VOID )
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU           stSndEquPlmnInfo;
    VOS_UINT8                           ucEmcPdpStatusFlg;

    /* 协议描述如下:
        1.if there is no PDN connection for emergency bearer services established,
        the UE shall remove from the list any PLMN code that is already in the list of "forbidden PLMNs"
        or in the list of "forbidden PLMNs for GPRS service".
        If there is a PDN connection for emergency bearer services established,
        the UE shall remove from the list of equivalent PLMNs any PLMN code present in the list of forbidden PLMNs
        or in the list of "forbidden PLMNs for GPRS service" when the PDN connection for emergency bearer services is released.

        2.if the attach procedure is not for emergency bearer services,
        the UE shall remove from the list any PLMN code that is already in the list of "forbidden PLMNs"
        or in the list of "forbidden PLMNs for GPRS service".

        3.The UE shall delete the stored list if the USIM is removed
        or when the UE attached for emergency bearer services enters the state EMM-DEREGISTERED.
    */

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    ucEmcPdpStatusFlg   = NAS_MML_GetEmcPdpStatusFlg();

    /* 紧急PDN不存在时，不需要处理；紧急PDN存在时，清除标志，给LMM发送EPLMN通知 */
    if (VOS_TRUE == ucEmcPdpStatusFlg)
    {
        /* 清除紧急PDN连接标志 */
        NAS_MML_SetEmcPdpStatusFlg(VOS_FALSE);


        /* 卡不存在时，不需要发送EPLMN;卡存在时，给LMM发送EPLMN通知，删除Forb Plmn */
        if (VOS_TRUE == NAS_MML_GetSimPresentStatus())
        {
            pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
            PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(NAS_MML_EQUPLMN_INFO_STRU));
            NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
            NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);

            NAS_MMC_SndOmEquPlmn();
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedSndEplmn_LmmDetachCnf
 功能描述  : 判断收到LMM的DetachCnf时需要不需要给LMM发送EPLMN
 输入参数  : pstLmmDetachCnf:LMM的DetachCnf消息
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要发送，VOS_FALSE:不需要发送
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月25日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedSndEplmn_LmmDetachCnf(
    LMM_MMC_DETACH_CNF_STRU            *pstLmmDetachCnf
)
{
    VOS_UINT32                          ulRst;

    ulRst   = VOS_FALSE;

    /* 如果发起的是PS或CS+PS的detach，detach不为failure时，
        则认为紧急PDN连接释放，清除紧急PDN连接标记，
        同时通知LMM当前EPLMN列表信息，删除forbidden plmn列表
    */

    switch (pstLmmDetachCnf->ulReqType)
    {
        case MMC_LMM_MO_DET_PS_ONLY:
        case MMC_LMM_MO_DET_CS_PS:

            if ( (MMC_LMM_DETACH_RSLT_SUCCESS       == pstLmmDetachCnf->ulDetachRslt)
              || (MMC_LMM_DETACH_RSLT_ACCESS_BARED  == pstLmmDetachCnf->ulDetachRslt)
              || (MMC_LMM_DETACH_RSLT_AUTH_REJ      == pstLmmDetachCnf->ulDetachRslt) )
            {
                ulRst = VOS_TRUE;
            }

            break;

        default:

            ulRst   = VOS_FALSE;

            break;
    }

    return ulRst;
}

/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-13, end */

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertLmmDetachIndTypeToMmcType
 功能描述  : 将LMM detach ind转换成mmc内部定义的结构
 输入参数  : enCnReqType - lmm格式的detach type
 输出参数  : penDetachType  - mmc格式的detach type

 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月14日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertLmmDetachIndTypeToMmcType(
    MMC_LMM_MT_DETACH_TYPE_ENUM_UINT32                      enCnReqType,
    NAS_MSCC_PIF_NETWORK_DETACH_TYPE_ENUM_UINT8                 *penDetachType
)
{
    switch ( enCnReqType )
    {
        case MMC_LMM_MT_DET_REATTACH_REQUIRED:
            *penDetachType = NAS_MSCC_PIF_NETWORK_DETACH_TYPE_REATTACH;
            break;

        case MMC_LMM_MT_DET_REATTACH_NOT_REQUIRED:
            *penDetachType = NAS_MSCC_PIF_NETWORK_DETACH_TYPE_NOATTACH;
            break;

        case MMC_LMM_MT_DET_IMSI:
            *penDetachType = NAS_MSCC_PIF_NETWORK_DETACH_TYPE_IMSI;
            break;

        default:
            *penDetachType = NAS_MSCC_PIF_NETWORK_DETACH_TYPE_BUTT;
            break;
    }
}

#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_IsFailCauseInCustomizedForbLaCfgList
 功能描述  : CS注册失败时是否触发搜网
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月23日
    作    者   : z00359541
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsFailCauseInCustomizedForbLaCfgList(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enCause
)
{
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU   *pstForbLaWithValidPeriodCfg = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstForbLaWithValidPeriodCfg = NAS_MML_GetForbLaWithValidPeriodCfg();

    /* 测试卡时，按协议要求，不需要触发搜网 */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    /* 原因值是否在NV定制的原因值列表中 */
    for (i = 0; i < pstForbLaWithValidPeriodCfg->ulSupportForbLaWithValidPeriodNum; i++)
    {
        if (enCause == pstForbLaWithValidPeriodCfg->astForbLaWithValidPeriodCfgList[i].usRegFailCause)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedLauRejTrigPlmnSearch
 功能描述  : LAU被#12拒绝时是否触发搜网
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月23日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_IsNeedLauRejTrigPlmnSearch(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enCause
)
{
    NAS_MML_LAU_REJ_TRIG_PLMN_SEARCH_STRU                  *pstLauRejCfg    = VOS_NULL_PTR;
    VOS_UINT8                                               ucCmSrvExistFlg;
    VOS_UINT8                                               ucIsCurCauseInNvCauseList;
    VOS_UINT32                                              i;

    pstLauRejCfg    = NAS_MML_GetLauRejTrigPlmnSearchCfg();
    ucCmSrvExistFlg = NAS_MML_GetCmServiceSetupFlg();
    ucIsCurCauseInNvCauseList   = VOS_FALSE;

    /* 测试卡时，按协议要求，不需要触发搜网 */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    /* 原因值是否在NV定制的原因值列表中 */
    for (i=0; i < pstLauRejCfg->ucCmSrvTrigPlmnSearchCauseNum; i++)
    {
        if (enCause == pstLauRejCfg->aucCmSrvTrigPlmnSearchCause[i])
        {
            ucIsCurCauseInNvCauseList   = VOS_TRUE;
            break;
        }
    }

    /* 有业务时，并且NV打开，需要触发搜网 */
    if ((VOS_TRUE == pstLauRejCfg->ucCmSrvExistTrigPlmnSearch)
     && (VOS_TRUE == ucCmSrvExistFlg)
     && (VOS_TRUE == ucIsCurCauseInNvCauseList))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ConverGmmActionTypeToMml
 功能描述  : GMM的action 类型转换为MML的
 输入参数  : enGmmActionType:GMM的action type
 输出参数  : penProcType:MML中的注册类型
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月1日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年3月30日
   作    者   : w00176964
   修改内容   : DTS2013030802929,周期性RAU需要通知LMM
*****************************************************************************/
VOS_VOID    NAS_MMC_ConverGmmActionTypeToMml(
    GMM_MMC_ACTION_TYPE_ENUM_U32        enGmmActionType,
    NAS_MML_PROC_TYPE_ENUM_U32         *penProcType
)
{
    switch (enGmmActionType)
    {
        case GMM_MMC_ACTION_RAU:

            *penProcType = NAS_MML_PROC_RAU;
            break;

        case GMM_MMC_ACTION_ATTACH:

            *penProcType = NAS_MML_PROC_ATTACH;
            break;

        case GMM_MMC_ACTION_COMBINED_RAU:

            *penProcType = NAS_MML_PROC_COMBINED_RAU;
            break;

        case GMM_MMC_ACTION_COMBINED_ATTACH:

            *penProcType = NAS_MML_PROC_COMBINED_ATTACH;
            break;

        case GMM_MMC_ACTION_PERIODC_RAU:

            *penProcType = NAS_MML_PROC_PERIODC_RAU;
            break;

        default:

            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ConverGmmActionTypeToMml: Invalid action type!");
            *penProcType = NAS_MML_PROC_BUTT;
            break;
    }
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetSingleDomainFailAction
 功能描述  : 获取对应注册原因值运营商定制的动作
 输入参数  :
            enDomain,注册的域
            enFailCause,失败原因值

 输出参数  : penAction:定制的动作
 返 回 值  : VOS_UINT32 VOS_TRUE:获取成功  VOS_FALSE:获取失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月11日
   作    者   : w00166186
   修改内容   : AT&T&DCM新生成函数
2.日    期   : 2014年8月19日
  作    者   : w00167002
  修改内容   : DTS2014081905808:在配置PS注册拒绝14时候，若当前在HOME PLMN上，则可能
               触发循环乒乓，修改为增加ACTION动作:在漫游网络上触发选网，在HOME网络上
               不生效，按现有流程进行处理。
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8    NAS_MMC_GetSingleDomainFailAction(
    NAS_MML_REG_DOMAIN_ENUM_UINT8           enDomain,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enFailCause
)
{
    VOS_UINT8                                           i;
    NAS_MML_SINGLE_DOMAIN_FAIL_ACTION_LIST_CTX_STRU*    pstSingleDomainFailActionCtx;

    pstSingleDomainFailActionCtx = NAS_MML_GetSingleDomainFailActionCtx();

    /* 定制NV没有激活 */
    if (VOS_FALSE == pstSingleDomainFailActionCtx->ucActiveFlag)
    {
        return NAS_MMC_ADDITIONAL_ACTION_BUTT;
    }

    for (i = 0; i < pstSingleDomainFailActionCtx->ucCount; i++)
    {
        /* 对应的注册域和注册原因值在定制列表中 */
        if ((enDomain == pstSingleDomainFailActionCtx->astSingleDomainFailActionList[i].enDomain)
         && (enFailCause == pstSingleDomainFailActionCtx->astSingleDomainFailActionList[i].enRegCause))
        {
            switch (pstSingleDomainFailActionCtx->astSingleDomainFailActionList[i].enAction)
            {
                case NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_PLMN_SELECTION:
                     return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

                case NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_NORMAL_CAMP_ON:
                     return NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

                case NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_OPTIONAL_PLMN_SELECTION:
                     return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

                case NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_LIMITED_CAMP_ON:
                     return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

                case NAS_MML_SINGLE_DOMAIN_ROAMING_REG_FAIL_ACTION_PLMN_SELECTION:

                     /* 在漫游网络上则发起搜网，否则按原有流程处理 */
                     if ( VOS_TRUE == NAS_MMC_IsRoam() )
                     {
                         return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
                     }

                     return NAS_MMC_ADDITIONAL_ACTION_BUTT;

                default:
                     return NAS_MMC_ADDITIONAL_ACTION_BUTT;
            }
        }
    }

    return NAS_MMC_ADDITIONAL_ACTION_BUTT;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsCurrPlmnInEplmnList
 功能描述  : 判断当前驻留的PLMN是否是EPLMN
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_TRUE:   是EPLMN
             VOS_FALSE:  不是EPLMN

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月15日
    作    者   : l00208543
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsCurrPlmnInEplmnList(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MML_PLMN_ID_STRU               *pstCurplmn   =  VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnList =  VOS_NULL_PTR;

    i            = 0;
    pstCurplmn   = NAS_MML_GetCurrCampPlmnId();
    pstEplmnList = NAS_MML_GetEquPlmnList();

    if ((VOS_FALSE == NAS_MML_GetEplmnValidFlg())
     || (0         == pstEplmnList->ucEquPlmnNum))
    {
        return VOS_FALSE;
    }

    for ( i = 0 ; i < pstEplmnList->ucEquPlmnNum; i++ )
    {
        if ( ( pstCurplmn->ulMcc == pstEplmnList->astEquPlmnAddr[i].ulMcc)
          && ( pstCurplmn->ulMnc == pstEplmnList->astEquPlmnAddr[i].ulMnc))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsAccBarPlmnSearch
 功能描述  : 接入禁止后是否需要触发OPTIONAL_PLMN_SELECTION
             只有特性开关打开，且驻留的网络非HPLMN/RPLMN时需要搜网
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_TRUE:   需要plmn搜网
             VOS_FALSE:  不需要plmn搜网

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月15日
    作    者   : s00190137
    修改内容   : 新生成函数
  2.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 根据卡类型禁止网络制式
  3.日    期   : 2013年11月30日
    作    者   : z00161729
    修改内容   : DTS2013112809149:9230 nv项设置禁止接入技术为w和g，手动搜网模式驻留g的23002成功，syscfg设置w only，anycell驻留24005，会反复触发w下anycell搜网
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsAccBarPlmnSearch(VOS_VOID)
{
    VOS_UINT32                          ulIsRoam;
    VOS_UINT32                          ulIsAccBarPlmnSearchFlg;
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;
    NAS_MMC_TIMER_STATUS_ENUM_U8        enAvailableTimerStatus;
    NAS_MML_PLMN_ID_STRU                stRPlmnId;
    NAS_MML_PLMN_ID_STRU               *pstCurplmn =  VOS_NULL_PTR;

    /* 获取NV特性开关 */
    ulIsAccBarPlmnSearchFlg = (VOS_UINT32)NAS_MML_GetSupportAccBarPlmnSearchFlg();

    /* 获取漫游状态 */
    ulIsRoam                = NAS_MMC_IsRoam();

    /* 获取当前Camp的网络*/
    pstCurplmn              = NAS_MML_GetCurrCampPlmnId();

    /* 获取当前状态机Id*/
    enFsmId                 = NAS_MMC_GetCurrFsmId();

    /* 查询MMC_AVAILABLE_TIMER定时器状态*/
    enAvailableTimerStatus  = NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER);

    if (VOS_FALSE == NAS_MMC_IsNeedPlmnSearch_RegLocalFailCause())
    {
        return VOS_FALSE;
    }


    /* 增加测试卡保护，测试卡时不修改，直接返回 */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_IsAccBarPlmnSearch(): The sim is Test card!");
        return VOS_FALSE;
    }

    /* 特性开关未打开或非漫游状态，接入禁止不需要搜网 */
    if ((VOS_FALSE == ulIsAccBarPlmnSearchFlg)
     || (VOS_FALSE == ulIsRoam))
    {
        return VOS_FALSE;
    }

    /* 在L1状态机下且available定时器在运行时，不需要再触发搜网 */
    if ((NAS_MMC_FSM_L1_MAIN == enFsmId)
     && (NAS_MMC_TIMER_STATUS_RUNING == enAvailableTimerStatus))
    {
        return VOS_FALSE;
    }

    /* 当前Rplmn不存在时，需要搜网 */
    if (VOS_FALSE == NAS_MML_GetRPlmn(NAS_MML_GetLastRplmnRat(), &stRPlmnId))
    {
        return VOS_TRUE;
    }

    /* 如果当前网络为EPLMN则不需要搜网 */
    if (VOS_TRUE == NAS_MMC_IsCurrPlmnInEplmnList())
    {
        return VOS_FALSE;
    }

    /* 驻留禁止网络为RPLMN，则不需要搜网*/
    /* 这里还是需要判断RPLMN，防止RPLMN有效EPLMN的场景下漏判 */
    if ( VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurplmn, &stRPlmnId))
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}

/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-30, begin */
#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegFailCause417ECallInactive
 功能描述  : CS的cause为ecall inactive状态的处理
 输入参数  :
             VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年4月30日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause417ECallInactive(VOS_VOID)
{
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
}

#endif
/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-30, end */

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

