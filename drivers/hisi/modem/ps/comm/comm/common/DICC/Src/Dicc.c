
 
 #ifdef  __cplusplus
 #if  __cplusplus
    extern "C" {
 #endif
#endif

/******************************************************************************
   1 头文件包含
******************************************************************************/
#include "product_config.h"
#if( FEATURE_ON == FEATURE_CSD )

#include "vos.h"
#include "Dicc.h"
#if (VOS_WIN32 != VOS_OS_VER)
    #if (OSA_CPU_CCPU == VOS_OSA_CPU)
    #elif (OSA_CPU_ACPU == VOS_OSA_CPU)
    #include <linux/spinlock.h>
    #endif
#else
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e(767)*/
#define     THIS_FILE_ID PS_FILE_ID_DICC_C
/*lint +e(767)*/

#if (VOS_WIN32 != VOS_OS_VER)
    #if (OSA_CPU_CCPU == VOS_OSA_CPU)
    #define    DICC_LOCAL_CPU_ID   (DICC_CPU_ID_CCPU)
    #define    LOCAL_UEPS_PID_DICC (UEPS_PID_DICC_C)
    #elif (OSA_CPU_ACPU == VOS_OSA_CPU)
    #define    DICC_LOCAL_CPU_ID (DICC_CPU_ID_ACPU)
    #define    LOCAL_UEPS_PID_DICC (UEPS_PID_DICC_A)
    #endif
#else
    #define     LOCAL_UEPS_PID_DICC (UEPS_PID_DICC_A)    /* WIN32上按照A核来设置PID, 用于看虚实转换有没有执行 */
#endif

#ifdef __UT_CENTER__
    #define DICC_TTF_PHY_TO_VIRT(var) (g_aucDiccBuff)
    #define DICC_DRV_PHY_TO_VIRT(var) (&g_ulMagicNum)
#else
    #define  DICC_TTF_PHY_TO_VIRT(var)  (TTF_PHY_TO_VIRT(var))
    #define  DICC_DRV_PHY_TO_VIRT(var)  (DRV_AXI_PHY_TO_VIRT(var))
#endif

/******************************************************************************
   2 外部函数变量声明
******************************************************************************/


/******************************************************************************
   3 私有定义
******************************************************************************/
/* DICC模块内部的DFx功能开关, 1 - 打开, 0 - 关闭 */
#define DICC_DFX_SWITCH    (1)

/* 调试使用的宏 */
#define DICC_BBIT          (0)
#define DICC_RELEASE       (1)

/* 调试打印 */
#define DEBUG_PRINT(...)\
        {\
            if ( PS_TRUE == g_ulDiccDebugPrint )\
            {\
                vos_printf(__VA_ARGS__);\
            }\
        }

#define DICC_LOG(Level, String)\
    {\
        (TTF_LOG(LOCAL_UEPS_PID_DICC, DIAG_MODE_COMM, (Level), (String)));\
        /*lint --e{506, 774}*/\
        if (DICC_BBIT == g_ucDiccStability)\
        {\
            if (((Level) == PS_PRINT_WARNING) || ((Level) == PS_PRINT_ERROR))\
            {\
                Print((String));\
            }\
        }\
    }
#define DICC_LOG1(Level, String, Para1)\
    {\
        (TTF_LOG1(LOCAL_UEPS_PID_DICC, DIAG_MODE_COMM, (Level), (String), (Para1)));\
        /*lint --e{506, 774}*/\
        if (DICC_BBIT == g_ucDiccStability)\
        {\
            if (((Level) == PS_PRINT_WARNING) || ((Level) == PS_PRINT_ERROR))\
            {\
                Print1((String), (Para1));\
            }\
        }\
    }
#define DICC_LOG2(Level, String, Para1, Para2)\
    {\
        (TTF_LOG2(LOCAL_UEPS_PID_DICC, DIAG_MODE_COMM, (Level), (String), (Para1), (Para2)));\
        /*lint --e{506, 774}*/\
        if (DICC_BBIT == g_ucDiccStability)\
        {\
            if (((Level) == PS_PRINT_WARNING) || ((Level) == PS_PRINT_ERROR))\
            {\
                Print2((String), (Para1), (Para2));\
            }\
        }\
    }
#define DICC_LOG3(Level, String, Para1, Para2, Para3)\
    {\
        (TTF_LOG3(LOCAL_UEPS_PID_DICC, DIAG_MODE_COMM, (Level), (String), (Para1), (Para2), (Para3)));\
        /*lint --e{506, 774}*/\
        if (DICC_BBIT == g_ucDiccStability)\
        {\
            if (((Level) == PS_PRINT_WARNING) || ((Level) == PS_PRINT_ERROR))\
            {\
                Print3((String), (Para1), (Para2), (Para3));\
            }\
        }\
    }
#define DICC_LOG4(Level, String, Para1, Para2, Para3, Para4)\
    {\
        (TTF_LOG4(LOCAL_UEPS_PID_DICC, DIAG_MODE_COMM, (Level), (String), (Para1), (Para2), (Para3), (Para4)));\
        /*lint --e{506, 774}*/\
        if (DICC_BBIT == g_ucDiccStability)\
        {\
            if (((Level) == PS_PRINT_WARNING) || ((Level) == PS_PRINT_ERROR))\
            {\
                Print4((String), (Para1), (Para2), (Para3), (Para4));\
            }\
        }\
    }


/******************************************************************************
   4 全局变量定义
******************************************************************************/
/*
DICC通道记录表
采用静态配置方式, 既管理简单, 又能防止通道的误使用
 */
volatile DICC_CHAN_ROLE_STRU g_astChanRole[] =
{
    {
        /* enLocalCpuId */
        DICC_CPU_ID_CCPU,

        /* aenSender */
        {
            DICC_CHAN_ID_2,           /* for service 0 */
            DICC_CHAN_ID_1            /* for service 1 */
        },

        /* aenRecver */
        {
            DICC_CHAN_ID_0,           /* for service 0 */
            DICC_CHAN_ID_3            /* for service 1 */
        },

        /* aenRole */
        {
            DICC_CHAN_ROLE_RECVER,    /* for channel 0 */
            DICC_CHAN_ROLE_SENDER,    /* for channel 1 */
            DICC_CHAN_ROLE_SENDER,    /* for channel 2 */
            DICC_CHAN_ROLE_RECVER     /* for channel 3 */
        },

        /* aucReserve */
        {
            0x00,
            0x00
        },

        /* ucSemCreated */
        0,

        /* ulDiccLocalMutexSem */
        VOS_NULL,

        /* pastDICCMgmt */
        VOS_NULL_PTR,

        /* PID */
        UEPS_PID_DICC_C
    },
    {
        /* enLocalCpuId */
        DICC_CPU_ID_ACPU,

        /* aenSender */
        {
            DICC_CHAN_ID_0,           /* for service 0 */
            DICC_CHAN_ID_3            /* for service 1 */
        },

        /* aenRecver */
        {
            DICC_CHAN_ID_2,           /* for service 0 */
            DICC_CHAN_ID_1            /* for service 1 */
        },

        /* aenRole */
        {
            DICC_CHAN_ROLE_SENDER,    /* for channel 0 */
            DICC_CHAN_ROLE_RECVER,    /* for channel 1 */
            DICC_CHAN_ROLE_RECVER,    /* for channel 2 */
            DICC_CHAN_ROLE_SENDER     /* for channel 3 */
        },

        /* aucReserve */
        {
            0x00,
            0x00
        },

        /* ucSemCreated */
        0,

        /* ulDiccLocalMutexSem */
        VOS_NULL,

        /* pastDICCMgmt */
        VOS_NULL_PTR,

        /* PID */
        UEPS_PID_DICC_A
    }
};

/* 串口打印开关, 设置为PS_TRUE时, 会向串口打印 */
VOS_UINT32 g_ulDiccDebugPrint                            = PS_FALSE;
VOS_UINT8  g_ucDiccPrintDataMaxLen                       = DICC_DEBUG_PRINT_MAX_LEN;
DICC_TRACE_INFO_STRU g_stDiccTraceInfo[DICC_CPU_ID_BUTT] = {{0,0,{0,0},0,0,0},{0,0,{0,0},0,0,0}};
VOS_UINT8  g_ucDiccStability                             = DICC_BBIT;

/* DICC初始化函数重入标记 */
VOS_UINT32      g_ulDiccMultiCoreFlag                    = DICC_MUTEX_SEM_NOT_CREATE;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
spinlock_t      g_stDiccSpinLock;
#endif

#ifdef __UT_CENTER__
VOS_UINT8 g_aucDiccBuff[DICC_QUEUE_MEM_SIZE] = {0};
VOS_UINT32 g_ulMagicNum;
#endif


/******************************************************************************
   5 函数实现
******************************************************************************/
/*lint -save -e958 */
/*****************************************************************************
 函 数 名  : Debug_DataPrint
 功能描述  : 供调试使用，打印数据信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月26日
    作    者   : s00164817
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DICC_PrintDebugData(VOS_VOID *pData, VOS_UINT32 ulDataLen)
{
    VOS_UINT8       *ptr;
    VOS_UINT32       ulLoop;
    VOS_UINT32       ulLoopLen;

    ptr       = (VOS_UINT8 *)pData;
    if (VOS_NULL_PTR == ptr)
    {
        return;
    }

    if (PS_TRUE != g_ulDiccDebugPrint)
    {
        return;
    }

    ulLoopLen = ulDataLen;
    if (ulDataLen > g_ucDiccPrintDataMaxLen)
    {
        vos_printf("Debug_DataPrint Data too long = %d ", ulDataLen );
        ulLoopLen = g_ucDiccPrintDataMaxLen;
    }

    for (ulLoop = 0; ulLoop < ulLoopLen; ++ulLoop)
    {
        vos_printf("0x%x ", ptr[ulLoop]);
    }

    vos_printf("\n");
}

/*****************************************************************************
 函 数 名  : Debug_PrintStateSet
 功能描述  : 供调试使用，配置Debug_print
 输入参数  : ulPrintState - 打印状态, PS_TRUE - 打印状态, 其它 - 关闭打印
             ucPrintDataMaxLen - 打印DICC通道数据字节数上限, 单位: 字节
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月26日
    作    者   : s00164817
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DICC_SetDebugPrintState(VOS_UINT32 ulPrintState, VOS_UINT8 ucPrintDataMaxLen)
{
    g_ulDiccDebugPrint      = (PS_TRUE != ulPrintState) ? PS_FALSE : PS_TRUE;
    g_ucDiccPrintDataMaxLen = (DICC_DEBUG_PRINT_MAX_LEN < ucPrintDataMaxLen) ? DICC_DEBUG_PRINT_MAX_LEN : ucPrintDataMaxLen;

    return;
}/* Debug_PrintStateSet */

/*****************************************************************************
 函 数 名  : DICC_TraceInfo
 功能描述  : 借鉴VC下TRACE记录机制, 记录下程序执行路径, 支持手动打印到串口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月17日
    作    者   : liukai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DICC_TraceInfo()
{
    DICC_TRACE_INFO_STRU     *pstDiccTraceInfo;
    DICC_CPU_ID_ENUM_UINT8    enCpuId;

#if (VOS_WIN32 != VOS_OS_VER)
 #if (OSA_CPU_CCPU == VOS_OSA_CPU)
    enCpuId = DICC_CPU_ID_CCPU;
 #elif (OSA_CPU_ACPU == VOS_OSA_CPU)
    enCpuId = DICC_CPU_ID_ACPU;
 #endif
#else
    enCpuId = DICC_CPU_ID_ACPU;
#endif

    pstDiccTraceInfo = &g_stDiccTraceInfo[enCpuId];

    vos_printf("enCpuId=%d\n",  pstDiccTraceInfo->enCpuId);
    vos_printf("enFuncId=%d\n", pstDiccTraceInfo->enFuncId);
    vos_printf("ulPid=%d\n",    pstDiccTraceInfo->ulPid);
    vos_printf("ulLine=%d\n",   pstDiccTraceInfo->ulLine);
    vos_printf("enResult=%d\n", pstDiccTraceInfo->enResult);
}    /* DICC_TraceInfo */

VOS_VOID DICC_DealWithFatalError(DICC_SOFT_REBOOT_INFO_STRU *pstRebootInfo)
{
    VOS_UINT32    ulTaskID;

    if (DICC_BBIT == g_ucDiccStability)
    {
        ulTaskID = VOS_GetCurrentTaskID();

        if ( VOS_OK != VOS_SuspendTask( ulTaskID ) )
        {
            DICC_LOG(PS_PRINT_ERROR, "# SUSPED PPP task error.\r\n");
        }
    }

    if (DICC_RELEASE == g_ucDiccStability)
    {
        if (VOS_NULL_PTR != pstRebootInfo)
        {
            /* 调用OM API进行单板复位 */
            VOS_ProtectionReboot((VOS_INT)pstRebootInfo->ulModule,
                (VOS_INT)(pstRebootInfo->ulFile), (VOS_INT)(pstRebootInfo->ulLine),
                (VOS_CHAR *)(pstRebootInfo->pucData),
                sizeof(pstRebootInfo->ulDataLen) );
        }
    }
}

/*****************************************************************************
 函 数 名  : DICC_SndEvent
 功能描述  : 上报DICC事件
 输入参数  : ulPid - 操作PID
             enEventId - 事件ID
             pEventData - 事件信息内容
             ulDataLen - 事件信息长度
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月22日
    作    者   : liukai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  DICC_SndEvent(DICC_MNTN_EVENT_ID_ENUM_UINT16 enEventId,
                        VOS_VOID   *pEventData,
                        VOS_UINT32  ulDataLen,
                        DICC_CPU_ID_ENUM_UINT8  enCpuId)
{
    DIAG_EVENT_IND_STRU                 stEvent;

    stEvent.ulEventId   = enEventId;
    stEvent.ulPid       = LOCAL_UEPS_PID_DICC;
    stEvent.ulModule    = DIAG_GEN_MODULE(VOS_GetModemIDFromPid(LOCAL_UEPS_PID_DICC), DIAG_MODE_COMM);
    stEvent.ulLength    = ulDataLen;
    stEvent.pData       = pEventData;

    /*调用OM的事件上报接口*/
#if (VOS_WIN32 != VOS_OS_VER)
    if (VOS_OK != DIAG_EventReport((DIAG_EVENT_IND_STRU *)&pEventData))
    {
        DICC_LOG(PS_PRINT_ERROR, "[LOCAL CPU_ID: DICC_SndEvent] DIAG_EventReport fail");
    }
#else
    /* 计划在PC机上测试A核, 但当前OAM组没有把DIAG_EventReport在WIN32上实现好,
       报不出事件, 暂时用DIAG_EventReport上报 */
    if (DICC_CPU_ID_CCPU == enCpuId)
    {
        if (VOS_OK != DIAG_EventReport((DIAG_EVENT_IND_STRU *)&pEventData))
        {
            DICC_LOG(PS_PRINT_ERROR, "[LOCAL CPU_ID: DICC_SndEvent] DIAG_EventReport fail");
        }
    }

    if (DICC_CPU_ID_ACPU == enCpuId)
    {
        if (VOS_OK != DIAG_EventReport((DIAG_EVENT_IND_STRU *)&pEventData))
        {
            DICC_LOG(PS_PRINT_ERROR, "[LOCAL CPU_ID: DICC_SndEvent] DIAG_EventReport fail");
        }
    }
#endif

    return ;
}    /* DICC_SndEvent */

/*****************************************************************************
函 数 名  : DICC_GetCtrlChnAddr
功能描述  : 获取通道的控制数据结构起始地址
输入参数  : ucChnId - 通道ID
输出参数  : 无
返 回 值  : 通道的控制数据结构起始地址
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年8月20日
   作    者   : g00178567
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8* DICC_GetCtrlChnAddr(VOS_UINT8 ucChnId, DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    VOS_UINT8                               *pucCtrlChnAddr = VOS_NULL_PTR;
    VOS_UINT8                               *pucStartAddr = VOS_NULL_PTR;

    pucStartAddr   = (VOS_UINT8*)(g_astChanRole[enCpuId].pastDICCMgmt);
    pucCtrlChnAddr = pucStartAddr + sizeof(DICC_CTRL_STRU) + (ucChnId * sizeof(DICC_CHAN_CTRL_STRU));

    return pucCtrlChnAddr;
}/* DICC_GetCtrlChnAddr */

