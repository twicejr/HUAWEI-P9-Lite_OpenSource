/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcSndMm.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2010年5月9日
  最近修改   :
  功能描述   : MMC发给MM的消息的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2011年05月9日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "NasMmSublayerDef.h"
#include "NasMmcCtx.h"
#include "NasMmcSndMm.h"
#include "NasMmlMsgProc.h"
#include "MmcMmInterface.h"
#include "NasMmlCtx.h"
#include "NasMmlLib.h"
#include "NasMmcProcRegRslt.h"
#include "NasMmcComFunc.h"
#include "Nasrrcinterface.h"
#include "NVIM_Interface.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_SND_MM_C

/*****************************************************************************
  2 全局变量
*****************************************************************************/
/*****************************************************************************
  3 宏定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMmStartReq
 功能描述  : 给MM发送开机消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月10日
    作    者   : luokaihui /l00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整

*****************************************************************************/
VOS_VOID NAS_MMC_SndMmStartReq(VOS_VOID)
{
    MMCMM_START_REQ_STRU               *pstMsg = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstMsg          = (MMCMM_START_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_START_REQ_STRU));
    if ( VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->MsgHeader.ulLength          = sizeof(MMCMM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息名称  */
    pstMsg->MsgHeader.ulMsgName   = MMCMM_START_REQ;

    NAS_MML_SndInternalMsg(pstMsg);
}

 /*****************************************************************************
  函 数 名  : NAS_MMC_SndMmPowerOffReq
  功能描述  : 向MM模块发送关机原语MMCMM_POWER_OFF_REQ的处理
  输入参数  : VOS_VOID
  输出参数  : 无
  返 回 值  : VOS_VOID
  调用函数  :
  被调函数  :

 修改历史      :
  1.日    期   : 2011年5月9日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整

*****************************************************************************/
VOS_VOID NAS_MMC_SndMmPowerOffReq(VOS_VOID)
{
    MMCMM_POWER_OFF_REQ_STRU               *pstMsg              = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstMsg          = (MMCMM_POWER_OFF_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_POWER_OFF_REQ_STRU));
    if ( VOS_NULL_PTR == pstMsg)
    {
        return;
    }
    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->MsgHeader.ulLength          = sizeof(MMCMM_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息类别 */
    pstMsg->MsgHeader.ulMsgName         = MMCMM_POWER_OFF_REQ;

    NAS_MML_SndInternalMsg(pstMsg);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMmSuspendInd
 功能描述  : MMC向MM发送挂起指示
 输入参数  : RRMM_SUSPEND_IND_ST                *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月9日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整

*****************************************************************************/
VOS_VOID NAS_MMC_SndMmSuspendInd(
    RRMM_SUSPEND_IND_ST                *pstMsg
)
{
    /*向MM发送挂起指示,定义原语类型指针 */
    MMCMM_SUSPEND_IND_STRU             *pstSndMsg = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstSndMsg       = (MMCMM_SUSPEND_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_SUSPEND_IND_STRU));
    if ( VOS_NULL_PTR == pstSndMsg)
    {
        return;
    }

    pstSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;

    /* 填写消息名称 */
    pstSndMsg->MsgHeader.ulMsgName         = MMCMM_SUSPEND_IND;
    pstSndMsg->MsgHeader.ulLength          = sizeof(MMCMM_SUSPEND_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->ucSuspendCause              = pstMsg->ucSuspendCause;
    pstSndMsg->ucSuspendOrigen             = pstMsg->ucSuspendOrigen;
    pstSndMsg->ucSuspendDestination        = pstMsg->ucSuspendDestination;

    PS_MEM_CPY(pstSndMsg->astReTxMsg, pstMsg->astReTxMsg, sizeof(NAS_RRC_RE_TX_MSG_STRU));

    NAS_MML_SndInternalMsg(pstSndMsg);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndMmPlmnSchInit
 功能描述  : 向MM发送plmnsrchinit
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月9日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID  NAS_MMC_SndMmPlmnSchInit(VOS_VOID)
{
    /*向MM发送挂起指示,定义原语类型指针 */
    MMCMM_PLMN_SEARCH_INITIATED_STRU   *pstSndMsg = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstSndMsg       = (MMCMM_PLMN_SEARCH_INITIATED_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_PLMN_SEARCH_INITIATED_STRU));
    if ( VOS_NULL_PTR == pstSndMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMmPlmnSchInit:ALLOC MEM ERROR!");
        return;
    }

    pstSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstSndMsg->MsgHeader.ulLength
        = sizeof(MMCMM_PLMN_SEARCH_INITIATED_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息类别 */
    pstSndMsg->MsgHeader.ulMsgName         = MMCMM_PLMN_SEARCH_INITIATED;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstSndMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMmWasSysInfoInd
 功能描述  : 向MM转发WAS系统消息
 输入参数  : VOS_UINT32                          ulForbiddenFlg
             VOS_UINT8                           ucUserSpecSrchPlmnFlg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月21日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2011年12月24日
    作    者   : w00166186
    修改内容   : DTS2011122004483,指定搜网不停LAU问题统一修改
  3.日    期   : 2012年09月26日
    作    者   : l65478
    修改内容   : DTS2012092201886,HPLMN注册失败#11,重新驻留后cs没有发起注册
  4.日    期   : 2012年11月29日
    作    者   : W00176964
    修改内容   : DTS2012112902395,BVT测试,hplmn被拒#11后后续需要继续注册
  5.日    期   : 2013年07月25日
    作    者   : l65478
    修改内容   : 当前限制驻留,在用户指定搜索当前的网络时,MM不发起注册,GCF失败
  6.日    期   : 2013年9月14日
    作    者   : w00167002
    修改内容   : DTS2013090908249:开机用户指定搜网24003，CS注册被拒15，MM在LIMIT
                 状态，在选网状态机收到同一小区的SYSINFO后，通知MM当前没有FORB FLG,
                 导致MM发起循环注册；
                 在NAS_MMC_SndMmGsmSysInfoInd函数中，如果是用户指定搜网，则将FORBFLG设置为null，
                 将此耦合去除；
                 在选网状态机识别出是否是用户指定搜网，并配置正确的ulForbiddenFlg标志；
  7.日    期   : 2015年6月11日
    作    者   : b00269685
    修改内容   : 区分ota 和 sys
  8.日    期   : 2015年11月16日
    作    者   : c00318887
    修改内容   : DTS2015061609864
*****************************************************************************/
VOS_VOID   NAS_MMC_SndMmWasSysInfoInd(
    VOS_UINT32                          ulForbiddenFlg,
    VOS_UINT32                          ulUserSpecSrchPlmnFlg,
    struct MsgCB                       *pstMsg
)
{
    MMCMM_SYS_INFO_IND_STRU            *pstInternalMsg    = VOS_NULL_PTR;
    RRMM_SYS_INFO_IND_STRU             *pstRrMmSysInfoInd = VOS_NULL_PTR;

    pstInternalMsg  = (MMCMM_SYS_INFO_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_SYS_INFO_IND_STRU));
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    PS_MEM_SET(pstInternalMsg, 0x00, sizeof(MMCMM_SYS_INFO_IND_STRU));

    pstRrMmSysInfoInd = (RRMM_SYS_INFO_IND_STRU *)pstMsg;

    pstInternalMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstInternalMsg->MsgHeader.ulMsgName         = MMCMM_SYS_INFO_IND;
    pstInternalMsg->MsgHeader.ulLength
                                = sizeof(MMCMM_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstInternalMsg->ulMask = NAS_MMC_GetOptMask_WasSysinfo(pstRrMmSysInfoInd);

    pstInternalMsg->enSysInfoType  = pstRrMmSysInfoInd->enSysInfoType;

    pstInternalMsg->ucCnCommonSize = pstRrMmSysInfoInd->ucCnCommonSize;

    /* aucCnCommonInfo[0] 和 aucCnCommonInfo[1] 代表 lac[0] 和  Lac[1]*/
    pstInternalMsg->usLac  = (VOS_UINT16)pstRrMmSysInfoInd->aucCnCommonInfo[1];
    pstInternalMsg->usLac |= (VOS_UINT16)(pstRrMmSysInfoInd->aucCnCommonInfo[0]<< NAS_MML_OCTET_MOVE_EIGHT_BITS);

    pstInternalMsg->ucCsInfoSize    = pstRrMmSysInfoInd->ucCsInfoSize;
    pstInternalMsg->ucLRTimerT3212  = pstRrMmSysInfoInd->aucCsInfo[0];

    /* aucCsInfo[1]的最低Bit代表当前是否允许注册 */
    if (0 == (pstRrMmSysInfoInd->aucCsInfo[1] & NAS_MML_ATTATCH_IND_BIT_MASK_WAS_SYS_INFO))
    {
        pstInternalMsg->ucAttachDetach = VOS_FALSE;
    }
    else
    {
        pstInternalMsg->ucAttachDetach = VOS_TRUE;
    }

    pstInternalMsg->ucPsInfoSize       = pstRrMmSysInfoInd->ucPsInfoSize;
    pstInternalMsg->ucRac              = pstRrMmSysInfoInd->aucPsInfo[0];

    if (0 == (pstRrMmSysInfoInd->aucPsInfo[1] & NAS_MML_NET_MODE_BIT_MASK_WAS_SYS_INFO))
    {
        pstInternalMsg->ucNetworkOperationMode = GRRMM_NW_OP_MODE_I;
    }
    else
    {
        pstInternalMsg->ucNetworkOperationMode = GRRMM_NW_OP_MODE_II;
    }

    if (0 == pstRrMmSysInfoInd->ucPsInfoSize)
    {
        pstInternalMsg->ucGprsSupportInd = VOS_FALSE;
    }
    else
    {
        pstInternalMsg->ucGprsSupportInd = VOS_TRUE;
    }

    pstInternalMsg->PlmnId.ulMcc           = pstRrMmSysInfoInd->PlmnId.ulMcc;
    pstInternalMsg->PlmnId.ulMnc           = pstRrMmSysInfoInd->PlmnId.ulMnc;

    pstInternalMsg->ulCsDrxLength          = pstRrMmSysInfoInd->ulCsDrxLength;
    pstInternalMsg->ulPsDrxLength          = pstRrMmSysInfoInd->ulPsDrxLength;

    pstInternalMsg->ulForbiddenFlg         = ulForbiddenFlg;


    /* 删除设置用户指定搜时，将ulForbiddenFlg设置为NULL的处理 */
    pstInternalMsg->ulForbiddenFlg           = ulForbiddenFlg;

    /* 在Hplmn上CS注册被拒后，非E5时，不在发起注册 ,E5时，HplmnRejlist不记录值 */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(NAS_MML_GetCurrCampPlmnId()))
    {
        pstInternalMsg->ulForbiddenFlg  = NAS_MMC_ModifyForbiddenFlg_HplmnRegisterRej(
                                                ulForbiddenFlg,
                                                ulUserSpecSrchPlmnFlg,
                                                NAS_MML_NET_RAT_TYPE_WCDMA,
                                                NAS_MMC_REG_DOMAIN_CS);
    }

    pstInternalMsg->ulCellId                = pstRrMmSysInfoInd->ulCellId;

    pstInternalMsg->ucUserSpecificSearchFlg = (VOS_UINT8)ulUserSpecSrchPlmnFlg;

     /* 从bar转为不bar的标志位 */
    pstInternalMsg->ucCsChanged2UnBarFlg    = (VOS_UINT8)NAS_MML_GetCsRegisterBarToUnBarFlg();
    pstInternalMsg->ucPsChanged2UnBarFlg    = (VOS_UINT8)NAS_MML_GetPsRegisterBarToUnBarFlg();

    NAS_MML_SndInternalMsg(pstInternalMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMmGsmSysInfoInd
 功能描述  : 向MM转发系统消息
 输入参数  : VOS_UINT32                          ulForbiddenFlg
             VOS_UINT8                           ucUserSpecSrchPlmnFlg
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月21日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2011年12月24日
    作    者   : w00166186
    修改内容   : DTS2011122004483,指定搜网不停LAU问题统一修改
  3.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 修改变量名
  4.日    期   : 2013年07月25日
    作    者   : l65478
    修改内容   : 当前限制驻留,在用户指定搜索当前的网络时,MM不发起注册,GCF失败
  5.日    期   : 2013年9月14日
    作    者   : w00167002
    修改内容   : DTS2013090908249:开机用户指定搜网24003，CS注册被拒15，MM在LIMIT
                 状态，在选网状态机收到同一小区的SYSINFO后，通知MM当前没有FORB FLG,
                 导致MM发起循环注册；
                 在NAS_MMC_SndMmGsmSysInfoInd函数中，如果是用户指定搜网，则将FORBFLG设置为null，
                 将此耦合去除；
                 在选网状态机识别出是否是用户指定搜网，并配置正确的ulForbiddenFlg标志；
  6.日    期   : 2015年11月16日
    作    者   : c00318887
    修改内容   : DTS2015061609864
*****************************************************************************/
VOS_VOID   NAS_MMC_SndMmGsmSysInfoInd(
    VOS_UINT32                          ulForbiddenFlg,
    VOS_UINT32                          ulUserSpecSrchPlmnFlg,
    struct MsgCB                       *pstMsg
)
{
    MMCMM_GSM_SYS_INFO_IND_ST          *pstInternalMsg  = VOS_NULL_PTR;
    GRRMM_SYS_INFO_IND_ST              *pstGrrMmSysInfo = VOS_NULL_PTR;

    NAS_NORMAL_LOG2(WUEPS_PID_MMC, 
                    "NAS_MMC_SndMmGsmSysInfoInd: ulForbiddenFlg and ulUserSpecSrchPlmnFlg ",
                    ulForbiddenFlg,
                    ulUserSpecSrchPlmnFlg);

    pstInternalMsg  = (MMCMM_GSM_SYS_INFO_IND_ST *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_GSM_SYS_INFO_IND_ST));
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstGrrMmSysInfo = (GRRMM_SYS_INFO_IND_ST *)pstMsg;

    pstInternalMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;

    pstInternalMsg->MsgHeader.ulMsgName         = MMCMM_GSM_SYS_INFO_IND;
    pstInternalMsg->MsgHeader.ulLength
        = sizeof(MMCMM_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填充CS信息 */
    pstInternalMsg->ucAttachDetach           = pstGrrMmSysInfo->ucAttachDetach;
    pstInternalMsg->ucLRTimerT3212           = pstGrrMmSysInfo->ucLRTimerT3212;
    pstInternalMsg->ucGprsSupportInd         = pstGrrMmSysInfo->ucGprsSupportInd;
    pstInternalMsg->usLac                    = pstGrrMmSysInfo->usLac;

    /* 填充PS信息 */
    if (GRRMM_NW_OP_MODE_III == pstGrrMmSysInfo->ucNetworkOperationMode)
    {
        pstInternalMsg->ucNetworkOperationMode = GRRMM_NW_OP_MODE_II;
    }
    else
    {
        pstInternalMsg->ucNetworkOperationMode = pstGrrMmSysInfo->ucNetworkOperationMode;
    }

    pstInternalMsg->ucRac                    = pstGrrMmSysInfo->ucRac;
    pstInternalMsg->stPlmnId.ulMcc           = pstGrrMmSysInfo->PlmnId.ulMcc;
    pstInternalMsg->stPlmnId.ulMnc           = pstGrrMmSysInfo->PlmnId.ulMnc;

    pstInternalMsg->ulForbiddenFlg           = ulForbiddenFlg;

    /* 在Hplmn上CS注册被拒后，非E5时，不在发起注册 ,E5时，HplmnRejlist不记录值 */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(NAS_MML_GetCurrCampPlmnId()))
    {
        pstInternalMsg->ulForbiddenFlg = NAS_MMC_ModifyForbiddenFlg_HplmnRegisterRej(
                                                ulForbiddenFlg,
                                                ulUserSpecSrchPlmnFlg,
                                                NAS_MML_NET_RAT_TYPE_GSM,
                                                NAS_MMC_REG_DOMAIN_CS);

    }

    pstInternalMsg->ucMsrRelease             = pstGrrMmSysInfo->ucMsrRelease;
    pstInternalMsg->ulCellId                 = pstGrrMmSysInfo->usCellId;

    pstInternalMsg->ucUserSpecificSearchFlg  = (VOS_UINT8)ulUserSpecSrchPlmnFlg;

    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    pstInternalMsg->unAcInfo.ucRestrictType               = pstGrrMmSysInfo->unAcInfo.ucRestrictType;

    /* 如果是GSM禁止接入，通知MM/GMM，防止发起注册 */
    if (VOS_TRUE == NAS_MML_GetGsmForbidFlg())
    {
     pstInternalMsg->unAcInfo.ucRestrictType            = RRC_NAS_ACCESS_RESTRICTION_ALL_SERVICE;
    }
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

     /* 从bar转为不bar的标志位 */
    pstInternalMsg->ucCsChanged2UnBarFlg    = (VOS_UINT8)NAS_MML_GetCsRegisterBarToUnBarFlg();
    pstInternalMsg->ucPsChanged2UnBarFlg    = (VOS_UINT8)NAS_MML_GetPsRegisterBarToUnBarFlg();

    NAS_MML_SndInternalMsg(pstInternalMsg);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndMmResumeInd
 功能描述  : NAS向MM发送ResumeInd的指示
 输入参数  : RRMM_RESUME_IND_ST                 *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月10日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整
  3.日    期   : 2013年11月26日
    作    者   : w00176964
    修改内容   : Volte PhaseII项目调整

*****************************************************************************/
VOS_VOID  NAS_MMC_SndMmResumeInd(
    RRMM_RESUME_IND_ST                 *pstMsg
)
{
    /*向MM发送恢复指示,定义原语类型指针 */
    MMCMM_RESUME_IND_STRU              *pstSndMsg = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstSndMsg  = (MMCMM_RESUME_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_RESUME_IND_STRU));
    if ( VOS_NULL_PTR == pstSndMsg)
    {
        return;
    }

    pstSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstSndMsg->MsgHeader.ulLength          = sizeof(MMCMM_RESUME_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息名称 */
    pstSndMsg->MsgHeader.ulMsgName   = MMCMM_RESUME_IND;

    pstSndMsg->ucCsResumeResult      = pstMsg->ucCsResumeResult;
    pstSndMsg->ucPsResumeResult      = pstMsg->ucPsResumeResult;
    pstSndMsg->ucResumeOrigen        = pstMsg->ucResumeOrigen;

    pstSndMsg->ucCsSigExistFlg       = VOS_FALSE;

    NAS_MML_SndInternalMsg(pstSndMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMmCoverageLostInd
 功能描述  : NAS向MM发送coverage lost的指示
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月11日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID  NAS_MMC_SndMmCoverageLostInd(VOS_VOID)
{

    MMCMM_COVERAGE_LOST_IND_STRU       *pstSndMsg           = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstSndMsg       = (MMCMM_COVERAGE_LOST_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_COVERAGE_LOST_IND_STRU));
    if ( VOS_NULL_PTR == pstSndMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,"NAS_MMC_SndMmCoverageLostInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    pstSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstSndMsg->MsgHeader.ulLength
        = sizeof(MMCMM_COVERAGE_LOST_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息类别 */
    pstSndMsg->MsgHeader.ulMsgName   = MMCMM_COVERAGE_LOST_IND;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstSndMsg);

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMmWasAcInfoChangeInd
 功能描述  : NAS向MM发送AC INFO CHANGE的指示
 输入参数  :
    VOS_UINT8                           ucCsResTrictionRegister,
    VOS_UINT8                           ucPsResTrictionRegister,
    VOS_UINT8                           ucOldCsResTrictionRegister,
    VOS_UINT8                           ucOldPsResTrictionRegister

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : W00166186
    修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID  NAS_MMC_SndMmWasAcInfoChangeInd(
    VOS_UINT8                           ucCsResTrictionRegister,
    VOS_UINT8                           ucPsResTrictionRegister,
    VOS_UINT8                           ucOldCsResTrictionRegister,
    VOS_UINT8                           ucOldPsResTrictionRegister
)
{
    MMCMM_W_AC_INFO_CHANGE_IND_STRU         *pstSndMsg           = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstSndMsg       = (MMCMM_W_AC_INFO_CHANGE_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_W_AC_INFO_CHANGE_IND_STRU));
    if ( VOS_NULL_PTR == pstSndMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,"NAS_MMC_SndMmWasAcInfoChangeInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    pstSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstSndMsg->MsgHeader.ulLength
        = sizeof(MMCMM_W_AC_INFO_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息类别 */
    pstSndMsg->MsgHeader.ulMsgName         = MMCMM_W_AC_INFO_CHANGE_IND;
    pstSndMsg->enCsRestrictRegisterChange  = NAS_MML_RESTRICTION_NO_CHANGE;
    pstSndMsg->enPsRestrictRegisterChange  = NAS_MML_RESTRICTION_NO_CHANGE;

    /* CS注册从受限变为不受限 */
    if ((VOS_TRUE == ucOldCsResTrictionRegister)
     && (VOS_FALSE == ucCsResTrictionRegister))
    {
        pstSndMsg->enCsRestrictRegisterChange = NAS_MML_RESTRICTION_BAR_TO_UNBAR;
    }

    /* CS注册从不受限变为受限 */
    if ((VOS_FALSE == ucOldCsResTrictionRegister)
     && (VOS_TRUE == ucCsResTrictionRegister))
    {
        pstSndMsg->enCsRestrictRegisterChange = NAS_MML_RESTRICTION_UNBAR_TO_BAR;
    }

    /* PS注册从受限变为不受限 */
    if ((VOS_TRUE == ucOldPsResTrictionRegister)
     && (VOS_FALSE == ucPsResTrictionRegister))
    {
        pstSndMsg->enPsRestrictRegisterChange = NAS_MML_RESTRICTION_BAR_TO_UNBAR;
    }

    /* PS注册从不受限变为受限 */
    if ((VOS_FALSE == ucOldPsResTrictionRegister)
     && (VOS_TRUE == ucPsResTrictionRegister))
    {
        pstSndMsg->enPsRestrictRegisterChange = NAS_MML_RESTRICTION_UNBAR_TO_BAR;
    }

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstSndMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMmRelReq
 功能描述  : 向MM发送CS信令链接释放消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年07月11日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndMmRelReq(VOS_VOID)
{
    /* 向MM发送CS信令链接释放消息 */
    MMCMM_REL_REQ_STRU                 *pstSndMmRelMsg      = VOS_NULL_PTR;

    pstSndMmRelMsg  = (MMCMM_REL_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_REL_REQ_STRU));
    if ( VOS_NULL_PTR == pstSndMmRelMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMmRelReq,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstSndMmRelMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMmRelMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMmRelMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMmRelMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;

    /* 填写消息类别 */
    pstSndMmRelMsg->MsgHeader.ulMsgName         = MMCMM_REL_REQ;
    pstSndMmRelMsg->MsgHeader.ulLength          = sizeof(MMCMM_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstSndMmRelMsg);
    return;
}


/*******************************************************************************
 函 数 名  : NAS_MMC_SndMmAttachReq
 功能描述  : 发送原语MMCMM_ATTACH_REQ的公共处理
 输入参数  : ulOpid       - Opid
              ulAttachType - Attach类型
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月9日
   作    者   : w00166186
   修改内容   : 新建，V7R1 PHASE II,ATTACH/DETACH调整
*******************************************************************************/
VOS_VOID NAS_MMC_SndMmAttachReq(
    VOS_UINT32                          ulOpid,
    VOS_UINT32                          ulAttachType
)
{
    MMCMM_ATTACH_REQ_STRU              *pstMsg              = VOS_NULL_PTR;
    MMCMM_ATTACH_REQ_STRU              *pstInternalMsg      = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstInternalMsg  = (MMCMM_ATTACH_REQ_STRU*)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_ATTACH_REQ_STRU));
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MM;
    pstMsg->MsgHeader.ulMsgName           = MMCMM_ATTACH_REQ;
    pstMsg->MsgHeader.ulLength            = sizeof(MMCMM_ATTACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulOpid                        = ulOpid;
    pstMsg->enAttachType                  = ulAttachType;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);
}

/*******************************************************************************
  函 数 名  : NAS_MMC_SndMmDetachReq
  功能描述  : 发送原语MMCMM_DETACH_REQ的公共处理
  输入参数  : ulOpid         -- 操作标识
              ulDetachType   -- detach类型
              enDetachReason -- detach原因
  输出参数  : 无
  返 回 值  :
  调用函数  :
  被调函数  :

  修改历史      :
  1.日    期   : 2011年7月9日
    作    者   : w00166186
    修改内容   : V7R1 PHASE II,ATTACH/DETACH调整
  2.日    期   : 2015年4月11日
    作    者   : y00245242
    修改内容   : iteration 13开发
*******************************************************************************/
VOS_VOID NAS_MMC_SndMmDetachReq(
    VOS_UINT32                          ulOpid,
    MMC_MM_DETACH_TYPE_ENUM_UINT32      enDetachType,  /* detach类型 */
    MMC_MM_DETACH_REASON_ENUM_UINT32    enDetachReason /* detach原因 */
)
{
    MMCMM_DETACH_REQ_STRU              *pstMsg              = VOS_NULL_PTR;
    MMCMM_DETACH_REQ_STRU              *pstInternalMsg      = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstInternalMsg  = (MMCMM_DETACH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_DETACH_REQ_STRU));
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstMsg                                          = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid                   = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid                 = WUEPS_PID_MM;
    pstMsg->MsgHeader.ulMsgName                     = MMCMM_DETACH_REQ;
    pstMsg->MsgHeader.ulLength                      = sizeof(MMCMM_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enDetachType                            = enDetachType;
    pstMsg->enDetachReason                          = enDetachReason;
    pstMsg->ulOpid                                  = ulOpid;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndMmModeChangeReq
 功能描述  : 给MM发送手机模式更改消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月10日
   作    者   : luokaihui /l00167671
   修改内容   : 新生成函数

 2.日    期   : 2011年8月4日
   作    者   : zhoujun 40661
   修改内容   : 调整接口

*****************************************************************************/
VOS_VOID NAS_MMC_SndMmModeChangeReq(
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode
)
{
    MMCGMM_MODE_CHANGE_REQ_STRU         *pstMsg             = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstMsg          = (MMCGMM_MODE_CHANGE_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_MODE_CHANGE_REQ_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->MsgHeader.ulLength          = sizeof(MMCGMM_MODE_CHANGE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = MMCMM_MODE_CHANGE_REQ;
    pstMsg->enMsMode                    = enMsMode;

    NAS_MML_SndInternalMsg(pstMsg);

    return;
}

/*******************************************************************************
 函 数 名  : NAS_MMC_SndMmRatChangeInd
 功能描述  : 向MM发送MMCMM_RAT_CHANGE_IND消息
 输入参数  : enNetRatType:目标接入层
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

1.日    期   : 2013年3月27日
  作    者   : y00176023
  修改内容   : DSDS GUNAS II项目新增函数
*******************************************************************************/
VOS_VOID NAS_MMC_SndMmRatChangeInd(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType
)
{
    MMCMM_RAT_CHANGE_IND_STRU          *pstMsg              = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstMsg          = (MMCMM_RAT_CHANGE_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_RAT_CHANGE_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {

        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMmRatChangeInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->MsgHeader.ulLength          = sizeof(MMCMM_RAT_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = MMCMM_RAT_CHANGE_IND;
    pstMsg->enNetRatType                = enNetRatType;

    NAS_MML_SndInternalMsg(pstMsg);

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_SndMmLauReq
 功能描述  : 给MM发送LAU消息
 输入参数  : enLauReqReason - MMC触发LAU的原因
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年5月21日
   作    者   : w00167002
   修改内容   : 新生成函数 DTS2014051602857:在SOR打开时候，如果CS注册失败达到4次，则等周期
               搜网定时器超时发起LIST搜网，如果当前仅有原有网络，则发起LAU,否则
               触发MM发起LAU;如果LIST搜后，发现有其他网络，则发起其他网络的搜网注册。

*****************************************************************************/
VOS_VOID NAS_MMC_SndMmLauReq(
    MMC_MM_LAU_REQ_REASON_ENUM_UINT32   enLauReqReason
)
{
    MMCMM_LAU_REQ_STRU                  *pstMsg             = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstMsg          = (MMCMM_LAU_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_LAU_REQ_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->MsgHeader.ulLength          = sizeof(MMCMM_LAU_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = MMCMM_LAU_REQ;
    pstMsg->enLauReqReason              = enLauReqReason;

    NAS_MML_SndInternalMsg(pstMsg);

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_SndMmLteSysinfoInd
 功能描述  : NAS通知mm的LTE系统消息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月19日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年4月28日
    作    者   : W00166186
    修改内容   : DTS2012042602593,MM没有保存当前驻留的PLMN，导致后续判断出错
*****************************************************************************/
VOS_VOID NAS_MMC_SndMmLteSysinfoInd(
    LMM_MMC_SYS_INFO_IND_STRU          *pstLmmSysInfoMsg
)
{

    /* 定义原语类型指针 */
    MMC_MM_LTE_SYS_INFO_IND_STRU       *pstMsg = VOS_NULL_PTR;

    pstMsg              = (MMC_MM_LTE_SYS_INFO_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_MM_LTE_SYS_INFO_IND_STRU));
    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMmLteSysinfoInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* 消息IE项赋值 */
    PS_MEM_CPY(pstMsg, pstLmmSysInfoMsg, sizeof(MMC_MM_LTE_SYS_INFO_IND_STRU));

    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->ulMsgId       = MMCMM_LTE_SYS_INFO_IND;
    pstMsg->ulLength        = sizeof(MMC_MM_LTE_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMmLmmAttachInd
 功能描述  : MMC向MM通知当前LMM的attach结果
 输入参数  : LMM_MMC_ATTACH_IND_STRU        *pstActionResultInd
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月26日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_SndMmLmmAttachInd(
    LMM_MMC_ATTACH_IND_STRU            *pstAttachInd
)
{
    MMCMM_LMM_ATTACH_IND_STRU          *pstMsg = VOS_NULL_PTR;

    pstMsg              = (MMCMM_LMM_ATTACH_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_LMM_ATTACH_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMmLmmAttachInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* 消息IE项赋值 */
    PS_MEM_CPY(pstMsg, pstAttachInd, sizeof(MMCMM_LMM_ATTACH_IND_STRU));

    /* 修改消息头 */
    pstMsg->ulLength        = sizeof(MMCMM_LMM_ATTACH_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->ulMsgId         = MMCMM_LMM_ATTACH_IND;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMmLmmTauResultInd
 功能描述  : MMC向MM通知当前LMM的TAU注册结果
 输入参数  : LMM_MMC_ATTACH_IND_STRU        *pstTauResultInd
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月26日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_SndMmLmmTauResultInd(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstTauResultInd
)
{
    MMCMM_LMM_TAU_RESULT_IND_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg              = (MMCMM_LMM_TAU_RESULT_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_LMM_TAU_RESULT_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMmLmmTauResultInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* 消息IE项赋值 */
    PS_MEM_CPY(pstMsg, pstTauResultInd, sizeof(MMCMM_LMM_TAU_RESULT_IND_STRU));

    /* 修改消息头 */
    pstMsg->ulLength        = sizeof(MMCMM_LMM_TAU_RESULT_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->ulMsgId         = MMCMM_LMM_TAU_RESULT_IND;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMmLmmSerResultnd
 功能描述  : MMC向MM通知当前LMM的service request结果
 输入参数  : LMM_MMC_SERVICE_RESULT_IND_STRU        *pstSerInd
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月26日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_SndMmLmmSerResultnd(
    LMM_MMC_SERVICE_RESULT_IND_STRU    *pstSerInd
)
{
    MMCMM_LMM_SERVICE_RESULT_IND_STRU          *pstMsg = VOS_NULL_PTR;

    pstMsg              = (MMCMM_LMM_SERVICE_RESULT_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_LMM_SERVICE_RESULT_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMmLmmSerResultnd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* 消息IE项赋值 */
    PS_MEM_CPY(pstMsg, pstSerInd, sizeof(MMCMM_LMM_SERVICE_RESULT_IND_STRU));

    /* 修改消息头 */
    pstMsg->ulLength        = sizeof(MMCMM_LMM_SERVICE_RESULT_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->ulMsgId         = MMCMM_LMM_SERVICE_RESULT_IND;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMmLmmMtDetachInd
 功能描述  : MMC向MM通知当前LMM的网侧去注册结果
 输入参数  : LMM_MMC_DETACH_IND_STRU            *pstDetachInd
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月26日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年12月5日
   作    者   : w00176964
   修改内容   : V7R1 PhaseIV调整
*****************************************************************************/
VOS_VOID  NAS_MMC_SndMmLmmMtDetachInd(
    LMM_MMC_DETACH_IND_STRU            *pstDetachInd
)
{
    MMCMM_LMM_MT_DETACH_IND_STRU       *pstMsg = VOS_NULL_PTR;

    /* 申请消息内存分配 */
    pstMsg              = (MMCMM_LMM_MT_DETACH_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_LMM_MT_DETACH_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MMC_SndMmLmmMtDetachInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* 消息IE项赋值 */
    PS_MEM_CPY(pstMsg, pstDetachInd, sizeof(MMCMM_LMM_MT_DETACH_IND_STRU));

    /* 修改消息头 */
    pstMsg->ulLength        = sizeof(MMCMM_LMM_MT_DETACH_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->ulMsgId         = MMCMM_LMM_MT_DETACH_IND;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMmLmmLocalDetachInd
 功能描述  : MMC向MM通知当前LMM的本地去注册结果
 输入参数  : LMM_MMC_DETACH_IND_STRU            *pstDetachInd
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月7日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_MMC_SndMmLmmLocalDetachInd(
    LMM_MMC_DETACH_IND_STRU            *pstDetachInd
)
{
    MMCMM_LMM_LOCAL_DETACH_IND_STRU       *pstMsg = VOS_NULL_PTR;

    /* 申请消息内存分配 */
    pstMsg              = (MMCMM_LMM_LOCAL_DETACH_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_LMM_LOCAL_DETACH_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MMC_SndMmLmmLocalDetachInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* 消息IE项赋值 */
    PS_MEM_CPY(pstMsg, pstDetachInd, sizeof(MMCMM_LMM_LOCAL_DETACH_IND_STRU));

    /* 修改消息头 */
    pstMsg->ulLength        = sizeof(MMCMM_LMM_LOCAL_DETACH_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->ulMsgId         = MMCMM_LMM_LOCAL_DETACH_IND;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMmLmmMoDetachInd
 功能描述  : MMC向MM通知当前LMM的UE去注册结果
 输入参数  : LMM_MMC_DETACH_CNF_STRU            *pstDetachCnf
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月5日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_MMC_SndMmLmmMoDetachInd(
    LMM_MMC_DETACH_CNF_STRU            *pstDetachCnf
)
{
    MMCMM_LMM_MO_DETACH_IND_STRU       *pstMsg = VOS_NULL_PTR;

    /* 申请消息内存分配 */
    pstMsg              = (MMCMM_LMM_MO_DETACH_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_LMM_MO_DETACH_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MMC_SndMmLmmMoDetachInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* 消息IE项赋值 */
    PS_MEM_CPY(pstMsg, pstDetachCnf, sizeof(MMCMM_LMM_MO_DETACH_IND_STRU));

    /* 修改消息头 */
    pstMsg->ulLength        = sizeof(MMCMM_LMM_MO_DETACH_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->ulMsgId         = MMCMM_LMM_MO_DETACH_IND;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndMmLmmTimerStateNotify
 功能描述  : MMC向MM通知当前LMM的定时器状态
 输入参数  : pstTimerStatusNotify - 消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月20日
   作    者   : z00161729
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_MMC_SndMmLmmTimerStateNotify(
    LMM_MMC_TIMER_STATE_NOTIFY_STRU    *pstTimerStatusNotify
)
{
    MMCMM_LMM_TIMER_STATE_NOTIFY_STRU  *pstMsg = VOS_NULL_PTR;

    /* 申请消息内存分配 */
    pstMsg              = (MMCMM_LMM_TIMER_STATE_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_LMM_TIMER_STATE_NOTIFY_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMmLmmTimerStatusNotify,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* 消息IE项赋值 */
    PS_MEM_CPY(pstMsg, pstTimerStatusNotify, sizeof(MMCMM_LMM_TIMER_STATE_NOTIFY_STRU));

    /* 修改消息头 */
    pstMsg->ulLength        = sizeof(MMCMM_LMM_TIMER_STATE_NOTIFY_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->ulMsgId         = MMCMM_LMM_TIMER_STATE_NOTIFY;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMmSrvccInfoNotify
 功能描述  : 向MM发送SRVCC通知消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年11月26日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndMmSrvccInfoNotify(VOS_VOID)
{
    MMCMM_SRVCC_INFO_NOTIFY_STRU       *pstSndMmSrvccMsg      = VOS_NULL_PTR;

    pstSndMmSrvccMsg  = (MMCMM_SRVCC_INFO_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_REL_REQ_STRU));
    if ( VOS_NULL_PTR == pstSndMmSrvccMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMmSrvccInfoNotify,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstSndMmSrvccMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMmSrvccMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMmSrvccMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMmSrvccMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;

    /* 填写消息类别 */
    pstSndMmSrvccMsg->MsgHeader.ulMsgName         = MMCMM_SRVCC_INFO_NOTIFY;
    pstSndMmSrvccMsg->MsgHeader.ulLength          = sizeof(MMCMM_SRVCC_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstSndMmSrvccMsg);
    return;
}



/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

