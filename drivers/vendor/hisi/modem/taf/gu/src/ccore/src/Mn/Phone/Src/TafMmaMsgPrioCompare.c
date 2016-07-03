

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafMmaMsgPrioCompare.h"
#include  "TafFsm.h"
#include  "Taf_Tafm_Remote.h"
#include  "TafOamInterface.h"
#include  "TafLog.h"
#include  "TafMmaSndInternalMsg.h"
#include  "TafMmaSndApp.h"

#include  "MmaMsccInterface.h"

#include "Taf_Status.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_MSG_PRIO_COMPARE_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

TAF_MMA_MSG_COMPARE_STRU g_astMmaMsgPrioCompareWithPhoneModeTbl[] =
{
    /* phone mode过程中收到OM的模式设置请求的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_SPY, OAM_MMA_PHONE_MODE_SET_REQ),
                             TAF_MMA_ComparePhoneModeSetReqPrioWithPhoneMode),

    /* 模式查询不需要比较 */



    /* phone mode过程中收到模式设置请求的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PHONE_MODE_SET_REQ),
                             TAF_MMA_ComparePhoneModeSetReqPrioWithPhoneMode),

    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(CCPU_PID_CBT, OAM_MMA_PHONE_MODE_SET_REQ),
                             TAF_MMA_ComparePhoneModeSetReqPrioWithPhoneMode),

    /* phone mode过程中收到MMA的内部卡状态指示的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_USIM_STATUS_CHANGE_IND),
                             TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithPhoneMode),


    /* phone mode过程中收到TAF的SYSCFG设置请求的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_SYS_CFG_SET_REQ),
                             TAF_MMA_CompareAtSyscfgReqPrioWithPhoneMode),

    /* phone mode过程中收到AT的list搜网请求的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_LIST_REQ),
                             TAF_MMA_CompareAtPlmnListReqPrioWithPhoneMode),
#if (FEATURE_ON == FEATURE_CSG)
    /* phone mode过程中收到AT的csg list搜网请求的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_CSG_LIST_SEARCH_REQ),
                             TAF_MMA_CompareAtCsgListSearchReqPrioWithPhoneMode),

#endif
    /* phone mode过程中收到AT的用户指定搜网请求的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_SPECIAL_SEL_REQ),
                             TAF_MMA_CompareAtPlmnUserSelReqPrioWithPhoneMode),

    /* phone mode过程中收到AT的attach请求的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_ATTACH_REQ),
                             TAF_MMA_CompareAtAttachPrioWithPhoneMode),


    /* phone mode过程中收到AT的detach请求的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_DETACH_REQ),
                             TAF_MMA_CompareAtDetachPrioWithPhoneMode),

    /* phone mode过程中收到AT的自动重选请求的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_AUTO_RESEL_REQ),
                             TAF_MMA_CompareAtPlmnReselPrioWithPhoneMode),
#if (FEATURE_ON == FEATURE_IMS)
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_IMS_SWITCH_SET_REQ),
                             TAF_MMA_CompareImsSwitchSetReqPrioWithPhoneMode),
#endif

    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(MAPS_PIH_PID, USIMM_STKREFRESH_IND),
                             TAF_MMA_CompareSTKRefreshWithPhoneMode),
};

#if (FEATURE_ON == FEATURE_IMS)

TAF_MMA_MSG_COMPARE_STRU g_astMmaMsgPrioCompareWithImsSwitchTbl[] =
{
    /* IMS SWITCH过程中收到OM的模式设置请求的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_SPY, OAM_MMA_PHONE_MODE_SET_REQ),
                             TAF_MMA_ComparePhoneModeSetReqPrioWithImsSwitch),

    /* IMS SWITCH过程中收到模式设置请求的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PHONE_MODE_SET_REQ),
                             TAF_MMA_ComparePhoneModeSetReqPrioWithImsSwitch),

    /* IMS SWITCH过程中收到MMA的内部卡状态指示的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_USIM_STATUS_CHANGE_IND),
                             TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithImsSwitch),

    /* IMS SWITCH过程中收到TAF的SYSCFG设置请求的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_SYS_CFG_SET_REQ),
                             TAF_MMA_CompareAtSyscfgReqPrioWithImsSwitch),

    /* IMS SWITCH过程中收到AT的用户指定搜网请求的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_SPECIAL_SEL_REQ),
                             TAF_MMA_CompareAtPlmnUserSelReqPrioWithImsSwitch),

    /* IMS SWITCH过程中收到AT的attach请求的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_ATTACH_REQ),
                             TAF_MMA_CompareAtAttachPrioWithImsSwitch),

    /* IMS SWITCH过程中收到AT的detach请求的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_DETACH_REQ),
                             TAF_MMA_CompareAtDetachPrioWithImsSwitch),

    /* IMS SWITCH过程中收到AT的自动重选请求的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_AUTO_RESEL_REQ),
                             TAF_MMA_CompareAtPlmnReselPrioWithImsSwitch),

    /* IMS SWITCH过程中收到TAF的IMS开关机请求的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_IMS_SWITCH_SET_REQ),
                             TAF_MMA_CompareImsSwitchSetReqPrioWithImsSwitch),


    /* IMS SWITCH过程中收到MSCC的PLMN RESEL回复的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMA_PLMN_RESEL_CNF),
                             TAF_MMA_CompareMsccPlmnReselCnfPrioWithImsSwitch),

};
#endif


TAF_MMA_MSG_COMPARE_STRU g_astMmaMsgPrioCompareWithSysCfgTbl[] =
{
    /* 在SYS CFG过程中，收到OAM模式设置请求 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_SPY, OAM_MMA_PHONE_MODE_SET_REQ),
                             TAF_MMA_ComparePhoneModeSetReqPrioWithSysCfg),

    /* 在SYS CFG过程中，收到APP的模式设置请求 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PHONE_MODE_SET_REQ),
                             TAF_MMA_ComparePhoneModeSetReqPrioWithSysCfg),

    /* 在SYS CFG过程中，收到CBT的模式设置请求 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(CCPU_PID_CBT, OAM_MMA_PHONE_MODE_SET_REQ),
                             TAF_MMA_ComparePhoneModeSetReqPrioWithSysCfg),

    /* 在SYS CFG过程中, 收到MMA的内部卡状态指示的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_USIM_STATUS_CHANGE_IND),
                             TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithSysCfg),



    /* 在SYS CFG过程中, 收到APP的SYSCFG设置请求的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_SYS_CFG_SET_REQ),
                             TAF_MMA_CompareSyscfgSetReqPrioWithSysCfg),

    /* 在SYS CFG过程中，收到MMA内部发送的系统配置请求 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_SYS_CFG_SET_REQ),
                             TAF_MMA_CompareSyscfgSetReqPrioWithSysCfg),

    /* 在SYS CFG过程中, 收到APP的ATTACH设置请求的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_ATTACH_REQ),
                             TAF_MMA_CompareAttachReqPrioWithSysCfg),

    /* 在SYS CFG过程中, 收到APP的DETACH设置请求的消息优先级比较, 属于L-C互操作 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_DETACH_REQ),
                             TAF_MMA_CompareDetachReqPrioWithSysCfg),

    /* 在SYS CFG过程中, 收到APP的PLMN RESEL设置请求的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_AUTO_RESEL_REQ),
                             TAF_MMA_ComparePlmnReselReqPrioWithSysCfg),

    /* 在SYS CFG过程中, 收到APP的PLMN LIST设置请求的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_LIST_REQ),
                             TAF_MMA_ComparePlmnListReqPrioWithSysCfg),
#if (FEATURE_ON == FEATURE_CSG)
    /* 在SYS CFG过程中, 收到APP的CSG PLMN LIST设置请求的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_CSG_LIST_SEARCH_REQ),
                             TAF_MMA_CompareCsgListSearchReqPrioWithSysCfg),

    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_CSG_LIST_ABORT_REQ),
                             TAF_MMA_CompareCsgListAbortReqPrioWithSysCfg),
#endif

    /* 在SYS CFG过程中, 收到APP的PLMN USER SEL设置请求的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_SPECIAL_SEL_REQ),
                             TAF_MMA_ComparePlmnUserSelReqPrioWithSysCfg),

    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_LIST_ABORT_REQ),
                             TAF_MMA_ComparePlmnAbortReqPrioWithSysCfg),

    #if (FEATURE_ON == FEATURE_IMS)
    /* 在SYS CFG过程中, 收到APP的ims switch设置请求的消息优先级比较 */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_IMS_SWITCH_SET_REQ),
                             TAF_MMA_CompareImsSwitchSetReqPrioWithSysCfg),
    #endif

    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(MAPS_PIH_PID, USIMM_STKREFRESH_IND),
                             TAF_MMA_CompareSTKRefreshWithSysCfg),
};


