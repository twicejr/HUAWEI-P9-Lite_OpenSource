

/************************************************************************
Copyright   : 2005-2008, Huawei Tech. Co., Ltd.
File name   : STKApi.c
Author      : m00128685
Version     : V200R001
Date        : 2008-12-28
Description : 该文件定义了STK模块的对外接口

Description :
History     :

1.日    期  : 2008年12月28日
  作    者  : m00128685
  修改内容  : Create
************************************************************************/

#include "siappstk.h"
#include "si_stk.h"
#include "product_config.h"

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#include "UsimPsInterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID PS_FILE_ID_STK_API_C
/*lint +e767*/

/*****************************************************************************
函 数 名  : GetMainMenu
功能描述  : 获取STK功能的主菜单
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_UINT32函数执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年7月6日
  作    者  : H9254
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STK_SendReqMsg(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId, 
    VOS_UINT32                          MsgName,
    VOS_UINT32                          CmdType, 
    VOS_UINT32                          DataLen, 
    VOS_UINT8                           *pData)
{
    SI_STK_REQ_STRU         *pstSTKReq;
    VOS_UINT32              ulSendPid;
    VOS_UINT32              ulReceiverPid;
#if (OSA_CPU_ACPU == VOS_OSA_CPU)
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    MODEM_ID_ENUM_UINT16    enModemID;
#endif  /*( FEATURE_MULTI_MODEM == FEATURE_ON )*/

    ulSendPid = WUEPS_PID_AT;

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    /* 调用接口获取Modem ID */
    if(VOS_OK != AT_GetModemIdFromClient(ClientId,&enModemID))
    {
      STK_ERROR_LOG("SI_STK_SendReqMsg: AT_GetModemIdFromClient Return Error");
      return VOS_ERR;
    }

    if(MODEM_ID_1 == enModemID)
    {
        ulReceiverPid = I1_MAPS_STK_PID;
    }
#if (MULTI_MODEM_NUMBER == 3)
    else if(MODEM_ID_2 == enModemID)
    {
        ulReceiverPid = I2_MAPS_STK_PID;
    }
#endif
    else
    {
        ulReceiverPid = I0_MAPS_STK_PID;
    }
#else
    ulReceiverPid = MAPS_STK_PID;
#endif  /*( FEATURE_MULTI_MODEM == FEATURE_ON )*/

#else   /*CCPU STK->STK*/
    ulSendPid = MAPS_STK_PID;
    ulReceiverPid = MAPS_STK_PID;
#endif  /* (OSA_CPU_ACPU == VOS_OSA_CPU) */

    pstSTKReq = (SI_STK_REQ_STRU *)VOS_AllocMsg(ulSendPid, sizeof(SI_STK_REQ_STRU)-VOS_MSG_HEAD_LENGTH+DataLen);

    if(VOS_NULL_PTR == pstSTKReq)
    {
        STK_ERROR_LOG("SI_STK_SendReqMsg: VOS_AllocMsg Return Error");
        return VOS_ERR;
    }

    pstSTKReq->MsgName       = MsgName;
    pstSTKReq->ulReceiverPid = ulReceiverPid;
    pstSTKReq->OpId          = OpId;
    pstSTKReq->ClientId      = ClientId;
    pstSTKReq->SatType       = CmdType;
    pstSTKReq->Datalen       = DataLen;

    if(DataLen != 0)
    {
        /*lint -e534*/
        VOS_MemCpy(pstSTKReq->Data, pData, DataLen);
        /*lint +e534*/
    }

    if(VOS_OK != VOS_SendMsg(ulSendPid, pstSTKReq))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

