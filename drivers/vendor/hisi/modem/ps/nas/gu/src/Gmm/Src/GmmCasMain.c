/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : GmmCasMain.c
  Author       : Roger Leo
  Version      : V200R001
  Date         : 2005-08-25
  Description  : 该C文件给出了GmmCasMain模块的实现
  Function List:
        ---
        ---
        ---
  History      :
  1. Date:2005-08-25
     Author: Roger Leo
     Modification:update
  2. s46746 2006-03-08 根据问题单A32D02368修改
  3. x51137 2006/4/28 A32D02889
  4. s46746 2006-05-08 根据问题单A32D03487修改
  5. 日    期   : 2006年9月19日
     作    者   : liurui id:40632
     修改内容   : 根据问题单号：A32D05237
  6.日    期   : 2006年10月9日
    作    者   : s46746
    修改内容   : 根据问题单号：A32D05744
  7.x51137 2006/11/3 A32D06511
  8.日    期   : 2006年11月20日
    作    者   : s46746
    修改内容   : 创建，根据问题单号：A32D07433
  9.日    期   : 2007年3月30日
    作    者   : s46746
    修改内容   : 问题单号:A32D09854
 10.日    期   : 2007年10月13日
    作    者   : s46746
    修改内容   : 根据问题单号：A32D13060
 11.日    期   : 2007年11月22日
    作    者   : l00107747
    修改内容   : 问题单号:A32D13535
 12.日    期   : 2007年12月2日
    作    者   : s46746
    修改内容   : 问题单号:A32D13679,GMM在悬挂状态，如果接收到SM建立请求消息，回复失败
 13.日    期   : 2007年12月28日
    作    者   : s46746
    修改内容   : 根据问题单号：A32D13954,修改GMM在2G3过程中缓存消息机制
 14.日    期   : 2008年7月18日
    作    者   : luojian 00107747
    修改内容   : 根据问题单号：AT2D03887,修改CS无效情况下网络模式变更处理
 15.日    期   : 2008年08月05日
    作    者   : s46746
    修改内容   : 问题单号:AT2D04423,提供短消息模块获取当前PS是否可用的API函数
 16.日    期   : 2008年9月23日
    作    者   : o00132663
    修改内容   : 根据问题单号：AT2D05839,清除无用全局变量 ucRlsMsgFlg和状态GMM_REGISTERED_WAIT_FOR_RAU
 17.日    期   : 2008年9月26日
    作    者   : x00115505
    修改内容   : 问题单号:AT2D05431
 18.日    期    : 2008年10月15日
    作    者    : o00132663
    修改内容    : 问题单号:AT2D06211,增加在GMM_GPRS_SUSPENSION状态时对GMM_TIMER_5S定时器超时的处理。
 19.日    期    : 2009年02月06日
    作    者    : o00132663
    修改内容    : 问题单号:AT2D08277,小区重选导致的网络模式改变后RAU流程异常。
 20.日    期   : 2009年05月14日
    作    者   : h44270
    修改内容   : 问题单号:AT2D11898/AT2D11828,在IDLE态下发送PS域短信，没有按照ATTACH ACCEPT消息中Radio Priority for SMS来请求资源
 21.日    期   : 2009年06月12日
    作    者   : f62575
    修改内容   : 问题单号:AT2D12345,A/Gb接入模式下通过PS域发送短信发送的短信无线优先级比实际值大1
 22.日    期   : 2009年08月19日
    作    者   : x00115505
    修改内容   : 问题单号:AT2D13829,TLLI维护错误
 23.日    期   : 2009年09月12日
    作    者   : s46746
    修改内容   : 问题单号：AT2D14432,HPLMN定时器在异系统重选过程中超时没有立即进行HPLMN搜索
*****************************************************************************/

/*****************************************************************************
   1 头文件包含
*****************************************************************************/

#include "GmmInc.h"
#include "MM_Share.h"
#include "GmmCasGlobal.h"
#include "GmmCasSuspend.h"
#include "GmmCasMain.h"
#include "GmmCasComm.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:luojian 107747;检视人:sunshaohua65952;原因:LOG方案设计需要*/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_CASMAIN_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/



/*****************************************************************************
   2 全局变量定义
******************************************************************************/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*---------------2.1 其他模块内部全局变量 ---------------*/
/*=======================================================*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*---------------2.2 本模块内部全局变量 -----------------*/
/*=======================================================*/
GMM_CAS_CTRL_STRU       gstGmmCasGlobalCtrl;        /* GMM CAS全局控制结构变量 */

GMM_SUSPEND_CTRL_STRU   gstGmmSuspendCtrl;

VOS_UINT8     g_GmmInterRatCellReselect = 0;

/*****************************************************************************
   3 函数实现
******************************************************************************/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*---------------3.1 GMM接收消息处理        -------------*/
/*=======================================================*/

