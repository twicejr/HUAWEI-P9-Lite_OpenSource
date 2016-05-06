/*******************************************************************************
  Copyright     : 2005-2007, Huawei Tech. Co., Ltd.
  File name     : GmmComm.c
  Description   : GMM COMMON PROCEDURE功能相关处理用源文件
  Function List :
    01.   Gmm_Attach_Prepare
    02.   Gmm_Au_MacAutnWrong
    03.   Gmm_AuCntFail
    04.   Gmm_AuthenAndCipherFailureMsgMake
    05.   Gmm_AuthenAndCipherResponseMsgMake
    06.   Gmm_Com_RcvAgentUsimAuthenticationCnf
    07.   Gmm_IdentityResponseMsgMake
    08.   Gmm_PagingInd_common
    09.   Gmm_PtmsiReallocationCompleteMsgMake
    10.   Gmm_RcvAgentUsimAuthenticationCnf
    11.   Gmm_RcvAuthenAndCipherRejectMsg
    12.   Gmm_RcvAuthenAndCipherRequestMsg
    13.   Gmm_RcvGmmInformationMsg
    14.   Gmm_RcvIdentityRequestMsg
    15.   Gmm_RcvPtmsiReallocationCommandMsg
    16.   Gmm_RcvRrmmPagingInd
    17.   Gmm_RcvRrmmPagingInd_DeregInit
    18.   Gmm_RcvRrmmPagingInd_RauInit
    19.   Gmm_RcvRrmmPagingInd_RegNmlServ
    20.   Gmm_RcvRrmmPagingInd_ServReqInit
    21.   Gmm_Start_StopedRetransmissionTimer
    22.   Gmm_Stop_RetransmissionTimer
  History       :
    1.  张志勇  2003.12.05  新规作成
    2.  s46746 2006-03-08 根据问题单A32D02368修改
    3.  l40632 2006-04-11 根据问题单A32D03039修改
    4.  x51137 2006/4/13 A32D03056
    5.  x51137 2006/4/28 A32D02889
    6.  s46746 2006-05-08 根据问题单A32D03487修改
    7.  日    期   : 2006年9月13日
        作    者   : liurui id:40632
        修改内容   : 根据问题单号：A32D05596
    8.  日    期   : 2006年10月8日
        作    者   : luojian id:60022475
        修改内容   : 根据问题单号：A32D06583

    9. x51137 2006/11/2 A32D06628
   10.日    期  : 2006年11月25日
      作    者  : luojian id:60022475
      修改内容  : 问题单号:A32D06583
   11.日    期  : 2007年01月13日
      作    者  : s46746
      修改内容  : 根据问题单号：A32D08326
   12.日    期   : 2007年01月16日
      作    者   : s46746
      修改内容   : 根据问题单号：A32D08381
   13.日    期   : 2007年05月11日
      作    者   : luojian id:60022475
      修改内容   : 问题单号:A32D10713
   14.日    期   : 2007年06月05日
      作    者   : s46746
      修改内容   : 问题单号:A32D11127,向卡发鉴权请求时，判断是否正在等待卡回复鉴权响应，如果有，
                   则清除等待标志，也不向卡发鉴权请求，如果没有，则向卡发送鉴权请求
   15.日    期   : 2007年06月16日
      作    者   : luojian id:60022475
      修改内容   : 根据问题单号：A32D11635,gas上报GPRS RESUME FAILURE时,仍然通知
                   RABM 恢复成功,如果存在PDP激活时,发起RAU,如果在这个RAU过程中系
                   统消息指示RAI发生改变就不再发起RAU.
   16.日    期   : 2007年07月27日
      作    者   : luojian id:60022475
      修改内容   : 问题单号:A32D12606,support GMM identity type:TMSI
   17.日    期   : 2007年09月30日
      作    者   : s46746
      修改内容   : 问题单号:A32D12878,在register状态支持PTMSI的重分配处理
   18.日    期   : 2007年10月13日
      作    者   : s46746
      修改内容   : 根据问题单号：A32D13060
   19.日    期   : 2007年10月29日
      作    者   : s46746
      修改内容   : 根据问题单号：A32D13271
   20.日    期   : 2007年11月22日
      作    者   : s46746
      修改内容   : 根据问题单号：A32D13475,修改异系统改变后指派的old TLLI和开机加密密钥为全0问题
   21.日    期   : 2007年12月14日
      作    者   : s46746
      修改内容   : 问题单A32D13638，保证进行RAU之前不向网侧发送其它数据，并且RAU不成功，不恢复层2
   22.日    期   : 2007年12月18日
      作    者   : s46746
      修改内容   : 问题单A32D13913，GMM在进行鉴权过程中，如果rand相同，也需要指
                   示层2加密算法和密钥
   23.日    期   : 2007年12月28日
      作    者   : s46746
      修改内容   : 根据问题单号：A32D13954,修改GMM在2G3过程中缓存消息机制
   24.日    期   : 2008年07月18日
      作    者   : s46746
      修改内容   : 根据问题单号：AT2D04481,连续两次相同鉴权请求，不应被中断
   25.日    期   : 2008年9月23日
      作    者   : o00132663
      修改内容   : 根据问题单号：AT2D05839,清除无用全局变量 ucRlsMsgFlg和状态GMM_REGISTERED_WAIT_FOR_RAU
   26.日    期   : 2008年10月15日
      作    者   : s46746
      修改内容   : 根据问题单号：AT2D06216,GMM连续接收到两条相同鉴权请求时，
                   卡回复第一条鉴权请求，GMM没有将鉴权结果发回到网络侧
   27.日    期   : 2009年02月07日
      作    者   : x00115505
      修改内容   : 根据问题单号：AT2D06771,2G PS域鉴权，没有得到卡的回复之前
                   又收到网侧同样的鉴权消息，MS直接回复鉴权响应。
   28.日    期   : 2009年5月8日
      作    者   : x00115505
      修改内容   : AT2D11792,执行GCF测试用例8.2.2.50时由于GMM环回时不响应paging消息导致用例失败。
   29.日    期   : 2009年6月30日
      作    者   : s46746
      修改内容   : AT2D12561,3G2情形GPRS下未启动加密，NAS指派层2加密算法后，层2对上行数据进行了加密
   30.日    期   : 2009年08月24日
      作    者   : x00115505
      修改内容   : AT2D14023,测试GCF用例44.2.2.1.9失败
   31.日    期   : 2010年3月2日
      作    者   : o00132663
      修改内容   : NAS R7协议升级项目，合入链路释放增强处理等特性
*******************************************************************************/

#include "GmmInc.h"

#include "GmmCasGlobal.h"
#include "GmmCasGsm.h"
#include "GmmCasComm.h"
#include "GmmCasSend.h"
#include "GmmCasMain.h"
#include "GmmMmInterface.h"
#include "NasMmlCtx.h"
#include "NasGmmSndOm.h"

/* Added by l00167671 for NV拆分项目 , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV拆分项目 , 2013-05-17, end*/
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
#define    THIS_FILE_ID        PS_FILE_ID_GMM_COMM_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/

/*lint -save -e958 */

/*******************************************************************************
  Module   : Gmm_RcvRrmmPagingInd
  Function : 接收到RRMM_PAGING_IND原语后的处理
  Input    : VOS_VOID *pMsg    :RRMM_PAGING_IND原语首地址
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.08  新版作成
    2.日    期   : 2012年2月15日
      作    者   : w00166186
      修改内容   : CSFB&PPAC&ETWS&ISR 开发
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmPagingInd(
                          VOS_VOID *pMsg                                            /* RRMM_PAGING_IND原语首地址                */
                          )
{
    RRMM_PAGING_IND_STRU  *pPagingInd;                                          /* 指向RRMM_PAGING_IND_STRU结构的指针       */

    pPagingInd = (RRMM_PAGING_IND_STRU *)pMsg;
    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 根据GMM不同的状态，进行相应的处理        */
    case GMM_DEREGISTERED_INITIATED:
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
       Gmm_RcvRrmmPagingInd_DeregInit( pPagingInd);
       break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
       Gmm_RcvRrmmPagingInd_RauInit(pPagingInd);
       break;
    case GMM_SERVICE_REQUEST_INITIATED:
       Gmm_RcvRrmmPagingInd_ServReqInit(pPagingInd);
       break;
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_TC_ACTIVE:
    case GMM_REGISTERED_UPDATE_NEEDED:
       Gmm_RcvRrmmPagingInd_RegNmlServ(pPagingInd);
       break;
    default:
       PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmPagingInd:WARNING: g_GmmGlobalCtrl.ucState is Error");
       break;
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_PagingInd_common
  Function : 接收到RRMM_PAGING_IND原语后的一些公共处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.08  新版作成
    2.日    期   : 2012年2月15日
      作    者   : w00166186
      修改内容   : CSFB&PPAC&ETWS&ISR 开发
*******************************************************************************/
VOS_VOID Gmm_PagingInd_common(VOS_VOID)
{
    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* 等待鉴权响应                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护定时器                             */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;     /* 清除原语等待标志                         */
    }
    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);         /* 更新状态变为GU2                          */
    Gmm_DelPsLocInfoUpdateUsim();

    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                             /* 调用状态的公共处理                       */
    Gmm_SndMmcLocalDetachInd(NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);                    /* 发送MMCGMM_LOCAL_DETACH_IND()            */

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
        if (VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
        {
            Gmm_Attach_Prepare();                                                   /* 全局变量的清理工作，为attach作好准备     */
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                 /* 进行attach                               */
        }
        else
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
            /* 向MMC发送PS注册结果 */
            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                         GMM_MMC_ACTION_RESULT_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);
        }
    }
}

