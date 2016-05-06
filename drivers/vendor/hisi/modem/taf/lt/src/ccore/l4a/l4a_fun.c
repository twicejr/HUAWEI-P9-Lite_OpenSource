
/*lint --e{740,958,717}*/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "l4a_fun.h"

#define    THIS_FILE_ID        MSP_FILE_ID_L4A_FUN_C

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
VOS_UINT32 g_L4aPrintCtrl = 0;

/*****************************************************************************
  3 Function
*****************************************************************************/

#define L4A_VALID_PID_CHECK(pstReq, pstCnf) do{ \
if((NULL == pstReq) || (NULL == pstCnf) || (pstReq->stCtrl.ulPid != pstCnf->ulOpId))    \
    return ERR_MSP_FAILURE; \
else    \
    return ERR_MSP_SUCCESS; \
}while(0)


VOS_UINT32 l4a_GetValidCidNum(VOS_UINT8 *pData)
{
    VOS_UINT32 i = 0, ulNum = 0;
    
    for(i = 0; i < (APS_L4A_LTE_MAX_CID + 1); i++)
    {
        if(pData[i])
        {
            ulNum++;
        }
    }

    return ulNum;
}

VOS_UINT32 l4a_GetUlValidCidNum(VOS_UINT32 *pData)
{
    VOS_UINT32 i = 0, ulNum = 0;
    
    for(i = 0; i < (APS_L4A_LTE_MAX_CID + 1); i++)
    {
        if(pData[i])
        {
            ulNum++;
        }
    }

    return ulNum;
}


VOS_UINT32 l4a_GetValidCidIndex(VOS_UINT8 *pData, VOS_UINT32 x)
{
    VOS_UINT32 i = 0, ulNum = 0;
    
    for(i = 0; i < (APS_L4A_LTE_MAX_CID + 1); i++)
    {
        if((pData[i]) && (ulNum++ == x))
        {
            break;
        }
    }

    return i;
}

VOS_UINT32 l4a_GetUlValidCidIndex(VOS_UINT32 *pData, VOS_UINT32 x)
{
    VOS_UINT32 i = 0, ulNum = 0;
    
    for(i = 0; i < (APS_L4A_LTE_MAX_CID + 1); i++)
    {
        if((pData[i]) && (ulNum++ == x))
        {
            break;
        }
    }

    return i;
}


VOS_VOID l4a_GetPLMNInfo(L4A_PLMN_ID_STRU * pMspPlmn, APP_PLMN_ID_STRU * pPsPlmn)
{
    if((NULL == pMspPlmn) || (NULL == pPsPlmn))
    {
        return ;
    }

    pMspPlmn->Mcc = ((pPsPlmn->aucPlmnId[0] & 0x0f) << 8)
        | (pPsPlmn->aucPlmnId[0] & 0xf0)
        | (pPsPlmn->aucPlmnId[1] & 0x0f);

    /* 高四位全为1时，表示mnc只有两位*/
    if(0xf0 == (pPsPlmn->aucPlmnId[1] & 0xf0))
    {
        pMspPlmn->Mnc = ((pPsPlmn->aucPlmnId[2] & 0x0f) << 4)
            | ((pPsPlmn->aucPlmnId[2] & 0xf0) >> 4)
            | 0x0f00;
    }
    else
    {
        pMspPlmn->Mnc = (pPsPlmn->aucPlmnId[2] & 0x0f);
        pMspPlmn->Mnc <<= 8;
        pMspPlmn->Mnc |= (pPsPlmn->aucPlmnId[2] & 0xf0);
        pMspPlmn->Mnc |= ((pPsPlmn->aucPlmnId[1] & 0xf0) >> 4);
    }
    return ;
}

/* RDP命令第x个cid请求处理函数 */
VOS_UINT32 l4a_FunRDPCidIndexReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid, VOS_UINT32 x)
{
    APP_ESM_INQ_PARA_REQ_STRU stReq= {0};
    L4A_ONLY_CID_COMM_REQ_STRU *pstReq = NULL;

    pstReq = (L4A_ONLY_CID_COMM_REQ_STRU*)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulOpId = pstReq->stCtrl.ulPid;
    stReq.ulCid = l4a_GetValidCidIndex(pstReq->aucCid, x);
    if(stReq.ulCid == (APS_L4A_LTE_MAX_CID + 1))
    {
        return ERR_MSP_FAILURE;
    }
    return  l4aPacket2Ps(ulPsReqPid, &stReq, sizeof(APP_ESM_INQ_PARA_REQ_STRU));
}

VOS_UINT32 l4a_FunPsOnlyCidCommSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    /* 第一次处理的是第0个cide */
    return l4a_FunRDPCidIndexReq(pData, ulPsReqMsgId, ulPsReqPid, 0);
}

VOS_UINT32 l4a_FunPsNoCidCommSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    L4A_NO_CID_COMM_CNF_STRU stCnf  = {0};
    APP_ESM_PARA_SET_CNF_STRU *pstCnf=NULL;

    if(NULL == pData)
    {
        stCnf.ulErrorCode = ERR_MSP_TIMEOUT;
        return l4aPacket2Aps(&stCnf, sizeof(L4A_NO_CID_COMM_CNF_STRU));
    }

    pstCnf = (APP_ESM_PARA_SET_CNF_STRU *)(pData);

    stCnf.enMsgId = pstTable->ulAtCnfMsgId;
    stCnf.stCtrl.ulPid = pstCnf->ulOpId;
    stCnf.stCtrl.ulClientId = (VOS_UINT32)usClientId;

    stCnf.ulErrorCode = pstCnf->ulSetRslt;
    return l4aPacket2Aps(&stCnf, sizeof(L4A_NO_CID_COMM_CNF_STRU));
}

/* ^LWCLASH REQ */
VOS_UINT32 l4a_FunPsLwclashReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_RRC_LWCLASH_REQ_STRU stReq= {0};

    stReq.ulMsgId = ulPsReqMsgId;

    return l4aPacket2Ps(ulPsReqPid, &stReq, sizeof(APP_RRC_LWCLASH_REQ_STRU));
}


/* ^LWCLASH CNF */
VOS_UINT32 l4a_FunPsLwclashReadCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    L4A_READ_LWCLASH_CNF_STRU stCnf  = {0};
    RRC_APP_LWCLASH_CNF_STRU *pstCnf = NULL;

    stCnf.enMsgId = pstTable->ulAtCnfMsgId;
    stCnf.usClientId = usClientId;

    if(NULL == pData)
    {
        stCnf.ulErrorCode = ERR_MSP_TIMEOUT;
        return l4aPacket2At(&stCnf, sizeof(L4A_READ_LWCLASH_CNF_STRU));
    }

    pstCnf = (RRC_APP_LWCLASH_CNF_STRU *)(pData);
    stCnf.ulErrorCode = ERR_MSP_SUCCESS;
    (VOS_VOID)VOS_MemCpy(&stCnf.stLwclashInfo, &pstCnf->stLWClashPara, sizeof(RRC_APP_LWCLASH_PARA_STRU));

    return l4aPacket2At(&stCnf, sizeof(L4A_READ_LWCLASH_CNF_STRU));
}


VOS_UINT32 l4a_FunPsLcacellReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_L2_CA_CELL_INFO_REQ_STRU stReq= {0};
    
    stReq.ulMsgId = ulPsReqMsgId;
    
    return l4aPacket2Ps(ulPsReqPid, &stReq, sizeof(APP_L2_CA_CELL_INFO_REQ_STRU));
}

VOS_UINT32 l4a_FunPsLcacellReadCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    L4A_READ_LCACELL_CNF_STRU stCnf  = {0};
    L2_APP_CA_CELL_INFO_CNF_STRU *pstCnf = NULL;
    
    stCnf.enMsgId = pstTable->ulAtCnfMsgId;
    stCnf.usClientId = usClientId;
    
    if(NULL == pData)
    {
        stCnf.ulErrorCode = ERR_MSP_TIMEOUT;
        return l4aPacket2At(&stCnf, sizeof(L4A_READ_LCACELL_CNF_STRU));
    }

    pstCnf = (L2_APP_CA_CELL_INFO_CNF_STRU *)(pData);
    stCnf.ulErrorCode = ERR_MSP_SUCCESS;
    (VOS_VOID)VOS_MemCpy(stCnf.stLcacellInfo, pstCnf->astCellStatus, sizeof(L4A_CACELL_INFO_STRU)*CA_MAX_CELL_NUM);

    return l4aPacket2At(&stCnf, sizeof(L4A_READ_LCACELL_CNF_STRU));
}



/* ^LWURC */
VOS_UINT32 l4a_FunLwclashInd(L4A_PS_MSG_STRU* pData)
{
    RRC_APP_LWCLASH_IND_STRU *pstLwclashInd=NULL;
    L4A_READ_LWCLASH_IND_STRU stLwclash={0};

    if(L4A_GetRptCmdStatus(L4A_RPT_CMD_LWURC))
    {
        pstLwclashInd = (RRC_APP_LWCLASH_IND_STRU *)(pData);

        L4A_INFO_LOG("state %d, ulfreq %d, ulbw %d, dlfreq %d, dlbw %d, band %d\n",
            pstLwclashInd->stLWClashPara.enState, pstLwclashInd->stLWClashPara.usUlFreq,
            pstLwclashInd->stLWClashPara.usUlBandwidth, pstLwclashInd->stLWClashPara.usDlFreq,
            pstLwclashInd->stLWClashPara.usDlBandwidth, pstLwclashInd->stLWClashPara.usBand);

        (VOS_VOID)VOS_MemCpy(&stLwclash.stLwclashInfo, &pstLwclashInd->stLWClashPara, sizeof(RRC_APP_LWCLASH_PARA_STRU));

        stLwclash.enMsgId = ID_MSG_L4A_LWCLASH_IND;

        return l4aPacket2At(&stLwclash, sizeof(L4A_READ_LWCLASH_IND_STRU));
    }

    return ERR_MSP_SUCCESS;
}

VOS_UINT32 l4a_FunLcacellInd(L4A_PS_MSG_STRU* pData)
{
    L2_APP_CA_CELL_INFO_IND_STRU    *pstLcacellInd=NULL;
    L4A_READ_LCACELL_IND_STRU       stLcacell={0};

    if(L4A_GetRptCmdStatus(L4A_RPT_CMD_LCACELLURC))
    {
        pstLcacellInd = (L2_APP_CA_CELL_INFO_IND_STRU *)(pData);

        (VOS_VOID)VOS_MemCpy(stLcacell.stLcacellInfo, pstLcacellInd->astCellStatus, sizeof(L4A_CACELL_INFO_STRU)*CA_MAX_CELL_NUM);

        stLcacell.enMsgId = ID_MSG_L4A_LCACELL_IND;

        return l4aPacket2At(&stLcacell, sizeof(L4A_READ_LCACELL_IND_STRU));
    }

    return ERR_MSP_SUCCESS;
}


VOS_UINT32 l4a_IsmcoexTimeout(VOS_UINT16 usClientId)
{
    L4A_ISMCOEX_CNF_STRU stCnf = { 0 };

    L4A_INFO_LOG("%s, %d.\n",__FUNCTION__, __LINE__);

    stCnf.enMsgId = ID_MSG_L4A_ISMCOEXSET_CNF;
    stCnf.usClientId = usClientId;
    stCnf.ulErrorCode = ERR_MSP_TIMEOUT;
    return l4aPacket2At(&stCnf, sizeof(stCnf));
}

/* ^ISMCOEX REQ */
VOS_UINT32 l4a_FunLteWifiReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    L4A_ISMCOEX_REQ_STRU* pstReq = (L4A_ISMCOEX_REQ_STRU*)pData;
    LMSP_LPHY_LTE_WIFI_COEX_SET_REQ_STRU *pstReqToDsp = NULL;
    VOS_UINT32  ulSize, i, ulRet;

    ulSize = (sizeof(LMSP_LPHY_LTE_WIFI_COEX_SET_REQ_STRU) - 4
        + (sizeof(LMSP_LPHY_COEX_PARA_STRU)*L4A_ISMCOEX_BANDWIDTH_NUM));

    pstReqToDsp = VOS_MemAlloc(MSP_L4_L4A_PID, DYNAMIC_MEM_PT, ulSize);
    if(NULL == pstReqToDsp)
    {
        return l4a_IsmcoexTimeout((VOS_UINT16)pstReq->stCtrl.ulClientId);
    }
    
    /* 发送原语到DSP */
    pstReqToDsp->enMsgId            = ID_LMSP_LPHY_LTE_WIFI_COEX_SET_REQ;
    pstReqToDsp->usCoexParaNum      = L4A_ISMCOEX_BANDWIDTH_NUM;
    pstReqToDsp->usCoexParaSize     = (sizeof(LMSP_LPHY_COEX_PARA_STRU)*L4A_ISMCOEX_BANDWIDTH_NUM);

    for(i = 0; i < L4A_ISMCOEX_BANDWIDTH_NUM; i++)
    {
        pstReqToDsp->astCoexPara[i].enCoexBWType       = (VOS_UINT16)i;
        pstReqToDsp->astCoexPara[i].enCoexEnableInd    = (VOS_UINT16)pstReq->astCoex[i].ulFlag;
        pstReqToDsp->astCoexPara[i].usTx_begin         = (VOS_UINT16)pstReq->astCoex[i].ulTXBegin;
        pstReqToDsp->astCoexPara[i].usTx_End           = (VOS_UINT16)pstReq->astCoex[i].ulTXEnd;
        pstReqToDsp->astCoexPara[i].sTxPower           = (VOS_INT16)pstReq->astCoex[i].lTXPower;
        pstReqToDsp->astCoexPara[i].usRx_begin         = (VOS_UINT16)pstReq->astCoex[i].ulRXBegin;
        pstReqToDsp->astCoexPara[i].usRx_End           = (VOS_UINT16)pstReq->astCoex[i].ulRXEnd;

    }

    ulRet = BSP_MailBox_ComMsgWrite(EN_MAILBOX_SERVICE_LTE_COEX, pstReqToDsp, ulSize, EN_MAILBOX_SLEEP_WAKEUP);
    if(ulRet != VOS_OK)
    {
        L4A_ERROR_LOG("[%s] : l4a send to dsp fail, ulRet %d!!!.\n", __FUNCTION__, ulRet);
        (VOS_VOID)l4a_IsmcoexTimeout((VOS_UINT16)pstReq->stCtrl.ulClientId);
        
        (VOS_VOID)VOS_MemFree(MSP_L4_L4A_PID, pstReqToDsp);

        return ERR_MSP_SUCCESS;
    }
    
    (VOS_VOID)VOS_MemFree(MSP_L4_L4A_PID, pstReqToDsp);

    return ERR_MSP_WAIT_ASYNC;
}


