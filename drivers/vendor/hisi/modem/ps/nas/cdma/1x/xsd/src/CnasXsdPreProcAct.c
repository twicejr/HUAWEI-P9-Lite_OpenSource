/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdPreProcAct.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年07月03日
  功能描述   : 1X SD预处理事件处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年07月03日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasXsdPreProcAct.h"
#include  "CnasXsdSndXreg.h"
#include  "CnasXsdCtx.h"
#include  "CnasXsdComFunc.h"
#include  "CnasXsdMntn.h"
#include  "CnasXsdSndInternalMsg.h"
#include  "CnasXsdFsmMainTbl.h"
#include  "CnasXsdSysAcqStrategy.h"
#include  "CnasXsdSndCas.h"
#include  "CnasXsdSndMscc.h"
#include  "cas_1x_trchctrl_proc_nas_pif.h"
#include "CnasXsdProcNvim.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_PRE_PROC_ACT_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvSliceReverseProtectTimerExpired_PreProc
 功能描述  : 收到avoid list timer定时器超时处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月14日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvSliceReverseProtectTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulCurSlice;
    VOS_UINT32                          ulRunSliceNum;
    VOS_UINT8                           i;
    CNAS_XSD_AVOID_FREQ_INFO_STRU      *pstAvoidFreqInfo = VOS_NULL_PTR;

    /* 获取当前系统的slice */
    ulCurSlice = CNAS_XSD_GetSystemSlice();

    /* 遍历avoid列表中所有的频点的到期slice */
    for (i = 0; i < CNAS_MIN(CNAS_XSD_GetAvoidFreqListNum(), CNAS_XSD_MAX_AVOID_FREQ_NUM); i++)
    {
        pstAvoidFreqInfo = CNAS_XSD_GetAvoidFreqFromAvoidList(i);

        if (VOS_NULL_PTR == pstAvoidFreqInfo)
        {
            continue;
        }

        if (VOS_FALSE == pstAvoidFreqInfo->ucAvoidFlag)
        {
            continue;
        }

        if (ulCurSlice < pstAvoidFreqInfo->ulStartSlice)
        {
            /* 考虑反转问题 */
            ulRunSliceNum = CNAS_XSD_MAX_SLICE_VALUE - pstAvoidFreqInfo->ulStartSlice + ulCurSlice + 1;
        }
        else
        {
            ulRunSliceNum = ulCurSlice - pstAvoidFreqInfo->ulStartSlice;
        }

        /* 如果已经运行的slice数目大于等于到期的slice数目，从avoid频点列表中剔除该频点 */
        if (ulRunSliceNum >= pstAvoidFreqInfo->ulExpiredSliceNum)
        {
            CNAS_XSD_DeleteAvoidFlagFromAvoidList(i);
        }
    }

    /*如果avoid列表中存在禁用标记，表示存在被禁用的频点，启动定时器 */
    if (VOS_TRUE == CNAS_XSD_IsExistAvoidFlagInAvoidlist())
    {
        CNAS_XSD_StartTimer(TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER,
                            TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER_LEN);
    }

    CNAS_XSD_LogAvoidFreqList(CNAS_XSD_GetAvoidFreqListAddr());

    return VOS_TRUE;
}

