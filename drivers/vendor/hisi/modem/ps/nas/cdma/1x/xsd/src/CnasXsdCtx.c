

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CnasCcb.h"
#include "CnasXsdCtx.h"
#include "PsCommonDef.h"
#include "CnasMntn.h"
#include "CnasXsdFsmMainTbl.h"
#include "CnasXsdFsmSwitchOnTbl.h"
#include "CnasXsdFsmPowerOffTbl.h"
#include "CnasXsdFsmSysAcqTbl.h"
#include "CnasPrlApi.h"
#include "CnasXsdMntn.h"
#include "CnasXsdProcNvim.h"
#include "CnasXsdFsmRedirTbl.h"
#include "Nas_Mem.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_CTX_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* XSD CTX,用于保存MMC状态机,描述表 */
CNAS_XSD_CTX_STRU                       g_stCnasXsdCtx;

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

VOS_VOID CNAS_XSD_InitCurrFsmCtx(
    CNAS_XSD_FSM_CTX_STRU              *pstCurrFsmCtx
)
{
    pstCurrFsmCtx->enFsmId                  =   CNAS_XSD_FSM_L1_MAIN;
    pstCurrFsmCtx->pstFsmDesc               =   CNAS_XSD_GetMainFsmDescAddr();
    pstCurrFsmCtx->ulState                  =   CNAS_XSD_L1_STA_NULL;
    pstCurrFsmCtx->enParentFsmId            =   CNAS_XSD_BUTT;
    pstCurrFsmCtx->ulParentEventType        =   0;

    pstCurrFsmCtx->stEntryMsg.ulEventType   =   0;
    NAS_MEM_SET_S(pstCurrFsmCtx->stEntryMsg.aucMsgBuffer,
                  sizeof(pstCurrFsmCtx->stEntryMsg.aucMsgBuffer),
                  0x00,
                  CNAS_XSD_MAX_MSG_BUFFER_LEN);

    NAS_MEM_SET_S(&(pstCurrFsmCtx->unFsmCtx),
                  sizeof(pstCurrFsmCtx->unFsmCtx),
                  0x00,
                  sizeof(CNAS_XSD_FSM_EXTRA_CTX_UNION));
}


VOS_VOID CNAS_XSD_InitFsmStackCtx(
    CNAS_XSD_FSM_STACK_STRU            *pstFsmStack
)
{
    VOS_UINT32                          i;

    pstFsmStack->usStackDepth   = 0;
    pstFsmStack->usStackPopFlg  = VOS_FALSE;

    for (i = 0 ; i < CNAS_XSD_MAX_FSM_STACK_DEPTH ; i++)
    {
        pstFsmStack->astFsmStack[i].pstFsmDesc  = VOS_NULL_PTR;
        pstFsmStack->astFsmStack[i].enFsmId     = CNAS_XSD_BUTT;
        pstFsmStack->astFsmStack[i].ulState     = CNAS_XSD_L1_STA_BUTT;
    }
}



VOS_VOID CNAS_XSD_InitCacheMsgQueue(
    CNAS_XSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType,
    CNAS_XSD_CACHE_MSG_QUEUE_STRU      *pstCacheMsgQueue
)
{
    VOS_UINT32                          i;

    if (CNAS_XSD_INIT_CTX_STARTUP == enInitType)
    {
        pstCacheMsgQueue->ucCacheMsgNum = 0;

        for (i = 0; i < CNAS_XSD_MAX_CACHE_MSG_QUEUE_NUM; i++)
        {
            pstCacheMsgQueue->pastCacheMsg[i] = VOS_NULL_PTR;
        }
    }
    else
    {
        /* 关机时对于未执行完的缓存需要清除,避免内存泄漏 */
        for (i = 0; i < (VOS_UINT32)pstCacheMsgQueue->ucCacheMsgNum; i++)
        {
            if (VOS_NULL_PTR != pstCacheMsgQueue->pastCacheMsg[i])
            {
                PS_MEM_FREE(UEPS_PID_XSD, pstCacheMsgQueue->pastCacheMsg[i]);
                pstCacheMsgQueue->pastCacheMsg[i] = VOS_NULL_PTR;
            }
        }

        pstCacheMsgQueue->ucCacheMsgNum = 0;
    }

}


VOS_VOID CNAS_XSD_InitScanChanList(
    CNAS_XSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    if (CNAS_XSD_INIT_CTX_STARTUP == enInitType)
    {
        pstScanChanList->usCurScanIndex     = 0;
        pstScanChanList->usTotalNum         = 0;
        pstScanChanList->pstScanChanInfo    = VOS_NULL_PTR;

        return;
    }

    if (CNAS_XSD_INIT_CTX_POWEROFF == enInitType)
    {
        if (VOS_NULL_PTR != pstScanChanList->pstScanChanInfo)
        {
            PS_MEM_FREE(UEPS_PID_XSD, pstScanChanList->pstScanChanInfo);
            pstScanChanList->pstScanChanInfo = VOS_NULL_PTR;
        }

        pstScanChanList->usCurScanIndex = 0;
        pstScanChanList->usTotalNum  = 0;
    }

    return;
}


VOS_VOID CNAS_XSD_InitCurCampedSysInfo(
    CNAX_XSD_CAMPED_SYS_INFO_STRU      *pstCurCampedSysInfo
)
{
    NAS_MEM_SET_S(pstCurCampedSysInfo, sizeof(CNAX_XSD_CAMPED_SYS_INFO_STRU), 0, sizeof(CNAX_XSD_CAMPED_SYS_INFO_STRU));

    pstCurCampedSysInfo->ucRoamingInd = VOS_FALSE;
    pstCurCampedSysInfo->enSysType    = CNAS_XSD_SYS_TYPE_BUTT;
    pstCurCampedSysInfo->enSrvStatus  = CNAS_XSD_SERVICE_STATUS_NO_SERVICE;

    CNAS_CCB_SetCur1XSrvStatus(CNAS_CCB_SERVICE_STATUS_NO_SERVICE);

    return;
}


VOS_VOID CNAS_XSD_InitCallRedialCtrlInfo(
    CNAS_XSD_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    CNAS_XSD_CALL_REDIAL_CTRL_INFO_STRU *pstCallRedialInfo
)
{
    if (CNAS_XSD_INIT_CTX_POWEROFF == enInitType)
    {
        if (VOS_NULL_PTR != pstCallRedialInfo->stCallRedialChanScanList.pstScanChanInfo)
        {
            PS_MEM_FREE(UEPS_PID_XSD, pstCallRedialInfo->stCallRedialChanScanList.pstScanChanInfo);
        }
    }

    NAS_MEM_SET_S(pstCallRedialInfo, sizeof(CNAS_XSD_CALL_REDIAL_CTRL_INFO_STRU), 0, sizeof(CNAS_XSD_CALL_REDIAL_CTRL_INFO_STRU));

    pstCallRedialInfo->ucCallExistFlg                           = CNAS_XSD_CALL_EXIST_NULL_FLAG;
    pstCallRedialInfo->stCallRedialChanScanList.pstScanChanInfo = VOS_NULL_PTR;

    return;
}



VOS_VOID CNAS_XSD_InitEmcCallCtrlInfo(
    CNAS_XSD_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    CNAS_XSD_EMC_CALL_CTRL_INFO_STRU    *pstEmcCallInfo
)
{
    if (CNAS_XSD_INIT_CTX_POWEROFF == enInitType)
    {
        if (VOS_NULL_PTR != pstEmcCallInfo->stEmcCallRedialChanScanList.pstScanChanInfo)
        {
            PS_MEM_FREE(UEPS_PID_XSD, pstEmcCallInfo->stEmcCallRedialChanScanList.pstScanChanInfo);
        }
    }

    NAS_MEM_SET_S(pstEmcCallInfo, sizeof(CNAS_XSD_EMC_CALL_CTRL_INFO_STRU), 0x00, sizeof(CNAS_XSD_EMC_CALL_CTRL_INFO_STRU));

    return;
}


VOS_VOID CNAS_XSD_InitAvailSysList(
    CNAS_XSD_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    CNAS_XSD_AVAILABLE_LIST_STRU        *pstAvailList
)
{
    NAS_MEM_SET_S(pstAvailList,
                  sizeof(CNAS_XSD_AVAILABLE_LIST_STRU),
                  0,
                  sizeof(CNAS_XSD_AVAILABLE_LIST_STRU));

    return;
}


VOS_VOID CNAS_XSD_InitRedirectionInfo(
    CNAS_XSD_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    CNAS_XSD_REDIRECTION_INFO_STRU      *pstRedirInfo
)
{
    pstRedirInfo->ucRedirection   = VOS_FALSE;
    pstRedirInfo->ucReturnIfFail  = VOS_FALSE;
    pstRedirInfo->ucChanNum       = 0;

    pstRedirInfo->stOriginalSystem.usSid = CNAS_PRL_WILDCARD_SID;
    pstRedirInfo->stOriginalSystem.usNid = CNAS_PRL_WILDCARD_NID;
    pstRedirInfo->usExpectSid            = CNAS_PRL_WILDCARD_SID;
    pstRedirInfo->usExpectNid            = CNAS_PRL_WILDCARD_NID;
    pstRedirInfo->ucIsEmcRedir           = VOS_FALSE;

    NAS_MEM_SET_S(&(pstRedirInfo->astChanInfo[0]),
                  sizeof(pstRedirInfo->astChanInfo),
                  0x0,
                  sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * CNAS_XSD_MAX_REDIR_CHANNEL_NUM);

    return;
}




VOS_VOID CNAS_XSD_InitSystemAcquireCtrl(
    CNAS_XSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType,
    CNAS_XSD_SYSTEM_ACQUIRE_CTRL_STRU  *pstSysAcqCtrl
)
{


    NAS_MEM_SET_S(&(pstSysAcqCtrl->stAvoidFreqList), sizeof(pstSysAcqCtrl->stAvoidFreqList), 0, sizeof(CNAS_XSD_AVOID_FREQ_LIST_STRU));

    NAS_MEM_SET_S(&(pstSysAcqCtrl->stMruList), sizeof(pstSysAcqCtrl->stMruList), 0, sizeof(CNAS_XSD_MRU_LIST_STRU));

    NAS_MEM_SET_S(&(pstSysAcqCtrl->stCallList), sizeof(pstSysAcqCtrl->stCallList), 0, sizeof(CNAS_XSD_CALL_REDIAL_SYS_LIST_STRU));

    NAS_MEM_SET_S(&(pstSysAcqCtrl->unUeSupportedBand.ulBand), sizeof(pstSysAcqCtrl->unUeSupportedBand.ulBand), 0x0, sizeof(VOS_UINT32));
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_0 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_1 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_2 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_3 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_4 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_5 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_6 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_7 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_8 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_9 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_10 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_11 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_12 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_13 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_14 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_15 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_16 = VOS_TRUE;

    CNAS_XSD_InitScanChanList(enInitType, &(pstSysAcqCtrl->stChanScanList));


    CNAS_XSD_InitCurCampedSysInfo(&(pstSysAcqCtrl->stCurCampedSysInfo));

    CNAS_XSD_InitCallRedialCtrlInfo(enInitType, &pstSysAcqCtrl->stCallRedialInfo);

    CNAS_XSD_InitRedirectionInfo(enInitType, &pstSysAcqCtrl->stRedirInfo);

    CNAS_XSD_InitOocScheduleInfo(&(pstSysAcqCtrl->stOocScheduleInfo));

    CNAS_XSD_InitEmcCallCtrlInfo(enInitType, &(pstSysAcqCtrl->stEmcCallInfo));

    NAS_MEM_SET_S(&(pstSysAcqCtrl->stCdma1XCustomPrefChan),
                  sizeof(pstSysAcqCtrl->stCdma1XCustomPrefChan),
                  0,
                  sizeof(CNAS_XSD_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU));

    CNAS_XSD_SetSrvAcqFlg(VOS_FALSE);

    CNAS_XSD_InitHistorySyncedSysFreqList(&(pstSysAcqCtrl->stHisSyncedSysFreqList));

    CNAS_XSD_InitGeoSrchListInfo(&(pstSysAcqCtrl->stGeoListSrchInfo));
}