/* ^ISMCOEX CNF */
VOS_UINT32 l4a_FunLteWifiCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    L4A_ISMCOEX_CNF_STRU* pDspCnf = (L4A_ISMCOEX_CNF_STRU*)pData;
    L4A_ISMCOEX_CNF_STRU stCnf = { 0 };

    stCnf.enMsgId = pstTable->ulAtCnfMsgId;
    stCnf.usClientId = usClientId;

    if(NULL == pData)
    {
        L4A_INFO_LOG("%s, %d.\n",__FUNCTION__, __LINE__);

        /* L4A不处理，由AT处理超时 */
        return ERR_MSP_SUCCESS;
    }

    stCnf.ulErrorCode = pDspCnf->ulErrorCode;

    return l4aPacket2At(&stCnf, sizeof(stCnf));
}

/* ^RADVER REQ */
VOS_UINT32 l4a_FunRadverReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    L4A_SET_RADVER_REQ_STRU* pstReq = (L4A_SET_RADVER_REQ_STRU*)pData;
    APP_LRRC_SET_UE_REL_VERSION_REQ_STRU stReqtoRrc = {0};
    
    stReqtoRrc.ulMsgId= ulPsReqMsgId;
    stReqtoRrc.ulMode     = pstReq->ulMod;
    stReqtoRrc.ulVersion  = pstReq->ulVer;

    return l4aPacket2Ps(ulPsReqPid, &stReqtoRrc, sizeof(APP_LRRC_SET_UE_REL_VERSION_REQ_STRU));
}


/* ^RADVER CNF */
VOS_UINT32 l4a_FunRadverCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    LRRC_APP_SET_UE_REL_VERSION_CNF_STRU* pRrcCnf = (LRRC_APP_SET_UE_REL_VERSION_CNF_STRU*)pData;
    L4A_SET_RADVER_CNF_STRU stCnf = { 0 };

    stCnf.enMsgId = pstTable->ulAtCnfMsgId;
    stCnf.usClientId = usClientId;

    if(NULL == pData)
    {
        L4A_INFO_LOG("%s, %d.\n",__FUNCTION__, __LINE__);

        /* L4A不处理，由AT处理超时 */
        return ERR_MSP_SUCCESS;
    }

    stCnf.ulErrorCode = pRrcCnf->enResult;

    return l4aPacket2At(&stCnf, sizeof(stCnf));
}


/* ^CNMR REQ */
VOS_UINT32 l4a_FunPsCnmrReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_RRC_NMR_REQ_STRU stReq = {0};

    stReq.ulMsgId = ulPsReqMsgId;

    return  l4aPacket2Ps(ulPsReqPid,&stReq, sizeof(APP_RRC_NMR_REQ_STRU));
}


/* ^CNMR CNF */
VOS_UINT32 l4a_FunPsCnmrReadCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    L4A_READ_CNMR_CNF_STRU stCnf = {0};
    RRC_APP_NMR_CNF_STRU *pstCnf = NULL;

    stCnf.enMsgId = pstTable->ulAtCnfMsgId;
    stCnf.usClientId = usClientId;

    if(NULL == pData)
    {
        stCnf.ulErrorCode = ERR_MSP_TIMEOUT;
        return l4aPacket2Aps(&stCnf, sizeof(L4A_READ_CNMR_CNF_STRU));
    }

    pstCnf = (RRC_APP_NMR_CNF_STRU *)(pData);
    stCnf.ulErrorCode = pstCnf->enResult;
    (VOS_VOID)VOS_MemCpy(&(stCnf.stLteCelInfo),&(pstCnf->stLteCelInfo),sizeof(RRC_APP_LTE_CELL_INFO_STRU));

    return l4aPacket2At(&stCnf, sizeof(L4A_READ_CNMR_CNF_STRU));
}


/* ^CERSSI/+CSQ/^ANQUERY REQ */
VOS_UINT32 l4a_FunPsCsqReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_RRC_CSQ_REQ_STRU stReq= {0};
    L4A_CSQ_INFO_REQ_STRU *pstReq=NULL;

    pstReq = (L4A_CSQ_INFO_REQ_STRU *)(pData);

    if( ID_MSG_L4A_CERSSI_REQ == pData->enMsgId)
    {
        stReq.usSwt = EN_L4A_RSSI_IND;
    }
    else if (( ID_MSG_L4A_CSQ_INFO_REQ == pData->enMsgId)||(ID_MSG_L4A_ANQUERY_INFO_REQ == pData->enMsgId)\
        ||( ID_MSG_L4A_CERSSI_INQ_REQ == pData->enMsgId))
    {
        stReq.usSwt = EN_L4A_RSSI_INQ_NOT_IND;
    }

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.usNdb = pstReq->ucnDb;
    stReq.usMs  = pstReq->ucMinRptTimerInterval;

    return  l4aPacket2Ps(ulPsReqPid, &stReq, sizeof(APP_RRC_CSQ_REQ_STRU));
}


/* ^CERSSI/+CSQ/^ANQUERY CNF */
VOS_UINT32 l4a_FunPsCsqReadCnf(L4A_PS_MSG_STRU* pData, L4A_FW_MSG_FUN_TABLE_STRU* pstTable, VOS_UINT16 usClientId)
{
    L4A_CSQ_INFO_CNF_STRU stCnf = {0};
    RRC_APP_CSQ_CNF_STRU *pstCnf= NULL;

    stCnf.enMsgId = pstTable->ulAtCnfMsgId;
    stCnf.usClientId = usClientId;

    if(ID_MSG_L4A_CERSSI_CNF == pstTable->ulAtCnfMsgId)
    {
        return 0;
    }
    
    if(NULL == pData)
    {
        stCnf.ulErrorCode = ERR_MSP_TIMEOUT;
        return l4aPacket2Aps(&stCnf, sizeof(L4A_CSQ_INFO_CNF_STRU));
    }

    pstCnf = (RRC_APP_CSQ_CNF_STRU *)(pData);

    stCnf.ulErrorCode = ERR_MSP_SUCCESS;

    /*协议栈保存的值是8倍精度*/
    stCnf.sRssi = ((99 == pstCnf->sRssi)?99:pstCnf->sRssi/8);
    stCnf.sRsrp = ((99 == pstCnf->sRsrp)?99:pstCnf->sRsrp/8);
    stCnf.sRsrq = ((99 == pstCnf->sRsrq)?99:pstCnf->sRsrq/8);

    stCnf.lSINR             = pstCnf->lSINR;
    stCnf.stCQI.usRI        = pstCnf->stCQI.usRI;
    stCnf.stCQI.ausCQI[0]   = pstCnf->stCQI.ausCQI[0];
    stCnf.stCQI.ausCQI[1]   = pstCnf->stCQI.ausCQI[1];

    return l4aPacket2At(&stCnf, sizeof(L4A_CSQ_INFO_CNF_STRU));
}


/* ^LCELLINFO=n REQ */
VOS_UINT32 l4a_FunPsCellInfoReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_LRRC_GET_NCELL_INFO_REQ_STRU stReq= {0};
    L4A_READ_CELL_INFO_REQ_STRU *pstReq=NULL;

    pstReq = (L4A_READ_CELL_INFO_REQ_STRU *)(pData);

    stReq.ulMsgId    = ulPsReqMsgId;
    stReq.enCellFlag = pstReq->ulCellFlag;
    return  l4aPacket2Ps(ulPsReqPid, &stReq, sizeof(APP_LRRC_GET_NCELL_INFO_REQ_STRU));
}


/* ^LCELLINFO=n CNF */
VOS_UINT32 l4a_FunPsCellInfoReadCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    L4A_READ_CELL_INFO_CNF_STRU stCnf   = {0};
    LRRC_APP_GET_NCELL_INFO_CNF_STRU *pstCnf=NULL;

    stCnf.enMsgId = pstTable->ulAtCnfMsgId;
    stCnf.usClientId = usClientId;

    if(NULL == pData)
    {
        stCnf.ulErrorCode = ERR_MSP_TIMEOUT;
        return l4aPacket2At(&stCnf, sizeof(L4A_READ_CELL_INFO_CNF_STRU));
    }

    pstCnf = (LRRC_APP_GET_NCELL_INFO_CNF_STRU *)(pData);
    stCnf.ulErrorCode = pstCnf->enResult;
    (VOS_VOID)VOS_MemCpy(&(stCnf.stNcellListInfo), &pstCnf->stNcellListInfo, sizeof(LRRC_APP_NCELL_LIST_INFO_STRU));

    return l4aPacket2At(&stCnf, sizeof(L4A_READ_CELL_INFO_CNF_STRU));
}


/* ^CELLID? REQ */
VOS_UINT32 l4a_FunPsCellIDReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_RRC_CELLID_REQ_STRU stReq= {0};

    stReq.ulMsgId = ulPsReqMsgId;

    return  l4aPacket2Ps(ulPsReqPid,&stReq, sizeof(APP_RRC_CELLID_REQ_STRU));
}


/* ^CELLID? CNF */
VOS_UINT32 l4a_FunPsCellIDReadCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    L4A_READ_CELL_ID_CNF_STRU stCnf = {0};
    RRC_APP_CELLID_CNF_STRU *pstCnf=NULL;
    L4A_PLMN_ID_STRU stPlmn ={0};

    stCnf.enMsgId = pstTable->ulAtCnfMsgId;
    stCnf.usClientId = usClientId;

    if(NULL == pData)
    {
        stCnf.ulErrorCode = ERR_MSP_TIMEOUT;
        return l4aPacket2At(&stCnf, sizeof(L4A_READ_CELL_ID_CNF_STRU));
    }

    pstCnf = (RRC_APP_CELLID_CNF_STRU *)(pData);
    stCnf.ulErrorCode = pstCnf->enResult;

    l4a_GetPLMNInfo(&stPlmn,&pstCnf->stPlmnId);
    stCnf.usMncNum = (0x0f ==((stPlmn.Mnc)>>8))? 2: 3;
    stCnf.usMCC = stPlmn.Mcc;
    stCnf.usMNC = stPlmn.Mnc;
    stCnf.ulCi = pstCnf->ulCi;
    stCnf.usPci = pstCnf->usPci;
    stCnf.usTAC= pstCnf->usTAC;

    return l4aPacket2At(&stCnf, sizeof(L4A_READ_CELL_ID_CNF_STRU));
}


VOS_UINT32 l4a_FunPsFastDormReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_LRRC_FAST_DORM_CFG_NTF_STRU stReq = {0};
    L4A_SET_FAST_DORM_REQ_STRU*     pstReq = NULL;

    pstReq = (L4A_SET_FAST_DORM_REQ_STRU*)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulFlag        = (VOS_UINT32)pstReq->ulFlag;
    stReq.ulTimerLen    = (VOS_UINT32)pstReq->ulTimerLen;
    return l4aPacket2PsNoCnf(ulPsReqPid,&stReq, sizeof(APP_LRRC_FAST_DORM_CFG_NTF_STRU));
}

VOS_UINT32 l4a_FunPsThresholdReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    L4A_LW_THREASHOLD_CFG_REQ_STRU*    pstReq = NULL;
    APP_LRRC_RESEL_OFFSET_CFG_NTF_STRU stReq = {0};

    pstReq = (L4A_LW_THREASHOLD_CFG_REQ_STRU*)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulFlag  = pstReq->ulFlag;
    return l4aPacket2PsNoCnf(ulPsReqPid,&stReq, sizeof(APP_LRRC_RESEL_OFFSET_CFG_NTF_STRU));
}

VOS_UINT32 l4a_FunPsL2IdleSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_LRRC_CON_TO_IDLE_NTF_STRU stReq = {0};

    stReq.ulMsgId = ulPsReqMsgId;

    return l4aPacket2PsNoCnf(ulPsReqPid,&stReq, sizeof(APP_LRRC_CON_TO_IDLE_NTF_STRU));
}


/* ^LTECS REQ */
VOS_UINT32 l4a_FunPsLtecsReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_MM_INQ_LTE_CS_REQ_STRU stReq= {0};
    APS_L4A_GET_LTE_CS_REQ_STRU *pstReq = NULL;

    pstReq = (APS_L4A_GET_LTE_CS_REQ_STRU*)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulOpId  = pstReq->stCtrl.ulPid;

    return  l4aPacket2Ps(ulPsReqPid,&stReq, sizeof(APP_MM_INQ_LTE_CS_REQ_STRU));
}


/* ^LTECS CNF */
VOS_UINT32 l4a_FunPsLtecsReadCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    APS_L4A_GET_LTE_CS_CNF_STRU stCnf = {0};
    APP_MM_INQ_LTE_CS_CNF_STRU *pstCnf=NULL;

    if(NULL == pData)
    {
        stCnf.ulErrorCode = ERR_MSP_TIMEOUT;
        return l4aPacket2Aps(&stCnf, sizeof(APS_L4A_GET_LTE_CS_CNF_STRU));
    }

    pstCnf = (APP_MM_INQ_LTE_CS_CNF_STRU *)(pData);

    stCnf.enMsgId = pstTable->ulAtCnfMsgId;
    stCnf.stCtrl.ulPid = pstCnf->ulOpId;
    stCnf.stCtrl.ulClientId = (VOS_UINT32)usClientId;

    stCnf.ulErrorCode = pstCnf->ulRslt;
    if(ERR_MSP_SUCCESS == stCnf.ulErrorCode)
    {
        stCnf.ucSmsOverSGs = pstCnf->stLtecsInfo.ucSmsOverSGs;
        stCnf.ucSmsOverIMS = pstCnf->stLtecsInfo.ucSmsOverIMS;
        stCnf.ucCSFB = pstCnf->stLtecsInfo.ucCSFB;
        stCnf.ucSrVcc = pstCnf->stLtecsInfo.ucSrVcc;
        stCnf.ucVoLGA = pstCnf->stLtecsInfo.ucVoLGA;
    }

    return l4aPacket2Aps(&stCnf, sizeof(APS_L4A_GET_LTE_CS_CNF_STRU));
}


