

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MtcDebug.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_MTC_DEBUG_C
/*lint +e767*/

/*****************************************************************************
  2 外部函数声明
*****************************************************************************/


/******************************************************************************
   3 私有定义
******************************************************************************/


/******************************************************************************
   4 全局变量定义
******************************************************************************/
MTC_DEBUG_INFO_STRU                     g_stMtcDebugInfo;

MTC_DEBUG_RF_USING_FREQ_LIST_STRU       g_stRfUsingDebugInfo;

/******************************************************************************
   5 函数实现
******************************************************************************/

VOS_VOID MTC_DebugHelp(VOS_VOID)
{
    (VOS_VOID)vos_printf("Intrusion Info      : MTC_DEBUG_ShowIntrusionInfo\r\n");

    (VOS_VOID)vos_printf("Ps Transfer Info    : MTC_DEGUG_ShowPsTransferInfo\r\n");

    (VOS_VOID)vos_printf("Modem Info          : MTC_DEBUG_ShowModemInfo\r\n");
    return;
}


VOS_VOID MTC_DEBUG_ShowModemInfo(VOS_VOID)
{
    MTC_MODEM_INFO_STRU                *pstModemInfo = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstModemInfo = MTC_GetModemCtxAddr(enModemId);

        (VOS_VOID)vos_printf("Modem[%d] RatCap       : 0x%02X \r\n", enModemId, pstModemInfo->ucRatCap);
        (VOS_VOID)vos_printf("Modem[%d] Power state  : %d \r\n", enModemId, pstModemInfo->enPowerState);
        (VOS_VOID)vos_printf("Modem[%d] Rat Mode     : %d \r\n", enModemId, pstModemInfo->enRatMode);
        (VOS_VOID)vos_printf("Modem[%d] Call Srv     : %d \r\n", enModemId, pstModemInfo->stSrvInfo.ucCallSrvExistFlg);
        (VOS_VOID)vos_printf("Modem[%d] Sms Srv      : %d \r\n", enModemId, pstModemInfo->stSrvInfo.ucSmsSrvExistFlg);
        (VOS_VOID)vos_printf("Modem[%d] Ss Srv       : %d \r\n", enModemId, pstModemInfo->stSrvInfo.ucSsSrvExistFlg);
        (VOS_VOID)vos_printf("Modem[%d] Band info[0] : 0x%08X \r\n", enModemId, pstModemInfo->stCurBandInfo.aulBandInfo[0]);
        (VOS_VOID)vos_printf("Modem[%d] Band info[1] : 0x%08X \r\n", enModemId, pstModemInfo->stCurBandInfo.aulBandInfo[1]);
    }

    return;
}