TAF_MMA_FSM_MSG_COMPARE_STRU g_astMmaMsgCompareTbl[] =
{
     /* phone mode 状态机比较函数表*/
    TAF_MMA_FSM_COMPARE_TBL_ITEM(TAF_MMA_FSM_PHONE_MODE,
                                 g_astMmaMsgPrioCompareWithPhoneModeTbl),

#if (FEATURE_ON == FEATURE_IMS)
    /* IMS SWITCH状态机比较函数表*/
    TAF_MMA_FSM_COMPARE_TBL_ITEM(TAF_MMA_FSM_IMS_SWITCH,
                                 g_astMmaMsgPrioCompareWithImsSwitchTbl),
#endif
     TAF_MMA_FSM_COMPARE_TBL_ITEM(TAF_MMA_FSM_SYS_CFG,
                                  g_astMmaMsgPrioCompareWithSysCfgTbl),
};

/*****************************************************************************
  3 函数实现
*****************************************************************************/

VOS_UINT32 TAF_MMA_ComparePhoneModeSetReqPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}



VOS_UINT32 TAF_MMA_CompareAtSyscfgReqPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}



VOS_UINT32 TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_CompareAtPlmnListReqPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}

#if (FEATURE_ON == FEATURE_CSG)

VOS_UINT32 TAF_MMA_CompareAtCsgListSearchReqPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}

