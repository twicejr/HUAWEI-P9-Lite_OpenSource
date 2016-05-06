/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasEhsmMsgPrioCompare.h
  版 本 号   : 初稿
  作    者   : h00246512
  生成日期   : 2015年5月27日
  最近修改   :
  功能描述   : CnasEhsmMsgPrioCompare.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年5月27日
    作    者   : h00246512
    修改内容   : 创建文件

******************************************************************************/

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
/*****************************************************************************
 枚举名    : CNAS_EHSM_ABORT_FSM_TYPE_UINT8
 结构说明  : Abort类型
 1.日    期   : 2015年5月27日
   作    者   : h00246512
   修改内容   : 新增
*****************************************************************************/
enum CNAS_EHSM_ABORT_FSM_TYPE
{
    CNAS_EHSM_ABORT_FSM_IMMEDIATELY           = 0,
    CNAS_EHSM_ABORT_FSM_DELAY                 = 1,
    CNAS_EHSM_ABORT_BUTT
};
typedef VOS_UINT8 CNAS_EHSM_ABORT_FSM_TYPE_UINT8;

/*****************************************************************************
 枚举名    : CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ENUM
 结构说明  : EHSM消息优先级比较的结果
 1.日    期   : 2015年5月27日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
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

/*****************************************************************************
 结构名    : CNAS_EHSM_MSG_COMPARE_FUNC
 结构说明  : 优先级比较处理函数的类型定义
 1.日    期   : 2013年7月22日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/
typedef VOS_UINT32 (*CNAS_EHSM_MSG_COMPARE_FUNC)(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
);

/*****************************************************************************
 结构名    : CNAS_EHSM_MSG_COMPARE_STRU
 结构说明  : 比较函数结构
 1.日    期   : 2013年7月22日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCurrEventType;        /* 需比较的消息 */
    CNAS_EHSM_MSG_COMPARE_FUNC          pfCompareFun;           /* 比较函数 */
}  CNAS_EHSM_MSG_COMPARE_STRU;

/*****************************************************************************
 结构名    : CNAS_EHSM_MSG_COMPARE_STRU
 结构说明  : 比较函数结构
 1.日    期   : 2013年7月22日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/
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


/*****************************************************************************
 结构名    : CNAS_EHSM_COMPARE_TBL_ITEM
 结构说明  : 每个单个状态机比较函数表结构
 1.日    期   : 2015年5月27日
   作    者   : h00246512
   修改内容   : 新增
*****************************************************************************/
#define CNAS_EHSM_COMPARE_TBL_ITEM(ulCurrMsgType, pCompareFun)\
{\
    (ulCurrMsgType),\
    ((pCompareFun))\
}

/*****************************************************************************
 结构名    : CNAS_EHSM_FSM_COMPARE_TBL_ITEM
 结构说明  : 比较函数表结构
 1.日    期   : 2013年7月22日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/
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