/*******************************************************************************
  Module   : Gmm_Attach_Prepare
  Function : 全局变量的清理工作，为attach作好准备
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1.  张志勇    2003.12.08  新版作成
*******************************************************************************/
VOS_VOID Gmm_Attach_Prepare(VOS_VOID)
{
    g_GmmGlobalCtrl.ucSpecProc           = GMM_NULL_PROCEDURE;                  /* 清空"当前进行的specific流程"             */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_Attach_Prepare:INFO: specific procedure ended");
    g_GmmGlobalCtrl.ucSpecProcHold       = GMM_NULL_PROCEDURE;                  /* 清空"保留的specific流程"                 */
    g_GmmGlobalCtrl.ucSpecProcInCsTrans  = GMM_NULL_PROCEDURE;                  /* 清空"CS通信中进行的specific流程"         */
    g_GmmGlobalCtrl.ucFollowOnFlg        = GMM_FALSE;                           /* 清空"信令延长使用标志"                   */
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk = 0;                                   /* 清buffer                                 */
    Gmm_TimerStop(GMM_TIMER_ALL);
    g_GmmReqCnfMng.ucCnfMask = 0;                                               /* 等待cnf的标志清为0                       */
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmPagingInd_DeregInit
  Function : 在GMM-DEREGISTERED-INITIATED状态下，收到RRMM_PAGING_IND原
             语后的处理
  Input    : RRMM_PAGING_IND_STRU  *ptr    :RRMM_PAGING_IND原语首地址
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.08  新版作成
    2.日    期   : 2006年12月5日
      作    者   : luojian 60022475
      修改内容   : Maps3000接口修改
    3.日    期   : 2012年2月15日
      作    者   : w00166186
      修改内容   : CSFB&PPAC&ETWS&ISR 开发
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmPagingInd_DeregInit(
                                    RRMM_PAGING_IND_STRU  *ptr                  /* RRMM_PAGING_IND原语首地址                */
                                    )
{
    RRMM_PAGING_IND_STRU    *pMsg;

    if (RRC_IMSI_GSM_MAP == ptr->ulPagingUeId)
    {                                                                           /* 寻呼的类型为IMSI                         */
        if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
            && (GMM_RRC_RRMM_EST_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
        {                                                                       /* 无信令且正在建立信令连接                 */
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk    |= GMM_MSG_HOLD_FOR_PAGING; /* 置消息被缓存的标志                       */
            pMsg = (RRMM_PAGING_IND_STRU *)Gmm_MemMalloc(sizeof(RRMM_PAGING_IND_STRU));
            if (VOS_NULL_PTR == pMsg)
            {
                  PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvRrmmPagingInd_DeregInit:ERROR: allocate memory error");
                  return;
            }
            Gmm_MemCpy(pMsg, ptr, sizeof(RRMM_PAGING_IND_STRU));
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging = (VOS_UINT32)pMsg;      /* 保留RRMM_PAGING _IND首地址               */
        }
        else
        {                                                                       /* 有信令或没有信令且还没建信令             */
            if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
                == (g_GmmReqCnfMng.ucCnfMask
                & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
            {                                                                   /* 等待鉴权响应                             */
                Gmm_TimerStop(GMM_TIMER_PROTECT);                               /* 停保护定时器                             */
                g_GmmReqCnfMng.ucCnfMask
                    &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                  /* 清除原语等待标志                         */
            }
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED); /* 更新状态变为GU2                          */
            Gmm_DelPsLocInfoUpdateUsim();
            Gmm_SndMmcLocalDetachInd(NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);

            if (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
            {
                Gmm_RcvDetachAcceptMsg_DeregInit();
            }
            else
            {
                Gmm_RcvDetachAcceptMsg_RegImsiDtchInit();
                Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

                if (VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
                {
                    Gmm_Attach_Prepare();                                           /* 全局变量的清理工作，为attach作好准备     */
                    Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
                }
                else
                {
                    Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
                }
            }
        }
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmPagingInd_DeregInit:WARNING: NOT RRC_IMSI_GSM_MAP");
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmPagingInd_RauInit
  Function : 在GMM-ROUTING-AREA-UPDATING-INITIATED状态下，收到
             RRMM_PAGING_IND原语后的处理
  Input    : RRMM_PAGING_IND_STRU *ptr    :RRMM_PAGING_IND原语首地址
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.08  新版作成
    2.  日    期   : 2006年12月5日
        作    者   : luojian 60022475
        修改内容   : Maps3000接口修改
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmPagingInd_RauInit(
                                  RRMM_PAGING_IND_STRU *ptr                     /* RRMM_PAGING_IND原语首地址                */
                                  )
{
    RRMM_PAGING_IND_STRU    *pMsg;

    if (RRC_IMSI_GSM_MAP == ptr->ulPagingUeId)
    {                                                                           /* 寻呼的类型为IMSI                         */
        if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
            && (GMM_RRC_RRMM_EST_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
        {                                                                       /* 无信令且正在建立信令连接                 */
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk    |= GMM_MSG_HOLD_FOR_PAGING; /* 置消息被缓存的标志                       */
            pMsg = (RRMM_PAGING_IND_STRU *)Gmm_MemMalloc(sizeof(RRMM_PAGING_IND_STRU));
            if (VOS_NULL_PTR == pMsg)
            {
                  PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvRrmmPagingInd_RauInit:ERROR: Allocate memory error");
                  return;
            }
            Gmm_MemCpy(pMsg, ptr, sizeof(RRMM_PAGING_IND_STRU));
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging = (VOS_UINT32)pMsg;            /* 保留RRMM_PAGING _IND首地址              */
        }
        else
        {                                                                       /* 有信令或没有信令且还没建信令             */
            Gmm_TimerStop(GMM_TIMER_T3330);                                     /* 停T3330                                  */
            Gmm_TimerStop(GMM_TIMER_T3318);                                     /* 停止T3318                                */
            Gmm_TimerStop(GMM_TIMER_T3320);                                     /* 停止T3320                                */

            Gmm_ComCnfHandle();
            Gmm_PagingInd_common();
        }
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmPagingInd_RauInit:WARNING: NOT RRC_IMSI_GSM_MAP");
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmPagingInd_ServReqInit
  Function : 在GMM-SERVICE-REQUEST-INITIATED状态下，收到RRMM_PAGING_IND
             原语后的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.08  新版作成
    2.  日    期   : 2006年12月5日
        作    者   : luojian 60022475
        修改内容   : Maps3000接口修改
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmPagingInd_ServReqInit(
                                     RRMM_PAGING_IND_STRU  *ptr
                                     )
{
    RRMM_PAGING_IND_STRU    *pMsg;

    if (RRC_IMSI_GSM_MAP == ptr->ulPagingUeId)
    {                                                                           /* 寻呼的类型为IMSI(RRC_IMSI_DS41,RRC不支持 */
        if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
            && (GMM_RRC_RRMM_EST_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
        {                                                                       /* 无信令且正在建立信令连接                 */
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk    |= GMM_MSG_HOLD_FOR_PAGING; /* 置消息被缓存的标志                       */
            pMsg = (RRMM_PAGING_IND_STRU *)Gmm_MemMalloc(sizeof(RRMM_PAGING_IND_STRU));
            if (VOS_NULL_PTR == pMsg)
            {
                  PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvRrmmPagingInd_ServReqInit:ERROR: Allocate memory error");
                  return;
            }
            Gmm_MemCpy(pMsg, ptr, sizeof(RRMM_PAGING_IND_STRU));
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging = (VOS_UINT32)pMsg;           /* 保留RRMM_PAGING _IND首地址               */
        }
        else
        {                                                                       /* 有信令或没有信令且还没建信令             */
            Gmm_TimerStop(GMM_TIMER_T3317);                                     /* 停T3317                                  */
            Gmm_TimerStop(GMM_TIMER_T3318);                                     /* 停止T3318                                */
            Gmm_TimerStop(GMM_TIMER_T3320);                                     /* 停止T3320                                */

            Gmm_ComCnfHandle();
            Gmm_PagingInd_common();
        }
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmPagingInd_ServReqInit:WARNING: NOT RRC_IMSI_GSM_MAP");
    }

    return;
}
/*******************************************************************************
  Module   : Gmm_RcvRrmmPagingInd_RegNmlServ
  Function : 在GMM-REGISTERED.NORMAL-SERVICE状态下，收到RRMM_PAGING_IND
             原语后的处理
  Input    : RRMM_PAGING_IND_STRU  *ptr    :RRMM_PAGING_IND原语首地址
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.08  新版作成
    2. 张志勇  2005.02.21  MM_MT_BUG_005对应
    3.  日    期   : 2006年12月5日
        作    者   : luojian 60022475
        修改内容   : Maps3000接口修改
    4.  日    期   : 2010年11月20日
        作    者   : w00166186
        修改内容   : DTS2010111600353
    5.  日    期   : 2012年2月15日
        作    者   : w00166186
        修改内容   : CSFB&PPAC&ETWS&ISR 开发
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmPagingInd_RegNmlServ(
                                     RRMM_PAGING_IND_STRU *ptr                  /* RRMM_PAGING_IND原语首地址                */
                                     )
{
    NAS_MSG_STRU *ptrNasMsg;                                                    /* 指向NAS消息结构的指针                    */
    VOS_UINT8 ucEstCause = (VOS_UINT8)ptr->ulPagingCause;                               /* RRC建立的原因                            */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    enRatType;

                               /* 初始化指针                               */

    if (RRC_IMSI_GSM_MAP == ptr->ulPagingUeId)
    {                                                                           /* 寻呼的类型为IMSI                         */
        if (GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        {                                                                       /* 无信令连接                               */
            g_GmmAttachCtrl.ucPagingWithImsiFlg = GMM_TRUE;                     /* 标记由网侧的IMSI寻呼触发的ATTACH         */
        }
        Gmm_PagingInd_common();
        gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;
    }
    else
    {                                                                           /* 寻呼的类型为TMSI/P_TMSI                  */
        /* ps寻呼受限时不响应PTMSI寻呼 */
        if (VOS_TRUE == NAS_MML_GetPsRestrictPagingFlg())
        {
            return;
        }

        enRatType   = NAS_MML_GetCurrNetRatType();
        if ((GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
         && (gstGmmCasGlobalCtrl.ucLastDataSender != enRatType)
#if (FEATURE_ON == FEATURE_LTE)
          && (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_NET_RAT_TYPE_LTE)
#endif
        )
        {
            GMM_LOG_INFO("Gmm_RcvRrmmPagingInd_RegNmlServ:Inter System change, Exec select RAU.");
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;
            return;
        }

        if (GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        {                                                                       /* 无信令                                   */
            if (GMM_TIMER_T3302_FLG
                == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
            {                                                                   /* T3302正在运行                            */
                Gmm_TimerPause(GMM_TIMER_T3302);                                /* 挂起T3302                                */
            }
            else if (GMM_TIMER_T3311_FLG
                == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
            {                                                                   /* T3311正在运行                            */
                Gmm_TimerPause(GMM_TIMER_T3311);                                /* 挂起T3311                                */
            }
            else
            {
            }

            g_GmmGlobalCtrl.ucSpecProc   = GMM_SERVICE_REQUEST_PAGING_RSP;      /* 设置当前流程                             */

            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmPagingInd_RegNmlServ:INFO: Service request(paging response) procedure started");

            g_GmmGlobalCtrl.ucServPreSta = g_GmmGlobalCtrl.ucState;             /* 保存GMM的状态                            */

            GMM_CasFsmStateChangeTo(GMM_SERVICE_REQUEST_INITIATED);

            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRrmmPagingInd_RegNmlServ:NORMAL: STATUS IS GMM_SERVICE_REQUEST_INITIATED");

            g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;
            ptrNasMsg = Gmm_ServiceRequestMsgMake();                            /* 调用ServiceRequestMsg make函数           */

            switch (ucEstCause)
            {                                                                   /* RRMM_PAGING_IND与RRMM_EST_REQ中cause转换 */
            case RRC_PAGE_CAUSE_TERMINAT_CONVERSAT_CALL:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL;
                break;
            case RRC_PAGE_CAUSE_TERMINAT_STREAM_CALL:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_STREAM_CALL;
                break;
            case RRC_PAGE_CAUSE_TERMINAT_INTERACT_CALL:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_INTERACT_CALL;
                break;
            case RRC_PAGE_CAUSE_TERMINAT_BACKGROUND_CALL:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_BACKGROUND_CALL;
                break;
            case RRC_PAGE_CAUSE_TERMINAT_HIGH_PRIORITY_SIGNAL:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_HIGH_PRIORITY_SIGNAL;
                break;
            case RRC_PAGE_CAUSE_TERMINAT_LOW_PRIORITY_SIGNAL:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_LOW_PRIORITY_SIGNAL;
                break;
            default:
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmPagingInd_RegNmlServ:WARNING: RRC establish Cause is UNKNOWN");
                ucEstCause = RRC_EST_CAUSE_TERMINAT_CAUSE_UNKNOWN;
                break;
            }

            Gmm_SndRrmmEstReq(ucEstCause, RRC_IDNNS_LOCAL_TMSI, ptrNasMsg);  /* 发送RRMM_EST_REQ                         */

            Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);
            NAS_EventReport(WUEPS_PID_GMM,
                            NAS_OM_EVENT_DATA_SERVICE_REQ,
                            VOS_NULL_PTR,
                            NAS_OM_EVENT_NO_PARA);
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmPagingInd_RegNmlServ:WARNING: STATUS IS GMM_SERVICE_REQUEST_INITIATED");
        }

    }
    return;
}

/*******************************************************************************
  Module   : Gmm_RcvAgentUsimAuthenticationCnf
  Function : 收到AGENT_USIM_AUTHENTICATION_CNF后的处理
  Input    : VOS_VOID *pMsg :AGENT_USIM_AUTHENTICATION_CNF_STRU原语首地址
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1.张志勇  2003.12.08  新版作成
    2.日    期  : 2011年03月30日
      作    者  : 欧阳飞
      修改内容  : DTS2011032802556,网络异常，连续发送鉴权请求消息，导致鉴权失败，卡无效。
    3.日    期  : 2013年11月30日
      作    者  : l65478
      修改内容  : DTS2013121919477,连续收到网络的两条鉴权消息,网络把第一条消息的响应作为第二条请求的响应,导致鉴权失败
    4.日    期  : 2013年7月22日
      作    者  : y00245242
      修改内容  : 适配新的USIM接口

	5.日    期  :2014年01月09日
      作    者  :l65478
      修改内容  :DTS2014010704608:第一次鉴权响应和网络发起的第二次鉴权请求冲突
*******************************************************************************/
VOS_VOID Gmm_RcvAgentUsimAuthenticationCnf(
                                       VOS_VOID *pMsg
                                       )
{
/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-22, begin */
    USIMM_AUTHENTICATION_CNF_STRU *ptr;
/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-22, end */


/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-22, begin */
    ptr = (USIMM_AUTHENTICATION_CNF_STRU *)pMsg;
/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-22, end */

    NAS_GMM_LogAuthInfo((VOS_UINT8)ptr->stCmdResult.ulSendPara, g_GmmAuthenCtrl.ucOpId);

    /* 当前不在等待此消息,丢弃 */
    if ((VOS_UINT8)ptr->stCmdResult.ulSendPara != g_GmmAuthenCtrl.ucOpId)
    {
        return;
    }

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        != (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* 不等待该原语                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAgentUsimAuthenticationCnf:WARNING: USIM_Authentication_cnf is not expected");
        return;
    }
    Gmm_TimerStop(GMM_TIMER_PROTECT);                                           /* 停保护Timer                              */
    g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;         /* 清等待标志                               */


    Gmm_Com_RcvAgentUsimAuthenticationCnf(ptr);                                 /* 调用该原语的公共处理                     */

    return;
}

/*******************************************************************************
  Module   : Gmm_Com_RcvAgentUsimAuthenticationCnf
  Function : 收到AGENT_USIM_AUTHENTICATION_CNF的公共处理
  Input    : AGENT_USIM_AUTHENTICATION_CNF_STRU *ptr
            :AGENT_USIM_AUTHENTICATION_CNF_STRU原语首地址
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1.张志勇  2003.12.08  新版作成
    2.张志勇  2004.10.23  AGENT接口变更对应
    3.张志勇  2005.02.03  指针参数修改为数组格式
    4.liurui  2006.01.13  增加GSM鉴权失败处理
    5.日    期  : 2013年11月15日
      作    者  : m00217266
      修改内容  : sim卡鉴权失败原因上报
    6.日    期   : 2013年07月22日
      作    者   : y00245242
      修改内容   : 为开发VOLTE，适配新的USIM接口
*******************************************************************************/
VOS_VOID Gmm_Com_RcvAgentUsimAuthenticationCnf(
            USIMM_AUTHENTICATION_CNF_STRU         *ptr                                /* 原语指针                                 */
                                           )
{
    VOS_UINT8                           ucCause;
    NAS_MML_SIM_AUTH_FAIL_ENUM_UINT16   enUsimAuthFailVaule;

    ucCause             = NAS_MML_REG_FAIL_CAUSE_NULL;
    enUsimAuthFailVaule = NAS_MML_SIM_AUTH_FAIL_NULL;

    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-22, begin */
    if ((USIMM_3G_AUTH != ptr->enAuthType)
     && (USIMM_2G_AUTH != ptr->enAuthType))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
               "Gmm_Com_RcvAgentUsimAuthenticationCnf:WARNING: authentication is not expected");
        return;
    }
    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-22, end */

    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-23, begin */
    if (USIMM_AUTH_UMTS_SUCCESS == ptr->enResult)
    {/*UMTS鉴权成功*/
        GMM_CasRcvUsimCnfUmtsSucc(&(ptr->uCnfData.stTELECnf));
    }
    else if(USIMM_AUTH_GSM_SUCCESS == ptr->enResult)
    {/*GSM鉴权成功*/
        GMM_CasRcvUsimCnfGsmSucc(&(ptr->uCnfData.stTELECnf));
    }
    else if ((USIMM_AUTH_MAC_FAILURE == ptr->enResult)
             || (USIMM_AUTH_SYNC_FAILURE == ptr->enResult))
    {/*UMTS鉴权:SYNC失败或者MAC失败*/
        GMM_CasRcvUsimCnfFailUmts(&(ptr->uCnfData.stTELECnf), ptr->enResult);
    }
    else if (USIMM_AUTH_UMTS_OTHER_FAILURE == ptr->enResult)
    {/*GSM鉴权失败,或者其它原因*/
        GMM_CasRcvUsimCnfFailGsm(&(ptr->uCnfData.stTELECnf));
    }
    else
    {
        Gmm_AuCntFail();
    }
    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-23, end */

    switch (ptr->enResult)
    {
    case USIMM_AUTH_MAC_FAILURE:
        ucCause = NAS_OM_MM_CAUSE_MAC_FAILURE;
        break;
    case USIMM_AUTH_SYNC_FAILURE:
        ucCause = NAS_OM_MM_CAUSE_SYNCH_FAILURE;
        break;
    case USIMM_AUTH_UMTS_OTHER_FAILURE:
        ucCause = NAS_OM_MM_CAUSE_AUT_UMTS_OTHER_FAILURE;
        break;
    case USIMM_AUTH_GSM_OTHER_FAILURE:
        ucCause = NAS_OM_MM_CAUSE_AUT_GSM_OTHER_FAILURE;
        break;
    default:
        ucCause = NAS_OM_MM_CAUSE_AUT_UMTS_OTHER_FAILURE;
        break;
    }

    if ((USIMM_AUTH_UMTS_SUCCESS == ptr->enResult)
        || (USIMM_AUTH_GSM_SUCCESS == ptr->enResult))
    {
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_AUTH_AND_CIPHER_SUCC,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);
    }
    else
    {
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_AUTH_AND_CIPHER_FAIL,
                        (VOS_VOID *)&ucCause,
                        NAS_OM_EVENT_AUTH_AND_CIPHER_FAIL_LEN);
        enUsimAuthFailVaule = NAS_GMM_ConvertUsimAuthFailInfo(ptr->enResult);
        NAS_GMM_SndMmcSimAuthFailInfo(enUsimAuthFailVaule);

    }
    return;
}

/*lint -e438 -e830*/

/*******************************************************************************
  Module   : Gmm_RcvPtmsiReallocationCommandMsg
  Function : 收到P_TMSI reallocation消息后的处理
  Input    : NAS_MSG_STRU *pMsg :P_TMSI reallocation 消息首地址
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1. 张志勇  2003.12.09  新版作成
  2. 张志勇  2005.04.07  NAS_IT_BUG_049对应
  3. x51137 2006/4/28 A32D02889
  2.日    期   : 2011年7月27日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  3.日    期   : 2012年3月3日
    作    者   : z00161729
    修改内容   : V7R1 C50 支持ISR修改,T3312启动停止超时均需通知L
  4.日    期   : 2013年08月23日
    作    者   : f00179208
    修改内容   : ErrLog&FTM项目,PTMSI发生改变时上报给OM
  5.日    期   : 2014年6月17日
    作    者   : z00234330
    修改内容   : PCINT清理
  6.日    期   : 2015年2月6日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整
*******************************************************************************/
VOS_VOID Gmm_RcvPtmsiReallocationCommandMsg(
                                        NAS_MSG_FOR_PCLINT_STRU *pMsg
                                        )
{
    VOS_UINT8               *pucMsgTemp;                                            /* 暂时指针变量                             */
    VOS_UINT8               *pucRaiTemp;
    VOS_UINT8               ucPtmsiSigFlg;
    NAS_MSG_STRU        *pNasMsg;                                               /* 定义指向NAS消息的指针                    */
    GMM_RAI_STRU        RaiTemp;
    NAS_MSG_STRU        *pGmmStatus;

    NAS_MML_RAI_STRU                       *pstLastSuccRai;

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();


    /*if (0x20 != (g_GmmGlobalCtrl.ucState & 0xF0))*/
    if ((0x0 != (g_GmmGlobalCtrl.ucState & 0xF0))
     &&  (0x20 != (g_GmmGlobalCtrl.ucState & 0xF0)))
    {                                                                           /* 非REGISTERED状态                         */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvPtmsiReallocationCommandMsg:WARNING: P-TMSI reallocation is not expected");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_MSG_TYPE_NOT_COMPATIBLE);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;
    }
    if (pMsg->ulNasMsgSize < GMM_MSG_LEN_P_TMSI_REALLOCATION_COMMAND)
    {                                                                           /* 如果空中接口消息的长度非法               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvPtmsiReallocationCommandMsg:WARNING: The length of P-TMSI REALLOCATION is invalid");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;
    }

    if ( GMM_FALSE == Gmm_RcvPtmsiRelocCmdIEChk(pMsg) )
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvPtmsiReallocationCommandMsg:WARNING: The check result of P-TMSI REALLOCATION is invalid");
        pGmmStatus = Gmm_GmmStatusMsgMake(
            NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;
    }

    ucPtmsiSigFlg = GMM_FALSE;
    pucMsgTemp = pMsg->aucNasMsg;                                               /* 得到空中接口消息首地址                   */
    pucRaiTemp = pucMsgTemp+8;
    /* Modified by z00234330 for PCLINT清理, 2014-06-24, begin */
    RaiTemp.Lai.PlmnId.aucMccDigit[0] = (VOS_UINT8)((*pucRaiTemp) & 0x0F);
    RaiTemp.Lai.PlmnId.aucMccDigit[1] = (VOS_UINT8)((*pucRaiTemp) >> 4);
    pucRaiTemp++;

    RaiTemp.Lai.PlmnId.aucMccDigit[2] = (VOS_UINT8)((*pucRaiTemp) & 0x0F);
    RaiTemp.Lai.PlmnId.aucMncDigit[2] = (VOS_UINT8)((*pucRaiTemp) >> 4);
    pucRaiTemp++;

    RaiTemp.Lai.PlmnId.aucMncDigit[0] = (VOS_UINT8)((*pucRaiTemp) & 0x0F);
    RaiTemp.Lai.PlmnId.aucMncDigit[1] = (VOS_UINT8)((*pucRaiTemp) >> 4);
    pucRaiTemp++;

    if (0x0F == RaiTemp.Lai.PlmnId.aucMncDigit[2])
    {
        RaiTemp.Lai.PlmnId.ucMncCnt = 2;
    }
    else
    {
        RaiTemp.Lai.PlmnId.ucMncCnt = 3;
    }

    RaiTemp.Lai.aucLac[0] = *(pucRaiTemp);
    pucRaiTemp++;

    RaiTemp.Lai.aucLac[1] = *(pucRaiTemp);
    pucRaiTemp++;

    RaiTemp.ucRac = *pucRaiTemp;

    /* Modified by z00234330 for PCLINT清理, 2014-06-24, end */

    if(GMM_MSG_LEN_P_TMSI_REALLOCATION_COMMAND != pMsg->ulNasMsgSize)
    {
        if((GMM_IEI_P_TMSI_SIGNATURE ==
            *(pucMsgTemp+GMM_MSG_LEN_P_TMSI_REALLOCATION_COMMAND))
            && (pMsg->ulNasMsgSize ==
                        (GMM_MSG_LEN_P_TMSI_REALLOCATION_COMMAND + 4)))
        {
            ucPtmsiSigFlg = GMM_TRUE;
        }
    }

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {/* 2G模式处理 */
        pucMsgTemp += 2;
        if (GMM_FALSE == GMM_GetPtmsiFromMsgIe(pucMsgTemp))
        {
            GMM_LOG_WARN("Gmm_RcvPtmsiReallocationCommandMsg:WARNING: Cannot get new ptmsi!");
        }
        pucMsgTemp += 6;
    }
    else if ( NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {/* 3G模式处理 */
        pucMsgTemp +=4;
        NAS_MML_SetUeIdPtmsi(pucMsgTemp);
        pucMsgTemp = pucMsgTemp + NAS_MML_MAX_PTMSI_LEN;
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask |= GMM_UEID_P_TMSI;              /* 设置UE ID存在标志                        */

#if (FEATURE_ON == FEATURE_PTM)
        /* 工程菜单打开后，PTMSI发生改变需要上报给OM */
        NAS_GMM_SndAcpuOmChangePtmsi();
#endif
    }
    else
    {

    }


    pstLastSuccRai->ucRac               = RaiTemp.ucRac;
    pstLastSuccRai->stLai.aucLac[0]     = RaiTemp.Lai.aucLac[0];
    pstLastSuccRai->stLai.aucLac[1]     = RaiTemp.Lai.aucLac[1];
    NAS_GMM_ConvertPlmnIdToMmcFormat(&(RaiTemp.Lai.PlmnId),
         &(pstLastSuccRai->stLai.stPlmnId));


    if (GMM_TRUE == ucPtmsiSigFlg )
    {                                                                           /* 消息中有P-TMSI signature                 */
        pucMsgTemp += 8;                                                        /* 指针指向P-TMSI signature域               */
        Gmm_MemCpy(NAS_MML_GetUeIdPtmsiSignature(),
                   pucMsgTemp,
                   NAS_MML_MAX_PTMSI_SIGNATURE_LEN);                            /* P_TMSI signature赋值 */
        pucMsgTemp += NAS_MML_MAX_PTMSI_SIGNATURE_LEN;
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask |= GMM_UEID_P_TMSI_SIGNATURE;    /* 设置UE ID存在标志                        */
    }

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
    }
    else
    {
        Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
    }

    Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_PTMSI_RAI);                        /* 通知RRC NAS层信息变化                    */

    /* Gmm_SndPmmAgentProcedureInd(GMM_PROCEDURE_PTMSI_RELOC); */

    pNasMsg = Gmm_PtmsiReallocationCompleteMsgMake();                           /* P-TMSI REALLOCATION COMPLETE消息的作成   */

    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH,pNasMsg);                       /* 调用发送RRMM_DATA_REQ函数                */
    if (GMM_TRUE == GMM_IsCasGsmMode())
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
    return;
}
/*lint +e438 +e830*/

/*******************************************************************************
  Module   : Gmm_Auth_Request_Option_Ie_Check
  Function : 对Authentication and Ciphering Request消息中的可选项进行检查
  Input    : NAS_MSG_STRU *pMsg
             VOS_UINT8     ucIeOffset
  Output   : 无
  NOTE     : 无
  Return   : GMM_SUCCESS   检查成功
             GMM_FAILURE   检查失败
  History  :
    1.日    期 : 2009年06月10日
      作    者 : x00115505
      修改内容 : Created
*******************************************************************************/
VOS_UINT8 Gmm_Auth_Request_Option_Ie_Check(NAS_MSG_FOR_PCLINT_STRU *pMsg,
                                                           VOS_UINT8 **ppRand,
                                                           VOS_UINT8 *pucRandFlag,
                                                           VOS_UINT8 **ppCksn,
                                                           VOS_UINT8 *pucCksnFlag,
                                                           VOS_UINT8 **ppAutn,
                                                           VOS_UINT8 *pucAutnFlag)
{
    VOS_UINT8        ucAddOffset = 0;
    VOS_UINT8       *pucMsgTemp;                                                /* 暂时指针变量                             */
    NAS_MSG_STRU    *pGmmStatus;

    if (VOS_NULL == pMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_Auth_Request_Option_Ie_Check:ERROR: Null Pointer");
        return GMM_FAILURE;
    }

    pucMsgTemp = pMsg->aucNasMsg;                                               /* 得到空中接口消息首地址                   */

    for (; pMsg->ulNasMsgSize > (VOS_UINT32)(4 + ucAddOffset); )
    {
        switch (*(pucMsgTemp + 4 + ucAddOffset))
        {
        case GMM_IEI_AUTHENTICATION_PARAMETER_RAND:
            if ((GMM_TRUE == *pucRandFlag)
                || (((ucAddOffset + 4) + 17) > (VOS_UINT8)pMsg->ulNasMsgSize ))
            {
                ucAddOffset += 17;
                break;
            }
            *pucRandFlag = GMM_TRUE;
            *ppRand = pucMsgTemp + 4 + ucAddOffset;
            ucAddOffset += 17;
            break;
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER0:
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER1:
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER2:
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER3:
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER4:
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER5:
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER6:
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER7:
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER0|(GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_SPARE1):
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER1|(GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_SPARE1):
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER2|(GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_SPARE1):
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER3|(GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_SPARE1):
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER4|(GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_SPARE1):
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER5|(GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_SPARE1):
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER6|(GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_SPARE1):
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER7|(GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_SPARE1):
            if (GMM_TRUE == *pucCksnFlag)
            {
                ucAddOffset += 1;
                break;
            }
            *pucCksnFlag = GMM_TRUE;
            *ppCksn = pucMsgTemp + 4 + ucAddOffset;
            ucAddOffset += 1;
            break;
        case GMM_IEI_AUTHENTICATION_PARAMETER_AUTN:
            if ( (VOS_UINT8)pMsg->ulNasMsgSize < (ucAddOffset + 6) )
            {
                ucAddOffset = (VOS_UINT8)pMsg->ulNasMsgSize;
                break;
            }
            if ((GMM_TRUE == *pucAutnFlag)
                || (((ucAddOffset + 4) + 18) > (VOS_UINT8)pMsg->ulNasMsgSize ))
            {
                ucAddOffset += 18;
                break;
            }
            if (16 != (*(pucMsgTemp + 4 + ucAddOffset + 1)))
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAuthenAndCipherRequestMsg:WARNING: Semantically incorrect message");
                pGmmStatus = Gmm_GmmStatusMsgMake(
                                  NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

                Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
                return GMM_FAILURE;
            }

            *pucAutnFlag = GMM_TRUE;
            *ppAutn = pucMsgTemp + 4 + ucAddOffset;
            ucAddOffset += 18;
            break;
        default :
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAuthenAndCipherRequestMsg:WARNING: Conditional IE error");
            ucAddOffset = (VOS_UINT8)pMsg->ulNasMsgSize;
            break;
        }
    }

    return GMM_SUCCESS;
}

/*******************************************************************************
  Module   : Gmm_RcvAuthenAndCipherRequestMsg_ForceToStandby
  Function : Gmm_RcvAuthenAndCipherRequestMsg降复杂度: ForceToStandby 处理
  Input    : VOS_UINT8 ucForceToStandby
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 欧阳飞  2009.06.11  新版作成
*******************************************************************************/
VOS_VOID Gmm_RcvAuthenAndCipherRequestMsg_ForceToStandby(
                                      VOS_UINT8 ucForceToStandby
                                      )
{
    if (0 == ucForceToStandby)
    {
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }

    else if (1 == ucForceToStandby)
    {
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_TRUE;
    }

    else
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAuthenAndCipherRequestMsg_ForceToStandby:WARNING: AUTHENTICATION AND CIPHER REQUEST is semantically incorrect");
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvAuthenAndCipherRequestMsg_No_Rand_Handling
  Function : Gmm_RcvAuthenAndCipherRequestMsg降复杂度: Rand 不存在的处理
  Input    : VOS_VOID
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 欧阳飞  2009.06.11  新版作成
*******************************************************************************/
VOS_VOID Gmm_RcvAuthenAndCipherRequestMsg_No_Rand_Handling(VOS_VOID)
{
    NAS_MSG_STRU *pNasMsg = VOS_NULL;                                           /* 定义指向NAS消息的指针                    */

    pNasMsg = Gmm_AuthenAndCipherResponseMsgMake(
                                    GMM_AUTH_AND_CIPH_RES_UNNEEDED);            /* 调用Gmm_AuthenAndCipherResponseMsgMake   */

    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);                      /* 调用Gmm_SndRrmmDataReq                   */

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_ComGprsCipherHandle();
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvAuthenAndCipherRequestMsg_Umts_Auth_Handling
  Function : Gmm_RcvAuthenAndCipherRequestMsg降复杂度: Umts_Auth的处理
  Input    : VOS_UINT8  ucCksnFlag,
             VOS_UINT8 *pCksn,
             VOS_UINT8 *pAutn
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.欧阳飞  2009.06.11  新版作成
  2.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  3.日    期  : 2011年03月30日
    作    者  : 欧阳飞
    修改内容  : DTS2011032802556,网络异常，连续发送鉴权请求消息，导致鉴权失败，卡无效。
  4.日    期  : 2011年05月13日
    作    者  : 欧阳飞
    修改内容  : DTS2011051304471,RAU 鉴权过程中，网络下发鉴权请求后，在卡回复鉴权结果
                  前，发生W到G重选再回退，重新驻留W小区后，网络重新下发鉴权消息，GMM未向
                  卡发送鉴权请求，而将老的鉴权结果回复网络，导致鉴权失败，卡无效。
 5.日    期   : 2012年12月25日
   作    者   : L65478
   修改内容   : DTS2012122900226,G下定时器超时根据失败次数决定是否禁止当前小区
*******************************************************************************/
VOS_VOID Gmm_RcvAuthenAndCipherRequestMsg_Umts_Auth_Handling(
                                                  VOS_UINT8  ucCksnFlag,
                                                  VOS_UINT8 *pCksn,
                                                  VOS_UINT8 *pAutn)
{
    NAS_MSG_STRU *pNasMsg = VOS_NULL;                                           /* 定义指向NAS消息的指针                    */

    if (GMM_TRUE == ucCksnFlag)
    {
        g_GmmAuthenCtrl.ucCksnSav = (VOS_UINT8)((*pCksn) & 0x07);               /* 暂存CKSN                                 */
    }

    /* 24.008规定连续3次鉴权失败才认为MS鉴权网络失败,所以当上次鉴权没有失败时清除鉴权失败次数 */
    if ((GMM_TIMER_T3318_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3318_FLG))
     && (GMM_TIMER_T3320_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3320_FLG)))
    {
        g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;
    }

    if (GMM_FALSE == g_GmmAuthenCtrl.ucResStoredFlg)
    {                                                                           /* 易失性内存为空                           */
        Gmm_SndAgentUsimAuthenticationReq(*(pAutn+1), (pAutn+1));
        Gmm_TimerStart(GMM_TIMER_PROTECT);
    }
    else
    {                                                                           /* 易失性内存非空                           */
        /* 是否和上次RAND相同 */
        if (GMM_TRUE == GMM_IsLastRand())
        {
            /* 消息中的RAND = 易失性内存中的RAND，无需再向卡进行鉴权，直接回复网络 */
            Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_SECURITY_KEY);

            if (GMM_TRUE == GMM_IsCasGsmMode())
            {
                Gmm_ComGprsCipherHandle();
            }

            pNasMsg = Gmm_AuthenAndCipherResponseMsgMake(
                                    GMM_AUTH_AND_CIPH_RES_NEEDED);              /* 调用Gmm_AuthenAndCipherResponseMsgMake   */

            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH,pNasMsg);               /* 调用Gmm_SndRrmmDataReq                   */

            Gmm_Start_StopedRetransmissionTimer();                              /* 存在被停止的retransmission timer将其启动 */

            g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;                              /* GMM Authentication attempt counter清0    */
        }
        else
        {
            g_GmmAuthenCtrl.ucResStoredFlg = GMM_FALSE;

            /* 消息中的RAND 不等于 易失性内存中的RAND，需再向卡进行鉴权 */
            Gmm_SndAgentUsimAuthenticationReq(*(pAutn+1), (pAutn+1));
            Gmm_TimerStart(GMM_TIMER_PROTECT);
        }
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvAuthenAndCipherRequestMsg_Gsm_Auth_Handling
  Function : Gmm_RcvAuthenAndCipherRequestMsg降复杂度: Gsm_Auth的处理
  Input    : VOS_UINT8  ucCksnFlag,
             VOS_UINT8 *pCksn
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 欧阳飞  2009.06.11  新版作成
    2.日    期  : 2011年03月30日
      作    者  : 欧阳飞
      修改内容  : DTS2011032802556,网络异常，连续发送鉴权请求消息，导致鉴权失败，卡无效。
    3.日    期  : 2011年05月13日
      作    者  : 欧阳飞
      修改内容  : DTS2011051304471,RAU 鉴权过程中，网络下发鉴权请求后，在卡回复鉴权结果
                  前，发生W到G重选再回退，重新驻留W小区后，网络重新下发鉴权消息，GMM未向
                  卡发送鉴权请求，而将老的鉴权结果回复网络，导致鉴权失败，卡无效。
    4.日    期   : 2012年12月25日
      作    者   : L65478
      修改内容   : DTS2012122900226,G下定时器超时根据失败次数决定是否禁止当前小区
    5.日    期  : 2012年12月26日
      作    者  : 张鹏 id:00214637
      修改内容  : USIM对外接口函数变更的处理 ，Client ID 到 PID的转换处理。
    6.日    期  : 2013年6月4日
      作    者  : w00242748
      修改内容  : NAS_SndUsimmAuthReq修改为NAS_USIMMAPI_AuthReq，后者会根据当前模式自动
                  适配
    7.日    期  : 2013年11月30日
      作    者  : l65478
      修改内容  : DTS2013121919477,连续收到网络的两条鉴权消息,网络把第一条消息的响应作为第二条请求的响应,导致鉴权失败

    8.日    期  : 2014年1月3日
      作    者  : s00261364
      修改内容  : mm模块Converity告警消除
    9.日    期   : 2014年2月19日
      作    者   : s00217060
      修改内容   : coverity清理
*******************************************************************************/
VOS_VOID Gmm_RcvAuthenAndCipherRequestMsg_Gsm_Auth_Handling(
                                                  VOS_UINT8  ucCksnFlag,
                                                  VOS_UINT8 *pCksn)
{
    NAS_MSG_STRU *pNasMsg    = VOS_NULL;                                           /* 定义指向NAS消息的指针                    */
    VOS_UINT8     ucTempOpId = 0;

    if (GMM_TRUE == ucCksnFlag)
    {
        g_GmmAuthenCtrl.ucCksnSav = (VOS_UINT8)((*pCksn) & 0x07);               /* 暂存CKSN                                 */
    }

    /* 24.008规定连续3次鉴权失败才认为MS鉴权网络失败,所以当上次鉴权没有失败时清除鉴权失败次数 */
    if ((GMM_TIMER_T3318_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3318_FLG))
     && (GMM_TIMER_T3320_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3320_FLG)))
    {
        g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;
    }

    if (GMM_FALSE == g_GmmAuthenCtrl.ucResStoredFlg)
    {                                                                           /* 易失性内存为空                           */

        ucTempOpId = g_GmmAuthenCtrl.ucOpId;

        g_GmmAuthenCtrl.ucOpId = (VOS_UINT8)((ucTempOpId) % 255);
        g_GmmAuthenCtrl.ucOpId++;

        NAS_USIMMAPI_AuthReq(WUEPS_PID_GMM,
                      AUTHENTICATION_REQ_GSM_CHALLENGE,
                      g_GmmAuthenCtrl.aucRandSav,
                      VOS_NULL_PTR,
                      g_GmmAuthenCtrl.ucOpId
                      );


        g_GmmReqCnfMng.ucCnfMask |= GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;

        Gmm_TimerStart(GMM_TIMER_PROTECT);
    }
    else
    {
        /* 是否和上次RAND相同 */
        if (GMM_TRUE == GMM_IsLastRand())
        {
            /* 消息中的RAND = 易失性内存中的RAND        */
            Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_SECURITY_KEY);
            if (GMM_TRUE == GMM_IsCasGsmMode())
            {
                Gmm_ComGprsCipherHandle();
            }
            pNasMsg = Gmm_AuthenAndCipherResponseMsgMake(
                                    GMM_AUTH_AND_CIPH_RES_NEEDED );
            Gmm_SndRrmmDataReq( RRC_NAS_MSG_PRIORTY_HIGH,pNasMsg );

            Gmm_Start_StopedRetransmissionTimer();
            g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;
        }
        else
        {
            g_GmmAuthenCtrl.ucResStoredFlg = GMM_FALSE;

            /* Modified by s00217060 for coverity清理, 2014-02-17, begin */
            g_GmmAuthenCtrl.ucOpId = (VOS_UINT8)((ucTempOpId) % 255);
            g_GmmAuthenCtrl.ucOpId++;
            /* Modified by s00217060 for coverity清理, 2014-02-17, end */

            NAS_USIMMAPI_AuthReq( WUEPS_PID_GMM,
                           AUTHENTICATION_REQ_GSM_CHALLENGE,
                           g_GmmAuthenCtrl.aucRandSav,
                           VOS_NULL_PTR,
                           g_GmmAuthenCtrl.ucOpId);

            g_GmmReqCnfMng.ucCnfMask |= GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;
            Gmm_TimerStart(GMM_TIMER_PROTECT);
        }
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvAuthenAndCipherRequestMsg_Auth_Fail_Handling
  Function : Gmm_RcvAuthenAndCipherRequestMsg降复杂度: Auth Fail的处理
  Input    : VOS_UINT8 ucGmmAuthType
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1. 欧阳飞  2009.06.11  新版作成
  2.  日    期  : 2011年03月30日
      作    者  : 欧阳飞
      修改内容  : DTS2011032802556,网络异常，连续发送鉴权请求消息，导致鉴权失败，卡无效。
  3.  日    期   : 2012年8月25日
      作    者   : m00217266
      修改内容   : 删除GMM_SaveErrCode，添加Gmm_Save_Detach_Cause，
                  保存导致Attach失败的原因值
  4.  日    期  :2014年01月09日
      作    者  :l65478
      修改内容  :DTS2014010704608:第一次鉴权响应和网络发起的第二次鉴权请求冲突
*******************************************************************************/
VOS_VOID Gmm_RcvAuthenAndCipherRequestMsg_Auth_Fail_Handling(
                                                  VOS_UINT8 ucGmmAuthType)
{
    NAS_MSG_STRU *pNasMsg;                                                      /* 定义指向NAS消息的指针                    */

    g_GmmAuthenCtrl.ucAuthenAttmptCnt++;                                /* GMM Authentication attempt counter加1    */
    if (GMM_AUTHEN_ATTEMPT_MAX_CNT == g_GmmAuthenCtrl.ucAuthenAttmptCnt)
    {                                                                   /* Authentication attempt counter达到最大   */
        if ( GMM_AUTH_GSM_AUTH_UNACCEPTABLE == ucGmmAuthType )
        {
            pNasMsg = Gmm_AuthenAndCipherFailureMsgMake(NAS_MML_REG_FAIL_CAUSE_GSM_AUT_UNACCEPTABLE, 0, VOS_NULL_PTR);     /* AUTHENTICATION AND CIPHERING FAILURE作成 */
            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH,pNasMsg);                   /* 调用发送函数                             */

            Gmm_TimerStop(GMM_TIMER_T3316);                             /* 停止T3316                                */

            /* 清除鉴权相关全局变量 */
            g_GmmAuthenCtrl.ucResStoredFlg       = GMM_FALSE;
            g_GmmAuthenCtrl.ucRandStoredFlg      = GMM_FALSE;

            /*保存鉴权失败的错误码*/
            NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_GSM_AUT_UNACCEPTABLE);
        }

        Gmm_AuCntFail();
    }
    else
    {                                                                   /* Auth attempt counter没有达到最大         */
        if (GMM_AUTH_GSM_AUTH_UNACCEPTABLE == ucGmmAuthType)
        {
            Gmm_Au_MacAutnWrong(NAS_MML_REG_FAIL_CAUSE_GSM_AUT_UNACCEPTABLE);
        }
    }

    if (GMM_AUTH_GSM_AUTH_UNACCEPTABLE == ucGmmAuthType)
    {
        NAS_GMM_SndMmcSimAuthFailInfo(NAS_MML_SIM_AUTH_FAIL_GSM_AUT_UNACCEPTABLE);
    }

    return;
}


/*******************************************************************************
  Module   : Gmm_RcvAuthenAndCipherRequestMsg_T3314_Handling
  Function : Gmm_RcvAuthenAndCipherRequestMsg降复杂度: T3314的处理
  Input    : VOS_VOID
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 欧阳飞  2009.06.11  新版作成
    2.日    期   : 2012年3月3日
      作    者   : z00161729
      修改内容   : V7R1 C50 支持ISR修改,T3312启动停止超时均需通知L
*******************************************************************************/
VOS_VOID Gmm_RcvAuthenAndCipherRequestMsg_T3314_Handling(VOS_VOID)
{
    if (GMM_TRUE == GMM_IsCasGsmMode())
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

    return;

}

/*******************************************************************************
  Module   : Gmm_RcvAuthenAndCipherRequestMsg_Preprocess
  Function : Gmm_RcvAuthenAndCipherRequestMsg降复杂度: 消息预处理
  Input    : NAS_MSG_STRU *pMsg :NAS消息首地址
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 欧阳飞  2009.06.11  新版作成
*******************************************************************************/
VOS_UINT8 Gmm_RcvAuthenAndCipherRequestMsg_Preprocess(
                                                NAS_MSG_FOR_PCLINT_STRU *pMsg
                                                )
{
    NAS_MSG_STRU        *pGmmStatus;

    if (GMM_MSG_LEN_AUTHENTICATION_AND_CIPHERING_REQUEST > pMsg->ulNasMsgSize)
    {                                                                           /* 如果空中接口消息的长度过短               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAuthenAndCipherRequestMsg:WARNING: The length of AUTHENTICATION AND CIPHER REQUEST is invalid");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return GMM_FAILURE;
    }

    if ((GMM_STATUS_DETACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
        && (GMM_REGISTERED_INITIATED != g_GmmGlobalCtrl.ucState))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAuthenAndCipherRequestMsg:WARNING: The check result of P-TMSI REALLOCATION is invalid AUTHENTICATION AND CIPHER REQUEST is not expected");
        return GMM_FAILURE;
    }

    return GMM_SUCCESS;

}

/*******************************************************************************
  Module   : Gmm_RcvAuthenAndCipherRequestMsg
  Function : Authentication and ciphering request接收处理
  Input    : NAS_MSG_STRU *pMsg :NAS消息首地址
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.09  新版作成
    2. 张志勇  2005.03.18  NAS_IT_BUG_007对应
    3. x51137        2006/4/13 A32D03056
    3. x51137  2006/4/28 A32D02889
    4.日    期  : 2006年11月25日
      作    者  : luojian id:60022475
      修改内容  : 问题单号:A32D06583
    5.日    期  : 2007年01月13日
      作    者  : s46746
      修改内容  : 根据问题单号：A32D08326
    6.日    期  : 2009年03月18日
      作    者  : l65478
      修改内容  : 根据问题单号：AT2D08671,数传状态下，W出服务区后，切到G，数传恢复失败，因为GMM没有配置LL加密算法
    7.日    期  : 2011年03月30日
      作    者  : 欧阳飞
      修改内容  : DTS2011032802556,网络异常，连续发送鉴权请求消息，导致鉴权失败，卡无效。
    8.日    期  : 2013年11月30日
      作    者  : l65478
      修改内容  : DTS2013121919477,连续收到网络的两条鉴权消息,网络把第一条消息的响应作为第二条请求的响应,导致鉴权失败
*******************************************************************************/
VOS_VOID Gmm_RcvAuthenAndCipherRequestMsg(
    NAS_MSG_FOR_PCLINT_STRU            *pMsg
)
{
    VOS_UINT8                           i;
    VOS_UINT8                          *pucMsgTemp;
    VOS_UINT8                           ucRandFlag      = GMM_FALSE;
    VOS_UINT8                           ucAutnFlag      = GMM_FALSE;
    VOS_UINT8                          *pRand           = VOS_NULL_PTR;
    VOS_UINT8                          *pCksn           = VOS_NULL_PTR;
    VOS_UINT8                          *pAutn           = VOS_NULL_PTR;
    NAS_MSG_STRU                       *pGmmStatus      = VOS_NULL_PTR;

    VOS_UINT8                           ucCksnFlag      = GMM_FALSE;
    VOS_UINT8                           ucOptionalIeFlg = GMM_TRUE;

    VOS_UINT8                           ucGmmAuthType;
    VOS_UINT8                           ucForceToStandby;
    VOS_UINT8                           ucResult        = GMM_SUCCESS;

    ucResult = Gmm_RcvAuthenAndCipherRequestMsg_Preprocess(pMsg);
    if (GMM_FAILURE == ucResult)
    {
        return;
    }

    /* 上报鉴权事件 */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_AUTH_AND_CIPHER_REQ,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    Gmm_TimerStop(GMM_TIMER_T3318);
    Gmm_TimerStop(GMM_TIMER_T3320);

    /* ForceStandby标志处理 */
    ucForceToStandby = (VOS_UINT8)(pMsg->aucNasMsg[3] & 0x0F);
    Gmm_RcvAuthenAndCipherRequestMsg_ForceToStandby(ucForceToStandby);

    /* 检查是否有可选IE */
    if (GMM_MSG_LEN_AUTHENTICATION_AND_CIPHERING_REQUEST < pMsg->ulNasMsgSize)
    {
        ucOptionalIeFlg = GMM_TRUE;
    }
    else
    {
        ucOptionalIeFlg = GMM_FALSE;
    }

    /* 可选IE有效性检查 */
    pucMsgTemp = pMsg->aucNasMsg;
    if (GMM_TRUE == ucOptionalIeFlg)
    {
        ucResult = Gmm_Auth_Request_Option_Ie_Check(pMsg, &pRand, &ucRandFlag, &pCksn, &ucCksnFlag,
                                               &pAutn, &ucAutnFlag);

        if (GMM_FAILURE == ucResult)
        {
            return;
        }
    }

    /* 保存A&C reference number */
    g_GmmAuthenCtrl.ucAcRefNum = (VOS_UINT8)((*(pucMsgTemp+3) & 0xf0) >> 4);        /* 存 A&C reference number                  */

    /* 保存GPRS加密算法 */
    gstGmmCasGlobalCtrl.ucGprsCipherAlg = (VOS_UINT8)(*(pucMsgTemp+2) & 0x07);

    NAS_GMM_SndMmcCipherInfoInd();

    if (1 == ((*(pucMsgTemp+2)&0x70)>>4))
    {
        g_GmmAuthenCtrl.ucImeisvFlg = GMM_TRUE;
    }
    else
    {
        g_GmmAuthenCtrl.ucImeisvFlg = GMM_FALSE;
    }

    /* 消息中不包含参数:GPRS RAND */
    if ((GMM_FALSE == ucRandFlag) || (VOS_NULL_PTR == pRand))
    {                                                                           /* 消息中不包含参数:GPRS RAND               */
        Gmm_RcvAuthenAndCipherRequestMsg_No_Rand_Handling();
    }
    else
    {
        /* 含参数:GPRS RAND */
        if (VOS_NULL_PTR == pCksn)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAuthenAndCipherRequestMsg:WARNING: cksn in AUTHENTICATION AND CIPHER REQUEST is expected");
            pGmmStatus = Gmm_GmmStatusMsgMake(
                NAS_MML_REG_FAIL_CAUSE_CONDITIONAL_IE_ERROR);
            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
            return;
        }

        /* 越过IEI，保存本次RAND */
        pRand++;
        for (i=0; i<GMM_MAX_SIZE_RAND; i++)
        {
            g_GmmAuthenCtrl.aucRandSav[i] = *(pRand+i);
        }

        /* 如果在鉴权过程中，再次收到网络的鉴权消息，处理如下 */
        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {
            if (GMM_TRUE == GMM_IsLastRand())
            {
                /* 当前正在鉴权过程中，网络下发了新的鉴权，并且RAND与上次的相同，不再给卡
                   下发新的请求，继续等待卡的回复 */
                return;
            }
        }

        /* GSM下，无需保存RES */
        if (GMM_TRUE == GMM_IsCasGsmMode())
        {
            if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG ==
                (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
            {
                g_GmmAuthenCtrl.ucResStoredFlg = GMM_FALSE;
            }
        }

        /* 获取鉴权类型，并调用不同函数处理 */
        ucGmmAuthType = GMM_AuthType(ucAutnFlag);
        if ((GMM_AUTH_UMTS == ucGmmAuthType) && (VOS_NULL_PTR != pAutn))
        {
            /*UMTS鉴权*/
            Gmm_RcvAuthenAndCipherRequestMsg_Umts_Auth_Handling(ucCksnFlag, pCksn, pAutn);
            
            NAS_MML_SetUsimDoneGsmPsAuthFlg(VOS_FALSE);
            
        }
        else if (GMM_AUTH_GSM == ucGmmAuthType)
        {   /*GSM鉴权*/
            Gmm_RcvAuthenAndCipherRequestMsg_Gsm_Auth_Handling(ucCksnFlag, pCksn);

            if (VOS_TRUE == NAS_MML_IsNeedSetUsimDoneGsmAuthFlg())
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAuthenAndCipherRequestMsg:SetUsimDoneGsmPsAuthFlg to true");
            
                NAS_MML_SetUsimDoneGsmPsAuthFlg(VOS_TRUE);
            }
        }
        else
        {
            Gmm_RcvAuthenAndCipherRequestMsg_Auth_Fail_Handling(ucGmmAuthType);
        }
    }

    /* 保存RAND用于下次鉴权进行比较 */
    for (i=0; i<GMM_MAX_SIZE_RAND; i++)
    {
        g_GmmAuthenCtrl.aucRand[i] = g_GmmAuthenCtrl.aucRandSav[i];
    }

    Gmm_RcvAuthenAndCipherRequestMsg_T3314_Handling();

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvAuthenAndCipherRejectMsg
  Function : 接收Authentication and ciphering reject消息的处理
  Input    : NAS_MSG_STRU *pMsg :NAS消息首地址
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.09  新版作成
    2.日    期   : 2007年01月16日
      作    者   : s46746
      修改内容   : 根据问题单号：A32D08381
    3.日    期   : 2007年05月11日
      作    者   : luojian id:60022475
      修改内容   : 问题单号:A32D10713
    4.日    期   : 2007年06月16日
      作    者   : luojian id:60022475
      修改内容   : 根据问题单号：A32D11635
    5.日    期   : 2009年03月31日
      作    者   : L65478
      修改内容   : 根据问题单号：AT2D10529两次鉴权失败后没有释放RRC连接
    6.日    期   : 2011年07月13日
      作    者   : w00166186
      修改内容   : V7R1 PHASE II ATTACH/DETACH调整
    7.日    期   : 2011年10月8日
      作    者   : s46746
      修改内容   : V7R1 phase II,将EPLMN、RPLMN移到MM/GMM维护
    8.日    期  : 2012年08月24日
      作    者  : m00217266
      修改内容  : 修改Gmm_SndSmEstablishCnf接口，添加原因值
    9.日    期   : 2013年10月05日
      作    者   : l65478
      修改内容   : DTS2013092509860:GPRS detach过程被BG搜索终止后,GMM又自动发起了注册
	10.日    期   : 2014年2月18日
      作    者   : l00215384
      修改内容   : DTS2014021006453，注册成功后鉴权拒绝计数清零
*******************************************************************************/
VOS_VOID Gmm_RcvAuthenAndCipherRejectMsg(
                                     NAS_MSG_FOR_PCLINT_STRU *pMsg
                                     )
{
    NAS_MSG_STRU        *pGmmStatus;
    VOS_UINT8            ucCause = NAS_MML_REG_FAIL_CAUSE_NULL;
	NAS_MML_PLMN_ID_STRU         *pstCurrCampPlmnId = VOS_NULL_PTR;
	NAS_MML_IGNORE_AUTH_REJ_INFO_STRU      *pstAuthRejInfo = VOS_NULL_PTR;

    g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_FALSE;

    if (pMsg->ulNasMsgSize < GMM_MSG_LEN_AUTHENTICATION_AND_CIPHERING_REJECT)
    {                                                                           /* 如果空中接口消息的长度非法               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAuthenAndCipherRejectMsg:WARNING: The length of AUTHENTICATION AND CIPHER REJECT is invalid");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;
    }

    pstCurrCampPlmnId = NAS_MML_GetCurrCampPlmnId();
    pstAuthRejInfo = NAS_MML_GetAuthRejInfo();

    if (pstAuthRejInfo->ucHplmnPsAuthRejCounter < pstAuthRejInfo->ucMaxAuthRejNo)
    {
         if ((VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(pstCurrCampPlmnId))
         && (VOS_TRUE == pstAuthRejInfo->ucIgnoreAuthRejFlg))
         {
               pstAuthRejInfo->ucHplmnPsAuthRejCounter++;
               return;
         }
    }

    g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_INVALID;

    Gmm_TimerStop(GMM_TIMER_ALL);                                               /* 停所有Timer,(T3316/3318/3320/3310...)    */
    g_GmmReqCnfMng.ucCnfMask = 0;                                               /* 清除原语等待标志                         */
    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                                    /* 调用状态的公共处理                       */

    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
        {
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
        }
        NAS_GMM_SndMmcMmDetachInfo();
    }

    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);      /* 更新状态设为GU2                          */

    /* 清除相关标志 */
    NAS_GMM_ClearIMSIOfUeID();

    NAS_GMM_DeleteEPlmnList();

    if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
    {                                                                           /* SMS在等待响应                            */
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                              /* 发送PMMSMS_ERROR_IND                     */
        g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
    }

    if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
    {
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                              /* 清除followon标志                         */

        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);
    }

    ucCause = NAS_OM_MM_CAUSE_AUT_NETWORK_REJECT;

    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_AUTH_AND_CIPHER_REJ,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    switch (g_GmmGlobalCtrl.ucSpecProc)
    {
    case GMM_SERVICE_REQUEST_PAGING_RSP:
    case GMM_SERVICE_REQUEST_DATA_IDLE:
    case GMM_SERVICE_REQUEST_SIGNALLING:

        /* 向MMC发送SERVICE REQUEST结果 */
        NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                              NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_DATA_SERVICE_REJ,
                        (VOS_VOID *)&ucCause,
                        NAS_OM_EVENT_SERVICE_REJ_LEN);
        break;
    case GMM_ATTACH_COMBINED:
    case GMM_ATTACH_WHILE_IMSI_ATTACHED:
    case GMM_ATTACH_NORMAL:
    case GMM_ATTACH_NORMAL_CS_TRANS:

        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_ATTACH_FAIL,
                        (VOS_VOID *)&ucCause,
                        NAS_OM_EVENT_ATTACH_FAIL_LEN);
        break;
    case GMM_RAU_COMBINED:
    case GMM_RAU_WITH_IMSI_ATTACH:
    case GMM_RAU_NORMAL:
    case GMM_RAU_NORMAL_CS_TRANS:
    case GMM_RAU_NORMAL_CS_UPDATED:

        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_RAU_FAIL,
                        (VOS_VOID *)&ucCause,
                        NAS_OM_EVENT_RAU_FAIL_LEN);
        break;
    default:
        break;
    }

    Gmm_DelPsLocInfoUpdateUsim();
    NAS_GMM_SndMmAuthenticationFailureInd();                                       /* 发送MMCGMM_AUTHENTICATON_FAILURE_IND     */

    if (0x10 == (g_GmmGlobalCtrl.ucSpecProc & 0xF0))
    {                                                                           /* ATTACH流程                               */
        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {                                                                       /* 需要上报给SM                             */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_AUTHENTICATION_REJ);    /* 通知SM GMM注册失败                       */

            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* 清ucSmCnfFlg标志                         */
        }

        if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
         && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
        {
            NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );
        }
    }
    else
    {                                                                           /* 其他流程                                 */
        if ((GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc)
            || (GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProc))
        {                                                                       /* "Service type"是"data"                   */
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);             /* 通知RABM结果                             */
        }
        else if (0x20 == (g_GmmGlobalCtrl.ucSpecProc & 0xF0))
        {
            if (GMM_TRUE == GMM_IsCasGsmMode())
            {
                /*==>A32D11635*/
                g_GmmGlobalCtrl.ucGprsResumeFlg = GMM_FALSE;
                /*<==A32D11635*/
                /* GMM_SndLlcResumeReq(); */
            }

            if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
            {
                GMM_RauFailureInterSys();
            }
            else
            {
                GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
            }
        }
        else
        {
        }
    }

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* 清除当前流程                             */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvAuthenAndCipherRejectMsg:INFO: specific procedure ended");

    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                        /* 清除保留流程                             */
    Gmm_HoldBufferFree();                                                       /* 清除保留消息                             */
    return;
}

