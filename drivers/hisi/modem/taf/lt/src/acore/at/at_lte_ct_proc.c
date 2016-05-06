

/******************************************************************************
 */
/* PROJECT   :
 */
/* SUBSYSTEM :
 */
/* MODULE    :
 */
/* OWNER     :
 */
/******************************************************************************
 */
/*#include <stdlib.h>
 */
#include "osm.h"
#include "gen_msg.h"

#include "at_lte_common.h"
/*lint --e{7,64,537,322,958,734,813,718,746,830,438,409}*/
#include "ATCmdProc.h"
#include "AtCmdMsgProc.h"
#include "TafDrvAgent.h"
#include "LPsNvInterface.h"
#include "LNvCommon.h"

/*lint -e767 原因:Log打印*/
#define    THIS_FILE_ID        MSP_FILE_ID_AT_LTE_CT_PROC_C
/*lint +e767 */

/******************************************************************************
 */
/* 功能描述: 设置VCTCXO电压
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetVCTCXOPara(VOS_UINT8 ucClientId)
{
    FTM_SET_FVCTCXO_REQ_STRU stVCTCXOSetReq = {0};
    VOS_UINT32 ulRst;

    /* 参数检查
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stVCTCXOSetReq.ulVol = gastAtParaList[0].ulParaValue;

    /* TO DO, 待VCTCXO电压范围确定后需对电压是否过高做出判断
 */
    /* 如设置电压值过高，则返回提示用户
 */
    /* 和深圳老高初步确认
 */
#if 0
    if(((0x8200 - 200) > stVCTCXOSetReq.ulVol) || ((0x8200 + 200) < stVCTCXOSetReq.ulVol))
    {
        return ERR_MSP_VCTCXO_OVER_HIGH;
    }
#endif

    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_FVCTCXO_REQ,ucClientId, (VOS_VOID*)(&stVCTCXOSetReq), sizeof(stVCTCXOSetReq));

    if(AT_SUCCESS == ulRst)
    {
        /* 设置当前操作类型
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FVCTCXO_SET;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态
 */
    }

    return AT_ERROR;
}

VOS_UINT32 atSetVCTCXOParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    OS_MSG_STRU* pEvent = NULL;
    FTM_SET_FVCTCXO_CNF_STRU *pstCnf = NULL;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_FVCTCXO_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;

}


/******************************************************************************
 */
/* 功能描述: 查询VCTCXO电压
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atQryVCTCXOPara(VOS_UINT8 ucClientId)
{
    FTM_RD_FVCTCXO_REQ_STRU stVCTCXOQryReq = {0};
    VOS_UINT32 ulRst;

    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_FVCTCXO_REQ,ucClientId, (VOS_VOID*)(&stVCTCXOQryReq), sizeof(stVCTCXOQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FVCTCXO_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

VOS_UINT32 atQryVCTCXOParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

    FTM_RD_FVCTCXO_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    VOS_UINT16 usLength = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_FVCTCXO_CNF_STRU *)pEvent->ulParam1;


    if(NULL == pstCnf)
    {
        return ERR_MSP_FAILURE;
    }

    usLength = 0;
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
        (VOS_CHAR *)pgucLAtSndCodeAddr,
        (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
        "^FVCTCXO:%d",
        pstCnf->ulVol);


    CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;



}


/******************************************************************************
 */
/* 功能描述: 打开上行信道
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetFTXONPara(VOS_UINT8 ucClientId)
{
    FTM_SET_TXON_REQ_STRU stFTXONSetReq = {(FTM_TXON_SWT_ENUM)0, };
    VOS_UINT32 ulRst;

    // 参数检查


    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stFTXONSetReq.enSwtich = (FTM_TXON_SWT_ENUM)(gastAtParaList[0].ulParaValue);

    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_TXON_REQ, ucClientId, (VOS_VOID*)(&stFTXONSetReq), sizeof(stFTXONSetReq));

    if(AT_SUCCESS == ulRst)
    {
        /* 设置当前操作类型
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FTXON_SET;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态
 */
    }

    return AT_ERROR;
}

VOS_UINT32 atSetFTXONParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

    OS_MSG_STRU* pEvent = NULL;
    FTM_SET_TXON_CNF_STRU *pstCnf = NULL;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_TXON_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;

}

/******************************************************************************
 */
