/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcSndOm.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2010年5月9日
  最近修改   :
  功能描述   : MMC发给OM的消息的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2011年05月9日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "NasComm.h"

#include "NasMmcSndOm.h"
#include "MM_Ext.h"
#include "GmmExt.h"
#include "NasMmcPlmnSelectionStrategy.h"
#include "NasMmcCtx.h"
#include "NasMmcProcUsim.h"

/* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, begin */
#include  "NasMmlCtx.h"
/* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, end */

#include "NasMmcFsmMainTbl.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_SND_OM_C

/*****************************************************************************
  2 全局变量
*****************************************************************************/
/*****************************************************************************
  3 宏定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : NAS_MMC_LogMmcState
 功能描述  : 打印出MMC的内部状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年1月13日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_LogMmcFsmInfo( VOS_VOID )
{
    NAS_MMC_LOG_FSM_INFO_STRU           *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_MMC_LOG_FSM_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                             sizeof(NAS_MMC_LOG_FSM_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogMmcFsmInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MMC_LOG_FSM_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_FSM_INFO_IND;
    pstMsg->enFsmId                     = NAS_MMC_GetCurrFsmId();
    pstMsg->ulTopState                  = NAS_MMC_GetFsmTopState();

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}

#if (FEATURE_LTE == FEATURE_ON)
/*****************************************************************************
 函 数 名  : NAS_MMC_LogGutiInfo
 功能描述  : 通过Trace显示从同步接口获取的GUTI相关信息
 输入参数  : NAS_LMM_GUTI_STRU                    stGutiMsg
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_LogGutiInfo(
    NAS_LMM_GUTI_STRU                  *pstGuti
)
{
    NAS_MMC_LOG_GUTI_INFO_STRU         *pstGutiMsg = VOS_NULL_PTR;

    pstGutiMsg = (NAS_MMC_LOG_GUTI_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                             sizeof(NAS_MMC_LOG_GUTI_INFO_STRU));
    if ( VOS_NULL_PTR == pstGutiMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_MMC_LogGutiInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstGutiMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstGutiMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstGutiMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstGutiMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstGutiMsg->stMsgHeader.ulLength        = sizeof(NAS_MMC_LOG_GUTI_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstGutiMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_GUTI_INFO_IND;

    PS_MEM_CPY(&(pstGutiMsg->stGutiMsg), pstGuti, sizeof(NAS_LMM_GUTI_STRU));

    DIAG_TraceReport(pstGutiMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstGutiMsg);

    return;
}
#endif


/*****************************************************************************
 函 数 名  : NAS_MMC_LogBufferQueueMsg
 功能描述  : 导出缓存的消息
 输入参数  : ulFullFlg:缓存是否已经满的标志位
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月7日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_LogBufferQueueMsg(
    VOS_UINT32                          ulFullFlg
)
{
    NAS_MMC_LOG_BUffER_MSG_INFO_STRU    *pstBufferMsg = VOS_NULL_PTR;
    NAS_MMC_MSG_QUEUE_STRU              *pstMsgQueue  = VOS_NULL_PTR;

    pstBufferMsg = (NAS_MMC_LOG_BUffER_MSG_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                             sizeof(NAS_MMC_LOG_BUffER_MSG_INFO_STRU));
    if ( VOS_NULL_PTR == pstBufferMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_MMC_LogBufferQueueMsg:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsgQueue                               = NAS_MMC_GetCachMsgBufferAddr();
    pstBufferMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstBufferMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstBufferMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstBufferMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstBufferMsg->stMsgHeader.ulLength        = sizeof(NAS_MMC_LOG_BUffER_MSG_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBufferMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_BUFFER_MSG_INFO_IND;
    pstBufferMsg->ulFullFlg                   = ulFullFlg;
    PS_MEM_CPY(&(pstBufferMsg->stMsgQueue), pstMsgQueue, sizeof(pstBufferMsg->stMsgQueue));

    DIAG_TraceReport(pstBufferMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstBufferMsg);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndOutsideFixedContextData
 功能描述  : 把MMC外部固定变量上下文作为SDT消息发送出去，以便在回放时通过桩函数还原
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年05月11日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数
  2.日    期   : 2009年08月11日
    作    者   : 欧阳飞 00132663
    修改内容   : AT2D13441, 增加g_MmcGlobalCtrl.ucLastRplmnRatEnableFlag变量导出
  3.日    期   : 2011年07月14日
    作    者   : z00161729
    修改内容   : V7R1 phase II全局变量调整修改
  4.日    期   : 2011年07月20日
    作    者   : zhoujun \40661
    修改内容   : V7R1 phase II全局变量调整修改
  5.日    期   : 2011年12月1日
    作    者   : z00161729
    修改内容   : 增加pc 回放压缩
  6.日    期   : 2012年3月1日
    作    者   : z00161729
    修改内容   : DTS2012012902207:msg hook后内存未释放

*****************************************************************************/
VOS_VOID NAS_MMC_SndOutsideFixedContextData( VOS_VOID )
{
    NAS_MMC_FIXED_CONTEXT_MSG_STRU                         *pstFixedCtx;
    NAS_MML_CTX_STRU                                       *pstMmlCtx;
    NAS_MMC_CONTEXT_STRU                                   *pstMmcCtx;
    VOS_UINT8                                              *pucCompressBuf;
    NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU                *pstPcreplayCompressCnt;
    VOS_UINT32                                              ulCompressDataLen;
    VOS_UINT32                                              ulCount;
    VOS_UINT8                                              *pucEndBuf;
    VOS_UINT32                                              ulItemCount;
    VOS_UINT8                                              *pucDest;
    VOS_UINT8                                              *pucSrc;
    VOS_UINT32                                              ulCmLen;

    ulCount = sizeof(NAS_MMC_FIXED_CONTEXT_MSG_STRU);
    ulItemCount = 0;

    pstFixedCtx = (NAS_MMC_FIXED_CONTEXT_MSG_STRU *)PS_ALLOC_MSG
                         (WUEPS_PID_MMC, sizeof(NAS_MMC_FIXED_CONTEXT_MSG_STRU));

    if ( VOS_NULL_PTR == pstFixedCtx )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOutsideFixedContextData:ERROR: Alloc Memory Fail.");
        return;
    }

    ulCompressDataLen  = NAS_MML_PC_RECUR_COMPRESS_DATA_LEN;
    pucCompressBuf     = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_MMC, ulCompressDataLen);

    if (VOS_NULL_PTR == pucCompressBuf)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOutsideFixedContextData: Alloc Fail.");
        PS_FREE_MSG(WUEPS_PID_MMC, pstFixedCtx);
        return;
    }

    pstPcreplayCompressCnt = (NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU *)pucCompressBuf;

    /* 获取buf结尾地址，用于计算剩余空间*/
    pucEndBuf = (VOS_UINT8 *)(pucCompressBuf + ulCompressDataLen);

    /* 压缩 fix data */
    pucDest  = pstPcreplayCompressCnt->aucData;

    /* 原始数据大小 */
    PS_MEM_CPY(pucDest, &ulCount, sizeof(VOS_UINT32));
    pucDest += sizeof(VOS_UINT32);

    pstMmlCtx  =  NAS_MML_GetMmlCtx();
    pstMmcCtx  =  NAS_MMC_GetMmcCtxAddr();

    /* 保存IMEI的内容 */
    PS_MEM_CPY(pstFixedCtx->aucImeisv,
               pstMmlCtx->stMsCfgInfo.stMsCapability.aucImeisv,
               NAS_MML_MAX_IMEISV_LEN);

    /* 保存搜网模式 */
    pstFixedCtx->enSelectionMode = pstMmcCtx->stPlmnSearchCtrl.enSelectionMode;

    pstFixedCtx->ucPsAutoAttachFlg = pstMmlCtx->stMsCfgInfo.stMsSysCfgInfo.ucPsAutoAttachFlg;

    /* 保存等效PLMN */
    PS_MEM_CPY(&(pstFixedCtx->stEquPlmnInfo),
               &(pstMmlCtx->stNetworkInfo.stEquPlmnInfo),
               sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    /* 保存等效RPLMN相关定制 */
    PS_MEM_CPY(&(pstFixedCtx->stRplmnCfg),
               &(pstMmlCtx->stMsCfgInfo.stCustomCfg.stRplmnCfg),
               sizeof(NAS_MML_RPLMN_CFG_INFO_STRU));

    /* 保存网络能力 */
    pstFixedCtx->stMsNetworkCapability.ucNetworkCapabilityLen = pstMmlCtx->stMsCfgInfo.stMsCapability.stMsNetworkCapability.ucNetworkCapabilityLen;

    if (pstFixedCtx->stMsNetworkCapability.ucNetworkCapabilityLen > NAS_MML_MAX_NETWORK_CAPABILITY_LEN)
    {
        pstFixedCtx->stMsNetworkCapability.ucNetworkCapabilityLen  = NAS_MML_MAX_NETWORK_CAPABILITY_LEN;
    }
    PS_MEM_CPY(pstFixedCtx->stMsNetworkCapability.aucNetworkCapability,
               pstMmlCtx->stMsCfgInfo.stMsCapability.stMsNetworkCapability.aucNetworkCapability,
               NAS_MML_MAX_NETWORK_CAPABILITY_LEN);


    /* 保存BG搜网相关信息 */
    PS_MEM_CPY(&(pstFixedCtx->stBGSrchCfg),
               &(pstMmlCtx->stMsCfgInfo.stCustomCfg.stBgSearchCfg),
               sizeof(NAS_MML_BG_SEARCH_CFG_INFO_STRU));

    /* NV项的恢复,恢复快速开机 */
    pstFixedCtx->ulQuickStartFlag = NAS_MML_IsQuickStartFlg();


    /* 压缩NAS_MMC_FIXED_CONTEXT_MSG_STRU */
    pucSrc      = (VOS_UINT8 *)pstFixedCtx;
    ulItemCount = sizeof(NAS_MMC_FIXED_CONTEXT_MSG_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen , pucSrc , ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pucCompressBuf);
        PS_FREE_MSG(WUEPS_PID_MMC, pstFixedCtx);
        return;
    }
    pucDest          += (ulCmLen);
    ulCompressDataLen = (VOS_UINT32)(pucDest - (VOS_UINT8 *)pstPcreplayCompressCnt);

    pstPcreplayCompressCnt->ulReceiverPid      = WUEPS_PID_MMC;
    pstPcreplayCompressCnt->ulSenderPid        = WUEPS_PID_MMC;
    pstPcreplayCompressCnt->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstPcreplayCompressCnt->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstPcreplayCompressCnt->ulLength           = ulCompressDataLen;
    pstPcreplayCompressCnt->ulMsgName          = MMCOM_FIXED_PART_CONTEXT;
    DIAG_TraceReport(pstPcreplayCompressCnt);

    PS_MEM_FREE(WUEPS_PID_MMC, pucCompressBuf);
    PS_FREE_MSG(WUEPS_PID_MMC, pstFixedCtx);

}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndOutsideContextData
 功能描述  : 把MMC外部上下文作为SDT消息发送出去，以便在回放时通过桩函数还原
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年01月03日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数

  2.日    期   : 2011年4月22日
    作    者   : zhoujun /40661
    修改内容   : V7R1 Phase I删除相关结构