VOS_VOID MTC_DEBUG_ShowIntrusionInfo(VOS_VOID)
{
    (VOS_VOID)vos_printf("\r\nShow Power Num:\r\n");
    (VOS_VOID)vos_printf("Rcv Modem0 Power On Num     : %d\r\n", g_stMtcDebugInfo.stIntrusionDebugInfo.ausRcvPowerOnNum[MODEM_ID_0]);
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    (VOS_VOID)vos_printf("Rcv Modem1 Power On Num     : %d\r\n", g_stMtcDebugInfo.stIntrusionDebugInfo.ausRcvPowerOnNum[MODEM_ID_1]);
#endif
    (VOS_VOID)vos_printf("Rcv Modem0 Power Off Num    : %d\r\n", g_stMtcDebugInfo.stIntrusionDebugInfo.ausRcvPowerOffNum[MODEM_ID_0]);
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    (VOS_VOID)vos_printf("Rcv Modem1 Power Off Num    : %d\r\n", g_stMtcDebugInfo.stIntrusionDebugInfo.ausRcvPowerOffNum[MODEM_ID_1]);
#endif

    (VOS_VOID)vos_printf("\r\nShow Rcv CsSrv Info Num :\r\n");
    (VOS_VOID)vos_printf("Rcv Modem0 Cs Srv Info Num  : %d\r\n", g_stMtcDebugInfo.stIntrusionDebugInfo.ausRcvCsSrvNum[MODEM_ID_0]);
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    (VOS_VOID)vos_printf("Rcv Modem1 Cs Srv Info Num  : %d\r\n", g_stMtcDebugInfo.stIntrusionDebugInfo.ausRcvCsSrvNum[MODEM_ID_1]);
#endif

    (VOS_VOID)vos_printf("\r\nShow Send Action Num :\r\n");
    (VOS_VOID)vos_printf("Snd Action to Lte Rrc Num   : %d\r\n", g_stMtcDebugInfo.stIntrusionDebugInfo.usSndAction2LTERrcReqNum);
    (VOS_VOID)vos_printf("Snd Action to Tds Rrc Num   : %d\r\n", g_stMtcDebugInfo.stIntrusionDebugInfo.usSndAction2TDSRrcReqNum);
    (VOS_VOID)vos_printf("Snd Action to Gas Rrc Num   : %d\r\n", g_stMtcDebugInfo.stIntrusionDebugInfo.usSndAction2GASReqNum);

    (VOS_VOID)vos_printf("\r\nShow Rcv Action Cnf Num :\r\n");
    (VOS_VOID)vos_printf("Rcv Lte Rrc Action Cnf Num  : %d\r\n", g_stMtcDebugInfo.stIntrusionDebugInfo.usRcvLTERrcActionCnfNum);
    (VOS_VOID)vos_printf("Rcv Tds Rrc Action Cnf Num  : %d\r\n", g_stMtcDebugInfo.stIntrusionDebugInfo.usRcvTDSRrcActionCnfNum);
    (VOS_VOID)vos_printf("Rcv Gas Rrc Action Cnf Num  : %d\r\n", g_stMtcDebugInfo.stIntrusionDebugInfo.usRcvGASActionCnfNum);

    (VOS_VOID)vos_printf("\r\nShow Rcv Band Set Cnf Num :\r\n");
    (VOS_VOID)vos_printf("Snd Gas Band Set Req Num    : %d\r\n", g_stMtcDebugInfo.stIntrusionDebugInfo.usSndGasSetBandReqNum);
    (VOS_VOID)vos_printf("Snd Lte Band Set Req Num    : %d\r\n", g_stMtcDebugInfo.stIntrusionDebugInfo.usSndLteSetBandReqNum);
    (VOS_VOID)vos_printf("Snd Tds Band Set Req Num    : %d\r\n", g_stMtcDebugInfo.stIntrusionDebugInfo.usSndTdsSetBandReqNum);

    (VOS_VOID)vos_printf("\r\nShow Rcv Set Band Cnf Num :\r\n");
    (VOS_VOID)vos_printf("Rcv Gas Band Set Cnf Num    : %d\r\n", g_stMtcDebugInfo.stIntrusionDebugInfo.usRcvGASBandSetCnfNum);
    (VOS_VOID)vos_printf("Rcv Lte Band Set Cnf Num    : %d\r\n", g_stMtcDebugInfo.stIntrusionDebugInfo.usRcvLTEBandSetCnfNum);
    (VOS_VOID)vos_printf("Rcv Tds Band Set Cnf Num    : %d\r\n", g_stMtcDebugInfo.stIntrusionDebugInfo.usRcvTDSBandSetCnfNum);

    return;
}


VOS_VOID MTC_DEGUG_ShowPsTransferInfo(VOS_VOID)
{
    MTC_PS_TRANSFER_DEBUG_INFO         *pstPsTransferDebugInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucLoop;

    pstPsTransferDebugInfo = MTC_GetPsTransferDebugCtxAddr();

    (VOS_VOID)vos_printf("\r\nRcv Tds Area Lost Ind Num   : %d\r\n", pstPsTransferDebugInfo->usRcvTDSAreaLostIndNum);
    (VOS_VOID)vos_printf("Rcv Lte Area Lost Ind Num   : %d\r\n", pstPsTransferDebugInfo->usRcvLTEAreaLostIndNum);

    (VOS_VOID)vos_printf("\r\nSend Ps Transfer Num        :\r\n");

    for (ucLoop = 0; ucLoop < MTC_PS_TRANSFER_CAUSE_BUTT; ucLoop++)
    {
        (VOS_VOID)vos_printf("Ps Transfer Cause[%d]       : %d\r\n", pstPsTransferDebugInfo->ausSndPsTransferIndNum[ucLoop]);
    }

    return;
}


VOS_VOID MTC_InitDebugCtx(VOS_VOID)
{
    /* 初始化MTC调试信息全局变量 */
    PS_MEM_SET(&g_stMtcDebugInfo, 0, sizeof(g_stMtcDebugInfo));

    return;
}


MTC_INTRUSION_DEBUG_INFO* MTC_GetIntrusionDebugCtxAddr(VOS_VOID)
{
    return &g_stMtcDebugInfo.stIntrusionDebugInfo;
}


MTC_PS_TRANSFER_DEBUG_INFO* MTC_GetPsTransferDebugCtxAddr(VOS_VOID)
{
    return &g_stMtcDebugInfo.stPsTransferDebugInfo;
}


