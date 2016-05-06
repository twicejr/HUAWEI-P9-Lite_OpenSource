/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MtcMain.c
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2013年07月30日
  最近修改   :
  功能描述   : MTC模块消息处理函数对应表及相关公共处理定义
  函数列表   :
  修改历史   :
  1.日    期   : 2013年7月30日
    作    者   : l60609
    修改内容   : 新生成

******************************************************************************/
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
/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
#include "TafMtcApi.h"
/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */

#include "ImsaMtcInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767 修改人: l00198894; */
#define    THIS_FILE_ID        PS_FILE_ID_MTC_MAIN_C
/*lint +e767 修改人: l00198894; */


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
    /* Added by Y00213812 for RF&LCD干扰规避, 2014-02-07, begin */
    {ID_RRC_MTC_USING_FREQ_IND,             MTC_RcvRrcUsingFreqInd},            /* 接入层主的上报频点变化消息 */
    /* Added by Y00213812 for RF&LCD干扰规避, 2014-02-07, end */
    /* Added by Y00213812 for 主动离网重选, 2014-04-10, begin */
    {ID_RRC_MTC_GSM_CELL_INFO_IND,          MTC_RcvGsmCellInfoInd},             /* 上报频点和信号强度消息 */
    /* Added by Y00213812 for 主动离网重选, 2014-04-10, end */

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
    /* Added by Y00213812 for RF&LCD干扰规避, 2014-02-07, begin */
    {ID_RRC_MTC_USING_FREQ_IND,             MTC_RcvRrcUsingFreqInd},            /* 接入层主的上报频点变化消息 */
    /* Added by Y00213812 for RF&LCD干扰规避, 2014-02-07, end */

    /* Added by Y00213812 for 主动离网重选, 2014-02-07, begin */
    {ID_RRC_MTC_AREA_AVALIABLE_IND,         MTC_RcvRrcAreaAvaliableInd},        /* 接入层网络恢复信息主动上报 */
    /* Added by Y00213812 for 主动离网重选, 2014-02-07, end */
};

/* MTC模块处理来自Modem0 LTE消息函数对应表*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem0LteTab[] =
{
    {ID_RRC_MTC_INTRUSION_ACTION_SET_CNF,   MTC_RcvIntrusionActionSetCnf},      /* 干扰控制开关设置回复 */
    {ID_RRC_MTC_INTRUSION_BAND_SET_CNF,     MTC_RcvIntrusionBandSetCnf},        /* 干扰控制禁用频段设置回复 */
    {ID_RRC_MTC_INTRUSION_BAND_INFO_IND,    MTC_RcvIntrusionBandInfoInd},       /* 频段信息主动上报 */
    {ID_RRC_MTC_AREA_LOST_IND,              MTC_RcvRrcAreaLostInd},             /* 接入层丢网信息主动上报 */
    {ID_RRC_MTC_AREA_AVALIABLE_IND,         MTC_RcvRrcAreaAvaliableInd},        /* 接入层网络恢复信息主动上报 */
    /* Added by Y00213812 for RF&LCD干扰规避, 2014-02-07, begin */
    {ID_RRC_MTC_USING_FREQ_IND,             MTC_RcvRrcUsingFreqInd},            /* 接入层主的上报频点变化消息 */
    /* Added by Y00213812 for RF&LCD干扰规避, 2014-02-07, end */
};

/* Added by Y00213812 for RF&LCD干扰规避, 2014-02-07, begin */
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
/* Added by Y00213812 for RF&LCD干扰规避, 2014-02-07, end */

/* Added by l60609 for L-C互操作项目, 2014-02-19, Begin */
/* MTC模块处理来自CMMCA消息函数对应表*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcCmmcaTab[] =
{
    {ID_CMMCA_MTC_OTHER_RAT_INFO_IND,       MTC_RcvCmmcaOtherRatInfoInd},
};
/* Added by l60609 for L-C互操作项目, 2014-02-19, End */