VOS_VOID CNAS_XSD_InitFsmCtx_L1Main(VOS_VOID)
{
    CNAS_XSD_CTX_STRU                  *pstXsdCtx = VOS_NULL_PTR;

    pstXsdCtx = CNAS_XSD_GetXsdCtxAddr();

    /* 检查当前状态机是否是L1状态机 */
    if (CNAS_XSD_FSM_L1_MAIN != CNAS_XSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_InitFsmCtx_L1Main:ENTERED");

        return;
    }

    pstXsdCtx->stCurFsm.unFsmCtx.stL1MainCtx.ulCurAvailableTimerCount = 0;
}


VOS_VOID CNAS_XSD_InitFsmCtx_SwitchOn(VOS_VOID)
{
    CNAS_XSD_CTX_STRU                  *pstXsdCtx = VOS_NULL_PTR;

    pstXsdCtx = CNAS_XSD_GetXsdCtxAddr();

    /* 检查当前状态机是否时开机状态机 */
    if (CNAS_XSD_FSM_SWITCH_ON != CNAS_XSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_InitFsmCtx_SwitchOn:ENTERED");

        return;
    }

    pstXsdCtx->stCurFsm.unFsmCtx.stSwitchOnCtx.ulXsdReadCardFileFlg = CNAS_XSD_READ_CARD_FILE_FLG_NULL;
}



VOS_VOID CNAS_XSD_InitFsmCtx_PowerOff(VOS_VOID)
{
    CNAS_XSD_CTX_STRU                  *pstXsdCtx = VOS_NULL_PTR;

    pstXsdCtx = CNAS_XSD_GetXsdCtxAddr();

    /* 检查当前状态机是否为关机状态机 */
    if (CNAS_XSD_FSM_POWER_OFF != CNAS_XSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_InitFsmCtx_PowerOff:ENTERED");

        return;
    }

    pstXsdCtx->stCurFsm.unFsmCtx.stPowerOffCtx.ucCampOnNeedFlg      = VOS_FALSE;
    pstXsdCtx->stCurFsm.unFsmCtx.stPowerOffCtx.ucBufCallRelIndFlg   = VOS_FALSE;

    NAS_MEM_SET_S(&(pstXsdCtx->stCurFsm.unFsmCtx.stPowerOffCtx.stBuffCallRelFreq),
                  sizeof(pstXsdCtx->stCurFsm.unFsmCtx.stPowerOffCtx.stBuffCallRelFreq),
                  0x0,
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU));
}



VOS_VOID CNAS_XSD_InitFsmCtx_SysAcq(VOS_VOID)
{
    CNAS_XSD_CTX_STRU                  *pstXsdCtx = VOS_NULL_PTR;

    pstXsdCtx = CNAS_XSD_GetXsdCtxAddr();

    /* 检查当前状态机是否时SYSTEM ACQUIRE状态机 */
    if (CNAS_XSD_FSM_SYS_ACQ != CNAS_XSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_InitFsmCtx_SysAcq:ENTERED");

        return;
    }

    /* 退出L2捕获状态机前，确保内存释放 */
    if (VOS_NULL_PTR != pstXsdCtx->stCurFsm.unFsmCtx.stSysAcqCtx.stGeoSysSrchList.pstAcqSysInfo)
    {
        PS_MEM_FREE(UEPS_PID_XSD, pstXsdCtx->stCurFsm.unFsmCtx.stSysAcqCtx.stGeoSysSrchList.pstAcqSysInfo);
    }

    NAS_MEM_SET_S(&(pstXsdCtx->stCurFsm.unFsmCtx.stSysAcqCtx),
                  sizeof(pstXsdCtx->stCurFsm.unFsmCtx.stSysAcqCtx),
                  0,
                  sizeof(CNAS_XSD_FSM_SYS_ACQ_CTX_STRU));

    return;
}



VOS_VOID CNAS_XSD_InitFsmCtx_Redirection(VOS_VOID)
{
    CNAS_XSD_CTX_STRU                  *pstXsdCtx = VOS_NULL_PTR;

    pstXsdCtx = CNAS_XSD_GetXsdCtxAddr();

    /* Checking for current state machine is redirection or not */
    if (CNAS_XSD_FSM_REDIRECTION != CNAS_XSD_GetCurrFsmId())
    {
        /* abnormal event */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_InitFsmCtx_Redirection:ENTERED");

        return;
    }

    pstXsdCtx->stCurFsm.unFsmCtx.stRedirCtx.ucAbortFlag                      = VOS_FALSE;
    pstXsdCtx->stCurFsm.unFsmCtx.stRedirCtx.stRedireScanList.usTotalNum      = 0;
    pstXsdCtx->stCurFsm.unFsmCtx.stRedirCtx.stRedireScanList.usCurScanIndex  = 0;
    pstXsdCtx->stCurFsm.unFsmCtx.stRedirCtx.stRedireScanList.pstScanChanInfo = VOS_NULL_PTR;

    return;
}



VOS_VOID CNAS_XSD_InitCtx(
    CNAS_XSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType
)
{
    CNAS_XSD_CTX_STRU                  *pstXsdCtx = VOS_NULL_PTR;

    pstXsdCtx = CNAS_XSD_GetXsdCtxAddr();

    /* 当前不处理开机原因值，后续会扩展 */

    /* 当前的状态机数组初始化 */
    CNAS_XSD_InitCurrFsmCtx(&(pstXsdCtx->stCurFsm));

    /* 状态机栈数组初始化 */
    CNAS_XSD_InitFsmStackCtx(&(pstXsdCtx->stFsmStack));

    /* CNAS XSD缓存消息队列初始化 */
    CNAS_XSD_InitCacheMsgQueue(enInitType, &(pstXsdCtx->stCacheMsgQueue));

    /* CNAS XSD缓存内部消息队列初始化 */
    CNAS_XSD_InitInternalBuffer(&(CNAS_XSD_GetXsdCtxAddr()->stIntMsgQueue));

    /* CNAS XSD系统获取控制初始化 */
    CNAS_XSD_InitSystemAcquireCtrl(enInitType, &(pstXsdCtx->stSysAcqCtrl));

    CNAS_XSD_InitCFreqLockValue();

    CNAS_XSD_InitTestConfig(&(pstXsdCtx->stTestConfig));

    CNAS_XSD_InitSysAcqNvimCfg(&(pstXsdCtx->stSysAcqNvimCfg));
    CNAS_CCB_Set1xReturnCause(CNAS_CCB_1X_RETURN_CAUSE_NORMAL_ACCESS);
}


VOS_VOID  CNAS_XSD_LoadSubFsm(
    CNAS_XSD_FSM_ID_ENUM_UINT32         enFsmId,
    CNAS_XSD_FSM_CTX_STRU              *pstCurFsm
)
{
    switch (enFsmId)
    {
        case CNAS_XSD_FSM_SWITCH_ON :
            pstCurFsm->ulState                  = CNAS_XSD_SWITCH_ON_STA_INIT;
            pstCurFsm->pstFsmDesc               = CNAS_XSD_GetSwitchOnFsmDescAddr();
            break;

        case CNAS_XSD_FSM_POWER_OFF :
            pstCurFsm->ulState                  = CNAS_XSD_POWER_OFF_STA_INIT;
            pstCurFsm->pstFsmDesc               = CNAS_XSD_GetPowerOffFsmDescAddr();
            break;

        case CNAS_XSD_FSM_SYS_ACQ:
            pstCurFsm->ulState                  = CNAS_XSD_SYS_ACQ_STA_INIT;
            pstCurFsm->pstFsmDesc               = CNAS_XSD_GetSysAcqFsmDescAddr();
            break;

        case CNAS_XSD_FSM_REDIRECTION:
            pstCurFsm->ulState                  = CNAS_XSD_REDIR_STA_INIT;
            pstCurFsm->pstFsmDesc               = CNAS_XSD_GetRedirFsmDescAddr();
            break;

        default:
            CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LoadSubFsm:Invalid Fsm Id");
            return;
    }

    /*执行初始化L2状态机的函数*/
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }
}


VOS_VOID CNAS_XSD_PushFsm(
    CNAS_XSD_FSM_STACK_STRU            *pstFsmStack,
    CNAS_XSD_FSM_CTX_STRU              *pstNewFsm
)
{
    CNAS_XSD_FSM_CTX_STRU              *pstCurFsm = VOS_NULL_PTR;

    /* 入参指针检查 */
    if ((VOS_NULL_PTR == pstFsmStack)
     || (VOS_NULL_PTR == pstNewFsm))
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD,
                       "CNAS_XSD_PushFsm: pstFsmStack or pstNewFsm is null pointer!");

        return;
    }

    /* 栈深度检查 */
    if (pstFsmStack->usStackDepth >= CNAS_XSD_MAX_FSM_STACK_DEPTH)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XSD,
                       "CNAS_XSD_PushFsm: Fsm Stack Depth = %d Error!",
                       pstFsmStack->usStackDepth);

        return;
    }

    /* push当前状态机上下文入栈 */
    pstCurFsm = &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]);

    NAS_MEM_CPY_S(pstCurFsm, sizeof(CNAS_XSD_FSM_CTX_STRU), pstNewFsm, sizeof(CNAS_XSD_FSM_CTX_STRU));

    /* 栈深度增加 */
    pstFsmStack->usStackDepth++;

    return;
}


VOS_VOID CNAS_XSD_PopFsm(VOS_VOID)
{
    CNAS_XSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;
    CNAS_XSD_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;

    /* 根据并行状态机栈弹出的状态机获取当前状态机描述地址  */
    pstFsmStack = CNAS_XSD_GetFsmStackAddr();
    pstCurFsm   = CNAS_XSD_GetCurFsmAddr();

    /* 检查栈空间是否为空 */
    if (0 == pstFsmStack->usStackDepth)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_PopFsm: FSM Stack is empty");

        return;
    }

    /* 状态机栈深度减少 */
    pstFsmStack->usStackDepth--;

    /* 设置当前状态机 */
    NAS_MEM_CPY_S(pstCurFsm,
                  sizeof(CNAS_XSD_FSM_CTX_STRU),
                  &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]),
                  sizeof(CNAS_XSD_FSM_CTX_STRU));
}


