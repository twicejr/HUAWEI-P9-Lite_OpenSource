 


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*lint --e{740}*/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "l4a_proc.h"
#include  "l4a_fun.h"
#include  "taf_drx.h"

#define    THIS_FILE_ID        MSP_FILE_ID_L4A_PROC_C

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

HI_LIST_S g_stL4aNodeHead = {0};
VOS_SEM g_ulL4aNodeSem = 0;
VOS_SEM g_ulL4aMbxSem = 0;

L4A_MNTN_INFO_STRU g_stmntn;

VOS_UINT8 g_aucL4aCurcRptCfg[L4A_CURC_RPT_CFG_MAX_SIZE] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

static L4A_FW_MSG_FUN_TABLE_STRU g_astRpiMsgFunTable[] = {

    {ID_MSG_L4A_LWCLASHQRY_REQ,     ID_APP_RRC_LWCLASH_REQ,             PS_PID_ERRC,    l4a_FunPsLwclashReadReq,
        ID_RRC_APP_LWCLASH_CNF,         (PFN_L4A_CNF)l4a_FunPsLwclashReadCnf,    ID_MSG_L4A_LWCLASHQRY_CNF,
        NULL,                       "^LWCLASH"},

    {ID_MSG_L4A_ISMCOEXSET_REQ,     ID_LMSP_LPHY_LTE_WIFI_COEX_SET_REQ, MSP_L4_L4A_PID, l4a_FunLteWifiReq,
        ID_LMSP_LPHY_LTE_WIFI_COEX_SET_CNF,(PFN_L4A_CNF)l4a_FunLteWifiCnf,       ID_MSG_L4A_ISMCOEXSET_CNF,
        NULL,                       "^ISMCOEX"},

    {ID_MSG_L4A_RADVER_SET_REQ,     ID_APP_LRRC_SET_UE_REL_VERSION_REQ, PS_PID_ERRC,    l4a_FunRadverReq,
        ID_LRRC_APP_SET_UE_REL_VERSION_CNF,(PFN_L4A_CNF)l4a_FunRadverCnf,       ID_MSG_L4A_RADVER_SET_CNF,
        NULL,                       "^RADVER"},

    {ID_MSG_L4A_CNMR_REQ,           ID_APP_RRC_NMR_REQ,                 PS_PID_ERRC,    l4a_FunPsCnmrReadReq,
        ID_RRC_APP_NMR_CNF,             (PFN_L4A_CNF)l4a_FunPsCnmrReadCnf,       ID_MSG_L4A_CNMR_CNF,
        NULL,                       "^CNMR"},

    {ID_MSG_L4A_CERSSI_REQ,         ID_APP_RRC_CSQ_REQ,                 PS_PID_ERRC,    l4a_FunPsCsqReadReq,
        ID_RRC_APP_CSQ_CNF,             (PFN_L4A_CNF)l4a_FunPsCsqReadCnf,        ID_MSG_L4A_CERSSI_CNF,
        NULL,                       "^CERSSI"},

    {ID_MSG_L4A_CERSSI_INQ_REQ,     ID_APP_RRC_CSQ_REQ,                 PS_PID_ERRC,    l4a_FunPsCsqReadReq,
        ID_RRC_APP_CSQ_CNF,             (PFN_L4A_CNF)l4a_FunPsCsqReadCnf,        ID_MSG_L4A_CERSSI_INQ_CNF,
        NULL,                       "^CERSSI"},

    {ID_MSG_L4A_CSQ_INFO_REQ,       ID_APP_RRC_CSQ_REQ,                 PS_PID_ERRC,    l4a_FunPsCsqReadReq,
        ID_RRC_APP_CSQ_CNF,             (PFN_L4A_CNF)l4a_FunPsCsqReadCnf,        ID_MSG_L4A_CSQ_INFO_CNF,
        NULL,                       "+CSQ"},

    {ID_MSG_L4A_ANQUERY_INFO_REQ,   ID_APP_RRC_CSQ_REQ,                 PS_PID_ERRC,    l4a_FunPsCsqReadReq,
        ID_RRC_APP_CSQ_CNF,             (PFN_L4A_CNF)l4a_FunPsCsqReadCnf,        ID_MSG_L4A_ANQUERY_INFO_CNF,
        NULL,                       "^ANQUERY"},

    {ID_MSG_L4A_CELL_INFO_REQ,      ID_APP_LRRC_GET_NCELL_INFO_REQ,     PS_PID_ERRC,    l4a_FunPsCellInfoReadReq,
        ID_RRC_APP_GET_NCELL_INFO_CNF,  (PFN_L4A_CNF)l4a_FunPsCellInfoReadCnf,   ID_MSG_L4A_CELL_INFO_CNF,
        NULL,                       "^LCELLINFO"},

    {ID_MSG_L4A_CELL_ID_REQ,        ID_APP_RRC_CELLID_REQ,              PS_PID_ERRC,    l4a_FunPsCellIDReadReq,
        ID_RRC_APP_CELLID_CNF,          (PFN_L4A_CNF)l4a_FunPsCellIDReadCnf,     ID_MSG_L4A_CELL_ID_CNF,
        NULL,                       "^CELLID"},

    {ID_MSG_L4A_FAST_DORM_REQ,      ID_APP_LRRC_FAST_DORM_CFG_NTF,      PS_PID_ERRC,    l4a_FunPsFastDormReadReq,
        0,                           (PFN_L4A_CNF)NULL,   0,
        NULL,                       "^FASTDORM"},
    {ID_MSG_L4A_LW_THRESHOLD_REQ,   ID_APP_LRRC_RESEL_OFFSET_CFG_NTF,   PS_PID_ERRC,    l4a_FunPsThresholdReadReq,
        0,                           (PFN_L4A_CNF)NULL,   0,
        NULL,                       "^WLTHRESHOLDCFG"},
    {ID_MSG_L4A_LTE_TO_IDLE_REQ,    ID_APP_LRRC_CON_TO_IDLE_NTF,        PS_PID_ERRC,    l4a_FunPsL2IdleSetReq,
        0,                           (PFN_L4A_CNF)NULL,   0,
        NULL,                       "^LFROMCONNTOIDLE"},
    {ID_MSG_L4A_LCACELLQRY_REQ,     ID_APP_MAC_CA_CELL_CMD_REQ,         PS_PID_MAC_UL,    l4a_FunPsLcacellReadReq,
        ID_MAC_APP_CA_CELL_CMD_CNF, (PFN_L4A_CNF)l4a_FunPsLcacellReadCnf,    ID_MSG_L4A_LCACELLQRY_CNF,
        NULL,                       "^LCACELL"},

    {ID_APS_L4A_GET_LTE_CS_REQ,     ID_APP_MM_INQ_LTE_CS_REQ,           PS_PID_MM,      l4a_FunPsLtecsReadReq,
        ID_APP_MM_INQ_LTE_CS_CNF,       (PFN_L4A_CNF)l4a_FunPsLtecsReadCnf,      ID_L4A_APS_GET_LTE_CS_CNF,
        l4a_FunLtecsChk,            "^LTECS"},
    {ID_APS_L4A_GET_CEMODE_REQ,     ID_APP_MM_INQ_UE_MODE_REQ,          PS_PID_MM,      l4a_FunPsCemodeReadReq,
        ID_APP_MM_INQ_UE_MODE_CNF,      (PFN_L4A_CNF)l4a_FunPsCemodeReadCnf,     ID_L4A_APS_GET_CEMODE_CNF,
        l4a_FunCemodChk,            "+CEMODE"},
    {ID_APS_L4A_SET_AUTHDATA_REQ,   ID_APP_ESM_SET_GW_AUTH_REQ,         PS_PID_ESM,     l4a_FunPsAuthDataSetReq,
        ID_APP_ESM_SET_GW_AUTH_CNF,     (PFN_L4A_CNF)l4a_FunPsNoCidCommSetCnf,   ID_L4A_APS_SET_AUTHDATA_CNF,
        l4a_FunAuthdataChk,         "^AUTHDATA"},

    {ID_APS_L4A_SET_CGDCONT_REQ,    ID_APP_ESM_SET_CGDCONT_REQ,         PS_PID_ESM,     l4a_FunPsCgdcontSetReq,
        ID_APP_ESM_SET_CGDCONT_CNF,     (PFN_L4A_CNF)l4a_FunPsCgdcontSetCnf,     ID_L4A_APS_SET_CGDCONT_CNF,
        l4a_FunCgdcontChk,          "+CGDCONT"},
    {ID_APS_L4A_SET_CGDSCONT_REQ,   ID_APP_ESM_SET_BEARER_TYPE_REQ,     PS_PID_ESM,     l4a_FunPsCgdscontSetReq,
        ID_APP_ESM_SET_BEARER_TYPE_CNF, (PFN_L4A_CNF)l4a_FunPsNoCidCommSetCnf,   ID_L4A_APS_SET_CGDSCONT_CNF,
        l4a_FunCgdscontChk,         "+CGDSCONT"},
    {ID_APS_L4A_SET_CGTFT_REQ,      ID_APP_ESM_SET_TFT_REQ,             PS_PID_ESM,     l4a_FunPsCgtftSetReq,
        ID_APP_ESM_SET_TFT_CNF,         (PFN_L4A_CNF)l4a_FunPsNoCidCommSetCnf,   ID_L4A_APS_SET_CGTFT_CNF,
        l4a_FunCgtftChk,            "+CGTFT"},

    {ID_APS_L4A_SET_CGAUTO_REQ,     ID_APP_ESM_SET_PDP_MANAGER_TYPE_REQ,PS_PID_ESM,     l4a_FunPsCgautoSetReq,
        ID_APP_ESM_SET_PDP_MANAGER_TYPE_CNF,(PFN_L4A_CNF)l4a_FunPsCgautoSetCnf,  ID_L4A_APS_SET_CGAUTO_CNF,
        l4a_FunCgautoChk,           "+CGAUTO"},
    {ID_APS_L4A_SET_CGCONTRDP_REQ,  ID_APP_ESM_INQ_DYNAMIC_PDP_CONT_REQ,PS_PID_ESM,     l4a_FunPsOnlyCidCommSetReq,
        ID_APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF, (PFN_L4A_CNF)l4a_FunPsCgcontrdpSetCnf, ID_L4A_APS_SET_CGCONTRDP_CNF,
        l4a_FunCgcontrdpChk,        "+CGCONTRDP"},
    {ID_APS_L4A_SET_CGSCONTRDP_REQ, ID_APP_ESM_INQ_DYNAMIC_PDP_CONT_REQ,PS_PID_ESM,     l4a_FunPsOnlyCidCommSetReq,
        ID_APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF, (PFN_L4A_CNF)l4a_FunPsCgscontrdpSetCnf,ID_L4A_APS_SET_CGSCONTRDP_CNF,
        l4a_FunCgscontrdpChk,       "+CGSCONTRDP"},
    {ID_APS_L4A_SET_CGTFTRDP_REQ,   ID_APP_ESM_INQ_DYNAMIC_TFT_REQ,     PS_PID_ESM,     l4a_FunPsOnlyCidCommSetReq,
        ID_APP_ESM_INQ_DYNAMIC_TFT_CNF,     (PFN_L4A_CNF)l4a_FunPsCgtftrdpSetCnf,ID_L4A_APS_SET_CGTFTRDP_CNF,
        l4a_FunCgtftrdpChk,         "+CGTFTRDP"},
    {ID_APS_L4A_SET_CGEQOS_REQ,     ID_APP_ESM_SET_EPS_QOS_REQ,         PS_PID_ESM,     l4a_FunPsCgeqosSetReq,
        ID_APP_ESM_SET_EPS_QOS_CNF,     (PFN_L4A_CNF)l4a_FunPsNoCidCommSetCnf,   ID_L4A_APS_SET_CGEQOS_CNF,
        l4a_FunCgeqosChk,            "+CGEQOS"},
    {ID_APS_L4A_SET_CGEQOSRDP_REQ,  ID_APP_ESM_INQ_DYNAMIC_EPS_QOS_REQ, PS_PID_ESM,     l4a_FunPsOnlyCidCommSetReq,
        ID_APP_ESM_INQ_DYNAMIC_EPS_QOS_CNF,(PFN_L4A_CNF)l4a_FunPsCgeqosrdpSetCnf,ID_L4A_APS_SET_CGEQOSRDP_CNF,
        l4a_FunCgeqosrdpChk,        "+CGEQOSRDP"},

    {ID_APS_L4A_ABORT_REQ,          ID_APP_ESM_PROCEDURE_ABORT_NOTIFY,  PS_PID_ESM,     l4a_FunPsAbortSetReq,
        0,                              (PFN_L4A_CNF)NULL,  0,
        NULL,                       "ABORT"},
    {ID_APS_L4A_IPV6_INFO_NOTIFY_IND,ID_APP_ESM_IPV6_INFO_NOTIFY,       PS_PID_ESM,     l4a_FunPsIpv6SetReq,
        0,                              (PFN_L4A_CNF)NULL,  0,
        NULL,                       "IPV6NTF"},
    {ID_MSG_L4A_IND_CFG_REQ,        0,                                  0,              l4a_FunIndCfgSetReq,
        0,                              (PFN_L4A_CNF)NULL,  0,
        NULL,                       "^CURC"}

};

