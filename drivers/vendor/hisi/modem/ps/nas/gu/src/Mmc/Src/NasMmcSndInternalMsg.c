
/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "NasMmcSndInternalMsg.h"
#include "NasComm.h"
#include "NasMmlCtx.h"
#include "NasMmlLib.h"
#include "NasMmlMsgProc.h"
#include "NasMmcComFunc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_SND_INTERNALMSG_C

/*****************************************************************************
  2 全局变量
*****************************************************************************/

/*****************************************************************************
  3 宏定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  4 函数实现
*****************************************************************************/


VOS_VOID  NAS_MMC_SndAbortFsmMsg(
    VOS_UINT32                          ulEventType,
    NAS_MMC_ABORT_FSM_TYPE_UINT8        enAbortFsmType
)
{
    NAS_MMC_ABORT_FSM_STRU              *pstMsg         = VOS_NULL_PTR;
    NAS_MML_INTERNAL_MSG_BUF_STRU       *pstInternalMsg = VOS_NULL_PTR;
    VOS_UINT32                           ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(NAS_MMC_ABORT_FSM_STRU);

    pstInternalMsg  = NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstMsg                                  = (NAS_MMC_ABORT_FSM_STRU*)pstInternalMsg;
    pstMsg->ulSenderCpuId                   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId                 = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid                   = WUEPS_PID_MMC;
    pstMsg->ulLength                        = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgID                         = MMCMMC_ABORT_FSM_REQ;

    pstMsg->ulEventType                     = ulEventType;

    pstMsg->enAbortFsmType                  = enAbortFsmType;

    NAS_MML_SndInternalMsg((VOS_VOID*)(pstMsg));

}