#if  ((OSA_CPU_ACPU == VOS_OSA_CPU) || (defined(DMT)))
/*****************************************************************************
函 数 名  : GetMainMenu
功能描述  : 获取STK功能的主菜单
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_UINT32函数执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年7月6日
  作    者  : H9254
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STK_GetMainMenu(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId)
{
    return SI_STK_SendReqMsg(ClientId,OpId, SI_STK_GETMAINMNUE, SI_STK_NOCMDDATA,0,VOS_NULL_PTR);
}

/*****************************************************************************
函 数 名  : SI_STK_GetSTKCommand
功能描述  : 获取缓存的STK主动命令
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_UINT32函数执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2008年10月18日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STK_GetSTKCommand(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    SI_STK_CMD_TYPE                     CmdType)
{
    return SI_STK_SendReqMsg(ClientId,OpId, SI_STK_GETCOMMAND, CmdType,0,VOS_NULL_PTR);
}

/*****************************************************************************
函 数 名  : SI_STK_QuerySTKCommand
功能描述  : 查询最后一次SIM卡上报的主动命令
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_UINT32函数执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2008年10月18日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STK_QuerySTKCommand(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId)
{
#if (( FEATURE_MULTI_MODEM == FEATURE_ON )&&(!defined(DMT)))
    return VOS_ERR;
#else
    return SI_STK_SendReqMsg(ClientId,OpId, SI_STK_QUERYCOMMAND, SI_STK_NOCMDDATA,0,VOS_NULL_PTR);
#endif
}

/*****************************************************************************
函 数 名  : SI_STK_DataSendSimple
功能描述  : 终端给予下发数据函数
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_UINT32函数执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2008年10月18日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STK_DataSendSimple(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    SI_SEND_DATA_TYPE                   SendType,
    VOS_UINT32                          DataLen,
    VOS_UINT8                           *pData)
{
    return SI_STK_SendReqMsg(ClientId,OpId, SI_STK_SIMPLEDOWN,SendType,DataLen,pData);
}

/*****************************************************************************
函 数 名  : SI_STK_TerminalResponse
功能描述  : 终端给予响应函数
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_UINT32函数执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2008年10月18日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STK_TerminalResponse(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    SI_STK_TERMINAL_RSP_STRU            *pstTRStru)
{
#if (( FEATURE_MULTI_MODEM == FEATURE_ON )&&(!defined(DMT)))
    return VOS_ERR;
#else

    if(pstTRStru == VOS_NULL_PTR)
    {
        STK_ERROR_LOG("SI_STK_TerminalResponse: The input parameter is null.");

        return VOS_ERR;
    }

    return SI_STK_SendReqMsg(ClientId,OpId, SI_STK_TRDOWN, SI_STK_NOCMDDATA,sizeof(SI_STK_TERMINAL_RSP_STRU),(VOS_UINT8*)pstTRStru);
#endif
}


/*****************************************************************************
函 数 名  : SI_STKDualIMSIChangeReq
功能描述  : 触发IMSI切换流程，沃达丰定制流程
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_UINT32函数执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2010年02月10日
  作    者  : m00128685
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STKDualIMSIChangeReq(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId)
{
#if (( FEATURE_MULTI_MODEM == FEATURE_ON )&&(!defined(DMT)))
    return TAF_FAILURE;
#else
    SI_STK_REQ_STRU *pstSTKReq;

    pstSTKReq = (SI_STK_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_STK_REQ_STRU)-VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR ==pstSTKReq)
    {
        STK_ERROR_LOG("SI_STKDualIMSIChangeReq: VOS_AllocMsg Return Error");
        return VOS_ERR;
    }

    pstSTKReq->ClientId      = ClientId;
    pstSTKReq->OpId          = OpId;
    pstSTKReq->MsgName       = SI_STK_IMSICHG;
    pstSTKReq->ulReceiverPid = MAPS_STK_PID;

    if(VOS_OK != VOS_SendMsg(MAPS_STK_PID, pstSTKReq))
    {
        STK_ERROR_LOG("SI_STKDualIMSIChangeReq: VOS_SendMsg Return Error");
        return VOS_ERR;
    }

    return VOS_OK;
#endif
}

/*****************************************************************************
函 数 名  : SI_STKIsDualImsiSupport
功能描述  : 判断是否支持Dual IMSI切换
输入参数  : 无
输出参数  : 无
返 回 值  : 执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2010年02月11日
  作    者  : m00128685
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STKIsDualImsiSupport(VOS_VOID)
{
#if (( FEATURE_MULTI_MODEM == FEATURE_ON )&&(!defined(DMT)))
    return TAF_FAILURE;
#else
    VOS_UINT16 usDualIMSIFlag = 0;

    if ( NV_OK != NV_Read(en_NV_Item_NV_HUAWEI_DOUBLE_IMSI_CFG_I, &usDualIMSIFlag, sizeof(VOS_UINT16)) )
    {
        STK_WARNING_LOG("STK_InitGobal: Read en_NV_Item_NV_HUAWEI_DOUBLE_IMSI_CFG_I Fail");
    }

    /* 前后两个自节均为1，Dual IMSI功能才开启，第一个字节为NV激活标志，第二个为使能位 */
    if ( STK_NV_ENABLED == usDualIMSIFlag )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
