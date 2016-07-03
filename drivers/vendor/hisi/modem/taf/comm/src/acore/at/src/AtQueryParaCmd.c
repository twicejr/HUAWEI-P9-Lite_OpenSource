

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "mdrv.h"
#include "PppInterface.h"
#include "TafDrvAgent.h"
#include "Taf_Tafm_Remote.h"
#include "TtfMemAtInterface.h"
#include "ATCmdProc.h"
#include "AtCheckFunc.h"
#include "AtParseCmd.h"
#include "AtPhyInterface.h"
#include "AtDataProc.h"
#include "AtCmdMsgProc.h"
#include "AtCheckFunc.h"
#include "AtSndMsg.h"
#include "AtRnicInterface.h"
#include "AtCheckFunc.h"
#include "AtInputProc.h"
#include "AtEventReport.h"
#include "AtDeviceCmd.h"


#include "BSP_SOCP_DRV.h"

#include "NasNvInterface.h"
#include "TafNvInterface.h"

#include "AtTafAgentInterface.h"
#include "AppVcApi.h"
#include "TafOamInterface.h"

#if (FEATURE_ON==FEATURE_LTE)
#include "msp_nvim.h"
#include "msp_nv_def.h"
#include "msp_nv_id.h"
#include "at_common.h"
#include "at_lte_common.h"
#endif

#include "CssAtInterface.h"

#include "AtMsgPrint.h"

#include "PsCommonDef.h"
#include "PsLib.h"
#include "product_config.h"
#include "TafAppCall.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 -e960 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_QUERYPARACMD_C
/*lint +e767 +e960 修改人:罗建 107747;检视人:sunshaohua*/


/*****************************************************************************
   2 全局变量定义
*****************************************************************************/

/*纪录查询错误码的类型*/
extern TAF_UINT32                       gulErrType;

extern VOS_UINT32                       g_ulWifiFreq;
extern VOS_UINT32                       g_ulWifiMode;
extern VOS_UINT32                       g_ulWifiRate;
extern VOS_UINT32                       g_lWifiPower;
extern VOS_UINT32                       g_ulUcastWifiRxPkts;
extern VOS_UINT32                       g_ulMcastWifiRxPkts;


/*****************************************************************************
   3 函数、变量声明
*****************************************************************************/

#if (VOS_WIN32 == VOS_OS_VER)
extern VOS_UINT8 NAS_GetPsRegContainDrx();
#endif
/*****************************************************************************
   4 函数实现
*****************************************************************************/


VOS_UINT32 At_QrySecuBootFeaturePara( VOS_UINT8 ucIndex )
{
    VOS_UINT8                          usSecBootSupportedFlag;

    usSecBootSupportedFlag = 0;

    /*调用底软接口*/
    if(MDRV_OK != mdrv_crypto_secboot_supported(&usSecBootSupportedFlag))
    {
        AT_WARN_LOG("At_QrySecuBootFeaturePara: get mdrv_crypto_secboot_supported() failed");
        return AT_ERROR;
    }


    /* 打印输出 */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            "%s: %d",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            usSecBootSupportedFlag);

    return AT_OK;
}


VOS_UINT32 At_QrySecuBootPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                 usSecBootStartedFlag;

    usSecBootStartedFlag = 0;

    if(MDRV_OK != mdrv_crypto_sec_started(&usSecBootStartedFlag))
    {
        AT_WARN_LOG("At_QrySecuBootPara: get mdrv_crypto_sec_started() failed");
        return AT_ERROR;
    }


    /* 打印输出 */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            "%s: %d",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            usSecBootStartedFlag);

     return AT_OK;
}


VOS_UINT32 AT_QryGTimerPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulGTimerLength;


    ulGTimerLength = 0;

    /* 读取NV项en_NV_Item_GPRS_ActiveTimerLength获取GPRS定时器时长 */
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_GPRS_ActiveTimerLength,
                    &ulGTimerLength,
                    sizeof(ulGTimerLength));
    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryGTimerPara: Fail to read en_NV_Item_GPRS_ActiveTimerLength");
        return AT_DEVICE_OTHER_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s:%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      ulGTimerLength);

    return AT_OK;
}


VOS_UINT32 AT_QryRsimPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                           ucCardStatus;
    VOS_UINT32                           ucCardType;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulGetModemIdRslt;
    AT_USIM_INFO_CTX_STRU              *pstUsimInfoCtx = VOS_NULL_PTR;

    enModemId = MODEM_ID_0;

    ulGetModemIdRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulGetModemIdRslt)
    {
        AT_ERR_LOG("At_SetCardModePara:Get Modem Id fail!");
        return AT_ERROR;
    }

    pstUsimInfoCtx = AT_GetUsimInfoCtxFromModemId(enModemId);

    /* 获取 SIM 卡类型和状态 */
    ucCardType   =  pstUsimInfoCtx->enCardType;
    ucCardStatus =  pstUsimInfoCtx->enCardStatus;

    AT_NORM_LOG1("AT_QryRsimPara: ucCardStatus is ", (VOS_INT32)ucCardStatus);
    AT_NORM_LOG1("AT_QryRsimPara: ucCardType is ",   (VOS_INT32)ucCardType);

    if (USIMM_CARD_SERVIC_BUTT == ucCardStatus)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          AT_RSIM_STATUS_USIMM_CARD_BUSY);
        return AT_OK;
    }

    /* 输出卡类型为USIMM_CARD_ROM_SIM指示当前为快速开机等效于无卡 */
    if ((USIMM_CARD_ROM_SIM == ucCardType)
     || (USIMM_CARD_SERVIC_ABSENT == ucCardStatus))
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          AT_RSIM_STATUS_USIMM_CARD_ABSENT);
    }
    else
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          AT_RSIM_STATUS_USIMM_CARD_AVAILABLE);
    }

    return AT_OK;
}


VOS_UINT32 AT_QryBatVolPara(VOS_UINT8 ucIndex)
{

    /*获取 电池电压值*/
    if (TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                             gastAtClientTab[ucIndex].opId,
                                             DRV_AGENT_TBATVOLT_QRY_REQ,
                                             VOS_NULL_PTR,
                                             0,
                                             I0_WUEPS_PID_DRV_AGENT))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_TBATVOLT_QRY;           /*设置当前操作模式 */
        return AT_WAIT_ASYNC_RETURN;                                            /* 等待异步事件返回 */
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 AT_DeciDigit2Ascii(
    VOS_UINT8                           aucDeciDigit[],
    VOS_UINT32                          ulLength,
    VOS_UINT8                           aucAscii[]
)
{
    VOS_UINT32                          ulLoop;

    for (ulLoop = 0; ulLoop < ulLength; ulLoop++)
    {
        if (aucDeciDigit[ulLoop] > 9)
        {
            return VOS_ERR;
        }

        aucAscii[ulLoop] = aucDeciDigit[ulLoop] + '0';
    }

    return VOS_OK;
}


VOS_VOID AT_ConvertImsiDigit2String(
    VOS_UINT8                          *pucImsi,
    VOS_UINT8                          *pucImsiString
)
{
    VOS_UINT8                           ucImsiLen;
    VOS_UINT32                          ulTempNum;
    VOS_UINT8                           aucImsiNum[NAS_IMSI_STR_LEN];
    VOS_UINT32                          i;

    PS_MEM_SET(aucImsiNum, 0, NAS_IMSI_STR_LEN);
    ulTempNum       = 0;
    ucImsiLen       = pucImsi[0];

    aucImsiNum[ulTempNum++] = (pucImsi[1] & 0xf0) >> 4;

    for (i = 2; i <= ucImsiLen; i++)
    {
        aucImsiNum[ulTempNum++] = pucImsi[i] & 0x0f;
        aucImsiNum[ulTempNum++] = (pucImsi[i] & 0xf0) >> 4;
    }

    /* 非'f'的IMSI号转换为字符 */
    i = 0;

    while ((0x0f != aucImsiNum[i])
        && (i < ulTempNum))
    {
        pucImsiString[i] = aucImsiNum[i] + '0';
        i++;
    }

    pucImsiString[i] = '\0';

    return;
}


VOS_UINT32 AT_GetPhynumMac(VOS_UINT8 aucMac[])
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucE5GwMacAddr[AT_MAC_ADDR_LEN + 1]; /* MAC地址*/
    VOS_UINT32                          ulE5GwMacAddrOffset;
    VOS_UINT32                          ulMacOffset;


    PS_MEM_SET(aucE5GwMacAddr, 0x00, sizeof(aucE5GwMacAddr));

    /* 获取MAC地址字符串 */
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_WIFI_MAC_ADDR, aucE5GwMacAddr, AT_MAC_ADDR_LEN);
    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_GetPhynumMac: Fail to read en_Nv_Item_Imei_Svn.");
        return AT_ERROR;
    }

    /* MAC地址格式匹配: 7A:FE:E2:21:11:E4=>7AFEE22111E4 */
    ulMacOffset         = 0;
    ulE5GwMacAddrOffset = 0;
    for (ulLoop = 0; ulLoop < (1 + AT_PHYNUM_MAC_COLON_NUM); ulLoop++)
    {
        PS_MEM_CPY(&aucMac[ulMacOffset],
                   &aucE5GwMacAddr[ulE5GwMacAddrOffset],
                   AT_WIFIGLOBAL_MAC_LEN_BETWEEN_COLONS);
        ulMacOffset         += AT_WIFIGLOBAL_MAC_LEN_BETWEEN_COLONS;
        ulE5GwMacAddrOffset += AT_WIFIGLOBAL_MAC_LEN_BETWEEN_COLONS + VOS_StrLen(":");
    }

    aucMac[AT_PHYNUM_MAC_LEN] = '\0';

    return AT_OK;
}


VOS_UINT32 AT_QryPhyNumPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucAsciiImei[TAF_PH_IMEI_LEN + 1];
    TAF_SVN_DATA_STRU                   stSvn;
    VOS_UINT8                           aucAsciiSvn[TAF_SVN_DATA_LENGTH + 1];
    VOS_UINT8                           aucMac[AT_PHYNUM_MAC_LEN + 1]; /* MAC地址*/
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;


    PS_MEM_SET(&stSvn, 0x00, sizeof(stSvn));


    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_QryPhyNumPara: Get modem id fail.");
        return AT_ERROR;
    }

    /* 读取NV项获取IMEI */
    ulRet = AT_GetImeiValue(enModemId, aucAsciiImei);

    if (VOS_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryPhyNumPara: Fail to read en_NV_Item_IMEI.");
        return AT_ERROR;
    }

    /* 读取NV项获取SVN */
    ulRet = NV_ReadEx(enModemId, en_NV_Item_Imei_Svn, &stSvn, sizeof(stSvn));
    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryPhyNumPara: Fail to read en_Nv_Item_Imei_Svn.");
        return AT_ERROR;
    }
    else
    {
        if (NV_ITEM_ACTIVE != stSvn.ucActiveFlag)
        {
            PS_MEM_SET(aucAsciiSvn, '0', TAF_SVN_DATA_LENGTH);
        }
        else
        {
            AT_DeciDigit2Ascii(stSvn.aucSvn, TAF_SVN_DATA_LENGTH, aucAsciiSvn);
        }

        aucAsciiSvn[TAF_SVN_DATA_LENGTH] = '\0';
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s:IMEI,%s%s",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      aucAsciiImei, gaucAtCrLf);

    if (BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        ulRet = AT_GetPhynumMac(aucMac);
        if (AT_OK != ulRet)
        {
            AT_WARN_LOG("AT_QryPhyNumPara: Fail to read en_NV_Item_IMEI.");
            return AT_ERROR;
        }

        /* MAC地址输出 */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s:MACWLAN,%s%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           aucMac,
                                           gaucAtCrLf);
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s:SVN,%s",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       aucAsciiSvn);


    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_WriteActiveMessage(
    MODEM_ID_ENUM_UINT16                enModemId,
    MN_MSG_ACTIVE_MESSAGE_STRU         *pstOrgActiveMessageInfo,
    MN_MSG_ACTIVE_MESSAGE_STRU         *pstActiveMessageInfo
)
{
    VOS_UINT32                          ulRet;
    VOS_INT32                           lRet;
    VOS_UINT8                          *pucActiveMessageInfo;
    VOS_UINT8                          *pucEvaluate;

    /*1.判断待写入的激活短信参数与NVIM中的参数是否一致；一致则不用写NVIM直接退出*/
    if (pstOrgActiveMessageInfo->enActiveStatus == pstActiveMessageInfo->enActiveStatus)
    {
        if (pstOrgActiveMessageInfo->stUrl.ulLen == pstActiveMessageInfo->stUrl.ulLen)
        {
            if (pstOrgActiveMessageInfo->enMsgCoding == pstActiveMessageInfo->enMsgCoding)
            {
                lRet = VOS_MemCmp(pstOrgActiveMessageInfo->stUrl.aucUrl,
                                  pstActiveMessageInfo->stUrl.aucUrl,
                                  pstActiveMessageInfo->stUrl.ulLen);
                if (0 == lRet)
                {
                    return MN_ERR_NO_ERROR;
                }
            }
        }
    }

    /*2.写激活短信参数到NVIM中*/
    /*2.1 为NVIM存储的数据流申请内存*/
    pucActiveMessageInfo = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_AT,
                                                     MN_MSG_ACTIVE_MESSAGE_PARA_LEN);
    if (VOS_NULL_PTR == pucActiveMessageInfo)
    {
        return MN_ERR_NOMEM;
    }

    /*2.2 将激活短信参数数据结构转换成NVIM存储的数据流*/
    pucEvaluate  = pucActiveMessageInfo;
    *pucEvaluate = pstActiveMessageInfo->enActiveStatus;
    pucEvaluate++;

    *pucEvaluate = pstActiveMessageInfo->enMsgCoding;
    pucEvaluate++;

    *pucEvaluate = (VOS_UINT8)(pstActiveMessageInfo->stUrl.ulLen & 0xff);
    pucEvaluate++;
    *pucEvaluate = (VOS_UINT8)((pstActiveMessageInfo->stUrl.ulLen >> 8) & 0xff);
    pucEvaluate++;
    *pucEvaluate = (VOS_UINT8)((pstActiveMessageInfo->stUrl.ulLen >> 16) & 0xff);
    pucEvaluate++;
    *pucEvaluate = (VOS_UINT8)((pstActiveMessageInfo->stUrl.ulLen >> 24) & 0xff);
    pucEvaluate++;

    PS_MEM_CPY(pucEvaluate,
               pstActiveMessageInfo->stUrl.aucUrl,
               (VOS_UINT16)pstActiveMessageInfo->stUrl.ulLen);

    /*2.3 写激活短信信息到NVIM*/
    ulRet = NV_WriteEx(enModemId,
                       en_NV_Item_SMS_ActiveMessage_Para,
                       pucActiveMessageInfo,
                       MN_MSG_ACTIVE_MESSAGE_PARA_LEN);
    if (NV_OK != ulRet)
    {
        ulRet = MN_ERR_CLASS_SMS_NVIM;
    }
    else
    {
        ulRet = MN_ERR_NO_ERROR;
    }

    PS_MEM_FREE(WUEPS_PID_AT, pucActiveMessageInfo);
    return ulRet;
}


TAF_UINT32 AT_QryRstriggerPara(
    TAF_UINT8                           ucIndex
)
{
    TAF_UINT32                          ulRet;
    TAF_UINT16                          usLength;
    MN_MSG_ACTIVE_MESSAGE_STRU          stActiveMessageInfo;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    usLength  = 0;
    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_SetRstriggerPara: Get modem id fail.");
        return AT_ERROR;
    }

    /*获取NVIM中记录的激活短信参数*/
    ulRet = AT_ReadActiveMessage(enModemId, &stActiveMessageInfo);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        AT_LOG1("AT_QryRstriggerPara: fail to get NVIM information, cause is %d",
                ulRet);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: 255,\"\"",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    else
    {
        if (MN_MSG_ACTIVE_MESSAGE_STATUS_ACTIVE != stActiveMessageInfo.enActiveStatus)
        {
            stActiveMessageInfo.enActiveStatus = MN_MSG_ACTIVE_MESSAGE_STATUS_DEACTIVE;
        }

        /*拼接响应字符串: 命令字，激活状态和URL信息*/
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: ",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "%d,\"",
                                            stActiveMessageInfo.enActiveStatus);

        usLength += (TAF_UINT16)At_PrintReportData(AT_CMD_MAX_LEN,
                                                   (TAF_INT8 *)pgucAtSndCodeAddr,
                                                   stActiveMessageInfo.enMsgCoding,
                                                   (pgucAtSndCodeAddr + usLength),
                                                   stActiveMessageInfo.stUrl.aucUrl,
                                                   (TAF_UINT16)stActiveMessageInfo.stUrl.ulLen);

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "\"");
    }

    gstAtSendData.usBufLen = usLength;
    return AT_OK;
}


TAF_UINT32 At_QryClipPara(TAF_UINT8 ucIndex)
{
    TAF_SS_INTERROGATESS_REQ_STRU para;

    /* 初始化 */
    PS_MEM_SET(&para,0x00,sizeof(para));

    /* 设置SsCode */
    para.SsCode = TAF_CLIP_SS_CODE;

    if(AT_SUCCESS == TAF_InterrogateSSReq(gastAtClientTab[ucIndex].usClientId, 0,&para))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLIP_READ;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */
    }
    else
    {
        return AT_ERROR;
    }
}

TAF_UINT32 At_QryClirPara(TAF_UINT8 ucIndex)
{
    TAF_SS_INTERROGATESS_REQ_STRU para;

    /* 初始化 */
    PS_MEM_SET(&para,0x00,sizeof(para));

    /* 设置SsCode */
    para.SsCode = TAF_CLIR_SS_CODE;

    if (TAF_InterrogateSSReq(gastAtClientTab[ucIndex].usClientId,
        0, &para) == TAF_SUCCESS)
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLIR_READ;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryColpPara(TAF_UINT8 ucIndex)
{
    TAF_SS_INTERROGATESS_REQ_STRU para;

    /* 初始化 */
    PS_MEM_SET(&para,0x00,sizeof(para));

    /* 设置SsCode */
    para.SsCode = TAF_COLP_SS_CODE;

    para.OP_BsService = 0;

    if(AT_SUCCESS == TAF_InterrogateSSReq(gastAtClientTab[ucIndex].usClientId, 0,&para))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_COLP_READ;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */
    }
    else
    {
        return AT_ERROR;
    }
}