VOS_UINT32 l4a_FunLtecsChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode)
{
    APS_L4A_GET_LTE_CS_REQ_STRU *pstReq = (APS_L4A_GET_LTE_CS_REQ_STRU*)(pNode->pData);
    APP_MM_INQ_LTE_CS_CNF_STRU *pstCnf = (APP_MM_INQ_LTE_CS_CNF_STRU *)(pData);

    L4A_VALID_PID_CHECK(pstReq, pstCnf);
}


/* +CEMODE REQ */
VOS_UINT32 l4a_FunPsCemodeReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_MM_INQ_UE_MODE_REQ_STRU stReq= {0};
    APS_L4A_GET_CEMODE_REQ_STRU *pstReq;

    pstReq = (APS_L4A_GET_CEMODE_REQ_STRU *)pData;

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulOpId  = pstReq->stCtrl.ulPid;

    return  l4aPacket2Ps(ulPsReqPid,&stReq, sizeof(APP_MM_INQ_UE_MODE_REQ_STRU));
}

/* +CEMODE CNF */
VOS_UINT32 l4a_FunPsCemodeReadCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    APS_L4A_GET_CEMODE_CNF_STRU stCnf   = {0};
    APP_MM_INQ_UE_MODE_CNF_STRU *pstCnf=NULL;
    VOS_UINT32 i=0;
    VOS_UINT32 aulMode[NAS_LMM_UE_MODE_BUTT-1] = {3, 0, 1, 2};

    if(NULL == pData)
    {
        stCnf.ulErrorCode = ERR_MSP_TIMEOUT;
        return l4aPacket2Aps(&stCnf, sizeof(APS_L4A_GET_CEMODE_CNF_STRU));
    }

    pstCnf = (APP_MM_INQ_UE_MODE_CNF_STRU *)(pData);

    stCnf.enMsgId = pstTable->ulAtCnfMsgId;
    stCnf.stCtrl.ulPid = pstCnf->ulOpId;
    stCnf.stCtrl.ulClientId = (VOS_UINT32)usClientId;

    stCnf.ulErrorCode = pstCnf->ulRslt;
    if(0 != pstCnf->enCurrentUeMode)
    {
        stCnf.ulCurrentUeMode = aulMode[pstCnf->enCurrentUeMode - 1];   /* 把PS的结果转成AT协议的定义 */
    }
    stCnf.ulSupportModeCnt = pstCnf->ulSupportModeCnt;
    for(i=0;i<4;i++)
    {
        stCnf.aulSupportModeList[i] = pstCnf->aenSupportModeList[i];
    }
    return l4aPacket2Aps(&stCnf, sizeof(APS_L4A_GET_CEMODE_CNF_STRU));
}


VOS_UINT32 l4a_FunCemodChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode)
{
    APS_L4A_GET_CEMODE_REQ_STRU *pstReq = (APS_L4A_GET_CEMODE_REQ_STRU*)(pNode->pData);
    APP_MM_INQ_UE_MODE_CNF_STRU *pstCnf = (APP_MM_INQ_UE_MODE_CNF_STRU *)(pData);

    L4A_VALID_PID_CHECK(pstReq, pstCnf);
}

VOS_UINT32 l4a_FunPsAuthDataSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_ESM_SET_GW_AUTH_REQ_STRU stReq= {0};
    APS_L4A_SET_AUTHDATA_REQ_STRU *pstReq=NULL;

    pstReq = (APS_L4A_SET_AUTHDATA_REQ_STRU *)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulOpId  = pstReq->stCtrl.ulPid;
    stReq.ulCid   = (VOS_UINT32)pstReq->stAuthData.ucCid;

    /* win7专有AT命令*/
    if(0 != pstReq->stAuthData.usAuthType)
    {
        stReq.enSetType = APP_ESM_PARA_SETTING;

        /* USER NAME*/
        stReq.stGwAuthInfo.ucUserNameLen = pstReq->stAuthData.ucUserNameLen;
        (VOS_VOID)VOS_MemCpy(stReq.stGwAuthInfo.aucUserName,pstReq->stAuthData.aucUserName,APP_ESM_MAX_USER_NAME_LEN); /* [false alarm]: 屏蔽Fortify错误 */

        /* PASSWORD*/
        stReq.stGwAuthInfo.ucPwdLen = pstReq->stAuthData.ucPwdLen;
        (VOS_VOID)VOS_MemCpy(stReq.stGwAuthInfo.aucPwd,pstReq->stAuthData.aucPassword,APP_ESM_MAX_PASSWORD_LEN); /* [false alarm]: 屏蔽Fortify错误 */

        /* AUTH TYPE */
        stReq.stGwAuthInfo.enGwAuthType = (VOS_UINT8)pstReq->stAuthData.usAuthType;
    }
    else
    {
        stReq.enSetType = APP_ESM_PARA_DELETE;
    }
    return  l4aPacket2Ps(ulPsReqPid,&stReq, sizeof(APP_ESM_SET_GW_AUTH_REQ_STRU));
}


VOS_UINT32 l4a_FunAuthdataChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode)
{
    APS_L4A_SET_AUTHDATA_REQ_STRU *pstReq = (APS_L4A_SET_AUTHDATA_REQ_STRU*)(pNode->pData);
    APP_ESM_PARA_SET_CNF_STRU *pstCnf = (APP_ESM_PARA_SET_CNF_STRU *)(pData);

    L4A_VALID_PID_CHECK(pstReq, pstCnf);
}


/* +CGDCONT REQ */
VOS_UINT32 l4a_FunPsCgdcontSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_ESM_SET_CGDCONT_REQ_STRU stReq= {0};
    APS_L4A_SET_CGDCONT_REQ_STRU *pstReq = NULL;

    pstReq = (APS_L4A_SET_CGDCONT_REQ_STRU*)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulOpId = pstReq->stCtrl.ulPid;
    stReq.ulCid = pstReq->stCgdcontInfo.ucCid;

    if((pstReq->stCgdcontInfo.bitOpEmergency) && (APS_L4A_PDP_FOR_EMC == pstReq->stCgdcontInfo.enEmergency))
    {
        stReq.enBearCidType = APP_ESM_BEARER_TYPE_EMERGENCY;
    }
    else
    {
        stReq.enBearCidType = APP_ESM_CID_TYPE_DEFAULT;
    }

    if((0 == pstReq->stCgdcontInfo.bitOpPdpType) && (0 == pstReq->stCgdcontInfo.bitOpApn))
    {
        stReq.enSetType = APP_ESM_PARA_DELETE;
        stReq.bitOpIpv4AddrAllocType = 0;
        stReq.enIpv4AddrAllocType = APP_ESM_IPV4_ADDR_ALLOC_TYPE_BUTT;
        stReq.enPdnType = APP_ESM_PDN_TYPE_BUTT;
        stReq.stApnInfo.ucApnLen = 0;
    }
    else
    {
        stReq.enSetType              = APP_ESM_PARA_SETTING;
        stReq.bitOpBearType          = 1;
        stReq.bitOpPdnType           = pstReq->stCgdcontInfo.bitOpPdpType;
        stReq.bitOpApn               = pstReq->stCgdcontInfo.bitOpApn;
        stReq.bitOpIpv4AddrAllocType = pstReq->stCgdcontInfo.bitOpIPV4ADDRALLOC;
#if 1
        stReq.bitOpPcscfDiscovery    = pstReq->stCgdcontInfo.bitOpPcscfDiscovery;
        stReq.bitOpImsCnSignalFlag   = pstReq->stCgdcontInfo.bitOpImCnSignalFlg;
#endif
        stReq.enIpv4AddrAllocType   = pstReq->stCgdcontInfo.ucIPV4ADDRALLOC;
        stReq.enPdnType             = pstReq->stCgdcontInfo.enPdpType;
#if 1
        stReq.enPcscfDiscovery      = pstReq->stCgdcontInfo.enPcscfDiscovery;
        stReq.enImsCnSignalFlag     = pstReq->stCgdcontInfo.enImCnSignalFlg;
#endif
        stReq.stApnInfo.ucApnLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pstReq->stCgdcontInfo.aucApn);
        if(stReq.stApnInfo.ucApnLen > APP_MAX_APN_LEN)
        {
            stReq.stApnInfo.ucApnLen = APP_MAX_APN_LEN;
        }

        (VOS_VOID)VOS_MemCpy((VOS_VOID*)(stReq.stApnInfo.aucApnName),
            (VOS_VOID*)(pstReq->stCgdcontInfo.aucApn), stReq.stApnInfo.ucApnLen);
    }

    return  l4aPacket2Ps(ulPsReqPid,&stReq, sizeof(APP_ESM_SET_CGDCONT_REQ_STRU));
}


/* +CGDCONT CNF */
VOS_UINT32 l4a_FunPsCgdcontSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    APS_L4A_SET_CGDCONT_CNF_STRU stCnf  = {0};
    APP_ESM_SET_CGDCONT_CNF_STRU *pstCnf=NULL;


    if(NULL == pData)
    {
        stCnf.ulErrorCode = ERR_MSP_TIMEOUT;

        return l4aPacket2Aps(&stCnf, sizeof(APS_L4A_SET_CGDCONT_CNF_STRU));
    }

    pstCnf = (APP_ESM_SET_CGDCONT_CNF_STRU *)(pData);

    stCnf.enMsgId           = pstTable->ulAtCnfMsgId;
    stCnf.stCtrl.ulPid      = pstCnf->ulOpId;
    stCnf.stCtrl.ulClientId = (VOS_UINT32)usClientId;

    stCnf.ulErrorCode = pstCnf->ulRslt;

    return l4aPacket2Aps(&stCnf, sizeof(APS_L4A_SET_CGDCONT_CNF_STRU));
}


VOS_UINT32 l4a_FunCgdcontChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode)
{
    APS_L4A_SET_CGDCONT_REQ_STRU *pstReq = (APS_L4A_SET_CGDCONT_REQ_STRU*)(pNode->pData);
    APP_ESM_SET_CGDCONT_CNF_STRU *pstCnf = (APP_ESM_SET_CGDCONT_CNF_STRU *)(pData);

    L4A_VALID_PID_CHECK(pstReq, pstCnf);
}


/* +CGDSCONT REQ */
VOS_UINT32 l4a_FunPsCgdscontSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_ESM_SET_BEARER_TYPE_REQ_STRU stReq= {0};
    APS_L4A_SET_CGDSCONT_REQ_STRU*  pstReq = NULL;

    pstReq = (APS_L4A_SET_CGDSCONT_REQ_STRU*)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulOpId = pstReq->stCtrl.ulPid;
    stReq.ulCid = pstReq->stCgdscontInfo.ucSecondaryCid;

    if(0 == pstReq->stCgdscontInfo.bitOpPrimaryCid)
    {
        stReq.enSetType = APP_ESM_PARA_DELETE;
    }
    else
    {
        stReq.enSetType = APP_ESM_PARA_SETTING;
        stReq.enBearCidType = APP_ESM_CID_TYPE_DEDICATED;
        stReq.bitOpLinkdCid = pstReq->stCgdscontInfo.bitOpPrimaryCid;
        stReq.ulLinkdCid = pstReq->stCgdscontInfo.ucPrimaryCid;
    }
    return  l4aPacket2Ps(ulPsReqPid,&stReq, sizeof(APP_ESM_SET_BEARER_TYPE_REQ_STRU));
}


VOS_UINT32 l4a_FunCgdscontChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode)
{
    APS_L4A_SET_CGDSCONT_REQ_STRU *pstReq = (APS_L4A_SET_CGDSCONT_REQ_STRU*)(pNode->pData);
    APP_ESM_PARA_SET_CNF_STRU *pstCnf = (APP_ESM_PARA_SET_CNF_STRU *)(pData);

    L4A_VALID_PID_CHECK(pstReq, pstCnf);
}


static VOS_VOID l4a_SetPortRange(APS_L4A_PDP_TFT_EXT_STRU * pstL4aTft, APP_ESM_TFT_INFO_STRU * pstEsmTft)
{
    /* 调用的地方保证输入参数指针不为空*/

    /* <destination port range>*/
    if(pstL4aTft->bitOpDestPortRange)
    {
        if(pstL4aTft->usLowDestPort == pstL4aTft->usHighDestPort)
        {
            pstEsmTft->bitOpSingleLocalPort = 1;
            pstEsmTft->bitOpLocalPortRange = 0;
            pstEsmTft->usSingleLcPort = pstL4aTft->usLowDestPort;
        }
        else if(pstL4aTft->usLowDestPort < pstL4aTft->usHighDestPort)
        {
            pstEsmTft->bitOpSingleLocalPort = 0;
            pstEsmTft->bitOpLocalPortRange = 1;

            pstEsmTft->usLcPortLowLimit = pstL4aTft->usLowDestPort;
            pstEsmTft->usLcPortHighLimit = pstL4aTft->usHighDestPort;
        }
        else /* 最小值大于最大值*/
        {
            pstEsmTft->bitOpSingleLocalPort = 0;
            pstEsmTft->bitOpLocalPortRange = 0;
        }
    }

    /* <source port range>*/
    if(pstL4aTft->bitOpSrcPortRange)
    {
        if(pstL4aTft->usLowSourcePort == pstL4aTft->usHighSourcePort)
        {
            pstEsmTft->bitOpSingleRemotePort = 1;
            pstEsmTft->bitOpRemotePortRange = 0;
            pstEsmTft->usSingleRmtPort = pstL4aTft->usLowSourcePort;
        }
        else if(pstL4aTft->usLowSourcePort < pstL4aTft->usHighSourcePort)
        {
            pstEsmTft->bitOpSingleRemotePort = 0;
            pstEsmTft->bitOpRemotePortRange = 1;

            pstEsmTft->usRmtPortLowLimit = pstL4aTft->usLowSourcePort;
            pstEsmTft->usRmtPortHighLimit = pstL4aTft->usHighSourcePort;
        }
        else
        {
            pstEsmTft->bitOpSingleRemotePort = 0;
            pstEsmTft->bitOpRemotePortRange = 0;
        }
    }

    return ;
}


