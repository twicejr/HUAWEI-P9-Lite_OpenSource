/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : omnosig.c
  版 本 号   : 初稿
  作    者   : 甘兰 47350
  生成日期   : 2011年9月27日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2011年9月27日
    作    者   : 甘兰 47350
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "omprivate.h"
#include "omnosig.h"
#include "hpacomm.h"
#include "wasphycomminterface.h"
#include "RrcPhyInterface.h"
#include "PhyGrmInterface.h"
#include "PhyGasInterface.h"
#include "PhyGasComm.h"
#include "PhyNasInterface.h"
#include "PhyGrrInterface.h"
#include "WttfDspInterface.h"
#include "TtfOamInterface.h"
#include "phytoolinterface.h"
#include "pamom.h"

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#include "csdr_ddr_ram_ext.h"
#include "csdr_1x_decdata_pif.h"
#include "csdr_1x_encdata_pif.h"
#include "cproc_1x_ccbt.h"

#endif


#if (VOS_WIN32 == VOS_OS_VER)
#include "SocInterface.h"
#include "MemoryMap.h"
#else
#include "soc_interface.h"
#endif

/*lint -e767 修改人:g47350;检视人:徐铖 51137;原因:Log打印 */
#define    THIS_FILE_ID        PS_FILE_ID_OM_NO_SIG_C
/*lint +e767 修改人:g47350;检视人:徐铖 51137; */


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

#if (VOS_WIN32 == VOS_OS_VER)

VOS_UINT8 g_aucPhyDataReqAddr[1024];
#define  WTTFPHY_MAC_PHY_DATA_REQ_ADDR  (VOS_UINT32)(&g_aucPhyDataReqAddr[0])

#endif


#define CBT_MOD_ADD(x, y, z)                    (((x) + (y)) % (z))
/* Bit转换为Byte并向上取整 */
#define CBT_BIT2BYTE_BOTTOM(bitlen)             ((bitlen + 7) >> 3)
/* 保存R99 Mailbox VTB 译码数据 */
VOS_UINT8   g_aucOmR99MBData[OM_R99_MAILBOX_MAX_PHY_DATA_IND_LEN];

/*传输格式标识数组*/
VOS_UINT16  g_ausTrchId[OM_UL_TRANS_CHANNEL_NUM] = {1 , 5};

/*保存SN号*/
VOS_UINT32  g_ulOmSerialNum = 0;

VOS_UINT32  g_ulReportFlag = VOS_FALSE;
VOS_BOOL    g_bReleaseAfterTest = VOS_FALSE;

const VOS_INT16 g_asGsmPclToGamma[] = {0, 0, 0, 0};
const VOS_INT16 g_asEdgePclToGamma[] = {-2, -2, 3, 3};

VOS_UINT16                              g_usCBadFrames = 0;
VOS_UINT16                              g_usListModeDataMode = 0;
VOS_UINT16                              g_usListModeCurrentMode = VOS_RATMODE_BUTT;
VOS_UINT32                              g_ulListModeMsgLen = 0;
VOS_UINT8                              *g_pucListModeMsgContext = VOS_NULL_PTR;
CBT_LISI_MODE_CTRL_STRU                 g_stListmodeCtrl;
MODEM_ID_ENUM_UINT16                    g_enListModeWorkModem;


/*Wcdma ListMode 测试过程中需要的所有Req消息*/
CBT_LIST_MODE_MSG_STRU                      g_stWcdmaMsgList[] =
{
    /*LoopBack*/
    {SHL1(ID_RRC_PHY_CELL_SEARCHING_REQ),    0, 0},

    {SHL1(ID_RRC_PHY_CAMPED_MAINCELL_REQ),   0, 0},

    {SHL1(ID_RRC_PHY_RL_SETUP_REQ),          0, 0},

    {SHL1(ID_RRC_PHY_TRCH_CONFIG_REQ),       0, 0},

    {SHL2(ID_RRC_PHY_TRCH_CONFIG_REQ),       0, 0},

    {SHL1(ID_RRC_PHY_CS_PS_IND),             0, 0},

    /*Handover*/
    {SHL1(ID_RRC_PHY_RL_MODIFY_REQ),         0, 0},

    /*Release*/
    {SHL1(ID_RRC_PHY_RELALL_PHYCH_REQ),      0, 0}
};
/*Wcdma ListMode 测试Loopback过程需要的所有消息*/
CBT_CONVERT_MSG_STRU                    g_stWcdmaLoopBackMsg[] =
{
    {SHL1(ID_RRC_PHY_CELL_SEARCHING_REQ),    CBT_TO_DSP, 0, CBT_WCellSearchFunc},
    {SHL1(ID_PHY_RRC_CELL_SEARCH_IND),       DSP_TO_CBT, 0, VOS_NULL_PTR},

    {SHL1(ID_RRC_PHY_CAMPED_MAINCELL_REQ),   CBT_TO_DSP, 0, CBT_WCampedMainCellFunc},
    {SHL1(ID_PHY_RRC_CAMPED_MAINCELL_CNF),   DSP_TO_CBT, 0, VOS_NULL_PTR},

    {SHL1(ID_RRC_PHY_RL_SETUP_REQ),          CBT_TO_DSP, 0, CBT_WRlSetUpDldpchFunc},
    {SHL1(ID_PHY_RRC_RL_SETUP_CNF),          DSP_TO_CBT, 0, VOS_NULL_PTR},

    {SHL1(ID_RRC_PHY_TRCH_CONFIG_REQ),       CBT_TO_DSP, 0, VOS_NULL_PTR},
    {SHL1(ID_PHY_RRC_TRCH_CONFIG_CNF),       DSP_TO_CBT, 0, VOS_NULL_PTR},

    {SHL2(ID_RRC_PHY_TRCH_CONFIG_REQ),       CBT_TO_DSP, 0, VOS_NULL_PTR},
    {SHL2(ID_PHY_RRC_TRCH_CONFIG_CNF),       DSP_TO_CBT, 0, VOS_NULL_PTR},

    {SHL1(ID_RRC_PHY_CS_PS_IND),             CBT_TO_DSP, 0, VOS_NULL_PTR},
    {SHL1(ID_PHY_RRC_SYNC_IND),              DSP_TO_CBT, 0, VOS_NULL_PTR},
};
/*Wcdma ListMode 测试Handover过程需要的所有消息*/
CBT_CONVERT_MSG_STRU                    g_stWcdmaHandOverMsg[] =
{
    {SHL1(ID_RRC_PHY_RL_MODIFY_REQ),         CBT_TO_DSP, 0, CBT_WRlSetUpDldpchFunc},
    {SHL1(ID_PHY_RRC_RL_MODIFY_CNF),         DSP_TO_CBT, 0, VOS_NULL_PTR},

    {SHL1(ID_RRC_PHY_TRCH_CONFIG_REQ),       CBT_TO_DSP, 0, VOS_NULL_PTR},
    {SHL1(ID_PHY_RRC_TRCH_CONFIG_CNF),       DSP_TO_CBT, 0, VOS_NULL_PTR},

    {SHL2(ID_RRC_PHY_TRCH_CONFIG_REQ),       CBT_TO_DSP, 0, VOS_NULL_PTR},
    {SHL2(ID_PHY_RRC_TRCH_CONFIG_CNF),       DSP_TO_CBT, 0, VOS_NULL_PTR},

    /*添加 方便查询同步状态*/
    {SHL1(ID_PHY_RRC_SYNC_IND),              DSP_TO_CBT, 0, VOS_NULL_PTR},
};
/*Wcdma ListMode 测试 Release过程需要的所有消息*/
CBT_CONVERT_MSG_STRU                    g_stWcdmaReleaseMsg[] =
{
    {SHL1(ID_RRC_PHY_RELALL_PHYCH_REQ),      CBT_TO_DSP, 0, VOS_NULL_PTR},
    {SHL1(ID_PHY_RRC_RELALL_PHYCH_CNF),      DSP_TO_CBT, 0, VOS_NULL_PTR},
};

/*Gsm ListMode 测试过程中需要的所有Req消息*/
CBT_LIST_MODE_MSG_STRU                  g_stGsmMsgList[] =
{
    /*LoopBack*/
    {SHL1(ID_MPH_RXLEV_REQ),                    0, 0},
    {SHL1(ID_MPH_START_BCCH_READING),           0, 0},
    {SHL1(ID_MPH_STOP_BCCH_READING),            0, 0},

    {SHL1(ID_MPH_PAGING_MODE_REQ),              0, 0},
    {SHL1(ID_MPH_UPDATE_PARSE_PAGING_PARA_REQ), 0, 0},
    {SHL1(ID_MPH_SI_UPDATE_REQ),                0, 0},
    {SHL1(ID_MPHP_UPDATE_PSI_PARAM_REQ),        0, 0},
    {SHL1(ID_MPH_UPDATE_RESEL_PARA_REQ),        0, 0},

    {SHL1(ID_MPH_RA_REQ),                       0, 0},
    {SHL1(ID_MPH_RA_ABORT_REQ),                 0, 0},
    {SHL1(ID_MPH_IMMED_ASSIGN_REQ),             0, 0},
    {SHL1(ID_MPH_CHANNEL_ASSIGN_REQ),           0, 0},
    {SHL1(ID_VC_GPHY_TEST_MODE_NOTIFY),         0, 0},

    /*Handover*/

    /*Release*/
    {SHL1(ID_MPH_STOP_DEDICATED_REQ),           0, 0},
    {SHL1(ID_MPHC_NETWORK_LOST_REQ),            0, 0},
    {SHL1(ID_MPH_SET_WORK_MODE_REQ),            0, 0},
};
/*Gsm ListMode 测试Loopback过程需要的所有消息*/
CBT_CONVERT_MSG_STRU                    g_stGsmLoopBackMsg[] =
{
    {SHL1(ID_MPH_RXLEV_REQ),                    CBT_TO_DSP, 0, CBT_GeRxLevReqFunc},
    {SHL1(ID_MPH_RXLEV_CNF),                    DSP_TO_CBT, 0, VOS_NULL_PTR},
    {SHL1(ID_MPH_START_BCCH_READING),           CBT_TO_DSP, 0, CBT_GeStartBcchReadingFunc},
    {SHL1(ID_MPH_CELL_SB_IND),                  DSP_TO_CBT, 0, VOS_NULL_PTR},
    {SHL1(ID_MPH_STOP_BCCH_READING),            CBT_TO_DSP, 0, CBT_GeStopBcchReadingFunc},

    {SHL1(ID_MPH_PAGING_MODE_REQ),              CBT_TO_DSP, 0, VOS_NULL_PTR},
    {SHL1(ID_MPH_UPDATE_PARSE_PAGING_PARA_REQ), CBT_TO_DSP, 0, VOS_NULL_PTR},
    {SHL1(ID_MPH_SI_UPDATE_REQ),                CBT_TO_DSP, 0, VOS_NULL_PTR},
    {SHL1(ID_MPHP_UPDATE_PSI_PARAM_REQ),        CBT_TO_DSP, 0, VOS_NULL_PTR},
    {SHL1(ID_MPH_UPDATE_RESEL_PARA_REQ),        CBT_TO_DSP, 0, VOS_NULL_PTR},

    {SHL1(ID_MPH_RA_REQ),                       CBT_TO_DSP, 0, VOS_NULL_PTR},
    {SHL1(ID_MPH_RA_CNF),                       DSP_TO_CBT, 0, VOS_NULL_PTR},
    {SHL1(ID_MPH_RA_ABORT_REQ),                 CBT_TO_DSP, 0, VOS_NULL_PTR},
    {SHL1(ID_MPH_IMMED_ASSIGN_REQ),             CBT_TO_DSP, 0, CBT_GeImmedAssignReqFunc},
    {SHL1(ID_MPH_IMMED_ASSIGN_CNF),             DSP_TO_CBT, 0, VOS_NULL_PTR},
    {SHL1(ID_MPH_CHANNEL_ASSIGN_REQ),           CBT_TO_DSP, 0, CBT_GeChannelAssignReqFunc},
    {SHL1(ID_MPH_CHANNEL_ASSIGN_CNF),           DSP_TO_CBT, 0, VOS_NULL_PTR},
    {SHL1(ID_VC_GPHY_TEST_MODE_NOTIFY),         CBT_TO_DSP, 0, VOS_NULL_PTR},
};
/*Gsm ListMode 测试Handover过程需要的所有消息*/
CBT_CONVERT_MSG_STRU                    g_stGsmHandOverMsg[] =
{
    {SHL1(ID_MPH_CHANNEL_ASSIGN_REQ),           CBT_TO_DSP, 0, CBT_GeChannelAssignReqFunc},
    {SHL1(ID_MPH_CHANNEL_ASSIGN_CNF),           DSP_TO_CBT, 0, VOS_NULL_PTR},
};
/*Gsm ListMode 测试 Release过程需要的所有消息*/
CBT_CONVERT_MSG_STRU                    g_stGsmReleaseMsg[] =
{
    {SHL1(ID_MPH_STOP_DEDICATED_REQ),           CBT_TO_DSP, 0, CBT_GeStopDedicatedReqFunc},
    {SHL1(ID_MPH_STOP_DEDICATED_CNF),           DSP_TO_CBT, 0, VOS_NULL_PTR},
    {SHL1(ID_MPHC_NETWORK_LOST_REQ),            CBT_TO_DSP, 0, VOS_NULL_PTR},
    {SHL1(ID_MPHC_NETWORK_LOST_CNF),            DSP_TO_CBT, 0, VOS_NULL_PTR},
    {SHL1(ID_MPH_SET_WORK_MODE_REQ),            CBT_TO_DSP, 0, VOS_NULL_PTR},
    {SHL1(ID_MPH_SET_WORK_MODE_CNF),            DSP_TO_CBT, 0, VOS_NULL_PTR},
};

/*Wcdma ListMode 测试需要的所有req消息*/
CBT_LIST_MODE_MSG_STRU g_stEdgeMsgList[] =
{
    /*LoopBack*/
    {SHL1(ID_MPH_RXLEV_REQ),                    0, 0},
    {SHL1(ID_MPH_START_BCCH_READING),           0, 0},
    {SHL1(ID_MPH_STOP_BCCH_READING),            0, 0},

    {SHL1(ID_MPH_PAGING_MODE_REQ),              0, 0},
    {SHL1(ID_MPH_UPDATE_PARSE_PAGING_PARA_REQ), 0, 0},
    {SHL1(ID_MPH_SI_UPDATE_REQ),                0, 0},
    {SHL1(ID_MPHP_UPDATE_PSI_PARAM_REQ),        0, 0},
    {SHL1(ID_MPH_UPDATE_RESEL_PARA_REQ),        0, 0},
    /*{SHL1(ID_MPH_BA_LIST),                      0, 0},*/

    {SHL1(ID_MPHP_DL_SETUP_REQ),                0, 0},
    {SHL1(ID_MPHP_DL_RECONFIG_REQ),             0, 0},
    {SHL1(ID_PHP_EGPRS_SRB_REQ),                0, 0},
    {SHL1(ID_MPHP_UL_SETUP_REQ),                0, 0},

    /*Handover*/

    /*Release*/
    {SHL1(ID_MPHP_DL_RELEASE_REQ),              0 , 0},
    {SHL1(ID_MPHP_UL_RELEASE_REQ),              0 , 0},
    {SHL1(ID_MPHC_NETWORK_LOST_REQ),            0, 0},
    {SHL1(ID_MPH_SET_WORK_MODE_REQ),            0, 0},
};