#endif
}

/*****************************************************************************
函 数 名  : SI_STK_MenuSelection
功能描述  : STK功能ENVELOP下载函数
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_UINT32函数执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2008年10月18日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/

VOS_UINT32 SI_STK_MenuSelection(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    SI_STK_ENVELOPE_STRU                *pstENStru)
{
#if (( FEATURE_MULTI_MODEM == FEATURE_ON )&&(!defined(DMT)))
    return TAF_FAILURE;
#else
    if((VOS_NULL_PTR == pstENStru)||(SI_STK_ENVELOPE_MENUSEL != pstENStru->enEnvelopeType))
    {
        STK_ERROR_LOG("SI_STK_MenuSelection: The Input Data is Error");

        return VOS_ERR;
    }

    return SI_STK_SendReqMsg(ClientId,OpId, SI_STK_MENUSELECTION, pstENStru->enEnvelopeType,sizeof(SI_STK_ENVELOPE_STRU),(SI_UINT8*)pstENStru);
#endif
}

/*****************************************************************************
函 数 名  : SI_STK_SetUpCallConfirm
功能描述  : 用户回复是否允许发起呼叫
输入参数  : ulAction -- 用户回复结果
输出参数  : 无
返 回 值  : 执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2012年9月14日
  作    者  : j00168360
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STK_SetUpCallConfirm(
    MN_CLIENT_ID_T                      ClientId, 
    SI_STK_SETUPCALLCONFIRM_ENUM_UINT32 enAction)
{
    /* 参数检查 */
    if (SI_STK_SETUPCALL_BUTT <= enAction)
    {
        STK_ERROR_LOG("SI_STK_SetUpCallConfirm: The Input Para is Error");

        return VOS_ERR;
    }

    return SI_STK_SendReqMsg(ClientId, 0, SI_STK_SETUPCALL_CONFIRM, SI_STK_SETUPCALL, sizeof(VOS_UINT32), (VOS_UINT8*)&enAction);
}
#endif

