/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcProcSuspend.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2011年8月03日
  最近修改   :
  功能描述   : MMC处理异系统挂起时的相关公共处理函数
  函数列表   :
  修改历史   :
  1.日    期   : 2011年08月03日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasMmlCtx.h"
#include "NasMmcCtx.h"
#include "NasComm.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndLmm.h"
#include "NasMmlLib.h"
#include "NasMmcProcSuspend.h"
/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
#include "NasMmcSndOm.h"
/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */
#include "NasMmcSndInternalMsg.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_PROC_SUSPEND_C

/*****************************************************************************
  2 全局变量
*****************************************************************************/

/*****************************************************************************
  3 宏定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************此处为异系统挂起时公共调用的函数抽取********************************************/
#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertLmmSysChngTypeToMmcType
 功能描述  : 将LMM上报的异系统重选类型转换为MMC内部的重选类型
 输入参数  : MMC_LMM_SYS_CHNG_TYPE_ENUM_UINT32   enSysChngType,
 输出参数  : MMC_SUSPEND_CAUSE_ENUM_UINT8       *penSuspendCause
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月14日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整
  3.日    期   : 2012年04月24日
    作    者   : w00166186
    修改内容   : DTS2012042303735，从L CCO到G后再重选会L，第一次TAU失败
