

#ifndef __CNAS_HSM_COM_FUNC_H__
#define __CNAS_HSM_COM_FUNC_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "CnasHsmTimer.h"
#include "CnasHsmCtx.h"
#include "cas_hrpd_airlinkmgmt_nas_pif.h"
#include "cttf_hrpd_mac_config_public_pif.h"
#include "cas_hrpd_sessioncfg_nas_pif.h"
#include "CnasHsmEncode.h"
#include "CnasCcb.h"
#include "hsm_hlu_pif.h"
#include "cas_hrpd_sessioncfg_session_layer_pif.h"
#include "cttf_hrpd_fsps_ctrl_callback_pif.h"

#include "omnvinterface.h"

#include "cas_hrpd_idlestate_nas_pif.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 The Macro Define
*****************************************************************************/

#define CNAS_HSM_IS_VALID_PTR(x)        ((x) != VOS_NULL_PTR)
#define CNAS_HSM_IS_NULL_PTR(x)         ((x) == VOS_NULL_PTR)
#define CNAS_HSM_IS_EQUAL(x, y)         ((x) == (y))
#define CNAS_HSM_IS_NOT_EQUAL(x, y)     ((x) != (y))

#define CNAS_HSM_CONST                  const
#define CNAS_HSM_CDMA_SYS_TIME_MICROSEC_UNIT                (26670u)
#define CNAS_HSM_SEQ_NUM_BIT_LEN                            (8)


/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/



/*****************************************************************************
  4 The Declaration Of The Gloabal Variable
*****************************************************************************/
#ifdef DMT
    extern VOS_UINT32                                       g_ulCurTick;
    extern CAS_HRPD_DEFAULT_AMP_ATTRIB_STRU                 g_stAmpNegAttribs;
    extern CAS_HRPD_DEFAULT_SMP_ATTRIB_STRU                 g_stSmpNegAttribs;
#endif

/*****************************************************************************
  5 The Define Of the Message Header
*****************************************************************************/


/*****************************************************************************
  6 The Define of the Message Name
*****************************************************************************/


/*****************************************************************************
  7 The Struct Define
*****************************************************************************/

typedef struct
{
    CAS_CNAS_HRPD_SCP_NEG_RSLT_ENUM_UINT8                   enScpReason;
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason;
    VOS_UINT8                                               aucRsv[2];
}CNAS_HSM_SCP_FAIL_REASON_MAP_SESSION_DEACT_REASON_STRU;


typedef struct
{
    VOS_UINT32                          ulHigherOrderWord;
    VOS_UINT32                          ulLowerOrderWord;
}CNAS_HSM_64_BIT_DATA_STRU;


typedef struct
{
    CNAS_HSM_TIMER_ID_ENUM_UINT32       enTimerId;
    VOS_TIMER_PRECISION_ENUM_UINT32     enTimerPrecision;
}CNAS_HSM_TIMER_PRECISION_MAP_TBL_STRU;

/*****************************************************************************
  8 The Union Define
*****************************************************************************/


/*****************************************************************************
  9 Other Defines
*****************************************************************************/


/*****************************************************************************
  10 The Declaration Of The Function
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID CNAS_HSM_StartTimer(
    CNAS_HSM_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulTimerLen
);

VOS_VOID CNAS_HSM_StopTimer(
    CNAS_HSM_TIMER_ID_ENUM_UINT32       enTimerId
);

VOS_UINT32  CNAS_HSM_GenerateInitSessionSeed(VOS_VOID);
VOS_UINT32  CNAS_HSM_GenerateCurrentSessionSeed(
    VOS_UINT32                          ulPreSessionSeed
);

VOS_UINT16 CNAS_HSM_CovertBitLenToByteLen(
    VOS_UINT16                   usMsgBitLen
);

VOS_VOID CNAS_HSM_ProcPowerOffReq(VOS_VOID);

VOS_VOID CNAS_HSM_StopAllTimer(VOS_VOID);

CTTF_HRPD_ATI_TYPE_ENUM_UINT8 CNAS_HSM_CovertHsmAtiTypeToTtfAtiType(
    CNAS_HSM_ATI_TYPE_ENUM_UINT8        enHsmAtiType
);

VOS_VOID CNAS_HSM_SetRandEsnAsHardwareIdInfo(VOS_VOID);

VOS_UINT8 CNAS_HSM_IsUIMIDValid(
    VOS_UINT8                          *pucEFRUIMID
);

VOS_VOID CNAS_HSM_SetUIMIDAsHardwareIdInfo(VOS_VOID);

VOS_UINT8 CNAS_HSM_IsPesnValid(
    NV_PESN_STRU                       *pstPesn
);

VOS_UINT8 CNAS_HSM_IsMeidValid(
    NV_MEID_STRU                       *pstMeid
);
VOS_UINT8 CNAS_HSM_CompareSeqNum(
    VOS_UINT8                           ucNewSeqNum,
    VOS_UINT8                           ucOldSeqNum
);

VOS_UINT8 CNAS_HSM_IsValidUatiAssignment(
    CNAS_HSM_UATI_ASSIGN_MSG_STRU      *pstUatiAssignMsg
);

VOS_UINT8 CNAS_HSM_IsFreshUatiAssignment(
    CNAS_HSM_UATI_ASSIGN_MSG_STRU      *pstUatiAssignMsg
);

VOS_UINT8 CNAS_HSM_IsUatiAssignValidAndFresh(
    CNAS_HSM_UATI_ASSIGN_MSG_STRU      *pstUatiAssignMsg
);

VOS_UINT32 CNAS_HSM_SquareRoot(VOS_UINT32 ulNumber);

VOS_UINT32 CNAS_HSM_CalcNoMonitorDistance(
    VOS_INT32                           ulOldLat,
    VOS_INT32                           ulOldLong,
    VOS_INT32                           ulNewLat,
    VOS_INT32                           ulNewLong
);

VOS_VOID CNAS_HSM_HandleUatiAssignMsg(
    CNAS_HSM_UATI_ASSIGN_MSG_STRU      *pstUatiAssignMsg
);

#if (VOS_RTOSCK == VOS_OS_VER)
extern double cos(double angle);
#endif  /*(VOS_RTOSCK == VOS_OS_VER)*/

