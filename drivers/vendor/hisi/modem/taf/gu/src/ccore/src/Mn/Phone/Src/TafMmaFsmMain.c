/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaFsmMain.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2013年7月9日
  最近修改   :
  功能描述   : 主状态机处理函数
  函数列表   :
  修改历史   :
  1.日    期   : 2013年7月9日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "TafSdcCtx.h"
#include "MmaAppLocal.h"
#include "TafMmaCtx.h"
#include "Taf_Status.h"
#include "TafMmaSndInternalMsg.h"
#include "TafMmaMain.h"
#include "TafMmaSndApp.h"
#include "TafMmaComFunc.h"


/* Added by w00167002 for L-C互操作项目, 2014-2-20, begin */
#include "TafMmaMntn.h"
/* Added by w00167002 for L-C互操作项目, 2014-2-20, end */
#include "NasComm.h"
#include "TafMmaFsmMain.h"
#include "TafMmaFsmMainTbl.h"

#include "TafMmaSndMscc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define     THIS_FILE_ID        PS_FILE_ID_TAF_MMA_FSM_MAIN_C
#define     STA_WARNING_PRINT   PS_LOG_LEVEL_WARNING

/*****************************************************************************
  2 全局变量
*****************************************************************************/
extern STATUS_CONTEXT_STRU                     g_StatusContext;
extern MMA_ME_PERSONALISATION_STATUS_STRU      g_stMmaMePersonalisationStatus;

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/

/*****************************************************************************
  6 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvAppPhoneModeSetReq_Main
 功能描述  : 收到OM或AT的模式设置和查询消息的主处理
 输入参数  : ulEventType
             pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvAppPhoneModeSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PH_OP_MODE_STRU                *pstPhModeSet    = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstRcvMsg       = VOS_NULL_PTR;

    pstRcvMsg           = (MN_APP_REQ_MSG_STRU*)pstMsg;
    pstPhModeSet        = (TAF_PH_OP_MODE_STRU *)pstRcvMsg->aucContent;

    /* 关机时需要判断是否需要终止其他流程,开机时不需要判断 */
    if ((STA_FSM_ENABLE   != g_StatusContext.ulFsmState)
     && (TAF_PH_MODE_FULL != pstPhModeSet->PhMode))
    {
        TAF_MMA_ProcPhoneStop_NotEnableStatus();
    }

    /* 启动phone mode状态机 */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_PHONE_MODE);

    return VOS_TRUE;
}

/* Added by w00167002 for L-C互操作项目, 2014-2-14, begin */

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvTafPhoneModeSetReq_Main
 功能描述  : 收到TAF的模式设置消息的主处理
 输入参数  : ulEventType
             pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年02月14日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTafPhoneModeSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_PHONE_MODE_SET_REQ_STRU    *pstPhoneModeSetReq  = VOS_NULL_PTR;

    pstPhoneModeSetReq  = (TAF_MMA_PHONE_MODE_SET_REQ_STRU *)pstMsg;

    /* 关机时需要判断是否需要终止其他流程,开机时不需要判断 */
    if ((STA_FSM_ENABLE   != g_StatusContext.ulFsmState)
     && (TAF_PH_MODE_FULL != pstPhoneModeSetReq->stPhoneModePara.PhMode))
    {
        TAF_MMA_ProcPhoneStop_NotEnableStatus();
    }

    /* 启动phone mode状态机 */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_PHONE_MODE);

    return VOS_TRUE;
}

/* Added by w00167002 for L-C互操作项目, 2014-2-14, end */

/* Added by w00167002 for L-C互操作项目, 2014-2-14, begin */

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvSysCfgSetReq_Main
 功能描述  : 收到OM或AT的模式设置和查询消息的主处理
 输入参数  : ulEventType
             pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年02月14日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2014年02月14日
    作    者   : w00167002
    修改内容   : DTS2014060305973:在PHONE MODE状态机时候，用户设置SYSCFG设置，会
                进行缓存，在处理缓存时候出错，导致后续无法下发SYSCFG设置。
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvSysCfgSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_SYS_CFG_REQ_STRU           *pstRcvMsg = VOS_NULL_PTR;

    pstRcvMsg = (TAF_MMA_SYS_CFG_REQ_STRU *)pstMsg;

    switch (g_StatusContext.ulFsmState)
    {
        case STA_FSM_NULL:
        case STA_FSM_STOP:
            TAF_MMA_SetSyscfg_PowerOffStatus(pstRcvMsg);
            break;

        case STA_FSM_PLMN_RESEL:
            /* 如果是6F15触发的自动搜网，下发SYSCFG；
                  如果是AT触发的，由AT保证串行处理，此处不需处理 */
            if (TAF_MMA_AUTO_PLMN_SEL_USER_USIM_REFRESH == TAF_MMA_GetAutoPlmnSelUser())
            {
                /* 进状态机之前，迁移当前L1状态到SYSCFG状态 */
                TAF_MMA_FSM_SetCurrState(TAF_MMA_MAIN_STA_SYSCFG);

                /* 启动SYS CFG状态机 */
                TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_SYS_CFG);
            }
            else
            {
                TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvSysCfgSetReq_Main: wrong state!");
            }

            break;

        case STA_FSM_ENABLE:
            /* 进状态机之前，迁移当前L1状态到SYSCFG状态 */
            TAF_MMA_FSM_SetCurrState(TAF_MMA_MAIN_STA_SYSCFG);

            /* 启动SYS CFG状态机 */
            TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_SYS_CFG);
            break;


        default:
            TAF_MMA_SndSysCfgSetCnf(&(pstRcvMsg->stCtrl), TAF_ERR_CMD_TYPE_ERROR);

            break;
    }

    return VOS_TRUE;
}


/* Added by w00167002 for L-C互操作项目, 2014-2-14, end */