/*******************************************************************************
  Module   : Gmm_RcvIdentityRequestMsg
  Function : 接收Identity Request消息的处理
  Input    : NAS_MSG_STRU *pMsg :NAS消息首地址
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1. 张志勇  2003.12.09  新版作成
  2. x51137 2006/4/28 A32D02889
  3.日    期   : 2007年07月27日
    作    者   : luojian id:60022475
    修改内容   : 问题单号:A32D12606
  4.日    期   : 2011年7月27日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  5.日    期   : 2012年03月03日
    作    者   : l65478
    修改内容   : DTS2012020106640判断ID类型时应该是PTMSI而不是TMSI
  6.日    期   : 2012年3月3日
    作    者   : z00161729
    修改内容   : V7R1 C50 支持ISR修改,T3312启动停止超时均需通知L
*******************************************************************************/
VOS_VOID Gmm_RcvIdentityRequestMsg(
                               NAS_MSG_FOR_PCLINT_STRU *pMsg
                               )
{
    VOS_UINT8           *pucMsgTemp;                                                /* 暂时指针变量                             */
    NAS_MSG_STRU        *pNasMsg;                                                   /* 定义指向NAS消息的指针                    */
    VOS_UINT8            ucMsId;
    NAS_MSG_STRU        *pGmmStatus;
    VOS_UINT8       ucForceToStandby;

    if (GMM_MSG_LEN_IDENTITY_REQUEST > pMsg->ulNasMsgSize)
    {                                                                           /* 如果空中接口消息长度过短                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvIdentityRequestMsg:WARNING: Invalid mandatory information");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;
    }

    if ((GMM_STATUS_DETACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
        && (GMM_REGISTERED_INITIATED != g_GmmGlobalCtrl.ucState))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvIdentityRequestMsg:WARNING: IDENTITY REQUEST is unexpected");
        return;
    }

    if ( 0 != (pMsg->aucNasMsg[2] & 0x08))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvIdentityRequestMsg:WARNING: The length of IDENTITY REQUEST is invalid");
        pGmmStatus =
            Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;
    }

    pucMsgTemp = &(pMsg->aucNasMsg[0]);                                         /* 得到空中接口消息首地址                   */

    /* ==>A32D12606 */
    ucForceToStandby = (VOS_UINT8)((*(pucMsgTemp+2) >> 4) & 0x07);
    /* <==A32D12606 */
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
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvIdentityRequestMsg:WARNING: Wrong information of [Force to standby]");
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }
    ucMsId = (VOS_UINT8)((*(pucMsgTemp+2)) & 0x07);
    /* ==>A32D12606 */
    if ((GMM_MOBILE_ID_IMSI != ucMsId)
        && (GMM_MOBILE_ID_IMEI != ucMsId)
        && (GMM_MOBILE_ID_IMEISV != ucMsId)
        && (GMM_MOBILE_ID_TMSI_PTMSI!= ucMsId ))
    {
        ucMsId = GMM_MOBILE_ID_IMSI;                                            /* All other values are interpreted as      *
                                                                                 * IMSI by this version of the protocol.    */
    }

    if ((GMM_MOBILE_ID_IMSI == ucMsId)
        && (GMM_UEID_IMSI != (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_IMSI)))
    {
        ucMsId = GMM_MOBILE_ID_NONE;
    }

    if ((VOS_FALSE  == NAS_MML_IsPtmsiValid())
     && (GMM_MOBILE_ID_TMSI_PTMSI == ucMsId))
    {
        ucMsId = GMM_MOBILE_ID_NONE;
    }

    /* <==A32D12606 */
    pNasMsg = Gmm_IdentityResponseMsgMake(ucMsId);                              /* 调用Identity response的make函数          */

    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);                      /* 调用发送RRMM_DATA_REQ函数                */

    if (GMM_TRUE == GMM_IsCasGsmMode())
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
    return;
}

/*******************************************************************************
  Module   : Gmm_RcvGmmInformationMsg
  Function : 接收information消息后的处理
  Input    : NAS_MSG_STRU *pMsg :NAS消息首地址
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.09  新版作成
    2.日    期   : 2011年10月08日
      作    者   : s46746
      修改内容   : V7R1 phase II高优先级状态机实现
    3.日    期   : 2013年5月17日
      作    者   : l00167671
      修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*******************************************************************************/
VOS_VOID Gmm_RcvGmmInformationMsg(
    NAS_MSG_FOR_PCLINT_STRU             *pMsg
)
{
    NAS_MM_INFO_IND_STRU                                    stMmInfo;
    VOS_UINT32                                              ulIeOffset = GMM_MSG_LEN_GMM_INFORMATION;
    VOS_UINT32                                              ulRst;
    VOS_UINT8                                               ucNetworkNameFlg;
    NAS_MML_OPERATOR_NAME_INFO_STRU                         stOldOperatorName;
    NAS_MML_OPERATOR_NAME_INFO_STRU                        *pstCurrOperatorName = VOS_NULL_PTR;

    /* Added by l00167671 for NV拆分项目 , 2013-05-17, begin */
    NAS_MMC_NVIM_OPERATOR_NAME_INFO_STRU                    stNvimOperatorName;
    /* Added by l00167671 for NV拆分项目 , 2013-05-17, begin */

    PS_MEM_SET(&stMmInfo, 0, sizeof(NAS_MM_INFO_IND_STRU));

    ulRst = NAS_GMM_CheckGmmInfoMsg(pMsg);
    if (VOS_ERR == ulRst)
    {
        return;
    }

    pstCurrOperatorName = NAS_MML_GetOperatorNameInfo();
    PS_MEM_CPY(&stOldOperatorName, pstCurrOperatorName, sizeof(NAS_MML_OPERATOR_NAME_INFO_STRU));

    ucNetworkNameFlg = VOS_FALSE;
    for (; (ulIeOffset < pMsg->ulNasMsgSize);)
    {                                                                           /* 存储IE的偏移量小于空口消息的长度         */
        switch (pMsg->aucNasMsg[ulIeOffset])
        {                                                                       /* IEI                                      */
            case GMM_IEI_FULL_NAME_FOR_NETWORK:                                 /* Full name for network                    */
                ulRst = NAS_GMM_DecodeFullNameforNetworkIE(pMsg, &ulIeOffset);

                ucNetworkNameFlg = VOS_TRUE;
                break;

            case GMM_IEI_SHORT_NAME_FOR_NETWORK:                                /* Short name for network                   */
                ulRst = NAS_GMM_DecodeShortNameforNetworkIE(pMsg, &ulIeOffset);

                ucNetworkNameFlg = VOS_TRUE;
                break;

            case GMM_IEI_LOCAL_TIME_ZONE:                                       /* Local time zone                          */
                ulRst = NAS_GMM_DecodeLocalTimeZoneIE(pMsg, &ulIeOffset, &stMmInfo);
                break;

            case GMM_IEI_UNIVERSAL_TIME_AND_LOCAL_TIME_ZONE:                    /* Universal time and local time zone       */
                ulRst = NAS_GMM_DecodeUniversalTimeAndLocalTimeZoneIE(pMsg, &ulIeOffset, &stMmInfo);
                break;

            case GMM_IEI_LSA_IDENTITY:                                          /* LSA Identity                             */
                ulRst = NAS_GMM_DecodeLSAIdentityIE(pMsg, &ulIeOffset, &stMmInfo);
                break;

            case GMM_IEI_NETWORK_DAYLIGHT_SAVING_TIME:                          /* Network Daylight Saving Time             */
                ulRst = NAS_GMM_DecodeDaylightSavingTimeIE(pMsg, &ulIeOffset, &stMmInfo);
                break;

            default:
                NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_RcvGmmInformationMsg:WARNING: unknown IE.");
                ulIeOffset += pMsg->aucNasMsg[ulIeOffset + 1] + 2;
                break;
        }

        if (VOS_ERR == ulRst)
        {
            return;
        }

        /* 如果消息解析后的网络名与之前保存的内容不同,需要写NV */
        if (0 != VOS_MemCmp(pstCurrOperatorName, &stOldOperatorName, sizeof(NAS_MML_OPERATOR_NAME_INFO_STRU)))
        {
            /* Modified by l00167671 for NV拆分项目 , 2013-05-17, begin */
            PS_MEM_CPY(&stNvimOperatorName, pstCurrOperatorName, sizeof(stNvimOperatorName));

            if (NV_OK != NV_Write(en_NV_Item_Network_Name_From_MM_Info,
                                  &stNvimOperatorName,
                                  sizeof(stNvimOperatorName)))
            {
                NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_RcvGmmInformationMsg:Write NV fail.");
            }
            /* Modified by l00167671 for NV拆分项目 , 2013-05-17, end */

        }
    }

    /* GMM INFO中包含有用信息时，上报给MMC */
    if ( (0 != stMmInfo.ucIeFlg)
      || (VOS_TRUE == ucNetworkNameFlg))
    {
        Gmm_SndMmcInfoInd(&stMmInfo);
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_PtmsiReallocationCompleteMsgMake
  Function : 对P-TMSI reallocation complete进行封装
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1.张志勇  2003.12.09  新版作成
*******************************************************************************/
NAS_MSG_STRU *Gmm_PtmsiReallocationCompleteMsgMake(VOS_VOID)
{
    NAS_MSG_STRU * ptrNasMsg;

    ptrNasMsg = (NAS_MSG_STRU *)Gmm_MemMalloc(sizeof(NAS_MSG_STRU));            /* 申请内存空间                             */
    if (VOS_NULL_PTR == ptrNasMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
            "Gmm_PtmsiReallocationCompleteMsgMake:Error: Alloc Memory fail.");
        return ptrNasMsg;
    }
    Gmm_MemSet(ptrNasMsg, 0, sizeof(NAS_MSG_STRU));                             /* 将申请的内存空间清0                      */

    ptrNasMsg->ulNasMsgSize = GMM_MSG_LEN_P_TMSI_REALLOCATION_COMPLETE;
    ptrNasMsg->aucNasMsg[0] = GMM_PD_GMM;
    ptrNasMsg->aucNasMsg[1] = GMM_MSG_P_TMSI_REALLOCATION_COMPLETE;

    return ptrNasMsg;
}

/*******************************************************************************
Module   : Gmm_AuthenAndCipherResponseMsgMake
Function : 对AUTHENTICATION AND CIPHERING RESPONSE进行封装
Input    : VOS_UINT8 ucResFlg :0 时，表示不需回传res；非空时，表示需回传res
Output   : 无
NOTE     : 无
Return   : 无
History  :
   1.张志勇  2003.12.09  新版作成
  2.日    期   : 2012年05月25日
    作    者   : w00166186
    修改内容   : DTS2012052108400,IMEI填写错误
 3.日    期   : 2014年6月17日
   作    者   : z00234330
   修改内容   : PCINT清理
*******************************************************************************/
NAS_MSG_STRU *Gmm_AuthenAndCipherResponseMsgMake(
                                                 VOS_UINT8 ucResFlg                 /* 0:表示不需回传res;1:表示需回传res        */
                                                 )
{
    NAS_MSG_FOR_PCLINT_STRU *ptrNasMsg;                                         /* 定义指向NAS消息结构体的指针              */
    NAS_MSG_STRU *pNasMsg;                                                      /* 定义指向NAS消息结构体的指针              */
    VOS_UINT8 ucTotalLen;                                                           /* NAS消息总长                              */
    VOS_UINT8 ucTempLen;                                                            /* NAS消息临时长度                          */
    VOS_UINT8 j;                                                                    /* 循环控制变量                             */
    VOS_UINT8                           *pucImeisv;

    pucImeisv    = NAS_MML_GetImeisv();

    ucTotalLen = GMM_MSG_LEN_AUTHENTICATION_AND_CIPHERING_RESPONSE;
    if (GMM_AUTH_AND_CIPH_RES_NEEDED == ucResFlg)
    {                                                                           /* 需回传res                                */
        if (0 == g_GmmAuthenCtrl.ucResExtLen)
        {                                                                       /* 全局中RES Extension长度标识为0           */
            ucTotalLen += 5;
        }
        else
        {                                                                       /* 全局中RES Extension长度标识不为0         */
            ucTotalLen += (7 + g_GmmAuthenCtrl.ucResExtLen);
        }

    }
    if (GMM_TRUE == g_GmmAuthenCtrl.ucImeisvFlg)
    {                                                                           /* 全局变量显示RESPONSE消息中需要带IMEISV   */
        ucTotalLen += 11;
    }

    if (ucTotalLen < 4)
    {
        pNasMsg = (NAS_MSG_STRU *)Gmm_MemMalloc(sizeof(NAS_MSG_STRU));          /* 申请内存空间                             */
        if (VOS_NULL_PTR == pNasMsg)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_AuthenAndCipherResponseMsgMake:Error: Alloc Memory fail.");
            return pNasMsg;
        }
        ptrNasMsg = (NAS_MSG_FOR_PCLINT_STRU *)pNasMsg;
        Gmm_MemSet(ptrNasMsg, 0, sizeof(NAS_MSG_STRU));                         /* 将申请的内存空间清0                      */
    }
    else
    {
        pNasMsg = (NAS_MSG_STRU *)Gmm_MemMalloc(
                                    (sizeof(NAS_MSG_STRU) + ucTotalLen) - 4);     /* 申请内存空间                             */
        if (VOS_NULL_PTR == pNasMsg)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_AuthenAndCipherResponseMsgMake:Error: Alloc Memory fail.");
            return pNasMsg;
        }
        ptrNasMsg = (NAS_MSG_FOR_PCLINT_STRU *)pNasMsg;
        Gmm_MemSet(ptrNasMsg, 0, ((sizeof(NAS_MSG_STRU) + ucTotalLen) - 4));      /* 将申请的内存空间清0                      */
    }

    ptrNasMsg->ulNasMsgSize = ucTotalLen;
    ptrNasMsg->aucNasMsg[0] = GMM_PD_GMM;
    ptrNasMsg->aucNasMsg[1] = GMM_MSG_AUTHENTICATION_AND_CIPHERING_RESPONSE;
    ptrNasMsg->aucNasMsg[2] = (VOS_UINT8)(g_GmmAuthenCtrl.ucAcRefNum & 0x0F);

    ucTempLen = 3;                                                              /* 指向Authentication Response parameter域  */
    if (GMM_AUTH_AND_CIPH_RES_NEEDED == ucResFlg)
    {
        /* Modified by z00234330 for PCLINT清理, 2014-06-24, begin */
        /*lint -e961*/
        ptrNasMsg->aucNasMsg[ucTempLen++] =
            GMM_IEI_AUTHENTICATION_PARAMETER_RESPONSE;                          /* 对IEI赋值                                */
        /*lint +e961*/
        for (j=0; j<4; j++)
        {                                                                       /* 填写RES                                  */
            ptrNasMsg->aucNasMsg[ucTempLen] = g_GmmAuthenCtrl.aucRes[j];
            ucTempLen++;
        }
        #ifdef GSM_GCF_RS_SIM_STUB
        ucTempLen = ucTempLen - 4;
        ptrNasMsg->aucNasMsg[ucTempLen] = 0x11;
        ucTempLen++;
        ptrNasMsg->aucNasMsg[ucTempLen] = 0x10;
        ucTempLen++;
        ptrNasMsg->aucNasMsg[ucTempLen] = 0x13;
        ucTempLen++;
        ptrNasMsg->aucNasMsg[ucTempLen] = 0x12;
        ucTempLen++;
        #endif
    }

    if (GMM_TRUE == g_GmmAuthenCtrl.ucImeisvFlg)
    {                                                                           /* 全局变量显示RESPONSE消息中需要带IMEISV   */
        ptrNasMsg->aucNasMsg[ucTempLen] = GMM_IEI_IMEISV;                     /* 对IEI赋值                                */
        ucTempLen++;
        ptrNasMsg->aucNasMsg[ucTempLen] = 9;                                  /* 对length域赋值                           */
        ucTempLen++;
        ptrNasMsg->aucNasMsg[ucTempLen] = (VOS_UINT8)(GMM_MOBILE_ID_IMEISV        /* b2~b0                                    */
                                            | GMM_EVEN_NUM_OF_ID_DIGITS         /* b3                                       */
                                            | (pucImeisv[0] << 4));          /* b7~b4                                    */
        ucTempLen++;
        for (j=0; j<7; j++ )
        {
            ptrNasMsg->aucNasMsg[ucTempLen] =
                (VOS_UINT8)((pucImeisv[1 + (2*j)] & 0x0F)
                | (pucImeisv[2 + (2*j)] << 4));
            ucTempLen++;
        }
        ptrNasMsg->aucNasMsg[ucTempLen] =
            (VOS_UINT8)(pucImeisv[15] | 0xF0);          /* 最后字节的b7~b4:置为'1111'               */
        ucTempLen++;
    }
    if (GMM_AUTH_AND_CIPH_RES_NEEDED == ucResFlg)
    {
        if (0 != g_GmmAuthenCtrl.ucResExtLen)
        {                                                                       /* 全局中RES Extension长度标识"不为0        */
            ptrNasMsg->aucNasMsg[ucTempLen]
                = GMM_IEI_AUTHENTICATION_RESPONSE_PARAMETER;                    /* 对IEI赋值为29                            */
            ucTempLen++;
            ptrNasMsg->aucNasMsg[ucTempLen]
                = g_GmmAuthenCtrl.ucResExtLen;                                  /* 对length域赋值                           */
            ucTempLen++;
            for (j=0; j<g_GmmAuthenCtrl.ucResExtLen; j++)
            {                                                                   /* 填写RES extension                        */
                ptrNasMsg->aucNasMsg[ucTempLen]= g_GmmAuthenCtrl.aucResExt[j];
                ucTempLen++;
            }
        }
    }
    /* Modified by z00234330 for PCLINT清理, 2014-06-24, begin */

    return (NAS_MSG_STRU *)ptrNasMsg;
}

/*******************************************************************************
  Module   : Gmm_AuthenAndCipherFailureMsgMake
  Function : 对Authentication and Ciphering Failure进行封装
  Input    : VOS_UINT8  GmmCause :失败原因
             VOS_UINT8  ucFailParaLenFailure :  Parameter的长度，单位为字节 ；
                                            0代表Failure Paramete无效
             VOS_UINT8 *pFailPara : Authentication Failure parameter 首地址
  Output   : 无
  NOTE     : 无
  Return   : NAS_MSG_STRU     *ptrNasMsg:    NAS消息首地址
  History  :
    1.张志勇  2003.12.09  新版作成
*******************************************************************************/
NAS_MSG_STRU *Gmm_AuthenAndCipherFailureMsgMake(
                                                VOS_UINT8  GmmCause,                /* 失败原因                                 */
                                                VOS_UINT8  ucFailParaLen,           /* Parameter的长度，单位为字节 ；           */
                                                VOS_UINT8 *pFailPara                /* Authentication Failure parameter 首地址  */
                                                )
{
    NAS_MSG_FOR_PCLINT_STRU *ptrNasMsg;
    NAS_MSG_STRU            *pNasMsg;
    VOS_UINT8     ucTotalLen;                                                       /* 空中接口消息的长度                       */
    VOS_UINT8 i;                                                                    /* 循环控制变量                             */

    ucTotalLen = GMM_MSG_LEN_AUTHENTICATION_AND_CIPHERING_FAILURE;
    if (NAS_MML_REG_FAIL_CAUSE_SYNCH_FAILURE == GmmCause )
    {                                                                           /* GmmCause为Synch failure                  */
        ucTotalLen += 16;
    }
    if(ucTotalLen < 4)
    {                                                                           /* 长度不足4个时                            */
        pNasMsg = (NAS_MSG_STRU *)Gmm_MemMalloc(sizeof(NAS_MSG_STRU));        /* 申请内存空间                             */
        if (VOS_NULL_PTR == pNasMsg)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_AuthenAndCipherFailureMsgMake:Error: Alloc Memory fail.");
            return pNasMsg;
        }
        ptrNasMsg = (NAS_MSG_FOR_PCLINT_STRU *)pNasMsg;
        Gmm_MemSet(ptrNasMsg, 0, sizeof(NAS_MSG_STRU));                         /* 将申请的内存空间清0                      */
    }
    else
    {
        pNasMsg = (NAS_MSG_STRU *)Gmm_MemMalloc(
                                    (sizeof(NAS_MSG_STRU) + ucTotalLen) - 4);     /* 申请内存空间                             */
        if (VOS_NULL_PTR == pNasMsg)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_AuthenAndCipherFailureMsgMake:Error: Alloc Memory fail.");
            return pNasMsg;
        }
        ptrNasMsg = (NAS_MSG_FOR_PCLINT_STRU *)pNasMsg;
        Gmm_MemSet(ptrNasMsg, 0, ((sizeof(NAS_MSG_STRU) + ucTotalLen) - 4));      /* 将申请的内存空间清0                      */
    }

    ptrNasMsg->ulNasMsgSize = ucTotalLen;                                       /* 填写原语长度域                           */
    ptrNasMsg->aucNasMsg[0] = GMM_PD_GMM;
    ptrNasMsg->aucNasMsg[1] = GMM_MSG_AUTHENTICATION_AND_CIPHERING_FAILURE;
    ptrNasMsg->aucNasMsg[2] = GmmCause;

    if (NAS_MML_REG_FAIL_CAUSE_SYNCH_FAILURE == GmmCause )
    {                                                                           /* GmmCause为Synch failure                  */
        ptrNasMsg->aucNasMsg[3] = GMM_IEI_AUTHENTICATION_FAILURE_PARAMETER;
        ptrNasMsg->aucNasMsg[4] = 14;
        if ( ucFailParaLen > 14 )
        {
            for ( i = 0; i < 14; i++)
            {
                ptrNasMsg->aucNasMsg[5+i] = *(pFailPara + i);
            }
        }
        else
        {
            for ( i = 0; i < ucFailParaLen; i++)
            {
                ptrNasMsg->aucNasMsg[5+i] = *(pFailPara + i);
            }
            if ( ucFailParaLen < 14 )
            {
                for ( ; i < 14; i++)
                {
                    ptrNasMsg->aucNasMsg[5+i] = 0xFF;
                }
            }
        }
    }

    return (NAS_MSG_STRU *)ptrNasMsg;
}

/*******************************************************************************
  Module   : Gmm_IdentityResponseMsgMake
  Function : 对Identity response进行封装
  Input    : UNCHAR IdType    :bit  3 2 1
                                    001: IMSI ，不超过15 digits
                                    010: IMEI ，IMEI由15 digits组成
                                    011: IMEISV，IMEISV由16 digits组成
                                    100: TMSI,8 digits
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.张志勇  2003.12.09  新版作成
  2.日    期   : 2007年07月27日
    作    者   : luojian id:60022475
    修改内容   : 问题单号:A32D12606
  3.日    期   : 2011年7月27日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  4.日    期   : 2012年03月03日
    作    者   : l65478
    修改内容   : DTS2012020106640判断ID类型时应该是PTMSI而不是TMSI
  5.日    期   : 2012年05月17日
    作    者   : l65478
    修改内容   : DTS2012051700882,IMEI错误
*******************************************************************************/
NAS_MSG_STRU *Gmm_IdentityResponseMsgMake(
                                          VOS_UINT8 IdType                          /* 对Identity request 要求的ID              */
                                          )
{
    NAS_MSG_FOR_PCLINT_STRU            *ptrNasMsg;
    NAS_MSG_STRU                       *pNasMsg;
    MM_CSPS_INFO_ST                     stCsInfo;
    VOS_UINT8                           ucTotalLen;                                                 /* 定义临时变量                             */
    VOS_UINT8                           i;                                                          /* 循环控制变量                             */
    VOS_UINT8                          *pucMmlImsi;
    VOS_UINT8                          *pucImeisv;

    pucImeisv    = NAS_MML_GetImeisv();
    ucTotalLen = 2;                                                             /* 初始化临时变量                           */

    pucMmlImsi = NAS_MML_GetSimImsi();
    if (GMM_MOBILE_ID_IMSI == IdType)
    {                                                                           /* IdType为IMSI                             */
        ucTotalLen += (pucMmlImsi[0] + 1);
    }

    /* ==>A32D12606 */
    else if(GMM_MOBILE_ID_TMSI_PTMSI == IdType)
    {
        ucTotalLen += 6;
    }
    /* <==A32D12606 */
    else if(GMM_MOBILE_ID_IMEI == IdType)
    {                                                                           /* Identication_TypeOfID为IMEI              */
        ucTotalLen += 9;
    }
    else if (GMM_MOBILE_ID_NONE == IdType)
    {
        ucTotalLen += 4;
    }
    else
    {                                                                           /* Identication_TypeOfID为IMEISV            */
        ucTotalLen += 10;
    }

    pNasMsg = (NAS_MSG_STRU *)Gmm_MemMalloc(
                                (sizeof(NAS_MSG_STRU) + ucTotalLen) - 4);         /* 申请内存空间                             */
    if (VOS_NULL_PTR == pNasMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
            "Gmm_IdentityResponseMsgMake:Error: Alloc Memory fail.");
        return pNasMsg;
    }

    ptrNasMsg = (NAS_MSG_FOR_PCLINT_STRU *)pNasMsg;
    Gmm_MemSet(ptrNasMsg, 0, ((sizeof(NAS_MSG_STRU) + ucTotalLen) - 4));          /* 将申请的内存空间清0                      */

    ptrNasMsg->ulNasMsgSize = ucTotalLen;
    ptrNasMsg->aucNasMsg[0] = GMM_PD_GMM;
    ptrNasMsg->aucNasMsg[1] = GMM_MSG_IDENTITY_RESPONSE;

    if (GMM_MOBILE_ID_IMSI == IdType)                                           /* IdType为IMSI                             */
    {
        Gmm_MemCpy(&ptrNasMsg->aucNasMsg[2],
                   pucMmlImsi,
                   pucMmlImsi[0] + 1);
    }


    if (GMM_MOBILE_ID_IMEI == IdType)
    {                                                                           /* IdType为IMEI                             */
        ptrNasMsg->aucNasMsg[2] = 8;                                            /* 对length域赋值                           */
        ptrNasMsg->aucNasMsg[3] = (VOS_UINT8)(GMM_MOBILE_ID_IMEI                    /* b2~b0                                    */
                                  | GMM_ODD_NUM_OF_ID_DIGITS                    /* b3                                       */
                                  | (pucImeisv[0] << 4));                    /* b7~b4                                    */
        for (i=0; i<7; i++ )
        {
            ptrNasMsg->aucNasMsg[4 + i] =
                (VOS_UINT8)((pucImeisv[1 + (2*i)] & 0x0F)
                | ((pucImeisv[2 + (2*i)]) << 4));
        }
        ptrNasMsg->aucNasMsg[10] &= 0x0F;                                       /* 最后字节的b7~b4:置为'0000'               */
    }

    if (GMM_MOBILE_ID_IMEISV == IdType)
    {                                                                           /* IdType为IMEISV                           */
        ptrNasMsg->aucNasMsg[2] = 9;                                            /* 对length域赋值                           */
        ptrNasMsg->aucNasMsg[3] = (VOS_UINT8)(GMM_MOBILE_ID_IMEISV                  /* b2~b0                                    */
                                  | GMM_EVEN_NUM_OF_ID_DIGITS                   /* b3                                       */
                                  | (pucImeisv[0] << 4));                    /* b7~b4                                    */
        for (i=0; i<7; i++)
        {
            ptrNasMsg->aucNasMsg[4 + i] =
                (VOS_UINT8)((pucImeisv[1 + (2*i)] & 0x0F)
                | (pucImeisv[2 + (2*i)] << 4));
        }
        ptrNasMsg->aucNasMsg[11] =
            (VOS_UINT8)(pucImeisv[15] | 0xF0);          /* 最后字节的b7~b4:置为'1111'               */

    }
    /* ==>A32D12606 */
    if (GMM_MOBILE_ID_TMSI_PTMSI == IdType)
    {
        PS_MEM_SET(&stCsInfo, 0, sizeof(MM_CSPS_INFO_ST));
        GMM_GetSecurityInfo(&stCsInfo);
        /*MM_GetSecurityInfo(&stCsInfo);
 */
        ptrNasMsg->aucNasMsg[2]   = 5;                                                              /* Length of mobile identity contents       */
        ptrNasMsg->aucNasMsg[3]   = 0xF0;                                                           /* 高4bit置"1111"                           */
        ptrNasMsg->aucNasMsg[3]  |= GMM_MOBILE_ID_TMSI_PTMSI;                                       /* Type of identity                         */

        /* 填写TMSI  */
        ptrNasMsg->aucNasMsg[4]   = stCsInfo.aucPTMSI[0];
        ptrNasMsg->aucNasMsg[5]   = stCsInfo.aucPTMSI[1];
        ptrNasMsg->aucNasMsg[6]   = stCsInfo.aucPTMSI[2];
        ptrNasMsg->aucNasMsg[7]   = stCsInfo.aucPTMSI[3];
    }
    if (GMM_MOBILE_ID_NONE == IdType)
    {                                                                           /* IdType为NONE                             */
        ptrNasMsg->aucNasMsg[2] = 3;                                            /* 对length域赋值                           */
        ptrNasMsg->aucNasMsg[3] = (VOS_UINT8)(GMM_MOBILE_ID_NONE                /* b2~b0                                    */
                                  | GMM_ODD_NUM_OF_ID_DIGITS);                  /* b3                                       */
    }

    /* <==A32D12606 */
    return (NAS_MSG_STRU *)ptrNasMsg;
}

/*******************************************************************************
  Module   : Gmm_Start_StopedRetransmissionTimer
  Function : 如果存在被停止的retransmission timer将其启动
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1.张志勇  2003.12.11  新版作成
*******************************************************************************/
VOS_VOID Gmm_Start_StopedRetransmissionTimer(VOS_VOID)
{
    if (0x10 == (g_GmmGlobalCtrl.ucSpecProc & 0xF0))
    {                                                                           /* 当前流程为attach,启T3310                 */
        if (0 == (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3310)))
        {                                                                           /* 该timer已经启动                          */
            Gmm_TimerStart(GMM_TIMER_T3310);
        }
    }
    else if (0x20 == (g_GmmGlobalCtrl.ucSpecProc & 0xF0))
    {                                                                           /* 当前流程为RAU,启动T3330                  */
        if (0 == (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3330)))
        {                                                                           /* 该timer已经启动                          */
            Gmm_TimerStart(GMM_TIMER_T3330);
        }
    }
    else if (0x30 == (g_GmmGlobalCtrl.ucSpecProc & 0xF0))
    {                                                                           /* 当前流程为DETACH,启动T3321               */
        if (0 == (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3321)))
        {                                                                           /* 该timer已经启动                          */
            Gmm_TimerStart(GMM_TIMER_T3321);
        }
    }
    else if (0x40 == (g_GmmGlobalCtrl.ucSpecProc & 0xF0))
    {                                                                           /* 当前流程为SERVICE_REQUEST,启动T3317      */
        if (0 == (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3317)))
        {                                                                           /* 该timer已经启动                          */
            Gmm_TimerStart(GMM_TIMER_T3317);
        }
    }
    else
    {
    }
}

/*******************************************************************************
  Module   : Gmm_Stop_RetransmissionTimer
  Function : 停止正在运行的retransmission timer
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1.张志勇  2003.12.11  新版作成
*******************************************************************************/
VOS_VOID Gmm_Stop_RetransmissionTimer(VOS_VOID)
{
    if (0x10 == (g_GmmGlobalCtrl.ucSpecProc & 0xF0))
    {                                                                           /* 当前流程为attach,停T3310                 */
        Gmm_TimerStop(GMM_TIMER_T3310);
    }
    else if (0x20 == (g_GmmGlobalCtrl.ucSpecProc & 0xF0))
    {                                                                           /* 当前流程为RAU,停T3330                    */
        Gmm_TimerStop(GMM_TIMER_T3330);
    }
    else if (0x30 == (g_GmmGlobalCtrl.ucSpecProc & 0xF0))
    {                                                                           /* 当前流程为DETACH,停T3321                 */
        Gmm_TimerStop(GMM_TIMER_T3321);
    }
    else if (0x40 == (g_GmmGlobalCtrl.ucSpecProc & 0xF0))
    {                                                                           /* 当前流程为SERVICE_REQUEST,停T3317        */
        Gmm_TimerStop(GMM_TIMER_T3317);
    }
    else
    {
    }
}

/*******************************************************************************
  Module   : Gmm_AuCntFail
  Function : 当GMM Authentication attempt counter等于3时的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1.张志勇  2003.12.11  新版作成
    2.日    期   : 2009年03月31日
      作    者   : L65478
      修改内容   : 根据问题单号：AT2D10529两次鉴权失败后没有释放RRC连接
    3.日    期   : 2012年4月20日
      作    者   : l00130025
      修改内容   : DTS2012032004389，Netork连续3次被Ms Auth Rej或T3318/T3320超时时，没有通知GAS Bar掉当前小区
*******************************************************************************/
VOS_VOID Gmm_AuCntFail(VOS_VOID)
{
    g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;                                      /* GMM Authentication attempt counter清0    */
    g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_INVALID;

    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停T3318                                  */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停T3320                                  */

    NAS_GMM_SndGasGprsAuthFailNotifyReq();

    Gmm_SndRrmmRelReq(RRC_CELL_BARRED);

    Gmm_Start_StopedRetransmissionTimer();                                      /* 存在被停止的retransmission timer将其启动 */
}

