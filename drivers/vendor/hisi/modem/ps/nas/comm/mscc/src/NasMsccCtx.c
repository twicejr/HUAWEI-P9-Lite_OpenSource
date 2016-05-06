/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMsccCtx.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2015年01月26日
  功能描述   : NAS MSCC全局变量管理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年01月26日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasMsccCtx.h"
#include "PsCommonDef.h"
#include "NasMsccFsmSwitchOnTbl.h"
#include "NasMsccFsmPowerOffTbl.h"
#include "NasMsccFsmSysAcqTbl.h"
#include "NasMsccFsmMainTbl.h"
#include "NasNvInterface.h"
#include "NasMsccTimerMgmt.h"
#include "NasMsccMntn.h"
#include "NasMsccProcNvim.h"
#include "xsd_mscc_pif.h"
#include "hsd_mscc_pif.h"

#include "NasMsccFsmBsrTbl.h"

#include "NasMmlCtx.h"

#include "NasMsccComFunc.h"
#include "NasMsccSysAcqStrategy.h"
#include "NasMsccMlplMsplApi.h"
#include "NasMsccFsmSysCfgTbl.h"
#include "NasMsccFsmSysCfg.h"
#include "NasComm.h"

#include "NasMsccFsmCLInterSysTbl.h"
#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_CTX_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
NAS_MSCC_CTX_STRU                       g_stNasMsccCtx;




/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : NAS_MSCC_GetMsccCtxAddr
 功能描述  : 获取当前MSCC的CTX
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回当前MSCC的CTX地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月26日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MSCC_CTX_STRU* NAS_MSCC_GetMsccCtxAddr(VOS_VOID)
{
    return &(g_stNasMsccCtx);
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_InitCtx
 功能描述  : MSCC上下文全局变量初始化
 输入参数  : enInitType - 指示是开机初始化还是关机初始化
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月26日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2015年04月13日
   作    者   : y00174758
   修改内容   : CDMA Iteration 10 Modified
 3. Date      : 2015-04-14
    Author    : a00295761
    Content   : Added Init MS Cfg Info Function
 4. Date      : 2015-04-27
    Author    : y00174758
    Content   : 添加开机、关机初始化指示

*****************************************************************************/
VOS_VOID NAS_MSCC_InitCtx(
    NAS_MSCC_INIT_CTX_TYPE_ENUM_UINT8 enInitType
)
{
    NAS_MSCC_CTX_STRU                  *pstMsccCtx = VOS_NULL_PTR;

    pstMsccCtx = NAS_MSCC_GetMsccCtxAddr();

    /* Init the Current FSM context */
    NAS_MSCC_InitCurrFsmCtx(&(pstMsccCtx->stCurFsm));

    /* Init the FSM Stack */
    NAS_MSCC_InitFsmStackCtx(&(pstMsccCtx->stFsmStack));

    /* Init the Cache message queue */
    NAS_MSCC_InitCacheMsgQueue(&(pstMsccCtx->stCacheMsgQueue));

    /* Init the internal message queue */
    NAS_MSCC_InitInternalBuffer(&(pstMsccCtx->stIntMsgQueue));

    /* Init the Timer Context */
    NAS_MSCC_InitTimerCtx(&(pstMsccCtx->astMsccTimerCtx[0]));

    /* INit the Network info Structure. */
    NAS_MSCC_InitNetworkInfo(&(pstMsccCtx->stNwInfo));

    NAS_MSCC_InitMlplMsplInfo(enInitType, &(pstMsccCtx->stMlplMsplInfo));

    NAS_MSCC_InitSimInfo(&(pstMsccCtx->stSimInfo));

    NAS_MSCC_InitMsCfgInfo(&(pstMsccCtx->stMsCfgInfo));

    NAS_MSCC_InitPowerSaveCtrlInfo(&(pstMsccCtx->stPowerSaveCtrl));

    NAS_MSCC_InitSysAcqCtrlInfo(&(pstMsccCtx->stSysAcqCtrl));

    NAS_MSCC_InitMntnInfo(&(pstMsccCtx->stMntnInfo));



    NAS_MSCC_InitNoCardInitSearchLocInfo(&(pstMsccCtx->stSysAcqCtrl.stNoCardInitSearchLoc));
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_InitNetworkInfo
 功能描述  : 初始化网络相关信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月26日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2015年04月11日
   作    者   : w00176964
   修改内容   : CDMA Iteration 10 Modified
 3. Date      : 2015-04-14
    Author    : a00295761
    Content   : Added Init Steps
 4. Date      : 2015-09-22
    Author    : y00346957
    Content   : DTS2015070910885 修改，删掉了mscc sys pri class这个结构体

*****************************************************************************/
VOS_VOID NAS_MSCC_InitNetworkInfo(
    NAS_MSCC_NW_INFO_STRU               *pstNwInfo
)
{
    PS_MEM_SET(pstNwInfo, 0, sizeof(NAS_MSCC_NW_INFO_STRU));

    pstNwInfo->stGuNwCapInfo.enLteCsCap    = NAS_MSCC_LTE_CS_CAPBILITY_BUTT;
    pstNwInfo->stGuNwCapInfo.enNwEmcBsCap  = NAS_MSCC_NW_EMC_BS_BUTT;
    pstNwInfo->stGuNwCapInfo.enNwImsVoCap  = NAS_MSCC_NW_IMS_VOICE_BUTT;

    pstNwInfo->stLteNwCapInfo.enLteCsCap   = NAS_MSCC_LTE_CS_CAPBILITY_BUTT;
    pstNwInfo->stLteNwCapInfo.enNwEmcBsCap = NAS_MSCC_NW_EMC_BS_BUTT;
    pstNwInfo->stLteNwCapInfo.enNwImsVoCap = NAS_MSCC_NW_IMS_VOICE_BUTT;

    pstNwInfo->stImsDomainInfo.enPersistentBearerState = NAS_MSCC_PERSISTENT_BEARER_STATE_NOT_EXIST;
    pstNwInfo->stImsDomainInfo.enImsVoiceCap           = MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE;

    pstNwInfo->stSysInfo.st3gppSysInfo.enLmmAccessType   = NAS_MSCC_LMM_ACCESS_TYPE_BUTT;
    pstNwInfo->stSysInfo.st3gppSysInfo.enSysMode         = NAS_MSCC_SYS_MODE_BUTT;
    pstNwInfo->stSysInfo.st3gppSysInfo.stPlmnId.ulMcc    = NAS_MSCC_INVALID_MCC;
    pstNwInfo->stSysInfo.st3gppSysInfo.stPlmnId.ulMnc    = NAS_MSCC_INVALID_MNC;
    pstNwInfo->stSysInfo.st3gppSysInfo.ucRac             = NAS_MSCC_INVALID_RAC;
    pstNwInfo->stSysInfo.st3gppSysInfo.ucRoamFlag        = VOS_FALSE;
    pstNwInfo->stSysInfo.st3gppSysInfo.ulCellId          = NAS_MSCC_INVALID_CELL_ID;
    pstNwInfo->stSysInfo.st3gppSysInfo.usLac             = NAS_MSCC_INVALID_LAC;
    pstNwInfo->stSysInfo.st3gppSysInfo.enPrioClass       = NAS_MSCC_PIF_PRI_CLASS_ANY;

    /* Init the 1x Sys Info */
    pstNwInfo->stSysInfo.st3gpp2SysInfo.st1xSysInfo.en1xPrioClass = NAS_MSCC_PIF_PRI_CLASS_ANY;
    pstNwInfo->stSysInfo.st3gpp2SysInfo.st1xSysInfo.enAIPrioClass = NAS_MSCC_PIF_PRI_CLASS_ANY;
    pstNwInfo->stSysInfo.st3gpp2SysInfo.st1xSysInfo.ucCampOnFlg   = VOS_FALSE;
    pstNwInfo->stSysInfo.st3gpp2SysInfo.st1xSysInfo.ulMcc         = NAS_MSCC_INVALID_MCC;
    pstNwInfo->stSysInfo.st3gpp2SysInfo.st1xSysInfo.ulMnc         = NAS_MSCC_INVALID_MNC;
    pstNwInfo->stSysInfo.st3gpp2SysInfo.st1xSysInfo.usSid         = NAS_MSCC_WILDCARD_SID;
    pstNwInfo->stSysInfo.st3gpp2SysInfo.st1xSysInfo.usNid         = NAS_MSCC_WILDCARD_NID;

    /* Init the HRPD Sys Info */
    pstNwInfo->stSysInfo.st3gpp2SysInfo.stHrpdSysInfo.enAIPrioClass   = NAS_MSCC_PIF_PRI_CLASS_ANY;
    pstNwInfo->stSysInfo.st3gpp2SysInfo.stHrpdSysInfo.enHrpdPrioClass = NAS_MSCC_PIF_PRI_CLASS_ANY;
    pstNwInfo->stSysInfo.st3gpp2SysInfo.stHrpdSysInfo.ucCampOnFlg     = VOS_FALSE;
    pstNwInfo->stSysInfo.st3gpp2SysInfo.stHrpdSysInfo.ulMcc           = NAS_MSCC_INVALID_MCC;
    pstNwInfo->stSysInfo.st3gpp2SysInfo.stHrpdSysInfo.ucSubNetMask    = 0;
    PS_MEM_SET(pstNwInfo->stSysInfo.st3gpp2SysInfo.stHrpdSysInfo.aucSectorId, 0x00, NAS_MSCC_BYTES_IN_SUBNET);

    /* Init the Service status info */
    pstNwInfo->stServiceStatusInfo.en1xServiceStatus     = NAS_MSCC_SERVICE_STATUS_NO_SERVICE;
    pstNwInfo->stServiceStatusInfo.en3gppPsServiceStatus = NAS_MSCC_SERVICE_STATUS_NO_SERVICE;
    pstNwInfo->stServiceStatusInfo.enHrpdServiceStatus   = NAS_MSCC_SERVICE_STATUS_NO_SERVICE;

    /* Init the Connection status info */
    pstNwInfo->stConnStatusInfo.ucHrpdConnExistFlg   = VOS_FALSE;
    pstNwInfo->stConnStatusInfo.ucLteEpsConnExistFlg = VOS_FALSE;

    pstNwInfo->stSendToImsaInfo.ucRoamFlg            = VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SetGuNwCapInfo
 功能描述  : 设置GU网络能力信息
 输入参数  : pstGuNwCap -- LTE网络能力信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月26日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SetGuNwCapInfo(NAS_MSCC_NETWORK_CAP_INFO_STRU *pstGuNwCap)
{
    NAS_MSCC_NETWORK_CAP_INFO_STRU     *pstGuNwCapInfo = VOS_NULL;

    pstGuNwCapInfo = &(NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stGuNwCapInfo);

    pstGuNwCapInfo->enLteCsCap   = pstGuNwCap->enLteCsCap;
    pstGuNwCapInfo->enNwEmcBsCap = pstGuNwCap->enNwEmcBsCap;
    pstGuNwCapInfo->enNwImsVoCap = pstGuNwCap->enNwImsVoCap;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_GetGuNwCapInfo
 功能描述  : MSCC上下文全局变量初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MSCC_NETWORK_CAP_INFO_STRU -- GU网络能力信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月26日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MSCC_NETWORK_CAP_INFO_STRU *NAS_MSCC_GetGuNwCapInfo(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stGuNwCapInfo);
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_SetLteNwCapInfo
 功能描述  : 设置LTE 网络能力信息
 输入参数  : pstLteNwCap -- LTE网络能力信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月26日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SetLteNwCapInfo(NAS_MSCC_NETWORK_CAP_INFO_STRU *pstLteNwCap)
{
    NAS_MSCC_NETWORK_CAP_INFO_STRU     *pstLteNwCapInfo = VOS_NULL;

    pstLteNwCapInfo = &(NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stLteNwCapInfo);

    pstLteNwCapInfo->enLteCsCap   = pstLteNwCap->enLteCsCap;
    pstLteNwCapInfo->enNwEmcBsCap = pstLteNwCap->enNwEmcBsCap;
    pstLteNwCapInfo->enNwImsVoCap = pstLteNwCap->enNwImsVoCap;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SetPersistentBearerState
 功能描述  : 设置当前是否存在persistent eps bearer标识
 输入参数  : enPersistentBearerState - 是否存在persistent eps bearer标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年5月12日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
VOS_VOID    NAS_MSCC_SetPersistentBearerState(
    NAS_MSCC_PERSISTENT_BEARER_STATE_ENUM_UINT8             enPersistentBearerState
)
{
    NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stImsDomainInfo.enPersistentBearerState = enPersistentBearerState;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_GetPersistentBearerState
 功能描述  : 获取当前是否存在persistent eps bearer标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 是否存在persistent eps bearer标识
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年5月12日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
NAS_MSCC_PERSISTENT_BEARER_STATE_ENUM_UINT8  NAS_MSCC_GetPersistentBearerState(VOS_VOID)
{
    return NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stImsDomainInfo.enPersistentBearerState;
}



/*****************************************************************************
 函 数 名  : NAS_MSCC_SetImsVoiceCapability
 功能描述  : 设置当前语音能力
 输入参数  : enImsVoiceCap - IMS语音能力
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年8月14日
   作    者   : n00269697
   修改内容   : DTS2015072803051

*****************************************************************************/
VOS_VOID    NAS_MSCC_SetImsVoiceCapability(
    MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8                      enImsVoiceCap
)
{
    NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stImsDomainInfo.enImsVoiceCap = enImsVoiceCap;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_GetImsVoiceCapability
 功能描述  : 获取当前语音能力
 输入参数  : enImsVoiceCap - IMS语音能力
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年8月14日
   作    者   : n00269697
   修改内容   : DTS2015072803051

*****************************************************************************/
MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8  NAS_MSCC_GetImsVoiceCapability(VOS_VOID)
{
    return NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stImsDomainInfo.enImsVoiceCap;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_GetLteNwCapInfo
 功能描述  : MSCC上下文全局变量初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MSCC_NETWORK_CAP_INFO_STRU -- LTE网络能力信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月26日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MSCC_NETWORK_CAP_INFO_STRU *NAS_MSCC_GetLteNwCapInfo(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stLteNwCapInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_GetCurrSysInfo
 功能描述  : 获取当前网络的系统信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MSCC_SYS_INFO_STRU -- 当前网络系统信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月26日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MSCC_SYS_INFO_STRU *NAS_MSCC_GetCurrSysInfo(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_GetTimerCtxAddr
 功能描述  : 获取MSCC CTX模块中定时器的上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MSCC CTX模块中定时器的上下文指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月27日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MSCC_TIMER_CTX_STRU *NAS_MSCC_GetTimerCtxAddr( VOS_VOID )
{
    return &(NAS_MSCC_GetMsccCtxAddr()->astMsccTimerCtx[0]);
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_GetImsCfgInfo
 功能描述  : 获取MSCC模块中IMS配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : IMS配置信息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月27日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MSCC_IMS_CONFIG_PARA_STRU *NAS_MSCC_GetImsCfgInfo( VOS_VOID )
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo.stCustomCfgInfo.stImsCfgInfo);
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_GetWaitImsVoiceAvailTimerLen
 功能描述  : 获取等待IMS VOICE可用的定时器时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 等待IMS VOICE可用的定时器时长
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年01月27日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_GetWaitImsVoiceAvailTimerLen(VOS_VOID)
{
    return NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo.stCustomCfgInfo.stImsCfgInfo.ulWaitImsVoiceAvailTimerLen;
}



VOS_VOID  NAS_MSCC_LoadSubFsm(
    NAS_MSCC_FSM_ID_ENUM_UINT32         enFsmId,
    NAS_MSCC_FSM_CTX_STRU              *pstCurFsm
)
{
    switch (enFsmId)
    {
        case NAS_MSCC_FSM_SWITCH_ON :
            pstCurFsm->ulState                  = NAS_MSCC_SWITCHON_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MSCC_GetSwitchOnFsmDescAddr();
            break;

        case NAS_MSCC_FSM_POWER_OFF :
            pstCurFsm->ulState                  = NAS_MSCC_POWER_OFF_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MSCC_GetPowerOffFsmDescAddr();
            break;

        case NAS_MSCC_FSM_SYSTEM_CONFIG :
            pstCurFsm->ulState                  = NAS_MSCC_SYSCFG_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MSCC_GetSysCfgFsmDescAddr();
            break;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case NAS_MSCC_FSM_SYS_ACQ :
            pstCurFsm->ulState                  = NAS_MSCC_SYSACQ_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MSCC_GetSysAcqFsmDescAddr();
            break;

        case NAS_MSCC_FSM_CL_INTERSYS:
            pstCurFsm->ulState                  = NAS_MSCC_CL_INTERSYS_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MSCC_GetCLInterSysFsmDescAddr();
            break;

        case NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION :
            pstCurFsm->ulState                  = NAS_MSCC_BSR_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MSCC_GetBsrFsmDescAddr();
            break;
#endif

        default:
            NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_LoadSubFsm:Invalid Fsm Id");
            return;
    }

    /*执行初始化L2状态机的函数*/
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }
}




VOS_VOID NAS_MSCC_InitFsmL2(
    NAS_MSCC_FSM_ID_ENUM_UINT32         enFsmId
)
{
    NAS_MSCC_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;
    NAS_MSCC_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;
    NAS_MSCC_FSM_ID_ENUM_UINT32         enParentFsmId;
    VOS_UINT32                          ulParentEventType;
    NAS_MSCC_FSM_ID_ENUM_UINT32         enCurrFsmId;

    enCurrFsmId = NAS_MSCC_GetCurrFsmId();
    if (NAS_MSCC_BUTT == enCurrFsmId)
    {
        /* Sending the Warning Log for this case */
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_InitFsmL2: NAS_MSCC_GetCurrFsmId return Butt");
    }

    /* The FSM Info is logged in OM */
    NAS_MSCC_MNTN_LogFsmInfo(enCurrFsmId, NAS_MSCC_GetFsmTopState());

    /* Getting the parent FSM ID and the Parent Event Type */
    enParentFsmId     = NAS_MSCC_GetCurrFsmId();
    ulParentEventType = NAS_MSCC_GetCurFsmAddr()->stEntryMsg.ulEventType;

    /* Getting the FSM stack address, Current FSM Context structure. The Current FSM context is pushed to the stack */
    pstFsmStack = NAS_MSCC_GetFsmStackAddr();
    pstCurFsm   = NAS_MSCC_GetCurFsmAddr();
    NAS_MSCC_PushFsm(pstFsmStack, pstCurFsm);

    /* The current FSM context must now contain the ID of the new FSM to be loaded. */
    pstCurFsm->enFsmId = enFsmId;

    /* The current FSM context must contain the init state of the NEW FSM. The initializing function is also called. */
    NAS_MSCC_LoadSubFsm(enFsmId, pstCurFsm);

    /* 记录上层状态机名和入口消息类型 */
    pstCurFsm->enParentFsmId     = enParentFsmId;
    pstCurFsm->ulParentEventType = ulParentEventType;

    enCurrFsmId = NAS_MSCC_GetCurrFsmId();
    if (NAS_MSCC_BUTT == enCurrFsmId)
    {
        /* Log the warning for the error case*/
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_InitFsmL2: NAS_MSCC_GetCurrFsmId return Butt");
    }

    /* The FSM Info is logged in OM */
    NAS_MSCC_MNTN_LogFsmInfo(enCurrFsmId, NAS_MSCC_GetFsmTopState());
}




VOS_VOID NAS_MSCC_PopFsm( VOS_VOID )
{
    NAS_MSCC_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;
    NAS_MSCC_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;

    /* Get the FSM Stack Address and the current FSM address */
    pstFsmStack = NAS_MSCC_GetFsmStackAddr();
    pstCurFsm   = NAS_MSCC_GetCurFsmAddr();

    /* If the Stack Depth is empty then return with Error Log */
    if (0 == pstFsmStack->usStackDepth)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_PopFsm: FSM Stack is empty");
        return;
    }

    /* Decrease the Stack depth */
    pstFsmStack->usStackDepth--;

    /* Copy the top Context in FSM stack to the Current FSM Context global structure */
    PS_MEM_CPY(pstCurFsm,
              &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]),
              sizeof(NAS_MSCC_FSM_CTX_STRU));
}




VOS_VOID NAS_MSCC_PushFsm(
    NAS_MSCC_FSM_STACK_STRU             *pstFsmStack,
    NAS_MSCC_FSM_CTX_STRU               *pstNewFsm
)
{
    NAS_MSCC_FSM_CTX_STRU              *pstCurFsm = VOS_NULL_PTR;

    /* Check if the New FSM stack or the New FSM to be pushed */
    if ((VOS_NULL_PTR == pstFsmStack)
     || (VOS_NULL_PTR == pstNewFsm))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC,
                       "NAS_MSCC_PushFsm: pstFsmStack or pstNewFsm is null pointer!");

        return;
    }

    /* Check if the Stack Depth is greater than the max FSM stack depth */
    if (pstFsmStack->usStackDepth >= NAS_MSCC_MAX_FSM_STACK_DEPTH)
    {
        NAS_ERROR_LOG1(UEPS_PID_MSCC,
                       "NAS_MSCC_PushFsm: Fsm Stack Depth = %d Error!",
                       pstFsmStack->usStackDepth);

        return;
    }

    /* Get the address of the top member of the FSM stack and store it in pstCurFsm */
    pstCurFsm = &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]);

    /* Copy the New FSM to the address pointed by pstCurFsm */
    PS_MEM_CPY(pstCurFsm, pstNewFsm, sizeof(NAS_MSCC_FSM_CTX_STRU));

    /* Increase the stack depth */
    pstFsmStack->usStackDepth++;

    return;
}




VOS_VOID NAS_MSCC_QuitFsmL2(VOS_VOID)
{

    NAS_MSCC_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;
    NAS_MSCC_FSM_ID_ENUM_UINT32         enCurrFsmId;

    pstCurFsm = NAS_MSCC_GetCurFsmAddr();

    /* The context specific to the current FSM is re-initialized */
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }

    enCurrFsmId = NAS_MSCC_GetCurrFsmId();
    if (NAS_MSCC_BUTT == enCurrFsmId)
    {
        /* Log Warning if the current FSM ID is abnormal */
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_QuitFsmL2: NAS_MSCC_GetCurrFsmId return Butt");
    }

    /*  Log the Current FSM info to OM */
    NAS_MSCC_MNTN_LogFsmInfo(enCurrFsmId, NAS_MSCC_GetFsmTopState());

    /* Pop the FSM Stack Structure */
    NAS_MSCC_PopFsm();

    enCurrFsmId = NAS_MSCC_GetCurrFsmId();
    if (NAS_MSCC_BUTT == enCurrFsmId)
    {
        /* Log Warning if the current FSM ID is abnormal */
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_QuitFsmL2: NAS_MSCC_GetCurrFsmId return Butt");
    }

    /*  Log the Current FSM info to OM */
    NAS_MSCC_MNTN_LogFsmInfo(enCurrFsmId, NAS_MSCC_GetFsmTopState());

    return;
}




VOS_VOID  NAS_MSCC_SetCurrFsmState(
    VOS_UINT32                          ulCurrState
)
{
    NAS_MSCC_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;

    /* Get the current FSM address*/
    pstCurFsm                   = NAS_MSCC_GetCurFsmAddr();

    /* Set the current FSM State to the New state */
    pstCurFsm->ulState          = ulCurrState;

    /*  Log the FSM to OM. */
    NAS_MSCC_MNTN_LogFsmInfo(pstCurFsm->enFsmId, ulCurrState);

    return;

}




VOS_UINT32 NAS_MSCC_GetFsmTopState(VOS_VOID)
{
    return (NAS_MSCC_GetCurFsmAddr()->ulState);
}




NAS_MSCC_CACHE_MSG_QUEUE_STRU* NAS_MSCC_GetCacheMsgAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stCacheMsgQueue);
}




