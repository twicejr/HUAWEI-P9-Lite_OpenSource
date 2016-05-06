

/*****************************************************************************
  1. File Inclusions
*****************************************************************************/
#include "CnasHsmTimer.h"
#include "CnasHsmCtx.h"
#include "CnasHsmComFunc.h"
#include "CnasHsmKeepAlive.h"
#include "CnasTimerMgmt.h"
#include "CnasMntn.h"
#include "PsCommonDef.h"
#include "CnasHsmFsmTbl.h"
#include "CnasHsmProcNvim.h"
#include "CnasHsmFsmMain.h"
#include "CnasHsmMntn.h"

#include "CnasHsmSndAs.h"
#include "CnasHsmSndTtf.h"
#include "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_KEEP_ALIVE_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 Global variables
*****************************************************************************/
CNAS_HSM_KEEP_ALIVE_TIMER_PROCESS_TBL_STRU                  g_astCnasHsmKeepAliveTimerProcessTbl[] =
{
    {CNAS_HSM_KEEP_ALIVE_SCENE_SESSION_RECOVERED,                     CNAS_HSM_ProcKeepAliveTimerSessionRecovered},
    {CNAS_HSM_KEEP_ALIVE_SCENE_SESSION_ACTIVATED,                     CNAS_HSM_ProcKeepAliveTimerSessionActivated},
    {CNAS_HSM_KEEP_ALIVE_SCENE_SESSION_DEACTIVATED,                   CNAS_HSM_ProcKeepAliveTimerSessionDeactivated},
    {CNAS_HSM_KEEP_ALIVE_SCENE_TSMP_CLOSE_CHANGED,                    CNAS_HSM_ProcKeepAliveTimerTsmpCloseChanged},
    {CNAS_HSM_KEEP_ALIVE_SCENE_POWER_OFF,                             CNAS_HSM_ProcKeepAliveTimerRcvPowerOff},
    {CNAS_HSM_KEEP_ALIVE_SCENE_RCV_KEEP_ALIVE_MSG,                    CNAS_HSM_ProcKeepAliveTimerRcvKeepAliveMsg},
    {CNAS_HSM_KEEP_ALIVE_SCENE_FWD_TRAF_DATA_RCVD,                    CNAS_HSM_ProcKeepAliveTimerFwdTrafDataRcvd},
    {CNAS_HSM_KEEP_ALIVE_SCENE_TIMER_NOT_FULLY_EXPIRED,               CNAS_HSM_ProcKeepAliveTimerNotFullyExpired},

    {CNAS_HSM_KEEP_ALIVE_SCENE_FWD_TRAF_DATA_NOT_RCVD,                CNAS_HSM_ProcKeepAliveTimerFwdTrafDataNotRcvd}
};


/*****************************************************************************
  3 Functions
*****************************************************************************/


VOS_VOID CNAS_HSM_StartSessionKeepAliveProcedure(
    VOS_UINT32                          ulKeepAliveTimerLen
)
{
    VOS_UINT32                          ulTimerLen;

    if (0 == ulKeepAliveTimerLen)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_StartSessionKeepAliveProcedure: Timer Len is zero!");
        return;
    }

    /* Copy the System Tick at the time of Last Received Forward Traffic channel data to the Previous_Tick global var */
    CNAS_HSM_SetOldSysTickFwdTrafChan(CNAS_HSM_GetSysTickFwdTrafficChan());

    /* Set the Keep Alive timer length to global variable */
    CNAS_HSM_SetKeepAliveTimerLen(ulKeepAliveTimerLen);

    /* Reset the total Timer expired count to zero */
    CNAS_HSM_SetKeepAliveTimerExpiredCount(0);

    /* If Keep alive timer length is less than or equal the Max timer len, the Keep alive timer could be run just once */
    if (CNAS_HSM_MAX_TIMER_LEN >= ulKeepAliveTimerLen)
    {
        /* Set The total Keep alive timer run count to 1 */
        CNAS_HSM_SetKeepAliveTimerTotalRunCount(1);

        ulTimerLen = ulKeepAliveTimerLen;
    }
    else if (0 == (ulKeepAliveTimerLen % CNAS_HSM_MAX_TIMER_LEN))
    {
        /* If Keep Alive Timer Length is greter than the Max Timer length, HSM must run the Keep Alive timer multiple times
        to get the required time duration */

        /* If The Keep Alive timer len is a multiple of CNAS_HSM_MAX_TIMER_LEN,
        The Total Number of times the Keep Alive timer should be run is the quotient */
        CNAS_HSM_SetKeepAliveTimerTotalRunCount(ulKeepAliveTimerLen / CNAS_HSM_MAX_TIMER_LEN);

        ulTimerLen = CNAS_HSM_MAX_TIMER_LEN;
    }
    else
    {
        /* The Total Number of times the Keep Alive timer should be run is the quotient+1 */
        CNAS_HSM_SetKeepAliveTimerTotalRunCount((ulKeepAliveTimerLen / CNAS_HSM_MAX_TIMER_LEN) + 1);

        ulTimerLen = CNAS_HSM_MAX_TIMER_LEN;
    }

    /* Start the keep alive timer */
    CNAS_HSM_StartTimer(TI_CNAS_HSM_KEEP_ALIVE_TIMER, ulTimerLen);
}