TAF_UINT32 At_QryS0Para(TAF_UINT8 ucIndex)
{
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;

    pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen  = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%d",
                                                    pstCcCtx->stS0TimeInfo.ucS0TimerLen);
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_QryS3Para
 Description    :
 Input          : ucIndex --- 用户索引
 Output         :
 Return Value   : AT_XXX  --- ATC返回码
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryS3Para(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%03d",ucAtS3);
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_QryS4Para
 Description    :
 Input          : ucIndex --- 用户索引
 Output         :
 Return Value   : AT_XXX  --- ATC返回码
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryS4Para(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%03d",ucAtS4);
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_QryS5Para
 Description    :
 Input          : ucIndex --- 用户索引
 Output         :
 Return Value   : AT_XXX  --- ATC返回码
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryS5Para(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%03d",ucAtS5);
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_QryS6Para
 Description    :
 Input          : ucIndex --- 用户索引
 Output         :
 Return Value   : AT_XXX  --- ATC返回码
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-05-27
    Author      : L47619
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryS6Para(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%03d",ucAtS6);
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_QryS7Para
 Description    :
 Input          : ucIndex --- 用户索引
 Output         :
 Return Value   : AT_XXX  --- ATC返回码
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-05-27
    Author      : L47619
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryS7Para(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%03d",ucAtS7);
    return AT_OK;
}

TAF_UINT32 At_QryCusdPara(TAF_UINT8 ucIndex)
{
    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU     stAtCmd;
    VOS_UINT32                              ulResult;

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU));
    stAtCmd.enReqType       = AT_MTA_QRY_CUSD_RPT_TYPE;

    /* 给MTA发送+cusd查询请求 */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UNSOLICITED_RPT_READ;

    return AT_WAIT_ASYNC_RETURN;
}

TAF_UINT32 At_QryCcwaPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,"%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSsCtx->ucCcwaType);
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_QryCpinPara
 Description    :
 Input          : ucIndex --- 用户索引
 Output         :
 Return Value   : AT_XXX  --- ATC返回码
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  1.Date        : 2009-08-25
    Author      : h44270
    Modification: 问题单号：AT2D14070
*****************************************************************************/
TAF_UINT32 At_QryCpinPara(TAF_UINT8 ucIndex)
{
    TAF_PH_PIN_DATA_STRU stPinData;

    PS_MEM_SET(&stPinData,0x00,sizeof(stPinData));

    stPinData.CmdType = TAF_PIN_QUERY;

    stPinData.PinType = TAF_SIM_NON;


    if(AT_SUCCESS == Taf_PhonePinHandle(gastAtClientTab[ucIndex].usClientId, 0,&stPinData))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPIN_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


/*****************************************************************************
 Prototype      : At_QryIccidPara
 Description    : ^ICCID查询
 Input          : ucIndex --- 用户索引
 Output         :
 Return Value   : AT_WAIT_ASYNC_RETURN
                  AT_ERROR
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-08-27
    Author      : L47619
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryIccidPara(TAF_UINT8 ucIndex)
{
    /* 执行命令操作 */
    if(AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,0,TAF_PH_ICC_ID,TAF_NULL_PTR))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ICCID_READ;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryCardTypePara(TAF_UINT8 ucIndex)
{
    VOS_UINT32 ulResult;

    ulResult = SI_PIH_CardTypeQuery(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("SI_PIH_CardTypeQuery: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CARDTYPE_QUERY;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 At_QryPNNPara (TAF_UINT8 ucIndex)
{
#if 0
    VOS_UINT32                      ulFileExist;

    ulFileExist = USIMM_IsServiceAvailable(USIM_SVR_PLMN_NTWRK_NAME);
    if (PS_USIM_SERVICE_AVAILIABLE != ulFileExist)
    {
        return AT_ERROR;
    }

    return AT_OK;
#endif

    return AT_OK;
}


TAF_UINT32 At_QryCPNNPara (TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   DRV_AGENT_CPNN_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPNN_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryOPLPara (TAF_UINT8 ucIndex)
{
#if 0
    VOS_UINT32                      ulFileExist;

    ulFileExist = USIMM_IsServiceAvailable(USIM_SVR_OPLMN_LIST);
    if (PS_USIM_SERVICE_AVAILIABLE != ulFileExist)
    {
        return AT_ERROR;
    }

    return AT_OK;
#endif

    return AT_OK;

}

/*****************************************************************************
 Prototype      : At_QryCpinStatus
 Description    :
 Input          : ucIndex --- 用户索引
 Output         :
 Return Value   : AT_XXX  --- ATC返回码
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2007-09-29
    Author      : ---
    Modification: Created function by z100318
*****************************************************************************/
TAF_UINT32 At_QryCpinStatus(TAF_UINT8 ucIndex)
{
    TAF_PH_PIN_DATA_STRU stPinData;

    PS_MEM_SET(&stPinData,0x00,sizeof(stPinData));

    stPinData.CmdType = TAF_PIN_RemainTime;
    stPinData.PinType = TAF_SIM_NON;

    if(AT_SUCCESS == Taf_PhonePinHandle(gastAtClientTab[ucIndex].usClientId, 0,&stPinData))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPIN_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
/*****************************************************************************
 Prototype      : At_QryCardlockPara
 Description    :
 Input          : ucIndex --- 用户索引
 Output         :
 Return Value   : AT_XXX  --- ATC返回码
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2007-03-15
    Author      : luojian
    Modification: Created function by z100318
*****************************************************************************/
TAF_UINT32 At_QryCardlockPara(TAF_UINT8 ucIndex)
{
    TAF_ME_PERSONALISATION_DATA_STRU    stMePersonalisationData;

    PS_MEM_SET(&stMePersonalisationData, 0, sizeof(TAF_ME_PERSONALISATION_DATA_STRU));

    /* 安全命令类型为查询 */
    stMePersonalisationData.CmdType     = TAF_ME_PERSONALISATION_QUERY;
    /* 锁卡操作为锁网络 */
    stMePersonalisationData.MePersonalType = TAF_OPERATOR_PERSONALISATION;
    /* 执行命令操作 */
    if(AT_SUCCESS == Taf_MePersonalisationHandle(gastAtClientTab[ucIndex].usClientId, 0,&stMePersonalisationData))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CARD_LOCK_READ;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryCpin2Para(TAF_UINT8 ucIndex)
{
    TAF_PH_PIN_DATA_STRU stPinData;

    PS_MEM_SET(&stPinData,0x00,sizeof(stPinData));

    stPinData.CmdType = TAF_PIN2_QUERY;

    stPinData.PinType = TAF_SIM_NON;

    if(AT_SUCCESS == Taf_PhonePinHandle(gastAtClientTab[ucIndex].usClientId, 0,&stPinData))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPIN2_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

TAF_UINT32 At_QryCpbsPara(TAF_UINT8 ucIndex)
{
    gulPBPrintTag = VOS_TRUE;

    if(AT_SUCCESS == SI_PB_Query(gastAtClientTab[ucIndex].usClientId,0))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPBS_READ;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */
    }
    else
    {
        return AT_ERROR;
    }

}

TAF_UINT32 At_QryCfunPara(TAF_UINT8 ucIndex)
{
    if(VOS_TRUE == TAF_MMA_QryPhoneModeReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CFUN_READ;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryCpamPara(TAF_UINT8 ucIndex)
{
    if(VOS_TRUE == TAF_MMA_QryAccessModeReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPAM_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

TAF_UINT32 At_QryStsfPara(TAF_UINT8 ucIndex)
{
    USIMM_STK_CFG_STRU                  ProfileContent={0};
    TAF_UINT32                          Result ;
    TAF_UINT16                          NVLen = sizeof(USIMM_STK_CFG_STRU);
    TAF_UINT16                          Length = 0;
    MODEM_ID_ENUM_UINT16                usModemId;

    Result = NV_ReadEx(MODEM_ID_0, en_NV_Item_TerminalProfile_Set, &ProfileContent, NVLen);

    if(NV_OK != Result)
    {
        return AT_ERROR;
    }

    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &usModemId))
    {
        return AT_ERROR;
    }

    Length += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR*)pgucAtSndCodeAddr+Length,
                                                "^STSF:%d,",
                                                ProfileContent.ucFuncEnable);

    if (USIMM_CARD_USIM == AT_GetUsimInfoCtxFromModemId(usModemId)->enCardType)
    {
        Length += (TAF_UINT16)At_HexAlpha2AsciiString(AT_CMD_MAX_LEN,
                                                    (TAF_INT8 *)pgucAtSndCodeAddr,
                                                    (TAF_UINT8 *)pgucAtSndCodeAddr+Length,
                                                    ProfileContent.stUsimProfile.aucProfile,
                                                    ProfileContent.stUsimProfile.ucProfileLen);
    }
    else
    {
        Length += (TAF_UINT16)At_HexAlpha2AsciiString(AT_CMD_MAX_LEN,
                                                    (TAF_INT8 *)pgucAtSndCodeAddr,
                                                    (TAF_UINT8 *)pgucAtSndCodeAddr+Length,
                                                    ProfileContent.stSimProfile.aucProfile,
                                                    ProfileContent.stSimProfile.ucProfileLen);

    }

    Length += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr+Length,
                                                    ",%d",
                                                    ProfileContent.ucTimer);

    gstAtSendData.usBufLen = Length;

    return AT_OK;
}

/*****************************************************************************
 Prototype      : At_QryStgiPara
 Description    :
 Input          : ucIndex --- 用户索引
 Output         :
 Return Value   : AT_XXX  --- ATC返回码
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryStgiPara(TAF_UINT8 ucIndex)
{
    if(TAF_FALSE == g_ulSTKFunctionFlag)
    {
        return AT_ERROR;
    }

    if(AT_SUCCESS == SI_STK_QuerySTKCommand(gastAtClientTab[ucIndex].usClientId,USAT_CMDQRYSTGI))
    {
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryImsichgPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    if (VOS_FALSE == SI_STKIsDualImsiSupport())
    {
        return AT_CMD_NOT_SUPPORT;
    }

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   DRV_AGENT_IMSICHG_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_IMSICHG_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryCgclassPara(TAF_UINT8 ucIndex)
{
    VOS_UINT16                          usLength = 0;

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"\"A\"");

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

TAF_UINT32 At_QryCopsPara(TAF_UINT8 ucIndex)
{
    /* 放开CL模式下AT+COPS查询功能 */

    if(VOS_TRUE == TAF_MMA_QryCopsInfoReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_COPS_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 At_QryHplmnPara(VOS_UINT8 ucIndex)
{
    if(VOS_TRUE == TAF_MMA_QryApHplmnInfoReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_EHPLMN_LIST_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}


VOS_UINT32 AT_QryDplmnListPara(VOS_UINT8 ucIndex)
{
    if ( VOS_TRUE == TAF_MMA_QryDplmnListReq(WUEPS_PID_AT,
                                             gastAtClientTab[ucIndex].usClientId,
                                             0))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DPLMNLIST_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}



VOS_UINT32 At_QryCgcattPara(VOS_UINT8 ucIndex)
{


    /* AT给MMA模块发消息，要求MMA返回CS和PS的注册状态 */
    if (VOS_TRUE == TAF_MMA_AttachStatusQryReq(WUEPS_PID_AT,
                                               gastAtClientTab[ucIndex].usClientId,
                                               gastAtClientTab[ucIndex].opId,
                                               TAF_MMA_SERVICE_DOMAIN_CS_PS))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MMA_GET_CURRENT_ATTACH_STATUS;
        return AT_WAIT_ASYNC_RETURN;
    }
    return AT_ERROR;
}

VOS_UINT32 At_QryCgattPara(VOS_UINT8 ucIndex)
{


    /* AT给MMA模块发消息，要求MMA返回CS和PS的注册状态 */
    if (VOS_TRUE == TAF_MMA_AttachStatusQryReq(WUEPS_PID_AT,
                                               gastAtClientTab[ucIndex].usClientId,
                                               gastAtClientTab[ucIndex].opId,
                                               TAF_MMA_SERVICE_DOMAIN_PS))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MMA_GET_CURRENT_ATTACH_STATUS;
        return AT_WAIT_ASYNC_RETURN;
    }
    return AT_ERROR;
}


TAF_UINT32 AT_QryCgdnsPara(TAF_UINT8 ucIndex)
{
    /* 执行命令操作 */
    if ( VOS_OK != TAF_PS_GetPdpDnsInfo(WUEPS_PID_AT,
                                        gastAtClientTab[ucIndex].usClientId,
                                        0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDNS_READ;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 AT_QryCgautoPara(TAF_UINT8 ucIndex)
{
    /* 执行命令操作 */
    if ( VOS_OK != TAF_PS_GetAnsModeInfo(WUEPS_PID_AT,
                                         gastAtClientTab[ucIndex].usClientId,
                                         0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGAUTO_READ;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 AT_QryCgtftPara(TAF_UINT8 ucIndex)
{
    /* 执行命令操作 */
    if ( VOS_OK != TAF_PS_GetTftInfo(WUEPS_PID_AT,
                                     gastAtClientTab[ucIndex].usClientId,
                                     0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGTFT_READ;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 AT_QryCgactPara(TAF_UINT8 ucIndex)
{
    /* 执行命令操作 */
    if ( VOS_OK != TAF_PS_GetPdpContextState(WUEPS_PID_AT,
                                             gastAtClientTab[ucIndex].usClientId,
                                             0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGACT_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryCgdcontPara(VOS_UINT8 ucIndex)
{
    /* 执行命令操作 */
    if ( VOS_OK != TAF_PS_GetPrimPdpContextInfo(WUEPS_PID_AT,
                                                gastAtClientTab[ucIndex].usClientId,
                                                0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDCONT_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryCgeqreqPara(VOS_UINT8 ucIndex)
{
    /* 执行命令操作 */
    if ( VOS_OK != TAF_PS_GetUmtsQosInfo(WUEPS_PID_AT,
                                         gastAtClientTab[ucIndex].usClientId,
                                         0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGEQREQ_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 At_QryCgeqminPara(VOS_UINT8 ucIndex)
{
    /* 执行命令操作 */
    if ( VOS_OK != TAF_PS_GetUmtsQosMinInfo(WUEPS_PID_AT,
                                            gastAtClientTab[ucIndex].usClientId,
                                            0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGEQMIN_READ;

    return AT_WAIT_ASYNC_RETURN;
}

VOS_UINT32 AT_QryCgdscontPara(VOS_UINT8 ucIndex)
{
    /* 执行命令操作 */
    if ( VOS_OK != TAF_PS_GetSecPdpContextInfo(WUEPS_PID_AT,
                                               gastAtClientTab[ucIndex].usClientId,
                                               0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDSCONT_READ;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 At_QryCrcPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSsCtx->ucCrcType);
    return AT_OK;
}


TAF_UINT32 At_QryCbstPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d,%d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSsCtx->stCbstDataCfg.enSpeed,
                                                    pstSsCtx->stCbstDataCfg.enName,
                                                    pstSsCtx->stCbstDataCfg.enConnElem);

    return AT_OK;

}

TAF_UINT32 At_QryCmodPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSsCtx->enCModType);
    return AT_OK;
}


TAF_UINT32 At_QryCstaPara(TAF_UINT8 ucIndex)
{

    gstAtSendData.usBufLen  = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%s: %d",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,g_enAtCstaNumType);

    return AT_OK;
}


TAF_UINT32 At_QryCcugPara(TAF_UINT8 ucIndex)
{
    TAF_UINT16                          usLength = 0;
    TAF_UINT16                          usIndex;
    TAF_UINT16                          usInfo;
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    if (0 == pstSsCtx->stCcugCfg.bIndexPresent)
    {
        usIndex = 10;
    }
    else
    {
        usIndex = (TAF_UINT16)pstSsCtx->stCcugCfg.ulIndex;
    }

    usInfo = (TAF_UINT16)((pstSsCtx->stCcugCfg.bSuppressPrefer << 1) | pstSsCtx->stCcugCfg.bSuppressOA);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s: %d",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,pstSsCtx->stCcugCfg.bEnable);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,",%d",usIndex);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,",%d",usInfo);


    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


TAF_UINT32 At_QryCssnPara(TAF_UINT8 ucIndex)
{
    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU     stAtCmd;
    VOS_UINT32                              ulResult;

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU));
    stAtCmd.enReqType       = AT_MTA_QRY_CSSN_RPT_TYPE;

    /* 给MTA发送^cssn查询请求 */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UNSOLICITED_RPT_READ;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 At_QryCnmiPara(TAF_UINT8 ucIndex)
{
    TAF_UINT16                          usLength            = 0;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s: %d",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,pstSmsCtx->stCnmiType.CnmiModeType);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,",%d",pstSmsCtx->stCnmiType.CnmiMtType);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,",%d",pstSmsCtx->stCnmiType.CnmiBmType);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,",%d",pstSmsCtx->stCnmiType.CnmiDsType);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,",%d",pstSmsCtx->stCnmiType.CnmiBfrType);

    gstAtSendData.usBufLen = usLength;
    return AT_OK;
}


TAF_UINT32 At_QryCmgfPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)(pgucAtSndCodeAddr + gstAtSendData.usBufLen),
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSmsCtx->enCmgfMsgFormat);

    return AT_OK;
}


VOS_UINT32 At_QryCscaPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    MN_MSG_READ_COMM_PARAM_STRU         stReadParam;

    /*  设置要查询的短信中心号码存储位置 :
    AT模块获取短信中心号码等参数默认从SIM卡的EFSMSP文件的第一条记录中获取 */
    stReadParam.ulIndex     = 0;
    stReadParam.enMemStore  = MN_MSG_MEM_STORE_SIM;
    PS_MEM_SET(stReadParam.aucReserve1, 0x00, sizeof(stReadParam.aucReserve1));

    /* 发消息到C核获取短信中心号码 */
    gastAtClientTab[ucIndex].opId = At_GetOpId();
    ulRet = MN_MSG_ReadSrvParam(gastAtClientTab[ucIndex].usClientId,
                                gastAtClientTab[ucIndex].opId,
                                &stReadParam);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSCA_READ;
    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 At_QryCsmsPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)(pgucAtSndCodeAddr + gstAtSendData.usBufLen),
                                                    "%s: %d,",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSmsCtx->enCsmsMsgVersion);
    At_PrintCsmsInfo(ucIndex);
    return AT_OK;
}


TAF_UINT32 At_QryCsmpPara(TAF_UINT8 ucIndex)
{
    TAF_UINT16                          usLength            = 0;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;
    MN_MSG_VALID_PERIOD_ENUM_U8         enValidPeriod;                          /*TP Validity Period Format*/

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if (TAF_TRUE == pstSmsCtx->stCscaCsmpInfo.bFoUsed)
    {
        /* <fo> */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: %d,",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstSmsCtx->stCscaCsmpInfo.ucFo);

        AT_GET_MSG_TP_VPF(enValidPeriod, pstSmsCtx->stCscaCsmpInfo.ucFo);

        /* <vp> */
        if (enValidPeriod == pstSmsCtx->stCscaCsmpInfo.stVp.enValidPeriod)
        {
            usLength += At_MsgPrintVp(&(pstSmsCtx->stCscaCsmpInfo.stVp), (pgucAtSndCodeAddr + usLength));
        }

    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s: ,",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }

    /* <pid>  <dcs> */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                       ",%d,%d",
                                       pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucPid,
                                       pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucDcs);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

TAF_UINT32 At_QryCpmsPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if (AT_OK != At_GetSmsStorage(ucIndex,
                                  pstSmsCtx->stCpmsInfo.enMemReadorDelete,
                                  pstSmsCtx->stCpmsInfo.enMemSendorWrite,
                                  pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore))
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPMS_READ;
    return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */
}


TAF_UINT32 At_QryCgsmsPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)(pgucAtSndCodeAddr + gstAtSendData.usBufLen),
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSmsCtx->stCgsmsSendDomain.enSendDomain);

    return AT_OK;
}



TAF_UINT32 At_QryCmgdPara(TAF_UINT8 ucIndex)
{
    MN_MSG_LIST_PARM_STRU               stListPara;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    stListPara.bChangeFlag = VOS_FALSE;
    stListPara.enMemStore  = pstSmsCtx->stCpmsInfo.enMemReadorDelete;
    stListPara.enStatus    = MN_MSG_STATUS_NONE;
    PS_MEM_SET(stListPara.aucReserve1, 0x00, sizeof(stListPara.aucReserve1));

    gastAtClientTab[ucIndex].opId = At_GetOpId();
    if (MN_ERR_NO_ERROR == MN_MSG_Delete_Test(gastAtClientTab[ucIndex].usClientId,
                                         gastAtClientTab[ucIndex].opId,
                                         &stListPara))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMGD_TEST;
        g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryCmmsPara(
    TAF_UINT8                           ucIndex
)
{
    TAF_UINT32                          ulRet;

    gastAtClientTab[ucIndex].opId = At_GetOpId();
    ulRet = MN_MSG_GetLinkCtrl(gastAtClientTab[ucIndex].usClientId,
                               gastAtClientTab[ucIndex].opId);
    if (MN_ERR_NO_ERROR == ulRet)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMMS_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


VOS_UINT32 At_QryCscbPara(
    VOS_UINT8                           ucIndex
)
{
    TAF_UINT32                          ulRet;

    gastAtClientTab[ucIndex].opId = At_GetOpId();

    ulRet = MN_MSG_GetAllCbMids(gastAtClientTab[ucIndex].usClientId,
                             gastAtClientTab[ucIndex].opId);
    if (MN_ERR_NO_ERROR == ulRet)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSCB_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
#endif


TAF_UINT32 At_QryCgregPara(TAF_UINT8 ucIndex)
{
    if (VOS_TRUE == TAF_MMA_QryRegStateReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0, TAF_MMA_QRY_REG_STATUS_TYPE_PS))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGREG_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

#if(FEATURE_ON == FEATURE_LTE)

VOS_UINT32 At_QryCeregPara(VOS_UINT8 ucIndex)
{
    if (VOS_TRUE == TAF_MMA_QryRegStateReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0, TAF_MMA_QRY_REG_STATUS_TYPE_EPS))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CEREG_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

#endif

TAF_UINT32 At_QryCregPara(TAF_UINT8 ucIndex)
{
    if (VOS_TRUE == TAF_MMA_QryRegStateReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0, TAF_MMA_QRY_REG_STATUS_TYPE_CS))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CREG_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

TAF_UINT32 At_QryCsdhPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSmsCtx->ucCsdhType);

    return AT_OK;
}

TAF_UINT32 At_QryCscsPara(TAF_UINT8 ucIndex)
{
    if(AT_CSCS_IRA_CODE == gucAtCscsType)
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%s: \"IRA\"",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    else if (AT_CSCS_UCS2_CODE == gucAtCscsType)
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%s: \"UCS2\"",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    else
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%s: \"GSM\"",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    return AT_OK;
}


TAF_UINT32 At_QryCmeePara(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%s: %d",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,gucAtCmeeType);
    return AT_OK;
}


TAF_UINT32 At_QryParaCmd(TAF_UINT8 ucIndex)
{
    AT_RRETURN_CODE_ENUM_UINT32         ulResult = AT_FAILURE;

    if(TAF_NULL_PTR != g_stParseContext[ucIndex].pstCmdElement->pfnQryProc)
    {
        ulResult = (AT_RRETURN_CODE_ENUM_UINT32)g_stParseContext[ucIndex].pstCmdElement->pfnQryProc(ucIndex);

        if(AT_WAIT_ASYNC_RETURN == ulResult)
        {
            /* 开定时器 */
            if(AT_SUCCESS != At_StartTimer(g_stParseContext[ucIndex].pstCmdElement->ulQryTimeOut,ucIndex))
            {
                AT_ERR_LOG("At_QryParaCmd:ERROR:Start Timer");
                return AT_ERROR;
            }

            g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;
        }
        return ulResult;
    }
    else
    {
        return AT_ERROR;
    }
}



TAF_UINT32 At_QryFPlmnPara(TAF_UINT8 ucIndex)
{
    if (VOS_TRUE == TAF_MMA_QryFPlmnInfo(WUEPS_PID_AT,
                                         gastAtClientTab[ucIndex].usClientId,0))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CFPLMN_READ;           /*设置当前操作模式 */
        return AT_WAIT_ASYNC_RETURN;                                         /* 等待异步事件返回 */
    }
    else
    {
        return AT_ERROR;                    /* 错误返回 */

    }
}


VOS_UINT32 At_QryMaxFreelockSizePara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* 发消息到C核获取 MFREELOCKSIZE信息 */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_MFREELOCKSIZE_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("At_QryMaxFreelockSizePara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MFREELOCKSIZE_READ;
    return AT_WAIT_ASYNC_RETURN;


}


VOS_UINT32 At_QryCpuLoadPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* 发消息到C核获取 CPULOAD信息 */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_CPULOAD_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("At_QryCpuLoadPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPULOAD_READ;
    return AT_WAIT_ASYNC_RETURN;


}


VOS_UINT32 At_QryLcStartTimePara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                          *pucSystemAppConfig;

    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();



    if (SYSTEM_APP_WEBUI != *pucSystemAppConfig)
    {
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    g_ulLcStartTime);
    return AT_OK;

}


TAF_UINT32 At_QryDialModePara(TAF_UINT8 ucIndex)
{
    VOS_UINT8   ucDialmode;
    VOS_UINT8   ucCdcSpec;
    VOS_UINT32  ulRst;

    /* 调用底软接口，根据当前的设备形态来获取当前支持的拨号方式 */
    /* ucRst:       VOS_OK/VOS_ERR */
    /* ucDialmode:  0 - 使用Modem拨号; 1 - 使用NDIS拨号; 2 - Modem和NDIS共存 */
    /* ucCdcSpec:   0 - Modem/NDIS都符合CDC规范; 1 - Modem符合CDC规范;
                    2 - NDIS符合CDC规范;         3 - Modem/NDIS都符合CDC规范 */


    ucDialmode = 0;
    ucCdcSpec  = 0;

    ulRst = (VOS_UINT32)DRV_GET_DIAG_MODE_VALUE(&ucDialmode, &ucCdcSpec);

    if (VOS_OK != ulRst)
    {
        AT_ERR_LOG("At_QryDialModePara:ERROR:DRV_GET_DIAG_MODE_VALUE Return Err!");
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ucDialmode, ucCdcSpec);
    return AT_OK;
}



TAF_UINT32 At_QryPortSelPara(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen =
        (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                               (TAF_CHAR*)pgucAtSndCodeAddr,
                               (TAF_CHAR*)pgucAtSndCodeAddr,
                               "%s: %d",
                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                               gucAtPortSel);
    return AT_OK;
}


TAF_UINT32 At_QryCurcPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* AT 给MTA 发送CURC查询请求消息 */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_CURC_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("At_QryCurcPara: send Msg fail.");
        return AT_ERROR;
    }

    /* 设置当前操作类型 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CURC_READ;

    return AT_WAIT_ASYNC_RETURN;

}


TAF_UINT32 At_QryTimePara(TAF_UINT8 ucIndex)
{
    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU     stAtCmd;
    VOS_UINT32                              ulResult;

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU));
    stAtCmd.enReqType       = AT_MTA_QRY_TIME_RPT_TYPE;

    /* 给MTA发送^time查询请求 */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UNSOLICITED_RPT_READ;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 At_QryCtzrPara(TAF_UINT8 ucIndex)
{
    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU     stAtCmd;
    VOS_UINT32                              ulResult;

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU));
    stAtCmd.enReqType       = AT_MTA_QRY_CTZR_RPT_TYPE;

    /* 给MTA发送^ctzr查询请求 */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UNSOLICITED_RPT_READ;

    return AT_WAIT_ASYNC_RETURN;
}




VOS_UINT32 At_QryQuickStart(TAF_UINT8 ucIndex)
{
    if(VOS_TRUE == TAF_MMA_QryQuickStartReq(WUEPS_PID_AT,
                                            gastAtClientTab[ucIndex].usClientId,
                                            0))
    {
        /*设置当前操作模式 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CQST_READ;
        /* 等待异步事件返回 */
        return AT_WAIT_ASYNC_RETURN;
    }

    else
    {
        /* 错误返回 */
        return AT_ERROR;
    }
}

VOS_UINT32 At_QryAutoAttach(TAF_UINT8 ucIndex)
{
    if(VOS_TRUE == TAF_MMA_QryAutoAttachInfoReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CAATT_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 AT_QrySysCfgExPara(VOS_UINT8 ucIndex)
{
    if (VOS_TRUE == TAF_MMA_QrySyscfgReq(WUEPS_PID_AT,
                                         gastAtClientTab[ucIndex].usClientId,
                                         0))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SYSCFGEX_READ;             /*设置当前操作模式 */
        return AT_WAIT_ASYNC_RETURN;                                            /* 等待异步事件返回 */
    }
    else
    {
        return AT_ERROR;
    }

}




TAF_UINT32 At_QrySysCfgPara(TAF_UINT8 ucIndex)
{

    if (VOS_TRUE == TAF_MMA_QrySyscfgReq(WUEPS_PID_AT,
                                         gastAtClientTab[ucIndex].usClientId,
                                         0))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SYSCFG_READ;             /*设置当前操作模式 */
        return AT_WAIT_ASYNC_RETURN;                                            /* 等待异步事件返回 */
    }
    else
    {
        return AT_ERROR;
    }
}


#if(FEATURE_ON == FEATURE_LTE)

TAF_UINT32 At_QryCemode(TAF_UINT8 ucIndex)
{
    if (AT_SUCCESS == TAF_PS_GetCemodeInfo(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0))
    {

        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CEMODE_READ;             /*设置当前操作模式 */
        return AT_WAIT_ASYNC_RETURN;                                            /* 等待异步事件返回 */
    }
    else
    {
        (VOS_VOID)vos_printf(" At_QryCemode TAF_PS_GetCemodeInfo fail\n");
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryLtecsInfo(TAF_UINT8 ucIndex)
{

    if(AT_SUCCESS == TAF_PS_GetLteCsInfo(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_LTECS_READ;

        /* 返回命令处理挂起状态 */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
#endif

VOS_UINT32 At_QryClvlPara(VOS_UINT8 ucIndex)
{
    if (VOS_OK == APP_VC_GetVoiceVolume(gastAtClientTab[ucIndex].usClientId, 0))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLVL_READ;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 At_QryVMSETPara(VOS_UINT8 ucIndex)
{
    /* 不是查询命令返回参数错误 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*获取当前语音设备模式：0 手持；1 手持免提；2 车载免提；3 耳机；4 蓝牙；5 PC语音模式 */
    if (VOS_OK == APP_VC_GetVoiceMode(gastAtClientTab[ucIndex].usClientId, 0))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_VMSET_READ;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */
    }
    else
    {
        return AT_ERROR;
    }

}


TAF_UINT32 At_QryRRCVersion(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;


    /* 发送消息ID_AT_MTA_WRR_RRC_VERSION_QRY_REQ给AT代理处理 */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_WRR_RRC_VERSION_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_RRC_VERSION_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryCSNR(TAF_UINT8 ucIndex)
{
        /* 给MMA发送消息，查询新参数类型TAF_PH_CSNR_VALUE_PARA */
    if(VOS_TRUE == TAF_MMA_QryCsnrReq(WUEPS_PID_AT,
                                      gastAtClientTab[ucIndex].usClientId,
                                      0))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSNR_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}



TAF_UINT32 At_QryFreqLock(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;


    /* 发送消息ID_AT_MTA_WRR_FREQLOCK_QRY_REQ给AT代理处理 */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_WRR_FREQLOCK_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_FREQLOCK_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}



TAF_UINT32 At_QryU2DiagPara(TAF_UINT8 ucIndex)
{
    AT_USB_ENUM_STATUS_STRU             stUsbEnumStatus;
    AT_PID_ENABLE_TYPE_STRU             stPidEnableType;


    stPidEnableType.ulPidEnabled = VOS_FALSE;

    PS_MEM_SET(&stUsbEnumStatus, 0x00, sizeof(stUsbEnumStatus));


    /* 读取PID使能NV项 */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_PID_Enable_Type,
                        &stPidEnableType,
                        sizeof(AT_PID_ENABLE_TYPE_STRU)))
    {
        return AT_ERROR;
    }

    /* NV读取成功，检查PID是否使能，若使能，返回ERROR */
    if (VOS_FALSE != stPidEnableType.ulPidEnabled)
    {
        return AT_ERROR;
    }

    if(NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_USB_Enum_Status,
                         &stUsbEnumStatus,
                         sizeof(AT_USB_ENUM_STATUS_STRU)))
    {
        return AT_ERROR;
    }

    if (0 == stUsbEnumStatus.ulStatus)
    {
        /* 若en_NV_Item_USB_Enum_Status未设置，则调用底软的API来获取默认的USB设备形态 */
        stUsbEnumStatus.ulValue = DRV_GET_U2DIAG_DEFVALUE();
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stUsbEnumStatus.ulValue);
    return AT_OK;
}


VOS_UINT32 At_QryPort(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucCount;
    VOS_UINT32                          ulResult;
    DRV_DYNAMIC_PID_TYPE_STRU           stDynamicPidType;
    AT_PID_ENABLE_TYPE_STRU             stPidEnableType;

    usLength = 0;
    ucCount  = 0;


    stPidEnableType.ulPidEnabled = VOS_FALSE;


    PS_MEM_SET(&stDynamicPidType, 0x00, sizeof(DRV_DYNAMIC_PID_TYPE_STRU));

    /* 读取PID使能NV项 */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_PID_Enable_Type,
                        &stPidEnableType,
                        sizeof(AT_PID_ENABLE_TYPE_STRU)))
    {
        AT_ERR_LOG("At_QryPort:Read NV fail!");
        return AT_ERROR;
    }

    /* NV读取成功，检查PID是否使能，若不使能，返回ERROR */
    if (VOS_TRUE != stPidEnableType.ulPidEnabled)
    {
        AT_WARN_LOG("At_QryPort:The PID is not enabled!");
        return AT_ERROR;
    }

    /* 查询当前端口形态 */
    ulResult = DRV_SET_PORT_QUIRY(&stDynamicPidType);
    if (AT_SUCCESS != ulResult)
    {
        AT_ERR_LOG("At_QryPort:Qry the pot type fail!");
        return AT_ERROR;
    }

    /* ^SETPORT: */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    "%s:",
                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* OLD PORT */
    for (i = 0; i< AT_SETPORT_PARA_MAX_LEN; i++)
    {
        for (j = 0; j < AT_SETPORT_DEV_MAP_LEN; j++)
        {
            if (stDynamicPidType.aucFirstPortStyle[i] == g_astSetPortParaMap[j].ucDrvPara)
            {
                /* 大于1个参数的显示格式: */
                if (ucCount > 0)
                {
                    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                    ",");
                }

                /* 参数 */
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                "%s",
                                                g_astSetPortParaMap[j].aucAtSetPara);

                ucCount++;
                break;
            }
        }
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    ";");

    ucCount = 0;

    /* CUR PORT */
    for (i = 0; i< AT_SETPORT_PARA_MAX_LEN; i++)
    {
        for (j = 0; j < AT_SETPORT_DEV_LEN; j++)
        {
            if (stDynamicPidType.aucRewindPortStyle[i] == g_astSetPortParaMap[j].ucDrvPara)
            {
                /* 大于1个参数的显示格式: */
                if (ucCount > 0)
                {
                    /* 回车换行 */
                    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                    ",");
                }

                /* 参数 */
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                "%s",
                                                g_astSetPortParaMap[j].aucAtSetPara);

                ucCount++;

                break;
            }
        }
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


TAF_UINT32 At_QryPcscInfo(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulPortState;

    /*PCSC 口的开关状态, 0 打开; 1 关闭*/
    if (VOS_TRUE == AT_ExistSpecificPort(AT_DEV_PCSC))
    {
        ulPortState = VOS_TRUE;
    }
    else
    {
        ulPortState = VOS_FALSE;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ulPortState);
    return AT_OK;
}


VOS_UINT32 At_QryCellSearch(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* 发送消息 ID_AT_MTA_WRR_CELLSRH_QRY_REQ 给 DRV AGENT 处理， */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_MTA_WRR_CELLSRH_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_WAS_MNTN_QRY_CELLSRH;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


/*****************************************************************************
 Prototype      : At_QryGetportmodePara
 Description    :
 Input          : ucIndex --- 用户索引
 Output         :
 Return Value   : AT_XXX  --- ATC返回码
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-07-13
    Author      : S62952
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryGetportmodePara (TAF_UINT8 ucIndex)
{
     /*根据需求直接返回ERROR*/
     return AT_ERROR;
}


VOS_UINT32 At_QryCvoicePara (VOS_UINT8 ucIndex)
{
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*获取当前语音设备模式：0 手持；1 手持免提；2 车载免提；3 耳机；4 蓝牙 */
    if (VOS_OK == APP_VC_GetVoiceMode(gastAtClientTab[ucIndex].usClientId, 0))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CVOICE_READ;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */
    }
    else
    {
        return AT_ERROR;
    }

}



VOS_UINT32 At_QryDdsetexPara(VOS_UINT8 ucIndex)
{
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (VOS_OK == APP_VC_GetVoicePort(gastAtClientTab[ucIndex].usClientId, 0))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DDSETEX_READ;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryCmsrPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSmsCtx->ucParaCmsr);
    return AT_OK;
}



TAF_UINT32 At_QryUssdModePara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    /* 0：USSD非透传方案（即单板进行USSD字符编解码）1：USSD透传方案（即单板不进行USSD字符编解码，只是透传)*/
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSsCtx->usUssdTransMode);

    return AT_OK;
}


TAF_UINT32 At_QryAdcTempPara(TAF_UINT8 ucIndex)
{
    SPY_TEMP_PROTECT_NV_STRU stTempProtectNv;


    PS_MEM_SET(&stTempProtectNv, 0x00, sizeof(stTempProtectNv));


    /*读取热保护门限值的NV项*/
    if(NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_USIM_TEMP_PROTECT_NEW,
                        (VOS_VOID*)&stTempProtectNv,
                        sizeof(SPY_TEMP_PROTECT_NV_STRU)))
    {
        AT_ERR_LOG("Spy_SetTempPara: NV_ReadEx en_NV_Item_USIM_TEMP_PROTECT Fail!");

        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR*)pgucAtSndCodeAddr,
                                                "^ADCTEMP: %d,%d,%d,%d",
                                                stTempProtectNv.ulIsEnable,
                                                stTempProtectNv.lCloseAdcThreshold,
                                                stTempProtectNv.lAlarmAdcThreshold,
                                                stTempProtectNv.lResumeAdcThreshold);

    return AT_OK;
}


TAF_UINT32 At_QryCommDebugPara(TAF_UINT8 ucIndex)
{
    TAF_AT_NVIM_COMMDEGBUG_CFG_STRU     stDebugFlag;


    stDebugFlag.ulCommDebugFlag = 0;

    if(NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_COMMDEGBUG_CFG,
                        (VOS_VOID*)&(stDebugFlag.ulCommDebugFlag),
                        sizeof(TAF_AT_NVIM_COMMDEGBUG_CFG_STRU)))
    {
        AT_ERR_LOG("At_QryOamDebugPara: NV_ReadEx en_NV_Item_USIM_TEMP_PROTECT Fail!");

        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                "^COMM: 0x%X", stDebugFlag.ulCommDebugFlag);

    return AT_OK;
}


TAF_UINT32 At_QryDwinsPara(TAF_UINT8 ucIndex)
{
    WINS_CONFIG_STRU    stWins;
    VOS_UINT32          ulLength;

    ulLength = 0;


    PS_MEM_SET(&stWins, 0x00, sizeof(stWins));

    (VOS_VOID)NV_GetLength(en_NV_Item_WINS_Config, &ulLength);
    if(NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_WINS_Config, &stWins, ulLength))
    {
        return AT_ERROR;
    }

    if (0 == stWins.ucStatus)
    {
        /* 若en_NV_Item_WINS未设置，则默认WINS设置为使能 */
        stWins.ucWins = WINS_CONFIG_ENABLE;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stWins.ucWins);
    return AT_OK;
}


TAF_UINT32 At_QryYjcxPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;


    /* 发送DRV_AGENT_YJCX_QRY_REQ消息给AT代理处理 */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   DRV_AGENT_YJCX_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (VOS_OK == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_YJCX_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}


VOS_UINT32 At_QryCplsPara(VOS_UINT8 ucIndex)
{
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstNetCtx->enPrefPlmnType);

    return AT_OK;

}


TAF_UINT32 At_QryCpolPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    TAF_MMA_CPOL_INFO_QUERY_REQ_STRU    stCpolInfo;

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /*
    AT向MMA请求运营商信息:
    因为核间消息限制，不能一次获取所有运营商信息，这里定义为一次获取37条运营商信息
    第一条请求消息，从索引0开始要求连续的37条运营商信息
    */
    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    PS_MEM_SET(&stCpolInfo, 0, sizeof(stCpolInfo));

    stCpolInfo.enPrefPLMNType   = pstNetCtx->enPrefPlmnType;
    stCpolInfo.ulFromIndex      = 0;

    stCpolInfo.ulPlmnNum        = TAF_MMA_MAX_PLMN_NAME_LIST_NUM;

    /* 向MMA发消息请求运营商信息 */
    ulRet = TAF_MMA_QueryCpolReq(WUEPS_PID_AT,
                                 gastAtClientTab[ucIndex].usClientId,
                                 0,
                                 &stCpolInfo);
    if (VOS_TRUE != ulRet)
    {
        return AT_ERROR;
    }


    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPOL_READ;

    return AT_WAIT_ASYNC_RETURN;

}


