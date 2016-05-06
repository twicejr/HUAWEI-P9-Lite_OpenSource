/******************************************************************************

                  版权所有 (C), 2001-2013, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MtcRfLcdIntrusion.c
  版 本 号   : 初稿
  作    者   : j00174725
  生成日期   : 2014年03月04日
  最近修改   :
  功能描述   : 处理RF&LCD干扰规避相关功能
  函数列表   :
  修改历史   :
  1.日    期   : 2014年03月04日
    作    者   : j00174725
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MtcDebug.h"
#include "MtcComm.h"
#include "MtaMtcInterface.h"
#include "MtcRfLcdIntrusion.h"
#include "MtcCalcFreq.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*lint -e767 修改人: j00174725; */
#define    THIS_FILE_ID        PS_FILE_ID_MTC_RF_LCD_INTRUSION_C
/*lint +e767 修改人: j00174725; */

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : MTC_SndMtaMipiClkInfoInd
 功能描述  : 通知MTA模块上报^MIPICLK命令
 输入参数  : usMipiClk    -- MipiClk值
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月10日
    作    者   : j00174725
    修改内容   : RF&LCD干扰控制项目新增
*****************************************************************************/
VOS_VOID MTC_SndMtaMipiClkInfoInd(VOS_UINT16  usMipiClk)
{
    VOS_UINT16                          ulLenth;
    MTC_MTA_MIPICLK_INFO_IND_STRU      *pstMipiClkInd = VOS_NULL_PTR;

    ulLenth = sizeof(MTC_MTA_MIPICLK_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 分配消息空间 */
    pstMipiClkInd = (MTC_MTA_MIPICLK_INFO_IND_STRU*)PS_ALLOC_MSG(UEPS_PID_MTC, ulLenth);

    if (VOS_NULL_PTR == pstMipiClkInd)
    {
        MTC_ERROR_LOG("MTC_SndMtaMipiClkInfoInd: Alloc msg fail!");
        MTC_DEBUG_RF_LCD_ALLOC_MSG_ERR();
        return;
    }

    /* 清消息空间 */
    PS_MEM_SET((VOS_UINT8*)pstMipiClkInd + VOS_MSG_HEAD_LENGTH, 0x0, ulLenth);

    /* 填充消息 */
    pstMipiClkInd->stMsgHeader.ulReceiverPid = MTC_GetMipiClkRcvPid();          /* 从上下文件获取接收Pid */
    pstMipiClkInd->stMsgHeader.ulMsgName     = ID_MTC_MTA_MIPICLK_INFO_IND;
    pstMipiClkInd->usMipiCLk                 = usMipiClk;

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstMipiClkInd))
    {
        MTC_DEBUG_RF_LCD_SND_MIPICLK_IND_ERR();
        MTC_ERROR_LOG("MTC_SndMtaMipiClkInfoInd: Snd Msg err. Rec Pid ");
        return;
    }

    MTC_DEBUG_RF_LCD_SND_MIPICLK_IND_OK();

    return;
}

