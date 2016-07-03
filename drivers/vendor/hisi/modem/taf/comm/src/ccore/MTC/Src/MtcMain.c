
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MtcMain.h"
#include "MtcComm.h"
#include "MtcCtx.h"
#include "MtcIntrusion.h"
#include "MtcPsTransfer.h"
#include "CmmcaMtcInterface.h"
#include "MtcRfLcdIntrusion.h"
#include "TafMtcApi.h"

#include "ImsaMtcInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_MTC_MAIN_C


/*****************************************************************************
  2 全局变量声明
*****************************************************************************/
/* MTC模块处理来自Modem0 Mma消息函数对应表*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem0MmaTab[] =
{
    {ID_MMA_MTC_POWER_STATE_IND,            MTC_RcvMmaPowerStateInd},           /* Modem0开关机状态通知 */
    {ID_MMA_MTC_RAT_MODE_IND,               MTC_RcvMmaRatModeInd},              /* 接入模式通知 */

    {ID_MMA_MTC_CURR_CAMP_PLMN_INFO_IND,    MTC_RcvMmaCurrCampPlmnInfoInd},

    {ID_MMA_MTC_EPLMN_INFO_IND,             MTC_RcvMmaEplmnInfoInd},

    {ID_MMA_MTC_REG_STATUS_IND,             MTC_RcvMmaRegStatusInd},

    {ID_MMA_MTC_IMSA_STATE_IND,             MTC_RcvMmaImsaStateInd},

    {ID_MMA_MTC_IMS_VOICE_CAP_IND,          MTC_RcvMmaImsVoiceCapInd},

    {ID_MMA_MTC_RAT_CFG_IND,                MTC_RcvMmaRatCfgInd},
};

/* MTC模块处理来自Modem1 Mma消息函数对应表*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem1MmaTab[] =
{
    {ID_MMA_MTC_POWER_STATE_IND,            MTC_RcvMmaPowerStateInd},           /* Modem1开关机状态通知 */
    {ID_MMA_MTC_RAT_MODE_IND,               MTC_RcvMmaRatModeInd},              /* 接入模式通知 */

    {ID_MMA_MTC_CURR_CAMP_PLMN_INFO_IND,    MTC_RcvMmaCurrCampPlmnInfoInd},

    {ID_MMA_MTC_EPLMN_INFO_IND,             MTC_RcvMmaEplmnInfoInd},

    {ID_MMA_MTC_REG_STATUS_IND,             MTC_RcvMmaRegStatusInd},

    {ID_MMA_MTC_RAT_CFG_IND,                MTC_RcvMmaRatCfgInd},
};

#if (3 == MULTI_MODEM_NUMBER)

/* MTC模块处理来自Modem2 Mma消息函数对应表*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem2MmaTab[] =
{
    {ID_MMA_MTC_POWER_STATE_IND,            MTC_RcvMmaPowerStateInd},           /* Modem2开关机状态通知 */
    {ID_MMA_MTC_RAT_MODE_IND,               MTC_RcvMmaRatModeInd},              /* 接入模式通知 */
    {ID_MMA_MTC_CURR_CAMP_PLMN_INFO_IND,    MTC_RcvMmaCurrCampPlmnInfoInd},
    {ID_MMA_MTC_EPLMN_INFO_IND,             MTC_RcvMmaEplmnInfoInd},
    {ID_MMA_MTC_REG_STATUS_IND,             MTC_RcvMmaRegStatusInd},
    {ID_MMA_MTC_RAT_CFG_IND,                MTC_RcvMmaRatCfgInd},
};

#endif

/* MTC模块处理来自Modem0 Taf消息函数对应表*/
const MTC_MSG_PROC_STRU g_astMtcMsgProcModem0TafTab[] =
{
    {ID_MTC_CS_SERVICE_INFO_IND,            MTC_RcvTafCsSrvInfoInd},            /* CS域业务状态通知 */
};