/*****************************************************************************
函 数 名  : DICC_GetTtfRingQStChnAddr
功能描述  : 获取通道的TTF_RING_Q_ST管理结构(DICC queue node)起始地址
输入参数  : ucChnId - 通道ID
输出参数  : 无
返 回 值  : 通道的TTF_RING_Q_ST管理结构起始地址
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年8月20日
   作    者   : g00178567
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8* DICC_GetTtfRingQStChnAddr(VOS_UINT8 ucChnId, DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    DICC_CHAN_CTRL_STRU                    *pstDiccChnCtrl = VOS_NULL_PTR;
    VOS_UINT8                              *pucSpace = VOS_NULL_PTR;

    /* 初始化为核间内存首地址 */
    pucSpace = (VOS_UINT8 *)(g_astChanRole[enCpuId].pastDICCMgmt);
    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);

    /* 加上通道的TTFRINGQST偏移量 */
    pucSpace = pucSpace + pstDiccChnCtrl->ulTtfRingQStAddrOffSet;

    return pucSpace;
}/* DICC_GetTtfRingQStChnAddr */

/*****************************************************************************
函 数 名  : DICC_GetQueueNodeChnAddr
功能描述  : 获取核间通道用于传递数据的内存(DICC queue data)起始地址
输入参数  : ucChnId - 通道ID
输出参数  : 无
返 回 值  : 核间通道用于传递数据的起始地址
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年8月20日
   作    者   : g00178567
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8* DICC_GetQueueNodeChnAddr(VOS_UINT8 ucChnId,
               DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    DICC_CHAN_CTRL_STRU                    *pstDiccChnCtrl = VOS_NULL_PTR;
    VOS_UINT8                              *pucSpace = VOS_NULL_PTR;

    /* 初始化为核间内存首地址 */
    pucSpace = (VOS_UINT8 *)(g_astChanRole[enCpuId].pastDICCMgmt);
    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);

    /* 加上通道的TTFRINGQST偏移量 */
    pucSpace = pucSpace + pstDiccChnCtrl->ulQueueNodeAddrOffSet;

    return pucSpace;
}/* DICC_GetQueueNodeChnAddr */

/*****************************************************************************
函 数 名  : DICC_GetChannelNodeCnt
功能描述  : 检查获取通道中数据块数的参数
输入参数  : ulPid - 调用此接口的PID
            ucChanId - 通道ID
            enGetChnNodeCntType - 指示获取通道中已经存放的数据个数,
                                  或者通道中可以继续存放的个数
输出参数  : 无
返 回 值  : 操作成功与否, DICC_OK - 成功, 其它 - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年8月11日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_CheckCpuId(DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    if (DICC_CPU_ID_BUTT <= enCpuId)
    {
        return DICC_ERR_CPU_ID_NOT_MATCH;
    }

#if (VOS_WIN32 != VOS_OS_VER)
 #if (OSA_CPU_CCPU == VOS_OSA_CPU)
    if (DICC_CPU_ID_CCPU != enCpuId)
    {
        return DICC_ERR_CPU_ID_NOT_MATCH;
    }
 #elif (OSA_CPU_ACPU == VOS_OSA_CPU)
    if (DICC_CPU_ID_ACPU != enCpuId)
    {
        return DICC_ERR_CPU_ID_NOT_MATCH;
    }
 #endif
#endif

    return DICC_OK;
}

/*****************************************************************************
函 数 名  : DICC_RecordIsrOp
功能描述  : 记录用户中断操作
输入参数  : pstIsrRecord - 用户操作中断的记录信息
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年12月13日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DICC_RecordIsrOp(DICC_RECORD_ISR_STRU *pstIsrRecord,
                          DICC_CPU_ID_ENUM_UINT8       enCpuId)
{
    DICC_DFX_STRU        *pstDFx;
    VOS_UINT8             ucChanId;

    pstDFx = DICC_GET_CHAN_DFX(g_astChanRole[enCpuId].pastDICCMgmt);

    if (PS_TRUE == pstIsrRecord->enOpResult)    /* 正确操作中断, 记录下轨迹即可 */
    {
        /* 在通道完成初始化后, 都是接收端来DiableIsr, EnableIsr */
        ucChanId = g_astChanRole[enCpuId].aenRecver[pstIsrRecord->enServiceType];

        if (DICC_SERVICE_ISR_ENABLE == pstIsrRecord->enIsrOp)
        {
            pstDFx->astChanStatus[ucChanId].stIsrOp.ulEnableOpPid  = pstIsrRecord->ulPid;
            pstDFx->astChanStatus[ucChanId].stIsrOp.ulEnableOpTime = mdrv_timer_get_normal_timestamp();
            pstDFx->astChanStatus[ucChanId].stIsrOp.ulEnableCnt++;
        }
        else
        {
            pstDFx->astChanStatus[ucChanId].stIsrOp.ulDisableOpPid  = pstIsrRecord->ulPid;
            pstDFx->astChanStatus[ucChanId].stIsrOp.ulDisableOpTime = mdrv_timer_get_normal_timestamp();
            pstDFx->astChanStatus[ucChanId].stIsrOp.ulDisableCnt++;
        }
    }
    else    /* 当DiableIsr, EnableIsr参数错误时, 记录到Debug中, 只记录下最近一次的情形 */
    {
        if (DICC_SERVICE_ISR_ENABLE == pstIsrRecord->enIsrOp)
        {
            pstDFx->stIsrDbg.ulInvalidEnableOpPid   = pstIsrRecord->ulPid;
            pstDFx->stIsrDbg.ulInvalidEnableOpTime  = mdrv_timer_get_normal_timestamp();
        }
        else
        {
            pstDFx->stIsrDbg.ulInvalidDisableOpPid  = pstIsrRecord->ulPid;
            pstDFx->stIsrDbg.ulInvalidDisableOpTime = mdrv_timer_get_normal_timestamp();
        }
    }
}    /* DICC_RecordIsrOp */

/*****************************************************************************
函 数 名  : DICC_EnableIsr
功能描述  : 上报用户操作消息
输入参数  : 使能核间通信中断API
输出参数  : ulPid - 操作PID
            enServiceType - 服务号
返 回 值  : 操作成功与否, DICC_OK - 成功, 其它 - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年8月13日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_EnableIsr(VOS_UINT32                   ulPid,
                          DICC_SERVICE_TYPE_ENUM_UINT8 enServiceType,
                          DICC_CPU_ID_ENUM_UINT8       enCpuId)
{
#if (1 == DICC_DFX_SWITCH)
    DICC_RECORD_ISR_STRU    stIsrRecord;
#endif
    VOS_UINT32              ulRet;
    /*lint --e{550, 830} */
    PS_BOOL_ENUM_UINT8      enOpResult;    /* PS_FALSE - 误操作中断 */
    VOS_INT32               lIntRet;    /* 中断操作返回值 */
    IPC_INT_LEV_E           lIntLvl;

    if ((DICC_SERVICE_TYPE_0 != enServiceType)
        && (DICC_SERVICE_TYPE_1 != enServiceType))
    {
        enOpResult = PS_FALSE;    /* 无此服务类别, 属于误操作中断 */
        ulRet      = DICC_ERR_SERVCE_UNDEFINED;
    }
    else
    {
        enOpResult = PS_TRUE;    /* 正确的服务类别, 不属于误操作中断 */
        ulRet      = DICC_OK;

        if (DICC_SERVICE_TYPE_0 == enServiceType)
        {
            lIntLvl = DICC_SERVICE_0_INT_LEVEL;
        }
        else
        {
            lIntLvl = DICC_SERVICE_1_INT_LEVEL;
        }

        /* 使能service通知中断 */
#ifndef WTTF_PS_FUSION_PC_ST
        lIntRet = mdrv_ipc_int_enable(lIntLvl);
#else
        lIntRet = VHW_IPC_IntEnable(ulPid,lIntLvl);
#endif
        if (BSP_OK != lIntRet)
        {
            ulRet      = DICC_ERR_OP_ISR_FAIL;
        }
    }

#if (1 == DICC_DFX_SWITCH)
    SET_ISR_RECORD(&stIsrRecord, ulPid, enServiceType, DICC_SERVICE_ISR_ENABLE, enOpResult);
    DICC_RecordIsrOp(&stIsrRecord, enCpuId);    /* 记录用户误操作中断 */
#endif

    return ulRet;
}    /* DICC_EnableIsr */

/*****************************************************************************
函 数 名  : DICC_DisableIsr
功能描述  : 去使能核间通信中断API
            在中断服务程序中执行, 不能有阻塞性操作
输入参数  : ulPid - 操作PID
            enServiceType - 服务号
输出参数  : 无
返 回 值  : 操作成功与否, DICC_OK - 成功, 其它 - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年12月7日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_DisableIsr(VOS_UINT32 ulPid, DICC_SERVICE_TYPE_ENUM_UINT8 enServiceType,
               DICC_CPU_ID_ENUM_UINT8       enCpuId)
{
#if (1 == DICC_DFX_SWITCH)
    DICC_RECORD_ISR_STRU    stIsrRecord;
#endif
    VOS_UINT32              ulRet;
    /*lint --e{550, 830} */
    PS_BOOL_ENUM_UINT8      enOpResult;    /* PS_FALSE - 误操作中断 */
    VOS_INT32               lIntRet;    /* 中断操作返回值 */
    IPC_INT_LEV_E           lIntLvl;

    if ((DICC_SERVICE_TYPE_0 != enServiceType)
        && (DICC_SERVICE_TYPE_1 != enServiceType))
    {
        enOpResult = PS_FALSE;    /* 无此服务类别, 属于误操作中断 */
        ulRet      = DICC_ERR_SERVCE_UNDEFINED;
    }
    else
    {
        enOpResult = PS_TRUE;    /* 正确的服务类别, 不属于误操作中断 */
        ulRet      = DICC_OK;

        if (DICC_SERVICE_TYPE_0 == enServiceType)
        {
            lIntLvl = DICC_SERVICE_0_INT_LEVEL;
        }
        else
        {
            lIntLvl = DICC_SERVICE_1_INT_LEVEL;
        }

        /* 去使能service通知中断 */
#ifndef WTTF_PS_FUSION_PC_ST
        lIntRet = mdrv_ipc_int_disable(lIntLvl);
#else
        lIntRet = VHW_IPC_IntDisable(ulPid,lIntLvl);
#endif

        if (BSP_OK != lIntRet)
        {
            ulRet      = DICC_ERR_OP_ISR_FAIL;
        }
    }

#if (1 == DICC_DFX_SWITCH)
    SET_ISR_RECORD(&stIsrRecord, ulPid, enServiceType, DICC_SERVICE_ISR_DISABLE, enOpResult);
    DICC_RecordIsrOp(&stIsrRecord, enCpuId);    /* 记录用户误操作中断 */
#endif

    return ulRet;
}    /* DICC_DisableIsr */

/*****************************************************************************
函 数 名  : DICC_CheckIsExistEnoughMem
功能描述  : 检查核间是否还存在足够的内存
输入参数  : penSndChnInfo    -   通道参数
输出参数  : 无
返 回 值  : 操作成功与否, DICC_OK - 成功, 其它 - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年8月20日
   作    者   : g00178567
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_CheckIsExistEnoughMem(DICC_BLK_CHN_INFO_STRU *penSndChnInfo,
               DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    VOS_UINT32 ulAllocMemSize;

    if ((0 == penSndChnInfo->usChnBlkNum)
        || (DICC_PER_QUEUE_MAX_NODE_NUM < penSndChnInfo->usChnBlkNum))
    {
        DICC_LOG1(PS_PRINT_WARNING, "[LOCAL CPU_ID: DICC_CheckIsExistEnoughMem] check <usChnBlkNum> fail",
            penSndChnInfo->usChnBlkNum);

        return DICC_ERR_CHAN_BLK_NUM;
    }

    if (DICC_INFO_BLOCK_MAX_LEN < penSndChnInfo->usChnBlkSize)
    {
        DICC_LOG1(PS_PRINT_WARNING, "[LOCAL CPU_ID: DICC_CheckIsExistEnoughMem] check <usChnBlkSize> fail",
            penSndChnInfo->usChnBlkSize);

        return DICC_ERR_CHAN_BLK_SIZE;
    }

    ulAllocMemSize = (penSndChnInfo->usChnBlkNum) * (penSndChnInfo->usChnBlkSize + sizeof(VOS_VOID *));

    if ((g_astChanRole[enCpuId].pastDICCMgmt->ulCurrSize + ulAllocMemSize) > DICC_MEMORY_TOTAL_SIZE)
    {
        DICC_LOG(PS_PRINT_WARNING, "[LOCAL CPU_ID: DICC_CheckIsExistEnoughMem] check total memory size fail");

        /* 确保了blk_size和blk_num的正确性, 就不会出现内存不足, 故不再重复上报SDT */
        return DICC_ERR_MEM_SIZE;
    }

    return DICC_OK;
}/* DICC_CheckIsExistEnoughMem */

/*****************************************************************************
函 数 名  : DICC_CheckChnInitStatus
功能描述  : 检查核间通道是否已经初始化
输入参数  : enServiceType - 服务号
输出参数  : 无
返 回 值  : DICC_OK       -    通道未初始化
            其它          -    通道已经初始化
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年8月20日
   作    者   : g00178567
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_CheckChnInitStatus(DICC_SERVICE_TYPE_ENUM_UINT8 enServiceType,
               DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    DICC_CHAN_ID_ENUM_UINT8             ucChnId;
    volatile DICC_CHAN_CTRL_STRU       *pstDiccChnCtrl;

    ucChnId = g_astChanRole[enCpuId].aenSender[enServiceType];
    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);

    /* 存在其他任务抢占pstDiccChnCtrl->ucValidFlag的问题，需要加任务互斥锁 */

    if (DICC_CHAN_STATUS_INITIALED == pstDiccChnCtrl->enValidFlag)    /* 发送通道已初始化 */
    {
        VOS_TaskUnlock();
        DICC_LOG1(PS_PRINT_WARNING, "[LOCAL CPU_ID: DICC_CheckChnInitStatus] <pstDiccChnCtrl->enValidFlag>",
            pstDiccChnCtrl->enValidFlag);
        return DICC_ERR_EXISTED_CHAN_ID;
    }


    return DICC_OK;
}/* DICC_CheckChnInitStatus */

/*****************************************************************************
函 数 名  : DICC_RING_Q_InitAndNodeAddrSet
功能描述  : 初始化环形队列，关联核间共享结点地址到通道结点队列中
输入参数  : pstDiccChnCtrl - 通道管理结构
输出参数  : 无
返 回 值  : 操作成功与否, DICC_OK - 成功, 其它 - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年8月21日
   作    者   : g00178567
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  DICC_RING_Q_InitAndNodeAddrSet(VOS_UINT32 ulPid,
                DICC_CHAN_CTRL_STRU *pstDiccChnCtrl,
                DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    VOS_UINT16                          usNodeLoop = 0;

    /* 指向对通道的ring_queue的指针(ring_queue的ppNode) */
    VOS_VOID                           *pstTtfRingQStAddr = VOS_NULL_PTR;

    /* 通道中ring_queue的指针数组的基址 */
    DICC_QUEUE_NODE_STRU               *pstQueueNodeBaseAddr = VOS_NULL_PTR;

    /* 在计算每个核间数据的首地址时使用到的临时指针 */
    VOS_UINT8                          *pucBaseQueueNodeAddr = VOS_NULL_PTR;

    /* 每个核间数据的首地址 */
    VOS_UINT8                          *pucQueuePerNodeAddr = VOS_NULL_PTR;
    DICC_QUEUE_NODE_STRU               *pstPerNodeAddr = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulChnNodeSize;

    ulChnNodeSize        = sizeof(DICC_QUEUE_NODE_STRU);
    pstTtfRingQStAddr = (VOS_VOID *)DICC_GetTtfRingQStChnAddr(pstDiccChnCtrl->ucChanId, enCpuId);
    pstQueueNodeBaseAddr = (DICC_QUEUE_NODE_STRU *)DICC_GetQueueNodeChnAddr(pstDiccChnCtrl->ucChanId, enCpuId);
    ulRslt = TTF_RING_Q_InitAndNodeAddrSet(ulPid,
                                           &(pstDiccChnCtrl->stRingBuffer),
                                           (VOS_VOID **)pstTtfRingQStAddr,
                                           (VOS_VOID *)pstQueueNodeBaseAddr,
                                           ulChnNodeSize,
                                           (VOS_UINT32)pstDiccChnCtrl->usChnBlkNum);
    if (PS_FAIL == ulRslt)
    {
        DICC_LOG(PS_PRINT_WARNING,
            "[LOCAL CPU_ID: DICC_RING_Q_InitAndNodeAddrSet] TTF_RING_Q_InitAndNodeAddrSet fail");
        return DICC_ERR_RING_QUEUE_FAIL;
    }

    pucBaseQueueNodeAddr = (VOS_UINT8 *)pstQueueNodeBaseAddr;
    for (usNodeLoop = 0; usNodeLoop < pstDiccChnCtrl->usChnBlkNum; usNodeLoop++)
    {
        pucQueuePerNodeAddr = (pucBaseQueueNodeAddr + (ulChnNodeSize * usNodeLoop));

        /* 核间共享结点的地址 */
        pstPerNodeAddr = (DICC_QUEUE_NODE_STRU *)pucQueuePerNodeAddr;

        /* 核间传递结点内存清零 */
        VOS_MemSet(pstPerNodeAddr->aucPriData, 0x0, sizeof(pstPerNodeAddr->aucPriData));

        pstPerNodeAddr->usIndex = usNodeLoop;
        pstPerNodeAddr->usMagicNum = DICC_MAGIC_NUM_VALUE;
    }

    return DICC_OK;
} /* DICC_RING_Q_InitAndNodeAddrSet */