#endif

VOS_UINT32 TAF_MMA_CompareAtPlmnUserSelReqPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_CompareAtAttachPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}



VOS_UINT32 TAF_MMA_CompareAtDetachPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_CompareAtPlmnReselPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_CompareSTKRefreshWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}

#if (FEATURE_ON == FEATURE_IMS)

VOS_UINT32 TAF_MMA_CompareImsSwitchSetReqPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_ComparePhoneModeSetReqPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_CompareAtSyscfgReqPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_CompareAtPlmnListReqPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_CompareAtPlmnUserSelReqPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_CompareAtAttachPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_CompareAtDetachPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_CompareAtPlmnReselPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_CompareImsSwitchSetReqPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}



VOS_UINT32 TAF_MMA_CompareMsccPlmnReselCnfPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}

#endif

TAF_MMA_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32 TAF_MMA_ComparePhoneModeSetReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    TAF_MMA_ENTRY_MSG_STRU                                 *pstEntryMsg  = VOS_NULL_PTR;
    TAF_MMA_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32               enPrioRslt;

    /* 获取SYS CFG当前状态机入口消息 */
    pstEntryMsg  = TAF_MMA_GetCurrFsmMsgAddr();

    switch (pstEntryMsg->ulEventType)
    {
        /* 如果当前SYS CFG状态机是因为attach/detach触发，收到phone mode设置，可打断当前操作 */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_ATTACH_REQ):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_DETACH_REQ):
            *penAbortType = TAF_MMA_ABORT_FSM_IMMEDIATELY;
            enPrioRslt    = TAF_MMA_MSG_COMPARE_PRIO_RSLT_ABORT;
            break;

        /* 如果当前SYS CFG状态机是因为system cofigure setting触发，收到phone mode设置，缓存phone mode */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_SYS_CFG_SET_REQ):
        case TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_SYS_CFG_SET_REQ):
            *penAbortType = TAF_MMA_ABORT_BUTT;
            enPrioRslt    = TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
            break;

        default:
            /* 理论上不应该发生，打印错误信息 */
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ComparePhoneModeSetReqPrioWithSysCfg: abnormal message!");

            *penAbortType = TAF_MMA_ABORT_FSM_IMMEDIATELY;
            enPrioRslt    = TAF_MMA_MSG_COMPARE_PRIO_RSLT_ABORT;
            break;
    }

    return enPrioRslt;
}


