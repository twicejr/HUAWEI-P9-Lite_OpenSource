/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcSndLmm.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2010年5月9日
  最近修改   :
  功能描述   : MMC发给Lmm的消息的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2011年05月9日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"

#include "NasComm.h"
#include "NasMmcComFunc.h"

/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

#if (FEATURE_ON == FEATURE_LTE)
#include "NasMmlCtx.h"
#include "NasMmcCtx.h"
#include "NasMmcSndLmm.h"
#include "NasMmcProcNvim.h"
#include "NasMmcProcUsim.h"
#include "asnasapi.h"
#include "NasMmlLib.h"
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
/* 删除ExtAppMmcInterface.h*/
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */
#include "NasMmlMsgProc.h"
#include "MmcLmmInterface.h"
#include "NasMmcFsmPlmnSelection.h"
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
#include "NasUtranCtrlCommFunc.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_SND_LMM_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/


/*****************************************************************************
   2 全局变量定义
*****************************************************************************/
/*****************************************************************************
  3 宏定义
*****************************************************************************/

/*lint -save -e958 */


#if (FEATURE_ON == FEATURE_LTE)

enum NAS_MMC_LMM_START_RAT_MASK{

    NAS_MMC_LMM_START_GSM_MASK          = (0x01),
    NAS_MMC_LMM_START_WCDMA_MASK        = (0x02),
    NAS_MMC_LMM_START_LTE_FDD_MASK      = (0x04),
    NAS_MMC_LMM_START_LTE_TDD_MASK      = (0x08),
    NAS_MMC_LMM_START_MASK_BUTT

};

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmStopReq
 功能描述  : 向LMM发送关机请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年3月28日
   作    者   : W00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年8月11日
   作    者   : W00167002
   修改内容   : 增加消息长度的赋值
 3.日    期   : 2011年11月28日
   作    者   : z00161729
   修改内容   : MMC与LMM消息交互采用内部消息队列，为保证PC上GTR功能已有用例可以正常使用，
                在PC上MMC、GMM和LMM的交互还使用外部消息，发送消息函数需要用宏NAS_STUB隔开

 4.日    期   : 2013年7月4日
   作    者   : z00234330
   修改内容   : 增加开机LOG