VOS_VOID MTC_DEBUG_IntrusionRcvSetBandCnf(VOS_UINT32 ulPid)
{
    MTC_INTRUSION_DEBUG_INFO           *pstIntrusionDebugInfo;
    pstIntrusionDebugInfo = MTC_GetIntrusionDebugCtxAddr();

    if (TPS_PID_RRC == ulPid)
    {
        pstIntrusionDebugInfo->usRcvTDSBandSetCnfNum++;
    }
    else if (PS_PID_ERRC == ulPid)
    {
        pstIntrusionDebugInfo->usRcvLTEBandSetCnfNum++;
    }
    else if (I1_UEPS_PID_GAS == ulPid)
    {
        pstIntrusionDebugInfo->usRcvGASBandSetCnfNum++;
    }
    else
    {
        MTC_ERROR1_LOG("MTC_DEBUG_IntrusionRcvSetBandCnf: Err SenderPid ", ulPid);
    }

    return;

}


VOS_VOID MTC_DEBUG_IntrusionRcvActionCnf(VOS_UINT32 ulPid)
{
    MTC_INTRUSION_DEBUG_INFO           *pstIntrusionDebugInfo;
    pstIntrusionDebugInfo = MTC_GetIntrusionDebugCtxAddr();

    if (TPS_PID_RRC == ulPid)
    {
        pstIntrusionDebugInfo->usRcvTDSRrcActionCnfNum++;
    }
    else if (PS_PID_ERRC == ulPid)
    {
        pstIntrusionDebugInfo->usRcvLTERrcActionCnfNum++;
    }
    else if (I1_UEPS_PID_GAS == ulPid)
    {
        pstIntrusionDebugInfo->usRcvGASActionCnfNum++;
    }
    else
    {
        MTC_ERROR1_LOG("MTC_DEBUG_IntrusionRcvActionCnf: Err SenderPid ", ulPid);
    }

    return;

}


VOS_VOID MTC_DEBUG_IntrusionSendActionReq(VOS_UINT32 ulPid)
{
    MTC_INTRUSION_DEBUG_INFO           *pstIntrusionDebugInfo;
    pstIntrusionDebugInfo = MTC_GetIntrusionDebugCtxAddr();

    if (TPS_PID_RRC == ulPid)
    {
        pstIntrusionDebugInfo->usSndAction2TDSRrcReqNum++;
    }
    else if (PS_PID_ERRC == ulPid)
    {
        pstIntrusionDebugInfo->usSndAction2LTERrcReqNum++;
    }
    else if (I1_UEPS_PID_GAS == ulPid)
    {
        pstIntrusionDebugInfo->usSndAction2GASReqNum++;
    }
    else
    {
        MTC_ERROR1_LOG("MTC_DEBUG_IntrusionSendActionReq: Err SenderPid ", ulPid);
    }

    return;

}


VOS_VOID MTC_DEBUG_IntrusionSendSetBandReq(VOS_UINT32 ulPid)
{
    MTC_INTRUSION_DEBUG_INFO           *pstIntrusionDebugInfo;
    pstIntrusionDebugInfo = MTC_GetIntrusionDebugCtxAddr();

    if (TPS_PID_RRC == ulPid)
    {
        pstIntrusionDebugInfo->usSndTdsSetBandReqNum++;
    }
    else if (PS_PID_ERRC == ulPid)
    {
        pstIntrusionDebugInfo->usSndLteSetBandReqNum++;
    }
    else if (I1_UEPS_PID_GAS == ulPid)
    {
        pstIntrusionDebugInfo->usSndGasSetBandReqNum++;
    }
    else
    {
        MTC_ERROR1_LOG("MTC_DEBUG_IntrusionSendSetBandReq: Err SenderPid ", ulPid);
    }

    return;

}


VOS_VOID MTC_DEBUG_RcvPowerStateInd(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enPowerState
)
{
    if (MTC_MODEM_POWER_ON == enPowerState)
    {
        MTC_GetIntrusionDebugCtxAddr()->ausRcvPowerOnNum[enModemId]++;
    }
    else
    {
        MTC_GetIntrusionDebugCtxAddr()->ausRcvPowerOffNum[enModemId]++;
    }

    return;
}


VOS_VOID MTC_DEBUG_RcvCsSrvInfoInd(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    MTC_GetIntrusionDebugCtxAddr()->ausRcvCsSrvNum[enModemId]++;

    return;
}


VOS_VOID MTC_DEBUG_RcvRrcAreaLostInd(
    VOS_UINT32                          ulSenderPid
)
{
    MTC_PS_TRANSFER_DEBUG_INFO         *pstPsTransferDebugInfo = VOS_NULL_PTR;

    pstPsTransferDebugInfo = MTC_GetPsTransferDebugCtxAddr();

    if (TPS_PID_RRC == ulSenderPid)
    {
        pstPsTransferDebugInfo->usRcvTDSAreaLostIndNum++;
    }
    else
    {
        pstPsTransferDebugInfo->usRcvLTEAreaLostIndNum++;
    }

    return;
}