VOS_UINT32 TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    TAF_MMA_ENTRY_MSG_STRU                                 *pstEntryMsg  = VOS_NULL_PTR;
    TAF_MMA_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32               enPrioRslt;

    /* 获取SYS CFG当前状态机入口消息 */
    pstEntryMsg  = TAF_MMA_GetCurrFsmMsgAddr();

    switch (pstEntryMsg->ulEventType)
    {
        /* 如果当前SYS CFG状态机是因为attach/detach触发，收到usim状态改变，可打断当前操作 */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_ATTACH_REQ):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_DETACH_REQ):
            *penAbortType = TAF_MMA_ABORT_FSM_IMMEDIATELY;
            enPrioRslt    = TAF_MMA_MSG_COMPARE_PRIO_RSLT_ABORT;
            break;

        /* 如果当前SYS CFG状态机是因为system cofigure setting触发，收到usim状态改变，缓存usim卡状态变化指示 */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_SYS_CFG_SET_REQ):
        case TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_SYS_CFG_SET_REQ):
            *penAbortType = TAF_MMA_ABORT_BUTT;
            enPrioRslt    = TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
            break;

        default:
            /* 理论上不应该发生，打印错误信息 */
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithSysCfg: abnormal message!");

            *penAbortType = TAF_MMA_ABORT_FSM_IMMEDIATELY;
            enPrioRslt    = TAF_MMA_MSG_COMPARE_PRIO_RSLT_ABORT;
            break;
    }

    return enPrioRslt;
}




VOS_UINT32 TAF_MMA_CompareSyscfgSetReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* 当前SYS CFG在运行，拒绝当前系统配置请求 */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_REJECT;
}


VOS_UINT32 TAF_MMA_CompareAttachReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* 缓存当前请求 */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;

}


VOS_UINT32 TAF_MMA_CompareDetachReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* 缓存当前请求 */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_CompareSTKRefreshWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* 缓存当前请求 */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_ComparePlmnReselReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    TAF_MMA_ENTRY_MSG_STRU                                 *pstEntryMsg  = VOS_NULL_PTR;

    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* 获取SYS CFG当前状态机入口消息 */
    pstEntryMsg  = TAF_MMA_GetCurrFsmMsgAddr();

    if (TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_SYS_CFG_SET_REQ) == pstEntryMsg->ulEventType)
    {
        /* 如果当前SYS CFG状态机是内部系统配置请求触发的，缓存当前请求 */
        return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
    }

    /* 其他拒绝当前的请求 */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_REJECT;
}

#if (FEATURE_ON == FEATURE_CSG)

VOS_UINT32 TAF_MMA_CompareCsgListSearchReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    TAF_MMA_ENTRY_MSG_STRU                                 *pstEntryMsg  = VOS_NULL_PTR;

    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* 获取SYS CFG当前状态机入口消息 */
    pstEntryMsg  = TAF_MMA_GetCurrFsmMsgAddr();

    if (TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_SYS_CFG_SET_REQ) == pstEntryMsg->ulEventType)
    {
        /* 如果当前SYS CFG状态机是内部系统配置请求触发的，缓存当前请求 */
        return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
    }

    /* 其他拒绝当前的请求 */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_REJECT;
}


