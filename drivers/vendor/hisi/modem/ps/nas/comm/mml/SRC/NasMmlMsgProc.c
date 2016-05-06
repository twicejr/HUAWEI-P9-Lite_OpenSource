/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmlMsgProc.c
  版 本 号   : 初稿
  作    者   : zhoujun 40661
  生成日期   : 2011年6月29日
  最近修改   : 2011年6月29日
  功能描述   : MML_CTX管理的内部消息队列处理函数
  函数列表   :
  修改历史   :
  1.日    期   : 2011年6月29日
    作    者   : zhoujun 40661
    修改内容   : 创建文件

****************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsLib.h"

#include "PsCommonDef.h"
#include "NasComm.h"
#include "MM_Ext.h"
#include "GmmExt.h"
#include "NasMmcMain.h"
#include "NasMmlMsgProc.h"
#include "NasMmcSndOm.h"
#include "NasUtranCtrlInterface.h"

/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-15, begin */
#include "TafMmaMain.h"
/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-15, end */

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/

/*lint -e767 修改人:zhoujun \40661;原因:Log打印*/
#define THIS_FILE_ID PS_FILE_ID_NASMML_MSGPROC_C
/*lint +e767 修改人:zhoujun \40661;原因:Log打印*/

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/
extern VOS_UINT32 WuepsMmPidInit ( enum VOS_INIT_PHASE_DEFINE ip );

extern VOS_UINT32 WuepsGmmPidInit ( enum VOS_INIT_PHASE_DEFINE ip );

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-16, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-16, end */

/*****************************************************************************
  5 变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  6 函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : NAS_MML_GetIntMsgSendBuf
 功能描述  : 从 内部消息缓存队列中获取内部消息发送缓冲区, 该缓冲区仅用于构建 NAS
             MM子层的内部消息。
 输入参数  : VOS_UINT32 ulBufLen:缓存区大小
 输出参数  : 无
 返 回 值  : MsgBlock *
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年07月11日
   作    者   : zhoujun / 40661
   修改内容   : 新增获取内部消息缓存队列的指针

  2.日    期   : 2012年4月21日
    作    者   : z40661
    修改内容   : DTS2012040701419，增加内部消息队列的可谓可测
*****************************************************************************/
NAS_MML_INTERNAL_MSG_BUF_STRU *NAS_MML_GetIntMsgSendBuf(
    VOS_UINT32                          ulLen
)
{
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstNasMmlMsg        = VOS_NULL_PTR;
    NAS_MML_INTERNAL_MSG_QUEUE_STRU    *pstInternalMsgQueue = VOS_NULL_PTR;

    pstInternalMsgQueue         = &(NAS_MML_GetMmlCtx()->stInternalMsgQueue);

    /* 从上下文中获取消息缓冲区指针 */
    pstNasMmlMsg = ( NAS_MML_INTERNAL_MSG_BUF_STRU *)&(pstInternalMsgQueue->stSendMsgBuf);

    if ( ulLen > NAS_MML_MAX_INTERNAL_MSG_LEN )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MML_GetIntMsgSendBuf: Buffer full" );
        NAS_MMC_SndOmInternalMsgQueueInfo(VOS_FALSE, VOS_TRUE);
        return VOS_NULL_PTR;
    }

    /* 清空这个消息缓冲单元 */
    PS_MEM_SET(pstNasMmlMsg, 0x00, sizeof(NAS_MML_INTERNAL_MSG_BUF_STRU));

    /* 返回缓冲区指针 */
    return pstNasMmlMsg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SndInternalMsg
 功能描述  : 发送内部消息
 输入参数  : usMsgID:发送消息ID
             usMsgLen:发送消息长度
             pSndMsg:待发送的消息内容
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月11日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

  2.日    期   : 2012年4月21日
    作    者   : z40661
    修改内容   : DTS2012040701419，增加内部消息队列的可谓可测

  3.日    期   : 2014年1月21日
    作    者   : w00242748
    修改内容   : DTS2014012008306，对内部消息队列扩容。

