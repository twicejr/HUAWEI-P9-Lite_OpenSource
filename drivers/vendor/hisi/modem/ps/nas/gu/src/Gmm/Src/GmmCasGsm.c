/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : GmmCasGsm.c
  Author       : Roger Leo
  Version      : V200R001
  Date         : 2005-08-25
  Description  : 该C文件给出了GmmCasGsm模块的实现
  Function List:
        ---
        ---
        ---
  History      :
  1. Date:2005-08-25
     Author: Roger Leo
     Modification:update
  2. s46746 2006-03-08 根据问题单A32D02368修改
  3. l40632 2006-04-30 根据问题单A32D03550修改
  4. x51137 2006/4/28 A32D02889
  5. s46746 2006-05-08 根据问题单A32D03487修改
  6.日    期   : 2006年9月9日
    作    者   : sunxibo id:46746
    修改内容   : 根据问题单号：A32D05653
  7.日    期   : 2006年9月11日
    作    者   : sunxibo id:46746
    修改内容   : 根据问题单号：A32D05743
  8.日    期   : 2006年10月9日
    作    者   : s46746
    修改内容   : 根据问题单号：A32D05744
  9.日    期   : 2006年11月1日
    作    者   : s46746
    修改内容   : 根据问题单号：A32D06572
 10.日    期   : 2006年11月8日
    作    者   : s46746
    修改内容   : 问题单号:A32D06867
 11.日    期   : 2007年01月04日
    作    者   : s46746
    修改内容   : 根据问题单号：A32D08236
 12.日    期   : 2007年01月13日
    作    者   : s46746
    修改内容   : 根据问题单号：A32D08326
 13.日    期   : 2007年3月30日
    作    者   : s46746
    修改内容   : 问题单号:A32D09854
 14.日    期   : 2007年4月25日
    作    者   : s46746
    修改内容   : 问题单号:A32D09766
 15.日    期   : 2007年05月11日
    作    者   : luojian id:60022475
    修改内容   : 问题单号:A32D10713
 16.日    期   : 2007年5月18日
    作    者   : s46746
    修改内容   : 问题单号:A32D10990
 17.日    期   : 2007年06月16日
    作    者   : luojian id:60022475
    修改内容   : 根据问题单号：A32D11635,gas上报GPRS RESUME FAILURE时,仍然通知
                 RABM 恢复成功,如果存在PDP激活时,发起RAU,如果在这个RAU过程中系
                 统消息指示RAI发生改变就不再发起RAU.
 18.日    期   : 2007年6月25日
    作    者   : s46746
    修改内容   : 问题单号:A32D11895,GPRS resume failure后没必要停止定时器T3302
 19.日    期   : 2007年09月10日
    作    者   : s46746
    修改内容   : 根据问题单号：A32D12829
 20.日    期   : 2007年10月13日
    作    者   : s46746
    修改内容   : 根据问题单号：A32D13060
 21.日    期   : 2007年11月12日
    作    者   : l39007
    修改内容   : 根据问题单A32D13044,GSM网络,ATTACH失败5次,通知MM发起一次LAU
                 的时机更改为在GMM回了ATTACH COMPLETE之后
 22.日    期   : 2007年11月20日
    作    者   : s46746
    修改内容   : 根据问题单号：A32D13510,在搜网状态指示接入层P/TMSI
 23.日    期   : 2007年11月22日
    作    者   : s46746
    修改内容   : 根据问题单号：A32D13475,修改异系统改变后指派的old TLLI和开机加密密钥为全0问题
 24.日    期   : 2007年05月11日
    作    者   : luojian id:60022475
    修改内容   : 问题单号: A32D13862
 25.日    期   : 2007年12月14日
    作    者   : s46746
    修改内容   : 问题单A32D13638，保证进行RAU之前不向网侧发送其它数据，并且RAU不成功，不恢复层2
 26.日    期   : 2007年12月28日
    作    者   : s46746
    修改内容   : 根据问题单号：A32D13954,修改GMM在2G3过程中缓存消息机制
 27.日    期   : 2007年12月28日
    作    者   : s46746
    修改内容   : 根据问题单号：A32D13987,RAU之后没有清除SPEC标志
 28.日    期   : 2008年5月2日
    作    者   : s46746
    修改内容   : 根据问题单号：AT2D03268,没有判断小区是否改变标志，直接进行了RAU或Attach
 29.日    期   : 2008年7月28日
    作    者   : s46746
    修改内容   : 问题单号:AT2D03915,修改联合RAU类型,CS如果已经单独LAU成功，需要
                 发起with IMSI Attach的RAU
 30.日    期   : 2008年9月26日
    作    者   : x00115505
    修改内容   : 问题单号:AT2D05431
 31.日    期   : 2008年10月16日
    作    者   : l00130025
    修改内容   : 根据问题单号：AT2D6236:Syscfg处理关机状态下频段设置
 32.日    期   : 2008年10月30日
    作    者   : x00115505
    修改内容   : 根据问题单号：AT2D06422
 33.日    期   : 2009年01月15日
    作    者   : l00130025
    修改内容   : 问题单号:AT2D07018,LAU或RAU过程中搜网和SYSCFG设置,发起底层释放链接的操作
 34.日    期   : 2009年6月30日
    作    者   : s46746
    修改内容   : AT2D12561,3G2情形GPRS下未启动加密，NAS指派层2加密算法后，层2对上行数据进行了加密
 35.日    期   : 2009年7月23日
    作    者   : s46746
    修改内容   : 根据问题单号：AT2D12878，GSM下HPLMN搜索时接收到GPRS寻呼或PDP激活(W下PDP激活相同处理)请求需要能及时响应
 36.日    期   : 2009年08月19日
    作    者   : x00115505
    修改内容   : 问题单号:AT2D13829,TLLI维护错误
 37.日    期   : 2009年9月7日
    作    者   : s46746
    修改内容   : 根据问题单号：AT2D14311，出服务区后，GMM存在连接时先进行了连接释放，会导致服务状态临时更新为Normal service
 38.日    期   : 2009年12月7日
    作    者   : s46746
    修改内容   : 问题单号：AT2D15718,CS LAU失败四次搜网修改为CS LAU失败四次PS RAU/ATTACH失败五次后搜网
 39.日    期   : 2009年12月24日
    作    者   : x00115505
    修改内容   : 问题单号:AT2D16025,2G下，detach过程中接入阻塞，detach失败
 40.日    期   : 2010年04月09日
    作    者   : x00115505
    修改内容   : 问题单号:AT2D18182,五次Rau失败后，T3302未超时，在相同位置区发起了Rau
 41.日    期   : 2010年04月11
    作    者   : s46746
    修改内容   : 问题单号:AT2D18123,CS流程结束，GAS指示GPRS恢复失败，由之前存在PDP才发起RAU修改为处于正常服务状态就发起RAU
************************************************************************/

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasComm.h"
#include "GmmCasMain.h"
#include "GmmCasSuspend.h"
#include "GmmCasSend.h"
#include "GmmCasGsm.h"
#include "GmmMmInterface.h"
#include "GmmExt.h"
#include "NasGmmSndOm.h"
/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-23, begin */
#include "NasUtranCtrlInterface.h"
/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-23, end */
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
#define    THIS_FILE_ID        PS_FILE_ID_GMM_CASGSM_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/

extern VOS_VOID Gmm_RcvRoutingAreaUpdateRejectMsg_AttachFlg_Handling(VOS_VOID);


/*lint -save -e958 */

/*****************************************************************************
 Prototype      : GMM_CasCellS0E45
 Description    :
                  接收ID_LL_GMM_STATUS_IND消息处理
                  HSS 4100 V200R001 新增
                  接收到LLC上报状态信息ID_LL_GMM_STATUS_IND的处理

 Input          : VOS_VOID*     pRcvMsg     入口消息指针
 Output         :
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_CasCellS0E45(VOS_VOID *pRcvMsg)
{
    LL_GMM_STATUS_IND_MSG   *pStatusInd;

    if ((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
        || (0x20 == (g_GmmGlobalCtrl.ucState & 0xF0)))
    {
        /* GSM模式处理过程 */
        pStatusInd = (LL_GMM_STATUS_IND_MSG*)pRcvMsg;

        /* 检查TLLI值 */
        if (gstGmmCasGlobalCtrl.ulTLLI != pStatusInd->stLlGmmStatusInd.ulTlli)
        {
            #ifdef __PS_WIN32_RECUR__
            if ((pStatusInd->stLlGmmStatusInd.ulTlli & 0xf0000000) != 0x70000000)
            {
                GMM_AssignSysTlli();                                                /* 同步更新LLC的new TLLI */
            }
            #else
                GMM_AssignSysTlli();                                                /* 同步更新LLC的new TLLI */
            #endif

        }

        if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            /*如果层二还没有挂起，需要挂起*/
            if (GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
            {
                GMM_SndLlcSuspendReq();
            }

            /*在GMM_ROUTING_AREA_UPDATING_INITIATED状态，没有置GMM_SUSPEND_LLC_FOR_RAU*/
            if (GMM_SUSPEND_LLC_FOR_RAU != (GMM_SUSPEND_LLC_FOR_RAU & gstGmmCasGlobalCtrl.ucSuspendLlcCause))
            {
                gstGmmCasGlobalCtrl.ucSuspendLlcCause |= GMM_SUSPEND_LLC_FOR_RAU;
            }
        }
        /* 分析ucCause原因值 */
        GMM_ExecLlgmmStatusIndCause(pStatusInd->stLlGmmStatusInd.usCause);
    }

    return;
}
/*****************************************************************************
 Prototype      :
 Description    : 接收GMMRABM_ROUTING_AREA_UPDATE_RSP消息处理
                 在GSM接入模式下，收到该消息后发送RAU complete消息
                 在消息挂起模式下，2G到3G切换完成后要发送一条RAU指示到RABM
                 在WCDMA接入模式下，不发送RAU指示到RABM，也就不会收到该消息
                  HSS 4100 V200R001 新增

 Input          : VOS_VOID*     pRcvMsg     入口消息指针
 Output         :
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
  2.日    期   : 2006年11月1日
    作    者   : s46746
    修改内容   : 根据问题单号：A32D06572
  3.日    期   : 2006年11月8日
    作    者   : s46746
    修改内容   : 问题单号:A32D06867
  4.日    期   : 2007年11月12日
    作    者   : l39007
    修改内容   : 问题单号:A32D13044
  4.日    期   : 2008年11月27日
    作    者   : L65478
    修改内容   : 问题单号:A32D06903
*****************************************************************************/
VOS_VOID NAS_GMM_RcvGmmRabmRoutingAreaUpdateRsp(VOS_VOID *pRcvMsg)
{
    VOS_UINT8                                ucNum = 0;
    GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG     *pRabmRauRspMsg;

    Gmm_TimerStop(GMM_TIMER_RAU_RSP);

    gstGmmCasGlobalCtrl.ucRabmRauRspRcvdFlg = VOS_TRUE;

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        return;
    }
    pRabmRauRspMsg = (GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG*)pRcvMsg;

    /* 保存消息中NPDU的内容 */
    if (GMM_RABM_NPDU_VALID == pRabmRauRspMsg->ucNpduValidFlg)
    {
        g_GmmRauCtrl.ucNpduCnt = pRabmRauRspMsg->aucRecvNPDUNumListIE[1];
        g_GmmDownLinkNpduBake.ucNpduCnt = pRabmRauRspMsg->aucRecvNPDUNumListIE[1];
        for (ucNum=0; ucNum<g_GmmRauCtrl.ucNpduCnt; ucNum++)
        {
            g_GmmRauCtrl.aucNpduNum[ucNum] =
                pRabmRauRspMsg->aucRecvNPDUNumListIE[ucNum+2];
            g_GmmDownLinkNpduBake.aucNpduNum[ucNum] =
                pRabmRauRspMsg->aucRecvNPDUNumListIE[ucNum+2];
        }
    }
    else
    {
        g_GmmRauCtrl.ucNpduCnt = 0;     /* UE侧NPDU无有效数据 */
        g_GmmDownLinkNpduBake.ucNpduCnt = 0;
    }

    /* 不需要等待WRR的回复消息，或者已经收到WRR的回复消息，进行RAU流程结束的相应处理 */
    if (   (VOS_FALSE == g_GmmInterRatInfoCtrl.ucRauCmpWaitInterRatCnfMsg)
        || (VOS_TRUE == g_GmmInterRatInfoCtrl.ucInterRatCnfMsgRcvdFlg))
    {
        NAS_GMM_RauCompleteHandling();
    }

    return;
}
/*****************************************************************************
 Prototype      : GMM_RcvGasPagingInd
 Description    :
                  接收GRRMM_PAGING_IND消息入口处理
                  HSS 4100 V200R001 新增

 Input          : VOS_VOID*     pMsg     入口消息指针
 Output         :
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_RcvGasPagingInd(VOS_VOID *pMsg)
{
    GRRMM_PAGING_IND_ST     *pIndMsg;

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        GMM_LOG_WARN("GMM_RcvGasPagingInd():Warning: message only use for GSM");
        return;
    }

    pIndMsg = (GRRMM_PAGING_IND_ST*)pMsg;
    /* 判断寻呼发起的域 */
    if (GAS_PAGING_CS == pIndMsg->ucPagingType)
    {/* CS寻呼 */
        return;                                                                 /* 不处理，直接结束 */
    }

    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_DEREGISTERED_INITIATED:
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
       GMM_RcvGsmPagingAtDeregInit(pIndMsg);
       break;

    case GMM_ROUTING_AREA_UPDATING_INITIATED:
       GMM_RcvGsmPagingAtRauInit(pIndMsg);
       break;

    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
       GMM_RcvGsmPagingAtRegNmlServ(pIndMsg);
       break;
    case GMM_REGISTERED_PLMN_SEARCH:
        GMM_RcvGsmPaging_RegPlmnSrch(pIndMsg);
        break;
    default:
       break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_GsmAccessBarredProcess
 功能描述  : GSM模式下系统信息中指示当前的小区接入禁止时的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月21日
    作    者   : l65478
    修改内容   : 新生成函数
  2.日    期   : 2010年8月31日
    作    者   : l65478
    修改内容   : 问题单号:DTS2010082300491,GSM禁止接入时，并且GSM ONLY开机，进入限制服务
  3.日    期   : 2011年07月13日
    作    者   : w00166186
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  4.日    期   : 2012年3月3日
    作    者   : z00161729
    修改内容   : V7R1 C50 支持ISR修改
  5.日    期   : 2013年8月7日
    作    者   : w00167002
    修改内容   : DTS2013080207367:在CS only时候，用户发起PDP激活，网络模式I时候，
                 会触发联合注册.用户发起PDP去激活，会导致PS域的去注册。收到网侧
                 的去注册成功后需要通知MM，否则MM当前在NORMAL SERVICE状态，不
                 触发T3212定时器的启动，长时间可能导致丢寻呼.
  6.日    期   : 2013年10月05日
    作    者   : l65478
    修改内容   : DTS2013092509860:GPRS detach过程被BG搜索终止后,GMM又自动发起了注册
*****************************************************************************/
VOS_UINT32 NAS_GMM_GsmAccessBarredProcess(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    enRatType;


    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
    enRatType   = NAS_MML_GetCurrNetRatType();

    if ( (VOS_TRUE == NAS_MML_GetGsmForbidFlg())
      && (NAS_MML_NET_RAT_TYPE_GSM == enRatType))
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
        return VOS_ERR;
    }
    if ((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || ((0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
        && (GMM_NULL != g_GmmGlobalCtrl.ucState)
        && (GMM_DEREGISTERED_NO_IMSI != g_GmmGlobalCtrl.ucState)))
    {                                                                       /* PS域没有注册                             */
        Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
        return VOS_ERR;
    }
    else if (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerStop(GMM_TIMER_T3321);                                     /* 停T3321                                  */
        Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);

        /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();
        }
        return VOS_ERR;
    }
    else if (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerStop(GMM_TIMER_T3321);                                     /* 停T3321                                  */
        NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
        Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);

        Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ALL);                       /* 去指配TLLI，释放LLC层数据 */
        Gmm_TimerStop(GMM_TIMER_T3314);
        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;
        gstGmmCasGlobalCtrl.ulReadyTimerValue = 44000;


#if (FEATURE_LTE == FEATURE_ON)
        if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
        {
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
        }
