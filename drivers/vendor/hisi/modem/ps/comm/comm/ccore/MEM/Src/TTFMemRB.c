

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TTFMemRB.h"
#include "v_timer.h"
#include "v_id.h"
#include "TTFMem.h"
#include "TtfMemoryMap.h"
#include "TtfMemAtInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_TTF_MEM_RB_C
/*lint +e767*/

#if (FEATURE_ON == FEATURE_SKB_EXP)
/* 垃圾回收任务定时器时长 */
const VOS_UINT16 TTF_MEM_RB_TX_MEM_FREE_INTERVAL            = 1000;

/* 垃圾释放任务栈深度 */
const VOS_UINT16 TTF_MEM_RB_RX_MEM_FREE_TASK_STACK_SIZE     = 4096;

#if(TTF_DEBUG_TRACE_FUNC == FEATURE_ON)
/* TTF MEM 内存块调试打印开关 */
VOS_UINT8       g_ucTtfMemDebugPrint                        = PS_FALSE;
#endif

/* C核TTF内存释放队列 */
LUP_QUEUE_STRU  *g_pstCcpuTTFMemFreeQue                     = VOS_NULL_PTR;

/* C核IMM内存回收队列 */
LUP_QUEUE_STRU  *g_pstCcpuIMMMemFreeQue                     = VOS_NULL_PTR;

/* TTF MEM 内存释放门限 */
VOS_UINT8        g_ulFreeTtfMemBlkNoticNum                  = 0x1f;

/* CCPU通知IMC接收垃圾回收通知任务信号量 */
VOS_SEM         g_ulTtfMemRbFreeSem                         = 0;

/* TTF MEM RB 可维可测实体 */
TTF_MEM_RB_MNTN_INFO_STRU               g_stTtfMemRbMntnEntity;




/*其它版本支持IPC，中断号相同*/
#define TTF_IPC_MEM_FREE_INT                        (IPC_INT_DICC_RELDATA)
#define TTF_IPC_MEM_RECYCLE_INT                     (IPC_INT_DICC_RELDATA)

#define TTF_MEM_CONNECT_IPC_MEMFREE_INT(a,b,c)       mdrv_ipc_int_connect(a,b,c)
#define TTF_MEM_ENABLE_IPC_INT(a)                    mdrv_ipc_int_enable(a)
#define TTF_MEM_TRIG_IPC_MEMRB_INT(a,b)              mdrv_ipc_int_send(a,(IPC_INT_LEV_E)(b))


/*****************************************************************************
  3 私有定义
*****************************************************************************/
VOS_SPINLOCK             g_stTtfMemRBSpinLock;


/*****************************************************************************
  4 函数实现
*****************************************************************************/
/*lint -save -e958 */

VOS_VOID TTF_DebugLOG
(
    VOS_CHAR       *pcString
)
{
    (VOS_VOID)vos_printf(pcString);

    return;
}/* TTF_DebugLOG */



VOS_VOID TTF_DebugLOG1
(
    VOS_CHAR       *pcString,
    VOS_INT32       lPara1
)
{
    (VOS_VOID)vos_printf(pcString, lPara1);

    return;
}/* TTF_DebugLOG1 */



VOS_VOID TTF_DebugLOG2
(
    VOS_CHAR       *pcString,
    VOS_INT32       lPara1,
    VOS_INT32       lPara2
)
{
    (VOS_VOID)vos_printf(pcString, lPara1, lPara2);

    return;
}/* TTF_DebugLOG2 */



VOS_VOID TTF_DebugLOG3
(
    VOS_CHAR       *pcString,
    VOS_INT32       lPara1,
    VOS_INT32       lPara2,
    VOS_INT32       lPara3
)
{
    (VOS_VOID)vos_printf(pcString, lPara1, lPara2, lPara3);

    return;
}/* TTF_DebugLOG3 */



VOS_VOID TTF_DebugLOG4
(
    VOS_CHAR       *pcString,
    VOS_INT32       lPara1,
    VOS_INT32       lPara2,
    VOS_INT32       lPara3,
    VOS_INT32       lPara4
)
{
    (VOS_VOID)vos_printf(pcString, lPara1, lPara2, lPara3, lPara4);

    return;
}/* TTF_DebugLOG4 */