VOS_UINT32 NAS_MSCC_GetCacheMsgNum(VOS_VOID)
{
    NAS_MSCC_CACHE_MSG_QUEUE_STRU      *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue = NAS_MSCC_GetCacheMsgAddr();

    return pstMsgQueue->ucCacheMsgNum;
}




VOS_UINT32  NAS_MSCC_SaveCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    MSG_HEADER_STRU                     *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    /* Check if the message size does not exceed the maximum */
    if ((NAS_MSCC_MAX_MSG_BUFFER_LEN - VOS_MSG_HEAD_LENGTH) <= pstMsgHeader->ulLength)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SaveCacheMsg:Len too Long");
        return VOS_FALSE;
    }

    /* If the message does not exceed max size, save in cache message queue.  */
    NAS_MSCC_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    return VOS_TRUE;

}




VOS_UINT32 NAS_MSCC_GetNextCachedMsg(
    NAS_MSCC_MSG_STRU                  *pstEntryMsg
)
{
    NAS_MSCC_CACHE_MSG_QUEUE_STRU      *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue = NAS_MSCC_GetCacheMsgAddr();

    /* Check if the Cache is empty */
    if ( 0 == pstMsgQueue->ucCacheMsgNum )
    {
        NAS_INFO_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetNextCachedMsg:Empty buffer");

        return VOS_FALSE;
    }

    /* Copy the first cache message to the pstEntryMsg  */
    PS_MEM_CPY(pstEntryMsg,
               &(pstMsgQueue->astCacheMsg[0]),
               sizeof(NAS_MSCC_MSG_STRU));

    return VOS_TRUE;

}




NAS_MSCC_FSM_CTX_STRU* NAS_MSCC_GetCurFsmAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stCurFsm);
}




NAS_FSM_DESC_STRU* NAS_MSCC_GetCurFsmDesc(VOS_VOID)
{
    return (NAS_MSCC_GetCurFsmAddr()->pstFsmDesc);
}



NAS_MSCC_FSM_SYS_ACQ_CTX_STRU* NAS_MSCC_GetSysAcqFsmCtxAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stCurFsm.unFsmCtx.stSysAcqCtx);
}




NAS_MSCC_FSM_ID_ENUM_UINT32 NAS_MSCC_GetCurrFsmId(VOS_VOID)
{
    return (g_stNasMsccCtx.stCurFsm.enFsmId);
}




NAS_MSCC_MSG_STRU* NAS_MSCC_GetCurrFsmEntryMsgAddr(VOS_VOID)
{
    return &(g_stNasMsccCtx.stCurFsm.stEntryMsg);
}




VOS_UINT8* NAS_MSCC_GetCurrFsmEntryMsgBufferAddr(VOS_VOID)
{
    return (g_stNasMsccCtx.stCurFsm.stEntryMsg.aucMsgBuffer);
}




NAS_MSCC_FSM_STACK_STRU* NAS_MSCC_GetFsmStackAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stFsmStack);
}




VOS_UINT16 NAS_MSCC_GetFsmStackDepth(VOS_VOID)
{
    NAS_MSCC_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = NAS_MSCC_GetFsmStackAddr();

    return pstFsmStack->usStackDepth;
}




NAS_MSCC_INT_MSG_QUEUE_STRU* NAS_MSCC_GetIntMsgQueueAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stIntMsgQueue);
}




VOS_VOID NAS_MSCC_InitInternalBuffer(
    NAS_MSCC_INT_MSG_QUEUE_STRU        *pstIntMsgQueue
)
{
    VOS_UINT8                           i;

    for (i = 0; i < NAS_MSCC_MAX_INT_MSG_QUEUE_NUM; i++)
    {
        pstIntMsgQueue->pastIntMsg[i] = VOS_NULL_PTR;
    }

    pstIntMsgQueue->ucIntMsgNum = 0;
}




VOS_VOID NAS_MSCC_PutMsgInIntMsgQueue(
    VOS_UINT8                          *pstMsg
)
{
    VOS_UINT8                           ucIntMsgNum;

    /* Check if the number of internal messages is greater than Max */
    if (NAS_MSCC_MAX_INT_MSG_QUEUE_NUM <= NAS_MSCC_GetIntMsgNum())
    {
        PS_MEM_FREE(UEPS_PID_MSCC, pstMsg);

        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_PutMsgInIntMsgQueue: msg queue is full!" );

        return;
    }

    ucIntMsgNum = NAS_MSCC_GetIntMsgQueueAddr()->ucIntMsgNum;

    /* Insert the message in internal message queue */
    NAS_MSCC_GetIntMsgQueueAddr()->pastIntMsg[ucIntMsgNum] = pstMsg;

    /* Incrememt the number of internal messages */
    NAS_MSCC_GetIntMsgQueueAddr()->ucIntMsgNum = (ucIntMsgNum + 1);

    return;
}




VOS_UINT8 *NAS_MSCC_GetNextIntMsg(VOS_VOID)
{
    VOS_UINT8                           ucIntMsgNum;
    VOS_UINT8                          *pstIntMsg = VOS_NULL_PTR;

    ucIntMsgNum = NAS_MSCC_GetIntMsgQueueAddr()->ucIntMsgNum;

    if (0 < ucIntMsgNum)
    {
        /* Get the first member in the queue */
        pstIntMsg = NAS_MSCC_GetIntMsgQueueAddr()->pastIntMsg[0];

        /* Decrement the number of internal messages */
        ucIntMsgNum--;

        if (0 != ucIntMsgNum)
        {
            /* Shift the Queue by one place */
            PS_MEM_MOVE(&(NAS_MSCC_GetIntMsgQueueAddr()->pastIntMsg[0]),
                        &(NAS_MSCC_GetIntMsgQueueAddr()->pastIntMsg[1]),
                        ucIntMsgNum * sizeof(VOS_UINT8 *));
        }

        /* The last member must now point to NULL */
        NAS_MSCC_GetIntMsgQueueAddr()->pastIntMsg[ucIntMsgNum] = VOS_NULL_PTR;

        NAS_MSCC_GetIntMsgQueueAddr()->ucIntMsgNum = ucIntMsgNum;
    }

    return pstIntMsg;
}




VOS_UINT8 NAS_MSCC_GetIntMsgNum(VOS_VOID)
{
    VOS_UINT8                           ucIntMsgNum;

    ucIntMsgNum = NAS_MSCC_GetIntMsgQueueAddr()->ucIntMsgNum;

    return ucIntMsgNum;
}




VOS_VOID NAS_MSCC_ClearCacheMsg(
    VOS_UINT8                           ucIndex
)
{
    NAS_MSCC_CACHE_MSG_QUEUE_STRU       *pstMsgQueue = VOS_NULL_PTR;

    /* IF the index to be cleared is out of bounds, Return */
    if (NAS_MSCC_MAX_CACHE_MSG_QUEUE_NUM <= ucIndex)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ClearCacheMsg: Attempted to clear out of bound value!");
        return;
    }

    pstMsgQueue = NAS_MSCC_GetCacheMsgAddr();

    if (0 < pstMsgQueue->ucCacheMsgNum)
    {
        pstMsgQueue->ucCacheMsgNum--;

        if (ucIndex < (NAS_MSCC_MAX_CACHE_MSG_QUEUE_NUM - 1))
        {
            /* Shift the Messages from (Index + 1) to (Index). The message at (Index) is deleted */
            PS_MEM_MOVE(&(pstMsgQueue->astCacheMsg[ucIndex]),
                        &(pstMsgQueue->astCacheMsg[ucIndex + 1]),
                        (pstMsgQueue->ucCacheMsgNum - ucIndex) * sizeof(NAS_MSCC_MSG_STRU));
        }

        /* Clear the last member of the queue */
        PS_MEM_SET(&(pstMsgQueue->astCacheMsg[pstMsgQueue->ucCacheMsgNum]),
                   0,
                   sizeof(NAS_MSCC_MSG_STRU));
    }

    NAS_MSCC_MNTN_LogBufferQueueMsg(VOS_FALSE);
}

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE))
/*****************************************************************************
Function Name   :   NAS_MSCC_InitFsmCtx_CLInterSys
Description     :   CL异系统流程的状态机的初始化函数
Input parameters:   None.
Output parameters:  None.
Return Value    :   None.
Modify History:
    1)  Date    :   2015-11-05
        Author  :   w00176964
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_InitFsmCtx_CLInterSys(VOS_VOID)
{
    return;
}

#endif



VOS_VOID NAS_MSCC_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    NAS_MSCC_CACHE_MSG_QUEUE_STRU      *pstMsgQueue   = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader  = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    pstMsgQueue  = NAS_MSCC_GetCacheMsgAddr();

    /* Check if the cache message queue is full */
    if (NAS_MSCC_MAX_CACHE_MSG_QUEUE_NUM <= pstMsgQueue->ucCacheMsgNum)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SaveCacheMsgInMsgQueue:No Empty buffer");

        return;
    }

    for (i = 0; i < pstMsgQueue->ucCacheMsgNum; i++)
    {
        /* 队列中已经存在相同事件，则不需要在添加的队列中 */
        if (pstMsgQueue->astCacheMsg[i].ulEventType == ulEventType)
        {
            return;
        }
    }

    /* Save the message to the end of the cache message queue */
    pstMsgQueue->astCacheMsg[pstMsgQueue->ucCacheMsgNum].ulEventType = ulEventType;
    PS_MEM_CPY((pstMsgQueue->astCacheMsg[pstMsgQueue->ucCacheMsgNum].aucMsgBuffer),
               pstMsg,
               pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);
    pstMsgQueue->ucCacheMsgNum++;

    /* Log the Buffer Queue */
    NAS_MSCC_MNTN_LogBufferQueueMsg(VOS_FALSE);

    NAS_INFO_LOG1(UEPS_PID_MSCC, "NAS_MSCC_SaveCacheMsgInMsgQueue: Cache Num = %d", pstMsgQueue->ucCacheMsgNum);
}




VOS_VOID NAS_MSCC_InitCacheMsgQueue(
    NAS_MSCC_CACHE_MSG_QUEUE_STRU      *pstCacheMsgQueue
)
{
    pstCacheMsgQueue->ucCacheMsgNum = 0;

    PS_MEM_SET(&(pstCacheMsgQueue->astCacheMsg[0]),
               0,
               sizeof(NAS_MSCC_MSG_STRU)*NAS_MSCC_MAX_CACHE_MSG_QUEUE_NUM);
}




VOS_VOID NAS_MSCC_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSG_STRU                  *pstEntryMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* Get the Current entry message address from the FSM context */
    pstEntryMsg                 = NAS_MSCC_GetCurrFsmEntryMsgAddr();

    ulLen                       = pstMsg->ulLength + VOS_MSG_HEAD_LENGTH;

    /* Save the message received in the entry message address  */
    PS_MEM_CPY( pstEntryMsg->aucMsgBuffer, pstMsg, ulLen );

    /* Save the event type */
    pstEntryMsg->ulEventType    = ulEventType;

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_GetImsSupportFlag
 功能描述  : 获取当前是否支持IMS标志,GSM,UTRAN,LTE IMS其中有一个支持IMS就认为支持IMS
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前是否支持IMS标志
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月27日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_GetImsSupportFlag(VOS_VOID)
{
    NAS_MSCC_IMS_CONFIG_PARA_STRU      *pstImsCfgInfo = VOS_NULL_PTR;

    pstImsCfgInfo = NAS_MSCC_GetImsCfgInfo();

    /* 如果支持GSM/UTRAN/LTE IMS, 任何一接入技术支持IMS，即认为支持IMS */
    if ((VOS_TRUE == pstImsCfgInfo->stImsRatSupport.ucGsmImsSupportFlag)
     || (VOS_TRUE == pstImsCfgInfo->stImsRatSupport.ucUtranImsSupportFlag)
     || (VOS_TRUE == pstImsCfgInfo->stImsRatSupport.ucLteImsSupportFlag))
    {
        return VOS_TRUE;
    }

    /* 其他情况下认为当前不支持IMS */
    return VOS_FALSE;
}




NAS_MSCC_FSM_SWITCH_ON_CTX_STRU* NAS_MSCC_GetModuleOrderAddr_SwitchOn(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stCurFsm.unFsmCtx.stSwitchOnCtx);
}