/*Edge ListMode 测试Loopback过程需要的所有消息*/
CBT_CONVERT_MSG_STRU                    g_stEdgeLoopBackMsg[] =
{
    {SHL1(ID_MPH_RXLEV_REQ),                    CBT_TO_DSP, 0, CBT_GeRxLevReqFunc},
    {SHL1(ID_MPH_RXLEV_CNF),                    DSP_TO_CBT, 0, VOS_NULL_PTR},
    {SHL1(ID_MPH_START_BCCH_READING),           CBT_TO_DSP, 0, CBT_GeStartBcchReadingFunc},
    {SHL1(ID_MPH_CELL_SB_IND),                  DSP_TO_CBT, 0, VOS_NULL_PTR},
    {SHL1(ID_MPH_STOP_BCCH_READING),            CBT_TO_DSP, 0, CBT_GeStopBcchReadingFunc},

    {SHL1(ID_MPH_PAGING_MODE_REQ),              CBT_TO_DSP, 0, VOS_NULL_PTR},
    {SHL1(ID_MPH_UPDATE_PARSE_PAGING_PARA_REQ), CBT_TO_DSP, 0, VOS_NULL_PTR},
    {SHL1(ID_MPH_SI_UPDATE_REQ),                CBT_TO_DSP, 0, CBT_GeSiUpdateReqFunc},
    {SHL1(ID_MPHP_UPDATE_PSI_PARAM_REQ),        CBT_TO_DSP, 0, VOS_NULL_PTR},
    {SHL1(ID_MPH_UPDATE_RESEL_PARA_REQ),        CBT_TO_DSP, 0, VOS_NULL_PTR},
/*
    {SHL1(ID_MPH_BA_LIST),                      CBT_TO_DSP, 0, VOS_NULL_PTR},
    {SHL1(ID_MPH_BA_LIST_CNF),                  DSP_TO_CBT, 0, VOS_NULL_PTR},
*/
    {SHL1(ID_MPHP_DL_SETUP_REQ),                CBT_TO_DSP, 0, CBT_GeDlSetupReqFunc},
    {SHL1(ID_MPHP_DL_SETUP_CNF),                DSP_TO_CBT, 0, VOS_NULL_PTR},
/*
    {SHL1(ID_MPH_BA_LIST),                      CBT_TO_DSP, 0, VOS_NULL_PTR},
    {SHL1(ID_MPH_BA_LIST_CNF),                  DSP_TO_CBT, 0, VOS_NULL_PTR},
*/
    {SHL1(ID_MPHP_DL_RECONFIG_REQ),             CBT_TO_DSP, 0, CBT_GeDlSetupReqFunc},
    {SHL1(ID_MPHP_DL_RECONFIG_CNF),             DSP_TO_CBT, 0, VOS_NULL_PTR},
    {SHL1(ID_PHP_EGPRS_SRB_REQ),                CBT_TO_DSP, 0, VOS_NULL_PTR},
    {SHL1(ID_PHP_EGPRS_SRB_CNF),                DSP_TO_CBT, 0, VOS_NULL_PTR},
    {SHL1(ID_MPHP_UL_SETUP_REQ),                CBT_TO_DSP, 0, CBT_GeUlSetupReqFunc},
    {SHL1(ID_MPHP_UL_SETUP_CNF),                DSP_TO_CBT, 0, VOS_NULL_PTR},
};
/*Edge ListMode 测试Handover过程需要的所有消息*/
CBT_CONVERT_MSG_STRU                    g_stEdgeHandOverMsg[] =
{
    {SHL1(ID_MPH_SI_UPDATE_REQ),                CBT_TO_DSP, 0, CBT_GeSiUpdateReqFunc},
    {SHL1(ID_MPH_SI_UPDATE_CNF),                DSP_TO_CBT, 0, VOS_NULL_PTR},
/*
    {SHL1(ID_MPHP_DL_RECONFIG_REQ),             CBT_TO_DSP, 0, CBT_GeDlSetupReqFunc},
    {SHL1(ID_MPHP_DL_RECONFIG_CNF),             DSP_TO_CBT, 0, VOS_NULL_PTR},

    {SHL1(ID_PHP_EGPRS_SRB_REQ),                CBT_TO_DSP, 0, VOS_NULL_PTR},
    {SHL1(ID_PHP_EGPRS_SRB_CNF),                DSP_TO_CBT, 0, VOS_NULL_PTR},
*/
    {SHL1(ID_MPHP_UL_SETUP_REQ),                CBT_TO_DSP, 0, CBT_GeUlSetupReqFunc},
    {SHL1(ID_MPHP_UL_SETUP_CNF),                DSP_TO_CBT, 0, VOS_NULL_PTR},
};

/*Edge ListMode 测试 Release过程需要的所有消息*/
CBT_CONVERT_MSG_STRU                    g_stEdgeReleaseMsg[] =
{
    {SHL1(ID_MPHP_DL_RELEASE_REQ),              CBT_TO_DSP, 0, VOS_NULL_PTR},
    {SHL1(ID_MPHP_DL_RELEASE_CNF),              DSP_TO_CBT, 0, VOS_NULL_PTR},

    {SHL1(ID_MPHP_UL_RELEASE_REQ),              CBT_TO_DSP, 0, VOS_NULL_PTR},
    {SHL1(ID_MPHP_UL_RELEASE_CNF),              DSP_TO_CBT, 0, VOS_NULL_PTR},

    {SHL1(ID_MPHC_NETWORK_LOST_REQ),            CBT_TO_DSP, 0, VOS_NULL_PTR},
    {SHL1(ID_MPHC_NETWORK_LOST_CNF),            DSP_TO_CBT, 0, VOS_NULL_PTR},

    {SHL1(ID_MPH_SET_WORK_MODE_REQ),            CBT_TO_DSP, 0, VOS_NULL_PTR},
    {SHL1(ID_MPH_SET_WORK_MODE_CNF),            DSP_TO_CBT, 0, VOS_NULL_PTR},
};


CBT_MSG_FUN_STRU g_astOmNoSigProcTbl[] =
{
    {OM_BtTransProc,            APP_OM_NON_SIG_BT_TRAN_REQ,     OM_APP_NON_SIG_BT_TRAN_CNF},
    {OM_WSyncStatusProc,        APP_OM_W_SYNC_STATUS_REQ,       OM_APP_W_SYNC_STATUS_CNF},
    {OM_GeDlStatusProc,         APP_OM_GE_DL_STATUS_REQ,        OM_APP_GE_DL_STATUS_CNF},
    {OM_EdgeBlerProc,           APP_OM_EDGE_BLER_REQ,           OM_APP_EDGE_BLER_CNF},
    {OM_BerConfigProc,          APP_OM_W_BER_DATA_REQ,          OM_APP_W_BER_DATA_CNF},

    {CBT_GetListModeMsgID,      APP_OM_LISTMODE_BT_GETMSG_REQ,  OM_APP_LISTMODE_BT_GETMSG_CNF},
    {CBT_ListModeMsgContext,    APP_OM_LISTMODE_BT_TRAN_REQ,    OM_APP_LISTMODE_BT_TRAN_CNF},
    {CBT_ListModeTestProc,      APP_OM_LISTMODE_BT_TEST_REQ,    OM_APP_LISTMODE_BT_TEST_CNF},

    {CBT_CSyncStatusProc,       APP_OM_NON_SIG_BT_C_SYNC_REQ,   OM_APP_NON_SIG_BT_C_SYNC_CNF},
    {CBT_CFrameErrorRate,       APP_OM_NON_SIG_BT_C_FER_REQ,    OM_APP_NON_SIG_BT_C_FER_CNF},
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    {CBT_CSetPower,             APP_OM_BT_C_TX_SET_POWER_REQ,   OM_APP_BT_C_TX_SET_POWER_CNF},
#endif
};


/*非信令控制结构体*/
OM_NOSIG_CTRL_STRU  g_stOmNoSigCtrl;


/*BT非信令支持标记*/
VOS_UINT32  g_ulOmNosigEnable = 0;
VOS_UINT32  g_ulListmodeEnable = 0;

