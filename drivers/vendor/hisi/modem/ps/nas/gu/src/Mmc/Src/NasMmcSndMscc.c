/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcSndMscc.c
  版 本 号   : 初稿
  作    者   : L00171473
  生成日期   : 2011年7月13日
  最近修改   :
  功能描述   : MMC发给MSCC的消息的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2011年7月13日
    作    者   : L00171473
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "TafMmcInterface.h"
#include "MsccMmcInterface.h"
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
/* 删除ExtAppMmcInterface.h*/
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */
#include "NasMmSublayerDef.h"
#include "NasMmlCtx.h"
#include "NasMmcCtx.h"
#include "NasMmlLib.h"
#include "NasMmcSndMm.h"
#include "NasComm.h"
#include "NasMmcSndMscc.h"
#include "MnComm.h"
#include "NasMmcFsmMainTbl.h"
#include "NasMmcComFunc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_SND_MSCC_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/


/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccUserSpecPlmnSearchCnf
 功能描述  : 向MSCC发送用户指定搜的结果
 输入参数  : ucResult: 指定搜网的结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月13日
   作    者   : L00171473
   修改内容   : 新生成函数
 2.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccUserSpecPlmnSearchCnf(
    NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_ENUM_UINT8         enResult
)
{
    MMC_MSCC_PLMN_SPECIAL_SEL_CNF_STRU *pstSpecPlmnSrchCnf = VOS_NULL_PTR;

    pstSpecPlmnSrchCnf = (MMC_MSCC_PLMN_SPECIAL_SEL_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                             sizeof(MMC_MSCC_PLMN_SPECIAL_SEL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstSpecPlmnSrchCnf )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccUserSpecPlmnSearchCnf():ERROR:Memory Alloc Error for pstSpecPlmnSrchCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSpecPlmnSrchCnf)+VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_PLMN_SPECIAL_SEL_CNF_STRU)- VOS_MSG_HEAD_LENGTH);
    pstSpecPlmnSrchCnf->enResult                    = enResult;

    /* 填充消息头 */
    pstSpecPlmnSrchCnf->MsgHeader.ulMsgName         = ID_MMC_MSCC_PLMN_SPECIAL_SEL_CNF;
    pstSpecPlmnSrchCnf->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSpecPlmnSrchCnf->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSpecPlmnSrchCnf->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSpecPlmnSrchCnf->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstSpecPlmnSrchCnf->MsgHeader.ulLength          = sizeof(MMC_MSCC_PLMN_SPECIAL_SEL_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstSpecPlmnSrchCnf);

    return;
}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccUserCsgListAbortCnf
 功能描述  : 向MSCC发送用户CSG list搜终止的结果
 输入参数  : pstCsgListAbortCnf - 消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月10日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccUserCsgListAbortCnf(
    MMC_MSCC_CSG_LIST_ABORT_CNF_STRU   *pstCsgListAbortCnf
)
{
    MMC_MSCC_CSG_LIST_ABORT_CNF_STRU   *pstMsg = VOS_NULL_PTR;

    pstMsg = (MMC_MSCC_CSG_LIST_ABORT_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                              sizeof(MMC_MSCC_CSG_LIST_ABORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccUserCsgListAbortCnf():ERROR:Memory Alloc Error for pstPlmnListAbortCnf ");
        return;
    }

    /* 填充消息头 */
    PS_MEM_SET(((VOS_UINT8*)pstMsg) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_CSG_LIST_ABORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstMsg->MsgHeader.ulMsgName         = ID_MMC_MSCC_CSG_LIST_ABORT_CNF;
    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength          = sizeof(MMC_MSCC_CSG_LIST_ABORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 若传进来的消息为空指针则表示列表为空 */
    if ( VOS_NULL_PTR == pstCsgListAbortCnf)
    {
        pstMsg->stCsgIdInfo.ulPlmnWithCsgIdNum = 0;

        PS_SEND_MSG(WUEPS_PID_MMC, pstMsg);

        return;
    }

    PS_MEM_CPY(&pstMsg->stCsgIdInfo, &pstCsgListAbortCnf->stCsgIdInfo, sizeof(pstMsg->stCsgIdInfo));

    PS_SEND_MSG(WUEPS_PID_MMC, pstMsg);
    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccUserCsgListSearchCnf
 功能描述  : 向MSCC发送用户CSG list搜的结果
 输入参数  : pstCsgListSearchCnf - 消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月10日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccUserCsgListSearchCnf(
    MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU  *pstCsgListSearchCnf
)
{
    MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU   *pstMsg = VOS_NULL_PTR;

    pstMsg = (MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                         sizeof(MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccUserCsgListSearchCnf():ERROR:Memory Alloc Error ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstMsg) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);


    /* 填充消息头 */
    pstMsg->MsgHeader.ulMsgName         = ID_MMC_MSCC_CSG_LIST_SEARCH_CNF;
    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength          = sizeof(MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 若传进来的消息为空指针则表示列表为空 */
    if ( VOS_NULL_PTR == pstCsgListSearchCnf)
    {
        pstMsg->stCsgIdInfo.ulPlmnWithCsgIdNum = 0;
        PS_SEND_MSG(WUEPS_PID_MMC, pstMsg);

        return;
    }

    PS_MEM_CPY(&pstMsg->stCsgIdInfo, &pstCsgListSearchCnf->stCsgIdInfo, sizeof(pstMsg->stCsgIdInfo));

    PS_SEND_MSG(WUEPS_PID_MMC, pstMsg);
    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccCsgListSearchRej
 功能描述  : 向MSCC发送用户CSG list搜rej
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月10日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccCsgListSearchRej(VOS_VOID)
{
    MMC_MSCC_CSG_LIST_REJ_STRU         *pstCsgListRej = VOS_NULL_PTR;

    pstCsgListRej = (MMC_MSCC_CSG_LIST_REJ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                         sizeof(MMC_MSCC_CSG_LIST_REJ_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstCsgListRej )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccCsgListSearchRej():ERROR:Memory Alloc Error ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstCsgListRej) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_CSG_LIST_REJ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstCsgListRej->MsgHeader.ulMsgName         = ID_MMC_MSCC_CSG_LIST_REJ;
    pstCsgListRej->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstCsgListRej->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstCsgListRej->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstCsgListRej->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstCsgListRej->MsgHeader.ulLength          = sizeof(MMC_MSCC_CSG_LIST_REJ_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstCsgListRej);
    return;
}

#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccPlmnReselCnf
 功能描述  : 向MSCC发送at+cops=0的结果
 输入参数  : ucResult: 指定搜网的结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月13日
   作    者   : L00171473
   修改内容   : 新生成函数
 2.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccPlmnReselCnf(
    NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_ENUM_UINT8         enPlmnReselRslt
)
{
    MMC_MSCC_PLMN_RESEL_CNF_STRU       *pstReselPlmnSrchCnf = VOS_NULL_PTR;

    pstReselPlmnSrchCnf = (MMC_MSCC_PLMN_RESEL_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                              sizeof(MMC_MSCC_PLMN_RESEL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstReselPlmnSrchCnf )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccPlmnReselCnf():ERROR:Memory Alloc Error for pstReselPlmnSrchCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstReselPlmnSrchCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_PLMN_RESEL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstReselPlmnSrchCnf->enResult                    = enPlmnReselRslt;

    pstReselPlmnSrchCnf->MsgHeader.ulMsgName         = ID_MMC_MSCC_PLMN_RESEL_CNF;
    pstReselPlmnSrchCnf->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstReselPlmnSrchCnf->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstReselPlmnSrchCnf->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstReselPlmnSrchCnf->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstReselPlmnSrchCnf->MsgHeader.ulLength          = sizeof(MMC_MSCC_PLMN_RESEL_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstReselPlmnSrchCnf);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccPlmnSelectStartInd
 功能描述  : 向MSCC上报搜网开始的标示
 输入参数  : enFlag
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年10月09日
   作    者   : l00208543
   修改内容   : DTS2013100904573 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccPlmnSelectStartInd(VOS_VOID)
{
    MMC_MSCC_PLMN_SELECTION_START_IND_STRU  *pstPlmnSeleStartInd = VOS_NULL_PTR;

    pstPlmnSeleStartInd = (MMC_MSCC_PLMN_SELECTION_START_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                           sizeof(MMC_MSCC_PLMN_SELECTION_START_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstPlmnSeleStartInd )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccPlmnSelectStartInd():ERROR:Memory Alloc Error for pstPlmnSelRlstInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstPlmnSeleStartInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_PLMN_SELECTION_START_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstPlmnSeleStartInd->enPlmnSeleStartFlag         = NAS_MSCC_PIF_PLMN_SELECTION_START;

    /* 填充消息头 */
    pstPlmnSeleStartInd->MsgHeader.ulMsgName         = ID_MMC_MSCC_PLMN_SELE_START_IND;
    pstPlmnSeleStartInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPlmnSeleStartInd->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstPlmnSeleStartInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPlmnSeleStartInd->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstPlmnSeleStartInd->MsgHeader.ulLength          = sizeof(MMC_MSCC_PLMN_SELECTION_START_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstPlmnSeleStartInd);
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccPlmnSelectionRsltInd
 功能描述  : 向MSCC上报当前的搜网结果
 输入参数  : enResult: 搜网结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月22日
   作    者   : L00171473
   修改内容   : 新生成函数
 2.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
 3.日    期   : 2015年4月17日
   作    者   : w00176964
   修改内容   : CDMA 1X Iteration 10 Modified:add lte coverage flg and notify mscc
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccPlmnSelectionRsltInd(
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_ENUM_UINT32          enResult,
    VOS_UINT8                                               ucLteCoverFlg
)
{
    NAS_MSCC_PIF_PLMN_SELECTION_RLST_IND_STRU                   *pstPlmnSelRlstInd = VOS_NULL_PTR;

    pstPlmnSelRlstInd = (NAS_MSCC_PIF_PLMN_SELECTION_RLST_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                         sizeof(NAS_MSCC_PIF_PLMN_SELECTION_RLST_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstPlmnSelRlstInd )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccPlmnSelectionRsltInd():ERROR:Memory Alloc Error for pstPlmnSelRlstInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstPlmnSelRlstInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(NAS_MSCC_PIF_PLMN_SELECTION_RLST_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstPlmnSelRlstInd->enResult                    = enResult;

    /* 填充消息头 */
    pstPlmnSelRlstInd->MsgHeader.ulMsgName         = ID_MMC_MSCC_PLMN_SELECTION_RLST_IND;
    pstPlmnSelRlstInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPlmnSelRlstInd->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstPlmnSelRlstInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPlmnSelRlstInd->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstPlmnSelRlstInd->MsgHeader.ulLength          = sizeof(MMC_MSCC_PLMN_SELECTION_RLST_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstPlmnSelRlstInd->ucLteCoverageFlg = ucLteCoverFlg;

    PS_SEND_MSG(WUEPS_PID_MMC, pstPlmnSelRlstInd);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccDetachInd
 功能描述  : 向MSCC发送TAFMMC_DETACH_IND消息
 输入参数  : VOS_UINT32                          ulCnDomainId
             VOS_UINT32                          ulDetachType
             VOS_UINT32                          ulCause
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月11日
   作    者   : lijun 00171473
   修改内容   : 修改函数名及函数实现 for V7R1 phase II
 2.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccDetachInd(
    VOS_UINT32                          ulCnDomainId,
    VOS_UINT32                          ulDetachType,
    VOS_UINT32                          ulCause
)
{
    MMC_MSCC_DETACH_IND_STRU            *pstDetachInd   = VOS_NULL_PTR;
    NAS_MMC_SERVICE_INFO_CTX_STRU      *pstServiceInfo = VOS_NULL_PTR;

    pstDetachInd = (MMC_MSCC_DETACH_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                         sizeof(MMC_MSCC_DETACH_IND_STRU)- VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstDetachInd )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccDetachInd():ERROR:Memory Alloc Error for pstDetachInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstDetachInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_DETACH_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 获取服务状态 */
    pstServiceInfo = NAS_MMC_GetServiceInfo();

    pstDetachInd->enCnDomainId                = ulCnDomainId;
    if (NAS_MSCC_PIF_SRVDOMAIN_CS == ulCnDomainId)
    {
        /* CS域信息有效, 填写"CS服务状态" */
        pstDetachInd->enServiceStatus = pstServiceInfo->enCsCurrService;
    }
    else if (NAS_MSCC_PIF_SRVDOMAIN_PS == ulCnDomainId)
    {
        /* PS域信息有效, 填写"PS服务状态" */
        pstDetachInd->enServiceStatus = pstServiceInfo->enPsCurrService;
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccDetachInd():ERROR: ulCnDomainId Error ");

        /* 释放内存 */
        PS_MEM_FREE(WUEPS_PID_MMC, pstDetachInd);

        return;
    }

    /* 填充消息头 */
    pstDetachInd->MsgHeader.ulMsgName         = ID_MMC_MSCC_DETACH_IND;
    pstDetachInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstDetachInd->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstDetachInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstDetachInd->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstDetachInd->MsgHeader.ulLength          = sizeof(MMC_MSCC_DETACH_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstDetachInd->ulDetachCause               = ulCause;
    pstDetachInd->enNetworkDetachType         = (VOS_UINT8)ulDetachType;

    pstDetachInd->ucOriginalDetachCause       = NAS_MML_GetOriginalRejectCause(pstDetachInd->ulDetachCause);

    PS_SEND_MSG(WUEPS_PID_MMC, pstDetachInd);

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccAttachCnf
 功能描述  : 发送原语D_MMC_ATTACH_CNF的公共处理
 输入参数  : VOS_UINT32  ulCnDomainId
             VOS_UINT32  ulServiceStatus
             VOS_UINT32  ulOpid
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月14日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数
  2.日    期   : 2012年4月27日
    作    者   : l00130025
    修改内容   : DTS2012032303156:MMC的服务状态与上报的服务状态需要转换
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccAttachCnf(
     VOS_UINT32                                             ulCnDomainId,
     NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8                   enMsccServiceStatus,
     VOS_UINT32                                             ulOpid
)
{
    MMC_MSCC_ATTACH_CNF_STRU           *pstAttachCnf = VOS_NULL_PTR;

    pstAttachCnf = (MMC_MSCC_ATTACH_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                        sizeof(MMC_MSCC_ATTACH_CNF_STRU)- VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstAttachCnf )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccAttachCnf():ERROR:Memory Alloc Error for pstAttachCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstAttachCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_ATTACH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstAttachCnf->enServiceStatus             = enMsccServiceStatus;
    pstAttachCnf->enCnDomainId                = ulCnDomainId;
    pstAttachCnf->ulOpID                      = NAS_MMC_GetAttachReqOpId();

    /* 填充消息头 */
    pstAttachCnf->MsgHeader.ulMsgName         = ID_MMC_MSCC_ATTACH_CNF;
    pstAttachCnf->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstAttachCnf->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstAttachCnf->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstAttachCnf->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstAttachCnf->MsgHeader.ulLength          = sizeof(MMC_MSCC_ATTACH_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstAttachCnf);
    return;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccDetachCnf
 功能描述  : 发送原语D_MMC_DETACH_CNF的公共处理
 输入参数  : VOS_UINT32  ulCnDomainId
             VOS_UINT32  ulServiceStatus
             VOS_UINT32  ulOpid
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月14日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数
  2.日    期   : 2012年4月27日
    作    者   : l00130025
    修改内容   : DTS2012032303156:MMC的服务状态与上报的服务状态需要转换
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccDetachCnf(
    VOS_UINT32                                              ulCnDomainId,
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8                    enMsccServiceStatus,
    VOS_UINT32                                              ulOpid,
    NAS_MSCC_PIF_OPER_RESULT_ENUM_UINT32                    enOperRslt
)
{
    MMC_MSCC_DETACH_CNF_STRU            *pstDetachCnf = VOS_NULL_PTR;

    pstDetachCnf = (MMC_MSCC_DETACH_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                        sizeof(MMC_MSCC_DETACH_CNF_STRU)- VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstDetachCnf )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccDetachCnf():ERROR:Memory Alloc Error for pstDetachCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstDetachCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_DETACH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstDetachCnf->enServiceStatus             = enMsccServiceStatus;
    pstDetachCnf->enCnDomainId                = ulCnDomainId;
    pstDetachCnf->enOperRslt                  = enOperRslt;

    pstDetachCnf->MsgHeader.ulMsgName         = ID_MMC_MSCC_DETACH_CNF;
    pstDetachCnf->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstDetachCnf->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstDetachCnf->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstDetachCnf->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstDetachCnf->MsgHeader.ulLength          = sizeof(MMC_MSCC_DETACH_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstDetachCnf);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccServiceStatusInd
 功能描述  : 向MSCC发送服务状态指示
 输入参数  : ulCnDomainId    - 服务域
             ulServiceStatus - 服务状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月19日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
 3.日    期   : 2013年11月20日
   作    者   : w00176964
   修改内容   : Volte PhaseII项目修改:增加CSPS的SIM卡状态
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccServiceStatusInd(
    VOS_UINT32                          ulCnDomainId,
    VOS_UINT32                          ulServiceStatus
)
{
    /* 按MMC_MSCC_SERVICE_STATUS_IND_STRU消息结果封装 */
    MMC_MSCC_SERVICE_STATUS_IND_STRU   *pstServiceStatusInd = VOS_NULL_PTR;

    pstServiceStatusInd = (MMC_MSCC_SERVICE_STATUS_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                              sizeof(MMC_MSCC_SERVICE_STATUS_IND_STRU)- VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstServiceStatusInd )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccServiceStatusInd():ERROR:Memory Alloc Error for pstServiceStatusInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstServiceStatusInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_SERVICE_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-22, begin */
    pstServiceStatusInd->bitOpSrvSta                 = VOS_TRUE;
    pstServiceStatusInd->bitOpRegSta                 = VOS_FALSE;
    pstServiceStatusInd->enServiceStatus             = ulServiceStatus;
    pstServiceStatusInd->enCnDomainId                = ulCnDomainId;
    pstServiceStatusInd->ucSimCsRegStatus            = NAS_MML_GetSimCsRegStatus();
    pstServiceStatusInd->ucSimPsRegStatus            = NAS_MML_GetSimPsRegStatus();
    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-22, end */

    /* 填充消息头 */
    pstServiceStatusInd->MsgHeader.ulMsgName         = ID_MMC_MSCC_SERVICE_STATUS_IND;
    pstServiceStatusInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstServiceStatusInd->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstServiceStatusInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstServiceStatusInd->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstServiceStatusInd->MsgHeader.ulLength          = sizeof(MMC_MSCC_SERVICE_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstServiceStatusInd);
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccRegStatusInd
 功能描述  : 向MSCC发送注册状态指示
 输入参数  : ulCnDomainId - 服务域
             enRegStatus  - 注册状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年4月7日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccRegStatusInd(
    VOS_UINT32                          ulCnDomainId,
    NAS_MSCC_PIF_REG_STATE_ENUM_UINT8   enRegStatus
)
{
    /* 按MMC_MSCC_SERVICE_STATUS_IND_STRU消息结果封装 */
    MMC_MSCC_SERVICE_STATUS_IND_STRU    *pstServiceStatusInd = VOS_NULL_PTR;

    pstServiceStatusInd = (MMC_MSCC_SERVICE_STATUS_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_MSCC_SERVICE_STATUS_IND_STRU)- VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstServiceStatusInd )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccServiceStatusInd():ERROR:Memory Alloc Error for pstServiceStatusInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstServiceStatusInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_SERVICE_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-22, begin */
    pstServiceStatusInd->bitOpSrvSta                 = VOS_FALSE;
    pstServiceStatusInd->bitOpRegSta                 = VOS_TRUE;
    pstServiceStatusInd->enRegState                  = enRegStatus;
    pstServiceStatusInd->enCnDomainId                = ulCnDomainId;
    pstServiceStatusInd->ucSimCsRegStatus            = NAS_MML_GetSimCsRegStatus();
    pstServiceStatusInd->ucSimPsRegStatus            = NAS_MML_GetSimPsRegStatus();
    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-11-22, end */

    if (NAS_MSCC_PIF_SRVDOMAIN_CS == ulCnDomainId)
    {
        pstServiceStatusInd->ulOosCause              = NAS_MML_GetErrLogCsOosCause();
    }
    else
    {
        pstServiceStatusInd->ulOosCause              = NAS_MML_GetErrLogPsOosCause();
    }

    /* 填充消息头 */
    pstServiceStatusInd->MsgHeader.ulMsgName         = ID_MMC_MSCC_SERVICE_STATUS_IND;
    pstServiceStatusInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstServiceStatusInd->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstServiceStatusInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstServiceStatusInd->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstServiceStatusInd->MsgHeader.ulLength          = sizeof(MMC_MSCC_SERVICE_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstServiceStatusInd);
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccCoverageLost
 功能描述  : 向MSCC发送丢网指示
 输入参数  : ucType - 出服务区还是进服务区类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月20日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年4月27日
    作    者   : l00130025
    修改内容   : DTS2012032303156:MMC的服务状态与上报的服务状态需要转换
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  4.日    期   : 2015年10月28日
    作    者   : s00217060
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0修改
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccCoverageInd(
    VOS_UINT8                           ucType
)
{
    MMC_MSCC_COVERAGE_AREA_IND_STRU    *pstCoverageInd   = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmn      = VOS_NULL_PTR;
    VOS_UINT32                          ulDeepTimerLen;

    pstCoverageInd = (MMC_MSCC_COVERAGE_AREA_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                          sizeof(MMC_MSCC_COVERAGE_AREA_IND_STRU)- VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstCoverageInd )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccCoverageInd():ERROR:Memory Alloc Error for pstCoverageInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstCoverageInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_COVERAGE_AREA_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST == ucType)
    {
        pstCoverageInd->enCoverageChgMode  = NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST;
    }
    else
    {
        pstCoverageInd->enCoverageChgMode  = NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_ENTER;

    }

    pstCoverageInd->enCsSvcSta             = NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_CS);
    pstCoverageInd->enPsSvcSta             = NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_PS);

    /* 用于获取当前驻留网络的PLMN */
    pstCurrPlmn = NAS_MML_GetCurrCampPlmnId();

    pstCoverageInd->stPlmnId.ulMcc           = pstCurrPlmn->ulMcc;
    pstCoverageInd->stPlmnId.ulMnc           = pstCurrPlmn->ulMnc;

    /* 用于获取available timer定时器深睡的时长 */
    ulDeepTimerLen = (NAS_MMC_GetPhaseTwoPeriodicSleepTimerLen()) * NAS_MML_ONE_THOUSAND_MILLISECOND;
    if ( NAS_MMC_GetNextAvailableTimerValue() < ulDeepTimerLen)
    {
        pstCoverageInd->ulTimMaxFlg        = VOS_FALSE;
    }
    else
    {
        pstCoverageInd->ulTimMaxFlg        = VOS_TRUE;
    }

    /* 填充消息头 */
    pstCoverageInd->MsgHeader.ulMsgName         = ID_MMC_MSCC_COVERAGE_AREA_IND;
    pstCoverageInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstCoverageInd->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstCoverageInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstCoverageInd->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstCoverageInd->MsgHeader.ulLength          = sizeof(MMC_MSCC_COVERAGE_AREA_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstCoverageInd);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccMmInfo
 功能描述  : 上报网络下发的MM INFO消息中包含的相关信息
 输入参数  : NAS_MM_INFO_IND_STRU *pstMmInfo - MM INFO结构的指针
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月25日
   作    者   : o00132663
   修改内容   : 新生成函数
 2.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccMmInfo(
    NAS_MM_INFO_IND_STRU               *pstMmInfo
)
{
    MMC_MSCC_MM_INFO_IND_STRU           *pstMmInfoInd       = VOS_NULL_PTR;
    NAS_MML_OPERATOR_NAME_INFO_STRU    *pstNasOperatorName = VOS_NULL_PTR;

    pstMmInfoInd = (MMC_MSCC_MM_INFO_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                         sizeof(MMC_MSCC_MM_INFO_IND_STRU)- VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstMmInfoInd )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccMmInfo():ERROR:Memory Alloc Error for pstMmInfoInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstMmInfoInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_MM_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 按MMC_MSCC_MM_INFO_IND_STRU消息封装发送 */
    pstMmInfoInd->ucIeFlg        = pstMmInfo->ucIeFlg;
    pstMmInfoInd->ucDST          = pstMmInfo->ucDST;
    pstMmInfoInd->cLocalTimeZone = pstMmInfo->cLocalTimeZone;
    PS_MEM_CPY(pstMmInfoInd->aucLSAID, pstMmInfo->ucLSAID, sizeof(pstMmInfoInd->aucLSAID));
    pstMmInfoInd->stUniversalTimeandLocalTimeZone = pstMmInfo->stUniversalTimeandLocalTimeZone;
    pstNasOperatorName           = NAS_MML_GetOperatorNameInfo();
    pstMmInfoInd->stName         = *pstNasOperatorName;

    /* 填充消息头 */
    pstMmInfoInd->MsgHeader.ulMsgName         = ID_MMC_MSCC_MM_INFO_IND;
    pstMmInfoInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMmInfoInd->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMmInfoInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMmInfoInd->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstMmInfoInd->MsgHeader.ulLength          = sizeof(MMC_MSCC_MM_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstMmInfoInd);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccDataTranAttri
 功能描述  : 上报当前PDP激活情况
 输入参数  : ucDataTranAttri:PDP激活标志
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月20日
   作    者   : zhoujun \40661
   修改内容   : 新生成函数
 2.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccDataTranAttri(
    NAS_MSCC_PIF_DATATRAN_ATTRI_ENUM_UINT8                  ucDataTranAttri
)
{
    MMC_MSCC_DATATRAN_ATTRI_IND_STRU    *pstDataTransAttriInd = VOS_NULL_PTR;

    pstDataTransAttriInd = (MMC_MSCC_DATATRAN_ATTRI_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                               sizeof(MMC_MSCC_DATATRAN_ATTRI_IND_STRU)- VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstDataTransAttriInd )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccDataTranAttri():ERROR:Memory Alloc Error for pstDataTransAttriInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstDataTransAttriInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_DATATRAN_ATTRI_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstDataTransAttriInd->enDataTranAttri             = ucDataTranAttri;

    /* 填充消息头 */
    pstDataTransAttriInd->MsgHeader.ulMsgName         = ID_MMC_MSCC_DATATRAN_ATTRI_IND;
    pstDataTransAttriInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstDataTransAttriInd->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstDataTransAttriInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstDataTransAttriInd->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstDataTransAttriInd->MsgHeader.ulLength          = sizeof(MMC_MSCC_DATATRAN_ATTRI_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstDataTransAttriInd);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccSysInfo
 功能描述  : 发送MSCC系统消息
 输入参数  : ulMsgType:消息类型
             MmRegState:MM层的注册状态
             GmmRegState:GMM层的注册状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月20日
   作    者   : zhoujun \40661
   修改内容   : 新生成函数
 2.日    期   : 2011年11月30日
   作    者   : H00202780
   修改内容 :增加对LMM上报的服务状态或者注册状态上报给MMA
 3.日    期   : 2012年4月27日
   作    者   : l00130025
   修改内容   : DTS2012032303156:MMC的服务状态与上报的服务状态需要转换
 4.日    期   : 2012年06月13日
   作    者   : s46746
   修改内容   : For CS/PS mode 1，修改LTE系统子模式
 5.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
 6.日    期   : 2013年11月22日
   作    者   : z00161729
   修改内容   : SVLTE优化G-TL ps切换性能修改
 7.日    期   : 2013年10月16日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseII 项目:增加漫游信息参数
 8.日    期   : 2014年01月17日
   作    者   : l00198894
   修改内容   : V9R1C53 C+L 离网重选项目
 9.日    期   : 2014年2月14日
   作    者   : z00161729
   修改内容   : DTS2014021000537:sim卡anycell驻留l的小区mmc收到系统消息转给mma时应该将禁止网络标识置为TRUE，
                不上报pstransfer:1,否则导致ps迁移到modem0后l不注册，乒乓ps迁移
 10.日    期   : 2014年2月20日
    作    者   : z00161729
    修改内容   : DTS2014022100125:单待驻留g的网络，切双待后tl无网络限制驻留g的网络，
               available超时做list搜网构造搜网列表把last rplmn rat排在最前面导致g
               排在第一个无法回l或tds的网络
 11.日    期   : 2014年2月14日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
 12.日    期   : 2014年8月14日
    作    者   : s00217060
    修改内容   : DTS2014080700822:LTE驻留的小区是FDD还是TDD上报给MMA
 13.日    期   : 2015年4月2日
   作    者   : b00269685
   修改内容   : 若是EPLMN包含home，则显示为非漫游
 14.日    期   : 2015年8月13日
    作    者   : l00289540
    修改内容   : User_Exp_Improve修改
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccSysInfo( VOS_VOID )
{
    MMC_MSCC_SYS_INFO_IND_STRU          *pstSysInfoInd       = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo     = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT32                          ulIsHplmnInEplmnList;

    VOS_UINT32                          ulIsCurrCampPlmnInEplmnList;

    VOS_UINT32                          ulForbiddenFlg;

#if (FEATURE_ON == FEATURE_LTE)
    MMC_LMM_PLMN_ID_STRU                stLmmPlmnId;
#endif

    ulForbiddenFlg            = VOS_FALSE;
    ulIsHplmnInEplmnList      = NAS_MML_IsHplmnInEplmnList();

    ulIsCurrCampPlmnInEplmnList = NAS_MML_IsCurrCampPlmnInEplmnList();

    pstSysInfoInd = (MMC_MSCC_SYS_INFO_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                        sizeof(MMC_MSCC_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstSysInfoInd )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccSysInfo():ERROR:Memory Alloc Error for pstSysInfoInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSysInfoInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充MMC_MSCC_SYS_INFO_IND_STRU消息*/
    pstCampPlmnInfo                             = NAS_MML_GetCurrCampPlmnInfo();

    pstSysInfoInd->stCellId.ucCellNum                  = pstCampPlmnInfo->stCampCellInfo.ucCellNum;
    for ( i = 0; i < pstCampPlmnInfo->stCampCellInfo.ucCellNum ; i++ )
    {
        pstSysInfoInd->stCellId.aulCellId[i] = pstCampPlmnInfo->stCampCellInfo.astCellInfo[i].ulCellId;
    }

    pstSysInfoInd->ucRac            = pstCampPlmnInfo->ucRac;
    pstSysInfoInd->usLac            = (pstCampPlmnInfo->stLai.aucLac[0] << 8) | (pstCampPlmnInfo->stLai.aucLac[1]);
    pstSysInfoInd->stPlmnId.ulMcc   = pstCampPlmnInfo->stLai.stPlmnId.ulMcc;
    pstSysInfoInd->stPlmnId.ulMnc   = pstCampPlmnInfo->stLai.stPlmnId.ulMnc;
    pstSysInfoInd->enCurNetWork     = NAS_MML_GetCurrNetRatType();
    pstSysInfoInd->ucSysSubMode     = NAS_MMC_CovertMmlSysSubModeToMsccSysSubMode(pstCampPlmnInfo->enSysSubMode);

    pstSysInfoInd->ucCsAttachAllowFlag = NAS_MML_GetCsAttachAllowFlg();
    pstSysInfoInd->ucPsAttachAllowFlag = NAS_MML_GetPsAttachAllowFlg();

    /* Added by s00246516 for L-C互操作项目, 2014-02-14, Begin */
    pstSysInfoInd->ulArfcn          = NAS_MML_GetCurrCampArfcn();
    pstSysInfoInd->enPrioClass      = NAS_MMC_GetPlmnPrioClass(&(pstCampPlmnInfo->stLai.stPlmnId));
    /* Added by s00246516 for L-C互操作项目, 2014-02-14, End */

    ulForbiddenFlg = NAS_MMC_GetCurrentLaiForbbidenType();

#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        /* 将PLMN ID进行转换 */
        NAS_MML_ConvertNasPlmnToLMMFormat(&stLmmPlmnId, &pstCampPlmnInfo->stLai.stPlmnId);

        /* 禁止网络或者access bar都认为是forbidden plmn */
        if (MMC_LMM_PLMN_ALLOW_REG != Nas_PlmnIdIsForbid(&stLmmPlmnId))
        {
            ulForbiddenFlg = VOS_TRUE;
        }


        pstSysInfoInd->enLmmAccessType  = pstCampPlmnInfo->enLmmAccessType;
    }
    else
#endif
    {
        if (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
        {
            ulForbiddenFlg = MMCMM_FORBIDDEN_PLMN;
        }

        pstSysInfoInd->enLmmAccessType  = NAS_MML_LMM_ACCESS_TYPE_BUTT;
    }

    pstSysInfoInd->ucIsFobbiddenPlmnFlag = (VOS_UINT8)ulForbiddenFlg;

    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-10-16, begin */
    pstSysInfoInd->ucRoamFlag       = VOS_FALSE;

    pstSysInfoInd->ucPsSupportFlg   = NAS_MML_GetPsSupportFLg();

    /* 在Hplmn上CS注册被拒后，非E5时，不在发起注册 ,E5时，HplmnRejlist不记录值 */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(NAS_MML_GetCurrCampPlmnId()))
    {
        if (VOS_FALSE == NAS_MMC_GetHPlmnSpecDomainAccessCapa(NAS_MMC_REG_DOMAIN_PS))
        {
            if (MMCMM_NO_FORBIDDEN == ulForbiddenFlg)
            {
                pstSysInfoInd->ucIsFobbiddenPlmnFlag = MMCMM_FORBIDDEN_PLMN;
            }

            if ( VOS_TRUE == NAS_MML_GetHplmnRegisterCtrlFlg())
            {
                pstSysInfoInd->ucIsFobbiddenPlmnFlag  &= (~MMCMM_FORBIDDEN_PLMN);
            }
        }
    }
    else
    {

        /* 当前驻留网络肯定不在HOME PLMN上,默认漫游 */
        pstSysInfoInd->ucRoamFlag   = VOS_TRUE;

        /* 如果NV开启在EPLMN里面有HPLMN，需要额外设置为不显示漫游 */
        if ((VOS_TRUE == NAS_MML_GetHplmnInEplmnDisplayHomeFlg())
         && (VOS_TRUE == ulIsHplmnInEplmnList)
         && (VOS_TRUE == ulIsCurrCampPlmnInEplmnList))
        {
            pstSysInfoInd->ucRoamFlag   = VOS_FALSE;
        }
    }
    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-10-16, end */

    /* 填充消息头 */
    pstSysInfoInd->MsgHeader.ulMsgName         = ID_MMC_MSCC_SYS_INFO_IND;
    pstSysInfoInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSysInfoInd->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSysInfoInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSysInfoInd->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstSysInfoInd->MsgHeader.ulLength          = sizeof(MMC_MSCC_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstSysInfoInd);
    return;
}


/* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccRegResultInd
 功能描述  : 发送MSCC指定服务域的注册结果消息
 输入参数  : enSrvDomain-----当前注册的服务域
             ucResult   -----当前注册结果
             enRejCause -----当前注册失败的原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年8月15日
   作    者   : l00208543
   修改内容   : 新生成函数
 2.日    期   : 2013年12月13日
   作    者   : W00176964
   修改内容   : Volte PhaseIII项目修改:修改消息和消息结构体名
 3.日    期   : 2014年4月3日
   作    者   : z00161729
   修改内容   : DTS2014040300125:service 被拒和网络detach ind被拒需要上报^rejinfo

*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccRegResultInd(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32            enSrvDomain,
    VOS_UINT8                           ucResult,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enRejCause
)
{
    MMC_MSCC_REG_RESULT_IND_STRU        *pstRegResultInd       = VOS_NULL_PTR;

    pstRegResultInd = (MMC_MSCC_REG_RESULT_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                        sizeof(MMC_MSCC_REG_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstRegResultInd )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccRegResultInd():ERROR:Memory Alloc Error for pstRejInfoInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstRegResultInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_REG_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息*/
    pstRegResultInd->enCnDomainId   = enSrvDomain;
    pstRegResultInd->ucRegRslt      = ucResult;

    if (VOS_FALSE == ucResult)
    {
        pstRegResultInd->enRejCause     = enRejCause;
        pstRegResultInd->ucOriginalRejCause = NAS_MML_GetOriginalRejectCause(pstRegResultInd->enRejCause);
        /* 只上报小于等于256或者等于258、301、302、303的拒绝原因值，其余内部扩展的拒绝原因值不进行上报 */
        if ((pstRegResultInd->enRejCause <= NAS_MML_REG_FAIL_CAUSE_AUTH_REJ)
         || (NAS_MML_REG_FAIL_CAUSE_COMB_REG_CS_FAIL_OTHER_CAUSE == pstRegResultInd->enRejCause)
         || (NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT == pstRegResultInd->enRejCause)
         || (NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL == pstRegResultInd->enRejCause)
         || (NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL == pstRegResultInd->enRejCause))
        {
            pstRegResultInd->ucReportCauseCtrl = VOS_TRUE;
        }
    }

    /* 填充消息头 */
    pstRegResultInd->MsgHeader.ulMsgName         = ID_MMC_MSCC_REG_RESULT_IND;
    pstRegResultInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstRegResultInd->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstRegResultInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstRegResultInd->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstRegResultInd->MsgHeader.ulLength          = sizeof(MMC_MSCC_REG_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstRegResultInd);

    return;
}


/* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccServRejRsltInd
 功能描述  : 收到SERVICE_REJECT_IND消息后发送给mscc
 输入参数  : enCnDomainId - 服务域
             usRejCause   - 拒绝原因值
             enRejType    - 拒绝类型
 输出参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014年4月1日
    作    者   : z00161729
    修改内容   : DTS2014040300125:service 被拒和网络detach ind被拒需要上报^rejinfo
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccServRejRsltInd(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId,
    VOS_UINT16                          usRejCause
)
{
    MMC_MSCC_SERV_REJ_IND_STRU          *pstServReqRsltInd = VOS_NULL_PTR;

    pstServReqRsltInd = (MMC_MSCC_SERV_REJ_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                        sizeof(MMC_MSCC_SERV_REJ_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstServReqRsltInd)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccServRejRsltInd():ERROR:Memory Alloc Error");
        return;
    }
    PS_MEM_SET(((VOS_UINT8*)pstServReqRsltInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_SERV_REJ_IND_STRU) - VOS_MSG_HEAD_LENGTH);


    /* 填充消息头 */
    pstServReqRsltInd->MsgHeader.ulMsgName        = ID_MMC_MSCC_SRV_REJ_IND;
    pstServReqRsltInd->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstServReqRsltInd->MsgHeader.ulSenderPid      = WUEPS_PID_MMC;
    pstServReqRsltInd->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstServReqRsltInd->MsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
    pstServReqRsltInd->MsgHeader.ulLength         = sizeof(MMC_MSCC_SERV_REJ_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填充消息 */
    pstServReqRsltInd->enCnDomainId = enCnDomainId;
    pstServReqRsltInd->usRejCause   = usRejCause;
    pstServReqRsltInd->ucOriginalRejCause = NAS_MML_GetOriginalRejectCause(pstServReqRsltInd->usRejCause);
    PS_SEND_MSG(WUEPS_PID_MMC, pstServReqRsltInd);

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccUsimAuthFailInd
 功能描述  : 发送MSCC网络拒绝原因值消息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 修改历史      :
 1.日    期   : 2013年11月15日
   作    者   : m00217266
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccUsimAuthFailInd(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32            enSrvDomain,
    NAS_MML_SIM_AUTH_FAIL_ENUM_UINT16   enRejCause
                    )
{
    MMC_MSCC_USIM_AUTH_FAIL_IND_STRU    *pstUsimAuthFailInd       = VOS_NULL_PTR;

    pstUsimAuthFailInd = (MMC_MSCC_USIM_AUTH_FAIL_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                        sizeof(MMC_MSCC_USIM_AUTH_FAIL_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstUsimAuthFailInd )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccUsimAuthFailInd():ERROR:Memory Alloc Error for pstUsimAuthFailInds ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstUsimAuthFailInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_USIM_AUTH_FAIL_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息*/
    pstUsimAuthFailInd->enCnDomainId   = enSrvDomain;
    pstUsimAuthFailInd->enRejCause     = enRejCause;

    /* 填充消息头 */
    pstUsimAuthFailInd->MsgHeader.ulMsgName         = ID_MMC_MSCC_USIM_AUTH_FAIL_IND;
    pstUsimAuthFailInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstUsimAuthFailInd->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstUsimAuthFailInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstUsimAuthFailInd->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstUsimAuthFailInd->MsgHeader.ulLength          = sizeof(MMC_MSCC_USIM_AUTH_FAIL_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstUsimAuthFailInd);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccCsServiceConnStatusInd
 功能描述  : 给MSCC发送cs业务信令连接状态消息
 输入参数  : ucCsServiceConnStatusFlag - cs业务信令连接状态标识
 输出参数  : 无
 返 回 值  : 无
 修改历史      :
 1.日    期   : 2014年3月4日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccCsServiceConnStatusInd(
    VOS_UINT8                           ucCsServiceConnStatusFlag
)
{
    MMC_MSCC_CS_SERVICE_CONN_STATUS_IND_STRU    *pstCsServiceConnStatusInd = VOS_NULL_PTR;

    pstCsServiceConnStatusInd = (MMC_MSCC_CS_SERVICE_CONN_STATUS_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                        sizeof(MMC_MSCC_CS_SERVICE_CONN_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstCsServiceConnStatusInd )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccCsServiceConnStatusInd():ERROR:Memory Alloc Error for pstUsimAuthFailInds ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstCsServiceConnStatusInd) + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(MMC_MSCC_CS_SERVICE_CONN_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstCsServiceConnStatusInd->stMsgHeader.ulMsgName         = ID_MMC_MSCC_CS_SERVICE_CONN_STATUS_IND;
    pstCsServiceConnStatusInd->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstCsServiceConnStatusInd->stMsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstCsServiceConnStatusInd->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstCsServiceConnStatusInd->stMsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstCsServiceConnStatusInd->stMsgHeader.ulLength          = sizeof(MMC_MSCC_CS_SERVICE_CONN_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填充消息*/
    pstCsServiceConnStatusInd->ucCsServiceConnStatusFlag   = ucCsServiceConnStatusFlag;

    PS_SEND_MSG(WUEPS_PID_MMC, pstCsServiceConnStatusInd);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccRssiInd
 功能描述  : 发送信号质量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月20日
   作    者   : zhoujun \40661
   修改内容   : 新生成函数
 2.日    期   : 2011年8月11日
   作    者   : W00167002
   修改内容   : 跟周君确认为取RssiNum的值
 3.日    期   : 2012年11月21日
   作    者   : z00161729
   修改内容  : 支持cerssi和nmr
 4.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
 5.日    期   : 2014年6月4日
   作    者   : B00269685
   修改内容   : 增加是否需要上报的判断
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccRssiInd(MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN *punMeasReportType)
{
    MMC_MSCC_RSSI_IND_STRU              *pstRssiInfoInd      = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo     = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstRssiInfoInd = (MMC_MSCC_RSSI_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                         sizeof(MMC_MSCC_RSSI_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstRssiInfoInd )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccRssiInd():ERROR:Memory Alloc Error for pstRssiInfoInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstRssiInfoInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_RSSI_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 按MSCC_MMC_RSSI_INFO_STRU消息封装 */
    pstCampPlmnInfo                             = NAS_MML_GetCurrCampPlmnInfo();
    pstRssiInfoInd->usCellDlFreq = pstCampPlmnInfo->stCampCellInfo.usCellDlFreq;
    pstRssiInfoInd->usCellUlFreq = pstCampPlmnInfo->stCampCellInfo.usCellUlFreq;
    pstRssiInfoInd->sUeRfPower   = pstCampPlmnInfo->stCampCellInfo.sUeRfPower;
    pstRssiInfoInd->ucRssiNum    = pstCampPlmnInfo->stCampCellInfo.ucRssiNum;

    pstRssiInfoInd->enRat = NAS_MML_GetCurrNetRatType();

    for ( i = 0; i < pstRssiInfoInd->ucRssiNum ; i++ )
    {
        pstRssiInfoInd->astRssi[i].ucBer      = pstCampPlmnInfo->stCampCellInfo.astRssiInfo[i].ucChannalQual;
        pstRssiInfoInd->astRssi[i].sRssiValue = pstCampPlmnInfo->stCampCellInfo.astRssiInfo[i].sRssiValue;
        pstRssiInfoInd->astRssi[i].sRscpValue = pstCampPlmnInfo->stCampCellInfo.astRssiInfo[i].sRscpValue;
    }

    PS_MEM_CPY((VOS_UINT8 *)&(pstRssiInfoInd->unMeasReportType),
                   (VOS_UINT8 *)punMeasReportType,
                   sizeof(MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN));

    /* 填充消息头 */
    pstRssiInfoInd->MsgHeader.ulMsgName         = ID_MMC_MSCC_RSSI_IND;
    pstRssiInfoInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstRssiInfoInd->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstRssiInfoInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstRssiInfoInd->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstRssiInfoInd->MsgHeader.ulLength          = sizeof(MMC_MSCC_RSSI_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstRssiInfoInd);
    return;
}





#if(FEATURE_LTE == FEATURE_ON)
/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccMsgLmmCellSignInfoInd
 功能描述  : 给MMA发生L 模的CELL SIGN INFO REPORT IND
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月28日
   作    者   : W00281933
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_SndMsccMsgLmmCellSignInfoInd(
    MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN  *punMeasReportType,
    MSCC_MMC_LMM_CELL_SIGN_INFO_STRU     *pstRssiValueInfo
    )
{
    MMC_MSCC_LMM_CELL_SIGN_INFO_REPORT_IND_STRU      *pstSndMsg            = VOS_NULL_PTR;                               /* 定义原语类型指针                         */

    pstSndMsg = (MMC_MSCC_LMM_CELL_SIGN_INFO_REPORT_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                         sizeof(MMC_MSCC_LMM_CELL_SIGN_INFO_REPORT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstSndMsg )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccMsgLmmCellSignInfoInd():ERROR:Memory Alloc Error for pstRssiInfoInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSndMsg) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_LMM_CELL_SIGN_INFO_REPORT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 按MMC_MSCC_LMM_RSSI_IND_STRU消息封装 */
    pstSndMsg->stLteRssi.sRssi = pstRssiValueInfo->sRssi;
    pstSndMsg->stLteRssi.sRsd  = pstRssiValueInfo->sRsd;
    pstSndMsg->stLteRssi.sRsrp = pstRssiValueInfo->sRsrp;
    pstSndMsg->stLteRssi.sRsrq = pstRssiValueInfo->sRsrq;
    pstSndMsg->stLteRssi.lSINR = pstRssiValueInfo->lSINR;

    pstSndMsg->stLteRssi.stCQI.usRI      = pstRssiValueInfo->stCQI.usRI;
    pstSndMsg->stLteRssi.stCQI.ausCQI[0] = pstRssiValueInfo->stCQI.ausCQI[0];
    pstSndMsg->stLteRssi.stCQI.ausCQI[1] =pstRssiValueInfo->stCQI.ausCQI[1];

    PS_MEM_CPY((VOS_UINT8 *)&(pstSndMsg->unMeasReportType),
                   (VOS_UINT8 *)punMeasReportType,
                   sizeof(MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN));

    /* 填充消息头 */
    pstSndMsg->MsgHeader.ulMsgName         = ID_MMC_MSCC_LMM_CELL_SIGN_INFO_REPORT_IND;
    pstSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstSndMsg->MsgHeader.ulLength          = sizeof(MMC_MSCC_LMM_CELL_SIGN_INFO_REPORT_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstSndMsg);

    return;
}

#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccSysCfgCnf
 功能描述  : MMC给MSCC上报syscfg设置结果
 输入参数  : ulRst - syscfg设置结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月21日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccSysCfgCnf(
    NAS_MSCC_PIF_SYS_CFG_SET_RESULT_ENUM_UINT32                   ulRst
)
{
    MMC_MSCC_SYS_CFG_SET_CNF_STRU        *pstSyscfgSetCnf = VOS_NULL_PTR;

    pstSyscfgSetCnf = (MMC_MSCC_SYS_CFG_SET_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                          sizeof(MMC_MSCC_SYS_CFG_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstSyscfgSetCnf )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccSysCfgCnf():ERROR:Memory Alloc Error for pstSyscfgSetCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSyscfgSetCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_SYS_CFG_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSyscfgSetCnf->enRst                       = ulRst;

    /* 填充消息头 */
    pstSyscfgSetCnf->MsgHeader.ulMsgName         = ID_MMC_MSCC_SYS_CFG_CNF;
    pstSyscfgSetCnf->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSyscfgSetCnf->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSyscfgSetCnf->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSyscfgSetCnf->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstSyscfgSetCnf->MsgHeader.ulLength          = sizeof(MMC_MSCC_SYS_CFG_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstSyscfgSetCnf);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccNetScanCnf
 功能描述  : MMC给MSCC上报NetScan结果
 输入参数  : pstNetScanCnf - 接入层上报的结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月16日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccNetScanCnf(
    MMC_MSCC_NET_SCAN_CNF_STRU             *pstMmcMsccNetScanCnfMsg
)
{
    MMC_MSCC_NET_SCAN_CNF_STRU          *pstNetScanCnf       = VOS_NULL_PTR;

    pstNetScanCnf = (MMC_MSCC_NET_SCAN_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                          sizeof(MMC_MSCC_NET_SCAN_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstNetScanCnf )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccNetScanCnf():ERROR:Memory Alloc Error");
        return;
    }

    PS_MEM_SET( ((VOS_UINT8*)pstNetScanCnf) + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(MMC_MSCC_NET_SCAN_CNF_STRU) - VOS_MSG_HEAD_LENGTH );

    /* 填充消息头 */
    pstNetScanCnf->MsgHeader.ulMsgName         = ID_MMC_MSCC_NET_SCAN_CNF;
    pstNetScanCnf->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstNetScanCnf->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstNetScanCnf->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstNetScanCnf->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstNetScanCnf->MsgHeader.ulLength          = sizeof(MMC_MSCC_NET_SCAN_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstNetScanCnf->enResult                    = pstMmcMsccNetScanCnfMsg->enResult;
    pstNetScanCnf->enCause                     = pstMmcMsccNetScanCnfMsg->enCause;
    pstNetScanCnf->ucFreqNum                   = pstMmcMsccNetScanCnfMsg->ucFreqNum;

    PS_MEM_CPY( pstNetScanCnf->astNetScanInfo,
                pstMmcMsccNetScanCnfMsg->astNetScanInfo,
                sizeof(pstNetScanCnf->astNetScanInfo) );

    PS_SEND_MSG(WUEPS_PID_MMC, pstNetScanCnf);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccAbortNetScanCnf
 功能描述  : MMC给MSCC上报停止NetScan结果
 输入参数  : pstSndMsccAbortNetScanCnfMsg - 接入层上报的结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月16日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccAbortNetScanCnf(
    MMC_MSCC_ABORT_NET_SCAN_CNF_STRU    *pstSndMsccAbortNetScanCnfMsg
)
{
    MMC_MSCC_ABORT_NET_SCAN_CNF_STRU    *pstNetScanStopCnf   = VOS_NULL_PTR;

    pstNetScanStopCnf = (MMC_MSCC_ABORT_NET_SCAN_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                          sizeof(MMC_MSCC_ABORT_NET_SCAN_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstNetScanStopCnf )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccAbortNetScanCnf():ERROR:Memory Alloc Error");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstNetScanStopCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_ABORT_NET_SCAN_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstNetScanStopCnf->MsgHeader.ulMsgName                  = ID_MMC_MSCC_ABORT_NET_SCAN_CNF;
    pstNetScanStopCnf->MsgHeader.ulSenderCpuId              = VOS_LOCAL_CPUID;
    pstNetScanStopCnf->MsgHeader.ulSenderPid                = WUEPS_PID_MMC;
    pstNetScanStopCnf->MsgHeader.ulReceiverCpuId            = VOS_LOCAL_CPUID;
    pstNetScanStopCnf->MsgHeader.ulReceiverPid              = UEPS_PID_MSCC;
    pstNetScanStopCnf->MsgHeader.ulLength                   = sizeof(MMC_MSCC_ABORT_NET_SCAN_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstNetScanStopCnf->ucFreqNum                            = pstSndMsccAbortNetScanCnfMsg->ucFreqNum;

    PS_MEM_CPY( pstNetScanStopCnf->astNetScanInfo,
                pstSndMsccAbortNetScanCnfMsg->astNetScanInfo,
                sizeof(pstNetScanStopCnf->astNetScanInfo) );


    PS_SEND_MSG(WUEPS_PID_MMC, pstNetScanStopCnf);


    return;
}



/*****************************************************************************
 函 数 名  : NAS_Mmc_SndMsccPowerOffCnf
 功能描述  : 向MSCC发送关机回复
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月19日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_VOID NAS_Mmc_SndMsccPowerOffCnf(VOS_VOID)
{
    MMC_MSCC_POWER_OFF_CNF_STRU         *pstPowerOffCnf = VOS_NULL_PTR;

    pstPowerOffCnf = (MMC_MSCC_POWER_OFF_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                         sizeof(MMC_MSCC_POWER_OFF_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstPowerOffCnf )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_Mmc_SndMsccPowerOffCnf():ERROR:Memory Alloc Error for pstPowerOffCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstPowerOffCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_POWER_OFF_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstPowerOffCnf->MsgHeader.ulMsgName         = ID_MMC_MSCC_POWER_OFF_CNF;

    /* 填充消息头 */
    pstPowerOffCnf->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPowerOffCnf->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstPowerOffCnf->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPowerOffCnf->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstPowerOffCnf->MsgHeader.ulLength          = sizeof(MMC_MSCC_POWER_OFF_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstPowerOffCnf);

    NAS_TRACE_HIGH("Send Msg!");

    return;
}

/*****************************************************************************
 函 数 名  : NAS_Mmc_SndMsccStartCnf
 功能描述  : 向MSCC发送开机回复
 输入参数  : ulResult - 开机结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月19日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_VOID NAS_Mmc_SndMsccStartCnf(VOS_UINT32  ulResult)
{
    MMC_MSCC_START_CNF_STRU             *pstStartCnf = VOS_NULL_PTR;

    pstStartCnf = (MMC_MSCC_START_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                      sizeof(MMC_MSCC_START_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstStartCnf )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_Mmc_SndMsccStartCnf():ERROR:Memory Alloc Error for pstStartCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstStartCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_START_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstStartCnf->ulResult                    = ulResult;

    /* 填充消息头 */
    pstStartCnf->MsgHeader.ulMsgName         = ID_MMC_MSCC_START_CNF;
    pstStartCnf->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstStartCnf->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstStartCnf->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstStartCnf->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstStartCnf->MsgHeader.ulLength          = sizeof(MMC_MSCC_START_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstStartCnf);

    NAS_TRACE_HIGH("Send Msg!");

    return;
}

/*****************************************************************************
 函 数 名  : NAS_Mmc_SndMsccPlmnListAbortCnf
 功能描述  : 向MSCC发送ID_MMC_MSCC_PLMN_LIST_ABORT_CNF消息
 输入参数  : usSearchPlmnNum 搜索列表中保存的PLMN ID个数
             pstListInfo     搜索列表信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年09月21日
   作    者   : W00166186
   修改内容   : V7R1 PHASE II
 3.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核

  4.日    期   : 2013年5月30日
    作    者   : z00234330
    修改内容   : DTS2013052800822,list搜网输入为空指针时，接收PID为非法,导致-
                 MM_FID复位
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccPlmnListAbortCnf(
    MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU  *pstSndMsccMsg
)
{
    MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU  *pstPlmnListAbortCnf = VOS_NULL_PTR;
    VOS_UINT32                           i;

    pstPlmnListAbortCnf = (MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                              sizeof(MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pstPlmnListAbortCnf )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccPlmnListAbortCnf():ERROR:Memory Alloc Error for pstPlmnListAbortCnf ");
        return;
    }

    /* 填充消息头 */
    PS_MEM_SET(((VOS_UINT8*)pstPlmnListAbortCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstPlmnListAbortCnf->MsgHeader.ulMsgName         = ID_MMC_MSCC_PLMN_LIST_ABORT_CNF;
    pstPlmnListAbortCnf->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPlmnListAbortCnf->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstPlmnListAbortCnf->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPlmnListAbortCnf->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstPlmnListAbortCnf->MsgHeader.ulLength          = sizeof(MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 若传进来的消息为空指针则表示列表为空 */
    if ( VOS_NULL_PTR == pstSndMsccMsg)
    {
        pstPlmnListAbortCnf->ulCnt = 0;

        PS_SEND_MSG(WUEPS_PID_MMC, pstPlmnListAbortCnf);

        return;
    }


    /* 转换GU格式的消息为MSCC格式的 */
    pstPlmnListAbortCnf->ulCnt  = pstSndMsccMsg->ulCnt;

    for (i =0; i<pstSndMsccMsg->ulCnt; i++)
    {
        pstPlmnListAbortCnf->aPlmnList[i].ulMcc = pstSndMsccMsg->aPlmnList[i].ulMcc;
        pstPlmnListAbortCnf->aPlmnList[i].ulMnc = pstSndMsccMsg->aPlmnList[i].ulMnc;

        pstPlmnListAbortCnf->aucPlmnStatus[i]   = pstSndMsccMsg->aucPlmnStatus[i];
        pstPlmnListAbortCnf->aucRaMode[i]       = pstSndMsccMsg->aucRaMode[i];
    }


    PS_SEND_MSG(WUEPS_PID_MMC, pstPlmnListAbortCnf);
}

/*****************************************************************************
 函 数 名  : NAS_Mmc_SndMsccPlmnListInd
 功能描述  : 向MSCC发送ID_MMC_MSCC_PLMN_LIST_CNF消息
 输入参数  : usSearchPlmnNum 搜索列表中保存的PLMN ID个数
             pstListInfo     搜索列表信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccPlmnListInd(
    MMC_MSCC_PLMN_LIST_CNF_STRU         *pstSndMsccMsg
)
{
    MMC_MSCC_PLMN_LIST_CNF_STRU          *pstPlmnListCnf = VOS_NULL_PTR;
    VOS_UINT32                           i;

    pstPlmnListCnf = (MMC_MSCC_PLMN_LIST_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                         sizeof(MMC_MSCC_PLMN_LIST_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstPlmnListCnf )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccDetachInd():ERROR:Memory Alloc Error for pstPlmnListCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstPlmnListCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_PLMN_LIST_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 转换GU格式的消息为MSCC格式的 */
    pstPlmnListCnf->ulCnt  = pstSndMsccMsg->ulCnt;

    for (i =0; i<pstSndMsccMsg->ulCnt; i++)
    {
        pstPlmnListCnf->aPlmnList[i].ulMcc = pstSndMsccMsg->aPlmnList[i].ulMcc;
        pstPlmnListCnf->aPlmnList[i].ulMnc = pstSndMsccMsg->aPlmnList[i].ulMnc;

        pstPlmnListCnf->aucPlmnStatus[i]   = pstSndMsccMsg->aucPlmnStatus[i];
        pstPlmnListCnf->aucRaMode[i]       = pstSndMsccMsg->aucRaMode[i];
    }

    /* 填充消息头 */
    pstPlmnListCnf->MsgHeader.ulMsgName         = ID_MMC_MSCC_PLMN_LIST_CNF;
    pstPlmnListCnf->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPlmnListCnf->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstPlmnListCnf->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPlmnListCnf->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstPlmnListCnf->MsgHeader.ulLength          = sizeof(MMC_MSCC_PLMN_LIST_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstPlmnListCnf);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_Mmc_SndMsccPlmnListRej
 功能描述  : 向MSCC发送TAFMMC_PLMN_LIST_Rej消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_VOID NAS_Mmc_SndMsccPlmnListRej(VOS_VOID)
{
    MMC_MSCC_PLMN_LIST_REJ_STRU        *pstPlmnListRej = VOS_NULL_PTR;

    pstPlmnListRej = (MMC_MSCC_PLMN_LIST_REJ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                         sizeof(MMC_MSCC_PLMN_LIST_REJ_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstPlmnListRej )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_Mmc_SndMsccPlmnListRej():ERROR:Memory Alloc Error for pstPlmnListRej ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstPlmnListRej) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_PLMN_LIST_REJ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstPlmnListRej->MsgHeader.ulMsgName         = ID_MMC_MSCC_PLMN_LIST_REJ;
    pstPlmnListRej->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPlmnListRej->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstPlmnListRej->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPlmnListRej->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstPlmnListRej->MsgHeader.ulLength          = sizeof(MMC_MSCC_PLMN_LIST_REJ_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstPlmnListRej);
    return;
}

/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */

/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */

/*****************************************************************************
 函 数 名  : NAS_MMC_GetOperPlmnInfoForMscc
 功能描述  : 提供Oper Plmn信息给MSCC查询使用
 输入参数  : 无
 输出参数  : pstRptMsccOperList:给MSCC查询使用的Oper Plmn信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月28日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2013年4月7日
   作    者   : z00161729
   修改内容   : 主动上报AT命令控制下移至C核及mma和mmc接口调整
 3.日    期    : 2013年11月26日
   作    者    : s00190137
   修改内容    : 将最大支持设置的OPLMN扩展到256个
*****************************************************************************/
VOS_VOID  NAS_MMC_GetOperPlmnInfoForMscc(
    MMC_TAF_PLMN_LIST_INFO_ST          *pstRptMsccOperList
)
{
    NAS_MML_SIM_OPERPLMN_INFO_STRU     *pstOperPlmnList = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstOperPlmnList                     = NAS_MML_GetSimOperPlmnList();

    pstRptMsccOperList->usCurPlmnNum     = pstOperPlmnList->usOperPlmnNum;

    if (pstRptMsccOperList->usCurPlmnNum > TAF_USER_MAX_PLMN_NUM)
    {
        pstRptMsccOperList->usCurPlmnNum = TAF_USER_MAX_PLMN_NUM;
    }

    for(i = 0; i < pstRptMsccOperList->usCurPlmnNum; i++)
    {
        /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
        PS_MEM_CPY((&(pstRptMsccOperList->astPlmnInfo[i].stPlmn)) , &(pstOperPlmnList->astOperPlmnInfo[i].stPlmnId), sizeof(NAS_MML_PLMN_ID_STRU));
        /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */

        pstRptMsccOperList->astPlmnInfo[i].usRaMode  = pstOperPlmnList->astOperPlmnInfo[i].usSimRat;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetUserPlmnInfoForMscc
 功能描述  : 提供User Plmn信息给MSCC查询使用
 输入参数  : 无
 输出参数  : pstRptMsccUserList:给MSCC查询使用的User Plmn信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月28日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2013年4月7日
   作    者   : z00161729
   修改内容   : 主动上报AT命令控制下移至C核及mma和mmc接口调整
 3.日    期    : 2013年11月26日
   作    者    : s00190137
   修改内容    : 将最大支持设置的OPLMN扩展到256个
*****************************************************************************/
VOS_VOID  NAS_MMC_GetUserPlmnInfoForMscc(
    MMC_TAF_PLMN_LIST_INFO_ST          *pstRptMsccUserList
)
{
    NAS_MML_SIM_USERPLMN_INFO_STRU     *pstUserPlmnList = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstUserPlmnList                     = NAS_MML_GetSimUserPlmnList();

    pstRptMsccUserList->usCurPlmnNum     = (VOS_UINT16)pstUserPlmnList->ucUserPlmnNum;

    if (pstRptMsccUserList->usCurPlmnNum > NAS_MML_MAX_USERPLMN_NUM)
    {
        pstRptMsccUserList->usCurPlmnNum = NAS_MML_MAX_USERPLMN_NUM;
    }

    for(i = 0; i < pstRptMsccUserList->usCurPlmnNum; i++)
    {
        /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
        PS_MEM_CPY(&(pstRptMsccUserList->astPlmnInfo[i].stPlmn) , &(pstUserPlmnList->astUserPlmnInfo[i].stPlmnId), sizeof(MSCC_MMC_PLMN_ID_STRU));
        /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */

        pstRptMsccUserList->astPlmnInfo[i].usRaMode  = pstUserPlmnList->astUserPlmnInfo[i].usSimRat;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetHPlmnInfoForMscc
 功能描述  : 提供HPlmn信息给MSCC查询使用
 输入参数  : 无
 输出参数  : pstRptMsccHplmnList:给MSCC查询使用的HPlmn信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月28日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2012年8月10日
   作    者   : L00171473
   修改内容   : DTS2012082204471, TQE清理
 3.日    期   : 2013年4月7日
   作    者   : z00161729
   修改内容   : 主动上报AT命令控制下移至C核及mma和mmc接口调整
 4.日    期    : 2013年11月26日
   作    者    : s00190137
   修改内容    : 将最大支持设置的OPLMN扩展到256个
*****************************************************************************/
VOS_VOID  NAS_MMC_GetHPlmnInfoForMscc(
    MMC_TAF_PLMN_LIST_INFO_ST           *pstRptMsccHplmnList
)
{
    NAS_MML_SIM_HPLMN_WITH_RAT_INFO_STRU *pstHplmnWithRat = VOS_NULL_PTR;
    VOS_UINT32                            i;

    pstHplmnWithRat                     = NAS_MML_GetSimHplmnWithRatList();

    pstRptMsccHplmnList->usCurPlmnNum    = (VOS_UINT16)pstHplmnWithRat->ucHPlmnWithRatNum;

    if (pstRptMsccHplmnList->usCurPlmnNum > NAS_MML_MAX_HPLMN_WITH_RAT_NUM)
    {
        pstRptMsccHplmnList->usCurPlmnNum = NAS_MML_MAX_HPLMN_WITH_RAT_NUM;
    }

    for(i = 0; i < pstRptMsccHplmnList->usCurPlmnNum; i++)
    {
        /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
        PS_MEM_CPY(&(pstRptMsccHplmnList->astPlmnInfo[i].stPlmn) , &(pstHplmnWithRat->astHPlmnWithRatInfo[i].stPlmnId), sizeof(MSCC_MMC_PLMN_ID_STRU));
        /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */

        pstRptMsccHplmnList->astPlmnInfo[i].usRaMode = pstHplmnWithRat->astHPlmnWithRatInfo[i].usSimRat;
    }

}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetSelPlmnInfoForMscc
 功能描述  : 提供SelPlmn信息给MSCC查询使用
 输入参数  : 无
 输出参数  : pstRptMsccSelPlmnList:给MSCC查询使用的SelPlmn信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月28日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2011年11月30日
   作    者   : w00176964
   修改内容   : 联合注册BBIT调整
 3.日    期   : 2013年4月7日
   作    者   : z00161729
   修改内容   : 主动上报AT命令控制下移至C核及mma和mmc接口调整
 4.日    期   : 2013年8月29日
   作    者   : w00242748
   修改内容   : KLOC告警清理
 5.日    期    : 2013年11月26日
   作    者    : s00190137
   修改内容    : 将最大支持设置的OPLMN扩展到256个
*****************************************************************************/
VOS_VOID  NAS_MMC_GetSelPlmnInfoForMscc(
    MMC_TAF_PLMN_LIST_INFO_ST          *pstRptMsccSelPlmnList
)
{
    NAS_MML_SIM_SELPLMN_INFO_STRU      *pstSelPlmnList = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstSelPlmnList                      = NAS_MML_GetSimSelPlmnList();

    pstRptMsccSelPlmnList->usCurPlmnNum  = (VOS_UINT16)pstSelPlmnList->ucSelPlmnNum;

    if (pstRptMsccSelPlmnList->usCurPlmnNum > NAS_MML_MAX_SELPLMN_NUM)
    {
        pstRptMsccSelPlmnList->usCurPlmnNum = NAS_MML_MAX_SELPLMN_NUM;
    }

    pstRptMsccSelPlmnList->usCurPlmnNum = NAS_COMM_MIN(pstRptMsccSelPlmnList->usCurPlmnNum, NAS_MML_MAX_SELPLMN_NUM);

    for (i = 0; i <  pstRptMsccSelPlmnList->usCurPlmnNum; i++)
    {
        /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
        PS_MEM_CPY(&(pstRptMsccSelPlmnList->astPlmnInfo[i].stPlmn), &(pstSelPlmnList->astPlmnId[i]), sizeof(MSCC_MMC_PLMN_ID_STRU));
        /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */

#if (FEATURE_ON == FEATURE_LTE)
        pstRptMsccSelPlmnList->astPlmnInfo[i].usRaMode   = NAS_MML_SIM_UE_SUPPORT_RAT_SUPPORT_LTE;
#else
        pstRptMsccSelPlmnList->astPlmnInfo[i].usRaMode   = NAS_MML_SIM_UE_SUPPORT_RAT;
#endif
    }

}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetServiceStatusForMscc
 功能描述  : 将MMC当前的服务状态转换为MSCC的服务状态
 输入参数  : ucSimStatus:当前该域的卡状态
             enServiceStatus:当前该域的服务状态
 输出参数  : 无
 返 回 值  : 上报MSCC当前服务状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月29日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2012年4月27日
   作    者   : l00130025
   修改内容   : DTS2012032303156:MMC的服务状态与上报的服务状态需要转换
 3.日    期   : 2015年7月24日
   作    者   : w00167002
   修改内容   : DTS2015072107308:澳电测试:开机pin码，在无覆盖区域显示可以进行紧急呼业务，
                需要显示无服务给用户。
*****************************************************************************/
NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8  NAS_MMC_GetServiceStatusForMscc(
    NAS_MM_COM_SERVICE_DOMAIN_ENUM_UINT8 enSrvDomain
)
{
    NAS_MMC_SERVICE_ENUM_UINT8          enServiceStatus;

    if (NAS_MSCC_PIF_SRVDOMAIN_CS == enSrvDomain)
    {
        enServiceStatus  = NAS_MMC_GetCsServiceStatus();
    }
    else
    {
        enServiceStatus  = NAS_MMC_GetPsServiceStatus();
    }


    if ( NAS_MMC_NORMAL_SERVICE == enServiceStatus )
    {
        return MM_COM_SRVST_NORMAL_SERVICE;
    }

    if ( NAS_MMC_LIMITED_SERVICE_REGION == enServiceStatus )
    {
        return MM_COM_SRVST_LIMITED_SERVICE_REGION;
    }


    if ( NAS_MMC_LIMITED_SERVICE == enServiceStatus )
    {
        return MM_COM_SRVST_LIMITED_SERVICE;
    }

    return MM_COM_SRVST_NO_SERVICE;
}

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
/*****************************************************************************
 函 数 名  : NAS_MMC_SndCbaMsgNetModInd
 功能描述  : 当前模式发生变化时,MSCC需要通知TAF模块当前接
             入模式以便CBS模块发送激活列表到接入层
 输入参数  : ucNetWorkMode:当前网络模式,0:GSM,1:WCDMA
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月15日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年3月2日
    作    者   : l00171473
    修改内容   : for V7R1C50 CSFB&PPAC&ETWS&ISR
  3.日    期   : 2012年11月29日
    作    者   : w00176964
    修改内容   : DTS2012042804167:接入技术为LTE时暂时在回放工程中不发该消息
  4.日    期   : 2013年4月7日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mmc接口调整
*****************************************************************************/
VOS_VOID NAS_MMC_SndCbaMsgNetModInd(
    VOS_UINT8                           ucNetWorkMode
)
{
    TAFMMC_CBS_CURR_NET_MODE_IND_STRU  *pstMsg;


    if ( (ucNetWorkMode != NAS_MML_NET_RAT_TYPE_GSM)
      && (ucNetWorkMode != NAS_MML_NET_RAT_TYPE_WCDMA)
      && (ucNetWorkMode != NAS_MML_NET_RAT_TYPE_LTE) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndCbaMsgNetModInd: NetMode ERROR");
        return;
    }


    pstMsg = (TAFMMC_CBS_CURR_NET_MODE_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                           sizeof(TAFMMC_CBS_CURR_NET_MODE_IND_STRU));


    if( VOS_NULL_PTR == pstMsg )
    {
        PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_MMC_SndCbaMsgNetModInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET(pstMsg,0,sizeof(TAFMMC_CBS_CURR_NET_MODE_IND_STRU));

    pstMsg->MsgHeader.ulLength          = sizeof(TAFMMC_CBS_CURR_NET_MODE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_TAF;

    /* 填写消息类别  */
    pstMsg->MsgHeader.ulMsgName         = TAFMMC_CBS_CURR_NET_MODE_IND;


    if ( NAS_MML_NET_RAT_TYPE_WCDMA == ucNetWorkMode)
    {
        pstMsg->ucCurNetWork            = MN_NET_MODE_WCDMA;
    }
    else if( NAS_MML_NET_RAT_TYPE_GSM == ucNetWorkMode)
    {
        pstMsg->ucCurNetWork            = MN_NET_MODE_GSM;
    }
    else if (NAS_MML_NET_RAT_TYPE_LTE == ucNetWorkMode)
    {
        pstMsg->ucCurNetWork            = MN_NET_MODE_LTE;
    }
    else
    {

    }

   PS_SEND_MSG( WUEPS_PID_MMC, pstMsg);

}



/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccMsgNoNetWorkInd
 功能描述  : 通知CBS模块当前网络模式为非法
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : zhoujun \ 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_SndMsccMsgNoNetWorkInd( VOS_VOID )
{
    TAFMMC_CBS_NO_NETWORK_IND_STRU      *pstSndMsg;                               /* 定义原语类型指针                         */

    /*申请消息  */
    pstSndMsg = (TAFMMC_CBS_NO_NETWORK_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMC,
                                             sizeof(TAFMMC_CBS_NO_NETWORK_IND_STRU));
    if( VOS_NULL_PTR == pstSndMsg )
    {
        PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_MMC_SndMsccMsgNoNetWorkInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    pstSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_TAF;

    pstSndMsg->MsgHeader.ulMsgName   = TAFMMC_CBS_NO_NETWORK_IND;

    PS_SEND_MSG(WUEPS_PID_MMC, pstSndMsg);

    return;
}

#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccSpecPlmnSearchAbortCnf
 功能描述  : 向MSCC发送MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_CNF消息
 输入参数  : pstSndMsccMsg - MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_CNF消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月28日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccSpecPlmnSearchAbortCnf(VOS_VOID)
{
    /* 按MMC_MSCC_SPEC_PLMN_SEARCH_ABORT_CNF_STRU封装消息并发送 */
    MMC_MSCC_SPEC_PLMN_SEARCH_ABORT_CNF_STRU                *pstSpecPlmnSrchAbortCnf = VOS_NULL_PTR;

    pstSpecPlmnSrchAbortCnf = (MMC_MSCC_SPEC_PLMN_SEARCH_ABORT_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                  sizeof(MMC_MSCC_SPEC_PLMN_SEARCH_ABORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pstSpecPlmnSrchAbortCnf )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccSpecPlmnSearchAbortCnf():ERROR:Memory Alloc Error for pstSpecPlmnSrchAbortCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSpecPlmnSrchAbortCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_SPEC_PLMN_SEARCH_ABORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstSpecPlmnSrchAbortCnf->MsgHeader.ulMsgName            = ID_MMC_MSCC_SPEC_PLMN_SEARCH_ABORT_CNF;
    pstSpecPlmnSrchAbortCnf->MsgHeader.ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstSpecPlmnSrchAbortCnf->MsgHeader.ulSenderPid          = WUEPS_PID_MMC;
    pstSpecPlmnSrchAbortCnf->MsgHeader.ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstSpecPlmnSrchAbortCnf->MsgHeader.ulReceiverPid        = UEPS_PID_MSCC;
    pstSpecPlmnSrchAbortCnf->MsgHeader.ulLength             = sizeof(MMC_MSCC_SPEC_PLMN_SEARCH_ABORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstSpecPlmnSrchAbortCnf);

}
/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccWCipherInfoInd
 功能描述  : 将AS上报的Cipher信息上报给MSCC
             (D_MMC_CIPHER_INFO_IND)
 输入参数  : VOS_VOID   pMsgData        - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月18日
    作    者   : l00198894
    修改内容   : 新生成函数
  2.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccWCipherInfoInd(
    RRMM_CIPHER_INFO_IND_STRU          *pstCipherInfoInd
)
{

    MMC_MSCC_UMTS_CIPHER_INFO_IND_STRU  *pstUmtsCipherInfoInd = VOS_NULL_PTR;

    pstUmtsCipherInfoInd = (MMC_MSCC_UMTS_CIPHER_INFO_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                               sizeof(MMC_MSCC_UMTS_CIPHER_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pstUmtsCipherInfoInd )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccDetachInd():ERROR:Memory Alloc Error for pstAppMsg ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstUmtsCipherInfoInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_UMTS_CIPHER_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 按MMC_MSCC_UMTS_CIPHER_INFO_IND_STRU封装消息并发送 */
    pstUmtsCipherInfoInd->ucCipherAlgorForCSDomain    = pstCipherInfoInd->enCipherAlgorForCSDomain;
    pstUmtsCipherInfoInd->ucCipherAlgorForPSDomain    = pstCipherInfoInd->enCipherAlgorForPSDomain;

    /* 填充消息头 */
    pstUmtsCipherInfoInd->MsgHeader.ulMsgName         = ID_MMC_MSCC_UMTS_CIPHER_INFO_IND;
    pstUmtsCipherInfoInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstUmtsCipherInfoInd->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstUmtsCipherInfoInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstUmtsCipherInfoInd->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstUmtsCipherInfoInd->MsgHeader.ulLength          = sizeof(MMC_MSCC_UMTS_CIPHER_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstUmtsCipherInfoInd);
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccGCipherInfoInd
 功能描述  : 将GMM上报的Cipher信息上报给MSCC
             (D_MMC_GPRS_CIPHER_INFO_IND)
 输入参数  : VOS_VOID   pMsgData        - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月18日
    作    者   : l00198894
    修改内容   : 新生成函数
  2.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccGCipherInfoInd(
    MMC_GMM_CIPHER_INFO_IND_STRU       *pstCipherInfoInd
)
{

    MMC_MSCC_GPRS_CIPHER_INFO_IND_STRU  *pstGprsCipherInfoInd = VOS_NULL_PTR;

    pstGprsCipherInfoInd = (MMC_MSCC_GPRS_CIPHER_INFO_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                               sizeof(MMC_MSCC_GPRS_CIPHER_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pstGprsCipherInfoInd )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccDetachInd():ERROR:Memory Alloc Error for pstAppMsg ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstGprsCipherInfoInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_GPRS_CIPHER_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 按MMC_MSCC_GPRS_CIPHER_INFO_IND_STRU封装消息并发送 */
    pstGprsCipherInfoInd->ucGprsCipher                      = pstCipherInfoInd->ucGprsCipher;
    pstGprsCipherInfoInd->ucGprsCipherAlg                   = pstCipherInfoInd->ucGprsCipherAlg;

    /* 填充消息头 */
    pstGprsCipherInfoInd->MsgHeader.ulMsgName               = ID_MMC_MSCC_GPRS_CIPHER_INFO_IND;
    pstGprsCipherInfoInd->MsgHeader.ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstGprsCipherInfoInd->MsgHeader.ulSenderPid             = WUEPS_PID_MMC;
    pstGprsCipherInfoInd->MsgHeader.ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstGprsCipherInfoInd->MsgHeader.ulReceiverPid           = UEPS_PID_MSCC;
    pstGprsCipherInfoInd->MsgHeader.ulLength                = sizeof(MMC_MSCC_GPRS_CIPHER_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstGprsCipherInfoInd);
    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccUserSpecPlmnSearchRej
 功能描述  : 向MSCC发送用户指定搜拒绝的结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年10月09日
   作    者   : z40661
   修改内容   : 新生成函数
2. 日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccUserSpecPlmnSearchRej( VOS_VOID )
{
    MMC_MSCC_PLMN_SPECIAL_SEL_REJ_STRU   *pstUserSelRej = VOS_NULL_PTR;

    pstUserSelRej = (MMC_MSCC_PLMN_SPECIAL_SEL_REJ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                        sizeof(MMC_MSCC_PLMN_SPECIAL_SEL_REJ_STRU) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pstUserSelRej )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccUserSpecPlmnSearchRej():ERROR:Memory Alloc Error for pstUserSelRej ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstUserSelRej) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_PLMN_SPECIAL_SEL_REJ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstUserSelRej->MsgHeader.ulMsgName                      = ID_MMC_MSCC_PLMN_SPECIAL_SEL_REJ;
    pstUserSelRej->MsgHeader.ulSenderCpuId                  = VOS_LOCAL_CPUID;
    pstUserSelRej->MsgHeader.ulSenderPid                    = WUEPS_PID_MMC;
    pstUserSelRej->MsgHeader.ulReceiverCpuId                = VOS_LOCAL_CPUID;
    pstUserSelRej->MsgHeader.ulReceiverPid                  = UEPS_PID_MSCC;
    pstUserSelRej->MsgHeader.ulLength                       = sizeof(MMC_MSCC_PLMN_SPECIAL_SEL_REJ_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstUserSelRej);
    return;
}




/* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccAcInfoChangeInd
 功能描述  : 向MSCC发送小区接入信息变化指示
 输入参数  : VOS_UINT32                          ulCnDomainId,
             NAS_MML_ACCESS_RESTRICTION_STRU    *pstPsAcInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccAcInfoChangeInd(
    VOS_UINT32                          ulCnDomainId,
    NAS_MML_ACCESS_RESTRICTION_STRU    *pstAcInfo
)
{
    MMC_MSCC_AC_INFO_CHANGE_IND_STRU    *pstAcInfoChgInd = VOS_NULL_PTR;

    pstAcInfoChgInd = (MMC_MSCC_AC_INFO_CHANGE_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                         sizeof(MMC_MSCC_AC_INFO_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstAcInfoChgInd )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccAcInfoChangeInd():ERROR:Memory Alloc Error for pstAcInfoChgInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstAcInfoChgInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_AC_INFO_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 按MMC_MSCC_AC_INFO_CHANGE_IND_STRU封装消息并发送 */
    pstAcInfoChgInd->enCnDomainId                           = (VOS_UINT8)ulCnDomainId;
    pstAcInfoChgInd->ucRestrictPagingRsp                    = pstAcInfo->ucRestrictPagingRsp;
    pstAcInfoChgInd->ucRestrictRegister                     = pstAcInfo->ucRestrictRegister;

    if ((VOS_TRUE == pstAcInfo->ucRestrictEmergencyService)
     && (VOS_TRUE == pstAcInfo->ucRestrictNormalService))
    {
        pstAcInfoChgInd->enCellAcType = NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_ALL_SERVICE;
    }
    else if (VOS_TRUE == pstAcInfo->ucRestrictNormalService)
    {
        pstAcInfoChgInd->enCellAcType = NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_NORMAL_SERVICE;
    }
    else if (VOS_TRUE == pstAcInfo->ucRestrictEmergencyService)
    {
        pstAcInfoChgInd->enCellAcType = NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_EMERGENCY_SERVICE;
    }
    else
    {
        pstAcInfoChgInd->enCellAcType = NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_NONE;
    }

    /* 填充消息头 */
    pstAcInfoChgInd->MsgHeader.ulMsgName         = ID_MMC_MSCC_AC_INFO_CHANGE_IND;
    pstAcInfoChgInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstAcInfoChgInd->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstAcInfoChgInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstAcInfoChgInd->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstAcInfoChgInd->MsgHeader.ulLength          = sizeof(MMC_MSCC_AC_INFO_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstAcInfoChgInd);

    return;
}

/* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */



/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccEplmnInfoInd
 功能描述  : MMC给MSCC上报等效plmn信息
 输入参数  : pstEplmnInfo - 等效plmn信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月24日
    作    者   : z00161729
    修改内容   : SVLTE支持NCELL搜网

*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccEplmnInfoInd(
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnInfo
)
{
    MMC_MSCC_EPLMN_INFO_IND_STRU        *pstEplmnInfoInd = VOS_NULL_PTR;

    pstEplmnInfoInd = (MMC_MSCC_EPLMN_INFO_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                          sizeof(MMC_MSCC_EPLMN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstEplmnInfoInd )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccEplmnInfoInd():ERROR:Memory Alloc Error");
        return;
    }

    PS_MEM_SET( ((VOS_UINT8*)pstEplmnInfoInd) + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(MMC_MSCC_EPLMN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH );

    /* 填充消息头 */
    pstEplmnInfoInd->stMsgHeader.ulMsgName         = ID_MMC_MSCC_EPLMN_INFO_IND;
    pstEplmnInfoInd->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstEplmnInfoInd->stMsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstEplmnInfoInd->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstEplmnInfoInd->stMsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstEplmnInfoInd->stMsgHeader.ulLength          = sizeof(MMC_MSCC_EPLMN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstEplmnInfoInd->stEplmnInfo.ucEquPlmnNum    = pstEplmnInfo->ucEquPlmnNum;
    PS_MEM_CPY(pstEplmnInfoInd->stEplmnInfo.astEquPlmnAddr, pstEplmnInfo->astEquPlmnAddr,
               sizeof(pstEplmnInfoInd->stEplmnInfo.astEquPlmnAddr));

    PS_SEND_MSG(WUEPS_PID_MMC, pstEplmnInfoInd);
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccEOPlmnSetCnf
 功能描述  : 向MSCC发送EOPLMN设置结果
 输入参数  : VOS_UINT32                          ulRst,

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月15日
    作    者   : x65241
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccEOPlmnSetCnf(
    VOS_UINT32                     ulRst
)
{
    MMC_MSCC_EOPLMN_SET_CNF_STRU        *pstSPlmnSetCnf = VOS_NULL_PTR;

    pstSPlmnSetCnf = (MMC_MSCC_EOPLMN_SET_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                              sizeof(MMC_MSCC_EOPLMN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstSPlmnSetCnf )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccEOPlmnSetCnf():ERROR:Memory Alloc Error for pstSPlmnSetCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSPlmnSetCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_EOPLMN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstSPlmnSetCnf->ulResult                    = ulRst;

    pstSPlmnSetCnf->MsgHeader.ulMsgName         = ID_MMC_MSCC_EOPLMN_SET_CNF;
    pstSPlmnSetCnf->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSPlmnSetCnf->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSPlmnSetCnf->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSPlmnSetCnf->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstSPlmnSetCnf->MsgHeader.ulLength          = sizeof(MMC_MSCC_EOPLMN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstSPlmnSetCnf);
    return;

}

/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-13, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccNetworkCapabilityInfoInd
 功能描述  : 上报网络能力参数给MSCC module
 输入参数  : pstRcvMsg -- 消息地址

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年07月13日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2014年5月122日
   作    者   : b00269685
   修改内容   : DTS2014050604659修改
 3.日    期   : 2014年6月16日
   作    者   : y00245242
   修改内容   : dts2014052905705修改
*****************************************************************************/
VOS_VOID  NAS_MMC_SndMsccNetworkCapabilityInfoInd(
    NAS_MSCC_PIF_NW_IMS_VOICE_CAP_ENUM_UINT8                     enNwImsVoCap,
    NAS_MSCC_PIF_NW_EMC_BS_CAP_ENUM_UINT8                        enNwEmcBsCap,
    NAS_MSCC_PIF_LTE_CS_CAPBILITY_ENUM_UINT8                     enLteCsCap
)
{
    MMC_MSCC_NETWORK_CAPABILITY_INFO_IND_STRU               *pstSndMsg = VOS_NULL_PTR;

    /*申请消息  */
    pstSndMsg = (MMC_MSCC_NETWORK_CAPABILITY_INFO_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                    WUEPS_PID_MMC,
                    sizeof(MMC_MSCC_NETWORK_CAPABILITY_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstSndMsg)
    {
        PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_MMC_SndMsccNetworkCapabilityInfoInd: Memory Alloc Fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSndMsg) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_NETWORK_CAPABILITY_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* fill in message header */
    pstSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;

    /* fill in message name */
    pstSndMsg->MsgHeader.ulMsgName         = ID_MMC_MSCC_NETWORK_CAPABILITY_INFO_IND;

    /* fill in message content */
    pstSndMsg->enLteCsCap         = enLteCsCap;

    pstSndMsg->enNwImsVoCap       = enNwImsVoCap;
    pstSndMsg->enNwEmcBsCap       = enNwEmcBsCap;

    PS_SEND_MSG(WUEPS_PID_MMC, pstSndMsg);

    return;
}
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-13, end */

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccCampOnInd
 功能描述  : 发送MSCC驻留指示
 输入参数  : ucCampOnFlg---是否驻留
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年11月18日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccCampOnInd(
    VOS_UINT8                           ucCampOnFlg
)
{
    MMC_MSCC_CAMP_ON_IND_STRU_STRU      *pstCampOnInd       = VOS_NULL_PTR;

    pstCampOnInd = (MMC_MSCC_CAMP_ON_IND_STRU_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                        sizeof(MMC_MSCC_CAMP_ON_IND_STRU_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstCampOnInd )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccCampOnInd():ERROR:Memory Alloc Error for pstCampOnInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstCampOnInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_CAMP_ON_IND_STRU_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstCampOnInd->MsgHeader.ulMsgName         = ID_MMC_MSCC_CAMP_ON_IND;
    pstCampOnInd->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstCampOnInd->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstCampOnInd->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstCampOnInd->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstCampOnInd->MsgHeader.ulLength          = sizeof(MMC_MSCC_CAMP_ON_IND_STRU_STRU) - VOS_MSG_HEAD_LENGTH;

    pstCampOnInd->ucCampOnFlg                 = ucCampOnFlg;

    PS_SEND_MSG(WUEPS_PID_MMC, pstCampOnInd);

    return;
}

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

/* Added by s00246516 for L-C互操作项目, 2014-02-12, Begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccAcqCnf
 功能描述  : 发送ACQ CNF消息
 输入参数  : enAcqRslt--获取结果
             pstPlmnId--获取成功时的PLMN ID
             usArfcn  --获取成功时的频点
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年02月12日
   作    者   : s00246516
   修改内容   : 新生成函数
 2.日    期   : 2015年7月20日
   作    者   : w000316404
   修改内容   : R11协议升级(LTE频点配置值扩展)
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccAcqCnf(
    NAS_MSCC_PIF_ACQ_RESULT_ENUM_UINT32      enAcqRslt,
    MSCC_MMC_PLMN_ID_STRU                   *pstPlmnId,
    VOS_UINT32                               ulArfcn
)
{
    MMC_MSCC_ACQ_CNF_STRU               *pstAcqCnf = VOS_NULL_PTR;

    /* 申请消息包 */
    pstAcqCnf = (MMC_MSCC_ACQ_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_MSCC_ACQ_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstAcqCnf)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccAcqCnf():ERROR:Memory Alloc Error for pstAcqCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstAcqCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_ACQ_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstAcqCnf->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstAcqCnf->stMsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstAcqCnf->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstAcqCnf->stMsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstAcqCnf->stMsgHeader.ulLength          = sizeof(MMC_MSCC_ACQ_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstAcqCnf->stMsgHeader.ulMsgName         = ID_MMC_MSCC_ACQ_CNF;

    /* 填充消息内容 */
    pstAcqCnf->enAcqRslt                     = enAcqRslt;
    pstAcqCnf->ulArfcn                       = ulArfcn;
    pstAcqCnf->stPlmnId.ulMcc                = pstPlmnId->ulMcc;
    pstAcqCnf->stPlmnId.ulMnc                = pstPlmnId->ulMnc;
    pstAcqCnf->enPrioClass                   = NAS_MMC_GetPlmnPrioClass(pstPlmnId);

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMC, pstAcqCnf);
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccAcqInd
 功能描述  : 发送ACQ Ind消息
 输入参数  : enAcqRslt--获取结果
             pstPlmnId--获取成功时的PLMN ID
             usArfcn  --获取成功时的频点
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年02月12日
   作    者   : s00246516
   修改内容   : 新生成函数
 2.日    期   : 2015年7月20日
   作    者   : w000316404
   修改内容   : R11协议升级(LTE频点配置值扩展)
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccAcqInd(
    NAS_MSCC_PIF_ACQ_RESULT_ENUM_UINT32      enAcqRslt,
    MSCC_MMC_PLMN_ID_STRU               *pstPlmnId,
    VOS_UINT32                          ulArfcn
)
{
    MMC_MSCC_ACQ_IND_STRU               *pstAcqInd = VOS_NULL_PTR;

    /* 申请消息包 */
    pstAcqInd = (MMC_MSCC_ACQ_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_MSCC_ACQ_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstAcqInd)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccAcqInd():ERROR:Memory Alloc Error for pstAcqCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstAcqInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_ACQ_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstAcqInd->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstAcqInd->stMsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstAcqInd->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstAcqInd->stMsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstAcqInd->stMsgHeader.ulLength          = sizeof(MMC_MSCC_ACQ_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstAcqInd->stMsgHeader.ulMsgName         = ID_MMC_MSCC_ACQ_IND;

    /* 填充消息内容 */
    pstAcqInd->enAcqRslt                     = enAcqRslt;
    pstAcqInd->ulArfcn                       = ulArfcn;
    pstAcqInd->stPlmnId.ulMcc                = pstPlmnId->ulMcc;
    pstAcqInd->stPlmnId.ulMnc                = pstPlmnId->ulMnc;
    pstAcqInd->enPrioClass                   = NAS_MMC_GetPlmnPrioClass(pstPlmnId);

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMC, pstAcqInd);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccRegCnf
 功能描述  : 发送Reg CNF消息
 输入参数  : enRegRslt--注册结果
             pstPlmnId--最后注册时的PLMN ID
             usArfcn  --最后注册时的频点
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年02月12日
   作    者   : s00246516
   修改内容   : 新生成函数
 2.日    期   : 2015年7月20日
   作    者   : w000316404
   修改内容   : R11协议升级(LTE频点配置值扩展)
 3.日    期   : 2015年08月20日
   作    者   : wx270776
   修改内容   : VIA CL DTS2015031602665
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccRegCnf(
    MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8  enLmmAttachClRegStatus,
    NAS_MSCC_PIF_REG_RESULT_ENUM_UINT32 enRegRslt,
    MSCC_MMC_PLMN_ID_STRU              *pstPlmnId,
    VOS_UINT32                          ulArfcn
)
{
    MMC_MSCC_REG_CNF_STRU               *pstRegCnf = VOS_NULL_PTR;

    /* 申请消息包 */
    pstRegCnf = (MMC_MSCC_REG_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_MSCC_REG_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstRegCnf)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccRegCnf():ERROR:Memory Alloc Error for pstRegCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstRegCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_REG_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstRegCnf->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstRegCnf->stMsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstRegCnf->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstRegCnf->stMsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstRegCnf->stMsgHeader.ulLength          = sizeof(MMC_MSCC_REG_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstRegCnf->stMsgHeader.ulMsgName         = ID_MMC_MSCC_REG_CNF;

    /* 填充消息内容 */
    pstRegCnf->enRegRslt                     = enRegRslt;
    pstRegCnf->ulArfcn                       = ulArfcn;
    pstRegCnf->stPlmnId.ulMcc                = pstPlmnId->ulMcc;
    pstRegCnf->stPlmnId.ulMnc                = pstPlmnId->ulMnc;
    pstRegCnf->enPrioClass                   = NAS_MMC_GetPlmnPrioClass(pstPlmnId);
    pstRegCnf->enLmmAttachClRegStatus        = enLmmAttachClRegStatus;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMC, pstRegCnf);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccPowerSaveCnf
 功能描述  : 发送Power Save CNF消息
 输入参数  : enCause -- power save原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年02月12日
   作    者   : s00246516
   修改内容   : 新生成函数
 2.日    期   : 2015年4月27日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccPowerSaveCnf(
    NAS_MSCC_PIF_POWER_SAVE_RESULT_ENUM_UINT8               enCause
)
{
    MMC_MSCC_POWER_SAVE_CNF_STRU        *pstPowerSaveCnf = VOS_NULL_PTR;

    /* 申请消息包 */
    pstPowerSaveCnf = (MMC_MSCC_POWER_SAVE_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_MSCC_POWER_SAVE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstPowerSaveCnf)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccPowerSaveCnf():ERROR:Memory Alloc Error for pstPowerSaveCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstPowerSaveCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_POWER_SAVE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstPowerSaveCnf->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPowerSaveCnf->stMsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstPowerSaveCnf->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPowerSaveCnf->stMsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstPowerSaveCnf->stMsgHeader.ulLength          = sizeof(MMC_MSCC_POWER_SAVE_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPowerSaveCnf->stMsgHeader.ulMsgName         = ID_MMC_MSCC_POWER_SAVE_CNF;

    pstPowerSaveCnf->enResult                      = enCause;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMC, pstPowerSaveCnf);

    return;
}

/* Added by s00246516 for L-C互操作项目, 2014-02-12, End */

/* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, Begin */
/*lint -e958 修改人: j00174725; */
/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccPsServiceConnStatusInd
 功能描述  : 给MSCC发送ps业务信令连接状态消息
 输入参数  : ucPsServiceConnStatusFlag - ps业务信令连接状态标识
 输出参数  : 无
 返 回 值  : 无
 修改历史      :
 1.日    期   : 2014年6月27日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccPsServiceConnStatusInd(
    VOS_UINT8                                       ucPsServiceConnStatusFlag,
    MSCC_MMC_PS_SIGNALING_TYPE_ENUM_UINT8           enPsSigType
)
{
    MMC_MSCC_PS_SERVICE_CONN_STATUS_IND_STRU    *pstPsServiceConnStatusInd = VOS_NULL_PTR;

    pstPsServiceConnStatusInd = (MMC_MSCC_PS_SERVICE_CONN_STATUS_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                        sizeof(MMC_MSCC_PS_SERVICE_CONN_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstPsServiceConnStatusInd )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccCsServiceConnStatusInd():ERROR:Memory Alloc Error for pstUsimAuthFailInds ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstPsServiceConnStatusInd) + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(MMC_MSCC_PS_SERVICE_CONN_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstPsServiceConnStatusInd->stMsgHeader.ulMsgName         = ID_MMC_MSCC_PS_SERVICE_CONN_STATUS_IND;
    pstPsServiceConnStatusInd->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPsServiceConnStatusInd->stMsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstPsServiceConnStatusInd->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPsServiceConnStatusInd->stMsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstPsServiceConnStatusInd->stMsgHeader.ulLength          = sizeof(MMC_MSCC_PS_SERVICE_CONN_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填充消息*/
    pstPsServiceConnStatusInd->ucPsServiceConnStatusFlag   = ucPsServiceConnStatusFlag;
    pstPsServiceConnStatusInd->enPsSigType                 = enPsSigType;

    PS_SEND_MSG(WUEPS_PID_MMC, pstPsServiceConnStatusInd);
    return;
}
/*lint +e958 修改人: j00174725; */
/* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, End */
/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccRfAvailInd
 功能描述  : 向MSCC发送RF资源是否可用指示
 输入参数  : ucRfAvail    - RF是否可用
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月30日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccRfAvailInd(
    VOS_UINT8                           ucRfAvail
)
{
    /* 按MMC_MSCC_AREA_LOST_NO_RF_STATUS_IND_STRU消息结果封装 */
    MMC_MSCC_RF_AVAILABLE_IND_STRU     *pstRfAvailInd = VOS_NULL_PTR;

    pstRfAvailInd = (MMC_MSCC_RF_AVAILABLE_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                              sizeof(MMC_MSCC_RF_AVAILABLE_IND_STRU)- VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstRfAvailInd )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccRfAvailInd():ERROR:Memory Alloc Error for pstServiceStatusInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstRfAvailInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_RF_AVAILABLE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstRfAvailInd->stMsgHeader.ulMsgName           = ID_MMC_MSCC_RF_AVAILABLE_IND;
    pstRfAvailInd->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstRfAvailInd->stMsgHeader.ulSenderPid         = WUEPS_PID_MMC;
    pstRfAvailInd->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstRfAvailInd->stMsgHeader.ulReceiverPid       = UEPS_PID_MSCC;
    pstRfAvailInd->stMsgHeader.ulLength            = sizeof(MMC_MSCC_RF_AVAILABLE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstRfAvailInd->ucRfAvailFlg                    = ucRfAvail;
    pstRfAvailInd->enRatType                       = NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_3GPP;

    PS_SEND_MSG(WUEPS_PID_MMC, pstRfAvailInd);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccSrchedPlmnInfo
 功能描述  : 发送ID_MMC_MSCC_SRCHED_PLMN_INFO_IND消息
 输入参数  : MSCC_MMC_SRCHED_PLMN_INFO_IND_STRU  *pstMmcSrchedPlmnINfo搜索PLMN info
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年02月12日
   作    者   : s00246516
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccSrchedPlmnInfo(const MMC_MSCC_SRCHED_PLMN_INFO_IND_STRU  *pstMmcSrchedPlmnINfo)
{
    MMC_MSCC_SRCHED_PLMN_INFO_IND_STRU                     *pstSrchedPlmnInfoInd = VOS_NULL_PTR;

    pstSrchedPlmnInfoInd = (MMC_MSCC_SRCHED_PLMN_INFO_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                            sizeof(MMC_MSCC_SRCHED_PLMN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSrchedPlmnInfoInd)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccSrchedPlmnInfo():ERROR:Memory Alloc Error for pstSrchedPlmnInfoInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSrchedPlmnInfoInd) + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(MMC_MSCC_SRCHED_PLMN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);


    /* 填充ID_MMC_MSCC_SRCHED_PLMN_INFO_IND消息 */
    PS_MEM_CPY(pstSrchedPlmnInfoInd,
               pstMmcSrchedPlmnINfo,
               sizeof(MMC_MSCC_SRCHED_PLMN_INFO_IND_STRU));

    /* 填充消息头 */
    pstSrchedPlmnInfoInd->stMsgHeader.ulMsgName         = ID_MMC_MSCC_SRCHED_PLMN_INFO_IND;
    pstSrchedPlmnInfoInd->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSrchedPlmnInfoInd->stMsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSrchedPlmnInfoInd->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSrchedPlmnInfoInd->stMsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstSrchedPlmnInfoInd->stMsgHeader.ulLength          = sizeof(MMC_MSCC_SRCHED_PLMN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_SEND_MSG(WUEPS_PID_MMC, pstSrchedPlmnInfoInd);

    return;
}


#if(FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccSrvAcqCnf
 功能描述  : 发送ID_MMC_MSCC_SRV_ACQ_CNF消息
 输入参数  : enResult  - 获取结果
             enSrvType - 业务类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年06月17日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccSrvAcqCnf(
    NAS_MSCC_PIF_SRV_ACQ_RESULT_ENUM_UINT8   enResult
)
{
    MMC_MSCC_SRV_ACQ_CNF_STRU           *pstSrvAcqCnf = VOS_NULL_PTR;

    /* 申请消息包 */
    pstSrvAcqCnf = (MMC_MSCC_SRV_ACQ_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_MSCC_SRV_ACQ_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSrvAcqCnf)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccSrvAcqCnf():ERROR:Memory Alloc Error for pstAcqCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSrvAcqCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_SRV_ACQ_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstSrvAcqCnf->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSrvAcqCnf->stMsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSrvAcqCnf->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSrvAcqCnf->stMsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstSrvAcqCnf->stMsgHeader.ulLength          = sizeof(MMC_MSCC_SRV_ACQ_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSrvAcqCnf->stMsgHeader.ulMsgName         = ID_MMC_MSCC_SRV_ACQ_CNF;

    /* 填充消息内容 */
    pstSrvAcqCnf->enResult                      = enResult;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMC, pstSrvAcqCnf);

    return;
}



#endif
/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccCFPlmnSetCnf
 功能描述  : MMC上MSCC上报处理的结果
 输入参数  : enRegRslt
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月5日
   作    者   : f00279542
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccCFPlmnSetCnf(
    NAS_MSCC_PIF_CFPLMN_OPER_RESULT_ENUM_UINT32             enRslt
)
{
    MMC_MSCC_CFPLMN_SET_CNF_STRU       *pstCFPlmnCnf = VOS_NULL_PTR;

    pstCFPlmnCnf = (MMC_MSCC_CFPLMN_SET_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                                   sizeof(MMC_MSCC_CFPLMN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    if(VOS_NULL_PTR == pstCFPlmnCnf)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccCFPlmnSetCnf:ERROR:Memory Alloc Error for pstCFPlmnCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstCFPlmnCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_CFPLMN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);


    /* 填充消息头 */
    pstCFPlmnCnf->stMsgHeader.ulMsgName         = ID_MMC_MSCC_CFPLMN_SET_CNF;
    pstCFPlmnCnf->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstCFPlmnCnf->stMsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstCFPlmnCnf->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstCFPlmnCnf->stMsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstCFPlmnCnf->stMsgHeader.ulLength          = sizeof(MMC_MSCC_CFPLMN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCFPlmnCnf->enResult                      = enRslt;

    PS_SEND_MSG(WUEPS_PID_MMC, pstCFPlmnCnf);
    return;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccCFPlmnQueryCnf
 功能描述  : MMC上MSCC上报处理的结果
 输入参数  : pstCFPlmnListCnf: 消息内容
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月5日
   作    者   : f00279542
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccCFPlmnQueryCnf(
    NAS_MSCC_PIF_CFPLMN_OPER_RESULT_ENUM_UINT32             enRslt,
    NAS_MSCC_PIF_CFPLMN_LIST_STRU                          *pstCFPlmnListInfo
)
{
    MMC_MSCC_CFPLMN_QUERY_CNF_STRU     *pstCFPlmnCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulLoop;

    pstCFPlmnCnf = (MMC_MSCC_CFPLMN_QUERY_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                                     sizeof(MMC_MSCC_CFPLMN_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstCFPlmnCnf)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccCFPlmnQueryCnf:ERROR:Memory Alloc Error for pstCFPlmnCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstCFPlmnCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_CFPLMN_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstCFPlmnCnf->stMsgHeader.ulMsgName         = ID_MMC_MSCC_CFPLMN_QUERY_CNF;
    pstCFPlmnCnf->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstCFPlmnCnf->stMsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstCFPlmnCnf->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstCFPlmnCnf->stMsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstCFPlmnCnf->stMsgHeader.ulLength          = sizeof(MMC_MSCC_CFPLMN_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCFPlmnCnf->enResult                      = enRslt;

    if (VOS_NULL_PTR != pstCFPlmnListInfo)
    {
        pstCFPlmnCnf->ucPlmnNum = pstCFPlmnListInfo->ucPlmnNum;
        if (pstCFPlmnListInfo->ucPlmnNum > NAS_MSCC_PIF_MAX_CFPLMN_NUM)
        {
            pstCFPlmnCnf->ucPlmnNum = NAS_MSCC_PIF_MAX_CFPLMN_NUM;
        }

        for (ulLoop = 0; ulLoop < pstCFPlmnCnf->ucPlmnNum; ulLoop++)
        {
            pstCFPlmnCnf->astPlmn[ulLoop].ulMcc = pstCFPlmnListInfo->astPlmn[ulLoop].ulMcc;
            pstCFPlmnCnf->astPlmn[ulLoop].ulMnc= pstCFPlmnListInfo->astPlmn[ulLoop].ulMnc;
        }
    }

    PS_SEND_MSG(WUEPS_PID_MMC, pstCFPlmnCnf);
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccPrefPlmnSetCnf
 功能描述  : MMC上MSCC上报处理的结果
 输入参数  : NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_ENUM_UINT32          enRslt
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月08日
   作    者   : y00307564
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccPrefPlmnSetCnf(
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_ENUM_UINT32          enRslt
)
{
    NAS_MSCC_PIF_PREF_PLMN_SET_CNF_STRU                    *pstPrefPlmnCnf  = VOS_NULL_PTR;

    pstPrefPlmnCnf = (NAS_MSCC_PIF_PREF_PLMN_SET_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                          sizeof(NAS_MSCC_PIF_PREF_PLMN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstPrefPlmnCnf )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccPrefPlmnSetCnf:ERROR:Memory Alloc Error for pstPrefPlmnCnf ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstPrefPlmnCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(NAS_MSCC_PIF_PREF_PLMN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstPrefPlmnCnf->stMsgHeader.ulMsgName         = ID_MMC_MSCC_PREF_PLMN_SET_CNF;
    pstPrefPlmnCnf->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPrefPlmnCnf->stMsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstPrefPlmnCnf->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPrefPlmnCnf->stMsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstPrefPlmnCnf->stMsgHeader.ulLength          = sizeof(NAS_MSCC_PIF_PREF_PLMN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstPrefPlmnCnf->enRslt                        = enRslt;

    PS_SEND_MSG(WUEPS_PID_MMC, pstPrefPlmnCnf);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccDplmnSetCnf
 功能描述  : MMC给MSCC发送ID_MMC_MSCC_DPLMN_SET_CNF消息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : n00355355
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccDplmnSetCnf(
    VOS_UINT32                         ulRslt,
    TAF_MMA_CTRL_STRU                 *pstCtrl
)
{
    MMC_MSCC_DPLMN_SET_CNF_STRU        *pstSndMsg = VOS_NULL_PTR;

    /* 申请消息 */
    pstSndMsg = (MMC_MSCC_DPLMN_SET_CNF_STRU *)NAS_MMC_ALLOC_MSG_WITH_HDR(sizeof(MMC_MSCC_DPLMN_SET_CNF_STRU));

    if (VOS_NULL_PTR == pstSndMsg)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccDplmnSetCnf:ERROR:Memory Alloc Error for pstMsg ");
        return;
    }

    /* 清空消息内容 */
    NAS_MMC_CLR_MSG_ENTITY(pstSndMsg);

    /* 填写消息头*/
    NAS_MMC_CFG_MSG_HDR(pstSndMsg,
                        UEPS_PID_MSCC,
                        ID_MMC_MSCC_DPLMN_SET_CNF,
                        sizeof(MMC_MSCC_DPLMN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息内容*/
    PS_MEM_CPY(&(pstSndMsg->stCtrl), pstCtrl, sizeof(TAF_MMA_CTRL_STRU));
    pstSndMsg->ulRslt = ulRslt;

    /* 消息发送 */
    NAS_MMC_SEND_MSG(pstSndMsg);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccGetGeoCnf
 功能描述  : 发送ID_MMC_MSCC_GET_GEO_CNF消息
 输入参数  : NAS_MSCC_PIF_PLMN_ID_STRU          *pstPlmnId
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月23日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccGetGeoCnf(
    NAS_MSCC_PIF_PLMN_ID_STRU          *pstPlmnId
)
{
    MMC_MSCC_GET_GEO_CNF_STRU                    *pstMsg  = VOS_NULL_PTR;

    pstMsg = (MMC_MSCC_GET_GEO_CNF_STRU *)NAS_MMC_ALLOC_MSG_WITH_HDR(sizeof(MMC_MSCC_GET_GEO_CNF_STRU));

    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccGetGeoCnf:ERROR:Memory Alloc Error for pstMsg ");
        return;
    }

    /* 清空消息内容 */
    NAS_MMC_CLR_MSG_ENTITY(pstMsg);

    /* 填写消息头 */
    NAS_MMC_CFG_MSG_HDR(pstMsg,
                        UEPS_PID_MSCC,
                        ID_MMC_MSCC_GET_GEO_CNF,
                        sizeof(MMC_MSCC_GET_GEO_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息内容 */
    /* PLMN ID */
    if (VOS_NULL_PTR == pstPlmnId)
    {
        pstMsg->stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
        pstMsg->stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    }
    else
    {
        PS_MEM_CPY(&(pstMsg->stPlmnId), pstPlmnId, sizeof(NAS_MSCC_PIF_PLMN_ID_STRU));
    }

    NAS_MMC_SEND_MSG(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccStopGetGeoCnf
 功能描述  : 给MSCC发送ID_MMC_MSCC_STOP_GET_GEO_CNF
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月5日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccStopGetGeoCnf(VOS_VOID)
{
    MMC_MSCC_STOP_GET_GEO_CNF_STRU     *pstMsg  = VOS_NULL_PTR;

    pstMsg = (MMC_MSCC_STOP_GET_GEO_CNF_STRU *)NAS_MMC_ALLOC_MSG_WITH_HDR(sizeof(MMC_MSCC_STOP_GET_GEO_CNF_STRU));

    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccStopGetGeoCnf:ERROR:Memory Alloc Error for pstMsg ");
        return;
    }

    /* 清空消息内容 */
    NAS_MMC_CLR_MSG_ENTITY(pstMsg);

    /* 填写消息头 */
    NAS_MMC_CFG_MSG_HDR(pstMsg,
                        UEPS_PID_MSCC,
                        ID_MMC_MSCC_STOP_GET_GEO_CNF,
                        sizeof(MMC_MSCC_STOP_GET_GEO_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息内容 */

    NAS_MMC_SEND_MSG(pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndMmcUpdateUplmnNotify
 功能描述  : 模拟MSCC给mmc上报处理的结果
 输入参数  : pstCFPlmnListCnf: 消息内容
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月08日
   作    者   : y00307564
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndMmcUpdateUplmnNotify( VOS_VOID )
{
    MSCC_MMC_UPDATE_UPLMN_NTF_STRU      *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_MMC_UPDATE_UPLMN_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_MMC_UPDATE_UPLMN_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndMmcUpdateUplmnNtf:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MSCC_MMC_UPDATE_UPLMN_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->MsgHeader.ulLength         = sizeof(MSCC_MMC_UPDATE_UPLMN_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName        = ID_MSCC_MMC_UPDATE_UPLMN_NTF;

    /* 调用VOS发送原语 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}




VOS_VOID NAS_MMC_SndMsccBgSearchCnf(
    MMC_LMM_BG_SRCH_RLT_ENUM_UINT32  enRlst,
    VOS_UINT8                        ucHrpdSysNum,
    LMM_MMC_HRPD_SYS_STRU           *pstHrpdSysList
)
{
    MMC_MSCC_BG_SEARCH_CNF_STRU      *pstMsg = VOS_NULL_PTR;

    /* apply for memory */
    pstMsg = (MMC_MSCC_BG_SEARCH_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                          sizeof(MMC_MSCC_BG_SEARCH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccBgSearchCnf:ERROR:Memory Alloc Error for MMC_MSCC_BG_SEARCH_CNF_STRU ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstMsg) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_BG_SEARCH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* fill message head */
    pstMsg->stMsgHeader.ulMsgName         = ID_MMC_MSCC_BG_SEARCH_CNF;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength          = sizeof(MMC_MSCC_BG_SEARCH_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* fill bg search reseult */
    switch (enRlst)
    {
        case MMC_LMM_BG_SRCH_RLT_SUCCESS:
            pstMsg->enRslt = MSCC_MMC_BG_SRCH_RESULT_SUCCESS;
            break;
        case MMC_LMM_BG_SRCH_RLT_FAIL:
            pstMsg->enRslt = MSCC_MMC_BG_SRCH_RESULT_FAIL;
            break;
        case MMC_LMM_BG_SRCH_RLT_ABORT:
            pstMsg->enRslt = MSCC_MMC_BG_SRCH_RESULT_ABORT;
            break;
        default:
            pstMsg->enRslt = MSCC_MMC_BG_SRCH_RESULT_BUTT;
            break;
    }

    /* only LMM return success, ucHrpdSysNum is valid  */
    if (MSCC_MMC_BG_SRCH_RESULT_SUCCESS == enRlst)
    {
        if (MSCC_MMC_BG_HRPD_MAX_SYS_NUM < ucHrpdSysNum)
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccBgSearchCnf: ucHrpdSysNum overstep the boundary");
            ucHrpdSysNum = MSCC_MMC_BG_HRPD_MAX_SYS_NUM;
        }
        pstMsg->ucHrpdSysNum              = ucHrpdSysNum;
        PS_MEM_CPY(pstMsg->astHrpdSysList, pstHrpdSysList, (ucHrpdSysNum * sizeof(LMM_MMC_HRPD_SYS_STRU)));
    }
    else
    {
        pstMsg->ucHrpdSysNum              = 0;
    }

    /* send message */
    PS_SEND_MSG(WUEPS_PID_MMC, pstMsg);

    return;
}


VOS_VOID NAS_MMC_SndMsccStopBgSearchCnf(VOS_VOID)
{
    MMC_MSCC_STOP_BG_SEARCH_CNF_STRU   *pstMsg = VOS_NULL_PTR;

    /* apply for memory */
    pstMsg = (MMC_MSCC_STOP_BG_SEARCH_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                          sizeof(MMC_MSCC_STOP_BG_SEARCH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccStopBgSearchCnf:ERROR:Memory Alloc Error for MMC_MSCC_STOP_BG_SEARCH_CNF_STRU ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstMsg) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_STOP_BG_SEARCH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* fill message head */
    pstMsg->stMsgHeader.ulMsgName         = ID_MMC_MSCC_STOP_BG_SEARCH_CNF;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength          = sizeof(MMC_MSCC_STOP_BG_SEARCH_CNF_STRU) - VOS_MSG_HEAD_LENGTH;


    /* send message */
    PS_SEND_MSG(WUEPS_PID_MMC, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccMmssLteUnAvailableInd
 功能描述  : 向MSCC发送ID_MMC_MSCC_MMSS_LTE_UNAVAILABLE_IND消息
 输入参数  : enReason----不可用原因
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月30日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2016年1月18日
   作    者   : w00176964
   修改内容   : DTS2016011802320:修改消息名
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccMmssLteUnAvailableInd(
    MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_ENUM_UINT8          enReason
)
{
    MMC_MSCC_MMSS_LTE_UNAVAILABLE_IND_STRU                 *pstMmssLteUnavailableInd = VOS_NULL_PTR;

    pstMmssLteUnavailableInd = (MMC_MSCC_MMSS_LTE_UNAVAILABLE_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                         sizeof(MMC_MSCC_MMSS_LTE_UNAVAILABLE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstMmssLteUnavailableInd )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccMmssLteUnAvailableInd():ERROR:Memory Alloc Error for pstMmssLteUnavailableInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstMmssLteUnavailableInd) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_MMSS_LTE_UNAVAILABLE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstMmssLteUnavailableInd->stMsgHeader.ulMsgName         = ID_MMC_MSCC_MMSS_LTE_UNAVAILABLE_IND;
    pstMmssLteUnavailableInd->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMmssLteUnavailableInd->stMsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMmssLteUnavailableInd->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMmssLteUnavailableInd->stMsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstMmssLteUnavailableInd->stMsgHeader.ulLength          = sizeof(MMC_MSCC_MMSS_LTE_UNAVAILABLE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMmssLteUnavailableInd->enReason = enReason;

    PS_SEND_MSG(WUEPS_PID_MMC, pstMmssLteUnavailableInd);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccQueryPlmnPriClassCnf
 功能描述  : 向MSCC发送ID_MMC_MSCC_PLMN_PRI_CLASS_QUERY_CNF消息
 输入参数  : pstPlmnPriClassListInfo----plmn with pri class info
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年5月4日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2015年6月3日
   作    者   : w00176964
   修改内容   : CDMA Iteration 12
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccQueryPlmnPriClassCnf(
    NAS_MSCC_PIF_PLMN_PRI_CLASS_LIST_INFO_STRU             *pstPlmnPriClassListInfo
)
{
    MMC_MSCC_PLMN_PRI_CLASS_QUERY_CNF_STRU                 *pstPlmnPriClassQueryCnf = VOS_NULL_PTR;

    pstPlmnPriClassQueryCnf = (MMC_MSCC_PLMN_PRI_CLASS_QUERY_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                               sizeof(MMC_MSCC_PLMN_PRI_CLASS_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstPlmnPriClassQueryCnf)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccQueryPlmnPriClassCnf():ERROR:Memory Alloc Error for pstRegRejPlmnSeleInd ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstPlmnPriClassQueryCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_PLMN_PRI_CLASS_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstPlmnPriClassQueryCnf->stMsgHeader.ulMsgName         = ID_MMC_MSCC_PLMN_PRI_CLASS_QUERY_CNF;
    pstPlmnPriClassQueryCnf->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPlmnPriClassQueryCnf->stMsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstPlmnPriClassQueryCnf->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPlmnPriClassQueryCnf->stMsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstPlmnPriClassQueryCnf->stMsgHeader.ulLength          = sizeof(MMC_MSCC_PLMN_PRI_CLASS_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_CPY(&pstPlmnPriClassQueryCnf->stPlmnPriClassList, pstPlmnPriClassListInfo, sizeof(NAS_MSCC_PIF_PLMN_PRI_CLASS_LIST_INFO_STRU));

    PS_SEND_MSG(WUEPS_PID_MMC, pstPlmnPriClassQueryCnf);

    return;
}


/*****************************************************************************
Function Name   :   NAS_MMC_SndMsccPrefPlmnInfoInd
Description     :   Send message MMC_MSCC_PERF_PLMN_INFO to MSCC.
Input parameters:   enPrefPlmnType----pref plmn type
Outout parameters:  VOS_VOID
Return Value    :   VOS_VOID
Modify History:
    1)  Date    :   2015-05-5
        Author  :   w00176964
        Modify content :    Create
    2)  Date    :   2015-06-19
        Author  :   w00242748
        Modify content :    DTS2015061904170: oplmn超过255个后，会导致死循环
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccPrefPlmnInfoInd(
    NAS_MSCC_PIF_PREF_PLMN_TYPE_ENUM_UINT8                  enPrefPlmnType
)
{
    MMC_MSCC_PREF_PLMN_INFO_IND_STRU   *pstMsg          = VOS_NULL_PTR;
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEhplmnInfo   = VOS_NULL_PTR;
    NAS_MML_SIM_USERPLMN_INFO_STRU     *pstUplmnInfo    = VOS_NULL_PTR;
    NAS_MML_SIM_OPERPLMN_INFO_STRU     *pstOplmnInfo    = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    /* apply for memory */
    pstMsg = (MMC_MSCC_PREF_PLMN_INFO_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                          sizeof(MMC_MSCC_PREF_PLMN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccPrefPlmnInfoInd:ERROR:Memory Alloc Error for MMC_MSCC_PREF_PLMN_INFO_IND_STRU ");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstMsg) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_PREF_PLMN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* fill message head */
    pstMsg->stMsgHeader.ulMsgName         = ID_MMC_MSCC_PREF_PLMN_INFO_IND;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength          = sizeof(MMC_MSCC_PREF_PLMN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    if (NAS_MSCC_PREF_PLMN_HPLMN == enPrefPlmnType)
    {
        pstEhplmnInfo = NAS_MML_GetSimEhplmnList();

        for (i = 0,j = 0; i < NAS_MML_MIN(pstEhplmnInfo->ucEhPlmnNum, NAS_MML_MAX_EHPLMN_NUM); i++)
        {
            if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&pstEhplmnInfo->astEhPlmnInfo[i].stPlmnId))
            {
                pstMsg->stEhplmnInfo.astEhPlmnInfo[j].stPlmnId = pstEhplmnInfo->astEhPlmnInfo[i].stPlmnId;
                j++;
            }
        }

        pstMsg->stEhplmnInfo.ucEhPlmnNum = (VOS_UINT8)j;
        pstMsg->enPrefPlmnType           = NAS_MSCC_PREF_PLMN_HPLMN;
    }
    else if (NAS_MSCC_PREF_PLMN_UPLMN == enPrefPlmnType)
    {
        pstUplmnInfo = NAS_MML_GetSimUserPlmnList();

        for (i = 0,j = 0; i < NAS_MML_MIN(pstUplmnInfo->ucUserPlmnNum, NAS_MML_MAX_USERPLMN_NUM); i++)
        {
            if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&pstUplmnInfo->astUserPlmnInfo[i].stPlmnId))
            {
                pstMsg->stUplmnInfo.astUserPlmnInfo[j].stPlmnId = pstUplmnInfo->astUserPlmnInfo[i].stPlmnId;
                j++;
            }
        }

        pstMsg->stUplmnInfo.ucUserPlmnNum = (VOS_UINT8)j;
        pstMsg->enPrefPlmnType            = NAS_MSCC_PREF_PLMN_UPLMN;
    }
    else if (NAS_MSCC_PREF_PLMN_OPLMN == enPrefPlmnType)
    {
        pstOplmnInfo = NAS_MML_GetSimOperPlmnList();

        for (i = 0,j = 0; i < NAS_MML_MIN(pstOplmnInfo->usOperPlmnNum, NAS_MML_MAX_OPERPLMN_NUM); i++)
        {
            if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&pstOplmnInfo->astOperPlmnInfo[i].stPlmnId))
            {
                pstMsg->stOplmnInfo.astOperPlmnInfo[j].stPlmnId = pstOplmnInfo->astOperPlmnInfo[i].stPlmnId;
                j++;
            }
        }

        pstMsg->stOplmnInfo.usOperPlmnNum = (VOS_UINT16)j;
        pstMsg->enPrefPlmnType            = NAS_MSCC_PREF_PLMN_OPLMN;
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccPrefPlmnInfoInd:ERROR:invalid pref plmn type entered! ");
        pstMsg->enPrefPlmnType = NAS_MSCC_PREF_PLMN_TYPE_BUTT;
    }

    /* send message */
    PS_SEND_MSG(WUEPS_PID_MMC, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccInterSysStartInd
 功能描述  : 向MSCC发送ID_MMC_MSCC_INTERSYS_START_IND消息
 输入参数  : enInterSysCause----异系统变换原因值
             enOrignRatMode-----异系统变换时原始接入模式
             enDestRatMode-----异系统变换到的目标接入模式
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年11月4日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccInterSysStartInd(
    NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32                 enInterSysCause,
    VOS_RATMODE_ENUM_UINT32                                 enOrignRatMode,
    VOS_RATMODE_ENUM_UINT32                                 enDestRatMode
)
{
    MMC_MSCC_INTERSYS_START_IND_STRU   *pstMsg = VOS_NULL_PTR;

    /* apply for memory */
    pstMsg = (MMC_MSCC_INTERSYS_START_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                          sizeof(MMC_MSCC_INTERSYS_START_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstMsg) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_INTERSYS_START_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* fill message head */
    pstMsg->stMsgHeader.ulMsgName         = ID_MMC_MSCC_INTERSYS_START_IND;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength          = sizeof(MMC_MSCC_INTERSYS_START_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enInterSysCause = enInterSysCause;
    pstMsg->enOrignRatMode  = enOrignRatMode;
    pstMsg->enDestRatMode   = enDestRatMode;

    /* send message */
    PS_SEND_MSG(WUEPS_PID_MMC, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccInterSysEndInd
 功能描述  : 向MSCC发送ID_MMC_MSCC_INTERSYS_END_IND消息
 输入参数  : enCampedRatMode----当前驻留接入模式
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年11月4日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccInterSysEndInd(
    VOS_RATMODE_ENUM_UINT32             enCurrRatMode
)
{
    MMC_MSCC_INTERSYS_END_IND_STRU   *pstMsg = VOS_NULL_PTR;

    /* apply for memory */
    pstMsg = (MMC_MSCC_INTERSYS_END_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                          sizeof(MMC_MSCC_INTERSYS_END_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstMsg) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_INTERSYS_END_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* fill message head */
    pstMsg->stMsgHeader.ulMsgName         = ID_MMC_MSCC_INTERSYS_END_IND;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulLength          = sizeof(MMC_MSCC_INTERSYS_END_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enCurrRatMode = enCurrRatMode;

    /* send message */
    PS_SEND_MSG(WUEPS_PID_MMC, pstMsg);

    return;
}

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