*****************************************************************************/
VOS_VOID NAS_MMC_SndOutsideContextData( VOS_VOID )
{
    VOS_UINT8                                              *pucCompressBuf;
    NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU                *pstPcreplayCompressCtx;
    VOS_UINT32                                              ulCompressDataLen;
    VOS_UINT32                                              ulCount;
    VOS_UINT8                                              *pucEndBuf;
    VOS_UINT32                                              ulItemCount;
    VOS_UINT8                                              *pucDest;
    VOS_UINT8                                              *pucSrc;
    VOS_UINT32                                              ulCmLen;

    ulCount     = sizeof(NAS_MML_CTX_STRU)
                + sizeof(MM_SUB_LAYER_SHARE_STRU)
                + sizeof(NAS_MMC_CONTEXT_STRU)
                + sizeof(TAF_PLMN_ID_STRU);  /* 需要备份 g_stSetRplmn，用于PC回放 */

    ulItemCount = 0;

    ulCompressDataLen  = NAS_MML_PC_RECUR_COMPRESS_DATA_LEN;
    pucCompressBuf     = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_MMC, ulCompressDataLen);

    if(VOS_NULL_PTR == pucCompressBuf)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_SndOutsideContextData: Alloc Fail.");
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

    /* 压缩MML context g_stNasMmlCtx*/
    pucSrc      = (VOS_UINT8 *)NAS_MML_GetMmlCtx();
    ulItemCount = sizeof(NAS_MML_CTX_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen , pucSrc , ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* 压缩g_MmSubLyrShare */
    pucSrc      = (VOS_UINT8 *)&g_MmSubLyrShare;
    ulItemCount = sizeof(MM_SUB_LAYER_SHARE_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* 压缩MMC context g_stNasMmcCtx */
    pucSrc      = (VOS_UINT8 *)NAS_MMC_GetMmcCtxAddr();
    ulItemCount = sizeof(NAS_MMC_CONTEXT_STRU);

    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/

    if( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

#if (FEATURE_ON == FEATURE_LTE)
#ifdef WIN32
	/* PC工程需要备份g_stSetRplmn用于回放 */
    PS_MEM_CPY(pucDest,&g_stSetRplmn,sizeof(TAF_PLMN_ID_STRU));
#endif
#endif
    pucDest += sizeof(TAF_PLMN_ID_STRU);

    ulCompressDataLen = (VOS_UINT32)(pucDest - (VOS_UINT8 *)pstPcreplayCompressCtx);

    pstPcreplayCompressCtx->ulReceiverPid      = WUEPS_PID_MMC;
    pstPcreplayCompressCtx->ulSenderPid        = WUEPS_PID_MMC;
    pstPcreplayCompressCtx->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstPcreplayCompressCtx->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstPcreplayCompressCtx->ulLength           = ulCompressDataLen;
    pstPcreplayCompressCtx->ulMsgName          = MMCOM_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY;
    DIAG_TraceReport(pstPcreplayCompressCtx);


    PS_MEM_FREE(WUEPS_PID_MMC, pucCompressBuf);

}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndOmOtaCnf
 功能描述  : 发送OM的请求消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月21日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

 2.日    期   : 2012年11月1日
   作    者   : z40661
   修改内容   : DTS2012102501504

 3.日    期   : 2013年04月02日
   作    者   : m00217266
   修改内容   : DTS2013041202045&DTS2013040104447

 3.日    期   : 2015年07月01日
   作    者   : wx270776
   修改内容   : OM融合

*****************************************************************************/
VOS_VOID NAS_MMC_SndOmOtaCnf(
    VOS_UINT32                          ulErrCode,
    OM_NAS_OTA_REQ_STRUCT              *pstOtaReq
)
{
    /* Modified by wx270776 for OM融合, 2015-7-1, begin */
    VOS_UINT16                          usNasOtaCnfLen;
    NAS_OM_OTA_CNF_STRUCT              *pstNasOtaCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* 申请内存 */
    usNasOtaCnfLen = sizeof(NAS_OM_OTA_CNF_STRUCT) - VOS_MSG_HEAD_LENGTH;

    pstNasOtaCnf   = (NAS_OM_OTA_CNF_STRUCT *)PS_ALLOC_MSG(WUEPS_PID_MMC, usNasOtaCnfLen);
    if ( VOS_NULL_PTR == pstNasOtaCnf )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_RcvOmOtaReq:WARNING: Alloc Memory Fail.");
        return;
    }

    /* 初始化 */
    PS_MEM_SET((VOS_UINT8*)pstNasOtaCnf + VOS_MSG_HEAD_LENGTH, 0x00, usNasOtaCnfLen);

    /* 填写消息内容 */
    pstNasOtaCnf->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
    pstNasOtaCnf->ulMsgId          = NAS_OM_OTA_CNF;
    pstNasOtaCnf->usOriginalId     = pstOtaReq->usOriginalId;
    pstNasOtaCnf->usTerminalId     = pstOtaReq->usTerminalId;
    pstNasOtaCnf->ulTimeStamp      = pstOtaReq->ulTimeStamp;
    pstNasOtaCnf->ulSN             = pstOtaReq->ulSN;

    pstNasOtaCnf->ulErrCode        = ulErrCode;

    /* 发送消息 */
    ulRet = PS_SEND_MSG(WUEPS_PID_MMC, pstNasOtaCnf);
    if (VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOmOtaCnf:WARNING: Send msg fail.");
    }
    else
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOmOtaCnf: NAS_OM_OTA_CNF has been sent.");
    }

    return;
    /* Modified by wx270776 for OM融合, 2015-7-1, end */

}

/*****************************************************************************
 函 数 名  : NAS_MMC_FillNasMmImsiInfo
 功能描述  : 填充OM查询消息的IMSI项
 输入参数  : 无
 输出参数  : pstMsIdMsg:当前IMSI内容
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月23日
   作    者   : zhoujun \40661
   修改内容   : 新生成函数
 2.日    期   : 2012年8月10日
   作    者   : L00171473
   修改内容   : DTS2012082204471, TQE清理

 3.日    期   : 2014年6月17日
   作    者   : z00234330
   修改内容   : PCINT清理
*****************************************************************************/
VOS_VOID NAS_MMC_FillNasMmImsiInfo(
    MS_ID_STRUCT                       *pstMsIdMsg
)
{
    VOS_UINT8                           i = 0;
    VOS_UINT8                           j = 0;
    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity;

    pstMsIdentity           = NAS_MML_GetSimMsIdentity();

    /* SIM卡不在位 */
    if ( VOS_FALSE == NAS_MML_GetSimPresentStatus())
    {
        pstMsIdMsg->ucLength        = 0;
        return ;
    }

    pstMsIdMsg->ucLength            = 15;
    pstMsIdMsg->ucMobileIDValue[0]  = (pstMsIdentity->aucImsi[1] & 0xF0) >> 4;

    i   = 1;
    j   = 2;

    for ( ; (i < pstMsIdMsg->ucLength) && (j < 9); i++)
    {
        if ( (2 * i) >= LEN_MOBILE )
        {
            break;
        }

        pstMsIdMsg->ucMobileIDValue[(2 * i) - 1]
                    = pstMsIdentity->aucImsi[j] & 0x0F;
        /* Modified by z00234330 for PCLINT清理, 2014-06-16, begin */
        pstMsIdMsg->ucMobileIDValue[2 * i]
                    = pstMsIdentity->aucImsi[j] >> 4;
        j++;
        /* Modified by z00234330 for PCLINT清理, 2014-06-16, end */
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_FillNasSimUpdateStatusInfo
 功能描述  : 填充OM查询消息的卡的更新状态,包括CS域和PS域的
 输入参数  : 无
 输出参数  : pstMsg:更新后的卡状态
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月23日
   作    者   : zhoujun \40661
   修改内容   : 新生成函数
 2.日    期   : 2014年6月16日
   作    者   : w00176964
   修改内容   : DTS2014061006131:MM增加新的U值
 3.日    期   : 2015年9月17日
   作    者   : zwx247453
   修改内容   : Dallas寄存器按原语上报及BBP采数项目

*****************************************************************************/
VOS_VOID NAS_MMC_FillNasSimUpdateStatusInfo(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus;

    pstSimStatus                = NAS_MML_GetSimStatus();

    /* 填写PS域的卡状态 */
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, begin */
    switch (pstSimStatus->enPsUpdateStatus)
    {
        case NAS_MML_ROUTING_UPDATE_STATUS_UPDATED:
            pstMsg->enGmmUpdateStatus   = UPDATE_STATUS_GU1;
            break;

        case NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED:
            pstMsg->enGmmUpdateStatus   = UPDATE_STATUS_GU2;
            break;

        case NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED:
        case NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED:
            pstMsg->enGmmUpdateStatus   = UPDATE_STATUS_GU3;
            break;

        default:
            pstMsg->enGmmUpdateStatus   = GMM_UPDATE_STATUS_BUTT;
            break;
    }

    /* 填写CS域的卡状态 */
    switch (pstSimStatus->enCsUpdateStatus)
    {
        case NAS_MML_LOCATION_UPDATE_STATUS_UPDATED:
            pstMsg->enMmUpdateStatus    = UPDATE_STATUS_U1;
            break;

        case NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED:
            pstMsg->enMmUpdateStatus    = UPDATE_STATUS_U2;
            break;

        case NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED:
        case NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED:
            pstMsg->enMmUpdateStatus    = UPDATE_STATUS_U3;
            break;

        case NAS_MML_LOCATION_UPDATE_DISABLED:
            pstMsg->enMmUpdateStatus    = UPDATE_STATUS_U4;
            break;

        default:
            pstMsg->enMmUpdateStatus    = MM_UPDATE_STATUS_BUTT;
            break;
    }
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, end */
}

/*****************************************************************************
 函 数 名  : NAS_MMC_FillNasMmSimInfo
 功能描述  : 填充OM查询消息的SIM卡信息项
 输入参数  : 无
 输出参数  : pstMsg:当前查询内容
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月23日
   作    者   : zhoujun \40661
   修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID NAS_MMC_FillNasMmSimInfo(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    VOS_UINT8                           i;
    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity;

    pstMsIdentity           = NAS_MML_GetSimMsIdentity();

    /* 填写PTMSI的内容 */
    for (i = 0; i < LEN_PTMSI; i++)
    {
        pstMsg->ucPtmsi[i]  = pstMsIdentity->aucPtmsi[i];
    }

    /* 填写TMSI的内容 */
    for (i = 0; i < LEN_TMSI; i++)
    {
        pstMsg->aucTmsi[i]  = pstMsIdentity->aucTmsi[i];
    }

    /* 填写IMSI的内容 */
    NAS_MMC_FillNasMmImsiInfo(&(pstMsg->IMSI));

    /* 填写卡更新状态 */
    NAS_MMC_FillNasSimUpdateStatusInfo(pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertNetworkModeToOm
 功能描述  : 将内部的网络模式信息转换为显示给OM的网络信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月12日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_ConvertNetworkModeToDispalyFormat(
    NAS_MML_NET_MODE_ENUM_UINT8         enNetworkMode,
    NET_OPERATE_MODE_ENUM_UINT8        *penNetOperateMode

)
{
    if ( NAS_MML_NET_MODE_I == enNetworkMode )
    {
        *penNetOperateMode = NET_OPERATE_MODE_1;
    }
    else if ( NAS_MML_NET_MODE_II == enNetworkMode )
    {
        *penNetOperateMode = NET_OPERATE_MODE_2;
    }
    else if ( NAS_MML_NET_MODE_III == enNetworkMode )
    {
        *penNetOperateMode = NET_OPERATE_MODE_3;
    }
    else
    {
        *penNetOperateMode = NET_OPERATE_MODE_BUTT;
    }
}


/* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, begin */

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPlmnHUOType
 功能描述  : 返回PLMN的时HUO中的哪种
 输入参数  : pstPlmn,指向PLMN的指针
 输出参数  : 无
 返 回 值  : PLMN的类型
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年06月27日
   作    者   : luokaihui 00167671
   修改内容   : 新生成函数
 2.日    期   : 2013年09月03日
   作    者   : w00242748
   修改内容   : DTS2013082909799 查询NAS MM QUERY时，RPLMN显示成EHPLMN，关机时
                无效PLMN显示为OPLMN修正。
 3.日    期    : 2013年11月26日
   作    者    : s00190137
   修改内容    : 将最大支持设置的OPLMN扩展到256个
 4.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
*****************************************************************************/
NAS_OM_PLMN_HUO_TYPE_ENUM_UINT32 NAS_MMC_GetPlmnHUOType(NAS_MML_PLMN_ID_STRU *pstPlmn)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                             *pstCampPlmnInfo;
    NAS_MML_PLMN_ID_STRU                                     stRPlmnId;

    if (VOS_FALSE == NAS_MML_IsPlmnIdValid(pstPlmn))
    {
        return NAS_MMC_HUO_INVALID_PLMN;
    }

    /* 获取RPLMN配置信息 */
    pstCampPlmnInfo         = NAS_MML_GetCurrCampPlmnInfo();

    if (VOS_TRUE == NAS_MMC_GetRPlmn_PlmnSelectionStrategy(pstCampPlmnInfo->enNetRatType, &stRPlmnId))
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmn, &stRPlmnId))
        {
            return NAS_MMC_HUO_RPLMN;
        }
    }

    /* 检查是否是HOME PLMN */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(pstPlmn))
    {
        return NAS_MMC_HUO_HPLMN;
    }

    /* Modified by s00246516 for L-C互操作项目, 2014-02-12, Begin */
    /* 检查是否是 UPLMN */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithUplmn(pstPlmn))
    {
        return NAS_MMC_HUO_UPLMN;
    }

    /* 检查是否是 OPLMN */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithOplmn(pstPlmn))
    {
        return NAS_MMC_HUO_OPLMN;
    }
    /* Modified by s00246516 for L-C互操作项目, 2014-02-12, End */

    /* 其他PLMN */
    return NAS_MMC_HUO_OTHER_PLMN;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_FillNasTinInfo
 功能描述  : 填充OM查询消息的Tin Type和相应的GUTI或者PTMSI
 输入参数  : 无
 输出参数  : pstMsg:当前查询内容
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年06月27日
   作    者   : luokaihui 00167671
   修改内容   : 新生成函数

  2.日    期   : 2013年9月30日
    作    者   : z00234330
    修改内容   : dts2013090407261,关机时,调用此接口导致踩内存
  3.日    期   : 2013年11月30日
    作    者   : l65478
    修改内容   : DTS2013112400009,不查主卡,打开SDT中的MM STATE页面C核复位
