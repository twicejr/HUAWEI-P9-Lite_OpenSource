

#ifndef __CNAS_XREG_CTX_H__
#define __CNAS_XREG_CTX_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "PsCommonDef.h"
#include  "NasFsm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 状态机栈的深度 */
#define CNAS_XREG_MAX_FSM_STACK_DEPTH                       (4)

/* 消息的最大长度，包括状态机保存的入口消息和CACHE消息 */
#define CNAS_XREG_MAX_MSG_BUFFER_LEN                        (1600)

/* 缓存消息队列的最大个数 */
#define CNAS_XREG_MAX_CACHE_MSG_QUEUE_NUM                   (8)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


enum CNAS_XREG_FSM_ID_ENUM
{
    /***********************************************************************
     * XREG L1状态机标识
     ***********************************************************************/
    /* L1 main状态机的标识 */
    CNAS_XREG_FSM_L1_MAIN                                   = 0x00,

    /***********************************************************************
     * XREG L2状态机的标识
     ***********************************************************************/
    /* L2 开机状态机 */
    CNAS_XREG_FSM_SWITCH_ON                                 = 0x01,

    /* L2 注册状态机 */
    CNAS_XREG_FSM_REGING                                    = 0x02,

    CNAS_XREG_FSM_BUTT
};
typedef VOS_UINT32 CNAS_XREG_FSM_ID_ENUM_UINT32;


enum   CNAS_XREG_READ_CARD_FILES_CNF_ENUM
{
    CNAS_XREG_READ_CARD_FILE_FLG_NULL                       = 0x00,             /* 初始值 */

    CNAS_XREG_READ_CARD_FILE_TERM_FLG                       = 0x01,             /* EFterm文件 */

    CNAS_XREG_READ_CARD_FILE_SSCI_FLG                       = 0x02,             /* EFssci文件 */

    CNAS_XREG_READ_CARD_FILE_CNF_BUTT
};

typedef VOS_UINT32 CNAS_XREG_READ_CARD_FILES_CNF_ENUM_UINT32;


enum   CNAS_XREG_REFRESH_CARD_FILES_IND_ENUM
{
    CNAS_XREG_REFRESH_CARD_FILE_FLG_NULL                       = 0x00,             /* 初始值 */

    CNAS_XREG_REFRESH_CARD_FILE_TERM_FLG                       = 0x01,             /* EFterm文件 */

    CNAS_XREG_REFRESH_CARD_FILE_SSCI_FLG                       = 0x02,             /* EFssci文件 */

    CNAS_XREG_REFRESH_CARD_FILE_SSCI_TERM_FLG                  = 0x03,             /* EFterm and EFssci文件 */

    CNAS_XREG_REFRESH_CARD_FILE_CNF_BUTT
};

typedef VOS_UINT32 CNAS_XREG_REFRESH_CARD_FILES_IND_ENUM_UINT32;


enum   CNAS_XREG_CARD_FILES_CHANGE_ENUM
{
    CNAS_XREG_CARD_FILE_CHANGE_FLG_NULL                       = 0x00,             /* 初始值 */

    CNAS_XREG_CARD_FILE_TERM_CHANGE_FLG                       = 0x01,             /* EFterm文件 */

    CNAS_XREG_CARD_FILE_SSCI_CHANGE_FLG                       = 0x02,             /* EFssci文件 */

    CNAS_XREG_CARD_FILE_SSCI_TERM_CHANGE_FLG                  = 0x03,             /* EFterm and EFssci文件 */

    CNAS_XREG_CARD_FILE_CNF_BUTT
};

typedef VOS_UINT32 CNAS_XREG_CARD_FILES_CHANGE_ENUM_UINT32;

typedef struct
{
    CNAS_XREG_REFRESH_CARD_FILES_IND_ENUM_UINT32        enRefreshReadCard;               /* Refresh Card Ind 读卡消息回复 */
    CNAS_XREG_CARD_FILES_CHANGE_ENUM_UINT32             enCardFileChange;        /* 卡文件变化 */
}CNAS_XREG_REFRESH_CARD_FILES_STATUS_STRU;


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
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           aucMsgBuffer[CNAS_XREG_MAX_MSG_BUFFER_LEN];
}CNAS_XREG_MSG_STRU;


