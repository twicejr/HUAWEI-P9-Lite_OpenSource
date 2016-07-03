

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "AtCmdPacketProc.h"
#include "AtDataProc.h"

#include "product_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 -e960*/
#define    THIS_FILE_ID                 PS_FILE_ID_AT_CMD_PACKET_PROC_C
/*lint +e767 +e960*/

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/


AT_APP_CONN_STATE_ENUM_U32 AT_AppConvertPdpStateToConnStatus(
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    AT_APP_CONN_STATE_ENUM_U32          enConnStatus;

    switch (enPdpState)
    {
        case AT_PDP_STATE_ACTING:
            enConnStatus = AT_APP_DIALING;
            break;

        case AT_PDP_STATE_ACTED:
        case AT_PDP_STATE_DEACTING:
            enConnStatus = AT_APP_DIALED;
            break;

        case AT_PDP_STATE_IDLE:
        default:
            enConnStatus = AT_APP_UNDIALED;
            break;
    }

    return enConnStatus;
}


VOS_UINT32 AT_SetChdataPara_AppUser(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucCid;
    AT_CH_DATA_CHANNEL_ENUM_UINT32      enDataChannelId;
    RNIC_RMNET_ID_ENUM_UINT8            enRnicRmNetId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    ucCid = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    /* 指定CID的PDP若已经激活，则不允许删除或修改该CID的通道映射关系，直接返回ERROR */
    if ((VOS_TRUE == pstPsModemCtx->astChannelCfg[ucCid].ulUsed)
      && (VOS_TRUE == pstPsModemCtx->astChannelCfg[ucCid].ulRmNetActFlg))
    {
        return AT_ERROR;
    }

    /* 第二个参数为空，则表示删除配置关系 */
    if (0 == gastAtParaList[1].usParaLen)
    {
        pstPsModemCtx->astChannelCfg[ucCid].ulUsed     = VOS_FALSE;
        pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId  = AT_PS_INVALID_RMNET_ID;
        return AT_OK;
    }

    enDataChannelId = gastAtParaList[1].ulParaValue;

    /* 获取网卡ID */
    ulRslt = AT_PS_GetRnicRmNetIdFromChDataValue(ucIndex, enDataChannelId, &enRnicRmNetId);

    if (VOS_OK != ulRslt)
    {
        return AT_ERROR;
    }

    /* 查找是否有不同的<CID>配置了相同的<enRnicRmNetId> */
    for (ucLoop = 1; ucLoop <= TAF_MAX_CID; ucLoop++)
    {
        if ( (ucLoop != ucCid)
          && (VOS_TRUE == pstPsModemCtx->astChannelCfg[ucLoop].ulUsed)
          && (enRnicRmNetId == (RNIC_RMNET_ID_ENUM_UINT8)pstPsModemCtx->astChannelCfg[ucLoop].ulRmNetId))
        {
            /* 不同的<CID>配置了相同的<enRnicRmNetId>，直接返回ERROR */
            return AT_ERROR;
        }
    }

    /* 配置数传通道映射表 */
    pstPsModemCtx->astChannelCfg[ucCid].ulUsed     = VOS_TRUE;
    pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId  = enRnicRmNetId;

    return AT_OK;
}


VOS_UINT32 AT_SetChdataPara_HsicUser(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucCid;
    AT_CH_DATA_CHANNEL_ENUM_UINT32      enDataChannelId;
    UDI_DEVICE_ID_E                     enUdiDevId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    ucCid = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    /* 指定CID的PDP若已经激活，则不允许删除或修改该CID的通道映射关系，直接返回ERROR */
    if ((VOS_TRUE == pstPsModemCtx->astChannelCfg[ucCid].ulUsed)
      && (VOS_TRUE == pstPsModemCtx->astChannelCfg[ucCid].ulRmNetActFlg))
    {
        return AT_ERROR;
    }

    /* 第二个参数为空，则表示删除配置关系 */
    if (0 == gastAtParaList[1].usParaLen)
    {
        pstPsModemCtx->astChannelCfg[ucCid].ulUsed     = VOS_FALSE;
        pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId  = UDI_INVAL_DEV_ID;
        return AT_OK;
    }

    enDataChannelId = gastAtParaList[1].ulParaValue;

    /* 低软接口返回值修改，之前返回PS_TRUE的为SUPPORT */
    if (BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_HSIC_NCM))
    {
        if (AT_CH_DATA_CHANNEL_ID_1 == enDataChannelId)
        {
            enUdiDevId = UDI_NCM_HSIC_NCM0_ID;
        }
        else if(AT_CH_DATA_CHANNEL_ID_2 == enDataChannelId)
        {
            enUdiDevId = UDI_NCM_HSIC_NCM1_ID;
        }
        else
        {
            enUdiDevId = UDI_NCM_HSIC_NCM2_ID;
        }
    }
    else
    {
        if (AT_CH_DATA_CHANNEL_ID_1 == enDataChannelId)
        {
            enUdiDevId = UDI_ACM_HSIC_ACM1_ID;
        }
        else if(AT_CH_DATA_CHANNEL_ID_2 == enDataChannelId)
        {
            enUdiDevId = UDI_ACM_HSIC_ACM3_ID;
        }
        else
        {
            enUdiDevId = UDI_ACM_HSIC_ACM5_ID;
        }
    }

    /* 查找是否有不同的<CID>配置了相同的<enUdiDevId> */
    for (ucLoop = 1; ucLoop <= TAF_MAX_CID; ucLoop++)
    {
        if ( (ucLoop != ucCid)
          && (VOS_TRUE == pstPsModemCtx->astChannelCfg[ucLoop].ulUsed)
          && (enUdiDevId == (UDI_DEVICE_ID_E)pstPsModemCtx->astChannelCfg[ucLoop].ulRmNetId))
        {
            /* 不同的<CID>配置了相同的<enUdiDevId>，直接返回ERROR */
            return AT_ERROR;
        }
    }

    /* 配置数传通道映射表 */
    pstPsModemCtx->astChannelCfg[ucCid].ulUsed     = VOS_TRUE;
    pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId  = enUdiDevId;

    return AT_OK;
}