*****************************************************************************/

VOS_VOID NAS_MMC_FillNasTinInfo(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_LMM_INFO_STRU                   stLmmInfo;

    NAS_MMC_FSM_ID_ENUM_UINT32  enFsmId;
    VOS_UINT32                  ucMmcTopState;
    VOS_UINT8                   aucPtmsiAddr[20];

    PS_MEM_SET(&stLmmInfo, 0, sizeof(NAS_LMM_INFO_STRU));
    PS_MEM_SET(aucPtmsiAddr, 0x00, sizeof(aucPtmsiAddr));
    pstMsg->enTinType     = NAS_MML_GetTinType();
    pstMsg->stMsId.ulMsId = 0;


    enFsmId         = (VOS_UINT8)NAS_MMC_GetCurrFsmId();
    ucMmcTopState   = (VOS_UINT8)NAS_MMC_GetFsmTopState();


    /*关机状态下返回无效值,不能调用NAS_Gmm_FillPtmsiIeForSnd这个接口*/
    if ( ( NAS_MMC_FSM_L1_MAIN == enFsmId )
      && ( NAS_MMC_L1_STA_NULL == ucMmcTopState ))
    {
        pstMsg->stMsId.ulMsId = 0;
        PS_MEM_SET(&(pstMsg->stMsId.stGuti),0xFF,sizeof(pstMsg->stMsId.stGuti));
        PS_MEM_SET(&(pstMsg->stMsId.stPtmsi),0xFF,sizeof(pstMsg->stMsId.stPtmsi));
        PS_MEM_SET((pstMsg->stMsId.aucImsi),0x00,sizeof(pstMsg->stMsId.aucImsi));

        return;
    }

    if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
    {
        return;
    }

    /* 根据TIN TYPE的值填写相应的TIN值 */
    if (NAS_MML_TIN_TYPE_PTMSI == pstMsg->enTinType)
    {
        (VOS_VOID)NAS_Gmm_FillPtmsiIeForSnd(aucPtmsiAddr);
        PS_MEM_CPY((pstMsg->stMsId).stPtmsi.aucPtmsi,&aucPtmsiAddr[2],NAS_MAX_SIZE_PTMSI);
        pstMsg->stMsId.ulMsId |= NAS_MS_ID_PTMSI_IMSI_VALID;
    }
    else if (NAS_MML_TIN_TYPE_GUTI == pstMsg->enTinType)
    {
        if ( VOS_TRUE == NAS_GMM_GetLteInfo( NAS_LMM_GUTI, &stLmmInfo ) )
        {
            PS_MEM_CPY(&(pstMsg->stMsId.stGuti), &(stLmmInfo.u.stGuti), sizeof(NAS_LMM_GUTI_STRU));
            pstMsg->stMsId.ulMsId |= NAS_MS_ID_GUTI_VALID;
        }
    }
    else if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == pstMsg->enTinType)
    {
        (VOS_VOID)NAS_Gmm_FillPtmsiIeForSnd(aucPtmsiAddr);
        PS_MEM_CPY((pstMsg->stMsId).stPtmsi.aucPtmsi,&aucPtmsiAddr[2],NAS_MAX_SIZE_PTMSI);
        pstMsg->stMsId.ulMsId |= NAS_MS_ID_PTMSI_IMSI_VALID;

        if ( VOS_TRUE == NAS_GMM_GetLteInfo( NAS_LMM_GUTI, &stLmmInfo ) )
        {
            PS_MEM_CPY(&(pstMsg->stMsId.stGuti), &(stLmmInfo.u.stGuti), sizeof(NAS_LMM_GUTI_STRU));
            pstMsg->stMsId.ulMsId |= NAS_MS_ID_GUTI_VALID;
        }
    }
    else if (NAS_MML_TIN_TYPE_INVALID == pstMsg->enTinType)
    {
        (VOS_VOID)NAS_Gmm_FillPtmsiIeForSnd(aucPtmsiAddr);
        PS_MEM_CPY((pstMsg->stMsId).stPtmsi.aucPtmsi,&aucPtmsiAddr[2],NAS_MAX_SIZE_PTMSI);
        pstMsg->stMsId.ulMsId |= NAS_MS_ID_PTMSI_IMSI_VALID;
    }
    else
    {
    }

#else
/*
    pstMsg->enTinType     = NAS_MML_TIN_TYPE_BUTT;
    pstMsg->stMsId.ulMsId = 0;
    NAS_Gmm_FillPtmsiIeForSnd( (pstMsg->stMsId).stPtmsi.aucPtmsi );
    pstMsg->stMsId.ulMsId |= NAS_MS_ID_PTMSI_IMSI_VALID;
    */
#endif
}
/* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, end */

/*****************************************************************************
 函 数 名  : NAS_MMC_FillNasMsNetworkInfo
 功能描述  : 填充OM查询消息的网络信息项
 输入参数  : 无
 输出参数  : pstMsg:当前查询内容
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月23日
   作    者   : zhoujun \40661
   修改内容   : 新生成函数

 2.日    期   : 2011年11月12日
   作    者   : zhoujun 40661
   修改内容   : 网络模式OM显示不正确,修改
 3.日    期   : 2013年06月27日
   作    者   : luokaihui 00167671
   修改内容   : 添加网络优先级
 4.日    期   : 2015年9月17日
   作    者   : zwx247453
   修改内容   : Dallas寄存器按原语上报及BBP采数项目
*****************************************************************************/

VOS_VOID NAS_MMC_FillNasMsNetworkInfo(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo;

    pstCampPlmnInfo         = NAS_MML_GetCurrCampPlmnInfo();

    /* 驻留网络信息 */


    pstMsg->ucRac           = pstCampPlmnInfo->ucRac;
    pstMsg->usLac           = ((pstCampPlmnInfo->stLai.aucLac[0] << 8) | (pstCampPlmnInfo->stLai.aucLac[1]));

    /* 搜网模式信息 */
    pstMsg->enPlmnSelMode   = NAS_MMC_GetPlmnSelectionMode();

    /* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, begin */
    pstMsg->enPlmnType      = NAS_MMC_GetPlmnHUOType(&(pstCampPlmnInfo->stLai.stPlmnId));
    /* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, end */

    NAS_MMC_ConvertPlmnIdToOmDispalyFormat(&(pstCampPlmnInfo->stLai.stPlmnId),
                                           &(pstMsg->SelectedPlmn));


    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, begin */
    NAS_MMC_ConvertNetworkModeToDispalyFormat(pstCampPlmnInfo->enNetworkMode,
                                             &(pstMsg->enNetMode));
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, end */


}

