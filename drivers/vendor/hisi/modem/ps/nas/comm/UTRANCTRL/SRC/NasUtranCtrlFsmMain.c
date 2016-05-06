/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasUtranCtrlFsmMain.c
  版 本 号   : 初稿
  作    者   : w00167002
  生成日期   : 2012年7月12日
  最近修改   :
  功能描述   : NasUtranCtrlFsmMain.C文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年7月12日
    作    者   : w00167002
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "NasComm.h"

#include "NasUtranCtrlCtx.h"
#include "NasUtranCtrlCommFunc.h"
#include "NasUtranCtrlFsmMain.h"
#include "Nasrrcinterface.h"
#include "NasUtranCtrlProcNvim.h"
#include "NasMmcTimerMgmt.h"
#include "NasMmlLib.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
#include "NasMmcComFunc.h"
#include "NVIM_Interface.h"
#include "NasMmcSndLmm.h"
#include "siappstk.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_FSM_MAIN_C

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)

#if defined (__PS_WIN32_RECUR__)

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_InitFsmDesc
 功能描述  : 根据FsmId取得PC工程中的相应状态机的地址
 输入参数  : VOS_UINT32                          ulPcRecurFsmId
 输出参数  : NAS_FSM_DESC_STRU                  *pstFsmDesc
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月16日
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_ReloadFsmDesc(
    NAS_UTRANCTRL_FSM_CTX_STRU         *pstFsmCtx,
    VOS_UINT32                          ulPcRecurFsmId
)
{
    switch ( ulPcRecurFsmId )
    {
        case NAS_UTRANCTRL_FSM_MAIN:
            pstFsmCtx->pstFsmDesc       = NAS_UTRANCTRL_GetMainFsmDescAddr();
            break;

        case NAS_UTRANCTRL_FSM_SWITCH_ON:
            pstFsmCtx->pstFsmDesc       = NAS_UTRANCTRL_GetSwitchOnFsmDescAddr();
            break;

        case NAS_UTRANCTRL_FSM_POWER_OFF:
            pstFsmCtx->pstFsmDesc       = NAS_UTRANCTRL_GetPowerOffFsmDescAddr();
            break;

        case NAS_UTRANCTRL_FSM_PLMN_SELECTION:
            pstFsmCtx->pstFsmDesc       = NAS_UTRANCTRL_GetPlmnSelectionFsmDescAddr();
            break;

        case NAS_UTRANCTRL_FSM_SYSCFG:
            pstFsmCtx->pstFsmDesc       = NAS_UTRANCTRL_GetSysCfgFsmDescAddr();
            break;

        case NAS_UTRANCTRL_FSM_MODE_CHANGE:
            pstFsmCtx->pstFsmDesc       = NAS_UTRANCTRL_GetModeChangeFsmDescAddr();
            break;

        default:
            break;
    }

}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RestoreContextData_Main
 功能描述  : 恢复UTRANCTRL全局变量。
 输入参数  : ulEventType:消息类型
              pstMsg:需要恢复的全局变量
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年08月16日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2013年6月4日
   作    者   : z00161729
   修改内容   : SVLTE 和usim接口调整修改

*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RestoreContextData_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_CTX_STRU                                  *pstUtranCtrlCtx;
    NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU                 *pstRcMsg;
    VOS_UINT32                                               ulExpectCount;
    VOS_UINT32                                               ulCount;
    VOS_UINT32                                               ulItemCount;
    VOS_UINT8                                               *pucDest;
    VOS_UINT8                                               *pucSrc;
    VOS_UINT32                                               ulDestLen;

    pstUtranCtrlCtx     = NAS_UTRANCTRL_GetUtranCtrlCtx();

    ulExpectCount = 0;
    ulCount       = 0;
    ulItemCount   = 0;
    ulExpectCount = sizeof(NAS_UTRANCTRL_CTX_STRU);

    /*注册状态机*/
    NAS_UTRANCTRL_RegFsm();

    pstRcMsg = (NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU *)pstMsg;
    pucSrc   = pstRcMsg->aucData;

    /* 解析总长度 */
    PS_MEM_CPY(&ulCount, pucSrc, sizeof(VOS_UINT32));
    pucSrc += sizeof(VOS_UINT32);

    if( ulExpectCount != ulCount )
    {
        return VOS_FALSE;
    }

    /* g_stNasUtranCtrlCtx目标地址 */
    pucDest     = (VOS_UINT8 *)pstUtranCtrlCtx;
    ulDestLen   = sizeof(NAS_UTRANCTRL_CTX_STRU);

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }

    pucSrc += (ulItemCount);

    NAS_UTRANCTRL_ReloadFsmDesc(NAS_UTRANCTRL_GetCurFsmAddr(), pstUtranCtrlCtx->stCurFsm.enFsmId);


    NAS_INFO_LOG(WUEPS_PID_MMC, "UTRANCTRL: NAS_UTRANCTRL_RestoreContextData_Main - data is restored.");

    return VOS_TRUE;
}

#endif  /* END OF #if defined (__PS_WIN32_RECUR__) */



