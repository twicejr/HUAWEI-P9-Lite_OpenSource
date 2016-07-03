

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_OS_Timer.h"
#include "BST_OS_Thread.h"
#include "BST_LIB_SnGenerator.h"
#include "BST_SRV_Event.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_OS_TIMER_CPP
/*lint +e767*/
/******************************************************************************
   2 宏定义
******************************************************************************/

/*****************************************************************************
  3 函数声明
*****************************************************************************/

/******************************************************************************
   4 私有定义
******************************************************************************/

/******************************************************************************
   5 全局变量定义
******************************************************************************/
BST_Lib_CSnGenrator<BST_OS_TIMERID_T>      *g_cBstOsTimerIdGenrator = BST_NULL_PTR;
LIST                   *g_pstOsTimerList = BST_NULL_PTR;
BST_OS_PAL_SPINLOCK_T                       g_BstTimerSpinLock;
extern "C" BST_UINT32                       BST_OS_TimerChkNearest( BST_VOID );
/******************************************************************************
   6 函数实现
******************************************************************************/


BST_UINT32 BST_OS_TimerNowMs( BST_VOID )
{
    return BST_OS_PalTimerNowMs();
}

BST_UINT32 BST_OS_TimeGetRemain( BST_OS_TIMERID_T ulId )
{
    BST_OS_LOCKCNT_T                    tThreadLockCnt;
    BST_UINT32                          ulSysNowMs;
    BST_UINT32                          ulRemainer;
    BST_UINT32                          ulTempVar;
    BST_UINT32                          ulRemainerSince0tick;
    ulRemainer                          = 0;
    tThreadLockCnt                      = BST_OS_ThreadLock();

    if ( ulId == BST_OS_INVALID_TIMER_ID )
    {
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return 0U;
    }
    BST_OS_TIMER_STRU *pstTimer = BST_OS_TimerSrch( ulId );

    if ( pstTimer == BST_NULL_PTR )
    {
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return 0U;
    }
    ulSysNowMs                  = BST_OS_TimerNowMs();
    if( ulSysNowMs < pstTimer->ulStartTime )
    {
        /* 这里是时间翻转才能走到的 */
        BST_DBG_LOG1("BST_OS_TimeGetRemain: time flipped while checking timer:%d ", ulId);
        ulTempVar               = BST_OS_MAX_UINT32 - pstTimer->ulStartTime;
        if( ulTempVar >= pstTimer->ulLength )
        {
            /* ulLength + ulStartTime未溢出32位UINT，判定定时器已经超时 */
            ulRemainer          = 0;
        }
        else
        {
            /*
               ulLength + ulStartTime溢出32位UINT，根据以下公式计算ulRemainer
               ulRemainerSince0tick：以刚经历的0tick为StartTime，计算得出的新的定时时长/剩余时间
               ulRemainerSince0tick    = ulLength - (0xFFFFFFFF - ulStartTime) - 1;
            */
            ulRemainerSince0tick           = pstTimer->ulLength - ulTempVar - 1;
            if(ulRemainerSince0tick < ulSysNowMs)
            {
                /* 如果ulRemainerSince0tick未超过当前时间，则判定定时器溢出 */
                ulRemainer      = 0;
            }
            else
            {
                ulRemainer      = ulRemainerSince0tick - ulSysNowMs;
            }
        }
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return ulRemainer;
    }

    ulRemainer                  = ulSysNowMs - pstTimer->ulStartTime;
    if( ulRemainer > pstTimer->ulLength )
    {
        ulRemainer              = 0;
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return ulRemainer;
    }
    ulRemainer                  = pstTimer->ulLength - ulRemainer;
    BST_OS_ThreadUnLock( tThreadLockCnt );
    return ulRemainer;
}

BST_BOOL BST_OS_TimerChkExpire(
    BST_UINT32  ulPastLength,
    BST_UINT32  ulTimerLength )
{
    if( ulPastLength >= ulTimerLength )
    {
        return BST_TRUE;
    }
    else if ( ( ulTimerLength - ulPastLength ) <= BST_OS_TIMER_PRECISION )
    {
        return BST_TRUE;
    }
    return BST_FALSE;
}