/*****************************************************************************
 函 数 名  : NAS_MMC_FillNasMsMode
 功能描述  : 填充OM查询消息的手机模式信息项
 输入参数  : 无
 输出参数  : pstMsg:当前查询内容
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月23日
   作    者   : zhoujun \40661
   修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID NAS_MMC_FillNasMsMode(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;

    enMsMode    = NAS_MML_GetMsMode();

    switch ( enMsMode )
    {
        case NAS_MML_MS_MODE_NULL:
            pstMsg->enUeOperMode = UE_OPERATE_MODE_NULL;
            break;

        case NAS_MML_MS_MODE_PS_CS:
            pstMsg->enUeOperMode = UE_OPERATE_MODE_A;
            if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            {
                pstMsg->enUeOperMode = UE_OPERATE_MODE_B;
            }
            break;

        case NAS_MML_MS_MODE_PS_ONLY:
            pstMsg->enUeOperMode = UE_OPERATE_MODE_CG;
            break;

        case NAS_MML_MS_MODE_CS_ONLY:
            pstMsg->enUeOperMode = UE_OPERATE_MODE_CC;
            break;

        default:
            pstMsg->enUeOperMode = UE_OPERATE_MODE_BUTT;
            NAS_WARNING_LOG(WUEPS_PID_MMC,
            "NAS_MMC_FillNasMsMode:WARNING: enMsMod is Error");
            break;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_FillNasImeiInfo
 功能描述  : 填充OM查询消息的IMEI信息项
 输入参数  : 无
 输出参数  : pstMsg:当前查询内容
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月23日
   作    者   : zhoujun \40661
   修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID NAS_MMC_FillNasImeiInfo(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucCheckData;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapacility;

    pstMsg->IMEI.ucLength   = LEN_MOBILE - 1;
    pstMsg->IMEISV.ucLength = LEN_MOBILE;
    pstMsCapacility         = NAS_MML_GetMsCapability();
    ucCheckData             = 0;

    for (i = 0; i < (LEN_MOBILE - 2); i += 2)
    {
        ucCheckData += (VOS_UINT8)((pstMsCapacility->aucImeisv[i]
                    + ((pstMsCapacility->aucImeisv[i + 1] * 2) / 10))
                    + ((pstMsCapacility->aucImeisv[i + 1] * 2) % 10));
    }
    ucCheckData = (10 - (ucCheckData % 10)) % 10;

    pstMsg->IMEI.ucMobileIDValue[14] = ucCheckData;
    pstMsg->IMEI.ucMobileIDValue[15] = 0;


    for (i = 0; i < (LEN_MOBILE - 2); i++)
    {
        pstMsg->IMEI.ucMobileIDValue[i]     = pstMsCapacility->aucImeisv[i];
        pstMsg->IMEISV.ucMobileIDValue[i]   = pstMsCapacility->aucImeisv[i];
    }

    pstMsg->IMEISV.ucMobileIDValue[14]      = pstMsCapacility->aucImeisv[14];
    pstMsg->IMEISV.ucMobileIDValue[15]      = pstMsCapacility->aucImeisv[15];

}


/*****************************************************************************
 函 数 名  : NAS_MMC_FillNasMsCfgInfo
 功能描述  : 填充OM查询消息的手机配置信息项
 输入参数  : 无
 输出参数  : pstMsg:当前查询内容
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月23日
   作    者   : zhoujun \40661
   修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID NAS_MMC_FillNasMsCfgInfo(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    /* 填写IMEI内容 */
    NAS_MMC_FillNasImeiInfo(pstMsg);


    /* 填写手机模式内容 */
    NAS_MMC_FillNasMsMode(pstMsg);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertPlmnIdToOmDispalyFormat
 功能描述  : 将内部格式的PlmnID转换为OM显示用的格式
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月23日
   作    者   : zhoujun \40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_ConvertPlmnIdToOmDispalyFormat(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    PLMN_ID_STRUCT                     *pstOmPlmnIdFormat
)
{
    pstOmPlmnIdFormat->aucMccDigit[0] = (VOS_UINT8)(pstPlmnId->ulMcc & 0x0F);
    pstOmPlmnIdFormat->aucMccDigit[1] = (VOS_UINT8)((pstPlmnId->ulMcc >> 8) & 0x0F);
    pstOmPlmnIdFormat->aucMccDigit[2] = (VOS_UINT8)((pstPlmnId->ulMcc >> 16) & 0x0F);

    pstOmPlmnIdFormat->aucMncDigit[0] = (VOS_UINT8)(pstPlmnId->ulMnc & 0x0F);
    pstOmPlmnIdFormat->aucMncDigit[1] = (VOS_UINT8)((pstPlmnId->ulMnc >> 8) & 0x0F);
    pstOmPlmnIdFormat->aucMncDigit[2] = (VOS_UINT8)((pstPlmnId->ulMnc >> 16) & 0x0F);

    pstOmPlmnIdFormat->ucMncCount = 3;

    if (0x0F == pstOmPlmnIdFormat->aucMncDigit[2])
    {
        pstOmPlmnIdFormat->ucMncCount = 2;
    }

}

/*****************************************************************************
 函 数 名  : NAS_MMC_FillNasServiceStatus
 功能描述  : 填写NAS内部服务状态
 输入参数  : 无
 输出参数  : pstMsg:待填写的消息内容
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月23日
   作    者   : zhoujun \40661
   修改内容   : 新生成函数
 2.日    期   : 2015年9月17日
   作    者   : zwx247453
   修改内容   : Dallas寄存器按原语上报及BBP采数项目

*****************************************************************************/
VOS_VOID NAS_MMC_FillNasServiceStatus(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    NAS_MMC_SERVICE_INFO_CTX_STRU      *pstServiceStatus = VOS_NULL_PTR;

    pstServiceStatus = NAS_MMC_GetServiceInfo();

    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, begin */
    if ( ( NAS_MMC_NORMAL_SERVICE == pstServiceStatus->enCsCurrService)
      || ( NAS_MMC_NORMAL_SERVICE == pstServiceStatus->enPsCurrService))
    {
        pstMsg->enServiceStatus     = NAS_OM_SERVICE_STATE_NORMAL_SERVICE;
    }
    else if ( ( NAS_MMC_NO_SERVICE == pstServiceStatus->enCsCurrService)
           && ( NAS_MMC_NO_SERVICE == pstServiceStatus->enPsCurrService))
    {
        pstMsg->enServiceStatus     = NAS_OM_SERVICE_STATE_NO_SERVICE;
    }
    else if ( ( NAS_MMC_LIMITED_SERVICE_REGION == pstServiceStatus->enCsCurrService)
           || ( NAS_MMC_LIMITED_SERVICE_REGION == pstServiceStatus->enPsCurrService))
    {
        pstMsg->enServiceStatus     = NAS_OM_SERVICE_STATE_REGIONAL_LIMITED_SERVICE;
    }
    else
    {
        pstMsg->enServiceStatus     = NAS_OM_SERVICE_STATE_LIMITED_SERVICE;
    }
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, end */
}

/*****************************************************************************
 函 数 名  : NAS_MMC_FillOmAvailPlmnList
 功能描述  : 填写NAS可用的网络列表
 输入参数  : 无
 输出参数  : pstMsg:待填写的消息内容
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月23日
   作    者   : zhoujun \40661
   修改内容   : 新生成函数
 2.日    期   : 2011年9月7日
   作    者   : s46746
   修改内容   : 同步V3R1版本问题单DTS2011072203231
*****************************************************************************/

