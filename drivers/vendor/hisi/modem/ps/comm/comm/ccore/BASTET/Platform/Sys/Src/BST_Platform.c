/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_Platform.c
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年06月28日
  最近修改   :
  功能描述   : 处理平台初始化相关函数
  函数列表   :
  修改历史   :
  1.日    期   : 2014年06月28日
    作    者   : d00173029
    修改内容   : 建立文件

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_OS_Thread.h"
#include "BST_OS_Memory.h"
#include "BST_OS_Timer.h"
#include "BST_OS_Log.h"
#include "BST_DRV_Acom.h"
#include "BST_DRV_As.h"
#include "BST_DRV_Net.h"
#include "BST_PAL_Acom.h"
#include "BST_SYS_MsgProc.h"
#include "BST_PAL_As.h"
#include "NVIM_Interface.h"
#include "BST_DRV_LinkSta.h"
#include "TafNvInterface.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_PLATFORM_C
/*lint +e767*/
/*****************************************************************************
  2 函数声明
*****************************************************************************/
extern BST_VOID BST_SRV_InitInstance( BST_VOID );
extern BST_VOID BST_SRV_InitMultiThread( BST_VOID );
extern BST_VOID BST_PAL_NetApiInitial   ( BST_VOID );
extern BST_VOID BST_OS_PalTimerCallBack ( BST_VOID );
extern BST_VOID BST_IP_ApiInitPortPreproc( BST_VOID );
BST_VOID        BST_SYS_InitDriver      ( BST_VOID );
BST_UINT32      BST_SYS_InitThread      ( BST_VOID );
/******************************************************************************
  3 全局变量定义
******************************************************************************/
BST_UINT32                              g_ulBastetTaskId    = 0;
BST_UINT32                              g_BstThreadInitFlags= 0;
BST_UINT32                              g_ulBstTaskReadyFlag= BST_FALSE;
extern BST_OS_SPINLOCK_T                g_MboxLock;
BST_BOOL                                g_BstBastetFlg = BST_FALSE;
/******************************************************************************
  4 函数实现
******************************************************************************/

/*****************************************************************************
 函 数 名  : BST_SYS_InitPlatform
 功能描述  : BST平台初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SYS_InitPlatform( BST_VOID )
{
    if(BST_FALSE == BST_SYS_ApiGetSupported())
    {
        BST_DBG_LOG("BST_SYS_InitPlatform: bastet nv disabled");
        return;
    }

    BST_OS_InitLock();
    BST_OS_InitSpinLock( &g_MboxLock );
    BST_OS_MemInit();
    BST_OS_TimerSysInit();
    if( BST_TRUE == BST_SYS_InitThread() )
    {
        BST_DBG_INITIAL();
        BST_SYS_InitDriver();
    }
}

/*****************************************************************************
 函 数 名  : BST_SYS_InitDriver
 功能描述  : BST驱动初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SYS_InitDriver( BST_VOID )
{
    BST_DRV_STRU   *pDrvHandle;

    pDrvHandle      = BST_DRV_AcomGetDvcHandle();
    pDrvHandle->pfInit( pDrvHandle );

    pDrvHandle      = BST_DRV_AsGetDvcHandle();
    pDrvHandle->pfInit( pDrvHandle );

    pDrvHandle      = BST_DRV_LsGetDvcHandle();
    pDrvHandle->pfInit( pDrvHandle );
}

/*****************************************************************************
 函 数 名  : BST_SYS_InitThread
 功能描述  : 线程初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT32 BST_SYS_InitThread( BST_VOID )
{
    BST_SRV_InitMultiThread();
    /*
     * 切换线程，让线程完全创建，
     * 之后BST_SRV_CAsCtrl会在构造函数的
     * 初始化列表中获取线程的句柄时才不会失败
     */
    BST_OS_SleepMs( 500 );
    BST_IP_ApiInitPortPreproc();
    BST_PAL_NetApiInitial();
    BST_SRV_InitInstance();
    return BST_TRUE;
}