TAF_UINT32 AT_QryAuthdataPara(TAF_UINT8 ucIndex)
{
    if ( VOS_OK != TAF_PS_GetAuthDataInfo(WUEPS_PID_AT,
                                          gastAtClientTab[ucIndex].usClientId,
                                          0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHDATA_READ;

    return AT_WAIT_ASYNC_RETURN;
}


#if (FEATURE_ON == FEATURE_IPV6)


VOS_UINT32 AT_QryIpv6CapPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucIpv6Capability;

    switch (AT_GetIpv6Capability())
    {
        case AT_IPV6_CAPABILITY_IPV4_ONLY:
            ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY;
            break;

        case AT_IPV6_CAPABILITY_IPV6_ONLY:
            ucIpv6Capability = AT_IPV6_CAPABILITY_IPV6_ONLY;
            break;

        case AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP:
            ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY
                               + AT_IPV6_CAPABILITY_IPV6_ONLY
                               + AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP;
            break;

        case AT_IPV6_CAPABILITY_IPV4V6_OVER_TWO_PDP:
            ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY
                               + AT_IPV6_CAPABILITY_IPV6_ONLY
                               + AT_IPV6_CAPABILITY_IPV4V6_OVER_TWO_PDP;
            break;

        default:
            ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY;
            break;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     ucIpv6Capability);
    return AT_OK;
}
#endif

/*****************************************************************************
 Prototype      : At_QryCrpnPara
 Description    : ^CRPN?
 Input          : ucIndex --- 用户索引
 Output         :
 Return Value   :
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-09-01
    Author      : L47619
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryCrpnPara(TAF_UINT8 ucIndex)
{
    return AT_OK;
}


VOS_UINT32 AT_QryAlsPara( TAF_UINT8 ucIndex )
{
    VOS_UINT32                          ulRst;
    MN_CALL_APP_REQ_ENUM_UINT32         usMsg;

    usMsg                           = MN_CALL_APP_QRY_ALS_REQ;
    gastAtClientTab[ucIndex].opId   = At_GetOpId();

    /*发送TAF_CS_ALS_LINE_NO_QRY消息给TAF，由TAF返回当前的线路号。*/
    ulRst = MN_CALL_SendAppRequest(usMsg,
                                   gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   0,
                                   VOS_NULL_PTR);
    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APP_QRY_ALS_REQ;
        return AT_WAIT_ASYNC_RETURN;
    }
    return AT_ERROR;
}


VOS_VOID At_CovertMsInternalRxDivParaToUserSet(
                    VOS_UINT16 usCurBandSwitch,
                    VOS_UINT32 *pulUserDivBandsLow,
                    VOS_UINT32 *pulUserDivBandsHigh
                    )
{
    *pulUserDivBandsLow      = 0;
    *pulUserDivBandsHigh     = 0;

    /*用户设置的接收分集格式如下:
        0x80000            GSM850
        0x300              GSM900
        0x80               DCS1800
        0x200000           PCS1900
        0x400000           WCDMA2100
        0x800000           WCDMA1900
        0x1000000          WCDMA1800
        0x2000000          WCDMA_AWS
        0x4000000          WCDMA850
        0x2000000000000    WCDMA900
        0x4000000000000    WCDMA1700
      而MS支持的接收分集格式如下:
        2100M/ bit1  1900M/bit2  1800M/bit3  1700M/bit4  1600M/bit5
        1500M/bit6   900M/bit7   850M/bit8   800M/bit9   450M/bit10
      需要把用户设置的接收分集转换成MS支持的格式
    */
    if (0 != (usCurBandSwitch & AT_MS_SUPPORT_RX_DIV_900))
    {
        *pulUserDivBandsHigh |= TAF_PH_BAND_WCDMA_VIII_900;
    }
    if (0 != (usCurBandSwitch & AT_MS_SUPPORT_RX_DIV_IX_1700))
    {
        *pulUserDivBandsHigh |= TAF_PH_BAND_WCDMA_IX_1700;
    }
    if (0 != (usCurBandSwitch & AT_MS_SUPPORT_RX_DIV_2100))
    {
        *pulUserDivBandsLow |= TAF_PH_BAND_WCDMA_I_IMT_2100;
    }
    if (0 != (usCurBandSwitch & AT_MS_SUPPORT_RX_DIV_1900))
    {
        *pulUserDivBandsLow |= TAF_PH_BAND_WCDMA_II_PCS_1900;
    }
    if (0 != (usCurBandSwitch & AT_MS_SUPPORT_RX_DIV_1800))
    {
        *pulUserDivBandsLow |= TAF_PH_BAND_WCDMA_III_1800;
    }
    if (0 != (usCurBandSwitch & AT_MS_SUPPORT_RX_DIV_850))
    {
        *pulUserDivBandsLow |= TAF_PH_BAND_WCDMA_V_850;
    }

    return;
}


VOS_UINT32 At_QryFrssiPara(
    VOS_UINT8                           ucIndex
)
{
    AT_HPA_RF_RX_RSSI_REQ_STRU          *pstMsg;
    VOS_UINT32                          ulLength;

#if(FEATURE_LTE == FEATURE_ON)
    if ((AT_RAT_MODE_FDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode)
      ||(AT_RAT_MODE_TDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        return atQryFRSSIPara(ucIndex);
    }
#endif

#if(FEATURE_UE_MODE_TDS == FEATURE_ON)
    if(AT_RAT_MODE_TDSCDMA == g_stAtDevCmdCtrl.ucDeviceRatMode)
    {
        return atQryFRSSIPara(ucIndex);
    }

#endif

    /*该命令需在非信令模式下使用*/
    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /*该命令需在设置非信令信道后使用*/
    if (VOS_FALSE == g_stAtDevCmdCtrl.bDspLoadFlag)
    {
        return AT_CHANNEL_NOT_SET;
    }

    /*该命令需要在打开接收机后使用*/
    if (AT_DSP_RF_SWITCH_OFF == g_stAtDevCmdCtrl.ucRxOnOff)
    {
        return AT_FRSSI_RX_NOT_OPEN;
    }

    /* GDSP LOAD的情况下不支持接收机和发射机同时打开，需要判断最近一次执行的是打开接收机操作
    还是打开发射机操作，如果是打开发射机操作，则直接返回出错无需和GDSP 交互 */
    if ((AT_TXON_OPEN == g_stAtDevCmdCtrl.ucRxonOrTxon)
     && ((AT_RAT_MODE_GSM == g_stAtDevCmdCtrl.ucDeviceRatMode)
      || (AT_RAT_MODE_EDGE == g_stAtDevCmdCtrl.ucDeviceRatMode)))
    {
        return AT_FRSSI_OTHER_ERR;
    }

    /* 申请AT_HPA_RF_RX_RSSI_REQ_STRU消息 */
    ulLength = sizeof(AT_HPA_RF_RX_RSSI_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (AT_HPA_RF_RX_RSSI_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_QryFrssiPara: alloc msg fail!");
        return AT_FRSSI_OTHER_ERR;
    }

    if ((AT_RAT_MODE_GSM == g_stAtDevCmdCtrl.ucDeviceRatMode)
     || (AT_RAT_MODE_EDGE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        pstMsg->ulReceiverPid = AT_GetDestPid(ucIndex, I0_DSP_PID_GPHY);
        pstMsg->usMsgID       = ID_AT_GHPA_RF_RX_RSSI_REQ;
    }
    else
    {
        pstMsg->ulReceiverPid = DSP_PID_WPHY;
        pstMsg->usMsgID       = ID_AT_HPA_RF_RX_RSSI_REQ;
    }

    pstMsg->usMeasNum  = AT_DSP_RSSI_MEASURE_NUM;
    pstMsg->usInterval = AT_DSP_RSSI_MEASURE_INTERVAL;
    pstMsg->usRsv      = 0;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("At_QryFrssiPara: Send msg fail!");
        return AT_FRSSI_OTHER_ERR;
    }

    /* 设置当前操作类型 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_QUERY_RSSI;
    g_stAtDevCmdCtrl.ucIndex               = ucIndex;

    return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */

}


VOS_UINT32 At_QryRxDiv(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* 发送消息DRV_AGENT_HARDWARE_QRY给DRV AGENT处理，该消息无参数结构 */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_RXDIV_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DRV_AGENT_RXDIV_QRY_REQ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;

}


VOS_UINT32 At_QryCuus1Para(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulRst;
    MN_CALL_APP_REQ_ENUM_UINT32         ucMsg;

    ucMsg = MN_CALL_APP_QRY_UUSINFO_REQ;

    ulRst = MN_CALL_SendAppRequest(ucMsg,
                                   gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   0,
                                   VOS_NULL_PTR);
    if (MN_ERR_NO_ERROR == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APP_SET_UUSINFO_REQ;
        return AT_WAIT_ASYNC_RETURN;
    }
    return AT_ERROR;
}


VOS_UINT32 At_QryApHplmn( VOS_UINT8  ucIndex )
{
    if(VOS_TRUE == TAF_MMA_QryApHplmnInfoReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HOMEPLMN_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

VOS_UINT32 AT_QryAnQuery( VOS_UINT8 ucIndex )
{
    if(VOS_TRUE == TAF_MMA_QryAntennaInfoReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ANQUERY_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


AT_CMD_ANTENNA_LEVEL_ENUM_UINT8 AT_CalculateAntennaLevel(
    VOS_INT16                           sRscp,
    VOS_INT16                           sEcio
)
{
    VOS_UINT16                          usRscp;
    VOS_UINT16                          usEcio;
    AT_CMD_ANTENNA_LEVEL_ENUM_UINT8     enRlstAntennaLevel;

/* RSCP and ECIO different Thresholds variables */
   VOS_INT32                            alRscpThreshold[AT_ANTEN_LEV_MAX_NUM] = {125, 108, 102, 96} ;
   VOS_INT32                            alEcioThreshold[AT_ANTEN_LEV_MAX_NUM] = {30, 16, 13, 10};

#if(FEATURE_ON == FEATURE_LTE)

    VOS_UINT8                          *pucSystemAppConfig;
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    if ( SYSTEM_APP_WEBUI == *pucSystemAppConfig)
    {
        /* 取绝对值 */
        usRscp                    = (VOS_UINT16)-sRscp;
        usEcio                    = (VOS_UINT16)-sEcio;

        /* 3 level of Signal */
        if ( (usEcio <= g_stEcioCfg.ssValue[3])
          && (usRscp <= g_stRscpCfg.ssValue[3]))
        {
            enRlstAntennaLevel = AT_CMD_ANTENNA_LEVEL_4;
        }
        /* 2 level of Signal */
        else if (((usEcio <= g_stEcioCfg.ssValue[2]) && (usEcio > g_stEcioCfg.ssValue[3])
               && (usRscp <= g_stRscpCfg.ssValue[2]))
              || ((usRscp <= g_stRscpCfg.ssValue[2]) && (usRscp > g_stRscpCfg.ssValue[3])
               && (usEcio < g_stEcioCfg.ssValue[2])))
        {
            enRlstAntennaLevel  = AT_CMD_ANTENNA_LEVEL_3;
        }
        /* 1 level of Signal */
        else if (((usEcio <= g_stEcioCfg.ssValue[1]) && (usEcio > g_stEcioCfg.ssValue[2])
               && (usRscp <= g_stRscpCfg.ssValue[1]))
              || ((usRscp <= g_stRscpCfg.ssValue[1]) && (usRscp > g_stRscpCfg.ssValue[2])
               && (usEcio < g_stEcioCfg.ssValue[1])))
        {
            enRlstAntennaLevel  = AT_CMD_ANTENNA_LEVEL_2;
        }
        else
        {
            enRlstAntennaLevel  = AT_CMD_ANTENNA_LEVEL_1;
        }
        return enRlstAntennaLevel;
    }
#endif

    enRlstAntennaLevel        = 0;

    /* 取绝对值 */
    usRscp                    = (VOS_UINT16)-sRscp;
    usEcio                    = (VOS_UINT16)-sEcio;

    /* 3 level of Signal */
    if ( (usEcio <= alEcioThreshold[3])
      && (usRscp <= alRscpThreshold[3]))
    {
        enRlstAntennaLevel = AT_CMD_ANTENNA_LEVEL_4;
    }
    /* 2 level of Signal */
    else if (((usEcio <= alEcioThreshold[2]) && (usEcio > alEcioThreshold[3])
           && (usRscp <= alRscpThreshold[2]))
          || ((usRscp <= alRscpThreshold[2]) && (usRscp > alRscpThreshold[3])
           && (usEcio < alEcioThreshold[2])))
    {
        enRlstAntennaLevel  = AT_CMD_ANTENNA_LEVEL_3;
    }
    /* 1 level of Signal */
    else if (((usEcio <= alEcioThreshold[1]) && (usEcio > alEcioThreshold[2])
           && (usRscp <= alRscpThreshold[1]))
          || ((usRscp <= alRscpThreshold[1]) && (usRscp > alRscpThreshold[2])
           && (usEcio < alEcioThreshold[1])))
    {
        enRlstAntennaLevel  = AT_CMD_ANTENNA_LEVEL_2;
    }
    else
    {
        enRlstAntennaLevel  = AT_CMD_ANTENNA_LEVEL_1;
    }

    return enRlstAntennaLevel;

}

VOS_VOID AT_GetSmoothAntennaLevel(
    VOS_UINT8                           ucIndex,
    AT_CMD_ANTENNA_LEVEL_ENUM_UINT8     enLevel
)
{
    VOS_UINT8                               i;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    /* 丢网时 立即更新  */
    if ( AT_CMD_ANTENNA_LEVEL_0 == enLevel )
    {
        pstNetCtx->enCalculateAntennaLevel = enLevel;

        PS_MEM_SET( pstNetCtx->aenAntennaLevel, 0, sizeof(pstNetCtx->aenAntennaLevel) );
        return;
    }

    /* 丢网到有服务状态  立即更新  */
    if ( AT_CMD_ANTENNA_LEVEL_0 == pstNetCtx->enCalculateAntennaLevel )
    {
        pstNetCtx->enCalculateAntennaLevel = enLevel;

        PS_MEM_SET( pstNetCtx->aenAntennaLevel, 0, sizeof(pstNetCtx->aenAntennaLevel) );
        pstNetCtx->aenAntennaLevel[AT_ANTENNA_LEVEL_MAX_NUM-1] = enLevel;
        return;
    }

    /* 与上次的信号格数比较, 变化比较大(超过1格)就立即更新 */
    if ( enLevel > (pstNetCtx->aenAntennaLevel[AT_ANTENNA_LEVEL_MAX_NUM-1] + 1) )
    {
        pstNetCtx->enCalculateAntennaLevel = enLevel;

        PS_MEM_SET( pstNetCtx->aenAntennaLevel, 0, sizeof(pstNetCtx->aenAntennaLevel) );
        pstNetCtx->aenAntennaLevel[AT_ANTENNA_LEVEL_MAX_NUM-1] = enLevel;
        return;
    }
    else if (( enLevel + 1) < pstNetCtx->aenAntennaLevel[AT_ANTENNA_LEVEL_MAX_NUM-1] )
    {
        pstNetCtx->enCalculateAntennaLevel = enLevel;

        PS_MEM_SET( pstNetCtx->aenAntennaLevel, 0, sizeof(pstNetCtx->aenAntennaLevel) );
        pstNetCtx->aenAntennaLevel[AT_ANTENNA_LEVEL_MAX_NUM-1] = enLevel;
        return;
    }
    else
    {
      /* Do nothing... */
    }


    /* 先进先出存最近3次的查询结果 */
    for ( i=0; i<AT_ANTENNA_LEVEL_MAX_NUM-1; i++ )
    {
         pstNetCtx->aenAntennaLevel[i] = pstNetCtx->aenAntennaLevel[i+1];
    }
    pstNetCtx->aenAntennaLevel[i] = enLevel;


    /* 格数波动则不更新，以达到平滑的效果 */
    for ( i=0; i<AT_ANTENNA_LEVEL_MAX_NUM; i++ )
    {
        if ( pstNetCtx->enCalculateAntennaLevel == pstNetCtx->aenAntennaLevel[i] )
        {
            return;
        }
    }

    /* 信号格数稳定了 AT_ANTENNA_LEVEL_MAX_NUM 次时才做更新 */
    pstNetCtx->enCalculateAntennaLevel = enLevel;
}


#if (FEATURE_LTE == FEATURE_ON)

TAF_VOID AT_CalculateLTESignalValue(
                                              VOS_INT16    *psRssi,
                                              VOS_UINT8    *pusLevel,
                                              VOS_INT16    *psRsrp,
                                              VOS_INT16    *psRsrq

)
{
        VOS_UINT8                           enCurAntennaLevel;
        VOS_INT16                           sRsrp;
        VOS_INT16                           sRsrq;

        /* 与 atSetAnlevelCnfSameProc处理相同*/
        /* 上报数据转换:将 Rscp、Ecio显示为非负值，若Rscp、Ecio为-145，-32，或者rssi为99，
        则转换为0 */
        if ( (TAF_PH_RSSIUNKNOW == *psRsrp)
          || (TAF_PH_RSSIUNKNOW == *psRssi) )
        {
            /* 丢网返回0, 对应应用的圈外 */
            enCurAntennaLevel       = AT_CMD_ANTENNA_LEVEL_0;
        }
        else
        {
            /* 取绝对值 */
            sRsrp            = (-(*psRsrp));

            /* 调用函数AT_CalculateAntennaLevel来根据D25算法计算出信号格数 */
            enCurAntennaLevel = AT_CalculateLTEAntennaLevel((VOS_INT16)(sRsrp));
        }

        /* 信号磁滞处理 */
        *pusLevel = AT_GetSmoothLTEAntennaLevel(enCurAntennaLevel);



        if(AT_RSSI_UNKNOWN == *psRssi)
        {
            *psRssi = AT_RSSI_UNKNOWN;
        }
        else if(*psRssi >= AT_RSSI_HIGH)
        {
            *psRssi = AT_CSQ_RSSI_HIGH;
        }
        else if(*psRssi <= AT_RSSI_LOW)
        {
            *psRssi = AT_CSQ_RSSI_LOW;
        }
        else
        {
            *psRssi = ( VOS_INT16)((*psRssi - AT_RSSI_LOW) / 2);
        }

        sRsrp = (*psRsrp == 99)?99:(-(*psRsrp));
        sRsrq = (*psRsrq == 99)?99:(-(*psRsrq));

        *psRsrp = sRsrp;
        *psRsrq = sRsrq;

        return;

}
#endif

#if defined (DMT)

#define AT_ANTENNA_LEVEL_NUM        3
VOS_UINT8         g_ATAntennaLevel[AT_ANTENNA_LEVEL_NUM];
VOS_UINT8         g_ulAntennaLevel = 0;

VOS_UINT32       g_ATE5Order = 0;

VOS_UINT8 AT_CalculateLTEAntennaLevel(
    VOS_INT16                           usRsrp
)
{
    VOS_INT16 usLevel = 0;
       g_ATE5Order =4;
    /*天线格式显示规则
 */
    if ( usRsrp <= g_stRsrpCfg.ssValue[3])
    {
        usLevel = AT_CMD_ANTENNA_LEVEL_4;
    }
    else if (( g_stRsrpCfg.ssValue[3] < usRsrp) && (usRsrp <= g_stRsrpCfg.ssValue[2]))
    {
        usLevel = AT_CMD_ANTENNA_LEVEL_3;
    }
    else if (( g_stRsrpCfg.ssValue[2] < usRsrp) && (usRsrp <= g_stRsrpCfg.ssValue[1]))
    {
        usLevel = AT_CMD_ANTENNA_LEVEL_2;
    }
    else
    {
        usLevel = AT_CMD_ANTENNA_LEVEL_1;
    }
    return (VOS_UINT8)usLevel;

}

VOS_UINT8 AT_GetSmoothLTEAntennaLevel(
    AT_CMD_ANTENNA_LEVEL_ENUM_UINT8     enLevel
)
{
    VOS_UINT8                               i;
    g_ATE5Order =5;
    /* 丢网时 立即更新  */
    if ( AT_CMD_ANTENNA_LEVEL_0 == enLevel )
    {
        g_ulAntennaLevel = enLevel;

        MSP_MEMSET( g_ATAntennaLevel, 0, sizeof(g_ATAntennaLevel) );
        return g_ulAntennaLevel;
    }

    /* 丢网到有服务状态  立即更新  */
    if ( AT_CMD_ANTENNA_LEVEL_0 == g_ulAntennaLevel )
    {
        g_ulAntennaLevel = enLevel;

        MSP_MEMSET( g_ATAntennaLevel, 0, sizeof(g_ATAntennaLevel) );
        g_ATAntennaLevel[AT_ANTENNA_LEVEL_NUM-1] = enLevel;
        return g_ulAntennaLevel;
    }

    /* 与上次的信号格数比较, 变化比较大(超过1格)就立即更新 */
    if ( enLevel > (g_ulAntennaLevel + 1) )
    {
        g_ulAntennaLevel = enLevel;

        MSP_MEMSET( g_ATAntennaLevel, 0, sizeof(g_ATAntennaLevel) );
        g_ATAntennaLevel[AT_ANTENNA_LEVEL_NUM-1] = enLevel;
        return g_ulAntennaLevel;
    }
    else if (( enLevel + 1) < g_ulAntennaLevel )
    {
        g_ulAntennaLevel = enLevel;

        MSP_MEMSET( g_ATAntennaLevel, 0, sizeof(g_ATAntennaLevel) );
        g_ATAntennaLevel[AT_ANTENNA_LEVEL_NUM-1] = enLevel;
        return g_ulAntennaLevel;
    }
    else
    {
      /* Do nothing... */
    }

    /* 先进先出存最近3次的查询结果 */
    for ( i=0; i<AT_ANTENNA_LEVEL_NUM-1; i++ )
    {
         g_ATAntennaLevel[i] = g_ATAntennaLevel[i+1];
    }
    g_ATAntennaLevel[i] = enLevel;


    /* 格数波动则不更新，以达到平滑的效果 */
    for ( i=0; i<AT_ANTENNA_LEVEL_NUM-1; i++ )
    {
        if (g_ATAntennaLevel[i]  != g_ATAntennaLevel[i+1] )
        {
            return g_ulAntennaLevel;
        }
    }

    /* 信号格数稳定了 AT_ANTENNA_LEVEL_MAX_NUM 次时才做更新 */
    g_ulAntennaLevel = enLevel;
	return g_ulAntennaLevel;
}

#endif



TAF_UINT32 At_QryGlastErrPara( TAF_UINT8 ucIndex )
{
    TAF_UINT16                 usLength;

    /* 将错误码上报给后台*/
    usLength =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR*)pgucAtSndCodeAddr, "%s:",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength, "%d",
                                       gulErrType);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}


TAF_UINT32  At_QryTModePara(TAF_UINT8 ucIndex )
{
    TAF_UINT16                 usLength;

    /* 查询当前TMODE的执行状态 */
    usLength =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR*)pgucAtSndCodeAddr, "%s:",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength, "%d",
                                       1);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32  At_QryFpaPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    /*当前不为非信令模式*/
    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /* 查询当前发射机PA等级的设置 */
    usLength =  (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       g_stAtDevCmdCtrl.ucPaLevel);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}


VOS_UINT32  At_QryFlnaPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    /* 添加 LTE 模的接口分支 */
#if(FEATURE_LTE == FEATURE_ON)
    if ((AT_RAT_MODE_FDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode)
      ||(AT_RAT_MODE_TDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        return atQryFLNAPara(ucIndex);
    }
#endif

    /*当前不为非信令模式*/
    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /* 查询当前发射机PA等级的设置 */
    usLength =  (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       g_stAtDevCmdCtrl.ucLnaLevel);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}


TAF_UINT32  At_QryFChanPara(TAF_UINT8 ucIndex )
{
    TAF_UINT16                 usLength;

#if(FEATURE_LTE == FEATURE_ON)
    if ((AT_RAT_MODE_FDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode)
      ||(AT_RAT_MODE_TDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        return atQryFCHANPara(ucIndex);
    }
#endif

    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /* 查询当前FCHAN的设置 */
    usLength =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR*)pgucAtSndCodeAddr, "%s:",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                  (TAF_CHAR *)pgucAtSndCodeAddr + usLength, "%d,%d,%d,%d",
                                   g_stAtDevCmdCtrl.ucDeviceRatMode,
                                   g_stAtDevCmdCtrl.ucDeviceAtBand,
                                   g_stAtDevCmdCtrl.stDspBandArfcn.usUlArfcn,
                                   g_stAtDevCmdCtrl.stDspBandArfcn.usDlArfcn);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}


VOS_UINT32  At_QryFRxonPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    /* 添加LTE 模的接口分支 */
#if(FEATURE_LTE == FEATURE_ON)
    if ((AT_RAT_MODE_FDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode)
      ||(AT_RAT_MODE_TDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        return atQryFRXONPara(ucIndex);
    }
#endif

    /*当前不为非信令模式*/
    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /* 查询当前接收机开关状态 */
    usLength =  (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       g_stAtDevCmdCtrl.ucRxOnOff);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}


TAF_UINT32  At_QryFTxonPara(TAF_UINT8 ucIndex )
{
    TAF_UINT16                 usLength;

    /*添加 LTE 模的接口分支 */
#if(FEATURE_LTE == FEATURE_ON)
    if ((AT_RAT_MODE_FDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode)
      ||(AT_RAT_MODE_TDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        return atQryFTXONPara(ucIndex);
    }
#endif

    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }
    /* 查询当前DAC的设置 */
    usLength =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR*)pgucAtSndCodeAddr, "%s:",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                  (TAF_CHAR *)pgucAtSndCodeAddr + usLength, "%d",
                                   g_stAtDevCmdCtrl.ucTxOnOff);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}