static L4A_IND_MSG_FUN_TABLE_STRU g_astRpiPsIndTable[] = {

    {ID_RRC_APP_CSQ_IND,            l4a_FunCsqInd,              "+CSQ"},
    {ID_RRC_APP_LWCLASH_IND,        l4a_FunLwclashInd,          "^LWURC"},
    {ID_MAC_APP_CA_CELL_CMD_IND,    l4a_FunLcacellInd,          "^LCACELLURC"},
};


/*****************************************************************************
  3 Function
*****************************************************************************/

VOS_VOID mntn_UpdateMsgInfo(L4A_MNTN_MSG_INFO_STRU *pstMsg, VOS_UINT32 ulMsgId)
{
    pstMsg->aulMsgId[pstMsg->ulptr] = ulMsgId;
    pstMsg->aulTime[pstMsg->ulptr]  = VOS_GetTick();
    pstMsg->ulptr                   = (pstMsg->ulptr + 1) % L4A_MNTN_MSG_NUM;
}

L4A_FW_MSG_FUN_TABLE_STRU* mntn_GetInfo(VOS_UINT32 ulMsgId, VOS_UINT32 *pulStep)
{
    VOS_UINT32 i;
    VOS_UINT32 ulTableLen;
    L4A_FW_MSG_FUN_TABLE_STRU* pTable;

    pTable = FwProGetMsgFunTbl(&ulTableLen);

    for (i = 0; i < (ulTableLen / sizeof(L4A_FW_MSG_FUN_TABLE_STRU)); i++)
    {
        if (ulMsgId == (pTable + i)->ulAtReqMsgId)
        {
            *pulStep = 0;
        }
        else if (ulMsgId == (pTable + i)->ulPsReqMsgId)
        {
            *pulStep = 1;
        }
        else if (ulMsgId == (pTable + i)->ulPsCnfMsgId)
        {
            *pulStep = 2;
        }
        else if (ulMsgId == (pTable + i)->ulAtCnfMsgId)
        {
            *pulStep = 3;
        }
        else
        {
            continue;
        }

        return (L4A_FW_MSG_FUN_TABLE_STRU*)(pTable + i);
    }

    return NULL;
}