/*****************************************************************************
 函 数 名  : MTC_GetInterBitMap
 功能描述  : 筛选MIPICLK BitMap
 输入参数  : ulFreq    -- 频率值
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月06日
    作    者   : Y00213812
    修改内容   : RF&LCD干扰规避项目新增
*****************************************************************************/
VOS_UINT16 MTC_GetInterBitMap(
    VOS_UINT32                          ulFreq
)
{
    VOS_UINT32                          ulMIpiClkIndex;
    VOS_UINT32                          ulFreqIndex;
    VOS_UINT16                          usWidth;
    VOS_UINT16                          usInterBitMap;
    MTC_RF_LCD_INTRUSION_CTX_STRU      *pstRfLcdIntrCtx;

    pstRfLcdIntrCtx                     = MTC_GetRfLcdIntrusionCtxAddr();
    usWidth                             = pstRfLcdIntrCtx->usFreqWidth / 2;
    usInterBitMap                       = 0;

    for (ulMIpiClkIndex = 0; ulMIpiClkIndex < pstRfLcdIntrCtx->ucAvailFreqListNum; ulMIpiClkIndex++)
    {
        for (ulFreqIndex = 0; ulFreqIndex < pstRfLcdIntrCtx->astRfLcdFreqList[ulMIpiClkIndex].ulAvailNum; ulFreqIndex++)
        {
            if ((ulFreq >= pstRfLcdIntrCtx->astRfLcdFreqList[ulMIpiClkIndex].aulFreq[ulFreqIndex] - usWidth)
             && (ulFreq <= pstRfLcdIntrCtx->astRfLcdFreqList[ulMIpiClkIndex].aulFreq[ulFreqIndex] + usWidth))
            {
                usInterBitMap |= (VOS_UINT16)MTC_SET_BIT(ulMIpiClkIndex);
                break;
            }
        }
    }

    return usInterBitMap;
}

/*****************************************************************************
 函 数 名  : MTC_VerdictModemBitMapPri
 功能描述  : 调整服务小区的优先级
 输入参数  : usMipiClk    -- MipiClk值
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月06日
    作    者   : Y00213812
    修改内容   : RF&LCD干扰规避项目新增
*****************************************************************************/
VOS_VOID MTC_VerdictModemBitMapPri(
    MTC_MODEM_MIPI_CLK_PRI_STRU        *pstMomdemPri
)
{
    MTC_MODEM_MIPICLK_BITMAP_STRU      *pstModem0 = VOS_NULL_PTR;
    MTC_MODEM_MIPICLK_BITMAP_STRU      *pstModem1 = VOS_NULL_PTR;

    pstModem0 = MTC_GetRfCellInfoAddr(MODEM_ID_0);
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    pstModem1 = MTC_GetRfCellInfoAddr(MODEM_ID_1);
#else
    pstModem1 = pstModem0;
#endif

    /* Modem0已经有CS连接，或者modem0和modem1都没有cs连接 */
    if ((PS_TRUE == pstModem0->enCsExistFlag)
     || (PS_FALSE == pstModem1->enCsExistFlag))
    {
        pstMomdemPri->usPriScellMipiClkBitMap   = pstModem0->usScellBitMap;
        pstMomdemPri->usPriHoppingMipiClkBitMap = pstModem0->usHoppingBitMap;
        pstMomdemPri->usPriNcellMipiClkBitMap   = pstModem0->usNcellBitMap;
        pstMomdemPri->usSecScellMipiClkBitMap   = pstModem1->usScellBitMap;
        pstMomdemPri->usSecHoppingMipiClkBitMap = pstModem1->usHoppingBitMap;
        pstMomdemPri->usSecNcellMipiClkBitMap   = pstModem1->usNcellBitMap;

        return;
    }

    /* Modem1已经有CS连接 */
    pstMomdemPri->usPriScellMipiClkBitMap   = pstModem1->usScellBitMap;
    pstMomdemPri->usPriHoppingMipiClkBitMap = pstModem1->usHoppingBitMap;
    pstMomdemPri->usPriNcellMipiClkBitMap   = pstModem1->usNcellBitMap;
    pstMomdemPri->usSecScellMipiClkBitMap   = pstModem0->usScellBitMap;
    pstMomdemPri->usSecHoppingMipiClkBitMap = pstModem0->usHoppingBitMap;
    pstMomdemPri->usSecNcellMipiClkBitMap   = pstModem0->usNcellBitMap;

    return;
}

