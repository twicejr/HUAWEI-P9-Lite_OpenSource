

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MTA_CTX_C

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "TafMtaCtx.h"
#include "TafMtaComm.h"

#include "NVIM_Interface.h"



/*****************************************************************************
  2 全局变量声明
*****************************************************************************/
/* MTA模块运行上下文资源 */
TAF_MTA_CONTEXT_STRU            g_stTafMtaCtx;

/*****************************************************************************
  3 函数声明
*****************************************************************************/

TAF_MTA_AGPS_CTX_STRU*  TAF_MTA_GetMtaAgpsCtxAddr( VOS_VOID )
{
    return &(g_stTafMtaCtx.stAgpsCtx);
}


TAF_MTA_CONTEXT_STRU*  TAF_MTA_GetMtaCtxAddr( VOS_VOID )
{
    return &(g_stTafMtaCtx);
}


TAF_MTA_TIMER_CTX_STRU*  TAF_MTA_GetTimerCtxAddr( VOS_VOID )
{
    return g_stTafMtaCtx.astTimerCtx;
}


TAF_MTA_RF_LCD_CTX_STRU* TAF_MTA_GetRfLcdCtxAddr( VOS_VOID )
{
    return &g_stTafMtaCtx.stMtaRfLcdCtx;
}


VOS_VOID  TAF_MTA_InitRfLcdIntrusionCtx(
    TAF_MTA_RF_LCD_CTX_STRU            *pstRfLcdCtx
)
{
    VOS_UINT32                          ulRet;
    MTC_RF_LCD_TIMER_INTERVAL_STRU      stRfLcdTimerInterval;
    MTC_NVIM_RF_LCD_CFG_STRU            stRfLcdCfg;

    /* 初始化 */
    PS_MEM_SET(&stRfLcdCfg, 0x0, sizeof(MTC_NVIM_RF_LCD_CFG_STRU));
    PS_MEM_SET(&stRfLcdTimerInterval, 0x0, sizeof(MTC_RF_LCD_TIMER_INTERVAL_STRU));
    PS_MEM_SET(pstRfLcdCtx, 0x0, sizeof(TAF_MTA_RF_LCD_CTX_STRU));


    /* 读取en_NV_Item_MTC_RF_LCD_TIMER_INTERVAL_CFG NV项 */
    ulRet = NV_Read(en_NV_Item_MTC_RF_LCD_TIMER_INTERVAL_CFG,
                    &stRfLcdTimerInterval,
                    sizeof(MTC_RF_LCD_TIMER_INTERVAL_STRU));
    if (VOS_OK != ulRet)
    {
        MTA_WARNING1_LOG("MTC_ReadRfLcdCfgNv: Read Nv Fail.", en_NV_Item_MTC_RF_LCD_TIMER_INTERVAL_CFG);
        pstRfLcdCtx->ulTimerInterVal = TAF_MTA_RF_LCD_TIMER_INTERVAL_DEFAULT;
    }
    else
    {
        pstRfLcdCtx->ulTimerInterVal = stRfLcdTimerInterval.ulTimerInterval * TIMER_S_TO_MS_1000;
    }

    /* 读取en_NV_Item_MTC_RF_LCD_CFG NV项 */
    ulRet = NV_Read(en_NV_Item_MTC_RF_LCD_CFG,
                    &stRfLcdCfg,
                    sizeof(MTC_NVIM_RF_LCD_CFG_STRU));
    if (VOS_OK != ulRet)
    {
        pstRfLcdCtx->usEnableBitMap = 0;
    }
    else
    {
        pstRfLcdCtx->usEnableBitMap = stRfLcdCfg.usEnableBitMap;
    }

    pstRfLcdCtx->usNewMipiClk    = 0x0000;
    pstRfLcdCtx->usReportMipiClk = 0x0000;

    return;
}



VOS_VOID  TAF_MTA_InitCmdBufferQueue(
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBufferQueue
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < TAF_MTA_MAX_CMD_BUFFER_QUEUE_SIZE; i++ )
    {
        pstCmdBufferQueue[i].enTimerId      = TI_TAF_MTA_TIMER_BUTT;
        pstCmdBufferQueue[i].pucMsgInfo     = VOS_NULL_PTR;
        pstCmdBufferQueue[i].ulMsgInfoLen   = 0;
    }

    return;
}


TAF_MTA_CMD_BUFFER_STRU  *TAF_MTA_GetCmdBufferQueueAddr( VOS_VOID )
{
    return g_stTafMtaCtx.astCmdBufferQueue;
}