BST_UINT32 BST_OS_TimerChkNearest( BST_VOID )
{
    BST_OS_TIMER_STRU      *pstTimerIdx;
    BST_OS_TIMER_STRU      *pstTimerNextIdx;
    BST_UINT32              ulMinMs;
    BST_UINT32              ulRemainMs;
    BST_UINT32              ulPastMs;
    BST_UINT32              ulNowMs;
    BST_UINT32              ulThreadLockCnt;
    BST_UINT32              ulTempVar;
    BST_BOOL                bIsExpired;
    BST_ASSERT_NULL_RTN( g_pstOsTimerList, 0 );
    ulThreadLockCnt         = BST_OS_SpinLock( &g_BstTimerSpinLock );
BST_OS_TIMER_FIND_NEAREST:

    ulNowMs                 = BST_OS_TimerNowMs();
    ulPastMs                = 0;
    ulMinMs                 = 0;
    ulRemainMs              = 0;
    bIsExpired              = BST_FALSE;

    for ( pstTimerIdx = ( BST_OS_TIMER_STRU *)lstFirst( g_pstOsTimerList );
          pstTimerIdx!= BST_NULL_PTR ; 
          pstTimerIdx = pstTimerNextIdx)
    {
        pstTimerNextIdx     = ( BST_OS_TIMER_STRU *)lstNext( (NODE *)pstTimerIdx);

        if ( pstTimerIdx->ulStoped == BST_FALSE )
        {
            if( ulNowMs < pstTimerIdx->ulStartTime )
            {
                /* 这里是时间翻转才能走到的 */
                ulTempVar               = BST_OS_MAX_UINT32 - pstTimerIdx->ulStartTime;
                if( ulTempVar >= pstTimerIdx->ulLength )
                {
                    /* ulLength + ulStartTime未溢出32位UINT，判定定时器已经超时 */
                    pstTimerIdx->ulStoped    = BST_TRUE;
                    BST_SRV_ApiSendExpiredEvent( pstTimerIdx->pstRcver, pstTimerIdx->ulId );
                    goto BST_OS_TIMER_FIND_NEAREST;
                }
                else
                {
                    /*
                       处理时间反转: 定时器重设StartTime为0,并重新计算Length
                       newLength    = ulLength - (0xFFFFFFFF - ulStartTime) - 1 避免计算溢出
                       newStartTime = 0
                    */
                    pstTimerIdx->ulLength    = pstTimerIdx->ulLength - ulTempVar - 1;
                    pstTimerIdx->ulStartTime = 0;
                    BST_DBG_LOG3("BST_OS_TimerChkNearest: timer %d re-freshed because of time flip. New Length:%d, new StartTime:%d ",
                                 pstTimerIdx->ulId, pstTimerIdx->ulLength, pstTimerIdx->ulStartTime);
                }
            }

            ulPastMs        = ulNowMs - pstTimerIdx->ulStartTime;
            bIsExpired      = BST_OS_TimerChkExpire( ulPastMs, pstTimerIdx->ulLength );

            if ( BST_TRUE == bIsExpired )
            {
                pstTimerIdx->ulStoped   = BST_TRUE;
                BST_SRV_ApiSendExpiredEvent( pstTimerIdx->pstRcver, pstTimerIdx->ulId );
                goto BST_OS_TIMER_FIND_NEAREST;
            }
            else
            {
                ulRemainMs  = pstTimerIdx->ulLength - ulPastMs;

                if ( 0 == ulMinMs )
                {
                    ulMinMs = ulRemainMs;
                }

                if ( ulRemainMs < ulMinMs )
                {
                    ulMinMs = ulRemainMs;
                }
            }
        }
    }
    BST_OS_SpinUnLock(&g_BstTimerSpinLock, ulThreadLockCnt);
    return ulMinMs;
}


BST_VOID BST_OS_TimerSysInit( BST_VOID )
{
    BST_OS_LOCKCNT_T        tThreadLockCnt;
    tThreadLockCnt          = BST_OS_ThreadLock();
    g_pstOsTimerList        = ( LIST *)BST_OS_MALLOC
                              ( BST_OS_SIZEOF( LIST ) );
    lstInit( g_pstOsTimerList );
    g_cBstOsTimerIdGenrator = new BST_Lib_CSnGenrator<BST_OS_TIMERID_T>
                            ( BST_OS_TIMER_START_ID,
                              BST_MAX_TIMER_NUMBER );
    BST_OS_InitSpinLock( &g_BstTimerSpinLock );
    BST_OS_PalTimerInit();
    BST_OS_ThreadUnLock( tThreadLockCnt );
}


