
/*lint -save -e537 -e958 -e775*/
#include "osm.h"
#include "gen_msg.h"
#include "at_lte_common.h"
#include "gen_msg.h"
#include "ATCmdProc.h"

/* AT^FCALIIP2S=<dl_channel_num>[,<dl_channel_list>] 处理函数，启动IP2校准流程 */
VOS_UINT32 atSetFCALIIP2SPara(VOS_UINT8 ucClientId)
{
    FTM_SET_FCALIIP2S_REQ_STRU stSetCaliIp2SReq = {0};

    (VOS_VOID)vos_printf("\r\natSetFCALIIP2SPara: %d, %s\r\n", gastAtParaList[0].ulParaValue, gastAtParaList[1].aucPara);

    /* 参数检查 */
    if((AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
		|| (2 != gucAtParaIndex)
		|| (0 == gastAtParaList[0].usParaLen)
		|| (0 == gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 获取参数 */
    stSetCaliIp2SReq.usChanNum = (VOS_UINT16)(gastAtParaList[0].ulParaValue);

    if((stSetCaliIp2SReq.usChanNum<=0) || (stSetCaliIp2SReq.usChanNum > FTM_CALIIP2_MAX_CHAN_NUM))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(initParaListU16(&gastAtParaList[1], stSetCaliIp2SReq.usChanNum, stSetCaliIp2SReq.usChan) != ERR_MSP_SUCCESS)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 发送消息给命令处理模块 */
    if(atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_FCALIIP2S_REQ,
         ucClientId ,  (VOS_VOID*)(&stSetCaliIp2SReq), sizeof(stSetCaliIp2SReq)) != AT_SUCCESS)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FCALIIP2S_SET;
    return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */
}

/* AT^FCALIIP2S=<dl_channel_num>[,<dl_channel_list>] 返回处理函数 */
VOS_UINT32 atSetFCALIIP2SParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    OS_MSG_STRU* pEvent = (OS_MSG_STRU*)((MsgBlock*)pMsgBlock)->aucValue;
    FTM_SET_FCALIIP2S_CNF_STRU* pFCaliIP2SCnf = (FTM_SET_FCALIIP2S_CNF_STRU*)pEvent->ulParam1;

    (VOS_VOID)vos_printf("\r\natSetFCALIIP2SParaCnfProc, error code: %d\r\n", pFCaliIP2SCnf->ulErrCode);

    CmdErrProc(ucClientId, pFCaliIP2SCnf->ulErrCode, 0, NULL);
    return AT_FW_CLIENT_STATUS_READY;
}

/* AT^FCALIIPS? 处理函数 */
VOS_UINT32 atQryFCALIIP2SPara(VOS_UINT8 ucClientId)
{
    FTM_RD_NOPRARA_REQ_STRU stQryCaliIp2SReq = {0};

    (VOS_VOID)vos_printf("\r\natQryFCALIIP2SPara\r\n");

    if(atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_FCALIIP2S_REQ, ucClientId,
        (VOS_VOID*)(&stQryCaliIp2SReq), sizeof(stQryCaliIp2SReq)) != AT_SUCCESS)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FCALIIP2S_READ;
    return AT_WAIT_ASYNC_RETURN;
}

/* AT^FCALIIPSS? 返回处理函数 */
VOS_UINT32 atQryFCALIIP2SParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    VOS_UINT32 i = 0;
    VOS_UINT16 usLength = 0;
    OS_MSG_STRU* pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	/* coverity[tainted_data_downcast] */
    FTM_RD_FCALIIP2S_CNF_STRU* pFCaliIp2SCnf = (FTM_RD_FCALIIP2S_CNF_STRU*)pEvent->ulParam1;

    (VOS_VOID)vos_printf("\r\natQryFCALIIP2SParaCnfProc\r\n");

    if(NULL == pFCaliIp2SCnf)
    {
        return ERR_MSP_FAILURE;
    }

    if(ERR_MSP_SUCCESS != pFCaliIp2SCnf->ulErrCode)
    {
       CmdErrProc(ucClientId, pFCaliIp2SCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
       return ERR_MSP_FAILURE;
    }

	/* coverity[lower_bounds] */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"^FCALIIP2S:%u,%u", pFCaliIp2SCnf->usStatus, pFCaliIp2SCnf->usChanNum);

    /* channel number */
	/* coverity[tainted_data] */
    for(i=0; i<pFCaliIp2SCnf->usChanNum; i++)
    {
        if(0 == i)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
              "%s^FCALIIP2S:CHAN:%u",gaucAtCrLf, pFCaliIp2SCnf->usChan[i]);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                " %u", pFCaliIp2SCnf->usChan[i]);
        }
    }

    /* main I path optimum code with diversity path off */
    for(i=0; i<pFCaliIp2SCnf->usChanNum; i++)
    {
        if(0 == i)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
              "%s^FCALIIP2S:Main_I_DivOff:%u", gaucAtCrLf, pFCaliIp2SCnf->usMain_I_DivOff[i]);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                " %u", pFCaliIp2SCnf->usMain_I_DivOff[i]);
        }
    }

    /* main Q path optimum code with diversity path off */
    for(i=0; i<pFCaliIp2SCnf->usChanNum; i++)
    {
        if(0 == i)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
              "%s^FCALIIP2S:Main_Q_DivOff:%u", gaucAtCrLf, pFCaliIp2SCnf->usMain_Q_DivOff[i]);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                " %u", pFCaliIp2SCnf->usMain_Q_DivOff[i]);
        }
    }

    /* main I path optimum code with diversity path on */
    for(i=0; i<pFCaliIp2SCnf->usChanNum; i++)
    {
        if(0 == i)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
              "%s^FCALIIP2S:Main_I_DivOn:%u", gaucAtCrLf, pFCaliIp2SCnf->usMain_I_DivOn[i]);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                " %u", pFCaliIp2SCnf->usMain_I_DivOn[i]);
        }
    }

    /* main Q path optimum code with diversity path on */
    for(i=0; i<pFCaliIp2SCnf->usChanNum; i++)
    {
        if(0 == i)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
              "%s^FCALIIP2S:Main_Q_DivOn:%u", gaucAtCrLf, pFCaliIp2SCnf->usMain_Q_DivOn[i]);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                " %u", pFCaliIp2SCnf->usMain_Q_DivOn[i]);
        }
    }

    /* diversity I path code */
    for(i=0; i<pFCaliIp2SCnf->usChanNum; i++)
    {
        if(0 == i)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
              "%s^FCALIIP2S:Div_I:%u", gaucAtCrLf, pFCaliIp2SCnf->usDiv_I[i]);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                " %u", pFCaliIp2SCnf->usDiv_I[i]);
        }
    }

    /* diversity Q path code */
    for(i=0; i<pFCaliIp2SCnf->usChanNum; i++)
    {
        if(0 == i)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
              "%s^FCALIIP2S:Div_Q:%u", gaucAtCrLf, pFCaliIp2SCnf->usDiv_Q[i]);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                " %u", pFCaliIp2SCnf->usDiv_Q[i]);
        }
    }

    CmdErrProc(ucClientId, pFCaliIp2SCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;
}