VOS_VOID NAS_MSCC_SetModuleOrder_SwitchOn(VOS_VOID)
{
    NAS_MSCC_FSM_SWITCH_ON_CTX_STRU    *pstModuleOrder;

    pstModuleOrder                     = NAS_MSCC_GetModuleOrderAddr_SwitchOn();

    /* Clearing the Module order structure */
    PS_MEM_SET(pstModuleOrder,
               0x00,
               sizeof(NAS_MSCC_FSM_SWITCH_ON_CTX_STRU));

    /* If IMS Feature is ON, Add IMS module ID to the Module order array */
#if (FEATURE_ON == FEATURE_IMS)
    if (VOS_TRUE == NAS_MSCC_GetImsSupportFlag())
    {
        pstModuleOrder->aulModuleID[pstModuleOrder->usNum] = PS_PID_IMSA;
        pstModuleOrder->usNum ++;
    }
#endif

    /* If CDMA Feature is ON, Add XSD and HSD module ID to the Module order array */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == NAS_MSCC_IsPlatformSupportCdma1X())
    {
        /* Adding XSD module ID */
        pstModuleOrder->aulModuleID[pstModuleOrder->usNum] = UEPS_PID_XSD;
        pstModuleOrder->usNum ++;
    }

    if (VOS_TRUE == NAS_MSCC_IsPlatformSupportCdmaEVDO())
    {
        /* Adding HSD module ID */
        pstModuleOrder->aulModuleID[pstModuleOrder->usNum] = UEPS_PID_HSD;
        pstModuleOrder->usNum ++;
    }
#endif

    /* If GUL is supported add MMC module ID to the Module order array */
    if (VOS_TRUE == NAS_MSCC_IsPlatformSupport3Gpp())
    {
        pstModuleOrder->aulModuleID[pstModuleOrder->usNum] = WUEPS_PID_MMC;
        pstModuleOrder->usNum ++;
    }

    /* Reset the module order index */
    pstModuleOrder->usIndex = 0;

    return;
}




VOS_UINT32 NAS_MSCC_GetNextModuleId_SwitchOn(
    VOS_UINT32                          *pulNextModuleId
)
{
    NAS_MSCC_FSM_SWITCH_ON_CTX_STRU    *pstModuleOrder;

    pstModuleOrder                      = NAS_MSCC_GetModuleOrderAddr_SwitchOn();

    /* If the index of the Module order array is greater than the Total number of supported Modules, Return FALSE*/
    if (pstModuleOrder->usIndex >= pstModuleOrder->usNum)
    {
        return VOS_FALSE;
    }

    /* Write the next module ID from the module order array at the address pointed by pulNextModuleId */
    *pulNextModuleId = pstModuleOrder->aulModuleID[pstModuleOrder->usIndex];

    /* Increment the index of the module order array */
    pstModuleOrder->usIndex ++;

    return VOS_TRUE;
}




VOS_UINT32 NAS_MSCC_IsModuleOrderValid_SwitchOn(VOS_VOID)
{
    NAS_MSCC_FSM_SWITCH_ON_CTX_STRU    *pstModuleOrder;

    pstModuleOrder                   = NAS_MSCC_GetModuleOrderAddr_SwitchOn();

    /* Return FALSE if Number of modules is zero. */
    if (0 == pstModuleOrder->usNum)
    {
        NAS_ERROR_LOG1(UEPS_PID_MSCC,
                       "NAS_MSCC_IsModuleOrderValid: Module Number = %d Error!",
                       pstModuleOrder->usNum);
        return VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_IMS)
    /* If IMS feature is enabled, atleast one other module must also be supported. */
    if ((1 == pstModuleOrder->usNum)
     && (PS_PID_IMSA == pstModuleOrder->aulModuleID[0]))
    {
        NAS_ERROR_LOG1(UEPS_PID_MSCC,
                       "NAS_MSCC_IsModuleOrderValid: Module Number = %d Error!",
                       pstModuleOrder->usNum);
        return VOS_FALSE;
    }
#endif

    return VOS_TRUE;
}



NAS_MSCC_FSM_POWER_OFF_CTX_STRU* NAS_MSCC_GetModuleOrderAddr_PowerOff(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stCurFsm.unFsmCtx.stPowerOffCtx);
}


/*****************************************************************************
Function Name   :   NAS_MSCC_SetModuleOrder_PowerOff
Description     :   This function is used to set the module order global structure address. The Power Off order is
                    written in the list by reading the Platform Rat Cap global strucuture in the MSCC global context
Input parameters:   None.
Output parameters:  None.
Return Value    :   None.
Modify History:
    1)  Date    :   2014-02-02
        Author  :   a00295761
        Modify content :    Create

    1)  Date    :   2015-05-08
        Author  :   y00245242
        Modify content : iteration 13开发
*****************************************************************************/
VOS_VOID NAS_MSCC_SetModuleOrder_PowerOff(VOS_VOID)
{
    NAS_MSCC_FSM_POWER_OFF_CTX_STRU    *pstModuleOrder;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT16                          usPowerOffHrpdIndex;
    VOS_UINT16                          usPowerOff3GppIndex;

    usPowerOffHrpdIndex                = 0xFFFF;
    usPowerOff3GppIndex                = 0xFFFF;
#endif

    pstModuleOrder                     = NAS_MSCC_GetModuleOrderAddr_PowerOff();

    /* Clearing the Module order structure */
    PS_MEM_SET(pstModuleOrder,
               0x00,
               sizeof(NAS_MSCC_FSM_POWER_OFF_CTX_STRU));

    /* If IMS Feature is ON, Add IMS module ID to the Module order array */
#if (FEATURE_ON == FEATURE_IMS)
    if (VOS_TRUE == NAS_MSCC_GetImsSupportFlag())
    {
        pstModuleOrder->aulModuleID[pstModuleOrder->usNum] = PS_PID_IMSA;
        pstModuleOrder->usNum ++;
    }
#endif

    /* If CDMA Feature is ON, Add XSD and HSD module ID to the Module order array */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == NAS_MSCC_IsPlatformSupportCdma1X())
    {
        /* Adding XSD module ID */
        pstModuleOrder->aulModuleID[pstModuleOrder->usNum] = UEPS_PID_XSD;
        pstModuleOrder->usNum ++;
    }

    if (VOS_TRUE == NAS_MSCC_IsPlatformSupportCdmaEVDO())
    {
        /* Adding HSD module ID */
        pstModuleOrder->aulModuleID[pstModuleOrder->usNum] = UEPS_PID_HSD;
        pstModuleOrder->usNum ++;

        usPowerOffHrpdIndex = pstModuleOrder->usNum - 1;
    }
#endif

    /* If GUL is supported add MMC module ID to the Module order array */
    if (VOS_TRUE == NAS_MSCC_IsPlatformSupport3Gpp())
    {
        pstModuleOrder->aulModuleID[pstModuleOrder->usNum] = WUEPS_PID_MMC;
        pstModuleOrder->usNum ++;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        usPowerOff3GppIndex = pstModuleOrder->usNum - 1;
#endif
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* 对于HRPD与LTE都支持时，确保主模先关机, 这里交换一下主从模power save顺序 */
    if ((VOS_TRUE == NAS_MSCC_Get3gppActiveFlg())
     && (0xFFFF    != usPowerOffHrpdIndex)
     && (0xFFFF    != usPowerOff3GppIndex))
    {
        pstModuleOrder->aulModuleID[usPowerOffHrpdIndex] = WUEPS_PID_MMC;

        pstModuleOrder->aulModuleID[usPowerOff3GppIndex] = UEPS_PID_HSD;
    }
#endif

    /* Reset the module order index */
    pstModuleOrder->usIndex = 0;

    return;
}




VOS_UINT32 NAS_MSCC_GetNextModuleId_PowerOff(
    VOS_UINT32                          *pulNextModuleId
)
{
    NAS_MSCC_FSM_POWER_OFF_CTX_STRU    *pstModuleOrder;

    pstModuleOrder                      = NAS_MSCC_GetModuleOrderAddr_PowerOff();

    /* If the index of the Module order array is greater than the Total number of supported Modules, Return FALSE*/
    if (pstModuleOrder->usIndex >= pstModuleOrder->usNum)
    {
        return VOS_FALSE;
    }

    /* Write the next module ID from the module order array at the address pointed by pulNextModuleId */
    *pulNextModuleId = pstModuleOrder->aulModuleID[pstModuleOrder->usIndex];

    /* Increment the index of the module order array */
    pstModuleOrder->usIndex ++;

    return VOS_TRUE;
}




VOS_UINT32 NAS_MSCC_IsModuleOrderValid_PowerOff(VOS_VOID)
{
    NAS_MSCC_FSM_POWER_OFF_CTX_STRU    *pstModuleOrder;

    pstModuleOrder                   = NAS_MSCC_GetModuleOrderAddr_PowerOff();

    /* Return FALSE if Number of modules is zero. */
    if (0 == pstModuleOrder->usNum)
    {
        NAS_ERROR_LOG1(UEPS_PID_MSCC,
                       "NAS_MSCC_IsModuleOrderValid: Module Number = %d Error!",
                       pstModuleOrder->usNum);
        return VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_IMS)
    /* If IMS feature is enabled, atleast one other module must also be supported. */
    if ((1 == pstModuleOrder->usNum)
     && (PS_PID_IMSA == pstModuleOrder->aulModuleID[0]))
    {
        NAS_ERROR_LOG1(UEPS_PID_MSCC,
                       "NAS_MSCC_IsModuleOrderValid: Module Number = %d Error!",
                       pstModuleOrder->usNum);
        return VOS_FALSE;
    }
#endif

    return VOS_TRUE;
}



VOS_UINT32 NAS_MSCC_IsPlatformSupport3Gpp(VOS_VOID)
{
    VOS_UINT32                                              i;
    VOS_RATMODE_ENUM_UINT32                                 enRatType         = VOS_RATMODE_BUTT;
    NAS_MSCC_PLATFORM_RAT_CAP_STRU                         *pstPlatformRatCap = VOS_NULL_PTR;


    pstPlatformRatCap = NAS_MSCC_GetPlatformRatCap();

    /* Check if GSM, WCDMA, TDS or LTE is present in the Platform RAT List */
    for (i = 0 ; i < pstPlatformRatCap->ucRatNum; i++)
    {
        enRatType = pstPlatformRatCap->aenRatList[i];

        if ((VOS_RATMODE_GSM             == enRatType)
         || (VOS_RATMODE_WCDMA           == enRatType)
         || (VOS_RATMODE_TDS             == enRatType)
         || (VOS_RATMODE_LTE             == enRatType))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_MSCC_IsPlatformSupport3Gpp2(VOS_VOID)
{
    VOS_UINT32                                              i;
    VOS_RATMODE_ENUM_UINT32                                 enRatType         = VOS_RATMODE_BUTT;
    NAS_MSCC_PLATFORM_RAT_CAP_STRU                         *pstPlatformRatCap = VOS_NULL_PTR;


    pstPlatformRatCap = NAS_MSCC_GetPlatformRatCap();

    /* Check if ix or hrpd is present in the Platform RAT List */
    for (i = 0 ; i < pstPlatformRatCap->ucRatNum; i++)
    {
        enRatType = pstPlatformRatCap->aenRatList[i];

        if ((VOS_RATMODE_1X     == enRatType)
         || (VOS_RATMODE_HRPD   == enRatType))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_MSCC_IsPlatformSupportLte(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_RATMODE_ENUM_UINT32             enRatType         = VOS_RATMODE_BUTT;
    NAS_MSCC_PLATFORM_RAT_CAP_STRU     *pstPlatformRatCap = VOS_NULL_PTR;


    pstPlatformRatCap = NAS_MSCC_GetPlatformRatCap();

    /* Check if LTE is present in the Platform RAT List */
    for (i = 0 ; i < pstPlatformRatCap->ucRatNum; i++)
    {
        enRatType = pstPlatformRatCap->aenRatList[i];

        if (VOS_RATMODE_LTE == enRatType)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_MSCC_IsPlatformSupportCdma1X(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MSCC_PLATFORM_RAT_CAP_STRU     *pstPlatformRatCap = VOS_NULL_PTR;

    pstPlatformRatCap = NAS_MSCC_GetPlatformRatCap();

    /* Check if CDMA or EVDO is listed in the plaform RAT LIST */
    for (i = 0 ; i < pstPlatformRatCap->ucRatNum; i++)
    {
        if ((VOS_RATMODE_1X   == pstPlatformRatCap->aenRatList[i]))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}




VOS_UINT32 NAS_MSCC_IsPlatformSupportCdmaEVDO(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MSCC_PLATFORM_RAT_CAP_STRU     *pstPlatformRatCap = VOS_NULL_PTR;

    pstPlatformRatCap = NAS_MSCC_GetPlatformRatCap();

    /* Check if CDMA or EVDO is listed in the plaform RAT LIST */
    for (i = 0 ; i < pstPlatformRatCap->ucRatNum; i++)
    {
        if ((VOS_RATMODE_HRPD   == pstPlatformRatCap->aenRatList[i]))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}




NAS_MSCC_PLATFORM_RAT_CAP_STRU*  NAS_MSCC_GetPlatformRatCap(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo.stCustomCfgInfo.stPlatformRatCap);
}




VOS_UINT32 NAS_MSCC_IsPlatformRatCapNvimValid(
    PLATAFORM_RAT_CAPABILITY_STRU      *pstNvPlatformRatCap
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    /* Return False if the number of the RAT supported is zero */
    if (0 == pstNvPlatformRatCap->usRatNum)
    {
        NAS_TRACE_HIGH("NAS_MSCC_IsPlatformRatCapNvimValid: Number of RATs read from NV Item is zero!");

        return VOS_FALSE;
    }

    for (i = 0; i < pstNvPlatformRatCap->usRatNum; i++)
    {
        /* Check if any duplicate exists in the NVIM data  */
        for (j = i + 1 ; j < pstNvPlatformRatCap->usRatNum; j++)
        {
            if (pstNvPlatformRatCap->aenRatList[i] == pstNvPlatformRatCap->aenRatList[j])
            {
                NAS_TRACE_HIGH("NAS_MSCC_IsPlatformRatCapNvimValid: Duplicates exist in RATs read from NV Item!");

                return VOS_FALSE;
            }
        }

        /* Return False if any undefined value exists */
        if (pstNvPlatformRatCap->aenRatList[i] >= PLATFORM_RAT_BUTT)
        {
            NAS_TRACE_HIGH("NAS_MSCC_IsPlatformRatCapNvimValid: Invalid RAT read from NV Item!");

            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}



VOS_VOID NAS_MSCC_InitCurrFsmCtx(
    NAS_MSCC_FSM_CTX_STRU              *pstCurrFsmCtx
)
{
    pstCurrFsmCtx->enFsmId                  =   NAS_MSCC_FSM_L1_MAIN;
    pstCurrFsmCtx->pstFsmDesc               =   NAS_MSCC_GetMainFsmDescAddr();
    pstCurrFsmCtx->ulState                  =   NAS_MSCC_L1_STA_NULL;
    pstCurrFsmCtx->enParentFsmId            =   NAS_MSCC_BUTT;
    pstCurrFsmCtx->ulParentEventType        =   0;
    pstCurrFsmCtx->stEntryMsg.ulEventType   =   0;

    /* Clear the Entry message buffer */
    PS_MEM_SET(pstCurrFsmCtx->stEntryMsg.aucMsgBuffer,
               0x00,
               NAS_MSCC_MAX_MSG_BUFFER_LEN);
}




VOS_VOID NAS_MSCC_InitFsmStackCtx(
    NAS_MSCC_FSM_STACK_STRU            *pstFsmStack
)
{
    VOS_UINT32                          i;

    pstFsmStack->usStackDepth   = 0;

    for (i = 0 ; i < NAS_MSCC_MAX_FSM_STACK_DEPTH ; i++)
    {
        pstFsmStack->astFsmStack[i].pstFsmDesc  = VOS_NULL_PTR;
        pstFsmStack->astFsmStack[i].enFsmId     = NAS_MSCC_BUTT;
        pstFsmStack->astFsmStack[i].ulState     = NAS_MSCC_L1_STA_BUTT;
    }
}




VOS_VOID NAS_MSCC_InitTimerCtx(
    NAS_MSCC_TIMER_CTX_STRU            *pstTimerCtx
)
{
    VOS_UINT32                          i;

    for (i = 0; i < TI_NAS_MSCC_TIMER_BUTT; i++ )
    {
        pstTimerCtx[i].hTimer           = VOS_NULL_PTR;
        pstTimerCtx[i].enTimerId        = TI_NAS_MSCC_TIMER_BUTT;
        pstTimerCtx[i].enTimerStatus    = NAS_MSCC_TIMER_STATUS_STOP;
    }

}




NAS_MSCC_MS_CFG_INFO_STRU* NAS_MSCC_GetMsCfgInfoStruAddr(VOS_VOID)
{
    return (&(NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo));
}




VOS_VOID NAS_MSCC_InitFsmCtx_SwitchOn(VOS_VOID)
{
    if (NAS_MSCC_FSM_SWITCH_ON != NAS_MSCC_GetCurrFsmId())
    {
        /* Make Error log is FSM Id is not Switch On */
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_InitFsmCtx_SwitchOn:ENTERED");

        return;
    }

    NAS_MSCC_InitCardReadInfor(NAS_MSCC_GetCardReadInforAddr());

    /* Create the Switch On Module Order list */
    NAS_MSCC_SetModuleOrder_SwitchOn();
}




VOS_VOID NAS_MSCC_InitFsmCtx_PowerOff(VOS_VOID)
{
    if (NAS_MSCC_FSM_POWER_OFF != NAS_MSCC_GetCurrFsmId())
    {
        /* Make Error log is FSM Id is not Power Off */
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_InitFsmCtx_PowerOff:ENTERED");

        return;
    }

    /* Create the Power Off Module Order list */
    NAS_MSCC_SetModuleOrder_PowerOff();
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID NAS_MSCC_InitFsmCtx_SysAcq(VOS_VOID)
{

    NAS_MSCC_FSM_SYS_ACQ_CTX_STRU                          *pstSysAcqFsmCtx;

    pstSysAcqFsmCtx     = NAS_MSCC_GetSysAcqFsmCtxAddr();

    if (NAS_MSCC_FSM_SYS_ACQ != NAS_MSCC_GetCurrFsmId())
    {
        /* Make Error log is FSM Id is not system acquire */
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_InitFsmCtx_SysAcq:ENTERED");

        return;
    }

    PS_MEM_SET(pstSysAcqFsmCtx,
               0x00,
               sizeof(NAS_MSCC_FSM_SYS_ACQ_CTX_STRU));

    pstSysAcqFsmCtx->ucNeedReAcqLteFlg               = NAS_MSCC_GetMmssSysAcqCfgInfoAddr()->ucReAcqLteOnHrpdSyncIndFlag;
    pstSysAcqFsmCtx->ucAbortFlg                      = VOS_FALSE;
    pstSysAcqFsmCtx->ucSearchLteFlag                 = VOS_FALSE;
    pstSysAcqFsmCtx->ucSearchHrpdFlag                = VOS_FALSE;
    pstSysAcqFsmCtx->st1xInitLocSta.enLocInfoStatus  = NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_BUTT;
    pstSysAcqFsmCtx->stLteInitLocSta.enLocInfoStatus = NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_BUTT;
}


VOS_VOID NAS_MSCC_InitFsmCtx_BSR(VOS_VOID)
{
    NAS_MSCC_3GPP_SYS_INFO_STRU                            *pst3gppSysInfo = VOS_NULL_PTR;
    NAS_MSCC_HRPD_SYS_INFO_STRU                            *pstHrpdSysInfo = VOS_NULL_PTR;
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                        stOutSysList;
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU                stIn3gppInfo;
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU                stInHrpdInfo;
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8                  enSysType;
    NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8                  enPriClass;
    NAS_MSCC_CTX_STRU                                      *pstMsccCtx = VOS_NULL_PTR;
    VOS_UINT8                                               ucMsplIndex;
    VOS_UINT8                                               ucDefMsplRec;
    NAS_MSCC_MSPL_ID_STRU                                  *pstMatchedMsplTable = VOS_NULL_PTR;

    pstMsccCtx = NAS_MSCC_GetMsccCtxAddr();

    PS_MEM_SET(&(pstMsccCtx->stCurFsm.unFsmCtx.stBsrCtx), 0x00, sizeof(NAS_MSCC_FSM_BSR_CTX_STRU));

    pstMsccCtx->stCurFsm.unFsmCtx.stBsrCtx.stPrefPlmnList.enRat = NAS_MSCC_PIF_NET_RAT_TYPE_LTE;

    if (VOS_TRUE == NAS_MSCC_GetHrpdCampOnFlag())
    {
        pstHrpdSysInfo = NAS_MSCC_GetHrpdSysInfoAddr();

        stInHrpdInfo.enPriClassCdma2000Hrpd = pstHrpdSysInfo->enHrpdPrioClass;
        stInHrpdInfo.enPriClassCdma2000Ai   = pstHrpdSysInfo->enAIPrioClass;
        stInHrpdInfo.ucIsMccValid           = VOS_TRUE;
        stInHrpdInfo.ulMcc                  = pstHrpdSysInfo->ulMcc;
        stInHrpdInfo.ucSubNetMask           = pstHrpdSysInfo->ucSubNetMask;

        PS_MEM_CPY(stInHrpdInfo.aucSectorId,
                   pstHrpdSysInfo->aucSectorId,
                   NAS_MSCC_BYTES_IN_SUBNET);

        PS_MEM_SET(&stOutSysList, 0x00, sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

        (VOS_VOID)NAS_MSCC_GetHigherPriMsplSysListThanHrpd(&stInHrpdInfo, &stOutSysList);

        enPriClass = NAS_MSCC_GetDestBsrSysPriClassInSysList(VOS_RATMODE_HRPD, &stOutSysList);
        enSysType  = NAS_MSCC_GetDestBsrSysTypeInSysList(VOS_RATMODE_HRPD, &stOutSysList);
    }
    else
    {
        pst3gppSysInfo         =   NAS_MSCC_Get3gppSysInfoAddr();

        stIn3gppInfo.stPlmnId.ulMcc = pst3gppSysInfo->stPlmnId.ulMcc;
        stIn3gppInfo.stPlmnId.ulMnc = pst3gppSysInfo->stPlmnId.ulMnc;
        stIn3gppInfo.enPriClass     = pst3gppSysInfo->enPrioClass;
        stIn3gppInfo.enSysRat       = VOS_RATMODE_LTE;

        PS_MEM_SET(&stOutSysList, 0x00, sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

        pstMatchedMsplTable= NAS_MSCC_GetMatchedMsplTableBy3gppInfo(&stIn3gppInfo);

        if (VOS_NULL_PTR != pstMatchedMsplTable)
        {
            (VOS_VOID)NAS_MSCC_GetHigherPriSysListWithMsplTable(&stIn3gppInfo,
                                                                pstMatchedMsplTable,
                                                                &stOutSysList);
        }

        enSysType  = NAS_MSCC_GetDestBsrSysTypeInSysList(VOS_RATMODE_LTE, &stOutSysList);
        enPriClass = NAS_MSCC_GetDestBsrSysPriClassInSysList(VOS_RATMODE_LTE, &stOutSysList);
    }

    NAS_MSCC_SetDestBsrSysType_BSR(enSysType);
    NAS_MSCC_SetDestBsrSysPriClass_BSR(enPriClass);

    ucMsplIndex = 0;

    ucDefMsplRec = VOS_FALSE;

    NAS_MSCC_SetOrigSysDefMsplRecFlg_BSR(VOS_FALSE);

    if (VOS_TRUE == NAS_MSCC_GetCurrentCampedSysMsplIndex(&ucMsplIndex, &ucDefMsplRec))
    {
        NAS_MSCC_SetOrigSysMsplIndex_BSR(ucMsplIndex);

        NAS_MSCC_SetOrigSysDefMsplRecFlg_BSR(ucDefMsplRec);
    }

    return;
}
#endif

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))
/*****************************************************************************
Function Name   :   NAS_MSCC_IsCLCombinedModeWithRatPrio
Description     :   是否是CL mode
Input parameters:   None.
Output parameters:  None.
Return Value    :

Modify History:
    1)  Date    :   2015-07-13
        Author  :   f00279542
        Modify content :    Create
*****************************************************************************/
VOS_UINT8 NAS_MSCC_IsCLCombinedModeWithRatPrio
(
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstUserRatPrio
)
{
    VOS_UINT16                          ulLoop;

    /* 有1X或hrpd rat 就表示是CL模式 */
    for (ulLoop = 0; ulLoop < pstUserRatPrio->ucRatNum; ulLoop++)
    {
        if ((NAS_MSCC_PIF_NET_RAT_TYPE_1X == pstUserRatPrio->aucRatPrio[ulLoop])
         || (NAS_MSCC_PIF_NET_RAT_TYPE_HRPD == pstUserRatPrio->aucRatPrio[ulLoop]))
        {
            return TRUE;
        }
    }

    return FALSE;
}

#endif



NAS_MSCC_SYSACQ_TIMER_CFG_STRU*         NAS_MSCC_GetSysAcqTimerCfgAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo.stCustomCfgInfo.stMmssNvimCfgInfo.stMmssSysAcqCfg.stSysAcqTimerCfg);
}




NAS_MSCC_MMSS_LOCATION_INFO_STRU*       NAS_MSCC_GetMmssLastLocationInfoAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo.stCustomCfgInfo.stMmssNvimCfgInfo.stMmssLastLocInfo);
}




NAS_MSCC_MMSS_CFG_INFO_STRU* NAS_MSCC_GetMmssNvimCfgInfoAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo.stCustomCfgInfo.stMmssNvimCfgInfo);
}




NAS_MSCC_MMSS_SYSACQ_CFG_STRU* NAS_MSCC_GetMmssSysAcqCfgInfoAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo.stCustomCfgInfo.stMmssNvimCfgInfo.stMmssSysAcqCfg);
}



NAS_MSCC_3GPP_SYS_INFO_STRU* NAS_MSCC_Get3gppSysInfoAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gppSysInfo);
}