/*****************************************************************************
 函 数 名  : BST_SYS_InitBastetNvFlag
 功能描述  : 根据NV:BST_PAL_ReadModemBastetCfgNvim初始化是否支持Bastet
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : z00128442
    修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SYS_InitBastetNvFlag(BST_VOID)
{
    BASTET_SUPPORT_FLG_STRU                     stBastetFlag;
    TAF_NV_LC_CTRL_PARA_STRU                    stLcCtrlPara;

    PS_MEM_SET(&stBastetFlag, 0x00, sizeof(BASTET_SUPPORT_FLG_STRU));
    PS_MEM_SET(&stLcCtrlPara, 0x00, sizeof(stLcCtrlPara));

    /* 读NV项en_NV_MODEM_RF_SHARE_CFG，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_Bastet_CONFIG,
                         &stBastetFlag, sizeof(BASTET_SUPPORT_FLG_STRU)))
    {
        BST_RLS_LOG("BST_SYS_InitBastetNvFlag():WARNING: read en_NV_Item_Bastet_CONFIG Error");

        return;
    }

    if (BST_TRUE != stBastetFlag.ucActiveFlg)
    {
        /* NV内容异常保护 */
        g_BstBastetFlg  = BST_FALSE;
    }
    else
    {
        g_BstBastetFlg  = BST_TRUE;
        BST_PAL_SetLogSwitch(stBastetFlag.ucHookFlg);
    }

    /* 读NV项是否CL模式nv项，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_LC_Ctrl_PARA,
                         &stLcCtrlPara,
                         sizeof(stLcCtrlPara)))
    {
        BST_RLS_LOG("BST_SYS_InitBastetNvFlag():WARNING: read en_NV_Item_LC_Ctrl_PARA Error");
        return;
    }

    /*如果当前工作在CL模式，bastet模块暂不支持*/
    if ((BST_TRUE == stLcCtrlPara.ucLCEnableFlg )
        && (TAF_NVIM_LC_RAT_COMBINED_CL == stLcCtrlPara.enRatCombined))
    {
        g_BstBastetFlg  = BST_FALSE;
    }

    return;
}

/*****************************************************************************
 函 数 名  : BST_SYS_ApiGetSupported
 功能描述  : 返回否支持Bastet
 输入参数  : 无
 输出参数  : 无
 返 回 值  : BST_TRUE 支持， BST_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : z00128442
    修改内容   : 新生成函数
*****************************************************************************/
BST_BOOL BST_SYS_ApiGetSupported(BST_VOID)
{
    return g_BstBastetFlg;
}