/* MTC模块处理来自Modem1 Taf消息函数对应表*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem1TafTab[] =
{
    {ID_MTC_CS_SERVICE_INFO_IND,            MTC_RcvTafCsSrvInfoInd},            /* CS域业务状态通知 */
};

/* MTC模块处理来自Modem2 Taf消息函数对应表*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem2TafTab[] =
{
    {ID_MTC_CS_SERVICE_INFO_IND,            MTC_RcvTafCsSrvInfoInd},            /* CS域业务状态通知 */
};

/* MTC模块处理来自Modem1 GAS消息函数对应表*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem1GasTab[] =
{
    {ID_RRC_MTC_INTRUSION_ACTION_SET_CNF,   MTC_RcvIntrusionActionSetCnf},      /* 干扰控制开关设置回复 */
    {ID_RRC_MTC_INTRUSION_BAND_SET_CNF,     MTC_RcvIntrusionBandSetCnf},        /* 干扰控制禁用频段设置回复 */
    {ID_RRC_MTC_INTRUSION_BAND_INFO_IND,    MTC_RcvIntrusionBandInfoInd},       /* 频段信息主动上报 */

    {ID_RRC_MTC_NCELL_INFO_IND,             MTC_RcvRrcNcellInfoInd},
    {ID_RRC_MTC_USING_FREQ_IND,             MTC_RcvRrcUsingFreqInd},            /* 接入层主的上报频点变化消息 */
    {ID_RRC_MTC_GSM_CELL_INFO_IND,          MTC_RcvGsmCellInfoInd},             /* 上报频点和信号强度消息 */

    {ID_RRC_MTC_GSM_CELL_INFO_EX_IND,       MTC_RcvGsmCellInfoExInd},           /* GAS上报小区扩展信息消息 */

};

const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem2GasTab[] =
{
    {ID_RRC_MTC_NCELL_INFO_IND,             MTC_RcvRrcNcellInfoInd},
   // {ID_RRC_MTC_USING_FREQ_IND,             MTC_RcvRrcUsingFreqInd},            /* 接入层主的上报频点变化消息 */
   // {ID_RRC_MTC_GSM_CELL_INFO_IND,          MTC_RcvGsmCellInfoInd},             /* 上报频点和信号强度消息 */
    {ID_RRC_MTC_GSM_CELL_INFO_EX_IND,       MTC_RcvGsmCellInfoExInd},           /* GAS上报小区扩展信息消息 */

};


/* MTC模块处理来自Modem0 TD-SCDMA消息函数对应表*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem0TdsTab[] =
{
    {ID_RRC_MTC_INTRUSION_ACTION_SET_CNF,   MTC_RcvIntrusionActionSetCnf},      /* 干扰控制开关设置回复 */
    {ID_RRC_MTC_INTRUSION_BAND_SET_CNF,     MTC_RcvIntrusionBandSetCnf},        /* 干扰控制禁用频段设置回复 */
    {ID_RRC_MTC_INTRUSION_BAND_INFO_IND,    MTC_RcvIntrusionBandInfoInd},       /* 频段信息主动上报 */
    {ID_RRC_MTC_AREA_LOST_IND,              MTC_RcvRrcAreaLostInd},             /* 接入层丢网信息主动上报 */
    {ID_RRC_MTC_USING_FREQ_IND,             MTC_RcvRrcUsingFreqInd},            /* 接入层主的上报频点变化消息 */

    {ID_RRC_MTC_AREA_AVALIABLE_IND,         MTC_RcvRrcAreaAvaliableInd},        /* 接入层网络恢复信息主动上报 */
};