VOS_VOID l4a_FunSetTftInfo(APP_ESM_SET_TFT_REQ_STRU* pstPsCgtftReq, APS_L4A_SET_CGTFT_REQ_STRU* pstCgtftReq)
{
    if((0 == pstCgtftReq->stTftInfo.bitOpPktFilterId) && (0 == pstCgtftReq->stTftInfo.bitOpPrecedence))
    {
        pstPsCgtftReq->enSetType = APP_ESM_PARA_DELETE;   /* 0:set 1:del*/
    }
    else
    {
        pstPsCgtftReq->enSetType = APP_ESM_PARA_SETTING;   /* 0:set 1:del*/

        /* <packet filter identifier>*/
        pstPsCgtftReq->stAppTftInfo.ucPacketFilterId = pstCgtftReq->stTftInfo.ucPacketFilterId;

        /* <evaluation precedence index>*/
        pstPsCgtftReq->stAppTftInfo.ucPrecedence = pstCgtftReq->stTftInfo.ucPrecedence;

        /* <source address and subnet mask>*/

        if(1 == pstCgtftReq->stTftInfo.bitOpSrcIp)
        {
            if(APP_ESM_PDN_TYPE_IPV4 == pstCgtftReq->stTftInfo.stSourceIpaddr.enPdpType)
            {
                pstPsCgtftReq->stAppTftInfo.bitOpRmtIpv4AddrAndMask = 1;
                
                
                (VOS_VOID)VOS_MemCpy((VOS_VOID*)(pstPsCgtftReq->stAppTftInfo.aucRmtIpv4Address),
                    (VOS_VOID*)(pstCgtftReq->stTftInfo.stSourceIpaddr.aucIpv4Addr), APP_MAX_IPV4_ADDR_LEN);

                (VOS_VOID)VOS_MemCpy((VOS_VOID*)(pstPsCgtftReq->stAppTftInfo.aucRmtIpv4Mask),
                    (VOS_VOID*)(pstCgtftReq->stTftInfo.stSourceIpMask.aucIpv4Addr), APP_MAX_IPV4_ADDR_LEN);
                
            }

            if(APP_ESM_PDN_TYPE_IPV6 == pstCgtftReq->stTftInfo.stSourceIpaddr.enPdpType)
            {
                pstPsCgtftReq->stAppTftInfo.bitOpRmtIpv6AddrAndMask = 1;

                
                (VOS_VOID)VOS_MemCpy((VOS_VOID*)(pstPsCgtftReq->stAppTftInfo.aucRmtIpv6Address),
                    (VOS_VOID*)(pstCgtftReq->stTftInfo.stSourceIpaddr.aucIpv6Addr), APP_MAX_IPV6_ADDR_LEN);

                (VOS_VOID)VOS_MemCpy((VOS_VOID*)(pstPsCgtftReq->stAppTftInfo.aucRmtIpv6Mask),
                    (VOS_VOID*)(pstCgtftReq->stTftInfo.stSourceIpMask.aucIpv6Addr), APP_MAX_IPV6_ADDR_LEN);
                
            }
        }

        /* <protocol number (ipv4) / next header (ipv6)>*/
        pstPsCgtftReq->stAppTftInfo.bitOpProtocolId = pstCgtftReq->stTftInfo.bitOpProtocolId;
        if(pstPsCgtftReq->stAppTftInfo.bitOpProtocolId)
        {
            pstPsCgtftReq->stAppTftInfo.ucProtocolId = pstCgtftReq->stTftInfo.ucProtocolId;
        }

        /* <destination port range>,<source port range>*/
        l4a_SetPortRange(&(pstCgtftReq->stTftInfo), &(pstPsCgtftReq->stAppTftInfo));

        /* <ipsec security parameter index (spi)>*/
        pstPsCgtftReq->stAppTftInfo.bitOpSecuParaIndex = pstCgtftReq->stTftInfo.bitOpSpi;
        if(pstPsCgtftReq->stAppTftInfo.bitOpSecuParaIndex)
        {
            pstPsCgtftReq->stAppTftInfo.ulSecuParaIndex = pstCgtftReq->stTftInfo.ulSecuParaIndex;
        }

        pstPsCgtftReq->stAppTftInfo.bitOpTypeOfService = pstCgtftReq->stTftInfo.bitOpTosMask;
        pstPsCgtftReq->stAppTftInfo.bitOpFlowLabelType = pstCgtftReq->stTftInfo.bitOpFlowLable;

        /* <type of service (tos) (ipv4) and mask / traffic class (ipv6) and mask>*/
        pstPsCgtftReq->stAppTftInfo.bitOpTypeOfService = pstCgtftReq->stTftInfo.bitOpTosMask;
        if(pstPsCgtftReq->stAppTftInfo.bitOpTypeOfService)
        {
            pstPsCgtftReq->stAppTftInfo.ucTypeOfService = pstCgtftReq->stTftInfo.ucTypeOfService;
            pstPsCgtftReq->stAppTftInfo.ucTypeOfServiceMask = pstCgtftReq->stTftInfo.ucTypeOfServiceMask;
        }

        /* <flow label (ipv6)>*/
        pstPsCgtftReq->stAppTftInfo.bitOpFlowLabelType = pstCgtftReq->stTftInfo.bitOpFlowLable;
        if(pstPsCgtftReq->stAppTftInfo.bitOpFlowLabelType)
        {
            pstPsCgtftReq->stAppTftInfo.ulFlowLabelType = pstCgtftReq->stTftInfo.ulFlowLable;
        }

        /* <direction>  AT与NAS的协议相反*/
        /* (AT:  0-pre rel 7, 1-uplink,   2-downlink, 3-birectional)*/
        /* (NAS: 0-pre rel 7, 1-downlink, 2-uplink,   3-birectional)*/
        if(1 == pstCgtftReq->stTftInfo.enTftFilterDirection)
        {
            pstPsCgtftReq->stAppTftInfo.enDirection = APP_ESM_TRANSFER_DIRECTION_UPLINK;
        }
        else if(2 == pstCgtftReq->stTftInfo.enTftFilterDirection)
        {
            pstPsCgtftReq->stAppTftInfo.enDirection = APP_ESM_TRANSFER_DIRECTION_DOWNLINK;
        }
        else
        {
            pstPsCgtftReq->stAppTftInfo.enDirection = pstCgtftReq->stTftInfo.enTftFilterDirection;
        }

        /* <local address and subnet mask>*/
        if (1 == pstCgtftReq->stTftInfo.bitOpLocalIpv4AddrAndMask)
        {
            pstPsCgtftReq->stAppTftInfo.bitOpLocalIpv4AddrAndMask = 1;

            (VOS_VOID)VOS_MemCpy((VOS_VOID*)(pstPsCgtftReq->stAppTftInfo.aucLocalIpv4Addr),
                (VOS_VOID*)(pstCgtftReq->stTftInfo.aucLocalIpv4Addr), APP_MAX_IPV4_ADDR_LEN);

            (VOS_VOID)VOS_MemCpy((VOS_VOID*)(pstPsCgtftReq->stAppTftInfo.aucLocalIpv4Mask),
                (VOS_VOID*)(pstCgtftReq->stTftInfo.aucLocalIpv4Mask), APP_MAX_IPV4_ADDR_LEN);
        }

        if (1 == pstCgtftReq->stTftInfo.bitOpLocalIpv6AddrAndMask)
        {
            pstPsCgtftReq->stAppTftInfo.bitOpLocalIpv6AddrAndMask = 1;

            (VOS_VOID)VOS_MemCpy((VOS_VOID*)(pstPsCgtftReq->stAppTftInfo.aucLocalIpv6Addr),
                (VOS_VOID*)(pstCgtftReq->stTftInfo.aucLocalIpv6Addr), APP_MAX_IPV6_ADDR_LEN);

            pstPsCgtftReq->stAppTftInfo.ucLocalIpv6Prefix         = pstCgtftReq->stTftInfo.ucLocalIpv6Prefix;
        }
    }

    return ;
}

/* +CGTFT REQ */
VOS_UINT32 l4a_FunPsCgtftSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_ESM_SET_TFT_REQ_STRU stReq= {0};
    APS_L4A_SET_CGTFT_REQ_STRU *pstReq = NULL;

    pstReq = (APS_L4A_SET_CGTFT_REQ_STRU*)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulOpId = pstReq->stCtrl.ulPid;
    stReq.ulCid = pstReq->ulCid;

    l4a_FunSetTftInfo(&stReq, pstReq);
    return  l4aPacket2Ps(ulPsReqPid,&stReq, sizeof(APP_ESM_SET_TFT_REQ_STRU));
}


VOS_UINT32 l4a_FunCgtftChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode)
{
    APS_L4A_SET_CGTFT_REQ_STRU *pstReq = (APS_L4A_SET_CGTFT_REQ_STRU*)(pNode->pData);
    APP_ESM_PARA_SET_CNF_STRU *pstCnf = (APP_ESM_PARA_SET_CNF_STRU *)(pData);

    L4A_VALID_PID_CHECK(pstReq, pstCnf);
}

/* +CGAUTO */
VOS_UINT32 l4a_FunPsCgautoSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_ESM_SET_PDP_MANAGER_TYPE_REQ_STRU stReq= {0};
    APS_L4A_SET_CGAUTO_REQ_STRU *pstReq = NULL;

    pstReq = (APS_L4A_SET_CGAUTO_REQ_STRU*)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulOpId = pstReq->stCtrl.ulPid;

    stReq.enSetType = APP_ESM_PARA_SETTING;

    if(EN_L4A_AUTO_ANSWER == pstReq->enAnsMode)
    {
        stReq.enAnsMode = APP_ESM_ANSWER_MODE_MANI;  /* 手动应答*/
    }
    else if(EN_L4A_MANU_ANSWER == pstReq->enAnsMode)
    {
        stReq.enAnsMode = APP_ESM_ANSWER_MODE_AUTO;
        stReq.enAnsType = APP_ESM_ANSWER_ACCEPT;  /* 自动应答*/
    }
    else
    {
        stReq.enAnsMode = APP_ESM_ANSWER_MODE_AUTO;
        stReq.enAnsType = APP_ESM_ANSWER_REJ;   /* 自动拒绝*/
    }
    return  l4aPacket2Ps(ulPsReqPid,&stReq, sizeof(APP_ESM_SET_PDP_MANAGER_TYPE_REQ_STRU));
}


VOS_UINT32 l4a_FunPsCgautoSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    APS_L4A_SET_CGAUTO_CNF_STRU stCnf  = {0};
    APP_ESM_SET_PDP_MANAGER_TYPE_CNF_STRU *pstCnf=NULL;

    if(NULL == pData)
    {
        stCnf.ulErrorCode = ERR_MSP_TIMEOUT;
        return l4aPacket2Aps(&stCnf, sizeof(L4A_NO_CID_COMM_CNF_STRU));
    }

    pstCnf = (APP_ESM_SET_PDP_MANAGER_TYPE_CNF_STRU *)(pData);

    stCnf.enMsgId = pstTable->ulAtCnfMsgId;
    stCnf.stCtrl.ulPid = pstCnf->ulOpId;
    stCnf.stCtrl.ulClientId = (VOS_UINT32)usClientId;

    stCnf.ulErrorCode = pstCnf->ulSetRslt;
    return l4aPacket2Aps(&stCnf, sizeof(APS_L4A_SET_CGAUTO_CNF_STRU));
}


VOS_UINT32 l4a_FunCgautoChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode)
{
    APS_L4A_SET_CGAUTO_REQ_STRU *pstReq = (APS_L4A_SET_CGAUTO_REQ_STRU*)(pNode->pData);
    APP_ESM_SET_PDP_MANAGER_TYPE_CNF_STRU *pstCnf = (APP_ESM_SET_PDP_MANAGER_TYPE_CNF_STRU *)(pData);

    L4A_VALID_PID_CHECK(pstReq, pstCnf);
}


VOS_VOID l4a_FunCgcontrdpPkj(APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU* pstPsPdpContCnf, APS_L4A_PRIM_PDP_DYNAMIC_EXT_STRU *pstPrim)
{
    if(0 == pstPsPdpContCnf->bitOpApn)
    {
        /* 标识专有承载，用于过滤 */
        pstPrim->bitOpApn = 0;
        return;
    }
    
    pstPrim->ucPrimayCid          = (VOS_UINT8)pstPsPdpContCnf->ulCid;
    pstPrim->bitOpBearerId        = 1;
    pstPrim->bitOpApn             = pstPsPdpContCnf->bitOpApn;
    pstPrim->bitOpIpAddr          = pstPsPdpContCnf->bitOpPdnAddr;
    pstPrim->bitOpSubMask         = pstPsPdpContCnf->bitOpPdnAddr;
    pstPrim->ucBearerId           = (VOS_UINT8)pstPsPdpContCnf->ulEpsbId;
    pstPrim->bitOpDNSPrimAddr     = pstPsPdpContCnf->bitOpDnsPrim;
    pstPrim->bitOpDNSSecAddr      = pstPsPdpContCnf->bitOpDnsSec;
    pstPrim->bitOpPCSCFPrimAddr   = pstPsPdpContCnf->bitOpPCscfPrim;
    pstPrim->bitOpPCSCFSecAddr    = pstPsPdpContCnf->bitOpPCscfSec;
    pstPrim->bitOpGwAddr          = pstPsPdpContCnf->bitOpGateWayAddrInfo;
#if 1
    pstPrim->bitOpImCnSignalFlg   = pstPsPdpContCnf->bitOpImsCnSignalFlag;
    pstPrim->enImCnSignalFlg      = (APS_L4A_IMS_CN_SIG_FLAG_ENUM_UINT8)pstPsPdpContCnf->enImsCnSignalFlag;
#endif
    (VOS_VOID)VOS_MemSet((VOS_VOID*)(pstPrim->aucApn), 0, APS_L4A_MAX_APN_LEN + 1);

    (VOS_VOID)VOS_MemCpy((VOS_VOID*)(pstPrim->aucApn),
        (VOS_VOID*)(pstPsPdpContCnf->stApnInfo.aucApnName), (VOS_UINT32)pstPsPdpContCnf->stApnInfo.ucApnLen);

    (VOS_VOID)VOS_MemCpy((VOS_VOID*)&(pstPrim->stPdpAddr),
        (VOS_VOID*)&(pstPsPdpContCnf->stPDNAddrInfo), sizeof(APP_ESM_IP_ADDR_STRU));

    (VOS_VOID)VOS_MemCpy((VOS_VOID*)&(pstPrim->stSubnetMask),
        (VOS_VOID*)&(pstPsPdpContCnf->stSubnetMask), sizeof(APP_ESM_IP_ADDR_STRU));

    (VOS_VOID)VOS_MemCpy((VOS_VOID*)&(pstPrim->stGWAddr),
        (VOS_VOID*)&(pstPsPdpContCnf->stGateWayAddrInfo), sizeof(APP_ESM_IP_ADDR_STRU));

    (VOS_VOID)VOS_MemCpy((VOS_VOID*)&(pstPrim->stDNSPrimAddr),
        (VOS_VOID*)&(pstPsPdpContCnf->stDnsPrimAddrInfo), sizeof(APP_ESM_IP_ADDR_STRU));

    (VOS_VOID)VOS_MemCpy((VOS_VOID*)&(pstPrim->stDNSSecAddr),
        (VOS_VOID*)&(pstPsPdpContCnf->stDnsSecAddrInfo), sizeof(APP_ESM_IP_ADDR_STRU));

    (VOS_VOID)VOS_MemCpy((VOS_VOID*)&(pstPrim->stPCSCFPrimAddr),
        (VOS_VOID*)&(pstPsPdpContCnf->stPCscfPrimAddrInfo), sizeof(APP_ESM_IP_ADDR_STRU));

    (VOS_VOID)VOS_MemCpy((VOS_VOID*)&(pstPrim->stPCSCFSecAddr),
        (VOS_VOID*)&(pstPsPdpContCnf->stPCscfSecAddrInfo), sizeof(APP_ESM_IP_ADDR_STRU));
}