/*****************************************************************************
 函 数 名  :
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID BST_SYS_MsgProcEntry( MsgBlock  *pstMsg )
{
    if(BST_FALSE == BST_SYS_ApiGetSupported())
    {
        BST_DBG_LOG("BST_SYS_MsgProcEntry: bastet nv disabled");
        return;
    }

    switch(pstMsg->ulSenderPid)
    {
        case VOS_PID_TIMER:
            BST_DBG_LOG("BST_SYS_MsgProcEntry: VOS_PID_TIMER");
            BST_OS_PalTimerCallBack();
            break;

        case ACPU_PID_BASTET_COMM:
            BST_DBG_LOG("BST_SYS_MsgProcEntry: ACPU_PID_BASTET_COMM");
            BST_Pal_DrvAcomRecv( ( BST_UINT32 ) BST_OS_SIZEOF( BST_ACOM_MSG_STRU ),
                                 ( BST_UINT8 *) pstMsg );
            break;

        case UEPS_PID_CDS:
            BST_DBG_LOG("BST_SYS_MsgProcEntry: UEPS_PID_CDS");
            DIAG_TraceReport(pstMsg);
            BST_PAL_NetMsgEntry( pstMsg );
            break;

        case I0_WUEPS_PID_MMA:
            DIAG_TraceReport(pstMsg);
            BST_MSG_ProcMmaRecv(pstMsg,BST_MODEM_ID_1);
            break;

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
        case I1_WUEPS_PID_MMA:
            DIAG_TraceReport(pstMsg);
            BST_MSG_ProcMmaRecv(pstMsg,BST_MODEM_ID_2);
            break;

#if ( 3 == MULTI_MODEM_NUMBER )
        case I2_WUEPS_PID_MMA:
            DIAG_TraceReport(pstMsg);
            BST_MSG_ProcMmaRecv(pstMsg,BST_MODEM_ID_3);
            break;
#endif
#endif

        case WUEPS_PID_WRR:
            DIAG_TraceReport(pstMsg);
            BST_MSG_ProcWrrcRecv(pstMsg);
            break;
        case TPS_PID_RRC:
            DIAG_TraceReport(pstMsg);
            BST_MSG_ProcTrrcRecv(pstMsg);
            break;
        case PS_PID_ERRC:
            DIAG_TraceReport(pstMsg);
            BST_MSG_ProcLrrcRecv(pstMsg);
            break;
        case WUEPS_PID_RLC:
            DIAG_TraceReport(pstMsg);
            BST_MSG_ProcWRlcRecv(pstMsg);
            break;
        case I0_UEPS_PID_SN:
            DIAG_TraceReport(pstMsg);
            BST_MSG_ProcGRlcRecv(pstMsg);
            break;

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
        case I1_UEPS_PID_SN:
            DIAG_TraceReport(pstMsg);
            BST_MSG_ProcGRlcRecv(pstMsg);
            break;

#if ( 3 == MULTI_MODEM_NUMBER )
        case I2_UEPS_PID_SN:
            DIAG_TraceReport(pstMsg);
            BST_MSG_ProcGRlcRecv(pstMsg);
            break;
#endif
#endif

        default:
            break;
    }
}

/*****************************************************************************
 函 数 名  : BST_SYS_EvtProcEntry
 功能描述  : BST事件处理
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年5月12日
      作    者   : d00173029
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID BST_SYS_EvtProcEntry(VOS_UINT32 ulEvent)
{
    /*处理下行CDS IP包收到唤醒*/
    if (ulEvent & BST_CDS_EVENT_RCV_DL_PROC)
    {
        BST_PAL_NetDLEvtProc();
    }
    return;
}

/*****************************************************************************
 函 数 名  : BST_SYS_ApiSndEvtToBastet
 功能描述  : 调用该接口向BASTET触发事件处理
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年5月12日
      作    者   : d00173029
      修改内容   : 新生成函数

*****************************************************************************/
BST_VOID BST_SYS_ApiSndEvtToBastet(BST_UINT32 ulEvent)
{
    if ( BST_TRUE == g_ulBstTaskReadyFlag )
    {
        (VOS_VOID)VOS_EventWrite(g_ulBastetTaskId, ulEvent);
    }
    return;
}

