

#ifndef __CNAS_HSM_KEEP_ALIVE_H__
#define __CNAS_HSM_KEEP_ALIVE_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "CnasHsmCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 The Macro Define
*****************************************************************************/

#define TI_CNAS_HSM_KEEP_ALIVE_TIMER_DEFAULT_LEN                    (18*3600*1000) /* The Default value of Tsmpclose is 54 hours. Tsmpclose/3 is 18 hours */
#define CNAS_HSM_MAX_TIMER_LEN                                      (18*3600*1000) /* Maximum timer length supported by platform is 18 hours */
#define CNAS_HSM_MAX_SYS_TICK                                       (0xFFFFFFFFUL)
#define CNAS_HSM_DEFAULT_TSMP_CLOSE_LEN                             (54 * 60) /* The default Tsmpclose is 54 hours. Unit
                                                                                 is minues */
#define CNAS_HSM_DEFAULT_TSMP_CLOSE_REMAIN_LEN                      (54 * 60 * 60) /* The default TsmpClose Remain Len is
                                                                                      54 hours. The Unit is seconds */
#define CNAS_HSM_MIN_TO_MILLISEC                                    (60*1000)
#define CNAS_HSM_SEC_TO_MILLISEC                                    (1000)
#define CNAS_HSM_MIN_TO_SEC                                         (60)
#define CNAS_HSM_SYS_TICK_TO_MILLISEC                               (10)
#define CNAS_HSM_SMP_KEEP_ALIVE_LIMIT                               (3)

/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/


enum CNAS_HSM_KEEP_ALIVE_TIMER_SCENE_ENUM
{
    CNAS_HSM_KEEP_ALIVE_SCENE_SESSION_RECOVERED,

    CNAS_HSM_KEEP_ALIVE_SCENE_SESSION_ACTIVATED,

    CNAS_HSM_KEEP_ALIVE_SCENE_SESSION_DEACTIVATED,

    CNAS_HSM_KEEP_ALIVE_SCENE_TSMP_CLOSE_CHANGED,

    CNAS_HSM_KEEP_ALIVE_SCENE_POWER_OFF,

    CNAS_HSM_KEEP_ALIVE_SCENE_RCV_KEEP_ALIVE_MSG,

    CNAS_HSM_KEEP_ALIVE_SCENE_FWD_TRAF_DATA_RCVD,

    CNAS_HSM_KEEP_ALIVE_SCENE_TIMER_NOT_FULLY_EXPIRED,

    CNAS_HSM_KEEP_ALIVE_SCENE_FWD_TRAF_DATA_NOT_RCVD,

    CNAS_HSM_KEEP_ALIVE_SCENE_BUTT
};
typedef VOS_UINT32  CNAS_HSM_KEEP_ALIVE_TIMER_SCENE_ENUM_UINT32;


/*****************************************************************************
  4 The Declaration Of The Gloabal Variable
*****************************************************************************/

/*****************************************************************************
  5 The Define Of the Message Header
*****************************************************************************/


/*****************************************************************************
  6 The Define of the Message Name
*****************************************************************************/


/*****************************************************************************
  7 The Struct Define
*****************************************************************************/


typedef VOS_VOID (*pCnasHsmKeepAliveTimerHandlerFunc)(VOS_VOID);




typedef struct
{
   CNAS_HSM_KEEP_ALIVE_TIMER_SCENE_ENUM_UINT32             enKeepAliveTimerScene;
   pCnasHsmKeepAliveTimerHandlerFunc                       pfuncKeepAliveTimerHandler;
}CNAS_HSM_KEEP_ALIVE_TIMER_PROCESS_TBL_STRU;

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

VOS_VOID CNAS_HSM_StartSessionKeepAliveProcedure(
   VOS_UINT32                          ulKeepAliveTimerLen
);

VOS_VOID CNAS_HSM_StopSessionKeepAliveProcedure(VOS_VOID);

VOS_VOID CNAS_HSM_ProcKeepAliveTimerNotFullyExpired(VOS_VOID);

VOS_VOID CNAS_HSM_ProcKeepAliveTimer(
   CNAS_HSM_KEEP_ALIVE_TIMER_SCENE_ENUM_UINT32             enKeepAliveTimerScene
);

VOS_VOID CNAS_HSM_ProcKeepAliveTimerSessionRecovered(VOS_VOID);

VOS_VOID CNAS_HSM_ProcKeepAliveTimerSessionActivated(VOS_VOID);

VOS_VOID CNAS_HSM_ProcKeepAliveTimerSessionDeactivated(VOS_VOID);

VOS_VOID CNAS_HSM_ProcKeepAliveTimerTsmpCloseChanged(VOS_VOID);

VOS_VOID CNAS_HSM_ProcKeepAliveTimerRcvPowerOff(VOS_VOID);

VOS_VOID CNAS_HSM_ProcKeepAliveTimerRcvKeepAliveMsg(VOS_VOID);

VOS_VOID CNAS_HSM_ProcKeepAliveTimerFwdTrafDataRcvd(VOS_VOID);

VOS_VOID CNAS_HSM_SaveSessionKeepAliveInfo(
    CNAS_HSM_SESSION_STATUS_ENUM_UINT8  ucSessionStatus
);

VOS_UINT32 CNAS_HSM_CalculateTsmpCloseRemainTime(VOS_VOID);

VOS_VOID CNAS_HSM_SavePowerOffSysTime(VOS_VOID);

VOS_UINT32 CNAS_HSM_IsTsmpCloseValueChanged(
    VOS_UINT16                          usNewTsmpClose
);

VOS_UINT32 CNAS_HSM_IsSessionExpired(
    VOS_UINT32                         *pulCurSysTime,
    VOS_UINT32                         *pulOldSysTime
);

VOS_UINT8 CNAS_HSM_IsNeedSessionRecovery(
    VOS_UINT32                         *pulCurSysTime,
    VOS_UINT32                         *pulOldSysTime
);

VOS_VOID CNAS_HSM_CalcTsmpCloseRemainTimeAfterFirstSysAcq(
    VOS_UINT32                         *pulNewSysTime,
    VOS_UINT32                         *pulOldSysTime
);

VOS_VOID CNAS_HSM_ProcKeepAliveTimerFwdTrafDataNotRcvd(VOS_VOID);

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

#endif /* end of CnasHsmKeepAlive.h */