TAF_UINT32  AT_QryFDac(TAF_UINT8 ucIndex )
{
    TAF_UINT16                 usLength;

    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /* 查询当前DAC的设置 */
    usLength =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR*)pgucAtSndCodeAddr, "%s:",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                  (TAF_CHAR *)pgucAtSndCodeAddr + usLength, "%d",
                                   g_stAtDevCmdCtrl.usFDAC);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}



TAF_UINT32  At_QryPlatForm(TAF_UINT8 ucIndex )
{
    VOS_UINT32                          ulRet;
    NAS_NVIM_PLATFORM_STRU              stPlatform;



    stPlatform.usPlatform = 0;

    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_SubPlatFormInfo, &stPlatform.usPlatform, sizeof(stPlatform.usPlatform));
    if (NV_OK != ulRet)
    {
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d,%d",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    1,
                                                    stPlatform.usPlatform);

    return AT_OK;

}

VOS_UINT32  At_QryDataLock(VOS_UINT8 ucIndex )
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d", g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    g_bAtDataLocked);

    return AT_OK;

}

VOS_UINT32  At_QrySD(VOS_UINT8 ucIndex )
{

    VOS_UINT32                          ulCurrentOprtStaus;

    ulCurrentOprtStaus = mdrv_sd_get_opptstatus();

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d", g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ulCurrentOprtStaus);
    return AT_OK;
}

VOS_UINT32  At_DelCtlAndBlankCharWithEndPadding(
    VOS_UINT8                               *pucData,
    VOS_UINT16                              *pusCmdLen
)
{

    VOS_UINT16                              usOrigLen;

    usOrigLen = *pusCmdLen;

    /* 扫描控制符 */
    if(AT_FAILURE == At_ScanCtlChar(pucData, pusCmdLen))
    {
        return AT_FAILURE;
    }

    /* 扫描引号以外的空格符 */
    if(AT_FAILURE == At_ScanBlankChar(pucData, pusCmdLen))
    {
        return AT_FAILURE;
    }

    PS_MEM_SET(pucData + (*pusCmdLen),0x00, (VOS_SIZE_T)(usOrigLen - (*pusCmdLen)));

    return AT_SUCCESS;

}

VOS_UINT32  At_QryVersion(VOS_UINT8 ucIndex )
{
    if(TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                            gastAtClientTab[ucIndex].opId,
                                            DRV_AGENT_VERSION_QRY_REQ,
                                            VOS_NULL_PTR,
                                            0,
                                            I0_WUEPS_PID_DRV_AGENT))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_VERSION_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}



VOS_UINT32  At_QryBsn(VOS_UINT8 ucIndex )
{
    /* 序列号长度为16,再加最后一位存储结束符 */
    VOS_UINT8                            aucBsnSerialNum[17];
    VOS_UINT16                           usLength;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRet;

    enModemId = MODEM_ID_0;

    /* 参数检查 */
    if(AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    usLength = sizeof(aucBsnSerialNum);

    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("At_SetSDomainPara: Get modem id fail.");
        return AT_ERROR;
    }

    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_ManufactureInfo, aucBsnSerialNum, usLength))
    {
        AT_WARN_LOG("At_QryBsn:WARNING:NVIM Read en_NV_Item_Serial_Num falied!");
        return AT_ERROR;
    }
    else
    {
        aucBsnSerialNum[16]=0;/*将最后一位置以结束符号'\0'*/
        usLength = 0;
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s:",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s",aucBsnSerialNum);
    }
    gstAtSendData.usBufLen = usLength;
    return AT_OK;

}

VOS_UINT32  At_QryCsVer(VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRet;
    TAF_NVIM_CS_VER_STRU                stCsver;


    stCsver.usCsver = 0;

    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_Csver, &stCsver, sizeof(VOS_UINT16));
    if (NV_OK != ulRet)
    {
        return AT_ERROR;
    }

   gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   "%s:%d",
                                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                   stCsver.usCsver);

    return AT_OK;
}

VOS_UINT32  At_QryQosPara(VOS_UINT8 ucIndex )
{
    AT_TRAFFIC_CLASS_CUSTOMIZE_STRU     stATTrafficClass;
    VOS_UINT16                          usReadLength;
    VOS_UINT16                          usLength;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRet;

    enModemId = MODEM_ID_0;


    stATTrafficClass.ucStatus       = NV_ITEM_DEACTIVE;
    stATTrafficClass.ucTrafficClass = AT_QOS_TRAFFIC_CLASS_SUBSCRIBE;


    /*命令状态类型检查*/
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /*读取NV中的值到stATTrafficClass结构体变量*/
    usReadLength = sizeof(stATTrafficClass);

    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("At_QryQosPara: Get modem id fail.");
        return AT_ERROR;
    }

    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_TRAFFIC_CLASS_Type, &stATTrafficClass, usReadLength))
    {
        AT_WARN_LOG("At_QryQosPara:WARNING:NVIM Read en_NV_Item_TRAFFIC_CLASS_Type failed!");
        return AT_DEVICE_OTHER_ERROR;
    }

    /*NV处于非激活态,直接上报默认值:AT_QOS_TRAFFIC_CLASS_INTERACTIVE*/
    if (NV_ITEM_DEACTIVE == stATTrafficClass.ucStatus)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr, "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          AT_QOS_TRAFFIC_CLASS_SUBSCRIBE);


    }
    else
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                         (VOS_CHAR *)pgucAtSndCodeAddr, "%s:%d",
                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                         stATTrafficClass.ucTrafficClass);
    }
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

VOS_UINT32   At_QrySDomainPara(VOS_UINT8 ucIndex)
{
    NAS_NVIM_MS_CLASS_STRU              stMsClass;
    VOS_UINT16                          usLength;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLength;

    enModemId = MODEM_ID_0;
    ulLength  = 0;


    PS_MEM_SET(&stMsClass, 0x00, sizeof(NAS_NVIM_MS_CLASS_STRU));
    stMsClass.ucMsClass = TAF_PH_MS_CLASS_A;

    /*命令状态类型检查*/
    if(AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /*读取NV*/
    usLength = sizeof(TAF_PH_MS_CLASS_TYPE);

    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("At_QrySDomainPara: Get modem id fail.");
        return AT_ERROR;
    }
    (VOS_VOID)NV_GetLength(en_NV_Item_MMA_MsClass, &ulLength);
    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_MMA_MsClass, &stMsClass, ulLength))
    {
        AT_WARN_LOG("At_QrySDomainPara:WARNING:NVIM Read en_NV_Item_MMA_MsClass failed!");
        return AT_DEVICE_OTHER_ERROR;
    }

    /*上报从NV中读取的MsClass值*/
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr, "%s:%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName, stMsClass.ucMsClass);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

VOS_UINT32   At_QryGPIOPL(VOS_UINT8 ucIndex)
{
    if (TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                              gastAtClientTab[ucIndex].opId,
                                              DRV_AGENT_GPIOPL_QRY_REQ,
                                              VOS_NULL_PTR,
                                              0,
                                              I0_WUEPS_PID_DRV_AGENT))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_GPIOPL_QRY;             /*设置当前操作模式 */
        return AT_WAIT_ASYNC_RETURN;                                            /* 等待异步事件返回 */
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 AT_QryMDatePara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usLength;
    TAF_AT_NVIM_MANUFACTURE_DATE_STRU   stManufactrueDate;

    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_AT_MANUFACTURE_DATE,
                    &stManufactrueDate,
                    AT_MDATE_STRING_LENGTH);
    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryMDatePara: fail to read NVIM . ");
        return AT_ERROR;
    }

    /*拼接响应字符串: 命令字，生产日期信息*/
    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s:",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    stManufactrueDate.aucMDate[AT_MDATE_STRING_LENGTH - 1] = '\0';
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s",
                                       stManufactrueDate.aucMDate);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_QryFacInfoPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           *pucFacInfo = TAF_NULL_PTR;
    VOS_UINT16                          usLength;

    /* 获取NV中已经存储的制造信息 */
    pucFacInfo = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_AT, AT_FACINFO_STRING_LENGTH);
    if (VOS_NULL_PTR == pucFacInfo)
    {
        AT_WARN_LOG("AT_QryFacInfoPara: fail to alloc memory.");
        return AT_ERROR;
    }

    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_AT_FACTORY_INFO,
                    pucFacInfo,
                    AT_FACINFO_STRING_LENGTH);
    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryFacInfoPara: fail to read en_NV_Item_AT_FACTORY_INFO . ");
        PS_MEM_FREE(WUEPS_PID_AT, pucFacInfo);
        return AT_ERROR;
    }

    /* 容错处理，强制给NV的INFO字段加结束符*/
    *(pucFacInfo + (AT_FACINFO_STRING_LENGTH - 1))     = '\0';
    *(pucFacInfo + AT_FACINFO_INFO1_LENGTH)            = '\0';

    /* 拼接响应字符串: 命令字，第一段制造信息 */
    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s:0,%s",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       pucFacInfo);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s",
                                       gaucAtCrLf);

    /* 拼接响应字符串: 命令字，第二段制造信息 */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s:1,%s",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       ((pucFacInfo + AT_FACINFO_INFO1_LENGTH) + 1));

    gstAtSendData.usBufLen = usLength;

    PS_MEM_FREE(WUEPS_PID_AT, pucFacInfo);
    return AT_OK;
}


VOS_UINT32  At_ReadDpaCatFromNV(VOS_UINT8 *pucDpaRate)
{
    AT_NVIM_UE_CAPA_STRU                stUECapa;
    AT_DPACAT_PARA_STRU                 astDhpaCategory[AT_DPACAT_CATEGORY_TYPE_BUTT] = {
                {PS_TRUE,   AT_HSDSCH_PHY_CATEGORY_6,  PS_FALSE, 0, PS_FALSE},                                                           /* 支持速率等级3.6M  */
                {PS_TRUE,   AT_HSDSCH_PHY_CATEGORY_8,  PS_FALSE, 0, PS_FALSE},                                                           /* 支持速率等级7.2M  */
                {PS_TRUE,   AT_HSDSCH_PHY_CATEGORY_11, PS_FALSE, 0, PS_FALSE},                                                           /* 支持速率等级1.8M  */
                {PS_TRUE,   AT_HSDSCH_PHY_CATEGORY_10, PS_FALSE, 0, PS_FALSE},                                                          /*  支持速率等级14.4M */
                {PS_TRUE,   AT_HSDSCH_PHY_CATEGORY_10, PS_TRUE,  AT_HSDSCH_PHY_CATEGORY_14, PS_FALSE}};           /*  支持速率等级21M */
    VOS_UINT8                           ucLoop;


    PS_MEM_SET(&stUECapa, 0x00, sizeof(stUECapa));


    /* 输入参数空指针检查*/
    if ( VOS_NULL_PTR == pucDpaRate )
    {
        AT_WARN_LOG("At_ReadDpaCatFromNV: null PTR.");
        return VOS_ERR;
    }

    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_WAS_RadioAccess_Capa_New, &stUECapa,
                        sizeof(AT_NVIM_UE_CAPA_STRU)))
    {
        AT_WARN_LOG("At_ReadDpaCatFromNV():en_NV_Item_WAS_RadioAccess_Capa NV Read Fail!");
        return VOS_ERR;
    }

    for (ucLoop = 0; ucLoop < AT_DPACAT_CATEGORY_TYPE_BUTT; ucLoop++)
    {
        if ((stUECapa.enHSDSCHSupport        == astDhpaCategory[ucLoop].enHSDSCHSupport)
         && (stUECapa.ucHSDSCHPhyCategory    == astDhpaCategory[ucLoop].ucHSDSCHPhyCategory)
         && (stUECapa.enMacEhsSupport        == astDhpaCategory[ucLoop].enMacEhsSupport)
         && (stUECapa.ucHSDSCHPhyCategoryExt == astDhpaCategory[ucLoop].ucHSDSCHPhyCategoryExt)
         && (stUECapa.enMultiCellSupport     == astDhpaCategory[ucLoop].enMultiCellSupport))
        {
            *pucDpaRate = ucLoop;
            return VOS_OK;
        }
    }

    return VOS_ERR;
}



VOS_UINT32   At_QryDpaCat(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucDpaRate;
    VOS_UINT32                          ulWasResult;
    VOS_UINT16                          usLength;

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* 调用读NV接口函数: At_ReadDpaCatFromNV,返回操作结果 */
    ulWasResult = At_ReadDpaCatFromNV(&ucDpaRate);
    if (VOS_OK == ulWasResult)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr, "%s:",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength, "%d",
                                           (VOS_UINT32)ucDpaRate);
        gstAtSendData.usBufLen = usLength;
        return  AT_OK;
    }
    else
    {
        AT_WARN_LOG("At_QryDpaCat:WARNING:WAS_MNTN_QueryDpaCat failed!");
        return AT_ERROR;
    }
}

VOS_UINT32 AT_ReadRrcVerFromNV(VOS_UINT8 *pucRrcVer)
{
    AT_NVIM_UE_CAPA_STRU                stUECapa;


    PS_MEM_SET(&stUECapa, 0x00, sizeof(stUECapa));


    /* 输入参数非空性检查 */
    if (VOS_NULL_PTR == pucRrcVer)
    {
        AT_WARN_LOG("AT_ReadRrcVerFromNV: null PTR.");
        return VOS_ERR;
    }

    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_WAS_RadioAccess_Capa_New,
                         &stUECapa,
                         sizeof(AT_NVIM_UE_CAPA_STRU)))
    {
        AT_WARN_LOG("AT_ReadRrcVerFromNV: NV_ReadEx en_NV_Item_WAS_RadioAccess_Capa_New fail!");
        return VOS_ERR;
    }

    /* NV未使能 */
    if (VOS_FALSE == stUECapa.ulHspaStatus)
    {
        *pucRrcVer = AT_RRC_VERSION_DPA_AND_UPA;
        return VOS_OK;
    }

    /* NV使能 */
    /* HSPA+ */
    if ((stUECapa.enAsRelIndicator >= AT_PTL_VER_ENUM_R7)
     && (VOS_TRUE == stUECapa.enEDCHSupport)
     && (VOS_TRUE == stUECapa.enHSDSCHSupport))
    {
        *pucRrcVer = AT_RRC_VERSION_HSPA_PLUNS;
    }
    /* DPA/UPA */
    else if((VOS_TRUE == stUECapa.enEDCHSupport)
         && (VOS_TRUE == stUECapa.enHSDSCHSupport))
    {
        *pucRrcVer = AT_RRC_VERSION_DPA_AND_UPA;
    }
    /* DPA */
    else if(VOS_TRUE == stUECapa.enHSDSCHSupport)
    {
        *pucRrcVer = AT_RRC_VERSION_DPA;
    }
    /* WCDMA */
    else
    {
        *pucRrcVer = AT_RRC_VERSION_WCDMA;
    }


    return VOS_OK;
}



VOS_UINT32   AT_QryHspaSpt(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucRRCVer;
    VOS_UINT32                          ulWasResult;
    VOS_UINT16                          usLength;

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DPAUPA_ERROR;
    }

    ulWasResult = AT_ReadRrcVerFromNV(&ucRRCVer);

    if (VOS_OK == ulWasResult)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr, "%s:",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength, "%d",
                                           (VOS_UINT32)ucRRCVer);
        gstAtSendData.usBufLen = usLength;
        return  AT_OK;
    }
    else
    {
        AT_WARN_LOG("AT_QryHspaSpt:WARNING:WAS_MNTN_QueryHspaSpt failed!");
        return AT_DPAUPA_ERROR;
    }
}


VOS_UINT32 At_QryCallSrvPara(VOS_UINT8 ucIndex)
{
    NAS_NVIM_CUSTOMIZE_SERVICE_STRU              stCustSrv;
    VOS_UINT16                          usLength;


    stCustSrv.ulStatus           = NV_ITEM_DEACTIVE;
    stCustSrv.ulCustomizeService = 0;


    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_CustomizeService, &stCustSrv, sizeof(stCustSrv)))
    {
        AT_WARN_LOG("At_QryCallSrvPara():en_NV_Item_CustomizeService NV Read Fail!");
        return AT_DEVICE_OTHER_ERROR;
    }

    /* 如果NV项未激活，返回单板默认值FALSE */
    if (NV_ITEM_DEACTIVE == stCustSrv.ulStatus)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          VOS_FALSE);
    }
    else
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          stCustSrv.ulCustomizeService);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}


VOS_UINT32 At_ReadCustomizeServiceNV(
    NAS_NVIM_CUSTOMIZE_SERVICE_STRU              *pstCustSrv,
    VOS_UINT16                          *pusValueInfo
)
{
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_CustomizeService, pstCustSrv,
                         sizeof(NAS_NVIM_CUSTOMIZE_SERVICE_STRU)))
    {
        AT_WARN_LOG("At_ReadCustomizeServiceNV():en_NV_Item_CustomizeService NV Read Fail!");
        return VOS_ERR;
    }

    if (AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED == *pusValueInfo)
    {
        return VOS_OK;
    }

    /*判断NV项的内容是否为默认值*/
    if ((pstCustSrv->ulStatus != NV_ITEM_DEACTIVE)
     || (pstCustSrv->ulCustomizeService != VOS_FALSE))
    {
        *pusValueInfo = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
    }

    return VOS_OK;

}


VOS_UINT32 At_ReadGprsActiveTimerLenNV(
    VOS_UINT32                          *pulGprsActiveTimerLen,
    VOS_UINT16                          *pusValueInfo
)
{
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_GPRS_ActiveTimerLength,
                          pulGprsActiveTimerLen, sizeof(VOS_UINT32)))
    {
        AT_WARN_LOG("At_ReadGprsActiveTimerLenNV():en_NV_Item_GPRS_ActiveTimerLength NV Read Fail!");
        return VOS_ERR;
    }

    if (AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED == *pusValueInfo)
    {
        return VOS_OK;
    }

    /*判断NV项的内容是否为默认值*/
    if (*pulGprsActiveTimerLen != AT_GPRS_ACT_TIMER_LEN_DEFAULT_VAL)
    {
        *pusValueInfo = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
    }

    return VOS_OK;

}


VOS_UINT32 At_QryCsdfltPara(VOS_UINT8 ucIndex)
{

    /* 发消息到C核获取SIMLOCK 状态信息 */
    if(TAF_SUCCESS != Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,
                                    0,
                                    TAF_PH_SIMLOCK_VALUE_PARA,
                                    TAF_NULL_PTR))
    {
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSDFLT_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_JudgeU8ArrayZero(
    VOS_UINT8                           aucValue[],
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulLoop;

    for (ulLoop = 0; ulLoop < ulLength; ulLoop++)
    {
        if (0 != aucValue[ulLoop])
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;
}


VOS_UINT32 AT_GetWifiNvValue(VOS_UINT16 *pusCsdValue)
{
    TAF_AT_MULTI_WIFI_SEC_STRU                              stWifiKey;
    TAF_AT_MULTI_WIFI_SSID_STRU                             stWifiSsid;
    VOS_UINT32                                              ulRet;
    VOS_UINT32                                              ulLoop;

    /* 不支持WIFI情况下WIFI的NV项不关注，直接返回未修改 */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI))
    {
        *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_UNCHANGE;
        return VOS_OK;
    }

    PS_MEM_SET(&stWifiKey, 0, sizeof(stWifiKey));
    PS_MEM_SET(&stWifiSsid, 0, sizeof(stWifiSsid));

    /* 判断en_NV_Item_WIFI_KEY是否为默认值，关注下述字段是否全0:
       aucWifiWpapsk aucWifiWepKey1 aucWifiWepKey2 aucWifiWepKey3 aucWifiWepKey4 */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_KEY, &stWifiKey, sizeof(TAF_AT_MULTI_WIFI_SEC_STRU)))
    {
        AT_WARN_LOG("AT_GetWifiNvValue:READ NV ERROR");
        return VOS_ERR;
    }

    /* 判断en_NV_Item_WIFI_STATUS_SSID是否为默认值，关注下述字段是否全0:
        aucWifiSsid
    */
    if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_STATUS_SSID, &stWifiSsid, sizeof(TAF_AT_MULTI_WIFI_SSID_STRU)))
    {
        AT_WARN_LOG("AT_GetWifiNvValue:READ NV ERROR");
        return VOS_ERR;
    }

    for (ulLoop = 0; ulLoop < AT_WIFI_MAX_SSID_NUM; ulLoop++)
    {
        ulRet = AT_JudgeU8ArrayZero(stWifiKey.aucWifiWpapsk[ulLoop], sizeof(stWifiKey.aucWifiWpapsk[ulLoop]));
        if (VOS_OK != ulRet)
        {
            *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
            return VOS_OK;
        }

        ulRet = AT_JudgeU8ArrayZero(stWifiKey.aucWifiWepKey1[ulLoop], sizeof(stWifiKey.aucWifiWepKey1[ulLoop]));
        if (VOS_OK != ulRet)
        {
            *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
            return VOS_OK;
        }

        ulRet = AT_JudgeU8ArrayZero(stWifiKey.aucWifiWepKey2[ulLoop], sizeof(stWifiKey.aucWifiWepKey2[ulLoop]));
        if (VOS_OK != ulRet)
        {
            *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
            return VOS_OK;
        }

        ulRet = AT_JudgeU8ArrayZero(stWifiKey.aucWifiWepKey3[ulLoop], sizeof(stWifiKey.aucWifiWepKey3[ulLoop]));
        if (VOS_OK != ulRet)
        {
            *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
            return VOS_OK;
        }

        ulRet = AT_JudgeU8ArrayZero(stWifiKey.aucWifiWepKey4[ulLoop], sizeof(stWifiKey.aucWifiWepKey4[ulLoop]));
        if (VOS_OK != ulRet)
        {
            *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
            return VOS_OK;
        }

        ulRet = AT_JudgeU8ArrayZero(stWifiSsid.aucWifiSsid[ulLoop], sizeof(stWifiSsid.aucWifiSsid[ulLoop]));
        if (VOS_OK != ulRet)
        {
            *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
            return VOS_OK;
        }
    }

    *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_UNCHANGE;
    return VOS_OK;

}


