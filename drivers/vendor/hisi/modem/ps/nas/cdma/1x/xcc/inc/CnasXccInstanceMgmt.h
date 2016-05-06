/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXccInstMgmt.h
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年9月6日
  最近修改   :
  功能描述   : CnasXccInstMgmt.c 的头文件
  函数列表   :

  修改历史   :
  1.日    期   : 2014年9月6日
    作    者   : y00245242
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_XCC_INSTANCE_MGMT_H__
#define __CNAS_XCC_INSTANCE_MGMT_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "CnasXccCtx.h"
#include "cas_1x_control_main_nas_pif.h"


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
 结构名    : CNAS_XCC_CALL_INSTANCE_LIST_STRU
 结构说明  : call instance列表数据结构
 1.日    期   : 2014年09月11日
   作    者   : y00245242
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucInstanceNum;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucInstance[CNAS_XCC_MAX_FSM_ENTITY_NUM];
} CNAS_XCC_CALL_INSTANCE_LIST_STRU;

/*****************************************************************************
 结构名    : CNAS_XCC_CALL_INST_FSM_LIST_STRU
 结构说明  : call control instance列表
 1.日    期   : 2014年09月09日
   作    者   : y00245242
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucFsmNum;
    VOS_UINT8                           aucReserved[3];
    CNAS_XCC_FSM_ENTITY_STRU           *pstFsmEntity[CNAS_XCC_MAX_FSM_ENTITY_NUM];
}CNAS_XCC_FSM_ENTITY_LIST_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT8 CNAS_XCC_GetActivedCallInstanceNum(VOS_VOID);

VOS_VOID CNAS_XCC_GetAllActiveCallInstanceIndex(
    CNAS_XCC_CALL_INSTANCE_LIST_STRU    *pstIndexList
);

VOS_UINT8 CNAS_XCC_GetSpecTypeInstance(
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType,
    VOS_UINT8                          *pucIndex
);

VOS_UINT8 CNAS_XCC_IsVoiceCallInstanceActive(VOS_VOID);

VOS_UINT8 CNAS_XCC_IsCallConRefExist(
    VOS_UINT8                           ucConRef
);

VOS_VOID CNAS_XCC_GetCallInstanceOf1xEstCnf(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
);

VOS_VOID CNAS_XCC_GetCallInstanceOf1xDschDataCnf(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
);

VOS_VOID CNAS_XCC_GetCallInstanceOf1xDschDataInd(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
);

VOS_VOID CNAS_XCC_GetCallInstanceOf1xPagingInd(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
);

VOS_VOID CNAS_XCC_GetCallInstanceOf1xResetWfoSubStateTimerInd(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
);

VOS_VOID CNAS_XCC_GetCallInstanceOf1xUpdateCallInfoInd(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
);

VOS_VOID CNAS_XCC_GetCallInstanceOf1xCallInitInd(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
);

VOS_VOID CNAS_XCC_GetCallInstanceOf1xCallRelInd(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
);

VOS_VOID CNAS_XCC_GetCallInstanceOf1xCallTerminateInd(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
);

VOS_VOID CNAS_XCC_GetCallInstanceOfOrigCallReq(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
);

VOS_VOID CNAS_XCC_GetCallInstanceOfOtherMsg(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
);

VOS_VOID CNAS_XCC_GetCallInstanceOfApsDataCallSuspendRsp(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
);

VOS_VOID CNAS_XCC_GetCallInstanceOfTimerMsg(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
);

VOS_VOID CNAS_XCC_GetCallInstanceOfXccMoCalingRlstCnf(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
);

VOS_VOID CNAS_XCC_GetCallInstanceOfXccMtCalingRlstCnf(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
);

VOS_VOID CNAS_XCC_GetCallInstanceOfXccAbortReq(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
);

VOS_VOID CNAS_XCC_GetCallInstanceOfXccPowerDownReq(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
);

VOS_VOID CNAS_XCC_GetCallInstanceEntity(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_XCC_FSM_ENTITY_LIST_STRU      *pstFsmEntityList
);

VOS_VOID CNAS_XCC_GetConRefFromDschDataInd(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pst1xDschDataInd,
    VOS_UINT8                          *pucConRef
);



extern VOS_VOID CNAS_XCC_GetCallInstanceOfXccSendBurstDtmfReq(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
);

extern VOS_VOID CNAS_XCC_GetCallInstanceOfXccSendFlashReq(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
);

extern VOS_UINT8 CNAS_XCC_GetCallInstanceIndexByCallId(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                          *pucIndex
);

extern CNAS_XCC_SERVICE_TYPE_ENUM_UINT32 CNAS_XCC_GetServiceTypeAccordingMsgId(
    VOS_UINT32                          ulMsgName
);

extern VOS_UINT8 CNAS_XCC_GetCallInstanceIndexByConnId(
    VOS_UINT8                           ucConnId,
    VOS_UINT8                          *pucIndex
);

VOS_UINT8 CNAS_XCC_GetCallInstanceIndexByCallRef(
    VOS_UINT8                           ucConRef,
    VOS_UINT8                          *pucIndex
);

VOS_VOID CNAS_XCC_GetCallInstanceOfXccNdssRedialInd(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
);

VOS_VOID CNAS_XCC_GetCallInstanceOfXccSendContDtmfReq(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
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

#endif /* end of CnasXccInstMgmt.h */