*****************************************************************************/
VOS_VOID NAS_MML_SndInternalMsg(
    VOS_VOID                           *pSndMsg
)
{
    VOS_UINT8                           ucMsgPnt;
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstMmlMsg           = VOS_NULL_PTR;
    NAS_MML_INTERNAL_MSG_QUEUE_STRU    *pstInternalMsgQueue = VOS_NULL_PTR;
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstSndMsg           = VOS_NULL_PTR;

    pstInternalMsgQueue                 = &(NAS_MML_GetMmlCtx()->stInternalMsgQueue);
    pstSndMsg                           = (NAS_MML_INTERNAL_MSG_BUF_STRU*)pSndMsg;

    /* 1. 判断内部消息缓冲区是否已满 */
    ucMsgPnt = pstInternalMsgQueue->ucTail;
    if ( ((ucMsgPnt + 1) % NAS_MML_MAX_MSG_QUEUE_SIZE) == pstInternalMsgQueue->ucHeader )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MML_SndInternalMsg:Warning: The Queue is full.");
        NAS_MMC_SndOmInternalMsgQueueInfo(VOS_TRUE, VOS_FALSE);
        NAS_MMC_SndOmInternalMsgQueueDetailInfo(pstInternalMsgQueue);

        return;
    }

    /* 2. 取得一个消息缓冲单元 */
    pstMmlMsg = (NAS_MML_INTERNAL_MSG_BUF_STRU *)&(pstInternalMsgQueue->astNasMmMsgQueue[ucMsgPnt]);

    /* 3. 判断消息长度是否非法 */
    if ( pstSndMsg->ulLength > NAS_MML_MAX_INTERNAL_MSG_LEN)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MML_SndInternalMsg:Warning: ulBufLen is too long.");
        NAS_MMC_SndOmInternalMsgQueueInfo(VOS_FALSE, VOS_TRUE);
        return;
    }

    NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MML_SndInternalMsg: usMsgID is ", pstMmlMsg->usMsgID);

    /* 4. 将内部消息发送到内部消息队列中 */
    PS_MEM_CPY(pstMmlMsg, pstSndMsg, sizeof(NAS_MML_INTERNAL_MSG_BUF_STRU));

    /* 更新内部消息缓冲区 */
    pstInternalMsgQueue->ucTail++;
    pstInternalMsgQueue->ucTail         %= NAS_MML_MAX_MSG_QUEUE_SIZE;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetNextInternalMsg
 功能描述  : 获取内部消息队列中的下一条可用的内部消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 内部消息队列的指针
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2010年11月4日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

 2.日    期   : 2012年4月21日
   作    者   : z40661
   修改内容   : DTS2012040701419，增加内部消息队列的可谓可测

 3.日    期   : 2012年9月10日
   作    者   : z40661
   修改内容   : DTS2012090606624，删除多余的的可谓可测
*****************************************************************************/
NAS_MML_INTERNAL_MSG_BUF_STRU* NAS_MML_GetNextInternalMsg( VOS_VOID )
{
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstNextMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucNextIndex;
    NAS_MML_CTX_STRU                   *pstMmlCtx  =  VOS_NULL_PTR;

    pstMmlCtx   = NAS_MML_GetMmlCtx();

    if ( pstMmlCtx->stInternalMsgQueue.ucHeader != pstMmlCtx->stInternalMsgQueue.ucTail)
    {
        ucNextIndex     = pstMmlCtx->stInternalMsgQueue.ucHeader;
        pstNextMsg      = (NAS_MML_INTERNAL_MSG_BUF_STRU *)&(pstMmlCtx->stInternalMsgQueue.astNasMmMsgQueue[ucNextIndex]);

        /* 取完一条消息,头指针向后偏移 */
        (pstMmlCtx->stInternalMsgQueue.ucHeader)++;
        (pstMmlCtx->stInternalMsgQueue.ucHeader) %= NAS_MML_MAX_MSG_QUEUE_SIZE;
        return pstNextMsg;
    }

    NAS_INFO_LOG(WUEPS_PID_MM, "NAS_MML_GetNextInternalMsg:Empty Internal Msg");
    return VOS_NULL_PTR;

}