VOS_UINT32 AT_GetCsdValue(
    VOS_BOOL                            bSimlockEnableFlg,
    VOS_UINT16                         *pusCsdValue)
{
    VOS_UINT32                          ulRet;

    /*判断SIM LOCK Status定制项的内容是否为默认值DISABLE */
    /*获取SIM Lock Status定制项的值并检查是否为默认值*/
    if (VOS_FALSE != bSimlockEnableFlg)
    {
        *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
        return VOS_OK;
    }

    /* 判断WIFI相关的NV项是否为默认值 */
    ulRet = AT_GetWifiNvValue(pusCsdValue);

    return ulRet;
}


VOS_UINT32 AT_OutputCsdfltDefault(
    VOS_UINT8                           ucIndex,
    VOS_BOOL                            bSimlockEnableFlg
)
{
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulCsdfltFlg;
    VOS_UINT16                          usCsdfltValue;
    VOS_UINT32                          ulRslt;

    ulCsdfltFlg = VOS_TRUE;

    ulRslt = AT_GetCsdValue(bSimlockEnableFlg, &usCsdfltValue);

    if (VOS_OK != ulRslt)
    {
        return AT_ERROR;
    }

    /* 显示定制值信息，0:表示定制项中的值为单板自定义的默认值;
                       1:表示定制项中的值为非单板自定义的默认值 */
    if (AT_CUSTOMIZE_ITEM_DEFAULT_VAL_UNCHANGE == usCsdfltValue)
    {
        ulCsdfltFlg = VOS_FALSE;
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      ulCsdfltFlg);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}


VOS_UINT32  At_SimlockPlmnNumToAscii(
    const VOS_UINT8                     *pucPlmnRange,
    VOS_UINT8                           ucPlmnRangeLen,
    VOS_UINT8                            *pucAsciiStr
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucLen;
    VOS_UINT8                           ucBcdCode;

    if ((VOS_NULL_PTR == pucPlmnRange)
     || (VOS_NULL_PTR == pucAsciiStr))
    {
        AT_WARN_LOG("At_SimlockPlmnNumToAscii: Parameter of the function is null.");
        return AT_FAILURE;
    }

    /*整理号码字符串，去除无效的0XFF数据*/
    while (ucPlmnRangeLen > 1)
    {
        if (0xFF == pucPlmnRange[ucPlmnRangeLen - 1])
        {
            ucPlmnRangeLen--;
        }
        else
        {
            break;
        }
    }

    /*判断pucPlmnRange所指向的字符串的最后一个字节的低位是否为1111，
    如果是，说明号码位数为奇数，否则为偶数*/
    if ((pucPlmnRange[ucPlmnRangeLen - 1] & 0x0F) == 0x0F)
    {
        ucLen = (VOS_UINT8)((ucPlmnRangeLen * 2) - 1);
    }
    else
    {
        ucLen = (VOS_UINT8)(ucPlmnRangeLen * 2);
    }

    /*解析号码*/
    for (ucLoop = 0; ucLoop < ucLen; ucLoop++)
    {
        /*判断当前解码的是奇数位号码还是偶数位号码从0开始是偶数*/
        if (0 == (ucLoop % 2))
        {
            /*如果是偶数位号码，则取高4位的值*/
            ucBcdCode = ((pucPlmnRange[(ucLoop / 2)] >> 4) & 0x0F);
        }
        else
        {
            /*如果是奇数位号码，则取低4位的值*/
            ucBcdCode = (pucPlmnRange[(ucLoop / 2)] & 0x0F);
        }

        /*将数字转换成Ascii码形式*/
        if (ucBcdCode <= 9)
        {
            pucAsciiStr[ucLoop] = (ucBcdCode + '0');
        }
        else
        {
            return AT_FAILURE;
        }
    }

    pucAsciiStr[ucLoop] = '\0';      /*字符串末尾为0*/

    return AT_SUCCESS;
}


VOS_UINT32 At_QrySimLockPlmnInfo(VOS_UINT8 ucIndex)
{
    TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU  stSimLockPlmnInfo;
    VOS_UINT32                          i;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucMncLen;
    VOS_UINT32                          ulPlmnIdx;
    VOS_UINT32                          ulRsltChkPlmnBegin;
    VOS_UINT32                          ulRsltChkPlmnEnd;
    VOS_UINT32                          ulTotalPlmnNum;
    VOS_BOOL                            abPlmnValidFlg[TAF_MAX_SIM_LOCK_RANGE_NUM] = {VOS_FALSE};
    VOS_UINT8                           aucAsciiNumBegin[(TAF_PH_SIMLOCK_PLMN_STR_LEN * 2) + 1];
    VOS_UINT8                           aucAsciiNumEnd[(TAF_PH_SIMLOCK_PLMN_STR_LEN * 2) + 1];


    PS_MEM_SET(&stSimLockPlmnInfo, 0x00, sizeof(stSimLockPlmnInfo));


    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_CustomizeSimLockPlmnInfo,
                       &stSimLockPlmnInfo,
                       sizeof(stSimLockPlmnInfo)))
    {
        return AT_ERROR;
    }

    ulTotalPlmnNum = 0;

    if (NV_ITEM_DEACTIVE == stSimLockPlmnInfo.ulStatus)
    {
        /* 状态非激活时，显示Plmn个数为0 */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr, "%s:%d",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,ulTotalPlmnNum);

        gstAtSendData.usBufLen = usLength;
        return AT_OK;
    }

    /*  判断Plmn号段是否有效 */
    for ( i = 0; i < TAF_MAX_SIM_LOCK_RANGE_NUM; i++ )
    {
        ucMncLen = stSimLockPlmnInfo.astSimLockPlmnRange[i].ucMncNum;

        ulRsltChkPlmnBegin = At_SimlockPlmnNumToAscii(stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin,
                                    TAF_PH_SIMLOCK_PLMN_STR_LEN,aucAsciiNumBegin);

        ulRsltChkPlmnEnd = At_SimlockPlmnNumToAscii(stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin,
                                    TAF_PH_SIMLOCK_PLMN_STR_LEN,aucAsciiNumEnd);

        if ((AT_SUCCESS == ulRsltChkPlmnBegin)
         && (AT_SUCCESS == ulRsltChkPlmnEnd)
         && ((ucMncLen <= 3) && (ucMncLen >= 2)))
        {
            abPlmnValidFlg[i] = VOS_TRUE;
            ++ ulTotalPlmnNum;
        }
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr, "%s:%d",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,ulTotalPlmnNum);


    if (0 == ulTotalPlmnNum)
    {
        gstAtSendData.usBufLen = usLength;
        return AT_OK;
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    "%s", gaucAtCrLf);
    }


    ulPlmnIdx = 0;
    for ( i = 0; i < TAF_MAX_SIM_LOCK_RANGE_NUM; i++ )
    {
        if (VOS_FALSE == abPlmnValidFlg[i])
        {
            continue;
        }

        ++ ulPlmnIdx;

        At_SimlockPlmnNumToAscii(stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin,
                                    TAF_PH_SIMLOCK_PLMN_STR_LEN,aucAsciiNumBegin);

        At_SimlockPlmnNumToAscii(stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeEnd,
                                    TAF_PH_SIMLOCK_PLMN_STR_LEN,aucAsciiNumEnd);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    "%s:%d,%d,%s,%s",
                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                    ulPlmnIdx,
                                    stSimLockPlmnInfo.astSimLockPlmnRange[i].ucMncNum,
                                    aucAsciiNumBegin,
                                    aucAsciiNumEnd);

        if (ulPlmnIdx < ulTotalPlmnNum)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "%s", gaucAtCrLf);
        }
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

VOS_UINT32 At_QryMaxLockTimes(VOS_UINT8 ucIndex)
{
    TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU          stSimLockMaxTimes;
    VOS_UINT32                                  ulResult;
    VOS_UINT16                                  usLength;


    stSimLockMaxTimes.ulStatus       = NV_ITEM_DEACTIVE;
    stSimLockMaxTimes.ulLockMaxTimes = 0;


    ulResult = NV_ReadEx(MODEM_ID_0, en_NV_Item_CustomizeSimLockMaxTimes,
                       &stSimLockMaxTimes,
                       sizeof(stSimLockMaxTimes));
    if (NV_OK != ulResult)
    {
        AT_WARN_LOG("At_QryMaxLockTimes():en_NV_Item_CustomizeSimLockMaxTimes NV_ReadEx Fail!");
        return AT_DEVICE_OTHER_ERROR;
    }


    /* 如果NV项未激活，返回单板默认值 10 */
    if (NV_ITEM_DEACTIVE == stSimLockMaxTimes.ulStatus)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          TAF_PH_CARDLOCK_DEFAULT_MAXTIME);
    }
    else
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          stSimLockMaxTimes.ulLockMaxTimes);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}


VOS_UINT32  At_QryAppWronReg( VOS_UINT8 ucIndex )
{
    /* 发送消息给MMA，查询注册时间 */

    if(VOS_TRUE == TAF_MMA_QryApPwrOnAndRegTimeReq(WUEPS_PID_AT,
                                                   gastAtClientTab[ucIndex].usClientId,
                                                   0))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_REGISTER_TIME_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 At_QryNdisdupPara(
    VOS_UINT8                           ucIndex
)
{
    /* 其他的PDP TYPE 没有提出需求，目前只返回OK */
    return AT_OK;
}


VOS_UINT32 At_QryNdisConnPara(
    VOS_UINT8                           ucIndex
)
{
    /*--------------------------------------------------------------
       拨号参数查询, 直接返回本地保存的信息, 不在下发到适配层查询,
       PS域业务处理融合后, 查询处理再统一修改
    --------------------------------------------------------------*/
    AT_NDISCONN_PARA_STRU              *pstNdisConnDialInfo;
    VOS_UINT16                          usLength;

    /* 获取NDISCONN拨号时的参数 */
    usLength            = 0;
    pstNdisConnDialInfo = AT_GetNdisConnParaAddr();

    /* ^NDISCONN:  */
    usLength =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr, "%s:", "^NDISCONN");

    /*<pdpid>*/
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength, "%d", pstNdisConnDialInfo->ucCID);


    /*当前不在激活状态时不上报APN等信息*/
    if ( (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4State)
      && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv6State)
      && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4v6State) )
    {
        /*<connect>*/
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength, ",%d", 0);
    }
    else
    {
        /*<connect>*/
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength, ",%d", pstNdisConnDialInfo->ulConnectState);

        /*<APN>*/
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength, ",\"%s\"", pstNdisConnDialInfo->aucAPN);

        /*<username>*/
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength, ",\"%s\"", pstNdisConnDialInfo->aucUsername);

        /*<passwd>*/
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength, ",\"%s\"", pstNdisConnDialInfo->aucPassword);

        /*<auth>*/
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength, ",%d", pstNdisConnDialInfo->usAuthType);
    }
    gstAtSendData.usBufLen = usLength;



    return AT_OK;
}


AT_PDP_STATUS_ENUM_UINT32 AT_NdisGetConnStatus(
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    AT_PDP_STATUS_ENUM_UINT32           enConnStatus;

    enConnStatus                        = AT_PDP_STATUS_DEACT;

    if ( (AT_PDP_STATE_ACTED    == enPdpState)
      || (AT_PDP_STATE_DEACTING == enPdpState) )
    {
        enConnStatus = AT_PDP_STATUS_ACT;
    }

    return enConnStatus;
}


VOS_UINT32 AT_ReportNdisStatInfo(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    AT_PDP_STATUS_ENUM_UINT32           enIpv4Status;

    /* 初始化 */
    usLength        = 0;
    enIpv4Status    = AT_PDP_STATUS_DEACT;

    /* 上报查询结果 */
    if (AT_PDP_STATE_ACTED == AT_NdisGetState(TAF_PDP_IPV4))
    {
        enIpv4Status = AT_PDP_STATUS_ACT;
    }

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       "%d",
                                       enIpv4Status);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_QryNdisStatPara(
    VOS_UINT8                           ucIndex
)
{
    AT_PDP_STATUS_ENUM_UINT32           enIpv4Status;
#if (FEATURE_ON == FEATURE_IPV6)
    AT_PDP_STATUS_ENUM_UINT32           enIpv6Status;
    AT_PDP_STATUS_ENUM_UINT32           enIpv4v6Status;
#endif
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucAtStrIpv4[] = "IPV4";
#if (FEATURE_ON == FEATURE_IPV6)
    VOS_UINT8                           aucAtStrIpv6[] = "IPV6";
#endif

    usLength                            = 0;
    enIpv4Status                        = AT_PDP_STATUS_DEACT;
#if (FEATURE_ON == FEATURE_IPV6)
    enIpv6Status                        = AT_PDP_STATUS_DEACT;
    enIpv4v6Status                      = AT_PDP_STATUS_DEACT;
#endif

#if (FEATURE_ON == FEATURE_IPV6)
    switch (AT_GetIpv6Capability())
    {
        case AT_IPV6_CAPABILITY_IPV4_ONLY:
            enIpv4Status = AT_NdisGetConnStatus(AT_NdisGetState(TAF_PDP_IPV4));

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               "%d,,,\"%s\"",
                                               enIpv4Status,
                                               aucAtStrIpv4);
            break;

        case AT_IPV6_CAPABILITY_IPV6_ONLY:
            enIpv6Status    = AT_NdisGetConnStatus(AT_NdisGetState(TAF_PDP_IPV6));

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               "%d,,,\"%s\"",
                                               enIpv6Status,
                                               aucAtStrIpv6);
            break;

        case AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP:
            enIpv4v6Status  = AT_NdisGetConnStatus(AT_NdisGetState(TAF_PDP_IPV4V6));
            if ( AT_PDP_STATUS_ACT != enIpv4v6Status )
            {
                enIpv4Status = AT_NdisGetConnStatus(AT_NdisGetState(TAF_PDP_IPV4));
                enIpv6Status = AT_NdisGetConnStatus(AT_NdisGetState(TAF_PDP_IPV6));
            }
            else
            {
                enIpv4Status = enIpv4v6Status;
                enIpv6Status = enIpv4v6Status;
            }

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               "%d,,,\"%s\"",
                                               enIpv4Status,
                                               aucAtStrIpv4);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               ",%d,,,\"%s\"",
                                               enIpv6Status,
                                               aucAtStrIpv6);
            break;

        case AT_IPV6_CAPABILITY_IPV4V6_OVER_TWO_PDP:
            enIpv4Status = AT_NdisGetConnStatus(AT_NdisGetState(TAF_PDP_IPV4));
            enIpv6Status = AT_NdisGetConnStatus(AT_NdisGetState(TAF_PDP_IPV6));

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               "%d,,,\"%s\"",
                                               enIpv4Status,
                                               aucAtStrIpv4);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               ",%d,,,\"%s\"",
                                               enIpv6Status,
                                               aucAtStrIpv6);
            break;

        default:
            break;
    }
#else
    enIpv4Status = AT_NdisGetConnStatus(AT_NdisGetState(TAF_PDP_IPV4));

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       "%d,,,\"%s\"",
                                       enIpv4Status,
                                       aucAtStrIpv4);
#endif
    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}


TAF_UINT32 At_QryNdisAddPara(VOS_UINT8 ucIndex)
{
    return AT_CMD_NOT_SUPPORT;
}


VOS_UINT32 At_QryDnsPrim(
    VOS_UINT8                           ucIndex
)
{
    TAF_UINT16                          usLength;
    VOS_UINT32                          ulPdpStateFlag;
    AT_PDP_STATE_ENUM_U8                enState;

    AT_DIAL_PARAM_STRU                 *pstAppDialPara;

    pstAppDialPara                      = AT_APP_GetDailParaAddr();

    ulPdpStateFlag                      = VOS_FALSE;
    usLength                            = 0;

    if (AT_APP_USER == gastAtClientTab[ucIndex].UserType)
    {
        ulPdpStateFlag = AT_AppCheckIpv4PdpState(AT_PDP_STATE_ACTED);
        if (VOS_TRUE != ulPdpStateFlag)
        {
            AT_WARN_LOG("At_QryDnsPrim:WARNING: PDP is not ativated!");
            return AT_CME_NO_CONNECTION_TO_PHONE;
        }

        if (VOS_FALSE == pstAppDialPara->ulPrimIPv4DNSValidFlag)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (VOS_CHAR*)pgucAtSndCodeAddr,
                                   (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                   "%s: %s",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                   "0.0.0.0");
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               "%s: %s",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               pstAppDialPara->aucPrimIPv4DNSAddr);
        }

        gstAtSendData.usBufLen = usLength;

        return AT_OK;
    }

    enState = AT_NdisGetState(TAF_PDP_IPV4);
    if(AT_PDP_STATE_ACTED == enState)
    {
       ulPdpStateFlag = VOS_TRUE;
    }

    if (VOS_FALSE == ulPdpStateFlag)
    {
        AT_WARN_LOG("At_QryDnsPrim AT_NdisGetState:");
        return AT_CME_NO_CONNECTION_TO_PHONE;
    }

    if (VOS_FALSE == gstAtNdisAddParam.ulPrimIPv4DNSValidFlag)
    {
        usLength    += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               "%s",
                                               "^DNSP: 0.0.0.0");
    }
    else
    {
        usLength    += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               "%s: %s",
                                               "^DNSP",
                                               gstAtNdisAddParam.aucPrimIPv4DNSAddr);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}


VOS_UINT32 At_QryDnsSnd(
    VOS_UINT8                           ucIndex
)
{
    TAF_UINT16                          usLength;
    VOS_UINT32                          ulPdpStateFlag;
    AT_PDP_STATE_ENUM_U8                enState;
    AT_DIAL_PARAM_STRU                 *pstAppDialPara;

    pstAppDialPara                      = AT_APP_GetDailParaAddr();

    ulPdpStateFlag                      = VOS_FALSE;
    usLength                            = 0;

    if (AT_APP_USER == gastAtClientTab[ucIndex].UserType)
    {
        ulPdpStateFlag = AT_AppCheckIpv4PdpState(AT_PDP_STATE_ACTED);
        if (VOS_TRUE != ulPdpStateFlag)
        {
            AT_WARN_LOG("At_QryDnsPrim:WARNING: PDP is not ativated!");
            return AT_CME_NO_CONNECTION_TO_PHONE;
        }

        if (VOS_FALSE == pstAppDialPara->ulSndIPv4DNSValidFlag)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               "%s: %s",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               "0.0.0.0");
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               "%s: %s",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               pstAppDialPara->aucSndIPv4DNSAddr);

        }

        gstAtSendData.usBufLen = usLength;

        return AT_OK;
    }

    enState = AT_NdisGetState(TAF_PDP_IPV4);
    if(AT_PDP_STATE_ACTED == enState)
    {
       ulPdpStateFlag = VOS_TRUE;
    }

    if (VOS_FALSE == ulPdpStateFlag)
    {
        AT_WARN_LOG("At_QryDnsPrim AT_NdisGetState:");
        return AT_CME_NO_CONNECTION_TO_PHONE;
    }

    if (VOS_FALSE == gstAtNdisAddParam.ulSndIPv4DNSValidFlag)
    {
        usLength    += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               "%s",
                                               "^DNSS: 0.0.0.0");
    }
    else
    {
        usLength    += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               "%s: %s",
                                               "^DNSS:",
                                               gstAtNdisAddParam.aucSndIPv4DNSAddr);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32  At_QryApDialModePara(
    VOS_UINT8                           ucIndex
)
{
    AT_RNIC_DIAL_MODE_REQ_STRU         *pstMsg;

    /* 申请ID_RNIC_AT_DIAL_MODE_REQ消息 */
    pstMsg = (AT_RNIC_DIAL_MODE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_DIAL_MODE_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_QryApDialModePara: alloc msg fail!");
        return VOS_ERR;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR *)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_DIAL_MODE_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头 */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_DIAL_MODE_REQ;
    pstMsg->clientId        = gastAtClientTab[ucIndex].usClientId;

    /* 发ID_RNIC_AT_DIAL_MODE_REQ消息给RNIC获取当前的流速 */
    if (VOS_OK == PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APDIALMODE_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        AT_WARN_LOG("At_QryApDialModePara: Send msg failed!");
        return AT_ERROR;
    }
}


VOS_UINT32  AT_QryAppdmverPara ( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRet;

    /* 发消息到C核获取 PDM版本号 */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_APPDMVER_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryAppdmverPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APPDMVER_READ;
    return AT_WAIT_ASYNC_RETURN;

}


VOS_UINT32  AT_QryDislogPara ( VOS_UINT8 ucIndex )
{
    AT_DIAG_OPEN_FLAG_ENUM_U32          enDiagPortState;

#if (FEATURE_ON==FEATURE_LTE)
    VOS_UINT32                          ulRetDiag;
    VOS_UINT32                          ulRet3GDiag;
    VOS_UINT32                          ulRetGps;

    ulRet3GDiag   = AT_ExistSpecificPort(AT_DEV_DIAG);
    ulRetDiag     = AT_ExistSpecificPort(AT_DEV_4G_DIAG);
    ulRetGps      = AT_ExistSpecificPort(AT_DEV_4G_GPS);

    if ((VOS_TRUE == ulRet3GDiag)
      &&(VOS_TRUE == ulRetDiag)
      &&(VOS_TRUE == ulRetGps))
    {
        enDiagPortState = AT_DIAG_OPEN_FLAG_OPEN;
    }
    else
    {
        enDiagPortState = AT_DIAG_OPEN_FLAG_CLOSE;
    }
#else
    /* 从NV中读取 DISLOG 操作的密码及DIAG口的开关状态 */

    /*DIAG 口的开关状态, 0 打开; 1 关闭*/
    if (VOS_TRUE != AT_ExistSpecificPort(AT_DEV_DIAG))
    {
        enDiagPortState = AT_DIAG_OPEN_FLAG_CLOSE;
    }
    else
    {
        enDiagPortState = AT_DIAG_OPEN_FLAG_OPEN;
    }

#endif

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    enDiagPortState);
    return AT_OK;

}

#if (FEATURE_ON == FEATURE_SECURITY_SHELL)

VOS_UINT32 AT_QryShellPara (VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulShellStatus;


    ulShellStatus = AT_SHELL_CLOSE;


    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_AT_SHELL_OPEN_FLAG, &ulShellStatus,
                          sizeof(ulShellStatus)))
    {
        AT_WARN_LOG("AT_QryShellPara:WARNING:NV_ReadEx SHELL_OPEN_FLAG faild!");

        return AT_ERROR;
    }

    /* shell的状态只能为0,1,2 */
    if (AT_SHELL_OPEN < ulShellStatus)
    {
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ulShellStatus);
    return AT_OK;

}
#endif


VOS_UINT32 AT_QryWifiGlobalMacPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucE5GwMacAddr[AT_MAC_ADDR_LEN+1]; /* MAC地址*/

    /* 读取网关MAC地址*/
    ulResult = NV_ReadEx(MODEM_ID_0, en_NV_Item_WIFI_MAC_ADDR, aucE5GwMacAddr, AT_MAC_ADDR_LEN);
    aucE5GwMacAddr[AT_MAC_ADDR_LEN] = '\0';

    if ( NV_OK != ulResult )
    {
        AT_WARN_LOG("AT_QryApMacPara:read en_NV_Item_GWMAC_ADDR failed or no need to updatee");
        return AT_ERROR;
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%s",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      aucE5GwMacAddr);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}



VOS_UINT32 AT_QryDloadInfoPara( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRet;

    /* 发消息到C核获取单板信息 */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_DLOADINFO_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryDloadInfoPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DLOADINFO_READ;
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryAuthorityVerPara( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRet;

    /* 发消息到C核获取鉴权协议版本号 */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_AUTHORITYVER_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryAuthorityVerPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHORITYVER_READ;
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryAuthorityIdPara( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRet;

    /* 发消息到C核获取鉴权标识 */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_AUTHORITYID_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryAuthorityIdPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHORITYID_READ;
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryFlashInfoPara( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRet;

    /* 发消息到C核获取FLASH信息 */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_FLASHINFO_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryFlashInfoPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_FLASHINFO_READ;
    return AT_WAIT_ASYNC_RETURN;

}


VOS_UINT32 AT_QryAuthverPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* 发消息到C核获取SIMLOCK MANAGER版本信息 */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_AUTHVER_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryAuthverPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHVER_READ;
    return AT_WAIT_ASYNC_RETURN;

}


VOS_UINT32 AT_QryWiFiEnablePara(VOS_UINT8 ucIndex)
{
    /* 调用驱动接口查询当前WiFi的状态 */
    VOS_UINT32                          ulWifiStatus;

    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }

    ulWifiStatus = (VOS_UINT32)WIFI_GET_STATUS();

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     ulWifiStatus);
    return AT_OK;
}

VOS_UINT32 AT_QryWiFiModePara(VOS_UINT8 ucIndex)
{
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }

    /* WIFI模块只支持B/G/N模式 */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     g_ulWifiMode);
    return AT_OK;
}

VOS_UINT32 AT_QryWiFiBandPara(VOS_UINT8 ucIndex)
{
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }

    /* 目前只支持20M带宽 */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     AT_WIFI_BAND_20M);
    return AT_OK;
}

VOS_UINT32 AT_QryWiFiFreqPara(VOS_UINT8 ucIndex)
{
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }


    /* 查询设置值 */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     g_ulWifiFreq);
    return AT_OK;
}

VOS_UINT32 AT_QryWiFiRatePara(VOS_UINT8 ucIndex)
{
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }

    /* 查询设置值 */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     g_ulWifiRate);
    return AT_OK;
}

VOS_UINT32 AT_QryWiFiPowerPara(VOS_UINT8 ucIndex)
{
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }



    /* 查询设置值 */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    g_lWifiPower);
    return AT_OK;
}