/*存放X模动态搬数地址*/
VOS_UINT32  g_ulCttfCsdr1xRequireAddr = MAIL_BOX_PROTECTWORD_FST;

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : CBT_WCellSearchFunc
 功能描述  : W小区搜索数据转换
 输入参数  : 无
 输出参数  : 无

  修改历史      :
  1.日    期   : 2015-05-28
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CBT_WCellSearchFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen)
{
    CELL_SEARCHING_REQ_STRU            *pstCellSearchingReq;


    /*根据band信息选择每个band需要修改的参数*/
    pstCellSearchingReq = (CELL_SEARCHING_REQ_STRU *)pucData;

    /*修改band*/
    pstCellSearchingReq->stFreqList.usFreqBandNo = (VOS_UINT16)g_stListmodeCtrl.ulBand;

    /*修改chan*/
    pstCellSearchingReq->usFreqInfo = g_stListmodeCtrl.usRxChan;

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : CBT_WCampedMainCellFunc
 功能描述  : W小区驻留数据转换
 输入参数  : 无
 输出参数  : 无

  修改历史      :
  1.日    期   : 2015-05-28
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CBT_WCampedMainCellFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen)
{
    RRC_PHY_CAMPED_MAINCELL_REQ_STRU   *pCampedMaincellReq;


    /*根据band信息选择每个band需要修改的参数*/
    pCampedMaincellReq = (RRC_PHY_CAMPED_MAINCELL_REQ_STRU *)pucData;
    /*修改band no*/
    pCampedMaincellReq->usFreqBandNo  = (VOS_UINT16)g_stListmodeCtrl.ulBand;

    /*修改chan*/
    pCampedMaincellReq->sFreqInfo    = (VOS_INT16)g_stListmodeCtrl.usRxChan;

    /*修改TX RX Sepation*/
    pCampedMaincellReq->usTxRxFreqSeparation = g_stListmodeCtrl.usRxChan - g_stListmodeCtrl.usTxChan;

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : CBT_WRlSetUpDldpchFunc
 功能描述  : W dldpch数据转换
 输入参数  : 无
 输出参数  : 无

  修改历史      :
  1.日    期   : 2015-05-28
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CBT_WRlSetUpDldpchFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen)
{
    RL_SETUP_DL_REQ_STRU               *pstRlSetupReq;


    /*根据band信息选择每个band需要修改的参数*/
    pstRlSetupReq = (RL_SETUP_DL_REQ_STRU *)pucData;

    /*修改band No*/
    pstRlSetupReq->stRlPara1.usFreqBandNo = (VOS_UINT16)g_stListmodeCtrl.ulBand;

    /*修改chan*/
    pstRlSetupReq->stRlPara1.usFreqInfo   = g_stListmodeCtrl.usRxChan;

    /*修改TX RX Sepation*/
    pstRlSetupReq->stRlPara1.usTxRxFreqSeparation  = g_stListmodeCtrl.usRxChan - g_stListmodeCtrl.usTxChan;

    /*UlFreq  = DlFreq - TX_RX_Sepation */
    pstRlSetupReq->stRlPara2.usFreqInfo     = g_stListmodeCtrl.usTxChan;
    pstRlSetupReq->stRlPara2.usFreqBandNo   = (VOS_UINT16)g_stListmodeCtrl.ulBand;

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : CBT_GeRxLevReqFunc
 功能描述  : Gsm/edge RxLev数据转换
 输入参数  : 无
 输出参数  : 无

  修改历史      :
  1.日    期   : 2015-05-28
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CBT_GeRxLevReqFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen)
{
    EVT_MPH_RXLEV_REQ_STRU             *pEvtRxLevReq;


    /*根据GSM band信息选择每个band需要修改的参数*/
    pEvtRxLevReq = (EVT_MPH_RXLEV_REQ_STRU *)pucData;

    pEvtRxLevReq->usFreqBand = (VOS_UINT16)g_stListmodeCtrl.ulBand;

    /*高4位表示频段,低12为表示频点信息*/
    pEvtRxLevReq->usFreqInfo[0] =  ((VOS_UINT16)(g_stListmodeCtrl.ulBand << 12)) \
                            | (0xFFF & g_stListmodeCtrl.usRxChan);
    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : CBT_GeStartBcchReadingFunc
 功能描述  : Gsm/edge StartBcchReading数据转换
 输入参数  : 无
 输出参数  : 无

  修改历史      :
  1.日    期   : 2015-05-28
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CBT_GeStartBcchReadingFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen)
{
    MPH_START_BCCH_READING_STRU * pStartBcchReading;


    /*根据GSM band信息选择每个band需要修改的参数*/
    pStartBcchReading = (MPH_START_BCCH_READING_STRU *)pucData;

    /*高4位表示频段,低12为表示频点信息*/
    pStartBcchReading->usFreqInfo = ((VOS_UINT16)(g_stListmodeCtrl.ulBand << 12)) \
                                    | (0xFFF & g_stListmodeCtrl.usRxChan);
    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : CBT_GeStopBcchReadingFunc
 功能描述  : Gsm/edge StopBcchReading数据转换
 输入参数  : 无
 输出参数  : 无

  修改历史      :
  1.日    期   : 2015-05-28
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CBT_GeStopBcchReadingFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen)
{
    MPH_STOP_BCCH_READING_STRU * pstStopBcchReading;


    /*根据GSM band信息选择每个band需要修改的参数*/
    pstStopBcchReading = (MPH_STOP_BCCH_READING_STRU *)pucData;

    /*高4位表示频段,低12为表示频点信息*/
    pstStopBcchReading->usFreqInfo = ((VOS_UINT16)(g_stListmodeCtrl.ulBand << 12)) \
                                   | (0xFFF & (VOS_UINT16)g_stListmodeCtrl.usRxChan);

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : CBT_GeImmedAssignReqFunc
 功能描述  : Gsm/edge ImmedAssign数据转换
 输入参数  : 无
 输出参数  : 无

  修改历史      :
  1.日    期   : 2015-05-28
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CBT_GeImmedAssignReqFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen)
{
    MPH_IMMED_ASSIGN_REQ_STRU *pstImmedAssign;

    /*根据GSM band信息选择每个band需要修改的参数*/
    pstImmedAssign = (MPH_IMMED_ASSIGN_REQ_STRU *)pucData;

    /*高4位表示频段,低12为表示频点信息*/
    pstImmedAssign->stChanDesc.usFreInfo = ((VOS_UINT16)(g_stListmodeCtrl.ulBand << 12)) \
                                        | (0xFFF & (VOS_UINT16)g_stListmodeCtrl.usRxChan);

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : CBT_GeImmedAssignReqFunc
 功能描述  : Gsm/edge ChannelAssign数据转换
 输入参数  : 无
 输出参数  : 无

  修改历史      :
  1.日    期   : 2015-05-28
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CBT_GeChannelAssignReqFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen)
{
    MPH_CHANNEL_ASSIGN_REQ_STRU        *pstChannelAssignReq;


    /*根据GSM band信息选择每个band需要修改的参数*/
    pstChannelAssignReq = (MPH_CHANNEL_ASSIGN_REQ_STRU *)pucData;

    /*修改PCL*/
    pstChannelAssignReq->usTXPwr = g_stListmodeCtrl.usPcl;
    /*pstChannelAssignReq->usChanMode = GAS_PHY_CHANNEL_MODE_TCH_EFR;*/

    /*高4位表示频段,低12为表示频点信息*/
    pstChannelAssignReq->stChanDesc.usFreInfo = ((VOS_UINT16)(g_stListmodeCtrl.ulBand << 12)) \
                                                | (0xFFF & g_stListmodeCtrl.usRxChan);
    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : CBT_GeStopDedicatedReqFunc
 功能描述  : Gsm/edge StopDedicated数据转换
 输入参数  : 无
 输出参数  : 无

  修改历史      :
  1.日    期   : 2015-05-28
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CBT_GeStopDedicatedReqFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen)
{
    MPH_STOP_DEDICATED_REQ_STRU        *pstStopDedicatedReq;


    /*根据GSM band信息选择每个band需要修改的参数*/
    pstStopDedicatedReq = (MPH_STOP_DEDICATED_REQ_STRU *)pucData;

    pstStopDedicatedReq->usFreqInfo = (VOS_UINT16)g_stListmodeCtrl.usRxChan;

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : CBT_GeStopDedicatedReqFunc
 功能描述  : Gsm/edge SiUpdate数据转换
 输入参数  : 无
 输出参数  : 无

  修改历史      :
  1.日    期   : 2015-05-28
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CBT_GeSiUpdateReqFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen)
{
    MPH_SI_UPDATE_REQ_STRU             *pReq;
    /*修改Max Power*/
    VOS_UINT16 usMaxPcl[CBT_GE_MAX_BAND_SUPPORT] = {5, 5, 0, 0};


    /*(VOS_VOID)LogPrint3("CBT_GeSiUpdateReqFunc: Band: %d, chan: %d, pcl: %d\r\n", g_stListmodeCtrl.ulBand, \
                            g_stListmodeCtrl.usRxChan, g_stListmodeCtrl.usPcl);*/

    if (CBT_GE_MAX_BAND_SUPPORT <= g_stListmodeCtrl.ulBand)
    {
        (VOS_VOID)LogPrint1("CBT_GeSiUpdateReqFunc: Band[%d] error\r\n", g_stListmodeCtrl.ulBand);
        return VOS_ERR;
    }

    pReq = (MPH_SI_UPDATE_REQ_STRU *)pucData;

    pReq->stSIInfo.usMS_TXPWR_MAX_CCH = usMaxPcl[g_stListmodeCtrl.ulBand];

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : CBT_GeDlSetupReqFunc
 功能描述  : Gsm/edge DlSetup数据转换
 输入参数  : 无
 输出参数  : 无

  修改历史      :
  1.日    期   : 2015-05-28
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CBT_GeDlSetupReqFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen)
{
    VOS_UINT16                          usGammaPcl;
    MPHP_DL_SETUP_REQ_ST               *pstMphpDlSetupReq;


    if (CBT_GE_MAX_BAND_SUPPORT <= g_stListmodeCtrl.ulBand)
    {
        (VOS_VOID)LogPrint1("CBT_GeDlSetupReqFunc: Band[%d] error\r\n", g_stListmodeCtrl.ulBand);
        return VOS_ERR;
    }

    /*根据GSM band信息选择每个band需要修改的参数*/
    pstMphpDlSetupReq = (MPHP_DL_SETUP_REQ_ST *)pucData;

    /*高4位表示频段,低12为表示频点信息*/
    pstMphpDlSetupReq->stFreqParams.usArfcn = ((VOS_UINT16)(g_stListmodeCtrl.ulBand << 12)) \
                                             | (0xFFF & g_stListmodeCtrl.usRxChan);

    /*配置功率的gamma值  先将PCL转换成Gamma值*/
    if (CBT_DATA_GSM == g_usListModeDataMode)
    {
        usGammaPcl = (VOS_UINT16)(g_stListmodeCtrl.usPcl + g_asGsmPclToGamma[g_stListmodeCtrl.ulBand]);
    }
    else
    {
        usGammaPcl = (VOS_UINT16)(g_stListmodeCtrl.usPcl + g_asEdgePclToGamma[g_stListmodeCtrl.ulBand]);
    }
    pstMphpDlSetupReq->ausGammaTn[3] = usGammaPcl;

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : CBT_GeDlSetupReqFunc
 功能描述  : Gsm/edge UlSetup数据转换
 输入参数  : 无
 输出参数  : 无

  修改历史      :
  1.日    期   : 2015-05-28
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CBT_GeUlSetupReqFunc(VOS_UINT8 *pucData, VOS_UINT16 usDataLen)
{
    VOS_UINT16                          usGammaPcl;
    MPHP_UL_SETUP_REQ_ST               *pUlSetupReq;


    if (CBT_GE_MAX_BAND_SUPPORT <= g_stListmodeCtrl.ulBand)
    {
        (VOS_VOID)LogPrint1("CBT_GeUlSetupReqFunc: Band[%d] error\r\n", g_stListmodeCtrl.ulBand);
        return VOS_ERR;
    }

    /*根据GSM band信息选择每个band需要修改的参数*/
    pUlSetupReq = (MPHP_UL_SETUP_REQ_ST *)pucData;

    /*高4位表示频段,低12为表示频点信息*/
    pUlSetupReq->stFreqParams.usArfcn = ((VOS_UINT16)(g_stListmodeCtrl.ulBand << 12)) \
                                    | (0xFFF & g_stListmodeCtrl.usRxChan);

    /*配置功率的gamma值  先将PCL转换成Gamma值*/
    if (CBT_DATA_GSM == g_usListModeDataMode)
    {
        usGammaPcl = (VOS_UINT16)(g_stListmodeCtrl.usPcl + g_asGsmPclToGamma[g_stListmodeCtrl.ulBand]);
    }
    else
    {
        usGammaPcl = (VOS_UINT16)(g_stListmodeCtrl.usPcl + g_asEdgePclToGamma[g_stListmodeCtrl.ulBand]);
    }
    pUlSetupReq->ausGammaTn[3] = usGammaPcl;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CBT_GetMsgList
 功能描述  : 通过mode找到需要的消息列表
 输入参数  : 无
 输出参数  : 无

  修改历史      :
  1.日    期   : 2015-05-28
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CBT_GetMsgList(VOS_UINT16 usMode, VOS_UINT32 *pulMsgCount, VOS_UINT32 *pulTraceMsg)
{
    /*找到对应mode下的消息内容指针*/
    if (CBT_DATA_GSM == usMode)
    {
        *pulMsgCount = sizeof(g_stGsmMsgList) / sizeof(g_stGsmMsgList[0]);
        *pulTraceMsg = (VOS_UINT32)g_stGsmMsgList;
    }
    else if (CBT_DATA_EDGE == usMode)
    {
        *pulMsgCount = sizeof(g_stEdgeMsgList) / sizeof(g_stEdgeMsgList[0]);
        *pulTraceMsg = (VOS_UINT32)g_stEdgeMsgList;
    }
    else
    {
        *pulMsgCount = sizeof(g_stWcdmaMsgList) / sizeof(g_stWcdmaMsgList[0]);
        *pulTraceMsg = (VOS_UINT32)g_stWcdmaMsgList;
    }

    return;
}
/*****************************************************************************
 函 数 名  : CBT_GetActionMsg
 功能描述  : 通过mode和action找到合适的消息功能列表
 输入参数  : 无
 输出参数  : 无

  修改历史      :
  1.日    期   : 2015-05-28
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CBT_GetActionMsg(VOS_UINT16 usMode, CBT_ACTION_ENUM enAction,
                        VOS_UINT32 *pulMsgCount, VOS_UINT32 *pulFuncMsg)
{
    if (CBT_DATA_GSM == usMode)
    {
        if (CBT_ACTION_CALL == enAction)
        {
            *pulFuncMsg  = (VOS_UINT32)g_stGsmLoopBackMsg;
            *pulMsgCount = sizeof(g_stGsmLoopBackMsg) / sizeof(g_stGsmLoopBackMsg[0]);
        }
        else if (CBT_ACTION_HANDOVER == enAction)
        {
            *pulFuncMsg  = (VOS_UINT32)g_stGsmHandOverMsg;
            *pulMsgCount = sizeof(g_stGsmHandOverMsg) / sizeof(g_stGsmHandOverMsg[0]);
        }
        else
        {
            *pulFuncMsg  = (VOS_UINT32)g_stGsmReleaseMsg;
            *pulMsgCount = sizeof(g_stGsmReleaseMsg) / sizeof(g_stGsmReleaseMsg[0]);
        }
    }
    else if (CBT_DATA_EDGE == usMode)
    {
        if (CBT_ACTION_CALL == enAction)
        {
            *pulFuncMsg  = (VOS_UINT32)g_stEdgeLoopBackMsg;
            *pulMsgCount = sizeof(g_stEdgeLoopBackMsg) / sizeof(g_stEdgeLoopBackMsg[0]);
        }
        else if (CBT_ACTION_HANDOVER == enAction)
        {
            *pulFuncMsg  = (VOS_UINT32)g_stEdgeHandOverMsg;
            *pulMsgCount = sizeof(g_stEdgeHandOverMsg) / sizeof(g_stEdgeHandOverMsg[0]);
        }
        /*
        else if (CBT_ACTION_PCLHANDOVER == enAction)
        {
            *pulFuncMsg  = (VOS_UINT32)g_stEdgePclHandOverMsg;
            *pulMsgCount = sizeof(g_stEdgePclHandOverMsg) / sizeof(g_stEdgePclHandOverMsg[0]);
        }*/
        else
        {
            *pulFuncMsg  = (VOS_UINT32)g_stEdgeReleaseMsg;
            *pulMsgCount = sizeof(g_stEdgeReleaseMsg) / sizeof(g_stEdgeReleaseMsg[0]);
        }
    }
    else
    {
        if (CBT_ACTION_CALL == enAction)
        {
            *pulFuncMsg  = (VOS_UINT32)g_stWcdmaLoopBackMsg;
            *pulMsgCount = sizeof(g_stWcdmaLoopBackMsg) / sizeof(g_stWcdmaLoopBackMsg[0]);
        }
        else if (CBT_ACTION_HANDOVER == enAction)
        {
            *pulFuncMsg  = (VOS_UINT32)g_stWcdmaHandOverMsg;
            *pulMsgCount = sizeof(g_stWcdmaHandOverMsg) / sizeof(g_stWcdmaHandOverMsg[0]);
        }
        else
        {
            *pulFuncMsg  = (VOS_UINT32)g_stWcdmaReleaseMsg;
            *pulMsgCount = sizeof(g_stWcdmaReleaseMsg) / sizeof(g_stWcdmaReleaseMsg[0]);
        }
    }
}

