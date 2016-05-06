/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasEhsmMsgPrioCompare.c
  版 本 号   : 初稿
  作    者   : h00246512
  生成日期   : 2015年5月27日
  最近修改   :
  功能描述   : CnasEhsmMsgPrioCompare.h的实现
  函数列表   :
  修改历史   :
  1.日    期   : 2015年5月27日
    作    者   : h00246512
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasEhsmMsgPrioCompare.h"
#include  "NasFsm.h"
#include  "CnasEhsmSndInternalMsg.h"
#include  "CnasCcb.h"
#include  "ehsm_hsd_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_CNAS_EHSM_MSG_PRIO_COMPARE_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/*****************************************************************************
 全局变量名    : g_astEhmsMsgPrioCompareWithActivatingTbl
 全局变量说明  : Activating状态机消息优先级比较处理的比较表
 1.日    期   : 2015年5月27日
   作    者   : h00246512
   修改内容   : 新建

*****************************************************************************/
CNAS_EHSM_MSG_COMPARE_STRU g_astEhsmMsgPrioCompareWithActivatingTbl[] =
{
    /* Activating过程中收到HSD的关机请求的消息优先级比较 */
    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(UEPS_PID_HSD, ID_HSD_EHSM_POWER_OFF_REQ),
                               CNAS_EHSM_CompareHsdPowerOffReqPrioWithActivating),

    /* Activating过程中收到HSD的关机请求的消息优先级比较 */
    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(UEPS_PID_HSM, ID_HSM_EHSM_SUSPEND_IND),
                               CNAS_EHSM_CompareHsmSuspendIndPrioWithActivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(MSPS_PID_PPPC, ID_CTTF_CNAS_EHRPD_DETACH_IND),
                               CNAS_EHSM_CompareCttfEhrpdDetachIndPrioWithActivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_DEACTIVATE_REQ),
                               CNAS_EHSM_CompareTafPdnDeactivateReqWithActivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_RECONN_REQ),
                               CNAS_EHSM_CompareTafPdnReconnReqWithActivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ),
                               CNAS_EHSM_CompareTafPdnActivateReqWithActivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_LOC_DETACH_NOTIFY),
                               CNAS_EHSM_CompareTafLocalDetachNotifyWithActivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_LOC_DEACTIVATE_NOTIFY),
                               CNAS_EHSM_CompareTafLocalDeactivateNotifyWithActivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(UEPS_PID_HSM, ID_HSM_EHSM_SESSION_INFO_IND),
                               CNAS_EHSM_CompareHsmSessionInfoIndPrioWithActivating)/* ,

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(UEPS_PID_HSD, ID_HSD_EHSM_POWER_SAVE_REQ),
                               CNAS_EHSM_CompareHsdPowerSaveReqPrioWithActivating)*/
};

/*****************************************************************************
 全局变量名    : g_astEhmsMsgPrioCompareWithDeactivatingTbl
 全局变量说明  : Activating状态机消息优先级比较处理的比较表
 1.日    期   : 2015年5月27日
   作    者   : h00246512
   修改内容   : 新建

*****************************************************************************/
CNAS_EHSM_MSG_COMPARE_STRU g_astEhsmMsgPrioCompareWithDeactivatingTbl[] =
{
    /* Deactivating过程中收到HSD的关机请求的消息优先级比较 */
    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(UEPS_PID_HSD, ID_HSD_EHSM_POWER_OFF_REQ),
                               CNAS_EHSM_CompareHsdPowerOffReqPrioWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(UEPS_PID_HSM, ID_HSM_EHSM_SUSPEND_IND),
                               CNAS_EHSM_CompareHsmSuspendIndPrioWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(MSPS_PID_PPPC, ID_CTTF_CNAS_EHRPD_DETACH_IND),
                               CNAS_EHSM_CompareCttfEhrpdDetachIndPrioWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ),
                               CNAS_EHSM_CompareTafPdnActivateReqPrioWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_DEACTIVATE_REQ),
                               CNAS_EHSM_CompareTafPdnDeactivateReqPrioWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_RECONN_REQ),
                               CNAS_EHSM_CompareTafReconnReqPrioWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_LOC_DETACH_NOTIFY),
                               CNAS_EHSM_CompareTafLocalDetachNotifyPrioWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_LOC_DEACTIVATE_NOTIFY),
                               CNAS_EHSM_CompareTafLocalDeactivateNotifyWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(UEPS_PID_HSM, ID_HSM_EHSM_SESSION_INFO_IND),
                               CNAS_EHSM_CompareHsmSessionInfoIndPrioWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_DISC_NOTIFY),
                               CNAS_EHSM_CompareTafDiscNotifyPrioWithDeactivating)/* ,


    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(UEPS_PID_HSD, ID_HSD_EHSM_POWER_SAVE_REQ),
                               CNAS_EHSM_CompareHsdPowerSaveReqPrioWithDeactivating)*/

};