VOS_UINT32 l4a_FunPsCgcontrdpSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU *pstPsPdpContCnf = NULL;
    APS_L4A_SET_CGCONTRDP_CNF_STRU *pstCnf = NULL;
    VOS_UINT32 ulsize, i, j;
    VOS_UINT32 ret;
    L4A_RX_INFO_STRU *pNode = NULL;
    L4A_ONLY_CID_COMM_REQ_STRU *pstReq = NULL;

    pNode = l4a_GetExeCmdNode(pstTable->ulAtReqMsgId, L4A_REQ_FLAG);
    if((NULL == pNode) || (NULL == pNode->pData) || (NULL == pData))
    {
        L4A_INFO_LOG("%s pNode: %p, pData %p.\n", __FUNCTION__, pNode, pData);

        /* 找不到请求节点，靠AT/TAF超时机制返回ERROR */
        return ERR_MSP_SUCCESS;
    }

    pstPsPdpContCnf = (APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU *)(pData);

    pstReq = (L4A_ONLY_CID_COMM_REQ_STRU *)pNode->pData;

    if(0 == pNode->ulCidNum)
    {
        pNode->ulCidNum = l4a_GetValidCidNum(pstReq->aucCid);
        if(0 == pNode->ulCidNum)
        {
            L4A_INFO_LOG("%s %d failed.\n", __FUNCTION__, __LINE__);
            
            return ERR_MSP_SUCCESS;
        }
        
        L4A_INFO_LOG("%s %d.\n", __FUNCTION__, pNode->ulCidNum);

        ulsize = sizeof(APS_L4A_SET_CGCONTRDP_CNF_STRU) + (pNode->ulCidNum * sizeof(APS_L4A_PRIM_PDP_DYNAMIC_EXT_STRU));

        pstCnf = VOS_MemAlloc(MSP_L4_L4A_PID, DYNAMIC_MEM_PT, ulsize);
        if(NULL == pstCnf)
        {
            /* 申请内存失败，靠AT/TAF超时机制返回ERROR */
            return ERR_MSP_SUCCESS;
        }
        
        (VOS_VOID)VOS_MemSet((VOS_VOID*)pstCnf, 0, ulsize);

        pNode->pCnfData = pstCnf;

        pstCnf->enMsgId             = pstTable->ulAtCnfMsgId;
        pstCnf->stCtrl.ulPid        = pstPsPdpContCnf->ulOpId;
        pstCnf->stCtrl.ulClientId   = (VOS_UINT32)usClientId;
        pstCnf->ulCidNum            = pNode->ulCidNum;
    }
    else
    {
        if(NULL == pNode->pCnfData)
        {
            L4A_INFO_LOG("%s %d failed.\n", __FUNCTION__, __LINE__);
            
            return ERR_MSP_SUCCESS;
        }
        pstCnf = pNode->pCnfData;
    }

    pstCnf->ulErrorCode = pstPsPdpContCnf->ulRslt;

    /* 如果成功先保存应答信息，然后判断是否最后一个处理的cid，如果失败直接应答给AT/TAF */
    if(ERR_MSP_SUCCESS == pstCnf->ulErrorCode)
    {
        l4a_FunCgcontrdpPkj(pstPsPdpContCnf, &pstCnf->astPrimParaInfo[pNode->ulCidIndex]);
        
        pNode->ulCidIndex++;
        if(pNode->ulCidIndex != pNode->ulCidNum)
        {
            /* 再次发起请求 */
            ret = l4a_FunRDPCidIndexReq((L4A_DATA_MSG_STRU*)pstReq, pstTable->ulPsReqMsgId, pstTable->ulPsReqPid, pNode->ulCidIndex);
            if(ERR_MSP_WAIT_ASYNC == ret)
            {
                L4A_INFO_LOG("%s %d.\n", __FUNCTION__, pNode->ulCidIndex);

                /* 返回异步状态，调用的地方要判断 */
                return ERR_MSP_WAIT_ASYNC;
            }
        }
    }

    for(i = 0, j = 0; i < pNode->ulCidNum; i++)
    {
        if(0 != pstCnf->astPrimParaInfo[i].bitOpApn)
        {
            (VOS_VOID)VOS_MemCpy(&pstCnf->astPrimParaInfo[j++], &pstCnf->astPrimParaInfo[i], sizeof(APS_L4A_PRIM_PDP_DYNAMIC_EXT_STRU));
        }
    }

    pstCnf->ulCidNum = j;

    ulsize = sizeof(APS_L4A_SET_CGCONTRDP_CNF_STRU) + (pNode->ulCidNum * sizeof(APS_L4A_PRIM_PDP_DYNAMIC_EXT_STRU));

    ret = l4aPacket2Aps(pstCnf, ulsize);

    (VOS_VOID)VOS_MemFree(MSP_L4_L4A_PID, pstCnf);

    return ret;
}


VOS_UINT32 l4a_FunCgcontrdpChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode)
{
    APS_L4A_SET_CGCONTRDP_REQ_STRU *pstReq = (APS_L4A_SET_CGCONTRDP_REQ_STRU*)(pNode->pData);
    APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU *pstCnf = (APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU *)(pData);

    L4A_VALID_PID_CHECK(pstReq, pstCnf);
}



VOS_UINT32 l4a_FunPsCgscontrdpSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU *pstPsPdpContCnf = NULL;
    APS_L4A_SET_CGSCONTRDP_CNF_STRU *pstCnf = NULL;
    VOS_UINT32 ulsize, i,j;
    VOS_UINT32 ret;
    L4A_RX_INFO_STRU *pNode = NULL;
    L4A_ONLY_CID_COMM_REQ_STRU *pstReq = NULL;
    
    pNode = l4a_GetExeCmdNode(pstTable->ulAtReqMsgId, L4A_REQ_FLAG);
    if((NULL == pNode) || (NULL == pNode->pData) || (NULL == pData))
    {
        L4A_INFO_LOG("%s %d failed.\n", __FUNCTION__, __LINE__);

        /* 找不到请求节点，靠AT/TAF超时机制返回ERROR */
        return ERR_MSP_SUCCESS;
    }

    pstPsPdpContCnf = (APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU *)(pData);
    pstReq = pNode->pData;

    if(0 == pNode->ulCidNum)
    {
        pNode->ulCidNum = l4a_GetValidCidNum(pstReq->aucCid);
        if(0 == pNode->ulCidNum)
        {
            L4A_INFO_LOG("%s %d failed.\n", __FUNCTION__, __LINE__);
            
            return ERR_MSP_SUCCESS;
        }

        L4A_INFO_LOG("%s %d.\n", __FUNCTION__, pNode->ulCidNum);

        ulsize = sizeof(APS_L4A_SET_CGSCONTRDP_CNF_STRU) + (pNode->ulCidNum * sizeof(APS_L4A_SEC_PDP_DYNAMIC_EXT_STRU));

        pstCnf = VOS_MemAlloc(MSP_L4_L4A_PID, DYNAMIC_MEM_PT, ulsize);
        if(NULL == pstCnf)
        {
            /* 申请内存失败，靠AT/TAF超时机制返回ERROR */
            return ERR_MSP_SUCCESS;
        }

        (VOS_VOID)VOS_MemSet((VOS_VOID*)pstCnf, 0, ulsize);

        pNode->pCnfData = pstCnf;

        pstCnf->enMsgId             = pstTable->ulAtCnfMsgId;
        pstCnf->stCtrl.ulPid        = pstPsPdpContCnf->ulOpId;
        pstCnf->stCtrl.ulClientId   = (VOS_UINT32)usClientId;
        pstCnf->ulCidNum            = pNode->ulCidNum;
    }
    else
    {
        if(NULL == pNode->pCnfData)
        {
            L4A_INFO_LOG("%s %d failed.\n", __FUNCTION__, __LINE__);
            
            return ERR_MSP_SUCCESS;
        }
        pstCnf = pNode->pCnfData;
    }

    pstCnf->ulErrorCode = pstPsPdpContCnf->ulRslt;

    /* 如果成功先保存应答信息，然后判断是否最后一个处理的cid，如果失败直接应答给AT/TAF */
    if(ERR_MSP_SUCCESS == pstCnf->ulErrorCode)
    {
        if(pstPsPdpContCnf->bitOpLinkCid)   /* 只记录专有承载信息 */
        {
            pstCnf->astSecParaInfo[pNode->ulCidIndex].ucPrimaryCid  = (VOS_UINT8)pstPsPdpContCnf->ulLinkCid;
            pstCnf->astSecParaInfo[pNode->ulCidIndex].ucCid         = (VOS_UINT8)pstPsPdpContCnf->ulCid;
            pstCnf->astSecParaInfo[pNode->ulCidIndex].ucBearerId    = (VOS_UINT8)pstPsPdpContCnf->ulEpsbId;
        }
        else
        {
            pstCnf->astSecParaInfo[pNode->ulCidIndex].ucPrimaryCid  = 0;
            pstCnf->astSecParaInfo[pNode->ulCidIndex].ucCid         = 0;
            pstCnf->astSecParaInfo[pNode->ulCidIndex].ucBearerId    = 0;
        }

        pNode->ulCidIndex++;
        if(pNode->ulCidIndex != pNode->ulCidNum)
        {
            /* 再次发起请求 */
            ret = l4a_FunRDPCidIndexReq((L4A_DATA_MSG_STRU*)pstReq, pstTable->ulPsReqMsgId, pstTable->ulPsReqPid, pNode->ulCidIndex);
            if(ERR_MSP_WAIT_ASYNC == ret)
            {
                L4A_INFO_LOG("%s %d.\n", __FUNCTION__, pNode->ulCidIndex);

                /* 返回异步状态，调用的地方要判断 */
                return ERR_MSP_WAIT_ASYNC;
            }
        }
    }

    for(i = 0, j = 0; i < pNode->ulCidNum; i++)
    {
        /* 5 <= bearerid <= 15，以此来判断是否是专有承载 */
        if(0 != pstCnf->astSecParaInfo[i].ucBearerId)
        {
            (VOS_VOID)VOS_MemCpy(&pstCnf->astSecParaInfo[j++], &pstCnf->astSecParaInfo[i], sizeof(APS_L4A_SEC_PDP_DYNAMIC_EXT_STRU));
        }
    }

    pstCnf->ulCidNum = j;

    ulsize = sizeof(APS_L4A_SET_CGSCONTRDP_CNF_STRU) + (pNode->ulCidNum * sizeof(APS_L4A_SEC_PDP_DYNAMIC_EXT_STRU));

    ret = l4aPacket2Aps(pstCnf, ulsize);

    (VOS_VOID)VOS_MemFree(MSP_L4_L4A_PID, pstCnf);

    return ret;
}


VOS_UINT32 l4a_FunCgscontrdpChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode)
{
    APS_L4A_SET_CGSCONTRDP_REQ_STRU *pstReq = (APS_L4A_SET_CGSCONTRDP_REQ_STRU*)(pNode->pData);
    APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU *pstCnf = (APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU *)(pData);

    L4A_VALID_PID_CHECK(pstReq, pstCnf);
}