#endif
        Gmm_TimerStop(GMM_TIMER_T3312);
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
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
            if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
            {
                NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
            }
            NAS_GMM_SndMmcMmDetachInfo();
        }
        else
        {
            /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
            NAS_GMM_SndMmGprsDetachComplete();
        }

        return VOS_ERR;
    }
    else if ((GMM_NULL != g_GmmGlobalCtrl.ucState)
        && (GMM_DEREGISTERED_NO_IMSI != g_GmmGlobalCtrl.ucState))
    {
        Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);
        return VOS_ERR;
    }
    else
    {
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_GasSysInfoPreCheck
 功能描述  : 预处理GSM的系统信息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32 VOS_ERR:需要立刻返回
                        VOS_OK:需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月21日
    作    者   : l65478
    修改内容   : 新生成函数
  2.日    期   : 2010年8月31日
    作    者   : l65478
    修改内容   : 问题单号:DTS2010082300491,GSM禁止接入时，并且GSM ONLY开机，进入限制服务
  3.日    期   : 2011年7月13日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII阶段调整，向RABM指示RAB是否需要重建
  4.日    期   : 2011年7月13日
    作    者   : l00130025
    修改内容   : V7R1 PhaseII阶段调整，删除UserDelay标志，由MMC处理
  5.日    期   : 2011年12月8日
    作    者   : s46746
    修改内容   : 问题单号：DTS2011111603445,接收到系统消息而且层2已经指派后才能恢复RABM
  6.日    期   : 2012年12月13日
    作    者   : w00176964
    修改内容   : 问题单号：消息消息AC信息变量替换
  7.日    期   : 2014年1月26日
    作    者   : w00242748
    修改内容   : DTS2014011800247:修正GMM在ACC BAR时，GMM给MMC发送的PS域注册原因值
*****************************************************************************/
VOS_UINT32 NAS_GMM_GasSysInfoPreCheck(VOS_VOID *pMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST  *pSysInfoMsg;
    VOS_UINT32                  ulResult;
    VOS_UINT8                           ucSimPsRegStatus;

    pSysInfoMsg = (MMCGMM_GSM_SYS_INFO_IND_ST *)pMsg;

    Gmm_SndSmSysInfoInd(pSysInfoMsg->ucSgsnRelease);

    gstGmmCasGlobalCtrl.ucCellReselFlg = VOS_FALSE;

    ucSimPsRegStatus = NAS_MML_GetSimPsRegStatus();

    if ( (VOS_TRUE == ucSimPsRegStatus)
      && (MMC_GMM_NO_FORBIDDEN == pSysInfoMsg->ulForbiddenFlg) )
    {
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
        if ((RRC_NAS_ACCESS_RESTRICTION_NORMAL_SERVICE  == pSysInfoMsg->unAcInfo.ucRestrictType)
         || (RRC_NAS_ACCESS_RESTRICTION_ALL_SERVICE     == pSysInfoMsg->unAcInfo.ucRestrictType))
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */
        {
            GMM_BufferMsgDump();

            ulResult = NAS_GMM_GsmAccessBarredProcess();
            if (VOS_ERR == ulResult)
            {

                NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);

                return VOS_ERR;
            }
        }
    }

    /* 分析接收消息，修改参数标志 */
    if (GMM_FAILURE == GMM_SaveGsmSysInfoIndMsgPara(pSysInfoMsg))
    {
        GMM_LOG_NORM("GMM_RcvGasSysInfoInd():Normal: Sys info handle finish in GMM_SaveGsmSysInfoIndMsgPara.");
        return VOS_ERR;
    }

    if ((GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
        || (GMM_DEREGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState))
    {
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_PTMSI_RAI);
    }

    if ((GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
        && (GMM_TRUE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg))
    {
        if(GMM_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
        {
            g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_FALSE;
        }
        Gmm_ComStaChg(GMM_REGISTERED_NO_CELL_AVAILABLE);
        g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_TRUE;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_GasSysInfoDistribute
 功能描述  : 根据当前的状态分发GSM系统信息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月21日
    作    者   : l65478
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_GasSysInfoDistribute(VOS_VOID *pMsg)
{
    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_DEREGISTERED_NORMAL_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_PLMN_SEARCH:
       GMM_CasCellS1E49(pMsg);
       break;

    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
       GMM_CasCellS4E49(pMsg);
       break;

    case GMM_REGISTERED_INITIATED:
       GMM_CasCellS8E49(pMsg);
       break;

    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
       GMM_CasCellS9E49(pMsg);
       break;

    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_PLMN_SEARCH:
       GMM_CasCellS10E49(pMsg);
       break;

    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
       GMM_CasCellS11E49(pMsg);
       break;

    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
       NAS_GMM_EnterCovery(pMsg);
       break;

    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
    case GMM_DEREGISTERED_INITIATED:
       GMM_CasCellS18E49(pMsg);
       break;

    case GMM_ROUTING_AREA_UPDATING_INITIATED:
       GMM_CasCellS19E49(pMsg);
       break;
    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
       GMM_RcvGasSysInfoInd_SuspWaitSys(pMsg);
       break;
    default:
       break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : GMM_RcvGasSysInfoInd
 功能描述  : 接收MMCGMM_GSM_SYS_INFO_IND消息入口
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月12日
    作    者   : f62575
    修改内容   : 新生成函数
  2.日    期   : 2009年01月15日
    作    者   : l00130025
    修改内容   : 问题单号:AT2D07018,LAU或RAU过程中搜网和SYSCFG设置,发起底层释放链接的操作
  3.日    期   : 2009年05月23日
    作    者   : L65478
    修改内容   : 问题单号:AT2D06770,RAU失败，因为GRM建链的原因是DATA，实际应该是信令
  4.日    期   : 2009年07月23日
    作    者   : L65478
    修改内容   : 问题单号:AT2D13173,GMM在收到系统信息后，给MMC发送了NO SERVICE，导致MMC启动了搜网定时器
  5.日    期   : 2010年4月12日
    作    者   : l65478
    修改内容   : AT2D18389,在初始小区更新时，GMM应该通知LLC发送NULL帧
  6.日    期   : 2010年8月14日
    作    者   : s46746
    修改内容   : DTS2010073001405,G2W异系统重选后，不向层2发送去指派而是挂起层2
  7.日    期   : 2010年9月09日
    作    者   : l65478
    修改内容   : DTS2010090302562,PDP激活过程中发生重选，PDP激活事件比标杆慢
  8.日    期   : 2010年10月29日
    作    者   : l00167671/罗开辉
    修改内容   : 问题单号：DTS2010100802035,删除多余的判断条件
  9.日    期   : 2010年11月18日
    作    者   : o00132663
    修改内容   : DTS2010111800285,G下长时间通话过程中T3312超时，电话释放后，第一次RAU失败
  10.日    期   : 2011年03月3日
    作    者   : f00179208
    修改内容   : 问题单号：DTS2011022800037，G下ping包，然后打电话，切换到W失败后多次回退到G，挂断电话.ping包比其他场景恢复慢
  11.日    期  : 2011年7月25日
     作    者  : h44270
     修改内容  : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  12.日    期  : 2011年12月8日
     作    者  : s46746
     修改内容  : 问题单号：DTS2011111603445,接收到系统消息而且层2已经指派后才能恢复RABM
  13.日    期   : 2012年1月9日
     作    者   : l00130025
     修改内容   : DTS2011122900476,调整对缓存的Gsm系统消息的处理
  14.日    期   : 2012年2月15日
     作    者   : w00166186
     修改内容   : CSFB&PPAC&ETWS&ISR 开发
  15.日    期   : 2012年3月15日
     作    者   : z00161729
     修改内容   : ISR 开发修改
  16.日    期   : 2012年4月17日
     作    者   : z00161729
     修改内容  : DTS2012041402264：L小区下发起CS语音业务，通过重定向CS Fallback到W小区。激活PDP后释放CS语音，未上系统消息，UE不会发起联合RAU
  17.日    期   : 2012年10月16日
     作    者   : z00161729
     修改内容   : DTS2012101503609,网络模式II，L异系统到G,rai未改变isr未激活不做rau，
                  原因第一条系统消息缓存不处理将gstGmmSuspendCtrl.ucPreRat改为g，lau结束gprs
                  resume后收到系统消息已判断不出是异系统，rai未改变认为无需rau
 18.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : NAS_MML_GetPsRestrictNormalServiceFlg修改函数名
 19.日    期   : 2012年12月22日
    作    者   : l65478
    修改内容   : DTS2012122103936 PS可以发起注册时才需要缓存系统信息
 20.日    期   : 2012年12月27日
    作    者   : l65478
    修改内容   : DTS2012122702544 GCF42.4.1.2测试失败
 21.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
 22.日    期   : 2014年10月22日
    作    者   : z00161729
    修改内容   : DTS2014102109190:勾gmm和mm的全局变量，增加可维可测信息
 23.日    期   : 2014年12月25日
    作    者   : w00167002
    修改内容   : DTS2014122201960:在L下SRVCC HO到G再HO到W,RABM触发重建，导致立即
                 触发RAU，后续收到系统消息又再次发起RAU,导致网络REL了链路，导致
                 掉话。修改为在HO后，启动保护定时器等系统消息
 24.日    期   : 2015年6月11日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID GMM_RcvGasSysInfoInd(VOS_VOID *pMsg)
{
    VOS_UINT32                          ulRestul;
    VOS_UINT8                           ucSimPsRegStatus;

    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus;

    VOS_UINT8                           ucPsAttachAllowFlg;

    MMCGMM_GSM_SYS_INFO_IND_ST         *pSysInfo;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatuChgNeedRegFlg;
    VOS_UINT32                          ulIsNeedDeactiveIsrFlg;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetType;

    pstRplmnCfgInfo           = NAS_MML_GetRplmnCfg();
    enCurrNetType             = NAS_MML_GetCurrNetRatType();
    ulT3423StatuChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                 NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    pstConnStatus       = NAS_MML_GetConnStatus();

    NAS_GMM_LogGmmCtxInfo();

    /* 停HO等待系统消息定时器 */
    Gmm_TimerStop(GMM_TIMER_HO_WAIT_SYSINFO);

    /* 如果CS正在建立连接或者连接已经建立成功 */
    pSysInfo           = (MMCGMM_GSM_SYS_INFO_IND_ST *)pMsg;
    ucPsAttachAllowFlg = NAS_MML_GetPsAttachAllowFlg();

    /* PS可以发起注册时才需要缓存系统信息 */
    if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
     && (0 != pSysInfo->ucGprsSupportInd)
     && (MMCGMM_GSM_NO_FORBIDDEN == pSysInfo->ulForbiddenFlg)
     && (VOS_TRUE  == ucPsAttachAllowFlg))
    {
        if (VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg)
        {
            /* RR连接不存在表示CS正在建立连接,此时缓存系统消息 */
            if (VOS_FALSE == pstConnStatus->ucRrcStatusFlg)
            {
                NAS_GMM_SaveGsmSysInfo((MMCGMM_GSM_SYS_INFO_IND_ST*)pMsg);
            }
            return;
        }
    }

#if (FEATURE_ON == FEATURE_LTE)
    if (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
    {
        /* L下丢网，搜网到GU后，需要判断如果有ISR激活后激活的pdp上下文，需要去激活ISR*/
        ulIsNeedDeactiveIsrFlg = NAS_GMM_IsNeedDeactiveIsr_InterSys(gstGmmSuspendCtrl.ucPreRat, enCurrNetType, MMC_SUSPEND_CAUSE_BUTT);

        if (VOS_TRUE == ulIsNeedDeactiveIsrFlg)
        {
            NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_GUTI, pstRplmnCfgInfo->aucLastImsi);

            /* ISR去激活，需要更新pdp激活是在ISR激活前激活的 */
            NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
        }
    }
#endif

    ulRestul = NAS_GMM_GasSysInfoPreCheck(pMsg);

    if (VOS_ERR == ulRestul)
    {
        /* 系统消息处理后，释放缓存的系统消息 */
        NAS_GMM_FreeGsmSysInfo();

        gstGmmSuspendCtrl.ucPreRat = NAS_MML_NET_RAT_TYPE_GSM;
        return;
    }

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {
        /*  suspend过程中收到T3312超时，若GPRS NOT SUPPORT,不会再进入suspend的处理，转换为expiredFlag */
        if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
        {
            g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;
            gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
        }
    }

    /* 重选到PS被BARRED的小区,在网络模式I,并且T3312超时 */
    if (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
    {
        /*  suspend过程中收到T3312超时，若PS barred,不会再进入suspend的处理，转换为expiredFlag */
        if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
        {
            g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;
            gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
        }

        if ((VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
          && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);
        }
#if (FEATURE_ON == FEATURE_LTE)
        else if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
              && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
              && (VOS_TRUE == ulT3423StatuChgNeedRegFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3412OrT3423_EXPIRED);
        }
        else
        {
        }
#endif
    }

    NAS_GMM_GasSysInfoDistribute(pMsg);

    /* 系统消息处理后，释放缓存的系统消息 */
    NAS_GMM_FreeGsmSysInfo();

    gstGmmSuspendCtrl.ucPreRat = NAS_MML_NET_RAT_TYPE_GSM;

    if ((GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState)
        && (GMM_ROUTING_AREA_UPDATING_INITIATED != g_GmmGlobalCtrl.ucState))
    {
        if (GMM_TRUE == gstGmmCasGlobalCtrl.ucCellUpdateFlg)
        {
            NAS_GMM_InitCellUpdate_RcvSysInfo(GMM_FALSE);                                               /* 小区更新 */
            gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        }
    }

    /*  获取SIM卡PS是否有效标志 */
    ucSimPsRegStatus = NAS_MML_GetSimPsRegStatus();

    if (VOS_TRUE != ucSimPsRegStatus)
    {
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;
        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
        return;
    }

    /*收到系统消息，可能是小区重选结束，也可能是out of service之后，重新搜到网
      或者是3G重选到2G，或者是CS业务在3G被释放，只有RAI不改变，并且是前面挂起过层2才向层二指示resume*/
    if (GMM_NOT_SUSPEND_LLC != gstGmmCasGlobalCtrl.ucSuspendLlcCause)
    {
        if (GMM_SUSPEND_LLC_FOR_RAU != (GMM_SUSPEND_LLC_FOR_RAU & gstGmmCasGlobalCtrl.ucSuspendLlcCause))
        {
            GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_ALL);
            gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_NOT_SUSPEND_LLC;
        }
        else
        {
            gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_SUSPEND_LLC_FOR_RAU;
        }
    }

    /* 收到G模系统消息, 指示RABM当前系统模式, 根据是否支持GPRS, 挂起或恢复RABM */
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    if ((VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
     || (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
     || (GMM_FALSE == gstGmmCasGlobalCtrl.ucTlliAssignFlg))
    {
        /* 不支持GPRS、PS bar或者没有指派层2, 挂起RABM, bRatChangeFlg为FALSE
           没有指派层2时如果不挂起RABM，RABM会向SN发送数据，SN会发送到LLC，
           而LLC在未指派情况下接收到数据会释放内存导致解除流控,后续数传小包会将消息队列灌满 */
        NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_GSM,
                                    VOS_FALSE,
                                    VOS_TRUE,
                                    VOS_TRUE);
    }
    else
    {
        /* 支持GPRS, 恢复RABM, bRatChangeFlg为FALSE */
        NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_GSM,
                                    VOS_FALSE,
                                    VOS_FALSE,
                                    VOS_TRUE);
    }

    return;
}
/*****************************************************************************
 Prototype      : GMM_CasCellS1E49
 Description    :
                  HSS 4100 V200R001 新增
                  在GMM_DEREGISTERED_NORMAL_SERVICE状态，
                  消息MMCGMM_GAS_SYS_INFO_IND(GSM ONLY)处理
 Input          : VOS_VOID*     pRcvMsg     入口消息指针
 Output         :
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
  2. 日    期   : 2010年9月9日
     作    者   : s46746
     修改内容   : 根据问题单号：DTS2010090600355，高优先级列表搜索时，CS ONLY下仍然需要能触发PS Attach
  3. 日    期   : 2010年12月24日
     作    者   : s46746
     修改内容   : 根据问题单号：DTS2010121400435，五次联合注册失败后，只进行了一次CS注册
  4. 日    期   : 2011年7月14日
     作    者   : h44270
     修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  5. 日    期   : 2011年07月29日
     作    者   : L65478
     修改内容   : 根据问题单号：DTS2011072503161,CS ONLY在重选过程中,发起PDP激活
  6. 日    期   : 2011年04月02日
     作    者   : x00180552
     修改内容   : 根据问题单号：DTS2011040600327,CS ONLY紧急驻留下,发起PDP激活
  7. 日    期   : 2012年1月30日
     作    者   : l00130025
     修改内容   : DTS2012010500368,调用同步接口VOS_GetRelTmRemainTimehTimer时没有判断hTimer是否为0，与定时器异步消息冲突导致异常打印
  8. 日    期   : 2012年08月24日
     作    者   : m00217266
     修改内容   : 修改Gmm_SndSmEstablishCnf接口，添加原因值
  9.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
  10.日    期   : 2016年1月26日
     作    者   : z00359541
     修改内容   : DTS2016012302336:周期RAU被用户指定搜打断，后续搜到同一网络要能发起注册
*****************************************************************************/
VOS_VOID GMM_CasCellS1E49(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST         *pSysInfo;
    VOS_UINT8                           ucLaiChgFlg;
    VOS_UINT8                           ucRaiChgFlg;

    pSysInfo    = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucLaiChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg;
    ucRaiChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;

    if (VOS_TRUE != NAS_MML_GetSimPsRegStatus())
    {                                                                           /* 原来SIM无效                              */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */

        GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NO_IMSI);

        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvMmcSysInfoInd_DeregNmlServ:NORMAL: STATUS IS GMM_DEREGISTERED_NO_IMSI");
        return;
    }

    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        if(MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                    /* 调用状态的公共处理                       */
        }
        else
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                     /* 调用状态的公共处理                       */
        }
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcSysInfoInd_DeregNmlServ:WARNING: Not allow Attach");

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);


        /* 此时可能有缓冲的SM注册请求消息 */
        GMM_BufferMsgResume();

        return;
    }

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        if ((GMM_DEREGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
            && (GMM_FALSE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg))
        {                                                                       /* 前一个小区也不支持GPRS                   */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcSysInfoInd_DeregNmlServ:WARNING: Not support GPRS and No cell available");
            NAS_GMM_CnfSmNotAttach(GMM_SM_CAUSE_GPRS_NOT_SUPPORT);
            NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);
            return;
        }
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* 调用状态的公共处理                       */


        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* A+I                                      */

            if (GMM_FALSE == ucLaiChgFlg)
            {                                                                   /* LA没变                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* 通知MM进行LU                             */
            }
        }

        NAS_GMM_CnfSmNotAttach(GMM_SM_CAUSE_GPRS_NOT_SUPPORT);


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* 在forbidden列表中                        */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                         /* 调用对禁止列表的操作                     */

        NAS_GMM_CnfSmNotAttach(GMM_SM_CAUSE_FORBID_LA);

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);

    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA改变                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;                                  /* Attach attempt counter清0                */
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* 进行Attach                               */
    }
    else
    {                                                                           /* 小区改变                                 */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        NAS_GMM_HandleModeANOIWhenDeregister();
    }

    return;
}
/*****************************************************************************
 Prototype      : GMM_CasCellS4E49
 Description    :
                  HSS 4100 V200R001 新增
                  在GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH状态，
                  消息MMCGMM_GAS_SYS_INFO_IND(GSM ONLY)处理
 Input          : VOS_VOID*     pRcvMsg     入口消息指针
 Output         :
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
  2.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  3.日    期   : 2011年05月13日
    作    者   : h44270
    修改内容   : 根据问题单号：DTS2011051203553，在ATTACH过程中发生重选，异系统RAi相同时，GMM状态不正确，导致业务不可用
  4.日    期   : 2011年11月8日
    作    者   : s46746
    修改内容   : V7R1 PhaseII阶段解决关机慢问题
  5.日    期   : 2011年12月02日
    作    者   : w00166186
    修改内容   : DTS2011112804542,联合注册失败5此后，MM不停注册
  6.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
  7.日    期   : 2013年9月29日
    作    者   : w00242748
    修改内容   : DTS2013092302598:手动搜网，L下成功驻留，CSFB到W下，位置区变化，LAU/RAU建联失败(5次)，
                 搜网回原小区，继续进行联合RAU失败，MM单独LAU失败，死循环，MM ATTEMPT COUNTER无限增加
  8.日    期   : 2014年04月08日
    作    者   : s00217060
    修改内容   : DTS2014040901544:PS域注册被拒#111,网络带的T3302定时器时长为0，链接释放再收到系统消息时，UE一直发起ATTACH
  9.日    期   : 2016年1月26日
    作    者   : z00359541
    修改内容   : DTS2016012302336:周期RAU被用户指定搜打断，后续搜到同一网络要能发起注册
*****************************************************************************/
VOS_VOID GMM_CasCellS4E49(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST *pSysInfo;
    VOS_UINT8                   ucRaiChgFlg;
    VOS_UINT8                   ucDrxLengthChgFlg;
    VOS_UINT8                   ucLaiChgFlg;

    pSysInfo          = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucRaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;
    ucDrxLengthChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg;
    ucLaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg;

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        if (GMM_TRUE == ucRaiChgFlg)
        {
            if (MMCGMM_GSM_NO_FORBIDDEN == pSysInfo->ulForbiddenFlg)
            {
                g_GmmAttachCtrl.ucAttachAttmptCnt = 0;                              /* attach attempt counter清0                */
            }
        }
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* 调用状态的公共处理                       */
        Gmm_TimerStop(GMM_TIMER_ALL);                                           /* 停所有Timer                              */


        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* A+I                                      */

            if (GMM_FALSE == ucLaiChgFlg)
            {                                                                   /* LA没变                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* 通知MM进行LU                             */
            }
        }

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */

        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                        /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);


    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA改变                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;                                  /* Attach attempt counter清0                */
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* 进行Attach                               */
    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX改变                                  */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* 进行Attach                               */
    }
    else
    {
        if ((GMM_TRUE == g_GmmAttachCtrl.ucRetryFlg)
            && (GMM_TRUE == gstGmmCasGlobalCtrl.TempMsgPara.ucGsmCellChgFlg))
        {                                                                       /* 换小区需要进行attach                     */
            Gmm_TimerStop(GMM_TIMER_T3311);                                     /* 停T3311                                  */
            Gmm_TimerStop(GMM_TIMER_T3302);                                     /* 停T3302                                  */
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                               /* 进行Attach                               */
        }
        else
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
                NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

                if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                 && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
                {
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

                    NAS_GMM_SndMmCombinedAttachInitiation();

                    NAS_GMM_SndMmCombinedAttachRejected(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES);

                    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
                }

            }
        }
    }

    return;
}
/*****************************************************************************
 Prototype      : GMM_CasCellS8E49
 Description    :
                  HSS 4100 V200R001 新增
                  在GMM_REGISTERED_INITIATED状态，
                  消息MMCGMM_GAS_SYS_INFO_IND(GSM ONLY)处理
 Input          : VOS_VOID*     pRcvMsg     入口消息指针
 Output         :
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
  2.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  3.日    期  : 2012年08月24日
    作    者  : m00217266
    修改内容  : 修改Gmm_SndSmEstablishCnf接口，添加原因值
  4.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
  5.日    期   : 2016年1月22日
    作    者   : z00359541
    修改内容   : DTS2016010902457:小区重选挂起层二的场景，需要通知层二清除缓存
*****************************************************************************/
VOS_VOID GMM_CasCellS8E49(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST *pSysInfo;
    VOS_UINT8                   ucRaiChgFlg;
    VOS_UINT8                   ucDrxLengthChgFlg;
    VOS_UINT8                   ucLaiChgFlg;

    pSysInfo          = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucRaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;
    ucDrxLengthChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg;
    ucLaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg;

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        g_GmmReqCnfMng.ucCnfMask = 0;                                           /* 清除原语等待标志                         */
        Gmm_TimerStop(GMM_TIMER_ALL);                                           /* 停所有Timer                              */
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* 调用状态的公共处理                       */
        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_GPRS_NOT_SUPPORT);    /* 通知SM GMM注册失败                       */

            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* 清ucSmCnfFlg标志                         */
        }
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清当前流程                               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegInit:INFO: specific procedure ended");

        if (((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
          && (GMM_FALSE == ucLaiChgFlg))
        {                                                                       /* LA没变,并且是A+I                         */
            NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* 通知MM进行LU                             */
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* 停T3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {                                                                       /* ATTACH过程是由SM触发的                   */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_FORBID_LA);  /* 通知SM GMM注册失败                       */

            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* 清ucSmCnfFlg标志                         */
        }
        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG ==
            (g_GmmReqCnfMng.ucCnfMask
                    & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* 清除原语等待标志                         */
        }
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                        /* 调用对禁止列表的操作                     */


        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);


    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA改变                                   */
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* 停T3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG ==
            (g_GmmReqCnfMng.ucCnfMask
                    & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* 清除原语等待标志                         */
        }
        /* 当前是小区重选挂起层二的场景，需要通知层二清除缓存*/
        if (GMM_SUSPEND_LLC_FOR_CELL_RESEL == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
        {
            NAS_NORMAL_LOG(WUEPS_PID_GMM,
                "GMM_CasCellS8E49: Snd ABORT REQ with CLEAR ALL to LL when LL is suspended caused by Cell Reselection");
            Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_ALL);
        }

        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* 进行Attach                               */
    }
    else if ((GMM_TRUE == ucDrxLengthChgFlg)
        || (GMM_TRUE == gstGmmCasGlobalCtrl.ucCellUpdateFlg))
    {                                                                           /* DRX改变                                  */
        if (GMM_TRUE == ucDrxLengthChgFlg)
        {
            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;                      /* 流程结束之后进行RAU                      */
            g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                    /* 标记GMM不能进行RAU时不需要触发MM的LU过程 */
        }
        if (GMM_TRUE == gstGmmCasGlobalCtrl.ucCellUpdateFlg)
        {
            GMM_SndLlcTriggerReq(LL_GMM_TRIG_CAUSE_CELUPD_CELL_NOTIFY);
            gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        }
    }
    else
    {
    }

    return;
}
/*****************************************************************************
 Prototype      : GMM_CasCellS9E49
 Description    : GMM消息矩阵的单元处理函数
                  HSS 4100 V200R001 新增
                  在GMM_REGISTERED_NORMAL_SERVICE状态，
                  消息MMCGMM_GAS_SYS_INFO_IND(GSM ONLY)处理
 Input          : VOS_VOID*     pRcvMsg     入口消息指针
 Output         :
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
  2.日    期    : 2007年01月13日
    作    者    : s46746
    修改内容    : 根据问题单号：A32D08326
  4.日    期   : 2010年09月24日
    作    者   : l00167671
    修改内容   : 问题单号: DTS2010092001266，恢复GPRS服务的RAU过程中出服务区，重新进相同路由区没有再次发起RAU流程
  5.日    期   : 2010年12月08日
    作    者   : l00167671
    修改内容   : 问题单号:DTS2010111202717,重选过程中不做RAU,
                      等到SYS_INFO上报时再做
  4. 日    期   : 2010年12月24日
     作    者   : s46746
     修改内容   : 根据问题单号：DTS2010121400435，五次联合注册失败后，只进行了一次CS注册
  7. 日    期   : 2011年6月7日
     作    者   : c00173809
     修改内容   : 根据问题单号：DTS2011052605262，GPRS 挂起时收到PDP激活请求，在挂起恢复后不会处理该PDP激活请求。
  8. 日    期   : 2011年10月31日
     作    者   : w00166186
     修改内容   : 列表搜过程，GMM没有上报系统消息，导致列表搜失败
  9. 日    期   : 2011年11月19日
     作    者   : zhoujun 40661
     修改内容   : DTS2011111700165,网络模式I下,GMM回到原小区,未能通知MM进入正常服务
 10.日    期   : 201112月16日
    作    者   : l65478
    修改内容   : 问题单号：DTS2011111403722,网络模式I CS注册失败#4时,没有发起注册,导致CS业务不可用
 11. 日    期   : 2012年1月18日
     作    者   : s46746
     修改内容   : 问题单号：DTS2012011601544,网络模式I 联合注册仅PS成功,紧急呼叫后CS指示正常服务
 12. 日    期   : 2012年2月14日
     作    者   : w00176964
     修改内容   : 问题单号：DTS2012021005606:UE在U模发起RAU无响应,T3311运行期间重传RAU
 13. 日    期   : 2012年3月3日
     作    者   : z00161729
     修改内容   : V7R1 C50 支持ISR修改
 14.日    期   : 2012年8月15日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改
 15.日    期   : 2013年07月5日
    作    者   : w00176964
    修改内容   : DTS2013062503351:增加RAU触发场景:NMO下lastr succ lai中携带的RAC改变时
                 但last succ rai不改变时GS口不存在则触发联合RAU流程
 16.日    期   : 2013年7月19日
    作    者   : w00167002
    修改内容   : DTS2013071900239:W下网络模式I,联合注册PS only成功，CS失败原因
                  #17,网络模式由I--->II,此时不应发起联合ATTACH.
                  如果此时依然是网络模式I,但用户设置为PS ONLY,则也不用发起
                  联合ATTACH.
 17.日    期   : 2013年08月07日
    作    者   : l65478
    修改内容   : 修改问题单DTS2013080502397,在重选到G下进行LU后,然后GAS指示重定向到W原来的小区时，如果Gs口不存在,需要发起联合RAU
 18.日    期   : 2015年1月20日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
 19.日    期   : 2015年2月12日
    作    者   : s00217060
    修改内容   : VOLTE SWITCH修改：voice domain发生变化时需要做RAU
*****************************************************************************/
VOS_VOID GMM_CasCellS9E49(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST *pSysInfo;
    VOS_UINT8                   ucRaiChgFlg;
    VOS_UINT8                   ucDrxLengthChgFlg;
    VOS_UINT8                   ucSimCsRegStatus;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatusChgNeedRegFlg;
#endif
    NAS_MML_LAI_STRU                   *pstCsSuccLai = VOS_NULL_PTR;

    GMM_RAI_STRU                        stRai;
    VOS_UINT8                           ucCmpWithLastSucRaiChgFlg;
    VOS_UINT8                           ucCsRestrictFlg;

    pstCsSuccLai     = NAS_MML_GetCsLastSuccLai( );
    stRai.ucRac = pstCsSuccLai->ucRac;
    /* 填写LAC */
    stRai.Lai.aucLac[0] = pstCsSuccLai->aucLac[0];
    stRai.Lai.aucLac[1] = pstCsSuccLai->aucLac[1];                       /* LAC */
    /* 填写PLMN */
    stRai.Lai.PlmnId.aucMccDigit[0] =
        (VOS_UINT8)(pstCsSuccLai->stPlmnId.ulMcc & 0x0F);                           /* MCC Digit 1                              */
    stRai.Lai.PlmnId.aucMccDigit[1] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMcc >> 8) & 0x0F);                    /* MCC Digit 2                              */
    stRai.Lai.PlmnId.aucMccDigit[2] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMcc >> 16) & 0x0F);                   /* MCC Digit 3                              */
    stRai.Lai.PlmnId.aucMncDigit[0] =
        (VOS_UINT8)(pstCsSuccLai->stPlmnId.ulMnc & 0x0F);                           /* MNC Digit 1                              */
    stRai.Lai.PlmnId.aucMncDigit[1] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMnc >> 8) & 0x0F);                    /* MNC Digit 2                              */
    stRai.Lai.PlmnId.aucMncDigit[2] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMnc >> 16) & 0x0F);                   /* MNC Digit 3                              */
    stRai.Lai.PlmnId.ucMncCnt = 3;                                          /* MNC Degit count                          */
    if (GMM_PLMNID_MNC3_INVALID == stRai.Lai.PlmnId.aucMncDigit[2])
    {
        stRai.Lai.PlmnId.ucMncCnt = 2;                                      /* MNC Degit count                          */
    }
    ucCmpWithLastSucRaiChgFlg = Gmm_Compare_Rai(&stRai, &(g_GmmGlobalCtrl.SysInfo.Rai));
    ucCsRestrictFlg = NAS_MML_GetCsRestrictRegisterFlg();


    pSysInfo          = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucRaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;
    ucDrxLengthChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg;