/*****************************************************************************
 全局变量名    : g_astEhsmMsgCompareTbl
 全局变量说明  : EHSM状态机比较函数表单
  1.日    期   : 2015年5月27日
    作    者   : h00246512
    修改内容   : 新建
*****************************************************************************/
CNAS_EHSM_FSM_MSG_COMPARE_STRU g_astEhsmMsgCompareTbl[] =
{
    /* ACTIVATING 状态机比较函数表*/
    CNAS_EHSM_FSM_COMPARE_TBL_ITEM(CNAS_EHSM_FSM_ACTIVATING,
                                 g_astEhsmMsgPrioCompareWithActivatingTbl),

    /* DEACTIVATING 状态机比较函数表*/
    CNAS_EHSM_FSM_COMPARE_TBL_ITEM(CNAS_EHSM_FSM_DEACTIVATING,
                                 g_astEhsmMsgPrioCompareWithDeactivatingTbl),
};

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : CNAS_EHSM_CompareHsdPowerOffReqPrioWithActivating
 功能描述  : 将EHSM收到的HSD的power off消息与Activating状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年5月27日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareHsdPowerOffReqPrioWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    CNAS_EHSM_StartTimer(TI_CNAS_EHSM_PROTECTING_POWER_OFF_PROCESS, TI_CNAS_EHSM_PROTECTING_POWER_OFF_PROCESS_LEN);

    CNAS_EHSM_ClearAllCacheMsg();

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 函 数 名  : CNAS_EHSM_CompareHsmSuspendIndPrioWithActivating
 功能描述  : 将EHSM收到的HSM的Suspend消息与Activating状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年5月27日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareHsmSuspendIndPrioWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_CompareCttfEhrpdDetachIndPrioWithActivating
 功能描述  : 将EHSM收到的CTTF的Ehrpd_Detach_Ind消息与Activating状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年5月27日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareCttfEhrpdDetachIndPrioWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    VOS_UINT32                              i;
    CNAS_EHSM_CACHE_MSG_QUEUE_STRU         *pstMsgQueue = VOS_NULL_PTR;
    MSG_HEADER_STRU                        *pstCacheMsgHdr;
    REL_TIMER_MSG                          *pstTimerMsg;
    VOS_UINT32                              ulCacheMsgEventType;

    pstMsgQueue     = CNAS_EHSM_GetCacheMsgAddr();
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    /* 清除之前缓存的不需要处理的消息 */
    for (i = 0; i < pstMsgQueue->ucCacheMsgNum; i++)
    {
        pstCacheMsgHdr = (MSG_HEADER_STRU *)(pstMsgQueue->pastCacheMsg[i]);

        if (VOS_NULL_PTR == pstCacheMsgHdr)
        {
            continue;
        }

        if (VOS_PID_TIMER == pstCacheMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstCacheMsgHdr;

            ulCacheMsgEventType  = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulCacheMsgEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstCacheMsgHdr->ulMsgName);
        }

        if ((CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_DEACTIVATE_REQ) == ulCacheMsgEventType)
         || (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_RECONN_REQ)         == ulCacheMsgEventType)
         || (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ)   == ulCacheMsgEventType))
        {
            CNAS_EHSM_ClearCacheMsg((VOS_UINT8)i);
        }
    }

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_CompareTafPdnDeactivateReqWithActivating
 功能描述  : 将EHSM收到的TAF的Pdn Deactivate Req消息与Activating状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年6月8日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareTafPdnDeactivateReqWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    VOS_UINT8                           ucCid;
    APS_EHSM_PDN_DEACTIVATE_REQ_STRU   *pstPdnDeactReq;

    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    pstPdnDeactReq  = (APS_EHSM_PDN_DEACTIVATE_REQ_STRU*)pstMsg;
    ucCid           = CNAS_EHSM_GetCid_Activating();

    if (ucCid == pstPdnDeactReq->ucCid)
    {
        return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
    }


    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_CompareTafPdnReconnReqWithActivating
 功能描述  : 将EHSM收到的TAF的Pdn Reconn Req消息与Activating状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年6月8日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareTafPdnReconnReqWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_CompareTafPdnActivateReqWithActivating
 功能描述  : 将EHSM收到的TAF的Pdn Activate Req消息与Activating状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年6月8日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareTafPdnActivateReqWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_STORE;
}


