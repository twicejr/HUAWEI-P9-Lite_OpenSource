

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