/* L4A模块可维可测信息显示 */
VOS_VOID l4a_help(VOS_VOID)
{
    VOS_UINT32 ulRxMin, ulTxMin;
    VOS_UINT32 i;
    L4A_MNTN_MSG_INFO_STRU stRx = {{0}}, stTx = {{0}};
    VOS_UINT32 aulMsg[L4A_MNTN_MSG_NUM*2] = {0}, aulTime[L4A_MNTN_MSG_NUM*2] = {0};
    VOS_UINT32 ulRxNum = 0, ulTxNum = 0, ulTotalNum = 0;
    VOS_UINT32 ulStep;
    L4A_FW_MSG_FUN_TABLE_STRU* ptable;
    L4A_IND_MSG_FUN_TABLE_STRU* ptableind;

    for(i = 0; i < sizeof(g_astRpiMsgFunTable)/sizeof(g_astRpiMsgFunTable[0]); i++)
    {
        (VOS_VOID)vos_printf("%25s: req msgid 0x%08x, cnf msgid 0x%08x\n",
            g_astRpiMsgFunTable[i].ATCmdName,g_astRpiMsgFunTable[i].ulPsReqMsgId, g_astRpiMsgFunTable[i].ulPsCnfMsgId);
    }

    ulRxMin = g_stmntn.stMsgInfoRx.ulptr;
    ulTxMin = g_stmntn.stMsgInfoTx.ulptr;

    /* 按顺序存储，获取实际个数 */
    for(i = 0; i < L4A_MNTN_MSG_NUM; i++)
    {
        if(0 != g_stmntn.stMsgInfoRx.aulTime[ulRxMin])
        {
            stRx.aulMsgId[ulRxNum] = g_stmntn.stMsgInfoRx.aulMsgId[ulRxMin];
            stRx.aulTime[ulRxNum]  = g_stmntn.stMsgInfoRx.aulTime[ulRxMin];
            ulRxNum++;
        }
        ulRxMin = (ulRxMin + 1) % L4A_MNTN_MSG_NUM;

        if(0 != g_stmntn.stMsgInfoTx.aulTime[ulTxMin])
        {
            stTx.aulMsgId[ulTxNum] = g_stmntn.stMsgInfoTx.aulMsgId[ulTxMin];
            stTx.aulTime[ulTxNum]  = g_stmntn.stMsgInfoTx.aulTime[ulTxMin];
            ulTxNum++;
        }
        ulTxMin = (ulTxMin + 1) % L4A_MNTN_MSG_NUM;
    }

    /* 综合排序 */
    for(i = 0; i < L4A_MNTN_MSG_NUM*2; i++)
    {
        /* 如果两个缓冲区里面都有数据待排序 */
        if((stRx.ulptr < ulRxNum) && (stTx.ulptr < ulTxNum))
        {
            if(stRx.aulTime[stRx.ulptr] > stTx.aulTime[stTx.ulptr])
            {
                aulMsg[ulTotalNum]  = stTx.aulMsgId[stTx.ulptr];
                aulTime[ulTotalNum] = stTx.aulTime[stTx.ulptr];
                stTx.ulptr++;
            }
            else    /* 相等时先存储收的 */
            {
                aulMsg[ulTotalNum]  = stRx.aulMsgId[stRx.ulptr];
                aulTime[ulTotalNum] = stRx.aulTime[stRx.ulptr];
                stRx.ulptr++;
            }
        }
        else if((stRx.ulptr < ulRxNum) && (stTx.ulptr >= ulTxNum))
        {
            aulMsg[ulTotalNum]  = stRx.aulMsgId[stRx.ulptr];
            aulTime[ulTotalNum] = stRx.aulTime[stRx.ulptr];
            stRx.ulptr++;
        }
        else if((stTx.ulptr < ulTxNum) && (stRx.ulptr >= ulRxNum))
        {
            aulMsg[ulTotalNum]  = stTx.aulMsgId[stTx.ulptr];
            aulTime[ulTotalNum] = stTx.aulTime[stTx.ulptr];
            stTx.ulptr++;
        }
        else
        {
            break;
        }

        ulTotalNum++;
    }

    /* 打印 */
    (VOS_VOID)vos_printf("AT/TAF                  L4A                     LPS\n");
    for(i = 0; i < ulTotalNum; i++)
    {
        ptable = mntn_GetInfo(aulMsg[i], &ulStep);
        if(NULL != ptable)
        {
            switch(ulStep)
            {
                case 0:
                    (VOS_VOID)vos_printf("%s 0x%x--> \n", ptable->ATCmdName, aulTime[i]);
                    break;
                case 1:
                    (VOS_VOID)vos_printf("                        %s 0x%x--> \n", ptable->ATCmdName, aulTime[i]);
                    break;
                case 2:
                    (VOS_VOID)vos_printf("                        <--%s 0x%x \n", ptable->ATCmdName, aulTime[i]);
                    break;
                default:
                    (VOS_VOID)vos_printf("<--%s 0x%x \n", ptable->ATCmdName, aulTime[i]);
                    break;
            }
            continue;
        }

        ptableind = l4a_FwProGetPsIndFun(aulMsg[i]);
        if(ptableind)
        {
            (VOS_VOID)vos_printf("                        <--%s 0x%x \n", ptableind->ATCmdName, aulTime[i]);
        }
        else
        {
            (VOS_VOID)vos_printf("<--0x%x 0x%x \n", aulMsg[i], aulTime[i]);
        }
        continue;
    }
}

/*****************************************************************************
 Function Name   : FwProGetMsgFunTbl
 Description     : 查找消息对应处理表格
 Input           :VOS_UINT32 * pulTableLenth
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-5-25  Draft Enact

*****************************************************************************/

L4A_FW_MSG_FUN_TABLE_STRU * FwProGetMsgFunTbl(VOS_UINT32 * pulTableLenth)
{
    *pulTableLenth = sizeof(g_astRpiMsgFunTable);

    return g_astRpiMsgFunTable;
}

L4A_IND_MSG_FUN_TABLE_STRU * FwProGetPsIndFunTbl(VOS_UINT32 * pulTableLenth)
{
    *pulTableLenth = sizeof(g_astRpiPsIndTable);

    return g_astRpiPsIndTable;
}

L4A_FW_MSG_FUN_TABLE_STRU* l4a_FwProGetMsgFun(VOS_UINT32 ulMsgId,VOS_UINT32 flag)
{
    VOS_UINT32 i;
    VOS_UINT32 ulTableLen;
    L4A_FW_MSG_FUN_TABLE_STRU* pTable;

    pTable = FwProGetMsgFunTbl(&ulTableLen);

    if( L4A_REQ_FLAG == flag)
    {
        for (i = 0; i < (ulTableLen / sizeof(L4A_FW_MSG_FUN_TABLE_STRU)); i++)
        {
            if (ulMsgId == (pTable + i)->ulAtReqMsgId)
            {
                return (L4A_FW_MSG_FUN_TABLE_STRU*)(pTable + i);
            }
        }
    }
    else
    {
        for (i = 0; i < (ulTableLen / sizeof(L4A_FW_MSG_FUN_TABLE_STRU)); i++)
        {
            if (ulMsgId == (pTable + i)->ulPsCnfMsgId)
            {
                return (L4A_FW_MSG_FUN_TABLE_STRU*)(pTable + i);
            }
        }
    }

    return NULL;
}