VOS_VOID l4a_FunCgtftrdpPkj(APP_ESM_INQ_DYNAMIC_TFT_CNF_STRU* pstPsInqTftCnf, APS_L4A_SDF_PF_TFT_STRU *psttft)
{
    VOS_UINT32 j = 0;

    /* 调用的地方保证pstPsInqTftCnf、pstCgtftCnf不为空*/

    psttft->ulPfNum= pstPsInqTftCnf->ulPfNum;
    psttft->ulCid = pstPsInqTftCnf->ulCid;
    for(j = 0; j < pstPsInqTftCnf->ulPfNum; j++)
    {
        psttft->astTftInfo[j].bitOpPktFilterId = 1;
        psttft->astTftInfo[j].bitOpPrecedence = 1;
        psttft->astTftInfo[j].bitOpSrcIp = pstPsInqTftCnf->astPfInfo[j].bitOpRmtIpv4AddrAndMask;

        if(pstPsInqTftCnf->astPfInfo[j].bitOpRmtIpv4AddrAndMask)
        {
            psttft->astTftInfo[j].stSourceIpaddr.enPdpType = APS_L4A_PDP_IPV4;
            psttft->astTftInfo[j].stSourceIpMask.enPdpType = APS_L4A_PDP_IPV4;
            (VOS_VOID)VOS_MemCpy((VOS_VOID*)(psttft->astTftInfo[j].stSourceIpaddr.aucIpv4Addr),
            (VOS_VOID*)(pstPsInqTftCnf->astPfInfo[j].aucRmtIpv4Address), APP_MAX_IPV4_ADDR_LEN);

            (VOS_VOID)VOS_MemCpy((VOS_VOID*)(psttft->astTftInfo[j].stSourceIpMask.aucIpv4Addr),
            (VOS_VOID*)(pstPsInqTftCnf->astPfInfo[j].aucRmtIpv4Mask), APP_MAX_IPV4_ADDR_LEN);
        }
        if(pstPsInqTftCnf->astPfInfo[j].bitOpRmtIpv6AddrAndMask)
        {
            psttft->astTftInfo[j].stSourceIpaddr.enPdpType = APS_L4A_PDP_IPV6;
            psttft->astTftInfo[j].stSourceIpMask.enPdpType = APS_L4A_PDP_IPV6;
            (VOS_VOID)VOS_MemCpy((VOS_VOID*)(psttft->astTftInfo[j].stSourceIpaddr.aucIpv6Addr),
            (VOS_VOID*)(pstPsInqTftCnf->astPfInfo[j].aucRmtIpv6Address), APP_MAX_IPV6_ADDR_LEN);

            (VOS_VOID)VOS_MemCpy((VOS_VOID*)(psttft->astTftInfo[j].stSourceIpMask.aucIpv6Addr),
            (VOS_VOID*)(pstPsInqTftCnf->astPfInfo[j].aucRmtIpv6Mask), APP_MAX_IPV6_ADDR_LEN);
        }

        if((pstPsInqTftCnf->astPfInfo[j].bitOpRmtIpv4AddrAndMask)&&(pstPsInqTftCnf->astPfInfo[j].bitOpRmtIpv6AddrAndMask))
        {
            psttft->astTftInfo[j].stSourceIpaddr.enPdpType = APS_L4A_PDP_IPV4V6;
            psttft->astTftInfo[j].stSourceIpMask.enPdpType = APS_L4A_PDP_IPV4V6;
        }

        if ( pstPsInqTftCnf->astPfInfo[j].bitOpLocalIpv4AddrAndMask )
        {
            psttft->astTftInfo[j].bitOpLocalIpv4AddrAndMask = 1;
            (VOS_VOID)VOS_MemCpy((VOS_VOID*)(psttft->astTftInfo[j].aucLocalIpv4Addr),
                                 (VOS_VOID*)(pstPsInqTftCnf->astPfInfo[j].aucLocalIpv4Addr),
                                 APS_L4A_MAX_IPV4_ADDR_LEN);
            (VOS_VOID)VOS_MemCpy((VOS_VOID*)(psttft->astTftInfo[j].aucLocalIpv4Mask),
                                 (VOS_VOID*)(pstPsInqTftCnf->astPfInfo[j].aucLocalIpv4Mask),
                                 APS_L4A_MAX_IPV4_ADDR_LEN);
        }

        if ( pstPsInqTftCnf->astPfInfo[j].bitOpLocalIpv6AddrAndMask )
        {
            psttft->astTftInfo[j].bitOpLocalIpv6AddrAndMask = 1;
            (VOS_VOID)VOS_MemCpy((VOS_VOID*)(psttft->astTftInfo[j].aucLocalIpv6Addr),
                                 (VOS_VOID*)(pstPsInqTftCnf->astPfInfo[j].aucLocalIpv6Addr),
                                 APS_L4A_MAX_IPV6_ADDR_LEN);

            psttft->astTftInfo[j].ucLocalIpv6Prefix         = pstPsInqTftCnf->astPfInfo[j].ucLocalIpv6Prefix;
        }

        psttft->astTftInfo[j].bitOpProtocolId = pstPsInqTftCnf->astPfInfo[j].bitOpProtocolId;
        psttft->astTftInfo[j].bitOpSpi = pstPsInqTftCnf->astPfInfo[j].bitOpSecuParaIndex;
        psttft->astTftInfo[j].bitOpTosMask = pstPsInqTftCnf->astPfInfo[j].bitOpTypeOfService;
        psttft->astTftInfo[j].bitOpFlowLable = pstPsInqTftCnf->astPfInfo[j].bitOpFlowLabelType;
        psttft->astTftInfo[j].bitOpDirection = 1;

        psttft->astTftInfo[j].ucPacketFilterId = pstPsInqTftCnf->astPfInfo[j].ucPacketFilterId;
        psttft->astTftInfo[j].ucPrecedence = pstPsInqTftCnf->astPfInfo[j].ucPrecedence;

        psttft->astTftInfo[j].ucProtocolId = pstPsInqTftCnf->astPfInfo[j].ucProtocolId;

        if(pstPsInqTftCnf->astPfInfo[j].bitOpLocalPortRange)
        {
            psttft->astTftInfo[j].bitOpDestPortRange = 1;
            psttft->astTftInfo[j].usLowDestPort =pstPsInqTftCnf->astPfInfo[j].usLcPortLowLimit;
            psttft->astTftInfo[j].usHighDestPort = pstPsInqTftCnf->astPfInfo[j].usLcPortHighLimit;
        }
        else if(pstPsInqTftCnf->astPfInfo[j].bitOpSingleLocalPort)
        {
            psttft->astTftInfo[j].bitOpDestPortRange = 1;
            psttft->astTftInfo[j].usLowDestPort =pstPsInqTftCnf->astPfInfo[j].usSingleLcPort;
            psttft->astTftInfo[j].usHighDestPort = pstPsInqTftCnf->astPfInfo[j].usSingleLcPort;
        }
        else
        {
            psttft->astTftInfo[j].bitOpDestPortRange = 0;
        }

        if(pstPsInqTftCnf->astPfInfo[j].bitOpRemotePortRange)
        {
            psttft->astTftInfo[j].bitOpSrcPortRange = 1;
            psttft->astTftInfo[j].usLowSourcePort = pstPsInqTftCnf->astPfInfo[j].usRmtPortLowLimit;
            psttft->astTftInfo[j].usHighSourcePort = pstPsInqTftCnf->astPfInfo[j].usRmtPortHighLimit;
        }
        else if(pstPsInqTftCnf->astPfInfo[j].bitOpSingleRemotePort)
        {
            psttft->astTftInfo[j].bitOpSrcPortRange = 1;
            psttft->astTftInfo[j].usLowSourcePort = pstPsInqTftCnf->astPfInfo[j].usSingleRmtPort;
            psttft->astTftInfo[j].usHighSourcePort = pstPsInqTftCnf->astPfInfo[j].usSingleRmtPort;
        }
        else
        {
            psttft->astTftInfo[j].bitOpSrcPortRange = 0;
        }

        psttft->astTftInfo[j].ulSecuParaIndex = pstPsInqTftCnf->astPfInfo[j].ulSecuParaIndex;
        psttft->astTftInfo[j].ucTypeOfService = pstPsInqTftCnf->astPfInfo[j].ucTypeOfService;
        psttft->astTftInfo[j].ucTypeOfServiceMask = pstPsInqTftCnf->astPfInfo[j].ucTypeOfServiceMask;
        psttft->astTftInfo[j].ulFlowLable = pstPsInqTftCnf->astPfInfo[j].ulFlowLabelType;

        /* AT与NAS的协议相反*/
        /* (AT:  0-pre rel 7, 1-uplink,   2-downlink, 3-birectional)*/
        /* (NAS: 0-pre rel 7, 1-downlink, 2-uplink,   3-birectional)*/
        if(APP_ESM_TRANSFER_DIRECTION_UPLINK == pstPsInqTftCnf->astPfInfo[j].enDirection)
        {
            psttft->astTftInfo[j].enTftFilterDirection = 1;
        }
        else if(APP_ESM_TRANSFER_DIRECTION_DOWNLINK == pstPsInqTftCnf->astPfInfo[j].enDirection)
        {
            psttft->astTftInfo[j].enTftFilterDirection = 2;
        }
        else
        {
            psttft->astTftInfo[j].enTftFilterDirection = pstPsInqTftCnf->astPfInfo[j].enDirection;
        }

        psttft->astTftInfo[j].bitOpNwPktFilterId = 1;
        psttft->astTftInfo[j].ucNwPktFilterId = pstPsInqTftCnf->astPfInfo[j].ucNwPacketFilterId;
    }

    return ;
}

VOS_UINT32 l4a_FunPsCgtftrdpSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    APS_L4A_SET_CGTFTRDP_CNF_STRU *pstCnf = NULL;
    APP_ESM_INQ_DYNAMIC_TFT_CNF_STRU *pstPsInqTftCnf=NULL;
    VOS_UINT32 ulsize;
    VOS_UINT32 ret;
    L4A_RX_INFO_STRU *pNode = NULL;
    L4A_ONLY_CID_COMM_REQ_STRU *pstReq = NULL;

    pNode = l4a_GetExeCmdNode(pstTable->ulAtReqMsgId, L4A_REQ_FLAG);
    if((NULL == pNode) || (NULL == pNode->pData) || (NULL == pData))
    {
        L4A_INFO_LOG("%s %d failed.\n", __FUNCTION__, __LINE__);

        /* 找不到请求节点，靠AT/TAF超时机制返回ERROR */
        return ERR_MSP_SUCCESS;
    }

    pstPsInqTftCnf = (APP_ESM_INQ_DYNAMIC_TFT_CNF_STRU *)(pData);
    pstReq = pNode->pData;

    if(0 == pNode->ulCidNum)
    {
        pNode->ulCidNum = l4a_GetValidCidNum(pstReq->aucCid);
        if(0 == pNode->ulCidNum)
        {
            L4A_INFO_LOG("%s %d failed.\n", __FUNCTION__, __LINE__);

            return ERR_MSP_SUCCESS;
        }
        
        L4A_INFO_LOG("%s %d.\n", __FUNCTION__, pNode->ulCidNum); /* [false alarm]: 屏蔽Fortify错误 */

        ulsize = sizeof(APS_L4A_SET_CGTFTRDP_CNF_STRU) \
            + (pNode->ulCidNum * sizeof(APS_L4A_SDF_PF_TFT_STRU)); /* [false alarm]: 屏蔽Fortify错误 */

        pstCnf = VOS_MemAlloc(MSP_L4_L4A_PID, DYNAMIC_MEM_PT, ulsize);
        if(NULL == pstCnf)
        {
            /* 申请内存失败，靠AT/TAF超时机制返回ERROR */
            return ERR_MSP_SUCCESS;
        }

        pNode->pCnfData = pstCnf;

        pstCnf->enMsgId             = pstTable->ulAtCnfMsgId;
        pstCnf->stCtrl.ulPid        = pstPsInqTftCnf->ulOpId;
        pstCnf->stCtrl.ulClientId   = (VOS_UINT32)usClientId;
        pstCnf->ulCidNum            = pNode->ulCidNum;
    }
    else
    {
        if(NULL == pNode->pCnfData)
        {
            L4A_INFO_LOG("%s %d failed.\n", __FUNCTION__, __LINE__);
            
            return ERR_MSP_SUCCESS;
        }
        pstCnf = pNode->pCnfData;
    }

    pstCnf->ulErrorCode = pstPsInqTftCnf->ulRslt;

    /* 如果成功先保存应答信息，然后判断是否最后一个处理的cid，如果失败直接应答给AT/TAF */
    if(ERR_MSP_SUCCESS == pstCnf->ulErrorCode)
    {
        l4a_FunCgtftrdpPkj(pstPsInqTftCnf, &pstCnf->astPfTftInfo[pNode->ulCidIndex]);

        pNode->ulCidIndex++;
        if(pNode->ulCidIndex != pNode->ulCidNum)
        {
            /* 再次发起请求 */
            ret = l4a_FunRDPCidIndexReq((L4A_DATA_MSG_STRU*)pstReq, pstTable->ulPsReqMsgId, pstTable->ulPsReqPid, pNode->ulCidIndex);
            if(ERR_MSP_WAIT_ASYNC == ret)
            {
                L4A_INFO_LOG("%s %d.\n", __FUNCTION__, pNode->ulCidIndex);

                /* 返回异步状态，调用的地方要判断 */
                return ERR_MSP_WAIT_ASYNC;
            }
        }
    }

    ulsize = sizeof(APS_L4A_SET_CGTFTRDP_CNF_STRU) + (pNode->ulCidNum * sizeof(APS_L4A_SDF_PF_TFT_STRU));
    ret = l4aPacket2Aps(pstCnf, ulsize);

    (VOS_VOID)VOS_MemFree(MSP_L4_L4A_PID, pstCnf);

    return ret;
}


VOS_UINT32 l4a_FunCgtftrdpChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode)
{
    L4A_ONLY_CID_COMM_REQ_STRU *pstReq = (L4A_ONLY_CID_COMM_REQ_STRU*)(pNode->pData);
    APP_ESM_INQ_DYNAMIC_TFT_CNF_STRU *pstCnf = (APP_ESM_INQ_DYNAMIC_TFT_CNF_STRU *)(pData);

    L4A_VALID_PID_CHECK(pstReq, pstCnf);
}


VOS_UINT32 l4a_FunPsCgeqosSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_ESM_SET_EPS_QOS_REQ_STRU stReq= {0};
    APS_L4A_SET_CGEQOS_REQ_STRU *pstReq = NULL;

    pstReq = (APS_L4A_SET_CGEQOS_REQ_STRU*)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulOpId = pstReq->stCtrl.ulPid;
    stReq.ulCid = pstReq->stCgeqosInfo.ucCid ;

    if(0 == pstReq->stCgeqosInfo.bitOpQCI)
    {
        stReq.enSetType = APP_ESM_PARA_DELETE; /* 0:set, 1:del*/
    }
    else
    {
       stReq.enSetType = APP_ESM_PARA_SETTING; /* 0:set, 1:del*/

       /* 协议栈与AT不对应 */
       stReq.stSdfQosInfo.ucQCI = pstReq->stCgeqosInfo.ucValQCI;
       stReq.stSdfQosInfo.ulDLGMaxRate = pstReq->stCgeqosInfo.ulValDLGBR;
       stReq.stSdfQosInfo.ulULGMaxRate = pstReq->stCgeqosInfo.ulValULGBR;
       stReq.stSdfQosInfo.ulDLMaxRate = pstReq->stCgeqosInfo.ulValDLMBR;
       stReq.stSdfQosInfo.ulULMaxRate = pstReq->stCgeqosInfo.ulValULMBR;
    }

    return  l4aPacket2Ps(ulPsReqPid,&stReq, sizeof(APP_ESM_SET_EPS_QOS_REQ_STRU));
}