VOS_VOID MTC_DEBUG_RcvRrcAreaAvaliableInd(VOS_VOID)
{
    MTC_PS_TRANSFER_DEBUG_INFO         *pstPsTransferDebugInfo = VOS_NULL_PTR;

    pstPsTransferDebugInfo = MTC_GetPsTransferDebugCtxAddr();

    pstPsTransferDebugInfo->usRcvAreaAvaliableIndNum++;

    return;
}


VOS_VOID MTC_DEBUG_SndPsTransferInd(
    MTC_PS_TRANSFER_CAUSE_ENUM_UINT8    enPsTransferCause
)
{
    MTC_GetPsTransferDebugCtxAddr()->ausSndPsTransferIndNum[enPsTransferCause]++;

    return;
}


MTC_DEBUG_RF_LCD_INFO_STRU* MTC_DEBUG_GetRfLcdDebugAddr(VOS_VOID)
{
    return &g_stMtcDebugInfo.stRfLcdDebugInfo;
}


#if 1

VOS_VOID MTC_DEBUG_ShowBand(VOS_VOID)
{
    (VOS_VOID)vos_printf("\r\nBAND_NONE   : %d\r\n", MTC_DEBUG_BAND_NONE);
    (VOS_VOID)vos_printf("BAND_1      : %d\r\n", MTC_DEBUG_BAND_1);
    (VOS_VOID)vos_printf("BAND_3      : %d\r\n", MTC_DEBUG_BAND_3);
    (VOS_VOID)vos_printf("BAND_8      : %d\r\n", MTC_DEBUG_BAND_8);
    (VOS_VOID)vos_printf("BAND_3_8    : %d\r\n", MTC_DEBUG_BAND_3_8);
    (VOS_VOID)vos_printf("BAND_31     : %d\r\n", MTC_DEBUG_BAND_31);
    (VOS_VOID)vos_printf("BAND_31_8   : %d\r\n", MTC_DEBUG_BAND_31_8);
    (VOS_VOID)vos_printf("BAND_32     : %d\r\n", MTC_DEBUG_BAND_32);
    (VOS_VOID)vos_printf("BAND_32_8   : %d\r\n", MTC_DEBUG_BAND_32_8);
    (VOS_VOID)vos_printf("BAND_39     : %d\r\n", MTC_DEBUG_BAND_39);

    return;
}


VOS_VOID MTC_DEBUG_FillBandInfo(
    RRC_MTC_INTRUSION_BAND_INFO_IND_STRU   *pstBandInfo,
    MTC_DEBUG_BAND_ENUM_UINT8               enBand
)
{
    switch (enBand)
    {
        case MTC_DEBUG_BAND_1:
            pstBandInfo->stCurBandInfo.aulBandInfo[0] = 1;
            break;
        case MTC_DEBUG_BAND_31:
            pstBandInfo->stCurBandInfo.aulBandInfo[0] = 1 << MTC_BAND_B31_BIT;
            break;
        case MTC_DEBUG_BAND_32:
            pstBandInfo->stCurBandInfo.aulBandInfo[0] = (VOS_UINT32)1 << MTC_BAND_B32_BIT;
            break;
        case MTC_DEBUG_BAND_8:
            pstBandInfo->stCurBandInfo.aulBandInfo[0] = 1 << MTC_BAND_B8_BIT;
            break;
        case MTC_DEBUG_BAND_3:
            pstBandInfo->stCurBandInfo.aulBandInfo[0] = 1 << MTC_BAND_B31_BIT;
            pstBandInfo->stCurBandInfo.aulBandInfo[0] |= (VOS_UINT32)1 << MTC_BAND_B32_BIT;
            break;
        case MTC_DEBUG_BAND_3_8:
            pstBandInfo->stCurBandInfo.aulBandInfo[0] = 1 << MTC_BAND_B31_BIT;
            pstBandInfo->stCurBandInfo.aulBandInfo[0] |= (VOS_UINT32)1 << MTC_BAND_B32_BIT;
            pstBandInfo->stCurBandInfo.aulBandInfo[0] |= 1 << MTC_BAND_B8_BIT;
            break;
        case MTC_DEBUG_BAND_31_8:
            pstBandInfo->stCurBandInfo.aulBandInfo[0] = 1 << MTC_BAND_B31_BIT;
            pstBandInfo->stCurBandInfo.aulBandInfo[0] |= 1 << MTC_BAND_B8_BIT;
            break;
        case MTC_DEBUG_BAND_32_8:
            pstBandInfo->stCurBandInfo.aulBandInfo[0] = (VOS_UINT32)1 << MTC_BAND_B32_BIT;
            pstBandInfo->stCurBandInfo.aulBandInfo[0] |= 1 << MTC_BAND_B8_BIT;
            break;
        case MTC_DEBUG_BAND_39:
            pstBandInfo->stCurBandInfo.aulBandInfo[1] = 1 << MTC_BAND_B39_BIT;
            break;
        default:

            break;
    }

    pstBandInfo->stSerCellBandInfo.aulBandInfo[0] = pstBandInfo->stCurBandInfo.aulBandInfo[0];
    pstBandInfo->stSerCellBandInfo.aulBandInfo[1] = pstBandInfo->stCurBandInfo.aulBandInfo[1];

    return;
}


