/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnCallFacilityDecode.h
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年9月15日
  最近修改   : 2007年9月15日
  功能描述   : MNCC原语发送模块的接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2007年9月15日
    作    者   : 丁庆 49431
    修改内容   : 创建文件
******************************************************************************/
#ifndef  MN_CALL_FACILITY_PROC_H
#define  MN_CALL_FACILITY_PROC_H


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafAppMma.h"
#include "TafAppSsa.h"
#include "MnCallApi.h"
#include "NasCcIe.h"
#include "product_config.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 常量定义
*****************************************************************************/


/*****************************************************************************
  3类型定义
*****************************************************************************/

/******* 根据呼叫相关补充业务的需求添加 -- 丁庆  2006-2-7  Begin *******/

typedef struct
{
    VOS_UINT32                          OP_DataCodingScheme:1;
    VOS_UINT32                          OP_LengthInCharacters:1;
    VOS_UINT32                          OP_NameString:1;
    VOS_UINT32                          OP_Spare:29;

    VOS_UINT8                           DataCodingScheme;
    VOS_UINT8                           aucReserved1[3];
    VOS_INT32                           LengthInCharacters;
    VOS_UINT8                           NameString[161];
    VOS_UINT8                           aucReserved2[3];
} MN_CALL_NAME_PRESENTATION_STRU;

typedef struct
{
    VOS_UINT32                          OP_NamePresentationAllowed:1;
    VOS_UINT32                          OP_RresentationRestricted:1;
    VOS_UINT32                          OP_NameUnAvailable:1;
    VOS_UINT32                          OP_NamePresentationRestricted:1;
    VOS_UINT32                          OP_Spare:1;

    MN_CALL_NAME_PRESENTATION_STRU      NamePresentationAllowed;
    MN_CALL_NAME_PRESENTATION_STRU      NamePresentationRestricted;
} MN_CALL_NAME_INDICATOR_STRU;

#define MN_CALL_MAX_ECT_NUM_LEN         40
#define MN_CALL_MAX_SUB_ADDR_NUM_LEN    42
typedef struct
{
    VOS_UINT8                           NumType;
    VOS_UINT8                           aucPartyNumber[MN_CALL_MAX_ECT_NUM_LEN + 1];
    VOS_UINT8                           AddrType;
    VOS_UINT8                           aucPartyNumberSubAddr[MN_CALL_MAX_SUB_ADDR_NUM_LEN + 1];
} MN_CALL_PRESENTATION_ADDR_STRU;

typedef VOS_UINT8  MN_CALL_ECT_CALL_STATE;
#define MN_CALL_ECT_ST_ALERTING         0x00
#define MN_CALL_ECT_ST_ACTIVE           0x01
typedef struct
{
    VOS_UINT32                          OP_PresentationAllowedAddr:1;
    VOS_UINT32                          OP_PresentationRestricted:1;
    VOS_UINT32                          OP_NumNotAvailableDueToInterworking:1;
    VOS_UINT32                          OP_PresentationRestrictedAddr:1;
    VOS_UINT32                          OP_Spare:28;

    MN_CALL_ECT_CALL_STATE              EctCallState;
    VOS_UINT8                           aucReserved[3];
    MN_CALL_PRESENTATION_ADDR_STRU      PresentationAllowedAddr;
    MN_CALL_PRESENTATION_ADDR_STRU      PresentationRestrictedAddr;
}MN_CALL_ECT_INDICATOR_STRU;

enum MN_CALL_SS_NOTIFICATION_ENUM
{
    TAF_FWDIND_FORWARDED_CALL_INCOM = 1,                                        /* 呼入的是一个被转移的呼叫 */
    TAF_FWDIND_INCALL_FORWARDED     = 2,                                        /* 呼入的呼叫被转移 */
    TAF_FWDIND_OUTCALL_FORWARDED    = 4                                         /* 呼出的呼叫被对方转移 */
};
typedef VOS_UINT8  MN_CALL_SS_NOTIFICATION_ENUM_U8;

typedef VOS_UINT8  MN_CALL_ON_HOLD_INDICATOR;
#define MN_CALL_ON_HOLD_IND_RETRIEVED   0x00
#define MN_CALL_ON_HOLD_IND_HOLD        0x01


typedef VOS_INT32  MN_CALL_CUG_INDEX;

typedef VOS_UINT8  MN_CALL_MULTICALL_INDICATOR;
#define MN_CALL_MULTICALL_IND_SN_EXCEEDED      0x00
#define MN_CALL_MULTICALL_IND_USER_EXCEEDED    0x01