VOS_UINT32 AT_SetChdataPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucUserIndex;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数过多 */
    if (gucAtParaIndex > 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 第一个参数为空 */
    if ((0 == gastAtParaList[0].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ucUserIndex = ucIndex;

    /* PCUI口且已设置PCUI口模拟NDISDUP拨号 */
    if (AT_USBCOM_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetPcuiPsCallFlag())
        {
            ucUserIndex = AT_GetPcuiUsertId();
        }
    }

    /* CTRL口且已设置CTRL口模拟NDISDUP拨号 */
    if (AT_CTR_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetCtrlPsCallFlag())
        {
            ucUserIndex = AT_GetCtrlUserId();
        }
    }

    /* PCUI2口且已设置PCUI2口模拟NDISDUP拨号 */
    if (AT_PCUI2_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetPcui2PsCallFlag())
        {
            ucUserIndex = AT_GetPcui2UserId();
        }
    }

    /* HSIC和MUX通道的处理 */
    if (VOS_TRUE == AT_IsHsicOrMuxUser(ucUserIndex))
    {
        return AT_SetChdataPara_HsicUser(ucUserIndex);
    }

    /* APP通道的处理 */
    if (VOS_TRUE == AT_CheckAppUser(ucUserIndex))
    {
        return AT_SetChdataPara_AppUser(ucUserIndex);
    }

    return AT_ERROR;
}


VOS_UINT32 AT_QryChdataPara_AppUser(TAF_UINT8 ucIndex)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucNum;
    VOS_UINT16                          usLength;
    AT_CH_DATA_CHANNEL_ENUM_UINT32      enDataChannelId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    ucNum    = 0;
    usLength = 0;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    /* 输出结果 */
    for (ucLoop = 1; ucLoop <= TAF_MAX_CID; ucLoop++)
    {
        if ( (VOS_TRUE == pstPsModemCtx->astChannelCfg[ucLoop].ulUsed)
          && (AT_PS_INVALID_RMNET_ID != pstPsModemCtx->astChannelCfg[ucLoop].ulRmNetId) )
        {
            if (0 != ucNum)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);
            }

            /* ^CHDATA:  */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,"^CHDATA: ");

            /* <cid> */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%d", ucLoop);

            /* <datachannel> */
            ulRslt = AT_PS_GetChDataValueFromRnicRmNetId((RNIC_RMNET_ID_ENUM_UINT8)(pstPsModemCtx->astChannelCfg[ucLoop].ulRmNetId), &enDataChannelId);

            if (VOS_OK != ulRslt)
            {
                return AT_ERROR;
            }

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,",%d", enDataChannelId);

            ucNum++;
        }
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_QryChdataPara_HsicUser(TAF_UINT8 ucIndex)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucNum;
    VOS_UINT16                          usLength;
    AT_CH_DATA_CHANNEL_ENUM_UINT32      enDataChannelId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    ucNum    = 0;
    usLength = 0;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    /* 输出结果 */
    for (ucLoop = 1; ucLoop <= TAF_MAX_CID; ucLoop++)
    {
        if ( (VOS_TRUE == pstPsModemCtx->astChannelCfg[ucLoop].ulUsed)
          && (UDI_INVAL_DEV_ID != pstPsModemCtx->astChannelCfg[ucLoop].ulRmNetId) )
        {
            if (0 != ucNum)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);
            }

            /* ^CHDATA:  */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,"^CHDATA: ");

            /* <cid> */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%d", ucLoop);

            /* <datachannel> */
            switch ( pstPsModemCtx->astChannelCfg[ucLoop].ulRmNetId)
            {
                case UDI_ACM_HSIC_ACM1_ID:
                case UDI_NCM_HSIC_NCM0_ID:
                    enDataChannelId = AT_CH_DATA_CHANNEL_ID_1;
                    break;
                case UDI_ACM_HSIC_ACM3_ID:
                case UDI_NCM_HSIC_NCM1_ID:
                    enDataChannelId = AT_CH_DATA_CHANNEL_ID_2;
                    break;
                case UDI_ACM_HSIC_ACM5_ID:
                case UDI_NCM_HSIC_NCM2_ID:
                    enDataChannelId = AT_CH_DATA_CHANNEL_ID_3;
                    break;
                default:
                    return AT_ERROR;
            }
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,",%d", enDataChannelId);

            ucNum++;
        }
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_QryChdataPara(TAF_UINT8 ucIndex)
{
    VOS_UINT8                           ucUserId;

    /*命令状态类型检查*/
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    ucUserId = ucIndex;

    /* PCUI口且已设置PCUI口模拟NDISDUP拨号 */
    if (AT_USBCOM_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetPcuiPsCallFlag())
        {
            ucUserId = AT_GetPcuiUsertId();
        }
    }

    /* CTRL口且已设置CTRL口模拟NDISDUP拨号 */
    if (AT_CTR_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetCtrlPsCallFlag())
        {
            ucUserId = AT_GetCtrlUserId();
        }
    }

    /* PCUI2口且已设置PCUI2口模拟NDISDUP拨号 */
    if (AT_PCUI2_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetPcui2PsCallFlag())
        {
            ucUserId = AT_GetPcui2UserId();
        }
    }

    /* HSIC和MUX通道的处理 */
    if (VOS_TRUE == AT_IsHsicOrMuxUser(ucUserId))
    {
        return AT_QryChdataPara_HsicUser(ucUserId);
    }

    /* APP通道的处理 */
    if (VOS_TRUE == AT_CheckAppUser(ucUserId))
    {
        return AT_QryChdataPara_AppUser(ucUserId);
    }

    return AT_ERROR;
}


VOS_UINT32 AT_TestChdataPara(VOS_UINT8 ucIndex)
{
    /* 通道检查 */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: %s",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       CHDATA_TEST_CMD_PARA_STRING);

    return AT_OK;
}