VOS_VOID CNAS_HSM_StopSessionKeepAliveProcedure(VOS_VOID)
{
    /* Reset the Keep Alive timer length to global variable */
    CNAS_HSM_SetKeepAliveTimerLen(0);

    /* Reset the total Timer expired count to zero */
    CNAS_HSM_SetKeepAliveTimerExpiredCount(0);

    /* Reset the Total Timer Run count to zero */
    CNAS_HSM_SetKeepAliveTimerTotalRunCount(0);

    /* Reset the Keep alive Req snd count to zero */
    CNAS_HSM_SetKeepAliveReqSndCount(0);

    /* Stop the Keep alive timer */
    CNAS_HSM_StopTimer(TI_CNAS_HSM_KEEP_ALIVE_TIMER);

}




VOS_VOID CNAS_HSM_ProcKeepAliveTimer(
    CNAS_HSM_KEEP_ALIVE_TIMER_SCENE_ENUM_UINT32             enKeepAliveTimerScene
)
{
    VOS_UINT32                          i;

    VOS_UINT32                          ulIsKeepAliveAfterProc;

    pCnasHsmKeepAliveTimerHandlerFunc   pfuncKeepAliveTimerHandler = VOS_NULL_PTR;

    /* Log the keep alive info before keepalive process */

    ulIsKeepAliveAfterProc = VOS_FALSE;
    CNAS_HSM_LogSessionKeepAliveInfo(enKeepAliveTimerScene, ulIsKeepAliveAfterProc, CNAS_HSM_GetKeepAliveCtrlCtxAddr());


    for (i = 0; i < (sizeof(g_astCnasHsmKeepAliveTimerProcessTbl)/sizeof(CNAS_HSM_KEEP_ALIVE_TIMER_PROCESS_TBL_STRU)); i++)
    {
        if (enKeepAliveTimerScene == g_astCnasHsmKeepAliveTimerProcessTbl[i].enKeepAliveTimerScene)
        {
            pfuncKeepAliveTimerHandler = g_astCnasHsmKeepAliveTimerProcessTbl[i].pfuncKeepAliveTimerHandler;
            break;
        }
    }

    if (VOS_NULL_PTR != pfuncKeepAliveTimerHandler)
    {
        pfuncKeepAliveTimerHandler();
    }

    ulIsKeepAliveAfterProc = VOS_TRUE;

    /* Log the keep alive info after keepalive process */
    CNAS_HSM_LogSessionKeepAliveInfo(enKeepAliveTimerScene, ulIsKeepAliveAfterProc, CNAS_HSM_GetKeepAliveCtrlCtxAddr());

    return;
}




VOS_VOID CNAS_HSM_ProcKeepAliveTimerSessionRecovered(VOS_VOID)
{
    VOS_UINT16                          usTsmpClose;
    VOS_UINT32                          ulTsmpCloseInSec;
    VOS_UINT32                          ulTsmpCloseRemainTime;
    VOS_UINT32                          ulKeepAliveTimerLenInSec;
    VOS_UINT32                          ulKeepAliveTimerLen;
    VOS_UINT8                           ucKeepAliveReqSndCount;
    VOS_UINT8                           ucLoop;

    /* Get the Tsmpclose value from global variable. Unit is minutes */
    usTsmpClose             = CNAS_HSM_GetTsmpClose();

    /* Get the TsmpClose_Remain_Time from global varible. Unit is seconds */
    ulTsmpCloseRemainTime   = CNAS_HSM_GetTsmpCloseRemainTime();

    /* Convert the TsmpClose to seconds */
    ulTsmpCloseInSec = usTsmpClose * CNAS_HSM_MIN_TO_SEC;

    /* If Tsmpclose value or Tsmpclose_remain_time is zero, do not start the Keep Alive timer */
    if ((0 == usTsmpClose)
     || (0 == ulTsmpCloseRemainTime))
    {
        return;
    }

    /* Find the values of KeepAliveReqSndCount and KeepAliveTimerLen */
    /* FOR LOOP LOGIC (CNAS_HSM_SMP_KEEP_ALIVE_LIMIT = 3)

    0       Tsmpclose/3      2 * Tsmpclose/3            Tsmpclose
    ---------------|-----------------|--------------------|
                                         ^ucLoop = 1, KeepAliveReqSndCount = 2, KeepAliveTimerLen = Tsmpclose_Remain_Len

                            ^ucLoop = 2, KeepAliveReqSndCount = 1, KeepAliveTimerLen = Tsmpclose_Remain_Len - Tsmpclose/3

        ^ucLoop = 3, KeepAliveReqSndCount = 0, KeepAliveTimerLen = Tsmpclose_Remain_Len - 2 *Tsmpclose/3
    */

    ulKeepAliveTimerLenInSec = ulTsmpCloseRemainTime;
    ucKeepAliveReqSndCount   = CNAS_HSM_SMP_KEEP_ALIVE_LIMIT - 1;

    for (ucLoop = 1 ; ucLoop <= CNAS_HSM_SMP_KEEP_ALIVE_LIMIT; ucLoop++)
    {
        if (ulTsmpCloseRemainTime <= (ucLoop * ulTsmpCloseInSec) / CNAS_HSM_SMP_KEEP_ALIVE_LIMIT)
        {
            break;
        }

        /* Decrement the KeepAliveReqSndCount and subtract TsmpClose/Nsmpkeepalive minutes from the Timer Len in min */
        ucKeepAliveReqSndCount--;
        ulKeepAliveTimerLenInSec -= ulTsmpCloseInSec / CNAS_HSM_SMP_KEEP_ALIVE_LIMIT;
    }

    /* Convert from seconds to ms */
    ulKeepAliveTimerLen = ulKeepAliveTimerLenInSec * CNAS_HSM_SEC_TO_MILLISEC;

    /* Save the Keep alive timer length and the Keep alive req snd count */
    CNAS_HSM_SetKeepAliveReqSndCount(ucKeepAliveReqSndCount);
    CNAS_HSM_SetKeepAliveTimerLen(ulKeepAliveTimerLen);

    /* Start the Keep Alive Process */
    CNAS_HSM_StartSessionKeepAliveProcedure(ulKeepAliveTimerLen);

    return;
}