VOS_UINT32 AT_QryWiFiTxPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8   ucWifiTxStatus;

    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }

    /* 调用驱动接口查询当前WiFi的模式 */
    if (AT_WIFI_TX_MODE == WIFI_GET_TCMD_MODE())
    {
        ucWifiTxStatus = AT_WIFI_TX_ON;
    }
    else
    {
        ucWifiTxStatus = AT_WIFI_TX_OFF;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ucWifiTxStatus );
    return AT_OK;
}

VOS_UINT32 AT_QryWiFiRxPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucWifiRxStatus;

    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }


    /* 调用驱动接口查询当前WiFi的模式 */
    if (AT_WIFI_RX_MODE == WIFI_GET_TCMD_MODE())
    {
        ucWifiRxStatus = AT_WIFI_TX_ON;
    }
    else
    {
        ucWifiRxStatus = AT_WIFI_TX_OFF;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ucWifiRxStatus );
    return AT_OK;
}

VOS_UINT32 AT_QryWiFiPacketPara(VOS_UINT8 ucIndex)
{
    VOS_UINT                                ulUcastWifiRxPkts;
    VOS_UINT                                ulMcastWifiRxPkts;
    VOS_UINT32                              ulWifiRxPkts;

    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }


    /* 判断接收机是否打开 */
    if (AT_WIFI_RX_MODE != WIFI_GET_TCMD_MODE())
    {
        AT_WARN_LOG("AT_QryWiFiPacketPara: Not Rx Mode.");
        return AT_ERROR;
    }

    /* 调用驱动接口查询包的数量 */
    WIFI_GET_RX_PACKET_REPORT(&ulUcastWifiRxPkts,  &ulMcastWifiRxPkts);
    ulWifiRxPkts = (ulUcastWifiRxPkts - g_ulUcastWifiRxPkts);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ulWifiRxPkts,
                                                    0);


    return AT_OK;
}


VOS_UINT32 AT_QryWiFiSsidPara(VOS_UINT8 ucIndex)
{
    TAF_AT_MULTI_WIFI_SSID_STRU                             stWifiSsid;
    VOS_UINT16                                              usLen;
    VOS_UINT8                                               ucSsidNum;
    VOS_UINT32                                              ulLoop;
    VOS_UINT8                                               aucSsidLen[AT_WIFI_MAX_SSID_NUM];

    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }

    PS_MEM_SET(&stWifiSsid, 0 ,sizeof(stWifiSsid));

    /*读取WIFI SSID对应的NV项*/
    if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_STATUS_SSID,&stWifiSsid, sizeof(TAF_AT_MULTI_WIFI_SSID_STRU)))
    {
        AT_WARN_LOG("AT_SetWiFiSsidPara:READ NV ERROR");
        return AT_ERROR;
    }

    ucSsidNum = 0;
    PS_MEM_SET(aucSsidLen, 0, sizeof(aucSsidLen));

    for (ulLoop = 0; ulLoop < AT_WIFI_MAX_SSID_NUM; ulLoop++)
    {
        aucSsidLen[ulLoop] = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)stWifiSsid.aucWifiSsid[ulLoop]);

        if (0 != aucSsidLen[ulLoop])
        {
            ucSsidNum++ ;
        }
    }

    usLen = 0;
    usLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                    (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                    "%s:%d%s",
                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                    ucSsidNum,
                                    gaucAtCrLf);

    for (ulLoop = 0; ulLoop < AT_WIFI_MAX_SSID_NUM; ulLoop++)
    {
        if (0 != aucSsidLen[ulLoop])
        {
            usLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                            "%s:%d,%s%s",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            ulLoop,
                                            stWifiSsid.aucWifiSsid[ulLoop],
                                            gaucAtCrLf);
        }
    }

    gstAtSendData.usBufLen = usLen;

    return AT_OK;
}


VOS_UINT32 AT_QryWiFiLogPara(VOS_UINT8 ucIndex)
{
    TAF_AT_MULTI_WIFI_SSID_STRU                             stWifiSsid;
    TAF_AT_MULTI_WIFI_SEC_STRU                              stWifiSec;
    VOS_UINT16                                              usLen;

    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }

    PS_MEM_SET(&stWifiSec, 0, sizeof(stWifiSec));
    PS_MEM_SET(&stWifiSsid, 0, sizeof(stWifiSsid));

    /* 读取WIFI SSID对应的NV项 */
    if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_STATUS_SSID,&stWifiSsid, sizeof(TAF_AT_MULTI_WIFI_SSID_STRU)))
    {
        AT_WARN_LOG("AT_QryWiFiLogPara:READ NV FAIL");
        return AT_ERROR;
    }

    usLen = 0;

    usLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                   "%s:0,%s%s",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                   stWifiSsid.aucWifiSsid[0],
                                   gaucAtCrLf);

    /* 读取WIFI key对应的NV项 */
    if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_KEY, &stWifiSec,sizeof(TAF_AT_MULTI_WIFI_SEC_STRU)))
    {
        AT_WARN_LOG("AT_QryWiFiLogPara:READ NV FAIL");
        return AT_ERROR;
    }

    /* KEY1对应的NV不空表示KEY1有效 */
    if (0 != VOS_StrLen((VOS_CHAR*)stWifiSec.aucWifiWepKey1[0]))
    {
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                        "%s:1,%s%s",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        stWifiSec.aucWifiWepKey1[0],
                                        gaucAtCrLf);
    }

    /* KEY2对应的NV不空表示KEY2有效 */
    if (0 != VOS_StrLen((VOS_CHAR*)stWifiSec.aucWifiWepKey2[0]))
    {
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                        "%s:2,%s%s",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        stWifiSec.aucWifiWepKey2[0],
                                        gaucAtCrLf);
    }
    /* KEY3对应的NV不空表示KEY3有效 */
    if (0 != VOS_StrLen((VOS_CHAR*)stWifiSec.aucWifiWepKey3[0]))
    {
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                        "%s:3,%s%s",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        stWifiSec.aucWifiWepKey3[0],
                                        gaucAtCrLf);
    }
    /* KEY4对应的NV不空表示KEY3有效 */
    if (0 != VOS_StrLen((VOS_CHAR*)stWifiSec.aucWifiWepKey4[0]))
    {
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                        "%s:4,%s%s",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        stWifiSec.aucWifiWepKey4[0],
                                        gaucAtCrLf);
    }

    gstAtSendData.usBufLen = usLen;

    return AT_OK;
}

VOS_UINT32 AT_QryWiFiKeyPara(VOS_UINT8 ucIndex)
{
    TAF_AT_MULTI_WIFI_SEC_STRU                              stWifiSec;
    VOS_UINT8                                               ucWifiKeyNum;
    VOS_UINT16                                              usLen;
    VOS_UINT8                                               aucWpapskLen[AT_WIFI_MAX_SSID_NUM];
    VOS_UINT32                                              ulLoop;

    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }

    PS_MEM_SET(&stWifiSec, 0, sizeof(stWifiSec));

    /* 读取WIFI key对应的NV项 */
    if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_KEY, &stWifiSec,sizeof(TAF_AT_MULTI_WIFI_SEC_STRU)))
    {
        AT_WARN_LOG("AT_QryWiFiSsidPara:READ NV FAIL");
        return AT_ERROR;
    }


    ucWifiKeyNum = 0;
    PS_MEM_SET(aucWpapskLen, 0, sizeof(aucWpapskLen));

    for (ulLoop = 0; ulLoop < AT_WIFI_MAX_SSID_NUM; ulLoop++)
    {

        /* KEY1对应的NV不空表示KEY1有效 */
        aucWpapskLen[ulLoop] = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)stWifiSec.aucWifiWpapsk[ulLoop]);

        if (0 != aucWpapskLen[ulLoop])
        {
            ucWifiKeyNum++ ;
        }
    }

    /* 未解锁时，需要返回已定制0组 */
    if (VOS_TRUE == g_bAtDataLocked)
    {
        ucWifiKeyNum = 0;
        PS_MEM_SET(aucWpapskLen, 0, sizeof(aucWpapskLen));
    }

    usLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   "%s:%d%s",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                   ucWifiKeyNum,
                                   gaucAtCrLf);

    for (ulLoop = 0; ulLoop < AT_WIFI_MAX_SSID_NUM; ulLoop++)
    {
        if (0 != aucWpapskLen[ulLoop])
        {
            usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                            "%s:%d,%s%s",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            ulLoop,
                                            stWifiSec.aucWifiWpapsk[ulLoop],
                                            gaucAtCrLf);
        }
    }

    gstAtSendData.usBufLen = usLen;


    return AT_OK;
}


VOS_UINT32 AT_QryWifiPaRangePara (VOS_UINT8 ucIndex)
{
    AT_WIFI_MODE_ENUM_UINT8             ucCurWifiMode;

    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }


    /* 调用底软提供查询接口获取当前WIFI模式 */
    ucCurWifiMode   = (VOS_UINT8)WIFI_GET_PA_CUR_MODE();

    if (AT_WIFI_MODE_ONLY_PA == ucCurWifiMode)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s:%s",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        "h");
    }
    else if (AT_WIFI_MODE_ONLY_NOPA == ucCurWifiMode)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s:%s",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        "l");
    }
    else
    {
        return AT_ERROR;
    }

    return AT_OK;
}

 
VOS_UINT32 AT_QryProdTypePara(VOS_UINT8 ucIndex)
{
    if (TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                              gastAtClientTab[ucIndex].opId,
                                              DRV_AGENT_PRODTYPE_QRY_REQ,
                                              VOS_NULL_PTR,
                                              0,
                                              I0_WUEPS_PID_DRV_AGENT))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PRODTYPE_QRY;             /*设置当前操作模式 */
        return AT_WAIT_ASYNC_RETURN;                                            /* 等待异步事件返回 */
    }
    else
    {
        return AT_ERROR;
    }
}

VOS_UINT32 AT_QryTmmiPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           aucFacInfo[AT_FACTORY_INFO_LEN];
    VOS_UINT8                           ucMmiFlag;
    VOS_UINT32                          ulResult;

    ulResult = NV_ReadEx(MODEM_ID_0, en_NV_Item_Factory_Info,
                       aucFacInfo,
                       AT_FACTORY_INFO_LEN);

    if (NV_OK != ulResult)
    {
        return AT_ERROR;
    }

    if (VOS_OK == VOS_MemCmp(&aucFacInfo[AT_MMI_TEST_FLAG_OFFSET],
                             AT_MMI_TEST_FLAG_SUCC,
                             AT_MMI_TEST_FLAG_LEN))
    {
        ucMmiFlag = VOS_TRUE;
    }
    else
    {
        ucMmiFlag = VOS_FALSE;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            "%s:%d",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            ucMmiFlag);

    return AT_OK;
}


VOS_UINT32 AT_QryChrgInfoPara(VOS_UINT8 ucIndex)
{

    VOS_INT32                           lChargeState;

    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_CHARGE) )
    {
        return AT_ERROR;
    }

    /* 调用驱动接口获取充电状态 */
    lChargeState = mdrv_misc_get_charging_status();

    /* 打印输出 */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)(pgucAtSndCodeAddr),
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    lChargeState);

    return AT_OK;

}

VOS_UINT32 AT_QryChrgEnablePara(VOS_UINT8 ucIndex)
{
    VOS_INT32                             ucChargeEnable;

    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_CHARGE) )
    {
        return AT_ERROR;
    }

    /* 调用驱动接口获取充电状态 */

    ucChargeEnable = mdrv_misc_get_charge_state();
    /* 打印输出 */
    /* 只有TRUE/FLASE的返回值是有效的 */
    if((ucChargeEnable == TRUE)||( ucChargeEnable == FALSE))
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       "%s:%d",
                                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                       ucChargeEnable);

        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
}

VOS_UINT32 AT_QryWebPwdPara(VOS_UINT8 ucIndex)
{
    TAF_AT_NVIM_WEB_ADMIN_PASSWORD_STRU stWebPwd;

    PS_MEM_SET(&stWebPwd, 0x0, sizeof(stWebPwd));

    /* 读取WEBPWD对应的NV项 */
    if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_WEB_ADMIN_PASSWORD, &stWebPwd, sizeof(stWebPwd)))
    {
        AT_WARN_LOG("AT_QryWebPwdPara:READ NV FAIL");
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%s,%s",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     stWebPwd.aucWebPwd);
    return AT_OK;
}

VOS_UINT32 AT_GetWcdmaBandStr(
    VOS_UINT8                          *pucGsmBandstr,
    AT_UE_BAND_CAPA_ST                 *pstBandCapa
)
{
    VOS_UINT32                          ulLen;
    ulLen = 0;

    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_I_2100)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC1,");
    }

    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_II_1900)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC2,");
    }


    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_III_1800)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC3,");
    }

    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_IV_1700)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC4,");
    }

    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_V_850)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC5,");
    }

    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_VI_800)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC6,");
    }


    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_VII_2600)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC7,");
    }

    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_VIII_900)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC8,");
    }

    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_IX_J1700)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC9,");
    }

    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_XI_1500)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC11,");
    }
    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_XIX_850)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "BC19,");
    }

    if (ulLen != 0)
    {
        pucGsmBandstr[ulLen - 1] = '\0';
    }

    return ulLen;
 }


VOS_UINT32 AT_GetWcdmaDivBandStr(
    VOS_UINT8                          *pucGsmBandstr
)
{
    VOS_UINT32                                  ulLen;
    VOS_UINT32                                  ulBand;

    AT_WCDMA_PREF_BAND_STRU      *pstBitBand;

    /* 获取UMTS支持的分集频带集合
        V3R2版本是en_NV_Item_W_RF_DIV_BAND，V3R1是en_NV_Item_ANTENNA_CONFIG */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_W_RF_DIV_BAND, &ulBand, sizeof(ulBand)))
    {
        AT_WARN_LOG("AT_GetWcdmaDivBandStr: Read NVIM Smss Error");
        return 0;
    }

    ulLen = 0;
    pstBitBand = (AT_WCDMA_PREF_BAND_STRU *)&ulBand;

    /* 单板分集支持的BAND 通路，数据为十进制数，转化为二进制后
        从右往左依次为Band1、2、3……。*/

    if (1 == pstBitBand->BandWCDMA_I_2100)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U1,");
    }

    if (1 == pstBitBand->BandWCDMA_II_1900)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U2,");
    }


    if (1 == pstBitBand->BandWCDMA_III_1800)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U3,");
    }

    if (1 == pstBitBand->BandWCDMA_IV_1700)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U4,");
    }

    if (1 == pstBitBand->BandWCDMA_V_850)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U5,");
    }

    if (1 == pstBitBand->BandWCDMA_VI_800)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U6,");
    }


    if (1 == pstBitBand->BandWCDMA_VII_2600)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U7,");
    }

    if (1 == pstBitBand->BandWCDMA_VIII_900)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U8,");
    }

    if (1 == pstBitBand->BandWCDMA_IX_J1700)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U9,");
    }

    if (1 == pstBitBand->BandWCDMA_XI_1500)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U11,");
    }

    if (1 == pstBitBand->BandWCDMA_XIX_850)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U19,");
    }

    if (ulLen != 0)
    {
        pucGsmBandstr[ulLen - 1] = '\0';
    }

    return ulLen;
 }


VOS_UINT32 AT_GetGsmBandStr(
    VOS_UINT8                          *pucGsmBandstr ,
    AT_UE_BAND_CAPA_ST                 *pstBandCapa
)
{
    VOS_UINT32                          ulLen;

    ulLen = 0;

    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsm450)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "450,");
    }

    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsm480)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "480,");
    }


    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsm850)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "850,");
    }


    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsmP900)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "P900,");
    }
    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsmR900)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "R900,");
    }
    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsmE900)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "E900,");
    }
    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsm1800)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "1800,");
    }
    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsm1900)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "1900,");
    }
    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsm700)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "700,");
    }

    if (ulLen != 0)
    {
        pucGsmBandstr[ulLen - 1] = '\0';
    }

    return ulLen;
}
 
VOS_UINT32 AT_QryFeaturePara(VOS_UINT8 ucIndex)
{
    if (TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                             gastAtClientTab[ucIndex].opId,
                                             DRV_AGENT_SFEATURE_QRY_REQ,
                                             VOS_NULL_PTR,
                                             0,
                                             I0_WUEPS_PID_DRV_AGENT))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SFEATURE_QRY;           /*设置当前操作模式 */
        return AT_WAIT_ASYNC_RETURN;                                            /* 等待异步事件返回 */
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 AT_QryProdNamePara(VOS_UINT8 ucIndex)
{
    TAF_AT_PRODUCT_ID_STRU              stProductId;
    VOS_UINT32                          ulRet;

    PS_MEM_SET(&stProductId,0,sizeof(TAF_AT_PRODUCT_ID_STRU));

    /* 从NV50048中读取产品名称 */
    /* 读取NV项en_NV_Item_PRODUCT_ID获取产品名称 */
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_PRODUCT_ID,
                    &stProductId,
                    sizeof(stProductId.ulNvStatus) + sizeof(stProductId.aucProductId));

    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryProdNamePara: Fail to read en_NV_Item_PRODUCT_ID");
        return AT_ERROR;
    }

    /*该NV是否使能*/
    if (VOS_TRUE != stProductId.ulNvStatus)
    {
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%s",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stProductId.aucProductId);

    return AT_OK;
}


VOS_UINT32 AT_QryEqverPara(VOS_UINT8 ucIndex)
{
    /*<version>装备归一化 AT命令版本号，版本号以三位表示，每位为0~9的数字字符。
    该版本号取决于单板实现的AT命令时参考的本文档的版本号。
    114 支持归一化AT命令版本查询的第一个版本
    balong固定返回115*/
    VOS_UINT32                          ulRet;
    TAF_AT_EQ_VER_STRU                  stEqver;

    stEqver.usEqver = 0;

    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_Eqver, &stEqver.usEqver, sizeof(stEqver.usEqver));
    if (NV_OK != ulRet)
    {
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     stEqver.usEqver);

    return AT_OK;
}



VOS_UINT32 AT_QryApRptSrvUrlPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           aucApRptSrvUrl[AT_AP_NVIM_XML_RPT_SRV_URL_LEN + 1];
    VOS_UINT32                          ulRet;
    TAF_AT_NVIM_AP_RPT_SRV_URL_STRU     stApRptSrvUrl;

    PS_MEM_SET(aucApRptSrvUrl, 0, (VOS_SIZE_T)(AT_AP_NVIM_XML_RPT_SRV_URL_LEN + 1));

    PS_MEM_SET(&stApRptSrvUrl, 0x0, sizeof(stApRptSrvUrl));

    /* 读NV:en_NV_Item_AP_RPT_SRV_URL*/
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_AP_RPT_SRV_URL,
                    &stApRptSrvUrl,
                    AT_AP_NVIM_XML_RPT_SRV_URL_LEN);

    if (NV_OK != ulRet)
    {
        AT_ERR_LOG("AT_QryApRptSrvUrlPara:Read NV fail");
        return AT_ERROR;
    }
    PS_MEM_CPY(aucApRptSrvUrl, stApRptSrvUrl.aucApRptSrvUrl, AT_AP_NVIM_XML_RPT_SRV_URL_LEN);
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:\"%s\"",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    aucApRptSrvUrl);

    return AT_OK;
}


VOS_UINT32 AT_QryApXmlInfoTypePara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           aucApXmlInfoType[AT_AP_XML_RPT_INFO_TYPE_LEN + 1];
    VOS_UINT32                          ulRet;
    TAF_AT_NVIM_AP_XML_INFO_TYPE_STRU   stApXmlInfoType;

    PS_MEM_SET(aucApXmlInfoType, 0, (VOS_SIZE_T)(AT_AP_XML_RPT_INFO_TYPE_LEN + 1));

    PS_MEM_SET(&stApXmlInfoType, 0x0, sizeof(stApXmlInfoType));

    /* 读NV:en_NV_Item_AP_XML_INFO_TYPE*/
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_AP_XML_INFO_TYPE,
                    &stApXmlInfoType,
                    AT_AP_NVIM_XML_RPT_INFO_TYPE_LEN);

    if (NV_OK != ulRet)
    {
        AT_ERR_LOG("AT_QryApXmlInfoTypePara:Read NV fail");
        return AT_ERROR;
    }

    PS_MEM_CPY(aucApXmlInfoType, stApXmlInfoType.aucApXmlInfoType, AT_AP_NVIM_XML_RPT_INFO_TYPE_LEN);

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%s",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    aucApXmlInfoType);

    return AT_OK;
}


VOS_UINT32 AT_QryApXmlRptFlagPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    TAF_AT_NVIM_AP_XML_RPT_FLG_STRU     stApXmlRptFlg;
    VOS_UINT32                          ulLength;

    ulLength                   = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_AP_XML_RPT_FLAG, &ulLength);

    stApXmlRptFlg.ucApXmlRptFlg = VOS_FALSE;

    /* 读NV:en_NV_Item_AP_XML_RPT_FLAG*/
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_AP_XML_RPT_FLAG,
                        &stApXmlRptFlg,
                        ulLength);

    if (NV_OK != ulRet)
    {
        AT_ERR_LOG("AT_QryApXmlRptFlagPara:Read NV fail");
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stApXmlRptFlg.ucApXmlRptFlg);

    return AT_OK;
}



VOS_UINT32 AT_QryFastDormPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRslt;

    /* 调用MN_FillAndSndAppReqMsg()，等待RABM的回复 */
    ulRslt = AT_SndQryFastDorm(gastAtClientTab[ucIndex].usClientId,gastAtClientTab[ucIndex].opId);
    if (AT_SUCCESS == ulRslt)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_FASTDORM_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}


VOS_UINT32 AT_QryAcpuMemInfoPara(TAF_UINT8 ucIndex)
{
    (VOS_VOID)vos_printf("AT_QryAcpuMemInfoPara:at cmd\r\n");

    /*命令状态类型检查*/
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }



    return AT_OK;

}



VOS_UINT32 AT_QryCcpuMemInfoPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    (VOS_VOID)vos_printf("AT_QryCcpuMemInfoPara:at cmd\r\n");

    /*命令状态类型检查*/
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* 发消息到C核处理CCPU内存泄漏检查 */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_QRY_CCPU_MEM_INFO_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryCcpuMemInfoPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    return AT_OK;
}


VOS_UINT32 AT_QryCipherPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* 发消息给MMA获取Cipher信息 */
    ulResult = TAF_MMA_QryCipherReq(WUEPS_PID_AT,
                                    gastAtClientTab[ucIndex].usClientId,
                                    0);

    /* 执行命令操作 */
    if (VOS_TRUE == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CIPERQRY_READ;

        /* 返回命令处理挂起状态 */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 AT_QryLocinfoPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* 发消息给MMA获取当前UE的位置信息 */
    ulResult = TAF_MMA_QryLocInfoReq(WUEPS_PID_AT,
                                     gastAtClientTab[ucIndex].usClientId,
                                     0);

    /* 执行命令操作 */
    if (VOS_TRUE == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_LOCINFO_READ;

        /* 返回命令处理挂起状态 */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}


VOS_UINT32 AT_QryNvResumePara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usNvResumeFlag;


    usNvResumeFlag = AT_NV_RESUME_SUCC;


    /* 读取en_NV_Resume_Flag */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Resume_Flag, &usNvResumeFlag, sizeof(VOS_UINT16)))
    {
        AT_WARN_LOG("AT_QryNvResumePara:READ NV FAIL");
        return AT_ERROR;
    }

    /* 读出的值只能为0或者1 */
    if ((AT_NV_RESUME_SUCC != usNvResumeFlag)
     && (AT_NV_RESUME_FAIL != usNvResumeFlag))
    {
        AT_WARN_LOG("AT_QryNvResumePara:PARA IS INVALID");
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     usNvResumeFlag);
    return AT_OK;
}


VOS_UINT32 AT_QryNvBackupStatusPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* 发消息到C核获取当前NV备份状态信息 */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_NVBACKUPSTAT_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryNvBackupStatusPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NVBACKUPSTAT_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryNandBadBlockPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* 发消息到C核获取NAND FLASH的所有坏块索引列表信息 */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_NANDBBC_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryNandBadBlockPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NANDBBC_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryNandDevInfoPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* 发消息到C核获取NAND FLASH的型号信息 */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_NANDVER_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryNandDevInfoPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NANDVER_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryChipTempPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* 发消息到C核获取PA、SIM卡和电池的温度信息 */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_CHIPTEMP_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryChipTempPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CHIPTEMP_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryApRptPortSelectPara(VOS_UINT8 ucIndex)
{
    AT_PORT_RPT_CFG_UNION               unRptCfg;
    AT_CLIENT_CONFIGURATION_STRU       *pstClientCfg;
    AT_CLIENT_CFG_MAP_TAB_STRU         *pstCfgMapTbl;
    VOS_UINT8                           i;

    unRptCfg.ulRptCfgBit64  = 0;

    /* 通道检查 */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    for (i = 0; i < AT_GET_CLIENT_CFG_TAB_LEN(); i++)
    {
        pstCfgMapTbl = AT_GetClientCfgMapTbl(i);
        pstClientCfg = AT_GetClientConfig(pstCfgMapTbl->enClientId);

        if (VOS_TRUE == pstClientCfg->ucReportFlg)
        {
            unRptCfg.ulRptCfgBit64 |= pstCfgMapTbl->ulRptCfgBit64;
        }
    }

    /* 返回查询结果 */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %08X, %08X",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    unRptCfg.aulRptCfgBit32[0],
                                                    unRptCfg.aulRptCfgBit32[1]);


    return AT_OK;
}


VOS_UINT32 At_QryUsbSwitchPara (VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucUsbStatus;
    VOS_UINT32                          ulResult;


    ucUsbStatus = USB_SWITCH_OFF;

    /* 通道检查 */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    if (VOS_OK != DRV_USB_PHY_SWITCH_GET(&ucUsbStatus))
    {
        return AT_ERROR;
    }

    ulResult = (ucUsbStatus == USB_SWITCH_ON)?AT_USB_SWITCH_SET_VBUS_VALID:\
                                              AT_USB_SWITCH_SET_VBUS_INVALID;

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            "+USBSWITCH: %X", ulResult);

    return AT_OK;
}


VOS_UINT32 AT_QryAntState(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usAntState;

    /* 参数检查 */
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }


    usAntState = 0;

    ulRet = TAF_AGENT_GetAntState(ucIndex, &usAntState);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_QryAntState: TAF_AGENT_GetAntState fail");

        return AT_ERROR;
    }

    /* AT输出 */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    usAntState);
    return AT_OK;
}