/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvWasSysInfo_Main
 功能描述  : 收到系统消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月7日
   作    者   : s00217060
   修改内容   : for V7R1C50_GUTL_PhaseII新生成函数
 2.日    期   : 2012年8月14日
   作    者   : w00176964
   修改内容   : 模式写入NV修改
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvWasSysInfo_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enPreUtranMode;

    enPreUtranMode     = NAS_UTRANCTRL_GetPreUtranMode();

    /* 自动模式收到WAS消息,统一切换成FDD模式,写入NV中 */
    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO == NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        /* 更新当前的工作模式 */
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);
    }

    /* 模式不变不通知RRC */
    if (enPreUtranMode == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        /* 消息未被处理完成需继续进入MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 把当前UtranMode写到NV中 */
    NAS_UTRANCTRL_WriteUtranModeNvim(NAS_UTRANCTRL_UTRAN_MODE_FDD);

    /* 更新上次发给接入层的UtranMode */
    NAS_UTRANCTRL_SetPreUtranMode(NAS_UTRANCTRL_GetCurrUtranMode());

    /* 进入ModeChange状态机 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MODE_CHANGE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvGasSysInfo_Main
 功能描述  : 收到系统消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月7日
   作    者   : s00217060
   修改内容   : for V7R1C50_GUTL_PhaseII新生成函数
 2.日    期   : 2012年8月14日
   作    者   : w00176964
   修改内容   : 模式写入NV修改
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvGasSysInfo_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GRRMM_SYS_INFO_IND_ST              *pstGrrSysInfo;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enPreUtranMode;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;

    pstGrrSysInfo      = (GRRMM_SYS_INFO_IND_ST *)pstMsg;
    enPreUtranMode     = NAS_UTRANCTRL_GetPreUtranMode();

    /* 自动模式收到GAS消息，解析系统消息中的MCC，更新当前模式并写NV */
    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO == NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        /* 如果当前的MCC不在TD的PLMN LIST列表中，UTRAN MODE为FDD */
        if (VOS_FALSE == NAS_MML_IsMccInDestMccList(pstGrrSysInfo->PlmnId.ulMcc,
                                                NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                                NAS_UTRANCTRL_GetSpecTdMccList()))
        {
            enCurrUtranMode = NAS_UTRANCTRL_UTRAN_MODE_FDD;
        }
        else
        {
            enCurrUtranMode = NAS_UTRANCTRL_UTRAN_MODE_TDD;

            NAS_UTRANCTRL_SetSearchedSpecTdMccFlg(VOS_TRUE);
        }

        NAS_UTRANCTRL_SetCurrUtranMode(enCurrUtranMode);
    }

    /* 模式不变不通知RRC */
    if (enPreUtranMode == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        /* 消息未被处理完成需继续进入MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 把当前UtranMode写到NV中 */
    NAS_UTRANCTRL_WriteUtranModeNvim(NAS_UTRANCTRL_GetCurrUtranMode());

    /* 更新上次发给接入层的UtranMode */
    NAS_UTRANCTRL_SetPreUtranMode(NAS_UTRANCTRL_GetCurrUtranMode());

    /* 进入ModeChange状态机 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MODE_CHANGE);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTdSysInfo_Main
 功能描述  : 收到系统消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月7日
   作    者   : s00217060
   修改内容   : for V7R1C50_GUTL_PhaseII新生成函数
 2.日    期   : 2012年8月14日
   作    者   : w00176964
   修改内容   : 模式写入NV修改
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTdSysInfo_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enPreUtranMode;

    enPreUtranMode   = NAS_UTRANCTRL_GetPreUtranMode();

    /* 自动模式收到TDS消息，可能是FDD  模式切换成TDD模式,需要更新当前模式 */
    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO == NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);

        NAS_UTRANCTRL_SetSearchedSpecTdMccFlg(VOS_TRUE);
    }

    /* 模式不变不通知RRC */
    if (enPreUtranMode == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        /* 消息未被处理完成需继续处理 */
        return VOS_FALSE;
    }

    /* 把当前UtranMode写到NV中 */
    NAS_UTRANCTRL_WriteUtranModeNvim(NAS_UTRANCTRL_UTRAN_MODE_TDD);

    /* 更新上次发给接入层的UtranMode */
    NAS_UTRANCTRL_SetPreUtranMode(NAS_UTRANCTRL_GetCurrUtranMode());

    /* 进入ModeChange状态机 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MODE_CHANGE);

    return VOS_TRUE;
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvLmmSysInfo_Main
 功能描述  : 收到系统消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月7日
   作    者   : s00217060
   修改内容   : for V7R1C50_GUTL_PhaseII新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvLmmSysInfo_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SYS_INFO_IND_STRU          *pstLmmSysInfoMsg;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enPreUtranMode;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;
    MMC_LMM_PLMN_ID_STRU                stLmmPlmn;
    NAS_MML_PLMN_ID_STRU                stGUNasPlmn;

    pstLmmSysInfoMsg = (LMM_MMC_SYS_INFO_IND_STRU*)pstMsg;
    enPreUtranMode   = NAS_UTRANCTRL_GetPreUtranMode();
    stLmmPlmn        = (pstLmmSysInfoMsg->stLteSysInfo.stSpecPlmnIdList.astSuitPlmnList[0]);

    if (VOS_FALSE == NAS_MML_IsGULModeConfigured())
    {
        return VOS_FALSE;
    }

    /* 把LMM的PLMN转换成GU NAS的PLMN格式 */
    NAS_MMC_ConvertLmmPlmnToGUNasFormat(&stLmmPlmn,
                                        &stGUNasPlmn);

    /* 自动模式收到GAS消息，需要更新当前模式 */
    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO == NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        /* 如果当前的MCC不在TD的PLMN LIST列表中,UTRAN MODE为FDD */
        if (VOS_FALSE == NAS_MML_IsMccInDestMccList(stGUNasPlmn.ulMcc,
                                                    NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                                    NAS_UTRANCTRL_GetSpecTdMccList()))
        {
            enCurrUtranMode = NAS_UTRANCTRL_UTRAN_MODE_FDD;
        }
        else
        {
            enCurrUtranMode = NAS_UTRANCTRL_UTRAN_MODE_TDD;

            NAS_UTRANCTRL_SetSearchedSpecTdMccFlg(VOS_TRUE);
        }

        NAS_UTRANCTRL_SetCurrUtranMode(enCurrUtranMode);
    }

    /* 模式不变不通知RRC */
    if (enPreUtranMode == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        /* 消息未被处理完成需继续处理 */
        return VOS_FALSE;
    }

    /* 把当前UtranMode写到NV中 */
    NAS_UTRANCTRL_WriteUtranModeNvim(NAS_UTRANCTRL_GetCurrUtranMode());

    /* 更新上次发给接入层的UtranMode */
    NAS_UTRANCTRL_SetPreUtranMode(NAS_UTRANCTRL_GetCurrUtranMode());

    /* 进入ModeChange状态机 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MODE_CHANGE);

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvMmcGmmStartCnf_Main
 功能描述  : 收到开机请求消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月14日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年7月14日
   作    者   : w00176964
   修改内容   : GUTL PhaseII 开机时通知RRC当前的UTRAN MODE,记录发给RRC的PRE UTRAN MODE
 3.日    期   : 2012年10月13日
   作    者   : w00167002
   修改内容   : DTS2012101300714:开机读取HOME PLMN时候，在没有读取指示网络号
                 长度文件时6FAD时，默认按照网络号长度为3位，导致在网络号长度
                 为2时出错.
                 修改为在收到GMM的开机回复时候更新AUTO SWITCH 模式，此时网络
                 长度是确定的。
 4.日    期   : 2013年11月19日
   作    者   : w00167002
   修改内容   : DTS2013112006986:控制在3G TDD模式下是否需要开启SMC验证标记:中国移动拉萨网络设备在
                TD下不发起SMC流程。

*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcGmmStartCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity = VOS_NULL_PTR;
    VOS_UINT8                           ucSimPresentStatus;

    pstMsIdentity                       = NAS_MML_GetSimMsIdentity();
    ucSimPresentStatus                  = NAS_MML_GetSimPresentStatus();


    /* 开机读取 en_NV_Item_SMC_Ctrl_Flg NV项 */
    NAS_UTRANCTRL_ReadSmcCtrlFlgNvim();

    /* 开机读取 en_NV_Item_Utran_Mode_Auto_Switch NV项 */
    NAS_UTRANCTRL_ReadUtranModeAutoSwitchNvim();

    /* 开机读取 en_NV_Item_Current_Utran_Mode NV项 */
    NAS_UTRANCTRL_ReadUtranModeNvim();

    /* 根据IMSI及en_NV_Item_Utran_Mode_Auto_Switch NV项来更新当前的UTRAN切换模式 */
    NAS_UTRANCTRL_UpdateCurUtranSwitchMode( pstMsIdentity->aucImsi,
                                            ucSimPresentStatus,
                                            NAS_UTRANCTRL_GetUtranModeAutoSwtich() );

    /* 开机时会通知RRC当前的UTRAN MODE,此时记录下来,后续收到系统消息不再通知 */
    if (VOS_TRUE == NAS_MML_IsGULModeConfigured())
    {
        NAS_UTRANCTRL_SetPreUtranMode(NAS_UTRANCTRL_GetCurrUtranMode());
    }
    else
    {
        NAS_UTRANCTRL_SetPreUtranMode(NAS_UTRANCTRL_UTRAN_MODE_NULL);
    }

    /* 消息未被处理完成需继续处理 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvPlmnSearchReq_Main
 功能描述  : 收到开机搜网消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月25日
   作    者   : z00161729
   修改内容   : 开机搜网优化项目修改
 2.日    期   : 2/4/2015
   作    者   : w00176964
   修改内容   : CDMA Iteration 10 Modified

*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvPlmnSearchReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_PLMN_SEARCH_REQ_STRU      *pstMsccPlmnSrchReq;

    pstMsccPlmnSrchReq = (MSCC_MMC_PLMN_SEARCH_REQ_STRU *)pstMsg;

    if (NAS_MSCC_PIF_ACQ_REASON_POWER_UP == pstMsccPlmnSrchReq->enAcqReason)
    {
        NAS_UTRANCTRL_SetSwithOnPlmnSearchFlag(VOS_TRUE);
    }

    /* 消息未被处理完成需继续处理 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvMmaAcqReq_Main
 功能描述  : 收到ID_MMA_MMC_ACQ_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月25日
   作    者   : z00161729
   修改内容   : 开机搜网优化项目修改

*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMsccAcqReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_SetSwithOnPlmnSearchFlag(VOS_FALSE);

    /* 消息未被处理完成需继续处理 */
    return VOS_FALSE;
}