/* 功能描述: 查询上行信道打开状态
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atQryFTXONPara(VOS_UINT8 ucClientId)
{
    FTM_RD_TXON_REQ_STRU stFTXONQryReq = {0};
    VOS_UINT32 ulRst;


    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_TXON_REQ,ucClientId, (VOS_VOID*)(&stFTXONQryReq), sizeof(stFTXONQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FTXON_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

VOS_UINT32 atQryFTXONParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

    FTM_RD_TXON_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    VOS_UINT16 usLength = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_TXON_CNF_STRU *)pEvent->ulParam1;


    if(NULL == pstCnf)
    {
        return ERR_MSP_FAILURE;
    }

    usLength = 0;
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
        (VOS_CHAR *)pgucLAtSndCodeAddr,
        (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
        "^FTXON:%d",
        pstCnf->enSwtich);


    CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;



}

VOS_UINT32 atQryFPllStatusPara(VOS_UINT8 ucClientId)
{
    FTM_RD_FPLLSTATUS_REQ_STRU stFPLLSTATUSQryReq = {0};
    VOS_UINT32 ulRst;

    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_FPLLSTATUS_REQ,ucClientId, (VOS_VOID*)(&stFPLLSTATUSQryReq), sizeof(stFPLLSTATUSQryReq));
    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FPLLSTATUS_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

VOS_UINT32 atQryFPllStatusParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

    FTM_RD_FPLLSTATUS_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    VOS_UINT16 usLength = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_FPLLSTATUS_CNF_STRU *)pEvent->ulParam1;

    if(NULL == pstCnf)
    {
        return ERR_MSP_FAILURE;
    }

    usLength = 0;
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
        (VOS_CHAR *)pgucLAtSndCodeAddr,
        (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
        "^FPLLSTATUS: %d,%d",
        pstCnf->tx_status,pstCnf->rx_status);

    CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;
}


/******************************************************************************
 */
/* 功能描述: 打开下行信道
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetFRXONPara(VOS_UINT8 ucClientId)
{
    FTM_SET_RXON_REQ_STRU stFRXONSetReq = {0};
    VOS_UINT32 ulRst;

    /* 参数检查
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }


    stFRXONSetReq.ulRxSwt = gastAtParaList[0].ulParaValue;

    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_RXON_REQ,ucClientId, (VOS_VOID*)(&stFRXONSetReq), sizeof(stFRXONSetReq));

    if(AT_SUCCESS == ulRst)
    {
        /* 设置当前操作类型
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FRXON_SET;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态
 */
    }

    return AT_ERROR;
}

VOS_UINT32 atSetFRXONParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

    OS_MSG_STRU* pEvent = NULL;
    FTM_SET_RXON_CNF_STRU *pstCnf = NULL;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_RXON_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;

}

/******************************************************************************
 */
/* 功能描述: 查询下行信道开启状态
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atQryFRXONPara(VOS_UINT8 ucClientId)
{
    FTM_RD_RXON_REQ_STRU stFRXONQryReq = {0};
    VOS_UINT32 ulRst;

    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_RXON_REQ,ucClientId, (VOS_VOID*)(&stFRXONQryReq), sizeof(stFRXONQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FRXON_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

VOS_UINT32 atQryFRXONParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

    FTM_RD_RXON_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    VOS_UINT16 usLength = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_RXON_CNF_STRU *)pEvent->ulParam1;


    if(NULL == pstCnf)
    {
        return ERR_MSP_FAILURE;
    }

    usLength = 0;
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
        (VOS_CHAR *)pgucLAtSndCodeAddr,
        (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
        "^FRXON:%d",
        pstCnf->ulRxSwt);


    CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;



}

/******************************************************************************
 */
/* 功能描述: 设置非信令的信道
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetFCHANPara(VOS_UINT8 ucClientId)
{
    FTM_SET_FCHAN_REQ_STRU stFCHANSetReq = {(FCHAN_MODE_ENUM)0, };
    VOS_UINT32 ulRst;
    /* 参数检查
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(3 != gucAtParaIndex)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(0 == gastAtParaList[0].usParaLen)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(0 == gastAtParaList[1].usParaLen)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(0 == gastAtParaList[2].usParaLen)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    stFCHANSetReq.enFchanMode = (FCHAN_MODE_ENUM)(gastAtParaList[0].ulParaValue);
    stFCHANSetReq.ucBand = (VOS_UINT8)(gastAtParaList[1].ulParaValue);
    stFCHANSetReq.usChannel = (VOS_UINT16)(gastAtParaList[2].ulParaValue);

    (VOS_VOID)AT_SetGlobalFchan((VOS_UINT8)(gastAtParaList[0].ulParaValue));


    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_FCHAN_REQ,ucClientId, (VOS_VOID*)(&stFCHANSetReq), sizeof(stFCHANSetReq));

    if(AT_SUCCESS == ulRst)
    {
        /* 设置当前操作类型
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FCHAN_SET;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态
 */
    }

    return AT_ERROR;
}

