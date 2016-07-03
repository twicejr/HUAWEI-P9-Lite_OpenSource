

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_PAL_Net.h"
#include "BST_PAL_Thread.h"
#include "BST_PAL_Timer.h"
#include "BST_OS_Thread.h"

#include "vos.h"
#if (VOS_RTOSCK == VOS_OS_VER)
#include "sre_sem.h"
#else
#include <semLib.h>
#endif 

#include "PsCommonDef.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_PAL_TIMER_C
/*lint +e767*/
/******************************************************************************
   2 宏定义
******************************************************************************/

/*****************************************************************************
  3 函数声明
*****************************************************************************/
BST_VOID    BST_OS_PalTimerCallBack ( BST_VOID );
BST_UINT32  BST_OS_TimerChkNearest  ( BST_VOID );
/******************************************************************************
   4 私有定义
******************************************************************************/

/******************************************************************************
   5 全局变量定义
******************************************************************************/
HTIMER                                  g_BstTimer;
/******************************************************************************
   6 函数实现
******************************************************************************/


BST_VOID BST_OS_PalTimerStart( BST_UINT32 ulLength )
{
    BST_RLS_LOG1( "BST_OS_PalTimerStart : Length.", ulLength );
    if ( VOS_NULL_PTR != g_BstTimer )
    {
        if ( VOS_OK != PS_STOP_REL_TIMER( &g_BstTimer ) )
        {
            BST_RLS_LOG( "BST_OS_PalTimerStart : Start(Stop) Tmr Fail." );
            return;
        }
    }
    if ( VOS_OK != PS_START_REL_TIMER(  &g_BstTimer,
                                        UEPS_PID_BASTET,
                                        ulLength,
                                        0,
                                        0,
                                        VOS_RELTIMER_NOLOOP) )
    {
        BST_RLS_LOG( "BST_OS_PalTimerStart : Start Tmr Fail." );
        return ;
    }
}

BST_VOID BST_OS_PalTimerStop( BST_VOID )
{
    if ( VOS_NULL_PTR == g_BstTimer )
    {
        return;
    }
    if ( VOS_OK != PS_STOP_REL_TIMER( &g_BstTimer ) )
    {
        BST_RLS_LOG( "BST_OS_PalTimerStart : Start(Stop) Tmr Fail." );
    }
}

BST_VOID BST_OS_PalTimerInit( BST_VOID )
{
    g_BstTimer                          = BST_NULL_PTR;
}

BST_VOID BST_OS_PalTimerCallBack( BST_VOID )
{
    BST_UINT32                          ulNearestTime;

    ulNearestTime                       = BST_OS_TimerChkNearest();
    if( 0 != ulNearestTime )
    {
        BST_OS_PalTimerStart( ulNearestTime );
    }
}

BST_UINT32 BST_OS_PalTimerNowMs( BST_VOID )
{
    BST_UINT32                          ulSysNow;

    ulSysNow    = VOS_GetTick();
    ulSysNow   *= BST_OS_TICKS_MS;

    return ulSysNow;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