/*****************************************************************************
 函 数 名  : CBT_GetListModeMsgID
 功能描述  : 获取Listmod测试需要的MsgId
 输入参数  : pstAppToOmMsg： 指向工具发来的数据指针
             usReturnPrimId: 返回给PC工具的PRIMID

 输出参数  : 无
 返 回 值  : VOS_OK:成功，其他为失败

*****************************************************************************/
VOS_UINT32 CBT_GetListModeMsgID(CBT_UNIFORM_MSG_STRU * pstPcToCbtMsg, VOS_UINT16 usReturnPrimId)
{
    VOS_UINT16                          usMode;
    VOS_UINT16                          usIndex;
    VOS_UINT32                          ulMsgCount = 0;
    VOS_UINT32                          ulTotalSize;
    VOS_UINT32                          ulMsgListData;
    VOS_UINT32                         *pulParaData;
    CBT_UNIFORM_MSG_STRU               *pstCbtToPcMsg;
    CBT_LIST_MODE_MSG_STRU             *pstMsgList = VOS_NULL_PTR;
    CBT_GETMSG_CNF_STRU                *pstMsgCnf;

    usMode = *(VOS_UINT16 *)pstPcToCbtMsg->aucPara;
    CBT_GetMsgList(usMode, &ulMsgCount, &ulMsgListData);
    pstMsgList = (CBT_LIST_MODE_MSG_STRU *)ulMsgListData;

    /* 消息头 + result + count + 消息个数*消息大小 */
    ulTotalSize = CBT_MSG_HEAD_EX_LENGTH + 2*sizeof(VOS_UINT32) + ulMsgCount*sizeof(VOS_UINT32);
    pstCbtToPcMsg = (CBT_UNIFORM_MSG_STRU *)VOS_MemAlloc(WUEPS_PID_NOSIG,
                                          DYNAMIC_MEM_PT, ulTotalSize);

    if (VOS_NULL_PTR == pstCbtToPcMsg)
    {
        CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, (VOS_UINT32)VOS_ERR);
        return VOS_ERR;
    }

    pstMsgCnf = (CBT_GETMSG_CNF_STRU *)pstCbtToPcMsg->aucPara;
    pstMsgCnf->ulResult = VOS_OK;
    pstMsgCnf->ulCount  = ulMsgCount;

    pulParaData = (VOS_UINT32 *)pstMsgCnf->aucData;

    for (usIndex = 0; usIndex < ulMsgCount; usIndex++)
    {
        *pulParaData = pstMsgList->ulMsgId;
        pulParaData++;
        pstMsgList++;
    }

    pstCbtToPcMsg->ulMsgLength = ulTotalSize - CBT_MSG_HEAD_EX_LENGTH;
    CBT_SendContentChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, pstCbtToPcMsg);
    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_NOSIG, pstCbtToPcMsg);
    /*lint +e534*/
    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : CBT_UpdateMsgListPos
 功能描述  : 将消息的len 和 pos更新到消息列表中
 输入参数  : 无
 输出参数  : 无

  修改历史      :
  1.日    期   : 2015-05-28
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CBT_UpdateMsgListPos(VOS_UINT16 usMode, VOS_UINT32 ulMsgId, VOS_UINT32 ulLen, VOS_UINT32 ulPos)
{
    VOS_UINT16                          usIndex;
    VOS_UINT32                          ulMsgCount;
    VOS_UINT32                          ulMsgListData;

    CBT_LIST_MODE_MSG_STRU             *pstMsgList = VOS_NULL_PTR;

    CBT_GetMsgList(usMode, &ulMsgCount, &ulMsgListData);
    pstMsgList = (CBT_LIST_MODE_MSG_STRU *)ulMsgListData;

    for (usIndex = 0; usIndex < ulMsgCount; usIndex++, pstMsgList ++)
    {
        if (ulMsgId != pstMsgList->ulMsgId)
        {
            continue;
        }

        pstMsgList->usDataLen  = (VOS_UINT16)ulLen;
        pstMsgList->usPosition = (VOS_UINT16)ulPos;

        return VOS_OK;
    }
    return VOS_ERR;
}
/*****************************************************************************
 函 数 名  : CBT_ListModeTransMsg
 功能描述  : 取得Listmod测试MsgId需要的消息内容
 输入参数  : pstAppToOmMsg： 指向工具发来的数据指针
             usReturnPrimId: 返回给PC工具的PRIMID

 输出参数  : 无
 返 回 值  : VOS_OK:成功，其他为失败

*****************************************************************************/
VOS_UINT32 CBT_ListModeMsgContext(CBT_UNIFORM_MSG_STRU * pstPcToCbtMsg, VOS_UINT16 usReturnPrimId)
{
    VOS_UINT16                          usIndex;
    VOS_UINT16                          usMode;
    VOS_UINT32                          ulOneMsgLen;
    VOS_UINT32                          ulOneMsgId;
    VOS_UINT32                          ulMsgTotalLen = 0;
    VOS_UINT32                          ulMsgCount;
    VOS_UINT32                          ulMsgDataAddr;
    CBT_TRANS_MSG_HEAD_STRU            *pstTransMsg;
    CBT_LISTMODE_MSG_CONTEXT_REQ_STRU  *pstMsgContextReq;

    pstMsgContextReq = (CBT_LISTMODE_MSG_CONTEXT_REQ_STRU *)pstPcToCbtMsg->aucPara;

    usMode        = pstMsgContextReq->usMode;
    ulMsgCount    = pstMsgContextReq->ulMsgCount;
    ulMsgDataAddr = (VOS_UINT32)(pstMsgContextReq->aucData);

    for (usIndex = 0; usIndex < ulMsgCount; usIndex++)
    {
        pstTransMsg  = (CBT_TRANS_MSG_HEAD_STRU *)ulMsgDataAddr;

        ulOneMsgId   = pstTransMsg->ulMsgId;
        /* 2*sizeof(VOS_UINT32) == ulMsgId + ulMsgLen */
        ulOneMsgLen  = pstTransMsg->ulMsgLen + 2*sizeof(VOS_UINT32);

        if (VOS_OK != CBT_UpdateMsgListPos(usMode, ulOneMsgId, ulOneMsgLen, ulMsgTotalLen))
        {
            /*将出错的msgid返回*/
            CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, ulOneMsgId);
            return VOS_ERR;
        }
        /*统计总长度，方便计算偏移量*/
        ulMsgTotalLen += ulOneMsgLen;
        /*数据指针前移*/
        ulMsgDataAddr += ulOneMsgLen;
    }

    if (VOS_NULL_PTR != g_pucListModeMsgContext)
    {
        (VOS_VOID)VOS_MemFree(WUEPS_PID_NOSIG, g_pucListModeMsgContext);
        g_pucListModeMsgContext = VOS_NULL_PTR;
    }

    g_ulListModeMsgLen = ulMsgTotalLen;
    g_pucListModeMsgContext = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_NOSIG, DYNAMIC_MEM_PT, ulMsgTotalLen);

    if (VOS_NULL_PTR == g_pucListModeMsgContext)
    {
        CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, (VOS_UINT32)VOS_ERR);
        return VOS_ERR;
    }

    /*将消息内容拷贝到消息列表中*/
    (VOS_VOID)VOS_MemCpy(g_pucListModeMsgContext, pstMsgContextReq->aucData, ulMsgTotalLen);

    CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, VOS_OK);
    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : CBT_FindPosInMsgList
 功能描述  : 通过msgid 在msglist中找到msgid的索引
 输入参数  : 无
 输出参数  : 无

  修改历史      :
  1.日    期   : 2015-05-28
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CBT_FindPosInMsgList(CBT_LIST_MODE_MSG_STRU *pstMsgList, VOS_UINT32 ulMsgCount, VOS_UINT32 ulMsgId)
{
    VOS_UINT32                          ulMsgIndex = CBT_INDEXNOEXIT;

    for (ulMsgIndex=0; ulMsgIndex < ulMsgCount; ulMsgIndex++)
    {
        if (ulMsgId == pstMsgList[ulMsgIndex].ulMsgId)
        {
            return ulMsgIndex;
        }
    }
    return ulMsgIndex;
}
/*****************************************************************************
 函 数 名  : CBT_SendListModeMsg
 功能描述  : listmode测试，本模块与PHY层测试指令的自动交互
 输入参数  : 无
 输出参数  : 无

  修改历史      :
  1.日    期   : 2015-05-28
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CBT_SendListModeMsg(VOS_UINT16 usMode, CBT_ACTION_ENUM enAction)
{
    VOS_UINT32                          ulMsgIndex;
    VOS_UINT32                          ulActionMsgCount;
    VOS_UINT32                          ulMsgListCount;
    VOS_UINT16                          usMsgLen;
    VOS_UINT16                          usPosition;
    VOS_UINT32                          ulMsgListData;
    VOS_UINT32                          ulMsgActionData;
    VOS_UINT32                          ulPosInMsgList;
    VOS_UINT8                          *pucData;
    CBT_DIRECTION_ENUM_UINT16           enDirection;
    CBT_CONVERT_MSG_STRU               *pstActionMsg = VOS_NULL_PTR;
    CBT_LIST_MODE_MSG_STRU             *pstMsgList = VOS_NULL_PTR;
    CBT_PFNTRANSMSG                     pfnConvertFunc;
    MsgBlock                           *pMsgBlock;

    CBT_GetMsgList(usMode, &ulMsgListCount, &ulMsgListData);
    pstMsgList = (CBT_LIST_MODE_MSG_STRU *)ulMsgListData;
    CBT_GetActionMsg(usMode, enAction, &ulActionMsgCount, &ulMsgActionData);
    pstActionMsg = (CBT_CONVERT_MSG_STRU *)ulMsgActionData;

    (VOS_VOID)VOS_TaskLock();

    for (ulMsgIndex = 0; ulMsgIndex < ulActionMsgCount; ulMsgIndex++)
    {
        enDirection = pstActionMsg[ulMsgIndex].enDirection;

        if (CBT_TO_DSP == enDirection)
        {
            /*找到action消息列表中的消息在Msglist中的位置索引*/
            ulPosInMsgList = CBT_FindPosInMsgList(pstMsgList, ulMsgListCount, pstActionMsg[ulMsgIndex].ulMsgId);

            if (CBT_INDEXNOEXIT == ulPosInMsgList)
            {
                (VOS_VOID)LogPrint1("CBT_SendListModeMsg: Req msgid: 0x%x is not exist in message list.\r\n", pstActionMsg[ulMsgIndex].ulMsgId);

                (VOS_VOID)VOS_TaskUnlock();
                return VOS_ERR;
            }

            /*msgId + msglen = 2*sizeof(VOS_UINT32)*/
            if (2*sizeof(VOS_UINT32) >= pstMsgList[ulPosInMsgList].usDataLen)
            {
                (VOS_VOID)LogPrint1("CBT_SendListModeMsg: Msg Len is too short, msgid: 0x%x.\r\n", pstActionMsg[ulMsgIndex].ulMsgId);
                (VOS_VOID)VOS_TaskUnlock();
                return VOS_ERR;
            }

            usMsgLen   = pstMsgList[ulPosInMsgList].usDataLen - 2*sizeof(VOS_UINT32);
            usPosition = pstMsgList[ulPosInMsgList].usPosition + 2*sizeof(VOS_UINT32);

            if (usPosition + usMsgLen > g_ulListModeMsgLen)
            {
                (VOS_VOID)LogPrint("CBT_SendListModeMsg: List mode Msg Len is out of range.\r\n");
                (VOS_VOID)VOS_TaskUnlock();
                return VOS_ERR;
            }

            pucData = g_pucListModeMsgContext + usPosition;
            pfnConvertFunc = pstActionMsg[ulMsgIndex].pfnCbtTrans;

            pMsgBlock = (MsgBlock *)VOS_AllocMsg(WUEPS_PID_NOSIG, usMsgLen - VOS_MSG_HEAD_LENGTH);

            if (VOS_NULL_PTR == pMsgBlock)
            {
                (VOS_VOID)LogPrint("CBT_SendListModeMsg: VOS_AllocMsg Msg fail ...\r\n");
                (VOS_VOID)VOS_TaskUnlock();
                return VOS_ERR;
            }

            if (VOS_NULL_PTR != pfnConvertFunc)
            {
                if (VOS_OK != (*pfnConvertFunc)(pucData, usMsgLen))
                {
                    (VOS_VOID)VOS_FreeMsg(WUEPS_PID_NOSIG, pMsgBlock);
                    (VOS_VOID)VOS_TaskUnlock();
                    return VOS_ERR;
                }
            }

            (VOS_VOID)VOS_MemCpy(pMsgBlock, pucData, usMsgLen);

            (VOS_VOID)VOS_SendMsg(pMsgBlock->ulSenderPid, pMsgBlock);
        }
        else
        {
            g_stListmodeCtrl.usRecvPrimId = (VOS_UINT16)pstActionMsg[ulMsgIndex].ulMsgId;
            (VOS_VOID)VOS_TaskUnlock();

            if (VOS_OK != VOS_SmP(g_stListmodeCtrl.ulCbtSyncSem, OM_NOSIG_WAIT_TIME_LEN))
            {
                (VOS_VOID)LogPrint1("CBT_SendListModeMsg: receive no responce: 0x%x.\r\n", g_stListmodeCtrl.usRecvPrimId);
                return VOS_ERR;
            }

            (VOS_VOID)VOS_TaskLock();
        }
    }

    (VOS_VOID)VOS_TaskUnlock();
    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : CBT_WcdmaIlpcCtrl
 功能描述  : 设置UE的目标功率
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   : 2015-05-28
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CBT_WcdmaIlpcCtrl(VOS_UINT32 ulMask, VOS_INT16 sInitTxPower)
{
    /*CBT_WPHY_PWR_PARA_SET_REQ_STRU      stCbtToWphySetPwr;*/
    WPHY_TOOL_PWR_PARA_SET_REQ_STRU     stCbtToWphySetPwr;
    MsgBlock                           *pstMsg;

    (VOS_VOID)VOS_MemSet(&stCbtToWphySetPwr, 0x00, sizeof(WPHY_TOOL_PWR_PARA_SET_REQ_STRU));
    stCbtToWphySetPwr.enMsgId        = ID_TOOL_WPHY_PWR_PARA_SET_REQ;
    stCbtToWphySetPwr.enPwrParaMask  = ulMask;

    if (WPHY_MNTN_PWR_PARA_LIST_MODE_SET_PWR == stCbtToWphySetPwr.enPwrParaMask)
    {
        stCbtToWphySetPwr.sInitTxPwr = sInitTxPower;
    }

    /* W mode 给DSP发送消息控制power */
    pstMsg = VOS_AllocMsg(CCPU_PID_CBT, sizeof(WPHY_TOOL_PWR_PARA_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        (VOS_VOID)LogPrint("CBT_WcdmaIlpcCtrl: Alloc message fail. \r\n");
        return VOS_ERR;
    }

    pstMsg->ulReceiverPid = DSP_PID_WPHY;

    /*lint -e534 -e419 -e420*/
    VOS_MemCpy(pstMsg->aucValue, &stCbtToWphySetPwr.enMsgId, sizeof(WPHY_TOOL_PWR_PARA_SET_REQ_STRU)- VOS_MSG_HEAD_LENGTH);
    /*lint +e534 +e419 +e420*/

    DIAG_TraceReport((VOS_VOID *)pstMsg);

    (VOS_VOID)VOS_SendMsg(CCPU_PID_CBT, pstMsg);

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : CBT_TrigerEdgeReportStatus
 功能描述  : 出发edge上报信号质量
 输入参数  : pstAppToOmMsg： 指向工具发来的数据指针
             usReturnPrimId: 返回给PC工具的PRIMID

 输出参数  : 无
 返 回 值  : VOS_OK:成功，其他为失败

*****************************************************************************/
VOS_UINT32 CBT_TrigerEdgeReportStatus()
{
    VOS_UINT32                          ulPreFN;
    VOS_UINT32                          ulCurrentFN;
    VOS_UINT32                          ulRealFN;
    MODEM_ID_ENUM_UINT16                enModemID;
    MsgBlock                           *pstSndMsg;
    PHP_RRBP_FN_REQ                    *pstPhpRrbpReq;

    enModemID = g_stListmodeCtrl.stModemSsid.ucModem;

    pstSndMsg = VOS_AllocMsg(UEPS_PID_GRM, sizeof(PHP_RRBP_FN_REQ) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSndMsg)
    {
        PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_ERROR, "CBT_TrigerEdgeReportStatus :DIAG_DataProc Alloc Msg Failed!\r\n");
        return VOS_ERR;
    }

    if(MODEM_ID_1 == enModemID)
    {
        pstSndMsg->ulSenderPid      = I1_UEPS_PID_GRM;
        pstSndMsg->ulReceiverPid    = I1_DSP_PID_GPHY;   /*发送给卡1的PID*/
    }
    else
    {
        pstSndMsg->ulSenderPid      = I0_UEPS_PID_GRM;
        pstSndMsg->ulReceiverPid    = I0_DSP_PID_GPHY;   /*发送给卡0的PID*/
    }
    /*通过读取寄存器获得当前帧数*/
    ulPreFN  = HPA_Read32Reg(g_aulGUCBBPRegAddr[GTC_FN][enModemID][VOS_RATMODE_GSM]);

    /*当前帧数由两部分组成，高16位*1326 + 低16位寄存器值*/
    ulCurrentFN  = ((ulPreFN >> 16)& OM_FRAME_NUM_REG_MASKBIT)* OM_HIHG_ADDR_FRAME_NUM;
    ulCurrentFN  += (ulPreFN & OM_FRAME_NUM_REG_MASKBIT);

    /*实际帧数为当前帧数加上下发消息时间估计值*/
    ulRealFN     = (ulCurrentFN + OM_DL_MSG_FRAME_NUM ) % OM_FRAME_MAX_NUM;

    pstPhpRrbpReq            = (PHP_RRBP_FN_REQ *)pstSndMsg;
    pstPhpRrbpReq->enRptMeas = VOS_TRUE;
    pstPhpRrbpReq->enMsgID   = ID_PHP_RRBP_FN_REQ ;
    pstPhpRrbpReq->ulFN      = ulRealFN;

    (VOS_VOID)LogPrint("CBT_TrigerEdgeReportStatus: Trigger Edge Report\r\n");
    if(VOS_OK != VOS_SendMsg(UEPS_PID_GRM, pstSndMsg))
    {
        PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_ERROR, "CBT_TrigerEdgeReportStatus :VOS_SendMsg Failed");

        return VOS_ERR;
    }
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CBT_QuerySyncStatus
 功能描述  : 查询同步状态
 输入参数  : pstAppToOmMsg： 指向工具发来的数据指针
             usReturnPrimId: 返回给PC工具的PRIMID

 输出参数  : 无
 返 回 值  : VOS_OK:成功，其他为失败

*****************************************************************************/
VOS_UINT32 CBT_QuerySyncStatus(VOS_UINT16 usMode)
{
    if (CBT_DATA_UMTS == usMode)
    {
        if (OM_W_SYNC_STATUS_SYNC == g_stListmodeCtrl.usWSyncStatus)
        {
            return VOS_OK;
        }
        else
        {
            (VOS_VOID)LogPrint1("CBT_QuerySyncStatus: W sync status is %d.\r\n", g_stListmodeCtrl.usWSyncStatus);
            return VOS_ERR;
        }
    }
    else
    {
        g_stListmodeCtrl.usGeReportFlag = VOS_TRUE;

        /* GSM CS 状态下，无需下发，物理层主动上报状态 */
        if (CBT_DATA_GSM == usMode)
        {
            return VOS_OK;
        }

        if (VOS_OK != CBT_TrigerEdgeReportStatus())
        {
            (VOS_VOID)LogPrint("CBT_QuerySyncStatus: Triger Edge Report Status error.\r\n");
            return VOS_ERR;
        }

        return VOS_OK;
    }
}

/*****************************************************************************
 函 数 名  : CBT_Call
 功能描述  : 呼叫过程
 输入参数  : 无
 输出参数  : 无

  修改历史      :
  1.日    期   : 2015-05-28
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CBT_Call(VOS_UINT16 usMode)
{
    if (VOS_OK != CBT_SendListModeMsg(usMode, CBT_ACTION_CALL))
    {
        (VOS_VOID)LogPrint("CBT_Call: call fail\r\n");
        return VOS_ERR;
    }

    if (VOS_OK != CBT_QuerySyncStatus(usMode))
    {
        (VOS_VOID)LogPrint("CBT_Call: Sync Status error\r\n");
        return VOS_ERR;
    }

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : CBT_HandOver
 功能描述  : 信道切换过程
 输入参数  : 无
 输出参数  : 无

  修改历史      :
  1.日    期   : 2015-05-28
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CBT_HandOver(VOS_UINT16 usMode)
{
    if (CBT_SendListModeMsg(usMode, CBT_ACTION_HANDOVER))
    {
        (VOS_VOID)LogPrint("CBT_HandOver: handover fail\r\n");
        return VOS_ERR;
    }

    if (VOS_OK != CBT_QuerySyncStatus(usMode))
    {
        (VOS_VOID)LogPrint("CBT_HandOver: Sync Status error\r\n");
        return VOS_ERR;
    }
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CBT_Release
 功能描述  : 信道释放过程
 输入参数  : 无
 输出参数  : 无

  修改历史      :
  1.日    期   : 2015-05-28
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CBT_Release(VOS_UINT16 usMode)
{
    /*控制Release，方便定于问题*/
    if (VOS_TRUE == g_bReleaseAfterTest)
    {
        return VOS_OK;
    }

    if (CBT_DATA_UMTS == usMode)
    {
        if (VOS_OK != CBT_WcdmaIlpcCtrl(WPHY_MNTN_PWR_PARA_LIST_MODE_OPEN_ILPC, 0))
        {
            (VOS_VOID)LogPrint("CBT_ExitListmodeTest: CBT_WcdmaIlpcCtrl error\r\n");
            return VOS_ERR;
        }
    }

    return CBT_SendListModeMsg(usMode, CBT_ACTION_RELEASE);
}
/*****************************************************************************
 函 数 名  : CBT_SetPower
 功能描述  : 设置UE的目标功率
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   : 2015-05-28
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CBT_SetPower(VOS_UINT16 usMode, CBT_LIST_MODE_SEGMENT_STRU *pstSegment)
{
    if (CBT_DATA_UMTS == usMode)
    {
        /*为了保证最大功率测试准确，需要在tpc下进行。只有第一段，并且在最大功率处，才有意义，否则功率切不到期望的数值*/
        if (W_TPC_ENABLE == pstSegment->usEnableTpc)
        {
            return VOS_OK;
        }

        if (VOS_OK != CBT_WcdmaIlpcCtrl(WPHY_MNTN_PWR_PARA_LIST_MODE_SET_PWR, pstSegment->unWgPowerCtrl.sWPower10th))
        {
            (VOS_VOID)LogPrint("CBT_SetPower: CBT_WcdmaIlpcCtrl fail");
            return VOS_ERR;
        }

        /*(VOS_VOID)LogPrint1("\r\nW set power[%d] Pass\r\n", pstSegment->unWgPowerCtrl.sWPower10th);*/
        return VOS_OK;
    }
    else
    {
        /*PCL不变，不需要进行切换*/
        if (g_stListmodeCtrl.usPcl == pstSegment->unWgPowerCtrl.usGsmPcl)
        {
            (VOS_VOID)LogPrint1("\r\nGe do not need set pcl[%d]\r\n", pstSegment->unWgPowerCtrl.usGsmPcl);
            return VOS_OK;
        }

        g_stListmodeCtrl.usPcl = pstSegment->unWgPowerCtrl.usGsmPcl;

        /*(VOS_VOID)LogPrint1("\r\nGe set pcl[%d] Pass\r\n", pstSegment->unWgPowerCtrl.usGsmPcl);*/

        return CBT_HandOver(usMode);
    }
}