/*****************************************************************************
 函 数 名  : MTC_ProcScellClkBitMap
 功能描述  : 筛选LCD MIPICLK BitMap
 输入参数  : usMipiClk    -- MipiClk值
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月06日
    作    者   : Y00213812
    修改内容   : RF&LCD干扰规避项目新增
*****************************************************************************/
VOS_UINT16 MTC_ProcScellClkBitMap(
    VOS_UINT32                          ulScellFreq
)
{
    VOS_UINT16                          usScellClkBitMap;
    VOS_UINT16                          usInterBitMap;

    usScellClkBitMap = MTC_GetMipiClkBitMap();

    usInterBitMap = MTC_GetInterBitMap(ulScellFreq);

    usScellClkBitMap &= ~usInterBitMap;

    return usScellClkBitMap;
}

/*****************************************************************************
 函 数 名  : MTC_ProcHoppingClkBitMap
 功能描述  : 筛选LCD MIPICLK BitMap
 输入参数  : usMipiClk    -- MipiClk值
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月06日
    作    者   : Y00213812
    修改内容   : RF&LCD干扰规避项目新增
*****************************************************************************/
VOS_UINT16 MTC_ProcHoppingClkBitMap(
    MTC_RF_FREQ_LIST_STRU              *pstFreq
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT16                          usInterBitMap;
    VOS_UINT16                          usHoppingllClk;

    usHoppingllClk = MTC_GetMipiClkBitMap();

    for (ulIndex = 0; ulIndex < pstFreq->ulFreqNum; ulIndex ++)
    {
        usInterBitMap = MTC_GetInterBitMap(pstFreq->ausFreq[ulIndex]);

        if ((usHoppingllClk & (~usInterBitMap)) == 0)
        {
            return usHoppingllClk;
        }

        usHoppingllClk &= ~usInterBitMap;
    }

    return usHoppingllClk;
}

/*****************************************************************************
 函 数 名  : MTC_ProcNcellClkBitMap
 功能描述  : 筛选LCD MIPICLK BitMap
 输入参数  : usMipiClk    -- MipiClk值
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月06日
    作    者   : Y00213812
    修改内容   : RF&LCD干扰规避项目新增
*****************************************************************************/
VOS_UINT16 MTC_ProcNcellClkBitMap(
    MTC_RF_FREQ_LIST_STRU              *pstFreq
)
{
    VOS_UINT16                          usNcellClk;
    VOS_UINT16                          usInterBitMap;
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucNum;
    VOS_UINT16                          usMin;
    MTC_RF_LCD_INTRUSION_CTX_STRU      *pstMtcRfLcdCtx;
    VOS_UINT16                          ausCount[MTC_RF_LCD_MIPICLK_MAX_NUM];

    usNcellClk      = MTC_GetMipiClkBitMap();
    pstMtcRfLcdCtx  = MTC_GetRfLcdIntrusionCtxAddr();
    usMin           = 0xFFFF;
    PS_MEM_SET(ausCount, 0, sizeof(ausCount));

    /* 计算频率影响位图 */
    for (ulIndex = 0; ulIndex < pstFreq->ulFreqNum; ulIndex++)
    {
        usInterBitMap = MTC_GetInterBitMap(pstFreq->ausFreq[ulIndex]);

        for (ucNum = 0; ucNum < pstMtcRfLcdCtx->ucAvailFreqListNum; ucNum++)
        {
            ausCount[ucNum] += ((usInterBitMap >> ucNum) & 0x0001);
        }
    }

    /* 统计各LCD MipiClk影响权重 */
    for (ucNum = 0; ucNum < pstMtcRfLcdCtx->ucAvailFreqListNum; ucNum++)
    {
        if (ausCount[ucNum] < usMin)
        {
            usMin = ausCount[ucNum];
        }
    }

    /* 筛选最佳位图 */
    for (ucNum = 0; ucNum < pstMtcRfLcdCtx->ucAvailFreqListNum; ucNum++)
    {
        if (ausCount[ucNum] > usMin)
        {
            usNcellClk &= ~((VOS_UINT16)MTC_SET_BIT(ucNum));
        }
    }

    return usNcellClk;
}