/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
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
/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */

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
/*****************************************************************************
 函 数 名  : MTC_SearchMsgProcTab
 功能描述  : 查找消息处理函数
 输入参数  : ulMsgCnt       消息列表的大小
             *pstMsg        处理消息
             pstMsgProcTab  消息列表
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : j00174725
    修改内容   : V9R1 干扰控制项目
  2.日    期   : 2014年02月13日
    作    者   : f00179208
    修改内容   : Jazz Narrow Band dcs项目
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

/*****************************************************************************
 函 数 名  : MTC_RcvModem0MmaMsg
 功能描述  : 处理来自Modem0 Mma的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : j00174725
    修改内容   : V9R1 干扰控制项目

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MTC_RcvModem1MmaMsg
 功能描述  : 处理来自Modem1 Mma的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : j00174725
    修改内容   : V9R1 干扰控制项目

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MTC_RcvModem0TafMsg
 功能描述  : 处理来自Modem0 Taf的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MTC_RcvModem1TafMsg
 功能描述  : 处理来自Modem1 Taf的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MTC_RcvModem1GasMsg
 功能描述  : 处理来自Modem1 Gas的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目

*****************************************************************************/
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
/*****************************************************************************
 函 数 名  : MTC_RcvModem2MmaMsg
 功能描述  : 处理来自Modem2 Mma的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月30日
    作    者   : w00281933
    修改内容   : 新增函数，三卡三待，增加处理Modem2的MMA消息

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MTC_RcvModem2TafMsg
 功能描述  : 处理来自Modem2 Taf的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月30日
    作    者   : w00281933
    修改内容   : 新增函数，三卡三待，增加处理Modem2的TAF消息

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MTC_RcvModem2GasMsg
 功能描述  : 处理来自Modem2 Gas的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月30日
    作    者   : w00281933
    修改内容   : 新增函数，三卡三待，增加处理Modem2的GAS消息

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MTC_RcvModem2TcMsg
 功能描述  : 处理来自Tc的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月20日
    作    者   : zwx247453
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MTC_RcvModem0TdsMsg
 功能描述  : 处理来自Modem0 TD-SCDMA的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MTC_RcvModem0LteMsg
 功能描述  : 处理来自Modem0 Lte的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目

*****************************************************************************/
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

/* Added by l60609 for L-C互操作项目, 2014-02-19, Begin */
/*****************************************************************************
 函 数 名  : MTC_RcvCmmcaMsg
 功能描述  : 处理来自CMMCA的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月19日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
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
/* Added by l60609 for L-C互操作项目, 2014-02-19, End */

/* Added by Y00213812 for RF&LCD干扰规避, 2014-02-07, begin */
/*****************************************************************************
 函 数 名  : MTC_RcvModem0GasMsg
 功能描述  : 处理来自Modem0Gas的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月07日
    作    者   : Y00213812
    修改内容   : RF&LCD干扰规避项目

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MTC_RcvModem0WasMsg
 功能描述  : 处理来自Modem0Was的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月07日
    作    者   : Y00213812
    修改内容   : RF&LCD干扰规避项目

*****************************************************************************/
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
/* Added by Y00213812 for RF&LCD干扰规避, 2014-02-07, end */

/*****************************************************************************
 函 数 名  : MTC_RcvModem0MtaMsg
 功能描述  : 处理来自Modem0 MTA的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月17日
    作    者   : l00198894
    修改内容   : 新生成函数
*****************************************************************************/
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

/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
/*****************************************************************************
 函 数 名  : MTC_RcvMtcMsg
 功能描述  : 处理来自MTC内部的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月16日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
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
/*****************************************************************************
 函 数 名  : MTC_RcvImsaMsg
 功能描述  : 处理来自IMSA内部的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月16日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MTC_RcvModem0TcMsg
 功能描述  : 处理来自Tc的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月6日
    作    者   : wx270776
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MTC_RcvModem1TcMsg
 功能描述  : 处理来自Tc的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月6日
    作    者   : wx270776
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MTC_RcvModem0ETcMsg
 功能描述  : 处理来自Tc的消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月6日
    作    者   : wx270776
    修改内容   : 新生成函数
*****************************************************************************/
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

/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */

/*****************************************************************************
 函 数 名  : MTC_ProcMsg
 功能描述  : MTC模块消息处理函数
 输入参数  : MsgBlock* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月13日
    作    者   : j00174725
    修改内容   :  V9R1 干扰控制项目

  2.日    期   : 2014年11月17日
    作    者   : l00198894
    修改内容   : ECID命令产品线定制需求

  3.日    期   : 2015年5月6日
    作    者   : wx270776
    修改内容   : TAS环回测试状态上报

  4.日    期   : 2015年05月30日
   作    者   : w00281933
   修改内容   : Modified for The TSTS Project

  5.日    期   : 2015年7月20日
    作    者   : zwx247453
    修改内容   : 3 mdoem TAS
*****************************************************************************/
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

        /* Added by l60609 for L-C互操作项目, 2014-02-19, Begin */
        /* 来自CBPCA的消息 */
        case WUEPS_PID_CMMCA:
            MTC_RcvCmmcaMsg(pMsg);
            return;
        /* Added by l60609 for L-C互操作项目, 2014-02-19, End */

        /* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
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
        /* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */

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


