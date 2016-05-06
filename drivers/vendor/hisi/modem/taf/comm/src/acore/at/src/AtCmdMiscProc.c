

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "AtCmdMiscProc.h"
#include "AtSndMsg.h"
#include "ATCmdProc.h"
#include "dms_core.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -save -e960 */
#define    THIS_FILE_ID                 PS_FILE_ID_AT_CMD_MISC_PROC_C
/*lint -restore */

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : AT_SetActiveModem
 功能描述  : 命令^ACTIVEMODEM设置处理函数
             命令格式:AT^ACTIVEMODEM=<enable>
 输入参数  : ucIndex - 用户索引
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月21日
    作    者   : l00198894
    修改内容   : DSDS单/双卡模式

*****************************************************************************/
VOS_UINT32 AT_SetActiveModem(VOS_UINT8 ucIndex)
{
    TAF_NV_DSDS_ACTIVE_MODEM_MODE_STRU  stMode;

    /* 参数个数检查 */
    if (gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_SET(&stMode, 0, sizeof(stMode));
    stMode.enActiveModem = (TAF_NV_ACTIVE_MODEM_MODE_ENUM_UINT8)gastAtParaList[0].ulParaValue;

    /* 写NV, 返回AT_OK */
    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_DSDS_Active_Modem_Mode, &stMode, sizeof(stMode)))
    {
        AT_ERR_LOG("AT_SetActiveModem(): en_NV_Item_DSDS_Active_Modem_Mode NV Write Fail!");
        return AT_ERROR;
    }

    return AT_OK;
}