VOS_UINT32 AT_PS_ReportDhcp(VOS_UINT8 ucIndex)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulSpeed;
    VOS_UINT8                           ucCallId;
    AT_DHCP_PARA_STRU                   stDhcpConfig;

    usLength = 0;

    ucCallId = AT_PS_TransCidToCallId(ucIndex, (VOS_UINT8)gastAtParaList[0].ulParaValue);
    if (VOS_TRUE != AT_PS_IsCallIdValid(ucIndex, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ReportDhcp:ERROR: CallId is invalid!");
        return AT_ERROR;
    }

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    if (AT_PDP_STATE_ACTED != pstCallEntity->enIpv4State)
    {
        AT_WARN_LOG("AT_PS_ReportDhcp: PDP is not actived.");
        return AT_ERROR;
    }

    /* 获取接入理论带宽*/
    if (VOS_ERR == AT_GetDisplayRate(ucIndex, &ulSpeed))
    {
        ulSpeed = AT_DEF_DISPLAY_SPEED;
        AT_WARN_LOG("AT_PS_ReportDhcp: ERROR : AT_GetDisplayRate Error!");
    }

    /* 获取DHCP参数(网络序) */
    AT_GetDhcpPara(&stDhcpConfig, &pstCallEntity->stIpv4DhcpInfo);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulIPAddr);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulSubNetMask);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulGateWay);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulGateWay);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulPrimDNS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulSndDNS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%d,",ulSpeed);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%d",ulSpeed);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 At_SetDhcpPara(VOS_UINT8 ucIndex)
{
    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数过多 */
    if (gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 查询指定CID的实体PDP上下文 */
    return AT_PS_ReportDhcp(ucIndex);
}


VOS_UINT32 At_QryDhcpPara_AppUser(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulSpeed;
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity = VOS_NULL_PTR;
    VOS_UINT32                          ulPdpActingFlg;
    VOS_UINT32                          ulPdpDeactingFlg;
    AT_DHCP_PARA_STRU                   stDhcpConfig;

    usLength         = 0;
    pstAppPdpEntity  = AT_APP_GetPdpEntInfoAddr();
    ulPdpActingFlg   = AT_AppCheckIpv4PdpState(AT_PDP_STATE_ACTING);
    ulPdpDeactingFlg = AT_AppCheckIpv4PdpState(AT_PDP_STATE_DEACTING);

    if ( (VOS_TRUE == ulPdpActingFlg)
      || (VOS_TRUE == ulPdpDeactingFlg)
      || ((AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4State)
       && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4v6State)))
    {
        AT_WARN_LOG("At_QryDhcpPara_AppUser: PDP is not active for APP.");
        return AT_ERROR;
    }

    /* 获取接入理论带宽*/
    if (VOS_ERR == AT_GetDisplayRate(ucIndex, &ulSpeed))
    {
        ulSpeed = AT_DEF_DISPLAY_SPEED;
        AT_WARN_LOG("At_QryDhcpPara_AppUser: ERROR : AT_GetDisplayRate Error!");
    }

    /* 获取DHCP参数(网络序) */
    AT_GetDhcpPara(&stDhcpConfig, &pstAppPdpEntity->stIpv4Dhcp);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulIPAddr);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulSubNetMask);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulGateWay);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulGateWay);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulPrimDNS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulSndDNS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%d,",ulSpeed);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%d",ulSpeed);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}


VOS_UINT32 At_QryDhcpPara_NdisUser(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulSpeed;
    VOS_UINT32                          ulPdpActingFlg;
    VOS_UINT32                          ulPdpDeactingFlg;
    AT_DHCP_PARA_STRU                   stDhcpConfig;

    ulPdpActingFlg      = AT_NdisCheckIpv4PdpState(AT_PDP_STATE_ACTING);
    ulPdpDeactingFlg    = AT_NdisCheckIpv4PdpState(AT_PDP_STATE_DEACTING);
    usLength            = 0;

    if ( (VOS_TRUE == ulPdpActingFlg)
      || (VOS_TRUE == ulPdpDeactingFlg)
      || ((AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4State)
       && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4v6State)))
    {
        AT_WARN_LOG("At_QryDhcpPara_NdisUser AT_NdisGetState:");
        return AT_ERROR;
    }

    /* 获取接入理论带宽*/
    if (VOS_ERR == AT_GetDisplayRate(ucIndex, &ulSpeed))
    {
        ulSpeed = AT_DEF_DISPLAY_SPEED;
        AT_ERR_LOG("At_QryDhcpPara_NdisUser : ERROR : AT_GetDisplayRate Error!");
    }

    /* 获取DHCP参数(网络序) */
    AT_NdisGetDhcpPara(&stDhcpConfig);

    usLength =  (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr, "%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%X,",stDhcpConfig.stDhcpCfg.ulIPAddr);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%X,",stDhcpConfig.stDhcpCfg.ulSubNetMask);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%X,",stDhcpConfig.stDhcpCfg.ulGateWay);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%X,",stDhcpConfig.stDhcpCfg.ulGateWay);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%X,",stDhcpConfig.stDhcpCfg.ulPrimDNS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%X,",stDhcpConfig.stDhcpCfg.ulSndDNS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%d,",ulSpeed);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%d",ulSpeed);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


AT_USER_TYPE AT_PS_GetDailPortUsrType(AT_USER_TYPE enUsrType)
{
    VOS_UINT8                          *pucSystemAppConfig = VOS_NULL_PTR;
    AT_USER_TYPE                        enExpUsrType;

    pucSystemAppConfig = AT_GetSystemAppConfigAddr();
    enExpUsrType       = enUsrType;

    if (AT_USBCOM_USER == enUsrType)
    {
        switch (*pucSystemAppConfig)
        {
            case SYSTEM_APP_MP:
                enExpUsrType = AT_NDIS_USER;
                break;

            case SYSTEM_APP_WEBUI:
                enExpUsrType = AT_APP_USER;
                break;

            default:
                break;
        }
    }

    return enExpUsrType;
}


VOS_UINT32 At_QryDhcpPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;
    AT_USER_TYPE                        enUsrType;

    ulResult  = AT_OK;

    enUsrType = AT_PS_GetDailPortUsrType(gastAtClientTab[ucIndex].UserType);

    switch (enUsrType)
    {
        case AT_NDIS_USER:
            ulResult = At_QryDhcpPara_NdisUser(ucIndex);
            break;

        case AT_APP_USER:
            ulResult = At_QryDhcpPara_AppUser(ucIndex);
            break;

        default:
            break;
    }

    return ulResult;
}


VOS_UINT32 AT_TestDhcpPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-11)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}

#if (FEATURE_ON == FEATURE_IPV6)