#if (FEATURE_ON == FEATURE_CSG)

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvTafCsgListSearchReq_Main
 功能描述  : 收到OM或AT的模式CSG列表搜的主处理
 输入参数  : ulEventType - 事件类型
             pstMsg      - 消息类型
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月6日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTafCsgListSearchReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_CSG_LIST_SEARCH_REQ_STRU   *pstRcvMsg          = VOS_NULL_PTR;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx      = VOS_NULL_PTR;
    TAF_MMA_PLMN_LIST_CTRL_STRU        *pstPlmnListCtrl    = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;
    VOS_UINT32                          ulRet;

    pstRcvMsg = (TAF_MMA_CSG_LIST_SEARCH_REQ_STRU *)pstMsg;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();


    /* 如果g_stTafMmaCtx.astMmaOperCtx里TAF_MMA_OPER_CSG_LIST_SEARCH_REQ类型结构正在被使用 */
    if (VOS_TRUE == TAF_MMA_IsOperTypeUsed(TAF_MMA_OPER_CSG_LIST_SEARCH_REQ))
    {
        /* 直接回复csg list失败 */
        TAF_MMA_ReportCsgListError(&(pstRcvMsg->stCtrl), TAF_ERR_TI_ALLOC_FAIL);

        return VOS_TRUE;
    }

    /* 找不到未被使用的，回复失败 */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        /* 直接回复csg list失败 */
        TAF_MMA_ReportCsgListError(&(pstRcvMsg->stCtrl), TAF_ERR_TI_ALLOC_FAIL);

        return VOS_TRUE;
    }

    /* 分配一个g_stTafMmaCtx.astMmaOperCtx到对应操作 */
    TAF_MMA_SetOperCtx(pstRcvMsg->stCtrl,
                       TAF_MMA_OPER_CSG_LIST_SEARCH_REQ, ucCtxIndex);

    pstPlmnListCtrl = (TAF_MMA_PLMN_LIST_CTRL_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_MMA_PLMN_LIST_CTRL_STRU));
    if (NULL == pstPlmnListCtrl)
    {
        TAF_MMA_ReportCsgListError(&(pstRcvMsg->stCtrl), TAF_ERR_ERROR);

        return VOS_TRUE;
    }

    pstPlmnListCtrl->usCurrIndex = pstRcvMsg->stPlmnListPara.usCurrIndex;
    pstPlmnListCtrl->usReadNum   = pstRcvMsg->stPlmnListPara.usQryNum;

    pstMmaOperCtx[ucCtxIndex].pPara = (VOS_VOID *)pstPlmnListCtrl;

    /* 给mscc发送csg list搜网请求 */
    ulRet = TAF_MMA_SndMsccCsgListSearchReq();

    if ( VOS_ERR == ulRet )
    {
        TAF_MMA_ReportCsgListError(&(pstRcvMsg->stCtrl), TAF_ERR_ERROR);

        return VOS_TRUE;
    }

    /* 设置CSG LIST状态标志量 */
    g_StatusContext.ulFsmState               = STA_FSM_PLMN_LIST;

    /* 启动CSG LIST状态定时器 */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_CSG_LIST_SEARCH_CNF, TI_TAF_MMA_WAIT_MSCC_CSG_LIST_SEARCH_CNF_LEN);

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMsccCsgListSearchCnf_Main
 功能描述  : 收到mscc的csg list搜网回复消息的处理
 输入参数  : ulEventType - 事件类型
             pstMsg      - 消息类型
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月8日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccCsgListSearchCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_CSG_LIST_SEARCH_CFN_STRU  *pstCsgListSearchCnf = VOS_NULL_PTR;
    TAF_MMA_CSG_LIST_CTX_STRU          *pstCsgListCtx       = VOS_NULL_PTR;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx     = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;
    TAF_MMA_TIMER_STATUS_ENUM_UINT8     enWaitCsgListAbortCnfTimerStatus;
    VOS_UINT8                           ucCtxIndex;
    TAF_MMA_PLMN_LIST_CTRL_STRU        *pstPlmnListCtrl = VOS_NULL_PTR;

    pstCsgListCtx       = TAF_MMA_GetCsgListCtxAddr();
    pstCsgListSearchCnf = (MSCC_MMA_CSG_LIST_SEARCH_CFN_STRU *)pstMsg;
    pstCsgListCtx       = TAF_MMA_GetCsgListCtxAddr();
    pstMmaOperCtx       = TAF_MMA_GetOperCtxAddr();

    if ( STA_FSM_PLMN_LIST != g_StatusContext.ulFsmState)
    {
        return VOS_TRUE;
    }

    /* 停止等csg list搜网回复定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_CSG_LIST_SEARCH_CNF);

    /* at csg abort请求与csg list搜网回复对冲场景，需要回复abort cnf */
    enWaitCsgListAbortCnfTimerStatus = TAF_MMA_GetTimerStatus(TI_TAF_MMA_WAIT_MSCC_CSG_LIST_ABORT_CNF);

    if ((TAF_MMA_PLMN_LIST_ABORT_PROCESSING_USER_ABORT == TAF_MMA_GetCsgListAbortType())
     && (TAF_MMA_TIMER_STATUS_RUNING == enWaitCsgListAbortCnfTimerStatus))
    {
        TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_CSG_LIST_ABORT_CNF);

        if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_CSG_LIST_ABORT_REQ, &ucCtxIndex))
        {
            /*  回复LIST_ABORT_CNF */
            TAF_MMA_SndCsgListAbortCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl), TAF_ERR_NO_ERROR);

            TAF_MMA_ClearOperCtx(ucCtxIndex);
            TAF_MMA_ClearCsgListSearchOperCtx();

            /* 迁移状态到ENABLE状态 */
            g_StatusContext.ulFsmState = STA_FSM_ENABLE;

            /* 设置当前没有处理用户CSG列表搜打断过程 */
            TAF_MMA_SetCsgListAbortType(TAF_MMA_PLMN_LIST_ABORT_BUTT);
            return VOS_TRUE;
        }
    }

    pstCsgListCtx->ulPlmnWithCsgIdNum = (VOS_UINT8)TAF_SDC_MIN(TAF_SDC_MAX_CSG_ID_LIST_NUM, pstCsgListSearchCnf->stCsgIdInfo.ulPlmnWithCsgIdNum);


    /* 将搜网结果保存在全局变量中 */
    for (ulIndex = 0; ulIndex < pstCsgListCtx->ulPlmnWithCsgIdNum; ulIndex++)
    {
        pstCsgListCtx->astCsgIdListInfo[ulIndex].stPlmnId.Mcc           = pstCsgListSearchCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].stPlmnId.ulMcc;
        pstCsgListCtx->astCsgIdListInfo[ulIndex].stPlmnId.Mnc           = pstCsgListSearchCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].stPlmnId.ulMnc;
        pstCsgListCtx->astCsgIdListInfo[ulIndex].enPlmnWithCsgIdType    = pstCsgListSearchCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].enPlmnWithCsgIdType;
        pstCsgListCtx->astCsgIdListInfo[ulIndex].ulCsgId                = pstCsgListSearchCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].ulCsgId;
        pstCsgListCtx->astCsgIdListInfo[ulIndex].ucRaMode               = pstCsgListSearchCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].enRatType;

        pstCsgListCtx->astCsgIdListInfo[ulIndex].stCsgType.ucCsgTypeLen = TAF_SDC_MIN(TAF_MMA_MAX_CSG_TYPE_LEN,pstCsgListSearchCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].ucCsgTypeLen);
        PS_MEM_CPY(pstCsgListCtx->astCsgIdListInfo[ulIndex].stCsgType.aucCsgType,
                   pstCsgListSearchCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].aucCsgType,
                   sizeof(pstCsgListCtx->astCsgIdListInfo[ulIndex].stCsgType.aucCsgType));

        pstCsgListCtx->astCsgIdListInfo[ulIndex].stCsgIdHomeNodeBName.ucHomeNodeBNameLen = TAF_SDC_MIN(TAF_MMA_MAX_HOME_NODEB_NAME_LEN, pstCsgListSearchCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].ucHomeNodeBNameLen);
        PS_MEM_CPY(pstCsgListCtx->astCsgIdListInfo[ulIndex].stCsgIdHomeNodeBName.aucHomeNodeBName,
                   pstCsgListSearchCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].aucHomeNodeBName,
                   sizeof(pstCsgListCtx->astCsgIdListInfo[ulIndex].stCsgIdHomeNodeBName.aucHomeNodeBName));
    }

    /* 上报结果 */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_CSG_LIST_SEARCH_REQ, &ucCtxIndex))
    {
        pstPlmnListCtrl = (TAF_MMA_PLMN_LIST_CTRL_STRU *)pstMmaOperCtx[ucCtxIndex].pPara;
        TAF_MMA_ReportCsgListSearchResult(&(pstMmaOperCtx[ucCtxIndex].stCtrl), pstPlmnListCtrl);
    }

    /* 状态恢复 */
    g_StatusContext.ulFsmState = STA_FSM_ENABLE;

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMsccCsgListRej_Main
 功能描述  : 收到mscc的csg list rej消息的处理
 输入参数  : ulEventType - 事件类型
             pstMsg      - 消息类型
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccCsgListRej_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx   = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstMmaOperCtx      = TAF_MMA_GetOperCtxAddr();

    /* 不是CSG LIST状态 */
    if ( STA_FSM_PLMN_LIST != g_StatusContext.ulFsmState )
    {
        /* 输出跟踪调试信息 */
        STA_TRACE (STA_WARNING_PRINT,
            "TAF_MMA_RcvMsccCsgListRej_Main():WARNING:unmatched system FSM state\n" );

        return VOS_TRUE;
    }

    /* 停止状态定时器*/
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_CSG_LIST_SEARCH_CNF);

    /* 清除子状态 */
    g_StatusContext.ulFsmState = STA_FSM_ENABLE;

    if (VOS_FALSE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_CSG_LIST_SEARCH_REQ, &ucCtxIndex))
    {
        STA_TRACE(PS_LOG_LEVEL_ERROR,"TAF_MMA_RcvMsccCsgListRej_Main:ERROR: GET CTX FAIL.");
        return VOS_TRUE;
    }

    TAF_MMA_ReportCsgListError(&(pstMmaOperCtx[ucCtxIndex].stCtrl), TAF_ERR_CMD_TYPE_ERROR);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMsccCsgListAbortCnf_Main
 功能描述  : 收到mscc的csg list abort回复消息的处理
 输入参数  : ulEventType - 事件类型
             pstMsg      - 消息类型
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月8日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccCsgListAbortCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_CSG_LIST_ABORT_CNF_STRU   *pPlmnListAbortCnf = VOS_NULL_PTR;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx     = VOS_NULL_PTR;
    TAF_MMA_CSG_LIST_CTX_STRU          *pstCsgListCtx     = VOS_NULL_PTR;
    TAF_MMA_PLMN_LIST_CTRL_STRU        *pstPlmnListCtrl   = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucCtxIndex;

    pstCsgListCtx     = TAF_MMA_GetCsgListCtxAddr();
    pPlmnListAbortCnf = (MSCC_MMA_CSG_LIST_ABORT_CNF_STRU*)pstMsg;
    pstMmaOperCtx     = TAF_MMA_GetOperCtxAddr();

    /* 停止保护定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_CSG_LIST_ABORT_CNF);

    /* 当前不是CSG LIST状态，直接返回 */
    if (STA_FSM_PLMN_LIST != g_StatusContext.ulFsmState)
    {
        STA_TRACE(STA_WARNING_PRINT, "TAF_MMA_RcvMsccCsgListAbortCnf_Main():WARNING:Sta_UpdateFsmFlag failed\n");
        return VOS_TRUE;
    }

    /* 异常保护：当前没有正在处理CSG列表搜打断，直接返回 */
    if (TAF_MMA_PLMN_LIST_ABORT_BUTT == TAF_MMA_GetCsgListAbortType())
    {
        STA_TRACE(STA_WARNING_PRINT, "TAF_MMA_RcvMsccCsgListAbortCnf_Main():WARNING:Sta_UpdateFsmFlag failed\n");
        return VOS_TRUE;
    }

    /* 定时器超时导致的 LIST ABORT的处理 */
    if ( TAF_MMA_PLMN_LIST_ABORT_PROCESSING_TIMEOUT == TAF_MMA_GetCsgListAbortType())
    {
        /* stop cnf和search cnf对冲时有可能带上来的列表不为空，需要上报, 将搜网结果保存在全局变量中 */
        if (pPlmnListAbortCnf->stCsgIdInfo.ulPlmnWithCsgIdNum > 0)
        {
            for (ulIndex = 0; ulIndex < TAF_SDC_MIN(TAF_SDC_MAX_CSG_ID_LIST_NUM, pPlmnListAbortCnf->stCsgIdInfo.ulPlmnWithCsgIdNum); ulIndex++)
            {
                pstCsgListCtx->astCsgIdListInfo[ulIndex].stPlmnId.Mcc           = pPlmnListAbortCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].stPlmnId.ulMcc;
                pstCsgListCtx->astCsgIdListInfo[ulIndex].stPlmnId.Mnc           = pPlmnListAbortCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].stPlmnId.ulMnc;
                pstCsgListCtx->astCsgIdListInfo[ulIndex].enPlmnWithCsgIdType    = pPlmnListAbortCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].enPlmnWithCsgIdType;
                pstCsgListCtx->astCsgIdListInfo[ulIndex].ulCsgId                = pPlmnListAbortCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].ulCsgId;
                pstCsgListCtx->astCsgIdListInfo[ulIndex].ucRaMode               = pPlmnListAbortCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].enRatType;

                pstCsgListCtx->astCsgIdListInfo[ulIndex].stCsgType.ucCsgTypeLen = TAF_SDC_MIN(TAF_MMA_MAX_CSG_TYPE_LEN,pPlmnListAbortCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].ucCsgTypeLen);
                PS_MEM_CPY(pstCsgListCtx->astCsgIdListInfo[ulIndex].stCsgType.aucCsgType,
                    pPlmnListAbortCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].aucCsgType,
                    sizeof(pstCsgListCtx->astCsgIdListInfo[ulIndex].stCsgType.aucCsgType));

                pstCsgListCtx->astCsgIdListInfo[ulIndex].stCsgIdHomeNodeBName.ucHomeNodeBNameLen = TAF_SDC_MIN(TAF_MMA_MAX_HOME_NODEB_NAME_LEN, pPlmnListAbortCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].ucHomeNodeBNameLen);
                PS_MEM_CPY(pstCsgListCtx->astCsgIdListInfo[ulIndex].stCsgIdHomeNodeBName.aucHomeNodeBName,
                    pPlmnListAbortCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].aucHomeNodeBName,
                    sizeof(pstCsgListCtx->astCsgIdListInfo[ulIndex].stCsgIdHomeNodeBName.aucHomeNodeBName));
            }

            pstCsgListCtx->ulPlmnWithCsgIdNum = (VOS_UINT8)TAF_SDC_MIN(TAF_SDC_MAX_CSG_ID_LIST_NUM, pPlmnListAbortCnf->stCsgIdInfo.ulPlmnWithCsgIdNum);

            /* 上报结果 */
            if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_CSG_LIST_SEARCH_REQ, &ucCtxIndex))
            {
                pstPlmnListCtrl = (TAF_MMA_PLMN_LIST_CTRL_STRU *)pstMmaOperCtx[ucCtxIndex].pPara;
                TAF_MMA_ReportCsgListSearchResult(&(pstMmaOperCtx[ucCtxIndex].stCtrl), pstPlmnListCtrl);
            }

            /* 状态恢复 */
            g_StatusContext.ulFsmState = STA_FSM_ENABLE;

            /* 设置当前没有处理用户CSG列表搜打断过程 */
            TAF_MMA_SetCsgListAbortType(TAF_MMA_PLMN_LIST_ABORT_BUTT);
            return VOS_TRUE;
        }

        /* abort cnf中不携带网络,上报空列表 */
        if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_CSG_LIST_SEARCH_REQ, &ucCtxIndex))
        {
            TAF_MMA_ReportCsgListError(&(pstMmaOperCtx[ucCtxIndex].stCtrl), TAF_ERR_TIME_OUT);
        }

        /* 状态恢复 */
        g_StatusContext.ulFsmState = STA_FSM_ENABLE;

        /* 设置当前没有处理用户CSG列表搜打断过程 */
        TAF_MMA_SetCsgListAbortType(TAF_MMA_PLMN_LIST_ABORT_BUTT);
        return VOS_TRUE;

    }

    /* AT下发的csg list abort，向AT回复列表搜超时结果 */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_CSG_LIST_ABORT_REQ, &ucCtxIndex))
    {
        /*  回复LIST_ABORT_CNF */
        TAF_MMA_SndCsgListAbortCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl), TAF_ERR_NO_ERROR);

        TAF_MMA_ClearOperCtx(ucCtxIndex);
    }

    TAF_MMA_ClearCsgListSearchOperCtx();

    /* 迁移状态到ENABLE状态 */
    g_StatusContext.ulFsmState = STA_FSM_ENABLE;

    /* 设置当前没有处理用户CSG列表搜打断过程 */
    TAF_MMA_SetCsgListAbortType(TAF_MMA_PLMN_LIST_ABORT_BUTT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvTafCsgListAbortReq_Main
 功能描述  : 收到OM或AT的模式CSG列表搜打断消息的主处理
 输入参数  : ulEventType - 事件类型
             pstMsg      - 消息类型
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月6日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTafCsgListAbortReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_CSG_LIST_ABORT_REQ_STRU    *pstPlmnListAbortMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucCtxIndex;

    pstPlmnListAbortMsg = (TAF_MMA_CSG_LIST_ABORT_REQ_STRU *)pstMsg;

    /* MMA上报CSG LIST CNF和列表搜打断对冲时，当前状态已不是CSG LIST状态，
       直接给AT回复abort cnf */
    if ( STA_FSM_PLMN_LIST != g_StatusContext.ulFsmState )
    {
        /* 上报AT当前状态事件 */
        TAF_MMA_SndCsgListAbortCnf(&pstPlmnListAbortMsg->stCtrl, TAF_ERR_NO_ERROR);

        return VOS_TRUE;
    }

    /* 定时器超时打断CSG列表搜和用户打断CSG列表搜对冲时，以用户打断为准 */
    if (TAF_MMA_PLMN_LIST_ABORT_PROCESSING_TIMEOUT == TAF_MMA_GetCsgListAbortType())
    {
        /* 设置当前正在处理用户CSG打断列表搜过程 */
        TAF_MMA_SetCsgListAbortType(TAF_MMA_PLMN_LIST_ABORT_PROCESSING_USER_ABORT);

        return VOS_TRUE;
    }

    /* 停CSG列表搜定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_CSG_LIST_SEARCH_CNF);

    /* 如果g_stTafMmaCtx.astMmaOperCtx里TAF_MMA_OPER_CSG_LIST_ABORT_REQ类型结构正在被使用 */
    if (VOS_TRUE == TAF_MMA_IsOperTypeUsed(TAF_MMA_OPER_CSG_LIST_ABORT_REQ))
    {
        /* 直接回复LIST ABORT设置失败 */
        TAF_MMA_SndCsgListAbortCnf(&pstPlmnListAbortMsg->stCtrl, TAF_ERR_ERROR);
        return VOS_TRUE;
    }

    /* 找不到未被使用的，回复失败 */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        TAF_MMA_SndCsgListAbortCnf(&pstPlmnListAbortMsg->stCtrl, TAF_ERR_NO_ERROR);
        return VOS_TRUE;
    }

    /* 分配一个g_stTafMmaCtx.astMmaOperCtx到对应操作 */
    TAF_MMA_SetOperCtx(pstPlmnListAbortMsg->stCtrl,
                       TAF_MMA_OPER_CSG_LIST_ABORT_REQ, ucCtxIndex);

    /* MMA的LIST搜网保护定时器超时则主动向MSCC发送停止LIST搜网请求
       收到MSCC的回复后再向AT回复 */
    ulRet = TAF_MMA_SndMsccCsgListAbortReq();

    if (VOS_ERR == ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvTafCsgListAbortReq_Main():ERROR: failed");
        return VOS_TRUE;
    }

    /* 启动10s定时器，如果超时未收到MSCC的回复则上报AT失败 */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_CSG_LIST_ABORT_CNF, TI_TAF_MMA_WAIT_MSCC_CSG_LIST_ABORT_CNF_LEN);

    /* 设置当前正在进行用户打断CSG列表搜过程 */
    TAF_MMA_SetCsgListAbortType(TAF_MMA_PLMN_LIST_ABORT_PROCESSING_USER_ABORT);

    return VOS_TRUE;
}