VOS_UINT32 TAF_MMA_CompareCsgListAbortReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    TAF_MMA_MSG_QUEUE_STRU             *pstEntryMsgAddr = VOS_NULL_PTR;
    VOS_UINT16                          i;
    VOS_UINT32                          ulPlmnListEvent;
    TAF_MMA_CSG_LIST_SEARCH_REQ_STRU   *pstPlmnListAbortMsg = VOS_NULL_PTR;

    pstPlmnListAbortMsg = (TAF_MMA_CSG_LIST_SEARCH_REQ_STRU *)pstMsg;

    ulPlmnListEvent = TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_CSG_LIST_SEARCH_REQ);

    pstEntryMsgAddr = TAF_MMA_GetCachMsgBufferAddr();

    for (i = 0; i < pstEntryMsgAddr->ucCacheMsgNum; i++)
    {
        if (ulPlmnListEvent == pstEntryMsgAddr->astMsgQueue[i].stMsgEntry.ulEventType)
        {
            pstEntryMsgAddr->ucCacheMsgNum--;

            /* 清除CSG LIST REQ事件, move队列中后面的缓存消息 */
            PS_MEM_MOVE(&(pstEntryMsgAddr->astMsgQueue[i].stMsgEntry),
                        &(pstEntryMsgAddr->astMsgQueue[i+1].stMsgEntry),
                        sizeof(TAF_MMA_ENTRY_MSG_STRU) * (pstEntryMsgAddr->ucCacheMsgNum - i));

            /* 消息队列中最后一条消息入口清0 */
            PS_MEM_SET(&(pstEntryMsgAddr->astMsgQueue[pstEntryMsgAddr->ucCacheMsgNum].stMsgEntry),
                       0,
                       sizeof(TAF_MMA_ENTRY_MSG_STRU));

            break;
        }
    }

    /* 上报AT当前状态事件 */
    TAF_MMA_SndCsgListAbortCnf(&(pstPlmnListAbortMsg->stCtrl), TAF_ERR_NO_ERROR);

    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* 已处理完毕，忽略该消息 */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_DISCARD;
}
#endif


VOS_UINT32 TAF_MMA_ComparePlmnListReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    TAF_MMA_ENTRY_MSG_STRU                                 *pstEntryMsg  = VOS_NULL_PTR;

    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* 获取SYS CFG当前状态机入口消息 */
    pstEntryMsg  = TAF_MMA_GetCurrFsmMsgAddr();

    if (TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_SYS_CFG_SET_REQ) == pstEntryMsg->ulEventType)
    {
        /* 如果当前SYS CFG状态机是内部系统配置请求触发的，缓存当前请求 */
        return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
    }

    /* 其他拒绝当前的请求 */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_REJECT;
}


VOS_UINT32 TAF_MMA_ComparePlmnUserSelReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    TAF_MMA_ENTRY_MSG_STRU                                 *pstEntryMsg  = VOS_NULL_PTR;

    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* 获取SYS CFG当前状态机入口消息 */
    pstEntryMsg  = TAF_MMA_GetCurrFsmMsgAddr();

    if (TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_SYS_CFG_SET_REQ) == pstEntryMsg->ulEventType)
    {
        /* 如果当前SYS CFG状态机是内部系统配置请求触发的，缓存当前请求 */
        return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
    }

    /* 其他拒绝当前的请求 */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_REJECT;
}


VOS_UINT32 TAF_MMA_ComparePlmnAbortReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    TAF_MMA_MSG_QUEUE_STRU             *pstEntryMsgAddr = VOS_NULL_PTR;
    VOS_UINT16                          i;
    VOS_UINT32                          ulPlmnListEvent;
    TAF_MMA_PLMN_LIST_ABORT_REQ_STRU   *pstPlmnListAbortMsg = VOS_NULL_PTR;

    pstPlmnListAbortMsg = (TAF_MMA_PLMN_LIST_ABORT_REQ_STRU *)pstMsg;

    ulPlmnListEvent = TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_LIST_REQ);

    pstEntryMsgAddr = TAF_MMA_GetCachMsgBufferAddr();

    for (i = 0; i < pstEntryMsgAddr->ucCacheMsgNum; i++)
    {
        if (ulPlmnListEvent == pstEntryMsgAddr->astMsgQueue[i].stMsgEntry.ulEventType)
        {
            pstEntryMsgAddr->ucCacheMsgNum--;

            /* 清除PLMN LIST REQ事件, move队列中后面的缓存消息 */
            PS_MEM_MOVE(&(pstEntryMsgAddr->astMsgQueue[i].stMsgEntry),
                        &(pstEntryMsgAddr->astMsgQueue[i+1].stMsgEntry),
                        sizeof(TAF_MMA_ENTRY_MSG_STRU) * (pstEntryMsgAddr->ucCacheMsgNum - i));

            /* 消息队列中最后一条消息入口清0 */
            PS_MEM_SET(&(pstEntryMsgAddr->astMsgQueue[pstEntryMsgAddr->ucCacheMsgNum].stMsgEntry),
                       0,
                       sizeof(TAF_MMA_ENTRY_MSG_STRU));

            break;
        }
    }

    /* 上报AT当前状态事件 */
    TAF_MMA_SndPlmnListAbortCnf(&(pstPlmnListAbortMsg->stCtrl), TAF_ERR_NO_ERROR);

    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* 已处理完毕，忽略该消息 */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_DISCARD;
}