#if(FEATURE_ON == FEATURE_LTE)
#if(FEATURE_ON == FEATURE_LTE_MBMS)
/*****************************************************************************
 函 数 名  : AT_SetMBMSServiceOptPara
 功能描述  : ^MBMSCMD="MBMS_SERVICE_ENABLER",<param1>
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetMBMSServiceOptPara(VOS_UINT8 ucIndex)
{
    AT_MTA_MBMS_SERVICE_OPTION_SET_REQ_STRU         stMBMSServiceOption;
    VOS_UINT32                                      ulRst;

    PS_MEM_SET(&stMBMSServiceOption, 0x00, sizeof(AT_MTA_MBMS_SERVICE_OPTION_SET_REQ_STRU));

    /* 参数为空 */
    if(1 != gastAtParaList[1].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRst = atAuc2ul(gastAtParaList[1].aucPara,
                     (VOS_UINT16)gastAtParaList[1].usParaLen,
                     &gastAtParaList[1].ulParaValue);

    if(AT_SUCCESS != ulRst)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    switch(gastAtParaList[1].ulParaValue)
    {
        case 0:
            stMBMSServiceOption.enCfg = AT_MTA_CFG_DISABLE;
            break;

        case 1:
            stMBMSServiceOption.enCfg = AT_MTA_CFG_ENABLE;
            break;

        default:
            return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 发送跨核消息到C核, 设置使能或者去使能MBMS服务特性 */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_MTA_MBMS_SERVICE_OPTION_SET_REQ,
                                   &stMBMSServiceOption,
                                   sizeof(stMBMSServiceOption),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulRst)
    {
        AT_WARN_LOG("AT_SetMBMSServicePara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MBMS_SERVICE_OPTION_SET;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 函 数 名  : AT_SetMBMSServiceStatePara
 功能描述  : ^MBMSCMD="ACTIVATE",<param1>,<param2>
             ^MBMSCMD="DEACTIVATE",<param1>,<param2>
             ^MBMSCMD="DEACTIVATE_ALL"
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetMBMSServiceStatePara(VOS_UINT8 ucIndex)
{
    AT_MTA_MBMS_SERVICE_STATE_SET_REQ_STRU          stMBMSServiceState;
    VOS_UINT32                                      ulRst;

    PS_MEM_SET(&stMBMSServiceState, 0x00, sizeof(AT_MTA_MBMS_SERVICE_STATE_SET_REQ_STRU));

    switch(gastAtParaList[0].ulParaValue)
    {
        case AT_MBMS_ACTIVATE_TYPE:
            stMBMSServiceState.enStateSet   = AT_MTA_MBMS_SERVICE_STATE_SET_ACTIVE;
            break;

        case AT_MBMS_DEACTIVATE_TYPE:
            stMBMSServiceState.enStateSet   = AT_MTA_MBMS_SERVICE_STATE_SET_DEACTIVE;
            break;

        case AT_MBMS_DEACTIVATE_ALL_TYPE:
            stMBMSServiceState.enStateSet   = AT_MTA_MBMS_SERVICE_STATE_SET_DEACTIVE_ALL;
            break;

        default:
            return AT_CME_INCORRECT_PARAMETERS;
    }

    if(AT_MTA_MBMS_SERVICE_STATE_SET_DEACTIVE_ALL != stMBMSServiceState.enStateSet)
    {
        /* 参数为空 */
        if(0 == gastAtParaList[1].usParaLen || 0 == gastAtParaList[2].usParaLen)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        ulRst = atAuc2ul(gastAtParaList[1].aucPara,
                         (VOS_UINT16)gastAtParaList[1].usParaLen,
                         &gastAtParaList[1].ulParaValue);

        if(AT_SUCCESS != ulRst)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        /* 参数长度不正确 */
        if(((AT_MBMS_TMGI_MAX_LENGTH - 1 ) != gastAtParaList[2].usParaLen)
        && (AT_MBMS_TMGI_MAX_LENGTH != gastAtParaList[2].usParaLen))
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        /* <AreaID> */
        stMBMSServiceState.ulAreaId                 = gastAtParaList[1].ulParaValue;

        /* <TMGI>:MBMS Service ID */
        if(AT_FAILURE == At_Auc2ul(gastAtParaList[2].aucPara, AT_MBMS_SERVICE_ID_LENGTH, &stMBMSServiceState.stTMGI.ulMbmsSerId))
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        /* <TMGI>:Mcc */
        if(AT_FAILURE == At_String2Hex(&gastAtParaList[2].aucPara[AT_MBMS_SERVICE_ID_LENGTH], AT_MBMS_MCC_LENGTH, &stMBMSServiceState.stTMGI.stPlmnId.ulMcc))
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        /* <TMGI>:Mnc */
        if(AT_FAILURE == At_String2Hex(&gastAtParaList[2].aucPara[AT_MBMS_SERVICE_ID_AND_MCC_LENGTH], gastAtParaList[2].usParaLen - AT_MBMS_SERVICE_ID_AND_MCC_LENGTH, &stMBMSServiceState.stTMGI.stPlmnId.ulMnc))
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        if ( (AT_MBMS_TMGI_MAX_LENGTH - 1 ) == gastAtParaList[2].usParaLen)
        {
            stMBMSServiceState.stTMGI.stPlmnId.ulMnc |= 0x0F00;
        }
    }

    /* 发送跨核消息到C核, 设置使能或者去使能MBMS服务特性 */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_MTA_MBMS_SERVICE_STATE_SET_REQ,
                                   &stMBMSServiceState,
                                   sizeof(stMBMSServiceState),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulRst)
    {
        AT_WARN_LOG("AT_SetMBMSServiceStatePara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MBMS_SERVICE_STATE_SET;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 函 数 名  : AT_SetMBMSPreferencePara
 功能描述  : ^MBMSCMD="MBMS_PREFERENCE",<param1>
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetMBMSPreferencePara(VOS_UINT8 ucIndex)
{
    AT_MTA_MBMS_PREFERENCE_SET_REQ_STRU             stMBMSCastMode;
    VOS_UINT32                                      ulRst;

    PS_MEM_SET(&stMBMSCastMode, 0x00, sizeof(AT_MTA_MBMS_PREFERENCE_SET_REQ_STRU));

    /* 参数为空 */
    if(1 != gastAtParaList[1].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRst = atAuc2ul(gastAtParaList[1].aucPara, (VOS_UINT16)gastAtParaList[1].usParaLen, &gastAtParaList[1].ulParaValue);

    if(AT_SUCCESS != ulRst)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    switch(gastAtParaList[1].ulParaValue)
    {
        case 0:
            stMBMSCastMode.enCastMode   = AT_MTA_MBMS_CAST_MODE_UNICAST;
            break;

        case 1:
            stMBMSCastMode.enCastMode   = AT_MTA_MBMS_CAST_MODE_MULTICAST;
            break;

        default:
            return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 发送跨核消息到C核, 设置MBMS广播模式 */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_MTA_MBMS_PREFERENCE_SET_REQ,
                                   &stMBMSCastMode,
                                   sizeof(stMBMSCastMode),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulRst)
    {
        AT_WARN_LOG("AT_SetMBMSPreferencePara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MBMS_PREFERENCE_SET;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 函 数 名  : AT_SetMBMSCMDPara
 功能描述  : ^MBMSCMD
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetMBMSCMDPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数过多 */
    if (gucAtParaIndex > 3)
    {
        return AT_TOO_MANY_PARA;
    }

    /* 参数为空 */
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 设置<cmd>*/
    switch(gastAtParaList[0].ulParaValue)
    {
        /* <cmd> equal "MBMS_SERVICE_ENABLER" */
        case AT_MBMS_SERVICE_ENABLER_TYPE:
            ulRst = AT_SetMBMSServiceOptPara(ucIndex);
            break;
        /* <cmd> equal "ACTIVATE", "DEACTIVATE" or "DEACTIVATE_ALL" */
        case AT_MBMS_ACTIVATE_TYPE:
        case AT_MBMS_DEACTIVATE_TYPE:
        case AT_MBMS_DEACTIVATE_ALL_TYPE:
            ulRst = AT_SetMBMSServiceStatePara(ucIndex);
            break;
        /* <cmd> equal "MBMS_PREFERENCE" */
        case AT_MBMS_PREFERENCE_TYPE:
            ulRst = AT_SetMBMSPreferencePara(ucIndex);
            break;
        /* <cmd> equal "SIB16_GET_NETWORK_TIME" */
        case AT_MBMS_SIB16_GET_NETWORK_TIME_TYPE:
            ulRst = AT_QryMBMSSib16NetworkTimePara(ucIndex);
            break;
        /* <cmd> equal "BSSI_SIGNAL_LEVEL" */
        case AT_MBMS_BSSI_SIGNAL_LEVEL_TYPE:
            ulRst = AT_QryMBMSBssiSignalLevelPara(ucIndex);
            break;
        /* <cmd> equal "NETWORK_INFORMATION" */
        case AT_MBMS_NETWORK_INFORMATION_TYPE:
            ulRst = AT_QryMBMSNetworkInfoPara(ucIndex);
            break;
        /* <cmd> equal "MODEM_STATUS" */
        case AT_MBMS_MODEM_STATUS_TYPE:
            ulRst = AT_QryMBMSModemStatusPara(ucIndex);
            break;

        default:
            ulRst = AT_CME_INCORRECT_PARAMETERS;
            break;
    }

    return ulRst;
}

/*****************************************************************************
 函 数 名  : AT_SetMBMSEVPara
 功能描述  : ^MBMSEV
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetMBMSEVPara(VOS_UINT8 ucIndex)
{
    AT_MTA_MBMS_UNSOLICITED_CFG_SET_REQ_STRU        stMBMSUnsolicitedCfg;
    VOS_UINT32                                      ulRst;

    PS_MEM_SET(&stMBMSUnsolicitedCfg, 0x00, sizeof(AT_MTA_MBMS_UNSOLICITED_CFG_SET_REQ_STRU));

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数个数不正确 */
    if (1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数为空 */
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    switch(gastAtParaList[0].ulParaValue)
    {
        case 0:
            stMBMSUnsolicitedCfg.enCfg  = AT_MTA_CFG_DISABLE;
            break;

        case 1:
            stMBMSUnsolicitedCfg.enCfg  = AT_MTA_CFG_ENABLE;
            break;

        default:
            return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 发送跨核消息到C核, 设置MBMS主动上报配置 */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_MTA_MBMS_UNSOLICITED_CFG_SET_REQ,
                                   &stMBMSUnsolicitedCfg,
                                   sizeof(stMBMSUnsolicitedCfg),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulRst)
    {
        AT_WARN_LOG("AT_SetMBMSEVPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MBMS_UNSOLICITED_CFG_SET;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 函 数 名  : AT_SetMBMSInterestListPara
 功能描述  : ^MBMSINTERESTLIST
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetMBMSInterestListPara(VOS_UINT8 ucIndex)
{
    AT_MTA_MBMS_INTERESTLIST_SET_REQ_STRU           stMBMSInterestList;
    VOS_UINT32                                      ulRst;
    VOS_UINT8                                       interestNum;

    PS_MEM_SET(&stMBMSInterestList, 0x00, sizeof(AT_MTA_MBMS_INTERESTLIST_SET_REQ_STRU));

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数个数不正确 */
    if (gucAtParaIndex != 6)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数为空 */
    if(0 == gastAtParaList[5].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    switch(gastAtParaList[5].ulParaValue)
    {
        case 0:
            stMBMSInterestList.enMbmsPriority    = AT_MTA_MBMS_PRIORITY_UNICAST;
            break;

        case 1:
            stMBMSInterestList.enMbmsPriority    = AT_MTA_MBMS_PRIORITY_MBMS;
            break;

        default:
            return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 频点列表赋值 */
    for(interestNum = 0; interestNum < AT_MTA_INTEREST_FREQ_MAX_NUM; interestNum++)
    {
        if (0 != gastAtParaList[interestNum].usParaLen)
        {
            ulRst = atAuc2ul(gastAtParaList[interestNum].aucPara,
                             (VOS_UINT16)gastAtParaList[interestNum].usParaLen,
                             &gastAtParaList[interestNum].ulParaValue);

            if(AT_SUCCESS != ulRst)
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }

            stMBMSInterestList.aulFreqList[interestNum]   =   gastAtParaList[interestNum].ulParaValue;
        }
        else
        {
            /* 默认值为无效值0xFFFFFFFF */
            stMBMSInterestList.aulFreqList[interestNum]   =   0xFFFFFFFF;
        }
    }

    /* 发送跨核消息到C核, 设置MBMS主动上报配置 */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_MTA_INTEREST_LIST_SET_REQ,
                                   &stMBMSInterestList,
                                   sizeof(stMBMSInterestList),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulRst)
    {
        AT_WARN_LOG("AT_SetMBMSInterestListPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MBMS_INTERESTLIST_SET;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 函 数 名  : AT_QryMBMSSib16NetworkTimePara
 功能描述  : ^MBMSCMD="SIB16_GET_NETWORK_TIME"
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_QryMBMSSib16NetworkTimePara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                                      ulRst;

    /* 发送跨核消息到C核, 查询SIB16网络时间请求 */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_MTA_SIB16_NETWORK_TIME_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulRst)
    {
        AT_WARN_LOG("AT_QryMBMSSib16NetworkTimePara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MBMS_SIB16_NETWORK_TIME_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 函 数 名  : AT_QryMBMSBssiSignalLevelPara
 功能描述  : ^MBMSCMD="BSSI_SIGNAL_LEVEL"
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_QryMBMSBssiSignalLevelPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                                      ulRst;

    /* 发送跨核消息到C核, 查询BSSI信号强度请求 */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_MTA_BSSI_SIGNAL_LEVEL_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulRst)
    {
        AT_WARN_LOG("AT_QryMBMSBssiSignalLevelPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MBMS_BSSI_SIGNAL_LEVEL_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 函 数 名  : AT_QryMBMSNetworkInfoPara
 功能描述  : ^MBMSCMD="NETWORK_INFORMATION"
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_QryMBMSNetworkInfoPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                                      ulRst;

    /* 发送跨核消息到C核, 查询网络信息请求 */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_MTA_NETWORK_INFO_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulRst)
    {
        AT_WARN_LOG("AT_QryMBMSNetworkInfoPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MBMS_NETWORK_INFO_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 函 数 名  : AT_QryMBMSModemStatusPara
 功能描述  : ^MBMSCMD="MODEM_STATUS"
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_QryMBMSModemStatusPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                                      ulRst;

    /* 发送跨核消息到C核, 查询eMBMS功能状态请求 */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_MTA_EMBMS_STATUS_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulRst)
    {
        AT_WARN_LOG("AT_QryMBMSModemStatusPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_EMBMS_STATUS_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 函 数 名  : AT_QryMBMSCmdPara
 功能描述  : ^MBMSCMD查询命令处理函数
 输入参数  : ucIndex - 用户索引
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月22日
    作    者   : w00316404
    修改内容   :新增查询函数
*****************************************************************************/
VOS_UINT32 AT_QryMBMSCmdPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    if(AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* AT 给MTA 发送查询请求消息 */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_MBMS_AVL_SERVICE_LIST_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryMBMSCmdPara: send Msg fail.");
        return AT_ERROR;
    }

    /* 设置当前操作类型 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MBMS_AVL_SERVICE_LIST_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 函 数 名  : At_TestMBMSCMDPara
 功能描述  : ^MBMSCMD=?
 输入参数  : ucIndex - 用户索引
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月22日
    作    者   : w00316404
    修改内容   :新增函数
*****************************************************************************/

VOS_UINT32 At_TestMBMSCMDPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: (\"MBMS_SERVICE_ENABLER\",\"ACTIVATE\",\"DEACTIVATE\",\"DEACTIVATE_ALL\",\"MBMS_PREFERENCE\",\"SIB16_GET_NETWORK_TIME\",\"BSSI_SIGNAL_LEVEL\",\"NETWORK_INFORMATION\",\"MODEM_STATUS\")",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;
    return AT_OK;
}


/*****************************************************************************
 函 数 名  : AT_RcvMtaMBMSServiceOptSetCnf
 功能描述  : 收到MTA设置MBMS服务特性的回复
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvMtaMBMSServiceOptSetCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                            *pRcvMsg         = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                     *pstMtaCnf       = VOS_NULL_PTR;
    VOS_UINT32                                  ulResult;
    VOS_UINT8                                   ucIndex;

    /* 初始化 */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstMtaCnf           = (MTA_AT_RESULT_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMBMSServiceOptSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMBMSServiceOptSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_MBMS_SERVICE_OPTION_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaMBMSServiceOptSetCnf : Current Option is not AT_CMD_MBMS_SERVICE_OPTION_SET.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstMtaCnf->enResult)
    {
        ulResult = AT_ERROR;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaMBMSServiceStateSetCnf
 功能描述  : 收到MTA设置MBMS服务状态的回复
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaMBMSServiceStateSetCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                            *pRcvMsg         = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                     *pstMtaCnf       = VOS_NULL_PTR;
    VOS_UINT32                                  ulResult;
    VOS_UINT8                                   ucIndex;

    /* 初始化 */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstMtaCnf           = (MTA_AT_RESULT_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMBMSServiceStateSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMBMSServiceStateSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_MBMS_SERVICE_STATE_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaMBMSServiceStateSetCnf : Current Option is not AT_CMD_MBMS_SERVICE_STATE_SET.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstMtaCnf->enResult)
    {
        ulResult = AT_ERROR;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaMBMSPreferenceSetCnf
 功能描述  : 收到MTA设置MBMS广播模式的回复
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaMBMSPreferenceSetCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                            *pRcvMsg         = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                     *pstMtaCnf       = VOS_NULL_PTR;
    VOS_UINT32                                  ulResult;
    VOS_UINT8                                   ucIndex;

    /* 初始化 */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstMtaCnf           = (MTA_AT_RESULT_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMBMSPreferenceSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMBMSPreferenceSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_MBMS_PREFERENCE_SET  != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaMBMSPreferenceSetCnf : Current Option is not AT_CMD_MBMS_PREFERENCE_SET.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstMtaCnf->enResult)
    {
        ulResult = AT_ERROR;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaMBMSSib16NetworkTimeQryCnf
 功能描述  : 收到MTA查询SIB16网络时间的回复
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaMBMSSib16NetworkTimeQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                                *pRcvMsg         = VOS_NULL_PTR;
    MTA_AT_MBMS_SIB16_NETWORK_TIME_QRY_CNF_STRU    *pstMtaCnf       = VOS_NULL_PTR;
    VOS_UINT64                                     *pullUTC;
    VOS_UINT8                                       aucUTC[AT_MBMS_UTC_MAX_LENGTH + 1];
    VOS_UINT32                                      ulResult;
    VOS_UINT8                                       ucIndex;

    /* 初始化 */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstMtaCnf           = (MTA_AT_MBMS_SIB16_NETWORK_TIME_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;
    PS_MEM_SET(aucUTC, 0x00, sizeof(aucUTC));

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMBMSSib16NetworkTimeQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMBMSSib16NetworkTimeQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_MBMS_SIB16_NETWORK_TIME_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaMBMSSib16NetworkTimeQryCnf : Current Option is not AT_CMD_MBMS_SIB16_NETWORK_TIME_QRY.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstMtaCnf->enResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        pullUTC = (VOS_UINT64 *)pstMtaCnf->aulUTC;
        sprintf((VOS_CHAR *)aucUTC, "%llu", *pullUTC);
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %s",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    aucUTC);
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaMBMSBssiSignalLevelQryCnf
 功能描述  : 收到MTA查询BSSI信号强度的回复
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaMBMSBssiSignalLevelQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                                *pRcvMsg         = VOS_NULL_PTR;
    MTA_AT_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU     *pstMtaCnf       = VOS_NULL_PTR;
    VOS_UINT32                                      ulResult;
    VOS_UINT8                                       ucIndex;

    /* 初始化 */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstMtaCnf           = (MTA_AT_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMBMSBssiSignalLevelQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMBMSBssiSignalLevelQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_MBMS_BSSI_SIGNAL_LEVEL_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaMBMSBssiSignalLevelQryCnf : Current Option is not AT_CMD_MBMS_BSSI_SIGNAL_LEVEL_QRY.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstMtaCnf->enResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    (VOS_INT32)pstMtaCnf->ucBSSILevel);
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaMBMSNetworkInfoQryCnf
 功能描述  : 收到MTA查询网络信息的回复
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaMBMSNetworkInfoQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                                *pRcvMsg         = VOS_NULL_PTR;
    MTA_AT_MBMS_NETWORK_INFO_QRY_CNF_STRU          *pstMtaCnf       = VOS_NULL_PTR;
    VOS_UINT32                                      ulResult;
    VOS_UINT8                                       ucIndex;

    /* 初始化 */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstMtaCnf           = (MTA_AT_MBMS_NETWORK_INFO_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMBMSNetworkInfoQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMBMSNetworkInfoQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_MBMS_NETWORK_INFO_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaMBMSNetworkInfoQryCnf : Current Option is not AT_CMD_MBMS_NETWORK_INFO_QRY.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstMtaCnf->enResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    (VOS_INT32)pstMtaCnf->ulCellId);
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaMBMSModemStatusQryCnf
 功能描述  : 收到MTA查询EMBMS功能状态的回复
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaMBMSModemStatusQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                                *pRcvMsg         = VOS_NULL_PTR;
    MTA_AT_EMBMS_STATUS_QRY_CNF_STRU               *pstMtaCnf       = VOS_NULL_PTR;
    VOS_UINT32                                      ulResult;
    VOS_UINT8                                       ucIndex;

    /* 初始化 */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstMtaCnf           = (MTA_AT_EMBMS_STATUS_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMBMSModemStatusQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMBMSModemStatusQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_EMBMS_STATUS_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaMBMSModemStatusQryCnf : Current Option is not AT_CMD_EMBMS_STATUS_QRY.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstMtaCnf->enResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    (VOS_INT32)pstMtaCnf->enStatus);
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaMBMSEVSetCnf
 功能描述  : 收到MTA设置MBMS主动上报配置的回复
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaMBMSEVSetCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                            *pRcvMsg         = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                     *pstMtaCnf       = VOS_NULL_PTR;
    VOS_UINT32                                  ulResult;
    VOS_UINT8                                   ucIndex;

    /* 初始化 */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstMtaCnf           = (MTA_AT_RESULT_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMBMSEVSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMBMSEVSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_MBMS_UNSOLICITED_CFG_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaMBMSEVSetCnf : Current Option is not AT_CMD_MBMS_UNSOLICITED_CFG_SET.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstMtaCnf->enResult)
    {
        ulResult = AT_ERROR;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaMBMSServiceEventInd
 功能描述  : AT收到MTA ID_MTA_AT_MBMS_SERVICE_EVENT_IND消息处理函数
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaMBMSServiceEventInd(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg      = VOS_NULL_PTR;
    MTA_AT_MBMS_SERVICE_EVENT_IND_STRU     *pstMtaAtInd    = VOS_NULL_PTR;
    VOS_UINT8                               ucIndex;
    VOS_UINT16                              usLength;

    /* 初始化 */
    pstRcvMsg           = (AT_MTA_MSG_STRU *)pstMsg;
    pstMtaAtInd         = (MTA_AT_MBMS_SERVICE_EVENT_IND_STRU *)pstRcvMsg->aucContent;
    ucIndex             = 0;
    usLength            = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMBMSServiceEventInd : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s%s %d%s",
                                       gaucAtCrLf,
                                       gastAtStringTab[AT_STRING_MBMSEV].pucText,
                                       pstMtaAtInd->enEvent,
                                       gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaMBMSInterestListSetCnf
 功能描述  : 收到MTA设置Interest List的回复
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaMBMSInterestListSetCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                            *pRcvMsg         = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                     *pstMtaCnf       = VOS_NULL_PTR;
    VOS_UINT32                                  ulResult;
    VOS_UINT8                                   ucIndex;

    /* 初始化 */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstMtaCnf           = (MTA_AT_RESULT_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMBMSInterestListSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMBMSInterestListSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_MBMS_INTERESTLIST_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaMBMSInterestListSetCnf : Current Option is not AT_CMD_MBMS_INTERESTLIST_SET.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstMtaCnf->enResult)
    {
        ulResult = AT_ERROR;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_ReportMBMSCmdQryCnf
 功能描述  : 打印MBMS可用服务列表信息
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_ReportMBMSCmdQryCnf(
    MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU      *pstMtaCnf,
    VOS_UINT8                                       ucIndex
)
{
    VOS_UINT32                          ulListNum;
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucServiceID[AT_MBMS_SERVICE_ID_LENGTH + 1];

    usLength = 0;

    for (ulListNum = 0; ulListNum < pstMtaCnf->ulAvlServiceNum; ulListNum++)
    {
        /* 获得MBMS Service ID字符串形式 */
        PS_MEM_SET(aucServiceID, 0, sizeof(aucServiceID));
        At_ul2Auc(pstMtaCnf->astAvlServices[ulListNum].stTMGI.ulMbmsSerId, AT_MBMS_SERVICE_ID_LENGTH, aucServiceID);

        /* ^MBMSCMD: <AreaID>,<TMGI>:MBMS Service ID */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s: %d,%s",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          (VOS_INT32)pstMtaCnf->astAvlServices[ulListNum].ulAreaId,
                                          aucServiceID);

        /* <TMGI>:Mcc */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%x%x%x",
                                          (pstMtaCnf->astAvlServices[ulListNum].stTMGI.stPlmnId.ulMcc & 0x0f00) >> 8,
                                          (pstMtaCnf->astAvlServices[ulListNum].stTMGI.stPlmnId.ulMcc & 0xf0) >> 4,
                                          (pstMtaCnf->astAvlServices[ulListNum].stTMGI.stPlmnId.ulMcc & 0x0f));
        /* <TMGI>:Mnc */
        if (0x0f00 == (pstMtaCnf->astAvlServices[ulListNum].stTMGI.stPlmnId.ulMnc & 0x0f00))
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                              "%x%x",
                                              (pstMtaCnf->astAvlServices[ulListNum].stTMGI.stPlmnId.ulMnc & 0xf0) >> 4,
                                              (pstMtaCnf->astAvlServices[ulListNum].stTMGI.stPlmnId.ulMnc & 0x0f));
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                              "%x%x%x",
                                              (pstMtaCnf->astAvlServices[ulListNum].stTMGI.stPlmnId.ulMnc & 0x0f00) >> 8,
                                              (pstMtaCnf->astAvlServices[ulListNum].stTMGI.stPlmnId.ulMnc & 0xf0) >> 4,
                                              (pstMtaCnf->astAvlServices[ulListNum].stTMGI.stPlmnId.ulMnc & 0x0f));
        }

        if (VOS_TRUE == pstMtaCnf->astAvlServices[ulListNum].bitOpSessionId)
        {
            /* <SessionID> */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                              ",%d",
                                              (VOS_INT32)pstMtaCnf->astAvlServices[ulListNum].ulSessionId);
        }

        if (ulListNum != (pstMtaCnf->ulAvlServiceNum - 1))
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                              "%s",
                                              gaucAtCrLf);
        }
    }

    gstAtSendData.usBufLen = usLength;
    return;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaMBMSCmdQryCnf
 功能描述  : 收到MTA查询MBMS可用服务列表信息的回复
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaMBMSCmdQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                                *pRcvMsg         = VOS_NULL_PTR;
    MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU      *pstMtaCnf       = VOS_NULL_PTR;
    VOS_UINT32                                      ulResult;
    VOS_UINT8                                       ucIndex;

    /* 初始化 */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstMtaCnf           = (MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMBMSCmdQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMBMSCmdQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_MBMS_AVL_SERVICE_LIST_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaMBMSCmdQryCnf : Current Option is not AT_CMD_MBMS_AVL_SERVICE_LIST_QRY.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstMtaCnf->enResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        AT_ReportMBMSCmdQryCnf(pstMtaCnf, ucIndex);
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
#endif

/*****************************************************************************
 函 数 名  : AT_SetLteLowPowerPara
 功能描述  : ^LTELOWPOWER
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetLteLowPowerPara(VOS_UINT8 ucIndex)
{
    AT_MTA_LOW_POWER_CONSUMPTION_SET_REQ_STRU       stPowerConsumption;
    VOS_UINT32                                      ulRst;

    PS_MEM_SET(&stPowerConsumption, 0x00, sizeof(AT_MTA_LOW_POWER_CONSUMPTION_SET_REQ_STRU));

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数个数不正确 */
    if (1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数为空 */
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    switch(gastAtParaList[0].ulParaValue)
    {
        case 0:
            stPowerConsumption.enLteLowPowerFlg = AT_MTA_LTE_LOW_POWER_NORMAL;
            break;

        case 1:
            stPowerConsumption.enLteLowPowerFlg = AT_MTA_LTE_LOW_POWER_LOW;
            break;

        default:
            return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 发送跨核消息到C核, 设置低功耗 */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_MTA_LTE_LOW_POWER_SET_REQ,
                                   &stPowerConsumption,
                                   sizeof(stPowerConsumption),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulRst)
    {
        AT_WARN_LOG("AT_SetLteLowPowerPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_LTE_LOW_POWER_CONSUMPTION_SET;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 函 数 名  : AT_GetIsmCoexParaValue
 功能描述  : GetIsmCoexPara
 输入参数  : pucBegain,ppEnd
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_INT32 AT_GetIsmCoexParaValue(VOS_UINT8 *pucBegain, VOS_UINT8 **ppEnd)
{
    VOS_UINT32 ulTotal      = 0;
    VOS_INT32  lRstTotal    = 0;
    VOS_UINT32 ulRst;
    VOS_UINT8 *pucEnd;
    VOS_UINT32 ulFlag       = 0;

    pucEnd = pucBegain;

    while((' ' != *pucEnd) && ('\0' != *pucEnd))
    {
        pucEnd++;
    }

    if('-' == *pucBegain)
    {
        ulFlag = 1;
        pucBegain++;
    }

    ulRst = atAuc2ul(pucBegain, (VOS_UINT16)(pucEnd - pucBegain), &ulTotal);

    if(AT_SUCCESS != ulRst)
    {
        lRstTotal = AT_COEX_INVALID;
    }
    else
    {
        *ppEnd      = (pucEnd + 1);
        lRstTotal   = (VOS_INT32)(ulFlag ? (0 - ulTotal):ulTotal);
    }

    return lRstTotal;
}

/*****************************************************************************
 函 数 名  : AT_CheckIsmCoexParaValue
 功能描述  : 检查^ISMCOEX参数的有效性
 输入参数  : usVal,ulParaNum
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_CheckIsmCoexParaValue(VOS_INT32 ulVal, VOS_UINT32 ulParaNum)
{
    VOS_UINT32                          ulRst = AT_SUCCESS;

    switch(ulParaNum)
    {
        case AT_COEX_PARA_COEX_ENABLE:
            if((AT_COEX_PARA_COEX_ENABLE_MIN > ulVal)
            || (AT_COEX_PARA_COEX_ENABLE_MAX < ulVal))
            {
                ulRst = AT_FAILURE;
            }
            break;
        case AT_COEX_PARA_TX_BEGIN:
            if((AT_COEX_PARA_TX_BEGIN_MIN > ulVal)
            || (AT_COEX_PARA_TX_BEGIN_MAX < ulVal))
            {
                ulRst = AT_FAILURE;
            }
            break;
        case AT_COEX_PARA_TX_END:
            if((AT_COEX_PARA_TX_END_MIN > ulVal)
            || (AT_COEX_PARA_TX_END_MAX < ulVal))
            {
                ulRst = AT_FAILURE;
            }
            break;
        case AT_COEX_PARA_TX_POWER:
            if((AT_COEX_PARA_TX_POWER_MIN > ulVal)
            || (AT_COEX_PARA_TX_POWER_MAX < ulVal))
            {
                ulRst = AT_FAILURE;
            }
            break;
        case AT_COEX_PARA_RX_BEGIN:
            if((AT_COEX_PARA_RX_BEGIN_MIN > ulVal)
            || (AT_COEX_PARA_RX_BEGIN_MAX < ulVal))
            {
                ulRst = AT_FAILURE;
            }
            break;
        case AT_COEX_PARA_RX_END:
            if((AT_COEX_PARA_RX_END_MIN > ulVal)
            || (AT_COEX_PARA_RX_END_MAX < ulVal))
            {
                ulRst = AT_FAILURE;
            }
            break;
        default:
            ulRst = AT_FAILURE;
            break;

    }

    return ulRst;
}

/*****************************************************************************
 函 数 名  : AT_SetL4AIsmCoexParaValue
 功能描述  : 填充发往L4A的消息参数
 输入参数  : stIsmCoex
 输出参数  : pstReqToL4A
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_SetL4AIsmCoexParaValue(AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU stIsmCoex, L4A_ISMCOEX_REQ_STRU *pstReqToL4A, VOS_UINT8 ucIndex)
{
    VOS_UINT32                          i;

    pstReqToL4A->stCtrl.ulClientId = gastAtClientTab[ucIndex].usClientId;;
    pstReqToL4A->stCtrl.ulOpId     = 0;
    pstReqToL4A->stCtrl.ulPid      = WUEPS_PID_AT;

    for(i = 0; i < AT_MTA_ISMCOEX_BANDWIDTH_NUM; i++)
    {
        pstReqToL4A->astCoex[i].ulFlag      = (VOS_UINT32)stIsmCoex.astCoexPara[i].enCfg;
        pstReqToL4A->astCoex[i].ulTXBegin   = (VOS_UINT32)stIsmCoex.astCoexPara[i].usTxBegin;
        pstReqToL4A->astCoex[i].ulTXEnd     = (VOS_UINT32)stIsmCoex.astCoexPara[i].usTxEnd;
        pstReqToL4A->astCoex[i].lTXPower    = (VOS_INT32)stIsmCoex.astCoexPara[i].sTxPower;
        pstReqToL4A->astCoex[i].ulRXBegin   = (VOS_UINT32)stIsmCoex.astCoexPara[i].usRxBegin;
        pstReqToL4A->astCoex[i].ulRXEnd     = (VOS_UINT32)stIsmCoex.astCoexPara[i].usRxEnd;
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_SetIsmCoexPara
 功能描述  : ^ISMCOEX
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetIsmCoexPara(VOS_UINT8 ucIndex)
{
    AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU               stIsmCoex;
    L4A_ISMCOEX_REQ_STRU                            stReqToL4A = {0};
    VOS_UINT32                                      ulRst,ulRet;
    VOS_UINT32                                      i, j;
    VOS_INT32                                       ret;
    VOS_UINT16                                     *pusVal;                     /* 将要存储的值指针 */
    VOS_UINT8                                      *pucCur;                     /* 解析字符串时的当前指针 */
    VOS_UINT8                                      *pucPara;                    /* 参数字符串头指针 */

    PS_MEM_SET(&stIsmCoex, 0x00, sizeof(AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU));

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数个数 */
    if (AT_MTA_ISMCOEX_BANDWIDTH_NUM != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }


    for(i = 0; i < AT_MTA_ISMCOEX_BANDWIDTH_NUM; i++)
    {
        pucCur = gastAtParaList[i].aucPara;
        stIsmCoex.astCoexPara[i].enCoexBWType = (AT_MTA_COEX_BW_TYPE_ENUM_UINT16)i;
        pusVal = &(stIsmCoex.astCoexPara[i].enCfg);

        for(j = 0; j < sizeof(AT_MTA_COEX_PARA_STRU)/sizeof(VOS_UINT16) - 2; j++)
        {
            pucPara = pucCur;
            ret = AT_GetIsmCoexParaValue(pucPara, &pucCur);

            if(AT_COEX_INVALID == ret)
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }

            if (AT_FAILURE == AT_CheckIsmCoexParaValue(ret, j))
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }

           *pusVal = (VOS_UINT16)ret;
            pusVal++;
        }
    }

    stIsmCoex.usCoexParaNum     = AT_MTA_ISMCOEX_BANDWIDTH_NUM;
    stIsmCoex.usCoexParaSize    = sizeof(stIsmCoex.astCoexPara);

    AT_SetL4AIsmCoexParaValue(stIsmCoex, &stReqToL4A, ucIndex);

    /* 发送消息到L4A */
    ulRet = atSendDataMsg(MSP_L4_L4A_PID, ID_MSG_L4A_ISMCOEXSET_REQ, (VOS_VOID*)(&stReqToL4A), sizeof(stReqToL4A));

    /* 发送跨核消息到C核 */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_MTA_LTE_WIFI_COEX_SET_REQ,
                                   &stIsmCoex,
                                   sizeof(stIsmCoex),
                                   I0_UEPS_PID_MTA);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_SetIsmCoexPara: atSendDataMsg fail.");
    }

    if (TAF_SUCCESS != ulRst)
    {
        AT_WARN_LOG("AT_SetIsmCoexPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_LTE_WIFI_COEX_SET;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 函 数 名  : AT_QryIsmCoexPara
 功能描述  : ^ISMCOEX查询命令处理函数,查询
 输入参数  : ucIndex - 用户索引
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月22日
    作    者   : w00316404
    修改内容   :新增查询函数
*****************************************************************************/
VOS_UINT32 AT_QryIsmCoexPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                                      ulRst;

    if(AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* 发送跨核消息到C核, 查询ISMCOEX列表请求 */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_MTA_LTE_WIFI_COEX_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulRst)
    {
        AT_WARN_LOG("AT_QryIsmCoexPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_LTE_WIFI_COEX_QRY;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaLteLowPowerSetCnf
 功能描述  : 收到MTA设置低功耗的回复
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaLteLowPowerSetCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                            *pRcvMsg         = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                     *pstMtaCnf       = VOS_NULL_PTR;
    VOS_UINT32                                  ulResult;
    VOS_UINT8                                   ucIndex;

    /* 初始化 */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstMtaCnf           = (MTA_AT_RESULT_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaLteLowPowerSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaLteLowPowerSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_LTE_LOW_POWER_CONSUMPTION_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaLteLowPowerSetCnf : Current Option is not AT_CMD_LTE_LOW_POWER_CONSUMPTION_SET.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstMtaCnf->enResult)
    {
        ulResult = AT_ERROR;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaIsmCoexSetCnf
 功能描述  : 收到MTA设置命令 ^ISMCOEX的回复
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaIsmCoexSetCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                            *pRcvMsg         = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                     *pstCnf          = VOS_NULL_PTR;
    VOS_UINT32                                  ulResult;
    VOS_UINT8                                   ucIndex;

    /* 初始化 */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstCnf              = (MTA_AT_RESULT_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaIsmCoexSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaIsmCoexSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_LTE_WIFI_COEX_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaIsmCoexSetCnf : Current Option is not AT_CMD_LTE_WIFI_COEX_SET.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstCnf->enResult)
    {
        ulResult = AT_ERROR;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvL4AIsmCoexSetCnf
 功能描述  : 收到L4A设置命令 ^ISMCOEX的回复
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvL4AIsmCoexSetCnf(
    VOS_VOID                           *pMsg
)
{
    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_RcvMtaIsmCoexQryCnf
 功能描述  : 收到MTA查询命令 ^ISMCOEX的回复
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaIsmCoexQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                            *pRcvMsg         = VOS_NULL_PTR;
    MTA_AT_LTE_WIFI_COEX_QRY_CNF_STRU          *pstCnf          = VOS_NULL_PTR;
    VOS_UINT32                                  ulResult;
    VOS_UINT32                                  i;
    VOS_UINT8                                   ucIndex;

    /* 初始化 */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstCnf              = (MTA_AT_LTE_WIFI_COEX_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaIsmCoexQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaIsmCoexQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_LTE_WIFI_COEX_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaIsmCoexQryCnf : Current Option is not AT_CMD_LTE_WIFI_COEX_QRY.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    for(i = 0; i < AT_MTA_ISMCOEX_BANDWIDTH_NUM; i++)
    {
        gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR*)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                        " %d %d %d %d %d %d,",
                                                        pstCnf->astCoexPara[i].enCfg,
                                                        pstCnf->astCoexPara[i].usTxBegin,
                                                        pstCnf->astCoexPara[i].usTxEnd,
                                                        pstCnf->astCoexPara[i].sTxPower,
                                                        pstCnf->astCoexPara[i].usRxBegin,
                                                        pstCnf->astCoexPara[i].usRxEnd);
    }

    gstAtSendData.usBufLen--;

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
#endif


/*****************************************************************************
 函 数 名  : AT_SetLogEnablePara
 功能描述  : ^LOGENABLE
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : z00301431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetLogEnablePara(VOS_UINT8 ucIndex)
{
    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数个数检查 */
    if (1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* AT设置1表示允许抓取modemlog，设置0表示不允许抓取modemlog */
    if (1 == gastAtParaList[0].ulParaValue)
    {
        /* 设置为FALSE表示允许抓MODEM LOG */
        DMS_SET_PRINT_MODEM_LOG_TYPE(VOS_FALSE);
    }
    else
    {
        /* 设置为TRUE表示不允许抓MODEM LOG */
        DMS_SET_PRINT_MODEM_LOG_TYPE(VOS_TRUE);
    }

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : AT_QryLogEnable
 功能描述  : ^LOGENABLE
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : z00301431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_QryLogEnable(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulEnableFlag;

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    usLength                            = 0;

    if (VOS_FALSE == DMS_GET_PRINT_MODEM_LOG_TYPE())
    {
        /* DMS当前允许抓MODEM LOG，返回enable为TRUE */
        ulEnableFlag = VOS_TRUE;
    }
    else
    {
        /* DMS当前不允许抓MODEM LOG，返回enable为FALSE */
        ulEnableFlag = VOS_FALSE;
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
                                       ulEnableFlag);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


/*****************************************************************************
 函 数 名  : AT_SetActPdpStubPara
 功能描述  : ^ACTPDPSTUB
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月04日
    作    者   : z00301431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetActPdpStubPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucFlag;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数个数检查 */
    if (2 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if((0 == gastAtParaList[0].usParaLen)
    || (0 == gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 获取设置的标志 */
    ucFlag = (VOS_UINT8)gastAtParaList[1].ulParaValue;

    /* 根据MODEM ID调用不同的桩函数 */
    if (0 == gastAtParaList[0].ulParaValue)
    {
        AT_SetPcuiPsCallFlag(ucFlag, AT_CLIENT_TAB_APP_INDEX);
    }
    else if (1 == gastAtParaList[0].ulParaValue)
    {
        AT_SetCtrlPsCallFlag(ucFlag, AT_CLIENT_TAB_APP_INDEX);
    }
    else if (2 == gastAtParaList[0].ulParaValue)
    {
    
   AT_SetPcui2PsCallFlag(ucFlag, AT_CLIENT_TAB_APP_INDEX);
    }
    else
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : AT_SetNVCHKPara
 功能描述  : AT_CMD_NVCHK
 输入参数  : ucIndex --- 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX  --- ATC返回码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : x00316382
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_SetNVCHKPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8           ucLoopIndex;
    VOS_UINT16          usValidCount[3];
    VOS_UINT16          usNVID[3] = { en_NV_Item_GU_CHECK_ITEM,
                                      en_NV_Item_TL_CHECK_ITEM,
                                      en_NV_Item_GU_M2_CHECK_ITEM };

    /* 参数检查 */
    if ( AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数过多 */
    if ( 1 != gucAtParaIndex )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 未带参数判断 */
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    VOS_MemSet( usValidCount, 0 ,sizeof( usValidCount ));

    /* 读取校验的NV值 */
    for( ucLoopIndex = 0; ucLoopIndex < 3; ucLoopIndex++ )
    {
        if( NV_OK != NV_ReadPartEx( MODEM_ID_0, usNVID[ucLoopIndex], 0, &usValidCount[ucLoopIndex], 2 ))
        {
            return AT_DEVICE_NV_READ_FAILURE;
        }
    }

    /* 如果全0，直接返回不支持 */
    if ( ( 0 == usValidCount[0] ) && ( 0 == usValidCount[1] ) &&( 0 == usValidCount[2] ) )
    {
        return AT_DEVICE_NOT_SUPPORT;
    }

    /* 如果是全部检查，则循环检查全部CRC */
    if ( 0 == gastAtParaList[0].ulParaValue)
    {
        for( ucLoopIndex = 0; ucLoopIndex < 3; ucLoopIndex++ )
        {
            /* 如果当前有效个数不为0，则执行检查 */
            if ( 0 != usValidCount[ucLoopIndex] )
            {
                if ( 0 != mdrv_nv_check_factorynv( ucLoopIndex ) )
                {
                    return AT_ERROR;
                }
            }
        }

        return AT_OK;
    }

    /* 如果有效个数非0，则执行检查 */
    if( 0 != usValidCount[ gastAtParaList[0].ulParaValue - 1 ] )
    {
        /* 如果返回0，为正常，非0为异常 */
        if ( 0 == mdrv_nv_check_factorynv( gastAtParaList[0].ulParaValue - 1 ))
        {
            return AT_OK;
        }
        else
        {
            return AT_ERROR;
        }
    }
    else
    {
        return AT_DEVICE_NOT_SUPPORT;
    }

}



/*****************************************************************************
 函 数 名  : AT_RcvMtaAfcClkInfo
 功能描述  : 处理来自mta模块AFC_INFO消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月24日
    作    者   : C00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaAfcClkInfoCnf(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                                   ucIndex;
    AT_MTA_MSG_STRU                            *pstMtaMsg    = VOS_NULL_PTR;
    MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU    *pstAfcCnf    = VOS_NULL_PTR;
    VOS_UINT32                                  ulRet;

    pstMtaMsg = (AT_MTA_MSG_STRU*)pMsg;

    pstAfcCnf = (MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU*)pstMtaMsg->aucContent;

    /* 初始化消息变量 */
    ucIndex             = 0;
    ulRet               = AT_OK;

     /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaAfcClkInfoCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaAfcClkInfoCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_AFCCLKINFO_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaAfcClkInfoCnf : Current Option is not AT_CMD_AFCCLKINFO_QRY.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstAfcCnf->enResult)
    {
        ulRet = AT_ERROR;
    }
    else
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %u,%d,%d,%d,%u,%u,%u,%u,%u,%u,%u,%u",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstAfcCnf->enStatus,
                                                    pstAfcCnf->lDeviation,
                                                    pstAfcCnf->sCoeffStartTemp,
                                                    pstAfcCnf->sCoeffEndTemp,
                                                    pstAfcCnf->aulCoeffMantissa[0],
                                                    pstAfcCnf->aulCoeffMantissa[1],
                                                    pstAfcCnf->aulCoeffMantissa[2],
                                                    pstAfcCnf->aulCoeffMantissa[3],
                                                    pstAfcCnf->ausCoeffExponent[0],
                                                    pstAfcCnf->ausCoeffExponent[1],
                                                    pstAfcCnf->ausCoeffExponent[2],
                                                    pstAfcCnf->ausCoeffExponent[3]);
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulRet);

    return VOS_OK;

}



/*****************************************************************************
 函 数 名  : AT_SetSecureStatePara
 功能描述  : 命令AT^SECURESTATE设置Secure State
 输入参数  : ucIndex    -- AT通道索引
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月24日
    作    者   : h00360002
    修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32 AT_SetSecureStatePara(VOS_UINT8 ucIndex)
{
    VOS_INT                                 iRst;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
       return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数合法性检查 */
    if ( (1 != gucAtParaIndex)
      || (0 == gastAtParaList[0].usParaLen) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 调用底软提供的接口实现设置操作 */
    iRst = mdrv_efuse_ioctl(MDRV_EFUSE_IOCTL_CMD_SET_SECURESTATE,
                            (VOS_INT)gastAtParaList[0].ulParaValue,
                            VOS_NULL_PTR,
                            0);

    /* 根据底软接口返回的结果返回设置结果 */
    /* 底软返回1时表明重复设置,返回0时设置成功,其他情况设置失败 */
    if (AT_EFUSE_REPEAT == iRst)
    {
        return AT_ERROR;
    }
    else if (AT_EFUSE_OK == iRst)
    {
        return AT_OK;
    }
    else
    {
        AT_WARN_LOG("AT_SetSecureStatePara : Set Secure state req failed.");
    }

    return AT_CME_UNKNOWN;
}

/*****************************************************************************
 函 数 名  : AT_SetKcePara
 功能描述  : 命令AT^KCE设置128bit的key值用于image加密
 输入参数  : ucIndex    -- AT通道索引
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月25日
    作    者   : h00360002
    修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32 AT_SetKcePara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                              ulResult;
    VOS_INT                                 iRst;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
       return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数合法性检查 */
    if ( (1 != gucAtParaIndex)
      || (AT_KCE_PARA_LEN != gastAtParaList[0].usParaLen) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* Ascii转字节流 */
    ulResult = At_AsciiNum2HexString(gastAtParaList[0].aucPara, &gastAtParaList[0].usParaLen);

    if ( (AT_SUCCESS != ulResult)
      || (AT_DRV_KCE_LEN != gastAtParaList[0].usParaLen) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 调用底软提供的接口实现设置操作 */
    iRst = mdrv_efuse_ioctl(MDRV_EFUSE_IOCTL_CMD_SET_KCE,
                            0,
                            gastAtParaList[0].aucPara,
                            (VOS_INT)gastAtParaList[0].usParaLen);

    /* 根据底软接口返回的结果返回设置结果 */
    /* 底软返回1时表明重复设置,返回0时设置成功,其他情况设置失败 */
    if (AT_EFUSE_REPEAT == iRst)
    {
        return AT_ERROR;
    }
    else if (AT_EFUSE_OK == iRst)
    {
        return AT_OK;
    }
    else
    {
        AT_WARN_LOG("AT_SetSecureStatePara : Set KCE req failed.");
    }

    return AT_CME_UNKNOWN;
}

/*****************************************************************************
 函 数 名  : At_QrySecureStatePara
 功能描述  : 命令AT^SECURESTATE查询Secure State
 输入参数  : ucIndex    -- AT通道索引
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月24日
    作    者   : h00360002
    修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32 AT_QrySecureStatePara(VOS_UINT8 ucIndex)
{
    VOS_INT                             iResult;
    VOS_UINT16                          usLength;

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    usLength = 0;

    /* 调用底软提供的借口查询 */
    iResult = mdrv_efuse_ioctl(MDRV_EFUSE_IOCTL_CMD_GET_SECURESTATE,
                               0,
                               VOS_NULL_PTR,
                               0);

    /* 处理异常查询结果 */
    /* 查询失败 */
    if (AT_SECURE_STATE_NOT_SET > iResult)
    {
        return AT_ERROR;
    }

    /* 查询结果异常 */
    if (AT_SECURE_STATE_RMA < iResult)
    {
        return AT_CME_UNKNOWN;
    }

    /* 打印结果 */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     "%s: %d",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                     iResult);

    gstAtSendData.usBufLen = usLength;
    return AT_OK;
}

/*****************************************************************************
 函 数 名  : AT_QrySocidPara
 功能描述  : 命令AT^SOCID查询SOCID
 输入参数  : ucIndex    -- AT通道索引
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月29日
    作    者   : h00360002
    修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32 AT_QrySocidPara(VOS_UINT8 ucIndex)
{
    VOS_INT                                 iResult;
    VOS_UINT16                              usLength;
    VOS_UINT8                               aucSocid[AT_DRV_SOCID_LEN];
    VOS_UINT32                              i;

    /* 局部变量初始化 */
    PS_MEM_SET(aucSocid, 0x00, AT_DRV_SOCID_LEN);
    usLength = 0;

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }



    /* 调用底软提供的借口查询 */

    iResult = mdrv_efuse_ioctl(MDRV_EFUSE_IOCTL_CMD_GET_SOCID,
                               0,
                               aucSocid,
                               AT_DRV_SOCID_LEN);

    /* 处理异常查询结果 */
    if (AT_EFUSE_OK != iResult)
    {
        return AT_ERROR;
    }

    /* 输出结果 */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     "%s: ",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* 用16进制输出码流 */
    for (i = 0; i < AT_DRV_SOCID_LEN; i++)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%02X",
                                          aucSocid[i]);
    }

    gstAtSendData.usBufLen = usLength;
    return AT_OK;
}


/*****************************************************************************
 函 数 名  : AT_SetPdmCtrlPara
 功能描述  : AT_CMD_PDMCTRL
 输入参数  : ucIndex --- 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX  --- ATC返回码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : x00316382
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_SetPdmCtrlPara(VOS_UINT8 ucIndex)
{
    AT_HPA_PDM_CTRL_REQ_STRU                *pstMsg;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数过多 */
    if ( 4 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if ( (0 == gastAtParaList[0].usParaLen)
      || (0 == gastAtParaList[1].usParaLen)
      || (0 == gastAtParaList[2].usParaLen)
      || (0 == gastAtParaList[3].usParaLen) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    pstMsg   = (AT_HPA_PDM_CTRL_REQ_STRU *)AT_ALLOC_MSG_WITH_HDR( sizeof(AT_HPA_PDM_CTRL_REQ_STRU) );

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_SetPdmCtrlPara: alloc msg fail!");
        return AT_ERROR;
    }

    /* 填写消息头 */
    AT_CFG_MSG_HDR( pstMsg, DSP_PID_WPHY, ID_AT_HPA_PDM_CTRL_REQ );

    pstMsg->usMsgID                             = ID_AT_HPA_PDM_CTRL_REQ;
    pstMsg->usRsv                               = 0;
    pstMsg->usPdmRegValue                       = ( VOS_UINT16 )gastAtParaList[0].ulParaValue;
    pstMsg->usPaVbias                           = ( VOS_UINT16 )gastAtParaList[1].ulParaValue;
    pstMsg->usPaVbias2                          = ( VOS_UINT16 )gastAtParaList[2].ulParaValue;
    pstMsg->usPaVbias3                          = ( VOS_UINT16 )gastAtParaList[3].ulParaValue;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_SetPdmCtrlPara: Send msg fail!");
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt      = AT_CMD_PDM_CTRL;                /*设置当前操作模式 */
    g_stAtDevCmdCtrl.ucIndex                    = ucIndex;

    return AT_WAIT_ASYNC_RETURN;                                                /* 等待异步事件返回 */
}

/*****************************************************************************
 函 数 名  : AT_SetCtzuPara
 功能描述  : +CTZU
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX  - ATC返回码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月8日
    作    者   : z00301431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetCtzuPara(VOS_UINT8 ucIndex)
{
    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数个数检查 */
    if (1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 == gastAtParaList[0].usParaLen)
    {
        g_ulCtzuFlag = 0;
    }
    else
    {
        g_ulCtzuFlag = gastAtParaList[0].ulParaValue;
    }

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : AT_QryCtzuPara
 功能描述  : 查询CTZU
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月8日
    作    者   : z00301431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_QryCtzuPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                           usLength;

    /* 参数检查 */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     "%s: %d",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                     g_ulCtzuFlag);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

