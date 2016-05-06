/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafCbaComFunc.h
  版 本 号   : 初稿
  作    者   : l00171473
  生成日期   : 2012年3月19日
  最近修改   :
  功能描述   : TafCbaComFunc.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAFCBACOMFUNC_H__
#define __TAFCBACOMFUNC_H__

/*****************************************************************************
  1 其他头文件包含                            
*****************************************************************************/
#include  "TafCbaCtx.h" 
#include  "TafCbsInterface.h"

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


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/



VOS_UINT32 TAF_CBA_IsMsgIdInCbsActiveList(
    VOS_UINT16                          usMsgId
);

VOS_UINT32 TAF_CBA_IsRecordExpired(
    TAF_CBA_RECORD_STRU                *pstRecord
);

VOS_UINT32 TAF_CBA_IsSameMsgCode(
    VOS_UINT16      usNewSn, 
    VOS_UINT16      usOldSn
);

VOS_UINT32 TAF_CBA_IsSameGsCode(
    VOS_UINT16      usNewSn, 
    VOS_UINT16      usOldSn
);

VOS_UINT32 TAF_CBA_IsSameUpdateNum(
    VOS_UINT16      usNewSn, 
    VOS_UINT16      usOldSn
);

VOS_VOID TAF_CBA_ConvertMnNetModeToCbaFormat(
    VOS_UINT8                           ucMnNtMode,
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8    *penNetType
);

VOS_UINT32 TAF_CBA_AddCbMiRangeListToActiveList(
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstOrgCbMirList
);

VOS_UINT32 TAF_CBA_IsCbmirExist(
    TAF_CBA_CBMI_RANGE_STRU            *pstMsgRange,
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstCbmirList,
    VOS_UINT32                         *pulCbmirIdx
);

VOS_UINT32 TAF_CBA_IsCbmiRangeListEmpty(VOS_VOID);

VOS_UINT32 TAF_CBA_IsCbsActiveListEmpty(VOS_VOID);

VOS_UINT32 TAF_CBA_IsDupMidsInActiveList(
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstAddbMids
);

VOS_UINT32 TAF_CBA_IsNeedActAsCbs(VOS_VOID);

VOS_VOID   TAF_CBA_SndAsActiveCbsReq(
    TAF_CBS_CFG_ENUM_UINT32             enActiveFlg
);

VOS_UINT32 TAF_CBA_DelCbMiRangeListFromActiveList(
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstOrgCbMirList
);

VOS_VOID TAF_CBA_DelInvalidCbsRecordByGsChgType(
    TAF_CBS_GS_CHG_TYPE_ENUM_UINT8      enGsChgType,
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enGsChgNetMode
);

VOS_VOID TAF_CBA_DelRecordByActiveList(VOS_VOID);

VOS_VOID TAF_CBA_DelCbsExpiredRecord(VOS_VOID);

VOS_VOID TAF_CBA_DelInvalidEtwsPrimNtfRecordByGsChgType(
    TAF_CBS_GS_CHG_TYPE_ENUM_UINT8      enGsChgType,
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enGsChgNetMode
);

VOS_UINT32 TAF_CBA_IsRecordValidByGsChgType(
    VOS_UINT16                          usSerialNum,
    TAF_CBS_GS_CHG_TYPE_ENUM_UINT8      enGsChgType
);

VOS_VOID TAF_CBA_SortCbmiRangeList(
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstRangeList
);

VOS_VOID TAF_CBA_SortEtwsRangList(
    TAF_CBA_ETWS_MSGID_RANGE_STRU      *pstEtwsRangeList,
    VOS_UINT32                          ulMaxNum
);

TAF_CBS_GS_CHG_TYPE_ENUM_UINT8 TAF_CBA_GetGsChgTypeByNetworkInfo(
    TAF_CBA_NETWORK_INFO_STRU          *pstCurrNetworkInfo,
    TAF_CBA_NETWORK_INFO_STRU          *pstOldGsChgNetworkInfo
);

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

#endif /* end of TafCbaComFunc.h */
