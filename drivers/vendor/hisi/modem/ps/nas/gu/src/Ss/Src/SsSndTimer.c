/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SsSndTimer.c
  Description  : 发送Timer消息的处理
  Function List:
      1.  Ss_TimerStart         建立并启动Timer
      2.  Ss_TimerStop          停止并销毁Timer
  History:
      1.  张志勇 2004.03.09   新版作成
      2.  丁  庆 2006.11.07   问题单A32D07063
*******************************************************************************/

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif



/*=>A32D07063*/
#if 0

#include "SsInclude.h"

#define SS_TIMER_START(ulTimerId, TimerName, ulTimerLen) \
VOS_StartRelTimer(&g_SsTimerMng[ulTimerId].SsTimerId,\
                  WUEPS_PID_SS,\
                  ulTimerLen,\
                  TimerName,\
                  ulTimerId,\
                  VOS_RELTIMER_NOLOOP)

#define SS_TIMER_STOP(ulTimerId)  VOS_StopRelTimer(&g_SsTimerMng[ulTimerId].SsTimerId)

/***********************************************************************
*  MODULE   : Ss_TimerStart
*  FUNCTION : 建立并启动Timer
*  INPUT    : VOS_UINT8     ucTi         对应的Ti
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-09  新版作成
*     2.
************************************************************************/

VOS_VOID Ss_TimerStart(
                   VOS_UINT8 ucTi                                                   /* 对应的Ti                                 */
                   )
{
                                                 /* 发送的消息                               */
    VOS_UINT32       ulResult;                                                        /* 用于接收启动结果                         */

    if( SS_TIMER_IDLE == g_SsTimerMng[ucTi].ucTimerState )
    {                                                                           /* 判断指定Timer是否未启动                  */

        ulResult = SS_TIMER_START(ucTi, SS_T551, SS_T551_LEN * 1000);
        if( VOS_OK != ulResult)
        {
            SS_WARN_LOG( "\n [Error]Timer T551 Start Failure! \r" );
            return;
        }

        g_SsTimerMng[ucTi].ucTimerState = SS_TIMER_RUN;                         /* 设置Timer启动标志                        */


    }
}

/***********************************************************************
*  MODULE   : Ss_TimerStop
*  FUNCTION : 停止并销毁Timer
*  INPUT    : VOS_UINT8     ucTi           对应的Ti
*  OUTPUT   : 无
*  RETURN   : 无
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 03-12-10  新版作成
************************************************************************/

VOS_VOID Ss_TimerStop(
                  VOS_UINT8 ucTi                                                    /* 对应的Ti                                 */
                  )
{
    VOS_UINT32        ulResult;                                                        /* 用于接收停止结果                         */

    if( SS_TIMER_RUN == g_SsTimerMng[ucTi].ucTimerState )
    {                                                                           /* 此Timer在启动中                          */
        SS_TIMER_STOP(ucTi);
        if( VOS_OK != ulResult)
        {
            SS_WARN_LOG( "\n [Error]Timer Stop Failure! \r" );
        }

        SS_NORM_LOG("\n SS TimerStop: T551\r" );

        g_SsTimerMng[ucTi].ucTimerState = SS_TIMER_IDLE;                        /* 设置Timer已停止标志                      */


    }
}

#endif
/*<=A32D07063*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