/*****************************************************************************
 函 数 名  : NAS_MML_InsertInternalMsgHead
 功能描述  : 将内部队列的消息插在内部队列的最前面
 输入参数  : pSndMsg:需要插入的消息
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月30日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数
  2.日    期   : 2012年9月10日
    作    者   : z40661
    修改内容   : DTS2012090606624，内部队列满判断出错
  3.日    期   : 2014年1月21日
    作    者   : w00242748
    修改内容   : DTS2014012008306，对内部消息队列扩容。
*****************************************************************************/
VOS_VOID NAS_MML_InsertInternalMsgHead(
    VOS_VOID                           *pSndMsg
)
{
    VOS_UINT8                           ucMsgPnt;
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstMmlMsg           = VOS_NULL_PTR;
    NAS_MML_INTERNAL_MSG_QUEUE_STRU    *pstInternalMsgQueue = VOS_NULL_PTR;
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstSndMsg           = VOS_NULL_PTR;

    pstInternalMsgQueue                 = &(NAS_MML_GetMmlCtx()->stInternalMsgQueue);
    pstSndMsg                           = (NAS_MML_INTERNAL_MSG_BUF_STRU*)pSndMsg;

    /* 1. 判断内部消息缓冲区是否已满 */
    ucMsgPnt = pstInternalMsgQueue->ucTail;
    if ( ((ucMsgPnt + 1) % NAS_MML_MAX_MSG_QUEUE_SIZE) == pstInternalMsgQueue->ucHeader )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MML_InsertInternalMsgHead:Warning: The Queue is full.");
        NAS_MMC_SndOmInternalMsgQueueInfo(VOS_TRUE, VOS_FALSE);
        NAS_MMC_SndOmInternalMsgQueueDetailInfo(pstInternalMsgQueue);
        return;
    }
    /* 2. 判断消息长度是否非法 */
    if ( pstSndMsg->ulLength > NAS_MML_MAX_INTERNAL_MSG_LEN)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MML_InsertInternalMsgHead:Warning: ulBufLen is too long.");
        NAS_MMC_SndOmInternalMsgQueueInfo(VOS_FALSE, VOS_TRUE);
        return;
    }

    if ( (pstInternalMsgQueue->ucHeader % NAS_MML_MAX_MSG_QUEUE_SIZE) >= 1 )
    {
        pstInternalMsgQueue->ucHeader--;
        pstInternalMsgQueue->ucHeader         %= NAS_MML_MAX_MSG_QUEUE_SIZE;
    }
    else
    {
        pstInternalMsgQueue->ucHeader = NAS_MML_MAX_MSG_QUEUE_SIZE- 1;
    }

    /* 3. 取得一个消息缓冲单元 */
    pstMmlMsg = (NAS_MML_INTERNAL_MSG_BUF_STRU *)&(pstInternalMsgQueue->astNasMmMsgQueue[pstInternalMsgQueue->ucHeader]);

    NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MML_InsertInternalMsgHead: usMsgID is ", pstMmlMsg->usMsgID);

    /* 4. 将内部消息发送到内部消息队列的最前面 */
    PS_MEM_CPY(pstMmlMsg, pstSndMsg, sizeof(NAS_MML_INTERNAL_MSG_BUF_STRU));

    /* 更新内部消息缓冲区 */

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MML_FindPidMsgProc
 功能描述  : 找到接收消息PID的处理函数
 输入参数  : ulRcvPid           :接收消息ID
 输出参数  : 无
 返 回 值  : pNasMmPIdMsgProc   :接收消息处理函数
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年07月21日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数
 2.日    期   : 2011年11月28日
   作    者   : z00161729
   修改内容   : LMM加入MM子层内部消息队列,增加LMM消息处理函数

*****************************************************************************/
pNasMmPIdMsgProc NAS_MML_FindPidMsgProc(
    VOS_UINT32                          ulRcvPid
)
{
    pNasMmPIdMsgProc                    fReturnMsgProcHandle;

    fReturnMsgProcHandle =  VOS_NULL_PTR;
    switch ( ulRcvPid )
    {
        case WUEPS_PID_MM :
            fReturnMsgProcHandle    = MmMsgProc;
            break;
        case WUEPS_PID_GMM :
            fReturnMsgProcHandle    = GmmMsgProc;
            break;
        case WUEPS_PID_MMC :
            fReturnMsgProcHandle    = NAS_MMC_MsgProc;
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case PS_PID_MM:
            fReturnMsgProcHandle    = NAS_MM_PidMsgEntry;
            break;
#endif

        default:
            NAS_WARNING_LOG1(WUEPS_PID_MMC, "NAS_MML_FindPidMsgProc:invalide rcv pid", ulRcvPid);
            break;
    }

    return fReturnMsgProcHandle;
}