VOS_VOID CNAS_XSD_InitFsmL2(
    CNAS_XSD_FSM_ID_ENUM_UINT32         enFsmId
)
{
    CNAS_XSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;
    CNAS_XSD_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;
    CNAS_XSD_FSM_ID_ENUM_UINT32         enParentFsmId;
    VOS_UINT32                          ulParentEventType;
    CNAS_XSD_FSM_ID_ENUM_UINT32         enCurrFsmId;

    enCurrFsmId = CNAS_XSD_GetCurrFsmId();
    if (CNAS_XSD_BUTT == enCurrFsmId)
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_InitFsmL2: CNAS_XSD_GetCurrFsmId return Butt");
    }

    /* 打印压栈前的状态机及状态ID */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_XSD, enCurrFsmId, CNAS_XSD_GetFsmTopState(), 0);

    /* 记录压栈前的状态机名和入口消息类型 */
    enParentFsmId     = CNAS_XSD_GetCurrFsmId();
    ulParentEventType = CNAS_XSD_GetCurFsmAddr()->stEntryMsg.ulEventType;

    /* 将当前状态机压栈操作 */
    pstFsmStack = CNAS_XSD_GetFsmStackAddr();
    pstCurFsm   = CNAS_XSD_GetCurFsmAddr();
    CNAS_XSD_PushFsm(pstFsmStack, pstCurFsm);

    /* 设置当前状态机 */
    pstCurFsm->enFsmId = enFsmId;

    /* 加载L2状态机 */
    CNAS_XSD_LoadSubFsm(enFsmId, pstCurFsm);

    /* 记录上层状态机名和入口消息类型 */
    pstCurFsm->enParentFsmId     = enParentFsmId;
    pstCurFsm->ulParentEventType = ulParentEventType;

    enCurrFsmId = CNAS_XSD_GetCurrFsmId();
    if (CNAS_XSD_BUTT == enCurrFsmId)
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_InitFsmL2: CNAS_XSD_GetCurrFsmId return Butt");
    }

    /* 打印压栈前的状态机及状态ID */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_XSD, enCurrFsmId, CNAS_XSD_GetFsmTopState(), 0);
}


VOS_VOID CNAS_XSD_QuitFsmL2(VOS_VOID)
{
    CNAS_XSD_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;

    CNAS_XSD_FSM_ID_ENUM_UINT32         enCurrFsmId;

    pstCurFsm = CNAS_XSD_GetCurFsmAddr();

    /* QUIT时清空当前L2状态机的CTX */
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }

    enCurrFsmId = CNAS_XSD_GetCurrFsmId();
    if (CNAS_XSD_BUTT == enCurrFsmId)
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_QuitFsmL2: CNAS_XSD_GetCurrFsmId return Butt");
    }

    /*  打印当前的状态机ID以及状态 */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_XSD, enCurrFsmId, CNAS_XSD_GetFsmTopState(), 0);

    /* 状态机出栈操作 */
    CNAS_XSD_PopFsm();

    enCurrFsmId = CNAS_XSD_GetCurrFsmId();
    if (CNAS_XSD_BUTT == enCurrFsmId)
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_QuitFsmL2: CNAS_XSD_GetCurrFsmId return Butt");
    }

    /*  打印当前的状态机ID以及状态 */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_XSD, enCurrFsmId, CNAS_XSD_GetFsmTopState(), 0);

    return;
}


CNAS_XSD_CTX_STRU* CNAS_XSD_GetXsdCtxAddr(VOS_VOID)
{
    return &(g_stCnasXsdCtx);
}


CNAS_XSD_FSM_STACK_STRU* CNAS_XSD_GetFsmStackAddr(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stFsmStack);
}


CNAS_XSD_FSM_CTX_STRU* CNAS_XSD_GetCurFsmAddr(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stCurFsm);
}


VOS_UINT32 CNAS_XSD_GetFsmTopState(VOS_VOID)
{
    return (CNAS_XSD_GetCurFsmAddr()->ulState);
}


NAS_FSM_DESC_STRU* CNAS_XSD_GetCurFsmDesc(VOS_VOID)
{
    return (CNAS_XSD_GetCurFsmAddr()->pstFsmDesc);
}


VOS_UINT16 CNAS_XSD_GetFsmStackDepth(VOS_VOID)
{
    CNAS_XSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = CNAS_XSD_GetFsmStackAddr();

    return pstFsmStack->usStackDepth;
}


VOS_VOID CNAS_XSD_SetFsmStackPopFlg(
    VOS_UINT16                          ucStackPopFlg
)
{
    CNAS_XSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = CNAS_XSD_GetFsmStackAddr();

    pstFsmStack->usStackPopFlg = ucStackPopFlg;
}


VOS_UINT16 CNAS_XSD_GetFsmStackPopFlg(VOS_VOID)
{
    CNAS_XSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = CNAS_XSD_GetFsmStackAddr();

    return pstFsmStack->usStackPopFlg;
}


CNAS_XSD_CACHE_MSG_QUEUE_STRU* CNAS_XSD_GetCacheMsgAddr(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stCacheMsgQueue);
}



CNAS_XSD_AVOID_SCHEDULE_INFO_STRU* CNAS_XSD_GetAvoidScheduInfoAddr(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stAvoidScheduInfo);
}


VOS_UINT8 CNAS_XSD_GetAvoidFreqIndexOfAvoidlist(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstAvoidFreq,
    VOS_UINT8                          *pucIndex
)
{
    VOS_UINT8                           i;
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList = VOS_NULL_PTR;

    *pucIndex         = 0;
    pstAvoidFreqList  = CNAS_XSD_GetAvoidFreqListAddr();

    for (i = 0; i < CNAS_MIN(pstAvoidFreqList->ucAvoidFreqNum, CNAS_XSD_MAX_AVOID_FREQ_NUM); i++)
    {
        if ((pstAvoidFreq->enBandClass == pstAvoidFreqList->astAvoidFreqInfo[i].stAvoidFreq.enBandClass)
         && (pstAvoidFreq->usChannel   == pstAvoidFreqList->astAvoidFreqInfo[i].stAvoidFreq.usChannel))
        {
            *pucIndex = i;
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

VOS_VOID CNAS_XSD_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    CNAS_XSD_CACHE_MSG_QUEUE_STRU      *pstMsgQueue   = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    pstMsgQueue  = CNAS_XSD_GetCacheMsgAddr();

    if (CNAS_XSD_MAX_CACHE_MSG_QUEUE_NUM <= pstMsgQueue->ucCacheMsgNum)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_SaveCacheMsgInMsgQueue:No Empty buffer");

        return;
    }

    pstMsgQueue->pastCacheMsg[pstMsgQueue->ucCacheMsgNum]
            = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_XSD, pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsgQueue->pastCacheMsg[pstMsgQueue->ucCacheMsgNum])
    {
        return;
    }

    NAS_MEM_CPY_S(pstMsgQueue->pastCacheMsg[pstMsgQueue->ucCacheMsgNum],
                  pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH,
                  pstMsgHeader,
                  pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);

    pstMsgQueue->ucCacheMsgNum++;

    CNAS_XSD_LogBufferQueueMsg(VOS_FALSE);

    CNAS_INFO_LOG1(UEPS_PID_XSD, "CNAS_XSD_SaveCacheMsgInMsgQueue: Cache Num = %d", pstMsgQueue->ucCacheMsgNum);
}


VOS_UINT32  CNAS_XSD_SaveCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    MSG_HEADER_STRU                     *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    /* 被cache的消息长度检查 */
    if ((CNAS_XSD_MAX_MSG_BUFFER_LEN - VOS_MSG_HEAD_LENGTH) <= pstMsgHeader->ulLength)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_SaveCacheMsg:Len too Long");
        return VOS_FALSE;
    }

    /* 将消息缓存在缓存内存池中 */
    CNAS_XSD_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    return VOS_TRUE;
}



VOS_VOID CNAS_XSD_ClearCacheMsg(
    VOS_UINT8                           ucIndex
)
{
    CNAS_XSD_CACHE_MSG_QUEUE_STRU       *pstMsgQueue = VOS_NULL_PTR;

    if (CNAS_XSD_MAX_CACHE_MSG_QUEUE_NUM <= ucIndex)
    {
        return;
    }

    pstMsgQueue = CNAS_XSD_GetCacheMsgAddr();

    if (0 < pstMsgQueue->ucCacheMsgNum)
    {
        pstMsgQueue->ucCacheMsgNum--;

        if (VOS_NULL_PTR != pstMsgQueue->pastCacheMsg[ucIndex])
        {
            PS_MEM_FREE(UEPS_PID_XSD, pstMsgQueue->pastCacheMsg[ucIndex]);

            pstMsgQueue->pastCacheMsg[ucIndex] = VOS_NULL_PTR;
        }

        if (ucIndex < (CNAS_XSD_MAX_CACHE_MSG_QUEUE_NUM - 1))
        {
            /* 清除的消息不是数组最后一个，需要把后续对列中的消息前移 */
            NAS_MEM_MOVE_S(&(pstMsgQueue->pastCacheMsg[ucIndex]),
                            (pstMsgQueue->ucCacheMsgNum - ucIndex) * sizeof(VOS_UINT8 *),
                           &(pstMsgQueue->pastCacheMsg[ucIndex + 1]),
                            (pstMsgQueue->ucCacheMsgNum - ucIndex) * sizeof(VOS_UINT8 *));
        }

        pstMsgQueue->pastCacheMsg[pstMsgQueue->ucCacheMsgNum] = VOS_NULL_PTR;
    }

    CNAS_XSD_LogBufferQueueMsg(VOS_FALSE);
}