/* MTC模块处理来自Modem0 LTE消息函数对应表*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem0LteTab[] =
{
    {ID_RRC_MTC_INTRUSION_ACTION_SET_CNF,   MTC_RcvIntrusionActionSetCnf},      /* 干扰控制开关设置回复 */
    {ID_RRC_MTC_INTRUSION_BAND_SET_CNF,     MTC_RcvIntrusionBandSetCnf},        /* 干扰控制禁用频段设置回复 */
    {ID_RRC_MTC_INTRUSION_BAND_INFO_IND,    MTC_RcvIntrusionBandInfoInd},       /* 频段信息主动上报 */
    {ID_RRC_MTC_AREA_LOST_IND,              MTC_RcvRrcAreaLostInd},             /* 接入层丢网信息主动上报 */
    {ID_RRC_MTC_AREA_AVALIABLE_IND,         MTC_RcvRrcAreaAvaliableInd},        /* 接入层网络恢复信息主动上报 */
    {ID_RRC_MTC_USING_FREQ_IND,             MTC_RcvRrcUsingFreqInd},            /* 接入层主的上报频点变化消息 */
};

/* MTC模块处理来自Modem0Gas消息函数对应表*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem0GasTab[] =
{
    {ID_RRC_MTC_USING_FREQ_IND,             MTC_RcvRrcUsingFreqInd},            /* 接入层主的上报频点变化消息 */
};

/* MTC模块处理来自Modem0 Was消息函数对应表*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem0WasTab[] =
{
    {ID_RRC_MTC_USING_FREQ_IND,             MTC_RcvRrcUsingFreqInd},            /* 接入层主的上报频点变化消息 */
};

/* MTC模块处理来自CMMCA消息函数对应表*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcCmmcaTab[] =
{
    {ID_CMMCA_MTC_OTHER_RAT_INFO_IND,       MTC_RcvCmmcaOtherRatInfoInd},
};

const MTC_MSG_PROC_STRU                 g_astMtcMsgProcMtcTab[] =
{
    {ID_MSG_MTC_CDMA_CONN_STATE_IND,          MTC_ProcSetCdmaExtModemConnStateInfo},
    {ID_MSG_MTC_MODEM_SERVICE_CONN_STATE_IND, MTC_ProcModemServiceConnStateInd},
    {ID_MSG_MTC_USIMM_STATE_IND,              MTC_ProcUsimmStateInd},
    {ID_MSG_MTC_BEGIN_SESSION_IND,            MTC_ProcBeginSessionInd},
    {ID_MSG_MTC_END_SESSION_IND,              MTC_ProcEndSessionInd},
};

/* MTC模块处理来自Modem0 Mta消息函数对应表*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem0MtaTab[] =
{
    {ID_MTA_MTC_GSM_CELLINFO_QRY_REQ,       MTC_RcvMtaGsmCellInfoQryReq},
};

#if (FEATURE_ON == FEATURE_IMS)
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcImsaTab[] =
{
    {ID_IMSA_MTC_SRV_CONN_STATUS_NOTIFY,   MTC_ProcImsaSrvConnStateInfo},
};
#endif

const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem0TcStatTab[] =
{
    {ID_NAS_MTC_TC_STATUS_INFO_IND,        MTC_RcvTcStatusInfo},                /* TC换回状态通知 */
};
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem1TcStatTab[] =
{
    {ID_NAS_MTC_TC_STATUS_INFO_IND,        MTC_RcvTcStatusInfo},                /* TC换回状态通知 */
};
#if (3 == MULTI_MODEM_NUMBER)
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem2TcStatTab[] =
{
    {ID_NAS_MTC_TC_STATUS_INFO_IND,        MTC_RcvTcStatusInfo},                /* TC换回状态通知 */
};
#endif
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem0ETcStatTab[] =
{
    {ID_NAS_MTC_TC_STATUS_INFO_IND,        MTC_RcvTcStatusInfo},                /* TC换回状态通知 */
};

/*****************************************************************************
  3 函数声明
*****************************************************************************/

