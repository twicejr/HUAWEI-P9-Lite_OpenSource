/*******************************************************************************
  Copyright     : 2005-2007, Huawei Tech. Co., Ltd.
  File name     : GmmSend.c
  Description   : GMM原语发送功能相关处理用源文件
  Function List :
    01.   Gmm_Com_CmpPlmnid
    02.   Gmm_Com_DealOfMsId
    03.   Gmm_Com_DealOfPlmnList
    04.   Gmm_SndAgentUsimAuthenticationReq
    05.   Gmm_SndAgentUsimUpdateFileReq
    06.   Gmm_SndMmcAuthenticationFailureInd
    07.   Gmm_SndMmcCombinedAttachAccept
    08.   Gmm_SndMmcCombinedAttachInitiation
    09.   Gmm_SndMmcCombinedAttachRejected
    10.   Gmm_SndMmcCombinedRauAccept
    11.   Gmm_SndMmcCombinedRauInitiation
    12.   Gmm_SndMmcCombinedRauRejected
    13.   Gmm_SndMmcDetachCnf
    14.   Gmm_SndMmcGmmActionResultInd
    15.   Gmm_SndMmcGprsDetachInitiation
    16.   Gmm_SndMmcImsiDetachInitiation
    17.   Gmm_SndMmcInfoInd
    18.   Gmm_SndMmcLocalDetachInd
    19.   Gmm_SndMmcLuInitiation
    20.   Gmm_SndMmcNetworkDetachInd
    21.   Gmm_SndMmcPdpStatusInd
    22.   Gmm_SndMmcPowerOffCnf
    23.   Gmm_SndMmcSignalingStatusInd
    24.   Gmm_SndMmcStartCnf
    25.   Gmm_SndMsg
    26.   Gmm_SndRabmReestablishCnf
    27.   Gmm_SndRrmmAbortReq
    28.   Gmm_SndRrmmDataReq
    29.   Gmm_SndRrmmDataReqForCm
    30.   Gmm_SndRrmmEstReq
    31.   Gmm_SndRrmmNasInfoChangeReq
    32.   Gmm_SndRrmmRelReq
    33.   Gmm_SndSmDataInd
    34.   Gmm_SndSmEstablishCnf
    35.   Gmm_SndSmsErrorInd
    36.   Gmm_SndSmsEstCnf
    37.   Gmm_SndSmsRegStateInd
    38.   Gmm_SndSmStatusInd
    39.   Gmm_SndSmsUnitdataInd
    40.   Gmm_SndTcDataInd

  History       :
    1.  张志勇  2003.12.05  新规作成
    2.  s46746  2006-03-08  根据问题单A32D02368修改
    3.  s46746  2006-05-08  根据问题单A32D03487修改
    4.  l46746  2006-06-29  根据问题单A32D04514修改
    5.  l40632  2006-07-07  根据问题单A32D04776修改
    6.  s46746  2006-07-08  根据问题单A32D04551修改
    7.日    期   : 2006年9月13日
      作    者   : liurui id:40632
      修改内容   : 根据问题单号：A32D05806
    8.日    期   : 2006年10月6日
      作    者   : s46746
      修改内容   : 问题单号：A32D05960
    9.日    期  : 2006年11月25日
      作    者  : luojian id:60022475
      修改内容  : 问题单号:A32D06583
   10.日    期  : 2007年05月25日
      作    者  : luojian id:60022475
      修改内容  : 问题单号:A32D11232
   11.日    期  : 2007年06月19日
      作    者  : s46746
      修改内容  : 问题单号:A32D11737,关机后，需要去指配LLC
   12.日    期   : 2007年9月27日
      作    者   : s46746
      修改内容   : 将卡无效信息从RRMM_NAS_INFO_CHANGE消息中拿掉
   13.日    期   : 2007年10月13日
      作    者   : s46746
      修改内容   : 根据问题单号：A32D13060
   14.日    期   : 2007年10月27日
      作    者   : luojian id:107747
      修改内容   : 根据问题单号：A32D13038
   15.日    期   : 2007年11月12日
      作    者   : l39007
      修改内容   : 根据问题单A32D13044,ATTACH失败5次,启动T3302定时器,通知MM
                   发起一次LAU之后,计数器清0
   16.日    期   : 2008年8月8日
      作    者   : ouyangfei id:00132663
      修改内容   : 根据问题单号：AT2D04972
   17.日    期   : 2008年08月08日
      作    者   : luojian id:00107747
      修改内容   : 根据问题单AT2D04880/AT2D05000,等效PLMN列表清除排查
   18.日    期   : 2009年03月25日
      作    者   : h44270
      修改内容   : 问题单AT2D10415,USIM GCF测试的无卡紧急呼叫有问题
   19.日    期   : 2009年6月30日
      作    者   : x00115505
      修改内容   : AT2D12552,W重选到不支持GPRS的GSM小区，发PS短信，TAF没有判断
                   当前状态是否应该发起，仍然发送该短信
   20.日    期   : 2009年7月23日
      作    者   : s46746
      修改内容   : 根据问题单号：AT2D12878，GSM下HPLMN搜索时接收到GPRS寻呼或PDP激活(W下PDP激活相同处理)请求需要能及时响应
   21.日    期   : 2009年08月14日
      作    者   : l60609
      修改内容   : 问题单号:AT2D13779,IMSI DETACH上报事件不合理
   22.日    期   : 2009年08月24日
      作    者   : x00115505
      修改内容   : AT2D14023,测试GCF用例44.2.2.1.9失败
   23.日    期   : 2009年9月7日
      作    者   : s46746
      修改内容   : 根据问题单号：AT2D14311，出服务区后，GMM存在连接时先进行了连接释放，会导致服务状态临时更新为Normal service
   24.日    期   : 2009年09月12日
      作    者   : s46746
      修改内容   : 问题单号：AT2D14432,HPLMN定时器在异系统重选过程中超时没有立即进行HPLMN搜索
   25.日    期   : 2009年09月25日
      作    者   : s46746
      修改内容   : 问题单号：AT2D14765,LAU/RAU过程中设置SYSCFG失败
   26.日    期   : 2009年10月12日
      作    者   : s46746
      修改内容   : 根据问题单号：AT2D14959，GMM向MMC发送RAU、Attach成功的假流程时，没有携带EPLMN列表
*******************************************************************************/

#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasComm.h"
#include "GmmCasSend.h"
#include "NasComm.h"
#include "NasCommDef.h"
#include "GmmMmInterface.h"
#include "NasMmlMsgProc.h"
#include "NasMmlCtx.h"
#include "GmmExt.h"
#include "NasUtranCtrlInterface.h"

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
#define    THIS_FILE_ID        PS_FILE_ID_GMM_SEND_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/

/* Delete by z00234330 for PCLINT清理, 2014-06-16, begin */

/* Delete by z00234330 for PCLINT清理, 2014-06-16, end */

/*lint -save -e958 */

#if (FEATURE_LTE == FEATURE_ON)
/*****************************************************************************
 函 数 名  : NAS_GMM_SndLmmReselSecuInfoReq
 功能描述  : LMM发送重选安全参数获取请求
 输入参数  :
 输出参数  : 无
 返 回 值  : 表示发送消息是否成功。成功返回VOS_OK,失败返回VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月19日
    作    者   : luokaihui /l00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年11月28日
    作    者   : z00161729
    修改内容   : GMM与LMM消息交互采用内部消息队列，为保证PC上GTR功能已有用例可以正常使用，
                在PC上MMC、GMM和LMM的交互还使用外部消息，发送消息函数需要用宏NAS_STUB隔开
*****************************************************************************/

VOS_VOID NAS_GMM_SndLmmReselSecuInfoReq( VOS_VOID )
{
    GMM_LMM_RESEL_SECU_INFO_REQ_STRU   *pstReselSecuInfoReq;

#if (VOS_WIN32 == VOS_OS_VER)
    /* 申请内存  */
    pstReselSecuInfoReq                 = (GMM_LMM_RESEL_SECU_INFO_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                                            sizeof(GMM_LMM_RESEL_SECU_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstReselSecuInfoReq = (GMM_LMM_RESEL_SECU_INFO_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(GMM_LMM_RESEL_SECU_INFO_REQ_STRU));
#endif

    if( VOS_NULL_PTR == pstReselSecuInfoReq )
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndLmmReselSecuInfoReq:分配内存失败");
        return ;
    }

    pstReselSecuInfoReq->ulReceiverCpuId= VOS_LOCAL_CPUID;
    pstReselSecuInfoReq->ulSenderCpuId  = VOS_LOCAL_CPUID;
    pstReselSecuInfoReq->ulSenderPid    = WUEPS_PID_GMM;
    pstReselSecuInfoReq->ulReceiverPid  = PS_PID_MM;
    pstReselSecuInfoReq->ulMsgId        = ID_GMM_LMM_RESEL_SECU_INFO_REQ;
    pstReselSecuInfoReq->ulLength       = sizeof(GMM_LMM_RESEL_SECU_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ulOpId、ulTransceiverType目前不使用 */
    pstReselSecuInfoReq->ulOpId         = 0;
    pstReselSecuInfoReq->aucRsv[0]      = 0;
    pstReselSecuInfoReq->aucRsv[1]      = 0;
    pstReselSecuInfoReq->aucRsv[2]      = 0;
    pstReselSecuInfoReq->aucRsv[3]      = 0;

#if (VOS_WIN32 == VOS_OS_VER)
    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_GMM, pstReselSecuInfoReq);
#else
    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstReselSecuInfoReq);
#endif

    return ;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_SndLmmHoSecuInfoReq
 功能描述  : LMM发送切换安全参数获取请求
 输入参数  :
 输出参数  : 无
 返 回 值  : 表示发送消息是否成功。成功返回VOS_OK,失败返回VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月19日
    作    者   : luokaihui /l00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年11月28日
    作    者   : z00161729
    修改内容   : GMM与LMM消息交互采用内部消息队列，为保证PC上GTR功能已有用例可以正常使用，
                 在PC上MMC、GMM和LMM的交互还使用外部消息，发送消息函数需要用宏NAS_STUB隔开
*****************************************************************************/
VOS_VOID NAS_GMM_SndLmmHoSecuInfoReq( VOS_VOID )
{
    GMM_LMM_HO_SECU_INFO_REQ_STRU      *pstHoSecuInfoReq;

#if (VOS_WIN32 == VOS_OS_VER)
    /* 申请内存  */
    pstHoSecuInfoReq = (GMM_LMM_HO_SECU_INFO_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                                            (sizeof(GMM_LMM_HO_SECU_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH));
#else
    pstHoSecuInfoReq = (GMM_LMM_HO_SECU_INFO_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(GMM_LMM_HO_SECU_INFO_REQ_STRU));
#endif

    if( VOS_NULL_PTR == pstHoSecuInfoReq )
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndLmmReselSecuInfoReq:分配内存失败");
        return ;
    }

    pstHoSecuInfoReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstHoSecuInfoReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstHoSecuInfoReq->ulSenderPid       = WUEPS_PID_GMM;
    pstHoSecuInfoReq->ulReceiverPid     = PS_PID_MM;
    pstHoSecuInfoReq->ulMsgId           = ID_GMM_LMM_HO_SECU_INFO_REQ;
    pstHoSecuInfoReq->ulLength          = sizeof(GMM_LMM_HO_SECU_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ulOpId、ulTransceiverType目前不使用 */
    pstHoSecuInfoReq->ulOpId            = 0;
    pstHoSecuInfoReq->aucRsv[0]         = 0;
    pstHoSecuInfoReq->aucRsv[1]         = 0;
    pstHoSecuInfoReq->aucRsv[2]         = 0;
    pstHoSecuInfoReq->aucRsv[3]         = 0;

#if (VOS_WIN32 == VOS_OS_VER)
    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_GMM, pstHoSecuInfoReq );

#else
    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstHoSecuInfoReq);
#endif

    return ;

}
/*****************************************************************************
 函 数 名  : NAS_GMM_SndLmmInfoChangeNotifyReq
 功能描述  : 发送通知LMM模块GMM连接状态信息消息
 输入参数  : enRat
             ucSrvState
             ulGprsSuspendFlg
             bitOpConnState
             bitOpGprsSuspend
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月27日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年11月28日
   作    者   : z00161729
   修改内容   : GMM与LMM消息交互采用内部消息队列，为保证PC上GTR功能已有用例可以正常使用，
               在PC上MMC、GMM和LMM的交互还使用外部消息，发送消息函数需要用宏NAS_STUB隔开
 3.日    期   : 2012年10月10日
   作    者   : z00161729
   修改内容  : DTS2012101002998:csfb mt到g，lai未改变呼叫结束后rel ind指示重定向到l，未做tau

*****************************************************************************/
VOS_VOID NAS_GMM_SndLmmInfoChangeNotifyReq(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           bitOpConnState,
    VOS_UINT8                           bitOpGprsSuspend,
    VOS_UINT8                           ucSrvState,
    VOS_UINT32                          ulGprsSuspendFlg
)
{
    GMM_LMM_INFO_CHANGE_NOTIFY_REQ_STRU                    *pstInfoChange = VOS_NULL_PTR;

#if (VOS_WIN32 == VOS_OS_VER)
    /* 申请消息包  */
    pstInfoChange = (GMM_LMM_INFO_CHANGE_NOTIFY_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_GMM,
                                       (sizeof(GMM_LMM_INFO_CHANGE_NOTIFY_REQ_STRU) - VOS_MSG_HEAD_LENGTH));
#else
    pstInfoChange = (GMM_LMM_INFO_CHANGE_NOTIFY_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(GMM_LMM_INFO_CHANGE_NOTIFY_REQ_STRU));
#endif

    if (VOS_NULL_PTR == pstInfoChange)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndLmmInfoChangeNotifyReq:分配消息内存失败");

        return ;
    }

    /* 消息头填充  */
    pstInfoChange->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstInfoChange->ulReceiverPid            = PS_PID_MM;

    pstInfoChange->ulSenderPid              = WUEPS_PID_GMM;
    pstInfoChange->ulSenderCpuId            = VOS_LOCAL_CPUID;

    pstInfoChange->ulMsgId                  = ID_GMM_LMM_INFO_CHANGE_NOTIFY_REQ;
    pstInfoChange->ulOpId                   = 0;
    pstInfoChange->ulLength                 = sizeof(GMM_LMM_INFO_CHANGE_NOTIFY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 初始化Op项 */
    pstInfoChange->bitOpGprsMmState         = VOS_FALSE;
    pstInfoChange->bitOpPacketMmState       = VOS_FALSE;
    pstInfoChange->bitOpGprsSuspensionState = VOS_FALSE;
    pstInfoChange->bitSpare                 = VOS_FALSE;

    /* 如果当前接入技术为2G */
    if (NAS_MML_NET_RAT_TYPE_GSM == enRat)
    {
        pstInfoChange->bitOpGprsMmState         = bitOpConnState;
        pstInfoChange->bitOpGprsSuspensionState = bitOpGprsSuspend;

        /* 根据ucSrvState填充enGConnState */
        if (GMM_AGB_GPRS_READY == ucSrvState)
        {
            pstInfoChange->enGprsMmState = GMM_LMM_GPRS_MM_STATE_READY;
        }
        else if (GMM_AGB_GPRS_STANDBY == ucSrvState)
        {
            pstInfoChange->enGprsMmState = GMM_LMM_GPRS_MM_STATE_STANDBY;
        }
        else
        {
            pstInfoChange->enGprsMmState = GMM_LMM_GPRS_MM_STATE_IDLE;
        }

        /* 根据ulGprsSuspendFlg填充enPsState */
        pstInfoChange->enGprsSuspensionState      = GMM_LMM_GPRS_NOT_SUSPENSION;
        if (VOS_TRUE == ulGprsSuspendFlg)
        {
            pstInfoChange->enGprsSuspensionState  = GMM_LMM_GPRS_SUSPENSION;
        }

        pstInfoChange->enPacketMmState            = GMM_LMM_PACKET_MM_STATE_BUTT;
    }
    else if (NAS_MML_NET_RAT_TYPE_WCDMA == enRat)
    {
        pstInfoChange->bitOpPacketMmState = bitOpConnState;

        /* 根据ucSrvState填充enUConnState */
        if (GMM_IU_PMM_CONNECTED == ucSrvState)
        {
            pstInfoChange->enPacketMmState        = GMM_LMM_PACKET_MM_STATE_PMM_CONNECTED;
        }
        else if (GMM_IU_PMM_IDLE == ucSrvState)
        {
            pstInfoChange->enPacketMmState        = GMM_LMM_PACKET_MM_STATE_PMM_IDLE;
        }
        else
        {
            pstInfoChange->enPacketMmState        = GMM_LMM_PACKET_MM_STATE_PMM_DETACH;
        }

        pstInfoChange->enGprsMmState              = GMM_LMM_GPRS_MM_STATE_BUTT;
        pstInfoChange->enGprsSuspensionState      = GMM_LMM_GPRS_SUSPENSION_BUTT;
    }
    else
    {
        /* warning级别打印 */
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_SndLmmInfoChangeNotifyReq:接入技术不正确");
    }

#if (VOS_WIN32 == VOS_OS_VER)
    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_GMM, pstInfoChange );
#else
    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstInfoChange);
#endif

    return ;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_SndLmmTimerInfoNotify
 功能描述  : 通知LMM T3312定时器改变消息
 输入参数  : ucTimerId   - 定时器ID
             enTimerInfo - 定时器状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月2日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_SndLmmTimerInfoNotify(
   VOS_UINT8                            ucTimerId,
   GMM_LMM_TIMER_STATE_ENUM_UINT32      enTimerInfo
)
{
    /* 按GMM_LMM_TIMER_STATE_NOTIFY_STRU结构封装消息发送给LMM */
    GMM_LMM_TIMER_STATE_NOTIFY_STRU    *pstTimerStatusNotify;

#if (VOS_WIN32 == VOS_OS_VER)
    /* 申请内存  */
    pstTimerStatusNotify = (GMM_LMM_TIMER_STATE_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_GMM,
                               sizeof(GMM_LMM_TIMER_STATE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstTimerStatusNotify = (GMM_LMM_TIMER_STATE_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(GMM_LMM_TIMER_STATE_NOTIFY_STRU));
#endif

    if( VOS_NULL_PTR == pstTimerStatusNotify )
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndLmmTimerInfoNotify:分配内存失败");
        return ;
    }

    pstTimerStatusNotify->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstTimerStatusNotify->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstTimerStatusNotify->ulSenderPid     = WUEPS_PID_GMM;
    pstTimerStatusNotify->ulReceiverPid   = PS_PID_MM;
    pstTimerStatusNotify->ulMsgId         = ID_GMM_LMM_TIMER_STATE_NOTIFY;
    pstTimerStatusNotify->ulLength        = sizeof(GMM_LMM_TIMER_STATE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 初始化Op项 */
    pstTimerStatusNotify->bitOpT3312      = VOS_FALSE;
    pstTimerStatusNotify->bitOpRsv        = VOS_FALSE;

    if (GMM_TIMER_T3312 == ucTimerId)
    {
        pstTimerStatusNotify->bitOpT3312    = VOS_TRUE;
        pstTimerStatusNotify->enT3312State  = enTimerInfo;
    }
    pstTimerStatusNotify->ulOpId            = 0;

#if (VOS_WIN32 == VOS_OS_VER)
    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_GMM, pstTimerStatusNotify);
#else
    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstTimerStatusNotify);
#endif
    return;
}


