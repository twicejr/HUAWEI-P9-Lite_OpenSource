/*******************************************************************************
*                                                                              *
*        Copyright 2003-2006  Huawei Technologies India Private Limited        *
*                          All Rights Reserved                                 *
*                                                                              *
*------------------------------------------------------------------------------*
*                                                                              *
*                              twl_api.h                                       *
*                                                                              *
*    Project Code:  VRP5.0                                                     *
*    Module Name:   Timing Wheel (TWL) Module                                  *
*    Create Date:  2003/08/03                                                  *
*         Author:  Rainbow                                                     *
*     Description: This header file list funtion prototypes for twl api.       * 
*   TWL provide a high efficent timer extention mechanism .With the            * 
*   mechanism you can support several thousands of logical timers , but        * 
*   only one vos timer is need.                                                *
*   App module who use TWL must include this header file.                      *
*                                                                              *
*------------------------------------------------------------------------------*
*  Modification History                                                        *
*  DATE        NAME             DESCRIPTION                                    *
*  --------------------------------------------------------------------------  *
*  2003-08-03  Rainbow           Create                                        *
*                                                                              *
*******************************************************************************/

#ifndef _TWL_API_H
#define _TWL_API_H

#define TWL_MAX_DEFAULT_WHEEL_SCALE    3600
#define TWL_MAX_WHEEL_SCALE       64000
#define TWL_MIN_WHEEL_SCALE       128
#define TWL_MAX_USE_PARA_LEN      4

typedef GADS_HANDLE TWL_HANDLE;
#define TWL_INVALID_HANDLE   GADS_INVALID_HANDLE    
#define TWL_ATTR_PERIODICAL    0x01
#define TWL_ATTR_NON_PERIODICAL   0x02
#define TWL_INVALID_TIMER_ID   0xFFFFFFFF

/*Time unit in timing wheel*/
typedef enum tagTWL_TIME_UNIT_E
{
    TWL_TIME_UNIT_100MS = 100 ,  /*100ms*/
    TWL_TIME_UNIT_500MS = 500,  /*100ms*/
    TWL_TIME_UNIT_1000MS= 1000  /*1000ms*/
}TWL_TIME_UNIT_E;

/*State for twl*/
typedef enum tagTWL_STATE_E
{
    TWL_SUSPENDING = 0,
    TWL_ACTIVE,
    TWL_TOBEDELETED,
    TWL_TOBEREFRESHED,
    TWL_TOBESUSPENDED
}TWL_STATE_E;

/*call back function provided by app module*/
typedef ULONG (*TWL_CALLBACK)(UINTPTR aulPara[TWL_MAX_USE_PARA_LEN]) ; 

