/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafFsm.h
  版 本 号   : 初稿
  作    者   : h44270
  生成日期   : 2011年12月17日
  最近修改   :
  功能描述   : TafFsm.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月17日
    作    者   : h44270
    修改内容   : 创建文件

******************************************************************************/
#ifndef _TAF_FSM_H_
#define _TAF_FSM_H_

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
#define TAF_FSM_NAME_LENGTH             (32)

/* 对PID,MsgName,以及EventType的操作 */
/*
    约束: PID结构 Bit0~Bit11: 模块ID  Bit12~Bit15: 保留 Bit16~Bit19: CPU ID Bit20~Bit31: 保留
    例: PID: 0x000A0BCD  ->  0x0000ABCD  ->  0xABCD0000
        MSG: 0x0000abcd
        EVT: 0xABCDabcd
*/
#define TAF_BuildEventType(ulSndPid,usMsgName) \
    (((VOS_UINT32)(/*lint -e778*/((ulSndPid) & 0xF0000)/*lint +e778*/ \
    | (((ulSndPid) & 0xFFF) << 4)) << 12) | (VOS_UINT16)(usMsgName))      /* 根据 Pid以及usMsgName 构建EventType  */

#define TAF_ExtractMsgNameFromEvtType(ulEventType)     ((VOS_UINT16)((ulEventType) & 0x0000FFFF))          /* 从EventType中获取MsgName     */
#define TAF_ExtractSndPidFromEvtType(ulEventType)  \
    ((((ulEventType) & 0xFFF0000) >> 16) | (((ulEventType) & 0xF0000000) >> 12))   /* 从EventType中获取SndPid      */

/* 状态机定义宏 */
#define TAF_STA_TBL_ITEM(ulState, astActTbl)\
{\
    ( ulState),\
    ((sizeof(astActTbl))/sizeof(TAF_ACT_STRU)),\
    (astActTbl)\
}

#define TAF_ACT_TBL_ITEM(PID, enMsgType, pActFun)\
{\
    (((VOS_UINT32)(/*lint -e778*/((PID) & 0xF0000)/*lint +e778*/ \
    | (((PID) & 0xFFF) << 4)) << 12) | (VOS_UINT16)(enMsgType)),\
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
typedef VOS_UINT32 ( * TAF_EXCEP_FUN )
(
    VOS_UINT32, /* EVENT ID,包括PID和MSG ID */
    VOS_VOID *  /* 消息指针 */
);

/* 状态机初始化处理函数的类型定义 */
typedef VOS_VOID ( * TAF_INIT_FUN )
(
    VOS_VOID
);


/* 动作处理函数的类型定义 */
typedef VOS_UINT32 (*TAF_ACTION_FUNC)(VOS_UINT32 ulEventType ,struct MsgCB* pMsg);


/* 动作表结构 */
typedef struct
{
    VOS_UINT32                          ulEventType;   /* 事件类型 */
    TAF_ACTION_FUNC                     pfActionFun;   /* 动作函数 */
}  TAF_ACT_STRU;


/* 状态转移表结构 */
typedef struct
{
    VOS_UINT32                          ulState;       /* 状态                                */
    VOS_UINT32                          ulSize;        /* 动作表的大小字节数除以ACT结构的大小 */
    TAF_ACT_STRU                       *pActTable;     /* 动作表的基地址                      */
}  TAF_STA_STRU;


/* 有限状态机描述符结构 */
typedef struct
{
    TAF_STA_STRU                       *pStaTable;                /* 状态转移表的基地址     */
    VOS_UINT32                          ulSize;                   /* 状态转移表的大小       */
    VOS_CHAR                            aucName[TAF_FSM_NAME_LENGTH]; /* 有限状态机的名字       */
    TAF_EXCEP_FUN                       pfExceptHandle;           /* 用于处理异常的回调函数 */
    TAF_INIT_FUN                        pfInitHandle;             /* 用于对每个状态机进行初始化的函数*/
}  TAF_FSM_DESC_STRU;


typedef VOS_INT (* TAF_FSM_COMP_FUNC)(const VOS_VOID*, const VOS_VOID*);

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

VOS_VOID TAF_FSM_RegisterFsm(
    TAF_FSM_DESC_STRU                  *pstFsmDesc,
    VOS_CHAR                           *pucName,
    VOS_UINT32                          ulSize,
    TAF_STA_STRU                       *pstStaTbl,
    TAF_EXCEP_FUN                       pfExceptHandle,
    TAF_INIT_FUN                        pfInitHandle
);

TAF_ACTION_FUNC TAF_FSM_FindAct(
    TAF_FSM_DESC_STRU                  *pstFsmDesc,
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