*****************************************************************************/
VOS_VOID NAS_MMC_ConvertLmmSysChngTypeToMmcType(
    MMC_LMM_SYS_CHNG_TYPE_ENUM_UINT32   enSysChngType,
    MMC_SUSPEND_CAUSE_ENUM_UINT8       *penSuspendCause
)
{
    switch ( enSysChngType )
    {
        case MMC_LMM_SUS_TYPE_RSL :
            *penSuspendCause = MMC_SUSPEND_CAUSE_CELLRESELECT;
            break;

        case MMC_LMM_SUS_TYPE_HO :
            *penSuspendCause = MMC_SUSPEND_CAUSE_HANDOVER;
            break;

        case MMC_LMM_SUS_TYPE_CCO :
            *penSuspendCause = MMC_SUSPEND_CAUSE_CELLCHANGE;
            break;

        case MMC_LMM_SUS_TYPE_REDIR :
            *penSuspendCause = MMC_SUSPEND_CAUSE_REDIRECTION;
            break;

        case MMC_LMM_SUS_TYPE_CCO_REVERSE :
            *penSuspendCause = MMC_SUSPEND_CAUSE_CELLCHANGE_FALLBACK;
            break;

        default:
            *penSuspendCause = MMC_SUSPEND_CAUSE_BUTT;
            break;
    }
    return;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertLmmSysChngDirToMmcType
 功能描述  : 将LMM上报的异系统重选方向类型转换为MMC内部的重选方向搜类型
 输入参数  : MMC_LMM_SYS_CHNG_DIR_ENUM_UINT32    ulSysChngDir,
 输出参数  : penSuspendDestination:挂起目的方
             penSuspendOrigen:挂起发起方
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月14日
    作    者   : w00167002
    修改内容   : 新生成函数
 2. 日    期   : 2011年8月03日
    作    者   : w00176964
    修改内容   : V7R1 Phase II调整:增加挂起发起方
 3. 日    期   : 2014年1月26日
    作    者   : s00246516
    修改内容   : L-C互操作项目增加到Lte到CDMA的重选或重定向
*****************************************************************************/
VOS_VOID NAS_MMC_ConvertLmmSysChngDirToMmcType(
    MMC_LMM_SYS_CHNG_DIR_ENUM_UINT32    ulSysChngDir,
    MMC_SUSPEND_DESTINATION_UINT8      *penSuspendDestination,
    MMC_SUSPEND_ORIGEN_UINT8           *penSuspendOrigen
)
{
    switch ( ulSysChngDir )
    {
        case MMC_LMM_SYS_CHNG_DIR_L2W:
            *penSuspendDestination  = MMC_SUSPEND_DESTINATION_WCDMA;
            *penSuspendOrigen       = MMC_SUSPEND_ORIGEN_LTE;
            break;

        case MMC_LMM_SYS_CHNG_DIR_L2G:
            *penSuspendDestination  = MMC_SUSPEND_DESTINATION_GSM;
            *penSuspendOrigen       = MMC_SUSPEND_ORIGEN_LTE;
            break;

        case MMC_LMM_SYS_CHNG_DIR_G2L:
            *penSuspendDestination  = MMC_SUSPEND_DESTINATION_LTE;
            *penSuspendOrigen       = MMC_SUSPEND_ORIGEN_GSM;
            break;

        case MMC_LMM_SYS_CHNG_DIR_W2L:
            *penSuspendDestination  = MMC_SUSPEND_DESTINATION_LTE;
            *penSuspendOrigen       = MMC_SUSPEND_ORIGEN_WCDMA;
            break;

        /* Added by s00246516 for L-C互操作项目, 2014-01-26, Begin */
        /* 增加L2C case的处理，发起方为LTE，目的方为CDMA */
        case MMC_LMM_SYS_CHNG_DIR_L2C:
            *penSuspendDestination  = MMC_SUSPEND_DESTINATION_HRPD;
            *penSuspendOrigen       = MMC_SUSPEND_ORIGEN_LTE;
            break;
        /* Added by s00246516 for L-C互操作项目, 2014-01-26, End */

        default:
            *penSuspendDestination  = MMC_SUSPEND_DESTINATION_BUTT;
            *penSuspendOrigen       = MMC_SUSPEND_ORIGEN_BUTT;
            break;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertLmmSuspendMsgToGUtype
 功能描述  : 将LMM上报的异系统重选方向类型转换为MMC内部的重选方向搜类型
 输入参数  : pstLmmSuspendIndMsg:LTE的挂起消息
 输出参数  : pstGuSuspendIndMsg:GU的挂起消息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月03日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID    NAS_MMC_ConvertLmmSuspendMsgToGUtype(
    LMM_MMC_SUSPEND_IND_STRU           *pstLmmSuspendIndMsg,
    RRMM_SUSPEND_IND_ST                *pstGuSuspendIndMsg
)
{
    /* 转换L的挂起类型为GU格式的*/
    NAS_MMC_ConvertLmmSysChngTypeToMmcType(pstLmmSuspendIndMsg->ulSysChngType,&(pstGuSuspendIndMsg->ucSuspendCause));

    /* L模下，SUSPEND方向定义与GU下不同，转换一下SUSPEND方向定义 */
    NAS_MMC_ConvertLmmSysChngDirToMmcType(pstLmmSuspendIndMsg->ulSysChngDir,
                                          &(pstGuSuspendIndMsg->ucSuspendDestination),
                                          &(pstGuSuspendIndMsg->ucSuspendOrigen));

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmEquPlmn_InterSysChangeLte
 功能描述  : 异系统到L时，向LMM发送等效网络列表
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月01日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2012年8月21日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改
  3.日    期   : 2012年10月23日
    作    者   : z00161729
    修改内容   : DTS2012082401763:异系统到L通知L等效plmn时需要删除forbidden plmn
  4.日    期   : 2013年12月18日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseIII项目

  5.日    期   : 2014年1月9日
    作    者   : w00167002
    修改内容   : DTS2014010305488:在L下24005上注册成功，用户指定搜46009，用户发起紧急
               呼叫，在W下ANYCELL驻留后发起紧急电话业务。后W异系统重选到L下得24005
               网络上，LMM直接给MMC上报TAU成功。
  6.日    期   : 2015年8月13日
    作    者   : l00289540
    修改内容   : User_Exp_Improve修改
  7.日    期   : 2015年12月02日
    作    者   : j00174725
    修改内容   : DTS2015102004448
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmEquPlmn_InterSysChangeLte()
{
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmnId   = VOS_NULL_PTR;
    VOS_UINT32                                              ulEplmnValidFlg;
    VOS_UINT32                                              ulRegFlag;
    VOS_UINT32                                              ulIsSimPlmnIdInDestBcchPlmnList;
    VOS_UINT32                                              ulIsBcchPlmnIdInDestSimPlmnList;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
    pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
    PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    pstUserSpecPlmnId = NAS_MMC_GetUserSpecPlmnId();

    ulEplmnValidFlg     = NAS_MML_GetEplmnValidFlg();
    ulRegFlag           = NAS_MMC_GetUserSpecPlmnRegisterStatus();

    ulIsSimPlmnIdInDestBcchPlmnList = NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&(pstUserSpecPlmnId->stPlmnId),
                                                                            stSndEquPlmnInfo.ucEquPlmnNum,
                                                                            stSndEquPlmnInfo.astEquPlmnAddr);

    ulIsBcchPlmnIdInDestSimPlmnList = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(pstUserSpecPlmnId->stPlmnId),
                                                                            stSndEquPlmnInfo.ucEquPlmnNum,
                                                                            stSndEquPlmnInfo.astEquPlmnAddr);

    /* 手动模式下，如果用户指定的网络不在EPLMN列表中，则通知LMM当前的EPLMN信息为用户指定的网络
       否则通知LMM当前EPLMN信息 */
    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        if ( (VOS_FALSE == ulIsSimPlmnIdInDestBcchPlmnList)
           && (VOS_FALSE == ulIsBcchPlmnIdInDestSimPlmnList) )
        {
            if ( (VOS_TRUE == ulRegFlag)                                        /* 指定PLMN注册成功 */
              && (VOS_TRUE == ulEplmnValidFlg) )                                /* EPLMN 标志存在 */
            {
                /* 将指定搜放在最后 */
                stSndEquPlmnInfo.ucEquPlmnNum++;
                stSndEquPlmnInfo.ucEquPlmnNum = (stSndEquPlmnInfo.ucEquPlmnNum <= NAS_MML_MAX_EQUPLMN_NUM) ? stSndEquPlmnInfo.ucEquPlmnNum : NAS_MML_MAX_EQUPLMN_NUM;
                stSndEquPlmnInfo.astEquPlmnAddr[stSndEquPlmnInfo.ucEquPlmnNum - 1].ulMcc = pstUserSpecPlmnId->stPlmnId.ulMcc;
                stSndEquPlmnInfo.astEquPlmnAddr[stSndEquPlmnInfo.ucEquPlmnNum - 1].ulMnc = pstUserSpecPlmnId->stPlmnId.ulMnc;
            }
            else
            {
                /* 只准备通知用户指定的网络 */
                stSndEquPlmnInfo.ucEquPlmnNum = 1;
                stSndEquPlmnInfo.astEquPlmnAddr[0].ulMcc = pstUserSpecPlmnId->stPlmnId.ulMcc;
                stSndEquPlmnInfo.astEquPlmnAddr[0].ulMnc = pstUserSpecPlmnId->stPlmnId.ulMnc;
            }
        }
    }

    NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
    NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
    NAS_MMC_SndOmEquPlmn();
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */

    return;
}

#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_SndAsSuspendRsp
 功能描述  : 向接入层发送挂起回复
 输入参数  : enRat:需要发送的接入技术
             enSuspendRslt:挂起结果
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月03日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID    NAS_MMC_SndSuspendRsp(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    RRC_NAS_SUSPEND_RESULT_ENUM_UINT8   enSuspendRslt
)
{
#if (FEATURE_ON == FEATURE_LTE)
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulRslt;

    if ( RRC_NAS_SUSPEND_SUCCESS == enSuspendRslt)
    {
        ulRslt = MMC_LMM_SUCC;
    }
    else
    {
        ulRslt = MMC_LMM_FAIL;
    }

#endif

    switch(enRat)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
            NAS_MMC_SndAsSuspendRsp(enSuspendRslt, UEPS_PID_GAS);
            break;
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_MMC_SndAsSuspendRsp(enSuspendRslt, WUEPS_PID_WRR);
            break;
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            NAS_MMC_SndLmmSuspendRsp(ulRslt);
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSuspendRsp:Unexpected Rat Type!");
            break;
    }

}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndResumeRsp
 功能描述  : 向接入层发送恢复回复
 输入参数  : enRat:当前接入技术
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月03日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID    NAS_MMC_SndResumeRsp(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    switch(enRat)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            /* 发送RRMM_RESUME_RSP */
            NAS_MMC_SndAsResumeRsp(WUEPS_PID_WRR);

#if (FEATURE_ON == FEATURE_LTE)
            /* 通知LMM恢复结果 */
            if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
            {
                NAS_MMC_SndLmmResumeNotify();
            }

#endif
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:
            NAS_MMC_SndAsResumeRsp(UEPS_PID_GAS);

#if (FEATURE_ON == FEATURE_LTE)
            if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
            {
                NAS_MMC_SndLmmResumeNotify();
            }

#endif
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndResumeRsp:Unexpected Rat Type!");
            break;
    }

    return;
}