/*****************************************************************************
 函 数 名  : CNAS_EHSM_CompareTafLocalDetachNotifyWithActivating
 功能描述  : 将EHSM收到的TAF的ID_APS_EHSM_LOC_DETACH_NOTIFY消息与Activating状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年6月8日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareTafLocalDetachNotifyWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_CompareTafLocalDeactivateNotifyWithActivating
 功能描述  : 将EHSM收到的TAF的ID_APS_EHSM_LOC_DEACTIVATE_NOTIFY消息与Activating状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年6月8日
   作    者   : h00246512
   修改内容   : 新生成函数
 2.日    期   : 2015年9月9日
   作    者   : w00176964
   修改内容   : CNAS内存裁剪
*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareTafLocalDeactivateNotifyWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    VOS_UINT32                              i;
    CNAS_EHSM_CACHE_MSG_QUEUE_STRU         *pstMsgQueue = VOS_NULL_PTR;
    APS_EHSM_PDN_ACTIVATE_REQ_STRU         *pstPdnAct;
    APS_EHSM_PDN_DEACTIVATE_REQ_STRU       *pstPdnDeact;
    APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU    *pstLocPdnDeact;
    /* Added by w00176964 for CNAS内存裁剪, 2015-9-9, begin */
    MSG_HEADER_STRU                        *pstCacheMsgHdr;
    REL_TIMER_MSG                          *pstTimerMsg;
    VOS_UINT32                              ulCacheMsgEventType;
    /* Added by w00176964 for CNAS内存裁剪, 2015-9-9, end */

    pstMsgQueue     = CNAS_EHSM_GetCacheMsgAddr();
    pstLocPdnDeact  = (APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU*)pstMsg;
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    /* 查看缓存中有没有相同CID的操作，有的话，清除缓存 */
    for  (i = 0; i < pstMsgQueue->ucCacheMsgNum; i++)
    {
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, begin */
        pstCacheMsgHdr          = (MSG_HEADER_STRU *)(pstMsgQueue->pastCacheMsg[i]);

        if (VOS_NULL_PTR == pstCacheMsgHdr)
        {
            continue;
        }

        if (VOS_PID_TIMER == pstCacheMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstCacheMsgHdr;

            ulCacheMsgEventType  = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulCacheMsgEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstCacheMsgHdr->ulMsgName);
        }

        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ) == ulCacheMsgEventType)
        {
            pstPdnAct = (APS_EHSM_PDN_ACTIVATE_REQ_STRU*)pstCacheMsgHdr;
            if (pstLocPdnDeact->ucCid == pstPdnAct->ucCid)
            {
                CNAS_EHSM_ClearCacheMsg((VOS_UINT8)i);
                return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_DISCARD;
            }
        }

        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_DEACTIVATE_REQ) == ulCacheMsgEventType)
        {
            pstPdnDeact = (APS_EHSM_PDN_DEACTIVATE_REQ_STRU*)pstCacheMsgHdr;
            if (pstLocPdnDeact->ucCid == pstPdnDeact->ucCid)
            {
                CNAS_EHSM_ClearCacheMsg((VOS_UINT8)i);
            }
        }
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, end */
    }

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}