/*****************************************************************************
 Prototype      : GMM_CasMsgProc
 Description    : 双模方式下GMM接收消息的入口函数
                  HSS 4100 V200R001 新增：
                1.处理挂起消息RRMM_SUSPEND_IND
                2.处理挂起恢复消息RRMM_RESUME_IND
                3.处理GSM接入模式下，GMM的接收消息处理
                4.挂起状态下定时器消息的事件分析转换
                5.挂起状态下GMM消息的事件分析转换
 Input          : struct MsgCB*     pMsg            入口消息指针
 Output         :
 Return Value   : GMM_FAILURE       返回失败，
                                    表明没有处理该消息，需要其他消息过程处理
                  GMM_SUCCESS       返回成功
                                    表明处理完成，不需要其他消息过程处理
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
  2.日    期    : 2007年3月30日
    作    者    : s46746
    修改内容    : 问题单号:A32D09854
  3.日    期    : 2007年11月22日
    作    者    : l00107747
    修改内容    : 问题单号:A32D13535
  4.日    期    : 2008年10月15日
    作    者    : o00132663
    修改内容    : 问题单号:AT2D06211,增加在GMM_GPRS_SUSPENSION状态时对GMM_TIMER_5S定时器超时的处理。
  5.日    期   : 2009年5月9日
    作    者   : l00130025
    修改内容   : 根据问题单号：AT2D11645/AT2D11797,关机，若detach的EST_REQ失败，Gmm会反复发起EST_REQ
  6.日    期   : 2011年3月5日
    作    者   : 欧阳飞
    修改内容   : DTS2011030300897，挂起态下T3312超时，未清除相应定时器运行状态全局变量。
  7.日    期   : 2011年8月18日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII调整 HO过程中增加LMM向GMM回复安全上下文回复以及保护定时器超时消息的处理
  8.日    期   : 2011年11月18日
    作    者   : w00167002
    修改内容   : DTS2011110300229:G下CSonly时，背景搜CS失败3次后用户发起ATTACH，
                  失败4此后，用户回RPlmn，发起了PS域的注册。在GMM suspend状态，
                  收到搜网请求后，将GMM状态迁移到搜网状态。
  9.日    期   : 2012年02月29日
    作    者   : l00130025
    修改内容   : DTS2012022906401:L->W Handover SMC在系统消息前收到时没有处理，导致RAU失败
  10.日    期   : 2012年3月7日
    作    者   : w00167002
    修改内容   : V7R1C50 CSFB&PPAC&ETWS&ISR:ST用例CSFB_MO_HO_SUCC001发现在L HO
                  到W后，未上报系统消息，LAU成功，处理用户的电话业务，电话业务
                  被释放后，GMM未清除信令连接.
  11.日    期   : 2012年7月27日
     作    者   : l65478
     修改内容  : DTS2012072305591:L切换到U后第一次RAU失败，PDP drop
  12.日    期   : 2013年02月08日
     作    者   : l00167671
     修改内容   : DTS2013020607201
  13.日    期   : 2013年1月22日
     作    者   : W00176964
     修改内容   : DTS2013012105162:OOS流程收到PS域detach需要进行本地detach

  14.日    期   : 2013年6月5日
     作    者   : w00167002
     修改内容   : V9R1_SVLTE:收到DETACH /ATTACH REQ消息，不进行缓存
  15.日    期   : 2013年08月16日
     作    者   : l65478
     修改内容   : DTS2013091003969,L handover to W后收到鉴权消息没有处理
  16.日    期   : 2014年3月28日
     作    者   : w00242748
     修改内容   : DTS2014032508763:W下正常驻留后，改变支持LTE的能力，W到G进行重选
                  后，GMM发起RAU，报的能力与接入层报的不一致。
*****************************************************************************/
VOS_VOID GMM_CasMsgProc(struct MsgCB* pMsg, VOS_UINT8 *pucFollowOn)
{
    /* 局部变量声明 */
    REL_TIMER_MSG           *pTimerMsg;
    MSG_HEADER_STRU         *pNasMsgHeader;

    /* 消息参数分析 */
    *pucFollowOn = GMM_FALSE;                               /* 默认不再进入原消息入口函数处理 */

    /* Modified by wx270776 for OM融合, 2015-7-16, begin */
    if (WUEPS_PID_ADMIN == pMsg->ulSenderPid)
    /* Modified by wx270776 for OM融合, 2015-7-16, end */
    {
        *pucFollowOn = GMM_TRUE;
        return;
    }

    pNasMsgHeader = (MSG_HEADER_STRU*)pMsg;
    pTimerMsg = (REL_TIMER_MSG*)pMsg;

    /* 处理切换状态下的消息 */
    switch (g_GmmGlobalCtrl.ucState)
    {
        case GMM_SUSPENDED_NORMAL_SERVICE:

            GMM_CasMsgProc_GmmSuspendNormalService(pMsg, pucFollowOn);

            break;

        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            if (WUEPS_PID_MMC == pMsg->ulSenderPid)
            {
                if (MMCGMM_GSM_SYS_INFO_IND == pNasMsgHeader->ulMsgName)
                {
                    if (GMM_TRUE == GMM_IsCasGsmMode())
                    {
                        /* 进入消息分发函数处理此条消息 */
                        GMM_LOG_INFO("GMM_CasMsgProc:Receive MMCGMM_GSM_SYS_INFO_IND in GMM_SUSPENDED_WAIT_FOR_SYSINFO state.");
                        *pucFollowOn = GMM_TRUE;
                        return;
                    }
                }
                else if(MMCGMM_SYS_INFO_IND == pNasMsgHeader->ulMsgName)
                {
                    if (GMM_FALSE == GMM_IsCasGsmMode())
                    {
                        /* 进入消息分发函数处理此条消息 */
                        GMM_LOG_INFO("GMM_CasMsgProc:Receive MMCGMM_SYS_INFO_IND in GMM_SUSPENDED_WAIT_FOR_SYSINFO state.");
                        *pucFollowOn = GMM_TRUE;
                        return;
                    }
                }
                else if (MMCGMM_SUSPEND_IND == pNasMsgHeader->ulMsgName)
                {
                    GMM_LOG_INFO("GMM_CasMsgProc:Receive MMCGMM_SUSPEND_IND in GMM_SUSPENDED_WAIT_FOR_SYSINFO state.");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
                else if (MMCGMM_POWER_OFF_REQ == pNasMsgHeader->ulMsgName)
                {
                    GMM_BufferMsgDump();
                    Gmm_TimerStop(GMM_TIMER_SUSPENDED);
                    Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
                else if (MMCGMM_COVERAGE_LOST_IND == pNasMsgHeader->ulMsgName)
                {
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
                else if (MMCGMM_PLMN_SEARCH_INITIATED == pNasMsgHeader->ulMsgName)
                {
                    *pucFollowOn = GMM_TRUE;
                    return;
                }

                /* 收到MMCGMM_ATTACH_REQ消息，则不进行缓存，而是直接回复Attach成功，
                   待重新驻留可用网络后进行Attach */
                else if ( MMCGMM_ATTACH_REQ == pNasMsgHeader->ulMsgName )
                {
                    *pucFollowOn = GMM_TRUE;
                    return;
                }

                /* 收到MMCGMM_DETACH_REQ消息，则不进行缓存 */
                else if (MMCGMM_DETACH_REQ == pNasMsgHeader->ulMsgName)
                {
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
                else
                {
                }
            }
            else if (UEPS_PID_GAS == pMsg->ulSenderPid)
            {
                if (RRMM_GPRS_SUSPENSION_IND == pNasMsgHeader->ulMsgName)
                {
                    /* 进入消息分发函数处理此条消息 */
                    GMM_LOG_INFO("GMM_CasMsgProc:Receive RRMM_GPRS_SUSPENSION_IND in GMM_SUSPENDED_WAIT_FOR_SYSINFO state.");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }

                if (GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND == pNasMsgHeader->ulMsgName)
                {
                    /* 进入消息分发函数处理此条消息 */
                    GMM_LOG_INFO("GMM_CasMsgProc:Receive GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND in GMM_SUSPENDED_WAIT_FOR_SYSINFO state.");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }

                if (GRRMM_MS_RADIO_ACCESS_CAPABILITIES_TDS_IND == pNasMsgHeader->ulMsgName)
                {
                    /* 进入消息分发函数处理此条消息 */
                    GMM_LOG_INFO("GMM_CasMsgProc:Receive GRRMM_MS_RADIO_ACCESS_CAPABILITIES_TDS_IND in GMM_SUSPENDED_WAIT_FOR_SYSINFO state.");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
            }
            else if (WUEPS_PID_WRR == pMsg->ulSenderPid)
            {
                if (RRMM_SECURITY_IND == pNasMsgHeader->ulMsgName)
                {
                    *pucFollowOn = GMM_TRUE;
                    return;
                }

                if (RRMM_REL_IND == pNasMsgHeader->ulMsgName)
                {
                    /* 进入消息分发函数处理此条消息 */
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
            }
            else
            {
                if (RRMM_REL_IND == pNasMsgHeader->ulMsgName)
                {
                    /* 进入消息分发函数处理此条消息 */
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
            }
            if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
             && (MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause)
             && (NAS_MML_NET_RAT_TYPE_GSM   == gstGmmSuspendCtrl.ucPreRat))
            {
                if (WUEPS_PID_SM == pMsg->ulSenderPid)
                {
                    if (GMMSM_DATA_REQ == pNasMsgHeader->ulMsgName)
                    {
                        *pucFollowOn = GMM_TRUE;
                        return;
                    }
                }
                else if (WUEPS_PID_SMS == pMsg->ulSenderPid)
                {
                    if (PMMSMS_EST_REQ == pNasMsgHeader->ulMsgName)
                    {
                        *pucFollowOn = GMM_TRUE;
                        return;
                    }
                }
                else if (WUEPS_PID_RABM == pMsg->ulSenderPid)
                {
                    if (ID_RABM_GMM_REESTABLISH_REQ == pNasMsgHeader->ulMsgName)
                    {
                        *pucFollowOn = GMM_TRUE;
                        return;
                    }
                }
                else
                {
                }
            }
            GMM_SuspendMsgProc(pMsg, pucFollowOn);
            break;

        case GMM_GPRS_SUSPENSION:
        case GMM_SUSPENDED_GPRS_SUSPENSION:
            if (UEPS_PID_GAS == pMsg->ulSenderPid)
            {
                if (RRMM_GPRS_RESUME_IND == pNasMsgHeader->ulMsgName)
                {
                    /* 进入消息分发函数处理此条消息 */
                    GMM_LOG_INFO("GMM_CasMsgProc:Receive RRMM_GPRS_RESUME_IND in GMM_GPRS_SUSPENSION state.");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }

                if (GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND == pNasMsgHeader->ulMsgName)
                {
                    /* 进入消息分发函数处理此条消息 */
                    GMM_LOG_INFO("GMM_CasMsgProc:Receive GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND in GMM_SUSPENDED_WAIT_FOR_SYSINFO state.");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }

                if (GRRMM_MS_RADIO_ACCESS_CAPABILITIES_TDS_IND == pNasMsgHeader->ulMsgName)
                {
                    /* 进入消息分发函数处理此条消息 */
                    GMM_LOG_INFO("GMM_CasMsgProc:Receive GRRMM_MS_RADIO_ACCESS_CAPABILITIES_TDS_IND in GMM_SUSPENDED_WAIT_FOR_SYSINFO state.");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
            }
            else if (WUEPS_PID_MMC == pMsg->ulSenderPid)
            {
                /* 提取函数降圈复杂度 */
                if (VOS_TRUE == NAS_GMM_RcvMmcMsg_PreProc_GprsSuspension(pMsg, pucFollowOn))
                {
                    return;
                }
            }
            else if (VOS_PID_TIMER == pMsg->ulSenderPid)
            {
                if (GMM_TIMER_T3314 == pTimerMsg->ulName)
                {
                    /* 进入消息分发函数处理此条消息 */
                    GMM_LOG_INFO("GMM_CasMsgProc:Ready time expired in GMM_GPRS_SUSPENSION state.");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
                else if (GMM_TIMER_T3312 == pTimerMsg->ulName)
                {
                    gstGmmSuspendCtrl.ucT3312State = GMM_T3312_TIMEOUT;
                    Gmm_TimerStop(GMM_TIMER_T3312);
#if (FEATURE_LTE == FEATURE_ON)
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_EXP);
#endif
                    return;
                }
                else if (GMM_TIMER_1S == pTimerMsg->ulName)
                {
                    /* 进入消息分发函数处理此条消息 */
                    GMM_LOG_INFO("GMM_CasMsgProc:GMM_TIMER_5S timer expired in GMM_GPRS_SUSPENSION state");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
                else
                {
                }
            }
            else
            {
            }

            /* 其他消息全部缓存 */
            GMM_SuspendMsgProc(pMsg, pucFollowOn);
            break;
        default:
            *pucFollowOn = GMM_TRUE;
            break;
    }
    return;
}

/*****************************************************************************
 函 数 名  : GMM_SaveMsg
 功能描述  : GMM缓冲收到的消息
 输入参数  : VOS_VOID *pMsg           - 收到的消息指针
 输出参数  : VOS_UINT8 *pucFollowOn   - 是否还需要进一步处理标志
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月17日
    作    者   : 欧阳飞
    修改内容   : 新生成函数
  2.日    期   : 2010年10月29日
    作    者   : l00167671/罗开辉
    修改内容   : 问题单号：DTS2010100802035,添加对GMMSM_PDP_DEACTIVATED_IND的缓存
  3.日    期   : 2011年03月3日
    作    者   : f00179208
    修改内容   : 问题单号：DTS2011022800037，G下ping包，然后打电话，切换到W失败后多次回退到G，挂断电话.ping包比其他场景恢复慢
  4. 日    期   : 2011年7月10日
     作    者   : w00166186
     修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  5. 日    期   : 2011年12月01日
     作    者   : w00166186
     修改内容   : DTS2011112400118,CS语音过程发起PS ATTACH，后处理缓存时返回ERROR
  6. 日    期   : 2012年4月20日
     作    者   : l00130025
     修改内容   : DTS2012031502528，GMM GPRS Suspension状态没有处理LuRsltInd，
                  W->G Rej 11->W原小区时,没有做Attach，导致后续SM业务失败

 7.  日    期   : 2012年11月08日
	 作    者   : l00167671
     修改内容   : DTS2012110508357,SUSPENSION状态时收到CS ONLY的设置如果GAS resume ind失败，不会做detach
*****************************************************************************/
VOS_VOID GMM_SaveMsg(VOS_VOID *pMsg, VOS_UINT8 *pucFollowOn)
{
    MSG_HEADER_STRU         *pNasMsgHeader;

    pNasMsgHeader = (MSG_HEADER_STRU*)pMsg;

    switch (pNasMsgHeader->ulSenderPid)
    {
    case WUEPS_PID_USIM:
        /*鉴权回应消息，清除标志停定时器，丢弃，重新成功后会重新发起响应流程，
          回退等待网络重发鉴权*/
        if (USIMM_AUTHENTICATION_CNF == pNasMsgHeader->ulMsgName)
        {
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                           /* 停保护Timer                              */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;         /* 清等待标志                               */
            GMM_LOG_NORM("GMM_SaveMsg:Receive USIM AUTHENTICATION CNF,Discard.");
        }
        break;

    case WUEPS_PID_WRR:/*RRC_NAS_AP_CLASS:
 */
        GMM_LOG_WARN("GMM_SaveMsg:Receive unexpected msg of RRC.");
        break;

    case WUEPS_PID_RABM:/*GMM_RABM_AP_CLASS:
 */
        if (ID_RABM_GMM_REESTABLISH_REQ == pNasMsgHeader->ulMsgName)
        {
            /*GMM_BufferMsgReceive(pMsg);*/
            /* 切换后处于W网络才处理RABM消息，G网络下无RABM */
            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
            {
                /* 如果切换之前有被中断的Detach流程，则不缓存RABM的重建请求 */
                if ((GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
                    && ((GMM_DETACH_COMBINED == g_GmmGlobalCtrl.ucSpecProcHold)
                     || (GMM_DETACH_NORMAL == g_GmmGlobalCtrl.ucSpecProcHold)
                     || (GMM_DETACH_NORMAL_NETMODE_CHANGE == g_GmmGlobalCtrl.ucSpecProcHold)
                     || (GMM_DETACH_WITH_IMSI == g_GmmGlobalCtrl.ucSpecProcHold)))
                {
                    Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);     /* 发送GMMRABM_REESTABLISH_CNF(fail)        */
                }
                else
                {
                    g_GmmGlobalCtrl.ucFollowOnFlg       = GMM_TRUE;
                    g_GmmGlobalCtrl.ucSpecProcHold      = GMM_SERVICE_REQUEST_DATA_IDLE;
                    NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

                    #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
                    g_GmmGlobalCtrl.usUplinkDataStatus  = ((GMMRABM_REESTABLISH_REQ_STRU *)pMsg)->usUplinkDataStatus;
                    #endif
                }
            }
            else
            {
                Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);         /* 发送GMMRABM_REESTABLISH_CNF(fail)        */
                GMM_LOG_NORM("GMM_SaveMsg:Receive Rabm Reestablish In 2G,Discard.");
            }
        }
        /* RAU RSP消息，*/
        else if (ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP == pNasMsgHeader->ulMsgName)
        {
            Gmm_TimerStop(GMM_TIMER_RAU_RSP);
        }
        else
        {
        }
        break;

    case WUEPS_PID_MMC:/*MMC_GMM_AP_CLASS:
 */
        switch (pNasMsgHeader->ulMsgName)
        {
            case MMCGMM_REGISTER_INITIATION:
            case MMCGMM_REL_REQ:
                *pucFollowOn = GMM_TRUE;
                break;
            case MMCGMM_ATTACH_REQ:
                g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
                GMM_BufferMsgReceive((struct MsgCB *)pMsg);
                break;
            case MMCGMM_DETACH_REQ:
                NAS_GMM_SaveDetachMsg(pMsg);
                break;

            case MMCGMM_MODE_CHANGE_REQ:
                GMM_BufferMsgReceive((struct MsgCB *)pMsg);
                break;
            default:
                GMM_LOG_WARN("GMM_SaveMsg:Receive unexpected msg of MMC.");
                break;
        }
        break;

    case WUEPS_PID_MM:
        switch (pNasMsgHeader->ulMsgName)
        {
            case MMGMM_CS_CONNECT_IND:
            case MMGMM_CM_SERVICE_REJECT_IND:
            case MMGMM_AUTHENTICATON_FAILURE_IND:
            case MMGMM_LU_RESULT_IND:

                *pucFollowOn = GMM_TRUE;
                break;

            default:
                 break;
        }
        break;

    case WUEPS_PID_SM:/*GMM_SM_AP_CLASS:
 */
        switch (pNasMsgHeader->ulMsgName)
        {
            case GMMSM_ESTABLISH_REQ:
            case GMMSM_PDP_DEACTIVATED_IND:
                GMM_BufferMsgReceive((struct MsgCB *)pMsg);
                break;
            case GMMSM_DATA_REQ:
                /*GMM_BufferMsgReceive(pMsg);*/
                g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
                NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

                g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;
                Gmm_BufSmDataReqMsg(pMsg);
                break;
            case GMMSM_PDP_STATUS_IND:
                Gmm_RcvSmPdpStatusInd(pMsg);
                break;
            default :
                GMM_LOG_WARN("GMM_SaveMsg:Receive unexpected msg of SM.");
                break;
        }
        break;

    case WUEPS_PID_SMS:/*GMM_SMS_AP_CLASS:
 */
        switch (pNasMsgHeader->ulMsgName)
        {
            case PMMSMS_EST_REQ:
                Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
                break;
            case PMMSMS_UNITDATA_REQ:
                GMM_BufferMsgReceive((struct MsgCB *)pMsg);
                break;
            default :
                GMM_LOG_WARN("GMM_SaveMsg:Receive unexpected msg of SMS.");
                break;
        }
        break;

    case UEPS_PID_LL:/*LLC_GMM_AP_CLASS:
 */
        GMM_LOG_WARN("GMM_SaveMsg:Receive unexpected msg of LLC.");
        break;
    case UEPS_PID_GAS:/*GAS_GMM_AP_CLASS:
 */
        GMM_LOG_WARN("GMM_SaveMsg:Receive unexpected msg of GAS.");
        break;
    default :
        GMM_LOG_WARN("GMM_SaveMsg:Receive unexpected msg of others.");
        break;
    }
}

/*****************************************************************************
 函 数 名  : GMM_SuspendMsgProc
 功能描述  : GMM挂起态下收到消息的处理
 输入参数  : struct MsgCB* pMsg           - 收到的消息指针
 输出参数  : VOS_UINT8     *pucFollowOn   - 是否还需要进一步处理标志
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月17日
    作    者   : 欧阳飞
    修改内容   : 新生成函数
  2.日    期   : 2011年3月5日
    作    者   : 欧阳飞
    修改内容   : DTS2011030300897，挂起态下T3312超时，未清除相应定时器运行状态全局变量。
  3.日    期   : 2011年8月18日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII调整 HO过程中增加LMM向GMM回复安全上下文回复以及保护定时器超时消息的处理
  4.日    期   : 2011年11月22日
    作    者   : w00166186
    修改内容   : DTS2011112301504,BT测试W2G_HO失败
  5.日    期   :2014年4月2日
    作    者   :w00242748
    修改内容   :DTS2014040310584:LTE下未与网络交互的ATTACH/TAU，不停止T3211/T3212/T3213;
                只有与网络交互后，才将T3211/T3212/T3213停止。
  6.日    期   : 2014年12月25日
    作    者   : w00167002
    修改内容   : DTS2014122201960:在L下SRVCC HO到G再HO到W,RABM触发重建，导致立即
                 触发RAU，后续收到系统消息又再次发起RAU,导致网络REL了链路，导致
                 掉话。修改为在HO后，启动保护定时器等系统消息。
*****************************************************************************/
VOS_VOID GMM_SuspendMsgProc(struct MsgCB* pMsg, VOS_UINT8 *pucFollowOn)
{
    /* 局部变量声明 */
    REL_TIMER_MSG           *pTimerMsg;

    if (VOS_PID_TIMER == pMsg->ulSenderPid)
    {
        pTimerMsg = (REL_TIMER_MSG*)pMsg;
        if ((GMM_TIMER_SUSPENDED == pTimerMsg->ulName) || (GMM_TIMER_T3314 == pTimerMsg->ulName) || (GMM_TIMER_TC_DELAY_SUSPEND_RSP == pTimerMsg->ulName) || (GMM_TIMER_T3323 == pTimerMsg->ulName))
        {
            *pucFollowOn = GMM_TRUE;
            return;
        }
        else if (GMM_TIMER_T3312 == pTimerMsg->ulName)
        {
            gstGmmSuspendCtrl.ucT3312State = GMM_T3312_TIMEOUT;
            Gmm_TimerStop(GMM_TIMER_T3312);
#if (FEATURE_LTE == FEATURE_ON)
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_EXP);
#endif
            return;
        }
        /* 挂起状态下需要处理LMM的安全上下文回复消息 */
#if (FEATURE_ON == FEATURE_LTE)
        else if (GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF == pTimerMsg->ulName)
        {
            *pucFollowOn = GMM_TRUE;
            GMM_LOG_INFO("GMM_SuspendMsgProc:Receive GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF in SUSPENDED_NORMAL_SERVICE state.");
            return;
        }
#endif

        else if (GMM_TIMER_HO_WAIT_SYSINFO == pTimerMsg->ulName)
        {
            *pucFollowOn = GMM_TRUE;
            GMM_LOG_INFO("GMM_SuspendMsgProc:Receive GMM_TIMER_HO_WAIT_SYSINFO in SUSPENDED_NORMAL_SERVICE state.");
            return;

        }

        else
        {
            GMM_LOG_WARN("GMM_SuspendMsgProc:Receive unexpected timer expired msg.");
            return;
        }
    }

    GMM_SaveMsg((VOS_VOID *)pMsg, pucFollowOn);

    return;
}

/*****************************************************************************
 Prototype      : GMM_CasNetModeChangeByRau
 Description    : 网络模式改变时GMM需要进行的RAU操作
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2006-07-26
    Author      : Roger Leo
    Modification: Created function
  2.日    期   : 2006年9月19日
    作    者   : liurui id:40632
    修改内容   : 根据问题单号：A32D05237
  3.日    期   : 2006年11月20日
    作    者   : s46746
    修改内容   : 根据问题单号：A32D07433
  4.日    期   : 2008年7月18日
    作    者   : luojian 00107747
    修改内容   : 根据问题单号：AT2D03887
  5.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  6.日    期   : 2014年3月14日
    作    者   : w00176964
    修改内容   : DTS2014031207844:dereg_init状态时NMO改变且LARA改变时按照24008协议需要进行RAU
*****************************************************************************/
VOS_VOID GMM_CasNetModeChangeByRau(
                GMM_NETMODE_CHG_TYPE ucNetChgTyp,
                VOS_UINT8            ucRaiChgFlg)
{
    VOS_UINT8                           ucSimCsRegStatus;
    VOS_UINT8                           ucCsAttachAllow;

    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
    ucCsAttachAllow  = NAS_MML_GetCsAttachAllowFlg();

    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
    case GMM_REGISTERED_PLMN_SEARCH:
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);

        if ((GMM_NETMODE_CHG_I_II == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_I_III == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_II_III == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_II == ucNetChgTyp))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
        }
        else if ((GMM_NETMODE_CHG_II_I == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_I == ucNetChgTyp))
        {
            if ((VOS_TRUE != ucSimCsRegStatus)
             || (VOS_FALSE == ucCsAttachAllow))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }
            else
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
            }
        }
        else
        {
        }

        break;

    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        Gmm_TimerStop(GMM_TIMER_T3321);
        Gmm_TimerStop(GMM_TIMER_PROTECT);
        Gmm_TimerStop(GMM_TIMER_T3318);
        Gmm_TimerStop(GMM_TIMER_T3320);
        g_GmmReqCnfMng.ucCnfMask = 0;

        if ((GMM_NETMODE_CHG_I_II == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_I_III == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_II_III == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_II == ucNetChgTyp))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
        }
        else if ((GMM_NETMODE_CHG_II_I == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_I == ucNetChgTyp))
        {
            if ((VOS_TRUE != ucSimCsRegStatus)
             || (VOS_FALSE == ucCsAttachAllow))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }
            else
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
            }
        }
        else
        {
        }
        break;

    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);
        Gmm_TimerStop(GMM_TIMER_T3317);
        Gmm_TimerStop(GMM_TIMER_PROTECT);
        Gmm_TimerStop(GMM_TIMER_T3318);
        Gmm_TimerStop(GMM_TIMER_T3320);
        g_GmmReqCnfMng.ucCnfMask = 0;
        if ((GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProc)
         || (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc))
        {/* 当前流程为SR_DATA */
            g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;        /* 保留被中断的SR流程                       */
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;                           /* 设置follow on标志                        */
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);
        }

        if ((GMM_NETMODE_CHG_I_II == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_I_III == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_II_III == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_II == ucNetChgTyp))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
        }
        else if ((GMM_NETMODE_CHG_II_I == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_I == ucNetChgTyp))
        {
            if ((VOS_TRUE !=  ucSimCsRegStatus)
             || (VOS_FALSE == ucCsAttachAllow))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }
            else
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
            }
        }
        else
        {
        }

        break;

    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        /* 当前RAU终止后发起新的RAU */
        Gmm_TimerStop(GMM_TIMER_T3330);
        Gmm_TimerStop(GMM_TIMER_T3318);
        Gmm_TimerStop(GMM_TIMER_T3320);
        if ((GMM_NETMODE_CHG_I_II == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_I_III == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_II_III == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_II == ucNetChgTyp))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
        }
        else if ((GMM_NETMODE_CHG_II_I == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_I == ucNetChgTyp))
        {
            if ((VOS_TRUE !=  ucSimCsRegStatus)
             || (VOS_FALSE == ucCsAttachAllow))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }
            else
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);

            }
        }
        else
        {
        }

        break;

    case GMM_REGISTERED_INITIATED:

        if (GMM_FALSE == ucRaiChgFlg)
        {/* RA未改变，当前RAU完成后再发起新的RAU */
            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;
            return;
        }
        /* RA改变，当前RAU终止后发起新的RAU */
        Gmm_TimerStop(GMM_TIMER_T3310);
        Gmm_TimerStop(GMM_TIMER_T3318);
        Gmm_TimerStop(GMM_TIMER_T3320);
        NAS_MML_SetPsAttachAllowFlg( VOS_TRUE );      /* 设置注册允许标志 */
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);

        break;

    case GMM_DEREGISTERED_INITIATED:

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

        if ((GMM_NETMODE_CHG_I_II == ucNetChgTyp)
         || (GMM_NETMODE_CHG_I_III == ucNetChgTyp)
         || (GMM_NETMODE_CHG_II_III == ucNetChgTyp)
         || (GMM_NETMODE_CHG_III_II == ucNetChgTyp))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
        }
        else if ((GMM_NETMODE_CHG_II_I == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_I == ucNetChgTyp))
        {
            if ((VOS_TRUE !=  ucSimCsRegStatus)
             || (VOS_FALSE == ucCsAttachAllow))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }
            else
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
            }
        }
        else
        {
        }

        break;

    case GMM_DEREGISTERED_NORMAL_SERVICE:
    case GMM_DEREGISTERED_PLMN_SEARCH:
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
            "GMM_CasNetModeChangeByRau:WARNING: not surpport NetMode Change!");
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
               "GMM_CasNetModeChangeByRau:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }
    return;
}