#if (FEATURE_ON == FEATURE_LTE)
    ulT3423StatusChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                 NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                         /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);


    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX改变                                  */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (VOS_TRUE == ulT3423StatusChgNeedRegFlg)
    {
        NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
    }
#endif
    else if ((GMM_TRUE == ucRaiChgFlg)
        || (GMM_TRUE == g_GmmGlobalCtrl.ucGprsResumeFlg))
    {                                                                           /* RA改变                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);
        /*4.2.5.1.7 Substate, ATTEMPTING-TO-UPDATE-MM
        - perform routing area update indicating "combined RA/LA updating with
        IMSI attach" when the routing area of the serving cell has changed and
        the location area this cell is belonging to is not in the list of forbidden LAs.*/

        if ( (VOS_TRUE == NAS_GMM_IsAllowedCombinedAttach_GmmRegisteredAttemptingToUpdateMm())
          && (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState) )
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
    }
    else if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
    {
        /*此分枝预期是G下小区重选过程中T3312超时时才会进入*/
        /* T3311不在运行时才发起RAU */
        if (VOS_FALSE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3311))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
        }
    }
    else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
    else if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_TRUE == g_GmmRauCtrl.ucCsSpringRauFlg)
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
          && (VOS_TRUE == ucSimCsRegStatus))
    {
        Gmm_TimerStop(GMM_TIMER_T3311);                                             /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                             /* 停T3302                                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);         /* 执行RAU                                  */
        g_GmmRauCtrl.ucCsSpringRauFlg = GMM_FALSE;                                  /* 清除CS触发RAU的标志                      */
    }
    /* NMO1下如果LAU成功时携带的RAC与当前驻留的RAC不一样,也认为RAI改变,需要触发RAU */
    else if  ((VOS_TRUE                             == NAS_MML_GetCsAttachAllowFlg())
           && (VOS_FALSE                            == ucCmpWithLastSucRaiChgFlg)
           && (GMM_NET_MODE_I                       == g_GmmGlobalCtrl.ucNetMod)
           && (VOS_TRUE                             == ucSimCsRegStatus)
           && (VOS_FALSE                            == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
           && (VOS_FALSE                            == ucCsRestrictFlg))
    {
        Gmm_TimerStop(GMM_TIMER_T3311);                                             /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                             /* 停T3302                                  */

        Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
    }
    else
    {
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);


        if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {
            NAS_GMM_NotifyMmUnrealCombinedRauResult();
        }


        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

        /* 如果存在缓存的PDP激活请求,那么处理缓存 */
        Gmm_DealWithBuffAfterProc();
    }

    NAS_GMM_ProcSavedMmT3211ExpiredNotify();

    return;
}
/*****************************************************************************
 Prototype      : GMM_CasCellS10E49
 Description    :
                  HSS 4100 V200R001 新增
                  在GMM_REGISTERED_UPDATE_NEEDED状态，
                  消息MMCGMM_GAS_SYS_INFO_IND(GSM ONLY)处理
 Input          : VOS_VOID*     pRcvMsg     入口消息指针
 Output         :
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
  2.Date        : 2007-10-16
    Author      : l65478
    Modification: 根据问题单号：A32D11957
  3.日    期   : 2009-6-3
    作    者   : l00130025
    修改内容   : 问题单号:AT2D12225,从GPRS小区重选到GSM小区,t3312超时后,重回原GPRS小区,发起了normal RAU而非周期性RAU
  4.日    期   : 2010年09月24日
    作    者   : l00167671
    修改内容   : 问题单号: DTS2010092001266，恢复GPRS服务的RAU过程中出服务区，重新进相同路由区没有再次发起RAU流程
  5.日    期   : 2010年12月24日
    作    者   : s46746
    修改内容   : 根据问题单号：DTS2010121400435，五次联合注册失败后，只进行了一次CS注册
  6.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  7.日    期   : 2011年05月10日
    作    者   : c00173809
    修改内容   : 根据问题单号：DTS2011050402447，相同ra/la从支持GPRS重选到不支持GPRS的小区,再重选到原来小区要做联合RAU
  8.日    期   : 2011年06月09日
    作    者   : c00173809
    修改内容   : 根据问题单号：DTS2011060705224，GMM在LIMITED SERVICE状态下，I+A模式收到不支持
                  GPRS相同LAI的小区时，不断做LAU。
  9.日    期   : 2011年08月01日
    作    者   : f00179208
    修改内容   : 根据问题单号：DTS2011072503590，【RAU】正常驻留下用户cops发起PLMN搜索，
                 来到新小区后发起的RAU类型固定为RA UPDATING
 10.日    期   : 2011年04月20日
    作    者   : s46746
    修改内容   : 根据问题单号：DTS2011040804149，【 V3R1C31B027】【RAU】PS ONLY下，PMM_IDLE态W2G重选后，发起ping未进行RAU流程，无法进行数传
 11.日    期   : 2011年11月16日
    作    者   : w00167002
    修改内容   : 问题单号：DTS2011110500571:开机在W下驻留成功，搜网到G下，位置区和
                  路由区都未改变，GMM回复MMC ps域注册完成假流程，同时发起了真
                  流程的注册。3G搜网到2G,此时应该做真流程而非假流程。
 12.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
 13.日    期   : 2012年3月3日
    作    者   : z00161729
    修改内容   : V7R1 C50 支持ISR修改
 14.日    期   : 2012年8月15日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改
 15.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
 16. 日    期   : 2013年5月22日
     作    者   : w00167002
     修改内容   : DTS2013051408623:在W下46007上PS注册失败5次，搜网到L下的46002
                    上注册成功。用户拨打电话通过搜网方式回落到W下的46002网络上，
                    GMM发起RAU失败后没有再尝试RAU.
                    原因:在46007网络上注册失败5次后回落到W下的46002上后，没有
                    重置ATTEMPT COUNTER导致.
 17.日    期   : 2013年9月29日
    作    者   : w00242748
    修改内容   : DTS2013092302598:手动搜网，L下成功驻留，CSFB到W下，位置区变化，LAU/RAU建联失败(5次)，
                 搜网回原小区，继续进行联合RAU失败，MM单独LAU失败，死循环，MM ATTEMPT COUNTER无限增加
 18.日    期   : 2013年11月1日
    作    者   : z00161729
    修改内容   : DTS2013110103529:L重建到gu，ISR激活位置区未改变，gmm未发起rau
 19.日    期   : 2014年04月08日
    作    者   : s00217060
    修改内容   : DTS2014040901544:PS域注册被拒#111,网络带的T3302定时器时长为0，链接释放再收到系统消息时，UE一直发起ATTACH
 20.日    期   : 2015年2月6日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
 21.日    期   : 2015年2月12日
    作    者   : s00217060
    修改内容   : VOLTE SWITCH修改:voice domain发生变化时需要做RAU
 22.日    期   : 2016年1月26日
    作    者   : z00359541
    修改内容   : DTS2016012302336:周期RAU被用户指定搜打断，后续搜到同一网络要能发起注册
*****************************************************************************/
VOS_VOID GMM_CasCellS10E49(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST         *pSysInfo;
    VOS_UINT8                           ucLaiChgFlg;
    VOS_UINT8                           ucRauFlg = GMM_TRUE;
    VOS_UINT8                           ucOldSpecProc;
    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucCsRestrictionFlg;
     VOS_UINT8                          ucRaiChgFlg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatusChgNeedRegFlg;
    ulT3423StatusChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                          NAS_MML_GetTinType(), NAS_MML_GetT3423Status());