VOS_UINT32 l4a_FunCgeqosChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode)
{
    APS_L4A_SET_CGEQOS_REQ_STRU *pstReq = (APS_L4A_SET_CGEQOS_REQ_STRU*)(pNode->pData);
    APP_ESM_PARA_SET_CNF_STRU *pstCnf = (APP_ESM_PARA_SET_CNF_STRU *)(pData);

    L4A_VALID_PID_CHECK(pstReq, pstCnf);
}


VOS_UINT32 l4a_FunPsCgeqosrdpSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    APS_L4A_SET_CGEQOSRDP_CNF_STRU *pstCnf    = NULL;
    APP_ESM_INQ_DYNAMIC_EPS_QOS_CNF_STRU *pstEsmCnf=NULL;
    VOS_UINT32 ulsize;
    VOS_UINT32 ret;
    L4A_RX_INFO_STRU *pNode = NULL;
    L4A_ONLY_CID_COMM_REQ_STRU *pstReq = NULL;

    pNode = l4a_GetExeCmdNode(pstTable->ulAtReqMsgId, L4A_REQ_FLAG);
    if((NULL == pNode) || (NULL == pNode->pData) || (NULL == pData))
    {
        L4A_INFO_LOG("%s %d failed.\n", __FUNCTION__, __LINE__);

        /* 找不到请求节点，靠AT/TAF超时机制返回ERROR */
        return ERR_MSP_SUCCESS;
    }

    pstEsmCnf = (APP_ESM_INQ_DYNAMIC_EPS_QOS_CNF_STRU *)(pData);
    pstReq = pNode->pData;

    if(0 == pNode->ulCidNum)
    {
        pNode->ulCidNum = l4a_GetValidCidNum(pstReq->aucCid);
        if(0 == pNode->ulCidNum)
        {
            L4A_INFO_LOG("%s %d failed.\n", __FUNCTION__, __LINE__);
            
            return ERR_MSP_SUCCESS;
        }
        
        L4A_INFO_LOG("%s %d.\n", __FUNCTION__, pNode->ulCidNum); /* [false alarm]: 屏蔽Fortify错误 */

        ulsize = sizeof(APS_L4A_SET_CGEQOSRDP_CNF_STRU) \
            + (pNode->ulCidNum * sizeof(APS_L4A_EPS_QOS_EXT_STRU)); /* [false alarm]: 屏蔽Fortify错误 */

        pstCnf = VOS_MemAlloc(MSP_L4_L4A_PID, DYNAMIC_MEM_PT, ulsize);
        if(NULL == pstCnf)
        {
            /* 申请内存失败，靠AT/TAF超时机制返回ERROR */
            return ERR_MSP_SUCCESS;
        }

        pNode->pCnfData = pstCnf;

        pstCnf->enMsgId             = pstTable->ulAtCnfMsgId;
        pstCnf->stCtrl.ulPid        = pstEsmCnf->ulOpId;
        pstCnf->stCtrl.ulClientId   = (VOS_UINT32)usClientId;
        pstCnf->ulCidNum            = pNode->ulCidNum;
    }
    else
    {
        if(NULL == pNode->pCnfData)
        {
            L4A_INFO_LOG("%s %d failed.\n", __FUNCTION__, __LINE__);
            
            return ERR_MSP_SUCCESS;
        }
        pstCnf = pNode->pCnfData;
    }

    pstCnf->ulErrorCode = pstEsmCnf->ulRslt;
    
    /* 如果成功先保存应答信息，然后判断是否最后一个处理的cid，如果失败直接应答给AT/TAF */
    if(ERR_MSP_SUCCESS == pstCnf->ulErrorCode)
    {
        pstCnf->astEpsQosInfo[pNode->ulCidIndex].ucCid   = (VOS_UINT8)pstEsmCnf->ulCid;
        pstCnf->astEpsQosInfo[pNode->ulCidIndex].ucQCI   = pstEsmCnf->stSdfQosInfo.ucQCI;
        pstCnf->astEpsQosInfo[pNode->ulCidIndex].ulDLGBR = pstEsmCnf->stSdfQosInfo.ulDLGMaxRate;
        pstCnf->astEpsQosInfo[pNode->ulCidIndex].ulULGBR = pstEsmCnf->stSdfQosInfo.ulULGMaxRate;
        pstCnf->astEpsQosInfo[pNode->ulCidIndex].ulDLMBR = pstEsmCnf->stSdfQosInfo.ulDLMaxRate;
        pstCnf->astEpsQosInfo[pNode->ulCidIndex].ulULMBR = pstEsmCnf->stSdfQosInfo.ulULMaxRate;
        pstCnf->astEpsQosInfo[pNode->ulCidIndex].bitOpQCI   = 1;
        pstCnf->astEpsQosInfo[pNode->ulCidIndex].bitOpDLGBR = 1;
        pstCnf->astEpsQosInfo[pNode->ulCidIndex].bitOpULGBR = 1;
        pstCnf->astEpsQosInfo[pNode->ulCidIndex].bitOpDLMBR = 1;
        pstCnf->astEpsQosInfo[pNode->ulCidIndex].bitOpULMBR = 1;

        pNode->ulCidIndex++;
        if(pNode->ulCidIndex != pNode->ulCidNum)
        {
            /* 再次发起请求 */
            ret = l4a_FunRDPCidIndexReq((L4A_DATA_MSG_STRU*)pstReq, pstTable->ulPsReqMsgId, pstTable->ulPsReqPid, pNode->ulCidIndex);
            if(ERR_MSP_WAIT_ASYNC == ret)
            {
                L4A_INFO_LOG("%s %d.\n", __FUNCTION__, pNode->ulCidIndex);
                
                /* 返回异步状态，调用的地方要判断 */
                return ERR_MSP_WAIT_ASYNC;
            }
        }
    }

    ulsize = sizeof(APS_L4A_SET_CGEQOSRDP_CNF_STRU) + (pNode->ulCidNum * sizeof(APS_L4A_EPS_QOS_EXT_STRU));

    ret = l4aPacket2Aps(pstCnf, ulsize);

    (VOS_VOID)VOS_MemFree(MSP_L4_L4A_PID, pstCnf);

    return ret;
}


VOS_UINT32 l4a_FunCgeqosrdpChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode)
{
    L4A_ONLY_CID_COMM_REQ_STRU *pstReq = (L4A_ONLY_CID_COMM_REQ_STRU*)(pNode->pData);
    APP_ESM_INQ_DYNAMIC_EPS_QOS_CNF_STRU *pstCnf = (APP_ESM_INQ_DYNAMIC_EPS_QOS_CNF_STRU *)(pData);

    L4A_VALID_PID_CHECK(pstReq, pstCnf);
}

VOS_UINT32 l4a_FunPsAbortSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_ESM_PROCEDURE_ABORT_NOTIFY_STRU stReq= {0};
    APS_L4A_ABORT_REQ_STRU* pstReq = (APS_L4A_ABORT_REQ_STRU*)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulCid   = pstReq->ucCid;

    return l4aPacket2PsNoCnf(ulPsReqPid, &stReq, sizeof(APP_ESM_PROCEDURE_ABORT_NOTIFY_STRU));
}

VOS_UINT32 l4a_FunPsIpv6SetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_ESM_IPV6_INFO_NOTIFY_STRU stReq = {0};
    APS_L4A_IPV6_INFO_NOTIFY_IND_STRU*  pstReq = (APS_L4A_IPV6_INFO_NOTIFY_IND_STRU*)(pData);

    /* 打包stIpv6InfoNotify数据*/
    stReq.ulMsgId         = ulPsReqMsgId;
    stReq.ucEpsbId        = pstReq->ucRabId;
    stReq.ucIpv6PrefixNum = pstReq->ucIpv6PrefixNum;
    (VOS_VOID)VOS_MemCpy(stReq.astIpv6PrefixArray, pstReq->astIpv6PrefixArray, \
        APP_ESM_MAX_IPV6_PREFIX_NUM*sizeof(APP_ESM_IPV6_PREFIX_STRU));

    return l4aPacket2PsNoCnf(ulPsReqPid, &stReq, sizeof(APP_ESM_IPV6_INFO_NOTIFY_STRU));
}


VOS_UINT32 l4a_FunIndCfgSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    L4A_IND_CFG_REQ_STRU *pstReq = (L4A_IND_CFG_REQ_STRU*)(pData);
    VOS_UINT32 i;

    if(pstReq->stIndCfg.curc_bit_valid)
    {
        /* AT转换字符串时是按逆序存储的，L4A转换成正序 */
        for(i = 0; i < L4A_CURC_RPT_CFG_MAX_SIZE; i++)
        {
            g_aucL4aCurcRptCfg[i] = pstReq->stIndCfg.aucCurcCfgReq[L4A_CURC_RPT_CFG_MAX_SIZE - 1 - i];
        }
    }

    if(pstReq->stIndCfg.anlevel_bit_valid)
    {
        L4A_INFO_LOG("l4a curc set anlevel\n");
        L4A_SetRptCmdStatus(L4A_RPT_CMD_ANLEVEL, pstReq->stIndCfg.anlevel_bit);
    }

    if(pstReq->stIndCfg.rssi_bit_valid)
    {
        L4A_INFO_LOG("l4a curc set rssi\n");
        L4A_SetRptCmdStatus(L4A_RPT_CMD_RSSI, pstReq->stIndCfg.rssi_bit);
    }

    if(pstReq->stIndCfg.lwurc_bit_valid)
    {
        L4A_INFO_LOG("l4a curc set lwurc\n");
        L4A_SetRptCmdStatus(L4A_RPT_CMD_LWURC, pstReq->stIndCfg.lwurc_bit);
    }

    if(pstReq->stIndCfg.mode_bit_valid)
    {
        L4A_INFO_LOG("l4a curc set mode\n");
        L4A_SetRptCmdStatus(L4A_RPT_CMD_MODE, pstReq->stIndCfg.mode_bit);
    }

    if(pstReq->stIndCfg.cerssi_bit_valid)
    {
        L4A_INFO_LOG("l4a curc set cerssi\n");
        L4A_SetRptCmdStatus(L4A_RPT_CMD_CERSSI, pstReq->stIndCfg.cerssi_bit);
    }
    
    if(pstReq->stIndCfg.lcacell_bit_valid)
    {
        L4A_INFO_LOG("l4a curc set lcacellurc\n");
        L4A_SetRptCmdStatus(L4A_RPT_CMD_LCACELLURC, pstReq->stIndCfg.lcacell_bit);
    }

    return ERR_MSP_SUCCESS;
}

VOS_UINT32 l4a_FunCsqInd(L4A_PS_MSG_STRU* pData)
{
    RRC_APP_CSQ_IND_STRU *pstPsCsqInd = NULL;
    L4A_CSQ_INFO_IND_STRU stCsqInd = {0};
    VOS_UINT32 ret = ERR_MSP_SUCCESS;

    pstPsCsqInd = (RRC_APP_CSQ_IND_STRU *)(pData);

    /*协议栈保存的值是8倍精度*/
    stCsqInd.sRssi = ((99 == pstPsCsqInd->sRssi)?99:pstPsCsqInd->sRssi/8);
    stCsqInd.sRsrp = ((99 == pstPsCsqInd->sRsrp)?99:pstPsCsqInd->sRsrp/8);
    stCsqInd.sRsrq = ((99 == pstPsCsqInd->sRsrq)?99:pstPsCsqInd->sRsrq/8);

    stCsqInd.lSINR      = pstPsCsqInd->lSINR;
    stCsqInd.stCQI.usRI       = pstPsCsqInd->stCQI.usRI;
    stCsqInd.stCQI.ausCQI[0]   = pstPsCsqInd->stCQI.ausCQI[0];
    stCsqInd.stCQI.ausCQI[1]   = pstPsCsqInd->stCQI.ausCQI[1];

    if(VOS_TRUE == L4A_GetRptCmdStatus(L4A_RPT_CMD_RSSI))
    {
        stCsqInd.enMsgId = ID_MSG_L4A_RSSI_IND;
        ret |= l4aPacket2At(&stCsqInd, sizeof(L4A_CSQ_INFO_IND_STRU));
    }
    if(VOS_TRUE == L4A_GetRptCmdStatus(L4A_RPT_CMD_CERSSI))
    {
        stCsqInd.enMsgId = ID_MSG_L4A_CERSSI_IND;
        ret |= l4aPacket2At(&stCsqInd, sizeof(L4A_CSQ_INFO_IND_STRU));
    }
    if(VOS_TRUE == L4A_GetRptCmdStatus(L4A_RPT_CMD_ANLEVEL))
    {
        stCsqInd.enMsgId = ID_MSG_L4A_ANLEVEL_IND;
        ret |= l4aPacket2At(&stCsqInd, sizeof(L4A_CSQ_INFO_IND_STRU));
    }
    return ret;
}