VOS_VOID TAF_MMA_ProcessComparePrioRsltAbort(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_ENTRY_MSG_STRU              stEntryMsg;

    PS_MEM_SET(&stEntryMsg, 0, sizeof(TAF_MMA_ENTRY_MSG_STRU));

    /* 如果有缓存，先清除缓存中的消息 */
    while (VOS_TRUE ==TAF_MMA_GetNextCachedMsg(&stEntryMsg))
    {
        TAF_MMA_RejectAppRequest(stEntryMsg.ulEventType, (struct MsgCB *)stEntryMsg.aucEntryMsgBuffer);
    }

    /* 保存当前的用户请求 */
    (VOS_VOID)TAF_MMA_SaveCacheMsgInMsgQueue(ulEventType, (VOS_VOID *) pstMsg);
}


VOS_VOID TAF_MMA_ProcessComparePrioRsltReject(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_RejectAppRequest(ulEventType, pstMsg);
}


VOS_VOID TAF_MMA_RejectAppRequest(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                    *pstRcvMsg          = VOS_NULL_PTR;
    TAF_MMA_PLMN_LIST_CNF_PARA_STRU    *pstPlmnListCnfPara = VOS_NULL_PTR;

    pstRcvMsg = (MSG_HEADER_STRU *)pstMsg;

    switch (ulEventType)
    {
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_ATTACH_REQ):
            /* 调用attach confirm回复接口函数 */
            TAF_MMA_SndAttachCnf(&(((TAF_MMA_ATTACH_REQ_STRU *)(pstRcvMsg))->stCtrl),
                                 TAF_MMA_APP_OPER_RESULT_FAILURE,
                                 TAF_ERR_PHONE_MSG_UNMATCH);
            break;

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_DETACH_REQ):
            /* 调用detach confirm回复接口函数 */
            TAF_MMA_SndDetachCnf(&(((TAF_MMA_DETACH_REQ_STRU *)(pstRcvMsg))->stCtrl),
                                 TAF_MMA_APP_OPER_RESULT_FAILURE,
                                 TAF_ERR_PHONE_MSG_UNMATCH);
            break;

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_SYS_CFG_SET_REQ):
            /* 调用SYS CFG SET回复接口函数 */
            TAF_MMA_SndSysCfgSetCnf(&(((TAF_MMA_SYS_CFG_REQ_STRU *)(pstRcvMsg))->stCtrl),
                                    TAF_ERR_ERROR);
            break;

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_AUTO_RESEL_REQ):
            TAF_MMA_SndPlmnAutoReselCnf(&(((TAF_MMA_PLMN_AUTO_RESEL_REQ_STRU *)(pstRcvMsg))->stCtrl),
                                        TAF_ERR_PHONE_MSG_UNMATCH);
            break;
#if (FEATURE_ON == FEATURE_CSG)
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_CSG_LIST_SEARCH_REQ):
            /* 回复csg列表搜网结果 */
            TAF_MMA_ReportCsgListError(&(((TAF_MMA_CSG_LIST_SEARCH_REQ_STRU *)(pstRcvMsg))->stCtrl), TAF_ERR_PHONE_MSG_UNMATCH);
            break;