VOS_VOID  TAF_MTA_DelItemInCmdBufferQueue(
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId
)
{
    VOS_UINT32                          i;
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBufferQueue;

    pstCmdBufferQueue = TAF_MTA_GetCmdBufferQueueAddr();

    for ( i = 0; i < TAF_MTA_MAX_CMD_BUFFER_QUEUE_SIZE; i++ )
    {
        if (enTimerId == pstCmdBufferQueue[i].enTimerId)
        {
            /* 如果有缓存的消息，释放消息内存 */
            if (VOS_NULL_PTR != pstCmdBufferQueue[i].pucMsgInfo)
            {
                PS_MEM_FREE(UEPS_PID_MTA, pstCmdBufferQueue[i].pucMsgInfo);
            }

            /* 初始化 */
            pstCmdBufferQueue[i].pucMsgInfo     = VOS_NULL_PTR;
            pstCmdBufferQueue[i].enTimerId      = TI_TAF_MTA_TIMER_BUTT;
            pstCmdBufferQueue[i].ulMsgInfoLen   = 0;

            break;
        }
    }

    return;
}


VOS_VOID  TAF_MTA_SaveItemInCmdBufferQueue(
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT8                          *pucMsgInfo,
    VOS_UINT32                          ulMsgInfoLen
)
{
    VOS_UINT32                          i;
    VOS_UINT8                          *pucMsgBuf;
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBufferQueue;

    /* 如果消息指针为空，直接返回 */
    if (VOS_NULL_PTR == pucMsgInfo)
    {
        return;
    }

    pstCmdBufferQueue = TAF_MTA_GetCmdBufferQueueAddr();

    for ( i = 0; i < TAF_MTA_MAX_CMD_BUFFER_QUEUE_SIZE; i++ )
    {
        if (TI_TAF_MTA_TIMER_BUTT == pstCmdBufferQueue[i].enTimerId)
        {
            break;
        }
    }

    /* 判定当前的循环队列是否已经满了，如果满了则直接返回，进行异常打印 */
    if ( i >= TAF_MTA_MAX_CMD_BUFFER_QUEUE_SIZE )
    {
        /* 缓存队列已满 */
        MTA_WARNING2_LOG("TAF_MTA_SaveItemInCmdBufferQueue, Buffer Full, Timer Id :",
                         UEPS_PID_MTA,
                         enTimerId);

        return;
    }

    /* 在队列增加相应的信息，分配内存，进行信息赋值 */
    pucMsgBuf = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_MTA, ulMsgInfoLen);
    if (VOS_NULL_PTR == pucMsgBuf)
    {
        /* 内存分配失败 */
        MTA_WARNING2_LOG("TAF_MTA_SaveItemInCmdBufferQueue, Mem Alloc Fail, Timer Id :",
                         UEPS_PID_MTA,
                         enTimerId );
        return;
    }

    /* 赋值 */
    PS_MEM_CPY((VOS_UINT8 *)pucMsgBuf, pucMsgInfo, ulMsgInfoLen);
    pstCmdBufferQueue[i].pucMsgInfo     = pucMsgBuf;
    pstCmdBufferQueue[i].enTimerId      = enTimerId;
    pstCmdBufferQueue[i].ulMsgInfoLen   = ulMsgInfoLen;

    return;
}


TAF_MTA_CMD_BUFFER_STRU  *TAF_MTA_GetItemFromCmdBufferQueue(
    TAF_MTA_TIMER_ID_ENUM_UINT32                enTimerId
)
{
    VOS_UINT32                          i;
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBufferQueue;


    pstCmdBufferQueue = TAF_MTA_GetCmdBufferQueueAddr();

    /* 遍历队列, 获取enTimerId指定的消息节点 */
    for ( i = 0; i < TAF_MTA_MAX_CMD_BUFFER_QUEUE_SIZE; i++ )
    {
        if (enTimerId == pstCmdBufferQueue[i].enTimerId)
        {
            break;
        }
    }

    /* 判定当前的循环队列是否已经满了，如果满了则直接返回，进行异常打印 */
    if ( i >= TAF_MTA_MAX_CMD_BUFFER_QUEUE_SIZE )
    {
        /* 未找到 */
        MTA_WARNING2_LOG("TAF_MTA_GetItemFromCmdBufferQueue, Msg Not Found, Timer Id :",
                         UEPS_PID_MTA,
                         enTimerId);

        return VOS_NULL_PTR;
    }

    /* 将缓存的消息指针返回 */
    return &pstCmdBufferQueue[i];
}


