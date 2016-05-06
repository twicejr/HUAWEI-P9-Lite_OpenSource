/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : GmmCasTimer.c
  Author       : Roger Leo
  Version      : V200R001
  Date         : 2005-08-25
  Description  : 该C文件给出了GmmCasTimer模块的实现
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
  5.日    期   : 2006年11月1日
    作    者   : s46746
    修改内容   : 根据问题单号：A32D06572
  6.日    期   : 2006年11月8日
    作    者   : s46746
    修改内容   : 问题单号:A32D06867
  7.日    期   : 2006年12月31日
    作    者   : s46746
    修改内容   : 问题单号:A32D08178
  8.日    期   : 2007年06月16日
    作    者   : l60022475
    修改内容   : 问题单号:A32D11726
  9.日    期   : 2007年12月12日
    作    者   : l00107747
    修改内容   : 根据问题单号：A32D12829
 10.日    期   : 2007年12月28日
    作    者   : s46746
    修改内容   : 根据问题单号：A32D13987,RAU之后没有清除SPEC标志
************************************************************************/

/*****************************************************************************
   1 头文件包含
*****************************************************************************/

#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasTimer.h"
#include "GmmCasSend.h"
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
#define    THIS_FILE_ID        PS_FILE_ID_GMM_CASTIMER_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/

/*****************************************************************************
 Prototype      :
 Description    :
                  HSS 4100 V200R001 新增
                  READY TIMER超时消息入口函数
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function

  2. x51137 2006/4/28 A32D02889
  3.日    期   : 2006年11月8日
    作    者   : s46746
    修改内容   : 问题单号:A32D06867
  4.日    期   : 2006年12月31日
    作    者   : s46746
    修改内容   : 问题单号:A32D08178
  5.日    期   : 2007年06月16日
    作    者   : l60022475
    修改内容   : 问题单号:A32D11726
  6.日    期   : 2009年08月23日
    作    者   : l00130025
    修改内容   : 问题单号:AT2D13700,关机后,T3314超时导致T3312未关闭
  7.日    期   : 2011年05月03日
    作    者   : l65478
    修改内容   : 问题单DTS2011043000267,ready状态，G->W->G CCO,在W下接入禁止,在W下没有启动T3312
  8.日    期   : 2011年12月24日
    作    者   : w00166186
    修改内容   : DTS2011121905287,L重选到W，3312超时不发起ATTACH
  9.日    期   : 2012年1月30日
    作    者   : l00130025
    修改内容   : DTS2012010500368,调用同步接口VOS_GetRelTmRemainTimehTimer时没有判断hTimer是否为0，与定时器异步消息冲突导致异常打印
  10.日    期   : 2012年3月3日
     作    者   : z00161729
     修改内容   : V7R1 C50 支持ISR修改,T3312启动停止超时均需通知L
  11.日    期   : 2012年08月02日
    作    者   : l65478
    修改内容   : DTS2012080104467,在W下T3314超时,服务状态没有更新
  12.日    期   : 2013年07月24日
    作    者   : l65478
    修改内容   : DTS2013072303435,T3314超时后,在RAU等状态下没有通知GAS进入STANDBY
  13.日    期   : 2013年08月16日
    作    者   : l65478
    修改内容   : DTS2013081400197,T3314超时后,不能终止当前的注册过程

*****************************************************************************/
VOS_VOID GMM_TimReadyExpired(VOS_VOID)
{
    VOS_UINT32                          ulT3311Status;
    VOS_UINT32                          ulT3302Status;

    if (GMM_DEREGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
    {
        gstGmmCasGlobalCtrl.GmmSrvState     = GMM_IU_PMM_DETACHED;
    }
    else
    {
        gstGmmCasGlobalCtrl.GmmSrvState     = GMM_AGB_GPRS_STANDBY;
    }

    /* WCDMA模式，由HSS 4100 V100R001代码处理 */
    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        /* 在注册状态,并且服务状态是空闲态时,启动3312 */
        if ((0x20 == (g_GmmGlobalCtrl.ucState & 0xF0))
         && (GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
         && (GMM_TRUE != g_GmmRauCtrl.ucT3312ExpiredFlg ))
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);
        }
        return;     /* 不需处理返回 */
    }

    if (GMM_DEREGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
    {
        gstGmmCasGlobalCtrl.GmmSrvState     = GMM_IU_PMM_DETACHED;
    }
    else
    {
        ulT3311Status = NAS_GMM_QryTimerStatus(GMM_TIMER_T3311);
        ulT3302Status = NAS_GMM_QryTimerStatus(GMM_TIMER_T3302);

        if ((GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState)
          || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == g_GmmGlobalCtrl.ucState))
        {
            if ((VOS_FALSE == ulT3311Status)
             && (VOS_FALSE == ulT3302Status))
            {
#if (FEATURE_LTE == FEATURE_ON)
                if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                {
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                }
#endif
                Gmm_TimerStart(GMM_TIMER_T3312);
            }
        }
        else
        {
            if ((0x10 != (g_GmmGlobalCtrl.ucState & 0xF0))
             && (GMM_REGISTERED_INITIATED != g_GmmGlobalCtrl.ucState))
                {
#if (FEATURE_LTE == FEATURE_ON)
                if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                {
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                }
#endif
                Gmm_TimerStart(GMM_TIMER_T3312);
            }
        }

        gstGmmCasGlobalCtrl.GmmSrvState     = GMM_AGB_GPRS_STANDBY;
    }

    NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);


    return;
}

/*****************************************************************************
 Prototype      :
 Description    :
                  HSS 4100 V200R001 新增
                  GMM_TIMER_RAU_RSP超时消息处理
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-25
    Author      : Roger Leo
    Modification: Created function

  2. x51137 2006/4/28 A32D02889
  3.日    期   : 2006年11月1日
    作    者   : s46746
    修改内容   : 根据问题单号：A32D06572
  4.日    期   : 2006年11月6日
    作    者   : s46746
    修改内容   : 根据问题单号：A32D06867
*****************************************************************************/
VOS_VOID GMM_TimRauRspExpired(VOS_VOID)
{
    gstGmmCasGlobalCtrl.ucRabmRauRspRcvdFlg = VOS_TRUE;

    /* 不需要等待WRR的回复消息，或者已经收到WRR的回复消息，进行RAU流程结束的相应处理 */
    if (   (VOS_FALSE == g_GmmInterRatInfoCtrl.ucRauCmpWaitInterRatCnfMsg)
        || (VOS_TRUE == g_GmmInterRatInfoCtrl.ucInterRatCnfMsgRcvdFlg))
    {
        NAS_GMM_RauCompleteHandling();
    }

    return;
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