VOS_UINT32 atSetFCHANParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    OS_MSG_STRU* pEvent = NULL;
    FTM_SET_FCHAN_CNF_STRU *pstCnf = NULL;


    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_FCHAN_CNF_STRU *)pEvent->ulParam1;

    
    if(ERR_MSP_SUCCESS == pstCnf->ulErrCode)
    {
       (VOS_VOID)AT_SetGlobalFchan((VOS_UINT8)(pstCnf->enFchanMode));
    }
    

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;

}

/******************************************************************************
 */
/* 功能描述:
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetFWAVEPara(VOS_UINT8 ucClientId)
{
    VOS_UINT32 ulRst;
    FTM_SET_FWAVE_REQ_STRU stFWaveSetReq = { 0 };

    /* 参数检查
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(2 != gucAtParaIndex)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(0 == gastAtParaList[0].usParaLen)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(0 == gastAtParaList[1].usParaLen)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    stFWaveSetReq.usType  = gastAtParaList[0].ulParaValue;
    stFWaveSetReq.usPower = gastAtParaList[1].ulParaValue;

    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_FWAVE_REQ,ucClientId,
        (VOS_VOID*)(&stFWaveSetReq), sizeof(stFWaveSetReq));


    if(AT_SUCCESS == ulRst)
    {
        /* 设置当前操作类型
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FWAVE_SET;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态
 */
    }

    return AT_ERROR;
}

VOS_UINT32 atSetFWAVEParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    OS_MSG_STRU* pEvent = NULL;
    FTM_SET_FWAVE_CNF_STRU *pstCnf = NULL;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_FWAVE_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);
    return AT_FW_CLIENT_STATUS_READY;
}


/*******************************************************************************/

/* 功能描述: 查询非信令的信道 */

/* 参数说明:*/

/*   ulIndex [in] ... */

/* 返 回 值: */