/*****************************************************************************
 Prototype      : GMM_CasGetNetChgType
 Description    : 判断异系统切换网络模式的改变类型
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.日    期   : 2006年10月9日
    作    者   : s46746
    修改内容   : 创建，根据问题单号：A32D05744
*****************************************************************************/
VOS_UINT8 GMM_CasGetNetChgType(VOS_UINT8 ucNewNetMod)
{
    GMM_NETMODE_CHG_TYPE   ucNetChgType = GMM_NETMODE_CHG_NULL;

    if (GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod)
    {
        if (GMM_NET_MODE_II == ucNewNetMod)
        {
            ucNetChgType = GMM_NETMODE_CHG_I_II;
        }
        else if (GMM_NET_MODE_III == ucNewNetMod)
        {
            ucNetChgType = GMM_NETMODE_CHG_I_III;
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                    "GMM_CasGetNetChgType:WARNING: New Netmode is incorrect!");
        }
    }
    else if (GMM_NET_MODE_II == g_GmmGlobalCtrl.SysInfo.ucNetMod)
    {
        if (GMM_NET_MODE_I == ucNewNetMod)
        {
            ucNetChgType = GMM_NETMODE_CHG_II_I;
        }
        else if (GMM_NET_MODE_III == ucNewNetMod)
        {
            ucNetChgType = GMM_NETMODE_CHG_II_III;
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                    "GMM_CasGetNetChgType:WARNING: New Netmode is incorrect!");
        }
    }
    else if (GMM_NET_MODE_III == g_GmmGlobalCtrl.SysInfo.ucNetMod)
    {
        if (GMM_NET_MODE_I == ucNewNetMod)
        {
            ucNetChgType = GMM_NETMODE_CHG_III_I;
        }
        else if (GMM_NET_MODE_II == ucNewNetMod)
        {
            ucNetChgType = GMM_NETMODE_CHG_III_II;
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                    "GMM_CasGetNetChgType:WARNING: New Netmode is incorrect!");
        }
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                    "GMM_CasGetNetChgType:WARNING: Old Netmode is incorrect!");
    }

    return ucNetChgType;
}