/*****************************************************************************
 函 数 名  : NAS_MMC_BulidResumeMsg
 功能描述  : 构造恢复消息
 输入参数  : enRat:需要那个接入技术进行恢复
 输出参数  : pstMsg:构造后的消息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月03日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID    NAS_MMC_BulidResumeMsg(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    RRMM_RESUME_IND_ST                 *pstMsg
)
{
    switch(enRat)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
            pstMsg->ucResumeOrigen = MMC_RESUME_ORIGEN_GSM;
            break;
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            pstMsg->ucResumeOrigen = MMC_RESUME_ORIGEN_WCDMA;
            break;
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            pstMsg->ucResumeOrigen = MMC_RESUME_ORIGEN_LTE;
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_BulidResumeMsg:Unexpected Rat Type!");
            return;
    }

    pstMsg->ucCsResumeResult = MMC_RESUME_RESULT_SUCCESS;
    pstMsg->ucPsResumeResult = MMC_RESUME_RESULT_SUCCESS;

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetSuspendOrigenRatType
 功能描述  : 获取挂起前的网络类型
 输入参数  : pstEntryMsg :状态机的入口消息
 输出参数  :
 返 回 值  : 挂起前的网络类型
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月03日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2015年6月6日
    作    者   : l00324781
    修改内容   : Iteration 12修改

*****************************************************************************/
NAS_MML_NET_RAT_TYPE_ENUM_UINT8    NAS_MMC_GetSuspendOrigenRatType(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
#if   (FEATURE_ON == FEATURE_LTE)
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg      = VOS_NULL_PTR;
#endif
    RRMM_SUSPEND_IND_ST                 stGuSuspendMsg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    enRat   = NAS_MML_NET_RAT_TYPE_BUTT;

    /* 根据消息类型，转换入口消息 */
    switch (pstEntryMsg->ulEventType)
    {
        case NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND):
        case NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND):
            stGuSuspendMsg   = *(RRMM_SUSPEND_IND_ST*)(pstEntryMsg->aucEntryMsgBuffer);
            break;
