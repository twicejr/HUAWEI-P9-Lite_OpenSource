
#ifndef _NAS_MMC_PROC_REG_RSLT_H
#define _NAS_MMC_PROC_REG_RSLT_H

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "MmcGmmInterface.h"
#include "MmcMmInterface.h"
#include "Nasrrcinterface.h"
#include "NasMmcCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


enum NAS_MMC_REG_RSLT_TYPE_ENUM
{
    MM_MMC_CS_REG_RESULT_IND            = 0X01,             /* MM通知MMC当前CS域注册结果 */
    GMM_MMC_PS_REG_RESULT_IND           = 0X02,             /* GMM通知MMC当前PS域注册结果 */
    GMM_MMC_PS_SERVICE_RESULT_IND       = 0X03,             /* GMM通知MMC当前PS域服务注册结果 */
    GMM_MMC_PS_NETWORK_DETACH_IND       = 0X04,             /* GMM通知MMC当前PS域被网侧去注册结果 */

    LMM_MMC_ATTACH_IND                  = 0X50,             /* LMM通知MMC当前ATTACH注册结果 */
    LMM_MMC_TAU_RESULT_IND              = 0X51,             /* LMM通知MMC当前TAU注册结果 */
    LMM_MMC_DETACH_IND                  = 0X52,             /* LMM通知MMC当前DETACH注册结果 */
    LMM_MMC_SERVICE_RESULT_IND          = 0X53,             /* LMM通知MMC当前SERVICE注册结果 */
    NAS_MMC_REG_RSULT_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


typedef NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 (*NAS_MMC_PROC_REG_FAIL_FUNC_PTR)(VOS_VOID);


typedef struct
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                  enRegCause;
    NAS_MMC_PROC_REG_FAIL_FUNC_PTR                      pRegFailProcFunc;
}NAS_MMC_REG_FAIL_PROC_ENTITY;


typedef VOS_VOID (*NAS_MMC_PROC_COMBINED_EPS_REG_FAIL_FUNC_PTR)(NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 *penPsRegAdditionalAction, NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 *penCsRegAdditionalAction);


typedef struct
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                  enRegCause;
    NAS_MMC_PROC_COMBINED_EPS_REG_FAIL_FUNC_PTR         pCombinedEpsRegFailProcFunc;
}NAS_MMC_COMBINED_EPS_REG_REJ_PROC_ENTITY;


typedef VOS_VOID (*NAS_MMC_PROC_EPS_DETACH_CAUSE_FUNC_PTR)(NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 *penPsRegAdditionalAction,
                                                           NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 *penCsRegAdditionalAction
                                                           );


typedef struct
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enRegCause;
    NAS_MMC_PROC_EPS_DETACH_CAUSE_FUNC_PTR                  pEpsDetachCauseProcFunc;
}NAS_MMC_EPS_DETACH_CAUSE_PROC_ENTITY;



typedef struct
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                 enAdditionalAction;
    VOS_UINT8                                            ucPriority;
}NAS_MMC_ADDITIONAL_ACTION_PRIORITY_PAIR;



typedef struct
{
    MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8                   enLmmAttachClReqStatus;
    VOS_UINT8                                            ucPriority;
}NAS_MMC_LMM_ATTACH_CL_REG_STATUS_PRIORITY_PAIR;


typedef union
{
    /* MM向MMC上报的CS注册结果消息 */
    MMMMC_CS_REG_RESULT_IND_STRU                           *pstCsRegRsltInd;

    /* GMM向MMC上报的PS注册结果消息 */
    GMMMMC_PS_REG_RESULT_IND_STRU                          *pstPsRegRsltInd;

    /* GMM向MMC上报的PS服务域结果消息 */
    GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU                 *pstServiceRsltIndMsg;

    /* GMM向MMC上报的PS去注册结果消息 */
    MMCGMM_NETWORK_DETACH_IND_STRU                         *pstDetachIndMsg;

#if (FEATURE_ON == FEATURE_LTE)
    /* LMM向MMC上报的ATTACH注册结果消息 */
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg;

    /* LMM向MMC上报的TAU注册结果消息 */
    LMM_MMC_TAU_RESULT_IND_STRU                            *pstLmmTauIndMsg;

    /* LMM向MMC上报的DETACH注册结果消息 */
    LMM_MMC_DETACH_IND_STRU                                *pstLmmDetachMsg;

    /* LMM向MMC上报的SERVICE注册结果消息 */
    LMM_MMC_SERVICE_RESULT_IND_STRU                        *pstLmmServiceIndMsg;
#endif
}NAS_MMC_REG_RSLT_CTX_UNION;


