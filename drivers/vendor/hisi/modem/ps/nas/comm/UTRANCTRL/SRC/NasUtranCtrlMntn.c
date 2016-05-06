/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasUtranCtrlMntn.c
  版 本 号   : 初稿
  作    者   : w00167002
  生成日期   : 2012年8月16日
  最近修改   :
  功能描述   : UTRANCTRL模块可维可测相关的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2012年8月16日
    作    者   : w00167002
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "NasComm.h"
#include "NasMmlLib.h"
#include "NasUtranCtrlMntn.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_MNTN_C

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SndOmUtranCtrlFsmInfo
 功能描述  : 打印出UTRANCTRL的内部状态信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月15日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_SndOmUtranCtrlFsmInfo( VOS_VOID )
{
    NAS_UTRANCTRL_MNTN_INFO_STRU       *pstMsg;

    pstMsg = (NAS_UTRANCTRL_MNTN_INFO_STRU *)PS_MEM_ALLOC( WUEPS_PID_MMC,
                             sizeof(NAS_UTRANCTRL_MNTN_INFO_STRU) );

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndOmUtranCtrlFsmInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    /* 初始化发送消息 */
    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                (VOS_UINT8)0X00,
                sizeof(NAS_UTRANCTRL_MNTN_INFO_STRU) - VOS_MSG_HEAD_LENGTH );

    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->ulLength        = sizeof(NAS_UTRANCTRL_MNTN_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = NAS_UTRANCTRL_OM_MSG_LOG_FSM_INFO;

    /* 获取UTRANCTRL的内部状态信息 */
    pstMsg->u.stLogFsmInfo.enFsmId                = NAS_UTRANCTRL_GetCurrFsmId();
    pstMsg->u.stLogFsmInfo.ulState                = NAS_UTRANCTRL_FSM_GetCurrState();
    pstMsg->u.stLogFsmInfo.ucSearchedSpecTdMccFlg = NAS_UTRANCTRL_GetSearchedSpecTdMccFlg();
    pstMsg->u.stLogFsmInfo.enCurUtranSwitchMode   = NAS_UTRANCTRL_GetCurUtranSwitchMode();
    pstMsg->u.stLogFsmInfo.enCurrUtranMode        = NAS_UTRANCTRL_GetCurrUtranMode();
    pstMsg->u.stLogFsmInfo.enPreUtranMode         = NAS_UTRANCTRL_GetPreUtranMode();
    pstMsg->u.stLogFsmInfo.ucReplaceMmcMsgFlg     = NAS_UTRANCTRL_GetReplaceMmcMsgFlg();

    DIAG_TraceReport(pstMsg);

    /* 释放动态申请的内存 */
    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SndOmUtranModeAutoSwitchInfo
 功能描述  : 打印出用户配置的UTRAN模式切换信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月15日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_SndOmUtranModeAutoSwitchInfo( VOS_VOID )
{
    NAS_UTRANCTRL_MNTN_INFO_STRU                           *pstMsg;
    NAS_UTRANCTRL_UTRAN_MODE_AUTO_SWITCH_STRU              *pstUtranModeAutoSwitch;

    pstUtranModeAutoSwitch = NAS_UTRANCTRL_GetUtranModeAutoSwtich();
    pstMsg = (NAS_UTRANCTRL_MNTN_INFO_STRU *)PS_MEM_ALLOC( WUEPS_PID_MMC,
                             sizeof(NAS_UTRANCTRL_MNTN_INFO_STRU) );

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndOmUtranModeAutoSwitchInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    /* 初始化发送消息 */
    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                (VOS_UINT8)0X00,
                sizeof(NAS_UTRANCTRL_MNTN_INFO_STRU) - VOS_MSG_HEAD_LENGTH );

    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->ulLength        = sizeof(NAS_UTRANCTRL_MNTN_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = NAS_UTRANCTRL_OM_MSG_LOG_UTRAN_MODE_AUTO_SWITCH_INFO;


    /* 获取内部用户配置的EHplmn信息 */
    PS_MEM_CPY( &(pstMsg->u.stUtranModeAutoSwitch),
                pstUtranModeAutoSwitch,
                sizeof(NAS_UTRANCTRL_UTRAN_MODE_AUTO_SWITCH_STRU) );

    DIAG_TraceReport(pstMsg);

    /* 释放动态申请的内存 */
    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SndOmBufferQueueMsg
 功能描述  : 导出缓存消息队列消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月7日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_SndOmBufferQueueMsg(VOS_VOID)
{
    NAS_UTRANCTRL_MNTN_INFO_STRU       *pstMsg;
    NAS_UTRANCTRL_MSG_QUEUE_STRU       *pstMsgQueue;

    pstMsgQueue     = NAS_UTRANCTRL_GetCachMsgBufferAddr();
    pstMsg          = (NAS_UTRANCTRL_MNTN_INFO_STRU *)PS_MEM_ALLOC( WUEPS_PID_MMC,
                             sizeof(NAS_UTRANCTRL_MNTN_INFO_STRU) );

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndOmUtranCtrlFsmInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    /* 初始化发送消息 */
    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                (VOS_UINT8)0X00,
                sizeof(NAS_UTRANCTRL_MNTN_INFO_STRU) - VOS_MSG_HEAD_LENGTH );

    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->ulLength        = sizeof(NAS_UTRANCTRL_MNTN_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = NAS_UTRANCTRL_OM_MSG_LOG_MSG_QUEUE_INFO;

    /* 获取内部队列信息 */
    PS_MEM_CPY( &(pstMsg->u.stBufferEntryMsgQueue),
                pstMsgQueue,
                sizeof(NAS_UTRANCTRL_MSG_QUEUE_STRU) );

    DIAG_TraceReport(pstMsg);

    /* 释放动态申请的内存 */
    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return ;
}
#endif /* END OF #if (FEATURE_ON == FEATURE_UE_MODE_TDS) */


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SndOutsideContextData
 功能描述  : 把UTRANCTRL外部上下文作为SDT消息发送出去，以便在回放时通过桩函数还原
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月7日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SndOutsideContextData( VOS_VOID )
{
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    VOS_UINT8                                              *pucCompressBuf;
    NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU                *pstPcreplayCompressCtx;
    VOS_UINT32                                              ulCompressDataLen;
    VOS_UINT32                                              ulCount;
    VOS_UINT8                                              *pucEndBuf;
    VOS_UINT32                                              ulItemCount;
    VOS_UINT8                                              *pucDest;
    VOS_UINT8                                              *pucSrc;
    VOS_UINT32                                              ulCmLen;

    ulCount     = sizeof(NAS_UTRANCTRL_CTX_STRU);

    ulItemCount = 0;

    ulCompressDataLen  = NAS_MML_PC_RECUR_COMPRESS_DATA_LEN;
    pucCompressBuf     = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_MMC, ulCompressDataLen);

    if (VOS_NULL_PTR == pucCompressBuf)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_UTRANCTRL_SndOutsideContextData: Alloc Fail.");
        return;
    }

    pstPcreplayCompressCtx = (NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU *)pucCompressBuf;

    /* 获取buf结尾地址，用于计算剩余空间*/
    pucEndBuf = pucCompressBuf + ulCompressDataLen;

    /* 压缩 fix data */
    pucDest  = pstPcreplayCompressCtx->aucData;

    /* 原始数据大小 */
    PS_MEM_CPY(pucDest, &ulCount, sizeof(VOS_UINT32));
    pucDest += sizeof(VOS_UINT32);

    /* 压缩UTRANCTRL context g_stNasUtranCtrlCtx*/
    pucSrc      = (VOS_UINT8 *)NAS_UTRANCTRL_GetUtranCtrlCtx();
    ulItemCount = sizeof(NAS_UTRANCTRL_CTX_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen , pucSrc , ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pucCompressBuf);
        return;
    }

    pucDest += (ulCmLen);

    ulCompressDataLen = (VOS_UINT32)(pucDest - (VOS_UINT8 *)pstPcreplayCompressCtx);

    pstPcreplayCompressCtx->ulReceiverPid      = WUEPS_PID_MMC;
    pstPcreplayCompressCtx->ulSenderPid        = WUEPS_PID_MMC;
    pstPcreplayCompressCtx->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstPcreplayCompressCtx->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstPcreplayCompressCtx->ulLength           = ulCompressDataLen;
    pstPcreplayCompressCtx->ulMsgName          = NAS_UTRANCTRL_OM_MSG_LOG_RUNNING_CONTEXT_FOR_PC_REPLAY;

    DIAG_TraceReport(pstPcreplayCompressCtx);

    PS_MEM_FREE(WUEPS_PID_MMC, pucCompressBuf);
#endif
    return;

}




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