#endif

    pSysInfo    = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucLaiChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg;

    ucRaiChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;

    if ( (GMM_TRUE                   == ucRaiChgFlg)
      && (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState))
    {
        if ( (GMM_REGISTERED_NO_CELL_AVAILABLE    == g_GmmGlobalCtrl.ucPlmnSrchPreSta)
          || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == g_GmmGlobalCtrl.ucPlmnSrchPreSta))
        {
            /* 在由ATTEMPT TO UPDATE或者REGISTERED_NO_CELL_AVAILABLE状态经过
               搜网后收到系统消息，需要清除ATTEMPT COUNTER */
            if (MMCGMM_GSM_NO_FORBIDDEN == pSysInfo->ulForbiddenFlg)
            {
                g_GmmRauCtrl.ucRauAttmptCnt = 0;
            }
        }
    }

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */

        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, begin */
        if (VOS_TRUE == NAS_GMM_IsAModeAndNetworkI())
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, end */
        {                                                                       /* A+I                                      */
            if ((GMM_FALSE == ucLaiChgFlg)
             && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
             && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
            {                                                                   /* LA没变                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);          /* 通知MM进行LU                             */
            }
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    /* 周期RAU被用户指定搜打断，后续搜到同一个RAI网络需要停T3311定时器并发起注册 */
    else if ((VOS_TRUE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3311))
          && (GMM_FALSE == ucRaiChgFlg)
          && (VOS_TRUE == pSysInfo->ulUserSrchFlg)
          && (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "GMM_CasCellS10E49: User NW Srch, need to stop T3311 and send RAU Req");
        /* 用户发起的指定搜网，强制发起注册 */
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                         /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);

    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (VOS_TRUE == ulT3423StatusChgNeedRegFlg)
    {
        if (GMM_REGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState)
        {
            NAS_GMM_RcvLmmTimerInfoNotify_RegLimitServ();
            return;
        }

        if (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
        {
            NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
        }
    }
#endif
    else
    {                                                                           /* 小区改变                                 */
        /* g下attach成功lau #17 9088nv开启触发搜网搜hplmn失败，anycell成功回原lau被拒小区，
        gmm在gprs suspend状态搜到mmc搜网指示将g_GmmGlobalCtrl.ucPlmnSrchPreSta设置为6
        gprs suspend，后续在搜网状态收到gprs resume和系统消息多发了rau*/
        if (((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucPlmnSrchPreSta)
          || (GMM_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucPlmnSrchPreSta)
          || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == g_GmmGlobalCtrl.ucPlmnSrchPreSta)
          || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucPlmnSrchPreSta)
          || ((GMM_REGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucPlmnSrchPreSta)
             && (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat)))
            && (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState))
        {
            if ((GMM_FALSE == gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg)
                && (GMM_FALSE == gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg)
                && (GMM_FALSE == g_GmmGlobalCtrl.ucGprsResumeFlg))
            {
                ucRauFlg = GMM_FALSE;
            }
        }

        ucCsAttachAllow    = NAS_MML_GetCsAttachAllowFlg();
        ucCsRestrictionFlg = NAS_MML_GetCsRestrictRegisterFlg();

        if (GMM_TRUE == ucRauFlg)
        {
            Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
            Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
            if ((GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
                &&(GMM_FALSE == gstGmmCasGlobalCtrl.ucSysRauFlg))
            {
                if ((VOS_TRUE == NAS_MML_GetSimCsRegStatus())
                 && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
                 && (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
                 && (VOS_TRUE == ucCsAttachAllow)
                 && (VOS_FALSE == ucCsRestrictionFlg))
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                }
                else
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
                    g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
                }
            }
            else
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
            }
        }
        else
        {
#if (FEATURE_ON == FEATURE_LTE)
            if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
             && (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
             && (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat))
            {
                NAS_GMM_IsrActiveRaiNoChg_InterSys();
            }
            else if ((NAS_MML_ROUTING_UPDATE_STATUS_UPDATED != NAS_MML_GetPsUpdateStatus())
                  && (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState))
#else
            if ((NAS_MML_ROUTING_UPDATE_STATUS_UPDATED != NAS_MML_GetPsUpdateStatus())
                  && (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState))
#endif
            {
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
                    Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE);
                    NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
                }

            }
            else if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            }

            /*3G重选或者搜网到2G网络，两者RAI完全相同，而且UE之前在3G发
              送过信令或用户数据，此时在2G做PS业务时没有进行RAU，导致业
              务失败，修改方案是立即进行RAU(与协议不完全一致，经CCB裁决)*/
            else if (gstGmmCasGlobalCtrl.ucLastDataSender !=
                        NAS_MML_GetCurrNetRatType())
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }
            /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-16, begin */
            /* attahc或rau中携带的ms radio capability是否支持L能力与接入层上报的ms radio capabitlity是否支持L能力不一致需要触发Rau*/
            else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }

            /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-16, end */
            else
            {
                if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
                 && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
                 && (VOS_TRUE == ucCsAttachAllow))
                {
                    NAS_GMM_HandleModeANOIWhenRAInotChange();
                }
                else
                {
                    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;
                    ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;
                    g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;


                    /* 向MMC发送PS注册结果 */
                    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                 GMM_MMC_ACTION_RESULT_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);

                    g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
                }
            }



            if (GMM_ROUTING_AREA_UPDATING_INITIATED != g_GmmGlobalCtrl.ucState)
            {
                if (GMM_SERVICE_REQ_PAGING == g_GmmGlobalCtrl.enServReq)
                {
                    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
                    {
                        GMM_UpdateSysTlli(GMM_LOCAL_TLLI);
                        GMM_AssignSysTlli();
                    }

                    Gmm_TimerStop(GMM_TIMER_T3314);

#if (FEATURE_LTE == FEATURE_ON)
                    if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
                    {
                        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
                    }
#endif

                    Gmm_TimerStop(GMM_TIMER_T3312);

                    if ( 0xffffffff == gstGmmCasGlobalCtrl.ulReadyTimerValue )
                    {
                        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;
#if (FEATURE_LTE == FEATURE_ON)
                    if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
                    {
                        Gmm_TimerStop(GMM_TIMER_T3323);
                    }
#endif
                    }
                    else if ( 0 == gstGmmCasGlobalCtrl.ulReadyTimerValue )
                    {
                        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
                        Gmm_TimerStart(GMM_TIMER_T3312);
                    }
                    else
                    {
                        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;
#if (FEATURE_LTE == FEATURE_ON)
                        if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
                        {
                            Gmm_TimerStop(GMM_TIMER_T3323);
                        }
#endif
                        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
                            = gstGmmCasGlobalCtrl.ulReadyTimerValue;
                        g_GmmTimerMng.ulTimerValMask |= GMM_TIMER_T3314_FLG;
                        Gmm_TimerStart(GMM_TIMER_T3314);
                    }
                    NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);

                    GMM_SndLlcTriggerReq(LL_GMM_TRIG_CAUSE_PAG_RSP);
                }
                else if (GMM_SERVICE_REQ_PDPACT == g_GmmGlobalCtrl.enServReq)
                {
                    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
                    {
                        GMM_UpdateSysTlli(GMM_LOCAL_TLLI);
                        GMM_AssignSysTlli();
                    }

                    Gmm_DealWithBuffAfterProc();
                }
                else
                {
                    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
                    {
                        GMM_UpdateSysTlli(GMM_LOCAL_TLLI);
                        GMM_AssignSysTlli();
                    }
                }
            }
        }
    }


    g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_NONE;

    return;
}
/*****************************************************************************
 Prototype      : GMM_CasCellS11E49
 Description    :
                  HSS 4100 V200R001 新增
                  在GMM_REGISTERED_ATTEMPTING_TO_UPDATE状态，
                  消息MMCGMM_GAS_SYS_INFO_IND(GSM ONLY)处理
 Input          : VOS_VOID*     pRcvMsg     入口消息指针
 Output         :
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
 2.日    期   : 2011年7月14日
   作    者   : h44270
   修改内容   : V7R1 PhaseII阶段调整，注册结果简化
 3.日    期   : 2011年08月01日
   作    者   : f00179208
   修改内容   : 根据问题单号：DTS2011072503590，【RAU】正常驻留下用户cops发起PLMN搜索，
                来到新小区后发起的RAU类型固定为RA UPDATING
 4.日    期   : 2011年11月8日
   作    者   : s46746
   修改内容   : V7R1 PhaseII阶段解决关机慢问题
 5.日    期   : 2011年11月15日
   作    者   : w00166186
   修改内容   : DTS201111402055,网络模式I下被17号原因值拒绝5次后，MM不停的发起注册
 7.日    期   : 2012年1月30日
   作    者   : l00130025
   修改内容   : DTS2012010500368,调用同步接口VOS_GetRelTmRemainTimehTimer时没有判断hTimer是否为0，与定时器异步消息冲突导致异常打印
 8.日    期   : 2013年2月4日
   作    者   : w00176964
   修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
 9.日    期   : 2013年9月29日
   作    者   : w00242748
   修改内容   : DTS2013092302598:手动搜网，L下成功驻留，CSFB到W下，位置区变化，LAU/RAU建联失败(5次)，
                搜网回原小区，继续进行联合RAU失败，MM单独LAU失败，死循环，MM ATTEMPT COUNTER无限增加
10.日    期   : 2016年1月26日
   作    者   : z00359541
   修改内容   : DTS2016012302336:周期RAU被用户指定搜打断，后续搜到同一网络要能发起注册
*****************************************************************************/
VOS_VOID GMM_CasCellS11E49(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST         *pSysInfo;
    VOS_UINT8                           ucRaiChgFlg;
    VOS_UINT8                           ucDrxLengthChgFlg;
    VOS_UINT8                           ucLaiChgFlg;

    pSysInfo          = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucRaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;
    ucDrxLengthChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg;
    ucLaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg;

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
        Gmm_TimerStop(GMM_TIMER_ALL);                                           /* 停所有Timer                              */
        if (GMM_TRUE == ucRaiChgFlg)
        {
            if (MMCGMM_GSM_NO_FORBIDDEN == pSysInfo->ulForbiddenFlg)
            {
                g_GmmRauCtrl.ucRauAttmptCnt = 0;                                    /* RAU attempt counter清0                   */
            }
        }

        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* A+I                                      */
            if (GMM_FALSE == ucLaiChgFlg)
            {                                                                   /* LA没变                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* 通知MM进行LU                             */
            }
        }

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);



    }

    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */

        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                         /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);


    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA改变                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        g_GmmRauCtrl.ucRauAttmptCnt = 0;                                        /* RAU attempt counter清0                   */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX改变                                  */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
    }
    else
    {
        if ((GMM_TRUE == g_GmmRauCtrl.ucRetryFlg)
         && (GMM_TRUE == gstGmmCasGlobalCtrl.TempMsgPara.ucGsmCellChgFlg))
        {                                                                       /* 换小区需要进行RAU                        */
            Gmm_TimerStop(GMM_TIMER_T3311);                                     /* 停T3311                                  */
            Gmm_TimerStop(GMM_TIMER_T3302);                                     /* 停T3302                                  */
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* 进行RAU                                  */
        }

        else
        {
            NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

            if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
             && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
            {
                g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

                NAS_GMM_SndMmCombinedRauInitiation();
                NAS_GMM_SndMmCombinedRauRejected(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES);
                g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
            }

        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_ProcessSmMsgInBuff
 功能描述  : 处理缓存的SM消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月26日
    作    者   : l65478
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_ProcessSmMsgInBuff()
{
    if(GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
    {
        if(GMM_SERVICE_REQ_PDPACT == g_GmmGlobalCtrl.enServReq)
        {
            Gmm_DealWithBuffAfterProc();
            g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_NONE;
        }
    }
}

/*****************************************************************************
 函 数 名  : NAS_GMM_EnterCoveryRaiNoChg_BeforeT3312Exp
 功能描述  : T3312超时前重进服务区，RAI没有改变
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2010年4月26日
   作    者   : l65478
   修改内容   : 新生成函数
 2.日    期   : 2010年10月05日
   作    者   : o00132663
   修改内容   : g->w->g:网络模式I, W下PS接入禁止，MM单独进行LAU，回到G下后，
                GMM应该发起联合RAU with imsi attach
 3.日    期   : 2011年7月14日
   作    者   : h44270
   修改内容   : V7R1 PhaseII阶段调整，注册结果简化
 4.日    期   : 2011年7月25日
   作    者   : h44270
   修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整

 5.日    期   : 2011年04月20日
   作    者   : s46746
   修改内容   : 根据问题单号：DTS2011040804149，【 V3R1C31B027】【RAU】PS ONLY下，PMM_IDLE态W2G重选后，发起ping未进行RAU流程，无法进行数传
 6.日    期   : 2012年2月15日
   作    者   : w00166186
   修改内容   : CSFB&PPAC&ETWS&ISR 开发
 7.日    期   : 2012年3月3日
   作    者   : z00161729
   修改内容   : V7R1 C50 支持ISR修改，T3312启动停止超时需通知L
 8.日    期   : 2012年08月24日
   作    者   : m00217266
   修改内容   : 修改Gmm_SndSmEstablishCnf接口，添加原因值
 9.日    期   : 2013年2月4日
   作    者   : w00176964
   修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册

*****************************************************************************/
VOS_VOID NAS_GMM_EnterCoveryRaiNoChg_BeforeT3312Exp(VOS_VOID)
{
    VOS_UINT8                           ucCsRestrictionFlg;
    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucSimCsRegStatus;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType        = NAS_MML_GetCurrNetRatType();
    ucCsAttachAllow  = NAS_MML_GetCsAttachAllowFlg();
    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
    ucCsRestrictionFlg  =   NAS_MML_GetCsRestrictRegisterFlg();

    if ( (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == NAS_MML_GetPsUpdateStatus())
       && ( gstGmmCasGlobalCtrl.ucLastDataSender == enRatType ))
    {
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;            /* 设置假流程标志                           */

        if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
         || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod)
         || (VOS_TRUE == ucCsRestrictionFlg))
        {                                                               /* 非A+I                                    */
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);               /* 调用状态的公共处理                       */
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }

            /* 如果之前出服务区，T3312超时，启动了T3323,后重进服务区，需要停止T3323*/
            Gmm_TimerStop(GMM_TIMER_T3323);
#endif

            Gmm_TimerStart(GMM_TIMER_T3312);                            /* 启动T3312                                */
            g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: normal RAU procedure started");


            /* 向MMC发送PS注册结果 */
            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                         GMM_MMC_ACTION_RESULT_SUCCESS,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);

            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
        }
        else
        {                                                               /* A+I                                      */
            if (  (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
                &&(VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
            {                                                           /* 更新状态是U1                             */
                Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);           /* 调用状态的公共处理                       */
#if (FEATURE_LTE == FEATURE_ON)
                if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                {
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                }

                /* 如果之前出服务区，T3312超时，启动了T3323,后重进服务区，需要停止T3323*/
                Gmm_TimerStop(GMM_TIMER_T3323);
#endif

                Gmm_TimerStart(GMM_TIMER_T3312);                        /* 启动T3312                                */
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
                                                   VOS_NULL_PTR);            /* 发送 MMCGMM_COMBINED_RAU_ACCEPTED        */
                }


                /* 向MMC发送PS注册结果 */
                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                             GMM_MMC_ACTION_RESULT_SUCCESS,
                                             NAS_MML_REG_FAIL_CAUSE_NULL);

            }
            else
            {                                                           /* 更新状态不是U1                           */
                if ((VOS_FALSE == ucCsAttachAllow)
                 || (VOS_TRUE != ucSimCsRegStatus))
                {                                                       /* sim无效或者CS域不允许注册                */
                    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);       /* 调用状态的公共处理                       */
#if (FEATURE_LTE == FEATURE_ON)
                    if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                    {
                        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                    }

                    /* 如果之前出服务区，T3312超时，启动了T3323,后重进服务区，需要停止T3323*/
                    Gmm_TimerStop(GMM_TIMER_T3323);
#endif

                    Gmm_TimerStart(GMM_TIMER_T3312);                    /* 启动T3312                                */
                    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                    {                                                   /* 需要给SM回EST_CNF                        */
                        g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;
                        Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);    /* 向SM回建立成功的响应                     */
                    }
                    g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: normal RAU procedure started");


                    /* 向MMC发送PS注册结果 */
                    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                 GMM_MMC_ACTION_RESULT_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);

                    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
                }
                else
                {
                    Gmm_RoutingAreaUpdateInitiate(
                                        GMM_UPDATING_TYPE_INVALID);     /* 调用RAU                                  */
                }
            }
        }
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: specific procedure ended");
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;              /* 设置真流程标志                           */
    }
    else
    {                                                                   /* 更新状态不是GU1                          */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);       /* 调用RAU                                  */
    }

    NAS_GMM_ProcessSmMsgInBuff();
}

/*****************************************************************************
 函 数 名  : NAS_GMM_EnterCoveryRaiNoChg_AfterT3312Exp
 功能描述  : T3312超时前重进服务区，RAI改变
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月26日
    作    者   : l65478
    修改内容   : 新生成函数
  2.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
*****************************************************************************/
VOS_VOID NAS_GMM_EnterCoveryRaiNoChg_AfterT3312Exp(VOS_VOID)
{
    g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                      /* 清除出覆盖区标志                         */

    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
    {                                                                   /* 非A+I                                    */
        Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
    }
    else
    {                                                                   /* A+I                                      */
        Gmm_RoutingAreaUpdateInitiate(
                            GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);       /* 调用RAU过程combined RAU with IMSI attach */
    }
}

/*****************************************************************************
 函 数 名  : NAS_GMM_EnterCovery
 功能描述  : 在GMM_REGISTERED_NO_CELL_AVAILABLE状态，消息MMCGMM_GAS_SYS_INF-
             O_IND(GSM ONLY)处理
 输入参数  : VOS_VOID *pRcvMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年06月23日
    作    者   : l65478
    修改内容   : 新生成函数
  2.日    期   : 2009年07月23日
    作    者   : l65478
    修改内容   : 问题单号: AT2D13173，在搜网结束后，立刻进行缓存的SM消息的处理
  3.日    期   : 2009年07月23日
    作    者   : l65478
    修改内容   : 问题单号: AT2D17764，在发起RAU后,立刻把变量ucSpecProc清除,导致
                 RAU失败
  4.日    期   : 2010年09月24日
    作    者   : l00167671
    修改内容   : 问题单号: DTS2010092001266，恢复GPRS服务的RAU过程中出服务区，重新进相同路由区没有再次发起RAU流程
  5.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  6.日    期   : 2011年05月12日
    作    者   : h44270
    修改内容   : 根据问题单号：DTS2011051104889，出服务区后，进入到不支持GPRS小区，再重选回原来注册的小区，服务不可用
  7.日    期   : 2012年3月3日
    作    者   : z00161729
    修改内容   : V7R1 C50 支持ISR修改
  8.日    期   : 2012年8月15日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改
  9.日    期   : 2013年11月1日
    作    者   : z00161729
    修改内容   : DTS2013110103529:L重建到gu，ISR激活位置区未改变，gmm未发起rau
 10.日    期   : 2015年2月12日
    作    者   : s00217060
    修改内容   : VOLTE SWITCH修改：voice domain发生变化时需要做RAU
*****************************************************************************/
VOS_VOID NAS_GMM_EnterCovery(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST         *pSysInfo;
    VOS_UINT8                           ucRaiChgFlg;
    VOS_UINT8                           ucDrxLengthChgFlg;
    VOS_UINT8                           ucLaiChgFlg;
     NAS_MML_RAI_STRU                       *pstLastSuccRai;
     GMM_RAI_STRU                            stGmmRai;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatusChgNeedRegFlg;

    ulT3423StatusChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                                 NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif



    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

    pSysInfo          = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucRaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;
    ucDrxLengthChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg;
    ucLaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg;

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        if (GMM_TRUE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg)
        {
            g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;

            if (GMM_FALSE == ucLaiChgFlg)
            {
                if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
                {
                    NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);             /* 通知MM进行LU                             */
                }
            }
        }

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);
    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* 在forbidden列表中                        */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                        /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);


    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (VOS_TRUE == ulT3423StatusChgNeedRegFlg)
    {
        NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
    }

    else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