L4A_IND_MSG_FUN_TABLE_STRU* l4a_FwProGetPsIndFun(VOS_UINT32 ulMsgId)
{
    VOS_UINT32 i;
    VOS_UINT32 ulTableLen;
    const L4A_IND_MSG_FUN_TABLE_STRU* pTable;

    pTable = FwProGetPsIndFunTbl(&ulTableLen);

    for (i = 0; i < (ulTableLen / sizeof(L4A_IND_MSG_FUN_TABLE_STRU)); i++)
    {
        if (ulMsgId == (pTable + i)->ulPsIndMsgId)
        {
            return (L4A_IND_MSG_FUN_TABLE_STRU*)(pTable + i);
        }
    }

    return NULL;
}

/*****************************************************************************
 Function Name   : l4a_StartTimer
 Description     : 定时器启动接口封装
 Input           :L4A_RX_INFO_STRU* pNewNode
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-5-25  Draft Enact

*****************************************************************************/

VOS_UINT32 l4a_StartTimer(HTIMER *phTimerId, L4A_RX_INFO_STRU* pNewNode, VOS_UINT32 ulms)
{
    return VOS_StartRelTimer(phTimerId, MSP_L4_L4A_PID,ulms, 0,(VOS_UINT32)pNewNode,VOS_RELTIMER_NOLOOP, VOS_TIMER_NO_PRECISION);
}

/*****************************************************************************
 Function Name   : l4a_StopTimer
 Description     : 定时器停止接口封装
 Input           :VOS_UINT32 hTimerId
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-5-25  Draft Enact

*****************************************************************************/

VOS_UINT32 l4a_StopTimer(HTIMER *phTimerId)
{
    /*删除定时器*/
    return VOS_StopRelTimer(phTimerId);
}


/*****************************************************************************
 Function Name   : L4A_GetRptCmdStatus
 Description     : L4A 获取对应命令是否上报函数
 Input           : enRptCmdIndex    对应的命令ID
 Output          : None
 Return          : VOS_TRUE-report; VOS_FALSE-not report

 History         :
    1.c64416      2013-5-30  Draft Enact

*****************************************************************************/
VOS_BOOL L4A_GetRptCmdStatus( L4A_RPT_CMD_INDEX_ENUM_UINT32 enRptCmdIndex )
{
    VOS_UINT32 ulOffset;
    VOS_UINT8  ucBit;

    /* 主动上报命令索引错误，默认主动上报 */
    if(enRptCmdIndex >= (L4A_CURC_RPT_CFG_MAX_SIZE * 8))
    {
        return VOS_TRUE;
    }

    /* 8表示8bits */
    ulOffset = enRptCmdIndex / 8;
    ucBit    = enRptCmdIndex % 8;

    return (VOS_BOOL)((g_aucL4aCurcRptCfg[ulOffset] >> ucBit) & 0x1);
}


/*****************************************************************************
 Function Name   : L4A_SetRptCmdStatus
 Description     : L4A 设置对应命令是否上报函数
 Input           : enRptCmdIndex    对应的命令ID
                   bFlag            是否上报 : VOS_TRUE-report; VOS_FALSE-not report
 Output          : None
 Return          : VOS_VOID

 History         :
    1.c64416      2013-5-30  Draft Enact

*****************************************************************************/
VOS_VOID L4A_SetRptCmdStatus( L4A_RPT_CMD_INDEX_ENUM_UINT32 enRptCmdIndex, VOS_BOOL bFlag )
{
    VOS_UINT32 ulOffset;
    VOS_UINT32 ucBit;

    /* 越界，设置无效 */
    if (enRptCmdIndex >= (L4A_CURC_RPT_CFG_MAX_SIZE * 8))
    {
        return ;
    }

    /* 8表示8bits */
    ulOffset = enRptCmdIndex / 8;
    ucBit    = enRptCmdIndex % 8;

    if(bFlag)
    {
        g_aucL4aCurcRptCfg[ulOffset] |= (VOS_UINT8)(0x01 << ucBit); /*lint !e701*/
    }
    else
    {
        g_aucL4aCurcRptCfg[ulOffset] &= (VOS_UINT8)(0xfe << ucBit); /*lint !e701*/
    }

    return ;
}


/*****************************************************************************
 Function Name   : l4a_GetNodeHead
 Description     : 获取链表头结点指针
 Input           : VOS_VOID
 Output          : None
 Return          : 链表头结点指针

 History         :
    1.c64416      2013-6-1  Draft Enact

*****************************************************************************/
HI_LIST_S* l4a_GetNodeHead(VOS_VOID)
{
    return &g_stL4aNodeHead;
}

/*****************************************************************************
 Function Name   : l4a_GetExeCmdNode
 Description     : 通道命令ID查找执行节点
 Input           :VOS_UINT32 ulCmdId
 Output          : None
 Return          : L4A_RX_INFO_STRU*

 History         :
    1.w00182550      2012-11-22  Draft Enact

*****************************************************************************/
L4A_RX_INFO_STRU* l4a_GetExeCmdNode(VOS_UINT32 ulMsgId,VOS_UINT32 ulFlag)
{
    HI_LIST_S* pHeadNode = NULL;
    L4A_RX_INFO_STRU* pTempNode = NULL;
    HI_LIST_S* me = NULL;

    /* 获取链表头 */
    pHeadNode= l4a_GetNodeHead();

    /*添加信号量保护*/
    /* coverity[check_return] */
    (VOS_VOID)VOS_SmP(g_ulL4aNodeSem,0);

    /* 在链表中查找每个子命令结点*/
    msp_list_for_each(me, pHeadNode)
    {
        pTempNode = msp_list_entry(me, L4A_RX_INFO_STRU, HiL4aList);

        L4A_INFO_LOG("%s, msgid req 0x%x, cnf 0x%x.\n",__FUNCTION__, pTempNode->ulReqMsgId, pTempNode->ulCnfMsgId);

        /* 找到需要的节点*/
        if (((L4A_REQ_FLAG == ulFlag)&&(ulMsgId == pTempNode->ulReqMsgId))|| \
            ((L4A_CNF_FLAG == ulFlag)&&(ulMsgId == pTempNode->ulCnfMsgId)))
        {
            (VOS_VOID)VOS_SmV(g_ulL4aNodeSem);
            return pTempNode;
        }

    }
    (VOS_VOID)VOS_SmV(g_ulL4aNodeSem);
    return NULL;
}

/*****************************************************************************
 Function Name   : l4a_DelCmdNode
 Description     : 删除已经处理完的节点
 Input           :L4A_RX_INFO_STRU* pstCmdNode
 Output          : None
 Return          : VOS_VOID

 History         :
    1.w00182550      2012-11-22  Draft Enact

*****************************************************************************/
VOS_VOID l4a_DelCmdNode(L4A_RX_INFO_STRU* pstCmdNode)
{
    /*添加信号量保护*/
    /* coverity[check_return] */
    (VOS_VOID)VOS_SmP(g_ulL4aNodeSem,0);

    /*删除节点*/
    msp_list_del(&pstCmdNode->HiL4aList);

    (VOS_VOID)VOS_SmV(g_ulL4aNodeSem);

    /*释放内存*/
    (VOS_VOID)VOS_MemFree(MSP_L4_L4A_PID,pstCmdNode->pData);

    /*释放内存*/
    (VOS_VOID)VOS_MemFree(MSP_L4_L4A_PID,pstCmdNode);

    return ;
}