/* AT^FCALIDCOCS=<dl_channel> 处理函数，启动DCOC校准流程 */
VOS_UINT32 atSetFCALIDCOCSPara(VOS_UINT8 ucClientId)
{
    FTM_SET_FCALIDCOCS_REQ_STRU stSetCaliDcocSReq = {0};

    (VOS_VOID)vos_printf("\r\natSetFCALIDCOCSPara: %d\r\n", gastAtParaList[0].ulParaValue);

    /* 参数检查 */
    if((AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
		|| (1 != gucAtParaIndex)
		|| (0 == gastAtParaList[0].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 获取参数 */
    stSetCaliDcocSReq.usChannel= (VOS_UINT16)(gastAtParaList[0].ulParaValue);

    /* 发送消息给命令处理模块 */
    if(atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_FCALIDCOCS_REQ,
         ucClientId ,  (VOS_VOID*)(&stSetCaliDcocSReq), sizeof(stSetCaliDcocSReq)) != AT_SUCCESS)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FCALIDCOCS_SET;
    return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */
}

/* AT^FCALIDCOCS=<dl_channel> 返回处理函数 */
VOS_UINT32 atSetFCALIDCOCSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    OS_MSG_STRU* pEvent = (OS_MSG_STRU*)((MsgBlock*)pMsgBlock)->aucValue;
    FTM_SET_FCALIDCOCS_CNF_STRU* pFCaliDCOCSCnf = (FTM_SET_FCALIDCOCS_CNF_STRU*)pEvent->ulParam1;

    (VOS_VOID)vos_printf("\r\natSetFCALIIP2SParaCnfProc\r\n");

    CmdErrProc(ucClientId, pFCaliDCOCSCnf->ulErrCode, 0, NULL);
    return AT_FW_CLIENT_STATUS_READY;
}

//AT^FCALIDCOCS? 处理函数
VOS_UINT32 atQryFCALIDCOCSPara(VOS_UINT8 ucClientId)
{
    FTM_RD_NOPRARA_REQ_STRU stQryCaliDCOCSReq = {0};

    (VOS_VOID)vos_printf("\r\natQryFCALIDCOCSPara\r\n");

    if(atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_FCALIDCOCS_REQ, ucClientId,
        (VOS_VOID*)(&stQryCaliDCOCSReq), sizeof(stQryCaliDCOCSReq)) != AT_SUCCESS)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FCALIDCOCS_READ;
    return AT_WAIT_ASYNC_RETURN;
}

