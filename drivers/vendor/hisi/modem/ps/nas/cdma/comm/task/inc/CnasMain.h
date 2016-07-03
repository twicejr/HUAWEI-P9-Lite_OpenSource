
#ifndef _CNAS_MAIN_H_
#define _CNAS_MAIN_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "PsLogdef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* DMT 使用 */
#if (VOS_WIN32 == VOS_OS_VER)
#define CNAS_TASK_PRIO                                (137)
#endif

/* 具体消息size大小待定 */
#define CNAS_MAX_INTERNAL_MSG_LEN                     (1600)

/* queue消息size大小待定 */
#define CNAS_INTERNAL_MSG_MAX_QUEUE_SIZE              (10)

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



typedef struct
{
    VOS_UINT8                           ucIntMsgNum;                                /* 缓存消息的个数 */
    VOS_UINT8                           aucReserve[3];
    VOS_UINT8                          *pastIntMsg[CNAS_INTERNAL_MSG_MAX_QUEUE_SIZE]; /* CNAS的内部消息队列数组，存放消息指针 */
}CNAS_INTERNAL_MSG_CTX_STRU;

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
CNAS_INTERNAL_MSG_CTX_STRU *CNAS_GetIntMsgCtxAddr(VOS_VOID);

VOS_VOID CNAS_InitIntMsgCtx(VOS_VOID);

VOS_VOID CNAS_InitIntMsgBuf(
    CNAS_INTERNAL_MSG_CTX_STRU          *pstInternalMsgCtx
);

VOS_VOID *CNAS_GetIntMsgSendBuf(
    VOS_UINT32                          ulModuleId,
    VOS_UINT32                          ulBufLen
);

VOS_UINT32  CNAS_SndInternalMsg(
    VOS_VOID                           *pSndMsg
);

VOS_UINT8 *CNAS_GetNextInternalMsg(VOS_VOID);



VOS_VOID  CNAS_InitTask(VOS_VOID);

VOS_UINT32  CNAS_FidMsgProc(
    struct MsgCB                        *pRcvMsg
);

typedef VOS_VOID  (*pCnasPidMsgProc)(struct MsgCB* pMsg);
#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif
