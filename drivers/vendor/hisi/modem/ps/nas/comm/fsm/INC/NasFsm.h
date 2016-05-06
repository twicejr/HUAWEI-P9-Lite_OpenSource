/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasFsm.h
  版 本 号   : 初稿
  作    者   : zhoujun /40661
  生成日期   : 2010年11月12日
  最近修改   :
  功能描述   : MMC_Main.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2010年11月12日
    作    者   : zhoujun /40661
    修改内容   : 创建文件

  2.日    期   : 2011年5月9日
    作    者   : zhoujun 40661
    修改内容   : V7R1 Phase I修改
******************************************************************************/
#ifndef _NAS_FSM_H_
#define _NAS_FSM_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NAS_FSM_NAME_LENGTH             (32)

#define NAS_BuildCurState(usMainState,usSubState)   (((VOS_UINT32)(usMainState) << 16) | (usSubState))                  /* 根据 主状态，子状态，构建CurState */


/* 状态机定义宏 */
#define NAS_STA_TBL_ITEM(ulState, astActTbl)\
{\
    ( ulState),\
    ((sizeof(astActTbl))/sizeof(NAS_ACT_STRU)),\
    (astActTbl)\
}

#define NAS_MUTI_STA_TBL_ITEM(enMainState, enSubState, astActTbl)\
{\
    (((enMainState) << 16) | (enSubState)),\
    ((sizeof(astActTbl))/sizeof(NAS_ACT_STRU)),\
    (astActTbl)\
}


#define NAS_ACT_TBL_ITEM(PID, enMsgType, pActFun)\
{\
    (((VOS_UINT32)(/*lint -e778*/((PID) & 0xF0000)/*lint +e778*/ \
    | (((PID) & 0xFFF) << 4)) << 12) | (enMsgType)),\
    ((pActFun))\
}

/*****************************************************************************
  3 枚举定义
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

/* 异常处理函数的类型定义 */
typedef VOS_UINT32 ( * NAS_EXCEP_FUN )
(
    VOS_UINT32, /* EVENT ID,包括PID和MSG ID */
    VOS_VOID *  /* 消息指针 */
);

/* 状态机初始化处理函数的类型定义 */
typedef VOS_VOID ( * NAS_INIT_FUN )
(
    VOS_VOID
);


/* 动作处理函数的类型定义 */
typedef VOS_UINT32 (*NAS_ACTION_FUNC)(VOS_UINT32 ulEventType ,struct MsgCB* pMsg);


/* 动作表结构 */
typedef struct
{
    VOS_UINT32                          ulEventType;   /* 事件类型 */
    NAS_ACTION_FUNC                     pfActionFun;   /* 动作函数 */
}  NAS_ACT_STRU;


/* 状态转移表结构 */
typedef struct
{
    VOS_UINT32                          ulState;       /* 状态                                */
    VOS_UINT32                          ulSize;        /* 动作表的大小字节数除以ACT结构的大小 */
    NAS_ACT_STRU                       *pActTable;     /* 动作表的基地址                      */
}  NAS_STA_STRU;


/* 有限状态机描述符结构 */
typedef struct
{
    NAS_STA_STRU                       *pStaTable;                /* 状态转移表的基地址     */
    VOS_UINT32                          ulSize;                   /* 状态转移表的大小       */
    VOS_CHAR                            aucName[NAS_FSM_NAME_LENGTH]; /* 有限状态机的名字       */
    NAS_EXCEP_FUN                       pfExceptHandle;           /* 用于处理异常的回调函数 */
    NAS_INIT_FUN                        pfInitHandle;             /* 用于对每个状态机进行初始化的函数*/
}  NAS_FSM_DESC_STRU;


typedef VOS_INT (* NAS_FSM_COMP_FUNC)(const VOS_VOID*, const VOS_VOID*);

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

VOS_VOID NAS_FSM_RegisterFsm(
    NAS_FSM_DESC_STRU                   *pstFsmDesc,
    VOS_CHAR                            *pucName,
    VOS_UINT32                          ulSize,
    NAS_STA_STRU                        *pstStaTbl,
    NAS_EXCEP_FUN                       pfExceptHandle,
    NAS_INIT_FUN                        pfInitHandle
);

NAS_ACTION_FUNC NAS_FSM_FindAct(
    NAS_FSM_DESC_STRU                   *pstFsmDesc,
    VOS_UINT32                          ulState,
    VOS_UINT32                          ulEventType
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

#endif /* end of NasFsm.h */
