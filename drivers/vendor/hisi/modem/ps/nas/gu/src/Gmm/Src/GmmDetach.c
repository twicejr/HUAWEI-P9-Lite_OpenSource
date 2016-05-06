/*******************************************************************************
  Copyright     : 2005-2007, Huawei Tech. Co., Ltd.
  File name     : GmmDetach.c
  Description   : GMM DETACH功能相关处理用源文件
  Function List :
    01.   Gmm_RcvMmcDetachReq
    02.   Gmm_SimRemoveDetach
    03.   Gmm_RcvMmcDetachReq_RegNoCell
    04.   Gmm_MsInitNormalDetach
    05.   Gmm_Com_MsInitNormalDetach
    06.   Gmm_RcvMmcPowerOffReq
    07.   Gmm_PowerOffDetach
    08.   Gmm_DetachRequestMsgMake
    09.   Gmm_RcvDetachRequestMsg
    10.   Gmm_RcvDetachRequestMsg_RegInit
    11.   Gmm_RcvDetachRequestMsg_DeregInit
    12.   Gmm_RcvDetachRequestMsg_RauInit
    13.   Gmm_RcvDetachRequestMsg_ServReqInit
    14.   Gmm_RcvDetachRequestMsg_RegNmlServ
    15.   Gmm_RcvDetachRequestMsg_RegAtmpToUpdtMm
    16.   Gmm_RcvDetachRequestMsg_RegImsiDtchInit
    17.   Gmm_NetInitNotRequiredDetach
    18.   Gmm_Com_Cause2Detach
    19.   Gmm_Com_CauseDetach
    20.   Gmm_NetInitRequiredDetach
    21.   Gmm_NetInitImsiDetach
    22.   Gmm_DetachAcceptMsgMake
    23.   Gmm_RcvDetachAcceptMsg
    24.   Gmm_RcvDetachAcceptMsg_DeregInit
    25.   Gmm_RcvDetachAcceptMsg_RegImsiDtchInit
  History       :
    1.  张志勇  2003.12.09  新规作成
    2.  s46746  2006-03-08  根据问题单A32D02368修改
    3.  s46746  2006-03-09  根据问题单A32D02387修改
    4.  l40632  2006-04-17  根据问题单A32D03132修改
    5.  l40632  2006-04-28  根据问题单A32D03272修改
    6. x51137 2006/4/28 A32D02889
    7.  s46746  2006-06-16  根据问题单A32D03581修改
    8. 日    期   : 2006年9月9日
       作    者   : sunxibo id:46746
       修改内容   : 根据问题单号：A32D05604
    9.日    期   : 2006年11月06日
       作    者   : s46746
       修改内容   : 问题单号:A32D05787
    10.日    期   : 2006年11月9日
       作    者   : sunxibo id:46746
       修改内容   : 根据问题单号：A32D06822
    11.日    期   : 2006年11月20日
       作    者   : s46746
       修改内容   : 创建，根据问题单号：A32D07433
    12.日    期   : 2007年01月04日
       作    者   : s46746
       修改内容   : 创建，根据问题单号：A32D08235
    13.日    期   : 2007年12月12日
       作    者   : l00107747
       修改内容   : 根据问题单号：A32D13861
    14.日    期   : 2007年12月14日
       作    者   : s46746
       修改内容   : 问题单A32D13638，保证进行RAU之前不向网侧发送其它数据，并且RAU不成功，不恢复层2
    15.日    期   : 2007年12月28日
       作    者   : s46746
       修改内容   : 根据问题单号：A32D13954,修改GMM在2G3过程中缓存消息机制
    16.日    期   : 2008年7月2日
       作    者   : l00107747
       修改内容   : 根据问题单号：AT2D03900,FOLLOW ON标志清除排查
    17.日    期   : 2008年9月23日
       作    者   : o00132663
       修改内容   : 根据问题单号：AT2D05839,清除无用全局变量 ucRlsMsgFlg和状态GMM_REGISTERED_WAIT_FOR_RAU
    18.日    期   : 2009年01月20日
       作    者   : l00130025
       修改内容   : 问题单号:AT2D08378,当服务域改变时,MM/GMM没有对UE的mode进行改变;GMM在RAU过程中收到Detach请求时,直接返回,没有处理
    19.日    期   : 2009年05月25日
       作    者   : h44270
       修改内容   : 问题单号:AT2D09923/AT2D12099,发送attach请求，所带的tlli有问题
    20.日    期   : 2009年08月14日
       作    者   : l60609
       修改内容   : 问题单号:AT2D13779,IMSI DETACH上报事件不合理
    21.日    期   : 2009年08月19日
       作    者   : x00115505
       修改内容   : 问题单号:AT2D13855,Combined Attach过程中通过SYSCFG设置仅支持PS域，设置失败
    22.日    期   : 2009年08月24日
       作    者   : x00115505
       修改内容   : AT2D14023,测试GCF用例44.2.2.1.9失败
*******************************************************************************/

#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasComm.h"
#include "GmmCasSend.h"
#include "GmmCasGsm.h"
#include "NasCommDef.h"
#include "GmmCasSuspend.h"

#include "NasUtranCtrlInterface.h"

#include "NasUsimmApi.h"



#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:luojian 107747;检视人:sunshaohua65952;原因:LOG方案设计需要*/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_DETACH_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/

/*lint -save -e958 */


/*****************************************************************************
 函 数 名  : NAS_GMM_SaveDetachMsg
 功能描述  : 缓冲detach消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月10日
    作    者   : l65478
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_SaveDetachMsg(VOS_VOID *pMsg)
{
    MMCGMM_DETACH_REQ_STRU      *pDetachMsg = VOS_NULL_PTR;

    /* 已经有缓冲的detach消息时,以最后一个detach消息为准
       此处不考虑detach类型不同的情况 */
    if ((VOS_NULL_PTR != g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach)
     && (GMM_MSG_HOLD_FOR_DETACH == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH)))
    {
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;
    }

    pDetachMsg = (MMCGMM_DETACH_REQ_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_DETACH_REQ_STRU));
    if (VOS_NULL_PTR == pDetachMsg)
    {
          PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_GMM_SaveDetachMsg:ERROR: Allocate memory error in Gmm_RcvMmcDetachReq");
          return;
    }
    Gmm_MemCpy(pDetachMsg, pMsg, sizeof(MMCGMM_DETACH_REQ_STRU));
    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach = (VOS_UINT32)pDetachMsg;
    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_DETACH;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_DeleteSavedDetachMsg
 功能描述  : 删除缓冲的detach消息
 输入参数  : ulDelDetachType        - 删除的DETACH类型
 输出参数  : 无
 返 回 值  : VOS_TRUE               - 删除成功
             VOS_FALSE              - 未进行删除
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月13日
    作    者   : w00167002
    修改内容   : 新生成函数
                 注:在网络模式I下，GMM缓存的可能是CS+PS两个域的detach消息。GMM和
                 MM同时启动去注册保护定时器，且CS域超时时长比PS域长1秒。
                 如果此时CS域超时，那么PS域信息也可以被清除；
                 如果此时PS域超时，那么CS和PS域信息都可以被清除；
*****************************************************************************/
VOS_UINT32 NAS_GMM_DeleteSavedDetachMsg(
    NAS_GMM_DETACH_TYPE_ENUM_UINT32     ulDelDetachType
)
{
    MMCGMM_DETACH_REQ_STRU             *pstMsDetach = VOS_NULL_PTR;
    NAS_GMM_DETACH_TYPE_ENUM_UINT32     ulGmmDetach;

    if ( ( GMM_MSG_HOLD_FOR_DETACH == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH) )
      && ((VOS_NULL_PTR            != g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach)) )
    {
         pstMsDetach = (MMCGMM_DETACH_REQ_STRU *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach;

         /* 获取缓存的DETACH类型 */
         ulGmmDetach = pstMsDetach->enDetachType;

          /* 如果缓存的需要删除域的DETACH,则清除缓存的Detach消息 */
        if ( ulDelDetachType == (ulGmmDetach & ulDelDetachType) )
        {
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;   /* 清除缓存标志                             */
            Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach = VOS_NULL_PTR;
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMmcGmmDetachReqMsg_GmmRegisteredInitiated
 功能描述  : GMM在GMM_REGISTERED_INITIATED状态收到DETACH REQ的处理
 输入参数  : pMsg        - DETACH REQ 消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月17日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcGmmDetachReqMsg_GmmRegisteredInitiated(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT32                          ulDetachType;                                  /* 定义detach类型                           */
    MMCGMM_DETACH_REQ_STRU             *pMsDetach       = VOS_NULL_PTR;                                     /* 定义指针                                 */

    pMsDetach    = (MMCGMM_DETACH_REQ_STRU *)pMsg;                              /* 初始化指针                               */
    ulDetachType = pMsDetach->enDetachType;

    /* 正在建链过程中，则缓存去注册消息 */
    if ( (GMM_FALSE                 == g_GmmGlobalCtrl.ucSigConFlg)
      && (GMM_RRC_RRMM_EST_CNF_FLG  == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)) )
    {                                                                       /* 无信令且正在建立信令连接                 */
        /* 缓存DETACH消息时候需要释放先前已缓存的DETACH消息，否则会导致内存泄露 */
        NAS_GMM_SaveDetachMsg(pMsg);

        return;                                                       /* 返回                                     */
    }

    /* 在联合注册过程中，则缓存消息,在联合注册过程结束后再处理 */
    if ( (GMM_ATTACH_COMBINED            == g_GmmGlobalCtrl.ucSpecProc)
      || (GMM_ATTACH_WHILE_IMSI_ATTACHED == g_GmmGlobalCtrl.ucSpecProc) )
    {
        if (MMC_GMM_PS_CS_DETACH != ulDetachType)
        {
            /* 在进行联合注册过程中,缓存消息,在联合注册过程结束后再处理 */
            NAS_GMM_SaveDetachMsg(pMsg);

            return;
        }
    }

    /* 网络模式I,如果当前CS域已处于DETACH状态，并且当前是CS与PS域的DETACH，则只进行PS ONLY DETACH */
    ulDetachType = NAS_GMM_ConvertDetachType(ulDetachType);

    Gmm_TimerStop(GMM_TIMER_T3310);                                             /* 停T3310                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */
    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                                  /* 清除followon标志                         */
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
    {                                                                           /* ATTACH过程是由SM触发的                   */
        Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_PS_DETACH);      /* 通知SM GMM注册失败                       */
        g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                                 /* 清ucSmCnfFlg标志                         */
    }

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask
        & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* 等待鉴权响应                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护定时器                             */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;     /* 清除原语等待标志                         */
    }

    if (MMC_GMM_CS_DETACH != ulDetachType)
    {
        NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );                               /* 设置禁止注册标志                         */
    }

    Gmm_MsInitNormalDetach(ulDetachType);

    return;

}


/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMmcGmmDetachReqMsg_GmmServiceReqInitiated
 功能描述  : GMM在GmmServiceReqInitiated状态收到DETACH REQ消息的处理
 输入参数  : pMsg        - DETACH REQ 消息
 输出参数  : 无
 返 回 值  : VOS_TRUE               - 进行DETACH消息的处理
             VOS_FALSE              - 未进行DETACH消息的处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月17日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcGmmDetachReqMsg_GmmServiceReqInitiated(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT32                          ulDetachType;                                  /* 定义detach类型                           */
    MMCGMM_DETACH_REQ_STRU             *pMsDetach       = VOS_NULL_PTR;                                     /* 定义指针                                 */

    pMsDetach    = (MMCGMM_DETACH_REQ_STRU *)pMsg;                              /* 初始化指针                               */
    ulDetachType = pMsDetach->enDetachType;

    /* 正在建链过程中，则缓存去注册消息 */
    if ( (GMM_FALSE                 == g_GmmGlobalCtrl.ucSigConFlg)
      && (GMM_RRC_RRMM_EST_CNF_FLG  == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)) )
    {                                                                       /* 无信令且正在建立信令连接                 */
        /* 缓存DETACH消息时候需要释放先前已缓存的DETACH消息，否则会导致内存泄露 */
        NAS_GMM_SaveDetachMsg(pMsg);

        return;                                                       /* 返回                                     */
    }

    Gmm_TimerStop(GMM_TIMER_T3317);                                             /* 停T3317                                  */
    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* 停止T3302                                */
    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* 停止T3311                                */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask
        & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* 等待鉴权响应                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护定时器                             */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;     /* 清除原语等待标志                         */
    }

    if ((GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProc)
        ||(GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* SR类型为data                             */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* 向RABM发送结果                           */
    }
    if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
    {
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                              /* 发送PMMSMS_ERROR_IND                     */
        g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
    }
    if (GMM_MSG_HOLD_FOR_SM
        ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvMmcGmmDetachReqMsg_GmmServiceReqInitiated(): Clear cached SM Data Req");

        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;
    }

    /* 进行DETACH类型的转换 */
    ulDetachType = NAS_GMM_ConvertDetachType(ulDetachType);

    Gmm_MsInitNormalDetach(ulDetachType);                                       /* 调用MS启动的detach处理                   */

    return;

}

/*****************************************************************************
 函 数 名  : NAS_GMM_LocalDetach_GmmDeregisteredNoImsi
 功能描述  : GMM处于GmmDeregisteredNoImsi状态时，做本地DETACH操作
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月19日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_LocalDetach_GmmDeregisteredNoImsi(VOS_VOID)
{
    NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );     /* 设置禁止注册标志                         */

    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }

    /* 向MMC发送PS注册结果 */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_LocalDetach_GmmDeregisteredNormalService
 功能描述  : GMM处于GmmDeregisteredNormalService状态时，做本地DETACH操作
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月19日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2013年8月7日
    作    者   : w00167002
    修改内容   : DTS2013080207367:在CS only时候，用户发起PDP激活，网络模式I时候，
                 会触发联合注册.用户发起PDP去激活，会导致PS域的去注册。收到网侧
                 的去注册成功后需要通知MM，否则MM当前在NORMAL SERVICE状态，不
                 触发T3212定时器的启动，长时间可能导致丢寻呼.
*****************************************************************************/
VOS_VOID NAS_GMM_LocalDetach_GmmDeregisteredNormalService(VOS_VOID)
{
    NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );     /* 设置禁止注册标志                         */

    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else
    {
        /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
        NAS_GMM_SndMmGprsDetachComplete();
    }

    /* 向MMC发送PS注册结果 */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_LocalDetach_GmmDeregisteredAttemptingToAttach
 功能描述  : GMM处于GmmDeregisteredAttemptingToAttach状态时，做本地DETACH操作
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月19日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_LocalDetach_GmmDeregisteredAttemptingToAttach(VOS_VOID)
{
    /* 通知MM模块 */
    if ((VOS_TRUE      == NAS_MML_GetCsAttachAllowFlg())
     && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod) )
    {
        NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);
    }

    /* GMM进行本地DEACH */
    NAS_GMM_GprsLocalDetach();

    /* 迁移状态 */
    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                             /* 调用状态的公共处理                       */

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_LocalDetach_GmmDeregisteredInitiated
 功能描述  : GMM处于GmmDeregisteredInitiated状态时，做本地DETACH操作
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月19日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_LocalDetach_GmmDeregisteredInitiated(VOS_VOID)
{
    /* 如果当前PS域已经去注册了，并且存在P-TMSI signature,则清除P-TMSI signature */
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
        {
            /* Upon completion of an MS initiated detach procedure, the used P-TMSI signature shall be deleted */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;

            NAS_MML_InitUeIdPtmsiSignatureInvalid();
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
        }
    }

    /* GMM本地去注册 */
    NAS_GMM_GprsLocalDetach();

    /* 迁移状态 */
    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_LocalDetach_GmmRauInitiated
 功能描述  : GMM处于GmmRauInitiated状态时，做本地DETACH操作
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月19日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_LocalDetach_GmmRauInitiated(VOS_VOID)
{
    if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
    {
        GMM_RauFailureInterSys();
    }
    else
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
    }

    Gmm_ComCnfHandle();

    /* GMM本地去注册 */
    NAS_GMM_GprsLocalDetach();

    /* 迁移状态 */
    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

    return;
}