/*****************************************************************************
 函 数 名  : CNAS_EHSM_CompareHsdPowerOffReqPrioWithDeactivating
 功能描述  : 将EHSM收到的HSD的power off消息与Deactivating状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年5月27日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareHsdPowerOffReqPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    CNAS_EHSM_StartTimer(TI_CNAS_EHSM_PROTECTING_POWER_OFF_PROCESS, TI_CNAS_EHSM_PROTECTING_POWER_OFF_PROCESS_LEN);

    CNAS_EHSM_ClearAllCacheMsg();

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_CompareHsmSuspendIndPrioWithDeactivating
 功能描述  : 将EHSM收到的HSM的Suspend消息与Deactivating状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年5月27日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareHsmSuspendIndPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 函 数 名  : CNAS_EHSM_CompareCttfEhrpdDetachIndPrioWithDeactivating
 功能描述  : 将EHSM收到的CTTF的Detach Ind消息与Deactivating状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年5月27日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareCttfEhrpdDetachIndPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    VOS_UINT32                              i;
    CNAS_EHSM_CACHE_MSG_QUEUE_STRU         *pstMsgQueue = VOS_NULL_PTR;
    MSG_HEADER_STRU                        *pstCacheMsgHdr;
    REL_TIMER_MSG                          *pstTimerMsg;
    VOS_UINT32                              ulCacheMsgEventType;

    pstMsgQueue     = CNAS_EHSM_GetCacheMsgAddr();
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    /* 清除之前缓存的不需要处理的消息 */
    for (i = 0; i < pstMsgQueue->ucCacheMsgNum; i++)
    {
        pstCacheMsgHdr = (MSG_HEADER_STRU *)(pstMsgQueue->pastCacheMsg[i]);

        if (VOS_NULL_PTR == pstCacheMsgHdr)
        {
            continue;
        }

        if (VOS_PID_TIMER == pstCacheMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstCacheMsgHdr;

            ulCacheMsgEventType  = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulCacheMsgEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstCacheMsgHdr->ulMsgName);
        }

        if ((CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_DEACTIVATE_REQ) == ulCacheMsgEventType)
         || (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_RECONN_REQ)         == ulCacheMsgEventType)
         || (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ)   == ulCacheMsgEventType))
        {
            CNAS_EHSM_ClearCacheMsg((VOS_UINT8)i);
        }
    }

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_CompareTafPdnActivateReqPrioWithDeactivating
 功能描述  : 将EHSM收到的APS的Pdn Activate Req消息与Deactivating状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年5月27日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareTafPdnActivateReqPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_CompareTafPdnDeactivateReqPrioWithDeactivating
 功能描述  : 将EHSM收到的APS的Pdn Deactivate Req消息与Deactivating状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年5月27日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareTafPdnDeactivateReqPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_CompareTafReconnReqPrioWithDeactivating
 功能描述  : 将EHSM收到的APS的Reconn Req消息与Deactivating状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年5月27日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareTafReconnReqPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_CompareTafLocalDetachNotifyPrioWithDeactivating
 功能描述  : 将EHSM收到的ID_APS_EHSM_LOC_DETACH_NOTIFY消息与Deactivating状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年5月27日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareTafLocalDetachNotifyPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 函 数 名  : CNAS_EHSM_CompareTafLocalDeactivateNotifyWithDeactivating
 功能描述  : 将EHSM收到的TAF的ID_APS_EHSM_LOC_DEACTIVATE_NOTIFY消息与Deactivating状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年6月8日
   作    者   : h00246512
   修改内容   : 新生成函数
 2.日    期   : 2015年9月8日
   作    者   : w00176964
   修改内容   : CNAS内存裁剪