VOS_UINT32 CNAS_XSD_ClearCacheMsgByMsgName(
    VOS_UINT32                          ulSndPid,
    VOS_UINT16                          usMsgName
)
{
    VOS_UINT32                          ulCurCacheMsgNum;
    VOS_UINT32                          ulCacheMsgEventType;
    MSG_HEADER_STRU                    *pstCacheMsg;
    REL_TIMER_MSG                      *pstTimerMsg;
    VOS_UINT32                          ulEventType;
    VOS_UINT32                          i;

    ulCurCacheMsgNum                    = CNAS_XSD_GetCacheMsgNum();
    ulEventType                         = CNAS_BuildEventType(ulSndPid, usMsgName);

    for (i = 0; i < ulCurCacheMsgNum; i++)
    {
        pstCacheMsg         = (MSG_HEADER_STRU *)CNAS_XSD_GetCacheMsgAddr()->pastCacheMsg[i];

        if (VOS_NULL_PTR == pstCacheMsg)
        {
            continue;
        }

        if (VOS_PID_TIMER == pstCacheMsg->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstCacheMsg;

            ulCacheMsgEventType = CNAS_BuildEventType(pstCacheMsg->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulCacheMsgEventType = CNAS_BuildEventType(pstCacheMsg->ulSenderPid, pstCacheMsg->ulMsgName);
        }

        if (ulEventType == ulCacheMsgEventType)
        {
            CNAS_XSD_ClearCacheMsg((VOS_UINT8)i);

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT32 CNAS_XSD_GetNextCachedMsg(
    CNAS_XSD_MSG_STRU                  *pstEntryMsg
)
{
    CNAS_XSD_CACHE_MSG_QUEUE_STRU      *pstMsgQueue = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstCacheMsgHdr = VOS_NULL_PTR;
    REL_TIMER_MSG                      *pstTimerMsg;

    pstMsgQueue = CNAS_XSD_GetCacheMsgAddr();

    if ( 0 == pstMsgQueue->ucCacheMsgNum )
    {
        CNAS_INFO_LOG(UEPS_PID_XSD, "CNAS_XSD_GetNextCachedMsg:Empty buffer");

        return VOS_FALSE;
    }

    /* 按照先入先出原则,默认取第1个缓存内容 */
    pstCacheMsgHdr = (MSG_HEADER_STRU *)(pstMsgQueue->pastCacheMsg[0]);

    if (VOS_NULL_PTR == pstCacheMsgHdr)
    {
        return VOS_FALSE;
    }

    if (VOS_PID_TIMER == pstCacheMsgHdr->ulSenderPid)
    {
        pstTimerMsg = (REL_TIMER_MSG *)pstCacheMsgHdr;

        pstEntryMsg->ulEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstTimerMsg->ulName);
    }
    else
    {
        pstEntryMsg->ulEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstCacheMsgHdr->ulMsgName);
    }

    NAS_MEM_CPY_S(&pstEntryMsg->aucMsgBuffer[0],
                  sizeof(pstEntryMsg->aucMsgBuffer),
                  pstCacheMsgHdr,
                  pstCacheMsgHdr->ulLength + VOS_MSG_HEAD_LENGTH);

    /* 清除index为0的cache消息 */
    CNAS_XSD_ClearCacheMsg(0);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_XSD_GetCacheMsgNum(VOS_VOID)
{
    CNAS_XSD_CACHE_MSG_QUEUE_STRU      *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue = CNAS_XSD_GetCacheMsgAddr();

    return pstMsgQueue->ucCacheMsgNum;
}


VOS_VOID  CNAS_XSD_SetCurrFsmState(
    VOS_UINT32                          ulCurrState
)
{
    CNAS_XSD_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;

    /* 获取当前的状态信息 */
    pstCurFsm                   = CNAS_XSD_GetCurFsmAddr();

    /* 设置当前状态 */
    pstCurFsm->ulState          = ulCurrState;

    /*  打印当前的当前状态机ID以及状态 */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_XSD, pstCurFsm->enFsmId, ulCurrState, 0);

    return;
}


CNAS_XSD_MSG_STRU* CNAS_XSD_GetCurrFsmEntryMsgAddr(VOS_VOID)
{
    return &(g_stCnasXsdCtx.stCurFsm.stEntryMsg);
}


VOS_VOID CNAS_XSD_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_MSG_STRU                  *pstEntryMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 获得当前处理CNAS XSD入口消息的缓冲区地址 */
    pstEntryMsg                 = CNAS_XSD_GetCurrFsmEntryMsgAddr();

    ulLen                       = pstMsg->ulLength + VOS_MSG_HEAD_LENGTH;

    if (ulLen > CNAS_XSD_MAX_MSG_BUFFER_LEN)
    {
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_SaveCurEntryMsg:beyond the Size!");

        ulLen = CNAS_XSD_MAX_MSG_BUFFER_LEN;
    }

    /* 将当前处理的入口消息拷贝到Context对应的缓冲区 */
    NAS_MEM_CPY_S( pstEntryMsg->aucMsgBuffer, sizeof(pstEntryMsg->aucMsgBuffer), pstMsg, ulLen );

    /* 填写Context中的参数 */
    pstEntryMsg->ulEventType    = ulEventType;

    return;
}


CNAS_XSD_FSM_ID_ENUM_UINT32 CNAS_XSD_GetCurrFsmId(VOS_VOID)
{
    return (g_stCnasXsdCtx.stCurFsm.enFsmId);
}


CNAS_XSD_READ_CARD_FILES_CNF_ENUM_UINT32 CNAS_XSD_GetWaitCardFilesCnfFlg_SwitchOn(VOS_VOID)
{
    /* 如果当前状态机不是switch on */
    if (CNAS_XSD_FSM_SWITCH_ON != CNAS_XSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetWaitCardFilesCnfFlg_SwitchOn: Wrong state ENTERED");
    }

    return g_stCnasXsdCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulXsdReadCardFileFlg;
}


VOS_VOID CNAS_XSD_SetWaitCardFilesCnfFlg_SwitchOn(
    CNAS_XSD_READ_CARD_FILES_CNF_ENUM_UINT32                enReadCardFileCnfFlg
)
{
    /* 如果当前状态机不是switch on */
    if (CNAS_XSD_FSM_SWITCH_ON != CNAS_XSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_SetWaitCardFilesCnfFlg_SwitchOn: Wrong state ENTERED");

        return;
    }

    g_stCnasXsdCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulXsdReadCardFileFlg |= enReadCardFileCnfFlg;
}


VOS_UINT8 CNAS_XSD_GetCampOnNeedFlg_PowerOff(VOS_VOID)
{
    /* 如果当前状态机不是power off */
    if (CNAS_XSD_FSM_POWER_OFF != CNAS_XSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "sCNAS_XSD_GetCampOnNeedFlg_PowerOff: Wrong state ENTERED");
    }

    return g_stCnasXsdCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucCampOnNeedFlg;
}


VOS_VOID CNAS_XSD_SetCampOnNeedFlg_PowerOff(
    VOS_UINT8                           ucCampOnNeedFlg
)
{
    /* 如果当前状态机不是power off */
    if (CNAS_XSD_FSM_POWER_OFF != CNAS_XSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_SetCampOnNeedFlg_PowerOff: Wrong state ENTERED");

        return;
    }

    g_stCnasXsdCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucCampOnNeedFlg = ucCampOnNeedFlg;
}


VOS_UINT8 CNAS_XSD_GetBufCallRelIndFlg_PowerOff(VOS_VOID)
{
    /* 如果当前状态机不是power off */
    if (CNAS_XSD_FSM_POWER_OFF != CNAS_XSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetBufCallRelFlg_PowerOff: Wrong state ENTERED");
    }

    return g_stCnasXsdCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucBufCallRelIndFlg;
}


VOS_VOID CNAS_XSD_SetBufCallRelIndFlg_PowerOff(
    VOS_UINT8                           ucBufCallRelIndFlg
)
{
    /* 如果当前状态机不是power off */
    if (CNAS_XSD_FSM_POWER_OFF != CNAS_XSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_SetBufCallRelIndFlg_PowerOff: Wrong state ENTERED");

        return;
    }

    g_stCnasXsdCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucBufCallRelIndFlg = ucBufCallRelIndFlg;
}


CNAS_PRL_FREQENCY_CHANNEL_STRU* CNAS_XSD_GetBufCallRelFreqInfo_PowerOff(VOS_VOID)
{
    /* 如果当前状态机不是power off */
    if (CNAS_XSD_FSM_POWER_OFF != CNAS_XSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetBufCallRelFreqInfo_PowerOff: Wrong state ENTERED");
    }

    return &(g_stCnasXsdCtx.stCurFsm.unFsmCtx.stPowerOffCtx.stBuffCallRelFreq);
}




VOS_VOID CNAS_XSD_SaveBufCallRelFreqInfo_PowerOff(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
)
{
    /* 如果当前状态机不是power off */
    if (CNAS_XSD_FSM_POWER_OFF != CNAS_XSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetBufCallRelFreqInfo_PowerOff: Wrong state ENTERED");

        return;
    }

    g_stCnasXsdCtx.stCurFsm.unFsmCtx.stPowerOffCtx.stBuffCallRelFreq.enBandClass = pstFreq->enBandClass;
    g_stCnasXsdCtx.stCurFsm.unFsmCtx.stPowerOffCtx.stBuffCallRelFreq.usChannel   = pstFreq->usChannel;
}



CNAS_XSD_TEST_CONFIG_STRU* CNAS_XSD_GetTestConfig(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stTestConfig);
}


CNAS_XSD_SYS_ACQ_NVIM_CFG_STRU* CNAS_XSD_Get1xSysAcqNvimConfig(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqNvimCfg);
}


CNAS_XSD_NEG_PREF_SYS_CMP_TYPE_ENUM_UINT8 CNAS_XSD_GetNegPrefSysCmpType()
{
    return (CNAS_XSD_Get1xSysAcqNvimConfig()->stNegPrefSysCmpCtrl.enNegPrefSysCmpType);
}



VOS_VOID CNAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn(
    CNAS_XSD_READ_CARD_FILES_CNF_ENUM_UINT32                enReadCardFileCnfFlg
)
{
    /* 如果当前状态机不是switch on */
    if (CNAS_XSD_FSM_SWITCH_ON != CNAS_XSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn: Wrong state ENTERED");
    }

    g_stCnasXsdCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulXsdReadCardFileFlg &= ~enReadCardFileCnfFlg;
}


CNAS_XSD_MRU_LIST_STRU* CNAS_XSD_GetMruList(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stMruList);
}


VOS_UINT8 CNAS_XSD_GetMruListNum(VOS_VOID)
{
    return (CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stMruList.ucSysNum);
}


