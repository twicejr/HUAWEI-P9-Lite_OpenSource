

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#ifndef _CSD_CTX_H_
#define _CSD_CTX_H_


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "PsLogdef.h"
#include "ImmInterface.h"
#include "DiccInterface.h"
#include "AtCsdInterface.h"
#include "CsdLog.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



#pragma pack(4)

#if( FEATURE_ON == FEATURE_CSD )


/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*默认slice值，ulTxSlice初始化时使用*/
#define CSD_DEFAULT_TX_SLICE    (0)

/*The count number of the semaphore that create*/
#define CSD_SEMAPHORE_INIT_CNT  (0)
/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
  2 全局变量定义
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
结构名    : CSD_CTX_STRU
结构说明  : CSD的上下文

  1.日    期   : 2011年12月6日
    作    者   : w00199382
    修改内容   : 新增结构
  2.日    期   : 2013年05月28日
    作    者   : f00179208
    修改内容   : V3R3 PPP PROJECT
*****************************************************************************/

typedef struct
{
    VOS_SEM                             hULdataSem;                             /*上行数据信号量*/
    VOS_SEM                             hDLdataSem;                             /*下行数据信号量*/
    VOS_UINT32                          ulLastDICCIsrSlice;                     /*记录DICC中断SLICE*/
    AT_CSD_CALL_TYPE_STATE_ENUM_UINT16  enCallState;                            /*记录当前通话状态*/
    VOS_UINT8                           ucAtClientIndex;                        /* AT Client Index */
    VOS_UINT8                           aucReserved[1];
    IMM_ZC_HEAD_STRU                   *pstULQueue;                             /*上行缓存队列*/
    VOS_SPINLOCK                        stSpinLock;
}CSD_CTX_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/

AT_CSD_CALL_TYPE_STATE_ENUM_UINT16 CSD_GetCallState(VOS_VOID);
VOS_SEM CSD_GetDownLinkDataSem(VOS_VOID);
VOS_UINT32 CSD_GetLastTxSlice(VOS_VOID);
VOS_SEM CSD_GetUpLinkDataSem(VOS_VOID);
VOS_UINT32 CSD_InitCtx(VOS_VOID);
VOS_UINT32 CSD_InitSem(VOS_VOID);
VOS_VOID CSD_SetCallState(AT_CSD_CALL_TYPE_STATE_ENUM_UINT16 enCallState);
VOS_VOID CSD_SetCurrTxSlice(VOS_UINT32 ulCurrSlice);
VOS_UINT32 CSD_UL_FreeQueue(IMM_ZC_HEAD_STRU *pstQueue);
IMM_ZC_HEAD_STRU *CSD_UL_GetQueue(VOS_VOID);
VOS_VOID CSD_UL_SetQueue(IMM_ZC_HEAD_STRU *pstULQueue);
VOS_UINT32 CSD_UL_InsertQueueTail(
    IMM_ZC_HEAD_STRU                    *pstQueueHead,
    IMM_ZC_STRU                         *pData
);
IMM_ZC_STRU  *CSD_UL_GetQueueFrontNode(IMM_ZC_HEAD_STRU *pstQueue);

VOS_UINT8 CSD_UL_GetAtClientIndex(VOS_VOID);
VOS_VOID CSD_UL_SetAtClientIndex(VOS_UINT8 ucIndex);

#endif /*FEATURE_ON == FEATURE_CSD*/

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