VOS_UINT32 AT_PS_ReportDhcpv6(TAF_UINT8 ucIndex)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulSpeed;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucInvalidIpv6Addr[TAF_IPV6_ADDR_LEN];

    usLength = 0;
    PS_MEM_SET(aucIpv6AddrStr, 0x00, (TAF_MAX_IPV6_ADDR_COLON_STR_LEN));
    PS_MEM_SET(aucInvalidIpv6Addr, 0x00, TAF_IPV6_ADDR_LEN);

    ucCallId = AT_PS_TransCidToCallId(ucIndex, (VOS_UINT8)gastAtParaList[0].ulParaValue);
    if (VOS_TRUE != AT_PS_IsCallIdValid(ucIndex, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ReportDhcpv6:ERROR: CallId is invalid!");
        return AT_ERROR;
    }

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    if (AT_PDP_STATE_ACTED != pstCallEntity->enIpv6State)
    {
        AT_WARN_LOG("AT_PS_ReportDhcpv6: PDP is not actived.");
        return AT_ERROR;
    }

    if (VOS_TRUE != pstCallEntity->stIpv6RaInfo.bitOpPrefixAddr)
    {
        AT_WARN_LOG("AT_PS_ReportDhcpv6: Prefix address is not received.");
        return AT_ERROR;
    }

    /* 获取接入理论带宽*/
    if (VOS_ERR == AT_GetDisplayRate(ucIndex, &ulSpeed))
    {
        ulSpeed = AT_DEF_DISPLAY_SPEED;
        AT_WARN_LOG("AT_PS_ReportDhcpv6: ERROR : AT_GetDisplayRate Error!");
    }

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr, "%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* 填写IPV6地址 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      pstCallEntity->stIpv6DhcpInfo.aucIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, "%s", aucIpv6AddrStr);

    /* 填写IPV6掩码, 该字段填全0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* 填写IPV6网关, 该字段填全0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* 填写DHCP IPV6, 该字段填全0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* 填写IPV6 Primary DNS */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      pstCallEntity->stIpv6DhcpInfo.aucIpv6PrimDNS,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* 填写IPV6 Secondary DNS */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      pstCallEntity->stIpv6DhcpInfo.aucIpv6SecDNS,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* 填写MAX TX/RX Rate */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%d", ulSpeed);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%d", ulSpeed);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_SetDhcpv6Para(VOS_UINT8 ucIndex)
{
    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数错误 */
    if (gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 查询指定CID的实体PDP上下文 */
    return AT_PS_ReportDhcpv6(ucIndex);
}

VOS_UINT32 AT_QryDhcpV6Para_AppUser(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucInvalidIpv6Addr[TAF_IPV6_ADDR_LEN];
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity = VOS_NULL_PTR;
    VOS_UINT32                          ulPdpActingFlg;
    VOS_UINT32                          ulPdpDeactingFlg;
    VOS_UINT32                          ulSpeed;

    usLength                            = 0;

    PS_MEM_SET(aucInvalidIpv6Addr, 0x00, sizeof(aucInvalidIpv6Addr));

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    ulPdpActingFlg   = AT_AppCheckIpv6PdpState(AT_PDP_STATE_ACTING);
    ulPdpDeactingFlg = AT_AppCheckIpv6PdpState(AT_PDP_STATE_DEACTING);

    if ( (VOS_TRUE == ulPdpActingFlg)
      || (VOS_TRUE == ulPdpDeactingFlg)
      || ((AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv6State)
       && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4v6State)))
    {
        AT_ERR_LOG("AT_QryDhcpV6Para_AppUser:ERROR: PDP is not active for APP.");
        return AT_ERROR;
    }

    /* 获取接入理论带宽*/
    if (VOS_ERR == AT_GetDisplayRate(ucIndex, &ulSpeed))
    {
        ulSpeed = AT_DEF_DISPLAY_SPEED;
        AT_WARN_LOG("AT_QryDhcpV6Para_AppUser:WARNING: AT_GetDisplayRate Error!");
    }

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr, "%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* 填写IPV6地址 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      pstAppPdpEntity->stIpv6Dhcp.aucIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, "%s", aucIpv6AddrStr);

    /* 填写IPV6掩码, 该字段填全0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* 填写IPV6网关, 该字段填全0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* 填写DHCP IPV6, 该字段填全0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* 填写IPV6 Primary DNS */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      pstAppPdpEntity->stIpv6Dhcp.aucIpv6PrimDNS,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* 填写IPV6 Secondary DNS */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      pstAppPdpEntity->stIpv6Dhcp.aucIpv6SecDNS,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* 填写MAX TX/RX Rate */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength, ",%d", ulSpeed);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength, ",%d", ulSpeed);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_QryDhcpV6Para_NdisUser(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucInvalidIpv6Addr[TAF_IPV6_ADDR_LEN];
    VOS_UINT32                          ulPdpActingFlg;
    VOS_UINT32                          ulPdpDeactingFlg;
    VOS_UINT32                          ulSpeed;

    usLength                            = 0;

    PS_MEM_SET(aucInvalidIpv6Addr, 0x00, sizeof(aucInvalidIpv6Addr));

    ulPdpActingFlg   = AT_NdisCheckIpv6PdpState(AT_PDP_STATE_ACTING);
    ulPdpDeactingFlg = AT_NdisCheckIpv6PdpState(AT_PDP_STATE_DEACTING);

    if ((VOS_TRUE == ulPdpActingFlg)
     || (VOS_TRUE == ulPdpDeactingFlg)
     || ((AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv6State)
      && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4v6State)))
    {
        AT_WARN_LOG("AT_QryDhcpV6Para_NdisUser AT_NdisGetState:");
        return AT_ERROR;
    }

    /* 获取接入理论带宽*/
    if (VOS_ERR == AT_GetDisplayRate(ucIndex, &ulSpeed))
    {
        ulSpeed = AT_DEF_DISPLAY_SPEED;
        AT_ERR_LOG("AT_QryDhcpV6Para_NdisUser : ERROR : AT_GetDisplayRate Error!");
    }

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr, "%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* 填写IPV6地址 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      g_stAtNdisDhcpPara.stIpv6Dhcp.aucIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, "%s", aucIpv6AddrStr);

    /* 填写IPV6掩码, 该字段填全0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* 填写IPV6网关, 该字段填全0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* 填写DHCP IPV6, 该字段填全0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* 填写IPV6 Primary DNS */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      g_stAtNdisDhcpPara.stIpv6Dhcp.aucIpv6PrimDNS,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s",  aucIpv6AddrStr);

    /* 填写IPV6 Secondary DNS */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      g_stAtNdisDhcpPara.stIpv6Dhcp.aucIpv6SecDNS,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s",  aucIpv6AddrStr);

    /* 填写MAX TX/RX Rate */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength, ",%d", ulSpeed);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength, ",%d", ulSpeed);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_QryDhcpv6Para(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;
    AT_USER_TYPE                        enUsrType;

    ulResult  = AT_OK;

    enUsrType = AT_PS_GetDailPortUsrType(gastAtClientTab[ucIndex].UserType);

    switch (enUsrType)
    {
        case AT_NDIS_USER:
            ulResult = AT_QryDhcpV6Para_NdisUser(ucIndex);
            break;

        case AT_APP_USER:
            ulResult = AT_QryDhcpV6Para_AppUser(ucIndex);
            break;

        default:
            break;
    }

    return ulResult;
}


