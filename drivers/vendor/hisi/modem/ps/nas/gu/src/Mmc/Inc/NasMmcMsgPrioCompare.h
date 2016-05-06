/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcMsgCompare.h
  版 本 号   : 初稿
  作    者   : zhoujun 40661
  生成日期   : 2011年9月27日
  最近修改   :
  功能描述   : NasMmcMsgCompare.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年9月27日
    作    者   : zhoujun 40661
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "PsTypeDef.h"
#include  "NasMmcCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NAS_MMC_UNIVERAL_MSG_ID                (0xFFFFFFFF)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : NAS_MMC_MSG_PRIO_ENUM
 结构说明  : MMC消息优先级比较的结果
 1.日    期   : 2011年4月28日
   作    者   : zhoujun 40661
   修改内容   : 新建
 1.日    期   : 2011年7月14日
   作    者   : w00167002
   修改内容   : V7R1 PHASEII 重构: 更新为UINT32位
*****************************************************************************/
enum NAS_MMC_MSG_COMPARE_PRIO_RSLT_ENUM
{
    NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT  ,                                       /* 高优先级消息中断当前流程 */
    NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE              ,                          /* 需要缓存的消息 */
    NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM            ,                         /* 进入状态机中处理 */
    NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD            ,                          /* 直接丢弃的消息 */

    NAS_MMC_MSG_COMPARE_PRIO_RSLT_BUTT
};
typedef VOS_UINT32 NAS_MMC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32;

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
 结构名    : NAS_MMC_MSG_COMPARE_FUNC
 结构说明  : 优先级比较处理函数的类型定义
 1.日    期   : 2011年9月28日
   作    者   : zhoujun \40661
   修改内容   : 新增
*****************************************************************************/
typedef VOS_UINT32 (*NAS_MMC_MSG_COMPARE_FUNC)(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

/*****************************************************************************
 结构名    : NAS_MMC_MSG_COMPARE_STRU
 结构说明  : 比较函数结构
 1.日    期   : 2011年9月28日
   作    者   : zhoujun \40661
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCurrEventType;        /* 需比较的消息 */
    NAS_MMC_MSG_COMPARE_FUNC            pfCompareFun;           /* 比较函数 */
}  NAS_MMC_MSG_COMPARE_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_MSG_COMPARE_STRU
 结构说明  : 比较函数结构
 1.日    期   : 2011年9月28日
   作    者   : zhoujun \40661
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;                /* 当前运行的FSM ID */
    VOS_UINT32                          ulSize;                 /* 动作表的大小字节数除以ACT结构的大小 */
    NAS_MMC_MSG_COMPARE_STRU           *pfCompareTbl;           /* 比较函数表 */
}  NAS_MMC_FSM_MSG_COMPARE_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

/*****************************************************************************
 结构名    : NAS_MMC_COMPARE_TBL_ITEM
 结构说明  : 每个单个状态机比较函数表结构
 1.日    期   : 2011年9月28日
   作    者   : zhoujun \40661
   修改内容   : 新增
*****************************************************************************/

#define NAS_MMC_COMPARE_TBL_ITEM(ulCurrMsgType, pCompareFun)\
{\
    (ulCurrMsgType),\
    ((pCompareFun))\
}

/*****************************************************************************
 结构名    : NAS_MMC_COMPARE_TBL_ITEM
 结构说明  : 比较函数表结构
 1.日    期   : 2011年9月28日
   作    者   : zhoujun \40661
   修改内容   : 新增
*****************************************************************************/
#define NAS_MMC_FSM_COMPARE_TBL_ITEM(enFsmId, astFsmCompareTbl)\
{\
    ( enFsmId),\
    ((sizeof(astFsmCompareTbl))/sizeof(NAS_MMC_MSG_COMPARE_STRU)),\
    (astFsmCompareTbl)\
}

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_MMC_IsTrigerDisableLte_MoDetach(
    MSCC_MMC_DETACH_REQ_STRU           *pstDetachReq
);
#endif

VOS_UINT32 NAS_MMC_CompareMmcMsgPrioWithInterSysCco(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareMmcMsgPrioWithInterSysHo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareUserPlmnSpecPrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareSysCfgSetPrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_ComparePowerOffPrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_ComparePowerSavePrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareDetachReqPrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_ComparePlmnSearchIndPrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);
VOS_UINT32 NAS_MMC_CompareMmcMsgPrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);