/*    TODO: ... */
/*******************************************************************************/
VOS_UINT32 atQryFCHANPara(VOS_UINT8 ucClientId)
{
    FTM_RD_FCHAN_REQ_STRU stFCHANQryReq = {0};
    VOS_UINT32 ulRst;

    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_FCHAN_REQ,ucClientId, (VOS_VOID*)(&stFCHANQryReq), sizeof(stFCHANQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FCHAN_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

#define AT_CT_FREQ_INVALID_VALUE                (65536)  /* 36.101 0-65535
 */

VOS_UINT32 atQryFCHANParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
     FTM_RD_FCHAN_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    VOS_UINT16 usLength = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_FCHAN_CNF_STRU *)pEvent->ulParam1;


    if(NULL == pstCnf)
    {
        return ERR_MSP_FAILURE;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
        (VOS_CHAR *)pgucLAtSndCodeAddr,
        (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
        "^FCHAN:%d,%d,%d,%d",
        pstCnf->enFchanMode,
        pstCnf->ucBand,
        pstCnf->usUlChannel,
        pstCnf->usDlChannel);

    CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;
}

/******************************************************************************
 */
/* 功能描述: AT^TSELRF  选择射频通路指令
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
#if 1
extern VOS_UINT32 g_ulWifiRF;

VOS_UINT32 atSetTselrfPara(VOS_UINT8 ucClientId)
{
    FTM_SET_TSELRF_REQ_STRU stTselrfSetReq = { 0 };
    VOS_UINT32 ulRst = AT_SUCCESS;
    VOS_UINT32 Rst;
    VOS_UINT8 ulPath = 0 ;

    
    VOS_CHAR acCmd[200]={0};

    

    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if((1 != gucAtParaIndex) &&
       (2 != gucAtParaIndex))
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(0 == gastAtParaList[0].usParaLen)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    ulPath = (VOS_UINT8)(gastAtParaList[0].ulParaValue);

    if((FTM_TSELRF_FDD_LTE_MAIN     == ulPath)
        || (FTM_TSELRF_TDD_LTE_MAIN == ulPath)
        || (FTM_TSELRF_FDD_LTE_SUB  == ulPath)
        || (FTM_TSELRF_TDD_LTE_SUB  == ulPath)
        || (FTM_TSELRF_TD           == ulPath))

    {
        stTselrfSetReq.ucPath  = ulPath;
        stTselrfSetReq.ucGroup = (VOS_UINT8)gastAtParaList[1].ulParaValue;

    }
    else if(FTM_TSELRF_WIFI == ulPath)
    {
        /*DTS2012041102190 : h00135900 start in 2011-04-11 AT代码融合*/
#ifdef VERSION_V7R1_C010
        ulRst=BSP_HwIsSupportWifi();
#endif
        /*DTS2012041102190 : h00135900 end in 2011-04-11 AT代码融合*/
        if(ulRst == ERR_MSP_SUCCESS)
        {
            /*WIFI未Enable直接返回失败*/
            if(VOS_FALSE == (VOS_UINT32)WIFI_GET_STATUS())
            {
                return AT_ERROR;
            }

            if((0 != gastAtParaList[1].ulParaValue) && (1 != gastAtParaList[1].ulParaValue))
            {
                return AT_ERROR;
            }

            g_ulWifiRF = gastAtParaList[1].ulParaValue;


            Rst = (VOS_UINT32)VOS_sprintf(acCmd, "wl txchain %d", (gastAtParaList[1].ulParaValue + 1));
            if(Rst != ERR_MSP_SUCCESS)
            {

            }

            WIFI_TEST_CMD(acCmd);

            Rst = (VOS_UINT32)VOS_sprintf(acCmd, "wl rxchain %d", (gastAtParaList[1].ulParaValue + 1));
            if(Rst != ERR_MSP_SUCCESS)
            {

            }

            WIFI_TEST_CMD(acCmd);


            Rst = (VOS_UINT32)VOS_sprintf(acCmd, "wl txant %d", gastAtParaList[1].ulParaValue);
            if(Rst != ERR_MSP_SUCCESS)
            {

            }

            WIFI_TEST_CMD(acCmd);

            Rst = (VOS_UINT32)VOS_sprintf(acCmd, "wl antdiv %d", gastAtParaList[1].ulParaValue);
            if(Rst != ERR_MSP_SUCCESS)
            {

            }

            WIFI_TEST_CMD(acCmd);

            return AT_OK;
        }
    }
    else
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_TSELRF_REQ, ucClientId,(VOS_VOID*)(&stTselrfSetReq), sizeof(stTselrfSetReq));

    if(AT_SUCCESS == ulRst)
    {
        /* 设置当前操作类型
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_TSELRF_SET;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态
 */
    }

    return ulRst;
}
VOS_UINT32 atSetTselrfParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    OS_MSG_STRU* pEvent = NULL;
    FTM_SET_TSELRF_CNF_STRU* pstCnf = NULL;

    HAL_SDMLOG("\n enter atSetTselrfParaCnfProc !!!\n");

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_TSELRF_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;

}

/******************************************************************************
 */
/* 功能描述: AT^TSELRF  选择射频通路指令
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */

VOS_UINT32 atQryTselrfPara(VOS_UINT8 ucClientId)
{
/*
平台不提供该接口，由产品线实现。具体使用如下三个NV项获取:
10000 NV_WG_RF_MAIN_BAND
0xD22C NV_ID_UE_CAPABILITY
0xD304 EN_NV_ID_TDS_SUPPORT_FREQ_BAND
*/
    return AT_OK;
}
#endif
/******************************************************************************
 */
/* 功能描述: 设置接收机LNA的等级
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetFLNAPara(VOS_UINT8 ucClientId)
{
    FTM_SET_AAGC_REQ_STRU stFLNASetReq = {0};
    VOS_UINT32 ulRst;

    /* 参数检查
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stFLNASetReq.ucAggcLvl = (VOS_UINT8)(gastAtParaList[0].ulParaValue);

    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_AAGC_REQ,ucClientId, (VOS_VOID*)(&stFLNASetReq), sizeof(stFLNASetReq));

    if(AT_SUCCESS == ulRst)
    {
        /* 设置当前操作类型
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FLNA_SET;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态
 */
    }

    return AT_ERROR;
}