/*****************************************************************************
 Function Name   : l4a_AddCmdToListEx
 Description     : 添加解码后数据到缓存中，用于一条请求对应多个处理的特殊场景
                    (ID_APS_L4A_SET_CGACT_REQ对应+CGACT=0/1)
 Input           :VOS_VOID * pstReq
                VOS_UINT32 ulRcvlen
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c64416      2013-08-12  Draft Enact

*****************************************************************************/
VOS_UINT32 l4a_AddCmdToListEx(L4A_DATA_MSG_STRU * pstReq, VOS_UINT32 ulATReqMsgId, VOS_UINT32 ulPSCnfMsgId)
{
    HI_LIST_S* pHeadNode = NULL;
    L4A_RX_INFO_STRU* pNewNode = NULL;
    VOS_UINT32 ulLen = pstReq->ulLength + VOS_MSG_HEAD_LENGTH;

    /*申请一个节点大小*/
    pNewNode = VOS_MemAlloc(MSP_L4_L4A_PID, DYNAMIC_MEM_PT, sizeof(L4A_RX_INFO_STRU));
    if (NULL == pNewNode)
    {
        return ERR_MSP_FAILURE;
    }
    (VOS_VOID)VOS_MemSet(pNewNode, 0, sizeof(L4A_RX_INFO_STRU));

    /*再申请一个请求缓存区*/
    pNewNode->pData = VOS_MemAlloc(MSP_L4_L4A_PID, DYNAMIC_MEM_PT, ulLen);
    if (NULL == pNewNode->pData)
    {
        (VOS_VOID)VOS_MemFree(MSP_L4_L4A_PID, pNewNode);
        return ERR_MSP_FAILURE;
    }

    (VOS_VOID)VOS_MemCpy(pNewNode->pData, pstReq, ulLen);

    pNewNode->ulReqMsgId = ulATReqMsgId;
    pNewNode->ulCnfMsgId = ulPSCnfMsgId;
    pNewNode->usClientId = (VOS_UINT16)(((L4A_REQ_MSG_STRU*)pstReq)->stCtrl.ulClientId); /*lint !e740*/
    (VOS_VOID)l4a_StartTimer(&(pNewNode->fwCtrlTimer), pNewNode, L4A_CMD_TIMEOUT_TIME_LEN);

    /* 获取链表头 */
    pHeadNode = l4a_GetNodeHead();

    /*添加信号量保护*/
    /* coverity[check_return] */
    (VOS_VOID)VOS_SmP(g_ulL4aNodeSem,0);

    /* 插入节点到链表尾部 */
    msp_list_add_tail(&pNewNode->HiL4aList, pHeadNode);

    (VOS_VOID)VOS_SmV(g_ulL4aNodeSem);

    return ERR_MSP_SUCCESS;
}

/*****************************************************************************
 Function Name   : l4a_AddCmdToList
 Description     : 添加解码后数据到缓存中
 Input           :VOS_VOID * pstReq
                VOS_UINT32 ulRcvlen
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2012-11-19  Draft Enact

*****************************************************************************/
VOS_UINT32 l4a_AddCmdToList(L4A_DATA_MSG_STRU * pstReq, L4A_FW_MSG_FUN_TABLE_STRU* pstFunTable)
{
    if ((NULL == pstReq) || (NULL == pstFunTable))
    {
        return ERR_MSP_FAILURE;
    }

    L4A_INFO_LOG("%s, msgid req 0x%x, cnf 0x%x.\n",__FUNCTION__, pstFunTable->ulAtReqMsgId, pstFunTable->ulPsCnfMsgId);

    (VOS_VOID)l4a_AddCmdToListEx(pstReq, pstFunTable->ulAtReqMsgId, pstFunTable->ulPsCnfMsgId);

    return ERR_MSP_SUCCESS;
}

/*****************************************************************************
 Function Name   : l4a_SendMsg
 Description     : L4A发送消息接口
 Input           :VOS_UINT32 ulRecverId
                VOS_UINT8* pDta
                VOS_UINT32 dtaSize
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-5-25  Draft Enact

*****************************************************************************/

VOS_UINT32 l4a_SendMsg(VOS_UINT32 ulSendId, VOS_UINT32 ulRecverId, VOS_VOID* pDta, VOS_UINT32 dtaSize)
{
    VOS_UINT32 ret = ERR_MSP_UNKNOWN;
    VOS_UINT32 ulMsgid = 0;
    L4A_DATA_MSG_STRU* pDataMsg = NULL;

    L4A_INFO_LOG("%s, ulRecverId %d.\n",__FUNCTION__, ulRecverId);

    /* 传进来的dtaSize已经包含了VOS HEADER，因此申请时需要-20 */
    pDataMsg = (L4A_DATA_MSG_STRU*)VOS_AllocMsg(ulSendId, dtaSize - VOS_MSG_HEAD_LENGTH); /*lint !e740*/

    if (pDataMsg)
    {
        (VOS_VOID)VOS_MemCpy(pDataMsg, pDta, dtaSize);

        pDataMsg->ulSenderCpuId   = 0x7f000001;
        pDataMsg->ulReceiverCpuId = 0x7f000001;

        pDataMsg->ulReceiverPid = ulRecverId;
        pDataMsg->ulSenderPid   = ulSendId;
        /* coverity[overflow_const] */
        pDataMsg->ulLength      = dtaSize - VOS_MSG_HEAD_LENGTH;

        ulMsgid = pDataMsg->enMsgId;

        ret = VOS_SendMsg(ulSendId, pDataMsg);
        if (ret != VOS_OK)
        {
            L4A_ERROR_LOG("l4a_SendMsg ulRecverId=%d, dtaSize=%d!\n",ulRecverId, dtaSize);
            ret = ERR_MSP_FAILURE;
        }
        else
        {
            mntn_UpdateMsgInfo(&g_stmntn.stMsgInfoTx, ulMsgid);

            ret = ERR_MSP_SUCCESS;
        }
    }

    return ret;
}

/*****************************************************************************
 Function Name   : l4aPacket2Aps
 Description     : L4A发送消息到APS接口
 Input           :VOS_VOID* pstDataCnf
                VOS_UINT32 ulSize
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-5-25  Draft Enact

*****************************************************************************/

VOS_UINT32 l4aPacket2Aps(VOS_VOID *pstDataCnf, VOS_UINT32 ulSize)
{
    ((L4A_DATA_MSG_STRU*)pstDataCnf)->ulSenderCpuId = 0x7f000001;
    ((L4A_DATA_MSG_STRU*)pstDataCnf)->ulReceiverCpuId = 0x7f000001;

    return l4a_SendMsg(MSP_L4_L4A_PID, WUEPS_PID_TAF, pstDataCnf, ulSize);

}