VOS_UINT32 MTC_SearchMsgProcTab(
    VOS_UINT32                          ulMsgCnt,
    VOS_VOID                           *pstMsg,
    const MTC_MSG_PROC_STRU            *pstMsgProcTab
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMsgName;

    /* 从消息包中获取MSG ID */
    ulMsgName  = ((MSG_HEADER_STRU*)pstMsg)->ulMsgName;

    /* 查表，进行消息分发 */
    for (ulLoop = 0; ulLoop < ulMsgCnt; ulLoop++)
    {
        if (pstMsgProcTab[ulLoop].ulMsgType == ulMsgName)
        {
            /* 异常保护 */
            if (VOS_NULL_PTR != pstMsgProcTab[ulLoop].pProcMsgFunc)
            {
                pstMsgProcTab[ulLoop].pProcMsgFunc(pstMsg);
            }
            break;
        }
    }

    /* 没有找到匹配的消息 */
    if (ulMsgCnt == ulLoop)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_VOID MTC_RcvModem0MmaMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* 从g_astMtcMsgProcModem0MmaTab中获取消息个数 */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem0MmaTab) / sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem0MmaTab查表，进行消息分发*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem0MmaTab);

    /* 没有找到匹配的消息 */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem0MmaMsg: Msg Id is invalid!");
    }

    return;
}


VOS_VOID MTC_RcvModem1MmaMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* 从g_astMtcMsgProcModem1MmaTab中获取消息个数 */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem1MmaTab) / sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem1MmaTab查表，进行消息分发*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem1MmaTab);

    /* 没有找到匹配的消息 */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem1MmaMsg: Msg Id is invalid!");
    }

    return;
}


VOS_VOID MTC_RcvModem0TafMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* 从g_astMtcMsgProcModem0TafTab中获取消息个数 */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem0TafTab) / sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem0TafTab查表，进行消息分发*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem0TafTab);

    /* 没有找到匹配的消息 */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem0TafMsg: Msg Id is invalid!");
    }

    return;
}


VOS_VOID MTC_RcvModem1TafMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* 从g_astMtcMsgProcModem1TafTab中获取消息个数 */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem1TafTab) / sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem1TafTab查表，进行消息分发*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem1TafTab);

    /* 没有找到匹配的消息 */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem1TafMsg: Msg Id is invalid!");
    }

    return;
}


VOS_VOID MTC_RcvModem1GasMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* 从g_astMtcMsgProcModem1GasTab中获取消息个数 */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem1GasTab) / sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem1GasTab查表，进行消息分发*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem1GasTab);

    /* 没有找到匹配的消息 */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem1GasMsg: Msg Id is invalid!");
    }

    return;
}

#if (3 == MULTI_MODEM_NUMBER)

VOS_VOID MTC_RcvModem2MmaMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* 从g_astMtcMsgProcModem2MmaTab中获取消息个数 */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem2MmaTab) / sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem2MmaTab查表，进行消息分发*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem2MmaTab);

    /* 没有找到匹配的消息 */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem2MmaMsg: Msg Id is invalid!");
    }

    return;
}


VOS_VOID MTC_RcvModem2TafMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* 从g_astMtcMsgProcModem2TafTab中获取消息个数 */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem2TafTab) / sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem2TafTab查表，进行消息分发*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem2TafTab);

    /* 没有找到匹配的消息 */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem2TafMsg: Msg Id is invalid!");
    }

    return;
}


VOS_VOID MTC_RcvModem2GasMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* 从g_astMtcMsgProcModem2GasTab中获取消息个数 */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem2GasTab) / sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem2GasTab查表，进行消息分发*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem2GasTab);

    /* 没有找到匹配的消息 */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem2GasMsg: Msg Id is invalid!");
    }

    return;
}


VOS_VOID MTC_RcvModem2TcMsg(
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* 从g_astMtcMsgProcModem2TcStatTab中获取消息个数 */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem2TcStatTab) / sizeof(MTC_MSG_PROC_STRU);

    /* g_astMtcMsgProcModem2TcStatTab查表，进行消息分发 */
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem2TcStatTab);

    /* 没有找到匹配的消息 */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem2TcMsg: Msg Id is invalid!");
    }

    return;
}
#endif