#endif

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMmaPlmnListReq_Main
 功能描述  : 收到OM或AT的模式列表搜的主处理
 输入参数  : ulEventType
             pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月12日
    作    者   : b00269685
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaPlmnListReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_PLMN_LIST_REQ_STRU         *pstRcvMsg          = VOS_NULL_PTR;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx      = VOS_NULL_PTR;
    TAF_MMA_PLMN_LIST_CTRL_STRU        *pstPlmnListCtrl    = VOS_NULL_PTR;
    TAF_MMA_PLMN_LIST_CNF_PARA_STRU    *pstPlmnListCnfPara = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstRcvMsg = (TAF_MMA_PLMN_LIST_REQ_STRU *)pstMsg;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    pstPlmnListCnfPara = (TAF_MMA_PLMN_LIST_CNF_PARA_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_MMA_PLMN_LIST_CNF_PARA_STRU));
    if (NULL == pstPlmnListCnfPara)
    {
        return VOS_TRUE;
    }

    PS_MEM_SET(pstPlmnListCnfPara, 0x0, sizeof(TAF_MMA_PLMN_LIST_CNF_PARA_STRU));

    /* 如果g_stTafMmaCtx.astMmaOperCtx里TAF_MMA_OPER_PLMN_LIST_REQ类型结构正在被使用 */
    if (VOS_TRUE == TAF_MMA_IsOperTypeUsed(TAF_MMA_OPER_PLMN_LIST_REQ))
    {
        /* 直接回复plmn list失败 */
        pstPlmnListCnfPara->ucOpError    = VOS_TRUE;
        pstPlmnListCnfPara->enPhoneError = TAF_ERR_TI_ALLOC_FAIL;
        TAF_MMA_SndPlmnListCnf(&(pstRcvMsg->stCtrl), pstPlmnListCnfPara);

        PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

        return VOS_TRUE;
    }

    /* 找不到未被使用的，回复失败 */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
         /* 直接回复plmn list失败 */
        pstPlmnListCnfPara->ucOpError    = VOS_TRUE;
        pstPlmnListCnfPara->enPhoneError = TAF_ERR_TI_ALLOC_FAIL;
        TAF_MMA_SndPlmnListCnf(&(pstRcvMsg->stCtrl), pstPlmnListCnfPara);

        PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

        return VOS_TRUE;
    }

    /* 分配一个g_stTafMmaCtx.astMmaOperCtx到对应操作 */
    TAF_MMA_SetOperCtx(pstRcvMsg->stCtrl,
                       TAF_MMA_OPER_PLMN_LIST_REQ, ucCtxIndex);

    pstPlmnListCtrl = (TAF_MMA_PLMN_LIST_CTRL_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_MMA_PLMN_LIST_CTRL_STRU));
    if (NULL == pstPlmnListCtrl)
    {
        /* 直接回复plmn list失败 */
        TAF_MMA_PlmnListErrorReport(TAF_ERR_ERROR);

        PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

        return VOS_TRUE;
    }

    pstPlmnListCtrl->usCurrIndex = pstRcvMsg->stPlmnListPara.usCurrIndex;
    pstPlmnListCtrl->usReadNum   = pstRcvMsg->stPlmnListPara.usQryNum;

    pstMmaOperCtx[ucCtxIndex].pPara = (VOS_VOID *)pstPlmnListCtrl;

    /* 如果不是分段上报中的首次查询，则直接调用缓存中的内容上报 */
    if (0 != pstPlmnListCtrl->usCurrIndex)
    {
        Sta_PlmnListEventReport();

        PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

        return VOS_TRUE;
    }

    PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

    /* 继续原有的plmn list流程 */
    MMA_PhonePlmnList();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMmaInterPowerInit_Main
 功能描述  : 收到MMA的内部上电消息的主处理
 输入参数  : ulEventType
             pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaInterPowerInit_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 启动phone mode状态机 */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_PHONE_MODE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMmaInterUsimStatusChangeInd_Main
 功能描述  : 收到MMA的内部卡状态改变消息的主处理
 输入参数  : ulEventType
             pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2014年2月19日
    作    者   : w00167002
    修改内容   : 开机后解PIN，STK IMSI改变，3G session或掉卡触发重新关机和开机流
                 程中，USIM模块分别上报卡状态消息到MMA和CDMA modem，此时，由CDMA
                 modem再触发Balong modem关机开机流程, Balong modem不自动进行关机
                 和开机操作；由于Balong modem没有开启锁卡锁网特性，锁卡锁网始终由
                 CDMA modem完成.
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaInterUsimStatusChangeInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (STA_FSM_ENABLE != g_StatusContext.ulFsmState)
    {
        TAF_MMA_ProcPhoneStop_NotEnableStatus();
    }

    /* Modified by w00167002 for L-C互操作项目, 2014-2-19, begin */

    /* 如果当前为CL模式，则等待CDMA触发关机 */
    if (VOS_TRUE == TAF_SDC_IsConfigCLInterWorkCOutside())
    {
        return VOS_TRUE;
    }
    /* Modified by w00167002 for L-C互操作项目, 2014-2-19, end */



    /* 启动phone mode状态机 */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_PHONE_MODE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMmaSimlockStatusChangeInd_Main
 功能描述  : 收到MMA的锁网锁卡状态改变消息的主处理
 输入参数  : ulEventType
             pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月12日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaSimlockStatusChangeInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (STA_FSM_ENABLE != g_StatusContext.ulFsmState)
    {
        TAF_MMA_ProcPhoneStop_NotEnableStatus();
    }

    /* 启动phone mode状态机 */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_PHONE_MODE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMmaPhoneModeRsltInd_Main
 功能描述  : 收到MMA的模式设置状态机退出消息的主处理
 输入参数  : ulEventType
             pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2014年2月18日
    作    者   : w00167002
    修改内容   : L-C互操作项目:在关机时候，初始化CL互操作内容
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaPhoneModeRsltInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by w00167002 for L-C互操作项目, 2014-2-18, begin */
    TAF_MMA_PHONE_MODE_RSLT_IND_STRU   *pstPhoneModeRslt    = VOS_NULL_PTR;
    TAF_SDC_CTX_STRU                   *pstSdcCtx           = VOS_NULL_PTR;

    pstPhoneModeRslt = (TAF_MMA_PHONE_MODE_RSLT_IND_STRU*)pstMsg;
    pstSdcCtx = TAF_SDC_GetSdcCtx();
    /* Modified by w00167002 for L-C互操作项目, 2014-2-18, end */

    if (TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_SUCC == pstPhoneModeRslt->enRslt)
    {
        /*进入使能状态，设置状态标志量*/
        g_StatusContext.ulFsmState = STA_FSM_ENABLE;
    }
    else
    {
        /* 初始化全局变量 */
        TAF_MMA_InitCtx(TAF_MMA_INIT_CTX_POWEROFF, TAF_MMA_GetMmaCtxAddr());

        TAF_SDC_InitServiceInfo(&pstSdcCtx->stServiceInfo);

        /* Added by w00167002 for L-C互操作项目, 2014-2-18, begin */
        TAF_SDC_InitLcConfigPara(&(pstSdcCtx->stMsCfgInfo.stMsCapInfo.stLcConfigPara));
        /* Added by w00167002 for L-C互操作项目, 2014-2-18, end */

        g_StatusContext.ulFsmState = STA_FSM_NULL;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMmaSysCfgRsltInd_Main
 功能描述  : 收到MMA的SysCfg状态机退出消息的主处理
 输入参数  : ulEventType
             pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月5日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaSysCfgRsltInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucOrigLockStatus;

    TAF_MMA_SYS_CFG_RSLT_STRU          *pstSysCfgRslt   = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                          enSubMode;
    pTafSdcSysmodServiceRegStaUpdateFunc                    pFuncTafSdcSysmodServiceRegStaUpdate;

    pFuncTafSdcSysmodServiceRegStaUpdate = VOS_NULL_PTR;
    enSysMode = TAF_SDC_SYS_MODE_BUTT;
    enSubMode = TAF_SDC_SYS_SUBMODE_BUTT;

    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        if (VOS_FALSE == TAF_SDC_IsSyscfgSupportSpecRat(TAF_SDC_SYS_MODE_LTE))
        {
            TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(TAF_SDC_LTE_NETWORK_NOT_EXIST, &enSysMode, &enSubMode, &pFuncTafSdcSysmodServiceRegStaUpdate);

            TAF_MMA_ChgSysModeAndSrvRegSta(TAF_PH_ACCESS_TECH_E_UTRAN,
                                           enSysMode,
                                           enSubMode,
                                           pFuncTafSdcSysmodServiceRegStaUpdate);

            TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode();
        }

        if (VOS_FALSE == TAF_SDC_IsSyscfgSupportSpecRat(TAF_SDC_SYS_MODE_CDMA_1X))
        {
            TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(TAF_SDC_1X_NETWORK_NOT_EXIST, &enSysMode, &enSubMode, &pFuncTafSdcSysmodServiceRegStaUpdate);

            TAF_MMA_ChgSysModeAndSrvRegSta(TAF_PH_ACCESS_TECH_CDMA_1X,
                                           enSysMode,
                                           enSubMode,
                                           pFuncTafSdcSysmodServiceRegStaUpdate);

            TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode();
        }

        if (VOS_FALSE == TAF_SDC_IsSyscfgSupportSpecRat(TAF_SDC_SYS_MODE_EVDO))
        {
            TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(TAF_SDC_HRPD_NETWORK_NOT_EXIST, &enSysMode, &enSubMode, &pFuncTafSdcSysmodServiceRegStaUpdate);

            TAF_MMA_ChgSysModeAndSrvRegSta(TAF_PH_ACCESS_TECH_EVDO,
                                           enSysMode,
                                           enSubMode,
                                           pFuncTafSdcSysmodServiceRegStaUpdate);

            TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode();
        }
    }

    /* 上报当前的是否是CL模式 */
    TAF_MMA_SndCLModeInd();