VOS_VOID TAF_MTA_InitRefClockInfo(
    TAF_MTA_REFCLOCK_INFO_STRU         *pstRefClockInfo
)
{
    PS_MEM_SET(pstRefClockInfo, 0, sizeof(TAF_MTA_REFCLOCK_INFO_STRU));

    pstRefClockInfo->enRptFlg       = AT_MTA_CMD_RPT_FLG_OFF;
    pstRefClockInfo->ulFreq         = TAF_MTA_REFCLOCK_DEFAULT_FREQ;
    pstRefClockInfo->ulPrecision    = TAF_MTA_REFCLOCK_DEFAULT_PRECISION;
    pstRefClockInfo->enStatus       = PHY_MTA_REFCLOCK_UNLOCKED;

    return;
}


TAF_MTA_REFCLOCK_INFO_STRU* TAF_MTA_GetRefClockInfo(VOS_VOID)
{
    return &(g_stTafMtaCtx.stAgpsCtx.stRefClockInfo);
}



VOS_VOID TAF_MTA_InitEcidCfg(
    TAF_NVIM_ECID_TL2GSM_CFG_STRU      *pstEcidCfg
)
{
    TAF_NVIM_ECID_TL2GSM_CFG_STRU       stNvTmp;

    PS_MEM_SET(&stNvTmp, 0, sizeof(stNvTmp));
    PS_MEM_SET(pstEcidCfg, 0, sizeof(TAF_NVIM_ECID_TL2GSM_CFG_STRU));

    /* 读取NV项 */
    if (NV_OK == NV_Read(en_NV_Item_ECID_TL2GSM_CFG,
                         &stNvTmp,
                         sizeof(TAF_NVIM_ECID_TL2GSM_CFG_STRU)))
    {
        /* NV有效性检查 */
        if ( (VOS_TRUE == stNvTmp.ucEnableFlg)
          && (TAF_MTA_INVALID_MCC > stNvTmp.usMcc) )
        {
            pstEcidCfg->ucEnableFlg = stNvTmp.ucEnableFlg;
            pstEcidCfg->usMcc       = stNvTmp.usMcc;
            return;
        }
    }

    return;
}


TAF_NVIM_ECID_TL2GSM_CFG_STRU* TAF_MTA_GetEcidCfg(VOS_VOID)
{
    return &(g_stTafMtaCtx.stAgpsCtx.stEcidCfg);
}



VOS_VOID  TAF_MTA_InitNetmonGsmInfo(
    TAF_MTA_NETMON_GSM_INFO_STRU       *pstNetmonGsmInfo
)
{
    pstNetmonGsmInfo->enNetMonGsmState = MTA_AT_NETMON_GSM_STATE_INIT;
    PS_MEM_SET(&pstNetmonGsmInfo->stNetMonCellInfoCnf, 0x0, sizeof(pstNetmonGsmInfo->stNetMonCellInfoCnf));

    return;
}


MTA_AT_NETMON_GSM_STATE_ENUM_UINT32  TAF_MTA_GetNetmonGsmState(VOS_VOID)
{
    return g_stTafMtaCtx.stNetmonGsmInfo.enNetMonGsmState;
}


VOS_VOID  TAF_MTA_SetNetmonGsmState(
    MTA_AT_NETMON_GSM_STATE_ENUM_UINT32 enNetMonGsmState
)
{
    g_stTafMtaCtx.stNetmonGsmInfo.enNetMonGsmState = enNetMonGsmState;

    return;
}


MTA_AT_NETMON_CELL_INFO_STRU*  TAF_MTA_GetNetmonCellInfo(VOS_VOID)
{
    return &(g_stTafMtaCtx.stNetmonGsmInfo.stNetMonCellInfoCnf);
}


#if(FEATURE_ON == FEATURE_LTE)

TAF_MTA_COEX_PARA_STRU*  TAF_MTA_GetIsmCoexAddr( VOS_VOID )
{
    return g_stTafMtaCtx.astIsmCoex;
}


VOS_VOID  TAF_MTA_InitIsmCoex(
    TAF_MTA_COEX_PARA_STRU              *pstMtaCoexPara
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < TAF_MTA_ISMCOEX_BANDWIDTH_NUM; i++)
    {
        PS_MEM_SET(pstMtaCoexPara + i, 0x00, sizeof(TAF_MTA_COEX_PARA_STRU));
    }

    return;
}
#endif


#if (FEATURE_ON == FEATURE_PTM)

VOS_VOID  TAF_MMA_InitInfoCltCtx(
    TAF_MTA_INFO_CLT_CTX_STRU          *pstInfoCltCtx
)
{
    pstInfoCltCtx->pstFreqInfoCltCtx =  VOS_NULL_PTR;

    TAF_MTA_ClrAllWaitFreqCltCnfFlag();

    TAF_MMA_ClearNetworkInfo();

    TAF_MTA_ClrAllWaitNetworkInfoCnfFlag();
    return;
}

/*lint -e429 -e830*/