/*****************************************************************************
 Prototype      : GMM_ProcedureByNetMode
 Description    : 判断异系统切换网络模式的改变类型
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.日    期   : 2006年10月9日
    作    者   : s46746
    修改内容   : 创建，根据问题单号：A32D05744
  2.日    期   : 2006年11月20日
    作    者   : s46746
    修改内容   : 创建，根据问题单号：A32D07433
*****************************************************************************/
VOS_VOID GMM_ProcedureByNetMode(VOS_UINT8 ucNetModChangeType)
{
    if (GMM_NETMODE_CHG_I_II == ucNetModChangeType)
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
    else if ((GMM_NETMODE_CHG_I_III == ucNetModChangeType)
          || (GMM_NETMODE_CHG_II_III == ucNetModChangeType))
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
    else if (GMM_NETMODE_CHG_II_I == ucNetModChangeType)
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
    }
    else if (GMM_NETMODE_CHG_III_I == ucNetModChangeType)
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
    }
    else if (GMM_NETMODE_CHG_III_II == ucNetModChangeType)
    {
        if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
        {
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                    "GMM_ProcedureByNetMode:WARNING: Netmode change type is incorrect!");
    }
}

/*****************************************************************************
 Prototype      : GMM_CasChangSysMode
 Description    : 切换到指定的网络模式，2G/3G
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-25
    Author      : Roger Leo
    Modification: Created function

  2. x51137 2006/4/28 A32D02889
  3.日    期    : 2009年03月18日
    作    者    : l65478
    修改内容    : 根据问题单号：AT2D08671,数传状态下，W出服务区后，切到G，数传恢复失败，因为GMM没有配置LL加密算法
*****************************************************************************/
VOS_VOID GMM_CasChangSysMode(VOS_UINT8 ucState)
{
    /* 与最近的网络模式相同，不做改变处理 */
    /*if (ulState == gstGmmCasGlobalCtrl.ulGmmCasPreState)*/
    /*{*/
    /*    return;*/
    /*}*/

    /* 新模式下系统状态描述初始化 */
    if (NAS_MML_NET_RAT_TYPE_GSM == ucState)
    {/* 切换到2G接入模式 */
        /* 系统CAS状态维护 */
        gstGmmCasGlobalCtrl.ucGmmCasPreState
                    = gstGmmCasGlobalCtrl.ucGmmCasState;
        gstGmmCasGlobalCtrl.ucGmmCasState
                    = GMM_CAS_GSM_AS;

        /* TLLI初始化 */
        gstGmmCasGlobalCtrl.ulTLLI    = 0xffffffff;         /* 无效TLLI值 */
        gstGmmCasGlobalCtrl.ulOldTLLI = 0xffffffff;         /* 无效TLLI值 */
        gstGmmCasGlobalCtrl.ucflgTLLI = GMM_INVALID_TLLI;   /* 置TLLI无效标志 */
        gstGmmCasGlobalCtrl.ucTlliAssignFlg = GMM_FALSE;    /* 未完成TLLI指配 */

        /* READY TIMER初始化 */
        /*gstGmmCasGlobalCtrl.ulReadyTimerValue
            = GMM_TIMER_T3314_VALUE * GMM_TIMER_T3314_CNT*/;                      /* 默认值 */
        /*gstGmmCasGlobalCtrl.ulReadyTimerCntMax = GMM_TIMER_T3314_CNT*/;           /* 默认值 */
        /* gstGmmCasGlobalCtrl.ulReadyTimerCnt    = 0;  */       /* 计数器清零 */
        gstGmmCasGlobalCtrl.ucReadyTimerNgtFlg = GMM_FALSE;  /* 允许协商标志 */

        /* 2G过程变量和标志复位 */
        gstGmmCasGlobalCtrl.ucRabmResumeFlg = GMM_FALSE;
        gstGmmCasGlobalCtrl.ucRauCmpFlg     = GMM_FALSE;
        gstGmmCasGlobalCtrl.ucGprsCipherAlg = LL_GEA0;      /* 无加密算法 */

        NAS_GMM_SndMmcCipherInfoInd();

        gstGmmCasGlobalCtrl.ucCellNotifyFlg = GMM_FALSE;
        gstGmmCasGlobalCtrl.ucFtsFlg        = GMM_FALSE;
        gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        gstGmmCasGlobalCtrl.ucSysRauFlg     = GMM_FALSE;

        g_GmmGlobalCtrl.ucSigConFlg         = GMM_TRUE;
    }
#if 0
    else if (GMM_CAS_WCDMA_AS == ulState)
    {/* 切换到3G接入模式 */
        /* 系统CAS状态维护 */
        gstGmmCasGlobalCtrl.ucGmmCasPreState
                    = gstGmmCasGlobalCtrl.ucGmmCasState;
        gstGmmCasGlobalCtrl.ucGmmCasState
                    = GMM_CAS_WCDMA_AS;

        /* TLLI 3G网络不使用，保持不变 */
        /* READY TIMER 3G网络不使用，保持不变 */
        /* 2G过程变量和标志3G网络不使用，保持不变 */
        gstGmmCasGlobalCtrl.ucSysRauFlg     = GMM_FALSE;
        g_GmmGlobalCtrl.ucSigConFlg         = GMM_FALSE;
    }
    else
    {/* 切换到SUSPEND模式 */
        /* 置GMM CAS状态 */
        gstGmmCasGlobalCtrl.ucGmmCasPreState
            = gstGmmCasGlobalCtrl.ucGmmCasState;
        gstGmmCasGlobalCtrl.ucGmmCasState
            = GMM_CAS_SUSPEND;

        /* 准备进行消息缓存，通知CM层模块挂起指示 */
        Gmm_TimerStart(GMM_TIMER_BUFFER_QUEUE);
        GMM_SndRabmSuspendInd();                /* 通知RABM CAS挂起消息*/
        return;
    }

    /* 开机启动消息后，不需要上报RAU过程信息 */
    if (GMM_NULL == g_GmmGlobalCtrl.ucState)
    {
        return;
    }

    /* inter-system change后的RA update过程 */
    GMM_CasGetRauType(&ucRauType, ulState);
    GMM_CasExecRauInSysChg(ucRauType);
#endif

    gstGmmCasGlobalCtrl.ucGprsCipherAssign    = VOS_FALSE;  /* 加密算法没有支配 */
    gstGmmCasGlobalCtrl.ucGprsCipher          = VOS_FALSE;

    NAS_GMM_SndMmcCipherInfoInd();

    return;
}