VOS_UINT32 NAS_MMC_ComparePowerOffPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareUserReselPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);


VOS_UINT32 NAS_MMC_CompareUserPlmnListPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

#if (FEATURE_ON == FEATURE_CSG)
VOS_UINT32 NAS_MMC_CompareUserCsgListPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);
VOS_UINT32 NAS_MMC_CompareUserCsgListPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);
VOS_UINT32 NAS_MMC_CompareUserCsgListPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);
VOS_UINT32 NAS_MMC_CompareUserCsgListPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);
#endif
VOS_UINT32 NAS_MMC_CompareUserPlmnSpecPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareSysCfgSetPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareTiAvailableTimerExpiredPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareTiForbidLaTimerExpiredPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_ComparePowerOffPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

/* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
VOS_UINT32 NAS_MMC_ComparePowerSavePrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareAcqReqPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareRegReqPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);
/* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

/* Added by c00318887 for 预置频点搜网优化, 2015-9-10, begin */
VOS_UINT32 NAS_MMC_ComparePlmnSearchPhaseOneTotalTimePrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);
VOS_UINT32 NAS_MMC_CompareDplmnSetReqPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);
VOS_UINT32 NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimePrioWithAnyCellSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);
VOS_UINT32 NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);
VOS_UINT32 NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

/* Added by c00318887 for 预置频点搜网优化, 2015-9-10, end */

#if (FEATURE_ON == FEATURE_DSDS)
VOS_UINT32 NAS_MMC_CompareSrvAcqReqPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);
VOS_UINT32 NAS_MMC_CompareSrvAcqReqPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);
VOS_UINT32 NAS_MMC_CompareSrvAcqReqPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);
VOS_UINT32 NAS_MMC_CompareSrvAcqReqPrioWithAnyCellSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

#endif

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_MMC_CompareCsfbAbortIndPrioWithAnyCellSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);
#endif


VOS_UINT32 NAS_MMC_CompareSysCfgSetPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareUserReselPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareUserPlmnListPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareUserPlmnSpecPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareCmServiceIndPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareMmcMsgPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_ComparePowerOffPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

/* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
VOS_UINT32 NAS_MMC_ComparePowerSavePrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareAcqReqPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareRegReqPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);
/* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

VOS_UINT32 NAS_MMC_CompareSysCfgSetPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareUserReselPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareUserPlmnSpecPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32  NAS_MMC_CompareUserPlmnListPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32  NAS_MMC_CompareUserDetachReqPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32  NAS_MMC_CompareSuspendIndPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareRrmPsStatusIndPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32  NAS_MMC_CompareLmmSuspendIndPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);
#endif

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-13, begin */
VOS_UINT32 NAS_MMC_CompareCmServiceIndPrioWithAnyCellSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-13, end */

VOS_UINT32 NAS_MMC_ComparePoweroffPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);


/* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
VOS_UINT32 NAS_MMC_ComparePowerSavePrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareAcqReqPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareRegReqPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);
/* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

VOS_UINT32 NAS_MMC_CompareUserPlmnListPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);


VOS_UINT32  NAS_MMC_CompareUserReselPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareStkRoamingIndPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareUserPlmnSpecPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareUsimRefreshPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareMsccUpdateUplmnNtfPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);
VOS_UINT32  NAS_MMC_CompareSuspendIndPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);


VOS_UINT32 NAS_MMC_CompareSysCfgSetPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32  NAS_MMC_CompareUserDetachReqPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32  NAS_MMC_CompareLmmSuspendIndPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareCsfbAbortIndPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_ComparePlmnSearchIndPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_ComparePlmnSearchIndPrioWithAnyCellSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);


/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-13, begin */
VOS_UINT32 NAS_MMC_CompareLmmServiceResultIndPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32  NAS_MMC_CompareLmmServiceResultIndPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);


VOS_UINT32  NAS_MMC_CompareLmmServiceResultIndPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-13, end */
#endif


NAS_MMC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32 NAS_MMC_GetMsgComparePrioRslt(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 NAS_MMC_CompareCmServiceIndPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);


VOS_UINT32 NAS_MMC_CompareMmcNvimOPlmnRefreshIndPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);
VOS_UINT32 NAS_MMC_ComparePowerOffPrioWithGetGeo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
);
VOS_UINT32 NAS_MMC_CompareRrmPsStatusIndPrioWithPowerOff(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
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