NAS_MSCC_1X_SYS_INFO_STRU* NAS_MSCC_Get1xSysInfoAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gpp2SysInfo.st1xSysInfo);
}




NAS_MSCC_HRPD_SYS_INFO_STRU* NAS_MSCC_GetHrpdSysInfoAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gpp2SysInfo.stHrpdSysInfo);
}



VOS_VOID NAS_MSCC_Set1xCampOnFlag(
    VOS_UINT8                           ucFlag
)
{
    NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gpp2SysInfo.st1xSysInfo.ucCampOnFlg = ucFlag;
}



VOS_UINT8 NAS_MSCC_Get1xCampOnFlag(VOS_VOID)
{
   return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gpp2SysInfo.st1xSysInfo.ucCampOnFlg);
}




VOS_VOID NAS_MSCC_SetHrpdCampOnFlag(
    VOS_UINT8                           ucFlag
)
{
    NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gpp2SysInfo.stHrpdSysInfo.ucCampOnFlg = ucFlag;
}



VOS_UINT8 NAS_MSCC_GetHrpdCampOnFlag(VOS_VOID)
{
   return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gpp2SysInfo.stHrpdSysInfo.ucCampOnFlg);
}



VOS_VOID NAS_MSCC_Set3gppCampOnFlag(
    VOS_UINT8                           ucFlag
)
{
    NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gppSysInfo.ucCampOnFlg = ucFlag;
}



NAS_MSCC_SYS_MODE_ENUM_UINT8 NAS_MSCC_Get3gppCurSysMode(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gppSysInfo.enSysMode);
}



VOS_UINT8 NAS_MSCC_Get3gppCampOnFlag(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gppSysInfo.ucCampOnFlg);
}