VOS_VOID CNAS_HSM_ProcKeepAliveTimerSessionActivated(VOS_VOID)
{
    VOS_UINT16                          usTsmpClose;
    VOS_UINT32                          ulKeepAliveTimerLen;

    /* Get the Tsmpclose value from global variable. The unit is minutes */
    usTsmpClose = CNAS_HSM_GetTsmpClose();

    /* Do not start the keep alive timer if the Tsmpclose is zero */
    if (0 != usTsmpClose)
    {
        /* If Tsmpclose is non zero, Set timer len = Tsmpclose/Nsmpkeepalive(converted to millisec) */
        ulKeepAliveTimerLen = ((VOS_UINT32)usTsmpClose * CNAS_HSM_MIN_TO_MILLISEC) / CNAS_HSM_SMP_KEEP_ALIVE_LIMIT;

        /* Start the Keep alive Process */
        CNAS_HSM_StartSessionKeepAliveProcedure(ulKeepAliveTimerLen);
    }

    return;
}




VOS_VOID CNAS_HSM_ProcKeepAliveTimerSessionDeactivated(VOS_VOID)
{
    /* if the Session is not open, then set the Tsmpclose to default value of 54 hours,
    Tsmpclose_Remain_Time to 54 hours */
    CNAS_HSM_SetTsmpClose(CNAS_HSM_DEFAULT_TSMP_CLOSE_LEN);
    CNAS_HSM_SetTsmpCloseRemainTime(CNAS_HSM_DEFAULT_TSMP_CLOSE_REMAIN_LEN);

    /* stop the keep alive process */
    CNAS_HSM_StopSessionKeepAliveProcedure();

    return;
}




VOS_VOID CNAS_HSM_ProcKeepAliveTimerTsmpCloseChanged(VOS_VOID)
{
    VOS_UINT16                          usTsmpClose;
    VOS_UINT32                          ulKeepAliveTimerLen;
    CNAS_TIMER_STATUS_ENUM_UINT8        enKeepAliveTimerStatus;
    CNAS_HSM_SESSION_STATUS_ENUM_UINT8  enSessionStatus;

    /* Get the Tsmpclose value from global variable. The unit is minutes */
    usTsmpClose = CNAS_HSM_GetTsmpClose();

    /* Get the Keep alive timer status */
    enKeepAliveTimerStatus = CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM, TI_CNAS_HSM_KEEP_ALIVE_TIMER, 0);

    /* Get the HRPD session status  */
    enSessionStatus = CNAS_HSM_GetSessionStatus();

    if (CNAS_TIMER_STATUS_RUNNING == enKeepAliveTimerStatus )
    {
        /* IF the timer is already running, first stop the Keep alive timer */
        CNAS_HSM_StopSessionKeepAliveProcedure();
    }

    /* Start the Session Keep alive process if the TsmpClose is not zero and session is also Open */
    if ((usTsmpClose != 0)
     && (CNAS_HSM_SESSION_STATUS_OPEN == enSessionStatus))
    {
        /* If Tsmpclose is non zero, Set timer len = Tsmpclose/3(converted to millisec) */
        ulKeepAliveTimerLen = ((VOS_UINT32)usTsmpClose * CNAS_HSM_MIN_TO_MILLISEC) / CNAS_HSM_SMP_KEEP_ALIVE_LIMIT;

        /* Start the Keep alive Process */
        CNAS_HSM_StartSessionKeepAliveProcedure(ulKeepAliveTimerLen);
    }

    return;
}


/*****************************************************************************
Function Name   :   CNAS_HSM_ProcKeepAliveTimerRcvPowerOff
Description     :   The function is used to judge if the Keep alive timer must be stopped for the Power Off
                    scene. The function also stops the keep alive timer, if the timer is running
Input parameters:   None
Output parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2015-05-29
        Author  :   a00295761
        Modify content :Create

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity
*****************************************************************************/

VOS_VOID CNAS_HSM_ProcKeepAliveTimerRcvPowerOff(VOS_VOID)
{
    CNAS_HSM_SESSION_STATUS_ENUM_UINT8  enCurrSessionStatus;

    enCurrSessionStatus = CNAS_HSM_GetSessionStatus();

    if (CNAS_HSM_SESSION_STATUS_BUTT == enCurrSessionStatus)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_ProcKeepAliveTimerRcvPowerOff: curr Session Type is BUTT!");
    }

    /* Save the Session Keep Alive Info to NV */
    CNAS_HSM_SaveSessionKeepAliveInfo(enCurrSessionStatus);

    /* Stop the Keep alive timer */
    CNAS_HSM_StopSessionKeepAliveProcedure();

    return;
}