VOS_VOID CNAS_HSM_UpdateHrpdAtiInfo(VOS_VOID);


CNAS_HSM_SESSION_TYPE_ENUM_UINT8 CNAS_HSM_ConvertPaModeToHsmSessionType(
    CAS_CNAS_HRPD_PA_MODE_ENUM_UINT8                        enPaMode
);

EHSM_HSM_SESSION_TYPE_ENUM_UINT32 CNAS_HSM_ConvertHsmSessionToEhsmSessionType(
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enSessionType
);

VOS_VOID CNAS_HSM_GetCloseReasonSendAnByDeactReason(
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason,
    CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_ENUM_UINT8      *penOutCloseReasonSendToAn
);

CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8 CNAS_HSM_ConvertScpActiveFailReasonToSessionDeactReason(
    CAS_CNAS_HRPD_SCP_NEG_RSLT_ENUM_UINT8                   enScpReason
);

CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8 CNAS_HSM_ConvertScpNegRsltIndFailReasonToSessionDeactReason(
    CAS_CNAS_HRPD_SCP_NEG_RSLT_ENUM_UINT8                   enScpReason
);

HSM_HLU_SESSION_RAT_MODE_ENUM_UINT8 CNAS_HSM_ConvertHsmSessionTypeToHluSessionRatMode(
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8    enSessionType
);

VOS_VOID CNAS_HSM_ConvertCdmaSysTimeToHsmFormat(
    VOS_UINT32                         *pulCdmaSysTime,
    VOS_UINT32                         *pulHsmSysTime
);

VOS_VOID CNAS_HSM_64Add32(
    CNAS_HSM_64_BIT_DATA_STRU          *pstAddend,
    VOS_UINT32                          ulAddFactor,
    CNAS_HSM_64_BIT_DATA_STRU          *pstRslt
);

VOS_VOID CNAS_HSM_64Sub64(
    CNAS_HSM_64_BIT_DATA_STRU          *pstMinuend,
    CNAS_HSM_64_BIT_DATA_STRU          *pstSubtrahend,
    CNAS_HSM_64_BIT_DATA_STRU          *pstResult
);

VOS_TIMER_PRECISION_ENUM_UINT32 CNAS_HSM_GetTimerPrecision(
    CNAS_HSM_TIMER_ID_ENUM_UINT32       enTimerId
);

VOS_VOID CNAS_HSM_SaveSysTimeAndCurSysTick(
    VOS_UINT32                         *pulCdmaSysTime
);

VOS_UINT32  CNAS_HSM_GetSysTick(VOS_VOID);

CNAS_HSM_SESSION_RELEASE_TYPE_ENUM_UINT8 CNAS_HSM_ConvertCasSessionRelTypeToHsmSessionRelType(
    CAS_CNAS_HRPD_SESSION_RELEASE_TYPE_UINT8                enSessionReleaseType
);

VOS_UINT8 CNAS_HSM_IsIccIdValid(
    VOS_UINT8                          *pucIccId
);

VOS_UINT32 CNAS_HSM_IsInUatiProcedure(VOS_VOID);

VOS_UINT32 CNAS_HSM_IsInScpProcedure(VOS_VOID);

VOS_UINT8 CNAS_HSM_IsEqualIccId(
    VOS_UINT8                          *pucSrcIccId,
    VOS_UINT8                          *pucDstIccId
);