VOS_VOID MTC_DEBUG_SendBandInfoInd(
    VOS_UINT8                               ucAs,
    MTC_DEBUG_BAND_ENUM_UINT8               enBand
)
{
    VOS_UINT16                              ulLenth;
    RRC_MTC_INTRUSION_BAND_INFO_IND_STRU   *pstBandInfo = VOS_NULL_PTR;
    VOS_UINT32                              ulSendPid;

    /* 分配消息空间 */
    ulLenth         = sizeof(RRC_MTC_INTRUSION_BAND_INFO_IND_STRU);
    pstBandInfo     = (RRC_MTC_INTRUSION_BAND_INFO_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                UEPS_PID_MTC,
                                                                ulLenth);

    if (VOS_NULL_PTR == pstBandInfo)
    {
        MTC_ERROR_LOG("MTC_DEBUG_SendBandInfoInd: Alloc Msg Fail!");
        return;
    }

    /* 填充消息 */
    pstBandInfo->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstBandInfo->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstBandInfo->stMsgHeader.ulReceiverPid     = UEPS_PID_MTC;
    pstBandInfo->stMsgHeader.ulMsgName         = ID_RRC_MTC_INTRUSION_BAND_INFO_IND;

    PS_MEM_SET(&pstBandInfo->stCurBandInfo, 0, sizeof(RRC_MTC_MS_BAND_INFO_STRU));

    if (1 == ucAs)
    {
        ulSendPid = TPS_PID_RRC;
    }
    else if(2 == ucAs)
    {
        ulSendPid = PS_PID_ERRC;
    }
    else
    {
        ulSendPid = I1_UEPS_PID_GAS;
    }
    pstBandInfo->stMsgHeader.ulSenderPid       = ulSendPid;

    MTC_DEBUG_FillBandInfo(pstBandInfo, enBand);

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(ulSendPid, pstBandInfo))
    {
        MTC_ERROR1_LOG("MTC_DEBUG_SendBandInfoInd: Snd Msg Err. SendPid: ", ulSendPid);
        return;
    }

    return;
}


VOS_VOID MTC_DEBUG_SendTBandSetReq(
    VOS_UINT8                               ucBand
)
{
    RRC_MTC_MS_BAND_INFO_STRU           stForbiddenBandInfo;

    PS_MEM_SET(&stForbiddenBandInfo, 0, sizeof(stForbiddenBandInfo));

    if (1 == ucBand)
    {
        stForbiddenBandInfo.aulBandInfo[1] |= 1 << MTC_BAND_B39_BIT;
    }
    else if (2 == ucBand)
    {
        stForbiddenBandInfo.aulBandInfo[1] |= 1 << MTC_BAND_B40_BIT;
    }
    else
    {

    }

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    /* 判断当前接入技术是否支持TDS */
    if (VOS_TRUE == MTC_IsSupportRatType(MODEM_ID_0, MTC_RATMODE_TDS))
    {
        MTC_SndRrcIntrusionBandSetReq(TPS_PID_RRC, &stForbiddenBandInfo);
    }
#endif

    return;
}


VOS_VOID MTC_DEBUG_SendLBandSetReq(
    VOS_UINT8                               ucBand
)
{
    RRC_MTC_MS_BAND_INFO_STRU           stForbiddenBandInfo;

    PS_MEM_SET(&stForbiddenBandInfo, 0, sizeof(stForbiddenBandInfo));

    if (1 == ucBand)
    {
        stForbiddenBandInfo.aulBandInfo[1] |= 1 << MTC_BAND_B39_BIT;
    }
    else if (2 == ucBand)
    {
        stForbiddenBandInfo.aulBandInfo[1] |= 1 << MTC_BAND_B40_BIT;
    }
    else
    {

    }

#if (FEATURE_ON == FEATURE_LTE)
    /* 判断当前接入技术是否支持LTE */
    if (VOS_TRUE == MTC_IsSupportRatType(MODEM_ID_0, MTC_RATMODE_LTE))
    {
        MTC_SndRrcIntrusionBandSetReq(PS_PID_ERRC, &stForbiddenBandInfo);
    }
#endif

    return;
}