VOS_UINT32 CNAS_XSD_GetMru0SysId(
    CNAS_PRL_1X_SYSTEM_STRU         *pstMru0SysId
)
{
    CNAS_XSD_MRU_LIST_STRU             *pstMruList = VOS_NULL_PTR;

    pstMruList = CNAS_XSD_GetMruList();

    if (0 < CNAS_XSD_GetMruListNum())
    {
        pstMru0SysId->stFreq    = pstMruList->astSystem[0].stFreq;
        pstMru0SysId->usNid     = pstMruList->astSystem[0].usNid;
        pstMru0SysId->usSid     = pstMruList->astSystem[0].usSid;

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 CNAS_XSD_GetMru1SysId(
    CNAS_PRL_1X_SYSTEM_STRU         *pstMru1SysId
)
{
    CNAS_XSD_MRU_LIST_STRU             *pstMruList = VOS_NULL_PTR;

    pstMruList = CNAS_XSD_GetMruList();

    if (1 < CNAS_XSD_GetMruListNum())
    {
        pstMru1SysId->stFreq    = pstMruList->astSystem[1].stFreq;
        pstMru1SysId->usNid     = pstMruList->astSystem[1].usNid;
        pstMru1SysId->usSid     = pstMruList->astSystem[1].usSid;

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_VOID CNAS_XSD_UpdateMru0(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysId
)
{
    VOS_UINT32                          i;
    CNAS_XSD_MRU_LIST_STRU             *pstMruList;
    VOS_UINT32                          ulIsSysInMru;

    ulIsSysInMru    = VOS_FALSE;
    pstMruList      = CNAS_XSD_GetMruList();

    /* 查找MRU中，是否有重复的系统 */
    for (i = 0; i < pstMruList->ucSysNum; i++)
    {
        /* 如果有重复的，则删除重复的 */
        if ((pstCurSysId->usSid == pstMruList->astSystem[i].usSid)
         && (pstCurSysId->usNid == pstMruList->astSystem[i].usNid)
         && (pstCurSysId->stFreq.enBandClass == pstMruList->astSystem[i].stFreq.enBandClass)
         && (pstCurSysId->stFreq.usChannel == pstMruList->astSystem[i].stFreq.usChannel))
        {
            /* 如果当前系统就在MRU0位置，直接返回，不需要任何操作 */
            if (0 == i)
            {
                return;
            }

            ulIsSysInMru = VOS_TRUE;
            pstMruList->ucSysNum--;

            NAS_MEM_MOVE_S(&pstMruList->astSystem[1],
                           sizeof(CNAS_PRL_1X_SYSTEM_STRU) * (CNAS_XSD_MAX_MRU_SYS_NUM - 1),
                           pstMruList->astSystem,
                           sizeof(CNAS_PRL_1X_SYSTEM_STRU)*(i));

            break;
        }
    }

    /* 如果当前不在MRU中，直接空出MRU[0]即可 */
    if (VOS_FALSE == ulIsSysInMru)
    {
        if (CNAS_XSD_MAX_MRU_SYS_NUM == pstMruList->ucSysNum)
        {
            NAS_MEM_MOVE_S(&pstMruList->astSystem[1],
                           sizeof(CNAS_PRL_1X_SYSTEM_STRU) * (CNAS_XSD_MAX_MRU_SYS_NUM - 1),
                           pstMruList->astSystem,
                           sizeof(CNAS_PRL_1X_SYSTEM_STRU)*(CNAS_XSD_MAX_MRU_SYS_NUM-1));
            pstMruList->ucSysNum--;
        }
        else
        {
            NAS_MEM_MOVE_S(&pstMruList->astSystem[1],
                           sizeof(CNAS_PRL_1X_SYSTEM_STRU) * (CNAS_XSD_MAX_MRU_SYS_NUM - 1),
                           pstMruList->astSystem,
                           sizeof(CNAS_PRL_1X_SYSTEM_STRU)*pstMruList->ucSysNum);
        }
    }

    /* 赋值到MRU[0]中 */
    pstMruList->astSystem[0] = *pstCurSysId;
    pstMruList->ucSysNum++;

    CNAS_XSD_WriteMruNvim(pstMruList);

    CNAS_XSD_LogMruList(pstMruList);

}


VOS_UINT32 CNAS_XSD_GetUeSupportedBandClass(VOS_VOID)
{
    return (CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.unUeSupportedBand.ulBand);
}


VOS_VOID CNAS_XSD_SetUeSupportedBandClass(
    VOS_UINT32                          ulUeSupportedBand
)
{
    (CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.unUeSupportedBand.ulBand) = ulUeSupportedBand;
}




CNAS_XSD_SCAN_CHANNEL_LIST_STRU* CNAS_XSD_GetScanChanListAddr(VOS_VOID)
{
    return &(g_stCnasXsdCtx.stSysAcqCtrl.stChanScanList);
}


VOS_UINT16 CNAS_XSD_GetScanChannelNum(VOS_VOID)
{
    return (g_stCnasXsdCtx.stSysAcqCtrl.stChanScanList.usTotalNum);
}


VOS_UINT16 CNAS_XSD_GetCurChannelScanIndex(VOS_VOID)
{
    return (g_stCnasXsdCtx.stSysAcqCtrl.stChanScanList.usCurScanIndex);
}


VOS_VOID CNAS_XSD_SetCurChannelScanIndex(
    VOS_UINT16                          usCurScanIndex
)
{
    g_stCnasXsdCtx.stSysAcqCtrl.stChanScanList.usCurScanIndex = usCurScanIndex;
}


CNAS_XSD_AVAILABLE_LIST_STRU* CNAS_XSD_GetAvailSysFreqListAddr(VOS_VOID)
{
    /* 如果当前状态机不是CNAS_XSD_FSM_SYS_ACQ */
    if (CNAS_XSD_FSM_SYS_ACQ != CNAS_XSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetAvailSysFreqListAddr: Wrong state ENTERED");
    }

    return &(CNAS_XSD_GetXsdCtxAddr()->stCurFsm.unFsmCtx.stSysAcqCtx.stAvailSysList);
}


VOS_VOID CNAS_XSD_AddAvailSysFreqList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
)
{
    CNAS_XSD_AVAILABLE_LIST_STRU       *pstAvailSysList = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstAvailSysList = CNAS_XSD_GetAvailSysFreqListAddr();

    /* 判断是否已经存在 */
    for (i = 0; i < (VOS_UINT32)CNAS_MIN(pstAvailSysList->ucAvailSysNum, CNAS_XSD_MAX_AVAILABLE_SYS_NUM); i++)
    {
        if (0 == PS_MEM_CMP(&(pstAvailSysList->astAvailSystem[i].stFreq),
                            pstFreq,
                            sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU)))
        {
            NAS_MEM_MOVE_S(&(pstAvailSysList->astAvailSystem[1]),
                           sizeof(CNAS_XSD_AVAIL_SYSTEM_INFO_STRU) * (CNAS_XSD_MAX_AVAILABLE_SYS_NUM - 1),
                           &(pstAvailSysList->astAvailSystem[0]),
                           sizeof(CNAS_XSD_AVAIL_SYSTEM_INFO_STRU) * i);

            NAS_MEM_CPY_S(&(pstAvailSysList->astAvailSystem[0].stFreq),
                          sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU),
                          pstFreq,
                          sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU));

            return;
        }
    }

    /* 所有记录后移，最新的available system保存在index 0的位置 */
    if (pstAvailSysList->ucAvailSysNum < CNAS_XSD_MAX_AVAILABLE_SYS_NUM)
    {
        NAS_MEM_MOVE_S(&(pstAvailSysList->astAvailSystem[1]),
                       sizeof(CNAS_XSD_AVAIL_SYSTEM_INFO_STRU) * (CNAS_XSD_MAX_AVAILABLE_SYS_NUM - 1),
                       &(pstAvailSysList->astAvailSystem[0]),
                       sizeof(CNAS_XSD_AVAIL_SYSTEM_INFO_STRU) * pstAvailSysList->ucAvailSysNum);

        pstAvailSysList->ucAvailSysNum++;
    }
    else
    {
        NAS_MEM_MOVE_S(&(pstAvailSysList->astAvailSystem[1]),
                       sizeof(CNAS_XSD_AVAIL_SYSTEM_INFO_STRU) * (CNAS_XSD_MAX_AVAILABLE_SYS_NUM - 1),
                       &(pstAvailSysList->astAvailSystem[0]),
                       sizeof(CNAS_XSD_AVAIL_SYSTEM_INFO_STRU) * (CNAS_XSD_MAX_AVAILABLE_SYS_NUM - 1));
    }

    NAS_MEM_CPY_S(&(pstAvailSysList->astAvailSystem[0].stFreq),
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU),
                  pstFreq,
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU));

    CNAS_XSD_LogAvailSystemList(pstAvailSysList);

    return;
}


VOS_VOID CNAS_XSD_SetAvailSysFeqListNextSrchIndex(
    VOS_UINT8                           ucNextSrchIndex
)
{
    CNAS_XSD_AVAILABLE_LIST_STRU       *pstAvailSysList = VOS_NULL_PTR;

    pstAvailSysList = CNAS_XSD_GetAvailSysFreqListAddr();

    pstAvailSysList->ucNextSrchIndex = ucNextSrchIndex;
}


VOS_UINT8 CNAS_XSD_GetAvailSysFreqListNextSrchIndex(VOS_VOID)
{
    CNAS_XSD_AVAILABLE_LIST_STRU       *pstAvailSysList = VOS_NULL_PTR;

    pstAvailSysList = CNAS_XSD_GetAvailSysFreqListAddr();

    return pstAvailSysList->ucNextSrchIndex;
}


VOS_UINT8 CNAS_XSD_GetAvailSysFreqNum(VOS_VOID)
{
    CNAS_XSD_AVAILABLE_LIST_STRU       *pstAvailSysList = VOS_NULL_PTR;

    pstAvailSysList = CNAS_XSD_GetAvailSysFreqListAddr();

    return pstAvailSysList->ucAvailSysNum;
}


VOS_VOID CNAS_XSD_SetAvailSysAcqListFlg_SysAcq(
    VOS_UINT8                           ucFlg
)
{
    /* 如果当前状态机不是CNAS_XSD_FSM_SYS_ACQ */
    if (CNAS_XSD_FSM_SYS_ACQ != CNAS_XSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetAvailSysAcqListFlg_SysAcq: Wrong state ENTERED");

        return;
    }

    g_stCnasXsdCtx.stCurFsm.unFsmCtx.stSysAcqCtx.ucIsAvailSysAcqList = ucFlg;

    return;
}


VOS_UINT8 CNAS_XSD_GetAvailSysAcqListFlg_SysAcq(VOS_VOID)
{
    /* 如果当前状态机不是CNAS_XSD_FSM_SYS_ACQ */
    if (CNAS_XSD_FSM_SYS_ACQ != CNAS_XSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetAvailSysAcqListFlg_SysAcq: Wrong state ENTERED");
    }

    return g_stCnasXsdCtx.stCurFsm.unFsmCtx.stSysAcqCtx.ucIsAvailSysAcqList;
}


VOS_VOID CNAS_XSD_SetAbortFlg_SysAcq(
    VOS_UINT8                           ucFlg
)
{
    /* 如果当前状态机不是CNAS_XSD_FSM_SYS_ACQ */
    if (CNAS_XSD_FSM_SYS_ACQ != CNAS_XSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_SetAbortFlg_SysAcq: Wrong state ENTERED");

        return;
    }

    g_stCnasXsdCtx.stCurFsm.unFsmCtx.stSysAcqCtx.ucAbortFlg = ucFlg;

    return;
}


VOS_UINT8 CNAS_XSD_GetAbortFlg_SysAcq(VOS_VOID)
{
    /* 如果当前状态机不是CNAS_XSD_FSM_SYS_ACQ */
    if (CNAS_XSD_FSM_SYS_ACQ != CNAS_XSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetAbortFlg_SysAcq: Wrong state ENTERED");
    }

    return g_stCnasXsdCtx.stCurFsm.unFsmCtx.stSysAcqCtx.ucAbortFlg;
}



VOS_VOID CNAS_XSD_SetAbortFlag_Redir(
    VOS_UINT8                                ucAbortFlag
)
{

    /* Checking for current state machine is redirection or not */
    if (CNAS_XSD_FSM_REDIRECTION != CNAS_XSD_GetCurrFsmId())
    {
        /* abnormal event */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_SetAbortFlag_Redir:Wrong state ENTERED");

        return;
    }

    g_stCnasXsdCtx.stCurFsm.unFsmCtx.stRedirCtx.ucAbortFlag = ucAbortFlag;

    return;
}


VOS_UINT8 CNAS_XSD_GetAbortFlag_Redir(VOS_VOID)
{

    /* Checking for current state machine is redirection or not */
    if (CNAS_XSD_FSM_REDIRECTION != CNAS_XSD_GetCurrFsmId())
    {
        /* abnormal event */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetAbortFlag_Redir:Wrong state ENTERED");
    }

    return (g_stCnasXsdCtx.stCurFsm.unFsmCtx.stRedirCtx.ucAbortFlag);
}


