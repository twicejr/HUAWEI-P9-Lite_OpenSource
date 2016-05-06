/************************************************************************
Copyright   : 2005-2008, Huawei Tech. Co., Ltd.
File name   : SimProc.c
Author      : z00100318
Version     : V200R001
Date        : 2008-10-18
Description : 该文件定义了SIM卡事件实现

Description : SIM卡事件的处理和实现
History     :

1.日    期  : 2008年10月28日
  作    者  : H59254
  修改内容  : Create
************************************************************************/

#include "si_stk.h"
#include "siapppih.h"
#include "AtOamInterface.h"
#include "pamom.h"
#include "NasNvInterface.h"
#include "LNasStkInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID PS_FILE_ID_STK_PROC_C
/*lint +e767*/



SI_STK_CMDHANDLE_LIST_STRU gSTKCmdHandleList[]=
{
    {SI_STK_REFRESH             ,   SI_STKCommDecode            ,   SI_STK_RefreshProc},
    {SI_STK_MORETIME            ,   SI_STKNoNeedDecode          ,   SI_STK_MoreTimeProc},
    {SI_STK_POLLINTERVAL        ,   SI_STKCommDecode            ,   SI_STK_PollIntervalProc},
    {SI_STK_POLLINGOFF          ,   SI_STKNoNeedDecode          ,   SI_STK_PollingOFFProc},
    {SI_STK_SETUPEVENTLIST      ,   SI_STKCommDecode            ,   SI_STK_SetUpEeventListSpecialProc},
    {SI_STK_SETUPCALL           ,   SI_STKSetUpCall_Decode      ,   SI_STK_SetCallSpecialProc},
    {SI_STK_SENDSS              ,   SI_STKCommDecode            ,   SI_STK_SendSSProc},
    {SI_STK_SENDUSSD            ,   SI_STKCommDecode            ,   SI_STK_SendUSSDProc},
    {SI_STK_SENDSMS             ,   SI_STKCommDecode            ,   SI_STK_SendSMSProc},
    {SI_STK_SENDDTMF            ,   SI_STKCommDecode            ,   SI_STK_SendDTMFProc},
    {SI_STK_LAUNCHBROWSER       ,   SI_STK_LaunchBrowser_Decode ,   SI_STKDataIndCallback},
    {SI_STK_PLAYTONE            ,   SI_STKCommDecode            ,   SI_STKDataIndCallback},
    {SI_STK_DISPLAYTET          ,   SI_STKCommDecode            ,   SI_STK_DisplayTextProc},
    {SI_STK_GETINKEY            ,   SI_STKCommDecode            ,   SI_STKDataIndCallback},
    {SI_STK_GETINPUT            ,   SI_STKCommDecode            ,   SI_STKDataIndCallback},
    {SI_STK_SELECTITEM          ,   SI_STK_SelectItem_Decode    ,   SI_STKDataIndCallback},
    {SI_STK_SETUPMENU           ,   SI_STK_SetUpMenu_Decode     ,   SI_STK_SetUpMenuProc},
    {SI_STK_PROVIDELOCALINFO    ,   SI_STKCommDecode            ,   SI_STK_ProvideLocIProc},
    {SI_STK_TIMERMANAGEMENT     ,   SI_STKCommDecode            ,   SI_STK_TimerManageProc},
    {SI_STK_SETUPIDLETEXT       ,   SI_STKCommDecode            ,   SI_STK_SetUpIdleTextProc},
    {SI_STK_PERFORMCARDAPDU     ,   VOS_NULL_PTR                ,   VOS_NULL_PTR},
    {SI_STK_POWERONCARD         ,   VOS_NULL_PTR                ,   VOS_NULL_PTR},
    {SI_STK_POWEROFFCARD        ,   VOS_NULL_PTR                ,   VOS_NULL_PTR},
    {SI_STK_GETREADERSTATUS     ,   VOS_NULL_PTR                ,   VOS_NULL_PTR},
    {SI_STK_RUNATCOMMAND        ,   VOS_NULL_PTR                ,   VOS_NULL_PTR},
    {SI_STK_LANGUAGENOTIFICATION,   SI_STKCommDecode            ,   SI_STKDataIndCallback},
    {SI_STK_OPENCHANNEL         ,   VOS_NULL_PTR                ,   VOS_NULL_PTR},
    {SI_STK_CLOSECHANNEL        ,   VOS_NULL_PTR                ,   VOS_NULL_PTR},
    {SI_STK_RECEIVEDATA         ,   VOS_NULL_PTR                ,   VOS_NULL_PTR},
    {SI_STK_SENDDATA            ,   VOS_NULL_PTR                ,   VOS_NULL_PTR},
    {SI_STK_GETCHANNELSTATUS    ,   VOS_NULL_PTR                ,   VOS_NULL_PTR},
    {SI_STK_SERVICESEARCH       ,   VOS_NULL_PTR                ,   VOS_NULL_PTR},
    {SI_STK_GETSERVICEINFO      ,   VOS_NULL_PTR                ,   VOS_NULL_PTR},
    {SI_STK_DECLARESERVICE      ,   VOS_NULL_PTR                ,   VOS_NULL_PTR},
    {SI_STK_SETFRAMES           ,   SI_STKSetFrame_Decode       ,   SI_STKDataIndCallback},
    {SI_STK_GETFRAMESSTATUS     ,   SI_STKNoNeedDecode          ,   SI_STKDataIndCallback}
};

/*****************************************************************************
函 数 名  :SI_STK_CheckSupportAP
功能描述  :判断当前是否支持AP
输入参数  :无
输出参数  :无
返 回 值  :VOS_TRUE/VOS_FALSE
调用函数  : GetProductType
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_BOOL SI_STK_CheckSupportAP(VOS_VOID)
{
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU stAPPConfig;

    if(NV_OK != NV_Read(en_NV_Item_System_APP_Config, &stAPPConfig, sizeof(VOS_UINT16)))
    {
        STK_ERROR_LOG("SI_STK_CheckSupportAP: Read en_NV_Item_System_APP_Config Failed");

        return VOS_FALSE;
    }

    if(SYSTEM_APP_ANDROID == stAPPConfig.usSysAppConfigType)
    {
        STK_NORMAL_LOG("SI_STK_CheckSupportAP: System App is Android");

        return VOS_TRUE;
    }

    STK_NORMAL_LOG("SI_STK_CheckSupportAP: System App is other");

    return VOS_FALSE;
}

/*****************************************************************************
函 数 名  :SI_STK_CheckCardStatus
功能描述  :判断当前是否支持AP
输入参数  :无
输出参数  :无
返 回 值  :VOS_TRUE/VOS_FALSE
调用函数  : GetProductType
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_BOOL SI_STK_CheckCardStatus(VOS_VOID)
{
    if (USIMM_CARD_SERVIC_AVAILABLE == g_stStkCardInfo.enSvcStatus)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
函 数 名  :SI_STK_IsProactiveCmdNeedSnd2Csima
功能描述  :判断当前是否支持C+L共SIM卡特性
输入参数  :无
输出参数  :无
返 回 值  :VOS_TRUE/VOS_FALSE
History     :
1.日    期  : 2013年12月20日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_BOOL SI_STK_IsProactiveCmdNeedSnd2Csima(VOS_VOID)
{
    return (VOS_BOOL)((TAF_NVIM_LC_RAT_COMBINED_CL == g_stLCEnableCfg.enRatCombined) && (VOS_TRUE == g_stLCEnableCfg.ucLCEnableFlg));
}

/*****************************************************************************
函 数 名  :SI_STK_IsCbpMainCtrlProactiveCmd
功能描述  :判断当前是否由CBP主控主动命令
输入参数  :无
输出参数  :无
返 回 值  :VOS_TRUE/VOS_FALSE
History     :
1.日    期  : 2014年01月19日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_BOOL SI_STK_IsCbpMainCtrlProactiveCmd(VOS_VOID)
{
    return (VOS_BOOL)((VOS_TRUE == g_stLCEnableCfg.ucLCEnableFlg) && (USIMM_CARD_NOCARD == g_stStkCardInfo.enCardType));
}

/*****************************************************************************
 Prototype      : SI_STK_GetRecMMCPID
 Description    : STK发送给TAF消息函数
 Input          : pulTAFPid:接收消息的TAF的PID
 Output         : 无
 Return Value   : VOS_ERR/VOS_OK

 History        : ---
  1.Date        : 2013-05-24
    Author      : zhuli
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SI_STK_GetRecMMCPID(VOS_UINT32 *pulTAFPid)
{
    if (VOS_TRUE == USIMM_IsSvlte())
    {
        if (MODEM_ID_0 == g_enSTKCurCSModem)
        {
            *pulTAFPid = I0_WUEPS_PID_MMC;

            return VOS_OK;
        }
        else if (MODEM_ID_1 == g_enSTKCurCSModem)
        {
            *pulTAFPid = I1_WUEPS_PID_MMC;

            return VOS_OK;
        }
        else
        {
            return VOS_ERR;
        }
    }

    *pulTAFPid = WUEPS_PID_MMC;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :SI_STK_EventDownComptiable
功能描述  :EventDown兼容性处理函数
输入参数  :
输出参数  :无
返 回 值  :无
History     :
1.日    期  : 2015年10月28日
  作    者  : zhuli
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_EventDownComptiable(VOS_VOID)
{
    if (SI_STK_SETUPEVENTLIST != gstUsatCmdDecode.SatType)
    {
        return;
    }

    if ( (VOS_TRUE  == g_stSTKEventState.OP_LociStatus)
        &&(VOS_TRUE == g_stStkSysInfo.ulEventMsgFlag)
        &&(VOS_TRUE == g_stSTKFeatureCnf.unCfg.stFeatureCfg.ulLociEventCmp))
    {
        g_stStkSysInfo.ulEventMsgFlag = VOS_FALSE;

        SI_STK_LocationStatusEventDownload();
    }

    return;
}

/* Add by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, begin */
/*****************************************************************************
函 数 名  :SI_STK_TACnfProc
功能描述  :TA回复命令的处理函数
输入参数  :
输出参数  :无
返 回 值  :无
History     :
1.日    期  : 2012年03月28日
  作    者  : w00184875
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_TACnfProc(PS_SI_MSG_STRU *pstMsg)
{
    STK_AS_TA_INFO_CNF_STRU         *pstTAMsg;

    VOS_UINT8  aucResp[16]  = {0x81, 0x03, 0x01, 0x26, 0x05, 0x02, 0x02, 0x82,
                               0x81, 0x83, 0x01, 0x00, 0xAE, 0x02, 0x00, 0x00};
    VOS_UINT32 ulDataLen    = STK_TERMINAL_RSP_LEN;

    aucResp[2]  = gstUsatCmdDecode.CmdDetail.ucCommandNum;
    aucResp[3]  = gstUsatCmdDecode.CmdDetail.ucCommandType;
    aucResp[4]  = gstUsatCmdDecode.CmdDetail.ucCommandQua;

    pstTAMsg = (STK_AS_TA_INFO_CNF_STRU*)pstMsg;

    if (SI_STK_WAITING_CNF  == g_enTACmdStatus)
    {
        /*lint -e534*/
        (VOS_VOID)STK_GETTA_TIMER_STOP;
        /*lint +e534*/

        g_enTACmdStatus = SI_STK_NORMAL_CNF;
    }
    else
    {
        STK_WARNING_LOG("SI_STK_GasMsgProc: Recieve TA Message is not need.\r\n");
        return;
    }

    /*判断命令执行结果*/
    if(TERMINAL_CURRENTLY_UNABLE_TO_PROCESS_COMMAND == pstTAMsg->ulResult)
    {
        STK_ERROR_LOG("SI_STK_GasMsgProc: TA TERMINAL_CURRENTLY_UNABLE_TO_PROCESS_COMMAND");

        aucResp[11] = TERMINAL_CURRENTLY_UNABLE_TO_PROCESS_COMMAND;
        aucResp[12] = NO_SPECIFIC_CAUSE_CAN_BE_GIVEN_BY_TERMINAL;

        ulDataLen = STK_TERMINAL_RSP_LEN + 1;
    }
    else
    {
        aucResp[11] = (VOS_UINT8)pstTAMsg->ulResult;
        aucResp[14] = pstTAMsg->ucMEStatus;
        aucResp[15] = ((pstTAMsg->ucTAValue > SI_STK_MAX_TA_VALUE )? SI_STK_MAX_TA_VALUE : pstTAMsg->ucTAValue);

        ulDataLen += 4; /*TAG+LEN+MESTATUS+TAVALUE*/
    }

    if (VOS_OK != SI_STK_SendTerminalResponseReqMsg((VOS_UINT8)ulDataLen, aucResp, USIMM_TR_TYPE_BALONG))
    {
        STK_ERROR_LOG("SI_STK_GasMsgProc: SI_STK_SendTerminalResponse Error.");
    }

    return;
}
/* Add by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, end */

/*****************************************************************************
函 数 名  :SI_STK_MoreTimeProc
功能描述  :Refresh命令的处理函数
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
VOS_UINT32 SI_STK_MoreTimeProc(SI_STK_DATA_INFO_STRU *pCmdData)
{
    return SI_STK_OK;
}

/*****************************************************************************
函 数 名  : SI_STK_SteeringRoamingInd
功能描述  : Refresh命令指示Steering of Roaming时上报NAS
输入参数  : pMsg
输出参数  : 无
返 回 值  : SI_STK_OK 成功
            SI_STK_DATA_ERROR 失败
调用函数  :
被调函数  :
History     :
1.日    期  : 2010年02月03日
  作    者  : m00128685
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STK_SteeringRoamingInd(VOS_UINT32 ulLen, VOS_UINT8 *pucOplmnList)
{
    STK_NAS_STEERING_OF_ROAMING_STRU    *pstMsg;
    VOS_UINT32                          ulRecPID;

    if ((VOS_NULL_PTR == pucOplmnList)||(0 == ulLen))
    {
        return SI_STK_DATA_ERROR;
    }

    if (VOS_OK != SI_STK_GetRecMMCPID(&ulRecPID))
    {
        STK_ERROR_LOG("SI_STK_SteeringRoamingReq: NO CS Modem");

        return SI_STK_NOTSUPPORT;
    }

    pstMsg = (STK_NAS_STEERING_OF_ROAMING_STRU *)VOS_AllocMsg(MAPS_STK_PID,
                 (sizeof(STK_NAS_STEERING_OF_ROAMING_STRU) + ulLen) - VOS_MSG_HEAD_LENGTH );

    if(VOS_NULL_PTR == pstMsg)
    {
        STK_ERROR_LOG("SI_STK_SteeringRoamingReq: VOS_AllocMsg Return Error");

        return SI_STK_DATA_ERROR;
    }

    pstMsg->ulReceiverPid       = ulRecPID;
    pstMsg->ulMsgName           = STK_NAS_STEERING_OF_ROAMING_IND;
    pstMsg->usOplmnListLen      = (VOS_UINT16)ulLen;

    /*lint -e534*/
    VOS_MemCpy(pstMsg->aucOplmnList, pucOplmnList, ulLen);
    /*lint +e534*/

    if(VOS_OK != VOS_SendMsg(MAPS_STK_PID, pstMsg))
    {
        STK_ERROR_LOG("SI_STK_SteeringRoamingReq: VOS_SendMsg Return Error");

        return SI_STK_DATA_ERROR;
    }

    return SI_STK_OK;
}

/*****************************************************************************
函 数 名  :SI_STK_RefreshCallInServiceProc
功能描述  :Refresh命令当UE在呼叫状态的处理函数
输入参数  :pCmdData:主动命令内容
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2012年09月13日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STK_RefreshCallInServiceProc(SI_STK_DATA_INFO_STRU *pCmdData)
{
    /* 回复原因值ME currently busy on call */
    VOS_UINT8  aucTemp[] = {0x81,0x03,0x00,0x00,0x00,0x02,0x02,0x82,0x81,0x83,0x02,0x20,0x02};

    aucTemp[2]  = pCmdData->CmdDetail.ucCommandNum;
    aucTemp[3]  = pCmdData->CmdDetail.ucCommandType;
    aucTemp[4]  = pCmdData->CmdDetail.ucCommandQua;

    if (VOS_OK != SI_STK_SendTerminalResponseReqMsg(sizeof(aucTemp), aucTemp, USIMM_TR_TYPE_BALONG))
    {
        STK_WARNING_LOG("SI_STK_RefreshCallIsServiceProc: SI_STK_SendTerminalResponse Return Error");

        return SI_STK_NOTSUPPORT;
    }

    return SI_STK_NORP;
}