#if ((OSA_CPU_CCPU == VOS_OSA_CPU) || (defined(DMT)))
/*****************************************************************************
函 数 名  : SI_STKGetCurImsiSign
功能描述  : 获取当前IMSI对应的符号
输入参数  : 无
输出参数  : 0或1
返 回 值  : 执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2010年02月11日
  作    者  : m00128685
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STKGetCurImsiSign(
    VOS_UINT16                          *pusDualIMSIEnable, 
    VOS_UINT32                          *pulCurImsiSign)
{
    VOS_UINT32 i;
    VOS_UINT32 j;

    *pulCurImsiSign = gstSTKIMSIChgCtrl.ulCurImsiSign;

    *pusDualIMSIEnable = VOS_FALSE;

    /* 判断是否存在主菜单 */
    if (SI_STK_MENU_EXIST != gstSetUpMenuData.ucUsatTag)
    {
        STK_WARNING_LOG("SI_STKGetCurImsiSign: There is any Main Menu Content");

        return;
    }

    /* 在主菜单中匹配，如果匹配失败pusDualIMSIEnable设置为Disable，*/
    for (i = 0; i < gstSetUpMenuData.stSetUpMenu.ulItemNum; i++)
    {
        for (j = 0; j < gstSTKIMSIMatch.usMatchStrCnt; j++)
        {
            if (VOS_TRUE == SI_STK_StrStr(gstSetUpMenuData.stSetUpMenu.Item[i].pucItemText,
                                          gstSTKIMSIMatch.astMatchStr[j].aucMatchStr,
                                          gstSetUpMenuData.stSetUpMenu.Item[i].ucLen,
                                          gstSTKIMSIMatch.astMatchStr[j].usStrLen))
            {
                *pusDualIMSIEnable = VOS_TRUE;

                return;
            }
        }
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_CCResultInd
功能描述  : 将MO CALL CONTROL的结果广播上报给AT
输入参数  : pstRspData--指向CALL CONTROL的解码后码流
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2012年09月14日
  作    者  : j00168360
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_CCResultInd(
    SI_STK_ENVELOPE_RSP_STRU            *pstRspData)
{
/*lint -e813*/
    SI_STK_EVENT_INFO_STRU              stEvent;

    /*lint -e534*/
    VOS_MemSet(&stEvent, 0, sizeof(stEvent));
    /*lint +e534*/

    stEvent.STKCBEvent                                  = SI_STK_CC_RESULT_IND_EVENT;
    stEvent.STKErrorNo                                  = VOS_OK;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.ucResult    = (SI_UINT8)pstRspData->Result;

    if (USSD_STRING_TAG == (pstRspData->uResp.CallCtrlRsp.SpecialData.ucTag & 0x7F))
    {
        stEvent.STKCmdStru.CmdStru.STKCcIndInfo.ucType = SI_STK_USSD_CALL_CTRL;
    }
    else if (SS_STRING_TAG == (pstRspData->uResp.CallCtrlRsp.SpecialData.ucTag & 0x7F))
    {
        stEvent.STKCmdStru.CmdStru.STKCcIndInfo.ucType = SI_STK_SS_CALL_CTRL;
    }
    else if (ADDRESS_TAG == (pstRspData->uResp.CallCtrlRsp.SpecialData.ucTag & 0x7F))
    {
        stEvent.STKCmdStru.CmdStru.STKCcIndInfo.ucType = SI_STK_MO_CALL_CTRL;
    }
    else
    {
        return;
    }

    /* COPY aplhaid 字段 */
    if (VOS_TRUE == pstRspData->uResp.CallCtrlRsp.OP_Alaph)
    {
        stEvent.STKCmdStru.CmdStru.STKCcIndInfo.stAlphaIdInfo.ulAlphaLen
                                                        = pstRspData->uResp.CallCtrlRsp.AlphaId.ulLen;
        /*lint -e534*/
        VOS_MemCpy(stEvent.STKCmdStru.CmdStru.STKCcIndInfo.stAlphaIdInfo.aucAlphaId,
                   pstRspData->uResp.CallCtrlRsp.AlphaId.pucAlphabet,
                   stEvent.STKCmdStru.CmdStru.STKCcIndInfo.stAlphaIdInfo.ulAlphaLen);
        /*lint +e534*/
    }

    if (VOS_TRUE == pstRspData->uResp.CallCtrlRsp.OP_SepcialData)
    {
        /* 解析类型字段 */
        stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stCtrlDataInfo.ucDataType
                                                       = pstRspData->uResp.CallCtrlRsp.SpecialData.pValue[0];
        /* 数据字段copy */
        stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stCtrlDataInfo.usDataLen
                                                        = pstRspData->uResp.CallCtrlRsp.SpecialData.ucLen - 1;

        /*lint -e534*/
        VOS_MemCpy(stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stCtrlDataInfo.aucData,
                   &pstRspData->uResp.CallCtrlRsp.SpecialData.pValue[1],
                   pstRspData->uResp.CallCtrlRsp.SpecialData.ucLen - 1);
        /*lint +e534*/
    }

    SI_STKCallBack_BroadCast(&stEvent);
/*lint +e813*/
    return;
}

/*****************************************************************************
函 数 名  : SI_STK_SMSCtrlResultInd
功能描述  : 将MO SMS CONTROL的结果广播上报给AT
输入参数  : pstRspData--指向SMS CONTROL的解码后码流
输出参数  : 无
返 回 值  : 执行结果
History     :
1.日    期  : 2012年09月14日
  作    者  : j00168360
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_SMSCtrlResultInd(
    SI_STK_ENVELOPE_RSP_STRU            *pstRspData)
{
    //需要确认addr1是目的地址还是addr2
/*lint -e813*/
    SI_STK_EVENT_INFO_STRU              stEvent;

    /*lint -e534*/
    VOS_MemSet(&stEvent, 0, sizeof(stEvent));
    /*lint +e534*/

    stEvent.STKCBEvent                                  = SI_STK_SMSCTRL_RESULT_IND_EVENT;
    stEvent.STKErrorNo                                  = VOS_OK;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.ucResult    = (SI_UINT8)pstRspData->Result;
    stEvent.STKCmdStru.CmdStru.STKCcIndInfo.ucType      = SI_STK_SMS_CTRL;


    /* COPY aplhaid 字段 */
    if (VOS_TRUE == pstRspData->uResp.MoSmsCtrlRsp.OP_Alaph)
    {

        stEvent.STKCmdStru.CmdStru.STKCcIndInfo.stAlphaIdInfo.ulAlphaLen
                                                        = pstRspData->uResp.MoSmsCtrlRsp.AlphaId.ulLen;
        /*lint -e534*/
        VOS_MemCpy(stEvent.STKCmdStru.CmdStru.STKCcIndInfo.stAlphaIdInfo.aucAlphaId,
                   pstRspData->uResp.MoSmsCtrlRsp.AlphaId.pucAlphabet,
                   stEvent.STKCmdStru.CmdStru.STKCcIndInfo.stAlphaIdInfo.ulAlphaLen);
        /*lint +e534*/
    }

    if (VOS_TRUE == pstRspData->uResp.MoSmsCtrlRsp.OP_Addr1)
    {
        /* 解析目的地址类型字段 */
        stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stMoSmsCtrlInfo.stDstAddrInfo.ucNumType
                                                            = pstRspData->uResp.MoSmsCtrlRsp.Addr1.ucNumType;
        /* copy目的地址 */
        stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stMoSmsCtrlInfo.stDstAddrInfo.ucAddrLen
                                                            = pstRspData->uResp.MoSmsCtrlRsp.Addr1.ucLen;

        /*lint -e534*/
        VOS_MemCpy(stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stMoSmsCtrlInfo.stDstAddrInfo.aucAddr,
                   pstRspData->uResp.MoSmsCtrlRsp.Addr1.pucAddr,
                   pstRspData->uResp.MoSmsCtrlRsp.Addr1.ucLen);
        /*lint +e534*/
    }

    if (VOS_TRUE == pstRspData->uResp.MoSmsCtrlRsp.OP_Addr2)
    {
        /* 解析服务中心地址类型字段 */
        stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stMoSmsCtrlInfo.stSerCenterAddrInfo.ucNumType
                                                          = pstRspData->uResp.MoSmsCtrlRsp.Addr2.ucNumType;

        /* copy服务中心号码 */
        stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stMoSmsCtrlInfo.stSerCenterAddrInfo.ucAddrLen
                                                            =pstRspData->uResp.MoSmsCtrlRsp.Addr2.ucLen;

        /*lint -e534*/
        VOS_MemCpy(stEvent.STKCmdStru.CmdStru.STKCcIndInfo.uInfo.stMoSmsCtrlInfo.stSerCenterAddrInfo.aucAddr,
                   pstRspData->uResp.MoSmsCtrlRsp.Addr2.pucAddr,
                   pstRspData->uResp.MoSmsCtrlRsp.Addr2.ucLen);
        /*lint +e534*/
    }

    SI_STKCallBack_BroadCast(&stEvent);
/*lint +e813*/
    return;
}