VOS_UINT8 NAS_MSCC_GetLteCampOnFlag(VOS_VOID)
{
    if (NAS_MSCC_SYS_MODE_LTE == NAS_MSCC_Get3gppCurSysMode())
    {
        return NAS_MSCC_Get3gppCampOnFlag();
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SetCurr3gppRoamingFlg
 功能描述  : 设置当前网络的漫游状态信息
 输入参数  : ucRoamingFlg 当前网络漫游状态信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_SetCurr3gppRoamingFlg(
    VOS_UINT8                               ucRoamingFlg
)
{
    (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gppSysInfo.ucRoamFlag) = ucRoamingFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_GetCurr3gppRoamingFlg
 功能描述  : 设置当前网络的漫游状态信息
 输入参数  : ucRoamingFlg 当前网络漫游状态信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MSCC_GetCurr3gppRoamingFlg(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gppSysInfo.ucRoamFlag);
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_UpdateRoamFlag
 功能描述  : 更新MSCC保存的RoamFlag标示
 输入参数  : enRegState       --MMC上报的注册状态消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : DTS2015082002854: 漫游标记不准
*****************************************************************************/
VOS_VOID NAS_MSCC_UpdateRoamFlag(
    NAS_MSCC_PIF_REG_STATE_ENUM_UINT8   enRegState
)
{
    switch (enRegState)
    {
        case NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK:
            NAS_MSCC_SetCurr3gppRoamingFlg(VOS_FALSE);
            break;

        case NAS_MSCC_PIF_REG_REGISTERED_ROAM:
            NAS_MSCC_SetCurr3gppRoamingFlg(VOS_TRUE);
            break;

        default:
            NAS_NORMAL_LOG1(UEPS_PID_MSCC, "NAS_MSCC_UpdateRoamFlag enRegState", enRegState);
            break;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_SetCurr3gppPsServiceStatus
 功能描述  : 设置当前网络的业务状态信息
 输入参数  : enSrvSt 当前网络业务状态信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年04月11日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SetCurr3gppPsServiceStatus(
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enSrvSt
)
{
    (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stServiceStatusInfo.en3gppPsServiceStatus) = enSrvSt;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_GetCurr3gppPsServiceStatus
 功能描述  : 获取当前网络的业务状态信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MSCC_SERVICE_STATUS_INFO_STRU -- 当前网络业务状态信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年04月11日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MSCC_SERVICE_STATUS_ENUM_UINT8 NAS_MSCC_GetCurr3gppPsServiceStatus(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stServiceStatusInfo.en3gppPsServiceStatus);
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_GetLastSendToImsaRoamFlg
 功能描述  : 获取当前网络的上一次漫游状态信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8 -- 当前网络上一次漫游状态信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年11月23日
   作    者   : c00318887
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MSCC_GetLastSendToImsaRoamFlg(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSendToImsaInfo.ucRoamFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SetCurrRoamStatus
 功能描述  : 保存当前网络的漫游状态信息
 输入参数  : VOS_UINT8 -- 当前网络漫游状态信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月23日
    作    者   : c00318887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_SetLastSendToImsaRoamFlg(
    VOS_UINT8  ucRoamStatus
)
{
    NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSendToImsaInfo.ucRoamFlg = ucRoamStatus;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_SetCurr1xServiceStatus
 功能描述  : 获取当前网络的业务状态信息
 输入参数  : enSrvSt 当前网络业务状态信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年04月11日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SetCurr1xServiceStatus(
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enSrvSt
)
{
    (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stServiceStatusInfo.en1xServiceStatus) = enSrvSt;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_GetCurr1xServiceStatus
 功能描述  : 获取当前网络的业务状态信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MSCC_SERVICE_STATUS_INFO_STRU -- 当前网络业务状态信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年04月11日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MSCC_SERVICE_STATUS_ENUM_UINT8 NAS_MSCC_GetCurr1xServiceStatus(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stServiceStatusInfo.en1xServiceStatus);
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SetCurrHrpdServiceStatus
 功能描述  : 获取当前网络的业务状态信息
 输入参数  : enSrvSt -- 当前网络的业务状态信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年04月11日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SetCurrHrpdServiceStatus(
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enSrvSt
)
{
    (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stServiceStatusInfo.enHrpdServiceStatus) = enSrvSt;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_GetCurrHrpdServiceStatus
 功能描述  : 获取当前网络的业务状态信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MSCC_SERVICE_STATUS_INFO_STRU -- 当前网络业务状态信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年04月11日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MSCC_SERVICE_STATUS_ENUM_UINT8 NAS_MSCC_GetCurrHrpdServiceStatus(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stServiceStatusInfo.enHrpdServiceStatus);
}




VOS_VOID NAS_MSCC_SetBsrTimerNvimActiveFlag(
    VOS_UINT8                           ucFlag
)
{
    NAS_MSCC_GetMmssNvimCfgInfoAddr()->stMmssSysAcqCfg.stSysAcqTimerCfg.ucIsBsrTimerNvimActiveFlag = ucFlag;
}




VOS_UINT8 NAS_MSCC_GetBsrTimerNvimActiveFlag(VOS_VOID)
{
    return (NAS_MSCC_GetMmssNvimCfgInfoAddr()->stMmssSysAcqCfg.stSysAcqTimerCfg.ucIsBsrTimerNvimActiveFlag);
}

/*****************************************************************************
Function Name   :   NAS_MSCC_InitFsmCtx_L1Main
Description     :   This function is used to init the l1 main fsm ctx
Input parameters:   None.
Output parameters:  None.
Return Value    :   None.
Modify History:
    1)  Date    :   2014-04-07
        Author  :   w00176964
        Modify content :    Create
    2)  Date    :   2015-12-10
        Author  :   w00176964
        Modify content :CL_MUTIMODE_OPTIMIZE调整
*****************************************************************************/

VOS_VOID NAS_MSCC_InitFsmCtx_L1Main(VOS_VOID)
{
    NAS_MSCC_CTX_STRU                  *pstMsccCtx = VOS_NULL_PTR;

    pstMsccCtx = NAS_MSCC_GetMsccCtxAddr();

    if (NAS_MSCC_FSM_L1_MAIN != NAS_MSCC_GetCurrFsmId())
    {
        /* Make Error log is FSM Id is not Power Off */
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_InitFsmCtx_L1Main:ENTERED");

        return;
    }

    pstMsccCtx->stCurFsm.unFsmCtx.stL1MainCtx.stOosAvailableTimerCtx.ulAvailableTimerCount = 0;

    pstMsccCtx->stCurFsm.unFsmCtx.stL1MainCtx.st1xServiceAvailableTimerCtx.ucCurLteFullBandSrchCount = 0;
    pstMsccCtx->stCurFsm.unFsmCtx.stL1MainCtx.st1xServiceAvailableTimerCtx.ucCurLteHistorySrchCount  = 0;

}


/*****************************************************************************
Function Name   :   NAS_MSCC_GetCurOosAvailableTimerStartCount_L1Main
Description     :   The function is used to get current available timer start count
Input parameters:   None
Output parameters:  None.
Return Value    :   the available timer start count
Modify History:
    1)  Date    :   2015-04-07
        Author  :   w00176964
        Modify content :    Create
    2)  Date    :   2015-04-07
        Author  :   w00176964
        Modify content :CL_MUTIMODE_OPTIMIZE调整
*****************************************************************************/
VOS_UINT32  NAS_MSCC_GetCurOosAvailableTimerStartCount_L1Main(VOS_VOID)
{
    if (NAS_MSCC_FSM_L1_MAIN != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetCurAvailableTimerStartCount_L1Main,ERROR:FsmId Error");
    }

    return  NAS_MSCC_GetCurFsmAddr()->unFsmCtx.stL1MainCtx.stOosAvailableTimerCtx.ulAvailableTimerCount;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_ResetCurOosAvailableTimerStartCount_L1Main
Description     :   The function is used to reset current available timer start count
Input parameters:   None
Output parameters:  None.
Return Value    :   NONE
Modify History:
    1)  Date    :   2015-04-07
        Author  :   w00176964
        Modify content :    Create
    2)  Date    :   2015-12-12
        Author  :   w00176964
        Modify content :CL_MUTIMODE_OPTIMIZE调整
*****************************************************************************/
VOS_VOID  NAS_MSCC_ResetCurOosAvailableTimerStartCount_L1Main(VOS_VOID)
{
    if (NAS_MSCC_FSM_L1_MAIN != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ResetCurOosAvailableTimerStartCount_L1Main,ERROR:FsmId Error");

        return;
    }

    NAS_MSCC_GetCurFsmAddr()->unFsmCtx.stL1MainCtx.stOosAvailableTimerCtx.ulAvailableTimerCount = 0;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_AddCurOosAvailableTimerStartCount_L1Main
Description     :   The function is used to add current available timer start count
Input parameters:   None
Output parameters:  None.
Return Value    :   None
Modify History:
    1)  Date    :   2015-04-07
        Author  :   w00176964
        Modify content :    Create
    2)  Date    :   2015-04-07
        Author  :   w00176964
        Modify content :CL_MUTIMODE_OPTIMIZE调整
*****************************************************************************/
VOS_VOID  NAS_MSCC_AddCurOosAvailableTimerStartCount_L1Main(VOS_VOID)
{
    if (NAS_MSCC_FSM_L1_MAIN != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_AddCurAvailableTimerStartCount_L1Main,ERROR:FsmId Error");

        return;
    }

    (NAS_MSCC_GetCurFsmAddr()->unFsmCtx.stL1MainCtx.stOosAvailableTimerCtx.ulAvailableTimerCount)++;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_GetNextOosAvailableTimerLength_L1Main
Description     :   The function is used to get next start available timer length
Input parameters:   None
Output parameters:  None.
Return Value    :   the next available timer length
Modify History:
    1)  Date    :   2015-04-07
        Author  :   w00176964
        Modify content :    Create
    2)  Date    :   2015-12-10
        Author  :   w00176964
        Modify content :CL_MUTIMODE_OPTIMIZE调整
*****************************************************************************/
VOS_UINT32  NAS_MSCC_GetNextOosAvailableTimerLength_L1Main(VOS_VOID)
{
    VOS_UINT32                          ulCount;
    VOS_UINT32                          ulTimerLen;
    NAS_MSCC_SYSACQ_TIMER_CFG_STRU     *pstSysAcqTimerCfg;

    pstSysAcqTimerCfg          = NAS_MSCC_GetSysAcqTimerCfgAddr();

    ulCount                    = NAS_MSCC_GetCurOosAvailableTimerStartCount_L1Main();

    /* 如果当前搜索的次数不超过available 定时器的第一次次数,使用第一次时长,否则使用第二次的 */
    if (ulCount <= pstSysAcqTimerCfg->ulAvailableTimerCountFirstSearch)
    {
        ulTimerLen =  (pstSysAcqTimerCfg->ulAvailableTimerLengthFirstSearch);
    }
    else
    {
        ulTimerLen =  (pstSysAcqTimerCfg->ulAvailableTimerLengthDeepSearch);
    }

    return ulTimerLen;
}



VOS_UINT8 NAS_MSCC_GetMlplMsplValidFlag(VOS_VOID)
{
    NAS_MSCC_CTX_STRU                  *pstMsccCtx = VOS_NULL_PTR;

    pstMsccCtx = NAS_MSCC_GetMsccCtxAddr();

    if ((VOS_TRUE == pstMsccCtx->stMlplMsplInfo.ucMlplValid)
     && (VOS_TRUE == pstMsccCtx->stMlplMsplInfo.ucMsplValid))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}



VOS_VOID NAS_MSCC_SetMlplValidFlag(
    VOS_UINT8                           ucValid
)
{
    NAS_MSCC_GetMlplMsplInfoAddr()->ucMlplValid = ucValid;
}



VOS_VOID NAS_MSCC_SetMsplValidFlag(
    VOS_UINT8                           ucValid
)
{
    NAS_MSCC_GetMlplMsplInfoAddr()->ucMsplValid = ucValid;
}



NAS_MSCC_MLPL_MSPL_INFO_STRU* NAS_MSCC_GetMlplMsplInfoAddr(VOS_VOID)
{
    return (&(NAS_MSCC_GetMsccCtxAddr()->stMlplMsplInfo));
}



NAS_MSCC_MLPL_STRU* NAS_MSCC_GetMlplInfoAddr(VOS_VOID)
{
    return (&(NAS_MSCC_GetMsccCtxAddr()->stMlplMsplInfo.stMlplInfo));
}



NAS_MSCC_MSPL_STRU* NAS_MSCC_GetMsplInfoAddr(VOS_VOID)
{
    return (&(NAS_MSCC_GetMsccCtxAddr()->stMlplMsplInfo.stMsplInfo));
}



VOS_UINT32 NAS_MSCC_GetWaitCardReadCnfFlag_SwitchOn(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stCurFsm.unFsmCtx.stSwitchOnCtx.stCardReadInfo.ulWaitCardReadFlag);
}



VOS_VOID NAS_MSCC_SetWaitCardReadCnfFlag_SwitchOn(
    NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_ENUM_UINT32 enFlag
)
{
    NAS_MSCC_FSM_SWITCH_ON_CTX_STRU *pstSwitchOnCtx;

    pstSwitchOnCtx = &(NAS_MSCC_GetMsccCtxAddr()->stCurFsm.unFsmCtx.stSwitchOnCtx);

    pstSwitchOnCtx->stCardReadInfo.ulWaitCardReadFlag |= enFlag;
}



VOS_VOID NAS_MSCC_ClearWaitCardReadCnfFlag_SwitchOn(
    NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_ENUM_UINT32 enFlag
)
{
    NAS_MSCC_FSM_SWITCH_ON_CTX_STRU *pstSwitchOnCtx;

    pstSwitchOnCtx = &(NAS_MSCC_GetMsccCtxAddr()->stCurFsm.unFsmCtx.stSwitchOnCtx);

    pstSwitchOnCtx->stCardReadInfo.ulWaitCardReadFlag &= ~enFlag;
}


VOS_VOID NAS_MSCC_ResetWaitCardReadCnfFlg_SwitchOn(VOS_VOID)
{
    NAS_MSCC_FSM_SWITCH_ON_CTX_STRU *pstSwitchOnCtx;

    pstSwitchOnCtx = &(NAS_MSCC_GetMsccCtxAddr()->stCurFsm.unFsmCtx.stSwitchOnCtx);

    pstSwitchOnCtx->stCardReadInfo.ulWaitCardReadFlag = NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_NULL;
}



NAS_MSCC_PIF_SIM_EHPLMN_INFO_STRU* NAS_MSCC_GetEhPlmnInfoAddr(VOS_VOID)
{
   return (&(NAS_MSCC_GetMsccCtxAddr()->stSimInfo.stSimPlmnInfo.stEhPlmnInfo));
}



NAS_MSCC_PIF_SIM_USERPLMN_INFO_STRU* NAS_MSCC_GetUserPlmnInfoAddr(VOS_VOID)
{
   return (&(NAS_MSCC_GetMsccCtxAddr()->stSimInfo.stSimPlmnInfo.stUserPlmnInfo));
}



NAS_MSCC_PIF_SIM_OPERPLMN_INFO_STRU* NAS_MSCC_GetOperPlmnInfoAddr(VOS_VOID)
{
   return (&(NAS_MSCC_GetMsccCtxAddr()->stSimInfo.stSimPlmnInfo.stOperPlmnInfo));
}



VOS_VOID NAS_MSCC_InitMlplMsplInfo(
    NAS_MSCC_INIT_CTX_TYPE_ENUM_UINT8                       enInitType,
    NAS_MSCC_MLPL_MSPL_INFO_STRU                           *pstMlplMsplInfo
)
{
    VOS_UINT8                                               ucLoop;

    if (NAS_MSCC_INIT_CTX_STARTUP == enInitType)
    {
        PS_MEM_SET(pstMlplMsplInfo, 0, sizeof(NAS_MSCC_MLPL_MSPL_INFO_STRU));

        return;
    }

    if (NAS_MSCC_INIT_CTX_POWEROFF == enInitType)
    {
        for (ucLoop = 0; ucLoop < NAS_MSCC_MAX_NUM_MLPL_REC; ucLoop++)
        {
            if (VOS_NULL_PTR != pstMlplMsplInfo->stMlplInfo.apstMlplRec[ucLoop])
            {
                PS_MEM_FREE(UEPS_PID_MSCC, pstMlplMsplInfo->stMlplInfo.apstMlplRec[ucLoop]);
            }
        }

        for (ucLoop = 0; ucLoop < NAS_MSCC_MAX_NUM_MSPL_ID; ucLoop++)
        {
            if (VOS_NULL_PTR != pstMlplMsplInfo->stMsplInfo.apstMsplId[ucLoop])
            {
                PS_MEM_FREE(UEPS_PID_MSCC, pstMlplMsplInfo->stMsplInfo.apstMsplId[ucLoop]);
            }
        }

        PS_MEM_SET(pstMlplMsplInfo, 0, sizeof(NAS_MSCC_MLPL_MSPL_INFO_STRU));

        return;
    }
}



VOS_VOID NAS_MSCC_InitSimInfo(
    NAS_MSCC_SIM_INFO_STRU                                 *pstSimInfo
)
{
    PS_MEM_SET(pstSimInfo, 0, sizeof(NAS_MSCC_SIM_INFO_STRU));

    pstSimInfo->stSimStatus.enUsimStatus = NAS_MSCC_PIF_CARD_STATUS_BUTT;
    pstSimInfo->stSimStatus.enCsimStatus = NAS_MSCC_PIF_CARD_STATUS_BUTT;

    /* 这里默认CS和PS的SIM卡注册状态为卡有效 */
    pstSimInfo->stSimStatus.ucSimCsRegStatus = VOS_TRUE;
    pstSimInfo->stSimStatus.ucSimPsRegStatus = VOS_TRUE;

    NAS_MSCC_InitSimUserPlmnInfo(&(pstSimInfo->stSimPlmnInfo.stUserPlmnInfo));
    NAS_MSCC_InitSimOperPlmnInfo(&(pstSimInfo->stSimPlmnInfo.stOperPlmnInfo));

    pstSimInfo->ucIsCardChanged             = VOS_TRUE;
}



VOS_VOID NAS_MSCC_InitCardReadInfor(
    NAS_MSCC_FSM_SWITCH_ON_CARD_READ_INFO_STRU             *pstCardReadInfo
)
{
    PS_MEM_SET(pstCardReadInfo, 0, sizeof(NAS_MSCC_FSM_SWITCH_ON_CARD_READ_INFO_STRU));
}



NAS_MSCC_FSM_SWITCH_ON_CARD_READ_INFO_STRU* NAS_MSCC_GetCardReadInforAddr(VOS_VOID)
{
    return (&(NAS_MSCC_GetMsccCtxAddr()->stCurFsm.unFsmCtx.stSwitchOnCtx.stCardReadInfo));
}



VOS_VOID NAS_MSCC_InitSimUserPlmnInfo(
    NAS_MSCC_PIF_SIM_USERPLMN_INFO_STRU                    *pstUserPlmnInfo
)
{
    VOS_UINT32                                              i;

    pstUserPlmnInfo->ucUserPlmnNum = 0;

    for ( i = 0 ; i < NAS_MSCC_PIF_MAX_USERPLMN_NUM ; i++ )
    {
        pstUserPlmnInfo->astUserPlmnInfo[i].stPlmnId.ulMcc = NAS_MSCC_INVALID_MCC;
        pstUserPlmnInfo->astUserPlmnInfo[i].stPlmnId.ulMnc = NAS_MSCC_INVALID_MNC;
    }
}



VOS_VOID NAS_MSCC_InitSimOperPlmnInfo(
    NAS_MSCC_PIF_SIM_OPERPLMN_INFO_STRU                    *pstOperPlmnInfo
)
{
    VOS_UINT32                                              i;

    pstOperPlmnInfo->usOperPlmnNum = 0;

    for ( i = 0 ; i < NAS_MSCC_PIF_MAX_OPERPLMN_NUM ; i++ )
    {
        pstOperPlmnInfo->astOperPlmnInfo[i].stPlmnId.ulMcc   = NAS_MSCC_INVALID_MCC;
        pstOperPlmnInfo->astOperPlmnInfo[i].stPlmnId.ulMnc   = NAS_MSCC_INVALID_MNC;
    }
}




VOS_UINT32 NAS_MSCC_GetAbortFlag_SysAcq(VOS_VOID)
{
    /* 如果当前状态机不是CL system acquire */
    if (NAS_MSCC_FSM_SYS_ACQ!= NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MSCC_GetAbortFlag_SysAcq,ERROR:FsmId Error");
    }

    return (VOS_UINT32)(g_stNasMsccCtx.stCurFsm.unFsmCtx.stSysAcqCtx.ucAbortFlg);
}


VOS_VOID NAS_MSCC_SetAbortFlag_SysAcq(
    VOS_UINT8                           ucAbortFlg
)
{
    /* 如果当前状态机不是CL system acquire */
    if (NAS_MSCC_FSM_SYS_ACQ!= NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MSCC_SetAbortFlag_SysAcq,ERROR:FsmId Error");
    }

    g_stNasMsccCtx.stCurFsm.unFsmCtx.stSysAcqCtx.ucAbortFlg = ucAbortFlg;
}



VOS_UINT8 NAS_MSCC_GetLteInitialAcqFinishFlg_SysAcq(VOS_VOID)
{
    /* 如果当前状态机不是CL system acquire */
    if (NAS_MSCC_FSM_SYS_ACQ!= NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetLteInitialAcqFinishFlg_SysAcq,ERROR:FsmId Error");
    }

    return (NAS_MSCC_GetSysAcqFsmCtxAddr()->stLteInitLocSta.ucAcqFinishFlg);
}




VOS_UINT8 NAS_MSCC_Get1xInitialAcqFinishFlg_SysAcq(VOS_VOID)
{
    /* 如果当前状态机不是CL system acquire */
    if (NAS_MSCC_FSM_SYS_ACQ!= NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_Get1xInitialAcqFinishFlg_SysAcq,ERROR:FsmId Error");
    }

    return (NAS_MSCC_GetSysAcqFsmCtxAddr()->st1xInitLocSta.ucAcqFinishFlg);
}



VOS_VOID NAS_MSCC_SetLteInitialAcqLocInfoStatus_SysAcq(
    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM_UINT8            enStatus
)
{
    if (NAS_MSCC_FSM_SYS_ACQ != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SetLteInitialAcqLocInfoStatus_SysAcq,ERROR:FsmId Error");
    }

    (NAS_MSCC_GetSysAcqFsmCtxAddr()->stLteInitLocSta.enLocInfoStatus) = enStatus;
}



VOS_VOID NAS_MSCC_Set1xInitialAcqLocInfoStatus_SysAcq(
    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM_UINT8            enStatus
)
{
    if (NAS_MSCC_FSM_SYS_ACQ != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_Set1xInitialAcqLocInfoStatus_SysAcq,ERROR:FsmId Error");
    }

    (NAS_MSCC_GetSysAcqFsmCtxAddr()->st1xInitLocSta.enLocInfoStatus) = enStatus;
}


NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM_UINT8 NAS_MSCC_GetLteInitialAcqLocInfoStatus_SysAcq(VOS_VOID)
{
    if (NAS_MSCC_FSM_SYS_ACQ != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetLteInitialAcqLocInfoStatus_SysAcq,ERROR:FsmId Error");
    }

    return (NAS_MSCC_GetSysAcqFsmCtxAddr()->stLteInitLocSta.enLocInfoStatus);
}



NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM_UINT8 NAS_MSCC_Get1xInitialAcqLocInfoStatus_SysAcq(VOS_VOID)
{
    if (NAS_MSCC_FSM_SYS_ACQ != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_Get1xInitialAcqLocInfoStatus_SysAcq,ERROR:FsmId Error");
    }

    return (NAS_MSCC_GetSysAcqFsmCtxAddr()->st1xInitLocSta.enLocInfoStatus);
}


VOS_UINT8 NAS_MSCC_GetInterSysSearchLteFlag_SysAcq(VOS_VOID)
{
    return (NAS_MSCC_GetSysAcqFsmCtxAddr()->ucSearchLteFlag);
}


VOS_VOID NAS_MSCC_SetInterSysSearchLteFlag_SysAcq(
    VOS_UINT8                               ucSearchLteFLag
)
{
    (NAS_MSCC_GetSysAcqFsmCtxAddr()->ucSearchLteFlag) = ucSearchLteFLag;

    return;
}


VOS_UINT8 NAS_MSCC_GetInterSysSearchHrpdFlag_SysAcq(VOS_VOID)
{
    return (NAS_MSCC_GetSysAcqFsmCtxAddr()->ucSearchHrpdFlag);
}


VOS_VOID NAS_MSCC_SetInterSysSearchHrpdFlag_SysAcq(
    VOS_UINT8                           ucSearchHrpdFLag
)
{
    (NAS_MSCC_GetSysAcqFsmCtxAddr()->ucSearchHrpdFlag) = ucSearchHrpdFLag;

    return;
}


VOS_UINT32 NAS_MSCC_GetScanTimerLength(VOS_VOID)
{
    NAS_MSCC_SYSACQ_TIMER_CFG_STRU     *pstSysAcqTimerCfg;

    pstSysAcqTimerCfg          = NAS_MSCC_GetSysAcqTimerCfgAddr();

    return pstSysAcqTimerCfg->ulScanTimerLen;
}


VOS_UINT32 NAS_MSCC_GetSleepTimerLength(VOS_VOID)
{
    NAS_MSCC_SYSACQ_TIMER_CFG_STRU     *pstSysAcqTimerCfg;

    pstSysAcqTimerCfg          = NAS_MSCC_GetSysAcqTimerCfgAddr();

    return pstSysAcqTimerCfg->ulSleepTimerLen;
}



VOS_UINT8  NAS_MSCC_GetHrpdConnExistFlg(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stConnStatusInfo.ucHrpdConnExistFlg);
}


VOS_VOID  NAS_MSCC_SetHrpdConnExistFlg(
    VOS_UINT8                           ucFlg
)
{
    NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stConnStatusInfo.ucHrpdConnExistFlg = ucFlg;
}


VOS_UINT8  NAS_MSCC_GetLteEpsConnExistFlg(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stConnStatusInfo.ucLteEpsConnExistFlg);
}


VOS_VOID  NAS_MSCC_SetLteEpsConnExistFlg(
    VOS_UINT8                           ucFlg
)
{
    NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stConnStatusInfo.ucLteEpsConnExistFlg= ucFlg;
}



NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8  NAS_MSCC_GetLtePriClass(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gppSysInfo.enPrioClass);
}


NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8  NAS_MSCC_Get1xPriClass(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gpp2SysInfo.st1xSysInfo.en1xPrioClass);
}


NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8  NAS_MSCC_Get1xAIPriClass(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gpp2SysInfo.st1xSysInfo.enAIPrioClass);
}


VOS_VOID  NAS_MSCC_Set1xActiveFlg(
    VOS_UINT8                           ucFlg
)
{
    NAS_MSCC_GetMsccCtxAddr()->stPowerSaveCtrl.uc1xActiveFlg = ucFlg;
}


VOS_UINT8  NAS_MSCC_Get1xActiveFlg(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stPowerSaveCtrl.uc1xActiveFlg);
}


VOS_VOID  NAS_MSCC_SetPowerSaveReplyFlg(
    VOS_UINT8                           ucFlg
)
{
    NAS_MSCC_GetMsccCtxAddr()->stPowerSaveCtrl.ucPowerSaveReplyFlg = ucFlg;
}


VOS_UINT8  NAS_MSCC_GetPowerSaveReplyFlg(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stPowerSaveCtrl.ucPowerSaveReplyFlg);
}


VOS_VOID  NAS_MSCC_SetHrpdActiveFlg(
    VOS_UINT8                           ucFlg
)
{
    NAS_MSCC_GetMsccCtxAddr()->stPowerSaveCtrl.ucHrpdActiveFlg = ucFlg;
}