VOS_UINT8 CNAS_HSM_IsEqualMeId(
    VOS_UINT8                          *pucSrcMeId,
    VOS_UINT8                          *pucDstMeId
);

VOS_UINT8 CNAS_HSM_IsIccidChanged(
    VOS_UINT8                          *pucSrcIccId,
    VOS_UINT8                          *pucDstIccId
);

VOS_UINT8 CNAS_HSM_IsHardwareIdChanged(
    CNAS_HSM_HARDWARE_ID_INFO_STRU     *pstSrcHwid,
    CNAS_HSM_HARDWARE_ID_INFO_STRU     *pstDstHwid
);

VOS_VOID CNAS_HSM_ProcTrafficFlowOnForwardChannel(VOS_VOID);

HSM_APS_CAUSE_ENUM_UINT32 CNAS_HSM_MapApsCause(
    CAS_CNAS_HRPD_CONN_OPEN_RSLT_ENUM_UINT8                 enRslt
);

EHSM_HSM_RSLT_ENUM_UINT32 CNAS_HSM_MapEhsmCause(
    CAS_CNAS_HRPD_CONN_OPEN_RSLT_ENUM_UINT8                 enRslt
);

VOS_VOID CNAS_HSM_UpdateHrpdSysInfo(
    HSD_HSM_OVERHEAD_MSG_IND_STRU      *pstOverHeadMsgInd
);


HSM_HSD_HRPD_CONN_OPEN_RSLT_ENUM_UINT8 CNAS_HSM_ConvertConnOpenRsltFromCasToHsm(
    CAS_CNAS_HRPD_CONN_OPEN_RSLT_ENUM_UINT8                 enConnOpenIndRslt
);

VOS_UINT8 CNAS_HSM_IsHrpdAccessAuthUserChanged(
    CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU                    *pstSrcAccessAuthInfo,
    CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU                    *pstDstAccessAuthInfo
);

VOS_UINT8 CNAS_HSM_IsEsnMeidMeChanged(
    CNAS_HSM_STORE_ESN_MEID_RSLT_STRU                      *pstStoreEsnMeidRslt,
    CNAS_CCB_ESNMEIDME_INFO_STRU                           *pstEsnMeidMeInfo,
    CNAS_HSM_HARDWARE_ID_INFO_STRU                         *pstDstHwid
);

HSM_APS_CAUSE_ENUM_UINT32 CNAS_HSM_ConvertHrpdNetworkLostRsltToHsmApsErrCode(
    CAS_CNAS_HRPD_NETWORK_LOST_REASON_ENUM_UINT16           enNetworkLostReason
);

EHSM_HSM_RSLT_ENUM_UINT32 CNAS_HSM_ConvertHrpdNetworkLostRsltToHsmEhsmErrCode(
    CAS_CNAS_HRPD_NETWORK_LOST_REASON_ENUM_UINT16           enNetworkLostReason
);

VOS_VOID CNAS_HSM_VoteEnterSlottedMode(CNAS_HSM_SLOT_VOTE_TYPE_ENUM_UINT8 enSlotVoteType);

VOS_VOID CNAS_HSM_VoteExitSlottedMode(CNAS_HSM_SLOT_VOTE_TYPE_ENUM_UINT8 enSlotVoteType);


VOS_VOID CNAS_HSM_ProcWaitUaitAssignTimerLen(
    VOS_UINT8     ucInWaitUaitAssigntimerLen,
    VOS_UINT8    *pucOutInWaitUaitAssigntimerLen
);

VOS_UINT8  CNAS_HSM_IsUERevInfoChanged(VOS_VOID);

HSM_APS_CAUSE_ENUM_UINT32 CNAS_HSM_ConvertCasCloseReasonToHsmCause(
    CAS_CNAS_HRPD_CONN_CLOSE_REASON_ENUM_UINT16             enConnCloseReason
);

VOS_UINT8 CNAS_HSM_IsSubnetEqual(
    VOS_UINT8                          *pucDestSubnet,
    VOS_UINT8                          *pucSrcSubnet
);

VOS_VOID CNAS_HSM_GetSubnet(
    VOS_UINT8                          *pucOutSubnet,
    VOS_UINT8                          *pucInSectorId,
    VOS_UINT8                           ucSubetMask
);

VOS_UINT8 CNAS_HSM_IsHardWareIdResSnpDataCnf(
    VOS_UINT16                                              usOpId
);

VOS_UINT8 CNAS_HSM_IsKeepAliveReqSnpDataCnf(
    VOS_UINT16                                              usOpId
);

VOS_UINT8 CNAS_HSM_IsKeepAliveResSnpDataCnf(
    VOS_UINT16                                              usOpId
);

VOS_UINT8 CNAS_HSM_IsUatiCmplSnpDataCnf(
    VOS_UINT16                                              usOpId
);

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

#endif /* end of CnasHsmComFunc.h */