//AT^FCALIDCOCS? 返回处理函数
VOS_UINT32 atQryFCALIDCOCSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    VOS_UINT32 i = 0;
    VOS_UINT16 usLength = 0;
    OS_MSG_STRU* pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    FTM_RD_FCALIDCOCS_CNF_STRU* pFCaliDcocSCnf = (FTM_RD_FCALIDCOCS_CNF_STRU*)pEvent->ulParam1;

    (VOS_VOID)vos_printf("\r\natQryFCALIDCOCSParaCnfProc\r\n");

    if(NULL == pFCaliDcocSCnf)
    {
        return ERR_MSP_FAILURE;
    }

    if(ERR_MSP_SUCCESS != pFCaliDcocSCnf->ulErrCode)
    {
       CmdErrProc(ucClientId, pFCaliDcocSCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
       return ERR_MSP_FAILURE;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"^FCALIDCOCS:%u,%u", pFCaliDcocSCnf->usStatus, pFCaliDcocSCnf->usChannel);

    //Antenna1 Non-blocking I path
    for(i=0; i<FTM_CALIDCOCS_AGC_NUM; i++)
    {
        if(0 == i)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
              "%s^FCALIDCOCS:NOBLK_ANT1_I:%u", gaucAtCrLf, pFCaliDcocSCnf->usNOBLK_ANT1_I[i]);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                " %u", pFCaliDcocSCnf->usNOBLK_ANT1_I[i]);
        }
    }

    //Antenna1 Non-blocking Q path
    for(i=0; i<FTM_CALIDCOCS_AGC_NUM; i++)
    {
        if(0 == i)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
              "%s^FCALIDCOCS:NOBLK_ANT1_Q:%u", gaucAtCrLf, pFCaliDcocSCnf->usNOBLK_ANT1_Q[i]);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                " %u", pFCaliDcocSCnf->usNOBLK_ANT1_Q[i]);
        }
    }

    //Antenna1 Blocking I path
    for(i=0; i<FTM_CALIDCOCS_AGC_NUM; i++)
    {
        if(0 == i)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
              "%s^FCALIDCOCS:BLK_ANT1_I:%u", gaucAtCrLf, pFCaliDcocSCnf->usBLK_ANT1_I[i]);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                " %u", pFCaliDcocSCnf->usBLK_ANT1_I[i]);
        }
    }

    //Antenna1 Blocking Q path
    for(i=0; i<FTM_CALIDCOCS_AGC_NUM; i++)
    {
        if(0 == i)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
              "%s^FCALIDCOCS:BLK_ANT1_Q:%u", gaucAtCrLf, pFCaliDcocSCnf->usBLK_ANT1_Q[i]);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                " %u", pFCaliDcocSCnf->usBLK_ANT1_Q[i]);
        }
    }

    //Antenna2 Non-blocking I path
    for(i=0; i<FTM_CALIDCOCS_AGC_NUM; i++)
    {
        if(0 == i)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
              "%s^FCALIDCOCS:NOBLK_ANT2_I:%u", gaucAtCrLf, pFCaliDcocSCnf->usNOBLK_ANT2_I[i]);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                " %u", pFCaliDcocSCnf->usNOBLK_ANT2_I[i]);
        }
    }

    //Antenna2 Non-blocking Q path
    for(i=0; i<FTM_CALIDCOCS_AGC_NUM; i++)
    {
        if(0 == i)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
              "%s^FCALIDCOCS:NOBLK_ANT2_Q:%u",  gaucAtCrLf, pFCaliDcocSCnf->usNOBLK_ANT2_Q[i]);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                " %u", pFCaliDcocSCnf->usNOBLK_ANT2_Q[i]);
        }
    }

    //Antenna2 Blocking I path
    for(i=0; i<FTM_CALIDCOCS_AGC_NUM; i++)
    {
        if(0 == i)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
              "%s^FCALIDCOCS:BLK_ANT2_I:%u", gaucAtCrLf, pFCaliDcocSCnf->usBLK_ANT2_I[i]);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                " %u", pFCaliDcocSCnf->usBLK_ANT2_I[i]);
        }
    }

    //Antenna2 Blocking Q path
    for(i=0; i<FTM_CALIDCOCS_AGC_NUM; i++)
    {
        if(0 == i)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
              "%s^FCALIDCOCS:BLK_ANT2_Q:%u", gaucAtCrLf, pFCaliDcocSCnf->usBLK_ANT2_Q[i]);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                " %u", pFCaliDcocSCnf->usBLK_ANT2_Q[i]);
        }
    }

    CmdErrProc(ucClientId, pFCaliDcocSCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;
}

//AT^FGAINSTATES=<level_num>[,<level_list>] 处理函数
VOS_UINT32 atSetFGAINSTATESPara(VOS_UINT8 ucClientId)
{
    FTM_SET_FGAINSTATES_REQ_STRU stSetGainStateSReq = {0};

    (VOS_VOID)vos_printf("\r\natSetFGAINSTATESPara: %d, %s\r\n", gastAtParaList[0].ulParaValue, gastAtParaList[1].aucPara);

    //参数检查
    if((AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
		|| (2 != gucAtParaIndex)
		|| (0 == gastAtParaList[0].usParaLen)
		|| (0 == gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    // 获取参数
    stSetGainStateSReq.usGainStateNum = (VOS_UINT16)(gastAtParaList[0].ulParaValue);
#if (FEATURE_LPHY_RFIC_HI6362 == FEATURE_ON)
	if((stSetGainStateSReq.usGainStateNum<=0) || (stSetGainStateSReq.usGainStateNum > FTM_GAINSTATE_MAX_NUM_HI6362))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
#else
    if((stSetGainStateSReq.usGainStateNum<=0) || (stSetGainStateSReq.usGainStateNum > FTM_GAINSTATE_MAX_NUM))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
#endif
    if(initParaListU16(&gastAtParaList[1], stSetGainStateSReq.usGainStateNum, stSetGainStateSReq.usGainState) != ERR_MSP_SUCCESS)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    // 发送消息给命令处理模块
    if(atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_FGAINSTATES_REQ,
         ucClientId ,  (VOS_VOID*)(&stSetGainStateSReq), sizeof(stSetGainStateSReq)) != AT_SUCCESS)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FGAINSTATES_SET;
    return AT_WAIT_ASYNC_RETURN;    // 返回命令处理挂起状态
}

//AT^FGAINSTATES=<level_num>[,<level_list>] 返回处理函数
VOS_UINT32 atSetFGAINSTATESParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    OS_MSG_STRU* pEvent = (OS_MSG_STRU*)((MsgBlock*)pMsgBlock)->aucValue;
    FTM_SET_FGAINSTATES_CNF_STRU* pFGainStateSCnf = (FTM_SET_FGAINSTATES_CNF_STRU*)pEvent->ulParam1;

    (VOS_VOID)vos_printf("\r\natSetFGAINSTATESParaCnfProc\r\n");

    CmdErrProc(ucClientId, pFGainStateSCnf->ulErrCode, 0, NULL);
    return AT_FW_CLIENT_STATUS_READY;
}

//AT^FGAINSTATES? 处理函数
VOS_UINT32 atQryFGAINSTATESPara(VOS_UINT8 ucClientId)
{
    FTM_RD_NOPRARA_REQ_STRU stQryGainStateSReq = {0};

    (VOS_VOID)vos_printf("\r\natQryFGAINSTATESPara\r\n");

    if(atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_FGAINSTATES_REQ, ucClientId,
        (VOS_VOID*)(&stQryGainStateSReq), sizeof(stQryGainStateSReq)) != AT_SUCCESS)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FGAINSTATES_READ;
    return AT_WAIT_ASYNC_RETURN;
}