#endif

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_LIST_REQ):
            {
                pstPlmnListCnfPara = (TAF_MMA_PLMN_LIST_CNF_PARA_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA,
                                                                                     sizeof(TAF_MMA_PLMN_LIST_CNF_PARA_STRU));
                if (VOS_NULL_PTR != pstPlmnListCnfPara)
                {
                    PS_MEM_SET(pstPlmnListCnfPara, 0x0, sizeof(TAF_MMA_PLMN_LIST_CNF_PARA_STRU));

                    pstPlmnListCnfPara->ucOpError    = VOS_TRUE;
                    pstPlmnListCnfPara->enPhoneError = TAF_ERR_PHONE_MSG_UNMATCH;

                    TAF_MMA_SndPlmnListCnf(&(((TAF_MMA_PLMN_LIST_REQ_STRU *)(pstRcvMsg))->stCtrl),
                                           pstPlmnListCnfPara);

                    PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);
                }
            }
            break;

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_SPECIAL_SEL_REQ):
            TAF_MMA_SndPlmnSpecialSelCnf(&(((TAF_MMA_PLMN_SPECIAL_SEL_REQ_STRU *)(pstRcvMsg))->stCtrl),
                                         TAF_ERR_PHONE_MSG_UNMATCH);
            break;

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PHONE_MODE_SET_REQ):
             TAF_MMA_SndPhoneModeSetCnf(&(((TAF_MMA_PHONE_MODE_SET_REQ_STRU *)(pstRcvMsg))->stCtrl),
                                        ((TAF_MMA_PHONE_MODE_SET_REQ_STRU *)(pstRcvMsg))->stPhoneModePara.PhMode,
                                        TAF_MMA_APP_OPER_RESULT_FAILURE,
                                        TAF_ERR_PHONE_MSG_UNMATCH);
            break;

#if (FEATURE_IMS == FEATURE_ON)
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_IMS_SWITCH_SET_REQ):
             /* 给上层回复失败 */
            TAF_MMA_SndImsSwitchSetCnf(&(((TAF_MMA_IMS_SWITCH_SET_REQ_STRU *)(pstRcvMsg))->stCtrl),
                                         TAF_MMA_APP_OPER_RESULT_FAILURE,
                                         TAF_ERR_UNSPECIFIED_ERROR);
             break;
#endif

        default:
            /* unknown message, ignore it */
            break;
    }
}




TAF_MMA_MSG_COMPARE_FUNC  TAF_MMA_FindMsgPrioCompareFun(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_FSM_ID_ENUM_UINT32          enFsmId
)
{
    TAF_MMA_FSM_MSG_COMPARE_STRU       *pstFsmCompareTbl = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT32                          ulTblSize;

    ulTblSize = sizeof(g_astMmaMsgCompareTbl)/sizeof(TAF_MMA_FSM_MSG_COMPARE_STRU);

    for ( i = 0 ; i < ulTblSize ; i++ )
    {
        if ( enFsmId == g_astMmaMsgCompareTbl[i].enFsmId)
        {
            pstFsmCompareTbl = &g_astMmaMsgCompareTbl[i];
            break;
        }
    }

    /* 未能找到该状态机的比较函数表,直接返回空指针 */
    if ( VOS_NULL_PTR == pstFsmCompareTbl )
    {
        return VOS_NULL_PTR;
    }

    for ( i = 0 ; i < pstFsmCompareTbl->ulSize; i++ )
    {
        /* 查找不同事件的比较函数 */
        if ( pstFsmCompareTbl->pfCompareTbl[i].ulCurrEventType == ulEventType)
        {
            return pstFsmCompareTbl->pfCompareTbl[i].pfCompareFun;
        }
    }

    /* 未找到处理函数直接返回空指针 */
    return VOS_NULL_PTR;
}




TAF_MMA_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32 TAF_MMA_GetMsgComparePrioRslt(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    TAF_MMA_MSG_COMPARE_FUNC                    pfCompareFunc;
    TAF_MMA_FSM_ID_ENUM_UINT32                  enCurrFsmId;
    TAF_MMA_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32   enRslt;

    /*  获取当前状态机的ID */
    enCurrFsmId         = TAF_MMA_GetCurrFsmId();

    if (TAF_MMA_FSM_BUTT <= enCurrFsmId)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "ERROR:FsmId Error");
    }

    /*  获取比较函数 TAF_MMA_FindMsgPrioCompareFun() */
    pfCompareFunc       = TAF_MMA_FindMsgPrioCompareFun(ulEventType, pstMsg, enCurrFsmId);

    /* 未找到处理函数,则默认消息丢弃 */
    if ( VOS_NULL_PTR == pfCompareFunc )
    {
        *penAbortType = TAF_MMA_ABORT_BUTT;
        return TAF_MMA_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* 调用比较函数,返回优先级和打断类型 */
    enRslt = pfCompareFunc(ulEventType, pstMsg, penAbortType);

    return enRslt;

}


VOS_UINT32 TAF_MMA_CompareImsSwitchSetReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* 缓存当前请求 */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;

}
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