/*lint -e429*/
BST_OS_TIMERID_T BST_OS_TimerCreateCpp(
    BST_OS_CTimerCb    *pcCallBack,
    BST_VOID           *pvPara,
    BST_OS_MBX_T       *pstMsgHandle )
{
    BST_OS_TIMER_STRU          *pstTimer;
    BST_UINT32                  utThreadLockCnt;

    pstTimer                    = ( BST_OS_TIMER_STRU *)BST_OS_MALLOC
                                  ( BST_OS_SIZEOF( BST_OS_TIMER_STRU ) );
    if( BST_NULL_PTR == pstTimer )
    {
        return BST_OS_INVALID_TIMER_ID;
    }
    utThreadLockCnt             = BST_OS_SpinLock( &g_BstTimerSpinLock );
    if( BST_NULL_PTR != g_cBstOsTimerIdGenrator )
    {
        pstTimer->ulId          = g_cBstOsTimerIdGenrator->NewId();
    }
    pstTimer->ulStoped          = BST_TRUE;
    pstTimer->ulLength          = 0;
    pstTimer->unCallBack.pc     = pcCallBack;
    pstTimer->ulStartTime       = 0;
    pstTimer->pvPara            = pvPara;
    pstTimer->pstRcver          = pstMsgHandle;
    pstTimer->enCbMode          = BST_OS_TIMER_CB_CLASS;
    BST_DBG_LOG1( "BST_OS_TimerCreateCpp Id = %d\n", pstTimer->ulId );
    if( BST_NULL_PTR != g_pstOsTimerList )
    {
        lstAdd( g_pstOsTimerList, ( NODE *)pstTimer );
    }
    BST_OS_SpinUnLock(&g_BstTimerSpinLock, utThreadLockCnt);
    return pstTimer->ulId;
}
/*lint +e429*/

/*lint -e429*/
BST_OS_TIMERID_T BST_OS_TimerCreate(
    BST_OS_TIMER_CB_T   pfCallBack,
    BST_VOID           *pvPara,
    BST_OS_MBX_T       *pstMsgHandle )
{
    BST_OS_TIMER_STRU                  *pstTimer;
    BST_UINT32                          utThreadLockCnt;

    pstTimer                    = ( BST_OS_TIMER_STRU *)BST_OS_MALLOC
                                  ( BST_OS_SIZEOF( BST_OS_TIMER_STRU ) );
    if( BST_NULL_PTR == pstTimer )
    {
        return BST_OS_INVALID_TIMER_ID;
    }
    if( BST_NULL_PTR == pstMsgHandle )
    {
        return BST_OS_INVALID_TIMER_ID;
    }
    utThreadLockCnt             = BST_OS_SpinLock( &g_BstTimerSpinLock );
    if( BST_NULL_PTR != g_cBstOsTimerIdGenrator )
    {
        pstTimer->ulId          = g_cBstOsTimerIdGenrator->NewId();
    }                           
    pstTimer->ulStoped          = BST_TRUE;
    pstTimer->ulLength          = 0;
    pstTimer->unCallBack.pf     = pfCallBack;
    pstTimer->ulStartTime       = 0;
    pstTimer->pvPara            = pvPara;
    pstTimer->pstRcver          = pstMsgHandle;
    pstTimer->enCbMode          = BST_OS_TIMER_CB_FUN;
    BST_DBG_LOG1( "BST_OS_TimerCreate Id = %d\n", pstTimer->ulId );
    if( BST_NULL_PTR != g_pstOsTimerList )
    {
        lstAdd( g_pstOsTimerList, ( NODE *)pstTimer );
    }
    BST_OS_SpinUnLock(&g_BstTimerSpinLock, utThreadLockCnt);
    return pstTimer->ulId;
}
/*lint +e429*/

BST_VOID BST_OS_TimerStart( BST_OS_TIMERID_T ulId, BST_UINT32 ulLength )
{
    BST_UINT32                          ulNearestTime;

    if ( ( ulLength > 0 ) && ( ulId != BST_OS_INVALID_TIMER_ID ) )
    {
        BST_OS_TIMER_STRU *timer_ptr = BST_OS_TimerSrch( ulId );
        BST_DBG_LOG2( "BST_OS_TimerStart =%u,length=%u", ulId, ulLength );
        if ( timer_ptr != BST_NULL_PTR )
        {
            if( ulLength <= BST_OS_TIMER_PRECISION )
            {
                ulLength               += BST_OS_TIMER_PRECISION;
            }
            timer_ptr->ulLength         = ulLength ;
            timer_ptr->ulStoped         = BST_FALSE;
            timer_ptr->ulStartTime      = BST_OS_TimerNowMs();
            ulNearestTime               = BST_OS_TimerChkNearest();
            if( 0 != ulNearestTime )
            {
                BST_OS_PalTimerStart( ulNearestTime );
            }
        }
    }
}