typedef struct
{
    VOS_UINT32                          OP_SsCode               :1;
    VOS_UINT32                          OP_SsStatus             :1;
    VOS_UINT32                          OP_SsNotification       :1;
    VOS_UINT32                          OP_CallWaitingInd       :1;
    VOS_UINT32                          OP_CallOnHoldInd        :1;
    VOS_UINT32                          OP_MptyIndicator        :1;
    VOS_UINT32                          OP_CugIndex             :1;
    VOS_UINT32                          OP_ClirSuppressionRej   :1;
    VOS_UINT32                          OP_EctIndicator         :1;
    VOS_UINT32                          OP_NameIndicator        :1;
    VOS_UINT32                          OP_CcbsFeature          :1;
    VOS_UINT32                          OP_AlertingPattern      :1;
    VOS_UINT32                          OP_MulticallInd         :1;
    VOS_UINT32                          OP_Spare                :19;

    TAF_SS_CODE                         SsCode;
    TAF_SS_STATUS                       SsStatus;
    MN_CALL_SS_NOTIFICATION_ENUM_U8     SsNotification;
    MN_CALL_ON_HOLD_INDICATOR           CallOnHoldIndicator;
    MN_CALL_CUG_INDEX                   CugIndex;
    MN_CALL_ECT_INDICATOR_STRU          EctIndicator;
    MN_CALL_NAME_INDICATOR_STRU         NameIndicator;
    TAF_SS_CCBS_FEATURE_STRU            CcbsFeature;
    TAF_SS_ALERTINGPATTERN              AlertingPattern;
    MN_CALL_MULTICALL_INDICATOR         MulticallIndicator;
    VOS_UINT8                           aucReserved[2];
} MN_CALL_SS_NOTIFYSS_ARG_STRU;



    /* callDeflectionArg  */
#define MN_CALL_SS_CD_NUM_LEN           20
#define MN_CALL_SS_CD_SUB_ADDR_LEN      21

typedef struct
{
    VOS_UINT8                           ucNumberLen;
    VOS_UINT8                           aucNumber[MN_CALL_SS_CD_NUM_LEN];
    VOS_UINT8                           ucSubAddrLen;
    VOS_UINT8                           aucSubAddr[MN_CALL_SS_CD_SUB_ADDR_LEN];
} MN_CALL_SS_CD_ARG_STRU;

/* chargingInformation */
typedef struct
{
    VOS_UINT16                          bitOpE1  :  1;
    VOS_UINT16                          bitOpE2  :  1;
    VOS_UINT16                          bitOpE3  :  1;
    VOS_UINT16                          bitOpE4  :  1;
    VOS_UINT16                          bitOpE5  :  1;
    VOS_UINT16                          bitOpE6  :  1;
    VOS_UINT16                          bitOpE7  :  1;
    VOS_UINT16                          bitSpare :  9;

    VOS_UINT16                          usE1;
    VOS_UINT16                          usE2;
    VOS_UINT16                          usE3;
    VOS_UINT16                          usE4;
    VOS_UINT16                          usE5;
    VOS_UINT16                          usE6;
    VOS_UINT16                          usE7;
} MN_CALL_SS_CHARGE_INFO_STRU;

/* forwardChargeAdviceArg */
typedef struct
{
    TAF_SS_CODE                         ucSsCode;
    MN_CALL_SS_CHARGE_INFO_STRU         stChargeInfo;
} MN_CALL_SS_AOC_ARG_STRU;


/* Result of accessRegisterCCEntry operation */
typedef struct
{
    VOS_UINT32                          bitOpCcbsFeature  :  1;
    VOS_UINT32                          bitOpSpare        :  31;

    TAF_SS_CCBS_FEATURE_STRU stCcbsFeature;
} MN_CALL_SS_CCBS_RES_ARG_STRU;



typedef union
{
    MN_CALL_SS_NOTIFYSS_ARG_STRU        notifySsArg;
    MN_CALL_CUG_CFG_STRU                cugInfoArg;
    MN_CALL_SS_CD_ARG_STRU              stCdArg;
    MN_CALL_SS_AOC_ARG_STRU             stAocArg;
    MN_CALL_SS_CCBS_RES_ARG_STRU        stCcbsResArg;
} MN_CALL_SS_COMPONENT_ARG_UNION;


typedef struct
{
    VOS_UINT8                           ucCompType;
    VOS_UINT8                           bitOpLinkId     :1;
    VOS_UINT8                           bitOpArg        :1;
    VOS_UINT8                           bitOpSpare      :6;

    VOS_UINT8                           ucInvokeId;
    VOS_UINT8                           ucLinkId;
    VOS_UINT8                           ucOperateCode;
    VOS_UINT8                           aucReserved[3];
    MN_CALL_SS_COMPONENT_ARG_UNION      unArg;
} MN_CALL_SS_INVOKE_COMP_STRU;