#if   (FEATURE_ON == FEATURE_LTE)
        case NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SUSPEND_IND):
            pstLSuspendMsg   = (LMM_MMC_SUSPEND_IND_STRU*)(pstEntryMsg->aucEntryMsgBuffer);

            /* 转换L的挂起消息为GU的 */
            NAS_MMC_ConvertLmmSuspendMsgToGUtype(pstLSuspendMsg, &stGuSuspendMsg);
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendOrigenRatType:Invalid Event Type!");
            return enRat;
    }

    /* 根据挂起目的方，获取挂起前的网络类型 */
    switch(stGuSuspendMsg.ucSuspendOrigen)
    {
        case MMC_SUSPEND_ORIGEN_GSM:
            enRat = NAS_MML_NET_RAT_TYPE_GSM;
            break;
        case MMC_SUSPEND_ORIGEN_WCDMA:
            enRat = NAS_MML_NET_RAT_TYPE_WCDMA;
            break;
#if (FEATURE_ON == FEATURE_LTE)
        case MMC_SUSPEND_ORIGEN_LTE:
            enRat = NAS_MML_NET_RAT_TYPE_LTE;
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendOrigenRatType:Unexpected Rat Type!");
            return enRat;
    }

    return enRat;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetSuspendDestinationRatType
 功能描述  : 获取挂起目的方的网络类型
 输入参数  : pstEntryMsg :状态机的入口消息
 输出参数  :
 返 回 值  : 挂起目的方的网络类型
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月13日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_NET_RAT_TYPE_ENUM_UINT8    NAS_MMC_GetSuspendDestinationRatType(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
#if   (FEATURE_ON == FEATURE_LTE)
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg      = VOS_NULL_PTR;
#endif
    RRMM_SUSPEND_IND_ST                 stGuSuspendMsg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    enRat   = NAS_MML_NET_RAT_TYPE_BUTT;

    /* 根据消息类型，转换入口消息 */
    switch (pstEntryMsg->ulEventType)
    {
        case NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND):
        case NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND):
            stGuSuspendMsg   = *(RRMM_SUSPEND_IND_ST*)(pstEntryMsg->aucEntryMsgBuffer);
            break;