/**************************************/
/* 其它外部模块(RABM,APS)调用接口     */
/**************************************/
/*****************************************************************************
 Prototype      : GMM_GetCurNetwork
 Description    : 获取GMM的当前工作网络
                  HSS 4100 V200R001 新增
                  非GMM模块使用
 Input          :
 Output         :
 Return Value   : 当前驻留的接入技术
                  GMM_GMM_NET_RAT_TYPE_WCDMA  3G网络
                  GMM_GMM_NET_RAT_TYPE_GSM    2G网络
                  GMM_GMM_NET_RAT_TYPE_LTE
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-08
    Author      : Roger Leo
    Modification: Created function
  2.日    期    : 2011年11月28日
    作    者    : z00161729
    修改内容    : 增加L模的判断
*****************************************************************************/
VOS_UINT8 GMM_GetCurNetwork (VOS_VOID)
{
    /* 明确的网络接入模式 */
    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        return NAS_GMM_NET_RAT_TYPE_GSM;
    }
    else if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        return NAS_GMM_NET_RAT_TYPE_WCDMA;
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        return NAS_GMM_NET_RAT_TYPE_LTE;
    }
#endif
    else
    {
        /* 其他状态默认网络模式为3G */
        return NAS_GMM_NET_RAT_TYPE_WCDMA;
    }
}

