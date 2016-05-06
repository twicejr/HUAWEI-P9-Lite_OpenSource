/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_SRV_HbDetector.cpp
  版 本 号   : V1.1
  作    者   : d00173029
  生成日期   : 2015年05月25日
  最近修改   :
  功能描述   : 实现探测器周期处理
  函数列表   :

  修改历史   :
  1.日    期   : 2015年05月25日
    作    者   : d00173029
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_SRV_HbDetector.h"
#include "BST_SRV_TaskMng.h"
#include "BST_SRV_Event.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_SRV_HB_DETECTOR_CPP
/*lint +e767*/
/*****************************************************************************
  2 函数声明
*****************************************************************************/

/******************************************************************************
   4 私有定义
******************************************************************************/

/******************************************************************************
   5 全局变量定义
******************************************************************************/

/******************************************************************************
   6 函数实现
******************************************************************************/

/*****************************************************************************
 函 数 名  : 
 功能描述  : 
 输入参数  : 
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_SRV_CHbDetector* BST_SRV_CHbDetector::GetInstance( BST_VOID )
{
    static  BST_SRV_CHbDetector    *pHbDector = BST_NULL_PTR;

    if ( BST_NULL_PTR == pHbDector )
    {
        pHbDector                       = new BST_SRV_CHbDetector();
    }
    return pHbDector;
}
/*****************************************************************************
 函 数 名  : 
 功能描述  : 
 输入参数  : 
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数, 从m_ucDetectingCycle=1点探测，逐步提升点数，
                   探测失败首先调整m_ulDetectingOfset，
                   如果仍然失败则降低点数m_ucDetectingCycle。
                   
    3---------------->15min   |-|<-Step3-| 15分钟探测失败，链路断开,调整m_ulDetectingOfset
     ofset:1--------->14min <-| |<-Step4-| 还回14分钟探测成功，探测完成
     ofset:2--------->13min     |
              |                 |
              ^                 ^
              |                 |
    2---------------->10min     |<-Step2-| 10分钟探测成功，升级至15分钟点探测
     ofset:1--------->9min      |
     ofset:2--------->8min      |
              |                 ^
              ^                 |
              |                 |
    1---------------->5min      |<-Step1-| 分钟探测成功，升级至10分钟点探测
     ofset:1--------->4min
     ofset:2--------->3min

*****************************************************************************/
BST_SRV_CHbDetector::BST_SRV_CHbDetector( BST_VOID )
{
    BST_UINT32                          ulCnt;

    m_ulDetectingOfset                  = 0;
    m_ulCfmSysTick_Ms                   = BST_SRV_DTC_BAS_UNT;
    m_ucDetectingCycle                  = BST_SRV_DTC_INI_PNT;
    m_enDtcState                        = BST_SRV_DET_STATE_INIT;
    pcTaskItem                          = BST_NULL_PTR;
    m_bIsBlocked                        = BST_FALSE;
    m_ulDetectingTmr                    = BST_OS_TimerCreateCpp(
                                          this, BST_NULL_PTR,
                                          BST_SRV_GetSysMsgHandle() );
    for( ulCnt = 0; ulCnt <= BST_SRV_DTC_MAX_LEN; ulCnt++ )
    {
        m_ucCfmTable[ulCnt]             = BST_SRV_DTC_MIN_PNT;
    }
    return;
}
/*****************************************************************************
 函 数 名  : 
 功能描述  : 
 输入参数  : 
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_CHbDetector::Initial( BST_VOID )
{
    BST_UINT32                          ulCnt;

    m_ulDetectingOfset                  = 0;
    m_ulCfmSysTick_Ms                   = BST_SRV_DTC_BAS_UNT;
    m_ucDetectingCycle                  = BST_SRV_DTC_INI_PNT;

    for( ulCnt = 0; ulCnt <= BST_SRV_DTC_MAX_LEN; ulCnt++ )
    {
        m_ucCfmTable[ulCnt]             = BST_SRV_DTC_MIN_PNT;
    }
    /**
     初始化完成，进入前进模式，如果没有探测器，那么直接进入终结
     */
    if( BST_NULL_PTR == pcTaskItem )
    {
        m_enDtcState                    = BST_SRV_DET_STATE_FINISH;
    }
    else
    {
        m_enDtcState                    = BST_SRV_DET_STATE_FORWARD;
    }
    if( BST_OS_IsTimerValid( m_ulDetectingTmr ) )
    {
        BST_OS_TimerStop( m_ulDetectingTmr );
    }

    BST_DBG_LOG1("BST_SRV_CHbDetector,m_enDtcState:%d",m_enDtcState);
}
/*****************************************************************************
 函 数 名  : 
 功能描述  : 
 输入参数  : 
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_SRV_CHbDetector::DefTask( BST_CORE_PTASK_NODE_STRU *pDetTask )
{
    BST_ASSERT_NULL_RTN( pDetTask, BST_ERR_INVALID_PTR );
    BST_ASSERT_NULL_RTN( pDetTask->pcTask, BST_ERR_INVALID_PTR );

    if( ( BST_NULL_PTR != pcTaskItem )
      &&( pDetTask != pcTaskItem ) )
    {
        Initial();
    }
    pcTaskItem = pDetTask;
    return BST_NO_ERROR_MSG;
}
/*****************************************************************************
 函 数 名  : 
 功能描述  : 
 输入参数  : 
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_SRV_CHbDetector::ClrTask( BST_VOID )
{
    BST_DBG_LOG1("HB clr task m_enDtcState:%d",m_enDtcState);
    pcTaskItem  = BST_NULL_PTR;
    if( BST_SRV_DET_STATE_FINISH == m_enDtcState )
    {
        return BST_NO_ERROR_MSG;
    }
    if( BST_OS_IsTimerValid( m_ulDetectingTmr ) )
    {
        BST_OS_TimerStop( m_ulDetectingTmr );
    }
    return BST_NO_ERROR_MSG;
}
/*****************************************************************************
 函 数 名  : 
 功能描述  : 
 输入参数  : 
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_CHbDetector::AckSendResult( BST_UINT16 ucResult )
{
    BST_ASSERT_NULL( pcTaskItem );

    if( BST_CORE_SCHD_ACK_SUC == ucResult )
    {
        ProcHbSuc();
    }
    else
    {
        ProcHbErr();
    }
}

/*****************************************************************************
 函 数 名  : 
 功能描述  : 
 输入参数  : 
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_CHbDetector::ReStart( BST_VOID )
{
    if( BST_NULL_PTR == pcTaskItem )
    {
        Initial();
        return;
    }
    if( BST_NULL_PTR == pcTaskItem->pcTask )
    {
        Initial();
        return;
    }

    /*
     * 如果探测已经结束，且目前不是最大系统周期，因为探测要重新开始，要将服务器周期调制最大
     */
    if( ( BST_FALSE == IsRuning() )
      &&( m_ucDetectingCycle < BST_SRV_DTC_MAX_LEN ) )
    {
        BST_SRV_ApiSendPTaskEvent( pcTaskItem->pcTask,
                                   BST_SRV_S2T_CYC_UPDATE,
                                   BST_SRV_DTC_MAX_LEN );
    }
    Initial();
    /**
     初始化完成，进入前进模式，如果没有探测器，那么直接进入终结
     */

    /*
     * 如果上次执行的事件尚未完成，本次不运行
     */
    pcTaskItem->enSendState         = BST_APP_SEND_STATE_FIRST;
    if ( BST_TRUE == pcTaskItem->pcTask->IsBusy () )
    {
        BST_RLS_LOG( "BST_SRV_CHbDetector::ReStart pC_PTask Is Busy" );
        return;
    }
    if( BST_TASK_STATE_START != pcTaskItem->pcTask->GetState () )
    {
        BST_RLS_LOG( "BST_SRV_CHbDetector::ReStart pC_PTask Is not start state" );
        return;
    }
    BST_SRV_ApiSendPTaskEvent( pcTaskItem->pcTask, BST_SRV_S2T_EXE_COMAND, 0 );
    pcTaskItem->ulLastSendTime      = BST_OS_TimerNowMs();
    RunTimer();
}