/*****************************************************************************
 函 数 名  : CBT_ListModeOneChan
 功能描述  : listmode测试，测试一个channel下所有segment的过程
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   : 2015-05-28
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CBT_ListModeOneChan(VOS_UINT16 usMode, CBT_LIST_MODE_CHAN_STRU *pstOneChan)
{
    VOS_UINT32                          ulSegIndex;
    VOS_UINT32                          ulSegDataAddr;
    CBT_LIST_MODE_SEGMENT_STRU         *pstOneSeg;

    ulSegDataAddr = (VOS_UINT32)pstOneChan->stSegment;

    for (ulSegIndex=1; ulSegIndex <= pstOneChan->ulSegmentCount; ulSegIndex++)
    {
        pstOneSeg = (CBT_LIST_MODE_SEGMENT_STRU *)ulSegDataAddr;

        g_stListmodeCtrl.usTxTotalFrameNum = pstOneSeg->usTxFramCnt;

        if (VOS_OK != CBT_SetPower(usMode, pstOneSeg))
        {
            return (VOS_UINT32)CBT_SETPOWER_ERROR;
        }

        /*等待本次测试帧统计结束*/
        if (VOS_OK != VOS_SmP(g_stListmodeCtrl.ulCbtTxSegmentFrameSem, OM_NOSIG_WAIT_TIME_LEN))
        {
            return (VOS_UINT32)CBT_WAITTXFRAMES_ERROR;
        }

        ulSegDataAddr += sizeof(CBT_LIST_MODE_SEGMENT_STRU);
    }
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CBT_ListModeProc
 功能描述  : 开始listmode测试
 输入参数  : pstAppToOmMsg： 指向工具发来的数据指针
             usReturnPrimId: 返回给PC工具的PRIMID

 输出参数  : 无
 返 回 值  : VOS_OK:成功，其他为失败

*****************************************************************************/
VOS_UINT32 CBT_ListModeTestProc(CBT_UNIFORM_MSG_STRU * pstPcToCbtMsg, VOS_UINT16 usReturnPrimId)
{
    VOS_UINT16                          usMode;
    VOS_UINT32                          ulChanIndex = 1;
    VOS_UINT32                          ulChanCount;
    VOS_UINT32                          ulErrorCode;
    VOS_UINT32                          ulMsgDataAddr;
    CBT_LIST_MODE_STATE_ENUM            enState = CBT_STATE_INIT;
    CBT_LIST_MODE_CHAN_STRU            *pstOneChan;
    CBT_LISTMODE_TEST_PROC_STRU        *pstLmTestProc;

    pstLmTestProc = (CBT_LISTMODE_TEST_PROC_STRU *)pstPcToCbtMsg->aucPara;

    g_ulListmodeEnable = MAIL_BOX_PROTECTWORD_SND;
    g_stListmodeCtrl.stModemSsid = pstPcToCbtMsg->stMsgHeader.stModemSsid;
    g_stListmodeCtrl.stCompMode  = pstPcToCbtMsg->stCompMode;

    g_stListmodeCtrl.usEnableReport = pstLmTestProc->usEnableReport;

    usMode = pstLmTestProc->usMode;
    g_usListModeDataMode = usMode;
    g_usListModeCurrentMode = (CBT_DATA_UMTS == usMode)? VOS_RATMODE_WCDMA : VOS_RATMODE_GSM;
    g_enListModeWorkModem = pstPcToCbtMsg->stMsgHeader.stModemSsid.ucModem;

    ulChanCount = pstLmTestProc->ulChanCount;
    ulMsgDataAddr = (VOS_UINT32)(pstLmTestProc->aucData);

    if (0 == ulChanCount)
    {
        CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, (VOS_UINT32)CBT_CHANCOUNT_ERROR);
        return VOS_ERR;
    }

    while (ulChanIndex <= ulChanCount)
    {
        pstOneChan = (CBT_LIST_MODE_CHAN_STRU *)ulMsgDataAddr;

        g_stListmodeCtrl.ulBand   = pstOneChan->ulBand;
        g_stListmodeCtrl.usTxChan = pstOneChan->usTxChan;
        g_stListmodeCtrl.usRxChan = pstOneChan->usRxChan;

        /*取当前chan的第一段pcl*/
        if (0 < pstOneChan->ulSegmentCount)
        {
            g_stListmodeCtrl.usPcl = pstOneChan->stSegment[0].unWgPowerCtrl.usGsmPcl;
        }

        switch(enState)
        {
            case CBT_STATE_INIT:
            {
                if (VOS_OK != CBT_Call(usMode))
                {
                    CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, (VOS_UINT32)CBT_CALL_ERROR);
                    return VOS_ERR;
                }

                enState = CBT_STATE_LOOPBACK;
                break;
            }
            case CBT_STATE_LOOPBACK:
            {
                /*重新开始chan的帧统计*/
                g_stListmodeCtrl.usTotalFrameNum = pstOneChan->usDurationFrameCnt;
                g_stListmodeCtrl.usReportFrameNum = pstOneChan->usReportFrameCnt;

                enState = CBT_STATE_TEST;
                break;
            }
            case CBT_STATE_HANDOVER:
            {
                /*切换到下一个信道*/
                if (VOS_OK != CBT_HandOver(usMode))
                {
                    CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, (VOS_UINT32)CBT_HANDOVER_ERROR);
                    return VOS_ERR;
                }

                /*重新开始chan的帧统计*/
                g_stListmodeCtrl.usTotalFrameNum = pstOneChan->usDurationFrameCnt;
                g_stListmodeCtrl.usReportFrameNum = pstOneChan->usReportFrameCnt;

                enState = CBT_STATE_TEST;
                break;
            }
            case CBT_STATE_TEST:
            {
                ulErrorCode = CBT_ListModeOneChan(usMode, pstOneChan);
                if (VOS_OK != ulErrorCode)
                {
                    CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, ulErrorCode);
                    return ulErrorCode;
                }

                /*等待上一个chan帧统计结束*/
                if (VOS_OK != VOS_SmP(g_stListmodeCtrl.ulCbtTotalFrameSem, OM_NOSIG_WAIT_TIME_LEN))
                {
                    CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, (VOS_UINT32)CBT_WAITTOTALFRAMES_ERROR);
                    return VOS_ERR;
                }

                /* 帧统计结束，切换到下一个频段 */
                ulChanIndex++;
                ulMsgDataAddr += sizeof(CBT_LIST_MODE_CHAN_STRU);

                enState = CBT_STATE_HANDOVER;
                break;
            }
            default:
                break;
        }
    }

    if (VOS_OK != CBT_Release(usMode))
    {
        CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, (VOS_UINT32)CBT_RELEASE_ERROR);
        return VOS_ERR;
    }

    CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, VOS_OK);
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CBT_CSyncStatusProc
 功能描述  : cdma模式下，获取信令连接状态
 输入参数  : pstAppToOmMsg： 指向工具发来的数据指针
             usReturnPrimId: 返回给PC工具的PRIMID

 输出参数  : 无
 返 回 值  : VOS_OK:成功，其他为失败