/*****************************************************************************
 Function Name   : l4aPacket2PsNoCnf
 Description     : 发送消息给PS，需要PS回复时使用
 Input           :VOS_UINT32 ulRecverId
                  VOS_VOID* pData
                  VOS_UINT32 ulLen
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-5-17  Draft Enact

*****************************************************************************/
VOS_UINT32 l4aPacket2Ps(VOS_UINT32 ulRecverId, VOS_VOID *pData, VOS_UINT32 ulLen)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    APP_LPS_MSG_STRU* pstAppToPsMsg = NULL;

    pstAppToPsMsg = (APP_LPS_MSG_STRU*)LAPP_MemAlloc(ulLen + sizeof(APP_LPS_MSG_STRU) - 4);
    if(NULL == pstAppToPsMsg)
    {
        return ERR_MSP_FAILURE;
    }

    pstAppToPsMsg->ulMsgId   = ((L4A_PS_MSG_STRU *)pData)->ulMsgId;
    pstAppToPsMsg->ulSize    = ulLen;

    /* VOS MSG HEADER */
    ((L4A_PS_MSG_STRU *)pData)->ulSenderCpuId   = 0x7f000001;
    ((L4A_PS_MSG_STRU *)pData)->ulReceiverCpuId = 0x7f000001;
    ((L4A_PS_MSG_STRU *)pData)->ulSenderPid     = PS_PID_OM;
    ((L4A_PS_MSG_STRU *)pData)->ulReceiverPid   = ulRecverId;
    ((L4A_PS_MSG_STRU *)pData)->ulLength        = ulLen - VOS_MSG_HEAD_LENGTH;

    /* APP MSG HEADER*/
    ((L4A_PS_MSG_STRU *)pData)->usOriginalId = 0;
    ((L4A_PS_MSG_STRU *)pData)->usTerminalId = 0;
    ((L4A_PS_MSG_STRU *)pData)->ulTimeStamp = 0;
    ((L4A_PS_MSG_STRU *)pData)->ulSN = 0;

    (VOS_VOID)VOS_MemCpy(pstAppToPsMsg->aucValue, pData,ulLen);

    mntn_UpdateMsgInfo(&g_stmntn.stMsgInfoTx, pstAppToPsMsg->ulMsgId);

    ret = LAppSndMsgToLPs(pstAppToPsMsg);

    if(ret == ERR_MSP_SUCCESS)
    {
       return ERR_MSP_WAIT_ASYNC;
    }
    return ret;
}

/*****************************************************************************
 Function Name   : l4aPacket2PsNoCnf
 Description     : 发送消息给PS，不需要PS回复时使用
 Input           :VOS_UINT32 ulRecverId
                  VOS_VOID * pData
                  VOS_UINT32 ulLen
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-5-17  Draft Enact

*****************************************************************************/
VOS_UINT32 l4aPacket2PsNoCnf(VOS_UINT32 ulRecverId, VOS_VOID *pData, VOS_UINT32 ulLen)
{
   APP_LPS_MSG_STRU* pstAppToPsMsg = NULL;

    pstAppToPsMsg = (APP_LPS_MSG_STRU*)LAPP_MemAlloc(ulLen + sizeof(APP_LPS_MSG_STRU) - 4);
    if(NULL == pstAppToPsMsg)
    {
        return ERR_MSP_FAILURE;
    }

    pstAppToPsMsg->ulMsgId   = ((L4A_PS_MSG_STRU *)pData)->ulMsgId;
    pstAppToPsMsg->ulSize    = ulLen;

    /* VOS MSG HEADER */
    ((L4A_PS_MSG_STRU *)pData)->ulSenderCpuId   = 0x7f000001;
    ((L4A_PS_MSG_STRU *)pData)->ulReceiverCpuId = 0x7f000001;
    ((L4A_PS_MSG_STRU *)pData)->ulSenderPid     = PS_PID_OM;
    ((L4A_PS_MSG_STRU *)pData)->ulReceiverPid   = ulRecverId;
    ((L4A_PS_MSG_STRU *)pData)->ulLength        = ulLen - VOS_MSG_HEAD_LENGTH;

    /* APP MSG HEADER*/
    ((L4A_PS_MSG_STRU *)pData)->usOriginalId = 0;
    ((L4A_PS_MSG_STRU *)pData)->usTerminalId = 0;
    ((L4A_PS_MSG_STRU *)pData)->ulTimeStamp = 0;
    ((L4A_PS_MSG_STRU *)pData)->ulSN = 0;

    (VOS_VOID)VOS_MemCpy(pstAppToPsMsg->aucValue, pData,ulLen);

    mntn_UpdateMsgInfo(&g_stmntn.stMsgInfoTx, pstAppToPsMsg->ulMsgId);

    return LAppSndMsgToLPs(pstAppToPsMsg);
}

/*****************************************************************************
 Function Name   : l4aPacket2At
 Description     : 封装发给消息给AT接口
 Input           :L4A_DATA_MSG_STRU* pstDataCnf
                VOS_UINT32 ulSize
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-5-25  Draft Enact

*****************************************************************************/

VOS_UINT32 l4aPacket2At(VOS_VOID *pstDataCnf, VOS_UINT32 ulSize)
{
    VOS_UINT32 i;

    L4A_INFO_LOG("l4aPacket2At :");
    for(i = 0; i < ulSize; i++)
    {
        L4A_INFO_LOG("0x%x ", ((VOS_UINT8*)pstDataCnf)[i]);
    }
    L4A_INFO_LOG("\n");

    return l4a_SendMsg(MSP_L4_L4A_PID, WUEPS_PID_AT, pstDataCnf, ulSize);
}

/*****************************************************************************
 Function Name   : l4a_DealTimeOutCmdEntry
 Description     : 超时命令处理入口
 Input           :VOS_VOID* pData
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-5-25  Draft Enact

*****************************************************************************/
VOS_UINT32 l4a_DealTimeOutCmdEntry(L4A_RX_INFO_STRU* pData)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    PFN_L4A_CNF pfnCnfFun = NULL;
    L4A_FW_MSG_FUN_TABLE_STRU* pstFunTable = NULL;
    L4A_RX_INFO_STRU *pNode=NULL;
    VOS_UINT16 usClientId = 0;

    /* TODO: 多次请求 */
    pNode =l4a_GetExeCmdNode(pData->ulReqMsgId, L4A_REQ_FLAG);
    if(pNode)
    {
        usClientId = pNode->usClientId;

        pstFunTable = l4a_FwProGetMsgFun(pData->ulCnfMsgId, L4A_CNF_FLAG);
        if(pstFunTable)
        {
            pfnCnfFun = pstFunTable->pfnCnfFun;
            if(pfnCnfFun)
            {
                /* 数据为NULL表示超时错误，在回复函数中直接回复失败 */
                ulRet = (pfnCnfFun)(NULL, pstFunTable, usClientId);
            }
        }
    }

    /*删除超时处理节点*/
    l4a_DelCmdNode(pData);

    return ulRet;
}