VOS_UINT32 AT_TestDhcpv6Para(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-11)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}

VOS_UINT32 AT_PS_ReportApraInfo(TAF_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucInvalidIpv6Addr[TAF_IPV6_ADDR_LEN];
    VOS_UINT32                          ulMtuSize;
    VOS_UINT32                          ulPrefixBitLen;
    VOS_UINT32                          ulPreferredLifetime;
    VOS_UINT32                          ulValidLifetime;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;

    usLength                            = 0;
    PS_MEM_SET(aucInvalidIpv6Addr, 0x00, sizeof(aucInvalidIpv6Addr));
    PS_MEM_SET(aucIpv6AddrStr, 0x00, (TAF_MAX_IPV6_ADDR_COLON_STR_LEN));

    ucCallId = AT_PS_TransCidToCallId(ucIndex, (VOS_UINT8)gastAtParaList[0].ulParaValue);
    if (VOS_TRUE != AT_PS_IsCallIdValid(ucIndex, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ReportApraInfo:ERROR: CallId is invalid!");
        return AT_ERROR;
    }

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    if (AT_PDP_STATE_ACTED != pstCallEntity->enIpv6State)
    {
        AT_WARN_LOG("AT_PS_ReportApraInfo: PDP is not actived.");
        return AT_ERROR;
    }

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* 填写MTU */
    if (VOS_FALSE == pstCallEntity->stIpv6RaInfo.bitOpMtuSize)
    {
        ulMtuSize = 0;
    }
    else
    {
        ulMtuSize = pstCallEntity->stIpv6RaInfo.ulMtuSize;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       "%d",
                                       ulMtuSize);
    /* 填写Prefix */
    if (VOS_FALSE == pstCallEntity->stIpv6RaInfo.bitOpPrefixAddr)
    {
        ulPrefixBitLen = 0;
        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          aucInvalidIpv6Addr,
                                          TAF_IPV6_STR_RFC2373_TOKENS);
    }
    else
    {
        ulPrefixBitLen = pstCallEntity->stIpv6RaInfo.ulPrefixBitLen;
        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          pstCallEntity->stIpv6RaInfo.aucPrefixAddr,
                                          TAF_IPV6_STR_RFC2373_TOKENS);
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       ",\"%s/%d\"",
                                       aucIpv6AddrStr,
                                       ulPrefixBitLen);

    /* 填写Preferred Lifetime */
    if (VOS_FALSE == pstCallEntity->stIpv6RaInfo.bitOpPreferredLifetime)
    {
        ulPreferredLifetime = 0;
    }
    else
    {
        ulPreferredLifetime = pstCallEntity->stIpv6RaInfo.ulPreferredLifetime;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       ",%u",
                                       ulPreferredLifetime);

    if (VOS_FALSE == pstCallEntity->stIpv6RaInfo.bitOpValidLifetime)
    {
        ulValidLifetime = 0;
    }
    else
    {
        ulValidLifetime = pstCallEntity->stIpv6RaInfo.ulValidLifetime;
    }

    /* 填写Valid Lifetime */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       ",%u",
                                       ulValidLifetime);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_SetApRaInfoPara(VOS_UINT8 ucIndex)
{
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数错误 */
    if (gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 查询指定CID的实体PDP上下文 */
    return AT_PS_ReportApraInfo(ucIndex);
}


VOS_UINT32 AT_QryApRaInfoPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucInvalidIpv6Addr[TAF_IPV6_ADDR_LEN];
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_IPV6_RA_INFO_STRU               *pstAppRaInfoAddr;
    VOS_UINT32                          ulPdpActingFlg;
    VOS_UINT32                          ulPdpDeactingFlg;
    VOS_UINT32                          ulMtuSize;
    VOS_UINT32                          ulPrefixBitLen;
    VOS_UINT32                          ulPreferredLifetime;
    VOS_UINT32                          ulValidLifetime;

    usLength                            = 0;

    PS_MEM_SET(aucInvalidIpv6Addr, 0x00, sizeof(aucInvalidIpv6Addr));

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();
    pstAppRaInfoAddr                    = AT_APP_GetRaInfoAddr();

    ulPdpActingFlg   = AT_AppCheckIpv6PdpState(AT_PDP_STATE_ACTING);
    ulPdpDeactingFlg = AT_AppCheckIpv6PdpState(AT_PDP_STATE_DEACTING);

    if ( (VOS_TRUE == ulPdpActingFlg)
      || (VOS_TRUE == ulPdpDeactingFlg)
      || ( (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv6State)
        && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4v6State) ) )
    {
        AT_ERR_LOG("AT_QryApRaInfoPara:ERROR: PDP is not active for APP.");
        return AT_ERROR;
    }

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* 填写MTU */
    if (VOS_FALSE == pstAppRaInfoAddr->bitOpMtuSize)
    {
        ulMtuSize = 0;
    }
    else
    {
        ulMtuSize = pstAppRaInfoAddr->ulMtuSize;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       "%d",
                                       ulMtuSize);
    /* 填写Prefix */
    if (VOS_FALSE == pstAppRaInfoAddr->bitOpPrefixAddr)
    {
        ulPrefixBitLen = 0;
        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          aucInvalidIpv6Addr,
                                          TAF_IPV6_STR_RFC2373_TOKENS);
    }
    else
    {
        ulPrefixBitLen = pstAppRaInfoAddr->ulPrefixBitLen;
        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          pstAppRaInfoAddr->aucPrefixAddr,
                                          (VOS_UINT8)ulPrefixBitLen/16);
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       ",\"%s/%d\"",
                                       aucIpv6AddrStr,
                                       ulPrefixBitLen);

    /* 填写Preferred Lifetime */
    if (VOS_FALSE == pstAppRaInfoAddr->bitOpPreferredLifetime)
    {
        ulPreferredLifetime = 0;
    }
    else
    {
        ulPreferredLifetime = pstAppRaInfoAddr->ulPreferredLifetime;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       ",%u",
                                       ulPreferredLifetime);

    if (VOS_FALSE == pstAppRaInfoAddr->bitOpValidLifetime)
    {
        ulValidLifetime = 0;
    }
    else
    {
        ulValidLifetime = pstAppRaInfoAddr->ulValidLifetime;
    }

    /* 填写Valid Lifetime */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       ",%u",
                                       ulValidLifetime);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_TestApRaInfoPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-11)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}