/*****************************************************************************
 函 数 名  : 
 功能描述  : 
 输入参数  : 
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_CHbDetector::Resume( BST_VOID )
{
    if( BST_NULL_PTR == pcTaskItem )
    {
        return;
    }

    if( BST_NULL_PTR == pcTaskItem->pcTask )
    {
        return;
    }

    pcTaskItem->enSendState             = BST_APP_SEND_STATE_NORM;

    BST_RLS_LOG2( "BST_SRV_CHbDetector::Resume,m_enDtcState:%d,m_ucDetectingCycle:%d",m_enDtcState, m_ucDetectingCycle);

HB_DTCT_RSUM_STATE:
    switch( m_enDtcState )
    {
        case BST_SRV_DET_STATE_INIT:
            Initial();
        case BST_SRV_DET_STATE_FORWARD:
        case BST_SRV_DET_STATE_REVERSE:
            pcTaskItem->ulLastSendTime      = BST_OS_TimerNowMs();
            if( pcTaskItem->ulLastSendTime > BST_SRV_DTC_SYS_DLY )
            {
                pcTaskItem->ulLastSendTime -= BST_SRV_DTC_SYS_DLY;
            }
            else
            {
                pcTaskItem->ulLastSendTime  = 0;
            }
            RunTimer();
        break;

        case BST_SRV_DET_STATE_FINISH:
            if( m_ucDetectingCycle < BST_SRV_DTC_MAX_LEN )
            {
                if( BST_FALSE == BST_OS_TimerIsStop( m_ulDetectingTmr ))
                {
                    BST_RLS_LOG( "BST_SRV_CHbDetector::timer is still running" );
                    return;
                }
                m_enDtcState                = BST_SRV_DET_STATE_FORWARD;
                goto HB_DTCT_RSUM_STATE;
            }
        break; 

        default:
        break;
    }
}
/*****************************************************************************
 函 数 名  : 
 功能描述  : 
 输入参数  : 
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_CHbDetector::Pause( BST_VOID )
{
    BST_DBG_LOG1("HB Pause task m_enDtcState:%d",m_enDtcState);

    if( BST_SRV_DET_STATE_FINISH == m_enDtcState )
    {
        return;
    }
    if( BST_OS_IsTimerValid( m_ulDetectingTmr ) )
    {
        BST_OS_TimerStop( m_ulDetectingTmr );
    }
}
/*****************************************************************************
 函 数 名  : 
 功能描述  : 
 输入参数  : 
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT32 BST_SRV_CHbDetector::GetCurrentTick( BST_VOID )
{
    return( m_ulCfmSysTick_Ms - BST_SRV_DTC_GAD_OFS );
}
/*****************************************************************************
 函 数 名  : 
 功能描述  : 
 输入参数  : 
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_CHbDetector::onBlock( BST_VOID )
{
    m_bIsBlocked = BST_TRUE;
}
/*****************************************************************************
 函 数 名  : 
 功能描述  : 
 输入参数  : 
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_CHbDetector::onUnBlock( BST_VOID )
{
    BST_UINT32          ulTimeDiff;
    BST_UINT32          ulTimeNow;
    BST_UINT32          ulLongestTime;

    if( m_bIsBlocked != BST_TRUE )
    {
        return;
    }
    m_bIsBlocked    = BST_FALSE;

    BST_ASSERT_NULL( pcTaskItem );

    if( IsRuning() == BST_FALSE )
    {
        return;
    }

    if( pcTaskItem->enSendState != BST_APP_SEND_STATE_BLOCK )
    {
        return;
    }
    ulTimeNow           = BST_OS_TimerNowMs();

    /**
     *如果时间发生还回，上次时间已经无法确认，则认为超时
     */
    if( ulTimeNow < pcTaskItem->ulLastSendTime )
    {
        BST_SRV_ApiSendPTaskEvent( pcTaskItem->pcTask, BST_SRV_S2T_ERR_CLOSED, 0 );
        return;
    }
    else
    {
        ulTimeDiff      = ulTimeNow - pcTaskItem->ulLastSendTime;
    }

    /**
     *算出APK要求的最大周期
     */
    ulLongestTime       = pcTaskItem->pcTask->m_ulCycle * BST_SRV_DTC_BAS_UNT;
    /**
     *如果总体时间比APK规定短，那么可以试验一下发心跳
     */
    if( ulTimeDiff <= ulLongestTime )
    {
        BST_SRV_ApiSendPTaskEvent( pcTaskItem->pcTask, BST_SRV_S2T_EXE_COMAND, 0 );
        pcTaskItem->ulLastSendTime      = ulTimeNow;
    }
    else
    {
        BST_SRV_ApiSendPTaskEvent( pcTaskItem->pcTask, BST_SRV_S2T_ERR_CLOSED, 0 );
    }
}
/*****************************************************************************
 函 数 名  : 
 功能描述  : 
 输入参数  : 
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_BOOL BST_SRV_CHbDetector::IsRuning( BST_VOID )
{
    BST_ASSERT_NULL_RTN( pcTaskItem, BST_FALSE );

    switch( m_enDtcState )
    {
        case BST_SRV_DET_STATE_FORWARD:
        case BST_SRV_DET_STATE_REVERSE:
            return BST_TRUE;

        default:
            break;
    }
    return BST_FALSE;
}
/*****************************************************************************
 函 数 名  : 
 功能描述  : 
 输入参数  : 
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_BOOL BST_SRV_CHbDetector::IsTask( BST_CORE_CPTask *pcTask )
{
    BST_ASSERT_NULL_RTN( pcTaskItem, BST_FALSE );

    if( pcTask != pcTaskItem->pcTask )
    {
        return BST_FALSE;
    }
    return BST_TRUE;
}
/*****************************************************************************
 函 数 名  : 
 功能描述  : 
 输入参数  : 
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT16 BST_SRV_CHbDetector::GetConfCyc( BST_UINT16 usInAppCyc )
{
    if( usInAppCyc > BST_SRV_DTC_MAX_LEN )
    {
        return BST_SRV_DTC_MAX_LEN;
    }
    if( 0 == usInAppCyc )
    {
        return 0;
    }
    return m_ucCfmTable[usInAppCyc];
}
/*****************************************************************************
 函 数 名  : 
 功能描述  : 
 输入参数  : 
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_CHbDetector::Finish( BST_VOID )
{
    BST_CTaskSchdler           *pschd;

    UpdateConfCyc( m_ucDetectingCycle );
    m_enDtcState        = BST_SRV_DET_STATE_FINISH;

    /**
     如果最大周期已经探明，则无需重启，直至心跳失败后重启
    */
    if( m_ucDetectingCycle >= BST_SRV_DTC_MAX_LEN )
    {
        BST_OS_TimerStop( m_ulDetectingTmr );
    }
    /**
     如果探测结果为最小周期(5分钟量级)，那么3小时后就要刷新
    */
    else if( m_ucDetectingCycle == BST_SRV_DTC_MIN_PNT )
    {
        BST_OS_TimerStart( m_ulDetectingTmr, BST_SRV_DTC_THR_HUR );
    }
    /**
     其他介于最大和最小周期之间，则6小时后刷新
    */
    else
    {
        BST_OS_TimerStart( m_ulDetectingTmr, BST_SRV_DTC_SIX_HUR );
    }
    pschd                      = BST_CTaskSchdler::GetInstance();
    if( BST_NULL_PTR != pschd )
    {
        pschd->onDetFinished ( m_ucDetectingCycle );
    }
}
/*****************************************************************************
 函 数 名  : 
 功能描述  : 
 输入参数  : 
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_CHbDetector::ProcHbSuc( BST_VOID )
{
    BST_ASSERT_NULL( pcTaskItem );
    pcTaskItem->enLastErrType       = BST_CORE_SCHD_ACK_SUC;
    pcTaskItem->enSendState         = BST_APP_SEND_STATE_NORM;

    switch( m_enDtcState )
    {
        case BST_SRV_DET_STATE_INIT:
            Initial();
            RunTimer();
        break;

        case BST_SRV_DET_STATE_FORWARD:
            if( m_ucDetectingCycle >= BST_SRV_DTC_MAX_LEN )
            {
                Finish();
            }
            else
            {
                UpdateConfCyc( m_ucDetectingCycle );
                m_ulDetectingOfset  = 0;
                m_ucDetectingCycle++;
                RunTimer();
            }
        break;

        /**
         * 回退后心跳成功，意味着探测完成
         **/
        case BST_SRV_DET_STATE_REVERSE:
            Finish();
        break;

        case BST_SRV_DET_STATE_FINISH:
        break;

        default:
        break;
    }
}
/*****************************************************************************
 函 数 名  : 
 功能描述  : 
 输入参数  : 
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_CHbDetector::ProcHbErr( BST_VOID )
{
    BST_ASSERT_NULL( pcTaskItem );
    switch( m_enDtcState )
    {
        /**
         前进探测失败后，立即进入回退状态,前进/后退都用该配置方法
         */
        case BST_SRV_DET_STATE_FORWARD:
        case BST_SRV_DET_STATE_REVERSE:
            m_enDtcState                = BST_SRV_DET_STATE_REVERSE;
            if ( m_ulDetectingOfset <= BST_SRV_DTC_MAX_REW )
            {
                m_ulDetectingOfset     += BST_SRV_DTC_UNT_REW;
            }
            
            /**
             如果已经探测到最小偏移值，那么需要回退一个周期点
             */
            if( m_ulDetectingOfset > BST_SRV_DTC_MAX_REW )
            {
                /**
                 如果没有回探到最小周期(5分钟)，那么继续回探。
                 */
                if( m_ucDetectingCycle > BST_SRV_DTC_MIN_PNT )
                {
                    m_ucDetectingCycle--;
                    m_ulDetectingOfset  = 0;
                }
                /**
                 如果已经探测到底(3分钟)，那么无论结果如何，都需要停掉，3小时后重探
                 */
                else
                {
                    Finish();
                }
            }
        break;

        default:
        break;
    }
}
/*****************************************************************************
 函 数 名  : 
 功能描述  : 
 输入参数  : 
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_SRV_CHbDetector::UpdateConfCyc( BST_UINT8 ucPoint )
{
    BST_UINT32                          ulCnt;

    if( ucPoint > BST_SRV_DTC_MAX_LEN )
    {
        return BST_ERR_ITEM_NOT_EXISTED;
    }
    if( 0 == ucPoint )
    {
        return BST_ERR_ILLEGAL_PARAM;
    }

    /**
     * 该点之前的点，均可以认为是真实值，该点及其之后的点，则认为还未探明,以2为例
     *  0-->0
     *  1-->1
     *  2-->2
     *  3-->2(3倍周期15min点尚未探明，只能用10分钟)
     **/
    for( ulCnt = 0; ulCnt < ucPoint; ulCnt++ )
    {
        m_ucCfmTable[ulCnt]             = ulCnt;
    }
    for( ulCnt = ucPoint; ulCnt <= BST_SRV_DTC_MAX_LEN; ulCnt++ )
    {
        m_ucCfmTable[ulCnt]             = ucPoint;
    }
    /**
        |<-              5分钟的整数倍               ->|
        |------------------------|-Guard-|----Ofset----|
                                                ^探明的offset，说明不是5分钟整数倍
                                        ^保护时间，避免由于网络延迟造成心跳达到超时，一般取20S
                        ^最新探明的系统最大心跳时长，按照周期数等分，即为Tick长度
    */
    m_ulDetectingOfset = (m_ulDetectingOfset < BST_SRV_DTC_MAX_REW) ? m_ulDetectingOfset : BST_SRV_DTC_MAX_REW;
    m_ulCfmSysTick_Ms                   = ( ucPoint * BST_SRV_DTC_BAS_UNT
                                          - m_ulDetectingOfset
                                          - 2*BST_SRV_DTC_GAD_OFS )/ucPoint;
    BST_DBG_LOG3("UpdateConfCyc,ucPoint:%d,m_ulCfmSysTick_Ms:%d,m_ulDetectingOfset:%d",ucPoint,m_ulCfmSysTick_Ms,m_ulDetectingOfset);
    return BST_NO_ERROR_MSG;
}