/*****************************************************************************
 函 数 名  : MTC_ProcLcdMipiClkBitMap
 功能描述  : 筛选LCD MIPICLK BitMap
 输入参数  : usMipiClk    -- MipiClk值
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月06日
    作    者   : Y00213812
    修改内容   : RF&LCD干扰规避项目新增
*****************************************************************************/
VOS_UINT16 MTC_ProcLcdMipiClkBitMap(
    MTC_MODEM_MIPI_CLK_PRI_STRU        *pstMomdemPri
)
{
    /* 优先级顺序
       usPriScellMipiClkBitMap;
       usPriHoppingMipiClkBitMap;
       usPriNcellMipiClkBitMap;
       usSecScellMipiClkBitMap;
       usSecHoppingMipiClkBitMap;
       usSecNcellMipiClkBitMap;
    */

    VOS_UINT16                          usMipiClk;

    usMipiClk = pstMomdemPri->usPriScellMipiClkBitMap;

    if ((pstMomdemPri->usSecScellMipiClkBitMap & usMipiClk) == 0)
    {
        return usMipiClk;
    }
    usMipiClk &= pstMomdemPri->usSecScellMipiClkBitMap;

    if ((pstMomdemPri->usPriHoppingMipiClkBitMap & usMipiClk) == 0)
    {
        return usMipiClk;
    }
    usMipiClk &= pstMomdemPri->usPriHoppingMipiClkBitMap;

    if ((pstMomdemPri->usSecHoppingMipiClkBitMap & usMipiClk) == 0)
    {
        return usMipiClk;
    }
    usMipiClk &= pstMomdemPri->usSecHoppingMipiClkBitMap;

    if ((pstMomdemPri->usPriNcellMipiClkBitMap & usMipiClk) == 0)
    {
        return usMipiClk;
    }
    usMipiClk &= pstMomdemPri->usPriNcellMipiClkBitMap;

    if ((pstMomdemPri->usSecNcellMipiClkBitMap & usMipiClk) == 0)
    {
        return usMipiClk;
    }
    usMipiClk &= pstMomdemPri->usSecNcellMipiClkBitMap;


    return usMipiClk;
}