VOS_UINT8  NAS_MSCC_GetHrpdActiveFlg(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stPowerSaveCtrl.ucHrpdActiveFlg);
}



VOS_VOID  NAS_MSCC_Set3gppActiveFlg(
    VOS_UINT8                           ucFlg
)
{
    NAS_MSCC_GetMsccCtxAddr()->stPowerSaveCtrl.uc3gppActiveFlg = ucFlg;
}


VOS_UINT8  NAS_MSCC_Get3gppActiveFlg(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stPowerSaveCtrl.uc3gppActiveFlg);
}





NAS_MSCC_PREF_ORDER_MODULE_LIST* NAS_MSCC_GetPowerSaveModuleOrderAddr_SysCfg(VOS_VOID)
{
    /* If the current FSM is not System config print log */
    if (NAS_MSCC_FSM_SYSTEM_CONFIG != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetPowerSaveModuleOrderAddr_SysCfg : Wrong State entered..!");
    }

    return &(NAS_MSCC_GetMsccCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx.stPowerSaveModuleOrder);
}




NAS_MSCC_PREF_ORDER_MODULE_LIST* NAS_MSCC_GetSysCfgModuleOrderAddr_SysCfg(VOS_VOID)
{
    /* If the current FSM is not System config print log */
    if (NAS_MSCC_FSM_SYSTEM_CONFIG != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetSysCfgModuleOrderAddr_SysCfg : Wrong State entered..!");
    }

    return &(NAS_MSCC_GetMsccCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx.stSysCfgModuleOrder);
}





VOS_UINT32 NAS_MSCC_GetAbortFlag_BSR(VOS_VOID)
{
    /* 如果当前状态机不是BSR */
    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetAbortFlag_BSR ERROR:FsmId Error");
    }

    return (VOS_UINT32)(g_stNasMsccCtx.stCurFsm.unFsmCtx.stBsrCtx.ucAbortFlag);
}


VOS_VOID NAS_MSCC_SetAbortFlag_BSR(
    VOS_UINT8                           ucAbortFlg
)
{
    /* 如果当前状态机不是BSR */
    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SetAbortFlag_BSR ERROR:FsmId Error");
    }

    g_stNasMsccCtx.stCurFsm.unFsmCtx.stBsrCtx.ucAbortFlag = ucAbortFlg;

    return;
}


VOS_VOID NAS_MSCC_SetDestBsrSysPriClass_BSR(
    NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8                  enSysPriClass
)
{
    /* 如果当前状态机不是BSR */
    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetDestBsrSysPriClass_BSR ERROR:FsmId Error");
    }

    g_stNasMsccCtx.stCurFsm.unFsmCtx.stBsrCtx.enDestBsrSysPriClass = enSysPriClass;
}


NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8 NAS_MSCC_GetDestBsrSysPriClass_BSR(VOS_VOID)
{
    /* 如果当前状态机不是BSR */
    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetDestBsrSysPriClass_BSR ERROR:FsmId Error");
    }

    return (g_stNasMsccCtx.stCurFsm.unFsmCtx.stBsrCtx.enDestBsrSysPriClass);
}


VOS_VOID NAS_MSCC_SetDestBsrSysType_BSR(
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8                  enSysType
)
{
    /* 如果当前状态机不是BSR */
    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetDestBsrSysType_BSR ERROR:FsmId Error");
    }

    (g_stNasMsccCtx.stCurFsm.unFsmCtx.stBsrCtx.enDestBsrSysType) = enSysType;
}



VOS_VOID NAS_MSCC_SetOrigSysMsplIndex_BSR(
    VOS_UINT8                           ucOrigSysMsplIndex
)
{
    /* 如果当前状态机不是BSR */
    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SetOrigSysMsplIndex_BSR ERROR:FsmId Error");
    }

    (g_stNasMsccCtx.stCurFsm.unFsmCtx.stBsrCtx.ucOrigSysMsplIndex) = ucOrigSysMsplIndex;
}


VOS_UINT8 NAS_MSCC_GetOrigSysMsplIndex_BSR(VOS_VOID)
{
    /* 如果当前状态机不是BSR */
    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SetOrigSysMsplIndex_BSR ERROR:FsmId Error");
    }

    return (g_stNasMsccCtx.stCurFsm.unFsmCtx.stBsrCtx.ucOrigSysMsplIndex);
}


/*****************************************************************************
Function Name   :   NAS_MSCC_SetOrigSysDefMsplRecFlg_BSR
Description     :   设置原始系统是否在default mspl中的标记
Input parameters:   原始系统在default mspl中的标记
Output parameters:  None.
Return Value    :   None
Modify History:
    1)  Date    :   2016-01-08
        Author  :   w00176964
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_SetOrigSysDefMsplRecFlg_BSR(
    VOS_UINT8                           ucOrigSysUseDefMsplRec
)
{
    /* 如果当前状态机不是BSR */
    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SetOrigSysDefMsplRecFlg_BSR ERROR:FsmId Error");
    }

    (g_stNasMsccCtx.stCurFsm.unFsmCtx.stBsrCtx.ucOrigSysUseDefMsplRec) = ucOrigSysUseDefMsplRec;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_GetOrigSysDefMsplRecFlg_BSR
Description     :   获取原始系统是否在default mspl中的标记
Input parameters:   None.
Output parameters:  None.
Return Value    :   原始系统是否在default mspl中的标记
Modify History:
    1)  Date    :   2016-01-08
        Author  :   w00176964
        Modify content :    Create
*****************************************************************************/
VOS_UINT8 NAS_MSCC_GetOrigSysDefMsplRecFlg_BSR(VOS_VOID)
{
    /* 如果当前状态机不是BSR */
    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetOrigSysDefMsplRecFlg_BSR ERROR:FsmId Error");
    }

    return (g_stNasMsccCtx.stCurFsm.unFsmCtx.stBsrCtx.ucOrigSysUseDefMsplRec);
}





NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8 NAS_MSCC_GetDestBsrSysType_BSR(VOS_VOID)
{
    /* 如果当前状态机不是BSR */
    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetDestBsrSysType_BSR ERROR:FsmId Error");
    }

    return (g_stNasMsccCtx.stCurFsm.unFsmCtx.stBsrCtx.enDestBsrSysType);
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_GetHrpdHighPrioSysInfo_BSR
 功能描述  : 获取高优先级subnet列表
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年04月07日
   作    者   : y00307564
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MSCC_HIGH_PRIORITY_SYSTEM_INFO_STRU *NAS_MSCC_GetHrpdHighPrioSysInfo_BSR(VOS_VOID)
{
    return &(NAS_MSCC_GetCurFsmAddr()->unFsmCtx.stBsrCtx.stHighPriSysInfo);
}


NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU* NAS_MSCC_GetLtePrefPlmnListInfo_BSR(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stCurFsm.unFsmCtx.stBsrCtx.stPrefPlmnList);
}


VOS_VOID NAS_MSCC_SaveCardStatus(
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enUsimStatus,
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enCsimStatus
)
{
    NAS_MSCC_GetMsccCtxAddr()->stSimInfo.stSimStatus.enUsimStatus = enUsimStatus;
    NAS_MSCC_GetMsccCtxAddr()->stSimInfo.stSimStatus.enCsimStatus = enCsimStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SaveIsCardChanged
 功能描述  : 保存卡ICCID是否发生改变的标识
 输入参数  : VOS_UINT8          卡ICCID是否发生改变
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年08月26日
   作    者   : h00313353
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_SaveIsCardChangedFlg(
    VOS_UINT8                           ucIsCardChanged
)
{
    NAS_MSCC_GetMsccCtxAddr()->stSimInfo.ucIsCardChanged    = ucIsCardChanged;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_GetIsCardChanged
 功能描述  : 获取卡ICCID是否发生改变的标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8          卡ICCID是否发生改变
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年08月26日
   作    者   : h00313353
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MSCC_GetIsCardChangedFlg( VOS_VOID )
{
    return (NAS_MSCC_GetMsccCtxAddr()->stSimInfo.ucIsCardChanged);
}



VOS_VOID  NAS_MSCC_SetSimCsRegStatus(
    VOS_UINT8                           ucSimCsRegStatus
)
{
    NAS_MSCC_GetMsccCtxAddr()->stSimInfo.stSimStatus.ucSimCsRegStatus = ucSimCsRegStatus;
}


VOS_VOID  NAS_MSCC_SetSimPsRegStatus(
    VOS_UINT8                           ucSimPsRegStatus
)
{
    NAS_MSCC_GetMsccCtxAddr()->stSimInfo.stSimStatus.ucSimPsRegStatus = ucSimPsRegStatus;
}


VOS_UINT8  NAS_MSCC_GetSimCsRegStatus(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stSimInfo.stSimStatus.ucSimCsRegStatus);
}


VOS_UINT8  NAS_MSCC_GetSimPsRegStatus(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stSimInfo.stSimStatus.ucSimPsRegStatus);
}


VOS_VOID NAS_MSCC_SavePrioRatList(
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstRatPrio
)
{
    VOS_UINT8                           i;

    VOS_UINT8                           ucMinRatNum;

    ucMinRatNum = NAS_COMM_MIN(pstRatPrio->ucRatNum, NAS_MSCC_PIF_MAX_RAT_NUM);

    for (i = 0; i < ucMinRatNum; i++)
    {
        NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo.stMsSysCfgInfo.stRatPrio.aucRatPrio[i]
             = pstRatPrio->aucRatPrio[i];
    }

    NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo.stMsSysCfgInfo.stRatPrio.ucRatNum = ucMinRatNum;
}



NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 NAS_MSCC_GetUsimCardStatus(VOS_VOID)
{
    return NAS_MSCC_GetMsccCtxAddr()->stSimInfo.stSimStatus.enUsimStatus;
}


NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 NAS_MSCC_GetCsimCardStatus(VOS_VOID)
{
    return NAS_MSCC_GetMsccCtxAddr()->stSimInfo.stSimStatus.enCsimStatus;
}


NAS_MSCC_PIF_RAT_PRIO_STRU* NAS_MSCC_GetRatPrioList(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo.stMsSysCfgInfo.stRatPrio);
}