*****************************************************************************/
VOS_UINT32 CBT_CSyncStatusProc(CBT_UNIFORM_MSG_STRU * pstAppToCbtMsg, VOS_UINT16 usReturnPrimId)
{
    g_stListmodeCtrl.usCReportFlag = VOS_TRUE;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CBT_CFrameErrorRate
 功能描述  : cdma模式下，开始统计Frame error Rate
 输入参数  : pstAppToOmMsg： 指向工具发来的数据指针
             usReturnPrimId: 返回给PC工具的PRIMID

 输出参数  : 无
 返 回 值  : VOS_OK:成功，其他为失败

*****************************************************************************/
VOS_UINT32 CBT_CFrameErrorRate(CBT_UNIFORM_MSG_STRU * pstAppToCbtMsg, VOS_UINT16 usReturnPrimId)
{
    CBT_WC_BER_DATA_REQ_STRU *      pstBerConfig;

    pstBerConfig = (CBT_WC_BER_DATA_REQ_STRU *)pstAppToCbtMsg;

    g_usCBadFrames = 0;

    g_stListmodeCtrl.usTotalFrameNum = pstBerConfig->usFrameNum;
    g_stListmodeCtrl.usCurFrameNum   = 0;

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : CBT_CSetPower
 功能描述  : cdma模式下，关闭TPC，强配指定功率
 输入参数  : pstAppToOmMsg： 指向工具发来的数据指针
             usReturnPrimId: 返回给PC工具的PRIMID

 输出参数  : 无
 返 回 值  : VOS_OK:成功，其他为失败

*****************************************************************************/
VOS_UINT32 CBT_CSetPower(CBT_UNIFORM_MSG_STRU * pstAppToCbtMsg, VOS_UINT16 usReturnPrimId)
{
    CBT_C_SET_POWER_STRU               *pstRcvSetPower;
    CCBT_CPROC_1X_SET_POWER_REQ_STRU   *pMsg;

    pstRcvSetPower = (CBT_C_SET_POWER_STRU *)pstAppToCbtMsg->aucPara;

    pMsg = (CCBT_CPROC_1X_SET_POWER_REQ_STRU *)VOS_AllocMsg(CCPU_PID_CBT, sizeof(CCBT_CPROC_1X_SET_POWER_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pMsg)
    {
        CBT_SendResultChannel(pstAppToCbtMsg->stMsgHeader.stModemSsid, pstAppToCbtMsg->stCompMode, usReturnPrimId, (VOS_UINT32)VOS_ERR);
        return VOS_ERR;
    }

    pMsg->ulReceiverPid = CPROC_PID_1X_CM;
    pMsg->enMsgId       = ID_CCBT_CPROC_1X_SET_POWER_REQ;

    pMsg->usEnableTpc    = pstRcvSetPower->usEnableTpc;
    pMsg->sDedicatePower = pstRcvSetPower->sDedicatePower;

    (VOS_VOID)VOS_SendMsg(CCPU_PID_CBT, pMsg);

    return VOS_OK;
}
#endif

/*****************************************************************************
 函 数 名  : OM_BtTransProc
 功能描述  : BT非信令透明通道处理
 输入参数  : pstAppToOmMsg： 指向工具发来的数据指针
             usReturnPrimId: 返回给PC工具的PRIMID

 输出参数  : 无
 返 回 值  : VOS_OK:成功，其他为失败

*****************************************************************************/
VOS_UINT32 OM_BtTransProc(CBT_UNIFORM_MSG_STRU * pstAppToCbtMsg, VOS_UINT16 usReturnPrimId)
{
    VOS_UINT16                   usNoSigMsgCnt;
    VOS_UINT16                   usIndex;
    VOS_UINT32                   ulMsgDataAddr;
    OM_NOSIG_MSG_HEAD_STRU      *pstNoSigMsgHead;
    MsgBlock                    *pstSndMsg;

    if (MODEM_ID_BUTT <= pstAppToCbtMsg->stMsgHeader.stModemSsid.ucModem)
    {
        (VOS_VOID)LogPrint1("OM_BtTransProc: modem[%d] config error", pstAppToCbtMsg->stMsgHeader.stModemSsid.ucModem);
        return VOS_ERR;
    }
    /* 保存 stModemSsid */
    g_stListmodeCtrl.stModemSsid = pstAppToCbtMsg->stMsgHeader.stModemSsid;

    /* 保存是否使能消息上报 */
    g_stListmodeCtrl.usEnableReport = *(VOS_UINT16*)(pstAppToCbtMsg->aucPara);

    /* 非信令模式下的交互消息数 */
    usNoSigMsgCnt = *(VOS_UINT16*)(pstAppToCbtMsg->aucPara + sizeof(VOS_UINT16));

    ulMsgDataAddr =  (VOS_UINT32)(pstAppToCbtMsg->aucPara + sizeof(VOS_UINT32));

    /*lint -e534*/
    (VOS_VOID)VOS_TaskLock();
    /*lint +e534*/

    for (usIndex = 1; usIndex <= usNoSigMsgCnt; usIndex++)
    {
        pstNoSigMsgHead = (OM_NOSIG_MSG_HEAD_STRU*)ulMsgDataAddr;

        /* 假如是下发消息则调用VOS接口发送出去 */
        if (VOS_FALSE == pstNoSigMsgHead->usNsMsgType)
        {
            pstSndMsg = VOS_AllocMsg(WUEPS_PID_NOSIG, pstNoSigMsgHead->usNsMsgLen - VOS_MSG_HEAD_LENGTH);

            if (VOS_NULL_PTR == pstSndMsg)
            {
                /*lint -e534*/
                VOS_TaskUnlock();
                /*lint +e534*/

                return VOS_ERR;
            }

            /*lint -e534*/
            VOS_MemCpy(pstSndMsg, &(pstNoSigMsgHead->usRcvMsgPrimId), pstNoSigMsgHead->usNsMsgLen);
            /*lint +e534*/

            (VOS_VOID)VOS_SendMsg(pstSndMsg->ulSenderPid, pstSndMsg);

            /* 前4个字节为消息类型和消息长度字段 */
            ulMsgDataAddr += (sizeof(VOS_UINT32) + pstNoSigMsgHead->usNsMsgLen);
        }
        /* 否则为等待消息 */
        else
        {
            g_stListmodeCtrl.usRecvPrimId = pstNoSigMsgHead->usRcvMsgPrimId;

            /*lint -e534*/
            VOS_TaskUnlock();
            /*lint +e534*/

            if (VOS_OK != VOS_SmP(g_stListmodeCtrl.ulCbtSyncSem, OM_NOSIG_WAIT_TIME_LEN))
            {
                CBT_SendResultChannel(g_stListmodeCtrl.stModemSsid, g_stListmodeCtrl.stCompMode, usReturnPrimId, usIndex);

                return VOS_ERR;
            }
            /*lint -e534*/
            (VOS_VOID)VOS_TaskLock();
            /*lint +e534*/
            ulMsgDataAddr += sizeof(OM_NOSIG_MSG_HEAD_STRU);
        }
    }

    /*lint -e534*/
    VOS_TaskUnlock();
    /*lint +e534*/
    CBT_SendResultChannel(g_stListmodeCtrl.stModemSsid, g_stListmodeCtrl.stCompMode, usReturnPrimId, VOS_OK);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : OM_WSyncStatusProc
 功能描述  : 查询W下同步失步状态
 输入参数  : pstAppToOmMsg： 指向工具发来的数据指针
             usReturnPrimId: 返回给PC工具的PRIMID

 输出参数  : 无
 返 回 值  : VOS_OK:成功，其他为失败

*****************************************************************************/
VOS_UINT32 OM_WSyncStatusProc(CBT_UNIFORM_MSG_STRU * pstAppToCbtMsg, VOS_UINT16 usReturnPrimId)
{
    /*把同步状态发送给PC工具*/
    CBT_SendResultChannel(g_stListmodeCtrl.stModemSsid, g_stListmodeCtrl.stCompMode, usReturnPrimId, (VOS_UINT32)g_stListmodeCtrl.usWSyncStatus);/* g_stOmNoSigCtrl.usSyncStatus */

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : OM_EdgeBlerProc
 功能描述  : 查询BLER
 输入参数  : pstAppToOmMsg： 指向工具发来的数据指针
             usReturnPrimId: 返回给PC工具的PRIMID

 输出参数  : 无
 返 回 值  : VOS_OK:成功，其他为失败

*****************************************************************************/

VOS_UINT32 OM_EdgeBlerProc (CBT_UNIFORM_MSG_STRU * pstAppToCbtMsg, VOS_UINT16 usReturnPrimId)
{
    CBT_EDGE_BLER_STRU               stOmEdgeBlerData;
    MODEM_ID_ENUM_UINT16             enModemID;

    enModemID = pstAppToCbtMsg->stMsgHeader.stModemSsid.ucModem;

    if(MODEM_ID_BUTT <= enModemID)
    {
        PS_LOG(CCPU_PID_CBT, 0, PS_PRINT_ERROR, "OM_EdgeBlerProc : Modem ID Error!");
        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy(&stOmEdgeBlerData.stMsgHeader, &pstAppToCbtMsg->stMsgHeader, sizeof(CBT_MSG_HEADER_LENGTH));
    /*lint +e534*/
    stOmEdgeBlerData.usPrimId   = pstAppToCbtMsg->usMsgId;
    stOmEdgeBlerData.stCompMode = pstAppToCbtMsg->stCompMode;

    stOmEdgeBlerData.ulFirstErrNum    = HPA_Read32Reg(g_aulGUCBBPRegAddr[BLER_ERR][enModemID][VOS_RATMODE_GSM]);
    stOmEdgeBlerData.ulFirstTotalNum  = HPA_Read32Reg(g_aulGUCBBPRegAddr[BLER_TOTAL][enModemID][VOS_RATMODE_GSM]);

    if( VOS_OK != VOS_TaskDelay(OM_EDGE_BLER_TASK_DELAY))
    {
        PS_LOG(CCPU_PID_CBT, 0, PS_PRINT_ERROR, "OM_EdgeBlerProc : Task Delay Fail!");
        return VOS_ERR;
    }

    stOmEdgeBlerData.ulSecondErrNum   = HPA_Read32Reg(g_aulGUCBBPRegAddr[BLER_ERR][enModemID][VOS_RATMODE_GSM]);
    stOmEdgeBlerData.ulSecondTotalNum = HPA_Read32Reg(g_aulGUCBBPRegAddr[BLER_TOTAL][enModemID][VOS_RATMODE_GSM]);
    stOmEdgeBlerData.ulMsgLength      = (VOS_UINT32)(sizeof(CBT_EDGE_BLER_STRU)- CBT_MSG_HEAD_EX_LENGTH);

    CBT_SendContentChannel(g_stListmodeCtrl.stModemSsid, g_stListmodeCtrl.stCompMode, usReturnPrimId, (CBT_UNIFORM_MSG_STRU *)(&stOmEdgeBlerData));

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  :   OM_GeDlStatusProc
 功能描述  : 获得GSM/EDGE下的BER结果
 输入参数  : pstAppToOmMsg： 指向工具发来的数据指针
             usReturnPrimId: 返回给PC工具的PRIMID

 输出参数  : 无
 返 回 值  : VOS_OK:成功，其他为失败

*****************************************************************************/
VOS_UINT32  OM_GeDlStatusProc (CBT_UNIFORM_MSG_STRU * pstAppToCbtMsg, VOS_UINT16 usReturnPrimId)
{
    VOS_UINT32                          ulPreFN;
    VOS_UINT32                          ulCurrentFN;
    VOS_UINT32                          ulRealFN;
    MODEM_ID_ENUM_UINT16                enModemID;

    PHP_RRBP_FN_REQ                    *pstPhpRrbpReq;
    MsgBlock                           *pstSndMsg;
    CBT_GE_DL_STATUS_REQ_STRU          *pstOmGeDlStatReq;

    pstOmGeDlStatReq = (CBT_GE_DL_STATUS_REQ_STRU *)pstAppToCbtMsg;

    enModemID = (MODEM_ID_ENUM_UINT16)pstAppToCbtMsg->stMsgHeader.stModemSsid.ucModem;

    if(MODEM_ID_BUTT <= enModemID)
    {
        PS_LOG(CCPU_PID_CBT, 0, PS_PRINT_ERROR, "OM_GeDlStatusProc :Modem ID Error!");

        return VOS_ERR;
    }

    /* 物理层消息是否上报标记 */
    /*g_ulReportFlag = VOS_TRUE;*/
    g_stListmodeCtrl.usGeReportFlag = VOS_TRUE;

    /* GSM CS 状态下，无需下发，物理层主动上报状态 */
    if (VOS_TRUE == pstOmGeDlStatReq->usModeType)
    {
        return VOS_OK;
    }

    pstSndMsg = VOS_AllocMsg(UEPS_PID_GRM, sizeof(PHP_RRBP_FN_REQ) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSndMsg)
    {
        PS_LOG(CCPU_PID_CBT, 0, PS_PRINT_ERROR, "OM_GeDlStatusProc :DIAG_DataProc Alloc Msg Failed!");

        return VOS_ERR;
    }

    if(MODEM_ID_1 == enModemID)
    {
        pstSndMsg->ulSenderPid      = I1_UEPS_PID_GRM;
        pstSndMsg->ulReceiverPid    = I1_DSP_PID_GPHY;   /*发送给卡1的PID*/
    }
    else
    {
        pstSndMsg->ulSenderPid      = I0_UEPS_PID_GRM;
        pstSndMsg->ulReceiverPid    = I0_DSP_PID_GPHY;   /*发送给卡0的PID*/
    }
    /*通过读取寄存器获得当前帧数*/
    ulPreFN  = HPA_Read32Reg(g_aulGUCBBPRegAddr[GTC_FN][enModemID][VOS_RATMODE_GSM]);

    /*当前帧数由两部分组成，高16位*1326 + 低16位寄存器值*/
    ulCurrentFN  = ((ulPreFN >> 16)& OM_FRAME_NUM_REG_MASKBIT)* OM_HIHG_ADDR_FRAME_NUM;
    ulCurrentFN  += (ulPreFN & OM_FRAME_NUM_REG_MASKBIT);

    /*实际帧数为当前帧数加上下发消息时间估计值*/
    ulRealFN     = (ulCurrentFN + OM_DL_MSG_FRAME_NUM ) % OM_FRAME_MAX_NUM;

    pstPhpRrbpReq            = (PHP_RRBP_FN_REQ*)pstSndMsg;
    pstPhpRrbpReq->enRptMeas = VOS_TRUE;
    pstPhpRrbpReq->enMsgID   = ID_PHP_RRBP_FN_REQ ;
    pstPhpRrbpReq->ulFN      = ulRealFN;

    if(VOS_OK != VOS_SendMsg(UEPS_PID_GRM, pstSndMsg))
    {
        PS_LOG(CCPU_PID_CBT, 0, PS_PRINT_ERROR, "OM_GeDlStatusProc :VOS_SendMsg Failed");

        return VOS_ERR;
    }
    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : OM_BerConfigProc
 功能描述  : 配置BER上报次数
 输入参数  : pstAppToOmMsg： 指向工具发来的数据指针
             usReturnPrimId: 返回给PC工具的PRIMID

 输出参数  : 无
 返 回 值  : VOS_OK:成功，其他为失败

*****************************************************************************/
VOS_UINT32 OM_BerConfigProc(CBT_UNIFORM_MSG_STRU * pstAppToCbtMsg, VOS_UINT16 usReturnPrimId)
{
    CBT_WC_BER_DATA_REQ_STRU *      pstBerConfig;

    pstBerConfig = (CBT_WC_BER_DATA_REQ_STRU *)pstAppToCbtMsg;

    CBT_SendResultChannel(g_stListmodeCtrl.stModemSsid, g_stListmodeCtrl.stCompMode, usReturnPrimId, VOS_OK);

    /*lint -e534*/
    (VOS_VOID)VOS_TaskLock();
    /*lint +e534*/

    g_stListmodeCtrl.usTotalFrameNum = pstBerConfig->usFrameNum;
    g_stListmodeCtrl.usCurFrameNum   = 0;

    /*lint -e534*/
    VOS_TaskUnlock();
    /*lint +e534*/

    return VOS_OK;
}

/*****************************************************************************
 Prototype       : OM_NoSigMsgProc
 Description     :
 Input           : pMsg - 指向消息地址
 Output          : None
 Return Value    : VOS_VOID

 History         : ---
    Date         : 2011-07-01
    Author       : g47350
    Modification : Created function
 *****************************************************************************/
/*lint -e550*/
/*lint -e830*/
VOS_VOID OM_NoSigMsgProc(MsgBlock *pMsg)
{
    CBT_UNIFORM_MSG_STRU   *pstAppToOmMsg;
    VOS_UINT16              usReturnPrimId;
    VOS_UINT32              ulTotalNum;
    VOS_UINT32              ulIndex;

    if (CCPU_PID_CBT == pMsg->ulSenderPid)
    {
        pstAppToOmMsg = (CBT_UNIFORM_MSG_STRU *)pMsg->aucValue;

        ulTotalNum = sizeof(g_astOmNoSigProcTbl)/sizeof(CBT_MSG_FUN_STRU);

        /* 根据PrimId查找对应的处理函数 */
        for (ulIndex = 0; ulIndex < ulTotalNum; ulIndex++)
        {
            if (pstAppToOmMsg->usMsgId == g_astOmNoSigProcTbl[ulIndex].ulPrimId)
            {
                usReturnPrimId = (VOS_UINT16)(g_astOmNoSigProcTbl[ulIndex].ulReturnPrimId);

                (VOS_VOID)(g_astOmNoSigProcTbl[ulIndex].pfCbtFun(pstAppToOmMsg, usReturnPrimId));

                break;
            }
        }

        if (ulIndex == ulTotalNum)
        {
            PS_LOG2(CCPU_PID_CBT, 0, PS_PRINT_INFO, "OM_NoSigMsgProc: Result :%d, PrimId : %d can't be Found\n",
                    (VOS_INT32)VOS_ERR, (VOS_INT32)pstAppToOmMsg->usMsgId);
        }

    }

    return;
}
/*lint +e550*/
/*lint +e830*/

/*****************************************************************************
 函 数 名  : OM_R99Mailbox_ResetMutexFlag
 功能描述  : 重新设置Mailbox 互斥标识
 输入参数  : ulMailboxBufIndex-R99 Mailbox 索引
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011-10-09
    作    者   : w00184431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID OM_R99MailboxResetMutexFlag(VOS_UINT32  ulMailboxBufIndex)
{

    VOS_UINT32 ulVtbDataFlag;
    VOS_UINT32  aulR99MailboxVtbAddr[3];
    aulR99MailboxVtbAddr[0] = WTTFPHY_MAC_R99MAILBOX_VTB_ADDR_ZERO;
    aulR99MailboxVtbAddr[1] = WTTFPHY_MAC_R99MAILBOX_VTB_ADDR_FIRST;
    aulR99MailboxVtbAddr[2] = WTTFPHY_MAC_R99MAILBOX_VTB_ADDR_SECOND;

    ulVtbDataFlag = HPA_Read16Reg(aulR99MailboxVtbAddr[ulMailboxBufIndex]);

    /* 清除VTB和TURBO的数据指示标志 */
    if ( OM_R99_MAILBOX_MUTEX_DATA_EXIST == ulVtbDataFlag)
    {
        HPA_Write16Reg(aulR99MailboxVtbAddr[ulMailboxBufIndex],
                            OM_R99_MAILBOX_MUTEX_DATA_NOT_EXIST);
    }

    /* 清除所读取译码邮箱的读写互斥标记 */
    if (OM_R99_DECODE_BUF_INDEX_FIRST == ulMailboxBufIndex)
    {
        HPA_Write32Reg(WTTFPHY_MAC_DATA_IND_FIRST_MUTEX_ADDR,
                            OM_R99_MAILBOX_MUTEX_DATA_NOT_EXIST);
    }
    else if (OM_R99_DECODE_BUF_INDEX_SECOND == ulMailboxBufIndex)
    {
        HPA_Write32Reg(WTTFPHY_MAC_DATA_IND_SECOND_MUTEX_ADDR,
                            OM_R99_MAILBOX_MUTEX_DATA_NOT_EXIST);
    }
    else
    {

    }

    return;
}

/*****************************************************************************
 函 数 名  : OM_GetR99MailboxIndex
 功能描述  : 把译码数据邮箱分成0、1两组，每组都包含VITERBI和TURBO译码数据，
              DSP每次收到译码中断,会先看0号BUFF是否可读，如可读，则获取BUFF index
              否则，再看1号BUFF是否可读，如可读，则获取BUFF index ;
              如两块BUFF均不可读，则返回0。
              同一邮箱中VTB数据的序号与Turbo数据的序号一样, 所以取任1个即可。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 0:无Buf可读;1,2存在相应的Buf Index可读
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   :
    作    者   :
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 OM_GetR99MailboxIndex(VOS_VOID)
{

    VOS_UINT32 ulVtbDataFlag;
    VOS_UINT32 ulFirstSerialNum     = 0;
    VOS_UINT32 ulSecondSerialNum    = 0;

    /* 该变量既为表示邮箱1或2存在的掩码，又做邮箱地址数组下标 */
    VOS_UINT32 ulMailboxIndex       = 0;

    VOS_UINT32 ulFirstMailboxMuteFlag;   /* 保存译码邮箱1读写互斥标记 */
    VOS_UINT32 ulSecondMailboxMuteFlag;  /* 保存译码邮箱2读写互斥标记 */

    /* 获取VTB和TURBO BUFFER的数据指示标志 */
    ulFirstMailboxMuteFlag  = HPA_Read32Reg(WTTFPHY_MAC_DATA_IND_FIRST_MUTEX_ADDR);
    ulSecondMailboxMuteFlag = HPA_Read32Reg(WTTFPHY_MAC_DATA_IND_SECOND_MUTEX_ADDR);

    /* 根据数据BUFFER的互斥标志，置ulMailDataInd */
    if (OM_R99_MAILBOX_MUTEX_DATA_EXIST == ulFirstMailboxMuteFlag)
    {
        ulMailboxIndex |= OM_R99_DECODE_BUF_INDEX_FIRST;
    }
    if (OM_R99_MAILBOX_MUTEX_DATA_EXIST == ulSecondMailboxMuteFlag)
    {
        ulMailboxIndex |= OM_R99_DECODE_BUF_INDEX_SECOND;
    }

    /* 根据数据是否存在的掩码值，判断读取哪个邮箱的数据(用ulMailDataInd存放邮箱地址数组下标) */

    /* 如果只有1个邮箱有数据，则不改变ulMailDataInd，用其做数组下标，取邮箱地址 */

    /* 如果两个邮箱都有数据， */
    if ((OM_R99_DECODE_BUF_INDEX_FIRST|OM_R99_DECODE_BUF_INDEX_SECOND) == ulMailboxIndex)
    {
        /* 两个邮箱中都有数据的情况 */

        /* 同一邮箱中VTB数据的序号与Turbo数据的序号一样, 所以取任1个即可 */
        ulVtbDataFlag = HPA_Read16Reg(WTTFPHY_MAC_R99MAILBOX_VTB_ADDR_FIRST);

        if (OM_R99_MAILBOX_MUTEX_DATA_EXIST == ulVtbDataFlag)
        {
            /*lint -e413*/
            ulFirstSerialNum = HPA_Read32Reg(WTTFPHY_MAC_DATA_IND_FIRST_VTB_ADDR
                                  + OM_OFFSET_OF(WTTFPHY_MAC_DATA_IND_CTRL_PARAM_STRU, ulSerialNum));
        }
        else
        {
            ulFirstSerialNum = HPA_Read32Reg(WTTFPHY_MAC_DATA_IND_FIRST_TURBO_ADDR
                                   + OM_OFFSET_OF(WTTFPHY_MAC_DATA_IND_CTRL_PARAM_STRU, ulSerialNum));
        }

        ulVtbDataFlag = HPA_Read16Reg(WTTFPHY_MAC_R99MAILBOX_VTB_ADDR_SECOND);

        if (OM_R99_MAILBOX_MUTEX_DATA_EXIST == ulVtbDataFlag)
        {
            ulSecondSerialNum = HPA_Read32Reg(WTTFPHY_MAC_DATA_IND_SECOND_VTB_ADDR
                                          + OM_OFFSET_OF(WTTFPHY_MAC_DATA_IND_CTRL_PARAM_STRU, ulSerialNum));
        }
        else
        {
            ulSecondSerialNum = HPA_Read32Reg(WTTFPHY_MAC_DATA_IND_SECOND_TURBO_ADDR + OM_OFFSET_OF(WTTFPHY_MAC_DATA_IND_CTRL_PARAM_STRU, ulSerialNum));
            /*lint +e413*/
        }

        /* 比较两个邮箱中的数据序号，读数据序号小的邮箱 */
        if (ulFirstSerialNum < ulSecondSerialNum)
        {
            ulMailboxIndex = OM_R99_DECODE_BUF_INDEX_FIRST;
        }
        else
        {
            ulMailboxIndex = OM_R99_DECODE_BUF_INDEX_SECOND;
        }
    }

    return ulMailboxIndex;
}

/*****************************************************************************
 函 数 名  : HPA_R99Mailbox_Read
 功能描述  : 将 R99 Mailbox 数据读入到指定缓存
 输入参数  :  pucDataIndBuf,-保存邮箱数据指针
              ulMailboxBufIndex-邮箱索引
              pucDataIndBuf：保存邮箱数据指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011-10-09
    作    者   : w00184431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 OM_R99MailboxRead(VOS_UINT8 *pucDataIndBuf,
                                        VOS_UINT16 *pusDataLen,
                                        VOS_UINT32  ulMailboxBufIndex)
{
    VOS_UINT32                          ulMailboxBufAddr;
    VOS_UINT32                          ulVtbDataFlag;
    VOS_UINT16                          usVtbDataLen = 0;
    VOS_UINT32                          aulR99MailboxVtbAddr[3];

    aulR99MailboxVtbAddr[0] = WTTFPHY_MAC_R99MAILBOX_VTB_ADDR_ZERO;
    aulR99MailboxVtbAddr[1] = WTTFPHY_MAC_R99MAILBOX_VTB_ADDR_FIRST;
    aulR99MailboxVtbAddr[2] = WTTFPHY_MAC_R99MAILBOX_VTB_ADDR_SECOND;

    ulVtbDataFlag = HPA_Read16Reg(aulR99MailboxVtbAddr[ulMailboxBufIndex]);

    /* 信令等低速信道一般为VTB编码, 信令优先 ,如果VTB数据RAM有数据，判断数据长度的有效性*/
    if (OM_R99_MAILBOX_MUTEX_DATA_EXIST == ulVtbDataFlag)
    {
        ulMailboxBufAddr    = (aulR99MailboxVtbAddr[ulMailboxBufIndex]);

        usVtbDataLen        = HPA_Read16Reg(ulMailboxBufAddr + sizeof(VOS_UINT16));

        if (((usVtbDataLen*4) <= WTTFPHY_MAX_PHY_DATA_IND_VTB_DATA_LEN) && (usVtbDataLen > 0))
        {
            HPA_GetDspMem((VOS_CHAR *)ulMailboxBufAddr, (VOS_CHAR *)pucDataIndBuf,
                                    WTTFPHY_MAX_PHY_DATA_IND_VTB_HEAD_LEN+(usVtbDataLen*4));

            *pusDataLen = (VOS_UINT16)(usVtbDataLen*4);

            return VOS_TRUE;
        }
    }

    return  VOS_FALSE;
}
/*****************************************************************************
 函 数 名  : CBT_WcdmaReportFrames
 功能描述  : 读取wcdma ber数据，并上报
 输入参数  : 无
 输出参数  : 无

  修改历史      :
  1.日    期   : 2015-05-28
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CBT_WcdmaReportFrames()
{
    VOS_UINT32                              ulMailboxBufIndex;
    VOS_UINT32                              ulResult;
    VOS_UINT16                              usDataLen;
    WTTFPHY_PHY_DATA_REQ_BUF_STRU          *pstMacPhyDataReqBuf;
    WTTFPHY_MAC_DATA_IND_CTRL_PARAM_STRU   *pstPhyDataIndHead;
    /*lint -e813 */
    CBT_LIST_MODE_BER_IND_STRU              stBerDataInd;
    /*lint +e813 */

    /*译码邮箱有两组, 首先获取译码邮箱索引*/
    ulMailboxBufIndex = OM_GetR99MailboxIndex();

    if ( OM_R99_DECODE_BUF_INDEX_INIT == ulMailboxBufIndex )
    {
       return ;
    }

    ulResult = OM_R99MailboxRead(g_aucOmR99MBData, &usDataLen, ulMailboxBufIndex);

    if (VOS_TRUE == ulResult)
    {
        /*下行控制参数写入上行信道共享缓存中*/
        pstMacPhyDataReqBuf = (WTTFPHY_PHY_DATA_REQ_BUF_STRU *)(WTTFPHY_MAC_PHY_DATA_REQ_ADDR);

        pstPhyDataIndHead = (WTTFPHY_MAC_DATA_IND_CTRL_PARAM_STRU *)&g_aucOmR99MBData[0];

        pstMacPhyDataReqBuf->enMutexFlag = WTTFPHY_MUTEX_DATA_EXIST;
        pstMacPhyDataReqBuf->enCctrchID  = WTTFPHY_UL_DPCH;
        pstMacPhyDataReqBuf->enMsgName   = ID_MAC_PHY_DATA_REQ;
        pstMacPhyDataReqBuf->usUlTrchCnt = OM_UL_TRANS_CHANNEL_NUM ;

        /*上行信道CFN为当前CFN+1*/
        pstMacPhyDataReqBuf->usCFN = (g_ucHpaCfnRead + 1);

        /*Tfi取值[1,32],传输信道标识*/
        pstMacPhyDataReqBuf->astUlTrchDataInfo[0].usTfi = pstPhyDataIndHead->astDlTrchDataInfo[0].ucTfi;
        /* TrchId取值[0,63],传输格式标识，这里固定为1 */
        pstMacPhyDataReqBuf->astUlTrchDataInfo[0].usTrchId = g_ausTrchId[0];


        pstMacPhyDataReqBuf->astUlTrchDataInfo[1].usTfi = pstPhyDataIndHead->astDlTrchDataInfo[1].ucTfi ;
        pstMacPhyDataReqBuf->astUlTrchDataInfo[1].usTrchId = g_ausTrchId[1];

        pstMacPhyDataReqBuf->ulSerialNum = g_ulOmSerialNum;
        g_ulOmSerialNum++;

        pstMacPhyDataReqBuf->usDataLen = usDataLen;

        /*lint -e534*/
        VOS_MemSet(&stBerDataInd, 0, sizeof(stBerDataInd));
        /*lint +e534*/

        /*将消息上报给TOOL*/
        stBerDataInd.usTotalFrameNum = (VOS_UINT16)g_stListmodeCtrl.usReportFrameNum;
        stBerDataInd.usCurFrameNum   = (VOS_UINT16)g_stListmodeCtrl.usCurReportFrameNum;
        stBerDataInd.usBand          = (VOS_UINT16)g_stListmodeCtrl.ulBand;
        stBerDataInd.usRxChan        = g_stListmodeCtrl.usRxChan;
        stBerDataInd.usCrcData       = (VOS_UINT16)(pstPhyDataIndHead->astDlTrchDataInfo[0].ulCrcBitMap & 0x01);
        stBerDataInd.usRsv           = 0x00;

        g_stListmodeCtrl.usCurReportFrameNum++;

        if (OM_BER_DATA_MAX_SIZE < usDataLen)
        {
            stBerDataInd.ulDataLen = OM_BER_DATA_MAX_SIZE;

            /*lint -e534*/
            LogPrint1("CBT_WcdmaReportFrames: BER data is too large %d.\r\n", usDataLen);
            /*lint +e534*/
        }
        else
        {
            stBerDataInd.ulDataLen = (VOS_UINT32)usDataLen;
        }

        /*lint -e534*/
        VOS_MemCpy(stBerDataInd.aucData, g_aucOmR99MBData + WTTFPHY_MAX_PHY_DATA_IND_VTB_HEAD_LEN, stBerDataInd.ulDataLen);
        /*lint +e534*/

        stBerDataInd.ulMsgLength = sizeof(stBerDataInd) - CBT_MSG_HEAD_EX_LENGTH;
        CBT_SendContentChannel(g_stListmodeCtrl.stModemSsid, g_stListmodeCtrl.stCompMode, OM_APP_LISTMODE_BT_BER_IND, (CBT_UNIFORM_MSG_STRU *)&stBerDataInd);


        HPA_PutDspMem((VOS_CHAR*)&g_aucOmR99MBData[WTTFPHY_MAX_PHY_DATA_IND_VTB_HEAD_LEN],
                                      (VOS_CHAR*)pstMacPhyDataReqBuf->aucData, usDataLen);

    }

    OM_R99MailboxResetMutexFlag(ulMailboxBufIndex);

    return;
}
/*****************************************************************************
 函 数 名  : CBT_TotalFrameStatic
 功能描述  : 帧中断函数，用于listmode测试统计total帧数。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   : 2015-06-08
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CBT_TotalFrameStatics()
{
    if (g_stListmodeCtrl.usCurFrameNum + 1 < g_stListmodeCtrl.usTotalFrameNum)
    {
        if (g_stListmodeCtrl.usCurReportFrameNum < g_stListmodeCtrl.usReportFrameNum)
        {
            if (CBT_DATA_UMTS == g_usListModeDataMode)
            {
                /* usCurReportFrameNum 在有译码数据的情况下递增 */
                CBT_WcdmaReportFrames();
            }
            else
            {
            }
        }
        g_stListmodeCtrl.usCurFrameNum++;
/*
        (VOS_VOID)LogPrint3("CBT_TotalFrameStatics: Total: %d, Current: %d, Report: %d\r\n", g_stListmodeCtrl.usTotalFrameNum, \
                                    g_stListmodeCtrl.usCurFrameNum, g_stListmodeCtrl.usCurReportFrameNum);
*/
    }
    /*帧中断统计到达期望的帧数*/
    else if (0 != g_stListmodeCtrl.usTotalFrameNum)
    {
        g_stListmodeCtrl.usCurFrameNum = 0;
        g_stListmodeCtrl.usTotalFrameNum = 0;

        g_stListmodeCtrl.usCurReportFrameNum = 0;
        g_stListmodeCtrl.usReportFrameNum = 0;

        /*(VOS_VOID)LogPrint("CBT_TotalFrameStatics: (Total Acheived)\r\n");*/
        /*lint -e534*/
        VOS_SmV(g_stListmodeCtrl.ulCbtTotalFrameSem);
        /*lint +e534*/
    }
    else
    {
    }
}
/*****************************************************************************
 函 数 名  : CBT_TxFrameStatics
 功能描述  : 帧中断函数，用于listmode测试统计Tx segment帧数。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   : 2015-06-08
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CBT_TxFrameStatics()
{
    /*统计tx segment 帧数*/
    /*第一个帧中断上来之前，tx power还没有设置好，所以第一个帧必然丢弃了*/
    if (g_stListmodeCtrl.usTxCurFrameNum < g_stListmodeCtrl.usTxTotalFrameNum)
    {
        /*(VOS_VOID)LogPrint2("CBT_TxFrameStatics: Tx Total: %d, Current Tx Frame: %d\r\n", \
                                g_stListmodeCtrl.usTxTotalFrameNum, g_stListmodeCtrl.usTxCurFrameNum);*/

        /*tx第一个帧开始设置功率*/
        /*if (0 == g_stListmodeCtrl.usTxCurFrameNum)
        {
            if (VOS_OK != CBT_SetPower(g_usListModeDataMode, g_stOneSegmentCtrl->unWgPowerCtrl))
            {
                (VOS_VOID)LogPrint("CBT_TxFrameStatics: CBT Set Power fail ...\r\n");
            }
        }*/

        g_stListmodeCtrl.usTxCurFrameNum++;

    }
    else if (0 != g_stListmodeCtrl.usTxTotalFrameNum)
    {
        g_stListmodeCtrl.usTxCurFrameNum = 0;
        g_stListmodeCtrl.usTxTotalFrameNum = 0;

        /*(VOS_VOID)LogPrint("CBT_TxFrameStatics: (Tx Acheived)\r\n");*/

        (VOS_VOID)VOS_SmV(g_stListmodeCtrl.ulCbtTxSegmentFrameSem);
    }
    else
    {
    }
}
/*****************************************************************************
 函 数 名  : CBT_FramesStatistics
 功能描述  : 帧中断函数，用于listmode测试统计帧数。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   : 2015-05-28
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CBT_FramesStatistics(VOS_VOID)
{
    CBT_TotalFrameStatics();
    CBT_TxFrameStatics();
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : CBT_CLoopTestProc
 功能描述  : 通过此接口模拟CTTF实现数据LoopBack功能。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   : 2015-08-06
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CBT_CLoopTestProc(VOS_VOID)
{
    /*下行译码数据结构*/
    VOS_UINT16                          usDataLen;
    VOS_UINT_PTR                        ptrAddr;
    CTTF_CSDR_1X_ADDR_INFO_STRU        *pst1xAddrInfo;
    CSDR_CTTF_1X_F_CTRL_MGMT_STRU      *pstFCtrlMgmt;
    CSDR_CTTF_1X_GENERIC_DATA_IND_STRU *pstFchGenricData;
    CSDR_CTTF_1X_F_DATA_INFO_STRU      *pstCsdrData;
    CSDR_CTTF_1X_F_DATA_BLK_STRU       *pstDataBlock;
    CSDR_CTTF_1X_F_BUFFER_CTRL_STRU    *pstFBufferCtrl;
    CSDR_CTTF_1X_F_GENERIC_BUFF_CTRL_STRU *pstFGenericBuffCtrl;

    /*上行数据结构*/
    CTTF_CSDR_1X_R_CTRL_MGMT_STRU      *pstRCtrlMgmt = VOS_NULL_PTR;
    CTTF_CSDR_1X_FCH_DATA_REQ_STRU     *pst1xFchData = VOS_NULL_PTR;

    if(MAIL_BOX_PROTECTWORD_FST == g_ulCttfCsdr1xRequireAddr)
    {
        /*说明还没有收到CSDR提供的基地址，不作处理，返回*/
        return;
    }

    if(VOS_NULL == g_ulCttfCsdr1xRequireAddr)
    {
        /*说明收到CSDR提供的DDR基地址不合法，发起主动复位*/
        /*lint -e534*/
        LogPrint("CBT_CLoopTestProc:Waring: CSDR DDR BASE ADDR Invalid!\r\n");
        /*lint +e534*/

        VOS_ProtectionReboot(CBT_CSDR_DDR_BASE_ADDR_INVALID, THIS_FILE_ID, __LINE__, VOS_NULL_PTR, 0);

        return;
    }

    ptrAddr = HPA_Read32Reg(g_ulCttfCsdr1xRequireAddr);

    if(MAIL_BOX_PROTECTWORD_SND == ptrAddr)
    {
        /*说明CSDR提供的DTCM地址不合法，发起主动复位*/
        /*lint -e534*/
        LogPrint("CBT_CLoopTestProc:Waring: CSDR DTCM BASE ADDR Invalid!\r\n");
        /*lint +e534*/

        VOS_ProtectionReboot(CBT_CSDR_DTCM_BASE_ADDR_INVALID, THIS_FILE_ID, __LINE__, VOS_NULL_PTR, 0);

        return;
    }

    pst1xAddrInfo = (CTTF_CSDR_1X_ADDR_INFO_STRU *)ptrAddr;

    /*it's not allowed MAC to read addresses, until magic number turns to ready*/
    if (CTTF_CSDR_1X_ADDR_MAGIC_READY != pst1xAddrInfo->ulMagicNum)
    {
        /*(VOS_VOID)LogPrint1("Magic num: 0x%x \r\n", pst1xAddrInfo->ulMagicNum);*/
        return;
    }

     /*X No signal just consider FCH*/
    pstFBufferCtrl = (CSDR_CTTF_1X_F_BUFFER_CTRL_STRU *)pst1xAddrInfo->ulFBuffCtrlAddr;
    pstFGenericBuffCtrl = &(pstFBufferCtrl->stFchBuffCtrl);

    /* ring buffer is empty */
    if (pstFGenericBuffCtrl->usHeadIdx == pstFGenericBuffCtrl->usTailIdx)
    {
        return;
    }

    pstFCtrlMgmt = (CSDR_CTTF_1X_F_CTRL_MGMT_STRU *)pst1xAddrInfo->ulFCtrlMgmtAddr;
    pstFchGenricData = &(pstFCtrlMgmt->stFchDataInd);

    if (CSDR_1X_MAX_BLK_NUM_PER_RING_BUFFER <= pstFGenericBuffCtrl->usTailIdx)
    {
        (VOS_VOID)LogPrint1("TailIndex error: %d \r\n", pstFGenericBuffCtrl->usTailIdx);
        pstFGenericBuffCtrl->usTailIdx = pstFGenericBuffCtrl->usHeadIdx;
        return;
    }

    pstCsdrData = &(pstFchGenricData->ast1xDataInfo[pstFGenericBuffCtrl->usTailIdx]);

    if (0 == pstCsdrData->usReceivedInd)
    {
        return;
    }

    pstDataBlock = &(pstCsdrData->stDataBlock);
    usDataLen = CBT_BIT2BYTE_BOTTOM(pstDataBlock->usNumBit);

    /*处理上行的控制数据*/
    pstRCtrlMgmt = (CTTF_CSDR_1X_R_CTRL_MGMT_STRU *)pst1xAddrInfo->ulRCtrlMgmtAddr;
    pst1xFchData = &(pstRCtrlMgmt->st1xFchData);

    pst1xFchData->enMutexFlag       = CSDR_1X_MUTEX_DATA_EXISTED;
    pst1xFchData->enFrameDuration   = CSDR_1X_FRAME_DURATION_20MS;
    pst1xFchData->usBlkBitSize      = pstDataBlock->usNumBit;
    pst1xFchData->usSignalOnChannel = 0;
    pst1xFchData->ulTimeStamp       = 0;

    /*172 BitNum*/
    pst1xFchData->stPcAdjGain.sGain            = 0;
    pst1xFchData->stPcAdjGain.asPilotRefLvl[0] = 0;
    pst1xFchData->stPcAdjGain.asPilotRefLvl[1] = 0;

    /* 将下行译码数据拷贝到上行编码地址处 */
    (VOS_VOID)VOS_MemCpy((VOS_UINT8 *)pst1xFchData->ulDataAddr, (VOS_UINT8 *)pstDataBlock->ulDataAddr, usDataLen);

    pstCsdrData->usReceivedInd = 0;
    /* 数据取用后，将索引前移*/
    pstFGenericBuffCtrl->usTailIdx = CBT_MOD_ADD(pstFGenericBuffCtrl->usTailIdx, 1, CSDR_1X_MAX_BLK_NUM_PER_RING_BUFFER);

    return;
}
#endif