typedef struct
{
    VOS_UINT32                          ulCurrIndex;                            /* 记录当前处理缓存的index */
    VOS_UINT8                           ucCacheMsgNum;                          /* 缓存消息的个数 */
    VOS_UINT8                           aucReserve[3];
    VOS_UINT8                          *pastCacheMsg[CNAS_XREG_MAX_CACHE_MSG_QUEUE_NUM]; /* XREG的消息队列数组指针，存储的是带通用消息头的消息 */
}CNAS_XREG_CACHE_MSG_QUEUE_STRU;


typedef struct
{
    CNAS_XREG_REFRESH_CARD_FILES_STATUS_STRU            stXregRefreshCardFileStatus;
}CNAS_XREG_PREPROC_CTX_STRU;


typedef struct
{
    /* 本次迭代不涉及 */
    VOS_UINT8                           aucRsved[4];
}CNAS_XREG_FSM_REGISTER_CTX_STRU;


typedef struct
{
    /* 本次迭代不涉及 */
    VOS_UINT8                           aucRsved[4];
}CNAS_XREG_FSM_L1_MAIN_CTX_STRU;


typedef struct
{
    VOS_UINT32                          ulXregReadCardFileFlg;                  /* 标记卡文件是否读取完成 */
    VOS_UINT8                           aucReserved[4];
}CNAS_XREG_FSM_SWITCH_ON_CTX_STRU;


typedef union
{
    CNAS_XREG_FSM_REGISTER_CTX_STRU     stRegisterCtx;

    CNAS_XREG_FSM_L1_MAIN_CTX_STRU      stL1MainCtx;

    CNAS_XREG_FSM_SWITCH_ON_CTX_STRU    stSwitchOnCtx;
}CNAS_XREG_FSM_EXTRA_CTX_UNION;


typedef struct
{
    /* 状态机描述指针,指针为NULL表示当前状态机无效  */
    NAS_FSM_DESC_STRU                  *pstFsmDesc;

    /* 当前状态机标识 */
    CNAS_XREG_FSM_ID_ENUM_UINT32        enFsmId;

    /* 上层状态机标识 */
    CNAS_XREG_FSM_ID_ENUM_UINT32        enParentFsmId;

    /* 上层状态机入口消息类型 */
    VOS_UINT32                          ulParentEventType;

    /* 当前状态 */
    VOS_UINT32                          ulState;

    /* 入口消息MSGID和内容  */
    CNAS_XREG_MSG_STRU                  stEntryMsg;

    /* 状态机数据 */
    CNAS_XREG_FSM_EXTRA_CTX_UNION       unFsmCtx;
}CNAS_XREG_FSM_CTX_STRU;


typedef struct
{
    VOS_UINT16                          usStackDepth;                           /* 当前压栈的状态机数 */
    VOS_UINT16                          usStackPopFlg;                          /* 当前栈pop标志 */
    CNAS_XREG_FSM_CTX_STRU              astFsmStack[CNAS_XREG_MAX_FSM_STACK_DEPTH];  /* 状态机栈的深度 */
}CNAS_XREG_FSM_STACK_STRU;



typedef struct
{
    /* 预处理 */
    CNAS_XREG_PREPROC_CTX_STRU          stRegPreProcCtx;

    /**************************************************************************
                        CNAS XREG状态机状态及其状态栈
     **************************************************************************/
    CNAS_XREG_FSM_CTX_STRU              stCurFsm;                               /* 状态机当前的状态机数组 */
    CNAS_XREG_FSM_STACK_STRU            stFsmStack;                             /* 状态机的状态机栈数组   */

    /* CNAS XREG缓存消息队列 */
    CNAS_XREG_CACHE_MSG_QUEUE_STRU      stCacheMsgQueue;
}CNAS_XREG_CTX_STRU;


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

VOS_UINT32 CNAS_XREG_GetFsmTopState(VOS_VOID);