/*******************************************************************************
  Module   : Gmm_Au_MacAutnWrong
  Function : 当MAC错误或AUTN不存在时的处理
  Input    : VOS_UINT8  ucWrongCause    ：错误原因
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1.张志勇  2003.12.11  新版作成
    2.日    期   : 2006年12月5日
      作    者   : luojian 60022475
      修改内容   : Maps3000接口修改
    3.日    期   : 2009年03月31日
      作    者   : L65478
      修改内容   : 根据问题单号：AT2D10529两次鉴权失败后没有释放RRC连接
    4.日    期   : 2012年4月20日
      作    者   : l00130025
      修改内容   : DTS2012032004389，Netork连续3次被Ms Auth Rej或T3318/T3320超时时，没有通知GAS Bar掉当前小区
    5.日    期  :2014年01月09日
      作    者  :l65478
      修改内容  :DTS2014010704608:第一次鉴权响应和网络发起的第二次鉴权请求冲突
*******************************************************************************/
VOS_VOID Gmm_Au_MacAutnWrong(
                         VOS_UINT8  ucWrongCause                                    /* 错误原因                                 */
                         )
{
    NAS_MSG_STRU    *pNasMsg = VOS_NULL_PTR;

    if ((GMM_AUTHEN_REJ_CAUSE_MAC_FAIL == g_GmmAuthenCtrl.ucLastFailCause)
        || (GMM_AUTHEN_REJ_CAUSE_GSM_FAIL == g_GmmAuthenCtrl.ucLastFailCause))
     {                                                                          /* T3318在运行                              */
        pNasMsg = Gmm_AuthenAndCipherFailureMsgMake(ucWrongCause, 0, VOS_NULL_PTR);     /* AUTHENTICATION AND CIPHERING FAILURE作成 */

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH,pNasMsg);                   /* 调用发送函数                             */

        Gmm_TimerStop(GMM_TIMER_T3316);                                         /* 停止T3316                                */

        /* 清除鉴权相关全局变量 */
        g_GmmAuthenCtrl.ucResStoredFlg       = GMM_FALSE;
        g_GmmAuthenCtrl.ucRandStoredFlg      = GMM_FALSE;

        g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;                                  /* GMM Authentication attempt counter清0    */
        g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_INVALID;


        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停T3318                                  */

        NAS_GMM_SndGasGprsAuthFailNotifyReq();

        Gmm_SndRrmmRelReq(RRC_CELL_BARRED);

        Gmm_Start_StopedRetransmissionTimer();                                  /* 存在被停止的retransmission timer将其启动 */
     }
     else
     {                                                                          /* T3318不在运行                            */
         if(NAS_MML_REG_FAIL_CAUSE_GSM_AUT_UNACCEPTABLE == ucWrongCause)
         {
             g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_GSM_FAIL;
         }
         else
         {
             g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_MAC_FAIL;
         }
         pNasMsg = Gmm_AuthenAndCipherFailureMsgMake(ucWrongCause, 0, VOS_NULL_PTR);    /* AUTHENTICATION AND CIPHERING FAILURE作成 */

         Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH,pNasMsg);                  /* 调用发送函数                             */
         Gmm_TimerStop(GMM_TIMER_T3320);                                        /* 停T3320(如果在运行)                      */
         Gmm_TimerStart(GMM_TIMER_T3318);                                       /* 启T3318                                  */
         Gmm_Stop_RetransmissionTimer();                                        /* 停止正在运行的retransmission timer       */
     }
}

/*******************************************************************************
Module   : Gmm_RcvPtmsiRelocCmdIEChk
Function : 收到P_TMSI reallocation消息中的TE有效性检查
Input    : NAS_MSG_STRU *pMsg
Output   : 无
NOTE     : 无
Return   : 无
History  :
    1. 张志勇     2005.01.27  新版作成
    2. 张志勇  2005.03.26  NAS_IT_BUG_033对应
    3.日    期   : 2007年07月27日
      作    者   : luojian id:60022475
      修改内容   : 问题单号:A32D12606
*******************************************************************************/
VOS_UINT8 Gmm_RcvPtmsiRelocCmdIEChk(
                                NAS_MSG_FOR_PCLINT_STRU *pMsg
                                )
{
    VOS_UINT8        *pucMsgTemp;                                               /* 暂时指针变量                             */
    VOS_UINT8         ucForceToStandby;

    pucMsgTemp = pMsg->aucNasMsg;                                               /* 得到空中接口消息首地址                   */

    /*lint -e961*/
    pucMsgTemp +=2;                                                             /* 指针指到Allocated P-TMSI域               */
    if (5 != *(pucMsgTemp++))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvPtmsiRelocCmdIEChk:WARNING: The length of P-TMSI REALLOCATION is invalid");
        return GMM_FALSE;
    }
    if (GMM_MOBILE_ID_TMSI_PTMSI != ((*pucMsgTemp++) & 0x07))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvPtmsiRelocCmdIEChk:WARNING: MS ID in P-TMSI REALLOCATION is not P-TMSI");
        return GMM_FALSE;
    }
    /*lint +e961*/

    ucForceToStandby = (VOS_UINT8)(*(pucMsgTemp + 10) & 0x07);
    if (1 == ucForceToStandby)
    {
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_TRUE;
    }
    else if (0 == ucForceToStandby)
    {
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }
    else
    {                                                                           /* force to standby                         */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvPtmsiRelocCmdIEChk:WARNING: IE\" Force To Standby\" of P-TMSI REALLOCATION is invalid");
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }

    return GMM_TRUE;
}

/*****************************************************************************
 Prototype      :  GMM_GetSecurityInfo
 Description    :  查询GMM的安全上下文信息函数
 Input          :
 Output         : ---
 Return Value   : 1     返回成功
                  0     返回失败
 Calls          : ---
 Called By      :

 History        : ---
  1.Date        : ---
    Author      : ---
    Modification: ---

  2.日    期   : 2011年7月12日
    作    者   : zhoujun 40661
    修改内容   : 修改SIM保存内容的判断
  3.日    期   : 2011年7月27日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
*****************************************************************************/
VOS_VOID GMM_GetSecurityInfo(MM_CSPS_INFO_ST *pPsInfo)
{

    NAS_MML_SIM_STATUS_STRU             *pstSimStatusInfo;
    VOS_UINT8                           *pucMmlImsi;

    pstSimStatusInfo        = NAS_MML_GetSimStatus();
    if (VOS_NULL_PTR == pPsInfo)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                    "GMM_GetSecurityInfo: ERROR: Para check error!");

        return;
    }

    /* 将全局结构中相应信息拷贝到结构 pCsInfo 中 */
    /* 初始化结构中 InfoMask 变量 */
    pPsInfo->ucInfoMask = 0x0;

    if (VOS_FALSE == pstSimStatusInfo->ucSimPresentStatus) /* 卡不存在 */
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO,
                    "GMM_GetSecurityInfo: INFO: SIM is not present!");

        return;
    }

    /* 拷贝 Ck、Ik 和 Kc */
    pPsInfo->ucInfoMask |= 0x1F;
    PS_MEM_CPY(pPsInfo->aucCk, NAS_MML_GetSimPsSecurityUmtsCk(), 16);

    PS_MEM_CPY(pPsInfo->aucIk, NAS_MML_GetSimPsSecurityUmtsIk(), 16);

    PS_MEM_CPY(pPsInfo->aucKc, NAS_MML_GetSimPsSecurityGsmKc(), 8);

    /* 获取 IMSI,cksn */
    pucMmlImsi = NAS_MML_GetSimImsi();
    PS_MEM_CPY(pPsInfo->aucImsi, &(pucMmlImsi[1]), 8);
    pPsInfo->ucCksn = NAS_MML_GetSimPsSecurityCksn();

    if ( GMM_UEID_P_TMSI & g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask )
    {
        pPsInfo->ucInfoMask |= MM_SECURITY_P_TMSI_MASK;

        Gmm_MemCpy(&pPsInfo->aucPTMSI[0],
                   NAS_MML_GetUeIdPtmsi(),
                   NAS_MML_MAX_PTMSI_LEN);                                         /* P_TMSI赋值                               */
    }


    return;
}

/*******************************************************************************
Module   : Gmm_GetCurrCipherInfo
Function : 获得当前的加密是否启动信息
Input    : 无
Output   : 无
NOTE     : 无
Return   : 1 : 加密启动
           0 : 加密没有启动
History  :
  1. l65478  2009.04.09  新规作成
*******************************************************************************/
VOS_UINT8 Gmm_GetCurrCipherInfo(VOS_VOID)
{
    if(VOS_TRUE == gstGmmCasGlobalCtrl.ucGprsCipher)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*****************************************************************************
 函 数 名  : GMM_GetTlliInfo
 功能描述  : 获取当前的TLLI值
 输入参数  : 无
 输出参数  : pulNewTlli
             pulOldTlli
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月30日
    作    者   : j00174725
    修改内容   : 问题单修改
*******************************************************************************/
VOS_VOID GMM_GetTlliInfo(VOS_UINT32 *pulNewTlli, VOS_UINT32 *pulOldTlli)
{
    VOS_UINT8                          *pucPtmsiAddr        = VOS_NULL_PTR;
    NAS_MML_RAI_STRU                   *pstLastSuccRai      = VOS_NULL_PTR;
    NAS_LMM_GUTI_STRU                  *pstGutiInfo         = VOS_NULL_PTR;
    GMM_RAI_STRU                        stGmmRai;
    NAS_LMM_INFO_STRU                   stLmmInfo;
    VOS_UINT8                           aucPtmsi[NAS_MML_MAX_PTMSI_LEN];
    VOS_UINT32                          ulGutiValid;
    VOS_UINT32                          ulTLLI;
    VOS_UINT32                          ulGetLteInfoRet;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;
    VOS_UINT8                           ucUeIdMask;

    /* 初始化 */
    ulTLLI = 0;
    PS_MEM_SET(aucPtmsi, 0, sizeof(aucPtmsi));

    ucUeIdMask      = NAS_GMM_GetUeIdMask();
#if (FEATURE_ON == FEATURE_LTE)
    ulGutiValid     = NAS_GMM_GetLteGutiValid();
    enTinType       = NAS_MML_GetTinType();
    ulGetLteInfoRet = NAS_GMM_GetLteInfo( NAS_LMM_GUTI, &stLmmInfo );
#else
    ulGutiValid     = VOS_FALSE;
    ulGetLteInfoRet = VOS_FALSE;
#endif

    /* 如果PTMSI有效，但是从L映射过来的，则生成Foreign TLLI */
#if (FEATURE_ON == FEATURE_LTE)
    if ( (VOS_TRUE == ulGutiValid)
      && (VOS_TRUE == ulGetLteInfoRet) )
    {
        pstGutiInfo                         = &(stLmmInfo.u.stGuti);
        aucPtmsi[0]                         = (pstGutiInfo->stMTmsi.ucMTmsi & 0x3f) | 0xc0 ;
        aucPtmsi[1]                         = pstGutiInfo->stMmeCode.ucMmeCode;
        aucPtmsi[2]                         = pstGutiInfo->stMTmsi.ucMTmsiCnt2;
        aucPtmsi[3]                         = pstGutiInfo->stMTmsi.ucMTmsiCnt3;

        if ( ( (0 == (ucUeIdMask & GMM_UEID_P_TMSI))
            && (NAS_MML_TIN_TYPE_INVALID == enTinType) )
          || (NAS_MML_TIN_TYPE_GUTI == enTinType) )
        {
            /* 待更新的TLLI值 */
            GMM_CharToUlong(&ulTLLI, aucPtmsi);
            GMM_CreateNewTlli(&ulTLLI, GMM_FOREIGN_TLLI);

            *pulNewTlli = ulTLLI;
            *pulOldTlli = gstGmmCasGlobalCtrl.ulOldTLLI;

            return;
        }
    }
#endif

    /* 如果PTMSI 无效，则生成随机TLLI */
    if (0 == (ucUeIdMask & GMM_UEID_P_TMSI))
    {
         GMM_CreateNewTlli(&ulTLLI, GMM_RANDOM_TLLI);

        *pulNewTlli = ulTLLI;
        *pulOldTlli = 0xffffffff;

        return;
    }

    /* 如果PTMSI有效且不是从L映射过来的，比较当前驻留的RAI与PS注册成功的RAI，
    相同生成local TLLI,不同生成foreign TLLI */

    /* 取得存储PTMSI数据的地址 */
    pucPtmsiAddr        = NAS_MML_GetUeIdPtmsi();
    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];
    PS_MEM_CPY(aucPtmsi, pucPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    GMM_CharToUlong(&ulTLLI, aucPtmsi);

    if (VOS_TRUE == Gmm_Compare_Rai(&stGmmRai, &g_GmmGlobalCtrl.SysInfo.Rai))
    {

        GMM_CreateNewTlli(&ulTLLI, GMM_LOCAL_TLLI);
    }
    else
    {
        GMM_CreateNewTlli(&ulTLLI, GMM_FOREIGN_TLLI);
    }

    *pulNewTlli = ulTLLI;
    *pulOldTlli = gstGmmCasGlobalCtrl.ulOldTLLI;

    return;
}


/*******************************************************************************
Module   : Gmm_ClearLlcData
Function : GMM在DETACH或关机时，需要清除LLC数据
Input    : 无
Output   : 无
NOTE     : 无
Return   : 无
History  :
  1.日    期   : 2009年05月14日
    作    者   : l65478
    修改内容   : 问题单号:AT2D06770
  2.日    期   : 2009年06月30日
    作    者   : l65478
    修改内容   : 问题单：AT2D12655,增加清除LLC数据类型的处理
*******************************************************************************/
VOS_VOID Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ENUM_UINT8 ucClearDataType)
{
    if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
    {
        Gmm_SndLlcAbortReq(ucClearDataType);
        GMM_FreeSysTlli();
        Gmm_TimerStop(GMM_TIMER_PROTECT_OLD_TLLI);
        gstGmmCasGlobalCtrl.ulOldTLLI = 0xffffffff;
    }
}