/*****************************************************************************
 函 数 名  : NAS_GMM_StartDetachProtectingTimer
 功能描述  : 启动GMM的Detach消息的保护定时器
 输入参数  : MMCGMM_DETACH_REQ_STRU             *pstMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : w00167002
    修改内容   : 新生成函数

  2.日    期   : 2015年4月11日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
VOS_VOID NAS_GMM_StartDetachProtectingTimer(
    MMCGMM_DETACH_REQ_STRU             *pstMsg
)
{
    /* Detach流程保护定时器时长 */
    VOS_UINT32                          ulDetachTimerVal;

    MMC_GMM_DETACH_TYPE_ENUM_UINT32     enDetachType;

    /* GMM的PS域Detach保护定时器运行状态 */
    VOS_UINT32                          ulPsDetachTimerStatus;

    if (MMC_GMM_DETACH_CAUSE_USER_DETACH == pstMsg->enDetachReason)
    {
        /* 用户触发的DETACH的时长: 90s */
        ulDetachTimerVal  = GMM_TIMER_PROTECT_DETACH_NOT_BY_SYSCFG_VALUE;
    }
    else
    {
        /* 如果当前是SYSCFG或服务域变化触发的DETACH,则设置保护定时器的时长为15s */
        ulDetachTimerVal  = GMM_TIMER_PROTECT_DETACH_BY_SYSCFG_VALUE;
    }


    /* 获取GMM的Detach保护定时器运行状态 */
    ulPsDetachTimerStatus = NAS_GMM_QryTimerStatus(GMM_TIMER_PROTECT_PS_DETACH);

    /* 默认当前启动的PS域DETACH */
    enDetachType         = MMC_GMM_PS_DETACH;

    enDetachType         = pstMsg->enDetachType;

    /* 如果当前不需要PS域的DETACH，则直接返回 */
    if ( MMC_GMM_PS_DETACH != (enDetachType & MMC_GMM_PS_DETACH) )
    {
        return;
    }

    /* 否则用户执行的是PS域DETACH,如果GMM的PS域Detach保护定时器未在运行，则启动PS域Detach保护定时器 */
    if ( VOS_FALSE         == ulPsDetachTimerStatus )
    {
        /* 设置GMM的CS域Detach保护定时器时长 */
        g_GmmTimerMng.aTimerInf[GMM_TIMER_PROTECT_PS_DETACH].ulTimerVal = ulDetachTimerVal;

        /* 启动GMM的PS域detach保护定时器 */
        Gmm_TimerStart(GMM_TIMER_PROTECT_PS_DETACH);
    }

    return;
}



/*****************************************************************************
 函 数 名  : NAS_GMM_LocalDetach_GprsSuspension
 功能描述  : GMM处于GPRS_SUSPENSION状态时，做本地DETACH操作
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 20013年02月19日
    作    者   : l00167671
    修改内容   : 新生成函数
  2.日    期   : 2013年8月7日
    作    者   : w00167002
    修改内容   : DTS2013080207367:在CS only时候，用户发起PDP激活，网络模式I时候，
                 会触发联合注册.用户发起PDP去激活，会导致PS域的去注册。收到网侧
                 的去注册成功后需要通知MM，否则MM当前在NORMAL SERVICE状态，不
                 触发T3212定时器的启动，长时间可能导致丢寻呼.
  3.日    期   : 2014年3月12日
    作    者   : f00261442
    修改内容   : DTS2014031103926:在本地DETACH的时候通知SM
*****************************************************************************/
VOS_VOID NAS_GMM_LocalDetach_GprsSuspension(VOS_VOID)
{
    /* 设置禁止注册标志                         */
    NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );

    if (GMM_REGISTERED_NO_CELL_AVAILABLE == gstGmmSuspendCtrl.ucPreState)
    {
        gstGmmSuspendCtrl.ucPreState = GMM_DEREGISTERED_NO_CELL_AVAILABLE;
    }
    else if (GMM_DEREGISTERED_NO_IMSI != gstGmmSuspendCtrl.ucPreState)
    {
        gstGmmSuspendCtrl.ucPreState = GMM_DEREGISTERED_NORMAL_SERVICE;
    }
    else
    {

    }

    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else
    {
        /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
        NAS_GMM_SndMmGprsDetachComplete();
    }

    /* 向MMC发送PS注册结果 */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    NAS_GMM_SndSmStatusInd(GMM_SM_STATUS_DETACHED, GMM_SM_CAUSE_PS_DETACH);

    NAS_GMM_ClearMsgFromBuff(MMCGMM_ATTACH_REQ,WUEPS_PID_MMC,WUEPS_PID_GMM);
}

/*****************************************************************************
 函 数 名  : NAS_GMM_GprsLocalDetachRelCsPsAllConn
 功能描述  : GMM做本地DETACH时如果存在连接的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月21日
    作    者   : z00161729
    修改内容   : DTS2014032105704:国内TDS丢网瞬间找回原小区ps迁移modem1后不再回迁modem0
*****************************************************************************/
VOS_VOID NAS_GMM_GprsLocalDetachRelCsPsAllConn(VOS_VOID)
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetRatType;

    enUtranMode         = NAS_UTRANCTRL_GetCurrUtranMode();
    enCurNetRatType     = NAS_MML_GetCurrNetRatType();

    /* W下存在信令，则通知接入层进行链接释放 */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == enCurNetRatType )
     && ((GMM_TRUE                  == g_GmmGlobalCtrl.ucSigConFlg)
      || (GMM_RRC_RRMM_EST_CNF_FLG  == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))))

    {
        /* SVLTE特性TDD模式使用新增原语通知tds连接释放 */
        if ((VOS_TRUE == NAS_MML_GetSvlteSupportFlag())
         && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enUtranMode))
        {
            NAS_GMM_SndRrmmRelCsPsAllConnReq();
            return;
        }

        /* 非svlte场景使用rrmm_rel_req通知接入层连接释放 */
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_GprsLocalDetach
 功能描述  : GMM做本地DETACH的基本处理操作，不进行状态迁移
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月13日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2013年8月7日
    作    者   : w00167002
    修改内容   : DTS2013080207367:在CS only时候，用户发起PDP激活，网络模式I时候，
                 会触发联合注册.用户发起PDP去激活，会导致PS域的去注册。收到网侧
                 的去注册成功后需要通知MM，否则MM当前在NORMAL SERVICE状态，不
                 触发T3212定时器的启动，长时间可能导致丢寻呼.
  3.日    期   : 2014年3月21日
    作    者   : z00161729
    修改内容   : DTS2014032105704:国内TDS丢网瞬间找回原小区ps迁移modem1后不再回迁modem0
*****************************************************************************/
VOS_VOID NAS_GMM_GprsLocalDetach(VOS_VOID)
{

    NAS_GMM_GprsLocalDetachRelCsPsAllConn();

#if (FEATURE_LTE == FEATURE_ON)
    if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
    {
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
    }
#endif

    /* GMM停止保护定时器 */
    Gmm_TimerStop(GMM_TIMER_ALL);

    /* 设置禁止注册标志 */
    NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);

    /* 清除缓存的服务标志 */
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    /* 清除followon标志 */
    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;

    /* 清当前流程 */
    g_GmmGlobalCtrl.ucSpecProc    = GMM_NULL_PROCEDURE;

    /* G下清除层2相关数据 */
    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ALL);
    }

    /* 如果正在鉴权，则清除等待标志 */
    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;
    }

    /* 清除缓存的ATTACH标志 */
    NAS_GMM_ClearMsgFromBuff(MMCGMM_ATTACH_REQ, WUEPS_PID_MMC, WUEPS_PID_GMM);

    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else
    {
        /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
        NAS_GMM_SndMmGprsDetachComplete();
    }

    /* 向MMC发送PS注册结果 */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);


    /* 挂起用户面，保证数据不再下发 */
    NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_BUTT,
                                VOS_FALSE,
                                VOS_TRUE,
                                VOS_FALSE);

}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsNeedProcUserCsDetach
 功能描述  : 用来判别是否由GMM来处理用户发起的CS/CS+PS的detach
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_FALSE          -- 不需要GMM进行处理用户发起的CS/CS+PS的detach
             VOS_TRUE           -- 需要GMM进行处理用户发起的CS/CS+PS的detach
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月19日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedProcUserCsDetach(VOS_VOID)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo       = VOS_NULL_PTR;
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo    = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    /* 获取当前网络模式 */
    pstCampInfo       = NAS_MML_GetCurrCampPlmnInfo();

    /* 获取当前的网络信息 */
    pstNetWorkInfo    =  NAS_MML_GetNetworkInfo();

    ulRet             = VOS_FALSE;


    /* 非网络模式I下，不用GMM处理用户发起的detach */
    if ( NAS_MML_NET_MODE_I != pstCampInfo->enNetworkMode )
    {
        return VOS_FALSE;
    }

    /* PS域不准许注册，不用GMM处理用户发起的detach */
    if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
    {
        return VOS_FALSE;
    }

    /* PS域注册首限，不用GMM处理用户发起的detach */
    if ( VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg() )
    {
        return VOS_FALSE;
    }

    /* PS 卡无效，不用GMM处理用户发起的detach */
    if ( VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }

    /* 当前小区是否支持GPRS */
    if ( VOS_FALSE == pstNetWorkInfo->stPsDomainInfo.ucPsSupportFlg )
    {
        return VOS_FALSE;
    }

    /* 当前小区是否在FORB GPRS PLMN里面 */

    ulRet = NAS_MML_IsSimPlmnIdInDestBcchPlmnList( &(pstCampInfo->stLai.stPlmnId),
                                           pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                           pstForbidPlmnInfo->astForbGprsPlmnList );
    if ( VOS_TRUE == ulRet )
    {
        return VOS_FALSE;
    }

    /* MM已处于ATTACHED状态，但当前GS接口不存在 */
    if ( (VOS_FALSE          == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
      && (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState) )
    {
        return VOS_FALSE;
    }

    /* 否则用户发起的CS域的DETACH，可由GMM进行处理 */
    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_GMM_ConvertDetachType
 功能描述  : 用来转换去注册类型
 输入参数  : enDetachType                    -- 转换前的去注册类型
 输出参数  : 无
 返 回 值  : NAS_GMM_DETACH_TYPE_ENUM_UINT32 -- 转换后的去注册类型
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月19日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
NAS_GMM_DETACH_TYPE_ENUM_UINT32 NAS_GMM_ConvertDetachType(
    NAS_GMM_DETACH_TYPE_ENUM_UINT32     ulDetachType
)
{
    if (MMC_GMM_PS_CS_DETACH == ulDetachType)
    {                                                                           /* 是combined detach                        */
        if ( GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod )
        {                                                                       /* 当前是非A+I                              */
            return MMC_GMM_PS_DETACH;
        }

        if ( (MM_STATUS_DETACHED             == g_MmSubLyrShare.MmShare.ucCsAttachState)
          && (GMM_ATTACH_COMBINED            != g_GmmGlobalCtrl.ucSpecProc)
          && (GMM_ATTACH_WHILE_IMSI_ATTACHED != g_GmmGlobalCtrl.ucSpecProc) )
        {
            return MMC_GMM_PS_DETACH;                                           /* GMM只执行PS域的detach                    */
        }

        return MMC_GMM_PS_CS_DETACH;
    }

    /* 其它去注册类型保持不变 */
    return ulDetachType;

}



/*****************************************************************************
 函 数 名  : NAS_Gmm_RcvMmCsLocalDetachInd_RegImsiDtchInit
 功能描述  : GMM在GMM_REGISTERED_IMSI_DETACH_INITIATED状态收到MM的
             MMGMM_CS_LOCAL_DETACH_IND消息的处理
 输入参数  : MMCGMM_DETACH_REQ_STRU             *pstMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_Gmm_RcvMmCsLocalDetachInd_RegImsiDtchInit(VOS_VOID)
{
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* 等待鉴权响应                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护定时器                             */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;     /* 清除原语等待标志                         */
    }

    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);                               /* 调用状态的公共处理                       */
    g_GmmDetachCtrl.ucT3321OutCnt = 0;                                          /* T3321溢出次数清0                         */

    if (GMM_UEID_P_TMSI_SIGNATURE
        == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
        & GMM_UEID_P_TMSI_SIGNATURE))
    {                                                                           /* DETACH成功且使用了P_TMSI_SIGNATURE       */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
            &= ~GMM_UEID_P_TMSI_SIGNATURE;                                      /* 清除P_TMSI_SIGNATURE                     */

        NAS_MML_InitUeIdPtmsiSignatureInvalid();
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
    }

    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        g_GmmGlobalCtrl.stDetachInfo.enDetachType &= ~GMM_WAIT_CS_DETACH;
    }

    return;                                                                     /* 返回                                     */
}


/*****************************************************************************
 函 数 名  : NAS_Gmm_RcvMmCsLocalDetachInd_RegImsiDtchInit
 功能描述  : GMM在GMM_REGISTERED_IMSI_DETACH_INITIATED状态收到MM的
             MMGMM_CS_LOCAL_DETACH_IND消息的处理
 输入参数  : MMCGMM_DETACH_REQ_STRU             *pstMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : w00167002
    修改内容   : 新生成函数
                联合RAU过程中，CS域的DETACH消息是被缓存的，如果这个时候CS域
                定时器已经超时了，那么则释放当前的联合注册流程，待收到REL IND消息
                后，等定时器超时再触发RAU:Gmm_RcvRrmmRelInd_RauInit

*****************************************************************************/
VOS_VOID NAS_Gmm_RcvMmCsLocalDetachInd_RegInit(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;                           /* 当前的网络接入技术 */

    enCurRat = NAS_MML_GetCurrNetRatType();

    /* 当前处在联合RAU/attach过程中 */
    if ( (GMM_ATTACH_COMBINED            != g_GmmGlobalCtrl.ucSpecProc)
      && (GMM_ATTACH_WHILE_IMSI_ATTACHED != g_GmmGlobalCtrl.ucSpecProc) )
    {
        return ;
    }

    /* W下存在信令，则通知接入层进行链接释放 */
    if ( ( NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat )
      && ( (GMM_TRUE                  == g_GmmGlobalCtrl.ucSigConFlg)
        || (GMM_RRC_RRMM_EST_CNF_FLG  == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)) ) )
    {
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);

    }

    return;                                                                     /* 返回                                     */
}



/*****************************************************************************
 函 数 名  : NAS_Gmm_RcvMmCsLocalDetachInd_RegImsiDtchInit
 功能描述  : GMM在GMM_REGISTERED_IMSI_DETACH_INITIATED状态收到MM的
             MMGMM_CS_LOCAL_DETACH_IND消息的处理
 输入参数  : MMCGMM_DETACH_REQ_STRU             *pstMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : w00167002
    修改内容   : 新生成函数
                联合RAU过程中，CS域的DETACH消息是被缓存的，如果这个时候CS域
                定时器已经超时了，那么则释放当前的联合注册流程，待收到REL IND消息
                后，等定时器超时再触发RAU:Gmm_RcvRrmmRelInd_RauInit

*****************************************************************************/
VOS_VOID NAS_Gmm_RcvMmCsLocalDetachInd_RauInit(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;                           /* 当前的网络接入技术 */

    enCurRat = NAS_MML_GetCurrNetRatType();

    /* 当前处在联合RAU/attach过程中 */
    if ( (GMM_RAU_COMBINED            != g_GmmGlobalCtrl.ucSpecProc)
      && (GMM_RAU_WITH_IMSI_ATTACH    != g_GmmGlobalCtrl.ucSpecProc) )
    {
        return ;
    }

    /* W下存在信令，则通知接入层进行链接释放 */
    if ( ( NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat )
      && ( (GMM_TRUE                  == g_GmmGlobalCtrl.ucSigConFlg)
        || (GMM_RRC_RRMM_EST_CNF_FLG  == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)) )  )
    {
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
    }

    return;                                                                     /* 返回                                     */
}