#endif

    pstSysCfgRslt   = (TAF_MMA_SYS_CFG_RSLT_STRU *)pstMsg;

    /* 退出SYSCFG状态机后，迁移当前L1状态到idle状态 */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_MAIN_STA_IDLE);

#ifdef DMT
    return VOS_TRUE;
#endif

    if (TAF_MMA_SYS_CFG_RSLT_SYS_CFG_SUCC != pstSysCfgRslt->enRslt)
    {
        return VOS_TRUE;
    }

    /* GUL->CL或CL->GUL时需要重新判断锁网锁卡状态，若发生变化需发送USIMM STATUS CHANGE消息 */
    if (VOS_FALSE == pstSysCfgRslt->ucIsNeedChkLock)
    {
        return VOS_TRUE;
    }

    /* 锁网锁卡状态检查 */
    ucOrigLockStatus = g_stMmaMePersonalisationStatus.SimLockStatus;

    g_stMmaMePersonalisationStatus.SimLockStatus = MMA_SIM_IS_UNLOCK;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        /* 检查是否锁卡 */
        (VOS_VOID)MMA_CheckCsimMePersonalisationStatus();
    }
    else
#endif
    {
        /* 检查是否锁卡 */
        (VOS_VOID)MMA_CheckMePersonalisationStatus();
    }

    /* 锁网锁卡状态发生变更 */
    if (g_stMmaMePersonalisationStatus.SimLockStatus   != ucOrigLockStatus)
    {
        TAF_MMA_SndInterUsimChangeInd();
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMmaInterSysCfgSetReq_Main
 功能描述  : 收到MMA的内部SYS CFG设置请求的主处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaInterSysCfgSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 进状态机之前，迁移当前L1状态到SYSCFG状态 */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_MAIN_STA_SYSCFG);

    /* 启动SYS CFG状态机 */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_SYS_CFG);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvPihUsimStatusInd_Main
 功能描述  : 收到PB模块上报的卡状态指示消息的主处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月10日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 发送内部卡状态改变消息 */
    TAF_MMA_SndInterUsimChangeInd();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvUsimRefreshIndMsg_Main
 功能描述  : 收到usim的文件刷新指示消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月10日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvUsimRefreshIndMsg_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 发送内部卡状态改变消息 */
    TAF_MMA_SndInterUsimChangeInd();

    return VOS_TRUE;
}