VOS_VOID MTC_RcvModem0TdsMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* 从g_astMtcMsgProcModem0TdsTab中获取消息个数 */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem0TdsTab) / sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem0TdsTab查表，进行消息分发*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem0TdsTab);

    /* 没有找到匹配的消息 */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem0TdsMsg: Msg Id is invalid!");
    }

    return;
}


VOS_VOID MTC_RcvModem0LteMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* 从g_astMtcMsgProcModem0LteTab中获取消息个数 */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem0LteTab)/sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem0LteTab查表，进行消息分发*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem0LteTab);

    /* 没有找到匹配的消息 */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem0LteMsg: Msg Id is invalid!");
    }

    return;
}


VOS_VOID MTC_RcvCmmcaMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* 从g_astMtcMsgProcCmmcaTab中获取消息个数 */
    ulMsgCnt = sizeof(g_astMtcMsgProcCmmcaTab)/sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcCmmcaTab查表，进行消息分发*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcCmmcaTab);

    /* 没有找到匹配的消息 */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvCmmcaMsg: Msg Id is invalid!");
    }

    return;
}


VOS_VOID MTC_RcvModem0GasMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* 从g_astMtcMsgProcModem0GasTab中获取消息个数 */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem0GasTab)/sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem0GasTab查表，进行消息分发*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem0GasTab);

    /* 没有找到匹配的消息 */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem0GasMsg: Msg Id is invalid!");
    }

    return;
}


VOS_VOID MTC_RcvModem0WasMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* 从g_astMtcMsgProcModem0WasTab中获取消息个数 */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem0WasTab)/sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem0WasTab查表，进行消息分发*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem0WasTab);

    /* 没有找到匹配的消息 */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem0WasMsg: Msg Id is invalid!");
    }

    return;
}


VOS_VOID MTC_RcvModem0MtaMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* 从g_astMtcMsgProcModem0MtaTab中获取消息个数 */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem0MtaTab)/sizeof(MTC_MSG_PROC_STRU);

    /* g_astMtcMsgProcModem0MtaTab查表，进行消息分发 */
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem0MtaTab);

    /* 没有找到匹配的消息 */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem0MtaMsg: Msg Id is invalid!");
    }

    return;
}


VOS_VOID MTC_RcvMtcMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* 从g_astMtcMsgProcMtcTab中获取消息个数 */
    ulMsgCnt = sizeof(g_astMtcMsgProcMtcTab)/sizeof(MTC_MSG_PROC_STRU);

    /* g_astMtcMsgProcMtcTab查表，进行消息分发 */
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcMtcTab);

    /* 没有找到匹配的消息 */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvMtcMsg: Msg Id is invalid!");
    }

    return;
}

#if (FEATURE_ON == FEATURE_IMS)

VOS_VOID MTC_RcvImsaMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* 从g_astMtcMsgProcImsaTab中获取消息个数 */
    ulMsgCnt = sizeof(g_astMtcMsgProcImsaTab)/sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcImsaTab查表，进行消息分发*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcImsaTab);

    /* 没有找到匹配的消息 */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvImsaMsg: Msg Id is invalid!");
    }

    return;
}
#endif


VOS_VOID MTC_RcvModem0TcMsg(
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* 从g_astMtcMsgProcModem0TcStatTab中获取消息个数 */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem0TcStatTab) / sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem0TcStatTab查表，进行消息分发*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem0TcStatTab);

    /* 没有找到匹配的消息 */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem0TcMsg: Msg Id is invalid!");
    }

    return;
}