#if (FEATURE_MULTI_MODEM == FEATURE_ON)
/*****************************************************************************
 函 数 名  : NAS_GMM_GprsLocalDetach_SvltePsTransfer
 功能描述  : svlte ps transfer场景本地detach的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年11月25日
   作    者   : z00161729
   修改内容   : SVLTE优化G-TL ps切换性能修改

*****************************************************************************/
VOS_VOID NAS_GMM_GprsLocalDetach_SvltePsTransfer(VOS_VOID)
{
    switch (g_GmmGlobalCtrl.ucState)
    {
        case GMM_REGISTERED_INITIATED:
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        case GMM_SERVICE_REQUEST_INITIATED:
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);
            NAS_GMM_GprsLocalDetach();
            break;

        case GMM_REGISTERED_NORMAL_SERVICE:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
            NAS_GMM_GprsLocalDetach();
            break;

        case GMM_REGISTERED_PLMN_SEARCH:

            /* GMM进行本地DEACH */
            NAS_GMM_GprsLocalDetach();
            Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);
            break;

        case GMM_REGISTERED_NO_CELL_AVAILABLE:

            /* GMM进行本地DEACH */
            NAS_GMM_GprsLocalDetach();
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);
            break;

        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:

            NAS_GMM_LocalDetach_GmmDeregisteredAttemptingToAttach();
            break;

        case GMM_REGISTERED_UPDATE_NEEDED:

            /* GMM进行本地DEACH */
            NAS_GMM_GprsLocalDetach();

            /* 迁移状态 */
            Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
            break;

        case GMM_REGISTERED_LIMITED_SERVICE:

            /* GMM进行本地DEACH */
            NAS_GMM_GprsLocalDetach();

            /* 迁移状态 */
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
            break;

        case GMM_DEREGISTERED_NORMAL_SERVICE:
        case GMM_DEREGISTERED_LIMITED_SERVICE:
        case GMM_DEREGISTERED_ATTACH_NEEDED:
        case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
        case GMM_DEREGISTERED_PLMN_SEARCH:

            /* GMM进行本地DEACH */
            NAS_GMM_LocalDetach_GmmDeregisteredNormalService();
            break;

        case GMM_DEREGISTERED_NO_IMSI:

            /* GMM进行本地DEACH */
            NAS_GMM_LocalDetach_GmmDeregisteredNoImsi();
            break;

        case GMM_SUSPENDED_NORMAL_SERVICE:
        case GMM_GPRS_SUSPENSION:
        case GMM_SUSPENDED_GPRS_SUSPENSION:

        /* 在GMM_SUSPENDED_WAIT_FOR_SYSINFO需增加进行本地Detach的处理 */
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            NAS_GMM_LocalDetach_GprsSuspension();
            break;

        /* 在Gmm_MsgDistribute_GMM_TC_ACTIVE状态已经处理 */
        case GMM_TC_ACTIVE:
            break;

        /* 在GMM_DEREGISTERED_INITIATED状态，收到PS域detach，则不处理 */
        case GMM_DEREGISTERED_INITIATED:

            return;

        default:
            NAS_GMM_GprsLocalDetach();

            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "WARNING: g_GmmGlobalCtrl.ucState is Abnormal");
            break;
    }


    /* 通知MM当前CS已本地去注册 */
    if ( (VOS_TRUE             == NAS_GMM_IsNeedProcUserCsDetach())
      && (GMM_WAIT_CS_DETACH   == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_CS_DETACH)) )
    {
        NAS_GMM_SndMmcMmDetachInfo();
        return;
    }

    return;
}
#endif



/*******************************************************************************
Module   : Gmm_RcvMmcDetachReq
Function : GMM收到MMCGMM_DETACH_REQ的分发处理
Input    : VOS_VOID      *pMsg;    当前处理的消息
Output   : 无
NOTE     : 无
Return   : 无
History  :
1. 张志勇  2003.12.08  新规作成

2.日    期   : 2008年7月2日
  作    者   : l00107747
  修改内容   : 根据问题单号：AT2D03900

3.日    期   : 2009年01月20日
  作    者   : l00130025
  修改内容   : 问题单号:AT2D08378,当服务域改变时,MM/GMM没有对UE的mode进行改变;GMM在RAU过程中收到Detach请求时,直接返回,没有处理

4.日    期   : 2010年1月16日
  作    者   : o00132663
  修改内容   : NAS R7协议升级，当T3340正在运行时，表明前面流程正在释放链路
               ，缓存当前Detach请求。
5.日    期   : 2011年3月2日
  作    者   : z00161729
  修改内容   : DTS2010071601574:RAU过程完成收到rau accept需要等待RABM或WRR回复后再发送RAU cmp消息期间,
               缓存detach请求,等RAU结束再发起
6.日    期   : 2011年7月14日
  作    者   : h44270
  修改内容   : V7R1 PhaseII阶段调整，注册结果简化
7.日    期   : 2011年07月13日
  作    者   : w00166186
   修改内容   : V7R1 PHASE II ATTACH/DETACH调整

8. 日    期   : 2012年1月12日
   作    者   : w00166186
   修改内容   : DTS2011122704039:开机搜网后CS注册被拒#12,PS注册被拒#14，在ON
                 PLMN状态，服务域被设置为不支持GMM需要将服务域不支持信息通知给MMC.
9.日    期   : 2012年01月12日
   作    者   : l65478
   修改内容   : 问题单号：DTS2012010602762:SYSCFG设置成支持CS ONLY后
                 PS仍然显示正常服务
10.日    期   : 2012年2月15日
   作    者   : w00166186
   修改内容   : CSFB&PPAC&ETWS&ISR 开发
11.日    期  : 2012年08月24日
   作    者  : m00217266
   修改内容  : 修改Gmm_SndSmEstablishCnf接口，添加原因值
12.日    期   : 20013年02月19日
   作    者   : l00167671
   修改内容   : DTS2013020607201
13.日    期   : 2013年1月22日
   作    者   : W00176964
   修改内容   : DTS2013012105162:OOS流程收到PS域detach需要进行本地detach
14.日    期   : 2013年6月6日
   作    者   : w00167002
   修改内容   : V9R1_SVLTE项目修改
                缓存DETACH消息时候需要释放先前已缓存的DETACH消息，否则会导致内存泄露

                2. GMM当前无法处理CS域DEACH,则通知MM当前CS已本地去注册
15.日    期   : 2013年12月8日
   作    者   : z00161729
   修改内容   : SVLTE优化G-TL ps切换性能修改
 16.日    期   : 2013年12月8日
    作    者   : z00161729
    修改内容   : DTS2014010202583:SVLTE优化G-TL ps切换性能修改
*******************************************************************************/
VOS_VOID Gmm_RcvMmcDetachReq(
                         VOS_VOID       *pMsg                                   /* 当前处理的消息                           */
                         )
{
    VOS_UINT32                   ulDetachType;                                  /* 定义detach类型                           */
    MMCGMM_DETACH_REQ_STRU      *pMsDetach;                                     /* 定义指针                                 */

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetRatType;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;
    VOS_UINT8                           ucPsLocalDetachFlag;

    enUtranMode         = NAS_UTRANCTRL_GetCurrUtranMode();
    enCurNetRatType     = NAS_MML_GetCurrNetRatType();
    ucPsLocalDetachFlag = NAS_MML_GetPsLocalDetachFlag();
#endif

    pMsDetach    = (MMCGMM_DETACH_REQ_STRU *)pMsg;                              /* 初始化指针                               */
    ulDetachType = pMsDetach->enDetachType;                                     /* 初始化detach类型                         */


    ulDetachType = NAS_GMM_ConvertDetachType(ulDetachType);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* svlte特性开启，且gmm收到mtc的rrc假丢网消息，modem0 ps要迁移到modem1时为了减少detach ps
       时间，直接进行本地ps detach不和网络交互 */
    if ((VOS_TRUE == NAS_MML_GetSvlteSupportFlag())
     && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enUtranMode)
     && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurNetRatType)
     && (VOS_TRUE == ucPsLocalDetachFlag)
     && (MMC_GMM_PS_DETACH == ulDetachType))
    {
        NAS_GMM_GprsLocalDetach_SvltePsTransfer();


        NAS_MML_SetPsLocalDetachFlag(VOS_FALSE);
        return;
    }
#endif

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 判断当前状态进行不同处理                 */
    case GMM_REGISTERED_INITIATED:                                              /* GMM-REGISTERED-INITIATED状态             */

        /* GMM在GMM_REGISTERED_INITIATED状态收到DETACH REQ的处理 */
        NAS_GMM_RcvMmcGmmDetachReqMsg_GmmRegisteredInitiated(pMsg);
        return;

    case GMM_ROUTING_AREA_UPDATING_INITIATED:

        /* 在RAU过程中收到detach请求,缓冲此消息,在RAU完成后再进行DETACH操作 */
        NAS_GMM_SaveDetachMsg(pMsg);
        return;

    case GMM_REGISTERED_IMSI_DETACH_INITIATED:

        /* 在IMSI DETACH过程中收到detach请求,如果新的DETACH请求不是IMSI请求,
           缓冲此消息,在RAU完成后再进行DETACH操作 */
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            NAS_GMM_SaveDetachMsg(pMsg);
        }
        return;

    case GMM_SERVICE_REQUEST_INITIATED:                                         /* GMM-SERVICE-REQUEST-INITIATED状态        */
        NAS_GMM_RcvMmcGmmDetachReqMsg_GmmServiceReqInitiated(pMsg);
        return;

    case GMM_REGISTERED_NORMAL_SERVICE:                                         /* GMM-REGISTERED.NORMAL-SERVIC状态         */
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:                                /* REGISTERED.ATTEMPTING-TO-UPDATE-MM状态   */
        NAS_GMM_ProcDetachReq_RegNmlServ(pMsDetach, ulDetachType);
        return;

    case GMM_REGISTERED_PLMN_SEARCH:                                            /* GMM-REGISTERED.PLMN-SEARCH状态           */
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            /* GMM进行本地DEACH */
            NAS_GMM_GprsLocalDetach();

            Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);
        }
        break;

    case GMM_REGISTERED_NO_CELL_AVAILABLE:                                      /* GMM-REGISTERED.NO-CELL-AVAILABLE状态     */
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            /* GMM进行本地DEACH */
            NAS_GMM_GprsLocalDetach();

            Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);
        }
        break;

    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:                                   /* GMM-REGISTERED.ATTEMPTING-TO-UPDATE状态  */
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            NAS_GMM_LocalDetach_GmmDeregisteredAttemptingToAttach();
        }
        break;

    case GMM_REGISTERED_UPDATE_NEEDED:
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            /* GMM进行本地DEACH */
            NAS_GMM_GprsLocalDetach();

            /* 迁移状态 */
            Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
        }
        break;

    case GMM_REGISTERED_LIMITED_SERVICE:
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            /* GMM进行本地DEACH */
            NAS_GMM_GprsLocalDetach();

            /* 迁移状态 */
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
        }
        break;

    case GMM_DEREGISTERED_NORMAL_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_PLMN_SEARCH:
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            /* GMM进行本地DEACH */
            NAS_GMM_LocalDetach_GmmDeregisteredNormalService();
        }

        break;

    case GMM_DEREGISTERED_NO_IMSI:
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            /* GMM进行本地DEACH */
            NAS_GMM_LocalDetach_GmmDeregisteredNoImsi();
        }

        break;

    case GMM_SUSPENDED_NORMAL_SERVICE:

    case GMM_GPRS_SUSPENSION:
    case GMM_SUSPENDED_GPRS_SUSPENSION:

    /* 在GMM_SUSPENDED_WAIT_FOR_SYSINFO需增加进行本地Detach的处理 */
    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:

        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            NAS_GMM_LocalDetach_GprsSuspension();
        }

        break;

    /* 在Gmm_MsgDistribute_GMM_TC_ACTIVE状态已经处理 */
    case GMM_TC_ACTIVE:
        break;

    /* 在GMM_DEREGISTERED_INITIATED状态，收到PS域detach，则不处理 */
    case GMM_DEREGISTERED_INITIATED:
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            return;
        }

        /* 统一处理CS域DETACH */
        break;

    default:
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            NAS_GMM_GprsLocalDetach();
        }

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcDetachReq:WARNING: g_GmmGlobalCtrl.ucState is Abnormal");
        break;
    }


    /* 通知MM当前CS已本地去注册 */
    if ( (VOS_TRUE             == NAS_GMM_IsNeedProcUserCsDetach())
      && (GMM_WAIT_CS_DETACH   == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_CS_DETACH)) )
    {
        NAS_GMM_SndMmcMmDetachInfo();
        return;
    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcDetachReq_RegNoCell
  Function : 在GMM_REGISTERED_NO_CELL_AVAILABLE状态下收到MMCGMM_DETACH_REQ的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.11  新规作成
    2.日    期   : 2009年05月25日
      作    者   : h44270
      修改内容   : 问题单号:AT2D09923/AT2D12099,发送attach请求，所带的tlli有问题
    3.日    期   : 2011年07月13日
      作    者   : w00166186
      修改内容   : V7R1 PHASE II ATTACH/DETACH调整
    4. 日    期   : 2012年1月12日
       作    者   : w00166186
       修改内容   : DTS2011122704039:开机搜网后CS注册被拒#12,PS注册被拒#14，在ON
                      PLMN状态，服务域被设置为不支持GMM需要将服务域不支持信息通知给MMC.
*******************************************************************************/
VOS_VOID Gmm_RcvMmcDetachReq_RegNoCell(VOS_VOID)
{
    Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);                          /* 调用状态的公共处理                       */
    NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );              /* 设置PS域attach禁止标志                   */
    gstGmmCasGlobalCtrl.ucTlliAssignFlg = GMM_FALSE;

    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }


    /* 向MMC发送PS注册结果 */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);
}