#if(FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 函 数 名  : NAS_GMM_ConvertRrcSessionTypeToLmmFormat
 功能描述  : 将gmm和rrc接口中的session type转换为gmm和lmm的session type
 输入参数  : enRrcSessionType    - gmm和rrc接口中的session type
 输出参数  : pucLmmSessionType   - gmm和lmm的session type
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_ConvertRrcSessionTypeToLmmFormat(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType,
    GMM_LMM_SESSION_TYPE_ENUM_UINT8    *puclmmSessionType
)
{
    switch (enRrcSessionType)
    {
        case RRC_NAS_SESSION_TYPE_PS_MO_SMS:
            *puclmmSessionType = GMM_LMM_SESSION_TYPE_MO_SMS;
            break;

        case RRC_NAS_SESSION_TYPE_PS_MT_SMS:
            *puclmmSessionType = GMM_LMM_SESSION_TYPE_MT_SMS;
            break;

        case RRC_NAS_SESSION_TYPE_PS_ATTACH:
            *puclmmSessionType = GMM_LMM_SESSION_TYPE_PS_ATTACH;
            break;

        case RRC_NAS_SESSION_TYPE_PS_RAU:
            *puclmmSessionType = GMM_LMM_SESSION_TYPE_PS_RAU;
            break;

        case RRC_NAS_SESSION_TYPE_PS_DETACH:
            *puclmmSessionType = GMM_LMM_SESSION_TYPE_PS_DETACH;
            break;

        case RRC_NAS_SESSION_TYPE_PS_CONVERSAT_CALL:
            *puclmmSessionType = GMM_LMM_SESSION_TYPE_PS_CONVERSAT_CALL;
            break;

        case RRC_NAS_SESSION_TYPE_PS_STREAM_CALL:
            *puclmmSessionType = GMM_LMM_SESSION_TYPE_PS_STREAM_CALL;
            break;

        case RRC_NAS_SESSION_TYPE_PS_INTERACT_CALL:
            *puclmmSessionType = GMM_LMM_SESSION_TYPE_PS_INTERACT_CALL;
            break;

        case RRC_NAS_SESSION_TYPE_PS_BACKGROUND_CALL:
            *puclmmSessionType = GMM_LMM_SESSION_TYPE_PS_BACKGROUND_CALL;
            break;

        case RRC_NAS_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL:
            *puclmmSessionType = GMM_LMM_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL;
            break;

        default:
            *puclmmSessionType = GMM_LMM_SESSION_TYPE_BUTT;
            break;
    }
    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_SndLmmBeginSessionNotify
 功能描述  : GMM通知LMM开始Session通知
 输入参数  : enSessionType:GMM当前session类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月16日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_SndLmmBeginSessionNotify(
   GMM_LMM_SESSION_TYPE_ENUM_UINT8      enSessionType
)
{
    GMM_LMM_BEGIN_SESSION_NOTIFY_STRU  *pstBeginSessionNotify = VOS_NULL_PTR;

#if (VOS_WIN32 == VOS_OS_VER)
    /* 申请内存  */
    pstBeginSessionNotify = (GMM_LMM_BEGIN_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_GMM,
                               sizeof(GMM_LMM_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstBeginSessionNotify = (GMM_LMM_BEGIN_SESSION_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(GMM_LMM_BEGIN_SESSION_NOTIFY_STRU));
#endif

    if( VOS_NULL_PTR == pstBeginSessionNotify )
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndLmmBeginSessionNotify:分配内存失败");
        return ;
    }

    PS_MEM_SET((VOS_UINT8*)pstBeginSessionNotify + VOS_MSG_HEAD_LENGTH, 0x00,
                    sizeof(GMM_LMM_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 构造消息结构体 */
    pstBeginSessionNotify->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->stMsgHeader.ulSenderPid     = WUEPS_PID_GMM;
    pstBeginSessionNotify->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstBeginSessionNotify->stMsgHeader.ulLength        = sizeof(GMM_LMM_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBeginSessionNotify->stMsgHeader.ulMsgName       = ID_GMM_LMM_BEGIN_SESSION_NOTIFY;

    pstBeginSessionNotify->enSessionType               = enSessionType;

#if (VOS_WIN32 == VOS_OS_VER)
    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_GMM, pstBeginSessionNotify);
#else
    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstBeginSessionNotify);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_SndLmmEndSessionNotify
 功能描述  : GMM通知LMM结束Session通知
 输入参数  : enSessionType:GMM当前session类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月16日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_SndLmmEndSessionNotify(
   GMM_LMM_SESSION_TYPE_ENUM_UINT8      enSessionType
)
{
    GMM_LMM_END_SESSION_NOTIFY_STRU    *pstEndSessionNotify = VOS_NULL_PTR;

#if (VOS_WIN32 == VOS_OS_VER)
    /* 申请内存  */
    pstEndSessionNotify = (GMM_LMM_END_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_GMM,
                               sizeof(GMM_LMM_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstEndSessionNotify = (GMM_LMM_END_SESSION_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(GMM_LMM_END_SESSION_NOTIFY_STRU));
#endif

    if( VOS_NULL_PTR == pstEndSessionNotify )
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndLmmEndSessionNotify:分配内存失败");
        return ;
    }

    PS_MEM_SET((VOS_UINT8*)pstEndSessionNotify + VOS_MSG_HEAD_LENGTH, 0x00,
                        sizeof(GMM_LMM_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 构造消息结构体 */
    pstEndSessionNotify->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstEndSessionNotify->stMsgHeader.ulSenderPid     = WUEPS_PID_GMM;
    pstEndSessionNotify->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstEndSessionNotify->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstEndSessionNotify->stMsgHeader.ulLength        = sizeof(GMM_LMM_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstEndSessionNotify->stMsgHeader.ulMsgName       = ID_GMM_LMM_END_SESSION_NOTIFY;

    pstEndSessionNotify->enSessionType               = enSessionType;

#if (VOS_WIN32 == VOS_OS_VER)
    /* 调用VOS发送原语 */
    PS_SEND_MSG(WUEPS_PID_GMM, pstEndSessionNotify);
#else
    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstEndSessionNotify);
#endif

    return;
}


#endif

#endif
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-12, begin */
/*****************************************************************************
 函 数 名  : NAS_GMM_SndMmcNetworkCapabilityInfoInd
 功能描述  : 发送网络能力参数信息给MMC

 输入参数  : enNwEmcBS   网络的EMC BS支持参数
             enNwImsVoPS 网络IMS voice PS能力参数
             enLteCsCap  LTE网络的CS能力

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月12日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_SndMmcNetworkCapabilityInfoInd(
    GMM_MMC_NW_EMC_BS_CAP_ENUM_UINT8    enNwEmcBS,
    NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8 enNwImsVoPS,
    GMM_MMC_LTE_CS_CAPBILITY_ENUM_UINT8 enLteCsCap
)
{
    GMMMMC_NETWORK_CAPABILITY_INFO_IND_STRU                *pstMmcMsg = VOS_NULL_PTR;

    pstMmcMsg = (GMMMMC_NETWORK_CAPABILITY_INFO_IND_STRU *)NAS_MML_GetIntMsgSendBuf(
        sizeof(GMMMMC_NETWORK_CAPABILITY_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstMmcMsg)
    {
        /* print error information */
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmcNetworkCapabilityInfoInd: memory allocation is failure!");

        return ;
    }

    PS_MEM_SET(pstMmcMsg, 0, sizeof(GMMMMC_NETWORK_CAPABILITY_INFO_IND_STRU));

    /* set message header */
    pstMmcMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMmcMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMmcMsg->MsgHeader.ulSenderPid     = WUEPS_PID_GMM;
    pstMmcMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMmcMsg->MsgHeader.ulMsgName       = GMMMMC_NETWORK_CAPABILITY_INFO_IND;
    pstMmcMsg->MsgHeader.ulLength        = sizeof(GMMMMC_NETWORK_CAPABILITY_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMmcMsg->enNwEmcBsCap              = enNwEmcBS;
    pstMmcMsg->enNwImsVoCap              = enNwImsVoPS;
    pstMmcMsg->enLteCsCap                = enLteCsCap;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMmcMsg);
}

/*******************************************************************************
  Module:      GMM_ReportM2NOtaMsg
  Function:    在trace中勾取GMM的空口消息
  Input:       NAS_MSG_STRU*   pNasMsg     GMM空口消息
  NOTE:
  Return:      VOS_VOID
  History:
      1. 鲁琳    2009.07.11   新规作成
      2. 日    期   : 2011年07月14日
         作    者   : f00179208
         修改内容   : 根据问题单号：DTS2011071305294,MNO2网络发起PS DETACH类型为"IMSI detach",
                      空口消息显示有误
*******************************************************************************/
VOS_VOID GMM_ReportM2NOtaMsg(NAS_MSG_STRU *pNasMsg)
{
    NAS_OTA_MSG_ID_ENUM_UINT16 usNasOtaMsyId = NAS_OTA_MSG_ID_BUTT;

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "GMM_ReportM2NOtaMsg:NORMAL: msg id is", pNasMsg->aucNasMsg[1]);

    if (GMM_PD_GMM != (pNasMsg->aucNasMsg[0] & 0x0f))
    {
        return;
    }

    switch(pNasMsg->aucNasMsg[1])
    {
        case GMM_MSG_ATTACH_REQUEST:
            usNasOtaMsyId = NAS_OTA_MSG_ATTACH_REQ;
            break;

        case GMM_MSG_ATTACH_COMPLETE:
            usNasOtaMsyId = NAS_OTA_MSG_ATTACH_COMPLETE;
            break;

        case GMM_MSG_DETACH_REQUEST:
            usNasOtaMsyId = NAS_OTA_MSG_DETACH_REQ;
            break;

        case GMM_MSG_DETACH_ACCEPT:
            usNasOtaMsyId = NAS_OTA_MSG_DETACH_ACCEPT_BY_MS;
            break;

        case GMM_MSG_RAU_REQUEST:
            usNasOtaMsyId = NAS_OTA_MSG_RAU_REQ;
            break;

        case GMM_MSG_RAU_COMPLETE:
            usNasOtaMsyId = NAS_OTA_MSG_RAU_COMPLETE;
            break;

        case GMM_MSG_SERVICE_REQUEST:
            usNasOtaMsyId = NAS_OTA_MSG_DATA_SERVICE_REQ;
            break;

        case GMM_MSG_P_TMSI_REALLOCATION_COMPLETE:
            usNasOtaMsyId = NAS_OTA_MSG_P_TMSI_REALLOCATION_COMPLETE;
            break;

        case GMM_MSG_AUTHENTICATION_AND_CIPHERING_RESPONSE:
            usNasOtaMsyId = NAS_OTA_MSG_AUTH_AND_CIPHER_RESPONSE;
            break;

        case GMM_MSG_AUTHENTICATION_AND_CIPHERING_FAILURE:
            usNasOtaMsyId = NAS_OTA_MSG_AUTH_AND_CIPHER_FAIL;
            break;

        case GMM_MSG_IDENTITY_RESPONSE:
            usNasOtaMsyId = NAS_OTA_MSG_IDENTITY_RESPONSE;
            break;

        case GMM_MSG_GMM_STATUS:
            usNasOtaMsyId = NAS_OTA_MSG_GMM_STATUS_BY_MS;
            break;

        default:
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "GMM_ReportM2NOtaMsg:WARNING: invalid msg id");
            /*不属于GMM模块的空口消息，不在trace中显示*/
            return;
    }

    NAS_SendAirMsgToOM(WUEPS_PID_GMM, usNasOtaMsyId, NAS_OTA_DIRECTION_UP, pNasMsg->ulNasMsgSize + 4, (VOS_UINT8*)pNasMsg);
}

/*******************************************************************************
  Module   : Gmm_SndMmcNetworkDetachInd
  Function : MMCGMM_NETWORK_DETACH_IND原语填写及发送
  Input    : VOS_UINT8      ucDetachType           detach类型
             VOS_UINT8      ucDetachCause          detach原因
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.08  新规作成

*******************************************************************************/
VOS_VOID Gmm_SndMmcNetworkDetachInd(
                                VOS_UINT8 ucDetachType,                             /* detach类型                               */
                                VOS_UINT8 ucDetachCause                             /* detach原因                               */
                                )
{
    MMCGMM_NETWORK_DETACH_IND_STRU     *pstMsg          = VOS_NULL_PTR;
    MMCGMM_NETWORK_DETACH_IND_STRU     *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(MMCGMM_NETWORK_DETACH_IND_STRU);

    pstInternalMsg  = (MMCGMM_NETWORK_DETACH_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_SndMmcNetworkDetachInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_NETWORK_DETACH_IND;
    pstMsg->ulDetachType   = ucDetachType;                                        /* 填写detach类型                           */
    pstMsg->ulDetachCause  = ucDetachCause;                                       /* 填写detach原因                           */

    if (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR != ucDetachCause)
    {                                                                           /* 原因值不为#2                             */
        pstMsg->ulServiceSts   = Gmm_ComServiceSts();                             /* 填写服务状态                             */
    }
    else
    {
        pstMsg->ulServiceSts   = 0x0;
    }

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_SndMmcAttachCnf
 功能描述  : GMM向MMC发送MMCGMM_ATTACH_CNF
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月30日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_SndMmcAttachCnf(VOS_VOID)
{
    MMCGMM_ATTACH_CNF_STRU             *pstMsg          = VOS_NULL_PTR;
    MMCGMM_ATTACH_CNF_STRU             *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(MMCGMM_ATTACH_CNF_STRU);

    pstInternalMsg  = (MMCGMM_ATTACH_CNF_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmcAttachCnf,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_ATTACH_CNF;
    pstMsg->ulOpid                        = g_GmmGlobalCtrl.stAttachInfo.ulOpid;
    pstMsg->ulServiceStatus               = Gmm_ComServiceSts();

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_Gmm_SndMmcDetachCnf
 功能描述  : GMM 向MMC发送DETACH CNF
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月14日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数
  2.日    期   : 2011年12月01日
    作    者   : w00176964
    修改内容   : phaseIV调整:增加detach类型IE项，disable场景需要判断

*****************************************************************************/
VOS_VOID NAS_GMM_SndMmcDetachCnf(VOS_VOID)
{
    MMCGMM_DETACH_CNF_STRU             *pstMsg          = VOS_NULL_PTR;
    MMCGMM_DETACH_CNF_STRU             *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(MMCGMM_DETACH_CNF_STRU);

    pstInternalMsg  = (MMCGMM_DETACH_CNF_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmcDetachCnf,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_DETACH_CNF;
    pstMsg->ulOpid                        = g_GmmGlobalCtrl.stDetachInfo.ulOpid;
    pstMsg->ulServiceSts                  = Gmm_ComServiceSts();

    pstMsg->ulDetachType                  = g_GmmGlobalCtrl.stDetachInfo.enDetachType;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    if (MM_COM_SRVST_NORMAL_SERVICE != pstMsg->ulServiceSts)
    {
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_DETACH_FINISH,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);
    }

    /* 无条件清除该变量 */
    g_GmmDetachCtrl.ucSysCfgDetachFlg = VOS_FALSE;

    return;
}

/*******************************************************************************
  Module   : Gmm_SndMmcPowerOffCnf
  Function : MMCGMM_POWER_OFF_CNF原语填写及发送
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.08  新规作成

    2.日    期   : 2006年6月7日
      作    者   : liuyang id:48197
      修改内容   : 问题单号：A32D02883
    3.日    期   : 2006年9月13日
      作    者   : liurui id:40632
      修改内容   : 根据问题单号：A32D05806
    4.日    期   : 2010年09月13日
      作    者   : L65478
      修改内容   : 问题单号:DTS2010091301310,WCDMA下关机，重新开机后，在GSM模式下无法注册成功
    5.日    期   : 2010年12月18日
      作    者   : o00132663
      修改内容   : 根据问题单号：DTS2010121800152,GMM关机关不掉，状态挂死
*******************************************************************************/
VOS_VOID Gmm_SndMmcPowerOffCnf(VOS_VOID)
{
    MMCGMM_POWER_OFF_CNF_STRU          *pstMsg          = VOS_NULL_PTR;
    MMCGMM_POWER_OFF_CNF_STRU          *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(MMCGMM_POWER_OFF_CNF_STRU);

    pstInternalMsg  = (MMCGMM_POWER_OFF_CNF_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_SndMmcPowerOffCnf,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_POWER_OFF_CNF;
    /*A32D11737==>关机后，需要去指配LLC*/
    if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
    {
        NAS_GMM_FreeTlliForPowerOff();
    }

    Gmm_TimerStop( GMM_TIMER_ALL );

    /* GMM_TIMER_1S必须单独停掉，GMM_TIMER_ALL并不停止关机保护定时器 */
    Gmm_TimerStop( GMM_TIMER_1S );
    g_GmmGlobalCtrl.stPowerOffCtrl.ucSndDetachCnt = 0;

    gucGmmInitState = NAS_GMM_CTRL_STATUS_STARTUP;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}

/*******************************************************************************
  Module   : Gmm_SndMmcInfoInd
  Function : MMCGMM_INFO_IND原语填写及发送
  Input    : NAS_MM_INFO_IND_STRU    *pstMmInfo
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1.张志勇  2003.12.08  新规作成

    2.日    期   : 2010年3月23日
      作    者   : o00132663
      修改内容   : NAS R7协议升级，增加支持GMM INFO消息
*******************************************************************************/
VOS_VOID Gmm_SndMmcInfoInd(NAS_MM_INFO_IND_STRU    *pstMmInfo)
{
    MMCGMM_INFO_IND_STRU               *pstMsg          = VOS_NULL_PTR;
    MMCGMM_INFO_IND_STRU               *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                           ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(MMCGMM_INFO_IND_STRU);

    pstInternalMsg  = (MMCGMM_INFO_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_SndMmcInfoInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_INFO_IND;
    pstMsg->stMmInfo                      = *pstMmInfo;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}

/*******************************************************************************
  Module   : Gmm_SndMmcPdpStatusInd
  Function : MMCGMM_PDP_STATUS_IND原语填写及发送
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.08  新规作成

    2.日    期   : 2011年7月14日
      作    者   : zhoujun 40661
      修改内容   : 更新MML_CTX中的链接存在状态
    3.日    期   : 2011年8月11日
      作    者   : W00167002
      修改内容   : ut发现，跟预处理不兼容，需要上报pdpstatus
    4.日    期   : 2012年10月18日
      作    者   : s00217060
      修改内容   : DTS2012071702125:ucPdpStatusFlg标志维护更改
*******************************************************************************/

VOS_VOID Gmm_SndMmcPdpStatusInd(
                            VOS_UINT8 ucPdpStatusFlg
                            )

{
    MMCGMM_PDP_STATUS_IND_STRU          *pstMsg         = VOS_NULL_PTR;
    MMCGMM_PDP_STATUS_IND_STRU          *pstInternalMsg = VOS_NULL_PTR;
    VOS_UINT32                           ulLen;



    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(MMCGMM_PDP_STATUS_IND_STRU);

    pstInternalMsg  = (MMCGMM_PDP_STATUS_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_SndMmcPdpStatusInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_PDP_STATUS_IND;

    pstMsg->ulPdpStatusFlg = ucPdpStatusFlg;



    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}

/*******************************************************************************
  Module   : Gmm_SndMmcStartCnf
  Function : MMCGMM_START_CNF原语填写及发送
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.09  新规作成

*******************************************************************************/
VOS_VOID Gmm_SndMmcStartCnf(VOS_VOID)
{
    MMCGMM_START_CNF_STRU              *pstMsg          = VOS_NULL_PTR;
    MMCGMM_START_CNF_STRU              *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(MMCGMM_START_CNF_STRU);

    pstInternalMsg  = (MMCGMM_START_CNF_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_SndMmcStartCnf,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_START_CNF;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}
/*******************************************************************************
  Module   : Gmm_SndMmcTBFRelInd
  Function : MMCGMM_START_CNF原语填写及发送
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1.日    期   : 2009年09月25日
      作    者   : l00130025
      修改内容   : 问题单号:AT2D14675,RAU/Attach过程中，list搜网失败

    2.日    期   : 2011年7月14日
      作    者   : zhoujun 40661
      修改内容   : 更新MML_CTX中的链接存在状态
*******************************************************************************/
VOS_VOID Gmm_SndMmcTBFRelInd(VOS_VOID)
{
    MMCGMM_TBF_REL_IND_STRU            *pstMsg          = VOS_NULL_PTR;
    MMCGMM_TBF_REL_IND_STRU            *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    NAS_MML_SetPsTbfStatusFlg(VOS_FALSE);

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(MMCGMM_TBF_REL_IND_STRU);

    pstInternalMsg  = (MMCGMM_TBF_REL_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_SndMmcTBFRelInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_TBF_REL_IND;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;

}

/*******************************************************************************
  Module   : Gmm_SndMmcLocalDetachInd
  Function : MMCGMM_LOCAL_DETACH_IND原语填写及发送
  Input    : VOS_UINT32     ulDetachCause             detach原因
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.09  新规作成

*******************************************************************************/
VOS_VOID Gmm_SndMmcLocalDetachInd(
                              VOS_UINT32 ulDetachCause                               /* detach原因                               */
                              )
{
    MMCGMM_LOCAL_DETACH_IND_STRU       *pstMsg          = VOS_NULL_PTR;
    MMCGMM_LOCAL_DETACH_IND_STRU       *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(MMCGMM_LOCAL_DETACH_IND_STRU);

    pstInternalMsg  = (MMCGMM_LOCAL_DETACH_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_SndMmcLocalDetachInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_LOCAL_DETACH_IND;
    pstMsg->ulDetachCause                 = ulDetachCause;                                        /* 填写local detach原因                     */
    pstMsg->ulServiceSts                  = Gmm_ComServiceSts();                                   /* 填写服务状态                             */

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}

/* Deleted by s00261364 for V3R360_eCall项目, 2014-4-11, begin */

/* Deleted by s00261364 for V3R360_eCall项目, 2014-4-11, end */


/*******************************************************************************
  Module   : Gmm_SndRrmmEstReq
  Function : 发送RRMM_EST_REQ原语处理
  Input    : VOS_UINT32           ulEstCause        RRC Connection Setup原因
             VOS_UINT32           ulIdnnsType       3是响应paging的,6代表其他
             NAS_MSG_STRU    *pMsg             该CN Domain的NAS消息首地址
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.09  新规作成
    2.日    期   : 2007年11月1日
      作    者   : l65478
      修改内容   : 问题单号：A32D13307, 清除释放原因值
    3.日    期   : 2011年04月20日
      作    者   : s46746
      修改内容   : 根据问题单号：DTS2011040804149，【V3R1C31B027】【RAU】PS ONLY下，PMM_IDLE态W2G重选后，发起ping未进行RAU流程，无法进行数传
    4.日    期   : 2012年04月25日
      作    者   : l65478
      修改内容   : DTS2012041402691,连接建立ID类型错误
    5. 日    期   : 2012年7月17日
        作    者   : z00161729
        修改内容   : DTS2012071606177:W(LAI1)-L(TAI2/LAI2 ISR激活CS LAI改变)-W(LAI1网络模式I)需要
                     发起联合rau
    6.日    期  : 2013年03月13日
      作    者  : z00214637
      修改内容  : BodySAR项目

*******************************************************************************/
VOS_VOID Gmm_SndRrmmEstReq(
                       VOS_UINT32                     ulEstCause,                    /* RRC Connection Setup原因                 */
                       VOS_UINT32                     ulIdnnsType,                   /* 3是响应paging的,6代表其他                */
                       NAS_MSG_STRU              *pMsg                          /* 该CN Domain的NAS消息首地址               */
                       )
{
    IDNNS_STRU                   Idnns;
    VOS_UINT8                   *pucData;
    VOS_INT32                    lRet;
    VOS_UINT32                   ulRet;
    RRC_PLMN_ID_STRU             stPlmnId;
    NAS_MML_RAI_STRU                       *pstLastSuccRai;
    GMM_PLMN_ID_STRU                        stGmmPlmnId;
    GMM_RAI_STRU                            stRai;
    VOS_UINT8                               ucTmpUeIdMask;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                               aucPtmsi[RRC_NAS_PTMSI_LEN];

    NAS_MML_PLMN_ID_STRU                    stLteRplmn;
#endif

    ucTmpUeIdMask     = GMM_UEID_INVALID;

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmPlmnId);
    stRai.ucRac             = pstLastSuccRai->ucRac;
    stRai.Lai.aucLac[0]     = pstLastSuccRai->stLai.aucLac[0];
    stRai.Lai.aucLac[1]     = pstLastSuccRai->stLai.aucLac[1];
    stRai.Lai.PlmnId        = stGmmPlmnId;

    if(VOS_NULL_PTR == pMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndRrmmEstReq:WARNING: Null pointer");
        return;
    }

    GMM_ReportM2NOtaMsg(pMsg);


    if (3 == ulIdnnsType)
    {                                                                           /* 响应paging的                             */
        Idnns.ucIdnnsType = RRC_IDNNS_IMSI_PAGE_RSP;                            /* 赋值IDdns类型                            */
    }
    else
    {                                                                           /* 需要判断类型的                           */
        /* 如果当前UE靠IMSI识别,此时判断下当前是否支持LTE，支持的话判断从LTE下的
           GUTI映射过来的PTMSI是否有效，有效的话此时UE靠PTMSI识别 */
#if (FEATURE_ON == FEATURE_LTE)
        if (NAS_MML_NET_RAT_TYPE_LTE == gstGmmCasGlobalCtrl.ucLastDataSender)
        {
            if (VOS_TRUE == NAS_MML_GetLteRPlmn(&stLteRplmn))
            {
                NAS_GMM_ConvertPlmnIdToGmmFormat(&stLteRplmn, &stGmmPlmnId);
            }
        }

        ucTmpUeIdMask = NAS_GMM_GetPTmsi_GUL(aucPtmsi);
        if (GMM_UEID_INVALID == ucTmpUeIdMask)
        {
            ucTmpUeIdMask = g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask;
        }
#else
        ucTmpUeIdMask = g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask;
#endif

        if (GMM_UEID_P_TMSI
            == (ucTmpUeIdMask & GMM_UEID_P_TMSI))
        {                                                                       /* UeId存在标识中P_TMSI有效                 */
            if (GMM_FALSE
                == Gmm_Com_CmpPlmnid(&stGmmPlmnId))
            {                                                                   /* PLMN ID 不相同                           */
                Idnns.ucIdnnsType = RRC_IDNNS_TMSI_DIFFER_PLMN;                 /* 赋值IDdns类型                            */
            }

            else if (GMM_FALSE == Gmm_Com_CmpRai(&stRai, &g_GmmGlobalCtrl.SysInfo.Rai, g_GmmGlobalCtrl.ucNetMod))
            {                                                                   /* RAI不同                                  */
                Idnns.ucIdnnsType = RRC_IDNNS_TMSI_DIFFER_LA;                   /* 赋值IDdns类型                            */
            }
            else
            {                                                                   /* LAI相同                                  */
                Idnns.ucIdnnsType = RRC_IDNNS_LOCAL_TMSI;                       /* 赋值IDdns类型                            */
            }
        }
        else if(GMM_UEID_IMSI
                == (ucTmpUeIdMask & GMM_UEID_IMSI))
        {                                                                       /* UeId存在标识中IMSI有效                   */
            Idnns.ucIdnnsType = RRC_IDNNS_IMSI_UE_INIT;
        }
        else
        {                                                                       /* IMEI有效                                 */
            Idnns.ucIdnnsType = RRC_IDNNS_IMEI;                                 /* 赋值IDdns类型                            */
        }
    }
    if ((g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.aucMccDigit[0]
        != stGmmPlmnId.aucMccDigit[0])
        || (g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.aucMccDigit[1]
        != stGmmPlmnId.aucMccDigit[1]))
    {                                                                           /* 系统信息中RAI的最高字节不同于UE信息中的  */
        Idnns.ucEnterPara = NAS_RRC_SPLMN_DIFF_RPLMN;                                           /* 赋值Entered parameter                    */
    }
    else
    {                                                                           /* 系统信息中RAI的最高字节相同于UE信息中的  */
        Idnns.ucEnterPara = NAS_RRC_SPLMN_SAME_RPLMN;                                          /* 赋值Entered parameter                    */
    }

    stPlmnId.ulMcc = g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.aucMccDigit[0]
                   + ((VOS_UINT32)g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.aucMccDigit[1]<<8)
                   + ((VOS_UINT32)g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.aucMccDigit[2]<<16);

    stPlmnId.ulMnc = g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.aucMncDigit[0]
                   + ((VOS_UINT32)g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.aucMncDigit[1]<<8)
                   + ((VOS_UINT32)g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.aucMncDigit[2]<<16);

    g_GmmReqCnfMng.ucRrmmEstOpid
        = (g_GmmReqCnfMng.ucRrmmEstOpid+1) % GMM_MAX_OPID;
    if (GMM_FALSE == GMM_IsCasGsmMode())
    {   /*如果是W,则调用原来处理过程*/
        pucData = pMsg->aucNasMsg;
        lRet = (*g_GmmImportFunc.RrmmEstReqFunc)(g_GmmReqCnfMng.ucRrmmEstOpid,
                                       RRC_NAS_PS_DOMAIN,
                                       ulEstCause,
                                       &Idnns,
                                       &stPlmnId,
                                       pMsg->ulNasMsgSize,
                                       (VOS_INT8 *)pucData
                                       );                   /* 调用发送函数 */
        if (AS_SUCCESS != lRet)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndRrmmEstReq:WARNING: Send msg fail.");
        }
    }
    else
    {   /*GPRS情况*/
        GMM_SndRrmmEstReqGsm(g_GmmReqCnfMng.ucRrmmEstOpid, pMsg);
    }

    g_GmmReqCnfMng.ucCnfMask |= GMM_RRC_RRMM_EST_CNF_FLG;                       /* 置等待响应标志                           */
    /* 清除释放原因值 */
    g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;

    if ((GMM_DETACH_COMBINED_POWER_OFF > g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_SIM_REMOVE < g_GmmGlobalCtrl.ucSpecProc))
    {
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ESTING);          /* 通知MMC PS域信令连接正在建立             */
    }

    ulRet = Gmm_MemFree(pMsg);                                      /* 释放申请的内存空间                       */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndRrmmEstReq:WARNING: Free msg fail.");
    }

    g_GmmGlobalCtrl.ucTime2Sndout = VOS_TRUE;

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_Com_CmpPlmnid
  Function : 比较系统信息与UE信息中的PLMN ID是否相同
  Input    : GMM_PLMN_ID_STRU *pPlmnId
  Output   : 无
  NOTE     : 无
  Return   : GMM_TRUE   相同
             GMM_FALSE  不同
  History  :
    1. 张志勇  2003.12.09  新规作成
*******************************************************************************/
VOS_UINT8 Gmm_Com_CmpPlmnid(
                        GMM_PLMN_ID_STRU *pPlmnId                               /* 指向PLMN的指针                           */
                        )
{
    VOS_UINT8           i;                                                          /* 定义临时变量                             */

    for (i=0; i<3; i++)
    {                                                                           /* 在MCC个数内判断                          */
        if (g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.aucMccDigit[i]
            != pPlmnId->aucMccDigit[i])
        {                                                                       /* MCC不相同                                */
            return GMM_FALSE;                                                   /* 返回GMM_FALSE                            */
        }
    }

    if (g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.ucMncCnt != pPlmnId->ucMncCnt)
    {                                                                           /* MNC个数不相同                            */
        return GMM_FALSE;                                                       /* 返回GMM_FALSE                            */
    }

    for (i=0; i<g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.ucMncCnt; i++)
    {                                                                           /* 在MNC个数内判断                          */
        if (g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.aucMncDigit[i]
            != pPlmnId->aucMncDigit[i])
        {                                                                       /* MNC不相同                                */
            return GMM_FALSE;                                                   /* 返回GMM_FALSE                            */
        }
    }

    return GMM_TRUE;                                                            /* 返回GMM_TRUE                             */
}

/*******************************************************************************
  Module   : Gmm_SndRrmmDataReq
  Function : 发送RRMM_DATA_REQ原语处理
  Input    : VOS_UINT8          ucPriorityInd      消息优先级指示
             NAS_MSG_STRU   *Msg               该CN Domain的NAS消息首地址
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.09  新规作成
    2.日    期  : 2013年03月13日
      作    者  : z00214637
      修改内容  : BodySAR项目

*******************************************************************************/
VOS_VOID Gmm_SndRrmmDataReq(
                        VOS_UINT8               ucPriorityInd,                      /* 消息优先级指示                           */
                        NAS_MSG_STRU        *pMsg                               /* 该CN Domain的NAS消息首地址               */
                        )
{
    VOS_INT32  lRet;
    VOS_UINT32 ulRet;
    if(VOS_NULL_PTR == pMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndRrmmDataReq:WARNING: Null pointer");
        return;
    }

    GMM_ReportM2NOtaMsg(pMsg);


    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        GMM_SndRrmmDataReqGsm(pMsg);    /* 2G模式GMM消息发送 */
        ulRet = Gmm_MemFree(pMsg);                                       /* 释放申请的内存空间 */
        if (VOS_OK != ulRet)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndRrmmDataReq:WARNING: Free msg fail.");
        }
        return;
    }

    lRet = (g_GmmImportFunc.RrmmDataReqFunc)(RRC_NAS_PS_DOMAIN,
                                    ucPriorityInd,
                                    pMsg->ulNasMsgSize,
                                    (VOS_INT8 *)pMsg->aucNasMsg);                   /* 调用发送函数                             */

    gstGmmCasGlobalCtrl.ucLastDataSender = NAS_MML_NET_RAT_TYPE_WCDMA;

    if (AS_SUCCESS != lRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndRrmmDataReq:WARNING: Send msg fail.");
    }

    ulRet = Gmm_MemFree(pMsg);                                      /* 释放申请的内存空间                       */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndRrmmDataReq:WARNING: Free msg fail.");
    }
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_SndRrmmRelReq
  Function : 发送RRMM_REL_REQ原语处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.09  新规作成
*******************************************************************************/
VOS_VOID Gmm_SndRrmmRelReq(RRC_CELL_BAR_ENUM_UINT32  enBarValidFlg)
{
    VOS_INT32 lRet;

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        GMM_SndRrmmRelReqGsm();

        return;
    }

    lRet = (*g_GmmImportFunc.RrmmRelReqFunc)(RRC_NAS_PS_DOMAIN,enBarValidFlg);                /* 调用发送函数                             */
    if (AS_SUCCESS != lRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndRrmmRelReq:WARNING: Send msg fail.");
    }
    return;                                                                     /* 返回                                     */
}

/*****************************************************************************
 函 数 名  : NAS_GMM_SndRrmmRelCsPsAllConnReq
 功能描述  : 通知接入层连接释放，目前只有svlte tdd模式下本地detach ps时有连接时通知tds
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月21日
     作    者   : z00161729
     修改内容   : DTS2014032105704:国内TDS丢网瞬间找回原小区ps迁移modem1后不再回迁modem0

*****************************************************************************/
VOS_VOID  NAS_GMM_SndRrmmRelCsPsAllConnReq(VOS_VOID)
{
    RRMM_REL_CS_PS_ALL_CONN_REQ_STRU   *pstMsg = VOS_NULL_PTR;

    pstMsg = (RRMM_REL_CS_PS_ALL_CONN_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                          sizeof(RRMM_REL_CS_PS_ALL_CONN_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_GMM_SndRrmmRelCsPsAllConnReq:WARNING: Memory Alloc Fail.");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstMsg) + VOS_MSG_HEAD_LENGTH, 0, sizeof(RRMM_REL_CS_PS_ALL_CONN_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_WRR;
    pstMsg->stMsgHeader.ulLength        = sizeof(RRMM_REL_CS_PS_ALL_CONN_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = RRMM_REL_CS_PS_ALL_CONN_REQ;

    if (VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_GMM, (struct MsgCB **)&pstMsg))
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndRrmmRelCsPsAllConnReq Snd msg fail!");
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_SyncNasInfoChange_RegisteredStatus
 功能描述  : 注册状态，向AS同步NAS的消息
 输入参数  : VOS_UINT32 ulMask, 需要发送的标志位
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月29日
    作    者   : l00130025
    修改内容   : DTS2012022206186,W/G下注册状态更新错误,修改为只在注册状态发送

  2.日    期   : 2012年10月20日
    作    者   : l00167671
    修改内容   : DTS2012082707059,LTE CSFB TO GSM(重定向MOCALL)没有发送ATTACH
                 状态给GAS
*****************************************************************************/
VOS_VOID  NAS_GMM_SyncNasInfoChange_RegisteredStatus(VOS_UINT32 ulMask)
{
    GMM_STATE_TYPE_UINT8                     ucState;

    if ((GMM_SUSPENDED_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState)
     || (GMM_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState)
     || (GMM_SUSPENDED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
     || (GMM_SUSPENDED_WAIT_FOR_SYSINFO == g_GmmGlobalCtrl.ucState))
    {
        ucState = gstGmmSuspendCtrl.ucPreState;
    }
    else
    {
        ucState = g_GmmGlobalCtrl.ucState;
    }

    if ((GMM_REGISTERED_NORMAL_SERVICE == ucState)
     || (GMM_REGISTERED_LIMITED_SERVICE == ucState)
     || (GMM_REGISTERED_UPDATE_NEEDED == ucState)
     || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == ucState)
     || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == ucState)
     || (GMM_REGISTERED_NO_CELL_AVAILABLE == ucState)
     || (GMM_REGISTERED_PLMN_SEARCH == ucState)
     || (GMM_REGISTERED_IMSI_DETACH_INITIATED == ucState)
     || (GMM_ROUTING_AREA_UPDATING_INITIATED == ucState)
     || (GMM_SERVICE_REQUEST_INITIATED == ucState))
    {
        Gmm_SndRrmmNasInfoChangeReq(ulMask);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_SndWasInfoChangeReq
 功能描述  : 向Was发送Nas Gmm的信息变更通知
 输入参数  : VOS_UINT32 ulMask, 需要发送的标志位
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月29日
    作    者   : l00130025
    修改内容   : DTS2011082201679/DTS2011121504358,W/G下注册状态没有更新
  2.日    期   : 2012年8月14日
    作    者   : t00212959
    修改内容   : DCM定制需求和遗留问题
  3.日    期   : 2014年4月24日
    作    者   : s00217060
    修改内容   : 从L模获取映射的安全上下文之后，通知GU模
*****************************************************************************/
VOS_VOID  NAS_GMM_SndWasInfoChangeReq(VOS_UINT32 ulMask)
{

    RRMM_NAS_INFO_CHANGE_REQ_STRU      *pstNasInfoMsg = VOS_NULL_PTR;

    pstNasInfoMsg = (RRMM_NAS_INFO_CHANGE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                     WUEPS_PID_GMM, sizeof(RRMM_NAS_INFO_CHANGE_REQ_STRU));

    if (VOS_NULL_PTR == pstNasInfoMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstNasInfoMsg + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(RRMM_NAS_INFO_CHANGE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstNasInfoMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstNasInfoMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_WRR;
    pstNasInfoMsg->MsgHeader.ulMsgName       = RRMM_NAS_INFO_CHANGE_REQ;                              /* 消息名称                                  */

    /* 设置发送域 */
    pstNasInfoMsg->ulCnDomainCnt            = 1;
    pstNasInfoMsg->aNasInfo[0].ulCnDomainId = RRC_NAS_PS_DOMAIN;

    /* Attach状态填充 */
    if (RRC_NAS_MASK_ATTACH == (RRC_NAS_MASK_ATTACH & ulMask))
    {
        pstNasInfoMsg->aNasInfo[0].bitOpAttach  = VOS_TRUE;
        pstNasInfoMsg->aNasInfo[0].ulAttach     = NAS_GMM_GetAttachStatus();

    }

    /* DRX长度填充 */
    if (RRC_NAS_MASK_DRX == (RRC_NAS_MASK_DRX & ulMask))
    {
        pstNasInfoMsg->aNasInfo[0].bitOpDrxLength = VOS_TRUE;

        /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-14, begin */
        pstNasInfoMsg->aNasInfo[0].ulDrxLength    = (VOS_UINT32)NAS_MML_GetWSysInfoDrxLen();
        /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-14, end */

    }

    /* UMTS CK IK 信息填充 */
    if (RRC_NAS_MASK_SECURITY_KEY == ( RRC_NAS_MASK_SECURITY_KEY & ulMask ) )
    {
        pstNasInfoMsg->aNasInfo[0].bitOpSecurityKey = VOS_TRUE;

        PS_MEM_CPY(pstNasInfoMsg->aNasInfo[0].SecurityKey.aucCk,
                   NAS_MML_GetSimPsSecurityUmtsCk(), NAS_MML_UMTS_CK_LEN);
        PS_MEM_CPY(pstNasInfoMsg->aNasInfo[0].SecurityKey.aucIk,
                   NAS_MML_GetSimPsSecurityUmtsIk(), NAS_MML_UMTS_IK_LEN);
    }

    /* P_TMSI和RAI赋值 */
    if (RRC_NAS_MASK_PTMSI_RAI == (ulMask & RRC_NAS_MASK_PTMSI_RAI))
    {
        pstNasInfoMsg->aNasInfo[0].bitOpPTmsiRai = VOS_TRUE;

        NAS_GMM_GetPTmsiRAI(&(pstNasInfoMsg->aNasInfo[0].PTmsiRai));

    }

    /* Del Key Op项设置 */
    if (RRC_NAS_MASK_DEL_KEY == (ulMask & RRC_NAS_MASK_DEL_KEY))
    {
        pstNasInfoMsg->aNasInfo[0].bitDelKey = VOS_TRUE;
    }

    /* RRC_NAS_MASK_MAPPED_SECURITY_KEY项设置 */
    if (RRC_NAS_MASK_MAPPED_SECURITY_KEY == (ulMask & RRC_NAS_MASK_MAPPED_SECURITY_KEY))
    {
        pstNasInfoMsg->aNasInfo[0].bitOpIdleMappedLSecurity = VOS_TRUE;

        PS_MEM_CPY(pstNasInfoMsg->aNasInfo[0].SecurityKey.aucCk,
                   NAS_MML_GetSimPsSecurityUmtsCk(), NAS_MML_UMTS_CK_LEN);
        PS_MEM_CPY(pstNasInfoMsg->aNasInfo[0].SecurityKey.aucIk,
                   NAS_MML_GetSimPsSecurityUmtsIk(), NAS_MML_UMTS_IK_LEN);
    }


    /* 向Was 发送结果 */
    if (VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_GMM, (struct MsgCB **)&pstNasInfoMsg))
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndWasInfoChangeReq Snd pstNasInfoMsg fail!");
    }

    return;

}


/*******************************************************************************
  Module   : Gmm_SndRrmmNasInfoChangeReq
  Function : 发送RRMM_NAS_INFO_CHANGE_REQ原语处理
  Input    : VOS_UINT32  ulMask        各IE有效标志
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1. 张志勇  2003.12.09  新规作成
  2. 张志勇  2004.10.25  SECURITY_KEY_INFO_STRU变更对应
  3.日    期   : 2009年03月25日
    作    者   : h44270
    修改内容   : 问题单AT2D10415,USIM GCF测试的无卡紧急呼叫有问题
  4.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  5.日    期   : 2011年12月29日
    作    者   : l00130025
    修改内容   : DTS2011082201679/DTS2011121504358,切换模式，回退后W/G下注册状态没有与NAS同步
*******************************************************************************/
VOS_VOID Gmm_SndRrmmNasInfoChangeReq(VOS_UINT32 ulMask)
{

    if (RRC_NAS_MASK_NULL == ulMask)
    {
        return;
    }

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        NAS_GMM_SndGasInfoChangeReq(ulMask);
    }
    else if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        NAS_GMM_SndWasInfoChangeReq(ulMask);
    }
    else
    {

    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_SndSmEstablishCnf
  Function : 原语SM_ESTABLISH_CNF的发送处理
  Input    : VOS_UINT32      ulEstResult     注册结果
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.09  新规作成
    2.日    期  : 2012年08月24日
      作    者  : m00217266
      修改内容  : 添加enCause入参，上报注册成功或失败原因值

*******************************************************************************/
VOS_VOID Gmm_SndSmEstablishCnf(
                           VOS_UINT32                   ulEstResult,             /* 注册结果                                 */
                           GMM_SM_CAUSE_ENUM_UINT16     enCause                  /* 注册失败原因值 */
                           )
{
    GMMSM_ESTABLISH_CNF_STRU   *pMsg;                                           /* 定义指针                                 */
    VOS_UINT32                  ulRet;
    pMsg = (GMMSM_ESTABLISH_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                        sizeof(GMMSM_ESTABLISH_CNF_STRU));                      /* 申请内存                                 */
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR *)pMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(GMMSM_ESTABLISH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SM;
    pMsg->MsgHeader.ulMsgName   = GMMSM_ESTABLISH_CNF;                          /* 原语名称                                 */

    pMsg->ulEstResult = ulEstResult;                                            /* 注册结果                                 */


    pMsg->enCause     = enCause;


    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                                   /* 原语发送                                 */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndSmEstablishCnf:WARNING: Send msg fail.");
    }
    return;
}

/*******************************************************************************
Module   : Gmm_SndSmStatusInd
Function : 原语GMMSM_STATUS_IND的发送处理
Input    : 无
Output   : 无
NOTE     : 无
Return   : 无
History  :
 1. 张志勇  2003.12.09  新规作成
 2. 日    期   : 2009-6-3
    作    者   : l00130025
    修改内容   : 问题单号:AT2D12225,从GPRS小区重选到GSM小区,t3312超时后,重回原GPRS小区,发起了normal RAU而非周期性RAU
 3. 日    期   : 2012-04-27
    作    者   : l65478
    修改内容   : DTS2012042406368,原因值#7时LMM流程错误
 4. 日    期   : 2012-07-27
    作    者   : z00161729
    修改内容   : DTS2012072600458:cs ps mode 2 L下联合注册成功，用户detach ps disable lte
                 到W搜网成功cs注册成功，gmm 收到lmm的mo detach ind未通知sm当前detach状态，
                 导致后续ndis拨号sm没通知gmm attach拨号失败
 5. 日    期   : 2012年8月25日
    作    者   : m00217266
    修改内容   : 修改GMM上报原因值逻辑，当由ATTACH切换到DETACH时，非L模时上报g_GmmGlobalCtrl中的原因值
 6. 日    期   : 2012年10月18日
    作    者   : s00217060
    修改内容   : DTS2012071702125:ucPdpStatusFlg标志维护更改
 7. 日    期  :2014年01月09日
    作    者  :l65478
    修改内容  :DTS2014010704608:第一次鉴权响应和网络发起的第二次鉴权请求冲突

*******************************************************************************/
VOS_VOID Gmm_SndSmStatusInd(VOS_VOID)
{
    GMMSM_STATUS_IND_STRU   *pMsg;                                              /* 定义指针                                 */

    VOS_UINT32               ulGmmStatus;

    VOS_UINT8                   ucAttachSta;

    VOS_UINT8                ucStateChange = GMM_FALSE;
    VOS_UINT32               ulRet;

    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus;

    pstConnStatus   = NAS_MML_GetConnStatus();

    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_DEREGISTERED_NORMAL_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
    case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_PLMN_SEARCH:
    case GMM_DEREGISTERED_NO_IMSI:
    case GMM_NULL:
        ucAttachSta = GMM_STATUS_DETACHED;
        NAS_GMM_ClearAuthInfo();

#if (FEATURE_LTE == FEATURE_ON)
        if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
        {
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
        }
#endif

        Gmm_TimerStop(GMM_TIMER_T3312);                                         /* 停止T3312                                */
#if (FEATURE_LTE == FEATURE_ON)
        if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            Gmm_TimerStop(GMM_TIMER_T3323);
        }
#endif
        g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_DISABLE;

        break;

    case GMM_REGISTERED_LIMITED_SERVICE:

        ucAttachSta = GMM_STATUS_ATTACHED;
        g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_DISABLE;

        break;

    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:

        ucAttachSta = GMM_STATUS_ATTACHED;
        g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_DISABLE;

        break;
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
        ucAttachSta = GMM_STATUS_ATTACHED;

        g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;

        break;
    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
    case GMM_REGISTERED_PLMN_SEARCH:

        ucAttachSta = GMM_STATUS_ATTACHED;
        g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_DISABLE;

        break;
    case GMM_SUSPENDED_NORMAL_SERVICE:
    case GMM_SUSPENDED_GPRS_SUSPENSION:
    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
        return;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_SndSmStatusInd:INFO: g_GmmGlobalCtrl.ucState need not report");
        return;

    }

    if (ucAttachSta != g_MmSubLyrShare.GmmShare.ucAttachSta)
    {
        ucStateChange = GMM_TRUE;
        g_MmSubLyrShare.GmmShare.ucAttachSta = ucAttachSta;                         /* 更新全局量                               */
        Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_ATTACH);
        Gmm_SndSmsRegStateInd();                                                    /* 发送原语GMMSMS_REG_STATE_IND             */
    }


    /*if (GMM_STATUS_DETACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)*/
    if ((GMM_STATUS_DETACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
        && (GMM_TRUE == ucStateChange))
    {
        if (VOS_TRUE == NAS_MML_IsPsBearerExist())
        {                                                                        /* 存在激活的PDP context                   */
            NAS_MML_InitPsBearerContext(NAS_MML_GetPsBearerCtx());

            Gmm_SndMmcPdpStatusInd(MMC_GMM_ACTIVE_PDP_CONTEXT_NOT_EXIST);       /* 通知MMC PDP context 状态更新             */
            pstConnStatus->ucPdpStatusFlg       = VOS_FALSE;

        }
        ulGmmStatus = GMM_SM_STATUS_DETACHED;                         /* 改变后的GMM注册状态                      */
    }
    else if (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
    {
        if ((GMM_TRUE == g_GmmServiceCtrl.ucRejCauseVaildFlg)
         && (NAS_MML_REG_FAIL_CAUSE_NO_PDP_CONTEXT_ACT == g_GmmServiceCtrl.ucRejCause))
        {
            /*if ((0 != g_GmmGlobalCtrl.UeInfo.aucPdpContextSta[0])
             || (0 != g_GmmGlobalCtrl.UeInfo.aucPdpContextSta[1]))
            { */                                                                    /* 存在激活的PDP context                   */
            NAS_MML_InitPsBearerContext(NAS_MML_GetPsBearerCtx());

            Gmm_SndMmcPdpStatusInd(MMC_GMM_ACTIVE_PDP_CONTEXT_NOT_EXIST);       /* 通知MMC PDP context 状态更新             */
            /*}*/

            pstConnStatus->ucPdpStatusFlg       = VOS_FALSE;

            ulGmmStatus = GMM_SM_SER_REJ_CAUSE_PDP_NOEXIT;                    /* GMM_SM_STATUS_DEACTIVE;GMM_SM_STATUS_DETACHED;*/
        }
        else if (GMM_TRUE == ucStateChange)
        {
            ulGmmStatus = GMM_SM_STATUS_ATTACHED;                             /* 改变后的GMM注册状态                      */
        }
        else
        {
            return;
        }
    }
    else
    {
        return;
    }

    pMsg = (GMMSM_STATUS_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                        sizeof(GMMSM_STATUS_IND_STRU));                         /* 申请内存                                 */
    if (VOS_NULL_PTR == pMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndSmStatusInd:WARNING: Alloc Memory Fail.");
        return;
    }

    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SM;
    pMsg->MsgHeader.ulMsgName   = GMMSM_STATUS_IND;                             /* 原语名称                                 */

    pMsg->ulGmmStatus           = ulGmmStatus;

    /* 对四字节对齐reserve字节初始化 */
    pMsg->aucRsv[0] = 0;
    pMsg->aucRsv[1] = 0;

    /* 在L下被网络拒绝导致GMM进入去注册状态,通知SM去注册时,
       会导致L下无法处理网络原因值而导致流程错误 */
    /* 填写DETACH原因值 */
    /* 上报导致GMM状态改变的原因值 */
    /* DETACH -> ATTACH原因值: GMM_SM_CAUSE_BUTT */
    /* ATTACH -> DETACH原因值: L模:GMM_SM_CAUSE_LTE_MO_DETACH */
    /* ---------------------其他模:g_GmmGlobalCtrl.enGmmCause */
    pMsg->enCause = GMM_SM_CAUSE_BUTT;

    if (GMM_SM_STATUS_DETACHED == ulGmmStatus)
    {
        pMsg->enCause = NAS_GMM_GetAttach2DetachErrCode();

        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            pMsg->enCause = GMM_SM_CAUSE_LTE_MO_DETACH;
        }
    }

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                                    /* 原语发送                                 */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndSmStatusInd:WARNING: Send msg Fail.");
    }
    return;
}

/*******************************************************************************
  Module   : NAS_GMM_SndSmStatusInd
  Function : 原语GMMSM STATUS IND的发送处理
  Input    : ulGmmStatus : GMM Status:0  Detach 1 Attach
             enCause: 原因值
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 日    期: 2014-3-12
       作    者：f00261443
       修改内容: 新生成函数

*******************************************************************************/
VOS_VOID NAS_GMM_SndSmStatusInd(
    VOS_UINT32                          ulGmmStatus,
    GMM_SM_CAUSE_ENUM_UINT16            enCause
)
{

    GMMSM_STATUS_IND_STRU              *pstMsg = VOS_NULL_PTR;                                  /* 定义指针                                 */
    VOS_UINT32                          ulRet;

    pstMsg = (GMMSM_STATUS_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                        sizeof(GMMSM_STATUS_IND_STRU));                         /* 申请内存                                 */
    if (VOS_NULL_PTR == pstMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_SndSmStatusInd:WARNING: Alloc Memory Fail.");
        return;
    }

    pstMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SM;
    pstMsg->MsgHeader.ulMsgName   = GMMSM_STATUS_IND;                             /* 原语名称                                 */

    pstMsg->ulGmmStatus           = ulGmmStatus;
    pstMsg->enCause = enCause;

    pstMsg->aucRsv[0] = 0;
    pstMsg->aucRsv[1] = 0;

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pstMsg);                                    /* 原语发送                                 */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_SndSmStatusInd:WARNING: Send msg Fail.");
    }
    return;

}

/*******************************************************************************
  Module   : Gmm_SndSmDataInd
  Function : 原语GMMSM_DATA_IND的发送处理
  Input    : NAS_MSG_STRU    *pSmMsg     要发送消息的的指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.09  新规作成

*******************************************************************************/
VOS_VOID Gmm_SndSmDataInd(
                      NAS_MSG_FOR_PCLINT_STRU          *pSmMsg
                      )
{
    VOS_UINT8              i;                                                   /* 定义循环控制变量                         */
    GMMSM_DATA_IND_STRU   *pMsg;                                                /* 定义临时变量                             */
    VOS_UINT32             ulRet;

    if (4 < pSmMsg->ulNasMsgSize)
    {
        pMsg = (GMMSM_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                (sizeof(GMMSM_DATA_IND_STRU) + pSmMsg->ulNasMsgSize) - 4);        /* 申请内存                                 */

    }
    else
    {
        pMsg = (GMMSM_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                                                sizeof(GMMSM_DATA_IND_STRU));   /* 申请内存                                 */
    }
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SM;
    pMsg->MsgHeader.ulMsgName   = GMMSM_DATA_IND;                               /* 原语名称                                 */

    pMsg->SmMsg.ulNasMsgSize = pSmMsg->ulNasMsgSize;                            /* 填写消息长度                             */
    for (i=0; i<pSmMsg->ulNasMsgSize; i++)
    {
        pMsg->SmMsg.aucNasMsg[i] = pSmMsg->aucNasMsg[i];                        /* 填写消息内容                             */
    }

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                                   /* 原语发送                                 */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndSmDataInd:WARNING: Send msg Fail.");
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_SndSmServiceRej
  Function : 原语GMMSM_SERVICE_REJ的发送处理
  Input    :
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. s46746  2006.08.15  新规作成
    2.日    期  : 2012年08月24日
      作    者  : m00217266
      修改内容  : 添加enCause入参，上报拒绝原因值

*******************************************************************************/
VOS_VOID GMM_SndSmServiceRej(
                        GMM_SM_CAUSE_ENUM_UINT16     enCause
                        )
{
    GMMSM_SERVICE_REJ_STRU   *pMsg;                                                /* 定义临时变量                             */
    VOS_UINT32                ulRet;

    pMsg = (GMMSM_SERVICE_REJ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                          sizeof(GMMSM_SERVICE_REJ_STRU));   /* 申请内存                                 */
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_CHAR*)pMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(GMMSM_SERVICE_REJ_STRU) - VOS_MSG_HEAD_LENGTH);

    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SM;
    pMsg->MsgHeader.ulMsgName       = GMMSM_SERVICE_REJ;                               /* 原语名称                                 */

    pMsg->enCause = enCause;

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                                      /* 原语发送                                 */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "GMM_SndSmServiceRej:WARNING: Send msg Fail.");
    }
    return;
}
/*******************************************************************************
  Module   : Gmm_SndSmPdpStatusInd
  Function : 原语Gmm_SndSmPdpStatusInd的发送处理
  Input    :
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    10.日    期  : 2007年10月27日
       作    者  : luojian id:107747
       修改内容  : 问题单号:A32D13038
    11.日    期  : 2012年3月17日
       作    者  : z00161729
       修改内容  : V7R1C50支持ISR修改
    12.日    期  : 2012年08月24日
       作    者  : m00217266
       修改内容  : 修改Gmm_SndSmEstablishCnf接口，添加原因值
*******************************************************************************/
VOS_VOID Gmm_SndSmPdpStatusInd(
                        VOS_UINT32                      ulPDPStaus,
                        GMM_SM_CAUSE_ENUM_UINT16        enCause
                        )
{
    GMMSM_PDP_STATUS_IND_STRU          *pMsg;
    VOS_UINT32                          ulRet;

    VOS_UINT8                           i;
    VOS_UINT32                          ulPdpContextStatus;

    pMsg = (GMMSM_PDP_STATUS_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                          sizeof(GMMSM_PDP_STATUS_IND_STRU));   /* 申请内存                                 */
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_CHAR*)pMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(GMMSM_PDP_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SM;
    pMsg->MsgHeader.ulMsgName       = GMMSM_PDP_STATUS_IND;                               /* 原语名称                                 */

    pMsg->enCause = enCause;

    for (i = 0; i < NAS_MML_MAX_PS_BEARER_NUM; i++)
    {
        pMsg->aucPdpContextStatus[i] = GMMSM_PDP_STATE_INACTIVE;
        /*lint -e701*/
        ulPdpContextStatus = (ulPDPStaus) & (0x00000001 << (i + NAS_MML_NSAPI_OFFSET));
        /*lint +e701*/
        if (GMMSM_PDP_STATE_INACTIVE != ulPdpContextStatus)
        {
            pMsg->aucPdpContextStatus[i] = GMMSM_PDP_STATE_ACTIVE;
        }
    }

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                                      /* 原语发送                                 */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndSmPdpStatusInd:WARNING: Send msg Fail.");
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_SndSmSysInfoInd
  Function : 原语Gmm_SndSmSysInfoInd的发送处理
  Input    :
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    10.日    期  : 2009年05月12日
       作    者  : ouyangfei id:o00132663
       修改内容  : 新创函数
*******************************************************************************/
VOS_VOID Gmm_SndSmSysInfoInd(VOS_UINT8 ucSgsnRelease)
{
    GMMSM_SYS_INFO_IND_STRU   *pMsg;
    VOS_UINT32                 ulRet;

    pMsg = (GMMSM_SYS_INFO_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                          sizeof(GMMSM_SYS_INFO_IND_STRU));   /* 申请内存                                 */
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }
    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SM;
    pMsg->MsgHeader.ulMsgName       = GMMSM_SYS_INFO_IND;                               /* 原语名称                                 */
    pMsg->ucSgsnRelVer              = ucSgsnRelease;

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                                      /* 原语发送                                 */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndSmSysInfoInd:WARNING: Send msg Fail.");
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_SndSmRelInd
  Function : 原语GMMSM_REL_IND的发送处理
  Input    :
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. x00115505  2009.07.23  新规作成

*******************************************************************************/
VOS_VOID Gmm_SndSmRelInd(VOS_VOID)
{
    GMMSM_REL_IND_STRU        *pMsg;
    VOS_UINT32                ulRet;

    pMsg = (GMMSM_REL_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                          sizeof(GMMSM_REL_IND_STRU));
    if (VOS_NULL_PTR == pMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_SndSmRelInd:WARNING: Memory Alloc Fail.");
        return;
    }

    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SM;
    pMsg->MsgHeader.ulMsgName   = GMMSM_REL_IND;

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);

    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndSmRelInd:WARNING: Send msg Fail.");
    }
    return;
}
/*******************************************************************************
  Module   : Gmm_SndRabmReestablishCnf
  Function : 发送GMMRABM_REESTABLISH_CNF原语处理
  Input    : VOS_UINT8  ucResult    SERVICE REQUEST成功失败标志
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.09  新规作成

*******************************************************************************/
VOS_VOID Gmm_SndRabmReestablishCnf(
                               VOS_UINT8            ucResult                        /* SERVICE REQUEST成功失败标志              */
                               )
{
    GMMRABM_REESTABLISH_CNF_STRU   *pMsg;                                       /* 定义指针                                 */
    VOS_UINT32                      ulRet;

    pMsg = (GMMRABM_REESTABLISH_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                        sizeof(GMMRABM_REESTABLISH_CNF_STRU));                  /* 申请内存                                 */
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_RABM;
    pMsg->MsgHeader.ulMsgName   = ID_GMM_RABM_REESTABLISH_CNF;                      /* 原语名称                                 */

    pMsg->ulResult = ucResult;                                                  /* 置SERVICE REQUEST成功失败标志            */

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                                   /* 原语发送                                 */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndRabmReestablishCnf:WARNING: Send msg Fail.");
    }
    return;
}