VOS_UINT32 atSetFLNAParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

    OS_MSG_STRU* pEvent = NULL;
    FTM_SET_AAGC_CNF_STRU *pstCnf = NULL;


    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_AAGC_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;

}

/******************************************************************************
 */
/* 功能描述: 查询接收机LNA的等级
 */
/*
 */
/* 参数说明:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* 返 回 值:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atQryFLNAPara(VOS_UINT8 ucClientId)
{
    FTM_RD_AAGC_REQ_STRU stFLNAQryReq = {0};
    VOS_UINT32 ulRst;

    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_AAGC_REQ,ucClientId, (VOS_VOID*)(&stFLNAQryReq), sizeof(stFLNAQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FLNA_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

VOS_UINT32 atQryFLNAParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

    FTM_RD_AAGC_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    VOS_UINT16 usLength = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_AAGC_CNF_STRU *)pEvent->ulParam1;


    if(NULL == pstCnf)
    {
        return ERR_MSP_FAILURE;
    }

    usLength = 0;
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
        (VOS_CHAR *)pgucLAtSndCodeAddr,
        (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
        "^FLNA:%d",
        pstCnf->ucAggcLvl);


    CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;

}

/*******************************************************************************/

/* 功能描述: 查询RSSI*/

/* 参数说明: */

/*   ulIndex [in] ... */

/* 返 回 值: */

/*    TODO: ... */

