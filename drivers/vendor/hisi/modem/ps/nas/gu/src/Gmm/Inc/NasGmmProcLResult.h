/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasGmmProcLResult.h
  版 本 号   : 初稿
  作    者   : W00167002
  生成日期   : 2011年4月8日
  最近修改   :
  功能描述   : NasGmmProcLResult.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年4月8日
    作    者   : W00167002
    修改内容   : 创建文件

******************************************************************************/
#ifndef __NASGMMPROCLRESULT_H__
#define __NASGMMPROCLRESULT_H__
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif

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
#if (FEATURE_ON == FEATURE_LTE)
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    NAS_LMM_GUTI_STRU                   stGutiMsg;
}NAS_GMM_LOG_GUTI_INFO_STRU;
#endif

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_LTE)
extern VOS_UINT32 NAS_GMM_IsGutiInfoValid( VOS_VOID );


extern VOS_VOID NAS_GMM_ConvertLmmPlmnToGmmPlmnId(
           MMC_LMM_PLMN_ID_STRU                *pstLmmPlmn,
           GMM_PLMN_ID_STRU                    *pstGmmPlmn
       );

extern VOS_VOID NAS_GMM_GetGUSecContextFromEpsSecContextInReselect(
           struct MsgCB                       *pstMsg
       );
extern VOS_VOID NAS_GMM_GetGUSecContextFromEpsSecContextInHandOver(
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32  NAS_GMM_GetGuSecuInfo(
           NAS_GUMM_UMTS_CONTEXT_STRU         *pstSecuContext
       );
extern VOS_UINT32  NAS_GMM_GetLaiInfo(
           MMC_LMM_LAI_STRU                    *pstLai
       );

extern VOS_UINT32  NAS_GMM_GetRaiInfo(
    MMC_LMM_RAI_STRU                    *pstRai
);
extern VOS_VOID  NAS_GMM_GetTmsiStatusInfo(
           MMC_LMM_TMSI_STATUS_TYPE_ENUM_UINT32 *ulTmsiStatus
       );
extern VOS_UINT32  NAS_GMM_MapLaiFromGUTI( VOS_VOID );
extern VOS_UINT32  NAS_GMM_MapPtmsiFromGUTI( VOS_VOID );
extern VOS_UINT32  NAS_GMM_MapPtmsiSignFromGUTIAndNasToken( VOS_VOID );
extern VOS_UINT32  NAS_GMM_MapRaiFromGUTI( VOS_VOID );
extern VOS_VOID  NAS_GMM_ProcLmmRejCause3( VOS_VOID );
extern VOS_VOID NAS_GMM_RcvLmmAttachCause_Handling(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause,
    VOS_UINT32                          ulAttemptCount
);

extern VOS_VOID  NAS_GMM_RcvLmmAttachResult(
           VOS_VOID                           *pstMsg
       );
extern VOS_VOID  NAS_GMM_RcvLmmAuthResult(
           VOS_VOID                           *pstMsg
       );
extern VOS_VOID  NAS_GMM_RcvLmmNwInitDetachIndCause_Handling(
           NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause
       );

extern VOS_VOID  NAS_GMM_RcvLmmServiceCause_Handling(
            NAS_LMM_CN_CAUSE_ENUM_UINT8        enCnCause
       );
extern VOS_VOID  NAS_GMM_RcvLmmServiceResult(
           VOS_VOID                           *pstMsg
       );
extern VOS_VOID NAS_GMM_RcvLmmTauCause_Handling(
    NAS_LMM_CN_CAUSE_ENUM_UINT8                             enCnCause,
    VOS_UINT32                                              ulAttemptCount,
    MMC_LMM_TAI_IN_LIST_FLAG_ENUM_UINT8                     enTaiInListFlag,
    MMC_LMM_EPS_UPDATE_STATUS_ENUM_UINT8                    enEmmUpStat
);
extern VOS_VOID  NAS_GMM_RcvLmmTauResult(
           VOS_VOID                           *pstMsg
       );

VOS_VOID NAS_GMM_LogGutiInfo(
    NAS_LMM_GUTI_STRU                  *pstGuti
);

VOS_VOID  NAS_GMM_RcvLmmMtDetachInd(
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_GMM_RcvLmmMoDetachInd(
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_GMM_RcvLmmLocalDetachInd(
    struct MsgCB                       *pstMsg
);


VOS_VOID NAS_GMM_RcvLmmAttachRegFailOtherCause(
    VOS_UINT32                          ulAttemptCount
);

VOS_VOID NAS_GMM_RcvLmmTauRegFailOtherCause(
    VOS_UINT32                                              ulAttemptCount,
    MMC_LMM_TAI_IN_LIST_FLAG_ENUM_UINT8                     enTaiInListFlag,
    MMC_LMM_EPS_UPDATE_STATUS_ENUM_UINT8                    enEmmUpStat
);
VOS_VOID NAS_GMM_RcvLmmAttachRegFailCause42SevereNetworkFailure(
    VOS_UINT32                          ulAttemptCount
);
VOS_VOID NAS_GMM_RcvLmmTauRegFailCause42SevereNetworkFailure(
    VOS_UINT32                                              ulAttemptCount,
    MMC_LMM_TAI_IN_LIST_FLAG_ENUM_UINT8                     enTaiInListFlag,
    MMC_LMM_EPS_UPDATE_STATUS_ENUM_UINT8                    enEmmUpStat
);



extern VOS_UINT32 NAS_GMM_IsNeedUpdatePsUpdateStatus(
    VOS_UINT32                                              ulAttemptCount,
    MMC_LMM_TAI_IN_LIST_FLAG_ENUM_UINT8                     enTaiInListFlag,
    MMC_LMM_EPS_UPDATE_STATUS_ENUM_UINT8                    enEmmUpStat
);
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

#endif /* end of NasGmmProcLResult.h */