BST_VOID BST_OS_TimerStop( BST_OS_TIMERID_T ulId )
{
    BST_OS_TIMER_STRU *timer_ptr        = BST_OS_TimerSrch( ulId );
    BST_UINT32                          ulNearestTime;
    BST_DBG_LOG1("Stop Timer %u", ulId );

    if( BST_NULL_PTR == timer_ptr )
    {
        return;
    }

    if ( BST_TRUE == timer_ptr->ulStoped )
    {
        return;
    }

    timer_ptr->ulStoped                 = BST_TRUE;
    timer_ptr->ulLength                 = 0;
    ulNearestTime                       = BST_OS_TimerChkNearest();
    if( 0 != ulNearestTime )
    {
        BST_OS_PalTimerStart( ulNearestTime );
    }
    else
    {
        BST_OS_PalTimerStop();
    }
}


BST_BOOL BST_OS_TimerIsStop( BST_OS_TIMERID_T ulId )
{
    BST_OS_TIMER_STRU *timer_ptr = BST_OS_TimerSrch( ulId );

    if ( timer_ptr != BST_NULL_PTR )
    {
        return (BST_BOOL)( timer_ptr->ulStoped );
    }

    return BST_TRUE;
}


BST_VOID BST_OS_TimerRemove( BST_OS_TIMERID_T ulId )
{
    BST_OS_TIMER_STRU  *pstTimerIdx;
    BST_UINT32          ulNearestTime;
    BST_UINT32          utThreadLockCnt;

    BST_ASSERT_NULL( g_pstOsTimerList );
    if ( BST_OS_INVALID_TIMER_ID == ulId )
    {
        return;
    }
    BST_RLS_LOG1("BST_OS_TimerRemove id = %u", ulId);

    utThreadLockCnt     = BST_OS_SpinLock( &g_BstTimerSpinLock );
    for ( pstTimerIdx = ( BST_OS_TIMER_STRU *)
                        lstFirst( g_pstOsTimerList );
          pstTimerIdx!= BST_NULL_PTR;
          pstTimerIdx = ( BST_OS_TIMER_STRU *)
                        lstNext( ( NODE *)pstTimerIdx ) )
    {
        if ( pstTimerIdx->ulId != ulId )
        {
            continue;
        }
        g_cBstOsTimerIdGenrator->RmvId( ulId );
        lstDelete( g_pstOsTimerList, ( NODE *)pstTimerIdx );
        BST_OS_FREE( pstTimerIdx );
        ulNearestTime   = BST_OS_TimerChkNearest();
        if( 0 != ulNearestTime )
        {
            BST_OS_PalTimerStart( ulNearestTime );
        }
        else
        {
            BST_OS_PalTimerStop();
        }
        break;
    }
    BST_OS_SpinUnLock( &g_BstTimerSpinLock, utThreadLockCnt );
}


BST_OS_TIMER_STRU *BST_OS_TimerSrch( BST_OS_TIMERID_T ulId )
{
    BST_OS_TIMER_STRU  *pstTimerIdx;
    BST_UINT32          utThreadLockCnt;

    BST_ASSERT_NULL_RTN( g_pstOsTimerList, BST_NULL_PTR );
    if ( BST_OS_INVALID_TIMER_ID == ulId )
    {
        return BST_NULL_PTR;
    }

    utThreadLockCnt     = BST_OS_SpinLock( &g_BstTimerSpinLock );
    for ( pstTimerIdx = ( BST_OS_TIMER_STRU *)
                        lstFirst( g_pstOsTimerList );
          pstTimerIdx!= BST_NULL_PTR;
          pstTimerIdx = ( BST_OS_TIMER_STRU *)
                        lstNext( ( NODE *)pstTimerIdx ) )
    {
        if ( pstTimerIdx->ulId == ulId )
        {            
            BST_OS_SpinUnLock( &g_BstTimerSpinLock, utThreadLockCnt );
            return pstTimerIdx;
        }
    }

    BST_OS_SpinUnLock( &g_BstTimerSpinLock, utThreadLockCnt );
    return BST_NULL_PTR;
}