/*****************************************************************************
函 数 名  : SI_STK_DecodeCCRspSpecial
功能描述  : STK功能ENVELOP回复数据解码
输入参数  : ulDataLen:  需要解码的数据长度
            pucData:    需要解码的数据内容
输出参数  : pstRspData: 解码后的数据内容
返 回 值  : VOS_VOID
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2010年06月02日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_DecodeCCRspSpecial(
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                           *pucCmdData,
    SI_STK_ENVELOPE_RSP_STRU            *pstRspData)
{
    VOS_UINT8   aucTagList[]={ADDRESS_TAG,SS_STRING_TAG,USSD_STRING_TAG,PDP_CONTEXT_ACTIVATION_PAR_TAG,EPSPDN_ACTIVE_PARA_TAG};
    VOS_UINT32  i;
    VOS_UINT32  ulCCTagOffset;

    for(i=0; i<sizeof(aucTagList); i++)
    {
        ulCCTagOffset = SI_STKFindTag(aucTagList[i], pucCmdData, ulDataLen, 1);

        if(ulCCTagOffset != SI_TAGNOTFOUND)
        {
            pstRspData->uResp.CallCtrlRsp.SpecialData.ucTag = pucCmdData[ulCCTagOffset-1] & 0x7F;
            pstRspData->uResp.CallCtrlRsp.SpecialData.ucLen = pucCmdData[ulCCTagOffset];
            pstRspData->uResp.CallCtrlRsp.SpecialData.pValue
                = (SI_UINT8*)VOS_MemAlloc(MAPS_STK_PID, DYNAMIC_MEM_PT, pucCmdData[ulCCTagOffset]);

            if(VOS_NULL_PTR != pstRspData->uResp.CallCtrlRsp.SpecialData.pValue)
            {
                /*lint -e534*/
                VOS_MemCpy(pstRspData->uResp.CallCtrlRsp.SpecialData.pValue,
                    &pucCmdData[ulCCTagOffset+1], pucCmdData[ulCCTagOffset]);
                /*lint +e534*/
            }

            pstRspData->uResp.CallCtrlRsp.OP_SepcialData = 1;

            return;
        }
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_DecodeMoSmsRspSpecial
功能描述  : STK功能ENVELOP回复数据解码
输入参数  : ulDataLen:  需要解码的数据长度
            pucData:    需要解码的数据内容