#if   (FEATURE_ON == FEATURE_LTE)
        case NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SUSPEND_IND):
            pstLSuspendMsg   = (LMM_MMC_SUSPEND_IND_STRU*)(pstEntryMsg->aucEntryMsgBuffer);

            /* 转换L的挂起消息为GU的 */
            NAS_MMC_ConvertLmmSuspendMsgToGUtype(pstLSuspendMsg, &stGuSuspendMsg);
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendDestinationRatType:Invalid Event Type!");
            return enRat;
    }

    /* 根据挂起目的方，获取挂起前的网络类型 */
    switch(stGuSuspendMsg.ucSuspendDestination)
    {
        case MMC_SUSPEND_DESTINATION_GSM:
            enRat = NAS_MML_NET_RAT_TYPE_GSM;
            break;

        case MMC_SUSPEND_DESTINATION_WCDMA:
            enRat = NAS_MML_NET_RAT_TYPE_WCDMA;
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case MMC_SUSPEND_DESTINATION_LTE:
            enRat = NAS_MML_NET_RAT_TYPE_LTE;
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendDestinationRatType:Unexpected Rat Type!");
            return enRat;
    }

    return enRat;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetSuspendCause
 功能描述  : 获取挂起类型
 输入参数  : pstEntryMsg :状态机的入口消息
 输出参数  :
 返 回 值  : 挂起类型
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月13日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
MMC_SUSPEND_CAUSE_ENUM_UINT8    NAS_MMC_GetSuspendCause(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
#if   (FEATURE_ON == FEATURE_LTE)
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg      = VOS_NULL_PTR;
#endif
    RRMM_SUSPEND_IND_ST                 stGuSuspendMsg;
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause;

    enSuspendCause = MMC_SUSPEND_CAUSE_BUTT;

    /* 根据消息类型，转换入口消息 */
    switch (pstEntryMsg->ulEventType)
    {
        case NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND):
        case NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND):
            stGuSuspendMsg   = *(RRMM_SUSPEND_IND_ST*)(pstEntryMsg->aucEntryMsgBuffer);
            enSuspendCause   = stGuSuspendMsg.ucSuspendCause;
            break;

#if   (FEATURE_ON == FEATURE_LTE)
        case NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SUSPEND_IND):
            pstLSuspendMsg   = (LMM_MMC_SUSPEND_IND_STRU*)(pstEntryMsg->aucEntryMsgBuffer);

            /* 转换L的挂起消息为GU的 */
            NAS_MMC_ConvertLmmSuspendMsgToGUtype(pstLSuspendMsg, &stGuSuspendMsg);
            enSuspendCause   = stGuSuspendMsg.ucSuspendCause;
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendOrigenRatType:Invalid Event Type!");
            return enSuspendCause;
    }

    return enSuspendCause;
}

#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE)))

/*****************************************************************************
 函 数 名  : NAS_MMC_IsInterSysReselectToHrpd
 功能描述  : 判断是否重选到HRPD
 输入参数  : pstEntryMsg :状态机的入口消息
 输出参数  :
 返 回 值  : VOS_TRUE,是；VOS_FALSE，不是
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月19日
    作    者   : s00246516
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsInterSysReselectToHrpd(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
#if   (FEATURE_ON == FEATURE_LTE)
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg      = VOS_NULL_PTR;
#endif
    RRMM_SUSPEND_IND_ST                 stGuSuspendMsg;

    /* 根据消息类型，转换入口消息 */
    switch (pstEntryMsg->ulEventType)
    {
        case NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND):
        case NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND):
            return VOS_FALSE;

#if   (FEATURE_ON == FEATURE_LTE)
        case NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SUSPEND_IND):
            pstLSuspendMsg   = (LMM_MMC_SUSPEND_IND_STRU*)(pstEntryMsg->aucEntryMsgBuffer);

            /* 转换L的挂起消息为GU的 */
            NAS_MMC_ConvertLmmSuspendMsgToGUtype(pstLSuspendMsg, &stGuSuspendMsg);
            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendOrigenRatType:Invalid Event Type!");
            return VOS_FALSE;
    }

    if (MMC_SUSPEND_DESTINATION_HRPD == stGuSuspendMsg.ucSuspendDestination)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertMsccInterSysCauseToMmcFormat
 功能描述  : 将mscc格式的挂起原因值转换为mmc格式的挂起原因值
 输入参数  : enMsccSuspendCause:mscc格式的挂起原因值
 输出参数  : 无
 返 回 值  : NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32:mmc格式的挂起原因值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月27日
    作    者   : y00346957
    修改内容   : 新生成函数