VOS_UINT32 AT_QrySARReduction(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usUETestMode;
    AT_MODEM_MT_INFO_CTX_STRU          *pstMtInfoCtx = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT16                          usAntState;

    usUETestMode = VOS_FALSE;

    /* 读取NV项判定是否为测试模式 */
    ulRet = NV_ReadEx(MODEM_ID_0,
                      en_NV_Item_RF_SAR_BACKOFF_TESTMODE,
                      &usUETestMode,
                      sizeof(usUETestMode));

    if (NV_OK != ulRet)
    {
        AT_ERR_LOG("AT_QrySARReduction:Read NV fail");
        return AT_ERROR;
    }


    enModemId  = MODEM_ID_0;

    ulRet   = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_QrySARReduction:Get modem id fail");
        return AT_ERROR;
    }

    pstMtInfoCtx = AT_GetModemMtInfoCtxAddrFromModemId(enModemId);

    usAntState   = 0;
    ulRet        = TAF_AGENT_GetAntState(ucIndex, &usAntState);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_QrySARReduction:Get modem id fail");
        return AT_ERROR;
    }

    if ((AT_ANT_CONDUCTION_MODE == usAntState) && (VOS_TRUE != usUETestMode))
    {
        AT_ERR_LOG("AT_QrySARReduction: ant state wrong");
        return AT_ERROR;
    }

    /* AT输出 */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstMtInfoCtx->usSarReduction);

    return AT_OK;
}

#if (FEATURE_ON==FEATURE_LTE)

VOS_UINT32  AT_QryRsrpCfgPara ( VOS_UINT8 ucIndex )
{
    NVIM_RSRP_CFG_STRU stRsrpCfg;
    VOS_UINT32 i =0;

    PS_MEM_SET(&stRsrpCfg, 0, sizeof(stRsrpCfg));

    if (g_enATE5RightFlag == AT_E5_RIGHT_FLAG_YES)
    {
        if (NV_OK != NVM_Read(EN_NV_ID_RSRP_CFG, &stRsrpCfg,sizeof(stRsrpCfg)))
        {
            (VOS_VOID)vos_printf("read RSRP_CFG NV fail!\n");
            return AT_ERROR;
        }

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        "%s:",
                                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        for (i = 0 ;i < 3; i++)
        {
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                        "(%d)%d,",
                                                         i+1,
                                                         stRsrpCfg.ssValue[i]);
        }

        gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                    "(4)%d",
                                                     stRsrpCfg.ssValue[3]);
    }
    else
    {
        return AT_ERROR;
    }


    return AT_OK;
}

VOS_UINT32  AT_QryRscpCfgPara ( VOS_UINT8 ucIndex )
{
    NVIM_RSCP_CFG_STRU stRscpCfg;
    VOS_UINT32 i =0;

    PS_MEM_SET(&stRscpCfg, 0, sizeof(stRscpCfg));

    if (g_enATE5RightFlag == AT_E5_RIGHT_FLAG_YES)
    {
        if (NV_OK != NVM_Read(EN_NV_ID_RSCP_CFG, &stRscpCfg,
                          sizeof(stRscpCfg)))
        {
            return AT_ERROR;
        }


        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                                "%s:",
                                                                 g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        for (i = 0; i < 3; i++)
        {
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr+ gstAtSendData.usBufLen,
                                                        "(%d)%d,",
                                                         i+1,
                                                         stRscpCfg.ssValue[i]);
        }

        gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr+ gstAtSendData.usBufLen,
                                                    "(4)%d",
                                                     stRscpCfg.ssValue[3]);
    }
    else
    {
        return AT_ERROR;
    }


    return AT_OK;
}

VOS_UINT32  AT_QryEcioCfgPara ( VOS_UINT8 ucIndex )
{
    NVIM_ECIO_CFG_STRU stEcioCfg;
    VOS_UINT32 i =0;

    PS_MEM_SET(&stEcioCfg, 0, sizeof(stEcioCfg));

    if (g_enATE5RightFlag == AT_E5_RIGHT_FLAG_YES)
    {
        if (NV_OK != NVM_Read(EN_NV_ID_ECIO_CFG, &stEcioCfg,
                          sizeof(stEcioCfg)))
        {
            (VOS_VOID)vos_printf("read ECIO_CFG NV fail!\n");
            return AT_ERROR;
        }

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                                  (TAF_CHAR *)pgucAtSndCodeAddr,
                                                                  (TAF_CHAR *)pgucAtSndCodeAddr,
                                                                  "%s:",
                                                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        for (i = 0 ;i < 3; i++)
        {
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr+ gstAtSendData.usBufLen,
                                                        "(%d)%d,",
                                                         i+1,
                                                         stEcioCfg.ssValue[i]);
        }

        gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr+ gstAtSendData.usBufLen,
                                                    "(4)%d",
                                                     stEcioCfg.ssValue[3]);
    }
    else
    {
        return AT_ERROR; /* 如果权限未打开，返回ERROR */
    }

    return AT_OK;
}

/* 删除AT_QryCellRoamPara */


VOS_UINT32 AT_QryPdprofmodPara(VOS_UINT8 ucIndex)
{
    return AT_OK;
}

VOS_UINT32 At_QrySfm(VOS_UINT8 ucIndex)
{
    VOS_UINT32  ulCustomVersion;


    ulCustomVersion = 0;

    if ( VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_SW_VERSION_FLAG, &ulCustomVersion, sizeof(ulCustomVersion)) )
    {
        return AT_ERROR;
    }
    else
    {

        /* AT命令与NV中存储的信息相反 */
        if (0 == ulCustomVersion)
        {

            /* 1 表示烧片版本 */
            ulCustomVersion = 1;

        }
        else
        {

            /* 0 表示正式版本 */
            ulCustomVersion = 0;
        }

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
            (TAF_CHAR *)pgucAtSndCodeAddr,"^SFM: %d", ulCustomVersion);

        return AT_OK;
    }
}
#endif



VOS_UINT32 AT_QryPhoneSimlockInfoPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* 通道检查 */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* 发送跨核消息到C核, 查询锁网锁卡信息 */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_PHONESIMLOCKINFO_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryPhoneSimlockInfoPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PHONESIMLOCKINFO_READ;
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QrySimlockDataReadPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* 通道检查 */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* 发送跨核消息到C核, 查询锁网锁卡信息 */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_SIMLOCKDATAREAD_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QrySimlockDataReadPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SIMLOCKDATAREAD_READ;
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryPhonePhynumPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* 通道检查 */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* 发送跨核消息到C核, 查询锁网锁卡信息 */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_PHONEPHYNUM_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryPhonePhynumPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PHONEPHYNUM_READ;
    return AT_WAIT_ASYNC_RETURN;
}



VOS_UINT32 AT_QryPortCtrlTmpPara(VOS_UINT8 ucIndex)
{
    OM_HSIC_PORT_STATUS_ENUM_UINT32     enOmHsicPortStatus;

    /* 通道检查 */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* 调用A核OM模块提供的接口OM_GetHsicPortStatus()读取端口状态的全局变量，并返回给AP */
    enOmHsicPortStatus = PPM_GetHsicPortStatus();

    if ( (OM_HSIC_PORT_STATUS_ON != enOmHsicPortStatus)
       && (OM_HSIC_PORT_STATUS_OFF != enOmHsicPortStatus) )
    {
        return AT_ERROR;
    }


    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    enOmHsicPortStatus);

    return AT_OK;
}


VOS_UINT32 AT_QryPortAttribSetPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* 通道检查 */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* 发送跨核消息到C核，查询端口锁状态 */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_PORTATTRIBSET_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryPortAttribSetPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PORTATTRIBSET_READ;
    return AT_WAIT_ASYNC_RETURN;
}

#if (VOS_WIN32 == VOS_OS_VER)

VOS_UINT32 At_QryTinTypeStub(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucTinType;

#if (FEATURE_ON == FEATURE_LTE)
    ucTinType = NAS_GetTinType();
#endif
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     ucTinType);
    return AT_OK;

}


VOS_UINT32 AT_QryPsRegisterContainDrxStub(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucDrx;

    ucDrx = NAS_GetPsRegContainDrx();
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     ucDrx);
    return AT_OK;

}


#endif



VOS_UINT32 AT_QryCposrPara(VOS_UINT8 ucIndex)
{
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx = VOS_NULL_PTR;

    /* 通道检查 */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    pstAgpsCtx = AT_GetModemAgpsCtxAddrFromClientId(ucIndex);

    /* 打印+CPOSR主动上报控制当前状态 */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstAgpsCtx->enCposrReport);

    return AT_OK;
}


VOS_UINT32 AT_QryXcposrPara(VOS_UINT8 ucIndex)
{
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx = VOS_NULL_PTR;

    /* 通道检查 */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    pstAgpsCtx = AT_GetModemAgpsCtxAddrFromClientId(ucIndex);

    /* 打印^XCPOSR主动上报控制当前状态 */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstAgpsCtx->enXcposrReport);

    return AT_OK;
}


VOS_UINT32 AT_QryCPsErrPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      AT_PS_GetPsCallErrCause(ucIndex));

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_QryCmutPara(VOS_UINT8 ucIndex)
{
    if (VOS_OK != APP_VC_GetMuteStatus(gastAtClientTab[ucIndex].usClientId, 0))
    {
        return AT_ERROR;
    }

    /* 设置当前操作类型 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMUT_READ;

    /* 返回命令处理挂起状态 */
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryCCsErrPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      AT_GetCsCallErrCause(ucIndex));

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}



VOS_UINT32 At_QryCerssiPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    ulResult = TAF_MMA_QryCerssiReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, gastAtClientTab[ucIndex].opId);

    /* 执行命令操作 */
    if (VOS_TRUE == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CERSSI_READ;

        /* 返回命令处理挂起状态 */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

#if(FEATURE_ON == FEATURE_LTE)


VOS_UINT32 At_QryCecellidPara(VOS_UINT8 ucIndex)
{
    /* 调用L 提供接口 */
    return At_QryCellIdPara(ucIndex);
}
#endif



VOS_UINT32 AT_QryCbgPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* AT 给VC 发送模式查询请求消息 */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      APP_VC_MSG_FOREGROUND_QRY,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_WUEPS_PID_VC);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryCbgPara: send Msg fail.");
        return AT_ERROR;
    }

    /* 设置当前操作类型 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CBG_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryAcInfoPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* 发消息给MMA获取当前UE的位置信息 */
    ulResult = TAF_MMA_QryAcInfoReq(WUEPS_PID_AT,
                                    gastAtClientTab[ucIndex].usClientId,
                                    0);
    /* 执行命令操作 */
    if (VOS_TRUE == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ACINFO_READ;

        /* 返回命令处理挂起状态 */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}



VOS_UINT32 AT_QryCLteRoamAllowPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                                       ucLteRoamAllow;
    NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU    stNvimLteRoamAllowedFlg;
    VOS_UINT32                                      ulLength;

    ulLength = 0;


    /* 局部变量初始化 */
    ucLteRoamAllow          = VOS_FALSE;
    stNvimLteRoamAllowedFlg.ucLteRoamAllowedFlg = VOS_FALSE;

    (VOS_VOID)NV_GetLength(en_NV_Item_Lte_Internation_Roam_Config, &ulLength);

    /* 读取NV, 该NV的结构为 NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU, 只读取第1个字节 */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_Lte_Internation_Roam_Config,
                         &stNvimLteRoamAllowedFlg,
                         ulLength))
    {
        AT_WARN_LOG("AT_QryCLteRoamAllowPara(): en_NV_Item_Lte_Internation_Roam_Config NV_ReadEx Error");
        return AT_ERROR;
    }


    /* 容错处理, NV中值为VOS_FALSE时即不允许漫游, 为其它值时即为允许漫游 */
    if (VOS_FALSE == stNvimLteRoamAllowedFlg.ucLteRoamAllowedFlg)
    {
        ucLteRoamAllow = VOS_FALSE;
    }
    else
    {
        ucLteRoamAllow = VOS_TRUE;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     ucLteRoamAllow);
    return AT_OK;
}



VOS_UINT32 At_QryMmPlmnInfoPara(VOS_UINT8 ucIndex)
{
    if(VOS_TRUE == TAF_MMA_QryMMPlmnInfoReq(WUEPS_PID_AT,
                                            gastAtClientTab[ucIndex].usClientId,
                                            0))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MMPLMNINFO_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 At_QryEonsUcs2Para(VOS_UINT8 ucIndex)
{
    if(VOS_TRUE == TAF_MMA_QryEonsUcs2Req(
                    WUEPS_PID_AT,
                    gastAtClientTab[ucIndex].usClientId,
                    0))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_EONSUCS2_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 At_QryPlmnPara(VOS_UINT8 ucIndex)
{
    if(VOS_TRUE == TAF_MMA_QryPlmnReq(WUEPS_PID_AT,
                                      gastAtClientTab[ucIndex].usClientId,
                                      0))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PLMN_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}


VOS_UINT32 At_QryXlemaPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* 发送消息 */
    ulRst = MN_CALL_SendAppRequest(MN_CALL_APP_XLEMA_REQ,
                                   gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   0,
                                   TAF_NULL_PTR);

    if (MN_ERR_NO_ERROR != ulRst)
    {
        AT_WARN_LOG("At_QryXlemaPara: MN_CALL_SendAppRequest fail.");
        return AT_ERROR;
    }

    /* 设置结束直接返回OK */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_XLEMA_QRY;
    return AT_WAIT_ASYNC_RETURN;

}


VOS_UINT32 AT_QryBodySarOnPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     g_enAtBodySarState);
    return AT_OK;
}


VOS_UINT32 AT_FillBodySarWcdmaQryPara(
    MTA_BODY_SAR_PARA_STRU             *pstBodySarPara,
    AT_BODYSARWCDMA_SET_PARA_STRU      *pstBodySarWcdmaPara)
{
    VOS_UINT8                           ucLoop1;
    VOS_UINT8                           ucLoop2;
    AT_NV_WG_RF_MAIN_BAND_STRU          stWGBand;
    VOS_UINT32                          ulTmpBand;

    PS_MEM_SET(&stWGBand, 0, sizeof(stWGBand));
    ulTmpBand       = 0;

    /* 获取WCDMA Band能力值 */
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                            en_NV_Item_WG_RF_MAIN_BAND,
                            &stWGBand,
                            sizeof(stWGBand)))
    {
        AT_ERR_LOG("AT_FillBodySarWcdmaQryPara: Read NV fail!");
        return VOS_ERR;
    }

    for (ucLoop1 = 0; ucLoop1 < pstBodySarPara->usWBandNum; ucLoop1++)
    {
        for (ucLoop2 = 0; ucLoop2 < pstBodySarWcdmaPara->ucParaNum; ucLoop2++)
        {
            if (pstBodySarPara->astWBandPara[ucLoop1].sPower == pstBodySarWcdmaPara->asPower[ucLoop2])
            {
                break;
            }
        }

        if (ucLoop2 == pstBodySarWcdmaPara->ucParaNum)
        {
            pstBodySarWcdmaPara->ucParaNum++;
            pstBodySarWcdmaPara->asPower[ucLoop2] =pstBodySarPara->astWBandPara[ucLoop1].sPower;
        }

        pstBodySarWcdmaPara->aulBand[ucLoop2]   |= 0x00000001 << (pstBodySarPara->astWBandPara[ucLoop1].enBand - 1);
        ulTmpBand                               |= pstBodySarWcdmaPara->aulBand[ucLoop2];
    }

    /* 剩余未设置的频段返回默认值 */
    ulTmpBand = stWGBand.unWcdmaBand.ulBand & (~ulTmpBand);
    if (0 != ulTmpBand)
    {
        pstBodySarWcdmaPara->aulBand[pstBodySarWcdmaPara->ucParaNum] = ulTmpBand;
        pstBodySarWcdmaPara->asPower[pstBodySarWcdmaPara->ucParaNum] = AT_WCDMA_BAND_DEFAULT_POWER;
        pstBodySarWcdmaPara->ucParaNum++;
    }

    return VOS_OK;
}


VOS_UINT32 AT_QryBodySarWcdmaPara(VOS_UINT8 ucIndex)
{
    MTA_BODY_SAR_PARA_STRU              stBodySarPara;
    AT_BODYSARWCDMA_SET_PARA_STRU       stBodySarWcdmaPara;
    VOS_UINT8                           ucLoop;
    VOS_UINT16                          usLength;

    PS_MEM_SET(&stBodySarPara, 0, sizeof(stBodySarPara));
    PS_MEM_SET(&stBodySarWcdmaPara, 0, sizeof(stBodySarWcdmaPara));
    usLength        = 0;

    /* 从NV项中读取Body SAR功率门限值 */
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                            en_NV_Item_BODY_SAR_PARA,
                            &stBodySarPara,
                            sizeof(stBodySarPara)))
    {
        AT_ERR_LOG("AT_QryBodySarWcdmaPara: Read NV fail!");
        return AT_ERROR;
    }

    /* 从Body SAR参数结构体填充^BODYSARWCDMA命令参数结构体 */
    if (VOS_OK != AT_FillBodySarWcdmaQryPara(&stBodySarPara, &stBodySarWcdmaPara))
    {
        AT_ERR_LOG("AT_QryBodySarWcdmaPara: AT_FillBodySarWcdmaQryPara fail!");
        return AT_ERROR;
    }

    /* 打印命令名 */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* 打印WCDMA频段Body SAR参数 */
    if (1 == stBodySarWcdmaPara.ucParaNum)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "(%d,%08X)",
                                           stBodySarWcdmaPara.asPower[0],
                                           AT_RF_BAND_ANY);

        gstAtSendData.usBufLen = usLength;

        return AT_OK;
    }

    for (ucLoop = 0; ucLoop < stBodySarWcdmaPara.ucParaNum; ucLoop++)
    {
        if (0 != ucLoop)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                               ",");
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "(%d,%08X)",
                                           stBodySarWcdmaPara.asPower[ucLoop],
                                           stBodySarWcdmaPara.aulBand[ucLoop]);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_FillBodySarGsmDefaultPower(
    MTA_BODY_SAR_PARA_STRU             *pstBodySarPara)
{
    VOS_UINT32                          ulGBandCapa;
    VOS_UINT32                          ulTmpBand;

    ulGBandCapa     = 0;
    ulTmpBand       = 0;

    /* 获取GSM Band能力值 */
    if (VOS_OK != AT_GetGsmBandCapa(&ulGBandCapa))
    {
        AT_ERR_LOG("AT_FillBodySarGsmDefaultPower: AT_GetGsmBandCapa fail!");
        return VOS_ERR;
    }

    ulTmpBand = ulGBandCapa & (~pstBodySarPara->ulGBandMask);

    if (0 != (AT_BODY_SAR_GBAND_GPRS_850_MASK & ulTmpBand))
    {
        pstBodySarPara->ulGBandMask |= AT_BODY_SAR_GBAND_GPRS_850_MASK;
        pstBodySarPara->astGBandPara[AT_GSM_850].sGPRSPower = AT_GSM_GPRS_850_DEFAULT_POWER;
    }

    if (0 != (AT_BODY_SAR_GBAND_EDGE_850_MASK & ulTmpBand))
    {
        pstBodySarPara->ulGBandMask |= AT_BODY_SAR_GBAND_EDGE_850_MASK;
        pstBodySarPara->astGBandPara[AT_GSM_850].sEDGEPower = AT_GSM_EDGE_850_DEFAULT_POWER;
    }

    if (0 != (AT_BODY_SAR_GBAND_GPRS_900_MASK & ulTmpBand))
    {
        pstBodySarPara->ulGBandMask |= AT_BODY_SAR_GBAND_GPRS_900_MASK;
        pstBodySarPara->astGBandPara[AT_GSM_900].sGPRSPower = AT_GSM_GPRS_900_DEFAULT_POWER;
    }

    if (0 != (AT_BODY_SAR_GBAND_EDGE_900_MASK & ulTmpBand))
    {
        pstBodySarPara->ulGBandMask |= AT_BODY_SAR_GBAND_EDGE_900_MASK;
        pstBodySarPara->astGBandPara[AT_GSM_900].sEDGEPower = AT_GSM_EDGE_900_DEFAULT_POWER;
    }

    if (0 != (AT_BODY_SAR_GBAND_GPRS_1800_MASK & ulTmpBand))
    {
        pstBodySarPara->ulGBandMask |= AT_BODY_SAR_GBAND_GPRS_1800_MASK;
        pstBodySarPara->astGBandPara[AT_GSM_1800].sGPRSPower = AT_GSM_GPRS_1800_DEFAULT_POWER;
    }

    if (0 != (AT_BODY_SAR_GBAND_EDGE_1800_MASK & ulTmpBand))
    {
        pstBodySarPara->ulGBandMask |= AT_BODY_SAR_GBAND_EDGE_1800_MASK;
        pstBodySarPara->astGBandPara[AT_GSM_1800].sEDGEPower = AT_GSM_EDGE_1800_DEFAULT_POWER;
    }

    if (0 != (AT_BODY_SAR_GBAND_GPRS_1900_MASK & ulTmpBand))
    {
        pstBodySarPara->ulGBandMask |= AT_BODY_SAR_GBAND_GPRS_1900_MASK;
        pstBodySarPara->astGBandPara[AT_GSM_1900].sGPRSPower = AT_GSM_GPRS_1900_DEFAULT_POWER;
    }

    if (0 != (AT_BODY_SAR_GBAND_EDGE_1900_MASK & ulTmpBand))
    {
        pstBodySarPara->ulGBandMask |= AT_BODY_SAR_GBAND_EDGE_1900_MASK;
        pstBodySarPara->astGBandPara[AT_GSM_1900].sEDGEPower = AT_GSM_EDGE_1900_DEFAULT_POWER;
    }

    return VOS_OK;
}


VOS_VOID AT_FillBodySarGsmByModulationMode(
    MTA_BODY_SAR_PARA_STRU             *pstBodySarPara,
    VOS_UINT8                           ucModulationOffset,
    AT_BODYSARGSM_SET_PARA_STRU        *pstBodySarGsmPara)
{
    VOS_UINT8                           ucLoop1;
    VOS_UINT8                           ucLoop2;

    for (ucLoop1 = AT_GSM_850; ucLoop1 < AT_GSM_BAND_BUTT; ucLoop1++)
    {
        for (ucLoop2 = 0; ucLoop2 < pstBodySarGsmPara->ucParaNum; ucLoop2++)
        {
            if (AT_GSM_GPRS_BAND_OFFSET == ucModulationOffset)
            {
                if (pstBodySarPara->astGBandPara[ucLoop1].sGPRSPower == pstBodySarGsmPara->asPower[ucLoop2])
                {
                    break;
                }
            }
            else
            {
                if (pstBodySarPara->astGBandPara[ucLoop1].sEDGEPower == pstBodySarGsmPara->asPower[ucLoop2])
                {
                    break;
                }
            }
        }

        if (ucLoop2 == pstBodySarGsmPara->ucParaNum)
        {
            pstBodySarGsmPara->ucParaNum++;
            if (AT_GSM_GPRS_BAND_OFFSET == ucModulationOffset)
            {
                pstBodySarGsmPara->asPower[ucLoop2] = pstBodySarPara->astGBandPara[ucLoop1].sGPRSPower;
            }
            else
            {
                pstBodySarGsmPara->asPower[ucLoop2] = pstBodySarPara->astGBandPara[ucLoop1].sEDGEPower;
            }
        }

        pstBodySarGsmPara->aulBand[ucLoop2]   |= 0x00000001 << (ucLoop1 + ucModulationOffset);
    }

    return;
}


VOS_UINT32 AT_QryBodySarGsmPara(VOS_UINT8 ucIndex)
{
    MTA_BODY_SAR_PARA_STRU              stBodySarPara;
    AT_BODYSARGSM_SET_PARA_STRU         stBodySarGsmPara;
    VOS_UINT8                           ucLoop;
    VOS_UINT16                          usLength;

    PS_MEM_SET(&stBodySarPara, 0, sizeof(stBodySarPara));
    PS_MEM_SET(&stBodySarGsmPara, 0, sizeof(stBodySarGsmPara));
    usLength        = 0;

    /* 从NV项中读取Body SAR功率门限值 */
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                            en_NV_Item_BODY_SAR_PARA,
                            &stBodySarPara,
                            sizeof(stBodySarPara)))
    {
        AT_ERR_LOG("AT_QryBodySarGsmPara: Read NV fail!");
        return AT_ERROR;
    }

    /* 填充GSM频段Body SAR参数默认值 */
    if (VOS_OK != AT_FillBodySarGsmDefaultPower(&stBodySarPara))
    {
        AT_ERR_LOG("AT_QryBodySarGsmPara: AT_FillBodySarGsmDefaultPower fail!");
        return AT_ERROR;
    }

    /* 从Body SAR参数结构体填充^BODYSARGSM命令参数结构体 */
    /* GPRS调制方式 */
    AT_FillBodySarGsmByModulationMode(&stBodySarPara, AT_GSM_GPRS_BAND_OFFSET, &stBodySarGsmPara);

    /* EDGE调制方式 */
    AT_FillBodySarGsmByModulationMode(&stBodySarPara, AT_GSM_EDGE_BAND_OFFSET, &stBodySarGsmPara);

    /* 打印命令名 */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* 打印GSM频段Body SAR参数 */
    if (1 == stBodySarGsmPara.ucParaNum)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "(%d,%08X)",
                                           stBodySarGsmPara.asPower[0],
                                           AT_RF_BAND_ANY);

        gstAtSendData.usBufLen = usLength;

        return AT_OK;
    }

    for (ucLoop = 0; ucLoop < stBodySarGsmPara.ucParaNum; ucLoop++)
    {
        if (0 != ucLoop)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                               ",");
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "(%d,%08X)",
                                           stBodySarGsmPara.asPower[ucLoop],
                                           stBodySarGsmPara.aulBand[ucLoop]);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}



VOS_UINT32 At_QryIMEIVerifyPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* 发送消息 ID_AT_MTA_IMEI_VERIFY_QRY_REQ 给 MTA 处理， */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_MTA_IMEI_VERIFY_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_IMEI_VERIFY_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}


VOS_UINT32 AT_QryNCellMonitorPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* 给MTA发送^NCELLMONITOR查询请求 */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_NCELL_MONITOR_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NCELL_MONITOR_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryUserSrvStatePara(VOS_UINT8 ucIndex)
{
    if(VOS_TRUE == TAF_MMA_QryUserSrvStateReq(WUEPS_PID_AT,
                                              gastAtClientTab[ucIndex].usClientId,
                                              0))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_USER_SRV_STATE_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}



VOS_UINT32 AT_QryRefclkfreqPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* 通道检查 */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* 发送跨核消息到C核, 查询GPS参考时钟状态 */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_REFCLKFREQ_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("At_QryRefclkfreqPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_REFCLKFREQ_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 At_QryHandleDect(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;
    VOS_UINT8                          *pucSystemAppConfig;

    /* 读取NV项中当前产品形态 */
    pucSystemAppConfig = AT_GetSystemAppConfigAddr();

#ifndef DMT
    /* 非ANDROID系统不支持 */
    if ( SYSTEM_APP_ANDROID != *pucSystemAppConfig)
    {
        return AT_CMD_NOT_SUPPORT;
    }
#endif

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* 发送消息 ID_AT_MTA_HANDLEDECT_QRY_REQ 给MTA处理 */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   At_GetOpId(),
                                   ID_AT_MTA_HANDLEDECT_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HANDLEDECT_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}