输出参数  : pstRspData: 解码后的数据内容
返 回 值  : VOS_VOID
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2010年06月02日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_DecodeMoSmsRspSpecial(
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                           *pucCmdData,
    SI_STK_ENVELOPE_RSP_STRU            *pstRspData)
{
    VOS_UINT32  ulTagOffset;

    ulTagOffset = SI_STKFindTag(ADDRESS_TAG, pucCmdData, ulDataLen, 1);

    if(ulTagOffset != SI_TAGNOTFOUND)
    {
        pstRspData->uResp.MoSmsCtrlRsp.Addr1.ucLen = pucCmdData[ulTagOffset] - 1;
        pstRspData->uResp.MoSmsCtrlRsp.Addr1.ucNumType = pucCmdData[ulTagOffset+1];
        pstRspData->uResp.MoSmsCtrlRsp.Addr1.pucAddr
            = (SI_UINT8*)VOS_MemAlloc(MAPS_STK_PID, DYNAMIC_MEM_PT, pstRspData->uResp.MoSmsCtrlRsp.Addr1.ucLen);

        if(VOS_NULL_PTR != pstRspData->uResp.MoSmsCtrlRsp.Addr1.pucAddr)
        {
            /*lint -e534*/
            VOS_MemCpy(pstRspData->uResp.MoSmsCtrlRsp.Addr1.pucAddr,
                &pucCmdData[ulTagOffset+2], pstRspData->uResp.MoSmsCtrlRsp.Addr1.ucLen);
            /*lint +e534*/
        }

        pstRspData->uResp.MoSmsCtrlRsp.OP_Addr1 = 1;
    }

    ulTagOffset = SI_STKFindTag(ADDRESS_TAG, pucCmdData, ulDataLen, 2);

    if(ulTagOffset != SI_TAGNOTFOUND)
    {
        pstRspData->uResp.MoSmsCtrlRsp.Addr2.ucLen = pucCmdData[ulTagOffset] - 1;
        pstRspData->uResp.MoSmsCtrlRsp.Addr2.ucNumType = pucCmdData[ulTagOffset+1];
        pstRspData->uResp.MoSmsCtrlRsp.Addr2.pucAddr
            = (SI_UINT8*)VOS_MemAlloc(MAPS_STK_PID, DYNAMIC_MEM_PT, pstRspData->uResp.MoSmsCtrlRsp.Addr2.ucLen);

        if(VOS_NULL_PTR != pstRspData->uResp.MoSmsCtrlRsp.Addr2.pucAddr)
        {
            /*lint -e534*/
            VOS_MemCpy(pstRspData->uResp.MoSmsCtrlRsp.Addr2.pucAddr,
                &pucCmdData[ulTagOffset+2], pstRspData->uResp.MoSmsCtrlRsp.Addr2.ucLen);
            /*lint +e534*/
        }

        pstRspData->uResp.MoSmsCtrlRsp.OP_Addr2 = 1;
    }

    return;
}