*****************************************************************************/
MMC_LMM_SYS_CHNG_TYPE_ENUM_UINT32 NAS_MMC_ConvertMsccInterSysCauseToMmcFormat(
    NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32                 enMsccSuspendCause
)
{
    MMC_LMM_SYS_CHNG_TYPE_ENUM_UINT32                       enInterSysCause;

    switch (enMsccSuspendCause)
    {
        case NAS_MSCC_PIF_INTERSYS_CAUSE_RESELECT:
            enInterSysCause = MMC_LMM_SUS_TYPE_RSL;
            break;

        case NAS_MSCC_PIF_INTERSYS_CAUSE_REDIR:
            enInterSysCause = MMC_LMM_SUS_TYPE_REDIR;
            break;

        case NAS_MSCC_PIF_INTERSYS_CAUSE_HO:
            enInterSysCause = MMC_LMM_SUS_TYPE_HO;
            break;

        default:
            enInterSysCause = MMC_LMM_SUS_TYPE_BUTT;
    }

    return enInterSysCause;
}
#endif


/*****************************************************************************
 函 数 名  : NAS_MMC_StartResumeTimer_InterSysCellResel
 功能描述  : 拼片或CL模式下，异系统切换，从LTE重选或重定向到HRPD过程中，MME收到内部模块MM或GMM的SuspendRsp消息处理
           : 根据不同切换类型，启动不同时长定时器
 输入参数  : 无
 输出参数  :
 返 回 值  : VOS_TRUE,是LTE到HRPD的切换；VOS_FALSE，不是LTE到HRPD的切换
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月8日
    作    者   : l00324781
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_StartResumeTimer_InterSysCellResel(VOS_VOID)
{
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE)))

    if (VOS_TRUE == NAS_MMC_IsInterSysReselectToHrpd(NAS_MMC_GetCurrEntryMsg()))
    {
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CMMCA_RESUME_IND, TI_NAS_MMC_WAIT_CMMCA_RESUME_IND_LEN);
#endif

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE))
        /* 重定向，定时器时长为180s */
        if (MMC_SUSPEND_CAUSE_REDIRECTION == NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg()))
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF, TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF_REDIR_LEN);
        }
        /* 重选，定时器时长为35s  */
        else /* (MMC_SUSPEND_CAUSE_CELLRESELECT == NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg())) */
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF, TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF_RESELCT_LEN);
        }
#endif

        return VOS_TRUE;
    }
    else
#endif
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcResumeRspFromLteToHrpd_InterSysCellResel
 功能描述  : 拼片或CL模式下，异系统切换，从LTE重选或重定向到HRPD过程中，MME收到内部模块MM或GMM的ResumeRsp消息处理
           : 根据不同切换类型，发送不同类型的挂起完成消息
 输入参数  : 无
 输出参数  :
 返 回 值  : VOS_TRUE,是LTE到HRPD的切换；VOS_FALSE，不是LTE到HRPD的切换
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月8日
    作    者   : l00324781
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcResumeRspFromLteToHrpd_InterSysCellResel(VOS_VOID)
{
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE)))

    if (MMC_RESUME_ORIGEN_HRPD == NAS_MMC_GetResumeOrign_InterSysCellResel())
    {
        /* 通知LMM当前已经恢复 */
        NAS_MMC_SndLmmResumeNotify();

        /* 发送状态机成功的结果 */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
        NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);
#endif

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE))

        if (MMC_SUSPEND_CAUSE_CELLRESELECT == NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg()))
        {
            NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);
        }
        else /* 非重选，即重定向 */
        {
            NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_REDIRECTION, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);
        }
#endif

        /* 退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }
    else
#endif
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertMmcInterSysCauseToMsccFormat
 功能描述  : 将MMC格式的挂起原因值转换为MSCC格式的挂起原因值
 输入参数  : enMmcSuspendCause:MMC格式的挂起原因值
 输出参数  : 无
 返 回 值  : NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32:MSCC格式的挂起原因值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月05日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32 NAS_MMC_ConvertMmcInterSysCauseToMsccFormat(
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enMmcSuspendCause
)
{
    NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32                 enInterSysCause;

    switch (enMmcSuspendCause)
    {
        case MMC_SUSPEND_CAUSE_CELLRESELECT:
            enInterSysCause = NAS_MSCC_PIF_INTERSYS_CAUSE_RESELECT;
            break;

        case MMC_SUSPEND_CAUSE_REDIRECTION:
            enInterSysCause = NAS_MSCC_PIF_INTERSYS_CAUSE_REDIR;
            break;

        case MMC_SUSPEND_CAUSE_HANDOVER:
            enInterSysCause = NAS_MSCC_PIF_INTERSYS_CAUSE_HO;
            break;

        default:
            enInterSysCause = NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_BUTT;
    }

    return enInterSysCause;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