VOS_VOID MTC_RcvModem1TcMsg(
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* 从g_astMtcMsgProcModem1TcStatTab中获取消息个数 */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem1TcStatTab) / sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem1TcStatTab查表，进行消息分发*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem1TcStatTab);

    /* 没有找到匹配的消息 */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem1TcMsg: Msg Id is invalid!");
    }

    return;
}


VOS_VOID MTC_RcvModem0ETcMsg(
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* 从g_astMtcMsgProcModem0ETcStatTab中获取消息个数 */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem0ETcStatTab) / sizeof(MTC_MSG_PROC_STRU);

    /* g_astMtcMsgProcModem0ETcStatTab查表，进行消息分发 */
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem0ETcStatTab);

    /* 没有找到匹配的消息 */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem0ETcMsg: Msg Id is invalid!");
    }

    return;
}



VOS_VOID MTC_ProcMsg(MsgBlock* pMsg)
{
    if (VOS_NULL_PTR == pMsg)
    {
        MTC_ERROR_LOG("MTC_ProcMsg: pMsg Null.");
        return;
    }

    /* 消息的分发处理 */
    switch (pMsg->ulSenderPid)
    {
        /* 来自MMA的消息 */
        case I0_WUEPS_PID_MMA:
            MTC_RcvModem0MmaMsg(pMsg);
            break;

        case I1_WUEPS_PID_MMA:
            MTC_RcvModem1MmaMsg(pMsg);
            break;

        /* 来自TAF的消息 */
        case I0_WUEPS_PID_TAF:
            MTC_RcvModem0TafMsg(pMsg);
            break;

        case I1_WUEPS_PID_TAF:
            MTC_RcvModem1TafMsg(pMsg);
            break;

        case I0_WUEPS_PID_TC:
            MTC_RcvModem0TcMsg(pMsg);
            break;

        case I1_WUEPS_PID_TC:
            MTC_RcvModem1TcMsg(pMsg);
            break;

        case PS_PID_TC:
            MTC_RcvModem0ETcMsg(pMsg);
            break;

        /* 来自modem1 G接入层的消息 */
        case I1_UEPS_PID_GAS:
            MTC_RcvModem1GasMsg(pMsg);
            return;
        /* 来自modem1 G接入层的消息 */
        case I0_UEPS_PID_GAS:
            MTC_RcvModem0GasMsg(pMsg);
            return;

        /* 来自modem1 W接入层的消息 */
        case WUEPS_PID_WRR:
            MTC_RcvModem0WasMsg(pMsg);
            return;

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
        /* 来自modem0 T接入层的消息 */
        case TPS_PID_RRC:
            MTC_RcvModem0TdsMsg(pMsg);
            return;
#endif

#if (FEATURE_ON == FEATURE_LTE)
        /* 来自modem0 L接入层的消息 */
        case PS_PID_ERRC:
            MTC_RcvModem0LteMsg(pMsg);
            return;
#endif

        /* 来自CBPCA的消息 */
        case WUEPS_PID_CMMCA:
            MTC_RcvCmmcaMsg(pMsg);
            return;

        case UEPS_PID_MTC:
            MTC_RcvMtcMsg(pMsg);
            return;

        case UEPS_PID_MTA:
            MTC_RcvModem0MtaMsg(pMsg);
            return;

#if (FEATURE_ON == FEATURE_IMS)
        case PS_PID_IMSA:
            MTC_RcvImsaMsg(pMsg);
            return;
#endif

#if (3 == MULTI_MODEM_NUMBER)
        case I2_WUEPS_PID_MMA:
            MTC_RcvModem2MmaMsg(pMsg);
            break;

        case I2_WUEPS_PID_TAF:
            MTC_RcvModem2TafMsg(pMsg);
            break;

        /* 来自modem2 G接入层的消息 */
        case I2_UEPS_PID_GAS:
            MTC_RcvModem2GasMsg(pMsg);
            return;

        case I2_WUEPS_PID_TC:
            MTC_RcvModem2TcMsg(pMsg);
            break;
#endif

        default:
            return;
    }
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