/*****************************************************************************
函 数 名  : DICC_SenderChnInit
功能描述  : 通道发送端初始化
输入参数  : ucChnId - 通道ID
            penChnInfo - 通道基本信息(申请核间信息块数和大小等)
输出参数  : 无
返 回 值  : 操作成功与否, DICC_OK - 成功, 其它 - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年8月12日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_SenderChnInit(VOS_UINT32 ulPid, DICC_CHAN_ID_ENUM_UINT8 ucChnId,
                              DICC_BLK_CHN_INFO_STRU        *penChnInfo,
                              DICC_CHAN_LOCAL_SEM_PAPA_STRU *pstLocalSemPara,
                              DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    volatile DICC_CHAN_CTRL_STRU       *pstDiccChnCtrl;
    VOS_UINT32                          ulSize;
    VOS_UINT32                          ulReturn;


    /* 初始化过程同一核需要互斥, 由外部调用者确保 */

    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);

    /* 通道号 */
    pstDiccChnCtrl->ucChanId               = ucChnId;
    pstDiccChnCtrl->usChnBlkNum            = penChnInfo->usChnBlkNum;
    pstDiccChnCtrl->ucPriDataLen           = (VOS_UINT8)(penChnInfo->usChnBlkSize);
    pstDiccChnCtrl->ulTtfRingQStAddrOffSet = g_astChanRole[enCpuId].pastDICCMgmt->ulCurrSize;

    /* pstDiccChnCtrl->ulQueueNodeAddrOffSet加上通道TFFRINGQST的大小 */
    pstDiccChnCtrl->ulQueueNodeAddrOffSet = pstDiccChnCtrl->ulTtfRingQStAddrOffSet
        + (penChnInfo->usChnBlkNum * sizeof(VOS_VOID *));

    /* 通道申请的总长度 */
    ulSize = (penChnInfo->usChnBlkNum) * (sizeof(DICC_QUEUE_NODE_STRU) + sizeof(VOS_VOID *));

    /* 初始化通道的环形缓存并且关联核间共享结点地址到通道结点队列中 */
    ulReturn = DICC_RING_Q_InitAndNodeAddrSet(ulPid, (DICC_CHAN_CTRL_STRU *)pstDiccChnCtrl, enCpuId);

    if (DICC_OK != ulReturn)
    {
        DICC_LOG(PS_PRINT_WARNING, "[LOCAL CPU_ID: DICC_SenderChnInit] DICC_RING_Q_InitAndNodeAddrSet fail");

        return DICC_ERR_RING_QUEUE_FAIL;
    }

    /* 上自旋锁, 注意自旋锁寄存器的保护, 是通过此函数的调用者tasklock实现的 */
    DICC_SPIN_LOCK();

    /* 通道状态初始化 */
    pstDiccChnCtrl->ucStateMask &= ~DICC_CHAN_SENDER_OPEN_MASK;
    pstDiccChnCtrl->enValidFlag = DICC_CHAN_STATUS_INITIALED;

    /* 更新核间通道控制结构 */
    g_astChanRole[enCpuId].pastDICCMgmt->ulCurrSize += (ulSize);

    /* 解自旋锁 */
    DICC_SPIN_UNLOCK();

    return DICC_OK;
}    /* DICC_SenderChanInit */

/*****************************************************************************
函 数 名  : DICC_ChnIsrInit
功能描述  : DICC用户通道初始化参数检查函数
输入参数  : enServiceType - 服务类别号
            pfuncRecvIsr - 中断服务程序
输出参数  : 无
返 回 值  : 操作成功与否, DICC_OK - 成功, 其它 - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年12月8日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_ChnIsrInit(VOS_UINT32 ulPid, VOS_UINT32 ulIntLevel,
                           VOIDFUNCPTR pfuncRecvIsr, DICC_INT_OP_STRU *pstIntOp)
{
    VOS_INT32  lIntRet;


    /* 挂接中断 */
#ifndef WTTF_PS_FUSION_PC_ST
    lIntRet = mdrv_ipc_int_connect(((IPC_INT_LEV_E)ulIntLevel), ((VOIDFUNCPTR)pfuncRecvIsr), VOS_NULL);
#else
    lIntRet = VHW_IPC_IntConnect(ulPid,((IPC_INT_LEV_E)ulIntLevel), ((VOIDFUNCPTR)pfuncRecvIsr), VOS_NULL);
#endif
    /* 在此将中断操作记录下来 */
    pstIntOp->ulIntLevel = ulIntLevel;
    pstIntOp->lResult = lIntRet;

    if (lIntRet != VOS_OK)
    {
        DICC_LOG1(PS_PRINT_ERROR,
            "[LOCAL CPU_ID: DICC_ChnIsrInit] connect <ulIntLevel> ISR fail",
            (VOS_INT32)ulIntLevel);
        return DICC_ERR_ISR_CONNECT_FAIL;
    }

    /* 使能通知中断 */
    mdrv_ipc_int_enable((IPC_INT_LEV_E)ulIntLevel);

    return DICC_OK;
}    /* DICC_ChnIsrInit */

/*****************************************************************************
函 数 名  : DICC_RecverChnInit
功能描述  : 通道接收端初始化
输入参数  : ulPid - 操作PID
            enServiceType - 服务类别号
            pfuncRecvIsr - 中断服务程序
输出参数  : 无
返 回 值  : 操作成功与否, DICC_OK - 成功, 其它 - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年8月12日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_RecverChnInit(VOS_UINT32                        ulPid,
                              DICC_SERVICE_TYPE_ENUM_UINT8      enServiceType,
                              VOIDFUNCPTR                       pfuncRecvIsr,
                              DICC_INT_OP_STRU                 *pstIntOp,
                              DICC_CHAN_LOCAL_SEM_PAPA_STRU    *pstLocalSemPara,
                              DICC_CPU_ID_ENUM_UINT8            enCpuId)
{
    volatile DICC_CHAN_CTRL_STRU       *pstDiccChnCtrl  = VOS_NULL_PTR;
    DICC_CHAN_ID_ENUM_UINT8             ucChnId         = g_astChanRole[enCpuId].aenRecver[enServiceType];
    VOS_UINT32                          ulReturn;
    VOS_UINT32                          ulIntLevel;

    /* 初始化过程同一核需要互斥, 目前是由外部调用者确保 */

    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);

    /* 通道号 */
    pstDiccChnCtrl->ucChanId = ucChnId;

    /* 上自旋锁, 注意自旋锁寄存器的保护, 是通过此函数的调用者tasklock实现的 */
    DICC_SPIN_LOCK();

    /* 通道状态初始化 */
    pstDiccChnCtrl->ucStateMask &= ~DICC_CHAN_RECVER_OPEN_MASK;

    /* 解自旋锁 */
    DICC_SPIN_UNLOCK();

    if (DICC_SERVICE_TYPE_0 == enServiceType)
    {
        ulIntLevel = DICC_SERVICE_0_INT_LEVEL;
    }
    else
    {
        ulIntLevel = DICC_SERVICE_1_INT_LEVEL;
    }

    ulReturn = DICC_ChnIsrInit(ulPid, ulIntLevel, pfuncRecvIsr, pstIntOp);

    return ulReturn;
}    /* DICC_RecverChanInit */

/*****************************************************************************
函 数 名  : DICC_ChkChnInit
功能描述  : DICC用户通道初始化参数检查函数
输入参数  : enServiceType - 服务类别号
            pstInitChanInfo - 通道的基本信息
输出参数  : 无
返 回 值  : 操作成功与否, DICC_OK - 成功, 其它 - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年12月7日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_ChkChnServiceInfo(DICC_SERVICE_TYPE_ENUM_UINT8 enServiceType,
                           DICC_INIT_CHN_INFO_STRU     *pstInitChanInfo,
                           DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    VOS_UINT32 ulRet;

    if (DICC_SERVICE_TYPE_BUTT <= enServiceType)
    {
        DICC_LOG1(PS_PRINT_WARNING, "[LOCAL CPU_ID: DICC_ChkChnInit] undefined <enServiceType>",
            enServiceType);
        return DICC_ERR_SERVCE_UNDEFINED;
    }

    if (DICC_CHAN_ROLE_SENDER == pstInitChanInfo->enUserRole)
    {
        /* 检查通道是否已经初始化 */
        ulRet = DICC_CheckChnInitStatus(enServiceType, enCpuId);
        if (DICC_OK != ulRet)
        {
            return ulRet;
        }

        /* 检查核间是否还有足够的空间来初始化通道 */
        ulRet = DICC_CheckIsExistEnoughMem(&(pstInitChanInfo->u.stSndInitInfo.stSndChnInfo), enCpuId);
        if (DICC_OK != ulRet)
        {
            return ulRet;
        }
    }
    else if (DICC_CHAN_ROLE_RECVER == pstInitChanInfo->enUserRole)
    {
        if (VOS_NULL_PTR == pstInitChanInfo->u.stRcvInitInfo.pfuncRecvIsr)    /* 中断服务程序为空 */
        {
            DICC_LOG2(PS_PRINT_WARNING,
                "[LOCAL CPU_ID: DICC_ChkChnInit] pfuncRecvIsr is NULL, <enServiceType> <enUserRole>",
                enServiceType, pstInitChanInfo->enUserRole);
            return DICC_ERR_RECV_ISR_NULL;
        }
    }
    else
    {
        DICC_LOG1(PS_PRINT_WARNING, "[LOCAL CPU_ID: DICC_ChkChnInit] undefined enUserRole, <enUserRole>",
            pstInitChanInfo->enUserRole);
        return DICC_ERR_CHAN_ID_NOT_MATCH_ROLE;
    }

    return DICC_OK;
}   /* DICC_ChkChnInit */

/*****************************************************************************
函 数 名  : DICC_Sync
功能描述  : DICC双核共享内存初始化同步
输入参数  : 无
输出参数  : 无
返 回 值  : 操作成功与否, DICC_OK - 成功, 其它 - 失败
调用函数  :
被调函数  :
说    明  : 初始化过程同一核需要互斥
            防止重复创建硬件信号量, 锁中断, 直到整个操作结束,
            否则一旦管理结构没有完成初始化, 被高优先级任务抢走, 判断ucSemCreated为1,
            离开此函数, 实际上此时并没有完成sync的初始化

修改历史      :
 1.日    期   : 2011年10月20日
   作    者   : wangrong
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_Sync(VOS_UINT32 ulFileId, VOS_UINT32 ulLineNum, VOS_UINT32 ulPid,
               DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    volatile VOS_UINT32                *pulDiccMagicAddr;
    DICC_CHAN_SYNC_PARA_STRU            stSyncPara;
    volatile VOS_UINT8                 *pucStartAddr;
    DICC_SOFT_REBOOT_INFO_STRU          stRebootInfo     = {0};


    VOS_MemSet((VOID *)&stSyncPara, 0x00, sizeof(DICC_CHAN_SYNC_PARA_STRU));

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_SYNC, __LINE__, DICC_TRACE_OK);

#if (VOS_WIN32 != VOS_OS_VER)
    if (DICC_CPU_ID_CCPU == enCpuId)
    {
        pulDiccMagicAddr = (VOS_UINT32 *)(DICC_MEM_INIT_MAGIC_NUM_ADDR);

        pucStartAddr = (VOS_UINT8 *)DICC_TTF_PHY_TO_VIRT(DICC_MEM_START_PHY_ADDR);
    }
    else
    {
        /* 注意DICC_MEM_INIT_MAGIC_NUM_ADDR不在底软保留地址中, 需要调用Linux IO_ADDRESS进行地址转换 */
        pulDiccMagicAddr = (VOS_UINT32 *)DICC_DRV_PHY_TO_VIRT(DICC_MEM_INIT_MAGIC_NUM_ADDR);

        pucStartAddr = (VOS_UINT8 *)DICC_TTF_PHY_TO_VIRT(DICC_MEM_START_PHY_ADDR);
    }
#else
    pulDiccMagicAddr = (VOS_UINT32 *)DICC_DRV_PHY_TO_VIRT(DICC_MEM_INIT_MAGIC_NUM_ADDR);
    pucStartAddr = (VOS_UINT8 *)DICC_TTF_PHY_TO_VIRT(DICC_MEM_START_PHY_ADDR);
#endif

    if (1 == g_astChanRole[enCpuId].ucSemCreated)    /* 本CPU已创建硬件信号量 */
    {
        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_SYNC, __LINE__, DICC_TRACE_OK);

        return DICC_OK;    /* 防止重复创建 */
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_SYNC, __LINE__, DICC_TRACE_OK);

    /* 创建用于两核同步DICC内存清零的硬件信号量 */
    mdrv_ipc_sem_creat(IPC_SEM_DICC);

    g_astChanRole[enCpuId].ucSemCreated = 1;    /* 已经创建硬件信号量 */

    /* 获取硬件信号量, 它的寄存器保护是通过外部调用者用tasklock保护的 */
    stSyncPara.stHwSemPara.ulSingnalNum = IPC_SEM_DICC;
    stSyncPara.stHwSemPara.lTimeout     = 0;
    stSyncPara.stHwSemPara.lResult      = mdrv_ipc_sem_take(IPC_SEM_DICC, 0);
    if (BSP_OK != stSyncPara.stHwSemPara.lResult)
    {
        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_SYNC, __LINE__, DICC_ERR_USE_HW_SEMPHORE_FAIL);

        SET_DICC_SOFT_REBOOT_INFO((&stRebootInfo), TTF_SOFT_REBOOT_MODULE_ID_DICC_MEM_CLEAN_SYNC_FAIL,
            ulFileId, ulLineNum, (&stSyncPara), sizeof(stSyncPara));
        DICC_DealWithFatalError(&stRebootInfo);

        DICC_LOG2(PS_PRINT_ERROR, "[<LOCAL CPU_ID>: DICC_Sync] <SignalNum> <timeout>",
            IPC_SEM_DICC, 0);

        return DICC_ERR_USE_HW_SEMPHORE_FAIL;
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_SYNC, __LINE__, DICC_TRACE_OK);

    /* take到信号量后，需要检查魔术字，如果没有设置，则可以进行内存清0 */
    if (0 == (*pulDiccMagicAddr))
    {
        DICC_LOG1(PS_PRINT_INFO, "[<LOCAL CPU_ID>: DICC_Sync] <DICC MAGIC NUM> ",
            (VOS_INT32)(*pulDiccMagicAddr));

        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_SYNC, __LINE__, DICC_TRACE_OK);

        VOS_MemSet((VOID *)pucStartAddr, 0x00, DICC_QUEUE_MEM_SIZE);

        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_SYNC, __LINE__, DICC_TRACE_OK);

        *pulDiccMagicAddr = DICC_MEM_INIT_MAGIC_NUM;
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_SYNC, __LINE__, DICC_TRACE_OK);

    stSyncPara.ulDiccMagic = (*pulDiccMagicAddr);

    /* 防止出现MAGIC-NUM因AXI内存上电没有清零而残留或者被篡改 */
    if (DICC_MEM_INIT_MAGIC_NUM != stSyncPara.ulDiccMagic)
    {
        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_SYNC, __LINE__, DICC_ERR_MAGIC_MEM_TEMPERED);

        SET_DICC_SOFT_REBOOT_INFO((&stRebootInfo), TTF_SOFT_REBOOT_MODULE_ID_DICC_MEM_CLEAN_SYNC_FAIL,
            ulFileId, ulLineNum, (&stSyncPara), sizeof(stSyncPara));
        DICC_DealWithFatalError(&stRebootInfo);

        DICC_LOG1(PS_PRINT_ERROR, "[<LOCAL CPU_ID>: DICC_Sync] <ulDiccMagic> tempered",
            (VOS_INT)stSyncPara.ulDiccMagic);

        /* 释放硬件信号量 */
        mdrv_ipc_sem_give(IPC_SEM_DICC);

        return DICC_ERR_MAGIC_MEM_TEMPERED;
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_SYNC, __LINE__, DICC_TRACE_OK);

    /* 初始化通道管理结构的全局变量首地址 */
    g_astChanRole[enCpuId].pastDICCMgmt = (DICC_CTRL_STRU *)pucStartAddr;
    DEBUG_PRINT("DICC_MemInit Succ! virtual: 0x%0x\n", (int)(g_astChanRole[enCpuId].pastDICCMgmt));

    /* 初始化通道控制结构的变量, 仅由一核将DICC控制内存大小记录上去
       另一核可能因此更新过CurrSize, 比如已经将某些通道init了, 此时本核才执行到这里,
       因此需要判断是否为0, 即没有记录过 */
    if (0 == g_astChanRole[enCpuId].pastDICCMgmt->ulCurrSize)
    {
        g_astChanRole[enCpuId].pastDICCMgmt->ulCurrSize = sizeof(DICC_CTRL_STRU) + (DICC_MAX_CHAN_NUM * sizeof(DICC_CHAN_CTRL_STRU));
    }