CNAS_XSD_SCAN_CHANNEL_LIST_STRU *CNAS_XSD_GetScanChanListAddr_Redir(VOS_VOID)
{
    /* Checking for current state machine is redirection or not */
    if (CNAS_XSD_FSM_REDIRECTION != CNAS_XSD_GetCurrFsmId())
    {
        /* abnormal event */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetScanChanListAddr_Redir:Wrong state ENTERED");

    }

    return (&(g_stCnasXsdCtx.stCurFsm.unFsmCtx.stRedirCtx.stRedireScanList));
}


VOS_UINT16 CNAS_XSD_GetCurChannelScanIndex_Redir(VOS_VOID)
{
    /* 如果当前状态机不是CNAS_XSD_FSM_SYS_ACQ */
    if (CNAS_XSD_FSM_REDIRECTION != CNAS_XSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetCurChannelScanIndex_Redir: Wrong state ENTERED");
    }

    return (CNAS_XSD_GetXsdCtxAddr()->stCurFsm.unFsmCtx.stRedirCtx.stRedireScanList.usCurScanIndex);
}


VOS_VOID CNAS_XSD_SetCurChannelScanIndex_Redir(VOS_UINT16 usIndex)
{
    /* 如果当前状态机不是CNAS_XSD_FSM_SYS_ACQ */
    if (CNAS_XSD_FSM_REDIRECTION != CNAS_XSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_SetCurChannelScanIndex_Redir: Wrong state ENTERED");

        return;
    }

    CNAS_XSD_GetXsdCtxAddr()->stCurFsm.unFsmCtx.stRedirCtx.stRedireScanList.usCurScanIndex = usIndex;
}



VOS_UINT16 CNAS_XSD_GetScanChannelNum_Redir(VOS_VOID)
{
    /* Checking for current state machine is redirection or not */
    if (CNAS_XSD_FSM_REDIRECTION != CNAS_XSD_GetCurrFsmId())
    {
        /* abnormal event */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetScanChannelNum_Redir:Wrong state ENTERED");

    }

    return (g_stCnasXsdCtx.stCurFsm.unFsmCtx.stRedirCtx.stRedireScanList.usTotalNum);
}



CNAS_XSD_SCAN_CHANNEL_LIST_STRU* CNAS_XSD_GetCallRedialScanChanListAddr(VOS_VOID)
{
    return  (&(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCallRedialInfo.stCallRedialChanScanList));
}


CNAS_XSD_SCAN_CHANNEL_LIST_STRU *CNAS_XSD_GetEmcCallRedialScanChanListAddr(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.stEmcCallRedialChanScanList);
}


VOS_VOID CNAS_XSD_SetCallExistFlg(
    VOS_UINT8                           ucCallExistFlg
)
{
    CNAS_XSD_CALL_REDIAL_CTRL_INFO_STRU *pstCallStartSysInfo = VOS_NULL_PTR;

    pstCallStartSysInfo = &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCallRedialInfo);

    pstCallStartSysInfo->ucCallExistFlg |= ucCallExistFlg;

    return;
}


VOS_VOID CNAS_XSD_ClearEmcCallRedialScanChanList( VOS_VOID )
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList = VOS_NULL_PTR;

    pstScanChanList = CNAS_XSD_GetEmcCallRedialScanChanListAddr();

    if (VOS_NULL_PTR != pstScanChanList->pstScanChanInfo)
    {
        PS_MEM_FREE(UEPS_PID_XSD, pstScanChanList->pstScanChanInfo);
    }

    NAS_MEM_SET_S(pstScanChanList, sizeof(CNAS_XSD_SCAN_CHANNEL_LIST_STRU), 0x00, sizeof(CNAS_XSD_SCAN_CHANNEL_LIST_STRU));

    return;
}


VOS_VOID CNAS_XSD_ClearCallExistFlg(
    VOS_UINT8                           ucCallExistFlg
)
{
    CNAS_XSD_CALL_REDIAL_CTRL_INFO_STRU *pstCallStartSysInfo = VOS_NULL_PTR;

    pstCallStartSysInfo = &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCallRedialInfo);

    pstCallStartSysInfo->ucCallExistFlg &= ~(ucCallExistFlg);

    return;
}



VOS_UINT8 CNAS_XSD_GetCallExistFlg(VOS_VOID)
{
    CNAS_XSD_CALL_REDIAL_CTRL_INFO_STRU *pstCallStartSysInfo = VOS_NULL_PTR;

    pstCallStartSysInfo = &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCallRedialInfo);

    return (pstCallStartSysInfo->ucCallExistFlg);
}




VOS_VOID CNAS_XSD_SetCallOrigSysExistFlg(
    VOS_UINT8                           ucFlg
)
{
    CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCallRedialInfo.ucOrigSysExistFlg = ucFlg;

    return;
}


VOS_UINT8 CNAS_XSD_GetCallOrigSysExistFlg(VOS_VOID)
{
    return (CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCallRedialInfo.ucOrigSysExistFlg);

}




VOS_VOID CNAS_XSD_SaveCallOrignalSys(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysId
)
{
    CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCallRedialInfo.stCallOrignalSys = *pstCurSysId;

    return;
}


CNAS_PRL_1X_SYSTEM_STRU *CNAS_XSD_GetCallOrignalSys(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCallRedialInfo.stCallOrignalSys);

}



VOS_VOID CNAS_XSD_SaveEmcCallOriginalSys(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysId
)
{
    CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.stCallOrignalSys = *pstCurSysId;

    return;
}


CNAS_PRL_1X_SYSTEM_STRU *CNAS_XSD_GetEmcCallOriginalSys(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.stCallOrignalSys);
}


VOS_VOID CNAS_XSD_ClearEmcCallOriginalSys( VOS_VOID )
{
    NAS_MEM_SET_S(CNAS_XSD_GetEmcCallOriginalSys(), sizeof(CNAS_PRL_1X_SYSTEM_STRU), 0x00, sizeof(CNAS_PRL_1X_SYSTEM_STRU));

    return;
}


VOS_UINT32 CNAS_XSD_IsEmcCallOriginalSysExist( VOS_VOID )
{
    CNAS_PRL_1X_SYSTEM_STRU                         stNullSystem;

    NAS_MEM_SET_S(&stNullSystem, sizeof(stNullSystem), 0x00, sizeof(CNAS_PRL_1X_SYSTEM_STRU));

    if (0 == PS_MEM_CMP(&stNullSystem,
                         CNAS_XSD_GetEmcCallOriginalSys(),
                         sizeof(CNAS_PRL_1X_SYSTEM_STRU)))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}



CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU* CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq(VOS_VOID)
{
    CNAS_XSD_CTX_STRU                  *pstXsdCtx = VOS_NULL_PTR;

    pstXsdCtx = CNAS_XSD_GetXsdCtxAddr();

    return &(pstXsdCtx->stCurFsm.unFsmCtx.stSysAcqCtx.stGeoSysSrchList);
}


VOS_UINT16 CNAS_XSD_GetCurSysAcqListNum_SysAcq(VOS_VOID)
{
    /* 如果当前状态机不是CNAS_XSD_FSM_SYS_ACQ */
    if (CNAS_XSD_FSM_SYS_ACQ != CNAS_XSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetCurSysAcqListIndex_SysAcq: Wrong state ENTERED");
    }

    return g_stCnasXsdCtx.stCurFsm.unFsmCtx.stSysAcqCtx.stGeoSysSrchList.usTotalNum;
}



CNAX_XSD_CAMPED_SYS_INFO_STRU* CNAS_XSD_GetCurCampedSysInfo(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCurCampedSysInfo);
}


VOS_VOID CNAS_XSD_UpdateCurCampedSysInfo(
    CNAX_XSD_CAMPED_SYS_INFO_STRU      *pstCurCampedSysInfo
)
{
    NAS_MEM_CPY_S(CNAS_XSD_GetCurCampedSysInfo(), sizeof(CNAX_XSD_CAMPED_SYS_INFO_STRU), pstCurCampedSysInfo, sizeof(CNAX_XSD_CAMPED_SYS_INFO_STRU));

    return;
}



CNAS_XSD_SERVICE_STATUS_ENUM_UINT32 CNAS_XSD_GetCurSrvStatus(VOS_VOID)
{
    CNAX_XSD_CAMPED_SYS_INFO_STRU                          *pstCurCampedSysInfo = VOS_NULL_PTR;

    pstCurCampedSysInfo = CNAS_XSD_GetCurCampedSysInfo();

    return pstCurCampedSysInfo->enSrvStatus;
}


VOS_VOID CNAS_XSD_SetCurSrvStatus(
    CNAS_XSD_SERVICE_STATUS_ENUM_UINT32                     enSrvStatus
)
{
    CNAX_XSD_CAMPED_SYS_INFO_STRU                          *pstCurCampedSysInfo = VOS_NULL_PTR;

    pstCurCampedSysInfo = CNAS_XSD_GetCurCampedSysInfo();

    pstCurCampedSysInfo->enSrvStatus = enSrvStatus;

    /* 同步将状态设置到CCB全局变量供其他模块查询 */
    CNAS_INFO_LOG1(UEPS_PID_XSD, "CNAS_XSD_SetCurSrvStatus:Cur SrvStatus Set To:", (VOS_UINT32)pstCurCampedSysInfo->enSrvStatus);

    CNAS_CCB_SetCur1XSrvStatus((CNAS_CCB_SERVICE_STATUS_ENUM_UINT32)enSrvStatus);
}


CNAS_XSD_INT_MSG_QUEUE_STRU* CNAS_XSD_GetIntMsgQueueAddr(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stIntMsgQueue);
}


VOS_VOID CNAS_XSD_InitInternalBuffer(
    CNAS_XSD_INT_MSG_QUEUE_STRU        *pstIntMsgQueue
)
{
    VOS_UINT8                           i;

    for (i = 0; i < CNAS_XSD_MAX_INT_MSG_QUEUE_NUM; i++)
    {
        pstIntMsgQueue->pastIntMsg[i] = VOS_NULL_PTR;
    }

    pstIntMsgQueue->ucIntMsgNum = 0;
}



VOS_VOID  CNAS_XSD_PutMsgInIntMsgQueue(
    VOS_UINT8                          *pstMsg
)
{
    VOS_UINT8                           ucIntMsgNum;

    /* 检查内部消息队列，是否有缓存队列已满 */
    if (CNAS_XSD_MAX_INT_MSG_QUEUE_NUM <= CNAS_XSD_GetIntMsgNum())
    {
        PS_MEM_FREE(UEPS_PID_XSD, pstMsg);

        CNAS_ERROR_LOG( UEPS_PID_XSD, "CNAS_XSD_SndSwitchOnRlst: msg queue is full!" );

        return;
    }

    ucIntMsgNum = CNAS_XSD_GetIntMsgQueueAddr()->ucIntMsgNum;

    /* 保存当前信息 */
    CNAS_XSD_GetIntMsgQueueAddr()->pastIntMsg[ucIntMsgNum] = pstMsg;

    CNAS_XSD_GetIntMsgQueueAddr()->ucIntMsgNum = (ucIntMsgNum + 1);

    return;
}