VOS_VOID NAS_MMC_FillOmAvailPlmnList(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    VOS_UINT32                              i;
    VOS_UINT32                              j;
    VOS_UINT32                              ulPlmnCnt;
    AVAILABLE_PLMN_STRUCT                  *pstPlmnAddr = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8         enNetRat;
    NAS_MMC_NET_STATUS_ENUM_UINT8           enNetExistFlag;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU  *pstPlmnSelectionList = VOS_NULL_PTR;

    ulPlmnCnt           = 0;
    enNetExistFlag      = NAS_MMC_NET_STATUS_BUTT;
    enNetRat            = NAS_MML_NET_RAT_TYPE_BUTT;

    /* 只有搜网状态机运行时才会存在可用网络列表 */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        if (VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
        {
            pstPlmnAddr = &(pstMsg->AvailablePlmn[ulPlmnCnt]);

            NAS_MMC_ConvertPlmnIdToOmDispalyFormat(NAS_MML_GetCurrCampPlmnId(),
                                                   &(pstPlmnAddr->Plmn));

            pstPlmnAddr->ucRat = NAS_MML_GetCurrNetRatType();

            ulPlmnCnt++;
        }

        pstMsg->ucAvailPlmnNum = (VOS_UINT8)ulPlmnCnt;

        return;
    }

    pstPlmnSelectionList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    for (i = 0; i < pstPlmnSelectionList->usSearchPlmnNum; i++)
    {
        for (j = 0; j < pstPlmnSelectionList->astPlmnSelectionList[i].ucRatNum; j++)
        {
            if ( ulPlmnCnt >= MAX_AVAILABEL_PLMN_NUM )
            {
                break;
            }

            /* 只需要导出存在的网络 */
            enNetExistFlag = pstPlmnSelectionList->astPlmnSelectionList[i].astPlmnRatInfo[j].enNetStatus;
            enNetRat       = pstPlmnSelectionList->astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType;

            if  ( ( NAS_MMC_NET_STATUS_SEARCHED_EXIST     == enNetExistFlag)
               || ( NAS_MMC_NET_STATUS_SEARCHED_REGISTERED == enNetExistFlag ))
            {
                pstPlmnAddr = &(pstMsg->AvailablePlmn[ulPlmnCnt]);

                NAS_MMC_ConvertPlmnIdToOmDispalyFormat(&(pstPlmnSelectionList->astPlmnSelectionList[i].stPlmnId),
                                                       &(pstPlmnAddr->Plmn));

                pstPlmnAddr->ucRat = enNetRat;

                ulPlmnCnt++;

            }
        }
    }

    pstMsg->ucAvailPlmnNum = (VOS_UINT8)ulPlmnCnt;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_BuildNasOmInfo
 功能描述  : 构造填写给OM查询NAS的消息内容
 输入参数  : 无
 输出参数  : pstMsg:待填写的消息内容
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月23日
   作    者   : zhoujun \40661
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : zhoujun /40661
   修改内容   : MMC状态更新显示

 3.日    期   : 2013年06月28日
   作    者   : luokaihui 00167671
   修改内容   : 上报TIN信息和PLMN是属于HUO的哪种类型

 4.日    期   : 2015年9月17日
   作    者   : zwx247453
   修改内容   : Dallas寄存器按原语上报及BBP采数项目
*****************************************************************************/

VOS_VOID NAS_MMC_BuildNasOmInfo(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    /* 填写SIM卡信息 */
    NAS_MMC_FillNasMmSimInfo(pstMsg);

    /* 填写MS 配置信息 */
    NAS_MMC_FillNasMsCfgInfo(pstMsg);

    /* 填写当前驻留网络信息 */
    NAS_MMC_FillNasMsNetworkInfo(pstMsg);

    /* 填写MM的状态和子状态 */
    NAS_MM_FillNasMmState(pstMsg);

    /* 填写GMM的状态和子状态 */
    NAS_GMM_FillNasGmmState(pstMsg);

    /* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, begin */
    /* 填写TIN TYPE和MSID*/
    NAS_MMC_FillNasTinInfo(pstMsg);
    /* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, end */

    /* 填写MMC的状态和子状态 */
    /* 此处需要与OM讨论修改MMC内部接口 */
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, begin */
    pstMsg->enMmcFsmId = (VOS_UINT8)NAS_MMC_GetCurrFsmId();
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, end */
    pstMsg->ucMmcState = (VOS_UINT8)NAS_MMC_GetFsmTopState();

    /* 填写可用的网络 */
    NAS_MMC_FillOmAvailPlmnList(pstMsg);

    /* 填写当前服务状态 */
    NAS_MMC_FillNasServiceStatus(pstMsg);

}


/* Added by wx270776 for OM融合, 2015-7-21, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_SndOmIndMsg
 功能描述  : 发送OM的查询消息透传消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年7月21日
   作    者   : wx270776
   修改内容   : OM融合
 2.日    期   : 2015年9月17日
   作    者   : zwx247453
   修改内容   : Dallas寄存器按原语上报及BBP采数项目
*****************************************************************************/
VOS_UINT32 NAS_MMC_SndOmIndMsg(VOS_VOID)
{
    NAS_OM_MM_IND_STRU                  stNasOmMmInd;
    DIAG_TRANS_IND_STRU                 stDiagTransInd;
    VOS_UINT32                          ulRet;

    /* 初始化 */
    PS_MEM_SET(&stNasOmMmInd, 0x00, sizeof(NAS_OM_MM_IND_STRU));

    /* 填充消息内容 */
    NAS_MMC_BuildNasOmInfo(&stNasOmMmInd);
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, begin */
    stNasOmMmInd.enPrimId           = ID_NAS_OM_MM_CONFIRM;
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, end */
    stNasOmMmInd.usToolsId          = 0;

    stDiagTransInd.ulModule         = DIAG_GEN_MODULE(VOS_GetModemIDFromPid(WUEPS_PID_MMC), DIAG_MODE_UMTS);;
    stDiagTransInd.ulPid            = WUEPS_PID_MMC;
    /* Modified by zwx247453 for 寄存器上报, 2015-11-09, begin */
    stDiagTransInd.ulMsgId          = ((VOS_UINT32)(VOS_GetModemIDFromPid(WUEPS_PID_MMC)) << 16) + ID_NAS_OM_MM_CONFIRM;
    /* Modified by zwx247453 for 寄存器上报, 2015-11-09, end */
    stDiagTransInd.ulLength         = sizeof(NAS_OM_MM_IND_STRU);
    stDiagTransInd.pData            = &stNasOmMmInd;

    /* 发送消息 */
    ulRet = DIAG_TransReport(&stDiagTransInd);
    if (VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOmIndMsg:WARNING: Send msg fail.");
    }

    return ulRet;
}
/* Added by wx270776 for OM融合, 2015-7-21, end */
/*****************************************************************************
 函 数 名  : NAS_MMC_SndOmInquireCnfMsg
 功能描述  : 发送OM的查询消息回复
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月21日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

 2.日    期   : 2012年11月1日
   作    者   : z40661
   修改内容   : DTS2012102501504

 3.日    期   : 2013年9月10日
   作    者   : w00242748
   修改内容   : DTS2013082909799 查询NAS MM QUERY时，RPLMN显示成EHPLMN，关机时
                无效PLMN显示为OPLMN修正。

 4.日    期   : 2015年7月21日
   作    者   : wx270776
   修改内容   : OM融合
*****************************************************************************/
VOS_VOID NAS_MMC_SndOmInquireCnfMsg(
    ID_NAS_OM_INQUIRE_STRU             *pstOmInquireMsg
)
{
    /* Modified by wx270776 for OM融合, 2015-7-1, begin */
    NAS_OM_MM_CONFIRM_STRU             *pstNasOmMmCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;
    VOS_UINT32                          ulSndOmRet;
    VOS_UINT32                          ulRet;

    /* 1. 向OM发送IND消息 */
    ulSndOmRet = NAS_MMC_SndOmIndMsg();

    /* 2. 向工具侧回复CNF消息 */
    /* 申请内存 */
    ulMsgLen      = sizeof(NAS_OM_MM_CONFIRM_STRU) - VOS_MSG_HEAD_LENGTH;

    pstNasOmMmCnf = (NAS_OM_MM_CONFIRM_STRU*)PS_ALLOC_MSG(WUEPS_PID_MMC, ulMsgLen);
    if (VOS_NULL_PTR == pstNasOmMmCnf)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOmInquireCnfMsg:Memory Allocate fail!");
        return;
    }

    /* 初始化 */
    PS_MEM_SET((VOS_UINT8*)pstNasOmMmCnf + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLen);

    /* 填写消息内容 */
    pstNasOmMmCnf->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
    pstNasOmMmCnf->ulMsgId          = ID_NAS_OM_MM_CONFIRM;
    pstNasOmMmCnf->usOriginalId     = pstOmInquireMsg->usOriginalId;
    pstNasOmMmCnf->usTerminalId     = pstOmInquireMsg->usTerminalId;
    pstNasOmMmCnf->ulTimeStamp      = pstOmInquireMsg->ulTimeStamp;
    pstNasOmMmCnf->ulSN             = pstOmInquireMsg->ulSN;
    pstNasOmMmCnf->enResult         = (NAS_OM_RESULT_ENUM_UINT32)ulSndOmRet;


    /* 发送消息 */
    ulRet = PS_SEND_MSG(WUEPS_PID_MMC, pstNasOmMmCnf);
    if (VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOmInquireCnfMsg:WARNING: Send msg fail.");
    }

    return;
    /* Modified by wx270776 for OM融合, 2015-7-1, end */


}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndOmPlmnSelectionList
 功能描述  : 将选网列表导出到SDT LOG中
 输入参数  : pstPlmnSelectionList
             pstPrioRatList
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月29日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2012年10月17日
    作    者   : z00161729
    修改内容   : DTS2012081603683:搜网列表中有重复plmn信息

*****************************************************************************/
VOS_VOID NAS_MMC_SndOmPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList,
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              k;
    VOS_UINT32                                              ulPlmnNum;
    NAS_MMC_LOG_PLMN_SELECTION_LIST_MSG_STRU               *pstMsg               = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnSelectionInfo = VOS_NULL_PTR;

    pstMsg = (NAS_MMC_LOG_PLMN_SELECTION_LIST_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                          (sizeof(NAS_MMC_LOG_PLMN_SELECTION_LIST_MSG_STRU)));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogPlmnSelectionList_PlmnSelection:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_PLMN_SELECTION_LIST;

    ulPlmnNum = 0x0;

    for (i = 0; i < pstPlmnSelectionList->usSearchPlmnNum; i++)
    {


        pstPlmnSelectionInfo = &(pstPlmnSelectionList->astPlmnSelectionList[i]);

        /* 按SYSCFG设置的接入技术优先级依次查找 */
        for (k = 0; k < pstPrioRatList->ucRatNum; k++)
        {
            /* 依次查找一个网络的所有支持的接入技术 */
            for (j = 0; j < pstPlmnSelectionInfo->ucRatNum; j++)
            {
                /* 如果优先的接入技术与当前查找的网络支持的接入技术相同 */
                if (pstPrioRatList->aucRatPrio[k] == pstPlmnSelectionInfo->astPlmnRatInfo[j].enRatType)
                {
                    pstMsg->astPlmnSelectionList[ulPlmnNum].ulMcc       = pstPlmnSelectionInfo->stPlmnId.ulMcc;
                    pstMsg->astPlmnSelectionList[ulPlmnNum].ulMnc       = pstPlmnSelectionInfo->stPlmnId.ulMnc;
                    pstMsg->astPlmnSelectionList[ulPlmnNum].enPlmnType  = pstPlmnSelectionInfo->enPlmnType;
                    pstMsg->astPlmnSelectionList[ulPlmnNum].enRatType   = pstPlmnSelectionInfo->astPlmnRatInfo[j].enRatType;
                    pstMsg->astPlmnSelectionList[ulPlmnNum].enNetStatus = pstPlmnSelectionInfo->astPlmnRatInfo[j].enNetStatus;
                    pstMsg->astPlmnSelectionList[ulPlmnNum].enQuality   = pstPlmnSelectionInfo->astPlmnRatInfo[j].enQuality;

                    ulPlmnNum ++;
                }

                if (ulPlmnNum >= NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST)
                {
                    break;
                }
                }

            if (ulPlmnNum >= NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST)
            {
                break;
            }
        }

        if (ulPlmnNum >= NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST)
        {
            break;
        }
    }

    pstMsg->ulPlmnNum                   = ulPlmnNum;

    pstMsg->stMsgHeader.ulLength        = sizeof(pstMsg->stMsgHeader.ulMsgName)
                                          + sizeof(pstMsg->ulPlmnNum)
                                          + (ulPlmnNum * sizeof(NAS_MMC_LOG_PLMN_SELECTION_LIST_STRU));

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_LogPlmnRegRejInfo
 功能描述  : 将PLMN 注册信息发送到OM
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月20日
    作    者   : c00318887
    修改内容   : 新建函数