#if (1 == DICC_DFX_SWITCH)
    g_astChanRole[enCpuId].pastDICCMgmt->stDFx.enDFxEnabled = PS_TRUE;
#else
    g_astChanRole[enCpuId].pastDICCMgmt->stDFx.enDFxEnabled = PS_FALSE;
#endif

    /* 释放硬件信号量 */
    mdrv_ipc_sem_give(IPC_SEM_DICC);

    return DICC_OK;
}

/*****************************************************************************
函 数 名  : DICC_SingleChnInit
功能描述  : DICC用户单通道初始化API(按照服务类别初始化一个通道)
输入参数  : ulPid - 调用此接口的PID
            enServiceType - 服务类别号
            pstInitChanInfo - 要初始化的通道的具体参数
输出参数  : 无
返 回 值  : 操作成功与否, DICC_OK - 成功, 其它 - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年11月28日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_SingleChnInitAction(VOS_UINT32             ulFileId,
                              VOS_UINT32                   ulLineNum,
                              VOS_UINT32                   ulPid,
                              DICC_SERVICE_TYPE_ENUM_UINT8 enServiceType,
                              DICC_INIT_CHN_INFO_STRU     *pstInitChanInfo,
                              DICC_CPU_ID_ENUM_UINT8       enCpuId)
{
    VOS_UINT32                          ulRet;
    DICC_CHAN_SINGLE_INIT_CONTENT_STRU  stInitChanInfo     = {0};
    DICC_SOFT_REBOOT_INFO_STRU          stRebootInfo       = {0};

    ulRet = DICC_CheckCpuId(enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    /* 注意在此之前, 无法确认enCpuId是否正常, 直接入数组下标可能会出现问题, 故不能调用TRACE */
    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_SINGLE_CHAN_INIT, __LINE__, DICC_TRACE_OK);

    if (VOS_NULL_PTR == pstInitChanInfo)
    {
        DICC_LOG(PS_PRINT_WARNING,
            "[LOCAL CPU_ID: DICC_ChkChnInit] pstSndInitChanInfo is NULL");

        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_SINGLE_CHAN_INIT, __LINE__, DICC_ERR_INFO_PTR_NULL);
        return DICC_ERR_INFO_PTR_NULL;
    }

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    /* 高优先级任务抢占时，可能会出现重复初始化g_stDiccSpinLock的情况 */
    if( DICC_MUTEX_SEM_NOT_CREATE == g_ulDiccMultiCoreFlag )
    {
        spin_lock_init(&g_stDiccSpinLock);
    }

    spin_lock(&g_stDiccSpinLock);
#else
    VOS_TaskLock();
#endif

    if( DICC_MUTEX_SEM_NOT_CREATE == g_ulDiccMultiCoreFlag )
    {
        /* 创建本地互斥信号量(第一个参数只允许4字节, DICC Local Mutex, 缩写为DLM) */
        ulRet = VOS_SmMCreate("DLM", VOS_SEMA4_FIFO,
                (VOS_SEM *)(&(g_astChanRole[enCpuId].ulDiccLocalMutexSem)));

        if (VOS_OK != ulRet)
        {
            SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
                ID_DICC_TRACE_FUNC_MARK_SYNC, __LINE__, DICC_ERR_LOCAL_SEMPHORE_FAIL);

            DICC_DealWithFatalError(&stRebootInfo);

            DICC_LOG(PS_PRINT_ERROR, "[<LOCAL CPU_ID>: DICC_SingleChnInitAction] Create g_ulDiccLocalMutexSem fail ");

            return DICC_ERR_LOCAL_SEMPHORE_FAIL;
        }

        g_ulDiccMultiCoreFlag   = DICC_MUTEX_SEM_CREATED;
    }

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    spin_unlock(&g_stDiccSpinLock);
#else
    VOS_TaskUnlock();
#endif

    ulRet = VOS_SmP(g_astChanRole[enCpuId].ulDiccLocalMutexSem, 0);
    if (VOS_OK != ulRet)
    {
        DICC_LOG1(PS_PRINT_ERROR,
            "[<LOCAL CPU_ID>: DICC_SingleChnInitAction] take ulDiccLocalMutexSem fail, <ulSemRslt>",
            (VOS_INT32)(ulRet));

        return DICC_ERR_LOCAL_SEMPHORE_FAIL;
    }

    /* 进行DICC控制结构内存清零操作同步 */
    ulRet = DICC_Sync(ulFileId, ulLineNum, ulPid, enCpuId);
    if (DICC_OK != ulRet)
    {
        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_SINGLE_CHAN_INIT, __LINE__, ulRet);

        VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

        return ulRet;
    }

    /* 在此将用户参数记录下来 */
    stInitChanInfo.enServiceType = enServiceType;
    VOS_MemCpy(&(stInitChanInfo.stInitPara),
               pstInitChanInfo, sizeof(stInitChanInfo.stInitPara));

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_SINGLE_CHAN_INIT, __LINE__, DICC_TRACE_OK);

    ulRet = DICC_ChkChnServiceInfo(enServiceType, pstInitChanInfo, enCpuId);
    if (DICC_OK != ulRet)
    {
        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_SINGLE_CHAN_INIT, __LINE__, ulRet);

        SET_DICC_SOFT_REBOOT_INFO((&stRebootInfo), TTF_SOFT_REBOOT_MODULE_ID_DICC_CHAN_INIT_FAIL,
            ulFileId, ulLineNum, (&stInitChanInfo), sizeof(stInitChanInfo));
        DICC_DealWithFatalError(&stRebootInfo);

        VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

        return ulRet;
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_SINGLE_CHAN_INIT, __LINE__, DICC_TRACE_OK);

    if (DICC_CHAN_ROLE_SENDER == pstInitChanInfo->enUserRole)
    {
        ulRet = DICC_SenderChnInit(ulPid, g_astChanRole[enCpuId].aenSender[enServiceType],
                                   &(pstInitChanInfo->u.stSndInitInfo.stSndChnInfo),
                                   &(stInitChanInfo.stLocalSemPara), enCpuId);
        if (DICC_OK != ulRet)
        {
            SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
                ID_DICC_TRACE_FUNC_MARK_SINGLE_CHAN_INIT, __LINE__, ulRet);

            SET_DICC_SOFT_REBOOT_INFO((&stRebootInfo), TTF_SOFT_REBOOT_MODULE_ID_DICC_CHAN_INIT_FAIL,
                ulFileId, ulLineNum, (&stInitChanInfo), sizeof(stInitChanInfo));
            DICC_DealWithFatalError(&stRebootInfo);

            VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

            return ulRet;
        }
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_SINGLE_CHAN_INIT, __LINE__, DICC_TRACE_OK);

    if (DICC_CHAN_ROLE_RECVER == pstInitChanInfo->enUserRole)
    {
/*lint -e64*/
        ulRet = DICC_RecverChnInit(ulPid, enServiceType,
                                   (VOIDFUNCPTR)(pstInitChanInfo->u.stRcvInitInfo.pfuncRecvIsr),
                                   &(stInitChanInfo.stIntOp),
                                   &(stInitChanInfo.stLocalSemPara), enCpuId);
/*lint +e64*/
        if (DICC_OK != ulRet)
        {
            SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
                ID_DICC_TRACE_FUNC_MARK_SINGLE_CHAN_INIT, __LINE__, ulRet);

            SET_DICC_SOFT_REBOOT_INFO((&stRebootInfo), TTF_SOFT_REBOOT_MODULE_ID_DICC_CHAN_INIT_FAIL,
                ulFileId, ulLineNum, (&stInitChanInfo), sizeof(stInitChanInfo));
            DICC_DealWithFatalError(&stRebootInfo);

            VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

            return ulRet;
        }
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_SINGLE_CHAN_INIT, __LINE__, DICC_TRACE_OK);

    VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

    return DICC_OK;
}    /* DICC_SingleChnInit */

/*****************************************************************************
函 数 名  : DICC_OpenChannelByRole
功能描述  : 按照角色打开核间通信通道
输入参数  : ucChanId - 通道ID
            enUserRole - 在当前CPU上本端在通道上扮演的角色
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年8月11日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_OpenChannelByRole(DICC_CHAN_ID_ENUM_UINT8      ucChnId,
                                DICC_CHAN_ROLE_ENUM_UINT8      enUserRole,
                                VOS_UINT32                     ulPid,
                                DICC_CHAN_LOCAL_SEM_PAPA_STRU *pstLocalSemPara,
                                DICC_CPU_ID_ENUM_UINT8         enCpuId)
{
    volatile DICC_CHAN_CTRL_STRU   *pstDiccChnCtrl = VOS_NULL_PTR;
    VOS_UINT8                       ucStateMask    = DICC_CHAN_BOTH_CLOSE_MASK;

    if (DICC_CHAN_ROLE_SENDER == enUserRole)
    {
        ucStateMask = DICC_CHAN_SENDER_OPEN_MASK;
    }

    if (DICC_CHAN_ROLE_RECVER == enUserRole)
    {
        ucStateMask = DICC_CHAN_RECVER_OPEN_MASK;
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_OPEN, __LINE__, DICC_TRACE_OK);

    /* 任务抢占的问题, 由本地互斥信号量来保护自旋锁 */
    pstLocalSemPara->ulResult = VOS_SmP(g_astChanRole[enCpuId].ulDiccLocalMutexSem, 0);
    if (VOS_OK != pstLocalSemPara->ulResult)
    {
        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_OPEN, __LINE__, DICC_ERR_LOCAL_SEMPHORE_FAIL);

        DICC_LOG1(PS_PRINT_ERROR,
            "[<LOCAL CPU_ID>: DICC_OpenChannelByRole] take g_ulDiccLocalMutexSem fail, <ulSemRslt>",
            (VOS_INT32)(pstLocalSemPara->ulResult));

        return DICC_ERR_LOCAL_SEMPHORE_FAIL;
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_OPEN, __LINE__, DICC_TRACE_OK);

    /* 上自旋锁 */
    DICC_SPIN_LOCK();

    /* 根据通道号查找到核间数据管理控制结构 */
    pstDiccChnCtrl               = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);
    pstDiccChnCtrl->ucStateMask |= ucStateMask;

    /* 解自旋锁 */
    DICC_SPIN_UNLOCK();

    /* 释放信号量 */
    VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_OPEN, __LINE__, DICC_TRACE_OK);

    DEBUG_PRINT("DICC_OpenChannelByRole chan-id = %d, pstDiccChnCtrl->ucStateMask = %d\n",
                ucChnId, pstDiccChnCtrl->ucStateMask);

    return DICC_OK;
}    /* DICC_SenderOpenChannel */

/*****************************************************************************
函 数 名  : DICC_CheckChanOpPara
功能描述  : 检查通道操作的基本参数
输入参数  : ucChanId - 通道ID
输出参数  : 无
返 回 值  : 检查合法与否, DICC_OK - 合法, 其它 - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年12月15日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_CheckChanOpPara(DICC_CHAN_ID_ENUM_UINT8 ucChnId,
               DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    if (VOS_NULL_PTR == g_astChanRole[enCpuId].pastDICCMgmt)
    {
        DICC_LOG(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckChanOpPara] get g_pastDICCMgmt NULL ");
        return DICC_ERR_CHAN_NOT_READY;
    }

    if (DICC_CHAN_ID_BUTT <= ucChnId)
    {
        DICC_LOG1(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckChanOpPara] undefined <ucChnId> ",
            ucChnId);
        return DICC_ERR_INVALID_CHAN_ID;
    }

    /* 不检查pstDiccChnCtrl->ucValidFlag, 防止外部使用者异常时, 检查过严 */

    return DICC_OK;
}    /* DICC_CheckChanOpPara */

/*****************************************************************************
函 数 名  : DICC_CheckOpenPara
功能描述  : 检查通道操作的参数
输入参数  : ucChanId - 通道ID
            enUserRole - 在当前CPU上本端在通道上扮演的角色
输出参数  : 无
返 回 值  : 检查合法与否, DICC_OK - 合法, 其它 - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年12月15日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_CheckOpenPara(DICC_CHAN_ID_ENUM_UINT8   ucChnId,
                              DICC_CHAN_ROLE_ENUM_UINT8 enUserRole,
                              VOS_UINT32                ulPid,
                              DICC_CPU_ID_ENUM_UINT8    enCpuId)
{
    DICC_CHAN_ID_ENUM_UINT8      *penRole     = VOS_NULL_PTR;
    volatile DICC_CHAN_CTRL_STRU *pstDiccChnCtrl;
    VOS_UINT8                     ucStateMask = DICC_CHAN_BOTH_CLOSE_MASK;
    VOS_UINT32                    ulRet;

    ulRet = DICC_CheckChanOpPara(ucChnId, enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    if (DICC_CHAN_ROLE_SENDER == enUserRole)
    {
        penRole = (DICC_CHAN_ID_ENUM_UINT8 *)g_astChanRole[enCpuId].aenSender;
        ucStateMask |= DICC_CHAN_SENDER_OPEN_MASK;
    }
    else if (DICC_CHAN_ROLE_RECVER == enUserRole)
    {
        penRole = (DICC_CHAN_ID_ENUM_UINT8 *)g_astChanRole[enCpuId].aenRecver;
        ucStateMask |= DICC_CHAN_RECVER_OPEN_MASK;
    }
    else
    {
        return DICC_ERR_CHAN_ID_NOT_MATCH_ROLE;
    }

    if ((ucChnId != penRole[DICC_SERVICE_TYPE_0]) && (ucChnId != penRole[DICC_SERVICE_TYPE_1]))
    {
        DICC_LOG2(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckOpenPara] <ucChnId> <enUserRole> not match ",
            ucChnId, enUserRole);
        return DICC_ERR_CHAN_ID_NOT_MATCH_ROLE;
    }

    DEBUG_PRINT("DICC_OpenChannel enUserRole=%d, ucChnId=%d, penRole[DICC_SERVICE_TYPE_0]=%d, penRole[DICC_SERVICE_TYPE_1]=%d\n",
                enUserRole, ucChnId, penRole[DICC_SERVICE_TYPE_0], penRole[DICC_SERVICE_TYPE_1]);

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_OPEN, __LINE__, DICC_TRACE_OK);

    /* 根据通道号查找到核间数据管理控制结构  */
    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);

    /* 判断本端是否已经打开 */
    if (ucStateMask == (ucStateMask & pstDiccChnCtrl->ucStateMask))
    {
        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_OPEN, __LINE__, DICC_ERR_CHAN_ALREADY_OPENED);

        DICC_LOG1(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckOpenPara] <ucChnId> already opened ",
            ucChnId);
        return DICC_ERR_CHAN_ALREADY_OPENED;
    }

    return DICC_OK;
}    /* DICC_CheckOpenPara */