VOS_VOID NAS_MMC_SndInterAnyCellSearchReq(
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstAnycellSrchRatList,
    NAS_MMC_ANYCELL_SEARCH_SCENE_ENUM_UINT8                 enAnycellSearchScene
)
{
    /* 构造内部Ancell搜网消息 */
    NAS_MMC_INTER_ANYCELL_SEARCH_REQ_STRU                  *pstInternalMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(NAS_MMC_INTER_ANYCELL_SEARCH_REQ_STRU);

    pstInternalMsg  = (NAS_MMC_INTER_ANYCELL_SEARCH_REQ_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstInternalMsg + VOS_MSG_HEAD_LENGTH, 0,
          sizeof(NAS_MMC_INTER_ANYCELL_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstInternalMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstInternalMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstInternalMsg->stMsgHeader.ulMsgName       = MMCMMC_INTER_ANYCELL_SEARCH_REQ;
    pstInternalMsg->stMsgHeader.ulLength        = sizeof(NAS_MMC_INTER_ANYCELL_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstInternalMsg->enAnycellSearchScene        = enAnycellSearchScene;

    if (VOS_NULL_PTR == pstAnycellSrchRatList)
    {
        /*  不指定接入技术时，根据开机和SYSCFG/SYSCFGEX中确定的接入模式和当前模式，
        设定需要进行搜网的接入技术, 优先在当前模式发起搜网 */
        PS_MEM_CPY(&(pstInternalMsg->stAnycellSrchRatList),
                   NAS_MML_GetMsPrioRatList(), sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

        NAS_MML_SortSpecRatPrioHighest(NAS_MML_GetCurrNetRatType(),
                                       &(pstInternalMsg->stAnycellSrchRatList));

    }
    else
    {
        PS_MEM_CPY(&(pstInternalMsg->stAnycellSrchRatList),
                   pstAnycellSrchRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    }

    NAS_MML_SndInternalMsg(pstInternalMsg);

}


VOS_VOID NAS_MMC_SndInterPlmnSearchReq(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32    enPlmnSearchScene,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU    *pstIntraPlmnSrchInfo,
    VOS_UINT8                                ucRatNum
)
{
    /*根据场景和现在的PlmnId，构造内部搜网消息*/
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU  *pstInternalMsg;
    VOS_UINT32                           ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU);

    pstInternalMsg  = (NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    NAS_MMC_BulidInterPlmnSearchReqMsg(enPlmnSearchScene, pstIntraPlmnSrchInfo, ucRatNum, pstInternalMsg);

    NAS_MML_SndInternalMsg(pstInternalMsg);

    NAS_MMC_RecordOosEventForPlmnSearchScene(enPlmnSearchScene);

}



VOS_VOID NAS_MMC_SndInterPlmnListReq(VOS_VOID)
{
    NAS_MMC_INTER_PLMN_LIST_REQ_STRU   *pstInternalMsg;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(NAS_MMC_INTER_PLMN_LIST_REQ_STRU);

    pstInternalMsg  = (NAS_MMC_INTER_PLMN_LIST_REQ_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }


    PS_MEM_SET((VOS_UINT8*)pstInternalMsg + VOS_MSG_HEAD_LENGTH, 0,
              sizeof(NAS_MMC_INTER_PLMN_LIST_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstInternalMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulMsgName       = MMCMMC_INTER_PLMN_LIST_REQ;
    pstInternalMsg->MsgHeader.ulLength        = sizeof(NAS_MMC_INTER_PLMN_LIST_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    NAS_MML_SndInternalMsg(pstInternalMsg);
}


VOS_VOID NAS_MMC_SndSwitchOnRlst(VOS_UINT32 ulResult)
{
    NAS_MMC_SWITCHON_RLST_STRU         *pstMsg              = VOS_NULL_PTR;
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstInternalMsg      = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(NAS_MMC_SWITCHON_RLST_STRU);

    pstInternalMsg  = NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }
    pstMsg                            = (NAS_MMC_SWITCHON_RLST_STRU *)pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulMsgName       = MMCMMC_SWITCH_ON_RSLT_CNF;
    pstMsg->MsgHeader.ulLength        = sizeof(NAS_MMC_SWITCHON_RLST_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulResult                  = ulResult;


    NAS_MML_InsertInternalMsgHead(pstMsg);

}



VOS_VOID NAS_MMC_SndPowerOffRslt(
    NAS_MMC_POWEROFF_RSLT_ENUM_UINT32   enRslt
)
{
    NAS_MMCMMC_POWEROFF_RSLT_STRU      *pstMsg;
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstInternalMsg;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(NAS_MMCMMC_POWEROFF_RSLT_STRU);

    pstInternalMsg  = NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstMsg                              = (NAS_MMCMMC_POWEROFF_RSLT_STRU *)pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = MMCMMC_POWER_OFF_RSLT_CNF;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MMCMMC_POWEROFF_RSLT_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enRslt                      = enRslt;


    NAS_MML_InsertInternalMsgHead(pstMsg);


    (VOS_VOID)vos_printf("NAS_MMC_SndPowerOffRslt:0x%x",VOS_GetSlice());

    return;
}


VOS_VOID NAS_MMC_SndPlmnListRslt(
    NAS_MMC_PLMN_LIST_RESULT_ENUM_UINT32                    enRslt,
    VOS_UINT8                                               ucNeedPlmnSearch,
    NAS_MMC_PLMN_LIST_SEARCH_SCENE_ENUM_UINT8               enPlmnListSearchScene,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo,
    NAS_MMC_PLMN_LIST_REG_RSLT_INFO_STRU                   *pstRegRsltInfo
)
{
    NAS_MMCMMC_PLMN_LIST_RSLT_STRU     *pstMsg = VOS_NULL_PTR;
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstInternalMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          i;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(NAS_MMCMMC_PLMN_LIST_RSLT_STRU);

    pstInternalMsg  = NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstMsg                              = (NAS_MMCMMC_PLMN_LIST_RSLT_STRU *)pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = MMCMMC_PLMN_LIST_RSLT_CNF;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MMCMMC_PLMN_LIST_RSLT_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->ucNeedPlmnSearch            = ucNeedPlmnSearch;
    pstMsg->enRslt                      = enRslt;

    pstMsg->enPlmnListSearchScene       = enPlmnListSearchScene;
    /* 注册结果信息为空 */
    if ( VOS_NULL_PTR == pstRegRsltInfo)
    {
        pstMsg->enCsRegAdditionalAction     = NAS_MMC_ADDITIONAL_ACTION_BUTT;
        pstMsg->enPsRegAdditionalAction     = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    }
    else
    {
        pstMsg->enCsRegAdditionalAction         = pstRegRsltInfo->enCsRegAdditionalAction;
        pstMsg->enPsRegAdditionalAction         = pstRegRsltInfo->enPsRegAdditionalAction;
    }

    /* LIST搜网结果 */
    if (VOS_NULL_PTR == pstListInfo)
    {
        /* 设置接入技术为无效 */
        for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
        {
            pstMsg->astPlmnSearchInfo[i].enRatType = NAS_MML_NET_RAT_TYPE_BUTT;
        }
    }
    else
    {
        /* 根据消息中携带的搜网信息更新搜网列表 */
        PS_MEM_CPY(pstMsg->astPlmnSearchInfo,
                            pstListInfo, sizeof(pstMsg->astPlmnSearchInfo));
    }


    NAS_MML_InsertInternalMsgHead(pstMsg);


    return;
}


VOS_VOID NAS_MMC_SndAnycellSearchRslt(
    NAS_MMC_ANYCELL_SEARCH_RESULT_ENUM_UINT32               enResult
)
{
    NAS_MMCMMC_ANYCELL_SEARCH_RSLT_STRU                    *pstInternalMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulLen;


    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(NAS_MMCMMC_ANYCELL_SEARCH_RSLT_STRU);
    pstInternalMsg  = (NAS_MMCMMC_ANYCELL_SEARCH_RSLT_STRU *)NAS_MML_GetIntMsgSendBuf(ulLen);

    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }
    pstInternalMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulMsgName       = MMCMMC_ANYCELL_SEARCH_RSLT_CNF;
    pstInternalMsg->MsgHeader.ulLength        = sizeof(NAS_MMCMMC_ANYCELL_SEARCH_RSLT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstInternalMsg->enResult                  = enResult;


    NAS_MML_InsertInternalMsgHead(pstInternalMsg);


    return;
}




VOS_VOID  NAS_MMC_SndPlmnSelectionRslt(
    NAS_MMC_PLMN_SELECTION_RESULT_ENUM_UINT32               enPlmnSelectionRslt,
    VOS_UINT32                                              ulCampFlg,
    NAS_MMC_RAT_SEARCH_INFO_STRU                           *pstSearchRatInfo,
    VOS_UINT32                                              ulRatNum,
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   ulPlmnSearchScene
)
{
    NAS_MMCMMC_PLMN_SELECTION_RSLT_STRU                    *pstInternalMsg = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstInternalMsg  = (NAS_MMCMMC_PLMN_SELECTION_RSLT_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(NAS_MMCMMC_PLMN_SELECTION_RSLT_STRU));

    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstInternalMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulMsgName       = MMCMMC_PLMN_SELECTION_RSLT_CNF;
    pstInternalMsg->MsgHeader.ulLength        = sizeof(NAS_MMCMMC_PLMN_SELECTION_RSLT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstInternalMsg->enResult                  = enPlmnSelectionRslt;
    pstInternalMsg->ulCampFlg                 = ulCampFlg;
    pstInternalMsg->ulPlmnSearchScene         = ulPlmnSearchScene;

    /* 填充网络覆盖信息 */
    pstInternalMsg->ulRatNum = ulRatNum;

    PS_MEM_CPY(pstInternalMsg->astSearchRatInfo, pstSearchRatInfo,
               (NAS_MML_MAX_RAT_NUM * sizeof(NAS_MMC_RAT_SEARCH_INFO_STRU)));


    NAS_MML_InsertInternalMsgHead(pstInternalMsg);


    return;
}



VOS_VOID  NAS_MMC_SndInterSkipSearchWIndMsg(VOS_VOID)
{
    NAS_MMCMMC_INTER_SKIP_SEARCH_W_IND_STRU                *pstInternalMsg      = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstInternalMsg  = (NAS_MMCMMC_INTER_SKIP_SEARCH_W_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(NAS_MMCMMC_INTER_SKIP_SEARCH_W_IND_STRU));

    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstInternalMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulMsgName       = MMCMMC_INTER_SKIP_SEARCH_W_IND;
    pstInternalMsg->MsgHeader.ulLength        = sizeof(NAS_MMCMMC_INTER_SKIP_SEARCH_W_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_SET(pstInternalMsg->aucReserved, 0x00, sizeof(pstInternalMsg->aucReserved));

    NAS_MML_SndInternalMsg(pstInternalMsg);

    return;
}

VOS_VOID  NAS_MMC_SndInterSkipSearchTdsIndMsg(VOS_VOID)
{
    NAS_MMCMMC_INTER_SKIP_SEARCH_TDS_IND_STRU              *pstInternalMsg = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstInternalMsg  = (NAS_MMCMMC_INTER_SKIP_SEARCH_TDS_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(NAS_MMCMMC_INTER_SKIP_SEARCH_TDS_IND_STRU));

    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstInternalMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulMsgName       = MMCMMC_INTER_SKIP_SEARCH_TDS_IND;
    pstInternalMsg->MsgHeader.ulLength        = sizeof(NAS_MMCMMC_INTER_SKIP_SEARCH_TDS_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_SET(pstInternalMsg->aucReserved, 0x00, sizeof(pstInternalMsg->aucReserved));

    NAS_MML_SndInternalMsg(pstInternalMsg);

    return;
}




VOS_VOID  NAS_MMC_SndInterAbortUtranCtrlPlmnSearchReqMsg(VOS_VOID)
{
    NAS_MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_REQ_STRU *pstInternalMsg = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstInternalMsg  = (NAS_MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(NAS_MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_REQ_STRU));

    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstInternalMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulMsgName       = MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_REQ;
    pstInternalMsg->MsgHeader.ulLength        = sizeof(NAS_MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_SET(pstInternalMsg->aucReserved, 0x00, sizeof(pstInternalMsg->aucReserved));

    NAS_MML_SndInternalMsg(pstInternalMsg);

    return;
}


VOS_VOID  NAS_MMC_SndInterAbortUtranCtrlPlmnSearchCnfMsg(VOS_VOID)
{
    NAS_MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_CNF_STRU *pstInternalMsg = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstInternalMsg  = (NAS_MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_CNF_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(NAS_MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_CNF_STRU));

    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstInternalMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulMsgName       = MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_CNF;
    pstInternalMsg->MsgHeader.ulLength        = sizeof(NAS_MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_SET(pstInternalMsg->aucReserved, 0x00, sizeof(pstInternalMsg->aucReserved));

    NAS_MML_SndInternalMsg(pstInternalMsg);

    return;
}




VOS_VOID  NAS_MMC_SndBgPlmnSearchRslt(
    NAS_MMC_BG_PLMN_SEARCH_RSLT_ENUM_UINT32                 enPlmnSelectionRslt,
    VOS_UINT32                                              ulNeedPlmnSearch,
    NAS_MMC_BG_PLMN_SEARCH_SCENE_ENUM_UINT8                 enBgPlmnSearchScene,
    VOS_UINT32                                              ulBgSearchCompleted,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MMCMMC_BG_PLMN_SEARCH_RSLT_STRU                    *pstInternalMsg = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstInternalMsg  = (NAS_MMCMMC_BG_PLMN_SEARCH_RSLT_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(NAS_MMCMMC_BG_PLMN_SEARCH_RSLT_STRU));

    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        /* 异常打印 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndBgPlmnSearchRslt:pstInternalMsg IS VOS_NULL_PTR ");

        return;
    }

    pstInternalMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstInternalMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstInternalMsg->stMsgHeader.ulMsgName       = MMCMMC_BG_PLMN_SEARCH_RSLT_CNF;
    pstInternalMsg->stMsgHeader.ulLength        = sizeof(NAS_MMCMMC_BG_PLMN_SEARCH_RSLT_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填充消息内容 */
    pstInternalMsg->enRslt                      = enPlmnSelectionRslt;
    pstInternalMsg->ulNeedPlmnSearch            = ulNeedPlmnSearch;
    pstInternalMsg->ulSearchCompleted           = ulBgSearchCompleted;

    pstInternalMsg->enBgPlmnSearchScene         = enBgPlmnSearchScene;

    /* 填充已搜索到的网络信息 */
    if (VOS_NULL_PTR != pstSearchedPlmnListInfo)
    {
        PS_MEM_CPY(&(pstInternalMsg->stSearchedPlmnListInfo), pstSearchedPlmnListInfo,
                   sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU));
    }


    NAS_MML_InsertInternalMsgHead(pstInternalMsg);


    return;
}


VOS_VOID  NAS_MMC_SndSuspendRsltMsg(
    MMC_SUSPEND_CAUSE_ENUM_UINT8                            enSuspendCause,
    NAS_MMC_SUSPEND_RSLT_ENUM_UINT32                        enSuspendRslt,
    NAS_MMC_SUSPEND_FAIL_CAUSE_ENUM_UINT8                   enSuspendFailCause,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo
)
{
    NAS_MMCMMC_SUSPEND_RSLT_STRU       *pstMsg          = VOS_NULL_PTR;
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          i;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(NAS_MMCMMC_SUSPEND_RSLT_STRU);

    pstInternalMsg  = NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }
    pstMsg                              = (NAS_MMCMMC_SUSPEND_RSLT_STRU *)pstInternalMsg;

    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MMCMMC_SUSPEND_RSLT_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = MMCMMC_SUSPEND_RSLT_CNF;
    pstMsg->enSuspendCause              = enSuspendCause;
    pstMsg->enRslt                      = enSuspendRslt;
    pstMsg->enFailCause                 = enSuspendFailCause;

    /* 设置接入技术为无效 */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        pstMsg->astPlmnSearchInfo[i].enRatType = NAS_MML_NET_RAT_TYPE_BUTT;
    }

    /* F态出服务区搜网时才会上报列表 */
    if ( (MMC_SUSPEND_CAUSE_PLMNSEARCH          == enSuspendCause)
       &&(NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST  == enSuspendFailCause))
    {
        if (VOS_NULL_PTR != pstListInfo)
        {
            /* 根据消息中携带的搜网信息更新搜网列表 */
            PS_MEM_CPY(pstMsg->astPlmnSearchInfo,
                        pstListInfo, sizeof(pstMsg->astPlmnSearchInfo));
        }
    }


    NAS_MML_InsertInternalMsgHead(pstMsg);


}


VOS_VOID  NAS_MMC_SndSysCfgRslt(
    VOS_UINT32                          ulSysCfgRslt,
    VOS_UINT32                          ulNeedPlmnSrch,
    VOS_UINT32                          ulIsNeedAttachPs,

    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrePrioRatList
)
{
    NAS_MMCMMC_SysCfg_RSLT_STRU        *pstMsg              = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstMsg          = (NAS_MMCMMC_SysCfg_RSLT_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(NAS_MMCMMC_SysCfg_RSLT_STRU));
    if ( VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = MMCMMC_SYSCFG_RSLT_CNF;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MMCMMC_SysCfg_RSLT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulRslt                      = ulSysCfgRslt;
    pstMsg->ulNeedPlmnSrch              = ulNeedPlmnSrch;

    pstMsg->ulIsNeedAttachPs            = ulIsNeedAttachPs;

    PS_MEM_CPY((VOS_VOID*)&(pstMsg->stPrePrioRatList), (VOS_VOID*)pstPrePrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));


    NAS_MML_InsertInternalMsgHead(pstMsg);


    return;
}



VOS_VOID NAS_MMC_BulidInterPlmnSearchReqMsg(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstIntraPlmnSrchInfo,
    VOS_UINT8                                               ucRatNum,
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU                     *pstMsg
)
{
    VOS_UINT32                          i;

    PS_MEM_SET((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
          sizeof(NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = MMCMMC_INTER_PLMN_SEARCH_REQ;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enPlmnSearchScene           = enPlmnSearchScene;


    /* 设置接入技术为无效 */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        pstMsg->astInterPlmnSearchInfo[i].enRatType = NAS_MML_NET_RAT_TYPE_BUTT;
    }

    if (pstIntraPlmnSrchInfo != VOS_NULL_PTR)
    {
        /* 根据消息中携带的搜网信息更新搜网列表 */
        PS_MEM_CPY(pstMsg->astInterPlmnSearchInfo,
                   pstIntraPlmnSrchInfo,
                   sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU) * ucRatNum);
    }


}


VOS_VOID NAS_MMC_BuildInterDplmnSetReqMsg(
    VOS_UINT8                                              *pucVersion,
    VOS_UINT8                                               ucEhPlmnNum,
    NAS_MSCC_PIF_PLMN_ID_STRU                              *pstEhPlmnInfo,
    NAS_MMC_INTER_DPLMN_SET_REQ_STRU                       *pstMsg
)
{
    /* 清空消息内容 */
    NAS_MMC_CLR_MSG_ENTITY(pstMsg);

    /* 填写消息头 */
    NAS_MMC_CFG_MSG_HDR(pstMsg,
                        WUEPS_PID_MMC,
                        MMCMMC_INTER_DPLMN_SET_REQ,
                        sizeof(NAS_MMC_INTER_DPLMN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息内容 */

    /* EHPLMN个数 */
    pstMsg->ucEhPlmnNum  = ucEhPlmnNum;

    /* EHPLMN列表 */
    PS_MEM_CPY(pstMsg->astEhPlmnInfo,
               pstEhPlmnInfo,
               ucEhPlmnNum * sizeof(NAS_MSCC_PIF_PLMN_ID_STRU));

    /* 版本信息 */
    PS_MEM_CPY(pstMsg->aucVersionId,
               pucVersion,
               NAS_MSCC_PIF_INFO_VERSION_LEN);

    return;
}


VOS_VOID NAS_MMC_SndInterNvimOPlmnRefreshInd(VOS_VOID)
{
    VOS_UINT32                                   ulLen;
    NAS_MMC_INTER_NVIM_OPLMN_REFRESH_IND_STRU   *pstInternalMsg = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(NAS_MMC_INTER_NVIM_OPLMN_REFRESH_IND_STRU);

    pstInternalMsg  = (NAS_MMC_INTER_NVIM_OPLMN_REFRESH_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstInternalMsg + VOS_MSG_HEAD_LENGTH, 0,
              sizeof(NAS_MMC_INTER_NVIM_OPLMN_REFRESH_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstInternalMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulMsgName       = MMCMMC_INTER_NVIM_OPLMN_REFRESH_IND;
    pstInternalMsg->MsgHeader.ulLength        = sizeof(NAS_MMC_INTER_NVIM_OPLMN_REFRESH_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    NAS_MML_SndInternalMsg(pstInternalMsg);
}


VOS_VOID  NAS_MMC_SndGetGeoRsltMsg(
    NAS_MMC_GET_GEO_RSLT_ENUM_UINT32    enGetGeoRslt,
    NAS_MML_PLMN_ID_STRU               *pstGeoPlmn
)
{
    VOS_UINT32                          ulLen;
    NAS_MMCMMC_GET_GEO_RSLT_STRU       *pstMsg         = VOS_NULL_PTR;
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstInternalMsg = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen                               = sizeof(NAS_MMCMMC_GET_GEO_RSLT_STRU);

    pstInternalMsg                      = NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_TRACE_HIGH("Alloc msg fail.");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstInternalMsg + VOS_MSG_HEAD_LENGTH, 0,
                                        sizeof(NAS_MMCMMC_GET_GEO_RSLT_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg                              = (NAS_MMCMMC_GET_GEO_RSLT_STRU*)pstInternalMsg;

    /* 清空消息内容 */
    NAS_MMC_CLR_MSG_ENTITY(pstMsg);

    /* 填写消息头 */
    NAS_MMC_CFG_MSG_HDR(pstMsg,
                        WUEPS_PID_MMC,
                        MMCMMC_GET_GEO_RSLT_CNF,
                        sizeof(NAS_MMCMMC_GET_GEO_RSLT_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息内容 */
    pstMsg->enGetGeoRslt                = enGetGeoRslt;

    NAS_TRACE_HIGH("enGetGeoRslt is %u ", enGetGeoRslt);

    /* 扫频成功，填充覆盖信息 */
    if ((NAS_MMC_GET_GEO_SUCCESS == enGetGeoRslt)
     && (VOS_NULL_PTR != pstGeoPlmn))
    {
        pstMsg->stGetGeoPlmn.ulMcc      = pstGeoPlmn->ulMcc;
        pstMsg->stGetGeoPlmn.ulMnc      = pstGeoPlmn->ulMnc;

        NAS_TRACE_HIGH("ulMcc is %x ;ulMnc is %x ", pstMsg->stGetGeoPlmn.ulMcc, pstMsg->stGetGeoPlmn.ulMnc);
    }

    NAS_MML_InsertInternalMsgHead(pstMsg);

    return;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