/*****************************************************************************
 Function Name   : l4a_DealPsIndCnfEntry
 Description     : PS的上报和CNF处理入口
 Input           :L4A_PS_MSG_STRU* pData
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-5-25  Draft Enact

*****************************************************************************/
VOS_UINT32 l4a_DealPsIndCnfEntry(L4A_PS_MSG_STRU* pData)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    PFN_L4A_CNF pfnCnfFun = NULL;
    PFN_L4A_IND_MSG_FUN pfnIndFun = NULL;
    L4A_IND_MSG_FUN_TABLE_STRU* pstIndFunTable = NULL;
    L4A_RX_INFO_STRU *pstNode = NULL;
    L4A_FW_MSG_FUN_TABLE_STRU *pstFunTable;

    HI_LIST_S* pHeadNode = NULL;
    HI_LIST_S* me = NULL;

    L4A_INFO_LOG("%s, msgid 0x%x.\n",__FUNCTION__, pData->ulMsgId);

    /* 获取链表头 */
    pHeadNode= l4a_GetNodeHead();

    /*添加信号量保护*/
    (VOS_VOID)VOS_SmP(g_ulL4aNodeSem,0);

    /* 在链表中查找每个子命令结点*/
    msp_list_for_each(me, pHeadNode)
    {
        pstNode = msp_list_entry(me, L4A_RX_INFO_STRU, HiL4aList);

        L4A_INFO_LOG("%s, msgid cnf 0x%x.\n",__FUNCTION__, pstNode->ulCnfMsgId);

        /* 找到需要的节点*/
        if (pData->ulMsgId != pstNode->ulCnfMsgId)
        {
            continue;
        }

        /* 根据请求的消息ID来获取表格，因为PS的回复可能对应多种请求 */
        pstFunTable = l4a_FwProGetMsgFun(pstNode->ulReqMsgId, L4A_REQ_FLAG);
        if(NULL == pstFunTable)
        {
            (VOS_VOID)VOS_SmV(g_ulL4aNodeSem);
            L4A_INFO_LOG("%s, pstNode->ulReqMsgId 0x%x.\n",__FUNCTION__, pstNode->ulReqMsgId);
            return ERR_MSP_FAILURE;
        }

        if((NULL != pstFunTable->pfnCheck) && (ERR_MSP_SUCCESS != pstFunTable->pfnCheck(pData, pstNode)))
        {
            /* 不匹配，重新查找 */
            L4A_INFO_LOG("%s, %p failed.\n",__FUNCTION__, pstFunTable->pfnCheck);
            continue;
        }

        (VOS_VOID)VOS_SmV(g_ulL4aNodeSem);

        mntn_UpdateMsgInfo(&g_stmntn.stMsgInfoRx, pData->ulMsgId);

        L4A_INFO_LOG("%s, %s.\n",__FUNCTION__, pstFunTable->ATCmdName);

        (VOS_VOID)l4a_StopTimer(&(pstNode->fwCtrlTimer));

        pfnCnfFun = pstFunTable->pfnCnfFun;
        if(pfnCnfFun)
        {
            ulRet = (pfnCnfFun)(pData, pstFunTable, pstNode->usClientId);

            /* 如果不涉及CID，或cid个数为1，或没有向LPS再次发起请求，删除请求处理节点 */
            if((pstNode->ulCidNum <= 1) || (ERR_MSP_WAIT_ASYNC != ulRet))
            {
                l4a_DelCmdNode(pstNode);
            }
            /* 如果处于再次请求的状态，需要重新打开定时器 */
            else
            {
                (VOS_VOID)l4a_StartTimer(&(pstNode->fwCtrlTimer), pstNode, L4A_CMD_TIMEOUT_TIME_LEN);
            }
        }
        else
        {
            /* 不应出现此场景 */
            L4A_ERROR_LOG("fatal error : %s, msgid 0x%x.\n",__FUNCTION__, pData->ulMsgId);
        }

        return ulRet;
    }

    (VOS_VOID)VOS_SmV(g_ulL4aNodeSem);

    pstIndFunTable = l4a_FwProGetPsIndFun(pData->ulMsgId);
    if(pstIndFunTable)
    {
        mntn_UpdateMsgInfo(&g_stmntn.stMsgInfoRx, pData->ulMsgId);

        L4A_INFO_LOG("%s, %s.\n",__FUNCTION__, pstIndFunTable->ATCmdName);

        pfnIndFun = pstIndFunTable->pfnIndFun;
        ulRet = (pfnIndFun)(pData);

        return ulRet;
    }

    mntn_UpdateMsgInfo(&g_stmntn.stunMsg, pData->ulMsgId);

    return ERR_MSP_FAILURE;
}

/*****************************************************************************
 Function Name   : l4a_DealAtTafReqEntry
 Description     : AT和TAF给到L4A的请求处理入口
 Input           :L4A_DATA_MSG_STRU* pData
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-5-25  Draft Enact

*****************************************************************************/
VOS_UINT32 l4a_DealAtTafReqEntry(L4A_DATA_MSG_STRU* pData)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    PFN_L4A_REQ_MSG_FUN pfnReqFun = NULL;
    L4A_FW_MSG_FUN_TABLE_STRU* pstFunTable = NULL;

    pstFunTable = l4a_FwProGetMsgFun(pData->enMsgId, L4A_REQ_FLAG);
    if(NULL == pstFunTable)
    {
        mntn_UpdateMsgInfo(&g_stmntn.stunMsg, pData->enMsgId);

        L4A_INFO_LOG("%s, %d.\n",__FUNCTION__, __LINE__);

        return ERR_MSP_INVALID_OP;
    }

    L4A_INFO_LOG("%s, %s.\n",__FUNCTION__, pstFunTable->ATCmdName);

    mntn_UpdateMsgInfo(&g_stmntn.stMsgInfoRx, pData->enMsgId);

    pfnReqFun = pstFunTable->pfnReqFun;
    if(NULL == pfnReqFun)
    {
        return ERR_MSP_INVALID_OP;
    }

    ulRet = (pfnReqFun)(pData, pstFunTable->ulPsReqMsgId, pstFunTable->ulPsReqPid);

    if(ulRet == ERR_MSP_WAIT_ASYNC)
    {
        return l4a_AddCmdToList(pData,pstFunTable);
    }
    else if(ulRet == ERR_MSP_SUCCESS)
    {
        return ERR_MSP_SUCCESS;
    }
    else
    {
        return ERR_MSP_FAILURE;
    }
}


/*****************************************************************************
 Function Name   : l4a_TaskInit
 Description     : L4A PID初始化链表
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-5-25  Draft Enact

*****************************************************************************/
VOS_UINT32 l4a_TaskInit(VOS_VOID)
{
    HI_LIST_S* pHeadNode = NULL;
    VOS_UINT32 ret = ERR_MSP_SUCCESS;

    /* 获取链表头 */
    pHeadNode= l4a_GetNodeHead();

    /* 初始化请求链表 */
    HI_INIT_LIST_HEAD(pHeadNode);

    /* 创建节点保护信号量*/
    ret = VOS_SmBCreate(NULL, 1, VOS_SEMA4_FIFO, &g_ulL4aNodeSem);

    (VOS_VOID)VOS_MemSet(&g_stmntn, 0, sizeof(g_stmntn));

    return ret;
}

/*****************************************************************************
 Function Name   : l4a_MsgProc
 Description     : L4A PID初始化
 Input           :MsgBlock* pMsgBlock
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-5-25  Draft Enact

*****************************************************************************/
VOS_UINT32 l4a_MsgProcInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32 ret = 0;

    if (ip == VOS_IP_RESTART)
    {
        ret =  l4a_TaskInit();
        if(ERR_MSP_SUCCESS != ret)
        {
            L4A_ERROR_LOG("[%s] l4a_TaskInit failed ret 0x%x.\n", __FUNCTION__, ret);
        }
    }

    return 0;
}