//AT^FGAINSTATES? 返回处理函数
VOS_UINT32 atQryFGAINSTATESParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    VOS_UINT32 i        =0;
    VOS_UINT16 usLength = 0;
    OS_MSG_STRU* pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    FTM_RD_FGAINSTATES_CNF_STRU* pFGainStateSCnf = (FTM_RD_FGAINSTATES_CNF_STRU*)pEvent->ulParam1;

    (VOS_VOID)vos_printf("\r\natQryFGAINSTATESParaCnfProc\r\n");

    if(NULL == pFGainStateSCnf)
    {
        return ERR_MSP_FAILURE;
    }

    if(ERR_MSP_SUCCESS != pFGainStateSCnf->ulErrCode)
    {
       CmdErrProc(ucClientId, pFGainStateSCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
       return ERR_MSP_FAILURE;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"^FGAINSTATES:%u", pFGainStateSCnf->usGainStateNum);

    //channel number
    for(i=0; i<pFGainStateSCnf->usGainStateNum; i++)
    {
        if(0 == i)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
              ",%u", pFGainStateSCnf->usGainState[i]);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                " %u", pFGainStateSCnf->usGainState[i]);
        }
    }

    CmdErrProc(ucClientId, pFGainStateSCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//AT^FDBBATTS=< att_num>[,<att_list>]处理函数，
VOS_UINT32 atSetFDBBATTSPara(VOS_UINT8 ucClientId)
{
    FTM_SET_FDBBATTS_REQ_STRU stDbbAttSetReq = {0};

     //参数检查
    if((AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
		|| (2 != gucAtParaIndex)
		|| (0 == gastAtParaList[0].usParaLen)
		|| (0 == gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    // 获取参数
#if (FEATURE_LPHY_RFIC_HI6362 == FEATURE_ON)
	stDbbAttSetReq.usDbbCodeNum = (VOS_UINT16)(gastAtParaList[0].ulParaValue);
    stDbbAttSetReq.usDbbCode    = (VOS_UINT16)(gastAtParaList[1].ulParaValue);

    if((stDbbAttSetReq.usDbbCodeNum<=0) || (stDbbAttSetReq.usDbbCodeNum > FTM_DBBATT_MAX_NUM))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 99为下发命令中第二个参数usDbbCode的最大值, 1为最小值 */
    if(stDbbAttSetReq.usDbbCode > 31)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
#else
    stDbbAttSetReq.usDbbAttNum = (VOS_UINT16)(gastAtParaList[0].ulParaValue);

    if((stDbbAttSetReq.usDbbAttNum<=0) || (stDbbAttSetReq.usDbbAttNum > FTM_DBBATT_MAX_NUM))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(initParaListU16(&gastAtParaList[1], stDbbAttSetReq.usDbbAttNum, stDbbAttSetReq.usDbbAtt) != ERR_MSP_SUCCESS)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
#endif
    // 发送消息给命令处理模块
    if(atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_FDBBATTS_REQ,
         ucClientId ,  (VOS_VOID*)(&stDbbAttSetReq), sizeof(stDbbAttSetReq)) != AT_SUCCESS)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FDBBATTS_SET;
    return AT_WAIT_ASYNC_RETURN;    // 返回命令处理挂起状态
}

//AT^FDBBATTS=< att_num>[,<att_list>] 返回处理函数
VOS_UINT32 atSetFDBBATTSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
	OS_MSG_STRU* pEvent = NULL;
    FTM_SET_FDBBATTS_CNF_STRU *pstCnf = NULL;

    (VOS_VOID)vos_printf("\r\n atSetFDBBATTSParaCnfProc\r\n");

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_FDBBATTS_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;
}

//AT^FDBBATTS? 处理函数
VOS_UINT32 atQryFDBBATTSPara(VOS_UINT8 ucClientId)
{
    FTM_RD_NOPRARA_REQ_STRU stQryDbbAttSReq = {0};

    (VOS_VOID)vos_printf("\r\n atQryFDBBATTSPara \r\n");

    if(atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_FDBBATTS_REQ, ucClientId,
        (VOS_VOID*)(&stQryDbbAttSReq), sizeof(stQryDbbAttSReq)) != AT_SUCCESS)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FDBBATTS_READ;
    return AT_WAIT_ASYNC_RETURN;
}

//AT^FDBBATTS? 返回处理函数
VOS_UINT32 atQryFDBBATTSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    VOS_UINT32 i        =0;
    VOS_UINT16 usLength = 0;
    OS_MSG_STRU* pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    FTM_RD_FDBBATTS_CNF_STRU* pFDbbAttSCnf = (FTM_RD_FDBBATTS_CNF_STRU*)pEvent->ulParam1;

    (VOS_VOID)vos_printf("\r\n atQryFDBBATTSParaCnfProc\r\n");

    if(NULL == pFDbbAttSCnf)
    {
        return ERR_MSP_FAILURE;
    }

    if(ERR_MSP_SUCCESS != pFDbbAttSCnf->ulErrCode)
    {
       CmdErrProc(ucClientId, pFDbbAttSCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
       return ERR_MSP_FAILURE;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"^FDBBATTS:%u", pFDbbAttSCnf->usDbbAttNum);

    //channel number
    for(i=0; i<pFDbbAttSCnf->usDbbAttNum; i++)
    {
        if(0 == i)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
              ",%u", pFDbbAttSCnf->usDbbAtt[i]);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                " %u", pFDbbAttSCnf->usDbbAtt[i]);
        }
    }

    CmdErrProc(ucClientId, pFDbbAttSCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AT^FBBATTS =< att_num>[,<att_list>]处理函数
VOS_UINT32 atSetFBBATTSPara(VOS_UINT8 ucClientId)
{
    FTM_SET_FBBATTS_REQ_STRU stBbAttSetReq = {0};

    (VOS_VOID)vos_printf("\r\n atSetFBBATTSPara: %d, %s\r\n", gastAtParaList[0].ulParaValue, gastAtParaList[1].aucPara);

     //参数检查
    if((AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
		|| (2 != gucAtParaIndex)
		|| (0 == gastAtParaList[0].usParaLen)
		|| (0 == gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    // 获取参数
    stBbAttSetReq.usBbAttNum= (VOS_UINT16)(gastAtParaList[0].ulParaValue);

    if((stBbAttSetReq.usBbAttNum<=0) || (stBbAttSetReq.usBbAttNum > FTM_BBATT_MAX_NUM))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(initParaListU16(&gastAtParaList[1], stBbAttSetReq.usBbAttNum, stBbAttSetReq.usBbAtt) != ERR_MSP_SUCCESS)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    // 发送消息给命令处理模块
    if(atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_FBBATTS_REQ,
         ucClientId ,  (VOS_VOID*)(&stBbAttSetReq), sizeof(stBbAttSetReq)) != AT_SUCCESS)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FBBATTS_SET;
    return AT_WAIT_ASYNC_RETURN;    // 返回命令处理挂起状态
}

// AT^FBBATTS =< att_num>[,<att_list>]返回处理函数
VOS_UINT32 atSetFBBATTSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
	OS_MSG_STRU* pEvent = NULL;
    FTM_SET_FBBATTS_CNF_STRU *pstCnf = NULL;

    (VOS_VOID)vos_printf("\r\n atSetBbAttParaCnfProc\r\n");

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_FBBATTS_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;
}

//AT^FBBATTS? 处理函数
VOS_UINT32 atQryFBBATTSPara(VOS_UINT8 ucClientId)
{
    FTM_RD_NOPRARA_REQ_STRU stQryBbAttSReq = {0};

    (VOS_VOID)vos_printf("\r\n atQryFBBATTSPara \r\n");

    if(atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_FBBATTS_REQ, ucClientId,
        (VOS_VOID*)(&stQryBbAttSReq), sizeof(stQryBbAttSReq)) != AT_SUCCESS)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FBBATTS_READ;
    return AT_WAIT_ASYNC_RETURN;
}

//AT^FBBATTS? 返回处理函数
VOS_UINT32 atQryFBBATTSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    VOS_UINT32 i        =0;
    VOS_UINT16 usLength = 0;
    OS_MSG_STRU* pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    FTM_RD_FBBATTS_CNF_STRU* pFBbAttSCnf = (FTM_RD_FBBATTS_CNF_STRU*)pEvent->ulParam1;

    (VOS_VOID)vos_printf("\r\n atQryFBBATTSParaCnfProc\r\n");

    if(NULL == pFBbAttSCnf)
    {
        return ERR_MSP_FAILURE;
    }

    if(ERR_MSP_SUCCESS != pFBbAttSCnf->ulErrCode)
    {
       CmdErrProc(ucClientId, pFBbAttSCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
       return ERR_MSP_FAILURE;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"^FBBATTS:%u", pFBbAttSCnf->usBbAttNum);

    //channel number
    for(i=0; i<pFBbAttSCnf->usBbAttNum; i++)
    {
        if(0 == i)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
              ",%u", pFBbAttSCnf->usBbAtt[i]);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                " %u", pFBbAttSCnf->usBbAtt[i]);
        }
    }

    CmdErrProc(ucClientId, pFBbAttSCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//AT^FCALITXIQS处理函数
VOS_UINT32 atSetFCALITXIQSPara(VOS_UINT8 ucClientId)
{
    FTM_SET_FCALITXIQS_REQ_STRU stCaliTxiqSetReq = {0};

    (VOS_VOID)vos_printf("\r\n atSetFCALITXIQSPara\r\n, g_stATParseCmd.ucCmdOptType = %d, gucAtParaIndex=%d, gastAtParaList[0].usParaLen = %d",
                g_stATParseCmd.ucCmdOptType, gucAtParaIndex, gastAtParaList[0].usParaLen);

    /* 参数检查 */
#if (FEATURE_LPHY_RFIC_HI6362 == FEATURE_ON)
	if((AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
        || (3 != gucAtParaIndex)
		|| (0 == gastAtParaList[0].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 获取参数 */
    stCaliTxiqSetReq.usChannel = (VOS_UINT16)(gastAtParaList[0].ulParaValue);
    stCaliTxiqSetReq.usBand    = (VOS_UINT16)(gastAtParaList[1].ulParaValue);
    stCaliTxiqSetReq.usRfid    = (VOS_UINT16)(gastAtParaList[2].ulParaValue);
#else
    if((AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
        || (1 != gucAtParaIndex)
		|| (0 == gastAtParaList[0].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 获取参数 */
    stCaliTxiqSetReq.usChannel = (VOS_UINT16)(gastAtParaList[0].ulParaValue);
#endif

     // 发送消息给命令处理模块
    if(atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_FCALITXIQS_REQ,
         ucClientId ,  (VOS_VOID*)(&stCaliTxiqSetReq), sizeof(stCaliTxiqSetReq)) != AT_SUCCESS)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FCALITXIQS_SET;
    return AT_WAIT_ASYNC_RETURN;    // 返回命令处理挂起状态
}

//AT^FCALITXIQS返回处理函数
VOS_UINT32 atSetFCALITXIQSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
	OS_MSG_STRU* pEvent = NULL;
    FTM_SET_FCALITXIQS_CNF_STRU *pstCnf = NULL;

    (VOS_VOID)vos_printf("\r\n atSetFCALITXIWSParaCnfProc\r\n");

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_FCALITXIQS_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;
}

//AT^FCALITXIQS? 处理函数
VOS_UINT32 atQryFCALITXIQSPara(VOS_UINT8 ucClientId)
{
    FTM_RD_NOPRARA_REQ_STRU stCaliTxiqRdReq = {0};

     (VOS_VOID)vos_printf("\r\n atQryCaliTxiqPara \r\n");

    if(atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_FCALITXIQS_REQ, ucClientId,
        (VOS_VOID*)(&stCaliTxiqRdReq), sizeof(stCaliTxiqRdReq)) != AT_SUCCESS)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FCALITXIQS_READ;
    return AT_WAIT_ASYNC_RETURN;
}

//AT^FCALITXIQS? 返回处理函数
VOS_UINT32 atQryFCALITXIQSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    VOS_UINT16 usLength = 0;
    OS_MSG_STRU* pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    FTM_RD_FCALITXIQS_CNF_STRU* pFCaliTxiqCnf = (FTM_RD_FCALITXIQS_CNF_STRU*)pEvent->ulParam1;

    (VOS_VOID)vos_printf("\r\natQryFCALITXIQSParaCnfProc\r\n");

    if(NULL == pFCaliTxiqCnf)
    {
        return ERR_MSP_FAILURE;
    }

    if(ERR_MSP_SUCCESS != pFCaliTxiqCnf->ulErrCode)
    {
       CmdErrProc(ucClientId, pFCaliTxiqCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
       return ERR_MSP_FAILURE;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"^FCALITXIQS:%u", pFCaliTxiqCnf->usStatus);

	usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"%s^FCALITXIQS:Amplitude:%u", gaucAtCrLf, pFCaliTxiqCnf->usAmplitude);

	usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"%s^FCALITXIQS:Phase:%u", gaucAtCrLf, pFCaliTxiqCnf->usPhase);

	usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"%s^FCALITXIQS:DCI:%u", gaucAtCrLf, pFCaliTxiqCnf->usDCI);

	usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"%s^FCALITXIQS:DCQ:%u", gaucAtCrLf, pFCaliTxiqCnf->usDCQ);


    CmdErrProc(ucClientId, pFCaliTxiqCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;
}


/* AT^FCALIIP2SMRF=<channel> 处理函数，多RF通道, 启动IP2校准流程 */
VOS_UINT32 atSetFCALIIP2SMRFPara(VOS_UINT8 ucClientId)
{
    FTM_SET_FCALIIP2SMRF_REQ_STRU stSetCaliIp2SMRFReq = {0};

    (VOS_VOID)vos_printf("\r\natSetFCALIIP2SMRFPara: %d\r\n", gastAtParaList[0].ulParaValue);

    /* 参数检查 */
#if (FEATURE_LPHY_RFIC_HI6362 == FEATURE_ON)
	if((AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
		|| (4 != gucAtParaIndex)
		|| (0 == gastAtParaList[0].usParaLen)
		|| (0 == gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 获取参数 */
    stSetCaliIp2SMRFReq.usChanNum = (VOS_UINT16)(gastAtParaList[0].ulParaValue);
    stSetCaliIp2SMRFReq.usBand    = (VOS_UINT16)(gastAtParaList[2].ulParaValue);
    stSetCaliIp2SMRFReq.usRfid    = (VOS_UINT16)(gastAtParaList[3].ulParaValue);
#else
    if((AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
		|| (2 != gucAtParaIndex)
		|| (0 == gastAtParaList[0].usParaLen)
		|| (0 == gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 获取参数 */
    stSetCaliIp2SMRFReq.usChanNum = (VOS_UINT16)(gastAtParaList[0].ulParaValue);
#endif

    if(initParaListU16(&gastAtParaList[1], stSetCaliIp2SMRFReq.usChanNum, stSetCaliIp2SMRFReq.usChan) != ERR_MSP_SUCCESS)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 发送消息给命令处理模块 */
    if(atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_FCALIIP2SMRF_REQ,
         ucClientId ,  (VOS_VOID*)(&stSetCaliIp2SMRFReq), sizeof(stSetCaliIp2SMRFReq)) != AT_SUCCESS)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucClientId].CmdCurrentOpt = (AT_CMD_CURRENT_OPT_ENUM)AT_CMD_FCALIIP2SMRF_SET;
    return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */
}

/* AT^FCALIIP2SMRF=<channel> 返回处理函数 */
VOS_UINT32 atSetFCALIIP2SMRFParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    OS_MSG_STRU* pEvent = (OS_MSG_STRU*)((MsgBlock*)pMsgBlock)->aucValue;
    FTM_SET_FCALIIP2SMRF_CNF_STRU* pFCaliIP2SMRFCnf = (FTM_SET_FCALIIP2SMRF_CNF_STRU*)pEvent->ulParam1;

    (VOS_VOID)vos_printf("\r\atSetFCALIIP2SMRFParaCnfProc, error code: %d\r\n", pFCaliIP2SMRFCnf->ulErrCode);

    CmdErrProc(ucClientId, pFCaliIP2SMRFCnf->ulErrCode, 0, NULL);
    return AT_FW_CLIENT_STATUS_READY;
}

/* AT^FCALIIPSMRF? 处理函数 */
VOS_UINT32 atQryFCALIIP2SMRFPara(VOS_UINT8 ucClientId)
{
    FTM_RD_NOPRARA_REQ_STRU stQryCaliIp2SMRFReq = {0};

    (VOS_VOID)vos_printf("\r\atQryFCALIIP2SMRFPara\r\n");

    if(atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_FCALIIP2SMRF_REQ, ucClientId,
        (VOS_VOID*)(&stQryCaliIp2SMRFReq), sizeof(stQryCaliIp2SMRFReq)) != AT_SUCCESS)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucClientId].CmdCurrentOpt = (AT_CMD_CURRENT_OPT_ENUM)AT_CMD_FCALIIP2SMRF_READ;
    return AT_WAIT_ASYNC_RETURN;
}

/* AT^FCALIIP2SMRF? 返回处理函数 */
VOS_UINT32 atQryFCALIIP2SMRFParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    VOS_UINT32 i = 0;
    VOS_UINT32 j = 0;
    VOS_UINT16 usLength = 0;
    OS_MSG_STRU* pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    FTM_RD_FCALIIP2SMRF_CNF_STRU* pFCaliIp2SMRFCnf = (FTM_RD_FCALIIP2SMRF_CNF_STRU*)pEvent->ulParam1;

    (VOS_VOID)vos_printf("\r\natQryFCALIIP2SParaMRFCnfProc\r\n");

    if(NULL == pFCaliIp2SMRFCnf)
    {
        return ERR_MSP_FAILURE;
    }

    if(ERR_MSP_SUCCESS != pFCaliIp2SMRFCnf->ulErrCode)
    {
       CmdErrProc(ucClientId, pFCaliIp2SMRFCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
       return ERR_MSP_FAILURE;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"^FCALIIP2SMRF:%u,%u", pFCaliIp2SMRFCnf->usStatus, pFCaliIp2SMRFCnf->usChanNum);

    for(i=0; i<FTM_CALIIP2_MAX_CHAN_NUM; i++)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                ",%u", pFCaliIp2SMRFCnf->usChan[i]);
    }

    for(i=0; i<FTM_CT_MAX_RFIC_PATH_NUM; i++)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                ",%u", pFCaliIp2SMRFCnf->astIp2CalRst[i].usValidFlg);

        for(j=0; j<FTM_CALIIP2_MAX_CHAN_NUM; j++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                ",%u", pFCaliIp2SMRFCnf->astIp2CalRst[i].usMain_I_DivOff[j]);
        }
        for(j=0; j<FTM_CALIIP2_MAX_CHAN_NUM; j++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                ",%u", pFCaliIp2SMRFCnf->astIp2CalRst[i].usMain_Q_DivOff[j]);
        }
        for(j=0; j<FTM_CALIIP2_MAX_CHAN_NUM; j++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                ",%u", pFCaliIp2SMRFCnf->astIp2CalRst[i].usMain_I_DivOn[j]);
        }
        for(j=0; j<FTM_CALIIP2_MAX_CHAN_NUM; j++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                ",%u", pFCaliIp2SMRFCnf->astIp2CalRst[i].usMain_Q_DivOn[j]);
        }
        for(j=0; j<FTM_CALIIP2_MAX_CHAN_NUM; j++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                ",%u", pFCaliIp2SMRFCnf->astIp2CalRst[i].usDiv_I[j]);
        }
        for(j=0; j<FTM_CALIIP2_MAX_CHAN_NUM; j++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                ",%u", pFCaliIp2SMRFCnf->astIp2CalRst[i].usDiv_Q[j]);
        }
    }

    CmdErrProc(ucClientId, pFCaliIp2SMRFCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;
}