/*****************************************************************************
 函 数 名  : NAS_MML_FidMsgProc
 功能描述  : 处理整个MM子层的消息函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2010年11月4日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

 2.日    期   : 2011年7月20日
   作    者   : zhoujun 40661
   修改内容   : 内部缓存队列修改
 3.日    期   : 2011年8月22日
   作    者   : w00167002
   修改内容   : 增加回放消息的处理，这样在内部消息处理完后才会 导出回放消息
                 解决回放消息顺序不对的问题
 4.日    期   : 2012年4月24日
   作    者   : l00171473
   修改内容   : DTS2012041805606
 5.日    期   : 2012年8月8
   作    者   : w00167002
   修改内容   : 处理发给MM/GMM/MMC的消息。
 6.日    期   : 2012年8月25
   作    者   : w00176764
   修改内容   : LMM发给MMC的消息走内部消息队列,需要先进UTRANCTRL模块处理
 7.日    期   : 2012年12月26日
   作    者   : s46746
   修改内容   : DSDA GUNAS C CORE项目，平台不支持LTE时,内部消息队列中L消息丢弃
 8.日    期   : 2013年6月4日
   作    者   : z00161729
   修改内容   : SVLTE 和usim接口调整修改
 9.日    期   : 2014年10月13日
   作    者   : b00269685
   修改内容   : 保存入口消息和出口消息到全局变量，复位coredump可测

*****************************************************************************/
VOS_VOID NAS_MML_MsgProc(
    struct MsgCB                        *pRcvMsg
)
{
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstNextMsg   = VOS_NULL_PTR;
    pNasMmPIdMsgProc                    pMsgProc     = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
#ifndef __PS_WIN32_RECUR__
    VOS_UINT32                          ulIsSndOmPcRecurMsgValid;
#endif
    VOS_UINT32                          ulRslt;
    struct MsgCB                       *pstNextDestMsg;

    /* 入口参数检查 */
    if ( VOS_NULL_PTR == pRcvMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MML_MsgProc:Empty Msg");
        return;
    }

    if (VOS_TRUE == NAS_MML_GetSvlteSupportFlag())
    {
        NAS_MML_ConvertOamSendPid(&pRcvMsg->ulSenderPid);
    }

    pMsgProc = NAS_MML_FindPidMsgProc(pRcvMsg->ulReceiverPid);

    /* 未找到处理函数直接返回 */
    if ( VOS_NULL_PTR == pMsgProc )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MML_MsgProc:Invalid rcv pid");
        return;
    }

    /* 先处理外部消息 */
    pMsgProc(pRcvMsg);

    /* 外部消息处理完成后处理内部消息 */
    pstNextMsg = NAS_MML_GetNextInternalMsg();

    while (VOS_NULL_PTR != pstNextMsg)
    {
#if (FEATURE_ON == FEATURE_LTE)
        if (PS_PID_MM == pstNextMsg->ulSenderPid)
        {
            pstMsgHeader = (MSG_HEADER_STRU *)pstNextMsg;

            NAS_MML_LogMsgInfo(pstMsgHeader);

        }
#endif

        pMsgProc = NAS_MML_FindPidMsgProc(pstNextMsg->ulReceiverPid);

        /* 未找到处理函数直接返回 */
        if ( VOS_NULL_PTR == pMsgProc )
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MML_MsgProc:Invalid rcv pid");
        }
#if (FEATURE_ON == FEATURE_LTE)
        else if ((VOS_FALSE == NAS_MML_IsPlatformSupportLte())
              && (PS_PID_MM == pstNextMsg->ulReceiverPid))
        {
            NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MML_MsgProc:Platform not support Lte");
        }