#endif
    else if ((GMM_TRUE == Gmm_Compare_Rai(&g_GmmGlobalCtrl.SysInfo.Rai, &stGmmRai))
          && (GMM_FALSE == ucRaiChgFlg) && (GMM_FALSE == ucDrxLengthChgFlg)
          && (GMM_FALSE == g_GmmGlobalCtrl.ucGprsResumeFlg))
    {                                                                           /* 回到原来的RA并且DRX参数没有改变          */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */

#if (FEATURE_ON == FEATURE_LTE)
        if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
         && (GMM_REGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
         && (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat))
        {
            NAS_GMM_IsrActiveRaiNoChg_InterSys();
            return;
        }
#endif

        if (GMM_FALSE == g_GmmRauCtrl.ucT3312ExpiredFlg)
        {                                                                       /* 出覆盖区时T3312未溢出                    */
            NAS_GMM_EnterCoveryRaiNoChg_BeforeT3312Exp();
        }
        else
        {                                                                       /* 出覆盖区时T3312溢出                      */
            NAS_GMM_EnterCoveryRaiNoChg_AfterT3312Exp();
        }
    }
    else
    {                                                                           /* RA改变或者DRX参数变化                    */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        g_GmmRauCtrl.ucT3312ExpiredFlg    = GMM_FALSE;                          /* 清除T3312溢出标记                        */

        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, begin */
        if (VOS_FALSE == NAS_GMM_IsAModeAndNetworkI())
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, end */
        {                                                                       /* 非A+I                                    */
            Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
    }

    return;
}
/*****************************************************************************
 Prototype      : GMM_CasCellS18E49
 Description    :
                  HSS 4100 V200R001 新增
                  在GMM_DEREGISTERED_INITIATED状态，
                  消息MMCGMM_GAS_SYS_INFO_IND(GSM ONLY)处理
 Input          : VOS_VOID*     pRcvMsg     入口消息指针
 Output         :
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
  2.日    期   : 2006年11月1日
    作    者   : s46746
    修改内容   : 根据问题单号：A32D06572
  3.日    期   : 2011年07月13日
    作    者   : w00166186
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  4.日    期   : 2013年10月05日
    作    者   : l65478
    修改内容   : DTS2013092509860:GPRS detach过程被BG搜索终止后,GMM又自动发起了注册
*****************************************************************************/
VOS_VOID GMM_CasCellS18E49(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST *pSysInfo;
    VOS_UINT8                   ucRaiChgFlg;
    VOS_UINT8                   ucDrxLengthChgFlg;

    pSysInfo          = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucRaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;
    ucDrxLengthChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg;

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护定时器                             */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        g_GmmReqCnfMng.ucCnfMask = 0;                                           /* 清除原语等待标志                         */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清当前流程                               */

        /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            /* 本地detach后,需要迁移到对应的状态 */
            if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
            {
                NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);

                Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
            }
            NAS_GMM_SndMmcMmDetachInfo();
        }

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_DeregInit:INFO: specific procedure ended");

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG ==
            (g_GmmReqCnfMng.ucCnfMask
                        & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* 清除原语等待标志                         */
        }
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                         /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);


    }
    else if ((GMM_TRUE == ucRaiChgFlg) || (GMM_TRUE == ucDrxLengthChgFlg))
    {                                                                           /* RA改变或者DRX改变                        */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* 清除原语等待标志                         */
        }
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
    }
    else if (GMM_TRUE == gstGmmCasGlobalCtrl.ucCellUpdateFlg)
    {
        GMM_SndLlcTriggerReq(LL_GMM_TRIG_CAUSE_CELUPD_CELL_NOTIFY);
        gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
    }
    else
    {
    }
    return;
}
/*****************************************************************************
 Prototype      : GMM_CasCellS19E49
 Description    :
                  HSS 4100 V200R001 新增
                  在GMM_ROUTING_AREA_UPDATING_INITIATED状态，
                  消息MMCGMM_GAS_SYS_INFO_IND(GSM ONLY)处理
 Input          : VOS_VOID*     pRcvMsg     入口消息指针
 Output         :
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
 2.日    期   : 2007年06月16日
    作    者   : luojian id:60022475
    修改内容   : 根据问题单号：A32D11635
 3.日    期   : 2011年4月6日
   作    者   : c00173809
   修改内容   : 根据问题单号：DTS2011032900575,NMO1周期性RAU丢网到NMO1不支持
                GPRS的小区中，T3312超时没有发起周期性LAU
 4.日    期   : 2011年5月4日
   作    者   : c00173809
   修改内容   : 问题单号：DTS2011050401296,g单模,模式II,两G小区LAI不同,在周期性
                RAU过程中重选成功,只做周期性RAU不做正常RAU.
 5.日    期   : 2012年08月24日
   作    者   : m00217266
   修改内容   : 修改Gmm_SndSmEstablishCnf接口，添加原因值
 6.日    期   : 2013年2月4日
   作    者   : w00176964
   修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
10.日    期   : 2013年6月22日
   作    者   : l65478
   修改内容   : DTS2013062008301:CS紧急呼叫结束后PS恢复失败搜网结束后驻留到一个可用小区上,
                GMM发起RAU过程中GAS又上报系统信息RAI改变,GMM没有重新发起RAU
*****************************************************************************/
VOS_VOID GMM_CasCellS19E49(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST *pSysInfo;
    VOS_UINT8                   ucRaiChgFlg;
    VOS_UINT8                   ucDrxLengthChgFlg;
    VOS_UINT8                   ucLaiChgFlg;

    pSysInfo          = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucRaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;
    ucDrxLengthChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg;
    ucLaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg;

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护定时器                             */
        g_GmmReqCnfMng.ucCnfMask = 0;                                           /* 清除原语等待标志                         */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* 停T3330                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_FALSE == ucLaiChgFlg)
        {
            /* 当前驻留的位置区与之前驻留的位置区LAI没改变,并且在网络模式I,并且T3312超时 */
            if ((VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
             && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg))
            {
                NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);                    /* 通知MM进行LU                             */
            }
            else if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                  && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
            {                                                                   /* LA没变,并且是A+I                         */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);              /* 通知MM进行LU                             */
            }
            else
            {
            }
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* 停T3330                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {                                                                       /* RAU过程是由SM触发的                      */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_FORBID_LA);  /* 通知SM GMM注册失败                       */

            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* 清ucSmCnfFlg标志                         */
        }
        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG ==
            (g_GmmReqCnfMng.ucCnfMask
                        & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* 清除原语等待标志                         */
        }
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                        /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);


    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA改变                                   */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);                                    /* 更新状态设为GU2                          */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }

        if (GMM_TRUE == g_GmmGlobalCtrl.ucGprsResumeFlg)
        {
            g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_FALSE;
            g_GmmRauCtrl.ucPeriodicRauFlg = GMM_FALSE;

            GMM_LOG_WARN("GMM_CasCellS19E49 warning:Not Start RAU in GMM_RAU_NORMAL_GPRS_RESUME.");
        }
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* 停T3330                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG ==
            (g_GmmReqCnfMng.ucCnfMask
                        & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* 清除原语等待标志                         */
        }
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX改变                                  */
        g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;                      /* 流程结束之后进行RAU                      */
        g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_TRUE;                     /* 标记GMM不能进行RAU时要触发MM的LU过程     */
    }
    else
    {
    }

    return;
}
/*****************************************************************************
 函 数 名  : NAS_GMM_CheckBufferDetach
 功能描述  : 检查缓存中是否DETACH消息，若有则处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年11月11日
   作    者   : l00167671
   修改内容   : 新生成函数
 *****************************************************************************/
VOS_VOID NAS_GMM_CheckBufferDetach(VOS_VOID)
{
	VOS_VOID                           *pMsg;
	MMCGMM_DETACH_REQ_STRU             *pstDetach;

	if (GMM_MSG_HOLD_FOR_DETACH
		== (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
	{                                                                           /* 如果有保留的SR原语                       */
		g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;      /* 清除缓存标志                             */

		pMsg = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach;

		/*构造分发消息*/
		pstDetach = (MMCGMM_DETACH_REQ_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_DETACH_REQ_STRU));

		if (VOS_NULL_PTR == pstDetach)
		{
			Gmm_MemFree(pMsg);
			PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
				"Gmm_DealWithBuffAfterProc:ERROR: Gmm_MemMalloc fail !! ");
			return;
		}

		Gmm_MemCpy(pstDetach, pMsg, sizeof(MMCGMM_DETACH_REQ_STRU));

		/*释放保存的detach消息*/
		Gmm_MemFree(pMsg);

		/*分发缓存的detach消息*/
		Gmm_MsgDistribute((VOS_VOID *)(pstDetach));

		/*释放新申请的内存*/
		Gmm_MemFree(pstDetach);
	}
}
/*****************************************************************************
 Prototype      : GMM_RcvGasSysInfoInd_SuspWaitSys
 Description    :
                  HSS 4100 V200R001 新增
                  在GMM_SUSPENDED_WAIT_FOR_SYSINFO状态，
                  消息MMCGMM_GAS_SYS_INFO_IND(GSM ONLY)处理
 Input          : VOS_VOID*     pRcvMsg     入口消息指针
 Output         :
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
  2.日    期   : 2006年10月9日
    作    者   : s46746
    修改内容   : 根据问题单号：A32D05744
  3.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
 4. 日    期   : 2011年04月25日
    作    者   : c00173809
    修改内容   : 根据问题单号：DTS2011042205602，相同RAI的,从不支持GPRS的2G小区重选到GPRS的3G小区,不做RAU.
 5. 日    期   : 2011年5月16日
    作    者   : c00173809
    修改内容   : 根据问题单号：问题单号:DTS2011050905176,从支持GPRS的小区异系统重选到不支持GPRS的
                 小区,异常停止了T3312定时器.
 6. 日    期   : 2011年05月16日
    作    者   : c00173809
    修改内容   : 根据问题单号：DTS2011051005812，网络模式I,相同RAI,T3312超时时,从支持GPRS的3G小区重选到不支持GPRS的2G小区再重选回原来的3G小区,做联合RAU.

 7. 日    期   : 2011年04月20日
    作    者   : s46746
    修改内容   : 根据问题单号：DTS2011040804149，【V3R1C31B027】【RAU】PS ONLY下，PMM_IDLE态W2G重选后，发起ping未进行RAU流程，无法进行数传
 8. 日    期   : 2012年03月29日
    作    者   : z00161729
    修改内容   : 支持ISR修改
 9. 日    期   : 2012年7月17日
    作    者   : z00161729
    修改内容   : DTS2012073106360:ISR激活CSFB重定向或CCO到GU,idle态位置区不变无需做RAU

10. 日    期   : 2012年09月08日
    作    者   : l65478
    修改内容   : DTS012090302087,L->GU时,RAI没有改变时,GMM发起了RAU

11. 日    期   : 2012年11月08日
    作    者   : l00167671
    修改内容   : DTS2012110508357,SUSPENSION状态时收到CS ONLY的设置如果GAS resume ind失败，不会做detach
12. 日    期   : 2013年9月29日
    作    者   : w00242748
    修改内容   : DTS2013092302598:手动搜网，L下成功驻留，CSFB到W下，位置区变化，LAU/RAU建联失败(5次)，
                 搜网回原小区，继续进行联合RAU失败，MM单独LAU失败，死循环，MM ATTEMPT COUNTER无限增加
13. 日    期   : 2015年2月12日
    作    者   : s00217060
    修改内容   : VOLTE SWITCH修改：voice domain发生变化时，需要做RAU
*****************************************************************************/
VOS_VOID GMM_RcvGasSysInfoInd_SuspWaitSys(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST         *pSysInfo;
    VOS_UINT8                           ucRaiChgFlg;
    VOS_UINT8                           ucLaiChgFlg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatuChgNeedRegFlg;
    ulT3423StatuChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                    NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    pSysInfo    = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucRaiChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;
    ucLaiChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg;

    Gmm_TimerStop(GMM_TIMER_SUSPENDED);

    GMM_ResumeTimer(GMM_TIMER_RESUME);

    if (VOS_TRUE != NAS_MML_GetSimPsRegStatus())
    {                                                                           /* 原来SIM无效                              */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */

        GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NO_IMSI);

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "GMM_RcvGasSysInfoInd_SuspWaitSys:NORMAL: STATUS IS GMM_DEREGISTERED_NO_IMSI");
        return;
    }
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                         /* 调用状态的公共处理                       */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "GMM_RcvGasSysInfoInd_SuspWaitSys:WARNING: Not allow Attach");

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);


        return;
    }
    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        GMM_LOG_INFO("GMM_RcvGasSysInfoInd_SuspWaitSys:the cell not support GPRS.");
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
        Gmm_TimerStop(GMM_REGSTER_AND_SHUTDOWN_TIMER);                                           /* 停所有Timer                              */

        if (GMM_TRUE == ucRaiChgFlg)
        {
            if (MMCGMM_GSM_NO_FORBIDDEN == pSysInfo->ulForbiddenFlg)
            {
                g_GmmRauCtrl.ucRauAttmptCnt = 0;                                    /* RAU attempt counter清0                   */
            }
        }

        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, begin */
        if (VOS_TRUE == NAS_GMM_IsAModeAndNetworkI())
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, end */
        {                                                                       /* A+I                                      */
            if ((GMM_FALSE == ucLaiChgFlg)
             && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
             && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
            {                                                                   /* LA没变                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);                 /* 通知MM进行LU                             */
            }
        }

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* 在forbidden列表中                        */
        g_GmmRauCtrl.ucNpduCnt = 0x0;
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);

        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                        /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);


    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA改变                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */

        Gmm_TimerStop(GMM_TIMER_T3330);
        Gmm_TimerStop(GMM_TIMER_T3318);
        Gmm_TimerStop(GMM_TIMER_T3320);
        g_GmmRauCtrl.ucRauAttmptCnt = 0;                                        /* RAU attempt counter清0                   */
        gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_INTERSYSTEM;


        if (GMM_NETMODE_CHG_NULL == gstGmmSuspendCtrl.ucNetModeChange)
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* 进行RAU                                  */
        }
        else
        {
            GMM_ProcedureByNetMode(gstGmmSuspendCtrl.ucNetModeChange);
        }
    }
    else if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT
        == g_GmmGlobalCtrl.ucRelCause)
    {
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_RoutingAreaUpdateInitiateWithReEstRR();
    }
    else
    {
        if ((GMM_IU_PMM_CONNECTED == gstGmmSuspendCtrl.ucPreSrvState)
         && (NAS_MML_NET_RAT_TYPE_LTE != gstGmmSuspendCtrl.ucPreRat))
        {
            GMM_LOG_INFO("GMM_RcvGasSysInfoInd_SuspWaitSys:Need immediately RAU.");
#if 0
            GMM_SndRabmGprsInfoInd(GMM_RABM_GPRS_SUPPORTED, GMM_RABM_PROC_HANDOVER,
                                   GMM_RABM_IMMEDIATELY_RAU);
#endif
            Gmm_TimerStop(GMM_TIMER_T3311);                                     /* 停T3311                                  */
            Gmm_TimerStop(GMM_TIMER_T3302);                                     /* 停T3302                                  */
            Gmm_TimerStop(GMM_TIMER_T3330);
            Gmm_TimerStop(GMM_TIMER_T3318);
            Gmm_TimerStop(GMM_TIMER_T3320);
            g_GmmRauCtrl.ucRauAttmptCnt = 0;                                    /* RAU attempt counter清0                   */
            gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_INTERSYSTEM;
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* 进行RAU                                  */

        }
        else if ( (gstGmmCasGlobalCtrl.ucLastDataSender !=
                            NAS_MML_GetCurrNetRatType())
#if (FEATURE_ON == FEATURE_LTE)
                      && (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_NET_RAT_TYPE_LTE)
#endif
                )
        {
            GMM_LOG_INFO("GMM_RcvGasSysInfoInd_SuspWaitSys:Need selective RAU.");

            Gmm_TimerStop(GMM_TIMER_T3311);                                     /* 停T3311                                  */
            Gmm_TimerStop(GMM_TIMER_T3302);                                     /* 停T3302                                  */
            Gmm_TimerStop(GMM_TIMER_T3330);
            Gmm_TimerStop(GMM_TIMER_T3318);
            Gmm_TimerStop(GMM_TIMER_T3320);

            gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_INTERSYSTEM;
            if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
                gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
            }
            else
            {
                /* 无条件进行一次RAU */
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }
        }
#if (FEATURE_ON == FEATURE_LTE)
        else if (VOS_TRUE == ulT3423StatuChgNeedRegFlg)
        {
            NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
        }
        else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
#endif
        else
        {
            GMM_LOG_INFO("GMM_RcvGasSysInfoInd_SuspWaitSys:Need not RAU.");
            g_GmmRauCtrl.ucNpduCnt = 0x0;
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_SUCCESS);

            /* W->G, W下接入禁止或者不支持GPRS，到G下后，如果RAC不改变，
               重新调用下GMM_REGISTERED_UPDATE_NEEDED状态下的系统消息处理函数 */
            if ((GMM_REGISTERED_UPDATE_NEEDED == gstGmmSuspendCtrl.ucPreState)
             || (GMM_REGISTERED_LIMITED_SERVICE== gstGmmSuspendCtrl.ucPreState))
            {
                NAS_GMM_EnterCovery(pRcvMsg);
            }
            else
            {
                Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
                GMM_ResumeSuccess();
                if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
                {
                    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
                    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

                    Gmm_RoutingAreaUpdateHandleFollowOn();
                }
                else
                {
                    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
                    {
                        GMM_UpdateSysTlli(GMM_LOCAL_TLLI);
                        GMM_AssignSysTlli();
                    }
                }

#if   (FEATURE_ON == FEATURE_LTE)
                /* L重选到G,路由区未改变，ISR激活，无需做RAU时需要更新状态，
                  否则为register no cell available，后续无法做业务 */
                if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
                 && (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat))

                {
                    NAS_GMM_IsrActiveRaiNoChg_InterSys();
                }
#endif
            }
        }
    }

    if ( GMM_ROUTING_AREA_UPDATING_INITIATED != g_GmmGlobalCtrl.ucState)
	{
		NAS_GMM_CheckBufferDetach();
	}

    return;
}
/*****************************************************************************
 Prototype      : GMM_RcvLlcDataInd
 Description    : 接收LLC_DATA_IND消息处理函数
                  HSS 4100 V200R001 新增

 Input          : VOS_VOID*     pRcvMsg     入口消息指针
 Output         :
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
  2.日    期   : 2006年12月5日
    作    者   : luojian 60022475
    修改内容   : Maps3000接口修改
  3.日    期    : 2009年03月18日
    作    者    : l65478
    修改内容    : 根据问题单号：AT2D08671,数传状态下，W出服务区后，切到G，数传恢复失败，因为GMM没有配置LL加密算法
*****************************************************************************/
VOS_VOID GMM_RcvLlcDataInd(VOS_VOID *pRcvMsg)
{
    LL_NAS_UNITDATA_IND_MSG *pDataInd;
    RRMM_DATA_IND_STRU      *pRrmmDataInd;
    VOS_UINT8                aucBuffer[300];
    VOS_UINT8                ucGprsCipher;

    pDataInd = (LL_NAS_UNITDATA_IND_MSG*)pRcvMsg;

    pRrmmDataInd = (RRMM_DATA_IND_STRU*)aucBuffer;
    /*该域在Gmm_RcvRrmmDataInd函数中检查，这里填充好*/
    pRrmmDataInd->ulCnDomainId       = RRC_NAS_PS_DOMAIN;
    /*该域在Gmm_RcvRrmmDataInd函数中检查，这里填充好*/
    /*
    pRrmmDataInd->ulIntegCheckResult = RRC_NAS_MSG_INTEGRITY_CHECK_SUCCESS;
    */
    /*NAS消息包长度*/
    pRrmmDataInd->RcvNasMsg.ulNasMsgSize = pDataInd->stUnitDataInd.usPduLen;
    /*把LLC包中内容拷贝到RRMM_DATA_IND数据结构中的内容部分*/

    if (pDataInd->stUnitDataInd.usPduLen > 252)
    {
        GMM_LOG_WARN("The length of Msg from LLC is too large!");
        return;
    }

    Gmm_MemCpy(pRrmmDataInd->RcvNasMsg.aucNasMsg,
               pDataInd->stUnitDataInd.aucPdu,
               pDataInd->stUnitDataInd.usPduLen);

    /* 2G消息默认消息完整性通过 */
    if (GMM_FALSE == g_GmmGlobalCtrl.ucIntegrityProtStart)
    {
        g_GmmGlobalCtrl.ucIntegrityProtStart = GMM_TRUE;
    }

    if ((GMM_PD_GMM == (pRrmmDataInd->RcvNasMsg.aucNasMsg[0] & 0x0F))
     && (GMM_MSG_RAU_ACCEPT == pRrmmDataInd->RcvNasMsg.aucNasMsg[1]))
    {
        /* ucCiphInd LL使用的宏定义是LL_NONZERO_VALUE = 1,GMM需要保持同步 */
        if (1 == pDataInd->stUnitDataInd.ucCiphInd)
        {
            ucGprsCipher = VOS_TRUE;
        }
        else
        {
            ucGprsCipher = VOS_FALSE;
        }
        if (ucGprsCipher != gstGmmCasGlobalCtrl.ucGprsCipher)
        {
            gstGmmCasGlobalCtrl.ucGprsCipher = ucGprsCipher;

            NAS_GMM_SndMmcCipherInfoInd();

            /* 指定Kc和加密算法 */
            GMM_AssignGsmKc();
        }
    }

    /*走原来3G的分支 */
    Gmm_RcvRrmmDataInd(pRrmmDataInd);

    return;
}

/*****************************************************************************
  函 数 名  : NAS_GMM_RcvLlcDataCnf
  功能描述  : 接收IDD_LL_UINTDATA_CNF消息处理函数
  输入参数  : VOS_VOID*    pRcvMsg    入口消息指针
  输出参数  : 无
  返 回 值  : 无
  调用函数  :
  被调函数  :

  修改历史  :
1.日    期  : 2015年4月7日
  作    者  : wx270776
  修改内容  : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_RcvLlcDataCnf(
    VOS_VOID                           *pRcvMsg
)
{
    LL_NAS_UNITDATA_CNF_MSG            *pstLlNasUintdataCnf = VOS_NULL_PTR;

    pstLlNasUintdataCnf                 = (LL_NAS_UNITDATA_CNF_MSG*)pRcvMsg;

    /* 判断是否为关机流程 */
    if ( (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
      || (GMM_DETACH_NORMAL_POWER_OFF   == g_GmmGlobalCtrl.ucSpecProc) )
    {
        if ( pstLlNasUintdataCnf->usMui  != NAS_GMM_GetPowerOffDetachPsMui() )
        {
            NAS_WARNING_LOG(WUEPS_PID_GMM, "GMM_RcvLlcDataCnf:The Result Of ID_LL_UNITDATA_CNF Is Wrong!");

            return;
        }

        /* 关机DETACH消息发送给网侧后的处理 */
        NAS_GMM_RcvLlcDataCnf_PowerOff();

        return;
    }

    return;
}