VOS_VOID CNAS_HSM_ProcKeepAliveTimerRcvKeepAliveMsg(VOS_VOID)
{
    VOS_UINT16                          usTsmpClose;
    VOS_UINT32                          ulKeepAliveTimerLen;

    /* Get the Tsmpclose value from global variable. The unit is minutes */
    usTsmpClose = CNAS_HSM_GetTsmpClose();

    if (0 == usTsmpClose)
    {
        /* If Tsmpclose is zero, do not Restart the keep alive timer. */
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_ProcKeepAliveTimerRcvKeepAliveMsg: TsmpClose is zero!");

        return;
    }

    /* If Tsmpclose is non zero,  Restart the Keep alive timer. First stop the keep alive timer */
    CNAS_HSM_StopSessionKeepAliveProcedure();

    /* If Tsmpclose is non zero, Set timer len = Tsmpclose/3(converted to millisec) */
    ulKeepAliveTimerLen = ((VOS_UINT32)usTsmpClose * CNAS_HSM_MIN_TO_MILLISEC) / CNAS_HSM_SMP_KEEP_ALIVE_LIMIT;

    /* Start the Keep alive Process */
    CNAS_HSM_StartSessionKeepAliveProcedure(ulKeepAliveTimerLen);

    return;
}


/*****************************************************************************
Function Name   :   CNAS_HSM_ProcKeepAliveTimerFwdTrafDataRcvd
Description     :   THe function starts the Keep alive timer with timer length based on the System Tick at the
                    time of last received forward traffic channel data
Input parameters:   None
Output parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2015-05-29
        Author  :   a00295761
        Modify content :Create

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity
*****************************************************************************/

VOS_VOID CNAS_HSM_ProcKeepAliveTimerFwdTrafDataRcvd(VOS_VOID)
{
    VOS_UINT32                          ulSysTickFwdTrafChan;
    VOS_UINT16                          usTsmpClose;
    VOS_UINT32                          ulSysTickCurTick;
    VOS_UINT32                          ulExpiredTick;
    VOS_UINT32                          ulKeepAliveTimerLen;

    /* Get the Tsmpclose value. Unit Is minutes */
    usTsmpClose = CNAS_HSM_GetTsmpClose();

    /* Get The System Tick at the time of last received forward traffic channel data */
    ulSysTickFwdTrafChan = CNAS_HSM_GetSysTickFwdTrafficChan();

    /* Get the current System Tick. The System Tick is in units of 10 milliseconds */
    ulSysTickCurTick = CNAS_HSM_GetSysTick();

    /* Calculate the number of Sys Ticks expired since the last received Fwd Traffic Chan Data */
    if (ulSysTickCurTick < ulSysTickFwdTrafChan)
    {
        /* In this case the Sys Tick has reversed. */
        ulExpiredTick = ulSysTickCurTick + (CNAS_HSM_MAX_SYS_TICK - ulSysTickFwdTrafChan);

        CNAS_INFO_LOG(UEPS_PID_HSM, "CNAS_HSM_ProcKeepAliveTimerRcvFwdTrafData: Sys Tick has wrapped around!");
    }
    else
    {
        ulExpiredTick = ulSysTickCurTick - ulSysTickFwdTrafChan;
    }

    if (0 == usTsmpClose)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_ProcKeepAliveTimerFwdTrafDataRcvd: TsmpClose Timer Len is zero!");
    }

    /* Set the Keep Alive timer length so that Keep alive timer expires Tsmpclose/3 minutes after the time of last
    received Forward Traffic channel data. (1 millisec = 1/10 SysTick) */
    ulKeepAliveTimerLen = (((VOS_UINT32)usTsmpClose * CNAS_HSM_MIN_TO_MILLISEC) / CNAS_HSM_SMP_KEEP_ALIVE_LIMIT)
                           - (ulExpiredTick * CNAS_HSM_SYS_TICK_TO_MILLISEC);

    /* Reset the Keep Alive Req Snd Count to zero */
    CNAS_HSM_SetKeepAliveReqSndCount(0);

    /* Start the Keep alive timer with the timer calculated above */
    CNAS_HSM_StartSessionKeepAliveProcedure(ulKeepAliveTimerLen);

    return;
}