/*****************************************************************************
函 数 名  : DICC_OpenChannel
功能描述  : 打开核间通信通道API
输入参数  : ulPid - 调用此接口的PID
            ucChanId - 通道ID
            enUserRole - 在当前CPU上本端在通道上扮演的角色
输出参数  : 无
返 回 值  : 操作成功与否, VOS_OK - 成功, VOS_ERR - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年8月11日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_OpenChannel(VOS_UINT32 ulPid, DICC_CHAN_ID_ENUM_UINT8 ucChnId,
                            DICC_CHAN_ROLE_ENUM_UINT8 enUserRole,
                            DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    VOS_UINT32                          ulRet;
    DICC_CHAN_OPEN_PAPA_STRU            stOpenPara = {0};


    ulRet = DICC_CheckCpuId(enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    /* 注意在此之前, 无法确认enCpuId是否正常, 直接入数组下标可能会出现问题, 故不能调用TRACE */
    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_OPEN, __LINE__, DICC_TRACE_OK);

    ulRet = DICC_CheckOpenPara(ucChnId, enUserRole, ulPid, enCpuId);

    /* 保存参数 */
    stOpenPara.ucChnId    = ucChnId;
    stOpenPara.enUserRole = enUserRole;

    if (DICC_OK != ulRet)
    {
        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_OPEN, __LINE__, ulRet);

        return ulRet;
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_OPEN, __LINE__, DICC_TRACE_OK);

    ulRet = DICC_OpenChannelByRole(ucChnId, enUserRole, ulPid,
                &(stOpenPara.stLocalSemPara), enCpuId);

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_OPEN, __LINE__, ulRet);

    return ulRet;
}    /* DICC_SenderOpenChannel */

/*****************************************************************************
函 数 名  : DICC_CloseChannel
功能描述  : 关闭核间通信通道API
输入参数  : ulPid - 调用此接口的PID
            ucChanId - 通道ID
输出参数  : 无
返 回 值  : 操作成功与否, VOS_OK - 成功, VOS_ERR - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年8月11日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_CloseChannel(VOS_UINT32 ulPid, DICC_CHAN_ID_ENUM_UINT8 ucChnId,
               DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    volatile DICC_CHAN_CTRL_STRU       *pstDiccChnCtrl = VOS_NULL_PTR;
    DICC_CHAN_ROLE_ENUM_UINT8           enUserRole = DICC_CHAN_ROLE_BUTT;
    VOS_UINT32                          ulRet;
    DICC_CHAN_CLOSE_PAPA_STRU           stClosePara = {0};
    VOS_UINT32                          ulCnt;
    DICC_CHAN_CLOSE_FLUSH_EVENT_STRU    stEvent;
    PS_BOOL_ENUM_UINT8                  enFlushData = PS_FALSE;

    /* 保存参数 */
    stClosePara.ucChnId = ucChnId;

    ulRet = DICC_CheckCpuId(enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    /* 注意在此之前, 无法确认enCpuId是否正常, 直接入数组下标可能会出现问题, 故不能调用TRACE */
    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_CLOSE, __LINE__, DICC_TRACE_OK);

    ulRet = DICC_CheckChanOpPara(ucChnId, enCpuId);

    if (DICC_OK != ulRet)
    {
        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_CLOSE, __LINE__, ulRet);

        return ulRet;
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_CLOSE, __LINE__, DICC_TRACE_OK);

    /* 根据通道号查找到核间数据管理控制结构 */
    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);
    enUserRole = g_astChanRole[enCpuId].aenRole[ucChnId];

    /* 任务抢占的问题, 由本地互斥信号量来保护自旋锁 */
    stClosePara.stLocalSemPara.ulResult = VOS_SmP(g_astChanRole[enCpuId].ulDiccLocalMutexSem, 0);
    if (VOS_OK != stClosePara.stLocalSemPara.ulResult)
    {
        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_CLOSE, __LINE__, DICC_ERR_LOCAL_SEMPHORE_FAIL);

        DICC_LOG1(PS_PRINT_ERROR,
            "[<LOCAL CPU_ID>: DICC_CloseChannel] take g_ulDiccLocalMutexSem fail, <ulSemRslt>",
            (VOS_INT32)(stClosePara.stLocalSemPara.ulResult));

        return DICC_ERR_LOCAL_SEMPHORE_FAIL;
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_CLOSE, __LINE__, DICC_TRACE_OK);

    /* 上自旋锁 */
    DICC_SPIN_LOCK();

    if (DICC_CHAN_ROLE_SENDER == enUserRole)
    {
        /* 设置本端为关闭状态 */
        pstDiccChnCtrl->ucStateMask &= ~DICC_CHAN_SENDER_OPEN_MASK;
    }

    if (DICC_CHAN_ROLE_RECVER == enUserRole)
    {
        if (DICC_CHAN_SENDER_OPEN_MASK == (DICC_CHAN_SENDER_OPEN_MASK & pstDiccChnCtrl->ucStateMask))
        {
            /* 解自旋锁 */
            DICC_SPIN_UNLOCK();

            /* 释放信号量 */
            VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

            SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
                ID_DICC_TRACE_FUNC_MARK_CLOSE, __LINE__, DICC_ERR_CLOSE_BEFORE_SENDER_CLOSED);

            DICC_LOG2(PS_PRINT_WARNING,
                "[<LOCAL CPU_ID>: DICC_CloseChannel] receiver close channel before sender ",
            enCpuId, (VOS_INT32)(stClosePara.stLocalSemPara.ulResult));

            return DICC_ERR_CLOSE_BEFORE_SENDER_CLOSED;
        }

        /* 设置本端为关闭状态 */
        pstDiccChnCtrl->ucStateMask &= ~DICC_CHAN_RECVER_OPEN_MASK;
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_CLOSE, __LINE__, DICC_TRACE_OK);

    ulCnt = 0;
    /* 通道状态为两端关闭 */
    if (DICC_CHAN_BOTH_CLOSE_MASK == pstDiccChnCtrl->ucStateMask)
    {
        ulCnt = DICC_GetChannelCurrDataCnt(ulPid, ucChnId, enCpuId);
        if ((0 < ulCnt) && (DICC_INVALID_VALUE != ulCnt))
        {
            enFlushData = PS_TRUE;
        }
        /* 将首尾指针归零 */
        TTF_RING_Q_Flush(ulPid, (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));
    }

    /* 解自旋锁 */
    DICC_SPIN_UNLOCK();

    /* 释放信号量 */
    VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_CLOSE, __LINE__, DICC_TRACE_OK);

    if (PS_TRUE == enFlushData)
    {
        stEvent.ulOpPid    = ulPid;
        stEvent.ucFlushCnt = (VOS_UINT8)ulCnt;
        stEvent.ucChnId    = ucChnId;
        DICC_SndEvent(ID_DICC_MNTN_CLOSE_FLUSH_EVENT, &stEvent, sizeof(stEvent), enCpuId);
    }

    DEBUG_PRINT("DICC_CloseChannel MASK State : %d", pstDiccChnCtrl->ucStateMask );

    return DICC_OK;
}    /* DICC_CloseChannel */

/*****************************************************************************
函 数 名  : DICC_CheckTrigPara
功能描述  : 检查触发核间中断操作的参数
输入参数  : ucChanId - 通道ID
输出参数  : 无
返 回 值  : 检查合法与否, DICC_OK - 合法, 其它 - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年12月15日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_CheckTrigPara(DICC_CHAN_ID_ENUM_UINT8 ucChnId,
                              DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    VOS_UINT32 ulRet;

    ulRet = DICC_CheckChanOpPara(ucChnId, enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    if ((ucChnId != g_astChanRole[enCpuId].aenSender[DICC_SERVICE_TYPE_0])
        && (ucChnId != g_astChanRole[enCpuId].aenSender[DICC_SERVICE_TYPE_1]))
    {
        DICC_LOG2(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckTrigPara] <ucChnId> <enUserRole> not match ",
            ucChnId, DICC_CHAN_ROLE_SENDER);
        return DICC_ERR_CHAN_ID_NOT_MATCH_ROLE;
    }

    return DICC_OK;
}    /* DICC_CheckTrigPara */

/*****************************************************************************
函 数 名  : DICC_TriggerChanDataTx
功能描述  : 触发核间通信中断API
            触发核间通信中断, 以知会对端接收传递的信息
输入参数  : ulPid  - 调用此接口的PID
            ucChanId - 通道ID
输出参数  : 无
返 回 值  : 操作成功与否, VOS_OK - 成功, VOS_ERR - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年12月15日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_TriggerChanDataTx(VOS_UINT32 ulPid,
               DICC_CHAN_ID_ENUM_UINT8 ucChnId, DICC_CPU_ID_ENUM_UINT8 enCurrCpuId)
{
    VOS_UINT32                     ulDiccIsrIntLev;
    VOS_INT32                      lIsrRet;    /* 中断操作返回值 */
#if (1 == DICC_DFX_SWITCH)
    DICC_DFX_STRU                 *pstDFx;
#endif
    VOS_UINT32                     ulRet;
    IPC_INT_CORE_E                 enDstCore;

    ulRet = DICC_CheckCpuId(enCurrCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    ulRet = DICC_CheckTrigPara(ucChnId, enCurrCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    /* 根据通道ID获取核间通信中断号 */
    if (ucChnId == g_astChanRole[enCurrCpuId].aenSender[DICC_SERVICE_TYPE_0])
    {
        ulDiccIsrIntLev = DICC_SERVICE_0_INT_LEVEL;
    }
    else
    {
        ulDiccIsrIntLev = DICC_SERVICE_1_INT_LEVEL;
    }

#if (1 == DICC_DFX_SWITCH)
    /* 触发中断次数++ */
    pstDFx = DICC_GET_CHAN_DFX(g_astChanRole[enCurrCpuId].pastDICCMgmt);
    (pstDFx->astChanStatus[ucChnId].stStatistics.ulTrigIsrCnt)++;
    pstDFx->astChanStatus[ucChnId].stStatistics.ulTrigIsrPid = ulPid;
    pstDFx->astChanStatus[ucChnId].stStatistics.ulLastTrigIsrTime = mdrv_timer_get_normal_timestamp();
#endif

#ifndef WTTF_PS_FUSION_PC_ST
    /* 触发核间数据传递中断通知对方CPU */
    if (DICC_CPU_ID_CCPU == enCurrCpuId)
    {
        enDstCore = IPC_CORE_APPARM;
        lIsrRet = mdrv_ipc_int_send(enDstCore, (IPC_INT_LEV_E)ulDiccIsrIntLev);
    }
    else
    {
        enDstCore = IPC_CORE_COMARM;
        lIsrRet = mdrv_ipc_int_send(enDstCore, (IPC_INT_LEV_E)ulDiccIsrIntLev);
    }
#else
    if (DICC_CPU_ID_CCPU == enCurrCpuId)
    {
        enDstCore = IPC_CORE_APPARM;
        lIsrRet = VHW_IPC_IntSend(enDstCore, (IPC_INT_LEV_E)ulDiccIsrIntLev);
    }
    else
    {
        enDstCore = IPC_CORE_COMARM;
        lIsrRet = VHW_IPC_IntSend(enDstCore, (IPC_INT_LEV_E)ulDiccIsrIntLev);
    }
#endif

    if (lIsrRet != VOS_OK)
    {
        DICC_LOG3(PS_PRINT_ERROR,
            "[<LOCAL CPU_ID>: DICC_TriggerChanDataTx] <ucChnId> <enDstCore> <ulDiccIsrIntLev> trigger Isr fail ",
            ucChnId, enDstCore, (VOS_INT32)ulDiccIsrIntLev);

        return DICC_ERR_TRIG_ISR_FAIL;
    }

    return DICC_OK;
}    /* DICC_TriggerChanDataTx */

/*****************************************************************************
函 数 名  : DICC_TimeDiff
功能描述  : 计算两个时刻的时间差
输入参数  : ulTimeStart  - 起始时刻
            ulTimeEnd - 结束时刻
输出参数  : 无
返 回 值  : 时间差
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年12月14日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_TimeDiff(VOS_UINT32 ulTimeStart, VOS_UINT32 ulTimeEnd)
{
    VOS_UINT32 ulTimeDiff;

    if (ulTimeEnd < ulTimeStart)
    {
        ulTimeDiff = ulTimeStart - ulTimeEnd;
    }
    else
    {
        /* 将时戳间计算分为两部分: 0xFFFFFFFF和ulTimeEnd之间, ulTimeStart和0之间
           前者为(PS_NULL_UINT32 - ulTimeEnd + 1) 加1的原因:slice=PS_NULL_UINT32本身也需要计数,
           后者为(ulCurrTime - 0 ) slice=0已经计算在内 */
        ulTimeDiff = (PS_NULL_UINT32 - ulTimeEnd + 1) + ( ulTimeStart - 0);
    }

    return ulTimeDiff;
}    /* DICC_TimeDiff */
#if 0
/*****************************************************************************
函 数 名  : DICC_ChanStayInFullState
功能描述  : 队列数据满处理
输入参数  : ulPid - 调用此接口的PID
            pstDiccChnCtrl - 通道的控制数据结构起始地址
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年12月14日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DICC_ChanStayInFullState(VOS_UINT32 ulFileId, VOS_UINT32 ulLineNum,
                                  VOS_UINT32 ulPid,
                                  volatile DICC_CHAN_CTRL_STRU *pstDiccChnCtrl,
                                  DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    VOS_UINT8                    ucTraceBlkCnt;
    VOS_UINT32                   ulTraceBlkLoop;
    DICC_QUEUE_NODE_STRU        *pstQueueNode;
    DICC_DFX_STRU               *pstDFx;
    DICC_TRACE_QUEUE_STRU       *pstTraceQueue;
    DICC_TRACE_QUEUE_DATA_STRU  *pstQueueData;
    DICC_CHAN_EXECPTION_STRU    *pstDiccExcp;

    pstDiccExcp = VOS_MemAlloc(ulPid, (STATIC_MEM_PT), sizeof(DICC_CHAN_EXECPTION_STRU));

    if (VOS_NULL_PTR != pstDiccExcp)
    {
        pstTraceQueue = &(pstDiccExcp->stTraceQueue);
        pstTraceQueue->ucChanId = pstDiccChnCtrl->ucChanId;
        ucTraceBlkCnt = (VOS_UINT8)TTF_MIN(pstDiccChnCtrl->usChnBlkNum, DICC_MAX_TRACE_QUEUE_DATA_CNT);
        pstTraceQueue->ucDataCnt = ucTraceBlkCnt;

        /* 将通道中最前面的10块数据搜集起来 */
        for (ulTraceBlkLoop = 0; ulTraceBlkLoop < ucTraceBlkCnt; ulTraceBlkLoop++)
        {
            pstQueueNode = (DICC_QUEUE_NODE_STRU*)TTF_RING_Q_Out(ulPid,
                                                                 (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));
            pstQueueData = &(pstTraceQueue->astQueueData[ulTraceBlkLoop]);
            pstQueueData->ulInsertTime = pstQueueNode->ulInsertTime;
            pstQueueData->ucPriDataLen = pstQueueNode->ucPriDataLen;
            VOS_MemCpy(pstQueueData->aucPriData, pstQueueNode->aucPriData, pstQueueNode->ucPriDataLen);
        }

        /* 将出错的通道的状态信息带上 */
        pstDFx = DICC_GET_CHAN_DFX(g_astChanRole[enCpuId].pastDICCMgmt);
        VOS_MemCpy(&(pstDiccExcp->stIsrDbg), &(pstDFx->stIsrDbg), sizeof(pstDiccExcp->stIsrDbg));
        VOS_MemCpy(&(pstDiccExcp->stChanStatus), &(pstDFx->astChanStatus[pstTraceQueue->ucChanId]),
                   sizeof(pstDiccExcp->stChanStatus));

        /* 调用OM API进行单板复位 */
        VOS_ProtectionReboot(TTF_SOFT_REBOOT_MODULE_ID_DICC_CHAN_ALWAYS_FULL,
            (VOS_INT)ulFileId, (VOS_INT)ulLineNum, (VOS_CHAR *)(pstDiccExcp),
            sizeof(DICC_CHAN_EXECPTION_STRU) );

        VOS_MemFree(ulPid, pstDiccExcp);
    }

    return;
}    /* DICC_ChanStayInFullState */
#endif
/*****************************************************************************
函 数 名  : DICC_CheckInsertPara
功能描述  : 检查插入数据操作的参数
输入参数  : ucChanId - 通道ID
            pstDscpBlk - 核间传递描述字段
输出参数  : 无
返 回 值  : 检查合法与否, DICC_OK - 合法, 其它 - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年12月15日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_CheckInsertPara(DICC_CHAN_ID_ENUM_UINT8    ucChnId,
                                DICC_INSERT_DSCP_BLK_STRU *pstDscpBlk,
                                DICC_CPU_ID_ENUM_UINT8     enCpuId)
{
    VOS_UINT32                           ulRet;
    volatile DICC_CHAN_CTRL_STRU        *pstDiccChnCtrl = VOS_NULL_PTR;

    ulRet = DICC_CheckChanOpPara(ucChnId, enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    if ((ucChnId != g_astChanRole[enCpuId].aenSender[DICC_SERVICE_TYPE_0])
        && (ucChnId != g_astChanRole[enCpuId].aenSender[DICC_SERVICE_TYPE_1]))
    {
        DICC_LOG3(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckInsertPara] <ucChnId> <enRole> not match ",
            enCpuId, ucChnId, DICC_CHAN_ROLE_SENDER);
        return DICC_ERR_CHAN_ID_NOT_MATCH_ROLE;
    }

    if (VOS_NULL_PTR == pstDscpBlk)
    {
        DICC_LOG2(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckInsertPara] <ucChnId> pstDscpBlk is NULL ",
            enCpuId, ucChnId);
        return DICC_ERR_INSERT_DESP_BLK_PTR_NULL;
    }

    if (VOS_NULL_PTR == pstDscpBlk->pucUserData)
    {
        DICC_LOG2(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckInsertPara] <ucChnId> pstDscpBlk->pucUserData is NULL ",
            enCpuId, ucChnId);
        return DICC_ERR_INSERT_DESP_BLK_DATA_NULL;
    }

    /* 根据通道号查找到核间数据管理控制结构 */
    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);

    if (pstDiccChnCtrl->ucPriDataLen < (VOS_UINT16)(pstDscpBlk->ucDataLen))
    {
        DICC_LOG3(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckInsertPara] <ucChnId> <pstDscpBlk->ucDataLen> size error ",
            enCpuId, ucChnId, (pstDscpBlk->ucDataLen));
        return DICC_ERR_DLV_DATA_BLK_SIZE;
    }

    /* 这里不需要保护, 对同一核而言, 只要不是两核都打开, 则不能插入;
       另一核上mask是无法在sender端没有关闭前, recver端无法关闭 */
    if (DICC_CHAN_BOTH_OPEN_MASK != pstDiccChnCtrl->ucStateMask)
    {
        DICC_LOG3(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckInsertPara] <ucChnId> is not all open, <mask> ",
            enCpuId, ucChnId, (pstDiccChnCtrl->ucStateMask));
        return DICC_ERR_CHAN_NOT_OPEN_IN_BOTH_SIDES;
    }

    return DICC_OK;
}