VOS_UINT32 AT_PS_ReportLanAddr(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucCallId;
    AT_PS_CALL_ENTITY_STRU             *pstPsCallEntity = VOS_NULL_PTR;
    AT_IPV6_RA_INFO_STRU               *pstIpv6RaInfo;
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucInvalidIpv6Addr[TAF_IPV6_ADDR_LEN];

    usLength = 0;
    PS_MEM_SET(aucInvalidIpv6Addr, 0x00, sizeof(aucInvalidIpv6Addr));

    /* 根据cid获取对应的callid */
    ucCallId = AT_PS_TransCidToCallId(ucIndex, (VOS_UINT8)gastAtParaList[0].ulParaValue);

    if (VOS_TRUE != AT_PS_IsCallIdValid(ucIndex, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ReportLanAddr:ERROR: CallId is invalid!");
        return AT_ERROR;
    }

    pstPsCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    /* 当前未激活，直接返回error */
    if (AT_PDP_STATE_ACTED != pstPsCallEntity->enIpv6State)
    {
        return AT_ERROR;
    }

    pstIpv6RaInfo = &(pstPsCallEntity->stIpv6RaInfo);

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    if (VOS_FALSE == pstIpv6RaInfo->bitOpLanAddr)
    {
        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          aucInvalidIpv6Addr,
                                          TAF_IPV6_STR_RFC2373_TOKENS);
    }
    else
    {
        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          pstIpv6RaInfo->aucLanAddr,
                                          TAF_IPV6_STR_RFC2373_TOKENS);
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       "\"%s\"",
                                       aucIpv6AddrStr);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       ",%d",
                                       pstIpv6RaInfo->ulPrefixBitLen);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_SetApLanAddrPara(VOS_UINT8 ucIndex)
{
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数错误 */
    if (gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 查询指定CID的实体PDP上下文 */
    return AT_PS_ReportLanAddr(ucIndex);
}


VOS_UINT32 AT_QryApLanAddrPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucInvalidIpv6Addr[TAF_IPV6_ADDR_LEN];
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_IPV6_RA_INFO_STRU               *pstAppRaInfoAddr;
    VOS_UINT32                          ulPdpActingFlg;
    VOS_UINT32                          ulPdpDeactingFlg;

    usLength                            = 0;
    PS_MEM_SET(aucInvalidIpv6Addr, 0x00, sizeof(aucInvalidIpv6Addr));

    if (AT_APP_USER == gastAtClientTab[ucIndex].UserType)
    {

        pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();
        pstAppRaInfoAddr                    = AT_APP_GetRaInfoAddr();

        ulPdpActingFlg   = AT_AppCheckIpv6PdpState(AT_PDP_STATE_ACTING);
        ulPdpDeactingFlg = AT_AppCheckIpv6PdpState(AT_PDP_STATE_DEACTING);

        if ( (VOS_TRUE == ulPdpActingFlg)
          || (VOS_TRUE == ulPdpDeactingFlg)
          || ( (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv6State)
            && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4v6State) ) )
        {
            AT_ERR_LOG("AT_QryApLanAddrPara:ERROR: PDP is not active for APP.");
            return AT_ERROR;
        }

        usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr,
                                           "%s: ",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        if (VOS_FALSE == pstAppRaInfoAddr->bitOpLanAddr)
        {
            AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                              aucInvalidIpv6Addr,
                                              TAF_IPV6_STR_RFC2373_TOKENS);
        }
        else
        {
            AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                              pstAppRaInfoAddr->aucLanAddr,
                                              TAF_IPV6_STR_RFC2373_TOKENS);
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "\"%s\"",
                                           aucIpv6AddrStr);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                           ",%d",
                                           pstAppRaInfoAddr->ulPrefixBitLen);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_TestApLanAddrPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-11)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}

#endif


VOS_UINT32 AT_PS_ReportConnSt(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucCallId;
    AT_PS_CALL_ENTITY_STRU             *pstPsCallEntity = VOS_NULL_PTR;
    AT_APP_CONN_STATE_ENUM_U32          enIpv4ConnStatus;
#if (FEATURE_ON == FEATURE_IPV6)
    AT_APP_CONN_STATE_ENUM_U32          enIpv6ConnStatus;
#endif
    VOS_UINT16                          usLength;

    usLength = 0;

    /* 根据cid获取对应的callid */
    ucCallId = AT_PS_TransCidToCallId(ucIndex, (VOS_UINT8)gastAtParaList[0].ulParaValue);

    if (VOS_TRUE != AT_PS_IsCallIdValid(ucIndex, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ReportConnSt:ERROR: CallId is invalid!");
        return AT_ERROR;
    }

    pstPsCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

#if (FEATURE_ON == FEATURE_IPV6)
    switch (AT_GetIpv6Capability())
    {
        case AT_IPV6_CAPABILITY_IPV4_ONLY:
            enIpv4ConnStatus = AT_AppConvertPdpStateToConnStatus(pstPsCallEntity->enIpv4State);

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%d,\"IPV4\"",
                                               enIpv4ConnStatus);
            break;

        case AT_IPV6_CAPABILITY_IPV6_ONLY:
            enIpv6ConnStatus = AT_AppConvertPdpStateToConnStatus(pstPsCallEntity->enIpv6State);

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%d,\"IPV6\"",
                                               enIpv6ConnStatus);
            break;

        case AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP:
        case AT_IPV6_CAPABILITY_IPV4V6_OVER_TWO_PDP:
            enIpv4ConnStatus = AT_AppConvertPdpStateToConnStatus(pstPsCallEntity->enIpv4State);
            enIpv6ConnStatus = AT_AppConvertPdpStateToConnStatus(pstPsCallEntity->enIpv6State);

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%d,\"IPV4\"",
                                               enIpv4ConnStatus);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               ",%d,\"IPV6\"",
                                               enIpv6ConnStatus);
            break;

        default:
            break;
    }
