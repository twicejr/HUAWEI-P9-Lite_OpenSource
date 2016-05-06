
#ifndef __NAS_MSCC_MSG_PRIO_COMPARE_H__
#define __NAS_MSCC_MSG_PRIO_COMPARE_H__


/*****************************************************************************
  1. Including header files
*****************************************************************************/
#include  "vos.h"
#include  "PsTypeDef.h"
#include  "NasMsccCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 Macros Define
*****************************************************************************/
#define NAS_MSCC_WILDCARD_MSG_ID                (0xFFFFFFFF)

#define NAS_MSCC_COMPARE_TBL_ITEM(ulCurrMsgType, pCompareFun)\
{\
    (ulCurrMsgType),\
    ((pCompareFun))\
}

#define NAS_MSCC_FSM_COMPARE_TBL_ITEM(enFsmId, astFsmCompareTbl)\
{\
    (enFsmId),\
    ((sizeof(astFsmCompareTbl))/sizeof(NAS_MSCC_MSG_COMPARE_STRU)),\
    (astFsmCompareTbl)\
}

/*****************************************************************************
  3 Enum Define
*****************************************************************************/

enum NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM
{
    NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ABORT,                               /* compare result is abort,should abort the current procedure */
    NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE,                               /* comapre result is buffer,should buffer the current event */
    NAS_MSCC_MSG_COMPARE_PRIO_RSLT_INITFSM,                             /* compare result is init fsm,should enter the fsm and process */
    NAS_MSCC_MSG_COMPARE_PRIO_RSLT_DISCARD,                             /* compare result is discard,should discard the current event */

    NAS_MSCC_MSG_COMPARE_PRIO_RSLT_BUTT
};
typedef VOS_UINT8 NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8;

/*****************************************************************************
  4 Global Variables Define
*****************************************************************************/


/*****************************************************************************
  5 Message Header Define
*****************************************************************************/


/*****************************************************************************
  6 Message Define
*****************************************************************************/


/*****************************************************************************
  7 STRUCT Define
*****************************************************************************/

typedef NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 (*NAS_MSCC_MSG_COMPARE_FUNC)(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


typedef struct
{
    VOS_UINT32                          ulCurrEventType;        /* the current event type */
    NAS_MSCC_MSG_COMPARE_FUNC           pfCompareFun;           /* the compare function */
}NAS_MSCC_MSG_COMPARE_STRU;


typedef struct
{
    NAS_MSCC_FSM_ID_ENUM_UINT32         enFsmId;                /* the current FSM ID */
    VOS_UINT32                          ulSize;                 /* the compare table size */
    NAS_MSCC_MSG_COMPARE_STRU          *pfCompareTbl;           /* the compare function pointer */
}NAS_MSCC_FSM_MSG_COMPARE_STRU;


/*****************************************************************************
  8 UNION Define
*****************************************************************************/


/*****************************************************************************
  9 OTHERS Define
*****************************************************************************/


/*****************************************************************************
 10 Function Define
*****************************************************************************/
NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareSysCfgSetPrioWithSystemAcquire(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_ComparePowerOffReqPrioWithSystemAcquire(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareTiScanTimerExpiredPrioWithSystemAcquire(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareMoCallSuccessNtfPrioWithSystemAcquire(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareEmcCallBackIndPrioWithSystemAcquire(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareTi1xSrvClSysAcqPhaseOneTotalTimerExpiredPrioWithSystemAcquire(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareHsdRfAvailableIndPrioWithSystemAcquire(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareHsdInterSysStartIndPrioWithBSR(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareMmcInterSysStartIndPrioWithBSR(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif
NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareCdmaMoCallRedialSysAcqNtfPrioWithSystemAcquire(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareSysCfgSetPrioWithBSR(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_ComparePowerOffReqPrioWithBSR(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareMoCallSuccessNtfPrioWithBSR(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareEmcCallBackIndPrioWithBSR(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareCdmaMoCallRedialSysAcqNtfPrioWithBSR(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_ComparePowerOffReqPrioWithPowerOff(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareSysCfgSetPrioWithPowerOff(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_GetMsgComparePrioRslt(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MSCC_MSG_COMPARE_FUNC  NAS_MSCC_FindMsgPrioCompareFun(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MSCC_FSM_ID_ENUM_UINT32         enFsmId
);
NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_ComparePsStatusIndPrioWithSystemAcquire(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_ComparePsStatusIndPrioWithBSR(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_ComparePsStatusIndPrioWithPowerOff(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareEmcCallBackIndPrioWithPowerOff(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareMmaUserReselReqPrioWithPowerOff(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareSysCfgSetPrioWithCLInterSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareTiScanTimerExpiredPrioWithCLInterSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareTiWaitMmcPlmnSearchCnfTimerExpiredPrioWithCLInterSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_ComparePowerOffReqPrioWithCLInterSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareMoCallSuccessNtfPrioWithCLInterSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareEmcCallBackIndPrioWithCLInterSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareCdmaMoCallRedialSysAcqNtfPrioWithCLInterSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/* Added by w00176964 for CL数传切换优化, 2015-12-11, begin */
NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareCdmaMoCallRedialSysAcqNtfPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
/* Added by w00176964 for CL数传切换优化, 2015-12-11, end */


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

#endif//end of NasMsccMsgPrioCompare.h