/*****************************************************************************
 函 数 名  : MTC_RcvRrcUsingFreqInd
 功能描述  : 接收到使用频点的处理
 输入参数  : usMipiClk    -- MipiClk值
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月06日
    作    者   : Y00213812
    修改内容   : RF&LCD干扰规避项目新增
  2.日    期   : 2015年10月05日
    作    者   : j00174725
    修改内容   : DTS2015102706654
*****************************************************************************/
VOS_VOID MTC_RcvRrcUsingFreqInd(VOS_VOID *pMsg)
{
    RRC_MTC_USING_FREQ_IND_STRU        *pstFreqInfo     = VOS_NULL_PTR;
    MTC_MODEM_MIPICLK_BITMAP_STRU      *pstScellInfo    = VOS_NULL_PTR;
    MTC_MSG_BUF_STRU                   *pstBufAddr = VOS_NULL_PTR;
    MTC_MODEM_FREQ_LIST_STRU            stModemFreq;
    MTC_MODEM_MIPI_CLK_PRI_STRU         stMomdemPri;
    VOS_UINT16                          usMipiClk;
    MODEM_ID_ENUM_UINT16                enModemId;
    MTC_CFG_ENUM_UINT8                  enNotchCfg;

    pstFreqInfo     = (RRC_MTC_USING_FREQ_IND_STRU *)pMsg;

    enNotchCfg      = MTC_GetNotchCfg();
    enModemId       = VOS_GetModemIDFromPid(pstFreqInfo->stMsgHeader.ulSenderPid);
    pstBufAddr      = MTC_GetBufAddr(enModemId);
    if ( (MTC_CFG_ENABLE == enNotchCfg)
      && (MODEM_ID_0 == enModemId) )                                            /* 只有modem0上才支持TL */
    {
        if (PS_FALSE == MTC_IsNeedBufModem0Msg(pstFreqInfo->stMsgHeader.ulSenderPid))
        {
            /* 清除上下文中保存的临区TL Band信息 */
            MTC_ResetNCellBandInfo(MODEM_ID_0);

            /* 根据当前接入模式上报服务小区和邻区信息，计算出Band信息 */
            MTC_GetTLBandInfoFromUsingFreq(pstFreqInfo);

            /* 执行Notch裁决 */
            MTC_ProcNotchStrategy();

            pstBufAddr->stBufUsingFreqInfoMsg.enExitBufMsgFlag = PS_FALSE;
        }
        else
        {
            PS_MEM_SET(&pstBufAddr->stBufUsingFreqInfoMsg, 0x0, sizeof(MTC_USING_FREQ_MSG_BUF_STRU));
            PS_MEM_CPY(&pstBufAddr->stBufUsingFreqInfoMsg.stUsingFreqInfoMsg, pstFreqInfo, sizeof(RRC_MTC_USING_FREQ_IND_STRU));
            pstBufAddr->stBufUsingFreqInfoMsg.enExitBufMsgFlag = PS_TRUE;

            /* 勾取可维可测 */
            MTC_DEBUG_TraceNotchInfo();

            /* 如果需要缓存，则不再往下走，等到模式正确后再走这个函数 */
            return;
        }
    }

    if (MTC_CFG_DISABLE == MTC_GetRfLcdIntrusionCfg())
    {
        return;
    }

    PS_MEM_SET(&stModemFreq, 0, sizeof(MTC_MODEM_FREQ_LIST_STRU));
    PS_MEM_SET(&stMomdemPri, 0, sizeof(MTC_MODEM_MIPI_CLK_PRI_STRU));

    /* 默认更新modem的服务小区信息 */
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    if (I1_UEPS_PID_GAS == pstFreqInfo->stMsgHeader.ulSenderPid)
    {
        pstScellInfo = MTC_GetRfCellInfoAddr(MODEM_ID_1);
    }
    else
#endif
    {
        pstScellInfo = MTC_GetRfCellInfoAddr(MODEM_ID_0);
    }

    /* 更新服务信息 */
    pstScellInfo->enCsExistFlag = pstFreqInfo->enCsExistFlag;
    pstScellInfo->enPsExistFlag = pstFreqInfo->enPsExistFlag;

    /* 记录可维可测信息 */
    MTC_DEBUG_SAVE_RF_USING_CS_PS_INFO(pstScellInfo->enCsExistFlag,
                                       pstScellInfo->enPsExistFlag);

    /* 获取服务连接类型和频点转换为频率 */
    MTC_CalcRfDlFreq(pstFreqInfo, &stModemFreq);

    /* 筛选服务小区位图 */
    pstScellInfo->usScellBitMap         = MTC_ProcScellClkBitMap(stModemFreq.ulScellFreq);

    /* 筛选跳频位图 */
    pstScellInfo->usHoppingBitMap       = MTC_ProcHoppingClkBitMap(&stModemFreq.stGsmHoppingFreq);

    /* 筛选邻区位图 */
    pstScellInfo->usNcellBitMap         = MTC_ProcNcellClkBitMap(&stModemFreq.stNcellFreq);

    /* 根据各modem当前的业务调整优先级 */
    MTC_VerdictModemBitMapPri(&stMomdemPri);

    /* 记录可维可测信息 */
    MTC_DEBUG_COPY_MODEM_MIPICLK(stMomdemPri);

    /* 筛选最佳位图 */
    usMipiClk = MTC_ProcLcdMipiClkBitMap(&stMomdemPri);

    /* 上报LCD MipiClk位图给MTA */
    MTC_SndMtaMipiClkInfoInd(usMipiClk);

    MTC_DEBUG_TraceRfUsingFreqListInfo();

    return ;
}

/*lint +e958*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of MtcRfLcdIntrusion.c */