/*****************************************************************************
函 数 名  : DICC_InsertChannelDataAction
功能描述  : 将待传递的信息数据转移到核间API
            如果描述块结构中enAutoTrigTx置为0时, 不会触发传递行为,
            此时需要由发送端来触发调用DICC_TriggerChanDataTx传递;
            只有在通道打开后, 信息才会真正传递到对端
            发送端和接收端任意一端未打开, 向核间转移待传递的信息数据操作失败
输入参数  : ucChanId - 通道ID
            pstDscpBlk - 核间传递描述字段
输出参数  : 无
返 回 值  : 操作成功与否, VOS_OK - 成功, VOS_ERR - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年8月11日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_InsertChannelDataAction(VOS_UINT32 ulFileId, VOS_UINT32 ulLineNum,
                                        VOS_UINT32 ulPid, DICC_CHAN_ID_ENUM_UINT8 ucChnId,
                                        DICC_INSERT_DSCP_BLK_STRU *pstDscpBlk,
                                        DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    volatile DICC_CHAN_CTRL_STRU        *pstDiccChnCtrl = VOS_NULL_PTR;
    volatile DICC_QUEUE_NODE_STRU       *pstQueueNode = VOS_NULL_PTR;
    VOS_UINT32                           ulIsQFull;
    VOS_UINT32                           ulCurrTime;
#if 0
    VOS_UINT32                           ulFirstInsertTime;
    VOS_UINT32                           ulTimeDiff;
#endif
    DICC_DFX_STRU                       *pstDFx;
    VOS_UINT32                           ulRet;
    DICC_CHAN_INSERT_PAPA_STRU           stInsertPara = {0};
    VOS_UINT32                           ulTemp;
    DICC_CHAN_QUEUE_FULL_EVENT_STRU      stQueueFullEvent;


    DEBUG_PRINT("DICC_InsertChannelData entered ChnId: %d.\n", ucChnId);

    ulRet = DICC_CheckCpuId(enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    ulRet = DICC_CheckInsertPara(ucChnId, pstDscpBlk, enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    /* 成功时记录用户参数 */
    stInsertPara.ucChnId = ucChnId;
    stInsertPara.enChanInitFlag = PS_TRUE;
    stInsertPara.ucChanStateMask = DICC_CHAN_BOTH_OPEN_MASK;
    VOS_MemCpy(&(stInsertPara.stDscpBlk), pstDscpBlk, sizeof((stInsertPara.stDscpBlk)));

    /* 由本地互斥信号量来实现本核该API不重入 */
    stInsertPara.stLocalSemPara.ulResult = VOS_SmP(g_astChanRole[enCpuId].ulDiccLocalMutexSem, 0);
    if (VOS_OK != stInsertPara.stLocalSemPara.ulResult)
    {
        DICC_LOG1(PS_PRINT_ERROR,
            "[<LOCAL CPU_ID>: DICC_InsertChannelDataAction] take ulDiccLocalMutexSem fail, <ulSemRslt>",
            (VOS_INT32)(stInsertPara.stLocalSemPara.ulResult));

        return DICC_ERR_LOCAL_SEMPHORE_FAIL;
    }

    ulCurrTime = mdrv_timer_get_normal_timestamp();    /* 获取当前时戳 */

    /* 根据通道号查找到核间数据管理控制结构 */
    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);
    ulIsQFull = TTF_RING_Q_IsFull(ulPid, (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));

    if (PS_TRUE != ulIsQFull)    /* 队列不满 */
    {
        /* 获取核间传递结点 */
        pstQueueNode = (DICC_QUEUE_NODE_STRU*)TTF_RING_Q_Rear(ulPid,
            (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));
        if (VOS_NULL_PTR == pstQueueNode)
        {
            /* 释放信号量 */
            VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

            DICC_LOG(PS_PRINT_WARNING,
                "[<LOCAL CPU_ID>: DICC_InsertChannelDataAction] Get the node fail ");
            return DICC_ERR_GET_NODE_FAIL;
        }

        /* 数据打上时戳 */
        pstQueueNode->ulInsertTime = ulCurrTime;

        /* 不连续出现队列满, 变量ulConsecutiveQueueFullCnt归零 */
        pstDFx = DICC_GET_CHAN_DFX(g_astChanRole[enCpuId].pastDICCMgmt);
        pstDFx->astChanStatus[ucChnId].stStatistics.ulConsecutiveQueueFullCnt = 0;

        /* 拷贝构造核间传递结点 */
        VOS_MemCpy((VOS_UINT8 *)pstQueueNode->aucPriData, pstDscpBlk->pucUserData, pstDscpBlk->ucDataLen);
        pstQueueNode->ucPriDataLen = pstDscpBlk->ucDataLen;

#if (1 == DICC_DFX_SWITCH)
        /* 插入次数++ */
        (pstDFx->astChanStatus[ucChnId].stStatistics.ulInsertCnt)++;
        pstDFx->astChanStatus[ucChnId].stStatistics.ulInsertPid      = ulPid;
        pstDFx->astChanStatus[ucChnId].stStatistics.ulLastInsertTime = ulCurrTime;
#endif

        DICC_PrintDebugData((VOS_VOID *)(pstQueueNode->aucPriData), pstQueueNode->ucPriDataLen);

        /* 向核间插入信息数据 */
        TTF_RING_Q_In(ulPid, (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));

        if (PS_TRUE == pstDscpBlk->enAutoTrigTx)
        {
            DICC_TriggerChanDataTx(ulPid, ucChnId, enCpuId);
        }
    }
    else
    {
        pstDFx = DICC_GET_CHAN_DFX(g_astChanRole[enCpuId].pastDICCMgmt);
        (pstDFx->astChanStatus[ucChnId].stStatistics.ulConsecutiveQueueFullCnt)++;
        (pstDFx->astChanStatus[ucChnId].stStatistics.ulQueueFullCnt)++;
        ulTemp = pstDFx->astChanStatus[ucChnId].stStatistics.ulConsecutiveQueueFullCnt % DICC_CHAN_QUEUE_FULL_REPORT_TIMES;
        if (0 == ulTemp)
        {
            /* 创建事件 */
            stQueueFullEvent.ulOpPid        = ulPid;
            stQueueFullEvent.ucChnId        = ucChnId;
            stQueueFullEvent.ulQueueFullCnt = pstDFx->astChanStatus[ucChnId].stStatistics.ulQueueFullCnt;

            DICC_SndEvent(ID_DICC_MNTN_QUEUE_FULL_EVENT, &stQueueFullEvent, sizeof(stQueueFullEvent), enCpuId);

            /* 上报消息后, 将ulConsecutiveQueueFullCnt归零 */
            pstDFx->astChanStatus[ucChnId].stStatistics.ulConsecutiveQueueFullCnt = 0;
        }

/* 因为对单板进行软复位, 底软只在exec.bin中记录进行软复位的核上的CPU轨迹以及栈等信息,
   而对另一核上, 没有及时记录信息, 因此软复位后, 将无法知晓两核状况, 不利于定位,
   因此邮件交流决定改为上报事件来发现此场景 */
#if 0
        pstQueueNode = (DICC_QUEUE_NODE_STRU*)TTF_RING_Q_Front(ulPid,
            (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));

        /* 取队首结点的时戳 */
        ulFirstInsertTime = pstQueueNode->ulInsertTime;

        ulTimeDiff = DICC_TimeDiff(ulFirstInsertTime, ulCurrTime);
        if (DICC_CHAN_QUEUE_FULL_TIME <= ulTimeDiff)    /* 队首结点入队时间距今已经超过1s */
        {
            /* 将通道中最前面的10块数据搜集起来, 调用OM API进行单板复位 */
            DICC_ChanStayInFullState(ulFileId, ulLineNum, ulPid, pstDiccChnCtrl, enCpuId);
        }
#endif

        /* 释放信号量 */
        VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

        return DICC_ERR_CHAN_FULL;
    }

    /* 释放信号量 */
    VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

    return DICC_OK;
}    /* DICC_InsertChannelData */

/*****************************************************************************
函 数 名  : DICC_CheckRemovePara
功能描述  : 检查取出数据操作的参数
输入参数  : ucChanId - 通道ID
            pucUsrData - 从核间取出的数据拷贝到此, 外部使用者保证指针非空
输出参数  : 无
返 回 值  : 检查合法与否, DICC_OK - 合法, 其它 - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年12月15日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_CheckRemovePara(DICC_CHAN_ID_ENUM_UINT8 ucChnId,
                                VOS_UINT8              *pucUsrData,
                                DICC_CPU_ID_ENUM_UINT8  enCpuId)
{
    VOS_UINT32 ulRet;

    ulRet = DICC_CheckChanOpPara(ucChnId, enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    if ((ucChnId != g_astChanRole[enCpuId].aenRecver[DICC_SERVICE_TYPE_0])
        && (ucChnId != g_astChanRole[enCpuId].aenRecver[DICC_SERVICE_TYPE_1]))
    {
        DICC_LOG3(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckRemovePara] <ucChnId> <enUserRole> not match ",
            enCpuId, ucChnId, DICC_CHAN_ROLE_RECVER);
        return DICC_ERR_CHAN_ID_NOT_MATCH_ROLE;
    }

    if (VOS_NULL_PTR == pucUsrData)
    {
        DICC_LOG2(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckRemovePara] <ucChnId> pucUsrData is NULL ",
            enCpuId, ucChnId);
        return DICC_ERR_REMOVE_DATA_PTR_NULL;
    }

    return DICC_OK;
}

/*****************************************************************************
函 数 名  : DICC_RemoveChannelData
功能描述  : 将传递的信息从核间环形共享缓冲中取出API
输入参数  : ulPid - 调用此接口的PID
            ucChanId - 通道ID
            pucUsrData - 从核间取出的数据拷贝到此, 外部使用者保证指针非空
输出参数  : 无
返 回 值  : 操作成功与否, DICC_OK - 成功, 其它 - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年8月11日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_RemoveChannelData(VOS_UINT32              ulPid,
                                  DICC_CHAN_ID_ENUM_UINT8 ucChnId,
                                  VOS_UINT8              *pucUsrData,
                                  DICC_CPU_ID_ENUM_UINT8  enCpuId)
{
    volatile DICC_CHAN_CTRL_STRU             *pstDiccChnCtrl = VOS_NULL_PTR;
    volatile DICC_QUEUE_NODE_STRU            *pstQueueNode   = VOS_NULL_PTR;
#if (1 == DICC_DFX_SWITCH)
    DICC_DFX_STRU                            *pstDFx;
#endif
    VOS_UINT32                                ulRet;
    DICC_CHAN_MAGIC_NUM_CHANGED_EVENT_STRU    stMagicEvent;
    DICC_CHAN_REMOVE_PAPA_STRU                stRemovePara = {0};

    DEBUG_PRINT("DICC_RemoveChannelData entered! \n");

    ulRet = DICC_CheckCpuId(enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    ulRet = DICC_CheckRemovePara(ucChnId, pucUsrData, enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    /* 根据通道号查找到核间数据管理控制结构 */
    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);

    /* 成功后记录用户操作参数 */
    stRemovePara.ucChnId          = ucChnId;
    stRemovePara.enChanInitFlag   = PS_TRUE;
    stRemovePara.ucChanStateMask  = pstDiccChnCtrl->ucStateMask;
    stRemovePara.ucFlushData      = 0;
    stRemovePara.pucToSaveUsrData = pucUsrData;

    /* 由本地互斥信号量来实现本核该API不重入 */
    stRemovePara.stLocalSemPara.ulResult = VOS_SmP(g_astChanRole[enCpuId].ulDiccLocalMutexSem, 0);
    if (VOS_OK != stRemovePara.stLocalSemPara.ulResult)
    {
        DICC_LOG1(PS_PRINT_ERROR,
            "[<LOCAL CPU_ID>: DICC_InsertChannelDataAction] take ulDiccLocalMutexSem fail, <ulSemRslt>",
            (VOS_INT32)(stRemovePara.stLocalSemPara.ulResult));

        return DICC_ERR_LOCAL_SEMPHORE_FAIL;
    }

    /* 接收端没有关闭, 则可以继续取数 */
    if (DICC_CHAN_RECVER_OPEN_MASK == (DICC_CHAN_RECVER_OPEN_MASK & pstDiccChnCtrl->ucStateMask))
    {
        if (0 != TTF_RING_Q_GetCnt(ulPid, (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer))))
        {
            /* 获取下一个核间传递结点 */
            pstQueueNode = (DICC_QUEUE_NODE_STRU*)TTF_RING_Q_Out(ulPid,
                (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));

            if (VOS_NULL_PTR == pstQueueNode)
            {
                /* 释放信号量 */
                VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

                DICC_LOG(PS_PRINT_WARNING,
                    "[<LOCAL CPU_ID>: DICC_RemoveChannelData] Get the node fail ");
                return DICC_ERR_GET_NODE_FAIL;
            }

#if (1 == DICC_DFX_SWITCH)
            /* 取出次数++ */
            pstDFx = DICC_GET_CHAN_DFX(g_astChanRole[enCpuId].pastDICCMgmt);
            (pstDFx->astChanStatus[ucChnId].stStatistics.ulRemoveCnt)++;
            pstDFx->astChanStatus[ucChnId].stStatistics.ulRemovePid = ulPid;
            pstDFx->astChanStatus[ucChnId].stStatistics.ulLastRemoveTime = mdrv_timer_get_normal_timestamp();
#endif

            DEBUG_PRINT("pstQueueNode:0x%x pstQueueNode->aucPriData:0x%x\n",
                        (unsigned int)pstQueueNode, (unsigned int)pstQueueNode->aucPriData);

            if (DICC_MAGIC_NUM_VALUE != pstQueueNode->usMagicNum)
            {
                /* 释放信号量 */
                VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

                /* 创建事件 */
                stMagicEvent.ulOpPid    = ulPid;
                stMagicEvent.ucChnId    = ucChnId;
                PS_MEM_CPY(&(stMagicEvent.stQueueNode), (VOS_UINT8*)pstQueueNode, sizeof(stMagicEvent.stQueueNode));

                DICC_SndEvent(ID_DICC_MNTN_MAGIC_NUM_CHANGED_EVENT, &stMagicEvent, sizeof(stMagicEvent), enCpuId);

                DICC_LOG2(PS_PRINT_ERROR,
                    "[<LOCAL CPU_ID>: DICC_RemoveChannelData] <ucChnId> find magic num tampered",
                    enCpuId, ucChnId);
                return DICC_ERR_MAGIC_NUM_CHANGED;
            }

            VOS_MemCpy(pucUsrData, (VOS_UINT8 *)pstQueueNode->aucPriData, pstQueueNode->ucPriDataLen);

            DEBUG_PRINT("DICC_RemoveChannelData pstQueueNode->ucPriDataLen = %d:\n", pstQueueNode->ucPriDataLen);
            DEBUG_PRINT("DICC_RemoveChannelData print remove data start:\n");
            DICC_PrintDebugData(pucUsrData, pstQueueNode->ucPriDataLen);

            /* 考虑到传递信息可能有指针之类, 为了安全, 清除传递信息 */
            VOS_MemSet((VOS_VOID *)pstQueueNode->aucPriData, 0x0, sizeof(pstQueueNode->aucPriData));
        }
    }

    /* 释放信号量 */
    VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

    return DICC_OK;
}    /* DICC_RemoveChannelData */