VOS_UINT8 *CNAS_XSD_GetNextIntMsg(VOS_VOID)
{
    VOS_UINT8                           ucIntMsgNum;
    VOS_UINT8                          *pstIntMsg = VOS_NULL_PTR;

    ucIntMsgNum = CNAS_XSD_GetIntMsgQueueAddr()->ucIntMsgNum;

    if (0 < ucIntMsgNum)
    {
        /* 获取下一个缓存的消息消息 */
        pstIntMsg = CNAS_XSD_GetIntMsgQueueAddr()->pastIntMsg[0];

        /* 内部消息数目减少一个 */
        ucIntMsgNum--;

        if (0 != ucIntMsgNum)
        {
            /* 前移内部消息 */
            NAS_MEM_MOVE_S(&(CNAS_XSD_GetIntMsgQueueAddr()->pastIntMsg[0]),
                           CNAS_XSD_MAX_INT_MSG_QUEUE_NUM * sizeof(VOS_UINT8 *),
                           &(CNAS_XSD_GetIntMsgQueueAddr()->pastIntMsg[1]),
                           ucIntMsgNum * sizeof(VOS_UINT8 *));
        }

        /* 对消息队列中尾部的消息清为空指针 */
        CNAS_XSD_GetIntMsgQueueAddr()->pastIntMsg[ucIntMsgNum] = VOS_NULL_PTR;

        CNAS_XSD_GetIntMsgQueueAddr()->ucIntMsgNum = ucIntMsgNum;
    }

    return pstIntMsg;
}


VOS_UINT8 CNAS_XSD_GetIntMsgNum(VOS_VOID)
{
    VOS_UINT8                           ucIntMsgNum;

    ucIntMsgNum = CNAS_XSD_GetIntMsgQueueAddr()->ucIntMsgNum;

    return ucIntMsgNum;
}





CNAS_XSD_AVOID_FREQ_LIST_STRU* CNAS_XSD_GetAvoidFreqListAddr(VOS_VOID)
{
    return &(g_stCnasXsdCtx.stSysAcqCtrl.stAvoidFreqList);
}


VOS_UINT8 CNAS_XSD_GetAvoidFreqListNum(VOS_VOID)
{
    return (CNAS_XSD_GetAvoidFreqListAddr()->ucAvoidFreqNum);
}


VOS_VOID CNAS_XSD_DeleteAvoidFlagFromAvoidList(
    VOS_UINT8                           ucIndex
)
{
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList = VOS_NULL_PTR;

    if (ucIndex < CNAS_XSD_MAX_AVOID_FREQ_NUM)
    {
        pstAvoidFreqList = CNAS_XSD_GetAvoidFreqListAddr();

        pstAvoidFreqList->astAvoidFreqInfo[ucIndex].ucAvoidFlag = VOS_FALSE;


    }
}


CNAS_XSD_AVOID_FREQ_INFO_STRU *CNAS_XSD_GetAvoidFreqFromAvoidList(
    VOS_UINT8                           ucIndex
)
{
    CNAS_XSD_AVOID_FREQ_INFO_STRU      *pstAvoidFreqInfo = VOS_NULL_PTR;

    if (ucIndex < CNAS_XSD_MAX_AVOID_FREQ_NUM)
    {
        /* 返回指定索引的avoid频点信息 */
        pstAvoidFreqInfo = &(CNAS_XSD_GetAvoidFreqListAddr()->astAvoidFreqInfo[ucIndex]);

        return pstAvoidFreqInfo;
    }

    return VOS_NULL_PTR;
}


VOS_VOID CNAS_XSD_SetSystemCampOnFlag(
    VOS_UINT8                           ucCampOnFlg
)
{
    CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCurCampedSysInfo.ucCampOnFlag = ucCampOnFlg;

    return;
}


VOS_UINT8 CNAS_XSD_GetSystemCampOnFlag(VOS_VOID)
{
    return (CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCurCampedSysInfo.ucCampOnFlag);
}




CNAS_XSD_REDIRECTION_INFO_STRU *CNAS_XSD_GetRedirectionInfoAddr(VOS_VOID)
{
    return (&(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stRedirInfo));
}


VOS_UINT8 CNAS_XSD_GetRedirectionFlag(VOS_VOID)
{
    return (CNAS_XSD_GetRedirectionInfoAddr()->ucRedirection);
}


VOS_VOID CNAS_XSD_SetRedirectionFlag(
    VOS_UINT8               ucRedirection
)
{
    CNAS_XSD_REDIRECTION_INFO_STRU     *pstRedirInfo = VOS_NULL_PTR;

    pstRedirInfo                = CNAS_XSD_GetRedirectionInfoAddr();
    pstRedirInfo->ucRedirection = ucRedirection;

    return;
}


VOS_VOID CNAS_XSD_SetEmcRedirectionFlg(
    VOS_VOID
)
{
    CNAS_XSD_REDIRECTION_INFO_STRU     *pstRedirInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulIsEmcCallOriginalSysExist;

    pstRedirInfo                        = CNAS_XSD_GetRedirectionInfoAddr();
    ulIsEmcCallOriginalSysExist         = CNAS_XSD_IsEmcCallOriginalSysExist();

    if ((VOS_NULL_PTR != CNAS_XSD_GetEmcCallRedialScanChanListAddr()->pstScanChanInfo)
     || (VOS_TRUE     == ulIsEmcCallOriginalSysExist))
    {
        pstRedirInfo->ucIsEmcRedir  = VOS_TRUE;

        return;
    }

    pstRedirInfo->ucIsEmcRedir  = VOS_FALSE;

    return;
}


VOS_UINT8 CNAS_XSD_GetRedirectionReturnIfFailFlag(VOS_VOID)
{
    return (CNAS_XSD_GetRedirectionInfoAddr()->ucReturnIfFail);
}


VOS_VOID CNAS_XSD_SaveRedirectionOrignalSys(
    CNAS_PRL_1X_SYSTEM_STRU         *pstOriginalSystem
)
{
    CNAS_XSD_REDIRECTION_INFO_STRU     *pstRedirInfo = VOS_NULL_PTR;

    pstRedirInfo                   = CNAS_XSD_GetRedirectionInfoAddr();

    pstRedirInfo->stOriginalSystem = *pstOriginalSystem;

    return;
}


CNAS_PRL_1X_SYSTEM_STRU *CNAS_XSD_GetRedirectionOrignalSys(VOS_VOID)
{
    return (&(CNAS_XSD_GetRedirectionInfoAddr()->stOriginalSystem));
}


CNAS_XSD_SCAN_CHANNEL_INFO_STRU *CNAS_XSD_GetRedirectionChanList(VOS_VOID)
{
    return (CNAS_XSD_GetRedirectionInfoAddr()->astChanInfo);
}



CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU* CNAS_XSD_GetFreqLockAddr(VOS_VOID)
{
    return &(g_stCnasXsdCtx.stSysAcqCtrl.stFreqLockPara);
}


VOS_UINT8 CNAS_XSD_GetFreqLockMode(VOS_VOID)
{
    return (g_stCnasXsdCtx.stSysAcqCtrl.stFreqLockPara.ucFreqLockMode);
}


VOS_VOID CNAS_XSD_InitCFreqLockValue(VOS_VOID)
{
    CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU  *pstCnasXsdCFreqLockValue;

    pstCnasXsdCFreqLockValue = CNAS_XSD_GetFreqLockAddr();

    NAS_MEM_SET_S(pstCnasXsdCFreqLockValue, sizeof(CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU), 0x00, sizeof(CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU));

    return;
}




VOS_VOID CNAS_XSD_InitTestConfig(
    CNAS_XSD_TEST_CONFIG_STRU          *pstTestConfig
)
{
    NAS_MEM_SET_S(pstTestConfig, sizeof(CNAS_XSD_TEST_CONFIG_STRU), 0x00, sizeof(CNAS_XSD_TEST_CONFIG_STRU));

    return;
}


VOS_VOID CNAS_XSD_InitSysAcqNvimCfg(
    CNAS_XSD_SYS_ACQ_NVIM_CFG_STRU                         *pstSysAcqNvimCfg
)
{
    NAS_MEM_SET_S(pstSysAcqNvimCfg, sizeof(CNAS_XSD_SYS_ACQ_NVIM_CFG_STRU), 0x00, sizeof(CNAS_XSD_SYS_ACQ_NVIM_CFG_STRU));

    return;
}


CNAS_XSD_OOC_SCHEDULE_INFO_STRU *CNAS_XSD_GetOocScheduleInfo(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stOocScheduleInfo);
}


VOS_VOID CNAS_XSD_InitOocScheduleInfo(
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo
)
{
    NAS_MEM_SET_S(pstOocScheduleInfo, sizeof(CNAS_XSD_OOC_SCHEDULE_INFO_STRU), 0, sizeof(CNAS_XSD_OOC_SCHEDULE_INFO_STRU));

    pstOocScheduleInfo->stConfigInfo.ucPhaseNum                      = 0;
    pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[0].usTimerLen   = 5;
    pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[0].usTimes      = 5;

}


VOS_VOID CNAS_XSD_InitOocCtxInfo(VOS_VOID)
{
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo = VOS_NULL_PTR;

    pstOocScheduleInfo = CNAS_XSD_GetOocScheduleInfo();

    NAS_MEM_SET_S(&pstOocScheduleInfo->stOocCtxInfo, sizeof(pstOocScheduleInfo->stOocCtxInfo), 0, sizeof(CNAS_XSD_OOC_CTX_INFO_STRU));
}


VOS_UINT8 CNAS_XSD_GetOocWaitSearchFlag(VOS_VOID)
{
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU                        *pstOocSchedule = VOS_NULL_PTR;

    pstOocSchedule = CNAS_XSD_GetOocScheduleInfo();

    return (pstOocSchedule->stOocCtxInfo.ucWaitSearchFlag);
}


VOS_VOID CNAS_XSD_SetOocWaitSearchFlag(VOS_UINT8 ucWaitSearchFlag)
{
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU                        *pstOocSchedule = VOS_NULL_PTR;

    pstOocSchedule = CNAS_XSD_GetOocScheduleInfo();

    pstOocSchedule->stOocCtxInfo.ucWaitSearchFlag = ucWaitSearchFlag;
}



VOS_VOID CNAS_XSD_SetNdssIndFlag(
    VOS_UINT8                           ucNdssInd
)
{
    CNAS_XSD_REDIRECTION_INFO_STRU     *pstRedirInfo = VOS_NULL_PTR;

    pstRedirInfo            = CNAS_XSD_GetRedirectionInfoAddr();
    pstRedirInfo->ucNdssInd = ucNdssInd;

    return;
}


VOS_UINT8 CNAS_XSD_GetNdssIndFlag(VOS_VOID)
{
    CNAS_XSD_REDIRECTION_INFO_STRU     *pstRedirInfo = VOS_NULL_PTR;

    pstRedirInfo            = CNAS_XSD_GetRedirectionInfoAddr();

    return (pstRedirInfo->ucNdssInd);
}


CNAS_XSD_OOC_CONFIG_INFO_STRU *CNAS_XSD_GetOocScheduleConfigInfo(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stOocScheduleInfo.stConfigInfo);
}



