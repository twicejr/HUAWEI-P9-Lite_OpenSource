/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              fiba_synch.h
*
* Project Code: VISPV100R005
*  Module Name: SFIB4
* Date Created: 2003-07-08
*       Author: Zhang Hongyan
*  Description: Function prototypes for fib6a_synch.c
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2003-07-08   Zhang Hongyan           Create
*  2006-03-30   Jiangtao                Adjust for D00646
*  2006-04-21   Jiangtao                Adjust for D00859 
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _FIBA_SYNCH_H
#define _FIBA_SYNCH_H

#define FIB6A_TMR_REFRESH           (1000*60*60*24)
#define FIB6A_TMR_LOOP              VOS_TIMER_LOOP
#define FIB6A_TMR_NOLOOP            VOS_TIMER_NOLOOP
#define FIB6A_HA_SMOOTH_START       0x00000011
#define FIB6A_HA_SMOOTH_END         0x00000010

#define FIB6A_MAX_REFRESH_NUM       500
#define FIB6A_TMR_DOWNLOAD          50
#define FIB6A_TMR_WALKFORREFRESHING 5000
#define FIB6A_REFRESHING_ON         1
#define FIB6A_REFRESHING_START      2
#define FIB6A_REFRESHING_OFF        0
#define FIB6A_SMOOTH_ON             1
#define FIB6A_SMOOTH_OFF            0

#define FIB6A_RT_END                1
#define FIB6A_TMR_AGE               (2*FIB6A_TMR_REFRESH) + (1000*60*60*12)
#define FIB6A_TMR_WALKFORAGING      5000
#define FIB6A_TMR_GET_RMROUTES      200

#define FIB6A_MAX_FETCH_COUNT       3000
#define FIB6A_MAX_FASTDOWNLOAD_NUM  500
#define FIB6A_MAX_TIMES_AT_TIMESOUT 100
#define FIB6A_DEF_FASTDOWNLOAD_NUM  300
#define FIB6A_DEF_TIMES_AT_TIMESOUT 1

#define FIB6A_MAX_WALKFORAGE_NUM    3000

#define ST_COMPLETE                 0   
#define ST_HALF                     1   

extern ULONG IF_BoardIsUp ( ULONG ulSlot );
extern ULONG getSelfBoardId ();
extern ULONG VOS_time(ULONG *pulSecond);

ULONG IP6_FIBSynch_Init ();

VOID IP6_FIBSynch_TimerAge ();
STATIC VOID IP6_FIBSynch_StartTimerWalkForAging();
STATIC VOID IP6_FIBSynch_EndTimerWalkForAging();
VOID  IP6_FIBSynch_TimerWalkForAging();
VOID  IP6_FIBSynch_SetAgeTime ();
VOID  IP6_FIBSynch_GetRoutesFromRM ();

#endif  /* ifndef _FIB6A_SYNCH_H*/

#ifdef  __cplusplus
}
#endif