typedef struct
{
    /* 注册结果消息类型 */
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType;

    VOS_UINT8                           ucEpsAttemptCounter;

    VOS_UINT8                           ucIsLteRegTypeEpsOnly;                   /* 记录lte发起注册类型是否为eps only,1:是；0:不是*/
    VOS_UINT8                           aucReserve;

    /* 注册结果消息结构体 */
    NAS_MMC_REG_RSLT_CTX_UNION          unRegRsltCtx;
}NAS_MMC_REG_RSLT_CTX_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
NAS_MMC_REG_RSLT_CTX_STRU* NAS_MMC_GetRegRsltCtxAddr(VOS_VOID);
VOS_VOID  NAS_MMC_SaveRegRsltCtx(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType,
    VOS_VOID                           *pRegRsltIndMsg
);
NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8 NAS_MMC_GetRegRsltType(VOS_VOID);
VOS_UINT32 NAS_MMC_GetRegRsltAttemptCounter(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType
);

VOS_VOID  NAS_MML_SetRegRsltCtxUnion(
    NAS_MMC_REG_RSLT_CTX_UNION         *punRegRsltCtx
);





NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause2ImsiUnknownInHlr(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause3IllegalMs(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause6IllegalMe(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause11PlmnNotAllow(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause12LaNotAllow(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause13RoamNotAllow(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause15NoSuitableCell(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause17NetWorkFailure(VOS_VOID);


NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause95SemanticallyIncorrectMsg(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause96InvalidMandatoryInf(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause97MsgNonExistNotImplement(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause99IeNonExistNotImplement(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause111ProtocolError(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause256AuthRej(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause257AccessBarrd(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause301TimerTimeOut(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause302RrConnEstFail(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause303RrConnFail(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause401OtherCause(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause402MsCfgDomainNotSupport(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause403ForbiddenPlmn(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause404ForbiddenLaForRegPrvsSvs(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause405ForbiddenLaForRoam(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause407SimInvalid(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause408NetDetachImsi(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause409ServingCellDomainNotSupport(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCauseAbnormalCause(
    VOS_UINT16                          usCause,
    VOS_UINT32                          ulAttemptCnt
);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailAttemptCounterMaxTimes(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailAttemptCounterLessThanMaxTimes(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause17AttemptCounterMaxTimes(VOS_VOID);


NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause416DealyCsInTransLau(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause418T3212Running(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause419InterRatChangeSucc(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause421HoWaitSysinfoTimeout(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause3IllegalMs(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause6IllegalMe(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause7GprsServNotAllow(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause8GprsAndNonGprsNotAllow(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause9MsIdNotDerived(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause10ImplicitDetached(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause11PlmnNotAllow(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause12LaNotAllow(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause406ForbiddenPlmnForGprs(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause13RoamNotAllow(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause14GprsNotAllowInThisPlmn(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause15NoSuitableCell(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause40NoPdpContextActived(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause95SemanticallyIncorrectMsg(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause96InvalidMandatoryInf(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause97MsgNonExistNotImplement(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause99IeNonExistNotImplement(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause111ProtocolError(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause256AuthRej(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause257AccessBarrd(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause301TimerTimeOut(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause302RrConnEstFail(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause303RrConnFail(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause401OtherCause(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause402MsCfgDomainNotSupport(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause403ForbiddenPlmn(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause404ForbiddenLaForRegPrvsSvs(VOS_VOID);

VOS_UINT32 NAS_MMC_IsNeedPlmnSearch_RegLocalFailCause( VOS_VOID );


NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause405ForbiddenLaForRoam(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause407SimInvalid(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause408NetDetachImsi(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause409ServingCellDomainNotSupport(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause419InterRatChangeSucc(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCauseAbnormalCause(
    VOS_UINT16                          usCause,
    VOS_UINT32                          ulAttemptCnt
);

#if   (FEATURE_ON == FEATURE_LTE)

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause2ImsiUnknownInHss(VOS_VOID);

VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause3IllegalMs(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);

VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause6IllegalMe(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);

VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause7EpsServNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);

VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause8GprsAndNonGprsNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);

VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause9MsidCannotDerivedByNw(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);

VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause10ImplicitlyDetached(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);

VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause11PlmnNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);

VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause12TaNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause406ForbiddenPlmnForGprs(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause13RoamNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);

VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause14GprsNotAllowInThisPlmn(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);

VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause15NoSuitableCell(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause19EsmFailure(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);

VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause35ReqServOptNotAuthorizedInThisPlmn(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause16MscNotReachable(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause18CsDomainNotAvailable(VOS_VOID);


NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause22Congestion(VOS_VOID);


NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause17NetworkFailure(VOS_VOID);


VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause257AccessBarrd(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailAttemptCouterLessThanMaxTimes(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction
);
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause256AuthRej(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause301TimerTimeOut(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction
);
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause403ForbiddenPlmn(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);

VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause404ForbiddenTaForRegPrvsSvs(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause405ForbiddenLaForRoam(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);


#endif

VOS_VOID NAS_MMC_ProcCsRegFailForbLaWithValidPeriod(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enRegFailCause,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8    enAction
);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFail(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType,
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRsltInd
);


VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause401OtherCause(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFail(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType,
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRsltInd
);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsServiceRegFail(
    GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU                 *pstServiceRsltInd
);


NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcGmmNetworkDetachInd(
    MMCGMM_NETWORK_DETACH_IND_STRU     *pstDetachMsg
);

#if   (FEATURE_ON == FEATURE_LTE)
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause11PlmnNotAllow(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause12TaNotAllow(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause406ForbiddenPlmnForGprs(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause13RoamNotAllow(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause14GprsNotAllowInThisPlmn(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause15NoSuitableCell(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause25NotAuthorizedForThisCSG(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause3IllegalMs(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause6IllegalMe(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause7EpsServNotAllow(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause8GprsAndNonGprsNotAllow(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause257AccessBarrd(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause256AuthRej(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause301TimerTimeOut(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause401OtherCause(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause405ForbiddenLaForRoam(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause404ForbiddenTaForRegPrvsSvs(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause403ForbiddenPlmn(VOS_VOID);
VOS_VOID NAS_MMC_ProcEpsDetachCause11PlmnNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
);


NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCausePsAttachNotAllow(VOS_VOID);
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCausePsAttachNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);


NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause35ReqServOptNotAuthorizedInThisPlmn(VOS_VOID);

VOS_VOID NAS_MMC_ProcEpsDetachCause12TaNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
);
VOS_VOID NAS_MMC_ProcEpsDetachCause13RoamNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
);
VOS_VOID NAS_MMC_ProcEpsDetachCause14GprsNotAllowInThisPlmn(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
);
VOS_VOID NAS_MMC_ProcEpsDetachCause15NoSuitableCell(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
);
VOS_VOID NAS_MMC_ProcEpsDetachCause2ImsiUnknowInHss(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction
);
VOS_VOID NAS_MMC_ProcEpsDetachCause3IllegalMs(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
);
VOS_VOID NAS_MMC_ProcEpsDetachCause6IllegalMe(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
);
VOS_VOID NAS_MMC_ProcEpsDetachCause7EpsServNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
);
VOS_VOID NAS_MMC_ProcEpsDetachCause8GprsAndNonGprsNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
);
VOS_VOID NAS_MMC_ProcEpsDetachCauseAbnormalCause(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause10EpsImplicitlyDetached(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause11PlmnNotAllow(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause12TaNotAllow(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause13RoamNotAllow(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause14GprsNotAllowInThisPlmn(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause15NoSuitableCell(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause3IllegalMs(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause40NoEpsBearerActived(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause6IllegalMe(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause7EpsServNotAllow(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause9MsIdCannotBeDerivedByNW(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause257AccessBarrd(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause256AuthRej(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCauseForbiddenPlmn(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause35ReqServOptNotAuthorizedInThisPlmn(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause10EpsImplicitlyDetached(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause11PlmnNotAllow(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause12TaNotAllow(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause406ForbiddenPlmnForGprs(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause13RoamNotAllow(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause14GprsNotAllowInThisPlmn(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause15NoSuitableCell(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause3IllegalMs(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause40NoEpsBearerActived(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause6IllegalMe(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause7EpsServNotAllow(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause8GprsAndNonGprsNotAllow(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause9MsIdCannotBeDerivedByNW(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause257AccessBarrd(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause256AuthRej(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause301TimerTimeOut(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause401OtherCause(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause405ForbiddenLaForRoam(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause403ForbiddenPlmn(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause404ForbiddenTaForRegPrvsSvs(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause35ReqServOptNotAuthorizedInThisPlmn(VOS_VOID);


VOS_VOID NAS_MMC_ProcEpsRegFailAttemptCouterLessThanMaxTimes(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction
);
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCauseAbnormalCause(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause18CsDomainNotAvailable(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause25NotAuthorizedForThisCsg(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause39CsDomainTempNotAvailable(VOS_VOID);
#endif


#if   (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MMC_ConverLmmCombinedAttachRsltToMMLCause(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penPsRegRsltCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penCsRegRsltCause
);

VOS_VOID NAS_MMC_ConverLmmCombinedTauRsltToMMLCause(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauResultInd,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penPsRegRsltCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penCsRegRsltCause
);

VOS_VOID NAS_MMC_ProcCombinedAttachEpsRegFail(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType,
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction
);

VOS_VOID NAS_MMC_ProcCombinedTauEpsRegFail(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType,
    LMM_MMC_TAU_RESULT_IND_STRU                            *pstLmmTauIndMsg,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction
);


VOS_VOID NAS_MMC_ProcCombinedEpsRegOnlyEpsSucc(
    VOS_UINT16                                              usCause,
    VOS_UINT32                                              ulAttemptCnt,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction
);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFail(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType,
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFail(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType,
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
);

VOS_VOID NAS_MMC_ProcEpsDetachCause(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType,
    LMM_MMC_DETACH_IND_STRU                                *pstDetachMsg,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
);

VOS_VOID NAS_MMC_ProcLmmDetachInd(
    LMM_MMC_DETACH_IND_STRU                                *pstDetachMsg,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcLmmServiceRsltInd(
    LMM_MMC_SERVICE_RESULT_IND_STRU    *pstSerRsltMsg
);


VOS_VOID  NAS_MMC_ProcLmmCombinedAttachInd_AttRsltEpsOnlySucc(
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
);

VOS_VOID  NAS_MMC_ProcLmmCombinedAttachInd_AttRsltCsEpsSucc(
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
);

VOS_VOID  NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltCsEpsSucc(
    LMM_MMC_TAU_RESULT_IND_STRU                            *pstLmmTauIndMsg,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
);

VOS_VOID  NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltEpsOnlySucc(
    LMM_MMC_TAU_RESULT_IND_STRU                            *pstLmmTauIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
);

VOS_VOID  NAS_MMC_ProcLmmCombinedAttachInd_AttRsltSucc(
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
);

VOS_VOID NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltSucc(
    LMM_MMC_TAU_RESULT_IND_STRU                            *pstLmmTauIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
);

VOS_VOID NAS_MMC_ProcLmmCombinedTauResult(
    LMM_MMC_TAU_RESULT_IND_STRU                            *pstLmmTauIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction
);

VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCauseEpsBearerEstFail(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);

VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCauseMoDetach(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);

VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCauseMtDetach(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);

VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCauseT3402Running(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);

VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause40NoEpsBearerActived(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCauseMtDetach(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCauseMoDetach(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCauseEpsBearerEstFail(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCauseMoDetach(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCauseMtDetach(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCauseT3402Running(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCauseT3402Running(VOS_VOID);

VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCauseT3402RunningEpsOnlySucc(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType,
    LMM_MMC_TAU_RESULT_IND_STRU                            *pstLmmTauIndMsg,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction
);


VOS_VOID  NAS_MMC_ProcLmmCombinedAttachInd_AttRsltCsEpsSucc(
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
);

VOS_VOID  NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltCsEpsSucc(
    LMM_MMC_TAU_RESULT_IND_STRU                            *pstLmmTauIndMsg,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
);



#endif


#if   (FEATURE_ON == FEATURE_LTE)
VOS_VOID  NAS_MMC_ConvertLmmCauseToMmCause(
    NAS_LMM_CN_CAUSE_ENUM_UINT8          enLmmCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  *penMmCnCause
);

VOS_VOID NAS_MMC_ConverLmmAttachRsltToMMLCause(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penRegRsltCause
);

VOS_VOID NAS_MMC_ConverLmmServiceRsltToMMLCause(
    LMM_MMC_SERVICE_RESULT_IND_STRU    *pstLmmSerRsltIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penRegRsltCause
);

VOS_VOID NAS_MMC_ConverTauResultToMMLCause(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penRegRsltCause
);

MMC_LMM_ATTACH_TYPE_ENUM_UINT32 NAS_MMC_ConvertLmmAttachReqType(
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enUeOperationMode
);

VOS_UINT32 NAS_MMC_IsNeedDisableL_CombinedRegRsltSucc(VOS_VOID);

VOS_UINT32 NAS_MMC_IsNeedDisableL_CombinedRegRsltOnlyEpsSucc(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause
);

VOS_UINT32 NAS_MMC_IsNeedDisableL_ServiceReqFailCause18CsDomainNotAvailable(VOS_VOID);
VOS_UINT32 NAS_MMC_IsNeedDisableL_CombinedRegSuccAdditionUpdateRslt(
    NAS_MML_ADDITION_UPDATE_RSLT_INFO_ENUM_UINT8            enAdditionUpdateRslt
);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause42SevereNetworkFailure(VOS_VOID);
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause42SevereNetworkFailure(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause42SevereNetworkFailure(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause42SevereNetworkFailure(VOS_VOID);
VOS_UINT32 NAS_MMC_IsNeedDisableL_CombinedAttRsltFailCause14GprsNotAllowInThisPlmn(VOS_VOID);
VOS_UINT32 NAS_MMC_IsNeedDisableL_EpsDetachCause14GprsNotAllowInThisPlmn(VOS_VOID);
VOS_UINT32 NAS_MMC_IsNeedAddForbGprsPlmn_TauRsltFailCause14GprsNotAllowInThisPlmn(VOS_VOID);
VOS_UINT32 NAS_MMC_IsNeedAddForbPlmn_TauRsltFailCause11PlmnNotAllow(VOS_VOID);
VOS_UINT32 NAS_MMC_IsNeedDeleteEplmn_EpsDetachCause14GprsNotAllowInThisPlmn(VOS_VOID);
VOS_UINT32 NAS_MMC_IsNeedDeleteEplmn_EpsDetachCause14GprsNotAllowInThisPlmn(VOS_VOID);


NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause8GprsAndNonGprsNotAllow(VOS_VOID);
VOS_UINT32 NAS_MMC_IsNeedDisableL_RegFailCause16AttmptCntMaxTimes(VOS_VOID);
VOS_UINT32 NAS_MMC_IsNeedDisableL_RegFailCause17AttmptCntMaxTimes(VOS_VOID);

VOS_UINT32 NAS_MMC_IsNeedDeleteEplmn_CombinedRegRsltFailCause14GprsNotAllowInThisPlmn(VOS_VOID);


VOS_UINT32 NAS_MMC_IsNeedDisableL_ServiceRsltFail(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enRegRsltCause,
    VOS_UINT8                           ucIsReachMaxTimes
);
VOS_UINT32 NAS_MMC_IsNeedDisableL_RegFailCause22AttmptCntMaxTimes(VOS_VOID);


VOS_UINT32 NAS_MMC_IsNeedDisableL_EpsOnlyRegSucc(VOS_VOID);

VOS_UINT32 NAS_MMC_IsNeedDisableL_CombinedRegRsltFailMaxTimes(VOS_VOID);



VOS_UINT32 NAS_MMC_IsCsPsMode1NeedPeriodSearchGU(VOS_VOID);

VOS_UINT32 NAS_MMC_IsNeedDisableL_PsFailCause7PsServNotAllow(VOS_VOID);

VOS_UINT32 NAS_MMC_IsEutranNotAllowedNeedDisableL(VOS_VOID);

extern VOS_UINT32 NAS_MMC_IsNeedDisableL_LteRejCause14(VOS_VOID);

VOS_VOID NAS_MMC_SaveEpsAttachAttemptCounter(
    LMM_MMC_ATTACH_IND_STRU            *pstEpsAttachIndMsg
);

VOS_VOID NAS_MMC_SaveEpsTauAttemptCounter(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstEpsTauIndMsg
);

VOS_UINT32 NAS_MMC_IsNeedEnableLte_CsRegFailCause2ImsiUnknownInHlr(VOS_VOID);

VOS_UINT32 NAS_MMC_IsNeedEnableLte_CsRegFailCause256AuthRej(VOS_VOID);

VOS_UINT32 NAS_MMC_IsNeedEnableLte_PsRegFailCause256AuthRej(VOS_VOID);

VOS_UINT32 NAS_MMC_IsNeedEnableLte_PsRegFailCause3IllegalMs(VOS_VOID);

VOS_UINT32 NAS_MMC_IsNeedEnableLte_PsRegFailCause8GprsAndNonGprsNotAllow(VOS_VOID);

VOS_UINT32  NAS_MMC_IsNeedEnableLte_CmServiceRejectInd(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCmServiceRejCause
);

VOS_UINT32  NAS_MMC_IsNeedEnableLte_MmAbortInd(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enAbortCause
);


VOS_UINT32  NAS_MMC_IsNeedEnableLte_EnableLteTimerExp(VOS_VOID);

VOS_VOID NAS_MMC_ProcEmcPdpRelease_DetachPs( VOS_VOID );
VOS_UINT32 NAS_MMC_IsNeedSndEplmn_LmmDetachCnf(
    LMM_MMC_DETACH_CNF_STRU            *pstLmmDetachCnf
);

VOS_VOID NAS_MMC_ConvertLmmDetachIndTypeToMmcType(
    MMC_LMM_MT_DETACH_TYPE_ENUM_UINT32                      enCnReqType,
    NAS_MSCC_PIF_NETWORK_DETACH_TYPE_ENUM_UINT8                 *penDetachType
);

#endif
VOS_VOID NAS_MMC_GetAdditionalActionPrioValue(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAction,
    VOS_UINT8                          *pucPrioValue
);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8  NAS_MMC_GetPrioAddtionalAction(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enPsAdditionalAction
);
VOS_UINT32 NAS_MMC_IsAdditionalActionTrigerPlmnSrch(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAdditionalAction
);

VOS_UINT32 NAS_MMC_IsFailCauseInCustomizedForbLaCfgList(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enCause
);

VOS_UINT8 NAS_MMC_IsNeedLauRejTrigPlmnSearch(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enCause
);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetPsAdditionalAction(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCsAdditionalAction(VOS_VOID);

VOS_VOID    NAS_MMC_ConverGmmActionTypeToMml(
    GMM_MMC_ACTION_TYPE_ENUM_U32        enGmmActionType,
    NAS_MML_PROC_TYPE_ENUM_U32         *penProcType
);


VOS_VOID NAS_MMC_ConvertGmmRegDomainToMmcDomain(
	GMM_MMC_REG_DOMAIN_ENUM_UINT32		enRegDomain,
	NAS_MMC_REG_DOMAIN_ENUM_UINT8      *penMmcRegDomain
);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8    NAS_MMC_GetSingleDomainFailAction(
    NAS_MML_REG_DOMAIN_ENUM_UINT8           enDomain,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enFailCause
);

VOS_UINT32 NAS_MMC_IsCurrPlmnInEplmnList(VOS_VOID);

VOS_UINT32 NAS_MMC_IsAccBarPlmnSearch(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsRegFailCauseAbnormalCause(
    VOS_UINT16                          usCause,
    VOS_UINT32                          ulAttemptCnt
);

VOS_UINT32 NAS_MMC_GetLmmAttaClRegStatPrioValue(
    MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8  enLmmAttachClRegStatus
);

#if (FEATURE_ON == FEATURE_ECALL)
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause417ECallInactive(VOS_VOID);

#endif

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