CNAS_XREG_CTX_STRU* CNAS_XREG_GetCtxAddr(VOS_VOID);
CNAS_XREG_FSM_CTX_STRU* CNAS_XREG_GetCurFsmAddr(VOS_VOID);
NAS_FSM_DESC_STRU* CNAS_XREG_GetCurFsmDesc(VOS_VOID);
CNAS_XREG_FSM_ID_ENUM_UINT32 CNAS_XREG_GetCurrFsmId(VOS_VOID);
CNAS_XREG_MSG_STRU* CNAS_XREG_GetCurrFsmEntryMsgAddr(VOS_VOID);
CNAS_XREG_FSM_STACK_STRU* CNAS_XREG_GetFsmStackAddr(VOS_VOID);
VOS_VOID CNAS_XREG_SetCurrFsmState(
    VOS_UINT32                          ulCurrState
);

VOS_UINT16  CNAS_XREG_GetFsmStackDepth(VOS_VOID);
VOS_UINT32  CNAS_XREG_GetNextCachedMsg(
    CNAS_XREG_MSG_STRU                 *pstEntryMsg
);
VOS_VOID  CNAS_XREG_SetFsmStackPopFlg(
    VOS_UINT16                          ucStackPopFlg
);
VOS_UINT16  CNAS_XREG_GetFsmStackPopFlg(VOS_VOID);
VOS_UINT32  CNAS_XREG_GetCacheMsgNum(VOS_VOID);
CNAS_XREG_CACHE_MSG_QUEUE_STRU* CNAS_XREG_GetCacheMsgAddr(VOS_VOID);

VOS_VOID CNAS_XREG_InitCtx(VOS_VOID);
VOS_VOID CNAS_XREG_InitFsmCtx_L1Main(VOS_VOID);

VOS_VOID CNAS_XREG_PushFsm(
    CNAS_XREG_FSM_STACK_STRU           *pstFsmStack,
    CNAS_XREG_FSM_CTX_STRU             *pstNewFsm
);

VOS_VOID CNAS_XREG_InitFsmL2(
    CNAS_XREG_FSM_ID_ENUM_UINT32        enFsmId
);

VOS_VOID CNAS_XREG_QuitFsmL2(VOS_VOID);

VOS_VOID CNAS_XREG_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID  CNAS_XREG_SaveMsgToCache(
    VOS_UINT32                          ulEventType,
    VOS_UINT8                           *pucMsg
);
 
VOS_VOID  CNAS_XREG_LoadSubFsm(
    CNAS_XREG_FSM_ID_ENUM_UINT32         enFsmId,
    CNAS_XREG_FSM_CTX_STRU              *pstCurFsm
);

VOS_VOID CNAS_XREG_ClearCacheMsg(VOS_VOID);

VOS_VOID CNAS_XREG_InitFsmCtx_SwitchOn(VOS_VOID);

CNAS_XREG_READ_CARD_FILES_CNF_ENUM_UINT32 CNAS_XREG_GetWaitCardFilesCnfFlg_SwitchOn(VOS_VOID);

VOS_VOID CNAS_XREG_SetWaitCardFilesCnfFlg_SwitchOn(
    CNAS_XREG_READ_CARD_FILES_CNF_ENUM_UINT32               enReadCardFileCnfFlg
);

VOS_VOID CNAS_XREG_ClearWaitCardFilesCnfFlg_SwitchOn(
    CNAS_XREG_READ_CARD_FILES_CNF_ENUM_UINT32               enReadCardFileCnfFlg
);

CNAS_XREG_REFRESH_CARD_FILES_IND_ENUM_UINT32 CNAS_XREG_GetReadCardFilesIndFlg(VOS_VOID);

VOS_VOID CNAS_XREG_SetReadCardFilesIndFlg(
    CNAS_XREG_REFRESH_CARD_FILES_IND_ENUM_UINT32    enRefreshReadCard
);

VOS_VOID CNAS_XREG_ClearReadCardFilesIndFlg(
    VOS_UINT32                          ulEfId
);

CNAS_XREG_CARD_FILES_CHANGE_ENUM_UINT32 CNAS_XREG_GetCardFilesChangeFlg(VOS_VOID);

VOS_VOID CNAS_XREG_SetCardFilesChangeFlg(
    CNAS_XREG_CARD_FILES_CHANGE_ENUM_UINT32    enCardFileChange
);

VOS_VOID CNAS_XREG_ClearRefreshCardFilesCtx(VOS_VOID);

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

#endif /* end of CnasXregCtx.h */