/*****************************************************************************
 函 数 名  : HPA_LoopTestProc
 功能描述  : 通过此接口实现信道环回，读取译码数据并配置WDSP数据。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   : 2011-10-09
    作    者   : w00184431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID OM_LoopTestProc(VOS_VOID)
{
    VOS_UINT32                              ulMailboxBufIndex;
    VOS_UINT32                              ulResult;
    VOS_UINT16                              usDataLen;
    WTTFPHY_PHY_DATA_REQ_BUF_STRU           *pstMacPhyDataReqBuf;
    WTTFPHY_MAC_DATA_IND_CTRL_PARAM_STRU    *pstPhyDataIndHead;
    /*lint -e813 修改人:dongtinghuan;检视人:徐铖 51137 */
    CBT_W_BER_DATA_IND_STRU                 stBerDataInd;
    /*lint +e813 修改人:dongtinghuan;检视人:徐铖 51137 */

    if (MAIL_BOX_PROTECTWORD_SND != g_ulOmNosigEnable)
    {
        return;
    }

    /*译码邮箱有两组, 首先获取译码邮箱索引*/
    ulMailboxBufIndex = OM_GetR99MailboxIndex();

    if ( OM_R99_DECODE_BUF_INDEX_INIT == ulMailboxBufIndex )
    {
       return ;
    }

    ulResult = OM_R99MailboxRead(g_aucOmR99MBData, &usDataLen, ulMailboxBufIndex);

    if (VOS_TRUE == ulResult)
    {
        /*下行控制参数写入上行信道共享缓存中*/
        pstMacPhyDataReqBuf = (WTTFPHY_PHY_DATA_REQ_BUF_STRU *)(WTTFPHY_MAC_PHY_DATA_REQ_ADDR);

        pstPhyDataIndHead = (WTTFPHY_MAC_DATA_IND_CTRL_PARAM_STRU *)&g_aucOmR99MBData[0];

        pstMacPhyDataReqBuf->enMutexFlag = WTTFPHY_MUTEX_DATA_EXIST;
        pstMacPhyDataReqBuf->enCctrchID  = WTTFPHY_UL_DPCH;
        pstMacPhyDataReqBuf->enMsgName   = ID_MAC_PHY_DATA_REQ;
        pstMacPhyDataReqBuf->usUlTrchCnt = OM_UL_TRANS_CHANNEL_NUM ;

        /*上行信道CFN为当前CFN+1*/
        pstMacPhyDataReqBuf->usCFN = (g_ucHpaCfnRead + 1);

        /*Tfi取值[1,32],传输信道标识*/
        pstMacPhyDataReqBuf->astUlTrchDataInfo[0].usTfi = pstPhyDataIndHead->astDlTrchDataInfo[0].ucTfi;
        /* TrchId取值[0,63],传输格式标识，这里固定为1 */
        pstMacPhyDataReqBuf->astUlTrchDataInfo[0].usTrchId = g_ausTrchId[0];


        pstMacPhyDataReqBuf->astUlTrchDataInfo[1].usTfi = pstPhyDataIndHead->astDlTrchDataInfo[1].ucTfi ;
        pstMacPhyDataReqBuf->astUlTrchDataInfo[1].usTrchId = g_ausTrchId[1];

        pstMacPhyDataReqBuf->ulSerialNum = g_ulOmSerialNum;
        g_ulOmSerialNum++;

        pstMacPhyDataReqBuf->usDataLen = usDataLen;

        if (g_stListmodeCtrl.usCurFrameNum < g_stListmodeCtrl.usTotalFrameNum)
        {
            stBerDataInd.usTotalFrameNum = (VOS_UINT16)g_stListmodeCtrl.usTotalFrameNum;
            stBerDataInd.usCurFrameNum   = (VOS_UINT16)g_stListmodeCtrl.usCurFrameNum;
            g_stListmodeCtrl.usCurFrameNum++;

            if (OM_BER_DATA_MAX_SIZE < (usDataLen + WTTFPHY_MAX_PHY_DATA_IND_VTB_HEAD_LEN))
            {
                stBerDataInd.ulDataLen = OM_BER_DATA_MAX_SIZE;

                /*lint -e534*/
                LogPrint1("OM_LoopTestProc: BER data is too large %d.\r\n", usDataLen);
                /*lint +e534*/
            }
            else
            {
                stBerDataInd.ulDataLen = (VOS_UINT32)usDataLen + WTTFPHY_MAX_PHY_DATA_IND_VTB_HEAD_LEN;
            }

            /*lint -e534*/
            VOS_MemCpy(stBerDataInd.aucData, g_aucOmR99MBData, stBerDataInd.ulDataLen);
            /*lint +e534*/

            stBerDataInd.ulMsgLength = sizeof(stBerDataInd) - CBT_MSG_HEAD_EX_LENGTH;
            CBT_SendContentChannel(g_stListmodeCtrl.stModemSsid, g_stListmodeCtrl.stCompMode, OM_APP_W_BER_DATA_IND, (CBT_UNIFORM_MSG_STRU *)&stBerDataInd);
        }

        HPA_PutDspMem((VOS_CHAR*)&g_aucOmR99MBData[WTTFPHY_MAX_PHY_DATA_IND_VTB_HEAD_LEN],
                                      (VOS_CHAR*)pstMacPhyDataReqBuf->aucData, usDataLen);

    }

    OM_R99MailboxResetMutexFlag(ulMailboxBufIndex);

    return;
}