VOS_VOID MTC_DEBUG_SendTLBandSetReq(
    VOS_UINT8                               ucBand
)
{
    if (MTC_RATMODE_LTE == MTC_GetModemRatMode(MODEM_ID_0))
    {
        MTC_DEBUG_SendLBandSetReq(ucBand);

        MTC_DEBUG_SendTBandSetReq(ucBand);
    }
    else
    {
        MTC_DEBUG_SendTBandSetReq(ucBand);

        MTC_DEBUG_SendLBandSetReq(ucBand);
    }
    return;
}


VOS_VOID MTC_DEBUG_SendOtherRatInfoInd(VOS_VOID)
{
    VOS_UINT16                              ulLenth;
    VOS_UINT8                              *pMsg     = VOS_NULL_PTR;
    VOS_UINT8                               aucMsg[] =
    {
        0x00, 0x00, 0x00, 0x00, 0xDC, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xDB, 0x00, 0x00, 0x00,
        0x36, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x10,
        0x2E, 0x00, 0x00, 0x00, 0x18, 0x09, 0x01, 0x00,
        0x16, 0x0D, 0x01, 0x0E, 0x80, 0xFF, 0xFF, 0x35,
        0x05, 0x01, 0x2F, 0x00, 0x46, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00
    };

    /* 分配消息空间 */
    ulLenth = sizeof(aucMsg);
    pMsg    = (VOS_UINT8 *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_CBPCA, ulLenth);

    if (VOS_NULL_PTR == pMsg)
    {
        MTC_ERROR_LOG("MTC_DEBUG_SendOtherRatInfoInd: Alloc Msg Fail!");
        return;
    }

    /* 填充消息 */
    PS_MEM_CPY(pMsg, aucMsg, ulLenth);

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_CBPCA, pMsg))
    {
        MTC_ERROR1_LOG("MTC_DEBUG_SendOtherRatInfoInd: Snd Msg Err. SendPid: ", WUEPS_PID_CBPCA);
        return;
    }

    return;
}

#endif


VOS_VOID MTC_DEBUG_TraceEvent(VOS_VOID *pMsg)
{

    DIAG_TraceReport(pMsg);

    return;
}


/*lint -e813*/ /* auto variable 'stMtcCtxDebugInfo' in function 'MTC_DEBUG_TraceCtxInfo(void)' has size '1960') */
VOS_VOID MTC_DEBUG_TraceCtxInfo(VOS_VOID)
{
    MTC_CONTEXT_STRU                   *pstMtcCtx = VOS_NULL_PTR;
    MTC_CONTEXT_DEBUG_STRU              stMtcCtxDebugInfo;

    /* 获取上下文 */
    pstMtcCtx = MTC_GetCtxAddr();

    /* 填写消息头 */
    MTC_DEBUG_CFG_MSG_HDR(&stMtcCtxDebugInfo,
                            UEPS_PID_MTC,
                            UEPS_PID_MTC,
                            sizeof(MTC_CONTEXT_DEBUG_STRU) - VOS_MSG_HEAD_LENGTH);

    /*  填写Debug 消息ID */
    stMtcCtxDebugInfo.enMsgType = ID_DEBUG_MTC_CTX_INFO;

    /* 填写消息内容 */
    PS_MEM_CPY(&(stMtcCtxDebugInfo.stMtcCtx), pstMtcCtx, sizeof(MTC_CONTEXT_STRU));

    /* 发送消息 */
    MTC_DEBUG_TraceEvent(&stMtcCtxDebugInfo);

    return;
}
/*lint +e813*/



VOS_VOID MTC_DEBUG_InitRfUsingFreqListInfo(VOS_VOID)
{
    /* 初始化 */
    PS_MEM_SET(&g_stRfUsingDebugInfo, 0x0, sizeof(g_stRfUsingDebugInfo));
}



VOS_VOID MTC_DEBUG_TraceRfUsingFreqListInfo(VOS_VOID)
{
    /*  填写Debug 消息ID */
    g_stRfUsingDebugInfo.stMsgHeader.ulSenderCpuId      = VOS_LOCAL_CPUID;
    g_stRfUsingDebugInfo.stMsgHeader.ulSenderPid        = UEPS_PID_MTC;
    g_stRfUsingDebugInfo.stMsgHeader.ulReceiverCpuId    = VOS_LOCAL_CPUID;
    g_stRfUsingDebugInfo.stMsgHeader.ulReceiverPid      = UEPS_PID_MTC;
    g_stRfUsingDebugInfo.stMsgHeader.ulLength           = sizeof(MTC_DEBUG_RF_USING_FREQ_LIST_STRU) - VOS_MSG_HEAD_LENGTH;
    g_stRfUsingDebugInfo.stMsgHeader.ulMsgName          = ID_DEBUG_MTC_RF_USING_FREQ_LIST_INFO;

    /* 发送消息 */
    MTC_DEBUG_TraceEvent(&g_stRfUsingDebugInfo);

    return;
}