/*******************************************************************************
  Module   : Gmm_MsInitNormalDetach
  Function : MS启动的detach过程处理
  Input    : VOS_UINT32    ulDetachType    detach类型
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1. 张志勇  2003.12.08  新规作成

  2.日    期   : 2006年11月06日
    作    者   : s46746
    修改内容   : 问题单号:A32D05787

  3.日    期   : 2009年01月20日
    作    者   : l00130025
    修改内容   : 问题单号:AT2D08378,当服务域改变时,MM/GMM没有对UE的mode进行改变;
                 GMM在RAU过程中收到Detach请求时,直接返回,没有处理
  4.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  5.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
  6.日    期   : 2013年6月8日
    作    者   : w00167002
    修改内容   : V9R1_SVLTE:代码走读:卡无效时，MMC_GMM_PS_CS_DETACH走
                 GMM_DETACH_NORMAL类型的流程。
  7.日    期   : 2014年7月9日
    作    者   : w00242748
    修改内容   : DSDS III新特性
*******************************************************************************/
VOS_VOID Gmm_MsInitNormalDetach(
    VOS_UINT32                          ulDetachType                   /* detach类型                               */
)
{
    VOS_UINT8                           ucSimCsRegStatus;                       /* SIM卡CS域的注册结果导致的卡是否有效VOS_TRUE:CS域的卡有效,VOS_FALSE:CS域的卡无效*/

    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

    switch (ulDetachType)
    {                                                                           /* 判断detach类型进行不同处理               */
    case MMC_GMM_PS_CS_DETACH:                                                  /* combined detach                          */
        if((VOS_FALSE      == NAS_MML_GetCsRestrictRegisterFlg())
        && (VOS_TRUE       == ucSimCsRegStatus)
        && (GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod))
        {
            g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_COMBINED;                   /* 赋值当前spesific过程                     */
        }
        else
        {
            g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_NORMAL;
        }
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsInitNormalDetach:INFO: combined detach procedure started");

        GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_INITIATED);                    /* 状态迁移到GMM DEREGISTERED INITIATED     */

        NAS_GMM_SndMmGprsDetachInitiation();                                       /* 向MMC发送MMCGMM_GPRS_DETACH_INITIATION   */
        Gmm_Com_MsInitNormalDetach();                                           /* 调用MS启动的detach的公共处理             */


        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_MsInitNormalDetach:NORMAL: STATUS IS GMM_DEREGISTERED_INITIATED");

        g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;
        break;
    case MMC_GMM_PS_DETACH:                                                     /* GPRS detach                              */
        g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_NORMAL;                         /* 赋值当前spesific过程                     */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsInitNormalDetach:INFO: normal detach procedure start");

        GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_INITIATED);                    /* 状态迁移到GMM DEREGISTERED INITIATED     */

        Gmm_Com_MsInitNormalDetach();                                           /* 调用MS启动的detach的公共处理             */


        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_MsInitNormalDetach:NORMAL: STATUS IS GMM_DEREGISTERED_INITIATED");

        g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;
        break;
    case MMC_GMM_CS_DETACH:                                                     /* IMSI detach                              */
        if((VOS_FALSE == NAS_MML_GetCsRestrictRegisterFlg())
        && (GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod))
        {
            g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_WITH_IMSI;                      /* 赋值当前spesific过程                     */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsInitNormalDetach:INFO: IMSI detach procedure started");

            GMM_CasFsmStateChangeTo(GMM_REGISTERED_IMSI_DETACH_INITIATED);

            NAS_GMM_SndMmImsiDetachInitiation();                                       /* 向MMC发送MMCGMM_IMSI_DETACH_INITIATION   */
            Gmm_Com_MsInitNormalDetach();                                           /* 调用MS启动的detach的公共处理             */


            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_MsInitNormalDetach:NORMAL: STATUS IS GMM_REGISTERED_IMSI_DETACH_INITIATED");

            g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;
        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_MsInitNormalDetach:WARNING: Detach Type is Abnormal");
        break;
    }

    return;                                                                     /* 返回                                     */
}

/*****************************************************************************
 函 数 名  : NAS_GMM_ProcDetachReq_RegNmlServ
 功能描述  : 正常服务状态处理DETACH请求
 输入参数  : VOS_UINT32 ulOpID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数
  2.日    期   : 2013年02月01日
    作    者   : l65478
    修改内容   : DTS2013020104880

*****************************************************************************/
VOS_VOID NAS_GMM_ProcDetachReq_RegNmlServ(
    MMCGMM_DETACH_REQ_STRU             *pstDetachReq,
    VOS_UINT32                          ulDetachType                   /* detach类型                               */
)
{
    MMCGMM_DETACH_REQ_STRU              *pstBufDetach = VOS_NULL_PTR;

    if ((GMM_TIMER_T3340_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3340_FLG))
     || (VOS_TRUE == gstGmmCasGlobalCtrl.ucRauCmpFlg))
    {
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_DETACH;    /* 置原语缓存标志                           */
        pstBufDetach = (MMCGMM_DETACH_REQ_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_DETACH_REQ_STRU));
        if (VOS_NULL_PTR == pstBufDetach)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_GMM_ProcDetachReq_RegNmlServ:ERROR: Allocate memory error in Gmm_RcvMmcDetachReq");
              return;
        }

        Gmm_MemCpy(pstBufDetach, pstDetachReq, sizeof(MMCGMM_DETACH_REQ_STRU));
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach = (VOS_UINT32)pstBufDetach;       /* 缓存原语                                 */
    }
    else if ((gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_GetCurrNetRatType())
          && (GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
#if (FEATURE_ON == FEATURE_LTE)
          && (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_NET_RAT_TYPE_LTE)
#endif
          )
    {
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_DETACH;    /* 置原语缓存标志                           */
        pstBufDetach = (MMCGMM_DETACH_REQ_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_DETACH_REQ_STRU));
        if (VOS_NULL_PTR == pstBufDetach)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_GMM_ProcDetachReq_RegNmlServ:ERROR: Allocate memory error in Gmm_RcvMmcDetachReq");
              return;
        }
        Gmm_MemCpy(pstBufDetach, pstDetachReq, sizeof(MMCGMM_DETACH_REQ_STRU));
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach = (VOS_UINT32)pstBufDetach;       /* 缓存原语                                 */

        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

    else
    {
        Gmm_MsInitNormalDetach(ulDetachType);                                   /* 调用MS启动的detach处理                   */
    }
}

/*******************************************************************************
  Module   : Gmm_Com_MsInitNormalDetach
  Function : MS启动的detach过程的公共处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.08  新规作成
*******************************************************************************/
VOS_VOID Gmm_Com_MsInitNormalDetach(VOS_VOID)
{
    NAS_MSG_STRU    *pDetachRequest;                                            /* 定义指针                                 */

    pDetachRequest = Gmm_DetachRequestMsgMake();                                /* 调用detach request消息制作函数           */

    if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
    {                                                                           /* 当前有信令连接                           */
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachRequest);           /* 发送detach request消息                   */
        Gmm_TimerStart(GMM_TIMER_T3321);                                        /* 启动T3321                                */
    }
    else
    {                                                                           /* 当前没有有信令连接                       */
        Gmm_SndRrmmEstReq(RRC_EST_CAUSE_DETACH,
                          GMM_RRC_IDNNS_UNKNOWN,
                          pDetachRequest);                                      /* 建立信令连接                             */
        Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);
    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcPowerOffReq
  Function : GMM收到MMCGMM_POWER_OFF_REQ的分发处理
  Input    : VOS_VOID   *pMsg    原语指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.08  新规作成
    2. 日    期   : 2009年5月9日
       作    者   : l00130025
       修改内容   : 根据问题单号：AT2D11645/AT2D11797,关机，若detach的EST_REQ失败，Gmm会反复发起EST_REQ
    3. 日    期   : 2009年05月23日
       作    者   : L65478
       修改内容   : 问题单号:AT2D06770,RAU失败，因为GRM建链的原因是DATA，实际应该是信令
    4. 日    期   : 2010年07月26日
       作    者   : L65478
       修改内容   : 问题单号:DTS2010072200479,开机注册过程中，关机，再开机时失败，因为GMM没有立刻处理关机消息，导致MMC保护定时器超时
    5. 日    期   : 2010年09月13日
       作    者   : L65478
       修改内容   : 问题单号:DTS2010091301310,WCDMA下关机，重新开机后，在GSM模式下无法注册成功
    6. 日    期   : 2010年11月11日
       作    者   : 欧阳飞
       修改内容   : DTS2010111003071，GSM下，网络模式II，CS Only，PDP激活后，直
                    接关机，导致MM/GMM同时都发起了detach流程
    7.日    期   : 2012年1月9日
      作    者   : l00130025
      修改内容   : DTS2011122900476,释放缓存的Gsm系统消息
    8.日    期   : 2012年8月25日
      作    者   : m00217266
      修改内容   : 删除GMM_SaveErrCode，添加Gmm_Save_Detach_Cause，
                 保存导致由Attach切换到Detach的原因值

    9.日    期   : 2012年11月10日
      作    者   : w00176964
      修改内容   : DTS2012110707605:PS未attach上,直接给MMC回复关机结果,加快关机速度
   10.日    期   : 2011年12月28日
      作    者   : l00167671
      修改内容   : 修改问题单DTS2012122001075,问题单场景如下:
                  PS建链过程中发生RA改变，该场景中如果CS域有业务则PS域做RAU
                  会被不确定的推迟到CS连接释放时才做，修改此场景中的操作如下:
                  若CS域有业务则给WAS发送RRMM_REL_REQ请求，请WAS释放连接，
                  并保存系统消息。在收到WAS的RRMM_REL_IND时用保存的系统消息做RAU
   11.日    期   : 2013年2月4日
      作    者   : w00176964
      修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
*******************************************************************************/
VOS_VOID Gmm_RcvMmcPowerOffReq(
                           VOS_VOID *pMsg                                       /* 原语指针                                 */
                           )
{
    MMCGMM_POWER_OFF_REQ_STRU      *ptr;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_PS_DETACH);

    /* 启动关机保护定时器，*/
    Gmm_TimerStart(GMM_TIMER_1S);

    if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        && (GMM_RRC_RRMM_EST_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
        && ((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState)))
    {                                                                           /* 状态是GMM-流程-INITIATED                 *
                                                                                 * 且无信令且正在建立信令连接               */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_POWEROFF;      /* 置缓存标志                               */
        ptr = (MMCGMM_POWER_OFF_REQ_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_POWER_OFF_REQ_STRU));
        if (VOS_NULL_PTR == ptr)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcPowerOffReq:WARNING: STATUS IS GMM_REGISTERED_IMSI_DETACH_INITIATED");
            return;
        }
        Gmm_MemCpy(ptr, pMsg, sizeof(MMCGMM_POWER_OFF_REQ_STRU));
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff = (VOS_UINT32)ptr;         /* 缓存原语                                 */

        return;                                                                 /* 返回                                     */
    }

    /* GMM给上层应用回复失败 */
    Gmm_ComCnfHandle();
    Gmm_HoldBufferFree();
    /* 关机清除GMM缓存 */
    GMM_BufferMsgDump();

    NAS_GMM_FreeGsmSysInfo();

    NAS_GMM_FreeWasSysInfo();

    /* PS未attach上,直接给MMC回复关机结果 */
    if ((GMM_STATUS_ATTACHED                    != g_MmSubLyrShare.GmmShare.ucAttachSta)
     && (GMM_REGISTERED_INITIATED               != g_GmmGlobalCtrl.ucState)
     && (GMM_ROUTING_AREA_UPDATING_INITIATED    != g_GmmGlobalCtrl.ucState))
    {
        g_GmmReqCnfMng.ucCnfMask = 0;
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
        g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;

        Gmm_ComStaChg(GMM_NULL);                                                /* 调用状态的公共处理                       */
        Gmm_SndMmcPowerOffCnf();                                                /* 向MMC发送MMCGMM_POWER_CNF               */
        Gmm_ComVariantInit();                                                   /* 清除全局变量                             */

        return;
    }

    enCurRat = NAS_MML_GetCurrNetRatType();

    /*G下，当前MM有业务正在进行，缓存关机请求 */
    if ((MMC_MM_SIGNALING_STATUS_PRESENT == MM_GetSignalingStatus())
     && (NAS_MML_NET_RAT_TYPE_GSM == enCurRat))
    {
        gstGmmSuspendCtrl.ucPowerOff = GMM_POWER_OFF_RCV;

        return;
    }

    /* 进行关机流程 */
    Gmm_TimerStop(GMM_TIMER_ALL);

    g_GmmReqCnfMng.ucCnfMask = 0;
    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
    g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;

    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
    {                                                                           /* A+I                                      */
        if ((GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
            && (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState))

        {                                                                       /* MM和GMM均注册                            */
            g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_COMBINED_POWER_OFF;         /* 置当前的specific过程                     */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: combined detach(power off) procedure started");

        }
        else if ((GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
            && (MM_STATUS_DETACHED
            == g_MmSubLyrShare.MmShare.ucCsAttachState))
        {                                                                       /* MM未注册,GMM注册                         */
            if((GMM_RAU_COMBINED == g_GmmGlobalCtrl.ucSpecProc)
                || (GMM_RAU_WITH_IMSI_ATTACH == g_GmmGlobalCtrl.ucSpecProc))
            {                                                                   /* 当前流程是combined                       */
                g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_COMBINED_POWER_OFF;     /* 置当前的specific过程                     */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: combined detach(power off) procedure started");
            }
            else
            {                                                                   /* 当前流程不是combined                     */
                g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_NORMAL_POWER_OFF;       /* 置当前的specific过程                     */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: normal detach(power off) procedure started");
            }
        }
        else
        {                                                                       /* GMM未注册                                */
            if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
            {                                                                   /* 当前状态是REGISTERED_INITIATED           */

                if ((GMM_ATTACH_NORMAL == g_GmmGlobalCtrl.ucSpecProc)
                   ||(GMM_ATTACH_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc))
                {                                                               /* 进行normal attach                        */
                    g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_NORMAL_POWER_OFF;   /* 置当前的specific过程                     */
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: normal detach(power off) procedure started");
                }
                else
                {                                                               /* 进行combine attach                       */
                    g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_COMBINED_POWER_OFF; /* 置当前的specific过程                     */
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: combined detach(power off) procedure started");
                }
            }
            else if (GMM_ROUTING_AREA_UPDATING_INITIATED
                                            == g_GmmGlobalCtrl.ucState)
            {                                                                   /* 当前状态是RAU_INITIATED                  */

                if ((GMM_RAU_NORMAL == g_GmmGlobalCtrl.ucSpecProc)
                    ||(GMM_RAU_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc))
                {                                                               /* 进行normal rau                           */
                    g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_NORMAL_POWER_OFF;   /* 置当前的specific过程                     */
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: normal detach(power off) procedure started");
                }
                else
                {                                                               /* 进行combine rau                          */
                    g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_COMBINED_POWER_OFF; /* 置当前的specific过程                     */
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: combined detach(power off) procedure started");
                }
            }
            else
            {                                                                   /* 其他状态                                 */
                Gmm_ComStaChg(GMM_NULL);                 /* 调用状态的公共处理                       */
                Gmm_SndMmcPowerOffCnf();                                        /* 向MMC发送MMCGMM_DETACH_CNF               */
                Gmm_ComVariantInit();                                           /* 清除全局变量                             */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: specific procedure ended");
                return;
            }
        }
    }
    else
    {                                                                           /* A+II或C                                  */
        if ((GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
            || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
            || (GMM_ROUTING_AREA_UPDATING_INITIATED
                                             == g_GmmGlobalCtrl.ucState))
        {                                                                       /* GMM注册或者
                                                                                 * 当前状态是REGISTERED_INITIATE            */
            g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_NORMAL_POWER_OFF;           /* 置当前的specific过程                     */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: normal detach(power off) procedure started");
        }
        else
        {                                                                       /* GMM未注册                                */
            Gmm_ComStaChg(GMM_NULL);                     /* 调用状态的公共处理                       */
            Gmm_SndMmcPowerOffCnf();                                            /* 向MMC发送MMCGMM_DETACH_CNF               */
            Gmm_ComVariantInit();                                                   /* 清除全局变量                             */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: specific procedure ended");
            return;
        }
    }

    Gmm_PowerOffDetach();                                                       /* 调用Power Off时的detach处理              */

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_PowerOffDetach
  Function : Power Off时的detach处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.张志勇  2003.12.08  新规作成
  2.日    期   : 2009年5月9日
    作    者   : l00130025
    修改内容   : 根据问题单号：AT2D11645/AT2D11797,关机，若detach的EST_REQ失败，Gmm会反复发起EST_REQ
  3.日    期   : 2009年05月23日
    作    者   : L65478
    修改内容   : 问题单号:AT2D06770,RAU失败，因为GRM建链的原因是DATA，实际应该是信令
  4.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  5.日    期   : 2011年07月13日
    作    者   : w00166186
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  6.日    期   : 2012年04月20日
    作    者   : L65478
    修改内容   : DTS2012042005349在G下关机时没有挂起TTF，导致TTF一直发数,IOT失败
  7.日    期   : 2012年10月12日
    作    者   : w00176964
    修改内容   : DTS2012091400694:G模关机慢
  8.日    期   : 2015年2月6日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整
*******************************************************************************/
VOS_VOID Gmm_PowerOffDetach(VOS_VOID)
{
    NAS_MSG_STRU        *pDetachRequest;                                        /* 定义指针                                 */

    if ( (GMM_REGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
      || (GMM_REGISTERED_LIMITED_SERVICE  == g_GmmGlobalCtrl.ucState)
      || (GMM_REGISTERED_UPDATE_NEEDED  == g_GmmGlobalCtrl.ucState)
      || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE  == g_GmmGlobalCtrl.ucState)
      || (GMM_REGISTERED_PLMN_SEARCH  == g_GmmGlobalCtrl.ucState) )
    {
        if(GMM_TRUE == GMM_IsCasGsmMode())
        {
            Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ALL);
        }
        if ((GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
            || (GMM_DETACH_NORMAL_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc))
        {                                                                       /* 当前流程是POWER OFF                      */
            if (GMM_UEID_P_TMSI_SIGNATURE
             == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
            & GMM_UEID_P_TMSI_SIGNATURE))
            {                                                                   /* DETACH成功且使用了P_TMSI_SIGNATURE       */
                g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                    &= ~GMM_UEID_P_TMSI_SIGNATURE;                              /* 清除P_TMSI_SIGNATURE                     */
                NAS_MML_InitUeIdPtmsiSignatureInvalid();
                if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
                {
                    Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
                }
                else
                {
                    Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
                }
            }

            if (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
            {                                                                       /* 是combined流程                           */
                NAS_GMM_SndMmGprsDetachInitiation();                                   /* 发送原语通知MMC                          */
            }

            Gmm_SndMmcPowerOffCnf();                                            /* 向MMC回POWER OFF的响应                   */

            Gmm_ComStaChg(GMM_NULL);                     /* 调用状态的公共处理                       */

            /*Gmm_TimerDistroy();*/                                                     /* 销毁所有TIMER                            */
            Gmm_ComVariantInit();                                               /* 清除全局变量                             */
            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                    /* 清当前流程                               */
        }
        else if ((GMM_DETACH_COMBINED_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc)
            || (GMM_DETACH_NORMAL_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc))
        {                                                                       /* 当前流程是SIM REMOVE                     */
            /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                NAS_GMM_SndMmcMmDetachInfo();
            }


            /* 向MMC发送PS注册结果 */
            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                         GMM_MMC_ACTION_RESULT_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

            Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                            /* 调用状态的公共处理                       */

            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                    /* 清当前流程                               */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_Tim5sExpired:INFO: specific procedure ended");

            g_GmmReqCnfMng.ucCnfMask = 0;                                       /* 清等待cnf标志                            */
        }
        else
        {
        }
    }
    else
    {
        if (GMM_TRUE == GMM_IsCasGsmMode())
        {
            if(GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
            {
                GMM_SndLlcSuspendReq();
                gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_SUSPEND_LLC_FOR_DETACH;
            }
        }

        /* 在发起detach时，有可能原来曾经把LLC挂起，所以在发送detach前，需要恢复LLC */
        if (GMM_NOT_SUSPEND_LLC != gstGmmCasGlobalCtrl.ucSuspendLlcCause)
        {
            GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_SIGNAL);
        }

        pDetachRequest = Gmm_DetachRequestMsgMake();                            /* 调用detach request消息制作函数           */

        if ((GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
            || (GMM_DETACH_COMBINED_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc))
        {                                                                       /* 是combined流程                           */
            NAS_GMM_SndMmGprsDetachInitiation();                                   /* 发送原语通知MMC                          */
        }
        if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
        {                                                                       /* 当前存在信令连接                         */
            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachRequest);       /* 发送detach request消息                   */
            GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NORMAL_SERVICE);
            Gmm_TimerStart(GMM_TIMER_1S);                                       /* 启动1S定时器                             */
        }
        else
        {                                                                       /* 当前不存在信令连接                       */
            Gmm_SndRrmmEstReq(RRC_EST_CAUSE_DETACH,
                              GMM_RRC_IDNNS_UNKNOWN,
                              pDetachRequest);                                  /* 建立信令连接                             */

            Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ESTING);      /* 通知MMC PS域信令连接正在建立             */
            GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NORMAL_SERVICE);
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_PowerOffDetach:NORMAL: STATUS IS GMM_DEREGISTERED_NORMAL_SERVICE");

            if ((GMM_DETACH_COMBINED_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc)
                || (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc))
            {                                                                   /* 当前流程是combined sim remove或power off */
                g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;   /* 置标志位能作detach                       */
            }
            Gmm_TimerStart(GMM_TIMER_1S);                                       /* 启动5S定时器                             */
        }
        ++ (g_GmmGlobalCtrl.stPowerOffCtrl.ucSndDetachCnt);

        /* G下关机参考标杆做法:GMM启动5S定时器,这里detach发出后只需要尝试5次 */
        Gmm_TimerStart(GMM_TIMER_DETACH_FOR_POWER_OFF);
    }
    return;                                                                     /* 返回                                     */
}