#ifdef DMT
/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvXsdTestCfgREQ_PreProc
 功能描述  : 收到测试配置消息处理函数
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月14日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvXsdTestCfgREQ_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_XSD_TEST_CFG_REQ_STRU     *pstCfgReq = VOS_NULL_PTR;

    pstCfgReq = (CNAS_XSD_XSD_TEST_CFG_REQ_STRU *)pstMsg;

    g_ulCurSlice = pstCfgReq->ulCurSlice;

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvXsdMofiyPrlAcqRecordReq_PreProc
 功能描述  : 收到修改PRL捕获记录信息的请求消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月17日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvXsdMofiyPrlAcqRecordReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_XSD_MODIFY_PRL_ACQ_RECORD_REQ_STRU            *pstModifyReq   = VOS_NULL_PTR;
    VOS_UINT16                                              i;
    CNAS_PRL_ACQ_RECORD_STRU                               *pstRecordInfo = VOS_NULL_PTR;

    pstModifyReq = (CNAS_XSD_XSD_MODIFY_PRL_ACQ_RECORD_REQ_STRU *)pstMsg;

    for (i = 0; i < pstModifyReq->usRecNum; i++)
    {
        pstRecordInfo = CNAS_PRL_GetSpecifiedPrlAcqRecord(pstModifyReq->astAcqRecord[i].usAcqRecordIndex);

        if ((VOS_NULL_PTR != pstRecordInfo)
         && (VOS_TRUE     == pstRecordInfo->ucAcqValid))
        {
            switch (pstRecordInfo->enAcqType)
            {
                case CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_CUSTOM_CHANNELS:
                    {
                        if (pstModifyReq->astAcqRecord[i].stAcqRecordInfo.u.stCelluarCustomSys.ucNumOfChans <= pstRecordInfo->u.stCelluarCustomSys.ucNumOfChans)
                        {
                            pstRecordInfo->u.stCelluarCustomSys.ucNumOfChans = \
                                pstModifyReq->astAcqRecord[i].stAcqRecordInfo.u.stCelluarCustomSys.ucNumOfChans;

                            NAS_MEM_CPY_S(&(pstRecordInfo->u.stCelluarCustomSys.ausChan[0]),
                                          sizeof(VOS_UINT16)*pstRecordInfo->u.stCelluarCustomSys.ucNumOfChans,
                                          &(pstModifyReq->astAcqRecord[i].stAcqRecordInfo.u.stCelluarCustomSys.ausChan[0]),
                                          sizeof(VOS_UINT16)*pstRecordInfo->u.stCelluarCustomSys.ucNumOfChans);
                        }
                    }
                    break;

                default:

                    break;

            }
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvXsdMofiyPrlSysRecordReq_PreProc
 功能描述  : 收到修改PRL系统表记录请求消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月14日
    作    者   : y00245242
    修改内容   : 新生成函数

  2.日    期   : 2015年7月25日
    作    者   : y00245242
    修改内容   : iteration 17开发

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvXsdMofiyPrlSysRecordReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_XSD_MODIFY_PRL_SYS_RECORD_REQ_STRU            *pstModifyReq  = VOS_NULL_PTR;
    VOS_UINT16                                              i;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstRecordInfo = VOS_NULL_PTR;
    VOS_UINT16                                              usPriLvl;

    pstModifyReq = (CNAS_XSD_XSD_MODIFY_PRL_SYS_RECORD_REQ_STRU *)pstMsg;

    for (i = 0; i < pstModifyReq->usRecNum; i++)
    {
        pstRecordInfo = CNAS_PRL_GetSpecifiedPrlSysRecord(pstModifyReq->astSysRecord[i].usSysRecordIndex);

        if (VOS_NULL_PTR != pstRecordInfo)
        {
            NAS_MEM_CPY_S(pstRecordInfo,
                          sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU),
                          &(pstModifyReq->astSysRecord[i].stSysRecordInfo),
                          sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU));
        }
    }

    usPriLvl = 0;
    /* 这儿需要重新刷新一下PRL表中的level，避免后续GEO系统记录搜索时出错 */
    for (i = 0; i <CNAS_PRL_GetPrlHeaderInfoAddr()->usNumSysRecs; i++)
    {
        CNAS_PRL_GetPrlSysInfoAddr()->pstSysRecord[i].usPriLvl = usPriLvl;

        if (CNAS_PRL_RELATIVE_PRI_MORE == CNAS_PRL_GetPrlSysInfoAddr()->pstSysRecord[i].enPriInd)
        {
            usPriLvl++;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvXsdMofiyPrlHeadInfoReq_PreProc
 功能描述  : 收到修改PRL头信息的请求消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月14日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvXsdMofiyPrlHeadInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_XSD_MODIFY_PRL_HEAD_INFO_REQ_STRU             *pstModifyReq   = VOS_NULL_PTR;
    CNAS_PRL_HEADER_INFO_STRU                              *pstPrlHeadInfo = VOS_NULL_PTR;

    pstModifyReq = (CNAS_XSD_XSD_MODIFY_PRL_HEAD_INFO_REQ_STRU *)pstMsg;

    pstPrlHeadInfo = CNAS_PRL_GetPrlHeaderInfoAddr();

    pstPrlHeadInfo->ucPreferOnly = pstModifyReq->ucPreferOnly;
    pstPrlHeadInfo->enDefRoamInd = pstModifyReq->enDefRoamInd;

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvXsdMofiyOocScanIntervalReq_PreProc
 功能描述  : 收到修改PRL头信息的请求消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月17日
    作    者   : c00299063
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvXsdMofiyOocScanIntervalReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_XSD_MODIFY_OOC_SCAN_INTERVAL_REQ_STRU         *pstModifyReq        = VOS_NULL_PTR;
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU                        *pstOocScheduleInfo  = VOS_NULL_PTR;

    pstModifyReq        = (CNAS_XSD_XSD_MODIFY_OOC_SCAN_INTERVAL_REQ_STRU *)pstMsg;

    pstOocScheduleInfo  = CNAS_XSD_GetOocScheduleInfo();

    pstOocScheduleInfo->stOocCtxInfo.ucDoTrafficFlag      = pstModifyReq->ucDoTrafficFlag;

    NAS_MEM_CPY_S(&(pstOocScheduleInfo->stConfigInfo),
                  sizeof(pstOocScheduleInfo->stConfigInfo),
                  &(pstModifyReq->stOocCfgInfo),
                  sizeof(CNAS_XSD_OOC_CONFIG_INFO_STRU));

    return VOS_TRUE;
}


#endif

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccMoCallStartNtf_PreProc
 功能描述  : 收到mma的主叫开始消息的处理时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : c00299063
    修改内容   : 新生成函数

  2.日    期   : 2015年7月24日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccMoCallStartNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_1X_SYSTEM_STRU                *pstOrignalSys      = VOS_NULL_PTR;
    MSCC_XSD_MO_CALL_START_NTF_STRU        *pstCallStartNtfMsg = VOS_NULL_PTR;
    CNAS_XSD_CALL_EXIST_FLAG_ENUM_UINT8     enCallExistFlg;

    pstCallStartNtfMsg =  (MSCC_XSD_MO_CALL_START_NTF_STRU*)pstMsg;

    enCallExistFlg = CNAS_XSD_TransferMsccCallTypeToXsdFormat(pstCallStartNtfMsg->enCallType);

    /* 异常处理 */
    if (CNAS_XSD_CALL_EXIST_NULL_FLAG == enCallExistFlg)
    {
        return VOS_TRUE;
    }

    if (CNAS_XSD_EMC_VOICE_CALL_EXIST_FLAG == enCallExistFlg)
    {
        /* 申请Session保护 */
        CNAS_XSD_SndCasBeginSessionNotify(CNAS_CAS_1X_SESSION_TYPE_CS_CALL);

        /* 紧急呼构表 */
        CNAS_XSD_BuildEmcCallRedialScanChanList();

        /* 记录当前MRU LIST，用于紧急呼叫重拨计数*/
        CNAS_XSD_BuildEmcRedialMruList();

        return VOS_TRUE;
    }

    /* 新建呼叫重拨搜网频点列表 */
    if (CNAS_XSD_CALL_EXIST_NULL_FLAG == CNAS_XSD_GetCallExistFlg())
    {
        CNAS_XSD_BuildCallRedialScanChanList(CNAS_XSD_GetCurCampedSysInfo());
    }

    CNAS_XSD_SetCallExistFlg(enCallExistFlg);

    if (VOS_TRUE == CNAS_XSD_GetSystemCampOnFlag())
    {
        /* 如果是驻留状态,保存当前驻留系统 */
        pstOrignalSys = &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCurCampedSysInfo.stSystem);

        CNAS_XSD_SaveCallOrignalSys(pstOrignalSys);

        CNAS_XSD_SetCallOrigSysExistFlg(VOS_TRUE);
    }
    else
    {
        /* 记录标记呼叫开始时无驻留系统 */
        CNAS_XSD_SetCallOrigSysExistFlg(VOS_FALSE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccMoCallEndNtf_PreProc
 功能描述  : 收到MMA的主叫结束消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : c00299063
    修改内容   : 新生成函数

  2.日    期   : 2015年7月20日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccMoCallEndNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_1X_MO_CALL_END_NTF_STRU           *pstCallEndNtfMsg = VOS_NULL_PTR;
    CNAS_XSD_CALL_EXIST_FLAG_ENUM_UINT8         enCallExistFlg;
    CNAS_XSD_FSM_CTX_STRU                      *pstCurFsm        = VOS_NULL_PTR;

    pstCallEndNtfMsg = (MSCC_XSD_1X_MO_CALL_END_NTF_STRU*)pstMsg;

    enCallExistFlg = CNAS_XSD_TransferMsccCallTypeToXsdFormat(pstCallEndNtfMsg->enCallType);
    pstCurFsm                                   = CNAS_XSD_GetCurFsmAddr();

    if ((CNAS_XSD_NORMAL_VOICE_CALL_EXIST_FLAG == enCallExistFlg)
     || (CNAS_XSD_NORMAL_DATA_CALL_EXIST_FLAG  == enCallExistFlg))
    {
        /* 清除呼叫标记 */
        CNAS_XSD_ClearCallExistFlg(enCallExistFlg);

        if (CNAS_XSD_CALL_EXIST_NULL_FLAG == CNAS_XSD_GetCallExistFlg())
        {
            /* 清空呼叫重拨搜网频点列表 */
            CNAS_XSD_ClearCallRedialScanChanList();
        }

        return VOS_TRUE;
    }

    if (CNAS_XSD_EMC_VOICE_CALL_EXIST_FLAG == enCallExistFlg)
    {
        /* 清空紧急呼重拨搜网控制信息*/
        CNAS_XSD_ClearEmcRedialSysAcqCfgInfo();

        /* 紧急呼未接通收到Call End */
        if (VOS_NULL_PTR != CNAS_XSD_GetEmcCallRedialScanChanListAddr()->pstScanChanInfo)
        {
            /* 释放资源保护 */
            CNAS_XSD_SndCasEndSessionNotify(CNAS_CAS_1X_SESSION_TYPE_CS_CALL);

            /* 清空紧急呼搜网的频点扫描列表 */
            CNAS_XSD_ClearEmcCallRedialScanChanList();

            return VOS_FALSE;
        }

        /* 当前处于层1状态机的INITIAL态，说明是缓存消息的处理，进入状态机处理缓存 */
        if ((CNAS_XSD_FSM_L1_MAIN       == pstCurFsm->enFsmId)
         && (CNAS_XSD_L1_STA_INITIAL    == pstCurFsm->ulState))
        {
            return VOS_FALSE;
        }

        /* 释放资源保护 */
        CNAS_XSD_SndCasEndSessionNotify(CNAS_CAS_1X_SESSION_TYPE_CS_CALL);

        /* NV设置成不支持CALL BACK */
        if (VOS_FALSE == CNAS_XSD_GetCallBackCfg()->ulCallBackEnableFlg)
        {
            return VOS_TRUE;
        }

        /* 进入CallBack模式 */
        CNAS_XSD_SetEmcState(CNAS_XSD_EMC_STATE_CALLBACK);

        /* 上报进入CALLBACK模式NTF */
        CNAS_XSD_SndMsccEmcCallBackInd(NAS_MSCC_PIF_EMC_CALLBACK_MODE_ENABLE);

        /* 启动CALLBACK保护定时器 */
        CNAS_XSD_StartTimer(TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER, CNAS_XSD_GetCallBackCfg()->ulCallBackModeTimerLen);

        CNAS_XSD_LogCallBackStatusInd(ID_CNAS_XSD_MNTN_LOG_ENTER_CALLBACK_IND);

        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccMoCallSuccessNtf_PreProc
 功能描述  : 收到MMA的主叫成功的消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : c00299063
    修改内容   : 新生成函数

  2.日    期   : 2015年7月24日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccMoCallSuccessNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_MO_CALL_SUCCESS_NTF_STRU  *pstCallSuccessNtfMsg = VOS_NULL_PTR;
    CNAS_XSD_CALL_EXIST_FLAG_ENUM_UINT8 enCallExistFlg;

    pstCallSuccessNtfMsg = (MSCC_XSD_MO_CALL_SUCCESS_NTF_STRU*)pstMsg;

    enCallExistFlg = CNAS_XSD_TransferMsccCallTypeToXsdFormat(pstCallSuccessNtfMsg->enCallType);

    /* 异常处理 */
    if (CNAS_XSD_CALL_EXIST_NULL_FLAG == enCallExistFlg)
    {
        return VOS_TRUE;
    }

    if (CNAS_XSD_EMC_VOICE_CALL_EXIST_FLAG == enCallExistFlg)
    {
        /* 清空紧急呼重拨搜网的频点列表 */
        CNAS_XSD_ClearEmcCallRedialScanChanList();

        /* 保存建立成功的系统 */
        CNAS_XSD_SaveEmcCallOriginalSys(&(CNAS_XSD_GetCurCampedSysInfo()->stSystem));

        return VOS_TRUE;
    }

    /* 普通语音或数据呼:清除呼叫标记 */
    CNAS_XSD_ClearCallExistFlg(enCallExistFlg);

    if (CNAS_XSD_CALL_EXIST_NULL_FLAG == CNAS_XSD_GetCallExistFlg())
    {
        /* 清空呼叫重拨搜网频点列表 */
        CNAS_XSD_ClearCallRedialScanChanList();

        /* 清空紧急呼重拨搜网控制信息*/
        CNAS_XSD_ClearEmcRedialSysAcqCfgInfo();
    }

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccCFreqLockSetNtf_PreProc
 功能描述  : 收到MMA的设置锁频的消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月29日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCFreqLockSetNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_CFREQ_LOCK_NTF_STRU       *pstCFreqLockNtf         = VOS_NULL_PTR;
    CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU  *pstCFreqLockSetPara     = VOS_NULL_PTR;
    CNAX_XSD_CAMPED_SYS_INFO_STRU      *pstXsdCampedSysInfo     = VOS_NULL_PTR;

    pstCFreqLockNtf = (MSCC_XSD_CFREQ_LOCK_NTF_STRU *)pstMsg;

    /* 发送给CAS */
    if (VOS_TRUE != CNAS_XSD_SndCasCFreqLockNtf(pstCFreqLockNtf))
    {
        return VOS_TRUE;
    }

    pstCFreqLockSetPara                  = CNAS_XSD_GetFreqLockAddr();

    pstCFreqLockSetPara->ucFreqLockMode  = pstCFreqLockNtf->enFreqLockMode;
    pstCFreqLockSetPara->usCdmaBandClass = pstCFreqLockNtf->usCdmaBandClass;
    pstCFreqLockSetPara->usSid           = pstCFreqLockNtf->usSid;
    pstCFreqLockSetPara->usNid           = pstCFreqLockNtf->usNid;
    pstCFreqLockSetPara->usCdmaFreq      = pstCFreqLockNtf->usCdmaFreq;
    pstCFreqLockSetPara->usCdmaPn        = pstCFreqLockNtf->usCdmaPn;

    /* 当前sysCfg不支持1x，则不执行搜网 */
    if (VOS_FALSE == pstCFreqLockNtf->ulIsSupport1x)
    {
        return VOS_TRUE;
    }

    pstXsdCampedSysInfo = CNAS_XSD_GetCurCampedSysInfo();

    if (NAS_MSCC_PIF_CFREQ_LOCK_SET_MODE_ENABLE == pstCFreqLockNtf->enFreqLockMode)
    {
        /* 当前驻留系统的参数与即将锁频参数相同时，不触发搜网 */
        if ((VOS_TRUE == pstXsdCampedSysInfo->ucCampOnFlag)
         && (pstXsdCampedSysInfo->stSystem.stFreq.usChannel   == pstCFreqLockSetPara->usCdmaFreq)
         && (pstXsdCampedSysInfo->stSystem.stFreq.enBandClass == pstCFreqLockSetPara->usCdmaBandClass))
        {
            if (VOS_TRUE == CNAS_PRL_Is1xSysIdMatched(pstXsdCampedSysInfo->stSystem.usSid, pstXsdCampedSysInfo->stSystem.usNid,
                                                      pstCFreqLockSetPara->usSid, pstCFreqLockSetPara->usNid))
            {
                return VOS_TRUE;
            }
        }

        /* IDLE状态下触发搜网 */
        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_CFREQ_LOCK, 0, VOS_NULL_PTR);
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccCdmaCsqSetReq_PreProc
 功能描述  : 传递CdmaCsq的设置参数给CAS
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月25日
    作    者   : m00312079
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCdmaCsqSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_CDMACSQ_SET_REQ_STRU         *pstCdmaCsqReq = VOS_NULL_PTR;

    pstCdmaCsqReq = (MSCC_XSD_CDMACSQ_SET_REQ_STRU *)pstMsg;

    /* 发送给CAS */
    if (VOS_TRUE != CNAS_XSD_SndCasCdmaCsqSetReq(pstCdmaCsqReq->stCdmaCsq.ucRssiRptThreshold,
                                                 pstCdmaCsqReq->stCdmaCsq.ucEcIoRptThreshold,
                                                 pstCdmaCsqReq->stCdmaCsq.ucTimeInterval))
    {
        CNAS_XSD_SndCdmaCsqSetCnf(NAS_MSCC_PIF_CDMACSQ_SET_RESULT_FAIL);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvCasCdmaCsqSetCnf_PreProc
 功能描述  : XSD从CAS收到CdmaCsq的设置结果
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月26日
    作    者   : m00312079
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCasCdmaCsqSetCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_SET_SIGNAL_QUALITY_CNF_STRU                *pstCdmaCsqCnf = VOS_NULL_PTR;

    pstCdmaCsqCnf = (CAS_CNAS_1X_SET_SIGNAL_QUALITY_CNF_STRU *)pstMsg;

    if (CAS_CNAS_1X_SIGNAL_QUALITY_CNF_RSLT_SUCCESS == pstCdmaCsqCnf->enRslt)
    {
        CNAS_XSD_SndCdmaCsqSetCnf(NAS_MSCC_PIF_CDMACSQ_SET_RESULT_SUCC);
    }
    else
    {
        CNAS_XSD_SndCdmaCsqSetCnf(NAS_MSCC_PIF_CDMACSQ_SET_RESULT_FAIL);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvCasCdmaCsqInd_PreProc
 功能描述  : CAS主动上报CdmaCsq
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月27日
    作    者   : m00312079
    修改内容   : 新生成函数

  2.日    期   : 2015年10月16日
    作    者   : m00312079
    修改内容   : DTS2015101505057:添加ec/Io的上报门限

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCasCdmaCsqInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_SIGNAL_QUALITY_IND_STRU  *pstCdmaCsqInd = VOS_NULL_PTR;

    pstCdmaCsqInd = (CAS_CNAS_1X_SIGNAL_QUALITY_IND_STRU  *)pstMsg;

    CNAS_XSD_SndCdmaCsqInd(pstCdmaCsqInd->sCdmaRssi, pstCdmaCsqInd->sCdmaEcIo);

    return VOS_TRUE;

}
#if 0
/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvCasNegativeSystemQuery_PreProc
 功能描述  : 收到CAS查询系统是否是negative系统
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月9日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCasNegativeSystemQueryInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_NEGATIVE_SYSTEM_QUERY_IND_STRU             *pstQueryInd     = VOS_NULL_PTR;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                         stNegativeFreqList;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                         stSrcFreqInfo;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                         stDstFreqInfo;
    CNAS_PRL_1X_SYSTEM_ID_STRU                              stSysId;
    VOS_UINT32                                              i;

    pstQueryInd = (CAS_CNAS_1X_NEGATIVE_SYSTEM_QUERY_IND_STRU *)pstMsg;

    NAS_MEM_SET_S(&stNegativeFreqList, 0x0, sizeof(stNegativeFreqList));
    NAS_MEM_SET_S(&stSysId, 0x0, sizeof(stSysId));
    NAS_MEM_SET_S(&stSrcFreqInfo, 0x0, sizeof(stSrcFreqInfo));
    NAS_MEM_SET_S(&stDstFreqInfo, 0x0, sizeof(stDstFreqInfo));

    stSysId.usSid = pstQueryInd->stCurrSysId.usSid;
    stSysId.usNid = pstQueryInd->stCurrSysId.usNid;

    for (i = 0; i < pstQueryInd->ulFreqNum; i++)
    {
        stSrcFreqInfo.astFreqInfo[i].enBandClass = pstQueryInd->astFreqList[i].usBandClass;
        stSrcFreqInfo.astFreqInfo[i].usChannel   = pstQueryInd->astFreqList[i].usChannel;
    }
    stSrcFreqInfo.ulNum = pstQueryInd->ulFreqNum;

    /* 这里不做band能力支持检查，由CAS负责检查 */

    /* filter out negative freqs */
    CNAS_XSD_RemoveNegativeFreqs(&stSysId, &stSrcFreqInfo, &stDstFreqInfo);

    for (i = 0; i < stSrcFreqInfo.ulNum; i++)
    {
        if (VOS_FALSE == CNAS_XSD_IsChannelInChannelList(&stSrcFreqInfo.astFreqInfo[i],
                                                          (VOS_UINT16)stDstFreqInfo.ulNum,
                                                          &(stDstFreqInfo.astFreqInfo[0])))
        {
            stNegativeFreqList.astFreqInfo[stNegativeFreqList.ulNum] = stSrcFreqInfo.astFreqInfo[i];

            (stNegativeFreqList.ulNum)++;
        }
    }

    CNAS_XSD_SndCasNegativeSystemQueryRsp(&pstQueryInd->stCurrSysId, &stNegativeFreqList);

    return VOS_TRUE;
}
#endif
/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvCas1xSyncTimeInd_PreProc
 功能描述  : 收到CAS上报1X的系统时间
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE
             VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月4日
    作    者   : L00256032
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCas1xSyncTimeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_SYNC_TIME_IND_STRU      *pstSyncTimeInd = VOS_NULL_PTR;
    NAS_MSCC_PIF_1X_SYS_TIME_STRU        st1xSysTime;

    pstSyncTimeInd = (CAS_CNAS_1X_SYNC_TIME_IND_STRU *)pstMsg;

    NAS_MEM_CPY_S(st1xSysTime.aucSysTime,
                  sizeof(st1xSysTime.aucSysTime),
                  pstSyncTimeInd->stSysTime.aucSysTime,
                  sizeof(pstSyncTimeInd->stSysTime.aucSysTime));
    st1xSysTime.ucLpSec = pstSyncTimeInd->stSysTime.ucLpSec;
    st1xSysTime.cLtmOff = pstSyncTimeInd->stSysTime.cLtmOff;
    st1xSysTime.ucDaylt = pstSyncTimeInd->stSysTime.ucDaylt;

    CNAS_XSD_SndMscc1xSysTimeInd(&st1xSysTime);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccSysCfgReq_PreProc
 功能描述  : 透传系统配置消息给CAS
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月13日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccSysCfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_SYS_CFG_REQ_STRU          *pstSysReq = VOS_NULL_PTR;

    pstSysReq = (MSCC_XSD_SYS_CFG_REQ_STRU *)pstMsg;

    /* 发送给CAS */
    CNAS_XSD_SndCasSysCfgReq(pstSysReq);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvCas1xSysCfgCnf_PreProc
 功能描述  : 透传系统配置消息Cnf给Mscc
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月14日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCas1xSysCfgCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_SYS_CFG_CNF_STRU       *pstSysCnf = VOS_NULL_PTR;

    pstSysCnf = (CAS_CNAS_1X_SYS_CFG_CNF_STRU *)pstMsg;

    /* 发送给CAS */
    CNAS_XSD_SndMsccSysCfgCnf(pstSysCnf);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccHandsetInfoQry_PreProc
 功能描述  : 收到MSCC的手机信息查询请求
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE
             VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : z00316370
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccHandsetInfoQry_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_HANDSET_INFO_QRY_STRU     *pstInfoMsg = VOS_NULL_PTR;

    pstInfoMsg = (MSCC_XSD_HANDSET_INFO_QRY_STRU *)pstMsg;

    CNAS_HandsetInfoQry_Proc((VOS_UINT32)pstInfoMsg->ulInfoType);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvCas1xEnterRelSubStateReasonInd_PreProc
 功能描述  : 收到CAS进入release substate的原因值指示
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE
             VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月13日
    作    者   : m00312079
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCas1xEnterRelSubStateReasonInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_ENTER_RELEASE_SUBSTATE_REASON_IND_STRU     *pst1xEnterRelSubStateResonInd;

    pst1xEnterRelSubStateResonInd = (CAS_CNAS_1X_ENTER_RELEASE_SUBSTATE_REASON_IND_STRU *)pstMsg;

    /*  Ref to C.S0005-A_v6.0 2.6.4.4,following release subState should set the returnCause to 0x00(NORMAL_ACCESS)
        1.mobile station enters the Release Substate with a mobile station release indication;
        2.mobile station enters the Release Substate with a service inactive indication;
        3.mobile station enters the Release Substate with a base station release indication;
        4.mobile station enters the Release Substate with a base station extended release indication;
        5.mobile station enters the Release Substate with a base station extended release with mini message indication;
    */

    switch (pst1xEnterRelSubStateResonInd->enReason)
    {
        case CAS_CNAS_1X_ENTER_RELEASE_SUBSTATE_REASON_MS_RELEASE_INDICATION :
        case CAS_CNAS_1X_ENTER_RELEASE_SUBSTATE_REASON_SERVICE_INACTIVE_INDICATION :
        case CAS_CNAS_1X_ENTER_RELEASE_SUBSTATE_REASON_BS_RELEASE_INDICATION :
        case CAS_CNAS_1X_ENTER_RELEASE_SUBSTATE_REASON_BS_EXTEND_RELEASE_INDICATION :
        case CAS_CNAS_1X_ENTER_RELEASE_SUBSTATE_REASON_BS_EXTEND_RELEASE_WITH_MINI_INDICATION :
             CNAS_CCB_Set1xReturnCause(CNAS_CCB_1X_RETURN_CAUSE_NORMAL_ACCESS);
             break;

        default:
             CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvCas1xEnterRelSubStateReasonInd_PreProc: unknown release substate reason!");
             break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvRrmStatusInd_PreProc
 功能描述  : 收到RRM NO RF状态指示的时候，进行RRM模块的事件去注册
 输入参数  : 消息
 输出参数  : 无
 返 回 值  : VOS_UINT32
             VOS_FALSE : 继续处理
             VOS_TRUE  : 处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvRrmStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 向RRM发送去注册消息 */
    CNAS_XSD_DeRegisterRrmResourceNtf(RRM_PS_TASK_TYPE_1X_NETWORK_SEARCH);

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccSrvAcqReq_PreProc
 功能描述  : 收到MSCC业务触发搜网的预处理
 输入参数  : 消息
 输出参数  : 无
 返 回 值  : VOS_UINT32
             VOS_FALSE : 继续处理
             VOS_TRUE  : 处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   : h00313353
    修改内容   : 新生成函数

  2.日    期   : 2015年7月20日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccSrvAcqReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Srv Acq打断处理 */
    CNAS_XSD_SetSrvAcqFlg(VOS_TRUE);

    /* 打断消息二次进入预处理，直接进入状态机处理 */
    if (VOS_NULL_PTR != CNAS_XSD_GetEmcCallRedialScanChanListAddr()->pstScanChanInfo)
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == CNAS_XSD_GetSystemCampOnFlag())
    {
        CNAS_XSD_SndMsccSrvAcqCnf(NAS_MSCC_PIF_SRV_ACQ_RESULT_SUCCESS);

        CNAS_XSD_SetSrvAcqFlg(VOS_FALSE);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccBeginSessionNotify_PreProc
 功能描述  : 收到MSCC资源申请请求的处理:向CAS发送资源申请请求
 输入参数  : 消息
 输出参数  : 无
 返 回 值  : VOS_UINT32
             VOS_FALSE : 继续处理
             VOS_TRUE  : 处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccBeginSessionNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                    enSessionType;

    enSessionType = CNAS_XSD_ConvertSrvTypeToSessionType(((MSCC_XSD_BEGIN_SESSION_NOTIFY_STRU *)pstMsg)->enSrvType);

    /* 向CAS发送资源申请请求 */
    CNAS_XSD_SndCasBeginSessionNotify(enSessionType);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccEndSessionNotify_PreProc
 功能描述  : 收到MSCC资源申请请求的处理:向CAS发送资源释放请求
 输入参数  : 消息
 输出参数  : 无
 返 回 值  : VOS_UINT32
             VOS_FALSE : 继续处理
             VOS_TRUE  : 处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccEndSessionNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                    enSessionType;

    enSessionType = CNAS_XSD_ConvertSrvTypeToSessionType(((MSCC_XSD_END_SESSION_NOTIFY_STRU *)pstMsg)->enSrvType);

    /* 向CAS发送资源释放请求 */
    CNAS_XSD_SndCasEndSessionNotify(enSessionType);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_PreProc
 功能描述  : 收到MSCC呼叫重播的预处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
             VOS_FALSE : 继续处理
             VOS_TRUE  : 处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月02日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU           *pstCallRedialSysAcqNtf = VOS_NULL_PTR;

    pstCallRedialSysAcqNtf                                  = (MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU *)pstMsg;

    if ((NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_EMC_VOICE_CALL      == pstCallRedialSysAcqNtf->enCallType)
     || (NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_NORMAL_VOICE_CALL   == pstCallRedialSysAcqNtf->enCallType))
    {
        return VOS_FALSE;
    }

    if (NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_NORMAL_DATA_CALL     == pstCallRedialSysAcqNtf->enCallType)
    {
        /* CallBack流程中不处理普通数据呼的重拨 */
        if (CNAS_XSD_EMC_STATE_CALLBACK                     == CNAS_XSD_GetEmcState())
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }

    /* 其他消息不进入状态机处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccEndCallBackNtf_PreProc
 功能描述  : 收到MSCC退出CallBack模式指示的预处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
             VOS_FALSE : 继续处理
             VOS_TRUE  : 处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月02日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccEndCallBackNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 若当前不处于CALLBACK模式，做异常处理 */
    if (CNAS_XSD_EMC_STATE_CALLBACK != CNAS_XSD_GetEmcState())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiCallBackModeTimerExpired_PreProc
 功能描述  : 收到CallBack Nv定时器超的预处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
             VOS_FALSE : 继续处理
             VOS_TRUE  : 处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月02日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiCallBackModeTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 若当前不处于CALLBACK模式，做异常处理 */
    if (CNAS_XSD_EMC_STATE_CALLBACK != CNAS_XSD_GetEmcState())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiCallBackSrchTimerExpired_PreProc
 功能描述  : 收到CallBack 15s搜网定时器超的预处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
             VOS_FALSE : 继续处理
             VOS_TRUE  : 处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月02日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiCallBackSrchTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 若当前不处于CALLBACK模式，做异常处理 */
    if (CNAS_XSD_EMC_STATE_CALLBACK != CNAS_XSD_GetEmcState())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccCSidListReq_PreProc
 功能描述  : 收到MSCC Sid白名单设置请求的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
             VOS_TRUE  : 处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月02日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCSidListReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_SET_CSIDLIST_REQ_STRU                         *pstOperLockSysWhite     = VOS_NULL_PTR;
    CNAS_CCB_OPER_LOCK_SYS_WHITE_LIST_STRU                 *pstOperLockSysWhiteList = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstOperLockSysWhite                 = (MSCC_XSD_SET_CSIDLIST_REQ_STRU *)pstMsg;

    /* NV写入成功 */
    if (VOS_TRUE == CNAS_XSD_WriteOperLockWhiteSidListInfoNvim((MSCC_XSD_OPER_LOCK_SYS_WHITE_STRU *)(&pstOperLockSysWhite->stSidWhiteList)))
    {
        /* 存储到全局变量 */
        pstOperLockSysWhiteList                = CNAS_CCB_GetOperLockSysWhiteList();
        pstOperLockSysWhiteList->ucEnable      = pstOperLockSysWhite->stSidWhiteList.ucEnable;
        pstOperLockSysWhiteList->usWhiteSysNum = CNAS_MIN(pstOperLockSysWhite->stSidWhiteList.usWhiteSysNum, CNAS_CCB_MAX_WHITE_LOCK_SYS_NUM);

        for (i = 0; i < pstOperLockSysWhiteList->usWhiteSysNum;i++ )
        {
            pstOperLockSysWhiteList->astSysInfo[i].usStartSid = pstOperLockSysWhite->stSidWhiteList.astSysInfo[i].usStartSid;
            pstOperLockSysWhiteList->astSysInfo[i].usEndSid   = pstOperLockSysWhite->stSidWhiteList.astSysInfo[i].usEndSid;
            pstOperLockSysWhiteList->astSysInfo[i].ulMcc      = pstOperLockSysWhite->stSidWhiteList.astSysInfo[i].ulMcc;
        }

        CNAS_XSD_LogOperLockSysWhiteList(pstOperLockSysWhiteList);

        /* 上报MSCC设置成功 */
        CNAS_XSD_SndMsccSetCSidListCnf(VOS_TRUE);

        return VOS_TRUE;
    }

    /* 上报MSCC设置失败 */
    CNAS_XSD_SndMsccSetCSidListCnf(VOS_FALSE);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvCASStateInd_PreProc
 功能描述  : 收到cas state ind的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
             VOS_TRUE  : 处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月11日
    作    者   : C00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCasStateInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_CAS_STATE_IND_STRU     *pstStateInd;

    pstStateInd = (CAS_CNAS_1X_CAS_STATE_IND_STRU*)pstMsg;

    /* 进入tch态，清空avoid频点信息*/
    if (CAS_CNAS_1X_CAS_TCH_STATE == pstStateInd->enCasState)
    {
        CNAS_XSD_ClearAccessSuccessFreqFormAvoidList();
    }

    /* UE 状态发送給XREG*/
    CNAS_XSD_SndXregUeStateInd(pstStateInd->enCasState,
                               pstStateInd->enCasSubState);

    /* UE 状态发送給MSCC*/
    CNAS_XSD_SndMsccUeStatusInd(pstStateInd->enCasState,
                                pstStateInd->enCasSubState);
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvCasAvailableCampQueryReq_PreProc
 功能描述  : 收到CAS查询当前系统能否驻留的查询处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE
             VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月28日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCasAvailableCampQueryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_AVAILABLE_CAMP_QUERY_REQ_STRU              *pstQueryReq = VOS_NULL_PTR;
    CNAS_PRL_1X_SYSTEM_STRU                                 stCurSysInfo;
    PS_BOOL_ENUM_UINT8                                      enIsCurSysCanCamp;

    pstQueryReq = (CAS_CNAS_1X_AVAILABLE_CAMP_QUERY_REQ_STRU*)pstMsg;

    NAS_MEM_SET_S(&stCurSysInfo, sizeof(stCurSysInfo), 0x00, sizeof(stCurSysInfo));
    stCurSysInfo.stFreq.enBandClass = (CNAS_PRL_BAND_CLASS_ENUM_UINT16)pstQueryReq->usBandClass;
    stCurSysInfo.stFreq.usChannel   = pstQueryReq->usFreq;
    stCurSysInfo.usSid              = pstQueryReq->usSid;
    stCurSysInfo.usNid              = pstQueryReq->usNid;

    /* 该函数返回VOS_TRUE，表示不可以驻留 */
    if (VOS_TRUE == CNAS_XSD_IsCurSysNotSuitableSys(&stCurSysInfo, VOS_FALSE, 0))
    {
        /* 接口定义0表示可以驻留，其他值表示不能驻留，与内部接口正好相反 */
        enIsCurSysCanCamp = PS_FALSE;
    }
    else
    {
        enIsCurSysCanCamp = PS_TRUE;
    }

    CNAS_XSD_SndCasAvailableCampQueryCnf(pstQueryReq->usOpId, enIsCurSysCanCamp);

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvXregRegSuccessInd_PreProc
 功能描述  : 收到RegSuccessInd的处理, 清除avoid频点信息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
             VOS_TRUE  : 处理成功
  1.日    期   : 2015年12月5日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvXregRegSuccessInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAX_XSD_CAMPED_SYS_INFO_STRU      *pstCampedSysInfo = VOS_NULL_PTR;
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pstAvoidFreqList    = CNAS_XSD_GetAvoidFreqListAddr();

    ucIndex             = 0;

    pstCampedSysInfo = CNAS_XSD_GetCurCampedSysInfo();

    if (VOS_TRUE == CNAS_XSD_GetAvoidFreqIndexOfAvoidlist(&(pstCampedSysInfo->stSystem.stFreq), &ucIndex))
    {

        CNAS_XSD_ClearAvoidCountFromAvoidList(ucIndex, CNAS_XSD_AVOID_REG_REJECTED);

        if (VOS_TRUE == CNAS_XSD_IsClearFreqInfoOfAvoidList(ucIndex))
        {
            CNAS_XSD_ClearAvoidFreqInfoOfAvoidList(ucIndex);

            /*如果avoid列表中不存在禁用标记，表示没有被禁用的频点，停止定时器 */
            if (VOS_FALSE == CNAS_XSD_IsExistAvoidFlagInAvoidlist())
            {
                CNAS_XSD_StopTimer(TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER);
            }
        }

        CNAS_XSD_LogAvoidFreqList(pstAvoidFreqList);
    }

    return VOS_TRUE;
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