/*****************************************************************************
  函 数 名  : NAS_GMM_RcvLlcDataCnf_PowerOff
  功能描述  : GMM收到LLC发来的IDD_LL_UINTDATA_CNF消息后的关机处理函数
  输入参数  : 无
  输出参数  : 无
  返 回 值  : 无
  调用函数  :
  被调函数  :

  修改历史  :
1.日    期  : 2015年4月7日
  作    者  : wx270776
  修改内容  : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_RcvLlcDataCnf_PowerOff(VOS_VOID)
{
    /* 向OM上报NAS事件 */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    /* 判断当前接入模式是否GSM网络 */
    if (GMM_TRUE != GMM_IsCasGsmMode())
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvLlcDataCnf_PowerOff:Power Off Failure Due To GMM Is CasGsmMode!");
        return;
    }

    /* 停止定时器 */
    Gmm_TimerStop(GMM_TIMER_1S);
    Gmm_TimerStop(GMM_TIMER_DETACH_FOR_POWER_OFF);

    /* 清除P_TMSI_SIGNATURE */
    if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
    {
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;

        NAS_MML_InitUeIdPtmsiSignatureInvalid();

        Gmm_SndAgentUsimUpdateFileReq(GMM_USIM_FILE_PS_LOC_INFO);
    }

    /* 给MMC及缓存的应用模块回复消息 */
    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

    if (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
    {
        NAS_GMM_SndMmGprsDetachComplete();
    }

    Gmm_SndMmcPowerOffCnf();
    Gmm_ComCnfHandle();
    NAS_GMM_FreeTlliForPowerOff();

    /* 清除全局变量 */
    if (GMM_MSG_HOLD_FOR_POWEROFF == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_POWEROFF))
    {
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_POWEROFF;
    }
    Gmm_HoldBufferFree();

    GMM_BufferMsgDump();

    Gmm_ComVariantInit();

    return;
}

/*****************************************************************************
 Prototype      : GMM_RcvGasSuspensionInd
 Description    :
                  HSS 4100 V200R001 新增
                  接收RRMM_GPRS_SUSPENSION_IND (GSM ONLY)消息处理
 Input          : VOS_VOID*     pRcvMsg     入口消息指针
 Output         :
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
  2.日    期   : 2009年05月23日
    作    者   : L65478
    修改内容   : 问题单号:AT2D06770,RAU失败，因为GRM建链的原因是DATA，实际应该是信令
  3.日    期   : 2011年7月13日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII阶段调整，向RABM指示RAB是否需要重建
  4.日    期   : 2011年05月11日
    作    者   : c00173809
    修改内容   : 问题单号:DTS2011050904508,在不支持GPRS的小区做CS业务,然后重选到支持GPRS
                 的小区,在MSG_PROTECT_TIMER超时后,GMM会做RAU.
  5.日    期   : 2011年12月8日
    作    者   : s46746
    修改内容   : 问题单号：DTS2011111603445,接收到系统消息而且层2已经指派后才能恢复RABM
  6.日    期   : 2012年10月10日
    作    者   : z00161729
    修改内容   : DTS2012101002998:csfb mt到g，lai未改变呼叫结束后rel ind指示重定向到l，未做tau
*****************************************************************************/
VOS_VOID GMM_RcvGasSuspensionInd(VOS_VOID *pRcvMsg)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    GMM_LOG_INFO("GMM_RcvGasSuspensionInd:Receive RRMM_GPRS_SUSPENSION_IND");

    enCurRat = NAS_MML_GetCurrNetRatType();

    /* 此时CS域连接肯定存在，但MMCGMM_SERVICE_IND可能不会收到 */
    g_GmmGlobalCtrl.CsInfo.ucCsTransFlg       = GMM_TRUE;

#if (FEATURE_LTE == FEATURE_ON)

    /* 通知L,ps域状态为挂起 */
    NAS_GMM_SndLmmInfoChangeNotifyReq(NAS_MML_GetCurrNetRatType(),
                                      VOS_FALSE,
                                      VOS_TRUE,
                                      gstGmmCasGlobalCtrl.GmmSrvState,
                                      VOS_TRUE);
#endif

    switch (g_GmmGlobalCtrl.ucState)
    {
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            g_GmmGlobalCtrl.ucInterRatFlg = VOS_TRUE;
            Gmm_TimerStop(GMM_TIMER_SUSPENDED);
            Gmm_ComStaChg(GMM_SUSPENDED_GPRS_SUSPENSION);
            return;
        case GMM_GPRS_SUSPENSION:
        case GMM_SUSPENDED_GPRS_SUSPENSION:
        case GMM_SUSPENDED_NORMAL_SERVICE:
            GMM_LOG_INFO("GMM_RcvGasSuspensionInd:Receive RRMM_GPRS_SUSPENSION_IND in abnormal state.");
            return;
        default:
            break;
    }

    GMM_SuspendTimer();

    /* <==A32D09766 如果之前LLC没有被挂起，此时需要挂起LLC */
    if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
    {
        if(GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
        {
            GMM_SndLlcSuspendReq();
        }
        gstGmmCasGlobalCtrl.ucSuspendLlcCause |= GMM_SUSPEND_LLC_FOR_CS;
    }

    gstGmmSuspendCtrl.ucPreSrvState = gstGmmCasGlobalCtrl.GmmSrvState;
    gstGmmSuspendCtrl.ucPreState = g_GmmGlobalCtrl.ucState;

    Gmm_ComStaChg(GMM_GPRS_SUSPENSION);

    /* 指示RABM当前系统模式, 并挂起RABM, bRatChangeFlg为FALSE */
    NAS_GMM_SndRabmSysSrvChgInd(enCurRat,
                                VOS_FALSE,
                                VOS_TRUE,
                                VOS_TRUE);

    return;
}

/*****************************************************************************
 Prototype      : GMM_PowerOffHandle
 Description    : 在GPRS_SUSPENSION状态下,
                  接收POWER OFF消息的延迟处理
 Input          : VOS_VOID
 Output         :
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.Date        : 2007-03-30
    Author      : s46746
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_PowerOffHandle()
{
    MMCGMM_POWER_OFF_REQ_STRU stPowerOffReq;

    stPowerOffReq.MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    stPowerOffReq.MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    stPowerOffReq.MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    stPowerOffReq.MsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    stPowerOffReq.MsgHeader.ulLength        = sizeof(MMCGMM_POWER_OFF_REQ_STRU)
                                                    - VOS_MSG_HEAD_LENGTH;
    stPowerOffReq.MsgHeader.ulMsgName       = MMCGMM_POWER_OFF_REQ;

    Gmm_RcvMmcPowerOffReq(&stPowerOffReq);
}

/*****************************************************************************
 函 数 名  : NAS_GMM_HandleGrpsResumeFail
 功能描述  : GMM接收到GAS指示GPRS恢复失败的处理
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月10日
    作    者   : s46746
    修改内容   : 新生成函数
  4.日    期   : 2010年09月24日
    作    者   : l00167671
    修改内容   : 问题单号: DTS2010092001266，恢复GPRS服务的RAU过程中出服务区，重新进相同路由区没有再次发起RAU流程
  3.日    期   : 2011年6月1日
    作    者   : c00173809
    修改内容   : 根据问题单号：DTS2011050504027，GSM切EDGE慢.
*****************************************************************************/
VOS_VOID NAS_GMM_HandleGrpsResumeFail()
{
    if (GMM_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState)
    {
        gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;
        GMM_ResumeTimer(GMM_TIMER_RESUME);
        if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
        {
            gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
        }

        /*存在PDP激活时，进行路由区更新以回复PS域业务A32D10990==>*/
        /*处于正常服务状态，进行路由区更新以回复PS域业务AT2D18123==>*/
        Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
        if ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
         || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
         || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState)
         || (GMM_REGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
         || (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
         || (GMM_TRUE == g_GmmGlobalCtrl.ucSuspendProc))
        {
            g_GmmGlobalCtrl.ucGprsResumeFlg = GMM_TRUE;
            g_GmmGlobalCtrl.ucSuspendProc   = GMM_FALSE;
        }
        /*<==A32D10990*/
    }
    else
    {
        /*异系统改变之前GMM处于注册状态*/
        if ((0x20 == (gstGmmSuspendCtrl.ucPreState & 0xF0))
         || (GMM_ROUTING_AREA_UPDATING_INITIATED == gstGmmSuspendCtrl.ucPreState))
        {

            Gmm_ComStaChg(GMM_SUSPENDED_WAIT_FOR_SYSINFO);
            Gmm_TimerStart(GMM_TIMER_SUSPENDED);
        }
        else
        {
            if (GMM_TC_ACTIVE == gstGmmSuspendCtrl.ucPreState)
            {
                if ((gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_GetCurrNetRatType())
                 && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
                {
                    Gmm_ComStaChg(GMM_SUSPENDED_WAIT_FOR_SYSINFO);
                }
                else
                {
                    Gmm_ComStaChg(g_GmmGlobalCtrl.ucTcPreSta);
                }
            }
            else
            {
                Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
            }

            GMM_ResumeTimer(GMM_TIMER_RESUME);
            GMM_BufferMsgDump();
            Gmm_HoldBufferFree();                                           /* 清除保留消息                             */
            Gmm_ComCnfHandle();
        }
    }
}

/*****************************************************************************
 Prototype      : GMM_RcvGasGprsResumeInd
 Description    :
                  HSS 4100 V200R001 新增
                  在GPRS_SUSPENSION状态下,
                  接收RRMM_GPRS_RESUME_IND (GSM ONLY)消息处理
 Input          : VOS_VOID*     pRcvMsg     入口消息指针
 Output         :
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
  2.日    期    : 2007年3月30日
    作    者    : s46746
    修改内容    : 问题单号:A32D09854
  3.日    期   : 2007年06月16日
    作    者   : luojian id:60022475
    修改内容   : 根据问题单号：A32D11635
  4.日    期   : 2008年10月16日
    作    者   : l00130025
    修改内容   : 根据问题单号：AT2D6236:缓存信息处理
  5.日    期   : 2009年5月9日
    作    者   : l00130025
    修改内容   : 根据问题单号：AT2D11645/AT2D11797,关机，若detach的EST_REQ失败，Gmm会反复发起EST_REQ
  6.日    期   : 2009年05月23日
    作    者   : L65478
    修改内容   : 问题单号:AT2D06770,RAU失败，因为GRM建链的原因是DATA，实际应该是信令
  7.日    期   : 2010年9月09日
    作    者   : l65478
    修改内容   : DTS2010090302562,PDP激活过程中发生重选，PDP激活事件比标杆慢
  8.日    期   : 2010年11月18日
    作    者   : o00132663
    修改内容   : DTS2010111800285,G下长时间通话过程中T3312超时，电话释放后，第一次RAU失败
  9.日    期   : 2011年01月21日
    作    者   : A00165503
    修改内容   : 问题单号：DTS2011012103743，G下软关机，GMM没有恢复LLC，导致LLC无法发送DETACH REQUEST给网侧
  10.日    期   : 2011年03月3日
    作    者   : f00179208
    修改内容   : 问题单号：DTS2011022800037，G下ping包，然后打电话，切换到W失败后多次回退到G，挂断电话.ping包比其他场景恢复慢
  11.日    期   : 2011年7月13日
     作    者   : w00176964
     修改内容   : V7R1 PhaseII阶段调整，向RABM指示RAB是否需要重建
  12.日    期   : 2011年7月28日
     作    者   : sunxibo 46746
     修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
  13.日    期   : 2011年12月8日
     作    者   : s46746
     修改内容   : 问题单号：DTS2011111603445,接收到系统消息而且层2已经指派后才能恢复RABM
  14.日    期   : 2012年11月08日
	 作    者   : l00167671
	 修改内容   : DTS2012110508357,SUSPENSION状态时收到CS ONLY的设置如果GAS resume ind失败，不会做detach

  15.日    期   : 2014年12月24日
     作    者   : w00167002
     修改内容   : TC还回失败问题:在W下电话切换到GSM后，还回结束后，GMM状态迁移到GMM_TC_ACTIVE状态，导致没有处理系统消息
*****************************************************************************/
VOS_VOID GMM_RcvGasGprsResumeInd( VOS_VOID *pRcvMsg )
{
    RRMM_GPRS_RESUME_IND_ST *pstGprsResumeMsg;

    pstGprsResumeMsg = (RRMM_GPRS_RESUME_IND_ST*)pRcvMsg;

    GMM_LOG_INFO("GMM_RcvGasGprsResumeInd:Receive RRMM_GPRS_RESUME_IND");

    if ((GMM_GPRS_SUSPENSION != g_GmmGlobalCtrl.ucState)
      && (GMM_SUSPENDED_GPRS_SUSPENSION != g_GmmGlobalCtrl.ucState))
    {
        GMM_LOG_WARN("GMM_RcvGasResumeInd:Receive RRMM_GPRS_RESUME_IND in abnormal state.");
        return;
    }

    if (GMM_POWER_OFF_RCV == gstGmmSuspendCtrl.ucPowerOff)
    {
        if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
        {
            GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_SIGNAL);
        }
        Gmm_TimerStop(GMM_TIMER_1S);
        Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
        GMM_PowerOffHandle();
        gstGmmSuspendCtrl.ucPowerOff = GMM_POWER_OFF_NOT_RCV;
        return;
    }

    /* 此时CS域连接肯定不存在，因此将MMCGMM_SERVICE_IND消息中的处理提前放到此处 */
    g_GmmGlobalCtrl.CsInfo.ucCsTransFlg = GMM_FALSE;
    /* GSM下该标志仅使用GMM_RAU_NORMAL_CS_UPDATED，清除以免对后续流程影响 */
    if (GMM_RAU_NORMAL_CS_UPDATED != g_GmmGlobalCtrl.ucSpecProcInCsTrans)
    {
        g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
    }

    if ((GRR_GMM_GPRS_RESUME_SUCCESS == pstGprsResumeMsg->ucResult)
        && (VOS_FALSE == g_GmmGlobalCtrl.ucInterRatFlg))
    {

        /* 在W下电话切换到GSM后，还回结束后，GMM状态迁移到GMM_TC_ACTIVE状态，导致没有处理系统消息 */
        if (GMM_TC_ACTIVE ==  gstGmmSuspendCtrl.ucPreState)
        {
            if (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
            {
                Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            }
            else
            {
                Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
            }
        }
        else
        {
            /*只存在于非异系统改变过程中*/
            Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
        }

        GMM_ResumeTimer(GMM_TIMER_RESUME);

        GMM_BufferMsgResume();

        if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
        {
            g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;
            gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
        }
    }
    else
    {
        NAS_GMM_HandleGrpsResumeFail();

        GMM_BufferMsgResume();
    }

    g_GmmGlobalCtrl.ucInterRatFlg = VOS_FALSE;

    NAS_GMM_ProcSavedGsmSysInfo();

    return;
}

/*****************************************************************************
 Prototype      : GMM_RcvCellReselectInd
 Description    :
                  接收RRMM_CELL_RESELECT_IND (GSM ONLY)消息处理
 Input          : VOS_VOID*     pRcvMsg     入口消息指针
 Output         :
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.日    期    : 2009年5月11日
    作    者    : l65478
    修改内容    : created AT2D06770
  2.日    期    : 2009年7月23日
    作    者    : l65478
    修改内容    : 问题单号：AT2D13234，在挂起LLC时，没有判断TLLI是否分配
  2.日    期    : 2009年8月6日
    作    者    : l65478
    修改内容    : 问题单号：AT2D13610，测试GCF用例26.7.4.3.1失败，原因是在重选到原来的小区后发起了LAU
  3.日    期   : 2010年10月16日
    作    者   : o00132663
    修改内容   : DTS2010101401399:收到小区重选结束消息后，GMM通知LL清除除CM层以外的信令
  4.日    期   : 2010年12月23日
    作    者   : o00132663
    修改内容   : DTS2010122101449:CS ONLY,发起PDP激活，GMM发起注册请求后，GAS发起重选，导致本次注册
                 失败，PDP激活慢。
  5.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  6.日    期   : 2011年04月12日
    作    者   : w00176964
    修改内容   : DTS2011040201321:G模GCF51.2.2.3失败
  7.日    期   : 2013年1月4日
    作    者   : w00176964
    修改内容   : DTS2013010400031:全局变量g_ucGcfInd替换为USIM提供API函数USIMM_IsTestCard
  8.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : SVLTE和USIM接口调整
  9.日    期   : 2014年8月14日
    作    者   : z00161729
    修改内容   : gas下lau建链失败原因值random access reject no valid information场景未按协议实现8s内不发起lau，t3213 4s超时就发起了lau
*****************************************************************************/
VOS_VOID GMM_RcvCellReselectInd( VOS_VOID *pRcvMsg )
{
    RRMM_CELL_RESELECT_IND_ST *pstCellReselMsg;

    pstCellReselMsg = (RRMM_CELL_RESELECT_IND_ST *)pRcvMsg;

    GMM_LOG_INFO("GMM_RcvCellReselectInd:Receive RRMM_CELL_RESELECT_IND");

    if(GMM_FALSE == GMM_IsCasGsmMode())
    {
        return;
    }

    if(RRMM_CELL_RESEL_START == pstCellReselMsg->ucCellReselProc)
    {
        gstGmmCasGlobalCtrl.ucCellReselFlg = VOS_TRUE;
    }
    else
    {
        gstGmmCasGlobalCtrl.ucCellReselFlg = VOS_FALSE;
    }

    if(VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        return;
    }
    if ( VOS_FALSE == NAS_MML_GetSimPsRegStatus()  )
    {
        return;
    }

    /*
    当开始重选时，GMM需要通知LLC挂起用户面数据，并清除LLC的信令面数据
    */
    if(RRMM_CELL_RESEL_START == pstCellReselMsg->ucCellReselProc)
    {
        if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
        {
            if (GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
            {
                GMM_SndLlcSuspendReq();
            }
            NAS_NORMAL_LOG(WUEPS_PID_GMM,
                "GMM_RcvCellReselectInd: Suspend LLC for Cell Reselection");
            gstGmmCasGlobalCtrl.ucSuspendLlcCause |= GMM_SUSPEND_LLC_FOR_CELL_RESEL;
        }
    }
    else
    {
        if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
        {
            Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_NO_SM_SIGNALLING);
        }
        else
        {
            Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_TRIG);
        }
    }


    return;
}