VOS_VOID MTC_DEBUG_TraceAllModemConnStateInfo(VOS_VOID)
{
    MTC_DEBUG_ALL_MODEM_STATE_INFO      stAllModemState;
    MODEM_ID_ENUM_UINT16                enModemID;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCsSrvStatus;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enPsSrvStatus;

    enPsSrvStatus                       = TAF_MTC_SRV_CONN_STATE_BUTT;

    /* 初始化 */
    PS_MEM_SET(&stAllModemState, 0x0, sizeof(MTC_DEBUG_ALL_MODEM_STATE_INFO));

    /*  填写消息头 */
    MTC_DEBUG_CFG_MSG_HDR(&stAllModemState.stMsgHeader,
                            UEPS_PID_MTC, UEPS_PID_MTC,
                            sizeof(MTC_DEBUG_ALL_MODEM_STATE_INFO) - VOS_MSG_HEAD_LENGTH);

    stAllModemState.stMsgHeader.ulMsgName = ID_DEBUG_MTC_ALL_MODEM_STATE_INFO;

    /* 各Modem状态信息 */
    for (enModemID = 0; enModemID < MODEM_ID_BUTT; enModemID++)
    {
        stAllModemState.stModemStateInfo[enModemID].enPowerState        = MTC_GetModemPowerState(enModemID);

        stAllModemState.stModemStateInfo[enModemID].ulCsSessionValue    = MTC_GetCsSessionInfo(enModemID);
        stAllModemState.stModemStateInfo[enModemID].ulPsSessionValue    = MTC_GetPsSessionInfo(enModemID);
        stAllModemState.stModemStateInfo[enModemID].ucPsConnInfo        = MTC_GetPsTypeInfo(enModemID);
        enPsSrvStatus            = MTC_GetPsSrvState(enModemID);
        if ((PS_TRUE            == MTC_IsPsSessionInfoExit(enModemID))
         || (TAF_MTC_SRV_EXIST  == enPsSrvStatus))
        {
            stAllModemState.stModemStateInfo[enModemID].enIsPsSrvConnExist = TAF_MTC_SRV_EXIST;
        }
        else
        {
            stAllModemState.stModemStateInfo[enModemID].enIsPsSrvConnExist = TAF_MTC_SRV_NO_EXIST;
        }

        stAllModemState.stModemStateInfo[enModemID].ucCsConnInfo        = MTC_GetCsTypeInfo(enModemID);
        enCsSrvStatus                                                   = MTC_GetCsSrvState(enModemID);
        stAllModemState.stModemStateInfo[enModemID].enModemRatCfg       = MTC_ConvertToRcmRatCfg(MTC_GetUsimStateInfo(enModemID),
                                                                                                 MTC_GetRatCfgByModemId(enModemID));
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if ((MTC_RCM_MODEM_RAT_CFG_CL == stAllModemState.stModemStateInfo[enModemID].enModemRatCfg)
         || (MTC_RCM_MODEM_RAT_CFG_C  == stAllModemState.stModemStateInfo[enModemID].enModemRatCfg))
        {
            stAllModemState.stModemStateInfo[enModemID].enUsimmState    = MTC_GetCsimStateInfo(enModemID);
        }
        else
#endif
        {
            stAllModemState.stModemStateInfo[enModemID].enUsimmState    = MTC_GetUsimStateInfo(enModemID);
        }

        if ( (PS_TRUE           == MTC_IsCsSessionInfoExit(enModemID))
          || (TAF_MTC_SRV_EXIST == enCsSrvStatus) )
        {
            stAllModemState.stModemStateInfo[enModemID].enIsCsSrvConnExist = TAF_MTC_SRV_EXIST;
        }
        else
        {
            stAllModemState.stModemStateInfo[enModemID].enIsCsSrvConnExist = TAF_MTC_SRV_NO_EXIST;
        }
    }

    /* 外置modem状态信息 */
    stAllModemState.stModemStateInfo[MTC_RCM_MODEM_OTHER].enIsCsSrvConnExist  = MTC_GetOutSideCsConnStateInfo(MTC_OUTSIDE_MODEM_CDMA);
    stAllModemState.stModemStateInfo[MTC_RCM_MODEM_OTHER].enIsPsSrvConnExist  = MTC_GetOutSidePsConnStateInfo(MTC_OUTSIDE_MODEM_CDMA);
    stAllModemState.stModemStateInfo[MTC_RCM_MODEM_OTHER].enPowerState        = MTC_GetOutSideModemPowerState(MTC_OUTSIDE_MODEM_CDMA);
    stAllModemState.stModemStateInfo[MTC_RCM_MODEM_OTHER].enUsimmState        = MTC_GetOutSideModemUsimmState(MTC_OUTSIDE_MODEM_CDMA);
    stAllModemState.stModemStateInfo[MTC_RCM_MODEM_OTHER].enModemRatCfg       = MTC_RCM_MODEM_RAT_CFG_C;

    /* 发送消息 */
    MTC_DEBUG_TraceEvent(&stAllModemState);

    return;
}



