/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdMain.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年06月27日
  功能描述   : 1X SD(system determination)任务初始化，任务入口函数处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年06月27日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/

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
/*****************************************************************************
 函 数 名  : CNAS_XSD_InitCurrFsmCtx
 功能描述  : 初始化当前状态机上下文
 输入参数  : 无
 输出参数  : pstCurrFsmCtx -- 当前状态机上下文信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月14日
   作    者   : y00245242
   修改内容   : 新生成函数

 2.日    期   : 2015年7月17日
   作    者   : y00245242
   修改内容   : iteration 17开发

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_InitFsmStackCtx
 功能描述  : 初始化状态机栈上下文
 输入参数  : 无
 输出参数  : pstFsmStack -- 状态机栈信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月14日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : CNAS_XSD_InitCacheMsgQueue
 功能描述  : 初始化缓存的消息队列
 输入参数  : 无
 输出参数  : pstCacheMsgQueue -- 缓存的消息队列信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月14日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2015年09月07日
   作    者   : w00176964
   修改内容   : CNAS内存裁剪调整
*****************************************************************************/
VOS_VOID CNAS_XSD_InitCacheMsgQueue(
    CNAS_XSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType,
    CNAS_XSD_CACHE_MSG_QUEUE_STRU      *pstCacheMsgQueue
)
{
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-7, begin */
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

    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-7, end */
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_InitScanChanList
 功能描述  : 初始化频点扫描列表
 输入参数  : enInitType----初始化类型
 输出参数  : pstScanChanList -- 频点扫描列表
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年08月14日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_InitCurCampedSysInfo
 功能描述  : 初始化当前驻留的系统信息
 输入参数  : CNAX_XSD_CAMPED_SYS_INFO_STRU      *pstCurCampedSysInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月21日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年7月10日
    作    者   : y00245242
    修改内容   : iteration 17开发

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_InitCallRedialCtrlInfo
 功能描述  : 初始化呼叫重拨的控制信息
 输入参数  : CNAS_XSD_CALL_REDIAL_CTRL_INFO_STRU  pstCallRedialInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月2日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : CNAS_XSD_InitCallRedialCtrlInfo
 功能描述  : 初始化紧急呼叫重拨的控制信息
 输入参数  : CNAS_XSD_EMC_CALL_CTRL_INFO_STRU  pstEmcCallInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月04日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_InitAvailSysList
 功能描述  : Init available system list
 输入参数  : CNAS_XSD_AVAILABLE_LIST_STRU  pstAvailList
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月25日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2015年7月9日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_InitRedirectionInfo
 功能描述  : clear redirection info
 输入参数  : CNAS_XSD_REDIRECTION_INFO_STRU  pstRedirInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月25日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
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



/*****************************************************************************
 函 数 名  : CNAS_XSD_InitSystemAcquireCtrl
 功能描述  : 初始化1X系统获取控制信息
 输入参数  : enInitType------初始化类型
 输出参数  : pstSysAcqCtrl -- 系统获取控制信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月14日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2014年08月14日
   作    者   : w00176964
   修改内容   : 增加初始化类型
 3.日    期   : 2015年1月3日
   作    者   : y00245242
   修改内容   : HOME SID/NID list 开发
*****************************************************************************/
VOS_VOID CNAS_XSD_InitSystemAcquireCtrl(
    CNAS_XSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType,
    CNAS_XSD_SYSTEM_ACQUIRE_CTRL_STRU  *pstSysAcqCtrl
)
{
    /* Deleted by w00176964 for CNAS内存裁剪, 2015-9-6, begin */

    /* Deleted by w00176964 for CNAS内存裁剪, 2015-9-6, end */

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

/*****************************************************************************
 函 数 名  : CNAS_XSD_InitFsmCtx_L1Main
 功能描述  : 初始化L1状态机上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月04日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_InitFsmCtx_SwitchOn
 功能描述  : 初始化开机状态机上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月14日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : CNAS_XSD_InitFsmCtx_PowerOff
 功能描述  : 初始化关机状态机上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月20日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : CNAS_XSD_InitFsmCtx_SysAcq
 功能描述  : 初始化SYSTEM ACQUIRE状态机的上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月8日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2014年12月25日
    作    者   : w00176964
    修改内容   : CDMA Iteration 6:Move the avail system list to the global variables

  3.日    期   : 2015年7月6日
    作    者   : y00245242
    修改内容   : iteration 17开发

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : CNAS_XSD_InitCtx
 功能描述  : XSD 上下文全局变量初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月04日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2014年10月15日
   作    者   : c00299063
   修改内容   : CNAS XSD缓存内部消息队列初始化
*****************************************************************************/
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
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, begin */
    CNAS_XSD_InitCacheMsgQueue(enInitType, &(pstXsdCtx->stCacheMsgQueue));
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, end */

    /* CNAS XSD缓存内部消息队列初始化 */
    CNAS_XSD_InitInternalBuffer(&(CNAS_XSD_GetXsdCtxAddr()->stIntMsgQueue));

    /* CNAS XSD系统获取控制初始化 */
    CNAS_XSD_InitSystemAcquireCtrl(enInitType, &(pstXsdCtx->stSysAcqCtrl));

    CNAS_XSD_InitCFreqLockValue();

    CNAS_XSD_InitTestConfig(&(pstXsdCtx->stTestConfig));

    CNAS_XSD_InitSysAcqNvimCfg(&(pstXsdCtx->stSysAcqNvimCfg));
    CNAS_CCB_Set1xReturnCause(CNAS_CCB_1X_RETURN_CAUSE_NORMAL_ACCESS);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_LoadSubFsm
 功能描述  : 加载L2状态机的信息
 输入参数  : enFsmId - L2状态机ID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月14日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2014年12月25日
   作    者   : w00176964
   修改内容   : CDMA IX Iteration 6 Modified:Add redirection state machine

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_PushFsm
 功能描述  : 对状态机进行压栈
 输入参数  : pstFsmStack -- 状态机栈
             pstNewFsm   -- 需要压入的状态机
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月04日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_PopFsm
 功能描述  : 对状态机进行出栈
 输入参数  : 无
             无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月04日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_InitFsmL2
 功能描述  : XSD启动一个L2的状态机。启动流程的同时启动状态以及保护定时器
              该函数会进行压栈操作,如果不需要进行协议栈压栈, 必须保证退出前流程
 输入参数  : enFsmId -- L2状态机ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月07日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2015年01月17日
   作    者   : y00307564
   修改内容   : 清TQE

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_QuitFsmL2
 功能描述  : 结束L2状态机。如果结束流程，状态机弹出状态栈
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月07日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2015年01月17日
   作    者   : y00307564
   修改内容   : 清TQE

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetXsdCtxAddr
 功能描述  : 获取当前XSD的CTX
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回当前XSD的CTX地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月04日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_XSD_CTX_STRU* CNAS_XSD_GetXsdCtxAddr(VOS_VOID)
{
    return &(g_stCnasXsdCtx);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetFsmStackAddr
 功能描述  : 获取当前状态机栈地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机栈地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月04日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_XSD_FSM_STACK_STRU* CNAS_XSD_GetFsmStackAddr(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stFsmStack);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetCurFsmAddr
 功能描述  : 获取当前状态机地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月04日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_XSD_FSM_CTX_STRU* CNAS_XSD_GetCurFsmAddr(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stCurFsm);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetFsmTopState
 功能描述  : 获取状态机顶层的状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机的顶层状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月14日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_GetFsmTopState(VOS_VOID)
{
    return (CNAS_XSD_GetCurFsmAddr()->ulState);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetCurFsmDesc
 功能描述  : 获取当前状态机表的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机表的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月14日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU* CNAS_XSD_GetCurFsmDesc(VOS_VOID)
{
    return (CNAS_XSD_GetCurFsmAddr()->pstFsmDesc);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetFsmStackDepth
 功能描述  : 获取当前协议栈的栈深度
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机的深度
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月04日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 CNAS_XSD_GetFsmStackDepth(VOS_VOID)
{
    CNAS_XSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = CNAS_XSD_GetFsmStackAddr();

    return pstFsmStack->usStackDepth;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SetFsmStackPopFlg
 功能描述  : 设置状态机栈pop标志
 输入参数  : ucStackPopFlg -- 栈pop标志
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月04日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_SetFsmStackPopFlg(
    VOS_UINT16                          ucStackPopFlg
)
{
    CNAS_XSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = CNAS_XSD_GetFsmStackAddr();

    pstFsmStack->usStackPopFlg = ucStackPopFlg;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetFsmStackPopFlg
 功能描述  : 获取状态机栈pop标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回栈pop标志
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月04日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 CNAS_XSD_GetFsmStackPopFlg(VOS_VOID)
{
    CNAS_XSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = CNAS_XSD_GetFsmStackAddr();

    return pstFsmStack->usStackPopFlg;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetCacheMsgAddr
 功能描述  : 获取当前的缓存消息地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CNAS XSD缓存消息队列
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月04日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_XSD_CACHE_MSG_QUEUE_STRU* CNAS_XSD_GetCacheMsgAddr(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stCacheMsgQueue);
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_GetAvoidScheduInfoAddr
 功能描述  : 获取AvoidScheduInfo地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CNAS_XSD_AVOID_SCHEDULE_INFO_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年11月12日
   作    者   : c00299063
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_XSD_AVOID_SCHEDULE_INFO_STRU* CNAS_XSD_GetAvoidScheduInfoAddr(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stAvoidScheduInfo);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetAvoidFreqIndexOfAvoidlist
 功能描述  : 从avoid列表中获取频点索引
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月16日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
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
/*****************************************************************************
 函 数 名  : CNAS_XSD_SaveCacheMsgInMsgQueue
 功能描述  : 将缓存消息保存的缓存内存池中
 输入参数  : ulEventType -- 消息ID+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月14日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2015年09月07日
   作    者   : w00176964
   修改内容   : CNAS内存裁剪调整

*****************************************************************************/
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

    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-7, begin */
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
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-7, end */

    pstMsgQueue->ucCacheMsgNum++;

    CNAS_XSD_LogBufferQueueMsg(VOS_FALSE);

    CNAS_INFO_LOG1(UEPS_PID_XSD, "CNAS_XSD_SaveCacheMsgInMsgQueue: Cache Num = %d", pstMsgQueue->ucCacheMsgNum);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SaveCacheMsg
 功能描述  : 保存当前需要处理的缓存
 输入参数  : ulEventType -- 消息ID+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 保存成功
             VOS_FALSE -- 保存失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月14日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : CNAS_XSD_ClearCacheMsg
 功能描述  : 清除指定的缓存消息
 输入参数  : ulCurrIndex -- 清除指定index的消息
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月14日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2015年09月07日
   作    者   : w00176964
   修改内容   : CNAS内存裁剪调整
*****************************************************************************/
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

        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-7, begin */
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
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-7, end */
    }

    CNAS_XSD_LogBufferQueueMsg(VOS_FALSE);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ClearCacheMsgByMsgName
 功能描述  : 根据MsgName匹配清除对应的缓存消息
 输入参数  : VOS_UINT32                          ulSndPid  消息PID
             VOS_UINT16                          usMsgName 消息名称
 输出参数  : 无
 返 回 值  : VOS_UINT32:
             VOS_TRUE  : 找到对应消息并进行了清理
             VOS_FALSE : 未找到对应消息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年07月20日
   作    者   : h00313353
   修改内容   : 新生成函数
 2.日    期   : 2015年09月07日
   作    者   : w00176964
   修改内容   : CNAS内存裁剪调整
*****************************************************************************/
VOS_UINT32 CNAS_XSD_ClearCacheMsgByMsgName(
    VOS_UINT32                          ulSndPid,
    VOS_UINT16                          usMsgName
)
{
    VOS_UINT32                          ulCurCacheMsgNum;
    /* Added by w00176964 for CNAS内存裁剪, 2015-9-7, begin */
    VOS_UINT32                          ulCacheMsgEventType;
    MSG_HEADER_STRU                    *pstCacheMsg;
    REL_TIMER_MSG                      *pstTimerMsg;
    /* Added by w00176964 for CNAS内存裁剪, 2015-9-7, end */
    VOS_UINT32                          ulEventType;
    VOS_UINT32                          i;

    ulCurCacheMsgNum                    = CNAS_XSD_GetCacheMsgNum();
    ulEventType                         = CNAS_BuildEventType(ulSndPid, usMsgName);

    for (i = 0; i < ulCurCacheMsgNum; i++)
    {
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-7, begin */
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
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-7, end */
        {
            CNAS_XSD_ClearCacheMsg((VOS_UINT8)i);

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_GetNextCachedMsg
 功能描述  : 获取当前需要处理的缓存
 输入参数  : 无
 输出参数  : pstEntryMSg -- 当前需要处理的消息地址

 返 回 值  : VOS_TRUE  -- 获取成功
             VOS_FALSE -- 获取失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月04日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2015年09月07日
   作    者   : w00176964
   修改内容   : CNAS内存裁剪调整

*****************************************************************************/
VOS_UINT32 CNAS_XSD_GetNextCachedMsg(
    CNAS_XSD_MSG_STRU                  *pstEntryMsg
)
{
    CNAS_XSD_CACHE_MSG_QUEUE_STRU      *pstMsgQueue = VOS_NULL_PTR;
    /* Added by w00176964 for CNAS内存裁剪, 2015-9-7, begin */
    MSG_HEADER_STRU                    *pstCacheMsgHdr = VOS_NULL_PTR;
    REL_TIMER_MSG                      *pstTimerMsg;
    /* Added by w00176964 for CNAS内存裁剪, 2015-9-7, end */

    pstMsgQueue = CNAS_XSD_GetCacheMsgAddr();

    if ( 0 == pstMsgQueue->ucCacheMsgNum )
    {
        CNAS_INFO_LOG(UEPS_PID_XSD, "CNAS_XSD_GetNextCachedMsg:Empty buffer");

        return VOS_FALSE;
    }

    /* 按照先入先出原则,默认取第1个缓存内容 */
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-7, begin */
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
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-7, end */

    /* 清除index为0的cache消息 */
    CNAS_XSD_ClearCacheMsg(0);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetCacheMsgNum
 功能描述  : 获取当前缓存的消息个数
 输入参数  : 无
 输出参数  :
 返 回 值  : 当前存在的缓存个数
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月04日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_GetCacheMsgNum(VOS_VOID)
{
    CNAS_XSD_CACHE_MSG_QUEUE_STRU      *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue = CNAS_XSD_GetCacheMsgAddr();

    return pstMsgQueue->ucCacheMsgNum;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SetCurrFsmState
 功能描述  : 设置当前需要迁移的状态
 输入参数  : ulCurrState:当前迁移的状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月11日
    作    者   : h00246512
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetCurrFsmEntryMsgAddr
 功能描述  : 获取当前状态机入口消息的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机入口消息的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月12日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_XSD_MSG_STRU* CNAS_XSD_GetCurrFsmEntryMsgAddr(VOS_VOID)
{
    return &(g_stCnasXsdCtx.stCurFsm.stEntryMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SaveCurEntryMsg
 功能描述  : 保存当前状态机的入口消息
 输入参数  : ulEventType            :入口消息类型
              pstMsg             :入口消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期   : 2014年7月11日
     作    者   : h00246512
     修改内容   : 新生成函数

*****************************************************************************/
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

    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-16, begin */
    if (ulLen > CNAS_XSD_MAX_MSG_BUFFER_LEN)
    {
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_SaveCurEntryMsg:beyond the Size!");

        ulLen = CNAS_XSD_MAX_MSG_BUFFER_LEN;
    }
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-16, end */

    /* 将当前处理的入口消息拷贝到Context对应的缓冲区 */
    NAS_MEM_CPY_S( pstEntryMsg->aucMsgBuffer, sizeof(pstEntryMsg->aucMsgBuffer), pstMsg, ulLen );

    /* 填写Context中的参数 */
    pstEntryMsg->ulEventType    = ulEventType;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetCurrFsmId
 功能描述  : 获取当前状态机的ID
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机的ID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月11日
   作    者   : h00246512
   修改内容   : 新生成函数


*****************************************************************************/
CNAS_XSD_FSM_ID_ENUM_UINT32 CNAS_XSD_GetCurrFsmId(VOS_VOID)
{
    return (g_stCnasXsdCtx.stCurFsm.enFsmId);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SetWaitCardFilesCnfFlg_SwitchOn
 功能描述  : 开机过程中获取读取卡文件回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 读取卡文件回复标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014年7月11日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_SetWaitCardFilesCnfFlg_SwitchOn
 功能描述  : 开机过程中设置读取卡文件回复标记
 输入参数  : 设置卡文件回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014年7月11日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetCampOnNeedFlg_PowerOff
 功能描述  : 获取关机过程中是否需要驻留标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 关机过程中是否需要驻留标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014年10月19日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_SetCampOnNeedFlg_PowerOff
 功能描述  : 设置关机过程中是否需要驻留标记
 输入参数  : 驻留标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014年10月20s日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetBufCallRelIndFlg_PowerOff
 功能描述  : 获取关机过程中缓存的呼叫释放指示标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 关机过程中缓存的呼叫释放指示标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014年10月19日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_SetBufCallRelIndFlg_PowerOff
 功能描述  : 设置关机过程中缓存的呼叫释放指示标记
 输入参数  : 呼叫释放指示标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014年10月20s日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetBufCallRelFreqInfo_PowerOff
 功能描述  : 获取关机过程中缓存的呼叫释放指示的频点信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 关机过程中缓存的呼叫释放指示的频点信息
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014年10月19日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
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



/*****************************************************************************
 函 数 名  : CNAS_XSD_SaveBufCallRelFreqInfo_PowerOff
 功能描述  : 保存关机过程中缓存的呼叫释放指示的频点信息
 输入参数  : 呼叫释放指示的频点信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014年10月19日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : CNAS_XSD_GetTestConfig
 功能描述  : 获取stTestConfig首地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回stTestConfig首地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年5月11日
   作    者   : c00299063
   修改内容   : 新生成函数
*****************************************************************************/
CNAS_XSD_TEST_CONFIG_STRU* CNAS_XSD_GetTestConfig(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stTestConfig);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_Get1xSysAcqNvimConfig
 功能描述  : 获取stSysAcqNvimCfg首地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回stSysAcqNvimCfg首地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年6月8日
   作    者   : c00299063
   修改内容   : 新生成函数
*****************************************************************************/
CNAS_XSD_SYS_ACQ_NVIM_CFG_STRU* CNAS_XSD_Get1xSysAcqNvimConfig(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqNvimCfg);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetAcqPrefSysflg
 功能描述  : 是否按GEO中，存在匹配的pref系统，就按pref系统处理的标记
 输入参数  :
 输出参数  :
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月5日
    作    者   : c00299063
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_XSD_NEG_PREF_SYS_CMP_TYPE_ENUM_UINT8 CNAS_XSD_GetNegPrefSysCmpType()
{
    return (CNAS_XSD_Get1xSysAcqNvimConfig()->stNegPrefSysCmpCtrl.enNegPrefSysCmpType);
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn
 功能描述  : 开机过程中清除读取卡文件回复标记
 输入参数  : 卡文件回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014年7月11日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetMruList
 功能描述  : 获取MRU table首地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回MRU table首地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年08月06日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_XSD_MRU_LIST_STRU* CNAS_XSD_GetMruList(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stMruList);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetMruListNum
 功能描述  : 获取MRU table中系统个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回MRU table中系统个数
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年08月08日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetMruListNum(VOS_VOID)
{
    return (CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stMruList.ucSysNum);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetMru0SysId
 功能描述  : 获取MRU0对应的系统ID
 输入参数  : 无
 输出参数  : pstMru0SysId------MRU0对应的系统ID
 返 回 值  : 获取成功:VOS_TRUE
             获取失败:VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年08月08日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetMru1SysId
 功能描述  : 获取MRU1对应的系统ID
 输入参数  : 无
 输出参数  : pstMru0SysId------MRU1对应的系统ID
 返 回 值  : 获取成功:VOS_TRUE
             获取失败:VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年12月21日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateMru0
 功能描述  : 更新MRU0记录的网络信息
 输入参数  : pstCurNetwork -- 当前驻留的

 输出参数  : 无

 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年08月06日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : CNAS_XSD_GetScanChanListAddr
 功能描述  : 获取频点扫描列表的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前频点扫描列表的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年8月6日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/

CNAS_XSD_SCAN_CHANNEL_LIST_STRU* CNAS_XSD_GetScanChanListAddr(VOS_VOID)
{
    return &(g_stCnasXsdCtx.stSysAcqCtrl.stChanScanList);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetScanChannelNum
 功能描述  : 获取当前频点扫描列表中频点总个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前频点扫描列表中频点总个数
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年8月6日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 CNAS_XSD_GetScanChannelNum(VOS_VOID)
{
    return (g_stCnasXsdCtx.stSysAcqCtrl.stChanScanList.usTotalNum);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetCurChannelScanIndex
 功能描述  : 获取当前频点扫描列表中当前扫描到的列表索引
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前频点扫描列表中当前扫描到的列表索引
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年8月6日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 CNAS_XSD_GetCurChannelScanIndex(VOS_VOID)
{
    return (g_stCnasXsdCtx.stSysAcqCtrl.stChanScanList.usCurScanIndex);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SetCurChannelScanIndex
 功能描述  : 设置当前频点扫描列表中当前扫描到的列表索引
 输入参数  : usCurScanIndex------当前频点扫描列表中当前扫描到的列表索引
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年8月6日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_SetCurChannelScanIndex(
    VOS_UINT16                          usCurScanIndex
)
{
    g_stCnasXsdCtx.stSysAcqCtrl.stChanScanList.usCurScanIndex = usCurScanIndex;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetAvailSysFreqListAddr
 功能描述  : 获取available system list地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_XSD_AVAILABLE_LIST_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月14日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2014年12月25日
    作    者   : w00176964
    修改内容   : CDMA Iteration 6:Move the avail system list to the global variables
  3.日    期   : 2015年7月9日
    作    者   : y00245242
    修改内容   : iteration 17开发

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_AddAvailSysFreqList
 功能描述  : 更新available system频点
 输入参数  : CNAS_PRL_1X_SYSTEM_STRU            *pstAvailSys
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2014年12月25日
    作    者   : w00176964
    修改内容   : CDMA Iteration 6:Move the avail system list to the global variables
  3.日    期   : 2015年7月17日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_SetAvailSysFeqListNextSrchIndex
 功能描述  : 设置available system list的下次搜索索引
 输入参数  : ucNextSrchIndex------下次列表的搜索索引
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年7月6日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_SetAvailSysFeqListNextSrchIndex(
    VOS_UINT8                           ucNextSrchIndex
)
{
    CNAS_XSD_AVAILABLE_LIST_STRU       *pstAvailSysList = VOS_NULL_PTR;

    pstAvailSysList = CNAS_XSD_GetAvailSysFreqListAddr();

    pstAvailSysList->ucNextSrchIndex = ucNextSrchIndex;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetAvailSysFreqListNextSrchIndex
 功能描述  : 获取available system list的下次搜索索引
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8 -- 返回下次available系统的搜索索引
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年7月6日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetAvailSysFreqListNextSrchIndex(VOS_VOID)
{
    CNAS_XSD_AVAILABLE_LIST_STRU       *pstAvailSysList = VOS_NULL_PTR;

    pstAvailSysList = CNAS_XSD_GetAvailSysFreqListAddr();

    return pstAvailSysList->ucNextSrchIndex;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetAvailSysFreqNum
 功能描述  : 获取available system的个数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月13日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2014年12月25日
    作    者   : w00176964
    修改内容   : CDMA Iteration 6:Move the avail system list to the global variables

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetAvailSysFreqNum(VOS_VOID)
{
    CNAS_XSD_AVAILABLE_LIST_STRU       *pstAvailSysList = VOS_NULL_PTR;

    pstAvailSysList = CNAS_XSD_GetAvailSysFreqListAddr();

    return pstAvailSysList->ucAvailSysNum;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SetAvailSysAcqListFlg_SysAcq
 功能描述  : 设置当前获取列表是否为available system list
 输入参数  : VOS_UINT8                           ucFlg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月14日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetAvailSysAcqListFlg_SysAcq
 功能描述  : 获取当前获取列表是否为available system list
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月14日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_SetAbortFlg_SysAcq
 功能描述  : 设置当前状态机打断标记
 输入参数  : VOS_UINT8                           ucFlg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月15日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetAbortFlg_SysAcq
 功能描述  : 获取当前状态机打断标记
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月15日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetCurChannelScanIndex_Redir
 功能描述  : 获取重定向中，当前scan list的索引
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月29日
    作    者   : w00242748
    修改内容   : iteration 17开发

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_SetCurChannelScanIndex_Redir
 功能描述  : 设置重定向中，当前scan list的索引
 输入参数  : VOS_UINT16
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月29日
    作    者   : w00242748
    修改内容   : iteration 17开发

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : CNAS_XSD_SetCallFlg
 功能描述  : 设置呼叫标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CNAS_XSD_SCAN_CHANNEL_LIST_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : c00299063
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_XSD_SCAN_CHANNEL_LIST_STRU* CNAS_XSD_GetCallRedialScanChanListAddr(VOS_VOID)
{
    return  (&(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCallRedialInfo.stCallRedialChanScanList));
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetEmcCallRedialScanChanListAddr
 功能描述  : 获取紧急呼呼叫重播搜网列表地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CNAS_XSD_SCAN_CHANNEL_LIST_STRU *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月07日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_XSD_SCAN_CHANNEL_LIST_STRU *CNAS_XSD_GetEmcCallRedialScanChanListAddr(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.stEmcCallRedialChanScanList);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SetCallExistFlg
 功能描述  : 设置呼叫存在标记
 输入参数  : VOS_UINT8                           ucCallExistFlg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : c00299063
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_SetCallExistFlg(
    VOS_UINT8                           ucCallExistFlg
)
{
    CNAS_XSD_CALL_REDIAL_CTRL_INFO_STRU *pstCallStartSysInfo = VOS_NULL_PTR;

    pstCallStartSysInfo = &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCallRedialInfo);

    pstCallStartSysInfo->ucCallExistFlg |= ucCallExistFlg;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ClearEmcCallRedialScanChanList
 功能描述  : 清除紧急呼呼叫重拨搜网频点列表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年07月07日
   作    者   : h00313353
   修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_ClearCallExistFlg
 功能描述  : 清除呼叫存在标记
 输入参数  : VOS_UINT8                           ucCallExistFlg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : c00299063
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_ClearCallExistFlg(
    VOS_UINT8                           ucCallExistFlg
)
{
    CNAS_XSD_CALL_REDIAL_CTRL_INFO_STRU *pstCallStartSysInfo = VOS_NULL_PTR;

    pstCallStartSysInfo = &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCallRedialInfo);

    pstCallStartSysInfo->ucCallExistFlg &= ~(ucCallExistFlg);

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_GetCallExistFlg
 功能描述  : 获取呼叫存在标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 呼叫存在标记
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : c00299063
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetCallExistFlg(VOS_VOID)
{
    CNAS_XSD_CALL_REDIAL_CTRL_INFO_STRU *pstCallStartSysInfo = VOS_NULL_PTR;

    pstCallStartSysInfo = &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCallRedialInfo);

    return (pstCallStartSysInfo->ucCallExistFlg);
}



/*****************************************************************************
 函 数 名  : CNAS_XSD_SetCallOrigSysExistFlg
 功能描述  : 设置呼叫发起系统存在标记
 输入参数  : VOS_UINT8                           ucFlg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : c00299063
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_SetCallOrigSysExistFlg(
    VOS_UINT8                           ucFlg
)
{
    CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCallRedialInfo.ucOrigSysExistFlg = ucFlg;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetCallOrigSysExistFlg
 功能描述  : 获取呼叫发起系统存在标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : c00299063
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetCallOrigSysExistFlg(VOS_VOID)
{
    return (CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCallRedialInfo.ucOrigSysExistFlg);

}



/*****************************************************************************
 函 数 名  : CNAS_XSD_SaveCallOrignalSys
 功能描述  : 保存当前呼叫发起的系统
 输入参数  : CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : c00299063
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_SaveCallOrignalSys(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysId
)
{
    CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCallRedialInfo.stCallOrignalSys = *pstCurSysId;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetCallOrignalSys
 功能描述  : 获取当前呼叫发起的系统
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_PRL_1X_SYSTEM_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : c00299063
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_PRL_1X_SYSTEM_STRU *CNAS_XSD_GetCallOrignalSys(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCallRedialInfo.stCallOrignalSys);

}


/*****************************************************************************
 函 数 名  : CNAS_XSD_SaveEmcCallOrignalSys
 功能描述  : 保存紧急呼建立成功时的系统
 输入参数  : CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月02日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_SaveEmcCallOriginalSys(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysId
)
{
    CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.stCallOrignalSys = *pstCurSysId;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetEmcCallOrignalSys
 功能描述  : 获取当前紧急呼叫建立成功时的系统
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_PRL_1X_SYSTEM_STRU *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月07日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_PRL_1X_SYSTEM_STRU *CNAS_XSD_GetEmcCallOriginalSys(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.stCallOrignalSys);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ClearEmcCallOrignalSys
 功能描述  : 清除当前紧急呼叫建立成功时的系统
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_PRL_1X_SYSTEM_STRU *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月07日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_ClearEmcCallOriginalSys( VOS_VOID )
{
    NAS_MEM_SET_S(CNAS_XSD_GetEmcCallOriginalSys(), sizeof(CNAS_PRL_1X_SYSTEM_STRU), 0x00, sizeof(CNAS_PRL_1X_SYSTEM_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsEmcCallOrignalSysExist
 功能描述  : 判断当前紧急呼呼叫发起系统是否存在
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月07日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq
 功能描述  : 获取指定索引的捕获系统信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SYS ACQ状态机上下文中系统捕获列表首地址
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014年8月9日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU* CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq(VOS_VOID)
{
    CNAS_XSD_CTX_STRU                  *pstXsdCtx = VOS_NULL_PTR;

    pstXsdCtx = CNAS_XSD_GetXsdCtxAddr();

    return &(pstXsdCtx->stCurFsm.unFsmCtx.stSysAcqCtx.stGeoSysSrchList);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetCurSysAcqListNum_SysAcq
 功能描述  : 获取当前系统捕获列表的个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前系统捕获列表的索引
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014年8月9日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : CNAS_XSD_GetCurCampedSysInfo
 功能描述  : 获取当前驻留系统信息地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAX_XSD_CAMPED_SYS_INFO_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月21日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
CNAX_XSD_CAMPED_SYS_INFO_STRU* CNAS_XSD_GetCurCampedSysInfo(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCurCampedSysInfo);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateCurCampedSysInfo
 功能描述  : 更新当前驻留系统信息
 输入参数  : CNAX_XSD_CAMPED_SYS_INFO_STRU      *pstCurCampedSysInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月21日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateCurCampedSysInfo(
    CNAX_XSD_CAMPED_SYS_INFO_STRU      *pstCurCampedSysInfo
)
{
    NAS_MEM_CPY_S(CNAS_XSD_GetCurCampedSysInfo(), sizeof(CNAX_XSD_CAMPED_SYS_INFO_STRU), pstCurCampedSysInfo, sizeof(CNAX_XSD_CAMPED_SYS_INFO_STRU));

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_GetCurSrvStatus
 功能描述  : 获取当前服务状态
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_XSD_SERVICE_STATUS_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月10日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_XSD_SERVICE_STATUS_ENUM_UINT32 CNAS_XSD_GetCurSrvStatus(VOS_VOID)
{
    CNAX_XSD_CAMPED_SYS_INFO_STRU                          *pstCurCampedSysInfo = VOS_NULL_PTR;

    pstCurCampedSysInfo = CNAS_XSD_GetCurCampedSysInfo();

    return pstCurCampedSysInfo->enSrvStatus;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SetCurSrvStatus
 功能描述  : 设置当前服务状态
 输入参数  : enSrvStatus -- 服务状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月10日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetIntMsgQueueAddr
 功能描述  : 获取内部消息队列首地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_XSD_INT_MSG_QUEUE_STRU *
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年10月15日
   作    者   : c00299063
   修改内容   : 新生成函数
*****************************************************************************/
CNAS_XSD_INT_MSG_QUEUE_STRU* CNAS_XSD_GetIntMsgQueueAddr(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stIntMsgQueue);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_InitInternalBuffer
 功能描述  : 初始化XSD内部消息上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年10月15日
   作    者   : c00299063
   修改内容   : 新生成函数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : CNAS_XSD_PutMsgInIntMsgQueue
 功能描述  : 将消息放到内部消息队列中
 输入参数  : pSndMsg:待发送的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月15日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetNextIntMsg
 功能描述  : 获取内部消息队列中的下一条可用的内部消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 内部消息队列的指针
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年10月15日
   作    者   : c00299063
   修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetIntMsgNum
 功能描述  : 获取当前XSD内部消息个数
 输入参数  : 无
 输出参数  :
 返 回 值  : 当前存在的内部消息个数
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月0423
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetIntMsgNum(VOS_VOID)
{
    VOS_UINT8                           ucIntMsgNum;

    ucIntMsgNum = CNAS_XSD_GetIntMsgQueueAddr()->ucIntMsgNum;

    return ucIntMsgNum;
}




/*****************************************************************************
 函 数 名  : CNAS_XSD_GetAvoidFreqListAddr
 功能描述  : 获取avoid 频点列表地址
 输入参数  : 无

 输出参数  : 无
 返 回 值  : CNAS_XSD_AVOID_FREQ_LIST_STRU* -- avoid频点列表首地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月14日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_XSD_AVOID_FREQ_LIST_STRU* CNAS_XSD_GetAvoidFreqListAddr(VOS_VOID)
{
    return &(g_stCnasXsdCtx.stSysAcqCtrl.stAvoidFreqList);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetAvoidFreqListNum
 功能描述  : 获取avoid 频点列表数目
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_UINT8 -- avoid列表数目
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月14日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetAvoidFreqListNum(VOS_VOID)
{
    return (CNAS_XSD_GetAvoidFreqListAddr()->ucAvoidFreqNum);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_DeleteAvoidFreqFromAvoidList
 功能描述  : 从avoid列表中删除频点信息
 输入参数  : ucIndex -- 被删除的频点信息索引

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月14日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetAvoidFreqFromAvoidList
 功能描述  : 从avoid list中获取被禁频点信息
 输入参数  : ucIndex -- avoid频点信息索引

 输出参数  : 无
 返 回 值  : CNAS_XSD_AVOID_FREQ_STRU* -- avoid频点列表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月14日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_SetSystemCampOnFlag
 功能描述  : set system camp on flag
 输入参数  : ucCampOnFlg -- camp on flag
 输出参数  : none
 返 回 值  : none
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 3/12/2012
    作    者   : y00245242
    修改内容   : create

*****************************************************************************/
VOS_VOID CNAS_XSD_SetSystemCampOnFlag(
    VOS_UINT8                           ucCampOnFlg
)
{
    CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCurCampedSysInfo.ucCampOnFlag = ucCampOnFlg;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetSystemCampOnFlag
 功能描述  : get system camp on flag
 输入参数  : ucCampOnFlg -- camp on flag
 输出参数  : none
 返 回 值  : none
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 3/12/2012
    作    者   : y00245242
    修改内容   : create

*****************************************************************************/
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

/*****************************************************************************
Function Name   :   CNAS_XSD_SetEmcRedirectionFlg
Description     :   设置重定向紧急呼标记:以下情况标记置成TRUE,其余情况置成FALSE
                    1.当前收到紧急呼Start未收到紧急呼End
                    2.当前处于紧急呼回呼模式中

Input parameters:   None
Outout parameters:  None
Return Value    :   VOS_VOID

Modify History:
    1)  Date    :   2015-12-09
        Author  :   h00313353
        Modify content :    Create
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : CNAS_XSD_GetFreqLockAddr
 功能描述  : 获取stFreqLockPara地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月29日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU* CNAS_XSD_GetFreqLockAddr(VOS_VOID)
{
    return &(g_stCnasXsdCtx.stSysAcqCtrl.stFreqLockPara);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetFreqLockMode
 功能描述  : 获取当前锁频模式
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : ucFreqLockMode
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月29日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetFreqLockMode(VOS_VOID)
{
    return (g_stCnasXsdCtx.stSysAcqCtrl.stFreqLockPara.ucFreqLockMode);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_InitCFreqLockValue
 功能描述  : 初始化stFreqLockPara
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月29日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_InitCFreqLockValue(VOS_VOID)
{
    CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU  *pstCnasXsdCFreqLockValue;

    pstCnasXsdCFreqLockValue = CNAS_XSD_GetFreqLockAddr();

    NAS_MEM_SET_S(pstCnasXsdCFreqLockValue, sizeof(CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU), 0x00, sizeof(CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU));

    return;
}



/*****************************************************************************
 函 数 名  : CNAS_XSD_InitTestConfig
 功能描述  : 初始化TestConfig
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月3日
    作    者   : c00299063
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_InitTestConfig(
    CNAS_XSD_TEST_CONFIG_STRU          *pstTestConfig
)
{
    NAS_MEM_SET_S(pstTestConfig, sizeof(CNAS_XSD_TEST_CONFIG_STRU), 0x00, sizeof(CNAS_XSD_TEST_CONFIG_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_InitSysAcqNvimCfg
 功能描述  : 初始化SysAcqNvimCfg
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月3日
    作    者   : c00299063
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_InitSysAcqNvimCfg(
    CNAS_XSD_SYS_ACQ_NVIM_CFG_STRU                         *pstSysAcqNvimCfg
)
{
    NAS_MEM_SET_S(pstSysAcqNvimCfg, sizeof(CNAS_XSD_SYS_ACQ_NVIM_CFG_STRU), 0x00, sizeof(CNAS_XSD_SYS_ACQ_NVIM_CFG_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetOocScheduleInfo
 功能描述  : 获取OOC下调度信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回OOC调度信息地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月04日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_XSD_OOC_SCHEDULE_INFO_STRU *CNAS_XSD_GetOocScheduleInfo(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stOocScheduleInfo);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_InitOocScheduleInfo
 功能描述  : 初始化OOC下调度信息
 输入参数  : enInitType -- 初始化类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月04日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_InitOocScheduleInfo(
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo
)
{
    NAS_MEM_SET_S(pstOocScheduleInfo, sizeof(CNAS_XSD_OOC_SCHEDULE_INFO_STRU), 0, sizeof(CNAS_XSD_OOC_SCHEDULE_INFO_STRU));

    pstOocScheduleInfo->stConfigInfo.ucPhaseNum                      = 0;
    pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[0].usTimerLen   = 5;
    pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[0].usTimes      = 5;

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_InitOocCtxInfo
 功能描述  : 初始化OOC上下文信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月04日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_InitOocCtxInfo(VOS_VOID)
{
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo = VOS_NULL_PTR;

    pstOocScheduleInfo = CNAS_XSD_GetOocScheduleInfo();

    NAS_MEM_SET_S(&pstOocScheduleInfo->stOocCtxInfo, sizeof(pstOocScheduleInfo->stOocCtxInfo), 0, sizeof(CNAS_XSD_OOC_CTX_INFO_STRU));
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetOocWaitSearchFlag
 功能描述  : 获取OOC等待搜索标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月04日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetOocWaitSearchFlag(VOS_VOID)
{
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU                        *pstOocSchedule = VOS_NULL_PTR;

    pstOocSchedule = CNAS_XSD_GetOocScheduleInfo();

    return (pstOocSchedule->stOocCtxInfo.ucWaitSearchFlag);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SetOocWaitSearchFlag
 功能描述  : 设置OOC等待搜索标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月04日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_SetOocWaitSearchFlag(VOS_UINT8 ucWaitSearchFlag)
{
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU                        *pstOocSchedule = VOS_NULL_PTR;

    pstOocSchedule = CNAS_XSD_GetOocScheduleInfo();

    pstOocSchedule->stOocCtxInfo.ucWaitSearchFlag = ucWaitSearchFlag;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_SetNdssIndFlag
 功能描述  : 设置NDSS IND 指示
 输入参数  : ucNdssInd -- NDSS off指示flag
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月05日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_SetNdssIndFlag(
    VOS_UINT8                           ucNdssInd
)
{
    CNAS_XSD_REDIRECTION_INFO_STRU     *pstRedirInfo = VOS_NULL_PTR;

    pstRedirInfo            = CNAS_XSD_GetRedirectionInfoAddr();
    pstRedirInfo->ucNdssInd = ucNdssInd;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetNdssIndFlag
 功能描述  : 获取NDSS IND 指示
 输入参数  : ucNdssInd -- NDSS off指示flag
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月05日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetNdssIndFlag(VOS_VOID)
{
    CNAS_XSD_REDIRECTION_INFO_STRU     *pstRedirInfo = VOS_NULL_PTR;

    pstRedirInfo            = CNAS_XSD_GetRedirectionInfoAddr();

    return (pstRedirInfo->ucNdssInd);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetOocScheduleConfigInfo
 功能描述  : 获取OOC下调度信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回OOC调度配置信息地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月08日
   作    者   : h00313353
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_XSD_OOC_CONFIG_INFO_STRU *CNAS_XSD_GetOocScheduleConfigInfo(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stOocScheduleInfo.stConfigInfo);
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_GetSrvAcqFlg
 功能描述  : 获取当前是否处于业务触发搜网的标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8 : ucSrvAcqFlg
             VOS_TRUE  : 处于业务触发搜网流程
             VOS_FALSE : 不处于业务触发搜网流程
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年05月21日
   作    者   : h00313353
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetSrvAcqFlg(VOS_VOID)
{
    return CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.ucSrvAcqFlg;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SetSrvAcqFlg
 功能描述  : 设置当前是否处于业务触发的搜网标识
 输入参数  : VOS_UINT8 : ucSrvAcqFlg
             VOS_TRUE  : 处于业务触发搜网流程
             VOS_FALSE : 不处于业务触发搜网流程
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年05月21日
   作    者   : h00313353
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_SetSrvAcqFlg(
    VOS_UINT8                           ucSrvAcqFlg
)
{
    CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.ucSrvAcqFlg  = ucSrvAcqFlg;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetEmcState
 功能描述  : 获取当前紧急呼流程的状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CNAS_XSD_EMC_STATE_ENUM_UINT8 : enEmcState
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年07月02日
   作    者   : h00313353
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_XSD_EMC_STATE_ENUM_UINT8 CNAS_XSD_GetEmcState(VOS_VOID)
{
    return CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.enEmcState;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetEmcCallBackSrchCounter
 功能描述  : 获取当前紧急呼流程的计数器值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年07月02日
   作    者   : h00313353
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetEmcCallBackSrchCounter(VOS_VOID)
{
    return CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.ucCallBackSrchCounter;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetEmcCallBackSrchCounter
 功能描述  : 设置当前紧急呼流程的状态
 输入参数  : CNAS_XSD_EMC_STATE_ENUM_UINT8 : enEmcState
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年07月02日
   作    者   : h00313353
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_SetEmcCallBackSrchCounter(
    VOS_UINT8                           ucEmcCallBackCounter
)
{
    CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.ucCallBackSrchCounter = ucEmcCallBackCounter;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetEmcCallBackCandidateFreqInfo
 功能描述  : 获取当前紧急呼回呼异频临区信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CNAS_XSD_EMC_CALLBACK_CANDIDATE_FREQ_INFO_STRU *
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2016年01月28日
   作    者   : h00313353
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_XSD_EMC_CALLBACK_CANDIDATE_FREQ_INFO_STRU* CNAS_XSD_GetEmcCallBackCandidateFreqInfo(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.stEmcCallBackCfInfo);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ClearEmcCallBackCandidateFreq
 功能描述  : 清除当前紧急呼回呼模式异频临区频点
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2016年01月28日
   作    者   : h00313353
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_ClearEmcCallBackCandidateFreq(
    VOS_VOID
)
{
    PS_MEM_SET(CNAS_XSD_GetEmcCallBackCandidateFreqInfo(), 0x00, sizeof(CNAS_XSD_EMC_CALLBACK_CANDIDATE_FREQ_INFO_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SetEmcCallBackCandidateFreq
 功能描述  : 设置当前紧急呼回呼模式异频临区频点
 输入参数  : usCfFreqNum:频点数
             pstCfInfo:  频点信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2016年01月28日
   作    者   : h00313353
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_SetEmcState
 功能描述  : 设置当前紧急呼流程的状态
 输入参数  : CNAS_XSD_EMC_STATE_ENUM_UINT8 : enEmcState
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年07月02日
   作    者   : h00313353
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_SetEmcState(
    CNAS_XSD_EMC_STATE_ENUM_UINT8       enEmcState
)
{
    CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.enEmcState = enEmcState;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetCallBackCfg
 功能描述  : 获取Nv中对于紧急呼CallBack模式的相关设置
 输入参数  : CNAS_XSD_EMC_STATE_ENUM_UINT8 : enEmcState
 输出参数  : 无
 返 回 值  : CNAS_XSD_CALLBACK_CFG_STRU
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年07月02日
   作    者   : h00313353
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_XSD_CALLBACK_CFG_STRU *CNAS_XSD_GetCallBackCfg( VOS_VOID )
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.stCallBackCfg);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_InitGeoSrchListInfo
 功能描述  : 初始化GEO list搜索信息
 输入参数  : pstGeoListSrchInfo -- 指向GEO list搜索信息地址

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年07月03日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_InitGeoSrchListInfo(
    CNAS_XSD_GEO_LIST_SRCH_INFO_STRU   *pstGeoListSrchInfo
)
{
    NAS_MEM_SET_S(pstGeoListSrchInfo, sizeof(CNAS_XSD_GEO_LIST_SRCH_INFO_STRU), 0, sizeof(CNAS_XSD_GEO_LIST_SRCH_INFO_STRU));
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetGeoSrchListInfoAddr
 功能描述  : 获取当前GEO搜索list信息地址
 输入参数  : pstGeoListSrchInfo -- 指向GEO list搜索信息地址

 输出参数  : CNAS_XSD_GEO_LIST_SRCH_INFO_STRU* -- 返回GEO搜索列表信息地址
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年07月03日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_XSD_GEO_LIST_SRCH_INFO_STRU *CNAS_XSD_GetGeoSrchListInfoAddr(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stGeoListSrchInfo);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ClearGeoSrchListStatus
 功能描述  : 清除GEO搜索列表状态
 输入参数  : 无

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年07月07日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_FreeBufferOfGeoSrchList
 功能描述  : 释放GEO搜索列表空间
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月7日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_InitHistorySyncedSysFreqList
 功能描述  : 初始化历史同步到的系统频点列表
 输入参数  : pstHisSyncedSysFreqList -- 历史同步到的系统频点列表
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月7日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetHistorySyncedSysFreqList
 功能描述  : 获取同步到的系统记录列表地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_XSD_HISTORY_SYNCED_SYS_FREQ_LIST_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月7日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_XSD_HISTORY_SYNCED_SYS_FREQ_LIST_STRU* CNAS_XSD_GetHistorySyncedSysFreqList(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stHisSyncedSysFreqList);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateHistorySyncedSysFreqList
 功能描述  : 更新开机之后同步到系统的频点列表
 输入参数  : pstFreq -- 同步到的频点信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月7日
    作    者   : y00245242
    修改内容   : 新生成函数

  1.日    期   : 2015年9月10日
    作    者   : y00245242
    修改内容   : DTS2015090206027
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetLastSyncedSys
 功能描述  : 获取上次同步到的系统
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_PRL_1X_SYSTEM_ID_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月7日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_PRL_1X_SYSTEM_ID_STRU* CNAS_XSD_GetLastSyncedSys(VOS_VOID)
{
    CNAS_XSD_CTX_STRU                  *pstXsdCtx = VOS_NULL_PTR;

    pstXsdCtx = CNAS_XSD_GetXsdCtxAddr();

    return &(pstXsdCtx->stCurFsm.unFsmCtx.stSysAcqCtx.stLastSyncedSys);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetLastSyncedFreq
 功能描述  : 获取上次同步成功的频点
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_PRL_FREQENCY_CHANNEL_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月8日
    作    者   : c00299063
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_PRL_FREQENCY_CHANNEL_STRU* CNAS_XSD_GetLastSyncedFreq(VOS_VOID)
{
    return &(CNAS_XSD_GetHistorySyncedSysFreqList()->astFreq[0]);
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateLastSyncedSys
 功能描述  : 更新上次同步到的系统
 输入参数  : pstLastSyncedSys -- 当前同步到的系统
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月7日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateLastSyncedSys(
    CNAS_PRL_1X_SYSTEM_ID_STRU         *pstCurSyncedSys
)
{
    CNAS_PRL_1X_SYSTEM_ID_STRU         *pstLastSyncedSys = VOS_NULL_PTR;

    pstLastSyncedSys = CNAS_XSD_GetLastSyncedSys();

    pstLastSyncedSys->usNid = pstCurSyncedSys->usNid;
    pstLastSyncedSys->usSid = pstCurSyncedSys->usSid;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetCallRelAnyCampOnFreqListAddr
 功能描述  : 获取call release场景下，任何系统直接驻留频点
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_XSD_CALL_REL_ANY_CAMP_ON_FREQ_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月9日
    作    者   : y00245242
    修改内容   : iteration 17开发

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetCdma1XCustomPrefChannels
 功能描述  : 获取电信常用1X频点
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_XSD_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月14日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_XSD_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU* CNAS_XSD_GetCdma1XCustomPrefChannels(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCdma1XCustomPrefChan);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetNoCardModeCfgFlg
 功能描述  : 从avoid频点列表中删除可用的频点
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetNoCardModeCfgFlg()
{
    return (CNAS_XSD_GetTestConfig()->ucNoCardModeCfgFlg);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SetNoCardModeCfgFlg
 功能描述  : 设置无卡模式标记
 输入参数  : VOS_UINT8                           ucNoCardModeCfgFlg
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_SetNoCardModeCfgFlg(
    VOS_UINT8                           ucNoCardModeCfgFlg
)
{
    CNAS_XSD_GetTestConfig()->ucNoCardModeCfgFlg = ucNoCardModeCfgFlg;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetEmcRedialSysAcqCfgInfo
 功能描述  : 获取紧急呼重拨搜网控制信息
 输入参数  : 无
 输出参数  : CNAS_XSD_EMC_REDIAL_SYS_ACQ_CFG_STRU*
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
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