/*****************************************************************************
 Prototype      : GMM_GetTlli
 Description    : 获取GMM的当前TLLI值
                  HSS 4100 V200R001 新增
                  非GMM模块使用
 Input          :
 Output         :
 Return Value   : GMM当前使用的TLLI值
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-08
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT32 GMM_GetTlli (VOS_VOID)
{
    return gstGmmCasGlobalCtrl.ulTLLI;
}

/*****************************************************************************
 Prototype      : GMM_ServiceStatusForSms
 Description    : 获取GMM的当前服务是否可用

 Input          :
 Output         :
 Return Value   : GMM当前服务是否可用
 Calls          :
 Called By      :

 History        :
  1.Date        : 2008-07-31
    Author      : s46746
    Modification: Created function
  2.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV支持L下发短信修改
  3.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
  4.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : NAS_MML_GetPsRestrictNormalServiceFlg修改函数名
  5.日    期   : 2013年08月16日
    作    者   : l65478
    修改内容   : DTS2013091003969,L handover to W后收到鉴权消息没有处理
*****************************************************************************/
VOS_UINT32 GMM_ServiceStatusForSms(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        /* 当前驻留L模，无需判断GMM状态 */
        return GMM_SMS_SERVICE_AVAILABLE;
    }
    else
#endif
    {
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
        if (VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
        {
            return GMM_SMS_SERVICE_UNAVAILABLE;
        }

        if ((MM_COM_SRVST_NORMAL_SERVICE == NAS_GMM_GetRegUptNeededPsSrvStatus())
         && (GMM_REGISTERED_UPDATE_NEEDED == g_GmmGlobalCtrl.ucState))
        {
            return GMM_SMS_SERVICE_UNAVAILABLE;
        }

        switch (g_GmmGlobalCtrl.ucState)
        {
            case GMM_ROUTING_AREA_UPDATING_INITIATED:
            case GMM_SERVICE_REQUEST_INITIATED:
            case GMM_REGISTERED_NORMAL_SERVICE:
            case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
            case GMM_REGISTERED_IMSI_DETACH_INITIATED:
                return GMM_SMS_SERVICE_AVAILABLE;
            case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
                /* 在从G切换到W,SMS可以把业务通知GMM,由GMM触发一次RAU过程 */
                if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
                 && (MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause)
                 && (NAS_MML_NET_RAT_TYPE_GSM   == gstGmmSuspendCtrl.ucPreRat))
                {
                    return GMM_SMS_SERVICE_AVAILABLE;
                }
                else
                {
                    return GMM_SMS_SERVICE_UNAVAILABLE;
                }
            default:
                return GMM_SMS_SERVICE_UNAVAILABLE;
        }
    }
}

