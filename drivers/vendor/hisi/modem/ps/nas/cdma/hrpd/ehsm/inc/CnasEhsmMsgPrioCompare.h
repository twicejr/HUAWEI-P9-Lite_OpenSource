

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "CnasEhsmCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define TAF_MMA_UNIVERAL_MSG_ID                (0xFFFFFFFF)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum CNAS_EHSM_ABORT_FSM_TYPE
{
    CNAS_EHSM_ABORT_FSM_IMMEDIATELY           = 0,
    CNAS_EHSM_ABORT_FSM_DELAY                 = 1,
    CNAS_EHSM_ABORT_BUTT
};
typedef VOS_UINT8 CNAS_EHSM_ABORT_FSM_TYPE_UINT8;


enum CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ENUM
{
    CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT              ,                        /* 高优先级消息中断当前流程 */
    CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_STORE              ,                        /* 需要缓存的消息 */
    CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_INITFSM            ,                        /* 进入状态机中处理 */
    CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_DISCARD            ,                        /* 直接丢弃的消息 */

    CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_BUTT
};
typedef VOS_UINT32 CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32;

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


typedef VOS_UINT32 (*CNAS_EHSM_MSG_COMPARE_FUNC)(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);


typedef struct
{
    VOS_UINT32                          ulCurrEventType;        /* 需比较的消息 */
    CNAS_EHSM_MSG_COMPARE_FUNC          pfCompareFun;           /* 比较函数 */
}  CNAS_EHSM_MSG_COMPARE_STRU;


typedef struct
{
    CNAS_EHSM_FSM_ID_ENUM_UINT32        enFsmId;                /* 当前运行的FSM ID */
    VOS_UINT32                          ulSize;                 /* 动作表的大小字节数除以ACT结构的大小 */
    CNAS_EHSM_MSG_COMPARE_STRU         *pfCompareTbl;           /* 比较函数表 */
}  CNAS_EHSM_FSM_MSG_COMPARE_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32 CNAS_EHSM_GetMsgComparePrioRslt(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);



#define CNAS_EHSM_COMPARE_TBL_ITEM(ulCurrMsgType, pCompareFun)\
{\
    (ulCurrMsgType),\
    ((pCompareFun))\
}


#define CNAS_EHSM_FSM_COMPARE_TBL_ITEM(enFsmId, astFsmCompareTbl)\
{\
    ( enFsmId),\
    ((sizeof(astFsmCompareTbl))/sizeof(CNAS_EHSM_MSG_COMPARE_STRU)),\
    (astFsmCompareTbl)\
}

VOS_UINT32 CNAS_EHSM_CompareHsdPowerOffReqPrioWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);
VOS_UINT32 CNAS_EHSM_CompareHsdPowerOffReqPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);

CNAS_EHSM_MSG_COMPARE_FUNC  CNAS_EHSM_FindMsgPrioCompareFun(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_FSM_ID_ENUM_UINT32        enFsmId
);

VOS_UINT32 CNAS_EHSM_CompareHsmSuspendIndPrioWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);
VOS_UINT32 CNAS_EHSM_CompareHsmSuspendIndPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);

VOS_UINT32 CNAS_EHSM_CompareCttfEhrpdDetachIndPrioWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);
VOS_UINT32 CNAS_EHSM_CompareTafPdnDeactivateReqWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);
VOS_UINT32 CNAS_EHSM_CompareTafPdnReconnReqWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);
VOS_UINT32 CNAS_EHSM_CompareTafPdnActivateReqWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);
VOS_UINT32 CNAS_EHSM_CompareTafLocalDetachNotifyWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);
VOS_UINT32 CNAS_EHSM_CompareTafLocalDeactivateNotifyWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);

VOS_UINT32 CNAS_EHSM_CompareCttfEhrpdDetachIndPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);

VOS_UINT32 CNAS_EHSM_CompareTafPdnActivateReqPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);
VOS_UINT32 CNAS_EHSM_CompareTafPdnDeactivateReqPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);
VOS_UINT32 CNAS_EHSM_CompareTafReconnReqPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);
VOS_UINT32 CNAS_EHSM_CompareTafLocalDetachNotifyPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);
VOS_UINT32 CNAS_EHSM_CompareTafLocalDeactivateNotifyWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);

VOS_UINT32 CNAS_EHSM_CompareHsmSessionInfoIndPrioWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);

VOS_UINT32 CNAS_EHSM_CompareHsmSessionInfoIndPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);

VOS_UINT32 CNAS_EHSM_CompareTafDiscNotifyPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
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


