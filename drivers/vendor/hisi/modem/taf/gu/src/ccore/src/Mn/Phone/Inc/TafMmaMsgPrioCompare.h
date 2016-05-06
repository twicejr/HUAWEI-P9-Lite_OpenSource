/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaMsgPrioCompare.h
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2013年7月22日
  最近修改   :
  功能描述   : TafMmaMsgPrioCompare.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年7月22日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "PsTypeDef.h"
#include  "TafMmaCtx.h"

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
 枚举名    : TAF_MMA_ABORT_FSM_TYPE_UINT8
 结构说明  : Abort类型
 1.日    期   : 2013年7月22日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/
enum TAF_MMA_ABORT_FSM_TYPE
{
    TAF_MMA_ABORT_FSM_IMMEDIATELY           = 0,
    TAF_MMA_ABORT_FSM_DELAY                 = 1,
    TAF_MMA_ABORT_BUTT
};
typedef VOS_UINT8 TAF_MMA_ABORT_FSM_TYPE_UINT8;

/*****************************************************************************
 枚举名    : TAF_MMA_MSG_COMPARE_PRIO_RSLT_ENUM
 结构说明  : MMa消息优先级比较的结果
 1.日    期   : 2013年7月22日
   作    者   : w00176964
   修改内容   : 新建

 2.日    期   : 2015年4月8日
   作    者   : y00245242
   修改内容   : iteration 13开发

*****************************************************************************/
enum TAF_MMA_MSG_COMPARE_PRIO_RSLT_ENUM
{
    TAF_MMA_MSG_COMPARE_PRIO_RSLT_ABORT              ,                          /* 高优先级消息中断当前流程 */
    TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE              ,                          /* 需要缓存的消息 */
    TAF_MMA_MSG_COMPARE_PRIO_RSLT_INITFSM            ,                          /* 进入状态机中处理 */
    TAF_MMA_MSG_COMPARE_PRIO_RSLT_DISCARD            ,                          /* 直接丢弃的消息 */

    TAF_MMA_MSG_COMPARE_PRIO_RSLT_REJECT             ,                          /* 拒绝当前的用户请求 */

    TAF_MMA_MSG_COMPARE_PRIO_RSLT_BUTT
};
typedef VOS_UINT32 TAF_MMA_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32;

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
 结构名    : TAF_MMA_MSG_COMPARE_FUNC
 结构说明  : 优先级比较处理函数的类型定义
 1.日    期   : 2013年7月22日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/
typedef VOS_UINT32 (*TAF_MMA_MSG_COMPARE_FUNC)(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);

/*****************************************************************************
 结构名    : TAF_MMA_MSG_COMPARE_STRU
 结构说明  : 比较函数结构
 1.日    期   : 2013年7月22日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCurrEventType;        /* 需比较的消息 */
    TAF_MMA_MSG_COMPARE_FUNC            pfCompareFun;           /* 比较函数 */
}  TAF_MMA_MSG_COMPARE_STRU;

/*****************************************************************************
 结构名    : TAF_MMA_MSG_COMPARE_STRU
 结构说明  : 比较函数结构
 1.日    期   : 2013年7月22日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    TAF_MMA_FSM_ID_ENUM_UINT32          enFsmId;                /* 当前运行的FSM ID */
    VOS_UINT32                          ulSize;                 /* 动作表的大小字节数除以ACT结构的大小 */
    TAF_MMA_MSG_COMPARE_STRU           *pfCompareTbl;           /* 比较函数表 */
}  TAF_MMA_FSM_MSG_COMPARE_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
TAF_MMA_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32 TAF_MMA_GetMsgComparePrioRslt(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);


VOS_UINT32 TAF_MMA_ComparePhoneModeSetReqPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 TAF_MMA_CompareAtSyscfgReqPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);


VOS_UINT32 TAF_MMA_CompareAtPlmnListReqPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);

#if (FEATURE_ON == FEATURE_CSG)
VOS_UINT32 TAF_MMA_CompareAtCsgListSearchReqPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);
VOS_UINT32 TAF_MMA_CompareCsgListSearchReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 TAF_MMA_CompareCsgListAbortReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);
#endif


VOS_UINT32 TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);


VOS_UINT32 TAF_MMA_CompareAtPlmnUserSelReqPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 TAF_MMA_CompareAtAttachPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);


VOS_UINT32 TAF_MMA_CompareAtDetachPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);


VOS_UINT32 TAF_MMA_CompareAtPlmnReselPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);


#if (FEATURE_ON == FEATURE_IMS)
VOS_UINT32 TAF_MMA_CompareImsSwitchSetReqPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);
VOS_UINT32 TAF_MMA_ComparePhoneModeSetReqPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);
VOS_UINT32 TAF_MMA_CompareAtSyscfgReqPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);
VOS_UINT32 TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);
VOS_UINT32 TAF_MMA_CompareAtPlmnListReqPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);
VOS_UINT32 TAF_MMA_CompareAtPlmnUserSelReqPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);
VOS_UINT32 TAF_MMA_CompareAtAttachPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);
VOS_UINT32 TAF_MMA_CompareAtDetachPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);
VOS_UINT32 TAF_MMA_CompareAtPlmnReselPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);
VOS_UINT32 TAF_MMA_CompareImsSwitchSetReqPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);


VOS_UINT32 TAF_MMA_CompareMsccPlmnReselCnfPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);


VOS_UINT32 TAF_MMA_CompareImsSwitchSetReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);
#endif
TAF_MMA_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32 TAF_MMA_ComparePhoneModeSetReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);



VOS_UINT32 TAF_MMA_CompareSyscfgSetReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 TAF_MMA_CompareAttachReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 TAF_MMA_CompareDetachReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 TAF_MMA_ComparePlmnReselReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 TAF_MMA_ComparePlmnListReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_UINT32 TAF_MMA_ComparePlmnUserSelReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);

VOS_VOID TAF_MMA_ProcessComparePrioRsltAbort(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_MMA_ProcessComparePrioRsltReject(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_MMA_RejectAppRequest(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_ComparePlmnAbortReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
);






/*****************************************************************************
 结构名    : TAF_MMA_COMPARE_TBL_ITEM
 结构说明  : 每个单个状态机比较函数表结构
 1.日    期   : 2013年7月22日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/

#define TAF_MMA_COMPARE_TBL_ITEM(ulCurrMsgType, pCompareFun)\
{\
    (ulCurrMsgType),\
    ((pCompareFun))\
}

/*****************************************************************************
 结构名    : TAF_MMA_COMPARE_TBL_ITEM
 结构说明  : 比较函数表结构
 1.日    期   : 2013年7月22日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/
#define TAF_MMA_FSM_COMPARE_TBL_ITEM(enFsmId, astFsmCompareTbl)\
{\
    ( enFsmId),\
    ((sizeof(astFsmCompareTbl))/sizeof(TAF_MMA_MSG_COMPARE_STRU)),\
    (astFsmCompareTbl)\
}



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