VOS_UINT32 AT_QryLogNvePara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulEnable;
    VOS_UINT32                          ulTimeout;
    VOS_UINT32                          ulBufferSize;
    SOCP_ENC_DST_BUF_LOG_CFG_STRU       stLogCfg = {0};

    ulEnable                            = 0;
    ulTimeout                           = 0;
    ulBufferSize                        = 0;


    ulResult = mdrv_socp_get_sd_logcfg(&stLogCfg);

    if (VOS_OK != ulResult)
    {
        return AT_ERROR;
    }

    ulEnable = stLogCfg.logOnFlag;
    ulTimeout= stLogCfg.ulCurTimeout;
    ulBufferSize = stLogCfg.BufferSize;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %d,%d,%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      ulEnable,
                                      ulTimeout,
                                      ulBufferSize);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

#if (FEATURE_ON == FEATURE_IMS)

VOS_UINT32 AT_QryCiregPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* 发送消息 */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_IMSA_CIREG_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   PS_PID_IMSA);

    if (TAF_SUCCESS != ulRst)
    {
        AT_WARN_LOG("AT_QryCiregPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 查询结束挂起通道 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CIREG_QRY;
    return AT_WAIT_ASYNC_RETURN;

}


VOS_UINT32 AT_QryCirepPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* 发送消息 */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_IMSA_CIREP_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   PS_PID_IMSA);

    if (TAF_SUCCESS != ulRst)
    {
        AT_WARN_LOG("AT_QryCirepPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 查询结束挂起通道 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CIREP_QRY;
    return AT_WAIT_ASYNC_RETURN;

}

#endif


VOS_UINT32 AT_QryClccPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* 发消息到C核获取当前所有通话信息 */
    ulRet = MN_CALL_GetCallInfos(gastAtClientTab[ucIndex].usClientId,
                                 gastAtClientTab[ucIndex].opId,
                                 0);
    if (VOS_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryClccPara: MN_CALL_GetCallInfos fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLCC_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

#if (FEATURE_ON == FEATURE_IMS)

VOS_UINT32 AT_QryClccEconfInfo(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* 发消息到C核获取当前所有通话信息 */
    ulRet = MN_CALL_SendAppRequest(TAF_CALL_APP_GET_ECONF_CALLED_INFO_REQ,
                                   gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   0,
                                   VOS_NULL_PTR);
    if (VOS_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryClccEconfInfo: MN_CALL_SendAppRequest fail.");

        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLCCECONF_QRY;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryEconfErrPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          i;
    VOS_UINT16                          usLength;
    AT_MODEM_CC_CTX_STRU               *pstCcCtx     = VOS_NULL_PTR;
    AT_ECONF_INFO_STRU                 *pstEconfInfo = VOS_NULL_PTR;
    VOS_UINT8                           aucAsciiNum[MN_CALL_MAX_CALLED_ASCII_NUM_LEN + 1];
    VOS_UINT8                           ucNumOfCalls;
    VOS_UINT8                           ucErrNum;

    ucErrNum     = 0;
    usLength     = 0;
    pstCcCtx     = AT_GetModemCcCtxAddrFromClientId(ucIndex);
    pstEconfInfo = &(pstCcCtx->stEconfInfo);
    ucNumOfCalls = pstEconfInfo->ucNumOfCalls;
    PS_MEM_SET(aucAsciiNum, 0, sizeof(aucAsciiNum));

    for (i = 0; ((i < ucNumOfCalls) && (i < TAF_CALL_MAX_ECONF_CALLED_NUM)); i++)
    {
        /* 查询错误原因值 */
        if ((0 != pstEconfInfo->astCallInfo[i].stCallNumber.ucNumLen)
         && (TAF_CS_CAUSE_SUCCESS != pstEconfInfo->astCallInfo[i].enCause))
        {
            /* <CR><LF> */
            if (0 != ucErrNum)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%s",
                                                   gaucAtCrLf);
            }

            AT_BcdNumberToAscii(pstEconfInfo->astCallInfo[i].stCallNumber.aucBcdNum,
                                pstEconfInfo->astCallInfo[i].stCallNumber.ucNumLen,
                                (VOS_CHAR *)aucAsciiNum);

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s: \"%s\",%d,%d",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               aucAsciiNum,
                                               (pstEconfInfo->astCallInfo[i].stCallNumber.enNumType | AT_NUMBER_TYPE_EXT),
                                               pstEconfInfo->astCallInfo[i].enCause);

            ucErrNum++;
        }
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}


VOS_UINT32 AT_QryImsSwitchPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* AT 给MMA 发送查询请求消息 */
    ulRst = TAF_MMA_QryImsSwitchReq(WUEPS_PID_AT,
                                    gastAtClientTab[ucIndex].usClientId,
                                    0);
    if (VOS_TRUE == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_IMS_SWITCH_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 AT_QryCevdpPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* AT 给MMA 发送查询请求消息 */
    ulRst = TAF_MMA_QryVoiceDomainReq(WUEPS_PID_AT,
                                      gastAtClientTab[ucIndex].usClientId,
                                      0);
    if (VOS_TRUE == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_VOICE_DOMAIN_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
#endif


VOS_UINT32 AT_QryUserCfgOPlmnPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* 发送消息 ID_AT_MTA_HANDLEDECT_QRY_REQ 给MTA处理 */
    ulRst = TAF_MMA_QryEOPlmnReq(WUEPS_PID_AT,
                                 gastAtClientTab[ucIndex].usClientId,
                                 0);
    if (VOS_TRUE == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_EOPLMN_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

#if (FEATURE_ON == FEATURE_AT_HSUART)

VOS_UINT32 AT_QryIprPara(VOS_UINT8 ucIndex)
{
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;
    VOS_UINT16                          usLength;

    /* 初始化 */
    pstUartCtx = AT_GetUartCtxAddr();
    usLength   = 0;

    /* 通道检查 */
    if (VOS_TRUE != AT_CheckHsUartUser(ucIndex))
    {
        return AT_OK;
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %u",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      pstUartCtx->stPhyConfig.enBaudRate);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_QryIcfPara(VOS_UINT8 ucIndex)
{
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;
    VOS_UINT16                          usLength;

    /* 初始化 */
    pstUartCtx = AT_GetUartCtxAddr();
    usLength   = 0;

    /* 通道检查 */
    if (VOS_TRUE != AT_CheckHsUartUser(ucIndex))
    {
        return AT_OK;
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %d,%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      pstUartCtx->stPhyConfig.stFrame.enFormat,
                                      pstUartCtx->stPhyConfig.stFrame.enParity);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_QryIfcPara(VOS_UINT8 ucIndex)
{
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;
    VOS_UINT16                          usLength;

    /* 初始化 */
    pstUartCtx = AT_GetUartCtxAddr();
    usLength   = 0;

    /* 通道检查 */
    if (VOS_TRUE != AT_CheckHsUartUser(ucIndex))
    {
        return AT_OK;
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %d,%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      pstUartCtx->stFlowCtrl.enDceByDte,
                                      pstUartCtx->stFlowCtrl.enDteByDce);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}
#endif


VOS_UINT32 AT_QryAntSwitchPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   At_GetOpId(),
                                   DRV_AGENT_ANTSWITCH_QRY_REQ,
                                   VOS_NULL,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ANTSWITCH_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}



VOS_UINT32 AT_QryModemStatusPara(VOS_UINT8 ucIndex)
{
    return AT_OK;
}


VOS_UINT32 AT_QryRATCombinePara(VOS_UINT8 ucIndex)
{
    TAF_NV_LC_CTRL_PARA_STRU            stNVData;
    VOS_UINT16                          usLength;
    VOS_UINT8                           usRatMode;
    MODEM_ID_ENUM_UINT16                enModemId;

    PS_MEM_SET(&stNVData, 0x0, sizeof(stNVData));

    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &enModemId))
    {
        AT_ERR_LOG("AT_QryRATCombinePara: Get modem id fail.");

        return AT_ERROR;
    }

    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_LC_Ctrl_PARA, &stNVData, sizeof(TAF_NV_LC_CTRL_PARA_STRU)))
    {
        AT_ERR_LOG("AT_QryRATCombinePara: Get en_NV_Item_LC_Ctrl_PARA id fail.");

        return AT_ERROR;
    }

    if (VOS_TRUE != stNVData.ucLCEnableFlg)
    {
        return AT_CME_OPERATION_NOT_ALLOWED;
    }

    if (TAF_NVIM_LC_RAT_COMBINED_CL == stNVData.enRatCombined)
    {
        usRatMode = 0;
    }
    else if (TAF_NVIM_LC_RAT_COMBINED_GUL == stNVData.enRatCombined)
    {
        usRatMode = 1;
    }
    else
    {
        return AT_ERROR;
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      usRatMode);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}



VOS_UINT32 AT_QryMipiClkValue(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* AT 给MTA 发送查询请求消息 */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_MIPICLK_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryMipiClkValue: send Msg fail.");
        return AT_ERROR;
    }

    /* 设置当前操作类型 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MIPI_CLK_QRY;

    return AT_WAIT_ASYNC_RETURN;

}

VOS_VOID Show_Time(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

    (VOS_VOID)vos_printf("\r\nTime:\r\n");
    (VOS_VOID)vos_printf("ucIeFlg: %d\r\n",pstNetCtx->stTimeInfo.ucIeFlg);
    (VOS_VOID)vos_printf("cLocalTimeZone: %d\r\n",pstNetCtx->stTimeInfo.cLocalTimeZone);
    (VOS_VOID)vos_printf("ucDST: %d\r\n",pstNetCtx->stTimeInfo.ucDST);
    (VOS_VOID)vos_printf("ucLSAID: %d\r\n",pstNetCtx->stTimeInfo.ucLSAID);
    (VOS_VOID)vos_printf("cTimeZone: %d\r\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.cTimeZone);
    (VOS_VOID)vos_printf("ucYear: %d\r\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucYear);
    (VOS_VOID)vos_printf("ucMonth: %d\r\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucMonth);
    (VOS_VOID)vos_printf("ucDay: %d\r\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucDay);
    (VOS_VOID)vos_printf("ucHour: %d\r\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucHour);
    (VOS_VOID)vos_printf("ucMinute: %d\r\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucMinute);
    (VOS_VOID)vos_printf("ucSecond: %d\r\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucSecond);

    return;
}

VOS_UINT32 AT_QryCclkPara(VOS_UINT8 ucIndex)
{
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_INT8                            cTimeZone;

    enModemId = MODEM_ID_0;
    cTimeZone = AT_INVALID_TZ_VALUE;

    ulRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_QryCclkPara: Get modem id fail.");
        return AT_ERROR;
    }

    pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

    /*时间显示格式: +cclk: "yy/mm/dd,hh:mm:ss(+/-)zz" */
    if (NAS_MM_INFO_IE_UTLTZ == (pstNetCtx->stTimeInfo.ucIeFlg & NAS_MM_INFO_IE_UTLTZ))
    {
        /* 获得时区 */
        cTimeZone   = pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.cTimeZone;

        /* 若已经获得 Local time zone,则时区修改为 Local time zone */
        if (NAS_MM_INFO_IE_LTZ == (pstNetCtx->stTimeInfo.ucIeFlg & NAS_MM_INFO_IE_LTZ))
        {
            cTimeZone   = pstNetCtx->stTimeInfo.cLocalTimeZone;
        }

        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            "%s: \"%02d/%02d/%02d,%02d:%02d:%2d",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucYear,
                                            pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucMonth,
                                            pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucDay,
                                            pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucHour,
                                            pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucMinute,
                                            pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucSecond);

        if (cTimeZone >= 0)
        {
            gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                (VOS_CHAR *)pgucAtSndCodeAddr,
                (VOS_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                "+%02d\"",
                cTimeZone);

        }
        else
        {
            gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                (VOS_CHAR *)pgucAtSndCodeAddr,
                (VOS_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                "-%02d\"",
                -cTimeZone);

        }

        return AT_OK;
    }

    return AT_CME_NO_NETWORK_SERVICE;
}

#if (FEATURE_ON == FEATURE_HUAWEI_VP)

VOS_UINT32 AT_QryVoicePreferPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRslt;

    /* 调用MN_FillAndSndAppReqMsg()，等待RABM的回复 */
    ulRslt = AT_SndQryVoicePrefer(gastAtClientTab[ucIndex].usClientId,gastAtClientTab[ucIndex].opId);
    if (VOS_OK == ulRslt)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_VOICEPREFER_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}
#endif
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32 AT_QryCLocInfo(VOS_UINT8 ucIndex)
{

    VOS_UINT32                          ulRet;

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* 向MMA发消息请求运营商信息 */
    ulRet = TAF_MMA_QryCLocInfoReq(WUEPS_PID_AT,
                                   gastAtClientTab[ucIndex].usClientId,
                                   0);
    if (VOS_TRUE != ulRet)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLOCINFO_QRY;

    return AT_WAIT_ASYNC_RETURN;

}
#endif



VOS_UINT32 AT_QryEmcCallBack( VOS_UINT8 ucIndex  )
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulRet;

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRet = TAF_MMA_QryCurrEmcCallBackMode(WUEPS_PID_AT,
                                           gastAtClientTab[ucIndex].usClientId,
                                           0);
    if (VOS_TRUE != ulRet)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_EMCCBM_QRY;

    return AT_WAIT_ASYNC_RETURN;
#else
        return AT_ERROR;
#endif
}

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA)&&(FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT))


VOS_UINT32 AT_QryEncryptCallCap( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRet;

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRet = TAF_XCALL_QryEncryptCallCap ( WUEPS_PID_AT,
                                          gastAtClientTab[ucIndex].usClientId,
                                          0);
    if (VOS_OK != ulRet)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ECCAP_QRY;

    return AT_WAIT_ASYNC_RETURN;
}
#if  (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)


VOS_UINT32 AT_QryEncryptCallRandom( VOS_UINT8 ucIndex )
{

    VOS_UINT32                          ulRet;

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRet = TAF_XCALL_QryEncryptCallRandom (WUEPS_PID_AT,
                                            gastAtClientTab[ucIndex].usClientId,
                                            0);
    if (VOS_OK != ulRet)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ECRANDOM_QRY;

    return AT_WAIT_ASYNC_RETURN;

}

VOS_UINT32 AT_QryEncryptCallKmc( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRet;

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRet = TAF_XCALL_QryEncryptCallKmc (WUEPS_PID_AT,
                                         gastAtClientTab[ucIndex].usClientId,
                                         0);
    if (VOS_OK != ulRet)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ECKMC_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

VOS_UINT32  AT_QryEccTestMode( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRet;

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRet = TAF_XCALL_QryEncryptCallTestMode (WUEPS_PID_AT,
                                              gastAtClientTab[ucIndex].usClientId,
                                              0);
    if (VOS_OK != ulRet)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ECCTEST_QRY;

    return AT_WAIT_ASYNC_RETURN;
}
#endif
#endif
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32 AT_QryPrivacyModePreferred(VOS_UINT8 ucIndex)
{
    /* 检查当前命令操作类型 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }


    if (VOS_OK == TAF_XCALL_QryPrivacyModePreferred(WUEPS_PID_AT,
                                                    gastAtClientTab[ucIndex].usClientId,
                                                    0))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPMP_QRY;

        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}
#endif


VOS_UINT32 AT_QryCFreqLockInfo(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    if (VOS_TRUE ==  TAF_MMA_ProcCFreqLockQryReq(WUEPS_PID_AT,
                                                 gastAtClientTab[ucIndex].usClientId,
                                                 0))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CFREQLOCK_QRY;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */
    }
    else
    {
        return AT_ERROR;
    }
#else
    return AT_ERROR;
#endif

}

VOS_UINT32 AT_QryCdmaCsqPara(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    if (VOS_TRUE == TAF_MMA_ProcCdmaCsqQryReq(WUEPS_PID_AT,
                                               gastAtClientTab[ucIndex].usClientId,
                                               0))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CDMACSQ_QRY;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */
    }
    else
    {
        return AT_ERROR;
    }
#else
   return AT_ERROR;
#endif

}


VOS_UINT32 AT_QryTTYModePara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    if(AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* AT 给VC 发送模式查询请求消息 */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      APP_VC_MSG_QRY_TTYMODE_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_WUEPS_PID_VC);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryTTYModePara: send Msg fail.");
        return AT_ERROR;
    }

    /* 设置当前操作类型 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_TTYMODE_READ;

    return AT_WAIT_ASYNC_RETURN;
}



VOS_UINT32 AT_QryCtaPara(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* 执行命令操作 */
    if (VOS_OK != TAF_PS_GetCtaInfo(WUEPS_PID_AT,
                                    gastAtClientTab[ucIndex].usClientId,
                                    0))
    {
        return AT_ERROR;
    }

    /* 设置当前操作类型 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CTA_QRY;

    /* 返回命令处理挂起状态 */
    return AT_WAIT_ASYNC_RETURN;

#else
    return AT_ERROR;
#endif

}



VOS_UINT32 At_QryRatRfSwitch(VOS_UINT8 ucIndex)
{
    NAS_NV_TRI_MODE_ENABLE_STRU  stTriModeEnableStru;
    NAS_NV_TRI_MODE_FEM_PROFILE_ID_STRU  stTriModeFemProfileIdStru;

    PS_MEM_SET(&stTriModeEnableStru, 0x0, sizeof(stTriModeEnableStru));
    PS_MEM_SET(&stTriModeFemProfileIdStru, 0x0, sizeof(stTriModeFemProfileIdStru));

    if(AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }


    /* 读取NV项 */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_TRI_MODE_ENABLE, &stTriModeEnableStru, sizeof(stTriModeEnableStru)))
    {
        AT_WARN_LOG("At_QryRatRfSwitch:read en_NV_Item_TRI_MODE_ENABLE failed");
        return AT_ERROR;
    }

    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_TRI_MODE_FEM_PROFILE_ID, &stTriModeFemProfileIdStru, sizeof(stTriModeFemProfileIdStru)))
    {
        AT_WARN_LOG("At_QryRatRfSwitch:read en_NV_Item_TRI_MODE_FEM_PROFILE_ID failed");
        return AT_ERROR;
    }

    /* 输出*/
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            "%s: %d,%u",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            stTriModeEnableStru.usEnable,
                                            stTriModeFemProfileIdStru.ulProfileId);
    return AT_OK;
}


VOS_UINT32 AT_Qry1xChanPara(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    if (VOS_TRUE ==  TAF_MMA_Proc1xChanQryReq(WUEPS_PID_AT,
                                              gastAtClientTab[ucIndex].usClientId,
                                              0))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_1XCHAN_QRY;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */
    }
    else
    {
        return AT_ERROR;
    }
#else
    return AT_ERROR;
#endif
}


VOS_UINT32 AT_QryProRevInUse(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    if (VOS_TRUE ==  TAF_MMA_ProcProRevInUseQryReq(WUEPS_PID_AT,
                                                   gastAtClientTab[ucIndex].usClientId,
                                                   0))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CVER_QRY;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */
    }
    else
    {
        return AT_ERROR;
    }
#else
    return AT_ERROR;
#endif
}


VOS_UINT32 AT_QryCasState(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    if (VOS_TRUE ==  TAF_MMA_ProcStateQryReq(WUEPS_PID_AT,
                                             gastAtClientTab[ucIndex].usClientId,
                                             0))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_GETSTA_QRY;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */
    }
    else
    {
        return AT_ERROR;
    }
#else
    return AT_ERROR;
#endif
}


VOS_UINT32 AT_QryProGetEsn(VOS_UINT8 ucIndex)
{
    NV_ESN_MEID_STRU                    stEsnMeId;
    VOS_INT32                           slIndex;
    VOS_UINT32                          ulEsn;

    ulEsn = 0;
    PS_MEM_SET(&stEsnMeId, 0, sizeof(NV_ESN_MEID_STRU));

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* 读取en_NV_Item_ESN_MEID */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_ESN_MEID, &stEsnMeId, sizeof(NV_ESN_MEID_STRU)))
    {
        AT_WARN_LOG("AT_QryProGetEsn:Read Nvim Failed");
        return AT_ERROR;
    }

    /* 若未使能，回复失败还是填0 ??? */
    if ((ESN_ME_ENABLE_FLAG   == stEsnMeId.enEsnMeIDFlag)
     || (ESN_MEID_ENABLE_BOTH == stEsnMeId.enEsnMeIDFlag))
    {
        /* Read from high to low */
        for (slIndex = PS_MIN(stEsnMeId.aucEsn[0], sizeof(stEsnMeId.aucEsn) - 1); slIndex > 0; slIndex--)
        {
            /* Update the current value */
            ulEsn <<= sizeof(stEsnMeId.aucEsn[0]) * 8;

            /* Add lower bits */
            ulEsn |= stEsnMeId.aucEsn[slIndex];
        }

        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        ulEsn);

    }
    else
    {
        AT_WARN_LOG("AT_QryProGetEsn: ESN is disabled");
    }

    return AT_OK;
}


VOS_UINT32 AT_QryProGetMeid(VOS_UINT8 ucIndex)
{
    NV_ESN_MEID_STRU                    stEsnMeId;
    VOS_UINT8                           aucMeId[2*AT_MEID_OCTET_NUM + 1];

    PS_MEM_SET(&stEsnMeId, 0, sizeof(NV_ESN_MEID_STRU));

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* 读取en_NV_Item_ESN_MEID */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_ESN_MEID, &stEsnMeId, sizeof(NV_ESN_MEID_STRU)))
    {
        AT_WARN_LOG("AT_QryProGetMeid:Read Nvim Failed");
        return AT_ERROR;
    }

    /* 若未使能，回复失败还是填0 ??? */
    if ((MEID_ME_ENABLE_FLAG  == stEsnMeId.enEsnMeIDFlag)
     || (ESN_MEID_ENABLE_BOTH == stEsnMeId.enEsnMeIDFlag))
    {
        AT_Hex2Ascii_Revers(&(stEsnMeId.aucMeID[1]), AT_MEID_OCTET_NUM, aucMeId);
        aucMeId[2*AT_MEID_OCTET_NUM] = '\0';

        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %s%s",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        aucMeId,
                                                        gaucAtCrLf);

    }
    else
    {
        AT_WARN_LOG("AT_QryProGetMeid: MEID is disabled");
    }

    return AT_OK;
}


VOS_UINT32 AT_QryHighVer(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    if (VOS_TRUE ==  TAF_MMA_ProcCHVerQryReq(WUEPS_PID_AT,
                                             gastAtClientTab[ucIndex].usClientId,
                                             0))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CHIGHVER_QRY;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */
    }
    else
    {
        return AT_ERROR;
    }
#else
    return AT_ERROR;
#endif
}

VOS_UINT32 AT_QryCgmtuPara(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* 执行命令操作 */
    if (VOS_OK != TAF_PS_GetCgmtuInfo(WUEPS_PID_AT,
                                         gastAtClientTab[ucIndex].usClientId,
                                         0))
    {
        return AT_ERROR;
    }

    /* 设置当前操作类型 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGMTU_READ;

    /* 返回命令处理挂起状态 */
    return AT_WAIT_ASYNC_RETURN;

#else
    return AT_ERROR;
#endif
}


VOS_UINT32 AT_QryTransModePara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* 发送消息*/
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_TRANSMODE_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryTransModePara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置当前操作类型 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_TRANSMODE_READ;

    return AT_WAIT_ASYNC_RETURN;
}



VOS_UINT32 AT_QryCdmaDormTimerVal(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* 执行命令操作 */
    if (VOS_OK != TAF_PS_ProcCdmaDormTimerQryReq(WUEPS_PID_AT,
                                                 gastAtClientTab[ucIndex].usClientId,
                                                 0))
    {
        return AT_ERROR;
    }

    /* 设置当前操作类型 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DORMTIMER_QRY;

    /* 返回命令处理挂起状态 */
    return AT_WAIT_ASYNC_RETURN;

#else
    return AT_ERROR;
#endif
}



VOS_UINT32 AT_QryMccFreqPara(
    VOS_UINT8                           ucIndex
)
{
    AT_CSS_MCC_VERSION_INFO_REQ_STRU   *pstMsg = VOS_NULL_PTR;

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        AT_ERR_LOG("AT_QryMccFreqPara: Invalid Cmd Type");

        return AT_ERROR;
    }

    /* Allocating memory for message */
    pstMsg = (AT_CSS_MCC_VERSION_INFO_REQ_STRU *)AT_ALLOC_MSG_WITH_HDR(sizeof(AT_CSS_MCC_VERSION_INFO_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("AT_QryMccFreqPara: Mem Alloc failed");

        return AT_ERROR;
    }

    PS_MEM_SET( ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH), 0x00,
                (VOS_SIZE_T)(sizeof(AT_CSS_MCC_VERSION_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* 填写消息头 */
    AT_CFG_MSG_HDR(pstMsg, PS_PID_CSS, ID_AT_CSS_MCC_VERSION_INFO_REQ);

    pstMsg->usClientId          = gastAtClientTab[ucIndex].usClientId;

    AT_SEND_MSG(pstMsg);

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MCCFREQ_QRY;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryUECenterPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* 发送消息*/
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_UE_CENTER_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("At_QryUEModePara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置当前操作类型 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UE_CENTER_QRY;

    return AT_WAIT_ASYNC_RETURN;
}



VOS_UINT32 AT_QryHdrCsqPara(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    if (VOS_TRUE == TAF_MMA_ProcHdrCsqQryReq(WUEPS_PID_AT,
                                               gastAtClientTab[ucIndex].usClientId,
                                               0))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HDR_CSQ_QRY;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */
    }

    return AT_ERROR;

#else
   return AT_ERROR;
#endif

}



VOS_UINT32 AT_QryCurrSidNid(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulRet;

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    ulRet = TAF_MMA_QryCurrSidNid(WUEPS_PID_AT,
                                  gastAtClientTab[ucIndex].usClientId,
                                  0);
    if (VOS_TRUE != ulRet)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSNID_QRY;

    return AT_WAIT_ASYNC_RETURN;
#else
        return AT_ERROR;
#endif
}


VOS_UINT32 AT_QryAfcClkInfo(VOS_UINT8 ucIndex)
{

    VOS_UINT32                          ulRet;

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_QRY_AFC_CLK_FREQ_XOCOEF_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);
    if (TAF_SUCCESS != ulRet)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AFCCLKINFO_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