VOS_VOID CNAS_HSM_ProcKeepAliveTimerNotFullyExpired(VOS_VOID)
{
    VOS_UINT32                          ulTotalTimerRunCount;
    VOS_UINT32                          ulTimerExpiredCount;
    VOS_UINT32                          ulKeepAliveTimerLen;
    VOS_UINT32                          ulTimerLen;

    /* Get the Total Timer Run count and total Time Expired count */
    ulTotalTimerRunCount = CNAS_HSM_GetKeepAliveTimerTotalRunCount();
    ulTimerExpiredCount  = CNAS_HSM_GetKeepAliveTimerExpiredCount();
    ulKeepAliveTimerLen  = CNAS_HSM_GetKeepAliveTimerLen();

    if (ulTimerExpiredCount > ulTotalTimerRunCount)
    {
        /* If the Timer Expired count is greater than or equal to the total run count, make an error log */
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_ProcKeepAliveTimerNotFullyExpired: KeepAliveTimer HAS fully expired!");

        return;
    }

    /* Check if the timer must be started for the last time to reach the required KeepAliveTimerLen*/
    if (ulTimerExpiredCount == ulTotalTimerRunCount - 1)
    {
        /* At the last timer run, the timer len must be set to CNAS_HSM_MAX_TIMER_LEN if ulKeepAliveTimerLen is a multiple
        of CNAS_HSM_MAX_TIMER_LEN */
        if (ulKeepAliveTimerLen % CNAS_HSM_MAX_TIMER_LEN == 0)
        {
            ulTimerLen = CNAS_HSM_MAX_TIMER_LEN;
        }
        else
        {
            /* if ulKeepAliveTimerLen is not a multiple of CNAS_HSM_MAX_TIMER_LEN, then the Timer Len must be set to the
               remainder of ulKeepAliveTimerLen/CNAS_HSM_MAX_TIMER_LEN */
            ulTimerLen = ulKeepAliveTimerLen % CNAS_HSM_MAX_TIMER_LEN;
        }
    }
    else
    {
        /* At some intermediate timer expired count value, Set the timer len to CNAS_HSM_MAX_TIMER_LEN */
        ulTimerLen = CNAS_HSM_MAX_TIMER_LEN;
    }

    /* Start the Keep alive timer */
    CNAS_HSM_StartTimer(TI_CNAS_HSM_KEEP_ALIVE_TIMER, ulTimerLen);

    return;
}




VOS_VOID CNAS_HSM_SaveSessionKeepAliveInfo(
    CNAS_HSM_SESSION_STATUS_ENUM_UINT8  ucSessionStatus
)
{
    VOS_UINT16                          usTsmpClose;
    VOS_UINT32                          ulTsmpCloseRemainTime;

    if (CNAS_HSM_SESSION_STATUS_CLOSE == ucSessionStatus)
    {
        /* if the Session is not open, then set the Session Open flag to FALSE, Tsmpclose to default value of 54 hours,
        Tsmpclose_Remain_Time to 54 hours */
        CNAS_HSM_SetKeepAliveInfoValidFlag(VOS_FALSE);
        CNAS_HSM_SetTsmpClose(CNAS_HSM_DEFAULT_TSMP_CLOSE_LEN);
        CNAS_HSM_SetTsmpCloseRemainTime(CNAS_HSM_DEFAULT_TSMP_CLOSE_REMAIN_LEN);
        return;
    }

    CNAS_HSM_SetKeepAliveInfoValidFlag(VOS_TRUE);

    usTsmpClose = CNAS_HSM_GetTsmpClose();

    if (0 == usTsmpClose)
    {
        CNAS_HSM_SetTsmpCloseRemainTime(0);

        /* If TsmpClose is zero, HSM need not update the Power Off Sys time as HSM need not judge if session has
        expired in the next switch On event */
        return;
    }

     /* The below judge is used to handle the case where HSM does not receive Sys Acq Ind or IRAT to HRPD Ind after
        Switch ON and the Session before last Power Off is still valid and not expired. In this case, the keep alive timer
        will not be running. HSM need not update the TsmpClose remain time and the Power off sys time.
        HSM can use the NV values from the last session and still judge if the session has not expired in the next First
        System Acquire Session Activate flow */
    if (CNAS_TIMER_STATUS_RUNNING == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM, TI_CNAS_HSM_KEEP_ALIVE_TIMER, 0))
    {
        /* If the session is open and Tsmpclose is not zero, calculate the Tsmpclose remaining time. */
        ulTsmpCloseRemainTime   = CNAS_HSM_CalculateTsmpCloseRemainTime();

        /* Set the TsmpClose Remaining time. Unit is seconds */
        CNAS_HSM_SetTsmpCloseRemainTime(ulTsmpCloseRemainTime);

        /* Save the Current Sys Time to the global variable */
        CNAS_HSM_SavePowerOffSysTime();
    }

    return;
}




VOS_UINT32 CNAS_HSM_CalculateTsmpCloseRemainTime(VOS_VOID)
{
    VOS_UINT8                           ucKeepAliveReqSndCount;
    VOS_UINT32                          ulKeepAliveTimerRemainLen;
    VOS_UINT32                          ulKeepAliveTimerRemainLenInSec;
    VOS_UINT32                          ulRemainLen;
    VOS_UINT32                          ulTotalTimerRunCount;
    VOS_UINT32                          ulTimerExpiredCount;
    VOS_UINT32                          ulTsmpCloseRemainTime;
    VOS_UINT16                          usTsmpClose;

    /* Get the Keep Alive Req Snd Count, Total Timer Run Count, Total Timer Expired Count  */
    ucKeepAliveReqSndCount = CNAS_HSM_GetKeepAliveReqSndCount();
    ulTotalTimerRunCount   = CNAS_HSM_GetKeepAliveTimerTotalRunCount();
    ulTimerExpiredCount    = CNAS_HSM_GetKeepAliveTimerExpiredCount();

    /* Get the value of TsmpClose. Unit is Minutes */
    usTsmpClose            = CNAS_HSM_GetTsmpClose();

    /* If Keep Alive Req Snd Count is greater than or equal to 3, return 0 as TsmpClose time duration has expired */
    if (CNAS_HSM_SMP_KEEP_ALIVE_LIMIT <= ucKeepAliveReqSndCount)
    {
        return 0;
    }

    /* Get the keep alive timer remaining length. Unit is MilliSec */
    ulRemainLen = CNAS_GetSpecifiedTimerRemainLen(UEPS_PID_HSM, TI_CNAS_HSM_KEEP_ALIVE_TIMER, 0);

    ulKeepAliveTimerRemainLen = ulRemainLen + ((ulTotalTimerRunCount - ulTimerExpiredCount - 1)
                                                  * CNAS_HSM_MAX_TIMER_LEN);

    /* Convert the Keep Alive Timer Len from Millisec to seconds */
    ulKeepAliveTimerRemainLenInSec = ulKeepAliveTimerRemainLen / CNAS_HSM_SEC_TO_MILLISEC;

    /* Find the TsmpClose_Remain_Len  */
    ulTsmpCloseRemainTime = ulKeepAliveTimerRemainLenInSec
                                   + ((((VOS_UINT32)usTsmpClose * CNAS_HSM_MIN_TO_SEC) / CNAS_HSM_SMP_KEEP_ALIVE_LIMIT)
                                    * (CNAS_HSM_SMP_KEEP_ALIVE_LIMIT - 1 - ucKeepAliveReqSndCount));


    return ulTsmpCloseRemainTime;
}