/*******************************************************************************
Module   : NAS_GMM_SuspendLlcForInterSys
Function : GMM在驻留W后，需要挂起层2，在重新驻留GSM后恢复
Input    : 无
Output   : 无
NOTE     : 无
Return   : 无
History  :
  1.日    期   : 2010年07月20日
    作    者   : s46746
    修改内容   : 问题单号:DTS2010073001405,G2W异系统重选后，不向层2发送去指派而是挂起层2
*******************************************************************************/
VOS_VOID NAS_GMM_SuspendLlcForInterSys()
{
    if ((GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
     && (GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause))
    {
        GMM_SndLlcSuspendReq();
        gstGmmCasGlobalCtrl.ucSuspendLlcCause |= GMM_SUSPEND_LLC_FOR_INTER_SYS;

        Gmm_TimerStop(GMM_TIMER_PROTECT_OLD_TLLI);
        gstGmmCasGlobalCtrl.ulOldTLLI = 0xffffffff;
    }
}

/*******************************************************************************
Module   : Gmm_ComGprsCipherHandle
Function : GMM对GPRS下加密的公共处理
Input    : 无
Output   : 无
NOTE     : 无
Return   : 无
History  :
  1.日    期   : 2009年06月26日
    作    者   : s46746
    修改内容   : 问题单号:AT2D12561
*******************************************************************************/
VOS_VOID Gmm_ComGprsCipherHandle()
{
    if (0 != gstGmmCasGlobalCtrl.ucGprsCipherAlg)
    {
        gstGmmCasGlobalCtrl.ucGprsCipher = VOS_TRUE;
    }
    else
    {
        gstGmmCasGlobalCtrl.ucGprsCipher = VOS_FALSE;
    }

    NAS_GMM_SndMmcCipherInfoInd();

    /* 指定Kc和加密算法 */
    GMM_AssignGsmKc();
}

/*****************************************************************************
 函 数 名  : NAS_GMM_UpdateAttemptCounterForSpecialCause
 功能描述  : 检测原因值是否需要更新Attemp Counter值
 输入参数  : VOS_UINT8  ucUpdateAttachCounter :
                            VOS_TRUE: Attach流程, VOS_FALSE: RAU流程
             VOS_UINT32 ulGmmCause : 原因值
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : o00132663
    修改内容   : 新生成函数

  2.日    期   : 2010年11月18日
    作    者   : zhoujun /40661
    修改内容   : 问题单DTS2010111601893,收到拒绝原因值为102-110的
                 处理应该和原因值111的处理一致

  3.日    期   : 2011年2月11日
    作    者   : w00176964
    修改内容   : DTS2012021003156:GMM注册被拒原因值为4时，处理与协议不一致，发起
                 无效attach或RAU请求
*****************************************************************************/
VOS_VOID NAS_GMM_UpdateAttemptCounterForSpecialCause(
    VOS_UINT8                           ucUpdateAttachCounter,
    VOS_UINT32                          ulGmmCause
)
{
    /* 3GPP 24.008, 4.7.3.1.5 Abnormal cases in the MS
       d)ATTACH REJECT, other causes than those treated in subclause 4.7.3.1.4
         Upon reception of the cause codes # 95, # 96, # 97, # 99 and # 111 the
         MS should set the GPRS attach attempt counter to 5.

       Gmm Combined RAU has similiar handling. */

    /*  3GPP 24.008 10.5.5.14 GMM cause
        Any other value received by the mobile station shall be treated as 0110 1111,
        "Protocol error, unspecified". Any other value received by the network shall
        be treated as 0110 1111, "Protocol error, unspecified".*/

#if (PS_UE_REL_VER >= PS_PTL_VER_R6)
    if ((NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG == ulGmmCause)
     || (NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF      == ulGmmCause)
     || (NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE == ulGmmCause)
     || (NAS_MML_REG_FAIL_CAUSE_IE_NONEXIST_NOTIMPLEMENTED == ulGmmCause)
     /* 根据24008协议，增加对GMM遗漏的原因值处理 */
     || (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR        == ulGmmCause)
     || (NAS_MML_REG_FAIL_CAUSE_CS_DOMAIN_NOT_AVAILABLE    == ulGmmCause)
     || (NAS_MML_REG_FAIL_CAUSE_ESM_FAILURE                == ulGmmCause)
     || ((ulGmmCause >= NAS_MML_REG_FAIL_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG )
      && (ulGmmCause <= NAS_MML_REG_FAIL_CAUSE_CS_DOMAIN_TEMP_NOT_AVAILABLE))
     || ((ulGmmCause > NAS_MML_REG_FAIL_CAUSE_MSG_NOT_COMPATIBLE )
      && (ulGmmCause <= NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR) ))
    {
        if ( VOS_TRUE == ucUpdateAttachCounter )
        {
            g_GmmAttachCtrl.ucAttachAttmptCnt = 4;
        }
        else
        {
            g_GmmRauCtrl.ucRauAttmptCnt = 4;
        }
    }
#endif

    if (VOS_TRUE == NAS_MML_IsRoamingRejectNoRetryFlgActived((VOS_UINT8)ulGmmCause))
    {
        g_GmmAttachCtrl.ucAttachAttmptCnt = 4;
    }


    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_CheckCauseToStartT3340
 功能描述  : 检测拒绝原因值，判断是否需要启动T3340
 输入参数  : VOS_UINT8 ucCause : 原因值
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月15日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_CheckCauseToStartT3340(
    VOS_UINT8                           ucCause
)
{
    /*3GPP 24.008
      4.7.1.9 Release of the PS signalling connection (Iu mode only)
      In Iu mode, to allow the network to release the PS signalling connection
      (see 3GPP TS 25.331 [23c] and 3GPP TS 44.118 [110]) the MS shall start
      the timer T3340 in the following cases:

      a)the MS receives any of the reject cause values #11, #12, #13 or #15;
      */

    if (GMM_FALSE == GMM_IsCasGsmMode())
    {
        if (   (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW  == ucCause)
            || (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW    == ucCause)
            || (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW  == ucCause)
            || (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL == ucCause))
        {
            Gmm_TimerStart(GMM_TIMER_T3340);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_HandleDelayedEvent
 功能描述  : 处理follow on事件或者缓存的事件
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月16日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_HandleDelayedEvent( VOS_VOID )
{
    if (GMM_TIMER_T3340_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3340_FLG))
    {
        /* T3340正在运行中，等链路释放后再处理缓存消息 */
        return;
    }

    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucRauCmpFlg)
    {
        if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

            Gmm_RoutingAreaUpdateHandleFollowOn();
        }

        if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
        {
            Gmm_DealWithBuffAfterProc();
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_AsEstReq
 功能描述  : 通知接入层发送Est_Req
 输入参数  :  ulOpId       - 操作ID
              ucCnDomain   - 域枚举
              ulEstCause   - 建链原因值
              pIdnnsInfo   - 标识
              pstPlmnId    - 当前网络号
              ulSize       - 消息大小
              pFisrstMsg   - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年2月21日
    作    者   : zhoujun /z40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_INT32 NAS_GMM_AsEstReq(
    VOS_UINT32                          ulOpId,
    VOS_UINT8                           ucCnDomain,
    VOS_UINT32                          ulEstCause,
    IDNNS_STRU                          *pIdnnsInfo,
    RRC_PLMN_ID_STRU                    *pstPlmnId,
    VOS_UINT32                          ulSize,
    VOS_INT8                            *pFisrstMsg
)
{
    /* PS域的呼叫类型统一填写为Other */
    return As_RrEstReq(ulOpId,ucCnDomain,ulEstCause,RRC_NAS_CALL_TYPE_OTHER,
                       pIdnnsInfo,pstPlmnId,ulSize,pFisrstMsg);
}

 /*****************************************************************************
 函 数 名  : NAS_GMM_GetAttemptUpdateRaiInfo
 功能描述  : 获取ATTEMPT UPDATE时的RAI信息
 输入参数  : 无
 输出参数  : VOS_VOID
 返 回 值  : NAS_MML_RAI_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月14日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
NAS_MML_RAI_STRU *NAS_GMM_GetAttemptUpdateRaiInfo(VOS_VOID)
{
    return &(g_GmmGlobalCtrl.stAttemptToUpdateRai);
}

 /*****************************************************************************
  函 数 名  : NAS_GMM_SetAttemptUpdateRaiInfo
  功能描述  : 设置ATTEMPT UPDATE时的RAI信息
  输入参数  : pstRai - rai信息
  输出参数  : 无
  返 回 值  : 无
  调用函数  :
  被调函数  :

  修改历史      :
   1.日    期   : 2015年1月14日
     作    者   : z00161729
     修改内容   : AT&T 支持DAM特性修改
 *****************************************************************************/
 VOS_VOID NAS_GMM_SetAttemptUpdateRaiInfo(
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo
 )
 {
     g_GmmGlobalCtrl.stAttemptToUpdateRai.stLai = pstCampPlmnInfo->stLai;
     g_GmmGlobalCtrl.stAttemptToUpdateRai.ucRac = pstCampPlmnInfo->ucRac;
     return;
 }

 /*****************************************************************************
 函 数 名  : NAS_GMM_IsNeedUseAttemptUpdateRaiInfo
 功能描述  : 判断是否需要使用ATTEMPT UPDATE时的RAI信息
 输入参数  : pSysinfoRai - 当前系统消息的rai信息
 输出参数  : VOS_VOID
 返 回 值  : VOS_TRUE  - 需要使用
             VOS_FALSE - 不需要使用
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月14日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedUseAttemptUpdateRaiInfo(
     GMM_RAI_STRU                       *pstSysinfoRai,
     GMM_RAI_STRU                       *pstAttemptUpdateRai
)
{
    VOS_UINT32                           ulIsSameRai;
    VOS_UINT32                           ulT3302Status;

    ulIsSameRai   = Gmm_Compare_Rai(pstSysinfoRai, pstAttemptUpdateRai);
    ulT3302Status = NAS_GMM_QryTimerStatus(GMM_TIMER_T3302);

    /* U2,GMM状态为搜网或GMM_SUSPENDED_WAIT_FOR_SYSINFO状态，且T3302定时器在运行，
      不使用上次系统消息的rai与当前系统消息的rai比较判断位置区是否改变，
      使用g_GmmGlobalCtrl.stAttemptToUpdateLai与当前系统消息的rai比较位置区是否改变,
      以防止多做rau */
    if ((NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED == NAS_MML_GetPsUpdateStatus())
     && (GMM_TRUE == ulIsSameRai)
     && (VOS_TRUE == ulT3302Status)
     && ((GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
      || (GMM_REGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
      || (GMM_DEREGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
      || (GMM_DEREGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
      || (GMM_SUSPENDED_WAIT_FOR_SYSINFO == g_GmmGlobalCtrl.ucState)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_InitRaiInfo
 功能描述  : 初始化ATTEMPT UPDATE时的RAI信息
 输入参数  : pstRai - RAI信息
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月14日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
VOS_VOID NAS_GMM_InitRaiInfo(
    NAS_MML_RAI_STRU                   *pstRai
)
{
    pstRai->stLai.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstRai->stLai.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    pstRai->stLai.aucLac[0]      = NAS_MML_LAC_LOW_BYTE_INVALID;
    pstRai->stLai.aucLac[1]      = NAS_MML_LAC_HIGH_BYTE_INVALID;
    pstRai->ucRac                = NAS_MML_RAC_INVALID;

    return;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_RetryCurrentProcedureCommonCheck
 功能描述  : 是否需要重新发起PS流程通用检查函数
 输入参数  : NAS_MM_COM_PROCEDURE_ENUM_UINT8     ucCurrentProc
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年2月4日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_GMM_RetryCurrentProcedureCommonCheck(VOS_VOID)
{
    /* 重发流程，检查是否满足以下条件:
       1. Iu 模式
       2. 当前流程与被异常释放的流程一致
       3. 当前流程是在已存在的RRC连接上发起
       4. 当前流程没有收到Security Mode Command或其他来自核心网的 NAS层消息*/

    if (   (VOS_FALSE == GMM_IsCasGsmMode())
        && (g_GmmGlobalCtrl.ucSpecProc
                == g_GmmGlobalCtrl.stGmmLinkCtrl.ucCurrentProc)
        && (VOS_TRUE == g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedRrcConn)
        && (VOS_FALSE
                == g_GmmGlobalCtrl.stGmmLinkCtrl.ucSmcOrFirstNasMsgRcvdFlg))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RetryAttachProcedureCheck
 功能描述  : 检测是否需要重新发起Attach流程
 输入参数  : RRC_REL_CAUSE_ENUM_UINT32           ulRelCause         - 释放原因值
             RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus    - 链路状态
 输出参数  : 无
 返 回 值  : VOS_TRUE : 需要重新发起流程
             VOS_FALSE: 不需要重新发起流程
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月30日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_GMM_RetryAttachProcedureCheck(
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause,
    RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus
)
{
    /*24.008, 4.7.3.1.5 Abnormal cases in the MS
      b)    Lower layer failure before the ATTACH ACCEPT or ATTACH REJECT mess-
      age is received
      The procedure shall be aborted and. Tthe MS shall proceed as described
      below, except in the following implementation option cases b.1 and
      b.2.
      b.1)  Release of PS signalling connection in Iu mode before the comple-
      tion of the GPRS attach procedure
      If the release of the PS signalling connection occurs before completion
      of the GPRS attach procedure, then the GPRS attach procedure shall
      be initiated again, if the following conditions apply:
      i)    The original GPRS attach procedure was initiated over an existing
      PS signalling connection; and
      ii)   The GPRS attach procedure was not due to timer T3310 expiry; and
      iii)  No SECURITY MODE COMMAND message and no Non-Access Startum (NAS)
      messages relating to the PS signalling connection (e.g. PS authentica-
      tion procedure, see subclause 4.7.7) were received after the ATTACH
      REQUEST message was transmitted.
      b.2)  RR release in Iu mode (i.e. RRC connection release) with, for
      example, cause "Normal", or "User inactivity" (see 3GPP TS 25.331
      [32c] and 3GPP TS 44.118 [111])
      The GPRS attach procedure shall be initiated again, if the following
      conditions apply:
      i)    The original GPRS attach procedure was initiated over an existing
      RRC connection; and
      ii)   The GPRS attach procedure was not due to timer T3310 expiry; and
      iii)  No SECURITY MODE COMMAND message and no Non-Access Stratum (NAS)
      messages relating to the PS signalling connection (e.g. PS authentica-
      tion procedure, see subclause 4.7.7) were received after the ATTACH
      REQUEST message was transmitted.
      NOTE:     The RRC connection release cause that triggers the re-initiation
      of the GPRS attach procedure is implementation specific.*/

    VOS_UINT8                               ucRst;

    ucRst = NAS_GMM_RetryCurrentProcedureCommonCheck();

    if (VOS_TRUE == ucRst)
    {
        if (0 == g_GmmAttachCtrl.ucT3310outCnt)
        {
            if (RRC_RRC_CONN_STATUS_ABSENT == ulRrcConnStatus)
            {
                /* 释放的是RRC连接 */
                if ( (RRC_REL_CAUSE_RR_NORM_EVENT    == ulRelCause)
                  || (RRC_REL_CAUSE_RR_USER_INACT    == ulRelCause)
                  || (RRC_REL_CAUSE_CELL_UPDATE_FAIL == ulRelCause)
                  || (RRC_REL_CAUSE_T315_EXPIRED     == ulRelCause) )
                {
                    return VOS_TRUE;
                }
            }
            else
            {
                /* 释放的是PS信令连接 */
                if (VOS_TRUE
                        == g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedPsSignallingConn)
                {
                    /* 该流程是在已存在的PS信令连接上发起的 */
                    return VOS_TRUE;
                }
            }
        }
    }

    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : NAS_GMM_RetryDetachProcedureCheck
 功能描述  : 检查是否需要重新发起Detach流程
 输入参数  : RRC_REL_CAUSE_ENUM_UINT32           ulRelCause         - 释放原因值
             RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus    - 链路状态
 输出参数  : 无
 返 回 值  : VOS_TRUE : 需要重新发起流程
             VOS_FALSE: 不需要重新发起流程
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月30日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_GMM_RetryDetachProcedureCheck(
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause,
    RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus
)
{
    /*24.008, 4.7.4.1.4
      b.1)  Release of PS signalling connection before the completion of
      the GPRS detach procedure
      The release of the PS signalling connection before completion of the
      GPRS detach procedure shall result in the GPRS detach procedure being
      initiated again, if the following conditions apply:
      i)    The original GPRS detach procedure was initiated over an existing
      PS signalling connection; and
      ii)   No SECURITY MODE COMMAND message and no Non-Access Stratum (NAS)
      messages relating to the PS signalling connection (e.g. PS authentica-
      tion procedure, see subclause 4.7.7) were received after the DETACH
      REQUEST message was transmitted.
      b.2)  RR release in Iu mode (i.e. RRC connection release) with cause
      different than "Directed signalling connection re-establishment",
      for example, "Normal", or"User inactivity" (see 3GPP TS 25.331 [32c]
      and 3GPP TS 44.118 [111])
      The GPRS detach procedure shall be initiated again, if the following
      conditions apply:
      i)    The original GPRS detach procedure was initiated over an exisiting
      RRC connection; and
      ii)   No SECURITY MODE COMMAND message and no Non-Access Stratum (NAS)
      messages relating to the PS signalling connection (e.g. PS authentica-
      tion procedure, see subclause 4.7.7) were received after the DETACH
      REQUEST message was transmitted.
      NOTE:     The RRC connection release cause different than "Directed sign-
      alling connection re-establishment" that triggers the re-initiation
      of the GPRS detach procedure is implementation specific.
      b.3)  RR release in Iu mode (i.e. RRC connection release) with cause
      "Directed signalling connection re-establishment" (see 3GPP TS 25.331
      [32c] and 3GPP TS 44.118 [111])
      The routing area updating procedure shall be initiated followed by
      completion of the GPRS detach procedure if the following conditions
      apply:
      i)    The original GPRS detach procedure was not due to SIM removal; and
      ii)   The original GPRS detach procedure was not due to a rerun of the
      procedure due to "Directed signalling connection reestablishment".*/


    VOS_UINT8                               ucRst;

    if (   (GMM_DETACH_COMBINED_POWER_OFF
                == g_GmmGlobalCtrl.stGmmLinkCtrl.ucCurrentProc)
        || (GMM_DETACH_NORMAL_POWER_OFF
                == g_GmmGlobalCtrl.stGmmLinkCtrl.ucCurrentProc))
    {
        return VOS_FALSE;
    }

    ucRst = NAS_GMM_RetryCurrentProcedureCommonCheck();

    if (VOS_TRUE == ucRst)
    {
        if (RRC_RRC_CONN_STATUS_ABSENT == ulRrcConnStatus)
        {
            /* 释放的是RRC连接 */
            if ( (RRC_REL_CAUSE_RR_NORM_EVENT == ulRelCause)
              || (RRC_REL_CAUSE_RR_USER_INACT == ulRelCause)
              || (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST == ulRelCause)
              || (RRC_REL_CAUSE_CELL_UPDATE_FAIL        == ulRelCause)
              || (RRC_REL_CAUSE_T315_EXPIRED            == ulRelCause) )
            {
                return VOS_TRUE;
            }
        }
        else
        {
            /* 释放的是PS信令连接 */
            if (VOS_TRUE
                    == g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedPsSignallingConn)
            {
                /* 该流程是在已存在的PS信令连接上发起的 */
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;


}


/*****************************************************************************
 函 数 名  : NAS_GMM_RetryRauProcedureCheck
 功能描述  : 检查是否需要重新发起当前被中断的RAU流程
 输入参数  : RRC_REL_CAUSE_ENUM_UINT32           ulRelCause         - 释放原因值
             RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus    - 链路状态
 输出参数  : 无
 返 回 值  : VOS_TRUE : 需要重新发起流程
             VOS_FALSE: 不需要重新发起流程
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年2月1日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_GMM_RetryRauProcedureCheck(
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause,
    RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus
)
{
    /*24.008 4.7.5.1.5
      b.1)  Release of PS signalling connection before the completion of
      the routing area updating procedure
      The routing area updating procedure shall be initiated again, if the
      following conditions apply:
      i)    The original routing area update procedure was initiated over an
      existing PS signalling connection; and
      ii)   The routing area update procedure was not due to timer T3330
      expiry; and
      iii)  No SECURITY MODE COMMAND message and no Non-Access Stratum (NAS)
      messages relating to the PS signalling connection were (e.g. PS authe-
      ntication procedure, see subclause 4.7.7) received after the ROUTING
      AREA UPDATE REQUEST message was transmitted.
      b.2)  RR release in Iu mode (i.e. RRC connection release) with, for
      example, cause "Normal", or "User inactivity" or "Direct signalling
      connection re-establishment" (see 3GPP TS 25.331 [32c] and 3GPP TS
      44.118 [111])
      The routing area updating procedure shall be initiated again, if the
      following conditions apply:
      i)    The original routing area update procedure was initiated over an
      existing RRC connection; and
      ii)   The routing area update procedure was not due to timer T3330
      expiry; and
      iii)  No SECURITY MODE COMMAND message and no Non-Access Stratum (NAS)
      messages relating to the PS signalling connection (e.g. PS authentica-
      tion procedure, see subclause 4.7.7) were received after the ROUTING
      AREA UPDATE REQUEST message was transmitted.
      NOTE:     The RRC connection release cause that triggers the re-initiation
      of the routing area update procedure is implementation specific.

      注:
      Direct signalling connection re-establishment 原因值已经特殊处理了，
      此处不再处理。*/

    VOS_UINT8                               ucRst;

    ucRst = NAS_GMM_RetryCurrentProcedureCommonCheck();

    if (VOS_TRUE == ucRst)
    {
        if (0 == g_GmmRauCtrl.ucT3330outCnt)
        {
            if (RRC_RRC_CONN_STATUS_ABSENT == ulRrcConnStatus)
            {
                /* 释放的是RRC连接 */
                if ( (RRC_REL_CAUSE_RR_NORM_EVENT       == ulRelCause)
                  || (RRC_REL_CAUSE_RR_USER_INACT       == ulRelCause)
                  || (RRC_REL_CAUSE_CELL_UPDATE_FAIL    == ulRelCause)
                  || (RRC_REL_CAUSE_T315_EXPIRED        == ulRelCause) )
                {
                    return VOS_TRUE;
                }
            }
            else
            {
                /* 释放的是PS信令连接 */
                if (VOS_TRUE
                        == g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedPsSignallingConn)
                {
                    /* 该流程是在已存在的PS信令连接上发起的 */
                    return VOS_TRUE;
                }
            }
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RetrySrProcedureCheck
 功能描述  : 检查是否需要重新发起当前被中断的Service Request流程
 输入参数  : RRC_REL_CAUSE_ENUM_UINT32           ulRelCause         - 释放原因值
             RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus    - 链路状态
 输出参数  : 无
 返 回 值  : VOS_TRUE : 需要重新发起流程
             VOS_FALSE: 不需要重新发起流程
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年2月1日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_GMM_RetrySrProcedureCheck(
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause,
    RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus
)
{
    /*24.008 4.7.13.5
      b.1)  Release of PS signalling connection in Iu mode (i.e. RRC connect-
      ion release) before the completion of the service request procedure
      The service request procedure shall be initiated again, if the follow-
      ing conditions apply:
      i)    The original service request procedure was initiated over an exist-
      ing PS signalling connection; and
      ii)   No SECURITY MODE COMMAND message and no Non-Access Stratum (NAS)
      messages relating to the PS signalling connection were received after
      the SERVICE REQUEST message was transmitted.
      b.2)  RR release in Iu mode (i.e. RRC connection release) with cause
      different than "Directed signalling connection re-establishment",
      for example, "Normal", or "User inactivity" (see 3GPP TS 25.331 [32c]
      and 3GPP TS 44.118 [111])
      The service request procedure shall be initiated again, if the follow-
      ing conditions apply:
      i)    The original service request procedure was initiated over an exist-
      ing RRC connection and,
      ii)   No SECURITY MODE COMMAND message and no Non-Access Stratum (NAS)
      messages relating to the PS signalling connection were received after
      the SERVICE REQUEST messge was transmitted.
      NOTE:     The RRC connection release cause different than "Directed sign-
      alling connection re-establishment" that triggers the re-initiation
      of the service request procedure is implementation specific.
      b.3)  RR release in Iu mode (i.e. RRC connection release) with cause
      "Directed signalling connection re-establishment" (see 3GPP TS 25.331
      [32c] and 3GPP TS 44.118 [111])
      The routing area updating procedure shall be initiated followed by
      a rerun of the service request procedure if the following condition
      applies:
      i)    The service request procedure was not due to a rerun of the proced-
      ure due to "Directed signalling connection re-establishment"*/

    VOS_UINT8                               ucRst;

    ucRst = NAS_GMM_RetryCurrentProcedureCommonCheck();

    if (VOS_TRUE == ucRst)
    {
        if (RRC_RRC_CONN_STATUS_ABSENT == ulRrcConnStatus)
        {
            /* 释放的是RRC连接 */
            if ( (RRC_REL_CAUSE_RR_NORM_EVENT           == ulRelCause)
              || (RRC_REL_CAUSE_RR_USER_INACT           == ulRelCause)
              || (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST == ulRelCause)
              || (RRC_REL_CAUSE_CELL_UPDATE_FAIL        == ulRelCause)
              || (RRC_REL_CAUSE_T315_EXPIRED            == ulRelCause) )
            {
                return VOS_TRUE;
            }
        }
        else
        {
            /* 释放的是PS信令连接 */
            if (VOS_TRUE
                    == g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedPsSignallingConn)
            {
                /* 该流程是在已存在的PS信令连接上发起的 */
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;

}


/*****************************************************************************
 函 数 名  : NAS_GMM_UpdateGmmLinkCtrlStru
 功能描述  : 更新GMM连接释放控制结构
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年2月3日
    作    者   : o00132663
    修改内容   : 新生成函数

  2.日    期   : 2011年7月14日
    作    者   : zhoujun 40661
    修改内容   : 使用MML_CTX中的链接状态
*****************************************************************************/
VOS_VOID NAS_GMM_UpdateGmmLinkCtrlStru(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU       *pstConnStatus;

    pstConnStatus   = NAS_MML_GetConnStatus();

    if (VOS_TRUE== GMM_IsCasGsmMode())
    {
        /* GSM下无链路释放增强处理 */
        return;
    }


    g_GmmGlobalCtrl.stGmmLinkCtrl.ucCurrentProc = g_GmmGlobalCtrl.ucSpecProc;
    g_GmmGlobalCtrl.stGmmLinkCtrl.ucSmcOrFirstNasMsgRcvdFlg = VOS_FALSE;

    /* 检查当前流程是否在已建立的RRC连接上发起 */
    if (VOS_FALSE == pstConnStatus->ucRrcStatusFlg)
    {
        g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedRrcConn = VOS_FALSE;
        g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedPsSignallingConn = VOS_FALSE;
    }
    else if (VOS_TRUE ==
                        (pstConnStatus->ucPsSigConnStatusFlg))
    {
        /* PS 信令链路存在 */
        g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedRrcConn = VOS_TRUE;
        g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedPsSignallingConn = VOS_TRUE;
    }
    else
    {
        /* RRC连接存在，但PS 信令链路不存在 */
        g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedRrcConn = VOS_TRUE;
        g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedPsSignallingConn = VOS_FALSE;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_ClearGmmLinkCtrlStru
 功能描述  : 清除GMM链路控制变量
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年2月9日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_ClearGmmLinkCtrlStru( VOS_VOID )
{
    g_GmmGlobalCtrl.stGmmLinkCtrl.ucCurrentProc = GMM_NULL_PROCEDURE;
    g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedPsSignallingConn = GMM_NULL_PROCEDURE;
    g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedRrcConn = VOS_FALSE;
    g_GmmGlobalCtrl.stGmmLinkCtrl.ucSmcOrFirstNasMsgRcvdFlg = VOS_FALSE;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_GetDetachTypeFromProcName
 功能描述  : 根据当前流程名获得Detach类型
 输入参数  : NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8            ucSpecProc  - 流程名
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年2月4日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_GMM_GetDetachTypeFromProcName(
    NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8   ucSpecProc
)
{
    VOS_UINT8                           ucDetachType;

    switch (ucSpecProc)
    {
        case GMM_DETACH_COMBINED:
            if (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
            {
                ucDetachType = MMC_GMM_PS_CS_DETACH;
            }
            else
            {
                ucDetachType = MMC_GMM_PS_DETACH;
            }
            break;

        case GMM_DETACH_NORMAL:
        case GMM_DETACH_NORMAL_NETMODE_CHANGE:
            ucDetachType = MMC_GMM_PS_DETACH;
            break;

        case GMM_DETACH_WITH_IMSI:
            ucDetachType = MMC_GMM_CS_DETACH;
            break;

        default:
            ucDetachType = GMM_INVALID_DETACH_TYPE;
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                "NAS_GMM_GetDetachTypeFromCurrProc: Procedure is not detach related.");
    }

    return ucDetachType;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_SndStatusMsg
 功能描述  : 给网络回复STATUS消息
 输入参数  : VOS_UINT8 ulCause - 原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月23日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_SndStatusMsg(
    VOS_UINT8                           ucCause
)
{
    NAS_MSG_STRU        *pGmmStatus;

    pGmmStatus = Gmm_GmmStatusMsgMake(ucCause);

    if (VOS_NULL_PTR != pGmmStatus)
    {
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_ClearBufferedSmDataReq
 功能描述  : 清除缓存的SM DATA REQ
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月13日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_ClearBufferedSmDataReq( VOS_VOID )
{
    if (GMM_MSG_HOLD_FOR_SM ==
        (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvMmcGmmDetachReqMsg_GmmServiceReqInitiated(): Clear cached SM Data Req");

        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;
    }


    /* 没有短信时,清除follow on标志 */
    if (GMM_FALSE == g_GmmServiceCtrl.ucSmsFlg)
    {
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
    }

    if ((0x0 == g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
     && (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg))
    {
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);
    }



    return;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_CheckGmmInfoMsg
 功能描述  : 检查Gmm Information消息
 输入参数  : pMsg - Gmm Information 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32 - 消息检查结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月23日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_GMM_CheckGmmInfoMsg(
    NAS_MSG_FOR_PCLINT_STRU             *pMsg
)
{
    if (pMsg->ulNasMsgSize < GMM_MSG_LEN_GMM_INFORMATION)
    {
        /* 消息的长度非法 */
        NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_RcvGmmInformationMsg:WARNING: The length of GMM INFORMATION is invalid");
        NAS_GMM_SndStatusMsg(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        return VOS_ERR;
    }

    if (GMM_NOT_SUPPORT_INFORMATION_MSG == g_GmmGlobalCtrl.UeInfo.ucSupportInfoFlg)
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_RcvGmmInformationMsg:WARNING: GMM INFORMATION is unsupported");
        NAS_GMM_SndStatusMsg(NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE);

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_DecodeFullNameforNetworkIE
 功能描述  : 解码消息中的Full Name for Network IE
 输入参数  : NAS_MSG_FOR_PCLINT_STRU *pMsg - 消息指针
             VOS_UINT32 *pulIeOffset       - 当前处理指针的位置
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月23日
    作    者   : o00132663
    修改内容   : 新生成函数

  2.日    期   : 2013年01月09日
    作    者   : l65478
    修改内容   : DTS2013010809507网络名称上报错误

*****************************************************************************/
VOS_UINT32 NAS_GMM_DecodeFullNameforNetworkIE(
    NAS_MSG_FOR_PCLINT_STRU             *pMsg,
    VOS_UINT32                          *pulIeOffset
)
{
    VOS_UINT32                          ulIePos;
    NAS_MML_OPERATOR_NAME_INFO_STRU    *pstCurrOperatorName = VOS_NULL_PTR;

    pstCurrOperatorName = NAS_MML_GetOperatorNameInfo();
    ulIePos             = *pulIeOffset;

    /* 消息中只包含Tag */
    if ( pMsg->ulNasMsgSize < (ulIePos + 2) )
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeFullNameforNetworkIE:WARNING: FULL NAME for NETWORK is error in GMM INFORMATION");
        return VOS_ERR;
    }

    /* 该IE len为0 */
    if ( 0 == pMsg->aucNasMsg[ulIePos + 1] )
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeFullNameforNetworkIE:WARNING: GMM INFORMATION is semantically incorrect");
        NAS_GMM_SndStatusMsg(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

        return VOS_ERR;
    }

    PS_MEM_SET(pstCurrOperatorName->aucOperatorNameLong, 0, NAS_MML_MAX_OPER_LONG_NAME_LEN);
    if (NAS_MML_MAX_OPER_LONG_NAME_LEN >= (pMsg->aucNasMsg[ulIePos + 1] + 1))
    {
        PS_MEM_CPY(pstCurrOperatorName->aucOperatorNameLong, (VOS_UINT8 *)&(pMsg->aucNasMsg[ulIePos + 1]), pMsg->aucNasMsg[ulIePos + 1] + 1);
    }
    else
    {
        PS_MEM_CPY(pstCurrOperatorName->aucOperatorNameLong, (VOS_UINT8 *)&(pMsg->aucNasMsg[ulIePos + 1]), NAS_MML_MAX_OPER_LONG_NAME_LEN);
    }

    *pulIeOffset += pMsg->aucNasMsg[ulIePos + 1] + 2;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_DecodeShortNameforNetworkIE
 功能描述  : 解码消息中的Short Name for Network IE
 输入参数  : NAS_MSG_FOR_PCLINT_STRU *pMsg - 消息指针
             VOS_UINT32 *pulIeOffset       - 当前处理指针的位置
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月23日
    作    者   : o00132663
    修改内容   : 新生成函数

  2.日    期   : 2013年01月09日
    作    者   : l65478
    修改内容   : DTS2013010809507网络名称上报错误

*****************************************************************************/
VOS_UINT32  NAS_GMM_DecodeShortNameforNetworkIE(
    NAS_MSG_FOR_PCLINT_STRU             *pMsg,
    VOS_UINT32                          *pulIeOffset
)
{
    VOS_UINT32                          ulIePos;

    NAS_MML_OPERATOR_NAME_INFO_STRU    *pstCurrOperatorName = VOS_NULL_PTR;

    pstCurrOperatorName = NAS_MML_GetOperatorNameInfo();
    ulIePos             = *pulIeOffset;

    /* 消息中只包含Tag */
    if ((VOS_UINT8)(pMsg->ulNasMsgSize) < (ulIePos + 2))
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeShortNameforNetworkIE:WARNING: SHORT NAME for NETWORK is error in GMM INFORMATION");
        return VOS_ERR;
    }

    if (0 == pMsg->aucNasMsg[ulIePos + 1])
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeShortNameforNetworkIE:WARNING: GMM INFORMATION is semantically incorrect.");
        NAS_GMM_SndStatusMsg(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

        return VOS_ERR;
    }

    PS_MEM_SET(pstCurrOperatorName->aucOperatorNameShort, 0, NAS_MML_MAX_OPER_SHORT_NAME_LEN);
    if (NAS_MML_MAX_OPER_SHORT_NAME_LEN >= (pMsg->aucNasMsg[ulIePos + 1] + 1))
    {
        PS_MEM_CPY(pstCurrOperatorName->aucOperatorNameShort, (VOS_UINT8 *)&(pMsg->aucNasMsg[ulIePos + 1]), pMsg->aucNasMsg[ulIePos + 1] + 1);
    }
    else
    {
        PS_MEM_CPY(pstCurrOperatorName->aucOperatorNameShort, (VOS_UINT8 *)&(pMsg->aucNasMsg[ulIePos + 1]), NAS_MML_MAX_OPER_SHORT_NAME_LEN);
    }

    *pulIeOffset += pMsg->aucNasMsg[ulIePos + 1] + 2;

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_DecodeLocalTimeZoneIE
 功能描述  : 解码消息中的Local Time Zone IE
 输入参数  : NAS_MSG_FOR_PCLINT_STRU *pMsg - 消息指针
             VOS_UINT32 *pulIeOffset       - 当前处理指针的位置
             pstMmInfo                     - 保存解析好的IE值
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月23日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_GMM_DecodeLocalTimeZoneIE(
    NAS_MSG_FOR_PCLINT_STRU             *pMsg,
    VOS_UINT32                          *pulIeOffset,
    NAS_MM_INFO_IND_STRU                *pstMmInfo
)
{
    VOS_UINT32      ulIePos;
    VOS_INT8        cTimeZone;
    VOS_UINT8       ucDigit;

    ulIePos = *pulIeOffset;

    /* 消息长度不够 */
    if ((VOS_UINT8)(pMsg->ulNasMsgSize) < (ulIePos + 2))
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeLocalTimeZoneIE:WARNING: IE Len incorrect.");
        NAS_GMM_SndStatusMsg(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

        return VOS_ERR;
    }

    ucDigit = ((pMsg->aucNasMsg[ulIePos + 1]) & 0xF0) >> 4;
    if ( ucDigit > 9 )
    {
        /*值非法 */
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeLocalTimeZoneIE:WARNING: Time Zone value incorrect.");
        NAS_GMM_SndStatusMsg(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

        return VOS_ERR;
    }

    cTimeZone = (VOS_INT8)((((pMsg->aucNasMsg[ulIePos + 1]) & 0x07) * 10) + ucDigit);

    /* 判断时区的正负值 */
    if ((pMsg->aucNasMsg[ulIePos + 1]) & 0x08)
    {
        pstMmInfo->cLocalTimeZone = - cTimeZone;
    }
    else
    {
        pstMmInfo->cLocalTimeZone = cTimeZone;
    }

    pstMmInfo->ucIeFlg |= NAS_MM_INFO_IE_LTZ;

    *pulIeOffset += 2;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_DecodeUniversalTimeAndLocalTimeZoneIE
 功能描述  : 解码消息中的Universal Time and Local Time Zone IE
 输入参数  : NAS_MSG_FOR_PCLINT_STRU *pMsg - 消息指针
             VOS_UINT32 *pulIeOffset       - 当前处理指针的位置
             pstMmInfo                     - 保存解析好的IE值
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月23日
    作    者   : o00132663
    修改内容   : 新生成函数

  2.日    期   : 2010年7月1日
    作    者   : 欧阳飞
    修改内容   : DTS2010062801177,增加对IE的有效性检查

  3.日    期   : 2010年7月20日
    作    者   : 欧阳飞
    修改内容   : DTS2010072001259，当IE检查失败时，忽略该消息，但不再给网络
                 回复GMM STATUS消息
*****************************************************************************/
VOS_UINT32  NAS_GMM_DecodeUniversalTimeAndLocalTimeZoneIE(
    NAS_MSG_FOR_PCLINT_STRU             *pMsg,
    VOS_UINT32                          *pulIeOffset,
    NAS_MM_INFO_IND_STRU                *pstMmInfo
)
{
    VOS_UINT32      ulIePos;
    VOS_INT8        cTimeZone;
    VOS_UINT8       ucDigit;

    ulIePos = *pulIeOffset;

    /* 消息长度不够 */
    if ((VOS_UINT8)(pMsg->ulNasMsgSize) < (ulIePos + 8))
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeUniversalTimeAndLocalTimeZoneIE:WARNING: GMM INFORMATION is semantically incorrect.");
        NAS_GMM_SndStatusMsg(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

        return VOS_ERR;
    }

    /* 第一个字节为 Year */
    pstMmInfo->stUniversalTimeandLocalTimeZone.ucYear = (((pMsg->aucNasMsg[ulIePos + 1]) & 0x0f) * 10)
                                                     +(((pMsg->aucNasMsg[ulIePos + 1]) & 0xf0) >> 4);
    if (pstMmInfo->stUniversalTimeandLocalTimeZone.ucYear > 99)
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeUniversalTimeAndLocalTimeZoneIE:WARNING: Invalid Year Value.");
        return VOS_ERR;
    }


    /* 第二个字节为 Month */
    pstMmInfo->stUniversalTimeandLocalTimeZone.ucMonth = (((pMsg->aucNasMsg[ulIePos + 2]) & 0x0f) * 10)
                                                     +(((pMsg->aucNasMsg[ulIePos + 2]) & 0xf0) >> 4);
    if (  (pstMmInfo->stUniversalTimeandLocalTimeZone.ucMonth > 12)
        ||(0 == pstMmInfo->stUniversalTimeandLocalTimeZone.ucMonth) )
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeUniversalTimeAndLocalTimeZoneIE:WARNING: Invalid Month Value.");
        return VOS_ERR;
    }

    /* 第三个字节为 Day */
    pstMmInfo->stUniversalTimeandLocalTimeZone.ucDay = (((pMsg->aucNasMsg[ulIePos + 3]) & 0x0f) * 10)
                                                     +(((pMsg->aucNasMsg[ulIePos + 3]) & 0xf0) >> 4);
    if (  (pstMmInfo->stUniversalTimeandLocalTimeZone.ucDay > 31)
        || (0 == pstMmInfo->stUniversalTimeandLocalTimeZone.ucDay) )
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeUniversalTimeAndLocalTimeZoneIE:WARNING: Invalid Day Value.");
        return VOS_ERR;
    }

    /* 第四个字节为 Hour */
    pstMmInfo->stUniversalTimeandLocalTimeZone.ucHour = (((pMsg->aucNasMsg[ulIePos + 4]) & 0x0f) * 10)
                                                     +(((pMsg->aucNasMsg[ulIePos + 4]) & 0xf0) >> 4);
    if (pstMmInfo->stUniversalTimeandLocalTimeZone.ucHour >= 24)
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeUniversalTimeAndLocalTimeZoneIE:WARNING: Invalid Hour Value.");
        return VOS_ERR;
    }

    /* 第五个字节为 Minute */
    pstMmInfo->stUniversalTimeandLocalTimeZone.ucMinute = (((pMsg->aucNasMsg[ulIePos + 5]) & 0x0f) * 10)
                                                     +(((pMsg->aucNasMsg[ulIePos + 5]) & 0xf0) >> 4);
    if (pstMmInfo->stUniversalTimeandLocalTimeZone.ucMinute >= 60)
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeUniversalTimeAndLocalTimeZoneIE:WARNING: Invalid Minute Value.");
        return VOS_ERR;
    }

    /* 第六个字节为 Second */
    pstMmInfo->stUniversalTimeandLocalTimeZone.ucSecond = (((pMsg->aucNasMsg[ulIePos + 6]) & 0x0f) * 10)
                                                     +(((pMsg->aucNasMsg[ulIePos + 6]) & 0xf0) >> 4);
    if (pstMmInfo->stUniversalTimeandLocalTimeZone.ucSecond >= 60)
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeUniversalTimeAndLocalTimeZoneIE:WARNING: Invalid Second Value.");
        return VOS_ERR;
    }

    /* 第七个字节为 TimeZone */
    ucDigit = ((pMsg->aucNasMsg[ulIePos + 7]) & 0xF0) >> 4;
    if (ucDigit > 9)
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeUniversalTimeAndLocalTimeZoneIE:WARNING: Invalid Time Zone Value.");
        return VOS_ERR;
    }
    cTimeZone = (VOS_INT8)((((pMsg->aucNasMsg[ulIePos + 7]) & 0x07) * 10) + ucDigit );

    /* 判断时区的正负值 */
    if ((pMsg->aucNasMsg[ulIePos + 7]) & 0x08)
    {
        pstMmInfo->stUniversalTimeandLocalTimeZone.cTimeZone = - cTimeZone;
    }
    else
    {
        pstMmInfo->stUniversalTimeandLocalTimeZone.cTimeZone = cTimeZone;
    }

    pstMmInfo->ucIeFlg |= NAS_MM_INFO_IE_UTLTZ;

    *pulIeOffset += 8;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_DecodeLSAIdentityIE
 功能描述  : 解码消息中的LSA IDENTITY IE
 输入参数  : NAS_MSG_FOR_PCLINT_STRU *pMsg - 消息指针
             VOS_UINT32 *pulIeOffset       - 当前处理指针的位置
             pstMmInfo                     - 保存解析好的IE值
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月23日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_GMM_DecodeLSAIdentityIE(
    NAS_MSG_FOR_PCLINT_STRU             *pMsg,
    VOS_UINT32                          *pulIeOffset,
    NAS_MM_INFO_IND_STRU                *pstMmInfo
)
{
    VOS_UINT32      ulIePos;

    ulIePos = *pulIeOffset;

    /* 消息长度不够 */
    if ((VOS_UINT8)(pMsg->ulNasMsgSize) < (ulIePos + 2))
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeLSAIdentityIE:WARNING: GMM INFORMATION is semantically incorrect.");
        NAS_GMM_SndStatusMsg(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

        return VOS_ERR;
    }

    pstMmInfo->ucIeFlg |= NAS_MM_INFO_IE_LSA;

    /* IE 长度非法 */
    if (3 < pMsg->aucNasMsg[ulIePos + 1])
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeLSAIdentityIE:WARNING: GMM INFORMATION is semantically incorrect.");
        NAS_GMM_SndStatusMsg(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

        return VOS_ERR;
    }

    /* 目前LSA ID 信息未使用, 不解码 */


    *pulIeOffset += pMsg->aucNasMsg[ulIePos + 1] + 2;

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_DecodeDaylightSavingTimeIE
 功能描述  : 解码消息中的Daylight Saving Time IE
 输入参数  : NAS_MSG_FOR_PCLINT_STRU *pMsg - 消息指针
             VOS_UINT32 *pulIeOffset       - 当前处理指针的位置
             pstMmInfo                     - 保存解析好的IE值
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月23日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_GMM_DecodeDaylightSavingTimeIE(
    NAS_MSG_FOR_PCLINT_STRU             *pMsg,
    VOS_UINT32                          *pulIeOffset,
    NAS_MM_INFO_IND_STRU                *pstMmInfo
)
{
    VOS_UINT32      ulIePos;

    ulIePos = *pulIeOffset;

    /* 消息长度不够 */
    if ((VOS_UINT8)(pMsg->ulNasMsgSize) < (ulIePos + 3))
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeDaylightSavingTimeIE:WARNING: GMM INFORMATION is semantically incorrect.");
        NAS_GMM_SndStatusMsg(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

        return VOS_ERR;
    }

    /* IE 有效性检查失败 */
    if ((1 != pMsg->aucNasMsg[ulIePos + 1]) || (pMsg->aucNasMsg[ulIePos + 2] > 3))
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeDaylightSavingTimeIE:WARNING: GMM INFORMATION is semantically incorrect.");
        NAS_GMM_SndStatusMsg(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

        return VOS_ERR;
    }

    pstMmInfo->ucIeFlg |= NAS_MM_INFO_IE_DST;
    pstMmInfo->ucDST = pMsg->aucNasMsg[ulIePos + 2];

    *pulIeOffset += 3;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsNeedStartT3340RegSuccNoFollowOnProceed
 功能描述  : attach accept或rau accept不带follow on proceed判断是否需要启动t3340定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要启动T3340
             VOS_FALSE - 不需要启动T3340
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月17日
    作    者   : z00161729
    修改内容   : DTS2015071505434:rau或attach请求不带follow on，网络回复attach accept或rau accept中携带follow on proceed标识，gmm需要
                 增加判断如果ps rab存在或存在rabm重建或sm业务请求或cds存在缓存数据则不启动T3340，否则启动t3340开启网络防呆功能

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedStartT3340RegSuccNoFollowOnProceed(VOS_VOID)
{
    VOS_UINT32                          ulIsPsRabExistFlag;
    VOS_UINT8                           ucPdpExistNotStartT3340Flag;
    VOS_UINT32                          ulUsimMMApiIsTestCard;

    ulUsimMMApiIsTestCard       = NAS_USIMMAPI_IsTestCard();
    ulIsPsRabExistFlag          = NAS_RABM_IsPsRbExist();
    ucPdpExistNotStartT3340Flag = NAS_MML_GetPdpExistNotStartT3340Flag();

    /* 24008 R12 Table 11.3/3GPP TS 24.008描述如下:
     T3340定时器启动条件: ATTACH ACCEPT or ROUTING AREA UPDATE ACCEPT is
     received with "no follow-on proceed" indication and user plane
     radio access bearers have not been setup. */
    if (VOS_TRUE == ulIsPsRabExistFlag)
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == ulUsimMMApiIsTestCard)
    {
        return VOS_TRUE;
    }

    if ((VOS_TRUE == NAS_MML_IsPsBearerExist())
     && (VOS_TRUE == ucPdpExistNotStartT3340Flag))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsNeedStartT3340RegSuccWithFollowOnProceed
 功能描述  : attach accept或rau accept带follow on proceed判断是否需要启动t3340定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要启动T3340
             VOS_FALSE - 不需要启动T3340
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月17日
    作    者   : z00161729
    修改内容   : DTS2015071505434:rau或attach请求不带follow on，网络回复attach accept或rau accept中携带follow on proceed标识，gmm需要
                 增加判断如果ps rab存在或存在rabm重建或sm业务请求或cds存在缓存数据则不启动T3340，否则启动t3340开启网络防呆功能

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedStartT3340RegSuccWithFollowOnProceed(VOS_VOID)
{
    VOS_UINT32                          ulDataAvailFlg;
    VOS_UINT32                          ulIsPsRabExistFlag;

    ulIsPsRabExistFlag          = NAS_RABM_IsPsRbExist();

    if (VOS_FALSE == NAS_GMM_IsEnableRelPsSigCon())
    {
        return VOS_FALSE;
    }

    /* 24008 R12 4.7.13章节描述如下:
       If the network indicates "follow-on proceed" and the MS has no service
       request pending, then no specific action is required from the MS.
       As an implementation option, the MS may start timer T3340 as described
       in subclause 4.7.1.9 if no user plane radio access bearers are set up.
       RAU request消息未携带follow on,满足以下条件，则启动T3340:
       1、当前没有数据在进行
       2、且没有缓存的rabm重建请求
       3、没有缓存的sm业务请求
       4、不存在ps的rab
       5、2309 nv开启且不是测试卡 */
    ulDataAvailFlg     = CDS_IsPsDataAvail();

    if ((VOS_TRUE != NAS_GMM_IsFollowOnPend())
     && (PS_TRUE  != ulDataAvailFlg)
     && (VOS_TRUE != ulIsPsRabExistFlag)
     && (GMM_MSG_HOLD_FOR_SERVICE != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
     && (GMM_MSG_HOLD_FOR_SM != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_CheckIfNeedToStartTimerT3340
 功能描述  : 在收到RAU ACCEPT后，检查是否需要启动T3340定时器，监控RRC链路的
             释放
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月7日
    作    者   : o00132663
    修改内容   : 新生成函数
  2.日    期   : 2012年3月7日
    作    者   : z00161729
    修改内容   : V7R1 C50 支持ISR修改
  3.日    期   : 2014年10月23日
    作    者   : z00161729
    修改内容   : DTS2014102403468:rau accept网络没有带follow on proceed，需要启动T3340，T3340运行期间后续收到网络pdp modify请求或去激活请求需要正常回复
  4.日    期 : 2015-4-1
    作    者 : wx270776
	修改内容 : DTS2015032608956: 如果为测试卡，则启动3340定时器
  5.日    期   : 2015年7月14日
    作    者   : z00161729
    修改内容   : DTS2015071505434:rau或attach请求不带follow on，网络回复attach accept或rau accept中携带follow on proceed标识，gmm需要
                增加判断如果ps rab存在或存在rabm重建或sm业务请求或cds存在缓存数据则不启动T3340，否则启动t3340开启网络防呆功能
*****************************************************************************/
VOS_VOID  NAS_GMM_CheckIfNeedToStartTimerT3340(VOS_VOID)
{
    VOS_INT8                            cVersion;
    VOS_UINT32                          ulT3340TimerStatus;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;


    cVersion = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS);

#if (PS_UE_REL_VER >= PS_PTL_VER_R6)
    if (cVersion >= PS_PTL_VER_R6)
    {
        /* R7引入了T3340定时器，但在R6网络中也如此实现也是合理的。 */
        if (   (GMM_FALSE == GMM_IsCasGsmMode())
            && (GMM_FALSE == g_GmmGlobalCtrl.ucFopFlg))
        {
            if (VOS_TRUE == NAS_GMM_IsNeedStartT3340RegSuccNoFollowOnProceed())
            {
                Gmm_TimerStart(GMM_TIMER_T3340);
            }
        }

        /* 网络防呆处理 */
        ulT3340TimerStatus = NAS_GMM_QryTimerStatus(GMM_TIMER_T3340);
        enRatType          = NAS_MML_GetCurrNetRatType();

        if ((NAS_MML_NET_RAT_TYPE_WCDMA == enRatType)
         && (VOS_FALSE                  == ulT3340TimerStatus)
         && (GMM_TRUE == g_GmmGlobalCtrl.ucFopFlg))
        {
            if (VOS_TRUE == NAS_GMM_IsNeedStartT3340RegSuccWithFollowOnProceed())
            {
                /* 使用网络防呆功能配置的T3340的定时器时长 */
                g_GmmTimerMng.aTimerInf[GMM_TIMER_T3340].ulTimerVal = NAS_GMM_GetRelPsSigConCfg_T3340TimerLen();
                Gmm_TimerStart(GMM_TIMER_T3340);

                /* 恢复T3340的协议标准时长 */
                g_GmmTimerMng.aTimerInf[GMM_TIMER_T3340].ulTimerVal = GMM_TIMER_T3340_VALUE;
            }

        }
    }
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsNeedProcDelayPsSmsConnRelTimer
 功能描述  : 判断是否需要启动定时器 GMM_TIMER_DELAY_PS_SMS_CONN_REL
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要
             VOS_FALSE - 不需要
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月23日
    作    者   : c00318887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedProcDelayPsSmsConnRelTimer(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    /* 取得当前的链接信息 */
    pstConnStatus = NAS_MML_GetConnStatus();

    /* 网络防呆没开启或者是测试卡 */
    if (VOS_FALSE == NAS_GMM_IsEnableRelPsSigCon())
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_IsNeedProcDelayPsSmsConnRelTimer:IsEnableRelPsSigCon is false");
        return VOS_FALSE;
    }

    /* T3340在运行，则等T3340超时释放连接 */
    if (VOS_TRUE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3340))
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_IsNeedProcDelayPsSmsConnRelTimer:T3340 is runing");
        return VOS_FALSE;
    }
    
    /* 当前不在W下，不需要REL */
    if (NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_IsNeedProcDelayPsSmsConnRelTimer:rat isnot WCDMA");
        return VOS_FALSE;
    }
    
    /* sm在进行pdp激活、去激活、modify流程，返回false，不需要主动释放连接 */
    if (NAS_MML_SM_PROC_FLAG_START == NAS_MML_GetSmProcFlag())
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_IsNeedProcDelayPsSmsConnRelTimer:SmProcFlag is start");
        return VOS_FALSE;
    }

    /* pdp已经激活，返回false，不需要主动释放连接 */
    if (VOS_TRUE == NAS_MML_GetPdpConnStateInfo())
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_IsNeedProcDelayPsSmsConnRelTimer:PdpConnState is ture");
        return VOS_FALSE;
    }

    /* 当有GMM 流程时，不需要主动释放连接 */
    if (GMM_NULL_PROCEDURE != g_GmmGlobalCtrl.ucSpecProc)
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_IsNeedProcDelayPsSmsConnRelTimer:g_GmmGlobalCtrl.ucSpecProc != GMM_NULL_PROCEDURE");
        return VOS_FALSE;
    }

    /* 存在PS链路 */
    if ( (VOS_TRUE == pstConnStatus->ucRrcStatusFlg)
      && (VOS_TRUE == pstConnStatus->ucPsSigConnStatusFlg) )
    {
        return VOS_TRUE;
    }

    NAS_WARNING_LOG2(WUEPS_PID_GMM, "NAS_GMM_IsNeedProcDelayPsSmsConnRelTimer:RrcStatus and PsSigConnStatus are", 
                        pstConnStatus->ucRrcStatusFlg, pstConnStatus->ucPsSigConnStatusFlg);
    
    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_TransferSmEstCause2RrcEstCause
 功能描述  : 将SM的建链请求原因值转换为RRC建链原因值
 输入参数  : VOS_UINT32     ulSmEstCause    - SM的建链请求原因值
 输出参数  : VOS_UINT32     *pulRrcEstCause - RRC建链原因值指针
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月19日
    作    者   : 欧阳飞
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_TransferSmEstCause2RrcEstCause(
    VOS_UINT32                          ulSmEstCause,
    VOS_UINT32                          *pulRrcEstCause
)
{
    VOS_UINT32  ulRrcEstCause;

    switch (ulSmEstCause)
    {
        case GMM_SM_RRC_EST_CAUSE_ORG_CONV_CALL:
            ulRrcEstCause = RRC_EST_CAUSE_ORIGIN_CONVERSAT_CALL;
            break;
        case GMM_SM_RRC_EST_CAUSE_ORG_STM_CALL:
            ulRrcEstCause = RRC_EST_CAUSE_ORIGIN_STREAM_CALL;
            break;
        case GMM_SM_RRC_EST_CAUSE_ORG_INTER_CALL:
            ulRrcEstCause = RRC_EST_CAUSE_ORIGIN_INTERACT_CALL;
            break;
        case GMM_SM_RRC_EST_CAUSE_ORG_BG_CALL:
            ulRrcEstCause = RRC_EST_CAUSE_ORIGIN_BACKGROUND_CALL;
            break;
        case GMM_SM_RRC_EST_CAUSE_ORG_ST_CALL:
            ulRrcEstCause = RRC_EST_CAUSE_ORIGIN_SUBSCRIB_TRAFFIC_CALL;
            break;
        default:
            NAS_INFO_LOG1(WUEPS_PID_GMM, "NAS_GMM_TransferSmEstCause2RrcEstCause: Rcv SmEstCause:", ulSmEstCause);
            ulRrcEstCause = RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL;
            break;
    }

    *pulRrcEstCause = ulRrcEstCause;

    return;
}

/*******************************************************************************
Module   : NAS_GMM_FreeTlliForPowerOff
Function : 在关机状态时，释放TLLI，清除L2的数据，并恢复L2
Input    : 无
Output   : 无
NOTE     : 无
Return   : 无
History  :
  1.日    期   : 2010年09月13日
    作    者   : l65478
    修改内容   : 新生成函数
*******************************************************************************/
VOS_VOID NAS_GMM_FreeTlliForPowerOff(VOS_VOID)
{
    if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
    {
        Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_ALL);
        if (GMM_NOT_SUSPEND_LLC != gstGmmCasGlobalCtrl.ucSuspendLlcCause)
        {
            GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_ALL);                               /* 恢复LLC数据传输 */
            gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_NOT_SUSPEND_LLC;
        }
        GMM_FreeSysTlli();
        Gmm_TimerStop(GMM_TIMER_PROTECT_OLD_TLLI);
        gstGmmCasGlobalCtrl.ulOldTLLI = 0xffffffff;
    }
}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsFollowOnPend
 功能描述  : 在RAU、Attach消息中是否需要带Follow on条件判断
 输出参数  : 无
 返 回 值  : VOS_BOOL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年12月16日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2013年7月25日
    作    者   : w00242748
    修改内容   : DTS2013072200933:vodafone r8网络csfb mt到w，cs ps链接释放后1.5s内重选回l，
                 网络后续2s左右会重新下发paging消息，存在丢寻呼被叫打不通，参考标杆实现，
                 rau req中带follow on标志,无明确协议依据
  3.日    期   : 2013年7月25日
    作    者   : w00242748
    修改内容   : DTS2014053105098:CSFB mo是否需要带follow on增加NV控制
*****************************************************************************/
VOS_BOOL NAS_GMM_IsFollowOnPend(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                                               ucIsRauNeedFollowOnCsfbMtFlg;
    VOS_UINT8                                               ucDelayedCsfbLauFlg;
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  ucCsfbServiceStatus;
    VOS_UINT8                                               ucIsRauNeedFollowOnCsfbMoFlg;
#endif

    if (NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        return VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    ucIsRauNeedFollowOnCsfbMtFlg = NAS_MML_GetIsRauNeedFollowOnCsfbMtFlg();
    ucCsfbServiceStatus          = NAS_MML_GetCsfbServiceStatus();
    ucDelayedCsfbLauFlg          = NAS_MML_GetDelayedCsfbLauFlg();
    ucIsRauNeedFollowOnCsfbMoFlg = NAS_MML_GetIsRauNeedFollowOnCsfbMoFlg();

    /* 参照标杆实现，并无明确协议规定 */
    if ((VOS_TRUE == ucIsRauNeedFollowOnCsfbMtFlg)
     && (NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST == ucCsfbServiceStatus)
     && (VOS_FALSE == ucDelayedCsfbLauFlg))
    {
        return VOS_TRUE;
    }

    if ( (VOS_TRUE == NAS_MML_IsCsfbMoServiceStatusExist())
      && (VOS_TRUE == ucIsRauNeedFollowOnCsfbMoFlg) )
    {
        return VOS_TRUE;
    }

#endif

    if (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg)
    {
        return VOS_FALSE;
    }

    if (GMM_NULL_PROCEDURE != g_GmmGlobalCtrl.ucSpecProcHold)
    {
        return VOS_TRUE;
    }

    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
    {
        return VOS_TRUE;
    }

    if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
    {
        return VOS_TRUE;
    }

    if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_HandleModeANOIWhenRAInotChange
 功能描述  : GMM接收到系统消息，当前为A+I模式时RAI没有改变的处理
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年12月20日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2011年04月08日
    作    者   : o00132663
    修改内容   : DTS2011040803612，手动搜网，RAU拒绝原因为#9,#10时，特定场景
                 下在Attach结束前就给用户回复失败
  3.日    期   : 2013年7月4日
    作    者   : w00167002
    修改内容   : DSVLTE_bbit:DTS2013070302959:w下，II,在46002上注册成功,用户指定搜24005上，I,PS/CS注册失败
                 原因为建链失败(7)=>
                 1.收到系统消息后，PS注册状态迁移到了5(因为GMM给MMC上报了注册成功)；
                    -->GMM通知MMC注册状态失败，CAUSE401;
                 2. MMC发起了搜网(因为在ON PLMN状态，GMM给MMC上报401原因，给MM上报
                 原因410，MM给MMC通知410后，触发了搜网)；
                    -->MM收到GMM当前被拒原因410时候，转换给401原因通知MMC;
                 3.搜网成功后，在原小区收到系统消息后，MMC重复发起搜网(GMM通知MM当前
                   PS当前注册成功，CS原因16，导致MM给MMC上报16原因值，触发循环搜网)。
                   -->GMM在ATTEMPT TO UPDATE状态，通知MM被拒原因410；
                 4. 通知MM PS only成功的原因值由16修改为401。sunxibo一起走读，收到
                    系统消息时候，原因值不用填写为16，否则MM通知MMC16，ATTMPT尝试次数
                    为4次，会触发搜网。
  4.日    期   : 2014年04月08日
    作    者   : s00217060
    修改内容   : DTS2014040901544:PS域注册被拒#111,网络带的T3302定时器时长为0，链接释放再收到系统消息时，UE一直发起ATTACH

*****************************************************************************/
VOS_VOID NAS_GMM_HandleModeANOIWhenRAInotChange()
{
    VOS_UINT8 ucState;

    ucState = g_GmmGlobalCtrl.ucState;
    if (GMM_REGISTERED_PLMN_SEARCH == ucState)
    {
        ucState = g_GmmGlobalCtrl.ucPlmnSrchPreSta;
    }

    if ((VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
     && (GMM_REGISTERED_NORMAL_SERVICE == ucState))
    {
        Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;
        NAS_GMM_SndMmCombinedRauInitiation();
        NAS_GMM_SndMmCombinedRauAccept(GMMMM_RAU_RESULT_COMBINED,
                                       NAS_MML_REG_FAIL_CAUSE_NULL,
                                       VOS_NULL_PTR,
                                       VOS_NULL_PTR);


        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);

        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
    }
    else
    {
        /* 搜网过程中T3311、T3302超时时没有进行RAU */
        /* 网络带下来的T3302定时器时长为0时，不启T3302定时器，如果不加最后一个判断，UE会一直发起ATTACH */
        if ((GMM_TIMER_T3302_FLG
            != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
        && ((GMM_TIMER_T3311_FLG
            != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG)))
        && (0 != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal))
        {                                                                       /* Timer3302在运行中                        */
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
        }
        else
        {
            /* GMM迁到IDLE态，等T3311或T3302超时后再发起RAU */
            if (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == ucState)
            {

                g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

                NAS_GMM_SndMmCombinedRauInitiation();
                NAS_GMM_SndMmCombinedRauAccept(GMMMM_RAU_RESULT_PS_ONLY,
                                               NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE,
                                               VOS_NULL_PTR,
                                               VOS_NULL_PTR);


                /* 向MMC发送PS注册结果 */
                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                             GMM_MMC_ACTION_RESULT_SUCCESS,
                                             NAS_MML_REG_FAIL_CAUSE_NULL);

                g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

                Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM);
            }
            else
            {

                g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

                /* 向MMC发送PS注册结果 */
                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                             GMM_MMC_ACTION_RESULT_FAILURE,
                                             NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);


                NAS_GMM_SndMmCombinedRauInitiation();
                NAS_GMM_SndMmCombinedRauRejected(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES);

                g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

                Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE);
            }

        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_HandleModeANOIWhenDeregister
 功能描述  : GMM接收到系统消息，当前为A+I模式未注册时 的处理
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年12月20日
    作    者   : 12
    修改内容   : 新生成函数
  2.日    期   : 2011年11月8日
    作    者   : s46746
    修改内容   : V7R1 PhaseII阶段解决关机慢问题
  3.日    期   : 2012年9月25日
    作    者   : h00216089
    修改内容   : DTS2012090304976:调整，网侧Detach(re-attach not required)后，MM定时器超时发起LU，
                  LU结束后收到系统消息GMM不会再发起Attach
  4.日    期   : 2014年04月08日
    作    者   : s00217060
    修改内容   : DTS2014040901544:PS域注册被拒#111,网络带的T3302定时器时长为0，链接释放再收到系统消息时，UE一直发起ATTACH
*****************************************************************************/
VOS_VOID NAS_GMM_HandleModeANOIWhenDeregister()
{
    VOS_UINT8                           ucAttachCnt;

    if ((GMM_FALSE == gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg)
    && (VOS_TRUE == g_GmmGlobalCtrl.ucRcvNetDetachFlg))
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                     /* 调用状态的公共处理*/
        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
        return;
    }

    if ((GMM_FALSE == gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg)
    && (GMM_FALSE == gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg)
    && ((GMM_DEREGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
     || (GMM_DEREGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)))
    {
        /* 网络带下来的T3302定时器时长为0时，不启T3302定时器，如果不加最后一个判断，UE会一直发起ATTACH */
        if ((GMM_TIMER_T3302_FLG
            != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
        && ((GMM_TIMER_T3311_FLG
            != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG)))
        && (0 != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal))
        {
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        }
        else
        {
            if (GMM_TIMER_T3302_FLG
                == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
            {
                ucAttachCnt = g_GmmAttachCtrl.ucAttachAttmptCnt;
                g_GmmAttachCtrl.ucAttachAttmptCnt = 5;
                g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

                /* 向MMC发送PS注册结果,当PS注册失败，假流程需要给MMC上报原因值为OTHER CAUSE */
                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                             GMM_MMC_ACTION_RESULT_FAILURE,
                                             NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

                g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
                g_GmmAttachCtrl.ucAttachAttmptCnt = ucAttachCnt;
            }

            Gmm_ComStaChg(GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH);
        }
    }
    else
    {
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);

        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;

        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_BackToOrgPlmnAfterCoverageLost
 功能描述  : 从出服务区回到原来的PLMN的处理
 输入参数  : VOS_VOID                           *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月9日
    作    者   : l65478
    修改内容   : 新生成函数

  2.日    期   : 2011年11月19日
    作    者   : zhoujun 40661
    修改内容   : DTS2011111700165,网络模式I下,GMM回到原小区,未能通知MM进入正常服务
  3.日    期   : 2012年1月18日
    作    者   : s46746
    修改内容   : 问题单号：DTS2012011601544,网络模式I 联合注册仅PS成功,紧急呼叫后CS指示正常服务
  4.日    期   : 2012年02月23日
    作    者   : l65478
    修改内容   : DTS2012021306419,BVT测试，RAI没有改变时，发起了RAU
 5. 日    期   : 2012年3月28日
    作    者   : l65478
    修改内容   : 问题单号：DTS2012032002585:从W->L->W时，回到W后没有发起RAU
 6. 日    期   : 2012年7月17日
    作    者   : z00161729
    修改内容   : DTS2012071606177:W(LAI1)-L(TAI2/LAI2 ISR激活CS LAI改变)-W(LAI1网络模式I)需要
                  发起联合rau
  7.日    期   : 2013年9月29日
    作    者   : w00242748
    修改内容   : DTS2013092302598:手动搜网，L下成功驻留，CSFB到W下，位置区变化，LAU/RAU建联失败(5次)，
                 搜网回原小区，继续进行联合RAU失败，MM单独LAU失败，死循环，MM ATTEMPT COUNTER无限增加
*****************************************************************************/
VOS_UINT32 NAS_GMM_BackToOrgPlmnAfterCoverageLost(
    VOS_VOID                           *pMsg
)
{
    GMM_RAI_STRU                       *pRaiTemp = VOS_NULL_PTR;
    VOS_UINT8                           ucRaiChgFlg;
    VOS_UINT8                           ucLaiChgFlg;
    NAS_MML_RAI_STRU                   *pstLastSuccRai;
    GMM_RAI_STRU                        stGmmRai;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;
#endif

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

    pRaiTemp = (GMM_RAI_STRU *)Gmm_MemMalloc(sizeof(GMM_RAI_STRU));
    if (VOS_NULL_PTR == pRaiTemp)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
            "Gmm_RcvMmcSysInfoInd_RegUpdtNeed:ERROR: Alloc mem fail.");
        return VOS_FALSE;
    }
    Gmm_RcvMmcSysInfoInd_Fill_pRaiTemp(pRaiTemp, pMsg);

    Gmm_Get_Location_Change_info(pRaiTemp, &stGmmRai, &ucLaiChgFlg, &ucRaiChgFlg, g_GmmGlobalCtrl.ucNetMod);

    Gmm_MemFree(pRaiTemp);

    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
     && (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
    {
        return VOS_FALSE;
    }
    /* 进入GMM LIMITED只有下面几种情况:
       1. 拒绝原因值#13
       2. 拒绝原因值#11
       3. 当前小区不支持GPRS
       4. 当前网络禁止注册
       在前两种情况更新状态不在U1,
       在后两种情况下如果原来是U1,并且RAI不改变的时,不需要发起RAU */
#if (FEATURE_ON == FEATURE_LTE)
    enTinType = NAS_MML_GetTinType();
    if ((NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == NAS_MML_GetPsUpdateStatus())
     && (GMM_FALSE == ucRaiChgFlg)
     && (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
     && (NAS_MML_TIN_TYPE_PTMSI == enTinType))
#else
    if ((NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == NAS_MML_GetPsUpdateStatus())
     && (GMM_FALSE == ucRaiChgFlg)
     && (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG)))
#endif
    {
        Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);


        if ( ( VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {
            NAS_GMM_NotifyMmUnrealCombinedRauResult();
        }

        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;


        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_DeleteEPlmnList
 功能描述  : 清除EPLMN列表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
*****************************************************************************/
VOS_VOID NAS_GMM_DeleteEPlmnList()
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEPlmnList    = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmnId = VOS_NULL_PTR;

    pstEPlmnList = NAS_MML_GetEquPlmnList();


    NAS_MML_InitEquPlmnInfo(pstEPlmnList);

    /* 清除NV中保存的EPLMN */
    NAS_GMM_WriteEplmnNvim(pstEPlmnList);

    /*将当前网络添加Eplmn列表*/
    pstCurrPlmnId = NAS_MML_GetCurrCampPlmnId();

    pstEPlmnList->astEquPlmnAddr[0].ulMcc = pstCurrPlmnId->ulMcc;
    pstEPlmnList->astEquPlmnAddr[0].ulMnc = pstCurrPlmnId->ulMnc;

    pstEPlmnList->ucEquPlmnNum = 1;


    return;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_DecodeEquPlmnInfoIE
 功能描述  : 解码消息中的EQUIVALENT PLMN IE
 输入参数  : GMM_MMC_ACTION_TYPE_ENUM_U32        enActionType,
              GMM_MSG_RESOLVE_STRU               *pstAcceptIe,
              NAS_MSG_FOR_PCLINT_STRU            *pstNasMsg,
 输出参数  : NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2015年6月5日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改

*****************************************************************************/
VOS_VOID NAS_GMM_DecodeEquPlmnInfoIE(
    GMM_MMC_ACTION_TYPE_ENUM_U32        enActionType,
    GMM_MSG_RESOLVE_STRU               *pstAcceptIe,
    NAS_MSG_FOR_PCLINT_STRU            *pstNasMsg,
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
)
{
    VOS_UINT8                          *pucEPlmnlist    = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstPlmnId       = VOS_NULL_PTR;

    /* 先添加当前驻留的plmn信息到EPlmn列表中 */
    pstPlmnId    = NAS_MML_GetCurrCampPlmnId();
    pstEquPlmnInfo->astEquPlmnAddr[0].ulMcc = pstPlmnId->ulMcc;
    pstEquPlmnInfo->astEquPlmnAddr[0].ulMnc = pstPlmnId->ulMnc;
    pstEquPlmnInfo->ucEquPlmnNum = 1;

    /* 取得网侧返回的EPlmn信息，且网侧返回的最大的EPlmn的个数为15个 */
    if ( (VOS_NULL_PTR != pstAcceptIe)
      && (VOS_NULL_PTR != pstNasMsg) )
    {
        if ((GMM_MMC_ACTION_RAU == enActionType)
         && (GMM_RAU_ACCEPT_IE_EQUIVALENT_PLMN_FLG
             == (pstAcceptIe->ulOptionalIeMask
                 & GMM_RAU_ACCEPT_IE_EQUIVALENT_PLMN_FLG)))
        {
            pucEPlmnlist = &pstNasMsg->aucNasMsg[pstAcceptIe->
                              aucIeOffset[GMM_RAU_ACCEPT_IE_EQUIVALENT_PLMN]];

            /* 填写PLMN列表返回GMM_TRUE */
            if (GMM_TRUE == Gmm_Com_DealOfPlmnList(pucEPlmnlist,
                              (MMCGMM_PLMN_ID_STRU*)&pstEquPlmnInfo->astEquPlmnAddr[1]))
            {
                /* 等效PLMN个数 */
                pstEquPlmnInfo->ucEquPlmnNum += *((VOS_UINT8 *)pucEPlmnlist + 1) / 3;
            }
        }
        else if ((GMM_MMC_ACTION_ATTACH == enActionType)
              && (GMM_ATTACH_ACCEPT_IE_EQUIVALENT_PLMN_FLG
                  == (pstAcceptIe->ulOptionalIeMask
                    & GMM_ATTACH_ACCEPT_IE_EQUIVALENT_PLMN_FLG)))
        {
            pucEPlmnlist = &pstNasMsg->aucNasMsg[pstAcceptIe->
                              aucIeOffset[GMM_ATTACH_ACCEPT_IE_EQUIVALENT_PLMN]];

            /* 填写PLMN列表返回GMM_TRUE */
            if (GMM_TRUE == Gmm_Com_DealOfPlmnList(pucEPlmnlist,
                              (MMCGMM_PLMN_ID_STRU*)&pstEquPlmnInfo->astEquPlmnAddr[1]))
            {
                /* 等效PLMN个数 */
                pstEquPlmnInfo->ucEquPlmnNum += *((VOS_UINT8 *)pucEPlmnlist + 1) / 3;
            }
        }
        else
        {
        }


        /* 从EPLMN列表中删除无效 、禁止和不允许漫游的网络 */
        pstEquPlmnInfo->ucEquPlmnNum = (VOS_UINT8)NAS_MML_DelInvalidPlmnFromList(
                                          (VOS_UINT32)pstEquPlmnInfo->ucEquPlmnNum,
                                          pstEquPlmnInfo->astEquPlmnAddr);
        pstEquPlmnInfo->ucEquPlmnNum = (VOS_UINT8)NAS_MML_DelForbPlmnInList(
                                          (VOS_UINT32)pstEquPlmnInfo->ucEquPlmnNum,
                                      pstEquPlmnInfo->astEquPlmnAddr);

        return;
    }

    NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeEquPlmnInfoIE:parameter is null pointer");

    return;
}



/*****************************************************************************
 函 数 名  : NAS_GMM_WriteRplmnWithRatNvim
 功能描述  : 写NV: en_NV_Item_RPlmnWithRat
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_GMM_WriteRplmnWithRatNvim(
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo
)
{
    NAS_NVIM_RPLMN_WITH_RAT_STRU        stRplmn;

    stRplmn.ucLastRplmnRat          = pstRplmnCfgInfo->enLastRplmnRat;
    stRplmn.stGRplmn.ulMcc          = pstRplmnCfgInfo->stGRplmnInNV.ulMcc;
    stRplmn.stGRplmn.ulMnc          = pstRplmnCfgInfo->stGRplmnInNV.ulMnc;
    stRplmn.stWRplmn.ulMcc          = pstRplmnCfgInfo->stWRplmnInNV.ulMcc;
    stRplmn.stWRplmn.ulMnc          = pstRplmnCfgInfo->stWRplmnInNV.ulMnc;
    stRplmn.ucLastRplmnRatEnableFlg = pstRplmnCfgInfo->ucLastRplmnRatFlg;

    if (NV_OK != NV_Write(en_NV_Item_RPlmnWithRat, &stRplmn, sizeof(NAS_NVIM_RPLMN_WITH_RAT_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_GMM_WriteRplmnWithRatNvim(): en_NV_Item_RPlmnWithRat Error");
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_UpdateGURegRlstRPlmnIdInNV
 功能描述  : 注册成功后,判断Rplmn信息是否发生了改变搜
 输入参数  : pstRPlmnId
 输出参数  : 无
 返 回 值  : VOS_TRUE:rplmn改变
             VOS_FALSE:rplmn未改变
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月08日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsGURplmnChanged(
    NAS_MML_PLMN_ID_STRU               *pstRPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat
)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulGRplmnCompareRslt;
    VOS_UINT32                          ulWRplmnCompareRslt;

    /* 默认RPlmn比较结果未发生改变 */
    ulGRplmnCompareRslt = VOS_TRUE;
    ulWRplmnCompareRslt = VOS_TRUE;

    /* 用于获取RPLMN的定制需求信息 */
    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    /* 判断全局变量中的LastRPLMN的接入技术是否发生改变 */
    if (enCurrRat != NAS_MML_GetLastRplmnRat())
    {
        /* RPlmn信息发生了改变，返回VOS_TRUE */
        return VOS_TRUE;
    }

    /* 判断全局变量中的双RPLMN是否支持 */
    if (VOS_FALSE == pstRplmnCfgInfo->ucMultiRATRplmnFlg)
    {
        ulGRplmnCompareRslt = NAS_MML_CompareBcchPlmnwithSimPlmn(pstRPlmnId,
                                                 &pstRplmnCfgInfo->stGRplmnInNV);

        ulWRplmnCompareRslt = NAS_MML_CompareBcchPlmnwithSimPlmn(pstRPlmnId,
                                                 &pstRplmnCfgInfo->stWRplmnInNV);
    }
    else
    {
        /* 支持双RPLMN, 则只判断对应接入技术的RPLMN */
        if (NAS_MML_NET_RAT_TYPE_GSM == enCurrRat)
        {
            ulGRplmnCompareRslt = NAS_MML_CompareBcchPlmnwithSimPlmn(pstRPlmnId,
                                                     &pstRplmnCfgInfo->stGRplmnInNV);
        }
        else if (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRat)
        {
            ulWRplmnCompareRslt = NAS_MML_CompareBcchPlmnwithSimPlmn(pstRPlmnId,
                                                     &pstRplmnCfgInfo->stWRplmnInNV);
        }
        else
        {
            ;
        }
    }

    /* RPlmn比较结果，VOS_FALSE表示发生了改变 */
    if ((VOS_FALSE == ulGRplmnCompareRslt)
     || (VOS_FALSE == ulWRplmnCompareRslt))
    {
        /* RPlmn信息发生了改变，返回VOS_TRUE */
        return VOS_TRUE;
    }

    /* RPlmn信息未发生改变，返回VOS_FALSE */
    return VOS_FALSE;

}


/*****************************************************************************
 函 数 名  : NAS_GMM_ConvertMmlPlmnIdToNvimEquPlmn
 功能描述  : 将MML格式的PlmnID转换为Nvim的Eplmn
              23002f(MML的格式 Mcc:0x000302,Mnc:0x0f0200)-->2,3,0,0,2,f
 输入参数  : pstPlmnId: MML的PLMN ID
 输出参数  : pstNvimPlmnId: NvimEPlmn格式
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2012年03月15日
   作    者   : l00130025
   修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
*****************************************************************************/
VOS_VOID NAS_GMM_ConvertMmlPlmnIdToNvimEquPlmn(
    NAS_MML_PLMN_ID_STRU               *pstMmlPlmnId,
    NVIM_PLMN_VALUE_STRU               *pstNvimPlmnId
)
{
    /* 转化MCC */
    pstNvimPlmnId->ucMcc[0] = (VOS_UINT8)(pstMmlPlmnId->ulMcc & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMcc[1] = (VOS_UINT8)((pstMmlPlmnId->ulMcc >> 8) & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMcc[2] = (VOS_UINT8)((pstMmlPlmnId->ulMcc >> 16) & NAS_MML_OCTET_LOW_FOUR_BITS);

    /* 转化MNC */
    pstNvimPlmnId->ucMnc[0] = (VOS_UINT8)(pstMmlPlmnId->ulMnc & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMnc[1] = (VOS_UINT8)((pstMmlPlmnId->ulMnc >> 8) & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMnc[2] = (VOS_UINT8)((pstMmlPlmnId->ulMnc >> 16) & NAS_MML_OCTET_LOW_FOUR_BITS);

}

/*****************************************************************************
 函 数 名  : NAS_GMM_ConvertMmlEquListToNvimEquPlmnList
 功能描述  : 将MML格式的Eplmn列表转换为Nvim的Eplmn列表
 输入参数  : pstMmlEPlmnList: MML的EplmnList
 输出参数  : pstNvimEPlmnList:Nvim格式的EPlmnList
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2012年03月15日
   作    者   : l00130025
   修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
*****************************************************************************/
VOS_VOID NAS_GMM_ConvertMmlEquListToNvimEquPlmnList(
    NAS_MML_EQUPLMN_INFO_STRU          *pstMmlEPlmnList,
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNvimEPlmnList
)
{
    VOS_UINT8                           i;

    pstNvimEPlmnList->ucCount = pstMmlEPlmnList->ucEquPlmnNum;

    if (pstNvimEPlmnList->ucCount > NVIM_MAX_EPLMN_NUM)
    {
        pstNvimEPlmnList->ucCount = NVIM_MAX_EPLMN_NUM;
    }

    for (i = 0; i < pstNvimEPlmnList->ucCount; i++)
    {
        NAS_GMM_ConvertMmlPlmnIdToNvimEquPlmn(&(pstMmlEPlmnList->astEquPlmnAddr[i]),
                                              &(pstNvimEPlmnList->struPlmnList[i]));

    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsInNvEplmnList
 功能描述  : 判断PLMN ID是否在NV中的EPLMN LIST列表中
 输入参数  : pstPlmnId:需要判断的PLMN ID
             ucPlmnNum:PLMN ID个数
             pstPlmnIdList:PLMN ID列表
 输出参数  : 无
 返 回 值  : VOS_TRUE  : PLMN ID在NV中的EPLMN LIST列表中
             VOS_FALSE : PLMN ID不在NV中的EPLMN LIST列表中
 调用函数  :
 被调函数  :
 修改历史      :
    1.日    期   : 2012年03月15日
      作    者   : l00130025
      修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsInNvEplmnList(
    NVIM_PLMN_VALUE_STRU               *pstPlmnId,
    VOS_UINT8                           ucPlmnNum,
    NVIM_PLMN_VALUE_STRU               *pstPlmnIdList
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < ucPlmnNum ; i++ )
    {
        if ( (pstPlmnId->ucMcc[0] == pstPlmnIdList[i].ucMcc[0])
          && (pstPlmnId->ucMcc[1] == pstPlmnIdList[i].ucMcc[1])
          && (pstPlmnId->ucMcc[2] == pstPlmnIdList[i].ucMcc[2])
          && (pstPlmnId->ucMnc[0] == pstPlmnIdList[i].ucMnc[0])
          && (pstPlmnId->ucMnc[1] == pstPlmnIdList[i].ucMnc[1])
          && (pstPlmnId->ucMnc[2] == pstPlmnIdList[i].ucMnc[2]) )
        {
            return VOS_TRUE;
        }
    }
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsNvimEPlmnListEqual
 功能描述  : 判断2个NVIM_EQUIVALENT_PLMN_LIST_STRU是否相同
 输入参数  : pstNvimEPlmnList1,pstNvimEPlmnList2待比较的2个NvimPlmnList
 输出参数  : 无
 返 回 值  : VOS_TRUE  : 2个EplmnList相同
              VOS_FALSE : 2个EplmnList不同
 调用函数  :
 被调函数  :
 修改历史      :
    1.日    期   : 2012年03月15日
      作    者   : l00130025
      修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNvimEPlmnListEqual(
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNvimEPlmnList1,
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNvimEPlmnList2
)
{
    VOS_UINT32                          i;

    if (pstNvimEPlmnList1->ucCount != pstNvimEPlmnList2->ucCount)
    {
        return VOS_FALSE;
    }

    /* Eplmn个数大于0,但Rplmn不同时，EplmnList不相同 */
    if (pstNvimEPlmnList1->ucCount > 0)
    {
        if (VOS_FALSE == NAS_GMM_IsInNvEplmnList(&(pstNvimEPlmnList1->struPlmnList[0]),
                                                 1,
                                                 pstNvimEPlmnList2->struPlmnList))
        {
            return VOS_FALSE;
        }
    }
    else
    {
        return VOS_TRUE;
    }

    /* 其它Eplmn没有进行排序且有重复数据，需要对比2个列表才能确定相同 */
    for ( i = 1 ; i < pstNvimEPlmnList1->ucCount ; i++ )
    {
        if (VOS_FALSE == NAS_GMM_IsInNvEplmnList(&(pstNvimEPlmnList1->struPlmnList[i]),
                                                 pstNvimEPlmnList2->ucCount,
                                                 pstNvimEPlmnList2->struPlmnList))
        {
            return VOS_FALSE;
        }
    }

    for ( i = 1 ; i < pstNvimEPlmnList2->ucCount ; i++ )
    {
        if (VOS_FALSE == NAS_GMM_IsInNvEplmnList(&(pstNvimEPlmnList2->struPlmnList[i]),
                                                 pstNvimEPlmnList1->ucCount,
                                                 pstNvimEPlmnList1->struPlmnList))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_WriteEplmnNvim
 功能描述  : 将Eplmn更新到NV中
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年10月08日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_GMM_WriteEplmnNvim(
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnAddr
)
{
    VOS_UINT32                          ulUpdateNvFlag;
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNewNvEquPlmnList = VOS_NULL_PTR;
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstOldNvEquPlmnList = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    ulUpdateNvFlag  = VOS_FALSE;
    ulLength        = 0;

    pstNewNvEquPlmnList = (NVIM_EQUIVALENT_PLMN_LIST_STRU*)PS_MEM_ALLOC(
                                                      WUEPS_PID_GMM,
                                                      sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU));

    if (VOS_NULL_PTR == pstNewNvEquPlmnList)
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_WriteEplmnNvim:ERROR: Memory Alloc Error");
        return;
    }

    pstOldNvEquPlmnList = (NVIM_EQUIVALENT_PLMN_LIST_STRU*)PS_MEM_ALLOC(
                                                        WUEPS_PID_GMM,
                                                        sizeof (NVIM_EQUIVALENT_PLMN_LIST_STRU));

    if (VOS_NULL_PTR == pstOldNvEquPlmnList)
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_WriteEplmnNvim:ERROR: Memory Alloc Error");
        PS_MEM_FREE(WUEPS_PID_GMM, pstNewNvEquPlmnList);
        return;
    }

    PS_MEM_SET(pstNewNvEquPlmnList, 0, sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU));
    PS_MEM_SET(pstOldNvEquPlmnList, 0, sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU));

    NAS_GMM_ConvertMmlEquListToNvimEquPlmnList(pstEplmnAddr,
                                               pstNewNvEquPlmnList);

    (VOS_VOID)NV_GetLength(en_NV_Item_EquivalentPlmn, &ulLength);

    /* 读取NV中EPLMN信息 */
    if ( NV_OK == NV_Read(en_NV_Item_EquivalentPlmn,
                         pstOldNvEquPlmnList, ulLength) )
    {
        if (VOS_FALSE == NAS_GMM_IsNvimEPlmnListEqual(pstNewNvEquPlmnList,
                                                      pstOldNvEquPlmnList))
        {
            ulUpdateNvFlag = VOS_TRUE;
        }
    }
    else
    {
        ulUpdateNvFlag = VOS_TRUE;
    }

    if ( VOS_TRUE == ulUpdateNvFlag )
    {
        if (NV_OK != NV_Write(en_NV_Item_EquivalentPlmn,
                              pstNewNvEquPlmnList,
                              sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU)))
        {
            NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_WriteEplmnNvim:WARNING: en_NV_Item_EquivalentPlmn Error");
        }
    }

    PS_MEM_FREE(WUEPS_PID_GMM, pstNewNvEquPlmnList);
    PS_MEM_FREE(WUEPS_PID_GMM, pstOldNvEquPlmnList);



}


/*****************************************************************************
 函 数 名  : NAS_GMM_NotifyMmUnrealCombinedRauResult
 功能描述  : 当PS为正常服务时,通知MM模块联合注册结果
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年10月08日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_NotifyMmUnrealCombinedRauResult()
{
    NAS_GMM_SndMmCombinedRauInitiation();

    if (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
    {
        NAS_GMM_SndMmCombinedRauAccept(GMMMM_RAU_RESULT_PS_ONLY,
                                       NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE,
                                       VOS_NULL_PTR,
                                       VOS_NULL_PTR);                              /* 发送MMCGMM_COMBINED_RAU_ACCEPTED给MMC    */

    }
    else
    {
        NAS_GMM_SndMmCombinedRauAccept(GMMMM_RAU_RESULT_COMBINED,
                                       NAS_MML_REG_FAIL_CAUSE_NULL,
                                       VOS_NULL_PTR,
                                       VOS_NULL_PTR);                              /* 发送MMCGMM_COMBINED_RAU_ACCEPTED给MMC    */
    }

    return;
}

#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_GMM_IsT3412ExpiredNeedRegist
 功能描述  : T3412超时网络模式I是否需要联合RAU
 输入参数  : enLteCsServiceCfg - UE支持的cs 业务能力
             enTinType         - TIN类型
             enT3412Status     - T3412定时器状态
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要发起注册
             VOS_FALSE - 不需要发起注册
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月5日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsT3412ExpiredNeedRegist(
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg,
    NAS_MML_TIN_TYPE_ENUM_UINT8                             enTinType,
    NAS_MML_TIMER_INFO_ENUM_UINT8                           enT3412Status
)
{
     /* 3GPP 24.008中4.7.5.2.1 Combined routing area updating procedure initiation章节描述如下：
        when the MS is configured to use CS fallback and SMS over SGs,
        or SMS over SGs only, the TIN indicates "RAT-related TMSI" and the
        periodic tracking area update timer T3412 expires;
    */
    if ((NAS_MML_TIMER_EXP == enT3412Status)
     && ((NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == enLteCsServiceCfg)
      || (NAS_MML_LTE_SUPPORT_SMS_OVER_SGS_ONLY == enLteCsServiceCfg))
     && (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsT3423StatusChangeNeedRegist
 功能描述  : T3423在运行时或超时网络模式I是否需要联合RAU
 输入参数  : enLteCsServiceCfg - UE支持的cs 业务能力
             enTinType         - TIN类型
             enT3423Status     - T3423定时器状态
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要发起注册
             VOS_FALSE - 不需要发起注册
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月5日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsT3423StatusChangeNeedRegist(
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg,
    NAS_MML_TIN_TYPE_ENUM_UINT8                             enTinType,
    NAS_MML_TIMER_INFO_ENUM_UINT8                           enT3423Status
)
{
     /*
        3GPP 24.008中4.7.5.2.1 Combined routing area updating procedure initiation章节描述如下：
        when the MS which is configured to use CS fallback and SMS over SGs,
        or SMS over SGs only, enters a GERAN or UTRAN cell, the TIN indicates
        "RAT-related TMSI", and the E-UTRAN deactivate ISR timer T3423 is running.

        when the MS which is configured to use CS fallback and SMS over SGs,
        or SMS over SGs only, enters a GERAN or UTRAN cell and the E-UTRAN deactivate
        ISR timer T3423 has expired.
    */
    if (((NAS_MML_TIMER_START == enT3423Status)
      || (NAS_MML_TIMER_EXP == enT3423Status))
     && ((NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == enLteCsServiceCfg)
      || (NAS_MML_LTE_SUPPORT_SMS_OVER_SGS_ONLY == enLteCsServiceCfg))
     && (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType))
    {
        /* GMM当前满足发起RAU条件 */
        if (VOS_TRUE == NAS_GMM_IsAbleCombinedRau_TimerStatusChg())
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_WriteTinInfoNvim
 功能描述  : 更新TIN INFO的内容到NVIM
 输入参数  : enTinType - TIN类型
             pucImsi   - IMSI
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年1月8日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2013年5月17日
   作    者   : l00167671
   修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID  NAS_GMM_WriteTinInfoNvim(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType,
    VOS_UINT8                          *pucImsi
)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;

    /* Modified by l00167671 for NV拆分项目 , 2013-05-17, begin */
    NAS_NVIM_TIN_INFO_STRU              stTinInfo;
    /* Modified by l00167671 for NV拆分项目 , 2013-05-17, end*/

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    /*
        The following EMM parameter shall be stored in a non-volatile memory in the
        ME together with the IMSI from the USIM:
        -   TIN.
        This EMM parameter can only be used if the IMSI from the USIM matches the
        IMSI stored in the non-volatile memory of the ME; else the UE shall delete
        the EMM parameter.
    */

    if (pstRplmnCfgInfo->enTinType != enTinType)
    {
        /* 先更新MML的参数 */
        pstRplmnCfgInfo->enTinType  = enTinType;
        PS_MEM_CPY(pstRplmnCfgInfo->aucLastImsi, pucImsi, sizeof(pstRplmnCfgInfo->aucLastImsi));

        /* 再更新NVIM中的参数 */
        stTinInfo.ucTinType        = pstRplmnCfgInfo->enTinType;
        PS_MEM_CPY(stTinInfo.aucImsi, pstRplmnCfgInfo->aucLastImsi, sizeof(stTinInfo.aucImsi));
        PS_MEM_SET(stTinInfo.aucReserve, 0, sizeof(stTinInfo.aucReserve));

        /* 保存在NVIM中 */
        if (NV_OK != NV_Write (en_NV_Item_TIN_INFO,
                               &stTinInfo,
                               sizeof(stTinInfo)))
        {
            NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_WriteTinInfoNvim:Write NV Failed");
        }

        /* 可维可测增加消息打印 */
        NAS_GMM_LogTinTypeInfo(enTinType);
    }
    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsNeedDeactiveIsr_InterSys
 功能描述  : L到GU异系统变换时判断是否存在ISR激活后激活的ps承载，如果有需要去激活ISR
 输入参数  : ucPreRat        - 挂起前接入技术
             enCurrNetType   - 当前接入技术
             enSuspendCause  - 挂起原因，如果是搜网到gu的，填MMC_SUSPEND_CAUSE_BUTT
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要去激活ISR
             VOS_FALSE - 不需要去激活ISR
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月15日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2015年6月5日
   作    者   : z00161729
   修改内容   : 24008 23122 R11 CR升级项目修改

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedDeactiveIsr_InterSys(
    VOS_UINT8                           ucPreRat,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetType,
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause
)
{
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    enTinType = NAS_MML_GetTinType();

    /* 未发生异系统直接返回不需去激活ISR */
    if (ucPreRat == enCurrNetType)
    {
        return VOS_FALSE;
    }

    /* 如果不是L到GU的异系统变换或者不是L下出服务区，搜网到GU，或者ISR未激活，则直接返回VOS_FALSE,不需要去激活ISR */
    if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI != enTinType)
     || (NAS_MML_NET_RAT_TYPE_LTE != ucPreRat))
    {
        return VOS_FALSE;
    }

    /* 3GPP 24301 6.1.5 Coordination between ESM and EMM for supporting ISR描述:
      This subclause applies to a UE with its TIN set as "RAT related TMSI" for which ISR is activated.
      The UE shall change its TIN to "GUTI" to deactivate ISR:
    -  at the time when the UE changes from S1 mode to A/Gb mode or Iu mode,
       if any EPS bearer context activated after the ISR was activated in the UE exists;*/
    if (VOS_TRUE == NAS_MML_IsPsBearerAfterIsrActExist())
    {
        return VOS_TRUE;
    }

    /* 24008_CR2116R3_(Rel-11)_C1-122223 24008 4.7.5.1章节描述如下:
    - in A/Gb mode, after intersystem change from S1 mode via cell change order
    procedure not due to CS fallback, if the TIN indicates "RAT-related TMSI";
    in this case the MS shall set the TIN to "GUTI" before initiating
    the routing area updating procedure.*/
    if ((VOS_FALSE == NAS_MML_IsCsfbServiceStatusExist())
     && (MMC_SUSPEND_CAUSE_CELLCHANGE == enSuspendCause)
     && (NAS_MML_NET_RAT_TYPE_GSM == enCurrNetType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_LogTinTypeInfo
 功能描述  : GMM 更新TIN类型时需要把消息勾出到trace中
 输入参数  : enTinType - TIN类型
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_LogTinTypeInfo(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType
)
{
    NAS_GMM_LOG_TIN_INFO_STRU          *pstTinTypeInfo = VOS_NULL_PTR;

    pstTinTypeInfo = (NAS_GMM_LOG_TIN_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_GMM,
                             sizeof(NAS_GMM_LOG_TIN_INFO_STRU));

    if ( VOS_NULL_PTR == pstTinTypeInfo )
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_LogTinTypeInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstTinTypeInfo->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstTinTypeInfo->stMsgHeader.ulSenderPid     = WUEPS_PID_GMM;
    pstTinTypeInfo->stMsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    pstTinTypeInfo->stMsgHeader.ulLength        = sizeof(NAS_GMM_LOG_TIN_INFO_STRU) - VOS_MSG_HEAD_LENGTH;;
    pstTinTypeInfo->stMsgHeader.ulMsgName       = NAS_GMM_LOG_TIN_TYPE_INFO_IND;

    pstTinTypeInfo->enTinType = enTinType;

    DIAG_TraceReport(pstTinTypeInfo);

    PS_MEM_FREE(WUEPS_PID_GMM, pstTinTypeInfo);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsNeedDeactiveISR_RauAccept
 功能描述  : 在RAU结束是否需要去激活， 以便于异变到L下可以发起TAU
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 是否需要修改Tin type,完成去激活
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月17日
    作    者   : f00261443
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_GMM_IsNeedDeactiveISR_RauAccept(VOS_VOID)
{
    VOS_UINT8                                               ucImsVoiceMMEnableFlg;
    VOS_UINT8                                               ucImsVoiceAvailFlg;
    NAS_MML_VOICE_DOMAIN_PREFERENCE_ENUM_UINT8              enVoiceDomainPreference;
    NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8                     enGUNwImsVoiceSupport;
    NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8                     enLNwImsVoiceSupport;

    ucImsVoiceMMEnableFlg   = NAS_MML_GetImsVoiceMMEnableFlg();
    ucImsVoiceAvailFlg      = NAS_MML_GetImsVoiceAvailFlg();
    enVoiceDomainPreference = NAS_MML_GetVoiceDomainPreference();
    enGUNwImsVoiceSupport   = NAS_MML_GetGUNwImsVoiceSupportFlg();
    enLNwImsVoiceSupport    = NAS_MML_GetLteNwImsVoiceSupportFlg();

    /* ISR激活时,满足如下条件则设置TIN为PTMSI,保证重选到LTE下能TAU */
    /* 24008 协议场景:
       1)ISR没激活 MS支持L 则应该把TIN设为"P-TMSI"
       2)ISR激活 满足p.5则设置TIN为"P-TMSI"
    */
    /* 24008 附录P.5条件
       满足如下两个场景之一
       场景1：
       1)MMA指示IMS VOICE可用
       2)UE的IMS 语音终端的移动性管理NV配置打开
       3)GU或L下IMS VOICE有一个支持且语音优选域不为CS ONLY
       4)当前在W下
       场景2：
       1)MMA指示IMS VOICE可用
       2)UE的IMS 语音终端的移动性管理NV配置打开
       3)W和L均支持IMS VOICE且GU和L下有一处的语音优选域为CS ONLY
    */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA         == NAS_MML_GetCurrNetRatType())
     && (VOS_TRUE                           == ucImsVoiceMMEnableFlg)
     && (VOS_TRUE                           == ucImsVoiceAvailFlg)
     && (NAS_MML_CS_VOICE_ONLY              != enVoiceDomainPreference)
     && ((NAS_MML_NW_IMS_VOICE_SUPPORTED    == enGUNwImsVoiceSupport)
      || (NAS_MML_NW_IMS_VOICE_SUPPORTED    == enLNwImsVoiceSupport)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsISRActived_RauAccept
 功能描述  : 判断Rau完成之后是否已激活ISR
 输入参数  : ucUpdateResultValue - Rau accept消息中Update result information element IE内容
 输出参数  : 无
 返 回 值  : 是否已经激活ISR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月28日
    作    者   : f00261443
    修改内容   : 新生成函数
  2.日    期   : 2015年6月4日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT8 NAS_GMM_IsISRActived_RauAccept(VOS_UINT8 ucUpdateResultValue)
{

    VOS_UINT32                                              ulPlatformSuppLteFlg;
    VOS_UINT8                                               ucIsrSupport;

    NAS_MML_TIMER_INFO_ENUM_UINT8                           enT3412Status;
    VOS_INT8                                                cVersion;

    cVersion      = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS);
    enT3412Status = NAS_MML_GetT3412Status();

    ucIsrSupport        = NAS_MML_GetIsrSupportFlg();

    ulPlatformSuppLteFlg = NAS_MML_IsPlatformSupportLte();

    /* 24008_CR1528R2_(Rel-10)_C1-102727-rev-C1-102388 24008 4.7.5.1.3描述如下:
    If the ROUTING AREA UPDATE ACCEPT message contains
    i)  no indication that ISR is activated, an MS supporting S1 mode shall set the TIN to "P-TMSI"; or
    ii) an indication that ISR is activated, the MS shall regard the available GUTI and
    TAI list as valid and registered with the network. If the TIN currently indicates "GUTI" and
    the periodic tracking area update timer T3412 is running, the MS shall set the
    TIN to "RAT-related TMSI". If the TIN currently indicates "GUTI" and the periodic
    tracking area update timer T3412 has already expired, the MS shall set the TIN
    to "P-TMSI".*/
    if (((GMM_RA_UPDATED_ISR_ACTIVE             == ucUpdateResultValue)
      || (GMM_COMBINED_RALA_UPDATED_ISR_ACTIVE  == ucUpdateResultValue))
     && (VOS_TRUE                               == ulPlatformSuppLteFlg)
     && (VOS_TRUE                               == ucIsrSupport)
     && ((cVersion <= PS_PTL_VER_R9)
      || (NAS_MML_TIMER_EXP != enT3412Status)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_UpdateTinType_RauAccept
 功能描述  : GMM收到rau accept消息时更新TIN类型
 输入参数  : enTinType           - TIN类型
             pucImsi             - imsi内容
             ucUpdateResultValue - Rau accept消息中Update result information element IE内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月21日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年12月28日
    作    者   : s46746
    修改内容   : DSDA GUNAS C CORE项目，增加平台能力判断
  3.日    期   : 2013年05月23日
    作    者   : z00234330
    修改内容   : DTS2013052301419，增加IsR是否支持的判断
  4.日    期   : 2013年12月17日
    作    者   : f00261443
    修改内容   : 增加异系统到 L 下，去激活ISR和RAU完成设置Tin类型
                 为P-TMSI的场景
*****************************************************************************/
VOS_VOID NAS_GMM_UpdateTinType_RauAccept(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType,
    VOS_UINT8                          *pucImsi,
    VOS_UINT8                           ucUpdateResultValue
)
{


    /* RAU完成后是否激活ISR */
    if (VOS_TRUE == NAS_GMM_IsISRActived_RauAccept(ucUpdateResultValue))
    {
        /* 是否需要去激活ISR */
        if (VOS_TRUE == NAS_GMM_IsNeedDeactiveISR_RauAccept())
        {
            NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pucImsi);
            Gmm_TimerStop(GMM_TIMER_T3323);
            /* ISR去激活，需要更新pdp激活是在ISR激活前激活的 */
            NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);

            return;
        }

        /* ISR已经激活 */
        if (NAS_MML_TIN_TYPE_GUTI == enTinType)
        {
            NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_RAT_RELATED_TMSI, pucImsi);
        }

        return;
    }

    /* 没有激活ISR */
    NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pucImsi);
    Gmm_TimerStop(GMM_TIMER_T3323);
    /* ISR去激活，需要更新pdp激活是在ISR激活前激活的 */
    NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);


    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsAbleCombinedRau_TimerStatusChg
 功能描述  : GMM收到T3412定时器超时或T3423在运行或T3423超时是否能发起联合rau
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE -  满足发起RAU
             VOS_FALSE - 不满足发起RAU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月21日
    作    者   : z00161729
    修改内容   : 新生成函数

  2.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsAbleCombinedRau_TimerStatusChg(VOS_VOID)
{
    VOS_UINT8                           ucSimCsRegStatus;

    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
    {
         /* 如果当前不是网络模式I和cs ps mode，返回不满足发起RAU条件 */
         return VOS_FALSE;
    }

    if ((VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
     || (VOS_FALSE == ucSimCsRegStatus)
     || (VOS_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
    {
        /* 如果cs注册被禁或cs卡无效或cs在通话过程中，返回不满足发起RAU条件  */
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsrActiveRaiNoChgBeforeT3312Exp_InterSys
 功能描述  : ISR激活路由区未改变，idle态从L异系统到GU,T3312未超时的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月21日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2012年08月24日
   作    者   : m00217266
   修改内容   : 修改Gmm_SndSmEstablishCnf接口，添加原因值
 3.日    期   : 2013年2月4日
   作    者   : w00176964
   修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
 4.日    期   : 2013年11月1日
   作    者   : z00161729
   修改内容   : DTS2013110103529:L重建到gu，ISR激活位置区未改变，gmm未发起rau
 5.日    期   : 2014年01月10日
   作    者   : f00261443
   修改内容   : VoLTE_PhaseIII项目
 6.日    期   : 2014年04月08日
   作    者   : s00217060
   修改内容   : DTS2014040901544:PS域注册被拒#111,网络带的T3302定时器时长为0，链接释放再收到系统消息时，UE一直发起ATTACH
*****************************************************************************/
VOS_VOID NAS_GMM_IsrActiveRaiNoChgBeforeT3312Exp_InterSys(VOS_VOID)
{
    VOS_UINT8                                               ucCsRestrictionFlg;
    VOS_UINT8                                               ucCsAttachAllow;
    VOS_UINT8                                               ucSimCsRegStatus;
    VOS_UINT8                                               ucImsVoiceMMEnableFlg;
	VOS_UINT8                                               ucImsVoiceAvailFlg;
    NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8                     enImsSupportInLTE;
    NAS_MML_VOICE_DOMAIN_PREFERENCE_ENUM_UINT8              enVoiceDomainPreference;
    VOS_UINT8                                               ucOldSpecProc;

    ucCsAttachAllow    = NAS_MML_GetCsAttachAllowFlg();
    ucSimCsRegStatus   = NAS_MML_GetSimCsRegStatus();
    ucCsRestrictionFlg = NAS_MML_GetCsRestrictRegisterFlg();

    /* 24008 4.7.5中in Iu mode and A/Gb mode after intersystem change from S1 mode,
       and the GMM receives an indication of "RRC connection failure" from lower layers due to
       lower layer failure while in S1 mode;
       如果LTE重建成功如果ISR激活位置区未改变，gmm判断该标识为1需要触发rau */

    /* 网络带下来的T3302定时器时长为0时，不启T3302定时器，如果不加最后一个判断，UE会一直发起ATTACH */
    if ((VOS_TRUE == Nas_GetLrrcConnFailureFlag())
     && (GMM_TIMER_T3302_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
     && (0 != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal))
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
    else if (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == NAS_MML_GetPsUpdateStatus())
    {
        /**
          * 24301中对于从L异系统变换到U下，增加了RAU的场景：
          * If the TRACKING AREA UPDATE ACCEPT message contains:
          * i)  no indication that ISR is activated, the UE shall set the TIN to "GUTI";
          * ii) an indication that ISR is activated, then:
          * -   if the UE is required to perform routing area updating for IMS voice
          * termination as specified in 3GPP TS 24.008 [13], annex P.5,
          * the UE shall set the TIN to "GUTI";

          * 24008中规定：
          * 支持IMS的终端从L异变到G下，且Tin Type 为 RAT-related TIN,则需要进行RAU,见p.4
          * P.4
          * 1)设备支持 IMS Voice
          * 2)L下网络支持ImsVoice
          * 3)语音优选域不是 CS Only
          * 目前GU下不支持IMS，因此在L下ISR激活时按照协议L必然去激活ISR这样到g下
          会自然发起RAU，因此目前不会进入该分支,用于后续扩展.
          */
        ucImsVoiceMMEnableFlg = NAS_MML_GetImsVoiceMMEnableFlg();
        ucImsVoiceAvailFlg = NAS_MML_GetImsVoiceAvailFlg();
        enImsSupportInLTE = NAS_MML_GetLteNwImsVoiceSupportFlg();
        enVoiceDomainPreference = NAS_MML_GetVoiceDomainPreference();

        if ( (VOS_TRUE == ucImsVoiceMMEnableFlg)
          && (VOS_TRUE == ucImsVoiceAvailFlg)
          && (NAS_MML_NW_IMS_VOICE_SUPPORTED == enImsSupportInLTE)
          && (NAS_MML_CS_VOICE_ONLY != enVoiceDomainPreference))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);

            return;
        }
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
         || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod)
         || (VOS_TRUE == ucCsRestrictionFlg))
        {
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);

            g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;

            /* 向MMC发送PS注册结果 */
            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                         GMM_MMC_ACTION_RESULT_SUCCESS,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);

            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
        }
        else
        {
            if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
            {
                Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);

                if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                {                                                       /* 需要给SM回EST_CNF                        */
                    g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;

                    Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);    /* 向SM回建立成功的响应                     */
                }

                if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                {                                                       /* CS域允许注册                             */
                    NAS_GMM_SndMmCombinedRauInitiation();
                    NAS_GMM_SndMmCombinedRauAccept(GMMMM_RAU_RESULT_COMBINED,
                                                   NAS_MML_REG_FAIL_CAUSE_NULL,
                                                   VOS_NULL_PTR,
                                                   VOS_NULL_PTR);
                }

                /* 向MMC发送PS注册结果 */
                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                             GMM_MMC_ACTION_RESULT_SUCCESS,
                                             NAS_MML_REG_FAIL_CAUSE_NULL);

            }
            else
            {
                /* sim无效或者CS域不允许注册 */
                if ((VOS_FALSE == ucCsAttachAllow)
                 || (VOS_TRUE != ucSimCsRegStatus))
                {
                    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);

                    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                    {                                                   /* 需要给SM回EST_CNF                        */
                        g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;

                        Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);        /* 向SM回建立成功的响应                     */
                    }
                    g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;

                    /* 向MMC发送PS注册结果 */
                    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                 GMM_MMC_ACTION_RESULT_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);

                    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
                }
                else
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                }
            }
        }
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;       /* 设置真流程标志 */
    }
    else
    {
        if (GMM_TIMER_T3302_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
        {
            Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE);

            ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;
            g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
            g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

            /* 向MMC发送PS注册结果 */
            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

            if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
              && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
            {
                NAS_GMM_NotifyMmUnrealCombinedRauResult();
            }

            g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
            g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
        }
        else
        {
            /* PS更新状态不是GU1 */
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }

    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsrActiveRaiNoChgAfterT3312Exp_InterSys
 功能描述  : ISR激活路由区未改变，idle态从L异系统到GU,T3312超时的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月2日
    作    者   : z00161729
    修改内容   : 新生成函数

  2.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
*****************************************************************************/
VOS_VOID NAS_GMM_IsrActiveRaiNoChgAfterT3312Exp_InterSys(VOS_VOID)
{
    /* NMO1下,不通过手机模式判断是否需要发起联合注册 */
    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
    {
        /* 非A+I */
        Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
    }
    else
    {
        /* A+I */
        Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
    }
}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsrActiveRaiNoChg_InterSys
 功能描述  : ISR激活路由区未改变，idle态从L异系统到GU的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月21日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_IsrActiveRaiNoChg_InterSys(VOS_VOID)
{
    if (GMM_FALSE == g_GmmRauCtrl.ucT3312ExpiredFlg)
    {
        NAS_GMM_IsrActiveRaiNoChgBeforeT3312Exp_InterSys();
        return;
    }

    NAS_GMM_IsrActiveRaiNoChgAfterT3312Exp_InterSys();
    return;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_IsRegNeedFillVoiceDomainPreferenceAndUeUsageSettingIE
 功能描述  : 判断是否attach或rau注册消息中是否需要封装Voice domain preference and UE's usage setting IE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要
             VOS_FALSE - 不需要
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月4日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsRegNeedFillVoiceDomainPreferenceAndUeUsageSettingIE(VOS_VOID)
{
    VOS_UINT32                                  ulSupportLteFlg;
    VOS_UINT8                                   ucImsVoiceSupportFlag;

    ucImsVoiceSupportFlag = NAS_MML_IsUeSupportImsVoice();
    ulSupportLteFlg       = NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE);

    /* 24008_CR1678R2_(Rel-10)_C1-105172 rev of  C1-104874 rev of C1-104734 Correcting voice domain prefs IE conditions-Rel-10
    24008 9.4.1.11和9.4.14.16章节描述如下:
    This IE shall be included:
    -   if the MS supports CS fallback and SMS over SGs, or the MS is configured
        to support IMS voice, or both; and
    -   if the MS is E-UTRAN capable.*/
    if (((NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == NAS_MML_GetLteCsServiceCfg())
       || (VOS_TRUE == ucImsVoiceSupportFlag))
     && (VOS_TRUE == ulSupportLteFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_LogGasGmmRadioAccessCapability
 功能描述  : 勾包NAS调用GAS的接口GASGCOM_GetMsCapability
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月21日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_LogGasGmmRadioAccessCapability(
    VOS_UINT32                          ulRst,
    VOS_UINT8                           ucMsCapType,
    VOS_UINT16                          usSize,
    VOS_UINT8                          *pucData
)
{
    NAS_GMM_LOG_GAS_RADIO_ACCESS_CAP_STRU                  *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_GMM_LOG_GAS_RADIO_ACCESS_CAP_STRU*)PS_MEM_ALLOC(WUEPS_PID_GMM,
                                         sizeof(NAS_GMM_LOG_GAS_RADIO_ACCESS_CAP_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_LogGasGmmRadioAccessCapability:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(NAS_GMM_LOG_GAS_RADIO_ACCESS_CAP_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_GMM_LOG_GAS_RADIO_ACCESS_CAP_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = GMMOM_LOG_RADIAO_ACCESS_CAP;

    pstMsg->ulRst                       = ulRst;
    pstMsg->ucMsCapType                 = ucMsCapType;
    pstMsg->usSize                      = usSize;

    PS_MEM_CPY(pstMsg->aucData, pucData, usSize);

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_GMM, pstMsg);

    return;
}


#endif

/*****************************************************************************
 函 数 名  : NAS_GMM_StopT3311InIuPmmConnMode_T3312Exp
 功能描述  : w进入pmm connected mode时如果t3312定时器超时，如果T3311在运行，停止T3311
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月4日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_GMM_StopT3311InIuPmmConnMode_T3312Exp(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat;

    /* 取得当前的接入模式 */
    enCurrRat     = NAS_MML_GetCurrNetRatType();

    /* 取得当前的链接信息 */
    pstConnStatus = NAS_MML_GetConnStatus();

    /* 24008_CR1735R3_(Rel-10)_C1-111529 was 1470 was 1012 24008-a10 24008 4.7.5.1.5章节描述如下:
    If in addition the ROUTING AREA UPDATE REQUEST message indicated "periodic updating",
    -   in Iu mode, the timer T3311 may be stopped when the MS enters PMM-CONNECTED mode;
    -   in A/Gb mode, the timer T3311 may be stopped when the READY timer is started.*/
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRat)
     && (VOS_TRUE == pstConnStatus->ucPsSigConnStatusFlg)
     && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg))
    {
        Gmm_TimerStop(GMM_TIMER_T3311);
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_DeleteRandAndResInfoInPmmIdleMode
 功能描述  : w下pmm idle mode需要删除rand 和res信息，停止T3316
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月4日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_GMM_DeleteRandAndResInfoInPmmIdleMode(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    pstConnStatus = NAS_MML_GetConnStatus();

    /* 24008_CR2084_(Rel-11)_C1-120652 24008 4.7.7.2描述如下:
    The RAND and RES values stored in the mobile station shall be deleted and
    timer T3316, if running, shall be stopped: -if the mobile station enters
    PMM-IDLE mode (Iu mode only).*/
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
     && (VOS_FALSE == pstConnStatus->ucPsSigConnStatusFlg))
    {
        g_GmmAuthenCtrl.ucResStoredFlg  = GMM_FALSE;
        g_GmmAuthenCtrl.ucRandStoredFlg = GMM_FALSE;
        Gmm_TimerStop(GMM_TIMER_T3316);
    }
    return;
}

#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_GMM_IsRegNeedFillOldLocationAreaIdentificationIE
 功能描述  : 判断ATTCH和rau请求是否需要携带Old location area identification IE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要
             VOS_FALSE - 不需要
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月8日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsRegNeedFillOldLocationAreaIdentificationIE(VOS_VOID)
{
    NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8   enSpecProc;
    NAS_MML_LAI_STRU                   *pstCsSuccLai = VOS_NULL_PTR;
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;

    pstCsSuccLai = NAS_MML_GetCsLastSuccLai();
    enSpecProc   = NAS_GMM_GetSpecProc();
    enMsMode     = NAS_MML_GetMsMode();

    /* 24008_CR1986R5_(Rel-10)_C1-115368 和24008_CR1987R4_(Rel-11)_C1-115328 24008
    4.7.3.2.1章节描述如下:
    If the MS has stored a valid LAI and the MS supports EMM combined procedures,
    the MS shall include it in the Old location area identification IE in the ATTACH REQUEST message.
    4.7.5.2.1章节描述如下:
    If the MS has stored a valid LAI and the MS supports EMM combined procedures,
    the MS shall include it in the Old location area identification IE in the ROUTING AREA UPDATE REQUEST message.*/
    if (PS_PTL_VER_R11 > NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS))
    {
        return VOS_FALSE;
    }

    /* 不支持EMM Combined procedures capability(支持LTE且模式为CS_PS时认为支持),
       不需要携带Old location area identification IE*/
    if (VOS_FALSE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
    {
        return VOS_FALSE;
    }

    if (NAS_MML_MS_MODE_PS_CS != enMsMode)
    {
        return VOS_FALSE;
    }

    /* 不是联合注册流程，不需要携带Old location area identification IE */
    if ((GMM_RAU_COMBINED != enSpecProc)
     && (GMM_RAU_WITH_IMSI_ATTACH != enSpecProc)
     && (GMM_ATTACH_COMBINED != enSpecProc)
     && (GMM_ATTACH_WHILE_IMSI_ATTACHED != enSpecProc))
    {
        return VOS_FALSE;
    }

    /* LAI非法不需要携带,不需要携带Old location area identification IE */
    if (( NAS_MML_LAC_LOW_BYTE_INVALID == pstCsSuccLai->aucLac[0])
     && ( NAS_MML_LAC_HIGH_BYTE_INVALID == pstCsSuccLai->aucLac[1]))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_FillOldLocationAreaIdentificationIE
 功能描述  : 填充ATTCH和rau请求的Old location area identification的IE内容
 输入参数  : pucAddr - 封装IE消息地址
 输出参数  : 无
 返 回 值  : 填写的IE的长度ucNumber
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月8日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT8 NAS_GMM_FillOldLocationAreaIdentificationIE(
    VOS_UINT8                          *pucAddr
)
{
    VOS_UINT8                           ucLen;
    NAS_MML_LAI_STRU                   *pstCsSuccLai = VOS_NULL_PTR;

    pstCsSuccLai = NAS_MML_GetCsLastSuccLai( );
    ucLen        = 0;

    /* 该IE结构参见24008 10.5.5.30章节描述 */
    pucAddr[ucLen++] = NAS_GMM_IEI_OLD_LOCATION_AREA_IDENTIFICATION;
    pucAddr[ucLen++] = NAS_GMM_IE_OLD_LOCATION_AREA_IDENTIFICATION_LEN;

    pucAddr[ucLen] |= (VOS_UINT8)(0x0000000f & pstCsSuccLai->stPlmnId.ulMcc);

    pucAddr[ucLen++] |= (VOS_UINT8)((0x00000f00 & pstCsSuccLai->stPlmnId.ulMcc) >> NAS_MML_OCTET_MOVE_FOUR_BITS);
    pucAddr[ucLen]   |= (VOS_UINT8)((0x000f0000 & pstCsSuccLai->stPlmnId.ulMcc) >> NAS_MML_OCTET_MOVE_SIXTEEN_BITS);
    pucAddr[ucLen++] |= (VOS_UINT8)((0x000f0000 & pstCsSuccLai->stPlmnId.ulMnc) >> NAS_MML_OCTET_MOVE_TWELVE_BITS);
    pucAddr[ucLen]   |= (VOS_UINT8)(0x0000000f & pstCsSuccLai->stPlmnId.ulMnc );
    pucAddr[ucLen++] |= (VOS_UINT8)((0x00000f00 & pstCsSuccLai->stPlmnId.ulMnc) >> NAS_MML_OCTET_MOVE_FOUR_BITS);

    /* 设置LAC高8位 */
    pucAddr[ucLen++] = (VOS_UINT8)(pstCsSuccLai->aucLac[0]);

    /* 设置LAC低8位 */
    pucAddr[ucLen++] = (VOS_UINT8)pstCsSuccLai->aucLac[1];

    return ucLen;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_GMM_SaveGprsTimer3Value
 功能描述  : 更新T3312定时器时长
 输入参数  : ucTimerName     - 定时器名称
             ucMsgTimerValue - 消息中定时器值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年6月8日
   作    者   : z00161729
   修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_GMM_SaveGprsTimer3Value(
    VOS_UINT8                            ucTimerName,
    VOS_UINT8                            ucMsgTimerValue
)
{
    VOS_UINT8                            ucTimerUnit;                                                   /* 定义临时变量存储时长单位                 */
    VOS_UINT8                            ucTimerValue;                                                   /* 定义临时变量存储时长                     */


    ucTimerUnit     = 0;
    ucTimerValue    = 0;
    ucTimerUnit     = (VOS_UINT8)(ucMsgTimerValue >> 5);
    ucTimerValue    = (VOS_UINT8)(ucMsgTimerValue & 0x1F);

    /* 24008 10.5.163a章节描述如下:
    GPRS Timer 3 value (octet 3)
    Bits 5 to 1 represent the binary coded timer value.
    Bits 6 to 8 defines the timer value unit for the GPRS timer as follows:
    Bits
    8 7 6
    0 0 0 value is incremented in multiples of 10 minutes
    0 0 1 value is incremented in multiples of 1 hour
    0 1 0 value is incremented in multiples of 10 hours
    0 1 1 value is incremented in multiples of 2 seconds
    1 0 0 value is incremented in multiples of 30 seconds
    1 0 1 value is incremented in multiples of 1 minute
    1 1 1 value indicates that the timer is deactivated.

    Other values shall be interpreted as multiples of 1 hour in this version of the protocol.
    */
    switch (ucTimerUnit)
    {
        case 0:
            /* 10分钟 */
            g_GmmTimerMng.aTimerInf[ucTimerName].ulTimerVal
                = ucTimerValue * 10 * 60 * 1000;
            break;

        case 1:
            /* 1小时 */
            g_GmmTimerMng.aTimerInf[ucTimerName].ulTimerVal
                = ucTimerValue * 60 * 60 * 1000;
            break;

        case 2:
            /* 10小时 */
            g_GmmTimerMng.aTimerInf[ucTimerName].ulTimerVal
                = ucTimerValue * 10 * 60 * 60 * 1000;
            break;

        case 3:
            /* 2秒 */
            g_GmmTimerMng.aTimerInf[ucTimerName].ulTimerVal
                = ucTimerValue * 2 * 1000;
            break;

        case 4:
            /* 30秒 */
            g_GmmTimerMng.aTimerInf[ucTimerName].ulTimerVal
                = ucTimerValue * 30 * 1000;
            break;

        case 5:
            /* 1分钟 */
            g_GmmTimerMng.aTimerInf[ucTimerName].ulTimerVal
                = ucTimerValue * 60 * 1000;
            break;

        case 7:
            /* timer is deactivated */
            g_GmmTimerMng.aTimerInf[ucTimerName].ulTimerVal = 0;
            break;

        default:
            /* 1小时 */
            g_GmmTimerMng.aTimerInf[ucTimerName].ulTimerVal
                = ucTimerValue * 60 * 60 * 1000;
            break;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_IsRegNeedFillTmsiStatusIE
 功能描述  : 判断是否attach或rau注册消息中是否需要封装tmsi status IE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要
             VOS_FALSE - 不需要
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月4日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsRegNeedFillTmsiStatusIE(VOS_VOID)
{
    /* 24008 9.4.1.3章节描述如下:
      This IE shall be included if the MS performs a combined GPRS attach and no valid TMSI is available
      24008 9.4.14.4章节描述如下:
      This IE shall be included if the MS performs a combined routing area update and no valid TMSI is available.*/
    if ((VOS_FALSE  == NAS_MML_IsTmsiValid())
     && ((GMM_ATTACH_WHILE_IMSI_ATTACHED == NAS_GMM_GetSpecProc())
      || (GMM_ATTACH_COMBINED          == NAS_GMM_GetSpecProc())
      || (GMM_RAU_COMBINED         == NAS_GMM_GetSpecProc())
      || (GMM_RAU_WITH_IMSI_ATTACH == NAS_GMM_GetSpecProc())))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_GetAllocT3302ValuePlmnWithRat
 功能描述  : 获取下发t3302定时器时长网络信息
 输入参数  : 无
 输出参数  : VOS_VOID
 返 回 值  : NAS_MML_PLMN_ID_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
NAS_MML_PLMN_WITH_RAT_STRU *NAS_GMM_GetAllocT3302ValuePlmnWithRat(VOS_VOID)
{
    return &(g_GmmGlobalCtrl.stAllocT3302ValuePlmnWithRat);
}

/*****************************************************************************
 函 数 名  : NAS_GMM_SetAllocT3302ValuePlmnWithRat
 功能描述  : 设置下发t3302定时器时长网络信息
 输入参数  : 无
 输出参数  : VOS_VOID
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_GMM_SetAllocT3302ValuePlmnWithRat(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnWithRat
)
{
    g_GmmGlobalCtrl.stAllocT3302ValuePlmnWithRat.stPlmnId.ulMcc = pstPlmnWithRat->stPlmnId.ulMcc;
    g_GmmGlobalCtrl.stAllocT3302ValuePlmnWithRat.stPlmnId.ulMnc = pstPlmnWithRat->stPlmnId.ulMnc;
    g_GmmGlobalCtrl.stAllocT3302ValuePlmnWithRat.enRat = pstPlmnWithRat->enRat;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsNeedUseDefaultT3302ValueRauAttempCntMax
 功能描述  : 判断rau attempt cnt达到最大次数启动t3302定时器时是否需要使用T3302默认值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要使用默认值
             VOS_FALSE - 不需要使用默认值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedUseDefaultT3302ValueRauAttempCntMax(VOS_VOID)
{
    NAS_MML_PLMN_WITH_RAT_STRU         *pstAllocT3302PlmnWithRat = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;

    pstAllocT3302PlmnWithRat = NAS_GMM_GetAllocT3302ValuePlmnWithRat();
    enCurrNetRatType         = NAS_MML_GetCurrNetRatType();

    /* 24008_CR1904R1_(Rel-11)_C1-113602 Handling of timer T3302 24008 4.7.2.x章节描述如下:
    The MS shall apply this value in the routing area registered by the MS, until a new value is received.
    The default value of this timer is used in the following cases:
    -   ATTACH ACCEPT message, ROUTING AREA UPDATE ACCEPT message, ATTACH REJECT message, or ROUTING AREA UPDATE REJECT message is received without a value specified;
    -   In Iu mode, if the network provides a value in a non-integrity protected Iu mode GMM message and the MS is not attaching for emergency services or not attached for emergency services;
    -   the MS does not have a stored value for this timer; or
    -   a new PLMN which is not in the list of equivalent PLMNs has been entered, the routing area updating fails and the routing area updating attempt counter is equal to 5.
    注册失败达5次，且上次下发t3302定时器时长的网络同当前驻留网络不同，或接入技术不同，则t3302使用默认值。*/
    if (VOS_FALSE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstAllocT3302PlmnWithRat->stPlmnId, NAS_MML_GetCurrCampPlmnId()))
    {
        return VOS_TRUE;
    }

    if (pstAllocT3302PlmnWithRat->enRat != enCurrNetRatType)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsRegNeedFillTmsiBasedNRIContainerIE
 功能描述  : 判断ATTCH和rau请求是否需要携带TMSI based NRI container IE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要
             VOS_FALSE - 不需要
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月8日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsRegNeedFillTmsiBasedNRIContainerIE(VOS_VOID)
{
    NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8   enSpecProc;

    enSpecProc   = NAS_GMM_GetSpecProc();

    /* 24008_CR2145R3_(Rel-11)_C1-122517 /24008_CR2183R1_(Rel-11)_C1-123313/24008_CR2246_(Rel-11)_C1-123539
    24008 4.7.3.2.1描述如下:
    If the MS has stored a valid TMSI, the MS shall include the TMSI based NRI container IE
    in the ATTACH REQUEST message.
    4.7.5.2.1描述如下:
    If the MS has stored a valid TMSI, the MS shall include the TMSI based NRI container IE
    in the ROUTING AREA UPDATE REQUEST message..*/
    if (PS_PTL_VER_R11 > NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS))
    {
        return VOS_FALSE;
    }

    /* 不是联合注册流程，不需要携带TMSI based NRI container IE */
    if ((GMM_RAU_COMBINED != enSpecProc)
     && (GMM_RAU_WITH_IMSI_ATTACH != enSpecProc)
     && (GMM_ATTACH_COMBINED != enSpecProc)
     && (GMM_ATTACH_WHILE_IMSI_ATTACHED != enSpecProc))
    {
        return VOS_FALSE;
    }

    /* Tmsi非法,不需要携带TMSI based NRI container IE */
    if (VOS_FALSE  == NAS_MML_IsTmsiValid())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_FillTmsiBasedNRIContainerIE
 功能描述  : 填充ATTCH和rau请求的TMSI based NRI container IE内容
 输入参数  : pucAddr - 封装IE消息地址
 输出参数  : 无
 返 回 值  : 填写的IE的长度ucNumber
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月8日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT8 NAS_GMM_FillTmsiBasedNRIContainerIE(
    VOS_UINT8                          *pucAddr
)
{
    VOS_UINT8                           ucLen;
    VOS_UINT8                           ucBitValue;
    VOS_UINT8                          *pucTmsi = VOS_NULL_PTR;

    pucTmsi = NAS_MML_GetUeIdTmsi();
    ucLen   = 0;

    /* 该IE结构参见10.5.5.31章节描述:
    NRI container value (octet 3 and bit 7-8 of octet 4)
    The NRI container value consists of 10 bits which correspond to bits 23 to 14 of the valid TMSI.
    NRI container value shall start with bit 8 of octet 3, which corresponds to bit 23 of TMSI. Bit 7 of octet 4 corresponds to TMSI bit 14.
    Bits 6, 5, 4, 3, 2, and 1 in octet 4 are spare and shall be set to zero.*/
    pucAddr[ucLen++] = NAS_GMM_IEI_TMSI_BASED_NRI_CONTAINER;
    pucAddr[ucLen++] = NAS_GMM_IE_TMSI_BASED_NRI_CONTAINER_LEN;

    /* 取tmsi的第16位(pucTmsi[0]为第1位)，赋值到NRI container value octet 3 bit 1 */
    ucBitValue = NAS_MML_GetBitValueFromBuffer(pucTmsi, 16);
    NAS_MML_SetBitValueToBuffer(&pucAddr[ucLen], 1, ucBitValue);


    /* 取tmsi的第17位，赋值到NRI container value octet 3 bit 2 */
    ucBitValue = NAS_MML_GetBitValueFromBuffer(pucTmsi, 17);
    NAS_MML_SetBitValueToBuffer(&pucAddr[ucLen], 2, ucBitValue);


    /* 取tmsi的第18位，赋值到NRI container value octet 3 bit 3 */
    ucBitValue = NAS_MML_GetBitValueFromBuffer(pucTmsi, 18);
    NAS_MML_SetBitValueToBuffer(&pucAddr[ucLen], 3, ucBitValue);

    /* 取tmsi的第19位，赋值到NRI container value octet 3 bit 4 */
    ucBitValue = NAS_MML_GetBitValueFromBuffer(pucTmsi, 19);
    NAS_MML_SetBitValueToBuffer(&pucAddr[ucLen], 4, ucBitValue);

    /* 取tmsi的第20位，赋值到NRI container value octet 3 bit 5 */
    ucBitValue = NAS_MML_GetBitValueFromBuffer(pucTmsi, 20);
    NAS_MML_SetBitValueToBuffer(&pucAddr[ucLen], 5, ucBitValue);

    /* 取tmsi的第21位，赋值到NRI container value octet 3 bit 6 */
    ucBitValue = NAS_MML_GetBitValueFromBuffer(pucTmsi, 21);
    NAS_MML_SetBitValueToBuffer(&pucAddr[ucLen], 6, ucBitValue);

    /* 取tmsi的第22位，赋值到NRI container value octet 3 bit 7 */
    ucBitValue = NAS_MML_GetBitValueFromBuffer(pucTmsi, 22);
    NAS_MML_SetBitValueToBuffer(&pucAddr[ucLen], 7, ucBitValue);

    /* 取tmsi的第23位，赋值到NRI container value octet 3 bit 8 */
    ucBitValue = NAS_MML_GetBitValueFromBuffer(pucTmsi, 23);
    NAS_MML_SetBitValueToBuffer(&pucAddr[ucLen], 8, ucBitValue);

    ucLen++;

    /* 赋初值 */
    pucAddr[ucLen] = 0;

    /* 取tmsi的第14位，赋值到NRI container value octet 4 bit 7 */
    ucBitValue = NAS_MML_GetBitValueFromBuffer(pucTmsi, 14);
    NAS_MML_SetBitValueToBuffer(&pucAddr[ucLen], 7, ucBitValue);

    /* 取tmsi的第15位，赋值到NRI container value octet 4 bit 8 */
    ucBitValue = NAS_MML_GetBitValueFromBuffer(pucTmsi, 15);
    NAS_MML_SetBitValueToBuffer(&pucAddr[ucLen], 8, ucBitValue);

    ucLen++;

    return ucLen;
}

/*****************************************************************************
 函 数 名  : NAS_Gmm_FillMsNetworkFeatureSupportIE
 功能描述  : 封装ms network feature support IE
 输入参数  : pucAddr
 输出参数  : pucAddr
 返 回 值  : 长度
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年6月8日
   作    者   : z00161729
   修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT8 NAS_GMM_FillMsNetworkFeatureSupportIE(
    VOS_UINT8                          *pucAddr
)
{
    VOS_UINT8                           ucLen;

    ucLen = 0;

    pucAddr[0] = GMM_IE_MS_SUPPORT_EXTEND_PERIODIC_TIMER_IN_THIS_DOMAIN;

    /* 填写IEI为 C0 */
    pucAddr[0] |= GMM_IEI_MS_NETWORK_FEATURE_SUPPORT;

    ucLen      = GMM_MS_NETWORK_FEATURE_SUPPORT_IE_LEN;

    return ucLen;
}




/*****************************************************************************
 函 数 名  : NAS_GMM_ConvertPdpCtxStatusToNetworkPdpCtxStatus
 功能描述  : 将MML的pdp状态转换为发给网络格式
 输入参数  : pstPsBearerCtx  - MML中pdp状态信息
 输出参数  : pstPdpCtxStatus - 转换后pdp状态
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月15日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年3月15日
    作    者   : l65478
    修改内容   : DTS2013120300990:在PDP激活过程中发起RAU,第一次PDP激活失败
  3.日    期   : 2014年12月06日
    作    者   : A00165503
    修改内容   : DTS2014120207400: 连续去激活多个PDP, 网侧不释放RRC连接
*****************************************************************************/
VOS_VOID NAS_GMM_ConvertPdpCtxStatusToNetworkPdpCtxStatus(
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearerCtx,
    VOS_UINT32                         *pulPdpCtxStatus
)
{
    VOS_UINT32                          ulPdpCtxStatus;
    VOS_UINT32                          i;

    ulPdpCtxStatus = 0;

    for ( i = 0; i < NAS_MML_MAX_PS_BEARER_NUM; i++)
    {
        /* refer to 24.008 10.5.7.1
           1	indicates that the SM state of the corresponding PDP context is not PDP-INACTIVE */
        if ((NAS_MML_PS_BEARER_STATE_ACTIVE == pstPsBearerCtx[i].enPsBearerState)
         || (VOS_TRUE == pstPsBearerCtx[i].ucPsActPending)
         || (VOS_TRUE == pstPsBearerCtx[i].ucPsDeactPending))
        {
            /*lint -e701*/
            ulPdpCtxStatus |= 0x00000001 << (i + NAS_MML_NSAPI_OFFSET);
            /*lint +e701*/
        }
    }
    *pulPdpCtxStatus = ulPdpCtxStatus;

}



/*****************************************************************************
 函 数 名  : NAS_GMM_ConverRrcGmmProcTypeToMml
 功能描述  : rrmm的gmm proc type类型转换为MML的
 输入参数  : enRrmmGmmProcType:rrmm的gmm proc type
 输出参数  : penMmlGmmProcType:MML中gmm proc type
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月28日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
VOS_VOID    NAS_GMM_ConverRrcGmmProcTypeToMml(
    RRMM_GMM_PROC_TYPE_ENUM_UINT16      enRrmmGmmProcType,
    NAS_MML_GMM_PROC_TYPE_ENUM_UINT16  *penMmlGmmProcType
)
{
    switch (enRrmmGmmProcType)
    {
        case RRMM_GMM_PROC_TYPE_ATTACH:
            *penMmlGmmProcType = NAS_MML_GMM_PROC_TYPE_ATTACH;
            break;

        case RRMM_GMM_PROC_TYPE_NORMAL_RAU:
            *penMmlGmmProcType = NAS_MML_GMM_PROC_TYPE_NORMAL_RAU;
            break;

        case RRMM_GMM_PROC_TYPE_PERIOD_RAU:
            *penMmlGmmProcType = NAS_MML_GMM_PROC_TYPE_PERIOD_RAU;
            break;


        default:
            NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_ConverRrcGmmProcTypeToMml: Invalid gmm proc type!");
            *penMmlGmmProcType = NAS_MML_GMM_PROC_TYPE_INVALID;
            break;
    }
}


/*****************************************************************************
 函 数 名  : NAS_GMM_ConverRrcGmmProcFlagToMml
 功能描述  : rrmm的gmm proc flag类型转换为MML的
 输入参数  : enRrmmGmmProcFlag:rrmm的gmm proc type
 输出参数  : penMmlGmmProcFlag:MML中gmm proc type
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月28日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
VOS_VOID    NAS_GMM_ConverRrcGmmProcFlagToMml(
    RRMM_GMM_PROC_FLAG_ENUM_UINT16      enRrmmGmmProcFlag,
    NAS_MML_GMM_PROC_FLAG_ENUM_UINT16  *penMmlGmmProcFlag
)
{
    switch (enRrmmGmmProcFlag)
    {
        case RRMM_GMM_PROC_FLAG_START:
            *penMmlGmmProcFlag = NAS_MML_GMM_PROC_FLAG_START;
            break;

        case RRMM_GMM_PROC_FLAG_FINISH:
            *penMmlGmmProcFlag = NAS_MML_GMM_PROC_FLAG_FINISH;
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_GMM, "penMmlGmmProcFlag: Invalid gmm proc flag!");
            *penMmlGmmProcFlag = NAS_MML_GMM_PROC_FLAG_INVALID;
            break;
    }
}


/*****************************************************************************
 函 数 名  : NAS_GMM_TransGmmNwCause2GmmSmCause
 功能描述  : 将GMM Cause装换成GMM/SM Cause
 输入参数  : enGmmCause - GMM Cause
 输出参数  : 无
 返 回 值  : GMM_SM_CAUSE_ENUM_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月6日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
GMM_SM_CAUSE_ENUM_UINT16 NAS_GMM_TransGmmNwCause2GmmSmCause(
    VOS_UINT8  enGmmCause
)
{
    GMM_SM_CAUSE_ENUM_UINT16            enGmmSmCause;

    if ( (enGmmCause >= NAS_MML_REG_FAIL_CAUSE_RETRY_UPON_ENTRY_CELL_MIN)
      && (enGmmCause <= NAS_MML_REG_FAIL_CAUSE_RETRY_UPON_ENTRY_CELL_MAX) )
    {
        enGmmSmCause = NAS_MML_REG_FAIL_CAUSE_RETRY_UPON_ENTRY_CELL + GMM_SM_CAUSE_GMM_NW_CAUSE_OFFSET;
    }
    else
    {
        enGmmSmCause = enGmmCause + GMM_SM_CAUSE_GMM_NW_CAUSE_OFFSET;
    }

    return enGmmSmCause;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_LogGmmStateInfo
 功能描述  : 勾GMM的状态
 输入参数  : ucGmmState: GMM的当前状态
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年08月21日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_GMM_LogGmmStateInfo(
    VOS_UINT8                           ucGmmState
)
{
    NAS_GMM_LOG_STATE_INFO_STRU        *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_GMM_LOG_STATE_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_GMM,
                                         sizeof(NAS_GMM_LOG_STATE_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_LogGmmStateInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(NAS_GMM_LOG_STATE_INFO_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_GMM_LOG_STATE_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = GMMOM_LOG_STATE_INFO_IND;
    pstMsg->enGmmState                  = (NAS_GMM_STATE_ID_ENUM_UINT8)ucGmmState;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_GMM, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_LogGmmCtxInfo
 功能描述  : 勾GMM全局变量
 输入参数  : 无
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2015年2月12日
    作    者   : s00217060
    修改内容   : VOLTE SWITCH修改：勾出上次发attach/rau时的voice domain
  3.日    期   : 2015年6月15日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID  NAS_GMM_LogGmmCtxInfo(VOS_VOID)
{
    GMMOM_LOG_CTX_INFO_STRU            *pstMsg = VOS_NULL_PTR;
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    pstMsg = (GMMOM_LOG_CTX_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_GMM,
                                         sizeof(GMMOM_LOG_CTX_INFO_STRU));

    pstConnStatus = NAS_MML_GetConnStatus();

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_LogGmmCtxInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(GMMOM_LOG_CTX_INFO_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulLength        = sizeof(GMMOM_LOG_CTX_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = GMMOM_LOG_CTX_INFO_IND;

    pstMsg->stGmmGasGlobalCtrlInfo.ucLastDataSender  = gstGmmCasGlobalCtrl.ucLastDataSender;
    pstMsg->stGmmGasGlobalCtrlInfo.ucSuspendLlcCause = gstGmmCasGlobalCtrl.ucSuspendLlcCause;
    pstMsg->stGmmGasGlobalCtrlInfo.ucTlliAssignFlg   = gstGmmCasGlobalCtrl.ucTlliAssignFlg;

    pstMsg->stGmmGlobalCtrlInfo.CsInfo_ucCsTransFlg  = g_GmmGlobalCtrl.CsInfo.ucCsTransFlg;
    pstMsg->stGmmGlobalCtrlInfo.SysInfo_Rai          = g_GmmGlobalCtrl.SysInfo.Rai;
    pstMsg->stGmmGlobalCtrlInfo.SysInfo_ucCellChgFlg = g_GmmGlobalCtrl.SysInfo.ucCellChgFlg;
    pstMsg->stGmmGlobalCtrlInfo.SysInfo_ucNetMod     = g_GmmGlobalCtrl.SysInfo.ucNetMod;
    pstMsg->stGmmGlobalCtrlInfo.ucCvrgAreaLostFlg    = g_GmmGlobalCtrl.ucCvrgAreaLostFlg;
    pstMsg->stGmmGlobalCtrlInfo.ucDetachType         = (VOS_UINT8)g_GmmGlobalCtrl.stDetachInfo.enDetachType;
    pstMsg->stGmmGlobalCtrlInfo.ucRaiChgRelFlg       = g_GmmGlobalCtrl.ucRaiChgRelFlg;
    pstMsg->stGmmGlobalCtrlInfo.ucRelCause           = g_GmmGlobalCtrl.ucRelCause;
    pstMsg->stGmmGlobalCtrlInfo.ucSigConFlg          = g_GmmGlobalCtrl.ucSigConFlg;
    pstMsg->stGmmGlobalCtrlInfo.ucPlmnSrchPreSta     = g_GmmGlobalCtrl.ucPlmnSrchPreSta;
    pstMsg->stGmmGlobalCtrlInfo.ucSpecProc           = g_GmmGlobalCtrl.ucSpecProc;
    pstMsg->stGmmGlobalCtrlInfo.ucSpecProcInCsTrans  = g_GmmGlobalCtrl.ucSpecProcInCsTrans;
    pstMsg->stGmmGlobalCtrlInfo.UeInfo_ucMsRadioCapSupportLteFromAs     = g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs;
    pstMsg->stGmmGlobalCtrlInfo.UeInfo_ucMsRadioCapSupportLteFromRegReq = g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromRegReq;
    pstMsg->stGmmGlobalCtrlInfo.UeInfo_UeId_ucUeIdMask = g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask;
    PS_MEM_CPY(&pstMsg->stGmmGlobalCtrlInfo.stAttemptToUpdateRai, &g_GmmGlobalCtrl.stAttemptToUpdateRai, sizeof(NAS_MML_RAI_STRU));
    pstMsg->stGmmGlobalCtrlInfo.UeInfo_enVoiceDomainFromRegRq   = g_GmmGlobalCtrl.UeInfo.enVoiceDomainFromRegReq;

    PS_MEM_CPY(&pstMsg->stGmmGlobalCtrlInfo.stAllocT3302ValuePlmnWithRat, NAS_GMM_GetAllocT3302ValuePlmnWithRat(),sizeof(pstMsg->stGmmGlobalCtrlInfo.stAllocT3302ValuePlmnWithRat));

    pstMsg->stGmmRauCtrlInfo.ucT3311ExpiredFlg         = g_GmmRauCtrl.ucT3311ExpiredFlg;
    pstMsg->stGmmRauCtrlInfo.ucT3312ExpiredFlg         = g_GmmRauCtrl.ucT3312ExpiredFlg;

    pstMsg->stGmmReqCnfMngInfo.ucCnfMask               = g_GmmReqCnfMng.ucCnfMask;

    pstMsg->stGmmServiceCtrlInfo.ucRetrySrForRelCtrlFlg = g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg;

    pstMsg->stGmmSuspendCtrlInfo.ucNetModeChange        = gstGmmSuspendCtrl.ucNetModeChange;
    pstMsg->stGmmSuspendCtrlInfo.ucPreRat               = gstGmmSuspendCtrl.ucPreRat;
    pstMsg->stGmmSuspendCtrlInfo.ucPreSrvState          = gstGmmSuspendCtrl.ucPreSrvState;
    pstMsg->stGmmSuspendCtrlInfo.ucT3312State           = gstGmmSuspendCtrl.ucT3312State;

    pstMsg->stGmmTimerMngInfo.ulTimerRunMask            = g_GmmTimerMng.ulTimerRunMask;

    pstMsg->stMmlCtxInfo.ucWSysInfoDrxLen               = NAS_MML_GetWSysInfoDrxLen();
    pstMsg->stMmlCtxInfo.ucT3423State                   = NAS_MML_GetT3423Status();
    pstMsg->stMmlCtxInfo.ucPsServiceBufferStatusFlg     = pstConnStatus->ucPsServiceBufferFlg;
    pstMsg->stMmlCtxInfo.ucPsRegStatus                  = NAS_MML_GetSimPsRegStatus();
    pstMsg->stMmlCtxInfo.ucIsTmsiValid                  = (VOS_UINT8)NAS_MML_IsTmsiValid();
    PS_MEM_CPY(&pstMsg->stMmlCtxInfo.stPsLastSuccRai ,NAS_MML_GetPsLastSuccRai(),sizeof(pstMsg->stMmlCtxInfo.stPsLastSuccRai));
    pstMsg->stMmlCtxInfo.enTinType                      = NAS_MML_GetTinType();
    pstMsg->stMmlCtxInfo.enPsUpdateStatus               = NAS_MML_GetPsUpdateStatus();
    pstMsg->stMmlCtxInfo.enMsMode                       = NAS_MML_GetMsMode();
    pstMsg->stMmlCtxInfo.enCurrUtranMode                = NAS_UTRANCTRL_GetCurrUtranMode();
    PS_MEM_CPY(pstMsg->stMmlCtxInfo.astPsBearerContext, NAS_MML_GetPsBearerCtx(), sizeof(pstMsg->stMmlCtxInfo.astPsBearerContext));

    pstMsg->stMmSubLyrShareInfo.GmmShare_ucGsAssociationFlg = g_MmSubLyrShare.GmmShare.ucGsAssociationFlg;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_GMM, pstMsg);

    return;
}


/* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-14, begin */
/*****************************************************************************
 函 数 名  : NAS_GMM_LogPsRegContainDrxInfo
 功能描述  : GMM 更新是否携带Drx参数时需要把消息勾出到trace中
 输入参数  : enPsRegContainDrx - Drx参数携带类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月14日
    作    者   : t00212959
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_LogPsRegContainDrxInfo(
    NAS_MML_PS_REG_CONTAIN_DRX_PARA_ENUM_UINT8    enPsRegContainDrx
)
{
    NAS_GMM_LOG_PS_REG_DRX_INFO_STRU             *pstPsRegContainDrxInfo;

    pstPsRegContainDrxInfo = (NAS_GMM_LOG_PS_REG_DRX_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_GMM,
                             sizeof(NAS_GMM_LOG_PS_REG_DRX_INFO_STRU));

    if ( VOS_NULL_PTR == pstPsRegContainDrxInfo )
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_LogPsRegContainDrxInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstPsRegContainDrxInfo->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstPsRegContainDrxInfo->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstPsRegContainDrxInfo->stMsgHeader.ulSenderPid     = WUEPS_PID_GMM;
    pstPsRegContainDrxInfo->stMsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    pstPsRegContainDrxInfo->stMsgHeader.ulLength        = sizeof(NAS_GMM_LOG_PS_REG_DRX_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPsRegContainDrxInfo->stMsgHeader.ulMsgName       = NAS_GMM_LOG_PS_REG_DRX_INFO_IND;

    pstPsRegContainDrxInfo->enPsRegContainDrx = enPsRegContainDrx;

    DIAG_TraceReport(pstPsRegContainDrxInfo);

    PS_MEM_FREE(WUEPS_PID_GMM, pstPsRegContainDrxInfo);

    return;
}
/* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-14, end */

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, begin */
/*****************************************************************************
 函 数 名  : NAS_GMM_IsCsPsModeAndNetworkI
 功能描述  : 判断是否是A+I模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 是cs ps mode且网络模式为I
             VOS_FALSE - 不是A+I模式
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月18日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsAModeAndNetworkI(VOS_VOID)
{
    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsCombinedSpecProc
 功能描述  : 判断GMM在进行的专有流程是否是联合的rau或联合rau with imsi attach
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - GMM的专有流程是联合rau或联合rau with imsi attach
             VOS_FALSE - GMM的专有流程不是联合rau或联合rau with imsi attach
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月18日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsCombinedSpecProc(VOS_VOID)
{
    NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8   enSpecProc;

    enSpecProc = NAS_GMM_GetSpecProc();

    if ((GMM_RAU_COMBINED == enSpecProc)
     || (GMM_RAU_WITH_IMSI_ATTACH == enSpecProc))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, end */

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_GMM_GetLteInfo
 功能描述  : 获取LTE信息公共接口函数
 输入参数  : ulInfoType
 输出参数  : pstLmmInfo
 返 回 值  : VOS_TRUE:获取成功
              VOS_FALSE:获取失败
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012年12月27日
    作    者   : s46746
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_GMM_GetLteInfo(
    NAS_LMM_INFO_TYPE_ENUM_UINT32       ulInfoType,
    NAS_LMM_INFO_STRU                  *pstLmmInfo
)
{
    /* 平台不支持LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* 调用LNAS提供接口函数，成功返回VOS_OK */
    if (MMC_LMM_SUCC == Nas_GetLteInfo(ulInfoType, pstLmmInfo))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
/*****************************************************************************
 函 数 名  : NAS_GMM_HandleMsRadioCapLteSupportChanged
 功能描述  : MS Radio cap能力中LTE是否支持发生改变的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013年05月09日
    作    者   : s46746
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_GMM_HandleMsRadioCapLteSupportChanged(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    pstConnStatus   = NAS_MML_GetConnStatus();

    /* 如果存在CS业务则直接返回 */
    if (VOS_TRUE == pstConnStatus->ucCsServiceConnStatusFlg)
    {
        return;
    }

    /* 如果正在发起CS业务则启动定时器，业务发起失败依靠定时器触发RAU，
       业务发起成功定时器超时时会直接返回 */
    if ((VOS_TRUE == NAS_MML_GetCsServiceBufferStatusFlg())
     && (VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg))
    {
        Gmm_TimerStart(GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU);

        return;
    }

    if ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState))
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        return;
    }

    if ((GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        Gmm_TimerStart(GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU);
    }

    return;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_GMM_IsAllowedCombinedAttach_GmmRegisteredAttemptingToUpdateMm
 功能描述  : GMM在GmmRegisteredAttemptingToUpdateMm状态判断是否可以进行联合注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE    - 可以发起联合注册
              VOS_FALSE  - 不可以发起联合注册
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月18日
    作    者   : w00167002
    修改内容   : 新生成函数
        TS24.008:t3311超时发起COMBINED RA/LA updating with imsi attach.修改
        以下场景不发起联合ATTACH.

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsAllowedCombinedAttach_GmmRegisteredAttemptingToUpdateMm(VOS_VOID)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo         = VOS_NULL_PTR;

    VOS_UINT8                           ucCsRestrictRegister;

    /* 获取当前的CS受限标识 */
    ucCsRestrictRegister = NAS_MML_GetCsRestrictRegisterFlg();

    /* 获取当前网络模式 */
    pstCampInfo          = NAS_MML_GetCurrCampPlmnInfo();

    /* 当前非网络模式I */
    if ( NAS_MML_NET_MODE_I != pstCampInfo->enNetworkMode )
    {
        return VOS_FALSE;
    }

    /* 当前cs不准许注册 */
    if ( VOS_FALSE == NAS_MML_GetCsAttachAllowFlg() )
    {
        return VOS_FALSE;
    }

    /* 当前注册cs受限 */
    if ( VOS_TRUE == ucCsRestrictRegister )
    {
        return VOS_FALSE;
    }

    /* 当前CS卡无效 */
    if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
    {
        return VOS_FALSE;
    }

    /* CS有业务 */
    if ( GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_LogAuthInfo
 功能描述  : 勾MM的期望的鉴权信息
 输入参数  : VOS_VOID
 输出参数  : ucRcvOpId    : 消息中接受到的OPID
             ucExpectOpId : MM期望的OPID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年08月21日
    作    者   : l65478
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_GMM_LogAuthInfo(
    VOS_UINT8                           ucRcvOpId,
    VOS_UINT8                           ucExpectOpId
)
{
    NAS_GMM_LOG_AUTH_INFO_STRU        *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_GMM_LOG_AUTH_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_GMM,
                                         sizeof(NAS_GMM_LOG_AUTH_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_LogAuthInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(NAS_GMM_LOG_AUTH_INFO_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_GMM_LOG_AUTH_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = GMMOM_LOG_AUTH_INFO_IND;
    pstMsg->ucExpectOpId                = ucExpectOpId;
    pstMsg->ucRcvOpId                   = ucRcvOpId;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_GMM, pstMsg);

    return;
}

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 函 数 名  : NAS_GMM_NwDetachIndRecord
 功能描述  : 记录网络Detach指示事件
 输入参数  : VOS_UINT8  ucDetachType
             VOS_UINT8  ucGmmCause
             VOS_UINT8  ucForceToStandby
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_NwDetachIndRecord(
    VOS_UINT8                           ucDetachType,
    VOS_UINT8                           ucGmmCause,
    VOS_UINT8                           ucForceToStandby
)
{
    NAS_ERR_LOG_NW_DETACH_IND_EVENT_STRU                    stNwDetachIndEvent;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_NW_DETACH_IND);
    ulIsLogRecord = NAS_MML_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_NW_DETACH_IND_EVENT_STRU);

    /* 填充CS注册失败异常信息 */
    PS_MEM_SET(&stNwDetachIndEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stNwDetachIndEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_GMM),
                                      NAS_ERR_LOG_ALM_NW_DETACH_IND,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    NAS_MNTN_OutputPositionInfo(&stNwDetachIndEvent.stPositionInfo);

    stNwDetachIndEvent.ucDetachType         = ucDetachType;
    stNwDetachIndEvent.ucGmmCause           = ucGmmCause;
    stNwDetachIndEvent.ucForceToStandby     = ucForceToStandby;
    stNwDetachIndEvent.ucCurrNetRat         = NAS_MML_GetCurrNetRatType();

    stNwDetachIndEvent.ucOriginalGmmCause = NAS_MML_GetOriginalRejectCause(stNwDetachIndEvent.ucGmmCause);
    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stNwDetachIndEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_MMC_NwDetachIndRecord(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_NW_DETACH_IND,
                           WUEPS_PID_GMM,
                           (VOS_UINT8 *)&stNwDetachIndEvent,
                           sizeof(stNwDetachIndEvent));

    return;
}

#endif

/*****************************************************************************
 函 数 名  : NAS_GMM_IsEnableRelPsSigCon
 功能描述  : gmm 判断是否开启了网络防呆功能
 输入参数  : 无
 输出参数  : 无
 返 回 值  :  是否开启网络防呆功能，TRUE表示开启，FALSE:未开启

 修改历史  :
 1.日    期   : 2014年11月04日
   作    者   : w000281933
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_GMM_IsEnableRelPsSigCon(VOS_VOID)
{
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_GMM_IsEnableRelPsSigCon(): The sim is Test card!");
        return VOS_FALSE;
    }

    return (NAS_MML_GetRelPsSigConFlg());
}

/*****************************************************************************
 函 数 名  : NAS_GMM_GetRelPsSigConCfg_T3340TimerLen
 功能描述  : gmm 在开启网络防呆功能后，获取配置的T3340 的值；
 输入参数  : 无
 输出参数  : 无
 返 回 值  :  配置的T3340 的时长；单位为毫秒；

 修改历史  :
 1.日    期   : 2014年11月04日
   作    者   : w000281933
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_GMM_GetRelPsSigConCfg_T3340TimerLen(VOS_VOID)
{
    VOS_UINT32                          ulTmpT3340timeLen;

    ulTmpT3340timeLen = (NAS_MML_GetRelPsSigConCfg_T3340TimerLen() * NAS_MML_ONE_THOUSAND_MILLISECOND); /* 单位换为毫秒 */

    return ulTmpT3340timeLen;
}

/*lint -restore */

/*****************************************************************************
 函 数 名  : NAS_GMM_IsUeInfoChangeTriggerRau
 功能描述  : UE信息变化是否需要触发RAU
 输入参数  : 无
 输出参数  : 无
 返 回 值  :  VOS_TRUE:需要
              VOS_FALSE:不需要

 修改历史  :
 1.日    期   : 2014年11月04日
   作    者   : w000281933
   修改内容   : 新生成函数
 2.日    期   : 2015年8月13日
   作    者   : l00289540
   修改内容   : User_Exp_Improve修改

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsUeInfoChangeTriggerRau(VOS_VOID)
{
    VOS_INT8                            cVersion;

    cVersion = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS);

#if (FEATURE_ON == FEATURE_LTE)
    /* radio capability与上一次注册时的不同，需要做RAU */
    if (g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs != g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromRegReq)
    {
        return VOS_TRUE;
    }

    if (cVersion >= PS_PTL_VER_R9)
    {
        /* voice domain与上一次注册时的不同，需要做RAU */
        if (g_GmmGlobalCtrl.UeInfo.enVoiceDomainFromRegReq != NAS_MML_GetVoiceDomainPreference())
        {
            return VOS_TRUE;
        }
    }
#endif

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : Gmm_ComConvertRrcEstCnfCauseToMmlRegCause
 功能描述  : Gmm 建链失败原因值转换为MML Reg Fail Cause
 输入参数  : ulRrcEstResult:RRC 建链结果
 输出参数  : penMmlRegFailCause:转换之后的MML Reg fail cause
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月24日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Gmm_ComConvertRrcEstCnfCauseToMmlRegCause(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulRrcEstResult,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penMmlRegFailCause
)
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;

    *penMmlRegFailCause = NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL;
    enCurrUtranMode     = NAS_UTRANCTRL_GetCurrUtranMode();

    if (NAS_MML_NET_RAT_TYPE_WCDMA     == NAS_MML_GetCurrNetRatType())
    {
        if ((NAS_UTRANCTRL_UTRAN_MODE_FDD  == enCurrUtranMode)
         && (RRC_EST_RANDOM_ACCESS_REJECT  == ulRrcEstResult))
        {
            *penMmlRegFailCause = NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL_RANDOM_ACCESS_REJECT;
        }

        if ((NAS_UTRANCTRL_UTRAN_MODE_TDD  == enCurrUtranMode)
         && (RRC_EST_RJ_TIME_OUT           == ulRrcEstResult))
        {
            *penMmlRegFailCause = NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL_RANDOM_ACCESS_REJECT;
        }
    }

    return;
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