*****************************************************************************/
VOS_VOID NAS_MMC_LogPlmnRegRejInfo(VOS_VOID)
{
    NAS_MMC_LOG_PLMN_REG_REJ_INFO_STRU *pstMsg              = VOS_NULL_PTR;
    NAS_MMC_PLMN_REG_REJ_CTX_STRU      *pstPlmnRegInfo      = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstPlmnRegInfo                      = NAS_MMC_GetPlmnRegRejInfo();

    pstMsg = (NAS_MMC_LOG_PLMN_REG_REJ_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                          (sizeof(NAS_MMC_LOG_PLMN_REG_REJ_INFO_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogPlmnRegRejInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0X00, sizeof(NAS_MMC_LOG_PLMN_REG_REJ_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_PLMN_REG_REJ_INFO;
    pstMsg->stMsgHeader.ulLength        = sizeof(pstMsg->stMsgHeader.ulMsgName)
                                                 + sizeof(pstMsg->stPlmnRegRejInfo.ucPlmnRegInfoNum)
                                                 + sizeof(pstMsg->stPlmnRegRejInfo.aucReserve)
                                                 + (pstPlmnRegInfo->ucPlmnRegInfoNum * sizeof(NAS_MMC_PLMN_REG_INFO_STRU));

    for (i = 0; i < NAS_MML_MIN(pstPlmnRegInfo->ucPlmnRegInfoNum, NAS_MMC_MAX_REG_PLMN_INFO_NUM); i++)
    {

        PS_MEM_CPY((VOS_VOID*) &(pstMsg->stPlmnRegRejInfo.astPlmnRegInfoList[i]),
                    (VOS_VOID*)&(pstPlmnRegInfo->astPlmnRegInfoList[i]),
                    sizeof(NAS_MMC_PLMN_REG_INFO_STRU));
    }

    pstMsg->stPlmnRegRejInfo.ucPlmnRegInfoNum               = pstPlmnRegInfo->ucPlmnRegInfoNum;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_LogCurrPlmnRelatedInfo
 功能描述  : 将当前PLMN 相关信息发送到OM
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月20日
    作    者   : c00318887
    修改内容   : 新建函数
*****************************************************************************/
VOS_VOID NAS_MMC_LogCurrPlmnRelatedInfo(VOS_VOID)
{
    NAS_MMC_LOG_CURR_PLMN_RELATED_INFO_STRU *pstMsg              = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                    *pstPlmnId           = VOS_NULL_PTR;

    pstPlmnId                               = NAS_MML_GetCurrCampPlmnId();

    pstMsg = (NAS_MMC_LOG_CURR_PLMN_RELATED_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                          (sizeof(NAS_MMC_LOG_CURR_PLMN_RELATED_INFO_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogCurrPlmnRelatedInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0X00, sizeof(NAS_MMC_LOG_CURR_PLMN_RELATED_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_CURR_PLMN_RELATED_INFO;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MMC_LOG_CURR_PLMN_RELATED_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->stPlmnRelatedInfo.stPlmnId.ulMcc                = pstPlmnId->ulMcc;
    pstMsg->stPlmnRelatedInfo.stPlmnId.ulMnc                = pstPlmnId->ulMnc;
    pstMsg->stPlmnRelatedInfo.enNetRatType                  = NAS_MML_GetCurrNetRatType();
    pstMsg->stPlmnRelatedInfo.enCsCurrService               = NAS_MMC_GetCurrCsService();
    pstMsg->stPlmnRelatedInfo.enPsCurrService               = NAS_MMC_GetCurrPsService();
    pstMsg->stPlmnRelatedInfo.enCsRegStatus                 = NAS_MML_GetCsRegStatus();
    pstMsg->stPlmnRelatedInfo.enPsRegStatus                 = NAS_MML_GetPsRegStatus();

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_LogRplmnRelatedInfo
 功能描述  : 将RPLMN信息发送到OM
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月05日
    作    者   : w00167002
    修改内容   : DTS2014102109190_LOG_RPLMN
*****************************************************************************/
VOS_VOID NAS_MMC_LogRplmnRelatedInfo(VOS_VOID)
{
    NAS_MMC_LOG_RPLMN_RELATED_INFO_STRU                      *pstMsg  = VOS_NULL_PTR;

    pstMsg = (NAS_MMC_LOG_RPLMN_RELATED_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                          (sizeof(NAS_MMC_LOG_RPLMN_RELATED_INFO_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogRplmnRelatedInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0X00, sizeof(NAS_MMC_LOG_RPLMN_RELATED_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_RPLMN_RELATED_INFO;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MMC_LOG_RPLMN_RELATED_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 获取LTE的RPLMN */
    (VOS_VOID)NAS_MML_GetLteRPlmn(&pstMsg->stGetLteRplmn);

    /* 获取GU的RPLMN */
    (VOS_VOID)NAS_MML_GetGURPlmn(&pstMsg->stGetGuRplmn);

    /* 打印RPLMN的配置信息 */
    PS_MEM_CPY(&pstMsg->stRplmnCfg, NAS_MML_GetRplmnCfg(), sizeof(NAS_MML_RPLMN_CFG_INFO_STRU));

    /* CS域最后一次注册成功的LAI信息或注册失败后需要删除LAI，则该值为无效值 */
    PS_MEM_CPY(&pstMsg->stLastSuccLai, NAS_MML_GetCsLastSuccLai(), sizeof(NAS_MML_LAI_STRU));

    /* PS域最后一次注册成功的RAI信息或注册失败后需要删除RAI，则该值为无效值 */
    PS_MEM_CPY(&pstMsg->stLastSuccRai, NAS_MML_GetPsLastSuccRai(), sizeof(NAS_MML_RAI_STRU));

    /* PS UPDATE STATUS */
    pstMsg->enPsUpdateStatus   = NAS_MML_GetPsUpdateStatus();

    /* CS UPDATE STATUS */
    pstMsg->enCsUpdateStatus   = NAS_MML_GetCsUpdateStatus();

    /* MS MODE */
    pstMsg->enMsMode            = NAS_MML_GetMsMode();

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_LogForbiddenPlmnRelatedInfo
 功能描述  : 将FORBIDDEN PLMN相关的信息发送到OM
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月05日
    作    者   : w00167002
    修改内容   : DTS2014102109190_LOG_RPLMN
*****************************************************************************/
VOS_VOID NAS_MMC_LogForbiddenPlmnRelatedInfo(VOS_VOID)
{
    NAS_MMC_LOG_FORBIDDEN_PLMN_RELATED_INFO_STRU           *pstMsg       = VOS_NULL_PTR;
    NAS_MML_CUSTOM_CFG_INFO_STRU                           *pstCustomCfg = VOS_NULL_PTR;

    pstCustomCfg = NAS_MML_GetCustomCfg();

    pstMsg = (NAS_MMC_LOG_FORBIDDEN_PLMN_RELATED_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                          (sizeof(NAS_MMC_LOG_FORBIDDEN_PLMN_RELATED_INFO_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogForbiddenPlmnRelatedInfo:ERROR:Alloc Mem Fail.");

        return;
    }

    PS_MEM_SET(pstMsg, 0X00, sizeof(NAS_MMC_LOG_FORBIDDEN_PLMN_RELATED_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_FORBIDDEN_PLMN_RELATED_INFO;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MMC_LOG_FORBIDDEN_PLMN_RELATED_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 打印FORB PLMN的信息 */
    PS_MEM_CPY(&pstMsg->stSimForbidenInfo, NAS_MML_GetForbidPlmnInfo(), sizeof(NAS_MML_SIM_FORBIDPLMN_INFO_STRU));

    /* 打印ROMA CFG的信息 */
    PS_MEM_CPY(&pstMsg->stRoamCfg, NAS_MML_GetRoamCfg(), sizeof(NAS_MML_ROAM_CFG_INFO_STRU));

    /* 打印锁网定制需求,黑名单或白名单的信息 */
    PS_MEM_CPY(&pstMsg->stPlmnLockCfg, NAS_MML_GetPlmnLockCfg(), sizeof(NAS_MML_PLMN_LOCK_CFG_INFO_STRU));

    /* 打印LTE国际漫游的信息 */
    PS_MEM_CPY(&pstMsg->stLteRoamCfg, &(pstCustomCfg->stLteCustomCfgInfo.stLteRoamCfg), sizeof(NAS_MML_LTE_INTERNATION_ROAM_CFG_STRU));

    /* 打印禁止接入技术的信息 */
    PS_MEM_CPY(&pstMsg->stRatFirbiddenStatusCfg, &(pstCustomCfg->stRatFirbiddenStatusCfg), sizeof(NAS_MML_RAT_FORBIDDEN_STATUS_STRU));

    /* 打印DISABLE LTE的相关信息，在DISABLE LTE时对搜网会产生影响 */
    pstMsg->enLteCapabilityStatus = NAS_MML_GetLteCapabilityStatus();
    pstMsg->enDisableLteReason    = NAS_MML_GetDisableLteReason();
    pstMsg->ulDisableLteRoamFlg   = NAS_MML_GetDisableLteRoamFlg();

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_LogRplmnRelatedInfo
 功能描述  : 将RPLMN信息发送到OM
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月05日
    作    者   : w00167002
    修改内容   : DTS2014102109190_LOG_RPLMN
*****************************************************************************/
VOS_VOID NAS_MMC_LogRplmnCfgInfo(VOS_VOID)
{
    NAS_MMC_LOG_RPLMN_CFG_INFO_STRU                      *pstMsg  = VOS_NULL_PTR;

    pstMsg = (NAS_MMC_LOG_RPLMN_CFG_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                          (sizeof(NAS_MMC_LOG_RPLMN_CFG_INFO_STRU)));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogRplmnCfgInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0X00, sizeof(NAS_MMC_LOG_RPLMN_CFG_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_RPLMN_CFG_INFO;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MMC_LOG_RPLMN_CFG_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 打印RPLMN的配置信息 */
    PS_MEM_CPY(&pstMsg->stRplmnCfg, NAS_MML_GetRplmnCfg(), sizeof(NAS_MML_RPLMN_CFG_INFO_STRU));

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_LogFsmPlmnSelectionCtxRelatedInfo
 功能描述  : 将FORBIDDEN PLMN相关的信息发送到OM
 输入参数  : pstFsmPlmnSelectionCtx
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月05日
    作    者   : w00167002
    修改内容   : 增加选网状态机上下文信息的勾包，便于问题定位
*****************************************************************************/
VOS_VOID NAS_MMC_LogFsmPlmnSelectionCtxRelatedInfo(
    NAS_MMC_FSM_PLMN_SELECTION_CTX_STRU                    *pstFsmPlmnSelectionCtx
)
{
    NAS_MMC_LOG_FSM_PLMN_SELECTON_CTX_RELATED_INFO_STRU    *pstMsg       = VOS_NULL_PTR;

    if (VOS_NULL_PTR == pstFsmPlmnSelectionCtx )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogFsmPlmnSelectionCtxRelatedInfo:ERROR:pstFsmPlmnSelectionCtx is null pointer!");

        return;
    }

    pstMsg = (NAS_MMC_LOG_FSM_PLMN_SELECTON_CTX_RELATED_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                          (sizeof(NAS_MMC_LOG_FSM_PLMN_SELECTON_CTX_RELATED_INFO_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogFsmPlmnSelectionCtxRelatedInfo:ERROR:Alloc Mem Fail.");

        return;
    }

    PS_MEM_SET(pstMsg, 0X00, sizeof(NAS_MMC_LOG_FSM_PLMN_SELECTON_CTX_RELATED_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MMC_LOG_FSM_PLMN_SELECTON_CTX_RELATED_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_FSM_PLMN_SELECTION_CTX_RELATED_INFO;

    pstMsg->ucAbortFlg                  = pstFsmPlmnSelectionCtx->ucAbortFlg;
    pstMsg->ucRelRequestFlg             = pstFsmPlmnSelectionCtx->ucRelRequestFlg;
    pstMsg->ucInterSysSuspendRat        = pstFsmPlmnSelectionCtx->ucInterSysSuspendRat;
    pstMsg->ucSrvTrigPlmnSearchFlag     = pstFsmPlmnSelectionCtx->ucSrvTrigPlmnSearchFlag;
    PS_MEM_CPY(&pstMsg->stRegRlstInfo,      &pstFsmPlmnSelectionCtx->stRegRlstInfo,     sizeof(NAS_MMC_PLMN_SELECTION_REG_RSLT_INFO_STRU));
    PS_MEM_CPY(pstMsg->astSearchRatInfo,   pstFsmPlmnSelectionCtx->astSearchRatInfo,  sizeof(NAS_MMC_RAT_SEARCH_INFO_STRU) * NAS_MML_MAX_RAT_NUM);
    PS_MEM_CPY(&pstMsg->stForbRoamLaInfo,   &pstFsmPlmnSelectionCtx->stForbRoamLaInfo,  sizeof(NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU));
    PS_MEM_CPY(&pstMsg->stForbGprsPlmn,     &pstFsmPlmnSelectionCtx->stForbGprsPlmn,    sizeof(NAS_MML_PLMN_ID_STRU));
    PS_MEM_CPY(&pstMsg->stCsPsMode1ReCampLtePlmn,
               &pstFsmPlmnSelectionCtx->stCsPsMode1ReCampLtePlmn,  sizeof(NAS_MML_PLMN_ID_STRU));
    PS_MEM_CPY(&pstMsg->stCurrSearchingPlmn,&pstFsmPlmnSelectionCtx->stCurrSearchingPlmn,  sizeof(NAS_MML_PLMN_WITH_RAT_STRU));
    pstMsg->enCurrSearchingType         = pstFsmPlmnSelectionCtx->enCurrSearchingType;
    pstMsg->ucExistRplmnOrHplmnFlag     = pstFsmPlmnSelectionCtx->ucExistRplmnOrHplmnFlag;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_LogForbiddenPlmnRelatedInfo
 功能描述  : 将FORBIDDEN PLMN相关的信息发送到OM
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月05日
    作    者   : w00167002
    修改内容   : 增加对L1 MAIN状态机上下文信息的勾包，便于问题定位
  2.日    期   : 2015年10月28日
    作    者   : s00217060
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0修改
*****************************************************************************/
VOS_VOID NAS_MMC_LogFsmL1MainCtxRelatedInfo(
    NAS_MMC_FSM_L1_MAIN_CTX_STRU       *pstFsmL1MainCtx
)
{
    NAS_MMC_LOG_FSM_L1_MAIN_CTX_RELATED_INFO_STRU          *pstMsg = VOS_NULL_PTR;

    /* 异常保护 */
    if (VOS_NULL_PTR == pstFsmL1MainCtx )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogFsmL1MainCtxRelatedInfo:ERROR:pstFsmL1MainCtx is null pointer!");

        return;
    }

    pstMsg = (NAS_MMC_LOG_FSM_L1_MAIN_CTX_RELATED_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                          (sizeof(NAS_MMC_LOG_FSM_L1_MAIN_CTX_RELATED_INFO_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogFsmL1MainCtxRelatedInfo:ERROR:Alloc Mem Fail.");

        return;
    }

    PS_MEM_SET(pstMsg, 0X00, sizeof(NAS_MMC_LOG_FSM_L1_MAIN_CTX_RELATED_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulLength            = sizeof(NAS_MMC_LOG_FSM_L1_MAIN_CTX_RELATED_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName           = MMCOM_LOG_FSM_L1_MAIN_CTX_RELATED_INFO;

    PS_MEM_CPY(&pstMsg->stRegRsltInfo, &pstFsmL1MainCtx->stRegRsltInfo, sizeof(NAS_MMC_L1_MAIN_REG_RSLT_INFO_STRU));
    pstMsg->ulCurTimerCount                 = pstFsmL1MainCtx->ulCurTimerCount;
    pstMsg->ulCurHighRatHplmnTimerCount     = pstFsmL1MainCtx->ulCurHighRatHplmnTimerCount;
    pstMsg->ulCurNcellSearchTimerCount      = pstFsmL1MainCtx->ulCurNcellSearchTimerCount;
    pstMsg->ulCurHistorySearchTimerCount    = pstFsmL1MainCtx->ulCurHistorySearchTimerCount;
    pstMsg->ulCurPrefBandSearchTimerCount   = pstFsmL1MainCtx->ulCurPrefBandSearchTimerCount;
    pstMsg->enAvailableTimerType            = pstFsmL1MainCtx->enAvailableTimerType;


    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}




/*****************************************************************************
 函 数 名  : NAS_MMC_LogOosPlmnSearchStrategyRelatedInfo
 功能描述  : 增加对History/PrefBand/FullBand搜网信息的勾包
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : h00281185
    修改内容   : 增加对History/PrefBand/FullBand搜网信息的勾包，便于问题定位
*****************************************************************************/
VOS_VOID NAS_MMC_LogOosPlmnSearchStrategyRelatedInfo(VOS_VOID)
{
    NAS_MMC_LOG_OOS_PLMN_SEARCH_STRATEGY_RELATED_INFO_STRU                      *pstMsg                = VOS_NULL_PTR;
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU                                   *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU                                   *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_OOS_PLMN_SEARCH_STRATEGY_INFO_STRU                                  *pstOosPlmnSearchStrategyInfo = VOS_NULL_PTR;

    pstPhaseOneOosPlmnSearchPatternInfo    = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    pstPhaseTwoOosPlmnSearchPatternInfo    = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();
    pstOosPlmnSearchStrategyInfo           = NAS_MMC_GetOosPlmnSearchStrategyInfo();

    pstMsg = (NAS_MMC_LOG_OOS_PLMN_SEARCH_STRATEGY_RELATED_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                          (sizeof(NAS_MMC_LOG_OOS_PLMN_SEARCH_STRATEGY_RELATED_INFO_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogOosPlmnSearchStrategyRelatedInfo:ERROR:Alloc Mem Fail.");

        return;
    }

    PS_MEM_SET(pstMsg, 0X00, sizeof(NAS_MMC_LOG_OOS_PLMN_SEARCH_STRATEGY_RELATED_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulLength            = sizeof(NAS_MMC_LOG_OOS_PLMN_SEARCH_STRATEGY_RELATED_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName           = MMCOM_LOG_SEARCH_TYPE_STRATEGY_RELATED_INFO;

    PS_MEM_CPY(&(pstMsg->stSearchTypeStrategyInfo.stPhaseOnePatternCfg), pstPhaseOneOosPlmnSearchPatternInfo, sizeof(NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU));
    PS_MEM_CPY(&(pstMsg->stSearchTypeStrategyInfo.stPhaseTwoPatternCfg), pstPhaseTwoOosPlmnSearchPatternInfo, sizeof(NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU));
    PS_MEM_CPY(&(pstMsg->stGetGeoInfo.stGeoPlmn), NAS_MMC_GetGeoPlmn(), sizeof(NAS_MML_PLMN_WITH_RAT_STRU));
    pstMsg->stSearchTypeStrategyInfo.enCurrOosSearchPhaseNum = pstOosPlmnSearchStrategyInfo->enCurrOosSearchPhaseNum;
    pstMsg->stSearchTypeStrategyInfo.enNextOosSearchPhaseNum = pstOosPlmnSearchStrategyInfo->enNextOosSearchPhaseNum;


    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndOmMmcTimerStart
 功能描述  : 发送消息给OM模块，MMC定时器运行完成
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月6日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

 2.日    期   : 2011年8月22日
   作    者   : w00167002
   修改内容   : 回放修改，保留字段清空，消息体长度赋值
*****************************************************************************/
VOS_VOID  NAS_MMC_SndOmMmcTimerStatus(
    NAS_MMC_TIMER_STATUS_ENUM_U8        enTimerStatus,
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId,
    VOS_UINT32                          ulTimerRemainLen
)
{
    NAS_MMC_TIMER_INFO_STRU            *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_MMC_TIMER_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                             sizeof(NAS_MMC_TIMER_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOmMmcTimerStart:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;

    pstMsg->stMsgHeader.ulLength        = NAS_MML_MSG_TIMER_ID_LENGTH + NAS_MML_MSG_NAME_ID_LENGTH;

    pstMsg->stMsgHeader.ulMsgName       = enTimerId;
    pstMsg->enTimerStatus               = enTimerStatus;
    pstMsg->enTimerId                   = enTimerId;
    pstMsg->ucReserve                   = 0;

    pstMsg->ulTimerRemainLen            = ulTimerRemainLen;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndOmEquPlmn
 功能描述  : 上报Eplmn列表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月24日
   作    者   : l00130025
   修改内容   : 新生成函数

 2.日    期   : 2011年8月14日
   作    者   : w00167002
   修改内容   : ut工程时，eplmn个数为0时，内存分配为空，工程崩溃
 3.日    期   : 2011年11月24日
   作    者   : w00167002
   修改内容   : DTS2011112405567:原有的函数名NAS_MML_IsPlmnIdInDestPlmnList
                更改为NAS_MML_IsBcchPlmnIdInDestSimPlmnList
 4.日    期   : 2011年12月8日
   作    者   : l00130025
   修改内容   : DTS2011101105035:RPlmn在EPlmn列表中时，上报的EPlmn列表的个数错误
*****************************************************************************/
VOS_VOID NAS_MMC_SndOmEquPlmn(VOS_VOID)
{
    VOS_UINT8                          *pucEplmnContent = VOS_NULL_PTR;
    VOS_UINT32                          i;
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnList = VOS_NULL_PTR;
    NAS_MML_SIM_FORMAT_PLMN_ID          stReportPlmn;                           /* 该Plmn与Sim格式相同 */
    VOS_UINT32                          ulSndEplmnNum;
    VOS_UINT32                          ulPlmnIdx;

    pstEplmnList  = NAS_MML_GetEquPlmnList();

    /* 上报RPlmn+Eplmn当前网络 */
    ulSndEplmnNum  = pstEplmnList->ucEquPlmnNum;

    if ( 0 == ulSndEplmnNum )
    {
        /* 为了发送当前网络 */
        ulSndEplmnNum = 1;
    }

    pucEplmnContent = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                NAS_MML_SIM_FORMAT_PLMN_LEN * ulSndEplmnNum);
    if( VOS_NULL_PTR == pucEplmnContent )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOmEquPlmn():Memory Alloc Error for pucEplmnContent ");
        return;
    }

    PS_MEM_SET(pucEplmnContent, 0, ulSndEplmnNum * NAS_MML_SIM_FORMAT_PLMN_LEN);

    ulPlmnIdx = 0;

    if (pstEplmnList->ucEquPlmnNum > 0)
    {
        for (i = 0; i < pstEplmnList->ucEquPlmnNum; i++)
        {
            if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(pstEplmnList->astEquPlmnAddr[i]),
                                               (VOS_UINT8)ulPlmnIdx, pstEplmnList->astEquPlmnAddr))
            {
                continue;
            }

            NAS_MMC_ConvertNasPlmnToSimFormat(&(pstEplmnList->astEquPlmnAddr[i]), &stReportPlmn);

            PS_MEM_CPY(pucEplmnContent + (ulPlmnIdx * NAS_MML_SIM_FORMAT_PLMN_LEN),
                      stReportPlmn.aucSimPlmn, NAS_MML_SIM_FORMAT_PLMN_LEN);

            ulPlmnIdx++;
        }
    }
    /* EPlmn不存在时，只添加当前网络 */
    else
    {
        NAS_MMC_ConvertNasPlmnToSimFormat(NAS_MML_GetCurrCampPlmnId(), &stReportPlmn);

        PS_MEM_CPY(pucEplmnContent + (ulPlmnIdx * NAS_MML_SIM_FORMAT_PLMN_LEN),
                  stReportPlmn.aucSimPlmn, NAS_MML_SIM_FORMAT_PLMN_LEN);

        ulPlmnIdx++;
    }


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_EPLMN_LIST,
                    pucEplmnContent, (NAS_MML_SIM_FORMAT_PLMN_LEN * ulPlmnIdx));


    /* 释放内存 */
    PS_MEM_FREE(WUEPS_PID_MMC, pucEplmnContent);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndOmInternalMsgQueueDetailInfo
 功能描述  : 发送内部消息队列的详细信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月21日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndOmInternalMsgQueueDetailInfo(
    NAS_MML_INTERNAL_MSG_QUEUE_STRU    *pInternalMsgQueue
)
{
    VOS_UINT32                                              ulMsgPnt;
    VOS_UINT8                                               ucHeader;
    VOS_UINT8                                               ucTail;

    ucHeader = pInternalMsgQueue->ucHeader;
    ucTail   = pInternalMsgQueue->ucTail;

    /* 打印出消息队列中的内容 */
    for (ulMsgPnt = ucHeader; ulMsgPnt != ucTail; ulMsgPnt = (ulMsgPnt + 1)%NAS_MML_MAX_MSG_QUEUE_SIZE)
    {
        DIAG_TraceReport(&pInternalMsgQueue->astNasMmMsgQueue[ulMsgPnt]);
    }

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_SndOmInternalMsgQueueInfo
 功能描述  : 发送内部消息队列的相关信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月12日
    作    者   : z40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_SndOmInternalMsgQueueInfo(
    VOS_UINT8                          ucFullFlg,
    VOS_UINT8                          ucMsgLenValidFlg
)
{
    NAS_MMC_LOG_INTER_MSG_INFO_STRU     *pstInterMsg = VOS_NULL_PTR;

    pstInterMsg = (NAS_MMC_LOG_INTER_MSG_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                             sizeof(NAS_MMC_LOG_INTER_MSG_INFO_STRU));

    if ( VOS_NULL_PTR == pstInterMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_MMC_SndOmInternalMsgQueueInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstInterMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInterMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstInterMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstInterMsg->stMsgHeader.ulLength        = sizeof(NAS_MMC_LOG_INTER_MSG_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstInterMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_INTER_MSG_INFO_IND;
    pstInterMsg->ucFullFlg                   = ucFullFlg;
    pstInterMsg->ucMsgLenValidFlg            = ucMsgLenValidFlg;

    DIAG_TraceReport(pstInterMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstInterMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndOmGetCacheFile
 功能描述  : MMC调用USIMM_GetCachedFile接口，勾消息
 输入参数  : VOS_UINT32                          ulFileId
             VOS_UINT32                          ulFileLen
             VOS_UINT8                          *pucFileContent
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月30日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_SndOmGetCacheFile(
    VOS_UINT32                          ulFileId,
    VOS_UINT32                          ulFileLen,
    VOS_UINT8                          *pucFileContent
)
{
    NAS_MMC_GET_CACHE_FILE_STRU        *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;

    ulMsgLen = sizeof(NAS_MMC_GET_CACHE_FILE_STRU) + ulFileLen;

    pstMsg = (NAS_MMC_GET_CACHE_FILE_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC, ulMsgLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOmGetCacheFile:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulLength        = ulMsgLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = ulFileId;

    pstMsg->ulFileLen                   = ulFileLen;

    PS_MEM_CPY(pstMsg->aucFileContent, pucFileContent, ulFileLen);

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

}
/*****************************************************************************
 函 数 名  : NAS_MMC_SndDrxTimerInfo
 功能描述  : 发送DRX周期定时器的可维可测信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月9日
    作    者   : z40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_SndDrxTimerInfo( VOS_UINT8 ucDrxTimerStatus )
{
    NAS_MMC_DRX_TIMER_STAUTS_STRU        *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;

    ulMsgLen = sizeof(NAS_MMC_DRX_TIMER_STAUTS_STRU)  ;

    pstMsg = (NAS_MMC_DRX_TIMER_STAUTS_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC, ulMsgLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOmGetCacheFile:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulLength        = ulMsgLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_DRX_TIMER_STATUS_IND;
    PS_MEM_SET(pstMsg->aucReserve,0x00,sizeof(pstMsg->aucReserve));
    pstMsg->ucDrxTimerStatus            = ucDrxTimerStatus;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndOmPlatformRatCap
 功能描述  : 发送平台接入技术能力的可维可测信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月29日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_SndOmPlatformRatCap( VOS_VOID )
{
    NAS_MMC_PLATFORM_RAT_CAP_STRU          *pstMsg = VOS_NULL_PTR;
    NAS_MML_PLATFORM_RAT_CAP_STRU          *pstPlatformRatCap =VOS_NULL_PTR;
    VOS_UINT32                              ulMsgLen;

    pstPlatformRatCap   = NAS_MML_GetPlatformRatCap();
    ulMsgLen            = sizeof(NAS_MMC_PLATFORM_RAT_CAP_STRU);

    pstMsg = (NAS_MMC_PLATFORM_RAT_CAP_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC, ulMsgLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOmPlatformRatCap:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulLength        = ulMsgLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_MMC_PLATFORM_RAT_CAP;

    PS_MEM_CPY(&(pstMsg->stPlatformRatCap), pstPlatformRatCap, sizeof(NAS_MML_PLATFORM_RAT_CAP_STRU));

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

}


#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 函 数 名  : NAS_MMC_SndAcpuOmErrLogRptCnf
 功能描述  : 发送商用Errlog故障告警信息
 输入参数  : pbuffer:数据内容
             ulBufUseLen:数据长度
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月23日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndAcpuOmErrLogRptCnf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulBufUseLen
 )
{
    OM_ERR_LOG_REPORT_CNF_STRU         *pstQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;

    /* 上报的消息总长度 */
    /*lint -e961*/
    ulMsgLen  = sizeof(OM_ERR_LOG_REPORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH - 4 + ulBufUseLen;
    /*lint +e961*/

    /* 消息空间申请 */
    pstQryCnf = (OM_ERR_LOG_REPORT_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC, ulMsgLen);
    if (VOS_NULL_PTR == pstQryCnf)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAcpuOmErrLogRptCnf: Alloc msg fail!");
        return;
    }

    pstQryCnf->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstQryCnf->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstQryCnf->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
    pstQryCnf->ulSenderPid      = WUEPS_PID_MMC;
    pstQryCnf->ulMsgName        = ID_OM_ERR_LOG_REPORT_CNF;
    pstQryCnf->ulMsgType        = OM_ERR_LOG_MSG_ERR_REPORT;
    pstQryCnf->ulMsgSN          = 0;
    pstQryCnf->ulRptlen         = ulBufUseLen;

    if (VOS_NULL_PTR != pbuffer)
    {
        PS_MEM_CPY(pstQryCnf->aucContent, pbuffer, ulBufUseLen);
    }

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMC, pstQryCnf))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAcpuOmErrLogRptCnf: SEND MSG FAIL");
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndAcpuOmFtmRptInd
 功能描述  : 发送工程模式上报的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月23日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndAcpuOmFtmRptInd(
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulLen
)
{
    VOS_UINT32                          ulMsgLen;
    OM_FTM_REPROT_IND_STRU             *pstFtmRptInd = VOS_NULL_PTR;

    /* 申请消息结构内存 */
    /*lint -e961*/
    ulMsgLen     = sizeof(OM_FTM_REPROT_IND_STRU) - VOS_MSG_HEAD_LENGTH - 4 + ulLen;
    /*lint +e961*/
    pstFtmRptInd = (OM_FTM_REPROT_IND_STRU*)PS_ALLOC_MSG(WUEPS_PID_MMC, ulMsgLen);
    if (VOS_NULL_PTR == pstFtmRptInd)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAcpuOmFtmRptInd: Alloc msg fail!");
        return;
    }

    /* 构造消息结构体 */
    pstFtmRptInd->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstFtmRptInd->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstFtmRptInd->ulReceiverPid     = MSP_PID_DIAG_APP_AGENT;
    pstFtmRptInd->ulSenderPid       = WUEPS_PID_MMC;
    pstFtmRptInd->ulMsgName         = ID_OM_FTM_REPROT_IND;
    pstFtmRptInd->ulMsgType         = OM_ERR_LOG_MSG_FTM_REPORT;
    pstFtmRptInd->ulMsgSN           = 0;
    pstFtmRptInd->ulRptlen          = ulLen;

    PS_MEM_CPY(pstFtmRptInd->aucContent, pucData, ulLen);

    /* 发送消息到ACPU OM模块 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMC, pstFtmRptInd))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAcpuOmFtmRptInd: SEND MSG FIAL");
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndAcpuOmCurTmsi
 功能描述  : 上报当前的TMSI给上层应用
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月23日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndAcpuOmCurTmsi(VOS_VOID)
{
    VOS_UINT8                          *pucTmsi = VOS_NULL_PTR;
    NAS_FTM_TMSI_RPT_EVENT_STRU         stFtmTmsiRpt;

    /* 读取当前的TMSI */
    pucTmsi  = NAS_MML_GetUeIdTmsi();

    /* 填充工程模式上报的头 */
    NAS_COMM_BULID_FTM_HEADER_INFO(&stFtmTmsiRpt.stHeader,
                                   NAS_MML_MAX_TMSI_LEN,
                                   VOS_GetModemIDFromPid(WUEPS_PID_MMC),
                                   NAS_FTM_PROJECT_TMSI_RPT)

    PS_MEM_CPY(stFtmTmsiRpt.aucTmsi,   pucTmsi,  NAS_MML_MAX_TMSI_LEN);

    /* 通过消息ID_OM_FTM_REPROT_IND发送给ACPU OM */
    NAS_MMC_SndAcpuOmFtmRptInd((VOS_UINT8*)&stFtmTmsiRpt,  sizeof(stFtmTmsiRpt));

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndAcpuOmCurPtmsi
 功能描述  : 上报当前的PTMSI给上层应用
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月23日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SndAcpuOmCurPtmsi(VOS_VOID)
{
    VOS_UINT8                          *pucPtmsi = VOS_NULL_PTR;
    NAS_FTM_PTMSI_RPT_EVENT_STRU        stFtmPtmsiRpt;

    /* 读取当前的TMSI/PTMSI */
    pucPtmsi = NAS_MML_GetUeIdPtmsi();

    /* 填充工程模式上报的头 */
    NAS_COMM_BULID_FTM_HEADER_INFO(&stFtmPtmsiRpt.stHeader,
                                   NAS_MML_MAX_PTMSI_LEN,
                                   VOS_GetModemIDFromPid(WUEPS_PID_MMC),
                                   NAS_FTM_PROJECT_PTMSI_RPT)

    PS_MEM_CPY(stFtmPtmsiRpt.aucPtmsi, pucPtmsi, NAS_MML_MAX_PTMSI_LEN);

    /* 通过消息ID_OM_FTM_REPROT_IND发送给ACPU OM */
    NAS_MMC_SndAcpuOmFtmRptInd((VOS_UINT8*)&stFtmPtmsiRpt, sizeof(stFtmPtmsiRpt));
}

#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_LogForbLaWithValidPeriodListInfo
 功能描述  : 将禁止LA有效时长列表信息发送到OM
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月23日
    作    者   : z00359541
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_LogForbLaWithValidPeriodListInfo(VOS_VOID)
{
    NAS_MMC_LOG_FORB_LA_WITH_VALID_PERIOD_LIST_INFO_STRU   *pstMsg  = VOS_NULL_PTR;

    pstMsg = (NAS_MMC_LOG_FORB_LA_WITH_VALID_PERIOD_LIST_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
             (sizeof(NAS_MMC_LOG_FORB_LA_WITH_VALID_PERIOD_LIST_INFO_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogForbLaWithValidPeriodListInfo:ERROR:Alloc Mem Fail.");

        return;
    }

    PS_MEM_SET(pstMsg, 0X00, sizeof(NAS_MMC_LOG_FORB_LA_WITH_VALID_PERIOD_LIST_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MMC_LOG_FORB_LA_WITH_VALID_PERIOD_LIST_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_FORB_LA_WITH_VALID_PERIOD_LIST_INFO;

    /* 打印禁止LA有效时长配置信息 */
    PS_MEM_CPY(&pstMsg->stForbLaWithValidPeriodCfg, NAS_MML_GetForbLaWithValidPeriodCfg(),
               sizeof(NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU));

    /* 打印禁止LA有效时长列表信息 */
    PS_MEM_CPY(&pstMsg->stForbLaWithValidPeriod, NAS_MML_GetForbLaWithValidPeriodList(),
               sizeof(NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU));

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}

/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

