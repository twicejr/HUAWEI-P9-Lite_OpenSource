/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMtaMain.h
  版 本 号   : 初稿
  作    者   : 闫志吉
  生成日期   : 2012年6月27日
  最近修改   :
  功能描述   : MTA模块消息处理函数对应表及相关公共处理声明
  函数列表   :
  修改历史   :
  1.日    期   : 2012年6月27日
    作    者   : Y00213812
    修改内容   : A-GPS项目新增

******************************************************************************/

#ifndef __TAFMTAMAIN_H__
#define __TAFMTAMAIN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "AtMtaInterface.h"
#include "MtaRrcInterface.h"
#include "MtaPhyInterface.h"
#include "TafAppMma.h"
#include "TafMtaCtx.h"

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
typedef VOS_VOID (*MTA_MSG_PROC_FUNC)(VOS_VOID* pMsg);

/*****************************************************************************
结构名    : MTA_PROC_MSG_STRU
结构说明  : MTA模块消息处理函数的结构
1.日    期  : 2012年06月28日
  作    者  : y00213812
  修改内容  : V7R1C50 A_GPS项目新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMsgType;                              /* MTA接收消息ID */
    MTA_MSG_PROC_FUNC                   pProcMsgFunc;
}MTA_MSG_PROC_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/
/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_VOID TAF_MTA_InitCtx(TAF_MTA_CONTEXT_STRU *pstMtaCtx);
extern VOS_UINT32 TAF_MTA_InitPid(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 TAF_MTA_InitTask( VOS_VOID );
extern VOS_VOID TAF_MTA_ProcMsg (struct MsgCB *pstMsg);
extern VOS_VOID TAF_MTA_RcvAtMsg(struct MsgCB *pstMsg);
extern VOS_VOID TAF_MTA_RcvGasMsg(struct MsgCB *pstMsg);
extern VOS_VOID TAF_MTA_RcvGphyMsg(struct MsgCB *pstMsg);
extern VOS_VOID TAF_MTA_RcvTimerMsg(VOS_VOID *pstMsg);
extern VOS_VOID TAF_MTA_RcvWcomMsg(struct MsgCB *pstMsg);
extern VOS_VOID TAF_MTA_RcvWphyMsg(struct MsgCB *pstMsg);
extern VOS_VOID TAF_MTA_RcvTcMsg(struct MsgCB *pstMsg);
extern VOS_VOID TAF_MTA_RcvNasMsg(struct MsgCB *pstMsg);
extern VOS_VOID TAF_MTA_SndAtMsg(
           AT_APPCTRL_STRU                    *pAppCtrl,
           VOS_UINT32                          ulMsgId,
           VOS_UINT32                          ulLen,
           VOS_UINT8                          *pData);
extern VOS_UINT32 TAF_MTA_SearchMsgProcTab(
           VOS_UINT32                          ulMsgCnt,
           VOS_VOID                           *pstMsg,
           const MTA_MSG_PROC_STRU            *pstMsgProcTab);


extern  VOS_VOID TAF_MTA_RcvWrrMsg(struct MsgCB *pstMsg);

extern  VOS_VOID TAF_MTA_RcvApmMsg(struct MsgCB *pstMsg);

VOS_VOID TAF_MTA_RcvRttAgentMsg(struct MsgCB *pstMsg);
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
extern VOS_VOID TAF_MTA_RcvMtcMsg(struct MsgCB *pstMsg);
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
extern VOS_VOID TAF_MTA_RcvCtasMsg(struct MsgCB *pstMsg);

extern VOS_VOID TAF_MTA_RcvUsimmMsg(struct MsgCB *pstMsg);

#endif

VOS_VOID TAF_MTA_RcvRcmMsg(struct MsgCB *pstMsg);


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

#endif