*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareTafLocalDeactivateNotifyWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    VOS_UINT32                              i;
    CNAS_EHSM_CACHE_MSG_QUEUE_STRU         *pstMsgQueue = VOS_NULL_PTR;
    APS_EHSM_PDN_ACTIVATE_REQ_STRU         *pstPdnAct;
    APS_EHSM_PDN_DEACTIVATE_REQ_STRU       *pstPdnDeact;
    APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU    *pstLocPdnDeact;
    /* Added by w00176964 for CNAS内存裁剪, 2015-9-9, begin */
    MSG_HEADER_STRU                        *pstCacheMsgHdr;
    VOS_UINT32                              ulCacheMsgEventType;
    REL_TIMER_MSG                          *pstTimerMsg;
    /* Added by w00176964 for CNAS内存裁剪, 2015-9-9, end */

    pstMsgQueue     = CNAS_EHSM_GetCacheMsgAddr();
    pstLocPdnDeact  = (APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU*)pstMsg;
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    /* 查看缓存中有没有相同CID的操作，有的话，清除缓存 */
    for  (i = 0; i < pstMsgQueue->ucCacheMsgNum; i++)
    {
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, begin */
        pstCacheMsgHdr          = (MSG_HEADER_STRU *)(pstMsgQueue->pastCacheMsg[i]);

        if (VOS_PID_TIMER == pstCacheMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstCacheMsgHdr;

            ulCacheMsgEventType  = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulCacheMsgEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstCacheMsgHdr->ulMsgName);
        }

        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ) == ulCacheMsgEventType)
        {
            pstPdnAct = (APS_EHSM_PDN_ACTIVATE_REQ_STRU*)pstCacheMsgHdr;
            if (pstLocPdnDeact->ucCid == pstPdnAct->ucCid)
            {
                CNAS_EHSM_ClearCacheMsg((VOS_UINT8)i);
                return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_DISCARD;
            }
        }

        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_DEACTIVATE_REQ) == ulCacheMsgEventType)
        {
            pstPdnDeact = (APS_EHSM_PDN_DEACTIVATE_REQ_STRU*)pstCacheMsgHdr;
            if (pstLocPdnDeact->ucCid == pstPdnDeact->ucCid)
            {
                CNAS_EHSM_ClearCacheMsg((VOS_UINT8)i);
            }
        }
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, end */
    }

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_CompareCttfEhrpdDetachIndPrioWithActivating
 功能描述  : 将EHSM收到的CTTF的Ehrpd_Detach_Ind消息与Activating状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年07月14日
   作    者   : y00314741
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareHsmSessionInfoIndPrioWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    HSM_EHSM_SESSION_INFO_IND_STRU     *pstSessionInfo = VOS_NULL_PTR;

    pstSessionInfo = (HSM_EHSM_SESSION_INFO_IND_STRU *)pstMsg;

    if (EHSM_HSM_SESSION_TYPE_EHRPD != pstSessionInfo->enSessionType)
    {
        *penAbortType = CNAS_EHSM_ABORT_BUTT;

        return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
    }
    else
    {
        *penAbortType = CNAS_EHSM_ABORT_FSM_IMMEDIATELY;

        return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_CompareCttfEhrpdDetachIndPrioWithActivating
 功能描述  : 将EHSM收到的CTTF的Ehrpd_Detach_Ind消息与Activating状态机的优先级进行比较
 输入参数  : ulEventType:消息类型
             pstMsg     :消息内容
 输出参数  : penAbortType:打断类型
 返 回 值  : 比较结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年07月14日
   作    者   : y00314741
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareHsmSessionInfoIndPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    HSM_EHSM_SESSION_INFO_IND_STRU     *pstSessionInfo = VOS_NULL_PTR;

    pstSessionInfo = (HSM_EHSM_SESSION_INFO_IND_STRU *)pstMsg;

    if (EHSM_HSM_SESSION_TYPE_EHRPD != pstSessionInfo->enSessionType)
    {
        *penAbortType   = CNAS_EHSM_ABORT_BUTT;

        return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
    }
    else
    {
        *penAbortType = CNAS_EHSM_ABORT_FSM_IMMEDIATELY;

        return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_CompareTafDiscNotifyPrioWithDeactivating
 功能描述  : DEACTIVING状态下缓存处理TAF发来的DISC_NOTIFY消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
             CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月20日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareTafDiscNotifyPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_STORE;
}


/*****************************************************************************
 函 数 名  : CNAS_EHSM_FindMsgPrioCompareFun
 功能描述  : 查找消息比较函数
 输入参数  : ulEventType:待处理的消息类型
             pstMsg     :待处理的消息内容
             ulFsmEntryEventType    :状态机的入口消息
             enFsmId                :状态机的ID
 输出参数  : 无
 返 回 值  : 当前待处理消息的优先级
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月27日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_EHSM_MSG_COMPARE_FUNC  CNAS_EHSM_FindMsgPrioCompareFun(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_FSM_ID_ENUM_UINT32        enFsmId
)
{
    CNAS_EHSM_FSM_MSG_COMPARE_STRU     *pstFsmCompareTbl = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT32                          ulTblSize;

    ulTblSize = sizeof(g_astEhsmMsgCompareTbl)/sizeof(CNAS_EHSM_FSM_MSG_COMPARE_STRU);

    for ( i = 0 ; i < ulTblSize ; i++ )
    {
        if ( enFsmId == g_astEhsmMsgCompareTbl[i].enFsmId)
        {
            pstFsmCompareTbl = &g_astEhsmMsgCompareTbl[i];
            break;
        }
    }

    /* 未能找到该状态机的比较函数表,直接返回空指针 */
    if ( VOS_NULL_PTR == pstFsmCompareTbl )
    {
        return VOS_NULL_PTR;
    }

    for ( i = 0 ; i < pstFsmCompareTbl->ulSize; i++ )
    {
        /* 查找不同事件的比较函数 */
        if ( pstFsmCompareTbl->pfCompareTbl[i].ulCurrEventType == ulEventType)
        {
            return pstFsmCompareTbl->pfCompareTbl[i].pfCompareFun;
        }
    }

    /* 未找到处理函数直接返回空指针 */
    return VOS_NULL_PTR;
}