/*****************************************************************************
 Function Name   : l4a_MsgProc
 Description     : L4A 任务处理
 Input           :MsgBlock* pMsgBlock
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-5-25  Draft Enact

*****************************************************************************/
VOS_VOID l4a_MsgProc(MsgBlock* pMsgBlock)
{
    REL_TIMER_MSG *pTimer =NULL;
    L4A_DATA_MSG_STRU* pMsgTmp =NULL;
    L4A_PS_MSG_STRU* pData  =NULL;

    /* 入参判断 */
    if (NULL == pMsgBlock)
    {
        L4A_ERROR_LOG("[%s] pMsgBlock NULL.\n", __FUNCTION__);
        return;
    }

    /* 任务开始处理，不允许睡眠 */
    drx_taf_fid_vote_lock(DRX_L4A_VOTE);

    /*根据发送PID，执行不同处理*/
    switch(pMsgBlock->ulSenderPid)
    {
        /* 超时消息，按照超时包格式，打包回复 */
        case DOPRA_PID_TIMER:

            L4A_INFO_LOG("%s,DOPRA_PID_TIMER.\n",__FUNCTION__);

            pTimer   = (REL_TIMER_MSG*)pMsgBlock; /*lint !e740*/
            (VOS_VOID)l4a_DealTimeOutCmdEntry((L4A_RX_INFO_STRU*)(pTimer->ulPara));
            break;

        /* 接收到at发过来的数据，发给ps */
        case WUEPS_PID_TAF:
        case WUEPS_PID_AT:
        case WUEPS_PID_MMA:

            L4A_INFO_LOG("%s, TAF/AT/MMA SenderPid 0x%x.\n",__FUNCTION__, pMsgBlock->ulSenderPid);

            pMsgTmp = (L4A_DATA_MSG_STRU*)pMsgBlock; /*lint !e740*/
            (VOS_VOID)l4a_DealAtTafReqEntry(pMsgTmp);
            break;

        /* 接收PS OM的消息 */
        case PS_PID_OM:
        case PS_PID_MM:
        case PS_PID_ESM:
        case PS_PID_ERRC:
        case MSP_L4_L4A_PID:

            L4A_INFO_LOG("%s, OM/MM/ESM/ERRC SenderPid 0x%x.\n",__FUNCTION__, pMsgBlock->ulSenderPid);

            pData = (L4A_PS_MSG_STRU*)pMsgBlock; /*lint !e740*/
            (VOS_VOID)l4a_DealPsIndCnfEntry(pData);
            break;

        /* 接收到其他PID发过来的错误数据，不予处理 */
        default:

            L4A_INFO_LOG("%s, SenderPid 0x%x.\n",__FUNCTION__, pMsgBlock->ulSenderPid);
            break;
    }

    /* 任务处理完成，允许睡眠 */
    drx_taf_fid_vote_unlock(DRX_L4A_VOTE);

    return;
}


/*****************************************************************************
 函 数 名  : L4A_MailboxMsgProc
 功能描述  : 邮箱数据读取
 输入参数  :
 输出参数  : 无
 返 回 值  : 0无数据，大于0为邮箱数据长度
*****************************************************************************/
VOS_UINT32 L4A_MailboxMsgProc(VOS_VOID)
{
    VOS_UINT32 ulRet      = 0;
    VOS_UINT32 ulMsgSize  = 0;
    VOS_VOID* pMailBoxMsg = NULL;
    L4A_ISMCOEX_CNF_STRU* pDspCnf = NULL;

    /* 读取消息长度 */
    ulMsgSize = BSP_MailBox_ComMsgSize(EN_MAILBOX_SERVICE_LTE_COEX);
    if(0 == ulMsgSize)
    {
        return 0;
    }

    pMailBoxMsg = VOS_MemAlloc(MSP_L4_L4A_PID, DYNAMIC_MEM_PT, ulMsgSize);
    if(NULL == pMailBoxMsg)
    {
        L4A_ERROR_LOG("[%s] VOS_MemAlloc failed.\n", __FUNCTION__);
        return 0;
    }

    /* 读取邮箱数据 */
    ulRet = BSP_MailBox_ComMsgRead(EN_MAILBOX_SERVICE_LTE_COEX, pMailBoxMsg, ulMsgSize, EN_MAILBOX_SLEEP_WAKEUP);
    if(ulRet != VOS_OK)
    {
        (VOS_VOID)VOS_MemFree(MSP_L4_L4A_PID, pMailBoxMsg);
        L4A_ERROR_LOG("[%s] BSP_MailBox_ComMsgRead failed,ulRet %d.\n", __FUNCTION__, ulRet);
        return 0;
    }

    if(ulMsgSize == sizeof(LMSP_LPHY_LTE_WIFI_COEX_SET_CNF_STRU))
    {
        pDspCnf = (L4A_ISMCOEX_CNF_STRU*)VOS_AllocMsg(MSP_L4_L4A_PID, (sizeof(L4A_ISMCOEX_CNF_STRU)-VOS_MSG_HEAD_LENGTH));
        if(NULL == pDspCnf)
        {
            L4A_ERROR_LOG("[%s] VOS_AllocMsg failed.\n", __FUNCTION__);
            return ulMsgSize;
        }

        pDspCnf->ulReceiverPid = MSP_L4_L4A_PID;
        pDspCnf->ulSenderPid   = MSP_L4_L4A_PID;
        pDspCnf->enMsgId       = ID_LMSP_LPHY_LTE_WIFI_COEX_SET_CNF;
        pDspCnf->ulErrorCode   = (VOS_UINT32)((LMSP_LPHY_LTE_WIFI_COEX_SET_CNF_STRU*)pMailBoxMsg)->enCoexParaConfigResult;

        ulRet = VOS_SendMsg(MSP_L4_L4A_PID, pDspCnf);
        if (ulRet != VOS_OK)
        {
            L4A_ERROR_LOG("[%s] send msg to MSP_SYS_FTM_PID FAILED \n",  __FUNCTION__);
        }
    }

    return ulMsgSize;
}


VOS_VOID l4a_MailboxCb(MAILBOX_INT_TYPE_E enIntType)
{
    (VOS_VOID)VOS_SmV(g_ulL4aMbxSem);

    return;
}


VOS_VOID l4a_MailboxProc(VOS_UINT32 ulPara1, VOS_UINT32 ulPara2,
                            VOS_UINT32 ulPara3, VOS_UINT32 ulPara4)
{
    /* 创建读邮箱同步信号量*/
    if(VOS_OK != VOS_SmBCreate("L4AMBX", 0, VOS_SEMA4_FIFO, &g_ulL4aMbxSem))
    {
        L4A_ERROR_LOG("[%s] VOS_SmBCreate failed.\n", __FUNCTION__);
        return ;
    }

    if(VOS_OK != BSP_MailBox_ComNotifyReg(EN_MAILBOX_SERVICE_LTE_COEX, l4a_MailboxCb))
    {
        L4A_ERROR_LOG("[%s] BSP_MailBox_ComNotifyReg failed.\n", __FUNCTION__);
        return ;
    }

    while(1)     /*lint !e716*/
    {
        if(VOS_OK != VOS_SmP(g_ulL4aMbxSem, 0))
        {
            L4A_ERROR_LOG("[%s] VOS_SmP failed.\n", __FUNCTION__);

            continue;
        }

        /* 如果读取到的消息再触发一次读取 */
        if(L4A_MailboxMsgProc() > 0)
        {
            (VOS_VOID)VOS_SmV(g_ulL4aMbxSem);
        }
    }
}


/*****************************************************************************
 Function Name   : MSP_L4FidInit
 Description     : L4A任务注册
 Input           :enum VOS_INIT_PHASE_DEFINE ip
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-5-25  Draft Enact

*****************************************************************************/
VOS_UINT32 MSP_L4FidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32 ulRelVal;

    switch (ip)
    {
    case VOS_IP_LOAD_CONFIG:

        ulRelVal = VOS_RegisterPIDInfo(MSP_L4_L4A_PID, (Init_Fun_Type) l4a_MsgProcInit, (Msg_Fun_Type) l4a_MsgProc);

        if (ulRelVal != VOS_OK)
        {
            return VOS_ERR;
        }

        ulRelVal = VOS_RegisterMsgTaskPrio(MSP_L4_FID, VOS_PRIORITY_M2);

        if (ulRelVal != VOS_OK)
        {
            return VOS_ERR;
        }

        ulRelVal = VOS_RegisterSelfTask(MSP_L4_FID, l4a_MailboxProc, VOS_PRIORITY_M2, 4096);
        if (ulRelVal != VOS_OK)
        {
            L4A_ERROR_LOG("%s, VOS_RegisterSelfTask failed.\n",__FUNCTION__);
            return VOS_ERR;
        }

        break;

    default:
        break;
    }

    return VOS_OK;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