#else
    enIpv4ConnStatus = AT_AppConvertPdpStateToConnStatus(pstPsCallEntity->enIpv4State);

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d,\"IPV4\"",
                                       enIpv4ConnStatus);
#endif

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32  At_SetApConnStPara(
    VOS_UINT8                           ucIndex
)
{
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数错误 */
    if (gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 查询指定CID的实体PDP上下文 */
    return AT_PS_ReportConnSt(ucIndex);
}


VOS_UINT32  At_QryApConnStPara(
    VOS_UINT8                           ucIndex
)
{
    AT_APP_CONN_STATE_ENUM_U32         enIpv4ConnStatus;
#if (FEATURE_ON == FEATURE_IPV6)
    AT_APP_CONN_STATE_ENUM_U32         enIpv6ConnStatus;
    AT_APP_CONN_STATE_ENUM_U32         enIpv4v6ConnStatus;
#endif
    VOS_UINT16                         usLength = 0;

#if (FEATURE_ON == FEATURE_IPV6)
    switch (AT_GetIpv6Capability())
    {
        case AT_IPV6_CAPABILITY_IPV4_ONLY:
            enIpv4ConnStatus = AT_AppConvertPdpStateToConnStatus(AT_AppGetPdpState(TAF_PDP_IPV4));

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%d,\"IPV4\"",
                                               enIpv4ConnStatus);
            break;

        case AT_IPV6_CAPABILITY_IPV6_ONLY:
            enIpv6ConnStatus = AT_AppConvertPdpStateToConnStatus(AT_AppGetPdpState(TAF_PDP_IPV6));

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%d,\"IPV6\"",
                                               enIpv6ConnStatus);
            break;

        case AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP:
            enIpv4v6ConnStatus  = AT_AppConvertPdpStateToConnStatus(AT_AppGetPdpState(TAF_PDP_IPV4V6));

            if (AT_APP_UNDIALED == enIpv4v6ConnStatus)
            {
                enIpv4ConnStatus = AT_AppConvertPdpStateToConnStatus(AT_AppGetPdpState(TAF_PDP_IPV4));
                enIpv6ConnStatus = AT_AppConvertPdpStateToConnStatus(AT_AppGetPdpState(TAF_PDP_IPV6));
            }
            else
            {
                enIpv4ConnStatus = enIpv4v6ConnStatus;
                enIpv6ConnStatus = enIpv4v6ConnStatus;
            }

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%d,\"IPV4\"",
                                               enIpv4ConnStatus);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               ",%d,\"IPV6\"",
                                               enIpv6ConnStatus);
            break;

        case AT_IPV6_CAPABILITY_IPV4V6_OVER_TWO_PDP:
            enIpv4ConnStatus = AT_AppConvertPdpStateToConnStatus(AT_AppGetPdpState(TAF_PDP_IPV4));
            enIpv6ConnStatus = AT_AppConvertPdpStateToConnStatus(AT_AppGetPdpState(TAF_PDP_IPV6));

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%d,\"IPV4\"",
                                               enIpv4ConnStatus);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               ",%d,\"IPV6\"",
                                               enIpv6ConnStatus);
            break;

        default:
            break;
    }
#else
    enIpv4ConnStatus = AT_AppConvertPdpStateToConnStatus(AT_AppGetPdpState(TAF_PDP_IPV4));

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d,\"IPV4\"",
                                       enIpv4ConnStatus);
#endif

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_TestApConnStPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-11)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}