/*****************************************************************************
 函 数 名  : CNAS_EHSM_GetMsgComparePrio
 功能描述  : 获取消息优先级比较后的结果
 输入参数  : ulEventType:待处理的消息类型
             pstMsg     :待处理的消息内容
 输出参数  : pulAbortType:返回值为打断时,返回的打断类型
 返 回 值  : 当前待处理消息的优先级
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月27日
    作    者   : h00246512
    修改内容   : 新生成函数
*****************************************************************************/
CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32 CNAS_EHSM_GetMsgComparePrioRslt(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    CNAS_EHSM_MSG_COMPARE_FUNC                      pfCompareFunc;
    CNAS_EHSM_FSM_ID_ENUM_UINT32                    enCurrFsmId;
    CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32     enRslt;

    /*  获取当前状态机的ID */
    enCurrFsmId         = CNAS_EHSM_GetCurrFsmId();

    if (CNAS_EHSM_FSM_BUTT <= enCurrFsmId)
    {
        CNAS_ERROR_LOG(UEPS_PID_EHSM, "ERROR:FsmId Error");
    }

    /*  获取比较函数 CNAS_EHSM_FindMsgPrioCompareFun() */
    pfCompareFunc       = CNAS_EHSM_FindMsgPrioCompareFun(ulEventType, pstMsg, enCurrFsmId);

    /* 未找到处理函数,则默认消息丢弃 */
    if ( VOS_NULL_PTR == pfCompareFunc )
    {
        *penAbortType = CNAS_EHSM_ABORT_BUTT;
        return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* 调用比较函数,返回优先级和打断类型 */
    enRslt = pfCompareFunc(ulEventType, pstMsg, penAbortType);

    return enRslt;

}


#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