VOS_UINT32 L4aPktSdfInfo(APS_L4A_SDF_PARA_STRU* pstSdfParaInfo,APP_ESM_SDF_PARA_STRU* pstSdfPara)
{
    VOS_UINT32 i = 0;
    
    if((NULL == pstSdfParaInfo) || (NULL == pstSdfPara))
    {
        return ERR_MSP_FAILURE;
    }

    pstSdfPara->bitOpPdnType             = pstSdfParaInfo->bitOpPdnType;
    pstSdfPara->bitOpApn                 = pstSdfParaInfo->bitOpApn;
    pstSdfPara->bitOpSdfQos              = pstSdfParaInfo->bitOpSdfQos;
    pstSdfPara->bitOpLinkdCId            = pstSdfParaInfo->bitOpLinkdCId;
    pstSdfPara->bitIpv4AddrAllocType     = pstSdfParaInfo->bitIpv4AddrAllocType;
    pstSdfPara->bitOpGwAuthInfo          = pstSdfParaInfo->bitOpGwAuthInfo;
    pstSdfPara->bitOpSpare               = pstSdfParaInfo->bitOpSpare;
#if 1
    pstSdfPara->bitOpPcscfDiscovery      = pstSdfParaInfo->bitOpPcscfDiscovery;
    pstSdfPara->bitOpImsCnSignalFlag     = pstSdfParaInfo->bitOpImsCnSignalFlag;
#endif
    pstSdfPara->enPdnType                = pstSdfParaInfo->enPdnType;
    pstSdfPara->enIpv4AddrAllocType      = pstSdfParaInfo->enIpv4AddrAllocType;
    pstSdfPara->ulCId                    = pstSdfParaInfo->ulCid;
    pstSdfPara->ulLinkdCId               = pstSdfParaInfo->ulLinkdCid;
    pstSdfPara->ulPfNum                  = pstSdfParaInfo->ulPfNum;
#if 0
    pstSdfPara->enBearerCntxtType        = pstSdfParaInfo->enBearerCntxtType;
#else
    pstSdfPara->enPcscfDiscovery         = pstSdfParaInfo->enPcscfDiscovery;
    pstSdfPara->enImsCnSignalFlag        = pstSdfParaInfo->enImsCnSignalFlag;

    if((pstSdfParaInfo->bitOpEmergencyInd) && (APS_L4A_PDP_FOR_EMC == pstSdfParaInfo->enEmergencyInd))
    {
        pstSdfPara->enBearerCntxtType    = APP_ESM_BEARER_TYPE_EMERGENCY;
    }
    else
    {
        pstSdfPara->enBearerCntxtType    = pstSdfParaInfo->enBearerCntxtType;
    }
#endif

    (VOS_VOID)VOS_MemCpy(&(pstSdfPara->stSdfQosInfo), &(pstSdfParaInfo->stSdfQosInfo), sizeof(APP_ESM_EPS_QOS_INFO_STRU));
    pstSdfPara->stApnInfo.ucApnLen       = pstSdfParaInfo->stApnInfo.ucApnLen;
    (VOS_VOID)VOS_MemCpy(pstSdfPara->stApnInfo.aucApnName, pstSdfParaInfo->stApnInfo.aucApnName, APP_MAX_APN_LEN);

    /*(VOS_VOID)VOS_MemCpy(&(pstSdfPara->stGwAuthInfo), &(pstSdfParaInfo->stGwAuthInfo), sizeof(APP_ESM_GW_AUTH_INFO_STRU));注意，这里两个USERNAME长度不同，有待确认    */
    pstSdfPara->stGwAuthInfo.enGwAuthType = (VOS_UINT8)pstSdfParaInfo->stGwAuthInfo.enGwAuthType;
    pstSdfPara->stGwAuthInfo.ucAccNumLen  = pstSdfParaInfo->stGwAuthInfo.ucAccNumLen;
    pstSdfPara->stGwAuthInfo.ucPwdLen     = pstSdfParaInfo->stGwAuthInfo.ucPwdLen;
    pstSdfPara->stGwAuthInfo.ucUserNameLen= pstSdfParaInfo->stGwAuthInfo.ucUserNameLen;
    (VOS_VOID)VOS_MemCpy(pstSdfPara->stGwAuthInfo.auAccessNum, pstSdfParaInfo->stGwAuthInfo.auAccessNum, APP_ESM_MAX_ACCESS_NUM_LEN);
    (VOS_VOID)VOS_MemCpy(pstSdfPara->stGwAuthInfo.aucUserName, pstSdfParaInfo->stGwAuthInfo.aucUserName, APP_ESM_MAX_USER_NAME_LEN);
    (VOS_VOID)VOS_MemCpy(pstSdfPara->stGwAuthInfo.aucPwd, pstSdfParaInfo->stGwAuthInfo.aucPwd, APP_ESM_MAX_PASSWORD_LEN);

    for(i = 0; i < pstSdfParaInfo->ulPfNum; i++)
    {
        (VOS_VOID)VOS_MemCpy(pstSdfPara->astCntxtTftInfo + i, pstSdfParaInfo->astCntxtTftInfo + i, sizeof(APP_ESM_TFT_INFO_STRU));
/*
        if((1 == pstSdfParaInfo->astCntxtTftInfo[i].OP_SourceIpAddr) && (1 == pstSdfParaInfo->astCntxtTftInfo[i].OP_SourceIpMask))
        {
            pstSdfPara->astCntxtTftInfo[i].bitOpRmtIpv4AddrAndMask = 1;
        }

        if((1 == pstSdfParaInfo->astCntxtTftInfo[i].OP_SourceIpv6Addr) && (1 == pstSdfParaInfo->astCntxtTftInfo[i].OP_SourceIpv6Mask))
        {
            pstSdfPara->astCntxtTftInfo[i].bitOpRmtIpv6AddrAndMask = 1;
        }

        if((1 == pstSdfParaInfo->astCntxtTftInfo[i].OP_HighDestPort) && (1 == pstSdfParaInfo->astCntxtTftInfo[i].OP_LowDestPort))
        {
            pstSdfPara->astCntxtTftInfo[i].bitOpRemotePortRange = 1;
        }

        if((1 == pstSdfParaInfo->astCntxtTftInfo[i].OP_HighSourcePort) && (1 == pstSdfParaInfo->astCntxtTftInfo[i].OP_LowSourcePort))
        {
            pstSdfPara->astCntxtTftInfo[i].bitOpLocalPortRange = 1;
        }

        pstSdfPara->astCntxtTftInfo[i].bitOpProtocolId          = pstSdfParaInfo->astCntxtTftInfo[i].OP_ProtocolId;
        
        pstSdfPara->astCntxtTftInfo[i].bitOpSecuParaIndex       = pstSdfParaInfo->astCntxtTftInfo[i].OP_ulSecuParaIndex;
        pstSdfPara->astCntxtTftInfo[i].bitOpTypeOfService       = pstSdfParaInfo->astCntxtTftInfo[i].OP_ucTypeOfService;

        pstSdfPara->astCntxtTftInfo[i].ucPacketFilterId         = pstSdfParaInfo->astCntxtTftInfo[i].ucPacketFilterId;
        pstSdfPara->astCntxtTftInfo[i].ucNwPacketFilterId       = pstSdfParaInfo->astCntxtTftInfo[i].ucNwPacketFilterId;
        pstSdfPara->astCntxtTftInfo[i].enDirection              = pstSdfParaInfo->astCntxtTftInfo[i].enDirection;
        pstSdfPara->astCntxtTftInfo[i].ucPrecedence             = pstSdfParaInfo->astCntxtTftInfo[i].ucPrecedence;
        pstSdfPara->astCntxtTftInfo[i].ulSecuParaIndex          = pstSdfParaInfo->astCntxtTftInfo[i].ulSecuParaIndex;

        pstSdfPara->astCntxtTftInfo[i].usLcPortHighLimit        = pstSdfParaInfo->astCntxtTftInfo[i].usHighSourcePort;
        pstSdfPara->astCntxtTftInfo[i].usLcPortLowLimit         = pstSdfParaInfo->astCntxtTftInfo[i].usLowSourcePort;
        
        if(pstSdfParaInfo->astCntxtTftInfo[i].usHighSourcePort == pstSdfParaInfo->astCntxtTftInfo[i].usLowSourcePort)
        {
            pstSdfPara->astCntxtTftInfo[i].bitOpSingleLocalPort = 1;
            pstSdfPara->astCntxtTftInfo[i].usSingleLcPort   = pstSdfParaInfo->astCntxtTftInfo[i].usHighSourcePort;
        }

        pstSdfPara->astCntxtTftInfo[i].usRmtPortHighLimit   = pstSdfParaInfo->astCntxtTftInfo[i].usHighDestPort;
        pstSdfPara->astCntxtTftInfo[i].usRmtPortLowLimit    = pstSdfParaInfo->astCntxtTftInfo[i].usLowDestPort;

        if(pstSdfParaInfo->astCntxtTftInfo[i].usHighDestPort == pstSdfParaInfo->astCntxtTftInfo[i].usLowDestPort)
        {
            pstSdfPara->astCntxtTftInfo[i].bitOpSingleRemotePort = 1;
            pstSdfPara->astCntxtTftInfo[i].usSingleRmtPort = pstSdfParaInfo->astCntxtTftInfo[i].usHighDestPort;
        }

        pstSdfPara->astCntxtTftInfo[i].ucProtocolId             = pstSdfParaInfo->astCntxtTftInfo[i].OP_ProtocolId;
        pstSdfPara->astCntxtTftInfo[i].ucTypeOfService          = pstSdfParaInfo->astCntxtTftInfo[i].ucTypeOfService;
        pstSdfPara->astCntxtTftInfo[i].ucTypeOfServiceMask      = pstSdfParaInfo->astCntxtTftInfo[i].ucTypeOfServiceMask;

        VOS_MemCpy(pstSdfPara->astCntxtTftInfo[i].aucRmtIpv4Address, pstSdfParaInfo->astCntxtTftInfo[i].aucSourceIpAddr + 1, pstSdfParaInfo->astCntxtTftInfo[i].aucSourceIpAddr[0]);
        VOS_MemCpy(pstSdfPara->astCntxtTftInfo[i].aucRmtIpv4Mask, pstSdfParaInfo->astCntxtTftInfo[i].aucSourceIpMask + 1, pstSdfParaInfo->astCntxtTftInfo[i].aucSourceIpMask[0]);
        VOS_MemCpy(pstSdfPara->astCntxtTftInfo[i].aucRmtIpv6Address, pstSdfParaInfo->astCntxtTftInfo[i].aucRmtIpv6Address + 1, pstSdfParaInfo->astCntxtTftInfo[i].aucRmtIpv6Address[0]);
        VOS_MemCpy(pstSdfPara->astCntxtTftInfo[i].aucRmtIpv6Mask, pstSdfParaInfo->astCntxtTftInfo[i].aucRmtIpv6Mask + 1, pstSdfParaInfo->astCntxtTftInfo[i].aucRmtIpv6Mask[0]);

        pstSdfPara->astCntxtTftInfo[i].ulFlowLabelType          = pstSdfParaInfo->astCntxtTftInfo[i].ulFlowLableType;
*/
    }

    return ERR_MSP_SUCCESS;
}

VOS_UINT32 APP_GetSdfPara(VOS_UINT32 *pulSdfNum,APP_ESM_SDF_PARA_STRU *pstSdfPara)
{
    VOS_UINT32 ret = APP_FAILURE;
    VOS_UINT8 ucCid = 0;
    APS_L4A_SDF_PARA_STRU* pstSdfParaInfo = NULL;

    if((NULL == pulSdfNum)||(NULL == pstSdfPara))
    {
        return APP_FAILURE;
    }

    pstSdfParaInfo =
        (APS_L4A_SDF_PARA_STRU*)VOS_MemAlloc(MSP_L4_L4A_PID, DYNAMIC_MEM_PT, sizeof(APS_L4A_SDF_PARA_STRU));

    if(NULL == pstSdfParaInfo)
    {
        return APP_FAILURE;
    }

    (VOS_VOID)VOS_MemSet((VOS_VOID*)pstSdfParaInfo, 0, sizeof(APS_L4A_SDF_PARA_STRU));

    ucCid = (VOS_UINT8)(pstSdfPara->ulCId);
    
    ret = TAF_APS_GetCidSdfParaInfo(ucCid,pstSdfParaInfo);

    if(VOS_ERR == ret)
    {
        ret = APP_FAILURE;
    }
    else
    {
        (VOS_VOID)L4aPktSdfInfo(pstSdfParaInfo,pstSdfPara);

        *pulSdfNum = 1;
        ret        = APP_SUCCESS;
    }

    (VOS_VOID)VOS_MemFree(MSP_L4_L4A_PID, pstSdfParaInfo);

    return ret;
}

VOS_UINT32 APP_GetPdpManageInfo(APP_ESM_PDP_MANAGE_INFO_STRU *pstPdpManageInfo)
{
    VOS_UINT32 ret = APP_FAILURE;

    APS_L4A_PDP_MANAGE_INFO_STRU* pstApsPdpMngInfo = NULL;

    if(NULL == pstPdpManageInfo)
    {
        return APP_FAILURE;
    }
    
    pstApsPdpMngInfo = 
        (APS_L4A_PDP_MANAGE_INFO_STRU*)VOS_MemAlloc(MSP_L4_L4A_PID, DYNAMIC_MEM_PT, sizeof(APS_L4A_PDP_MANAGE_INFO_STRU));

    if(NULL == pstApsPdpMngInfo)
    {
        return APP_FAILURE;
    }
    
    ret = TAF_APS_GetPdpManageInfo(pstApsPdpMngInfo);

    if(VOS_ERR == ret)
    {
        (VOS_VOID)VOS_MemFree(MSP_L4_L4A_PID, pstApsPdpMngInfo);
        return APP_FAILURE;
    }

    pstPdpManageInfo->enMode = (APP_ESM_BEARER_MANAGE_MODE_ENUM_UINT8)pstApsPdpMngInfo->enMode;
    pstPdpManageInfo->enType = (APP_ESM_BEARER_MANAGE_TYPE_ENUM_UINT8)pstApsPdpMngInfo->enType;

    (VOS_VOID)VOS_MemFree(MSP_L4_L4A_PID, pstApsPdpMngInfo);

    return APP_SUCCESS;
}

/*****************************************************************************
 函 数 名  : APP_GetCidImsSuppFlag
 功能描述  : 获取CID对应的IMS配置
 输入参数  : ucCid                      - CID
 输出参数  : pucImsSuppFlag             - CID支持IMS配置
 返 回 值  : APP_FAILURE                - 函数执行异常
             APP_SUCCESS                - 函数执行成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月1日
    作    者   : z00301431
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 APP_GetCidImsSuppFlag(VOS_UINT8 ucCid ,VOS_UINT8 *pucImsSuppFlag)
{
    if(NULL == pucImsSuppFlag)
    {
        return APP_FAILURE;
    }

    *pucImsSuppFlag = TAF_APS_GetCidImsCfgFlag(ucCid);

    return APP_SUCCESS;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