/*****************************************************************************
函 数 名  :SI_STK_RefreshProc
功能描述  :Refresh命令的处理函数
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
VOS_UINT32 SI_STK_RefreshProc(SI_STK_DATA_INFO_STRU *pCmdData)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulCallState;
    USIMM_RESET_INFO_STRU               stRstInfo;
    USIMM_FEATURE_CFG_STRU              stUsimmFeatureCfg;

    if (VOS_TRUE == STK_IsCPBCsimRefreshCmd(pCmdData))
    {
        return SI_STK_OK_WAITRP;
    }

    if (VOS_OK != NV_Read(en_NV_Item_Usim_Support_Feature_Config,
                         (VOS_VOID*)&stUsimmFeatureCfg, sizeof(stUsimmFeatureCfg)))
    {
        (VOS_VOID)VOS_MemSet(stUsimmFeatureCfg.unCfg.aulValue,
                                VOS_FALSE, 
                                sizeof(stUsimmFeatureCfg.unCfg.aulValue));
    }

    ulCallState = STK_IsCallInService();

    if(VOS_FALSE == stUsimmFeatureCfg.unCfg.stFeatureCfg.ulAtt_flg)
    {
        /* 当前有呼叫，不处理REFRESH命令 */
        if (VOS_TRUE == ulCallState)
        {
            return SI_STK_RefreshCallInServiceProc(pCmdData);
        }
    }
    else
    {
        if ((VOS_TRUE       == ulCallState)
            &&(USIMM_RESET  == pCmdData->CmdDetail.ucCommandQua))
        {
            /* 当前有呼叫，不处理REFRESH命令 但是需要缓冲命令的标记，在呼叫结束的时候处理*/
            g_bSTKAttResetFlag = VOS_TRUE;

            return SI_STK_RefreshCallInServiceProc(pCmdData);
        }
    }

    /*lint -e534*/
    (VOS_VOID)VOS_MemSet(&stRstInfo, 0, sizeof(USIMM_RESET_INFO_STRU));
    /*lint +e534*/

    /* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, begin */
    switch(pCmdData->CmdDetail.ucCommandQua)
    {
        case USIMM_INITIAL_FULL_FILE_CHANGE_NOTIFY:
        case USIMM_FILE_CHANGE_NOTIFY:
        case USIMM_INITIAL_FILE_CHANGE_NOTIFY:
        case USIMM_RESET:
        case USIMM_INITIALIZATION:
        case USIMM_SESSION_RESET_3G_ONLY:
        case USIMM_APPLICATION_RESET_3G_ONLY:

            if (VOS_TRUE == pCmdData->CmdStru.Refresh.OP_FileList)
            {
                stRstInfo.usFileListLen = pCmdData->CmdStru.Refresh.FileList.ucLen;

                /*lint -e534*/
                (VOS_VOID)VOS_MemCpy(stRstInfo.aucFileList, pCmdData->CmdStru.Refresh.FileList.pucFiles, stRstInfo.usFileListLen);
                /*lint +e534*/
            }

            if (VOS_TRUE == pCmdData->CmdStru.Refresh.OP_AID)
            {
                stRstInfo.usAidLen = (VOS_UINT16)pCmdData->CmdStru.Refresh.AID.ulLen;

                /*lint -e534*/
                (VOS_VOID)VOS_MemCpy(stRstInfo.aucAid, pCmdData->CmdStru.Refresh.AID.pucAID, USIMM_AID_LEN_MAX);
                /*lint +e534*/
            }

            ulResult = SI_STK_SendResetReqMsg((USIMM_STK_COMMAND_DETAILS_STRU *)&pCmdData->CmdDetail,
                                               &stRstInfo);
            break;

        case USIMM_STEERING_OF_ROAMING:
            if (VOS_TRUE == pCmdData->CmdStru.Refresh.OP_OplmnList)
            {
                ulResult = SI_STK_SteeringRoamingInd(pCmdData->CmdStru.Refresh.PlmnwactList.ulLen,
                                                     pCmdData->CmdStru.Refresh.PlmnwactList.pucOplmnList);
            }
            else
            {
                ulResult = SI_STK_DATA_ERROR;
            }


            if (SI_STK_OK == ulResult)
            {
                SI_STKSimpleResponse(&gstUsatCmdDecode.CmdDetail, COMMAND_PERFORMED_SUCCESSFULLY);
            }

            break;

        default:
            ulResult = SI_STK_DATA_ERROR;
            break;
    }
    /* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, end */

    /* 为了规避重启过程的主动命令，此处需要清空当前保存的变量内容，不管是否成功都需要释放内存 */
    SI_STKCommDataFree(pCmdData->SatType, (SI_SAT_COMMDATA_STRU*)(&pCmdData->CmdStru));

    if (VOS_OK != ulResult)
    {
        ulResult = SI_STK_NOTSUPPORT;
    }
    else
    {
        ulResult = SI_STK_NORP;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :SI_STK_PollIntervalProc
功能描述  :主动命令PollInterval的处理函数
输入参数  :
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
2.日    期  : 2011年8月30日
  作    者  : j00168360
  修改内容  : [DTS2011082604548]，TIM SIM卡不能显示STK菜单
*****************************************************************************/
VOS_UINT32 SI_STK_PollIntervalProc(SI_STK_DATA_INFO_STRU *pCmdData)
{
    SI_STK_POLLINTERVAL_STRU *pstPollInter;
    VOS_UINT8                aucTpr[] = {0x81,0x03,0x01,0x03,0x00,0x02,0x02,0x82,0x81,0x83,0x01,0x00,0x84,0x02,0x00,0x00};
    VOS_UINT32               ulTimerLen;

    pstPollInter = (SI_STK_POLLINTERVAL_STRU *)&pCmdData->CmdStru;

    switch(pstPollInter->Duration.ucUnit)
    {
        case STK_DURATION_MIN:
            ulTimerLen = 60 * pstPollInter->Duration.ucInternal * 1000;
            break;
        case STK_DURATION_SEC:
            ulTimerLen = pstPollInter->Duration.ucInternal * 1000;
            /*根据实测情况，修正Polling值偏差*/
            ulTimerLen = (0 == ulTimerLen) ? 0:(ulTimerLen - 22);
            break;
        case STK_DURATION_TENTH_SEC:
            ulTimerLen = pstPollInter->Duration.ucInternal * 100;
            break;
        default:
            return COMMAND_DATA_NOT_UNDERSTOOD_BY_TERMINAL;
    }

    if(ulTimerLen != 0)
    {
        SI_STK_SendChangePollTimerLenMsg(ulTimerLen);

        /* 对CmdDetail字段重新赋值，以免主动命令上报的参数与aucTpr中默认值不一致导致的兼容性问题 */
        aucTpr[2] = pCmdData->CmdDetail.ucCommandNum;
        aucTpr[3] = pCmdData->CmdDetail.ucCommandType;
        aucTpr[4] = pCmdData->CmdDetail.ucCommandQua;

        aucTpr[14] = pstPollInter->Duration.ucUnit;
        aucTpr[15] = pstPollInter->Duration.ucInternal;

        if (VOS_OK == SI_STK_SendTerminalResponseReqMsg(sizeof(aucTpr), aucTpr, USIMM_TR_TYPE_BALONG))
        {
            return SI_STK_NORP;
        }
    }

    return COMMAND_DATA_NOT_UNDERSTOOD_BY_TERMINAL;
}

/*****************************************************************************
函 数 名  :SI_STK_PollingOFFProc
功能描述  :主动命令PollingOFF的处理函数
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
VOS_UINT32 SI_STK_PollingOFFProc(SI_STK_DATA_INFO_STRU *pCmdData)
{
    SI_STK_SendChangePollTimerLenMsg(SI_PIH_POLL_TIMER_LEN);

    return SI_STK_OK;
}

/*****************************************************************************
函 数 名  : SI_STK_SendSSProc
功能描述  : 发送SS字符串的处理
输入参数  : pCmdData:解码结果
输出参数  : 无
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STK_SendSSProc(SI_STK_DATA_INFO_STRU *pCmdData)
{
    if (VOS_TRUE == SI_STK_CheckSupportAP())
    {
        /*lint -e534*/
        SI_STKDataIndCallback(pCmdData);
        /*lint +e534*/
    }

    return SI_STK_SendSSSpecialProc(pCmdData);
}

/*****************************************************************************
函 数 名  : SI_STK_SendDTMFProc
功能描述  : 发送DTMF字符串的处理
输入参数  : pCmdData:解码结果
输出参数  : 无
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STK_SendDTMFProc(SI_STK_DATA_INFO_STRU *pCmdData)
{
    if (VOS_TRUE == SI_STK_IsProactiveCmdNeedSnd2Csima())
    {
        SI_STK_SndProactiveCmd2CBP(pCmdData->SatCmd.SatDataLen, pCmdData->SatCmd.SatCmdData);

        return SI_STK_OK_WAITRP;
    }

    if (VOS_TRUE == SI_STK_CheckSupportAP())
    {
        /*lint -e534*/
        SI_STKDataIndCallback(pCmdData);
        /*lint +e534*/
    }

    return SI_STK_SendDTMFSpecialProc(pCmdData);
}

/*****************************************************************************
函 数 名  : SI_STK_SendUSSDProc
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
VOS_UINT32 SI_STK_SendUSSDProc(SI_STK_DATA_INFO_STRU *pCmdData)
{
    if (VOS_TRUE == SI_STK_CheckSupportAP())
    {
        /*lint -e534*/
        SI_STKDataIndCallback(pCmdData);
        /*lint +e534*/
    }

    return SI_STK_SendUSSDSpecialProc(pCmdData);
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
  作    者  : H59254
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STK_SendSMSProc(SI_STK_DATA_INFO_STRU *pCmdData)
{
    if (VOS_TRUE == SI_STK_IsProactiveCmdNeedSnd2Csima())
    {
        SI_STK_SndProactiveCmd2CBP(pCmdData->SatCmd.SatDataLen, pCmdData->SatCmd.SatCmdData);

        return SI_STK_OK_WAITRP;
    }

    if (VOS_TRUE == SI_STK_CheckSupportAP())
    {
        /*lint -e534*/
        SI_STKDataIndCallback(pCmdData);
        /*lint +e534*/
    }

    return SI_STK_SendSMSSpecialProc(pCmdData);
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
VOS_UINT32 SI_STK_DisplayTextProc(SI_STK_DATA_INFO_STRU *pCmdData)
{
    if(pCmdData->CmdStru.DisplayText.TextStr.ucLen == 0)
    {
        STK_ERROR_LOG("SI_STK_DisplayTextProc: The Text is NULL");

        return SI_STK_DATA_ERROR;
    }

    return SI_STKDataIndCallback(pCmdData);
}

/*****************************************************************************
函 数 名  :SI_STK_ProvideLocIProc
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
2.日    期  : 2011年8月30日
  作    者  : j00168360
  修改内容  : [DTS2011082604548]，TIM SIM卡不能显示STK菜单
*****************************************************************************/
VOS_UINT32 SI_STK_SetUpMenuProc(SI_STK_DATA_INFO_STRU *pCmdData)
{
    VOS_UINT8  aucRsp[] = {0x81,0x03,0x01,0x25,0x00,0x02,0x02,0x82,0x81,0x83,0x01,0x00};

    if (VOS_FALSE == SI_STK_CheckSupportAP())
    {
        if(SI_STK_MENU_EXIST == gstSetUpMenuData.ucUsatTag)
        {
            SI_STKCommDataFree(SI_STK_SETUPMENU,(SI_SAT_COMMDATA_STRU*)&gstSetUpMenuData.stSetUpMenu);
        }

        /*lint -e534*/
        VOS_MemCpy(&gstSetUpMenuData.stSetUpMenu, &pCmdData->CmdStru, sizeof(gstSetUpMenuData.stSetUpMenu));

        VOS_MemCpy(&gstSetUpMenuData.CmdDetail, &pCmdData->CmdDetail, sizeof(gstSetUpMenuData.CmdDetail));

        VOS_MemCpy(&gstSetUpMenuData.CmdDevice, &pCmdData->CmdDevice, sizeof(gstSetUpMenuData.CmdDevice));

        VOS_MemSet(&pCmdData->CmdStru, 0, sizeof(gstSetUpMenuData.stSetUpMenu));
        /*lint +e534*/

        gstSetUpMenuData.ucUsatTag = SI_STK_MENU_EXIST;

        /* 对CmdDetail字段重新赋值，以免主动命令上报的参数与aucRsp中默认值不一致导致的兼容性问题 */
        aucRsp[2] = pCmdData->CmdDetail.ucCommandNum;
        aucRsp[3] = pCmdData->CmdDetail.ucCommandType;
        aucRsp[4] = pCmdData->CmdDetail.ucCommandQua;

        /*lint -e534*/
        (VOS_VOID)SI_STK_SendTerminalResponseReqMsg(sizeof(aucRsp), aucRsp, USIMM_TR_TYPE_BALONG);

        (VOS_VOID)SI_STKDataIndCallback(pCmdData);
        /*lint +e534*/

        return SI_STK_NORP;
    }
    else
    {
        /* 需要由AP来回复TERMINAL RESPONSE */
        /*lint -e534*/
        SI_STKDataIndCallback(pCmdData);
        /*lint +e534*/

        return SI_STK_OK_WAITRP;
    }
}

/*****************************************************************************
函 数 名  :SI_STK_SetUpIdleTextProc
功能描述  :SetUpIdleModeText的处理函数
输入参数  :
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2010年06月08日
  作    者  : m00128685
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STK_SetUpIdleTextProc(SI_STK_DATA_INFO_STRU *pCmdData)
{

    SI_STK_SET_UP_IDLE_MODE_TEXT_STRU *pstIdleTextMag;

    pstIdleTextMag = (SI_STK_SET_UP_IDLE_MODE_TEXT_STRU *)&pCmdData->CmdStru;

    /* 按协议规定Icon Qualifier为1时，Text String必须存在*/
    if ((1 == pstIdleTextMag->OP_IconId)&&(1 == pstIdleTextMag->IconId.ucQualifier)
       &&(0 == pstIdleTextMag->TextStr.ucLen))
    {
        return SI_STK_DATA_ERROR;
    }

    return SI_STKDataIndCallback(pCmdData);
}

/*****************************************************************************
函 数 名  :SI_STKCommDecode
功能描述  :STK命令的通用解码处理函数
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
VOS_UINT32 SI_STKCommDecode(VOS_UINT8* pucCmdData, VOS_UINT32 ulCmdType,SI_SAT_COMMDATA_STRU *pstResult)
{
    return (VOS_ERR == SI_STKCommDecodeData(pucCmdData,ulCmdType,pstResult))?SI_STK_DATA_ERROR:SI_STK_OK_WAITRP;/* [false alarm]: 屏蔽Fortify 错误 */
}

/*****************************************************************************
函 数 名  :SI_STKNoNeedDecode
功能描述  :主动命令无需解码的处理函数
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
VOS_UINT32 SI_STKNoNeedDecode(VOS_UINT8* pucCmdData, VOS_UINT32 ulCmdType,SI_SAT_COMMDATA_STRU *pstResult)
{
    return SI_STK_OK_WAITRP;
}

/*****************************************************************************
函 数 名  :SI_STK_LaunchBrowser_Decode
功能描述  :主主动命令LaunchBrowser的解码函数
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
VOS_UINT32 SI_STK_LaunchBrowser_Decode(VOS_UINT8* pucCmdData, VOS_UINT32 ulCmdType,SI_SAT_COMMDATA_STRU *pstResult)
{
    VOS_UINT32                  ulOffset;
    VOS_UINT32                  i;
    SI_STK_LAUNCH_BROWSER_STRU* pstLaunBrowser;

    pstLaunBrowser = (SI_STK_LAUNCH_BROWSER_STRU *)pstResult;

    if(VOS_ERR == SI_STKCommDecodeData(pucCmdData,ulCmdType,pstResult))
    {
        return SI_STK_DATA_ERROR;
    }

    for( i = 0; i < ITEMNUMMAX; i++)
    {
        ulOffset = SI_STKFindTag(PROVISIONING_REFFILE_TAG, &pucCmdData[1], pucCmdData[0], i+1);

        if(ulOffset == SI_TAGNOTFOUND)
        {
            break;
        }
        else
        {
            /*lint -e534*/
            SI_STKDecodeTagData(&pucCmdData[ulOffset+1], PROVISIONING_REFFILE_TAG, &(pstLaunBrowser->PFRef[i]));
            /*lint +e534*/
        }
    }

    if(i != 0)
    {
        pstLaunBrowser->OP_PFRef = 1;
    }

    pstLaunBrowser->PfNumber = i;

    return SI_STK_OK_WAITRP;
}

/*****************************************************************************
函 数 名  :SI_STK_SelectItem_Decode
功能描述  :主动命令SelectItem的解码函数
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
VOS_UINT32 SI_STK_SelectItem_Decode(VOS_UINT8* pucCmdData, VOS_UINT32 ulCmdType,SI_SAT_COMMDATA_STRU *pstResult)
{
    VOS_UINT32              ulOffset;
    VOS_UINT32              i;
    SI_STK_SELECT_ITEM_STRU*pstSelITem;

    pstSelITem = (SI_STK_SELECT_ITEM_STRU *)pstResult;

    if(VOS_ERR == SI_STKCommDecodeData(pucCmdData,ulCmdType,pstResult))
    {
        return SI_STK_DATA_ERROR;
    }

    for(i=0; i<ITEMNUMMAX; i++)
    {
        ulOffset = SI_STKFindTag(ITEM_TAG, &pucCmdData[1], pucCmdData[0], i+1);

        if(ulOffset == SI_TAGNOTFOUND)
        {
            break;
        }
        else
        {
            /*lint -e534*/
            SI_STKDecodeTagData(&pucCmdData[ulOffset+1], ITEM_TAG, &(pstSelITem->Item[i]));
            /*lint +e534*/
        }
    }

    if(i != 0)
    {
        pstSelITem->OP_ItemId = 1;
    }
    else
    {
        return SI_STK_DATA_ERROR;
    }

    pstSelITem->ItemNum = i;

    return SI_STK_OK_WAITRP;
}

/*****************************************************************************
函 数 名  :SI_STK_SetUpMenu_Decode
功能描述  :主动命令SetUpMenu的解码函数
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
VOS_UINT32 SI_STK_SetUpMenu_Decode(VOS_UINT8* pucCmdData, VOS_UINT32 ulCmdType,SI_SAT_COMMDATA_STRU*pstResult)
{
    VOS_UINT32              ulOffset;
    VOS_UINT32              i;
    SI_STK_SET_UP_MENU_STRU*pstSetUpMenu;

    if (VOS_TRUE == SI_STK_CheckSupportAP())    /*对接AP不需要解码*/
    {
        return SI_STK_OK_WAITRP;
    }

    pstSetUpMenu = (SI_STK_SET_UP_MENU_STRU*)pstResult;

    if(VOS_ERR == SI_STKCommDecodeData(pucCmdData,ulCmdType,pstResult))
    {
        gstSetUpMenuData.ucUsatTag = SI_STK_MENU_NOTEXIST;

        STK_ERROR_LOG("SI_STK_SetUpMenu_Decode:The SetUp Menu Command Data is Error");

        return SI_STK_DATA_ERROR;
    }

    for(i=0; i<ITEMNUMMAX; i++)
    {
        ulOffset = SI_STKFindTag(ITEM_TAG, &pucCmdData[1], pucCmdData[0], i+1);

        if(ulOffset == SI_TAGNOTFOUND)
        {
            break;
        }
        else
        {
            /*lint -e534*/
            SI_STKDecodeTagData(&pucCmdData[ulOffset+1], ITEM_TAG, &(pstSetUpMenu->Item[i]));
            /*lint +e534*/
        }
    }

    if(i != 0)
    {
        pstSetUpMenu->OP_Item = 1;
    }
    else
    {
        return SI_STK_DATA_ERROR;
    }

    pstSetUpMenu->ulItemNum = i;

    return SI_STK_OK_WAITRP;
}

/*****************************************************************************
函 数 名  :SI_STKSetUpCall_Decode
功能描述  :主动命令SetUpCall的解码函数
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
VOS_UINT32 SI_STKSetUpCall_Decode(VOS_UINT8* pucCmdData, VOS_UINT32 ulCmdType,SI_SAT_COMMDATA_STRU*pstResult)
{
    VOS_UINT32              ulOffset;
    SI_STK_SET_UP_CALL_STRU *pstSetCall;

    pstSetCall = (SI_STK_SET_UP_CALL_STRU *)pstResult;

    if(VOS_ERR == SI_STKCommDecodeData(pucCmdData,ulCmdType,pstResult))
    {
        return SI_STK_DATA_ERROR;
    }

    ulOffset = SI_STKFindTag(ALPHA_IDENTIFIER_TAG, &pucCmdData[1], pucCmdData[0], 2);

    if(ulOffset != SI_TAGNOTFOUND)
    {
        /*lint -e534*/
        SI_STKDecodeTagData(&pucCmdData[ulOffset+1], ALPHA_IDENTIFIER_TAG, &(pstSetCall->AlphaId2));
        /*lint +e534*/

        pstSetCall->OP_AlphaId2 = 1;
    }

    ulOffset = SI_STKFindTag(ICON_IDENTIFIER_TAG, &pucCmdData[1], pucCmdData[0], 2);

    if(ulOffset != SI_TAGNOTFOUND)
    {
        /*lint -e534*/
        SI_STKDecodeTagData(&pucCmdData[ulOffset+1], ICON_IDENTIFIER_TAG, &(pstSetCall->IconId2));
        /*lint +e534*/

        pstSetCall->OP_IconId2= 1;
    }

    ulOffset = SI_STKFindTag(TEXT_ATTRIBUTE_TAG, &pucCmdData[1], pucCmdData[0], 2);

    if(ulOffset != SI_TAGNOTFOUND)
    {
        /*lint -e534*/
        SI_STKDecodeTagData(&pucCmdData[ulOffset+1], TEXT_ATTRIBUTE_TAG, &(pstSetCall->TextAttr2));
        /*lint +e534*/

        pstSetCall->OP_TextAttr2= 1;
    }

    return SI_STK_OK_WAITRP;
}

/*****************************************************************************
函 数 名  :SI_STKOpenChannel_Decode
功能描述  :主动命令OpenChannel的解码函数
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
VOS_UINT32 SI_STKOpenChannel_Decode(VOS_UINT8* pucCmdData, VOS_UINT32 ulCmdType,SI_SAT_COMMDATA_STRU*pstResult)
{
    VOS_UINT32              ulOffset;
    SI_STK_OPEN_CHANNEL_STRU*pstOpenCH;

    pstOpenCH = (SI_STK_OPEN_CHANNEL_STRU*)pstResult;

    if(VOS_OK == SI_STKCommDecodeData(pucCmdData,ulCmdType,pstResult))
    {
        return SI_STK_DATA_ERROR;
    }

    ulOffset = SI_STKFindTag(DURATION_TAG, &pucCmdData[1], pucCmdData[0], 2);

    if(ulOffset != SI_TAGNOTFOUND)
    {
        /*lint -e534*/
        SI_STKDecodeTagData(&pucCmdData[ulOffset+1], DURATION_TAG, &(pstOpenCH->Duration2));
        /*lint +e534*/

        pstOpenCH->OP_Duration2 = 1;
    }

    ulOffset = SI_STKFindTag(TEXT_STRING_TAG, &pucCmdData[1], pucCmdData[0], 2);

    if(ulOffset != SI_TAGNOTFOUND)
    {
        /*lint -e534*/
        SI_STKDecodeTagData(&pucCmdData[ulOffset+1], TEXT_STRING_TAG, &(pstOpenCH->TextStr2));
        /*lint +e534*/

        pstOpenCH->OP_Textstr2 = 1;
    }

    ulOffset = SI_STKFindTag(OTHER_ADDR_TAG, &pucCmdData[1], pucCmdData[0], 2);

    if(ulOffset != SI_TAGNOTFOUND)
    {
        /*lint -e534*/
        SI_STKDecodeTagData(&pucCmdData[ulOffset+1], OTHER_ADDR_TAG, &(pstOpenCH->OtherAddr2));
        /*lint +e534*/

        pstOpenCH->OP_OtherAddr2 = 1;
    }

    return SI_STK_OK_WAITRP;
}