/*lint -e438 -e830*/

/*******************************************************************************
  Module   : Gmm_DetachRequestMsgMake
  Function : Detach request消息制作
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : NAS_MSG_STRU *
  History  :
  1. 张志勇  2003.12.08  新规作成
  2. 日    期   : 2006年11月20日
     作    者   : s46746
     修改内容   : 创建，根据问题单号：A32D07433
  3. 日    期   : 2009年06月17日
     作    者   : ouyangfei o00132663
     修改内容   : 根据终端可配置需求修改，R99以前版本不生成可选IE
  4. 日    期   : 2009年08月14日
     作    者   : ouyangfei o00132663
     修改内容   : AT2D13748:获取3GPP协议版本，函数参数错误，应该查询PS域版本。
  5.日    期   : 2011年7月27日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
*******************************************************************************/
NAS_MSG_STRU* Gmm_DetachRequestMsgMake(VOS_VOID)
{
    NAS_MSG_FOR_PCLINT_STRU    *pDetachRequest;                                 /* 定义指针                                 */
    NAS_MSG_STRU               *pNasMsg;
    VOS_UINT32                  ulMsgLen;                                       /* 定义变量存储消息长度                     */
    VOS_UINT8                   ucPtmsiFlg;                                     /* 定义变量标志是否存在P-TMSI               */
    VOS_UINT8                   ucPtmsiSigFlg;                                  /* 定义变量标志是否存在P-TMSI signature     */
    VOS_UINT8                   ucNumber;
    VOS_INT8                    cVersion;

    cVersion = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS);

    ulMsgLen        = GMM_MSG_LEN_DETACH_REQUEST;                               /* 初始化临时变量,消息中必选部分            */
    ucPtmsiFlg      = GMM_FALSE;                                                /* 初始化临时变量                           */
    ucPtmsiSigFlg   = GMM_FALSE;                                                /* 初始化临时变量                           */
    pDetachRequest  = VOS_NULL_PTR;                                             /* 初始化临时变量                           */

    /* R99以前版本无可选IE */
    if(PS_PTL_VER_PRE_R99 != cVersion)
    {
        if (GMM_UEID_P_TMSI == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI))
        {                                                                           /* 存在P-TMSI                               */
            ulMsgLen  += 7;                                                         /* 消息长度增加                             */
            ucPtmsiFlg = GMM_TRUE;                                                  /* 标志存在P-TMSI                           */
        }

        if (  (GMM_TRUE == ucPtmsiFlg)
            &&(GMM_UEID_P_TMSI_SIGNATURE == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE)))
        {                                                                           /* 存在P-TMSI signature                     */
            ulMsgLen     += 5;                                                      /* 消息长度增加                             */
            ucPtmsiSigFlg = GMM_TRUE;                                               /* 标志存在P-TMSI signature                 */
        }
    }

    if (ulMsgLen <= 4)
    {                                                                           /* 消息长度小于等于4                        */
        pNasMsg = (NAS_MSG_STRU *)Gmm_MemMalloc(sizeof(NAS_MSG_STRU));          /* 申请内存空间                             */
        if (VOS_NULL_PTR == pNasMsg)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_DetachRequestMsgMake:error: Alloc mem fail.");
            return pNasMsg;
        }
        pDetachRequest = (NAS_MSG_FOR_PCLINT_STRU *)pNasMsg;
        Gmm_MemSet(pDetachRequest, 0, sizeof(NAS_MSG_STRU));                    /* 将申请的内存空间清0                      */
    }
    else
    {                                                                           /* 消息长度大于4                            */
        pNasMsg = (NAS_MSG_STRU *)Gmm_MemMalloc(
                                         (sizeof(NAS_MSG_STRU) + ulMsgLen) - 4);  /* 申请内存空间                             */
        if (VOS_NULL_PTR == pNasMsg)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_DetachRequestMsgMake:error: Alloc mem fail.");
            return pNasMsg;
        }
        pDetachRequest = (NAS_MSG_FOR_PCLINT_STRU *)pNasMsg;
        Gmm_MemSet(pDetachRequest, 0, (sizeof(NAS_MSG_STRU) + ulMsgLen) - 4);   /* 将申请的内存空间清0                      */
    }

    pDetachRequest->ulNasMsgSize = ulMsgLen;                                    /* 赋值消息长度                             */
    pDetachRequest->aucNasMsg[0] = GMM_PD_GMM;                                  /* PD和Skip Indicator                       */
    pDetachRequest->aucNasMsg[1] = GMM_MSG_DETACH_REQUEST;                      /* message type                             */
    switch (g_GmmGlobalCtrl.ucSpecProc)
    {                                                                           /* 判断detach类型进行不同处理               */
    case GMM_DETACH_COMBINED:                                                   /* combined detach                          */
        pDetachRequest->aucNasMsg[2] = GMM_COMBINED_DETACH_NORMAL;              /* detach type                              */
        break;
    case GMM_DETACH_NORMAL:                                                     /* normal detach                            */
    case GMM_DETACH_NORMAL_NETMODE_CHANGE:
        pDetachRequest->aucNasMsg[2] = GMM_GPRS_DETACH_NORMAL;                  /* detach type                              */
        break;
    case GMM_DETACH_WITH_IMSI:                                                  /* IMSI detach                              */
        pDetachRequest->aucNasMsg[2] = GMM_IMSI_DETACH_MS_TO_NET;               /* detach type                              */
        break;
    case GMM_DETACH_COMBINED_POWER_OFF:                                         /* combined detach with power off           */
    case GMM_DETACH_COMBINED_SIM_REMOVE:                                        /* combined detach with sim removing        */
        pDetachRequest->aucNasMsg[2] = GMM_COMBINED_DETACH_POWEROFF;            /* detach type                              */
        break;
    case GMM_DETACH_NORMAL_POWER_OFF:                                           /* GPRS detach with power off               */
    case GMM_DETACH_NORMAL_SIM_REMOVE:                                          /* GPRS detach with sim removing            */
        pDetachRequest->aucNasMsg[2] = GMM_GPRS_DETACH_POWEROFF;                /* detach type                              */
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_DetachRequestMsgMake:WARNING: g_GmmGlobalCtrl.ucSpecProc is Abnormal");
        Gmm_MemFree(pDetachRequest);
        return VOS_NULL_PTR;
    }

    /* R99以前版本无可选IE */
    if(PS_PTL_VER_PRE_R99 != cVersion)
    {
        ucNumber = 3;
        if (GMM_TRUE == ucPtmsiFlg)
        {                                                                           /* 存在P-TMSI                               */
            /*lint -e961*/
            pDetachRequest->aucNasMsg[ucNumber++]
                                        = GMM_IEI_P_TMSI;                           /* IEI                                      */
            pDetachRequest->aucNasMsg[ucNumber++]
                                        = 0x05;                                     /* length                                   */
            pDetachRequest->aucNasMsg[ucNumber++]
                                        = GMM_MOBILE_ID_TMSI_PTMSI | 0xf0;          /* type of id and the 5-8 bit               */
            /*lint +e961*/
            Gmm_MemCpy(&pDetachRequest->aucNasMsg[ucNumber],
                       NAS_MML_GetUeIdPtmsi(),
                       NAS_MML_MAX_PTMSI_LEN);                                         /* P_TMSI赋值                               */
            ucNumber = ucNumber + NAS_MML_MAX_PTMSI_LEN;

        }
        if (GMM_TRUE == ucPtmsiSigFlg)
        {                                                                           /* 存在P-TMSI signature                     */
            /*lint -e961*/
            pDetachRequest->aucNasMsg[ucNumber++] = GMM_IEI_P_TMSI_SIGNATURE;       /* IEI                                      */
            pDetachRequest->aucNasMsg[ucNumber++] = 0x03;                           /* length                                   */
            /*lint +e961*/
            Gmm_MemCpy(&(pDetachRequest->aucNasMsg[ucNumber]),
                       NAS_MML_GetUeIdPtmsiSignature(),
                       NAS_MML_MAX_PTMSI_SIGNATURE_LEN);                            /* P_TMSI signature赋值 */
            ucNumber += NAS_MML_MAX_PTMSI_SIGNATURE_LEN;
        }
    }

    /* 发起Detach流程，更新GMM链路释放控制变量 */
    NAS_GMM_UpdateGmmLinkCtrlStru();
    g_GmmDetachCtrl.ucRetryDetachForRelCtrlFlg =  VOS_FALSE;
    g_GmmDetachCtrl.ucDetachProc = g_GmmGlobalCtrl.ucSpecProc;

    return (NAS_MSG_STRU *)pDetachRequest;                                                      /* 返回做成的消息                           */
}
/*lint +e438 +e830*/

/*******************************************************************************
  Module   : Gmm_RcvDetachRequestMsg
  Function : GMM收到DETACH_REQUEST的分发处理
  Input    : NAS_MSG_STRU   *pMsg  当前处理的消息
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1. 张志勇  2003.12.08  新规作成
  2. x51137 2006/4/28 A32D02889
  3.日    期   : 2012年1月12日
    作    者   : w00166186
    修改内容   : DTS2011122704039:开机搜网后CS注册被拒#12,PS注册被拒#14，在ON
                 PLMN状态，服务域被设置为不支持GMM需要将服务域不支持信息通知给MMC.
  4.日    期   : 2012年3月3日
    作    者   : z00161729
    修改内容   : V7R1 C50 支持ISR修改,T3312启动停止超时均需通知L
  5.日    期   : 2012年8月25日
    作    者   : m00217266
    修改内容   : 删除GMM_SaveErrCode，添加Gmm_Save_Detach_Cause，
                保存导致Attach失败的原因值

  6.日    期   : 2013年6月8日
    作    者   : w00167002
    修改内容   : V9R1_SVLTE:代码走读发现:ucDetachType类型维护错误.
  7.日    期   : 2014年10月20日
    作    者   : h00285180
    修改内容   : 拒绝原因值优化PhaseII DTS2014110307415
*******************************************************************************/
VOS_VOID Gmm_RcvDetachRequestMsg(
                             NAS_MSG_FOR_PCLINT_STRU       *pMsg
                             )
{
    VOS_UINT8               ucDetachType;                                           /* 定义临时变量                             */
    VOS_UINT8               ucGmmCause;                                             /* 定义临时变量                             */
    NAS_MSG_STRU        *pGmmStatus;
    VOS_UINT8           ucForceToStandby;

    ucDetachType = 0;                                                           /* 初始化临时变量                           */
    ucGmmCause   = NAS_MML_REG_FAIL_CAUSE_NULL;                                 /* 初始化临时变量                           */

    if (pMsg->ulNasMsgSize < GMM_MSG_LEN_DETACH_REQUEST)
    {                                                                           /* 消息中必选项的长度不够                   */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachRequestMsg:WARNING: Length of DETACH REQUEST is invalid");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;                                                                 /* 返回                                     */
    }

    ucForceToStandby = (VOS_UINT8)((pMsg->aucNasMsg[2]>>4) & 0x0F);
    if (1 == ucForceToStandby)
    {
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_TRUE;
    }
    else if (0 == ucForceToStandby)
    {
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }
    else
    {                                                                           /* Force to standby                         */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachRequestMsg:WARNING: DETACH REQUEST is semantically incorrect");
        /*pGmmStatus = */
        /*    Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);*/

        /*Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);*/
        /*return;*/
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }

    ucDetachType = (VOS_UINT8)(pMsg->aucNasMsg[2] & 0x0F);                          /* 从消息中取detach类型                     */
    if ((GMM_NET_DETACH_REATTACH_REQUIRED != ucDetachType)
        && (GMM_NET_DETACH_IMSI_DETACH    != ucDetachType))
    {                                                                           /* detach类型不是reattach required
                                                                                 * 并且也不是imsi detach                    */
        ucDetachType = GMM_NET_DETACH_REATTACH_NOT_REQUIRED;                    /* 将消息类型置为reattach not required      */
    }
    /* 如果是PS域DETACH，需要保存触发原因 */
    if (GMM_NET_DETACH_IMSI_DETACH != ucDetachType)
    {
        if (5 == pMsg->ulNasMsgSize)
        {                                                                           /* 消息长度等于5                            */
            if (GMM_IEI_GMM_CAUSE != pMsg->aucNasMsg[3])
            {
                /* 原因值的IEI不正确 */
                NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_PROTOCOL_ERROR);
            }
            else
            {
                /* 原因值的IEI正确 */
                NAS_GMM_ChangeDetachCauseAvoidInvalidSim(&(pMsg->aucNasMsg[4]));

                ucGmmCause = pMsg->aucNasMsg[4];                                    /* 从消息中取detach原因                     */
                NAS_GMM_SetAttach2DetachErrCode(NAS_GMM_TransGmmNwCause2GmmSmCause(ucGmmCause));
            }
        }
        else
        {
            NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_PROTOCOL_ERROR);
        }
    }

