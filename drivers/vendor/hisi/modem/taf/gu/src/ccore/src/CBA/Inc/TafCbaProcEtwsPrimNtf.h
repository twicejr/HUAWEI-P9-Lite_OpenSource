/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafCbaProcEtwsPrimNtf.h
  版 本 号   : 初稿
  作    者   : l00171473
  生成日期   : 2012年3月19日
  最近修改   :
  功能描述   : TafCbaProcEtwsPrimNtf.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAFCBAPROCETWSPRIMNTF_H__
#define __TAFCBAPROCETWSPRIMNTF_H__

/*****************************************************************************
  1 其他头文件包含                            
*****************************************************************************/
#include  "TafCbaCtx.h"
#include  "MnMsgApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

#if (FEATURE_ON == FEATURE_ETWS)

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


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

VOS_VOID TAF_CBA_RcvAsEtwsPrimNotifyInd(
    RR_CBS_ETWS_PRIMARY_NOTIFY_IND_STRU                    *pstMsg
);


VOS_UINT32 TAF_CBA_IsMsgIdInEtwsMsgIdList(
    VOS_UINT16                          usMsgId
);


VOS_UINT32  TAF_CBA_IsEtwsPrimNtfMsgIdValid(
    VOS_UINT16                          usMsgId
);


VOS_UINT32 TAF_CBA_GetEtwsDupDetcTimeLen(
    TAF_CBA_PLMN_ID_STRU                                   *pstPlmn
);

VOS_VOID TAF_CBA_BuildEtwsPrimNtfRecord(
    RR_CBS_ETWS_PRIMARY_NOTIFY_IND_STRU                    *pstMsg,
    TAF_CBA_RECORD_STRU                                    *pstNewRecord
);


VOS_VOID TAF_CBA_SaveEtwsPrimNtfRecord (
    TAF_CBA_RECORD_STRU                *pstNewRecord
);

VOS_VOID TAF_CBA_DelEtwsPrimNtfExpiredRecord(VOS_VOID);


VOS_UINT32  TAF_CBA_GetEarliestEtwsPrimNtfRecordInx(VOS_VOID);

VOS_UINT32 TAF_CBA_IsNeedDupDetectEtwsPrimNtf(VOS_VOID);



VOS_UINT32 TAF_CBA_IsDupEtwsPrimNtf(
    TAF_CBA_RECORD_STRU                *pstRecord
);


VOS_UINT32 TAF_CBA_GetEtwsPrimNtfRecordInxByMsgIdCode(
    TAF_CBA_RECORD_STRU                *pstRecord,
    VOS_UINT32                         *pstIndex
);


VOS_VOID TAF_CBA_TemporaryEnableCbs(VOS_VOID);


#endif  /* (FEATURE_ON == FEATURE_ETWS) */

#endif /* ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS)) */






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

#endif /* end of TafCbaProcEtwsPrimNtf.h */
