
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "AdsInit.h"
#include "AdsUpLink.h"
#include "AdsDownLink.h"
#include "AdsDebug.h"
#include "AcpuReset.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_ADS_INIT_C
/*lint +e767*/


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/


VOS_UINT32 ADS_UL_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    switch ( enPhase )
    {
        case VOS_IP_LOAD_CONFIG:

            /* 上下文初始化 */
            ADS_InitCtx();

            /* 给低软注册回调函数，用于C核单独复位的处理 */
            mdrv_sysboot_register_reset_notify(NAS_ADS_UL_FUNC_PROC_NAME,
                                               ADS_UL_CCpuResetCallback,
                                               0,
                                               ACPU_RESET_PRIORITY_ADS_UL);

            break;

        default:
            break;
    }

    return VOS_OK;
}


VOS_VOID ADS_UL_FidTask(
    VOS_UINT32                          ulQueueID,
    VOS_UINT32                          FID_value,
    VOS_UINT32                          Para1,
    VOS_UINT32                          Para2
)
{
    MsgBlock                           *pMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulEvent       = 0;
    VOS_UINT32                          ulTaskID      = 0;
    VOS_UINT32                          ulRtn         = VOS_ERR;
    VOS_UINT32                          ulEventMask   = 0;
    VOS_UINT32                          ulExpectEvent = 0;

    ulTaskID = VOS_GetCurrentTaskID();
    if (PS_NULL_UINT32 == ulTaskID)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_FidTask: ERROR, TaskID is invalid.");
        return;
    }

    if (VOS_OK != VOS_CreateEvent(ulTaskID))
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_FidTask: ERROR, create event fail.");
        return;
    }

    g_ulAdsULTaskId         = ulTaskID;
    g_ulAdsULTaskReadyFlag  = 1;

    ulExpectEvent = ADS_UL_EVENT_DATA_PROC | VOS_MSG_SYNC_EVENT;
    ulEventMask   = (VOS_EVENT_ANY | VOS_EVENT_WAIT);

    /*lint -e716*/
    while (1)
    /*lint +e716*/
    {
        ulRtn = VOS_EventRead(ulExpectEvent, ulEventMask, 0, &ulEvent);
        if (VOS_OK != ulRtn)
        {
            ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_FidTask: ERROR, read event error.");
            continue;
        }

        /*事件处理*/
        if (VOS_MSG_SYNC_EVENT != ulEvent)
        {
            ADS_UL_ProcEvent(ulEvent);
            continue;
        }

        pMsg = (MsgBlock*)VOS_GetMsg(ulTaskID);
        if (VOS_NULL_PTR != pMsg)
        {
            if (ACPU_PID_ADS_UL == pMsg->ulReceiverPid)
            {
                ADS_UL_ProcMsg(pMsg);
            }

            PS_FREE_MSG(ACPU_PID_ADS_UL, pMsg);
        }
    }
}



VOS_UINT32 ADS_UL_FidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32                          ulRslt;

    switch (ip)
    {
        case VOS_IP_LOAD_CONFIG:

            /* 上行PID初始化 */
            ulRslt = VOS_RegisterPIDInfo(ACPU_PID_ADS_UL,
                                         (Init_Fun_Type)ADS_UL_PidInit,
                                         (Msg_Fun_Type)ADS_UL_ProcMsg);

            if (VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterMsgTaskEntry(ACPU_FID_ADS_UL, (VOS_VOIDFUNCPTR)ADS_UL_FidTask);

            if (VOS_OK != ulRslt)
            {
                return ulRslt;
            }

            /* 任务优先级 */
            ulRslt = VOS_RegisterTaskPrio(ACPU_FID_ADS_UL, ADS_UL_TASK_PRIORITY);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            break;

        case VOS_IP_FARMALLOC:
        case VOS_IP_INITIAL:
        case VOS_IP_ENROLLMENT:
        case VOS_IP_LOAD_DATA:
        case VOS_IP_FETCH_DATA:
        case VOS_IP_STARTUP:
        case VOS_IP_RIVAL:
        case VOS_IP_KICKOFF:
        case VOS_IP_STANDBY:
        case VOS_IP_BROADCAST_STATE:
        case VOS_IP_RESTART:
        case VOS_IP_BUTT:
            break;
    }

    return VOS_OK;
}