VOS_UINT32 NAS_MSCC_IsSpecRatSupported(
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enRat
)
{
    VOS_UINT8                           i;
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstRatPrioList;

    pstRatPrioList = NAS_MSCC_GetRatPrioList();

    for (i = 0; i < pstRatPrioList->ucRatNum; i++)
    {
        if (enRat == pstRatPrioList->aucRatPrio[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MSCC_IsUserSysCfgRatCapSupport3Gpp(VOS_VOID)
{
    VOS_UINT32                                              i;
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enRatType;
    NAS_MSCC_PIF_RAT_PRIO_STRU                             *pstRatPrioList = VOS_NULL_PTR;


    pstRatPrioList = NAS_MSCC_GetRatPrioList();

    /* Check if GSM, WCDMA, TDS or LTE is present in the RAT List */
    for (i = 0; i < pstRatPrioList->ucRatNum; i++)
    {
        enRatType = pstRatPrioList->aucRatPrio[i];

        if ((NAS_MSCC_PIF_NET_RAT_TYPE_GSM   == enRatType)
         || (NAS_MSCC_PIF_NET_RAT_TYPE_WCDMA == enRatType)
         || (NAS_MSCC_PIF_NET_RAT_TYPE_LTE   == enRatType))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



NAS_MSCC_SYS_ACQ_CTRL_CTX_STRU* NAS_MSCC_GetSysAcqCtrlInfoAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl);
}


VOS_VOID NAS_MSCC_SetCurrBsrTimerLen(
    VOS_UINT32                          ulBsrTimerLen
)
{
    NAS_MSCC_GetSysAcqCtrlInfoAddr()->ulCurrBsrTimerLen = ulBsrTimerLen;
    return;
}


VOS_UINT32 NAS_MSCC_GetCurrBsrTimerLen(VOS_VOID)
{
    return NAS_MSCC_GetSysAcqCtrlInfoAddr()->ulCurrBsrTimerLen;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SetEmcCallExistFlag
 功能描述  : 设置紧急呼标记是否存在
 输入参数  : VOS_UINT8                           ucIsEmcCallExistFlg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月6日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SetEmcCallExistFlag(
    VOS_UINT8                           ucIsEmcCallExistFlg
)
{
    NAS_MSCC_GetSysAcqCtrlInfoAddr()->ucIsEmcCallExist = ucIsEmcCallExistFlg;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_GetEmcCallExistFlag
 功能描述  : 获取紧急呼标记是否存在
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月6日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MSCC_GetEmcCallExistFlag(VOS_VOID)
{
    return NAS_MSCC_GetSysAcqCtrlInfoAddr()->ucIsEmcCallExist;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SetCallBackEnableFlag
 功能描述  : 设置紧急呼回呼功能标记是否存在
 输入参数  : VOS_UINT32                          ulCallBackEnableFlg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月6日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SetEmcCallBackEnableFlag(
    VOS_UINT32                          ulCallBackEnableFlg
)
{
    NAS_MSCC_GetSysAcqCtrlInfoAddr()->ulCallBackEnableFlg = ulCallBackEnableFlg;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_GetCallBackEnableFlag
 功能描述  : 获取紧急呼回呼功能是否使能
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月6日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_GetEmcCallBackEnableFlag(VOS_VOID)
{
    return NAS_MSCC_GetSysAcqCtrlInfoAddr()->ulCallBackEnableFlg;
}





VOS_VOID NAS_MSCC_SetOrigBsrTimerStartRat(VOS_VOID)
{
    if (VOS_TRUE == NAS_MSCC_GetHrpdCampOnFlag())
    {
        NAS_MSCC_GetSysAcqCtrlInfoAddr()->enOrigBsrTimerStartRat = VOS_RATMODE_HRPD;
    }
    else if (VOS_TRUE == NAS_MSCC_Get3gppCampOnFlag())
    {
        NAS_MSCC_GetSysAcqCtrlInfoAddr()->enOrigBsrTimerStartRat = VOS_RATMODE_LTE;
    }
    else
    {
    }

    return;
}


VOS_RATMODE_ENUM_UINT32 NAS_MSCC_GetOrigBsrTimerStartRat(VOS_VOID)
{
    return NAS_MSCC_GetSysAcqCtrlInfoAddr()->enOrigBsrTimerStartRat;
}



VOS_VOID NAS_MSCC_InitMsCfgInfo(
    NAS_MSCC_MS_CFG_INFO_STRU          *pstMsCfgInfo
)
{
    /* Init the Custom Cfg Info */
    NAS_MSCC_InitCustomCfgInfo(&(pstMsCfgInfo->stCustomCfgInfo));

    /* Init the Ms Sys Cfg Info */
    NAS_MSCC_InitMsSysCfgInfo(&(pstMsCfgInfo->stMsSysCfgInfo));

    return;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_InitCustomCfgInfo
Description     :   The function is used to init the Custom Cfg Info
Input parameters:   Pointer to Custom Cfg Info global variable.
Output parameters:  None
Return Value    :   None

Modify History:
    1)  Date    :   2015-4-14
        Author  :   a00295761
        Modify content :    Create
    2)  Date    :   2015-12-10
        Author  :   w00176964
        Modify content : CL_MUTIMODE_OPTIMIZE调整
*****************************************************************************/

VOS_VOID NAS_MSCC_InitCustomCfgInfo(
    NAS_MSCC_CUSTOM_CONFIG_STRU        *pstCustomCfgInfo
)
{
    /* Init the platform RAT Capability structure */
    NAS_MSCC_InitPlatformRatCapInfo(&(pstCustomCfgInfo->stPlatformRatCap));

    /* Init the IMS Cfg Info */
    NAS_MSCC_InitImsCfgInfo(&(pstCustomCfgInfo->stImsCfgInfo));

    /* Init the MMSS Cfg Info */
    NAS_MSCC_InitMmssCfgInfo(&(pstCustomCfgInfo->stMmssNvimCfgInfo));

    NAS_MSCC_Init1xServiceClSysAcqStrategyInfo(&pstCustomCfgInfo->st1xSrvClSysAcqStrategy);

    return;
}




VOS_VOID NAS_MSCC_InitMsSysCfgInfo(
    NAS_MSCC_MS_SYS_CFG_INFO_STRU      *pstMsSysCfgInfo
)
{
    VOS_UINT32                          i;

    PS_MEM_SET(&(pstMsSysCfgInfo->stRatPrio), 0x00, sizeof(NAS_MSCC_PIF_RAT_PRIO_STRU));

    /* Initializing the Rat Mode List to VOS_RATMODE_BUTT */
    for (i = 0; i < NAS_MSCC_PIF_MAX_RAT_NUM; i++ )
    {
        pstMsSysCfgInfo->stRatPrio.aucRatPrio[i] = NAS_MSCC_PIF_NET_RAT_TYPE_BUTT;

    }

    return;
}




VOS_VOID NAS_MSCC_InitPlatformRatCapInfo(
    NAS_MSCC_PLATFORM_RAT_CAP_STRU     *pstPlatformRatCap
)
{
    VOS_UINT32                          i;

    PS_MEM_SET(pstPlatformRatCap, 0x00, sizeof(NAS_MSCC_PLATFORM_RAT_CAP_STRU));

    /* Initializing the Rat Mode List to VOS_RATMODE_BUTT */
    for (i = 0; i < NAS_MSCC_PLATFORM_MAX_RAT_NUM; i++ )
    {
        pstPlatformRatCap->aenRatList[i] = VOS_RATMODE_BUTT;

    }

    return;
}




VOS_VOID NAS_MSCC_InitImsCfgInfo(
    NAS_MSCC_IMS_CONFIG_PARA_STRU      *pstImsCfgInfo
)
{
    /* Init the IMS RAT Support */
    PS_MEM_SET(&(pstImsCfgInfo->stImsRatSupport), 0, sizeof(NAS_MSCC_IMS_RAT_SUPPORT_STRU));

    pstImsCfgInfo->stImsRatSupport.ucGsmImsSupportFlag   = VOS_FALSE;
    pstImsCfgInfo->stImsRatSupport.ucUtranImsSupportFlag = VOS_FALSE;
    pstImsCfgInfo->stImsRatSupport.ucLteImsSupportFlag   = VOS_FALSE;
    pstImsCfgInfo->stImsRatSupport.ucGsmEmsSupportFlag   = VOS_FALSE;
    pstImsCfgInfo->stImsRatSupport.ucUtranEmsSupportFlag = VOS_FALSE;
    pstImsCfgInfo->stImsRatSupport.ucLteEmsSupportFlag   = VOS_FALSE;

    /* Init the IMS VOICE Domain */
    pstImsCfgInfo->enVoiceDomain = NAS_MSCC_VOICE_DOMAIN_CS_ONLY;

    /* Init the IMS Voice Avail TImer length to default value */
    pstImsCfgInfo->ulWaitImsVoiceAvailTimerLen = TI_NAS_MSCC_WAIT_IMSA_IMS_VOICE_AVAIL_IND_LEN;

    return;
}




VOS_VOID NAS_MSCC_InitMmssCfgInfo(
    NAS_MSCC_MMSS_CFG_INFO_STRU        *pstMmssCfgInfo
)
{
    PS_MEM_SET(pstMmssCfgInfo, 0x00, sizeof(NAS_MSCC_MMSS_CFG_INFO_STRU));

    /* Initialize the control flag of MSCC Reacquire LTE after receiving HSD Sync Ind to FALSE */
    pstMmssCfgInfo->stMmssSysAcqCfg.ucReAcqLteOnHrpdSyncIndFlag = VOS_FALSE;

    /* Initialize the CDMA 1x Location Info as preferred */
    pstMmssCfgInfo->stMmssSysAcqCfg.ucIs1xLocInfoPrefThanLte = VOS_TRUE;

    /* INit the System Acquire Timer Config */
    NAS_MSCC_InitSysAcqTimerCfgInfo(&(pstMmssCfgInfo->stMmssSysAcqCfg.stSysAcqTimerCfg));

    /* Init the Last Location Info */
    NAS_MSCC_InitMmssLastLocationInfo(&(pstMmssCfgInfo->stMmssLastLocInfo));

    return;
}




VOS_VOID NAS_MSCC_InitMmssLastLocationInfo(
    NAS_MSCC_MMSS_LOCATION_INFO_STRU   *pstMmssLastLocationInfo
)
{
    /* Initialize the Location info used in Switch On flag to FALSE and Sys Acq mode as GUL */
    pstMmssLastLocationInfo->ucIsLocInfoUsedInSwitchOn = VOS_FALSE;
    pstMmssLastLocationInfo->enSysAcqMode              = NAS_MSCC_LC_RAT_COMBINED_GUL;

    /* Initialize the Location Info Global variable */
    pstMmssLastLocationInfo->ucCdma1xActiveFlag     = VOS_FALSE;
    pstMmssLastLocationInfo->ucLteActiveFlag        = VOS_FALSE;

    /* Initialize the 1x Location Info */
    pstMmssLastLocationInfo->st1xLocationInfo.ulMcc = NAS_MSCC_INVALID_MCC;
    pstMmssLastLocationInfo->st1xLocationInfo.ulMnc = NAS_MSCC_INVALID_MNC;
    pstMmssLastLocationInfo->st1xLocationInfo.usSid = NAS_MSCC_WILDCARD_SID;
    pstMmssLastLocationInfo->st1xLocationInfo.usNid = NAS_MSCC_WILDCARD_NID;

    /* Initialize the LTE location info */
    pstMmssLastLocationInfo->stLteLocationInfo.ulMcc = NAS_MSCC_INVALID_MCC;
    pstMmssLastLocationInfo->stLteLocationInfo.ulMnc = NAS_MSCC_INVALID_MNC;

    return;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_InitSysAcqTimerCfgInfo
Description     :   The function is used to init the Sys Acq Timer cfg global variable.
Input parameters:   Pointer to Sys Acq Timer cfg  global variable.
Output parameters:  None
Return Value    :   None

Modify History:
    1)  Date    :   2015-4-14
        Author  :   a00295761
        Modify content :    Create

    2) Date     : 2016-01-14
       Author   : W00176964
       Modify   : DTS2016011505496:增加对原始系统不在MSPL表进行BSR流程,定时器时长的NV控制

    3)  Date    :   2016-1-14
        Author  :   w00176964
        Modify content : DTS2016010704615:CCF05006用例(1进入dormant态,需要在BSR定时器超时后重选到
                         LTE上)不通过,需要修改NV2015中BSR的默认值才能通过用例
*****************************************************************************/

VOS_VOID NAS_MSCC_InitSysAcqTimerCfgInfo(
    NAS_MSCC_SYSACQ_TIMER_CFG_STRU     *pstSysAcqTimerCfg
)
{
    /* 参考标杆做法,BSR的时长默认取NV中的,不从卡中取,保证CCF(11102、11101、05006)用例通过 */
    pstSysAcqTimerCfg->ucIsBsrTimerNvimActiveFlag            = VOS_TRUE;

    /* Initialize the Timer Length Structure with default values */
    pstSysAcqTimerCfg->ulAvailableTimerCountFirstSearch     = TI_NAS_MSCC_AVAILABLE_TIMER_COUNT_FIRST_SEARCH;
    pstSysAcqTimerCfg->ulAvailableTimerLengthFirstSearch    = TI_NAS_MSCC_AVAILABLE_TIMER_FIRST_SEARCH_LEN;
    pstSysAcqTimerCfg->ulAvailableTimerLengthDeepSearch     = TI_NAS_MSCC_AVAILABLE_TIMER_DEEP_SEARCH_LEN;
    pstSysAcqTimerCfg->ulBsrTimerLen                        = TI_NAS_MSCC_BSR_TIMER_LEN;
    pstSysAcqTimerCfg->ulScanTimerLen                       = TI_NAS_MSCC_SCAN_TIMER_LEN;
    pstSysAcqTimerCfg->ulSleepTimerLen                      = TI_NAS_MSCC_SLEEP_TIMER_LEN;

    pstSysAcqTimerCfg->ulBsrTimerLenWithNoMatchedMsplRec    = TI_NAS_MSCC_DEFAULT_BSR_TIMER_LEN_WITH_UNMATCHED_MSPL_REC;

    return;
}




VOS_VOID NAS_MSCC_InitPowerSaveCtrlInfo(
    NAS_MSCC_POWER_SAVE_CTRL_CTX_STRU  *pstPowerSaveCtrlInfo
)
{
    PS_MEM_SET(pstPowerSaveCtrlInfo, 0x00, sizeof(NAS_MSCC_POWER_SAVE_CTRL_CTX_STRU));

    pstPowerSaveCtrlInfo->uc1xActiveFlg         = VOS_FALSE;
    pstPowerSaveCtrlInfo->ucHrpdActiveFlg       = VOS_FALSE;
    pstPowerSaveCtrlInfo->uc3gppActiveFlg       = VOS_FALSE;
    pstPowerSaveCtrlInfo->ucPowerSaveReplyFlg   = VOS_FALSE;

    return;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_InitSysAcqCtrlInfo
Description     :   The function is used to init the System Acquire Context global variable
Input parameters:   Pointer to Sys Acq Ctrl Info  global variable.
Output parameters:  None
Return Value    :   None

Modify History:
    1)  Date    :   2015-4-28
        Author  :   t00323010
        Modify content :    Create
    2)  Date    :   2015-9-19
        Author  :   y00346957
        Modify content :    add for DTS2015070910885
      3.日    期   : 2016年1月6日
        作    者   : w00242748
        修改内容   : DTS2015072705348:进入紧急呼回呼模式后，挂起HRPD和LTE；退出紧急呼
                     回呼模式后，再进行搜网，紧急呼回呼模式下，不进行其他任何形式搜网；
*****************************************************************************/

VOS_VOID NAS_MSCC_InitSysAcqCtrlInfo(
    NAS_MSCC_SYS_ACQ_CTRL_CTX_STRU     *pstSysAcqCtrlInfo
)
{
    pstSysAcqCtrlInfo->enOrigBsrTimerStartRat   = VOS_RATMODE_BUTT;
    pstSysAcqCtrlInfo->ulCurrBsrTimerLen        = 0;

    pstSysAcqCtrlInfo->ucSysAcqMoCallFlag = VOS_FALSE;
    pstSysAcqCtrlInfo->enCur1xServiceSysAcqPhaseNum  = NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE;

    /* 默认LTE允许搜索,待收到1X位置信息后更新 */
    pstSysAcqCtrlInfo->ucAllowSrchLteFlg        = VOS_TRUE;

    pstSysAcqCtrlInfo->ucIsEmcCallExist         = VOS_FALSE;
    pstSysAcqCtrlInfo->ulCallBackEnableFlg      = VOS_FALSE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_Set1xSysAcqMoCallFlag
Description     :   The function is used to set ucSysAcqMoCallFlag
Input parameters: VOS_UINT8                           ucFlg
Output parameters:  None.
Return Value    :   None
Modify History:
    1)  Date    :   2015-07-09
        Author  :   y00314741
        Modify content :    Create
    2)  Date    :   2015-12-10
        Author  :   w00176964
        Modify content :CL_MUTIMODE_OPTIMIZE调整
*****************************************************************************/
VOS_VOID  NAS_MSCC_Set1xSysAcqMoCallFlag(
    VOS_UINT8                           ucFlg
)
{
    NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.ucSysAcqMoCallFlag = ucFlg;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_Get1xSysAcqMoCallFlags
Description     :   The function is used to get ucSysAcqMoCallFlag
Input parameters:   None
Output parameters:  None.
Return Value    :
Modify History:
    1)  Date    :   2015-07-09
        Author  :   y00314741
        Modify content :    Create
    2)  Date    :   2015-12-10
        Author  :   w00176964
        Modify content :CL_MUTIMODE_OPTIMIZE调整
*****************************************************************************/
VOS_UINT8  NAS_MSCC_Get1xSysAcqMoCallFlag(VOS_VOID)
{
    return NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.ucSysAcqMoCallFlag;
}

VOS_UINT8  NAS_MSCC_GetAllowSrchLteFlg(VOS_VOID)
{
    return NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.ucAllowSrchLteFlg;
}


VOS_VOID NAS_MSCC_SetAllowSrchLteFlg(
    VOS_UINT8                           ucAllowSrchLteFlg
)
{
    NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.ucAllowSrchLteFlg = ucAllowSrchLteFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_InitMntnInfo
 功能描述  : The function is used to init the mntn Context global variableS
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_InitMntnInfo(
    NAS_MSCC_MNTN_CTX_STRU            *pstMntnInfo
)
{
    PS_MEM_SET(pstMntnInfo, 0x00, sizeof(NAS_MSCC_MNTN_CTX_STRU));
    return;
}



/*****************************************************************************
函 数 名  : NAS_MSCC_AddLogMsgState
功能描述  : 增加stLogMsgState
输入参数  : usSendPid, usMsgName,usReceivePid
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015年7月2日
  作    者   : y00322978
  修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_AddLogMsgState(
    VOS_UINT32                          ulSendPid,
    VOS_UINT32                          ulReceivePid,
    VOS_UINT16                          usMsgName
)
{
    NAS_MSCC_LOG_MSG_STATUS_STRU       *pstLogMsgState;
    VOS_UINT8                           ucIndex;

    pstLogMsgState = &(NAS_MSCC_GetMsccCtxAddr()->stMntnInfo.stLogMsgState);

    pstLogMsgState->ucLatestIndex = (pstLogMsgState->ucLatestIndex + 1) % NAS_MSCC_MAX_LOG_MSG_STATE_NUM;

    ucIndex                       = pstLogMsgState->ucLatestIndex;

    PS_MEM_SET(&(pstLogMsgState->stMsgState[ucIndex]), 0, sizeof(NAS_MSCC_MSG_STATE_STRU));

    pstLogMsgState->stMsgState[ucIndex].ulReceiveTime = VOS_GetTick();
    pstLogMsgState->stMsgState[ucIndex].usSendPid     = (VOS_UINT16)ulSendPid;
    pstLogMsgState->stMsgState[ucIndex].usReceivePid  = (VOS_UINT16)ulReceivePid;
    pstLogMsgState->stMsgState[ucIndex].ucMsccFsmId   = (VOS_UINT8)NAS_MSCC_GetCurrFsmId();
    pstLogMsgState->stMsgState[ucIndex].ucMsccState   = (VOS_UINT8)NAS_MSCC_GetFsmTopState();
    pstLogMsgState->stMsgState[ucIndex].usMsgName     = usMsgName;

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MSCC_UpdateExitTime
 功能描述  : 更新消息退出的时间
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_UpdateMsgExitTime( VOS_VOID )
{
    NAS_MSCC_LOG_MSG_STATUS_STRU       *pstLogMsgState;
    VOS_UINT8                           ucIndex;

    pstLogMsgState = &(NAS_MSCC_GetMsccCtxAddr()->stMntnInfo.stLogMsgState);
    ucIndex = pstLogMsgState->ucLatestIndex;

    pstLogMsgState->stMsgState[ucIndex].ulExitTime = VOS_GetTick();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_LogMsgInfo
 功能描述  : 判断消息是否是定时器发出的，如果是就打印定时器信息，否则打印消
             息信息
 输入参数  : MSG_HEADER_STRU
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : y00322978
    修改内容   : 新生成函数
  2.日    期   : 2016年01月23日
    作    者   : l00324781
    修改内容   : LOG_MSG_OPTIMIZE 修改
*****************************************************************************/
VOS_VOID NAS_MSCC_LogMsgInfo(
    MSG_HEADER_STRU                    *pstMsgHeader
)
{
    VOS_UINT32                          ulSenderPid;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulRet;

    /* 对MSCC模块收到的消息，判断是否在忽略列表中，如果在，不进行记录 */
    ulRet = NAS_MSCC_MNTN_IsNeedDiscardForRcvMsg(pstMsgHeader->ulSenderPid,
                                                 pstMsgHeader->ulReceiverPid,
                                                 pstMsgHeader->ulMsgName);
    if (VOS_TRUE == ulRet)
    {
        return;
    }
    /* 对MSCC模块发送的消息，判断是否在忽略列表中，如果在，不进行记录 */
    ulRet = NAS_MSCC_MNTN_IsNeedDiscardForSndMsg(pstMsgHeader->ulSenderPid,
                                                 pstMsgHeader->ulReceiverPid,
                                                 pstMsgHeader->ulMsgName);
    if (VOS_TRUE == ulRet)
    {
        return;
    }

    /* 判断发送id是否是定时器 */
    if (VOS_PID_TIMER == pstMsgHeader->ulSenderPid)
    {
        ulSenderPid      =    ((REL_TIMER_MSG*)pstMsgHeader)->ulSenderPid;
        ulReceiverPid    =    ((REL_TIMER_MSG*)pstMsgHeader)->ulReceiverPid;
        ulMsgName        =    ((REL_TIMER_MSG*)pstMsgHeader)->ulName;
    }
    else
    {
        ulSenderPid      =    pstMsgHeader->ulSenderPid;
        ulReceiverPid    =    pstMsgHeader->ulReceiverPid;
        ulMsgName        =    pstMsgHeader->ulMsgName;
    }

    /* 打印消息 */
    NAS_MSCC_AddLogMsgState(ulSenderPid, ulReceiverPid, (VOS_UINT16)ulMsgName);

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MSCC_IsCLModeSupportedInRatList
 功能描述  : 判断目标接入技术是否支持CL模式
 输入参数  : NAS_MSCC_PIF_RAT_PRIO_STRU         *pstRatPrioList
 输出参数  : 无
 返 回 值  : VOS_UINT32
             VOS_TRUE  表示支持
             VOS_FASLE 表示不支持
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月21日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_IsCLModeSupportedInRatList(
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstRatPrioList
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < (VOS_UINT32)pstRatPrioList->ucRatNum; i++ )
    {
        if ( (NAS_MSCC_PIF_NET_RAT_TYPE_1X == pstRatPrioList->aucRatPrio[i])
          || (NAS_MSCC_PIF_NET_RAT_TYPE_HRPD == pstRatPrioList->aucRatPrio[i]) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_Init1xServiceClSysAcqStrategyInfo
 功能描述  : 初始化1x有服务时CL系统捕获策略NV信息
 输入参数  : NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_STRATEGY_STRU
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月11日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2016年1月14日
    作    者   : w00176964
    修改内容   : DTS2016010704615:修改NV默认值保证CCF用例通过
*****************************************************************************/
VOS_VOID NAS_MSCC_Init1xServiceClSysAcqStrategyInfo(
    NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_STRATEGY_STRU    *pstSysAcqStrategy
)
{
    pstSysAcqStrategy->stPhaseOnePatternCfg.ucLteFullBandSrchNum = NAS_MSCC_DEFAULT_1X_SERVICE_PHASE_ONE_FULL_BAND_SRCH_NUM;
    pstSysAcqStrategy->stPhaseOnePatternCfg.ucLteHistorySrchNum  = NAS_MSCC_DEFAULT_1X_SERVICE_PHASE_ONE_HISTORY_SRCH_NUM;
    pstSysAcqStrategy->stPhaseOnePatternCfg.usSleepTimeLen       = TI_NAS_MSCC_DEFAULT_1X_SERVICE_AVAILABLE_TIMER_PHASE_ONE_SLEEP_TIMER_LEN;
    pstSysAcqStrategy->stPhaseOnePatternCfg.usTotalTimeLen       = TI_NAS_MSCC_DEFAULT_1X_SERVICE_AVAILABLE_TIMER_PHASE_ONE_TOTAL_TIMER_LEN;

    pstSysAcqStrategy->stPhaseTwoPatternCfg.ucLteFullBandSrchNum = NAS_MSCC_DEFAULT_1X_SERVICE_PHASE_TWO_FULL_BAND_SRCH_NUM;
    pstSysAcqStrategy->stPhaseTwoPatternCfg.ucLteHistorySrchNum  = NAS_MSCC_DEFAULT_1X_SERVICE_PHASE_TWO_HISTORY_SRCH_NUM;
    pstSysAcqStrategy->stPhaseTwoPatternCfg.usSleepTimeLen       = TI_NAS_MSCC_DEFAULT_1X_SERVICE_AVAILABLE_TIMER_PHASE_TWO_SLEEP_TIMER_LEN;
    pstSysAcqStrategy->stPhaseTwoPatternCfg.usTotalTimeLen       = 0;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_Get1xServiceClSysAcqPatternONeCfgAddr
 功能描述  : 获取1x有服务时CL系统捕获策略阶段1NV信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月11日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU* NAS_MSCC_Get1xServiceClSysAcqPatternOneCfgAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo.stCustomCfgInfo.st1xSrvClSysAcqStrategy.stPhaseOnePatternCfg);
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_Get1xServiceClSysAcqPatternTwoCfgAddr
 功能描述  : 获取1x有服务时CL系统捕获策略阶段2NV信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月11日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU* NAS_MSCC_Get1xServiceClSysAcqPatternTwoCfgAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo.stCustomCfgInfo.st1xSrvClSysAcqStrategy.stPhaseTwoPatternCfg);
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_GetCur1xServiceSysAcqPhaseNum
 功能描述  : 获取1x有服务时CL系统捕获当前处于哪个阶段
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月11日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ENUM_UINT8 NAS_MSCC_GetCur1xServiceSysAcqPhaseNum(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.enCur1xServiceSysAcqPhaseNum);
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SetCur1xServiceSysAcqPhaseNum
 功能描述  : 设置1x有服务时CL系统捕获当前处于哪个阶段
 输入参数  : NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ENUM_UINT8
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月11日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_SetCur1xServiceSysAcqPhaseNum(
    NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ENUM_UINT8  enPhase
)
{
    (NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.enCur1xServiceSysAcqPhaseNum) = enPhase;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_ResetCur1xServiceSysAcqPhaseNum
 功能描述  : RESET 1x有服务时CL系统捕获阶段
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月11日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_ResetCur1xServiceSysAcqPhaseNum(VOS_VOID)
{
    (NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.enCur1xServiceSysAcqPhaseNum) = NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_AddCur1xServiceSysAcqPhaseNum
 功能描述  : add 1x有服务时CL系统捕获阶段
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月11日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_AddCur1xServiceSysAcqPhaseNum(VOS_VOID)
{
    (NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.enCur1xServiceSysAcqPhaseNum)++;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_GetCur1xServiceLteFullBandSrchCount_L1Main
 功能描述  : 获取当前1x有服务时available定时器超时触发的LTE全频搜索次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月11日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MSCC_GetCur1xServiceLteFullBandSrchCount_L1Main(VOS_VOID)
{
    if (NAS_MSCC_FSM_L1_MAIN != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetCur1xServiceLteFullBandSrchCount_L1Main,ERROR:FsmId Error");
    }

    return NAS_MSCC_GetCurFsmAddr()->unFsmCtx.stL1MainCtx.st1xServiceAvailableTimerCtx.ucCurLteFullBandSrchCount;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_ResetCur1xServiceLteFullBandSrchCount_L1Main
 功能描述  : reset当前1x有服务时available定时器超时触发的lte全频搜索次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月11日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_ResetCur1xServiceLteFullBandSrchCount_L1Main(VOS_VOID)
{
    if (NAS_MSCC_FSM_L1_MAIN != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ResetCur1xServiceLteFullBandSrchCount_L1Main,ERROR:FsmId Error");
    }

    (NAS_MSCC_GetCurFsmAddr()->unFsmCtx.stL1MainCtx.st1xServiceAvailableTimerCtx.ucCurLteFullBandSrchCount) = 0;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_AddCur1xServiceLteFullBandSrchCount_L1Main
 功能描述  : 递增当前1x有服务时available定时器超时触发的全频搜索次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月11日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_AddCur1xServiceLteFullBandSrchCount_L1Main(VOS_VOID)
{
    if (NAS_MSCC_FSM_L1_MAIN != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_AddCur1xServiceLteFullBandSrchCount_L1Main,ERROR:FsmId Error");
    }

    (NAS_MSCC_GetCurFsmAddr()->unFsmCtx.stL1MainCtx.st1xServiceAvailableTimerCtx.ucCurLteFullBandSrchCount)++;
}




/*****************************************************************************
 函 数 名  : NAS_MSCC_GetCur1xServiceLteHistorySrchCount_L1Main
 功能描述  : 获取当前1x有服务时available定时器超时触发的历史频搜索次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月11日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MSCC_GetCur1xServiceLteHistorySrchCount_L1Main(VOS_VOID)
{
    if (NAS_MSCC_FSM_L1_MAIN != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetCur1xServiceLteHistorySrchCount_L1Main,ERROR:FsmId Error");
    }

    return NAS_MSCC_GetCurFsmAddr()->unFsmCtx.stL1MainCtx.st1xServiceAvailableTimerCtx.ucCurLteHistorySrchCount;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_ResetCur1xServiceLteHistorySrchCount_L1Main
 功能描述  : reset当前1x有服务时available定时器超时触发的历史频点搜索次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月11日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_ResetCur1xServiceLteHistorySrchCount_L1Main(VOS_VOID)
{
    if (NAS_MSCC_FSM_L1_MAIN != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ResetCur1xServiceLteHistorySrchCount_L1Main,ERROR:FsmId Error");
    }

    (NAS_MSCC_GetCurFsmAddr()->unFsmCtx.stL1MainCtx.st1xServiceAvailableTimerCtx.ucCurLteHistorySrchCount) = 0;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_AddCur1xServiceLteHistorySrchCount_L1Main
 功能描述  : 递增当前1x有服务时available定时器超时触发的历史频点搜索次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月11日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_AddCur1xServiceLteHistorySrchCount_L1Main(VOS_VOID)
{
    if (NAS_MSCC_FSM_L1_MAIN != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_AddCur1xServiceLteHistorySrchCount_L1Main,ERROR:FsmId Error");
    }

    (NAS_MSCC_GetCurFsmAddr()->unFsmCtx.stL1MainCtx.st1xServiceAvailableTimerCtx.ucCurLteHistorySrchCount)++;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_GetNext1xServiceAvailableTimerLength_L1Main
 功能描述  : 获取下次1x有服务时available定时器的启动时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月11日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/

VOS_UINT32  NAS_MSCC_GetNext1xServiceAvailableTimerLength_L1Main(
    NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ENUM_UINT8  enPhaseNum
)
{
    VOS_UINT32                          ulTimerLen;

    /* 下个阶段为1阶段,取一阶段的sleep时长，否则取2阶段,因为目前只控制两个阶段 */
    if (NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE == enPhaseNum)
    {
        ulTimerLen =  (NAS_MSCC_Get1xServiceClSysAcqPatternOneCfgAddr()->usSleepTimeLen) * NAS_MSCC_THOUSAND_MILLISECOND_UNIT;
    }
    else
    {
        ulTimerLen =  (NAS_MSCC_Get1xServiceClSysAcqPatternTwoCfgAddr()->usSleepTimeLen) * NAS_MSCC_THOUSAND_MILLISECOND_UNIT;
    }

    return ulTimerLen;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_IsNeedPerfromLteFullBandSrchWith1xServiceExist_L1Main
 功能描述  : 是否需要执行Lte全频搜在1x服务存在时
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要执行Lte全频搜在1x服务存在时
             VOS_FALSE:不需要执行Lte全频搜在1x服务存在时
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月11日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2016年1月14日
    作    者   : w00176964
    修改内容   : DTS2016011505664:搜索策略进行调整,全频搜L穿插历史搜L
*****************************************************************************/

VOS_UINT32  NAS_MSCC_IsNeedPerfromLteFullBandSrchWith1xServiceExist_L1Main(VOS_VOID)
{
    VOS_UINT8                           ucFullBandSrchNum;
    VOS_UINT8                           ucCurFullBandSrchCount;
    VOS_UINT8                           ucCurHistorySrchCount;
    VOS_UINT8                           ucHistorySrchNum;

    if (NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE == NAS_MSCC_GetCur1xServiceSysAcqPhaseNum())
    {
        ucHistorySrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternOneCfgAddr()->ucLteHistorySrchNum;

        ucFullBandSrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternOneCfgAddr()->ucLteFullBandSrchNum;
    }
    else
    {
        ucHistorySrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternTwoCfgAddr()->ucLteHistorySrchNum;

        ucFullBandSrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternTwoCfgAddr()->ucLteFullBandSrchNum;
    }

    /* 历史搜次数为0但全频搜次数不为0,一直进行全频搜 */
    if ((0 == ucHistorySrchNum)
     && (0 != ucFullBandSrchNum))
    {
        return VOS_TRUE;
    }

    ucCurFullBandSrchCount = NAS_MSCC_GetCur1xServiceLteFullBandSrchCount_L1Main();
    ucCurHistorySrchCount  = NAS_MSCC_GetCur1xServiceLteHistorySrchCount_L1Main();

    /* 当前搜索全频段次数小于NV中设置的最大值且历史搜次数达到最大值时,需要继续全频段搜索 */
    if ((ucCurFullBandSrchCount < ucFullBandSrchNum)
     && (ucCurHistorySrchCount  == ucHistorySrchNum))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_IsNeedPerfromLteHistorySrchWith1xServiceExist_L1Main
 功能描述  : 是否需要执行Lte历史频点搜索在1x服务存在时
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要执行Lte历史频点搜索在1x服务存在时
             VOS_FALSE:不需要执行Lte历史频点搜索在1x服务存在时
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月11日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/

VOS_UINT32  NAS_MSCC_IsNeedPerfromLteHistorySrchWith1xServiceExist_L1Main(VOS_VOID)
{
    VOS_UINT8                           ucHistorySrchNum;
    VOS_UINT8                           ucCurHistorySrchCount;
    VOS_UINT8                           ucFullBandSrchNum;

    if (NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE == NAS_MSCC_GetCur1xServiceSysAcqPhaseNum())
    {
        ucHistorySrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternOneCfgAddr()->ucLteHistorySrchNum;

        ucFullBandSrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternOneCfgAddr()->ucLteFullBandSrchNum;
    }
    else
    {
        ucHistorySrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternTwoCfgAddr()->ucLteHistorySrchNum;

        ucFullBandSrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternTwoCfgAddr()->ucLteFullBandSrchNum;
    }

    /* 历史搜次数不为0但全频搜次数为0,一直进行历史搜 */
    if ((0 == ucFullBandSrchNum)
     && (0 != ucHistorySrchNum))
    {
        return VOS_TRUE;
    }

    ucCurHistorySrchCount = NAS_MSCC_GetCur1xServiceLteHistorySrchCount_L1Main();

    /* 当前搜索历史频点次数小于NV中设置的最大值,需要继续历史频点搜索 */
    if (ucCurHistorySrchCount < ucHistorySrchNum)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_GetNextAvailableTimerLength_L1Main
 功能描述  : 获取下次available定时器的启动时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月11日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/

VOS_UINT32  NAS_MSCC_GetNextAvailableTimerLength_L1Main(VOS_VOID)
{
    if (VOS_TRUE == NAS_MSCC_Is1xNormalService())
    {
        return NAS_MSCC_GetNext1xServiceAvailableTimerLength_L1Main(NAS_MSCC_GetCur1xServiceSysAcqPhaseNum());
    }

    return NAS_MSCC_GetNextOosAvailableTimerLength_L1Main();
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_Start1xServiceClSysAcqPhaseOneTotalTimer_L1Main
 功能描述  : 启动1x有服务时CL系统捕获阶段1总搜索时长定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月11日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID  NAS_MSCC_Start1xServiceClSysAcqPhaseOneTotalTimer_L1Main(VOS_VOID)
{
    VOS_UINT16                          usPhaseOneTotalTimerLen;
    VOS_UINT16                          usPhaseOneSleepTimerLen;

    /* 已经不处于阶段1,不需要启动 */
    if (NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE != NAS_MSCC_GetCur1xServiceSysAcqPhaseNum())
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_Start1xServiceClSysAcqPhaseOneTotalTimer_L1Main: not in phase one");

        return;
    }

    usPhaseOneTotalTimerLen = NAS_MSCC_Get1xServiceClSysAcqPatternOneCfgAddr()->usTotalTimeLen;
    usPhaseOneSleepTimerLen = NAS_MSCC_Get1xServiceClSysAcqPatternOneCfgAddr()->usSleepTimeLen;

    /* NV中配置总时长为0不启动 */
    if (0 == usPhaseOneTotalTimerLen)
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_Start1xServiceClSysAcqPhaseOneTotalTimer_L1Main: total timer len is zero");

        return;
    }

    /* NV中配置总时长小于sleep时长,不启动 */
    if (usPhaseOneTotalTimerLen < usPhaseOneSleepTimerLen)
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_Start1xServiceClSysAcqPhaseOneTotalTimer_L1Main: total timer len less than sleep timer len");

        return;
    }

    (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE_TOTAL_TIMER, usPhaseOneTotalTimerLen * NAS_MSCC_THOUSAND_MILLISECOND_UNIT );

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_Reset1xServiceClSysAcqRelatedInfo_L1Main
 功能描述  : reset 1x有服务时CL系统捕获相关信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月15日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID  NAS_MSCC_Reset1xServiceClSysAcqRelatedInfo_L1Main(VOS_VOID)
{
    NAS_MSCC_StopTimer(TI_NAS_MSCC_AVAILABLE_TIMER);

    NAS_MSCC_StopTimer(TI_NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE_TOTAL_TIMER);

    NAS_MSCC_ResetCur1xServiceLteHistorySrchCount_L1Main();

    NAS_MSCC_ResetCur1xServiceLteFullBandSrchCount_L1Main();

    NAS_MSCC_ResetCur1xServiceSysAcqPhaseNum();

    NAS_MSCC_ResetCurOosAvailableTimerStartCount_L1Main();

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MSCC_InitNoCardInitSearchLocInfo
 功能描述  : 无卡初搜位置信息内容初始化
 输入参数  : NAS_MSCC_NO_CARD_INIT_SEARCH_LOC_STRU         *pstNoCardInitSearchLocInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月10日
    作    者   : j00354216
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_InitNoCardInitSearchLocInfo(
    NAS_MSCC_NO_CARD_INIT_SEARCH_LOC_STRU                  *pstNoCardInitSearchLocInfo
)
{
    pstNoCardInitSearchLocInfo->stInitSearchGulLoc.ulMcc  = NAS_MSCC_INVALID_MCC;
    pstNoCardInitSearchLocInfo->stInitSearchGulLoc.ulMnc  = NAS_MSCC_INVALID_MNC;
    pstNoCardInitSearchLocInfo->stInitSearchCdmaLoc.lSid  = NAS_MSCC_INVALID_SID;
    pstNoCardInitSearchLocInfo->stInitSearchCdmaLoc.lNid  = NAS_MSCC_INVALID_NID;
    pstNoCardInitSearchLocInfo->stInitSearchCdmaLoc.ulMcc = NAS_MSCC_INVALID_MCC;
    pstNoCardInitSearchLocInfo->enInitSearchWaitType      = NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_BUTT;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_GetNoCardInitSearchLocInfoAddr
 功能描述  : 获取无卡初搜位置信息内容地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MSCC_NO_CARD_INIT_SEARCH_LOC_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月10日
    作    者   : j00354216
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MSCC_NO_CARD_INIT_SEARCH_LOC_STRU *NAS_MSCC_GetNoCardInitSearchLocInfoAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.stNoCardInitSearchLoc);
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_Update1xNoCardInitSearchLocInfo
 功能描述  : 更新1x无卡初搜位置信息内容
 输入参数  : VOS_INT32 lSid
             VOS_INT32 lNid
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月10日
    作    者   : j00354216
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_Update1xNoCardInitSearchLocInfo(
    VOS_INT32                           lSid,
    VOS_INT32                           lNid
)
{
    NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.stNoCardInitSearchLoc.stInitSearchCdmaLoc.lSid = lSid;
    NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.stNoCardInitSearchLoc.stInitSearchCdmaLoc.lNid = lNid;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_Update1xNoCardInitSearchLocMcc
 功能描述  : 更新1x无卡初搜位置信息的MCC值
 输入参数  : VOS_UINT32    ulMcc
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月10日
    作    者   : j00354216
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_Update1xNoCardInitSearchLocMcc(
    VOS_UINT32                          ulMcc
)
{
    NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.stNoCardInitSearchLoc.stInitSearchCdmaLoc.ulMcc = ulMcc;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_UpdateGulNoCardInitSearchLocInfo
 功能描述  : 更新Gul无卡初搜位置信息内容
 输入参数  : VOS_UINT32 ulMcc
             VOS_UINT32 ulMcc
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月10日
    作    者   : j00354216
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_UpdateGulNoCardInitSearchLocInfo(
    VOS_UINT32                          ulMcc,
    VOS_UINT32                          ulMnc
)
{
    NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.stNoCardInitSearchLoc.stInitSearchGulLoc.ulMcc = ulMcc;
    NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.stNoCardInitSearchLoc.stInitSearchGulLoc.ulMnc = ulMnc;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SetNoCardInitSearchWaitType
 功能描述  : 设置无卡初搜当前等待的初搜类型
 输入参数  : NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_ENUM_UINT32  enNoCardInitSearchWaitType
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月10日
    作    者   : j00354216
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SetNoCardInitSearchWaitType(
    NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_ENUM_UINT32      enNoCardInitSearchWaitType
)
{
    NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.stNoCardInitSearchLoc.enInitSearchWaitType = enNoCardInitSearchWaitType;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_GetNoCardInitSearchWaitType
 功能描述  : 获取无卡初搜当前等待的初搜类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_ENUM_UINT32  enNoCardInitSearchWaitType
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月10日
    作    者   : j00354216
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_ENUM_UINT32 NAS_MSCC_GetNoCardInitSearchWaitType(VOS_VOID)
{
    return NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.stNoCardInitSearchLoc.enInitSearchWaitType;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_ResetNoCardInitSearchInfo
 功能描述  : 重置无卡初搜当前等待的初搜类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月10日
    作    者   : j00354216
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_ResetNoCardInitSearchInfo(VOS_VOID)
{
    NAS_MSCC_NO_CARD_INIT_SEARCH_LOC_STRU                  *pstNoCardInitSearchLocInfo = VOS_NULL_PTR;

    pstNoCardInitSearchLocInfo = NAS_MSCC_GetNoCardInitSearchLocInfoAddr();

    NAS_MSCC_Update1xNoCardInitSearchLocMcc(NAS_MSCC_INVALID_MCC);

    NAS_MSCC_Update1xNoCardInitSearchLocInfo(NAS_MSCC_INVALID_SID,
                                             NAS_MSCC_INVALID_NID);

    NAS_MSCC_UpdateGulNoCardInitSearchLocInfo(NAS_MSCC_INVALID_MCC,
                                              NAS_MSCC_INVALID_MNC);
    /* 初搜位置信息已使用过，置标志位为TRUE */
    pstNoCardInitSearchLocInfo->ucIsLocInfoUsed = VOS_TRUE;

    return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