VOS_VOID CNAS_HSM_SavePowerOffSysTime(VOS_VOID)
{
    VOS_UINT32                          ulCurrentSysTick;
    VOS_UINT32                          ulReferenceSysTick;
    VOS_UINT32                          ulExpiredSysTick;
    VOS_UINT32                          aulCurSysTime[CNAS_HSM_NUM_WORDS_IN_CDMA_SYS_TIME];
    VOS_UINT32                         *pulSysTime;
    CNAS_HSM_64_BIT_DATA_STRU           stAddend;
    CNAS_HSM_64_BIT_DATA_STRU           stRslt;

    NAS_MEM_SET_S(aulCurSysTime, sizeof(aulCurSysTime), 0x00, sizeof(VOS_UINT32) * CNAS_HSM_NUM_WORDS_IN_CDMA_SYS_TIME);
    NAS_MEM_SET_S(&stAddend, sizeof(stAddend), 0x00, sizeof(CNAS_HSM_64_BIT_DATA_STRU));
    NAS_MEM_SET_S(&stRslt, sizeof(stRslt), 0x00, sizeof(CNAS_HSM_64_BIT_DATA_STRU));

    /* Get the Last Received System Time Global variable. Contains the CDMA Sys time in Millisec */
    pulSysTime = CNAS_HSM_GetLastReceivedSysTime();

    /* Get the current system tick and the initial system tick */
    ulCurrentSysTick     = CNAS_HSM_GetSysTick();
    ulReferenceSysTick   = CNAS_HSM_GetReferenceSysTick();

    /* Calculate the number of Sys Ticks expired since the last received Fwd Traffic Chan Data */
    if (ulCurrentSysTick < ulReferenceSysTick)
    {
        /* In this case the Sys Tick has reversed. */
        ulExpiredSysTick = ulCurrentSysTick + (CNAS_HSM_MAX_SYS_TICK - ulReferenceSysTick);

        CNAS_INFO_LOG(UEPS_PID_HSM, "CNAS_HSM_SaveCurrentSysTime: Sys Tick has wrapped around.");
    }
    else
    {
        ulExpiredSysTick = ulCurrentSysTick - ulReferenceSysTick;
    }

    /* 1 millisec = 1/10 Sys Tick. Convert to millisec */
    ulExpiredSysTick *= CNAS_HSM_SYS_TICK_TO_MILLISEC;

    /* Add the Expired Sys Tick in milliseconds to the Sys Time */
    stAddend.ulHigherOrderWord = pulSysTime[1];
    stAddend.ulLowerOrderWord  = pulSysTime[0];

    CNAS_HSM_64Add32(&stAddend, ulExpiredSysTick, &stRslt);

    /* Set the System time global variable to the new value */
    aulCurSysTime[1] = stRslt.ulHigherOrderWord;
    aulCurSysTime[0] = stRslt.ulLowerOrderWord;

    CNAS_HSM_SetLastPowerOffSysTime(aulCurSysTime);

    return;
}




VOS_UINT32 CNAS_HSM_IsTsmpCloseValueChanged(
    VOS_UINT16                          usNewTsmpClose
)
{
    VOS_UINT16                          usOldTsmpClose;

    usOldTsmpClose = CNAS_HSM_GetTsmpClose();

    if (usNewTsmpClose != usOldTsmpClose)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}




