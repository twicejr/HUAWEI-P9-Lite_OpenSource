/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasUtranCtrCommFunc.c
  版 本 号   : 初稿
  作    者   : w00167002
  生成日期   : 2012年7月12日
  最近修改   :
  功能描述   : NasUtranCtrCommFunc.C文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年7月12日
    作    者   : w00167002
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "NasComm.h"
#include "NVIM_Interface.h"
#include "SysNvId.h"

#include "nasasapi.h"
#include "TcNasinterface.h"
#include "Nasrrcinterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasPdcpInterface.h"
#include "RabmExtFunc.h"

#include "NasUtranCtrlCtx.h"
#include "NasUtranCtrlInterface.h"
#include "NasUtranCtrlCommFunc.h"
#include "NasRlcInterface.h"

#include "NasMmcCtx.h"
#include "NasUtranCtrlMain.h"
#include "NasMmlMsgProc.h"
#include "NasMmcComFunc.h"
#include "NasMmlLib.h"
#include "NasMmcProcUsim.h"

#include "NasMmcSndGuAs.h"

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
#include "NasDynLoadApi.h"
#include "NasDynLoad.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_COMM_FUNC_C

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/


/*****************************************************************************
  5 变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  6 函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_ConvertNasUtranModeToRrcUtranMode
 功能描述  : 将NAS内部的UTRAN MODE类型转换为和GU接入层间的UTRAN MODE类型
 输入参数  : enNasUtranMode:NAS内部的UTRAN MODE类型
 输出参数  : 无
 返 回 值  : RRC_NAS_UTRAN_MODE_ENUM_UINT8: 和GU接入层间的UTRAN MODE类型
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月21日
   作    者   : L00171473
   修改内容   : 新生成函数
 2.日    期   : 2012年7月21日
   作    者   : w00167002
   修改内容   : V7R1C50_GUTL_PhaseII:通知接入层模式为BUTT时异常，进行打印，并转
                 换为FDD模式。
 3.日    期   : 2013年1月11日
   作    者   : s00217060
   修改内容   : for DSDA GUNAS C CORE:平台不支持GU时，默认给接入层发送的UtranMode为TDD
 4.日    期   : 2015年8月24日
   作    者   : w00242748
   修改内容   : 动态加载项目
*****************************************************************************/
RRC_NAS_UTRAN_MODE_ENUM_UINT8 NAS_UTRANCTRL_ConvertNasUtranModeToGuRrcUtranMode(
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enNasUtranMode
)
{
    RRC_NAS_UTRAN_MODE_ENUM_UINT8       enRrcUtranMode;

    switch ( enNasUtranMode )
    {
        case NAS_UTRANCTRL_UTRAN_MODE_FDD :
            enRrcUtranMode = RRC_NAS_UTRAN_MODE_FDD;
            break;

        case NAS_UTRANCTRL_UTRAN_MODE_TDD :
            enRrcUtranMode = RRC_NAS_UTRAN_MODE_TDD;
            break;

        case NAS_UTRANCTRL_UTRAN_MODE_NULL :
            enRrcUtranMode = RRC_NAS_UTRAN_MODE_NULL;
            break;

        default:

            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_ConvertNasUtranModeToGuRrcUtranMode:UTRANMODE IS BUTT! ");
            /* 平台不支持GU时，默认给接入层发送的UtranMode为TDD */
            enRrcUtranMode = RRC_NAS_UTRAN_MODE_TDD;

            break;
    }

    return enRrcUtranMode;
}

#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_ConvertNasUtranModeToLmmUtranMode
 功能描述  : 将NAS内部的UTRAN MODE类型转换为和LMM间的UTRAN MODE类型
 输入参数  : enNasUtranMode:NAS内部的UTRAN MODE类型
 输出参数  : 无
 返 回 值  : MMC_LMM_UTRAN_MODE_ENUM_UINT8: 和LMM间的UTRAN MODE类型
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月21日
   作    者   : L00171473
   修改内容   : 新生成函数
 2.日    期   : 2012年7月21日
   作    者   : w00167002
   修改内容   : V7R1C50_GUTL_PhaseII:通知接入层模式为BUTT时异常，进行打印，并转
                 换为FDD模式。
 3.日    期   : 2013年1月11日
   作    者   : s00217060
   修改内容   : for DSDA GUNAS C CORE:平台不支持GU时，默认给接入层发送的UtranMode为TDD
 4.日    期   : 2015年8月24日
   作    者   : w00242748
   修改内容   : 动态加载项目
*****************************************************************************/
MMC_LMM_UTRAN_MODE_ENUM_UINT8 NAS_UTRANCTRL_ConvertNasUtranModeToLmmUtranMode(
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enNasUtranMode
)
{
    MMC_LMM_UTRAN_MODE_ENUM_UINT8       enLmmUtranMode;

    switch ( enNasUtranMode )
    {
        case NAS_UTRANCTRL_UTRAN_MODE_FDD :
            enLmmUtranMode = MMC_LMM_UTRAN_MODE_FDD;
            break;

        case NAS_UTRANCTRL_UTRAN_MODE_TDD :
            enLmmUtranMode = MMC_LMM_UTRAN_MODE_TDD;
            break;

        case NAS_UTRANCTRL_UTRAN_MODE_NULL :
            enLmmUtranMode = MMC_LMM_UTRAN_MODE_NULL;
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_ConvertNasUtranModeToLmmUtranMode:UTRANMODE IS BUTT! ");
            /* 平台不支持GU时，默认给LMM发送的UtranMode为TDD */
            enLmmUtranMode = MMC_LMM_UTRAN_MODE_TDD;
            break;
    }

    return enLmmUtranMode;
}

#endif  /* (FEATURE_ON == FEATURE_LTE) */

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RABM_AdaptPdcpDataReq
 功能描述  : 适配TDS,根据不同的模式调用不同模的PDCP接口函数，发送数据
 输入参数  :  ucRbId: Rb ID
              pstData: 数据地址
              ulDataBitLen: 数据长度

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月13日
   作    者   : w00167002
   修改内容   : V7R1C50_GUTL_PhaseI:新增函数

*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_RABM_AdaptPdcpDataReq(
    VOS_UINT8                           ucRbId,
    TTF_MEM_ST                         *pstData,
    VOS_UINT32                          ulDataBitLen
)
{
    /* 数据发送结果 */
    VOS_UINT32                          ulDataSendRslt;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8  enCurrentUtranMode;

    /* 取得当前的UTRAN模式 */
    enCurrentUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    /* 默认数据发送结果 */
    ulDataSendRslt = PS_FAIL;

    /* 根据不同的UTRAN模式调用不同的API进行处理 */
    switch ( enCurrentUtranMode )
    {
        /* W模的处理 */
        case NAS_UTRANCTRL_UTRAN_MODE_FDD :
            ulDataSendRslt = WTTF_PDCP_RcvRabmData(ucRbId, pstData, ulDataBitLen);
            break;

        /* TD模的处理 */
#if ( FEATURE_ON == FEATURE_UE_MODE_TDS )
        case NAS_UTRANCTRL_UTRAN_MODE_TDD :
            ulDataSendRslt = TPDCP_DATA_REQ(ucRbId, pstData, ulDataBitLen);
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_RABM, "NAS_UTRANCTRL_RABM_AdaptPdcpDataReq:WARNING:UTRAN MODE NOT EXIST!");
            ulDataSendRslt = WTTF_PDCP_RcvRabmData(ucRbId, pstData, ulDataBitLen);
            break;
    }

    NAS_INFO_LOG2(WUEPS_PID_MMC, "NAS_UTRANCTRL_RABM_AdaptPdcpDataReq: Data Snd Failed! enCurrentUtranMode, ulDataSendRslt",
                  enCurrentUtranMode, ulDataSendRslt);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RABM_GetRbSuitableUlPduSize
 功能描述  : 适配TDS,根据不同的模式调用不同模的获取PDU大小接口函数，发送数据
 输入参数  : ucRbId: Rb ID
              pstData: 数据地址
              ulDataBitLen: 数据长度

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月13日
   作    者   : w00167002
   修改内容   : V7R1C50_GUTL_PhaseI:新增函数
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_RABM_GetRbSuitableUlPduSize(
    VOS_UINT8                          ucRbId,
    VOS_UINT32                         ulPduSize,
    VOS_UINT8                          ucCrcSize,
    VOS_UINT32                        *pulUlPduSize
)
{
    /* 数据发送结果 */
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8  enCurrentUtranMode;

    /* 取得当前的UTRAN模式 */
    enCurrentUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    /* 根据不同的UTRAN模式调用不同的API进行处理 */
    switch ( enCurrentUtranMode )
    {
        /* W模的处理 */
        case NAS_UTRANCTRL_UTRAN_MODE_FDD :
            (VOS_VOID)WTTF_RLC_GetRbSuitableUlPduSize(ucRbId,
                                           ulPduSize,
                                           ucCrcSize,
                                           pulUlPduSize);
            break;

        /* TD模的处理 */
#if ( FEATURE_ON == FEATURE_UE_MODE_TDS )
        case NAS_UTRANCTRL_UTRAN_MODE_TDD :
            (VOS_VOID)TDS_RLC_GetRbSuitableUlPduSize(ucRbId,
                                           ulPduSize,
                                           ucCrcSize,
                                           pulUlPduSize);

            break;
#endif

        default:
            NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_UTRANCTRL_RABM_GetRbSuitableUlPduSize:ERROR:UTRAN MODE Error!");
            (VOS_VOID)WTTF_RLC_GetRbSuitableUlPduSize(ucRbId,
                                            ulPduSize,
                                            ucCrcSize,
                                            pulUlPduSize);
            break;
    }

    return;
}