#if (FEATURE_ON == FEATURE_PTM)
    NAS_GMM_NwDetachIndRecord(ucDetachType, ucGmmCause, ucForceToStandby);
#endif

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 判断当前状态进行不同的处理               */
    case GMM_REGISTERED_INITIATED:                                              /* GMM-REGISTERED-INITIATED                 */
        Gmm_RcvDetachRequestMsg_RegInit(ucDetachType, ucGmmCause);              /* 调用该状态下的detach处理                 */
        break;
    case GMM_DEREGISTERED_INITIATED:                                            /* GMM-DEREGISTERED-INITIATED               */
        Gmm_RcvDetachRequestMsg_DeregInit(ucDetachType, ucGmmCause);                                    /* 调用该状态下的detach处理                 */
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:                                   /* GMM-ROUTING-AREA-UPDATING-INITIATED      */
        Gmm_RcvDetachRequestMsg_RauInit(ucDetachType, ucGmmCause);              /* 调用该状态下的detach处理                 */
        break;
    case GMM_SERVICE_REQUEST_INITIATED:                                         /* GMM-SERVICE-REQUEST-INITIATED            */
        Gmm_RcvDetachRequestMsg_ServReqInit(ucDetachType, ucGmmCause);          /* 调用该状态下的detach处理                 */
        break;
    case GMM_REGISTERED_NORMAL_SERVICE:                                         /* GMM-REGISTERED.NORMAL-SERVICE            */
    case GMM_REGISTERED_LIMITED_SERVICE:                                        /* GMM-REGISTERED.LIMITED-SERVICE           */
        Gmm_RcvDetachRequestMsg_RegNmlServ(ucDetachType, ucGmmCause);           /* 调用该状态下的detach处理                 */
        break;
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:                                /* GMM-REGISTERED.ATTEMPTING-TO-UPDATE-MM   */
        Gmm_RcvDetachRequestMsg_RegAtmpToUpdtMm(ucDetachType, ucGmmCause);      /* 调用该状态下的detach处理                 */
        break;
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:                                  /* GMM-REGISTERED.IMSI-DETACH-INITIATED     */
        Gmm_RcvDetachRequestMsg_RegImsiDtchInit(ucDetachType, ucGmmCause);                              /* 调用该状态下的detach处理                 */
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachRequestMsg:WARNING: g_GmmGlobalCtrl.ucState is Abnormal");
        break;
    }

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        if ( ucDetachType == GMM_NET_DETACH_IMSI_DETACH )
        {
            if ( GMM_TRUE == gstGmmCasGlobalCtrl.ucFtsFlg )
            {
                gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;

                if ( 0xffffffff != gstGmmCasGlobalCtrl.ulReadyTimerValue )
                {
                    gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
                    Gmm_TimerStop(GMM_TIMER_T3314);
#if (FEATURE_LTE == FEATURE_ON)
                    if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                    {
                        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                    }
#endif
                    Gmm_TimerStart(GMM_TIMER_T3312);
                    NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
                }
            }
        }
        else/* detach PS */
        {
            Gmm_TimerStop(GMM_TIMER_T3314);
            gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;
            gstGmmCasGlobalCtrl.ulReadyTimerValue = 44000;/* default 44s */
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
            }
#endif
            Gmm_TimerStop(GMM_TIMER_T3312);
            NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        }

    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvDetachRequestMsg_RegInit
  Function : 在GMM-REGISTERED-INITIATED状态下收到DETACH_REQUEST的处理
  Input    : VOS_UINT8     ucDetachType     detach类型
             VOS_UINT8     ucGmmCause       detach原因
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
   1. 张志勇  2003.12.08  新规作成
   2.日    期   : 2008年7月2日
     作    者   : l00107747
     修改内容   : 根据问题单号：AT2D03900
   3.日    期  : 2012年08月24日
     作    者  : m00217266
     修改内容  : 修改Gmm_SndSmEstablishCnf接口，添加原因值
   4.日    期   : 2015年6月5日
     作    者   : z00161729
     修改内容   : 24008 23122 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID Gmm_RcvDetachRequestMsg_RegInit(
                                     VOS_UINT8      ucDetachType,                   /* detach类型                               */
                                     VOS_UINT8      ucGmmCause                      /* detach原因                               */
                                     )
{
    /* 24008_CR2300R1_(Rel-11)_C1-124892 24008 4.7.3.1.5描述如下:
    If the MS receives a DETACH REQUEST message from the network in state
    GMM-REGISTERED-INITIATED with detach type of detach '"re-attach not required"
    and no cause code, or "re-attach not required"' and the cause code is not #2
    "IMSI unknown in HLR", the GPRS detach procedure shall be progressed and the
    GPRS attach procedure shall be aborted. Otherwise the GPRS attach procedure
    shall be progressed and the DETACH REQUEST message shall be ignored.*/
    if ((GMM_NET_DETACH_REATTACH_NOT_REQUIRED == ucDetachType)
     && (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR != ucGmmCause))
    {                                                                           /* detach类型是"re-attach not required"     */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* 停T3310                                  */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                              /* 清除followon标志                         */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

        g_GmmReqCnfMng.ucCnfMask   = 0;                                         /* 清除等待CNF标志                          */
        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {                                                                       /* ATTACH过程是由SM触发的                   */
            /* 该函数的入参ucGmmCause由函数Gmm_RcvDetachRequestMsg传入，其取值可
             能为NAS_MML_REG_FAIL_CAUSE_NULL，该值不在GMM/SM层的原因值内，故此处
             用g_GmmGlobalCtrl.enGmmCause保存的值 */

            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, NAS_GMM_GetAttach2DetachErrCode());    /* 通知SM GMM注册失败                       */

            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* 清ucSmCnfFlg标志                         */
        }
        Gmm_NetInitNotRequiredDetach(ucGmmCause);                               /* 调用detach的公共处理                     */
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清除当前进行的specific过程               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvDetachRequestMsg_RegInit:INFO: specific procedure ended");
    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvDetachRequestMsg_DeregInit
  Function : 在GMM-DEREGISTERED-INITIATED状态下收到DETACH_REQUEST的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.08  新规作成
    2. 日    期   : 2007年12月12日
       作    者   : l00107747
       修改内容   : 根据问题单号：A32D13861
    3. 日    期   : 2010年10月16日
       作    者   : s46746
       修改内容   : 根据问题单号：DTS2010100900274,接收到网络Detach请求后没有指示SM进入Detach状态
    4. 日    期   : 2011年07月13日
       作    者   : w00166186
       修改内容   : V7R1 PHASE II ATTACH/DETACH调整
    5. 日    期   : 2012年06月04日
       作    者   : l65478
       修改内容   : DTS2012060402840 MS发起的DETACH和网络的冲突时,没有清除ATTACH运行标志
    6.日    期   : 2013年6月8日
      作    者   : w00167002
      修改内容   : V9R1_SVLTE:代码走读发现:如果当前是CS域的DETACH，则不更新服务域.
    7.日    期   : 2013年8月7日
      作    者   : w00167002
      修改内容   : DTS2013080207367:在CS only时候，用户发起PDP激活，网络模式I时候，
                 会触发联合注册.用户发起PDP去激活，会导致PS域的去注册。收到网侧
                 的去注册成功后需要通知MM，否则MM当前在NORMAL SERVICE状态，不
                 触发T3212定时器的启动，长时间可能导致丢寻呼.
    8.日    期   : 2013年08月16日
      作    者   : l65478
      修改内容   : DTS2013092202614,G CCO到W失败回退到G,在G下通知了GAS进入了REDAY态
    9.日    期   : 2015年6月5日
      作    者   : z00161729
      修改内容   : 24008 23122 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID Gmm_RcvDetachRequestMsg_DeregInit(
    VOS_UINT8                           ucDetachType,           /* detach类型                               */
    VOS_UINT8                           ucGmmCause              /* detach原因                               */
)
{
    NAS_MSG_STRU    *pDetachAccept;                                             /* 定义指针                                 */

    /* 24008_CR2062R2_(Rel-11)_C1-121261 24008 4.7.4.1.4章节描述如下:
    GPRS detach containing other causes than "power off":
    If the DETACH REQUEST message received by the MS contains detach type "IMSI detach",
    and the MS initiated detach procedure is with detach type "GPRS detach" or
    "combined GPRS/IMSI detach", the MS shall progress both procedures.
    The MS in operation mode A or B in network operation mode I need not re-attach to non-GPRS services.*/
    if ((GMM_NET_DETACH_IMSI_DETACH == ucDetachType)
     && ((GMM_WAIT_PS_DETACH == g_GmmGlobalCtrl.stDetachInfo.enDetachType)
      || (GMM_WAIT_CS_PS_DETACH == g_GmmGlobalCtrl.stDetachInfo.enDetachType))
      && (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState))
    {
        Gmm_SndMmcNetworkDetachInd(NAS_MMC_GMM_NT_DETACH_IMSI, NAS_MML_REG_FAIL_CAUSE_NULL);  /* 发送MMCGMM_NETWORK_DETACH_IND            */
        NAS_GMM_SndMmNetworkDetachInd(GMMMM_NET_DETACH_IMSI,
                                      NAS_MML_REG_FAIL_CAUSE_NULL);

        pDetachAccept = Gmm_DetachAcceptMsgMake();
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachAccept);
        return;
    }

    pDetachAccept = Gmm_DetachAcceptMsgMake();                                  /* 调用函数制作detach accept消息            */

    Gmm_TimerStop(GMM_TIMER_T3321);
    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachAccept);                /* 发送RRMM_DATA_REQ(detach accept消息)     */
    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_USER);

        Gmm_TimerStop(GMM_TIMER_T3314);

        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;

        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
    }
    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else
    {
        /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
        NAS_GMM_SndMmGprsDetachComplete();
    }


    Gmm_SndMmcNetworkDetachInd(ucDetachType, ucGmmCause);  /* 发送MMCGMM_NETWORK_DETACH_IND            */

    NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvDetachRequestMsg_RauInit
  Function : GMM-RAU-INITIATED状态下收到DETACH_REQUEST的处理
  Input    : VOS_UINT8     ucDetachType     detach类型
             VOS_UINT8     ucGmmCause       detach原因
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.08  新规作成
    2.日    期   : 2015年6月4日
      作    者   : z00161729
      修改内容   : 24008 23122 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID Gmm_RcvDetachRequestMsg_RauInit(
                                     VOS_UINT8      ucDetachType,               /* detach类型                               */
                                     VOS_UINT8      ucGmmCause                  /* detach原因                               */
                                     )
{
    /* 24008_CR1598R2_(Rel-9)_C1-103557 24008 4.7.4.2.4描述如下:
    If the network receives a ROUTING AREA UPDATE REQUEST message before the network initiated
    GPRS detach procedure has been completed, the detach procedure shall be progressed,
    i.e. the ROUTING AREA UPDATE REQUEST message shall be ignored. If the DETACH REQUEST
    message contains detach type "re-attach not required" and GMM cause  #2 "IMSI unknown in HLR",
    the network will follow the procedure as described below for the detach type "IMSI detach".
    GPRS detach containing detach type "IMSI detach":
     If the network receives a ROUTING AREA UPDATE REQUEST message before the network
     initiated GPRS detach procedure has been completed, the network shall abort the detach procedure,
     shall stop T3322 and shall progress the routing area update procedure.*/
    if (GMM_NET_DETACH_IMSI_DETACH == ucDetachType)
    {
        return;
    }

    if ((GMM_NET_DETACH_REATTACH_NOT_REQUIRED == ucDetachType)
     && (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR == ucGmmCause))
    {
        return;
    }                                                                          /* detach类型为"re-attach not required"
                                                                             * 或"re-attach required                    */
    Gmm_TimerStop(GMM_TIMER_T3330);                                         /* 停T3330                                  */

    Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

    Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护Timer                              */

    Gmm_ComCnfHandle();
    g_GmmReqCnfMng.ucCnfMask   = 0;                                         /* 清除等待CNF标志                          */
    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清除当前进行的specific过程               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvDetachRequestMsg_RauInit:INFO: specific procedure ended");

    if (GMM_NET_DETACH_REATTACH_NOT_REQUIRED == ucDetachType)
    {                                                                       /* detach类型为"re-attach not required"     */
        Gmm_NetInitNotRequiredDetach(ucGmmCause);                           /* 调用"re-attach not required"的公共处理   */
    }
    else
    {                                                                       /* detach类型为"re-attach required"         */
        Gmm_NetInitRequiredDetach();                                        /* 调用re-attach required的处理             */
    }


    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvDetachRequestMsg_ServReqInit
  Function : 在GMM-SERVICE-REQUEST-INITIATED状态下收到DETACH_REQUEST的处理
  Input    : VOS_UINT8     ucDetachType     detach类型
             VOS_UINT8     ucGmmCause       detach原因
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.08  新规作成
    2.日    期   : 2015年6月4日
      作    者   : z00161729
      修改内容   : 24008 23122  R11 CR升级项目修改
*******************************************************************************/
VOS_VOID Gmm_RcvDetachRequestMsg_ServReqInit(
                                         VOS_UINT8      ucDetachType,           /* detach类型                               */
                                         VOS_UINT8      ucGmmCause              /* detach原因                               */
                                         )
{
    /* 24008_CR1598R2_(Rel-9)_C1-103557 24008 4.7.4.2.4描述如下:
    If the GPRS Detach Request message contains detach type "re-attach not required"
    and GMM cause  #2 "IMSI unknown in HLR", the network will follow the procedure as
    described below for the detach type "IMSI detach".
    GPRS detach containing detach type "IMSI detach":
    If the network receives a SERVICE REQUEST message before the network initiated
    GPRS detach procedure has been completed, the network shall progress both
    procedures.*/
    if ((GMM_NET_DETACH_REATTACH_NOT_REQUIRED == ucDetachType)
     && (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR == ucGmmCause))
    {
        ucDetachType = GMM_NET_DETACH_IMSI_DETACH;
    }

    Gmm_TimerStop(GMM_TIMER_T3317);                                             /* 停T3317                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */
    Gmm_TimerStop(GMM_TIMER_PROTECT);                                           /* 停保护Timer                              */

    g_GmmReqCnfMng.ucCnfMask = 0;                                               /* 清除等待CNF标志                          */
    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* 清除当前进行的specific过程               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvDetachRequestMsg_ServReqInit:INFO: specific procedure ended");

    switch (ucDetachType)
    {                                                                           /* 判断detach类型进行不同处理               */
    case GMM_NET_DETACH_REATTACH_NOT_REQUIRED:                                  /* "re-attach not required"                 */
        Gmm_ComCnfHandle();

        Gmm_NetInitNotRequiredDetach(ucGmmCause);                               /* 调用"re-attach not required"的公共处理   */
        break;
    case GMM_NET_DETACH_REATTACH_REQUIRED:                                      /* "re-attach required"                     */
        Gmm_ComCnfHandle();

        Gmm_NetInitRequiredDetach();                                            /* 调用re-attach required的处理             */
        break;

    case GMM_NET_DETACH_IMSI_DETACH:                                            /* IMSI detach                              */
        /* Gmm_ComCnfHandle函数会清除sm缓存，imsi detach场景会立即发rau，不清sm
           缓存rau带follow on rau成功后可处理缓存发起sm业务请求 */
        Gmm_NetInitImsiDetach();                                                /* ??IMSI detach???                    */
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachRequestMsg_ServReqInit:WARNING: Detach Type is Abnormal");
        break;
    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvDetachRequestMsg_RegNmlServ
  Function : 在GMM-REGISTERED.NORMAL-SERVICE状态下收到DETACH_REQUEST的处理
  Input    : VOS_UINT8     ucDetachType     detach类型
             VOS_UINT8     ucGmmCause       detach原因
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.08  新规作成
*******************************************************************************/
VOS_VOID Gmm_RcvDetachRequestMsg_RegNmlServ(
                                        VOS_UINT8      ucDetachType,                /* detach类型                               */
                                        VOS_UINT8      ucGmmCause                   /* detach原因                               */
                                        )
{
    switch (ucDetachType)
    {                                                                           /* 判断detach类型进行不同处理               */
    case GMM_NET_DETACH_REATTACH_NOT_REQUIRED:                                  /* "re-attach not required"                 */
        Gmm_NetInitNotRequiredDetach(ucGmmCause);                               /* 调用"re-attach not required"的公共处理   */
        break;
    case GMM_NET_DETACH_REATTACH_REQUIRED:                                      /* "re-attach required"                     */
        Gmm_NetInitRequiredDetach();                                            /* 调用re-attach required的处理             */
        break;
    case GMM_NET_DETACH_IMSI_DETACH:                                            /* IMSI detach                              */
        Gmm_NetInitImsiDetach();                                                /* 调用IMSI detach的处理                    */
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachRequestMsg_RegNmlServ:WARNING: Detach Type is Abnormal");
        break;
    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvDetachRequestMsg_RegAtmpToUpdtMm
  Function : 在REGISTERED.ATTEMPTING-TO-UPDATE-MM状态下收到DETACH_REQUEST的处理
  Input    : VOS_UINT8     ucDetachType     detach类型
             VOS_UINT8     ucGmmCause       detach原因
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.08  新规作成
*******************************************************************************/
VOS_VOID Gmm_RcvDetachRequestMsg_RegAtmpToUpdtMm(
                                             VOS_UINT8      ucDetachType,           /* detach类型                               */
                                             VOS_UINT8      ucGmmCause              /* detach原因                               */
                                             )
{
    Gmm_RcvDetachRequestMsg_RegNmlServ(ucDetachType, ucGmmCause);
}

/*******************************************************************************
  Module   : Gmm_RcvDetachRequestMsg_RegImsiDtchInit
  Function : 在REGISTERED.IMSI-DETACH-INITIATED状态下收到DETACH_REQUEST的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.08  新规作成
    2.日    期   : 2013年6月8日
      作    者   : w00167002
      修改内容   : V9R1_SVLTE:代码走读发现:
                   原先调用函数Gmm_RcvDetachRequestMsg_DeregInit(ucDetachType, ucGmmCause);
                   如果当前是CS域的DETACH，却设置PS不准许注册.
*******************************************************************************/
VOS_VOID Gmm_RcvDetachRequestMsg_RegImsiDtchInit(
    VOS_UINT8                           ucDetachType,           /* detach类型                               */
    VOS_UINT8                           ucGmmCause              /* detach原因                               */
)
{



    NAS_MSG_STRU    *pDetachAccept;                                             /* 定义指针                                 */

    pDetachAccept = Gmm_DetachAcceptMsgMake();                                  /* 调用函数制作detach accept消息            */

    Gmm_TimerStop(GMM_TIMER_T3321);

    switch (ucDetachType)
    {                                                                           /* 判断detach类型进行不同处理               */
        case GMM_NET_DETACH_REATTACH_NOT_REQUIRED:                              /* "re-attach not required"                 */
            Gmm_NetInitNotRequiredDetach(ucGmmCause);                           /* 调用"re-attach not required"的公共处理   */
            break;

        case GMM_NET_DETACH_REATTACH_REQUIRED:                                  /* "re-attach required"                     */

            /* 设置CS不准许标志，这样不会发起联合ATTACH */
            if (GMM_WAIT_CS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_CS_DETACH))
            {
                NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            }

            Gmm_NetInitRequiredDetach();                                        /* 调用re-attach required的处理             */
            break;

        case GMM_NET_DETACH_IMSI_DETACH:                                        /* IMSI detach                              */
            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachAccept);        /* 发送RRMM_DATA_REQ(detach accept消息)     */
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            Gmm_SndMmcNetworkDetachInd(ucDetachType, ucGmmCause);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_RcvDetachRequestMsg_RegImsiDtchInit: INVALID DETACH TYPE!");
            break;
    }
    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }


    return;
}

/*******************************************************************************
  Module   : Gmm_NetInitNotRequiredDetach
  Function : 网侧发起的类型为reattach not required的detach的处理
  Input    : VOS_UINT8  ucGmmCause        detach的原因值
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.08  新规作成
    2. 日    期   : 2009年06月22日
       作    者   : l00130025
       修改内容   : 问题单号:AT2D12541,【IOT测试】网络下发Detach(类型为 Re-attach not required)后，UE又重新发起attach请求
    3. 日    期   : 2009年09月07日
       作    者   : l65478
       修改内容   : 问题单号:AT2D13980,网络detach后，会出现PDP持续无法激活的问题
    4.日    期   : 2012年9月25日
      作    者   : h00216089
      修改内容   : DTS2012090304976:调整，网侧Detach(re-attach not required)后，MM定时器超时发起LU，
                   LU结束后收到系统消息GMM不会再发起Attach
    5.日    期   : 2015年6月3日
      作    者   : z00161729
      修改内容   : 24008 23122 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID Gmm_NetInitNotRequiredDetach(
                                  VOS_UINT8         ucGmmCause                      /* detach的原因值                           */
                                  )
{
    switch (ucGmmCause)
    {                                                                           /* 根据原因值不同进行不同处理               */
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:                                      /* 原因值2                                  */
        Gmm_Com_Cause2Detach();
        break;
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:                                               /* 原因值3                                  */
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:                                               /* 原因值6                                  */
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:                    /* 原因值8                                  */
        Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                                /* 调用状态的公共处理                       */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask  &= ~GMM_UEID_IMSI;              /* 清除IMSI存在MASK                         */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);/* Update status更新为GU2                   */
        break;
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:                                      /* 原因值7                                  */
        Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                                /* 调用状态的公共处理                       */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask  &= ~GMM_UEID_IMSI;              /* 清除IMSI存在MASK                         */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);  /* Update status更新为GU2                  */
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:                                           /* 原因值11                                 */
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* 调用状态的公共处理                       */
        g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_PLMN;               /* 设置禁止注册列表标志                     */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);  /* Update status更新为GU3                   */

        /* 24008_CR1229R1_(Rel-8)_C1-085365 24008 4.7.4.2.2章节描述如下:#11 The MS shall delete any RAI or LAI,
        P-TMSI, P-TMSI signature and GPRS ciphering key sequence number, shall set
        the GPRS update status to GU3 ROAMING NOT ALLOWED (and shall store it according to subclause 4.1.3.2)
        and shall reset the GPRS attach attempt counter. The new GMM state is GMM-DEREGISTERED.*/
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;
        break;
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:                                             /* 原因值12                                 */
        g_GmmGlobalCtrl.ucLaNotAllowFlg = GMM_TRUE;
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* 调用状态的公共处理                       */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);  /* Update status更新为GU3                   */
        g_GmmAttachCtrl.ucAttachAttmptCnt  = 0;                                 /* ATTACH ATTEMPT COUNTER RESET             */
        g_GmmGlobalCtrl.SysInfo.ucForbMask |=
                                        GMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS;      /* 设置禁止注册列表标志                     */
        break;
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:                                           /* 原因值13                                 */
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:                                          /* 原因值15                                 */
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* 调用状态的公共处理                       */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);  /* Update status更新为GU3                   */
        g_GmmAttachCtrl.ucAttachAttmptCnt  = 0;                                 /* ATTACH ATTEMPT COUNTER RESET             */
        g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_LA_FOR_ROAM;        /* 设置禁止注册列表标志                     */
        break;
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:                              /* 原因值14                                 */
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* 调用状态的公共处理                       */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);  /* Update status更新为GU3                   */
        g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_PLMN_FOR_GPRS;      /* 设置禁止注册列表标志                     */

        /* 24008_CR1229R1_(Rel-8)_C1-085365 24008 4.7.4.2.2章节描述如下:#14 The MS shall delete any RAI or LAI,
        P-TMSI, P-TMSI signature and GPRS ciphering key sequence number, shall set
        the GPRS update status to GU3 ROAMING NOT ALLOWED (and shall store it according to subclause 4.1.3.2)
        and shall reset the GPRS attach attempt counter. The new GMM state is GMM-DEREGISTERED.*/
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_NetInitNotRequiredDetach:WARNING: GMM Cause is Abnormal");
        ucGmmCause = NAS_MML_REG_FAIL_CAUSE_NULL;                                         /* 将原因值置为空                           */
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                         /* 调用状态的公共处理                       */
        g_GmmGlobalCtrl.ucRcvNetDetachFlg = VOS_TRUE;
        if (VOS_FALSE == NAS_MML_GetPsAutoAttachFlg())
        {
            NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );
        }
        break;
    }

    if (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR != ucGmmCause)
    {                                                                           /* 原因值不等于2                            */
        Gmm_Com_CauseDetach(ucGmmCause);                                        /* 调用原因值有效且不是2的公共处理          */
    }

    if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
     && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
    {
        NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );
    }

    return;                                                                     /* 返回                                     */
}