VOS_UINT32 CNAS_HSM_IsSessionExpired(
    VOS_UINT32                         *pulCurSysTime,
    VOS_UINT32                         *pulOldSysTime
)
{
    VOS_UINT32                          ulTsmpCloseRemainTime;
    CNAS_HSM_64_BIT_DATA_STRU           stMinuend;
    CNAS_HSM_64_BIT_DATA_STRU           stSubtrahend;
    CNAS_HSM_64_BIT_DATA_STRU           stTimeInterval;

    /* If Tsmpclose is zero, then the session has not expired */
    if (0 == CNAS_HSM_GetTsmpClose())
    {
        return VOS_FALSE;
    }

    /* Get the TsmpClose_Remain_time value from the session Keep alive Info. Units in Seconds */
    ulTsmpCloseRemainTime = CNAS_HSM_GetTsmpCloseRemainTime();

    /* Calculate the time interval since last power off and store in stTimeInterval */
    stMinuend.ulHigherOrderWord     = pulCurSysTime[1];
    stMinuend.ulLowerOrderWord      = pulCurSysTime[0];
    stSubtrahend.ulHigherOrderWord  = pulOldSysTime[1];
    stSubtrahend.ulLowerOrderWord   = pulOldSysTime[0];

    CNAS_HSM_64Sub64(&stMinuend, &stSubtrahend, &stTimeInterval);

    if ((stTimeInterval.ulHigherOrderWord > 0)
     || (stTimeInterval.ulLowerOrderWord >= ulTsmpCloseRemainTime * CNAS_HSM_SEC_TO_MILLISEC))
    {
        /* If the time interval since last power off is greater than the Tsmpclose remain time, the session has expired */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
Function Name   :   CNAS_HSM_IsNeedSessionRecovery
Description     :   The function is used to judge if HSM must perform Session recovery after first sys acq
Input parameters:   pulCurSysTime - current cdma sys time  (unit is ms)
Outout parameters:  pstOldSysTime - old cdmas sys time (unit is ms)
Return Value    :   VOS_TRUE: If session must be recovered

Modify History  :
1)  Date           : 2015-06-08
    Author         : a00295761
    Modify content : Create
2)  Date           : 2015-09-22
    Author         : t00323010
    Modify content : HSM MNTN(DTS2015092201636): log recovery judge related info
3)  Date           : 2015-12-21
    Author         : m00312079
    Modify content : DTS2015120208895: 如果UE的版本信息开关机后发生变化，则不进行recovery流程，直接发起初始协商
*****************************************************************************/

VOS_UINT8 CNAS_HSM_IsNeedSessionRecovery(
    VOS_UINT32                         *pulCurSysTime,
    VOS_UINT32                         *pulOldSysTime
)
{
    VOS_UINT8                                               ucCardChangedFlg;
    CNAS_HSM_SESSION_STATUS_ENUM_UINT8                      enSessionStatus;
    VOS_UINT8                                               ucIsKeepAliveInfoValid;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enLastSessionType;
    VOS_UINT32                                              ulIsCurrentSupportEhrpd;
    VOS_UINT32                                              ulIsSessionExpired;
    CNAS_HSM_CARD_STATUS_CHANGE_INFO_STRU                  *pstCardStatusChgInfo = VOS_NULL_PTR;

    ulIsSessionExpired      = VOS_FALSE;

    /* Get the last HRPD Session Status (value is from NV) */
    enSessionStatus         = CNAS_HSM_GetLastHrpdSessionStatus();

    /* Get the Keep Alive Info Valid flag */
    ucIsKeepAliveInfoValid  = CNAS_HSM_GetKeepAliveInfoValidFlag();

    /* Judge if the ICC ID and hardware ID have changed */
    ucCardChangedFlg = CNAS_HSM_IsCardChanged();

    ulIsSessionExpired      = CNAS_HSM_IsSessionExpired(pulCurSysTime, pulOldSysTime);

    CNAS_HSM_LogSessionRecoveryJudgeInfo(ucCardChangedFlg, ulIsSessionExpired);

    /* 将pre的状态设置为cur的状态 */
    pstCardStatusChgInfo = CNAS_HSM_GetCardStatusChangeInfoAddr();
    pstCardStatusChgInfo->ucIsPreCardPresent = pstCardStatusChgInfo->ucIsCurCardPresent;

    if ((CNAS_HSM_SESSION_STATUS_OPEN == enSessionStatus)
     && (VOS_TRUE == ucIsKeepAliveInfoValid)
     && (VOS_FALSE == ucCardChangedFlg))
    {
        /* Judge if the HRPD session has expired if all the below conditions are true:
        1. Session status is OPEN (read from NV)
        2. Keep alive info valid flag (read from NV) is true
        3. card has not changed
        4. UE rev info has not changed
        5. besides:
            a. NV store session type is EHRPD, if NV changed to not support EHRPD, no need to do recovery
            b. NV store session type is HRPD, if NV support EHRPD, no need to do recovery */

        if (VOS_TRUE == CNAS_HSM_IsUERevInfoChanged())
        {
            return VOS_FALSE;
        }

        /* session type is eHRPD before switch on, eHRPD is not supported after switch on，
         * recovery process should not be performed in this case
         */
        enLastSessionType       = CNAS_HSM_GetLastSessionType();
        ulIsCurrentSupportEhrpd = CNAS_HSM_IsCurrentCapSupportEhrpd();

        if ((CNAS_HSM_SESSION_TYPE_EHRPD == enLastSessionType)
         && (VOS_FALSE == ulIsCurrentSupportEhrpd))
        {
            return VOS_FALSE;
        }

        /* 定制需求，在开机或者进出飞行模式后，如果AT支持EHRPD，需要优先尝试协商EHRPD session */
        if ((CNAS_HSM_SESSION_TYPE_HRPD == enLastSessionType)
         && (VOS_TRUE == ulIsCurrentSupportEhrpd))
        {
            return VOS_FALSE;
        }

        /* Judge if session has expired */
        if (VOS_FALSE == ulIsSessionExpired)
        {
            return VOS_TRUE;
        }

    }

    return VOS_FALSE;
}