#endif
        else
        {
            /* 将该消息钩出来,以便于在PSTAS中显示 */
            DIAG_TraceReport(pstNextMsg);


            /* 将当前消息进入UTRANCTRL模块进行处理 */
            ulRslt = NAS_UTRANCTRL_MsgProc((struct MsgCB *)pstNextMsg, &pstNextDestMsg);

            /* 消息在UTRANCTRL模块处理完成，直接返回，不进入后续处理 */
            if ( VOS_FALSE == ulRslt )
            {
                pMsgProc((struct MsgCB *)pstNextDestMsg);
            }

        }

        /* 寻找下一条内部消息 */
        pstNextMsg = NAS_MML_GetNextInternalMsg();
    }

#ifndef __PS_WIN32_RECUR__

    ulIsSndOmPcRecurMsgValid = NAS_MML_IsSndOmPcRecurMsgValid();

    if ( (VOS_TRUE == NAS_MML_GetUePcRecurFlg())
      && (VOS_TRUE == ulIsSndOmPcRecurMsgValid))
    {
        NAS_MML_SetUePcRecurFlg(VOS_FALSE);

        NAS_MMC_SndOutsideContextData();
        NAS_MM_SndOutsideContextData();
        NAS_GMM_SndOutsideContextData();
    }

#endif


    return;
}




/*****************************************************************************
 函 数 名  : NAS_MML_FidMsgProc
 功能描述  : 处理整个MM子层的消息函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2010年11月4日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

 2.日    期   : 2011年7月20日
   作    者   : zhoujun 40661
   修改内容   : 内部缓存队列修改
 3.日    期   : 2011年8月22日
   作    者   : w00167002
   修改内容   : 增加回放消息的处理，这样在内部消息处理完后才会 导出回放消息
                 解决回放消息顺序不对的问题
 4.日    期   : 2012年4月24日
   作    者   : l00171473
   修改内容   : DTS2012041805606
 5.日    期   : 2012年7月13日
   作    者   : w00167002
   修改内容   : 增加针对TD模消息的适配处理:当软件版本支持TD时，接入层发给
                 NAS层的消息，会先进入适配模块进行处理，如果适配层处理后不
                 需要进入原来的消息处理函数，则直接退出，否则若消息的发送方
                 是TD接入层，则消息发送方PID改为W接入层的发送方PID后，再进入状态机处理。

 6.日    期   : 2012年7月13日
   作    者   : w00167002
   修改内容   : V7R1C50_GUTL_PhaseII:增加针对UTRANCTRL适配模块缓存消息的处理。
 7.日    期   : 2012年12月13日
   作    者   : L00171473
   修改内容   : DTS2012121802573, TQE清理
 8.日    期   : 2014年10月13日
   作    者   : b00269685
   修改内容   : 保存入口消息和出口消息到全局变量，复位coredump可测
*****************************************************************************/
VOS_UINT32  NAS_MML_FidMsgProc(
    struct MsgCB                        *pRcvMsg
)
{
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    struct MsgCB                       *pstDestMsg;
    VOS_UINT32                          ulRslt;


    pstDestMsg = VOS_NULL_PTR;

    /* 入口参数检查 */
    if ( VOS_NULL_PTR == pRcvMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MML_FidMsgProc:Empty Msg");
        return VOS_ERR;
    }

    pstMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;

    NAS_MML_LogMsgInfo(pstMsgHeader);


    /* 将当前消息进入UTRANCTRL模块进行处理 */
    ulRslt = NAS_UTRANCTRL_MsgProc(pRcvMsg, &pstDestMsg);

    /* 消息在UTRANCTRL模块处理完成，直接返回，不进入后续处理 */
    if ( VOS_TRUE == ulRslt )
    {
        return VOS_OK;
    }

    /* 如果经过UTRUNCTRL处理消息改变，则在记录一次 */
    if (pRcvMsg != pstDestMsg)
    {
        NAS_MML_LogMsgInfo(pstMsgHeader);
    }

    /* 处理从UTRANCTRL模块返回的消息 */
    NAS_MML_MsgProc(pstDestMsg);

    /* 处理UTRANCTRL模块缓存的消息 */
    NAS_UTRANCTRL_ProcBufferMsg();

    NAS_MML_UpdateExitTime();

    return VOS_OK;
}