/*******************************************************************************/
VOS_UINT32 atQryFRSSIPara(VOS_UINT8 ucClientId)
{
    FTM_FRSSI_REQ_STRU stFRssiQryReq = {0};
    VOS_UINT32 ulRst;

    /* lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_FRSSI_REQ,ucClientId, (VOS_VOID*)(&stFRssiQryReq), sizeof(stFRssiQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FRSSI_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}
VOS_UINT32 atQryFRSSIParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

    OS_MSG_STRU* pEvent = NULL;
    FTM_FRSSI_CNF_STRU *pstCnf = NULL;
    VOS_UINT16 usLength = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_FRSSI_CNF_STRU *)pEvent->ulParam1;

    if(NULL == pstCnf)
    {
        return ERR_MSP_FAILURE;
    }

    usLength = 0;

    /* 适配V7R5版本4RX接收，GU只报一个值，其他报0，L根据FTM上报结果，支持4RX接收上报4个值，不支持时上报1个值 */
#if (FEATURE_ON == FEATURE_LTE_4RX)
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucLAtSndCodeAddr,
                                       (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                                        "^FRSSI:%d,%d,%d,%d",
                                        pstCnf->lValue1,
                                        pstCnf->lValue2,
                                        pstCnf->lValue3,
                                        pstCnf->lValue4);
#else
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucLAtSndCodeAddr,
                                       (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                                        "^FRSSI:%d", pstCnf->lValue1);
#endif

    CmdErrProc(ucClientId, pstCnf->ulErrCode,usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;
}


VOS_UINT32 AT_GetLteFeatureInfo(AT_FEATURE_SUPPORT_ST*pstFeATure)
{

    /*AT_FEATURE_SUPPORT_ST *pstFeATure = NULL;
 */
    /*RRC_NV_SUPPORT_BAND_ID_LIST_STRU stSupportBandID = {0};
 */
    VOS_UINT32 ulRst  = 0;

    VOS_UINT8 ucBandStr[64] = {0};
    VOS_UINT8 ucBandNv = 0;
    VOS_UINT8 ucBandFlag = 0;

    VOS_UINT32 ulStrlen1=0;
    VOS_UINT32 i =0;

    VOS_UINT8  ucBandNum[65]={0};
    LRRC_NV_UE_EUTRA_CAP_STRU *pstEutraCap = NULL;

    pstEutraCap = VOS_MemAlloc(WUEPS_PID_AT, (DYNAMIC_MEM_PT), sizeof(LRRC_NV_UE_EUTRA_CAP_STRU));

    if( pstEutraCap == NULL)
    {
        return ERR_MSP_MALLOC_FAILUE;
    }

    MSP_MEMSET(pstEutraCap, 0, sizeof(LRRC_NV_UE_EUTRA_CAP_STRU ));

    ulRst = NVM_Read(EN_NV_ID_UE_CAPABILITY,pstEutraCap,sizeof(LRRC_NV_UE_EUTRA_CAP_STRU));
    if( ulRst != ERR_MSP_SUCCESS )
    {
        VOS_MemFree(WUEPS_PID_AT, pstEutraCap);
        return ERR_MSP_FAILURE;
    }

    /*RRC_MAX_NUM_OF_BANDS
 */

    for( i = 0; i < pstEutraCap->stRfPara.usCnt; i++ )
    {
        if( pstEutraCap->stRfPara.astSuppEutraBandList[i].ucEutraBand > 0 )
        {
            ucBandNv=pstEutraCap->stRfPara.astSuppEutraBandList[i].ucEutraBand;
            if( ucBandNv < (RRC_MAX_NUM_OF_BANDS+1) )
            {
                ucBandNum[ucBandNv]=1;
                ucBandFlag++;
            }
        }
    }

    /*解析获取LTE band信息
 */
    if( ucBandFlag > 0 )
    {
        pstFeATure[AT_FEATURE_LTE].ucFeatureFlag = AT_FEATURE_EXIST;
        /*ulStrlen1 += At_sprintf(64,ucBandStr,ucBandStr+ulStrlen1,"%s","LTE,");
 */
    }
    else
    {
        VOS_MemFree(WUEPS_PID_AT, pstEutraCap);
        return ERR_MSP_FAILURE;
    }

    for( i = 1 ; i < 65; i++ )
    {
        if( ucBandNum[i] == 1 )
        {
            ulStrlen1 +=(VOS_UINT32) At_sprintf(64,(VOS_CHAR* )ucBandStr,(VOS_CHAR* )(ucBandStr+ulStrlen1),"B%d,",i);
            /*ucBandNum[i]=2;
 */
        }
    }

    for( i = 0 ; i < ulStrlen1-1; i++ )
    {
        pstFeATure[AT_FEATURE_LTE].aucContent[i] = ucBandStr[i];
    }

    for( i = 0 ; i < ulStrlen1; i++ )/* [false alarm]:fortify */
    {
        ucBandStr[i] = 0;/* [false alarm]:fortify */
    }/* [false alarm]:fortify */

    ulStrlen1 = 0;/* [false alarm]:fortify*/

    VOS_MemFree(WUEPS_PID_AT, pstEutraCap);/* [false alarm]:fortify */
    return ERR_MSP_SUCCESS;/* [false alarm]:fortify */

}


VOS_UINT32 atSetTBATPara(VOS_UINT8 ucClientId)
{
    FTM_SET_TBAT_REQ_STRU stTbatSet ={0};
    FTM_RD_TBAT_REQ_STRU  stTbatRd={0};

    VOS_UINT8  ucType = 0;
    VOS_UINT8  ucOpr = 0;
    VOS_UINT16 usValue = 0;
    VOS_UINT32 ulRst=0;

    /* 参数检查
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(4 < gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if((0 == gastAtParaList[0].usParaLen) ||
       (0 == gastAtParaList[1].usParaLen) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ucType = (VOS_UINT8)(gastAtParaList[0].ulParaValue);
    ucOpr = (VOS_UINT8)(gastAtParaList[1].ulParaValue);

    if( ucOpr == 1 )
    {
        /*设置
 */
        if(0 != gastAtParaList[2].usParaLen)/* [false alarm]:fortify */
        {
            usValue = gastAtParaList[2].usParaLen;/* [false alarm]:fortify*/

            stTbatSet.ucOpr = ucOpr;/* [false alarm]:fortify */
            stTbatSet.ucType = ucType;/* [false alarm]:fortify */
            stTbatSet.usValueMin = (VOS_UINT16)gastAtParaList[2].ulParaValue;/* [false alarm]:fortify */
            stTbatSet.usValueMax = (VOS_UINT16)gastAtParaList[3].ulParaValue;/* [false alarm]:fortify */

            HAL_SDMLOG("\n stTbatSet.usValueMin=%d,stTbatSet.usValueMax=%d\n",stTbatSet.usValueMin,stTbatSet.usValueMax);

            ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_TBAT_REQ,ucClientId, (VOS_VOID*)(&stTbatSet), sizeof(stTbatSet));/* [false alarm]:fortify */
            if(AT_SUCCESS == ulRst)
            {
                gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_TBAT_SET;
                return AT_WAIT_ASYNC_RETURN;
            }
            return AT_ERROR;
        }
        else
        {
            return AT_ERROR;
        }
    }
    else if( ucOpr == 0 )
    {
        /*查询
 */
        usValue = (VOS_UINT16)gastAtParaList[2].usParaLen;/* [false alarm]:fortify */

        stTbatRd.ucOpr = ucOpr;/* [false alarm]:fortify */
        stTbatRd.ucType = ucType;/* [false alarm]:fortify */
        stTbatRd.usValue = usValue;

        ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_TBAT_REQ,ucClientId, (VOS_VOID*)(&stTbatRd), sizeof(stTbatRd));
        if(AT_SUCCESS == ulRst)
        {
            gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_TBAT_READ;
            return AT_WAIT_ASYNC_RETURN;
        }
        return AT_ERROR;

    }
    else
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
}