VOS_UINT32 ADS_DL_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    switch ( enPhase )
    {
        case VOS_IP_LOAD_CONFIG:

#if (defined(CONFIG_BALONG_SPE))
            /* 初始化内存池配置 */
            ADS_IPF_InitMemPoolCfg();

            /* 预分配内存 */
            ADS_IPF_CreateMemPool();
#endif

            /* ADQ初始化 */
            ADS_DL_AllocMemForAdq();

            /* 给低软注册回调函数，用于C核单独复位的处理 */
            mdrv_sysboot_register_reset_notify(NAS_ADS_DL_FUNC_PROC_NAME,
                                               ADS_DL_CCpuResetCallback,
                                               0,
                                               ACPU_RESET_PRIORITY_ADS_DL);

            break;

        default:
            break;
    }

    return VOS_OK;
}


VOS_VOID ADS_DL_FidTask(
    VOS_UINT32                          ulQueueID,
    VOS_UINT32                          FID_value,
    VOS_UINT32                          Para1,
    VOS_UINT32                          Para2
)
{
    MsgBlock                           *pMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulEvent       = 0;
    VOS_UINT32                          ulTaskID      = 0;
    VOS_UINT32                          ulRtn         = PS_FAIL;
    VOS_UINT32                          ulEventMask   = 0;
    VOS_UINT32                          ulExpectEvent = 0;

    ulTaskID = VOS_GetCurrentTaskID();
    if (PS_NULL_UINT32 == ulTaskID)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_FidTask: ERROR, TaskID is invalid.");
        return;
    }

    if (VOS_OK != VOS_CreateEvent(ulTaskID))
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_FidTask: ERROR, create event fail.");
        return;
    }

    g_ulAdsDLTaskId         = ulTaskID;
    g_ulAdsDLTaskReadyFlag  = 1;

    ulExpectEvent = ADS_DL_EVENT_IPF_RD_INT | ADS_DL_EVENT_IPF_ADQ_EMPTY_INT | VOS_MSG_SYNC_EVENT;
    ulEventMask   = (VOS_EVENT_ANY | VOS_EVENT_WAIT);

    /*lint -e716*/
    while (1)
    /*lint +e716*/
    {
        ulRtn = VOS_EventRead(ulExpectEvent, ulEventMask, 0, &ulEvent);

        if (VOS_OK != ulRtn)
        {
            ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_FidTask: ERROR, read event error.");
            continue;
        }

        /* 事件处理 */
        if (VOS_MSG_SYNC_EVENT != ulEvent)
        {
            ADS_DL_ProcEvent(ulEvent);
#ifdef __PC_UT__
            break;
#endif
            continue;
        }

        pMsg = (MsgBlock*)VOS_GetMsg(ulTaskID);
        if (VOS_NULL_PTR != pMsg)
        {
            if (ACPU_PID_ADS_DL == pMsg->ulReceiverPid)
            {
                ADS_DL_ProcMsg(pMsg);
            }

            PS_FREE_MSG(ACPU_PID_ADS_DL, pMsg);
        }

    }
}


VOS_UINT32 ADS_DL_FidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32                          ulRslt;
    VOS_INT32                           lIpfRslt;
    struct mdrv_ipf_ops                 stIpfOps;

    stIpfOps.rx_complete_cb = ADS_DL_IpfIntCB;
    stIpfOps.adq_empty_cb   = ADS_DL_IpfAdqEmptyCB;

    switch (ip)
    {
        case VOS_IP_LOAD_CONFIG:

            /* 下行PID初始化 */
            ulRslt = VOS_RegisterPIDInfo(ACPU_PID_ADS_DL,
                                         (Init_Fun_Type)ADS_DL_PidInit,
                                         (Msg_Fun_Type)ADS_DL_ProcMsg);

            if ( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }


            ulRslt = VOS_RegisterMsgTaskEntry(ACPU_FID_ADS_DL, (VOS_VOIDFUNCPTR)ADS_DL_FidTask);

            if (VOS_OK != ulRslt)
            {
                return ulRslt;
            }

            /* 调用mdrv_ipf_register_ops注册中断处理函数,以及AD空中断处理函数 */
            lIpfRslt = mdrv_ipf_register_ops(&stIpfOps);
            if (IPF_SUCCESS != lIpfRslt)
            {
                return VOS_ERR;
            }

            /* 任务优先级 */
            ulRslt = VOS_RegisterMsgTaskPrio(ACPU_FID_ADS_DL, VOS_PRIORITY_P6);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            break;

        case VOS_IP_FARMALLOC:
        case VOS_IP_INITIAL:
        case VOS_IP_ENROLLMENT:
        case VOS_IP_LOAD_DATA:
        case VOS_IP_FETCH_DATA:
        case VOS_IP_STARTUP:
        case VOS_IP_RIVAL:
        case VOS_IP_KICKOFF:
        case VOS_IP_STANDBY:
        case VOS_IP_BROADCAST_STATE:
        case VOS_IP_RESTART:
        case VOS_IP_BUTT:
            break;
    }

    return VOS_OK;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