/*****************************************************************************
 Prototype      : GMM_InitCellUpdate
 Description    : 判断当前是否在小区重选过程
 Input          :
 Output         :
 Return Value   :
                    VOS_TRUE :在进行重选
                    VOS_FALSE:不在进行重选
 Calls          :
 Called By      :

 History        :
  1.日    期    : 2009年8月6日
    作    者    : l65478
    修改内容    : created AT2D13610
*****************************************************************************/
VOS_UINT8 GMM_IsGasCellReselect(VOS_VOID)
{
    return gstGmmCasGlobalCtrl.ucCellReselFlg;
}
/*****************************************************************************
 Prototype      : GMM_RcvGasTbfRleInd
 Description    :
                  接收GRRMM_TBF_REL_IND (GSM ONLY)消息处理
 Input          : VOS_VOID*     pRcvMsg     入口消息指针
 Output         :
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.日    期    : 2009年9月03日
    作    者    : l65478
    修改内容    : created AT2D14239,detach完成后,再次发起ATTATCH REQ时,GAS使用旧的TLLI建立的TBF发送数据,没有及时使用新的TLLI,导致MS和仪器侧维护的TLLI不一致,从而导致GAS因为TLLI不匹配丢弃了建立下行TBF的指派命令,最终导致用例失败
  2.日    期   : 2009年09月25日
    作    者   : l00130025
    修改内容   : 问题单号:AT2D14675,RAU/Attach过程中，list搜网失败
  3.日    期   : 2010年12月23日
    作    者   : s46746
    修改内容   : DTS2010122305821:GPRS数传过程中高优先级定时器超时会发起指定搜网
  4.日    期   : 2011年7月11日
    作    者   : sunxibo 46746
    修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
*****************************************************************************/
VOS_VOID GMM_RcvGasTbfRleInd( VOS_VOID *pRcvMsg )
{
    Gmm_SndMmcTBFRelInd();

    if ((GMM_DEREGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState))
    {
        Gmm_TimerStop(GMM_TIMER_WAIT_CONNECT_REL);
    }
    else
    {
        if(GMM_TRUE == g_GmmGlobalCtrl.ulGmmAttachFlg)
        {
            if((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
            && (GMM_DEREGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
            {
                Gmm_RcvRoutingAreaUpdateRejectMsg_AttachFlg_Handling();
            }
            g_GmmGlobalCtrl.ulGmmAttachFlg = GMM_FALSE;
        }
    }
}

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMsRadioCapaInfo_TimerWaitAsMsRadioCapaRunning
 功能描述  : 接收到Gas发来的RadioAccessCapability,GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO定时器在运行的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月15日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，lte能力改变非CS业务过程中立即发起RAU
*****************************************************************************/
VOS_VOID NAS_GMM_RcvMsRadioCapaInfo_TimerWaitAsMsRadioCapaRunning(VOS_VOID)
{

    if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        NAS_GMM_SndRoutingAreaUpdateReq(NAS_GMM_GetRauUpdateType());
        return;
    }

    if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        NAS_GMM_SndAttachReq();
    }

    return;
}

#endif
/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, end */
/*****************************************************************************
 函 数 名  : GMM_RcvGasRadioAccessCapa
 功能描述  : 接收到Gas发来的RadioAccessCapability,更新到Gmm全局变量中，供下
             次RAU时使用
 输入参数  : pRcvMsg   -- 入口消息指针
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年9月4日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2010年10月05日
    作    者   : o00132663
    修改内容   : DTS2010100500115，增加对GAS上报的RAC有效性检查
  3.日    期   : 2012年5月15日
    作    者   : l00130025
    修改内容   : DTS2012041002516: L下默认承载存在数据连接时设置W only失败,GU下接入能力变化时，需要触发一次RAU过程
  4.日    期   : 2012年8月14日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改
  5.日    期   : 2013年1月17日
    作    者   : s00217060
    修改内容   : for DSDA GUNAS C CORE:Utran工作模式为FDD或BUTT时，都需要做RAU或Attach
  6.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，lte能力改变非CS业务过程中立即发起RAU
*****************************************************************************/
VOS_VOID GMM_RcvGasRadioAccessCapa( VOS_VOID *pRcvMsg )
{
    VOS_UINT8                                               ucLen;
    GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND_STRU            *pstRacMsg;


    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-23, begin */
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulIsWaitMsRadioCapaTimerRunning;

    ulIsWaitMsRadioCapaTimerRunning = NAS_GMM_QryTimerStatus(GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO);
#endif
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-23, end */

    if (VOS_NULL_PTR == pRcvMsg)
    {
        return;
    }

    pstRacMsg = (GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND_STRU *)pRcvMsg;

    ucLen = pstRacMsg->aucData[0] + 1;

    if ((ucLen > MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE) || (ucLen < MS_RADIO_ACCESS_CAPABILITY_MIN_SIZE))
    {
        NAS_ERROR_LOG1(WUEPS_PID_GMM, "GMM_RcvGasRadioAccessCapa: Wrong RAC Len: ", ucLen);
    }
    else
    {
        if (0 != VOS_MemCmp(g_GmmGlobalCtrl.UeInfo.aucRadioCpb,
                    pstRacMsg->aucData, MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE))
        {
            PS_MEM_CPY(g_GmmGlobalCtrl.UeInfo.aucRadioCpb, pstRacMsg->aucData,
                       MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE);

#if (FEATURE_ON == FEATURE_LTE)
            if (NAS_UTRANCTRL_UTRAN_MODE_TDD == NAS_UTRANCTRL_GetCurrUtranMode())
            {
                return;
            }

            /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, begin */
            /* 根据syscfg设置是否支持L和L是否enable状态更新ucMsRadioCapSupportLteFromAs*/
            g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs = (VOS_UINT8)NAS_MML_IsSupportLteCapability();

            if (VOS_TRUE == ulIsWaitMsRadioCapaTimerRunning)
            {
                Gmm_TimerStop(GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO);

                if ((GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
                 || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
                {
                    NAS_GMM_RcvMsRadioCapaInfo_TimerWaitAsMsRadioCapaRunning();

                    return;
                }
            }
            /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, end */

            /* 当前已经运行时，重新启动 */
            if (VOS_TRUE == NAS_GMM_QryTimerStatus(GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU))
            {
                Gmm_TimerStop(GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU);
                Gmm_TimerStart(GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU);
                return;
            }

            if (g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs != g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromRegReq)
            {
                NAS_GMM_HandleMsRadioCapLteSupportChanged();
            }
#endif
        }

    }

    return;
}

/*****************************************************************************
 函 数 名  : GMM_RcvGasTdsRadioAccessCapa
 功能描述  : 接收到Gas发来的TDS的RadioAccessCapability,更新到Gmm全局变量中，
              供下次RAU时使用
 输入参数  : pstRcvMsg   -- 入口消息指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月14日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2012年8月14日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改
  3.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，lte能力改变非CS业务过程中立即发起RAU
*****************************************************************************/
VOS_VOID GMM_RcvGasTdsRadioAccessCapa(
    VOS_VOID                           *pstRcvMsg
)
{
    VOS_UINT8                                               ucLen;
    GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND_STRU            *pstRacMsg = VOS_NULL_PTR;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-23, begin */
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulIsWaitMsRadioCapaTimerRunning;

    ulIsWaitMsRadioCapaTimerRunning = NAS_GMM_QryTimerStatus(GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO);
#endif
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-23, end */

    if (VOS_NULL_PTR == pstRcvMsg)
    {
        return;
    }

    pstRacMsg = (GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND_STRU *)pstRcvMsg;

    ucLen     = pstRacMsg->aucData[0] + 1;

    if ((ucLen > MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE) || (ucLen < MS_RADIO_ACCESS_CAPABILITY_MIN_SIZE))
    {
        NAS_ERROR_LOG1(WUEPS_PID_GMM, "GMM_RcvGasTdsRadioAccessCapa: Wrong RAC Len: ", ucLen);
    }
    else
    {
        if (0 != VOS_MemCmp(g_GmmGlobalCtrl.UeInfo.aucTdsRadioCpb,
                    pstRacMsg->aucData, MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE))
        {
            PS_MEM_CPY(g_GmmGlobalCtrl.UeInfo.aucTdsRadioCpb, pstRacMsg->aucData,
                       MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE);

#if (FEATURE_ON == FEATURE_LTE)
            /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, begin */
            /* 根据syscfg设置是否支持L和L是否enable状态更新ucMsRadioCapSupportLteFromAs*/
            if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
            {
                return;
            }

            g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs = (VOS_UINT8)NAS_MML_IsSupportLteCapability();

            if (VOS_TRUE == ulIsWaitMsRadioCapaTimerRunning)
            {
                Gmm_TimerStop(GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO);

                if ((GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
                 || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
                {
                    NAS_GMM_RcvMsRadioCapaInfo_TimerWaitAsMsRadioCapaRunning();

                    return;
                }
            }
            /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, end */


            /* 当前已经运行时，重新启动 */
            if (VOS_TRUE == NAS_GMM_QryTimerStatus(GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU))
            {
                Gmm_TimerStop(GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU);
                Gmm_TimerStart(GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU);
                return;
            }

            if (g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs != g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromRegReq)
            {
                NAS_GMM_HandleMsRadioCapLteSupportChanged();
            }
#endif
        }

    }

    return;
}
/*****************************************************************************
 函 数 名  : GMM_InitCellUpdate
 功能描述  : 发起小区更新过程
 输入参数  : VOS_UINT8 ucReadychangFLG
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月12日
    作    者   : l65478
    修改内容   : 新生成函数
  2.日    期   : 2010年4月12日
    作    者   : l65478
    修改内容   : AT2D18389,在初始小区更新时，GMM应该通知LLC发送NULL帧
  3.日    期   : 2012年3月3日
    作    者   : z00161729
    修改内容   : V7R1 C50 支持ISR修改

  4.日    期   : 2012年11月16日
    作    者   : z40661
    修改内容   : DTS2012102501504，需要记录网络下发的readytimer是否发生改变
*****************************************************************************/
VOS_VOID GMM_InitCellUpdate(VOS_UINT8 ucReadychangFLG)
{
    if (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask)
    {
        Gmm_TimerStop(GMM_TIMER_T3312);

#if (FEATURE_LTE == FEATURE_ON)
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif
    }

    /* force to standby状态，不发起 */
    if (GMM_TRUE == gstGmmCasGlobalCtrl.ucFtsFlg)
    {
        Gmm_TimerStop(GMM_TIMER_T3314);

        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;

        if ( 0xffffffff == gstGmmCasGlobalCtrl.ulReadyTimerValue )
        {
             gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;
#if (FEATURE_LTE == FEATURE_ON)
             if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
             {
                 Gmm_TimerStop(GMM_TIMER_T3323);
             }
#endif
        }
        else
        {
            gstGmmCasGlobalCtrl.ulReadyTimerValue = 0x0;
            gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);
        }
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        return;
    }

    /* READY TIMER值为0，不发起 */
    if (0 == gstGmmCasGlobalCtrl.ulReadyTimerValue)
    {
        Gmm_TimerStop(GMM_TIMER_T3314);

        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        Gmm_TimerStart(GMM_TIMER_T3312);

        gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        return;
    }

    /* 重启READY TIMER */
    if ( 0xffffffff != gstGmmCasGlobalCtrl.ulReadyTimerValue )
    {
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = gstGmmCasGlobalCtrl.ulReadyTimerValue;

        g_GmmTimerMng.ulTimerValMask |= GMM_TIMER_T3314_FLG;
        if ((GMM_TRUE == ucReadychangFLG))
        {
            Gmm_TimerStop(GMM_TIMER_T3314);
        }
        Gmm_TimerStart(GMM_TIMER_T3314);
    }
    else
    {
        Gmm_TimerStop(GMM_TIMER_T3314);
    }


    gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;   /* GSM READY态标志 */

#if (FEATURE_LTE == FEATURE_ON)
    if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
    {
        Gmm_TimerStop(GMM_TIMER_T3323);
    }
#endif


    NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);


    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucCellUpdateFlg)
    {/* 小区更新标志无效，不用通知LLC进行小区更新 */
        return;
    }

    if ( VOS_FALSE == gstGmmCasGlobalCtrl.ucReadyTimerChgFlg )
    {
        gstGmmCasGlobalCtrl.ucCellUpdateFlg     = GMM_FALSE;
        return;
    }

    /* 通知LLC */
    if ((GMM_TRUE == gstGmmCasGlobalCtrl.ucCellNotifyFlg)
        && (GMM_FALSE == ucReadychangFLG))
    {
        GMM_SndLlcTriggerReq(LL_GMM_TRIG_CAUSE_CELUPD_CELL_NOTIFY);
    }
    else
    {
        GMM_SndLlcTriggerReq(LL_GMM_TRIG_CAUSE_CELUPD_NO_CELL_NOTIFY);
    }

    gstGmmCasGlobalCtrl.ucCellUpdateFlg     = GMM_FALSE;
    gstGmmCasGlobalCtrl.ucReadyTimerChgFlg   = VOS_FALSE;
    return;
}

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-22, begin */
/*****************************************************************************
 函 数 名  : GMM_RcvGasClassMarkChangeInd
 功能描述  : 接收到Gas发来的RRMM_CLASSMARK_CHANGE_IND消息,供GU和LNAS发起PS注册时能力上报
             目前暂不使用classmark2和classmark3的信息,classmark3只存储供LNAS注册使用
 输入参数  : pRcvMsg   -- 入口消息指针
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月22日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年06月04日
    作    者   : s00217060
    修改内容   : 根据RRMM_CLASSMARK_CHANGE_IND更新classmark1,classmark2和classmark3
*****************************************************************************/
VOS_VOID GMM_RcvGasClassMarkChangeInd( VOS_VOID *pRcvMsg )
{
    RRMM_CLASSMARK_CHANGE_IND_STRU     *pstClassMarkMsg = VOS_NULL_PTR;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;

    pstClassMarkMsg = (RRMM_CLASSMARK_CHANGE_IND_STRU *)pRcvMsg;
    pstMsCapability = NAS_MML_GetMsCapability();

    /* 更新classmark1 */
    NAS_GMM_UpdateClassmark1(pstMsCapability, pstClassMarkMsg);

    /* 更新classmark2 */
    NAS_GMM_UpdateClassmark2(pstMsCapability, pstClassMarkMsg);

    /* 更新classmark3 */
    NAS_GMM_UpdateClassmark3(pstMsCapability, pstClassMarkMsg);

    return;
}

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-22, end */

/*****************************************************************************
 Prototype      : GMM_SaveReadyTimerValue
 Description    : 保存READY TIMER值
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-15
    Author      : Roger Leo
    Modification: Created function
 2. x51137 2006/4/28 A32D02889

  2.日    期   : 2012年11月16日
    作    者   : z40661
    修改内容   : DTS2012102501504，需要记录网络下发的readytimer是否发生改变
*****************************************************************************/
VOS_VOID GMM_SaveReadyTimerValue(
                        VOS_UINT8 ucMsgByte                 /* 消息中时长位置的字节 */
                        )
{
    VOS_UINT8   ucUnit       = 0;       /* 定义临时变量存储时长单位 */
    VOS_UINT8   ucTimerValue = 0;       /* 定义临时变量存储时长 */
    VOS_UINT32  ulLocalReadyTimer;

    #if 0
    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucReadyTimerNgtFlg)
    {/* 不允许协商READY TIMER */
        return;
    }

    ucUnit       = (VOS_UINT8)(ucMsgByte >> 5);             /* 得到时长单位 */
    ucTimerValue = (VOS_UINT8)(ucMsgByte & 0x1F);           /* 得到Timer Value */

    switch (ucUnit)
    {/* 判断时长单位 */
    case 0:                             /* 2 seconds */
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = GMM_TIMER_T3314_VALUE;    /* 作为READY TIMER超时基本单位，不改变 */
        gstGmmCasGlobalCtrl.ulReadyTimerValue = ucTimerValue * 2 * 1000;
        break;
    case 1:                             /* 1 minute */
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = GMM_TIMER_T3314_VALUE;    /* 作为READY TIMER超时基本单位，不改变 */
        gstGmmCasGlobalCtrl.ulReadyTimerValue = ucTimerValue * 60 * 1000;
        break;
    case 2:                             /* decihours */
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = GMM_TIMER_T3314_VALUE;    /* 作为READY TIMER超时基本单位，不改变 */
        gstGmmCasGlobalCtrl.ulReadyTimerValue = ucTimerValue * 360 * 1000;
        break;
    case 7:                             /* timer is deactivated */
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal = 0;
        gstGmmCasGlobalCtrl.ulReadyTimerValue = 0;
        break;
    default:
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = GMM_TIMER_T3314_VALUE;    /* 作为READY TIMER超时基本单位，不改变 */
        gstGmmCasGlobalCtrl.ulReadyTimerValue = ucTimerValue * 60 * 1000;
        break;
    }

    /* READY TIMER超时最大次数更新 */
    gstGmmCasGlobalCtrl.ulReadyTimerCntMax
            = gstGmmCasGlobalCtrl.ulReadyTimerValue / GMM_TIMER_T3314_VALUE;
    #endif

    ucUnit       = (VOS_UINT8)(ucMsgByte >> 5);             /* 得到时长单位 */
    ucTimerValue = (VOS_UINT8)(ucMsgByte & 0x1F);           /* 得到Timer Value */
    gstGmmCasGlobalCtrl.ucReadyTimerChgFlg = VOS_FALSE;
    ulLocalReadyTimer                   = gstGmmCasGlobalCtrl.ulReadyTimerValue;
    switch (ucUnit)
    {
        case 0 :/* 2 seconds */
            gstGmmCasGlobalCtrl.ulReadyTimerValue = ucTimerValue * 2 * 1000;
            break;

        case 1 :/* 1 minute */
            gstGmmCasGlobalCtrl.ulReadyTimerValue = ucTimerValue * 60 * 1000;
            break;

        case 2 :/* decihours */
            gstGmmCasGlobalCtrl.ulReadyTimerValue = ucTimerValue * 360 * 1000;
            break;

        case 7 : /* timer is deactivated */
            gstGmmCasGlobalCtrl.ulReadyTimerValue = 0xffffffff;
            break;

        default:break;

    }
    if ( gstGmmCasGlobalCtrl.ucReadyTimerChgFlg != ulLocalReadyTimer )
    {
        gstGmmCasGlobalCtrl.ucReadyTimerChgFlg = VOS_TRUE;
    }
    return;
}

/*****************************************************************************
 Prototype      : GMM_CasGetMsGprsMode
 Description    : 获取GMM当前MS GPRS模式
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2006-03-29
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT8 GMM_CasGetMsGprsMode(VOS_VOID)
{
    VOS_UINT8   ucMsMode = NAS_GSM_GPRS_MODE_A;
    NAS_MML_MS_MODE_ENUM_UINT8      enMsMode;

    enMsMode    = NAS_MML_GetMsMode();

    switch (enMsMode)
    {
        case NAS_MML_MS_MODE_PS_CS:
            ucMsMode = NAS_GSM_GPRS_MODE_A;
            break;
        case NAS_MML_MS_MODE_PS_ONLY:
            ucMsMode = NAS_GSM_GPRS_MODE_C_GPRS;
            break;
        case NAS_MML_MS_MODE_CS_ONLY:
            ucMsMode = NAS_GSM_GPRS_MODE_C_GSM;
            break;
        default:
            ucMsMode = NAS_GSM_GPRS_MODE_B;
            break;
    }

    return ucMsMode;
}

/*****************************************************************************
 Prototype      : GMM_CasGetGmmState
 Description    : 获取GMM当前服务状态，是否处于READY状态
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2006-03-29
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT8 GMM_CasGetGmmState(VOS_VOID)
{
    VOS_UINT8   ucGmmState = NAS_GMM_STATE_IDLE;

    switch (gstGmmCasGlobalCtrl.GmmSrvState)
    {
        case GMM_AGB_GPRS_IDLE:
            ucGmmState = NAS_GMM_STATE_IDLE;
            break;
        case GMM_AGB_GPRS_STANDBY:
            ucGmmState = NAS_GMM_STATE_STANDYBY;
            break;
        case GMM_AGB_GPRS_READY:
            ucGmmState = NAS_GMM_STATE_READY;
            break;
        default:
            ucGmmState = NAS_GMM_STATE_IDLE;
            break;
    }

    return ucGmmState;
}

/*****************************************************************************
 Prototype      :
 Description    : GMM FSM状态值改变
                  HSS 4121 V100R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2006-04-05
    Author      : Roger Leo
    Modification: Created function

  2.日    期   : 2011年12月14日
    作    者   : l00130025
    修改内容   : 问题单DTS2011091906272,Dereg状态下没有进入到Idle态,没有停止ReadyTimer

  3.日    期   : 2012年2月18日
    作    者   : w00181244
    修改内容   : 问题单DTS2012021305344,cgreg不上报问题，调整服务状态上报和注册状态上报的顺序
  4.日    期   : 2012年9月07日
    作    者   : l00171473
    修改内容   : DTS2012081701006, 添加GMM状态的可维可测消息
  5.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  6.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  7.日    期   : 2014年05月22日
    作    者   : W00242748
    修改内容   : DTS2014050900899:将GMM的处理状态通知给WAS
  8.日    期   : 2014年6月13日
    作    者   : w00242748
    修改内容   : DSDS 新特性
*****************************************************************************/
VOS_VOID GMM_CasFsmStateChangeTo(VOS_UINT8 ucFsmSta)
{

    /* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();
    if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
      || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        NAS_GMM_NotifyRrmmChgNonDrxMode(g_GmmGlobalCtrl.ucState, ucFsmSta);
    }
    /* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

#if(FEATURE_ON == FEATURE_DSDS)
    NAS_GMM_NotifySessionAccordingStateChg(g_GmmGlobalCtrl.ucState, ucFsmSta);
#endif

    g_GmmGlobalCtrl.ucState = ucFsmSta;

    NAS_GMM_LogGmmStateInfo(g_GmmGlobalCtrl.ucState);


    NAS_GMM_StopReadyTimer_DeregStat();

    NAS_GMM_SetIdleSrvState_DeregStat();


    GMM_PrintState();

    Gmm_Com_ServiceStatus_Handle();                                               /* 通知MMC服务状态                          */


    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvGprsAccessResultInd
 功能描述  : 收到接入层上报的GPRS接入结果，向MMC指示连接状态
 输入参数  : VOS_VOID  *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年07月12日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2012年03月12日
    作    者   : z00161729
    修改内容   : 支持ISR修改
*****************************************************************************/
VOS_VOID NAS_GMM_RcvGprsAccessResultInd(
    VOS_VOID                           *pstMsg
)
{
    GRRGMM_GPRS_ACCESS_RESULT_IND_STRU *pstRcvMsg;

    pstRcvMsg = (GRRGMM_GPRS_ACCESS_RESULT_IND_STRU*)pstMsg;

    /* 根据GAS上报的内容，通知MMC当前的信令连接状态 */
    if (NAS_GPRS_ACCESS_SUCCESS == pstRcvMsg->enResult )
    {
        /* 设置GSM模式下PS域存在业务或者在进行注册 */
        NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_PRESENT);


#if (FEATURE_LTE == FEATURE_ON)
        if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            Gmm_TimerStop(GMM_TIMER_T3323);
        }
#endif
    }
    else
    {
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
    }
}