/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvPlmnSpecialReq_Main
 功能描述  : 收到开机指定搜网消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月24日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年11月25日
   作    者   : z00161729
   修改内容   : 开机搜网优化项目修改

*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvPlmnSpecialReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO == NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        NAS_UTRANCTRL_SetSearchedSpecTdMccFlg(VOS_FALSE);
    }

    NAS_UTRANCTRL_SetSwithOnPlmnSearchFlag(VOS_FALSE);

    /* 消息未被处理完成需继续处理 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvWasStartCnf_Main
 功能描述  : 收到was的开机回复消息
 输入参数  : ulEventType:消息类型
              pstMsg:RRMM_START_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月7日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvWasStartCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_START_CNF_STRU                *pstRrStartCnfMsg;

    pstRrStartCnfMsg = (RRMM_START_CNF_STRU *)pstMsg;

    /* 如果当前UTRANCTRL模的等开机回复时状态定时器不运行认为异常 */
    if ( NAS_MMC_TIMER_STATUS_RUNING != NAS_UTRANCTRL_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_WAS_START_CNF))
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvWasStartCnf_Main: Unexpected Plmnsrch msg!");

        /* 丢弃该异常消息 */
        return VOS_TRUE;
    }

    /* 停止MMC通过UTRANCTRL模块给UTRAN模发送开机消息时候起的定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_START_CNF);

    if (MMC_START_FAILURE == pstRrStartCnfMsg->ulResult)
    {
        /* 若UTRAN模块开机失败，则直接进MMC状态机进行处理 */
        return VOS_FALSE;
    }

    /* 切换到适配模块的开机状态机进行处理 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_SWITCH_ON);

    /* WAS的开机回复消息在适配模块的开机状态机进行处理  */
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTiWaitWasStartCnfExpired_Main
 功能描述  : 收到was的开机回复超时消息
 输入参数  : ulEventType:消息类型
              pstMsg:RRMM_START_CNF超时消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasStartCnfExpired_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 构建开机失败消息，进原MMC状态机进行处理 */
    RRMM_START_CNF_STRU                *pstTempMsg      = VOS_NULL_PTR;
    VOS_UINT32                          ulTempMsgEventType;

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasStartCnfExpired_Main: ENTERED");

    /* 申请内存 */
    pstTempMsg = (RRMM_START_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                               sizeof(RRMM_START_CNF_STRU));
    if( VOS_NULL_PTR == pstTempMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasStartCnfExpired_Main: Alloc memeory Error");
        return VOS_FALSE;
    }

    /* 构造开机回复失败消息 */
    NAS_UTRANCTRL_BuildRrMmStartCnfMsg(WUEPS_PID_WRR,
                                       WUEPS_PID_MMC,
                                       MMC_START_FAILURE,
                                       pstTempMsg);

    /* 取得当前构建消息的类型 */
    ulTempMsgEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstTempMsg );

    /* 将更改过的超时消息放到输出队列中 */
    NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(ulTempMsgEventType,
                                           (struct MsgCB *)pstTempMsg);

    /* 设置需要替换入口消息标记 */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* 释放申请的消息 */
    PS_MEM_FREE(WUEPS_PID_MMC, pstTempMsg);

    /* 当前消息进入后续MMC状态机处理 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTdStartCnf_Main
 功能描述  : 收到td的开机回复消息
 输入参数  : ulEventType:消息类型
              pstMsg:RRMM_START_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月7日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTdStartCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_START_CNF_STRU                *pstRrStartCnfMsg;

    pstRrStartCnfMsg = (RRMM_START_CNF_STRU *)pstMsg;

    /* 如果当前UTRANCTRL模的等开机回复时状态定时器不运行认为异常 */
    if ( NAS_MMC_TIMER_STATUS_RUNING != NAS_UTRANCTRL_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_TD_START_CNF))
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTdStartCnf_Main: Unexpected Plmnsrch msg!");

        /* 丢弃该异常消息 */
        return VOS_TRUE;
    }

    /* 停止MMC通过UTRANCTRL模块给UTRAN模发送开机消息时候起的定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_START_CNF);

    if (MMC_START_FAILURE == pstRrStartCnfMsg->ulResult)
    {
        /* 若UTRAN模块开机失败，则直接进MMC状态机进行处理 */
        return VOS_FALSE;
    }

    /* 切换到适配模块的开机状态机进行处理 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_SWITCH_ON);

    /* TD的开机回复消息在适配模块的开机状态机进行处理  */
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTiWaitTdStartCnfExpired_Main
 功能描述  : 收到was的开机回复超时消息
 输入参数  : ulEventType:消息类型
              pstMsg:RRMM_START_CNF超时消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdStartCnfExpired_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 构建开机失败消息，进原MMC状态机进行处理 */
    RRMM_START_CNF_STRU                *pstTempMsg      = VOS_NULL_PTR;
    VOS_UINT32                          ulTempMsgEventType;

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdStartCnfExpired_Main: ENTERED");

    /* 申请内存  */
    pstTempMsg = (RRMM_START_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                               sizeof(RRMM_START_CNF_STRU));
    if( VOS_NULL_PTR == pstTempMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdStartCnfExpired_Main: Alloc memeory Error");
        return VOS_FALSE;

    }

    /* 构造开机回复失败消息 */
    NAS_UTRANCTRL_BuildRrMmStartCnfMsg(WUEPS_PID_WRR,
                                       WUEPS_PID_MMC,
                                       MMC_START_FAILURE,
                                       pstTempMsg);

    /* 取得当前构建消息的类型 */
    ulTempMsgEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstTempMsg );

    /* 将更改过的超时消息放到输出队列中 */
    NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(ulTempMsgEventType,
                                           (struct MsgCB *)pstTempMsg);

    /* 设置需要替换入口消息标记 */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* 释放申请的消息 */
    PS_MEM_FREE(WUEPS_PID_MMC, pstTempMsg);

    /* 当前消息进入后续MMC状态机处理 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvWasPowerOffCnf_Main
 功能描述  : 收到Was的关机回复消息
 输入参数  : ulEventType:消息类型
              pstMsg:RRMM_POWER_OFF_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月7日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvWasPowerOffCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果当前UTRANCTRL模的等开机回复时状态定时器不运行认为异常 */
    if ( NAS_MMC_TIMER_STATUS_RUNING != NAS_UTRANCTRL_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF))
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvWasPowerOffCnf_Main: Unexpected Plmnsrch msg!");

        /* 丢弃该异常消息 */
        return VOS_TRUE;
    }

    /* 停止MMC通过UTRANCTRL模块给UTRAN模发送关机消息时候起的定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF);

    /* 切换到适配模块的关机状态机进行处理 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_POWER_OFF);

    /* Was的关机回复消息在适配模块的关机状态机进行处理  */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTiWaitWasPowerOffCnfExpired_Main
 功能描述  : 收到was的关机回复超时消息
 输入参数  : ulEventType:消息类型
              pstMsg:RRMM_POWER_OFF_CNF超时消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasPowerOffCnfExpired_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasPowerOffCnfExpired_Main: ENTERED");

    /* 如果当前为UTRAN MODE AUTO SWITCH模式，则需要启动UTRANCTRL模块的关机状态机 */
    /* 切换到适配模块的关机状态机进行处理 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_POWER_OFF);

    /* Was的关机回复消息在适配模块的关机状态机进行处理  */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTdPowerOffCnf_Main
 功能描述  : 收到td的关机回复消息
 输入参数  : ulEventType:消息类型
              pstMsg:RRMM_POWER_OFF_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月7日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTdPowerOffCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果当前UTRANCTRL模的等开机回复时状态定时器不运行认为异常 */
    if ( NAS_MMC_TIMER_STATUS_RUNING != NAS_UTRANCTRL_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF))
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTdPowerOffCnf_Main: Unexpected Plmnsrch msg!");

        /* 丢弃该异常消息 */
        return VOS_TRUE;
    }

    /* 停止MMC通过UTRANCTRL模块给UTRAN模发送关机消息时候起的定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF);

    /* 切换到适配模块的关机状态机进行处理 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_POWER_OFF);

    /* td的关机回复消息在适配模块的关机状态机进行处理  */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTiWaitTdPowerOffCnfExpired_Main
 功能描述  : 收到was的关机回复超时消息
 输入参数  : ulEventType:消息类型
              pstMsg:RRMM_POWER_OFF_CNF超时消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdPowerOffCnfExpired_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdPowerOffCnfExpired_Main: ENTERED");

    /* 切换到适配模块的关机状态机进行处理 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_POWER_OFF);

    /* Td的关机回复消息在适配模块的关机状态机进行处理  */
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvWasSysCfgCnf_Main
 功能描述  : 收到Was的SYSCFG设置回复消息
 输入参数  : ulEventType:消息类型
              pstMsg:RRMM_SYS_CFG_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月7日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvWasSysCfgCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SYS_CFG_CNF_STRU              *pstSysCfgCnf;

    pstSysCfgCnf = (RRMM_SYS_CFG_CNF_STRU *)pstMsg;

    /* 如果当前UTRANCTRL模的等开机回复时状态定时器不运行认为异常 */
    if ( NAS_MMC_TIMER_STATUS_RUNING != NAS_UTRANCTRL_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_WAS_SYSCFG_CNF))
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvWasSysCfgCnf_Main: Unexpected Plmnsrch msg!");

        /* 丢弃该异常消息 */
        return VOS_TRUE;
    }

    /* 停止MMC通过UTRANCTRL模块给UTRAN模发送SYSCFG设置消息时候起的定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SYSCFG_CNF);

    if ( RRMM_SYS_CFG_RESULT_FAILURE == pstSysCfgCnf->ulResult)
    {
        /* 若syscfg设置失败，则直接进MMC状态机进行处理 */
        return VOS_FALSE;
    }

    /* 若syscfg设置回复成功，切换到适配模块的SYSCFG状态机进行处理 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_SYSCFG);

    /* Was的SYSCFG回复消息在适配模块的SYSCFG状态机进行处理  */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTiWaitWasSysCfgCnfExpired_Main
 功能描述  : 收到was的SYSCFG设置回复超时消息
 输入参数  : ulEventType:消息类型
              pstMsg:RRMM_SYS_CFG_CNF超时消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasSysCfgCnfExpired_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SYS_CFG_CNF_STRU              *pstTempMsg      = VOS_NULL_PTR;
    VOS_UINT32                          ulTempMsgEventType;

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasSysCfgCnfExpired_Main: ENTERED");

    /* 构建SYSCFG设置失败消息，进原MMC状态机进行处理 */
    pstTempMsg = (RRMM_SYS_CFG_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                               sizeof(RRMM_SYS_CFG_CNF_STRU));
    if( VOS_NULL_PTR == pstTempMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasSysCfgCnfExpired_Main: Alloc memeory Error");
        return VOS_TRUE ;
    }

    /* 构造SYSCFG设置回复消息 */
    NAS_UTRANCTRL_BuildRrMmSysCfgCnfMsg(WUEPS_PID_WRR,
                                        WUEPS_PID_MMC,
                                        RRMM_SYS_CFG_RESULT_FAILURE,
                                        pstTempMsg);

    ulTempMsgEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstTempMsg );

    /* 将更改过的超时消息放到输出队列中 */
    NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(ulTempMsgEventType,
                                           (struct MsgCB *)pstTempMsg);

    /* 设置需要替换入口消息标记 */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* 释放申请的消息 */
    PS_MEM_FREE(WUEPS_PID_MMC, pstTempMsg);

    /* 当前消息进入后续MMC状态机处理 */
    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTdSysCfgCnf_Main
 功能描述  : 收到Td的SYSCFG设置回复消息
 输入参数  : ulEventType:消息类型
              pstMsg:RRMM_SYS_CFG_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月7日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTdSysCfgCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SYS_CFG_CNF_STRU              *pstSysCfgCnf;

    pstSysCfgCnf = (RRMM_SYS_CFG_CNF_STRU *)pstMsg;

    /* 如果当前UTRANCTRL模的等开机回复时状态定时器不运行认为异常 */
    if ( NAS_MMC_TIMER_STATUS_RUNING != NAS_UTRANCTRL_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_TD_SYSCFG_CNF))
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTdSysCfgCnf_Main: Unexpected Plmnsrch msg!");

        /* 丢弃该异常消息 */
        return VOS_TRUE;
    }

    /* 停止MMC通过UTRANCTRL模块给UTRAN模发送SYSCFG设置消息时候起的定时器 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_SYSCFG_CNF);

    if ( RRMM_SYS_CFG_RESULT_FAILURE == pstSysCfgCnf->ulResult)
    {
        /* 若syscfg设置失败，则直接进MMC状态机进行处理 */
        return VOS_FALSE;
    }

    /* 切换到适配模块的SYSCFG状态机进行处理 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_SYSCFG);

    /* Td的SYSCFG回复消息在适配模块的SYSCFG状态机进行处理  */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTiWaitTdSysCfgCnfExpired_Main
 功能描述  : 收到td的SYSCFG设置回复超时消息
 输入参数  : ulEventType:消息类型
              pstMsg:RRMM_SYS_CFG_CNF超时消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdSysCfgCnfExpired_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SYS_CFG_CNF_STRU              *pstTempMsg      = VOS_NULL_PTR;
    VOS_UINT32                          ulTempMsgEventType;

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdSysCfgCnfExpired_Main: ENTERED");

    /* 构建SYSCFG设置失败消息，进原MMC状态机进行处理 */
    pstTempMsg = (RRMM_SYS_CFG_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                               sizeof(RRMM_SYS_CFG_CNF_STRU));
    if( VOS_NULL_PTR == pstTempMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdSysCfgCnfExpired_Main: Alloc memeory Error");
        return VOS_TRUE ;
    }

    /* 构造SYSCFG设置回复消息 */
    NAS_UTRANCTRL_BuildRrMmSysCfgCnfMsg(WUEPS_PID_WRR,
                                        WUEPS_PID_MMC,
                                        RRMM_SYS_CFG_RESULT_FAILURE,
                                        pstTempMsg);

    ulTempMsgEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstTempMsg );

    /* 将更改过的超时消息放到输出队列中 */
    NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(ulTempMsgEventType,
                                           (struct MsgCB *)pstTempMsg);

    /* 设置需要替换入口消息标记 */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* 释放申请的消息 */
    PS_MEM_FREE(WUEPS_PID_MMC, pstTempMsg);

    /* 当前消息进入后续MMC状态机处理 */
    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvWasPlmnSrchCnf_Main
 功能描述  : 收到was的RRMM_PLMN_SEARCH_CNF回复消息
 输入参数  : ulEventType:消息类型
              pstMsg:RRMM_PLMN_SEARCH_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月7日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
  2.日    期   : 2012年8月23日
    作    者   : w00176964
    修改内容   : V7R1C50_GUTL_PhaseII:修改函数NAS_MMC_IsSpecMccListInDestPlmnIdList
  3.日    期   : 2012年9月28日
    作    者   : w00176964
    修改内容   : DTS2012092702790:GUL模式下快速指定搜网回复消息错误的丢弃导致NAS流程异常
  4.日    期   : 2012年11月16日
    作    者   : z00161729
    修改内容   : DTS2012111605452:search cnf 增加list fail接口需要进list搜状态机处理
  5.日    期   : 2014年1月20日
    作    者   : w00167002
    修改内容   : SVLTE共天线项目:在W下搜网失败为NO RF，表示当前天线资源不可用，
                 则不需要再搜TD，直接进入MMC状态机进行处理。
  6.日    期   : 2014年2月21日
    作    者   : s00217060
    修改内容   : DTS2014021902519:CSFB存在时并且当前是FDD模式，不需要再搜TD的网络
  7.日    期   : 2014年11月13日
    作    者   : z00161729
    修改内容   : 开机搜网优化项目修改
  8.日    期   : 2015年5月26日
    作    者   : w00167002
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改

  9.日    期   : 2016年2月2日
    作    者   : w00167002
    修改内容   : DTS2015110904588: 移动用户搜TD失败，进UTRANCTRL搜W,搜到W时候发现
                 需要漫游排序，触发停W搜网。MMC通知UTRANCTRL退出后发送停止搜网消息，
                 此时收到了W的搜网CNF消息，导致异常进入选网状态机。
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvWasPlmnSrchCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;

    VOS_UINT32                          ulExistHongKongMcc;
    VOS_UINT8                           ucRoamPlmnSelectionSortFlg;
    VOS_UINT8                           ucSwitchOnPlmnSearchFlag;

    enUtranMode                 = NAS_UTRANCTRL_GetCurrUtranMode();
    ulExistHongKongMcc          = VOS_FALSE;
    ucRoamPlmnSelectionSortFlg  = NAS_MMC_GetRoamPlmnSelectionSortActiveFlg();
    ucSwitchOnPlmnSearchFlag    = NAS_UTRANCTRL_GetSwithOnPlmnSearchFlag();

    pstSrchCnfMsg   = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* 如果当前UTRANCTRL模的等指定搜网回复时状态定时器运行则停止定时器 */
    if (NAS_MMC_TIMER_STATUS_RUNING != NAS_UTRANCTRL_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvWasPlmnSrchCnf_Main:TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF not running");
        return VOS_FALSE;        
    }
    
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);    

    /* 降圈复杂度 */
    if (VOS_FALSE == NAS_UTRANCTRL_IsNeedProcGuPlmnSearchCnf(NAS_MML_NET_RAT_TYPE_WCDMA, pstSrchCnfMsg))
    {
        /* 清除缓存 */
        NAS_UTRANCTRL_ClearBufferedSndUtranReqMsg();

        /* 进入MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 自动切换模式下，CSFB标志存在时，并且当前是FDD模式，不再搜TD */
    if ((VOS_TRUE                       == NAS_MML_IsCsfbServiceStatusExist())
     && (NAS_UTRANCTRL_UTRAN_MODE_FDD   == enUtranMode))
    {
        /* 清除缓存的搜网请求消息 */
        NAS_UTRANCTRL_ClearBufferedSndUtranReqMsg();

        /* 进入MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 指定搜网失败根据搜网列表更新中国网络标记 */
    NAS_UTRANCTRL_UpdateSearchedSpecTdMccFLg(NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                             NAS_UTRANCTRL_GetSpecTdMccList(),
                                             &(pstSrchCnfMsg->PlmnIdList));

    /* 根据中国网络标记设置utran工作模式 */
    if (VOS_TRUE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);
    }


    ulExistHongKongMcc = NAS_UTRANCTRL_IsSpecPlmnMccInGuRrcPlmnIdList(NAS_UTRANCTRL_HONGKONG_MCC, &(pstSrchCnfMsg->PlmnIdList));

    if ((NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
     && (VOS_FALSE == ulExistHongKongMcc)
     && (VOS_TRUE == ucRoamPlmnSelectionSortFlg)
     && (VOS_TRUE == ucSwitchOnPlmnSearchFlag)
     && ((pstSrchCnfMsg->PlmnIdList.ulHighPlmnNum != 0)
      || (pstSrchCnfMsg->PlmnIdList.ulLowPlmnNum != 0)))
    {
        /* 开机搜网场景，如果was搜网结果中没有一个网络mcc在tds mcc列表中且不包括香港网络，且高低质量网络个数不全为0，
           则跳过tds搜网，清除缓存*/
        NAS_UTRANCTRL_ClearBufferedSndUtranReqMsg();

        /* 进入MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 切换到适配模块的选网状态机进行处理 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_PLMN_SELECTION);

    /* was的搜网回复消息在适配模块的选网状态机进行处理  */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvInterAbortUtranCtrlPlmnSearchReq_Main
 功能描述  : 收到was的inter abort utran ctrl plmn search req回复消息
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月13日
    作    者   : z00161729
    修改内容   : 开机搜网优化项目修改

*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvInterAbortUtranCtrlPlmnSearchReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* 如果当前UTRANCTRL模的等指定搜网回复时状态定时器运行则停止定时器 */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_UTRANCTRL_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF))
    {
        NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);
    }

    /* 更新utran mode为fdd，utranctrl 搜网状态机退出，消息进mmc继续处理，通知接入层打断由mmc处理 */
    NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);

    /* 通知mmc MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_CNF*/
    NAS_MMC_SndInterAbortUtranCtrlPlmnSearchCnfMsg();

    return VOS_TRUE;

}