/*****************************************************************************
函 数 名  : SI_STK_EnvelopeRsp_Decode
功能描述  : STK功能ENVELOP回复数据解码
输入参数  : enDataType: 解码的信封命令数据类型
            ulDataLen:  需要解码的数据长度
            pucData:    需要解码的数据内容
输出参数  : pstRspData: 解码后的数据内容
返 回 值  : VOS_UINT32函数执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2010年06月02日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/

VOS_UINT32 SI_STK_EnvelopeRsp_Decode(
    SI_STK_ENVELOPE_TYPE_UINT32         enDataType,
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                           *pucCmdData,
    SI_STK_ENVELOPE_RSP_STRU            *pstRspData)
{
    VOS_UINT32  i;
    VOS_UINT32  ulOffset;

    if((pucCmdData == VOS_NULL_PTR)||(pstRspData == VOS_NULL_PTR))
    {
        STK_ERROR_LOG("SI_STKCommCodeData: The Input Parameter is Error");

        return VOS_ERR;
    }

    pstRspData->EnvelopeType    = enDataType;
    pstRspData->Result          = pucCmdData[0];

    if(pucCmdData[0] > 0x80)/*确定主动命令的长度字节*/
    {
        ulOffset = 0x02;
    }
    else
    {
        ulOffset = 0x01;
    }

    for(i=0; i<ARRAYSIZE(gastEnvelopeDecodeList); i++)
    {
        if(enDataType == gastEnvelopeDecodeList[i].ulCmdType)
        {
            SI_STKDecodeTagList(&pucCmdData[ulOffset],
                                gastEnvelopeDecodeList[i].pucTagList,
                                gastEnvelopeDecodeList[i].ulTagLen,
                                (SI_SAT_COMMDATA_STRU *)pstRspData);

            break;
        }
    }

    if(i >= ARRAYSIZE(gastEnvelopeDecodeList))
    {
        STK_ERROR_LOG("SI_STKCommCodeData: The Input enDataType is Error");

        return VOS_ERR;
    }

    if(enDataType == SI_STK_ENVELOPE_CALLCRTL)
    {
        SI_STK_DecodeCCRspSpecial((VOS_UINT32)pucCmdData[ulOffset], &pucCmdData[ulOffset+1], pstRspData);
    }

    if(enDataType == SI_STK_ENVELOPE_SMSCRTL)
    {
        SI_STK_DecodeMoSmsRspSpecial((VOS_UINT32)pucCmdData[ulOffset], &pucCmdData[ulOffset+1], pstRspData);
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_STK_EnvelopeData_Code
功能描述  : STK功能ENVELOP下载数据编码
输入参数  : pstENStru: 下发的信封命令数据结构
输出参数  : pulDataLen: 编码后的数据长度
            pucData:    编码后的数据内容，输入数据空间要求至少要256个字节
            pulDataOffset: 编码后的有效数据起始偏移
返 回 值  : VOS_UINT32函数执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2010年06月02日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/

VOS_UINT32 SI_STK_EnvelopeData_Code(
    SI_STK_ENVELOPE_STRU                *pstENStru,
    VOS_UINT32                          *pulDataLen,
    VOS_UINT8                           *pucData,
    VOS_UINT32                          *pulDataOffset)
{
    if((pstENStru           == VOS_NULL_PTR)
        ||(pulDataLen       == VOS_NULL_PTR)
        ||(pucData          == VOS_NULL_PTR)
        ||(pulDataOffset    == VOS_NULL_PTR))
    {
        STK_ERROR_LOG("SI_STK_EnvelopeData_Code: The Input Data is Error");

        return VOS_ERR;
    }

    SI_STK_InitEnvelope(pucData, &pstENStru->DeviceId, (VOS_UINT8)pstENStru->enEnvelopeType);

    if (pstENStru->enEnvelopeType == SI_STK_ENVELOPE_CALLCRTL)
    {
        if(pstENStru->uEnvelope.CallCtrl.OP_SepcialData != 0)
        {
            pucData[2] += pstENStru->uEnvelope.CallCtrl.SpecialData.ucLen+2;
            pucData[7] = pstENStru->uEnvelope.CallCtrl.SpecialData.ucTag;
            pucData[8] = pstENStru->uEnvelope.CallCtrl.SpecialData.ucLen;

            /*lint -e534*/
            VOS_MemCpy(&pucData[9], pstENStru->uEnvelope.CallCtrl.SpecialData.pValue, pstENStru->uEnvelope.CallCtrl.SpecialData.ucLen);
            /*lint +e534*/
        }
    }

    if(VOS_OK != SI_STKCommCodeData(&pucData[1], SI_CODE_ENVELOPE_DATA, pstENStru->enEnvelopeType, (SI_SAT_COMMDATA_STRU*)pstENStru))
    {
        STK_ERROR_LOG("SI_STK_EnvelopeData_Code: The Code Data is Error");

        return VOS_ERR;
    }

    if(pucData[2] > 0x7F)
    {
        pucData[1] = 0x81;

        *pulDataLen = pucData[2] + 3;

        *pulDataOffset = 0;
    }
    else
    {
        *pulDataLen   = pucData[2] + 2;

        *pulDataOffset = 1;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :
功能描述  :
输入参数  :
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_EnvelopeRspDataFree(
    SI_STK_ENVELOPE_RSP_STRU                *pstData)
{
    VOS_UINT32 i;
    VOS_UINT32 j;
    VOS_UINT32 ulOffset = 0;
    VOS_UINT8* pData;

    if(VOS_NULL_PTR == pstData)
    {
        STK_ERROR_LOG("SI_STK_EnvelopeRspDataFree: The Input Parameter is Error");

        return ;
    }

    pData = (VOS_UINT8*)&(pstData->uResp)+sizeof(VOS_UINT32);

    for(i=0; i<STK_ARRAYSIZE(gastEnvelopeDecodeList); i++)
    {
        if(pstData->EnvelopeType == gastEnvelopeDecodeList[i].ulCmdType)
        {
            for(j=0; j<gastEnvelopeDecodeList[i].ulTagLen; j++)
            {
                ulOffset = SI_STKTagDataFree(*(gastEnvelopeDecodeList[i].pucTagList+j), pData);

                pData += ulOffset;
            }

            break;
        }
    }

    if((pstData->EnvelopeType == SI_STK_ENVELOPE_CALLCRTL)
      &&(pstData->uResp.CallCtrlRsp.OP_SepcialData != 0))
    {
        /*lint -e534*/
        VOS_MemFree(MAPS_STK_PID, pstData->uResp.CallCtrlRsp.SpecialData.pValue);
        /*lint +e534*/
    }

    if(pstData->EnvelopeType == SI_STK_ENVELOPE_SMSCRTL)
    {
        if(pstData->uResp.MoSmsCtrlRsp.OP_Addr1 != 0)
        {
            /*lint -e534*/
            VOS_MemFree(MAPS_STK_PID, pstData->uResp.MoSmsCtrlRsp.Addr1.pucAddr);
            /*lint +e534*/
        }

        if(pstData->uResp.MoSmsCtrlRsp.OP_Addr2 != 0)
        {
            /*lint -e534*/
            VOS_MemFree(MAPS_STK_PID, pstData->uResp.MoSmsCtrlRsp.Addr2.pucAddr);
            /*lint +e534*/
        }
    }

    return ;
}

/*****************************************************************************
函 数 名  : SI_STK_CLSndTrMsg
功能描述  : C+L共SIM卡CBP发送TERMINAL RESPONSE
输入参数  : DataLen:数据长度
            pData:数据内容
输出参数  : 无
返 回 值  : VOS_UINT32函数执行结果
History     :
1.日    期  : 2013年12月20日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STK_CLSndTrMsg(
    VOS_UINT32                          ulDataLen, 
    VOS_UINT8                           *pucData)
{
    SI_STK_REQ_STRU                    *pstSTKReq;

    pstSTKReq = (SI_STK_REQ_STRU *)VOS_AllocMsg(MAPS_STK_PID, sizeof(SI_STK_REQ_STRU) - VOS_MSG_HEAD_LENGTH + ulDataLen);

    if (VOS_NULL_PTR == pstSTKReq)
    {
        STK_ERROR_LOG("SI_STK_CLSndTrMsg: VOS_AllocMsg Return Error");
        return VOS_ERR;
    }

    pstSTKReq->MsgName       = SI_STK_VIA_TRDOWN;
    pstSTKReq->ulReceiverPid = MAPS_STK_PID;
    pstSTKReq->OpId          = 0;
    pstSTKReq->ClientId      = 0;
    pstSTKReq->SatType       = SI_STK_TRSEND;
    pstSTKReq->Datalen       = ulDataLen;

    if (VOS_NULL != ulDataLen)
    {
        /*lint -e534*/
        VOS_MemCpy(pstSTKReq->Data, pucData, ulDataLen);
        /*lint +e534*/
    }

    if (VOS_OK != VOS_SendMsg(MAPS_STK_PID, pstSTKReq))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_STK_CbpSetupEventListCmdSnd
功能描述  : C+L共SIM卡BALONG向CBP发送SETUP EVENT LIST命令
输入参数  : 无
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2014年01月22日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_CbpSetupEventListCmdSnd(VOS_VOID)
{
    if ((VOS_NULL_PTR == g_stCbpEventList.pucCmd)
     || (VOS_NULL == g_stCbpEventList.ulProactiveCmdLen))
    {
        return;
    }

    SI_STK_SndProactiveCmd2CBP(g_stCbpEventList.ulProactiveCmdLen, g_stCbpEventList.pucCmd);

    /*lint -e534*/
    VOS_MemFree(MAPS_STK_PID, g_stCbpEventList.pucCmd);
    /*lint +e534*/

    g_stCbpEventList.pucCmd            = VOS_NULL_PTR;
    g_stCbpEventList.ulProactiveCmdLen = VOS_NULL;

    return;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