/*****************************************************************************
 函 数 名  : OM_NoSigCtrlInit
 功能描述  : 非信令控制结构初全局变量始化
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOID
*****************************************************************************/
VOS_VOID OM_NoSigCtrlInit(VOS_VOID)
{
    CBT_MODEM_SSID_STRU     stInitModemSsid;
    CBT_COMPONENT_MODE_STRU stInitCompMode;

    stInitModemSsid.ucModem = 0;
    stInitModemSsid.ucResv  = 0;
    stInitModemSsid.ucSsid  = CBT_SSID_MODEM_CPU;

    stInitCompMode.ucCompID = CBT_COMP_NOSIG;
    stInitCompMode.ucMode   = 0;
    stInitCompMode.ucRsv    = 0;

    g_stOmNoSigCtrl.usEnableReport = VOS_FALSE;
    g_stOmNoSigCtrl.usRcvMsgPrimId = 0;
    g_stOmNoSigCtrl.stModemSsid    = stInitModemSsid;
    g_stOmNoSigCtrl.stCompMode     = stInitCompMode;
    g_stOmNoSigCtrl.usSyncStatus   = OM_W_SYNC_STATUS_UNKNOWN;
    g_stOmNoSigCtrl.ulTotalFrameNum= 0;
    g_stOmNoSigCtrl.ulCurFrameNum  = 0;
}

/*****************************************************************************
 函 数 名  : CBT_ListModeCtrlInit
 功能描述  : Listmode控制结构全局变量始化
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOID
*****************************************************************************/
VOS_VOID CBT_ListModeCtrlInit(VOS_VOID)
{
    CBT_MODEM_SSID_STRU     stInitModemSsid;
    CBT_COMPONENT_MODE_STRU stInitCompMode;

    stInitModemSsid.ucModem = 0;
    stInitModemSsid.ucResv  = 0;
    stInitModemSsid.ucSsid  = CBT_SSID_MODEM_CPU;

    stInitCompMode.ucCompID = CBT_COMP_NOSIG;
    stInitCompMode.ucMode   = 0;
    stInitCompMode.ucRsv    = 0;

    g_stListmodeCtrl.stModemSsid    = stInitModemSsid;
    g_stListmodeCtrl.stCompMode     = stInitCompMode;

    g_stListmodeCtrl.usWSyncStatus  = OM_W_SYNC_STATUS_UNKNOWN;
    g_stListmodeCtrl.usCSyncStatus  = CBT_C_SYNC_STATUS_UNKNOWN;

    g_stListmodeCtrl.usCReportFlag  = VOS_FALSE;
    g_stListmodeCtrl.usGeReportFlag = VOS_FALSE;

    g_stListmodeCtrl.usEnableReport = VOS_FALSE;
    g_stListmodeCtrl.usRecvPrimId  = 0;

    g_stListmodeCtrl.usCurFrameNum = 0;
    g_stListmodeCtrl.usTotalFrameNum = 0;

    g_stListmodeCtrl.usCurReportFrameNum = 0;
    g_stListmodeCtrl.usReportFrameNum = 0;

    g_stListmodeCtrl.usTxTotalFrameNum = 0;
    g_stListmodeCtrl.usTxCurFrameNum = 0;
}
/*****************************************************************************
 Prototype       : Om_NoSigPidInit
 Description     : OM NoSig Pid' initializtion function
 Input           : None
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2008-03-20
    Author       : g47350
    Modification : Created function
 *****************************************************************************/
VOS_UINT32 OM_NoSigPidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    if (VOS_IP_LOAD_CONFIG == ip)
    {
        /* 分配互斥信号量 */
        if (VOS_OK != VOS_SmBCreate( "NOSIG", 0, VOS_SEMA4_FIFO, &(g_stOmNoSigCtrl.ulNoSigSyncSem)))
        {
            (VOS_VOID)LogPrint("Sem NOSIG create fail");
            return VOS_ERR;
        }

        if (VOS_OK != VOS_SmBCreate( "LMSyn", 0, VOS_SEMA4_FIFO, &(g_stListmodeCtrl.ulCbtSyncSem)))
        {
            (VOS_VOID)LogPrint("Sem LMSyn create fail");
            return VOS_ERR;
        }

        if (VOS_OK != VOS_SmCCreate( "LMRxF", 0, VOS_SEMA4_FIFO, &(g_stListmodeCtrl.ulCbtTotalFrameSem)))
        {
            (VOS_VOID)LogPrint("Sem LMRxF create fail");
            return VOS_ERR;
        }

        if (VOS_OK != VOS_SmCCreate( "LMTxF", 0, VOS_SEMA4_FIFO, &(g_stListmodeCtrl.ulCbtTxSegmentFrameSem)))
        {
            (VOS_VOID)LogPrint("Sem LMTxF create fail");
            return VOS_ERR;
        }

        if (VOS_OK != VOS_SmBCreate( "LMDlQ", 0, VOS_SEMA4_FIFO, &(g_stListmodeCtrl.ulCbtGeDlQualitySem)))
        {
            (VOS_VOID)LogPrint("Sem LM Ge Dl Quality create fail");
            return VOS_ERR;
        }
        /* 初始化非信令控制结构 */
        OM_NoSigCtrlInit();
        /* 初始化listmode控制结构 */
        CBT_ListModeCtrlInit();
    }

    return VOS_OK;
}

/*****************************************************************************
 Prototype       : OM_NoSigFidInit
 Description     : OM NoSig Fid' initializtion function
 Input           : None
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2008-03-20
    Author       : g47350
    Modification : Created function
 *****************************************************************************/
VOS_UINT32 OM_NoSigFidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32 ulRslt;

    if (VOS_IP_LOAD_CONFIG == ip)
    {
        ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_NOSIG,
                                    (Init_Fun_Type)OM_NoSigPidInit,
                                    (Msg_Fun_Type)OM_NoSigMsgProc);
        if( VOS_OK != ulRslt )
        {
            return VOS_ERR;
        }

        ulRslt = VOS_RegisterTaskPrio(WUEPS_FID_NOSIG, COMM_NOSIG_TASK_PRIO);

        if( VOS_OK != ulRslt )
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