/*****************************************************************************
函 数 名  : DICC_IsCurrChnOpen
功能描述  : 判断通道本端是否打开
输入参数  : ucChanId - 通道ID
输出参数  : 无
返 回 值  : 打开:PS_TRUE
            没有打开:PS_FALSE
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年8月11日
   作    者   : g00178567
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 DICC_IsCurrChnOpen(DICC_CHAN_ID_ENUM_UINT8 ucChnId,
              DICC_CPU_ID_ENUM_UINT8           enCpuId)
{
    volatile DICC_CHAN_CTRL_STRU *pstDiccChnCtrl = VOS_NULL_PTR;
    DICC_CHAN_ROLE_ENUM_UINT8     enUserRole = DICC_CHAN_ROLE_BUTT;

    /* 根据通道号查找到核间数据管理控制结构 */
    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);

    enUserRole = g_astChanRole[enCpuId].aenRole[ucChnId];
    if (DICC_CHAN_ROLE_SENDER == enUserRole)
    {
        if (DICC_CHAN_SENDER_OPEN_MASK == (DICC_CHAN_SENDER_OPEN_MASK & pstDiccChnCtrl->ucStateMask))
        {
            return PS_TRUE;
        }
        else
        {
            return PS_FALSE;
        }
    }
    else if (DICC_CHAN_ROLE_RECVER == enUserRole)
    {
        if (DICC_CHAN_RECVER_OPEN_MASK == (DICC_CHAN_RECVER_OPEN_MASK & pstDiccChnCtrl->ucStateMask))
        {
            return PS_TRUE;
        }
        else
        {
            return PS_FALSE;
        }
    }
    else
    {
        DICC_LOG2(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_IsCurrChnOpen] undefined <enUserRole>",
            enCpuId, enUserRole);
        return PS_FALSE;
    }
}

/*****************************************************************************
函 数 名  : DICC_CheckGetNodeCntPara
功能描述  : 检查获取通道中数据块数的参数
输入参数  : ucChanId - 通道ID
            enGetChnNodeCntType - 指示获取通道中已经存放的数据个数,
                                  或者通道中可以继续存放的个数
输出参数  : 无
返 回 值  : 检查合法与否, DICC_OK - 合法, 其它 - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年8月11日
   作    者   : g00178567
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_CheckGetNodeCntPara(DICC_CHAN_ID_ENUM_UINT8          ucChnId,
                                    DICC_GET_CHN_NODE_CNT_ENUM_UINT8 enGetChnNodeCntType,
                                    DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    VOS_UINT32 ulRet;

    ulRet = DICC_CheckCpuId(enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    ulRet = DICC_CheckChanOpPara(ucChnId, enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    if (DICC_GET_CHN_NODE_CNT_BUTT <= enGetChnNodeCntType)
    {
        DICC_LOG3(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckGetNodeCntPara] <ucChnId> undefined <enGetChnNodeCntType>",
            enCpuId, ucChnId, enGetChnNodeCntType);
        return DICC_ERR_GET_CNT_TYPE_UNDEFINED;
    }

    return DICC_OK;
}

/*****************************************************************************
函 数 名  : DICC_GetChannelNodeCnt
功能描述  : 检查获取通道中数据块数的参数
输入参数  : ulPid - 调用此接口的PID
            ucChanId - 通道ID
            enGetChnNodeCntType - 指示获取通道中已经存放的数据个数,
                                  或者通道中可以继续存放的个数
输出参数  : 无
返 回 值  : 操作成功与否, DICC_OK - 成功, 其它 - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年8月11日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_GetChannelNodeCnt(VOS_UINT32                       ulPid,
                                  DICC_CHAN_ID_ENUM_UINT8          ucChnId,
                                  DICC_GET_CHN_NODE_CNT_ENUM_UINT8 enGetChnNodeCntType,
                                  DICC_CPU_ID_ENUM_UINT8           enCpuId)
{
    VOS_UINT32                    ulCurrCnt      = DICC_INVALID_VALUE;
    VOS_UINT32                    ulTmpCnt       = 0;
    volatile DICC_CHAN_CTRL_STRU *pstDiccChnCtrl = VOS_NULL_PTR;
    VOS_UINT32                    ulRet;

    ulRet = DICC_CheckGetNodeCntPara(ucChnId, enGetChnNodeCntType, enCpuId);
    if (DICC_OK != ulRet)
    {
        return DICC_INVALID_VALUE;
    }

    if (PS_TRUE == DICC_IsCurrChnOpen(ucChnId, enCpuId))
    {
        /* 根据通道号查找到核间数据管理控制结构 */
        pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);

        /* 获取通道中当前存放的信息块数 */
        ulTmpCnt = TTF_RING_Q_GetCnt(ulPid, (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));
        if (DICC_GET_CHN_CURR_DATA_CNT == enGetChnNodeCntType)
        {
            ulCurrCnt = ulTmpCnt;
        }
        else
        {
            ulCurrCnt = pstDiccChnCtrl->usChnBlkNum - ulTmpCnt - 1;
        }
    }

    return ulCurrCnt;
}    /* DICC_GetChannelNodeCnt */

#if (VOS_WIN32 != VOS_OS_VER)
/*****************************************************************************
函 数 名  : DICC_Info
功能描述  : DICC通道管理结构输出
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
说    明  : 单板上可测可维函数, 直接使用vos_printf向串口打印

修改历史      :
 1.日    期   : 2011年12月27日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DICC_Info()
{
    volatile DICC_CHAN_CTRL_STRU *pstDiccChnCtrl = VOS_NULL_PTR;
    VOS_UINT8                     ucChanLoop;
    DICC_CPU_ID_ENUM_UINT8        enCpuId;
    volatile DICC_CTRL_STRU      *pastDICCMgmt   = VOS_NULL_PTR;

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    enCpuId = DICC_CPU_ID_CCPU;
#elif (OSA_CPU_ACPU == VOS_OSA_CPU)
    enCpuId = DICC_CPU_ID_ACPU;
#endif

    pastDICCMgmt = g_astChanRole[enCpuId].pastDICCMgmt;

    if (VOS_NULL_PTR == pastDICCMgmt)
    {
        vos_printf("get g_pastDICCMgmt NULL\n");
        return ;
    }
    else
    {
        vos_printf("==============DFx Info============\n");
        vos_printf("CurrSlice:                  0x%x\n", mdrv_timer_get_normal_timestamp());
        vos_printf("ulCurrSize:                 %u\n", pastDICCMgmt->ulCurrSize);
        vos_printf("enDFxEnabled:               %u\n", pastDICCMgmt->stDFx.enDFxEnabled);
        vos_printf("==================================\n");
    }

    for (ucChanLoop = 0; ucChanLoop < DICC_MAX_CHAN_NUM; ucChanLoop++)
    {
        /* 根据通道号查找到核间数据管理控制结构 */
        pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChanLoop, enCpuId);
        if (VOS_NULL_PTR != pstDiccChnCtrl)
        {
            vos_printf("===========Chan Ctrl Info=========\n");
            vos_printf("ucChanId:                   %u\n", pstDiccChnCtrl->ucChanId);
            vos_printf("ucStateMask:                0x%x\n", pstDiccChnCtrl->ucStateMask);
            vos_printf("enValidFlag:                %u\n", pstDiccChnCtrl->enValidFlag);
            vos_printf("ucPriDataLen:               %u\n", pstDiccChnCtrl->ucPriDataLen);
            vos_printf("usChnBlkNum:                %u\n", pstDiccChnCtrl->usChnBlkNum);
            vos_printf("ulTtfRingQStAddrOffSet:     %u\n", pstDiccChnCtrl->ulTtfRingQStAddrOffSet);
            vos_printf("ulQueueNodeAddrOffSet:      %u\n", pstDiccChnCtrl->ulQueueNodeAddrOffSet);
            vos_printf("==================================\n");
        }
        else
        {
            vos_printf("get chan addr fail\n");
            vos_printf("==================================\n");
        }
    }

    vos_printf("==============ISR Dbg=============\n");
    vos_printf("ulInvalidDisableOpPid:      %u\n", pastDICCMgmt->stDFx.stIsrDbg.ulInvalidDisableOpPid);
    vos_printf("ulInvalidDisableOpTime:     0x%x\n", pastDICCMgmt->stDFx.stIsrDbg.ulInvalidDisableOpTime);
    vos_printf("ulInvalidEnableOpPid:       %u\n", pastDICCMgmt->stDFx.stIsrDbg.ulInvalidEnableOpPid);
    vos_printf("ulInvalidEnableOpTime:      0x%x\n", pastDICCMgmt->stDFx.stIsrDbg.ulInvalidEnableOpTime);
    vos_printf("==================================\n");

    return;
}

/*****************************************************************************
函 数 名  : DICC_Chan_Info
功能描述  : DICC通道现状输出
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
说    明  : 单板上可测可维函数, 直接使用vos_printf向串口打印

修改历史      :
 1.日    期   : 2011年12月27日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DICC_Chan_Info(VOS_INT32 lChanId)
{
    DICC_CPU_ID_ENUM_UINT8                 enCpuId;
    volatile DICC_CTRL_STRU               *pastDICCMgmt   = VOS_NULL_PTR;
    volatile DICC_CHAN_STATISTICS_STRU    *pstStatistics  = VOS_NULL_PTR;
    volatile DICC_ISR_OP_STRU             *pstIsrOp       = VOS_NULL_PTR;
    VOS_UINT8                              ucChanId;

    if ((lChanId >= DICC_CHAN_ID_BUTT) || (lChanId < 0))
    {
        vos_printf("invalid ucChanId\n");
        return ;
    }
    else
    {
        ucChanId = (VOS_UINT8)lChanId;
    }

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    enCpuId = DICC_CPU_ID_CCPU;
#elif (OSA_CPU_ACPU == VOS_OSA_CPU)
    enCpuId = DICC_CPU_ID_ACPU;
#endif

    pastDICCMgmt = g_astChanRole[enCpuId].pastDICCMgmt;

    if (VOS_NULL_PTR == pastDICCMgmt)
    {
        vos_printf("get g_pastDICCMgmt NULL\n");
        return ;
    }

    if (PS_FALSE == pastDICCMgmt->stDFx.enDFxEnabled)
    {
        vos_printf("enDFxEnabled is disable\n");
        return;    /* 未统计, 返回 */
    }

    pstStatistics = &(pastDICCMgmt->stDFx.astChanStatus[ucChanId].stStatistics);
    pstIsrOp      = &(pastDICCMgmt->stDFx.astChanStatus[ucChanId].stIsrOp);

    vos_printf("==========Chan Statistics Info=========\n");
    vos_printf("CurrSlice:                  0x%x\n", mdrv_timer_get_normal_timestamp());
    vos_printf("ulInsertPid:                %u\n", pstStatistics->ulInsertPid);
    vos_printf("ulInsertCnt:                %u\n", pstStatistics->ulInsertCnt);
    vos_printf("ulQueueFullCnt:             %u\n", pstStatistics->ulQueueFullCnt);
    vos_printf("ulConsecutiveQueueFullCnt:  %u\n", pstStatistics->ulConsecutiveQueueFullCnt);
    vos_printf("ulLastInsertTime:           0x%x\n", pstStatistics->ulLastInsertTime);
    vos_printf("ulRemovePid:                %u\n", pstStatistics->ulRemovePid);
    vos_printf("ulRemoveCnt:                %u\n", pstStatistics->ulRemoveCnt);
    vos_printf("ulLastRemoveTime:           0x%x\n", pstStatistics->ulLastRemoveTime);
    vos_printf("ulTrigIsrPid:               %u\n", pstStatistics->ulTrigIsrPid);
    vos_printf("ulTrigIsrCnt:               %u\n", pstStatistics->ulTrigIsrCnt);
    vos_printf("ulLastTrigIsrTime:          0x%x\n", pstStatistics->ulLastTrigIsrTime);
    vos_printf("ulDisableIptOpPid:          %u\n", pstIsrOp->ulDisableOpPid);
    vos_printf("ulDisableIptOpTime:         0x%x\n", pstIsrOp->ulDisableOpTime);
    vos_printf("ulDisableIptCnt:            %u\n", pstIsrOp->ulDisableCnt);
    vos_printf("ulEnableIptOpPid:           %u\n", pstIsrOp->ulEnableOpPid);
    vos_printf("ulEnableIptOpTime:          0x%x\n", pstIsrOp->ulEnableOpTime);
    vos_printf("ulEnableIptCnt:             %u\n", pstIsrOp->ulEnableCnt);
}

/*****************************************************************************
函 数 名  : DICC_Help
功能描述  : 单板上可测可维函数
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年12月27日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DICC_Help()
{
    vos_printf("===============================================\n");
    vos_printf("DICC_Info\n");
    vos_printf("DICC_Chan_Info  参数:通道ID[0-3]\n");
    vos_printf("通道0:上行CSD业务数据传递通道, 数据方向:A->C\n");
    vos_printf("通道1:释放上行用户业务数据传递通道, 数据方向:C->A\n");
    vos_printf("通道2:下行CSD业务数据传递通道, 数据方向:C->A\n");
    vos_printf("通道3:释放下行用户业务数据传递通道, 数据方向:A->C\n");
    vos_printf("===============================================\n");
}  /* DICC_Help */
#endif    /* end of #if (VOS_WIN32 != VOS_OS_VER) */

/*****************************************************************************
函 数 名  : DICC_CheckBatRemovePara
功能描述  : 检查取出数据操作的参数
输入参数  : ucChanId - 通道ID
            pucUsrData - 从核间取出的数据拷贝到此, 外部使用者保证指针非空
输出参数  : 无
返 回 值  : 检查合法与否, DICC_OK - 合法, 其它 - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年12月15日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_CheckBatRemovePara(DICC_CHAN_ID_ENUM_UINT8  ucChnId,
                                VOS_UINT16                  usNeedRemoveCnt,
                                VOS_UINT16                 *pusActiveRemoveCnt,
                                DICC_CPU_ID_ENUM_UINT8      enCpuId)
{
    VOS_UINT32 ulRet;

    ulRet = DICC_CheckChanOpPara(ucChnId, enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    if ((ucChnId != g_astChanRole[enCpuId].aenRecver[DICC_SERVICE_TYPE_0])
        && (ucChnId != g_astChanRole[enCpuId].aenRecver[DICC_SERVICE_TYPE_1]))
    {
        DICC_LOG3(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckRemovePara] <ucChnId> <enUserRole> not match ",
            enCpuId, ucChnId, DICC_CHAN_ROLE_RECVER);
        return DICC_ERR_CHAN_ID_NOT_MATCH_ROLE;
    }

    if (usNeedRemoveCnt > DICC_BAT_OP_CNT)
    {
        DICC_LOG2(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckRemovePara] <ucChnId> ulNeedRemoveCnt is invalid ",
            enCpuId, ucChnId);
        return DICC_ERR_REMOVE_DATA_CNT;
    }

/*
    if (VOS_NULL_PTR == apucUsrData)
    {
        DICC_LOG2(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckRemovePara] <ucChnId> apucUsrData is NULL ",
            enCpuId, ucChnId);
        return DICC_ERR_REMOVE_DATA_PTR_NULL;
    }
*/

    if (VOS_NULL_PTR == pusActiveRemoveCnt)
    {
        DICC_LOG2(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckRemovePara] <ucChnId> pusActiveRemoveCnt is NULL ",
            enCpuId, ucChnId);
        return DICC_ERR_REMOVE_DATA_PTR_NULL;
    }

    return DICC_OK;
}