/* Added by s00246516 for L-C互操作项目, 2014-02-14, Begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_RcvDetachReq_Main
 功能描述  : 收到Detach消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月14日
   作    者   : s00246516
   修改内容   : 新生成函数
 2.日    期   : 2015年4月20日
   作    者   : h00313353
   修改内容   : SysCfg Reconsitution
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvDetachReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_DETACH_REQ_STRU            *pstDetachReqMsg;

    pstDetachReqMsg                     = (TAF_MMA_DETACH_REQ_STRU *)pstMsg;

    /* ENABLE或RESTART状态允许进行DETACH */
    if (VOS_TRUE != TAF_MMA_IsEnableDeAttach())
    {
        TAF_MMA_SndDetachCnf(&(pstDetachReqMsg->stCtrl),
                             TAF_MMA_APP_OPER_RESULT_FAILURE,
                             TAF_ERR_ERROR);

        TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvDetachReq_Main():FSM state not in Enabled or Restart!");

        return VOS_TRUE;
    }

    /* 进状态机之前，迁移当前L1状态到SYSCFG状态 */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_MAIN_STA_SYSCFG);

    /* 启动System Config状态机 */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_SYS_CFG);

    return VOS_TRUE;
}
/* Added by s00246516 for L-C互操作项目, 2014-02-14, End */



