/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcMain.h
  版 本 号   : 初稿
  作    者   : zhoujun /40661
  生成日期   : 2011年3月30日
  最近修改   :
  功能描述   : NasMain.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年3月30日
    作    者   : zhoujun /40661
    修改内容   : 创建文件

******************************************************************************/

#ifndef _NAS_MMC_MAIN_
#define _NAS_MMC_MAIN_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "Nas_Mem.h"

#include "NasMmcCtx.h"
#include "NasMmcSndInternalMsg.h"

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

VOS_VOID NAS_MMC_InitTask( VOS_VOID );

VOS_UINT32 NAS_MMC_InitPid(
    enum VOS_INIT_PHASE_DEFINE          ip
);

VOS_UINT32 NAS_MMC_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pMsg
);

VOS_UINT32 NAS_MMC_PreProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pMsg
);


VOS_VOID NAS_MMC_RegMainL1Fsm( VOS_VOID  );


VOS_VOID NAS_MMC_RegL2Fsm( VOS_VOID  );


VOS_VOID NAS_MMC_RegPreFsm( VOS_VOID  );

VOS_UINT32 NAS_MMC_FSM_ProcessEvent(
    VOS_UINT32                          ulCurState,
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg
);

VOS_VOID  NAS_MMC_InitCtx(
    NAS_MMC_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    NAS_MMC_CONTEXT_STRU                *pstMmcCtx
);

VOS_VOID NAS_MMC_RestoreFsmStack(
    NAS_MMC_CONTEXT_STRU               *pstPcMmcCtx
);

VOS_VOID NAS_MMC_ReloadFsmDesc(
    NAS_MMC_FSM_CTX_STRU               *pstFsmCtx,
    VOS_UINT32                          ulPcRecurFsmId
);


VOS_UINT32  NAS_MMC_ProcMsgPrio(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID  NAS_MMC_MsgProc(
    struct MsgCB                       *pstMsg
);

VOS_VOID  NAS_MMC_RegFsm( VOS_VOID );

VOS_UINT32  NAS_MMC_IsNeedCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
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

#endif /* end of NasMmcMain.h */