/*******************************************************************************
  Module   : Gmm_Com_Cause2Detach
  Function : Reattch not required + #2的处理
  Input    : VOS_VOID
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.张志勇  2003.12.08  新规作成
  2.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
 3 .日    期   : 2013年08月16日
    作    者   : l65478
    修改内容   : DTS2013092202614,G CCO到W失败回退到G,在G下通知了GAS进入了REDAY态
*******************************************************************************/
VOS_VOID Gmm_Com_Cause2Detach(VOS_VOID)
{
    NAS_MSG_STRU    *pDetachAccept;                                             /* 定义消息指针                             */

    pDetachAccept = Gmm_DetachAcceptMsgMake();                                  /* 调用函数制作detach accept消息            */

    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachAccept);                /* 发送RRMM_DATA_REQ(detach accept消息)     */
    Gmm_SndMmcNetworkDetachInd(NAS_MMC_GMM_NT_DETACH_NOATTACH,
                               NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);               /* 发送MMCGMM_NETWORK_DETACH_IND            */
    NAS_GMM_SndMmNetworkDetachInd(GMMMM_NET_DETACH_NOATTACH,
                                  NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {                                                                           /* 当前状态为REGISTERED_INITIATED           */
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* 重新进行ATTACH                           */                                                  /* 重新进行attach                           */
    }
    else if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
    {                                                                           /* 当前状态为RAU_INITIATED                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 重新进行RAU                              */
    }
    else if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                            /* 调用状态的公共处理                       */
        if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* T3302正在运行                            */
            Gmm_TimerPause(GMM_TIMER_T3302);                                    /* 挂起T3302                                */
        }
        else if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* T3311正在运行                            */
            Gmm_TimerPause(GMM_TIMER_T3311);                                    /* 挂起T3311                                */
        }
        else
        {
        }
    }
    else
    {
    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_Com_CauseDetach
  Function : Reattch not required + 非#2的处理
  Input    : VOS_UINT8  ucGmmCause        detach的原因值
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.张志勇  2003.12.09  新规作成
  2.日    期   : 2007年01月04日
    作    者   : s46746
    修改内容   : 创建，根据问题单号：A32D08235
  3.日    期   : 2009年09月07日
    作    者   : l65478
    修改内容   : 根据问题单号：AT2D13980,网络detach后，重新attach失败，因为tlli没有去指派
  4.日    期   : 2010年01月03日
    作    者   : o00132663
    修改内容   : 问题单号：xxxx,NAS R7协议升级，引入监控PS信令链接释放定时器T3340
  5.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  6.日    期   : 2013年08月16日
    作    者   : l65478
    修改内容   : DTS2013092202614,G CCO到W失败回退到G,在G下通知了GAS进入了REDAY态
*******************************************************************************/
VOS_VOID Gmm_Com_CauseDetach(
                         VOS_UINT8  ucGmmCause                                      /* detach的原因值                           */
                         )
{
    NAS_MSG_STRU    *pDetachAccept;                                             /* 定义消息指针                             */

    pDetachAccept = VOS_NULL_PTR;                                                       /* 初始化消息指针                           */

    Gmm_TimerStop(GMM_TIMER_ALL);                                               /* 停止所有的GMM TIMER                      */

    pDetachAccept = Gmm_DetachAcceptMsgMake();                                  /* 调用函数制作detach accept消息            */

    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachAccept);                /* 发送RRMM_DATA_REQ(detach accept消息)     */
    Gmm_SndMmcNetworkDetachInd(NAS_MMC_GMM_NT_DETACH_NOATTACH, ucGmmCause);         /* 发送MMCGMM_NETWORK_DETACH_IND            */
    NAS_GMM_SndMmNetworkDetachInd(GMMMM_NET_DETACH_NOATTACH, ucGmmCause);
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    if (NAS_MML_REG_FAIL_CAUSE_NULL != ucGmmCause)
    {                                                                           /* 原因值有效                               */
        Gmm_DelPsLocInfoUpdateUsim();
    }

    NAS_GMM_CheckCauseToStartT3340(ucGmmCause);

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_TimerStop(GMM_TIMER_T3314);

        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;

        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        if(GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
        {
            Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_USER);
        }
    }
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_NetInitRequiredDetach
  Function : 网侧启动的类型为reattach required的detach过程处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.张志勇  2003.12.09  新规作成
  2.日    期    : 2009年9月03日
    作    者    : l65478
    修改内容    : created AT2D14239,detach完成后,再次发起ATTATCH REQ时,GAS使用旧的TLLI建立的TBF发送数据,没有及时使用新的TLLI,导致MS和仪器侧维护的TLLI不一致,从而导致GAS因为TLLI不匹配丢弃了建立下行TBF的指派命令,最终导致用例失败
  3.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  4.日    期   : 2013年08月16日
    作    者   : l65478
    修改内容   : DTS2013092202614,G CCO到W失败回退到G,在G下通知了GAS进入了REDAY态