/*****************************************************************************
 函 数 名  : TAF_MMA_RcvAttachReq_Main
 功能描述  :  主状态机收到ID_TAF_MMA_ATTACH_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月11日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvAttachReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ENABLE或者refresh触发的自动搜网允许发起attach */
    if (VOS_TRUE != TAF_MMA_IsEnableDeAttach())
    {
        TAF_MMA_SndAttachCnf(&(((TAF_MMA_ATTACH_REQ_STRU *)pstMsg)->stCtrl),
                             TAF_MMA_APP_OPER_RESULT_FAILURE,
                             TAF_ERR_PHONE_MSG_UNMATCH);

        return VOS_TRUE;
    }
    /* 进状态机之前，迁移当前L1状态到SYSCFG状态 */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_MAIN_STA_SYSCFG);

    /* 启动SYS CFG状态机 */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_SYS_CFG);

    return VOS_TRUE;
}


#if (FEATURE_IMS == FEATURE_ON)
/*****************************************************************************
 函 数 名  : TAF_MMA_IsRefreshTrigger_PreProc
 功能描述  : 是否是refresh触发
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE
             VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月03日
    作    者   : f00179208
    修改内容   : IMS动态开关配置项目
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsRefreshTrigger_Main(VOS_VOID)
{
    TAF_MMA_AUTO_PLMN_SEL_USER_ENUM_UINT8 enAutoPlmnSelUser;

    enAutoPlmnSelUser = TAF_MMA_GetAutoPlmnSelUser();

    /* refresh触发的自动搜网 */
    if ((STA_FSM_PLMN_RESEL == g_StatusContext.ulFsmState)
     && (TAF_MMA_AUTO_PLMN_SEL_USER_USIM_REFRESH == enAutoPlmnSelUser))
    {
        return VOS_TRUE;
    }

    /* refresh触发的SYSCFG*/
    /* 如果在SYSCFG过程，在SYSCFG状态机中处理abort。此处删除 */

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcImsSwitchOff_PreProc
 功能描述  : IMS关闭的预处理
 输入参数  : pstImsSwitchSet
 输出参数  : 无
 返 回 值  : VOS_TRUE:消息处理完成
             VOS_FALSE:消息未处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月03日
    作    者   : f00179208
    修改内容   : IMS动态开关配置项目