VOS_VOID TTF_MemRbRelDataIsr(VOS_VOID)
{
    if ( VOS_NULL == g_ulTtfMemRbFreeSem )
    {
        return ;
    }

    /* give semphore 调用OM提供的封装函数，释放信号量ulMemFreeSem */
    VOS_SmV(g_ulTtfMemRbFreeSem);
    g_stTtfMemRbMntnEntity.ulTtfMemRbReceiveIntCnt++;

    return ;
}    /* TTF_MemRbRelDataIsr */



VOS_UINT32 TTF_MemRbFreeMsgProc(const MsgBlock *pMsg)
{
    VOS_UINT32           ulMsgType;


    if ( VOS_NULL_PTR == pMsg )
    {
        /* 消息为空告警 */
        TTF_LOG(UEPS_PID_TTF_MEM_RB_FREE, DIAG_MODE_COMM, PS_PRINT_WARNING, "TTF_MemRb, TTF_MemRbFreeMsgProc, WARNING, Msg is NULL!\n");

        return VOS_ERR;
    }

    if ( WUEPS_PID_AT == pMsg->ulSenderPid )
    {
        ulMsgType = ((TTF_MEM_RB_CCPU_MEM_INFO_IND_STRU *)pMsg)->enMsgId;
    }
    else
    {
        return VOS_OK;
    }

    switch( ulMsgType )
    {
        case ID_TTF_AT_QRY_CCPU_MEM_INFO_IND:
            TTF_MemCcpuCheckPoolLeak();
        break;

        default:
        break;
    }

    return VOS_OK;

} /* TTF_MemRbFreeMsgProc */



VOS_VOID TTF_MemRbRemoteFreeMem( VOS_VOID *pucAddr)
{
    VOS_ULONG                           ulLockLevel;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulNum;
    VOS_INT32                           lIsrRet;    /* 中断操作返回值 */

    VOS_SpinLockIntLock(&g_stTtfMemRBSpinLock, ulLockLevel);
    ulResult    = LUP_EnQue(g_pstCcpuIMMMemFreeQue, pucAddr);
    g_stTtfMemRbMntnEntity.ulTtfMemRbEnQTotalCnt++;
    ulNum       = LUP_QueCnt(g_pstCcpuIMMMemFreeQue);
    VOS_SpinUnlockIntUnlock(&g_stTtfMemRBSpinLock, ulLockLevel);

    if (PS_SUCC != ulResult)
    {
        g_stTtfMemRbMntnEntity.ulTtfMemRbEnQFailCnt++;
        (VOS_VOID)vos_printf("TTF_MemRbRemoteFreeMem: LUP_EnQue fail!\n");
    }

#ifndef WTTF_PS_FUSION_PC_ST
    if ( 0 == (g_ulFreeTtfMemBlkNoticNum & ulNum))
    {
        lIsrRet = TTF_MEM_TRIG_IPC_MEMRB_INT(IPC_CORE_APPARM, TTF_IPC_MEM_RECYCLE_INT);
        g_stTtfMemRbMntnEntity.ulTtfMemRbSendIntCnt++;

        if (lIsrRet != VOS_OK)
        {
            TTF_LOG(UEPS_PID_TTF_MEM_RB_FREE, DIAG_MODE_COMM, PS_PRINT_ERROR, "ERROR:TTF_MemRbRemoteFreeMem: mdrv_ipc_int_send fail!\n");
        }
    }
#else
    lIsrRet = VHW_IPC_IntSend((IPC_INT_CORE_E)IPC_CORE_APPARM, (IPC_INT_LEV_E)IPC_INT_DICC_RELDATA);
    g_stTtfMemRbMntnEntity.ulTtfMemRbSendIntCnt++;

    if (lIsrRet != VOS_OK)
    {
        TTF_LOG(UEPS_PID_TTF_MEM_RB_FREE, DIAG_MODE_COMM, PS_PRINT_ERROR, "ERROR:TTF_MemRbRemoteFreeMem: mdrv_ipc_int_send fail!\n");
    }
#endif

    return;
}/*TTF_MemRbRemoteFreeMem*/