/*****************************************************************************
 函 数 名  : NAS_GMM_SaveGsmSysInfo
 功能描述  : 缓存GSM系统消息
 输入参数  : pstGsmSysInfo
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月28日
   作    者  : s46746
   修改内容  : 新生成函数
 2.日    期   : 2012年1月9日
   作    者   : l00130025
   修改内容   : DTS2011122900476,Gsm系统消息,多次缓存时，有内存泄漏问题
*****************************************************************************/
VOS_VOID NAS_GMM_SaveGsmSysInfo(
    MMCGMM_GSM_SYS_INFO_IND_ST         *pstGsmSysInfo
)
{
    MMCGMM_GSM_SYS_INFO_IND_ST         *pstHoldGsmSysInfo = VOS_NULL_PTR;



    /* 只保存一条GSM的系统消息，先释放原来存储的消息，避免内存泄露 */
    NAS_GMM_FreeGsmSysInfo();

    pstHoldGsmSysInfo = (MMCGMM_GSM_SYS_INFO_IND_ST *)Gmm_MemMalloc(sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
    if (VOS_NULL_PTR == pstHoldGsmSysInfo)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_SaveGsmSysInfo:WARNING: Mem alloc fail.");
        return;
    }

    /* 置缓存标志 */
    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_GSM_SYSINFO;

    /* 保存系统消息 */
    Gmm_MemCpy(pstHoldGsmSysInfo, pstGsmSysInfo, sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForGsmSysinfo = (VOS_UINT32)pstHoldGsmSysInfo;

    return;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_SetMmT3211ExpiredDelayRauFlag
 功能描述  : 设置mm T3211定时器超时是否需要延迟做rau的标识
 输入参数  : ucMmT3211ExpiredFlag - mm T3211定时器超时是否需要延迟做rau的标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月5日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改

*****************************************************************************/
VOS_VOID NAS_GMM_SetMmT3211ExpiredDelayRauFlag(
    VOS_UINT8                           ucMmT3211ExpiredDelayRauFlag
)
{
    g_GmmGlobalCtrl.MsgHold.ucMmT3211ExpiredDelayRauFlag = ucMmT3211ExpiredDelayRauFlag;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_GetMmT3211ExpiredDelayRauFlag
 功能描述  : 获取mm T3211定时器超时是否需要延迟做rau的标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : mm T3211定时器超时是否需要延迟做rau的标识
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月5日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改

*****************************************************************************/
VOS_UINT8 NAS_GMM_GetMmT3211ExpiredDelayRauFlag(VOS_VOID)
{
    return g_GmmGlobalCtrl.MsgHold.ucMmT3211ExpiredDelayRauFlag;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_ProcSavedMmT3211ExpiredNotify
 功能描述  : 处理缓存的mm T3211定时器超时消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月5日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改

*****************************************************************************/
VOS_VOID NAS_GMM_ProcSavedMmT3211ExpiredNotify(VOS_VOID)
{
    if (VOS_FALSE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
    {
        return;
    }

    if (VOS_FALSE == NAS_GMM_GetMmT3211ExpiredDelayRauFlag())
    {
        return;
    }

    if (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_ProcSavedGsmSysInfo
 功能描述  : 处理缓存GSM系统消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月28日
    作    者  : s46746
    修改内容  : 新生成函数

 2.日    期   : 2011年12月30日
   作    者   : zhoujun 40661
   修改内容   : 回放工程调用空指针修改

 3.日    期   : 2012年1月9日
   作    者   : l00130025
   修改内容   : DTS2011122900476,缓存的Gsm系统消息,有内存重复释放和泄漏问题,Gmm_MsgDistribute有仍无法处理的情况

*****************************************************************************/
VOS_VOID NAS_GMM_ProcSavedGsmSysInfo()
{
    if (NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
    {
        return;
    }


    if (GMM_MSG_HOLD_FOR_GSM_SYSINFO
        != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_GSM_SYSINFO))
    {
        return;
    }

    if ((GMM_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState)
     || (GMM_SUSPENDED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
     || (GMM_SUSPENDED_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState))
    {
        return;
    }


    /* Modified by z40661 for 回放工程调用空指针修改, 2011-12-30 begin */

    if (VOS_NULL_PTR != g_GmmGlobalCtrl.MsgHold.ulMsgAddrForGsmSysinfo)
    {
        Gmm_MsgDistribute((VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForGsmSysinfo);
    }
    /* Modified by z40661 for 回放工程调用空指针修改, 2011-12-30 begin */


    return;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_FreeGsmSysInfo
 功能描述  : 释放缓存GSM系统消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月28日
   作    者  : s46746
   修改内容  : 新生成函数
 2.日    期   : 2012年1月9日
   作    者   : l00130025
   修改内容   : DTS2011122900476,缓存的Gsm系统消息,有内存重复释放和泄漏问题，避免空指针
*****************************************************************************/
VOS_VOID NAS_GMM_FreeGsmSysInfo()
{
    VOS_VOID                           *pAddr = VOS_NULL_PTR;

    if (GMM_MSG_HOLD_FOR_GSM_SYSINFO
        != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_GSM_SYSINFO))
    {
        return;
    }

    /* 清除保留标志 */
    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_GSM_SYSINFO;

    /* 将保留buffer中所有的消息释放 */
    if (VOS_NULL_PTR != g_GmmGlobalCtrl.MsgHold.ulMsgAddrForGsmSysinfo)
    {
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForGsmSysinfo;
        Gmm_MemFree(pAddr);
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForGsmSysinfo = VOS_NULL_PTR;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_InitCellUpdate_RcvSysInfo
 功能描述  : 通知LLC进行小区更新
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年12月27日
   作    者  : l65478
   修改内容  : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_InitCellUpdate_RcvSysInfo(VOS_UINT8 ucReadychangFLG)
{
    if (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask)
    {
        Gmm_TimerStop(GMM_TIMER_T3312);

#if (FEATURE_LTE == FEATURE_ON)
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif
    }

    /* force to standby状态，不发起 */
    if (GMM_TRUE == gstGmmCasGlobalCtrl.ucFtsFlg)
    {
        Gmm_TimerStop(GMM_TIMER_T3314);

        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;

        if ( 0xffffffff == gstGmmCasGlobalCtrl.ulReadyTimerValue )
        {
             gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;
#if (FEATURE_LTE == FEATURE_ON)
             if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
             {
                 Gmm_TimerStop(GMM_TIMER_T3323);
             }
#endif
        }
        else
        {
            gstGmmCasGlobalCtrl.ulReadyTimerValue = 0x0;
            gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);
        }
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        return;
    }

    /* READY TIMER值为0，不发起 */
    if (0 == gstGmmCasGlobalCtrl.ulReadyTimerValue)
    {
        Gmm_TimerStop(GMM_TIMER_T3314);

        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        Gmm_TimerStart(GMM_TIMER_T3312);

        gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        return;
    }

    /* 重启READY TIMER */
    if ( 0xffffffff != gstGmmCasGlobalCtrl.ulReadyTimerValue )
    {
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = gstGmmCasGlobalCtrl.ulReadyTimerValue;

        g_GmmTimerMng.ulTimerValMask |= GMM_TIMER_T3314_FLG;
        if ((GMM_TRUE == ucReadychangFLG))
        {
            Gmm_TimerStop(GMM_TIMER_T3314);
        }
        Gmm_TimerStart(GMM_TIMER_T3314);
    }
    else
    {
        Gmm_TimerStop(GMM_TIMER_T3314);
    }


    gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;   /* GSM READY态标志 */

#if (FEATURE_LTE == FEATURE_ON)
    if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
    {
        Gmm_TimerStop(GMM_TIMER_T3323);
    }
#endif


    NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);


    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucCellUpdateFlg)
    {/* 小区更新标志无效，不用通知LLC进行小区更新 */
        return;
    }

    /* 通知LLC */
    if ((GMM_TRUE == gstGmmCasGlobalCtrl.ucCellNotifyFlg)
      && (GMM_FALSE == ucReadychangFLG))
    {
        GMM_SndLlcTriggerReq(LL_GMM_TRIG_CAUSE_CELUPD_CELL_NOTIFY);
    }
    else
    {
        GMM_SndLlcTriggerReq(LL_GMM_TRIG_CAUSE_CELUPD_NO_CELL_NOTIFY);
    }

    gstGmmCasGlobalCtrl.ucCellUpdateFlg     = GMM_FALSE;
    gstGmmCasGlobalCtrl.ucReadyTimerChgFlg   = VOS_FALSE;
    return;
}

/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
/*****************************************************************************
 函 数 名  : NAS_GMM_NotifyGasChgNonDrxMode
 功能描述  : 通知GAS进入Non-Drx模式
 输入参数  : ucCurState       :Gmm的当前状态
             ucTargetState    :Gmm将要迁移到的状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月1日
    作    者   : l00167671
    修改内容   : 新生成函数
  2.日    期   : 2014年05月22日
    作    者   : W00242748
    修改内容   : DTS2014050900899:将GMM的处理状态通知给WAS
  3.日    期   : 2015年4月21日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_GMM_NotifyRrmmChgNonDrxMode(
    VOS_UINT8                           ucCurState,
    VOS_UINT8                           ucTargetState
)
{

    /* 44060协议5.5.1.5中描述:
    When initiating the MM procedures for GPRS attach and routeing area update defined in 3GPP TS 24.008,
    the mobile station shall enter the MM non-DRX mode period. This period ends when either of the messages GPRS ATTACH ACCEPT,
    GPRS ATTACH REJECT, ROUTING AREA UPDATE ACCEPT or ROUTING AREA UPDATE REJECT is received by the mobile station.
    This period also ends after timeout when waiting for any of these messages
    在ATTACH和RAU开始到结束应该保持在MM non-DRX状态,本函数根据GMM
        状态的改变判断是否应该给GAS发送通知消息，并发送
    */
    RRMM_GMM_PROC_TYPE_ENUM_UINT16      enGprsProcType;
    RRMM_GMM_PROC_FLAG_ENUM_UINT16      enGprsProcFlg;

    NAS_MML_GMM_PROC_TYPE_ENUM_UINT16   enMmlGmmProcType;
    NAS_MML_GMM_PROC_FLAG_ENUM_UINT16   enMmlGmmProcFlag;

    enGprsProcType = RRMM_GMM_PROC_TYPE_INVALID;
    enGprsProcFlg  = RRMM_GMM_PROC_FLAG_INVALID;

    if ( GMM_REGISTERED_INITIATED == ucCurState )
    {
        enGprsProcType = RRMM_GMM_PROC_TYPE_ATTACH;

        if ( GMM_REGISTERED_INITIATED != ucTargetState )
        {
            enGprsProcFlg = RRMM_GMM_PROC_FLAG_FINISH;
        }
        else
        {
            enGprsProcFlg = RRMM_GMM_PROC_FLAG_START;
        }
    }
    else if ( GMM_ROUTING_AREA_UPDATING_INITIATED == ucCurState )
    {
        if ( GMM_TRUE == g_GmmRauCtrl.ucPeriodicRauFlg )
        {
            enGprsProcType = RRMM_GMM_PROC_TYPE_PERIOD_RAU;
        }
        else
        {
            enGprsProcType = RRMM_GMM_PROC_TYPE_NORMAL_RAU;
        }

        if ( GMM_ROUTING_AREA_UPDATING_INITIATED != ucTargetState )
        {
            enGprsProcFlg = RRMM_GMM_PROC_FLAG_FINISH;
        }
        else
        {
            enGprsProcFlg = RRMM_GMM_PROC_FLAG_START;
        }
    }
    else if ( GMM_REGISTERED_INITIATED == ucTargetState )
    {
        enGprsProcType = RRMM_GMM_PROC_TYPE_ATTACH;
        enGprsProcFlg = RRMM_GMM_PROC_FLAG_START;
    }
    else if ( GMM_ROUTING_AREA_UPDATING_INITIATED == ucTargetState )
    {
        if ( GMM_TRUE == g_GmmRauCtrl.ucPeriodicRauFlg )
        {
            enGprsProcType = RRMM_GMM_PROC_TYPE_PERIOD_RAU;
        }
        else
        {
            enGprsProcType = RRMM_GMM_PROC_TYPE_NORMAL_RAU;
        }

        enGprsProcFlg = RRMM_GMM_PROC_FLAG_START;
    }
    else
    {
    }

    if ( RRMM_GMM_PROC_TYPE_INVALID != enGprsProcType )
    {
        NAS_GMM_SndRrmmGmmProcNotify(enGprsProcType, enGprsProcFlg);

        NAS_GMM_ConverRrcGmmProcTypeToMml(enGprsProcType, &enMmlGmmProcType);
        NAS_GMM_ConverRrcGmmProcFlagToMml(enGprsProcFlg, &enMmlGmmProcFlag);
        NAS_MML_SetGmmProcType(enMmlGmmProcType);
        NAS_MML_SetGmmProcFlag(enMmlGmmProcFlag);
    }
}
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
/*****************************************************************************
 函 数 名  : NAS_GMM_UpdateClassmark1
 功能描述  : 根据RRMM_CLASSMARK_CHANGE_IND更新classmark1
 输入参数  : pstMsCapability       :全局变量中的Ms能力
             pstClassMarkMsg       :RRMM_CLASSMARK_CHANGE_IND消息中带的classmark信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月04日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_UpdateClassmark1(
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability,
    RRMM_CLASSMARK_CHANGE_IND_STRU     *pstClassMarkMsg
)
{
    VOS_UINT8                           ucClassmark2Len;


    ucClassmark2Len = pstClassMarkMsg->ucClassmark2Len;

    /* 长度非法或为0则不使用 */
    if ((MS_CLASSMARK2_MAX_LEN < ucClassmark2Len)
     || (0                    == ucClassmark2Len))
    {
        NAS_ERROR_LOG1(WUEPS_PID_GMM, "NAS_GMM_UpdateClassmark2: Wrong classmark2 Len: ", ucClassmark2Len);
    }
    else
    {
        /* pstClassMarkMsg->aucClassmark2[0]是classmark2的实际长度，从aucClassmark2[1]开始才是实际的值 */
        pstMsCapability->ucClassmark1 = pstClassMarkMsg->aucClassmark2[1];
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_UpdateClassmark2
 功能描述  : 根据RRMM_CLASSMARK_CHANGE_IND更新classmark2
 输入参数  : pstMsCapability       :全局变量中的Ms能力
             pstClassMarkMsg       :RRMM_CLASSMARK_CHANGE_IND消息中带的classmark信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月04日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_UpdateClassmark2(
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability,
    RRMM_CLASSMARK_CHANGE_IND_STRU     *pstClassMarkMsg
)
{
    VOS_UINT8                           ucClassmark2Len;


    ucClassmark2Len = pstClassMarkMsg->ucClassmark2Len;

    /* 长度非法或为0则不使用 */
    if ((MS_CLASSMARK2_MAX_LEN < ucClassmark2Len)
     || (0                    == ucClassmark2Len))
    {
        NAS_ERROR_LOG1(WUEPS_PID_GMM, "NAS_GMM_UpdateClassmark2: Wrong classmark2 Len: ", ucClassmark2Len);
    }
    else
    {
        if (0 != PS_MEM_CMP(pstMsCapability->aucClassmark2,
                            pstClassMarkMsg->aucClassmark2, MS_CLASSMARK2_MAX_LEN))
        {
            /* pstClassMarkMsg->aucClassmark2[0]是classmark2的实际长度，从aucClassmark2[1]开始才是实际的值 */
            pstMsCapability->aucClassmark2[0]   = pstClassMarkMsg->aucClassmark2[0];

            PS_MEM_CPY(&(pstMsCapability->aucClassmark2[1]), &(pstClassMarkMsg->aucClassmark2[1]), pstClassMarkMsg->aucClassmark2[0]);
        }
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_GMM_UpdateClassmark3
 功能描述  : 根据RRMM_CLASSMARK_CHANGE_IND更新classmark3
 输入参数  : pstMsCapability       :全局变量中的Ms能力
             pstClassMarkMsg       :RRMM_CLASSMARK_CHANGE_IND消息中带的classmark信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月04日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_UpdateClassmark3(
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability,
    RRMM_CLASSMARK_CHANGE_IND_STRU     *pstClassMarkMsg
)
{
    VOS_UINT8                           ucFddLen;
    VOS_UINT8                           ucTddLen;


    ucFddLen = pstClassMarkMsg->ucClassmark3FddLen;

    /* 长度非法或为0则不使用 */
    if ((MS_CLASSMARK3_MAX_LEN < ucFddLen)
     || (0                    == ucFddLen))
    {
        NAS_ERROR_LOG1(WUEPS_PID_GMM, "GMM_RcvGasClassMarkChangeInd: Wrong fdd classmark3 Len: ", ucFddLen);
    }
    else
    {
        if (0 != PS_MEM_CMP(&(pstMsCapability->aucFddClassmark3[1]),
                            pstClassMarkMsg->aucClassmark3Fdd, MS_CLASSMARK3_MAX_LEN))
        {
            pstMsCapability->aucFddClassmark3[0] = ucFddLen;
            PS_MEM_CPY(&(pstMsCapability->aucFddClassmark3[1]), pstClassMarkMsg->aucClassmark3Fdd, ucFddLen);
        }
    }

    ucTddLen = pstClassMarkMsg->ucClassmark3TddLen;

    if ((MS_CLASSMARK3_MAX_LEN < ucTddLen)
     || (0                     == ucTddLen))
    {
        NAS_ERROR_LOG1(WUEPS_PID_GMM, "GMM_RcvGasClassMarkChangeInd: Wrong tdd classmark3 Len: ", ucTddLen);
    }
    else
    {
        if (0 != VOS_MemCmp(&(pstMsCapability->aucTddClassmark3[1]),
                            pstClassMarkMsg->aucClassmark3Tdd, MS_CLASSMARK3_MAX_LEN))
        {
            pstMsCapability->aucTddClassmark3[0] = ucTddLen;
            PS_MEM_CPY(&(pstMsCapability->aucTddClassmark3[1]), pstClassMarkMsg->aucClassmark3Tdd, ucTddLen);
        }
    }

    return;

}


/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