/*****************************************************************************
函 数 名  :SI_STKSetFrame_Decode
功能描述  :主动命令SetFrame的解码函数
输入参数  :
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年12月23日
  作    者  : m00128685
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STKSetFrame_Decode(VOS_UINT8* pucCmdData, VOS_UINT32 ulCmdType,SI_SAT_COMMDATA_STRU*pstResult)
{
    VOS_UINT32              ulOffset;
    SI_STK_SET_FRAMES_STRU  *pstSetFrame;

    pstSetFrame = (SI_STK_SET_FRAMES_STRU*)pstResult;

    if(VOS_ERR == SI_STKCommDecodeData(pucCmdData,ulCmdType,pstResult))
    {
        return SI_STK_DATA_ERROR;
    }

    ulOffset = SI_STKFindTag(FRAME_IDENTIFIER_TAG, &pucCmdData[1], pucCmdData[0], 2);

    if(ulOffset != SI_TAGNOTFOUND)
    {
        /*lint -e534*/
        SI_STKDecodeTagData(&pucCmdData[ulOffset+1], FRAME_IDENTIFIER_TAG, &(pstSetFrame->FrameId2));
        /*lint +e534*/

        pstSetFrame->OP_FrameId2 = 1;
    }

    return SI_STK_OK_WAITRP;
}
/*****************************************************************************
函 数 名  : SI_STKHandleLocate
功能描述  : 根据主动命令的类型定位其在主动命令列表的中的位置
输入参数  : 无
输出参数  : 无
返 回 值  : SI_UINT32 函数执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STKHandleLocate(VOS_UINT32 ulTag, VOS_UINT32*pNum)
{
    VOS_UINT32 i;
    VOS_UINT32 ulResult;

    for(i=0; i<STK_ARRAYSIZE(gSTKCmdHandleList); i++)
    {
        if(ulTag == gSTKCmdHandleList[i].ulCmdType)
        {
            *pNum = i;

            break;
        }
    }

    if(i >= STK_ARRAYSIZE(gSTKCmdHandleList))
    {
        ulResult = SI_STK_TYPE_ERROR;
    }
    else if( (VOS_NULL_PTR == gSTKCmdHandleList[i].pfDecodeFun)
        || (VOS_NULL_PTR == gSTKCmdHandleList[i].pfProcFun) )
    {
        ulResult = SI_STK_NOTSUPPORT;
    }
    else
    {
        ulResult = SI_STK_OK;
    }

    return ulResult;
}


/*****************************************************************************
函 数 名  :SI_STKCommandIndHandle
功能描述  :主动命令处理的入口函数
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
VOS_VOID SI_STKCommandIndHandle(USIMM_STKDATA_IND_STRU *pMsg )
{
    VOS_UINT32 ulResult;
    VOS_UINT32 i;
    VOS_UINT32 ulOffset;
    VOS_UINT32 ulRet = VOS_OK;

    ulOffset = SI_STKFindTag(SI_STK_PROCMD, pMsg->aucContent,
                                sizeof(pMsg->aucContent),1);/*确定主动命令的长度字节*/

    if(ulOffset == SI_TAGNOTFOUND)  /*当前数据内容不能理解*/
    {
        STK_ERROR_LOG("SI_STKDecodeSATData: Could Not Found the D0 Tag");

        gstUsatCmdDecode.SatType    = pMsg->ucCmdType;

        SI_STKSimpleResponse(&gstUsatCmdDecode.CmdDetail, COMMAND_DATA_NOT_UNDERSTOOD_BY_TERMINAL);

        return ;
    }

    ulResult = SI_STK_CheckProfileCfg(pMsg->ucCmdType,
                                      gastSTKCmdProfileCfg,
                                      STK_ARRAYSIZE(gastSTKCmdProfileCfg));


    if(ulResult == VOS_FALSE)
    {
        STK_ERROR_LOG("SI_STKDecodeSATData: The Terminal Profile Config is not Support this Command");

        gstUsatCmdDecode.SatType    = pMsg->ucCmdType;

        gstUsatCmdDecode.CmdDetail.ucCommandNum = pMsg->aucContent[ulOffset+3]; /*保存公共内容*/
        gstUsatCmdDecode.CmdDetail.ucCommandType= pMsg->aucContent[ulOffset+4];
        gstUsatCmdDecode.CmdDetail.ucCommandQua = pMsg->aucContent[ulOffset+5];

        SI_STKSimpleResponse(&gstUsatCmdDecode.CmdDetail, COMMAND_BEYOND_TERMINALS_CAPABILITIES);

        return ;
    }

    /*lint -e534*/
    VOS_MemSet(&gstUsatCmdDecode, 0x00, sizeof(gstUsatCmdDecode));  /*清空当前的主动命令缓冲*/

    VOS_MemCpy(gstUsatCmdDecode.SatCmd.SatCmdData, pMsg->aucContent, pMsg->usLen);
    /*lint +e534*/

    gstUsatCmdDecode.SatCmd.SatDataLen      = pMsg->usLen;
    gstUsatCmdDecode.SatType                = pMsg->ucCmdType;

    gstUsatCmdDecode.CmdDetail.ucCommandNum = pMsg->aucContent[ulOffset+3]; /*保存公共内容*/
    gstUsatCmdDecode.CmdDetail.ucCommandType= pMsg->aucContent[ulOffset+4];
    gstUsatCmdDecode.CmdDetail.ucCommandQua = pMsg->aucContent[ulOffset+5];
    gstUsatCmdDecode.CmdDevice.ucSDId       = pMsg->aucContent[ulOffset+8];
    gstUsatCmdDecode.CmdDevice.ucDDId       = pMsg->aucContent[ulOffset+9];

    ulResult = SI_STKHandleLocate(pMsg->ucCmdType, &i);             /*确定解码和处理函数的位置*/

    if(ulResult != SI_STK_OK)                                       /*当前的命令不支持或者不能处理*/
    {
        /* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, begin */
        if (VOS_TRUE == SI_STK_CheckSupportAP())
        {
            /*lint -e534*/
            SI_STKDataIndCallback(&gstUsatCmdDecode);
            /*lint +e534*/
        }
        else
        {
            SI_STKSimpleResponse(&gstUsatCmdDecode.CmdDetail, (VOS_UINT8)ulResult);
        }
        /* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, end */
        return ;
    }

    ulResult = gSTKCmdHandleList[i].pfDecodeFun(&pMsg->aucContent[ulOffset],
                                                pMsg->ucCmdType,
                                                (SI_SAT_COMMDATA_STRU*)&gstUsatCmdDecode.CmdStru);

    if(ulResult != SI_STK_OK_WAITRP)                                /*如果错误需要回复命令执行结果*/
    {
        SI_STKSimpleResponse(&gstUsatCmdDecode.CmdDetail, (VOS_UINT8)ulResult);

        return;
    }

    ulResult = gSTKCmdHandleList[i].pfProcFun(&gstUsatCmdDecode);

    if(ulResult == SI_STK_NORP)                                 /*如果当前处理不需要回复*/
    {
        return;
    }
    else if(ulResult == SI_STK_OK_WAITRP)                       /*当前用户需要回复命令结果*/
    {
        /* 双IMSI切换过程中不起定时器 */
        if (SI_STK_IMSICHG_NULL != gstSTKIMSIChgCtrl.enIMSIChgState)
        {
            return;
        }

        /*DTS2015101901781 NV可以关闭定时器*/
        if (VOS_NULL != g_stSTKProfileContent.ucTimer)
        {
            ulRet = STK_PROTECT_TIMER_START(g_stSTKProfileContent.ucTimer);

            if(VOS_ERR == ulRet)/*启动保护定时器*/
            {
                STK_ERROR_LOG("SI_STK_PidMsgProc: Start The Protect Timer Error.");

                SI_STKSimpleResponse(&gstUsatCmdDecode.CmdDetail, SI_STK_NOTSUPPORT);
            }
        }

        if(VOS_FALSE == SI_STK_CheckSupportAP())    /*当不支持AP的时候需要开启改定时器*/
        {
            ulRet = STK_IND_TIMER_START(STK_IND_TIME_LEN);

            if (VOS_ERR == ulRet)
            {
                STK_INFO_LOG("SI_STKCommandIndHandle: Start STK_IND_TIME_LEN Timer Error.");
            }
        }
        /*DTS2015101901781 NV可以关闭定时器*/
    }
    else                                                        /*回复命令结果*/
    {
        SI_STKSimpleResponse(&gstUsatCmdDecode.CmdDetail, (VOS_UINT8)ulResult);

        SI_STK_EventDownComptiable();
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_ProactiveCmdTimeOutProc
功能描述  : 主动命令超时处理函数
输入参数  : 无
输出参数  : 无
返 回 值  : SI_UINT32 函数执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月10日
  作    者  : H59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_ProactiveCmdTimeOutProc(VOS_VOID)
{
    VOS_UINT8   aucTrData[12] = {0x81,0x03,0x00,0x00,0x00,0x02,0x02,0x82,0x81,0x83,0x01,NO_RESPONSE_FROM_USER};
    /*lint -e813*/
    SI_STK_EVENT_INFO_STRU stSTKEvent;

    if(SI_STK_NOCMDDATA == gstUsatCmdDecode.SatType)    /*当前主动命令内容无缓冲*/
    {
        STK_WARNING_LOG("SI_STK_ProactiveCmdTimeOutProc: There is Any STK command");

        return;
    }

    aucTrData[2]  = gstUsatCmdDecode.CmdDetail.ucCommandNum;

    aucTrData[3]  = gstUsatCmdDecode.CmdDetail.ucCommandType;

    aucTrData[4]  = gstUsatCmdDecode.CmdDetail.ucCommandQua;

    if (VOS_OK != SI_STK_SendTerminalResponseReqMsg(sizeof(aucTrData), aucTrData, USIMM_TR_TYPE_BALONG))
    {
        STK_INFO_LOG("SI_STK_ProactiveCmdTimeOutProc: SI_STK_SendTerminalResponse return Err");
    }

    /*如果超时了是否要回调通知应用*/
    stSTKEvent.STKCBEvent = SI_STK_CMD_TIMEOUT_IND_EVENT;   /*确定回调事件类型*/

    stSTKEvent.OpId       = 0;

    stSTKEvent.STKErrorNo = TAF_ERR_NO_ERROR;

    /*lint -e534*/
    VOS_MemCpy(&stSTKEvent.STKCmdStru.CmdDetail, &gstUsatCmdDecode.CmdDetail, sizeof(SI_STK_COMMAND_DETAILS_STRU));
    /*lint +e534*/

    stSTKEvent.STKCmdStru.SatType = gstUsatCmdDecode.SatType;

    SI_STKCallBack_BroadCast(&stSTKEvent);                  /*广播上报超时消息*/
    /*lint +e813*/
    return;
}

/*****************************************************************************
函 数 名  : SI_STK_CmdIndTimeOutProc
功能描述  : 主动命令上报超时处理函数
输入参数  : 无
输出参数  : 无
返 回 值  : SI_UINT32 函数执行结果
 调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月10日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_CmdIndTimeOutProc(VOS_VOID)
{
    /*lint -e813*/
    SI_STK_EVENT_INFO_STRU stSTKEvent;

    if(SI_STK_NOCMDDATA == gstUsatCmdDecode.SatType)    /*当前主动命令内容无缓冲*/
    {
        STK_WARNING_LOG("SI_STK_ProactiveCmdTimeOutProc: There is Any STK command");

        return;
    }

    stSTKEvent.STKCBEvent = SI_STK_CMD_IND_EVENT;   /*确定回调事件类型*/

    stSTKEvent.OpId       = 0;

    stSTKEvent.STKErrorNo = TAF_ERR_NO_ERROR;

    /*lint -e534*/
    VOS_MemCpy(&stSTKEvent.STKCmdStru.CmdDetail, &gstUsatCmdDecode.CmdDetail, sizeof(SI_STK_COMMAND_DETAILS_STRU));
    /*lint +e534*/

    stSTKEvent.STKCmdStru.SatType = gstUsatCmdDecode.SatType;

    SI_STKCallBack_BroadCast(&stSTKEvent);                  /*广播上报超时消息*/

    if(VOS_OK != STK_IND_TIMER_START(STK_IND_TIME_LEN))
    {
        STK_INFO_LOG("SI_STK_CmdIndTimeOutProc: Start STK_IND_TIME_LEN time fail");
    }
    /*lint +e813*/
    return;
}