/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvMmcInterSkipSearchWasIndMsg_Main
 功能描述  : 收到MMC发送的跳过搜索W的指示消息
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_INTER_SKIP_SEARCH_W_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月11日
    作    者   : w00167002
    修改内容   : 跳过搜网W结果.
                 注:SVLTE共天线，在W下搜网NO RF后，在G下搜网成功国内驻留成功后，
                 后续再发起搜网时候不能搜WAS,否则G会丢网。但在UTRANCTRL状态机时候
                 ，NO RF时候当前是FDD模式的，因而MMC再发起搜网时候，会先给WAS发送，
                 UTRAN构造SKIP W消息，在UTRANCTRL状态机搜索TDD.
  2.日    期   : 2015年5月18日
    作    者   : b00269685
    修改内容   : 增加当前正在搜W停止当前搜W的处理
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcInterSkipSearchWasIndMsg_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果正在搜TD，就不需要进状态机处理，在搜到TD search cnf的时候会跳过W */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF))
    {
        return VOS_TRUE;
    }

    /* SKIP W时候，则设置当前为TDD模式 */
    NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);

    /* 切换到适配模块的选网状态机进行处理 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_PLMN_SELECTION);

    /* was的搜网回复消息在适配模块的选网状态机进行处理  */
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvMmcInterSkipSearchTdsIndMsg_Main
 功能描述  : 收到MMC发送的跳过搜索TDS的指示消息
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_INTER_SKIP_SEARCH_TDS_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月3日
    作    者   : z00161729
    修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcInterSkipSearchTdsIndMsg_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* SKIP TDS时候，则设置当前为FDD模式 */
    NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);

    /* 切换到适配模块的选网状态机进行处理 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_PLMN_SELECTION);

    /* tds的搜网回复消息在适配模块的选网状态机进行处理  */
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_Main
 功能描述  : 收到td的指定搜网回复超时消息
 输入参数  : ulEventType:消息类型
              pstMsg:搜网超时消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
  2.日    期   : 2014年2月21日
    作    者   : s00217060
    修改内容   : DTS2014021902519:CSFB存在时并且当前是FDD模式，不需要再搜TD的网络
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;

    enUtranMode     = NAS_UTRANCTRL_GetCurrUtranMode();

    /* 获得当前缓存的缓冲区地址 */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_Main: ENTERED");

    /* CSFB标志存在时，并且当前是FDD模式，不再搜TD */
    if ((VOS_TRUE                       == NAS_MML_IsCsfbServiceStatusExist())
     && (NAS_UTRANCTRL_UTRAN_MODE_FDD   == enUtranMode))
    {
        /* 构造指定搜网回复失败消息到内存的缓存区域 */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                        WUEPS_PID_MMC,
                                                        NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                       (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* 保存构造指定搜网回复失败消息事件类型 */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* 设置需要替换入口消息标记 */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* 当前消息进入后续MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 如果当前为UTRAN MODE AUTO SWITCH模式，则需要启动UTRANCTRL模块的搜网状态机 */
    if ( NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO == NAS_UTRANCTRL_GetCurUtranSwitchMode() )
    {
        /* 切换到适配模块的选网状态机进行处理 */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_PLMN_SELECTION);

        /* 进入适配层选网状态机处理  */
        return VOS_TRUE;
    }

    /* 构造指定搜网回复失败消息到内存的缓存区域 */
    NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                WUEPS_PID_MMC,
                                                NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

    /* 保存构造指定搜网回复失败消息事件类型 */
    pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

    /* 设置需要替换入口消息标记 */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* 当前消息进入后续MMC状态机处理 */
    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvWasRrMmRelInd_Main
 功能描述  : 收到td的指定搜网回复超时消息
 输入参数  : ulEventType:消息类型
              pstMsg:RRMM_REL_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数

  2.日    期   : 2014年6月12日
    作    者   : w00167002
    修改内容   : WAS异常且当前NO RF,则进入MMC进行处理
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvWasRrMmRelInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_REL_IND_STRU                  *pstRrmmRelIndMsg    = VOS_NULL_PTR;

    pstRrmmRelIndMsg = (RRMM_REL_IND_STRU *)pstMsg;

    /* 如果当前UTRANCTRL模的等搜网回复时状态定时器运行，则停止定时器 */
    if ( NAS_MMC_TIMER_STATUS_RUNING != NAS_UTRANCTRL_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF))
    {
        /* 当前消息进入后续MMC状态机处理 */
        return VOS_FALSE;
    }

    /* WAS搜网时接入层复位，搜TD模 */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);


    /* 如果原因为NO RF，则进入MMC状态机进行处理 */
    if ( RRC_REL_CAUSE_NO_RF == pstRrmmRelIndMsg->ulRelCause)
    {
        return VOS_FALSE;
    }

    if ( NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO == NAS_UTRANCTRL_GetCurUtranSwitchMode() )
    {
        /* 切换到适配模块的选网状态机进行处理 */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_PLMN_SELECTION);

        /* 当前消息进入适配层选网状态机处理 */
        return VOS_TRUE;
    }

    /* 当前消息进入后续MMC状态机处理 */
    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvGasPlmnSrchCnf_Main
 功能描述  : 收到Gas的RRMM_PLMN_SEARCH_CNF回复消息
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_PLMN_SEARCH_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月7日
    作    者   : w00176964
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
  2.日    期   : 2012年11月16日
    作    者   : z00161729
    修改内容   : DTS2012111605452:search cnf 增加list fail接口需要进list搜状态机处理
  3.日    期   : 2014年6月24日
    作    者   : b00269685
    修改内容   : DSDS III:G下搜网NO RF场景，进入状态机处理
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvGasPlmnSrchCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg = VOS_NULL_PTR;

    pstSrchCnfMsg   = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* 降圈复杂度 */
    if (VOS_FALSE == NAS_UTRANCTRL_IsNeedProcGuPlmnSearchCnf(NAS_MML_NET_RAT_TYPE_GSM, pstSrchCnfMsg))
    {
        /* 进入MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 根据搜网列表更新中国网络标记 */
    NAS_UTRANCTRL_UpdateSearchedSpecTdMccFLg(NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                             NAS_UTRANCTRL_GetSpecTdMccList(),
                                             &(pstSrchCnfMsg->PlmnIdList));

    /* 根据中国网络标记设置utran工作模式 */
    if (VOS_TRUE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);
    }

    /* 进入状态机处理 */
    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvRcvLmmPlmnSrchCnf_Main
 功能描述  : 收到lmm的ID_LMM_MMC_PLMN_SRCH_CNF回复消息
 输入参数  : ulEventType:消息类型
              pstMsg:ID_LMM_MMC_PLMN_SRCH_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月7日
    作    者   : W00176964
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
  2.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2013年8月26日
    作    者   : w00242748
    修改内容   : DTS2013071808373, 编译告警清理
  4.日    期   : 2014年6月10日
    作    者   : w00167002
    修改内容   : DSDS III:L下搜网NO RF场景，进入状态机处理
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRcvLmmPlmnSrchCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU                             *pstLmmSrchCnfMsg;
    RRC_PLMN_ID_LIST_STRU                                  *pstGuPlmnIdList;

    pstLmmSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    /* 提取函数，utranctrl不需要处理的消息或场景都放在函数里 */
    if (VOS_FALSE == NAS_UTRANCTRL_IsNeedProcLmmPlmnSearchCnf(NAS_MML_NET_RAT_TYPE_LTE, pstLmmSrchCnfMsg))
    {
        /* 进入MMC状态机处理 */
        return VOS_FALSE;
    }

    pstGuPlmnIdList   = (RRC_PLMN_ID_LIST_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                                    sizeof(RRC_PLMN_ID_LIST_STRU));
    if (VOS_NULL_PTR == pstGuPlmnIdList)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRcvLmmPlmnSrchCnf_Main:Invalid pstGuPlmnIdList");
        return VOS_FALSE;
    }

    /*转换L格式的搜索列表成为GU格式的*/
    NAS_MMC_ConvertLmmPlmnIdListToGUFormat(&(pstLmmSrchCnfMsg->stPlmnIdList), pstGuPlmnIdList);

    /* 根据搜网列表更新中国网络标记 */
    NAS_UTRANCTRL_UpdateSearchedSpecTdMccFLg(NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                             NAS_UTRANCTRL_GetSpecTdMccList(),
                                             pstGuPlmnIdList);

    /* 根据中国网络标记设置utran工作模式 */
    if (VOS_TRUE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstGuPlmnIdList);

    /* 进入MMC状态机处理 */
    return VOS_FALSE;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTdPlmnSrchCnf_Main
 功能描述  : 收到Td的RRMM_PLMN_SEARCH_CNF回复消息
 输入参数  : ulEventType:消息类型
              pstMsg:RRMM_PLMN_SEARCH_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月7日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
  2.日    期   : 2012年9月28日
    作    者   : w00176964
    修改内容   : DTS2012092702790:GUL模式下快速指定搜网回复消息错误的丢弃导致NAS流程异常
  3.日    期   : 2012年11月16日
    作    者   : z00161729
    修改内容   : DTS2012111605452:search cnf 增加list fail接口需要进list搜状态机处理
  4.日    期   : 2013年11月25日
    作    者   : z00161729
    修改内容   : SVLTE优化G-TL ps切换性能修改
  5.日    期   : 2014年2月21日
    作    者   : s00217060
    修改内容   : DTS2014021902519:CSFB存在时并且当前是TDD模式，不需要再搜W的网络
  6.日    期   : 2014年6月10日
    作    者   : w00167002
    修改内容   : DSDS GUNAS III项目:自动切换模式下如果搜网NO RF直接透传到MMC状态机处理
  7.日    期   : 2016年2月2日
    作    者   : w00167002
    修改内容   : DTS2015110904588: 移动用户搜TD失败，进UTRANCTRL搜W,搜到W时候发现
                 需要漫游排序，触发停W搜网。MMC通知UTRANCTRL退出后发送停止搜网消息，
                 此时收到了W的搜网CNF消息，导致异常进入选网状态机。  
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTdPlmnSrchCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg = VOS_NULL_PTR;

    VOS_UINT32                          ulIsOtherModemPlmnInTdMccList;
    NAS_MML_PLMN_ID_STRU               *pstOtherModemPlmnId = VOS_NULL_PTR;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;

    enUtranMode     = NAS_UTRANCTRL_GetCurrUtranMode();

    pstSrchCnfMsg   = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* 如果当前UTRANCTRL模的等指定搜网回复时状态定时器运行则停止定时器 */
    if (NAS_MMC_TIMER_STATUS_RUNING != NAS_UTRANCTRL_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTdPlmnSrchCnf_Main TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF NOT RUNNING");
        return VOS_FALSE;
    }

    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF);    

    /* 降圈复杂度 */
    if (VOS_FALSE == NAS_UTRANCTRL_IsNeedProcGuPlmnSearchCnf(NAS_MML_NET_RAT_TYPE_WCDMA, pstSrchCnfMsg))
    {
        /* 清除缓存的搜网请求消息 */
        NAS_UTRANCTRL_ClearBufferedSndUtranReqMsg();

        /* 进入MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 自动切换模式下，CSFB标志存在时，并且当前是TDD模式，不再搜W */
    if ((VOS_TRUE                       == NAS_MML_IsCsfbServiceStatusExist())
     && (NAS_UTRANCTRL_UTRAN_MODE_TDD   == enUtranMode))
    {
        /* 清除缓存的搜网请求消息 */
        NAS_UTRANCTRL_ClearBufferedSndUtranReqMsg();

        /* 进入MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 根据搜网列表更新中国网络标记 */
    NAS_UTRANCTRL_UpdateSearchedSpecTdMccFLg(NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                             NAS_UTRANCTRL_GetSpecTdMccList(),
                                             &(pstSrchCnfMsg->PlmnIdList));

    /* 根据中国网络标记设置utran工作模式 */
    if (VOS_TRUE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);

        /* 进入MMC状态机处理 */
        return VOS_FALSE;
    }

    pstOtherModemPlmnId = NAS_MMC_GetOtherModemPlmnId();
    ulIsOtherModemPlmnInTdMccList = NAS_MML_IsMccInDestMccList(pstOtherModemPlmnId->ulMcc,
                                                NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                                NAS_UTRANCTRL_GetSpecTdMccList());

    if ((VOS_TRUE == NAS_MMC_GetUtranSkipWPlmnSearchFlag())
     && (VOS_TRUE == ulIsOtherModemPlmnInTdMccList))
    {
        /* 如果副卡已驻留中国网络跳过搜w网络，清除缓存的搜网请求消息 */
        NAS_UTRANCTRL_ClearBufferedSndUtranReqMsg();

        /* 进入MMC状态机处理 */
        return VOS_FALSE;
    }

    /* 切换到适配模块的选网状态机进行处理 */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_PLMN_SELECTION);

    /* tdrrc的搜网回复消息在适配模块的选网状态机进行处理 */
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_Main
 功能描述  : 收到td的指定搜网回复超时消息
 输入参数  : ulEventType:消息类型
              pstMsg:RRMM_SYS_CFG_CNF超时消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
  2.日    期   : 2014年2月21日
    作    者   : s00217060
    修改内容   : DTS2014021902519:CSFB存在时并且当前是TDD模式，不需要再搜W的网络
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU                           *pstBufferEntryMsg = VOS_NULL_PTR;
    NAS_UTRANCTRL_UTRAN_SWITCH_MODE_ENUM_UINT8              enCurUtranSwitchMode;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8                     enUtranMode;

    enUtranMode       = NAS_UTRANCTRL_GetCurrUtranMode();

    /* 获得当前缓存的缓冲区地址 */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    enCurUtranSwitchMode = NAS_UTRANCTRL_GetCurUtranSwitchMode();

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_Main: ENTERED");

    /* 自动切换模式下，CSFB标志存在时，并且当前是TDD模式，不再搜W */
    if ((VOS_TRUE                       == NAS_MML_IsCsfbServiceStatusExist())
     && (NAS_UTRANCTRL_UTRAN_MODE_TDD   == enUtranMode))
    {
        /* 构造指定搜网回复失败消息到内存的缓存区域 */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                   (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* 保存构造指定搜网回复失败消息事件类型 */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* 设置需要替换入口消息标记 */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* 当前消息进入后续MMC状态机处理 */
        return VOS_FALSE;
    }



    /* 如果当前为UTRAN MODE AUTO SWITCH模式，则需要启动UTRANCTRL模块的搜网状态机 */
    if ( (VOS_TRUE != NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
      && (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO == enCurUtranSwitchMode) )
    {
        /* 切换到适配模块的选网状态机进行处理 */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_PLMN_SELECTION);

        /* 进入适配层选网状态机处理 */
        return VOS_TRUE;
    }

    /* 构造指定搜网回复失败消息到内存的缓存区域 */
    NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                WUEPS_PID_MMC,
                                                NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                               (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

    /* 保存构造指定搜网回复失败消息事件类型 */
    pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

    /* 设置需要替换入口消息标记 */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* 当前消息进入后续MMC状态机处理 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvMmcInterSearchReq_Main
 功能描述  : 收到MMC 内部搜网请求,清除中国网络标记
 输入参数  : ulEventType:消息类型
              pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : x00203213
    修改内容   : V7R1C50_GUTL_PhaseII:新生成函数
  2.日    期   : 2014年11月25日
    作    者   : z00161729
    修改内容   : 开机搜网优化项目修改
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcInterSearchReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO == NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        NAS_UTRANCTRL_SetSearchedSpecTdMccFlg(VOS_FALSE);
    }

    NAS_UTRANCTRL_SetSwithOnPlmnSearchFlag(VOS_FALSE);

    /* 当前消息进入后续MMC状态机处理 */
    return VOS_FALSE;
}




/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTiHplmnTimerExpired_Main
 功能描述  : 收到HPLMN TIMER超时消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月14日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年12月20日
   作    者   : w00167002
   修改内容   : DTS2013112917981:guNAS删除在TD模式下不能进行bg搜的限制。
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiHplmnTimerExpired_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* 消息未被处理完成需继续处理 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RcvTiTryingHighPrioPlmnSearchExpired_Main
 功能描述  : 收到10S定时器超时消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月14日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年12月20日
   作    者   : w00167002
   修改内容   : DTS2013112917981:guNAS删除在TD模式下不能进行bg搜的限制。
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiTryingHighPrioPlmnSearchExpired_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* 消息未被处理完成需继续处理 */
    return VOS_FALSE;
}


/*lint -restore */


#endif  /* END OF #if (FEATURE_ON == FEATURE_UE_MODE_TDS) */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