typedef struct
{
    VOS_UINT8                           ucCompType;
    VOS_UINT8                           bitOpSequence   :1;
    VOS_UINT8                           bitOpOperateCode:1;
    VOS_UINT8                           bitOpArg        :1;
    VOS_UINT8                           bitOpSpare      :5;


    VOS_UINT8                           ucInvokeId;
    VOS_UINT8                           ucSequenceTag;
    VOS_UINT8                           ucOperateCode;
    VOS_UINT8                           aucReserved[3];
    MN_CALL_SS_COMPONENT_ARG_UNION      unArg;
} MN_CALL_SS_RESULT_COMP_STRU;


typedef struct
{
    VOS_UINT8                           ucCompType;
    VOS_UINT8                           bitOpArg        :1;
    VOS_UINT8                           bitOpSpare      :7;
    VOS_UINT8                           ucInvokeId;
    VOS_UINT8                           ucErrorCode;
    MN_CALL_SS_COMPONENT_ARG_UNION      unArg;
} MN_CALL_SS_ERROR_COMP_STRU;


typedef struct
{
    VOS_UINT8                           ucCompType;
    VOS_UINT8                           ucInvokeId;
    VOS_UINT8                           ucProblemTag;
    VOS_UINT8                           ucProblemCode;
} MN_CALL_SS_REJECT_COMP_STRU;


typedef union
{
    VOS_UINT8                           ucCompType;
    MN_CALL_SS_INVOKE_COMP_STRU         invokeComp;
    MN_CALL_SS_RESULT_COMP_STRU         resultComp;
    MN_CALL_SS_ERROR_COMP_STRU          errorComp;
    MN_CALL_SS_REJECT_COMP_STRU         rejectComp;
} MN_CALL_SS_COMPONENT_UNION;



/******* 根据呼叫相关补充业务的需求添加 -- 丁庆  2006-2-7  End *******/



/*****************************************************************************
  4 宏定义
*****************************************************************************/
#define	MN_CALL_IE_FACILITY	        	            0x1C

/* 呼叫相关补充业务的相关参数定义 */
/******************************************************************************/
/* Component type tag定义 */
#define MN_CALL_SS_INVOKE_TYPE_TAG                  0xa1
#define MN_CALL_SS_RETURN_RESULT_TYPE_TAG           0xa2
#define MN_CALL_SS_RETURN_ERROR_TYPE_TAG            0xa3
#define MN_CALL_SS_REJECT_TYPE_TAG                  0xa4

/* Component ID tag定义 */
#define MN_CALL_SS_INVOKE_ID_TAG                    0x02
#define MN_CALL_SS_LINKED_ID_TAG                    0x80

/* Operation Code tag定义 */
#define MN_CALL_SS_OPERATION_CODE_TAG               0x02

/* Sequence and Set tags定义 */
#define MN_CALL_SS_SEQUENCE_TAG                     0x30
#define MN_CALL_SS_SET_TAG                          0x31

/* Error Code tag定义 */
#define MN_CALL_SS_ERROR_TAG                        0x02

/* Problem Code tag定义 */
#define MN_CALL_SS_GENERAL_PROBLEM_TAG              0x80
#define MN_CALL_SS_IVOKE_PROBLEM_TAG                0x81
#define MN_CALL_SS_RETURN_RESULT_PROBLEM_TAG        0x82
#define MN_CALL_SS_RETURN_ERROR_PROBLEM_TAG         0x83

/* Operation Code定义 */
typedef VOS_UINT8  MN_CALL_SS_OPERATION_CODE_T;
#define MN_CALL_SS_NOTIFYSS_OPERATION               16
#define MN_CALL_SS_CD_OPERATION                     117
#define MN_CALL_SS_REG_CC_ENTRY_OPERATION           119
#define MN_CALL_SS_CUG_OPERATION                    120
#define MN_CALL_SS_SPLITMPTY_OPERATION              121
#define MN_CALL_SS_RETRIEVEMPTY_OPERATION           122
#define MN_CALL_SS_HOLDMPTY_OPERATION               123
#define MN_CALL_SS_BUILDMPTY_OPERATION              124
#define MN_CALL_SS_AOC_OPERATION                    125
#define MN_CALL_SS_ECT_OPERATION                    126

#define MN_CALL_MAX_INVOKE_NUM                      255                 /* 最多支持255个invoke id */



/*****************************************************************************
  5 全局变量声明
*****************************************************************************/


/*****************************************************************************
  6 接口函数声明
*****************************************************************************/
/*****************************************************************************
 Prototype      : MN_CALL_FacilityDecode()
 Description    : Facility消息解码
 Input          : ulMsgPointer   接收消息的指针
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
*****************************************************************************/
VOS_UINT32 MN_CALL_FacilityDecode(
    const NAS_CC_IE_FACILITY_STRU       *pstFacility,
    MN_CALL_SS_COMPONENT_UNION          *punComponent
);


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* MN_CALL_FACILITY_PROC_H */