VOS_UINT32 atSetTbatCnf(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    OS_MSG_STRU*pEvent = NULL;
    FTM_SET_TBAT_CNF_STRU *pstCnf=NULL;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_TBAT_CNF_STRU *)pEvent->ulParam1;
    HAL_SDMLOG("\n enter into atSetTbatCnf\n");
    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);
    return AT_OK;
}

VOS_UINT32 atRdTbatCnf(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    OS_MSG_STRU*pEvent = NULL;
    FTM_RD_TBAT_CNF_STRU *pstCnf=NULL;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_TBAT_CNF_STRU *)pEvent->ulParam1;
    HAL_SDMLOG("\n enter into atRdTbatCnf\n");
    HAL_SDMLOG("\n pstCnf->ucType=%d,pstCnf->usValue=%d \n",(VOS_INT)pstCnf->ucType,(VOS_INT)pstCnf->usValue);

    gstLAtSendData.usBufLen = 0;
    gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucLAtSndCodeAddr,
                                               (VOS_CHAR*)pgucLAtSndCodeAddr,
                                               "^TBAT:%d,%d",
                                               pstCnf->ucType,pstCnf->usValue
                                             );

    CmdErrProc(ucClientId, pstCnf->ulErrCode, gstLAtSendData.usBufLen, pgucLAtSndCodeAddr);

    return AT_OK;
}

// *****************************************************************************
// 功能描述: 设置发射机的发射功率
//
// 参数说明:
//   ulIndex [in] ...
//                ...
//
// 返 回 值:
//    TODO: ...
// *****************************************************************************
VOS_UINT32 atSetFPOWPara(VOS_UINT8 ucClientId)
{
    FTM_FPOW_REQ_STRU stFPOWSetReq = {0};
    VOS_UINT32 ulRst = 0;
    VOS_INT16 sPower = 0;

    /*lint -e516*/
    HAL_SDMLOG("-----enter:[%s] \n", __FUNCTION__);
    /*lint -e516*/

    // 参数检查
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 != gastAtParaList[0].usParaLen)
    {
        //sPower = (S16_T)atoi((CONST CHAR_T*)(gastAtParaList[0].aucPara));
        //sPower = gastAtParaList[0].ulParaValue;
        ulRst = initParaListS16((AT_PARSE_PARA_TYPE_STRU *)(&(gastAtParaList[0])),1,(VOS_INT16*)(&sPower));

        if(ulRst != ERR_MSP_SUCCESS)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        if(-60 > sPower || 24 < sPower)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }
    else
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stFPOWSetReq.sPower = sPower;

    //(S16_T)(gastAtParaList[0].ulParaValue);
    HAL_SDMLOG("-----[%s]:send data to C-core \n", __FUNCTION__);

    // lkf58113 @ 20110929 采用新的发送函数:atSendFtmDataMsg
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_FPOW_REQ, ucClientId, (VOS_VOID*)(&stFPOWSetReq), sizeof(stFPOWSetReq));

    if(AT_SUCCESS == ulRst)
    {
        // 设置当前操作类型
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FPOW_SET;

        return AT_WAIT_ASYNC_RETURN;
        // 返回命令处理挂起状态
     }

    return AT_ERROR;
}

VOS_UINT32 atSetFPOWParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID*pMsgBlock)
{
    OS_MSG_STRU* pEvent = NULL;
    FTM_FPOW_CNF_STRU *pstCnf = NULL;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_FPOW_CNF_STRU *)pEvent->ulParam1;
    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;
}