/*******************************************************************************
  Module:   NAS_UTRANCTRL_RABM_SendTcDataNotify
  Function: PDCP向RABM发送下行环回数据消息 ID_PDCP_RABM_TC_DATA_IND_NOTIFY
  Input:    VOS_VOID
  Output:   VOS_VOID
  NOTE:
  Return:   PS_SUCC   --- 成功
            PS_FAIL   --- 失败
  History:
  1.日    期   : 2012年7月14日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseI: 确认当前UTRAN模式，进而确认当前的发送
                  PID和接收PID.
  2.日    期   : 2012年7月19日
    作    者   : l00171473
    修改内容   : V7R1C50_GUTL_PhaseI: 从Rabm文件中移到UTRANCTRL文件中
*******************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RABM_SendTcDataNotify(VOS_VOID)
{
    PDCP_RABM_TC_DATA_IND_NOTIFY_STRU  *pstMsg;

    VOS_UINT32                          ulSendRslt;
#if ( FEATURE_ON == FEATURE_UE_MODE_TDS )
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrentUtranMode;
#endif


    /*申请消息内存:*/
    pstMsg = (PDCP_RABM_TC_DATA_IND_NOTIFY_STRU *)PS_ALLOC_MSG( WUEPS_PID_RABM,
        sizeof(PDCP_RABM_TC_DATA_IND_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH );

    if (VOS_NULL_PTR == pstMsg)
    {
        /*打印出错信息---申请消息包失败:*/
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_UTRANCTRL_RABM_SendTcDataNotify:WARNING: Allocates a message packet for ID_PDCP_RABM_TC_DATA_IND_NOTIFY msg FAIL!");
        return PS_FAIL;
    }

    /*填写消息内容:*/
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;

    /* 默认当前的发送pid为W模 */
    pstMsg->ulSenderPid     = WUEPS_PID_PDCP;

#if ( FEATURE_ON == FEATURE_UE_MODE_TDS )

    /* 取得当前的UTRAN模式 */
    enCurrentUtranMode      = NAS_UTRANCTRL_GetCurrUtranMode();

    /* TD被支持时,更改发送PID为TD模 */
    if ( NAS_UTRANCTRL_UTRAN_MODE_TDD == enCurrentUtranMode )
    {
        pstMsg->ulSenderPid = TPS_PID_PDC;
    }
#endif

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_RABM;
    pstMsg->enMsgName       = ID_PDCP_RABM_TC_DATA_IND_NOTIFY;

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    ulSendRslt = PS_SEND_MSG(pstMsg->ulSenderPid, pstMsg);

    if ( VOS_OK != ulSendRslt )
    {
        /* 打印警告信息---发送消息失败:*/
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_UTRANCTRL_RABM_SendTcDataNotify:WARNING: SEND ID_PDCP_RABM_TC_DATA_IND_NOTIFY msg FAIL!");
        return PS_FAIL;
    }

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_RABM_SetFinIpInRdFlag
 功能描述  : 设置CDS读取一次RD后处理最后一个IP包标识
 输入参数  : ulFlag
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月20日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2013年4月23日
    作    者   : z60575
    修改内容   : GU/TD组包优化合入
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_RABM_SetFinIpInRdFlag(VOS_UINT32 ulFlag)
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8  enCurrentUtranMode;

    /* 取得当前的UTRAN模式 */
    enCurrentUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    /* 根据不同的UTRAN模式调用不同的API进行处理 */
    switch (enCurrentUtranMode)
    {
        /* W模的处理 */
        case NAS_UTRANCTRL_UTRAN_MODE_FDD :
            WTTF_PDCP_TrigRlcUlProc();
            break;

        /* TD模的处理 */
#if ( FEATURE_ON == FEATURE_UE_MODE_TDS )
        case NAS_UTRANCTRL_UTRAN_MODE_TDD :
            TPDCP_IntUlDataProc();
            break;
#endif

        default:
            NAS_NORMAL_LOG(WUEPS_PID_RABM,
                "NAS_UTRANCTRL_RABM_SetFinIpInRdFlag:WARNING:UTRAN MODE NOT MATCH!");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SndAsMsg
 功能描述  : UTRAN控制模块发送WRR或TD消息
 输入参数  : ulSndPid -- 发送PID
             pstMsg  -- 发送消息
 输出参数  : 无
 返 回 值  : VOS_OK:发送成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月14日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年8月8日
    作    者   : w00176964
    修改内容   : 发送搜网请求时缓存发送给W的搜网请求消息
  3.日    期   : 2012年8月21日
    作    者   : w00167002
    修改内容   : 当前消息除了通知当前UTRAN模外，还需要判断是否需要通知另一模
  4.日    期   : 2012年12月25日
    作    者   : s00217060
    修改内容   : for DSDA GUNAS C CORE:平台接入技术能力只支持W/TD中的一个时，不需要给另一个模发消息，
                  不进预处理的函数
  5.日    期   : 2014年3月3日
    作    者   : z00234330
    修改内容   : dts2014022806114,没有释放内存
  6.日    期   : 2015年6月6日
    作    者   : s00217060
    修改内容   : 漫游搜网优化2.0
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_SndAsMsg(
    VOS_UINT32                          ulSndPid,
    struct MsgCB                       **ppstMsg
)
{
#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
    VOS_RATMODE_ENUM_UINT32             enRatMode;
#endif
#if ( FEATURE_ON == FEATURE_UE_MODE_TDS )
    MSG_HEADER_STRU                    *pstMsgHeader        = VOS_NULL_PTR;
    RRMM_PLMN_SEARCH_REQ_STRU          *pstPlmnSrchReq      = VOS_NULL_PTR;
    VOS_UINT32                          ulSupportFddFlg;
    VOS_UINT32                          ulSupportTddFlg;
#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
    VOS_RATMODE_ENUM_UINT32             enRatInCached;
#endif

    pstMsgHeader    = (MSG_HEADER_STRU *)*ppstMsg;
    pstPlmnSrchReq  = (RRMM_PLMN_SEARCH_REQ_STRU *)*ppstMsg;
    ulSupportFddFlg = NAS_MML_IsPlatformSupportUtranFdd();
    ulSupportTddFlg = NAS_MML_IsPlatformSupportUtranTdd();

    /* 对GET_GEO类型的搜网请求特殊处理 */
    if ((RRMM_PLMN_SEARCH_REQ    == pstMsgHeader->ulMsgName)
     && (RRC_PLMN_SEARCH_GET_GEO == pstPlmnSrchReq->ulSearchType))
    {
        NAS_MML_SaveNwSearchReqInfo(pstPlmnSrchReq);

        NAS_UTRANCTRL_ProcPlmnSearchReq_GetGeo(ulSndPid, pstPlmnSrchReq);

        return VOS_OK;
    }

    /* 如果当前是发给UTRAN模块的，并且平台对FDD/TDD都支持，则在发送消息前进行预处理
       如果平台只支持FDD/TDD中的一个，不需要预处理，直接判断是否替换PID即可 */
    if ( (WUEPS_PID_WRR == pstMsgHeader->ulReceiverPid)
      && (VOS_TRUE == ulSupportFddFlg)
      && (VOS_TRUE == ulSupportTddFlg) )
    {

        if ( VOS_TRUE == NAS_UTRANCTRL_IsNeedSkipSearchUtranFddMode(*ppstMsg) )
        {
            /* UTRANCTRL模块对发送消息的保存预处理 */
            NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg_SndUtranAsMsgPreProcessMsg(ulSndPid,
                                                                   *ppstMsg);
            /* 跳过搜索W,直接给MMC发送W下搜网失败 */
            NAS_MMC_SndInterSkipSearchWIndMsg();

            PS_FREE_MSG(ulSndPid, *ppstMsg);

            return VOS_OK;
        }

        if (VOS_TRUE == NAS_UTRANCTRL_IsNeedSkipSearchUtranTddMode(*ppstMsg))
        {
            /* UTRANCTRL模块对发送消息的保存预处理 */
            NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg_SndUtranAsMsgPreProcessMsg(ulSndPid,
                                                                   *ppstMsg);
            /* 跳过搜索tds,直接给MMC发送tds下搜网失败 */
            NAS_MMC_SndInterSkipSearchTdsIndMsg();

            PS_FREE_MSG(ulSndPid, *ppstMsg);
            return VOS_OK;
        }

        NAS_UTRANCTRL_SndUtranAsMsgPreProcessMsg(ulSndPid, *ppstMsg);
    }

    /* TD被支持时,当前的UTRAN为T模  */
    if ( NAS_UTRANCTRL_UTRAN_MODE_TDD == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        switch (pstMsgHeader->ulReceiverPid)
        {
            case WUEPS_PID_PDCP:

                pstMsgHeader->ulReceiverPid = TPS_PID_PDC;
                break;

            case WUEPS_PID_WRR:

                pstMsgHeader->ulReceiverPid = TPS_PID_RRC;
                break;

            case WUEPS_PID_RLC:

                pstMsgHeader->ulReceiverPid = TPS_PID_RLC;
                break;

            default:
                break;
        }
    }

#endif

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)*ppstMsg);

    /* 保存搜网请求信息 */
    if (RRMM_PLMN_SEARCH_REQ == pstMsgHeader->ulMsgName)
    {
        NAS_MML_SaveNwSearchReqInfo(pstPlmnSrchReq);
    }

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
    if (VOS_TRUE == NAS_DYNLOAD_GetEnableDynloadTWFlg())
    {
        if ( (RRMM_PLMN_SEARCH_REQ == pstMsgHeader->ulMsgName)
          && ( (WUEPS_PID_WRR == pstMsgHeader->ulReceiverPid)
            || (TPS_PID_RRC == pstMsgHeader->ulReceiverPid) ) )
        {
            enRatMode = (WUEPS_PID_WRR == pstMsgHeader->ulReceiverPid) ? VOS_RATMODE_WCDMA : VOS_RATMODE_TDS;

            (VOS_VOID)NAS_DYNLOAD_LoadAS(NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W, enRatMode);
        }

        /* 针对场景utranctrl模块中挂起U，但当前模式是TDD，此时utranctrl模块会构造搜网失败消息
           给MMC，这时MMC需要发送RRMM_SUSPEND_REQ,但utranctrl模块这时模式为TDD，所以会给TDS发
           送挂起指示，但此时的TDS可能没有被加载 */
        if ( (RRMM_SUSPEND_REQ == pstMsgHeader->ulMsgName)
          && ( (WUEPS_PID_WRR == pstMsgHeader->ulReceiverPid)
            || (TPS_PID_RRC == pstMsgHeader->ulReceiverPid) ) )
        {
            enRatInCached = NAS_DYNLOAD_GetCurRatInCached(NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W);

            pstMsgHeader->ulReceiverPid = (VOS_RATMODE_WCDMA == enRatInCached) ? WUEPS_PID_WRR : TPS_PID_RRC;
        }
    }

#endif



    if (VOS_OK != PS_SEND_MSG(ulSndPid, *ppstMsg))
    {
        /* 打印警告信息---发送消息失败:*/
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndAsMsg:WARNING: SEND utran msg FAIL!");

        return VOS_ERR;
    }

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_BuildEventType
 功能描述  : 根据usSndPid和usMsgName来构造当前的事件类型
 输入参数  : usSndPid:  发送PID信息
              usMsgName: 发送消息名称信息
 输出参数  : 无
 返 回 值  : VOS_UINT32:事件类型
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月13日
   作    者   : w00167002
   修改内容   : 新生成函数

  2.日    期   : 2015年6月6日
    作    者   : l00198894
    修改内容   : Modem PID扩展
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_BuildEventType (
    VOS_UINT32                          ulSndPid,
    VOS_UINT32                          ulMsgName
)
{
    VOS_UINT32                          ulEventType;

    /*
        约束: PID结构 Bit0~Bit11: 模块ID  Bit12~Bit15: 保留 Bit16~Bit19: CPU ID Bit20~Bit31: 保留
        例: PID: 0x000A0BCD  ->  0x0000ABCD  ->  0xABCD0000
            MSG: 0x0000abcd
            EVT: 0xABCDabcd
    */
    ulEventType = ((((ulSndPid) & 0xF0000) | (((ulSndPid) & 0xFFF) << 4)) << 12);

    ulEventType |= ulMsgName;

    return ulEventType;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetMsgEventType
 功能描述  : 获取消息的事件类型
 输入参数  : pstMsg       :消息内容
 输出参数  : 无
 返 回 值  : VOS_UINT32: ulEventType消息事件类型
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月14日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2012年8月20日
    作    者   : w00176964
    修改内容   : 定时器超时停止UTRANCTRL模块的定时器
  3.日    期   : 2015年6月6日
    作    者   : l00198894
    修改内容   : Modem PID 扩展
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_GetMsgEventType(
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulEventType;
    REL_TIMER_MSG                      *pRcvTimerMsg;
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* 动作表里的时间消息不能靠消息头名称进行区分，依靠其结构体的ulName域进行区分
       所以此处进行分别处理
    */
    if ( VOS_PID_TIMER == pstMsgHeader->ulSenderPid )
    {
        pRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

        ulEventType  = NAS_UTRANCTRL_BuildEventType(pstMsgHeader->ulSenderPid, pRcvTimerMsg->ulName);
    }
    else
    {
        ulEventType  = NAS_UTRANCTRL_BuildEventType(pstMsgHeader->ulSenderPid, pstMsgHeader->ulMsgName);
    }

    return ulEventType;

}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_ConvertSimPlmnToNasPlmn
 功能描述  : 将SIM卡中的3字节格式PLMN转换为MCC和MNC分开的格式
 输入参数  : pstSimPlmn -- SIM卡结构的PLMN
 输出参数  : pstNasPlmn -- NAS内部结构的PLMN
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月19日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_ConvertSimPlmnToNasPlmn(
    NAS_MML_SIM_FORMAT_PLMN_ID          *pstSimPlmn,
    NAS_MML_PLMN_ID_STRU                *pstNasPlmn
)
{
    NAS_MMC_ConvertSimPlmnToNasPLMN(pstSimPlmn, pstNasPlmn);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_StartTimer
 功能描述  : 启动指定的MMC定时器
 输入参数  : enTimerId - 需要启动的定时器ID
             ulLen-定时器时长
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月9日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_StartTimer(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId,
    VOS_UINT32                          ulLen
)
{
    (VOS_VOID)NAS_MMC_StartTimer(enTimerId, ulLen);
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetTimerStatus
 功能描述  : 查询指定的MMC定时器的状态
 输入参数  : enTimerId  - 需要查询的定时器ID
 输出参数  : 无
 返 回 值  : NAS_MMC_TIMER_STATUS_ENUM_U8:定时器状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_TIMER_STATUS_ENUM_U8  NAS_UTRANCTRL_GetTimerStatus(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId
)
{
    NAS_MMC_TIMER_STATUS_ENUM_U8        enTimerStatus;

    enTimerStatus = NAS_MMC_GetTimerStatus(enTimerId);

    return enTimerStatus;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_StopTimer
 功能描述  : 停止指定的MMC定时器
 输入参数  : enTimerId - 需要停止的定时器ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月9日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_StopTimer(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId
)
{
   NAS_MMC_StopTimer(enTimerId);
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SndGuAsUtranModeReq
 功能描述  : UTRAN控制模块发送GU接入层当前的UTRAN工作模式消息
 输入参数  : ulRcvPid:接受PID
             enMode:当前UTRAN工作模式
 输出参数  : 无
 返 回 值  : VOS_OK:发送成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月14日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2012年8月8日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:接口消息调整为RRMM_UTRAN_MODE_REQ，调整函数名
  3.日    期   : 2012年8月16日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII: 添加pc回放
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SndGuAsUtranModeReq(
    VOS_UINT32                          ulRcvPid,
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enMode
)
{
    VOS_UINT32                          ulRet;

    /* 定义原语类型指针 */
    RRMM_UTRAN_MODE_REQ_STRU           *pstMsg = VOS_NULL_PTR;

    pstMsg = (RRMM_UTRAN_MODE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                  WUEPS_PID_MMC,
                                                  sizeof(RRMM_UTRAN_MODE_REQ_STRU));
    /* 内存申请失败 */
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsUtranModeReq():ERROR:Memory Alloc Error for pstMsg");

        /* 返回失败 */
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(RRMM_UTRAN_MODE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = ulRcvPid;
    pstMsg->MsgHeader.ulLength          = sizeof(RRMM_UTRAN_MODE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->MsgHeader.ulMsgName         = RRMM_UTRAN_MODE_REQ;

    pstMsg->enUtranMode                 = NAS_UTRANCTRL_ConvertNasUtranModeToGuRrcUtranMode(enMode);

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /*发送消息*/
    ulRet = PS_SEND_MSG( WUEPS_PID_MMC, pstMsg);

    if (VOS_OK != ulRet)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsUtranModeReq():WARNING:MMC SEND failed!");
    }

#ifndef __PS_WIN32_RECUR__
    NAS_UTRANCTRL_SetUePcRecurFlg(VOS_TRUE);
#endif

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SndLmmUtranModeReq
 功能描述  : UTRAN控制模块发送LMM当前的UTRAN工作模式消息
 输入参数  : enMode:发送给LMM的UTRAN工作模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月14日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2012年8月8日
    作    者   : w00167002
    修改内容   : 接口调整ID_MMC_LMM_UTRAN_MODE_REQ，函数命名调整

  3.日    期   : 2012年8月16日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII: 添加pc回放

  4.日    期   : 2012年8月16日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII: 给LMM发送模式通知时候不能走MMC模块的
                  内部队列，否则MODE CHANGE消息一直得不到处理，直至超时。
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SndLmmUtranModeReq(
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8  enMode
)
{
    /* 定义调用VOS发送函数的返回值 */
    VOS_UINT32                          ulRet;

    /* 定义原语类型指针 */
    MMC_LMM_UTRAN_MODE_REQ_STRU        *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MMC_LMM_UTRAN_MODE_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_UTRAN_MODE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndLmmUtranModeNotify,ERROR:ALLOC MEM ERROR!");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                         sizeof(MMC_LMM_UTRAN_MODE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = PS_PID_MM;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulLength        = sizeof(MMC_LMM_UTRAN_MODE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId         = ID_MMC_LMM_UTRAN_MODE_REQ;
    pstMsg->enUtranMode     = NAS_UTRANCTRL_ConvertNasUtranModeToLmmUtranMode(enMode);

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    ulRet = PS_SEND_MSG( WUEPS_PID_MMC, pstMsg );

    if( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndLmmUtranModeNotify,ERROR:SNED MSG FAIL!");
        return;
    }

#ifndef __PS_WIN32_RECUR__
    NAS_UTRANCTRL_SetUePcRecurFlg(VOS_TRUE);
#endif

    return;
}


#endif  /* end of #if (FEATURE_ON == FEATURE_LTE) */

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SndGuAsSuspendReq
 功能描述  : UTRAN控制模块发送GU接入层挂起请求
 输入参数  : ulRcvPid:接受PID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年08月8日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年8月16日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII: 添加pc回放
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SndGuAsSuspendReq(
    VOS_UINT32                          ulRcvPid
)
{
    /* 定义调用VOS发送函数的返回值 */
    VOS_UINT32                          ulRet;

    /* 定义原语类型指针 */
    RRMM_SUSPEND_REQ_ST                *pstMsg;

    /* 申请内存  */
    pstMsg = (RRMM_SUSPEND_REQ_ST *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(RRMM_SUSPEND_REQ_ST) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsSuspendReq,ERROR:ALLOC MEM ERROR!");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                         sizeof(RRMM_SUSPEND_REQ_ST) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid   = ulRcvPid;
    pstMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength        = sizeof(RRMM_SUSPEND_REQ_ST) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName       = RRMM_SUSPEND_REQ;
    pstMsg->ucStopCause               = MMC_AS_SUSPEND_STOP_DSP;

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    ulRet = PS_SEND_MSG( WUEPS_PID_MMC, pstMsg );

    if( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsSuspendReq,ERROR:SNED MSG FAIL!");
        return;
    }

#ifndef __PS_WIN32_RECUR__
    NAS_UTRANCTRL_SetUePcRecurFlg(VOS_TRUE);
#endif

}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndAsSuspendRsp
 功能描述  : 向GU as发送挂起回复结果消息
 输入参数  : RRC_NAS_SUSPEND_RESULT_ENUM_UINT8   enSuspendRslt,挂起回复结果
              VOS_UINT32                          ulReceiverPid,接受接入层的PID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月10日
    作    者   : w00167002
    修改内容   : 新生成函数

  2.日    期   : 2012年8月16日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII: 添加pc回放
*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_SndAsSuspendRsp(
    RRC_NAS_SUSPEND_RESULT_ENUM_UINT8   enSuspendRslt,
    VOS_UINT32                          ulReceiverPid
)
{
    VOS_UINT32                          ulResult;
    RRMM_SUSPEND_RSP_ST                *pstAsMsg;

    /*申请消息  */

    pstAsMsg = (RRMM_SUSPEND_RSP_ST*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                 WUEPS_PID_MMC,
                                                 sizeof(RRMM_SUSPEND_RSP_ST));

    /* 内存申请失败,直接返回 */
    if( VOS_NULL_PTR == pstAsMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndAsSuspendRsp():ERROR:Alloc Msg fail");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstAsMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(RRMM_SUSPEND_RSP_ST) - VOS_MSG_HEAD_LENGTH );

    /*填写消息内容*/
    pstAsMsg->MsgHeader.ulMsgName       = RRMM_SUSPEND_RSP;
    pstAsMsg->MsgHeader.ulReceiverPid   = ulReceiverPid;
    pstAsMsg->MsgHeader.ulLength        = sizeof(RRMM_SUSPEND_RSP_ST) - VOS_MSG_HEAD_LENGTH;
    pstAsMsg->ucResult                  = enSuspendRslt;

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstAsMsg);

    /*发送消息*/
    ulResult = PS_SEND_MSG(WUEPS_PID_MMC, pstAsMsg);

    if (VOS_OK != ulResult)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndAsSuspendRsp():WARNING:MMC SEND AS SUSPEND RSP failed!");
    }

    return ;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SndGuAsPlmnStopReq
 功能描述  : UTRAN控制模块发送GU接入层停止搜网请求
 输入参数  : ulRcvPid:接受PID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年08月8日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年8月16日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII: 添加pc回放
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SndGuAsPlmnStopReq(
    VOS_UINT32                          ulRcvPid
)
{
    /* 定义调用VOS发送函数的返回值 */
    VOS_UINT32                          ulRet;

    /* 定义原语类型指针 */
    RRMM_PLMN_SEARCH_STOP_REQ_ST       *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (RRMM_PLMN_SEARCH_STOP_REQ_ST *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(RRMM_PLMN_SEARCH_STOP_REQ_ST) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsPlmnStopReq,ERROR:ALLOC MEM ERROR!");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                         sizeof(RRMM_PLMN_SEARCH_STOP_REQ_ST) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid   = ulRcvPid;
    pstMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength        = sizeof(RRMM_PLMN_SEARCH_STOP_REQ_ST) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName       = RRMM_PLMN_SEARCH_STOP_REQ;

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    ulRet = PS_SEND_MSG( WUEPS_PID_MMC, pstMsg );

    if( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsPlmnStopReq,ERROR:SNED MSG FAIL!");
    }

#ifndef __PS_WIN32_RECUR__
    NAS_UTRANCTRL_SetUePcRecurFlg(VOS_TRUE);
#endif
    return;

}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SndGuAsSpecPlmnSearchReq
 功能描述  : UTRAN控制模块发送GU接入层指定搜网请求
 输入参数  : ulRcvPid:接受PID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年08月8日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年8月16日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII: 添加pc回放
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SndGuAsSpecPlmnSearchReq(
    VOS_UINT32                          ulRcvPid
)
{
    /* 定义调用VOS发送函数的返回值 */
    VOS_UINT32                          ulRet;

    /* 定义原语类型指针 */
    RRMM_PLMN_SEARCH_REQ_STRU          *pstSndMsg;
    RRMM_PLMN_SEARCH_REQ_STRU          *pstBuffMsg;

    /* 申请内存  */
    pstSndMsg = (RRMM_PLMN_SEARCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(RRMM_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pstSndMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsSpecPlmnSearchReq,ERROR:ALLOC MEM ERROR!");
        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0,
                         sizeof(RRMM_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH );

    pstBuffMsg = (RRMM_PLMN_SEARCH_REQ_STRU *) (NAS_UTRANCTRL_GetBufferedSndUtranReqMsgAddr()->aucEntryMsgBuffer);
    pstBuffMsg->MsgHeader.ulReceiverPid   = ulRcvPid;

    PS_MEM_CPY( pstSndMsg, pstBuffMsg, sizeof(RRMM_PLMN_SEARCH_REQ_STRU) );

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstSndMsg);

    NAS_MML_SaveNwSearchReqInfo(pstSndMsg);

    /* 调用VOS发送原语 */
    ulRet = PS_SEND_MSG( WUEPS_PID_MMC, pstSndMsg );

    if( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsSpecPlmnSearchReq,ERROR:SNED MSG FAIL!");
    }

#ifndef __PS_WIN32_RECUR__
    NAS_UTRANCTRL_SetUePcRecurFlg(VOS_TRUE);
#endif
    return;

}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SndGuAsSyscfgReq
 功能描述  : UTRAN控制模块发送GU接入层SYSCFG设置请求
 输入参数  : ulRcvPid:接受PID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年08月8日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年8月16日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII: 添加pc回放
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SndGuAsSyscfgReq(
    VOS_UINT32                          ulRcvPid
)
{
    /* 定义调用VOS发送函数的返回值 */
    VOS_UINT32                          ulRet;

    /* 定义原语类型指针 */
    RRMM_SYS_CFG_REQ_STRU              *pstSndMsg;
    RRMM_SYS_CFG_REQ_STRU              *pstBuffMsg;

    /* 申请内存  */
    pstSndMsg = (RRMM_SYS_CFG_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(RRMM_SYS_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pstSndMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsSyscfgReq,ERROR:ALLOC MEM ERROR!");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0,
                         sizeof(RRMM_SYS_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstBuffMsg = (RRMM_SYS_CFG_REQ_STRU *) (NAS_UTRANCTRL_GetBufferedSndUtranReqMsgAddr()->aucEntryMsgBuffer);
    pstBuffMsg->MsgHeader.ulReceiverPid   = ulRcvPid;

    PS_MEM_CPY(pstSndMsg, pstBuffMsg, sizeof(RRMM_SYS_CFG_REQ_STRU));

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstSndMsg);

    /* 调用VOS发送原语 */
    ulRet = PS_SEND_MSG( WUEPS_PID_MMC, pstSndMsg );

    if( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsSyscfgReq,ERROR:SNED MSG FAIL!");
    }

#ifndef __PS_WIN32_RECUR__
    NAS_UTRANCTRL_SetUePcRecurFlg(VOS_TRUE);
#endif
    return;

}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SndGuAsPowerOffReq
 功能描述  : UTRAN控制模块发送GU接入层关机请求
 输入参数  : ulRcvPid:接受PID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年08月8日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年8月16日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII: 添加pc回放
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SndGuAsPowerOffReq(
    VOS_UINT32                          ulReceiverPid
)
{
    VOS_UINT32                          ulRet;                                  /* 定义调用VOS发送函数的返回值 */
    RRMM_POWER_OFF_REQ_STRU            *pstMsg;                                 /* 定义原语类型指针 */

    /* 申请内存  */
    pstMsg = (RRMM_POWER_OFF_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(RRMM_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        /* 内存申请失败 */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsPowerOffReq:ERROR: Memory Alloc Error for pMsg");
        return ;
    }

    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(RRMM_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH );

    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = ulReceiverPid;
    pstMsg->MsgHeader.ulLength          = sizeof(RRMM_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = RRMM_POWER_OFF_REQ;

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    ulRet = PS_SEND_MSG(WUEPS_PID_MMC, pstMsg);

    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsPowerOffReq:ERROR:PS_SEND_MSG ");
    }

#ifndef __PS_WIN32_RECUR__
    NAS_UTRANCTRL_SetUePcRecurFlg(VOS_TRUE);
#endif

    return ;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SndGuAsStartReq
 功能描述  : UTRAN控制模块发送GU接入层开机机请求
 输入参数  : ulRcvPid:接受PID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年08月8日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年8月16日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII: 添加pc回放
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SndGuAsStartReq(
    VOS_UINT32                          ulRcvPid
)
{
    /* 定义调用VOS发送函数的返回值 */
    VOS_UINT32                          ulRet;

    /* 定义原语类型指针 */
    RRMM_START_REQ_STRU                *pstSndMsg;
    RRMM_START_REQ_STRU                *pstBuffMsg;

    /* 申请内存  */
    pstSndMsg = (RRMM_START_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(RRMM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pstSndMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsStartReq,ERROR:ALLOC MEM ERROR!");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(RRMM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstBuffMsg = (RRMM_START_REQ_STRU *) (NAS_UTRANCTRL_GetBufferedSndUtranReqMsgAddr()->aucEntryMsgBuffer);
    pstBuffMsg->MsgHeader.ulReceiverPid   = ulRcvPid;

    PS_MEM_CPY(pstSndMsg, pstBuffMsg, sizeof(RRMM_START_REQ_STRU));

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstSndMsg);

    /* 调用VOS发送原语 */
    ulRet = PS_SEND_MSG( WUEPS_PID_MMC, pstSndMsg );

    if( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsSyscfgReq,ERROR:SNED MSG FAIL!");
    }

#ifdef NAS_STUB
    {
        VOS_UINT32                      ulRet;                     /* 定义调用VOS发送函数的返回值 */
        RRMM_START_CNF_STRU*            pStartCnfMsg;   /* 定义原语类型指针 */

        /* 申请内存  */
        pStartCnfMsg = (RRMM_START_CNF_STRU *)PS_ALLOC_MSG(ulRcvPid,
                                                   sizeof(RRMM_START_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
        if( VOS_NULL_PTR == pStartCnfMsg )
        {
            return ;
        }

        pStartCnfMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
        pStartCnfMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
        pStartCnfMsg->MsgHeader.ulMsgName           = RRMM_START_CNF;

        pStartCnfMsg->ulResult                      = MMC_START_SUCCESS;

        NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pStartCnfMsg);

        /* 调用VOS发送原语 */
        ulRet = PS_SEND_MSG(ulRcvPid, pStartCnfMsg);

        if(VOS_OK != ulRet)
        {
            return ;
        }
    }

#endif

#ifndef __PS_WIN32_RECUR__
    NAS_UTRANCTRL_SetUePcRecurFlg(VOS_TRUE);
#endif

    return;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_BuildRrMmStartCnfMsg
 功能描述  : 构造开机回复消息
 输入参数  : ulSndPid -- 发送消息PID
              ulRcvPid -- 接收消息PID
              ulResult -- 开机结果消息
 输出参数  : pstMsg  返回构造消息体指针
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2012年08月21日
    作    者   : W00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新增函数

*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_BuildRrMmStartCnfMsg(
    VOS_UINT32                          ulSndPid,
    VOS_UINT32                          ulRcvPid,
    MMC_START_RESULT_ENUM_UINT32        ulResult,
    RRMM_START_CNF_STRU                *pstMsg
)
{
    pstMsg->MsgHeader.ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid               = ulRcvPid;
    pstMsg->MsgHeader.ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid                 = ulSndPid;
    pstMsg->MsgHeader.ulLength                    = sizeof(RRMM_START_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName                   = RRMM_START_CNF;
    pstMsg->ulResult                              = ulResult;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_BuildRrMmPowerOffCnfMsg
 功能描述  : 构造关机回复消息
 输入参数  : ulSndPid -- 发送消息PID
              ulRcvPid -- 接收消息PID
 输出参数  : pstMsg  返回构造消息体指针
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2012年08月21日
    作    者   : W00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新增函数

*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_BuildRrMmPowerOffCnfMsg(
    VOS_UINT32                          ulSndPid,
    VOS_UINT32                          ulRcvPid,
    RRMM_POWER_OFF_CNF_STRU            *pstMsg
)
{
    pstMsg->MsgHeader.ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid               = ulRcvPid;
    pstMsg->MsgHeader.ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid                 = ulSndPid;
    pstMsg->MsgHeader.ulLength                    = sizeof(RRMM_POWER_OFF_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName                   = RRMM_POWER_OFF_CNF;

    /* 初始化保留字段 */
    PS_MEM_SET(pstMsg->aucReserve1, (VOS_UINT8)0X00, sizeof(pstMsg->aucReserve1));

    return;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_BuildRrMmSysCfgCnfMsg
 功能描述  : 构造SYSCFG设置回复消息
 输入参数  : ulSndPid -- 发送消息PID
              ulRcvPid -- 接收消息PID
              ulResult -- 开机结果消息
 输出参数  : pstMsg  返回构造消息体指针
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2012年08月21日
    作    者   : W00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新增函数

*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_BuildRrMmSysCfgCnfMsg(
    VOS_UINT32                          ulSndPid,
    VOS_UINT32                          ulRcvPid,
    RRMM_SYS_CFG_RESULT_ENUM_UINT32     ulResult,
    RRMM_SYS_CFG_CNF_STRU              *pstMsg
)
{
    pstMsg->MsgHeader.ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid               = ulRcvPid;
    pstMsg->MsgHeader.ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid                 = ulSndPid;
    pstMsg->MsgHeader.ulLength                    = sizeof(RRMM_SYS_CFG_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName                   = RRMM_SYS_CFG_CNF;
    pstMsg->ulResult                              = ulResult;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg
 功能描述  : 构造指定搜网回复失败消息
 输入参数  : ulSndPid -- 发送消息PID
              ulRcvPid -- 接收消息PID
 输出参数  : pstMsg  返回构造消息体指针
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2012年08月21日
    作    者   : W00167002
    修改内容   : V7R1C50_GUTL_PhaseII:新增函数
  2.日    期   : 2015年5月26日
    作    者   : s00217060
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0:根据不同的搜网类型构造对应的搜网失败结果
  3.日    期   : 2015年10月12日
    作    者   : s00217060
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0修改

*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(
    VOS_UINT32                          ulSndPid,
    VOS_UINT32                          ulRcvPid,
    RRC_PLMN_SEARCH_TYPE_ENUM_UINT32    enPlmnSearchType,
    RRMM_PLMN_SEARCH_CNF_STRU          *pstMsg
)
{
    pstMsg->MsgHeader.ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid               = ulRcvPid;
    pstMsg->MsgHeader.ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid                 = ulSndPid;
    pstMsg->MsgHeader.ulLength                    = sizeof(RRMM_PLMN_SEARCH_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName                   = RRMM_PLMN_SEARCH_CNF;

    pstMsg->ulSearchRlt = NAS_UTRANCTRL_BuildRrMmPlmnSearchFailRslt(enPlmnSearchType);

    pstMsg->enCoverageType                        = RRC_NAS_COVERAGE_TYPE_NONE;

    /* 将列表搜结果清空  */
    PS_MEM_SET(pstMsg->astSearchRatInfo,
               (VOS_UINT8)0X00,
               sizeof(pstMsg->astSearchRatInfo));

    /* 指定搜网携带的高质量网络个数为0个 */
    pstMsg->PlmnIdList.ulHighPlmnNum              = 0;
    PS_MEM_SET(pstMsg->PlmnIdList.aHighPlmnList,
               (VOS_UINT8)0X00,
               sizeof(pstMsg->PlmnIdList.aHighPlmnList));

    /* 指定搜网携带的低质量网络个数为0个 */
    pstMsg->PlmnIdList.ulLowPlmnNum               = 0;
    PS_MEM_SET(pstMsg->PlmnIdList.aLowPlmnList,
               (VOS_UINT8)0X00,
               sizeof(pstMsg->PlmnIdList.aLowPlmnList));


    return;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_BuildInterUtranCtrlPlmnSelectionAbortFinishIndMsg
 功能描述  : 构造UTRANCTRL搜网被MMC打断完成消息
 输入参数  : ulSndPid -- 发送消息PID
              ulRcvPid -- 接收消息PID
 输出参数  : pstMsg  返回构造消息体指针
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年12月17日
    作    者   : W00167002
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_BuildInterUtranCtrlPlmnSelectionAbortFinishIndMsg(
    NAS_MMCMMC_INTER_UTRAN_CTRL_PLMN_SELECTION_ABORT_FINISH_IND_STRU            *pstMsg
)
{
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength          = sizeof(NAS_MMCMMC_INTER_UTRAN_CTRL_PLMN_SELECTION_ABORT_FINISH_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = MMCMMC_INTER_UTRAN_CTRL_PLMN_SELECTION_ABORT_FINISH_IND;

    /* 将列表搜结果清空  */
    PS_MEM_SET(pstMsg->aucReserved, (VOS_UINT8)0X00, sizeof(pstMsg->aucReserved));
    return;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_BuildRrMmPlmnSearchFailRslt
 功能描述  : 根据搜网类型构造搜网失败结果
 输入参数  : RRC_PLMN_SEARCH_TYPE_ENUM_UINT32    enPlmnSearchType
 输出参数  : 无
 返 回 值  : RRC_PLMN_SEARCH_RLT_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
RRC_PLMN_SEARCH_RLT_ENUM_UINT32 NAS_UTRANCTRL_BuildRrMmPlmnSearchFailRslt(
    RRC_PLMN_SEARCH_TYPE_ENUM_UINT32    enPlmnSearchType
)
{
    RRC_PLMN_SEARCH_RLT_ENUM_UINT32     enPlmnSrchRslt;

    enPlmnSrchRslt  = RRC_PLMN_SEARCH_RLT_SPEC_FAIL;

    switch(enPlmnSearchType)
    {
        case RRC_PLMN_SEARCH_HISTORY:

            enPlmnSrchRslt  = RRC_PLMN_SEARCH_RLT_HISTORY_FAIL;
            break;

        case RRC_PLMN_SEARCH_GET_GEO:

            enPlmnSrchRslt  = RRC_PLMN_SEARCH_RLT_GET_GEO_FAIL;
            break;

        case RRC_PLMN_SEARCH_PREF_BAND:

            enPlmnSrchRslt  = RRC_PLMN_SEARCH_RLT_PREF_BAND_FAIL;
            break;

        case RRC_PLMN_SEARCH_LIST:

            enPlmnSrchRslt  = RRC_PLMN_SEARCH_RLT_LIST_FAIL;
            break;

        default:

            enPlmnSrchRslt  = RRC_PLMN_SEARCH_RLT_SPEC_FAIL;
            break;
    }

    return enPlmnSrchRslt;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_UpdateCurUtranSwitchMode
 功能描述  : 根据NV en_NV_Item_Utran_Mode_Auto_Switch中获取内容来更新当前的UTRAN的切换模式
 输入参数  : pucImsi -- 当前IMSI信息
              ucCardStatus -- 当前SIM卡状态
              pstUtranModeAutoSwitch -- NV en_NV_Item_Utran_Mode_Auto_Switch中的内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月8日
    作    者   : w00167002
    修改内容   : 新建
  2.日    期   : 2012年8月10日
    作    者   : w00176964
    修改内容   : 修改函数名
  3.日    期   : 2012年10月13日
    作    者   : w00167002
    修改内容   : DTS2012101300714:开机读取HOME PLMN时候，在没有读取指示网络号
                 长度文件时6FAD时，默认按照网络号长度为3位，导致在网络号长度
                 为2时出错.
                 第二个参数修改为当前sim卡是否存在。
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_UpdateCurUtranSwitchMode(
    VOS_UINT8                                              *pucImsi,
    VOS_UINT8                                               ucSimPresentStatus,
    NAS_UTRANCTRL_UTRAN_MODE_AUTO_SWITCH_STRU              *pstUtranModeAutoSwitch
)
{
    NAS_MML_PLMN_ID_STRU                                    stHPlmn;

    /* IMSI列表个数为0或当前切换模式为FDD ONLY，则更新当前UTRAN切换模式为FDD ONLY */
    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_FDD_ONLY == pstUtranModeAutoSwitch->ucUtranSwitchMode)
    {
        NAS_UTRANCTRL_SetCurUtranSwitchMode(NAS_UTRANCTRL_UTRAN_SWITCH_MODE_FDD_ONLY);

        return;
    }

    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_TDD_ONLY == pstUtranModeAutoSwitch->ucUtranSwitchMode)
    {
        NAS_UTRANCTRL_SetCurUtranSwitchMode(NAS_UTRANCTRL_UTRAN_SWITCH_MODE_TDD_ONLY);

        return;
    }

    if (0 == pstUtranModeAutoSwitch->ucImsiPlmnListNum)
    {
        NAS_UTRANCTRL_SetCurUtranSwitchMode(NAS_UTRANCTRL_UTRAN_SWITCH_MODE_FDD_ONLY);

        return;
    }

    /* 对于任意SIM都允许进行W和T的切换 */
    if (NAS_UTRANCTRL_SUPPORT_ALL_SIM_AUTO_SWITCH_UTRAN_NUM == pstUtranModeAutoSwitch->ucImsiPlmnListNum )
    {
        NAS_UTRANCTRL_SetCurUtranSwitchMode(NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO);

        return;
    }

    /* 如果当前SIM/USIM卡文件存在 */
    if (VOS_TRUE  == ucSimPresentStatus)
    {

        stHPlmn = NAS_MML_GetImsiHomePlmn(pucImsi);

        /* 当前的IMSI中的PLMN不在NV配置的IMSI PLMN LIST中，则当前为GUL模式,不允许自动切换 */
        if (VOS_TRUE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&stHPlmn,
                                    pstUtranModeAutoSwitch->ucImsiPlmnListNum,
                                    pstUtranModeAutoSwitch->astImsiPlmnList))
        {
            NAS_UTRANCTRL_SetCurUtranSwitchMode(NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO);
        }
        else
        {
            NAS_UTRANCTRL_SetCurUtranSwitchMode(NAS_UTRANCTRL_UTRAN_SWITCH_MODE_FDD_ONLY);
        }
    }
    else
    {
        NAS_UTRANCTRL_SetCurUtranSwitchMode(NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_IsSndOmPcRecurMsgValid
 功能描述  : 判断当前向SDT发送PC 回放消息是否有效
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年08月16日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_IsSndOmPcRecurMsgValid(VOS_VOID)
{
    VOS_UINT32                          ulRslt;

    /* 判断当前向SDT发送PC 回放消息是否有效 */
    ulRslt = NAS_MML_IsSndOmPcRecurMsgValid();

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_IsNeedUtranCtrlFsmProcMsg
 功能描述  : 判断是否需要进UTRANCTRL FSM处理消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要进UTRANCTRL FSM处理消息
             VOS_FALSE:不进UTRANCTRL FSM处理消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月29日
    作    者   : w00167002
    修改内容   : 新建
  2.日    期   : 2014年11月25日
    作    者   : z00161729
    修改内容   : 开机搜网优化项目修改
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_IsNeedUtranCtrlFsmProcMsg(
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulEventType;
    VOS_UINT32                          ulSupportFddFlg;
    VOS_UINT32                          ulSupportTddFlg;

    /* 取得当前消息的事件类型 */
    ulEventType = NAS_UTRANCTRL_GetMsgEventType(pstMsg);

    ulSupportFddFlg = NAS_MML_IsPlatformSupportUtranFdd();
    ulSupportTddFlg = NAS_MML_IsPlatformSupportUtranTdd();

    /* 如果FDD或TDD都支持，则进Utran状态机处理，直接返回VOS_TRUE */
    if (ulSupportFddFlg == ulSupportTddFlg)
    {
        return VOS_TRUE;
    }

    /* 否则在FDD/TDD单模时候，也处理GMM发来的开机回复消息，进行NV的读写 */
    if (ulEventType == NAS_UTRANCTRL_BuildEventType(WUEPS_PID_GMM, MMCGMM_START_CNF))
    {
        return VOS_TRUE;
    }

    if (ulEventType == NAS_UTRANCTRL_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_WAIT_MM_START_CNF))
    {
        return VOS_TRUE;
    }

    if (ulEventType == NAS_UTRANCTRL_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_REQ))
    {
        return VOS_TRUE;
    }

    /* 其他消息在FDD/TDD单模时候，不需要进入UTRANCTRL FSM处理 */
    return VOS_FALSE;
}



/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_IsNeedSndAnotherUtranModeMsg
 功能描述  : 给当前UTRAN模发消息时，需要判断是否需要通知另一UTRAN模
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要通知另一模
             VOS_FALSE:不需要通知另一模
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月21日
    作    者   : w00167002
    修改内容   : 新建
  2.日    期   : 2014年6月13日
    作    者   : w00242748
    修改内容   : DSDS 新特性
  3.日    期   : 2015年9月16日
    作    者   : wx270776
    修改内容   : AS上报优化
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_IsNeedSndAnotherUtranModeMsg(
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                    *pstMsgHeader  = VOS_NULL_PTR;
    RRMM_NAS_INFO_CHANGE_REQ_STRU      *pstNasInfoMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pstMsgHeader  = (MSG_HEADER_STRU *)pstMsg;
    pstNasInfoMsg = (RRMM_NAS_INFO_CHANGE_REQ_STRU *)pstMsg;

    /* 默认不需要通知另一模 */
    ulRslt = VOS_FALSE;

    /* 如果当前不支持UTRAN自动切换，则不需要通知另一模 */
    if ( NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO != NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        return VOS_FALSE;
    }

    switch (pstMsgHeader->ulMsgName)
    {
        /* 对于NAS COMM消息需要通知另一模 */
        case RRMM_NAS_COMM_INFO_CHANGE_REQ:
             ulRslt = VOS_TRUE;
             break;

        /* 对于NAS COMM消息需要通知另一模 */
        case RRMM_AT_MSG_REQ:
             ulRslt = VOS_TRUE;
             break;

        case RRMM_BEGIN_SESSION_NOTIFY:
             ulRslt = VOS_TRUE;
             break;

        case RRMM_END_SESSION_NOTIFY:
             ulRslt = VOS_TRUE;
             break;

        case RRMM_NAS_INFO_CHANGE_REQ:
             /* 当位置区改变时向TD接入层也发送RRMM_NAS_INFO_CHANGE_REQ */
             if (VOS_TRUE == pstNasInfoMsg->aNasInfo[0].bitOpTmsiLai)
             {
                 ulRslt = VOS_TRUE;
             }
             break;

        default:
            break;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_IsNeedSkipSearchUtranFddMode
 功能描述  : 给当前UTRAN模发消息时，需要判断是否需要他跳过搜索W
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要跳过搜网W
             VOS_FALSE:不需要跳过搜网W
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月11日
    作    者   : w00167002
    修改内容   : 新建
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_IsNeedSkipSearchUtranFddMode(
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                    *pstMsgHeader  = VOS_NULL_PTR;
    VOS_UINT32                          ulIsOtherModemPlmnInTdMccList;
    NAS_MML_PLMN_ID_STRU               *pstOtherModemPlmnId = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* 如果当前不支持UTRAN自动切换，则不需要跳过搜W模式 */
    if ( NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO != NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        return VOS_FALSE;
    }

    /* 当前不在FDD模式下，则不需要跳过 */
    if ( NAS_UTRANCTRL_UTRAN_MODE_FDD != NAS_UTRANCTRL_GetCurrUtranMode())
    {
        return VOS_FALSE;
    }

    /* 检测当前是否在W下的搜网信息,如果不是RRMM_PLMN_SEARCH_REQ搜网信息，则不需要跳过W */
    if ( (WUEPS_PID_MMC        != pstMsgHeader->ulSenderPid)
      || (RRMM_PLMN_SEARCH_REQ != pstMsgHeader->ulMsgName)  )
    {
        return VOS_FALSE;
    }

    /* 检测当前副卡是否在国内,如果在国内，则需要跳过W */
    pstOtherModemPlmnId = NAS_MMC_GetOtherModemPlmnId();
    ulIsOtherModemPlmnInTdMccList = NAS_MML_IsMccInDestMccList(pstOtherModemPlmnId->ulMcc,
                                                NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                                NAS_UTRANCTRL_GetSpecTdMccList());

    if ((VOS_TRUE == NAS_MMC_GetUtranSkipWPlmnSearchFlag())
     && (VOS_TRUE == ulIsOtherModemPlmnInTdMccList))
    {
        /* 当前副卡在中国，主卡可以跳过搜W */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_IsNeedSkipSearchUtranTddMode
 功能描述  : 给当前UTRAN模发消息时，需要判断是否需要跳过搜索TDS
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要跳过搜网TDS
             VOS_FALSE:不需要跳过搜网TDS
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月1日
    作    者   : z00161729
    修改内容   : 新建
  2.日    期   : 2015年5月26日
    作    者   : w00167002
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_IsNeedSkipSearchUtranTddMode(
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_REQ_STRU          *pstPlmnSearchReqMsg  = VOS_NULL_PTR;
    VOS_UINT8                           ucRoamPlmnSelectionSortFlg;
    NAS_MML_PLMN_ID_STRU               *pstOtherModemPlmnId = VOS_NULL_PTR;
    VOS_UINT32                          ulIsCurrSearchingPlmnInTdMccList;
    NAS_MML_PLMN_ID_STRU                stPlmnId;
    VOS_UINT32                          ulHongKongMcc;
    VOS_UINT32                          ulIsOtherModemPlmnInTdMccList;

    pstPlmnSearchReqMsg              = (RRMM_PLMN_SEARCH_REQ_STRU *)pstMsg;
    ucRoamPlmnSelectionSortFlg       = NAS_MMC_GetRoamPlmnSelectionSortActiveFlg();
    ulIsCurrSearchingPlmnInTdMccList = VOS_FALSE;
    ulIsOtherModemPlmnInTdMccList    = VOS_FALSE;
    PS_MEM_SET(&stPlmnId, 0, sizeof(stPlmnId));

    /* 香港国家码是454 */
    ulHongKongMcc = NAS_UTRANCTRL_HONGKONG_MCC;

    /* 如果当前不支持UTRAN自动切换，则不需要跳过搜tds模式 */
    if ( NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO != NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        return VOS_FALSE;
    }

    /* 当前不在TDD模式下，则不需要跳过 */
    if ( NAS_UTRANCTRL_UTRAN_MODE_TDD != NAS_UTRANCTRL_GetCurrUtranMode())
    {
        return VOS_FALSE;
    }

    /* 检测当前是否在W下的搜网信息,如果不是RRMM_PLMN_SEARCH_REQ搜网信息，则不需要跳过TDS */
    if ( (WUEPS_PID_MMC        != pstPlmnSearchReqMsg->MsgHeader.ulSenderPid)
      || (RRMM_PLMN_SEARCH_REQ != pstPlmnSearchReqMsg->MsgHeader.ulMsgName)  )
    {
        return VOS_FALSE;
    }

    /* 不是开机搜网不需要跳过tds */
    if (VOS_FALSE == NAS_UTRANCTRL_GetSwithOnPlmnSearchFlag())
    {
        return VOS_FALSE;
    }

    /* 检测当前副卡是否在国内,如果在国内，则不需要跳过TDS */
    pstOtherModemPlmnId = NAS_MMC_GetOtherModemPlmnId();
    ulIsOtherModemPlmnInTdMccList = NAS_MML_IsMccInDestMccList(pstOtherModemPlmnId->ulMcc,
                                                NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                                NAS_UTRANCTRL_GetSpecTdMccList());

    if (VOS_TRUE == ulIsOtherModemPlmnInTdMccList)
    {
        /* 当前副卡在中国，主卡不跳过搜TDS */
        return VOS_FALSE;
    }

    /* anycell搜网不跳过tds */
    if (0 == pstPlmnSearchReqMsg->ulPlmnIdNum)
    {
        return VOS_FALSE;
    }

    /* 如果当前搜索的网络不在TDS国家码里且不是香港网络，则跳过tds搜网 */
    stPlmnId.ulMcc = pstPlmnSearchReqMsg->aPlmnIdList[0].ulMcc;
    stPlmnId.ulMnc = pstPlmnSearchReqMsg->aPlmnIdList[0].ulMnc;


    ulIsCurrSearchingPlmnInTdMccList = NAS_MML_IsMccInDestMccList(stPlmnId.ulMcc,
                                        NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                        NAS_UTRANCTRL_GetSpecTdMccList());

    if ((VOS_FALSE == NAS_MML_ComparePlmnMcc(stPlmnId.ulMcc, ulHongKongMcc))
     && (VOS_FALSE == ulIsCurrSearchingPlmnInTdMccList)
     && (VOS_TRUE == ucRoamPlmnSelectionSortFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}




/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg_SndUtranAsMsgPreProcessMsg
 功能描述  : UTRANCTRL模块对发送消息的保存预处理
 输入参数  : ulSndPid -- 发送PID
             pstMsg  -- 发送消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月21日
    作    者   : w00167002
    修改内容   : 新建
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg_SndUtranAsMsgPreProcessMsg(
    VOS_UINT32                          ulSndPid,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_REQ_STRU          *pstReqMsg           = VOS_NULL_PTR;
    RRMM_SYS_CFG_REQ_STRU              *pstSysCfgReq        = VOS_NULL_PTR;

    pstReqMsg = (RRMM_PLMN_SEARCH_REQ_STRU*)pstMsg;

    /* 模式自动切换时,需要缓存搜网请求消息,便于后续状态机使用 */
    if ( (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO == NAS_UTRANCTRL_GetCurUtranSwitchMode())
      && (RRMM_PLMN_SEARCH_REQ == pstReqMsg->MsgHeader.ulMsgName) )
    {
        NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg(NAS_UTRANCTRL_GetMsgEventType(pstMsg), pstMsg);
    }

    /*  如果当前是向W模发SYSCFG请求，则也需要缓存，便于UTRANCTRL模块的SYSCFG状态机使用 */
    if ( RRMM_SYS_CFG_REQ == pstReqMsg->MsgHeader.ulMsgName )
    {
        pstSysCfgReq = (RRMM_SYS_CFG_REQ_STRU *)pstMsg;

        NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg(NAS_UTRANCTRL_GetMsgEventType(pstMsg), pstMsg);

        NAS_UTRANCTRL_SetPreUtranMode(pstSysCfgReq->enUtranMode);
    }

    /*  如果当前是向W模发开机请求，则也需要缓存，便于UTRANCTRL模块的开机状态机使用 */
    if ( RRMM_START_REQ == pstReqMsg->MsgHeader.ulMsgName )
    {
        NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg(NAS_UTRANCTRL_GetMsgEventType(pstMsg), pstMsg);
    }

    return;

}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SndAnotherUtranModeMsg_SndUtranAsMsgPreProcessMsg
 功能描述  : UTRANCTRL模块对通知另一模消息的预处理
 输入参数  : ulSndPid -- 发送PID
             pstMsg  -- 发送消息
 输出参数  : 无
 返 回 值  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月21日
    作    者   : w00167002
    修改内容   : 新建
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SndAnotherUtranModeMsg_SndUtranAsMsgPreProcessMsg(
    VOS_UINT32                          ulSndPid,
    struct MsgCB                       *pstMsg
)
{
    struct MsgCB                       *pstTempMsg          = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader        = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstTempMsgHeader    = VOS_NULL_PTR;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;
    VOS_UINT32                          ulAnotherUtranModePid;

    enCurrUtranMode       = NAS_UTRANCTRL_GetCurrUtranMode();
    ulAnotherUtranModePid = WUEPS_PID_WRR;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* 当前消息发送后，可能还需要再发送给另一个模，故需申请内存用于保存消息 */
    pstTempMsg = (struct MsgCB *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                              pstMsgHeader->ulLength);

    if ( VOS_NULL_PTR == pstTempMsg )
    {
        /* 打印警告信息---发送消息失败:*/
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndAsMsg:error: MEM ALLOC FAIL!");

        return;
    }

    /* 将当前消息保存到缓存里，已便于通知另一模 */
    PS_MEM_CPY( pstTempMsg,
                pstMsg,
                pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);

    pstTempMsgHeader = (MSG_HEADER_STRU *)pstTempMsg;

    /* 取另一UTRAN模的PID */
    switch (enCurrUtranMode)
    {
        case NAS_UTRANCTRL_UTRAN_MODE_FDD:
            ulAnotherUtranModePid = TPS_PID_RRC;
            break;

        case NAS_UTRANCTRL_UTRAN_MODE_TDD:
            ulAnotherUtranModePid = WUEPS_PID_WRR;
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndAnotherUtranModeMsg_SndUtranAsMsgPreProcessMsg():WARNING: ENTERED");
            break;
    }

    pstTempMsgHeader->ulReceiverPid = ulAnotherUtranModePid;

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstTempMsg);

    /* 给另一模发送消息 */
    if (VOS_OK != PS_SEND_MSG(ulSndPid, pstTempMsg))
    {
        /* 打印警告信息---发送消息失败:*/
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndAnotherUtranModeMsg_SndUtranAsMsgPreProcessMsg:WARNING: SEND utran msg FAIL!");

        return;
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_StartUtranTddModeMsgTimer
 功能描述  : UTRANCTRL模块对通知TDD模时候启动保护定时器
 输入参数  : ulSndPid -- 发送PID
             pstMsg  -- 发送消息
 输出参数  : 无
 返 回 值  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月21日
    作    者   : w00167002
    修改内容   : 新建

  2.日    期   : 2015年6月17日
    作    者   : w00167002
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0:增加HISTORY搜网定时器的启动保护
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_StartUtranTddModeMsgTimer(
    VOS_UINT32                          ulSndPid,
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                    *pstMsgHeader        = VOS_NULL_PTR;
    RRMM_PLMN_SEARCH_REQ_STRU          *pstPlmnSearchReqMsg = VOS_NULL_PTR;

    pstMsgHeader        = (MSG_HEADER_STRU *)pstMsg;
    pstPlmnSearchReqMsg = (RRMM_PLMN_SEARCH_REQ_STRU *)pstMsg;

    switch ( pstMsgHeader->ulMsgName )
    {
        /* 发送开机消息时候，启动开机保护定时器 */
        case RRMM_START_REQ:
            NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_START_CNF, TI_NAS_UTRANCTRL_WAIT_TD_START_CNF_LEN);
            break;

        /* 发送关机消息时候，启动关机保护定时器 */
        case RRMM_POWER_OFF_REQ:
            NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF, TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF_LEN);
            break;

        /* 发送SYSCFG设置消息时候，启动SYSCFG设置保护定时器 */
        case RRMM_SYS_CFG_REQ:
            NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SYSCFG_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SYSCFG_CNF_LEN);
            break;

        /* 发送搜网消息时候，启动搜网保护定时器 */
        case RRMM_PLMN_SEARCH_REQ:

            /* 如果当前是用户指定搜或者HISTORY搜索，则启动保护定时器 */
            if ( (RRC_PLMN_SEARCH_SPEC      == pstPlmnSearchReqMsg->ulSearchType)
              || (RRC_PLMN_SEARCH_HISTORY   == pstPlmnSearchReqMsg->ulSearchType) )
            {
                NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF, TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF_LEN);
            }
            break;

        default:
            break;
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_StartUtranFddModeMsgTimer
 功能描述  : UTRANCTRL模块对通知FDD模时候启动保护定时器
 输入参数  : ulSndPid -- 发送PID
              pstMsg  -- 发送消息
 输出参数  : 无
 返 回 值  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月21日
    作    者   : w00167002
    修改内容   : 新建
  2.日    期   : 2015年6月17日
    作    者   : w00167002
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0:增加HISTORY搜网定时器的启动保护
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_StartUtranFddModeMsgTimer(
    VOS_UINT32                          ulSndPid,
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                    *pstMsgHeader        = VOS_NULL_PTR;
    RRMM_PLMN_SEARCH_REQ_STRU          *pstPlmnSearchReqMsg = VOS_NULL_PTR;

    pstMsgHeader        = (MSG_HEADER_STRU *)pstMsg;
    pstPlmnSearchReqMsg = (RRMM_PLMN_SEARCH_REQ_STRU *)pstMsg;

    switch ( pstMsgHeader->ulMsgName )
    {
        /* 发送开机消息时候，启动开机保护定时器 */
        case RRMM_START_REQ:
            NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_START_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_START_CNF_LEN);
            break;

        /* 发送关机消息时候，启动关机保护定时器 */
        case RRMM_POWER_OFF_REQ:
            NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF_LEN);
            break;

        /* 发送SYSCFG设置消息时候，启动SYSCFG设置保护定时器 */
        case RRMM_SYS_CFG_REQ:
            NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SYSCFG_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SYSCFG_CNF_LEN);
            break;

        /* 发送搜网消息时候，启动搜网保护定时器 */
        case RRMM_PLMN_SEARCH_REQ:

            /* 如果当前是用户指定搜或者HISTORY搜索，则启动保护定时器 */
            if ( (RRC_PLMN_SEARCH_SPEC      == pstPlmnSearchReqMsg->ulSearchType)
              || (RRC_PLMN_SEARCH_HISTORY   == pstPlmnSearchReqMsg->ulSearchType) )
            {
                NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF_LEN);
            }
            break;

        default:
            break;
    }

    return;

}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_StopUtranTddModeMsgTimer
 功能描述  : UTRANCTRL模块对通知TDD模时候停止保护定时器
 输入参数  : ulSndPid -- 发送PID
             pstMsg  -- 发送消息
 输出参数  : 无
 返 回 值  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月21日
    作    者   : w00167002
    修改内容   : 新建
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_StopUtranTddModeMsgTimer(
    VOS_UINT32                          ulMsgName
)
{
    switch ( ulMsgName )
    {
        /* 发送停止搜网消息的时候，停止当前的TDD模的搜网保护定时器 */
        case RRMM_PLMN_SEARCH_STOP_REQ:

            if (NAS_MMC_TIMER_STATUS_RUNING == NAS_UTRANCTRL_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF))
            {
                NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF);
            }
            break;

        default:

            break;
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_StopUtranFddModeMsgTimer
 功能描述  : UTRANCTRL模块对通知FDD模时候停止保护定时器
 输入参数  : ulSndPid -- 发送PID
             pstMsg  -- 发送消息
 输出参数  : 无
 返 回 值  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月21日
    作    者   : w00167002
    修改内容   : 新建
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_StopUtranFddModeMsgTimer(
    VOS_UINT32                          ulMsgName
)
{
    switch ( ulMsgName )
    {
        /* 发送停止搜网消息时候，停止当前的FDD搜网保护定时器 */
        case RRMM_PLMN_SEARCH_STOP_REQ:
            if (NAS_MMC_TIMER_STATUS_RUNING == NAS_UTRANCTRL_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF))
            {
                NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);
            }

            break;

        default:
            break;
    }

    return;

}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_StartUtranModeMsgTimer_SndUtranAsMsgPreProcessMsg
 功能描述  : UTRANCTRL模块对通知UTRAN模时候启动保护定时器
 输入参数  : ulSndPid -- 发送PID
             pstMsg  -- 发送消息
 输出参数  : 无
 返 回 值  : VOS_OK: 消息处理成功
              VOS_ERR: 消息处理异常
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月21日
    作    者   : w00167002
    修改内容   : 新建
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_StartUtranModeMsgTimer_SndUtranAsMsgPreProcessMsg(
    VOS_UINT32                          ulSndPid,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;

    enCurrUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    switch ( enCurrUtranMode )
    {
        /* 发送消息时候，启动开机FDD保护定时器 */
        case NAS_UTRANCTRL_UTRAN_MODE_FDD:
             NAS_UTRANCTRL_StartUtranFddModeMsgTimer(ulSndPid, pstMsg);
             break;

        /* 发送消息时候，启动TDD保护定时器 */
        case NAS_UTRANCTRL_UTRAN_MODE_TDD:
             NAS_UTRANCTRL_StartUtranTddModeMsgTimer(ulSndPid, pstMsg);
             break;

        default:
            break;
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_StartUtranModeMsgTimer_SndUtranAsMsgPreProcessMsg
 功能描述  : UTRANCTRL模块对通知UTRAN模时候启动保护定时器
 输入参数  : ulSndPid -- 发送PID
             pstMsg  -- 发送消息
 输出参数  : 无
 返 回 值  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月21日
    作    者   : w00167002
    修改内容   : 新建
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_StopUtranModeMsgTimer_SndUtranAsMsgPreProcessMsg(
    VOS_UINT32                          ulSndPid,
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                    *pstMsgHeader        = VOS_NULL_PTR;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    enCurrUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    switch ( enCurrUtranMode )
    {
        /* 发送消息时候，停止开机FDD保护定时器 */
        case NAS_UTRANCTRL_UTRAN_MODE_FDD:
             NAS_UTRANCTRL_StopUtranFddModeMsgTimer(pstMsgHeader->ulMsgName);
             break;

        /* 发送消息时候，停止开启的TDD保护定时器 */
        case NAS_UTRANCTRL_UTRAN_MODE_TDD:
             NAS_UTRANCTRL_StopUtranTddModeMsgTimer(pstMsgHeader->ulMsgName);
             break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_StopUtranModeMsgTimer_SndUtranAsMsgPreProcessMsg():WARNING:UTRAN MODE INVALID");
            break;
    }

    return;

}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SndUtranAsMsgPreProcessMsg
 功能描述  : UTRANCTRL模块对发送消息的预处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月21日
    作    者   : w00167002
    修改内容   : 新建
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SndUtranAsMsgPreProcessMsg(
    VOS_UINT32                          ulSndPid,
    struct MsgCB                       *pstMsg
)
{
    /* UTRANCTRL模块对发送消息的保存预处理 */
    NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg_SndUtranAsMsgPreProcessMsg(ulSndPid,
                                                                   pstMsg);

    /* 判断当前消息是否需要发送给另一个模 */
    if ( VOS_TRUE == NAS_UTRANCTRL_IsNeedSndAnotherUtranModeMsg(pstMsg) )
    {
        /* 当前消息发送后，可能还需要再发送给另一个模，故需申请内存用于发送消息 */
        NAS_UTRANCTRL_SndAnotherUtranModeMsg_SndUtranAsMsgPreProcessMsg(ulSndPid,
                                                                   pstMsg);

    }

    /* 由于MMC状态机模块在发送消息时所启动的定时器实际上是保护W模和TD两个模
       的，当前模并未受到保护。如当前为GTL模式，在等TD模的消息超时，此时MMC
       还在等待W模的回复，故在发送消息前，对当前所发送消息进行定时器保护 */
    NAS_UTRANCTRL_StartUtranModeMsgTimer_SndUtranAsMsgPreProcessMsg(ulSndPid,
                                                                   pstMsg);


    /* 停止MMC状态机所保护的消息的定时器。如:MMC模块给WAS发送搜网消息的时候，
       收到了用户的打断请求，此时MMC发送停止搜网,UTRANCTRL模块需要停止当前保护
       的搜网定时器 */
    NAS_UTRANCTRL_StopUtranModeMsgTimer_SndUtranAsMsgPreProcessMsg(ulSndPid,
                                                                   pstMsg);

    return ;

}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_IsSpecPlmnMccInGuRrcPlmnIdList
 功能描述  : 根据GU RRC的PLMN ID列表判断是否指定mcc的网络
 输入参数  : ulSpecPlmnMcc   - 指定mcc的网络
             pstGuPlmnIdList - GU RRC的PLMN ID列表
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月15日
    作    者   : z00161729
    修改内容   : 开机搜网优化项目修改

*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_IsSpecPlmnMccInGuRrcPlmnIdList(
    VOS_UINT32                          ulSpecPlmnMcc,
    RRC_PLMN_ID_LIST_STRU              *pstGuPlmnIdList
)
{
    VOS_UINT32                          ulMccNum;
    VOS_UINT32                         *pulRrcMccList = VOS_NULL_PTR;

    pulRrcMccList = (VOS_UINT32 *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                        sizeof(VOS_UINT32) * (RRC_MAX_HIGH_PLMN_NUM + RRC_MAX_LOW_PLMN_NUM));


    if ( VOS_NULL_PTR == pulRrcMccList )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_IsSpecPlmnMccInDestPlmnIdList ERROR: MEM ALLOC FAIL");

        return VOS_FALSE;
    }

    /* 从RRC的PLMN ID列表中获取MCC列表 */
    NAS_MMC_GetMccListInRrcPlmnIdList(&ulMccNum, pulRrcMccList, pstGuPlmnIdList);

    /* 判断MCC是否在TD MCC列表中 */
    if (VOS_TRUE == NAS_MML_IsMccInDestMccList(ulSpecPlmnMcc, ulMccNum, pulRrcMccList))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pulRrcMccList);
        return VOS_TRUE;
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pulRrcMccList);
    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_UpdateSearchedSpecTdMccFLg
 功能描述  : 根据GU RRC的PLMN ID列表更新搜索过的指定TD MCC标记
 输入参数  : ulTdMccNum ---- 指定TD国家码个数
             pulTdMccList -- 指定TD国家码列表
             pstGuPlmnIdList --GU RRC的PLMN ID列表
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月23日
    作    者   : w00176964
    修改内容   : 新建

  2.日    期   : 2012年9月25日
    作    者   : w00167002
    修改内容   : DTS2012092405740:开机W下搜网失败，携带23002，46001网络，此时，
                  没有更新当前为中国网络标记。
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_UpdateSearchedSpecTdMccFLg(
    VOS_UINT32                          ulTdMccNum,
    VOS_UINT32                         *pulTdMccList,
    RRC_PLMN_ID_LIST_STRU              *pstGuPlmnIdList
)
{
    VOS_UINT32                          ulMccNum;
    VOS_UINT32                         *pulRrcMccList;
    VOS_UINT32                          i;

    pulRrcMccList = (VOS_UINT32 *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                        sizeof(VOS_UINT32) * (RRC_MAX_HIGH_PLMN_NUM + RRC_MAX_LOW_PLMN_NUM));


    if ( VOS_NULL_PTR == pulRrcMccList )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_UpdateSearchedSpecTdMccFLg ERROR: MEM ALLOC FAIL");

        return;
    }

    /* 从RRC的PLMN ID列表中获取MCC列表 */
    NAS_MMC_GetMccListInRrcPlmnIdList(&ulMccNum, pulRrcMccList, pstGuPlmnIdList);

    /* 遍历GU RRC的MCC列表 */
    for (i = 0; i < ulMccNum; i++)
    {

        /* 判断MCC是否在TD MCC列表中 */
        if (VOS_TRUE == NAS_MML_IsMccInDestMccList(pulRrcMccList[i], ulTdMccNum, pulTdMccList))
        {
             /* 根据搜网列表更新中国网络标记 */
            NAS_UTRANCTRL_SetSearchedSpecTdMccFlg(VOS_TRUE);

            break;
        }
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pulRrcMccList);
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_IsNeedProcGuPlmnSearchCnf
 功能描述  : UTRANCTRL是否需要处理搜网结果
 输入参数  : RRMM_PLMN_SEARCH_CNF_STRU          *pstPlmnSrchCnf
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2015年10月12日
    作    者   : s00217060
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0修改:增加对pref band搜的处理
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_IsNeedProcGuPlmnSearchCnf(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    RRMM_PLMN_SEARCH_CNF_STRU          *pstPlmnSrchCnf
)
{
    /* 非自动切换模式,消息直接透传到MMC状态机处理 */
    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO != NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        return VOS_FALSE;
    }

    /* 如果是LIST搜网的结果回复则直接透传到MMC状态机处理 */
    if (VOS_TRUE == NAS_MML_IsPlmnListSrchRslt(enRat, pstPlmnSrchCnf->ulSearchRlt))
    {
        return VOS_FALSE;
    }

    /* 自动切换模式下
       1. 搜网失败NORF
       2. 快速指定搜网或指定搜网 成功
       3. history搜成功
       直接透传快速指定搜网回复到MMC状态机处理 */
    if ((RRC_PLMN_SEARCH_SPEC_FAST          == NAS_UTRANCTRL_GetBufferedPlmnSearchReqType())
     || (RRC_PLMN_SEARCH_RLT_SPEC           == pstPlmnSrchCnf->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_SPEC_NO_RF     == pstPlmnSrchCnf->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_SUCC   == pstPlmnSrchCnf->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF  == pstPlmnSrchCnf->ulSearchRlt))
    {
        return VOS_FALSE;
    }

    /* 自动切换模式下如果是GET_GEO结果直接透传到MMC状态机处理 */
    if (VOS_TRUE == NAS_MML_IsGetGeoPlmnSrchRslt(enRat, pstPlmnSrchCnf->ulSearchRlt))
    {
        return VOS_FALSE;
    }

    /* 自动切换模式下如果是pref band结果直接透传到MMC状态机处理 */
    if (VOS_TRUE == NAS_MML_IsPrefBandPlmnSrchRslt(enRat, pstPlmnSrchCnf->ulSearchRlt))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_IsNeedProcLmmPlmnSearchCnf
 功能描述  : UTRANCTRL是否需要处理搜网结果
 输入参数  : LMM_MMC_PLMN_SRCH_CNF_STRU          *pstPlmnSrchCnf
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2015年10月13日
    作    者   : s00217060
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0修改：增加pref band的处理

*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_IsNeedProcLmmPlmnSearchCnf(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstPlmnSrchCnf
)
{
    /* 非自动切换模式,消息直接透传到MMC状态机处理 */
    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO != NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        return VOS_FALSE;
    }

    /* 如果是LIST搜网的结果回复则直接透传到MMC状态机处理 */
    if (VOS_TRUE == NAS_MML_IsPlmnListSrchRslt(enRat, pstPlmnSrchCnf->enRlst))
    {
        return VOS_FALSE;
    }

    /* 自动切换模式下如果是搜网失败NORF/快速指定搜网或指定搜网成功/history搜成功直接透传快速指定搜网回复到MMC状态机处理 */
    if ((MMC_LMM_PLMN_SRCH_RLT_SPEC_SUCC        == pstPlmnSrchCnf->enRlst)
     || (MMC_LMM_PLMN_SRCH_RLT_SPEC_NO_RF       == pstPlmnSrchCnf->enRlst)
     || (MMC_LMM_PLMN_SRCH_RLT_HISTORY_SUCC     == pstPlmnSrchCnf->enRlst)
     || (MMC_LMM_PLMN_SRCH_RLT_HISTORY_NO_RF    == pstPlmnSrchCnf->enRlst))
    {
        return VOS_FALSE;
    }

    /* 自动切换模式下如果是GET_GEO结果直接透传到MMC状态机处理 */
    if (VOS_TRUE == NAS_MML_IsGetGeoPlmnSrchRslt(enRat, pstPlmnSrchCnf->enRlst))
    {
        return VOS_FALSE;
    }

    /* 自动切换模式下如果是pref band结果直接透传到MMC状态机处理 */
    if (VOS_TRUE == NAS_MML_IsPrefBandPlmnSrchRslt(enRat, pstPlmnSrchCnf->enRlst))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_ProcPlmnSearchReq_GetGeo
 功能描述  : UTRANCTRL对GET_GEO类型的搜网的处理
 输入参数  : VOS_UINT32                          ulSndPid
             RRMM_PLMN_SEARCH_REQ_STRU          *pstPlmnSrchReq
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月27日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_ProcPlmnSearchReq_GetGeo(
    VOS_UINT32                          ulSndPid,
    RRMM_PLMN_SEARCH_REQ_STRU          *pstPlmnSrchReq
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstGeoPlmnSrchFail      = VOS_NULL_PTR;
    VOS_UINT32                          ulSupportFddFlg;

    ulSupportFddFlg = NAS_MML_IsPlatformSupportUtranFdd();

    /* Receive PID为GAS时，直接给GAS发送get_geo类型的搜网 */
    if (WUEPS_PID_WRR != pstPlmnSrchReq->MsgHeader.ulReceiverPid)
    {
        PS_SEND_MSG(ulSndPid, pstPlmnSrchReq);

        return;
    }

    /* Receive PID为WRR时: */

    /* 平台支持FDD，并且utran switch mode不是TDD only时，直接给WRR发送get_geo类型的搜网 */
    if ((NAS_UTRANCTRL_UTRAN_SWITCH_MODE_TDD_ONLY != NAS_UTRANCTRL_GetCurUtranSwitchMode())
     && (VOS_TRUE   == ulSupportFddFlg))
    {
#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
        /* GEO搜索是为了获取当前位置信息，收到搜网回复结果，不管成功还是失败，均会进行关机操作
           所以该流程只要保证在搜索W时，将W加载到内存中即可 */
        if (VOS_TRUE == NAS_DYNLOAD_GetEnableDynloadTWFlg())
        {
            (VOS_VOID)NAS_DYNLOAD_LoadAS(NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W, VOS_RATMODE_WCDMA);
        }
#endif

        PS_SEND_MSG(ulSndPid, pstPlmnSrchReq);

        return;
    }

    /* 平台不支持FDD或utran switch mode为TDD only时，构造geo_geo失败的消息发送给MMC */
    pstGeoPlmnSrchFail  = (RRMM_PLMN_SEARCH_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                        WUEPS_PID_MMC,
                                                        sizeof(RRMM_PLMN_SEARCH_CNF_STRU));

    /* 内存申请失败,直接返回 */
    if ( VOS_NULL_PTR == pstGeoPlmnSrchFail )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_ProcPlmnSearchReq_GetGeo():ERROR:Alloc Msg fail");

        PS_FREE_MSG(ulSndPid, pstPlmnSrchReq);

        return;
    }

    /* 构造搜网回复失败消息*/
    NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                WUEPS_PID_MMC,
                                                pstPlmnSrchReq->ulSearchType,
                                                pstGeoPlmnSrchFail);

    PS_SEND_MSG(ulSndPid, pstGeoPlmnSrchFail);

    PS_FREE_MSG(ulSndPid, pstPlmnSrchReq);

    return;

}

#endif  /* end of #if (FEATURE_ON == FEATURE_UE_MODE_TDS) */

/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