VOS_UINT32 TTF_MemRbIsrInit(VOS_UINT32 ulPid, VOS_UINT32 ulIntLevel,
                            VOIDFUNCPTR pfuncRecvIsr)
{
    VOS_INT32  lIntRet;


    /* 挂接中断 */
#ifndef WTTF_PS_FUSION_PC_ST
    lIntRet = TTF_MEM_CONNECT_IPC_MEMFREE_INT(((IPC_INT_LEV_E)ulIntLevel), ((VOIDFUNCPTR)pfuncRecvIsr), VOS_NULL);
#else
    lIntRet = VHW_IPC_IntConnect(ulPid,((IPC_INT_LEV_E)ulIntLevel), ((VOIDFUNCPTR)pfuncRecvIsr), VOS_NULL);
#endif

    if (lIntRet != VOS_OK)
    {
        TTF_LOG1(UEPS_PID_TTF_MEM_RB_FREE, DIAG_MODE_COMM, PS_PRINT_ERROR, "TTF_MemRbIsrInit connect %d ISR fail", (VOS_INT32)ulIntLevel);
        return VOS_ERR;
    }

    /* 使能通知中断 */
#ifndef WTTF_PS_FUSION_PC_ST
    TTF_MEM_ENABLE_IPC_INT((IPC_INT_LEV_E)ulIntLevel);
#else
    VHW_IPC_IntEnable(ulPid,ulIntLevel);
#endif

    return VOS_OK;
}    /* IMM_RbIsrInit */



VOS_UINT32 TTF_MemRbFreePidInit( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:

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
            break;
        default:
            break;
    }

    return VOS_OK;
}/* TTF_MemRbFreePidInit */



VOS_VOID TTF_MemFreeFromQue(VOS_VOID)
{
    TTF_MEM_ST *pstTtfMem = VOS_NULL_PTR;
    VOS_UINT32  ulResult;

    if (g_pstCcpuTTFMemFreeQue == VOS_NULL_PTR)
    {
        (VOS_VOID)vos_printf("CDS_TTFMemFree: g_pstCcpuTTFMemFreeQue is null\n");
        return;
    }

    if (g_pstCcpuTTFMemFreeQue->ulMaxNum != (TTF_MEM_FREE_QUE_LEN+1))
    {
        (VOS_VOID)vos_printf("CDS_TTFMemFree: g_pstCcpuTTFMemFreeQue ulMaxNum err\n");
        return;
    }


    while(PS_TRUE != (LUP_IsQueEmpty(g_pstCcpuTTFMemFreeQue)))
    {
        ulResult = LUP_DeQue(g_pstCcpuTTFMemFreeQue, (VOS_VOID **)&pstTtfMem);

        g_stTtfMemRbMntnEntity.ulTtfMemRbDeQTotalCnt++;

        if (PS_SUCC != ulResult)
        {
            g_stTtfMemRbMntnEntity.ulTtfMemRbDeQFailCnt++;
            (VOS_VOID)vos_printf("TTF_MemFreeFromQue: LUP_DeQue fail!\n");
            return;
        }

        TTF_MemFree(UEPS_PID_TTF_MEM_RB_FREE, pstTtfMem);
    }

    return;
}/* TTF_MemFreeFromQue */



VOS_VOID TTF_RbRxFreeMemTaskInit( VOS_VOID )
{
    VOS_UINT32              ulResult;


    PS_MEM_SET(&g_stTtfMemRbMntnEntity, 0x0, sizeof(TTF_MEM_RB_MNTN_INFO_STRU));

    /* 初始化信号量 */
    if ( VOS_OK != VOS_SmBCreate("ulMemFreeSem", 0, VOS_SEMA4_FIFO, (VOS_SEM *)&g_ulTtfMemRbFreeSem ) )
    {
         TTF_LOG(UEPS_PID_TTF_MEM_RB_FREE, DIAG_MODE_COMM, PS_PRINT_ERROR, "TTF_MemRb, TTF_MEM_RB_RxFreeMemTaskInit, ERROR, Create ulMemFreeSem fail!\n");
         return ;
    }

    /*两核内存回收和释放队列初始化*/
    /*lint -e778*/
    ulResult = LUP_CreateSharedQue(UEPS_PID_TTF_MEM_RB_FREE, &g_pstCcpuTTFMemFreeQue, TTF_MEM_FREE_QUE_LEN,
                                (VOS_UINT8*)(CORESHARE_MEM_WAN_ADDR), TTF_MEM_FREE_AREA_SIZE);
    /*lint +e778*/
    if (PS_SUCC != ulResult)
    {
         (VOS_VOID)vos_printf("TTF_RbRxFreeMemTaskInit: Create g_pstCcpuTTFMemFreeQue fail!\n");
         return ;
    }

    /*lint -e778*/
    ulResult = LUP_CreateSharedQue(UEPS_PID_TTF_MEM_RB_FREE, &g_pstCcpuIMMMemFreeQue, IMM_MEM_FREE_QUE_LEN,
                                (VOS_UINT8*)(CORESHARE_MEM_WAN_ADDR+TTF_MEM_FREE_AREA_SIZE), IMM_MEM_FREE_AREA_SIZE);
    /*lint +e778*/
    if (PS_SUCC != ulResult)
    {
         (VOS_VOID)vos_printf("TTF_RbRxFreeMemTaskInit: Create g_pstCcpuIMMMemFreeQue fail!\n");
         return ;
    }

    TTF_MemRbIsrInit(UEPS_PID_TTF_MEM_RB_FREE, TTF_IPC_MEM_FREE_INT, (VOIDFUNCPTR)TTF_MemRbRelDataIsr);

    TTF_MemRegExtFreeCallBack(TTF_MemRbRemoteFreeMem);

    return;
}/* TTF_RbRxFreeMemTaskInit */