/*****************************************************************************
 函 数 名  : NAS_MML_FidInit
 功能描述  : MM子层FID初始化
 输入参数  : enInitPhase:初始化阶段
 输出参数  : 无
 返 回 值  : VOS_OK:初始化成功
             VOS_ERR:初始化失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月6日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2011年11月28日
   作    者   : z00161729
   修改内容   : LMM加入MM子层内部消息队列，FID初始化时增加注册LMM PID初始化函数和消息处理函数
  3.日    期   : 2012年2月9日
    作    者   : w00167002
    修改内容   : 初始化时封装PID的处理，明确MMC函数的初始化处理。
  4.日    期   : 2012年5月9日
    作    者   : z60575
    修改内容   : DTS2012050905268, C核任务优先级调整
  5.日    期   : 2012年12月28日
    作    者   : s46746
    修改内容   : DSDA GUNAS C CORE项目，增加PS_PID_MM根据modem初始化
  6.日    期   : 2015年5月29日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_UINT32 NAS_MML_FidInit (
    enum VOS_INIT_PHASE_DEFINE          enInitPhase
)
{
    VOS_UINT32 ulReturnCode;

    switch( enInitPhase )
    {
        case   VOS_IP_LOAD_CONFIG:
#if defined(INSTANCE_1)
            (VOS_VOID)mdrv_pm_wake_lock(PWRCTRL_SLEEP_NAS_1);
#elif defined(INSTANCE_2)
            (VOS_VOID)mdrv_pm_wake_lock(PWRCTRL_SLEEP_NAS_2);
#else
            (VOS_VOID)mdrv_pm_wake_lock(PWRCTRL_SLEEP_NAS);
#endif

            ulReturnCode = VOS_RegisterPIDInfo(WUEPS_PID_MM,
                                  (Init_Fun_Type) WuepsMmPidInit,
                                  (Msg_Fun_Type) NAS_MML_FidMsgProc);
            if( VOS_OK != ulReturnCode )
            {
                return VOS_ERR;
            }

            ulReturnCode = VOS_RegisterPIDInfo(WUEPS_PID_MMC,
                                      (Init_Fun_Type) NAS_MMC_InitPid,
                                      (Msg_Fun_Type) NAS_MML_FidMsgProc);
            if( VOS_OK != ulReturnCode )
            {
                return VOS_ERR;
            }

            ulReturnCode = VOS_RegisterPIDInfo(WUEPS_PID_GMM,
                                  (Init_Fun_Type) WuepsGmmPidInit,
                                  (Msg_Fun_Type) NAS_MML_FidMsgProc);
            if( VOS_OK != ulReturnCode )
            {
                return VOS_ERR;
            }


            /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-9, begin */
            ulReturnCode = VOS_RegisterPIDInfo(WUEPS_PID_MMA,
                                    (Init_Fun_Type) TAF_MMA_InitPid,
                                    (Msg_Fun_Type)TAF_MMA_MsgProcEntry);
            /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-9, end */

            if( VOS_OK != ulReturnCode )
            {
                return VOS_ERR;
            }

#ifndef DMT
#if (FEATURE_ON == FEATURE_LTE)
    #if defined(INSTANCE_1) || defined(INSTANCE_2)
            /* 双卡双通modem1不编译L模 */
    #else
            ulReturnCode = VOS_RegisterPIDInfo(PS_PID_MM,
                          (Init_Fun_Type) NAS_MM_PidInit,
                          (Msg_Fun_Type) NAS_MML_FidMsgProc  );
    #endif
#endif
#endif

            ulReturnCode = VOS_RegisterTaskPrio(WUEPS_FID_MM,
                                                NAS_MM_TASK_PRIO);

            if( VOS_OK != ulReturnCode )
            {
                return VOS_ERR;
            }

            break;
        case   VOS_IP_FARMALLOC:
        case   VOS_IP_INITIAL:
        case   VOS_IP_ENROLLMENT:
        case   VOS_IP_LOAD_DATA:
        case   VOS_IP_FETCH_DATA:
        case   VOS_IP_STARTUP:
        case   VOS_IP_RIVAL:
        case   VOS_IP_KICKOFF:
        case   VOS_IP_STANDBY:
        case   VOS_IP_BROADCAST_STATE:
        case   VOS_IP_RESTART:
        case   VOS_IP_BUTT:
            break;

    }

    return VOS_OK;
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