/*lint -save -e961 */
/*******************************************************************************
  Module   : Gmm_Com_DealOfPlmnList
  Function : PLMN ID的填写
  Input    : VOS_VOID                   *pEquPlmnIdList   等效PLMN列表首地址
             MMCGMM_PLMN_ID_STRU    *pPlmnId          原语中的PLMN LIST的首地址
  Output   : 无
  NOTE     : 无
  Return   : GMM_FALSE  没有PLMN列表
             GMM_TRUE   有PLMN列表
  History  :
    1. 张志勇  2003.12.10  新规作成
    2. 日    期: 2013-08-30
       作    者: w00242748
       修改内容: KLCO告警清理
*******************************************************************************/
VOS_UINT8 Gmm_Com_DealOfPlmnList(
                            VOS_VOID                    *pEquPlmnIdList,            /* 等效PLMN列表首地址                       */
                            MMCGMM_PLMN_ID_STRU     *pPlmnId                    /* 原语中的PLMN LIST的首地址                */
                            )
{
    VOS_UINT8                   i;                                                  /* 定义循环控制变量                         */
    GMM_PLMN_ID_STRU            *pGmmPlmnId;                                        /* 定义变量                                 */
    VOS_UINT32                   ulMccDigit1;
    VOS_UINT32                   ulMccDigit2;
    VOS_UINT32                   ulMncDigit1;
    VOS_UINT32                   ulMncDigit2;
    VOS_UINT8                           ucEplmnNum;

    ulMccDigit1 = 0;
    ulMccDigit2 = 0;
    ulMncDigit1 = 0;
    ulMncDigit2 = 0;

    if (VOS_NULL_PTR == pEquPlmnIdList)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_Com_DealOfPlmnList:INFO: The Entry Pointer is VOS_NULL_PTR");
        return GMM_FALSE;                                                       /* 返回                                     */
    }

    pGmmPlmnId = (GMM_PLMN_ID_STRU *)Gmm_MemMalloc(sizeof(GMM_PLMN_ID_STRU)
                                                   * MMC_GMM_MAX_EQUPLMN_NUM);  /* 申请内存空间                             */
    if (VOS_NULL_PTR == pGmmPlmnId)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_Com_DealOfPlmnList:WARNING: Alloc mem fail.");
        return GMM_FALSE;                                                       /* 返回                                     */
    }
    Gmm_MemSet(pGmmPlmnId, 0, sizeof(GMM_PLMN_ID_STRU)*MMC_GMM_MAX_EQUPLMN_NUM);/* 将申请的内存空间清0                      */

    ucEplmnNum = NAS_COMM_MIN((*((VOS_UINT8 *)pEquPlmnIdList +1) / 3), MMC_GMM_MAX_EQUPLMN_NUM);

    for (i=0; i<ucEplmnNum; i++)
    {                                                                           /* 将PLMN List存储到临时变量                */
        pGmmPlmnId[i].aucMccDigit[0] = (VOS_UINT8)(*((VOS_UINT8 *)pEquPlmnIdList
                                                        + 2 + (i * 3)) & 0x0F);   /* MCC digit 1 of PLMN i                    */
        pGmmPlmnId[i].aucMccDigit[1] = (VOS_UINT8)((*((VOS_UINT8 *)pEquPlmnIdList
                                                  + 2 + (i * 3)) >> 4) & 0x0F);   /* MCC digit 2 of PLMN i                    */
        pGmmPlmnId[i].aucMccDigit[2] = (VOS_UINT8)(*((VOS_UINT8 *)pEquPlmnIdList
                                                     + 3 + (i * 3)) & 0x0F);      /* MCC digit 3 of PLMN i                    */
        pGmmPlmnId[i].aucMncDigit[0] = (VOS_UINT8)(*((VOS_UINT8 *)pEquPlmnIdList
                                                   + 4 + (i * 3)) & 0x0F);        /* MNC digit 1 of PLMN i                    */
        pGmmPlmnId[i].aucMncDigit[1] = (VOS_UINT8)((*((VOS_UINT8 *)pEquPlmnIdList
                                             + 4 + (i * 3)) >> 4) & 0x0F);        /* MNC digit 2 of PLMN i                    */
        pGmmPlmnId[i].aucMncDigit[2] = (VOS_UINT8)((*((VOS_UINT8 *)pEquPlmnIdList
                                             + 3 + (i * 3)) >> 4) & 0x0F);        /* MNC digit 3 of PLMN i                    */
    }
    for (i=0; i<(*((VOS_UINT8 *)pEquPlmnIdList +1) / 3); i++)
    {                                                                           /* 将PLMN List从临时变量拷到目标地址        */
        ulMccDigit1 = pGmmPlmnId[i].aucMccDigit[1];
        ulMccDigit2 = pGmmPlmnId[i].aucMccDigit[2];
        pPlmnId[i].ulMcc = pGmmPlmnId[i].aucMccDigit[0]                         /* 存储MCC digit 1 of PLMN i                */
                           | (ulMccDigit1 << 8)                                 /* 存储MCC digit 2 of PLMN i                */
                           | (ulMccDigit2 << 16);                               /* 存储MCC digit 3 of PLMN i                */
        ulMncDigit1 = pGmmPlmnId[i].aucMncDigit[1];
        ulMncDigit2 = pGmmPlmnId[i].aucMncDigit[2];
        pPlmnId[i].ulMnc = pGmmPlmnId[i].aucMncDigit[0]                         /* 存储MNC digit 1 of PLMN i                */
                           | (ulMncDigit1 << 8)                                 /* 存储MNC digit 2 of PLMN i                */
                           | (ulMncDigit2 << 16);                               /* 存储MNC digit 3 of PLMN i                */
    }

    Gmm_MemFree(pGmmPlmnId);                                            /* 释放申请的内存空间                       */
    return GMM_TRUE;                                                            /* 返回                                     */
}
/*lint -restore */