VOS_VOID TTF_MemRbRxFreeMemTask(VOS_VOID)
{
    /* 解决UT死循环问题 */
#ifdef __UT_CENTER__
    VOS_UINT32                          ulLoop;
#endif
    VOS_UINT32                          ulLoopCnt = 0;
    VOS_UINT32                          ulSmRst   = VOS_OK;

    TTF_RbRxFreeMemTaskInit();

#ifndef __UT_CENTER__
    for ( ; ; )
#else
    for (ulLoop = 0; ulLoop < 1; ulLoop++)
#endif
    {
        ulSmRst = VOS_SmP(g_ulTtfMemRbFreeSem, 0);

        /* take信号量失败是异常失败 */
        if(VOS_OK != ulSmRst)
        {
            ulLoopCnt++;
            if (ulLoopCnt >= TTF_MEM_RB_TASK_FAIL_CNT_MAX)
            {
                mdrv_om_system_error((VOS_INT)(TTF_MEM_RB_TASK_FAIL_SEM_ERR), (VOS_INT)ulSmRst,
                                    (VOS_INT)g_ulTtfMemRbFreeSem, (VOS_VOID *)&g_ulFreeTtfMemBlkNoticNum, 2 * sizeof(VOS_UINT32));

            }

            TTF_LOG1(UEPS_PID_TTF_MEM_RB_FREE, DIAG_MODE_COMM, PS_PRINT_ERROR, "TTF_MemRb, TTF_MEM_RB_RxFreeMemTask : ERROR : VOS_SmP Failed, Error Code = %d !\n", (VOS_INT)ulSmRst);

            VOS_TaskDelay(2);

            continue;
        }

        /* 释放 */
        TTF_MemFreeFromQue();
    }

}/* TTF_MemRbRxFreeMemTask */



VOS_UINT32 TTF_MemRbFreeFidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulReturnCode;

    switch( ip )
    {
        case   VOS_IP_LOAD_CONFIG:

            /* TTF_MemRb 模块注册PID */
            ulRslt = VOS_RegisterPIDInfo(UEPS_PID_TTF_MEM_RB_FREE,
                                (Init_Fun_Type)TTF_MemRbFreePidInit,
                                (Msg_Fun_Type)TTF_MemRbFreeMsgProc);

            if( VOS_OK != ulRslt )
            {
                TTF_LOG1(UEPS_PID_TTF_MEM_RB_FREE, DIAG_MODE_COMM, PS_PRINT_ERROR, "reg TTF_MEM_RB_MemFreeFidInit VOS_RegisterPIDInfo FAIL! ulRslt: %d\n", (VOS_INT32)ulRslt);
                return (VOS_UINT32)VOS_ERROR;
            }

            ulRslt = VOS_RegisterTaskPrio(UEPS_FID_TTF_MEM_RB_FREE, TTF_MEM_RB_FREE_TASK_PRIO );
            if( VOS_OK != ulRslt )
            {
                TTF_LOG1(UEPS_PID_TTF_MEM_RB_FREE, DIAG_MODE_COMM, PS_PRINT_ERROR, "reg MEM FREE task priority register FAIL ulRslt : %d !\n", (VOS_INT32)ulRslt);
                return (VOS_UINT32)VOS_ERROR;
            }


            /* TTF_MemRbRxFreeMemTask自处理任务注册 */
            ulReturnCode = VOS_RegisterSelfTask(UEPS_FID_TTF_MEM_RB_FREE,(VOS_TASK_ENTRY_TYPE)TTF_MemRbRxFreeMemTask,VOS_PRIORITY_P5, (VOS_UINT32)TTF_MEM_RB_RX_MEM_FREE_TASK_STACK_SIZE);

            if ( VOS_NULL_BYTE == ulReturnCode )
            {
                TTF_LOG(UEPS_PID_TTF_MEM_RB_FREE, DIAG_MODE_COMM, PS_PRINT_ERROR, "TTF_MemRb, TTF_MEM_RB_MemFreeFidInit, ERROR, Fail regist IMM_RxFreeMemTask \n" );

                return (VOS_UINT32)VOS_ERROR;
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
            break;

        default:
            break;
    }

    return VOS_OK;
}/* TTF_MemRbFreeFidInit */