#ifdef __cplusplus
extern "C"
{
#endif
/*******************************************************************************
* FUNCTION: 
*   Create Timing Wheel Instance. 
* INPUT:
*   ulMaxNum:  Max number of logical timer in this twl instance.
*   eTimeUnit: time unit in the timing wheel insance. Current only support: 
*         100ms / 500ms / 1000ms
*   ulScale :  Total scale in one circle of timing wheel. The default value is:
*         TWL_MAX_DEFAULT_WHEEL_SCALE = 3600. This value range from 128---64000.
* OUTPUT:
*   None
* RETURN: 
*   If success: Valid TWL handle for the Instance.
*   If fail: TWL_INVALID_HANDLE
*********************************************************************************/
TWL_HANDLE TWL_CreateTWLInstance(ULONG ulMaxNum, TWL_TIME_UNIT_E eTimeUnit , ULONG ulScale);

/*******************************************************************************
* FUNCTION: 
*   Activate a TWL instance after a twl instance is created.
* INPUT:
*   hTWL: the handle for a TWL instance to be resumed.
* OUTPUT:
*   None
* RETURN: 
*   If success: VOS_OK;
*   If fail: VOS_ERR;
*********************************************************************************/
ULONG TWL_ActivateInstance(TWL_HANDLE hTWL);

/*******************************************************************************
* FUNCTION: 
*   Delete a Timing Wheel Instance. 
* INPUT:
*    hTWL: the handle for a TWL instance to be deleted.
* OUTPUT:
*   None
* RETURN: 
*   If success: VOS_OK;
*   If fail: VOS_ERR;
*********************************************************************************/
ULONG TWL_DeleteTWLInstance(TWL_HANDLE hTWL);

/*******************************************************************************
* FUNCTION: 
*   Create non-periodical timer. 
* INPUT:
*    hTWL: the handle for a TWL instance to be deleted.
*    ulTimeValue: time interval fot this tiemr in millisecond and this value must be 
*          time of time unit provided TWL_CreateTWLInstance().
*    pfCallBack: Call back function for this timer.When timer is timrout TWL will 
*         Call this funtion. In this function you can only do little work, just
*         send an event or a message to your task or queue.
*    aulPara: App parameters.
*    
* OUTPUT:
*   None
* RETURN: 
*   If success: valid Timer id;
*   If fail: TWL_INVALID_TIMER_ID;
*********************************************************************************/
ULONG TWL_CreateNonPeriodTimer(TWL_HANDLE hTWL, ULONG ulTimeValue, 
             TWL_CALLBACK pfCallBack, UINTPTR ulPara[TWL_MAX_USE_PARA_LEN]);

/*******************************************************************************
* FUNCTION: 
*   Create periodical timer. 
* INPUT:
*    hTWL: the handle for a TWL instance to be deleted.
*    ulTimeValue: time interval fot this tiemr in millisecond and this value must be 
*          time of time unit provided TWL_CreateTWLInstance().
*    pfCallBack: Call back function for this timer.When timer is timrout TWL will 
*         Call this funtion. In this function you can only do little work, just
*         send an event or a message to your task or queue.
*    aulPara: App parameters.
*    
* OUTPUT:
*   None
* RETURN: 
*   If success: Invalid Timer id;
*   If fail: TWL_INVALID_TIMER_ID;
*********************************************************************************/
ULONG TWL_CreatePeriodTimer(TWL_HANDLE hTWL, ULONG ulTimeValue, 
           TWL_CALLBACK pfCallBack, UINTPTR ulPara[TWL_MAX_USE_PARA_LEN]);

/*******************************************************************************
* FUNCTION: 
*   Delete a  non-periodical / periodical timer. 
* INPUT:
*    hTWL: the handle for a TWL instance to be deleted.
*    ulTimerID: timer id to be deleted.
*    
* OUTPUT:
*   None
* RETURN: 
*   If success: VOS_OK;
*   If fail: VOS_ERR;
*********************************************************************************/
ULONG TWL_DeleteTimer(TWL_HANDLE hTWL, ULONG ulTimerID);

/*******************************************************************************
* FUNCTION: 
*   Suspend a  non-periodical / periodical timer. 
* INPUT:
*    hTWL: the handle for a TWL instance to be suspended.
*    ulTimerID: timer id to be suspended.
*    
* OUTPUT:
*   None
* RETURN: 
*   If success: VOS_OK;
*   If fail: VOS_ERR;
*********************************************************************************/
ULONG TWL_SuspendTimer(TWL_HANDLE hTWL, ULONG ulTimerID);

/*******************************************************************************
* FUNCTION: 
*   Resume a  non-periodical / periodical timer. 
* INPUT:
*    hTWL: the handle for a TWL instance to be resumed.
*    ulTimerID: timer id to be resumed.
*    
* OUTPUT:
*   None
* RETURN: 
*   If success: VOS_OK;
*   If fail: VOS_ERR;
*********************************************************************************/
ULONG TWL_ResumeTimer(TWL_HANDLE hTWL, ULONG ulTimerID);

/*******************************************************************************
* FUNCTION: 
*   For a given timer cancel old timing process and refresh it with new time value. 
* INPUT:
*    hTWL: the handle for a TWL instance to be deleted.
*    ulTimerID: timer id to be extended.
*    ulNewTimeValue : new time value.         
*    
* OUTPUT:
*   None
* RETURN: 
*   If success: VOS_OK;
*   If fail: VOS_ERR;
*********************************************************************************/
ULONG TWL_RefreshTimer(TWL_HANDLE hTWL, ULONG ulTimerID, ULONG ulNewTimeValue);

/*******************************************************************************
* FUNCTION: 
*   Tick function. When a TWL instance is working after each unit time passed this 
*   function must be called. Note: twl user maybe delete this timer in his/her callback
*   function.
* INPUT:
*   hTWL: the handle for a TWL instance to be deleted.
* OUTPUT:
*   None
* RETURN: 
*   If success: VOS_OK;
*   If fail: VOS_ERR;
*********************************************************************************/
ULONG TWL_TickProc(TWL_HANDLE hTWL);

/*******************************************************************************
* FUNCTION: 
*   Suspend a TWL instance. 
* INPUT:
*   hTWL: the handle for a TWL instance to be suspended.
* OUTPUT:
*   None
* RETURN: 
*   If success: VOS_OK;
*   If fail: VOS_ERR;
*********************************************************************************/
ULONG TWL_SuspendInstance(TWL_HANDLE hTWL);

/*******************************************************************************
* FUNCTION: 
*   Resume a TWL instance. 
* INPUT:
*   hTWL: the handle for a TWL instance to be resumed.
* OUTPUT:
*   None
* RETURN: 
*   If success: VOS_OK;
*   If fail: VOS_ERR;
*********************************************************************************/
ULONG TWL_ResumeInstance(TWL_HANDLE hTWL);

/*******************************************************************************
* FUNCTION: 
*   Get the static configured timer number. 
* INPUT:
*   hTWL: the handle.
* OUTPUT:
*   ulStaticMaxTimerNum: The max number of configure timers.
* RETURN: 
*   If success: VOS_OK;
*   If fail: VOS_ERR;
*********************************************************************************/
ULONG TWL_GetStaticCfgMaxTimerNum(TWL_HANDLE hTWL, ULONG *pulStaticMaxTimerNum);

/*******************************************************************************
* FUNCTION: 
*   Get the number of existed timers in a TWL instance. 
* INPUT:
*   hTWL: the handle.
* OUTPUT:
*   pulExistedTimerNum: Existed timer number in the TWL instance.
* RETURN: 
*   If success: VOS_OK;
*   If fail: VOS_ERR;
*********************************************************************************/
ULONG TWL_GetExistedTimerNum(TWL_HANDLE hTWL, ULONG *pulExistedTimerNum);

/*******************************************************************************
* FUNCTION: 
*   Get the state of a TWL instance. 
* INPUT:
*   hTWL: the handle.
* OUTPUT:
*   peState: the state of the twl instance.
* RETURN: 
*   If success: VOS_OK;
*   If fail: VOS_ERR;
*********************************************************************************/
ULONG TWL_GetInstanceState(TWL_HANDLE hTWL, TWL_STATE_E *peState);

/*******************************************************************************
* FUNCTION: 
*   Get the configured time unit type of a instance. 
* INPUT:
*   hTWL: the handle.
* OUTPUT:
*   peTimeUnitType: time unit type(100ms/500ms/1000ms)
* RETURN: 
*   If success: VOS_OK;
*   If fail: VOS_ERR;
*********************************************************************************/
ULONG TWL_GetCfgTimeUnitType(TWL_HANDLE hTWL, TWL_TIME_UNIT_E *peTimeUnitType);

/*******************************************************************************
* FUNCTION: 
*   Get the type of a timer: periodical or non-periodicall.  
* INPUT:
*   hTWL: the handle.
*   ulTimerID: timer id;
* OUTPUT:
*   pulTimeType: timer type(Periodical: TWL_ATTR_PERIODICAL Non-periodical:TWL_ATTR_NON_PERIODICAL)
* RETURN: 
*   If success: VOS_OK;
*   If fail: VOS_ERR;
*********************************************************************************/
ULONG TWL_GetCfgTimerType(TWL_HANDLE hTWL, ULONG ulTimerID, ULONG *pulTimeType);

/*******************************************************************************
* FUNCTION: 
*   Get the time value of a timer in millisecond, which provided by app user 
*   when this timer is created. 
* INPUT:
*   hTWL: the handle.
*   ulTimerID: timer id;
* OUTPUT:
*   pulTimeValue: rest time value for a timer in millisecond.
* RETURN: 
*   If success: VOS_OK;
*   If fail: VOS_ERR;
*********************************************************************************/
ULONG TWL_GetTimeValue(TWL_HANDLE hTWL, ULONG ulTimerID, ULONG *pulTimeValue);

/*******************************************************************************
* FUNCTION: 
*   Get the rest time value of a timer in millisecond. 
* INPUT:
*   hTWL: the handle.
*   ulTimerID: timer id;
* OUTPUT:
*   pulRestTimeValue: rest time value for a timer in millisecond.
* RETURN: 
*   If success: VOS_OK;
*   If fail: VOS_ERR;
*********************************************************************************/
ULONG TWL_GetRestTimeValue(TWL_HANDLE hTWL, ULONG ulTimerID, ULONG *pulRestTimeValue);

/*******************************************************************************
* FUNCTION: 
*   Get the state of a timer. (suspend or actived).
* INPUT:
*   hTWL: the handle.
*   ulTimerID: timer id;
* OUTPUT:
*   peState: timer state.
* RETURN: 
*   If success: VOS_OK;
*   If fail: VOS_ERR;
*********************************************************************************/
ULONG TWL_GetTimerState(TWL_HANDLE hTWL, ULONG ulTimerID,TWL_STATE_E *peState);

/*******************************************************************************
* FUNCTION: 
*   Get timer parameters.
* INPUT:
*   hTWL: the handle.
*   ulTimerID: timer id;
* OUTPUT:
*   ulPara[]: tiemr parameters.
* RETURN: 
*   If success: VOS_OK;
*   If fail: VOS_ERR;
*********************************************************************************/
ULONG TWL_GetTimerPara(TWL_HANDLE hTWL, ULONG ulTimerID, UINTPTR aulPara[TWL_MAX_USE_PARA_LEN]);

/*******************************************************************************
* FUNCTION: 
*   Set timer parameters and override original user parameters.
* INPUT:
*   hTWL: the handle.
*   ulTimerID: timer id;
* OUTPUT:
*   aulPara[]: tiemr parameters.
* RETURN: 
*   If success: VOS_OK;
*   If fail: VOS_ERR;
*********************************************************************************/
ULONG TWL_SetTimerPara(TWL_HANDLE hTWL, ULONG ulTimerID, UINTPTR aulPara[TWL_MAX_USE_PARA_LEN]);


/*******************************************************************************
* FUNCTION: 
*   Get the total time from the twl is initialized but not include suspending time.
* INPUT:
*   hTWL: the handle.
* OUTPUT:
* RETURN: 
*   Total time
*********************************************************************************/
ULONG TWL_GetTotalTimeFromBegin(TWL_HANDLE hTWL);

#ifdef __cplusplus
}
#endif

#endif