/*****************************************************************************
 Prototype      : GMM_GetRaPrioForSms
 Description    : 获取GMM的当前Radio priority for SMS 值
                  非GMM模块使用
 Input          :
 Output         :
 Return Value   : GMM当前使用的Radio priority for SMS 值
 Calls          :
 Called By      :

 History        :
  1.Date        : 2009-5-13
    Author      : h44270
    Modification: Created function
  2.日    期   : 2013年6月05日
    作    者   : Y00213812
    修改内容   : DTS2013060507591,COVERITY和FORITY修改
*****************************************************************************/
VOS_UINT8 GMM_GetRaPrioForSms (VOS_VOID)
{
    VOS_UINT8   ucRaPrioLevFosSms;

    ucRaPrioLevFosSms = gstGmmCasGlobalCtrl.enRaPrioLevFosSms - 1;
    return ucRaPrioLevFosSms;

}

/*****************************************************************************
 函 数 名  : GMM_CasMsgProc_GmmSuspendNormalService
 功能描述  : GMM在GmmSuspendNormalService状态收到消息的处理
 输入参数  : pMsg        - 收到消息
 输出参数  : pucFollowOn - follow on标志
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月17日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID GMM_CasMsgProc_GmmSuspendNormalService(
    struct MsgCB                       *pMsg,
    VOS_UINT8                          *pucFollowOn
)
{
    /* 局部变量声明 */
    MSG_HEADER_STRU         *pNasMsgHeader;

    RRMM_DATA_IND_FOR_PCLINT_STRU  *pstRrmmDataInd          = VOS_NULL_PTR;
    NAS_MSG_FOR_PCLINT_STRU        *pstNasMsg               = VOS_NULL_PTR;
    LL_NAS_UNITDATA_IND_MSG        *pstLLUnitDataInd        = VOS_NULL_PTR;

    pstRrmmDataInd = (RRMM_DATA_IND_FOR_PCLINT_STRU *)pMsg;
    pstNasMsg      = &pstRrmmDataInd->RcvNasMsg;
    pstLLUnitDataInd = (LL_NAS_UNITDATA_IND_MSG *)pMsg;

    /* 消息参数分析 */
    *pucFollowOn = GMM_FALSE;                                                   /* 默认不再进入原消息入口函数处理 */

    pNasMsgHeader = (MSG_HEADER_STRU*)pMsg;


    if (WUEPS_PID_MMC == pMsg->ulSenderPid)
    {
        if (MMCGMM_RESUME_IND == pNasMsgHeader->ulMsgName)
        {
            GMM_LOG_INFO("GMM_CasMsgProc:Receive MMCGMM_RESUME_IND in SUSPENDED_NORMAL_SERVICE state.");
            /* 进入消息分发函数处理此条消息 */
            *pucFollowOn = GMM_TRUE;
            return;
        }

        if (MMCGMM_POWER_OFF_REQ == pNasMsgHeader->ulMsgName)
        {
            GMM_BufferMsgDump();
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
            *pucFollowOn = GMM_TRUE;
            return;
        }

        if (MMCGMM_DETACH_REQ == pNasMsgHeader->ulMsgName)
        {
            *pucFollowOn = GMM_TRUE;
            return;
        }


        /* 收到MMCGMM_ATTACH_REQ消息，则不进行缓存，而是直接回复Attach成功，
           待重新驻留可用网络后进行Attach */
        if ( MMCGMM_ATTACH_REQ == pNasMsgHeader->ulMsgName )
        {
            *pucFollowOn = GMM_TRUE;
            return;
        }
    }
    else if (WUEPS_PID_WRR == pMsg->ulSenderPid)
    {
        /* 挂起状态收到REL_IND GMM需要处理:清除并通知MMC信令连接标志 */
        if (RRMM_REL_IND == pNasMsgHeader->ulMsgName)
        {
            *pucFollowOn = GMM_TRUE;
            GMM_LOG_INFO("GMM_CasMsgProc:Receive RRMM_REL_IND in SUSPENDED_NORMAL_SERVICE state.");
            return;
        }


        /* 透传给SM当前DATA_IND消息 */
        if ( (RRMM_DATA_IND == pNasMsgHeader->ulMsgName)
          && (GMM_PD_SM     == (pstNasMsg->aucNasMsg[0] & 0x0F)) )
        {
            *pucFollowOn = GMM_TRUE;
            GMM_LOG_INFO("GMM_CasMsgProc:Receive RRMM_DATA_IND in SUSPENDED_NORMAL_SERVICE state.");
            return;
        }
    }
    else if (UEPS_PID_LL == pMsg->ulSenderPid)
    {
        /* LL透传给SM当前DATA_IND消息 */
        if ( (ID_LL_UNITDATA_IND    == pNasMsgHeader->ulMsgName)
          && (GMM_PD_SM             == (pstLLUnitDataInd->stUnitDataInd.aucPdu[0] & 0x0F)) )
        {
            *pucFollowOn = GMM_TRUE;
            GMM_LOG_INFO("GMM_CasMsgProc:Receive ID_LL_UNITDATA_IND in SUSPENDED_NORMAL_SERVICE state.");
            return;
        }
    }

    /* 挂起状态下需要处理LMM的安全上下文回复消息 */
#if (FEATURE_ON == FEATURE_LTE)
    else if (PS_PID_MM == pMsg->ulSenderPid)
    {
        if (ID_LMM_GMM_HO_SECU_INFO_CNF == pNasMsgHeader->ulMsgName)
        {
            *pucFollowOn = GMM_TRUE;
            GMM_LOG_INFO("GMM_CasMsgProc:Receive ID_LMM_GMM_HO_SECU_INFO_CNF in SUSPENDED_NORMAL_SERVICE state.");
            return;
        }
    }
#endif
    else
    {
    }

    GMM_SuspendMsgProc(pMsg, pucFollowOn);

    return;

}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