VOS_VOID TTF_MemRbShowMntnInfo( VOS_VOID )
{
    (VOS_VOID)vos_printf("===========================================\n" );
    (VOS_VOID)vos_printf("TTF MEM RB 可维可测信息 :\n" );
    (VOS_VOID)vos_printf("C2A 核间释放队列中节点个数  : %d \n", (VOS_INT32)LUP_QueCnt(g_pstCcpuIMMMemFreeQue));
    (VOS_VOID)vos_printf("A2C 核间释放队列中节点个数  : %d \n", (VOS_INT32)LUP_QueCnt(g_pstCcpuTTFMemFreeQue));
    (VOS_VOID)vos_printf("TtfMemRb 出队失败次数       : %d \n", (VOS_INT32)g_stTtfMemRbMntnEntity.ulTtfMemRbDeQFailCnt);
    (VOS_VOID)vos_printf("TtfMemRb 出队总次数         : %d \n", (VOS_INT32)g_stTtfMemRbMntnEntity.ulTtfMemRbDeQTotalCnt);
    (VOS_VOID)vos_printf("TtfMemRb 入队失败次数       : %d \n", (VOS_INT32)g_stTtfMemRbMntnEntity.ulTtfMemRbEnQFailCnt);
    (VOS_VOID)vos_printf("TtfMemRb 入队总次数         : %d \n", (VOS_INT32)g_stTtfMemRbMntnEntity.ulTtfMemRbEnQTotalCnt);
    (VOS_VOID)vos_printf("TtfMemRb 收到IPF中断次数    : %d \n", (VOS_INT32)g_stTtfMemRbMntnEntity.ulTtfMemRbReceiveIntCnt);
    (VOS_VOID)vos_printf("TtfMemRb 向IPF发送中断次数  : %d \n", (VOS_INT32)g_stTtfMemRbMntnEntity.ulTtfMemRbSendIntCnt);

    return;

}/* TTF_MemMntnInfo */

VOS_VOID TTF_MemShowMntnInfo( VOS_VOID )
{
    TTF_MemFreeShowMntnInfo();
    TTF_MemRbShowMntnInfo();
}



VOS_VOID TTF_MemClearMntnInfo( VOS_VOID )
{
    PS_MEM_SET(&g_stTtfMemFreeMntnEntity, 0x0, sizeof(TTF_MEM_FREE_MNTN_INFO_STRU));
    PS_MEM_SET(&g_stTtfMemRbMntnEntity, 0x0, sizeof(TTF_MEM_RB_MNTN_INFO_STRU));
}



#if(TTF_DEBUG_TRACE_FUNC == FEATURE_ON)
VOS_VOID TTF_MemSetTraceFunc(VOS_UINT8 ucChoice)
{
    g_ucTtfMemDebugPrint = ucChoice;

    return;
}/* TTF_MemSetTraceFunc */
#endif


VOS_VOID TTF_RbMemPrintIsrCnt( VOS_VOID )
{
    (VOS_VOID)vos_printf("C核收到IPF中断次数: %d\n" , (VOS_INT32)g_stTtfMemRbMntnEntity.ulTtfMemRbReceiveIntCnt );
    return;
}/* TTF_RbMemPrintIsrCnt */

#else

VOS_UINT32 TTF_MemRbFreeFidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{

    return VOS_OK;
}
/*lint -restore */

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