/*******************************************************************************
  Module   : Gmm_Com_DealOfMsId
  Function : MS ID的填写
  Input    : VOS_VOID                       *pMsIdentity    MS IDENTITY首地址
             MMC_GMM_MS_IDENTITY_STRU   *pMsId          原语中的MS ID的首地址
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.10  新规作成

*******************************************************************************/
VOS_VOID Gmm_Com_DealOfMsId(
                        VOS_VOID                        *pMsIdentity,               /* MS IDENTITY首地址,如果为空则说明没有此IE */
                        MMC_GMM_MS_IDENTITY_STRU    *pMsId                      /* 原语中的MS ID的首地址                    */
                        )
{
    VOS_UINT8           i;                                                          /* 定义循环控制变量                         */

    if (VOS_NULL_PTR == pMsIdentity)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_Com_DealOfMsId:WARNING: The Entry Pointer is VOS_NULL_PTR");
        return;                                                                 /* 返回                                     */
    }
    if (GMM_IEI_MS_IDENTITY != *(VOS_UINT8 *)pMsIdentity)
    {                                                                           /* IEI错误                                  */
        pMsId->ulIdType = MMC_GMM_MS_ID_TYPE_NULL;                              /* MS ID 类型                               */
    }

    if (GMM_MOBILE_ID_TMSI_PTMSI
        == (*((VOS_UINT8 *)pMsIdentity + 2) & GMM_MOBILE_ID_TMSI_PTMSI))
    {                                                                           /* MS id 是TMSI                             */
        pMsId->ulIdType = MMC_GMM_MS_ID_TYPE_TMSI;                              /* MS ID 类型                               */
        for (i=0; i<4; i++)
        {
            pMsId->aucTmsi[i] = *((VOS_UINT8 *)pMsIdentity + 3 + i);                /* 赋值TMSI                                 */
        }

    }
    else if (GMM_MOBILE_ID_IMSI
             == (*((VOS_UINT8 *)pMsIdentity + 2) & GMM_MOBILE_ID_IMSI))
    {                                                                           /* MS id 是IMSI                             */
        pMsId->ulIdType = MMC_GMM_MS_ID_TYPE_IMSI;                              /* MS ID 类型                               */

    }
    else
    {                                                                           /* MS id 是其他                             */
        pMsId->ulIdType = MMC_GMM_MS_ID_TYPE_NULL;                              /* MS ID 类型                               */
    }

    return;                                                                     /* 返回                                     */
}

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 函 数 名  : NAS_GMM_SndAcpuOmChangePtmsi
 功能描述  : 将PTMSI的值发送给ACPU OM模块
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年08月23日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_SndAcpuOmChangePtmsi(VOS_VOID)
{
    VOS_UINT8                          *pucPtmsi     = VOS_NULL_PTR;
    OM_FTM_REPROT_IND_STRU             *pstFtmRptInd = VOS_NULL_PTR;
    NAS_FTM_PTMSI_RPT_EVENT_STRU        stFtmPtmsiRpt;
    VOS_UINT32                          ulMsgLen;
    VOS_UINT32                          ulContentAddr;

    PS_MEM_SET(&stFtmPtmsiRpt, 0, sizeof(NAS_FTM_PTMSI_RPT_EVENT_STRU));

    /* 如果工程菜单没有打开，则什么都不做 */
    if (VOS_FALSE == NAS_MML_GetFtmCtrlFlag())
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_GMM_SndAcpuOmChangePtmsi:INFO: FTM CTRL OFF.");
        return;
    }

    pucPtmsi = NAS_MML_GetUeIdPtmsi();

    /* 如果当前PTMSI没有发生改变，则什么都不做 */
    if (0 == PS_MEM_CMP(pucPtmsi, NAS_MML_GetSimPsLociFileContent(), NAS_MML_MAX_PTMSI_LEN))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_GMM_SndAcpuOmChangePtmsi:INFO: PTMSI NOT CHANGE.");
        return;
    }

    NAS_COMM_BULID_FTM_HEADER_INFO(&stFtmPtmsiRpt.stHeader,
                                   NAS_MML_MAX_PTMSI_LEN,
                                   VOS_GetModemIDFromPid(WUEPS_PID_GMM),
                                   NAS_FTM_PROJECT_PTMSI_RPT)

    PS_MEM_CPY(stFtmPtmsiRpt.aucPtmsi, pucPtmsi, NAS_MML_MAX_PTMSI_LEN);

    /* 将PTMSI的值发送给ACPU OM模块 */
    /* 申请消息结构内存 */
    /*lint -e961*/
    ulMsgLen     = sizeof(OM_FTM_REPROT_IND_STRU) - VOS_MSG_HEAD_LENGTH - 4 + sizeof(NAS_FTM_PTMSI_RPT_EVENT_STRU);
    /*lint +e961*/

    pstFtmRptInd = (OM_FTM_REPROT_IND_STRU*)PS_ALLOC_MSG(WUEPS_PID_GMM, ulMsgLen);
    if (VOS_NULL_PTR == pstFtmRptInd)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_GMM_SndAcpuOmChangePtmsi:ERROR: Alloc msg fail.");
        return;
    }

    /* 构造消息结构体 */
    pstFtmRptInd->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstFtmRptInd->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstFtmRptInd->ulReceiverPid     = MSP_PID_DIAG_APP_AGENT;
    pstFtmRptInd->ulSenderPid       = WUEPS_PID_GMM;
    pstFtmRptInd->ulMsgName         = ID_OM_FTM_REPROT_IND;
    pstFtmRptInd->ulMsgType         = OM_ERR_LOG_MSG_FTM_REPORT;
    pstFtmRptInd->ulMsgSN           = 0;
    pstFtmRptInd->ulRptlen          = sizeof(NAS_FTM_PTMSI_RPT_EVENT_STRU);

    ulContentAddr                   = (VOS_UINT32)pstFtmRptInd->aucContent;
    PS_MEM_CPY((VOS_UINT8 *)ulContentAddr, &stFtmPtmsiRpt, sizeof(NAS_FTM_PTMSI_RPT_EVENT_STRU));

    /* 发送消息到ACPU OM模块 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_GMM, pstFtmRptInd))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_GMM_SndAcpuOmChangePtmsi:ERROR: SEND MSG FIAL.");
    }

    return;
}
#endif

/*******************************************************************************
  Module   : Gmm_SndAgentUsimUpdateFileReq
  Function : 发送原语AGENT_USIM_UPDATE_FILE_REQ的处理
  Input    : VOS_UINT16 usEfId  希望获取的文件ID
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.张志勇  2003.12.10  新规作成
  2.张志勇  2004.10.25  AGENT接口变更对应
  3.张志勇  2005.03.18  NAS_IT_BUG_008对应
  4.日    期   : 2011年7月27日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整

  5.日    期   : 2011年12月1日
    作    者   : zhoujun /40661
    修改内容   : 比较EFLOCI文件改变后才需要更新卡内容
  6.日    期   : 2012年12月26日
    作    者   : 张鹏 id:00214637
    修改内容   : USIM对外接口函数变更的处理 ，
                 Client ID 到 PID的转换处理 ，入参封装成结构体。
  7.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
  8.日    期   : 2013年6月3日
    作    者   : z00161729
    修改内容   : SVLTE 和usim接口调整修改
  9.日    期   : 2015年2月6日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整
 10.日    期   : 2015年12月10日
    作    者   : z00359541
    修改内容   : DTS2015111208926 IMSI REFRESH时禁止写入EFPSLOCI文件
*******************************************************************************/
VOS_VOID Gmm_SndAgentUsimUpdateFileReq(
                                   VOS_UINT16 usEfId                                /* 希望获取的文件ID                         */
                                   )
{
    VOS_UINT8 *pucPsKey     = VOS_NULL_PTR;                                                 /* 定义指针                                 */
    VOS_UINT8 *pucPsLocInfo = VOS_NULL_PTR;                                                 /* 定义指针                                 */

    NAS_NVIM_PS_LOCI_SIM_FILES_STRU stPsLociSimFiles;

    NAS_MML_RAI_STRU                       *pstLastSuccRai;
    GMM_PLMN_ID_STRU                        stGmmPlmnId;

    NAS_USIMM_UPDATEFILE_INFO_STRU          stSetFileInfo;

    PS_MEM_SET(&stSetFileInfo, 0x00, sizeof(stSetFileInfo));

    pucPsLocInfo = VOS_NULL_PTR;                                                        /* 初始化指针                               */

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmPlmnId);


    switch (usEfId)
    {
    case USIMM_USIM_EFKCGPRS_ID:
    case USIMM_GSM_EFKCGPRS_ID:     /* 2G SIM GPRS Kc Key */
        pucPsKey = (VOS_UINT8 *)Gmm_MemMalloc(9);               /* 申请空间 */
        if (VOS_NULL_PTR == pucPsKey)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndAgentUsimUpdateFileReq:WARNING: Alloc mem fail.");
            return;                                                            /* 返回                                     */
        }

        Gmm_MemSet(pucPsKey, 0, 9);                         /* 将申请的空间清0 */

        pucPsKey[8] = NAS_MML_GetSimPsSecurityCksn();                    /* 填充文件内容 */

        Gmm_MemCpy(&pucPsKey[0],
                   NAS_MML_GetSimPsSecurityGsmKc(), 8);

        NAS_COMM_BUILD_USIM_SET_FILE_INFO(&stSetFileInfo,
                                        USIMM_GUTL_APP,
                                        usEfId,
                                        0,
                                        NAS_MML_PS_KC_SIM_FILE_LEN,
                                        pucPsKey);

        (VOS_VOID)NAS_USIMMAPI_SetFileReq(WUEPS_PID_GMM, 0, &stSetFileInfo);

        Gmm_MemFree(pucPsKey);                                                  /* 释放内存 */

        break;
    case USIMM_USIM_EFKEYSPS_ID:
        pucPsKey = (VOS_UINT8 *)Gmm_MemMalloc(33);                              /* 申请空间                                 */
        if (VOS_NULL_PTR == pucPsKey)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndAgentUsimUpdateFileReq:WARNING: Alloc mem fail.");
            return;                                                             /* 返回                                     */
        }
        Gmm_MemSet(pucPsKey, 0, 33);                                            /* 将申请的空间清0                          */

        pucPsKey[0] = NAS_MML_GetSimPsSecurityCksn();                    /* 填充文件内容                             */

        Gmm_MemCpy(&pucPsKey[1],
                   NAS_MML_GetSimPsSecurityUmtsCk(), 16);
        Gmm_MemCpy(&pucPsKey[17],
                   NAS_MML_GetSimPsSecurityUmtsIk(), 16);

        NAS_COMM_BUILD_USIM_SET_FILE_INFO(&stSetFileInfo,
                                        USIMM_GUTL_APP,
                                        usEfId,
                                        0,
                                        NAS_MML_PS_KEY_USIM_FILE_LEN,
                                        pucPsKey);

        (VOS_VOID)NAS_USIMMAPI_SetFileReq(WUEPS_PID_GMM, 0, &stSetFileInfo);

        Gmm_MemFree(pucPsKey);                                                  /* 释放内存                                 */
        break;
    case USIMM_USIM_EFPSLOCI_ID:                                             /* 更新PS Location information              */
    case USIMM_GSM_EFLOCIGPRS_ID:
        /* IMSI Refresh, 不更新卡文件，直接返回 */
        if (VOS_TRUE == NAS_MML_GetImsiRefreshStatus())
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_PRINT_INFO, "Gmm_SndAgentUsimUpdateFileReq: IMSI Refresh, do not write EFPSLOCI file");
            return;
        }
        
        pucPsLocInfo = (VOS_UINT8 *)Gmm_MemMalloc(14);                              /* 申请空间                                 */
        if (VOS_NULL_PTR == pucPsLocInfo)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndAgentUsimUpdateFileReq:WARNING: Alloc mem fail.");
            return;                                                             /* 返回                                     */
        }
        Gmm_MemSet(pucPsLocInfo, 0, 14);                                        /* 将申请的空间清0                          */

        Gmm_MemCpy(pucPsLocInfo,
                   NAS_MML_GetUeIdPtmsi(),
                   NAS_MML_MAX_PTMSI_LEN);                                         /* P_TMSI赋值                               */
        Gmm_MemCpy(pucPsLocInfo + 4,
                   NAS_MML_GetUeIdPtmsiSignature(),
                   NAS_MML_MAX_PTMSI_SIGNATURE_LEN);                               /* 赋P_TMSI signature                       */


        pucPsLocInfo[7] =
            (VOS_UINT8)(stGmmPlmnId.aucMccDigit[0]
            | (stGmmPlmnId.aucMccDigit[1] << 4));   /* 赋MCC和MNC                               */
        pucPsLocInfo[8] =
            (VOS_UINT8)(stGmmPlmnId.aucMccDigit[2]
            | (stGmmPlmnId.aucMncDigit[2] << 4));   /* 赋MCC和MNC                               */
        pucPsLocInfo[9] =
            (VOS_UINT8)(stGmmPlmnId.aucMncDigit[0]
            | (stGmmPlmnId.aucMncDigit[1] << 4));   /* 赋MCC和MNC                               */
        pucPsLocInfo[10] = pstLastSuccRai->stLai.aucLac[0];          /* 赋LAC                                    */
        pucPsLocInfo[11] = pstLastSuccRai->stLai.aucLac[1];
        pucPsLocInfo[12] = pstLastSuccRai->ucRac;                  /* 赋RAC                                    */
        pucPsLocInfo[13] = NAS_MML_GetPsUpdateStatus();                  /* 赋更新状态                               */


        /*如果写入文件6F73的数据和卡当前所存储的内容不相同，则执行写卡操作*/
        if (0 != PS_MEM_CMP(pucPsLocInfo, NAS_MML_GetSimPsLociFileContent(), NAS_MML_PS_LOCI_SIM_FILE_LEN))
        {
            NAS_COMM_BUILD_USIM_SET_FILE_INFO(&stSetFileInfo,
                                            USIMM_GUTL_APP,
                                            usEfId,
                                            0,
                                            NAS_MML_PS_LOCI_SIM_FILE_LEN,
                                            pucPsLocInfo);

            (VOS_VOID)NAS_USIMMAPI_SetFileReq(WUEPS_PID_GMM, 0, &stSetFileInfo);

            NAS_MML_UpdateSimPsLociFileContent(pucPsLocInfo);

            PS_MEM_CPY(stPsLociSimFiles.aucPsLocInfo, pucPsLocInfo, sizeof(stPsLociSimFiles.aucPsLocInfo));
            if (NV_OK != NV_Write(en_NV_Item_Ps_Loci, &stPsLociSimFiles, sizeof(NAS_NVIM_PS_LOCI_SIM_FILES_STRU)))
            {
                NAS_ERROR_LOG(WUEPS_PID_MMC, "Gmm_SndAgentUsimUpdateFileReq:ERROR: NV_Write Error");
            }

        }




        Gmm_MemFree(pucPsLocInfo);                                              /* 释放内存                                 */
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndAgentUsimUpdateFileReq:WARNING: EF id error");
        break;
    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_SndAgentUsimAuthenticationReq
  Function : 发送原语AGENT_USIM_AUTHENTICATION_REQ的处理
  Input    : VOS_UINT32  ulLength   AUTN的长度
             VOS_VOID   *pAutn     指向参数AUTN的的指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.10  新规作成
    2.日    期  : 2006年11月25日
      作    者  : luojian id:60022475
      修改内容  : 问题单号:A32D06583
    3.日    期  : 2012年12月26日
      作    者  : 张鹏 id:00214637
      修改内容  : USIM对外接口函数变更的处理 ，Client ID 到 PID的转换处理。
    4.日    期  : 2013年6月4日
      作    者  : w00242748
      修改内容  : NAS_SndUsimmAuthReq修改为NAS_USIMMAPI_AuthReq，后者会根据当前模式自动
                  适配
    5.日    期  : 2013年11月30日
      作    者  : l65478
      修改内容  : DTS2013121919477,连续收到网络的两条鉴权消息,网络把第一条消息的响应作为第二条请求的响应,导致鉴权失败

    6.日    期  : 2014年1月3日
      作    者  : s00261364
      修改内容  : mm模块Converity告警消除