*****************************************************************************/
VOS_UINT32 TAF_MMA_ProcImsSwitchOff_Main(
    TAF_MMA_IMS_SWITCH_SET_REQ_STRU     *pstImsSwitchSet
)
{
    TAF_SDC_IMS_SWITCH_STATE_ENUM_UINT8 enLastState;
    VOS_UINT32                          ulPhoneMode;

    enLastState      = TAF_SDC_GetCurImsSwitchState();
    ulPhoneMode      = TAF_SDC_GetCurPhoneMode();

    /* 如果当前处于IMS业务过程中，不允许关闭IMS业务 */
    if (VOS_TRUE == TAF_SDC_IsImsSrvExist())
    {
        /* 给上层回复失败 */
        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   TAF_MMA_APP_OPER_RESULT_REJECT,
                                   TAF_ERR_IMS_SERVICE_EXIST);

        return VOS_TRUE;
    }

    /* 如果语音优选域设置成了PS_ONLY，不允许关闭IMS业务 */
    if (TAF_SDC_VOICE_DOMAIN_IMS_PS_ONLY == TAF_SDC_GetVoiceDomain())
    {
        /* 给上层回复失败 */
        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   TAF_MMA_APP_OPER_RESULT_REJECT,
                                   TAF_ERR_IMS_VOICE_DOMAIN_PS_ONLY);

        return VOS_TRUE;
    }

    /* 更新IMS业务能力变量和NV */
    if (VOS_TRUE != TAF_MMA_UpdateLteImsSupportFlag(VOS_FALSE))
    {
        /* 给上层回复失败 */
        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   TAF_MMA_APP_OPER_RESULT_FAILURE,
                                   TAF_ERR_UNSPECIFIED_ERROR);
        return VOS_TRUE;
    }

    /* 当前IMS协议栈已经关闭或者处于飞行模式状态，
       则不需要给IMSA发关闭请求，只更新NV即可 */
    if ((TAF_SDC_IMS_SWITCH_STATE_OFF == enLastState)
     || (TAF_PH_MODE_FULL != ulPhoneMode))
    {
        /* 给上层回复成功 */
        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   TAF_MMA_APP_OPER_RESULT_SUCCESS,
                                   TAF_ERR_NO_ERROR);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcImsSwitchOn_PreProc
 功能描述  : IMS打开的预处理
 输入参数  : pstImsSwitchSet
 输出参数  : 无
 返 回 值  : VOS_TRUE:消息处理完成
             VOS_FALSE:消息未处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月03日
    作    者   : f00179208
    修改内容   : IMS动态开关配置项目
*****************************************************************************/
VOS_UINT32 TAF_MMA_ProcImsSwitchOn_Main(
    TAF_MMA_IMS_SWITCH_SET_REQ_STRU     *pstImsSwitchSet
)
{
    TAF_SDC_IMS_SWITCH_STATE_ENUM_UINT8 enLastState;
    VOS_UINT32                          ulPhoneMode;

    enLastState      = TAF_SDC_GetCurImsSwitchState();
    ulPhoneMode      = TAF_SDC_GetCurPhoneMode();

    /* 更新NV放在给IMSA发送start req的前面，IMSA收到start req会读NV项，需要用最新的NV值 */
    if (VOS_TRUE != TAF_MMA_UpdateLteImsSupportFlag(VOS_TRUE))
    {
        /* 给上层回复失败 */
        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   TAF_MMA_APP_OPER_RESULT_FAILURE,
                                   TAF_ERR_UNSPECIFIED_ERROR);

        return VOS_TRUE;
    }

    /* 当前IMS协议栈已经开启或者处于飞行模式状态，
       则不需要给IMSA发启动请求，只更新NV即可  */
    if ((TAF_SDC_IMS_SWITCH_STATE_ON == enLastState)
     || (TAF_PH_MODE_FULL != ulPhoneMode))
    {
        /* 给上层回复成功 */
        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   TAF_MMA_APP_OPER_RESULT_SUCCESS,
                                   TAF_ERR_NO_ERROR);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvTafImsSwitchSetReq_Main
 功能描述  : 收到TAF的IMS开关消息的主处理
 输入参数  : ulEventType
             pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月04日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTafImsSwitchSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_IMS_SWITCH_SET_REQ_STRU    *pstSetReq   = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;

    ulResult   = VOS_TRUE;
    pstSetReq  = (TAF_MMA_IMS_SWITCH_SET_REQ_STRU *)pstMsg;


    /* 如果当前有其他AT的请求在处理，则直接给上层回复失败，
       卡触发的请求可以设置IMS开关，但结果回复的时候需要缓存 */
    if ((STA_FSM_ENABLE != g_StatusContext.ulFsmState)
     && (STA_FSM_NULL   != g_StatusContext.ulFsmState)
     && (STA_FSM_STOP   != g_StatusContext.ulFsmState))
    {
        /* 不是卡触发的，即由AT触发的请求 */
        if (VOS_FALSE == TAF_MMA_IsRefreshTrigger_Main())
        {
            /* 给上层回复失败 */
            TAF_MMA_SndImsSwitchSetCnf(&pstSetReq->stCtrl,
                                       TAF_MMA_APP_OPER_RESULT_FAILURE,
                                       TAF_ERR_UNSPECIFIED_ERROR);

            return VOS_TRUE;
        }
    }

    /* 关闭IMS业务 */
    if (TAF_MMA_IMS_SWITCH_SET_POWER_OFF == pstSetReq->enImsSwitch)
    {
        ulResult = TAF_MMA_ProcImsSwitchOff_Main(pstSetReq);
    }
    else
    {
        ulResult = TAF_MMA_ProcImsSwitchOn_Main(pstSetReq);
    }

    /* 返回VOS_FALSE，代表需要继续进IMS_SWITCH状态机处理 */
    if ( VOS_FALSE == ulResult )
    {
        /* 启动IMS SWITCH状态机 */
        TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_IMS_SWITCH);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMmaImsSwitchRsltInd_Main
 功能描述  : 收到MMA的IMS SWITCH状态机退出消息的主处理
 输入参数  : ulEventType
             pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-02-04
    作    者   : n00269697
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaImsSwitchRsltInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 暂时没有处理，只是为了后续的缓存处理，以后如果有需要，可以在这里添加处理 */

    return VOS_TRUE;
}
#endif