*******************************************************************************/
VOS_VOID Gmm_NetInitRequiredDetach(VOS_VOID)
{
    NAS_MSG_STRU    *pDetachAccept;                                             /* 定义消息指针                             */

    pDetachAccept = VOS_NULL_PTR;                                                       /* 初始化消息指针                           */

    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                             /* 调用状态的公共处理                       */
    Gmm_SndMmcNetworkDetachInd(NAS_MMC_GMM_NT_DETACH_REATTACH, NAS_MML_REG_FAIL_CAUSE_NULL);  /* 通知MMC GMM进行的detach                  */
    NAS_GMM_SndMmNetworkDetachInd(GMMMM_NET_DETACH_REATTACH,
                                  NAS_MML_REG_FAIL_CAUSE_NULL);
    pDetachAccept = Gmm_DetachAcceptMsgMake();                                  /* 调用函数制作detach accept消息            */

    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachAccept);                /* 发送RRMM_DATA_REQ(detach accept消息)     */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);
    Gmm_HoldBufferFree();                                                       /* 清除保留消息                             */
    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_USER);

        Gmm_TimerStop(GMM_TIMER_T3314);

        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;

        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
    }

    if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
     && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
    {
        NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );

        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    }
    else
    {
        if(GMM_TRUE == GMM_IsCasGsmMode())
        {
            g_GmmGlobalCtrl.ulGmmAttachFlg = GMM_TRUE;
        }
        else
        {
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        }
    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_NetInitImsiDetach
  Function : 网侧启动的类型为IMSI detach的detach过程处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.张志勇  2003.12.09  新规作成
  2.日    期   : 2007年01月04日
    作    者   : s46746
    修改内容   : 创建，根据问题单号：A32D08235
  3.日    期   : 2009年05月23日
    作    者   : L65478
    修改内容   : 问题单号:AT2D06770,RAU失败，因为GRM建链的原因是DATA，实际应该是信令
  4.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  5.日     期  : 2011年9月26日
    作    者   : c00173809
    修改内容   : DTS2011092001088,GCF 44.2.2.2.4测试失败
  6.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
*******************************************************************************/
VOS_VOID Gmm_NetInitImsiDetach(VOS_VOID)
{
    NAS_MSG_STRU    *pDetachAccept;                                             /* 定义消息指针                             */

    pDetachAccept = VOS_NULL_PTR;                                                       /* 初始化消息指针                           */

    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {                                                                           /* CS域注册                                 */
        Gmm_SndMmcNetworkDetachInd(NAS_MMC_GMM_NT_DETACH_IMSI, NAS_MML_REG_FAIL_CAUSE_NULL);  /* 发送MMCGMM_NETWORK_DETACH_IND            */
        NAS_GMM_SndMmNetworkDetachInd(GMMMM_NET_DETACH_IMSI,
                                      NAS_MML_REG_FAIL_CAUSE_NULL);
        pDetachAccept = Gmm_DetachAcceptMsgMake();                              /* 调用函数制作detach accept消息            */

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachAccept);            /* 发送RRMM_DATA_REQ(detach accept消息)     */

        g_GmmGlobalCtrl.ucDetachAcceptedFlg = VOS_TRUE;

        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
         && (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH); /* 调用RAU过程combined RAU with IMSI attach */
        }
        else if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
              && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
              && (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
        {
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_ATTACH_NORMAL;
        }
        else
        {
        }

        g_GmmGlobalCtrl.ucDetachAcceptedFlg = VOS_FALSE;
    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_DetachAcceptMsgMake
  Function : Detach accept消息制作
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : NAS_MSG_STRU *
  History  :
    1. 张志勇  2003.12.09  新规作成
*******************************************************************************/
NAS_MSG_STRU* Gmm_DetachAcceptMsgMake(VOS_VOID)
{
    NAS_MSG_STRU    *pDetachAccept;                                             /* 定义消息指针                             */

    pDetachAccept = VOS_NULL_PTR;                                                       /* 初始化消息指针                           */

    pDetachAccept = (NAS_MSG_STRU *)Gmm_MemMalloc(sizeof(NAS_MSG_STRU));        /* 申请内存空间                             */
    if (VOS_NULL_PTR == pDetachAccept)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
            "Gmm_DetachAcceptMsgMake:error: Alloc mem fail.");
        return pDetachAccept;
    }
    Gmm_MemSet(pDetachAccept, 0, sizeof(NAS_MSG_STRU));                         /* 将申请的内存空间清0                      */

    pDetachAccept->ulNasMsgSize = GMM_MSG_LEN_DETACH_ACCEPT;                    /* 消息长度                                 */
    pDetachAccept->aucNasMsg[0] = GMM_PD_GMM;                                   /* PD                                       */
    pDetachAccept->aucNasMsg[1] = GMM_MSG_DETACH_ACCEPT;                        /* message type                             */

    return pDetachAccept;                                                       /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvDetachAcceptMsg
  Function : GMM收到DETACH_ACCEPT的分发处理
  Input    : NAS_MSG_STRU   *pMsg  当前处理的消息
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1. 张志勇  2003.12.09  新规作成
  2. x51137 2006/4/28 A32D02889
  3.日    期   : 2006年11月9日
    作    者   : sunxibo id:46746
    修改内容   : 根据问题单号：A32D06822
  4.日    期   : 2009年05月23日
    作    者   : L65478
    修改内容   : 问题单号:AT2D06770,RAU失败，因为GRM建链的原因是DATA，实际应该是信令
  5.日    期   : 2010年10月29日
    作    者   : l00167671/罗开辉
    修改内容   : 问题单号：DTS2010100802035,添加W模时对LLC的清理
  6.日    期   : 2010年11月24日
    作    者   : 王毛 00166186
    修改内容   : 根据问题单号DTS2010112205253,DEFAULT分支，错误原因值填写不正确
  7.日    期   : 2010年12月03日
    作    者   : w00166186
    修改内容   : DTS2010112403161 搜网整理发现问题
  8.日    期   : 2012年3月3日
    作    者   : z00161729
    修改内容   : V7R1 C50 支持ISR修改,T3312启动停止超时均需通知L
  9.日    期   : 2012年8月25日
    作    者   : m00217266
    修改内容   : 删除GMM_SaveErrCode，添加Gmm_Save_Detach_Cause，
                保存导致Attach失败的原因值
  *******************************************************************************/
VOS_VOID Gmm_RcvDetachAcceptMsg(
                            NAS_MSG_FOR_PCLINT_STRU        *pMsg
                            )
{
    NAS_MSG_STRU                       *pGmmStatus;
    VOS_UINT8                           ucForceToStandby;
    VOS_UINT8                           ucDetachType=0x0;

#if (FEATURE_LTE == FEATURE_ON)
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();
#endif

    if (GMM_MSG_LEN_DETACH_ACCEPT > pMsg->ulNasMsgSize)
    {                                                                           /* 消息中必选项的长度不够长                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachAcceptMsg:WARNING: Length of DETACH ACCEPT is invalid");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;                                                                 /* 返回                                     */
    }

    ucForceToStandby = (VOS_UINT8)(pMsg->aucNasMsg[2] & 0x0F);
    if (1 == ucForceToStandby)
    {
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_TRUE;
    }
    else if (0 == ucForceToStandby)
    {
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachAcceptMsg:WARNING: DETACH ACCEPT is semantically incorrect");
        /*pGmmStatus = Gmm_GmmStatusMsgMake(*/
        /*    NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);*/

        /*Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);*/
        /*return;*/
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 判断当前状态进行不同处理                 */
    case GMM_DEREGISTERED_INITIATED:                                            /* GMM-DEREGISTERED-INITIATED               */
        Gmm_RcvDetachAcceptMsg_DeregInit();                                     /* 调用该状态下的处理                       */
        ucDetachType = GMM_NET_DETACH_REATTACH_NOT_REQUIRED;
        break;
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:                                  /* GMM-REGISTERED.IMSI-DETACH-INITIATED     */
        Gmm_RcvDetachAcceptMsg_RegImsiDtchInit();                               /* 调用该状态下的处理                       */
        ucDetachType = GMM_NET_DETACH_IMSI_DETACH;
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachAcceptMsg:WARNING: DETACH ACCEPT is unexpected");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_MSG_NOT_COMPATIBLE);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        break;
    }

    if (ucDetachType != GMM_NET_DETACH_IMSI_DETACH)
    {
        NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_PS_DETACH);
    }

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {

        if ( ucDetachType == GMM_NET_DETACH_IMSI_DETACH )
        {
            if ( GMM_TRUE == gstGmmCasGlobalCtrl.ucFtsFlg )
            {
                gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;

                if ( 0xffffffff != gstGmmCasGlobalCtrl.ulReadyTimerValue )
                {
                     gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
                     Gmm_TimerStop(GMM_TIMER_T3314);
                     Gmm_TimerStart(GMM_TIMER_T3312);
                     NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
                }
            }
        }
        else/* detach PS */
        {
            Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ALL);                                                 /* 去指配TLLI，释放LLC层数据 */
            Gmm_TimerStop(GMM_TIMER_T3314);
            gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;
            gstGmmCasGlobalCtrl.ulReadyTimerValue = 44000;/* default 44s */

#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
            }

            /* detach ps后如果ISR激活，需要去激活ISR */
            if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
            {
                NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pstRplmnCfgInfo->aucLastImsi);
                Gmm_TimerStop(GMM_TIMER_T3323);

                /* ISR去激活，需要更新pdp激活是在ISR激活前激活的 */
                NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
            }
#endif
            Gmm_TimerStop(GMM_TIMER_T3312);
            NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        }

    }
    else
    {
        if (GMM_NET_DETACH_IMSI_DETACH != ucDetachType)
        {
            Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ALL);
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
            }

            /* detach ps后如果ISR激活，需要去激活ISR */
            if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
            {
                NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pstRplmnCfgInfo->aucLastImsi);
                Gmm_TimerStop(GMM_TIMER_T3323);

                /* ISR去激活，需要更新pdp激活是在ISR激活前激活的 */
                NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
            }
#endif
            Gmm_TimerStop(GMM_TIMER_T3312);
        }
    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvDetachAcceptMsg_DeregInit
  Function : 在GMM-REGISTERED.IMSI-DETACH-INITIATED下收到DETACH_ACCEPT的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1. 张志勇  2003.12.09  新规作成
  2. 日    期   : 2006年11月20日
     作    者   : s46746
     修改内容   : 创建，根据问题单号：A32D07433
  3. 日    期   : 2011年07月13日
     作    者   : w00166186
     修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  4.日    期   : 2011年7月27日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  5. 日    期   : 2012年1月12日
     作    者   : w00166186
     修改内容   : DTS2011122704039:开机搜网后CS注册被拒#12,PS注册被拒#14，在ON
                   PLMN状态，服务域被设置为不支持GMM需要将服务域不支持信息通知给MMC.

  6.日    期   : 2013年8月7日
    作    者   : w00167002
    修改内容   : DTS2013080207367:在CS only时候，用户发起PDP激活，网络模式I时候，
                 会触发联合注册.用户发起PDP去激活，会导致PS域的去注册。收到网侧
                 的去注册成功后需要通知MM，否则MM当前在NORMAL SERVICE状态，不
                 触发T3212定时器的启动，长时间可能导致丢寻呼.
*******************************************************************************/
VOS_VOID Gmm_RcvDetachAcceptMsg_DeregInit(VOS_VOID)
{
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* 停T3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    if (GMM_DETACH_NORMAL_NETMODE_CHANGE != g_GmmGlobalCtrl.ucSpecProc)
    {
        NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );             /* 置PS域的attach禁止标志                   */
    }
    /*Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);*/                             /* 调用状态的公共处理                       */
    if (GMM_UEID_P_TMSI_SIGNATURE
        == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
    {                                                                           /* DETACH成功且使用了P_TMSI_SIGNATURE       */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;   /* 清除P_TMSI_SIGNATURE                     */
        NAS_MML_InitUeIdPtmsiSignatureInvalid();
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
    }

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
        /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();
        }

        else
        {
            /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
            NAS_GMM_SndMmGprsDetachComplete();
        }

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
    }
    else if (VOS_OK != Mm_StartRelTimer(&g_stGmmProtectRrRelTimer,
                                            WUEPS_PID_GMM,
                                            GMM_TIMER_PROTECT_FOR_RR_REL_VALUE,
                                            GMM_TIMER_PROTECT_FOR_RR_REL,
                                            0,
                                            VOS_RELTIMER_NOLOOP))
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
        /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();
        }
        else
        {
            /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
            NAS_GMM_SndMmGprsDetachComplete();
        }

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachAcceptMsg_DeregInit:WARNING: Gmm Start Timer fail.");
    }
    else
    {
        g_GmmTimerMng.ulTimerRunMask |= (0x00000001 << GMM_TIMER_PROTECT_FOR_RR_REL);
    }

    /* 向MMC发送PS注册结果 */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvDetachAcceptMsg_DeregInit:INFO: specific procedure ended");
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvDetachAcceptMsg_RegImsiDtchInit
  Function : 在GMM-DEREGISTERED-INITIATED状态下收到DETACH_ACCEPT的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1. 张志勇  2003.12.09  新规作成
  2. 日    期   : 2011年07月13日
     作    者   : w00166186
     修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  3.日    期   : 2011年7月27日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
*******************************************************************************/
VOS_VOID Gmm_RcvDetachAcceptMsg_RegImsiDtchInit(VOS_VOID)
{
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* 停T3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);                               /* 调用状态的公共处理                       */
    if (GMM_UEID_P_TMSI_SIGNATURE
        == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
    {                                                                           /* DETACH成功且使用了P_TMSI_SIGNATURE       */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;   /* 清除P_TMSI_SIGNATURE                     */
        NAS_MML_InitUeIdPtmsiSignatureInvalid();
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
    }
    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    g_GmmGlobalCtrl.ucSpecProc               = GMM_NULL_PROCEDURE;              /* 清除当前进行的specific过程               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvDetachAcceptMsg_RegImsiDtchInit:INFO: specific procedure ended");
    return;                                                                     /* 返回                                     */
}

/*****************************************************************************
 函 数 名  : NAS_GMM_SetAttach2DetachErrCode
 功能描述  : 保存导致GMM由Attach状态切换到Detach状态的原因
 输入参数  : GMM_SM_CAUSE_ENUM_UINT16
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月15日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_ENUM_UINT16 enCause)
{
    g_GmmGlobalCtrl.enAttach2DetachCause = enCause;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_GetAttach2DetachErrCode
 功能描述  : 获取导致GMM由Attach状态切换到Detach状态的原因
 输入参数  : 无
 输出参数  : GMM_SM_CAUSE_ENUM_UINT16
 返 回 值  : GMM_SM_CAUSE_ENUM_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月15日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
GMM_SM_CAUSE_ENUM_UINT16 NAS_GMM_GetAttach2DetachErrCode(VOS_VOID)
{
    return g_GmmGlobalCtrl.enAttach2DetachCause;
}



/*****************************************************************************
 函 数 名  : NAS_GMM_ChangeDetachCauseAvoidInvalidSim
 功能描述  : 网络Detach拒绝原因值自适应
 输入参数  : VOS_UINT8 *pucRcvMsg  指向原始拒绝原因值的指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : h00285180
    修改内容   : 拒绝原因值PhaseII DTS2014110307415
*****************************************************************************/
VOS_VOID NAS_GMM_ChangeDetachCauseAvoidInvalidSim(VOS_UINT8 *pucRcvMsg)
{
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId    = VOS_NULL_PTR;
    VOS_UINT32                          bIsRegisteredInHplmn = VOS_FALSE;

    /* 增加测试卡保护，测试卡时不修改，直接返回 */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_ChangeDetachCauseAvoidInvalidSim: The sim is Test card");
        return;
    }

    /* 取得当前驻留的PLMN ID */
    pstCurrCampPlmnId    = NAS_MML_GetCurrCampPlmnId();
    bIsRegisteredInHplmn = NAS_MML_ComparePlmnIdWithHplmn(pstCurrCampPlmnId);

    NAS_MML_SetOriginalRejectCause(*pucRcvMsg);
    if (VOS_TRUE == bIsRegisteredInHplmn)
    {
        /* HPLMN */
        NAS_GMM_HandleHplmnRejCauseChange(NAS_MML_CHANGE_REJ_TYPE_DETACH, pucRcvMsg);
    }
    else
    {
        /* VPLMN */
        NAS_GMM_HandleVplmnRejCauseChange(NAS_MML_CHANGE_REJ_TYPE_DETACH, pucRcvMsg);
    }
}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