VOS_UINT32 At_SetApThroughputPara(
    VOS_UINT8                           ucIndex
)
{
    AT_RNIC_DSFLOW_IND_STRU            *pstMsg;
    RNIC_RMNET_ID_ENUM_UINT8            enRnicRmNetId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucCid;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数过多 */
    if (gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ucCid = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* 获取对应的RNIC网卡 */
    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    enRnicRmNetId = (RNIC_RMNET_ID_ENUM_UINT8)pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;

    if (enRnicRmNetId >= RNIC_RMNET_ID_BUTT)
    {
        return AT_ERROR;
    }

    /* 申请ID_AT_RNIC_DSFLOW_IND消息 */
    pstMsg = (AT_RNIC_DSFLOW_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_DSFLOW_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_SetApThroughputPara: alloc msg fail!");
        return AT_ERROR;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_DSFLOW_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头 */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_DSFLOW_IND;
    pstMsg->clientId        = gastAtClientTab[ucIndex].usClientId;
    pstMsg->enRnicRmNetId   = enRnicRmNetId;

    /* 发ID_AT_RNIC_DSFLOW_IND消息给RNIC获取当前的流速 */
    if (VOS_OK == PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APTHROUGH_PUT_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        AT_WARN_LOG("At_SetApThroughputPara: Send msg failed!");
        return AT_ERROR;
    }
}


VOS_UINT32 At_QryApThroughputPara(
    VOS_UINT8                           ucIndex
)
{
    AT_RNIC_DSFLOW_IND_STRU            *pstMsg;

    /* 申请ID_AT_RNIC_DSFLOW_IND消息 */
    pstMsg = (AT_RNIC_DSFLOW_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_DSFLOW_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_QryApThroughputPara: alloc msg fail!");
        return AT_ERROR;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_DSFLOW_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头 */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_DSFLOW_IND;
    pstMsg->clientId        = gastAtClientTab[ucIndex].usClientId;
    pstMsg->enRnicRmNetId   = RNIC_RMNET_ID_0;

    /* 发ID_AT_RNIC_DSFLOW_IND消息给RNIC获取当前的流速 */
    if (VOS_OK == PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APTHROUGH_PUT_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        AT_WARN_LOG("At_QryApThroughputPara: Send msg failed!");
        return AT_ERROR;
    }
}


VOS_UINT32 AT_TestApThroughputPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-11)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}


VOS_UINT32 AT_SetApEndPppPara(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == FEATURE_AT_HSIC)
    AT_DCE_MSC_STRU                     stMscStru;
    VOS_UINT8                           ucActIndex;
    VOS_UINT8                           ucDlci;

    if (VOS_TRUE != AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /*模拟拉底DTR信号*/
    VOS_MemSet(&stMscStru, 0x00, sizeof(stMscStru));
    stMscStru.OP_Dtr = 1;
    stMscStru.ucDtr  = 0;

    /* HSIC MODEM索引号 */
    ucActIndex  = AT_CLIENT_TAB_HSIC_MODEM_INDEX;

    /*MODEM链路号 */
    ucDlci      = AT_MODEM_USER_DLCI;

    At_ModemMscInd(ucActIndex, ucDlci, &stMscStru);

    return AT_OK;
#else
    return AT_ERROR;
#endif
}


VOS_UINT32 AT_SetApDsFlowRptCfgPara(VOS_UINT8 ucIndex)
{
    TAF_APDSFLOW_RPT_CFG_STRU           stRptCfg;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 命令参数个数检查 */
    if ((gucAtParaIndex < 1) || (gucAtParaIndex > 4))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* AT^APDSFLOWRPTCFG=, */
    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 设置<enable> */
    stRptCfg.ulRptEnabled = gastAtParaList[0].ulParaValue;

    if (VOS_TRUE == stRptCfg.ulRptEnabled)
    {
        /* AT^APDSFLOWRPTCFG=1 */
        if (1 == gucAtParaIndex)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        /* AT^APDSFLOWRPTCFG=1, */
        if (0 == gastAtParaList[1].usParaLen)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        /* AT^APDSFLOWRPTCFG=1,<threshold> */
        stRptCfg.ulFluxThreshold = gastAtParaList[1].ulParaValue;

        /* AT^APDSFLOWRPTCFG=1,0 */
        if (0 == stRptCfg.ulFluxThreshold)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }
    else
    {
        /* AT^APDSFLOWRPTCFG=0 */
        stRptCfg.ulFluxThreshold = 0;
    }

    /* 执行命令操作 */
    if (VOS_OK != TAF_PS_SetApDsFlowRptCfg(WUEPS_PID_AT,
                                           gastAtClientTab[ucIndex].usClientId,
                                           0,
                                           &stRptCfg))
    {
        return AT_ERROR;
    }

    /* 设置当前操作类型 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APDSFLOWRPTCFG_SET;

    /* 返回命令处理挂起状态 */
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryApDsFlowRptCfgPara(VOS_UINT8 ucIndex)
{
    /* 执行命令操作 */
    if (VOS_OK != TAF_PS_GetApDsFlowRptCfg(WUEPS_PID_AT,
                                           gastAtClientTab[ucIndex].usClientId,
                                           0))
    {
        return AT_ERROR;
    }

    /* 设置当前操作类型 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APDSFLOWRPTCFG_QRY;

    /* 返回命令处理挂起状态 */
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_SetDsFlowNvWriteCfgPara(VOS_UINT8 ucIndex)
{
    TAF_DSFLOW_NV_WRITE_CFG_STRU        stWriteNvCfg;

    PS_MEM_SET(&stWriteNvCfg, 0x00, sizeof(TAF_DSFLOW_NV_WRITE_CFG_STRU));

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 命令参数个数检查 */
    if (gucAtParaIndex > 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* AT^DSFLOWNVWRCFG= */
    if (0 == gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* AT^DSFLOWNVWRCFG=,<interval> */
    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 获取<enable> */
    stWriteNvCfg.ucEnabled          = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* 获取<interval> */
    if (gucAtParaIndex > 1)
    {
        if (0 != gastAtParaList[1].usParaLen)
        {
            /* AT^DSFLOWNVWRCFG=<enable>,<interval> */
            stWriteNvCfg.ucInterval = (VOS_UINT8)gastAtParaList[1].ulParaValue;
        }
        else
        {
            /* AT^DSFLOWNVWRCFG=<enable>, */
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }
    else
    {
        /* AT^DSFLOWNVWRCFG=<enable> */
        stWriteNvCfg.ucInterval     = TAF_DEFAULT_DSFLOW_NV_WR_INTERVAL;
    }

    /* AT^DSFLOWNVWRCFG=1,0 */
    if ((VOS_TRUE == stWriteNvCfg.ucEnabled) && (0 == stWriteNvCfg.ucInterval))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 执行命令操作 */
    if (VOS_OK != TAF_PS_SetDsFlowNvWriteCfg(WUEPS_PID_AT,
                                             gastAtClientTab[ucIndex].usClientId,
                                             0,
                                             &stWriteNvCfg))
    {
        return AT_ERROR;
    }

    /* 设置当前操作类型 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DSFLOWNVWRCFG_SET;

    /* 返回命令处理挂起状态 */
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryDsFlowNvWriteCfgPara(VOS_UINT8 ucIndex)
{
    /* 执行命令操作 */
    if (VOS_OK != TAF_PS_GetDsFlowNvWriteCfg(WUEPS_PID_AT,
                                             gastAtClientTab[ucIndex].usClientId,
                                             0))
    {
        return AT_ERROR;
    }

    /* 设置当前操作类型 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DSFLOWNVWRCFG_QRY;

    /* 返回命令处理挂起状态 */
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_SetImsPdpCfg(VOS_UINT8 ucIndex)
{
    TAF_IMS_PDP_CFG_STRU                stImsPdpCfg;

    /* 参数过多 */
    if (gucAtParaIndex != 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数检查 */
    if ((0 == gastAtParaList[0].usParaLen)
     || (0 == gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_SET(&stImsPdpCfg, 0, sizeof(stImsPdpCfg));

    /* 参数赋值 */
    stImsPdpCfg.ucCid           = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    stImsPdpCfg.ucImsFlag       = (VOS_UINT8)gastAtParaList[1].ulParaValue;

    /* 发送跨核消息 */
    if ( VOS_OK != TAF_PS_SetImsPdpCfg(WUEPS_PID_AT,
                                       gastAtClientTab[ucIndex].usClientId,
                                       0,
                                       &stImsPdpCfg) )
    {
        return AT_ERROR;
    }

    /* 设置当前操作类型 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_IMSPDPCFG_SET;

    /* 返回命令处理挂起状态 */
    return AT_WAIT_ASYNC_RETURN;
}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