/* AT^FCALIDCOCSMRF=<channel> 处理函数多RF,启动流程 */
VOS_UINT32 atSetFCALIDCOCSMRFPara(VOS_UINT8 ucClientId)
{
    FTM_SET_FCALIDCOCSMRF_REQ_STRU stSetCaliDcocSMRFReq = {0};

    (VOS_VOID)vos_printf("\r\n atSetFCALIDCOCSMRFPara: %d\r\n", gastAtParaList[0].ulParaValue);

    /* 参数检查 */
#if (FEATURE_LPHY_RFIC_HI6362 == FEATURE_ON)
	if((AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
		|| (3 != gucAtParaIndex)
		|| (0 == gastAtParaList[0].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 获取参数 */
    stSetCaliDcocSMRFReq.usChannel= (VOS_UINT16)(gastAtParaList[0].ulParaValue);
    stSetCaliDcocSMRFReq.usBand = (VOS_UINT16)(gastAtParaList[1].ulParaValue);
    stSetCaliDcocSMRFReq.usRfid = (VOS_UINT16)(gastAtParaList[2].ulParaValue);
#else
    if((AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
		|| (1 != gucAtParaIndex)
		|| (0 == gastAtParaList[0].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 获取参数 */
    stSetCaliDcocSMRFReq.usChannel= (VOS_UINT16)(gastAtParaList[0].ulParaValue);
#endif

    /* 发送消息给命令处理模块 */
    if(atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_FCALIDCOCSMRF_REQ,
         ucClientId ,  (VOS_VOID*)(&stSetCaliDcocSMRFReq), sizeof(stSetCaliDcocSMRFReq)) != AT_SUCCESS)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucClientId].CmdCurrentOpt = (AT_CMD_CURRENT_OPT_ENUM)AT_CMD_FCALIDCOCSMRF_SET;
    return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */
}

/* AT^FCALIDCOCSMRF=<channel> 返回处理函数 */
VOS_UINT32 atSetFCALIDCOCSMRFParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    OS_MSG_STRU* pEvent = (OS_MSG_STRU*)((MsgBlock*)pMsgBlock)->aucValue;
    FTM_SET_FCALIDCOCSMRF_CNF_STRU* pFCaliDCOCSMRFCnf = (FTM_SET_FCALIDCOCSMRF_CNF_STRU*)pEvent->ulParam1;

    (VOS_VOID)vos_printf("\r\natSetFCALIDCOCSMRFParaCnfProc\r\n");

    CmdErrProc(ucClientId, pFCaliDCOCSMRFCnf->ulErrCode, 0, NULL);
    return AT_FW_CLIENT_STATUS_READY;
}

//AT^FCALIDCOCSMRF? 处理函数
VOS_UINT32 atQryFCALIDCOCSMRFPara(VOS_UINT8 ucClientId)
{
    FTM_RD_NOPRARA_REQ_STRU stQryCaliDCOCSMRFReq = {0};

    (VOS_VOID)vos_printf("\r\natQryFCALIDCOCSMRFPara\r\n");

    if(atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_FCALIDCOCSMRF_REQ, ucClientId,
        (VOS_VOID*)(&stQryCaliDCOCSMRFReq), sizeof(stQryCaliDCOCSMRFReq)) != AT_SUCCESS)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucClientId].CmdCurrentOpt = (AT_CMD_CURRENT_OPT_ENUM)AT_CMD_FCALIDCOCSMRF_READ;
    return AT_WAIT_ASYNC_RETURN;
}

//AT^FCALIDCOCSMRF? 返回处理函数
VOS_UINT32 atQryFCALIDCOCSMRFParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    VOS_UINT32 i = 0;
    VOS_UINT32 j = 0;
    VOS_UINT32 k = 0;
    VOS_UINT16 usLength = 0;
    OS_MSG_STRU* pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    FTM_RD_FCALIDCOCSMRF_CNF_STRU* pFCaliDcocSMRFCnf = (FTM_RD_FCALIDCOCSMRF_CNF_STRU*)pEvent->ulParam1;

    (VOS_VOID)vos_printf("\r\natQryFCALIDCOCSMRFParaCnfProc\r\n");

    if(NULL == pFCaliDcocSMRFCnf)
    {
        return ERR_MSP_FAILURE;
    }

    if(ERR_MSP_SUCCESS != pFCaliDcocSMRFCnf->ulErrCode)
    {
       CmdErrProc(ucClientId, pFCaliDcocSMRFCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
       return ERR_MSP_FAILURE;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"^FCALIDCOCSMRF:%u,%u", pFCaliDcocSMRFCnf->usStatus, pFCaliDcocSMRFCnf->usChannel);


    for(i=0; i<FTM_CT_MAX_RFIC_PATH_NUM; i++)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
              ",%u,%u", pFCaliDcocSMRFCnf->astDcocCalRst[i].usValidFlg, pFCaliDcocSMRFCnf->astDcocCalRst[i].usValidAntNum);

        for(j=0; j<FTM_CT_MAX_RX_ANT_NUM; j++)
        {
            for(k=0; k<FTM_CALIDCOCS_AGC_NUM; k++)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                  ",%u", pFCaliDcocSMRFCnf->astDcocCalRst[i].astAntCal[j].usAntCompDCI[k]);
            }

            for(k=0; k<FTM_CALIDCOCS_AGC_NUM; k++)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                  ",%u", pFCaliDcocSMRFCnf->astDcocCalRst[i].astAntCal[j].usAntCompDCQ[k]);
            }
        }
    }

    CmdErrProc(ucClientId, pFCaliDcocSMRFCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;
}
/*lint -restore*/