VOS_VOID CNAS_HSM_CalcTsmpCloseRemainTimeAfterFirstSysAcq(
    VOS_UINT32                         *pulNewSysTime,
    VOS_UINT32                         *pulOldSysTime
)
{
    VOS_UINT32                          ulTsmpCloseRemainTime;
    CNAS_HSM_64_BIT_DATA_STRU           stMinuend;
    CNAS_HSM_64_BIT_DATA_STRU           stSubtrahend;
    CNAS_HSM_64_BIT_DATA_STRU           stTimeInterval;

    /* Get the TsmpClose_Remain_time value from the session Keep alive Info. Units in Seconds */
    ulTsmpCloseRemainTime = CNAS_HSM_GetTsmpCloseRemainTime();

    /* Calculate the time interval since last power off and store in stTimeInterval */
    stMinuend.ulHigherOrderWord     = pulNewSysTime[1];
    stMinuend.ulLowerOrderWord      = pulNewSysTime[0];
    stSubtrahend.ulHigherOrderWord  = pulOldSysTime[1];
    stSubtrahend.ulLowerOrderWord   = pulOldSysTime[0];

    CNAS_HSM_64Sub64(&stMinuend, &stSubtrahend, &stTimeInterval);

    /* update the Tsmpclose_Remain_time in Keep alive timer ctx. Unit of stTimeInterval is millisec */
    ulTsmpCloseRemainTime = ulTsmpCloseRemainTime - (stTimeInterval.ulLowerOrderWord / CNAS_HSM_SEC_TO_MILLISEC);

    CNAS_HSM_SetTsmpCloseRemainTime(ulTsmpCloseRemainTime);

}

/*****************************************************************************
Function Name   :   CNAS_HSM_ProcKeepAliveTimerFwdTrafDataNotRcvd
Description     :   The function is used to handle the scence that no forward
                    traffic channel data was received during the time ulKeepAliveTimerLen
Input parameters:   None
Output parameters:  None
Return Value    :   VOS_VOID

Modify History  :
1)  Date           : 2015-10-08
    Author         : w00351686
    Modify content : Create
2)  Date           : 2015-12-25
    Author         : m00312079
    Modify content : DTS2015121807624:当DO处于从模或者掉网时不发送keep alive req
*****************************************************************************/
VOS_VOID CNAS_HSM_ProcKeepAliveTimerFwdTrafDataNotRcvd(VOS_VOID)
{
    VOS_UINT8                                               ucKeepAliveReqSndCount;
    VOS_UINT16                                              usTsmpClose;
    CNAS_HSM_L1_STA_ENUM_UINT32                             enMainState;
    CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16                    enConvertedCasStatus;

    enMainState          = CNAS_HSM_GetCurrMainState();

    /* Increment the KeepAliveReqSndCount global variable and save the value to global variable */
    ucKeepAliveReqSndCount = CNAS_HSM_GetKeepAliveReqSndCount();
    ucKeepAliveReqSndCount++;
    CNAS_HSM_SetKeepAliveReqSndCount(ucKeepAliveReqSndCount);

    if (CNAS_HSM_SMP_KEEP_ALIVE_LIMIT == ucKeepAliveReqSndCount)
    {
        /* Send internal message to deactivate the session as TsmpClose has expired in this case */
        if (CNAS_HSM_L1_STA_SLAVE == enMainState)
        {
            CNAS_HSM_SndInternalSessionCloseInd(
                               CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_KEEP_ALIVE_EXP_SLAVE,
                               VOS_NULL_PTR);
        }
        else
        {
            CNAS_HSM_SndInternalSessionCloseInd(
                               CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_KEEP_ALIVE_EXP_OPEN,
                               VOS_NULL_PTR);
        }
    }
    else
    {
        /* Get the TsmpClose value. Unit is minutes */
        usTsmpClose = CNAS_HSM_GetTsmpClose();

        if (0 == usTsmpClose)
        {
            CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvTiKeepAliveTimerExpired_PreProc: TsmpClose Timer len is zero!");
        }

        /* Start the Keep Alive Timer with timer len TsmpClose/Nsmpkeepalive */
        CNAS_HSM_StartSessionKeepAliveProcedure(((VOS_UINT32)usTsmpClose * CNAS_HSM_MIN_TO_MILLISEC) / CNAS_HSM_SMP_KEEP_ALIVE_LIMIT);

        enConvertedCasStatus = CNAS_HSM_GetHrpdConvertedCasStatus();

        /* 当DO处于从模或者掉网时不发送keep alive req */
        if ((CNAS_HSM_L1_STA_SLAVE              == enMainState)
         || (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == enConvertedCasStatus))
        {
            return;
        }

        /* If the KeepAiveReqSndCount is less than Nsmpkeepalive, then HSM must send Keep Alive Req to AN. */
        CNAS_HSM_SndCasHrpdSessionBeginNtf(CNAS_CAS_HRPD_SESSION_TYPE_MO_KEEP_ALIVE);

        CNAS_HSM_SndKeepAliveReqMsg();

        CNAS_HSM_StartTimer(TI_CNAS_HSM_MO_KEEP_ALIVE_WAIT_SNP_DATA_CNF, TI_CNAS_HSM_WAIT_SNP_DATA_CNF_LEN);

        CNAS_HSM_VoteExitSlottedMode(CNAS_HSM_SLOT_VOTE_TYPE_KEEP_ALIVE_PROCEDURE);

        CNAS_HSM_StartTimer(TI_CNAS_HSM_WAIT_KEEP_ALIVE_RSP,
                            TI_CNAS_HSM_WAIT_KEEP_ALIVE_RSP_LEN);
    }

    return;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





