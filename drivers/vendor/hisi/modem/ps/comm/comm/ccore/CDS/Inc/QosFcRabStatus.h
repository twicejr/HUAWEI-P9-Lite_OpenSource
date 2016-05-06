/******************************************************************************

                  版权所有 (C), 2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : QosFcRabStatus.h
  版 本 号   : 初稿
  作    者   : w00145177
  生成日期   : 2011年12月23日
  最近修改   :
  功能描述   : QoS流控承载状态管理头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月23日
    作    者   : w00145177
    修改内容   : 创建文件

******************************************************************************/

#ifndef __QOS_FC_RAB_STATUS_H__
#define __QOS_FC_RAB_STATUS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "QosFcCommon.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/
/*****************************************************************************
 结构名    : QOS_FC_RAB_STATE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : 定义无线承载的状态。该状态对GU和L代表含义不同:对GU来说，其代表RAB
             的状态；对LTE来说，其代表DRB的状态
*****************************************************************************/
typedef enum QOS_FC_RAB_STATE
{
    QOS_FC_RAB_STATE_NORMAL,           /* 正常数传状态 */
    QOS_FC_RAB_STATE_RANDOM_DISCARD,   /* 随机丢包状态 */
    QOS_FC_RAB_STATE_DISCARD,          /* 丢包状态 */
    QOS_FC_RAB_STATE_NOT_DISCARD,      /* 流控不丢包状态，STICK */
    QOS_FC_RAB_STATE_BUTT
} QOS_FC_RAB_STATE_ENUM;

typedef VOS_UINT32 QOS_FC_RAB_STATE_ENUM_UINT32;


/*****************************************************************************
   5 STRUCT定义
*****************************************************************************/
/*****************************************************************************
 结构名    : QOS_FC_RAB_ENTITY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 定义CDS任务实体结构
*****************************************************************************/
typedef struct QOS_FC_RAB_ENTITY
{
    VOS_UINT8               ucRabId;                      /* 承载标识  */
    QCI_TYPE_ENUM_UINT8     enQci;
    VOS_UINT8               ucPriority;                   /* 承载优先级 */
    VOS_UINT8               ucLinkRabId;                  /* 主承载标识  */
    QOS_FC_RAB_STATE_ENUM_UINT32       enRabState;
} QOS_FC_RAB_ENTITY_STRU;



/*****************************************************************************
  6 UNION定义
*****************************************************************************/


/*****************************************************************************
  7 全局变量声明
*****************************************************************************/


/*****************************************************************************
  8 函数声明
*****************************************************************************/
extern VOS_VOID QosFcRabInit(VOS_VOID);
extern VOS_UINT32 QosFc_RestoreHighPriRab(VOS_VOID);
extern VOS_UINT32 QosFc_DiscardAllDataFlow(VOS_VOID);
extern VOS_UINT32 QosFc_RestoreDataFlow(VOS_VOID);
extern VOS_UINT32 QosFc_DiscardDataFlow(VOS_VOID);
extern VOS_UINT32 QosFc_RandomDiscardDataFlow(VOS_VOID);

extern VOS_VOID QosFc_RabCreate(CONST MsgBlock  *pstMsg);
extern VOS_VOID QosFc_RabRelease(CONST MsgBlock  *pstMsg);
extern VOS_VOID QosFc_UpdateRabStatus(VOS_UINT8 ucRabId, QOS_FC_RAB_STATE_ENUM_UINT32 enRabState);
extern QOS_FC_RAB_STATE_ENUM_UINT32 QosFc_GetRabStatus(VOS_UINT8 ucRabId);
extern VOS_VOID QosFc_RabEntityInit(VOS_UINT32 ulIndex);
extern VOS_UINT8 QosFc_OtherAvailRabOfPdn(VOS_UINT8 ucRabId);
extern VOS_BOOL QosFc_RabNeedFlowCtrl(VOS_UINT32 ulIndex);
extern VOS_VOID QosFc_SetRabDiscard(VOS_UINT32 ulIndex);
extern VOS_VOID QosFc_SetRabRandomDiscard(VOS_UINT32 ulIndex);
extern VOS_VOID QosFc_SetRabNormal(VOS_UINT32 ulIndex);
extern VOS_VOID QosFc_RestoreRabStatus(VOS_UINT32 ulIndex);
extern VOS_VOID QosFc_SetRabEntity(QOS_FC_RAB_ENTITY_STRU *pstQosFcRabEntity, CONST QOS_FC_RAB_CREATE_IND_STRU *pstRabCreate);
extern VOS_UINT32 QosFc_MoveUpEntityPos(VOS_UINT32 ulInitPos, VOS_UINT8 ucPriority);
extern VOS_UINT32 QosFc_MoveDownEntityPos(VOS_UINT32 ulInitPos, VOS_UINT8 ucPriority);
extern QOS_FC_RAB_ENTITY_STRU* QosFc_CreateRabEntity(CONST QOS_FC_RAB_CREATE_IND_STRU *pstRabCreate, VOS_UINT8 *pucOldLinkRabId);
extern QCI_TYPE_ENUM_UINT8 QosFc_GetPdnQci(VOS_UINT8 ucRabId);
extern VOS_UINT8 QosFc_ReleaseRabEntity(VOS_UINT8 ucRabId);

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