VOS_VOID MTC_DEBUG_TraceNotchInfo(VOS_VOID)
{
    MTC_MSG_BUF_STRU                   *pstBufAddr          = VOS_NULL_PTR;
    RRC_MTC_MS_BAND_INFO_STRU          *pstBandInfo         = VOS_NULL_PTR;
    RRC_MTC_MS_BAND_INFO_STRU          *pstNcellBandInfo    = VOS_NULL_PTR;
    MTC_DEBUG_ALL_MODEM_NOTCH_INFO_STRU stDebugNotchInfo;
    MODEM_ID_ENUM_UINT16                enModemId;

    PS_MEM_SET(&stDebugNotchInfo, 0x0, sizeof(MTC_DEBUG_ALL_MODEM_NOTCH_INFO_STRU));

    /*  填写消息头 */
    MTC_DEBUG_CFG_MSG_HDR(&stDebugNotchInfo.stMsgHeader,
                            UEPS_PID_MTC, UEPS_PID_MTC,
                            sizeof(MTC_DEBUG_ALL_MODEM_NOTCH_INFO_STRU) - VOS_MSG_HEAD_LENGTH);

    stDebugNotchInfo.stMsgHeader.ulMsgName  = ID_DEBUG_MTC_NOTCH_INFO;

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstBufAddr          = MTC_GetBufAddr(enModemId);
        pstBandInfo         = MTC_GetModemCurBandInfo(enModemId);
        pstNcellBandInfo    = MTC_GetModemNCellBandInfo(enModemId);

        PS_MEM_CPY(&stDebugNotchInfo.stModemNotchInfo[enModemId].stModemBandInfo, pstBandInfo, sizeof(RRC_MTC_MS_BAND_INFO_STRU));
        PS_MEM_CPY(&stDebugNotchInfo.stModemNotchInfo[enModemId].stModemBufInfo.stBufBandInfo.stModemBandInfo,
                   &pstBufAddr->stBufBandInfoMsg.stIntrusionBandInfoMsg.stCurBandInfo,
                   sizeof(RRC_MTC_MS_BAND_INFO_STRU));
        PS_MEM_CPY(&stDebugNotchInfo.stModemNotchInfo[enModemId].stModemBufInfo.stBufNCellFreqInfo.stLteNcellFreqInfo,
                   &pstBufAddr->stBufUsingFreqInfoMsg.stUsingFreqInfoMsg.stLteFreqInfo,
                   sizeof(RRC_MTC_LTE_NCELL_INFO_STRU));

        PS_MEM_CPY(&stDebugNotchInfo.stModemNotchInfo[enModemId].stModemBufInfo.stBufNCellFreqInfo.stTdsNcellFreqInfo,
                   &pstBufAddr->stBufUsingFreqInfoMsg.stUsingFreqInfoMsg.stTdsFreqInfo,
                   sizeof(RRC_MTC_TDS_NCELL_INFO_STRU));

        stDebugNotchInfo.stModemNotchInfo[enModemId].stModemBufInfo.stBufNCellFreqInfo.ucBufNcellBandFlag  = pstBufAddr->stBufUsingFreqInfoMsg.enExitBufMsgFlag;
        stDebugNotchInfo.stModemNotchInfo[enModemId].stModemBufInfo.stBufNCellFreqInfo.ulSndPid            = pstBufAddr->stBufUsingFreqInfoMsg.stUsingFreqInfoMsg.stMsgHeader.ulSenderPid;
        stDebugNotchInfo.stModemNotchInfo[enModemId].stModemBufInfo.stBufBandInfo.ucBufBandInfoFlag        = pstBufAddr->stBufBandInfoMsg.enExitBufMsgFlag;
        stDebugNotchInfo.stModemNotchInfo[enModemId].stModemBufInfo.stBufBandInfo.ulSndPid                 = pstBufAddr->stBufBandInfoMsg.stIntrusionBandInfoMsg.stMsgHeader.ulSenderPid;

        PS_MEM_CPY(&stDebugNotchInfo.stModemNotchInfo[enModemId].stModemNcellBandInfo, pstNcellBandInfo,sizeof(RRC_MTC_MS_BAND_INFO_STRU));
    }

    /* 发送消息 */
    MTC_DEBUG_TraceEvent(&stDebugNotchInfo);

    return;

}






/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