*******************************************************************************/
VOS_VOID Gmm_SndAgentUsimAuthenticationReq(
                                       VOS_UINT32    ulLength,                       /* AUTN的长度                               */
                                       VOS_VOID     *pAutn                          /* 指向参数AUTN的的指针                     */
                                       )
{
    VOS_UINT8   ucAuthenType;
    VOS_UINT8   ucTempOpId = 0;


    if (GMM_UMTS_AUTHEN_SUPPORTED == g_GmmAuthenCtrl.ucUmtsAuthFlg)
    {
        ucAuthenType = AUTHENTICATION_REQ_UMTS_CHALLENGE;
    }
    else
    {
        ucAuthenType = AUTHENTICATION_REQ_GSM_CHALLENGE;
    }

    ucTempOpId = g_GmmAuthenCtrl.ucOpId;

    g_GmmAuthenCtrl.ucOpId = (VOS_UINT8)((ucTempOpId) % 255);
    g_GmmAuthenCtrl.ucOpId++;

    /* 调用USIM的API发送函数 */
    NAS_USIMMAPI_AuthReq( WUEPS_PID_GMM,
                   ucAuthenType,
                   (VOS_UINT8 *)g_GmmAuthenCtrl.aucRandSav,
                   (VOS_UINT8 *)pAutn,
                   g_GmmAuthenCtrl.ucOpId);

    g_GmmReqCnfMng.ucCnfMask |= GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;          /* 置等待响应标志                           */

    return;                                                                     /* 返回                                     */
}


/*******************************************************************************
  Module   : Gmm_SndMmcSignalingStatusInd
  Function : 发送原语AGENT_GET_IMEI_REQ的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2004.02.17  新规作成

    2.日    期   : 2011年7月14日
      作    者   : zhoujun 40661
      修改内容   : 更新MML_CTX中的链接存在状态
    3.日    期   : 2015年6月5日
      作    者   : z00161729
      修改内容   : 24008 23122 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID Gmm_SndMmcSignalingStatusInd(
                                  VOS_UINT32  ulSignalingSts                         /* PS域信令连接状态                         */
                                  )
{
    MMCGMM_SIGNALING_STATUS_IND_STRU   *pstMsg          = VOS_NULL_PTR;
    MMCGMM_SIGNALING_STATUS_IND_STRU   *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(MMCGMM_SIGNALING_STATUS_IND_STRU);

    pstInternalMsg  = (MMCGMM_SIGNALING_STATUS_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_SndMmcSignalingStatusInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_SIGNALING_STATUS_IND;
    pstMsg->ulSignalingSts                = ulSignalingSts;                               /* 填写信令连接存在状态                     */                                         /* attach原因                               */


    if (MMC_GMM_SIGNALING_STATUS_ABSENT == ulSignalingSts)
    {
        g_MmSubLyrShare.GmmShare.ucPsSpecificFlg = GMM_SPECIFIC_OFF;
        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);

        NAS_GMM_DeleteRandAndResInfoInPmmIdleMode();
    }
    else
    {
        g_MmSubLyrShare.GmmShare.ucPsSpecificFlg = GMM_SPECIFIC_ON;

        if (VOS_FALSE == GMM_IsCasGsmMode())
        {
            NAS_MML_SetPsSigConnStatusFlg(VOS_TRUE);
        }
    }

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;

}