VOS_UINT8 CNAS_XSD_GetSrvAcqFlg(VOS_VOID)
{
    return CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.ucSrvAcqFlg;
}


VOS_VOID CNAS_XSD_SetSrvAcqFlg(
    VOS_UINT8                           ucSrvAcqFlg
)
{
    CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.ucSrvAcqFlg  = ucSrvAcqFlg;

    return;
}


CNAS_XSD_EMC_STATE_ENUM_UINT8 CNAS_XSD_GetEmcState(VOS_VOID)
{
    return CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.enEmcState;
}


VOS_UINT8 CNAS_XSD_GetEmcCallBackSrchCounter(VOS_VOID)
{
    return CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.ucCallBackSrchCounter;
}


VOS_VOID CNAS_XSD_SetEmcCallBackSrchCounter(
    VOS_UINT8                           ucEmcCallBackCounter
)
{
    CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.ucCallBackSrchCounter = ucEmcCallBackCounter;

    return;
}


CNAS_XSD_EMC_CALLBACK_CANDIDATE_FREQ_INFO_STRU* CNAS_XSD_GetEmcCallBackCandidateFreqInfo(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.stEmcCallBackCfInfo);
}


VOS_VOID CNAS_XSD_ClearEmcCallBackCandidateFreq(
    VOS_VOID
)
{
    PS_MEM_SET(CNAS_XSD_GetEmcCallBackCandidateFreqInfo(), 0x00, sizeof(CNAS_XSD_EMC_CALLBACK_CANDIDATE_FREQ_INFO_STRU));

    return;
}


VOS_VOID CNAS_XSD_SetEmcCallBackCandidateFreq(
    VOS_UINT16                          usCfFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstCfInfo
)
{
    VOS_UINT32                          i;
    CNAS_XSD_EMC_CALLBACK_CANDIDATE_FREQ_INFO_STRU         *pstEmcCallBackCfInfo    = VOS_NULL_PTR;

    pstEmcCallBackCfInfo    = CNAS_XSD_GetEmcCallBackCandidateFreqInfo();

    CNAS_XSD_ClearEmcCallBackCandidateFreq();

    pstEmcCallBackCfInfo->usCfChannelNum = CNAS_MIN(usCfFreqNum, CNAS_XSD_MAX_CANDIDATE_FREQ_NUM);

    for (i = 0; i < pstEmcCallBackCfInfo->usCfChannelNum; i++)
    {
        pstEmcCallBackCfInfo->astChannelList[i].enBandClass = pstCfInfo[i].enBandClass;
        pstEmcCallBackCfInfo->astChannelList[i].usChannel   = pstCfInfo[i].usChannel;

        CNAS_INFO_LOG3(UEPS_PID_XSD, "CNAS_XSD_SetEmcCallBackCandidateFreq: Index,Band,Chan", i, (VOS_UINT32)pstCfInfo[i].enBandClass, (VOS_UINT32)pstCfInfo[i].usChannel);
    }

    return;
}


VOS_VOID CNAS_XSD_SetEmcState(
    CNAS_XSD_EMC_STATE_ENUM_UINT8       enEmcState
)
{
    CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.enEmcState = enEmcState;

    return;
}


CNAS_XSD_CALLBACK_CFG_STRU *CNAS_XSD_GetCallBackCfg( VOS_VOID )
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.stCallBackCfg);
}


VOS_VOID CNAS_XSD_InitGeoSrchListInfo(
    CNAS_XSD_GEO_LIST_SRCH_INFO_STRU   *pstGeoListSrchInfo
)
{
    NAS_MEM_SET_S(pstGeoListSrchInfo, sizeof(CNAS_XSD_GEO_LIST_SRCH_INFO_STRU), 0, sizeof(CNAS_XSD_GEO_LIST_SRCH_INFO_STRU));
}


CNAS_XSD_GEO_LIST_SRCH_INFO_STRU *CNAS_XSD_GetGeoSrchListInfoAddr(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stGeoListSrchInfo);
}


VOS_VOID CNAS_XSD_ClearGeoSrchListStatus(VOS_VOID)
{
    VOS_UINT16                              i;
    CNAS_XSD_GEO_LIST_SRCH_INFO_STRU       *pstGeoListSrchInfo = VOS_NULL_PTR;

    pstGeoListSrchInfo = CNAS_XSD_GetGeoSrchListInfoAddr();

    if (VOS_NULL_PTR == pstGeoListSrchInfo->pstGeoSrchInfo)
    {
        return;
    }

    for (i = 0; i < pstGeoListSrchInfo->usGeoNum; i++)
    {
        pstGeoListSrchInfo->pstGeoSrchInfo[i].usGeoSrchStatus = VOS_FALSE;
    }
}


VOS_VOID CNAS_XSD_FreeBufferOfGeoSrchList(VOS_VOID)
{
    CNAS_XSD_GEO_LIST_SRCH_INFO_STRU       *pstGeoListSrchInfo = VOS_NULL_PTR;

    pstGeoListSrchInfo = CNAS_XSD_GetGeoSrchListInfoAddr();

    if (VOS_NULL_PTR != pstGeoListSrchInfo->pstGeoSrchInfo)
    {
        PS_MEM_FREE(UEPS_PID_XSD, pstGeoListSrchInfo->pstGeoSrchInfo);

        pstGeoListSrchInfo->pstGeoSrchInfo = VOS_NULL_PTR;
    }
}


VOS_VOID CNAS_XSD_InitHistorySyncedSysFreqList(
    CNAS_XSD_HISTORY_SYNCED_SYS_FREQ_LIST_STRU             *pstHisSyncedSysFreqList
)
{
    pstHisSyncedSysFreqList->ulCurNum   = 0;
    pstHisSyncedSysFreqList->ulTotalNum = 0;
    NAS_MEM_SET_S(&(pstHisSyncedSysFreqList->astFreq[0]),
                  sizeof(pstHisSyncedSysFreqList->astFreq),
                  0,
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * CNAS_XSD_1X_SYNC_SUCC_FREQ_MAX_NUM);
}


CNAS_XSD_HISTORY_SYNCED_SYS_FREQ_LIST_STRU* CNAS_XSD_GetHistorySyncedSysFreqList(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stHisSyncedSysFreqList);
}


VOS_VOID CNAS_XSD_UpdateHistorySyncedSysFreqList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq
)
{
    CNAS_XSD_HISTORY_SYNCED_SYS_FREQ_LIST_STRU             *pstHisSyncedSysList = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstHisSyncedSysList = CNAS_XSD_GetHistorySyncedSysFreqList();

    /* 查找是否已在列表中 */
    for (i = 0; i < CNAS_MIN(pstHisSyncedSysList->ulCurNum, CNAS_XSD_1X_SYNC_SUCC_FREQ_MAX_NUM); i++)
    {
        if (0 == PS_MEM_CMP(pstFreq,
                            &(pstHisSyncedSysList->astFreq[i]),
                            sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU)))
        {
            NAS_MEM_MOVE_S(&(pstHisSyncedSysList->astFreq[1]),
                           sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * (CNAS_XSD_1X_SYNC_SUCC_FREQ_MAX_NUM - 1),
                           &(pstHisSyncedSysList->astFreq[0]),
                           sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * i);

            NAS_MEM_CPY_S(&(pstHisSyncedSysList->astFreq[0]),
                          sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU),
                          pstFreq,
                          sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU));
            return;
        }
    }

    /* 所有记录后移，最新的system保存在index 0的位置 */
    if (pstHisSyncedSysList->ulCurNum < CNAS_XSD_1X_SYNC_SUCC_FREQ_MAX_NUM)
    {
        NAS_MEM_MOVE_S(&(pstHisSyncedSysList->astFreq[1]),
                       sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * (CNAS_XSD_1X_SYNC_SUCC_FREQ_MAX_NUM - 1),
                       &(pstHisSyncedSysList->astFreq[0]),
                       sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * pstHisSyncedSysList->ulCurNum);

        pstHisSyncedSysList->ulCurNum++;
    }
    else
    {
        NAS_MEM_MOVE_S(&(pstHisSyncedSysList->astFreq[1]),
                       sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * (CNAS_XSD_1X_SYNC_SUCC_FREQ_MAX_NUM - 1),
                       &(pstHisSyncedSysList->astFreq[0]),
                       sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * (CNAS_XSD_1X_SYNC_SUCC_FREQ_MAX_NUM - 1));
    }

    NAS_MEM_CPY_S(&(pstHisSyncedSysList->astFreq[0]),
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU),
                  pstFreq,
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU));

    return;
}


CNAS_PRL_1X_SYSTEM_ID_STRU* CNAS_XSD_GetLastSyncedSys(VOS_VOID)
{
    CNAS_XSD_CTX_STRU                  *pstXsdCtx = VOS_NULL_PTR;

    pstXsdCtx = CNAS_XSD_GetXsdCtxAddr();

    return &(pstXsdCtx->stCurFsm.unFsmCtx.stSysAcqCtx.stLastSyncedSys);
}


CNAS_PRL_FREQENCY_CHANNEL_STRU* CNAS_XSD_GetLastSyncedFreq(VOS_VOID)
{
    return &(CNAS_XSD_GetHistorySyncedSysFreqList()->astFreq[0]);
}



VOS_VOID CNAS_XSD_UpdateLastSyncedSys(
    CNAS_PRL_1X_SYSTEM_ID_STRU         *pstCurSyncedSys
)
{
    CNAS_PRL_1X_SYSTEM_ID_STRU         *pstLastSyncedSys = VOS_NULL_PTR;

    pstLastSyncedSys = CNAS_XSD_GetLastSyncedSys();

    pstLastSyncedSys->usNid = pstCurSyncedSys->usNid;
    pstLastSyncedSys->usSid = pstCurSyncedSys->usSid;
}


CNAS_XSD_CALL_REL_ANY_CAMP_ON_FREQ_STRU* CNAS_XSD_GetCallRelAnyCampOnFreqListAddr(VOS_VOID)
{
    /* 如果当前状态机不是CNAS_XSD_FSM_SYS_ACQ */
    if (CNAS_XSD_FSM_SYS_ACQ != CNAS_XSD_GetCurrFsmId())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetAvailSysFreqListAddr: Wrong state ENTERED");
    }

    return &(CNAS_XSD_GetXsdCtxAddr()->stCurFsm.unFsmCtx.stSysAcqCtx.stCallRelFirstSyncFreq);
}


CNAS_XSD_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU* CNAS_XSD_GetCdma1XCustomPrefChannels(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCdma1XCustomPrefChan);
}


VOS_UINT8 CNAS_XSD_GetNoCardModeCfgFlg()
{
    return (CNAS_XSD_GetTestConfig()->ucNoCardModeCfgFlg);
}


VOS_VOID CNAS_XSD_SetNoCardModeCfgFlg(
    VOS_UINT8                           ucNoCardModeCfgFlg
)
{
    CNAS_XSD_GetTestConfig()->ucNoCardModeCfgFlg = ucNoCardModeCfgFlg;

    return;
}


CNAS_XSD_EMC_REDIAL_SYS_ACQ_CFG_STRU* CNAS_XSD_GetEmcRedialSysAcqCfgInfo()
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.stEmcRedialSysAcqCfg);

}


/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