/*****************************************************************************
函 数 名  : SI_STK_TimerManagement
功能描述  : Timer Management定时器超时处理函数
输入参数  : 无
输出参数  : 无
返 回 值  : SI_UINT32 函数执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月09日
  作    者  : H59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_TimerManagement(VOS_UINT32 ulTimerId)
{
    VOS_UINT8   aucEnData[14] = {0xD7, 0x0C, 0x82, 0x02, 0x82, 0x81, 0xA4, 0x01, 0x00, 0xA5, 0x03, 0x00, 0x00, 0x00};

    aucEnData[8]  = (VOS_UINT8)(ulTimerId);

    aucEnData[11] = STK_HEX2BCD(gstSTKTimer[ulTimerId].ucHour);

    aucEnData[12] = STK_HEX2BCD(gstSTKTimer[ulTimerId].ucMin);

    aucEnData[13] = STK_HEX2BCD(gstSTKTimer[ulTimerId].ucSec);

    SI_STK_SaveEnvelopeCmd(sizeof(aucEnData), aucEnData);

    if(VOS_OK != SI_STK_SendEnvelopeReqMsg(VOS_NULL, USIMM_GUTL_APP,sizeof(aucEnData), aucEnData))
    {
        STK_WARNING_LOG("SI_STK_TimerManagement: Envelop Timer Management Send Fail.");
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_TerminalResponseCnfProc
功能描述  : 用于处理回复的 Terminal Response 消息
输入参数  : pMsg:消息内容
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2014年02月14日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_TerminalResponseCnfProc(PS_SI_MSG_STRU *pMsg)
{
    /* VIA拼片透传Terminal Response的回复处理 */
    if (USIMM_TR_TYPE_CBP == ((USIMM_STKTERMINALRSP_CNF_STRU *)pMsg)->stCmdResult.ulSendPara)
    {
        SI_STK_CbpTrCnfMsgProc(pMsg);
    }
    else
    {
        SI_STK_TRCnfMsgProc(pMsg);
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_CbpTrCnfMsgProc
功能描述  : 用于处理VIA下发的Terminal Response消息的CNF消息
输入参数  : pMsg:消息内容
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2014年02月14日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_CbpTrCnfMsgProc(PS_SI_MSG_STRU *pMsg)
{
    /*lint -e813*/
    SI_STK_EVENT_INFO_STRU              stSTKEvent;

    /*lint -e534*/
    (VOS_VOID)STK_PROTECT_TIMER_STOP;
    /*lint +e534*/

    SI_STKCommDataFree(gstUsatCmdDecode.SatType, (SI_SAT_COMMDATA_STRU*)(&gstUsatCmdDecode.CmdStru));

    /*lint -e534*/
    VOS_MemSet(&gstUsatCmdDecode, 0x00, sizeof(gstUsatCmdDecode));
    /*lint +e534*/

    /* TERMINAL RESPONSE处理结果不为OK时给CSIMA回复错误 */
    if (VOS_OK != (((USIMM_STKTERMINALRSP_CNF_STRU *)pMsg)->stCmdResult.ulResult))
    {
        SI_STK_CbpTRCnfProc(VOS_ERR, 0, 0);

        return;
    }

    /* 通过广播上报主动命令会话结束 */
    if ((0x90 == ((USIMM_STKTERMINALRSP_CNF_STRU *)pMsg)->ucSW1)
      && (0x00 == ((USIMM_STKTERMINALRSP_CNF_STRU *)pMsg)->ucSW2))
    {
        stSTKEvent.STKCBEvent = SI_STK_CMD_END_EVENT;
        stSTKEvent.STKErrorNo = VOS_OK;

        SI_STKCallBack_BroadCast(&stSTKEvent);
    }

    SI_STK_CbpTRCnfProc(VOS_OK,
                        ((USIMM_STKTERMINALRSP_CNF_STRU *)pMsg)->ucSW1,
                        ((USIMM_STKTERMINALRSP_CNF_STRU *)pMsg)->ucSW2);
    /*lint +e813*/
    return;
}

/*****************************************************************************
函 数 名  : SI_STK_TRCnfMsgProc
功能描述  : 用于处理回复的 Terminal Response 消息
输入参数  : pMsg:消息内容
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
History     :
1.日    期  : 2010年07月26日
  作    者  : zhuli
  修改内容  : Create
2.日    期  : 2011年05月05日
  作    者  : j00168360
  修改内容  : [DTS2011050504048]点击STK菜单发短信MP挂死20s
3.日    期  : 2011年5月31日
  作    者  : j00168360
  修改内容  : [DTS2011053103677],巴西10规避MP问题
*****************************************************************************/
VOS_VOID SI_STK_TRCnfMsgProc(PS_SI_MSG_STRU *pMsg)
{
    /*lint -e813*/
    SI_STK_EVENT_INFO_STRU  stSTKEvent;

    stSTKEvent.ClientId         = gstSTKCtrlStru.usClientID;
    stSTKEvent.OpId             = gstSTKCtrlStru.ucOpID;
    stSTKEvent.STKErrorNo       = ((USIMM_STKTERMINALRSP_CNF_STRU *)pMsg)->stCmdResult.ulErrorCode;   /*获取当前的消息内容相关信息*/
    stSTKEvent.STKSwStru.SW1    = ((USIMM_STKTERMINALRSP_CNF_STRU *)pMsg)->ucSW1;
    stSTKEvent.STKSwStru.SW2    = ((USIMM_STKTERMINALRSP_CNF_STRU *)pMsg)->ucSW2;
    stSTKEvent.STKCBEvent       = SI_STK_TERMINAL_RSP_EVENT;                  /*手机无论什么时候都需要回复下发结果*/

    /* 从AT来的TERMINAL RESPONSE或SETUP CALL的TERMINAL RESPONSE要停止定时器 */
    if (SI_STK_TRDOWN == gstSTKCtrlStru.enSTKEventType)
    {
        /*lint -e534*/
        SI_STKCallback(&stSTKEvent);

        (VOS_VOID)STK_PROTECT_TIMER_STOP;
        /*lint +e534*/
    }

    if (SI_STK_SETUPCALL == gstUsatCmdDecode.SatType)
    {
        /*lint -e534*/
        (VOS_VOID)STK_PROTECT_TIMER_STOP;
        /*lint +e534*/

        gstSTKCtrlStru.enSTKEventType = SI_STK_NULL;
    }

    if(SI_STK_SETUPMENU != gstUsatCmdDecode.SatType)        /*如果不是主菜单命令需要释放内存*/
    {
        SI_STKCommDataFree(gstUsatCmdDecode.SatType, (SI_SAT_COMMDATA_STRU*)(&gstUsatCmdDecode.CmdStru));

        /*lint -e534*/
        VOS_MemSet(&gstUsatCmdDecode, 0x00, sizeof(gstUsatCmdDecode));
        /*lint +e534*/
    }

    /* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, begin */
    /* 对于非AT命令回复的TERMINAL RESPONSE，如果卡回复的是9000，需要给AT上报上报^STIN:99,0,0以指示主动命令结束 */
    if((0x90 == ((USIMM_STKTERMINALRSP_CNF_STRU *)pMsg)->ucSW1)
            &&(0x00 == ((USIMM_STKTERMINALRSP_CNF_STRU *)pMsg)->ucSW2)) /*如果无后续主动命令*/
    {
        stSTKEvent.STKCBEvent = SI_STK_CMD_END_EVENT;                       /*Stick需要上报99*/

        SI_STKCallBack_BroadCast(&stSTKEvent);
    }
    /* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, end */

    /* 存在缓存的Evnelope命令 */
    if(0 != gstSTKEnvelopeCmd.ulCmdLen)
    {
        if((0x90 == ((USIMM_STKTERMINALRSP_CNF_STRU *)pMsg)->ucSW1)
            &&(0x00 == ((USIMM_STKTERMINALRSP_CNF_STRU *)pMsg)->ucSW2))
        {
            (VOS_VOID)VOS_SmP(gulSTKApiSmId,500);

            if (VOS_OK != SI_STK_SendEnvelopeReqMsg(VOS_NULL,
                                                    USIMM_GUTL_APP,
                                                    (VOS_UINT8)gstSTKEnvelopeCmd.ulCmdLen,
                                                     gstSTKEnvelopeCmd.aucCmdData))
            {
                STK_NORMAL_LOG("SI_STK_TRCnfMsgProc: SI_STK_SendEnvelopeReqMsg return Err");
            }

            /*lint -e534*/
            VOS_SmV(gulSTKApiSmId);
            /*lint +e534*/
        }
        else
        {
            stSTKEvent.STKCBEvent = SI_STK_ENVELPOE_RSP_EVENT;

            stSTKEvent.STKErrorNo = TAF_ERR_SIM_BUSY;

            gstSTKEnvelopeCmd.ulCmdLen = 0;

            /*lint -e534*/
            SI_STKCallback(&stSTKEvent);
            /*lint +e534*/
        }
    }
    /*lint +e813*/
    return;
}

/*****************************************************************************
函 数 名  : SI_STK_ATEnvelopeCnf
功能描述  : 处理AT信封命令下发回复的消息
输入参数  : pMsg: 消息内容
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
History     :
1.日    期  : 2013年07月12日
  作    者  : zhuli
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_ATEnvelopeCnf(USIMM_STKENVELOPE_CNF_STRU *pstMsg)
{
    /*lint -e813*/
    SI_STK_EVENT_INFO_STRU  stSTKEvent;

    stSTKEvent.ClientId         = gstSTKCtrlStru.usClientID;
    stSTKEvent.OpId             = gstSTKCtrlStru.ucOpID;

    stSTKEvent.STKErrorNo       = pstMsg->stCmdResult.ulErrorCode;
    stSTKEvent.STKSwStru.SW1    = pstMsg->ucSW1;
    stSTKEvent.STKSwStru.SW2    = pstMsg->ucSW2;

    stSTKEvent.STKCBEvent       = SI_STK_ENVELPOE_RSP_EVENT;

    /*lint -e534*/
    SI_STKCallback(&stSTKEvent);        /*回复下发结果*/
    /*lint +e534*/

    if ((0x90 == pstMsg->ucSW1) && (0x00 == pstMsg->ucSW2))
    {
        stSTKEvent.STKCBEvent = SI_STK_CMD_END_EVENT;

        SI_STKCallBack_BroadCast(&stSTKEvent);       /*需要上报99*/
    }
    /*lint +e813*/

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_MenuSelectionCnfProc
功能描述  : 处理信封命令下发回复的消息
输入参数  : pMsg: 消息内容
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
History     :
1.日    期  : 2010年07月26日
  作    者  : zhuli
  修改内容  : Create
2.日    期  : 2011年04月23日
  作    者  : j00168360
  修改内容  : [DTS2011042203287]当卡忙时未给AT回复导致AT挂死
*****************************************************************************/
VOS_VOID SI_STK_MenuSelectionCnf(USIMM_STKENVELOPE_CNF_STRU *pstMsg)
{
    if (USIMM_SW_CARD_BUSY == pstMsg->stCmdResult.ulErrorCode)    /*主菜单选择等待下次下发*/
    {
        STK_WARNING_LOG("SI_STK_MenuSelectionCnf: Receive USIMM_SW_CARD_BUSY");

        return;
    }
    else
    {
        SI_STK_ClearEnvelopeCmd();      /*清除缓存的信封命令,这里只缓存主菜单选择*/
    }

    SI_STK_ATEnvelopeCnf(pstMsg);

    return;
}

#if 0
/*****************************************************************************
函 数 名  : SI_STK_ChangePtrToLvData
功能描述  : 将STK解析后的数据结构转换为数据内容
输入参数  : pstSrc: 数据结构内容
输出参数  : pstDest:数据内容
返 回 值  : 无
调用函数  :
被调函数  :
History     :
1.日    期  : 2015年02月12日
  作    者  : zhuli
  修改内容  : Create
*****************************************************************************/

VOS_VOID SI_STK_ChangePtrToLvData(SI_STK_ENVELOPE_RSP_STRU *pstSrc, SI_STK_ENVELOPE_CNFDATA_STRU *pstDest)
{
    SI_SAT_COMMDATA_STRU        *pstInput;
    SI_STK_FLAGLVDATA_STRU      *pstOutput;
    VOS_UINT32                  i;
    SI_SAT_LV_STRU              *pstPtrData;
    VOS_UINT32                  ulBitValue;
    VOS_UINT32                  ulDecOffset;
    VOS_UINT32                  ulSrcOffet;

    pstInput    = (SI_SAT_COMMDATA_STRU *)pstSrc;

    pstOutput   = (SI_STK_FLAGLVDATA_STRU *)pstDest;

    pstOutput->ulReqFlag = pstInput->ulOpInfo ;

    ulDecOffset = 0;

    ulSrcOffet = 0;

    for(i=0; i<32; i++)
    {
        pstPtrData = (SI_SAT_LV_STRU*)&pstInput->aucDecode[ulSrcOffet];

        ulBitValue = SI_STKGetBit32(pstInput->ulOpInfo, i);

        if (0 != ulBitValue)
        {
            pstOutput->ulDataLen += pstPtrData->ulLen;

            pstOutput->aucData[ulDecOffset] = (VOS_UINT8)pstPtrData->ulLen;

            ulDecOffset ++;

            VOS_MemCpy(&pstOutput->aucData[ulDecOffset], &pstPtrData->pValue, pstPtrData->ulLen);

            ulDecOffset += pstPtrData->ulLen;
        }

        ulSrcOffet += sizeof(SI_SAT_LV_STRU);
    }

    return;
}
#endif

/*****************************************************************************
函 数 名  : SI_STK_EnvelopeCnfMsgProc
功能描述  : 处理信封命令下发回复的消息
输入参数  : pMsg: 消息内容
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
History     :
1.日    期  : 2013年07月12日
  作    者  : zhuli
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_TAFEnvelopeCnf(USIMM_STKENVELOPE_CNF_STRU *pstMsg)
{
    SI_STK_ENVELOPEDWON_CNF_STRU       *pstSendMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRecPID;

    if (VOS_ERR == SI_STK_GetRecTAFPID(&ulRecPID))
    {
        STK_WARNING_LOG("SI_STK_TAFEnvelopeCnf: Get Receiver PID Fail");

        return ;
    }

    if (STK_IS_TAF_ENVELOPE_CNF_DATATYPE_VALID(pstMsg->ucDataType))
    {
        pstSendMsg = (SI_STK_ENVELOPEDWON_CNF_STRU*)VOS_AllocMsg(MAPS_STK_PID,
                                        sizeof(SI_STK_ENVELOPEDWON_CNF_STRU)-VOS_MSG_HEAD_LENGTH);
    }

    if (VOS_NULL_PTR == pstSendMsg)
    {
        STK_ERROR_LOG("SI_STK_TAFEnvelopeCnf: Alloc Msg is Fail or Envelope Type is Error");

        return;
    }

    pstSendMsg->stCmdResult.ulSenderPid     = MAPS_STK_PID;
    pstSendMsg->stCmdResult.ulReceiverPid   = ulRecPID;
    pstSendMsg->stCmdResult.enMsgName       = SI_STK_ENVELOPE_CNF;
    pstSendMsg->stCmdResult.ulSendPara      = pstMsg->stCmdResult.ulSendPara;
    pstSendMsg->stCmdResult.ulResult        = pstMsg->stCmdResult.ulResult;
    pstSendMsg->stCmdResult.ulErrorNO       = pstMsg->stCmdResult.ulErrorCode;
    pstSendMsg->stCmdResult.stSWData.SW1    = pstMsg->ucSW1;
    pstSendMsg->stCmdResult.stSWData.SW2    = pstMsg->ucSW2;
    pstSendMsg->enEnvelopeType              = pstMsg->ucDataType;
    pstSendMsg->bTransFlag                  = VOS_TRUE;
    pstSendMsg->stCnfData.ulRspDataLen      = pstMsg->ucDataLen;

    /*lint -e534*/
    VOS_MemCpy(pstSendMsg->stCnfData.aucRspData, pstMsg->aucData, pstMsg->ucDataLen);
    /*lint +e534*/

    /*根据NAS需要，更改下面结果的返回*/
    if ((SI_STK_ENVELOPE_CALLCRTL == pstMsg->ucDataType)
       && (((0x6F == pstMsg->ucSW1)&&(0x00 == pstMsg->ucSW2))
        ||((0x6F == pstMsg->ucSW1)&&(0xC2 == pstMsg->ucSW2))
        ||((0x6D == pstMsg->ucSW1)&&(0x00 == pstMsg->ucSW2))))
    {
        STK_WARNING_LOG("SI_STK_TAFEnvelopeCnf: Change CC Result");

        pstSendMsg->stCmdResult.ulResult    = VOS_OK;
        pstSendMsg->stCmdResult.ulErrorNO   = USIMM_SW_OK;
    }

    if ((SI_STK_ENVELOPE_SMSCRTL == pstMsg->ucDataType)
      && (((0x6F == pstMsg->ucSW1)&&(0x00 == pstMsg->ucSW2))
        ||((0x6D == pstMsg->ucSW1)&&(0x00 == pstMsg->ucSW2))))
    {
        STK_WARNING_LOG("SI_STK_TAFEnvelopeCnf: Change MO Sms Result");

        pstSendMsg->stCmdResult.ulResult    = VOS_OK;
        pstSendMsg->stCmdResult.ulErrorNO   = USIMM_SW_OK;
    }

    if (VOS_OK != VOS_SendMsg(MAPS_STK_PID, pstSendMsg))
    {
        STK_ERROR_LOG("SI_STK_TAFEnvelopeCnf: Send Msg is Fail ");
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_EnvelopeCnfMsgProc
功能描述  : 处理信封命令下发回复的消息
输入参数  : pMsg: 消息内容
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
History     :
1.日    期  : 2013年07月12日
  作    者  : zhuli
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_EnvelopeCnfMsgProc(PS_SI_MSG_STRU *pstMsg)
{
    USIMM_STKENVELOPE_CNF_STRU             *pstUsimmMsg;

    pstUsimmMsg = (USIMM_STKENVELOPE_CNF_STRU *)pstMsg;

    /* 只有之前通过AT 主菜单选中的才回调 */
    if (SI_STK_MENUSELECTION == gstSTKCtrlStru.enSTKEventType)
    {
        SI_STK_MenuSelectionCnf(pstUsimmMsg);
    }
    /* 只有之前通过AT Envelope的才回调 ,现在XSMS也要回调*/
    else if ((SI_STK_ENVELOPEDOWN     == gstSTKCtrlStru.enSTKEventType)
          && (SI_STK_AT_ENVELOPE      == pstUsimmMsg->stCmdResult.ulSendPara))
    {
        STK_NORMAL_LOG("SI_STK_EnvelopeCnfMsgProc: The SI_STK_ENVELOPEDOWN Return");

        SI_STK_ATEnvelopeCnf(pstUsimmMsg);
    }
    else if (SI_STK_ENVELOPE_TIMEEXP == pstUsimmMsg->ucDataType)
    {
        if (USIMM_SW_CARD_BUSY != pstUsimmMsg->stCmdResult.ulErrorCode)
        {
            SI_STK_ClearEnvelopeCmd();
        }

        STK_NORMAL_LOG("SI_STK_EnvelopeCnfMsgProc: The SI_STK_ENVELOPE_TIMEEXP Return");
    }
    else if ((SI_STK_ENVELOPE_EVENTDOWN == pstUsimmMsg->ucDataType)
            &&((SI_STK_ENVELOPE_LOCI_RESEND == pstUsimmMsg->stCmdResult.ulSendPara)
              ||(SI_STK_ENVELOPE_ACC_RESEND == pstUsimmMsg->stCmdResult.ulSendPara)))
    {
        if ((0x93 == pstUsimmMsg->ucSW1)&&(0x00 == pstUsimmMsg->ucSW2))
        {
            STK_NORMAL_LOG("SI_STK_EnvelopeCnfMsgProc: The SI_STK_ENVELOPE_EVENTDOWN Return 9300");
        }
        else
        {
            SI_STK_EventResendClean(pstUsimmMsg->stCmdResult.ulSendPara);
        }
    }
    else if (SI_STK_ENVELOPE_EVENTDOWN == pstUsimmMsg->ucDataType)
    {
        STK_NORMAL_LOG("SI_STK_EnvelopeCnfMsgProc: The SI_STK_EVENT_DOWN Return");
    }
    else
    {
        SI_STK_RcvSmsEnvelopeCnfDispatchHandle(pstUsimmMsg);
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_RcvSmsEnvelopeCnfDispatchHandle
功能描述  : 处理信封命令下发回复的消息(PP DOWNLOAD 相关)
输入参数  : pMsg: 消息内容
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
History     :
1.日    期  : 2010年07月26日
  作    者  : zhuli
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_RcvSmsEnvelopeCnfDispatchHandle(
    USIMM_STKENVELOPE_CNF_STRU             *pstUsimmMsg
)
{
    /* 如果是对X模PP_DOWNLOAD短信的回复进入另外流程 */
    if ((SI_STK_XSMS_ENVELOPE   == pstUsimmMsg->stCmdResult.ulSendPara)
     && (SI_STK_ENVELOPE_PPDOWN == pstUsimmMsg->ucDataType))
    {
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        /* X模短信的PP_DOWNLOAD CNF处理函数 */
        SI_STK_RcvXsmsEnvelopeHandle(pstUsimmMsg);
#endif
    }
    else
    {
        SI_STK_TAFEnvelopeCnf(pstUsimmMsg);
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_EnvelopeCnfMsgProc
功能描述  : 处理信封命令下发回复的消息
输入参数  : pMsg: 消息内容
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
History     :
1.日    期  : 2010年07月26日
  作    者  : zhuli
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_RefreshCnfMsgProc(PS_SI_MSG_STRU *pMsg)
{
    /*lint -e813*/
    SI_STK_EVENT_INFO_STRU              stSTKEvent;
    USIMM_STKREFRESH_CNF_STRU           *pstMsg;

    /*lint -e534*/
    VOS_MemSet(&stSTKEvent, 0, sizeof(stSTKEvent));
    /*lint +e534*/

    pstMsg = (USIMM_STKREFRESH_CNF_STRU *)pMsg;

    /* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, begin */
    if ((pstMsg->enRefreshType == USIMM_RESET)&&(VOS_OK == pstMsg->stCmdResult.ulResult))
    {
        /* 清空Event List */
        /*lint -e534*/
        VOS_MemSet(&g_stSTKEventState, 0, sizeof(g_stSTKEventState));
        /*lint +e534*/
    }

    stSTKEvent.STKErrorNo                           = VOS_OK;

    stSTKEvent.STKCmdStru.CmdDetail.ucCommandType   = (VOS_UINT8)pstMsg->enRefreshType;

    stSTKEvent.STKCmdStru.SatType                   = SI_STK_REFRESH;

    /* Refresh命令处理完了之后还要上报到AP */
    if(VOS_TRUE == SI_STK_CheckSupportAP())
    {
        /*lint -e534*/
        SI_STKDataIndCallback(&gstUsatCmdDecode);
        /*lint +e534*/

        /* 后续没有主动命令，上报CSIN:0,0 */
        if (0 == pstMsg->ulSatLen)
        {
            stSTKEvent.STKCBEvent       = SI_STK_CMD_END_EVENT;

            stSTKEvent.STKSwStru.SW1    = 0x90;

            stSTKEvent.STKSwStru.SW2    = 0x00;

            SI_STKCallBack_BroadCast(&stSTKEvent);
        }

        return;
    }
    /* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, end */

    if ((VOS_OK == pstMsg->stCmdResult.ulResult)&&(TAF_TRUE == g_stSTKProfileContent.ucFuncEnable))
    {
        stSTKEvent.STKCBEvent = SI_STK_CMD_IND_EVENT;

        gucSTKRefreshQua    = (VOS_UINT8)pstMsg->enRefreshType;

        SI_STKCallBack_BroadCast(&stSTKEvent);

        if (VOS_OK != STK_REFRESH_CNF_TIMER_START(5000))
        {
            STK_INFO_LOG("SI_STK_RefreshCnfMsgProc: Start RefResh Time fail");
        }
    }
    /*lint +e813*/
    return;
}

/* Add by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, begin */
/*****************************************************************************
函 数 名  : SI_STK_CardStatusMsgProc
功能描述  : 处理卡状态remove时Event List更新
输入参数  : pMsg: 消息内容
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
History     :
1.日    期  : 2012年02月20日
  作    者  : wangxiaofei
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_CardStatusMsgProc(PS_SI_MSG_STRU *pMsg)
{
    USIMM_CARDSTATUS_IND_STRU          *pstUsimStatus;

    pstUsimStatus = (USIMM_CARDSTATUS_IND_STRU *)pMsg;

    /* 保存当前物理卡类型，其它信息以USIM的信息为准 */
    g_stStkCardInfo.enPhyType   = pstUsimStatus->enPhyCardType;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    g_stStkCardInfo.enCardType  = pstUsimStatus->stCsimUimInfo.enCardType;
    g_stStkCardInfo.enSvcStatus = pstUsimStatus->stCsimUimInfo.enCardService;

    /* 如果是国际卡 */
    if ((USIMM_CARD_SERVIC_ABSENT    == g_stStkCardInfo.enSvcStatus)
    &&  (USIMM_CARD_SERVIC_AVAILABLE == pstUsimStatus->stUsimSimInfo.enCardService))
    {
        g_stStkCardInfo.enCardType  = pstUsimStatus->stUsimSimInfo.enCardType;
        g_stStkCardInfo.enSvcStatus = pstUsimStatus->stUsimSimInfo.enCardService;
    }
#else
    g_stStkCardInfo.enCardType  = pstUsimStatus->stUsimSimInfo.enCardType;
    g_stStkCardInfo.enSvcStatus = pstUsimStatus->stUsimSimInfo.enCardService;
#endif

    /*卡不在*/
    if (USIMM_CARD_SERVIC_ABSENT == g_stStkCardInfo.enSvcStatus)
    {
        if (SI_STK_SETUPMENU == gstUsatCmdDecode.SatType)
        {
            gstSetUpMenuData.ucUsatTag = SI_STK_MENU_NOTEXIST;

            SI_STKCommDataFree(SI_STK_SETUPMENU, (SI_SAT_COMMDATA_STRU *)&gstSetUpMenuData.stSetUpMenu);
        }
        else if (SI_STK_NOCMDDATA != gstUsatCmdDecode.SatType)
        {
            SI_STKCommDataFree(gstUsatCmdDecode.SatType, (SI_SAT_COMMDATA_STRU *)&gstUsatCmdDecode.CmdStru);
        }
        else
        {

        }

        STK_ResetGlobalValue();
    }
    else
    {
        STK_ProfileInit(&g_stSTKProfileContent, g_stStkCardInfo.enPhyType);
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_GetMainMenuProc
功能描述  : 获取STK功能的主菜单
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年7月13日
  作    者  : m00128685
  修改内容  : Create
2.日    期  : 2011年5月31日
  作    者  : j00168360
  修改内容  : [DTS2011053103677],巴西10规避MP问题
*****************************************************************************/
VOS_VOID SI_STK_GetMainMenuReqProc(SI_STK_REQ_STRU *STKReqMsg)
{
    /*lint -e813*/
    SI_STK_EVENT_INFO_STRU stSTKEvent;
    VOS_UINT32             ulResult;

    stSTKEvent.ClientId = STKReqMsg->ClientId;

    stSTKEvent.OpId     = STKReqMsg->OpId;

    ulResult = SI_STKCheckCardState();

    if(TAF_ERR_NO_ERROR != ulResult)/*当前卡状态错误*/
    {
        stSTKEvent.STKErrorNo = ulResult;/*填写错误原因值*/

        /*lint -e534*/
        SI_STKEventCallback(&stSTKEvent);
        /*lint +e534*/

        return;
    }

    /*判断是否存在*/
    if(SI_STK_MENU_EXIST == gstSetUpMenuData.ucUsatTag) /*主菜单存在*/
    {
        /*lint -e534*/
        VOS_MemCpy(&stSTKEvent.STKCmdStru.CmdStru, &gstSetUpMenuData.stSetUpMenu, sizeof(gstSetUpMenuData.stSetUpMenu));

        VOS_MemCpy(&stSTKEvent.STKCmdStru.CmdDetail,&gstSetUpMenuData.CmdDetail, sizeof(gstSetUpMenuData.CmdDetail));

        VOS_MemCpy(&stSTKEvent.STKCmdStru.CmdDevice,&gstSetUpMenuData.CmdDevice, sizeof(gstSetUpMenuData.CmdDevice));
        /*lint +e534*/
    }
    else     /*主菜单不存在*/
    {
        stSTKEvent.STKErrorNo = TAF_ERR_SAT_NO_MAIN_MENU;/*menu not exist*/

        /*lint -e534*/
        SI_STKEventCallback(&stSTKEvent);
        /*lint +e534*/

        STK_WARNING_LOG("SI_STK_GetMainMenuProc: There is any Main Menu Content");/*打印错误*/

        return;
    }

    stSTKEvent.STKCmdStru.SatType = SI_STK_SETUPMENU;

    stSTKEvent.STKErrorNo = TAF_ERR_NO_ERROR;

    stSTKEvent.STKCBEvent = SI_STK_GET_CMD_RSP_EVENT;

    /*lint -e534*/
    SI_STKEventCallback(&stSTKEvent);
    /*lint +e534*/

    if((SI_STK_NOCMDDATA != gstUsatCmdDecode.SatType) && (SI_STK_SETUPMENU != gstUsatCmdDecode.SatType))
    {
        /*lint -e534*/
        SI_STKDataIndCallback(&gstUsatCmdDecode);
        /*lint +e534*/
    }
    /*lint +e813*/
    return;
}

/*****************************************************************************
函 数 名  : SI_STK_GetSTKCommandProc
功能描述  : 获取缓存的STK主动命令
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2008年10月18日
  作    者  : m00128685
  修改内容  : Create
2.日    期  : 2011年04月23日
  作    者  : j00168360
  修改内容  : [DTS2011042203287]当卡忙时未给AT回复导致AT挂死
*****************************************************************************/
VOS_VOID SI_STK_GetSTKCommandReqProc(SI_STK_REQ_STRU *STKReqMsg)
{
    /*lint -e813*/
    SI_STK_EVENT_INFO_STRU  stSTKEvent;
    VOS_BOOL                bSupportAP;

    bSupportAP = SI_STK_CheckSupportAP();

    /* Android系统不启动定时器，也不需要停定时器 */
    if (VOS_FALSE == bSupportAP)
    {
        /*lint -e534*/
        (VOS_VOID)STK_IND_TIMER_STOP;
        /*lint +e534*/
    }

    stSTKEvent.STKCBEvent = SI_STK_GET_CMD_RSP_EVENT;

    stSTKEvent.ClientId     = STKReqMsg->ClientId;
    stSTKEvent.OpId         = STKReqMsg->OpId;

    if ((VOS_FALSE == bSupportAP)              /*当前对接不是AP*/
        &&(SI_STK_REFRESH == STKReqMsg->SatType)            /*当前上报的是Refresh命令*/
        &&(TAF_TRUE == g_stSTKProfileContent.ucFuncEnable))   /*当前上报功能打开*/
    {
        stSTKEvent.STKErrorNo                        = TAF_ERR_NO_ERROR;
        stSTKEvent.STKCmdStru.SatType                = SI_STK_REFRESH;
        stSTKEvent.STKCmdStru.CmdDetail.ucCommandQua = gucSTKRefreshQua;

        /*lint -e534*/
        SI_STKEventCallback(&stSTKEvent);

        (VOS_VOID)STK_REFRESH_CNF_TIMER_STOP;
        /*lint +e534*/

        return;
    }

    /* 不与AP对接，需要判断是否存在 */
    if ((STKReqMsg->SatType != gstUsatCmdDecode.SatType)
       && (VOS_FALSE == bSupportAP))
    {
        stSTKEvent.STKErrorNo = TAF_ERR_SAT_WRONG_PARA;/*当前参数错误*/

        /*lint -e534*/
        SI_STKEventCallback(&stSTKEvent);
        /*lint +e534*/

        STK_WARNING_LOG("SI_STK_GetSTKCommandProc: There is any STK Command");/*打印错误*/

        return;
    }

    stSTKEvent.STKErrorNo = TAF_ERR_NO_ERROR;

    /*lint -e534*/
    VOS_MemCpy(&stSTKEvent.STKCmdStru, &gstUsatCmdDecode, sizeof(SI_STK_DATA_INFO_STRU));

    SI_STKEventCallback(&stSTKEvent);
    /*lint +e534*/
    /*lint +e813*/
    return;
}

/*****************************************************************************
函 数 名  : SI_STK_QuerySTKCommandProc
功能描述  : 查询最后一次SIM卡上报的主动命令
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2008年10月18日
  作    者  : m00128685
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_QuerySTKCommandReqProc(SI_STK_REQ_STRU *STKReqMsg)
{
    /*lint -e813*/
    SI_STK_EVENT_INFO_STRU stSTKEvent;
    VOS_UINT32             ulResult;

    stSTKEvent.ClientId = STKReqMsg->ClientId;
    stSTKEvent.OpId     = STKReqMsg->OpId;

    /*调用错误处理函数,PIN等卡状态*/
    ulResult = SI_STKCheckCardState();

    if(TAF_ERR_NO_ERROR != ulResult)
    {
        stSTKEvent.STKErrorNo = ulResult;   /*填写错误原因值*/
    }
    else
    {
        /*判断是否存在*/
        if(SI_STK_NOCMDDATA == gstUsatCmdDecode.SatType)
        {
            if(gstSetUpMenuData.ucUsatTag != SI_STK_MENU_EXIST)
            {
                stSTKEvent.STKErrorNo = TAF_ERR_SAT_WRONG_PARA;/*返回当前参数错误*/

                STK_WARNING_LOG("SI_STK_QuerySTKCommandProc: There is any STK Command");/*打印错误*/
            }
            else
            {
                stSTKEvent.STKErrorNo           = TAF_ERR_NO_ERROR;
                stSTKEvent.STKCBEvent           = SI_STK_CMD_QUERY_RSP_EVENT;
                stSTKEvent.STKCmdStru.SatType   = SI_STK_SETUPMENU;
            }
        }
        else
        {
            stSTKEvent.STKErrorNo           = TAF_ERR_NO_ERROR;
            stSTKEvent.STKCBEvent           = SI_STK_CMD_QUERY_RSP_EVENT;
            stSTKEvent.STKCmdStru.SatType   = gstUsatCmdDecode.SatType;
            /*lint -e534*/
            VOS_MemCpy(&stSTKEvent.STKCmdStru.CmdDetail, &gstUsatCmdDecode.CmdDetail, sizeof(SI_STK_COMMAND_DETAILS_STRU));
            /*lint +e534*/
        }
    }

    /*lint -e534*/
    SI_STKEventCallback(&stSTKEvent);
    /*lint +e813 +e534*/
    return;
}

/*****************************************************************************
函 数 名  : SI_STK_TRDownReqProc
功能描述  : 发送主动命令执行结果
输入参数  : STKReqMsg:外部下发的消息请求
输出参数  : 无
返 回 值  : 无
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2010年08月27日
  作    者  : zhuli
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_TRDownReqProc(SI_STK_REQ_STRU *pstTRMsg)
{
    /*lint -e813*/
    SI_STK_EVENT_INFO_STRU      stSTKEvent;
    SI_STK_TERMINAL_RSP_STRU    *pstData;
    VOS_UINT32                  ulResult;
    VOS_UINT8                   aucResp[256] = {0};

    stSTKEvent.ClientId     = pstTRMsg->ClientId;
    stSTKEvent.OpId         = pstTRMsg->OpId;
    stSTKEvent.STKCBEvent   = SI_STK_TERMINAL_RSP_EVENT;

    ulResult = SI_STKErrorProc();

    if(TAF_ERR_NO_ERROR != ulResult)
    {
        stSTKEvent.STKErrorNo = ulResult;

        /*lint -e534*/
        SI_STKEventCallback(&stSTKEvent);
        /*lint +e534*/

        STK_ERROR_LOG("SI_STK_TRDownReqProc: SI_STKErrorProc return error.");

        return;
    }

    pstData = (SI_STK_TERMINAL_RSP_STRU *)pstTRMsg->Data;

    if(pstData->CmdType != gstUsatCmdDecode.SatType)
    {
        stSTKEvent.STKErrorNo = TAF_ERR_SIM_FAIL;

        /*lint -e534*/
        SI_STKEventCallback(&stSTKEvent);
        /*lint +e534*/

        STK_ERROR_LOG("SI_STK_TRDownReqProc: The input Cmd Type is different to the Current.");

        return ;
    }

    SI_STK_InitTResponse(aucResp,&gstUsatCmdDecode.CmdDetail,&pstData->Result);

    /*AT 发送过来的数据指针需要重新定位*/
    if((pstData->CmdType == SI_STK_GETINPUT)&&(1 == pstData->uResp.GetInputRsp.OP_TextStr))
    {
        pstData->uResp.GetInputRsp.TextStr.pucText = pstData->aucData;
    }

    if((pstData->CmdType == SI_STK_GETINKEY)&&(1 == pstData->uResp.GetInkeyRsp.OP_TextStr))
    {
        pstData->uResp.GetInkeyRsp.TextStr.pucText = pstData->aucData;
    }

    if(VOS_OK != SI_STKCommCodeData(aucResp, SI_CODE_TR_DATA, pstData->CmdType, (SI_SAT_COMMDATA_STRU *)pstData))
    {
        stSTKEvent.STKErrorNo = TAF_ERR_SIM_FAIL;

        /*lint -e534*/
        SI_STKEventCallback(&stSTKEvent);
        /*lint +e534*/

        STK_ERROR_LOG("SI_STK_TRDownReqProc: SI_STKCommCodeData Error.");

        return;
    }

    gstSTKCtrlStru.enSTKLock        = SI_STK_PROLOCK;
    gstSTKCtrlStru.usClientID       = pstTRMsg->ClientId;
    gstSTKCtrlStru.ucOpID           = pstTRMsg->OpId;
    gstSTKCtrlStru.enSTKEventType   = SI_STK_TRDOWN;

    if (VOS_OK != SI_STK_SendTerminalResponseReqMsg(aucResp[0],&aucResp[1], USIMM_TR_TYPE_BALONG))
    {
        stSTKEvent.STKErrorNo = TAF_ERR_SIM_FAIL;

        /*lint -e534*/
        SI_STKCallback(&stSTKEvent);
        /*lint +e534*/

        STK_ERROR_LOG("SI_STK_SendTerminalResponse: SI_STK_SendTerminalResponse Error.");
    }
    /*lint +e813*/

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_MenuSelProtect
功能描述  : STK功能菜单选择时保护处理
输入参数  : ulEventType  --ENVELOPE类型
输出参数  : 无
返 回 值  : VOS_OK，VOS_ERR
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2011年04月23日
  作    者  : j00168360
  修改内容  : [DTS2011042203287]当卡忙时未给AT回复导致AT挂死且有时点击STK菜单无响应
*****************************************************************************/
VOS_UINT32 SI_STK_MenuSelProtect(VOS_UINT32 ulEventType)
{
    /* 只在ENVELOPE类型为菜单选择时作保护处理 */
    if(SI_STK_ENVELOPE_MENUSEL != ulEventType)
    {
        return VOS_OK;
    }

    if((SI_STK_NOCMDDATA == gstUsatCmdDecode.SatType)||(SI_STK_SETUPMENU == gstUsatCmdDecode.SatType))
    {
        return VOS_OK;
    }

    SI_STKSimpleResponse(&gstUsatCmdDecode.CmdDetail, SI_STK_CMDEND);

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  : SI_STK_MenuSelectionProc
功能描述  : 发送主菜单选择
输入参数  : STKReqMsg:外部下发的Envelope消息请求，目前只有选主菜单
输出参数  : 无
返 回 值  : 无
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2010年08月27日
  作    者  : zhuli
  修改内容  : Create
2.日    期  : 2011年04月23日
  作    者  : j00168360
  修改内容  : [DTS2011042203287]当卡忙时未给AT回复导致AT挂死且有时点击STK菜单无响应
3.日    期  : 2013年07月12日
  作    者  : zhuli
  修改内容  : 函数改名只处理主菜单选择
*****************************************************************************/
VOS_VOID SI_STK_MenuSelectionProc(SI_STK_REQ_STRU *STKReqMsg)
{
    /*lint -e813*/
    SI_STK_EVENT_INFO_STRU  stSTKEvent;
    VOS_UINT32              ulResult;
    SI_STK_ENVELOPE_STRU   *pstData;
    VOS_UINT8               aucEvent[256] = {0};
    VOS_UINT32              ulDataLen;
    VOS_UINT32              ulDataOffset;

    stSTKEvent.ClientId     = STKReqMsg->ClientId;
    stSTKEvent.OpId         = STKReqMsg->OpId;
    stSTKEvent.STKCBEvent   = SI_STK_ENVELPOE_RSP_EVENT;

    ulResult = SI_STKErrorProc();

    if (TAF_ERR_NO_ERROR != ulResult)
    {
        STK_ERROR_LOG("SI_STK_EnvelopeDownReqProc: SI_STKErrorProc return error.");

        stSTKEvent.STKErrorNo = ulResult;

        /*lint -e534*/
        SI_STKEventCallback(&stSTKEvent);
        /*lint +e534*/

        return;                                             /*Event的忽略*/
    }

    /*选中菜单才需要保存下发参数*/
    gstSTKCtrlStru.usClientID       = STKReqMsg->ClientId;
    gstSTKCtrlStru.ucOpID           = STKReqMsg->OpId;
    gstSTKCtrlStru.enSTKEventType   = SI_STK_MENUSELECTION;

    gstSTKCtrlStru.enSTKLock        = SI_STK_PROLOCK;

    pstData = (SI_STK_ENVELOPE_STRU *)STKReqMsg->Data;

    if (VOS_ERR == SI_STK_EnvelopeData_Code(pstData, &ulDataLen, aucEvent, &ulDataOffset))
    {
        STK_ERROR_LOG("SI_STK_EnvelopeDownReqProc: The SI_STK_EnvelopeData_Code is Error");

        stSTKEvent.STKErrorNo = TAF_ERR_SIM_FAIL;

        /*lint -e534*/
        SI_STKEventCallback(&stSTKEvent);
        /*lint +e534*/

        return ;
    }

    if (VOS_ERR == SI_STK_MenuSelProtect(STKReqMsg->SatType))
    {
        SI_STK_SaveEnvelopeCmd(ulDataLen, &aucEvent[ulDataOffset]);

        return ;
    }

    ulResult = SI_STK_SendEnvelopeReqMsg(VOS_NULL, USIMM_GUTL_APP, (VOS_UINT8)ulDataLen, &aucEvent[ulDataOffset]);

    if (VOS_OK != ulResult)
    {
        stSTKEvent.STKErrorNo = TAF_ERR_SIM_FAIL;

        /*lint -e534*/
        SI_STKCallback(&stSTKEvent);
        /*lint +e534*/

        STK_ERROR_LOG("SI_STK_EnvelopeDownReqProc: USIMM_EnvelopeReq Error.");
    }
    /*lint +e813*/

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_TRDownReqProc
功能描述  : 发送主动命令执行结果
输入参数  : STKReqMsg:外部下发的消息请求
输出参数  : 无
返 回 值  : 无
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2010年08月27日
  作    者  : zhuli
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_SimpleDownReqProc(SI_STK_REQ_STRU *STKReqMsg)
{
    /*lint -e813*/
    SI_STK_EVENT_INFO_STRU              stSTKEvent;
    VOS_UINT32                          ulResult;

    stSTKEvent.ClientId     = STKReqMsg->ClientId;
    stSTKEvent.OpId         = STKReqMsg->OpId;

    if(STKReqMsg->SatType == SI_STK_TRSEND)
    {
        stSTKEvent.STKCBEvent   = SI_STK_TERMINAL_RSP_EVENT;
    }
    else
    {
        stSTKEvent.STKCBEvent   = SI_STK_ENVELPOE_RSP_EVENT;
    }

    if (SI_STK_PROLOCK == gstSTKCtrlStru.enSTKLock)
    {
        STK_WARNING_LOG("SI_STK_SimpleDownReqProc: The STK is Locked");

        ulResult = TAF_ERR_UNSPECIFIED_ERROR;
    }
    else if (USIMM_CARD_SERVIC_ABSENT == g_stStkCardInfo.enSvcStatus)
    {
        STK_WARNING_LOG("SI_STK_SimpleDownReqProc: The Card Absent");

        ulResult = TAF_ERR_SIM_FAIL;
    }
    else
    {
        ulResult = TAF_ERR_NO_ERROR;
    }

    if(TAF_ERR_NO_ERROR != ulResult)
    {
        STK_ERROR_LOG("SI_STK_EnvelopeDownReqProc: SI_STKErrorProc return error.");

        stSTKEvent.STKErrorNo = ulResult;

        /*lint -e534*/
        SI_STKEventCallback(&stSTKEvent);
        /*lint +e534*/

        return;
    }

    gstSTKCtrlStru.enSTKLock        = SI_STK_PROLOCK;
    gstSTKCtrlStru.usClientID       = STKReqMsg->ClientId;
    gstSTKCtrlStru.ucOpID           = STKReqMsg->OpId;

    if (STKReqMsg->SatType == SI_STK_TRSEND)
    {
        gstSTKCtrlStru.enSTKEventType   = SI_STK_TRDOWN;

        ulResult = SI_STK_SendTerminalResponseReqMsg((VOS_UINT8)STKReqMsg->Datalen, STKReqMsg->Data, USIMM_TR_TYPE_BALONG);
    }
    else
    {
       gstSTKCtrlStru.enSTKEventType    = SI_STK_ENVELOPEDOWN;

       ulResult = SI_STK_SendEnvelopeReqMsg(SI_STK_AT_ENVELOPE, USIMM_GUTL_APP,(VOS_UINT8)STKReqMsg->Datalen, STKReqMsg->Data);
    }

    if(VOS_OK != ulResult)
    {
        stSTKEvent.STKErrorNo = TAF_ERR_SIM_FAIL;

        /*lint -e534*/
        SI_STKCallback(&stSTKEvent);
        /*lint +e534*/

        STK_ERROR_LOG("SI_STK_TerminalResponse: USIMM API Return Error.");
    }
    /*lint +e813*/
    return;
}

/*****************************************************************************
函 数 名  : SI_STK_CbpTRDataReqProc
功能描述  : 透传VIA下发的Terminal Response数据
输入参数  : STKReqMsg:外部下发的消息请求
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2014年02月14日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_CbpTRDataReqProc(SI_STK_REQ_STRU *STKReqMsg)
{
    if (SI_STK_PROLOCK == gstSTKCtrlStru.enSTKLock)
    {
        STK_WARNING_LOG("SI_STK_CbpTRDataReqProc: The STK is Locked");

        SI_STK_CbpTRCnfProc(VOS_ERR, 0, 0);

        return;
    }

    if (VOS_OK != SI_STK_SendTerminalResponseReqMsg((VOS_UINT8)STKReqMsg->Datalen, STKReqMsg->Data, USIMM_TR_TYPE_CBP))
    {
        SI_STK_CbpTRCnfProc(VOS_ERR, 0, 0);

        STK_ERROR_LOG("SI_STK_CbpTRDataReqProc: SI_STK_SendTerminalResponse Error.");
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_CbpTRCnfProc
功能描述  : 将VIA下发Terminal Response的处理结果回复给CSIM Agent
输入参数  : ulErrorCode:TR下发的处理结果
            ucSW1:状态字1
            ucSW2:状态字2
输出参数  : 无
返 回 值  : 无
调用函数  : 无
History     :
1.日    期  : 2014年02月14日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_CbpTRCnfProc(VOS_UINT32 ulErrorCode, VOS_UINT8 ucSW1, VOS_UINT8 ucSW2)
{
    USIMM_STKTERMINALRSP_CNF_STRU     *pstUsimMsg;

    pstUsimMsg = (USIMM_STKTERMINALRSP_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM, sizeof(USIMM_STKTERMINALRSP_CNF_STRU)-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        STK_ERROR_LOG("SI_STK_CbpTRCnfProc: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid   = WUEPS_PID_CSIMA;
    pstUsimMsg->stCmdResult.enMsgName       = USIMM_STKTERMINALRSP_CNF;
    pstUsimMsg->stCmdResult.ulErrorCode     = ulErrorCode;
    pstUsimMsg->stCmdResult.ulSendPara      = VOS_NULL_DWORD;
    pstUsimMsg->ucSW1                       = ucSW1;
    pstUsimMsg->ucSW2                       = ucSW2;

    if (ulErrorCode != USIMM_SW_OK)
    {
        pstUsimMsg->stCmdResult.ulResult    = VOS_ERR;
    }
    else
    {
        pstUsimMsg->stCmdResult.ulResult    = VOS_OK;
    }

    (VOS_VOID)VOS_SendMsg(pstUsimMsg->stCmdResult.ulSenderPid, pstUsimMsg);

    return;
}


/*****************************************************************************
函 数 名  : SI_STK_CurcRptCfg
功能描述  : 设置stin上报状态
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_OK
调用函数  : SI_STKInitRegister
被调函数  :
修订记录  :
1.日    期  : 2013年05月14日
  作    者  : j00168360
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_CurcRptCfg(PS_SI_MSG_STRU *pMsg)
{
    TAF_STK_CURC_RPT_CFG_INFO_MSG_STRU  *pstCurcRptCfg;

    pstCurcRptCfg = (TAF_STK_CURC_RPT_CFG_INFO_MSG_STRU *)pMsg;

    if (TAF_STK_CURC_RPT_CFG_INFO_IND != pMsg->ulMsgName)
    {
        return;
    }

    /* 取出stin所在的bit得到上报配置值 stin在第五个字节bit5，对应总的第29bit 数组中是倒序存储的 */
    g_ucCsinCurcRptCfg = (pstCurcRptCfg->aucCurcRptCfg[4] & 0x20) >> 5;

    return;
}
/* Add by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, end */

/*****************************************************************************
函 数 名  : SI_STK_GasMsgProc
功能描述  : STK模块处理从Gas模块收到的消息
输入参数  : pMsg
输出参数  : 无
返 回 值  : 无
调用函数  : USIMM_TerminalResponseReq
被调函数  : 外部接口
History     :
1.日    期  : 2009年12月21日
  作    者  : m00128685
  修改内容  : Create
2.日    期  : 2011年8月30日
  作    者  : j00168360
  修改内容  : [DTS2011092601656]，terminal response中的command mumber应该与主动命令中的一致
*****************************************************************************/
VOS_VOID SI_STK_GasMsgProc(PS_SI_MSG_STRU *pMsg)
{
    STK_GAS_NMR_INFO_STRU *pNmrMsg;

    VOS_UINT8  aucResp[255] = {0x81, 0x03, 0x01, 0x26, 0x02, 0x02, 0x02, 0x82,
                               0x81, 0x83, 0x01, 0x00, 0x96, 0x10, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    VOS_UINT32 ulDataLen = STK_TERMINAL_RSP_LEN;

    if (VOS_OK != SI_STK_SVLTECheckMsgPID(pMsg, UEPS_PID_GAS))
    {
        return;
    }

    aucResp[2]  = gstUsatCmdDecode.CmdDetail.ucCommandNum;
    aucResp[3]  = gstUsatCmdDecode.CmdDetail.ucCommandType;
    aucResp[4]  = gstUsatCmdDecode.CmdDetail.ucCommandQua;

    switch (pMsg->ulMsgName)
    {
        case STK_AS_NMR_INFO_CNF:           /*网络测量值回复*/

            if (SI_STK_WAITING_CNF  == g_enNMRCmdStatus)
            {
                /* 收到消息回复后先停掉定时器 */
                /*lint -e534*/
                (VOS_VOID)STK_NMR_TIMER_STOP;
                /*lint +e534*/

                g_enNMRCmdStatus = SI_STK_NORMAL_CNF;
            }
            else
            {
                STK_WARNING_LOG("SI_STK_ERRCMsgProc: Recieve NMR Message is not need.\r\n");
                return;
            }

            pNmrMsg = (STK_GAS_NMR_INFO_STRU *)pMsg;

            if(TERMINAL_CURRENTLY_UNABLE_TO_PROCESS_COMMAND == pNmrMsg->ulResult)
            {
                STK_ERROR_LOG("SI_STK_GasMsgProc: TERMINAL_CURRENTLY_UNABLE_TO_PROCESS_COMMAND");

                aucResp[10] = 0x02;
                aucResp[11] = TERMINAL_CURRENTLY_UNABLE_TO_PROCESS_COMMAND;
                aucResp[12] = NO_SPECIFIC_CAUSE_CAN_BE_GIVEN_BY_TERMINAL;

                ulDataLen = STK_TERMINAL_RSP_LEN + 1;
            }
            else
            {
                aucResp[11] = (VOS_UINT8)pNmrMsg->ulResult;

                /*lint -e534*/
                VOS_MemCpy(&aucResp[14], pNmrMsg->aucNmrData, (pNmrMsg->ulNmrLen > 16)?16:pNmrMsg->ulNmrLen);
                /*lint +e534*/

                ulDataLen += 18;/*18测量值Tag+Len+16bytes数据*/

                aucResp[30] = BCCH_CHANNEL_LIST_TAG|STK_DATA_TAG_MASK;

                aucResp[31] = (VOS_UINT8)((pNmrMsg->ulBCCHLen > 223)?223:pNmrMsg->ulBCCHLen);

                /*lint -e534*/
                VOS_MemCpy(&aucResp[32], pNmrMsg->aucBCCHData, aucResp[31]);
                /*lint +e534*/

                ulDataLen += aucResp[31]+2;/*2为BCCH测量值Tag+Len*/
            }

            if (VOS_OK != SI_STK_SendTerminalResponseReqMsg((VOS_UINT8)ulDataLen, aucResp, USIMM_TR_TYPE_BALONG))
            {
                STK_ERROR_LOG("SI_STK_GasMsgProc: SI_STK_SendTerminalResponse Error.");
            }

            break;

            /* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, begin */
            case STK_AS_TA_INFO_CNF:
                SI_STK_TACnfProc(pMsg);

                break;
            /* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, end */

        default:
            STK_WARNING_LOG("SI_STK_GasMsgProc: Receive Unkown Msg");
            break;
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_WasMsgProc
功能描述  : STK模块处理从Gas模块收到的消息
输入参数  : pMsg
输出参数  : 无
返 回 值  : 无
调用函数  : USIMM_TerminalResponseReq
被调函数  : 外部接口
History     :
1.日    期  : 2009年12月21日
  作    者  : m00128685
  修改内容  : Create
2.日    期  : 2011年8月30日
  作    者  : j00168360
  修改内容  : [DTS2011092601656]，terminal response中的command mumber应该与主动命令中的一致
*****************************************************************************/
VOS_VOID SI_STK_UtranMsgProc(PS_SI_MSG_STRU *pMsg)
{
    STK_WAS_NMR_INFO_STRU              *pNmrMsg;
    VOS_UINT8                           aucErrResp[] = {0x81, 0x03, 0x01, 0x26, 0x02, 0x02, 0x02, 0x82,
                                                        0x81, 0x83, 0x02, TERMINAL_CURRENTLY_UNABLE_TO_PROCESS_COMMAND,
                                                        NO_SPECIFIC_CAUSE_CAN_BE_GIVEN_BY_TERMINAL};
    VOS_UINT8                           aucTr[255] = {0x81, 0x03, 0x01, 0x26, 0x02, 0x02, 0x02, 0x82,
                                                      0x81, 0x83, 0x01, 0x00};
    VOS_UINT32                          ulDataLen = STK_TERMINAL_RSP_LEN;
    VOS_UINT8                          *pucRepData = VOS_NULL_PTR;

    switch (pMsg->ulMsgName)
    {
        case STK_AS_NMR_INFO_CNF:           /*网络测量值回复*/

            if (SI_STK_WAITING_CNF  == g_enNMRCmdStatus)
            {
                /* 收到消息回复后先停掉定时器 */
                /*lint -e534*/
                (VOS_VOID)STK_NMR_TIMER_STOP;
                /*lint +e534*/

                g_enNMRCmdStatus = SI_STK_NORMAL_CNF;
            }
            else
            {
                STK_WARNING_LOG("SI_STK_ERRCMsgProc: Recieve NMR Message is not need.\r\n");
                return;
            }

            pNmrMsg = (STK_WAS_NMR_INFO_STRU *)pMsg;

            if (COMMAND_PERFORMED_SUCCESSFULLY != pNmrMsg->ulResult)
            {
                aucErrResp[2]  = gstUsatCmdDecode.CmdDetail.ucCommandNum;
                aucErrResp[3]  = gstUsatCmdDecode.CmdDetail.ucCommandType;
                aucErrResp[4]  = gstUsatCmdDecode.CmdDetail.ucCommandQua;

                pucRepData = aucErrResp;
                ulDataLen  = sizeof(aucErrResp);

                STK_ERROR_LOG("SI_STK_WasMsgProc: TERMINAL_CURRENTLY_UNABLE_TO_PROCESS_COMMAND");

                break;
            }

            aucTr[2]  = gstUsatCmdDecode.CmdDetail.ucCommandNum;
            aucTr[3]  = gstUsatCmdDecode.CmdDetail.ucCommandType;
            aucTr[4]  = gstUsatCmdDecode.CmdDetail.ucCommandQua;

            ulDataLen += pNmrMsg->ulNmrLen+4;/*4个字节:Tag+Len+2个协议规定字节*/

            pucRepData = aucTr;
            pucRepData[12] = NET_MEASUREMENT_RESULTS_TAG|STK_DATA_TAG_MASK;
            pucRepData[13] = (VOS_UINT8)(pNmrMsg->ulNmrLen+2);/*2个协议规定字节*/

            /* 填充协议规定的两个字节 */
            if (STK_WAS_QUERYTYPE_INTRA == pNmrMsg->ulQueryType)
            {
                pucRepData[14] = 0x80;
                pucRepData[15] = 0x00;
            }
            else if(STK_WAS_QUERYTYPE_INTER == pNmrMsg->ulQueryType)
            {
                pucRepData[14] = 0x80;
                pucRepData[15] = 0x11;
            }
            else
            {
                pucRepData[14] = 0x80;
                pucRepData[15] = 0x00;
            }

            /*lint -e534*/
            VOS_MemCpy(&pucRepData[16], pNmrMsg->aucNmrData, pNmrMsg->ulNmrLen);
            /*lint +e534*/

            break;

        default:
            STK_WARNING_LOG("SI_STK_WasMsgProc: Receive Unkown Msg");
            return;
    }

    if (VOS_OK != SI_STK_SendTerminalResponseReqMsg((VOS_UINT8)ulDataLen, pucRepData, USIMM_TR_TYPE_BALONG))
    {
        STK_ERROR_LOG("SI_STK_WasMsgProc1: SI_STK_SendTerminalResponse Error.");
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_ERRCMsgProc
功能描述  : STK模块处理从ERRC模块收到的消息
输入参数  : pMsg
输出参数  : 无
返 回 值  : 无

History     :
1.日    期  : 2013年08月26日
  作    者  : j00168360
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_ERRCMsgProc(PS_SI_MSG_STRU *pMsg)
{
    STK_LAS_NMR_INFO_STRU              *pstNmrMsg;
    VOS_UINT8                           aucErrResp[2] = {TERMINAL_CURRENTLY_UNABLE_TO_PROCESS_COMMAND,
                                                        NO_SPECIFIC_CAUSE_CAN_BE_GIVEN_BY_TERMINAL};
    VOS_UINT8                           aucTr[255] = {0x81, 0x03, 0x01, 0x26, 0x02, 0x02, 0x02, 0x82,
                                                      0x81, 0x83, 0x01, 0x00};
    VOS_UINT32                          ulDataLen = STK_TERMINAL_RSP_LEN;
    VOS_UINT8                          *pucRepData = VOS_NULL_PTR;
    SI_STK_COMMAND_DETAILS_STRU         stCMDInfo;
    VOS_UINT32                          i;
    VOS_UINT8                           ucTmpLen = 0;

    switch (pMsg->ulMsgName)
    {
        case STK_AS_NMR_INFO_CNF:           /*网络测量值回复*/

            if (SI_STK_WAITING_CNF  == g_enNMRCmdStatus)
            {
                /* 收到消息回复后先停掉定时器 */
                /*lint -e534*/
                (VOS_VOID)STK_NMR_TIMER_STOP;
                /*lint +e534*/

                g_enNMRCmdStatus = SI_STK_NORMAL_CNF;
            }
            else
            {
                STK_WARNING_LOG("SI_STK_ERRCMsgProc: Recieve NMR Message is not need.\r\n");
                return;
            }

            pstNmrMsg = (STK_LAS_NMR_INFO_STRU *)pMsg;

            if (COMMAND_PERFORMED_SUCCESSFULLY != pstNmrMsg->ulResult)
            {
                stCMDInfo.ucCommandNum  = gstUsatCmdDecode.CmdDetail.ucCommandNum;
                stCMDInfo.ucCommandType = gstUsatCmdDecode.CmdDetail.ucCommandType;
                stCMDInfo.ucCommandQua  = gstUsatCmdDecode.CmdDetail.ucCommandQua;

                STK_ERROR_LOG("SI_STK_ERRCMsgProc: TERMINAL_CURRENTLY_UNABLE_TO_PROCESS_COMMAND");

                SI_STKSimpleResponseData(&stCMDInfo, sizeof(aucErrResp), aucErrResp);

                break;
            }

            pucRepData = aucTr;
            pucRepData[12] = NET_MEASUREMENT_RESULTS_TAG|STK_DATA_TAG_MASK;

            if (STK_LRRC_QUERYTYPE_INTRA_FREQ == pstNmrMsg->enQueryType)
            {
                pucRepData[13] = 4;
                pucRepData[14] = 0x02;
                pucRepData[15] = 0x00;
                pucRepData[16] = 0x00;
                pucRepData[17] = 0x00;
            }
            else if (STK_LRRC_QUERYTYPE_INTER_FREQ == pstNmrMsg->enQueryType)
            {
                pucRepData[13] = 6;
                pucRepData[14] = ((pstNmrMsg->usSecondCellFreq) & 0xFF00)>>8;
                pucRepData[15] = (pstNmrMsg->usSecondCellFreq) & 0x00FF;
                pucRepData[16] = 0x02;
                pucRepData[17] = 0x00;
                pucRepData[18] = 0x00;
                pucRepData[19] = 0x00;
            }
            else
            {
                pucRepData[13] = 0;
            }

            for (i = 0; i < pstNmrMsg->usCellFreqInfoNum; i++)
            {
                ucTmpLen = STK_TERMINAL_RSP_LEN + pucRepData[13] + 2;

                pucRepData[13] += (VOS_UINT8)(pstNmrMsg->astCellInfo[i].usNmrLen + 2);

                if (pucRepData[13] >= 128)
                {
                    pucRepData[13] -= (VOS_UINT8)(pstNmrMsg->astCellInfo[i].usNmrLen + 2);
                    break;
                }

                /*lint -e534*/
                VOS_MemCpy(&pucRepData[ucTmpLen], pstNmrMsg->astCellInfo[i].aucCellFreq, 2);
                VOS_MemCpy(&pucRepData[ucTmpLen + 2], pstNmrMsg->astCellInfo[i].aucNmrData, pstNmrMsg->astCellInfo[i].usNmrLen);
                /*lint +e534*/
            }

            ulDataLen = STK_TERMINAL_RSP_LEN + pucRepData[13] + 2;

            break;

        default:
            STK_WARNING_LOG("SI_STK_ERRCMsgProc: Receive Unkown Msg");
            return;
    }

    /* 下发terminal response */
    if (VOS_OK != SI_STK_SendTerminalResponseReqMsg((VOS_UINT8)ulDataLen, pucRepData, USIMM_TR_TYPE_BALONG))
    {
        STK_ERROR_LOG("SI_STK_ERRCMsgProc: SI_STK_SendTerminalResponse Error.");
    }

    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
函 数 名  : SI_STK_XsmsMsgProc
功能描述  : STK模块处理从XSMS模块收到的消息
输入参数  : pMsg
输出参数  : 无
返 回 值  : 无

History     :
1.日    期  : 2015年06月18日
  作    者  : C00299064
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_XsmsMsgProc(
    PS_SI_MSG_STRU                      *pMsg)
{
    switch (pMsg->ulMsgName)
    {
        case ID_XSMS_STK_SEND_SMS_CNF:
            SI_STK_XsmsRcvSendSmsCnf(pMsg);
            break;

        case ID_XSMS_STK_SEND_SMS_RSLT_IND:
            SI_STK_XsmsRcvSendSmsRsltInd(pMsg);
            break;

        case ID_XSMS_STK_RCV_SMS_IND:
            /* pp dowanload 流程 */
            SI_STK_XsmsRcvSmsPPDownLoadReq(pMsg);
            break;

        default:
            STK_ERROR_LOG("SI_STK_XsmsMsgProc : WRONG MSG ID");
            break;
    }

    return;
}


/*****************************************************************************
函 数 名  : SI_STK_XsmsRcvSendSmsCnf
功能描述  : STK模块处理从XSMS模块收到的SendSMSCNF消息
输入参数  : pMsg
输出参数  : 无
返 回 值  : 无

History     :
1.日    期  : 2015年06月18日
  作    者  : C00299064
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_XsmsRcvSendSmsCnf(
    PS_SI_MSG_STRU                      *pMsg)
{
    XSMS_STK_SEND_SMS_CNF_STRU             *pstSendCnf;
    VOS_UINT8                               aucRspNet[2] = {NETWORK_CURRENTLY_UNABLE_TO_PROCESS_COMMAND,
                                                            NO_SPECIFIC_CAUSE_CAN_BE_GIVEN_BY_NETWORK};

    pstSendCnf = (XSMS_STK_SEND_SMS_CNF_STRU*)pMsg;

    /* 如果失败直接回复USIM模块，短信发送失败 */
    if (VOS_OK != pstSendCnf->ulRet)
    {
        SI_STK_InitXsmsGlobal();

        SI_STKSimpleResponseData(&gstUsatCmdDecode.CmdDetail, sizeof(aucRspNet), aucRspNet);
    }

    /* 如果成功，不做其他操作，等待短信发送回复 */
    return;
}

/*****************************************************************************
函 数 名  : SI_STK_XsmsRcvSendSmsRsltInd
功能描述  : STK模块处理从XSMS模块收到的SendSmsRsltInd消息
输入参数  : pMsg
输出参数  : 无
返 回 值  : 无

History     :
1.日    期  : 2015年06月18日
  作    者  : C00299064
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_XsmsRcvSendSmsRsltInd(
    PS_SI_MSG_STRU                      *pMsg)
{
    XSMS_STK_SEND_SMS_RSLT_IND_STRU    *pstRsltInd;
    VOS_UINT8                           aucRspNet[2] = {NETWORK_CURRENTLY_UNABLE_TO_PROCESS_COMMAND,
                                                        NO_SPECIFIC_CAUSE_CAN_BE_GIVEN_BY_NETWORK};

    pstRsltInd = (XSMS_STK_SEND_SMS_RSLT_IND_STRU*)pMsg;

    if (VOS_TRUE == pstRsltInd->ulSendSucc)
    {
        /* 如果还有短信要发送，继续发送短信 */
        if (VOS_TRUE == g_ucIsXsmsInBuffFlag)
        {
            SI_STK_SendXsmsReq(g_pstStkSendXsmsBuff, VOS_FALSE);
        }
        else
        {
            /* 給USIMM回复成功 */
            SI_STKSimpleResponse(&gstUsatCmdDecode.CmdDetail, VOS_OK);
        }
    }
    else
    {
        aucRspNet[1] = 0x7f & pstRsltInd->ulCauseCode;

        SI_STKSimpleResponseData(&gstUsatCmdDecode.CmdDetail, sizeof(aucRspNet), aucRspNet);
    }

    SI_STK_InitXsmsGlobal();

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_XsmsRcvSendSmsRsltInd
功能描述  : STK模块处理从XSMS模块收到的pp down load消息
输入参数  : pMsg
输出参数  : 无
返 回 值  : 无

History     :
1.日    期  : 2015年06月18日
  作    者  : C00299064
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_XsmsRcvSmsPPDownLoadReq(
    PS_SI_MSG_STRU                      *pMsg)
{
    XSMS_STK_RCV_SMS_IND_STRU          *pstPPDownLoadInd;
    SI_STK_ENVELOPE_STRU                stDataDownLoad;
    SI_STK_SMS_PP_DOWNLOAD_STRU        *pstPPDown;
    VOS_UINT32                          ulOffset = 0;
    VOS_UINT8                           aucEvent[256]   = {0};
    VOS_UINT32                          ulDataLen       = 0;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulOffSet        = 0;

    (VOS_VOID)VOS_MemSet(&stDataDownLoad, 0, sizeof(SI_STK_ENVELOPE_STRU));

    pstPPDownLoadInd = (XSMS_STK_RCV_SMS_IND_STRU*)pMsg;

    stDataDownLoad.enEnvelopeType   = SI_STK_ENVELOPE_PPDOWN;
    stDataDownLoad.DeviceId.ucSDId  = SI_DEVICE_NETWORK;
    stDataDownLoad.DeviceId.ucDDId  = SI_DEVICE_UICC;

    pstPPDown = &stDataDownLoad.uEnvelope.PPDown;

    pstPPDown->OP_Addr  = 0;
    pstPPDown->OP_TPDU  = 0;
    pstPPDown->OP_XTPDU = VOS_TRUE;

    /* 收到的短信内容保存到全局变量,ENVELOP 完成后回复网侧需要用到 */
    if (VOS_NULL_PTR != g_pstStkRcvXsmsBuff)
    {
        (VOS_VOID)VOS_MemFree(MAPS_STK_PID,g_pstStkRcvXsmsBuff);

        g_pstStkRcvXsmsBuff = VOS_NULL_PTR;
    }

    g_pstStkRcvXsmsBuff  = (TAF_XSMS_MESSAGE_STRU*)VOS_MemAlloc(MAPS_STK_PID,
                                                               DYNAMIC_MEM_PT,
                                                               sizeof(TAF_XSMS_MESSAGE_STRU));

    (VOS_VOID)VOS_MemCpy(g_pstStkRcvXsmsBuff, &pstPPDownLoadInd->st1XSms, sizeof(TAF_XSMS_MESSAGE_STRU));

    /* 填写短信内容 */
    pstPPDown->XTPDU.pucCDMASms = &stDataDownLoad.aucData[ulOffset];
    pstPPDown->XTPDU.ulLen      = pstPPDownLoadInd->ulTpduLen;

    (VOS_VOID)VOS_MemCpy(&stDataDownLoad.aucData[ulOffset],
                pstPPDownLoadInd->aucTpduData,
                pstPPDown->XTPDU.ulLen);


    /* 数据重新编码存放到数组中 */
    ulRslt = SI_STK_EnvelopeData_Code(&stDataDownLoad, &ulDataLen, aucEvent, &ulOffSet);

    if(USIMM_API_SUCCESS != ulRslt)
    {
        STK_ERROR_LOG("SI_STK_XsmsRcvSmsPPDownLoadReq: SI_STK_EnvelopeData_Code Error");

        (VOS_VOID)VOS_MemFree(MAPS_STK_PID,g_pstStkRcvXsmsBuff);

        g_pstStkRcvXsmsBuff = VOS_NULL_PTR;

        return ;
    }


    ulRslt = SI_STK_SendEnvelopeReqMsg(SI_STK_XSMS_ENVELOPE,
                                       USIMM_CDMA_APP,
                                       (VOS_UINT8)ulDataLen,
                                       aucEvent + ulOffSet);

    if(USIMM_API_SUCCESS != ulRslt)
    {
        STK_ERROR_LOG("SI_STK_XsmsRcvSmsPPDownLoadReq: USIMM_EnvelopeReq return Error");
    }

    return ;
}

/*****************************************************************************
函 数 名  : SI_STK_RcvXsmsEnvelopeHandle
功能描述  : 处理信封命令下发回复的消息
输入参数  : pMsg: 消息内容
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
History     :
1.日    期  : 2015年06月25日
  作    者  : c00299064
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_RcvXsmsEnvelopeHandle(USIMM_STKENVELOPE_CNF_STRU *pstMsg)
{
    /* 如果R_UIM 回复90 00 直接回复SMS USER ACK MSG */
    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        SI_STK_SendXsmsPPDownLoadCnf(VOS_OK,
                                     TAF_XSMS_STK_PP_DOWNLOAD_ERR_NONE,
                                     pstMsg->ucDataLen,
                                     pstMsg->aucData);
    }
    else
    {
        if (VOS_NULL != pstMsg->ucDataLen)
        {
            /* 如果R_UIM 回复9E XX 回复SMS USER ACK MSG, 带USER DATA RSP_CODE = OTHER TEMINAL PROBLEM */
            SI_STK_SendXsmsPPDownLoadCnf(VOS_ERR,
                                         TAF_XSMS_STK_PP_DOWNLOAD_ERR_OTHER_PROBLEM,
                                         pstMsg->ucDataLen,
                                         pstMsg->aucData);
        }
        else
        {
            /* 如果R_UIM 回复93 00 回复SMS USER ACK MSG,里面RSP_CODE带 DESTINATION BUSY */
            SI_STK_SendXsmsPPDownLoadCnf(VOS_ERR,
                                         TAF_XSMS_STK_PP_DOWNLOAD_ERR_DEST_BUSY,
                                         0,
                                         VOS_NULL_PTR);
        }
    }

    return;
}


/*****************************************************************************
函 数 名  : SI_STK_SendXsmsPPDownLoadCnf
功能描述  : 处理信封命令下发回复的消息
输入参数  : pMsg: 消息内容
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
History     :
1.日    期  : 2015年06月25日
  作    者  : c00299064
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_SendXsmsPPDownLoadCnf(
    VOS_UINT32                          ulEnvelopeRslt,
    VOS_UINT32                          ulRspCode,
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucData
)
{
    TAF_XSMS_MSG_ID_STRU                stMsgId;
    TAF_XSMS_BD_MSG_USER_DATA_STRU      stUserData;
    VOS_UINT8                           aucEncodedData[256] = {0};
    VOS_UINT8                           ucEncodeDataLen     = 0;

    stMsgId.enMsgType           = TAF_XSMS_BD_MSG_TYPE_USER_ACK ;
    stMsgId.ucIsHeadIndExist    = VOS_FALSE;
    stMsgId.usMsgID             = 0;

    if (VOS_NULL_PTR == g_pstStkRcvXsmsBuff)
    {
        return;
    }

    /* 清除全局变量的BEARER DATA 字段 */
    (VOS_VOID)VOS_MemSet(g_pstStkRcvXsmsBuff->aucBearerData, 0, sizeof(g_pstStkRcvXsmsBuff->aucBearerData));

    g_pstStkRcvXsmsBuff->ulBearerDataLen = 0;

    /* 不需要等待TL_ACK */

    /* 生成MSG ID */
    TAF_XSMS_EncodeMsgID(&stMsgId,
                         &ucEncodeDataLen,
                         aucEncodedData);

    (VOS_VOID)VOS_MemCpy(g_pstStkRcvXsmsBuff->aucBearerData + g_pstStkRcvXsmsBuff->ulBearerDataLen,
                         aucEncodedData,
                         ucEncodeDataLen);

    g_pstStkRcvXsmsBuff->ulBearerDataLen += ucEncodeDataLen;

    if (VOS_OK != ulEnvelopeRslt)
    {
        /* 生成RSP_CODE */
        TAF_XSMS_EncodeUserRspCode((VOS_UINT8)ulRspCode,
                                    &ucEncodeDataLen,
                                    aucEncodedData);

        (VOS_VOID)VOS_MemCpy(g_pstStkRcvXsmsBuff->aucBearerData + g_pstStkRcvXsmsBuff->ulBearerDataLen,
                             aucEncodedData,
                             ucEncodeDataLen);

        g_pstStkRcvXsmsBuff->ulBearerDataLen += ucEncodeDataLen;
    }

    /* 如果成功而且DATA段长度为0，直接回复不带BEAR DATA的短信 */
    if (0 != ulDataLen)
    {
        (VOS_VOID)VOS_MemCpy(stUserData.aucUserData, pucData ,ulDataLen);

        stUserData.enMsgCodeType    = TAF_XSMS_USER_DATA_MSG_ENCODE_OCTET;
        stUserData.ucMsgType        = 0; /* 不存在 */
        stUserData.ucNumFields      = (VOS_UINT8)ulDataLen;

        TAF_XSMS_EncodeUserData(&stUserData,
                                &ucEncodeDataLen,
                                aucEncodedData);

        (VOS_VOID)VOS_MemCpy(g_pstStkRcvXsmsBuff->aucBearerData + g_pstStkRcvXsmsBuff->ulBearerDataLen,
                             aucEncodedData,
                             ucEncodeDataLen);

        g_pstStkRcvXsmsBuff->ulBearerDataLen += ucEncodeDataLen;
    }

    SI_STK_SendXsmsReq(g_pstStkRcvXsmsBuff, VOS_TRUE);

    return;
}
#endif


#if 0
/*****************************************************************************
函 数 名  : SI_STKTrasLVDataToPtr
功能描述  : 将协议栈TAF发送的数据内容转换为数据结构
输入参数  : pstLVData:数据内容
输出参数  : pstPtrData:数据结构
返 回 值  : 无
History     :
1.日    期  : 2015年02月12日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/

VOS_VOID SI_STKTrasLVDataToPtr(SI_STK_ENVELOPEDOWN_STRU *pstLVData, SI_STK_ENVELOPE_STRU *pstPtrData)
{
    SI_STK_FLAGLVDATA_STRU      *pstInput;
    SI_SAT_COMMDATA_STRU        *pstOutput;
    VOS_UINT32                  i;
    SI_SAT_LV_STRU              *pstDesLVData;
    VOS_UINT32                  ulBitValue;
    VOS_UINT32                  ulDecOffset;
    VOS_UINT32                  ulSrcOffet;
    VOS_UINT32                  ulDataOffet;

    pstInput    = (SI_STK_FLAGLVDATA_STRU *)pstLVData;

    pstOutput   = (SI_SAT_COMMDATA_STRU*)pstPtrData;

    pstOutput->ulOpInfo = pstInput->ulReqFlag;

    ulDecOffset = 0;

    ulSrcOffet = 0;

    ulDataOffet = 0;

    for(i=0; i<32; i++)
    {
        pstDesLVData = (SI_SAT_LV_STRU *)&pstOutput->aucDecode[ulDecOffset];

        ulBitValue = SI_STKGetBit32(pstInput->ulReqFlag, i);

        if (0 != ulBitValue)
        {
            VOS_MemCpy(&pstPtrData->aucData[ulDataOffet], &pstInput->aucData[ulSrcOffet+1], pstInput->aucData[ulSrcOffet]);

            pstDesLVData->ulLen  = pstInput->aucData[ulSrcOffet];

            pstDesLVData->pValue = &pstPtrData->aucData[ulDataOffet];

            ulDataOffet += pstInput->aucData[ulSrcOffet] + 1;

            ulSrcOffet += pstDesLVData->ulLen + 1;
        }
        else
        {
            pstDesLVData->pValue        = VOS_NULL_PTR;

            pstDesLVData->ulLen         = VOS_NULL;
        }

        ulDecOffset += sizeof(SI_SAT_LV_STRU);
    }

    return;
}
#endif

/*****************************************************************************
函 数 名  : SI_STK_EnvelopeDownHandle
功能描述  : STK功能ENVELOP下载函数,目前仅处理协议栈TAF的消息
输入参数  : pstReq:消息内容
输出参数  : 无
返 回 值  : VOS_UINT32 函数执行结果
History     :
1.日    期  : 2015年2月12日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STK_EnvelopeDownHandle(SI_STK_ENVELOPEDOWN_REQ_STRU *pstReq)
{
#if (FEATURE_VSIM == FEATURE_ON)
    VOS_BOOL                            bVSimState;
    SI_STK_SMS_PP_DOWNLOAD_STRU         stSmsPpDlData = {0};
    VOS_UINT32                          ulOffset;
#endif
    VOS_UINT32                          ulResult;


    if((SI_STK_ENVELOPE_MENUSEL == pstReq->enEnvelopeType)
        ||(SI_STK_PROCMD == pstReq->enEnvelopeType))
    {
        STK_ERROR_LOG("SI_STK_EnvelopeDownload: The Input EnvelopeType is Error");

        return VOS_ERR;
    }

#if (FEATURE_VSIM == FEATURE_ON)
    bVSimState = USIMM_VsimIsActive();

    if ((SI_STK_ENVELOPE_PPDOWN == pstReq->enEnvelopeType)
     && (VOS_TRUE == bVSimState))
    {
        ulOffset = SI_STKFindTag(SI_STK_ENVELOPE_PPDOWN,
                                  pstReq->stEnvelopeData.aucData,
                                  sizeof(pstReq->stEnvelopeData.aucData),
                                  1);

        if (SI_TAGNOTFOUND == ulOffset)
        {
            STK_ERROR_LOG("SI_STK_EnvelopeDownload: The Input Data is Error");

            return VOS_ERR;
        }

        ulOffset = SI_STKFindTag(SMS_TPDU_TAG,
                                  &pstReq->stEnvelopeData.aucData[ulOffset+1],
                                  pstReq->stEnvelopeData.aucData[ulOffset],
                                  1);

        if (SI_TAGNOTFOUND == ulOffset)
        {
            STK_ERROR_LOG("SI_STK_EnvelopeDownload: The TPDU Data is Error");

            return VOS_ERR;
        }

        stSmsPpDlData.OP_TPDU       = 1;
        stSmsPpDlData.TPDU.ulLen    = pstReq->stEnvelopeData.aucData[ulOffset];
        stSmsPpDlData.TPDU.pucTPDU  = &pstReq->stEnvelopeData.aucData[ulOffset+1];

        SI_STK_VsimSmsPpDownloadProc(pstReq->stMsgHeader.ulSenderPid,
                                        pstReq->stMsgHeader.ulSendPara,
                                        &stSmsPpDlData);

        return VOS_OK;
    }
#endif

    ulResult = SI_STK_SendEnvelopeReqMsg(pstReq->stMsgHeader.ulSendPara,
                                         USIMM_GUTL_APP,
                                         (VOS_UINT8)pstReq->stEnvelopeData.ulDataLen,
                                         pstReq->stEnvelopeData.aucData);

    if(USIMM_API_SUCCESS != ulResult)   /*如果错误，不返回消息让tAF超时返回*/
    {
        STK_ERROR_LOG("SI_STK_TAFEnvelopeDown: USIMM_EnvelopeReq return Error");
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  : SI_STK_ProvideLocalInfoTimerOutProc
功能描述  : STK模块NMR定时器超时消息处理函数
输入参数  : 无
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2013年08月26日
  作    者  : j00168360
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_ProvideLocalInfoTimerOutProc(VOS_VOID)
{
    VOS_UINT8                           aucErrResp[] = {TERMINAL_CURRENTLY_UNABLE_TO_PROCESS_COMMAND,
                                                        NO_SPECIFIC_CAUSE_CAN_BE_GIVEN_BY_TERMINAL};
    SI_STK_COMMAND_DETAILS_STRU         stCMDInfo;

    if(SI_STK_NOCMDDATA == gstUsatCmdDecode.SatType)    /*当前主动命令内容无缓冲*/
    {
        STK_WARNING_LOG("SI_STK_ProactiveCmdTimeOutProc: There is Any STK command");

        return;
    }

    stCMDInfo.ucCommandNum  = gstUsatCmdDecode.CmdDetail.ucCommandNum;
    stCMDInfo.ucCommandType = gstUsatCmdDecode.CmdDetail.ucCommandType;
    stCMDInfo.ucCommandQua  = gstUsatCmdDecode.CmdDetail.ucCommandQua;

    /* 下发terminal response */
    SI_STKSimpleResponseData(&stCMDInfo, sizeof(aucErrResp), aucErrResp);

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_TimeOutMsgProc
功能描述  : STK模块定时器超时消息处理函数
输入参数  : 无
输出参数  : 无
返 回 值  : SI_UINT32 函数执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月09日
  作    者  : H59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_TimeOutMsgProc(REL_TIMER_MSG *pRelTimerMsg)
{
    /*lint -e813*/
    SI_STK_EVENT_INFO_STRU  stSTKEvent;
    VOS_UINT8               aucRspNet[2] = {NETWORK_CURRENTLY_UNABLE_TO_PROCESS_COMMAND,USER_BUSY};

    /* IMSI切换过程中，不处理定时器超时消息 */
    if (SI_STK_IMSICHG_NULL != gstSTKIMSIChgCtrl.enIMSIChgState)
    {
        STK_WARNING_LOG("SI_STK_TimeOutMsgProc: The STK Command Duaring the IMSI Change");
        return;
    }

    if (STK_PROTECT_TIMER_NAME == pRelTimerMsg->ulName)
    {
        STK_WARNING_LOG("SI_STK_TimeOutMsgProc: The STK Command Protect Timer End");
        /*lint -e534*/
        (VOS_VOID)STK_IND_TIMER_STOP;
        /*lint +e534*/

        SI_STK_ProactiveCmdTimeOutProc();
    }
    /* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, begin */
    else if (STK_GETTA_TIMER_NAME == pRelTimerMsg->ulName)
    {
        if (SI_STK_WAITING_CNF != g_enTACmdStatus)
        {
            return;
        }

        STK_WARNING_LOG("SI_STK_TimeOutMsgProc: The STK Command Get TA  Timer End");

        g_enTACmdStatus = SI_STK_TIMEOUT_CNF;

        SI_STK_ProvideLocalInfoTimerOutProc();
    }
    /* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, end */
    else if (STK_IND_TIMER_NAME == pRelTimerMsg->ulName)
    {
        STK_WARNING_LOG("SI_STK_TimeOutMsgProc: The STK Command IND Timer End");

        SI_STK_CmdIndTimeOutProc();
    }
    else if (STK_REFRESH_TIMER_NAME == pRelTimerMsg->ulName)
    {
        STK_WARNING_LOG("SI_STK_TimeOutMsgProc: The STK Refresh Cnf Timer End");
        stSTKEvent.STKErrorNo                         = VOS_OK;
        stSTKEvent.STKCBEvent                         = SI_STK_CMD_IND_EVENT;
        stSTKEvent.STKCmdStru.CmdDetail.ucCommandType = gucSTKRefreshQua;
        stSTKEvent.STKCmdStru.SatType                 = SI_STK_REFRESH;

        SI_STKCallBack_BroadCast(&stSTKEvent);

        if(VOS_OK != STK_REFRESH_CNF_TIMER_START(5000))
        {
            STK_WARNING_LOG("SI_STK_TimeOutMsgProc: STK_REFRESH_CNF_TIMER_START fail");
        }
    }
    else if (STK_SETUP_CALL_DURATION_TIMER_NAME == pRelTimerMsg->ulName)
    {
        SI_STKSimpleResponseData(&gstUsatCmdDecode.CmdDetail, sizeof(aucRspNet), aucRspNet);

        /*lint -e534*/
        SI_STK_DisconnectStkCall();
        /*lint +e534*/

        /* dtmf资源清空，状态机重置 */
        STK_SetCallCleanGobal();
    }
    else if (STK_DTMF_PAUSE_TIMER_NAME == pRelTimerMsg->ulName)
    {
        /*lint -e534*/
        SI_STK_SendStartDtmfMsg((VOS_CHAR)g_stSTKDtmfData.acDtfm[g_stSTKDtmfData.ulCurDtmfPtr++],
                                 g_stSTKDtmfData.ucOpId,
                                 g_stSTKDtmfData.ucCallId);
        /*lint +e534*/
    }
    else if(STK_NMR_TIMER_NAME == pRelTimerMsg->ulName)
    {
        if (SI_STK_WAITING_CNF != g_enNMRCmdStatus)
        {
            return;
        }

        STK_WARNING_LOG("SI_STK_TimeOutMsgProc: The STK Command Get NMR Timer End");

        g_enNMRCmdStatus = SI_STK_TIMEOUT_CNF;

        SI_STK_ProvideLocalInfoTimerOutProc();
    }
    else if ((STK_LOCIEVENT_TIMER_NAME == pRelTimerMsg->ulName)||(STK_ACCEVENT_TIMER_NAME == pRelTimerMsg->ulName))
    {
        SI_STK_ResendTimerMsgHandle(pRelTimerMsg);
    }
    else
    {
        STK_NORMAL_LOG("SI_STK_TimeOutMsgProc: The STK Command Timer Management Timer End");

        SI_STK_TimerManagement(pRelTimerMsg->ulName);
    }
    /*lint +e813*/

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_ProactiveCmdProc
功能描述  : STK模块处理从USIM模块收到主动命令消息的处理
输入参数  : pMsg:USIM模块收到主动命令消息
输出参数  : 无
返 回 值  : VOS_VOID
History     :
1.日    期  : 2014年01月09日
  作    者  : H59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_ProactiveCmdProc(PS_SI_MSG_STRU *pMsg)
{
    USIMM_STKDATA_IND_STRU             *pstCmdMsg;

    if (VOS_TRUE == SI_STK_IsCbpMainCtrlProactiveCmd())
    {
        pstCmdMsg = (USIMM_STKDATA_IND_STRU *)pMsg;

        SI_STK_SndProactiveCmd2CBP(pstCmdMsg->usLen, pstCmdMsg->aucContent);
    }
    else
    {
        SI_STKCommandIndHandle((USIMM_STKDATA_IND_STRU *)pMsg);   /*调用解码函数进行处理*/
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_UsimmMsgProc
功能描述  : STK模块处理从USIM模块收到的消息
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_VOID
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月09日
  作    者  : H59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_UsimmMsgProc(PS_SI_MSG_STRU *pMsg)
{
    switch (pMsg->ulMsgName)
    {
        /*当前上报主动命令*/
        case USIMM_STKDATA_IND:
            SI_STK_ProactiveCmdProc(pMsg);
            break;

        /*当前上报的refresh命令执行结果*/
        case USIMM_STKREFRESH_CNF:
            SI_STK_RefreshCnfMsgProc(pMsg);
            break;

        case USIMM_STKTERMINALRSP_CNF:
            SI_STK_TerminalResponseCnfProc(pMsg);
            break;

        case USIMM_STKENVELOPE_CNF:          /*收到信封命令的返回*/
            SI_STK_EnvelopeCnfMsgProc(pMsg);
            break;

        default:
            STK_WARNING_LOG("SI_STK_UsimmMsgProc: Receive Unkown Msg");
            break;
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_PIHMsgProc
功能描述  : STK模块处理从PIH模块收到的消息
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月13日
  作    者  : m00128685
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_PIHMsgProc(PS_SI_MSG_STRU *pMsg)
{
    switch (pMsg->ulMsgName)
    {
        /* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, begin */
        case USIMM_CARDSTATUS_IND:
            SI_STK_CardStatusMsgProc(pMsg);
            break;
        /* Modified by w00184875 for V7R1C51 STK与AP对接, 2012-05-07, end */

        default:
            STK_ERROR_LOG("SI_STK_PIHMsgProc:Unknown Msg Name");
            break;
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_StkMsgProc
功能描述  : STK模块处理从STK模块收到的消息
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月13日
  作    者  : m00128685
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_StkMsgProc(SI_STK_REQ_STRU *pMsg)
{
    switch(pMsg->MsgName)
    {
        case SI_STK_GETMAINMNUE:    /*获取主菜单*/
            SI_STK_GetMainMenuReqProc(pMsg);
            break;

        case SI_STK_QUERYCOMMAND:   /*查询当前缓冲命令*/
            SI_STK_QuerySTKCommandReqProc(pMsg);
            break;

        case SI_STK_TRDOWN:
            SI_STK_TRDownReqProc(pMsg);
            break;

        case SI_STK_MENUSELECTION:
            SI_STK_MenuSelectionProc(pMsg);
            break;

        case SI_STK_SIMPLEDOWN:
            SI_STK_SimpleDownReqProc(pMsg);
            break;

        case SI_STK_GETCOMMAND:     /*获取当前命令内容*/
            SI_STK_GetSTKCommandReqProc(pMsg);
            break;

        case SI_STK_IMSICHG:
            SI_STK_IMSIChgBegin(pMsg);
            break;

        case SI_STK_SETUPCALL_CONFIRM:
            /* 调用函数处理用户对setup call的确认结果*/
            SI_STK_SetUpCallAllow(*(VOS_UINT32*)(pMsg->Data));
            break;

        case SI_STK_ENVELOPEDWON_REQ:
            /*lint -e534*/
            SI_STK_EnvelopeDownHandle((SI_STK_ENVELOPEDOWN_REQ_STRU*)pMsg);
            /*lint +e534*/
            break;

        case SI_STK_VIA_TRDOWN:
            SI_STK_CbpTRDataReqProc(pMsg);
            break;

        default:
            STK_ERROR_LOG("SI_STK_StkMsgProc:Unknown Msg Name");
            break;
    }
}

/*****************************************************************************
函 数 名  : SI_STK_MmMsgProc
功能描述  : STK处理MM模块消息的处理函数
输入参数  : pMsg:消息结构
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2013年07月17日
  作    者  : H59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_MmMsgProc(NAS_STK_EVENT_MSG_HEADER_STRU *pMsg)
{
    if (VOS_OK != SI_STK_SVLTECheckMsgPID((PS_SI_MSG_STRU *)pMsg, WUEPS_PID_MM))
    {
        return;
    }

    /* MM的消息目前只处理NETWORK REJECTION事件 */
    switch (pMsg->ulMsgName)
    {
        case ID_NAS_STK_NETWORK_REJECTION_EVENT:
            SI_STK_NetworkRejectionEventDownload((NAS_STK_NETWORK_REJECTION_EVENT_STRU *)pMsg);
            break;

        default:
            STK_WARNING_LOG("SI_STK_MmMsgProc: Unknow Msg Name");
            break;
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_GmmMsgProc
功能描述  : STK处理GMM模块消息的处理函数
输入参数  : pMsg:消息结构
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2013年07月17日
  作    者  : H59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_GmmMsgProc(NAS_STK_EVENT_MSG_HEADER_STRU *pMsg)
{
    if (VOS_OK != SI_STK_SVLTECheckCsDomainAndMsgPID((PS_SI_MSG_STRU *)pMsg, WUEPS_PID_GMM))
    {
        return;
    }

    /* GMM的消息目前只处理NETWORK REJECTION事件 */
    switch (pMsg->ulMsgName)
    {
        case ID_NAS_STK_NETWORK_REJECTION_EVENT:
            SI_STK_NetworkRejectionEventDownload((NAS_STK_NETWORK_REJECTION_EVENT_STRU *)pMsg);
            break;

        default:
            STK_WARNING_LOG("SI_STK_GmmMsgProc: Unknow Msg Name");
            break;
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_MmaMsgProc
功能描述  : STK处理MMA模块消息的处理函数
输入参数  : pMsg:消息结构
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2013年07月17日
  作    者  : H59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_MmaMsgProc(NAS_STK_EVENT_MSG_HEADER_STRU *pstMsg)
{
    NAS_STK_LOCATION_INFO_IND_STRU     *pstLociInfo;

    if (VOS_OK != SI_STK_SVLTECheckMsgPID((PS_SI_MSG_STRU *)pstMsg, WUEPS_PID_MMA))
    {
        return;
    }

    /* MMA的消息目前只处理LOCATION STATUS/ACC TECH CHANGE事件和SERVICE STATUS IND和SYS_INFO_IND消息 */
    switch (pstMsg->ulMsgName)
    {
        case ID_NAS_STK_LOC_STATUS_EVENT:
            /* 先更新全局变量中的内容再做下载 */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            g_ucIsRatCdma       = VOS_FALSE;
#endif
            SI_STK_UpdateLocationInfo(&((NAS_STK_LOC_STATUS_EVENT_STRU *)pstMsg)->stLocStatusEvent);
            SI_STK_LocationStatusEventDownload();
            break;

        case ID_NAS_STK_LOCATION_INFO_IND:
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            g_ucIsRatCdma       = VOS_FALSE;
#endif
            pstLociInfo= (NAS_STK_LOCATION_INFO_IND_STRU *)pstMsg;
            SI_STK_LociInfoIndMsgProc(pstLociInfo);
            break;

        case ID_MMA_STK_1X_SERVICE_INFO_IND:
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            SI_STK_ServiceInfoInd((MMA_STK_SERVICE_INFO_IND_STRU *)pstMsg);
            SI_STK_CdmaLocStatusEventDownload();
#endif
            break;

        default:
            STK_WARNING_LOG("SI_STK_MmaMsgProc: Unknow Msg Name");
            break;
    }

    return;
}


/*****************************************************************************
函 数 名  : SI_STK_MmcMsgProc
功能描述  : STK处理MMC模块消息的处理函数
输入参数  : pMsg:消息结构
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2013年07月17日
  作    者  : H59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_MmcMsgProc(NAS_STK_EVENT_MSG_HEADER_STRU *pMsg)
{
    if(VOS_OK != SI_STK_SVLTECheckMsgPID((PS_SI_MSG_STRU *)pMsg, WUEPS_PID_MMC))
    {
        return;
    }

    /* MMC的消息目前只处理NETWORK SEARCH MODE CHANGE事件 */
    switch (pMsg->ulMsgName)
    {
        case ID_NAS_STK_NET_SRCH_MODE_CHG_EVENT:
            STK_UpdateSearchMode(((NAS_STK_SRCHMODE_CHG_EVENT_STRU *)pMsg)->stSrchModeChgEvent.ucSrchMode);
            SI_STK_NetworkSearchModeChangeEventDownload();
            break;

        default:
            STK_WARNING_LOG("SI_STK_MmcMsgProc: Unknow Msg Name");
            break;
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_LMMMsgProc
功能描述  : STK处理MMC模块消息的处理函数
输入参数  : pMsg:消息结构
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2013年08月20日
  作    者  : j00168360
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_LMMMsgProc(LNAS_STK_NETWORK_REJECTION_EVENT_STRU *pstMsg)
{
    SI_STK_NETWORK_REJ_EVENT_STRU           stEvent;
    VOS_UINT8                               aucInfo[20];

    if (VOS_OK != SI_STK_SVLTECheckMsgPID((PS_SI_MSG_STRU *)pstMsg, PS_PID_MM))
    {
        return;
    }

    /* 目前只处理NETWORK REJECTION事件 */
    switch (pstMsg->ulMsgName)
    {
        case ID_LNAS_STK_NETWORK_REJECTION_EVENT:
                /* 当前不需要下载NETWORK REJECTION事件 */
            if (VOS_FALSE == g_stSTKEventState.OP_NetRej)
            {
                STK_WARNING_LOG("SI_STK_NetworkRejectionEventDownload: The Event is not Need Download");
                return;
            }

            /*lint -e534*/
            VOS_MemSet(&stEvent, 0, sizeof(SI_STK_NETWORK_REJ_EVENT_STRU));
            /*lint +e534*/

            stEvent.OP_AccTech                  = VOS_TRUE;
            stEvent.stAccTech.ucTech            = STK_ACCESS_TECH_EUTRAN;

            /* 设置拒绝原因 */
            stEvent.OP_RejCauseCode             = VOS_TRUE;
            stEvent.stRejCauseCode.ucCause      = pstMsg->stNetworkRejectionEvent.ucCauseCode;

            /* 设置UPDATE ATTACH TYPE */
            stEvent.OP_UpdateAttachType         = VOS_TRUE;
            stEvent.stUpdateAttachType.ucTpye   = pstMsg->stNetworkRejectionEvent.enUpdateAttachType;

            aucInfo[0] = pstMsg->stNetworkRejectionEvent.stTaiInfo.stCurPlmnID.aucPlmnId[0];
            aucInfo[1] = pstMsg->stNetworkRejectionEvent.stTaiInfo.stCurPlmnID.aucPlmnId[1];
            aucInfo[2] = pstMsg->stNetworkRejectionEvent.stTaiInfo.stCurPlmnID.aucPlmnId[2];

            /* 转换TAC的格式 */
            aucInfo[3] = pstMsg->stNetworkRejectionEvent.stTaiInfo.stTac.ucTac;
            aucInfo[4] = pstMsg->stNetworkRejectionEvent.stTaiInfo.stTac.ucTacCnt;

            stEvent.OP_TauInfo = VOS_TRUE;
            stEvent.stTauInfo.pucTauInfo= aucInfo;
            stEvent.stTauInfo.ulLen     = 0x05;

            SI_STK_EventDownload(&stEvent, sizeof(SI_STK_NETWORK_REJ_EVENT_STRU), SI_STK_EVENT_NETWORK_REJECTION, SI_STK_DEV_NETWORK);

            break;

        default:
            STK_WARNING_LOG("SI_STK_MmcMsgProc: Unknow Msg Name");
            break;
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_SIM_PidMsgProc
功能描述  : STK PID注册的消息处理函数
输入参数  : pMsg:消息结构
输出参数  : 无
返 回 值  : 无
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_PidMsgProc(PS_SI_MSG_STRU *pMsg)
{
    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_2,
                        pMsg->ulSenderPid,
                        MAPS_STK_PID,
                        pMsg->ulMsgName);

    switch(pMsg->ulSenderPid)
    {
        case VOS_PID_TIMER:     /*定时器消息*/
            STK_WARNING_LOG("SI_STK_PidMsgProc: The STK Timer TimeOut");
            SI_STK_TimeOutMsgProc((REL_TIMER_MSG *)pMsg);
            break;

        case WUEPS_PID_USIM:    /*来自USIM模块的消息*/
            SI_STK_UsimmMsgProc(pMsg);
            break;

        case WUEPS_PID_AT:      /*来自AT外部的请求*/
        case MAPS_STK_PID:      /*来自内部Nas的请求*/
            SI_STK_StkMsgProc((SI_STK_REQ_STRU*)pMsg);
            break;

        case I0_UEPS_PID_GAS:
        case I1_UEPS_PID_GAS:
        case I2_UEPS_PID_GAS:
            SI_STK_GasMsgProc(pMsg);
            break;

        case WUEPS_PID_WRR:
        case TPS_PID_RRC:
            SI_STK_UtranMsgProc(pMsg);
            break;

        case I0_WUEPS_PID_TAF:  /*TAF返回的特殊命令处理结果*/
        case I1_WUEPS_PID_TAF:
        case I2_WUEPS_PID_TAF:
            SI_STK_TAFMsgProc(pMsg);
            break;

        case UEPS_PID_MTA:      /* 控制主动命令上报 */
            SI_STK_CurcRptCfg(pMsg);
            break;

        case I0_WUEPS_PID_MM:
        case I1_WUEPS_PID_MM:
        case I2_WUEPS_PID_MM:
            SI_STK_MmMsgProc((NAS_STK_EVENT_MSG_HEADER_STRU *)pMsg);
            break;

        case I0_WUEPS_PID_GMM:
        case I1_WUEPS_PID_GMM:
        case I2_WUEPS_PID_GMM:
            SI_STK_GmmMsgProc((NAS_STK_EVENT_MSG_HEADER_STRU *)pMsg);
            break;

        case I0_WUEPS_PID_MMA:
        case I1_WUEPS_PID_MMA:
        case I2_WUEPS_PID_MMA:
            SI_STK_MmaMsgProc((NAS_STK_EVENT_MSG_HEADER_STRU *)pMsg);
            break;

        case I0_WUEPS_PID_MMC:
        case I1_WUEPS_PID_MMC:
        case I2_WUEPS_PID_MMC:
            SI_STK_MmcMsgProc((NAS_STK_EVENT_MSG_HEADER_STRU *)pMsg);
            break;

        case MAPS_PIH_PID:
            SI_STK_PIHMsgProc(pMsg);
            break;

        case PS_PID_MM:
            SI_STK_LMMMsgProc((LNAS_STK_NETWORK_REJECTION_EVENT_STRU *)pMsg);
            break;

        case PS_PID_ERRC:
            SI_STK_ERRCMsgProc(pMsg);
            break;

        case UEPS_PID_XSMS:
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            SI_STK_XsmsMsgProc(pMsg);
#endif
            break;

        default:
            STK_ERROR_LOG("SI_STK_PidMsgProc:Unknown PID");
            break;
    }

    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_2);

    /*定制需求处理*/
    SI_STK_IMSIChgProc(pMsg);

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_CallBack_BroadCast
功能描述  : 回调处理函数，给所有注册的APP/AT上报电话本事件
输入参数  : 无
输出参数  : 无
返 回 值  : SI_UINT32 函数执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STKEventCallback(SI_STK_EVENT_INFO_STRU *pEvent)
{
    pEvent->ClientId = MN_GetRealClientId(pEvent->ClientId, MAPS_STK_PID);

    At_STKCallBackFunc(pEvent);

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_CallBack_BroadCast
功能描述  : 回调处理函数，给所有注册的APP/AT上报电话本事件
输入参数  : 无
输出参数  : 无
返 回 值  : SI_UINT32 函数执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STKCallBack_BroadCast(SI_STK_EVENT_INFO_STRU *pEvent)
{
    pEvent->ClientId = MN_CLIENT_ALL;/*特殊的值*/

    pEvent->ClientId = MN_GetRealClientId(pEvent->ClientId, MAPS_STK_PID);

    if(VOS_FALSE == g_ucCsinCurcRptCfg)
    {
        return;
    }

    At_STKCallBackFunc(pEvent);

    return ;
}

/*****************************************************************************
函 数 名  : SI_PBCallback
功能描述  : 回调处理函数
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_UINT32，表示函数执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STKCallback(SI_STK_EVENT_INFO_STRU *pEvent)
{
    if (SI_STK_IMSICHG_NULL != gstSTKIMSIChgCtrl.enIMSIChgState)
    {
        return VOS_OK;
    }

    /*lint -e534*/
    VOS_MemSet(&gstSTKCtrlStru, 0, sizeof(gstSTKCtrlStru));/*系统运行锁解锁*/
    /*lint +e534*/

    return SI_STKEventCallback(pEvent);
}

/*****************************************************************************
函 数 名  : SI_PBCallback
功能描述  : 回调处理函数
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_UINT32，表示函数执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STKDataIndCallback(SI_STK_DATA_INFO_STRU *pCmdData)
{
    /*lint -e813*/
    SI_STK_EVENT_INFO_STRU stSTKEvent;

    stSTKEvent.STKErrorNo = VOS_OK;/*调用此函数就认为当前处理无问题*/

    stSTKEvent.STKCBEvent = SI_STK_CMD_IND_EVENT;/*当前事件为命令主动上报*/

    /*lint -e534*/
    VOS_MemCpy(&stSTKEvent.STKCmdStru, pCmdData, sizeof(SI_STK_DATA_INFO_STRU));
    /*lint +e534*/

    SI_STKCallBack_BroadCast(&stSTKEvent);
    /*lint +e813*/
    return SI_STK_OK_WAITRP;
}


/*****************************************************************************
函 数 名  : WuepsSTKPidInit
功能描述  : STK功能初始化时初始化函数，仅在需要特殊处理时才调用
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_OK
调用函数  : SI_STKInitRegister
被调函数  :
修订记录  :
1.日    期  : 2009年07月02日
  作    者  : H59254
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 WuepsSTKPidInit(enum VOS_INIT_PHASE_DEFINE InitPhrase)
{
    switch( InitPhrase )
    {
        case VOS_IP_LOAD_CONFIG:
            STK_InitGobal();
            break;

        case VOS_IP_RESTART:
            /*lint -e534*/
            PIH_RegUsimCardStatusIndMsg(MAPS_STK_PID);
            /*lint +e534*/
            break;

        default:
            break;
    }

    return VOS_OK;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