*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmStopReq( VOS_VOID )
{
    /* 定义原语类型指针 */
    MMC_LMM_STOP_REQ_STRU              *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_STOP_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_STOP_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_STOP_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmStopReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(MMC_LMM_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid    = PS_PID_MM;
    pstMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid      = WUEPS_PID_MMC;
    pstMsg->ulLength         = sizeof(MMC_LMM_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->ulMsgId          = ID_MMC_LMM_STOP_REQ;
    pstMsg->ulOpId           = 0;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmStopReq:ERROR:PS_SEND_MSG FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    /* Modified by z00234330 for 开机LOG, 2013-6-24, begin */
    (VOS_VOID)vos_printf("NAS_MMC_SndLmmStopReq, tick = 0x%x\r\n ", VOS_GetSlice());
    /* Modified by z00234330 for 开机LOG, 2013-6-24, begin */

    NAS_TRACE_HIGH("Snd poweroff req to LMM!");

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmUsimStatusReq
 功能描述  : NAS通知Lmm usim卡状态
 输入参数  : MMC_LMM_USIM_STATUS_ENUM_UINT32     ulUsimState
 输出参数  : 无
 返 回 值  : VOS_ERR: ID_MMC_LMM_USIM_STATUS_REQ消息发送失败
             VOS_OK : ID_MMC_LMM_USIM_STATUS_REQ消息发送成功
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年3月28日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年8月11日
   作    者   : W00167002
   修改内容   : 增加消息长度的赋值
 3.日    期   : 2011年11月28日
   作    者   : z00161729
   修改内容   : MMC与LMM消息交互采用内部消息队列，为保证PC上GTR功能已有用例可以正常使用，
                在PC上MMC、GMM和LMM的交互还使用外部消息，发送消息函数需要用宏NAS_STUB隔开

*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmUsimStatusReq(
    MMC_LMM_USIM_STATUS_ENUM_UINT32     enUsimState
)
{
    /* 定义原语类型指针 */
    MMC_LMM_USIM_STATUS_REQ_STRU*       pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_USIM_STATUS_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_USIM_STATUS_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_USIM_STATUS_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_USIM_STATUS_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmUsimStatusReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(MMC_LMM_USIM_STATUS_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_USIM_STATUS_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_USIM_STATUS_REQ;
    pstMsg->ulOpId                      = 0;
    pstMsg->ulUsimState                 = enUsimState;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmUsimStatusReq:ERROR: SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}




/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmPlmnAnyCellSrchReq
 功能描述  : 向LTE发送任意搜网请求
 输入参数  : ulEventType:消息类型
             pstMsg:ID_MMA_MMC_START_REQ消息的首地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月9日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2011年8月11日
   作    者   : W00167002
   修改内容   : 增加消息长度的赋值
 3.日    期   : 2011年11月28日
   作    者   : z00161729
   修改内容   : MMC与LMM消息交互采用内部消息队列，为保证PC上GTR功能已有用例可以正常使用，
                在PC上MMC、GMM和LMM的交互还使用外部消息，发送消息函数需要用宏NAS_STUB隔开
 4.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改

*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmPlmnAnyCellSrchReq(VOS_VOID)
{
    /* 定义原语类型指针 */
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmPlmnAnyCellSrchReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                         sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 构造发送消息 */
    pstMsg->ulReceiverCpuId                 = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid                   = PS_PID_MM;
    pstMsg->ulSenderCpuId                   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                     = WUEPS_PID_MMC;
    pstMsg->ulLength                        = sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                         = ID_MMC_LMM_PLMN_SRCH_REQ;
    pstMsg->ulOpId                          = 0;
    pstMsg->enSrchType                      = MMC_LMM_PLMN_SRCH_ANY;

    pstMsg->bitOpPlmnInfoCampFlg            = VOS_TRUE;
    pstMsg->enFftScanType                   = MMC_LMM_FFT_SCAN_TYPE_NONE;

    NAS_MML_SaveNwSearchReqInfo(pstMsg);

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
     {
         NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmPlmnAnyCellSrchReq():WARNING:SEND LMM PLMN ANYCELL SEARCH REQ FIAL");
     }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmPlmnListReq
 功能描述  : 向LTE发送LIST搜网请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月22日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年11月28日
   作    者   : z00161729
   修改内容   : MMC与LMM消息交互采用内部消息队列，为保证PC上GTR功能已有用例可以正常使用，
                在PC上MMC、GMM和LMM的交互还使用外部消息，发送消息函数需要用宏NAS_STUB隔开
 3.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmPlmnListReq(VOS_VOID)
{
    /* 定义原语类型指针 */
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmPlmnListReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                         sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 构造发送消息 */
    pstMsg->ulReceiverCpuId                 = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid                   = PS_PID_MM;
    pstMsg->ulSenderCpuId                   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                     = WUEPS_PID_MMC;
    pstMsg->ulLength                        = sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                         = ID_MMC_LMM_PLMN_SRCH_REQ;
    pstMsg->ulOpId                          = 0;
    pstMsg->enSrchType                      = MMC_LMM_PLMN_SRCH_LIST;

    pstMsg->bitOpPlmnInfoCampFlg            = VOS_TRUE;
    pstMsg->enFftScanType                   = MMC_LMM_FFT_SCAN_TYPE_NONE;

    NAS_MML_SaveNwSearchReqInfo(pstMsg);

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmPlmnListReq():WARNING:SEND LMM PLMN list SEARCH REQ FIAL");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}
#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmCsgListSearchReq
 功能描述  : 向LTE发送CSG LIST搜网请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年10月15日
   作    者   : y00358807
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmCsgListSearchReq(VOS_VOID)
{
    /* 定义原语类型指针 */
    MMC_LMM_CSG_LIST_SEARCH_REQ_STRU         *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_CSG_LIST_SEARCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_CSG_LIST_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_CSG_LIST_SEARCH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_CSG_LIST_SEARCH_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmCsgListSearchReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                         sizeof(MMC_LMM_CSG_LIST_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 构造发送消息 */
    pstMsg->ulReceiverCpuId                 = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid                   = PS_PID_MM;
    pstMsg->ulSenderCpuId                   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                     = WUEPS_PID_MMC;
    pstMsg->ulLength                        = sizeof(MMC_LMM_CSG_LIST_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                         = ID_MMC_LMM_CSG_LIST_SEARCH_REQ;
    pstMsg->ulOpId                          = 0;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmCsgListSearchReq():WARNING:SEND LMM CSG list SEARCH REQ FIAL");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}
#endif
/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmSuspendReq
 功能描述  : 向LTE发送挂起消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月9日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年8月11日
   作    者   : W00167002
   修改内容   : 增加消息长度的赋值
 3.日    期   : 2011年8月17日
   作    者   : w00167002
   修改内容   : V7R1 PHASEII 重构: 添加pc回放
 4.日    期   : 2011年11月28日
   作    者   : z00161729
   修改内容   : MMC与LMM消息交互采用内部消息队列，为保证PC上GTR功能已有用例可以正常使用，
                在PC上MMC、GMM和LMM的交互还使用外部消息，发送消息函数需要用宏NAS_STUB隔开

*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmSuspendReq(VOS_VOID)
{
    /* 定义原语类型指针 */
    MMC_LMM_SUSPEND_REQ_STRU           *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_SUSPEND_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_SUSPEND_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_SUSPEND_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_SUSPEND_REQ_STRU));
#endif

    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmSuspendReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMC_LMM_SUSPEND_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_SUSPEND_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_SUSPEND_REQ;
    pstMsg->ulOpId                      = 0;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmSuspendReq():WARNING:SEND LMM PLMN ANYCELL SEARCH REQ FIAL");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

#ifndef __PS_WIN32_RECUR__

    NAS_MML_SetUePcRecurFlg(VOS_TRUE);
#endif

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmPlmnSrchStopReq
 功能描述  : 向LTE发送停止搜网请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月10日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年8月11日
   作    者   : W00167002
   修改内容   : 增加消息长度的赋值
 3.日    期   : 2011年11月28日
   作    者   : z00161729
   修改内容   : MMC与LMM消息交互采用内部消息队列，为保证PC上GTR功能已有用例可以正常使用，
                在PC上MMC、GMM和LMM的交互还使用外部消息，发送消息函数需要用宏NAS_STUB隔开

*****************************************************************************/

VOS_VOID NAS_MMC_SndLmmPlmnSrchStopReq( VOS_VOID )
{
    /* 定义原语类型指针 */
    MMC_LMM_STOP_PLMN_SRCH_REQ_STRU    *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_STOP_PLMN_SRCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_STOP_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
        pstMsg = (MMC_LMM_STOP_PLMN_SRCH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_STOP_PLMN_SRCH_REQ_STRU));
#endif

    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmPlmnSrchStopReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                         sizeof(MMC_LMM_STOP_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_STOP_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_STOP_PLMN_SRCH_REQ;
    pstMsg->ulOpId                      = 0;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmPlmnSrchStopReq():WARNING:SEND LMM PLMN ANYCELL SEARCH REQ FIAL");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmStartReq
 功能描述  : 发送开机请求,本函数只能使用于L模的接入层开机请求。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

修改历史      :
 1.日    期   : 2011年4月8日
   作    者   : luokaihui /l00167671
   修改内容   : 新生成函数
 2.日    期   : 2011年8月10日
   作    者   : w00176964
   修改内容   : V7R1 PhaseII 开机接口调整
 3.日    期   : 2011年8月11日
   作    者   : W00167002
   修改内容   : 增加消息长度的赋值
 4.日    期   : 2011年11月28日
   作    者   : z00161729
   修改内容   : MMC与LMM消息交互采用内部消息队列，为保证PC上GTR功能已有用例可以正常使用，
                在PC上MMC、GMM和LMM的交互还使用外部消息，发送消息函数需要用宏NAS_STUB隔开
 5.日    期   : 2012年8月30日
   作    者   : w00176964
   修改内容   : GUTL PhaseII 开机通知RRC当前的UTRAN MODE
 6.日    期   : 2013年7月4日
   作    者   : z00234330
   修改内容   : 增加开机LOG
 7.日    期   : 2015年5月5日
   作    者   : y00245242
   修改内容   : iteration 13开发
 8.日    期   : 2015年8月20日
   作    者   : w00242748
   修改内容   : 动态加载项目

*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmStartReq(VOS_VOID)
{
    MMC_LMM_START_REQ_STRU             *pstMsg     = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatList = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_START_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                        sizeof(MMC_LMM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_START_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_START_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmStartReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET(((VOS_UCHAR *)pstMsg) + VOS_MSG_HEAD_LENGTH, 0,
                                         sizeof(MMC_LMM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_START_REQ;

    if (VOS_TRUE == NAS_MML_IsGULModeConfigured())
    {
        pstMsg->enUtranMode     = NAS_UTRANCTRL_ConvertNasUtranModeToLmmUtranMode(NAS_UTRANCTRL_GetCurrUtranMode());
    }
    else
    {
        pstMsg->enUtranMode     = MMC_LMM_UTRAN_MODE_NULL;
    }

    /* 获取卡状态 */
    if (VOS_TRUE == NAS_MML_GetSimPresentStatus())
    {
        pstMsg->ulUsimState             = MMC_LMM_USIM_VALID;
    }
    else
    {
        pstMsg->ulUsimState             = MMC_LMM_USIM_INVALID;
    }

    /* 取得接入优先级列表 */
    pstRatList  = NAS_MML_GetMsPrioRatList();

    /* 设置接入模式 */
    pstMsg->aucRatPrioList[0]              = NAS_MMC_GetSpecRatPrio(NAS_MML_NET_RAT_TYPE_GSM, pstRatList);
    pstMsg->aucRatPrioList[1]              = NAS_MMC_GetSpecRatPrio(NAS_MML_NET_RAT_TYPE_WCDMA, pstRatList);
    pstMsg->aucRatPrioList[2]              = NAS_MMC_GetSpecRatPrio(NAS_MML_NET_RAT_TYPE_LTE, pstRatList);

    /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    /* 如果有支持的3GPP2接入技术pstMsg->aucRatPrioList[3]填写为1X的优先级RRMM_RAT_PRIO_LOW */
    if (VOS_TRUE == NAS_MML_IsSpec3Gpp2RatInRatList(NAS_MML_3GPP2_RAT_TYPE_CDMA1X, NAS_MML_GetMs3Gpp2PrioRatList()))
    {
        pstMsg->aucRatPrioList[3]          = RRMM_RAT_PRIO_LOW;
    }
    /* 否则pstMsg->aucRatPrioList[3]填写为RRMM_RAT_PRIO_NULL */
    else
    {
        pstMsg->aucRatPrioList[3]          = RRMM_RAT_PRIO_NULL;
    }

    /* 如果有支持的3GPP2接入技术pstMsg->aucRatPrioList[4]填写为HRPD的优先级RRMM_RAT_PRIO_MIDDLE */
    if (VOS_TRUE == NAS_MML_IsSpec3Gpp2RatInRatList(NAS_MML_3GPP2_RAT_TYPE_HRPD, NAS_MML_GetMs3Gpp2PrioRatList()))
    {
        pstMsg->aucRatPrioList[4]          = RRMM_RAT_PRIO_MIDDLE;
    }
    /* 否则pstMsg->aucRatPrioList[4]填写为RRMM_RAT_PRIO_NULL */
    else
    {
        pstMsg->aucRatPrioList[4]          = RRMM_RAT_PRIO_NULL;
    }
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmStartReq():WARNING:SEND LMM START REQ FIAL");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif
    /* Modified by z00234330 for 开机LOG, 2013-6-24, begin */
    (VOS_VOID)vos_printf("NAS_MMC_SndLmmStartReq, tick = 0x%x\r\n ", VOS_GetSlice());
    /* Modified by z00234330 for 开机LOG, 2013-6-24, begin */

    return;
}

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_BuildSndLmmEquPlmnInfo
 功能描述  : 构造通知Lmm的等效plmn信息
 输入参数  : 无
 输出参数  : pstEquPlmnInfo - 构造后的等效plmn列表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年8月21日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2012年8月15日
   作    者   : w00176964
   修改内容   : V7R1C50_GUTL_PhaseII:在disabled RAT中的PLMN从等效PLMN
                列表中删除后发送给RRC
 3.日    期   : 2012年12月4日
   作    者   : w00176964
   修改内容   : DTS201212905979:通知RRC当前EPLMN时,清除禁止PLMN
 4.日    期   : 2013年1月13日
   作    者   : w00242748
   修改内容   : DTS2014010906851:NV 9052配置不允许国际漫游，配置允许漫游MCC为440，
                当前设置接入模式支持GL，L的46012在禁止国际漫游列表中，不应该发起
                注册。刚开始驻留在G，衰减G 46012小区信号，紧急驻留在L的46012，此时
                发生同系统切换到另一个PLMN为46012的小区上，L会报假的TAU流程，MMC收到
                TAU结果后，给LNAS发送等效PLMN 46012，此时LAS因为ANYCELL驻留又收到
                等效PLMN通知，则认为正常驻留，因此会发起注册。
 5.日    期   : 2013年12月13日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseIII项目
 6.日    期   : 2014年5月15日
   作    者   : s00217060
   修改内容   : DTS2014050804905: 删除forb plmn for gprs
 7.日    期   : 2015年4月23日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
 8.日    期   : 2015年5月21日
   作    者   : w001670000
   修改内容   : DTS2015071604422:联通3g卡未开通4g，在46001上LTE注册拒绝#15,LNAS通知MMC需要进行DISABLE
                LTE，后续在WCDMA网络上注册成功。
                接着在W下丢网，触发了搜网LTE失败，后续重新回到WCDMA网络上。接着发起了
                W->LTE的盲重定向，mmc通知LMM等效PLMN时候，删除了禁止网络，即EPLMN个数为0.
                由于LRRC只判断驻留在EPLMN上得TAI信息，导致没有给LNAS上报当前的禁止TAI
                信息，导致LNAS没有给MMC上报禁止LTE的指示，没有禁止LTE网络。
                修改为；MMC在通知LNAS当前EPLMN时候，不删除拒绝#15惩罚的网络，这样
                后续ENABLE LTE后，发生了gu->lte的重定向，LNAS会给MMC上报触发需要DISABLE
                LTE的消息，从而解决了GU->LTE盲重定向的问题。
*****************************************************************************/
VOS_VOID NAS_MMC_BuildSndLmmEquPlmnInfo(
     NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
)
{
    NAS_MML_PLMN_ID_STRU                                    astUniquePlmnList[NAS_MML_MAX_EQUPLMN_NUM];          /* 删除重复项后的EquPLMN列表 */
    VOS_UINT32                                              aulComparedMcc[NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER]; /*允许LTE漫游的MCC列表*/
    VOS_UINT8                                               ucSndEplmnNum;
    VOS_UINT8                                               ucEmcPdpStatusFlg;
    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                *pstDisabledRatPlmnCfg = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo = VOS_NULL_PTR;

    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                 stDisabledRatPlmnCfg;               /* 禁止接入技术的PLMN定制特性 */
    VOS_UINT32                                              i;

    PS_MEM_SET(astUniquePlmnList, 0x00, sizeof(astUniquePlmnList));
    PS_MEM_SET(aulComparedMcc, 0x00, sizeof(aulComparedMcc));
    PS_MEM_SET(&stDisabledRatPlmnCfg, 0, sizeof(NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU));

    ucEmcPdpStatusFlg = NAS_MML_GetEmcPdpStatusFlg();


    /* 获取禁止接入技术的PLMN信息 */
    pstDisabledRatPlmnCfg = NAS_MML_GetDisabledRatPlmnInfo();

    /* 获取运营商定制的MCC列表 */
    NAS_MML_GetRoamEnabledMccList(aulComparedMcc);

    /* 获取forbidden列表 */
    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    ucSndEplmnNum   = pstEquPlmnInfo->ucEquPlmnNum;
    PS_MEM_CPY(astUniquePlmnList, pstEquPlmnInfo->astEquPlmnAddr, ucSndEplmnNum * sizeof(NAS_MML_PLMN_ID_STRU));

    /* 从列表中删除重复的网络 */
    NAS_MMC_DelDuplicatedPlmnInPlmnList(&ucSndEplmnNum, astUniquePlmnList);


    /* 使用禁止接入技术网络列表前先判断下是否有惩罚时间到的网络，如果有先删除 */
    (VOS_VOID)NAS_MML_DeleteExpireValidPeriodPlmnInDisabledRatPlmnList();

    PS_MEM_SET(&stDisabledRatPlmnCfg, 0X00, sizeof(NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU));

    /* 从惩罚PLMN中删除拒绝15的网络 */
    for ( i = 0 ; i < pstDisabledRatPlmnCfg->ulDisabledRatPlmnNum; i++ )
    {
        if (MMC_LMM_DISABLE_LTE_REASON_LMM_NOTIFY_EUTRAN_NOT_ALLOW != pstDisabledRatPlmnCfg->astDisabledRatPlmnId[i].enDisableLteReason)
        {
            PS_MEM_CPY(&stDisabledRatPlmnCfg.astDisabledRatPlmnId[stDisabledRatPlmnCfg.ulDisabledRatPlmnNum],
                       &(pstDisabledRatPlmnCfg->astDisabledRatPlmnId[i]),
                       sizeof(NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU));

            stDisabledRatPlmnCfg.ulDisabledRatPlmnNum++;
        }
    }



    /* 紧急PDN连接不存在时，需要删除forbidden plmn\forbidden plmn for gprs\disabled rat plmn列表的EPLMN */
    if (VOS_FALSE == ucEmcPdpStatusFlg)
    {
        /* 从列表中删除不允许LTE漫游的网络 */
        NAS_MML_DelEqualPlmnNotInAllowLteRoamMccList(&ucSndEplmnNum, astUniquePlmnList, NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER, aulComparedMcc);

        /* 删除禁止的EPLMN，包括forb plmn, 锁网锁卡的PLMN, 不允许漫游的plmn, 卡无效等 */
        NAS_MML_DelForbPlmnInPlmnList(&ucSndEplmnNum, astUniquePlmnList);

        /* 删除forb plmn for gprs */
        NAS_MML_DelPlmnsInRefList(&ucSndEplmnNum, astUniquePlmnList,
                       pstForbidPlmnInfo->ucForbGprsPlmnNum, pstForbidPlmnInfo->astForbGprsPlmnList);


        /* 删除在禁止接入技术的PLMN列表中的EPLMN */
        NAS_MML_DelEqualPlmnsInDisableRatList(&ucSndEplmnNum,
                                              astUniquePlmnList,
                                              NAS_MML_NET_RAT_TYPE_LTE,
                                              stDisabledRatPlmnCfg.ulDisabledRatPlmnNum,
                                              stDisabledRatPlmnCfg.astDisabledRatPlmnId);

    }

    pstEquPlmnInfo->ucEquPlmnNum = ucSndEplmnNum;
    PS_MEM_CPY(pstEquPlmnInfo->astEquPlmnAddr, astUniquePlmnList, ucSndEplmnNum * sizeof(NAS_MML_PLMN_ID_STRU));

    return;
}



/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmEquPlmnReq
 功能描述  : 向LTE下发eplmn 请求
 输入参数  : pstEquPlmnInfo: 发送到LMM的等效PLMN列表信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月9日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年7月24日
    作    者   : l00130025
    修改内容   : PhaseII修改
  3.日    期   : 2011年11月28日
    作    者   : z00161729
    修改内容   : MMC与LMM消息交互采用内部消息队列，为保证PC上GTR功能已有用例可以正常使用，
                 在PC上MMC、GMM和LMM的交互还使用外部消息，发送消息函数需要用宏NAS_STUB隔开
  4.日    期   : 2011年11月24日
    作    者   : w00167002
    修改内容   : DTS2011112405567:原有的函数名NAS_MML_IsPlmnIdInDestPlmnList
                更改为NAS_MML_IsBcchPlmnIdInDestSimPlmnList
  5.日    期   : 2012年05月28日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 C50 CS/PS mode 1
  6.日    期   : 2012年8月14日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题
**************************************************************************/
VOS_VOID NAS_MMC_SndLmmEquPlmnReq(
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
)
{
    VOS_UINT32                          i;
    MMC_LMM_EPLMN_NOTIFY_REQ_STRU      *pstLmmEquPlmnStru = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstLmmEquPlmnStru = (MMC_LMM_EPLMN_NOTIFY_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_EPLMN_NOTIFY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstLmmEquPlmnStru = (MMC_LMM_EPLMN_NOTIFY_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_EPLMN_NOTIFY_REQ_STRU));
#endif

    /* 若分配内存出错,返回失败 */
    if ( VOS_NULL_PTR == pstLmmEquPlmnStru )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmEquPlmnReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstLmmEquPlmnStru + VOS_MSG_HEAD_LENGTH, 0X0,
               sizeof(MMC_LMM_EPLMN_NOTIFY_REQ_STRU) - VOS_MSG_HEAD_LENGTH );

    pstLmmEquPlmnStru->ulReceiverPid   = PS_PID_MM;
    pstLmmEquPlmnStru->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstLmmEquPlmnStru->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstLmmEquPlmnStru->ulSenderPid     = WUEPS_PID_MMC;
    pstLmmEquPlmnStru->ulMsgId         = ID_MMC_LMM_EPLMN_NOTIFY_REQ;
    pstLmmEquPlmnStru->ulLength        = sizeof(MMC_LMM_EPLMN_NOTIFY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
    /* 填充Eplmn,转换为LMM的格式 */
    pstLmmEquPlmnStru->ulEplmnNum = pstEquPlmnInfo->ucEquPlmnNum;

    for ( i = 0 ; i < pstEquPlmnInfo->ucEquPlmnNum ; i++ )
    {
        NAS_MML_ConvertNasPlmnToLMMFormat(&(pstLmmEquPlmnStru->astEplmnList[i]),
                                          &(pstEquPlmnInfo->astEquPlmnAddr[i]));
    }
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */
#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstLmmEquPlmnStru ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmEquPlmnReq():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstLmmEquPlmnStru);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstLmmEquPlmnStru);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmLocalDetachIndActionResultReq
 功能描述  : Local detach通知LMM
 输入参数  : ulLocalDetachType - 本地detach类型
 输出参数  : 无
 返 回 值  : VOS_OK : ID_MMC_LMM_ACTION_RESULT_REQ 消息发送成功
             VOS_ERR: ID_MMC_LMM_ACTION_RESULT_REQ 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月02日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmLocalDetachIndActionResultReq(
    MMC_LMM_GU_LOCAL_DETACH_TYPE_ENUM_UINT32                ulLocalDetachType
)
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_ACTION_RESULT_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
              sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_ACTION_RESULT_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmLocalDetachIndActionResultReq():ERROR:Memory Alloc Error for pstMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                         sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_ACTION_RESULT_REQ;
    pstMsg->ulOpId                      = 0;
    pstMsg->enActionType                = MMC_LMM_ACTION_LOCAL_DETACH;
    pstMsg->bitOpLocalDetachType        = VOS_TRUE;
    pstMsg->ulLocalDetachType           = ulLocalDetachType;
    pstMsg->ulActRst                    = MMC_LMM_RSLT_TYPE_SUCCESS;
    pstMsg->bitOpReqDomain              = VOS_TRUE;
    pstMsg->bitOpRstDomain              = VOS_TRUE;
    pstMsg->ulReqDomain                 = MMC_LMM_PS_ONLY;
    pstMsg->ulRstDomain                 = MMC_LMM_PS_ONLY;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmLocalDetachIndActionResultReq():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmMoDetachIndActionResultReq
 功能描述  : GU下cs或ps mo detach成功后通知LMM
 输入参数  : ulMoDetachType - UE主动detach类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月02日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmMoDetachIndActionResultReq(
    MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32  ulMoDetachType
)
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_ACTION_RESULT_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
              sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_ACTION_RESULT_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmMoDetachIndActionResultReq():ERROR:Memory Alloc Error for pstMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                         sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_ACTION_RESULT_REQ;
    pstMsg->ulOpId                      = 0;
    pstMsg->enActionType                = MMC_LMM_ACTION_MO_DETACH;
    pstMsg->bitOpMoDetachType           = VOS_TRUE;
    pstMsg->ulMoDetachType              = ulMoDetachType;
    pstMsg->ulActRst                    = MMC_LMM_RSLT_TYPE_SUCCESS;

    if (MMC_LMM_MO_DET_PS_ONLY == ulMoDetachType)
    {
        pstMsg->bitOpReqDomain = VOS_TRUE;
        pstMsg->bitOpRstDomain = VOS_TRUE;
        pstMsg->ulReqDomain    = MMC_LMM_PS_ONLY;
        pstMsg->ulRstDomain    = MMC_LMM_PS_ONLY;
    }
    else if (MMC_LMM_MO_DET_CS_ONLY == ulMoDetachType)
    {
        pstMsg->bitOpReqDomain = VOS_TRUE;
        pstMsg->bitOpRstDomain = VOS_TRUE;
        pstMsg->ulReqDomain    = MMC_LMM_IMSI_ONLY;
        pstMsg->ulRstDomain    = MMC_LMM_IMSI_ONLY;
    }
    else if(MMC_LMM_MO_DET_CS_PS == ulMoDetachType)
    {
        pstMsg->bitOpReqDomain = VOS_TRUE;
        pstMsg->bitOpRstDomain = VOS_TRUE;
        pstMsg->ulReqDomain    = MMC_LMM_COMBINED_PS_IMSI;
        pstMsg->ulRstDomain    = MMC_LMM_COMBINED_PS_IMSI;
    }
    else
    {
    }
#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmMoDetachIndActionResultReq():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmMtDetachIndActionResultReq
 功能描述  : GU业务流程：网络发起的detach
              通过此原语把业务流程结果通知LMM；LMM将按照24.008，24.301成功
              或拒绝描述进行处理
 输入参数  : enMtType:网络发起的DETACH 类型
             enCnCause:DEATCH失败原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2011年11月28日
    作    者   : z00161729
    修改内容   : MMC与LMM消息交互采用内部消息队列，为保证PC上GTR功能已有用例可以正常使用，
                 在PC上MMC、GMM和LMM的交互还使用外部消息，发送消息函数需要用宏NAS_STUB隔开
  3.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 Phase IV调整,修改函数名
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmMtDetachIndActionResultReq(
    NAS_MMC_GMM_NT_DETACH_ENUM_U32      enMtType,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCnCause
)
{
    /* 定义原语类型指针 */
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_ACTION_RESULT_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
         sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_ACTION_RESULT_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmMtDetachIndActionResultReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                         sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    NAS_MMC_BuildMmcLmmDetachIndActionResultReqMsg(enMtType, enCnCause, pstMsg);

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmMtDetachIndActionResultReq():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmRegActionResultReq
 功能描述  : GU业务流程：发起业务时的类型:仅ATTACH, RAU, DETACH
              通过此原语把业务流程结果通知LMM；LMM将按照24.008，24.301成功
              或拒绝描述进行处理
 输入参数  : NAS_MMC_GU_ACTION_RSLT_INFO_STRU   *pstGuActionRslt
 输出参数  : 无
 返 回 值  : VOS_OK : ID_MMC_LMM_ACTION_RESULT_REQ 消息发送成功
             VOS_ERR: ID_MMC_LMM_ACTION_RESULT_REQ 消息发送失败
 调用函数  : NAS_MMC_FormatProcTypeToLmm
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2011年11月28日
    作    者   : z00161729
    修改内容   : MMC与LMM消息交互采用内部消息队列，为保证PC上GTR功能已有用例可以正常使用，
                 在PC上MMC、GMM和LMM的交互还使用外部消息，发送消息函数需要用宏NAS_STUB隔开
  3.日    期   : 2012年7月13日
    作    者   : s00217060
    修改内容   : for sync lmm cs state:在消息中增加CS update状态和Lai是否改变的标志

*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmRegActionResultReq(
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU   *pstGuActionRslt
)
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pstMsg = VOS_NULL_PTR;
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnRejCause;
    MMC_LMM_DOMAIN_ENUM_UINT32          enLmmDomain;
    MMC_LMM_ACTION_TYPE_ENUM_UINT32     enActionType;

    /* 判断Action类型是否正确 */
    if ( VOS_OK != NAS_MMC_FormatProcTypeToLmm(pstGuActionRslt->enProcType, &enActionType))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmRegActionResultReq():NAS_MMC_FormatProcTypeToLmm:RETURNS FAILURE");

        return;
    }

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_ACTION_RESULT_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
         sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_ACTION_RESULT_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU));
#endif

    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmRegActionResultReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    /* 初始化内存 */
    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                         sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ucCnCause = NAS_EMM_CAUSE_BUTT;


    /* 填充消息发送内容 */
    pstMsg->ulReceiverCpuId                 = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid                   = PS_PID_MM;
    pstMsg->ulSenderCpuId                   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                     = WUEPS_PID_MMC;
    pstMsg->ulLength                        = sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                         = ID_MMC_LMM_ACTION_RESULT_REQ;

    pstMsg->ulOpId                          = 0;
    pstMsg->bitOpAtmpCnt                    = VOS_TRUE;

    pstMsg->ulAttemptCount                  = pstGuActionRslt->ulAttemptCount;
    pstMsg->ulMtDetachType                  = MMC_LMM_MT_DETACH_TYPE_BUTT;
    pstMsg->enActionType                    = enActionType;

    /* 获取注册结果 */
    NAS_MMC_ConvertGuRsltToLmmFormat(pstGuActionRslt->enRegRst,
                                     pstGuActionRslt->enCnCause,
                                     &(pstMsg->ulActRst));


    /* 获取注册原因值 */
    if ( VOS_OK == NAS_MMC_ConvertMmCauseToEmmCause(pstGuActionRslt->enCnCause, &enCnRejCause) )
    {
        pstMsg->bitOpCnCause                = VOS_TRUE;
        pstMsg->ucCnCause                   = enCnRejCause;
    }

    if ( VOS_OK == NAS_MMC_ConverCnDomainToLmm(pstGuActionRslt->enReqDomain, &enLmmDomain) )
    {
        pstMsg->bitOpReqDomain              = VOS_TRUE;
        pstMsg->ulReqDomain                 = enLmmDomain;
    }

    if ( VOS_OK == NAS_MMC_ConverCnDomainToLmm(pstGuActionRslt->enRstDomain, &enLmmDomain) )
    {
        pstMsg->bitOpRstDomain              = VOS_TRUE;
        pstMsg->ulRstDomain                 = enLmmDomain;
    }

    /* 填充CS update状态和Lai是否改变标志 */
    NAS_MMC_FillCsRegInfoInLmmActionRslt(pstMsg);

    /* 填充PS update状态和Rai是否改变标志 */
    NAS_MMC_FillGprsRegInfoInLmmActionRslt(pstMsg);

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmRegActionResultReq():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmRelReq
 功能描述  : 向LMM发送链路释放请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2011年11月28日
    作    者   : z00161729
    修改内容   : MMC与LMM消息交互采用内部消息队列，为保证PC上GTR功能已有用例可以正常使用，
                 在PC上MMC、GMM和LMM的交互还使用外部消息，发送消息函数需要用宏NAS_STUB隔开
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmRelReq( VOS_VOID )
{
    /* 定义原语类型指针 */
    MMC_LMM_REL_REQ_STRU               *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_REL_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_REL_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_REL_REQ_STRU));
#endif

    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmRelReq,ERROR:ALLOC MEM ERROR!");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                         sizeof(MMC_LMM_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_REL_REQ;
    pstMsg->ulOpId                      = 0;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmRelReq,ERROR:SNED MSG FAIL!");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmAttachReq
 功能描述  : 向LMM发送注册请求
 输入参数  : ulAttachType:Attach类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月11日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2011年8月11日
   作    者   : W00167002
   修改内容   : 增加消息长度的赋值
 3.日    期   : 2011年11月28日
   作    者   : z00161729
   修改内容   : MMC与LMM消息交互采用内部消息队列，为保证PC上GTR功能已有用例可以正常使用，
                在PC上MMC、GMM和LMM的交互还使用外部消息，发送消息函数需要用宏NAS_STUB隔开

*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmAttachReq(
    VOS_UINT32                                              ulOpId,
    VOS_UINT32                                              ulAttachType,
    NAS_MSCC_PIF_EPS_ATTACH_REASON_ENUM_UINT32              enEpsAttachReason
)
{
    /* 定义原语类型指针 */
    MMC_LMM_ATTACH_REQ_STRU            *pstMsg = VOS_NULL_PTR;

    MMC_LMM_ATT_REQ_TYPE_ENUM_UINT32    enAttachType;

    if ( VOS_OK != NAS_MMC_ConvertAttachTypeToLmm(ulAttachType, &enAttachType) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmAttachReq():NAS_MMC_ConvertAttachTypeToLmm:RETURNS FAILURE");

        return;
    }

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_ATTACH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_ATTACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_ATTACH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_ATTACH_REQ_STRU));
#endif

    if( VOS_NULL_PTR == pstMsg )
    {
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                    sizeof(MMC_LMM_ATTACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_ATTACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_ATTACH_REQ;
    pstMsg->ulOpId                      = ulOpId;
    pstMsg->ulAttachType                = enAttachType;

    /* Added by s00246516 for L-C互操作项目, 2014-02-14, Begin */
    pstMsg->ulAttachReason              = enEpsAttachReason;
    /* Added by s00246516 for L-C互操作项目, 2014-02-14, End */

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmAttachReq():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmDetachReq
 功能描述  : 向LMM发送去注册请求
 输入参数  : ulDetachType:detach类型
 输出参数  : 无
 返 回 值  : VOS_OK : ID_MMC_LMM_DETACH_REQ 消息发送成功
             VOS_ERR: ID_MMC_LMM_DETACH_REQ 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月11日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2011年8月11日
   作    者   : W00167002
   修改内容   : 增加消息长度的赋值
 3.日    期   : 2011年11月28日
   作    者   : z00161729
   修改内容   : MMC与LMM消息交互采用内部消息队列，为保证PC上GTR功能已有用例可以正常使用，
                在PC上MMC、GMM和LMM的交互还使用外部消息，发送消息函数需要用宏NAS_STUB隔开
 4.日    期   : 2014年2月13日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加异系统到HRPD的处理
 5.日    期   : 2015年4月11日
   作    者   : y00245242
   修改内容   : iteration 13开发
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmDetachReq(
    VOS_UINT32                                              ulOpId,
    VOS_UINT32                                              ulDetachType,
    NAS_MSCC_PIF_DETACH_REASON_ENUM_UINT32                  enDetachReason
)
{
    /* 定义原语类型指针 */
    MMC_LMM_DETACH_REQ_STRU            *pstMsg = VOS_NULL_PTR;
    MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32  enLmmDetachType;

    if ( VOS_OK != NAS_MMC_ConvertDetachTypeToLmm(ulDetachType, &enLmmDetachType) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmDetachReq():NAS_MMC_ConvertDetachTypeToLmm:RETURNS FAILURE");

        return;
    }

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_DETACH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_DETACH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_DETACH_REQ_STRU));
#endif

    if( VOS_NULL_PTR == pstMsg )
    {
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                         sizeof(MMC_LMM_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_DETACH_REQ;
    pstMsg->ulOpId                      = ulOpId;
    pstMsg->ulDetachType                = enLmmDetachType;

    /* Added by s00246516 for L-C互操作项目, 2014-02-14, Begin */
    if (NAS_MSCC_PIF_DETACH_REASON_3GPP2_ATTACHED == enDetachReason)
    {
        pstMsg->ulDetachReason = MMC_LMM_DETACH_RESEAON_NON_3GPP_ATTACH;
    }
    else
    {
        pstMsg->ulDetachReason = MMC_LMM_DETACH_RESEAON_NULL;
    }
    /* Added by s00246516 for L-C互操作项目, 2014-02-14, End */

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmDetachReq():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmResumeNotify
 功能描述  : 向LMM发送挂起恢复通知
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK : ID_MMC_LMM_RESUME_NOTIFY 消息发送成功
             VOS_ERR: ID_MMC_LMM_RESUME_NOTIFY 消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月12日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数
 2.日    期   : 2011年8月11日
   作    者   : W00167002
   修改内容   : 增加消息长度的赋值
 3.日    期   : 2011年11月28日
   作    者   : z00161729
   修改内容   : MMC与LMM消息交互采用内部消息队列，为保证PC上GTR功能已有用例可以正常使用，
                在PC上MMC、GMM和LMM的交互还使用外部消息，发送消息函数需要用宏NAS_STUB隔开

*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmResumeNotify( VOS_VOID )
{
    /* 定义原语类型指针 */
    MMC_LMM_RESUME_NOTIFY_STRU         *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_RESUME_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_RESUME_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_RESUME_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_RESUME_NOTIFY_STRU));
#endif

    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmResumeNotify():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                         sizeof(MMC_LMM_RESUME_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_RESUME_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_RESUME_NOTIFY;
    pstMsg->ulOpId                      = 0;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmResumeNotify():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmSuspendRsp
 功能描述  : 向LMM发送挂起回复消息
 输入参数  : ulRst:挂起结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月12日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2011年11月28日
    作    者   : z00161729
    修改内容   : MMC与LMM消息交互采用内部消息队列，为保证PC上GTR功能已有用例可以正常使用，
                 在PC上MMC、GMM和LMM的交互还使用外部消息，发送消息函数需要用宏NAS_STUB隔开

*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmSuspendRsp(
    VOS_UINT32                          ulRst
)
{
    /* 定义原语类型指针 */
    MMC_LMM_SUSPEND_RSP_STRU           *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_SUSPEND_RSP_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_SUSPEND_RSP_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_SUSPEND_RSP_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_SUSPEND_RSP_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmSuspendRsp():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                         sizeof(MMC_LMM_SUSPEND_RSP_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_SUSPEND_RSP_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_SUSPEND_RSP;
    pstMsg->ulOpId                      = 0;
    pstMsg->ulRst                       = ulRst;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmSuspendRsp():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : NAS_MMC_SetRatPriorityInCLMode
 功能描述  : 设置CL模式下的RAT优先级
 输入参数  : pstRatOrderList -- RAT order list
             pstPriorityList -- RAT优先级list
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

修改历史      :
 1.日    期   : 2015年5月5日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetRatPriorityInCLMode(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatOrderList,
    RRMM_RAT_PRIO_ENUM_UINT8           *pstPriorityList
)
{
    VOS_UINT32                          ucHrpdRatSupp;

    ucHrpdRatSupp = NAS_MML_IsSpecRatInRatList(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD, pstRatOrderList);

    if ((VOS_TRUE == NAS_MML_IsSpecRatInRatList(NAS_MSCC_PIF_NET_RAT_TYPE_1X, pstRatOrderList))
     || (VOS_TRUE == ucHrpdRatSupp))
    {
        /* 对于CL模式，如果有LTE，设置LTE为HIGH，避免会出现重复low或middle场景 */
        if (VOS_TRUE == NAS_MML_IsSpecRatInRatList(NAS_MSCC_PIF_NET_RAT_TYPE_LTE, pstRatOrderList))
        {
            *(pstPriorityList + NAS_MSCC_PIF_NET_RAT_TYPE_LTE) = RRMM_RAT_PRIO_HIGH;
        }
        else
        {
            *(pstPriorityList + NAS_MSCC_PIF_NET_RAT_TYPE_LTE) = RRMM_RAT_PRIO_NULL;
        }

        if (VOS_TRUE == NAS_MML_IsSpecRatInRatList(NAS_MSCC_PIF_NET_RAT_TYPE_1X, pstRatOrderList))
        {
            *(pstPriorityList + NAS_MSCC_PIF_NET_RAT_TYPE_1X) = RRMM_RAT_PRIO_LOW;
        }
        else
        {
            *(pstPriorityList + NAS_MSCC_PIF_NET_RAT_TYPE_1X) = RRMM_RAT_PRIO_NULL;
        }

        if (VOS_TRUE == ucHrpdRatSupp)
        {
            *(pstPriorityList + NAS_MSCC_PIF_NET_RAT_TYPE_HRPD) = RRMM_RAT_PRIO_MIDDLE;
        }
        else
        {
            *(pstPriorityList + NAS_MSCC_PIF_NET_RAT_TYPE_HRPD) = RRMM_RAT_PRIO_NULL;
        }
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmC2LInterSysStartNtf
 功能描述  : 向LMM发送CL异系统开始指示
 输入参数  : enSuspendCause
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月27日
    作    者   : y00346957
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmCLInterSysStartNtf(
    MMC_LMM_SYS_CHNG_TYPE_ENUM_UINT32                       enSuspendCause
)
{
     MMC_LMM_CL_INTERSYS_START_NTF_STRU                   *pstMmcLmmCLInterSysStartNtf = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstMmcLmmCLInterSysStartNtf = (MMC_LMM_CL_INTERSYS_START_NTF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_CL_INTERSYS_START_NTF_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMmcLmmCLInterSysStartNtf = (MMC_LMM_CL_INTERSYS_START_NTF_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_CL_INTERSYS_START_NTF_STRU));
#endif

    /* 若分配内存出错,返回*/
    if ( VOS_NULL_PTR == pstMmcLmmCLInterSysStartNtf )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmCLInterSysStartNtf():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMmcLmmCLInterSysStartNtf + VOS_MSG_HEAD_LENGTH, 0X0,
               sizeof(MMC_LMM_CL_INTERSYS_START_NTF_STRU) - VOS_MSG_HEAD_LENGTH );

    pstMmcLmmCLInterSysStartNtf->ulReceiverPid   = PS_PID_MM;
    pstMmcLmmCLInterSysStartNtf->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMmcLmmCLInterSysStartNtf->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMmcLmmCLInterSysStartNtf->ulSenderPid     = WUEPS_PID_MMC;
    pstMmcLmmCLInterSysStartNtf->ulMsgId         = ID_MMC_LMM_CL_INTERSYS_START_NTF;
    pstMmcLmmCLInterSysStartNtf->ulLength        = sizeof(MMC_LMM_CL_INTERSYS_START_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMmcLmmCLInterSysStartNtf->ulOpId          = 0;

    pstMmcLmmCLInterSysStartNtf->enSuspendCause  = enSuspendCause;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMmcLmmCLInterSysStartNtf ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmCLInterSysStartNtf():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMmcLmmCLInterSysStartNtf);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMmcLmmCLInterSysStartNtf);
#endif

    return;
}

#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmSyscfgReq
 功能描述  : 向LMM发送SYSCFG设置消息
 输入参数  : MMA_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgMsg,用户设置的SYSCFG消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月5日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年11月28日
    作    者   : z00161729
    修改内容   : MMC与LMM消息交互采用内部消息队列，为保证PC上GTR功能已有用例可以正常使用，
                 在PC上MMC、GMM和LMM的交互还使用外部消息，发送消息函数需要用宏NAS_STUB隔开
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  4.日    期   : 2015年4月15日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
VOS_VOID  NAS_MMC_SndLmmSyscfgReq(
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgSetParm
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU          stRatList;

    /* 定义原语类型指针 */
    MMC_LMM_SYS_CFG_REQ_STRU           *pstSndLmmSysCfgMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulIsCLModeFlg;

    PS_MEM_SET(&stRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstSndLmmSysCfgMsg = (MMC_LMM_SYS_CFG_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_SYS_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstSndLmmSysCfgMsg = (MMC_LMM_SYS_CFG_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_SYS_CFG_REQ_STRU));
#endif

    if( VOS_NULL_PTR == pstSndLmmSysCfgMsg )
    {
        /* 内存申请失败 */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmSyscfgReq,ERRORALLOC MEM MMC_LMM_SYS_CFG_REQ_STRU FAIL");
        return ;
    }

    PS_MEM_SET( (VOS_INT8*)pstSndLmmSysCfgMsg + VOS_MSG_HEAD_LENGTH, 0X0,
                sizeof(MMC_LMM_SYS_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH );

    pstSndLmmSysCfgMsg->ulReceiverCpuId                 = VOS_LOCAL_CPUID;
    pstSndLmmSysCfgMsg->ulSenderCpuId                   = VOS_LOCAL_CPUID;
    pstSndLmmSysCfgMsg->ulSenderPid                     = WUEPS_PID_MMC;
    pstSndLmmSysCfgMsg->ulReceiverPid                   = PS_PID_MM;
    pstSndLmmSysCfgMsg->ulLength                        = sizeof(MMC_LMM_SYS_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndLmmSysCfgMsg->ulMsgId                         = ID_MMC_LMM_SYS_CFG_REQ;
    pstSndLmmSysCfgMsg->ulOpId                          = 0;

    /* 设置OPT为VOS_TRUE */
    pstSndLmmSysCfgMsg->bitOpBand                       = VOS_TRUE;
    pstSndLmmSysCfgMsg->bitOpRat                        = VOS_TRUE;

    /* 设置频段信息 */
    PS_MEM_CPY( &(pstSndLmmSysCfgMsg->stBand.stLteBand ),
                &(pstSysCfgSetParm->stBand.stLteBand),
                sizeof(LTE_BAND_STRU) );

    pstSndLmmSysCfgMsg->stBand.stWcdmaBand.ulWcdmaBand = pstSysCfgSetParm->stBand.unWcdmaBand.ulBand;
    pstSndLmmSysCfgMsg->stBand.stGsmBand.ulGsmBand     = pstSysCfgSetParm->stBand.unGsmBand.ulBand;

    pstSndLmmSysCfgMsg->stBand.stCdmaBand.ulCdmaBand   = pstSysCfgSetParm->stBand.unCdmaBand.ulCdmaBand;
    /* 设置接入模式 */
    PS_MEM_CPY(&stRatList, &(pstSysCfgSetParm->stRatPrioList), sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
    pstSndLmmSysCfgMsg->aucRatPrioList[0]              = NAS_MMC_GetSpecRatPrio(NAS_MML_NET_RAT_TYPE_GSM, &stRatList);
    pstSndLmmSysCfgMsg->aucRatPrioList[1]              = NAS_MMC_GetSpecRatPrio(NAS_MML_NET_RAT_TYPE_WCDMA, &stRatList);
    pstSndLmmSysCfgMsg->aucRatPrioList[2]              = NAS_MMC_GetSpecRatPrio(NAS_MML_NET_RAT_TYPE_LTE, &stRatList);

    ulIsCLModeFlg = NAS_MML_IsCLModeSupportedInRatList(&(pstSysCfgSetParm->stRatPrioList));

    if (VOS_TRUE == ulIsCLModeFlg)
    {
        pstSndLmmSysCfgMsg->enUtranMode = MMC_LMM_UTRAN_MODE_NULL;
    }
    else
    {
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
        if (VOS_TRUE == NAS_MML_IsGULModeConfigured())
        {
            pstSndLmmSysCfgMsg->enUtranMode = NAS_UTRANCTRL_ConvertNasUtranModeToLmmUtranMode(NAS_UTRANCTRL_GetPreUtranMode());
        }
        else
        {
            pstSndLmmSysCfgMsg->enUtranMode = NAS_UTRANCTRL_ConvertNasUtranModeToLmmUtranMode(NAS_UTRANCTRL_GetCurrUtranMode());
        }
#else
        pstSndLmmSysCfgMsg->enUtranMode = MMC_LMM_UTRAN_MODE_FDD;
#endif

    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* 如果CDMA支持，如果是CL模式下，需要重新修改RAT优先级 */
    NAS_MMC_SetRatPriorityInCLMode(&stRatList, &pstSndLmmSysCfgMsg->aucRatPrioList[0]);
#endif

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstSndLmmSysCfgMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndRrMmCellSelReq():ERROR:SEND MESSAGE FAILURE");
        return ;
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstSndLmmSysCfgMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstSndLmmSysCfgMsg);
#endif

    return ;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmDisableLteNotify
 功能描述  : 向LMM发送disable LTE通知
 输入参数  : enDisableLteReason:Disable LTE在的原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月1日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年7月27日
    作    者   : s00217060
    修改内容   : for CS/PS mode 1, 上报服务状态时，带Disable LTE原因值
*****************************************************************************/
VOS_VOID  NAS_MMC_SndLmmDisableLteNotify(
    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32                  enDisableLteReason
)
{
    /* 定义原语类型指针 */
    MMC_LMM_DISABLE_LTE_NOTIFY_STRU    *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_DISABLE_LTE_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_DISABLE_LTE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_DISABLE_LTE_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_DISABLE_LTE_NOTIFY_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmDisableLteNotify():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                         sizeof(MMC_LMM_DISABLE_LTE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 构造发送消息 */
    pstMsg->ulReceiverCpuId                 = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid                   = PS_PID_MM;
    pstMsg->ulSenderCpuId                   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                     = WUEPS_PID_MMC;
    pstMsg->ulLength                        = sizeof(MMC_LMM_DISABLE_LTE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                         = ID_MMC_LMM_DISABLE_LTE_NOTIFY;
    pstMsg->ulOpId                          = 0;
    pstMsg->enDisableLteReason              = enDisableLteReason;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmDisableLteNotify():WARNING:SEND LMM disable lte notify FIAL");
        return;
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmEnableLteNotify
 功能描述  : 向LMM发送enable LTE通知
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月1日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_MMC_SndLmmEnableLteNotify(VOS_VOID)
{
    /* 定义原语类型指针 */
    MMC_LMM_ENABLE_LTE_NOTIFY_STRU     *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_ENABLE_LTE_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_ENABLE_LTE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_ENABLE_LTE_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_ENABLE_LTE_NOTIFY_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmEnableLteNotify():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                         sizeof(MMC_LMM_ENABLE_LTE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 构造发送消息 */
    pstMsg->ulReceiverCpuId                 = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid                   = PS_PID_MM;
    pstMsg->ulSenderCpuId                   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                     = WUEPS_PID_MMC;
    pstMsg->ulLength                        = sizeof(MMC_LMM_ENABLE_LTE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                         = ID_MMC_LMM_ENABLE_LTE_NOTIFY;
    pstMsg->ulOpId                          = 0;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmEnableLteNotify():WARNING:SEND LMM enbale lte notify FIAL");
        return;
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmConnStatusNotify
 功能描述  : MMC向LMM发送ID_MMC_LMM_CONN_STATUS_NOTIFY消息
 输入参数  : enSrvccStatus---SRVCC的状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月14日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmCsConnStatusNotify(
    VOS_UINT8                           ucCsRrConnStatusFlg,
    VOS_UINT8                           ucCsEmergencyConnStatusFlg
)
{
    MMC_LMM_CS_CONN_STATUS_NOTIFY_STRU *pstMsg = VOS_NULL_PTR;

#if (VOS_WIN32 == VOS_OS_VER)

    /* 申请内存 */
    pstMsg = (MMC_LMM_CS_CONN_STATUS_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_CS_CONN_STATUS_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_CS_CONN_STATUS_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_CS_CONN_STATUS_NOTIFY_STRU));
#endif

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MMC_SndLmmConnStatusNotify():ERROR:MALLOC MEMORY FAILURE");
        return ;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                    sizeof(MMC_LMM_CS_CONN_STATUS_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_CS_CONN_STATUS_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_CS_CONN_STATUS_NOTIFY;
    pstMsg->ulOpId                      = 0;
    pstMsg->ucCsRrConnStatusFlg         = ucCsRrConnStatusFlg;
    pstMsg->ucCsEmergencyConnStatusFlg  = ucCsEmergencyConnStatusFlg;


#if (VOS_WIN32 == VOS_OS_VER)

    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MM, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmConnStatusNotify():ERROR:SEND MESSAGE FAILURE");
        return ;
    }
#else

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);

#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_FormatProcTypeToLmm
 功能描述  : 将内部定义的过程类型转换为发送给LMM的类型
 输入参数  : enProcType:内部的过程类型
 输出参数  : penSerType:LMM的过程类型
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月9日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年3月1日
    作    者   : w00176964
    修改内容   : DTS2012022407450:增加联合注册类型
  3.日    期   : 2012年7月12日
    作    者   : s00217060
    修改内容   : for sync lmm cs state:增加MM Abort类型转换s
  4.日    期   : 2013年3月30日
    作    者   : w00176964
    修改内容   : DTS2013030802929,周期性RAU需要通知LMM

*****************************************************************************/
VOS_UINT32  NAS_MMC_FormatProcTypeToLmm(
    NAS_MML_PROC_TYPE_ENUM_U32          enProcType,
    MMC_LMM_ACTION_TYPE_ENUM_UINT32    *penActionType
)
{
    switch (enProcType)
    {
        case NAS_MML_PROC_ATTACH:
        case NAS_MML_PROC_COMBINED_ATTACH:
            *penActionType = MMC_LMM_ACTION_ATTACH;
            break;

        case NAS_MML_PROC_MT_DETACH:
            *penActionType = MMC_LMM_ACTION_MT_DETACH;
            break;

        case NAS_MML_PROC_LOCAL_DETACH:
           *penActionType = MMC_LMM_ACTION_LOCAL_DETACH;
           break;

        case NAS_MML_PROC_UE_DETACH:
            *penActionType = MMC_LMM_ACTION_MO_DETACH;
             break;

        case NAS_MML_PROC_RAU:
        case NAS_MML_PROC_COMBINED_RAU:
            *penActionType = MMC_LMM_ACTION_RAU;

            break;

        case NAS_MML_PROC_PERIODC_RAU:
            *penActionType = MMC_LMM_ACTION_PERIODC_RAU;
            break;


        case NAS_MML_PROC_LAU:
            *penActionType = MMC_LMM_ACTION_LAU;
            break;

        case NAS_MML_PROC_SER:
            *penActionType = MMC_LMM_ACTION_PS_SERVICE_REQ;
            break;

        case NAS_MML_PROC_CM_SER:
            *penActionType = MMC_LMM_ACTION_CM_REQ;
            break;

        /* 新增Abort类型转换 */
        case NAS_MML_PROC_MM_ABORT:
            *penActionType = MMC_LMM_ACTION_MM_ABORT;
            break;

        default:
            return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertAttachTypeToLmm
 功能描述  : 将attach type转换为LMM的类型
 输入参数  : ulAttachType:gu模的ATTACH类型
 输出参数  : penLmmAttachType:LMM的ATTACH类型
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月12日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
 2.日    期   : 2011年4月12日
   作    者   : w00176964
   修改内容   : V7R1 PhaseIV调整:UE attach类型结构变更
 3.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_UINT32  NAS_MMC_ConvertAttachTypeToLmm(
    VOS_UINT32                          ulAttachType,
    MMC_LMM_ATT_REQ_TYPE_ENUM_UINT32   *penLmmAttachType
)
{
    switch (ulAttachType)
    {
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
        case NAS_MSCC_PIF_ATTACH_TYPE_GPRS:
            *penLmmAttachType = MMC_LMM_ATT_REQ_TYPE_PS_ONLY;
            break;

        case NAS_MSCC_PIF_ATTACH_TYPE_GPRS_IMSI:
            *penLmmAttachType = MMC_LMM_ATT_REQ_TYPE_CS_PS;
            break;

        case NAS_MSCC_PIF_ATTACH_TYPE_IMSI:
            *penLmmAttachType = MMC_LMM_ATT_REQ_TYPE_CS_ONLY;
            break;

        default:
            return VOS_ERR;
       /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertLmmPlmnToGUNasFormat
 功能描述  : 将LMM的3字节格式PLMN转换为MCC和MNC分开的格式
 输入参数  : pLMMPlmn
 输出参数  : pGUNasPlmn
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月28日
    作    者   : likelai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_ConvertLmmPlmnToGUNasFormat(
    MMC_LMM_PLMN_ID_STRU               *pstLMMPlmn,
    NAS_MML_PLMN_ID_STRU               *pstGUNasPlmn
)
{
    NAS_MML_SIM_FORMAT_PLMN_ID          stSimPlmn;

    PS_MEM_SET(&stSimPlmn, 0, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));

    /* 先转换为SIM格式 */
    PS_MEM_CPY(stSimPlmn.aucSimPlmn, pstLMMPlmn->aucPlmnId, sizeof(pstLMMPlmn->aucPlmnId));

    NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, pstGUNasPlmn);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertLmmPlmnToGUNasPlmn
 功能描述  : 将指定个数的LMM的PLMN转换为GUnas格式的plmn
 输入参数  : VOS_UINT32                          ulLmmPlmnNum
              MMC_LMM_PLMN_ID_STRU               *pstLmmPlmn
              MMC_PLMN_ID_STRU                   *pstGUNasPlmn
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月12日
    作    者   : W00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertLmmPlmnToGUNasPlmn(
    VOS_UINT32                          ulLmmPlmnNum,
    MMC_LMM_PLMN_ID_STRU               *pstLmmPlmn,
    NAS_MML_PLMN_ID_STRU               *pstGUNasPlmn
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < ulLmmPlmnNum ; i++  )
    {
        NAS_MMC_ConvertLmmPlmnToGUNasFormat( &(pstLmmPlmn[i]), &(pstGUNasPlmn[i]) );
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertDetachCauseToLmm
 功能描述  : 将detach Cause转换为LMM的类型
 输入参数  : ulDetachType:DETACH 类型
 输出参数  : penLmmDetachType:LMM的DETACH类型
 返 回 值  : 返回成功VOS_OK 或者失败VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月12日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

 2.日    期   : 2011年7月14日
   作    者   : w00167002
   修改内容   : TAF_MMC_PS_CS_DETACH类型重复，更改为TAF_MMC_CS_DETACH
 3.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_UINT32  NAS_MMC_ConvertDetachTypeToLmm(
    VOS_UINT32                          ulDetachType,
    MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32 *penLmmDetachType
)
{
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    if ( NAS_MSCC_PIF_DETACH_TYPE_GPRS          == ulDetachType )
    {
        *penLmmDetachType = MMC_LMM_MO_DET_PS_ONLY;
    }
    else if ( NAS_MSCC_PIF_DETACH_TYPE_GPRS_IMSI  == ulDetachType )
    {
        *penLmmDetachType = MMC_LMM_MO_DET_CS_PS;
    }
    else if ( NAS_MSCC_PIF_DETACH_TYPE_IMSI  == ulDetachType )
    {
        *penLmmDetachType = MMC_LMM_MO_DET_CS_ONLY;
    }
    else
    {
        return VOS_ERR;
    }
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetTinTypeToLmm
 功能描述  : 获取TIN类型给LMM
 输入参数  : 无
 输出参数  : penTinType:LMM的TIN类型
 返 回 值  : VOS_OK:获取成功,VOS_ERR:获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月28日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetTinTypeToLmm(
    MMC_LMM_TIN_TYPE_ENUM_UINT32        *penTinType
)
{
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    enTinType = NAS_MML_GetTinType();
    if ( NAS_MML_TIN_TYPE_GUTI == enTinType )
    {
        *penTinType = MMC_LMM_TIN_GUTI;
    }
    else if ( NAS_MML_TIN_TYPE_PTMSI == enTinType )
    {
        *penTinType = MMC_LMM_TIN_P_TMSI;
    }
    else if ( NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType )
    {
        *penTinType = MMC_LMM_TIN_RAT_RELATED_TMSI;
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetEplmnToLmm
 功能描述  : 获取EPLMN通知LMM
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK:获取成功,VOS_ERR:获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月28日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetEplmnToLmm(
    MMC_LMM_EPLMN_STRU                  *pstEplmnList
)
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstGuEplmnAddr;
    VOS_UINT32                          i;

    pstGuEplmnAddr          = NAS_MML_GetEquPlmnList();
    pstEplmnList->ulPlmnNum = pstGuEplmnAddr->ucEquPlmnNum;

    for ( i = 0 ; i <  pstEplmnList->ulPlmnNum; i++ )
    {
        NAS_MML_ConvertNasPlmnToLMMFormat(&(pstEplmnList->astEplmnList[i]),
                                          &(pstGuEplmnAddr->astEquPlmnAddr[i]));
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetFplmnToLmm
 功能描述  : 获取FPLMN通知LMM
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK:获取成功,VOS_ERR:获取失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月28日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetFplmnToLmm(
    MMC_LMM_PLMN_LIST_STRU              *pstFplmnList
)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo;
    VOS_UINT8                           ucFplmnNum;
    VOS_UINT32                          i;

    pstForbidPlmnInfo       = NAS_MML_GetForbidPlmnInfo();
    ucFplmnNum              = pstForbidPlmnInfo->ucForbPlmnNum;
    pstFplmnList->ulPlmnNum = ucFplmnNum;

    for ( i = 0 ; i <  ucFplmnNum; i++ )
    {
        NAS_MML_ConvertNasPlmnToLMMFormat(&(pstFplmnList->astPlmnId[i]),
                                          &(pstForbidPlmnInfo->astForbPlmnIdList[i]));
    }

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetFplmnForGprsToLmm
 功能描述  : 获取FPLMN for Gprs通知LMM
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK:获取成功,VOS_ERR:获取失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月28日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetFplmnForGprsToLmm(
    MMC_LMM_PLMN_LIST_STRU              *pstFplmnForGprsList
)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo;
    VOS_UINT8                           ucFplmnNum;
    VOS_UINT32                          i;

    pstForbidPlmnInfo       = NAS_MML_GetForbidPlmnInfo();
    ucFplmnNum              = pstForbidPlmnInfo->ucForbGprsPlmnNum;

    pstFplmnForGprsList->ulPlmnNum = ucFplmnNum;

    for ( i = 0 ; i <  ucFplmnNum; i++ )
    {
        NAS_MML_ConvertNasPlmnToLMMFormat(&(pstFplmnForGprsList->astPlmnId[i]),
                                          &(pstForbidPlmnInfo->astForbGprsPlmnList[i]));
    }

    return VOS_OK;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetEHplmnToLmm
 功能描述  : 获取EHPLMN通知LMM,EHPLMN不存在或不支持时，使用IMSI-derived Plmn
 输入参数  : 无
 输出参数  : pstEHplmnList:EHPLMN信息
 返 回 值  : VOS_OK:获取成功,VOS_ERR:获取失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月28日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数
 2.日    期   : 2012年6月28日
   作    者   : w00166186
   修改内容   : AT&T&DCM项目
*****************************************************************************/
VOS_UINT32  NAS_MMC_GetEHplmnToLmm(
    MMC_LMM_PLMN_LIST_STRU             *pstEHplmnList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulHplmnNum ;
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEhplmnInfo = VOS_NULL_PTR;

    pstEhplmnInfo = NAS_MML_GetSimEhplmnList();

    if (NAS_MML_HPLMN_TYPE_EHPLMN == NAS_MML_GetHPlmnType())
    {
        /* EHPLMN的实际个数 */
        ulHplmnNum   = pstEhplmnInfo->ucEhPlmnNum;

        pstEHplmnList->ulPlmnNum = ulHplmnNum;

        /* 转换为LMM需要的格式 */
        for ( i = 0 ; i < ulHplmnNum; i++ )
        {
            NAS_MML_ConvertNasPlmnToLMMFormat(&(pstEHplmnList->astPlmnId[i]),
                                              &(pstEhplmnInfo->astEhPlmnInfo[i].stPlmnId));
        }
    }
    else
    {
        pstEHplmnList->ulPlmnNum = 0;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetHplmnToLmm
 功能描述  : 获取HPLMN通知LMM
 输入参数  : 无
 输出参数  : pstHplmn:HPLMN信息
 返 回 值  : VOS_OK:获取成功,VOS_ERR:获取失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月20日
   作    者   : w00166186
   修改内容   : AT&T&DCM项目

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetHplmnToLmm(
    MMC_LMM_PLMN_ID_STRU               *pstHplmn
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEHPlmnInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stPlmnId;
    NAS_MML_HPLMN_TYPE_ENUM_UINT8       enHplmnType;

    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity   = VOS_NULL_PTR;

    pstMsIdentity                       = NAS_MML_GetSimMsIdentity();

    enHplmnType   = NAS_MML_GetHPlmnType();
    pstEHPlmnInfo = NAS_MML_GetSimEhplmnList();

    /* 当前HPLMN类型为HPLMN或者ACTING-HPLMN */
    if ((NAS_MML_HPLMN_TYPE_HPLMN == enHplmnType)
     || (NAS_MML_HPLMN_TYPE_ACTING_HPLMN == enHplmnType))
    {
        /* 赋值HPLMN */
        stPlmnId = pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId;
    }
    /* 当前HPLMN类型为EHPLMN */
    else if (NAS_MML_HPLMN_TYPE_EHPLMN == enHplmnType)
    {
        /* 赋值HPLMN */
        stPlmnId = NAS_MML_GetImsiHomePlmn(pstMsIdentity->aucImsi);
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsHplmnReq(): HPLMN TYPE ERROR");
        return VOS_ERR;
    }

    NAS_MML_ConvertNasPlmnToLMMFormat(pstHplmn, &stPlmnId);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : Nas_GetPubInfo
 功能描述  : L调用接口获取GU模信息
 输入参数  : ulInfoType:L需获取的信息
 输出参数  : pstPubInfo:GU提供的信息
 返 回 值  : VOS_OK:获取成功,VOS_ERR:获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月28日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2012年6月20日
    作    者   : w00166186
    修改内容   : AT&T&DCM项目

*****************************************************************************/
MMC_LMM_RESULT_ID_ENUM_UINT32 Nas_GetPubInfo(
    MMC_LMM_INFO_TYPE_ENUM_UINT32       ulInfoType,
    MMC_LMM_PUB_INFO_STRU              *pstPubInfo
)
{
    VOS_UINT32                          ulRet;

    ulRet   = VOS_ERR;

    switch (ulInfoType)
    {
        case MMC_LMM_TIN_TYPE:
            ulRet = NAS_MMC_GetTinTypeToLmm(&(pstPubInfo->u.ulTinType));
            break;

        case MMC_LMM_EPLMN:
            ulRet = NAS_MMC_GetEplmnToLmm(&(pstPubInfo->u.stEplmnList));
            break;

        case MMC_LMM_FPLMN:
            ulRet = NAS_MMC_GetFplmnToLmm(&(pstPubInfo->u.stForbiddenPlmnList));
            break;

        case MMC_LMM_FPLMN_FOR_GPRS:
            ulRet = NAS_MMC_GetFplmnForGprsToLmm(&(pstPubInfo->u.stForbiddenPlmnListForGPRS));
            break;

        case MMC_LMM_EHPLMN:
            ulRet = NAS_MMC_GetEHplmnToLmm(&(pstPubInfo->u.stEHplmnList));
            break;

        case MMC_LMM_HPLMN:
            ulRet = NAS_MMC_GetHplmnToLmm(&(pstPubInfo->u.stHplmn));
            break;

        default:
            break;

    }

    if ( VOS_OK == ulRet )
    {
        return MMC_LMM_SUCC;
    }

    return MMC_LMM_FAIL;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_FillGprsRegInfoInLmmActionRslt
 功能描述  : 填充Gprs update状态和Rai是否改变标志
 输入参数  : pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年7月13日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_FillGprsRegInfoInLmmActionRslt(
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pstMsg
)
{
    /* 如果不携带ulAttemptCount，直接返回 */
    if (VOS_FALSE == pstMsg->bitOpAtmpCnt)
    {
        return;
    }

    /* 如果ulAttemptCount为0，直接返回 */
    if (0 == pstMsg->ulAttemptCount)
    {
        return;
    }

    /* 如果是联合RAU或联合ATTACH，ulCombReg为TRUE */
    if ((MMC_LMM_ACTION_RAU == pstMsg->enActionType)
     || (MMC_LMM_ACTION_ATTACH == pstMsg->enActionType))
    {
        /* 调用函数NAS_MML_GetPsUpdateStatus填充PS update状态 */
        pstMsg->bitOpGprsUpdateStatus = VOS_TRUE;
        pstMsg->ucGprsUpdateStatus    = NAS_MML_GetPsUpdateStatus();

        /* 调用函数NAS_MML_IsRaiChanged填充Rai是否改变标志 */
        pstMsg->bitOpRaiChangFlg      = VOS_TRUE;
        pstMsg->ucRaiChangFlg         = NAS_MML_IsRaiChanged();
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_FillCsRegInfoInLmmActionRslt
 功能描述  : 填充CS update状态和Lai是否改变标志
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年7月12日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_FillCsRegInfoInLmmActionRslt(
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo     = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstLastSuccLai  = VOS_NULL_PTR;
    VOS_UINT32                          ulCombReg;

    pstCampInfo    = NAS_MML_GetCurrCampPlmnInfo();
    pstLastSuccLai = NAS_MML_GetCsLastSuccLai();

    ulCombReg      = VOS_FALSE;

    /* 如果不带enReqDomain，直接返回 */
    if (VOS_FALSE == pstMsg->bitOpReqDomain)
    {
        return;
    }

    /* 如果不携带ulAttemptCount，直接返回 */
    if (VOS_FALSE == pstMsg->bitOpAtmpCnt)
    {
        return;
    }

    /* 如果ulAttemptCount为0，直接返回 */
    if (0 == pstMsg->ulAttemptCount)
    {
        return;
    }

    /* 如果是联合RAU或联合ATTACH，ulCombReg为TRUE */
    if ((MMC_LMM_ACTION_RAU == pstMsg->enActionType)
     || (MMC_LMM_ACTION_ATTACH == pstMsg->enActionType))
    {
        if (MMC_LMM_COMBINED_PS_IMSI == pstMsg->ulReqDomain)
        {
            ulCombReg = VOS_TRUE;
        }
    }

    /* 如果是LAU,联合RAU或联合ATTACH,填充CS update状态和Lai是否改变标志 */
    if ((MMC_LMM_ACTION_LAU == pstMsg->enActionType)
     || (VOS_TRUE == ulCombReg))
    {
        /* 调用函数NAS_MML_GetCsUpdateStatus填充CS update状态 */
        pstMsg->bitOpCsUpdateStatus = VOS_TRUE;
        pstMsg->ucCsUpdateStatus    = NAS_MML_GetCsUpdateStatus();

        /* 调用函数NAS_MML_CompareLai填充Lai是否改变标志 */
        pstMsg->bitOpLaiChangFlg    = VOS_TRUE;

        if (VOS_TRUE == NAS_MML_CompareLai(&(pstCampInfo->stLai), pstLastSuccLai))
        {
            pstMsg->ucLaiChangFlg = VOS_FALSE;
        }
        else
        {
            pstMsg->ucLaiChangFlg = VOS_TRUE;
        }
    }

    return;
}

/* Modified by s00246516 for L-C互操作项目, 2014-02-14, Begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_PlmnIdIsAllowRegManualMode
 功能描述  : 判断手动选网模式下网络是否允许注册
 输入参数  : pstPlmn:当前的PLMN信息
 输出参数  : 无
 返 回 值  : VOS_TRUE允许注册,
              VOS_FALSE:不允许注册
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月28日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加获取和注册请求的处理
*****************************************************************************/
VOS_UINT32 NAS_MMC_PlmnIdIsAllowRegManualMode(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnInfo  = VOS_NULL_PTR;
    VOS_UINT32                          ulIsUserPlmn;

    pstEplmnInfo = NAS_MML_GetEquPlmnList();

    pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

    ulIsUserPlmn = NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmnId, &(pstUserSpecPlmn->stPlmnId));

    /* 手动搜网模式下,判断该plmn是否为用户指定的PLMN */
    if ((NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
     && (VOS_FALSE == ulIsUserPlmn))
    {
        /* EPLMN无效 */
        if (VOS_FALSE == NAS_MML_GetEplmnValidFlg())
        {
            return VOS_FALSE;
        }

        /* 该PLMN不在EPLMN列表里 */
        if (VOS_FALSE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                                                pstEplmnInfo->ucEquPlmnNum,
                                                                pstEplmnInfo->astEquPlmnAddr))
        {
            return VOS_FALSE;
        }

        /* 用户指定搜网注册状态为 FALSE */
        if (VOS_FALSE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}
/* Modified by s00246516 for L-C互操作项目, 2014-02-14, end */

/*****************************************************************************
 函 数 名  : Nas_PlmnIdIsForbid
 功能描述  : L调用接口获取该PLMN是否被禁止
 输入参数  : pstPlmn:当前的PLMN信息
 输出参数  : 无
 返 回 值  : MMC_LMM_PLMN_ALLOW_REG允许注册,
              MMC_LMM_PLMN_NOT_ALLOW_REG:不允许注册
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月28日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2012年01月08日
    作    者   : w00176964
    修改内容   : DTS2013010703141:提供API给LNAS再任意驻留时判断是否需要发起注册
  3.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 根据卡类型禁止网络制式
  4.日    期   : 2014年2月14日
    作    者   : z00161729
    修改内容   : DTS2014021000537:sim卡anycell驻留l的小区mmc收到系统消息转给mma时应该将禁止网络标识置为TRUE，
                 不上报pstransfer:1,否则导致ps迁移到modem0后l不注册，乒乓ps迁移
  5.日    期   : 2014年1月28日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加获取和注册请求的处理
  6.日    期   : 2015年1月15日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
  7.日    期   : 2015年4月23日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
MMC_LMM_PLMN_CTRL_ENUM_UINT32  Nas_PlmnIdIsForbid(
    MMC_LMM_PLMN_ID_STRU                *pstPlmn
)
{
    /* Modified by s00246516 for L-C互操作项目, 2014-02-14, Begin */
    NAS_MML_PLMN_ID_STRU                                    stGuPlmnId;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo = VOS_NULL_PTR;
    VOS_UINT8                                               ucAsAnyCampOn;
    /* Modified by s00246516 for L-C互操作项目, 2014-02-14, End */

    /* 将PLMN ID进行转换 */
    NAS_MMC_ConvertLmmPlmnToGUNasFormat(pstPlmn, &stGuPlmnId);

    /* 先判断该Plmn是否有效 */
    if ( VOS_FALSE == NAS_MML_IsPlmnIdValid(&stGuPlmnId) )
    {
        return MMC_LMM_PLMN_CTRL_BUTT;
    }

    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        return MMC_LMM_PLMN_NOT_ALLOW_REG;
    }


    /* 当前plmn的MCC在禁止LTE国际漫游的MCC列表里,PLMN不允许发起注册 */
    if (VOS_TRUE == NAS_MMC_IsNeedDisableLteRoam(stGuPlmnId.ulMcc))
    {
        return MMC_LMM_PLMN_NOT_ALLOW_REG;
    }

    /* Modified by s00246516 for L-C互操作项目, 2014-02-14, Begin */
    ucAsAnyCampOn = NAS_MMC_GetAsAnyCampOn();

    /* 如果是3GPP2控制注册，当前L为限制驻留，不允许发起注册 */
    if ((NAS_MMC_REG_CONTROL_BY_3GPP_MMC != NAS_MMC_GetRegCtrl())
     && (VOS_TRUE == ucAsAnyCampOn))
    {
        return MMC_LMM_PLMN_NOT_ALLOW_REG;
    }

    if (VOS_FALSE == NAS_MMC_PlmnIdIsAllowRegManualMode(&stGuPlmnId))
    {
        return MMC_LMM_PLMN_NOT_ALLOW_REG;
    }
    /* Modified by s00246516 for L-C互操作项目, 2014-02-14, End */

    /* 该PLMN ID是否在锁网锁卡的PLMN 列表中 */
    if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInLockPlmnList(&stGuPlmnId))
    {
        return MMC_LMM_PLMN_NOT_ALLOW_REG;
    }

    /* 不允许漫游时 */
    if (VOS_FALSE == NAS_MML_IsPlmnIdRoamingAllowed(&stGuPlmnId))
    {
        return MMC_LMM_PLMN_NOT_ALLOW_REG;
    }


    /* 构造当前接入技术的PLMN ID */
    stPlmnWithRat.stPlmnId.ulMcc    = stGuPlmnId.ulMcc;
    stPlmnWithRat.stPlmnId.ulMnc    = stGuPlmnId.ulMnc;
    stPlmnWithRat.enRat             = NAS_MML_NET_RAT_TYPE_LTE;

    /* 判断当前PLMN是否在禁止RAT的PLMN列表中同时当前接入技术被禁止,则认为当前PLMN为禁止网络 */
    if (VOS_TRUE == NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
    {
        return MMC_LMM_PLMN_NOT_ALLOW_REG;
    }

    /* 判断PLMN的RAT在禁止接入技术列表中，则认为当前RAT对应网络为禁止网络 */
    if (VOS_TRUE == NAS_MML_IsRatInForbiddenList(stPlmnWithRat.enRat))
    {
        return MMC_LMM_PLMN_NOT_ALLOW_REG;
    }


    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    /* 在forbid plmn列表中 */
    if (VOS_TRUE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&stGuPlmnId,
                                                         pstForbidPlmnInfo->ucForbPlmnNum,
                                                         pstForbidPlmnInfo->astForbPlmnIdList))
    {
        return MMC_LMM_PLMN_NOT_ALLOW_REG;
    }

    if (VOS_TRUE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&stGuPlmnId,
                                                            pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                                            pstForbidPlmnInfo->astForbGprsPlmnList))
    {
        return MMC_LMM_PLMN_NOT_ALLOW_REG;
    }

    return MMC_LMM_PLMN_ALLOW_REG;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_BuildLmmSpecPlmnSearchReqMsg
 功能描述  : 构造通知Lmm指定搜网的消息体
 输入参数  : pstPlmnId, 指定搜网的PLMN ID
 输出参数  : pstMsg  返回构造消息体指针
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月19日
   作    者   : sunxibo 46746
   修改内容   : 新生成函数
 2.日    期   : 2011年12月15日
   作    者   : W00166186
   修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
 3.日    期   : 2014年3月19日
   作    者   : w00242748
   修改内容   : DTS2014031200137:当NV特性打开时，自动开机或者搜网时，如果首次搜索RPLMN的话，
                需要将HPLMN/EHPLMN带给接入层。
*****************************************************************************/
VOS_VOID NAS_MMC_BuildLmmSpecPlmnSearchReqMsg(
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg,
    NAS_MML_PLMN_LIST_WITH_RAT_STRU    *pstDestPlmnList,
    VOS_UINT32                          ulUserSpecFlag,
    VOS_UINT32                          ulPlmnSearchScene
)
{
    VOS_UINT32                          ulIndex;

    PS_MEM_SET((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                         sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId                 = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid                   = PS_PID_MM;
    /* 发送PID需要置上 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                        = sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                         = ID_MMC_LMM_PLMN_SRCH_REQ;
    pstMsg->ulOpId                          = 0;

    if (VOS_TRUE == ulUserSpecFlag)
    {
        pstMsg->enSrchType                      = MMC_LMM_PLMN_SRCH_USER_SPEC;
    }
    else
    {
        pstMsg->enSrchType                      = MMC_LMM_PLMN_SRCH_SPEC;
    }

    pstMsg->enPlmnSrchScene                 = MMC_LMM_PLMN_SEARCH_SCENE_NORMAL;

    if (NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_LTE_PLMN_SEARCH == ulPlmnSearchScene)
    {
        pstMsg->enPlmnSrchScene             = MMC_LMM_PLMN_SEARCH_SCENE_VIA_CL_BG_SEARCH;
    }

    pstMsg->bitOpSpecPlmn                   = VOS_TRUE;
    pstMsg->bitOpPlmnInfoCampFlg            = VOS_TRUE;
    pstMsg->enFftScanType                   = MMC_LMM_FFT_SCAN_TYPE_NONE;

    NAS_MML_ConvertNasPlmnToLMMFormat(&(pstMsg->stSpecPlmnId), &(pstDestPlmnList->astPlmnId[0].stPlmnId));

    if ( VOS_FALSE == ulUserSpecFlag )
    {
        if ( pstDestPlmnList->ulPlmnNum > 1 )
        {
            pstMsg->bitOpEqlPlmn = VOS_TRUE;
        }

        for ( ulIndex = 1; ulIndex < NAS_MML_MIN(pstDestPlmnList->ulPlmnNum, MMC_LMM_MAX_EQUPLMN_NUM); ulIndex++ )
        {
            NAS_MML_ConvertNasPlmnToLMMFormat(&(pstMsg->stEplmnList.astEplmnList[ulIndex-1]), &(pstDestPlmnList->astPlmnId[ulIndex].stPlmnId));
            pstMsg->stEplmnList.ulPlmnNum++;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmSpecPlmnSearchReq
 功能描述  : 根据是否用户指定搜网时，向LMM发送指定搜网请求消息
 输入参数  : stDestPlmn
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者  : s46746
   修改内容  : 新生成函数

 2.日    期   : 2011年8月17日
   作    者   : w00167002
   修改内容   : V7R1 PHASEII 重构: 添加pc回放
 3.日    期   : 2011年12月15日
   作    者   : W00166186
   修改内容   : dts2011111502641,L下PLMN加入禁止TA后不再搜网
 4.日    期   : 2011年11月28日
   作    者   : z00161729
   修改内容   : MMC与LMM消息交互采用内部消息队列，为保证PC上GTR功能已有用例可以正常使用，
                在PC上MMC、GMM和LMM的交互还使用外部消息，发送消息函数需要用宏NAS_STUB隔开
 5.日    期   : 2014年3月19日
   作    者   : w00242748
   修改内容   : DTS2014031200137:当NV特性打开时，自动开机或者搜网时，如果首次搜索RPLMN的话，
                需要将HPLMN/EHPLMN带给接入层。
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmSpecPlmnSearchReq(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU    *pstDestPlmnList,
    VOS_UINT32                          ulUserSpecFlag,
    VOS_UINT32                          ulPlmnSearchScene
)
{
    /* 定义原语类型指针 */
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmSpecPlmnSearchReq():WARNING:PS_ALLOC_MSG FIAL");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
                sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 构造发送消息 */
    NAS_MMC_BuildLmmSpecPlmnSearchReqMsg(pstMsg, pstDestPlmnList, ulUserSpecFlag, ulPlmnSearchScene);

    NAS_MML_SaveNwSearchReqInfo(pstMsg);

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmSpecPlmnSearchReq():WARNING:SEND LMM PLMN SEARCH REQ FIAL");
        return;
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif


#ifndef __PS_WIN32_RECUR__

    NAS_MML_SetUePcRecurFlg(VOS_TRUE);
#endif

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_BuildLmmHistoryPlmnSearchReqMsg
 功能描述  : 构造通知Lmm指定历史频点搜网的消息体
 输入参数  : pstDestPlmnList, 指定搜网的PLMN列表
 输出参数  : pstMsg  返回构造消息体指针
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年6月3日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
*****************************************************************************/
VOS_VOID NAS_MMC_BuildLmmHistoryPlmnSearchReqMsg(
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg,
    NAS_MML_PLMN_LIST_WITH_RAT_STRU    *pstDestPlmnList
)
{
    VOS_UINT32                          ulIndex;

    /* 清空消息内容 */
    NAS_MMC_CLR_MSG_ENTITY(pstMsg);

    /* 填写消息头 */
    NAS_MMC_CFG_MSG_HDR(pstMsg,
                        PS_PID_MM,
                        ID_MMC_LMM_PLMN_SRCH_REQ,
                        sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息内容 */
    pstMsg->ulOpId                          = 0;

    pstMsg->enSrchType                      = MMC_LMM_PLMN_SRCH_HISTORY;

    pstMsg->bitOpSpecPlmn                   = VOS_TRUE;
    pstMsg->bitOpPlmnInfoCampFlg            = VOS_TRUE;
    pstMsg->enFftScanType                   = MMC_LMM_FFT_SCAN_TYPE_NONE;

    NAS_MML_ConvertNasPlmnToLMMFormat(&(pstMsg->stSpecPlmnId), &(pstDestPlmnList->astPlmnId[0].stPlmnId));

    /* 构造EPLMN LIST网络 */
    if (pstDestPlmnList->ulPlmnNum > 1)
    {
        pstMsg->bitOpEqlPlmn = VOS_TRUE;
    }

    for (ulIndex = 1; ulIndex < NAS_MML_MIN(pstDestPlmnList->ulPlmnNum, MMC_LMM_MAX_EQUPLMN_NUM); ulIndex++)
    {
        NAS_MML_ConvertNasPlmnToLMMFormat(&(pstMsg->stEplmnList.astEplmnList[ulIndex-1]), &(pstDestPlmnList->astPlmnId[ulIndex].stPlmnId));
        pstMsg->stEplmnList.ulPlmnNum++;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmHistoryPlmnSearchReq
 功能描述  : 给LMM发送history类型的搜网请求
 输入参数  : NAS_MML_PLMN_LIST_WITH_RAT_STRU    *pstDestPlmnList
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月02日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmHistoryPlmnSearchReq(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU    *pstDestPlmnList
)
{
    /* 定义原语类型指针 */
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmHistoryPlmnSearchReq():WARNING:PS_ALLOC_MSG FAIL");
        return;
    }

    /* 构造发送消息 */
    NAS_MMC_BuildLmmHistoryPlmnSearchReqMsg(pstMsg, pstDestPlmnList);

    NAS_MML_SaveNwSearchReqInfo(pstMsg);

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))

    /* 调用VOS发送原语 */
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmHistoryPlmnSearchReq():WARNING:SEND LMM PLMN SEARCH REQ FAIL");
        return;
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_BuildLmmPrefBandPlmnSearchReqMsg
 功能描述  : 构造发送给LMM的Pref band搜网请求
 输入参数  : MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg
             NAS_MML_PLMN_LIST_WITH_RAT_STRU    *pstDestPlmnList
             VOS_UINT32                          ulUserSpecFlag
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月28日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_BuildLmmPrefBandPlmnSearchReqMsg(
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg,
    NAS_MML_PLMN_LIST_WITH_RAT_STRU    *pstDestPlmnList,
    VOS_UINT32                          ulUserSpecFlag
)
{
    VOS_UINT32                          ulIndex;

    PS_MEM_SET((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                         sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId                 = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid                   = PS_PID_MM;

    /* 发送PID需要置上 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                        = sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                         = ID_MMC_LMM_PLMN_SRCH_REQ;
    pstMsg->ulOpId                          = 0;

    pstMsg->enSrchType                      = MMC_LMM_PLMN_SRCH_PREF_BAND;
    pstMsg->bitOpSpecPlmn                   = VOS_TRUE;
    pstMsg->bitOpPlmnInfoCampFlg            = VOS_TRUE;
    pstMsg->enFftScanType                   = MMC_LMM_FFT_SCAN_TYPE_NONE;

    NAS_MML_ConvertNasPlmnToLMMFormat(&(pstMsg->stSpecPlmnId), &(pstDestPlmnList->astPlmnId[0].stPlmnId));

    if ( VOS_FALSE == ulUserSpecFlag )
    {
        if ( pstDestPlmnList->ulPlmnNum > 1 )
        {
            pstMsg->bitOpEqlPlmn = VOS_TRUE;
        }

        for ( ulIndex = 1; ulIndex < NAS_MML_MIN(pstDestPlmnList->ulPlmnNum, MMC_LMM_MAX_EQUPLMN_NUM); ulIndex++ )
        {
            NAS_MML_ConvertNasPlmnToLMMFormat(&(pstMsg->stEplmnList.astEplmnList[ulIndex-1]), &(pstDestPlmnList->astPlmnId[ulIndex].stPlmnId));
            pstMsg->stEplmnList.ulPlmnNum++;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmPrefBandPlmnSearchReq
 功能描述  : 向LMM发送指定搜网请求
 输入参数  : NAS_MML_PLMN_LIST_WITH_RAT_STRU    *pstDestPlmnList
             VOS_UINT32                          ulUserSpecFlag
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月28日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmPrefBandPlmnSearchReq(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU    *pstDestPlmnList,
    VOS_UINT32                          ulUserSpecFlag
)
{
    /* 定义原语类型指针 */
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmSpecPlmnSearchReq():WARNING:PS_ALLOC_MSG FIAL");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
                sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 构造发送消息 */
    NAS_MMC_BuildLmmPrefBandPlmnSearchReqMsg(pstMsg, pstDestPlmnList, ulUserSpecFlag);

    NAS_MML_SaveNwSearchReqInfo(pstMsg);

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmSpecPlmnSearchReq():WARNING:SEND LMM PLMN SEARCH REQ FIAL");
        return;
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmNcellSpecPlmnSearchReq
 功能描述  : 向lmm发送ncell快速指定搜网消息
 输入参数  : pstLteNcellInfo        - lte 频点列表信息
             pstOtherModemEplmnInfo - 等效plmn信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月25日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
 2.日    期   : 2014年2月14日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
 3.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmNcellSpecPlmnSearchReq(
    NAS_MMC_LTE_NCELL_INFO_STRU        *pstLteNcellInfo,
    NAS_MML_EQUPLMN_INFO_STRU          *pstOtherModemEplmnInfo
)
{
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucLoopEplmnNum;
    VOS_UINT8                           ucMaxEplmnNum;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmNcellSpecPlmnSearchReq():WARNING:PS_ALLOC_MSG FIAL");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
                sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 构造发送消息 */
    pstMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid    = PS_PID_MM;

    /* 发送PID需要置上 */
    pstMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid      = WUEPS_PID_MMC;
    pstMsg->ulLength         = sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId          = ID_MMC_LMM_PLMN_SRCH_REQ;
    pstMsg->ulOpId           = 0;

    pstMsg->enSrchType       = MMC_LMM_PLMN_SRCH_NCELL_SPEC;

    /* 带ncell 频点列表信息 */
    pstMsg->bitOpNcellInfo   = VOS_TRUE;
    pstMsg->stNcellInfo.ucLteArfcnNum = pstLteNcellInfo->ucLteArfcnNum;
    PS_MEM_CPY(pstMsg->stNcellInfo.aulLteArfcnList, pstLteNcellInfo->aulLteArfcnList,
               sizeof(pstMsg->stNcellInfo.aulLteArfcnList));

    /* Added by s00246516 for L-C互操作项目, 2014-02-14, Begin */
    pstMsg->stNcellInfo.ucLteCellIdNum = pstLteNcellInfo->ucLteCellNum;
    PS_MEM_CPY(pstMsg->stNcellInfo.ausLteCellIdList, pstLteNcellInfo->ausLteCellList,
               sizeof(pstMsg->stNcellInfo.ausLteCellIdList));
    /* Added by s00246516 for L-C互操作项目, 2014-02-14, End */

    ucMaxEplmnNum        = pstOtherModemEplmnInfo->ucEquPlmnNum;

    if (ucMaxEplmnNum > MMC_LMM_MAX_EQUPLMN_NUM)
    {
        ucMaxEplmnNum = MMC_LMM_MAX_EQUPLMN_NUM;
    }

    pstMsg->stNcellInfo.stEplmnList.ulPlmnNum = ucMaxEplmnNum;

    for (ucLoopEplmnNum = 0; ucLoopEplmnNum < ucMaxEplmnNum; ucLoopEplmnNum++ )
    {
        NAS_MML_ConvertNasPlmnToLMMFormat(&(pstMsg->stNcellInfo.stEplmnList.astEplmnList[ucLoopEplmnNum]),
                                          &(pstOtherModemEplmnInfo->astEquPlmnAddr[ucLoopEplmnNum]));
    }

    pstMsg->bitOpPlmnInfoCampFlg = VOS_TRUE;
    pstMsg->enFftScanType        = MMC_LMM_FFT_SCAN_TYPE_NONE;

    NAS_MML_SaveNwSearchReqInfo(pstMsg);

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MMC, pstMsg );
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

#ifndef __PS_WIN32_RECUR__
    NAS_MML_SetUePcRecurFlg(VOS_TRUE);
#endif

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_BuildMmcLmmDetachIndActionResultReqMsg
 功能描述  : 构造通知Lmm业务流程结果的消息体
 输入参数  : NAS_MMC_GMM_NT_DETACH_ENUM_U32       enMtType,
             NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16   enCnCause 拒绝原因值
 输出参数  : MMC_LMM_ACTION_RESULT_REQ_STRU      *pstMsg  返回构造消息体指针
 返 回 值  : 无
 调用函数  :
 被调函数  :
 协议说明  : TS 24008 10.5.5.5
   Type of detach (octet 1)

   In the MS to network direction:
   Bits
   3   2   1
   0   0   1       GPRS detach
   0   1   0       IMSI detach
   0   1   1       Combined GPRS/IMSI detach

   All other values are interpreted as Combined GPRS/IMSI detach by this version of the protocol.

   In the network to MS direction:
   Bits
   3   2   1
   0   0   1       re-attach required
   0   1   0       re-attach not required
   0   1   1       IMSI detach (after VLR failure)

   All other values are interpreted as re-attach not required by this version of the protocol.
 修改历史      :
 1.日    期   : 2011年4月19日
   作    者   : W00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年8月11日
   作    者   : W00167002
   修改内容   : 增加消息长度的赋值

*****************************************************************************/
VOS_VOID NAS_MMC_BuildMmcLmmDetachIndActionResultReqMsg(
    NAS_MMC_GMM_NT_DETACH_ENUM_U32      enMtType,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCnCause,
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pstMsg
)
{
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnRejCause;

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                         sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_ACTION_RESULT_REQ;
    pstMsg->ulOpId                      = 0;

    /* 根据DETACH 类型设置发起业务类型和结果域类型 */
    switch(enMtType)
    {
        case NAS_MMC_GMM_NT_DETACH_IMSI:
            pstMsg->bitOpReqDomain = VOS_TRUE;
            pstMsg->bitOpRstDomain = VOS_TRUE;
            pstMsg->ulReqDomain    = MMC_LMM_IMSI_ONLY;
            pstMsg->ulRstDomain    = MMC_LMM_IMSI_ONLY;
            pstMsg->ulMtDetachType = MMC_LMM_MT_DET_IMSI;
            break;

        case NAS_MMC_GMM_NT_DETACH_REATTACH:
            pstMsg->bitOpReqDomain = VOS_TRUE;
            pstMsg->bitOpRstDomain = VOS_TRUE;
            pstMsg->ulReqDomain    = MMC_LMM_PS_ONLY;
            pstMsg->ulRstDomain    = MMC_LMM_PS_ONLY;
            pstMsg->ulMtDetachType = MMC_LMM_MT_DET_REATTACH_REQUIRED;
            break;

        case NAS_MMC_GMM_NT_DETACH_NOATTACH:
            pstMsg->bitOpReqDomain = VOS_TRUE;
            pstMsg->bitOpRstDomain = VOS_TRUE;
            pstMsg->ulReqDomain    = MMC_LMM_PS_ONLY;
            pstMsg->ulRstDomain    = MMC_LMM_PS_ONLY;
            pstMsg->ulMtDetachType = MMC_LMM_MT_DET_REATTACH_NOT_REQUIRED;
            break;

        default:
            break;
    }

    pstMsg->bitOpMtDetachType           = VOS_TRUE;
    pstMsg->enActionType                = MMC_LMM_ACTION_MT_DETACH;
    pstMsg->ulActRst                    = MMC_LMM_RSLT_TYPE_SUCCESS;

    
    if ( (VOS_OK == NAS_MMC_ConvertMmCauseToEmmCause(enCnCause, &enCnRejCause))
     && (MMC_LMM_MT_DET_REATTACH_NOT_REQUIRED == pstMsg->ulMtDetachType))
    {
        pstMsg->bitOpCnCause            = VOS_TRUE;
        pstMsg->ucCnCause               = enCnRejCause;
    }

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConverCnDomainToLmm
 功能描述  : 将MMC内部保存的Domain转换为LMM格式的
 输入参数  : enCnDoamin:MMC内部保存的域
 输出参数  : penLmmDomain:LMM格式的域
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月12日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_ConverCnDomainToLmm(
    NAS_MMC_REG_DOMAIN_ENUM_UINT8      enCnDoamin,
    MMC_LMM_DOMAIN_ENUM_UINT32         *penLmmDomain
)
{
    if ( NAS_MMC_REG_DOMAIN_CS           == enCnDoamin)
    {
        *penLmmDomain = MMC_LMM_IMSI_ONLY;
    }
    else if ( NAS_MMC_REG_DOMAIN_PS_CS   == enCnDoamin)
    {
        *penLmmDomain = MMC_LMM_COMBINED_PS_IMSI;
    }
    else
    {
        *penLmmDomain = MMC_LMM_PS_ONLY;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertMmCauseToEmmCause
 功能描述  : 将MM的注册结果转换为EMM的注册结果,由于需要明确告诉EMM是否是网络
              拒绝还是其他原因拒绝
 输入参数  : enCnCause:MM注册结果
 输出参数  : penProtolCause:协议中规定的结果
 返 回 值  : VOS_OK:转换成功
              VOS_ERR:转换失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_ConvertMmCauseToEmmCause(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCnCause,
    NAS_LMM_CN_CAUSE_ENUM_UINT8        *penProtolCause
)
{
    /* 该原因值表明注册成功或网络无响应 */
    if ( NAS_MML_REG_FAIL_CAUSE_NULL == enCnCause )
    {
        return VOS_ERR;
    }

    if ( enCnCause >= NAS_MML_REG_FAIL_CAUSE_AUTH_REJ )
    {
        return VOS_ERR;
    }

    *penProtolCause = (VOS_UINT8)enCnCause;

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertGuRsltToLmmFormat
 功能描述  : 根据GU的注册结果，转换成L的格式
 输入参数  : enRegRst  注册结果
             enCnCause 注册原因值
 输出参数  :
 返 回 值  : VOS_OK:转换成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2012年7月13日
    作    者   : s00217060
    修改内容   : for sync lmm cs state:增加注册结果为Bar的类型转换

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertGuRsltToLmmFormat(
    NAS_MML_REG_RESULT_ENUM_UINT8       enGuRegRslt,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enGuCnCause,
    MMC_LMM_RSLT_TYPE_ENUM_UINT32      *penLmmActRslt
)
{
    MMC_LMM_RSLT_TYPE_ENUM_UINT32      enRslt;

    /* 获取注册结果 */
    if ( NAS_MML_REG_RESULT_SUCCESS == enGuRegRslt )
    {
        enRslt = MMC_LMM_RSLT_TYPE_SUCCESS;
    }
    else
    {
        /* 调整判断语句顺序，先判断enGuCnCause小于NAS_MML_REG_FAIL_CAUSE_AUTH_REJ
           再判断enGuCnCause等于NAS_MML_REG_FAIL_CAUSE_AUTH_REJ
           增加判断enGuCnCause等于NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED */
        if (enGuCnCause < NAS_MML_REG_FAIL_CAUSE_AUTH_REJ)
        {
            enRslt = MMC_LMM_RSLT_TYPE_CN_REJ;
        }
        else if (NAS_MML_REG_FAIL_CAUSE_AUTH_REJ == enGuCnCause)
        {
            enRslt = MMC_LMM_RSLT_TYPE_AUTH_REJ;
        }
        else if (NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED == enGuCnCause)
        {
            enRslt = MMC_LMM_RSLT_TYPE_ACCESS_BARRED;
        }
        else
        {
            enRslt = MMC_LMM_RSLT_TYPE_FAILURE;
        }
    }

    *penLmmActRslt = enRslt;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify
 功能描述  : 向LTE发送用户搜网结束通知
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月06日
   作    者   : w00166186
   修改内容   : 新生成函数
 2.日    期   : 2012年2月24日
   作    者   : w00176964
   修改内容   : V7R1 PhaseIV 调整
*****************************************************************************/

VOS_VOID NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify( VOS_VOID )
{
    /* 定义原语类型指针 */
    MMC_LMM_USER_PLMN_END_NOTIFY_STRU   *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_USER_PLMN_END_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_USER_PLMN_END_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_USER_PLMN_END_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_USER_PLMN_END_NOTIFY_STRU));
#endif

    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify():ERROR:Memory Alloc Error for pstMsg");
        return;
    }

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    /* 发送PID需要置上 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_USER_PLMN_END_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_USER_PLMN_END_NOTIFY;
    pstMsg->ulOpId                      = 0;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify():WARNING:SEND LMM PLMN ANYCELL SEARCH REQ FIAL");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmBgStopPlmnSearchReq
 功能描述  : 向LTE发送停止背景搜网消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年4月25日
   作    者   : z00161729
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmBgStopPlmnSearchReq(VOS_VOID)
{
    /* 定义原语类型指针 */
    MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU                   *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmBgStopPlmnSearchReq():WARNING:PS_ALLOC_MSG FIAL");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
                sizeof(MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 构造发送消息 */
    pstMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid    = PS_PID_MM;
    pstMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid      = WUEPS_PID_MMC;
    pstMsg->ulLength         = sizeof(MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId          = ID_MMC_LMM_STOP_BG_PLMN_SEARCH_REQ;
    pstMsg->ulOpId           = 0;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmBgStopPlmnSearchReq():WARNING:SEND LMM BG STOP PLMN SEARCH REQ FIAL");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmFastPlmnSearchReq
 功能描述  : 向LTE发送快速指定搜网消息
 输入参数  : pstDestPlmn - 搜索PLMN信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年4月25日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2015年5月26日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmFastPlmnSearchReq(
    NAS_MML_PLMN_ID_STRU               *pstDestPlmn
)
{
    /* 定义原语类型指针 */
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmFastPlmnSearchReq():WARNING:PS_ALLOC_MSG FIAL");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
                sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 构造发送消息 */
    pstMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid    = PS_PID_MM;
    pstMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid      = WUEPS_PID_MMC;
    pstMsg->ulLength         = sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId          = ID_MMC_LMM_PLMN_SRCH_REQ;
    pstMsg->ulOpId           = 0;

    /* 快速指定的PLMN的搜索 */
    pstMsg->enSrchType       = MMC_LMM_PLMN_SRCH_FAST_SPEC;

    pstMsg->bitOpSpecPlmn    = VOS_TRUE;
    NAS_MML_ConvertNasPlmnToLMMFormat(&(pstMsg->stSpecPlmnId), pstDestPlmn);

    pstMsg->bitOpPlmnInfoCampFlg = VOS_TRUE;
    pstMsg->enFftScanType        = MMC_LMM_FFT_SCAN_TYPE_NONE;

    NAS_MML_SaveNwSearchReqInfo(pstMsg);

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmFastPlmnSearchReq():WARNING:SEND LMM PLMN SEARCH REQ FIAL");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmBgPlmnSearchReq
 功能描述  : 向LTE发送快背景搜网消息
 输入参数  : pstDestPlmn - 搜索PLMN信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年4月25日
   作    者   : z00161729
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmBgPlmnSearchReq(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
)
{
    /* 定义原语类型指针 */
    MMC_LMM_BG_PLMN_SEARCH_REQ_STRU                        *pstMsg                          = VOS_NULL_PTR;
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriodList    = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstLai                          = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbPlmnInfo;
    VOS_UINT32                                              i;
    MMC_LMM_PLMN_ID_STRU                                    stLmmPlmn;

    /* 从全局变量中获取FORBIDEN ROAMING LAS信息 */
    pstForbPlmnInfo = NAS_MML_GetForbidPlmnInfo();


#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_BG_PLMN_SEARCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_BG_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_BG_PLMN_SEARCH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_BG_PLMN_SEARCH_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmBgPlmnSearchReq():WARNING:PS_ALLOC_MSG FIAL");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
                sizeof(MMC_LMM_BG_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 构造发送消息 */
    pstMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid     = PS_PID_MM;
    pstMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->ulLength          = sizeof(MMC_LMM_BG_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId           = ID_MMC_LMM_BG_PLMN_SEARCH_REQ;
    pstMsg->ulOpId            = 0;

    NAS_MML_ConvertNasPlmnToLMMFormat(&stLmmPlmn, &pstDestPlmn->stPlmnId);
    PS_MEM_CPY(pstMsg->stSpecPlmnWithRat.aucPlmnId, stLmmPlmn.aucPlmnId, MMC_LMM_PLMN_ID_LEN);
    pstMsg->stSpecPlmnWithRat.enPlmnRat = pstDestPlmn->enRat;

    if (NAS_MML_NET_RAT_TYPE_LTE != pstDestPlmn->enRat)
    {
        /* L下背景搜GU的网络，需要将所有禁止漫游 LA 添加到ForbLa列表 */
        for ( i = 0; i < pstForbPlmnInfo->ucForbRoamLaNum; i++ )
        {
            NAS_MML_ConvertNasPlmnToLMMFormat(&(pstMsg->astForbRoamLaiList[i].stPlmnId),
                                              &(pstForbPlmnInfo->astForbRomLaList[i].stPlmnId));
            pstMsg->astForbRoamLaiList[i].stLac.ucLac   =
                pstForbPlmnInfo->astForbRomLaList[i].aucLac[0];
            pstMsg->astForbRoamLaiList[i].stLac.ucLacCnt =
                pstForbPlmnInfo->astForbRomLaList[i].aucLac[1];
        }

        /* ForbLa列表中的禁止漫游 LA 的个数 */
        pstMsg->ulForbRoamLaiNum = pstForbPlmnInfo->ucForbRoamLaNum;

        pstForbLaWithValidPeriodList = NAS_MML_GetForbLaWithValidPeriodList();
        for ( i = 0; i < pstForbLaWithValidPeriodList->ulForbLaWithValidPeriodNum; i++ )
        {
            pstLai = &(pstForbLaWithValidPeriodList->astForbLaWithValidPeriodList[i].stForbLaWithValidPeriodLai);
            if (   (VOS_FALSE == NAS_MML_IsLaiInDestLaiList(pstLai, pstForbPlmnInfo->ucForbRoamLaNum,
                  pstForbPlmnInfo->astForbRomLaList)) 
                && ((pstMsg->ulForbRoamLaiNum) < MMC_LMM_MAX_FORB_ROAM_LAI_NUM)   )
            {
                NAS_MML_ConvertNasPlmnToLMMFormat(&(pstMsg->astForbRoamLaiList[pstMsg->ulForbRoamLaiNum].stPlmnId),
                                              &(pstLai->stPlmnId));
                pstMsg->astForbRoamLaiList[i].stLac.ucLac    = pstLai->aucLac[0];
                pstMsg->astForbRoamLaiList[i].stLac.ucLacCnt = pstLai->aucLac[1];
            }
        }
    }


#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmBgPlmnSearchReq():WARNING:SEND LMM BG PLMN SEARCH REQ FIAL");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmGetGeoPlmnSearchReq
 功能描述  : 向LMM发送获取地理信息请求消息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年05月08日
   作    者   : sunjitan 00193151
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmGetGeoPlmnSearchReq(VOS_VOID)
{
    /* 定义原语类型指针 */
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmGetGeoPlmnSearchReq:ERROR:Memory Alloc Error for pstMsg");
        return;
    }

    /* 清空消息内容 */
    NAS_MMC_CLR_MSG_ENTITY(pstMsg);

    /* 填写消息头 */
    NAS_MMC_CFG_MSG_HDR(pstMsg,
                        PS_PID_MM,
                        ID_MMC_LMM_PLMN_SRCH_REQ,
                        sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息内容 */
    pstMsg->ulOpId                      = 0;
    pstMsg->enSrchType                  = MMC_LMM_PLMN_SRCH_GET_GEO;

    pstMsg->enFftScanType               = MMC_LMM_FFT_SCAN_TYPE_LOW;
    pstMsg->bitOpPlmnInfoCampFlg        = VOS_FALSE;

    NAS_MML_SaveNwSearchReqInfo(pstMsg);

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
         NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmGetGeoPlmnSearchReq:WARNING:SEND LMM PLMN ANYCELL SEARCH REQ FIAL");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmStopGetGeoPlmnSearchReq
 功能描述  : 向LMM发送停止获取地理信息请求消息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年05月08日
   作    者   : sunjitan 00193151
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmStopGetGeoPlmnSearchReq(VOS_VOID)
{
    NAS_MMC_SndLmmPlmnSrchStopReq();
    return;
}






/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmUeOocStatusInd
 功能描述  : 通知LMM当前进入OOC状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月31日
   作    者   : z40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_SndLmmUeOocStatusInd( VOS_VOID )
{
    /* 定义原语类型指针 */
    MMC_LMM_UE_OOC_STATUS_NOTIFY_STRU  *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstMsg = (MMC_LMM_UE_OOC_STATUS_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_UE_OOC_STATUS_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_UE_OOC_STATUS_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_UE_OOC_STATUS_NOTIFY_STRU));
#endif

    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmUeOocStatusInd():ERROR:Memory Alloc Error for pstMsg");
        return;
    }

    pstMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid      = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid    = PS_PID_MM;
    pstMsg->ulLength         = sizeof(MMC_LMM_UE_OOC_STATUS_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId          = ID_MMC_LMM_UE_OOC_STATUS_NOTIFY;
    pstMsg->ulOpId           = 0;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmUeOocStatusInd():WARNING:SEND LMM MSG FIAL");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif
    return;
}




/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmWcdmaSysInfoInd
 功能描述  : 向LMM转发W的系统消息中的主要信息
 输入参数  : pstMsg: W的系统消息
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月15日
   作    者   : l00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmWcdmaSysInfoInd(
    struct MsgCB                       *pstMsg
)
{
    RRMM_SYS_INFO_IND_STRU             *pstRrMmSysInfoInd  = VOS_NULL_PTR;
    MMC_LMM_WCDMA_SYS_INFO_IND_STRU    *pstLmmWcdmaSysInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stGUNasPlmnId;

    pstRrMmSysInfoInd = (RRMM_SYS_INFO_IND_STRU*)pstMsg;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstLmmWcdmaSysInfo = (MMC_LMM_WCDMA_SYS_INFO_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_WCDMA_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstLmmWcdmaSysInfo = (MMC_LMM_WCDMA_SYS_INFO_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_WCDMA_SYS_INFO_IND_STRU));
#endif

    if( VOS_NULL_PTR == pstLmmWcdmaSysInfo )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmWcdmaSysInfoInd():ERROR:Memory Alloc Error for pstMsg");
        return;
    }

    pstLmmWcdmaSysInfo->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstLmmWcdmaSysInfo->ulSenderPid      = WUEPS_PID_MMC;
    pstLmmWcdmaSysInfo->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstLmmWcdmaSysInfo->ulReceiverPid    = PS_PID_MM;
    pstLmmWcdmaSysInfo->ulLength         = sizeof(MMC_LMM_WCDMA_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstLmmWcdmaSysInfo->ulMsgId          = ID_MMC_LMM_WCDMA_SYS_INFO_IND;

    /* 填充PLMN 字段 */
    stGUNasPlmnId.ulMcc = pstRrMmSysInfoInd->PlmnId.ulMcc;;
    stGUNasPlmnId.ulMnc = pstRrMmSysInfoInd->PlmnId.ulMnc;

    NAS_MML_ConvertNasPlmnToLMMFormat(&(pstLmmWcdmaSysInfo->stPlmnId),
                                      &(stGUNasPlmnId));

    /* 填充小区ID */
    pstLmmWcdmaSysInfo->ulCellId = pstRrMmSysInfoInd->ulCellId;

    /* 填充LAC */
    /* aucCnCommonInfo[0] 和 aucCnCommonInfo[1] 代表 lac[0] 和  Lac[1]*/
    pstLmmWcdmaSysInfo->usLac  = (VOS_UINT16)pstRrMmSysInfoInd->aucCnCommonInfo[1];
    pstLmmWcdmaSysInfo->usLac |= (VOS_UINT16)(pstRrMmSysInfoInd->aucCnCommonInfo[0]<< NAS_MML_OCTET_MOVE_EIGHT_BITS);


    /* 填充RAC */
    if ( 0 == pstRrMmSysInfoInd->ucPsInfoSize )
    {
        pstLmmWcdmaSysInfo->bitOpRac = VOS_FALSE;
        pstLmmWcdmaSysInfo->ucRac    = 0;
    }
    else
    {
        pstLmmWcdmaSysInfo->bitOpRac = VOS_TRUE;
        pstLmmWcdmaSysInfo->ucRac    = pstRrMmSysInfoInd->aucPsInfo[0];
    }

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstLmmWcdmaSysInfo ) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmWcdmaSysInfoInd():WARNING:SEND LMM MSG FIAL");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstLmmWcdmaSysInfo);
#endif
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmGsmSysInfoInd
 功能描述  : 向LMM转发G的系统消息中的主要信息
 输入参数  : pstMsg: G的系统消息
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月15日
   作    者   : l00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmGsmSysInfoInd(
    struct MsgCB                       *pstMsg
)
{
    GRRMM_SYS_INFO_IND_ST              *pstGrrMmSysInfo  = VOS_NULL_PTR;
    MMC_LMM_GSM_SYS_INFO_IND_STRU      *pstLmmGsmSysInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stGUNasPlmnId;

    pstGrrMmSysInfo = (GRRMM_SYS_INFO_IND_ST*)pstMsg;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 申请内存  */
    pstLmmGsmSysInfo = (MMC_LMM_GSM_SYS_INFO_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_GSM_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstLmmGsmSysInfo = (MMC_LMM_GSM_SYS_INFO_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_GSM_SYS_INFO_IND_STRU));
#endif

    if( VOS_NULL_PTR == pstLmmGsmSysInfo )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmGsmSysInfoInd():ERROR:Memory Alloc Error for pstMsg");
        return;
    }

    pstLmmGsmSysInfo->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstLmmGsmSysInfo->ulSenderPid      = WUEPS_PID_MMC;
    pstLmmGsmSysInfo->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstLmmGsmSysInfo->ulReceiverPid    = PS_PID_MM;
    pstLmmGsmSysInfo->ulLength         = sizeof(MMC_LMM_GSM_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstLmmGsmSysInfo->ulMsgId          = ID_MMC_LMM_GSM_SYS_INFO_IND;

    /* 填充PLMN 字段 */
    stGUNasPlmnId.ulMcc = pstGrrMmSysInfo->PlmnId.ulMcc;;
    stGUNasPlmnId.ulMnc = pstGrrMmSysInfo->PlmnId.ulMnc;

    NAS_MML_ConvertNasPlmnToLMMFormat(&(pstLmmGsmSysInfo->stPlmnId),
                                      &(stGUNasPlmnId));

    /* 填充小区ID */
    pstLmmGsmSysInfo->ulCellId = (VOS_UINT32)pstGrrMmSysInfo->usCellId;

    /* 填充LAC */
    pstLmmGsmSysInfo->usLac    = pstGrrMmSysInfo->usLac;

    /* 填充RAC */
    if ( 0 == pstGrrMmSysInfo->ucGprsSupportInd )
    {
        pstLmmGsmSysInfo->bitOpRac = VOS_FALSE;
        pstLmmGsmSysInfo->ucRac    = 0;
    }
    else
    {
        pstLmmGsmSysInfo->bitOpRac = VOS_TRUE;
        pstLmmGsmSysInfo->ucRac    = pstGrrMmSysInfo->ucRac;
    }

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstLmmGsmSysInfo ) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmGsmSysInfoInd():WARNING:SEND LMM MSG FIAL");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstLmmGsmSysInfo);
#endif

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmCellSelReq
 功能描述  : 向LTE下发送CELL_SELECTION_CTRL_REQ的处理
 输入参数  : ulSelType: 发送到LMM的等效PLMN列表信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

修改历史      :
 1.日    期   : 2012年10月12日
   作    者   : t00212959
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmCellSelReq(
    MMC_LMM_CELL_SEL_TYPE_ENUM_UINT32       ulSelType
)
{
    MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU                   *pstLmmCellSelStru = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstLmmCellSelStru = (MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstLmmCellSelStru = (MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU));
#endif

    /* 若分配内存出错,返回*/
    if ( VOS_NULL_PTR == pstLmmCellSelStru )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmEquPlmnReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstLmmCellSelStru + VOS_MSG_HEAD_LENGTH, 0X0,
               sizeof(MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU) - VOS_MSG_HEAD_LENGTH );

    pstLmmCellSelStru->ulReceiverPid   = PS_PID_MM;
    pstLmmCellSelStru->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstLmmCellSelStru->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstLmmCellSelStru->ulSenderPid     = WUEPS_PID_MMC;
    pstLmmCellSelStru->ulMsgId         = ID_MMC_LMM_CELL_SELECTION_CTRL_REQ;
    pstLmmCellSelStru->ulLength        = sizeof(MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstLmmCellSelStru->ulOpId          = 0;
    pstLmmCellSelStru->ulSelecType     = ulSelType;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstLmmCellSelStru ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmCellSelReq():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstLmmCellSelStru);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstLmmCellSelStru);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmCellSelReq
 功能描述  : 向LTE下发送CELL_SELECTION_CTRL_REQ的处理
 输入参数  : ulSelType: 发送到LMM的等效PLMN列表信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

修改历史      :
 1.日    期   : 2012年10月12日
   作    者   : t00212959
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmSuspendRelReq(VOS_VOID)
{
    MMC_LMM_SUSPEND_REL_REQ_STRU                   *pstMmcLmmSuspendRelReq = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstMmcLmmSuspendRelReq = (MMC_LMM_SUSPEND_REL_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_SUSPEND_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMmcLmmSuspendRelReq = (MMC_LMM_SUSPEND_REL_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_SUSPEND_REL_REQ_STRU));
#endif

    /* 若分配内存出错,返回*/
    if ( VOS_NULL_PTR == pstMmcLmmSuspendRelReq )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmSuspendRelReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMmcLmmSuspendRelReq + VOS_MSG_HEAD_LENGTH, 0X0,
               sizeof(MMC_LMM_SUSPEND_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH );

    pstMmcLmmSuspendRelReq->ulReceiverPid   = PS_PID_MM;
    pstMmcLmmSuspendRelReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMmcLmmSuspendRelReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMmcLmmSuspendRelReq->ulSenderPid     = WUEPS_PID_MMC;
    pstMmcLmmSuspendRelReq->ulMsgId         = ID_MMC_LMM_SUSPEND_REL_REQ;
    pstMmcLmmSuspendRelReq->ulLength        = sizeof(MMC_LMM_SUSPEND_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMmcLmmSuspendRelReq->ulOpId          = 0;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMmcLmmSuspendRelReq ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmSuspendRelReq():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMmcLmmSuspendRelReq);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMmcLmmSuspendRelReq);
#endif

    return;
}

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmOtherModemInfoNotify
 功能描述  : MMC给LMM下发Modem1的信息，LMM根据需要透传给LRRC
 输入参数  : pstLmmSysInfoMsg: 发送到LMM的LTE的系统消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

修改历史      :
 1.日    期   : 2013年11月22日
   作    者   : z00161729
   修改内容   : SVLTE优化G-TL ps切换性能修改
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmOtherModemInfoNotify(
    MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU                   *pstOtherModemInfoMsg
)
{
    MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU                   *pstMmcLmmOtherModemInfo = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstMmcLmmOtherModemInfo = (MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                            sizeof(MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMmcLmmOtherModemInfo = (MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU));
#endif

    /* 若分配内存出错,返回*/
    if ( VOS_NULL_PTR == pstMmcLmmOtherModemInfo )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmOtherModemInfoNotify():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMmcLmmOtherModemInfo + VOS_MSG_HEAD_LENGTH, 0X0,
               sizeof(MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH );

    /* 消息IE项赋值 */
    pstMmcLmmOtherModemInfo->ulReceiverPid       = PS_PID_MM;
    pstMmcLmmOtherModemInfo->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMmcLmmOtherModemInfo->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMmcLmmOtherModemInfo->ulSenderPid         = WUEPS_PID_MMC;
    pstMmcLmmOtherModemInfo->ulMsgId             = ID_MMC_LMM_OTHER_MODEM_INFO_NOTIFY;
    pstMmcLmmOtherModemInfo->ulLength            = sizeof(MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMmcLmmOtherModemInfo->bitOpCurrCampPlmnId = pstOtherModemInfoMsg->bitOpCurrCampPlmnId;

    PS_MEM_CPY(&pstMmcLmmOtherModemInfo->stCurrCampPlmnId, &pstOtherModemInfoMsg->stCurrCampPlmnId, sizeof(pstMmcLmmOtherModemInfo->stCurrCampPlmnId));

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMmcLmmOtherModemInfo ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmOtherModemInfoNotify():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMmcLmmOtherModemInfo);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMmcLmmOtherModemInfo);
#endif

    return;
}
#endif


/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmLteSysInfoInd
 功能描述  : 向LTE下发送LTE系统消息的处理
 输入参数  : pstLmmSysInfoMsg: 发送到LMM的LTE的系统消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

修改历史      :
 1.日    期   : 2012年12月20日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmLteSysInfoInd(
    LMM_MMC_SYS_INFO_IND_STRU          *pstLmmSysInfoMsg
)
{
    MMC_LMM_LTE_SYS_INFO_IND_STRU      *pstMmcLmmSysInfoInd = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstMmcLmmSysInfoInd = (MMC_LMM_LTE_SYS_INFO_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_LTE_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMmcLmmSysInfoInd = (MMC_LMM_LTE_SYS_INFO_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_LTE_SYS_INFO_IND_STRU));
#endif

    /* 若分配内存出错,返回*/
    if ( VOS_NULL_PTR == pstMmcLmmSysInfoInd )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmLteSysInfoInd():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMmcLmmSysInfoInd + VOS_MSG_HEAD_LENGTH, 0X0,
               sizeof(MMC_LMM_LTE_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH );

    /* 消息IE项赋值 */
    PS_MEM_CPY(pstMmcLmmSysInfoInd, pstLmmSysInfoMsg, sizeof(MMC_LMM_LTE_SYS_INFO_IND_STRU));

    pstMmcLmmSysInfoInd->ulReceiverPid   = PS_PID_MM;
    pstMmcLmmSysInfoInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMmcLmmSysInfoInd->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMmcLmmSysInfoInd->ulSenderPid     = WUEPS_PID_MMC;
    pstMmcLmmSysInfoInd->ulMsgId         = ID_MMC_LMM_LTE_SYS_INFO_IND;
    pstMmcLmmSysInfoInd->ulLength        = sizeof(MMC_LMM_LTE_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMmcLmmSysInfoInd->ulOpId          = 0;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMmcLmmSysInfoInd ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmLteSysInfoInd():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMmcLmmSysInfoInd);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMmcLmmSysInfoInd);
#endif

    return;
}

#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmBeginSessionNotify
 功能描述  : 向LMM下发送ID_MMC_LMM_BEGIN_SESSION_NOTIFY
 输入参数  : enSessionType - 通知接入层的session type
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

修改历史      :
 1.日    期   : 2014年6月23日
   作    者   : z00161729
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmBeginSessionNotify(
    MMC_LMM_SESSION_TYPE_ENUM_UINT8     enSessionType
)
{
    MMC_LMM_BEGIN_SESSION_NOTIFY_STRU  *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstMsg = (MMC_LMM_BEGIN_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_BEGIN_SESSION_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_BEGIN_SESSION_NOTIFY_STRU));
#endif

    /* 若分配内存出错,返回*/
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmBeginSessionNotify():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0X0,
               sizeof(MMC_LMM_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH );

    /* 消息IE项赋值 */
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = ID_MMC_LMM_BEGIN_SESSION_NOTIFY;
    pstMsg->stMsgHeader.ulLength        = sizeof(MMC_LMM_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enSessionType   = enSessionType;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmBeginSessionNotify():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmEndSessionNotify
 功能描述  : 向LMM下发送ID_MMC_LMM_END_SESSION_NOTIFY
 输入参数  : enSessionType - 通知接入层的session type
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

修改历史      :
 1.日    期   : 2014年6月23日
   作    者   : z00161729
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmEndSessionNotify(
    MMC_LMM_SESSION_TYPE_ENUM_UINT8     enSessionType
)
{
    MMC_LMM_END_SESSION_NOTIFY_STRU    *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstMsg = (MMC_LMM_END_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_END_SESSION_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_END_SESSION_NOTIFY_STRU));
#endif

    /* 若分配内存出错,返回*/
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmEndSessionNotify():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0X0,
               sizeof(MMC_LMM_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH );

    /* 消息IE项赋值 */
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = ID_MMC_LMM_END_SESSION_NOTIFY;
    pstMsg->stMsgHeader.ulLength        = sizeof(MMC_LMM_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enSessionType               = enSessionType;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmEndSessionNotify():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}

#endif

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-19, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmImsVoiceCapChangeNtf
 功能描述  : 向LMM下发送IMS VOICE CAP改变消息的处理
 输入参数  : ucImsVoiceAvail: 当前IMS VOICE是否可用
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

修改历史      :
 1.日    期   : 2013年12月20日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmImsVoiceCapChangeNtf(
    VOS_UINT8       ucImsVoiceAvail
)
{
    MMC_LMM_IMS_VOICE_CAP_CHANGE_NOTIFY_STRU               *pstMmcLmmImsVoiceChgNtf = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstMmcLmmImsVoiceChgNtf = (MMC_LMM_IMS_VOICE_CAP_CHANGE_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_IMS_VOICE_CAP_CHANGE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMmcLmmImsVoiceChgNtf = (MMC_LMM_IMS_VOICE_CAP_CHANGE_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_IMS_VOICE_CAP_CHANGE_NOTIFY_STRU));
#endif

    /* 若分配内存出错,返回*/
    if ( VOS_NULL_PTR == pstMmcLmmImsVoiceChgNtf )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmImsVoiceCapChangeNtf():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMmcLmmImsVoiceChgNtf + VOS_MSG_HEAD_LENGTH, 0X0,
               sizeof(MMC_LMM_IMS_VOICE_CAP_CHANGE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH );

    /* 消息IE项赋值 */
    pstMmcLmmImsVoiceChgNtf->ulReceiverPid   = PS_PID_MM;
    pstMmcLmmImsVoiceChgNtf->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMmcLmmImsVoiceChgNtf->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMmcLmmImsVoiceChgNtf->ulSenderPid     = WUEPS_PID_MMC;
    pstMmcLmmImsVoiceChgNtf->ulMsgId         = ID_MMC_LMM_IMS_VOICE_CAP_CHANGE_NOTIFY;
    pstMmcLmmImsVoiceChgNtf->ulLength        = sizeof(MMC_LMM_IMS_VOICE_CAP_CHANGE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMmcLmmImsVoiceChgNtf->ulOpId          = 0;

    pstMmcLmmImsVoiceChgNtf->enImsVoiceCap   = MMC_LMM_IMS_VOICE_CAP_UNAVAILABLE;

    if (VOS_TRUE == ucImsVoiceAvail)
    {
        pstMmcLmmImsVoiceChgNtf->enImsVoiceCap   = MMC_LMM_IMS_VOICE_CAP_AVAILABLE;
    }

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMmcLmmImsVoiceChgNtf ))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmImsVoiceCapChangeNtf():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMmcLmmImsVoiceChgNtf);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMmcLmmImsVoiceChgNtf);
#endif

    return;
}

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-19, end */

/*lint -restore */

/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmCellSignReportNotify
 功能描述  : 由MMC通知LMM信号质量上报间隔和门限
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

修改历史      :
 1.日    期   : 2014年12月05日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmCellSignReportNotify(VOS_VOID)
{
    /* NAS_MMC_GetMaintainInfo中取出ucSignThreshold和ucMinRptTimerInterval，通知LMM */
    MMC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU   *pstMsg     = VOS_NULL_PTR;
    NAS_MMC_MAINTAIN_CTX_STRU              *pstMainCtx = VOS_NULL_PTR;

    pstMainCtx = NAS_MMC_GetMaintainInfo();

    /* 平台不支持LTE时，不需要给LTE发送ID_MMC_LMM_CELL_SIGN_REPORT_NOTIFY */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmCellSignReportNotify():NORMAL:Platform Not Support LTE");

        /* 返回 */
        return;
    }


#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstMsg = (MMC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU));
#endif

    /* 若分配内存出错,返回*/
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmCellSignReportNotify():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0X0,
               sizeof(MMC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH );

    pstMsg->ucSignThreshold            = pstMainCtx->ucSignThreshold;
    pstMsg->ucMinRptTimerInterval      = pstMainCtx->ucMinRptTimerInterval;

    /* 消息IE项赋值 */
    pstMsg->ulReceiverPid   = PS_PID_MM;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulMsgId         = ID_MMC_LMM_CELL_SIGN_REPORT_NOTIFY;
    pstMsg->ulLength        = sizeof(MMC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmCellSignReportNotify():ERROR:SEND MESSAGE FAILURE");
    }
#else
    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndLmmVoiceDomainChangeInd
 功能描述  : 由MMC通知LMM voice domain发生改变
 输入参数  : enVoiceDomain: 语音优选域
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

修改历史      :
  1.日    期   : 2015年2月2日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmVoiceDomainChangeInd(
    MMC_LMM_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain
)
{
    MMC_LMM_VOICE_DOMAIN_CHANGE_IND_STRU       *pstMsg     = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstMsg = (MMC_LMM_VOICE_DOMAIN_CHANGE_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_VOICE_DOMAIN_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_VOICE_DOMAIN_CHANGE_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_VOICE_DOMAIN_CHANGE_IND_STRU));
#endif

    /* 若分配内存出错,返回*/
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmVoiceDomainChangeInd():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0X0,
               sizeof(MMC_LMM_VOICE_DOMAIN_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH );

    /* 消息IE项赋值 */
    pstMsg->ulReceiverPid   = PS_PID_MM;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulMsgId         = ID_MMC_LMM_VOICE_DOMAIN_CHANGE_IND;
    pstMsg->ulLength        = sizeof(MMC_LMM_VOICE_DOMAIN_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enVoiceDomain   = enVoiceDomain;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* 调用VOS发送原语 */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmVoiceDomainChangeInd():ERROR:SEND MESSAGE FAILURE");
    }
#else
    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}


VOS_VOID NAS_MMC_SndLmmBgSearchHrpdReq(VOS_VOID)
{
    MMC_LMM_BG_SEARCH_HRPD_REQ_STRU    *pstMsg     = VOS_NULL_PTR;

    /* apply for memory */
#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstMsg = (MMC_LMM_BG_SEARCH_HRPD_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_BG_SEARCH_HRPD_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_BG_SEARCH_HRPD_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_BG_SEARCH_HRPD_REQ_STRU));
#endif

    /* apply for memory  error, returns  */
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmBgSearchHrpdReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0X0,
               sizeof(MMC_LMM_BG_SEARCH_HRPD_REQ_STRU) - VOS_MSG_HEAD_LENGTH );

    /* fill message head */
    pstMsg->ulReceiverPid   = PS_PID_MM;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulMsgId         = ID_MMC_LMM_BG_SEARCH_HRPD_REQ;
    pstMsg->ulLength        = sizeof(MMC_LMM_BG_SEARCH_HRPD_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* Call Vos function send message */
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmBgSearchHrpdReq():ERROR:SEND MESSAGE FAILURE");
    }
#else
    /* internal message send */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}


VOS_VOID NAS_MMC_SndLmmStopBgSearchHrpdReq(VOS_VOID)
{
    MMC_LMM_STOP_BG_SEARCH_HRPD_REQ_STRU                   *pstMsg     = VOS_NULL_PTR;

    /* apply for memory */
#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstMsg = (MMC_LMM_STOP_BG_SEARCH_HRPD_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_STOP_BG_SEARCH_HRPD_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_STOP_BG_SEARCH_HRPD_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_STOP_BG_SEARCH_HRPD_REQ_STRU));
#endif

    /* apply for memory  error, returns  */
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmStopBgSearchHrpdReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0X0,
               sizeof(MMC_LMM_STOP_BG_SEARCH_HRPD_REQ_STRU) - VOS_MSG_HEAD_LENGTH );

    /* fill message head */
    pstMsg->ulReceiverPid   = PS_PID_MM;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulMsgId         = ID_MMC_LMM_STOP_BG_SEARCH_HRPD_REQ;
    pstMsg->ulLength        = sizeof(MMC_LMM_STOP_BG_SEARCH_HRPD_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* Call Vos function send message */
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmStopBgSearchHrpdReq():ERROR:SEND MESSAGE FAILURE");
    }
#else
    /* internal message send */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