/*****************************************************************************
函 数 名  : DICC_BatRemoveChannelData
功能描述  : 将传递的信息从核间环形共享缓冲中取出API
输入参数  : ulPid - 调用此接口的PID
            ucChanId - 通道ID
            pucUsrData - 从核间取出的数据拷贝到此, 外部使用者保证指针非空
输出参数  : 无
返 回 值  : 操作成功与否, DICC_OK - 成功, 其它 - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年8月11日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_BatRemoveChannelData(VOS_UINT32            ulPid,
                                  DICC_CHAN_ID_ENUM_UINT8  ucChnId,
                                  VOS_UINT8                aucUsrData[],
                                  VOS_UINT16               usNeedRemoveCnt,
                                  VOS_UINT16              *pusActiveRemoveCnt,
                                  DICC_CPU_ID_ENUM_UINT8   enCpuId)
{
    volatile DICC_CHAN_CTRL_STRU             *pstDiccChnCtrl = VOS_NULL_PTR;
    volatile DICC_QUEUE_NODE_STRU            *pstQueueNode   = VOS_NULL_PTR;
#if (1 == DICC_DFX_SWITCH)
    DICC_DFX_STRU                            *pstDFx;
#endif
    VOS_UINT32                                ulRet;
    DICC_CHAN_MAGIC_NUM_CHANGED_EVENT_STRU    stMagicEvent;
    VOS_UINT32                                ulActiveNeedCnt;
    VOS_UINT32                                ulResult;
    VOS_UINT32                                ulRingQCnt;
#if 0
    VOS_VOID                                 *astQueueNode[DICC_BAT_OP_CNT];
#endif
    VOS_UINT32                                ulCurrTime;
    VOS_UINT32                                ulCopyLen;

    DEBUG_PRINT("DICC_RemoveChannelData entered! \n");

    ulRet = DICC_CheckCpuId(enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    ulRet = DICC_CheckBatRemovePara(ucChnId, usNeedRemoveCnt,
                pusActiveRemoveCnt, enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    /* 根据通道号查找到核间数据管理控制结构 */
    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);

    /* 由本地互斥信号量来实现本核该API不重入 */
    ulResult = VOS_SmP(g_astChanRole[enCpuId].ulDiccLocalMutexSem, 0);
    if (VOS_OK != ulResult)
    {
        DICC_LOG1(PS_PRINT_ERROR,
            "[<LOCAL CPU_ID>: DICC_InsertChannelDataAction] take ulDiccLocalMutexSem fail, <ulSemRslt>",
            (VOS_INT32)ulResult);

        return DICC_ERR_LOCAL_SEMPHORE_FAIL;
    }

    /* 接收端没有关闭, 则可以继续取数 */
    if (DICC_CHAN_RECVER_OPEN_MASK == (DICC_CHAN_RECVER_OPEN_MASK & pstDiccChnCtrl->ucStateMask))
    {
        ulRingQCnt      = TTF_RING_Q_GetCnt(ulPid, (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));
        ulActiveNeedCnt = PS_MIN(ulRingQCnt, usNeedRemoveCnt);    /* 应对用户提供的个数不准确 */
        *pusActiveRemoveCnt = 0;
        ulCopyLen       = 0;
        ulCurrTime      = mdrv_timer_get_normal_timestamp();

        while (0 != ulActiveNeedCnt)
        {
            /* 获取下一个核间传递结点 */
            pstQueueNode = (DICC_QUEUE_NODE_STRU*)TTF_RING_Q_Out(ulPid,
                (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));

            if (VOS_NULL_PTR == pstQueueNode)
            {
                /* 释放信号量 */
                VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

                DICC_LOG(PS_PRINT_WARNING,
                    "[<LOCAL CPU_ID>: DICC_RemoveChannelData] Get the node fail ");
                return DICC_ERR_GET_NODE_FAIL;
            }

#if (1 == DICC_DFX_SWITCH)
            /* 取出次数++ */
            pstDFx = DICC_GET_CHAN_DFX(g_astChanRole[enCpuId].pastDICCMgmt);
            (pstDFx->astChanStatus[ucChnId].stStatistics.ulRemoveCnt)++;
            pstDFx->astChanStatus[ucChnId].stStatistics.ulRemovePid = ulPid;
            pstDFx->astChanStatus[ucChnId].stStatistics.ulLastRemoveTime = ulCurrTime;
#endif

            DEBUG_PRINT("pstQueueNode:0x%x pstQueueNode->aucPriData:0x%x\n",
                        (unsigned int)pstQueueNode, (unsigned int)pstQueueNode->aucPriData);

            if (DICC_MAGIC_NUM_VALUE != pstQueueNode->usMagicNum)
            {
                /* 释放信号量 */
                VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

                /* 创建事件 */
                stMagicEvent.ulOpPid    = ulPid;
                stMagicEvent.ucChnId    = ucChnId;
                PS_MEM_CPY(&(stMagicEvent.stQueueNode), (VOS_UINT8*)pstQueueNode, sizeof(stMagicEvent.stQueueNode));

                DICC_SndEvent(ID_DICC_MNTN_MAGIC_NUM_CHANGED_EVENT, &stMagicEvent, sizeof(stMagicEvent), enCpuId);

                DICC_LOG2(PS_PRINT_ERROR,
                    "[<LOCAL CPU_ID>: DICC_RemoveChannelData] <ucChnId> find magic num tampered",
                    enCpuId, ucChnId);
                return DICC_ERR_MAGIC_NUM_CHANGED;
            }

            VOS_MemCpy(&aucUsrData[ulCopyLen], (VOS_UINT8 *)pstQueueNode->aucPriData, pstQueueNode->ucPriDataLen);
            ulCopyLen += pstQueueNode->ucPriDataLen;

            /* 考虑到传递信息可能有指针之类, 为了安全, 清除传递信息 */
            VOS_MemSet((VOS_VOID *)pstQueueNode->aucPriData, 0x0, sizeof(pstQueueNode->aucPriData));

            /* 检查通过拷贝数据后才增加计数 */
            (*pusActiveRemoveCnt)++;

            ulActiveNeedCnt--;
        }
    }

    /* 释放信号量 */
    VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

    return DICC_OK;
}    /* DICC_RemoveChannelData */

VOS_UINT8 g_ucCheckBatInsert = 1;
/*****************************************************************************
函 数 名  : DICC_CheckBatInsertPara
功能描述  : 检查插入数据操作的参数
输入参数  : ucChanId - 通道ID
            pstDscpBlk - 核间传递描述字段
输出参数  : 无
返 回 值  : 检查合法与否, DICC_OK - 合法, 其它 - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年12月15日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_CheckBatInsertPara(VOS_UINT32 ulPid,
                                DICC_CHAN_ID_ENUM_UINT8    ucChnId,
                                DICC_BAT_INSERT_DSCP_BLK_STRU    *pstBatDscpBlk,
                                DICC_CPU_ID_ENUM_UINT8     enCpuId)
{
    VOS_UINT32                           ulRet;
    volatile DICC_CHAN_CTRL_STRU        *pstDiccChnCtrl = VOS_NULL_PTR;
    VOS_UINT32                           ulLoop;
    VOS_UINT32                           ulCurrCnt;

    ulRet = DICC_CheckChanOpPara(ucChnId, enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    if ((ucChnId != g_astChanRole[enCpuId].aenSender[DICC_SERVICE_TYPE_0])
        && (ucChnId != g_astChanRole[enCpuId].aenSender[DICC_SERVICE_TYPE_1]))
    {
        DICC_LOG3(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckInsertPara] <ucChnId> <enRole> not match ",
            enCpuId, ucChnId, DICC_CHAN_ROLE_SENDER);
        return DICC_ERR_CHAN_ID_NOT_MATCH_ROLE;
    }

    if (VOS_NULL_PTR == pstBatDscpBlk)
    {
        DICC_LOG2(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckInsertPara] <ucChnId> pstDscpBlk is NULL ",
            enCpuId, ucChnId);
        return DICC_ERR_INSERT_DESP_BLK_PTR_NULL;
    }

    if (pstBatDscpBlk->ucInsertCnt > DICC_BAT_OP_CNT)
    {
        DICC_LOG3(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckInsertPara] <ucChnId> <ucInsertCnt> is invalid ",
            enCpuId, ucChnId, pstBatDscpBlk->ucInsertCnt);
        return DICC_ERR_INSERT_DESP_BLK_DATA_CNT;
    }

    /* 根据通道号查找到核间数据管理控制结构 */
    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);

    if (1 == g_ucCheckBatInsert)
    {
        for (ulLoop = 0; ulLoop < (VOS_UINT32)(pstBatDscpBlk->ucInsertCnt); ulLoop ++)
        {
            if (VOS_NULL_PTR == pstBatDscpBlk->apucUserData[ulLoop])
            {
                DICC_LOG2(PS_PRINT_WARNING,
                    "[<LOCAL CPU_ID>: DICC_CheckInsertPara] <ucChnId> pstDscpBlk->pucUserData is NULL ",
                    enCpuId, ucChnId);
                return DICC_ERR_INSERT_DESP_BLK_DATA_NULL;
            }

            if (pstDiccChnCtrl->ucPriDataLen < (VOS_UINT16)(pstBatDscpBlk->aucDataLen[ulLoop]))
            {
                DICC_LOG3(PS_PRINT_WARNING,
                    "[<LOCAL CPU_ID>: DICC_CheckInsertPara] <ucChnId> <ucDataLen> size error ",
                    enCpuId, ucChnId, (pstBatDscpBlk->aucDataLen[ulLoop]));
                return DICC_ERR_DLV_DATA_BLK_SIZE;
            }
        }
    }

    /* 这里不需要保护, 对同一核而言, 只要不是两核都打开, 则不能插入;
       另一核上mask是无法在sender端没有关闭前, recver端无法关闭 */
    if (DICC_CHAN_BOTH_OPEN_MASK != pstDiccChnCtrl->ucStateMask)
    {
        DICC_LOG3(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckInsertPara] <ucChnId> is not all open, <mask> ",
            enCpuId, ucChnId, (pstDiccChnCtrl->ucStateMask));
        return DICC_ERR_CHAN_NOT_OPEN_IN_BOTH_SIDES;
    }

    /* 获取通道中当前存放的信息块数 */
    ulCurrCnt = TTF_RING_Q_GetCnt(ulPid, (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));
    if ((pstBatDscpBlk->ucInsertCnt + ulCurrCnt) >= pstDiccChnCtrl->usChnBlkNum)
    {
        DICC_LOG4(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckInsertPara] <ucChnId> cannot <insert>, <currcnt> ",
            enCpuId, ucChnId, (pstBatDscpBlk->ucInsertCnt), (VOS_INT)ulCurrCnt);
        return DICC_ERR_INSERT_DESP_BLK_DATA_CNT;
    }

    return DICC_OK;
}

/*****************************************************************************
函 数 名  : DICC_BatInsertChannelDataAction
功能描述  : 将待传递的信息数据转移到核间API
            如果描述块结构中enAutoTrigTx置为0时, 不会触发传递行为,
            此时需要由发送端来触发调用DICC_TriggerChanDataTx传递;
            只有在通道打开后, 信息才会真正传递到对端
            发送端和接收端任意一端未打开, 向核间转移待传递的信息数据操作失败
输入参数  : ucChanId - 通道ID
            pstDscpBlk - 核间传递描述字段
输出参数  : 无
返 回 值  : 操作成功与否, VOS_OK - 成功, VOS_ERR - 失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年8月11日
   作    者   : liukai
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DICC_BatInsertChannelDataAction(VOS_UINT32 ulFileId, VOS_UINT32 ulLineNum,
                                        VOS_UINT32 ulPid, DICC_CHAN_ID_ENUM_UINT8 ucChnId,
                                        DICC_BAT_INSERT_DSCP_BLK_STRU    *pstBatDscpBlk,
                                        DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    volatile DICC_CHAN_CTRL_STRU        *pstDiccChnCtrl = VOS_NULL_PTR;
    volatile DICC_QUEUE_NODE_STRU       *pstQueueNode = VOS_NULL_PTR;
    VOS_UINT32                           ulCurrTime;
    DICC_DFX_STRU                       *pstDFx;
    VOS_UINT32                           ulRet;
    VOS_UINT32                           ulResult;
    VOS_UINT32                           ulActiveInsertCnt;


    DEBUG_PRINT("DICC_InsertChannelData entered ChnId: %d.\n", ucChnId);

    ulRet = DICC_CheckCpuId(enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    ulRet = DICC_CheckBatInsertPara(ulPid, ucChnId, pstBatDscpBlk, enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    /* 由本地互斥信号量来实现本核该API不重入 */
    ulResult = VOS_SmP(g_astChanRole[enCpuId].ulDiccLocalMutexSem, 0);
    if (VOS_OK != ulResult)
    {
        DICC_LOG1(PS_PRINT_ERROR,
            "[<LOCAL CPU_ID>: DICC_InsertChannelDataAction] take ulDiccLocalMutexSem fail, <ulSemRslt>",
            (VOS_INT32)ulResult);

        return DICC_ERR_LOCAL_SEMPHORE_FAIL;
    }

    /* 根据通道号查找到核间数据管理控制结构 */
    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);
    ulActiveInsertCnt = 0;
    ulCurrTime = mdrv_timer_get_normal_timestamp();    /* 获取当前时戳 */

    while (ulActiveInsertCnt < pstBatDscpBlk->ucInsertCnt)
    {
        /* 获取核间传递结点 */
        pstQueueNode = (DICC_QUEUE_NODE_STRU*)TTF_RING_Q_Rear(ulPid,
            (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));
        if (VOS_NULL_PTR == pstQueueNode)
        {
            /* 释放信号量 */
            VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

            DICC_LOG(PS_PRINT_WARNING,
                "[<LOCAL CPU_ID>: DICC_InsertChannelDataAction] Get the node fail ");
            return DICC_ERR_GET_NODE_FAIL;
        }

        /* 数据打上时戳 */
        pstQueueNode->ulInsertTime = ulCurrTime;

        /* 不连续出现队列满, 变量ulConsecutiveQueueFullCnt归零 */
        pstDFx = DICC_GET_CHAN_DFX(g_astChanRole[enCpuId].pastDICCMgmt);
        pstDFx->astChanStatus[ucChnId].stStatistics.ulConsecutiveQueueFullCnt = 0;

        /* 拷贝构造核间传递结点 */
        VOS_MemCpy((VOS_UINT8 *)pstQueueNode->aucPriData,
                   pstBatDscpBlk->apucUserData[ulActiveInsertCnt],
                   pstBatDscpBlk->aucDataLen[ulActiveInsertCnt]);
        pstQueueNode->ucPriDataLen = pstBatDscpBlk->aucDataLen[ulActiveInsertCnt];

#if (1 == DICC_DFX_SWITCH)
        /* 插入次数++ */
        (pstDFx->astChanStatus[ucChnId].stStatistics.ulInsertCnt)++;
        pstDFx->astChanStatus[ucChnId].stStatistics.ulInsertPid      = ulPid;
        pstDFx->astChanStatus[ucChnId].stStatistics.ulLastInsertTime = ulCurrTime;
#endif

        ulActiveInsertCnt ++;

        /* 向核间插入信息数据 */
        TTF_RING_Q_In(ulPid, (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));
    }

    if (PS_TRUE == pstBatDscpBlk->enAutoTrigTx)
    {
        DICC_TriggerChanDataTx(ulPid, ucChnId, enCpuId);
    }

    /* 释放信号量 */
    VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

    return DICC_OK;
}    /* DICC_InsertChannelData */
/*lint -restore */

#endif  /*FEATURE_ON == FEATURE_CSD*/

#ifdef  __cplusplus
 #if  __cplusplus
}
 #endif
#endif