/*******************************************************************************
  Module   : Gmm_SndSmsRegStateInd
  Function : 发送原语GMMSMS_REG_STATE_IND的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1.  张志勇  2004.03.11  新规作成(二期改造_GMM_001_2)
*******************************************************************************/
VOS_VOID Gmm_SndSmsRegStateInd(VOS_VOID)
{
    GMMSMS_REG_STATE_IND_STRU   *pMsg;                                          /* 定义指针                                 */
    VOS_UINT32                   ulRet;

    pMsg = (GMMSMS_REG_STATE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                                    sizeof(GMMSMS_REG_STATE_IND_STRU));         /* 申请内存                                 */
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SMS;
    pMsg->MsgHeader.ulMsgName   = GMMSMS_REG_STATE_IND;                         /* 原语名称                                 */

    if (GMM_STATUS_DETACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
    {
        pMsg->ulRegSts = GMM_SMS_REG_DETTACHED;                                 /* 填写注册状态                             */                                         /* attach原因                               */
    }
    else
    {
        pMsg->ulRegSts = GMM_SMS_REG_ATTACHED;                                  /* 填写注册状态                             */
    }

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                                   /* 原语发送                                 */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndSmsRegStateInd:WARNING: Send msg fail.");
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_SndSmsEstCnf
  Function : 发送原语PMMSMS_EST_CNF的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1.  张志勇  2004.03.11  新规作成(二期改造_GMM_001_4)
*******************************************************************************/
VOS_VOID Gmm_SndSmsEstCnf(VOS_VOID)
{
    PMMSMS_EST_CNF_STRU   *pMsg;                                                /* 定义指针                                 */
    VOS_UINT32             ulRet;
    pMsg = (PMMSMS_EST_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                                    sizeof(PMMSMS_EST_CNF_STRU));               /* 申请内存                                 */
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SMS;
    pMsg->MsgHeader.ulMsgName   = PMMSMS_EST_CNF;                               /* 原语名称                                 */

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                                   /* 原语发送                                 */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndSmsEstCnf:WARNING: Send msg fail.");
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_SndSmsUnitdataInd
  Function : 发送原语PMMSMS_UNITDATA_IND的处理
  Input    : NAS_MSG_STRU    *pSmMsg     要发送消息的的指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2004.03.11  新规作成(二期改造_GMM_001_6)

*******************************************************************************/
VOS_VOID Gmm_SndSmsUnitdataInd(
                           NAS_MSG_FOR_PCLINT_STRU          *pSmsMsg
                           )
{
    VOS_UINT8                       i;                                              /* 定义循环控制变量                         */
    PMMSMS_UNITDATA_IND_STRU    *pMsg;                                          /* 定义临时变量                             */
    VOS_UINT32                   ulRet;

    if (4 < pSmsMsg->ulNasMsgSize)
    {
        pMsg = (PMMSMS_UNITDATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                (sizeof(PMMSMS_UNITDATA_IND_STRU)+ pSmsMsg->ulNasMsgSize) - 4);   /* 申请内存                                 */

        }
    else
    {
        pMsg = (PMMSMS_UNITDATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                                        sizeof(PMMSMS_UNITDATA_IND_STRU));      /* 申请内存                                 */
    }
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SMS;
    pMsg->MsgHeader.ulMsgName   = PMMSMS_UNITDATA_IND;                          /* 原语名称                                 */

    pMsg->SmsMsg.ulNasMsgSize = pSmsMsg->ulNasMsgSize;                          /* 填写消息长度                             */
    for (i=0; i<pSmsMsg->ulNasMsgSize; i++)
    {
        pMsg->SmsMsg.aucNasMsg[i] = pSmsMsg->aucNasMsg[i];                      /* 填写消息内容                             */
    }

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                                   /* 原语发送                                 */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndSmsUnitdataInd:WARNING: Send msg fail.");
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_SndSmsErrorInd
  Function : 发送原语PMMSMS_ERROR_IND的处理
  Input    : VOS_UINT8  ucCause         释放原因
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1.  张志勇  2004.03.11  新规作成(二期改造_GMM_001_7)
*******************************************************************************/
VOS_VOID Gmm_SndSmsErrorInd(
                        VOS_UINT8  ucCause                                          /* 释放原因                                 */
                        )
{
    PMMSMS_ERROR_IND_STRU   *pMsg;                                              /* 定义指针                                 */
    VOS_UINT32               ulRet;
    pMsg = (PMMSMS_ERROR_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                                    sizeof(PMMSMS_ERROR_IND_STRU));             /* 申请内存                                 */
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SMS;
    pMsg->MsgHeader.ulMsgName   = PMMSMS_ERROR_IND;                             /* 原语名称                                 */

    pMsg->ulCause = ucCause;                                                    /* 填写原因                                 */

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                                   /* 原语发送                                 */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndSmsErrorInd:WARNING: Send msg fail.");
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_SndSmsServiceStatusInd
  Function : 发送原语GMMSMS_SERVICE_STATUS_IND的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1.  x00115505  2009.06.30    Created
*******************************************************************************/
VOS_VOID Gmm_SndSmsServiceStatusInd(VOS_VOID)
{
    GMMSMS_SERVICE_STATUS_IND_STRU   *pMsg;                                     /* 定义指针                                 */
    VOS_UINT32                        ulRet;
    VOS_UINT32                        ulTempServiceStatus = GMM_SMS_NO_SERVICE;
    static VOS_UINT32                 ulServiceStatus     = GMM_SMS_NO_SERVICE;

    ulTempServiceStatus = Gmm_GetServiceStatusForSms();

    if (ulServiceStatus != ulTempServiceStatus)
    {                                                                           /* 服务状态变化了才上报给短信模块           */
        pMsg = (GMMSMS_SERVICE_STATUS_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                                        sizeof(GMMSMS_SERVICE_STATUS_IND_STRU));/* 申请内存                                 */
        if (VOS_NULL_PTR == pMsg)
        {
            return;
        }

        pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
        pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SMS;
        pMsg->MsgHeader.ulMsgName       = GMMSMS_SERVICE_STATUS_IND;            /* 原语名称                                 */

        ulServiceStatus    = ulTempServiceStatus;
        pMsg->enServiceSts = ulServiceStatus;

        ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                               /* 原语发送                                 */

        if (VOS_OK != ulRet)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndSmsServiceStatusInd:WARNING: Send msg fail.");
        }
    }

    return;
}
/*******************************************************************************
  Module   : Gmm_SndTcDataInd
  Function : 发送原语TCGMM_DATA_IND原语的处理
  Input    : NAS_MSG_STRU *pTcMsg  要发送消息的的指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2004.06.18  新规作成(TC对应)
    2. 张志勇  2004.08.20  GMM_CHK_二期_BUG_077
*******************************************************************************/
VOS_VOID Gmm_SndTcDataInd(
                      NAS_MSG_FOR_PCLINT_STRU          *pTcMsg
                      )
{
    VOS_UINT8                 i;                                                    /* 定义循环控制变量                           */
    TCGMM_DATA_IND_STRU   *pMsg;                                                /* 定义临时变量                             */
    VOS_UINT32             ulRet;

    if (4 < pTcMsg->ulNasMsgSize)
    {
        pMsg = (TCGMM_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
            (sizeof(TCGMM_DATA_IND_STRU) + pTcMsg->ulNasMsgSize) - 4);            /* 申请内存                                 */
    }
    else
    {
        pMsg = (TCGMM_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
            sizeof(TCGMM_DATA_IND_STRU));                                       /* 申请内存                                 */
    }
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_TC;
    pMsg->MsgHeader.ulMsgName   = TCGMM_DATA_IND;                               /* 原语名称                                 */

    pMsg->RcvTcMsg.ulTcMsgSize = pTcMsg->ulNasMsgSize;                          /* 填写消息长度                             */
    for (i=0; i<pTcMsg->ulNasMsgSize; i++)
    {
        pMsg->RcvTcMsg.aucTcMsg[i] = pTcMsg->aucNasMsg[i];                      /* 填写消息内容                             */
    }

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                                   /* 原语发送                                 */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndTcDataInd:WARNING: Send msg fail.");
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_SndRrmmDataReqForCm
  Function : 发送RRMM_DATA_REQ原语处理（发送CM层消息专用）
  Input    : VOS_UINT8          ucPriorityInd      消息优先级指示
             NAS_MSG_STRU   *Msg               该CN Domain的NAS消息首地址
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2004.07.06  新规作成（GMM_CHK_二期_BUG_070）
*******************************************************************************/
VOS_VOID Gmm_SndRrmmDataReqForCm(
                             VOS_UINT8               ucPriorityInd,                 /* 消息优先级指示                           */
                             NAS_MSG_STRU        *pMsg                          /* 该CN Domain的NAS消息首地址               */
                            )
{
    VOS_INT32 lRet;
    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        GMM_SndRrmmDataReqGsm(pMsg);
        return;
    }
    lRet = g_GmmImportFunc.RrmmDataReqFunc(RRC_NAS_PS_DOMAIN,
                                    ucPriorityInd,
                                    pMsg->ulNasMsgSize,
                                    (VOS_INT8 *)pMsg->aucNasMsg);                   /* 调用发送函数                             */

    if (AS_SUCCESS != lRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndRrmmDataReqForCm:WARNING: Send msg fail.");
    }
    return;                                                                     /* 返回                                     */
}
/*******************************************************************************
  Module:   Gmm_SndCcEmergencyNumberList
  Function: 向CC发送MMCC_ERR_IND的处理
  Input:    VOS_UINT32 ulTransactionId
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
        1.  x00115505     2009.05.11  新版做成
        2.日    期   : 2012年3月27日
          作    者   : w00166186
          修改内容   : CSFB&PPAC&ETWS&ISR 开发 ENERGENCY CALL
*******************************************************************************/
VOS_VOID Gmm_SndCcEmergencyNumberList(NAS_MML_EMERGENCY_NUM_LIST_STRU *pEmergencyList)
{
    GMMCC_EMERGENCY_LIST_STRU            *pEmcNumLst;                           /* 定义原语类型指针                         */
    VOS_UINT32                           ulRst;

    if (VOS_NULL_PTR == pEmergencyList)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_SndCcEmergencyNumberList:ERROR:Receive Null Pointer!");
        return;                                                                 /* 返回                                     */
    }

    pEmcNumLst = (GMMCC_EMERGENCY_LIST_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                                 sizeof(GMMCC_EMERGENCY_LIST_STRU));            /* 申请内存                                 */

    if (VOS_NULL_PTR == pEmcNumLst)
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_SndCcEmergencyNumberList:ERROR:MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }

    pEmcNumLst->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pEmcNumLst->MsgHeader.ulReceiverPid   = WUEPS_PID_CC;
    pEmcNumLst->MsgHeader.ulMsgName       = GMMCC_EMC_NUM_LST_IND;               /* 消息名称                                 */

    pEmcNumLst->ulMcc                     = pEmergencyList->ulMcc;

    pEmcNumLst->ucEmergencyNumber = pEmergencyList->ucEmergencyNumber;

    PS_MEM_CPY(pEmcNumLst->astEmergencyLists, pEmergencyList->aucEmergencyList,
                ((pEmergencyList->ucEmergencyNumber) * sizeof(GMMCC_EMERGENCY_CONTENT_STRU)));

    if (0 == pEmergencyList->ucEmergencyNumber)
    {
        pEmcNumLst->ulMcc = 0XFFFFFFFF;
        PS_MEM_SET((VOS_VOID*)pEmcNumLst->astEmergencyLists,
                    0xFF,
                    GMMCC_EMERGENCY_NUMBER_LISTS_MAX_NUMBER * sizeof(NAS_MML_EMERGENCY_NUM_STRU));
    }

    ulRst = PS_SEND_MSG(WUEPS_PID_GMM, pEmcNumLst);

    if (VOS_OK != ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_SndCcEmergencyNumberList:ERROR:Send Message ERROR!");
        return;
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_SndMmcGprsServiceInd
  Function : 发送原语MMCGMM_GPRS_SERVICE_IND的处理
  Input    : enGprsServiceType - GMM指示给MMC的服务类型
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1.  s46746  2009.07.21    Created
    2.日    期   : 2012年8月15日
      作    者   : z00161729
      修改内容   : DCM定制需求和遗留问题修改,增加入参
*******************************************************************************/
VOS_VOID Gmm_SndMmcGprsServiceInd(
    NAS_MMC_GMM_GPRS_SERVICE_TYPE_ENUM_UINT32               enGprsServiceType
)
{
    MMCGMM_GPRS_SERVICE_IND_STRU       *pstMsg          = VOS_NULL_PTR;
    MMCGMM_GPRS_SERVICE_IND_STRU       *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(MMCGMM_GPRS_SERVICE_IND_STRU);

    pstInternalMsg  = (MMCGMM_GPRS_SERVICE_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_SndMmcGprsServiceInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_GPRS_SERVICE_IND;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, begin */
    pstMsg->enGprsServiceType             = enGprsServiceType;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, end */

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_SndRrmmInterRatHandoverInfoReq
 功能描述  : 发送RRMM_INTER_RAT_HANDOVER_INFO_REQ消息，获得Inter Rat Handover Info信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32: VOS_OK/VOS_ERR - 函数执行是否成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月16日
    作    者   : o00132663
    修改内容   : 新生成函数
  2.日    期   : 2012年7月14日
    作    者   : W00176964
    修改内容   : V7R1 C50 GUTL PhaseI调整:发送给WRR的消息统一用适配层函数替换
  3.日    期   : 2014年7月9日
    作    者   : w00242748
    修改内容   : DSDS III新特性
*****************************************************************************/
VOS_UINT32  NAS_GMM_SndRrmmInterRatHandoverInfoReq( VOS_VOID )
{
    VOS_UINT32                              ulRet;
    RRMM_INTER_RAT_HANDOVER_INFO_REQ_STRU   *pSndMsg;

    pSndMsg = (RRMM_INTER_RAT_HANDOVER_INFO_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_GMM,
                    sizeof(RRMM_INTER_RAT_HANDOVER_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pSndMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_SndRrmmInterRatHandoverInfoReq():Error: Failed in VOS_AllocMsg()");
        return VOS_ERR;
    }

    /* NAS消息公共消息部分填写 */
    pSndMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_WRR;
    pSndMsg->MsgHeader.ulMsgName        = RRMM_INTER_RAT_HANDOVER_INFO_REQ;

    PS_MEM_SET(pSndMsg->aucReserve1, 0x00, sizeof(pSndMsg->aucReserve1));

    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_GMM, (struct MsgCB **)&pSndMsg);

    if (VOS_OK != ulRet)
    {
        /* 打印错误信息 */
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_SndRrmmInterRatHandoverInfoReq():Error: Failed in PS_SEND_MSG()");
        return VOS_ERR;
    }

    Gmm_TimerStart(GMM_TIMER_INTERRAT_HANDOVER_INFO_CNF);

    return VOS_OK;
}

#if   (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 函 数 名  : NAS_GMM_SndTinTypeToMmc
 功能描述  : 通知GMM当前TIN的类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月21日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_GMM_SndTinTypeToMmc(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType
)
{
    MMCGMM_TIN_TYPE_IND_STRU           *pstMsg          = VOS_NULL_PTR;
    MMCGMM_TIN_TYPE_IND_STRU           *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(MMCGMM_TIN_TYPE_IND_STRU);

    pstInternalMsg  = (MMCGMM_TIN_TYPE_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndTinTypeToMmc,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_TIN_TYPE_IND;
    pstMsg->enTinType                     = enTinType;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}

#endif


/*****************************************************************************
 函 数 名  : NAS_GMM_SndMmLuInitiation
 功能描述  : GMMMM_LU_INITIATION原语填写及发送
 输入参数  : ulT3312outFlg     T3312是否溢出标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月1日
   作    者   : h44270
   修改内容   : 新生成函数，V7R1 PhaseII阶段调整

*****************************************************************************/
VOS_VOID NAS_GMM_SndMmLuInitiation(
    VOS_UINT32                          ulT3312TimeoutFlg
)
{
    GMMMM_LU_INITIATION_STRU           *pstMsg          = VOS_NULL_PTR;
    GMMMM_LU_INITIATION_STRU           *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(GMMMM_LU_INITIATION_STRU);

    pstInternalMsg  = (GMMMM_LU_INITIATION_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmLuInitiation,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength          = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = GMMMM_LU_INITIATION;
    pstMsg->enTimerExpiredFlg             = ulT3312TimeoutFlg;
    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;

}

/*******************************************************************************
 函 数 名  : NAS_GMM_SndMmCombinedAttachInitiation
 功能描述  : 发送原语GMMMM_COMBINED_ATTACH_INITIATION的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月1日
   作    者   : h44270
   修改内容   : 新生成函数

*******************************************************************************/
VOS_VOID NAS_GMM_SndMmCombinedAttachInitiation(VOS_VOID)
{
    GMMMM_COMBINED_ATTACH_INITIATION_STRU  *pstMsg          = VOS_NULL_PTR;
    GMMMM_COMBINED_ATTACH_INITIATION_STRU  *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                              ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(GMMMM_COMBINED_ATTACH_INITIATION_STRU);

    pstInternalMsg  = (GMMMM_COMBINED_ATTACH_INITIATION_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmCombinedAttachInitiation,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                            = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid                   = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid                 = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength                      = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName                     = GMMMM_COMBINED_ATTACH_INITIATION;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;

}

/*******************************************************************************
 函 数 名  : NAS_GMM_SndMmCombinedAttachAccept
 功能描述  : 发送原语GMMMM_COMBINED_ATTACH_ACCEPTED的处理
 输入参数  : ulAttachResult   注册结果
              ulCause          失败原因值
              pNasMsg          NAS消息首地址
              pMsIdentity      IE是否存在的信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月1日
   作    者   : h44270
   修改内容   : 新生成函数
 2.日    期   : 2015年6月9日
   作    者   : z00161729
   修改内容   : 24008 23122 R11 CR升级项目修改

*******************************************************************************/
VOS_VOID NAS_GMM_SndMmCombinedAttachAccept(
    VOS_UINT32                          ulAttachResult,                         /* 注册结果                                 */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause,                                /* 失败原因值                               */
    NAS_MSG_FOR_PCLINT_STRU            *pNasMsg,                                /* NAS消息首地址                            */
    GMM_MSG_RESOLVE_STRU               *pAttachAcceptIe    /* IE是否存在的信息                         */
)
{
    GMMMM_COMBINED_ATTACH_ACCEPTED_STRU    *pstMsg          = VOS_NULL_PTR;
    GMMMM_COMBINED_ATTACH_ACCEPTED_STRU    *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                              ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(GMMMM_COMBINED_ATTACH_ACCEPTED_STRU);

    pstInternalMsg  = (GMMMM_COMBINED_ATTACH_ACCEPTED_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmCombinedAttachAccept,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength          = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = GMMMM_COMBINED_ATTACH_ACCEPTED;
    pstMsg->enCause                       = enCause;
    pstMsg->enAttachResult                = ulAttachResult;

    if (GMM_ATTACH_ACCEPT_IE_MS_IDENTITY_FLG
        == (pAttachAcceptIe->ulOptionalIeMask
        & GMM_ATTACH_ACCEPT_IE_MS_IDENTITY_FLG))
    {                                                                           /* 该IE存在                                 */
        Gmm_Com_DealOfMsId(&pNasMsg->aucNasMsg[pAttachAcceptIe->
                          aucIeOffset[GMM_ATTACH_ACCEPT_IE_MS_IDENTITY]],
                          (MMC_GMM_MS_IDENTITY_STRU*)&(pstMsg->stMsIdentity));                             /* 填写MS ID                                */
    }

    pstMsg->ulAttachAttCounter = g_GmmAttachCtrl.ucAttachAttmptCnt;

    if (GMMMM_ATTACH_RESLUT_PS_ONLY == ulAttachResult)
    {
        pstMsg->ulAttachAttCounter = g_GmmRauCtrl.ucRauAttmptCnt;
    }

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}

/*******************************************************************************
 函 数 名  : NAS_GMM_SndMmCombinedAttachRejected
 功能描述  : 发送原语GMMMM_COMBINED_ATTACH_ACCEPTED的处理
 输入参数  : ulCause     失败原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月1日
  作    者   : h44270
  修改内容   : 新生成函数
 2.日    期   : 2011年11月15日
  作    者   : w00166186
  修改内容   : DTS201111402055,网络模式I下被17号原因值拒绝5次后，MM不停的发起注册
*******************************************************************************/
VOS_VOID NAS_GMM_SndMmCombinedAttachRejected(
    VOS_UINT32                          ulCause                                          /* 失败原因值                               */
)
{
    GMMMM_COMBINED_ATTACH_REJECTED_STRU    *pstMsg          = VOS_NULL_PTR;
    GMMMM_COMBINED_ATTACH_REJECTED_STRU    *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                              ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(GMMMM_COMBINED_ATTACH_REJECTED_STRU);

    pstInternalMsg  = (GMMMM_COMBINED_ATTACH_REJECTED_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmCombinedAttachRejected,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength          = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = GMMMM_COMBINED_ATTACH_REJECTED;
    pstMsg->enCause                       = (VOS_UINT16)ulCause;
    pstMsg->ulAttachAttCounter            = g_GmmAttachCtrl.ucAttachAttmptCnt;

    if (( GMM_UNREAL_PROCEDURE == g_GmmGlobalCtrl.ucRealProFlg )
     && ( NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES != ulCause ))
    {
        pstMsg->enCause = NAS_MML_REG_FAIL_CAUSE_NULL;
    }
    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}


/*******************************************************************************
 函 数 名  : NAS_GMM_SndMmImsiDetachInitiation
 功能描述  : GMMMM_IMSI_DETACH_INITIATION原语填写及发送
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月1日
   作    者   : h44270
   修改内容   : 新生成函数

*******************************************************************************/
VOS_VOID NAS_GMM_SndMmImsiDetachInitiation(VOS_VOID)
{
    GMMMM_IMSI_DETACH_INITIATION_STRU  *pstMsg          = VOS_NULL_PTR;
    GMMMM_IMSI_DETACH_INITIATION_STRU  *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(GMMMM_IMSI_DETACH_INITIATION_STRU);

    pstInternalMsg  = (GMMMM_IMSI_DETACH_INITIATION_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmImsiDetachInitiation,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength          = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = GMMMM_IMSI_DETACH_INITIATION;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

}

/*******************************************************************************
 函 数 名  : NAS_GMM_SndMmImsiDetachComplete
 功能描述  : GMMMM_IMSI_DETACH_COMPLETED原语填写及发送
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月1日
    作    者   : h44270
    修改内容   : 新生成函数

*******************************************************************************/
VOS_VOID NAS_GMM_SndMmImsiDetachComplete(VOS_VOID)
{
    GMMMM_IMSI_DETACH_COMPLETED_STRU   *pstMsg          = VOS_NULL_PTR;
    GMMMM_IMSI_DETACH_COMPLETED_STRU   *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(GMMMM_IMSI_DETACH_COMPLETED_STRU);

    pstInternalMsg  = (GMMMM_IMSI_DETACH_COMPLETED_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmImsiDetachComplete,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength          = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = GMMMM_IMSI_DETACH_COMPLETED;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;

}

/*******************************************************************************
 函 数 名  : NAS_GMM_SndMmGprsDetachInitiation
 功能描述  : GMMMM_GPRS_DETACH_INITIATION原语填写及发送
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月1日
   作    者   : h44270
   修改内容   : 新生成函数

*******************************************************************************/
VOS_VOID NAS_GMM_SndMmGprsDetachInitiation(VOS_VOID)
{
    GMMMM_GPRS_DETACH_INITIATION_STRU  *pstMsg          = VOS_NULL_PTR;
    GMMMM_GPRS_DETACH_INITIATION_STRU  *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(GMMMM_GPRS_DETACH_INITIATION_STRU);

    pstInternalMsg  = (GMMMM_GPRS_DETACH_INITIATION_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmGprsDetachInitiation,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength          = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = GMMMM_GPRS_DETACH_INITIATION;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

}


/*******************************************************************************
 函 数 名  : NAS_GMM_SndMmGprsDetachComplete
 功能描述  : 向MM发送GPRS DETACH完成消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月1日
   作    者   : h44270
   修改内容   : 新生成函数
*******************************************************************************/
VOS_VOID NAS_GMM_SndMmGprsDetachComplete(VOS_VOID)
{
    GMMMM_GPRS_DETACH_COMPLETED_STRU   *pstMsg          = VOS_NULL_PTR;
    GMMMM_GPRS_DETACH_COMPLETED_STRU   *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(GMMMM_GPRS_DETACH_COMPLETED_STRU);

    pstInternalMsg  = (GMMMM_GPRS_DETACH_COMPLETED_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmGprsDetachComplete,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength          = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = GMMMM_GPRS_DETACH_COMPLETED;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

}



/*******************************************************************************
 函 数 名  : NAS_GMM_SndMmNetworkDetachInd
 功能描述  : GMMMM_NETWORK_DETACH_IND原语填写及发送
 输入参数  : ucDetachType           detach类型
              ucDetachCause          detach原因
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月1日
   作    者   : h44270
   修改内容   : 新生成函数
*******************************************************************************/
VOS_VOID NAS_GMM_SndMmNetworkDetachInd(
    VOS_UINT8                           ucDetachType,                           /* detach类型                               */
    VOS_UINT8                           ucDetachCause                           /* detach原因                               */
)
{
    GMMMM_NETWORK_DETACH_IND_STRU      *pstMsg          = VOS_NULL_PTR;
    GMMMM_NETWORK_DETACH_IND_STRU      *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(GMMMM_NETWORK_DETACH_IND_STRU);

    pstInternalMsg  = (GMMMM_NETWORK_DETACH_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmNetworkDetachInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength          = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = GMMMM_NETWORK_DETACH_IND;
    pstMsg->enDetachType                  = ucDetachType;                         /* 填写detach类型                           */
    pstMsg->ulDetachCause                 = ucDetachCause;                        /* 填写detach原因                           */

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;

}

/*******************************************************************************
 函 数 名  : NAS_GMM_SndMmGmmActionResultInd
 功能描述  : GMMMM_GMM_ACTION_RESULT_IND原语填写及发送
 输入参数  : ulActionResult           操作结果
              ulCause                  操作失败原因
              pMsg                     等效的PLMN列表
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月1日
   作    者   : h44270
   修改内容   : 新生成函数
*******************************************************************************/
VOS_VOID NAS_GMM_SndMmGmmActionResultInd(
    VOS_UINT32                          ulActionResult,                     /* 操作结果                                 */
    VOS_UINT32                          ulCause                             /* 操作失败原因                             */
)
{
    GMMMM_GMM_ACTION_RESULT_IND_STRU   *pstMsg          = VOS_NULL_PTR;
    GMMMM_GMM_ACTION_RESULT_IND_STRU   *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(GMMMM_GMM_ACTION_RESULT_IND_STRU);
    pstInternalMsg  = (GMMMM_GMM_ACTION_RESULT_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmGmmActionResultInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength          = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = GMMMM_GMM_ACTION_RESULT_IND;

    if(GMM_EVENT_CAUSE_INVALID != g_GmmGlobalCtrl.ucEventCause)
    {
        ulCause = g_GmmGlobalCtrl.ucEventCause;
    }

    pstMsg->ucAttCounter    = 0;

    switch (g_GmmGlobalCtrl.ucSpecProc & 0xF0)
    {                                                                           /* 判断当前specific过程                     */
        case 0x10:                                                                  /* 当前是attch流程                          */
            pstMsg->enGmmActionType = GMMMM_ACTION_ATTACH;                            /* action 类型                              */
            pstMsg->ucAttCounter    = g_GmmAttachCtrl.ucAttachAttmptCnt;
            break;
        case 0x20:                                                                  /* 当前是RAU流程                            */
            pstMsg->enGmmActionType = GMMMM_ACTION_RAU;                               /* action 类型                              */
            pstMsg->ucAttCounter    = g_GmmRauCtrl.ucRauAttmptCnt;
            break;
        case 0x40:                                                                  /* 当前是sevice request流程                 */
            pstMsg->enGmmActionType = GMMMM_ACTION_SR;                     /* action 类型                              */
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndMmcGmmActionResultInd:WARNING: Current procedure error");
            return;
    }

    pstMsg->enActionResult  = ulActionResult;
    pstMsg->enCause         = (VOS_UINT16)ulCause;                                /* action原因                               */

    if(GMM_UNREAL_PROCEDURE == g_GmmGlobalCtrl.ucRealProFlg)
    {
        pstMsg->enCause      = NAS_MML_REG_FAIL_CAUSE_NULL;
    }

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}

/*******************************************************************************
 函 数 名  : NAS_GMM_SndMmCombinedRauInitiation
 功能描述  : GMMMM_COMBINED_RAU_INITIATION原语填写及发送
 输入参数  : ulActionResult           操作结果
              ulCause                  操作失败原因
              pMsg                     等效的PLMN列表
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月1日
   作    者   : h44270
   修改内容   : 新生成函数
*******************************************************************************/
VOS_VOID NAS_GMM_SndMmCombinedRauInitiation(VOS_VOID)
{
    GMMMM_COMBINED_RAU_INITIATION_STRU *pstMsg          = VOS_NULL_PTR;
    GMMMM_COMBINED_RAU_INITIATION_STRU *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(GMMMM_COMBINED_RAU_INITIATION_STRU);

    pstInternalMsg  = (GMMMM_COMBINED_RAU_INITIATION_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmCombinedRauInitiation,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength          = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = GMMMM_COMBINED_RAU_INITIATION;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;

}

/*******************************************************************************
 函 数 名  : NAS_GMM_SndMmCombinedRauAccept
 功能描述  : GMMMM_COMBINED_RAU_ACCEPTED原语填写及发送
 输入参数  : ulRauResult     更新结果
              ulCause         更新失败原因
              pNasMsg        NAS消息地址
              pRauAcceptIe   IE是否存在的信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月1日
   作    者   : h44270
   修改内容   : 新生成函数
 2.日    期   : 2015年6月9日
   作    者   : z00161729
   修改内容   : 24008 23122 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID NAS_GMM_SndMmCombinedRauAccept(
    VOS_UINT32                          ulRauResult,                            /* 更新结果                                 */
    VOS_UINT32                          ulCause,                                /* 更新失败原因                             */
    NAS_MSG_FOR_PCLINT_STRU            *pstNasMsg,
    GMM_MSG_RESOLVE_STRU               *pstRauAcceptIe                            /* IE是否存在的信息                         */
)
{
    GMMMM_COMBINED_RAU_ACCEPTED_STRU   *pstMsg          = VOS_NULL_PTR;
    GMMMM_COMBINED_RAU_ACCEPTED_STRU   *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(GMMMM_COMBINED_RAU_ACCEPTED_STRU);

    pstInternalMsg  = (GMMMM_COMBINED_RAU_ACCEPTED_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmCombinedRauAccept,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength          = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = GMMMM_COMBINED_RAU_ACCEPTED;
    pstMsg->enRauResult                   = ulRauResult;                          /* 填写更新结果                             */
    pstMsg->enCause                       = (VOS_UINT16)ulCause;                  /* 填写更新失败原因                         */

    pstMsg->stMsIdentity.enMsIdType       = 0;

    if ((GMM_REAL_PROCEDURE == g_GmmGlobalCtrl.ucRealProFlg)
     && (VOS_NULL_PTR != pstRauAcceptIe))
    {                                                                           /* 当前为真流程                             */
        if (GMM_RAU_ACCEPT_IE_MS_IDENTITY_FLG
            == (pstRauAcceptIe->ulOptionalIeMask
            & GMM_RAU_ACCEPT_IE_MS_IDENTITY_FLG))
        {                                                                       /* 该IE存在                                 */
            Gmm_Com_DealOfMsId(&pstNasMsg->aucNasMsg[pstRauAcceptIe->aucIeOffset
                               [GMM_RAU_ACCEPT_IE_MS_IDENTITY]],
                               (MMC_GMM_MS_IDENTITY_STRU*)&(pstMsg->stMsIdentity));                          /* 填写MS ID                                */
        }
    }

    pstMsg->ulRauAttCounter = g_GmmRauCtrl.ucRauAttmptCnt;                        /* 填写RAU attempt counter值                */

    pstMsg->enRealProFlg    = g_GmmGlobalCtrl.ucRealProFlg;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

}

/*******************************************************************************
 函 数 名  : NAS_GMM_SndMmCombinedRauRejected
 功能描述  : GMMMM_COMBINED_RAU_REJECTED原语填写及发送
 输入参数  : ulCause         更新失败原因
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月1日
   作    者   : h44270
   修改内容   : 新生成函数

*******************************************************************************/
VOS_VOID NAS_GMM_SndMmCombinedRauRejected(
    VOS_UINT32                          ulCause
)
{
    GMMMM_COMBINED_RAU_REJECTED_STRU   *pstMsg          = VOS_NULL_PTR;
    GMMMM_COMBINED_RAU_REJECTED_STRU   *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(GMMMM_COMBINED_RAU_REJECTED_STRU);
    pstInternalMsg  = (GMMMM_COMBINED_RAU_REJECTED_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmCombinedRauRejected,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                  = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid       = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName           = GMMMM_COMBINED_RAU_REJECTED;

    pstMsg->enCause                         = (VOS_UINT16)ulCause;                  /* 填写更新失败原因                         */
    pstMsg->ulRauAttCounter                 = g_GmmRauCtrl.ucRauAttmptCnt;          /* 填写RAU attempt counter值                */
    pstMsg->enRealProFlg                    = g_GmmGlobalCtrl.ucRealProFlg;         /* 填写真假流程                             */

    if ((GMM_UNREAL_PROCEDURE == g_GmmGlobalCtrl.ucRealProFlg)
     && ( NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES != ulCause ))
    {
        pstMsg->enCause  = NAS_MML_REG_FAIL_CAUSE_NULL;                                          /* 填写更新失败原因                         */
    }

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

}

/*******************************************************************************
 函 数 名  : NAS_GMM_SndMmAuthenticationFailureInd
 功能描述  : GMMMM_AUTHENTICATON_FAILURE_IND原语填写及发送
 输入参数  : ulCause         更新失败原因
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月1日
   作    者   : h44270
   修改内容   : 新生成函数

*******************************************************************************/
VOS_VOID NAS_GMM_SndMmAuthenticationFailureInd(VOS_VOID)
{
    GMMMM_AUTHENTICATON_FAILURE_IND_STRU   *pstMsg          = VOS_NULL_PTR;
    GMMMM_AUTHENTICATON_FAILURE_IND_STRU   *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                              ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(GMMMM_AUTHENTICATON_FAILURE_IND_STRU);

    pstInternalMsg  = (GMMMM_AUTHENTICATON_FAILURE_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmAuthenticationFailureInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength          = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = GMMMM_AUTHENTICATON_FAILURE_IND;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;

}

/*******************************************************************************
 函 数 名  : NAS_GMM_IsCausePsOnlySucc_CombineReg
 功能描述  : 是否是联合注册过程(Attach/Rau)中，只有PsOnly成功所携带的Cause值:#2,#16,#17,#22
 输入参数  : ulCause 失败原因值
 输出参数  : 无
 返 回 值  : VOS_TRUE:在联合注册被拒原因值中，VOS_FALSE:不在联合注册被拒原因值列表中
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月30日
   作    者   : l00130025
   修改内容   : DTS2012032307791,发给LMM注册结果,CombineReg时需要区分结果域
*******************************************************************************/
VOS_UINT32 NAS_GMM_IsCausePsOnlySucc_CombineReg(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
)
{
    if ( (NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE       == enCause)
       || (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE      == enCause)
       || (NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION == enCause)
       || (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR  == enCause))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*******************************************************************************
 函 数 名  : NAS_GMM_GetRegRsltDomain
 功能描述  : 获取本次注册过程的结果域,:
             1)若本次注册过程为PS_Only则结果也为PS Only
             2)若本次注册过程为Combined，
                若注册失败，则结果域为CS_PS
                若注册成功，则判断当前的Cause值，为2,16,17,22时，结果填写为PS Only
                              当前的Cause值为NULL时，则填写为CS_PS
 输入参数  : enActionType 发起的动作类型，
             enActionResult 本次注册的结果
             ulCause 失败原因值
 输出参数  : 无
 返 回 值  : GMM_MMC_REG_DOMAIN_ENUM_UINT32,本次是PS或CS_PS
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月30日
   作    者   : l00130025
   修改内容   : DTS2012032307791,发给LMM注册结果,CombineReg时需要区分结果域

*******************************************************************************/
GMM_MMC_REG_DOMAIN_ENUM_UINT32 NAS_GMM_GetRegRsltDomain(
    GMM_MMC_ACTION_TYPE_ENUM_U32        enActionType,
    GMM_MMC_ACTION_RESULT_ENUM_U32      enActionResult,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause

)
{
    GMM_MMC_REG_DOMAIN_ENUM_UINT32  enRlstDomain;

    if ((GMM_MMC_ACTION_COMBINED_RAU == enActionType)
      || (GMM_MMC_ACTION_COMBINED_ATTACH == enActionType))
    {

        if (GMM_MMC_ACTION_RESULT_SUCCESS == enActionResult)
        {
            if (VOS_TRUE == NAS_GMM_IsCausePsOnlySucc_CombineReg(enCause))
            {
                enRlstDomain = GMM_MMC_REG_DOMAIN_PS;
            }
            else
            {
                enRlstDomain = GMM_MMC_REG_DOMAIN_PS_CS;
            }
        }
        else
        {
            enRlstDomain = GMM_MMC_REG_DOMAIN_PS_CS;
        }
    }
    else
    {
        enRlstDomain = GMM_MMC_REG_DOMAIN_PS;
    }

    return enRlstDomain;

}

/*****************************************************************************
 函 数 名  : NAS_GMM_SndMmcPsRegResultInd
 功能描述  : GMM 向MMC发送PS注册结果
 输入参数  : GMM_MMC_ACTION_TYPE_ENUM_U32        enActionRst  注册类型
             VOS_UINT32                          ulRegResult  注册结果
             VOS_UINT32                          ulCause      原因值
             VOS_VOID                            pEPlmnList   等效PLMN列表
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月25日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数
  2.日    期   : 2011年10月8日
    作    者   : s46746
    修改内容   : V7R1 phase II,将EPLMN、RPLMN移到MM/GMM维护

  3.日    期   : 2012年1月4日
    作    者   : w00167002
    修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网.
                  MMC不需要知道当前是真假流程，将MM/GMM给MMC的真假流程去掉。
                  MM/GMM自己维护的真假流程也是不需要的，待MM/GMM重构时清理掉。
  4.日    期   : 2012年3月2日
    作    者   : W00176964
    修改内容   : DTS2012022407450:成功时候区分真假流程对应不同原因值
  5.日    期   : 2012年3月30日
    作    者   : l00130025
    修改内容   : DTS2012032307791,发给LMM注册结果,CombineReg时需要区分结果域

  6.日    期   : 2013年3月30日
    作    者   : w00176964
    修改内容   : DTS2013030802929,周期性RAU需要通知LMM
  7.日    期   : 2014年12月19日
    作    者   : s00217060
    修改内容   : Service_State_Optimize_PhaseI 假流程succ增加原因值NAS_MML_REG_FAIL_CAUSE_HO_SUCC
*****************************************************************************/
VOS_VOID NAS_GMM_SndMmcPsRegResultInd(
    GMM_MMC_ACTION_TYPE_ENUM_U32        enActionType,
    GMM_MMC_ACTION_RESULT_ENUM_U32      enActionResult,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
)
{
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstMsg          = VOS_NULL_PTR;
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(GMMMMC_PS_REG_RESULT_IND_STRU);

    pstInternalMsg  = (GMMMMC_PS_REG_RESULT_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmcPsRegResultInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* 填充IE值 */
    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = GMMMMC_PS_REG_RESULT_IND;
    pstMsg->enGmmActionType               = enActionType;
    pstMsg->enActionResult                = enActionResult;
    pstMsg->enRegFailCause                = enCause;
    pstMsg->enNetType                     = NAS_MML_GetCurrNetRatType();
    pstMsg->ulServiceStatus               = Gmm_ComServiceSts();

    pstMsg->enReqDomain                   = GMM_MMC_REG_DOMAIN_PS;

    if (GMM_MMC_ACTION_RAU == enActionType)
    {
        pstMsg->ulRegCounter = g_GmmRauCtrl.ucRauAttmptCnt;

        /* 根据当前的注册类型决定是否为联合RAU */
        if ((GMM_RAU_COMBINED          == g_GmmGlobalCtrl.ucSpecProc)
         || (GMM_RAU_WITH_IMSI_ATTACH  == g_GmmGlobalCtrl.ucSpecProc))
        {
            pstMsg->enGmmActionType  = GMM_MMC_ACTION_COMBINED_RAU;

            pstMsg->enReqDomain      = GMM_MMC_REG_DOMAIN_PS_CS;

        }
    }
    else
    {
        pstMsg->ulRegCounter = g_GmmAttachCtrl.ucAttachAttmptCnt;

        /* 根据当前的注册类型决定是否为联合ATTACH */
        if ((GMM_ATTACH_WHILE_IMSI_ATTACHED == g_GmmGlobalCtrl.ucSpecProc)
         || (GMM_ATTACH_COMBINED            == g_GmmGlobalCtrl.ucSpecProc))
        {
            pstMsg->enGmmActionType  = GMM_MMC_ACTION_COMBINED_ATTACH;

            pstMsg->enReqDomain      = GMM_MMC_REG_DOMAIN_PS_CS;

        }
    }

    if ( (GMM_MMC_ACTION_PROC_FALSE == g_GmmGlobalCtrl.ucRealProFlg)
      && (GMM_MMC_ACTION_RESULT_SUCCESS == pstMsg->enActionResult))
    {
        /* RAU succ假流程可能带原因值NAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC */
        /* 除了NAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC，其他原因值都填为NAS_MML_REG_FAIL_CAUSE_LOCAL_NULL */
        if (NAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC != enCause)
        {
            pstMsg->enRegFailCause = NAS_MML_REG_FAIL_CAUSE_LOCAL_NULL;
        }
    }


    pstMsg->enRsltDomain = NAS_GMM_GetRegRsltDomain(pstMsg->enGmmActionType,
                                                    pstMsg->enActionResult,
                                                    pstMsg->enRegFailCause);


    /* 周期性RAU需要通知LMM */
    if ((GMM_TRUE == g_GmmRauCtrl.ucPeriodicRauFlg)
     && (GMM_MMC_ACTION_RAU == enActionType))
    {
        pstMsg->enGmmActionType  = GMM_MMC_ACTION_PERIODC_RAU;
    }

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);
}
/*****************************************************************************
 函 数 名  : NAS_GMM_SndMmcSrResultInd
 功能描述  : GMM向MMC发送SR的结果
 输入参数  : GMM_MMC_ACTION_RESULT_ENUM_U32      enActionResult
             NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月25日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_SndMmcServiceRequestResultInd(
    GMM_MMC_ACTION_RESULT_ENUM_U32      enActionResult,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
)
{
    GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU *pstMsg          = VOS_NULL_PTR;
    GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                              ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU);
    pstInternalMsg  = (GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmcServiceRequestResultInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    /* 填充IE值 */
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = GMMMMC_SERVICE_REQUEST_RESULT_IND;
    pstMsg->enActionResult                = enActionResult;                       /* 填写detach原因                           */
    pstMsg->enRegFailCause                = enCause;
    pstMsg->ulServiceSts                  = Gmm_ComServiceSts();

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);
}

/*****************************************************************************
 函 数 名  : NAS_GMM_SndMmcMmDetachInfo
 功能描述  : GMM向MMC和MM发送DETACH 信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月23日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数
  2.日    期   : 2011年12月01日
    作    者   : w00176964
    修改内容   : phaseIV调整:增加detach类型IE项，disable场景需要判断

  3.日    期   : 2013年6月6日
    作    者   : w00167002
    修改内容   : V9R1_SVLTE项目修改:发送给MMC当前的detach结果时候，需要停止DETACH
                 保护定时器。
  4.日    期   : 2014年10月18日
    作    者   : w00167002
    修改内容   : DETACH完成后没有充值T3321的超时次数，导致下次DETACH的次数不正确
*****************************************************************************/
VOS_VOID NAS_GMM_SndMmcMmDetachInfo()
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo;

    /* 获取当前网络模式 */
    pstCampInfo     = NAS_MML_GetCurrCampPlmnInfo();

    if (NAS_MML_NET_MODE_I == pstCampInfo->enNetworkMode)
    {
        /* 网络模式I下,PS DETACH标志存在,向MMC发送DETACH CNF的同时向MM发送GprsDetachComplete */
        if (GMM_WAIT_PS_DETACH ==
            (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH) )
        {
            NAS_GMM_SndMmGprsDetachComplete();

            /* MMC需要知道detach类型，因此先发送然后清除detach类型 */
            NAS_GMM_SndMmcDetachCnf();

            g_GmmGlobalCtrl.stDetachInfo.enDetachType &= ~GMM_WAIT_PS_DETACH;


            /* GMM停止PS域的DETACH保护定时器 */
            Gmm_TimerStop(GMM_TIMER_PROTECT_PS_DETACH);
        }

        /* 网络模式I下,CS DETACH标志存在,向MM发送ImsiDetachComplete */
        if (GMM_WAIT_CS_DETACH ==
            (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_CS_DETACH) )
        {
            NAS_GMM_SndMmImsiDetachComplete();
            g_GmmGlobalCtrl.stDetachInfo.enDetachType &= ~GMM_WAIT_CS_DETACH;
        }
    }
    else
    {
        /* 网络模式II下,PS DETACH标志存在,向MMC发送DETACH CNF */
        if (GMM_WAIT_PS_DETACH ==
            (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH) )
        {
            NAS_GMM_SndMmcDetachCnf();
            g_GmmGlobalCtrl.stDetachInfo.enDetachType &= ~GMM_WAIT_PS_DETACH;


            /* GMM停止PS域的DETACH保护定时器 */
            Gmm_TimerStop(GMM_TIMER_PROTECT_PS_DETACH);
        }
    }

    g_GmmDetachCtrl.ucT3321OutCnt = 0;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs
 功能描述  : 小区被BAR或不支持GPRS业务时，上报ACTION_RESULT
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年03月01日
    作    者   : W00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  3.日    期   : 2011年7月23日
    作    者   : w00166186
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
*****************************************************************************/
VOS_VOID NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
)
{
    VOS_UINT8                               ucOldSpecProc;

    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;
    ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;

    if ( (0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
      || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState) )
    {
        g_GmmGlobalCtrl.ucSpecProc = GMM_ATTACH_NORMAL;

        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     enCause);
    }
    else
    {
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;

        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     enCause);
    }
    g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_SndMmcActionResultIndWhenInForbiddenList
 功能描述  : 小区在禁止网络或者禁止小区时，上报ACTION_RESULT
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年03月15日
    作    者   : 欧阳飞
    修改内容   : 新生成函数
  2.日    期   : 2011年08月05日
    作    者   : w00166186
    修改内容   : 新生成函数
  3.日    期   : 2011年12月23日
    作    者   : w00167002
    修改内容   : DTS2011111901055:假流程上报原因值由NAS_MML_REG_FAIL_CAUSE_NULL
                  修改为NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE.
                  修改原因:在ON PLMN状态，收到此假流程消息，若原因值小于
                  NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE，则可能发起搜网。
  4.日    期   : 2012年4月19日
    作    者   : z40661
    修改内容   : DTS2012032204099：FORBID类型不正确
*****************************************************************************/
VOS_VOID NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(
    VOS_UINT32                          ulForbiddenMask
)
{
    VOS_UINT8                           ucOldSpecProc;
    VOS_UINT32                          ulCause;

    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;
    ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;

    if ( MMC_GMM_NO_FORBIDDEN == ulForbiddenMask )
    {
        ulCause = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
    }
    else if ( MMC_GMM_FORBIDDEN_PLMN == (ulForbiddenMask & MMC_GMM_FORBIDDEN_PLMN) )
    {
        ulCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN;
    }
    else if ( MMC_GMM_FORBIDDEN_PLMN_FOR_GPRS ==  (ulForbiddenMask & MMC_GMM_FORBIDDEN_PLMN_FOR_GPRS ) )
    {
        ulCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS;
    }
    else if ( MMC_GMM_FORBIDDEN_LA_FOR_ROAM == (ulForbiddenMask & MMC_GMM_FORBIDDEN_LA_FOR_ROAM )  )
    {
        ulCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM;
    }
    else if ( MMC_GMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS == (ulForbiddenMask & MMC_GMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS )  )
    {
        ulCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS;
    }
    else
    {
        ulCause = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
    }


    if ( (0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
      || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState) )
    {
        g_GmmGlobalCtrl.ucSpecProc = GMM_ATTACH_NORMAL;
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     (VOS_UINT16)ulCause);
    }
    else
    {
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;

        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     (VOS_UINT16)ulCause);
    }

    g_GmmGlobalCtrl.ucSpecProc   = ucOldSpecProc;
    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

    return;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_SndTcRrRelInd
 功能描述  : GMM向TC发送连接释放消息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月14日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_SndTcRrRelInd(VOS_VOID)
{
    TCGMM_RR_REL_IND_STRU              *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* 申请消息 */
    pstMsg = (TCGMM_RR_REL_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                                                  sizeof(TCGMM_RR_REL_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_GMM_SndTcRrRelInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* 封装消息 */
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TC;
    pstMsg->stMsgHeader.ulLength        = sizeof(TCGMM_RR_REL_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->stMsgHeader.ulMsgName       = TCGMM_RR_REL_IND;

    /* 发送消息 */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pstMsg);
    if( VOS_OK != ulRet )
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_SndTcRrRelInd,WARNING: Message sends fail");
        return;
    }
}


/*****************************************************************************
 函 数 名  : NAS_GMM_SndTcHandoverInd
 功能描述  : 通知TC发生系统间切换
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月14日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_SndTcHandoverInd(VOS_VOID)
{
    TCGMM_HANDOVER_IND_STRU            *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* 申请消息 */
    pstMsg = (TCGMM_HANDOVER_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                                               sizeof(TCGMM_HANDOVER_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndTcHandoverInd():ERROR:Memory Alloc Error for pstMsg");
        return;
    }

    /* 封装消息 */
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TC;
    pstMsg->stMsgHeader.ulLength        = sizeof(TCGMM_HANDOVER_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->stMsgHeader.ulMsgName       = TCGMM_HANDOVER_IND;

    pstMsg->enNetRat = NAS_MML_GetCurrNetRatType();

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pstMsg);
    if (VOS_OK != ulRet)
    {
        /* 发送失败 */
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_SndTcHandoverInd():WARNING:GMM SEND TC handover failed!");
    }

    return;
}



/*****************************************************************************
 函 数 名  : NAS_GMM_SndRabmMmlProcStatusQryCnf
 功能描述  : 通知RABM当前状态的查询结果
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月21日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_SndRabmMmlProcStatusQryCnf(
    RABM_GMM_MML_PROC_STATUS_STRU     *pstMmlProcStatus
)
{
    GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU      *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                  ulRet;

    /* 申请消息 */
    pstMsg = (GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                                               sizeof(GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndRabmMmlProcStatusQryCnf():ERROR:Memory Alloc Error for pstMsg");
        return;
    }

    /* 封装消息 */
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_RABM;
    pstMsg->stMsgHeader.ulLength        = sizeof(GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->stMsgHeader.ulMsgName       = ID_GMM_RABM_MML_PROC_STATUS_QRY_CNF;

    pstMsg->stMmlProcStatus = *pstMmlProcStatus;

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pstMsg);
    if (VOS_OK != ulRet)
    {
        /* 发送失败 */
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_SndRabmMmlProcStatusQryCnf():WARNING:GMM SEND MSG failed!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_SndMmcCipherInfoInd
 功能描述  : GMM主动向MMC发送Cipher信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年02月02日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_SndMmcCipherInfoInd(VOS_VOID)
{
    MMC_GMM_CIPHER_INFO_IND_STRU       *pstMsg          = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstMsg  = (MMC_GMM_CIPHER_INFO_IND_STRU*)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_GMM_CIPHER_INFO_IND_STRU));
    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmcCipherInfoInd: ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* 填写消息头 */
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = sizeof(MMC_GMM_CIPHER_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = GMMMMC_CIPHER_INFO_IND;

    pstMsg->ucGprsCipher                  = gstGmmCasGlobalCtrl.ucGprsCipher;
    pstMsg->ucGprsCipherAlg               = gstGmmCasGlobalCtrl.ucGprsCipherAlg;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);
}

/*****************************************************************************
 函 数 名  : NAS_GMM_SndSmSigConnInd
 功能描述  : 通知SM当前存在PS信令连接
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月1日
    作    者   : l65478
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_SndSmSigConnInd(VOS_VOID)
{
    GMMSM_SIG_CONN_IND_STRU            *pstMsg;
    VOS_UINT32                          ulRet;

    pstMsg = (GMMSM_SIG_CONN_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                          sizeof(GMMSM_SIG_CONN_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_GMM_SndSmSigConnInd:WARNING: Memory Alloc Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_SM;

    pstMsg->stMsgHeader.ulMsgName       = GMMSM_SIG_CONN_IND;

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pstMsg);

    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_SndSmSigConnInd:WARNING: Send msg Fail.");
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_SndSimAuthFailInfo
 功能描述  : 把USIMM_AUTH_RESULT_ENUM_UINT32类型鉴权失败原因值转换为
                NAS_MML_SIM_AUTH_FAIL_ENUM_UINT16类型
 输入参数  : enSimFailValue:USIMM_AUTH_RESULT_ENUM_UINT32类型鉴权失败原因值
 输出参数  : 无
 返 回 值  : NAS_MML_SIM_AUTH_FAIL_ENUM_UINT16类型鉴权失败原因值
 修改历史      :
 1.日    期   : 2013年11月16日
   作    者   : m00217266
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_SIM_AUTH_FAIL_ENUM_UINT16 NAS_GMM_ConvertUsimAuthFailInfo(
    USIMM_AUTH_RESULT_ENUM_UINT32    enSimFailValue
)
{
    NAS_MML_SIM_AUTH_FAIL_ENUM_UINT16 enRptSimFailValue;
    enRptSimFailValue = NAS_MML_SIM_AUTH_FAIL_NULL;

    switch (enSimFailValue)
    {
        case USIMM_AUTH_MAC_FAILURE:
            enRptSimFailValue = NAS_MML_SIM_AUTH_FAIL_MAC_FAILURE;
            break;
        case USIMM_AUTH_SYNC_FAILURE:
            enRptSimFailValue = NAS_MML_SIM_AUTH_FAIL_SYNC_FAILURE;
            break;
        case USIMM_AUTH_UMTS_OTHER_FAILURE:
            enRptSimFailValue = NAS_MML_SIM_AUTH_FAIL_UMTS_OTHER_FAILURE;
            break;
        case USIMM_AUTH_GSM_OTHER_FAILURE:
            enRptSimFailValue = NAS_MML_SIM_AUTH_FAIL_GSM_OTHER_FAILURE;
            break;
        default:
            enRptSimFailValue = NAS_MML_SIM_AUTH_FAIL_UMTS_OTHER_FAILURE;
            break;
    }

    return enRptSimFailValue;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_SndSimAuthFailInfo
 功能描述  : 上报的sim卡鉴权失败信息
 输入参数  : NAS_MML_SIM_AUTH_FAIL_ENUM_UINT16:鉴权失败原因值
 输出参数  : 无
 返 回 值  : VOS_VOID
 修改历史      :
 1.日    期   : 2013年11月16日
   作    者   : m00217266
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_SndMmcSimAuthFailInfo(
    NAS_MML_SIM_AUTH_FAIL_ENUM_UINT16  enSimAuthFailValue
)
{
    MMCGMM_SIM_AUTH_FAIL_IND_STRU      *pstMsg              = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstMsg  = (MMCGMM_SIM_AUTH_FAIL_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_SIM_AUTH_FAIL_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength          = sizeof(MMCGMM_SIM_AUTH_FAIL_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = MMCGMM_SIM_AUTH_FAIL_IND;
    pstMsg->ucReservel                  = 0;

    pstMsg->enSimAuthFailValue          = enSimAuthFailValue;
    pstMsg->enSrvDomain                 = MM_COM_SRVDOMAIN_PS;

    if ((GMM_RAU_COMBINED               == g_GmmGlobalCtrl.ucSpecProc)
     || (GMM_RAU_WITH_IMSI_ATTACH       == g_GmmGlobalCtrl.ucSpecProc)
     || (GMM_ATTACH_WHILE_IMSI_ATTACHED == g_GmmGlobalCtrl.ucSpecProc)
     || (GMM_ATTACH_COMBINED            == g_GmmGlobalCtrl.ucSpecProc))
    {
        pstMsg->enSrvDomain             = MM_COM_SRVDOMAIN_CS_PS;
    }

    NAS_MML_SndInternalMsg(pstMsg);

    return;
}

#if(FEATURE_ON == FEATURE_DSDS)
/*******************************************************************************
 函 数 名  : NAS_GMM_SndAsBeginSessionNotify
 功能描述  : 向AS发送RRMM_BEGIN_SESSION_NOTIFY消息
 输入参数  : ulReceiverPid:接收者PID
             enSessionType:Session类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

1.日    期   : 2014年6月16日
  作    者   : w00242748
  修改内容   : DSDS 新特性
*******************************************************************************/
VOS_VOID NAS_GMM_SndAsBeginSessionNotify(
    VOS_UINT32                          ulReceiverPid,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enSessionType
)
{
    VOS_UINT32                          ulResult;
    RRMM_BEGIN_SESSION_NOTIFY_STRU     *pstBeginSessionNotify = VOS_NULL_PTR;

    /* 申请消息结构内存 */
    pstBeginSessionNotify       = (RRMM_BEGIN_SESSION_NOTIFY_STRU*)PS_ALLOC_MSG(WUEPS_PID_GMM,
                                                                        sizeof(RRMM_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstBeginSessionNotify)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndAsBeginSessionNotify(): Alloc msg fail!");
        return;
    }

    /* 结构体清零 */
    PS_MEM_SET((VOS_INT8*)pstBeginSessionNotify + VOS_MSG_HEAD_LENGTH, 0,
                    sizeof(RRMM_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 构造消息结构体 */
    pstBeginSessionNotify->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstBeginSessionNotify->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->stMsgHeader.ulReceiverPid     = ulReceiverPid;
    pstBeginSessionNotify->stMsgHeader.ulMsgName         = RRMM_BEGIN_SESSION_NOTIFY;

    pstBeginSessionNotify->enSessionType                 = enSessionType;

    /* 调用VOS发送原语 */
    ulResult = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_GMM, (struct MsgCB **)&pstBeginSessionNotify);

    if(VOS_OK != ulResult)
    {
        /* 发送失败 */
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_SndAsBeginSessionNotify():WARNING:MMC SEND AS BEGIN SESSION FAILED!");
        return;
    }

    return;
}

/*******************************************************************************
 函 数 名  : NAS_GMM_SndAsEndSessionNotify
 功能描述  : 向AS发送RRMM_END_SESSION_NOTIFY消息
 输入参数  : ulReceiverPid:接收者PID
             enSessionType:Session类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

1.日    期   : 2014年6月16日
  作    者   : w00242748
  修改内容   : DSDS 新特性
2.日    期   : 2014年7月18日
  作    者   : b00269685
  修改内容   : 增加延迟时间
*******************************************************************************/
VOS_VOID NAS_GMM_SndAsEndSessionNotify(
    VOS_UINT32                          ulReceiverPid,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enSessionType,
    VOS_UINT32                          ulDelayTime
)
{
    VOS_UINT32                          ulResult;
    RRMM_END_SESSION_NOTIFY_STRU       *pstEndSessionNotify = VOS_NULL_PTR;

    /* 申请消息结构内存 */
    pstEndSessionNotify       = (RRMM_END_SESSION_NOTIFY_STRU*)PS_ALLOC_MSG(WUEPS_PID_GMM,
                                                                        sizeof(RRMM_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstEndSessionNotify)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndAsEndSessionNotify(): Alloc msg fail!");
        return;
    }

    /* 结构体清零 */
    PS_MEM_SET((VOS_INT8*)pstEndSessionNotify + VOS_MSG_HEAD_LENGTH, 0,
                    sizeof(RRMM_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 构造消息结构体 */
    pstEndSessionNotify->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstEndSessionNotify->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstEndSessionNotify->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstEndSessionNotify->stMsgHeader.ulReceiverPid     = ulReceiverPid;
    pstEndSessionNotify->stMsgHeader.ulMsgName         = RRMM_END_SESSION_NOTIFY;
    pstEndSessionNotify->enSessionType                 = enSessionType;
    pstEndSessionNotify->enCsRelAll                    = VOS_FALSE;
    pstEndSessionNotify->enPsRelAll                    = VOS_FALSE;
    pstEndSessionNotify->ulDelayTime                   = ulDelayTime;

    /* 调用VOS发送原语 */
    ulResult = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_GMM, (struct MsgCB **)&pstEndSessionNotify);

    if(VOS_OK != ulResult)
    {
        /* 发送失败 */
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_SndAsEndSessionNotify():WARNING:MMC SEND AS END SESSION failed!");
        return;
    }

    return;
}

/*******************************************************************************
 函 数 名  : NAS_GMM_SndBeginSessionNotify
 功能描述  : 向AS/LMM发送RRMM_BEGIN_SESSION_NOTIFY消息
 输入参数  : enRrcSessionType:Session类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

1.日    期   : 2014年6月16日
  作    者   : w00242748
  修改内容   : DSDS 新特性
2.日    期   : 2015年9月4日
  作    者   : j00174725
  修改内容   : DTS2015082406288
*******************************************************************************/
VOS_VOID NAS_GMM_SndBeginSessionNotify(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType
)
{
    TAF_CTRL_STRU                       stCtrl;
    MTC_SESSION_TYPE_ENUM_UINT8         enMtcSessionType;

#if(FEATURE_ON == FEATURE_LTE)
    GMM_LMM_SESSION_TYPE_ENUM_UINT8     enLmmSessionType;
#endif

    enMtcSessionType = MTC_SESSION_TYPE_BUTT;
    PS_MEM_SET(&stCtrl, 0x0, sizeof(stCtrl));


    /* 平台支持W/TD，发送end session */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
    {
        NAS_GMM_SndAsBeginSessionNotify(WUEPS_PID_WRR, enRrcSessionType);
    }

    /* 平台支持G，发送end session */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        NAS_GMM_SndAsBeginSessionNotify(UEPS_PID_GAS, enRrcSessionType);
    }

#if(FEATURE_ON == FEATURE_LTE)
    NAS_GMM_ConvertRrcSessionTypeToLmmFormat(enRrcSessionType, &enLmmSessionType);

    /* 平台支持LTE，发送end session */
    if ( VOS_TRUE == NAS_MML_IsPlatformSupportLte() )
    {
        NAS_GMM_SndLmmBeginSessionNotify(enLmmSessionType);
    }
#endif

    if(VOS_OK == NAS_ConvertSessionTypeToMTCFormat(enRrcSessionType, &enMtcSessionType))
    {
        /* 填写CTL头 */
        stCtrl.ulModuleId = WUEPS_PID_GMM;

        MTC_SetBeginSessionInfo(&stCtrl,enMtcSessionType);
    }

    return;
}

/*******************************************************************************
 函 数 名  : NAS_GMM_SndEndSessionNotify
 功能描述  : 向AS/LMM发送RRMM_END_SESSION_NOTIFY消息
 输入参数  : enRrcSessionType:Session类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

1.日    期   : 2014年6月16日
  作    者   : w00242748
  修改内容   : DSDS 新特性
2.日    期   : 2014年7月17日
  作    者   : b00269685
  修改内容   : 增加delay 时长
3.日    期   : 2015年9月4日
  作    者   : j00174725
  修改内容   : DTS2015082406288
*******************************************************************************/
VOS_VOID NAS_GMM_SndEndSessionNotify(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType
)
{
    TAF_CTRL_STRU                                           stCtrl;
    MTC_SESSION_TYPE_ENUM_UINT8                             enMtcSessionType;

    NAS_MML_DSDS_END_SESSION_DELAY_STRU                    *pstEndDelay = VOS_NULL_PTR;
    VOS_UINT32                                              ulDelayTime;
#if(FEATURE_ON == FEATURE_LTE)
    GMM_LMM_SESSION_TYPE_ENUM_UINT8                         enLmmSessionType;
#endif

    enMtcSessionType = MTC_SESSION_TYPE_BUTT;
    PS_MEM_SET(&stCtrl, 0x0, sizeof(stCtrl));
    pstEndDelay = NAS_MML_GetDsdsSessionEndDelay();

    if ((RRC_NAS_SESSION_TYPE_PS_ATTACH == enRrcSessionType)
     || (RRC_NAS_SESSION_TYPE_PS_RAU    == enRrcSessionType))
    {
        ulDelayTime = pstEndDelay->ulPsRegEndSessionDelayTime;
    }
    else
    {
        ulDelayTime = 0;
    }

    /* 平台支持W/TD，发送end session */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
    {
        NAS_GMM_SndAsEndSessionNotify(WUEPS_PID_WRR, enRrcSessionType, ulDelayTime);
    }

    /* 平台支持G，发送end session */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        NAS_GMM_SndAsEndSessionNotify(UEPS_PID_GAS, enRrcSessionType, ulDelayTime);
    }

#if(FEATURE_ON == FEATURE_LTE)
    NAS_GMM_ConvertRrcSessionTypeToLmmFormat(enRrcSessionType, &enLmmSessionType);

    /* 平台支持LTE，发送end session */
    if ( VOS_TRUE == NAS_MML_IsPlatformSupportLte() )
    {
        NAS_GMM_SndLmmEndSessionNotify(enLmmSessionType);
    }
#endif

    if(VOS_OK == NAS_ConvertSessionTypeToMTCFormat(enRrcSessionType, &enMtcSessionType))
    {
        /* 填写CTL头 */
        stCtrl.ulModuleId = WUEPS_PID_GMM;

        MTC_SetEndSessionInfo(&stCtrl,enMtcSessionType);
    }

    return;
}


/*******************************************************************************
 函 数 名  : NAS_GMM_NotifySession
 功能描述  : 向AS/LMM发送开始Session消息
 输入参数  : ucCurState:当前状态
             ucTargetState:目标状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

1.日    期   : 2014年6月16日
  作    者   : w00242748
  修改内容   : DSDS 新特性
2.日    期   : 2014年7月17日
  作    者   : b00269685
  修改内容   : end session修改
*******************************************************************************/
VOS_VOID NAS_GMM_NotifySessionAccordingStateChg(
    VOS_UINT8                           ucCurState,
    VOS_UINT8                           ucTargetState
)
{
    if ( ucCurState == ucTargetState )
    {
        return;
    }

    /* 当前状态是GMM_REGISTERED_INITIATED，目标状态不是GMM_REGISTERED_INITIATED，
       则认为PS ATTACH过程结束，需释放资源 */
    if ( GMM_REGISTERED_INITIATED == ucCurState )
    {

        /* 注册被拒或鉴权被拒，导致的ATTACH结束时，直接发送end session */
        NAS_GMM_SndEndSessionNotify(RRC_NAS_SESSION_TYPE_PS_ATTACH);

        /* GMM发起ATTACH注册时，进行detach PS域，需发送BEGIN；如果这时发起CS去注册
           直接由MM模块进行，RAU的话，协议上明确规定缓存，等RAU结束之后再发起 */
        if ( GMM_DEREGISTERED_INITIATED == ucTargetState )
        {
            /* 该状态为目标状态时，表示PS DETACH过程正在结束 */
            NAS_GMM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_PS_DETACH);
        }

        return;
    }

    if ( GMM_ROUTING_AREA_UPDATING_INITIATED == ucCurState )
    {
        NAS_GMM_SndEndSessionNotify(RRC_NAS_SESSION_TYPE_PS_RAU);

        return;
    }

    if ( GMM_REGISTERED_INITIATED == ucTargetState )
    {
        /* 该状态为目标状态时，表示PS attach过程正在进行 */
        NAS_GMM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_PS_ATTACH);

        return;
    }

    if ( GMM_ROUTING_AREA_UPDATING_INITIATED == ucTargetState )
    {
        /* 该状态为目标状态时，表示PS RAU过程正在进行 */
        NAS_GMM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_PS_RAU);

        return;
    }

    if ( (GMM_DEREGISTERED_INITIATED == ucCurState)
      || (GMM_REGISTERED_IMSI_DETACH_INITIATED == ucCurState) )
    {
        /* 该状态为目标状态时，表示PS DETACH过程正在进行 */
        NAS_GMM_SndEndSessionNotify(RRC_NAS_SESSION_TYPE_PS_DETACH);

        return;
    }

    if ( (GMM_DEREGISTERED_INITIATED == ucTargetState)
      || (GMM_REGISTERED_IMSI_DETACH_INITIATED == ucTargetState) )
    {
        /* 该状态为目标状态时，表示PS DETACH过程正在结束 */
        NAS_GMM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_PS_DETACH);

        return;
    }

    return;
}

#endif
/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