VOS_VOID  TAF_MMA_AllocFreqInfoCltCtx(VOS_VOID)
{
    TAF_MTA_INFO_CLT_CTX_STRU                  *pstInfoCltCtx  = VOS_NULL_PTR;
    NAS_INFO_CLT_CLOUD_FREQ_BAND_EVENT_STRU    *pstFreqInfoClt = VOS_NULL_PTR;
    VOS_UINT32                                  ulLength;

    /* 获取MTA上下文中保存云通信频点采集上下文 */
    pstInfoCltCtx  = TAF_MTA_GetInfoCltAddr();

    /* 分配内存给云通信频点采集上下文和初始化 */
    ulLength         = sizeof(NAS_INFO_CLT_CLOUD_FREQ_BAND_EVENT_STRU);
    pstFreqInfoClt   = (NAS_INFO_CLT_CLOUD_FREQ_BAND_EVENT_STRU *)PS_MEM_ALLOC(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstFreqInfoClt)
    {
        MTA_ERROR_LOG("TAF_MMA_AllocFreqInfoCltCtx: Alloc msg fail!");
        return;
    }

    PS_MEM_SET(pstFreqInfoClt, 0, ulLength);

    pstInfoCltCtx->pstFreqInfoCltCtx = pstFreqInfoClt;

    return;
}
/*lint +e429 +e830*/


VOS_VOID  TAF_MMA_FreeFreqInfoCltCtx(VOS_VOID)
{
    TAF_MTA_INFO_CLT_CTX_STRU                   *pstInfoCltCtx;

    pstInfoCltCtx = TAF_MTA_GetInfoCltAddr();

    if (VOS_NULL_PTR == pstInfoCltCtx->pstFreqInfoCltCtx)
    {
        return;
    }

    PS_MEM_FREE(UEPS_PID_MTA, pstInfoCltCtx->pstFreqInfoCltCtx);

    pstInfoCltCtx->pstFreqInfoCltCtx = VOS_NULL_PTR;

    return;
}


TAF_MTA_INFO_CLT_CTX_STRU*  TAF_MTA_GetInfoCltAddr(VOS_VOID)
{
    return &g_stTafMtaCtx.stInfoCltCtx;
}


VOS_UINT8 TAF_MTA_GetWaitFreqCltCnfFlag(VOS_VOID)
{
    return g_stTafMtaCtx.stInfoCltCtx.ucWaitFreqCltCnfFlag;
}


VOS_VOID TAF_MTA_SetWaitFreqCltCnfFlag(
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_ENUM_UINT8       enFreqCltCnf
)
{
    g_stTafMtaCtx.stInfoCltCtx.ucWaitFreqCltCnfFlag |= enFreqCltCnf;
}


VOS_VOID TAF_MTA_ClrWaitFreqCltCnfFlag(
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_ENUM_UINT8       enFreqCltCnf
)
{
    g_stTafMtaCtx.stInfoCltCtx.ucWaitFreqCltCnfFlag &= (~enFreqCltCnf);
}


VOS_VOID TAF_MTA_ClrAllWaitFreqCltCnfFlag(VOS_VOID)
{
    g_stTafMtaCtx.stInfoCltCtx.ucWaitFreqCltCnfFlag = TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_NULL;
}


VOS_VOID  TAF_MMA_ClearNetworkInfo(VOS_VOID)
{
    PS_MEM_SET(&(g_stTafMtaCtx.stInfoCltCtx.stNetworkInfo), 0, sizeof(TAF_NETWORK_INFO_CLT_CTX_STRU));
}

VOS_VOID TAF_MTA_ClrAllWaitNetworkInfoCnfFlag(VOS_VOID)
{
    g_stTafMtaCtx.stInfoCltCtx.ucWaitNetworkInfoCnfFlag = TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_NULL;
}


VOS_UINT8 TAF_MTA_GetWaitNetworkInfoCnfFlag(VOS_VOID)
{
    return g_stTafMtaCtx.stInfoCltCtx.ucWaitNetworkInfoCnfFlag;
}


VOS_VOID TAF_MTA_SetWaitNetworkInfoCnfFlag(
    TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_ENUM_UINT8           enNetworkInfoCltCnfFlag
)
{
    g_stTafMtaCtx.stInfoCltCtx.ucWaitNetworkInfoCnfFlag |= enNetworkInfoCltCnfFlag;
}


VOS_VOID TAF_MTA_ClrWaitNetworkInfoCnfFlag(
    TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_ENUM_UINT8           enNetworkInfoCltCnfFlag
)
{
    g_stTafMtaCtx.stInfoCltCtx.ucWaitNetworkInfoCnfFlag &= (~enNetworkInfoCltCnfFlag);
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