/**********************************************************
 函 数 名  : TAF_MMA_RcvPlmnSpecialSelReq_Main
 功能描述  : 处理用户指定搜请求
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年3月25日
    作    者   : f00279542
    修改内容   : CDMA Iteration 11 重构修改
*************************************************************/
VOS_UINT32 TAF_MMA_RcvPlmnSpecialSelReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PLMN_ID_STRU                    stPlmn;
    VOS_UINT32                          ulRet;
    TAF_MMA_PLMN_SPECIAL_SEL_REQ_STRU  *pstPlmnSpecialSelMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstPlmnSpecialSelMsg = (TAF_MMA_PLMN_SPECIAL_SEL_REQ_STRU *)pstMsg;

    /* 如果g_stTafMmaCtx.astMmaOperCtx里TAF_MMA_OPER_PLMN_SPEC_SEL_REQ类型结构正在被使用 */
    if (VOS_TRUE == TAF_MMA_IsOperTypeUsed(TAF_MMA_OPER_PLMN_SPEC_SEL_REQ))
    {
        /* 直接回复SEL设置失败 */
        TAF_MMA_SndPlmnSpecialSelCnf(&pstPlmnSpecialSelMsg->stCtrl, TAF_ERR_ERROR);
        return VOS_TRUE;
    }

    /* 找不到未被使用的，回复失败 */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        TAF_MMA_SndPlmnSpecialSelCnf(&pstPlmnSpecialSelMsg->stCtrl, TAF_ERR_ERROR);
        return VOS_TRUE;
    }

    /* 分配一个g_stTafMmaCtx.astMmaOperCtx到对应操作 */
    TAF_MMA_SetOperCtx(pstPlmnSpecialSelMsg->stCtrl,
                       TAF_MMA_OPER_PLMN_SPEC_SEL_REQ, ucCtxIndex);

    /* 在CL模式时候，不支持AT进行选网操作,直接返回ERROR */
    if (VOS_TRUE == TAF_MMA_IsPowerOnCLInterWork())
    {
        TAF_MMA_ProcPlmnSpecialSelCnf(TAF_ERR_ERROR);
        return VOS_TRUE;
    }

    /* 转化用户输入PLMN字符为PLMN ID */
    ulRet = MMA_FormatPlmnStr2PlmnId(&stPlmn,
                                      pstPlmnSpecialSelMsg->stPlmnUserSel.ucFormatType,
                                      pstPlmnSpecialSelMsg->stPlmnUserSel.usOperNameLen,
                                      pstPlmnSpecialSelMsg->stPlmnUserSel.ucOperName);
    if( VOS_TRUE == ulRet)
    {
        MMA_PlmnId2NasStyle(&stPlmn);

        /* 通过原有的TAF_PH_EVT_PLMN_SEL_CNF消息把指定搜结果发送给AT */
        MMA_PhonePlmnUserSel(pstPlmnSpecialSelMsg->stCtrl.usClientId, pstPlmnSpecialSelMsg->stCtrl.ucOpId, stPlmn, pstPlmnSpecialSelMsg->stPlmnUserSel.enAccessMode, TAF_PLMN_RESELETION_MANUAL);
    }
    else
    {
        /*错误处理*/
        TAF_MMA_ProcPlmnSpecialSelCnf(TAF_ERR_PARA_ERROR);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcPlmnAutoReselReq_Main
 功能描述  : 处理PLMN自动重选请求
 输入参数  : ulOpID   -- operation ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年12月26日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
VOS_VOID TAF_MMA_ProcPlmnAutoReselReq_Main(
    VOS_UINT32                          ulOpID
)
{
    VOS_UINT32                            ulRet;
    TAF_MMA_AUTO_PLMN_SEL_USER_ENUM_UINT8 enAutoPlmnSelUser;

    TAF_INFO_LOG1(WUEPS_PID_MMA,
                  "TAF_MMA_ProcPlmnAutoReselReq_Main: current ulFsmState",
                  g_StatusContext.ulFsmState);

    enAutoPlmnSelUser = TAF_MMA_GetAutoPlmnSelUser();

    /* svlte nv开启允许关机状态设置cops */
    if (TAF_PH_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        (VOS_VOID)TAF_MMA_PlmnReselectAutoReq_PowerOff(ulOpID);

        return;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_FALSE == TAF_SDC_IsConfigCLMode())       // liuqg 为FALSE的时候应该就是LTE, 那么1X 时不需要判断下面的内容吗
#endif
    {
        /* PLMN_RESEL状态输入条件检查异常 */
        /* 当前正在进行6F15文件触发的自动搜网 */
        if ((STA_FSM_PLMN_RESEL                      == g_StatusContext.ulFsmState)
         && (TAF_MMA_AUTO_PLMN_SEL_USER_USIM_REFRESH == enAutoPlmnSelUser))
        {
            TAF_INFO_LOG(WUEPS_PID_MMA, "TAF_MMA_ProcPlmnAutoReselReq_Main: 6F15 file trigered auto search!");

            /* 记录为AT发起的自动搜网，收到CNF之后需要给用户回复结果 */
            TAF_MMA_SetAutoPlmnSelUser(TAF_MMA_AUTO_PLMN_SEL_USER_AT); // liuqg 正在进行6F15文件触发的自动搜网, 为什么记录为AT发起的自动搜网

            /* 记录当前的操作过程标识号 */
            g_StatusContext.ulCurOpId = ulOpID;

            return;
        }
    }

    if ( VOS_FALSE == (g_StatusContext.ulFsmState & STA_FSM_ENABLE) )
    {
        /* 如果不是ENABLE状态，返回错误 */
        TAF_MMA_ProcPlmnAutoReselCnf(TAF_ERR_PHONE_MSG_UNMATCH);

        return;
    }

    ulRet = TAF_MMA_SndMsccPlmnUserReselReq(NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO);

    if ( VOS_ERR == ulRet )
    {
        return;
    }

    /* 记录AT发起的自动搜网请求 */
    TAF_MMA_SetAutoPlmnSelUser(TAF_MMA_AUTO_PLMN_SEL_USER_AT);

    /* 记录当前的操作过程标识号 */
    g_StatusContext.ulCurOpId = ulOpID;

    /* 记录PLMN重新类型 */
    g_StatusContext.ucReselMode = NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO;

    /* 设置PLMN_RESEL状态标志量 */
    g_StatusContext.ulFsmState = STA_FSM_PLMN_RESEL;

    TAF_INFO_LOG1(WUEPS_PID_MMA,
                  "TAF_MMA_ProcPlmnAutoReselReq_Main: new ulFsmState = ",
                  g_StatusContext.ulFsmState);

    /* 启动保护定时器TI_TAF_MMA_WAIT_MSCC_PLMNAUTORESEL_SET_CNF */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_PLMN_AUTO_RESEL_CNF, TI_TAF_MMA_WAIT_MSCC_PLMN_AUTO_RESEL_SET_CNF_LEN);

    /* 更新子状态的操作过程标识号 */
    g_StatusContext.aFsmSub[0].ulOpId = ulOpID;

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_RcvPlmnAutoReselReq_Main
 功能描述  : PLMN重选
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年3月25日
    作    者   : f00279542
    修改内容   : CDMA Iteration 11 重构修改

 2.日    期   : 2015年12月25日
   作    者   : y00245242
   修改内容   : CL模式下，亮屏触发搜网特性开发
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvPlmnAutoReselReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucError;
    TAF_MMA_PLMN_AUTO_RESEL_REQ_STRU   *pstPlmnReselMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstPlmnReselMsg = (TAF_MMA_PLMN_AUTO_RESEL_REQ_STRU *)pstMsg;

    /* 如果g_stTafMmaCtx.astMmaOperCtx里TAF_MMA_OPER_PLMN_AUTO_RESEL_REQ类型结构正在被使用 */
    if (VOS_TRUE == TAF_MMA_IsOperTypeUsed(TAF_MMA_OPER_PLMN_AUTO_RESEL_REQ))
    {
        /* 直接回复RESEL设置失败 */
        TAF_MMA_SndPlmnAutoReselCnf(&pstPlmnReselMsg->stCtrl, TAF_ERR_ERROR);
        return VOS_TRUE;
    }

    /* 找不到未被使用的，回复失败 */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        TAF_MMA_SndPlmnAutoReselCnf(&pstPlmnReselMsg->stCtrl, TAF_MMA_APP_OPER_RESULT_FAILURE);
        return VOS_TRUE;
    }

    /* 分配一个g_stTafMmaCtx.astMmaOperCtx到对应操作 */
    TAF_MMA_SetOperCtx(pstPlmnReselMsg->stCtrl,
                       TAF_MMA_OPER_PLMN_AUTO_RESEL_REQ, ucCtxIndex);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_FALSE == TAF_SDC_IsConfigCLMode())
#endif
    {
        ucError = TAF_ERR_NO_ERROR;
        ucError = MMA_CheckUsimStatusForPlmnSel();
        if(TAF_ERR_NO_ERROR != ucError)
        {
            MMA_WARNINGLOG("TAF_MMA_RcvPlmnAutoReselReq_Main():WARNING:UsimStatus Error!");
            /*错误处理*/
            TAF_MMA_ProcPlmnAutoReselCnf(ucError);
            return VOS_TRUE;
        }
    }

    TAF_MMA_ProcPlmnAutoReselReq_Main(pstPlmnReselMsg->stCtrl.ucOpId);

    return VOS_TRUE;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