/*****************************************************************************
 函 数 名  :
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID BST_FidTask ( VOS_UINT32 Para1, VOS_UINT32 Para2,
                       VOS_UINT32 Para3, VOS_UINT32 Para4 )
{
    MsgBlock       *pMsg                = VOS_NULL_PTR;
    VOS_UINT32      ulEvent             = 0;
    VOS_UINT32      ulTaskID            = 0;
    VOS_UINT32      ulEventMask         = 0;
    VOS_UINT32      ulExpectEvent       = 0;

    ulTaskID                = VOS_GetCurrentTaskID();

    if ( PS_NULL_UINT32 == ulTaskID )
    {
        BST_RLS_LOG ( "BST_FidTask: This Task Id is Error" );
        return;
    }

    if ( VOS_OK != VOS_CreateEvent(ulTaskID) )
    {
        BST_RLS_LOG ( "BST_FidTask:, Create Event Fail");
        return;
    }

    ulExpectEvent           = VOS_MSG_SYNC_EVENT|BST_CDS_EVENT_RCV_DL_PROC;
    ulEventMask             = (VOS_EVENT_ANY | VOS_EVENT_WAIT);
    g_ulBastetTaskId        = VOS_GetCurrentTaskID();
    g_ulBstTaskReadyFlag    = BST_TRUE;

    for (;;)
    {
        if ( VOS_OK != VOS_EventRead(ulExpectEvent,ulEventMask,0,&ulEvent) )
        {
            BST_RLS_LOG ( "BST_FidTask: BASTET Read Event Error" );
            continue;
        }
        /*事件处理*/
        if (VOS_MSG_SYNC_EVENT != ulEvent)
        {
            BST_SYS_EvtProcEntry(ulEvent);
            continue;
        }

        pMsg                = (MsgBlock *)VOS_GetMsg(ulTaskID);
        if ( VOS_NULL_PTR != pMsg )
        {
            switch ( TTF_GET_MSG_RECV_PID( pMsg ) )
            {
                case UEPS_PID_BASTET:
                    BST_SYS_MsgProcEntry( pMsg );
                    break;

                default:
                    BST_RLS_LOG1 ( "BST_FidTask: Recv Unkown Message %d\r\n", TTF_GET_MSG_NAME(pMsg) );
                    break;
            }
            PS_FREE_MSG ( UEPS_PID_BASTET, pMsg );
        }

    }
}

/*****************************************************************************
 函 数 名  :BST_PidInit
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月15日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 BST_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{

    switch (enPhase)
    {
        case   VOS_IP_LOAD_CONFIG:
            BST_SYS_InitBastetNvFlag();
            BST_SYS_InitPlatform();
            break;
        case   VOS_IP_FARMALLOC:
        case   VOS_IP_INITIAL:
        case   VOS_IP_ENROLLMENT:
        case   VOS_IP_LOAD_DATA:
        case   VOS_IP_FETCH_DATA:
        case   VOS_IP_STARTUP:
        case   VOS_IP_RIVAL:
        case   VOS_IP_KICKOFF:
        case   VOS_IP_STANDBY:
        case   VOS_IP_BROADCAST_STATE:
        case   VOS_IP_RESTART:
        case   VOS_IP_BUTT:
            break;
        default:
            break;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  :
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 BST_FidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    VOS_UINT32   ulResult = PS_FAIL;

    switch (enPhase)
    {
        case   VOS_IP_LOAD_CONFIG:
            ulResult = VOS_RegisterPIDInfo(UEPS_PID_BASTET,
                                BST_PidInit,
                                BST_SYS_MsgProcEntry);
            if (PS_SUCC != ulResult)
            {
                return (VOS_UINT32)PS_FAIL;
            }

            ulResult = VOS_RegisterMsgTaskEntry(UEPS_FID_BASTET, (VOS_VOIDFUNCPTR)BST_FidTask);
            if (PS_SUCC != ulResult)
            {
                vos_printf("UEPS_FID_BASTET Reg msg routine FAIL!,ulRslt\n", ulResult);
                return (VOS_UINT32)PS_FAIL;
            }


            ulResult = VOS_RegisterMsgTaskPrio(UEPS_FID_BASTET, VOS_PRIORITY_P3);

            if( PS_SUCC != ulResult )
            {
                vos_printf("Error: UEPS_FID_BASTET VOS_RegisterMsgTaskPrio failed!");
                return (VOS_UINT32)PS_FAIL;
            }
            break;
        case   VOS_IP_FARMALLOC:
        case   VOS_IP_INITIAL:
        case   VOS_IP_ENROLLMENT:
        case   VOS_IP_LOAD_DATA:
        case   VOS_IP_FETCH_DATA:
        case   VOS_IP_STARTUP:
        case   VOS_IP_RIVAL:
        case   VOS_IP_KICKOFF:
        case   VOS_IP_STANDBY:
        case   VOS_IP_BROADCAST_STATE:
        case   VOS_IP_RESTART:
        case   VOS_IP_BUTT:
            break;
        default:
            break;
    }

    return VOS_OK;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