/*****************************************************************************
 函 数 名  : 
 功能描述  : 
 输入参数  : 
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_CHbDetector::RunTimer( BST_VOID )
{
    BST_UINT32      ulTimerLen;
    BST_ASSERT_NULL( pcTaskItem );

    ulTimerLen                      = m_ucDetectingCycle*BST_SRV_DTC_BAS_UNT;

    if( ulTimerLen <= m_ulDetectingOfset )
    {
        return;
    }
    ulTimerLen                     -= m_ulDetectingOfset;

    if( ulTimerLen <= 2*BST_SRV_DTC_GAD_OFS )
    {
        return;
    }
    ulTimerLen                     -= 2*BST_SRV_DTC_GAD_OFS;
    BST_OS_TimerStart( m_ulDetectingTmr, ulTimerLen );
}

/*****************************************************************************
 函 数 名  : 
 功能描述  : 
 输入参数  : 
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_CHbDetector::TimerExpired( BST_OS_TIMERID_T ulId, BST_VOID *pvPara )
{
    BST_ASSERT_NULL( pcTaskItem );
    switch( m_enDtcState )
    {
        case BST_SRV_DET_STATE_FORWARD:
        case BST_SRV_DET_STATE_REVERSE:
            /**
             * 如果当时网络阻塞发送，那么只是记录阻塞标识
             **/
            if( BST_TRUE == m_bIsBlocked )
            {
                pcTaskItem->enSendState = BST_APP_SEND_STATE_BLOCK;
                BST_OS_TimerStop( m_ulDetectingTmr );
                return;
            }
        break;

        case BST_SRV_DET_STATE_FINISH:
            /**
             * 如果已经探测到最大周期，那么直接返回
             **/
            if( m_ucDetectingCycle >= BST_SRV_DTC_MAX_LEN )
            {
                return;
            }
            /**
             * 如果当时网络不稳，那么不适宜重启探测，需要延后1小时
             **/
            if( BST_TRUE == m_bIsBlocked )
            {
                BST_OS_TimerStart( m_ulDetectingTmr, BST_SRV_DTC_ONE_HUR );
                return;
            }
            /**
             * 向前继续探测
             **/
            m_ucDetectingCycle++;
            m_ulDetectingOfset      = 0;
            m_enDtcState            = BST_SRV_DET_STATE_FORWARD;
            pcTaskItem->enSendState = BST_APP_SEND_STATE_FIRST;
            BST_SRV_ApiSendPTaskEvent( pcTaskItem->pcTask,
                           BST_SRV_S2T_CYC_UPDATE,
                           BST_SRV_DTC_MAX_LEN );
            if ( BST_TRUE == pcTaskItem->pcTask->IsBusy () )
            {
                BST_RLS_LOG( "BST_SRV_CHbDetector::ReStart pC_PTask Is Busy" );
                return;
            }
            if( BST_TASK_STATE_START != pcTaskItem->pcTask->GetState () )
            {
                BST_RLS_LOG( "BST_SRV_CHbDetector::ReStart pC_PTask Is not start state" );
                return;
            }
            RunTimer();
        break;

        default:
        return;
    }
    BST_SRV_ApiSendPTaskEvent( pcTaskItem->pcTask, BST_SRV_S2T_EXE_COMAND, 0 );
    pcTaskItem->ulLastSendTime      = BST_OS_TimerNowMs();

}

/*****************************************************************************
 函 数 名  : 
 功能描述  : 
 输入参数  : 
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_SRV_CHbDetector::~BST_SRV_CHbDetector( BST_VOID )
{
    BST_OS_TimerRemove( m_ulDetectingTmr );
}

