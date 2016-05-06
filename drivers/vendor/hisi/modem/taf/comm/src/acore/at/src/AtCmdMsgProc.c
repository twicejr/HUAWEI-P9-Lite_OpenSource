

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "ATCmdProc.h"
#include "siapppb.h"
#include "siappstk.h"
#include "AtMsgPrint.h"
#include "mdrv.h"
#include "AtPhyInterface.h"
#include "PppInterface.h"
#include "AtDataProc.h"
#include "AtCmdMsgProc.h"
#include "TafDrvAgent.h"
#include "AtCmdMsgProc.h"
#include "AtEventReport.h"
#include "AtRabmInterface.h" /* V3R2和V7R1共用 z40661 c00149739 20111221 */
#include "AtRnicInterface.h"
#include "AtDeviceCmd.h"
#include "AtInit.h"
#include "at_common.h"
#include "AcpuReset.h"

#include "AtInternalMsg.h"

#if (FEATURE_ON==FEATURE_LTE)
#include "msp_nvim.h"

#include "LPsNvInterface.h"
#include "LNvCommon.h"
#include "at_lte_common.h"
#endif

#include "OmApi.h"
/* Added by l00167671 for NV拆分项目 , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV拆分项目 , 2013-05-17, end*/
#include "GasNvInterface.h"
/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-08-16, begin */
#include "AppVcApi.h"
/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-08-16, end */

#include "AtCmdImsProc.h"

#include  "product_config.h"

#include "AtCmdCallProc.h"

#include  "AtCmdFtmProc.h"

#include "AtCmdMiscProc.h"

#include "AtCmdCagpsProc.h"
#include "AtCmdCssProc.h"


#include "mdrv.h"
#include "TafAppCall.h"
#include "AtEventReport.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 -e960 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_CMDMSGPROC_C
/*lint +e767 +e960 修改人:罗建 107747;检视人:sunshaohua*/


/*****************************************************************************
  2 类型定义
*****************************************************************************/

/*****************************************************************************
   3 全局变量定义
*****************************************************************************/
#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA)&&(FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)&&(FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT))

EXTERN VOS_UINT8    gucCurrEncVoiceDataWriteFileNum;
EXTERN TAF_CHAR    *g_pacCurrEncVoiceDataWriteFilePath[];
#endif

/* Added by L60609 for AT Project，2011-10-04,  Begin*/

/*AT 模块处理来自AT AGENT消息函数对应表*/
const AT_PROC_MSG_FROM_DRV_AGENT_STRU g_astAtProcMsgFromDrvAgentTab[]=
{
    /* 消息ID */                            /* 消息处理函数 */
    {DRV_AGENT_MSID_QRY_CNF,                AT_RcvDrvAgentMsidQryCnf},
    {DRV_AGENT_GAS_MNTN_CMD_RSP,            AT_RcvDrvAgentGasMntnCmdRsp},
    {DRV_AGENT_HARDWARE_QRY_RSP,            AT_RcvDrvAgentHardwareQryRsp},
    {DRV_AGENT_FULL_HARDWARE_QRY_RSP,       AT_RcvDrvAgentFullHardwareQryRsp},
    {DRV_AGENT_RXDIV_SET_CNF,               AT_RcvDrvAgentSetRxdivCnf},
    {DRV_AGENT_RXDIV_QRY_CNF,               AT_RcvDrvAgentQryRxdivCnf},
    {DRV_AGENT_SIMLOCK_SET_CNF,             AT_RcvDrvAgentSetSimlockCnf},


    {DRV_AGENT_VERTIME_QRY_CNF,             AT_RcvDrvAgentVertimeQryRsp},
    {DRV_AGENT_YJCX_SET_CNF,                AT_RcvDrvAgentYjcxSetCnf},
    {DRV_AGENT_YJCX_QRY_CNF,                AT_RcvDrvAgentYjcxQryCnf},
    {DRV_AGENT_GPIOPL_SET_CNF,              AT_RcvDrvAgentSetGpioplRsp},
    {DRV_AGENT_GPIOPL_QRY_CNF,              AT_RcvDrvAgentQryGpioplRsp},
    {DRV_AGENT_DATALOCK_SET_CNF,            AT_RcvDrvAgentSetDatalockRsp},
    {DRV_AGENT_TBATVOLT_QRY_CNF,            AT_RcvDrvAgentQryTbatvoltRsp},
    {DRV_AGENT_VERSION_QRY_CNF,             AT_RcvDrvAgentQryVersionRsp},
    {DRV_AGENT_FCHAN_SET_CNF,               AT_RcvDrvAgentSetFchanRsp},
    {DRV_AGENT_SFEATURE_QRY_CNF,            AT_RcvDrvAgentQrySfeatureRsp},
    {DRV_AGENT_PRODTYPE_QRY_CNF,            AT_RcvDrvAgentQryProdtypeRsp},

    /* Added by 傅映君/f62575 for CPULOAD&MFREELOCKSIZE处理过程移至C核, 2011/11/15, begin */
    {DRV_AGENT_CPULOAD_QRY_CNF,             AT_RcvDrvAgentCpuloadQryRsp},
    {DRV_AGENT_MFREELOCKSIZE_QRY_CNF,       AT_RcvDrvAgentMfreelocksizeQryRsp},
    /* Added by 傅映君/f62575 for CPULOAD&MFREELOCKSIZE处理过程移至C核, 2011/11/15, end */
    /* Added by l00171473 for 内存监控AT命令, 2011-11-29,  begin */
    {DRV_AGENT_MEMINFO_QRY_CNF,             AT_RcvDrvAgentMemInfoQryRsp},
    /* Added by l00171473 for 内存监控AT命令, 2011-11-29,  end */
    {DRV_AGENT_DLOADINFO_QRY_CNF,           AT_RcvDrvAgentDloadInfoQryRsp},
    {DRV_AGENT_FLASHINFO_QRY_CNF,           AT_RcvDrvAgentFlashInfoQryRsp},
    {DRV_AGENT_AUTHORITYVER_QRY_CNF,        AT_RcvDrvAgentAuthorityVerQryRsp},
    {DRV_AGENT_AUTHORITYID_QRY_CNF,         AT_RcvDrvAgentAuthorityIdQryRsp},
    {DRV_AGENT_AUTHVER_QRY_CNF,             AT_RcvDrvAgentAuthVerQryRsp},
    {DRV_AGENT_GODLOAD_SET_CNF,             AT_RcvDrvAgentGodloadSetRsp},

    {DRV_AGENT_PFVER_QRY_CNF,               AT_RcvDrvAgentPfverQryRsp},
    {DRV_AGENT_HWNATQRY_QRY_CNF,            AT_RcvDrvAgentHwnatQryRsp},
    {DRV_AGENT_SDLOAD_SET_CNF,              AT_RcvDrvAgentSdloadSetRsp},
    {DRV_AGENT_APPDMVER_QRY_CNF,            AT_RcvDrvAgentAppdmverQryRsp},
    {DRV_AGENT_DLOADVER_QRY_CNF,            AT_RcvDrvAgentDloadverQryRsp},

    {DRV_AGENT_IMSICHG_QRY_CNF,             AT_RcvDrvAgentImsiChgQryRsp},
    {DRV_AGENT_INFORBU_SET_CNF,             AT_RcvDrvAgentInfoRbuSetRsp},
    /*DTS2012041102190 : h00135900 start in 2011-04-11 AT代码融合*/
#if ( FEATURE_ON == FEATURE_LTE )
    {DRV_AGENT_INFORRS_SET_CNF,             AT_RcvDrvAgentInfoRrsSetRsp},
#endif
    /*DTS2012041102190 : h00135900 end in 2011-04-11 AT代码融合*/
    {DRV_AGENT_CPNN_QRY_CNF,                AT_RcvDrvAgentCpnnQryRsp},
    {DRV_AGENT_CPNN_TEST_CNF,               AT_RcvDrvAgentCpnnTestRsp},
    {DRV_AGENT_NVBACKUP_SET_CNF,            AT_RcvDrvAgentNvBackupSetRsp},

    {DRV_AGENT_NVRESTORE_SET_CNF,           AT_RcvDrvAgentSetNvRestoreCnf},
    {DRV_AGENT_NVRSTSTTS_QRY_CNF,           AT_RcvDrvAgentQryNvRestoreRstCnf},
    {DRV_AGENT_NVRESTORE_MANU_DEFAULT_CNF,  AT_RcvDrvAgentNvRestoreManuDefaultRsp},

    {DRV_AGENT_ADC_SET_CNF,                 AT_RcvDrvAgentSetAdcRsp},
    {DRV_AGENT_TSELRF_SET_CNF,              AT_RcvDrvAgentTseLrfSetRsp},
    {DRV_AGENT_HKADC_GET_CNF,               AT_RcvDrvAgentHkAdcGetRsp},

    {DRV_AGENT_TBAT_QRY_CNF,                AT_RcvDrvAgentQryTbatRsp},
#if (FEATURE_ON == FEATURE_SECURITY_SHELL)
    {DRV_AGENT_SPWORD_SET_CNF,              AT_RcvDrvAgentSetSpwordRsp},
#endif

    {DRV_AGENT_NVBACKUPSTAT_QRY_CNF,        AT_RcvDrvAgentNvBackupStatQryRsp},
    {DRV_AGENT_NANDBBC_QRY_CNF,             AT_RcvDrvAgentNandBadBlockQryRsp},
    {DRV_AGENT_NANDVER_QRY_CNF,             AT_RcvDrvAgentNandDevInfoQryRsp},
    {DRV_AGENT_CHIPTEMP_QRY_CNF,            AT_RcvDrvAgentChipTempQryRsp},

    {DRV_AGENT_ANTSTATE_QRY_IND,            AT_RcvDrvAgentAntStateIndRsp},

    {DRV_AGENT_MAX_LOCK_TIMES_SET_CNF,      AT_RcvDrvAgentSetMaxLockTmsRsp},

    {DRV_AGENT_AP_SIMST_SET_CNF,            AT_RcvDrvAgentSetApSimstRsp},

    {DRV_AGENT_HUK_SET_CNF,                 AT_RcvDrvAgentHukSetCnf},
    {DRV_AGENT_FACAUTHPUBKEY_SET_CNF,       AT_RcvDrvAgentFacAuthPubkeySetCnf},
    {DRV_AGENT_IDENTIFYSTART_SET_CNF,       AT_RcvDrvAgentIdentifyStartSetCnf},
    {DRV_AGENT_IDENTIFYEND_SET_CNF,         AT_RcvDrvAgentIdentifyEndSetCnf},
    {DRV_AGENT_SIMLOCKDATAWRITE_SET_CNF,    AT_RcvDrvAgentSimlockDataWriteSetCnf},
    {DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF,    AT_RcvDrvAgentPhoneSimlockInfoQryCnf},
    {DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF,     AT_RcvDrvAgentSimlockDataReadQryCnf},
    {DRV_AGENT_PHONEPHYNUM_SET_CNF,         AT_RcvDrvAgentPhonePhynumSetCnf},
    {DRV_AGENT_PHONEPHYNUM_QRY_CNF,         AT_RcvDrvAgentPhonePhynumQryCnf},
    {DRV_AGENT_PORTCTRLTMP_SET_CNF,         AT_RcvDrvAgentPortctrlTmpSetCnf},
    {DRV_AGENT_PORTATTRIBSET_SET_CNF,       AT_RcvDrvAgentPortAttribSetCnf},
    {DRV_AGENT_PORTATTRIBSET_QRY_CNF,       AT_RcvDrvAgentPortAttribSetQryCnf},
    {DRV_AGENT_OPWORD_SET_CNF,              AT_RcvDrvAgentOpwordSetCnf},

    {DRV_AGENT_SWVER_SET_CNF,               AT_RcvDrvAgentSwverSetCnf},

#if (FEATURE_ON == FEATURE_VSIM)
    {DRV_AGENT_HVPDH_CNF,                   AT_RcvDrvAgentHvpdhSetCnf},
#endif

    /* Added by d00212987 for BalongV9R1 NV备份数据丢失容错&恢复 项目 2013-10-24, begin */
    {DRV_AGENT_NVMANUFACTUREEXT_SET_CNF,    AT_RcvNvManufactureExtSetCnf},
    /* Added by d00212987 for BalongV9R1 NV备份数据丢失容错&恢复 项目 2013-10-24, end */

    {DRV_AGENT_ANTSWITCH_SET_CNF,           AT_RcvDrvAgentAntSwitchSetCnf},
    {DRV_AGENT_ANTSWITCH_QRY_CNF,           AT_RcvDrvAgentAntSwitchQryCnf},
};

/* Added by L60609 for AT Project，2011-10-04,  End*/

/* AT模块处理来自MTA消息函数对应表*/
const AT_PROC_MSG_FROM_MTA_STRU g_astAtProcMsgFromMtaTab[]=
{
    /* 消息ID */                            /* 消息处理函数 */
    {ID_MTA_AT_CPOS_SET_CNF,                AT_RcvMtaCposSetCnf},
    {ID_MTA_AT_CPOSR_IND,                   AT_RcvMtaCposrInd},
    {ID_MTA_AT_XCPOSRRPT_IND,               AT_RcvMtaXcposrRptInd},
    {ID_MTA_AT_CGPSCLOCK_SET_CNF,           AT_RcvMtaCgpsClockSetCnf},

    {ID_MTA_AT_APSEC_SET_CNF,               AT_RcvMtaApSecSetCnf},

    {ID_MTA_AT_SIMLOCKUNLOCK_SET_CNF,       AT_RcvMtaSimlockUnlockSetCnf},

    {ID_MTA_AT_QRY_NMR_CNF,                 AT_RcvMtaQryNmrCnf},

    {ID_MTA_AT_WRR_AUTOTEST_QRY_CNF,        AT_RcvMtaWrrAutotestQryCnf},
    {ID_MTA_AT_WRR_CELLINFO_QRY_CNF,        AT_RcvMtaWrrCellinfoQryCnf},
    {ID_MTA_AT_WRR_MEANRPT_QRY_CNF,         AT_RcvMtaWrrMeanrptQryCnf},
    {ID_MTA_AT_WRR_FREQLOCK_SET_CNF,        AT_RcvMtaWrrFreqLockSetCnf},
    {ID_MTA_AT_WRR_RRC_VERSION_SET_CNF,     AT_RcvMtaWrrRrcVersionSetCnf},
    {ID_MTA_AT_WRR_CELLSRH_SET_CNF,         AT_RcvMtaWrrCellSrhSetCnf},
    {ID_MTA_AT_WRR_FREQLOCK_QRY_CNF,        AT_RcvMtaWrrFreqLockQryCnf},
    {ID_MTA_AT_WRR_RRC_VERSION_QRY_CNF,     AT_RcvMtaWrrRrcVersionQryCnf},
    {ID_MTA_AT_WRR_CELLSRH_QRY_CNF,         AT_RcvMtaWrrCellSrhQryCnf},

    {ID_MTA_AT_BODY_SAR_SET_CNF,           AT_RcvMtaBodySarSetCnf},

    /* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
    {ID_MTA_AT_CURC_QRY_CNF,                AT_RcvMtaQryCurcCnf},
    {ID_MTA_AT_UNSOLICITED_RPT_SET_CNF,     AT_RcvMtaSetUnsolicitedRptCnf},
    {ID_MTA_AT_UNSOLICITED_RPT_QRY_CNF,     AT_RcvMtaQryUnsolicitedRptCnf},
    /* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-1, end */

    {ID_MTA_AT_IMEI_VERIFY_QRY_CNF,         AT_RcvMtaImeiVerifyQryCnf},
    {ID_MTA_AT_CGSN_QRY_CNF,                AT_RcvMtaCgsnQryCnf},
    {ID_MTA_AT_NCELL_MONITOR_SET_CNF,       AT_RcvMtaSetNCellMonitorCnf},
    {ID_MTA_AT_NCELL_MONITOR_QRY_CNF,       AT_RcvMtaQryNCellMonitorCnf},
    {ID_MTA_AT_NCELL_MONITOR_IND,           AT_RcvMtaNCellMonitorInd},

    {ID_MTA_AT_REFCLKFREQ_SET_CNF,          AT_RcvMtaRefclkfreqSetCnf},
    {ID_MTA_AT_REFCLKFREQ_QRY_CNF,          AT_RcvMtaRefclkfreqQryCnf},
    {ID_MTA_AT_REFCLKFREQ_IND,              AT_RcvMtaRefclkfreqInd},

    {ID_MTA_AT_RFICSSIRD_QRY_CNF,           AT_RcvMtaRficSsiRdQryCnf},

    {ID_MTA_AT_HANDLEDECT_SET_CNF,          AT_RcvMtaHandleDectSetCnf},
    {ID_MTA_AT_HANDLEDECT_QRY_CNF,          AT_RcvMtaHandleDectQryCnf},

    {ID_MTA_AT_PS_TRANSFER_IND,             AT_RcvMtaPsTransferInd},

#if (FEATURE_ON == FEATURE_DSDS)
    {ID_MTA_AT_RRC_PROTECT_PS_CNF,          AT_RcvMtaPsProtectSetCnf},
#endif
    { ID_MTA_AT_PHY_INIT_CNF,               AT_RcvMtaPhyInitCnf},

    /* Added by l00198894 for 新增+ECID命令, 2013-12-09, begin */
    {ID_MTA_AT_ECID_SET_CNF,                AT_RcvMtaEcidSetCnf},
    /* Added by l00198894 for 新增+ECID命令, 2013-12-09, end */

    {ID_MTA_AT_MIPICLK_QRY_CNF,             AT_RcvMtaMipiInfoCnf},
    {ID_MTA_AT_MIPICLK_INFO_IND,            AT_RcvMtaMipiInfoInd},
    {ID_MTA_AT_SET_DPDTTEST_FLAG_CNF,       AT_RcvMtaSetDpdtTestFlagCnf},
    {ID_MTA_AT_SET_DPDT_VALUE_CNF,          AT_RcvMtaSetDpdtValueCnf},
    {ID_MTA_AT_QRY_DPDT_VALUE_CNF,          AT_RcvMtaQryDpdtValueCnf},

    {ID_MTA_AT_SET_JAM_DETECT_CNF,          AT_RcvMtaSetJamDetectCnf},
    {ID_MTA_AT_JAM_DETECT_IND,              AT_RcvMtaJamDetectInd},

    {ID_MTA_AT_SET_FREQ_LOCK_CNF,           AT_RcvMtaSetRatFreqLockCnf},

    {ID_MTA_AT_SET_GSM_FREQLOCK_CNF,        AT_RcvMtaSetGFreqLockCnf},
    {ID_MTA_AT_XPASS_INFO_IND,              AT_RcvMtaXpassInfoInd},

    {ID_AT_MTA_SET_FEMCTRL_CNF,             AT_RcvMtaSetFemctrlCnf},

    {ID_MTA_AT_NVWRSECCTRL_SET_CNF,         AT_RcvMtaNvwrSecCtrlSetCnf},

#if(FEATURE_ON == FEATURE_LTE)
#if(FEATURE_ON == FEATURE_LTE_MBMS)
    {ID_MTA_AT_MBMS_SERVICE_OPTION_SET_CNF,     AT_RcvMtaMBMSServiceOptSetCnf},
    {ID_MTA_AT_MBMS_SERVICE_STATE_SET_CNF,      AT_RcvMtaMBMSServiceStateSetCnf},
    {ID_MTA_AT_MBMS_PREFERENCE_SET_CNF,         AT_RcvMtaMBMSPreferenceSetCnf},
    {ID_MTA_AT_SIB16_NETWORK_TIME_QRY_CNF,      AT_RcvMtaMBMSSib16NetworkTimeQryCnf},
    {ID_MTA_AT_BSSI_SIGNAL_LEVEL_QRY_CNF,       AT_RcvMtaMBMSBssiSignalLevelQryCnf},
    {ID_MTA_AT_NETWORK_INFO_QRY_CNF,            AT_RcvMtaMBMSNetworkInfoQryCnf},
    {ID_MTA_AT_EMBMS_STATUS_QRY_CNF,            AT_RcvMtaMBMSModemStatusQryCnf},
    {ID_MTA_AT_MBMS_UNSOLICITED_CFG_SET_CNF,    AT_RcvMtaMBMSEVSetCnf},
    {ID_MTA_AT_MBMS_SERVICE_EVENT_IND,          AT_RcvMtaMBMSServiceEventInd},
    {ID_MTA_AT_INTEREST_LIST_SET_CNF,           AT_RcvMtaMBMSInterestListSetCnf},
    {ID_MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF,   AT_RcvMtaMBMSCmdQryCnf},
#endif
    {ID_MTA_AT_LTE_LOW_POWER_SET_CNF,           AT_RcvMtaLteLowPowerSetCnf},
    {ID_MTA_AT_LTE_WIFI_COEX_SET_CNF,           AT_RcvMtaIsmCoexSetCnf},
    {ID_MTA_AT_LTE_WIFI_COEX_QRY_CNF,           AT_RcvMtaIsmCoexQryCnf},
#endif

    {ID_MTA_AT_SET_FR_CNF,                  AT_RcvMtaSetFrCnf},

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    {ID_MTA_AT_MEID_SET_CNF,                AT_RcvMtaMeidSetCnf},
    {ID_MTA_AT_MEID_QRY_CNF,                AT_RcvMtaMeidQryCnf},
#endif
    {ID_MTA_AT_TRANSMODE_QRY_CNF,           AT_RcvMtaTransModeQryCnf},

    {ID_MTA_AT_UE_CENTER_SET_CNF,           AT_RcvMtaUECenterSetCnf},
    {ID_MTA_AT_UE_CENTER_QRY_CNF,           AT_RcvMtaUECenterQryCnf},
    {ID_MTA_AT_SET_NETMON_SCELL_CNF,        AT_RcvMtaSetNetMonSCellCnf},
    {ID_MTA_AT_SET_NETMON_NCELL_CNF,        AT_RcvMtaSetNetMonNCellCnf},

    {ID_MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF, AT_RcvMtaAfcClkInfoCnf},

};

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))
const AT_PROC_MSG_FROM_XPDS_STRU g_astAtProcMsgFromXpdsTab[]=
{
    {ID_XPDS_AT_GPS_START_CNF,                    AT_RcvXpdsCagpsRlstCnf},
    {ID_XPDS_AT_GPS_CFG_MPC_ADDR_CNF,             AT_RcvXpdsCagpsRlstCnf},
    {ID_XPDS_AT_GPS_CFG_PDE_ADDR_CNF,             AT_RcvXpdsCagpsRlstCnf},
    {ID_XPDS_AT_GPS_CFG_MODE_CNF,                 AT_RcvXpdsCagpsRlstCnf},
    {ID_XPDS_AT_GPS_STOP_CNF,                     AT_RcvXpdsCagpsRlstCnf},

    {ID_XPDS_AT_GPS_TIME_INFO_IND,                AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_REFLOC_INFO_CNF,              AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_PDE_POSI_INFO_IND,            AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_NI_SESSION_IND,               AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_START_REQ,                    AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_CANCEL_IND,                   AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_ACQ_ASSIST_DATA_IND,          AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_ABORT_IND,                    AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_DEL_ASSIST_DATA_IND,          AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_ION_INFO_IND,                 AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_EPH_INFO_IND,                 AT_RcvXpdsEphInfoInd},
    {ID_XPDS_AT_GPS_ALM_INFO_IND,                 AT_RcvXpdsAlmInfoInd},
    {ID_XPDS_AT_GPS_NI_CP_STOP,                   AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_NI_CP_START,                  AT_RcvXpdsCagpsCnf},

    {ID_XPDS_AT_AP_DATA_CALL_REQ,                 AT_RcvXpdsAgpsDataCallReq},
    {ID_XPDS_AT_AP_SERVER_BIND_REQ,               AT_RcvXpdsAgpsServerBindReq},
    {ID_XPDS_AT_AP_REVERSE_DATA_IND,              AT_RcvXpdsAgpsReverseDataInd},

    {ID_XPDS_AT_GPS_UTS_TEST_START_REQ,           AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_UTS_TEST_STOP_REQ,            AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_UTS_GPS_POS_INFO_IND,             AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_OM_TEST_START_REQ,            AT_RcvXpdsCagpsCnf},
    {ID_XPDS_AT_GPS_OM_TEST_STOP_REQ,             AT_RcvXpdsCagpsCnf},
};
#endif

const AT_PROC_MSG_FROM_CALL_STRU g_astAtProcMsgFromCallTab[]=
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    {ID_TAF_CALL_APP_ENCRYPT_VOICE_CNF,                     AT_RcvXcallEncryptCallCnf},
    {ID_TAF_CALL_APP_ENCRYPT_VOICE_IND,                     AT_RcvXcallEncryptCallInd},
    {ID_TAF_CALL_APP_EC_REMOTE_CTRL_IND,                    AT_RcvXcallEccRemoteCtrlInd},
    {ID_TAF_CALL_APP_REMOTE_CTRL_ANSWER_CNF,                AT_RcvXcallRemoteCtrlAnsCnf},
    {ID_TAF_CALL_APP_ECC_SRV_CAP_CFG_CNF,                   AT_RcvXcallEccCapSetCnf},
    {ID_TAF_CALL_APP_ECC_SRV_CAP_QRY_CNF,                   AT_RcvXcallEccCapQryCnf},
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)
    {ID_TAF_CALL_APP_SET_EC_TEST_MODE_CNF,                  AT_RcvXcallSetEccTestModeCnf},
    {ID_TAF_CALL_APP_GET_EC_TEST_MODE_CNF,                  AT_RcvXcallQryEccTestModeCnf},
    {ID_TAF_CALL_APP_GET_EC_RANDOM_CNF,                     AT_RcvXcallQryEccRandomCnf},
    {ID_TAF_CALL_APP_GET_EC_KMC_CNF,                        AT_RcvXcallQryEccKmcCnf},
    {ID_TAF_CALL_APP_SET_EC_KMC_CNF,                        AT_RcvXcallSetEccKmcCnf},
    {ID_TAF_CALL_APP_ENCRYPTED_VOICE_DATA_IND,              AT_RcvXcallEncryptedVoiceDataInd},
#endif
#endif
    {ID_TAF_CALL_APP_PRIVACY_MODE_SET_CNF,                  AT_RcvXcallPrivacyModeSetCnf},
    {ID_TAF_CALL_APP_PRIVACY_MODE_QRY_CNF,                  AT_RcvXcallPrivacyModeQryCnf},
    {ID_TAF_CALL_APP_PRIVACY_MODE_IND,                      AT_RcvXcallPrivacyModeInd},
#endif
    /* 为避免宏值关闭，编译报错，临时增加，后续删除  */
    {ID_TAF_CALL_APP_TYPE_BUTT,                             VOS_NULL_PTR}
};

/* Added by w00167002 for L-C互操作项目, 2014-2-21, begin */
const AT_PROC_MSG_FROM_MMA_STRU g_astAtProcMsgFromMmaTab[]=
{
    /* 消息ID */                            /* 消息处理函数 */
#ifndef __PS_WIN32_RECUR__
    {ID_TAF_MMA_OM_MAINTAIN_INFO_IND,   AT_RcvMmaOmMaintainInfoInd},
#endif

    {ID_TAF_MMA_USIM_STATUS_IND,            AT_RcvAtMmaUsimStatusInd},
    {ID_TAF_MMA_CMM_SET_CNF,            AT_RcvMmaCmmSetCmdRsp},
    {ID_TAF_MMA_SIMLOCK_STAUS_QUERY_CNF, AT_RcvSimLockQryRsp},
    {ID_TAF_MMA_AC_INFO_QRY_CNF,        AT_RcvMmaAcInfoQueryCnf},
    {ID_TAF_MMA_AC_INFO_CHANGE_IND,     AT_RcvMmaAcInfoChangeInd},
    {ID_TAF_MMA_EOPLMN_SET_CNF,         AT_RcvMmaEOPlmnSetCnf},
    {ID_TAF_MMA_NET_SCAN_CNF,           AT_RcvMmaNetScanCnf},
    {ID_TAF_MMA_USER_SRV_STATE_QRY_CNF,   AT_RcvMmaUserSrvStateQryCnf},
    {ID_TAF_MMA_POWER_ON_AND_REG_TIME_QRY_CNF,     AT_RcvMmaPwrOnAndRegTimeQryCnf},
    {ID_TAF_MMA_SPN_QRY_CNF,            AT_RcvMmaSpnQryCnf},
    {ID_TAF_MMA_MMPLMNINFO_QRY_CNF,     AT_RcvMmaMMPlmnInfoQryCnf},
    {ID_TAF_MMA_LAST_CAMP_PLMN_QRY_CNF,           AT_RcvMmaPlmnQryCnf},
    {ID_TAF_MMA_EOPLMN_QRY_CNF,         AT_RcvMmaEOPlmnQryCnf},
    {ID_TAF_MMA_COPN_INFO_QRY_CNF,      AT_RcvMmaCopnInfoQueryCnf},
    {ID_TAF_MMA_SIM_INSERT_CNF,          AT_RcvMmaSimInsertRsp},
    {ID_TAF_MMA_SYS_CFG_SET_CNF,        AT_RcvMmaSysCfgSetCnf},
    {ID_TAF_MMA_PHONE_MODE_SET_CNF,     AT_RcvMmaPhoneModeSetCnf},
    {ID_TAF_MMA_DETACH_CNF,             AT_RcvMmaDetachCnf},
    {ID_TAF_MMA_ATTACH_CNF,             AT_RcvMmaAttachCnf},
    {ID_TAF_MMA_ATTACH_STATUS_QRY_CNF,  AT_RcvMmaAttachStatusQryCnf},

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    {ID_TAF_MMA_CDMA_LOCINFO_QRY_CNF,   AT_RcvMmaCLocInfoQueryCnf},
    {ID_TAF_MMA_CSID_IND,               AT_RcvMmaCSidInd},

    {ID_TAF_MMA_1X_EMC_CALL_BACK_NTF,   AT_RcvMmaEmcCallBackNtf},
    {ID_TAF_MMA_QUIT_CALLBACK_SET_CNF,  AT_RcvMmaQuitCallBackCnf},
    {ID_TAF_MMA_CSIDLIST_SET_CNF,       AT_RcvMmaSetCSidListCnf},
    {ID_TAF_MMA_1X_EMC_CALL_BACK_QRY_CNF,  AT_RcvMmaQryEmcCallBackCnf},
    {ID_TAF_MMA_CURR_SID_NID_QRY_CNF,   AT_RcvMmaQryCurrSidNidCnf},

    {ID_TAF_MMA_CLOCINFO_IND,           AT_RcvMmaClocinfoInd},
#endif

    {ID_TAF_MMA_CTIME_IND,              AT_RcvMmaCTimeInd},

    {ID_TAF_MMA_CDMA_FREQ_LOCK_SET_CNF, AT_RcvMmaCFreqLockSetCnf},
    {ID_TAF_MMA_CDMA_FREQ_LOCK_QRY_CNF, AT_RcvMmaCFreqLockQueryCnf},

    {ID_TAF_MMA_CDMACSQ_SET_CNF,        AT_RcvMmaCdmaCsqSetCnf},
    {ID_TAF_MMA_CDMACSQ_QRY_CNF,        AT_RcvMmaCdmaCsqQryCnf},
    {ID_TAF_MMA_CDMACSQ_IND,            AT_RcvMmaCdmaCsqInd},

    {ID_MMA_TAF_HDR_CSQ_VALUE_IND,      AT_RcvMmaHdrCsqInd},
    {ID_MMA_TAF_HDR_CSQ_SET_CNF,        AT_RcvMmaHdrCsqSetCnf},
    {ID_MMA_TAF_HDR_CSQ_QRY_SETTING_CNF,AT_RcvMmaHdrCsqQryCnf},

    {ID_TAF_MMA_CFPLMN_SET_CNF,         AT_RcvMmaCFPlmnSetCnf},
    {ID_TAF_MMA_CFPLMN_QUERY_CNF,       AT_RcvMmaCFPlmnQueryCnf},

    {ID_TAF_MMA_PREF_PLMN_SET_CNF,     AT_RcvMmaPrefPlmnSetCnf},
    {ID_TAF_MMA_PREF_PLMN_QUERY_CNF,   AT_RcvMmaPrefPlmnQueryCnf},
    {ID_TAF_MMA_PREF_PLMN_TEST_CNF,    AT_RcvMmaPrefPlmnTestCnf},

    {ID_TAF_MMA_PLMN_AUTO_RESEL_CNF,   AT_RcvMmaPlmnReselAutoSetCnf},
    {ID_TAF_MMA_PLMN_SPECIAL_SEL_CNF,  AT_RcvMmaPlmnSpecialSelSetCnf},
    {ID_TAF_MMA_PLMN_LIST_ABORT_CNF,   AT_RcvMmaPlmnListAbortCnf},
    {ID_TAF_MMA_LOCATION_INFO_QRY_CNF,       AT_RcvMmaLocInfoQueryCnf},
    {ID_TAF_MMA_CIPHER_QRY_CNF,        AT_RcvMmaCipherInfoQueryCnf},
    {ID_TAF_MMA_PREF_PLMN_TYPE_SET_CNF,  AT_RcvMmaPrefPlmnTypeSetCnf},
    {ID_TAF_MMA_MT_POWER_DOWN_CNF,     AT_RcvMmaPowerDownCnf},


    {ID_TAF_MMA_PHONE_MODE_QRY_CNF,   AT_RcvMmaPhoneModeQryCnf},
    {ID_TAF_MMA_TIME_CHANGE_IND,      AT_RcvMmaTimeChangeInd},
    {ID_TAF_MMA_MODE_CHANGE_IND,      AT_RcvMmaModeChangeInd},
    {ID_TAF_MMA_PLMN_CHANGE_IND,      AT_RcvMmaPlmnChangeInd},

    {ID_TAF_MMA_CERSSI_SET_CNF,        AT_RcvMmaCerssiSetCnf},
    {ID_TAF_MMA_CERSSI_QRY_CNF,        AT_RcvMmaCerssiInfoQueryCnf},
    {ID_TAF_MMA_ACCESS_MODE_QRY_CNF,   AT_RcvMmaAccessModeQryCnf},
    {ID_TAF_MMA_COPS_QRY_CNF,          AT_RcvMmaCopsQryCnf},
    {ID_TAF_MMA_REG_STATE_QRY_CNF,     AT_RcvMmaRegStateQryCnf},
    {ID_TAF_MMA_AUTO_ATTACH_QRY_CNF,   AT_RcvMmaAutoAttachQryCnf},
    {ID_TAF_MMA_SYSINFO_QRY_CNF,       AT_RcvMmaSysInfoQryCnf},
    {ID_TAF_MMA_ANTENNA_INFO_QRY_CNF,  AT_RcvMmaAnqueryQryCnf},
    {ID_TAF_MMA_HOME_PLMN_QRY_CNF,     AT_RcvMmaEHplmnInfoQryCnf},

    {ID_TAF_MMA_SRV_STATUS_IND,        AT_RcvMmaSrvStatusInd},
    {ID_TAF_MMA_RSSI_INFO_IND,         AT_RcvMmaRssiInfoInd},
    {ID_TAF_MMA_REG_STATUS_IND,        AT_RcvMmaRegStatusInd},
    {ID_TAF_MMA_REG_REJ_INFO_IND,      AT_RcvMmaRegRejInfoInd},
    {ID_TAF_MMA_PLMN_SELECTION_INFO_IND,  AT_RcvMmaPlmnSelectInfoInd},


    {ID_TAF_MMA_QUICKSTART_SET_CNF,     AT_RcvTafMmaQuickStartSetCnf},
    {ID_TAF_MMA_AUTO_ATTACH_SET_CNF,    AT_RcvTafMmaAutoAttachSetCnf},
    {ID_TAF_MMA_SYSCFG_QRY_CNF,         AT_RcvTafMmaSyscfgQryCnf},
    {ID_TAF_MMA_SYSCFG_TEST_CNF,        AT_RcvTafMmaSyscfgTestCnf},
    {ID_TAF_MMA_CRPN_QRY_CNF,           AT_RcvTafMmaCrpnQryCnf},
    {ID_TAF_MMA_QUICKSTART_QRY_CNF,     AT_RcvTafMmaQuickStartQryCnf},
    {ID_TAF_MMA_CSNR_QRY_CNF,           AT_RcvTafMmaCsnrQryCnf},
    {ID_TAF_MMA_CSQ_QRY_CNF,            AT_RcvTafMmaCsqQryCnf},
    {ID_TAF_MMA_CSQLVL_QRY_CNF,         AT_RcvTafMmaCsqlvlQryCnf},

    {ID_TAF_MMA_BATTERY_CAPACITY_QRY_CNF, AT_RcvMmaCbcQryCnf},
    {ID_TAF_MMA_HAND_SHAKE_QRY_CNF,      AT_RcvMmaHsQryCnf},
    {ID_TAF_MMA_PLMN_LIST_CNF,          At_QryParaPlmnListProc},
    {ID_TAF_MSG_MMA_EONS_UCS2_CNF,      AT_RcvMmaEonsUcs2Cnf},

#if (FEATURE_ON == FEATURE_CSG)
     {ID_TAF_MMA_CSG_LIST_SEARCH_CNF,       AT_RcvMmaCsgListSearchCnfProc},
     {ID_TAF_MMA_CSG_LIST_ABORT_CNF,        AT_RcvMmaCsgListAbortCnf},
#endif
#if (FEATURE_ON == FEATURE_IMS)
    {ID_TAF_MMA_IMS_SWITCH_SET_CNF,     AT_RcvMmaImsSwitchSetCnf},
    {ID_TAF_MMA_IMS_SWITCH_QRY_CNF,     AT_RcvMmaImsSwitchQryCnf},
    {ID_TAF_MMA_VOICE_DOMAIN_SET_CNF,   AT_RcvMmaVoiceDomainSetCnf},
    {ID_TAF_MMA_VOICE_DOMAIN_QRY_CNF,   AT_RcvMmaVoiceDomainQryCnf},
#endif

    {ID_TAF_MMA_1XCHAN_SET_CNF,     AT_RcvMma1xChanSetCnf},
    {ID_TAF_MMA_1XCHAN_QUERY_CNF,   AT_RcvMma1xChanQueryCnf},
    {ID_TAF_MMA_CVER_QUERY_CNF,     AT_RcvMmaCVerQueryCnf},
    {ID_TAF_MMA_GETSTA_QUERY_CNF,   AT_RcvMmaStateQueryCnf},
    {ID_TAF_MMA_CHIGHVER_QUERY_CNF, AT_RcvMmaCHverQueryCnf},
    {ID_TAF_MMA_SRCHED_PLMN_INFO_IND, AT_RcvMmaSrchedPlmnInfoInd},

    {ID_TAF_MMA_DPLMN_SET_CNF,       AT_RcvMmaDplmnSetCnf},
    {ID_TAF_MMA_DPLMN_QRY_CNF,       AT_RcvMmaDplmnQryCnf},

    {ID_TAF_MMA_CLMODE_IND,           AT_RcvMmaCLModInd},
    {ID_TAF_MMA_INIT_LOC_INFO_IND,    AT_RcvMmaInitLocInfoInd},
};
/* Added by w00167002 for L-C互操作项目, 2014-2-21, end */

/* AT码流缓存数组(包括AT命令或其它数据)。
   设置该缓存数组的原因:底软任务在调用At_CmdStreamPreProc接口时，某些场景下(如直接使用超级终端发送AT命令),则会
   出现AT码流以一个字符为单位发送到AT的消息队列中，导致AT的消息队列慢，触发单板复位。*/
AT_DATA_STREAM_BUFFER_STRU              g_aucAtDataBuff[AT_MAX_CLIENT_NUM];

/*CREG/CGREG的<CI>域以4字节上报是否使能(VDF需求)*/

AT_CLIENT_MANAGE_STRU                   gastAtClientTab[AT_MAX_CLIENT_NUM];

TAF_UINT32                              gulPBPrintTag = VOS_FALSE;

/* Added by f00179208 for AT Project，2011-11-04,  Begin*/
extern VOS_BOOL                         g_bSetFlg;
/* Added by f00179208 for AT Project，2011-11-04,  End*/

/*****************************************************************************
   3 函数、变量声明
*****************************************************************************/

extern VOS_UINT32    AT_ProcTempprtEventInd(
    TEMP_PROTECT_EVENT_AT_IND_STRU     *pstMsg
);

/*****************************************************************************
   4 函数实现
*****************************************************************************/

#ifdef __PS_WIN32_RECUR__

/*****************************************************************************
 函 数 名  : AT_RestoreClientData
 功能描述  : 恢复AT模块上的客户端口数据表
 输入参数  : NAS_AT_OUTSIDE_RUNNING_CONTEXT_PART_ST          *pstOutsideCtx
 输出参数  : 无
 返 回 值  : TAF_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月17日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数

  2.日    期   : 2011年9月30日
    作    者   : 鲁琳/l60609
    修改内容   : AT Project: 删除At_RegTafCallBackFunc

*****************************************************************************/
TAF_VOID AT_RestoreClientData(
    NAS_AT_SDT_AT_CLIENT_TABLE_STRU    *pstAtClientData
)
{
    TAF_UINT8                                       ucLoop;

    for (ucLoop = 0; ucLoop < AT_MAX_CLIENT_NUM; ucLoop++)
    {
        gastAtClientTab[ucLoop].usClientId      = pstAtClientData->gastAtClientTab[ucLoop].usClientId;
        gastAtClientTab[ucLoop].opId            = pstAtClientData->gastAtClientTab[ucLoop].opId;
        gastAtClientTab[ucLoop].ucUsed          = pstAtClientData->gastAtClientTab[ucLoop].ucUsed;
        gastAtClientTab[ucLoop].UserType        = pstAtClientData->gastAtClientTab[ucLoop].UserType;
        gastAtClientTab[ucLoop].Mode            = pstAtClientData->gastAtClientTab[ucLoop].Mode;
        gastAtClientTab[ucLoop].IndMode         = pstAtClientData->gastAtClientTab[ucLoop].IndMode;
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_RestoreContextData
 功能描述  : 恢复AT全局变量。
 输入参数  : pMsg   PC回放消息指针；
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2010年02月12日
    作    者   : 傅映君 62575
    修改内容   : 新生成函数
  2.日    期   : 2010年7月16日
    作    者   : 傅映君/f62575
    修改内容   : 问题单号：DTS2010071402189，支持AT模块多CLIENT ID的回放
  3.日    期   : 2013年03月07日
    作    者   : f00179208
    修改内容   : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 AT_RestoreContextData(
    AT_MSG_STRU                         *pMsg
)
{
    NAS_AT_SDT_AT_PART_ST                  *pRcvMsgCB     = VOS_NULL_PTR;
    NAS_AT_OUTSIDE_RUNNING_CONTEXT_PART_ST *pstOutsideCtx = VOS_NULL_PTR;
    AT_MODEM_SMS_CTX_STRU                  *pstSmsCtx     = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                    enModemId;

    pRcvMsgCB     = (NAS_AT_SDT_AT_PART_ST *)pMsg;

    if (AT_PC_REPLAY_MSG == pRcvMsgCB->ucType)
    {
        for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
        {
            pstSmsCtx                       = AT_GetModemSmsCtxAddrFromModemId(enModemId);
            pstOutsideCtx                   = &pRcvMsgCB->astOutsideCtx[enModemId];

            gucAtCscsType                   = pstOutsideCtx->gucAtCscsType;
            pstSmsCtx->ucCsdhType           = pstOutsideCtx->gucAtCsdhType;
            g_OpId                          = pstOutsideCtx->g_OpId;
            pstSmsCtx->enCsmsMsgVersion     = pstOutsideCtx->g_enAtCsmsMsgVersion;
            pstSmsCtx->enCmgfMsgFormat      = pstOutsideCtx->g_enAtCmgfMsgFormat;

            PS_MEM_CPY(&(pstSmsCtx->stCnmiType),
                       &pstOutsideCtx->gstAtCnmiType,
                       sizeof(pstSmsCtx->stCnmiType));

            PS_MEM_CPY(&(pstSmsCtx->stCgsmsSendDomain),
                         &pstOutsideCtx->g_stAtCgsmsSendDomain,
                         sizeof(pstSmsCtx->stCgsmsSendDomain));

            PS_MEM_CPY(&(pstSmsCtx->stCscaCsmpInfo),
                         &pstOutsideCtx->g_stAtCscaCsmpInfo,
                         sizeof(pstSmsCtx->stCscaCsmpInfo));

            PS_MEM_CPY(&(pstSmsCtx->stCpmsInfo),
                         &pstOutsideCtx->g_stAtCpmsInfo,
                         sizeof(pstSmsCtx->stCpmsInfo));

            AT_INFO_LOG("MSG: AT_RestoreContextData data is restored.");
        }
    }

    return AT_OK;
}
#endif
/* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

/*****************************************************************************
 函 数 名  : At_MmaMsgProc
 功能描述  : AT模块处理来自MMA的消息
 输入参数  : MSG_HEADER_STRU * pstMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年2月22日
    作    者   : f62575
    修改内容   : 新生成函数

  2.日    期   : 2010年7月16日
    作    者   : 傅映君/f62575
    修改内容   : 问题单号：DTS2010071402189，支持AT模块多CLIENT ID的回放

  3.日    期   : 2011年10月17日
    作    者   : o00132663
    修改内容   : AT移植项目，增加AT处理CC和MMA模块的消息
  4.日    期   : 2012年4月24日
    作    者   : l00171473
    修改内容   : DTS2012041805606
  5.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 增加mma的小区接入禁止信息上报消息的处理
  6.日    期   : 2013年2月4日
    作    者   : t00212959
    修改内容   : DTS2013020600770:at^cerssi?增加返回参数
  7.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，支持+COPN命令
  8.日    期   : 2014年01月15日
    作    者   : f62575
    修改内容   : DTS2014011301359: 增加对+CPOL查询命令的响应消息处理

  9.日    期   : 2014年3月5日
    作    者   : w00167002
    修改内容   : AT处理MMA的消息调整为表格，降圈复杂度
*****************************************************************************/
TAF_VOID At_MmaMsgProc(
    MSG_HEADER_STRU                     *pstMsg
)
{
    /* Modified by w00167002 for L-C互操作项目, 2014-3-5, begin */
    VOS_UINT32                          i;
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /*从g_astAtProcMsgFromMmaTab中获取消息个数*/
    ulMsgCnt = sizeof(g_astAtProcMsgFromMmaTab)/sizeof(AT_PROC_MSG_FROM_MMA_STRU);

    /*g_astAtProcMsgFromMtaTab查表，进行消息分发*/
    for (i = 0; i < ulMsgCnt; i++)
    {
        if (g_astAtProcMsgFromMmaTab[i].ulMsgName == pstMsg->ulMsgName)
        {
            ulRst = g_astAtProcMsgFromMmaTab[i].pProcMsgFunc(pstMsg);

            if (VOS_ERR == ulRst)
            {
                AT_ERR_LOG("At_MmaMsgProc: Msg Proc Err!");
            }

            return;
        }
    }

    /*没有找到匹配的消息*/
    if (ulMsgCnt == i)
    {
        AT_ERR_LOG("At_MmaMsgProc: Msg Id is invalid!");
    }

    /* Modified by w00167002 for L-C互操作项目, 2014-3-5, end */
    return;
}

/*****************************************************************************
 函 数 名  : At_CallMsgProc
 功能描述  : AT模块处理来自XCALL的消息
 输入参数  : MSG_HEADER_STRU * pstMsg
 输出参数  : 无
 返 回 值  : TAF_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月2日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
TAF_UINT32 At_CallMsgProc(
    MSG_HEADER_STRU                     *pstMsg
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          i;
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /*从g_astAtProcMsgFromXcallTab中获取消息个数*/
    ulMsgCnt = sizeof(g_astAtProcMsgFromCallTab)/sizeof(AT_PROC_MSG_FROM_CALL_STRU);

    /*g_astAtProcMsgFromXcallTab查表，进行消息分发*/
    for (i = 0; i < ulMsgCnt; i++)
    {
        if ((g_astAtProcMsgFromCallTab[i].ulMsgName == pstMsg->ulMsgName)
         && (ID_TAF_CALL_APP_TYPE_BUTT != pstMsg->ulMsgName))
        {
            ulRst = g_astAtProcMsgFromCallTab[i].pProcMsgFunc(pstMsg);

            if (VOS_ERR == ulRst)
            {
                AT_ERR_LOG("AT_XcallMsgProc: Msg Proc Err!");
            }

            return AT_OK;
        }
    }

    /*没有找到匹配的消息*/
    if (ulMsgCnt == i)
    {
        AT_ERR_LOG("AT_XcallMsgProc: Msg Id is invalid!");
    }
#endif

    return AT_ERROR;
}

/*****************************************************************************
Prototype      : At_EventMsgProc
Description    : AT模块消息处理入口函数，该函数注册给DOPRA调度。
Input          : pMsg -- VOS消息指针
Output         : None
Return Value   : None
Calls          : None
Called By      : DOPRA

  History        : ---
  1.Date        : 2005-04-19
  Author      : ---
  Modification: Created function
  2. Date:2006-04-12
     Author: w42656
     Modification:修改At_MsgProc,问题单号: A32D01851
  3.日    期   : 2008年6月10日
    作    者   : luojian id:00107747
    修改内容   : 问题单号:AT2D03704
  4.日    期   : 2010年7月16日
    作    者   : 傅映君/f62575
    修改内容   : 问题单号：DTS2010071402189，支持AT模块多CLIENT ID的回放
  5.日    期   : 2011年12月20日
    作    者   : o00132663
    修改内容   : PS融合项目，MN_CALLBACK_DATA_FLOW消息已经被消息ID_EVT_TAF
                 _PS_REPORT_DSFLOW_IND替代，删除。
  6.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目

*****************************************************************************/
TAF_VOID At_EventMsgProc(MN_AT_IND_EVT_STRU *pMsg)
{

    switch(pMsg->usMsgName)
    {
        case MN_CALLBACK_MSG:
            At_SmsMsgProc(pMsg, pMsg->usLen);
            return;

        case MN_CALLBACK_SET:
            At_SetMsgProc(pMsg->aucContent, pMsg->usLen);
            return;

        case MN_CALLBACK_QRY:
            At_QryMsgProc(pMsg->aucContent, pMsg->usLen);
            return;

        case MN_CALLBACK_PS_CALL:
            /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
            /* PS域事件处理 */
            AT_RcvTafPsEvt((TAF_PS_EVT_STRU*)pMsg);
            /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */
            return;

        case MN_CALLBACK_DATA_STATUS:
            At_DataStatusMsgProc(pMsg->aucContent, pMsg->usLen);
            return;

        case MN_CALLBACK_CS_CALL:
            At_CsMsgProc(pMsg,pMsg->usLen);
            return;

        case MN_CALLBACK_SS:
            At_SsMsgProc(pMsg->aucContent, pMsg->usLen);
            return;

        case MN_CALLBACK_PHONE:
            At_PhMsgProc(pMsg->aucContent, pMsg->usLen);
            break;

        case MN_CALLBACK_PHONE_BOOK:
            At_TAFPbMsgProc(pMsg->aucContent, pMsg->usLen);
            break;

        case MN_CALLBACK_CMD_CNF:
            At_CmdCnfMsgProc(pMsg->aucContent, pMsg->usLen);
            break;

        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
        case MN_CALLBACK_VOICE_CONTROL:
            At_VcMsgProc(pMsg, pMsg->usLen);
            break;
        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

        case MN_CALLBACK_LOG_PRINT:
            AT_LogPrintMsgProc((TAF_MNTN_LOG_PRINT_STRU *)pMsg);
            break;

        default:
            AT_LOG1("At_MsgProc: invalid message name.", pMsg->usMsgName);
            return;
    }
}


/*****************************************************************************
 函 数 名  : AT_E5CheckRight
 功能描述  : 检查是否有权限操作AT命令
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_BOOL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年10月18日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2010年12月25日
    作    者   : lijun 00171473
    修改内容   : DTS2010122500864 修改OPENPORT在SSCOM中输入的特殊处理
  3.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目 :删除NAS_FEATURE_AT_PWD宏
*****************************************************************************/
VOS_BOOL AT_E5CheckRight(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    static VOS_BOOL                     bIsRight = VOS_FALSE;
    VOS_UINT8                           aucCmdTmp[20]; /* 须大于aucQuickCmd[]的长度 */
    VOS_UINT8                           aucQuickCmd[] = "AT^OPENPORT=";
    VOS_UINT16                          usQuickCmdLen;
    VOS_UINT16                          usLeftLen;
    VOS_UINT8                           *pucPwdPos;
    VOS_CHAR                            acPassword[AT_RIGHT_PWD_LEN+1];
    VOS_UINT8                           *pucAtStart ;

    /* 当前权限未开启,直接返回  */
    if ( AT_RIGHT_OPEN_FLAG_CLOSE == g_stAtRightOpenFlg.enRightOpenFlg )
    {
        return VOS_TRUE;
    }

    /* 如果已经获取到权限,则直接返回 */
    if ( VOS_TRUE == bIsRight )
    {
        return VOS_TRUE;
    }

    /* SSCOM 输入的字符串前有 0x0A */
    pucAtStart = pucData;
    while( (*pucAtStart != 'a') && (*pucAtStart != 'A')  )
    {
        pucAtStart++;
        if ( pucAtStart >= (pucData+usLen) )
        {
            /* 未找到 a 或 A break */
            break;
        }
    }
    usLen -= (VOS_UINT16)(pucAtStart - pucData);
    pucData = pucAtStart;

    /* 长度非法,直接返回无权限 */
    usQuickCmdLen = (VOS_UINT16)VOS_StrLen((VOS_CHAR *)aucQuickCmd);
    if (usLen <= usQuickCmdLen)
    {
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_FALSE;
    }

    VOS_MemSet(aucCmdTmp, 0x00, (VOS_SIZE_T)sizeof(aucCmdTmp));
    VOS_MemCpy(aucCmdTmp, pucData, (VOS_SIZE_T)usQuickCmdLen);

    /* 不是AT^OPENPORT命令直接返回无权限 */
    if (0 != VOS_StrNiCmp((VOS_CHAR *)aucCmdTmp,
                          (VOS_CHAR *)aucQuickCmd,
                          (VOS_SIZE_T)usQuickCmdLen))
    {
        At_FormatResultData(ucIndex,AT_ERROR);
        return VOS_FALSE;
    }

    usLeftLen = usLen - usQuickCmdLen;
    pucPwdPos = pucData + usQuickCmdLen;

    if ( usLeftLen >= sizeof(aucCmdTmp) )
    {
        At_FormatResultData(ucIndex,AT_ERROR);
        return VOS_FALSE;
    }

    VOS_MemSet(aucCmdTmp, 0x00, sizeof(aucCmdTmp));
    VOS_MemCpy(aucCmdTmp, pucPwdPos, usLeftLen);

    PS_MEM_SET(acPassword,0x00,sizeof(acPassword));
    PS_MEM_CPY(acPassword,g_stAtRightOpenFlg.acPassword,sizeof(g_stAtRightOpenFlg.acPassword));

    /* 比较密码是否相同*/
    if ( 0 == VOS_StrCmp(acPassword, (VOS_CHAR *)aucCmdTmp))
    {
        /* 上报OK并记录有权限 */
        At_FormatResultData(ucIndex, AT_OK);
        bIsRight = VOS_TRUE;
        return VOS_FALSE;
    }

    /* 上报ERROR */
    At_FormatResultData(ucIndex, AT_ERROR);
    return VOS_FALSE;
}

/*****************************************************************************
 Prototype      : At_PppProtocolRelIndProc
 Description    : AT接收PPP链路释放完成指示消息
 Input          : pMsg
 Output         : ---
 Return Value   : VOS_VOID
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2010-03-04
    Author      : L47619
    Modification: Created function

  2.日    期   : 2013年05月27日
    作    者   : f00179208
    修改内容   : V3R3 PPP PROJECT

  3.日    期   : 2013年9月21日
    作    者   : j00174725
    修改内容   : UART-MODEM: 增加支持UART端口
*****************************************************************************/
TAF_VOID At_PppProtocolRelIndProc(AT_PPP_PROTOCOL_REL_IND_MSG_STRU *pMsg)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usPppId;

    usPppId = pMsg->usPppId;
    ucIndex = gastAtPppIndexTab[usPppId];

    if ( (AT_MODEM_USER == gastAtClientTab[ucIndex].UserType)
      || (AT_HSUART_USER == gastAtClientTab[ucIndex].UserType) )
    {
        if ( (AT_DATA_MODE == gastAtClientTab[ucIndex].Mode)
          && (AT_PPP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
          && (AT_CMD_WAIT_PPP_PROTOCOL_REL_SET == gastAtClientTab[ucIndex].CmdCurrentOpt) )
        {
            /* 将AT通道切换为命令模式 */
            At_SetMode(ucIndex, AT_CMD_MODE, AT_NORMAL_MODE);

            /* 停止定时器 */
            AT_STOP_TIMER_CMD_READY(ucIndex);

            /* 回复NO CARRIER */
            gstAtSendData.usBufLen = 0;
            At_FormatResultData(ucIndex, AT_NO_CARRIER);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_ModemMscIndProc
 功能描述  : AT接收管脚信号的处理
 输入参数  : AT_PPP_MODEM_MSC_IND_MSG_STRU *pMsg
 输出参数  : 无
 返 回 值  : TAF_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.Date        : 2010-03-04
    Author      : L47619
    Modification: Created function

  2.日    期   : 2011年10月15日
    作    者   : 鲁琳/l60609
    修改内容   : AT Project:静态分配 client id

  3.日    期   : 2013年05月27日
    作    者   : f00179208
    修改内容   : V3R3 PPP PROJECT

  4.日    期   : 2013年09月21日
    作    者   : j00174725
    修改内容   : UART-MODEM: 增加支持UART端口
*****************************************************************************/
VOS_VOID AT_ModemMscIndProc(AT_PPP_MODEM_MSC_IND_MSG_STRU *pMsg)
{
    VOS_UINT8                           ucIndex;

    ucIndex = pMsg->ucIndex;

    AT_MNTN_TraceInputMsc(ucIndex, (AT_DCE_MSC_STRU *)pMsg->aucMscInd);

    if ( (AT_MODEM_USER == gastAtClientTab[ucIndex].UserType)
      || (AT_HSUART_USER == gastAtClientTab[ucIndex].UserType) )
    {
        AT_ModemStatusPreProc(ucIndex, (AT_DCE_MSC_STRU *)pMsg->aucMscInd);
    }
    else
    {
        AT_WARN_LOG1("AT_ModemMscIndProc: index %d is unused", ucIndex);
    }

    return;
}

/*****************************************************************************
Prototype      : At_PppMsgProc
Description    : AT处理PPP发送的消息
Input          : pMsg -- VOS消息指针
Output         : None
Return Value   : None
Calls          : None
Called By      : DOPRA

  History      : ---
  1.Date       : 2009-09-24
  Author       : L47619
  Modification : Created function
*****************************************************************************/
TAF_VOID At_PppMsgProc(MSG_HEADER_STRU *pMsg)
{
    switch  (pMsg->ulMsgName)
    {
        case AT_PPP_RELEASE_IND_MSG:
            At_PppReleaseIndProc(((AT_PPP_RELEASE_IND_MSG_STRU *)pMsg)->ucIndex);
            break;

        case AT_PPP_MODEM_MSC_IND_MSG:
            AT_ModemMscIndProc((AT_PPP_MODEM_MSC_IND_MSG_STRU *)pMsg);
            break;

        case AT_PPP_PROTOCOL_REL_IND_MSG:
            At_PppProtocolRelIndProc((AT_PPP_PROTOCOL_REL_IND_MSG_STRU *)pMsg);
            break;

        default:
            AT_LOG1("At_PppMsgProc: ulMsgName is abnormal!",pMsg->ulMsgName);
            break;
    }
}


/*****************************************************************************
 函 数 名  : At_RfCfgCnfReturnErrProc
 功能描述  : DSP返回的Rf配置结果原语,回复出错情况的处理
 输入参数  : ucIndex - 用户索引
 输出参数  : 无
 返 回 值  : 执行结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月30日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  At_RfCfgCnfReturnErrProc(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulRslt;

    switch (gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
       case AT_CMD_SET_FTXON:
           ulRslt = AT_FTXON_SET_FAIL;
           break;

       case AT_CMD_SET_FRXON:
           ulRslt = AT_FRXON_SET_FAIL;
           break;

       case AT_CMD_QUERY_RSSI:
           ulRslt = AT_FRSSI_OTHER_ERR;
           break;

       /* 设置主集和分集时收到DSP回复出错情况下返回的错误码相同 */
       case AT_CMD_SET_RXDIV:
       case AT_CMD_SET_RXPRI:
           ulRslt = AT_CME_RX_DIV_OTHER_ERR;
           break;

       default:
           ulRslt = AT_ERROR;
           break;
    }

   return ulRslt;
}

/*****************************************************************************
 函 数 名  : At_RfCfgCnfReturnSuccProc
 功能描述  : DSP返回的Rf配置结果原语,回复成功情况的处理
 输入参数  : ucIndex - 用户索引
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月30日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  At_RfCfgCnfReturnSuccProc(
    VOS_UINT8                           ucIndex
)
{
    switch (gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        case AT_CMD_SET_FTXON:
            g_stAtDevCmdCtrl.ucTxOnOff = (VOS_UINT8)gastAtParaList[0].ulParaValue;

            /* 如果是打开发射机操作，需要记录最近一次执行的是打开发射机还是打开接收机操作 */
            if (AT_DSP_RF_SWITCH_ON == g_stAtDevCmdCtrl.ucTxOnOff)
            {
                g_stAtDevCmdCtrl.ucRxonOrTxon = AT_TXON_OPEN;
            }
            break;

        case AT_CMD_SET_FRXON:
            g_stAtDevCmdCtrl.ucRxOnOff = (VOS_UINT8)gastAtParaList[0].ulParaValue;

            /* 如果是打开接收机操作，需要记录最近一次执行的是打开发射机还是打开接收机操作 */
            if (AT_DSP_RF_SWITCH_ON == g_stAtDevCmdCtrl.ucRxOnOff)
            {
                g_stAtDevCmdCtrl.ucRxonOrTxon = AT_RXON_OPEN;
            }
            break;

        case AT_CMD_QUERY_RSSI:
            break;

        case AT_CMD_SET_RXDIV:
           if ((AT_OK == At_SaveRxDivPara(g_stAtDevCmdCtrl.usOrigBand, 1))
            && (AT_TMODE_FTM == g_stAtDevCmdCtrl.ucCurrentTMode))
           {
               g_stAtDevCmdCtrl.ucPriOrDiv = AT_RX_DIV_ON;
               g_stAtDevCmdCtrl.usRxDiv    = g_stAtDevCmdCtrl.usOrigBand;
           }
           break;

        case AT_CMD_SET_RXPRI:
            g_stAtDevCmdCtrl.ucPriOrDiv = AT_RX_PRI_ON;
            g_stAtDevCmdCtrl.usRxPri    = g_stAtDevCmdCtrl.usOrigBand;
            break;

        default:
            break;
    }

    return;

}

/*****************************************************************************
 函 数 名  : At_HpaRfCfgCnfProc
 功能描述  : DSP返回的Rf配置结果原语
 输入参数  : pstMsg - DSP回复消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年6月28日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  At_HpaRfCfgCnfProc(
    HPA_AT_RF_CFG_CNF_STRU              *pstMsg
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;

    /*获取本地保存的用户索引*/
    ucIndex = g_stAtDevCmdCtrl.ucIndex;

    if (AT_HPA_RSLT_FAIL == pstMsg->usErrFlg)
    {
        AT_INFO_LOG("At_HpaRfCfgCnfProc: set rfcfg err");
        ulRslt = At_RfCfgCnfReturnErrProc(ucIndex);
        AT_STOP_TIMER_CMD_READY(ucIndex);
        At_FormatResultData(ucIndex, ulRslt);
    }
    else
    {
        ulRslt = AT_OK;
        At_RfCfgCnfReturnSuccProc(ucIndex);

        /* ^FRSSI?在GDSP LOAD情况会收到ID_HPA_AT_RF_CFG_CNF消息,不用上报,等收到
           ID_HPA_AT_RF_RX_RSSI_IND消息时再上报 */
        if (AT_CMD_QUERY_RSSI != gastAtClientTab[ucIndex].CmdCurrentOpt)
        {
            AT_STOP_TIMER_CMD_READY(ucIndex);
            At_FormatResultData(ucIndex, ulRslt);
        }
    }
    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : At_CHpaRfCfgCnfProc
 功能描述  : DSP返回的Rf配置结果原语
 输入参数  : pstMsg - DSP回复消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年6月28日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  At_CHpaRfCfgCnfProc(
    CHPA_AT_RF_CFG_CNF_STRU             *pstMsg
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;

    /*获取本地保存的用户索引*/
    ucIndex = g_stAtDevCmdCtrl.ucIndex;

    if (AT_HPA_RSLT_FAIL == pstMsg->usErrFlg)
    {
        AT_INFO_LOG("At_CHpaRfCfgCnfProc: set rfcfg err");
        ulRslt = At_RfCfgCnfReturnErrProc(ucIndex);
        AT_STOP_TIMER_CMD_READY(ucIndex);
        At_FormatResultData(ucIndex, ulRslt);
    }
    else
    {
        ulRslt = AT_OK;
        At_RfCfgCnfReturnSuccProc(ucIndex);

        AT_STOP_TIMER_CMD_READY(ucIndex);
        At_FormatResultData(ucIndex, ulRslt);
    }
    return;
}
#endif


/*****************************************************************************
 函 数 名  : AT_RfRssiIndProc
 功能描述  : 对DSP回复获取当前信道RSSI消息的处理
 输入参数  : pstMsg - 消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月19日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2011年10月18日
    作    者   : c00173809
    修改内容   : AT融合项目，修改浮点数运算。

*****************************************************************************/
VOS_VOID  At_RfRssiIndProc(
    HPA_AT_RF_RX_RSSI_IND_STRU          *pstMsg
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;
    VOS_INT32                           lRssi;

    /*获取本地保存的用户索引*/
    ucIndex  = g_stAtDevCmdCtrl.ucIndex;

    if (AT_DSP_RF_AGC_STATE_ERROR == pstMsg->sAGCGain)  /* 错误 */
    {
        AT_WARN_LOG("AT_RfRssiIndProc err");
        ulRslt = AT_FRSSI_OTHER_ERR;
    }
    else
    {

        gstAtSendData.usBufLen = 0;

        /*由于RSSI测量值单位0.125dBm，为了消除浮点数*1000.*/
        lRssi = pstMsg->sRSSI * AT_DSP_RSSI_VALUE_MUL_THOUSAND;

        /*读取的RSSI值，采用正值上报，精确到0.1dBm定制值信息。如果当前的RSSI
          值为-85.1dBm，返回值为851. 由于之前乘1000，所以精确到0.1dBm这里要除100*/
        if (lRssi < 0 )
        {
            lRssi = (-1*lRssi)/100;
        }
        else
        {
            lRssi = lRssi/100;
        }

        /* 适配V7R5版本4RX接收，GU只报一个值，其他报0，L根据FTM上报结果，支持4RX接收上报4个值，不支持时上报1个值 */
#if (FEATURE_ON == FEATURE_LTE_4RX)
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d,0,0,0",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           lRssi);
#else
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           lRssi);
#endif

        gstAtSendData.usBufLen = usLength;
        ulRslt = AT_OK;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRslt);

    return;
}

/*****************************************************************************
 函 数 名  : At_HpaMsgProc
 功能描述  : 对WDSP回复消息的处理
 输入参数  : pstMsg - 回复消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年6月28日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  At_HPAMsgProc(
    MsgBlock                            *pstMsg
)
{
    HPA_AT_HEADER_STRU                  *pHeader;

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_HpaMsgProc: pstMsg is NULL");
        return;
    }

    pHeader = (HPA_AT_HEADER_STRU *)pstMsg;

    switch (pHeader->usMsgID)
    {
        case ID_HPA_AT_RF_CFG_CNF:
            At_HpaRfCfgCnfProc((HPA_AT_RF_CFG_CNF_STRU *)pstMsg);
            break;

        case ID_HPA_AT_RF_RX_RSSI_IND:
            At_RfRssiIndProc((HPA_AT_RF_RX_RSSI_IND_STRU *)pstMsg);
            break;

        case ID_AT_WPHY_RF_PLL_STATUS_CNF:
            At_RfPllStatusCnfProc((PHY_AT_RF_PLL_STATUS_CNF_STRU *)pstMsg);
            break;

        case ID_AT_WPHY_POWER_DET_CNF:
            At_RfFpowdetTCnfProc((PHY_AT_POWER_DET_CNF_STRU *)pstMsg);
            break;
        case ID_HPA_AT_MIPI_WR_CNF:
            At_MipiWrCnfProc((HPA_AT_MIPI_WR_CNF_STRU *)pstMsg);
            break;
        case ID_HPA_AT_MIPI_RD_CNF:
            At_MipiRdCnfProc((HPA_AT_MIPI_RD_CNF_STRU *)pstMsg);
            break;
        case ID_HPA_AT_SSI_WR_CNF:
            At_SsiWrCnfProc((HPA_AT_SSI_WR_CNF_STRU *)pstMsg);
            break;

        case ID_HPA_AT_SSI_RD_CNF:
            At_SsiRdCnfProc((HPA_AT_SSI_RD_CNF_STRU *)pstMsg);
            break;


        case ID_HPA_AT_PDM_CTRL_CNF:
            At_PdmCtrlCnfProc((HPA_AT_PDM_CTRL_CNF_STRU *)pstMsg);
            break;

        default:
            AT_WARN_LOG("At_HpaMsgProc: ulMsgName is Abnormal!");
            break;
    }

    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : At_CHpaMsgProc
 功能描述  : 对X DSP回复消息的处理
 输入参数  : pstMsg - 回复消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月18日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  At_CHPAMsgProc(
    MsgBlock                            *pstMsg
)
{
    HPA_AT_HEADER_STRU                  *pHeader = VOS_NULL_PTR;

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_HpaMsgProc: pstMsg is NULL");
        return;
    }

    pHeader = (HPA_AT_HEADER_STRU *)pstMsg;

    switch (pHeader->usMsgID)
    {
        case ID_CHPA_AT_RF_CFG_CNF:
            At_CHpaRfCfgCnfProc((CHPA_AT_RF_CFG_CNF_STRU *)pstMsg);
            break;

        default:
            AT_WARN_LOG("At_CHPAMsgProc: ulMsgName is Abnormal!");
            break;
    }

    return;
}
#endif


/*****************************************************************************
 函 数 名  : At_GHpaMsgProc
 功能描述  : 对GDSP回复消息的处理
 输入参数  : pstMsg - 消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年6月28日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  At_GHPAMsgProc(
    MsgBlock                            *pstMsg
)
{
    HPA_AT_HEADER_STRU         *pHeader;

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_HpaMsgProc: pstMsg is NULL");
        return;
    }

    pHeader = (HPA_AT_HEADER_STRU *)pstMsg;

    switch (pHeader->usMsgID)
    {
        case ID_GHPA_AT_RF_MSG_CNF:
            At_HpaRfCfgCnfProc((HPA_AT_RF_CFG_CNF_STRU *)pstMsg);
            break;

        case ID_GHPA_AT_RF_RX_RSSI_IND:
            At_RfRssiIndProc((HPA_AT_RF_RX_RSSI_IND_STRU *)pstMsg);
            break;

        case ID_AT_GPHY_RF_PLL_STATUS_CNF:
            At_RfPllStatusCnfProc((PHY_AT_RF_PLL_STATUS_CNF_STRU *)pstMsg);
            break;

        case ID_HPA_AT_MIPI_WR_CNF:
            At_MipiWrCnfProc((HPA_AT_MIPI_WR_CNF_STRU *)pstMsg);
            break;

        case ID_HPA_AT_MIPI_RD_CNF:
            At_MipiRdCnfProc((HPA_AT_MIPI_RD_CNF_STRU *)pstMsg);
            break;

        case ID_HPA_AT_SSI_WR_CNF:
            At_SsiWrCnfProc((HPA_AT_SSI_WR_CNF_STRU *)pstMsg);
            break;

        case ID_HPA_AT_SSI_RD_CNF:
            At_SsiRdCnfProc((HPA_AT_SSI_RD_CNF_STRU *)pstMsg);
            break;

        default:
            AT_WARN_LOG("At_HpaMsgProc: ulMsgName is Abnormal!");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_FormatAtiCmdQryString
 功能描述  : 生成ATI命令查询信息字符串
 输入参数  : MODEM_ID_ENUM_UINT16                enModemId
             DRV_AGENT_MSID_QRY_CNF_STRU         *pstDrvAgentMsidQryCnf
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : o00132663
    修改内容   : 新生成函数
  2.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2013年3月4日
    作    者   : l60609
    修改内容   : DSDA PHASE III
  4.日    期   : 2013年5月20日
    作    者   : Y00213812
    修改内容   : 读取AT保存的IMEI号码
*****************************************************************************/
VOS_UINT32 AT_FormatAtiCmdQryString(
    MODEM_ID_ENUM_UINT16                enModemId,
    DRV_AGENT_MSID_QRY_CNF_STRU        *pstDrvAgentMsidQryCnf
)
{
    TAF_PH_MEINFO_STRU                  stMeInfo;
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           aucTmp[AT_MAX_VERSION_LEN];
    VOS_UINT32                          ulI;
    VOS_UINT8                           ucCheckData;

    /* 初始化 */
    usDataLen     = 0;
    ulI           = 0;
    ucCheckData   = 0;
    PS_MEM_SET(&stMeInfo, 0, sizeof(TAF_PH_MEINFO_STRU));


    PS_MEM_SET(aucTmp, 0x00, sizeof(aucTmp));

    /* 读取Model信息 */
    if ( (VOS_NULL_PTR == pstDrvAgentMsidQryCnf)
      || (DRV_AGENT_MSID_QRY_NO_ERROR != pstDrvAgentMsidQryCnf->ulResult))
    {
        return AT_ERROR;
    }

    /* 读取Manufacturer信息 */
    usDataLen = TAF_MAX_MFR_ID_LEN + 1;
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_FMRID, aucTmp, usDataLen))
    {
        AT_WARN_LOG("AT_FormatAtiCmdQryString:WARNING:NVIM Read en_NV_Item_FMRID falied!");
        return AT_ERROR;
    }
    else
    {
        PS_MEM_CPY(stMeInfo.FmrId.aucMfrId, aucTmp, usDataLen);
    }

    /* 读取IMEI信息 */
    for (ulI = 0; ulI < TAF_PH_IMEI_LEN; ulI++)
    {
        stMeInfo.ImeisV.aucImei[ulI] = pstDrvAgentMsidQryCnf->aucImei[ulI] + 0x30;
    }

    for (ulI = 0; ulI < (TAF_PH_IMEI_LEN - 2); ulI += 2)
    {
        ucCheckData += (TAF_UINT8)(((pstDrvAgentMsidQryCnf->aucImei[ulI])
                       +((pstDrvAgentMsidQryCnf->aucImei[ulI + 1UL] * 2) / 10))
                       +((pstDrvAgentMsidQryCnf->aucImei[ulI + 1UL] * 2) % 10));
    }
    ucCheckData = (10 - (ucCheckData%10)) % 10;

    stMeInfo.ImeisV.aucImei[TAF_PH_IMEI_LEN - 2] = ucCheckData + 0x30;
    stMeInfo.ImeisV.aucImei[TAF_PH_IMEI_LEN - 1] = 0;

    /* 输出ATI命令返回结果 */
    usDataLen = 0;
    usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s: %s\r\n","Manufacturer",stMeInfo.FmrId.aucMfrId);
    usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s: %s\r\n","Model",  pstDrvAgentMsidQryCnf->acModelId);
    usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s: %s\r\n","Revision",pstDrvAgentMsidQryCnf->acSoftwareVerId);
    usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s: %s\r\n","IMEI",stMeInfo.ImeisV.aucImei);
    usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s","+GCAP: +CGSM,+DS,+ES");

    gstAtSendData.usBufLen = usDataLen;

    return AT_OK;

}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentMsidQryCnf
 功能描述  : DRV_AGENT_MSID_QRY_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : o00132663
    修改内容   : 新生成函数
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题
  3.日    期   : 2013年3月4日
    作    者   : l60609
    修改内容   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentMsidQryCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_MSID_QRY_CNF_STRU        *pstDrvAgentMsidQryCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRet;

    enModemId = MODEM_ID_0;

    /* 初始化 */
    pRcvMsg               = (DRV_AGENT_MSG_STRU *)pMsg;
    pstDrvAgentMsidQryCnf = (DRV_AGENT_MSID_QRY_CNF_STRU *)(pRcvMsg->aucContent);

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstDrvAgentMsidQryCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentMsidQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentMsidQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_MSID_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);
        ulResult = AT_FormatAtiCmdQryString(enModemId, pstDrvAgentMsidQryCnf);
    }
    else if (AT_CMD_CGMM_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       "%s",
                                                       pstDrvAgentMsidQryCnf->acModelId);
        ulResult = AT_OK;
    }
    else if (AT_CMD_CGMR_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       "%s",
                                                       pstDrvAgentMsidQryCnf->acSoftwareVerId);
        ulResult = AT_OK;
    }
    else
    {
        return VOS_ERR;
    }

    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("At_SetImeiPara: Get modem id fail.");
        return VOS_ERR;
    }


    if (AT_ERROR == ulResult)
    {
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
    }
    else
    {
        At_FormatResultData(ucIndex, AT_OK);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentGasMntnCmdRsp
 功能描述  : DRV_AGENT_GAS_MNTN_CMD_RSP消息处理函数
 输入参数  : VOS_VOID *pMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : o00132663
    修改内容   : 新生成函数
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentGasMntnCmdRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_GAS_MNTN_CMD_CNF_STRU    *pstDrvAgentGasMntnCmdCnf;
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    VOS_UINT16                          usLength;

    /* 初始化 */
    pRcvMsg                  = (DRV_AGENT_MSG_STRU *)pMsg;
    pstDrvAgentGasMntnCmdCnf = (DRV_AGENT_GAS_MNTN_CMD_CNF_STRU *)(pRcvMsg->aucContent);
    ulResult                 = AT_OK;
    usLength                 = 0;
    j                        = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstDrvAgentGasMntnCmdCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentGasMntnCmdRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentGasMntnCmdRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_CGAS_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^CGAS命令返回 */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstDrvAgentGasMntnCmdCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        /* 邻区状态 */
        if (GAS_AT_CMD_NCELL == pstDrvAgentGasMntnCmdCnf->ucCmd)
        {
            if ((pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum > 0)
             &&((pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum%3) == 0))
            {
                for (i = 0; i< (pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum/3); i++)
                {
                    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                       "%d:%d,",
                                                       (i+1),
                                                       pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[j++]);
                    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                       "0x%X,",
                                                       pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[j++]&0xff);
                    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                       "%d\r\n",
                                                       pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[j++]);
                }
                gstAtSendData.usBufLen = usLength;
            }
            else if (0 == pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum)
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                   "0");
                gstAtSendData.usBufLen = usLength;
            }
            else
            {
                ulResult = AT_ERROR;
            }
        }
        else if (GAS_AT_CMD_SCELL == pstDrvAgentGasMntnCmdCnf->ucCmd)
        {
            /* 服务小区状态 */
            if (3 != pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum)
            {
                ulResult = AT_ERROR;
            }
            else
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                   "%d,",
                                                   pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[0]);
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                   "0x%X,",
                                                   pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[1]&0xff);
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                   "%d",
                                                   pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[2]);
                gstAtSendData.usBufLen = usLength;
                ulResult = AT_OK;
            }
        }
        else if (pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum > 0)
        {
            /* 其它命令 */
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                               "%d",
                                               pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[0]);

            for (i = 1; i< pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum ;i++)
            {
                usLength +=(TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                  (TAF_CHAR *)pgucAtSndCodeAddr,
                                                  (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                  ",%d",
                                                  pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[i]);
            }
            gstAtSendData.usBufLen = usLength;
        }
        else
        {

        }
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentHardwareQryRsp
 功能描述  : DRV_AGENT_HARDWARE_QRY_RSP消息处理函数
 输入参数  : VOS_VOID *pMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : c00173809
    修改内容   : 新生成函数
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentHardwareQryRsp(VOS_VOID *pMsg)
{
    VOS_UINT32                                  ulRet;
    TAF_UINT16                                  usLength;
    VOS_UINT8                                   ucIndex;
    DRV_AGENT_MSG_STRU                         *pRcvMsg;
    DRV_AGENT_HARDWARE_QRY_CNF_STRU            *pHardWareCnf;

    /* 初始化 */
    pRcvMsg      = (DRV_AGENT_MSG_STRU*)pMsg;
    pHardWareCnf = (DRV_AGENT_HARDWARE_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pHardWareCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentHardwareQryRsp: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentHardwareQryRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    if (AT_CMD_DRV_AGENT_HARDWARE_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    usLength               = 0;
    gstAtSendData.usBufLen = 0;

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ( DRV_AGENT_NO_ERROR == pHardWareCnf->ulResult )
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s:",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "\"%s\"",
                                           pHardWareCnf->aucHwVer);

        gstAtSendData.usBufLen = usLength;
        ulRet                  = AT_OK;
    }
    else
    {
        ulRet                  = AT_ERROR;
    }

    At_FormatResultData(ucIndex, ulRet);

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentVertimeQryRsp
 功能描述  : DRV_AGENT_VERTIME_QRY_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : o00132663
    修改内容   : 新生成函数
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentVertimeQryRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_VERSION_TIME_STRU        *pstDrvAgentVersionTime;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    pRcvMsg                     = (DRV_AGENT_MSG_STRU *)pMsg;
    pstDrvAgentVersionTime      = (DRV_AGENT_VERSION_TIME_STRU *)(pRcvMsg->aucContent);
    ulResult                    = AT_OK;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstDrvAgentVersionTime->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentVertimeQryRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentVertimeQryRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_VERSIONTIME_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^VERTIME命令返回 */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%s",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstDrvAgentVersionTime->aucData);

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentYjcxSetCnf
 功能描述  : DRV_AGENT_YJCX_SET_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : o00132663
    修改内容   : 新生成函数
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentYjcxSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_YJCX_SET_CNF_STRU            *pstYjcxSetCnf;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    VOS_UINT16                              usDataLen;

    /* 初始化 */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstYjcxSetCnf   = (DRV_AGENT_YJCX_SET_CNF_STRU *)(pRcvMsg->aucContent);
    ulResult        = AT_OK;
    usDataLen       = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstYjcxSetCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentYjcxSetCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentYjcxSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_YJCX_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^YJCX设置命令返回 */
    gstAtSendData.usBufLen = 0;
    if (VOS_OK != pstYjcxSetCnf->ulResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        usDataLen =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR*)pgucAtSndCodeAddr,
                                            "%s: ",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,
                                            "%s",
                                            pstYjcxSetCnf->aucflashInfo);
        gstAtSendData.usBufLen = usDataLen;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentYjcxQryCnf
 功能描述  : DRV_AGENT_YJCX_QRY_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : o00132663
    修改内容   : 新生成函数
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentYjcxQryCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_YJCX_QRY_CNF_STRU            *pstYjcxQryCnf;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    VOS_UINT16                              usDataLen;

    /* 初始化 */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstYjcxQryCnf   = (DRV_AGENT_YJCX_QRY_CNF_STRU *)(pRcvMsg->aucContent);
    ulResult        = AT_OK;
    usDataLen       = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstYjcxQryCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentYjcxQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentYjcxQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_YJCX_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^YJCX查询命令返回 */
    gstAtSendData.usBufLen = 0;
    if (VOS_OK != pstYjcxQryCnf->ulResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        usDataLen =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR*)pgucAtSndCodeAddr,
                                            "%s: ",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,
                                            "%s",
                                            pstYjcxQryCnf->aucgpioInfo);

        gstAtSendData.usBufLen = usDataLen;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : At_QryEonsUcs2RspProc
 功能描述  : AT口输出EONSUCS2查询结果
 输入参数  : VOS_VOID                            ucIndex - AT 通道
             VOS_UINT8                           OpId
             VOS_UINT32                          ulResult
             TAF_MMA_EONS_UCS2_PLMN_NAME_STRU    stEonsUcs2PlmnName
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年03月12日
    作    者   : c00318887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID At_QryEonsUcs2RspProc(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucOpId,
    VOS_UINT32                          ulResult,
    TAF_MMA_EONS_UCS2_PLMN_NAME_STRU   *stEonsUcs2PlmnName
)
{
    TAF_MMA_EONS_UCS2_PLMN_NAME_STRU   *pstPlmnName = VOS_NULL_PTR;
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulLoop;

    /* 变量初始化 */
    pstPlmnName = (TAF_MMA_EONS_UCS2_PLMN_NAME_STRU *)stEonsUcs2PlmnName;

    if (VOS_NULL_PTR == pstPlmnName)
    {
        return;
    }

    /* 转换LongName及ShortName */
    if ( pstPlmnName->ucLongNameLen <= TAF_PH_OPER_NAME_LONG
      && pstPlmnName->ucShortNameLen <= TAF_PH_OPER_NAME_SHORT )
    {

        /* ^EONSUCS2:<long name>,<short name> */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s:",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        for (ulLoop = 0; ulLoop < pstPlmnName->ucLongNameLen; ulLoop++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%02X",
                                               pstPlmnName->aucLongName[ulLoop]);
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr + usLength, ",");

        for (ulLoop = 0; ulLoop < pstPlmnName->ucShortNameLen; ulLoop++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%02X",
                                               pstPlmnName->aucShortName[ulLoop]);
        }

        gstAtSendData.usBufLen = usLength;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
    }

    At_FormatResultData(ucIndex,ulResult);

    return;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaEonsUcs2Cnf
 功能描述  : AT_RcvMmaEonsUcs2Cnf 消息处理函数
 输入参数  : VOS_VOID *pMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年03月12日
    作    者   : c00318887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvMmaEonsUcs2Cnf(VOS_VOID *pMsg)
{
    TAF_MMA_EONS_UCS2_CNF_STRU         *pstEonsUcs2QryCnfMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    pstEonsUcs2QryCnfMsg    = (TAF_MMA_EONS_UCS2_CNF_STRU *)pMsg;
    ulResult                = AT_OK;

    if (VOS_NULL_PTR == pstEonsUcs2QryCnfMsg)
    {
        AT_WARN_LOG("AT_RcvMmaCrpnQueryRsp:MSG IS NULL!");
        return VOS_ERR;
    }

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstEonsUcs2QryCnfMsg->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCrpnQueryRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaEonsUcs2Cnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_EONSUCS2_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^EONSUCS2查询命令返回 */
    if (TAF_ERR_NO_ERROR != pstEonsUcs2QryCnfMsg->enRslt)
    {
        ulResult = At_ChgTafErrorCode(ucIndex, (VOS_UINT16)pstEonsUcs2QryCnfMsg->enErrorCause);

        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex,ulResult);
        return VOS_OK;
    }

    At_QryEonsUcs2RspProc(ucIndex,
                    pstEonsUcs2QryCnfMsg->ucOpId,
                    ulResult,
                    &pstEonsUcs2QryCnfMsg->stEonsUcs2PlmnName);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvAtMmaUsimStatusInd
 功能描述  : AT_RcvMmaCrpnQueryRsp消息处理函数
 输入参数  : VOS_VOID *pMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : o00132663
    修改内容   : 新生成函数
  2.日    期   : 2012年12月24日
    作    者   : l60609
    修改内容   : DSDA Phase II
*****************************************************************************/
VOS_UINT32 AT_RcvAtMmaUsimStatusInd(VOS_VOID *pMsg)
{
    AT_MMA_USIM_STATUS_IND_STRU        *pstAtMmaUsimStatusIndMsg;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_USIM_INFO_CTX_STRU              *pstUsimInfoCtx = VOS_NULL_PTR;

    /* 初始化 */
    pstAtMmaUsimStatusIndMsg   = (AT_MMA_USIM_STATUS_IND_STRU *)pMsg;

    enModemId = AT_GetModemIDFromPid(pstAtMmaUsimStatusIndMsg->ulSenderPid);

    if (enModemId >= MODEM_ID_BUTT)
    {
#if (VOS_OS_VER == VOS_LINUX)
        printk(KERN_ERR "\n AT_RcvAtMmaUsimStatusInd: enModemId :%d , ulSenderPid :%d\n", enModemId, pstAtMmaUsimStatusIndMsg->ulSenderPid);
#endif

        return VOS_ERR;
    }

    pstUsimInfoCtx = AT_GetUsimInfoCtxFromModemId(enModemId);

    /* 刷新卡状态全局变量 */
    pstUsimInfoCtx->enCardType   = pstAtMmaUsimStatusIndMsg->enCardType;
    pstUsimInfoCtx->enCardStatus = pstAtMmaUsimStatusIndMsg->enCardStatus;
    pstUsimInfoCtx->ucIMSILen    = pstAtMmaUsimStatusIndMsg->ucIMSILen;
    PS_MEM_CPY(pstUsimInfoCtx->aucIMSI, pstAtMmaUsimStatusIndMsg->aucIMSI, NAS_MAX_IMSI_LENGTH);

#if (VOS_OS_VER == VOS_LINUX)
    printk(KERN_ERR "\nAT_RcvAtMmaUsimStatusInd: CardType: %d , CardStatus: %d , ulSenderPid: %d\n",
           pstAtMmaUsimStatusIndMsg->enCardType, pstAtMmaUsimStatusIndMsg->enCardStatus, pstAtMmaUsimStatusIndMsg->ulSenderPid);
#endif

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : At_RcvAtCcMsgStateQryCnfProc
 功能描述  : AT_CC_MSG_STATE_QRY_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : o00132663
    修改内容   : 新生成函数
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题

*****************************************************************************/
VOS_UINT32 At_RcvAtCcMsgStateQryCnfProc(VOS_VOID *pMsg)
{
    AT_CC_STATE_QRY_CNF_MSG_STRU           *pstAtCcStateQryCnfMsg;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              i;
    VOS_UINT16                              usLength;

    /* 初始化 */
    pstAtCcStateQryCnfMsg = (AT_CC_STATE_QRY_CNF_MSG_STRU *)pMsg;
    ulResult              = AT_OK;
    usLength              = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstAtCcStateQryCnfMsg->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("At_RcvAtCcMsgStateQryCnfProc:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvAtCcMsgStateQryCnfProc : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    /* 当前未等待该命令回复 */
    if (AT_CMD_CC_STATE_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^CCC查询命令返回 */
    gstAtSendData.usBufLen = 0;
    if (0 == pstAtCcStateQryCnfMsg->ucCallNum)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
        for ( i = 0 ; i < pstAtCcStateQryCnfMsg->ucCallNum ; i++ )
        {
            AT_ShowCccRst(&pstAtCcStateQryCnfMsg->astCcStateInfoList[i],&usLength);
        }

        if (0 == usLength)
        {
            ulResult = AT_ERROR;
        }
    }

    /* 输出结果 */
    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaCmmSetCmdRsp
 功能描述  : AT_MMA_CMM_SET_CMD_RSP消息处理函数
 输入参数  : VOS_VOID *pMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : o00132663
    修改内容   : 新生成函数
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题

*****************************************************************************/
VOS_UINT32 AT_RcvMmaCmmSetCmdRsp(VOS_VOID *pMsg)
{
    TAF_MMA_CMM_SET_CNF_STRU           *pstMnMmTestCmdRspMsg;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          i;
    VOS_UINT16                          usLength;

    /* 初始化 */
    pstMnMmTestCmdRspMsg = (TAF_MMA_CMM_SET_CNF_STRU *)pMsg;
    ulResult              = AT_OK;
    usLength              = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMnMmTestCmdRspMsg->stCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCmmSetCmdRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCmmSetCmdRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^CMM查询命令返回 */
    gstAtSendData.usBufLen = 0;
    if (VOS_OK != pstMnMmTestCmdRspMsg->ulResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        if (pstMnMmTestCmdRspMsg->stAtCmdRslt.ulRsltNum > 0)
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR*)pgucAtSndCodeAddr+usLength,
                                               "%d",
                                               pstMnMmTestCmdRspMsg->stAtCmdRslt.aulRslt[0]);

            for (i = 1; i< pstMnMmTestCmdRspMsg->stAtCmdRslt.ulRsltNum ;i++)
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR*)pgucAtSndCodeAddr+usLength,
                                                   ",%d",
                                                   pstMnMmTestCmdRspMsg->stAtCmdRslt.aulRslt[i]);
            }
            gstAtSendData.usBufLen = usLength;
        }
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentFullHardwareQryRsp
 功能描述  : DRV_AGENT_FULL_HARDWARE_QRY_RSP消息处理函数
 输入参数  : VOS_VOID *pMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : c00173809
    修改内容   : 新生成函数
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentFullHardwareQryRsp(VOS_VOID *pMsg)
{
    TAF_UINT16                                       usLength;
    VOS_UINT8                                        ucIndex;
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_FULL_HARDWARE_QRY_CNF_STRU            *pstEvent;

    /* 初始化 */
    pRcvMsg  = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent = (DRV_AGENT_FULL_HARDWARE_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentFullHardwareQryRsp: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentFullHardwareQryRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    if (AT_CMD_DRV_AGENT_FULL_HARDWARE_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    usLength               = 0;
    gstAtSendData.usBufLen = 0;

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s:",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "\"%s ",
                                           pstEvent->aucModelId);

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s,",
                                           pstEvent->aucRevisionId);

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s\"",
                                           pstEvent->aucHwVer);

        gstAtSendData.usBufLen = usLength;

        At_FormatResultData(ucIndex, AT_OK);
    }
    else
    {
        At_FormatResultData(ucIndex, AT_ERROR);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : At_SendRfCfgAntSelToHPA
 功能描述  : 在接收机打开后,进行分集主集切换时需重新发送配置请求给HPA
 输入参数  : ucDivOrPriOn - 要测量分集还是主集
 输出参数  : 无
 返 回 值  : 返回发送结果，AT_FAILURE:发送失败；AT_SUCCESS:发送成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月29日
    作    者   : z00161729
    修改内容   : 新生成函数
 2.日    期   : 2011年10月18日
   作    者   : c00173809
   修改内容   : AT Project,该函数从AtSetParaCmd.c移到该文件
*****************************************************************************/
VOS_UINT32 At_SendRfCfgAntSelToHPA(VOS_UINT8 ucDivOrPriOn)
{
    AT_HPA_RF_CFG_REQ_STRU              *pstMsg;
    VOS_UINT32                           ulLength;
    VOS_UINT16                           usMask;

    /* 申请AT_HPA_RF_CFG_REQ_STRU消息 */
    ulLength = sizeof(AT_HPA_RF_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (AT_HPA_RF_CFG_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_SendRfCfgAntSelToHPA: alloc msg fail!");
        return AT_FAILURE;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(AT_HPA_RF_CFG_REQ_STRU));

    /* Modified by L00171473 for DTS2012010901510 DSP PID更正, 2012-01-07, begin */

    /* 填写消息头 */
    pstMsg->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid        = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid      = DSP_PID_WPHY;
    pstMsg->ulLength           = ulLength;

    /* Modified by L00171473 for DTS2012010901510 DSP PID更正, 2012-01-07, end */

    /* 填写消息体 */
    pstMsg->usMsgID            = ID_AT_HPA_RF_CFG_REQ;
    usMask                     = W_RF_MASK_RX_ARFCN | W_RF_MASK_RX_ANTSEL \
                                 | W_RF_MASK_RX_RXONOFF;

    /* 按位标识配置类型 */
    pstMsg->stRfCfgPara.usMask = usMask;

    if (AT_RX_DIV_ON == ucDivOrPriOn)
    {
        pstMsg->stRfCfgPara.usRxAntSel = ANT_TWO;
        pstMsg->stRfCfgPara.usRxEnable = DSP_CTRL_RX_ALL_ANT_ON;
    }
    else
    {
        pstMsg->stRfCfgPara.usRxAntSel = ANT_ONE;
        pstMsg->stRfCfgPara.usRxEnable = DSP_CTRL_RX_ANT1_ON;
    }

    pstMsg->stRfCfgPara.usRxBand       = g_stAtDevCmdCtrl.stDspBandArfcn.usDspBand;
    pstMsg->stRfCfgPara.usRxFreqNum    = g_stAtDevCmdCtrl.stDspBandArfcn.usDlArfcn;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("At_SendRfCfgAntSelToHPA: Send msg fail!");
        return AT_FAILURE;
    }

    return AT_SUCCESS;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentSetSimlockCnf
 功能描述  : DRV_AGENT_SIMLOCK_SET_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月3日
    作    者   : c00173809
    修改内容   : 新生成函数
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题
  3.日    期   : 2012年2月20日
    作    者   : l60609
    修改内容   : B060 Prj:SIMLOCK安全检查放在C核处理
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentSetSimlockCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_SET_SIMLOCK_CNF_STRU                  *pstEvent;
    VOS_UINT32                                       ulRet;
    VOS_UINT8                                        ucIndex;

    /* 初始化 */
    pRcvMsg  = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent = (DRV_AGENT_SET_SIMLOCK_CNF_STRU *)pRcvMsg->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetSimlockCnf: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetSimlockCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    if (AT_CMD_DRV_AGENT_SIMLOCK_SET_REQ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {
        ulRet = AT_OK;
    }
    else
    {
        ulRet = AT_ERROR;
    }

    At_FormatResultData(ucIndex, ulRet);

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentQryRxdivCnf
 功能描述  : DRV_AGENT_RXDIV_QRY_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月22日
    作    者   : c00173809
    修改内容   : 新生成函数
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentQryRxdivCnf(VOS_VOID *pMsg)
{
    VOS_UINT32                                       ulRet;
    VOS_UINT8                                        ucIndex;
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_QRY_RXDIV_CNF_STRU                    *pstEvent;
    VOS_UINT32                                       ulUserDivBandsLow;
    VOS_UINT32                                       ulUserDivBandsHigh;
    VOS_UINT32                                       ulDrvDivBandsLow;
    VOS_UINT32                                       ulDrvDivBandsHigh;
    VOS_UINT16                                       usLen;

    /* 初始化 */
    pRcvMsg  = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent = (DRV_AGENT_QRY_RXDIV_CNF_STRU *)pRcvMsg->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryRxdivCnf: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryRxdivCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    if (AT_CMD_DRV_AGENT_RXDIV_QRY_REQ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    usLen                  = 0;
    gstAtSendData.usBufLen = 0;

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {
        At_CovertMsInternalRxDivParaToUserSet(pstEvent->usDrvDivBands,
                                             &ulDrvDivBandsLow,
                                             &ulDrvDivBandsHigh);
        At_CovertMsInternalRxDivParaToUserSet(pstEvent->usCurBandSwitch,
                                             &ulUserDivBandsLow,
                                             &ulUserDivBandsHigh);

        usLen +=  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                         (TAF_CHAR *)pgucAtSndCodeAddr,
                                         (TAF_CHAR*)pgucAtSndCodeAddr,
                                         "%s:",
                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        if (0 != ulDrvDivBandsHigh)
        {
            usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                            "%d,%X%08X,",
                                            0,
                                            ulDrvDivBandsHigh,ulDrvDivBandsLow);
        }
        else
        {
            usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                            "%d,%X,",
                                            0,
                                            ulDrvDivBandsLow);
        }

        if (0 != ulUserDivBandsHigh)
        {
            usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                            "%X%08X",
                                            ulUserDivBandsHigh,
                                            ulUserDivBandsLow);
        }
        else
        {
            usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                            "%X",
                                            ulUserDivBandsLow);
        }
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                        "\r\n");
        usLen +=  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                         (TAF_CHAR *)pgucAtSndCodeAddr,
                                         (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                         "%s:",
                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                        "%d,%X,%X",
                                        1,
                                        0,
                                        0);
        gstAtSendData.usBufLen = usLen;

        ulRet = AT_OK;
    }
    else
    {
        ulRet = AT_CME_UNKNOWN;
    }

    At_FormatResultData(ucIndex, ulRet);

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentSetRxdivCnf
 功能描述  : DRV_AGENT_RXDIV_SET_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : c00173809
    修改内容   : 新生成函数
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题
  3.日    期   : 2012年1月16日
    作    者   : f62575
    修改内容   : SMALL IMAGE特性合入: V3R1规格变更同步
                                接收机没有打开情况下，禁止用户设置分集接收
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentSetRxdivCnf(VOS_VOID *pMsg)
{
    VOS_UINT8                                        ucIndex;
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_AT_RXDIV_CNF_STRU                     *pstEvent;

    /* 初始化 */
    pRcvMsg  = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent = (DRV_AGENT_AT_RXDIV_CNF_STRU *)pRcvMsg->aucContent;


    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetRxdivCnf: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetRxdivCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    if (AT_CMD_DRV_AGENT_RXDIV_SET_REQ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    if( DRV_AGENT_CME_RX_DIV_OTHER_ERR == pstEvent->ulResult )
    {
        gstAtSendData.usBufLen = 0;

        AT_STOP_TIMER_CMD_READY(ucIndex);

        At_FormatResultData(ucIndex, AT_CME_RX_DIV_OTHER_ERR);

        return VOS_ERR;
    }

    if( DRV_AGENT_CME_RX_DIV_NOT_SUPPORTED == pstEvent->ulResult )
    {
        gstAtSendData.usBufLen = 0;

        AT_STOP_TIMER_CMD_READY(ucIndex);

        At_FormatResultData(ucIndex, AT_CME_RX_DIV_NOT_SUPPORTED);

        return VOS_ERR;
    }

    if( AT_DSP_RF_SWITCH_ON == pstEvent->ucRxOnOff )
    {
        if( DRV_AGENT_CME_RX_DIV_BAND_ERR == pstEvent->ulResult )
        {
            gstAtSendData.usBufLen = 0;

            AT_STOP_TIMER_CMD_READY(ucIndex);

            At_FormatResultData(ucIndex, AT_CME_RX_DIV_NOT_SUPPORTED);

            return VOS_ERR;
        }

        if (AT_FAILURE == At_SendRfCfgAntSelToHPA(AT_RX_DIV_ON))
        {
            gstAtSendData.usBufLen = 0;

            AT_STOP_TIMER_CMD_READY(ucIndex);

            At_FormatResultData(ucIndex, AT_CME_RX_DIV_OTHER_ERR);

            return VOS_ERR;
        }

        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SET_RXDIV;
        g_stAtDevCmdCtrl.ucIndex               = ucIndex;
        g_stAtDevCmdCtrl.usOrigBand            = pstEvent->usSetDivBands;

        /* 返回命令处理挂起状态 */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        gstAtSendData.usBufLen = 0;

        AT_STOP_TIMER_CMD_READY(ucIndex);

        At_FormatResultData(ucIndex, AT_ERROR);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentSetNvRestoreCnf
 功能描述  : DRV_AGENT_NVRESTORE_SET_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月03日
    作    者   : f00179208
    修改内容   : 新生成函数
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentSetNvRestoreCnf(VOS_VOID *pMsg)
{
    VOS_UINT8                                        ucIndex;
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_NVRESTORE_RST_STRU                *pstEvent;

    /* 初始化 */
    pRcvMsg                 = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent                = (DRV_AGENT_NVRESTORE_RST_STRU *)pRcvMsg->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetNvRestoreCnf: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetNvRestoreCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    if (AT_CMD_NVRESTORE_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%d",
                                                    pstEvent->ulResult);

    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentQryNvRestoreRstCnf
 功能描述  : DRV_AGENT_NVRSTSTTS_QRY_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月03日
    作    者   : f00179208
    修改内容   : 新生成函数
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题
  3.日    期   : 2011年12月1日
    作    者   : z60575
    修改内容   : DTS2012071704644，工具不识别OK
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentQryNvRestoreRstCnf(VOS_VOID *pMsg)
{
    VOS_UINT8                                        ucIndex;
    VOS_UINT32                                       ulRestoreStatus;
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_NVRESTORE_RST_STRU                    *pstEvent;

    /* 初始化 */
    pRcvMsg                 = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent                = (DRV_AGENT_NVRESTORE_RST_STRU *)pRcvMsg->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryNvRestoreRstCnf: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryNvRestoreRstCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    if (AT_CMD_NVRSTSTTS_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ((AT_NV_RESTORE_RESULT_INIT == pstEvent->ulResult)
     || (AT_NV_RESTORE_RUNNING == pstEvent->ulResult))
    {
        ulRestoreStatus = AT_NV_RESTORE_FAIL;
    }
    else if (VOS_OK == pstEvent->ulResult)
    {
        ulRestoreStatus = AT_NV_RESTORE_SUCCESS;
    }
    else
    {
        ulRestoreStatus = AT_NV_RESTORE_FAIL;
    }
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%d",
                                                     ulRestoreStatus);

    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentNvRestoreManuDefaultRsp
 功能描述  : DRV_AGENT_NVRESTORE_MANU_DEFAULT_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月04日
    作    者   : f00179208
    修改内容   : 新生成函数
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentNvRestoreManuDefaultRsp(VOS_VOID *pMsg)
{
    VOS_UINT8                                        ucIndex;
    VOS_UINT32                                       ulRst;
    VOS_UINT32                                       ulResult;
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_NVRESTORE_RST_STRU                    *pstEvent;

    /* 初始化 */
    pRcvMsg                 = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent                = (DRV_AGENT_NVRESTORE_RST_STRU *)pRcvMsg->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentNvRestoreManuDefaultRsp: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentNvRestoreManuDefaultRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    if (AT_CMD_F_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    ulResult = pstEvent->ulResult;
    if ( NV_OK != ulResult )
    {
        ulRst = AT_ERROR;
    }
    else
    {
        g_bSetFlg = VOS_TRUE;

        /* E5通知APP恢复用户设置  */
        AT_PhSendRestoreFactParm();

        ulRst = AT_OK;
    }
    At_FormatResultData(ucIndex, ulRst);

    return VOS_OK;

}


/*****************************************************************************
 函 数 名  : AT_GetImeiValue
 功能描述  : ^PHYNUM 读取NV项获取IMEI
 输入参数  : MODEM_ID_ENUM_UINT16                enModemId,
             VOS_UINT8 aucImei[TAF_PH_IMEI_LEN + 1]
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月3日
    作    者   : w00181244
    修改内容   : 新生成函数
  2.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2013年3月4日
    作    者   : l60609
    修改内容   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32  AT_GetImeiValue(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           aucImei[TAF_PH_IMEI_LEN + 1]
)
{
    NV_SC_PERS_CTRL_STRU                    stScPersCtrl;
    VOS_UINT8                               aucBuf[TAF_PH_IMEI_LEN + 1];
    VOS_UINT8                               ucCheckData;
    VOS_UINT32                              ulDataLen;
    VOS_UINT32                              i;

    ucCheckData = 0;
    ulDataLen   = TAF_PH_IMEI_LEN;


    PS_MEM_SET(aucBuf, 0x00, sizeof(aucBuf));

    PS_MEM_SET(&stScPersCtrl, 0x00, sizeof(NV_SC_PERS_CTRL_STRU));

    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_IMEI, aucBuf, ulDataLen))
    {
        AT_WARN_LOG("TAF_GetImeiValue:Read IMEI Failed!");
        return VOS_ERR;
    }

#if (3 == MULTI_MODEM_NUMBER)
#if (VOS_WIN32 != VOS_OS_VER)
    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_NV_SC_PERS_CTRL_CFG, &stScPersCtrl, sizeof(stScPersCtrl)))
    {
        AT_WARN_LOG("TAF_GetImeiValue:Read en_NV_Item_NV_SC_PERS_CTRL_CFG Failed!");
        return VOS_ERR;
    }

    /* NV 4008读取值为0x5a5a表示生效，其他值表示不生效 */
    if ((MODEM_ID_2 == enModemId)
     && (0x5A5A == stScPersCtrl.usImei0ReplaseImei2))
    {
        /* IMEI all zero */
        for (i = 0; i < ulDataLen; i++)
        {
            if (0 != aucBuf[i])
            {
                break;
            }
        }

        if (i >= ulDataLen)
        {
            PS_MEM_SET(aucBuf, 0x00, sizeof(aucBuf));

            if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_IMEI, aucBuf, ulDataLen))
            {
                AT_WARN_LOG("TAF_GetImeiValue:Read IMEI Failed!");
                return VOS_ERR;
            }
        }
    }
#endif
#endif

    ucCheckData = 0;
    for (i = 0; i < (TAF_PH_IMEI_LEN-2); i += 2)
    {
        ucCheckData += aucBuf[i]
                      +((aucBuf[i+1UL] + aucBuf[i+1UL])/10)
                      +((aucBuf[i+1UL] + aucBuf[i+1UL])%10);
    }
    ucCheckData = (10 - (ucCheckData%10))%10;
    AT_DeciDigit2Ascii(aucBuf, (VOS_UINT8)ulDataLen, aucImei);
    aucImei[TAF_PH_IMEI_LEN-2] = ucCheckData+0x30;
    aucImei[TAF_PH_IMEI_LEN-1] = 0;

    return VOS_OK;
}



/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentSetGpioplRsp
 功能描述  : 设置GPIO各管脚电平的回复处理
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : w00181244
    修改内容   : 新生成函数
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentSetGpioplRsp(VOS_VOID *pMsg)
{

    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_GPIOPL_SET_CNF_STRU      *pstDrvAgentGpioSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pRcvMsg               = (DRV_AGENT_MSG_STRU *)pMsg;
    pstDrvAgentGpioSetCnf = (DRV_AGENT_GPIOPL_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstDrvAgentGpioSetCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentGpioplRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentGpioplRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    if (AT_CMD_GPIOPL_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_TRUE == pstDrvAgentGpioSetCnf->bFail)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* 调用AT_FormATResultDATa发送命令结果 */
    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}



/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentQryGpioplRsp
 功能描述  : 查询GPIO管教电平回复的处理
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月15日
    作    者   : w00181244
    修改内容   : 新生成函数
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentQryGpioplRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                   *pRcvMsg;
    DRV_AGENT_GPIOPL_QRY_CNF_STRU        *pstGpioQryCnf;
    VOS_UINT16                            usLength;
    VOS_UINT32                            i;
    VOS_UINT8                             ucIndex;
    VOS_UINT32                            ulResult;

    /* 初始化消息，获取ucContent */
    pRcvMsg               = (DRV_AGENT_MSG_STRU *)pMsg;
    pstGpioQryCnf         = (DRV_AGENT_GPIOPL_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstGpioQryCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryGpioplRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryGpioplRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    /* 判断当前操作类型是否为AT_CMD_GPIOPL_QRY */
    if (AT_CMD_GPIOPL_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /*复位AT状态*/
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_TRUE != pstGpioQryCnf->bFail)
    {
        /* 打印结果 */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s:", g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        for (i = 0; i < DRVAGENT_GPIOPL_MAX_LEN; i++)
        {
           usLength += (VOS_UINT16)At_sprintf (AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                               "%02X", pstGpioQryCnf->aucGpiopl[i]);
        }

        gstAtSendData.usBufLen = usLength;
        ulResult               = AT_OK;
    }
    else
    {
        /* 调用AT_FormATResultDATa发送命令结果 */
        gstAtSendData.usBufLen = 0;
        ulResult               = AT_ERROR;
    }
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentSetDatalockRsp
 功能描述  : dATalock设置函数回复的处理
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月15日
    作    者   : w00181244
    修改内容   : 新生成函数
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentSetDatalockRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_DATALOCK_SET_CNF_STRU    *pstDatalockSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* 初始化 */
    pRcvMsg                   = (DRV_AGENT_MSG_STRU *)pMsg;
    pstDatalockSetCnf         = (DRV_AGENT_DATALOCK_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstDatalockSetCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetDatalockRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetDatalockRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    /* 判断当前操作类型是否为AT_CMD_DATALOCK_SET */
    if (AT_CMD_DATALOCK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_TRUE != pstDatalockSetCnf->bFail)
    {
        /* 设置dATalock已解锁 */
        g_bAtDataLocked    =  VOS_FALSE;
        ulResult           =  AT_OK;
    }
    else
    {
        ulResult           =  AT_ERROR;
    }

    /* 调用AT_FormAtResultData发送命令结果  */
    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
 }

/*****************************************************************************
 函 数 名  : AT_GetSimLockStatus
 功能描述  : AT^SIMLOCK使能状态查询命令,
                对于硬加密改制版本，
                补充文件保存密码校验结果更新en_NV_Item_CardlockStatus流程，
                其他场景仍然读取en_NV_Item_CardlockStatus状态，
                不等于永久解锁，            且en_NV_Item_CustomizeSimLockPlmnInfo中Plmn信息,
                有效时返回1,代             表激活,
                其他情况下返回0,非激活;
              密码校验操作需要在C核完成，此处改用异步处理过程
 输入参数  :ucIndex --- 用户索引
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : w00181244
    修改内容   : 新生成函数
  2.日    期   : 2012年02月3日
    作    者   : f62575
    修改内容   : B050 SIMLOCK命令的硬加密改制功能: 因为通过密码校验更新锁卡状态必须在C核完成，
                 修改为异步处理
*****************************************************************************/
VOS_UINT32 AT_GetSimLockStatus(VOS_UINT8 ucIndex)
{

    /* 发消息到C核获取SIMLOCK 状态信息 */
    if(TAF_SUCCESS != Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId, 0,
                                    TAF_PH_SIMLOCK_VALUE_PARA, VOS_NULL_PTR))
    {
        AT_WARN_LOG("AT_GetSimLockStatus: Taf_ParaQuery fail.");
        return VOS_ERR;
    }

    /* ^SIMLOCK=2查询UE的锁卡状态不在AT命令处理的主流程，需要本地启动保护定时器并更新端口状态 */
    if (AT_SUCCESS != At_StartTimer(AT_SET_PARA_TIME, ucIndex))
    {
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_ERR;
    }

    /* 设置AT模块实体的状态为等待异步返回 */
    gastAtClientTab[ucIndex].CmdCurrentOpt   = AT_CMD_SIMLOCKSTATUS_READ;

    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentQryTbatvoltRsp
 功能描述  : 电池电压查询回复处理
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月15日
    作    者   : w00181244
    修改内容   : 新生成函数
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentQryTbatvoltRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_TBATVOLT_QRY_CNF_STRU    *pstTbatvoltQryCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* 初始化 */
    pRcvMsg                   = (DRV_AGENT_MSG_STRU *)pMsg;
    pstTbatvoltQryCnf         = (DRV_AGENT_TBATVOLT_QRY_CNF_STRU *)pRcvMsg->aucContent;


    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstTbatvoltQryCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryTbatvoltRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryTbatvoltRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    /*判断当前操作类型是否为AT_CMD_TBATVOLT_QRY*/
    if (AT_CMD_TBATVOLT_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 电池电压查询结果判断 */
    if (VOS_TRUE != pstTbatvoltQryCnf->bFail)
    {

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        "%s:%d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstTbatvoltQryCnf->lBatVol);
        ulResult = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
        ulResult = AT_ERROR;
    }

    /* 调用AT_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}

/* Added by f00179208 for AT Project，2011-10-06,  Begin */
/*****************************************************************************
函 数 名  : At_RcvVcMsgQryModeCnfProc
功能描述  : VC消息查询语音模式回复的处理函数
输入参数  : MN_AT_IND_EVT_STRU   *pstData
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修订记录  :
  1.日    期   : 2011年10月15日
    作    者   : f00179208
    修改内容   : 创建函数,处理AT命令的结果回复
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题
  3.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目
  4.日    期   : 2012年8月10日
    作    者   : y00213812
    修改内容   : DTS2012082204471, TQE清理，类型定义错误
  5.日    期   : 2013年10月08日
    作    者   : j00174725
    修改内容   : TQE
*****************************************************************************/
VOS_VOID At_RcvVcMsgQryModeCnfProc(MN_AT_IND_EVT_STRU *pstData)
{

    MN_AT_IND_EVT_STRU                  *pRcvMsg;
    APP_VC_EVENT_INFO_STRU              *pstEvent;
    VOS_UINT8                            ucIndex;
    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, begin*/
    VOS_UINT16                           usVoiceMode;
    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, end*/
    VOS_UINT16                           usDevMode;
    VOS_UINT32                           ulRet;


    /* 初始化 */
    pRcvMsg         = pstData;
    pstEvent        = (APP_VC_EVENT_INFO_STRU *)pstData->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryModeCnfProc:WARNING:AT INDEX NOT FOUND!");
        return;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryModeCnfProc : AT_BROADCAST_INDEX.");
        return;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    /* 格式化VMSET命令返回 */
    if (AT_CMD_VMSET_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        usDevMode = pstEvent->enDevMode;

        /* 无效的模式，直接返回ERROR */
        if (usDevMode >= VC_PHY_DEVICE_MODE_BUTT)
        {
            gstAtSendData.usBufLen = 0;
            ulRet = AT_ERROR;
        }
        else
        {
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            "%s: %d",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            usDevMode);
            ulRet = AT_OK;
        }
    }
    /* 格式化CVOICE命令返回 */
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    else if ( AT_CMD_CVOICE_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        /* 转换为应用于VC语音模式 */
        usVoiceMode     = APP_VC_VcPhyVoiceMode2AppVcVoiceMode(pstEvent->enDevMode);

        /* 无效的模式，直接返回ERROR */
        if (usVoiceMode >= APP_VC_VOICE_MODE_BUTT)
        {
            gstAtSendData.usBufLen = 0;
            ulRet = AT_ERROR;
        }
        else
        {
            gstAtSendData.usBufLen =(VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                                           "%s: %d, %d, %d, %d",
                                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                           usVoiceMode,
                                                           AT_PCVOICE_SAMPLE_RATE,
                                                           AT_PCVOICE_DATA_BIT,
                                                           AT_PCVOICE_FRAME_PERIOD);
            ulRet = AT_OK;
        }
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    else
    {
        return;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return;
}

/*****************************************************************************
函 数 名  : At_RcvVcMsgSetPortCnfProc
功能描述  : VC消息设置端口回复的处理函数
输入参数  : MN_AT_IND_EVT_STRU   *pstData
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修订记录  :
  1.日    期   : 2011年10月15日
    作    者   : f00179208
    修改内容   : 创建函数,处理AT命令的结果回复
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题
*****************************************************************************/
VOS_VOID At_RcvVcMsgSetPortCnfProc(MN_AT_IND_EVT_STRU *pstData)
{
    MN_AT_IND_EVT_STRU                 *pRcvMsg;
    APP_VC_EVENT_INFO_STRU             *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;

    /* 初始化 */
    pRcvMsg         = pstData;
    pstEvent        = (APP_VC_EVENT_INFO_STRU *)pstData->aucContent;


    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgSetPortCnfProc:WARNING:AT INDEX NOT FOUND!");
        return;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgSetPortCnfProc : AT_BROADCAST_INDEX.");
        return;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    if (VOS_TRUE == pstEvent->bSuccess)
    {
        ulRet = AT_OK;
    }
    else
    {
        ulRet = AT_ERROR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return;

}

/*****************************************************************************
函 数 名  : At_RcvVcMsgQryPortCnfProc
功能描述  : VC消息设置端口回复的处理函数
输入参数  : MN_AT_IND_EVT_STRU   *pstData
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修订记录  :
1.  日    期   : 2011年10月17日
    作    者   : f00179208
    修改内容   : 创建函数,处理AT命令的结果回复
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题
*****************************************************************************/
VOS_VOID At_RcvVcMsgQryPortCnfProc(MN_AT_IND_EVT_STRU *pstData)
{
    MN_AT_IND_EVT_STRU                  *pRcvMsg;
    APP_VC_EVENT_INFO_STRU              *pstEvent;
    VOS_UINT8                            ucIndex;
    APP_VC_VOICE_PORT_ENUM_U8            ucVoicePort;                           /* 语音设备端口号 */
    VOS_UINT32                           ulRet;

    /* 初始化 */
    pRcvMsg         = pstData;
    pstEvent        = (APP_VC_EVENT_INFO_STRU *)pstData->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryPortCnfProc:WARNING:AT INDEX NOT FOUND!");
        return;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryPortCnfProc : AT_BROADCAST_INDEX.");
        return;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    /* 查询的端口号 */
    ucVoicePort = pstEvent->enVoicePort;

    if (APP_VC_VOICE_PORT_BUTT > ucVoicePort)
    {
        gstAtSendData.usBufLen =
            (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                   "%s: %d",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                   ucVoicePort);
        ulRet = AT_OK;
    }
    else
    {
        ulRet = AT_ERROR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return;

}
/* Added by f00179208 for AT Project，2011-10-06,  End */

/*****************************************************************************
 函 数 名  : At_RcvRnicMsgDsflowRspProc
 功能描述  : 处理RNIC发来的流量统计指示
 输入参数  : MsgBlock   *pstData
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_OK, VOS_ERR
 调用函数  :
 被调函数  :

 修订记录  :
 1.日    期   : 2011年12月15日
   作    者   : f00179208
   修改内容   : 创建函数,处理RNIC的消息
*****************************************************************************/
VOS_UINT32 AT_RcvRnicDsflowRsp(MsgBlock *pstMsg)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    RNIC_DATA_RATE_STRU                 stCurrentRateInfo;
    RNIC_AT_DSFLOW_RSP_STRU            *pstRcvMsg;

    usLength                            = 0;
    pstRcvMsg                           = (RNIC_AT_DSFLOW_RSP_STRU *)pstMsg;
    stCurrentRateInfo.ulULDataRate      = pstRcvMsg->stRnicDataRate.ulULDataRate;
    stCurrentRateInfo.ulDLDataRate      = pstRcvMsg->stRnicDataRate.ulDLDataRate;

    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryPortCnfProc:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryPortCnfProc : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    usLength =  (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d",
                                       stCurrentRateInfo.ulULDataRate);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       ",%d",
                                       stCurrentRateInfo.ulDLDataRate);

    gstAtSendData.usBufLen = usLength;

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : AT_RcvRnicDialModeCnf
 功能描述  : 处理RNIC发来的拨号模式查询请求
 输入参数  : MsgBlock   *pstData
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_OK, VOS_ERR
 调用函数  :
 被调函数  :

 修订记录  :
 1.日    期   : 2011年12月21日
   作    者   : f00179208
   修改内容   : 创建函数,处理RNIC的消息
*****************************************************************************/
VOS_UINT32 AT_RcvRnicDialModeCnf(MsgBlock *pstMsg)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    RNIC_AT_DIAL_MODE_CNF_STRU         *pstRcvMsg;

    usLength                            = 0;
    pstRcvMsg                           = (RNIC_AT_DIAL_MODE_CNF_STRU *)pstMsg;

    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->clientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvRnicDialModeCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvRnicDialModeCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    usLength =  (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR*)pgucAtSndCodeAddr,
                                        "%s:",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "%d",
                                        pstRcvMsg->ulDialMode);

    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        ",%d",
                                        pstRcvMsg->ulEventReportFlag);

    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                         ",%d",
                                         pstRcvMsg->ulIdleTime);

    gstAtSendData.usBufLen = usLength;

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}

/*****************************************************************************
 Prototype      : At_ZeroReplaceBlankInString
 Description    : 将第二空格替换成0
 Input          : pData --- 字符串
                  pLen  --- 长度
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2011-07-08
    Author      : f00179208
    Modification: Created function for DTS2011070803450

  2.日    期   : 2011年10月22日
    作    者   : w00181244
    修改内容   : 从 V3R1移植过来
*****************************************************************************/
VOS_VOID At_ZeroReplaceBlankInString( VOS_UINT8 *pData, VOS_UINT32 ulLen)
{
    TAF_UINT32 ulChkLen  = 0;
    TAF_UINT8  *pWrite   = pData;
    TAF_UINT8  *pRead    = pData;

    /* 输入参数检查 */
    while ( ulChkLen < ulLen )
    {
        /* 时间格式 May  5 2011 17:08:00
           转换成   May 05 2011 17:08:00 */
        if (' ' == *pRead++)
        {
            if (' ' == *pRead)
            {
                pWrite++;
                *pWrite = '0';
                pRead++;
                ulChkLen++;
            }
        }
        pWrite++;
        ulChkLen++;
    }

    return;
}


/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentQryVersionRsp
 功能描述  : version查询结果处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月6日
    作    者   : w00181244
    修改内容   : 新生成函数
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题
  3.日    期   : 2012年04月19日
    作    者   : f62575
    修改内容   : V7代码同步:  默认值值按版本区分，输出保持不变
  4.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  5.日    期   : 2013年3月4日
    作    者   : L60609
    修改内容   : DSDA PHASE III
  6.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentQryVersionRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_VERSION_QRY_CNF_STRU     *pstVersionQryCnfInfo;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulLen;
    VOS_CHAR                            acTmpTime[AT_AGENT_DRV_VERSION_TIME_LEN] = {0};
    VOS_UINT16                          usLength;
    VOS_BOOL                            bPhyNumIsNull;

    VOS_UINT32                          ulOpt;
    /* Modify by f62575 for V7代码同步, 2012-04-07, Begin   */
    VOS_UINT32                          ulRet;
    TAF_NVIM_CS_VER_STRU                stCsver;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;

    stCsver.usCsver = 0;

    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_Csver, &(stCsver.usCsver), sizeof(stCsver.usCsver));
    if (NV_OK != ulRet)
    {
        return AT_ERROR;
    }
    /* Modify by f62575 for V7代码同步, 2012-04-07, End   */

    /* 初始化消息，获取ucContent */
    ulLen                        = 0;
    pRcvMsg                      = (DRV_AGENT_MSG_STRU *)pMsg;
    pstVersionQryCnfInfo         = (DRV_AGENT_VERSION_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstVersionQryCnfInfo->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryVersionRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryVersionRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    /* 判断当前操作类型是否为AT_CMD_VERSION_QRY/AT_CMD_RSFR_VERSION_QRY, ^RSFR命令也借用此接口 */
    if ((AT_CMD_VERSION_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
        && (AT_CMD_RSFR_VERSION_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt))
    {
        return VOS_ERR;
    }

    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RcvDrvAgentQryVersionRsp: Get modem id fail.");
        return VOS_ERR;
    }

    ulOpt = gastAtClientTab[ucIndex].CmdCurrentOpt;

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /*查询出错 */
    if(DRV_AGENT_VERSION_QRY_NO_ERROR != pstVersionQryCnfInfo->enResult)
    {
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_OK;
    }

    /*版本编译时间格式转换，将时间戳中连续两个空格的后一个空格用0替换 */
    ulLen = VOS_StrLen(pstVersionQryCnfInfo->acVerTime);
    PS_MEM_CPY(acTmpTime, pstVersionQryCnfInfo->acVerTime, ulLen + 1);
    At_ZeroReplaceBlankInString((VOS_UINT8 *)acTmpTime, ulLen);

    /* 字符串预解析 */
    usLength = TAF_CDROM_VERSION_LEN;
    At_DelCtlAndBlankCharWithEndPadding(pstVersionQryCnfInfo->stIsoVer.aucIsoInfo, &usLength);

    /* 获取物理号是否为空的标识 */
    if (AT_OK != AT_PhyNumIsNull(enModemId, AT_PHYNUM_TYPE_IMEI, &bPhyNumIsNull))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryVersionRsp(): AT_PhyNumIsNull Error!");
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_OK;
    }

    usLength = 0;

    /* 内部版本号在单板未写入物理号前，查询需如实显示；写入物理号后，如查询版本号前未
       输入解锁指令，内部版本号显示为空，如果已经输入解锁指令，内部版本号如实显示 */
    if (VOS_FALSE == g_bAtDataLocked || (VOS_TRUE == bPhyNumIsNull))
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:BDT:%s%s",
                                           "^VERSION", acTmpTime, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTS:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stSoftVersion.aucRevisionId, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTS:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stSoftVersion.aucRevisionId, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTD:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stIsoVer.aucIsoInfo, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTD:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stIsoVer.aucIsoInfo,gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTH:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stInterHwVer.aucHwVer, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTH:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stFullHwVer.aucHwVer, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTU:%s%s",
                                           "^VERSION",pstVersionQryCnfInfo->stModelId.aucModelId, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTU:%s%s",
                                           "^VERSION",pstVersionQryCnfInfo->stInterModelId.aucModelId, gaucAtCrLf);

        /* Modify by f62575 for V7代码同步, 2012-04-07, Begin   */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:CFG:%d%s",
                                           "^VERSION",stCsver.usCsver, gaucAtCrLf);
        /* Modify by f62575 for V7代码同步, 2012-04-07, End   */

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:PRL:",
                                           "^VERSION");

        gstAtSendData.usBufLen = usLength;
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:BDT:%s%s",
                                           "^VERSION", acTmpTime, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTS:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stSoftVersion.aucRevisionId, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTS:%s",
                                           "^VERSION", gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTD:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stIsoVer.aucIsoInfo, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTD:%s",
                                           "^VERSION", gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTH:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stInterHwVer.aucHwVer, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTH:%s",
                                           "^VERSION", gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTU:%s%s",
                                           "^VERSION",pstVersionQryCnfInfo->stModelId.aucModelId, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTU:%s",
                                           "^VERSION", gaucAtCrLf);

        /* Modify by f62575 for V7代码同步, 2012-04-07, Begin   */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:CFG:%d%s",
                                           "^VERSION",stCsver.usCsver, gaucAtCrLf);
        /* Modify by f62575 for V7代码同步, 2012-04-07, End   */

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:PRL:",
                                           "^VERSION");

        gstAtSendData.usBufLen = usLength;
    }

    /* 如果是^RSFR命令发起的查询VERSION信息的请求,则由^RSFR命令去处理 */
    if(AT_CMD_RSFR_VERSION_QRY == ulOpt)
    {
        AT_SetRsfrVersionCnf(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

        /* AT返回的字符串在AT_SetRsfrVersionCnf中处理 */
        return VOS_OK;
    }

    At_FormatResultData(ucIndex, AT_OK);
    return VOS_OK;

}


/*****************************************************************************
 函 数 名  : AT_SetGlobalFchan
 功能描述  : 设置装备全局变量的接入模式
 输入参数  : VOS_UINT8 ucRATMode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月13日
    作    者   : w00181244
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetGlobalFchan(VOS_UINT8 ucRATMode)
{
    g_stAtDevCmdCtrl.ucDeviceRatMode = ucRATMode;

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_SetFchanRspErr
 功能描述  : Fchan错误码返回
 输入参数  : AT_AGENT_FCHAN_SET_ERROR_ENUM_UINT32  enResult
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : w00181244
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetFchanRspErr(DRV_AGENT_FCHAN_SET_ERROR_ENUM_UINT32  enResult)
{
    if(DRV_AGENT_FCHAN_BAND_NOT_MATCH == enResult)
    {
        return AT_FCHAN_BAND_NOT_MATCH;
    }

    if(DRV_AGENT_FCHAN_BAND_CHANNEL_NOT_MATCH == enResult)
    {
        return AT_FCHAN_BAND_CHANNEL_NOT_MATCH;
    }

    if(DRV_AGENT_FCHAN_OTHER_ERR == enResult)
    {
        g_stAtDevCmdCtrl.bDspLoadFlag = VOS_FALSE;
        AT_WARN_LOG("AT_SetFChanPara: DSP Load fail!");
        return AT_FCHAN_OTHER_ERR;
    }

    return DRV_AGENT_FCHAN_SET_NO_ERROR;

}


/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentSetFchanRsp
 功能描述  : Fchan设置函数回复处理
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : w00181244
    修改内容   : 新生成函数
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentSetFchanRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_FCHAN_SET_CNF_STRU       *pstFchanSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulError;

    /* 初始化 */
    pRcvMsg          = (DRV_AGENT_MSG_STRU *)pMsg;
    pstFchanSetCnf   = (DRV_AGENT_FCHAN_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstFchanSetCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetFchanRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetFchanRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    /* 判断当前操作类型是否为AT_CMD_FCHAN_SET */
    if (AT_CMD_FCHAN_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 设置有错误的处理 */
    ulError =  AT_SetFchanRspErr(pstFchanSetCnf->enResult);
    if(DRV_AGENT_FCHAN_SET_NO_ERROR != ulError)
    {
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, ulError);
        return VOS_OK;
    }

    /* 设置无错误的处理 */
    g_stAtDevCmdCtrl.bDspLoadFlag    = VOS_TRUE;
    g_stAtDevCmdCtrl.ucDeviceRatMode = (VOS_UINT8)pstFchanSetCnf->stFchanSetReq.ucDeviceRatMode;
    g_stAtDevCmdCtrl.ucDeviceAtBand  = (VOS_UINT8)pstFchanSetCnf->stFchanSetReq.ucDeviceAtBand;
    g_stAtDevCmdCtrl.stDspBandArfcn  = pstFchanSetCnf->stFchanSetReq.stDspBandArfcn;
    g_stAtDevCmdCtrl.usFDAC          = 0;                                       /* FDAC清零，防止G/W范围错误 */

    /* 调用AT_FormATResultDATa发送命令结果 */
    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex,AT_OK);
    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_GetRxpriErr
 功能描述  : Rxpri设置函数回复错误码处理
 输入参数  : AT_AGENT_RXPRI_SET_ERROR_ENUM_UINT32 enResult
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : w00181244
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_GetRxpriErr(DRV_AGENT_ERROR_ENUM_UINT32 enResult)
{
    if(DRV_AGENT_CME_RX_DIV_OTHER_ERR == enResult)
    {
        return AT_CME_RX_DIV_OTHER_ERR;
    }

    if(DRV_AGENT_CME_RX_DIV_NOT_SUPPORTED == enResult)
    {
        return AT_CME_RX_DIV_NOT_SUPPORTED;
    }

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : AT_SupportHsdpa
 功能描述  : ^SFEATURE查询单板是否支持DPA特性
 输入参数  : AT_UE_CAPA_STRU                    *pstUECapa
 输出参数  :*pbSupportHsdpa
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : w00181244
    修改内容   : 新生成函数
  2.日    期   : 2012年5月18日
    作    者   : z60575
    修改内容   : DTS2012051806821，读取接入层能力NV项修改，入参结构修改
*****************************************************************************/
VOS_VOID AT_SupportHsdpa(
    AT_NVIM_UE_CAPA_STRU               *pstUECapa,
    VOS_BOOL                           *pbSupportHsdpa
    )
{

    /* 初始化为不支持DPA */
    *pbSupportHsdpa = VOS_FALSE;

    if (pstUECapa->enAsRelIndicator >= 2)
    {
        if (1 == pstUECapa->ulHspaStatus)
        {
            if (PS_TRUE == pstUECapa->enHSDSCHSupport)
            {
                *pbSupportHsdpa = VOS_TRUE;
            }
        }
        else
        {
            *pbSupportHsdpa = VOS_TRUE;
        }
    }
}


/*****************************************************************************
 函 数 名  : AT_SupportHsupa
 功能描述  : ^SFEATURE查询单板是否支持UPA特性
 输入参数  : AT_UE_CAPA_STRU                    *pstUECapa
 输出参数  :*pbSupportHsupa
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : w00181244
    修改内容   : 新生成函数
  2.日    期   : 2012年5月18日
    作    者   : z60575
    修改内容   : DTS2012051806821，读取接入层能力NV项修改，入参结构修改
*****************************************************************************/
VOS_VOID AT_SupportHsupa(
    AT_NVIM_UE_CAPA_STRU               *pstUECapa,
    VOS_BOOL                           *pbSupportHsupa
)
{

    /* 初始化为不支持UPA */
    *pbSupportHsupa = VOS_FALSE;

    if (pstUECapa->enAsRelIndicator >= 3)
    {
       if (1 == pstUECapa->ulHspaStatus)
       {
           if (PS_TRUE == pstUECapa->enEDCHSupport)
           {
               *pbSupportHsupa = VOS_TRUE;
           }
       }
       else
       {
            *pbSupportHsupa = VOS_TRUE;
       }
    }
}

/*****************************************************************************
 函 数 名  : AT_GetWFeatureInfo
 功能描述  : ^SFEATURE查询单板3G特性
 输入参数  : AT_AGENT_SFEATURE_QRY_CNF_STRU *pstATAgentSfeATureQryCnf

 输出参数  :AT_FEATURE_SUPPORT_ST  *pstFeATure,
            VOS_UINT8               aucStrTmp[50]
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月13日
    作    者   : w00181244
    修改内容   : 新生成函数
  2.日    期   : 2012年5月15日
    作    者   : f62575
    修改内容   : DTS2012051400682，支持UMTS分集频段的输出
  3.日    期   : 2012年5月18日
    作    者   : z60575
    修改内容   : DTS2012051806821，读取接入层能力NV项修改
  4.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  5. 日    期   : 2012年11月12日
     作    者   : t00212959
     修改内容   : DTS2012103101740,MMA中Band结构改为VOS_UINT32,AT保持一致
*****************************************************************************/
VOS_UINT32 AT_GetWFeatureInfo(
    AT_FEATURE_SUPPORT_ST              *pstFeATure,
    DRV_AGENT_SFEATURE_QRY_CNF_STRU    *pstAtAgentSfeatureQryCnf
)
{
    AT_NVIM_UE_CAPA_STRU                stUECapa;
    VOS_UINT32                          ulLen;
    VOS_BOOL                            bSupportHsdpa;
    VOS_BOOL                            bSupportHsupa;
    VOS_UINT8                           aucStrTmp[50] = {0};
    VOS_UINT8                           aucStrDiv[AT_SFEATURE_DIV_STRING_LEN];
    VOS_UINT32                          ulDivLen;


    bSupportHsdpa = VOS_FALSE;
    bSupportHsupa = VOS_FALSE;

    PS_MEM_SET(&stUECapa, 0x00, sizeof(stUECapa));


    /* 读取HSPA,HSPA+支持能力 */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_WAS_RadioAccess_Capa_New, &stUECapa,
                        sizeof(AT_NVIM_UE_CAPA_STRU)))
    {
        AT_WARN_LOG("AT_GetWFeatureInfo: en_NV_Item_WAS_RadioAccess_Capa NV Read  Fail!");
        PS_MEM_FREE(WUEPS_PID_AT, pstFeATure);
        return VOS_ERR;
    }

    /* 获取Wcdma频段信息 */
    /* !!!如果增加频段，aucStrTmp 长度需要增加!!! */
    ulLen = (VOS_UINT32)AT_GetWcdmaBandStr(aucStrTmp,&(pstAtAgentSfeatureQryCnf->stBandFeature));

    /* HSPA+是否支持 */
    if ((stUECapa.enAsRelIndicator >= 4)
     && (PS_TRUE == stUECapa.enMacEhsSupport)
     && (stUECapa.ucHSDSCHPhyCategory >= 10)
     && (0 != stUECapa.ucHSDSCHPhyCategoryExt)
     && (PS_TRUE == stUECapa.enHSDSCHSupport))
     {
        pstFeATure[AT_FEATURE_HSPAPLUS].ucFeatureFlag = AT_FEATURE_EXIST;
        VOS_MemCpy(pstFeATure[AT_FEATURE_HSPAPLUS].aucContent, aucStrTmp, ulLen);
     }

    /* DPA是否支持 */
    AT_SupportHsdpa(&stUECapa, &bSupportHsdpa);
    if (VOS_TRUE == bSupportHsdpa)
    {
        pstFeATure[AT_FEATURE_HSDPA].ucFeatureFlag = AT_FEATURE_EXIST;
        VOS_MemCpy(pstFeATure[AT_FEATURE_HSDPA].aucContent, aucStrTmp, ulLen);
    }

    /*UPA是否支持*/
    AT_SupportHsupa(&stUECapa, &bSupportHsupa);
    if(VOS_TRUE == bSupportHsupa)
    {
        pstFeATure[AT_FEATURE_HSUPA].ucFeatureFlag = AT_FEATURE_EXIST;
        VOS_MemCpy(pstFeATure[AT_FEATURE_HSUPA].aucContent, aucStrTmp, ulLen);
    }


    /* 分集信息 */
    pstFeATure[AT_FEATURE_DIVERSITY].ucFeatureFlag = AT_FEATURE_EXIST;
    /* UMTS的分集信息输出*/
    PS_MEM_SET(aucStrDiv, 0x00, sizeof(aucStrDiv));

    /* !!!如果增加频段，aucStrDiv 长度需要增加!!! */
    ulDivLen = (VOS_UINT32)AT_GetWcdmaDivBandStr(aucStrDiv);

    VOS_MemCpy(pstFeATure[AT_FEATURE_DIVERSITY].aucContent, aucStrDiv, ulDivLen);

    /* UMTS */
    pstFeATure[AT_FEATURE_UMTS].ucFeatureFlag = AT_FEATURE_EXIST;
    VOS_MemCpy(pstFeATure[AT_FEATURE_UMTS].aucContent, aucStrTmp, ulLen);

    return VOS_OK;

}


/*****************************************************************************
 函 数 名  : AT_GetGFeatureInfo
 功能描述  : ^SFEATURE查询单板2G特性
 输入参数  : AT_AGENT_SFEATURE_QRY_CNF_STRU *pstATAgentSfeATureQryCnf

 输出参数  :AT_FEATURE_SUPPORT_ST  *pstFeATure,
            VOS_UINT8               aucStrTmp[50]
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月13日
    作    者   : w00181244
    修改内容   : 新生成函数
  2.日    期   : 2012年02月10日
    作    者   : l00171473
    修改内容   : 单板不支持G时，SFEATURE修改
  3.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  4.日    期   : 2012年11月12日
    作    者   : t00212959
    修改内容   : DTS2012103101740,MMA中Band结构改为VOS_UINT32,AT保持一致
*****************************************************************************/
VOS_VOID AT_GetGFeatureInfo(
    AT_FEATURE_SUPPORT_ST              *pstFeATure,
    DRV_AGENT_SFEATURE_QRY_CNF_STRU    *pstATAgentSfeatureQryCnf
)
{
    VOS_UINT32                          ulLen;

    VOS_UINT16                          usEgprsFlag;
    VOS_UINT8                           aucStrTmp[50] = {0};


    usEgprsFlag = 0;


    /* 获取GSM频段信息 */
    /* !!!如果增加频段，aucStrDiv 长度需要增加!!! */
    ulLen = (VOS_UINT32)AT_GetGsmBandStr(aucStrTmp,&(pstATAgentSfeatureQryCnf->stBandFeature));

    /* Modified by l00171473 for 单板不支持G时SFEATURE修改, 2012-02-10, begin */
    if ( 0 == ulLen )
    {
        (VOS_VOID)vos_printf("AT_GetGFeatureInfo, Not Support G.\n");
        return;
    }
    /* Modified by l00171473 for 单板不支持G时SFEATURE修改, 2012-02-10, end */

    /* 读取EDGE支持能力 */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_Egprs_Flag, &usEgprsFlag,
                        sizeof(VOS_UINT16)))
    {
        AT_WARN_LOG("AT_GetGFeatureInfo: en_NV_Item_Egprs_Flag NV Read  Fail!");
        pstFeATure[AT_FEATURE_EDGE].ucFeatureFlag = AT_FEATURE_EXIST;
        VOS_MemCpy(pstFeATure[AT_FEATURE_EDGE].aucContent, aucStrTmp, ulLen);
    }
    else
    {
        if (usEgprsFlag != 0)
        {
            pstFeATure[AT_FEATURE_EDGE].ucFeatureFlag = AT_FEATURE_EXIST;
            VOS_MemCpy(pstFeATure[AT_FEATURE_EDGE].aucContent, aucStrTmp, ulLen);
        }
    }

    /* GPRS */
    pstFeATure[AT_FEATURE_GPRS].ucFeatureFlag = AT_FEATURE_EXIST;
    VOS_MemCpy(pstFeATure[AT_FEATURE_GPRS].aucContent, aucStrTmp, ulLen);

    /* GSM */
    pstFeATure[AT_FEATURE_GSM].ucFeatureFlag = AT_FEATURE_EXIST;
    VOS_MemCpy(pstFeATure[AT_FEATURE_GSM].aucContent, aucStrTmp, ulLen);
}

/*****************************************************************************
 函 数 名  : AT_GetTdsFeatureInfo
 功能描述  : ^SFEATURE查询单板TDS特性
 输入参数  : AT_FEATURE_SUPPORT_ST * pstFeATure
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月13日
    作    者   : z00212940
    修改内容   : 新生成函数
  2.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
#if(FEATURE_ON == FEATURE_UE_MODE_TDS)
VOS_UINT32 AT_GetTdsFeatureInfo(AT_FEATURE_SUPPORT_ST * pstFeATure)
{
    VOS_UINT32 ulRst  = 0;
    NVIM_UE_TDS_SUPPORT_FREQ_BAND_LIST_STRU stTdsFeature;
    VOS_UINT32 i = 0;
    VOS_UINT32 ulLen;


    PS_MEM_SET(&stTdsFeature, 0x00, sizeof(stTdsFeature));

    ulRst = NV_ReadEx(MODEM_ID_0, en_NV_Item_UTRAN_TDD_FREQ_BAND, &stTdsFeature, sizeof(NVIM_UE_TDS_SUPPORT_FREQ_BAND_LIST_STRU));
    if( ulRst != ERR_MSP_SUCCESS )
    {
        (VOS_VOID)vos_printf("Read EN_NV_ID_TDS_SUPPORT_FREQ_BAND failed:0x%x.\n", en_NV_Item_UTRAN_TDD_FREQ_BAND);
        return ERR_MSP_FAILURE;
    }
    if(stTdsFeature.ucBandCnt > NVIM_TDS_MAX_SUPPORT_BANDS_NUM)
    {
        (VOS_VOID)vos_printf("Read en_NV_Item_UTRAN_TDD_FREQ_BAND stTdsFeature.ucBandCnt:%d.\n", stTdsFeature.ucBandCnt);
        return ERR_MSP_FAILURE;
    }

    /* 读取NV成功，支持TDS */
    pstFeATure[AT_FEATURE_TDSCDMA].ucFeatureFlag = AT_FEATURE_EXIST;

    ulLen = 0;

    /* BandA:2000Hz, BanE:2300Hz, BandF:1900Hz */
    for(i = 0; i < stTdsFeature.ucBandCnt; i++)
    {
        if(ID_NVIM_TDS_FREQ_BAND_A == stTdsFeature.aucBandNo[i])
        {
            VOS_sprintf((VOS_CHAR*)(pstFeATure[AT_FEATURE_TDSCDMA].aucContent + ulLen), "2000,");
            ulLen = VOS_StrLen((VOS_CHAR *)pstFeATure[AT_FEATURE_TDSCDMA].aucContent);
            continue;
        }

        if(ID_NVIM_TDS_FREQ_BAND_E == stTdsFeature.aucBandNo[i])
        {
            VOS_sprintf((VOS_CHAR*)(pstFeATure[AT_FEATURE_TDSCDMA].aucContent + ulLen), "2300,");
            ulLen = VOS_StrLen((VOS_CHAR *)pstFeATure[AT_FEATURE_TDSCDMA].aucContent);
            continue;
        }

        if(ID_NVIM_TDS_FREQ_BAND_F == stTdsFeature.aucBandNo[i])
        {
            VOS_sprintf((VOS_CHAR*)(pstFeATure[AT_FEATURE_TDSCDMA].aucContent + ulLen), "1900,");
            ulLen = VOS_StrLen((VOS_CHAR *)pstFeATure[AT_FEATURE_TDSCDMA].aucContent);
            continue;
        }
    }

    if(ulLen > 0)
    {
        /* 屏蔽掉最后一个逗号 */
        pstFeATure[AT_FEATURE_TDSCDMA].aucContent[ulLen - 1] = '\0';
    }

    return ERR_MSP_SUCCESS;
}
#endif

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentQrySfeatureRsp
 功能描述  : ^SFEATURE查询结果处理及单板其它特性查询
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月13日
    作    者   : w00181244
    修改内容   : 新生成函数
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题
  3.日    期   : 2012年04月13日
    作    者   : f62575
    修改内容   : V7代码同步: 配合AT_GetLteFeatureInfo接口功能的更新
                    AT_GetLteFeatureInfo仅输出LTE支持的频段信息
  4.日    期   : 2012年11月12日
    作    者   : t00212959
    修改内容   : DTS2012103101740,MMA中Band结构改为VOS_UINT32,AT保持一致
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentQrySfeatureRsp(VOS_VOID *pMsg)
{
    /* 初始化 */
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_SFEATURE_QRY_CNF_STRU    *pstAtAgentSfeatureQryCnf;
    VOS_UINT8                           ucIndex;
    AT_FEATURE_SUPPORT_ST              *pstFeATure;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          ulReult;
    VOS_UINT8                           ucFeATrueNum;
    VOS_UINT8                           ucIndexTmp;
    VOS_UINT8                           aucFeATureName[][AT_FEATURE_NAME_LEN_MAX] =
                                        {
                                            "LTE",
                                            "HSPA+",
                                            "HSDPA",
                                            "HSUPA",
                                            "DIVERSITY",
                                            "UMTS",
                                            "EVDO",
                                            "EDGE",
                                            "GPRS",
                                            "GSM",
                                            "CDMA1X",
                                            "WIMAX",
                                            "WIFI",
                                            "GPS",
                                            "TD"
                                        };

    pRcvMsg                      = (DRV_AGENT_MSG_STRU*)pMsg;
    pstAtAgentSfeatureQryCnf     = (DRV_AGENT_SFEATURE_QRY_CNF_STRU*)pRcvMsg->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstAtAgentSfeatureQryCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQrySfeatureRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQrySfeatureRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    /*判断当前操作类型是否为AT_CMD_SFEATURE_QRY */
    if (AT_CMD_SFEATURE_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    pstFeATure = (AT_FEATURE_SUPPORT_ST*)PS_MEM_ALLOC(WUEPS_PID_AT, AT_FEATURE_MAX*sizeof(AT_FEATURE_SUPPORT_ST));
    if (VOS_NULL == pstFeATure)
    {
        AT_WARN_LOG("AT_RcvDrvAgentQrySfeatureRsp: GET MEM Fail!");
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_OK;
    }
    VOS_MemSet(pstFeATure, 0, AT_FEATURE_MAX*sizeof(AT_FEATURE_SUPPORT_ST));

    ulReult = AT_GetWFeatureInfo(pstFeATure,pstAtAgentSfeatureQryCnf);
    if (VOS_OK != ulReult)
    {
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
        PS_MEM_FREE(WUEPS_PID_AT, pstFeATure);
        return VOS_OK;
    }

/* Modify by f62575 for V7代码同步, 2012-04-07, Begin   */
#if(FEATURE_ON == FEATURE_LTE)
    ulReult = AT_GetLteFeatureInfo(pstFeATure);
    if (VOS_OK != ulReult)
    {
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
        PS_MEM_FREE(WUEPS_PID_AT, pstFeATure);
        return VOS_OK;
    }
#endif
/* Modify by f62575 for V7代码同步, 2012-04-07, End   */

#if(FEATURE_UE_MODE_TDS == FEATURE_ON)
    ulReult = AT_GetTdsFeatureInfo(pstFeATure);
    if (VOS_OK != ulReult)
    {
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
        PS_MEM_FREE(WUEPS_PID_AT, pstFeATure);
        return VOS_OK;
    }
#endif

    AT_GetGFeatureInfo(pstFeATure,pstAtAgentSfeatureQryCnf);

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    if (BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        /* WIFI */
        pstFeATure[AT_FEATURE_WIFI].ucFeatureFlag = AT_FEATURE_EXIST;
        VOS_sprintf((VOS_CHAR*)pstFeATure[AT_FEATURE_WIFI].aucContent, "B,G,N");
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */

    /* 计算支持特性的个数 */
    ucFeATrueNum = 0;
    for (ucIndexTmp = 0; ucIndexTmp < AT_FEATURE_MAX; ucIndexTmp++)
    {
        VOS_MemCpy(pstFeATure[ucIndexTmp].aucFeatureName, aucFeATureName[ucIndexTmp],sizeof(aucFeATureName[ucIndexTmp]));
        if (AT_FEATURE_EXIST == pstFeATure[ucIndexTmp].ucFeatureFlag)
        {
            ucFeATrueNum++;
        }
    }

    ulLen = 0;
    /* 打印输出支持的特性数 */
    ulLen = (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   (TAF_CHAR *)pgucAtSndCodeAddr + ulLen,
                                   "%s:%d%s",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                   ucFeATrueNum,
                                   gaucAtCrLf);

    /* 分行打印输出支持的特性 */
    for (ucIndexTmp = 0; ucIndexTmp < AT_FEATURE_MAX; ucIndexTmp++)
    {
        if (AT_FEATURE_EXIST == pstFeATure[ucIndexTmp].ucFeatureFlag)
        {
            ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + ulLen,
                                           "%s:%s,%s%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstFeATure[ucIndexTmp].aucFeatureName,
                                           pstFeATure[ucIndexTmp].aucContent,
                                           gaucAtCrLf);
        }
    }

    gstAtSendData.usBufLen = (VOS_UINT16)(ulLen - (VOS_UINT32)VOS_StrLen((VOS_CHAR*)gaucAtCrLf));

    At_FormatResultData(ucIndex, AT_OK);
    PS_MEM_FREE(WUEPS_PID_AT, pstFeATure);
    return VOS_OK;

}


/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentQryProdtypeRsp
 功能描述  : ^PRODTYPE查询回复处理
 输入参数  : VOS_VOID * pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月13日
    作    者   : w00181244
    修改内容   : 新生成函数
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentQryProdtypeRsp(VOS_VOID * pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_PRODTYPE_QRY_CNF_STRU    *stProdTypeCnf;
    VOS_UINT8                           ucIndex;

    /* 初始化消息 */
    pRcvMsg                  = (DRV_AGENT_MSG_STRU *)pMsg;
    stProdTypeCnf            = (DRV_AGENT_PRODTYPE_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(stProdTypeCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryProdtypeRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryProdtypeRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    /* 判断当前操作类型是否为AT_CMD_PRODTYPE_QRY */
    if (AT_CMD_PRODTYPE_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stProdTypeCnf->ulProdType);

    /* 调用AT_FormATResultDATa发送命令结果 */
    At_FormatResultData(ucIndex, AT_OK);
    return VOS_OK;
}

/* Added by L60609 for AT Project，2011-10-04,  Begin*/
/*****************************************************************************
 函 数 名  : At_ProcMsgFromDrvAgent
 功能描述  : At模块处理来自At Agent的消息
 输入参数  : DRV_AGENT_MSG_STRU *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID At_ProcMsgFromDrvAgent(DRV_AGENT_MSG_STRU *pMsg)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulMsgId;
    VOS_UINT32                          ulRst;

    /*从g_astDrvAgentMsgProcTab中获取消息个数*/
    ulMsgCnt = sizeof(g_astAtProcMsgFromDrvAgentTab)/sizeof(AT_PROC_MSG_FROM_DRV_AGENT_STRU);

    /*从消息包中获取MSG ID*/
    ulMsgId  = ((DRV_AGENT_MSG_STRU *)pMsg)->ulMsgId;

    /*g_astDrvAgentMsgProcTab查表，进行消息分发*/
    for (i = 0; i < ulMsgCnt; i++)
    {
        if (g_astAtProcMsgFromDrvAgentTab[i].ulMsgType == ulMsgId)
        {
            ulRst = g_astAtProcMsgFromDrvAgentTab[i].pProcMsgFunc(pMsg);

            if (VOS_ERR == ulRst)
            {
                AT_ERR_LOG("At_ProcMsgFromDrvAgent: Msg Proc Err!");
            }

            return;
        }
    }

    /*没有找到匹配的消息*/
    if (ulMsgCnt == i)
    {
        AT_ERR_LOG("At_ProcMsgFromDrvAgent: Msg Id is invalid!");
    }

    return;
}

/*****************************************************************************
 Prototype      : At_PB_Unicode2UnicodePrint
 Description    : Unicode到Unicode打印转换
 Input          : ucNumType--- 号码类型
                  pucDst   --- 目的字串
                  usDstLen --- 目的字串长度
                  pucSrc   --- 源字串
                  usSrcLen --- 源字串长度
 Output         :
 Return Value   : AT_XXX  --- ATC返回码
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.日    期 : 2007-03-27
    作    者 : h59254
    修改内容 : 问题单号:A32D09820(PC-Lint修改)
*****************************************************************************/
TAF_UINT32 At_PB_Unicode2UnicodePrint(TAF_UINT32 MaxLength,TAF_INT8 *headaddr,TAF_UINT8 *pucDst, TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen)
{
    TAF_UINT16 usLen    = 0;
    TAF_UINT16 usChkLen = 0;
    TAF_UINT8  ucHigh1  = 0;
    TAF_UINT8  ucHigh2  = 0;
    TAF_UINT8 *pWrite   = pucDst;
    TAF_UINT8 *pRead    = pucSrc;

    if(((TAF_UINT32)(pucDst - (TAF_UINT8 *)headaddr) + (2 * usSrcLen)) >= MaxLength)
    {
        AT_ERR_LOG("At_Unicode2UnicodePrint too long");
        return 0;
    }

    /* 扫完整个字串 */
    while( usChkLen < usSrcLen )
    {
        /* 第一个字节 */
        ucHigh1 = 0x0F & (*pRead >> 4);
        ucHigh2 = 0x0F & *pRead;

        if(0x09 >= ucHigh1)   /* 0-9 */
        {
            *pWrite++ = ucHigh1 + 0x30;
        }
        else if(0x0A <= ucHigh1)    /* A-F */
        {
            *pWrite++ = ucHigh1 + 0x37;
        }
        else
        {

        }

        if(0x09 >= ucHigh2)   /* 0-9 */
        {
            *pWrite++ = ucHigh2 + 0x30;
        }
        else if(0x0A <= ucHigh2)    /* A-F */
        {
            *pWrite++ = ucHigh2 + 0x37;
        }
        else
        {

        }

        /* 下一个字符 */
        usChkLen++;
        pRead++;


        usLen += 2;    /* 记录长度 */
    }

    return usLen;
}

/*****************************************************************************
 Prototype      : At_PbGsmFormatPrint
 Description    : 将GSM编码的高位清0输出
 Input          : usMaxLength 指pucDst的最大长度
                : pucSrc输入的码流
                : usSrcLen 输入码流的长度
 Output         : pucDst 输出的GSM码流
 Return Value   : 输出GSM码流的长度

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.Date        : 2011-01-19
    Author      : j00168360
    Modification: [电话本第二阶段] 更改函数名称，
*****************************************************************************/
TAF_UINT16 At_PbGsmFormatPrint(TAF_UINT16 usMaxLength,
                               TAF_UINT8  *pucDst,
                               TAF_UINT8  *pucSrc,
                               TAF_UINT16 usSrcLen)
{
    TAF_UINT32  i;

    if (usSrcLen > usMaxLength)
    {
        AT_ERR_LOG("At_PbGsmFormatPrint error: too long");

        return 0;
    }

    for (i = 0; i < usSrcLen; i++)
    {
        /* 将最高bit清零 */
        pucDst[i] = pucSrc[i] & AT_PB_GSM7_CODE_MAX_VALUE;
    }

    return usSrcLen;
}

/*****************************************************************************
 Prototype      : At_PbOneUnicodeToIra
 Description    : 将一个UCS2编码转换为IRA编码
 Input          : usUnicodeChar -- UCS2编码
 Output         : pucDst      -- 指向转换后字符
 Return Value   : AT_SUCCESS -- 转换成功
                  AT_FAILURE -- 转换失败

 History        :
  1.Date        : 2011-01-19
    Author      : j00168360
    Modification: [电话本第二阶段] Created function
*****************************************************************************/
TAF_UINT32 At_PbOneUnicodeToIra(TAF_UINT16 usUnicodeChar, TAF_UINT8 *pucDst)
{
    TAF_UINT16 usIndex;

    for(usIndex = 0; usIndex < AT_PB_IRA_MAX_NUM; usIndex++)
    {
        if(usUnicodeChar == g_astIraToUnicode[usIndex].usUnicode)
        {
            *pucDst = g_astIraToUnicode[usIndex].ucOctet;

            return AT_SUCCESS;
        }
    }

    /* 未找到UCS2对应的IRA编码 */
    AT_LOG1("At_PbOneUnicodeToIra error: no found [%x]",usUnicodeChar);

    return AT_FAILURE;
}

/*****************************************************************************
 Prototype      : At_PbUnicodeToIraFormatPrint
 Description    : 当前字符集为IRA，需要查表将ucs2字符转换为IRA字符
 Input          : ulMaxLength -- 能存储转换后字符的最大长度
                  pucSrc      -- 指向待转换字符
                  ulSrcLen    -- 待转换字符长度
 Output         : pucDst      -- 指向转换后字符
 Return Value   : 转换后的IRA码流长度

 History        :
  1.Date        : 2011-01-19
    Author      : j00168360
    Modification: [电话本第二阶段] Created function
*****************************************************************************/
TAF_UINT16 At_PbUnicodeToIraFormatPrint(TAF_UINT16 usMaxLength,
                                        TAF_UINT8  *pucDst,
                                        TAF_UINT8  *pucSrc,
                                        TAF_UINT16 usSrcLen)
{
    TAF_UINT16      usIndex;
    TAF_UINT16      usRetLen = 0;
    TAF_UINT8       *pucData = pucSrc;
    TAF_UINT16      usUnicodeChar;

    /* IRA码流的长度是UCS2码流长度的一半 */
    usRetLen = usSrcLen >> 1;

    /* 检查存储空间是否足够 */
    if (usRetLen > usMaxLength)
    {
       AT_ERR_LOG("At_PbUnicodeToIraFormatPrint error: too long");

       return 0;
    }

    /* 逐个将UCS2字符通过查表转换为IRA编码 */
    for (usIndex = 0; usIndex < usRetLen; usIndex++)
    {
        /* 先将UINT8数据转为UINT16 */
        usUnicodeChar = (*pucData << 8) | (*(pucData + 1));
        pucData += 2;

        if (AT_SUCCESS != At_PbOneUnicodeToIra(usUnicodeChar, &pucDst[usIndex]))
        {
            AT_ERR_LOG("At_PbUnicodeToIraFormatPrint error: no found");

            return 0;
        }
    }

    return usRetLen;
}

/*****************************************************************************
 Prototype      : At_PbUnicode82FormatPrint
 Description    : 将UCS2码流按82编码格式解压
 Input          : puc82Code 输入的UCS2 82码流,'82'类型标志的字节已被截掉
 Input          :           第一个Byte表示长度,
                :           第二、三个Byte表示BaseCode,
                :           第四个及以后的Byte表示82压缩后的码流
 Output         : pucDst 是解压以后的码流
                : pulDstLen 是解压以后的码流的长度
 Return Value   : 无

 History        :
  1.Date        : 2011-01-19
    Author      : j00168360
    Modification: [电话本第二阶段] Created function
*****************************************************************************/
TAF_VOID At_PbUnicode82FormatPrint(TAF_UINT8  *puc82Code,
                                   TAF_UINT8  *pucDst,
                                   TAF_UINT16 *pusDstLen)
{

    TAF_UINT16      usIndex;
    TAF_UINT16      usBaseCode;
    TAF_UINT16      usUnicode;
    TAF_UINT16      usSrcLen;
    TAF_UINT16      usDstIndex  = 0;
    TAF_UINT16      usGsmCodeLen;
    TAF_UINT16      usGsm2UCS2CodeLen;
    TAF_UINT16      *pusUnicode = (TAF_UINT16 *)pucDst;
    TAF_UINT8       *pucSrc;

    /* 取得82编码的长度 */
    usSrcLen = puc82Code[0];

    /* 取得82编码的Basecode */
    usBaseCode = (puc82Code[1] << 8) | puc82Code[2];

    if((SI_PB_ALPHATAG_MAX_LEN < usSrcLen)||(0xFFFF == usBaseCode)) /*数据长度错误*/
    {
        *pusDstLen = 0;

        return;
    }

    /* 取得82编码的码流, 第四个及以后的Byte表示82压缩后的码流 */
    pucSrc = puc82Code + 3;

    /* 从第四个字节开始是82编码的码流 */
    for(usIndex = 0; usIndex < usSrcLen; usIndex++)
    {
        usGsmCodeLen = 0;
        while((AT_PB_GSM7_CODE_MAX_VALUE >= pucSrc[usIndex + usGsmCodeLen])
           && ((usIndex + usGsmCodeLen) < usSrcLen))
        {
            usGsmCodeLen++;
        }

        if(0 != usGsmCodeLen)
        {
            usGsm2UCS2CodeLen = 0;
            At_PbGsmToUnicode((pucSrc + usIndex), usGsmCodeLen,
                             (TAF_UINT8 *)(pusUnicode + usDstIndex),
                             &usGsm2UCS2CodeLen);

            usIndex    += (usGsmCodeLen - 1);
            usDstIndex += (usGsm2UCS2CodeLen >> 1);

            continue;
        }

        /* 82 编码先将第8bit置零再与基本码相加 */
        usUnicode = usBaseCode + (pucSrc[usIndex] & AT_PB_GSM7_CODE_MAX_VALUE);

        AT_UNICODE2VALUE(usUnicode);

        pusUnicode[usDstIndex++] = usUnicode;
    }

    *pusDstLen = (TAF_UINT16)(usDstIndex << 1);

    return;
}

/*****************************************************************************
 Prototype      : At_PbUnicode8FormatPrint
 Description    : 将UCS2码流按81编码格式解压
 Input          : puc81Code 输入的UCS2 81码流,'81'类型标志的字节已被截掉
                :           第一个Byte表示长度,
                :           第二个Byte表示基指针,
                :           第三个及以后的Byte表示81压缩后的码流
 Output         : pucDst 是解压以后的码流
                : pulDstLen 是解压以后的码流的长度
 Return Value   : 无

 History        :
  1.Date        : 2011-01-19
    Author      : j00168360
    Modification: [电话本第二阶段] Created function
*****************************************************************************/
TAF_VOID At_PbUnicode81FormatPrint(TAF_UINT8  *puc81Code,
                                   TAF_UINT8  *pucDst,
                                   TAF_UINT16 *pusDstLen)
{
    TAF_UINT16      usIndex;
    TAF_UINT16      usUnicode;
    TAF_UINT16      usBaseCode;
    TAF_UINT16      usSrcLen;
    TAF_UINT16      usDstIndex  = 0;
    TAF_UINT16      usGsmCodeLen;
    TAF_UINT16      usGsm2UCS2CodeLen;
    TAF_UINT16      *pusUnicode = (TAF_UINT16 *)pucDst;
    TAF_UINT8       *pucSrc;

    if(SI_PB_ALPHATAG_MAX_LEN < puc81Code[0])    /*字符个数不能大于姓名的最大值*/
    {
        *pusDstLen = 0;

        return;
    }

    /* 取得81编码的长度 */
    usSrcLen = puc81Code[0];

    /* 取得81编码的基指针 */
    usBaseCode = puc81Code[1] << 7;

    /* 取得81编码的码流, 第三个及以后的Byte表示81压缩后的码流 */
    pucSrc = puc81Code + 2;

    /* 从第三个字节开始是81编码的码流 */
    for (usIndex = 0; usIndex < usSrcLen; usIndex++)
    {
        usGsmCodeLen = 0;
        while ((AT_PB_GSM7_CODE_MAX_VALUE >= pucSrc[usIndex + usGsmCodeLen])
            && ((usIndex+usGsmCodeLen) < usSrcLen))
        {
            usGsmCodeLen++;
        }

        if (0 != usGsmCodeLen)
        {
            usGsm2UCS2CodeLen = 0;
            At_PbGsmToUnicode((pucSrc + usIndex), usGsmCodeLen,
                             (TAF_UINT8 *)(pusUnicode + usDstIndex),
                             &usGsm2UCS2CodeLen);

            usIndex    += (usGsmCodeLen - 1);
            usDstIndex += (usGsm2UCS2CodeLen >> 1);

            continue;
        }

        /* 81编码先将第8bit置零再与基本码相加 */
        usUnicode = usBaseCode + (pucSrc[usIndex] & AT_PB_GSM7_CODE_MAX_VALUE);

        AT_UNICODE2VALUE(usUnicode);

        pusUnicode[usDstIndex++] = usUnicode;
    }

    *pusDstLen = (TAF_UINT16)(usDstIndex << 1);

    return;
}

/*****************************************************************************
 Prototype      : At_PbUnicode80FormatPrint
 Description    : 将UCS2码流按80格式保存
 Input          : pucSrc -- 输入的UCS2码流
                : ulSrcLen -- 输入的UCS2码流长度
 Output         : pucDst -- 转成UCS2 80后的码流
                : pulDstLen -- 转成UCS2 80后的码流长度
 Return Value   : 无

 History        :
  1.Date        : 2011-01-19
    Author      : j00168360
    Modification: [电话本第二阶段] Created function
*****************************************************************************/
TAF_VOID At_PbUnicode80FormatPrint(TAF_UINT8  *pucSrc,
                                   TAF_UINT16 usSrcLen,
                                   TAF_UINT8  *pucDst,
                                   TAF_UINT16 *pusDstLen)
{
    if((0xFF == pucSrc[0])&&(0xFF == pucSrc[1]))   /*当首字符为FFFF，认为当前姓名为空*/
    {
        *pusDstLen = 0;
    }
    else
    {
        /* 跳过80标志位 */
        VOS_MemCpy(pucDst, pucSrc, usSrcLen);

        *pusDstLen = usSrcLen;
    }

    return;
}

/*****************************************************************************
 Prototype      :At_PbGsmExtToUnicode
 Description    :查找GSM到UNICODE扩展表，找到则返回成功，否则返回失败
 Input          : ucGsmExtChar -- GSM字符
 Output         : pusUnicodeChar --  UCS2字符
 Return Value   : AT_SUCCESS，AT_FAILURE

 History        :
  1.Date        : 2011-01-19
    Author      : j00168360
    Modification: [电话本第二阶段] Created function
*****************************************************************************/
TAF_UINT32 At_PbGsmExtToUnicode(TAF_UINT8 ucGsmExtChar, TAF_UINT16 *pusUnicodeChar)
{
    TAF_UINT16      usIndex;

    /* 查找GSM到UNICODE扩展表，找到则返回成功，否则返回失败 */
    for (usIndex = 0; usIndex < AT_PB_GSM7EXT_MAX_NUM; usIndex++)
    {
        if (ucGsmExtChar == g_astGsm7extToUnicode[usIndex].ucOctet)
        {
            *pusUnicodeChar = g_astGsm7extToUnicode[usIndex].usUnicode;

            return AT_SUCCESS;
        }
    }

    AT_LOG1("At_PbGsmExtToUnicode warning: no found [0x%x]", ucGsmExtChar);

    return AT_FAILURE;
}

/*****************************************************************************
 Prototype      :At_PbGsmToUnicode
 Description    :当前字符集为UCS2或IRA，而存储格式为GSM7bit，需要先将GSM7bit查表转换为UCS2
 Input          : pucSrc -- 输入的GSM码流
                : ulSrcLen -- 输入的GSM码流长度
 Output         : pucDst -- 转成UCS2后的码流
                : pulDstLen -- 转成UCS2后的码流长度
 Return Value   : 无

 History        :
  1.Date        : 2011-01-19
    Author      : j00168360
    Modification: [电话本第二阶段] Created function
*****************************************************************************/
TAF_VOID At_PbGsmToUnicode(TAF_UINT8  *pucSrc,
                           TAF_UINT16 usSrcLen,
                           TAF_UINT8  *pucDst,
                           TAF_UINT16 *pusDstLen)
{
    TAF_UINT16      usIndex;
    TAF_UINT16      usUnicodeLen = 0;
    TAF_UINT16      *pusUnicode  = (TAF_UINT16 *)pucDst;
    TAF_UINT16      usUnicodeChar;

    for (usIndex = 0; usIndex < usSrcLen; usIndex++)
    {
        /* 为兼容有些平台再GSM模式下写入记录时未对最高BIT置零 */
        pucSrc[usIndex] = pucSrc[usIndex] & AT_PB_GSM7_CODE_MAX_VALUE;

        /* 非0x1B字符，直接查GSM到UNICODE基本表 */
        if (AT_PB_GSM7EXT_SYMBOL != pucSrc[usIndex])
        {
            usUnicodeChar = g_astGsmToUnicode[pucSrc[usIndex]].usUnicode;
            AT_UNICODE2VALUE(usUnicodeChar);
            *pusUnicode = usUnicodeChar;
            pusUnicode++;
            usUnicodeLen++;

            continue;
        }

        /* 当前GSM编码为0x1b时,可能为扩展标志 */
        if ((usSrcLen - usIndex) < 2)
        {
            /* 最后一个字节为0x1B，查GSM到UNICODE基本表, 将0x1B译为SPACE */
            usUnicodeChar = g_astGsmToUnicode[pucSrc[usIndex]].usUnicode;
            AT_UNICODE2VALUE(usUnicodeChar);
            *pusUnicode = usUnicodeChar;
            pusUnicode++;
            usUnicodeLen++;

            continue;
        }

        /* 对于0x1B 0x1B的情况，因为我们不支持第三张扩展表，因此直接将0x1B
            0x1B译为SPACE SPACE */
        if (AT_PB_GSM7EXT_SYMBOL == pucSrc[usIndex + 1])
        {
            usUnicodeChar = g_astGsmToUnicode[pucSrc[usIndex]].usUnicode;
            AT_UNICODE2VALUE(usUnicodeChar);
            *pusUnicode = usUnicodeChar;
            pusUnicode++;

            usUnicodeChar = g_astGsmToUnicode[pucSrc[usIndex + 1]].usUnicode;
            AT_UNICODE2VALUE(usUnicodeChar);
            *pusUnicode = usUnicodeChar;
            pusUnicode++;

            usIndex++;
            usUnicodeLen += 2;

            continue;
        }

        /* 0x1B可能为标志，查找GSM到UNICODE扩展表 */
        if (AT_SUCCESS == At_PbGsmExtToUnicode(pucSrc[usIndex + 1], &usUnicodeChar))
        {
            AT_UNICODE2VALUE(usUnicodeChar);
            *pusUnicode = usUnicodeChar;
            pusUnicode++;
            usIndex++;
            usUnicodeLen++;

            continue;
        }

       /* 对于1BXX，未在扩展表中，且XX不为0x1B的情况，译为SPACE+XX对应的字符 */
       usUnicodeChar = g_astGsmToUnicode[pucSrc[usIndex]].usUnicode;
       AT_UNICODE2VALUE(usUnicodeChar);
       *pusUnicode = usUnicodeChar;
       pusUnicode++;
       usUnicodeLen++;
    }

    /* GSM7BIT 码流中可能有扩展表中字符，GSM7bit到UNICODE转换长度不一定是原码流长度的2倍 */
    *pusDstLen = (TAF_UINT16)(usUnicodeLen << 1);

    return;
}

/*****************************************************************************
 Prototype      : At_PbRecordToUnicode
 Description    : 将卡中姓名字段存储格式转化为UCS2码
 Input          : pEvent -- 事件内容
 Output         : pucDecode -- 转换后的UCS2码
                : pusDecodeLen -- 转换后的UCS2码长度
 Return Value   : 无

 History        :
  1.Date        : 2011-01-19
    Author      : j00168360
    Modification: [电话本第二阶段] Created function
*****************************************************************************/
TAF_VOID At_PbRecordToUnicode(SI_PB_EVENT_INFO_STRU *pstEvent,
                              TAF_UINT8             *pucDecode,
                              TAF_UINT16            *pusDecodeLen)
{
    TAF_UINT16      usDecodeLen = 0;

    switch(pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType)
    {
        case SI_PB_ALPHATAG_TYPE_GSM:
            At_PbGsmToUnicode(pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                              pstEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength,
                              pucDecode,
                              &usDecodeLen);
            break;
        case SI_PB_ALPHATAG_TYPE_UCS2_80:
            At_PbUnicode80FormatPrint(pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                      pstEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength,
                                      pucDecode,
                                      &usDecodeLen);
            break;
        case SI_PB_ALPHATAG_TYPE_UCS2_81:
            At_PbUnicode81FormatPrint(pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                      pucDecode,
                                      &usDecodeLen);
            break;
        case SI_PB_ALPHATAG_TYPE_UCS2_82:
            At_PbUnicode82FormatPrint(pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                      pucDecode,
                                      &usDecodeLen);
            break;
        default:
            AT_ERR_LOG("At_PbRecordToUnicode error: not support code type");

            break;
    }

    *pusDecodeLen = usDecodeLen;

    return;
}

/*****************************************************************************
 Prototype      : At_Pb_AlaphPrint
 Description    : 电话簿读取姓名数据打印函数
 Input          : pEvent -- 事件内容
                : pusDataLen -- 相对pgucAtSndCrLfAddr的偏移长度
 Output         : pucData  -- 输出的数据
 Return Value   : AT_SUCCESS， AT_FAILURE

 History        :
  1.Date        : 2011-01-19
    Author      : j00168360
    Modification: [电话本第二阶段] Created function
*****************************************************************************/
TAF_UINT32 At_Pb_AlaphPrint(TAF_UINT16            *pusDataLen,
                            SI_PB_EVENT_INFO_STRU *pstEvent,
                            TAF_UINT8             *pucData)
{
    TAF_UINT16              usLength = *pusDataLen;
    TAF_UINT16              usDecodeLen = 0;
    TAF_UINT16              usReturnLen = 0;
    TAF_UINT8               aucDecode[500] = {0};

    if (AT_CSCS_GSM_7Bit_CODE == gucAtCscsType)
    {
        /* 在GSM字符集下，不支持UCS2编码 */
        if ((SI_PB_ALPHATAG_TYPE_UCS2_80 == pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType)
         || (SI_PB_ALPHATAG_TYPE_UCS2_81 == pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType)
         || (SI_PB_ALPHATAG_TYPE_UCS2_82 == pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType))
        {
            usReturnLen = 0;

            AT_LOG1("At_Pb_AlaphPrint error: GSM7 doesn't read UCS code[%d]",
                    pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType);
            return AT_FAILURE;
        }

        usReturnLen = At_PbGsmFormatPrint((AT_CMD_MAX_LEN - usLength),
                                          (pucData + usLength),
                                          pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                          pstEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);
    }
    else  /* 当前字符集为UCS2或IRA时 */
    {
        /* 当前字符集为UCS2或IRA时，先根据存储格式转换为UCS2编码 */
        At_PbRecordToUnicode(pstEvent, aucDecode, &usDecodeLen);

        /* 当前字符集为IRA时，将UCS2转换为IRA码流输出*/
        if (AT_CSCS_IRA_CODE == gucAtCscsType)
        {
            usReturnLen = At_PbUnicodeToIraFormatPrint((AT_CMD_MAX_LEN - usLength),
                                                       (pucData + usLength),
                                                       aucDecode,
                                                       usDecodeLen);
        }

        /* 当前字符集为UCS2时，将UCS2转换为打印格式输出*/
        if (AT_CSCS_UCS2_CODE == gucAtCscsType)
        {
            usReturnLen = (TAF_UINT16)At_Unicode2UnicodePrint(AT_CMD_MAX_LEN,
                                                              (TAF_INT8 *)pucData,
                                                              (pucData + usLength),
                                                              aucDecode,
                                                              usDecodeLen);
        }
    }

    if (0 == usReturnLen)
    {
        gstAtSendData.usBufLen = 0;

        AT_LOG1("At_Pb_AlaphPrint error: usReturnLen = 0,gucAtCscsType = [%d]", gucAtCscsType);

        return AT_FAILURE;
    }

    usLength    += usReturnLen;
    *pusDataLen  = usLength;

    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : At_Pb_CnumAlaphPrint
 Description    : 电话簿读取姓名数据打印函数
 Input          : pEvent -- 事件内容
                : pusDataLen -- 相对pgucAtSndCrLfAddr的偏移长度
 Output         : pucData  -- 输出的数据
 Return Value   : AT_SUCCESS， AT_FAILURE

 History        :
  1.Date        : 2011-01-19
    Author      : j00168360
    Modification: [电话本第二阶段] Created function
*****************************************************************************/
TAF_UINT32 At_Pb_CnumAlaphPrint(TAF_UINT16            *pusDataLen,
                            SI_PB_EVENT_INFO_STRU *pstEvent,
                            TAF_UINT8             *pucData)
{
    TAF_UINT16              usLength = *pusDataLen;
    TAF_UINT16              usDecodeLen = 0;
    TAF_UINT16              usReturnLen = 0;
    TAF_UINT8               aucDecode[500] = {0};

    if (AT_CSCS_GSM_7Bit_CODE == gucAtCscsType)
    {
        /* 在GSM字符集下，不支持UCS2编码 */
        if ((SI_PB_ALPHATAG_TYPE_UCS2_80 == pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType)
         || (SI_PB_ALPHATAG_TYPE_UCS2_81 == pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType)
         || (SI_PB_ALPHATAG_TYPE_UCS2_82 == pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType))
        {

            AT_LOG1("At_Pb_AlaphPrint error: GSM7 doesn't read UCS code[%d]",
                    pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType);
            return AT_SUCCESS;
        }

        usReturnLen = At_PbGsmFormatPrint((AT_CMD_MAX_LEN - usLength),
                                          (pucData + usLength),
                                          pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                          pstEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);
    }
    else  /* 当前字符集为UCS2或IRA时 */
    {
        /* 当前字符集为UCS2或IRA时，先根据存储格式转换为UCS2编码 */
        At_PbRecordToUnicode(pstEvent, aucDecode, &usDecodeLen);

        /* 当前字符集为IRA时，将UCS2转换为IRA码流输出*/
        if (AT_CSCS_IRA_CODE == gucAtCscsType)
        {
            usReturnLen = At_PbUnicodeToIraFormatPrint((AT_CMD_MAX_LEN - usLength),
                                                       (pucData + usLength),
                                                       aucDecode,
                                                       usDecodeLen);
        }

        /* 当前字符集为UCS2时，将UCS2转换为打印格式输出*/
        if (AT_CSCS_UCS2_CODE == gucAtCscsType)
        {
            usReturnLen = (TAF_UINT16)At_Unicode2UnicodePrint(AT_CMD_MAX_LEN,
                                                              (TAF_INT8 *)pucData,
                                                              (pucData + usLength),
                                                              aucDecode,
                                                              usDecodeLen);
        }
    }

    if (0 == usReturnLen)
    {

        AT_LOG1("At_Pb_AlaphPrint error: usReturnLen = 0,gucAtCscsType = [%d]", gucAtCscsType);

        return AT_SUCCESS;
    }

    usLength    += usReturnLen;
    *pusDataLen  = usLength;

    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : AT_Pb_NumberPrint
 Description    : 电话簿读取号码及号码类型打印函数
 Input          : pEvent -- 事件内容
                : pusDataLen -- 相对pgucAtSndCrLfAddr的偏移长度
 Output         : pusDataLen  -- 输出相对pgucAtSndCrLfAddr的偏移长度
 Return Value   : AT_SUCCESS， AT_FAILURE

 History        :
  1.Date        : 2011-04-21
    Author      : j00168360
    Modification: [DTS] Created function，根据产品线意见当号码为空时号码类型显示为129
*****************************************************************************/
TAF_VOID AT_Pb_NumberPrint(TAF_UINT16 *pusDataLen, SI_PB_EVENT_INFO_STRU *pstEvent, TAF_UINT8 *pucData)
{
    TAF_UINT16      usLength = *pusDataLen;

    if(0 == pstEvent->PBEvent.PBReadCnf.PBRecord.NumberLength)
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pucData,
                                           (TAF_CHAR *)pucData+usLength,
                                           ",\"\",129");
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pucData,
                                           (TAF_CHAR *)pucData + usLength,
                                           ",\"");

        if (PB_NUMBER_TYPE_INTERNATIONAL == pstEvent->PBEvent.PBReadCnf.PBRecord.NumberType )
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pucData,
                                               (TAF_CHAR *)pucData+usLength,
                                               "+");
        }

        PS_MEM_CPY(pucData + usLength, pstEvent->PBEvent.PBReadCnf.PBRecord.Number,
                   pstEvent->PBEvent.PBReadCnf.PBRecord.NumberLength);

        usLength += (TAF_UINT16)pstEvent->PBEvent.PBReadCnf.PBRecord.NumberLength;

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pucData,
                                           (TAF_CHAR *)pucData + usLength,
                                           "\"");

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pucData,
                                           (TAF_CHAR *)pucData + usLength,
                                           ",%d",
                                           pstEvent->PBEvent.PBReadCnf.PBRecord.NumberType);
    }

    *pusDataLen  = usLength;

    return;
}

/*****************************************************************************
 Prototype      : At_PbReadCnfProc
 Description    : 电话簿读取数据打印函数
 Input          : pEvent --- 事件内容
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : z00100318
  1.Date        : 2008-11-10
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_PbCNUMCmdPrint(VOS_UINT8 ucIndex,TAF_UINT16 *pusDataLen,TAF_UINT8 *pucData,SI_PB_EVENT_INFO_STRU *pEvent)
{
    TAF_UINT16              usLength = *pusDataLen;
    TAF_UINT32              ulResult;

    if(SI_PB_CONTENT_INVALID == pEvent->PBEvent.PBReadCnf.PBRecord.ValidFlag)
    {
        return AT_SUCCESS;
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,(TAF_CHAR *)pucData + usLength,"%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* 注意:内容需要根据编码类型进行输出，如果是ASCII码直接打印，如果UNICODE需要转换 */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,(TAF_CHAR *)pucData + usLength,"\"");

    if(pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength != 0)
    {
         ulResult = At_Pb_CnumAlaphPrint(&usLength, pEvent, pucData);

        if(AT_SUCCESS != ulResult)
        {
            At_FormatResultData(ucIndex, AT_CME_INVALID_CHARACTERS_IN_TEXT_STRING);

            return AT_FAILURE;
        }
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,(TAF_CHAR *)pucData + usLength,"\"");


    /* 将电话号码及号码类型处理封装为函数 */
    AT_Pb_NumberPrint(&usLength, pEvent, pucData);

    *pusDataLen = usLength;

    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : At_PbReadCnfProc
 Description    : 电话簿读取数据打印函数
 Input          : pEvent --- 事件内容
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : z00100318
  1.Date        : 2008-11-10
    Author      : ---
    Modification: Created function
  2.Date        : 2011-04-21
    Author      : j00168360
    Modification: [DTS2011041403381],根据产品线意见，当电话号码为空时号码类型显示为129
*****************************************************************************/
TAF_UINT32 At_PbCPBR2CmdPrint(VOS_UINT8 ucIndex,TAF_UINT16 *pusDataLen,TAF_UINT8 *pucData,SI_PB_EVENT_INFO_STRU *pEvent)
{
    TAF_UINT16              usLength = *pusDataLen;
    TAF_UINT32              ulResult;

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                    (TAF_CHAR *)pucData+usLength, "%s: ",
                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                    (TAF_CHAR *)pucData+usLength, "%d",
                                    pEvent->PBEvent.PBReadCnf.PBRecord.Index);


    /* 将电话号码及号码类型处理封装为函数 */
    AT_Pb_NumberPrint(&usLength, pEvent, pucData);

    /* 注意:内容需要根据编码类型进行输出，如果是ASCII码直接打印，如果UNICODE需要转换 */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,(TAF_CHAR *)pucData + usLength,",\"");

    if(pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength != 0)
    {
        ulResult = At_Pb_AlaphPrint(&usLength, pEvent, pucData);

        if(AT_SUCCESS != ulResult)
        {
            At_FormatResultData(ucIndex, AT_CME_INVALID_CHARACTERS_IN_TEXT_STRING);

            return AT_FAILURE;
        }
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                (TAF_CHAR *)pucData+usLength, "\"");

    *pusDataLen = usLength;

    return AT_SUCCESS;
}


/*****************************************************************************
 Prototype      : At_PbReadCnfProc
 Description    : 电话簿读取数据打印函数
 Input          : pEvent --- 事件内容
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : z00100318
  1.Date        : 2008-11-10
    Author      : ---
    Modification: Created function
  2.Date        : 2011-04-21
    Author      : j00168360
    Modification: [DTS2011041403381],根据产品线意见，当电话号码为空时号码类型显示为129
*****************************************************************************/
TAF_UINT32 At_PbCPBRCmdPrint(VOS_UINT8 ucIndex,TAF_UINT16 *pusDataLen,TAF_UINT8 *pucData,SI_PB_EVENT_INFO_STRU *pEvent)
{
    TAF_UINT16              usLength = *pusDataLen;

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                    (TAF_CHAR *)pucData+usLength, "%s: ",
                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                    (TAF_CHAR *)pucData+usLength, "%d",
                                    pEvent->PBEvent.PBReadCnf.PBRecord.Index);


    /* 将电话号码及号码类型处理封装为函数 */
    AT_Pb_NumberPrint(&usLength, pEvent, pucData);

    /* 注意:内容需要根据编码类型进行输出，如果是ASCII码直接打印，如果UNICODE需要转换 */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,(TAF_CHAR *)pucData + usLength,",\"");

    if(pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength != 0)
    {

        if(SI_PB_ALPHATAG_TYPE_UCS2 == (pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType&0x80))  /* DATA:IRA */
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                                (TAF_CHAR *)pucData+usLength, "%X",
                                                pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType);

            usLength += (TAF_UINT16)At_PB_Unicode2UnicodePrint(AT_CMD_MAX_LEN,(TAF_INT8 *)pucData,
                                        pucData+usLength, pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                        pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);

            if((pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength%2) == 0)/*对于奇数个中文需要后面补充FF*/
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,(TAF_CHAR *)pucData + usLength,"FF");
            }
        }
        else                                    /* DATA:UCS2 */
        {
            PS_MEM_CPY((TAF_CHAR *)pucData + usLength,
                        pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                        pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);

            usLength += pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength;
        }
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                (TAF_CHAR *)pucData+usLength, "\"");

    if(SI_PB_ALPHATAG_TYPE_UCS2 == (pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType&0x80))
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                        (TAF_CHAR *)pucData+usLength, ",1");
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                        (TAF_CHAR *)pucData+usLength, ",0");
    }

    *pusDataLen = usLength;

    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : At_PbEmailPrint
 Description    : 将GSM7BIT格式存储的email转换为IRA上报
 Input          : pucSrc -- 输入的GSM码流
                : ulSrcLen -- 输入的GSM码流长度
 Output         : pucDst -- 转成IRA后的码流
                : pulDstLen -- 转成IRA后的码流长度
 Return Value   : 无
 Calls          : At_PbGsmToUnicode，At_PbUnicodeToIraFormatPrint
 Called By      : At_PbSCPBRCmdPrint

 History        :
  1.Date        : 2011-01-27
    Author      : j00168360
    Modification: [电话本第二阶]Created function

  2.日    期    : 2012年8月10日
    作    者    : y00213812
    修改内容    : DTS2012082204471, TQE清理
*****************************************************************************/
TAF_VOID At_PbEmailPrint(TAF_UINT8  *pucSrc,
                         TAF_UINT16 usSrcLen,
                         TAF_UINT8  *pucDst,
                         TAF_UINT16 *pusDstLen)
{
    TAF_UINT8   aucUCS2Code[2 * SI_PB_EMAIL_MAX_LEN];
    TAF_UINT16  usUCS2CodeLen;
    TAF_UINT16  usEMailLen = usSrcLen;

    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, begin*/
    TAF_UINT16  usReturnLen;

    /* 对EMAIL长度大于64Byte，进行截断处理 */
    if(SI_PB_EMAIL_MAX_LEN < usEMailLen)
    {
        usEMailLen = SI_PB_EMAIL_MAX_LEN;
    }

    /* 先将GSM模式转成UCS2模式 */
    At_PbGsmToUnicode(pucSrc, usEMailLen, aucUCS2Code, &usUCS2CodeLen);

    /* 再将UCS2模式转成IRA模式 */
    usReturnLen = At_PbUnicodeToIraFormatPrint(usSrcLen, pucDst, aucUCS2Code, usUCS2CodeLen);
    if (0 == usReturnLen)
    {
        AT_INFO_LOG("At_PbEmailPrint error: usReturnLen = 0");
        return;
    }
    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, end*/

    *pusDstLen = (TAF_UINT16)(usUCS2CodeLen >> 1);

    return;
}

/*****************************************************************************
 Prototype      : At_PbSCPBRCmdPrint
 Description    : 电话簿读取数据打印函数
 Input          : pEvent --- 事件内容
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : m00128685
  1.Date        : 2009-06-18
    Author      : ---
    Modification: Created function
  2.Date        : 2011-01-27
    Author      : j00168360
    Modification: [电话本第二阶]段修改EMAIL字段读取
  3.Date        : 2011-04-21
    Author      : j00168360
    Modification: [DTS2011041403381],根据产品线意见，当电话号码为空时号码类型显示为129
*****************************************************************************/
TAF_UINT32 At_PbSCPBRCmdPrint(VOS_UINT8 ucIndex,TAF_UINT16 *pusDataLen,SI_PB_EVENT_INFO_STRU *pEvent)
{
    TAF_UINT16              usLength = *pusDataLen;
    TAF_UINT16              i;
    TAF_UINT16              usEmailLen = 0;

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                    (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "%s: ",
                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                    (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "%d",
                                    pEvent->PBEvent.PBReadCnf.PBRecord.Index);


    /* 将电话号码及号码类型处理封装为函数 */
    AT_Pb_NumberPrint(&usLength, pEvent, pgucAtSndCrLfAddr);

    for(i = 0; i < 3; i++)
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                        (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, ",\"");

        if(0 == pEvent->PBEvent.PBReadCnf.PBRecord.AdditionNumber[i].NumberLength)
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                            (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "\",129");

            continue;
        }

        if (PB_NUMBER_TYPE_INTERNATIONAL == pEvent->PBEvent.PBReadCnf.PBRecord.AdditionNumber[i].NumberType )
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                        (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "+");
        }

        PS_MEM_CPY(pgucAtSndCrLfAddr + usLength,pEvent->PBEvent.PBReadCnf.PBRecord.AdditionNumber[i].Number,
                        pEvent->PBEvent.PBReadCnf.PBRecord.AdditionNumber[i].NumberLength);

        usLength += (TAF_UINT16)pEvent->PBEvent.PBReadCnf.PBRecord.AdditionNumber[i].NumberLength;

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                        (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "\"");

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                        (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, ",%d",
                                        pEvent->PBEvent.PBReadCnf.PBRecord.AdditionNumber[i].NumberType);
    }

    /* 注意:内容需要根据编码类型进行输出，如果是ASCII码直接打印，如果UNICODE需要转换 */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,(TAF_CHAR *)pgucAtSndCrLfAddr + usLength,",\"");

    if(pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength != 0)
    {
        if(SI_PB_ALPHATAG_TYPE_UCS2 == (pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType&0x80))  /* DATA:IRA */
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                                (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "%X",
                                                pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType);

            usLength += (TAF_UINT16)At_PB_Unicode2UnicodePrint(AT_CMD_MAX_LEN,(TAF_INT8 *)pgucAtSndCrLfAddr,
                                        pgucAtSndCrLfAddr+usLength, pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                        pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);

            if((pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength%2) == 0)/*对于奇数个中文需要后面补充FF*/
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,(TAF_CHAR *)pgucAtSndCrLfAddr + usLength,"FF");
            }
        }
        else                                    /* DATA:UCS2 */
        {
            PS_MEM_CPY((TAF_CHAR *)pgucAtSndCrLfAddr + usLength,
                        pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                        pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);

            usLength += pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength;
        }
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "\"");

    if (AT_CMD_SCPBR_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {

        if(SI_PB_ALPHATAG_TYPE_UCS2 == (pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType&0x80))
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                            (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, ",1");
        }
        else
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                            (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, ",0");
        }
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                    (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, ",\"");

    if ( 0 != pEvent->PBEvent.PBReadCnf.PBRecord.Email.EmailLen )
    {
        At_PbEmailPrint(pEvent->PBEvent.PBReadCnf.PBRecord.Email.Email,
                        (TAF_UINT16)pEvent->PBEvent.PBReadCnf.PBRecord.Email.EmailLen,
                        (TAF_UINT8 *)(pgucAtSndCrLfAddr + usLength),
                        &usEmailLen);

        usLength += usEmailLen;

    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                    (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "\"");

    *pusDataLen = usLength;

    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : At_PbSearchCnfProc
 Description    : 电话簿查找数据打印函数
 Input          : pEvent --- 事件内容
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : h59254
  1.Date        : 2009-03-14
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_VOID At_PbSearchCnfProc(VOS_UINT8 ucIndex,SI_PB_EVENT_INFO_STRU  *pEvent)
{
    TAF_UINT16              usLength = 0;

    gulPBPrintTag = TAF_TRUE;

/*
    if(0 != usLength)
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr, (TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);
    }
*/
    if(pEvent->PBEvent.PBSearchCnf.PBRecord.ValidFlag == SI_PB_CONTENT_INVALID)/*当前的内容无效*/
    {
        return;              /*返回不处理*/
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%d",pEvent->PBEvent.PBSearchCnf.PBRecord.Index);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,",\"");

    if (PB_NUMBER_TYPE_INTERNATIONAL == pEvent->PBEvent.PBSearchCnf.PBRecord.NumberType)
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"+");
    }

    PS_MEM_CPY(pgucAtSndCodeAddr + usLength,pEvent->PBEvent.PBSearchCnf.PBRecord.Number, pEvent->PBEvent.PBSearchCnf.PBRecord.NumberLength);
    usLength += (TAF_UINT16)pEvent->PBEvent.PBSearchCnf.PBRecord.NumberLength;
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"\"");

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,",%d,",pEvent->PBEvent.PBSearchCnf.PBRecord.NumberType);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
    /* PS_MEM_CPY((TAF_CHAR *)pgucAtSndCodeAddr + usLength,pEvent->PBEvent.PBSearchCnf.PBRecord.AlphaTag, pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength); */
    /* usLength += pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength; */

    if(SI_PB_ALPHATAG_TYPE_UCS2 == (pEvent->PBEvent.PBSearchCnf.PBRecord.AlphaTagType & 0x80))  /* DATA:IRA */
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr+usLength,"%X",pEvent->PBEvent.PBSearchCnf.PBRecord.AlphaTagType);

        usLength += (TAF_UINT16)At_PB_Unicode2UnicodePrint(AT_CMD_MAX_LEN,(TAF_INT8 *)pgucAtSndCodeAddr,pgucAtSndCodeAddr+usLength,pEvent->PBEvent.PBSearchCnf.PBRecord.AlphaTag,pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength);

        if((pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength%2) == 0)/*对于奇数个中文需要后面补充FF*/
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"FF");
        }
    }
    else                                    /* DATA:UCS2 */
    {
        if(AT_CSCS_UCS2_CODE == gucAtCscsType)       /* +CSCS:UCS2 */
        {
            usLength += (TAF_UINT16)At_Ascii2UnicodePrint(AT_CMD_MAX_LEN,(TAF_INT8 *)pgucAtSndCodeAddr,pgucAtSndCodeAddr+usLength,pEvent->PBEvent.PBSearchCnf.PBRecord.AlphaTag,pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength);
        }
        else
        {
            PS_MEM_CPY((TAF_CHAR *)pgucAtSndCodeAddr + usLength,pEvent->PBEvent.PBSearchCnf.PBRecord.AlphaTag,pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength);
            usLength += pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength;
        }
    }
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"\"");

    if(AT_V_ENTIRE_TYPE == gucAtVType)
    {
        PS_MEM_CPY((TAF_CHAR *)pgucAtSndCrLfAddr,(TAF_CHAR *)gaucAtCrLf,2);/*Code前面加\r\n*/
        At_SendResultData(ucIndex,pgucAtSndCrLfAddr,usLength+2);
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);

        At_SendResultData(ucIndex,pgucAtSndCodeAddr,usLength);
    }
}


/*****************************************************************************
 Prototype      : At_PbReadCnfProc
 Description    : 电话簿读取数据打印函数
 Input          : pEvent --- 事件内容
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : z00100318
  1.Date        : 2008-11-10
    Author      : ---
    Modification: Created function
  2.日    期   : 2012年03月03日
   作    者   : s62952
   修改内容   : BalongV300R002 Build优化项目 :oam确认电话本与E5、LCARD删除掉
*****************************************************************************/
TAF_UINT32 At_PbReadCnfProc(VOS_UINT8 ucIndex,SI_PB_EVENT_INFO_STRU  *pEvent)
{
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usPBReadPrintLength;
    ulResult                            = AT_FAILURE;
    usPBReadPrintLength                 = 0;

    if (SI_PB_CONTENT_INVALID == pEvent->PBEvent.PBReadCnf.PBRecord.ValidFlag)/*当前的内容无效*/
    {
        return AT_SUCCESS;              /*返回不处理*/
    }
    else
    {
        if (TAF_FALSE == gulPBPrintTag)
        {
             usPBReadPrintLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,(TAF_CHAR *)pgucAtSndCrLfAddr,"%s","\r\n");
        }

        gulPBPrintTag = TAF_TRUE;

        if(AT_CMD_CPBR_SET == gastAtClientTab[ucIndex].CmdCurrentOpt) /*按照 ^CPBR 的方式进行打印*/
        {
            ulResult = At_PbCPBRCmdPrint(ucIndex,&usPBReadPrintLength,pgucAtSndCrLfAddr,pEvent);
        }
        else if(AT_CMD_CPBR2_SET == gastAtClientTab[ucIndex].CmdCurrentOpt) /*按照 +CPBR 的方式进行打印*/
        {
            ulResult = At_PbCPBR2CmdPrint(ucIndex,&usPBReadPrintLength,pgucAtSndCrLfAddr,pEvent);
        }
        else if(AT_CMD_SCPBR_SET == gastAtClientTab[ucIndex].CmdCurrentOpt) /*按照 ^SCPBR 的方式进行打印*/
        {
            ulResult = At_PbSCPBRCmdPrint(ucIndex,&usPBReadPrintLength,pEvent);
        }
        else if(AT_CMD_CNUM_READ == gastAtClientTab[ucIndex].CmdCurrentOpt) /*按照 CNUM 的方式进行打印*/
        {
            ulResult = At_PbCNUMCmdPrint(ucIndex,&usPBReadPrintLength,pgucAtSndCrLfAddr,pEvent);
        }
        else
        {
            AT_ERR_LOG1("At_PbReadCnfProc: the Cmd Current Opt %d is Unknow", gastAtClientTab[ucIndex].CmdCurrentOpt);

            return AT_FAILURE;
        }
    }

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    if(AT_SUCCESS == ulResult)
    {
        usPBReadPrintLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                                (TAF_CHAR *)pgucAtSndCrLfAddr + usPBReadPrintLength,
                                                "%s","\r\n");
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    At_SendResultData(ucIndex,pgucAtSndCrLfAddr,usPBReadPrintLength);

    PS_MEM_CPY((TAF_CHAR *)pgucAtSndCrLfAddr,(TAF_CHAR *)gaucAtCrLf,2);/*AT输出Buffer的前两个字节恢复为\r\n*/

    return ulResult;
}


/*****************************************************************************
 Prototype      : At_PbCallBackFunc
 Description    : 电话簿管理上报函数
 Input          : pEvent --- 事件内容
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.日    期 : 2007-03-27
    作    者 : h59254
    修改内容 : 问题单号:A32D09820(PC-Lint修改)
  3.日    期   : 2007年06月11日
    作    者   : h44270
    修改内容   : 问题单A32D11418
  4.日    期   : 2007年11月22日
    作    者   : z00100318
    修改内容   : PB优化
  5.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题
*****************************************************************************/
TAF_VOID At_PbCallBackFunc(SI_PB_EVENT_INFO_STRU  *pEvent)
{
    TAF_UINT32 ulSendMsg = 0;
    TAF_UINT8  ucIndex;

    if(TAF_NULL_PTR == pEvent)      /*参数错误*/
    {
        AT_WARN_LOG("At_PbCallBackFunc pEvent NULL");

        return;
    }

    if(AT_FAILURE == At_ClientIdToUserId(pEvent->ClientId, &ucIndex))/*回复的客户端内容错误*/
    {
        //At_SendReportMsg(MN_CALLBACK_PHONE_BOOK, (TAF_UINT8*)pEvent, sizeof(SI_PB_EVENT_INFO_STRU));

        return;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_PbMsgProc : AT_BROADCAST_INDEX.");
        return;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    if(AT_CMD_CNUM == gastAtClientTab[ucIndex].CmdIndex)
    {
        pEvent->PBError = ((TAF_ERR_PB_NOT_FOUND == pEvent->PBError)?TAF_ERR_NO_ERROR:pEvent->PBError);
    }

    if(TAF_ERR_NO_ERROR != pEvent->PBError)/*出错，发送消息处理*/
    {
        ulSendMsg = SI_TRUE;
    }
    else if(((pEvent->PBEventType == SI_PB_EVENT_READ_CNF)||(pEvent->PBEventType == SI_PB_EVENT_SREAD_CNF))
        && (pEvent->PBLastTag != SI_PB_LAST_TAG_TRUE))/*由于读取的特殊要求，因此不能通过一次性的消息发送数据进行处理*/
    {
        if ( AT_SUCCESS != At_PbReadCnfProc(ucIndex,pEvent) )
        {
            AT_WARN_LOG("At_PbCallBackFunc:At_PbReadCnfProc Error");
        }

        ulSendMsg = SI_FALSE;
    }
    else if(pEvent->PBEventType == SI_PB_EVENT_SEARCH_CNF)
    {
        if( SI_PB_LAST_TAG_TRUE == pEvent->PBLastTag )
        {
            ulSendMsg = SI_TRUE;
        }
        else
        {
            At_PbSearchCnfProc(ucIndex,pEvent);
            return;
        }
    }
    else        /*其它的回复可以通过消息进行一次性发送处理*/
    {
        ulSendMsg = SI_TRUE;
    }

    if (SI_TRUE == ulSendMsg)
    {
        At_SendReportMsg(MN_CALLBACK_PHONE_BOOK,(TAF_UINT8*)pEvent,sizeof(SI_PB_EVENT_INFO_STRU));
    }

    return;
}

/* Added by L60609 for AT Project，2011-10-04,  End*/

/*****************************************************************************
函 数 名  : At_RcvVcMsgSetGroundCnfProc
功能描述  : VC 前台、后台模式设置回复消息的处理函数
输入参数  : MN_AT_IND_EVT_STRU   *pstData
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修订记录  :
  1.日    期   : 2012年12月28日
    作    者   : 张鹏/z00214637
    修改内容   : 创建函数,处理AT命令的结果回复
*****************************************************************************/
VOS_VOID At_RcvVcMsgSetGroundCnfProc(
    MN_AT_IND_EVT_STRU                 *pstData
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstData->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgSetGroundCnfProc:WARNING:AT INDEX NOT FOUND!");
        return;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgSetGroundCnfProc : AT_BROADCAST_INDEX.");
        return;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_CBG_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("At_RcvVcMsgSetGroundCnfProc:WARNING:AT ARE WAITING ANOTHER CMD!");
        return;
    }

    if (VOS_OK == pstData->aucContent[0])
    {
        ulRet = AT_OK;
    }
    else
    {
        ulRet = AT_ERROR;
    }

    /* 输出设置结果 */
    gstAtSendData.usBufLen = 0;

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return;
}

/*****************************************************************************
函 数 名  : At_RcvVcMsgQryGroundRspProc
功能描述  : VC消息查询前台模式回复的处理函数
输入参数  : MN_AT_IND_EVT_STRU   *pstData
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修订记录  :
  1.日    期   : 2012年12月28日
    作    者   : 张鹏/z00214637
    修改内容   : 创建函数,处理AT命令的结果回复
*****************************************************************************/
VOS_VOID At_RcvVcMsgQryGroundRspProc(
    MN_AT_IND_EVT_STRU                 *pstData
)
{
    APP_VC_QRY_GROUNG_RSP_STRU         *pstQryRslt;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstData->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryGroundRspProc:WARNING:AT INDEX NOT FOUND!");
        return;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryGroundRspProc : AT_BROADCAST_INDEX.");
        return;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_CBG_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("At_RcvVcMsgQryGroundRspProc:WARNING:AT ARE WAITING ANOTHER CMD!");
        return;
    }

    /* 初始化 */
    pstQryRslt = (APP_VC_QRY_GROUNG_RSP_STRU *)pstData->aucContent;

    if (VOS_OK == pstQryRslt->ucQryRslt)
    {
        /* 输出查询结果 */
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        "^CBG:%d",
                                                        pstQryRslt->enGround);
        ulRet = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
        ulRet = AT_ERROR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return;
}


/*****************************************************************************
 函 数 名  : At_RcvVcMsgQryTTYModeCnfProc
 功能描述  : VC消息查询端口回复的处理函数
 输入参数  :  MN_AT_IND_EVT_STRU *pstData
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月7日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID At_RcvVcMsgQryTTYModeCnfProc(
    MN_AT_IND_EVT_STRU                 *pstData
)
{
    APP_VC_QRY_TTYMODE_CNF_STRU        *pstTTYMode;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    pstTTYMode      = (APP_VC_QRY_TTYMODE_CNF_STRU *)pstData->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstData->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryTTYModeCnfProc: WARNING: AT INDEX NOT FOUND!");
        return;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryTTYModeCnfProc: AT_BROADCAST_INDEX.");
        return;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_TTYMODE_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("At_RcvVcMsgQryTTYModeCnfProc: WARNING:AT ARE WAITING ANOTHER CMD!");
        return;
    }

    /* 查询的TTY MODE */
    if (VOS_OK == pstTTYMode->ucQryRslt)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                   "%s: %u",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                   pstTTYMode->enTTYMode);
        ulRet = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
        ulRet = AT_ERROR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return;
}

/*****************************************************************************
 函 数 名  : At_RcvVcMsgSetTTYModeCnfProc
 功能描述  : VC消息设置端口回复的处理函数
 输入参数  :  MN_AT_IND_EVT_STRU *pstData
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月7日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID At_RcvVcMsgSetTTYModeCnfProc(
    MN_AT_IND_EVT_STRU                 *pstData
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                          *pucResult;
    VOS_UINT8                           ucIndex;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstData->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgSetTTYModeCnfProc: WARNING: AT INDEX NOT FOUND!");
        return;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgSetTTYModeCnfProc: AT_BROADCAST_INDEX.");
        return;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_TTYMODE_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("At_RcvVcMsgSetTTYModeCnfProc: WARNING:AT ARE WAITING ANOTHER CMD!");
        return;
    }

    pucResult = pstData->aucContent;
    if (VOS_OK == *pucResult)
    {
        ulRet = AT_OK;
    }
    else
    {
        ulRet = AT_ERROR;
    }

    /* 输出设置结果 */
    gstAtSendData.usBufLen = 0;

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return;
}


/* Added by f00179208 for AT Project，2011-10-06,  Begin */
/*****************************************************************************
 函 数 名  : At_ProcMsgFromVc
 功能描述  : At模块处理来自VC的消息
 输入参数  : MN_AT_IND_EVT_STRU *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月06日
    作    者   : f00179208
    修改内容   : 新生成函数
  2.日    期   : 2012年12月28日
    作    者   : 张鹏/z00214637
    修改内容   : ^CBG命令实现
  3.日    期   : 2014年3月27日
    作    者   : j00174725
    修改内容   : Ecall项目
*****************************************************************************/
VOS_VOID At_ProcMsgFromVc(MN_AT_IND_EVT_STRU *pMsg)
{
    switch(pMsg->usMsgName)
    {
        case APP_VC_MSG_CNF_QRY_MODE:
            At_RcvVcMsgQryModeCnfProc(pMsg);
            break;

        case APP_VC_MSG_CNF_SET_PORT:
            At_RcvVcMsgSetPortCnfProc(pMsg);
            break;

        case APP_VC_MSG_CNF_QRY_PORT:
            At_RcvVcMsgQryPortCnfProc(pMsg);
            break;

        case APP_VC_MSG_SET_FOREGROUND_CNF:
        case APP_VC_MSG_SET_BACKGROUND_CNF:
            /*AT 处理 VC 上报的前台模式、后台模式CNF MSG*/
            At_RcvVcMsgSetGroundCnfProc(pMsg);
            break;

        case APP_VC_MSG_FOREGROUND_RSP:
            /*AT 处理VC 上报的查询前台模式回复消息*/
            At_RcvVcMsgQryGroundRspProc(pMsg);
            break;
        case APP_VC_MSG_QRY_TTYMODE_CNF:
            At_RcvVcMsgQryTTYModeCnfProc(pMsg);
            break;
        case APP_VC_MSG_SET_TTYMODE_CNF:
            At_RcvVcMsgSetTTYModeCnfProc(pMsg);
            break;

        /* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, begin */
#if (FEATURE_ON == FEATURE_ECALL)
        case APP_VC_MSG_SET_MSD_CNF:
            AT_RcvVcMsgSetMsdCnfProc(pMsg);
            break;

        case APP_VC_MSG_QRY_MSD_CNF:
            AT_RcvVcMsgQryMsdCnfProc(pMsg);
            break;

        case APP_VC_MSG_QRY_ECALL_CFG_CNF:
            AT_RcvVcMsgQryEcallCfgCnfProc(pMsg);
            break;
#endif
        /* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, end */

        case APP_VC_MSG_DTMF_DECODER_IND:
            At_RcvVcMsgDtmfDecoderIndProc(pMsg);
            break;

        default:
            return;
    }
    return;
}
/* Added by f00179208 for AT Project，2011-10-06,  End */

/* Added by f00179208 for PS Project，2011-12-08,  Begin */
/*****************************************************************************
 函 数 名  : At_ProcMsgFromVc
 功能描述  : At模块处理来自RNIC的消息
 输入参数  : MN_AT_IND_EVT_STRU *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_OK, VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月08日
   作    者   : f00179208
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 At_RcvRnicMsg(MsgBlock *pstMsg)
{
    VOS_UINT32                          ulRst;
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader                        = (MSG_HEADER_STRU *)pstMsg;

    switch(pstMsgHeader->ulMsgName)
    {
        /* 处理RNIC发来的流量上报 */
        case ID_RNIC_AT_DSFLOW_RSP:

            ulRst = AT_RcvRnicDsflowRsp(pstMsg);
            break;

        /* 处理RNIC发来的拨号模式查询回复 */
        case ID_RNIC_AT_DIAL_MODE_CNF:

            ulRst = AT_RcvRnicDialModeCnf(pstMsg);
            break;

        default:
            ulRst = VOS_OK;
            break;
    }
    return ulRst;
}
/* Added by f00179208 for PS Project，2011-12-08,  End */

/* Added by o00132663 for AT Project，2011-10-06,  Begin */
/*****************************************************************************
 函 数 名  : At_ProcMsgFromCc
 功能描述  : At模块处理来自CC的消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月06日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID At_ProcMsgFromCc(VOS_VOID *pMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU *)pMsg;

    switch(pstMsgHeader->ulMsgName)
    {
        case AT_CC_MSG_STATE_QRY_CNF:
            At_RcvAtCcMsgStateQryCnfProc(pMsg);
            break;

        default:
            break;
    }
    return;
}
/* Added by o00132663 for AT Project，2011-10-06,  End */

/*****************************************************************************
 函 数 名  : AT_RcvNdisMsg
 功能描述  : NDIS模块消息处理
 输入参数  : MsgBlock* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月25日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_RcvNdisMsg(MsgBlock* pMsg)
{
    VOS_UINT32                          ulResult;
    AT_FW_MSG_STRU                     *pstAtFwMsg;
    AT_FW_CMD_BINARY_MSG_STRU          *pstBinaryInfo;
    AT_NDIS_MSG_STRU                   *pstNdisMsg;

    pstAtFwMsg      = (AT_FW_MSG_STRU*)(pMsg->aucValue);
    pstBinaryInfo   = (AT_FW_CMD_BINARY_MSG_STRU*)(pstAtFwMsg->pMsgParam);
    pstNdisMsg      = (AT_NDIS_MSG_STRU*)pstBinaryInfo;

    switch (pstNdisMsg->ulMsgId)
    {
        case ID_AT_NDIS_PDNINFO_CFG_CNF:
            ulResult = AT_RcvNdisPdnInfoCfgCnf(&pstNdisMsg->unMsg.stNdisPdnInfoCfgCnf);
            break;

        case ID_AT_NDIS_PDNINFO_REL_CNF:
            ulResult = AT_RcvNdisPdnInfoRelCnf(&pstNdisMsg->unMsg.stNdisPdnInfoRelCnf);
            break;

        default:
            AT_WARN_LOG("AT_RcvNdisMsg: Unexpected MSG is received.");
            ulResult = VOS_ERR;
            break;
    }

    if ( VOS_OK != ulResult )
    {
        AT_ERR_LOG1("AT_RcvNdisMsg: Process message failed. <MsgId>",
                    (VOS_INT32)pstNdisMsg->ulMsgId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_ProcRabmSetFastDormParaCnf
 功能描述  : 处理消息ID_RABM_AT_SET_FASTDORM_PARA_CNF
 输入参数  : pstMsg - 来自RABM的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月19日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32    AT_ProcRabmSetFastDormParaCnf(
    RABM_AT_SET_FASTDORM_PARA_CNF_STRU     *pstMsg
)
{
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulRslt;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMsg->usClientId,&ucIndex))
    {
        AT_WARN_LOG("At_ProcRabmSetFastDormParaCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 输出设置结果 */
    gstAtSendData.usBufLen = 0;
    ulRslt = AT_ERROR;
    if (AT_RABM_PARA_SET_RSLT_SUCC == pstMsg->enRslt)
    {
        ulRslt = AT_OK;
    }

    At_FormatResultData(ucIndex, ulRslt);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_ProcRabmQryFastDormParaCnf
 功能描述  : 处理消息RABM_AT_QRY_FASTDORM_PARA_CNF_STRU
 输入参数  : pstMsg - 来自RABM的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月19日
   作    者   : h44270
   修改内容   : 新生成函数

 2.日    期   : 2012年3月20日
   作    者   : l60609
   修改内容   : B070 Project:直接读写NV，不再调用底软接口

*****************************************************************************/
VOS_UINT32    AT_ProcRabmQryFastDormParaCnf(
    RABM_AT_QRY_FASTDORM_PARA_CNF_STRU     *pstMsg
)
{
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;
    VOS_UINT16                              usLength;

    ulResult = AT_ERROR;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMsg->usClientId,&ucIndex))
    {
        AT_WARN_LOG("At_RcvAtCcMsgStateQryCnfProc:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_TRUE == pstMsg->ucRslt)
    {
        /* 输出查询结果 */
        usLength = 0;
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"^FASTDORM:%d",pstMsg->stFastDormPara.enFastDormOperationType);

        if (AT_RABM_FASTDORM_STOP_FD_ASCR != pstMsg->stFastDormPara.enFastDormOperationType)
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,",%d",pstMsg->stFastDormPara.ulTimeLen);
        }

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);

        ulResult = AT_OK;
        gstAtSendData.usBufLen = usLength;
    }

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : AT_ProcRabmReleaseRrcCnf
 功能描述  : 快速拆除rrc连接
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月11日
    作    者   : M00217266
    修改内容  : Optimize RIL:

*****************************************************************************/
VOS_UINT32 AT_ProcRabmReleaseRrcCnf(RABM_AT_RELEASE_RRC_CNF_STRU *pstMsg)
{
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulRslt;

    ulRslt = AT_ERROR;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMsg->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_ProcRabmReleaseRrcCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* 输出设置结果 */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK == pstMsg->ulRslt)
    {
        ulRslt = AT_OK;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRslt);

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
/*****************************************************************************
 函 数 名  : AT_ProcRabmSetVoicePreferParaCnf
 功能描述  : 处理消息RABM_AT_SET_VOICEPREFER_PARA_CNF_STRU
 输入参数  : pstMsg - 来自RABM的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月26日
   作    者   : s00273135
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32    AT_ProcRabmSetVoicePreferParaCnf(
    RABM_AT_SET_VOICEPREFER_PARA_CNF_STRU     *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMsg->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_ProcRabmSetVoicePreferParaCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 输出设置结果 */
    gstAtSendData.usBufLen = 0;
    ulRslt = AT_ERROR;
    if (AT_RABM_PARA_SET_RSLT_SUCC == pstMsg->enRslt)
    {
        ulRslt = AT_OK;
    }

    At_FormatResultData(ucIndex, ulRslt);

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : AT_ProcRabmQryVoicePreferEnableParaCnf
 功能描述  : 处理消息RABM_AT_QRY_VOICEPREFER_PARA_CNF_STRU
 输入参数  : pstMsg - 来自RABM的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月26日
   作    者   : s00273135
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_ProcRabmQryVoicePreferEnableParaCnf(RABM_AT_QRY_VOICEPREFER_PARA_CNF_STRU *pstMsg)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    ulResult = AT_ERROR;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMsg->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_ProcRabmQryVoicePreferEnableParaCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 输出查询结果 */
    usLength = 0;
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s%s:%d%s",
                                       gaucAtCrLf,
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       pstMsg->ulRslt,
                                       gaucAtCrLf);
    ulResult = AT_OK;
    gstAtSendData.usBufLen = usLength;

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}
/*****************************************************************************
 函 数 名  : AT_ProcRabmVoicePreferStatusReport
 功能描述  : 处理消息RABM_AT_VOICEPREFER_STATUS_REPORT_STRU
 输入参数  : pstMsg - 来自RABM的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月26日
   作    者   : s00273135
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_ProcRabmVoicePreferStatusReport(RABM_AT_VOICEPREFER_STATUS_REPORT_STRU *pstMsg)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;

    ucIndex = 0;
    usLength = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMsg->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_ProcRabmVoicePreferStatusReport:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* 输出上报结果 */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                      "%s^VOICEPREFERSTATUS:%d%s",
                                      gaucAtCrLf,
                                      pstMsg->ulVpStatus,
                                      gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return VOS_OK;
}
#endif

/*****************************************************************************
 函 数 名  : AT_RabmMsgProc
 功能描述  : AT模块处理来自Rabm的消息
 输入参数  : MSG_HEADER_STRU * pstMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月19日
   作    者   : h44270
   修改内容   : 新生成函数
  2.日    期   : 2013年7月11日
    作    者   : M00217266
    修改内容  : Optimize RIL:

*****************************************************************************/
TAF_VOID AT_RabmMsgProc(
    MSG_HEADER_STRU                    *pstMsg
)
{
    switch(pstMsg->ulMsgName)
    {
        case ID_RABM_AT_SET_FASTDORM_PARA_CNF:
            AT_ProcRabmSetFastDormParaCnf((RABM_AT_SET_FASTDORM_PARA_CNF_STRU*)pstMsg);
            break;

        case ID_RABM_AT_QRY_FASTDORM_PARA_CNF:
            AT_ProcRabmQryFastDormParaCnf((RABM_AT_QRY_FASTDORM_PARA_CNF_STRU*)pstMsg);
            break;

        case ID_RABM_AT_SET_RELEASE_RRC_CNF:
            AT_ProcRabmReleaseRrcCnf((RABM_AT_RELEASE_RRC_CNF_STRU*)pstMsg);
            break;

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
        case ID_RABM_AT_SET_VOICEPREFER_PARA_CNF:
            AT_ProcRabmSetVoicePreferParaCnf((RABM_AT_SET_VOICEPREFER_PARA_CNF_STRU*)pstMsg);
            break;

        case ID_RABM_AT_QRY_VOICEPREFER_PARA_CNF:
            AT_ProcRabmQryVoicePreferEnableParaCnf((RABM_AT_QRY_VOICEPREFER_PARA_CNF_STRU*)pstMsg);
            break;

        case ID_RABM_AT_VOICEPREFER_STATUS_REPORT:
            AT_ProcRabmVoicePreferStatusReport((RABM_AT_VOICEPREFER_STATUS_REPORT_STRU *)pstMsg);
            break;
#endif
        default:
            AT_WARN_LOG("At_RabmMsgProc:WARNING:Wrong Msg!");
            break;
    }
}


/*****************************************************************************
 函 数 名  : At_MsgProc
 功能描述  : AT模块消息处理入口函数
 输入参数  : MsgBlock* pMsg
 输出参数  : 无
 返 回 值  : TAF_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.日    期   : 2010年2月23日
    作    者   : f62575
    修改内容   : 问题单号: AT2D16941：增加短信功能任意点回放功能
  3.日    期   : 2011年10月4日
    作    者   : 鲁琳/l60609
    修改内容   : AT Project: 增加AT AGENT的处理
  4.日    期   : 2011年10月23日
    作    者   : A00165503
    修改内容   : AT Project: NDIS消息处理
  5.日    期   : 2011年10月23日
    作    者   : f00179208
    修改内容   : AT Project: 增加VC消息处理
  6.日    期   : 2011年12月08日
    作    者   : f00179208
    修改内容   : PS Project: 增加RNIC消息处理
  7.日    期   : 2012年12月20日
    作    者   : l60609
    修改内容   : DSDA Phase II
  8.日    期   : 2015年6月25日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
TAF_VOID At_MsgProc(MsgBlock* pMsg)
{
    VOS_UINT32                          ulSendPid;
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulSliceStart;
    VOS_UINT32                          ulSliceEnd;
    VOS_UINT32                          ulType;
    TAF_UINT32                          ulRet;

    ulSliceStart = VOS_GetSlice();
    ulSendPid    = pMsg->ulSenderPid;
    ulMsgName    = ((MSG_HEADER_STRU *)pMsg)->ulMsgName;

    /* 超时处理 */
    if ( VOS_PID_TIMER == pMsg->ulSenderPid )
    {
        At_TimeOutProc((REL_TIMER_MSG*)pMsg);
        ulSliceEnd = VOS_GetSlice();
        AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);

        return;
    }

    /* 消息的分发处理 */
    switch ( pMsg->ulSenderPid )
    {
        case WUEPS_PID_AT:
            At_CmdMsgDistr((AT_MSG_STRU*)pMsg);
            ulSliceEnd = VOS_GetSlice();
            ulType     = ((AT_MSG_STRU*)pMsg)->ucType;
            ulMsgName  = (ulType<<16) | ulMsgName;
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_WUEPS_PID_TAF:
        case I1_WUEPS_PID_TAF:
        case I2_WUEPS_PID_TAF:
            ulRet = At_CallMsgProc((MSG_HEADER_STRU *)pMsg);
            if (AT_OK == ulRet)
            {
                return;
            }

            At_EventMsgProc((MN_AT_IND_EVT_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            ulMsgName = ((MN_AT_IND_EVT_STRU *)pMsg)->usMsgName;
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case PS_PID_APP_PPP:
            At_PppMsgProc((MSG_HEADER_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;


        case PS_PID_APP_NDIS:
            AT_RcvNdisMsg(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case DSP_PID_WPHY:
            At_HPAMsgProc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_DSP_PID_GPHY:
        case I1_DSP_PID_GPHY:
        case I2_DSP_PID_GPHY:
            At_GHPAMsgProc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_WUEPS_PID_MMA:
        case I1_WUEPS_PID_MMA:
        case I2_WUEPS_PID_MMA:
            At_MmaMsgProc((MSG_HEADER_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_WUEPS_PID_DRV_AGENT:
        case I1_WUEPS_PID_DRV_AGENT:
        case I2_WUEPS_PID_DRV_AGENT:
            At_ProcMsgFromDrvAgent((DRV_AGENT_MSG_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_WUEPS_PID_VC:
        case I1_WUEPS_PID_VC:
        case I2_WUEPS_PID_VC:
            At_ProcMsgFromVc((MN_AT_IND_EVT_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case ACPU_PID_RNIC:
            At_RcvRnicMsg(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_WUEPS_PID_CC:
        case I1_WUEPS_PID_CC:
        case I2_WUEPS_PID_CC:
            At_ProcMsgFromCc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        #if (FEATURE_ON == FEATURE_LTE)
        case MSP_L4_L4A_PID:
            at_L4aCnfProc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case MSP_SYS_FTM_PID:
            At_FtmEventMsgProc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;
        #endif

        case I0_MAPS_STK_PID:
        case I1_MAPS_STK_PID:
        case I2_MAPS_STK_PID:
            At_STKMsgProc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_MAPS_PB_PID:
        case I1_MAPS_PB_PID:
        case I2_MAPS_PB_PID:
            At_PbMsgProc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_MAPS_PIH_PID:
        case I1_MAPS_PIH_PID:
        case I2_MAPS_PIH_PID:
            At_PIHMsgProc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_WUEPS_PID_RABM:
        case I1_WUEPS_PID_RABM:
        case I2_WUEPS_PID_RABM:
            AT_RabmMsgProc((MSG_HEADER_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case WUEPS_PID_SPY:
            AT_SpyMsgProc((MSG_HEADER_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_UEPS_PID_MTA:
        case I1_UEPS_PID_MTA:
        case I2_UEPS_PID_MTA:
            At_ProcMtaMsg((AT_MTA_MSG_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

#if (FEATURE_ON == FEATURE_IMS)
        case PS_PID_IMSA:
            AT_ProcImsaMsg((AT_IMSA_MSG_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;
#endif

        case PS_PID_CSS:
            AT_ProcCssMsg((CssAtInterface_MSG *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_UEPS_PID_XSMS:
        case I1_UEPS_PID_XSMS:
        case I2_UEPS_PID_XSMS:
            AT_ProcXsmsMsg((TAF_XSMS_APP_AT_CNF_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))
        case I0_UEPS_PID_XPDS:
        case I1_UEPS_PID_XPDS:
        case I2_UEPS_PID_XPDS:
            AT_ProcXpdsMsg((AT_XPDS_MSG_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
         case DSP_PID_PROCSTUB:
            At_CHPAMsgProc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
#endif

        default:
            AT_LOG1("At_MsgProc other PID msg",pMsg->ulSenderPid);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;
    }
}

/*****************************************************************************
 函 数 名  : AT_EventReport
 功能描述  : 向OM上报AT事件
 输入参数  : VOS_UINT32 ulPid                   需要上报事件的模块ID
             NAS_OM_EVENT_ID_ENUM enEventId     需要上报的事件ID
             VOS_VOID *pPara                    事件中的可选参数
             VOS_UINT32 ulLen                   可选参数长度
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月22日
    作    者   : f62575
    修改内容   : 新生成函数
  2.日    期   : 2013年10月08日
    作    者   : j00174725
    修改内容   : TQE
  3.日    期   : 2015年07月23日
    作    者   : wx270776
    修改内容   : OM融合
*****************************************************************************/
VOS_VOID AT_EventReport(
    VOS_UINT32                          ulPid,
    NAS_OM_EVENT_ID_ENUM_UINT16         enEventId,
    VOS_VOID                           *pPara,
    VOS_UINT32                          ulLen
)
{
    /* Modified by wx270776 for OM融合, 2015-8-3, begin */
    DIAG_EVENT_IND_STRU                 stDiagEvent;
    NAS_OM_EVENT_IND_STRUCT            *pstAtEvent = VOS_NULL_PTR;
    VOS_VOID                           *pData = pPara;
    VOS_UINT32                          ulAtEventMsgLen;
    VOS_UINT32                          ulRslt;

    /* 入参检查 */
    if ( (VOS_NULL_PTR == pData) && (ulLen != 0) )
    {
        /* 错误打印 */
        TAF_LOG(ulPid, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_EventReport:pPara is NULL.");
        return;
    }

    /* 申请内存 */
    if (4 >= ulLen)
    {
        ulAtEventMsgLen = sizeof(NAS_OM_EVENT_IND_STRUCT);
        pstAtEvent = (NAS_OM_EVENT_IND_STRUCT*)PS_MEM_ALLOC(ulPid, ulAtEventMsgLen);
    }
    else
    {
        ulAtEventMsgLen = sizeof(NAS_OM_EVENT_IND_STRUCT) + ulLen -4;
        pstAtEvent = (NAS_OM_EVENT_IND_STRUCT*)PS_MEM_ALLOC(ulPid, ulAtEventMsgLen);
    }

    if (VOS_NULL_PTR == pstAtEvent)
    {
        TAF_LOG(ulPid, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_EventReport:Alloc mem fail.");
        return;
    }

    /* 初始化 */
    PS_MEM_SET(pstAtEvent, 0x0, ulAtEventMsgLen);

    /* 填写事件消息内容 */
    pstAtEvent->usEventId    = enEventId;
    pstAtEvent->usReserve    = 0;
    if ( (VOS_NULL_PTR != pData) && (ulLen > 0) )
    {
        PS_MEM_CPY(pstAtEvent->aucData, pData, ulLen);
    }

    /* 填写发给DIAG的结构体 */
    stDiagEvent.ulLength        = sizeof(NAS_OM_EVENT_IND_STRUCT) - 4 + ulLen;
    stDiagEvent.ulPid           = ulPid;
    stDiagEvent.ulEventId       = (VOS_UINT32)enEventId;
    stDiagEvent.ulModule        = DIAG_GEN_MODULE(VOS_GetModemIDFromPid(ulPid), DIAG_MODE_UMTS);
    stDiagEvent.pData           = pstAtEvent;

    ulRslt = DIAG_EventReport(&stDiagEvent);
    if (VOS_OK != ulRslt)
    {
        AT_WARN_LOG("AT_EventReport:OM_AcpuEvent Fail.");
    }

    PS_MEM_FREE(ulPid, pstAtEvent);
    /* Modified by wx270776 for OM融合, 2015-6-27, end */

    return;
}


/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentSetAdcRsp
 功能描述  : ^ADC的查询回复处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月5日
    作    者   : w00181244
    修改内容   : 新生成函数
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011112602473，解决自动应答开启情况下被叫死机问题
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentSetAdcRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                        *pRcvMsg;
    DRV_AGENT_ADC_SET_CNF_STRU                *pstAdcCnf;
    VOS_UINT8                                  ucIndex;
    VOS_UINT32                                 ulResult;

    /* 初始化消息 */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstAdcCnf       = (DRV_AGENT_ADC_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstAdcCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetAdcRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetAdcRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    /* 判断当前操作类型是否为AT_CMD_ADC_SET */
    if (AT_CMD_ADC_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /*设置门限值是否成功 */
    if (VOS_TRUE != pstAdcCnf->bFail)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    /* 调用AT_FormATResultDATa发送命令结果 */
    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentQryTbatRsp
 功能描述  : ^TBAT的查询回复处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : w00181244
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentQryTbatRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_TBAT_QRY_CNF_STRU        *stTbatTypeCnf;
    VOS_UINT8                           ucIndex;

    /* 初始化消息 */
    pRcvMsg                = (DRV_AGENT_MSG_STRU *)pMsg;
    stTbatTypeCnf          = (DRV_AGENT_TBAT_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(stTbatTypeCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryTbatRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /*自动应答开启情况下被叫死机问题*/
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryTbatRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_TBAT_QRY */
    if (AT_CMD_TBAT_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stTbatTypeCnf->ulTbatType);

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, AT_OK);
    return VOS_OK;

}


/*****************************************************************************
 函 数 名  : AT_RcvSimLockQryRsp
 功能描述  : ^SIMLOCK=2查询SIMLOCK状态的回复处理函数
     VOS_UINT8                           ucIndex,
     VOS_UINT8                           OpId,
     VOS_VOID                           *pPara
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月03日
    作    者   : f62575
    修改内容   : 新生成函数

  2.日    期   : 2014年2月21日
    作    者   : w00167002
    修改内容   : 调整函数返回值为VOS_UINT32
*****************************************************************************/
/* Modified by w00167002 for L-C互操作项目, 2014-2-21, begin */
VOS_UINT32 AT_RcvSimLockQryRsp(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;
    AT_MMA_SIMLOCK_STATUS_STRU         *pstEvent;

    pstEvent = (AT_MMA_SIMLOCK_STATUS_STRU *)pMsg;

    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvSimLockQryRsp: AT INDEX NOT FOUND!");

        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_SIMLOCKSTATUS_READ或AT_CMD_CSDFLT_READ */
    if ((AT_CMD_SIMLOCKSTATUS_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
     && (AT_CMD_CSDFLT_READ != gastAtClientTab[ucIndex].CmdCurrentOpt))
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    if (AT_CMD_SIMLOCKSTATUS_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s:%d",
                                                        "SIMLOCK",
                                                        pstEvent->bSimlockEnableFlg);
        ulRet                  = AT_OK;

    }
    else
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);
        gstAtSendData.usBufLen = 0;
        ulRet                  = AT_OutputCsdfltDefault(ucIndex, pstEvent->bSimlockEnableFlg);
    }

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulRet);

    return VOS_OK;
}
/* Modified by w00167002 for L-C互操作项目, 2014-2-21, end */


#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#if (VOS_WIN32 == VOS_OS_VER)
/*****************************************************************************
 函 数 名  : WuepsATFidInit
 功能描述  : AT FID初始化，用于ST测试，
 输入参数  : VOS_INIT_PHASE_DEFINE ip
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月22日
    作    者   : c00173809
    修改内容   : 新生成函数/PS融合项目
*****************************************************************************/
VOS_UINT32 WuepsATFidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32 ulRslt = VOS_OK;

    switch( ip )
    {
        case   VOS_IP_LOAD_CONFIG:
        /* Added by L60609 for AT Project，2011-10-20,  Begin*/
        #if (VOS_WIN32 == VOS_OS_VER)
            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_AT,
                                           (Init_Fun_Type)At_PidInit,
                                           (Msg_Fun_Type)At_MsgProc);

            if (VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }
        #endif
            /* Added by L60609 for AT Project，2011-10-20,  Begin*/

            ulRslt = VOS_RegisterMsgTaskPrio(WUEPS_FID_AT, VOS_PRIORITY_P6);

            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            break;
        default:
            break;
    }

    return VOS_OK;
}
#endif
#endif

#if (FEATURE_ON == FEATURE_SECURITY_SHELL)
/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentSetSpwordRsp
 功能描述  : 处理DRV_AGENT_SPWORD_SET_CNF消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月21日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentSetSpwordRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                        *pRcvMsg;
    DRV_AGENT_SPWORD_SET_CNF_STRU             *pstSpwordSetCnf;
    VOS_UINT8                                  ucIndex;

    /* 初始化消息 */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstSpwordSetCnf = (DRV_AGENT_SPWORD_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstSpwordSetCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("pstSpwordSetCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("pstSpwordSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_SPWORD_SET */
    if (AT_CMD_SPWORD_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 密码校验通过，错误次数需要清零 */
    if (VOS_OK == pstSpwordSetCnf->ulResult)
    {
        g_stSpWordCtx.ucShellPwdCheckFlag = VOS_TRUE;
        g_stSpWordCtx.ucErrTimes          = 0;

        /* 调用At_FormatResultData发送命令结果 */
        At_FormatResultData(ucIndex, AT_OK);
    }
    /* 密码校验失败，错误次数加1 */
    else
    {
        g_stSpWordCtx.ucErrTimes++;

        /* 调用At_FormatResultData发送命令结果 */
        At_FormatResultData(ucIndex, AT_ERROR);
    }

    return VOS_OK;
}

#endif
/*****************************************************************************
 函 数 名  : AT_RcvMmaCipherInfoQueryCnf
 功能描述  : AT_MMA_CIPHER_INFO_QUERY_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年02月02日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaCipherInfoQueryCnf(VOS_VOID *pMsg)
{
    TAF_MMA_CIPHER_QRY_CNF_STRU        *pstCipherQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    pstCipherQryCnf     = (TAF_MMA_CIPHER_QRY_CNF_STRU *)pMsg;
    ulResult            = AT_OK;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCipherQryCnf->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCipherInfoQueryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCipherInfoQueryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_CIPERQRY_READ */
    if (AT_CMD_CIPERQRY_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^CIPERQRY查询命令返回 */
    gstAtSendData.usBufLen = 0;
    if (VOS_OK != pstCipherQryCnf->ulResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR*)pgucAtSndCodeAddr,
                                                   "%s:%d",
                                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                   pstCipherQryCnf->ucCipherInfo);
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : AT_RcvMmaLocInfoQueryCnf
 功能描述  : AT_MMA_LOCATION_INFO_QUERY_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年02月02日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaLocInfoQueryCnf(VOS_VOID *pMsg)
{
    TAF_MMA_LOCATION_INFO_QRY_CNF_STRU *pstLocInfoCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    pstLocInfoCnf       = (TAF_MMA_LOCATION_INFO_QRY_CNF_STRU *)pMsg;
    usLength            = 0;
    ulResult            = AT_OK;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstLocInfoCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaLocInfoQueryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaLocInfoQueryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_LOCINFO_READ */
    if (AT_CMD_LOCINFO_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 使用AT_STOP_TIMER_CMD_READY恢复AT命令实体状态为READY状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^CIPERQRY查询命令返回 */
    if (VOS_OK != pstLocInfoCnf->ulResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s:",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        /* 上报MCC和MNC */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%X%X%X",
                                          (VOS_INT32)(pstLocInfoCnf->ulMcc & 0x0f) ,
                                          (VOS_INT32)(pstLocInfoCnf->ulMcc & 0x0f00) >> 8,
                                          (VOS_INT32)(pstLocInfoCnf->ulMcc & 0x0f0000) >> 16);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%X%X",
                                          (VOS_INT32)(pstLocInfoCnf->ulMnc & 0x0f) ,
                                          (VOS_INT32)(pstLocInfoCnf->ulMnc & 0x0f00) >> 8);

        /* MNC最后一位不等于F，则MNC为三位，否则为两位 */
        if (0x0f != ((pstLocInfoCnf->ulMnc & 0x0f0000) >> 16))
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%X",
                                          (VOS_INT32)(pstLocInfoCnf->ulMnc & 0x0f0000) >> 16);
        }

        /* Lac */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          ",0x%X",
                                          pstLocInfoCnf->usLac);

        /* Rac */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          ",0x%X",
                                          pstLocInfoCnf->ucRac);

        /* Cell ID */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          ",0x%X",
                                          pstLocInfoCnf->ulCellid);

        gstAtSendData.usBufLen = usLength;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentNvBackupStatQryRsp
 功能描述  : AT^NVBACKUPSTAT的查询回复处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年02月18日
    作    者   : l00198894
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentNvBackupStatQryRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_NVBACKUPSTAT_QRY_CNF_STRU    *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;
    VOS_UINT16                              usLength;

    /* 初始化消息变量 */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_NVBACKUPSTAT_QRY_CNF_STRU *)pRcvMsg->aucContent;
    usLength        = 0;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentNvBackupStatQryRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentNvBackupStatQryRsp: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_NVBACKUPSTAT_READ */
    if ( AT_CMD_NVBACKUPSTAT_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {
        if ( NV_OK == pstEvent->ulNvBackupStat )
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s: %d",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               VOS_TRUE);
        }
        else
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s: %d",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               VOS_FALSE);
        }

        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = usLength;
    /* 调用AT_FormATResultDATa发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentNandBadBlockQryRsp
 功能描述  : AT^NANDBBC的查询回复处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年02月18日
    作    者   : l00198894
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentNandBadBlockQryRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_NANDBBC_QRY_CNF_STRU         *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;
    VOS_UINT16                              usLength;
    VOS_UINT32                              uli;
    VOS_UINT32                              ulMaxBBNum;

    /* 初始化消息变量 */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_NANDBBC_QRY_CNF_STRU *)pRcvMsg->aucContent;
    usLength        = 0;
    uli             = 0;
    ulMaxBBNum      = 0;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentNandBadBlockQryRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentNandBadBlockQryRsp: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_NANDBBC_READ */
    if ( AT_CMD_NANDBBC_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: %d",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstEvent->ulBadBlockNum);

        ulMaxBBNum = (pstEvent->ulBadBlockNum > DRV_AGENT_NAND_BADBLOCK_MAX_NUM) ? DRV_AGENT_NAND_BADBLOCK_MAX_NUM : pstEvent->ulBadBlockNum;
        for (uli = 0; uli < ulMaxBBNum; uli++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s%s: %d",
                                               gaucAtCrLf,
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               pstEvent->aulBadBlockIndex[uli]);
        }

        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = usLength;
    /* 调用AT_FormATResultDATa发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentNandDevInfoQryRsp
 功能描述  : AT^NANDVER的查询回复处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年02月18日
    作    者   : l00198894
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentNandDevInfoQryRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_NANDVER_QRY_CNF_STRU         *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;
    VOS_UINT16                              usLength;

    /* 初始化消息变量 */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_NANDVER_QRY_CNF_STRU *)pRcvMsg->aucContent;
    usLength        = 0;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentNandDevInfoQryRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentNandDevInfoQryRsp: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_NANDVER_READ */
    if ( AT_CMD_NANDVER_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {
        /* 输出查询结果 */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: %d,\"%s\",%d,\"%s\"",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstEvent->stNandDevInfo.ulMufId,
                                           pstEvent->stNandDevInfo.aucMufName,
                                           pstEvent->stNandDevInfo.ulDevId,
                                           pstEvent->stNandDevInfo.aucDevSpec);

        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = usLength;
    /* 调用AT_FormATResultDATa发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentChipTempQryRsp
 功能描述  : AT^CHIPTEMP的查询回复处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年02月18日
    作    者   : l00198894
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentChipTempQryRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_CHIPTEMP_QRY_CNF_STRU    *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    /* 初始化消息变量 */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_CHIPTEMP_QRY_CNF_STRU *)pRcvMsg->aucContent;
    usLength        = 0;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentChipTempQryRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentChipTempQryRsp: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_CHIPTEMP_READ */
    if ( AT_CMD_CHIPTEMP_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {
        /* 输出查询结果 */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: %d,%d,%d,%d,%d",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstEvent->lGpaTemp,
                                           pstEvent->lWpaTemp,
                                           pstEvent->lLpaTemp,
                                           pstEvent->lSimTemp,
                                           pstEvent->lBatTemp);

        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = usLength;
    /* 调用AT_FormATResultDATa发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}




#ifndef __PS_WIN32_RECUR__
/*****************************************************************************
 函 数 名  : AT_RcvMmaOmMaintainInfoInd
 功能描述  : 处理来自MMA的PC工具可谓可测配置信息
 输入参数  : pstMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月24日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/

/* Modified by w00167002 for L-C互操作项目, 2014-2-21, begin */
VOS_UINT32 AT_RcvMmaOmMaintainInfoInd(
    VOS_VOID                           *pstMsg
)
{
    ATMMA_OM_MAINTAIN_INFO_IND_STRU    *pstOmMaintainInfo;

    pstOmMaintainInfo = (ATMMA_OM_MAINTAIN_INFO_IND_STRU*)pstMsg;

    if ( (VOS_TRUE == pstOmMaintainInfo->ucOmConnectFlg)
      && (VOS_TRUE == pstOmMaintainInfo->ucOmPcRecurEnableFlg) )
    {
        AT_MNTN_TraceContextData();
        AT_MNTN_TraceClientData();
    }

    return VOS_OK;
}
/* Modified by w00167002 for L-C互操作项目, 2014-2-21, end */
#endif

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentAntStateIndRsp
 功能描述  : ^ANTSTATE 查询回复处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2012年2月25日
    作    者   : w00184875
    修改内容   : 新生成函数
  2.日    期   : 2012年12月25日
    作    者   : l00227485
    修改内容   : DSDA PhaseII
  3.日    期   : 2013年5月30日
    作    者   : z60575
    修改内容   :DTS2013060307614, DSDA_SAR修改
  4.日    期   : 2013年8月2日
    作    者   : z60575
    修改内容   :DTS2013073103769,从C核查询天线状态
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentAntStateIndRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    VOS_UINT16                          usLength = 0;
    DRV_AGENT_ANT_STATE_IND_STRU       *pstAntState = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    gstAtSendData.usBufLen  = 0;
    pRcvMsg                 = (DRV_AGENT_MSG_STRU *)pMsg;
    pstAntState             = (DRV_AGENT_ANT_STATE_IND_STRU *)pRcvMsg->aucContent;
    ucIndex                 = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstAntState->stAtAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntStateIndRsp: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       "%s:%d%s",
                                       "^ANTSTATE",
                                       pstAntState->usAntState,
                                       gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);


    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentSetMaxLockTmsRsp
 功能描述  : DRV_AGENT_MAX_LOCK_TIMES_SET_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年03月19日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentSetMaxLockTmsRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                        *pRcvMsg;
    DRV_AGENT_MAX_LOCK_TMS_SET_CNF_STRU       *pstMaxlockTmsSetCnf;
    VOS_UINT8                                  ucIndex;

    /* 初始化消息 */
    pRcvMsg             = (DRV_AGENT_MSG_STRU *)pMsg;
    pstMaxlockTmsSetCnf = (DRV_AGENT_MAX_LOCK_TMS_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMaxlockTmsSetCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetMaxLockTmsRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetMaxLockTmsRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_MAXLCKTMS_SET */
    if (AT_CMD_MAXLCKTMS_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 使用AT_STOP_TIMER_CMD_READY恢复AT命令实体状态为READY状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^MAXLCKTMS设置命令返回 */
    if (VOS_OK != pstMaxlockTmsSetCnf->ulResult)
    {
        /* 调用At_FormatResultData发送命令结果 */
        At_FormatResultData(ucIndex, AT_DEVICE_OTHER_ERROR);
    }
    else
    {
        /* 调用At_FormatResultData发送命令结果 */
        At_FormatResultData(ucIndex, AT_OK);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentSetApSimstRsp
 功能描述  : DRV_AGENT_AT_DEACT_SIM_SET_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月18日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentSetApSimstRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                        *pRcvMsg;
    DRV_AGENT_AP_SIMST_SET_CNF_STRU           *pstApSimStSetCnf;
    VOS_UINT8                                  ucIndex;

    /* 初始化消息 */
    pRcvMsg             = (DRV_AGENT_MSG_STRU *)pMsg;
    pstApSimStSetCnf    = (DRV_AGENT_AP_SIMST_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstApSimStSetCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetApSimstRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetApSimstRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_APSIMST_SET */
    if (AT_CMD_APSIMST_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 使用AT_STOP_TIMER_CMD_READY恢复AT命令实体状态为READY状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^APSIMST设置命令返回 */
    if (VOS_OK != pstApSimStSetCnf->ulResult)
    {
        /* 调用At_FormatResultData发送命令结果 */
        At_FormatResultData(ucIndex, AT_ERROR);
    }
    else
    {
        /* 调用At_FormatResultData发送命令结果 */
        At_FormatResultData(ucIndex, AT_OK);
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentHukSetCnf
 功能描述  : ^HUK命令设置回复处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentHukSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_HUK_SET_CNF_STRU             *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;

    /* 初始化 */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_HUK_SET_CNF_STRU *)pRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    ulResult        = VOS_NULL;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentHukSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentHukSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_HUK_SET */
    if (AT_CMD_HUK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if (DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult)
    {
        /* 输出设置结果 */
        ulResult    = AT_OK;
    }
    else
    {
        /* 异常情况, 转换错误码 */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = 0;
    /* 调用AT_FormATResultDATa发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentFacAuthPubkeySetCnf
 功能描述  : ^FACAUTHPUBKEY命令设置回复处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentFacAuthPubkeySetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_FACAUTHPUBKEY_SET_CNF_STRU   *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;

    /* 初始化 */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_FACAUTHPUBKEY_SET_CNF_STRU *)pRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    ulResult        = VOS_NULL;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentFacAuthPubkeySetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentFacAuthPubkeySetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_FACAUTHPUBKEY_SET */
    if ( AT_CMD_FACAUTHPUBKEY_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* 输出设置结果 */
        ulResult    = AT_OK;
    }
    else
    {
        /* 异常情况, 转换错误码 */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = 0;
    /* 调用AT_FormATResultDATa发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentIdentifyStartSetCnf
 功能描述  : ^IDENTIFYSTART命令设置回复处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentIdentifyStartSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_IDENTIFYSTART_SET_CNF_STRU   *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;
    VOS_UINT16                              usLength;
    VOS_UINT32                              i;

    /* 初始化 */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_IDENTIFYSTART_SET_CNF_STRU *)pRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    usLength        = 0;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentIdentifyStartSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentIdentifyStartSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_IDENTIFYSTART_SET */
    if ( AT_CMD_IDENTIFYSTART_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* 输出设置结果 */
        ulResult    = AT_OK;
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s: ",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        for (i = 0; i < DRV_AGENT_RSA_CIPHERTEXT_LEN; i++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%02X",
                                          pstEvent->aucRsaText[i]);
        }
    }
    else
    {
        /* 异常情况, 转换错误码 */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = usLength;
    /* 调用AT_FormATResultDATa发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentIdentifyEndSetCnf
 功能描述  : ^IDENTIFYEND命令设置回复处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentIdentifyEndSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_IDENTIFYEND_SET_CNF_STRU     *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;

    /* 初始化消息变量 */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_IDENTIFYEND_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentIdentifyEndSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentIdentifyEndSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_IDENTIFYEND_SET */
    if ( AT_CMD_IDENTIFYEND_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* 输出设置结果 */
        ulResult    = AT_OK;
    }
    else
    {
        /* 异常情况, 转换错误码 */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = 0;
    /* 调用AT_FormATResultDATa发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentSimlockDataWriteSetCnf
 功能描述  : ^SIMLOCKDATAWRITE命令设置回复处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentSimlockDataWriteSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                         *pRcvMsg;
    DRV_AGENT_SIMLOCKDATAWRITE_SET_CNF_STRU    *pstEvent;
    VOS_UINT8                                   ucIndex;
    VOS_UINT32                                  ulResult;

    /* 初始化消息变量 */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_SIMLOCKDATAWRITE_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentSimlockDataWriteSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSimlockDataWriteSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_SIMLOCKDATAWRITE_SET */
    if ( AT_CMD_SIMLOCKDATAWRITE_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* 输出设置结果 */
        ulResult    = AT_OK;
    }
    else
    {
        /* 异常情况, 转换错误码 */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = 0;
    /* 调用AT_FormATResultDATa发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_Num2AsciiNum
 功能描述  : 十进制或十六进制数字转ASCII码
 输入参数  : VOS_UINT8          ucNum           -- 待转换数字
 输出参数  : 无
 返 回 值  : VOS_CHAR       -- 转换后的ASCII码，失败返回'*'
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月28日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
VOS_CHAR AT_Num2AsciiNum(VOS_UINT8 ucNum)
{
    if (9 >= ucNum)
    {
        return (VOS_CHAR)('0' + ucNum);
    }
    else if (0x0F >= ucNum)
    {
        return (VOS_CHAR)('A' + (ucNum - 0x0A));
    }
    else
    {
        return '*';
    }
}

/*****************************************************************************
 函 数 名  : AT_CheckSimlockCodeLast2Char
 功能描述  : 检查锁网锁卡号码字符串最后两位的合法性
 输入参数  : DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8   enCategory
 输出参数  : VOS_CHAR          *pcStrLast2Char        -- 检查后的最后两个字符
 返 回 值  : VOS_OK     -- 检查成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月14日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
VOS_UINT32 AT_CheckSimlockCodeLast2Char(
    DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8   enCategory,
    VOS_CHAR                                       *pcStrLast2Char
)
{
    VOS_UINT8                           i           = 0;

    /* 检测最后两位的有效性, NET无需检测 */
    if (DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK < enCategory)
    {
        for (i = 0; i < 2; i++)
        {
            /* NETSUB支持范围: 0x00~0x99 */
            if ( ('0' <= pcStrLast2Char[i]) && ('9' >= pcStrLast2Char[i]) )
            {
                continue;
            }
            /* SP支持范围: 0x00~0xFF */
            else if ( (DRV_AGENT_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER == enCategory)
                   && ('A' <= pcStrLast2Char[i]) && ('F' >= pcStrLast2Char[i]) )
            {
                continue;
            }
            else
            {
                return VOS_ERR;
            }
        }
    }

    return VOS_OK;

}


/*****************************************************************************
 函 数 名  : AT_CheckSimlockCodeStr
 功能描述  : 检查锁网锁卡号码字符串合法性，并补充字符串结束符
 输入参数  : DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8   enCategory
 输出参数  : VOS_CHAR          *pcStrCode       -- 检查后的字符串
 返 回 值  : VOS_OK     -- 检查成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月14日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
VOS_UINT32 AT_CheckSimlockCodeStr(
    DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8   enCategory,
    VOS_CHAR                                       *pcStrCode
)
{
    VOS_UINT8                           i           = 0;
    VOS_UINT8                           j           = 0;
    VOS_UINT8                           ucLen;              /* 锁网号码长度 */
    VOS_CHAR                           *pcTmpStr;

    pcTmpStr    = pcStrCode;

    switch(enCategory)
    {
        case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK:
            ucLen = AT_PERSONALIZATION_NET_CODE_LEN;
            break;
        default:
            ucLen = AT_PERSONALIZATION_CODE_LEN;
            break;
    }

    /* 检测PLMN合法性及其位数 */
    for (i = 0; i < AT_PERSONALIZATION_NET_CODE_LEN; i++)
    {
        if ( ('0' <= pcTmpStr[i]) && ('9' >= pcTmpStr[i]) )
        {
            continue;
        }
        else if ( ((AT_PERSONALIZATION_NET_CODE_LEN - 1) == i)
               && ('F' == pcTmpStr[i]) )
        {
            for (j = i + 1; j < ucLen; j++)
            {
                pcTmpStr[j - 1] = pcTmpStr[j];
            }
            ucLen = ucLen - 1;
            break;
        }
        else
        {
            return VOS_ERR;
        }
    }

    pcTmpStr[ucLen] = 0;

    /* 检测锁网锁卡号码最后两位的合法性 */
    if (VOS_OK != AT_CheckSimlockCodeLast2Char(enCategory, &pcTmpStr[ucLen - 2]))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_SimlockCodeBcd2Str
 功能描述  : 锁网锁卡号段BCD码转字符串
 输入参数  : DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8   enCategory
             VOS_UINT8         *pucBcdNum       -- 待转换号段BCD码
 输出参数  : VOS_CHAR          *pcStrNum        -- 转换后的字符串
 返 回 值  : VOS_OK     -- 转换成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
VOS_UINT32 AT_SimlockCodeBcd2Str(
    DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8   enCategory,
    VOS_UINT8                                      *pucBcdNum,
    VOS_CHAR                                       *pcStrNum
)
{
    VOS_UINT8                           i               = 0;
    VOS_UINT8                           ucDecodeLen;
    VOS_UINT8                           ucFirstNum;
    VOS_UINT8                           ucSecondNum;
    VOS_CHAR                           *pcStrTmp        = pcStrNum;
    VOS_CHAR                            cTmpChar;

    switch(enCategory)
    {
        case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK:
            ucDecodeLen = AT_PERSONALIZATION_NET_CODE_BCD_LEN;
            break;
        case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK_SUBSET:
            ucDecodeLen = AT_PERSONALIZATION_SUBNET_CODE_BCD_LEN;
            break;
        case DRV_AGENT_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER:
            ucDecodeLen = AT_PERSONALIZATION_SP_CODE_BCD_LEN;
            break;
        default:
            return VOS_ERR;
    }

    /* 对锁网锁卡号码进行高低字节转换 */
    for (i = 0; i < ucDecodeLen; i++)
    {
        /* 分别取出高低字节 */
        ucFirstNum  = (VOS_UINT8)((*(pucBcdNum + i)) & 0x0F);
        ucSecondNum = (VOS_UINT8)(((*(pucBcdNum + i)) >> 4) & 0x0F);

        *pcStrTmp++ = AT_Num2AsciiNum(ucFirstNum);
        *pcStrTmp++ = AT_Num2AsciiNum(ucSecondNum);
    }

    /* 将第四位号码后移到第六位(与产线对接) */
    pcStrTmp        = &pcStrNum[AT_PERSONALIZATION_CODE_FOURTH_CHAR_INDEX];
    cTmpChar        = pcStrTmp[0];
    pcStrTmp[0]     = pcStrTmp[1];
    pcStrTmp[1]     = pcStrTmp[2];
    pcStrTmp[2]     = cTmpChar;

    /* 对高低字节转换后的锁网锁卡号码进行合法性检查 */
    if (VOS_OK != AT_CheckSimlockCodeStr(enCategory, pcStrNum))
    {
        return VOS_ERR;
    }

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : AT_PhoneSimlockInfoPrint
 功能描述  : 锁网锁卡信息打印函数
 输入参数  : DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF_STRU    *pstPhoneSimlockInfo
             VOS_UINT8                                   ucIndex
             VOS_UINT16                                 *pusLength
 输出参数  : 无
 返 回 值  : VOS_UINT16     -- 打印字符串长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增函数
  2.日    期   : 2012年8月10日
    作    者   : y00213812
    修改内容   : DTS2012082204471, TQE清理，AT_PhoneSimlockInfoPrint第二个参数
                 由数据结构改为数据结构指针
*****************************************************************************/
VOS_UINT32 AT_PhoneSimlockInfoPrint(
    DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF_STRU    *pstPhoneSimlockInfo,
    VOS_UINT8                                   ucIndex,
    VOS_UINT16                                 *pusLength
)
{
    VOS_UINT16                                  usLength        = *pusLength;
    VOS_UINT8                                   ucCatIndex      = 0;
    VOS_UINT8                                   ucGroupIndex    = 0;
    VOS_CHAR                                    acCodeBegin[AT_PERSONALIZATION_CODE_LEN + 1];
    VOS_CHAR                                    acCodeEnd[AT_PERSONALIZATION_CODE_LEN + 1];
    VOS_UINT32                                  ucCodeBeginRslt;
    VOS_UINT32                                  ucCodeEndRslt;

    PS_MEM_SET(acCodeBegin,    0x00,   (AT_PERSONALIZATION_CODE_LEN + 1));
    PS_MEM_SET(acCodeEnd,      0x00,   (AT_PERSONALIZATION_CODE_LEN + 1));
    ucCodeBeginRslt = VOS_NULL;
    ucCodeEndRslt   = VOS_NULL;

    for (ucCatIndex = 0; ucCatIndex < DRV_AGENT_SUPPORT_CATEGORY_NUM; ucCatIndex++)
    {
        if (0 != ucCatIndex)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s",
                                               gaucAtCrLf);
        }

        /* ^PHONESIMLOCKINFO: <cat>,<indicator> [,(<code_begin>,<code_end>)...] */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: ",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        switch (pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].enCategory)
        {
            case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "NET");
                break;
            case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK_SUBSET:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "NETSUB");
                break;
            case DRV_AGENT_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "SP");
                break;
            case DRV_AGENT_PERSONALIZATION_CATEGORY_CORPORATE:
            case DRV_AGENT_PERSONALIZATION_CATEGORY_SIM_USIM:
            default:
                return VOS_ERR;
        }
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",%d",
                                           pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].enIndicator);
        if (DRV_AGENT_PERSONALIZATION_INDICATOR_ACTIVE == pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].enIndicator)
        {
            for (ucGroupIndex = 0; ucGroupIndex < pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].ucGroupNum; ucGroupIndex++)
            {
                ucCodeBeginRslt = AT_SimlockCodeBcd2Str(pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].enCategory,
                                                        pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].astLockCode[ucGroupIndex].aucPhLockCodeBegin,
                                                        acCodeBegin);
                ucCodeEndRslt   = AT_SimlockCodeBcd2Str(pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].enCategory,
                                                        pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].astLockCode[ucGroupIndex].aucPhLockCodeEnd,
                                                        acCodeEnd);
                if ( (VOS_OK == ucCodeBeginRslt)
                  && (VOS_OK == ucCodeEndRslt) )
                {
                    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                       ",(%s,%s)",
                                                       acCodeBegin,
                                                       acCodeEnd);
                }
                else
                {
                    return VOS_ERR;
                }
            }
        }

    }
    *pusLength = usLength;
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentPhoneSimlockInfoQryCnf
 功能描述  : ^PHONESIMLOCKINFO命令查询回复处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增函数
  2.日    期   : 2012年8月10日
    作    者   : y00213812
    修改内容   : DTS2012082204471, TQE清理，AT_PhoneSimlockInfoPrint第二个参数
                 由数据结构改为数据结构指针
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentPhoneSimlockInfoQryCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                         *pRcvMsg;
    DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF_STRU    *pstEvent;
    VOS_UINT8                                   ucIndex;
    VOS_UINT32                                  ulResult;
    VOS_UINT16                                  usLength;

    /* 初始化消息变量 */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    usLength        = 0;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentPhoneSimlockInfoQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentPhoneSimlockInfoQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_PHONESIMLOCKINFO_READ */
    if ( AT_CMD_PHONESIMLOCKINFO_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* 输出设置结果 */
        ulResult    = AT_OK;
        /* 打印结果 */
        /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, begin*/
        if (VOS_OK != AT_PhoneSimlockInfoPrint(pstEvent, ucIndex, &usLength))
        {
            ulResult = AT_PERSONALIZATION_OTHER_ERROR;
        }
    }   /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, end*/
    else
    {
        /* 异常情况, 转换错误码 */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = usLength;
    /* 调用AT_FormATResultDATa发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_SimlockDataReadPrint
 功能描述  : 锁网锁卡安全数据打印函数
 输入参数  : DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF_STRU     stSimlockDataRead
             VOS_UINT8                                  ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT16  *pusLength   -- 打印字符串长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
VOS_UINT32 AT_SimlockDataReadPrint(
    DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF_STRU      stSimlockDataRead,
    VOS_UINT8                                   ucIndex,
    VOS_UINT16                                 *pusLength
)
{
    VOS_UINT16                                  usLength        = *pusLength;
    VOS_UINT8                                   ucCatIndex      = 0;

    for (ucCatIndex = 0; ucCatIndex < DRV_AGENT_SUPPORT_CATEGORY_NUM; ucCatIndex++)
    {
        if (0 != ucCatIndex)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s",
                                               gaucAtCrLf);
        }

        /* ^SIMLOCKDATAREAD: <cat>,<indicator>,<lock_status>,<max_times>,<remain_times> */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: ",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        switch(stSimlockDataRead.astCategoryData[ucCatIndex].enCategory)
        {
            case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "NET");
                break;
            case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK_SUBSET:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "NETSUB");
                break;
            case DRV_AGENT_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "SP");
                break;
            case DRV_AGENT_PERSONALIZATION_CATEGORY_CORPORATE:
            case DRV_AGENT_PERSONALIZATION_CATEGORY_SIM_USIM:
            default:
                return VOS_ERR;
        }
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",%d",
                                           stSimlockDataRead.astCategoryData[ucCatIndex].enIndicator);
        if (DRV_AGENT_PERSONALIZATION_INDICATOR_ACTIVE == stSimlockDataRead.astCategoryData[ucCatIndex].enIndicator)
        {
            switch (stSimlockDataRead.astCategoryData[ucCatIndex].enStatus)
            {
            case DRV_AGENT_PERSONALIZATION_STATUS_READY:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   ",READY,,");
                break;
            case DRV_AGENT_PERSONALIZATION_STATUS_PIN:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   ",PIN,%d,%d",
                                                   stSimlockDataRead.astCategoryData[ucCatIndex].ucMaxUnlockTimes,
                                                   stSimlockDataRead.astCategoryData[ucCatIndex].ucRemainUnlockTimes);
                break;
            case DRV_AGENT_PERSONALIZATION_STATUS_PUK:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   ",PUK,,");
                break;
            default:
                return VOS_ERR;
            }
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               ",,,");
        }

    }
    *pusLength = usLength;
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentSimlockDataReadQryCnf
 功能描述  : ^SIMLOCKDATAREAD命令查询回复处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增函数
  2.日    期   : 2015年4月7日
    作    者   : w00316404
    修改内容   : M project A characeristic AT part
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentSimlockDataReadQryCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                         *pRcvMsg;
    DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF_STRU     *pstEvent;
    VOS_UINT8                                   ucIndex;
    VOS_UINT8                                   ucSimlockType;
    VOS_UINT32                                  ulResult;
    VOS_UINT16                                  usLength;

    /* 初始化消息变量 */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    ucSimlockType   = (VOS_UINT8)AT_GetSimlockUnlockCategoryFromClck();
    usLength        = 0;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentSimlockDataReadQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSimlockDataReadQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_SIMLOCKDATAREAD_READ或者为AT_CMD_CLCK_SIMLOCKDATAREAD_READ */
    if ( AT_CMD_SIMLOCKDATAREAD_READ != gastAtClientTab[ucIndex].CmdCurrentOpt
      && AT_CMD_CLCK_SIMLOCKDATAREAD != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 判断查询操作是否成功 */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* 输出设置结果 */
        ulResult    = AT_OK;
        /* 打印结果 */
        if ( AT_CMD_CLCK_SIMLOCKDATAREAD != gastAtClientTab[ucIndex].CmdCurrentOpt)
        {
            if ( VOS_OK != AT_SimlockDataReadPrint(*pstEvent, ucIndex, &usLength))
            {
                ulResult = AT_PERSONALIZATION_OTHER_ERROR;
            }
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%s: %d",
                                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                   pstEvent->astCategoryData[ucSimlockType].enIndicator);
        }
    }
    else
    {
        /* 异常情况, 转换错误码 */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = usLength;

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 调用AT_FormATResultDATa发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentPhonePhynumSetCnf
 功能描述  : ^SIMLOCKINFO命令设置回复处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentPhonePhynumSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_PHONEPHYNUM_SET_CNF_STRU *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* 初始化消息变量 */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_PHONEPHYNUM_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentPhonePhynumSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentPhonePhynumSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_PHONEPHYNUM_SET */
    if ( AT_CMD_PHONEPHYNUM_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* 输出设置结果 */
        ulResult    = AT_OK;
    }
    else
    {
        /* 异常情况, 转换错误码 */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = 0;
    /* 调用AT_FormATResultDATa发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentPhonePhynumQryCnf
 功能描述  : ^PHONEPHYNUM命令查询回复处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentPhonePhynumQryCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_PHONEPHYNUM_QRY_CNF_STRU *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT32                          i;

    /* 初始化消息变量 */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_PHONEPHYNUM_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    usLength        = 0;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentPhonePhynumQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentPhonePhynumQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_PHONEPHYNUM_READ */
    if ( AT_CMD_PHONEPHYNUM_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        ulResult    = AT_OK;
        /* 格式化输出查询结果 */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s: IMEI,",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        for (i = 0; i < DRV_AGENT_RSA_CIPHERTEXT_LEN; i++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%02X",
                                          pstEvent->aucImeiRsa[i]);
        }
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s%s: SN,",
                                           gaucAtCrLf,
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        for (i = 0; i < DRV_AGENT_RSA_CIPHERTEXT_LEN; i++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%02X",
                                          pstEvent->aucSnRsa[i]);
        }
    }
    else
    {
        /* 异常情况, 转换错误码 */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = usLength;
    /* 调用AT_FormATResultDATa发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_PortCtrlTmpSndMsg
 功能描述  : 密码校验通过之后发送OM和HSIC关联请求函数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_OK  设置或查询操作成功
             VOS_ERR 设置或查询操作失败
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012年04月10日
    作    者   : y00213812
    修改内容   : AP-Modem锁网锁卡项目新增函数

 *****************************************************************************/
VOS_UINT32  AT_PortCtrlTmpSndMsg(VOS_VOID)
{
    OM_HSIC_CONNECT_MSG_STRU           *pstMsg;

    pstMsg = (OM_HSIC_CONNECT_MSG_STRU*)PS_ALLOC_MSG(WUEPS_PID_AT,
                                                     sizeof(OM_HSIC_CONNECT_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        return AT_ERROR;
    }

    pstMsg->ulReceiverPid  = MSP_PID_DIAG_APP_AGENT;
    pstMsg->ulMsgName      = AT_OM_HSIC_PORT_CONNECT;

    if (VOS_OK !=  PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        return AT_ERROR;
    }

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentPortctrlTmpSetCnf
 功能描述  : ^PORTCTRLTMP命令设置回复处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentPortctrlTmpSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_PORTCTRLTMP_SET_CNF_STRU *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* 初始化消息变量 */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_PORTCTRLTMP_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentPortctrlTmpSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentPortctrlTmpSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_PORTCTRLTMP_SET */
    if ( AT_CMD_PORTCTRLTMP_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* 给OM发消息打开OM端口 */
        ulResult    = AT_PortCtrlTmpSndMsg();
        if ( AT_OK != ulResult)
        {
             ulResult    = AT_ERROR;
        }
    }
    else
    {
        /* 输出设置结果, 转换错误码 */
        ulResult         = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;;
    }

    gstAtSendData.usBufLen = 0;
    /* 调用AT_FormATResultDATa发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentPortAttribSetCnf
 功能描述  : ^PORTATTRIBSET命令设置回复处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentPortAttribSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                   *pRcvMsg;
    DRV_AGENT_PORTATTRIBSET_SET_CNF_STRU *pstEvent;
    VOS_UINT8                             ucIndex;
    VOS_UINT32                            ulResult;

    /* 初始化消息变量 */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_PORTATTRIBSET_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentPortAttribSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentPortAttribSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_PORTATTRIBSET_SET */
    if ( AT_CMD_PORTATTRIBSET_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        ulResult    = AT_OK;
    }
    else
    {
        /* 输出设置结果, 转换错误码 */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = 0;
    /* 调用AT_FormATResultDATa发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentPortAttribSetQryCnf
 功能描述  : ^PORTATTRIBSET命令查询回复处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentPortAttribSetQryCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                                     *pRcvMsg;
    DRV_AGENT_PORTATTRIBSET_QRY_CNF_STRU                   *pstEvent;
    VOS_UINT8                                               ucIndex;
    VOS_UINT32                                              ulResult;

    /* 初始化消息变量 */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_PORTATTRIBSET_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentPortAttribSetQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentPortAttribSetQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_PORTATTRIBSET_READ */
    if ( AT_CMD_PORTATTRIBSET_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    /* 判断查询操作是否成功 */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        if( (DRV_AGENT_PORT_STATUS_OFF  == pstEvent->enPortStatus)
         || (DRV_AGENT_PORT_STATUS_ON   == pstEvent->enPortStatus))
        {
            ulResult = AT_OK;
            gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstEvent->enPortStatus);
        }
        else
        {
            ulResult = AT_PERSONALIZATION_OTHER_ERROR;
        }
    }
    else
    {
        /* 输出设置结果, 转换错误码 */
        ulResult = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    /* 调用AT_FormATResultDATa发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentOpwordSetCnf
 功能描述  : ^OPWORD命令设置回复处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月18日
    作    者   : y00213812
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentOpwordSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                      *pRcvMsg;
    DRV_AGENT_OPWORD_SET_CNF_STRU           *pstEvent;
    VOS_UINT8                                ucIndex;
    VOS_UINT32                               ulResult;

    /* 初始化消息变量 */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_OPWORD_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentOpwordSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentOpwordSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_OPWORD_SET */
    if ( AT_CMD_OPWORD_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* 密码比对成功，获取权限 */
        g_enATE5RightFlag   = AT_E5_RIGHT_FLAG_YES;
        ulResult            = AT_OK;
    }
    else
    {
        /* 输出设置结果, 转换错误码 */
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;
    /* 调用AT_FormATResultDATa发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentAntSwitchSetCnf
 功能描述  : 响应ANTSWITCH设置处理结果
 输入参数  : VOS_VOID *pMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月1日
    作    者   : y00258578
    修改内容   : 新加函数
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentAntSwitchSetCnf(VOS_VOID *pstData)
{
    VOS_UINT8                           ucIndex = 0;
    DRV_AGENT_ANTSWITCH_SET_CNF_STRU   *pstAntSwitchCnf;
    DRV_AGENT_MSG_STRU                 *pRcvMsg;

    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pstData;
    pstAntSwitchCnf = (DRV_AGENT_ANTSWITCH_SET_CNF_STRU *)pRcvMsg->aucContent;
    /* 根据ClientID获取通道索引 */
    if(AT_FAILURE == At_ClientIdToUserId(pstAntSwitchCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntSwitchSetCnf: Get Index Fail!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntSwitchSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* AT模块在等待^ANTSWITCH命令的操作结果事件上报 */
    if (AT_CMD_ANTSWITCH_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntSwitchSetCnf: Error Option!");
        return VOS_ERR;
    }

    /* 使用AT_STOP_TIMER_CMD_READY恢复AT命令实体状态为READY状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_OK != pstAntSwitchCnf->ulResult)
    {
        At_FormatResultData(ucIndex, AT_ERROR);
    }
    else
    {
        At_FormatResultData(ucIndex, AT_OK);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvDrvAgentAntSwitchQryCnf
 功能描述  : 响应ANTSWITCH查询处理结果
 输入参数  : VOS_VOID *pMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月1日
    作    者   : y00258578
    修改内容   : 新加函数
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentAntSwitchQryCnf(VOS_VOID *pstData)
{
    VOS_UINT8                           ucIndex = 0;
    DRV_AGENT_ANTSWITCH_QRY_CNF_STRU   *pstAntSwitchCnf;
    DRV_AGENT_MSG_STRU                 *pRcvMsg;

    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pstData;
    pstAntSwitchCnf = (DRV_AGENT_ANTSWITCH_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* 根据ClientID获取通道索引 */
    if(AT_FAILURE == At_ClientIdToUserId(pstAntSwitchCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntSwitchQryCnf: Get Index Fail!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntSwitchQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* AT模块在等待^ANTSWITCH命令的操作结果事件上报 */
    if (AT_CMD_ANTSWITCH_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntSwitchQryCnf: Error Option!");
        return VOS_ERR;
    }

    /* 使用AT_STOP_TIMER_CMD_READY恢复AT命令实体状态为READY状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = 0;

    if(pstAntSwitchCnf->ulResult == VOS_OK)
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstAntSwitchCnf->ulState);

        At_FormatResultData(ucIndex, AT_OK);
    }
    else
    {
        At_FormatResultData(ucIndex, AT_ERROR);
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_RcvMtaCposSetCnf
 功能描述  : +CPOS命令设置回复处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月28日
    作    者   : y00213812
    修改内容   : V7R1C50 A-GPS项目新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaCposSetCnf(VOS_VOID *pMsg)
{
    /* 定义局部变量 */
    AT_MTA_MSG_STRU                  *pstCposMsg;
    MTA_AT_CPOS_CNF_STRU             *pstEvent;
    VOS_UINT8                         ucIndex;
    VOS_UINT32                        ulResult;

    /* 初始化消息变量 */
    pstCposMsg  = (AT_MTA_MSG_STRU*)pMsg;
    pstEvent    = (MTA_AT_CPOS_CNF_STRU*)pstCposMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCposMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaCposSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaCposSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_CPOS_SET */
    if ( AT_CMD_CPOS_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaCposSetCnf: WARNING:Not AT_CMD_CPOS_SET!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if ( MTA_AT_RESULT_NO_ERROR == pstEvent->enResult )
    {
        ulResult            = AT_OK;
    }
    else
    {
        ulResult            = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;
    /* 调用AT_FormatResultDATa发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaCposrInd
 功能描述  : +CPOSR主动上报命令处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月28日
    作    者   : y00213812
    修改内容   : V7R1C50 A-GPS项目新增函数
  2.日    期   : 2013年2月20日
    作    者   : l60609
    修改内容   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 AT_RcvMtaCposrInd(VOS_VOID *pMsg)
{
    /* 定义局部变量 */
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstCposrMsg;
    MTA_AT_CPOSR_IND_STRU              *pstEvent;
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx = VOS_NULL_PTR;

    /* 初始化消息变量 */
    pstCposrMsg = (AT_MTA_MSG_STRU*)pMsg;
    pstEvent    = (MTA_AT_CPOSR_IND_STRU*)pstCposrMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstCposrMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaCposrInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    pstAgpsCtx = AT_GetModemAgpsCtxAddrFromClientId(ucIndex);

    /* 根据当前的AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->enCposrReport的值判断是否允许主动上报辅助数据和指示 */
    if (AT_CPOSR_ENABLE == pstAgpsCtx->enCposrReport)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s+CPOSR: %s%s",
                                                        gaucAtCrLf, pstEvent->acXmlText, gaucAtCrLf);

        At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaXcposrRptInd
 功能描述  : ^XCPOSRRPT主动上报命令处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月28日
    作    者   : y00213812
    修改内容   : V7R1C50 A-GPS项目新增函数
  2.日    期   : 2013年2月20日
    作    者   : l60609
    修改内容   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 AT_RcvMtaXcposrRptInd(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstXcposrRptMsg;
    MTA_AT_XCPOSRRPT_IND_STRU          *pstEvent;
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx = VOS_NULL_PTR;

    /* 初始化消息变量 */
    pstXcposrRptMsg = (AT_MTA_MSG_STRU*)pMsg;
    pstEvent        = (MTA_AT_XCPOSRRPT_IND_STRU*)pstXcposrRptMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstXcposrRptMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaXcposrRptInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    pstAgpsCtx = AT_GetModemAgpsCtxAddrFromClientId(ucIndex);

    /* 根据当前的AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->enXcposrReport的值判断是否允许上报主动清除申请 */
    if (AT_XCPOSR_ENABLE == pstAgpsCtx->enXcposrReport)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "^XCPOSRRPT: %d",
                                                        pstEvent->ulClearFlg);

        At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaCgpsClockSetCnf
 功能描述  : ^CGPSCLOCK命令设置回复处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月28日
    作    者   : y00213812
    修改内容   : V7R1C50 A-GPS项目新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaCgpsClockSetCnf(VOS_VOID *pMsg)
{
    /* 定义局部变量 */
    AT_MTA_MSG_STRU                  *pRcvMsg;
    MTA_AT_CGPSCLOCK_CNF_STRU        *pstEvent;
    VOS_UINT8                         ucIndex;
    VOS_UINT32                        ulResult;
    /* 初始化消息变量 */
    pRcvMsg = (AT_MTA_MSG_STRU*)pMsg;
    pstEvent = (MTA_AT_CGPSCLOCK_CNF_STRU*)pRcvMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaCgpsClockSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaCgpsClockSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_CGPSCLOCK_SET */
    if ( AT_CMD_CGPSCLOCK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaCgpsClockSetCnf: WARNING:Not AT_CMD_CGPSCLOCK_SET!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if ( MTA_AT_RESULT_NO_ERROR == pstEvent->enResult )
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;
    /* 调用AT_FormATResultDATa发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : At_ProcMtaMsg
 功能描述  : 处理来自MTA模块的消息
 输入参数  : MTA_MSG_STRU *pMsg
 输出参数  : 无
 返 回 值  : TAF_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月28日
    作    者   : y00213812
    修改内容   : V7R1C50 A-GPS项目新增函数

*****************************************************************************/
VOS_VOID At_ProcMtaMsg(AT_MTA_MSG_STRU *pstMsg)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulMsgId;
    VOS_UINT32                          ulRst;

    /*从g_astAtProcMsgFromMtaTab中获取消息个数*/
    ulMsgCnt = sizeof(g_astAtProcMsgFromMtaTab)/sizeof(AT_PROC_MSG_FROM_MTA_STRU);

    /*从消息包中获取MSG ID*/
    ulMsgId  = ((AT_MTA_MSG_STRU *)pstMsg)->ulMsgId;

    /*g_astAtProcMsgFromMtaTab查表，进行消息分发*/
    for (i = 0; i < ulMsgCnt; i++)
    {
        if (g_astAtProcMsgFromMtaTab[i].ulMsgType == ulMsgId)
        {
            ulRst = g_astAtProcMsgFromMtaTab[i].pProcMsgFunc(pstMsg);

            if (VOS_ERR == ulRst)
            {
                AT_ERR_LOG("At_ProcMtaMsg: Msg Proc Err!");
            }

            return;
        }
    }

    /*没有找到匹配的消息*/
    if (ulMsgCnt == i)
    {
        AT_ERR_LOG("At_ProcMtaMsg: Msg Id is invalid!");
    }

    return;
}

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))
/*****************************************************************************
 函 数 名  : AT_ProcXpdsMsg
 功能描述  : AT处理XPDS模块发送来的消息
 输入参数  : AT_XPDS_MSG_STRU *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月2日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_ProcXpdsMsg(AT_XPDS_MSG_STRU *pstMsg)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulMsgId;
    VOS_UINT32                          ulRst;

    /*从g_astAtProcMsgFromXpdsTab中获取消息个数*/
    ulMsgCnt = sizeof(g_astAtProcMsgFromXpdsTab)/sizeof(AT_PROC_MSG_FROM_XPDS_STRU);

    /*从消息包中获取MSG ID*/
    ulMsgId  = ((AT_XPDS_MSG_STRU *)pstMsg)->ulMsgId;

    /*g_astAtProcMsgFromXpdsTab查表，进行消息分发*/
    for (i = 0; i < ulMsgCnt; i++)
    {
        if (g_astAtProcMsgFromXpdsTab[i].ulMsgType == ulMsgId)
        {
            ulRst = g_astAtProcMsgFromXpdsTab[i].pProcMsgFunc(pstMsg);

            if (VOS_ERR == ulRst)
            {
                AT_ERR_LOG("AT_ProcXpdsMsg: Msg Proc Err!");
            }

            return;
        }
    }

    /*没有找到匹配的消息*/
    if (ulMsgCnt == i)
    {
        AT_ERR_LOG("At_ProcXpdsMsg: Msg Id is invalid!");
    }

    return;
}

#endif

/*****************************************************************************
 函 数 名  : AT_RcvMtaApSecSetCnf
 功能描述  : AT模块收到MTA模块消息处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月31日
    作    者   : 李紫剑/00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaApSecSetCnf( VOS_VOID *pMsg )
{
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_APSEC_CNF_STRU              *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulLoop;

    /* 初始化 */
    pstRcvMsg       = (AT_MTA_MSG_STRU *)pMsg;
    pstEvent        = (MTA_AT_APSEC_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    usLength        = 0;

    /* 通过ClientId获取ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaApSecSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaApSecSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_APSEC_SET */
    if (AT_CMD_APSEC_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaApSecSetCnf: NOT CURRENT CMD OPTION!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断回复消息中的错误码 */
    if (MTA_AT_RESULT_NO_ERROR == pstEvent->enResult)
    {
        /* 输出设置结果 */
        ulResult    = AT_OK;

        /* 处理成功，输出安全封包，打印结果 */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: ",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        for (ulLoop = 0; ulLoop < pstEvent->ulSPLen; ulLoop++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%02X",
                                               pstEvent->aucSecPacket[ulLoop]);
        }
    }
    else
    {
        /* 异常情况, 输出ERROR */
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = usLength;

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaSimlockUnlockSetCnf
 功能描述  : AT模块收到MTA模块消息处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年09月19日
    作    者   : 李紫剑/00198894
    修改内容   : 新生成函数
  2.日    期   : 2015年4月7日
    作    者   : w00316404
    修改内容   : M project A characeristic AT part
*****************************************************************************/
VOS_UINT32 AT_RcvMtaSimlockUnlockSetCnf( VOS_VOID *pMsg )
{
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_SIMLOCKUNLOCK_CNF_STRU      *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* 初始化 */
    pstRcvMsg       = (AT_MTA_MSG_STRU *)pMsg;
    pstEvent        = (MTA_AT_SIMLOCKUNLOCK_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* 通过ClientId获取ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSimlockUnlockSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSimlockUnlockSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_SIMLOCKUNLOCK_SET或者为AT_CMD_CLCK_SIMLOCKUNLOCK_SET */
    if (AT_CMD_SIMLOCKUNLOCK_SET    != gastAtClientTab[ucIndex].CmdCurrentOpt
     && AT_CMD_CLCK_SIMLOCKUNLOCK   != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSimlockUnlockSetCnf: NOT CURRENT CMD OPTION!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断回复消息中的错误码 */
    if (MTA_AT_RESULT_NO_ERROR == pstEvent->enResult)
    {
        /* 解锁成功，输出OK */
        ulResult    = AT_OK;
    }
    else
    {
        /* 解锁失败，输出ERROR */
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaQryNmrCnf
 功能描述  : AT模块收到ID_MTA_AT_QRY_NMR_CNF模块消息处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月21日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaQryNmrCnf( VOS_VOID *pMsg )
{
    AT_MTA_MSG_STRU                    *pRcvMsg      = VOS_NULL_PTR;
    MTA_AT_QRY_NMR_CNF_STRU            *pstQryNmrCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulNmrDataIndex;
    VOS_UINT16                          usLength;

    /* 初始化 */
    pRcvMsg      = (AT_MTA_MSG_STRU *)pMsg;
    pstQryNmrCnf = (MTA_AT_QRY_NMR_CNF_STRU *)(pRcvMsg->aucContent);

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryNmrCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryNmrCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_CNMR_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    if (MTA_AT_RESULT_ERROR == pstQryNmrCnf->enResult)
    {
        /* 查询失败直接上报error */
        gstAtSendData.usBufLen = 0;

        /* 复位AT状态 */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        /* 输出结果 */
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_OK;
    }

    usLength = 0;

    /* 按AT^CNMR查询命令返回将接入层返回的数据码流显示上报 */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    if (0 == pstQryNmrCnf->ucTotalIndex)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%d,%d",
                                           0,
                                           0);

        gstAtSendData.usBufLen = usLength;

        /* 复位AT状态 */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        /* 输出结果 */
        At_FormatResultData(ucIndex, AT_OK);
        return VOS_OK;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d,%d,",
                                       pstQryNmrCnf->ucTotalIndex,
                                       pstQryNmrCnf->ucCurrIndex);

    for (ulNmrDataIndex = 0; ulNmrDataIndex < pstQryNmrCnf->usNMRLen; ulNmrDataIndex++)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "%02x",
                                           pstQryNmrCnf->aucNMRData[ulNmrDataIndex]);
    }

    if (pstQryNmrCnf->ucTotalIndex != pstQryNmrCnf->ucCurrIndex)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s",
                                          gaucAtCrLf);

         At_BufferorSendResultData(ucIndex, pgucAtSndCodeAddr, usLength);
    }


    if (pstQryNmrCnf->ucTotalIndex == pstQryNmrCnf->ucCurrIndex)
    {
        At_BufferorSendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

        gstAtSendData.usBufLen = 0;

        /* 复位AT状态 */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        /* 输出结果 */
        At_FormatResultData(ucIndex, AT_OK);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaWrrAutotestQryCnf
 功能描述  : 执行^CWAS后，收到MTA的回复结果。
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月30日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaWrrAutotestQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU   *pstWrrAutotestCnf   = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          i;

    /* 初始化 */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrAutotestCnf   = (MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrAutotestQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrAutotestQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_CWAS_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrAutotestQryCnf : Current Option is not AT_CMD_CWAS_QUERY.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^CWAS命令返回 */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrAutotestCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        if (pstWrrAutotestCnf->stWrrAutoTestRslt.ulRsltNum > 0)
        {
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                             (TAF_CHAR *)pgucAtSndCodeAddr,
                                                             (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                             "%d",
                                                             pstWrrAutotestCnf->stWrrAutoTestRslt.aulRslt[0]);

            for (i = 1; i < pstWrrAutotestCnf->stWrrAutoTestRslt.ulRsltNum; i++)
            {
                gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                                 (TAF_CHAR *)pgucAtSndCodeAddr,
                                                                 (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                                 ",%d",
                                                                 pstWrrAutotestCnf->stWrrAutoTestRslt.aulRslt[i]);
            }
        }
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaWrrCellinfoQryCnf
 功能描述  : 执行^CELLINFO后，收到MTA的回复
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月30日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaWrrCellinfoQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg              = VOS_NULL_PTR;
    MTA_AT_WRR_CELLINFO_QRY_CNF_STRU   *pstWrrCellinfoQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          i;

    /* 初始化 */
    pRcvMsg                 = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrCellinfoQryCnf    = (MTA_AT_WRR_CELLINFO_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult                = AT_OK;
    ucIndex                 = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellinfoQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellinfoQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_CELLINFO_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellinfoQryCnf : Current Option is not AT_CMD_CELLINFO_QUERY.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^CELLINFO命令返回 */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrCellinfoQryCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        /*没有获取的小区信息，打印0*/
        if ( 0 == pstWrrCellinfoQryCnf->stWrrCellInfo.ulCellNum )
        {
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR*)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                               "no cellinfo rslt");
        }

        for (i = 0; i< pstWrrCellinfoQryCnf->stWrrCellInfo.ulCellNum; i++)
        {
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                             (TAF_CHAR *)pgucAtSndCodeAddr,
                                                             (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                             "%d,%d,%d,%d\r\n",
                                                             pstWrrCellinfoQryCnf->stWrrCellInfo.astWCellInfo[i].usCellFreq,
                                                             pstWrrCellinfoQryCnf->stWrrCellInfo.astWCellInfo[i].usPrimaryScramCode,
                                                             pstWrrCellinfoQryCnf->stWrrCellInfo.astWCellInfo[i].sCpichRscp,
                                                             pstWrrCellinfoQryCnf->stWrrCellInfo.astWCellInfo[i].sCpichEcN0);
        }
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}



/*****************************************************************************
 函 数 名  : AT_RcvMtaWrrMeanrptQryCnf
 功能描述  : at下发^CELLINFO命令后，收到MTA的回复
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月30日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaWrrMeanrptQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_WRR_MEANRPT_QRY_CNF_STRU    *pstWrrMeanrptQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;
    VOS_UINT32                          i;
    VOS_UINT32                          ulCellNumLoop;

    /* 初始化 */
    pRcvMsg                 = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrMeanrptQryCnf     = (MTA_AT_WRR_MEANRPT_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult                = AT_OK;
    usLength                = 0;
    ucIndex                 = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrMeanrptQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrMeanrptQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_MEANRPT_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrMeanrptQryCnf : Current Option is not AT_CMD_MEANRPT_QUERY.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^MEANRPT命令返回 */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrMeanrptQryCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR*)pgucAtSndCodeAddr+usLength,
                                           "%d",
                                           pstWrrMeanrptQryCnf->stMeanRptRslt.ulRptNum);

        for ( i = 0 ; i < pstWrrMeanrptQryCnf->stMeanRptRslt.ulRptNum; i++ )
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR*)pgucAtSndCodeAddr+usLength,
                                               "\r\n0x%X,%d",
                                                pstWrrMeanrptQryCnf->stMeanRptRslt.astMeanRptInfo[i].usEventId,
                                                pstWrrMeanrptQryCnf->stMeanRptRslt.astMeanRptInfo[i].usCellNum );
            for ( ulCellNumLoop = 0; ulCellNumLoop < pstWrrMeanrptQryCnf->stMeanRptRslt.astMeanRptInfo[i].usCellNum; ulCellNumLoop++ )
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR*)pgucAtSndCodeAddr+usLength,
                                                   ",%d",
                                                   pstWrrMeanrptQryCnf->stMeanRptRslt.astMeanRptInfo[i].ausPrimaryScramCode[ulCellNumLoop]);
            }

        }
        gstAtSendData.usBufLen = usLength;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaWrrCellSrhSetCnf
 功能描述  : 通过at命令^CELLSRCH设置后，收到mTA的回复
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月30日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaWrrCellSrhSetCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_WRR_CELLSRH_SET_CNF_STRU    *pstWrrCellSrhSetCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrCellSrhSetCnf = (MTA_AT_WRR_CELLSRH_SET_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellSrhSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellSrhSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_WAS_MNTN_SET_CELLSRH != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellSrhSetCnf : Current Option is not AT_CMD_WAS_MNTN_SET_CELLSRH.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^CELLSRH命令返回 */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrCellSrhSetCnf->ulResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaWrrCellSrhQryCnf
 功能描述  : 通过AT命令^CELLSRCH查询后，收到mTA的回复
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月30日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaWrrCellSrhQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_WRR_CELLSRH_QRY_CNF_STRU    *pstWrrCellSrhQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrCellSrhQryCnf = (MTA_AT_WRR_CELLSRH_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellSrhQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellSrhQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_WAS_MNTN_QRY_CELLSRH != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellSrhQryCnf : Current Option is not AT_CMD_WAS_MNTN_QRY_CELLSRH.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^FREQLOCK查询命令返回 */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrCellSrhQryCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR*)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        (TAF_INT32)pstWrrCellSrhQryCnf->ucCellSearchType);

    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaWrrFreqLockSetCnf
 功能描述  : 通过at命令^FREQLOCK设置锁频信息后，收到MTA的回复
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月30日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaWrrFreqLockSetCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg           = VOS_NULL_PTR;
    MTA_AT_WRR_FREQLOCK_SET_CNF_STRU   *pstWrrFreqlockCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrFreqlockCnf   = (MTA_AT_WRR_FREQLOCK_SET_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrFreqLockSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrFreqLockSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_FREQLOCK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrFreqLockSetCnf : Current Option is not AT_CMD_FREQLOCK_SET.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^FREQLOCK命令返回 */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrFreqlockCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaWrrFreqLockQryCnf
 功能描述  : 通过at命令^FREQLOCK查询锁频信息后，收到MTAde回复
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月30日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaWrrFreqLockQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg           = VOS_NULL_PTR;
    MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU   *pstWrrFreqlockCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrFreqlockCnf   = (MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrFreqLockQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrFreqLockQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_FREQLOCK_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrFreqLockQryCnf : Current Option is not AT_CMD_FREQLOCK_QUERY.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^FREQLOCK查询命令返回 */
    gstAtSendData.usBufLen = 0;
    if (VOS_OK != pstWrrFreqlockCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        if (VOS_FALSE == pstWrrFreqlockCnf->stFreqLockInfo.ucFreqLockEnable)
        {
            gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                                            (TAF_CHAR*)pgucAtSndCodeAddr,
                                                            "%s: %d",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            (TAF_INT32)pstWrrFreqlockCnf->stFreqLockInfo.ucFreqLockEnable);
        }
        else
        {
            gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                                            (TAF_CHAR*)pgucAtSndCodeAddr,
                                                            "%s: %d,%d",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            (TAF_INT32)pstWrrFreqlockCnf->stFreqLockInfo.ucFreqLockEnable,
                                                            (TAF_INT32)pstWrrFreqlockCnf->stFreqLockInfo.usLockedFreq);
        }

    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaWrrRrcVersionSetCnf
 功能描述  : 通过at命令^HSPA设置RRC VERSION信息后，收到MTA的回复
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月30日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaWrrRrcVersionSetCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                        *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU    *pstWrrVersionSetCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* 初始化 */
    pRcvMsg                 = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrVersionSetCnf     = (MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU *)pRcvMsg->aucContent;
    ulResult                = AT_OK;
    ucIndex                 = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrRrcVersionSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrRrcVersionSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_RRC_VERSION_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrRrcVersionSetCnf : Current Option is not AT_CMD_RRC_VERSION_SET.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^FREQLOCK命令返回 */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrVersionSetCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        /* 设置成功后重新读写一下NV */
        AT_ReadWasCapabilityNV();

        ulResult = AT_OK;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}



/*****************************************************************************
 函 数 名  : AT_RcvMtaWrrRrcVersionQryCnf
 功能描述  : 通过at命令^HSPA查询RRC VERSION信息后，收到MTA的回复
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月30日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaWrrRrcVersionQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                        *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU    *pstWrrVersionQryCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* 初始化 */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrVersionQryCnf = (MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrRrcVersionQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrRrcVersionQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_RRC_VERSION_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrRrcVersionQryCnf : Current Option is not AT_CMD_RRC_VERSION_QUERY.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^FREQLOCK查询命令返回 */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrVersionQryCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        (TAF_INT32)pstWrrVersionQryCnf->ucRrcVersion);

    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
/*****************************************************************************
 函 数 名  : AT_RcvMmaAcInfoQueryCnf
 功能描述  : AT_MMA_AC_INFO_QUERY_CNF消息处理函数
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2015年03月24日
    作    者   : K00902809
    修改内容   : Changed the structure to TAF_MMA_AC_INFO_QRY_CNF_STRU
*****************************************************************************/
VOS_UINT32 AT_RcvMmaAcInfoQueryCnf(VOS_VOID *pstMsg)
{
    TAF_MMA_AC_INFO_QRY_CNF_STRU       *pstAcInfoQueryCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    pstAcInfoQueryCnf       = (TAF_MMA_AC_INFO_QRY_CNF_STRU*)pstMsg;
    usLength                = 0;
    ulResult                = AT_OK;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstAcInfoQueryCnf->stCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAcInfoQueryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAcInfoQueryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_LOCINFO_READ */
    if (AT_CMD_ACINFO_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 使用AT_STOP_TIMER_CMD_READY恢复AT命令实体状态为READY状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询结果是否失败,如果失败则返回ERROR */
    if (VOS_OK != pstAcInfoQueryCnf->ulRslt)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s:%d,%d,%d,%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellCsAcInfo.enSrvDomain),/* 上报服务域 */
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellCsAcInfo.enCellAcType),/* 上报小区禁止接入类型 */
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellCsAcInfo.ucRestrictRegister),/* 上报是否注册受限 */
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellCsAcInfo.ucRestrictPagingRsp));/* 上报是否寻呼受限 */

        /* 换行 */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s",
                                          gaucAtCrLf);

        usLength  += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s:%d,%d,%d,%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellPsAcInfo.enSrvDomain),/* 上报服务域 */
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellPsAcInfo.enCellAcType),/* 上报小区禁止接入类型 */
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellPsAcInfo.ucRestrictRegister),/* 上报是否注册受限 */
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellPsAcInfo.ucRestrictPagingRsp));/* 上报是否寻呼受限 */

        gstAtSendData.usBufLen = usLength;

    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
/*****************************************************************************
 函 数 名  : AT_RcvMtaQryCurcCnf
 功能描述  : AT收到MTA ID_MTA_AT_QRY_CURC_CNF消息处理函数
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月1日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaQryCurcCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg          = VOS_NULL_PTR;
    MTA_AT_CURC_QRY_CNF_STRU               *pstMtaAtQryCurcCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    VOS_UINT16                              usLength;
    VOS_UINT8                               ucLoop;

    /* 初始化 */
    pstRcvMsg           = (AT_MTA_MSG_STRU *)pstMsg;
    pstMtaAtQryCurcCnf  = (MTA_AT_CURC_QRY_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;
    usLength            = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryCurcCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryCurcCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_CURC_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaQryCurcCnf : Current Option is not AT_CMD_RRC_VERSION_QUERY.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^CURC查询命令返回 */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstMtaAtQryCurcCnf->enResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        usLength        += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                  "%s: %d",
                                                  g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                  pstMtaAtQryCurcCnf->enCurcRptType);

        /* 如果<mode>参数为2，需要打印参数<report_cfg> */
        if (AT_MTA_RPT_GENERAL_CONTROL_CUSTOM == pstMtaAtQryCurcCnf->enCurcRptType)
        {
            usLength    += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                  ",0x");

            for (ucLoop = 0; ucLoop < AT_CURC_RPT_CFG_MAX_SIZE; ucLoop++)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%02X",
                                                   pstMtaAtQryCurcCnf->aucRptCfg[ucLoop]);
            }
        }
    }

    gstAtSendData.usBufLen = usLength;

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaSetUnsolicitedRptCnf
 功能描述  : AT收到MTA ID_MTA_AT_SET_UNSOLICITED_RPT_CNF消息处理函数
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月1日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaSetUnsolicitedRptCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg            = VOS_NULL_PTR;
    MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU    *pstSetUnsolicitedCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* 初始化 */
    pstRcvMsg               = (AT_MTA_MSG_STRU *)pstMsg;
    pstSetUnsolicitedCnf    = (MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult                = AT_OK;
    ucIndex                 = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetUnsolicitedRptCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetUnsolicitedRptCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_UNSOLICITED_RPT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetUnsolicitedRptCnf : Current Option is not AT_CMD_RRC_VERSION_QUERY.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化命令返回 */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstSetUnsolicitedCnf->enResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : AT_RcvMtaQryUnsolicitedRptCnf
 功能描述  : AT收到MTA AT收到ID_MTA_AT_QRY_UNSOLICITED_RPT_CNF消息处理函数消息处理函数
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月1日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年5月25日
    作    者   : s00217060
    修改内容   : DTS2013052406352

*****************************************************************************/
VOS_UINT32 AT_RcvMtaQryUnsolicitedRptCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg            = VOS_NULL_PTR;
    MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU    *pstQryUnsolicitedCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* 初始化 */
    pstRcvMsg               = (AT_MTA_MSG_STRU *)pstMsg;
    pstQryUnsolicitedCnf    = (MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult                = AT_OK;
    ucIndex                 = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryUnsolicitedRptCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryUnsolicitedRptCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_UNSOLICITED_RPT_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaQryUnsolicitedRptCnf : Current Option is not AT_CMD_RRC_VERSION_QUERY.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化查询命令返回 */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstQryUnsolicitedCnf->enResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        /* ucIndex参数带下来 */
        ulResult = AT_ProcMtaUnsolicitedRptQryCnf(ucIndex, pstMsg);
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_ProcMtaUnsolicitedRptQryCnf
 功能描述  : AT处理查询消息函数
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月1日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年5月25日
    作    者   : s00217060
    修改内容   : for DTS2013052406352:
                 ucIndex错误，副卡设置at^time=0,查询时显示+ctzr: 0

*****************************************************************************/
VOS_UINT32 AT_ProcMtaUnsolicitedRptQryCnf(
    VOS_UINT8                               ucIndex,
    VOS_VOID                               *pstMsg
)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg            = VOS_NULL_PTR;
    MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU    *pstQryUnsolicitedCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    /* ucIndex通过上层函数传下来 */

    pstRcvMsg               = (AT_MTA_MSG_STRU *)pstMsg;
    pstQryUnsolicitedCnf    = (MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult                = AT_OK;

    switch (pstQryUnsolicitedCnf->enReqType)
    {
        /* TIME查询的处理 */
        case AT_MTA_QRY_TIME_RPT_TYPE:
            gstAtSendData.usBufLen =
                (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: %d",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       pstQryUnsolicitedCnf->u.ucTimeRptFlg);
            break;

        /* pstQryUnsolicitedCnf数据结构体修改 */
        /* CTZR查询的处理 */
        case AT_MTA_QRY_CTZR_RPT_TYPE:
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: %d",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       pstQryUnsolicitedCnf->u.ucCtzrRptFlg);
            break;

        /* CSSN查询的处理 */
        case AT_MTA_QRY_CSSN_RPT_TYPE:
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            "%s: %d,%d",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            pstQryUnsolicitedCnf->u.stCssnRptFlg.ucCssiRptFlg,
                                                            pstQryUnsolicitedCnf->u.stCssnRptFlg.ucCssuRptFlg);
            break;

        /* CUSD查询的处理 */
        case AT_MTA_QRY_CUSD_RPT_TYPE:
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,"%s: %d",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            pstQryUnsolicitedCnf->u.ucCusdRptFlg);
            break;

        default:
            ulResult = AT_CME_UNKNOWN;

    }

    return ulResult;
}

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-1, end */

/*****************************************************************************
 函 数 名  : AT_RcvMmaCerssiInfoQueryCnf
 功能描述  : TAF_MMA_CERSSI_INFO_QUERY_CNF_STRU消息处理函数
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月4日
    作    者   : z00161729
    修改内容   : 新生成函数
 2.日    期   : 2013年4月20日
   作    者   : z00161729
   修改内容   : 主动上报AT命令控制下移至C核及mma和mmc接口调整
  3.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
VOS_UINT32 AT_RcvMmaCerssiInfoQueryCnf(VOS_VOID *pstMsg)
{
    TAF_MMA_CERSSI_INFO_QRY_CNF_STRU   *pstCerssiInfoQueryCnf = VOS_NULL_PTR;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;


    /* 初始化 */
    pstCerssiInfoQueryCnf   = (TAF_MMA_CERSSI_INFO_QRY_CNF_STRU*)pstMsg;
    usLength                = 0;


    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCerssiInfoQueryCnf->stCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCerssiInfoQueryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCerssiInfoQueryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    /*判断当前操作类型是否为AT_CMD_CERSSI_READ */
    if (AT_CMD_CERSSI_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 使用AT_STOP_TIMER_CMD_READY恢复AT命令实体状态为READY状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询结果是否失败,如果失败则返回ERROR */
    if (TAF_ERR_NO_ERROR != pstCerssiInfoQueryCnf->enErrorCause)
    {
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_ERR;
    }
    else
    {
        /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-20, begin */
        if (TAF_MMA_RAT_GSM == pstCerssiInfoQueryCnf->stCerssi.enRatType)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s%s%d,%d,%d,%d,%d,%d,%d,%d,%d%s",
                                               gaucAtCrLf,
                                               gastAtStringTab[AT_STRING_CERSSI].pucText,
                                               pstNetCtx->ucCerssiReportType,
                                               pstNetCtx->ucCerssiMinTimerInterval,
                                               pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stGCellSignInfo.sRssiValue,
                                               0,
                                               255,
                                               0,
                                               0,
                                               0,
                                               0,
                                               gaucAtCrLf);

            gstAtSendData.usBufLen = usLength;

            /* 输出结果 */
            At_FormatResultData(ucIndex, AT_OK);
            return VOS_OK;
        }

        if (TAF_MMA_RAT_WCDMA == pstCerssiInfoQueryCnf->stCerssi.enRatType)
        {
            if (TAF_UTRANCTRL_UTRAN_MODE_FDD == pstCerssiInfoQueryCnf->stCerssi.ucCurrentUtranMode)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%s%s%d,%d,%d,%d,%d,%d,%d,%d,%d%s",
                                                   gaucAtCrLf,
                                                   gastAtStringTab[AT_STRING_CERSSI].pucText,
                                                   pstNetCtx->ucCerssiReportType,
                                                   pstNetCtx->ucCerssiMinTimerInterval,
                                                   0,      /* rssi */
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stWCellSignInfo.sRscpValue,
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stWCellSignInfo.sEcioValue,
                                                   0,
                                                   0,
                                                   0,
                                                   0,
                                                   gaucAtCrLf);

                gstAtSendData.usBufLen = usLength;

                /* 输出结果 */
                At_FormatResultData(ucIndex, AT_OK);
                return VOS_OK;
            }
            else
            {
                /* 非fdd 3g 小区，ecio值为无效值255 */
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%s%s%d,%d,%d,%d,%d,%d,%d,%d,%d%s",
                                                   gaucAtCrLf,
                                                   gastAtStringTab[AT_STRING_CERSSI].pucText,
                                                   pstNetCtx->ucCerssiReportType,
                                                   pstNetCtx->ucCerssiMinTimerInterval,
                                                   0,      /* rssi */
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stWCellSignInfo.sRscpValue,
                                                   255,
                                                   0,
                                                   0,
                                                   0,
                                                   0,
                                                   gaucAtCrLf);



                gstAtSendData.usBufLen = usLength;

                /* 输出结果 */
                At_FormatResultData(ucIndex, AT_OK);
                return VOS_OK;

            }
        }

        /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-20, end */

#if ( FEATURE_ON == FEATURE_LTE )
        if (TAF_MMA_RAT_LTE == pstCerssiInfoQueryCnf->stCerssi.enRatType)
        {
            /* LTE下的cerssi查询处理由L4A移到NAS，和atCerssiInfoCnfProc的处理相同 */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s%s%d,%d,0,0,255,%d,%d,%d,%d,%d,%d%s",
                                               gaucAtCrLf,
                                               gastAtStringTab[AT_STRING_CERSSI].pucText,
                                               pstNetCtx->ucCerssiReportType,
                                               pstNetCtx->ucCerssiMinTimerInterval,
                                               pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.sRsrp,
                                               pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.sRsrq,
                                               pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.lSINR,
                                               pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stCQI.usRI,
                                               pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stCQI.ausCQI[0],
                                               pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stCQI.ausCQI[1],
                                               gaucAtCrLf);

            gstAtSendData.usBufLen = usLength;

            /* 输出结果 */
            At_FormatResultData(ucIndex, AT_OK);
            return VOS_OK;
        }
#endif
    }

    /* 刚开机没有接入模式，参数都返回无效值 */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s%s%d,%d,%d,%d,%d,%d,%d,%d,%d%s",
                                        gaucAtCrLf,
                                        gastAtStringTab[AT_STRING_CERSSI].pucText,
                                        pstNetCtx->ucCerssiReportType,
                                        pstNetCtx->ucCerssiMinTimerInterval,
                                        pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stGCellSignInfo.sRssiValue,      /* rssi */
                                        pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stWCellSignInfo.sRscpValue,
                                        255,
                                        0,
                                        0,
                                        0,
                                        0,
                                        gaucAtCrLf);

    gstAtSendData.usBufLen = usLength;

    /* 输出结果 */
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}



/*****************************************************************************
 函 数 名  : AT_RcvMtaBodySarSetCnf
 功能描述  : AT_MMA_AC_INFO_QUERY_CNF消息处理函数
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年03月11日
    作    者   : z00214637
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaBodySarSetCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                    *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU             *pstBodySarSetCnf    = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    pRcvMsg          = (AT_MTA_MSG_STRU*)pstMsg;
    pstBodySarSetCnf = (MTA_AT_RESULT_CNF_STRU*)pRcvMsg->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaBodySarSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaBodySarSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_BODYSARON_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断回复消息中的错误码 */
    if (MTA_AT_RESULT_NO_ERROR == pstBodySarSetCnf->enResult)
    {
        ulResult    = AT_OK;

        /* 更新BODYSAR 状态 */
        if (AT_MTA_BODY_SAR_OFF == g_enAtBodySarState)
        {
            g_enAtBodySarState = AT_MTA_BODY_SAR_ON;
        }
        else
        {
            g_enAtBodySarState = AT_MTA_BODY_SAR_OFF;
        }
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_ReportResetCmd
 功能描述  : 上报^RESET命令
 输入参数  : enCause复位原因值
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2013年04月17日
    作    者   : f00179208
    修改内容   : 新生成函数

  2.日    期   : 2015年5月27日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_VOID AT_ReportResetCmd(AT_RESET_REPORT_CAUSE_ENUM_UINT32 enCause)
{
    VOS_UINT16                          usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "%s%s%d%s",
                                        gaucAtCrLf,
                                        gastAtStringTab[AT_STRING_RESET].pucText,
                                        enCause,
                                        gaucAtCrLf);

    /* 需要上报给上层的双RIL */
    At_SendResultData(AT_CLIENT_ID_APP,  pgucAtSndCodeAddr, usLength);
    At_SendResultData(AT_CLIENT_ID_PCUI, pgucAtSndCodeAddr, usLength);

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    At_SendResultData(AT_CLIENT_ID_APP5, pgucAtSndCodeAddr, usLength);
    At_SendResultData(AT_CLIENT_ID_CTRL, pgucAtSndCodeAddr, usLength);
#if (MULTI_MODEM_NUMBER == 3)
    At_SendResultData(AT_CLIENT_ID_APP20, pgucAtSndCodeAddr, usLength);
    At_SendResultData(AT_CLIENT_ID_PCUI2, pgucAtSndCodeAddr, usLength);
#endif
#endif

    return;
}

/*****************************************************************************
 函 数 名  : AT_StopAllTimer
 功能描述  : 停止AT所有的定时器
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年04月19日
   作    者   : f00179208
   修改内容   : 新生成函数
 2.日    期   : 2013年07月11日
   作    者   : l00198894
   修改内容   : V9R1 STK升级项目
 3.日    期   : 2014年03月13日
   作    者   : f00179208
   修改内容   : DTS2014031305234: AT命令设置和查询定时器没有停止
*****************************************************************************/
VOS_VOID AT_StopAllTimer(VOS_VOID)
{
    VOS_UINT8                           ucModemIndex;
    VOS_UINT8                           ucClientIndex;
    VOS_UINT32                          ulTimerName;
    AT_MODEM_CC_CTX_STRU               *pstCcCtx         = VOS_NULL_PTR;
    AT_PARSE_CONTEXT_STRU              *pstParseContext = VOS_NULL_PTR;
    AT_CLIENT_MANAGE_STRU              *pstClientContext = VOS_NULL_PTR;

    for (ucModemIndex = 0; ucModemIndex < MODEM_ID_BUTT; ucModemIndex++)
    {
        pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucModemIndex);

        /* 停止S0定时器 */
        if (VOS_TRUE == pstCcCtx->stS0TimeInfo.bTimerStart)
        {
            ulTimerName = pstCcCtx->stS0TimeInfo.ulTimerName;

            AT_StopRelTimer(ulTimerName, &(pstCcCtx->stS0TimeInfo.s0Timer));
            pstCcCtx->stS0TimeInfo.bTimerStart = VOS_FALSE;
            pstCcCtx->stS0TimeInfo.ulTimerName = 0;
        }

        /* Deleted by l00198894 for V9R1 STK升级, 2013/07/11 */
    }

    for (ucClientIndex = 0; ucClientIndex < AT_MAX_CLIENT_NUM; ucClientIndex++)
    {
        pstParseContext = &(g_stParseContext[ucClientIndex]);
        AT_StopRelTimer(ucClientIndex, &pstParseContext->hTimer);

        pstClientContext = &(gastAtClientTab[ucClientIndex]);
        AT_StopRelTimer(ucClientIndex, &pstClientContext->hTimer);
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_ResetParseCtx
 功能描述  : 重置PHARE CTX
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年04月19日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_ResetParseCtx(VOS_VOID)
{
    VOS_UINT8                           ucClientIndex;
    AT_PARSE_CONTEXT_STRU              *pstParseContext = VOS_NULL_PTR;

    for (ucClientIndex = 0; ucClientIndex < AT_MAX_CLIENT_NUM; ucClientIndex++)
    {
        pstParseContext = &(g_stParseContext[ucClientIndex]);

        pstParseContext->ucClientStatus = AT_FW_CLIENT_STATUS_READY;

        /* 清空所有的缓存的AT命令 */
        AT_ClearBlockCmdInfo(ucClientIndex);

        /* 重置AT组合命令解析的信息 */
        At_ResetCombinParseInfo(ucClientIndex);

        pstParseContext->ucMode    = AT_NORMAL_MODE;
        pstParseContext->usDataLen = 0;
        pstParseContext->usCmdLineLen = 0;

        PS_MEM_SET(pstParseContext->aucDataBuff, 0x00, AT_CMD_MAX_LEN);

        if (NULL != pstParseContext->pucCmdLine)
        {
            AT_FREE(pstParseContext->pucCmdLine);
            pstParseContext->pucCmdLine = NULL;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_ResetClientTab
 功能描述  : 重置CLIENT TAB
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年04月19日
   作    者   : f00179208
   修改内容   : 新生成函数

 2.日    期   : 2013年05月22日
   作    者   : f00179208
   修改内容   : V3R3 PPP PROJECT

  3.日    期   : 2013年11月12日
    作    者   : A00165503
    修改内容   : UART-MODEM: 增加HSAURT端口

  4.日    期   : 2015年5月27日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_VOID AT_ResetClientTab(VOS_VOID)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucClientIndex;

    for (ucClientIndex = 0; ucClientIndex < AT_MAX_CLIENT_NUM; ucClientIndex++)
    {
        /* 清空对应表项 */
        PS_MEM_SET(&gastAtClientTab[ucClientIndex], 0x00, sizeof(AT_CLIENT_MANAGE_STRU));
    }

    /* USB PCUI */
    ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_PCUI;
    gastAtClientTab[ucIndex].ucPortNo        = AT_USB_COM_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_USBCOM_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* USB Control */
    ucIndex = AT_CLIENT_TAB_CTRL_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_CTRL;
    gastAtClientTab[ucIndex].ucPortNo        = AT_CTR_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_CTR_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    ucIndex = AT_CLIENT_TAB_PCUI2_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_PCUI2;
    gastAtClientTab[ucIndex].ucPortNo        = AT_PCUI2_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_PCUI2_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* USB MODEM */
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_MODEM;
    gastAtClientTab[ucIndex].ucPortType      = AT_USB_MODEM_PORT_NO;
    gastAtClientTab[ucIndex].ucDlci          = AT_MODEM_USER_DLCI;
    gastAtClientTab[ucIndex].ucPortNo        = AT_USB_MODEM_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_MODEM_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* NDIS MODEM */
    ucIndex = AT_CLIENT_TAB_NDIS_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_NDIS;
    gastAtClientTab[ucIndex].ucPortNo        = AT_NDIS_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_NDIS_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* USB UART */
    ucIndex = AT_CLIENT_TAB_UART_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_UART;
    gastAtClientTab[ucIndex].ucPortNo        = AT_UART_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_UART_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

#if (FEATURE_ON == FEATURE_AT_HSUART)
    /* HSUART */
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_HSUART;
    gastAtClientTab[ucIndex].ucPortNo        = AT_HSUART_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_HSUART_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;
#endif

    /* SOCK */
    ucIndex = AT_CLIENT_TAB_SOCK_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_SOCK;
    gastAtClientTab[ucIndex].ucPortNo        = AT_SOCK_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_SOCK_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* APP SOCK */
    ucIndex = AT_CLIENT_TAB_APPSOCK_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_APPSOCK;
    gastAtClientTab[ucIndex].ucPortNo        = AT_APP_SOCK_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_APP_SOCK_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

#if (FEATURE_ON == FEATURE_AT_HSIC)
    /* HSIC */
    for (ucLoop = 0; ucLoop < AT_HSIC_AT_CHANNEL_MAX; ucLoop++)
    {
        ucIndex = g_astAtHsicCtx[ucLoop].ucAtClientTabIdx;
        gastAtClientTab[ucIndex].usClientId  = g_astAtHsicCtx[ucLoop].enAtClientId;
        gastAtClientTab[ucIndex].ucPortNo    = g_astAtHsicCtx[ucLoop].ucHsicPort;
        gastAtClientTab[ucIndex].UserType    = g_astAtHsicCtx[ucLoop].ucHsicUser;
        gastAtClientTab[ucIndex].ucUsed      = AT_CLIENT_USED;
    }
#endif
    /* MAX 有NV来控制的，CLIENT TAB的重置放在 AT_MuxInit里面 */

    /* APP */
    for (ucLoop = 0; ucLoop < AT_VCOM_AT_CHANNEL_MAX; ucLoop++)
    {
        ucIndex = AT_CLIENT_TAB_APP_INDEX + ucLoop;
        gastAtClientTab[ucIndex].usClientId  = AT_CLIENT_ID_APP + ucLoop;
        gastAtClientTab[ucIndex].ucPortNo    = APP_VCOM_DEV_INDEX_0 + ucLoop;
        gastAtClientTab[ucIndex].UserType    = AT_APP_USER;
        gastAtClientTab[ucIndex].ucUsed      = AT_CLIENT_USED;
    }

#if (FEATURE_ON == FEATURE_AT_HSIC)
    /* HSIC MODEM */
    ucIndex = AT_CLIENT_TAB_HSIC_MODEM_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_HSIC_MODEM;
    gastAtClientTab[ucIndex].ucPortType      = AT_HSIC_MODEM_PORT_NO;
    gastAtClientTab[ucIndex].ucDlci          = AT_MODEM_USER_DLCI;
    gastAtClientTab[ucIndex].ucPortNo        = AT_HSIC_MODEM_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_MODEM_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;
#endif

}

/*****************************************************************************
 函 数 名  : AT_ResetOtherCtx
 功能描述  : 重置散落在各文件的全局变量
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年06月03日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_ResetOtherCtx(VOS_VOID)
{
    /* <CR> */
    ucAtS3          = 13;

    gaucAtCrLf[0]   = ucAtS3;

    /* <LF> */
    ucAtS4          = 10;

    gaucAtCrLf[1]   = ucAtS4;

    /* <DEL> */
    ucAtS5          = 8;

    /* 指示命令返回码类型 */
    gucAtVType      = AT_V_ENTIRE_TYPE;

    /* 指示TE编码类型 */
    gucAtCscsType   = AT_CSCS_IRA_CODE;

    gucAtEType      = AT_E_ECHO_CMD;

    /* CONNECT <text> result code is given upon entering online data state.
       Dial tone and busy detection are disabled. */
    gucAtXType      = 0;
}

/*****************************************************************************
 函 数 名  : AT_RcvCcpuResetStartInd
 功能描述  : AT收到AT消息ID_CCPU_AT_RESET_START_IND的处理
 输入参数  : pMsg:消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_OK
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年04月17日
   作    者   : f00179208
   修改内容   : 新生成函数
 2.日    期   : 2013年6月1日
    作    者   : z60575
    修改内容   : DTS2012060100769，modem state新增接口

*****************************************************************************/
VOS_UINT32 AT_RcvCcpuResetStartInd(
    VOS_VOID                           *pstMsg
)
{
#if (VOS_OS_VER == VOS_LINUX)
    printk(KERN_ERR "\n AT_RcvCcpuResetStartInd enter %u \n", VOS_GetSlice());
#endif
    /* 上报^RESET:0命令 */
    AT_ReportResetCmd(AT_RESET_REPORT_CAUSE_CCPU_START);

    /* 停止所有启动的内部定时器 */
    AT_StopAllTimer();

    /* 初始化上下文信息 */
    AT_InitCtx();

#if (VOS_OS_VER == VOS_LINUX)
    printk(KERN_ERR "\n AT_RcvCcpuResetStartInd nv write begin %u \n", VOS_GetSlice());
#endif

    /* 将C核单独复位的标记写进NV中 */
    AT_WriteCcpuResetRecordNvim(VOS_TRUE);

#if (VOS_OS_VER == VOS_LINUX)
    printk(KERN_ERR "\n AT_RcvCcpuResetStartInd nv write end %u \n", VOS_GetSlice());
#endif

    /* 读取NV项 */
    AT_ReadNV();

    /* 装备初始化 */
    AT_InitDeviceCmd();

    /* STK初始化 */
    AT_InitStk();

#if (VOS_OS_VER == VOS_LINUX)
        printk(KERN_ERR "\n AT_RcvCcpuResetStartInd nv read end %u \n", VOS_GetSlice());
#endif

    /* AT模块参数的初始化 */
    AT_InitPara();

    /* 重置客户端解析信息 */
    AT_ResetParseCtx();

    /* 重置用户信息 */
    AT_ResetClientTab();

#if (FEATURE_ON == FEATURE_AT_HSIC)
    /* 初始化MAX通道 */
    AT_MuxInit();
#endif

    /* 重置其他散落的全局变量 */
    AT_ResetOtherCtx();

#if (VOS_OS_VER == VOS_LINUX)
    printk(KERN_ERR "\n AT_RcvCcpuResetStartInd set modem state %u \n", VOS_GetSlice());
#endif

    /* C核单独复位后设置设备节点，当前未启动 */
    mdrv_set_modem_state(PS_FALSE);

#if (VOS_OS_VER == VOS_LINUX)
    printk(KERN_ERR "\n AT_RcvCcpuResetStartInd leave %u \n", VOS_GetSlice());
#endif

    /* 释放信号量，使得调用API任务继续运行 */
    VOS_SmV(AT_GetResetSem());

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : AT_RcvCcpuResetEndInd
 功能描述  : AT收到AT消息ID_CCPU_AT_RESET_END_IND的处理
 输入参数  : pMsg:消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_OK
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年04月17日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvCcpuResetEndInd(
    VOS_VOID                           *pstMsg
)
{
#if (VOS_OS_VER == VOS_LINUX)
    printk(KERN_ERR "\n AT_RcvCcpuResetEndInd enter %u \n", VOS_GetSlice());
#endif

    /* 设置复位完成的标志 */
    AT_SetResetFlag(VOS_FALSE);

    /* 上报^RESET:1命令 */
    AT_ReportResetCmd(AT_RESET_REPORT_CAUSE_CCPU_END);

    AT_WriteCcpuResetRecordNvim(VOS_FALSE);

#if (VOS_OS_VER == VOS_LINUX)
    printk(KERN_ERR "\n AT_RcvCcpuResetEndInd leave %u \n", VOS_GetSlice());
#endif

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : AT_RcvHifiResetStartInd
 功能描述  : AT收到AT消息ID_HIFI_AT_RESET_START_IND的处理
 输入参数  : pMsg:消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_OK
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年04月17日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvHifiResetStartInd(
    VOS_VOID                           *pstMsg
)
{
#if (VOS_OS_VER == VOS_LINUX)
    printk(KERN_ERR "\n AT_RcvHifiResetStartInd %u \n", VOS_GetSlice());
#endif

    /* 上报^RESET:2命令 */
    AT_ReportResetCmd(AT_RESET_REPORT_CAUSE_HIFI_START);

    AT_DBG_SAVE_HIFI_RESET_NUM(1);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvHifiResetEndInd
 功能描述  : AT收到AT消息ID_HIFI_AT_RESET_END_IND的处理
 输入参数  : VOS_VOID                           *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月4日
    作    者   : s00190137
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvHifiResetEndInd(
    VOS_VOID                           *pstMsg
)
{
#if (VOS_OS_VER == VOS_LINUX)
    printk(KERN_ERR "\n AT_RcvHifiResetEndInd %u \n", VOS_GetSlice());
#endif

    /* 上报^RESET:3命令 */
    AT_ReportResetCmd(AT_RESET_REPORT_CAUSE_HIFI_END);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_SpyMsgProc
 功能描述  : AT Spy Pid消息处理函数
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年04月17日
    作    者   : z00214637
    修改内容   : 从at_lte_eventreport.c移植
*****************************************************************************/
VOS_UINT32 AT_SpyMsgProc(VOS_VOID* pstMsg)
{
    VOS_UINT32 ulRet = VOS_OK;
    TEMP_PROTECT_EVENT_AT_IND_STRU* pDataMsg = (TEMP_PROTECT_EVENT_AT_IND_STRU*)pstMsg;

    switch(pDataMsg->ulMsgId)
    {
#if ( FEATURE_ON == FEATURE_LTE )
        case ID_TEMPPRT_AT_EVENT_IND:
            ulRet = AT_ProcTempprtEventInd(pDataMsg);
            break;
#endif

        case ID_TEMPPRT_STATUS_AT_EVENT_IND:
            ulRet = AT_RcvTempprtStatusInd(pDataMsg);
            break;

        default:
            AT_WARN_LOG("AT_SpyMsgProc:WARNING:Wrong Msg!\n");
            break;
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : AT_RcvTempprtStatusInd
 功能描述  : 温保主动上报状态消息处理函数
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年04月17日
    作    者   : z00214637
    修改内容   : 新生成函数
  2.日    期   : 2013年10月08日
    作    者   : j00174725
    修改内容   : TQE

*****************************************************************************/
VOS_UINT32 AT_RcvTempprtStatusInd(VOS_VOID *pMsg)
{
    TEMP_PROTECT_EVENT_AT_IND_STRU     *pstTempPrt = VOS_NULL_PTR;
    TAF_TEMP_PROTECT_CONFIG_STRU        stTempProtectPara;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stTempProtectPara, 0x0, sizeof(stTempProtectPara));

    /* 读取温度保护状态主动上报NV项 */
    ulResult = NV_ReadEx(MODEM_ID_0,
                         en_NV_Item_TEMP_PROTECT_CONFIG,
                         &stTempProtectPara,
                         sizeof(TAF_TEMP_PROTECT_CONFIG_STRU));

    if (NV_OK != ulResult)
    {
        AT_ERR_LOG("AT_RcvTempprtStatusInd: Read NV fail");
        return VOS_ERR;
    }

    if (AT_TEMPPRT_STATUS_IND_ENABLE == stTempProtectPara.ucSpyStatusIndSupport)
    {
        pstTempPrt = (TEMP_PROTECT_EVENT_AT_IND_STRU*)pMsg;

        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s^THERM: %d%s",
                                                         gaucAtCrLf, pstTempPrt->ulTempProtectEvent, gaucAtCrLf);

        At_SendResultData(AT_BROADCAST_CLIENT_INDEX_MODEM_0, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

        return VOS_OK;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaImeiVerifyQryCnf
 功能描述  : 收到IMEI校验查询的处理
 输入参数  : pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月23日
    作    者   : Y00213812
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaImeiVerifyQryCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                    *pRcvMsg       = VOS_NULL_PTR;
    VOS_UINT32                         *pulImeiVerify = VOS_NULL_PTR;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    pRcvMsg       = (AT_MTA_MSG_STRU*)pstMsg;
    pulImeiVerify = (VOS_UINT32*)pRcvMsg->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaImeiVerifyQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaImeiVerifyQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_IMEI_VERIFY_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 打印^IMEIVERIFY */
    usLength  = 0;
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "^IMEIVERIFY: ");

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d",
                                       *pulImeiVerify);

    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaCgsnQryCnf
 功能描述  : 收到UE信息上报的处理
 输入参数  : pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月23日
    作    者   : Y00213812
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaCgsnQryCnf(VOS_VOID *pstMsg)
{
    VOS_UINT32                          ulI;
    VOS_UINT8                           ucCheckData;
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_CGSN_QRY_CNF_STRU           *pstCgsn;
    VOS_UINT8                           aucImeiAscii[TAF_PH_IMEI_LEN];

    /* 初始化 */
    ucCheckData   = 0;
    PS_MEM_SET(aucImeiAscii, 0x00, TAF_PH_IMEI_LEN);

    pstRcvMsg = (AT_MTA_MSG_STRU*)pstMsg;
    pstCgsn   = (MTA_AT_CGSN_QRY_CNF_STRU *)pstRcvMsg->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaCgsnQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaCgsnQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_CGSN_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 读取IMEI信息 */
    for (ulI = 0; ulI < (TAF_PH_IMEI_LEN - 2); ulI += 2)
    {
        aucImeiAscii[ulI]     = pstCgsn->aucImei[ulI] + 0x30;
        aucImeiAscii[ulI + 1UL] = pstCgsn->aucImei[ulI + 1UL] + 0x30;

        ucCheckData += (TAF_UINT8)(pstCgsn->aucImei[ulI]
                       +((pstCgsn->aucImei[ulI + 1UL] * 2) / 10)
                       +((pstCgsn->aucImei[ulI + 1UL] * 2) % 10));
    }
    ucCheckData = (10 - (ucCheckData%10)) % 10;

    aucImeiAscii[TAF_PH_IMEI_LEN - 2] = ucCheckData + 0x30;
    aucImeiAscii[TAF_PH_IMEI_LEN - 1] = 0;

    gstAtSendData.usBufLen  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      "%s",
                                      aucImeiAscii);

    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_RcvMmaCopnInfoQueryCnf
 功能描述  : TAF_MMA_COPN_INFO_QUERY_CNF_STRU消息处理函数
 输入参数  : VOS_VOID *pMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，支持+COPN命令
  2.日    期   : 2013年05月24日
    作    者   : W00176964
    修改内容   : SS FDN&Call Control项目:UT修改,增加逗号分隔符
  3.日    期   : 2014年01月15日
    作    者   : f62575
    修改内容   : DTS2014011301359: 接收方PID由原来的WUEPS_PID_MMA修改为I0_WUEPS_PID_MMA
  4.日    期   : 2015年03月24日
    作    者   : K00902809
    修改内容   : Added new structure TAF_MMA_COPN_INFO_QRY_CNF_STRU.
*****************************************************************************/
VOS_UINT32 AT_RcvMmaCopnInfoQueryCnf(VOS_VOID *pMsg)
{
    TAF_MMA_COPN_INFO_QRY_CNF_STRU     *pstCopnInfo = VOS_NULL_PTR;
    TAF_PH_OPERATOR_NAME_STRU          *pstPlmnName = VOS_NULL_PTR;
    VOS_UINT16                          usFromIndex;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulRet;

    /* 初始化 */
    pstCopnInfo   = (TAF_MMA_COPN_INFO_QRY_CNF_STRU *)pMsg;
    usLength      = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCopnInfo->stCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCopnInfoQueryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCopnInfoQueryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_COPN_QRY */
    if (AT_CMD_COPN_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 参照+COPS或^MMPLMNINFO命令处理 */
    pstPlmnName = (TAF_PH_OPERATOR_NAME_STRU *)pstCopnInfo->aucContent;

    for (ulLoop = 0; ulLoop < pstCopnInfo->usPlmnNum; ulLoop++)
    {
        /*  +COPN: <operator in numeric format><operator in long alphanumeric format>     */
        /* 输出命令名 */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s: ",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        /* 输出数字格式运营商名称 */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "\"%X%X%X",
                                           (TAF_MMA_PLMN_MCC_DIGIT3_MASK & pstPlmnName->PlmnId.Mcc) >> TAF_MMA_PLMN_MCC_DIGIT3_OFFSET,
                                           (TAF_MMA_PLMN_MCC_DIGIT2_MASK & pstPlmnName->PlmnId.Mcc) >> TAF_MMA_PLMN_MCC_DIGIT2_OFFSET,
                                           (TAF_MMA_PLMN_MCC_DIGIT1_MASK & pstPlmnName->PlmnId.Mcc) >> TAF_MMA_PLMN_MCC_DIGIT1_OFFSET);

        if (TAF_MMA_PLMN_MNC_DIGIT3_MASK != (TAF_MMA_PLMN_MNC_DIGIT3_MASK & pstPlmnName->PlmnId.Mnc))
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                               "%X",
                                               (TAF_MMA_PLMN_MNC_DIGIT3_MASK & pstPlmnName->PlmnId.Mnc) >> TAF_MMA_PLMN_MNC_DIGIT3_OFFSET);

        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%X%X\"",
                                           (TAF_MMA_PLMN_MNC_DIGIT2_MASK & pstPlmnName->PlmnId.Mnc) >> TAF_MMA_PLMN_MNC_DIGIT2_OFFSET,
                                           (TAF_MMA_PLMN_MNC_DIGIT1_MASK & pstPlmnName->PlmnId.Mnc) >> TAF_MMA_PLMN_MNC_DIGIT1_OFFSET);

        /* 添加逗号分隔符 */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",\"");

        /* 输出运营商长名 */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s",
                                           pstPlmnName->aucOperatorNameLong);

        /* 添加引号 */
        /* 添加逗号分隔符 */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "\"%s",
                                           gaucAtCrLf);

        At_BufferorSendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

        usLength = 0;

        pstPlmnName++;

    }

    /*
    AT模块根据MMA上报的运营商个数来确认运营商信息是否收集完成: 小于请求的运营商
    个数则认为运营商信息已经收集完成，原因如下所述:
    AT模块每次请求50条运营商信息，起始位置为已经输出的最后一个运营商的下一条运营商信息索引
    如果待输出的运营商信息总数不足50条，则按实际的输出，
    如果运营商数为50的倍数，则AT会再发一次运营商信息请求，MMA回复的运营商信息总数为0
    */
    if (pstCopnInfo->usPlmnNum < TAF_MMA_COPN_PLMN_MAX_NUM)
    {
        /* 使用AT_STOP_TIMER_CMD_READY恢复AT命令实体状态为READY状态 */
        AT_STOP_TIMER_CMD_READY(ucIndex);
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_OK);
    }
    else
    {
        usFromIndex = pstCopnInfo->usFromIndex + pstCopnInfo->usPlmnNum;

        ulRet = TAF_MMA_QryCopnInfoReq(WUEPS_PID_AT,
                                       gastAtClientTab[ucIndex].usClientId,
                                       usFromIndex,
                                       0);

        if (VOS_TRUE != ulRet)
        {
            /* 使用AT_STOP_TIMER_CMD_READY恢复AT命令实体状态为READY状态 */
            AT_STOP_TIMER_CMD_READY(ucIndex);
            gstAtSendData.usBufLen = 0;
            At_FormatResultData(ucIndex, AT_ERROR);
        }
    }
    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_RcvMtaSetNCellMonitorCnf
 功能描述  : AT收到MTA ID_MTA_AT_SET_NCELL_MONITOR_CNF消息处理函数
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月31日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaSetNCellMonitorCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                 *pstSetCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* 初始化 */
    pstRcvMsg    = (AT_MTA_MSG_STRU *)pstMsg;
    pstSetCnf    = (MTA_AT_RESULT_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult     = AT_OK;
    ucIndex      = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetNCellMonitorCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetNCellMonitorCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_NCELL_MONITOR_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetNCellMonitorCnf : Current Option is not AT_CMD_NCELL_MONITOR_SET.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化命令返回 */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstSetCnf->enResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : AT_RcvMtaQryNCellMonitorCnf
 功能描述  : AT收到MTA ID_MTA_AT_NCELL_MONITOR_QRY_CNF消息处理函数
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaQryNCellMonitorCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg      = VOS_NULL_PTR;
    MTA_AT_NCELL_MONITOR_QRY_CNF_STRU      *pstMtaAtQryCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    VOS_UINT16                              usLength;

    /* 初始化 */
    pstRcvMsg           = (AT_MTA_MSG_STRU *)pstMsg;
    pstMtaAtQryCnf      = (MTA_AT_NCELL_MONITOR_QRY_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;
    usLength            = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryNCellMonitorCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryNCellMonitorCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_NCELL_MONITOR_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaQryNCellMonitorCnf : Current Option is not AT_CMD_NCELL_MONITOR_READ.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^NCELLMONITOR查询命令返回 */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstMtaAtQryCnf->enResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        /* 查询时，还需要上报邻区状态 */
        usLength        += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                  "%s: %d,%d",
                                                  g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                  pstMtaAtQryCnf->ucSwitch,
                                                  pstMtaAtQryCnf->ucNcellState);

    }

    gstAtSendData.usBufLen = usLength;

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaNCellMonitorInd
 功能描述  : AT收到MTA ID_MTA_AT_NCELL_MONITOR_IND消息处理函数
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMtaNCellMonitorInd(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg      = VOS_NULL_PTR;
    MTA_AT_NCELL_MONITOR_IND_STRU          *pstMtaAtInd    = VOS_NULL_PTR;
    VOS_UINT8                               ucIndex;
    VOS_UINT16                              usLength;

    /* 初始化 */
    pstRcvMsg           = (AT_MTA_MSG_STRU *)pstMsg;
    pstMtaAtInd         = (MTA_AT_NCELL_MONITOR_IND_STRU *)pstRcvMsg->aucContent;
    ucIndex             = 0;
    usLength            = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaNCellMonitorInd : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s^NCELLMONITOR: %d%s",
                                       gaucAtCrLf,
                                       pstMtaAtInd->ucNcellState,
                                       gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_RcvMmaSimInsertRsp
 功能描述  : SIMINSERT设置命令的返回处理
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月4日
    作    者   : s00190137
    修改内容   : 新生成函数
  2.日    期   : 2015年03月24日
    作    者   : K00902809
    修改内容   : Added structure TAF_MMA_SIM_INSERT_CNF_STRU instead of TAF_MMA_SIM_INSERT_RSP_STRU

*****************************************************************************/
VOS_UINT32 AT_RcvMmaSimInsertRsp(VOS_VOID *pMsg)
{
    TAF_MMA_SIM_INSERT_CNF_STRU        *pstSimInsertRsp = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstSimInsertRsp = (TAF_MMA_SIM_INSERT_CNF_STRU *)pMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstSimInsertRsp->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSimInsertRsp : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSimInsertRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_SIMINSERT_SET */
    if (AT_CMD_SIMINSERT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_OK == pstSimInsertRsp->ulResult)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaRefclkfreqSetCnf
 功能描述  : AT模块收到MTA回复的REFCLKFREQ_SET_CNF消息的处理函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月22日
    作    者   : l00198894
    修改内容   : V9R1 AGPS
*****************************************************************************/
VOS_UINT32 AT_RcvMtaRefclkfreqSetCnf(VOS_VOID *pMsg)
{
    /* 定义局部变量 */
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_RESULT_CNF_STRU             *pstRltCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* 初始化消息变量 */
    ucIndex     = 0;
    pstMtaMsg   = (AT_MTA_MSG_STRU *)pMsg;
    pstRltCnf   = (MTA_AT_RESULT_CNF_STRU *)pstMtaMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_REFCLKFREQ_SET */
    if ( AT_CMD_REFCLKFREQ_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqSetCnf: WARNING:Not AT_CMD_REFCLKFREQ_SET!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if ( MTA_AT_RESULT_NO_ERROR == pstRltCnf->enResult )
    {
        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_RcvMtaRficSsiRdQryCnf
 功能描述  : AT模块收到MTA回复的RFIC SSIRD消息的处理函数
 输入参数  : pMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月29日
    作    者   : x00316382
    修改内容   : 新增
*****************************************************************************/
VOS_UINT32 AT_RcvMtaRficSsiRdQryCnf(VOS_VOID *pMsg)
{
    /* 定义局部变量 */
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_RFICSSIRD_CNF_STRU          *pstRficSsiRdCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* 初始化消息变量 */
    ucIndex                 = 0;
    pstMtaMsg               = ( AT_MTA_MSG_STRU * )pMsg;
    pstRficSsiRdCnf         = ( MTA_AT_RFICSSIRD_CNF_STRU * )pstMtaMsg->aucContent;

    ucIndex                 = g_stAtDevCmdCtrl.ucIndex;

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaRficSsiRdQryCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_RFICSSIRD_SET */
    if ( AT_CMD_RFICSSIRD_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaRficSsiRdQryCnf: WARNING:Not AT_CMD_REFCLKFREQ_READ!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 输出寄存器的值 */
    gstAtSendData.usBufLen  = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                                     "%s: %d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     pstRficSsiRdCnf->ulRegValue );
    ulResult                = AT_OK;

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_RcvMtaRefclkfreqQryCnf
 功能描述  : AT模块收到MTA回复的REFCLKFREQ_QRY_CNF消息的处理函数
 输入参数  : pMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月22日
    作    者   : l00198894
    修改内容   : V9R1 AGPS
*****************************************************************************/
VOS_UINT32 AT_RcvMtaRefclkfreqQryCnf(VOS_VOID *pMsg)
{
    /* 定义局部变量 */
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_REFCLKFREQ_QRY_CNF_STRU     *pstRefclkfreqCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* 初始化消息变量 */
    ucIndex             = 0;
    pstMtaMsg           = (AT_MTA_MSG_STRU *)pMsg;
    pstRefclkfreqCnf    = (MTA_AT_REFCLKFREQ_QRY_CNF_STRU *)pstMtaMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqQryCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_REFCLKFREQ_READ */
    if ( AT_CMD_REFCLKFREQ_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqQryCnf: WARNING:Not AT_CMD_REFCLKFREQ_READ!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if ( MTA_AT_RESULT_NO_ERROR == pstRefclkfreqCnf->enResult )
    {
        /* 输出GPS参考时钟信息，命令版本号默认为0 */
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: 0,%d,%d,%d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstRefclkfreqCnf->ulFreq,
                                                        pstRefclkfreqCnf->ulPrecision,
                                                        pstRefclkfreqCnf->enStatus);
        ulResult    = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
        ulResult    = AT_ERROR;
    }

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaRefclkfreqInd
 功能描述  : AT模块收到MTA回复的REFCLKFREQ_IND消息的处理函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月22日
    作    者   : l00198894
    修改内容   : V9R1 AGPS
*****************************************************************************/
VOS_UINT32 AT_RcvMtaRefclkfreqInd(VOS_VOID *pMsg)
{
    /* 定义局部变量 */
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_REFCLKFREQ_IND_STRU         *pstRefclkfreqInd;

    /* 初始化消息变量 */
    pstMtaMsg           = (AT_MTA_MSG_STRU*)pMsg;
    pstRefclkfreqInd    = (MTA_AT_REFCLKFREQ_IND_STRU*)pstMtaMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* 输出GPS参考时钟信息，命令版本号默认为0 */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s%s: 0,%d,%d,%d%s",
                                                    gaucAtCrLf,
                                                    gastAtStringTab[AT_STRING_REFCLKFREQ].pucText,
                                                    pstRefclkfreqInd->ulFreq,
                                                    pstRefclkfreqInd->ulPrecision,
                                                    pstRefclkfreqInd->enStatus,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaHandleDectSetCnf
 功能描述  : 处理MTA设置cp侧手持位置CNF消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月8日
    作    者   : M00217266
    修改内容   : AP Sensor:

*****************************************************************************/
VOS_UINT32 AT_RcvMtaHandleDectSetCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg           = VOS_NULL_PTR;
    MTA_AT_HANDLEDECT_SET_CNF_STRU     *pstSetCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf           = (MTA_AT_HANDLEDECT_SET_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaHandleDectSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaHandleDectSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_HANDLEDECT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaHandleDectSetCnf : Current Option is not AT_CMD_HANDLEDECT_SET.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;
    if (MTA_AT_RESULT_NO_ERROR != pstSetCnf->enResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaHandleDectQryCnf
 功能描述  : 处理MTA查询cp侧手持位置CNF消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月8日
    作    者   : M00217266
    修改内容   : AP Sensor:

*****************************************************************************/
VOS_UINT32 AT_RcvMtaHandleDectQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg           = VOS_NULL_PTR;
    MTA_AT_HANDLEDECT_QRY_CNF_STRU     *pstQryCnf         = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstQryCnf           = (MTA_AT_HANDLEDECT_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaHandleDectQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaHandleDectQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_HANDLEDECT_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaHandleDectQryCnf : Current Option is not AT_CMD_HANDLEDECT_QRY.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^HANDLEDECT?查询命令返回 */
    gstAtSendData.usBufLen = 0;
    if (MTA_AT_RESULT_NO_ERROR != pstQryCnf->enResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        (VOS_UINT16)pstQryCnf->usHandle);

    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaPsTransferInd
 功能描述  : 上报^PSTRANSFER命令通知应用执行PS域迁移流程
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月21日
    作    者   : l00198894
    修改内容   : V9R1C50 SVLTE离网重选项目新增
*****************************************************************************/
VOS_UINT32 AT_RcvMtaPsTransferInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_PS_TRANSFER_IND_STRU        *pstPsTransferInd;

    /* 初始化消息变量 */
    ucIndex             = 0;
    pstMtaMsg           = (AT_MTA_MSG_STRU*)pMsg;
    pstPsTransferInd    = (MTA_AT_PS_TRANSFER_IND_STRU*)pstMtaMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaPsTransferInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^PSTRANSFER: %d%s",
                                                    gaucAtCrLf,
                                                    pstPsTransferInd->ucCause,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaMipiInfoInd
 功能描述  : ^mipiclk主动上报通知应用层控制LCD
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月04日
    作    者   : j00174725
    修改内容   : RF&LCD INTRUSION项目新增
*****************************************************************************/
VOS_UINT32 AT_RcvMtaMipiInfoInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_RF_LCD_MIPICLK_IND_STRU     *pstMipiClkCnf;

    /* 初始化消息变量 */
    ucIndex             = 0;
    pstMtaMsg           = (AT_MTA_MSG_STRU*)pMsg;
    pstMipiClkCnf       = (MTA_AT_RF_LCD_MIPICLK_IND_STRU*)pstMtaMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaMipiInfoInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^MIPICLK: %d%s",
                                                    gaucAtCrLf,
                                                    pstMipiClkCnf->usMipiClk,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaMipiInfoCnf
 功能描述  : 回复^mipiclk查询通知应用层控制LCD
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月04日
    作    者   : j00174725
    修改内容   : RF&LCD INTRUSION项目新增
*****************************************************************************/
VOS_UINT32 AT_RcvMtaMipiInfoCnf(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_RF_LCD_MIPICLK_CNF_STRU     *pstMipiClkCnf;

    /* 初始化消息变量 */
    ucIndex             = 0;
    pstMtaMsg           = (AT_MTA_MSG_STRU*)pMsg;
    pstMipiClkCnf       = (MTA_AT_RF_LCD_MIPICLK_CNF_STRU*)pstMtaMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaMipiInfoCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMipiInfoCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_MIPI_CLK_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;
    if (VOS_OK != pstMipiClkCnf->usResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstMipiClkCnf->usMipiClk);
    }

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvSwitchCmdModeMsg
 功能描述  : 处理端口切换命令模式消息
 输入参数  : ucIndex - 端口索引号
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月23日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_RcvSwitchCmdModeMsg(VOS_UINT8 ucIndex)
{
    AT_UART_LINE_CTRL_STRU             *pstLineCtrl = VOS_NULL_PTR;

    pstLineCtrl = AT_GetUartLineCtrlInfo();

    /* 处理原则(enPortIndex对应的端口):
     * (1) ONLINE-DATA模式 - 上报OK
     * (2) 其他模式        - 丢弃
     */

    /* 端口索引检查 */
    if (ucIndex >= AT_CLIENT_BUTT)
    {
        return;
    }

    /* 只处理UART端口检测到的切换命令 */
    if (VOS_TRUE != AT_CheckHsUartUser(ucIndex))
    {
        return;
    }

    /* 目前只支持PPP和IP模式下切换为ONLINE-COMMAND模式 */
    if ( (AT_DATA_MODE == gastAtClientTab[ucIndex].Mode)
      && ( (AT_PPP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
        || (AT_IP_DATA_MODE == gastAtClientTab[ucIndex].DataMode) ) )
    {
        if (AT_UART_DSR_MODE_CONNECT_ON == pstLineCtrl->enDsrMode)
        {
            AT_CtrlDSR(ucIndex, AT_IO_LEVEL_LOW);
        }

        At_SetMode(ucIndex, AT_ONLINE_CMD_MODE, AT_NORMAL_MODE);
        At_FormatResultData(ucIndex, AT_OK);
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_RcvWaterLowMsg
 功能描述  : 端口TX达到低水线消息处理
 输入参数  : ucIndex --- 端口索引号
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月12日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_RcvWaterLowMsg(VOS_UINT8 ucIndex)
{
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;

    pstUartCtx = AT_GetUartCtxAddr();

    /* 端口索引检查 */
    if (ucIndex >= AT_CLIENT_BUTT)
    {
        return;
    }

    /* 只处理UART端口的低水线消息 */
    if (VOS_TRUE != AT_CheckHsUartUser(ucIndex))
    {
        return;
    }

    /* TX低水线处理 */
    if (VOS_NULL_PTR != pstUartCtx->pWmLowFunc)
    {
        pstUartCtx->pWmLowFunc(ucIndex);
    }

    return;
}

#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 函 数 名  : AT_RcvMtaPsProtectSetCnf
 功能描述  : AT模块收到MTA发来的ID_MTA_AT_RRC_PROTECT_PS_CNF请求消息的处理函数
 输入参数  : pMsg   -- MTA发送的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月25日
    作    者   : y00176023
    修改内容   : 新增^PSPROTECTMODE命令
*****************************************************************************/
VOS_UINT32 AT_RcvMtaPsProtectSetCnf(VOS_VOID *pMsg)
{
    /* 定义局部变量 */
    AT_MTA_MSG_STRU                    *pRcvMsg;
    MTA_AT_RRC_PROTECT_PS_CNF_STRU     *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    /* 初始化消息变量 */
    pRcvMsg = (AT_MTA_MSG_STRU*)pMsg;
    pstEvent = (MTA_AT_RRC_PROTECT_PS_CNF_STRU*)pRcvMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaPsProtectSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaPsProtectSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_PSPROTECTMODE_SET */
    if ( AT_CMD_PSPROTECTMODE_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaCgpsClockSetCnf: WARNING:Not AT_CMD_CGPSCLOCK_SET!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if ( MTA_AT_RESULT_NO_ERROR == pstEvent->enResult )
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* 调用AT_FormATResultDATa发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
#endif

/*****************************************************************************
 函 数 名  : AT_RcvMtaPhyInitCnf
 功能描述  : AT模块收到MTA发来的 ID_MTA_AT_PHY_INIT_CNF确认消息的处理函数
 输入参数  : pMsg   -- MTA发送的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月25日
    作    者   : y00176023
    修改内容   : 新增^PHYINIT命令
*****************************************************************************/
VOS_UINT32 AT_RcvMtaPhyInitCnf(VOS_VOID *pMsg)
{
    /* 定义局部变量 */
    AT_MTA_MSG_STRU                    *pRcvMsg;
    MTA_AT_PHY_INIT_CNF_STRU           *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* 初始化消息变量 */
    pRcvMsg = (AT_MTA_MSG_STRU*)pMsg;
    pstEvent = (MTA_AT_PHY_INIT_CNF_STRU*)pRcvMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaPhyInitCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaPhyInitCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_PHYINIT_SET */
    if ( AT_CMD_PHYINIT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaPhyInitCnf: WARNING:Not AT_CMD_PHYINIT!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if ( MTA_AT_RESULT_NO_ERROR == pstEvent->enResult )
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;
    /* 调用AT_FormATResultDATa发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}



/* Added by l00198894 for 新增+ECID命令, 2013-12-09, begin */
/*****************************************************************************
 函 数 名  : AT_RcvMtaEcidSetCnf
 功能描述  : AT模块收到MTA回复的ECID_SET_CNF消息的处理函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月10日
    作    者   : l00198894
    修改内容   : 新增+ECID命令
  2.日    期   : 2015年05月20日
    作    者   : j00174725
    修改内容   : DTS2015052207518
*****************************************************************************/
VOS_UINT32 AT_RcvMtaEcidSetCnf(VOS_VOID *pMsg)
{
    /* 定义局部变量 */
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_ECID_SET_CNF_STRU           *pstEcidSetCnf;
    VOS_UINT32                          ulResult;

    /* 初始化消息变量 */
    ucIndex         = 0;
    pstMtaMsg       = (AT_MTA_MSG_STRU*)pMsg;
    pstEcidSetCnf   = (MTA_AT_ECID_SET_CNF_STRU*)pstMtaMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaEcidSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaEcidSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_REFCLKFREQ_READ */
    if ( AT_CMD_ECID_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaEcidSetCnf: WARNING:Not AT_CMD_REFCLKFREQ_READ!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if ( MTA_AT_RESULT_NO_ERROR == pstEcidSetCnf->enResult )
    {
        /* 输出查询的增强型小区信息 */
        /* +ECID=<version>,<rat>,[<cell_description>] */
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s=%s",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstEcidSetCnf->aucCellInfoStr);
        ulResult    = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s=%s",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        "0,NONE:,");

        ulResult    = AT_OK;
    }

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
/* Added by l00198894 for 新增+ECID命令, 2013-12-09, end */

/* Added by s00261364 for L-C互操作项目, 2014-1-27, begin */

/*****************************************************************************
 函 数 名  : AT_RcvMmaSysCfgSetCnf
 功能描述  : 处理来自MMA模块ID_TAF_MMA_SYS_CFG_CNF消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaSysCfgSetCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_SYS_CFG_CNF_STRU           *pstCnfMsg;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstCnfMsg = (TAF_MMA_SYS_CFG_CNF_STRU *)pMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCnfMsg->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSysCfgSetCnf : WARNING:AT INDEX NOT FOUND!");

        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSysCfgSetCnf : AT_BROADCAST_INDEX.");

        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstCnfMsg->enRslt)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstCnfMsg->enErrorCause);
    }

    gstAtSendData.usBufLen = 0;

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaPhoneModeSetCnf
 功能描述  : 处理来自MMA模块ID_TAF_MMA_PHONE_MODE_SET_CNF消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : s00261364
    修改内容   : 新生成函数
  2.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
  3.日    期   : 2015年7月23日
    作    者   : wx270776
    修改内容   : OM融合
*****************************************************************************/
VOS_UINT32 AT_RcvMmaPhoneModeSetCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_PHONE_MODE_SET_CNF_STRU    *pstCnfMsg;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    MODEM_ID_ENUM_UINT16                enModemId;
#if(FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                           ucSptLteFlag;
    VOS_UINT8                           ucSptUtralTDDFlag;
#endif

    pstCnfMsg           = (TAF_MMA_PHONE_MODE_SET_CNF_STRU *)pMsg;
    ucIndex             = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    enModemId           = MODEM_ID_0;
    ulResult            = AT_FAILURE;

    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &enModemId))
    {
        AT_ERR_LOG1("AT_RcvMmaPhoneModeSetCnf:Get ModemID From ClientID fail,ClientID=%d", ucIndex);

        return VOS_ERR;
    }

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCnfMsg->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSysCfgSetCnf : WARNING:AT INDEX NOT FOUND!");

        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPhoneModeSetCnf : AT_BROADCAST_INDEX.");

        return VOS_ERR;
    }

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstCnfMsg->enRslt)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstCnfMsg->enErrorCause);       /* 发生错误 */
    }


    /* Deleted by wx270776 for OM融合, 2015-7-9, begin */

    /* Deleted by wx270776 for OM融合, 2015-7-9, end */

    /* V7R2 ^PSTANDBY命令复用关机处理流程 */
#ifdef FEATURE_UPGRADE_TL
    if(AT_CMD_PSTANDBY_SET == (AT_LTE_CMD_CURRENT_OPT_ENUM)gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);

        return VOS_OK;
    }
#endif

#if((FEATURE_ON == FEATURE_LTE) || (FEATURE_ON == FEATURE_UE_MODE_TDS))
    /* 如果GU处理结果正确，则发送到TL测并等待结果 */
    if (ulResult == AT_OK)
    {
        ucSptLteFlag        = AT_IsModemSupportRat(enModemId, TAF_MMA_RAT_LTE);
        ucSptUtralTDDFlag   = AT_IsModemSupportUtralTDDRat(enModemId);

        if ((VOS_TRUE       == ucSptLteFlag)
         || (VOS_TRUE       == ucSptUtralTDDFlag))
        {
            if ((AT_CMD_TMODE_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
             || (AT_CMD_SET_TMODE == gastAtClientTab[ucIndex].CmdCurrentOpt))
            {
                AT_ProcOperModeWhenLteOn(ucIndex);
                return VOS_OK;
            }
        }
    }
#endif

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaDetachCnf
 功能描述  : 处理来自MMA模块ID_TAF_MMA_DETACH_CNF消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaDetachCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_DETACH_CNF_STRU            *pstDetachCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstDetachCnf = (TAF_MMA_DETACH_CNF_STRU *)pMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstDetachCnf->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaDetachCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaDetachCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstDetachCnf->enRslt)
    {
        ulResult = AT_OK;
    }
    else
    {
        gastAtClientTab[ucIndex].ulCause = pstDetachCnf->enErrorCause;
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/* Added by s00261364 for L-C互操作项目, 2014-1-27, end */

/*****************************************************************************
 函 数 名  : AT_RcvMmaAttachCnf
 功能描述  : AT收到MMA Attach Cnf消息的处理
 输入参数  : void    *pstMsg
 输出参数  : 无
 返 回 值  : VOS_OK:成功 VOS_ERR:失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaAttachCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_ATTACH_CNF_STRU            *pstAttachCnf;
    VOS_UINT8                           ucIndex;

    pstAttachCnf = (TAF_MMA_ATTACH_CNF_STRU *)pstMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstAttachCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAttachCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* 去除广播CLIENT类型的情况 */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAttachCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 停止保护定时器 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 只输出结果(OK/ERROR)，不输出其他信息 */
    gstAtSendData.usBufLen = 0;

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstAttachCnf->enRslt)
    {
        /* 调用At_FormatResultData发送命令结果 */
        At_FormatResultData(ucIndex, AT_OK);
    }
    else
    {
        gastAtClientTab[ucIndex].ulCause = pstAttachCnf->enErrorCause;

        /* 调用At_FormatResultData发送命令结果 */
        At_FormatResultData(ucIndex, AT_ERROR);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaAttachStatusQryCnf
 功能描述  : AT收到MMA ATTACH QRY STATUS CNF消息的处理
 输入参数  : 无
 输出参数  : VOS_OK:成功 VOS_ERR:失败
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaAttachStatusQryCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_ATTACH_STATUS_QRY_CNF_STRU *pstAttachStatusQryCnf;
    VOS_UINT8                           ucIndex;

    pstAttachStatusQryCnf = (TAF_MMA_ATTACH_STATUS_QRY_CNF_STRU *)pstMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstAttachStatusQryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAttachStatusQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* 去除广播CLIENT类型的情况 */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAttachStatusQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 检查当前操作类型 */
    if (AT_CMD_MMA_GET_CURRENT_ATTACH_STATUS != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaAttachStatusQryCnf : CmdCurrentOpt Not Match.");
        return VOS_ERR;
    }

    /* 停止保护定时器 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 检查查询结果 */
    if (TAF_MMA_APP_OPER_RESULT_SUCCESS != pstAttachStatusQryCnf->enRslt)
    {
        At_FormatResultData(ucIndex,AT_ERROR);
        return AT_ERROR;
    }

    /* 根据Domain Type输出返回结果 */
    if (TAF_MMA_SERVICE_DOMAIN_CS_PS == pstAttachStatusQryCnf->enDomainType)
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR*)pgucAtSndCodeAddr,
                                                        "%s: %d,%d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        (VOS_UINT32)pstAttachStatusQryCnf->enPsStatus,
                                                        (VOS_UINT32)pstAttachStatusQryCnf->enCsStatus);

        At_FormatResultData(ucIndex,AT_OK);
    }
    else if (TAF_MMA_SERVICE_DOMAIN_PS == pstAttachStatusQryCnf->enDomainType)
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR*)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        (VOS_UINT32)pstAttachStatusQryCnf->enPsStatus);

        At_FormatResultData(ucIndex,AT_OK);
    }
    else
    {
        At_FormatResultData(ucIndex,AT_ERROR);
        return AT_ERROR;
    }

    return VOS_OK;
}


/* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, begin */
#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
函 数 名  : AT_RcvVcMsgSetMsdCnfProc
功能描述  : VC回复AT 设置eCall消息的处理函数
输入参数  : MN_AT_IND_EVT_STRU   *pstData
输出参数  : 无
返 回 值  : VOS_UINT32
调用函数  :
被调函数  :

修订记录  :
  1.日    期   : 2014年3月27日
    作    者   : j00174725
    修改内容   : V3R3C60_eCall项目
*****************************************************************************/
VOS_UINT32 AT_RcvVcMsgSetMsdCnfProc(
    MN_AT_IND_EVT_STRU                 *pstData
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;
    APP_VC_SET_MSD_CNF_STRU            *pstRslt  = VOS_NULL_PTR;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstData->clientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvVcMsgSetMsdCnfProc:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvVcMsgSetMsdCnfProc : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_ECLMSD_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvVcMsgSetMsdCnfProc:WARNING:AT ARE WAITING ANOTHER CMD!");
        return VOS_ERR;
    }

    pstRslt = (APP_VC_SET_MSD_CNF_STRU *)pstData->aucContent;

    if (VOS_OK == pstRslt->ucRslt)
    {
        ulRet = AT_OK;
    }
    else
    {
        ulRet = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : AT_RcvVcMsgQryMsdCnfProc
功能描述  : VC回复AT 查询eCall MSD 消息的处理函数
输入参数  : MN_AT_IND_EVT_STRU   *pstData
输出参数  : 无
返 回 值  : VOS_UINT32
调用函数  :
被调函数  :

修订记录  :
  1.日    期   : 2014年3月27日
    作    者   : j00174725
    修改内容   : V3R3C60_eCall项目
*****************************************************************************/
VOS_UINT32 AT_RcvVcMsgQryMsdCnfProc(
    MN_AT_IND_EVT_STRU                 *pstData
)
{
    APP_VC_MSG_QRY_MSD_CNF_STRU        *pstQryMsd  = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;
    VOS_UINT16                          i;
    VOS_UINT16                          usLength;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstData->clientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvVcMsgQryMsdCnfProc:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvVcMsgQryMsdCnfProc : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_ECLMSD_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvVcMsgQryMsdCnfProc:WARNING:AT ARE WAITING ANOTHER CMD!");
        return VOS_ERR;
    }

    /* 初始化 */
    pstQryMsd = (APP_VC_MSG_QRY_MSD_CNF_STRU *)pstData->aucContent;

    if (VOS_OK == pstQryMsd->ucQryRslt)
    {
        /* 输出查询结果 */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: \"",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        for (i = 0; i < APP_VC_MSD_DATA_LEN; i++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                        "%02x",
                                                        pstQryMsd->aucMsdData[i]);
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                        "\"");

        gstAtSendData.usBufLen = usLength;
        ulRet = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
        ulRet = AT_ERROR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : AT_RcvVcMsgQryEcallCfgCnfProc
功能描述  : VC回复AT 查询eCall 配置消息的处理函数
输入参数  : MN_AT_IND_EVT_STRU   *pstData
输出参数  : 无
返 回 值  : VOS_UINT32
调用函数  :
被调函数  :

修订记录  :
  1.日    期   : 2014年3月27日
    作    者   : j00174725
    修改内容   : V3R3C60_eCall项目
*****************************************************************************/
VOS_UINT32 AT_RcvVcMsgQryEcallCfgCnfProc(
    MN_AT_IND_EVT_STRU                 *pstData
)
{
    APP_VC_MSG_QRY_ECALL_CFG_CNF_STRU  *pstQryCfg  = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;



    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstData->clientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvVcMsgQryEcallCfgCnfProc:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvVcMsgQryEcallCfgCnfProc : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_ECLCFG_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvVcMsgQryEcallCfgCnfProc:WARNING:AT ARE WAITING ANOTHER CMD!");
        return VOS_ERR;
    }

    /* 初始化 */
    pstQryCfg  = (APP_VC_MSG_QRY_ECALL_CFG_CNF_STRU *)pstData->aucContent;

    if (VOS_OK == pstQryCfg->ucQryRslt)
    {
        /* 输出查询结果 */
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d,%d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstQryCfg->enMode,
                                                        pstQryCfg->enVocConfig);
        ulRet = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
        ulRet = AT_ERROR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return VOS_OK;
}
#endif
/* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, end */

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
 函 数 名  : AT_RcvMmaCLocInfoQueryCnf
 功能描述  : TAF_MMA_CLOCINFO_QUERY_CNF_STRU消息处理函数,^ClocInfo查询结果
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
    作    者   : g00261581
    修改内容   : 新生成函数
  2.日    期   : 2015年03月25日
    作    者   : K00902809
    修改内容   : Changed the structre to  TAF_MMA_CDMA_LOCINFO_QRY_CNF_STRU

*****************************************************************************/
VOS_UINT32 AT_RcvMmaCLocInfoQueryCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_CDMA_LOCINFO_QRY_CNF_STRU  *pstCLocInfoQueryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           IsClocInfoValid;

    /* 初始化 */
    pstCLocInfoQueryCnf = (TAF_MMA_CDMA_LOCINFO_QRY_CNF_STRU*)pstMsg;
    usLength            = 0;
    ulResult            = AT_OK;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCLocInfoQueryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCLocInfoQueryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCLocInfoQueryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_CLOCINFO_QRY */
    if (AT_CMD_CLOCINFO_QRY == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);

        if (VOS_OK == pstCLocInfoQueryCnf->ulRslt)
        {
            IsClocInfoValid = VOS_TRUE;

            usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                             (VOS_CHAR *)pgucAtSndCodeAddr,
                                             (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                             "%s: %d,%d,%d,%d,%d,%d,%d,%d,%d",
                                             g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                             IsClocInfoValid,
                                             pstCLocInfoQueryCnf->stClocinfoPara.usPrevInUse,
                                             pstCLocInfoQueryCnf->stClocinfoPara.ulMcc,
                                             pstCLocInfoQueryCnf->stClocinfoPara.ulMnc,
                                             pstCLocInfoQueryCnf->stClocinfoPara.lSid,
                                             pstCLocInfoQueryCnf->stClocinfoPara.lNid,
                                             pstCLocInfoQueryCnf->stClocinfoPara.ulBaseId,
                                             pstCLocInfoQueryCnf->stClocinfoPara.lBaseLatitude,
                                             pstCLocInfoQueryCnf->stClocinfoPara.lBaseLongitude);

            gstAtSendData.usBufLen = usLength;
        }
        else
        {
            IsClocInfoValid = VOS_FALSE;

            /* 查询失败，上报^CLOCINFO: 0*/
            usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                             (VOS_CHAR *)pgucAtSndCodeAddr,
                                             (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                             "%s: %d",
                                             g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                             VOS_FALSE);

            gstAtSendData.usBufLen = usLength;
        }
    }
    else
    {
        return VOS_ERR;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaCSidNidInd
 功能描述  : TAF_MMA_CSIDNID_IND_STRU消息处理函数,^CSidNid主动上报
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaCSidInd(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_CSID_IND_STRU              *pstCSidInd;

    /* 初始化消息变量 */
    ucIndex             = 0;
    pstCSidInd       = (TAF_MMA_CSID_IND_STRU*)pstMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCSidInd->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaCSidInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^CSID: %d%s",
                                                    gaucAtCrLf,
                                                    pstCSidInd->lSid,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_RcvMmaEmcCallBackNtf
 功能描述  : emc call back 主动上报
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月14日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaEmcCallBackNtf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_1X_EMC_CALL_BACK_NTF_STRU  *pstEmcCallBack;

    /* 初始化消息变量 */
    ucIndex             = 0;
    pstEmcCallBack      = (TAF_MMA_1X_EMC_CALL_BACK_NTF_STRU*)pstMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEmcCallBack->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaEmcCallBackNtf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^EMCCBM: %d%s",
                                                    gaucAtCrLf,
                                                    pstEmcCallBack->ulIsInCallBack,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaQuitCallBackCnf
 功能描述  : 上报退出callback模式的结果
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月10日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaQuitCallBackCnf(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_QUIT_CALLBACK_SET_CNF_STRU *pstQccbCnf;
    VOS_UINT32                          ulResult;

    /* 初始化消息变量 */
    ucIndex            = 0;
    pstQccbCnf = (TAF_MMA_QUIT_CALLBACK_SET_CNF_STRU*)pMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstQccbCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaQuitCallBackCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaQuitCallBackCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_QCCB_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaQuitCallBackCnf : Current Option is not AT_CMD_QCCB_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^QCCB查询命令返回 */
    gstAtSendData.usBufLen = 0;

    if (TAF_ERR_NO_ERROR == pstQccbCnf->enErrorCode)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : AT_RcvMmaQryEmcCallBackCnf
 功能描述  : 上报emc callback模式查询结果
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月14日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaQryEmcCallBackCnf(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_MMA_1X_EMC_CALL_BACK_QRY_CNF_STRU                  *pstQryEmcCallBackCnf;
    VOS_UINT16                                              usLength;
    VOS_UINT32                                              ulResult;

    /* 初始化消息变量 */
    ucIndex            = 0;
    usLength           = 0;
    pstQryEmcCallBackCnf = (TAF_MMA_1X_EMC_CALL_BACK_QRY_CNF_STRU*)pMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstQryEmcCallBackCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaQryEmcCallBackCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaQryEmcCallBackCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_EMCCBM_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaQuitCallBackCnf : Current Option is not AT_CMD_EMCCBM_QRY.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^QCCB查询命令返回 */
    gstAtSendData.usBufLen = 0;

    if (TAF_ERR_NO_ERROR == pstQryEmcCallBackCnf->enErrorCode)
    {
        ulResult = AT_OK;
        usLength = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                         (TAF_CHAR *)pgucAtSndCodeAddr,
                                         (TAF_CHAR *)pgucAtSndCodeAddr,
                                          "%s: %d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          pstQryEmcCallBackCnf->ucIsInCallBackMode);
        gstAtSendData.usBufLen = usLength;
    }
    else
    {
        ulResult = AT_CME_UNKNOWN;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : AT_RcvMmaSetCSidListCnf
 功能描述  : set csidlist cnf msg proc
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月13日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaSetCSidListCnf(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_CSIDLIST_SET_CNF_STRU      *pstSetCSidListCnf;
    VOS_UINT32                          ulResult;

    /* 初始化消息变量 */
    ucIndex            = 0;
    pstSetCSidListCnf = (TAF_MMA_CSIDLIST_SET_CNF_STRU*)pMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstSetCSidListCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSetCSidListCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSetCSidListCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_CSIDLIST_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaSetCSidListCnf : Current Option is not AT_CMD_CSIDLIST_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^CSIDLIST设置命令 */
    gstAtSendData.usBufLen = 0;

    if (TAF_ERR_NO_ERROR == pstSetCSidListCnf->enErrorCode)
    {
     ulResult = AT_OK;
    }
    else
    {
     ulResult = AT_ERROR;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaQryCurrSidNidCnf
 功能描述  : 上报home sid nid模式查询结果
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : f00279542
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaQryCurrSidNidCnf(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_MMA_CURR_SID_NID_QRY_CNF_STRU                      *pstQryCurrSidNidCnf = VOS_NULL_PTR;
    VOS_UINT16                                              usLength;
    VOS_UINT32                                              ulResult;

    /* 初始化消息变量 */
    ucIndex            = 0;
    usLength           = 0;
    pstQryCurrSidNidCnf = (TAF_MMA_CURR_SID_NID_QRY_CNF_STRU*)pMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstQryCurrSidNidCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaQryCurrSidNidCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaQryCurrSidNidCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_CSNID_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaQryCurrSidNidCnf : Current Option is not AT_CMD_EMCCBM_QRY.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^CSNID查询命令返回 */
    gstAtSendData.usBufLen = 0;

    if (TAF_ERR_NO_ERROR == pstQryCurrSidNidCnf->enErrorCode)
    {
        ulResult = AT_OK;
        usLength = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                         (TAF_CHAR *)pgucAtSndCodeAddr,
                                         (TAF_CHAR *)pgucAtSndCodeAddr,
                                          "%s: %d,%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          pstQryCurrSidNidCnf->lSid,
                                          pstQryCurrSidNidCnf->lNid);

        gstAtSendData.usBufLen = usLength;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)

/*****************************************************************************
 函 数 名  : AT_RcvXcallEncryptCallCnf
 功能描述  : xcall 处理密话请求回复消息处理
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月24日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvXcallEncryptCallCnf(
    VOS_VOID                                               *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_CALL_APP_ENCRYPT_VOICE_CNF_STRU                    *pstRcvMsg;
    VOS_UINT32                                              ulResult;
    AT_ENCRYPT_VOICE_ERROR_ENUM_UINT32                      enEcnErr;

    /* 初始化消息变量 */
    ucIndex           = 0;
    pstRcvMsg         = (TAF_CALL_APP_ENCRYPT_VOICE_CNF_STRU*)pstMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvXcallEncryptCallCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvXcallEncryptCallCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_ECCALL_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvXcallEncryptCallCnf : Current Option is not AT_CMD_ECCALL_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;
    /* 格式化AT^ECCALL  SET命令返回 */
    if (TAF_CALL_APP_ENCRYPT_VOICE_SUCC == pstRcvMsg->enEccVoiceStatus)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
        enEcnErr = AT_MapEncVoiceErr(pstRcvMsg->enEccVoiceStatus);

        /* 密话主叫结果其他原因值上报 */
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s^ECCALL: %d%s",
                                                        gaucAtCrLf,
                                                        enEcnErr,
                                                        gaucAtCrLf);

        At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);
    }

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvXcallEncryptCallInd
 功能描述  : 密话呼叫主动上报
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月24日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvXcallEncryptCallInd(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_CALL_APP_ENCRYPT_VOICE_IND_STRU                    *pstRcvMsg;
    VOS_UINT8                                               aucAsciiNum[MN_CALL_MAX_CALLED_BCD_NUM_LEN + 1];
    AT_ENCRYPT_VOICE_ERROR_ENUM_UINT32                      enEcnErr;

    /* 初始化消息变量 */
    ucIndex           = 0;
    pstRcvMsg         = (TAF_CALL_APP_ENCRYPT_VOICE_IND_STRU*)pstMsg;
    PS_MEM_SET(aucAsciiNum, 0, MN_CALL_MAX_CALLED_BCD_NUM_LEN + 1);

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvXcallEncryptCallInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;

    /* 错误原因值转换 */
    if ((TAF_CALL_APP_ENCRYPT_VOICE_XSMS_SEND_RESULT_FAIL <= pstRcvMsg->enEccVoiceStatus)
      &&(TAF_CALL_APP_ENCRYPT_VOICE_TX01_TIMEOUT > pstRcvMsg->enEccVoiceStatus))
    {
        enEcnErr = AT_ENCRYPT_VOICE_INTERNAL_ERROR;
    }
    else
    {
        enEcnErr = AT_MapEncVoiceErr(pstRcvMsg->enEccVoiceStatus);
    }

    /* AT^ECCALL ind命令返回 */
    if (AT_ENCRYPT_VOICE_MT_CALL_NOTIFICATION == enEcnErr)
    {
        /* 密话被叫主动上报 */
        AT_BcdNumberToAscii(pstRcvMsg->stCallingNumber.aucBcdNum,
                            pstRcvMsg->stCallingNumber.ucNumLen,
                            (VOS_CHAR *)aucAsciiNum);
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s^ECCALL: %d,\"%s\"%s",
                                                        gaucAtCrLf,
                                                        enEcnErr,
                                                        aucAsciiNum,
                                                        gaucAtCrLf);
    }
    else if (AT_ENCRYPT_VOICE_ERROR_ENUM_BUTT == enEcnErr)
    {
        /* 异常场景 */
        return VOS_ERR;
    }
    else
    {
        /* 密话主叫结果其他原因值上报 */
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s^ECCALL: %d%s",
                                                        gaucAtCrLf,
                                                        enEcnErr,
                                                        gaucAtCrLf);

    }

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;

}
/*****************************************************************************
 函 数 名  : AT_RcvXcallEcRemoteCtrlInd
 功能描述  : 远程控制命令上报
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月24日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvXcallEccRemoteCtrlInd(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_CALL_APP_EC_REMOTE_CTRL_IND_STRU                   *pstRcvMsg;

    /* 初始化消息变量 */
    ucIndex           = 0;
    pstRcvMsg         = (TAF_CALL_APP_EC_REMOTE_CTRL_IND_STRU*)pstMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvXcallEcRemoteCtrlInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^ECCTRL: %d%s",
                                                    gaucAtCrLf,
                                                    pstRcvMsg->enRemoteCtrlType,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : AT_RcvXcallRemoteCtrlAnsCnf
 功能描述  : 远程控制指令执行完后，短信通知kmc后回复消息
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月24日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvXcallRemoteCtrlAnsCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_CALL_APP_REMOTE_CTRL_ANSWER_CNF_STRU               *pstRcvMsg;
    VOS_UINT32                                              ulResult;

    /* 初始化消息变量 */
    ucIndex           = 0;
    pstRcvMsg         = (TAF_CALL_APP_REMOTE_CTRL_ANSWER_CNF_STRU*)pstMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvXcallRemoteCtrlAnsCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvXcallRemoteCtrlAnsCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_ECCTRL_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvXcallRemoteCtrlAnsCnf : Current Option is not AT_CMD_ECCTRL_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;
    /* 格式化AT^ECCTRL  SET命令返回 */
    if (TAF_CALL_SEND_RESULT_SUCC == pstRcvMsg->enResult)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}
/*****************************************************************************
 函 数 名  : AT_RcvXcallEccCapSetCnf
 功能描述  : 配置modem密话能力cnf消息处理
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月24日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvXcallEccCapSetCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_CALL_APP_ECC_SRV_CAP_CFG_CNF_STRU                  *pstRcvMsg;
    VOS_UINT32                                              ulResult;

    /* 初始化消息变量 */
    ucIndex           = 0;
    pstRcvMsg         = (TAF_CALL_APP_ECC_SRV_CAP_CFG_CNF_STRU*)pstMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvXcallEccCapSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvXcallEccCapSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_ECCAP_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvXcallEccCapSetCnf : Current Option is not AT_CMD_ECCAP_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    /* 格式化AT^ECCAP  SET命令返回 */
    if (TAF_CALL_APP_ECC_SRV_CAP_CFG_RESULT_SUCC == pstRcvMsg->enResult)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}
/*****************************************************************************
 函 数 名  : AT_RcvXcallEccCapQryCnf
 功能描述  : 查询modem密话能力cnf消息处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月24日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvXcallEccCapQryCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_CALL_APP_ECC_SRV_CAP_QRY_CNF_STRU                  *pstRcvMsg;
    VOS_UINT32                                              ulResult;

    /* 初始化消息变量 */
    ucIndex           = 0;
    pstRcvMsg         = (TAF_CALL_APP_ECC_SRV_CAP_QRY_CNF_STRU*)pstMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvXcallEccCapQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvXcallEccCapQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_ECCAP_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvXcallEccCapQryCnf : Current Option is not AT_CMD_ECCAP_QRY.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    /* 格式化AT^ECCAP  SET命令返回 */
    if (TAF_CALL_APP_ECC_SRV_CAP_DISABLE == pstRcvMsg->enEccSrvCap)
    {
        ulResult               = AT_OK;
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           "%s^ECCAP: %d,%d%s",
                                           gaucAtCrLf,
                                           pstRcvMsg->enEccSrvCap,
                                           TAF_CALL_APP_ECC_SRV_STATUS_CLOSE,
                                           gaucAtCrLf);
    }
    else if (TAF_CALL_APP_ECC_SRV_CAP_ENABLE == pstRcvMsg->enEccSrvCap)
    {
        ulResult               = AT_OK;
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           "%s^ECCAP: %d,%d%s",
                                           gaucAtCrLf,
                                           pstRcvMsg->enEccSrvCap,
                                           pstRcvMsg->enEccSrvStatus,
                                           gaucAtCrLf);

    }
    else
    {
        ulResult = AT_ERROR;
    }

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)
/*****************************************************************************
 函 数 名  : AT_RcvXcallSetEccTestModeCnf
 功能描述  : 密话测试模式设置结果回复
 功能描述  : 查询modem密话能力cnf消息处理
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月24日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvXcallSetEccTestModeCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_CALL_APP_SET_EC_TEST_MODE_CNF_STRU                 *pstRcvMsg;
    VOS_UINT32                                              ulResult;

    /* 初始化消息变量 */
    ucIndex           = 0;
    pstRcvMsg         = (TAF_CALL_APP_SET_EC_TEST_MODE_CNF_STRU*)pstMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvXcallSetEccTestModeCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvXcallSetEccTestModeCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_ECCTEST_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvXcallSetEccTestModeCnf : Current Option is not AT_CMD_ECCTEST_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    /* 格式化AT^ECCTEST  SET命令返回 */
    if (VOS_TRUE == pstRcvMsg->ulResult)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}
/*****************************************************************************
 函 数 名  : AT_RcvXcallQryEccTestModeCnf
 功能描述  : 查询当前是否是密话测试模式
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月24日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvXcallQryEccTestModeCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_CALL_APP_GET_EC_TEST_MODE_CNF_STRU                 *pstRcvMsg;
    VOS_UINT32                                              ulResult;

    /* 初始化消息变量 */
    ucIndex           = 0;
    pstRcvMsg         = (TAF_CALL_APP_GET_EC_TEST_MODE_CNF_STRU*)pstMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvXcallQryEccTestModeCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvXcallQryEccTestModeCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_ECCTEST_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvXcallQryEccTestModeCnf : Current Option is not AT_CMD_ECCTEST_QRY.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    /* 格式化AT^ECCTEST  SET命令返回 */
    if (VOS_TRUE == pstRcvMsg->ulResult)
    {
        ulResult               = AT_OK;
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           "%s^ECCTEST: %d%s",
                                           gaucAtCrLf,
                                           pstRcvMsg->enEccTestModeStatus,
                                           gaucAtCrLf);
    }
    else
    {
        ulResult               = AT_ERROR;
    }
    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : AT_RcvXcallQryEccRandomCnf
 功能描述  : 密话测试模式下获取随机数
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月24日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvXcallQryEccRandomCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_CALL_APP_GET_EC_RANDOM_CNF_STRU                    *pstRcvMsg;
    VOS_UINT32                                              ulResult;
    VOS_UINT32                                              ulIndex;
    VOS_UINT16                                              usLength;
    VOS_UINT8                                               ucRandomIndex;

    /* 初始化消息变量 */
    ucIndex           = 0;
    pstRcvMsg         = (TAF_CALL_APP_GET_EC_RANDOM_CNF_STRU*)pstMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvXcallQryEccRandomCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvXcallQryEccRandomCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_ECRANDOM_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvXcallQryEccRandomCnf : Current Option is not AT_CMD_ECRANDOM_QRY.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    /* 格式化AT^ECRANDOM  QRY命令返回 */
    if (VOS_TRUE == pstRcvMsg->ulResult)
    {
        ulResult      = AT_OK;
        ucRandomIndex = 0;

        for (ulIndex  = 1;ulIndex < TAF_CALL_APP_EC_RANDOM_MAX_GROUP + 1;ulIndex++)
        {

            usLength  = 0;
            usLength += (TAF_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                "%s^ECRANDOM: %d,%s",
                                                gaucAtCrLf,
                                                ulIndex,
                                                pstRcvMsg->stEccRandom[ucRandomIndex++].aucEccData);

            usLength += (TAF_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                "%s",
                                                pstRcvMsg->stEccRandom[ucRandomIndex++].aucEccData);

            usLength += (TAF_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                "%s",
                                                pstRcvMsg->stEccRandom[ucRandomIndex++].aucEccData);

            usLength += (TAF_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                "%s%s",
                                                pstRcvMsg->stEccRandom[ucRandomIndex++].aucEccData,
                                                gaucAtCrLf);
            gstAtSendData.usBufLen = usLength;
            At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);
        }


    }
    else
    {
        ulResult               = AT_ERROR;
    }

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : AT_RcvXcallQryEccKmcCnf
 功能描述  : 密话测试模式下查询kmc
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvXcallQryEccKmcCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_CALL_APP_GET_EC_KMC_CNF_STRU                       *pstRcvMsg;
    VOS_UINT32                                              ulResult;
    VOS_UINT8                                               aucKmcAsciiData[TAF_CALL_ECC_KMC_PUBLIC_KEY_MAX_ASCII_LENGTH + 1];

    /* 初始化消息变量 */
    ucIndex           = 0;
    pstRcvMsg         = (TAF_CALL_APP_GET_EC_KMC_CNF_STRU*)pstMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvXcallQryEccKmcCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvXcallQryEccKmcCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_ECKMC_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvXcallQryEccKmcCnf : Current Option is not AT_CMD_ECKMC_QRY.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;


    /* 格式化AT^ECKMC  QRY命令返回 */
    if (VOS_TRUE == pstRcvMsg->ulResult)
    {
        ulResult               = AT_OK;

        /* 把kmc data转换为ascii码 */
        if (AT_OK != AT_HexToAsciiString(pstRcvMsg->stKmcData.aucEccKmcData,
                                         aucKmcAsciiData,
                                         pstRcvMsg->stKmcData.usEccKmcLength))
        {
            return VOS_ERR;
        }

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           "%s^ECKMC: %d,\"%s\"%s",
                                           gaucAtCrLf,
                                           pstRcvMsg->stKmcData.ucEccKmcVer,
                                           aucKmcAsciiData,
                                           gaucAtCrLf);
        At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    }
    else
    {
        ulResult               = AT_ERROR;
    }

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}
/*****************************************************************************
 函 数 名  : AT_RcvXcallSetEccKmcCnf
 功能描述  : 密话测试模式下设置kmc返回结果
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvXcallSetEccKmcCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_CALL_APP_SET_EC_KMC_CNF_STRU                       *pstRcvMsg;
    VOS_UINT32                                              ulResult;

    /* 初始化消息变量 */
    ucIndex           = 0;
    pstRcvMsg         = (TAF_CALL_APP_SET_EC_KMC_CNF_STRU*)pstMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvXcallSetEccKmcCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvXcallSetEccKmcCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_ECKMC_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvXcallSetEccKmcCnf : Current Option is not AT_CMD_ECKMC_QRY.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    /* 格式化AT^ECKMC  SET命令返回 */
    if (VOS_TRUE == pstRcvMsg->ulResult)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : AT_RcvXcallEncryptedVoiceDataInd
 功能描述  : 测试模式下，把测试数据写入文件
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvXcallEncryptedVoiceDataInd(
    VOS_VOID                                               *pstMsg
)
{
    VOS_VOID                                               *pFile;
    VOS_INT32                                               ret;
#ifdef DMT
    TAF_CHAR                                               *DirPath = "D:\\modem_log\\Ecc_test";
#else
    TAF_CHAR                                               *DirPath = "/modem_log/ECC_TEST";
#endif
    TAF_CALL_APP_ENCRYPTED_VOICE_DATA_IND_STRU             *pstRcvMsg;

    pstRcvMsg = (TAF_CALL_APP_ENCRYPTED_VOICE_DATA_IND_STRU *)pstMsg;

#ifdef DMT
    /* 如果目录不存在则先创建目录 */
    if (VOS_OK != access(DirPath, 0))
    {
        if (VOS_OK != mkdir(DirPath))
        {
            AT_WARN_LOG("AT_RcvXcallEncryptedVoiceDataInd: mdrv_file_mkdir /modem_log/ECC_TEST failed.\n");
            return VOS_ERR;
        }
    }

    pFile = fopen(g_pacCurrEncVoiceDataWriteFilePath[gucCurrEncVoiceDataWriteFileNum], "a+");
    if(0 == pFile)
    {
        AT_WARN_LOG("AT_RcvXcallEncryptedVoiceDataInd: mdrv_file_open failed.\n");

        return VOS_ERR;
    }

    ret = fwrite(pstRcvMsg->aucData, 1, pstRcvMsg->usLength, pFile);
    if(ret != pstRcvMsg->usLength)
    {
        AT_WARN_LOG("AT_RcvXcallEncryptedVoiceDataInd: mdrv_file_write write data failed.\n");
        return VOS_ERR;
    }

    ret = fwrite("\n", 1, 1, pFile);
    if(ret != 1)
    {
        AT_WARN_LOG("AT_RcvXcallEncryptedVoiceDataInd: mdrv_file_write write data failed.\n");
        return VOS_ERR;
    }

    fclose(pFile);

#else
    /* 如果目录不存在则先创建目录 */
    if (VOS_OK != mdrv_file_access(DirPath, 0))
    {
        if (VOS_OK != mdrv_file_mkdir(DirPath))
        {
            AT_WARN_LOG("AT_RcvXcallEncryptedVoiceDataInd: mdrv_file_mkdir /modem_log/ECC_TEST failed.\n");
            return VOS_ERR;
        }
    }

    pFile = mdrv_file_open(g_pacCurrEncVoiceDataWriteFilePath[gucCurrEncVoiceDataWriteFileNum], "a+");
    if(0 == pFile)
    {
        AT_WARN_LOG("AT_RcvXcallEncryptedVoiceDataInd: mdrv_file_open failed.\n");

        return VOS_ERR;
    }

    ret = mdrv_file_write(pstRcvMsg->aucData, 1, pstRcvMsg->usLength, pFile);
    if(ret != pstRcvMsg->usLength)
    {
        AT_WARN_LOG("AT_RcvXcallEncryptedVoiceDataInd: mdrv_file_write write data failed.\n");
        return VOS_ERR;
    }

    ret = mdrv_file_write("\n", 1, 1, pFile);
    if(ret != 1)
    {
        AT_WARN_LOG("AT_RcvXcallEncryptedVoiceDataInd: mdrv_file_write write data failed.\n");
        return VOS_ERR;
    }

    mdrv_file_close(pFile);

#endif

    return VOS_OK;
}

#endif
#endif
/*****************************************************************************
 函 数 名  : AT_RcvMmaClocinfoInd
 功能描述  : TAF_MMA_CLOCINFO_IND_STRU消息处理函数,^CLOCINFO主动上报
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月28日
    作    者   : l00359089
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaClocinfoInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_CLOCINFO_IND_STRU          *pstClocinfoInd;

    /* 初始化消息变量 */
    ucIndex             = 0;
    pstClocinfoInd      = (TAF_MMA_CLOCINFO_IND_STRU*)pMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstClocinfoInd->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaClocinfoInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^CLOCINFO: %d,%d,%d,%d,%d,%d,%d,%d%s",
                                                    gaucAtCrLf,
                                                    pstClocinfoInd->stClocinfoPara.usPrevInUse,
                                                    pstClocinfoInd->stClocinfoPara.ulMcc,
                                                    pstClocinfoInd->stClocinfoPara.ulMnc,
                                                    pstClocinfoInd->stClocinfoPara.lSid,
                                                    pstClocinfoInd->stClocinfoPara.lNid,
                                                    pstClocinfoInd->stClocinfoPara.ulBaseId,
                                                    pstClocinfoInd->stClocinfoPara.lBaseLatitude,
                                                    pstClocinfoInd->stClocinfoPara.lBaseLongitude,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvXcallPrivacyModeSetCnf
 功能描述  : 处理privacy mode设置结果
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月24日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvXcallPrivacyModeSetCnf(
    VOS_VOID                                               *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_CALL_APP_PRIVACY_MODE_SET_CNF_STRU                 *pstRcvMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulResult;

    /* 初始化消息变量 */
    ucIndex           = 0;
    pstRcvMsg         = (TAF_CALL_APP_PRIVACY_MODE_SET_CNF_STRU*)pstMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvXcallPrivacyModeSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvXcallPrivacyModeSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_CPMP_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvXcallPrivacyModeSetCnf : Current Option is not AT_CMD_CPMP_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    /* 格式化AT^CPMP  SET命令返回 */
    if (TAF_CALL_APP_RESULT_TYPE_SUCCESS == pstRcvMsg->enResult)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvXcallPrivacyModeQryCnf
 功能描述  : 处理privacy mode查询结果
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月24日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvXcallPrivacyModeQryCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_CALL_APP_PRIVACY_MODE_QRY_CNF_STRU                 *pstRcvMsg = VOS_NULL_PTR;

    /* 初始化消息变量 */
    ucIndex           = 0;
    pstRcvMsg         = (TAF_CALL_APP_PRIVACY_MODE_QRY_CNF_STRU*)pstMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvXcallPrivacyModeQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvXcallPrivacyModeQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_CPMP_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvXcallPrivacyModeQryCnf : Current Option is not AT_CMD_ECCAP_QRY.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    /* X模下，只有一路激活的呼叫 */
    if (0 != pstRcvMsg->ucCallNums)
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           "%s^CPMP: %d,%d,%d%s",
                                           gaucAtCrLf,
                                           pstRcvMsg->enPrivacyMode,
                                           pstRcvMsg->astCallVoicePrivacyInfo[0].ucCallId,
                                           pstRcvMsg->astCallVoicePrivacyInfo[0].enPrivacyMode,
                                           gaucAtCrLf);
    }
    else
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           "%s^CPMP: %d%s",
                                           gaucAtCrLf,
                                           pstRcvMsg->enPrivacyMode,
                                           gaucAtCrLf);
    }

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvXcallPrivacyModeInd
 功能描述  : 处理privacy mode指示
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月24日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvXcallPrivacyModeInd(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    TAF_CALL_APP_PRIVACY_MODE_IND_STRU                     *pstRcvMsg = VOS_NULL_PTR;

    /* 初始化消息变量 */
    ucIndex           = 0;
    pstRcvMsg         = (TAF_CALL_APP_PRIVACY_MODE_IND_STRU*)pstMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvXcallPrivacyModeInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^CPMP: %d,%d,%d%s",
                                                    gaucAtCrLf,
                                                    pstRcvMsg->enPrivacyMode,
                                                    pstRcvMsg->stCallVoicePrivacyInfo.ucCallId,
                                                    pstRcvMsg->stCallVoicePrivacyInfo.enPrivacyMode,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

#endif

/*****************************************************************************
 函 数 名  : AT_RcvMmaCTimeInd
 功能描述  : TAF_MMA_CTIME_IND_STRU消息处理函数,^CTIME时间上报
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月26?
    作    者   : x00314862
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaCTimeInd(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_CTIME_IND_STRU             *pstCTimeInd;
    VOS_INT8                            cTimeZone;

    /* 初始化消息变量 */
    ucIndex           = 0;
    pstCTimeInd       = (TAF_MMA_CTIME_IND_STRU*)pstMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCTimeInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaCTimeInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* 底层上报的cTimeZone是以30分钟为单位的，AP要求以15分钟为单位 */
    if(pstCTimeInd->stTimezoneCTime.cTimeZone < 0)
    {
        cTimeZone = (VOS_INT8)(-1 * 2 * pstCTimeInd->stTimezoneCTime.cTimeZone);
    }
    else
    {
        cTimeZone = (VOS_INT8)(2 * pstCTimeInd->stTimezoneCTime.cTimeZone);
    }

    gstAtSendData.usBufLen = 0;
    /*时间显示格式: ^CTIME: "yy/mm/dd,hh:mm:ss(+/-)tz,dst" */
    if (pstCTimeInd->stTimezoneCTime.cTimeZone >= 0)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s^CTIME: \"%02d/%02d/%02d,%02d:%02d:%02d+%d,%02d\"%s",
                                                        gaucAtCrLf,
                                                        pstCTimeInd->stTimezoneCTime.ucYear%100,
                                                        pstCTimeInd->stTimezoneCTime.ucMonth,
                                                        pstCTimeInd->stTimezoneCTime.ucDay,
                                                        pstCTimeInd->stTimezoneCTime.ucHour,
                                                        pstCTimeInd->stTimezoneCTime.ucMinute,
                                                        pstCTimeInd->stTimezoneCTime.ucSecond,
                                                        cTimeZone,
                                                        pstCTimeInd->stTimezoneCTime.ucDayltSavings,
                                                        gaucAtCrLf);
    }
    else
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s^CTIME: \"%02d/%02d/%02d,%02d:%02d:%02d-%d,%02d\"%s",
                                                        gaucAtCrLf,
                                                        pstCTimeInd->stTimezoneCTime.ucYear%100,
                                                        pstCTimeInd->stTimezoneCTime.ucMonth,
                                                        pstCTimeInd->stTimezoneCTime.ucDay,
                                                        pstCTimeInd->stTimezoneCTime.ucHour,
                                                        pstCTimeInd->stTimezoneCTime.ucMinute,
                                                        pstCTimeInd->stTimezoneCTime.ucSecond,
                                                        cTimeZone,
                                                        pstCTimeInd->stTimezoneCTime.ucDayltSavings,
                                                        gaucAtCrLf);
    }

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_RcvMmaCFreqLockSetCnf
 功能描述  : 设置锁频结果上报
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月29日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaCFreqLockSetCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_CFREQ_LOCK_SET_CNF_STRU    *pstCFreqLockSetCnf;
    VOS_UINT32                          ulResult;

    /* 初始化消息变量 */
    ucIndex             = 0;
    pstCFreqLockSetCnf  = (TAF_MMA_CFREQ_LOCK_SET_CNF_STRU*)pstMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCFreqLockSetCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCFreqLockSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCFreqLockSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_CFREQLOCK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaCFreqLockSetCnf : Current Option is not AT_CMD_CFREQLOCK_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^CFREQLOCK命令返回 */
    gstAtSendData.usBufLen = 0;

    if (VOS_TRUE != pstCFreqLockSetCnf->ulRslt)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaCFreqLockQueryCnf
 功能描述  : 查询锁频结果上报
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月29日
    作    者   : y00307564
    修改内容   : 新生成函数
  2.日    期   : 2015年02月05日
    作    者   : y00307564
    修改内容   : Iteration 8 修改

*****************************************************************************/
VOS_UINT32 AT_RcvMmaCFreqLockQueryCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_CFREQ_LOCK_QUERY_CNF_STRU  *pstCFreqLockQryCnf;
    VOS_UINT16                          usLength;


    /* 初始化消息变量 */
    ucIndex            = 0;
    usLength           = 0;
    pstCFreqLockQryCnf = (TAF_MMA_CFREQ_LOCK_QUERY_CNF_STRU*)pstMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCFreqLockQryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCFreqLockQueryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCFreqLockQueryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_CFREQLOCK_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaCFreqLockQueryCnf : Current Option is not AT_CMD_CFREQLOCK_QUERY.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^CFREQLOCK查询命令返回 */
    gstAtSendData.usBufLen = 0;
    if (TAF_MMA_CFREQ_LOCK_MODE_OFF == pstCFreqLockQryCnf->stCFreqLockPara.enFreqLockMode)
    {
       usLength = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstCFreqLockQryCnf->stCFreqLockPara.enFreqLockMode);
    }
    else
    {
       usLength = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d,%d,%d,%d,%d,%d,%d,%d,%d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstCFreqLockQryCnf->stCFreqLockPara.enFreqLockMode,
                                                        pstCFreqLockQryCnf->stCFreqLockPara.usSid,
                                                        pstCFreqLockQryCnf->stCFreqLockPara.usNid,
                                                        pstCFreqLockQryCnf->stCFreqLockPara.usCdmaBandClass,
                                                        pstCFreqLockQryCnf->stCFreqLockPara.usCdmaFreq,
                                                        pstCFreqLockQryCnf->stCFreqLockPara.usCdmaPn,
                                                        pstCFreqLockQryCnf->stCFreqLockPara.usEvdoBandClass,
                                                        pstCFreqLockQryCnf->stCFreqLockPara.usEvdoFreq,
                                                        pstCFreqLockQryCnf->stCFreqLockPara.usEvdoPn);
    }

    gstAtSendData.usBufLen = usLength;
    /* 输出结果 */
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_RcvMmaCdmaCsqSetCnf
 功能描述  : 处理来自MMA模块ID_TAF_MMA_CDMACSQ_SET_CNF消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月25日
    作    者   : m00312079
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaCdmaCsqSetCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_CDMACSQ_SET_CNF_STRU            *pstCdmaCsqCnf;
    VOS_UINT8                                ucIndex;
    VOS_UINT32                               ulResult;

    pstCdmaCsqCnf = (TAF_MMA_CDMACSQ_SET_CNF_STRU *)pMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCdmaCsqCnf->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCdmaCsqSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCdmaCsqSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstCdmaCsqCnf->enRslt)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaCdmaCsqQryCnf
 功能描述  : 处理来自MMA模块ID_TAF_MMA_CDMACSQ_QRY_CNF消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月25日
    作    者   : m00312079
    修改内容   : 新生成函数

  2.日    期   : 2015年10月16日
    作    者   : m00312079
    修改内容   : DTS2015101505057:添加ec/Io的上报门限

*****************************************************************************/
VOS_UINT32 AT_RcvMmaCdmaCsqQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_CDMACSQ_QUERY_CNF_STRU     *pstCdmaCsqQueryCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    pstCdmaCsqQueryCnf  = (TAF_MMA_CDMACSQ_QUERY_CNF_STRU*)pMsg;
    usLength            = 0;
    ulResult            = AT_OK;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCdmaCsqQueryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCdmaCsqQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCdmaCsqQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_CDMACSQ_QRY */
    if (AT_CMD_CDMACSQ_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s: %d,%d,%d,%d,%d,%d",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                     pstCdmaCsqQueryCnf->enMode,
                                     pstCdmaCsqQueryCnf->ucTimeInterval,
                                     pstCdmaCsqQueryCnf->ucRssiRptThreshold,
                                     pstCdmaCsqQueryCnf->ucEcIoRptThreshold,
                                     pstCdmaCsqQueryCnf->stSigQualityInfo.sCdmaRssi,
                                     pstCdmaCsqQueryCnf->stSigQualityInfo.sCdmaEcIo);


    gstAtSendData.usBufLen = usLength;

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaCdmaCsqInd
 功能描述  : 处理来自MMA模块ID_TAF_MMA_CDMACSQ_IND消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月25日
    作    者   : m00312079
    修改内容   : 新生成函数

  2.日    期   : 2015年10月16日
    作    者   : m00312079
    修改内容   : DTS2015101505057:添加ec/Io的上报门限

*****************************************************************************/
VOS_UINT32 AT_RcvMmaCdmaCsqInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_CDMACSQ_IND_STRU           *pstCdmaCsqInd;

    /* 初始化消息变量 */
    ucIndex             = 0;
    pstCdmaCsqInd       = (TAF_MMA_CDMACSQ_IND_STRU*)pMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCdmaCsqInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaCdmaCsqInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^CDMACSQ: %d,%d%s",
                                                    gaucAtCrLf,
                                                    pstCdmaCsqInd->sCdmaRssi,
                                                    pstCdmaCsqInd->sCdmaEcIo,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;

}


/*****************************************************************************
 函 数 名  : AT_RcvMmaCLModInd
 功能描述  : 处理来自MMA模块ID_TAF_MMA_CLMODE_IND消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : f00279542
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaCLModInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_CLMODE_IND_STRU            *pstCLModeInd;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                          *pucIsCLMode;

    /* 初始化消息变量 */
    ucIndex             = 0;
    pstCLModeInd        = (TAF_MMA_CLMODE_IND_STRU*)pMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCLModeInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaCLModInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_RcvMmaCLModInd: Get modem id fail.");
        return VOS_ERR;
    }

    pucIsCLMode = AT_GetModemCLModeCtxAddrFromModemId(enModemId);

    *pucIsCLMode = pstCLModeInd->ucIsCLMode;
    return VOS_OK;

}
/*****************************************************************************
 函 数 名  : AT_RcvMtaXpassInfoInd
 功能描述  : AT模块收到MTA主动上报的xpass信息
 输入参数  : pstMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月25日
    作    者   : m00217266
    修改内容   : 新增
*****************************************************************************/
VOS_UINT32 AT_RcvMtaXpassInfoInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstMtaMsg       = VOS_NULL_PTR;
    MTA_AT_XPASS_INFO_IND_STRU         *pstXpassInfoInd = VOS_NULL_PTR;

    /* 初始化消息变量 */
    ucIndex             = 0;
    pstMtaMsg           = (AT_MTA_MSG_STRU*)pMsg;
    pstXpassInfoInd     = (MTA_AT_XPASS_INFO_IND_STRU*)pstMtaMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaXpassInfoInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^XPASSINFO: %d,%d%s",
                                                    gaucAtCrLf,
                                                    pstXpassInfoInd->enGphyXpassMode,
                                                    pstXpassInfoInd->enWphyXpassMode,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaCFPlmnSetCnfs
 功能描述  : 处理来自MMA模块ID_TAF_MMA_CFPLMN_SET_CNF消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月9日
    作    者   : f00279542
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaCFPlmnSetCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_CFPLMN_SET_CNF_STRU        *pstCFPLmnCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstCFPLmnCnf = (TAF_MMA_CFPLMN_SET_CNF_STRU *)pMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCFPLmnCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCFPlmnSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCFPlmnSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_CFPLMN_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaCFPlmnSetCnf : Current Option is not AT_CMD_CFPLMN_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstCFPLmnCnf->enRslt)
    {
        ulResult = AT_OK;
    }
    else
    {
        /* 这次代码的修改涉及接口的重构，为了保持和原有GU代码的一致性，返回结果出错时，结果设置为AT_CME_UNKNOWN  */
        ulResult = AT_CME_UNKNOWN;
    }

    gstAtSendData.usBufLen = 0;

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : AT_RcvMmaCFPlmnQueryCnf
 功能描述  : 查询FPLMN上报
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月7日
    作    者   : f00279542
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaCFPlmnQueryCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_CFPLMN_QUERY_CNF_STRU      *pstCFPlmnQrynf = VOS_NULL_PTR;
    TAF_USER_PLMN_LIST_STRU            *pstCFPlmnList  = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulLoop;

    /* 初始化消息变量 */
    ucIndex = 0;
    pstCFPlmnQrynf = (TAF_MMA_CFPLMN_QUERY_CNF_STRU *)pstMsg;
    pstCFPlmnList = (TAF_USER_PLMN_LIST_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(TAF_USER_PLMN_LIST_STRU));
    if (VOS_NULL_PTR == pstCFPlmnList)
    {
        AT_WARN_LOG("AT_RcvMmaCFPlmnQueryCnf : alloc fail");
        return VOS_ERR;
    }

    PS_MEM_SET(pstCFPlmnList, 0x00, sizeof(TAF_USER_PLMN_LIST_STRU));

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCFPlmnQrynf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCFPlmnQueryCnf : WARNING:AT INDEX NOT FOUND!");
        PS_MEM_FREE(WUEPS_PID_AT, pstCFPlmnList);
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCFPlmnQueryCnf : AT_BROADCAST_INDEX.");
        PS_MEM_FREE(WUEPS_PID_AT, pstCFPlmnList);
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_CFPLMN_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaCFPlmnQueryCnf : Current Option is not AT_CMD_CFREQLOCK_QUERY.");
        PS_MEM_FREE(WUEPS_PID_AT, pstCFPlmnList);
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS != pstCFPlmnQrynf->enRslt)
    {
        gstAtSendData.usBufLen = 0;
        /* 这次代码的修改涉及接口的重构，为了保持和原有GU代码的一致性，返回结果出错时，结果设置为AT_CME_UNKNOWN  */
        ulResult = AT_CME_UNKNOWN;
        At_FormatResultData(ucIndex, ulResult);
    }
    else
    {
        if (pstCFPlmnQrynf->usPlmnNum > TAF_USER_MAX_PLMN_NUM)
        {
            pstCFPlmnQrynf->usPlmnNum = TAF_USER_MAX_PLMN_NUM;
        }

        pstCFPlmnList->usPlmnNum = pstCFPlmnQrynf->usPlmnNum;

        for (ulLoop = 0; (ulLoop < pstCFPlmnQrynf->usPlmnNum); ulLoop++ )
        {
            pstCFPlmnList->Plmn[ulLoop].Mcc = pstCFPlmnQrynf->astPlmn[ulLoop].Mcc;
            pstCFPlmnList->Plmn[ulLoop].Mnc = pstCFPlmnQrynf->astPlmn[ulLoop].Mnc;
        }

        At_QryParaRspCfplmnProc(ucIndex, pstCFPlmnQrynf->stCtrl.ucOpId, (TAF_VOID *)pstCFPlmnList);
    }

    PS_MEM_FREE(WUEPS_PID_AT, pstCFPlmnList);
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_ReportQryPrefPlmnCmdPara
 功能描述  : 处理上报查询prefplmn上报
 输入参数  : TAF_MMA_PREF_PLMN_QUERY_CNF_STRU   *pstCpolQryCnf,
             AT_MODEM_NET_CTX_STRU              *pstNetCtx,
             VOS_UINT16                         *pusLength,
             VOS_UINT32                          ucIndex,
             VOS_UINT32                          ulLoop
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月05日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_ReportQryPrefPlmnCmdPara(
    TAF_MMA_PREF_PLMN_QUERY_CNF_STRU   *pstCpolQryCnf,
    AT_MODEM_NET_CTX_STRU              *pstNetCtx,
    VOS_UINT16                         *pusLength,
    VOS_UINT32                          ucIndex,
    VOS_UINT32                          ulLoop
)
{
    TAF_PLMN_NAME_LIST_STRU            *pstAvailPlmnInfo;
    AT_COPS_FORMAT_TYPE                 CurrFormat;

    pstAvailPlmnInfo = (TAF_PLMN_NAME_LIST_STRU*)&pstCpolQryCnf->stPlmnName;

    /* +CPOL:   */
    *pusLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + (*pusLength),
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* <index> */
    *pusLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + (*pusLength),
                                       "%d",
                                       ((ulLoop + pstCpolQryCnf->ulFromIndex) + 1));

    CurrFormat = pstNetCtx->ucCpolFormatType;

    if (('\0' == pstAvailPlmnInfo->astPlmnName[ulLoop].aucOperatorNameLong[0])
     && (AT_COPS_LONG_ALPH_TYPE == CurrFormat))
    {
        CurrFormat = AT_COPS_NUMERIC_TYPE;
    }

    if (('\0' == pstAvailPlmnInfo->astPlmnName[ulLoop].aucOperatorNameShort[0])
     && (AT_COPS_SHORT_ALPH_TYPE == CurrFormat))
    {
        CurrFormat = AT_COPS_NUMERIC_TYPE;
    }

    /* <format> */
    *pusLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + (*pusLength),
                                       ",%d",
                                       CurrFormat);

    /* <oper1> */
    if (AT_COPS_LONG_ALPH_TYPE == CurrFormat)
    {
        *pusLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + (*pusLength),
                                           ",\"%s\"",
                                           pstAvailPlmnInfo->astPlmnName[ulLoop].aucOperatorNameLong);
    }
    else if (AT_COPS_SHORT_ALPH_TYPE == CurrFormat)
    {
        *pusLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + (*pusLength),
                                           ",\"%s\"",
                                           pstAvailPlmnInfo->astPlmnName[ulLoop].aucOperatorNameShort);
    }
    else
    {
        *pusLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + (*pusLength),
                                           ",\"%X%X%X",
                                           (0x0f00 & pstAvailPlmnInfo->astPlmnName[ulLoop].PlmnId.Mcc) >> 8,
                                           (0x00f0 & pstAvailPlmnInfo->astPlmnName[ulLoop].PlmnId.Mcc) >> 4,
                                           (0x000f & pstAvailPlmnInfo->astPlmnName[ulLoop].PlmnId.Mcc));

        if (0x0F != ((0x0f00 & pstAvailPlmnInfo->astPlmnName[ulLoop].PlmnId.Mnc) >> 8))
        {
            *pusLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + (*pusLength),
                                               "%X",
                                               (0x0f00 & pstAvailPlmnInfo->astPlmnName[ulLoop].PlmnId.Mnc) >> 8);

        }

        *pusLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + (*pusLength),
                                           "%X%X\"",
                                           (0x00f0 & pstAvailPlmnInfo->astPlmnName[ulLoop].PlmnId.Mnc) >> 4,
                                           (0x000f & pstAvailPlmnInfo->astPlmnName[ulLoop].PlmnId.Mnc));
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_ReportQryPrefPLmnCmd
 功能描述  : 处理上报查询prefplmn上报
 输入参数  : TAF_MMA_CPOL_INFO_QUERY_CNF_STRU   *pstCpolQryCnf,
             VOS_UINT32                         *pulValidPlmnNum,
             AT_MODEM_NET_CTX_STRU              *pstNetCtx,
             VOS_UINT16                         *pusLength,
             VOS_UINT32                          ucIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月05日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_ReportQryPrefPlmnCmd(
    TAF_MMA_PREF_PLMN_QUERY_CNF_STRU   *pstCpolQryCnf,
    VOS_UINT32                         *pulValidPlmnNum,
    AT_MODEM_NET_CTX_STRU              *pstNetCtx,
    VOS_UINT16                         *pusLength,
    VOS_UINT32                          ucIndex
)
{
    VOS_UINT32                          i;
    TAF_PLMN_NAME_LIST_STRU            *pstAvailPlmnInfo;
    TAF_MMC_USIM_RAT                    usPlmnRat;

    pstAvailPlmnInfo = (TAF_PLMN_NAME_LIST_STRU*)&pstCpolQryCnf->stPlmnName;

    for(i = 0; i < pstAvailPlmnInfo->ulPlmnNum; i++)
    {
        if (VOS_FALSE == AT_PH_IsPlmnValid(&(pstAvailPlmnInfo->astPlmnName[i].PlmnId)))
        {
            continue;
        }

        (*pulValidPlmnNum)++;

        if ((0 == pstCpolQryCnf->ulValidPlmnNum)
         && (1 == *pulValidPlmnNum))
        {
            /* 参考V.250协议5.7.2: 根据V命令的设置给信息字段的头尾增加回车换行符 */
            if (AT_V_ENTIRE_TYPE == gucAtVType)
            {
                *pusLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + (*pusLength),
                                                   "%s",
                                                   gaucAtCrLf);
            }
        }
        else
        {
            *pusLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + (*pusLength),
                                               "%s",
                                               gaucAtCrLf);
        }

        AT_ReportQryPrefPlmnCmdPara(pstCpolQryCnf, pstNetCtx, pusLength, ucIndex, i);

        if ((MN_PH_PREF_PLMN_UPLMN == pstNetCtx->enPrefPlmnType)
         && (VOS_TRUE == pstAvailPlmnInfo->bPlmnSelFlg))
        {
            continue;
        }


        /* <GSM_AcT1> */
        /* <GSM_Compact_AcT1> */
        /* <UTRAN_AcT1> */
        usPlmnRat = pstAvailPlmnInfo->ausPlmnRat[i];

        *pusLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + (*pusLength),",%d,%d,%d,%d",
                                           (usPlmnRat & TAF_MMC_USIM_GSM_RAT) >> 7,
                                           (usPlmnRat & TAF_MMC_USIM_GSM_COMPACT_RAT) >> 6,
                                           (usPlmnRat & TAF_MMC_USIM_UTRN_RAT) >> 15,
                                           (usPlmnRat & TAF_MMC_USIM_E_UTRN_RAT) >> 14);

    }

    return;

}
/*****************************************************************************
 函 数 名  : AT_RcvMmaPrefPlmnSetCnf
 功能描述  : 处理来自MMA模块ID_TAF_MMA_PREF_PLMN_SET_CNF消息
 输入参数  : VOS_VOID *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月05日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaPrefPlmnSetCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_PREF_PLMN_SET_CNF_STRU     *pstPrefPlmnCnf;
    VOS_UINT32                          ulResult;

    /* 初始化消息变量 */
    ucIndex            = 0;
    ulResult           = AT_ERROR;
    pstPrefPlmnCnf     = (TAF_MMA_PREF_PLMN_SET_CNF_STRU*)pstMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstPrefPlmnCnf->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPrefPlmnSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPrefPlmnSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_CPOL_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaPrefPlmnSetCnf : Current Option is not AT_CMD_CPOL_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_PREF_PLMN_OPER_RESULT_SUCCESS != pstPrefPlmnCnf->enRslt)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* 格式化AT+CPOL测试命令返回 */
    gstAtSendData.usBufLen = 0;

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaPrefPlmnQueryCnf
 功能描述  : 处理来自MMA模块ID_TAF_MMA_PREF_PLMN_QUERY_CNF消息
 输入参数  : VOS_VOID *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月05日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaPrefPlmnQueryCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT32                          ulResult = AT_FAILURE;
    VOS_UINT16                          usLength = 0;
    TAF_PLMN_NAME_LIST_STRU            *pstAvailPlmnInfo;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulValidPlmnNum;
    TAF_MMA_CPOL_INFO_QUERY_REQ_STRU    stCpolInfo;
    VOS_UINT8                           ucIndex;
    TAF_MMA_PREF_PLMN_QUERY_CNF_STRU   *pstCpolQryCnf = VOS_NULL_PTR;

    pstCpolQryCnf    = (TAF_MMA_PREF_PLMN_QUERY_CNF_STRU *)pstMsg;

    pstAvailPlmnInfo = (TAF_PLMN_NAME_LIST_STRU*)&pstCpolQryCnf->stPlmnName;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCpolQryCnf->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_QryParaRspPrefPlmnProc:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_QryParaRspPrefPlmnProc : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    /*判断当前操作类型是否为AT_CMD_CPOL_READ */
    if (AT_CMD_CPOL_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    if (TAF_MMA_APP_PREF_PLMN_OPER_RESULT_SUCCESS != pstCpolQryCnf->enRslt)
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);

        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_CME_UNKNOWN);

        return VOS_OK;
    }

    ulValidPlmnNum = 0;
    AT_ReportQryPrefPlmnCmd(pstCpolQryCnf, &ulValidPlmnNum, pstNetCtx, &usLength, ucIndex);

    /*
    AT模块根据MMA上报的运营商个数来确认运营商信息是否收集完成: 小于请求的运营商
    个数则认为运营商信息已经收集完成，原因如下所述:
    AT模块每次请求37条运营商信息，起始位置为已经输出的最后一个运营商的下一条运营商信息索引
    如果待输出的运营商信息总数不足37条，则按实际的输出，
    如果运营商数为37的倍数，则AT会再发一次运营商信息请求，MMA回复的运营商信息总数为0
    */
    if (pstAvailPlmnInfo->ulPlmnNum < TAF_MMA_MAX_PLMN_NAME_LIST_NUM)
    {
        /* 参考V.250协议5.7.2: 根据V命令的设置给信息字段的头尾增加回车换行符 */
        if ((AT_V_ENTIRE_TYPE == gucAtVType)
         && (0 != (pstCpolQryCnf->ulValidPlmnNum + ulValidPlmnNum)))
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s",
                                               gaucAtCrLf);

        }

        At_BufferorSendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

        /* 使用AT_STOP_TIMER_CMD_READY恢复AT命令实体状态为READY状态 */
        AT_STOP_TIMER_CMD_READY(ucIndex);
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_OK);
    }
    else
    {
        At_BufferorSendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

        stCpolInfo.enPrefPLMNType   = pstNetCtx->enPrefPlmnType;
        stCpolInfo.ulFromIndex      = (pstCpolQryCnf->ulFromIndex + pstAvailPlmnInfo->ulPlmnNum);
        stCpolInfo.ulPlmnNum        = TAF_MMA_MAX_PLMN_NAME_LIST_NUM;
        stCpolInfo.ulValidPlmnNum   = (pstCpolQryCnf->ulValidPlmnNum + ulValidPlmnNum);
        ulResult                    = TAF_MMA_QueryCpolReq(WUEPS_PID_AT,
                                      gastAtClientTab[ucIndex].usClientId,
                                      0,
                                      &stCpolInfo);
        if (VOS_TRUE != ulResult)
        {
            /* 使用AT_STOP_TIMER_CMD_READY恢复AT命令实体状态为READY状态 */
            AT_STOP_TIMER_CMD_READY(ucIndex);
            gstAtSendData.usBufLen = 0;
            At_FormatResultData(ucIndex, AT_CME_UNKNOWN);
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaPrefPlmnTestCnf
 功能描述  : 处理来自MMA模块ID_TAF_MMA_PREF_PLMN_TEST_CNF消息
 输入参数  : VOS_VOID *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月05日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaPrefPlmnTestCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_PREF_PLMN_TEST_CNF_STRU    *pstPrefPlmnCnf;
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulResult;

    /* 初始化消息变量 */
    ucIndex            = 0;
    usLength           = 0;
    ulResult           = AT_ERROR;
    pstPrefPlmnCnf     = (TAF_MMA_PREF_PLMN_TEST_CNF_STRU*)pstMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstPrefPlmnCnf->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPrefPlmnTestCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPrefPlmnTestCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_CPOL_TEST != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaPrefPlmnTestCnf : Current Option is not AT_CMD_CPOL_TEST.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_PREF_PLMN_OPER_RESULT_SUCCESS != pstPrefPlmnCnf->enRslt)
    {
        gstAtSendData.usBufLen = usLength;
        At_FormatResultData(ucIndex, AT_CME_UNKNOWN);

        return VOS_OK;
    }

    /* 格式化AT+CPOL测试命令返回 */
    gstAtSendData.usBufLen = 0;
    if ( 0 == pstPrefPlmnCnf->usPlmnNum )
    {
        ulResult = AT_CME_OPERATION_NOT_ALLOWED;
    }
    else
    {
        usLength = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                         (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                         "%s: (1-%d),(0-2)",
                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                         pstPrefPlmnCnf->usPlmnNum);


        ulResult = AT_OK;
    }

    gstAtSendData.usBufLen = usLength;

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaAcInfoChangeInd
 功能描述  : 处理TAF_PH_EVT_AC_INFO_CHANGE_IND
 输入参数  : VOS_UINT8                           ucIndex,
             TAF_PHONE_EVENT_INFO_STRU          *pstEvent
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年2月25日
    作    者   : l60609
    修改内容   : DSDA PHASE III
  3.日    期   : 2015年03月24日
    作    者   : K00902809
    修改内容   : Changed the arguments to VOS_VOID     *pstMsg
                 Added new structure TAF_MMA_AC_INFO_CHANGE_IND_STRU instead of common event structure.
*****************************************************************************/
VOS_UINT32 AT_RcvMmaAcInfoChangeInd(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT16                          usLength;
    TAF_MMA_CELL_AC_INFO_STRU          *pstCellAcInfo = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;
    TAF_MMA_AC_INFO_CHANGE_IND_STRU    *psAcInfoChangeInd = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    psAcInfoChangeInd = (TAF_MMA_AC_INFO_CHANGE_IND_STRU*)pstMsg;

    if (AT_FAILURE == At_ClientIdToUserId(psAcInfoChangeInd->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAcInfoChangeInd : AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    enModemId = MODEM_ID_0;

    usLength = 0;
    pstCellAcInfo = (TAF_MMA_CELL_AC_INFO_STRU*)(&psAcInfoChangeInd->stCellAcInfo);

    ulRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_RcvMmaAcInfoChangeInd: Get modem id fail.");
        return VOS_ERR;
    }

    /* 通过AT^CURC控制紧急呼叫号码不上报 */
    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, end */

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s%s%d,%d,%d,%d%s",
                                       gaucAtCrLf,
                                       gastAtStringTab[AT_STRING_ACINFO].pucText,
                                       pstCellAcInfo->enSrvDomain,/* 上报服务域 */
                                       pstCellAcInfo->enCellAcType,/* 上报小区禁止接入类型 */
                                       pstCellAcInfo->ucRestrictRegister,/* 上报是否注册受限 */
                                       pstCellAcInfo->ucRestrictPagingRsp,/* 上报是否寻呼受限 */
                                       gaucAtCrLf);

    gstAtSendData.usBufLen = usLength;

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaEOPlmnSetCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;
    TAF_MMA_EOPLMN_SET_CNF_STRU        *pstEOPlmnSetCnf = VOS_NULL_PTR;

    pstEOPlmnSetCnf  = (TAF_MMA_EOPLMN_SET_CNF_STRU *)pstMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstEOPlmnSetCnf->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaEOPlmnSetCnf At_ClientIdToUserId FAILURE");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaEOPlmnSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_EOPLMN_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMmaEOPlmnSetCnf: WARNING:Not AT_CMD_EOPLMN_SET!");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if( TAF_ERR_NO_ERROR == pstEOPlmnSetCnf->ulResult)
    {
        ulRslt = AT_OK;
    }
    else
    {
        ulRslt = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;


    At_FormatResultData(ucIndex,ulRslt);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaEOPlmnQryCnf
 功能描述  : 处理TAF_MMA_EVT_USER_CFG_OPLMN_QRY_CNF
 输入参数  : TAF_UINT8* pData
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月16日
    作    者   : x65241
    修改内容   : 新生成函数
  2.日    期    : 2013年11月26日
    作    者    : s00190137
    修改内容    : 将最大支持设置的OPLMN扩展到256个
  3.日    期    : 2015年03月31日
    作    者    : K00902809
    修改内容    : changed the function name AT_PhEOPlmnQueryCnfProc to AT_RcvMmaEOPlmnQryCnf
                    and included new structure  TAF_MMA_EOPLMN_QRY_CNF_STRU
*****************************************************************************/
VOS_UINT32 AT_RcvMmaEOPlmnQryCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT16                                              usLen;
    VOS_UINT8                                               ucIndex;
    VOS_UINT32                                              ulRslt;
    TAF_MMA_EOPLMN_QRY_CNF_STRU                            *pstEOPlmnQryCnf = VOS_NULL_PTR;

    usLen            = 0;
    pstEOPlmnQryCnf  = (TAF_MMA_EOPLMN_QRY_CNF_STRU *)pstMsg;

    /* 通过ClientId获取ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstEOPlmnQryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaEOPlmnQryCnf At_ClientIdToUserId FAILURE");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_EOPLMN_QRY */
    if (AT_CMD_EOPLMN_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMmaEOPlmnQryCnf: WARNING:Not AT_CMD_EOPLMN_QRY!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 输出查询结果 */
    if (TAF_ERR_NO_ERROR == pstEOPlmnQryCnf->ulResult)
    {
        usLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLen,
                                        "%s: \"%s\",%d,",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        pstEOPlmnQryCnf->aucVersion,
                                        pstEOPlmnQryCnf->usOPlmnNum * TAF_AT_PLMN_WITH_RAT_LEN);


        /* 将16进制数转换为ASCII码后输入主动命令内容 */
        usLen += (TAF_UINT16)At_HexText2AsciiStringSimple(AT_CMD_MAX_LEN,
                                                            (TAF_INT8 *)pgucAtSndCodeAddr,
                                                            (TAF_UINT8 *)pgucAtSndCodeAddr + usLen,
                                                            pstEOPlmnQryCnf->usOPlmnNum * TAF_SIM_PLMN_WITH_RAT_LEN,
                                                            pstEOPlmnQryCnf->aucOPlmnList);

        gstAtSendData.usBufLen = usLen;

        ulRslt = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
        ulRslt = AT_ERROR;
    }

    At_FormatResultData(ucIndex, ulRslt);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaNetScanCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_NET_SCAN_CNF_STRU          *pstNetScanCnf       = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pstNetScanCnf  = (TAF_MMA_NET_SCAN_CNF_STRU *)pstMsg;

    if (AT_FAILURE == At_ClientIdToUserId(pstNetScanCnf->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaNetScanCnf At_ClientIdToUserId FAILURE");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaNetScanCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    if ( TAF_MMA_NET_SCAN_RESULT_SUCCESS == pstNetScanCnf->enResult )
    {
        AT_PhNetScanReportSuccess(ucIndex, pstNetScanCnf);
    }
    else
    {
        AT_PhNetScanReportFailure(ucIndex, pstNetScanCnf->enCause);
    }

    return VOS_OK;
}

/**********************************************************
 函 数 名  : AT_RcvMmaUserSrvStateQryCnf
 功能描述  : 参数查询结果^USERSRVSTATE的上报处理
 输入参数  : ucIndex - 索引
             OpId    - operation id
             pPara   - 参数内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月11日
    作    者   : s00217060
    修改内容   : 新增函数
  2.日    期   : 2015年03月28日
    作    者   : K00902809
    修改内容   : Modified the function name from  AT_RcvUserSrvStateQryCnf to AT_RcvMmaUserSrvStateQryCnf and structure.
*************************************************************/
VOS_UINT32 AT_RcvMmaUserSrvStateQryCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_USER_SRV_STATE_QRY_CNF_STRU                    *pstUserSrvStateCnf = VOS_NULL_PTR;
    VOS_UINT16                                              usLength;
    VOS_UINT8                                               ucIndex;

    pstUserSrvStateCnf = (TAF_MMA_USER_SRV_STATE_QRY_CNF_STRU *)pstMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstUserSrvStateCnf->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaUserSrvStateQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaUserSrvStateQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_USER_SRV_STATE_READ */
    if (AT_CMD_USER_SRV_STATE_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    usLength  = 0;

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "^USERSRVSTATE: ");

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d,%d",
                                       pstUserSrvStateCnf->ulCsSrvExistFlg,
                                       pstUserSrvStateCnf->ulPsSrvExistFlg);

    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_RcvMmaPwrOnAndRegTimeQryCnf
 功能描述  : 查询AT^APPWRONREG的返回值
 输入参数  :
     VOS_UINT8                           ucIndex,
     VOS_UINT8                           OpId,
     VOS_VOID                           *pPara
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : 欧阳飞
    修改内容   : 新生成函数
  2.日    期   : 2014年1月28日
    作    者   : s00217060
    修改内容   : DTS2014011709107:修改MMA按Slice上报给AT
  3.日    期   : 2015年03月28日
    作    者   : K00902809
    修改内容   : Changed the function name from AT_QryParaRegisterTimeProc to AT_RcvMmaPwrOnAndRegTimeQryCnf
                   and structure to TAF_MMA_POWER_ON_AND_REG_TIME_QRY_CNF_STRU
*****************************************************************************/
VOS_UINT32  AT_RcvMmaPwrOnAndRegTimeQryCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT32                                              ulCostTime;
    VOS_UINT16                                              usLength;
    VOS_UINT32                                              ulResult;
    TAF_MMA_POWER_ON_AND_REG_TIME_QRY_CNF_STRU             *pstAppwronregCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pstAppwronregCnf = (TAF_MMA_POWER_ON_AND_REG_TIME_QRY_CNF_STRU *)pstMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstAppwronregCnf->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPwrOnAndRegTimeQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPwrOnAndRegTimeQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_REGISTER_TIME_READ */
    if (AT_CMD_REGISTER_TIME_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    ulCostTime = pstAppwronregCnf->ulCostTime;

    /* 初始化 */
    ulResult   = AT_OK;
    usLength   = 0;

    /* MMA报给AT时，按slice上报，(32 * 1024)个slice是1S
       如果slice为0，表示没有注册成功；如果slice小于1S,AT按1S上报 */

    /* 将查询时间上报给APP*/
    if ( 0 ==  ulCostTime)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulCostTime = ulCostTime/(32 * 1024);

        if (0 == ulCostTime)
        {
            ulCostTime = 1;
        }

        ulResult   = AT_OK;

        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s",
                                          gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s:%d",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           ulCostTime);
    }

    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex,ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaSpnQryCnf
 功能描述  : 生成AT^SPN设置命令的返回结果
 输入参数  :
     VOS_UINT8                           ucIndex,
     VOS_UINT8                           OpId,
     VOS_VOID                           *pPara
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : 欧阳飞
    修改内容   : 新生成函数
  2.日    期   : 2012年7月24日
    作    者   : z60575
    修改内容   : DTS2012072102200,不存在SPN文件时返回错误码65286
  3.日    期   : 2013年2月22日
    作    者   : l60609
    修改内容   : DSDA PHASE III
  4.日    期   : 2015年03月30日
    作    者   : K00902809
    修改内容   : Modified the function name from MMA_SpnParaProc to AT_RcvMmaSpnQryCnf and structure is added.
*****************************************************************************/
VOS_UINT32  AT_RcvMmaSpnQryCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_SPN_QRY_CNF_STRU           *pstSpnCnf;
    VOS_UINT32                          ulResult;
    TAF_PH_USIM_SPN_STRU                stAtSPNRslt;
    VOS_UINT16                          usLength;
    VOS_UINT16                          usDatalen;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    VOS_UINT8                          *pucSystemAppConfig;
    VOS_UINT8                           ucIndex;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstSpnCnf = (TAF_MMA_SPN_QRY_CNF_STRU *)pstMsg ;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstSpnCnf->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSpnQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSpnQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_SPN_QUERY */
    if (AT_CMD_SPN_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    /* 初始化 */
    ulResult  = AT_OK;
    usLength  = 0;
    usDatalen = 0;

    /* 0 表示SIM */
    if (1 == pstNetCtx->ucSpnType)
    {
        PS_MEM_CPY(&stAtSPNRslt, &(pstSpnCnf->stMnMmaSpnInfo.stUsimSpnInfo), sizeof(TAF_PH_USIM_SPN_STRU));
    }
    else
    {
        PS_MEM_CPY(&stAtSPNRslt, &(pstSpnCnf->stMnMmaSpnInfo.stSimSpnInfo), sizeof(TAF_PH_USIM_SPN_STRU));
    }

    if (0 == stAtSPNRslt.ucLength)
    {
        /*  SPN file not exist */
        ulResult = AT_CME_SPN_FILE_NOT_EXISTS;
    }
    else
    {
        /* display format: ^SPN:disp_rplmn,coding,spn_name */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr+usLength,
                                            "%s:",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName);


        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
        if ( SYSTEM_APP_WEBUI == *pucSystemAppConfig)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr+usLength,
                                               "%d,%d,",
                                               stAtSPNRslt.ucDispRplmnMode & 0x03,
                                               stAtSPNRslt.ucCoding);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr+usLength,
                                               "%d,%d,",
                                               stAtSPNRslt.ucDispRplmnMode & 0x01,
                                               stAtSPNRslt.ucCoding);
        }

        if ( stAtSPNRslt.ucCoding == TAF_PH_GSM_7BIT_DEFAULT )
        {
            usDatalen = stAtSPNRslt.ucLength;
            PS_MEM_CPY(pgucAtSndCodeAddr+usLength,stAtSPNRslt.aucSpnName,usDatalen);
            usLength = usLength + usDatalen;
        }
        else
        {
            usDatalen = stAtSPNRslt.ucLength;

            usLength += (VOS_UINT16)At_HexAlpha2AsciiString(AT_CMD_MAX_LEN,
                                                            (VOS_INT8 *)pgucAtSndCodeAddr,
                                                            (VOS_UINT8 *)pgucAtSndCodeAddr + usLength,
                                                            stAtSPNRslt.aucSpnName,
                                                            (VOS_UINT16)usDatalen);
        }
    }

    gstAtSendData.usBufLen = usLength;

    /* 回复用户命令结果 */
    At_FormatResultData(ucIndex,ulResult);

    return VOS_OK;
}


/**********************************************************
 函 数 名  : At_QryMmPlmnInfoRspProc
 功能描述  : 参数查询结果^MMPLMNINFO的上报处理
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年01月09日
    作    者   : l65478
    修改内容   : 新增函数
  2.日    期   : 2015年01月07日
    作    者   : l00198894
    修改内容   : DTS2014102103988: ^MMPLMNINFO命令显示异常
  3.日    期   : 2015年03月30日
    作    者   : K00902809
    修改内容   : Changed the function name from At_QryMmPlmnInfoRspProc to AT_RcvMmaMMPlmnInfoQryCnf
                 and added new structure.
*************************************************************/
VOS_UINT32  AT_RcvMmaMMPlmnInfoQryCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_MMPLMNINFO_QRY_CNF_STRU    *pstMMPlmnInfoCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT8                           i;
    VOS_UINT8                           ucIndex;

    /* 变量初始化 */
    pstMMPlmnInfoCnf = (TAF_MMA_MMPLMNINFO_QRY_CNF_STRU *)pstMsg;
    ulResult    = AT_ERROR;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstMMPlmnInfoCnf->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaMMPlmnInfoQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaMMPlmnInfoQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_MMPLMNINFO_QRY */
    if (AT_CMD_MMPLMNINFO_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 转换LongName及ShortName */
    if ( pstMMPlmnInfoCnf->stMmPlmnInfo.ucLongNameLen <= TAF_PH_OPER_NAME_LONG
      && pstMMPlmnInfoCnf->stMmPlmnInfo.ucShortNameLen <= TAF_PH_OPER_NAME_SHORT )
    {

        /* ^MMPLMNINFO:<long name>,<short name> */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s:",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        for (i = 0; i < pstMMPlmnInfoCnf->stMmPlmnInfo.ucLongNameLen; i++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%02X",
                                               pstMMPlmnInfoCnf->stMmPlmnInfo.aucLongName[i]);
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr + usLength, ",");

        for (i = 0; i < pstMMPlmnInfoCnf->stMmPlmnInfo.ucShortNameLen; i++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%02X",
                                               pstMMPlmnInfoCnf->stMmPlmnInfo.aucShortName[i]);
        }

        ulResult = AT_OK;
        gstAtSendData.usBufLen = usLength;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
    }

    At_FormatResultData(ucIndex,ulResult);

    return VOS_OK;
}

/**********************************************************
 函 数 名  : At_QryMmPlmnInfoRspProc
 功能描述  : 参数查询结果^PLMN的上报处理
 输入参数  : ucIndex
             OpId
             pPara
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年01月23日
    作    者   : Y00213812
    修改内容   : 新增函数
  2.日    期   : 2015年03月30日
    作    者   : K00902809
    修改内容   : Changed the function name from At_RcvPlmnQryCnf to AT_RcvMmaPlmnQryCnf
                 and added new structure.
*************************************************************/
VOS_UINT32  AT_RcvMmaPlmnQryCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_LAST_CAMP_PLMN_QRY_CNF_STRU                    *pstPlmnCnf = VOS_NULL_PTR;
    VOS_UINT16                                              usLength;
    VOS_UINT8                                               ucIndex;

    pstPlmnCnf = (TAF_MMA_LAST_CAMP_PLMN_QRY_CNF_STRU *)pstMsg;
    usLength  = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstPlmnCnf->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPlmnQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPlmnQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_PLMN_QRY */
    if (AT_CMD_PLMN_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 无效的PLMN */
    if ((0 == pstPlmnCnf->stPlmnId.Mcc)
     && (0 == pstPlmnCnf->stPlmnId.Mnc))
    {
        At_FormatResultData(ucIndex, AT_OK);
        return VOS_ERR;
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s^PLMN: ",
                                       gaucAtCrLf);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%x%x%x,",
                                       (pstPlmnCnf->stPlmnId.Mcc & 0x0f00)>>8,
                                       (pstPlmnCnf->stPlmnId.Mcc & 0xf0)>>4,
                                       (pstPlmnCnf->stPlmnId.Mcc & 0x0f));

    if (0x0f00 == (pstPlmnCnf->stPlmnId.Mnc & 0x0f00))
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%x%x",
                                           (pstPlmnCnf->stPlmnId.Mnc & 0xf0)>>4,
                                           (pstPlmnCnf->stPlmnId.Mnc & 0x0f));
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%x%x%x",
                                           (pstPlmnCnf->stPlmnId.Mnc & 0x0f00)>>8,
                                           (pstPlmnCnf->stPlmnId.Mnc & 0xf0)>>4,
                                           (pstPlmnCnf->stPlmnId.Mnc & 0x0f));
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s",
                                       gaucAtCrLf);

    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex, AT_OK);
    return VOS_OK;

}



/*****************************************************************************
 函 数 名  : AT_RcvMmaCerssiSetCnf
 功能描述  : AT Rcv Mma Set Cerssi Cfg Cnf
 输入参数  : VOS_VOID                           *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月23日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaCerssiSetCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_CERSSI_SET_CNF_STRU        *pstCerssiSetCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstCerssiSetCnf = (TAF_MMA_CERSSI_SET_CNF_STRU *)pstMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCerssiSetCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCerssiSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCerssiSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_CERSSI_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaCerssiSetCnf : Current Option is not AT_CMD_CERSSI_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_ERR_NO_ERROR == pstCerssiSetCnf->enErrorCause)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstCerssiSetCnf->enErrorCause);
    }

    gstAtSendData.usBufLen = 0;

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaPlmnReselAutoSetCnf
 功能描述  : 处理来自MMA模块ID_TAF_MMA_PLMN_RESEL_AUTO_CNF消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月9日
    作    者   : f00279542
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaPlmnReselAutoSetCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_PLMN_AUTO_RESEL_CNF_STRU   *pstPlmnReselAutoCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstPlmnReselAutoCnf = (TAF_MMA_PLMN_AUTO_RESEL_CNF_STRU *)pstMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstPlmnReselAutoCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPlmnReselAutoSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPlmnReselAutoSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_COPS_SET_AUTOMATIC != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaPlmnReselAutoSetCnf : Current Option is not AT_CMD_COPS_SET_AUTOMATIC.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_ERR_NO_ERROR == pstPlmnReselAutoCnf->enErrorCause)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstPlmnReselAutoCnf->enErrorCause);
    }

    gstAtSendData.usBufLen = 0;

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : AT_RcvMmaPlmnSpecialSelSetCnf
 功能描述  : 处理来自MMA模块ID_TAF_MMA_PLMN_USER_SEL_CNF消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月31日
    作    者   : f00279542
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaPlmnSpecialSelSetCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_PLMN_SPECIAL_SEL_CNF_STRU  *pstPlmnSpecialSelCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstPlmnSpecialSelCnf = (TAF_MMA_PLMN_SPECIAL_SEL_CNF_STRU *)pstMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstPlmnSpecialSelCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPlmnSpecialSelSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPlmnSpecialSelSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_COPS_SET_MANUAL != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaPlmnSpecialSelSetCnf : Current Option is not AT_CMD_COPS_SET_MANUAL.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_ERR_NO_ERROR == pstPlmnSpecialSelCnf->enErrorCause)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstPlmnSpecialSelCnf->enErrorCause);
    }

    gstAtSendData.usBufLen = 0;

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : AT_RcvMmaPlmnListAbortCnf
 功能描述  : 处理来自MMA模块ID_TAF_MMA_PLMN_LIST_ABORT_CNF消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月31日
    作    者   : f00279542
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaPlmnListAbortCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_PLMN_LIST_ABORT_CNF_STRU   *pstPlmnListAbortCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstPlmnListAbortCnf = (TAF_MMA_PLMN_LIST_ABORT_CNF_STRU *)pstMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstPlmnListAbortCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPlmnSpecialSelSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPlmnSpecialSelSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    /* 容错处理, 当前不在列表搜ABORT过程中则不上报ABORT.
       如AT的ABORT保护定时器已超时, 之后再收到MMA的ABORT_CNF则不上报ABORT */
    if (AT_CMD_COPS_ABORT_PLMN_LIST != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaPlmnSpecialSelSetCnf : Current Option is not AT_CMD_COPS_SET_MANUAL.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    ulResult = AT_ABORT;

    gstAtSendData.usBufLen = 0;

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : AT_RcvMmaPowerDownCnf
 功能描述  : 处理来自MMA模块ID_TAF_MMA_MT_POWER_DOWN_CNF消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月31日
    作    者   : f00279542
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaPowerDownCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_MT_POWER_DOWN_CNF_STRU     *pstPrefPlmnTypeSetCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstPrefPlmnTypeSetCnf = (TAF_MMA_MT_POWER_DOWN_CNF_STRU *)pstMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstPrefPlmnTypeSetCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPowerDownCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPowerDownCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_MMA_MT_POWER_DOWN != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaPowerDownCnf : Current Option is not AT_CMD_MMA_MT_POWER_DOWN.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_ERR_NO_ERROR == pstPrefPlmnTypeSetCnf->enErrorCause)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : AT_RcvMmaPrefPlmnTypeSetCnf
 功能描述  : 处理来自MMA模块ID_TAF_MMA_CPLS_SET_CNF消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月31日
    作    者   : f00279542
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaPrefPlmnTypeSetCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_PREF_PLMN_TYPE_SET_CNF_STRU    *pstPrefPlmnTypeSetCnf = VOS_NULL_PTR;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;
    AT_MODEM_NET_CTX_STRU                  *pstNetCtx = VOS_NULL_PTR;

    pstPrefPlmnTypeSetCnf = (TAF_MMA_PREF_PLMN_TYPE_SET_CNF_STRU *)pstMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstPrefPlmnTypeSetCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPrefPlmnTypeSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPrefPlmnTypeSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_MMA_SET_PREF_PLMN_TYPE != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaPrefPlmnTypeSetCnf : Current Option is not AT_CMD_MMA_SET_PREF_PLMN_TYPE.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    pstNetCtx->enPrefPlmnType = pstPrefPlmnTypeSetCnf->enPrefPlmnType;

    ulResult = AT_OK;

    gstAtSendData.usBufLen = 0;

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : AT_RcvMmaPhoneModeQryCnf
 功能描述  : 处理来自MMA模块ID_TAF_MMA_Phone_Mode_Qry_CNF消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月9日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaPhoneModeQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_PHONE_MODE_QRY_CNF_STRU    *pstPhoneModeQryCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstPhoneModeQryCnf = (TAF_MMA_PHONE_MODE_QRY_CNF_STRU *)pMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstPhoneModeQryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPhoneModeQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPhoneModeQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前操作是否为查询操作AT_CMD_CFUN_READ */
    if (AT_CMD_CFUN_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaPhoneModeQryCnf : Current Option is not AT_CMD_CFUN_READ.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = 0;

    if (TAF_ERR_NO_ERROR == pstPhoneModeQryCnf->enErrorCause)
    {
        gstAtSendData.usBufLen  = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                         "%s: %d",
                                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                         pstPhoneModeQryCnf->ucPhMode);
        ulResult = AT_OK;
    }
    else
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstPhoneModeQryCnf->enErrorCause);
    }

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvTafMmaQuickStartSetCnf
 功能描述  : AT^CQST
 输入参数  : *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月24日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvTafMmaQuickStartSetCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_QUICKSTART_SET_CNF_STRU    *pstQuickStartSetCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstQuickStartSetCnf = (TAF_MMA_QUICKSTART_SET_CNF_STRU *)pMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstQuickStartSetCnf->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaQuickStartSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaQuickStartSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前操作是否为查询操作AT_CMD_CQST_SET */
    if (AT_CMD_CQST_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvTafMmaQuickStartSetCnf : Current Option is not AT_CMD_CQST_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_PARA_OK == pstQuickStartSetCnf->ucResult)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvTafMmaAutoAttachSetCnf
 功能描述  : AT^CAATT SET返回结果处理
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月26日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvTafMmaAutoAttachSetCnf(
    VOS_VOID                           *pMsg
)
{
     TAF_MMA_AUTO_ATTACH_SET_CNF_STRU   *pstAutoAttachSetCnf = VOS_NULL_PTR;
     VOS_UINT8                           ucIndex;
     AT_RRETURN_CODE_ENUM_UINT32         ulResult = AT_FAILURE;

     pstAutoAttachSetCnf = (TAF_MMA_AUTO_ATTACH_SET_CNF_STRU *)pMsg;

     ucIndex             = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

     /* 通过clientid获取index */
     if (AT_FAILURE == At_ClientIdToUserId(pstAutoAttachSetCnf->stCtrl.usClientId, &ucIndex))
     {
         AT_WARN_LOG("AT_RcvTafMmaAutoAttachSetCnf : WARNING:AT INDEX NOT FOUND!");
         return VOS_ERR;
     }

     if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
     {
         AT_WARN_LOG("AT_RcvTafMmaAutoAttachSetCnf : AT_BROADCAST_INDEX.");
         return VOS_ERR;
     }

     /* 当前操作是否为查询操作AT_CMD_CAATT_SET */
     if (AT_CMD_CAATT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
     {
         AT_WARN_LOG("AT_RcvTafMmaAutoAttachSetCnf : Current Option is not AT_CMD_CAATT_SET.");
         return VOS_ERR;
     }

     AT_STOP_TIMER_CMD_READY(ucIndex);

     if (TAF_PARA_OK == pstAutoAttachSetCnf->ucResult)
     {
         ulResult = AT_OK;
     }
     else
     {
         ulResult = AT_ERROR;
     }

     /* 调用At_FormatResultData发送命令结果 */
     At_FormatResultData(ucIndex, ulResult);

     return VOS_OK;

}

/*****************************************************************************
 函 数 名  : AT_RcvTafMmaSyscfgQryCnf
 功能描述  : AT+SYSCFG or AT+SYSCFGEX命令返回并输出
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月26日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvTafMmaSyscfgQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_SYSCFG_QRY_CNF_STRU        *pstSyscfgQryCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    AT_RRETURN_CODE_ENUM_UINT32         ulResult = AT_FAILURE;
    TAF_UINT16                          usLength = VOS_NULL;

    pstSyscfgQryCnf = (TAF_MMA_SYSCFG_QRY_CNF_STRU *)pMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstSyscfgQryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaSyscfgQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaSyscfgQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    if(TAF_ERR_NO_ERROR != pstSyscfgQryCnf->enErrorCause)  /* MT本地错误 */
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstSyscfgQryCnf->enErrorCause);       /* 发生错误 */
    }
    else if(AT_CMD_SYSCFG_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);

        AT_ReportSysCfgQryCmdResult(&(pstSyscfgQryCnf->stSysCfg), ucIndex, &usLength);

        ulResult = AT_OK;
    }
    else if (AT_CMD_SYSCFGEX_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);

        AT_ReportSysCfgExQryCmdResult(&(pstSyscfgQryCnf->stSysCfg), ucIndex, &usLength);

        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : AT_RcvMmaAccessModeQryCnf
 功能描述  : AT Rcv Mma Access Mode Qry Cnf
 输入参数  : VOS_VOID                           *pMsg
 输出参数  : VOS_UINT32
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaAccessModeQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_ACCESS_MODE_QRY_CNF_STRU   *pstAccessModeCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    pstAccessModeCnf    = (TAF_MMA_ACCESS_MODE_QRY_CNF_STRU *)pMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstAccessModeCnf->stCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAccessModeQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAccessModeQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_CPAM_READ */
    if (AT_CMD_CPAM_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    /* 如果查询的接入模式为无效值，则返回ERROR，例如当前LTE only不支持GU */
    if (pstAccessModeCnf->enAccessMode >= MN_MMA_CPAM_RAT_TYPE_BUTT)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                                         "%s: %d,%d",
                                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                         pstAccessModeCnf->enAccessMode,
                                                         pstAccessModeCnf->ucPlmnPrio);
    }

    At_FormatResultData(ucIndex,ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaCopsQryCnf
 功能描述  : At Rcv Mma Cops Qry Cnf
 输入参数  : VOS_VOID                           *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaCopsQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_COPS_QRY_CNF_STRU          *pstCopsQryCnf;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    pstCopsQryCnf    = (TAF_MMA_COPS_QRY_CNF_STRU *)pMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCopsQryCnf->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCopsQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCopsQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_COPS_READ */
    if (AT_CMD_COPS_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    At_QryParaRspCopsProc(ucIndex, pstCopsQryCnf->ucOpId, (VOS_VOID *)&(pstCopsQryCnf->stCopsInfo));

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaRegStateQryCnf
 功能描述  : AT Rcv Mma reg state Qry Cnf
 输入参数  : VOS_VOID                           *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaRegStateQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_REG_STATE_QRY_CNF_STRU     *pstRegStateCnf;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    pstRegStateCnf    = (TAF_MMA_REG_STATE_QRY_CNF_STRU *)pMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRegStateCnf->stCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaRegStateQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaRegStateQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_CREG_READ */
    if (AT_CMD_CREG_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        /* 复位AT状态 */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        At_QryParaRspCregProc(ucIndex, pstRegStateCnf->stCtrl.ucOpId, (VOS_VOID *)&(pstRegStateCnf->stRegInfo));
    }
    else if (AT_CMD_CGREG_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        /* 复位AT状态 */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        At_QryParaRspCgregProc(ucIndex, pstRegStateCnf->stCtrl.ucOpId, (VOS_VOID *)&(pstRegStateCnf->stRegInfo));
    }
#if(FEATURE_ON == FEATURE_LTE)
    else if (AT_CMD_CEREG_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        /* 复位AT状态 */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        AT_QryParaRspCeregProc(ucIndex, pstRegStateCnf->stCtrl.ucOpId, (VOS_VOID *)&(pstRegStateCnf->stRegInfo));
    }
#endif
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaAutoAttachQryCnf
 功能描述  : AT Rcv Mma Auto Attach Qry Cnf
 输入参数  : VOS_VOID                           *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月28日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaAutoAttachQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_AUTO_ATTACH_QRY_CNF_STRU   *pstAutoAttachCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    pstAutoAttachCnf    = (TAF_MMA_AUTO_ATTACH_QRY_CNF_STRU *)pMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstAutoAttachCnf->stCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAutoAttachQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAutoAttachQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_CAATT_READ */
    if (AT_CMD_CAATT_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    if (TAF_ERR_NO_ERROR == pstAutoAttachCnf->enErrorCause)
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                                         "%s: %d",
                                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                         pstAutoAttachCnf->ucAutoAttachFlag);
    }
    else
    {
        ulResult = AT_ERROR;
    }

    At_FormatResultData(ucIndex,ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaSysInfoQryCnf
 功能描述  : AT Rcv Mma Sys Info Qry Cnf
 输入参数  : VOS_VOID                           *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月28日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaSysInfoQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_SYSINFO_QRY_CNF_STRU       *pstSysInfoCnf;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    pstSysInfoCnf  = (TAF_MMA_SYSINFO_QRY_CNF_STRU *)pMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstSysInfoCnf->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSysInfoQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (VOS_FALSE == pstSysInfoCnf->ucIsSupport)
    {
        /* 复位AT状态 */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        At_FormatResultData(ucIndex,AT_CMD_NOT_SUPPORT);

        return VOS_OK;

    }


    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSysInfoQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_SYSINFO_READ */
    if (AT_CMD_SYSINFO_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        /* 复位AT状态 */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        At_QryParaRspSysinfoProc(ucIndex, pstSysInfoCnf->ucOpId, (VOS_VOID *)&(pstSysInfoCnf->stSysInfo));

        return VOS_OK;
    }
    else if (AT_CMD_SYSINFOEX_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        /* 复位AT状态 */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        AT_QryParaRspSysinfoExProc(ucIndex, pstSysInfoCnf->ucOpId, (VOS_VOID *)&(pstSysInfoCnf->stSysInfo));

        return VOS_OK;
    }
    else
    {
        return VOS_ERR;
    }
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaAnqueryQryCnf
 功能描述  : At Rcv Mma Anquery Qry Cnf
 输入参数  : VOS_VOID                           *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月30日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaAnqueryQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_ANTENNA_INFO_QRY_CNF_STRU  *pstAnqueryCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    pstAnqueryCnf  = (TAF_MMA_ANTENNA_INFO_QRY_CNF_STRU *)pMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstAnqueryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAnqueryQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAnqueryQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_ANQUERY_READ */
    if (AT_CMD_ANQUERY_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_ERR_NO_ERROR == pstAnqueryCnf->enErrorCause)
    {
        AT_QryParaAnQueryProc(ucIndex,
                              pstAnqueryCnf->stCtrl.ucOpId,
                              (VOS_VOID *)&(pstAnqueryCnf->stAntennaInfo));
    }
    else
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstAnqueryCnf->enErrorCause);

        At_FormatResultData(ucIndex, ulResult);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaEHplmnInfoQryCnf
 功能描述  : AT收到MMA的ID_TAF_MMA_HOME_PLMN_QRY_CNF处理
 输入参数  : VOS_VOID                           *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月24日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaEHplmnInfoQryCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_HOME_PLMN_QRY_CNF_STRU     *pstHplmnCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pstHplmnCnf  = (TAF_MMA_HOME_PLMN_QRY_CNF_STRU *)pstMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstHplmnCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaEHplmnInfoQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaEHplmnInfoQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 根据当前操作类型进入^HPLMN/^APHPLMN的处理 */
    if (AT_CMD_HOMEPLMN_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        /* ^APHPLMN */
        return AT_RcvMmaApHplmnQryCnf(ucIndex, pstMsg);
    }
    else if (AT_CMD_EHPLMN_LIST_QRY == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        /* ^HPLMN */
        return AT_RcvMmaHplmnQryCnf(ucIndex, pstMsg);
    }
    else
    {
        return VOS_ERR;
    }

}

/*****************************************************************************
 函 数 名  : AT_RcvMmaApHplmnQryCnf
 功能描述  : AT Rcv Mma ApHPLMN Qry Cnf
 输入参数  : VOS_VOID                           *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月30日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaApHplmnQryCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_HOME_PLMN_QRY_CNF_STRU     *pstHplmnCnf;
    VOS_UINT32                          ulResult;
    TAF_MMA_HPLMN_WITH_MNC_LEN_STRU     stHplmn;

    /* 初始化 */
    pstHplmnCnf  = (TAF_MMA_HOME_PLMN_QRY_CNF_STRU *)pstMsg;

    /* index的异常判断移到AT_RcvMmaEHplmnInfoQryCnf中 */

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_ERR_NO_ERROR == pstHplmnCnf->enErrorCause)
    {
        PS_MEM_SET(&stHplmn, 0, sizeof(TAF_MMA_HPLMN_WITH_MNC_LEN_STRU));
        stHplmn.ucHplmnMncLen   = pstHplmnCnf->stEHplmnInfo.ucHplmnMncLen;

        stHplmn.stHplmn.Mcc     = (pstHplmnCnf->stEHplmnInfo.aucImsi[1] & 0xF0) >> 4;
        stHplmn.stHplmn.Mcc     |= (pstHplmnCnf->stEHplmnInfo.aucImsi[2] & 0x0F) << 8;
        stHplmn.stHplmn.Mcc     |= (pstHplmnCnf->stEHplmnInfo.aucImsi[2] & 0xF0) << 12;

        stHplmn.stHplmn.Mnc     = (pstHplmnCnf->stEHplmnInfo.aucImsi[3] & 0x0F);
        stHplmn.stHplmn.Mnc     |= (pstHplmnCnf->stEHplmnInfo.aucImsi[3] & 0xF0) << 4;
        stHplmn.stHplmn.Mnc     |= (pstHplmnCnf->stEHplmnInfo.aucImsi[4] & 0x0F) << 16;

        AT_QryParaHomePlmnProc(ucIndex,
                               pstHplmnCnf->stCtrl.ucOpId,
                               (VOS_VOID *)&stHplmn);

        return VOS_OK;
    }
    else
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstHplmnCnf->enErrorCause);

        gstAtSendData.usBufLen = 0;

        At_FormatResultData(ucIndex,ulResult);

        return VOS_ERR;
    }
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaSrvStatusInd
 功能描述  : AT Proc Service Status Ind
 输入参数  : VOS_VOID                           *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月31日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaSrvStatusInd(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_SRV_STATUS_IND_STRU        *pstSrvStatusInd;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;

    /* 初始化消息变量 */
    ucIndex             = 0;
    usLength            = 0;
    pstSrvStatusInd     = (TAF_MMA_SRV_STATUS_IND_STRU*)pstMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstSrvStatusInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaSrvStatusInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &enModemId))
    {
        AT_ERR_LOG("AT_RcvMmaSrvStatusInd: Get modem id fail.");
        return VOS_ERR;
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s%s%d%s",
                                       gaucAtCrLf,
                                       gastAtStringTab[AT_STRING_SRVST].pucText,
                                       pstSrvStatusInd->ucSrvStatus,
                                       gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaRssiInfoInd
 功能描述  : AT Proc Rssi Info Ind
 输入参数  : VOS_VOID                           *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月31日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaRssiInfoInd(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_RSSI_INFO_IND_STRU         *pstRssiInfoInd;
    VOS_UINT8                           ucIndex;

    /* 初始化消息变量 */
    ucIndex            = 0;
    pstRssiInfoInd     = (TAF_MMA_RSSI_INFO_IND_STRU*)pstMsg;

    /* 通过ClientId获取ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRssiInfoInd->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaRssiInfoInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    AT_RcvMmaRssiChangeInd(ucIndex, pstRssiInfoInd);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaRegStatusInd
 功能描述  : AT Proc Reg Status Ind
 输入参数  : VOS_VOID                           *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月31日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaRegStatusInd(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_REG_STATUS_IND_STRU        *pstRegStatusInd;
    VOS_UINT8                           ucIndex;

    /* 初始化消息变量 */
    ucIndex             = 0;
    pstRegStatusInd     = (TAF_MMA_REG_STATUS_IND_STRU*)pstMsg;

    /* 通过ClientId获取ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRegStatusInd->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaRegStatusInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    AT_ProcRegStatusInfoInd(ucIndex, pstRegStatusInd);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaRegRejInfoInd
 功能描述  : AT Proc Mma Reg Rej Info Ind
 输入参数  : VOS_VOID                           *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月31日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaRegRejInfoInd(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_REG_REJ_INFO_IND_STRU      *pstRegRejInd;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;

    /* 初始化消息变量 */
    ucIndex          = 0;
    usLength         = 0;
    pstRegRejInd     = (TAF_MMA_REG_REJ_INFO_IND_STRU*)pstMsg;

    /* 通过ClientId获取ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRegRejInd->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaRegRejInfoInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &enModemId))
    {
        AT_ERR_LOG("AT_RcvMmaRegRejInfoInd: Get modem id fail.");
        return VOS_ERR;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s%s",
                                       gaucAtCrLf,
                                       gastAtStringTab[AT_STRING_REJINFO].pucText);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%x%x%x",
                                       (pstRegRejInd->stRegRejInfo.stPlmnId.Mcc & 0x0f00)>>8,
                                       (pstRegRejInd->stRegRejInfo.stPlmnId.Mcc & 0xf0)>>4,
                                       (pstRegRejInd->stRegRejInfo.stPlmnId.Mcc & 0x0f));

    if (0x0f00 == (pstRegRejInd->stRegRejInfo.stPlmnId.Mnc & 0x0f00))
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%x%x,",
                                           (pstRegRejInd->stRegRejInfo.stPlmnId.Mnc & 0xf0)>>4,
                                           (pstRegRejInd->stRegRejInfo.stPlmnId.Mnc & 0x0f));
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%x%x%x,",
                                           (pstRegRejInd->stRegRejInfo.stPlmnId.Mnc & 0x0f00)>>8,
                                           (pstRegRejInd->stRegRejInfo.stPlmnId.Mnc & 0xf0)>>4,
                                           (pstRegRejInd->stRegRejInfo.stPlmnId.Mnc & 0x0f));
    }
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d,%d,%d,%d,%d,",
                                       pstRegRejInd->stRegRejInfo.enSrvDomain,
                                       pstRegRejInd->stRegRejInfo.ulRejCause,
                                       pstRegRejInd->stRegRejInfo.enRat,
                                       pstRegRejInd->stRegRejInfo.ucRejType,
                                       pstRegRejInd->stRegRejInfo.ucOriginalRejCause);

    /* lac */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                (VOS_CHAR *)pgucAtSndCodeAddr,
                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                "\"%X%X%X%X\",",
                0x000f & (pstRegRejInd->stRegRejInfo.usLac >> 12),
                0x000f & (pstRegRejInd->stRegRejInfo.usLac >> 8),
                0x000f & (pstRegRejInd->stRegRejInfo.usLac >> 4),
                0x000f & (pstRegRejInd->stRegRejInfo.usLac >> 0));

    /* Rac */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                (VOS_CHAR *)pgucAtSndCodeAddr,
                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                "\"%X%X\",",
                0x000f & (pstRegRejInd->stRegRejInfo.ucRac >> 4),
                0x000f & (pstRegRejInd->stRegRejInfo.ucRac >> 0));


    /* <CI>域以4字节方式上报 */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
            (VOS_CHAR *)pgucAtSndCodeAddr,
            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
            "\"%X%X%X%X%X%X%X%X\"%s",
            0x000f & (pstRegRejInd->stRegRejInfo.ulCellId >> 28),
            0x000f & (pstRegRejInd->stRegRejInfo.ulCellId >> 24),
            0x000f & (pstRegRejInd->stRegRejInfo.ulCellId >> 20),
            0x000f & (pstRegRejInd->stRegRejInfo.ulCellId >> 16),
            0x000f & (pstRegRejInd->stRegRejInfo.ulCellId >> 12),
            0x000f & (pstRegRejInd->stRegRejInfo.ulCellId >> 8),
            0x000f & (pstRegRejInd->stRegRejInfo.ulCellId >> 4),
            0x000f & (pstRegRejInd->stRegRejInfo.ulCellId >> 0),
            gaucAtCrLf);


    gstAtSendData.usBufLen = usLength;

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaPlmnSelectInfoInd
 功能描述  : At Proc Mma Plmn Selection Info Ind
 输入参数  : VOS_VOID                           *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月31日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaPlmnSelectInfoInd(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_PLMN_SElECTION_INFO_IND_STRU   *pstPlmnSelecInd;
    MODEM_ID_ENUM_UINT16                    enModemId;
    VOS_UINT16                              usLength;
    VOS_UINT8                               ucIndex;

    /* 初始化消息变量 */
    ucIndex             = 0;
    usLength            = 0;
    pstPlmnSelecInd     = (TAF_MMA_PLMN_SElECTION_INFO_IND_STRU*)pstMsg;

    /* 通过ClientId获取ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstPlmnSelecInd->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPlmnSelectInfoInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &enModemId))
    {
        AT_ERR_LOG("AT_RcvMmaPlmnSelectInfoInd: Get modem id fail.");
        return VOS_ERR;
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s%s",
                                       gaucAtCrLf,
                                       gastAtStringTab[AT_STRING_PLMNSELEINFO].pucText);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d,%d%s",
                                       pstPlmnSelecInd->stPlmnSelectInfo.ulPlmnSelectFlag,
                                       pstPlmnSelecInd->stPlmnSelectInfo.ulPlmnSelectRlst,
                                       gaucAtCrLf);

    gstAtSendData.usBufLen = usLength;

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvTafMmaSyscfgTestCnf
 功能描述  : at 处理syscfg test 返回命令结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月26日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvTafMmaSyscfgTestCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_SYSCFG_TEST_CNF_STRU       *pstSysCfgTestCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstSysCfgTestCnf = (TAF_MMA_SYSCFG_TEST_CNF_STRU *)pMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstSysCfgTestCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaSyscfgTestCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaSyscfgTestCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    /* SYSCFG */
    if (AT_CMD_SYSCFG_TEST == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        if (AT_ROAM_FEATURE_OFF == pstNetCtx->ucRoamFeature)
        {
            AT_STOP_TIMER_CMD_READY(ucIndex);
            gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR*)pgucAtSndCodeAddr,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            "%s: (2,13,14,16),(0-3),%s,(0-2),(0-4)",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            pstSysCfgTestCnf->stBandInfo.strSysCfgBandGroup);
        }
        else
        {
            AT_STOP_TIMER_CMD_READY(ucIndex);
            gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR*)pgucAtSndCodeAddr,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            "%s: (2,13,14,16),(0-3),%s,(0-3),(0-4)",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            pstSysCfgTestCnf->stBandInfo.strSysCfgBandGroup);
        }

    }
    /* SYSCFGEX */
    else
    {
        if (AT_ROAM_FEATURE_OFF == pstNetCtx->ucRoamFeature)
        {
            AT_STOP_TIMER_CMD_READY(ucIndex);
            gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR*)pgucAtSndCodeAddr,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            "%s: (\"00\",\"01\",\"02\",\"03\",\"030201\",\"030102\",\"020301\",\"020103\",\"010203\",\"010302\",\"0302\",\"0301\",\"0201\",\"0203\",\"0102\",\"0103\",\"99\"),%s,(0-2),(0-4),((7fffffffffffffff,\"All bands\"))",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            pstSysCfgTestCnf->stBandInfo.strSysCfgBandGroup);
        }
        else
        {
            AT_STOP_TIMER_CMD_READY(ucIndex);
            gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR*)pgucAtSndCodeAddr,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            "%s: (\"00\",\"01\",\"02\",\"03\",\"030201\",\"030102\",\"020301\",\"020103\",\"010203\",\"010302\",\"0302\",\"0301\",\"0201\",\"0203\",\"0102\",\"0103\",\"99\"),%s,(0-2),(0-4),((7fffffffffffffff,\"All bands\"))",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            pstSysCfgTestCnf->stBandInfo.strSysCfgBandGroup);
        }
    }

    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_RcvTafMmaQuickStartQryCnf
 功能描述  : AT处理CQST QRY 查询结果并输出
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月27日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvTafMmaQuickStartQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_QUICKSTART_QRY_CNF_STRU    *pstQuickStartQryCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    pstQuickStartQryCnf = (TAF_MMA_QUICKSTART_QRY_CNF_STRU *)pMsg;
    ulResult = AT_OK;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstQuickStartQryCnf->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaQuickStartQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaQuickStartQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_CQST_READ */
    if (AT_CMD_CQST_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    /* 如果查询的接入模式为无效值，则返回ERROR，例如当前LTE only不支持GU */
    if (TAF_ERR_NO_ERROR != pstQuickStartQryCnf->enErrorCause)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                                         "%s: %d",
                                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                         pstQuickStartQryCnf->ulQuickStartMode);
    }

    At_FormatResultData(ucIndex,ulResult);
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvTafMmaCsnrQryCnf
 功能描述  : AT处理来自MMA的csnr qry查询返回结果并输出上报
 输入参数  : *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月28日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvTafMmaCsnrQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_CSNR_QRY_CNF_STRU          *pstrCsnrQryCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    pstrCsnrQryCnf = (TAF_MMA_CSNR_QRY_CNF_STRU *)pMsg;
    ulResult = AT_OK;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstrCsnrQryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaCsnrQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaCsnrQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_CSNR_READ */
    if (AT_CMD_CSNR_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    if (TAF_ERR_NO_ERROR  != pstrCsnrQryCnf->enErrorCause)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    (TAF_INT32)pstrCsnrQryCnf->stCsnrPara.sCpichRscp,
                                                    (TAF_INT32)pstrCsnrQryCnf->stCsnrPara.sCpichEcNo);
    }

    /* 回复用户命令结果 */
    At_FormatResultData(ucIndex,ulResult);
    return  VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvTafMmaCsqQryCnf
 功能描述  : AT处理CSQ QRY查询结果并输出
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月28日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvTafMmaCsqQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_CSQ_QRY_CNF_STRU           *pstrCsqQryCnf;
    VOS_UINT32                          ulResult = AT_FAILURE;
    VOS_UINT8                           ucIndex;
    TAF_UINT16                          usLength = 0;
    TAF_PH_RSSI_STRU                    stCsq;

    /* 初始化 */
    pstrCsqQryCnf = (TAF_MMA_CSQ_QRY_CNF_STRU *)pMsg;
    ulResult = AT_OK;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstrCsqQryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaCsqQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaCsqQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_CSQ_SET */
    if (AT_CMD_CSQ_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    PS_MEM_CPY(&stCsq, &pstrCsqQryCnf->stCsq, sizeof(TAF_PH_RSSI_STRU));
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    if (TAF_ERR_NO_ERROR  != pstrCsqQryCnf->enErrorCause)
    {
        ulResult = AT_ERROR;
    }
    else{
        ulResult = AT_OK;
        if(stCsq.ucRssiNum > 0)
        {
            /* 增加范围限制 */
            if((stCsq.aRssi[0].ucRssiValue >= 31) && (stCsq.aRssi[0].ucRssiValue < 99))
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%d",31);
            }
            else
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%d",stCsq.aRssi[0].ucRssiValue);
            }
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,",%d",stCsq.aRssi[0].ucChannalQual);
        }
    }

    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex,ulResult);
    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : AT_RcvTafMmaCsqlvlQryCnf
 功能描述  : AT收到来自MMA的csqlvl qry 消息处理结果并上报
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月28日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvTafMmaCsqlvlQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_CSQLVL_QRY_CNF_STRU        *pstrCsqlvlQryCnf;
    VOS_UINT32                          ulResult = AT_FAILURE;
    VOS_UINT8                           ucIndex;
    TAF_MMA_CSQLVL_PARA_STRU            stCsqlvl;
    TAF_MMA_CSQLVLEXT_PARA_STRU         stCsqlvlext;

    /* 初始化 */
    pstrCsqlvlQryCnf = (TAF_MMA_CSQLVL_QRY_CNF_STRU *)pMsg;
    ulResult = AT_OK;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstrCsqlvlQryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaCsqlvlQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaCsqlvlQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    PS_MEM_CPY(&stCsqlvlext, &pstrCsqlvlQryCnf->stCsqLvlExtPara, sizeof(TAF_MMA_CSQLVLEXT_PARA_STRU));
    PS_MEM_CPY(&stCsqlvl, &pstrCsqlvlQryCnf->stCsqLvlPara, sizeof(TAF_MMA_CSQLVL_PARA_STRU));

    if (TAF_ERR_NO_ERROR  == pstrCsqlvlQryCnf->enErrorCause)
    {
        if (AT_CMD_CSQLVL_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
        {
            /* 复位AT状态 */
            AT_STOP_TIMER_CMD_READY(ucIndex);

            ulResult = AT_OK;
            /* 根据MMA上报的查询结果显示Csqlvl到串口；*/
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                            (VOS_CHAR*)pgucAtSndCodeAddr,
                                                            (VOS_CHAR*)pgucAtSndCodeAddr,
                                                            "%s: %d,%d",
                                                             g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                             stCsqlvl.usLevel,
                                                             stCsqlvl.usRscp);
        }
        else if (AT_CMD_CSQLVLEXT_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
        {
            /* 复位AT状态 */
            AT_STOP_TIMER_CMD_READY(ucIndex);

            ulResult = AT_OK;
            /* 根据MMA上报的查询结果显示Csqlvl到串口；*/
            /* 根据MMA上报的查询结果显示CsqlvlExt到串口；*/
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR*)pgucAtSndCodeAddr,
                                                            (VOS_CHAR*)pgucAtSndCodeAddr,
                                                            "%s: %d,%d",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            stCsqlvlext.enRssilv,
                                                            stCsqlvlext.enBer);
        }
        else
        {
            ulResult = AT_ERROR;
        }

    }
    else
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstrCsqlvlQryCnf->enErrorCause);
    }


    At_FormatResultData(ucIndex,ulResult);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaTimeChangeInd
 功能描述  : 收到TIME CHANGE IND 后AT处理函数
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOID_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月30日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaTimeChangeInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_TIME_CHANGE_IND_STRU       *pstTimeChangeInd;
    TAF_UINT16                          usLength;

    /* 初始化消息变量 */
    ucIndex             = 0;
    pstTimeChangeInd    = (TAF_MMA_TIME_CHANGE_IND_STRU*)pMsg;
    usLength            = 0;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstTimeChangeInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaTimeChangeInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }


    if ((NAS_MM_INFO_IE_UTLTZ == (pstTimeChangeInd->ucIeFlg & NAS_MM_INFO_IE_UTLTZ))
     || (NAS_MM_INFO_IE_LTZ == (pstTimeChangeInd->ucIeFlg & NAS_MM_INFO_IE_LTZ)))
    {
        /* 存在时间信息 */
        /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, end */
        usLength += (TAF_UINT16)At_PrintMmTimeInfo(ucIndex,
                                                   pstTimeChangeInd,
                                                   (pgucAtSndCodeAddr + usLength));
        /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, end */
    }

    At_SendResultData(ucIndex,pgucAtSndCodeAddr,usLength);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaModeChangeInd
 功能描述  : AT处理mode change主动上报接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月31日
    作    者   : y00322978
    修改内容   : 新生成函数
  2.日    期   : 2015年08月22日
    作    者   : y00307564
    修改内容   : DTS2015081005519修改
*****************************************************************************/
VOS_UINT32 AT_RcvMmaModeChangeInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT16                          usLength;
    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;
    TAF_MMA_MODE_CHANGE_IND_STRU       *pstRcvMsg;
    pstRcvMsg = (TAF_MMA_MODE_CHANGE_IND_STRU *)pMsg;
    usLength  = 0;
    enModemId = MODEM_ID_0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaCsqlvlextQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    ulRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_RcvMmaModeChangeInd: Get modem id fail.");
        return VOS_ERR;
    }

    /* ^Mode命令处理，需要将L模显示为W模式,与SYSINFO保持一致 */
    if (TAF_PH_INFO_LTE_RAT == pstRcvMsg->RatType)
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s%s%d,%d%s",
                                           gaucAtCrLf,
                                           gastAtStringTab[AT_STRING_MODE].pucText,
                                           TAF_PH_INFO_WCDMA_RAT,
                                           TAF_SYS_SUBMODE_WCDMA,
                                           gaucAtCrLf);
    }



    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s%s%d,%d%s",
                                           gaucAtCrLf,
                                           gastAtStringTab[AT_STRING_MODE].pucText,
                                           pstRcvMsg->RatType,
                                           pstRcvMsg->ucSysSubMode,
                                           gaucAtCrLf);
    }

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    /* Deleted by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    /* 此处全局变量维护不再准确，需要删除，用时从C核获取 */
    /* Deleted by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, end */

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : AT_RcvMmaPlmnChangeInd
 功能描述  : plmn change主动上报AT处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月31日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaPlmnChangeInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT16                          usLength;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;
    TAF_MMA_PLMN_CHANGE_IND_STRU       *pstRcvMsg;

    usLength  = 0;
    pstRcvMsg = (TAF_MMA_PLMN_CHANGE_IND_STRU *)pMsg;
    enModemId = MODEM_ID_0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaCsqlvlextQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }
    ulRslt    = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("At_RcvMmaPlmnChangeIndProc: Get modem id fail.");
        return VOS_ERR;
    }

    /* Deleted by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    /* Deleted by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, end */

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s^PLMN:",gaucAtCrLf);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr +
                                       usLength,
                                       "%x%x%x,",
                                       (pstRcvMsg->stCurPlmn.Mcc & 0x0f00)>>8,
                                       (pstRcvMsg->stCurPlmn.Mcc & 0xf0)>>4,
                                       (pstRcvMsg->stCurPlmn.Mcc & 0x0f));

    if (0x0f00 == (pstRcvMsg->stCurPlmn.Mnc & 0x0f00))
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr +
                                           usLength,
                                           "%x%x",
                                           (pstRcvMsg->stCurPlmn.Mnc & 0xf0)>>4,
                                           (pstRcvMsg->stCurPlmn.Mnc & 0x0f));
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr +
                                           usLength,
                                           "%x%x%x",
                                           (pstRcvMsg->stCurPlmn.Mnc & 0x0f00)>>8,
                                           (pstRcvMsg->stCurPlmn.Mnc & 0xf0)>>4,
                                           (pstRcvMsg->stCurPlmn.Mnc & 0x0f));
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s",gaucAtCrLf);

    At_SendResultData((VOS_UINT8)ucIndex, pgucAtSndCodeAddr, usLength);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : AT_RcvTafMmaCrpnQryCnf
 功能描述  : AT 处理CRPN QRY返回结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月1日
    作    者   : y00322978
    修改内容   : 新生成函数
  2.日    期   : 2015年10月15日
    作    者   : zwx247453
    修改内容   : 网络安全代码修改

*****************************************************************************/
VOS_UINT32 AT_RcvTafMmaCrpnQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_CRPN_QRY_CNF_STRU          *pstCrpnQryCnf;
    TAF_MMA_CRPN_QRY_INFO_STRU         *pstMnMmaCrpnQryCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           aucPlmn[TAF_MAX_AUTHDATA_PLMN_LEN + 1];
    TAF_MMA_CRPN_QRY_PARA_STRU          stMnMmaCrpnQry;

    /* 初始化 */
    pstCrpnQryCnf           = (TAF_MMA_CRPN_QRY_CNF_STRU *)pMsg;
    pstMnMmaCrpnQryCnf      = &pstCrpnQryCnf->stCrpnQryInfo;
    ulResult                = AT_OK;
    usLength                = 0;
    ulLoop                  = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCrpnQryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaCrpnQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvTafMmaCrpnQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by 傅映君/f62575 for 自动应答开启情况下被叫死机问题, 2011/11/28, end */

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_CRPN_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }


    /* 格式化AT^CRPN查询命令返回 */
    gstAtSendData.usBufLen = 0;
    if (TAF_ERR_NO_ERROR != pstCrpnQryCnf->enErrorCause)
    {
        ulResult = At_ChgTafErrorCode(ucIndex, (VOS_UINT16)pstCrpnQryCnf->enErrorCause);;

        /* 使用AT_STOP_TIMER_CMD_READY恢复AT命令实体状态为READY状态 */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        /* 输出结果 */
        At_FormatResultData(ucIndex, ulResult);

        return VOS_OK;
    }

    ulResult = AT_OK;

    for (ulLoop = 0; ulLoop < pstMnMmaCrpnQryCnf->ucTotalNum; ulLoop++)
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s",
                                           gaucAtCrLf);

        /* ^CRPN:  */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: ",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        /* <PLMN> */
        /* 参照标杆，如果命令中输入的是PLMN ID，则输出时直接采用输入的PLMN ID */
        if (2 == pstMnMmaCrpnQryCnf->stMnMmaCrpnQry.ucPlmnType)
        {
            PS_MEM_SET(aucPlmn, 0, sizeof(aucPlmn));
            if (pstMnMmaCrpnQryCnf->stMnMmaCrpnQry.usPlmnNameLen > TAF_MAX_AUTHDATA_PLMN_LEN)
            {
                PS_MEM_CPY(aucPlmn,
                       pstMnMmaCrpnQryCnf->stMnMmaCrpnQry.aucPlmnName,
                       TAF_MAX_AUTHDATA_PLMN_LEN);
            }
            else
            {
                PS_MEM_CPY(aucPlmn,
                       pstMnMmaCrpnQryCnf->stMnMmaCrpnQry.aucPlmnName,
                       pstMnMmaCrpnQryCnf->stMnMmaCrpnQry.usPlmnNameLen);
            }
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "\"%s\"",
                                               aucPlmn);
        }
        else
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "\"%X%X%X",
                                               (0x0f00 & pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].PlmnId.Mcc) >> 8,
                                               (0x00f0 & pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].PlmnId.Mcc) >> 4,
                                               (0x000f & pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].PlmnId.Mcc));


            if (6 == pstMnMmaCrpnQryCnf->ucMaxMncLen)
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%X",
                                                   (0x0f00 & pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].PlmnId.Mnc) >> 8);

            }
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%X%X\"",
                                               (0x00f0 & pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].PlmnId.Mnc) >> 4,
                                               (0x000f & pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].PlmnId.Mnc));
        }

        /* <short name> */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",\"%s\"",
                                           pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].aucOperatorNameShort);

        /* <long name> */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",\"%s\"",
                                           pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].aucOperatorNameLong);
    }

    gstAtSendData.usBufLen = usLength;

    At_BufferorSendResultData(ucIndex, pgucAtSndCodeAddr, usLength);
    usLength = 0;

    /* 如果本次上报的CRPN数目与要求的相同，则认为C核仍有Plmn list没有上报，要继续发送请求进行查询 */
    if (TAF_PH_CRPN_PLMN_MAX_NUM == pstMnMmaCrpnQryCnf->ucTotalNum)
    {
        PS_MEM_CPY(&stMnMmaCrpnQry, &pstMnMmaCrpnQryCnf->stMnMmaCrpnQry, sizeof(TAF_MMA_CRPN_QRY_PARA_STRU));
        stMnMmaCrpnQry.ucCurrIndex = pstMnMmaCrpnQryCnf->ucCurrIndex + pstMnMmaCrpnQryCnf->ucTotalNum;
        stMnMmaCrpnQry.ucQryNum    = TAF_PH_CRPN_PLMN_MAX_NUM;

        /* 发送ID_TAF_MMA_CRPN_QRY_REQ消息给MMA处理 */
        if (VOS_TRUE == TAF_MMA_QryCrpnReq( WUEPS_PID_AT,
                                            gastAtClientTab[ucIndex].usClientId,
                                            0,
                                            &stMnMmaCrpnQry))
        {
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CRPN_QUERY;
        }
        else
        {
            /* 使用AT_STOP_TIMER_CMD_READY恢复AT命令实体状态为READY状态 */
            AT_STOP_TIMER_CMD_READY(ucIndex);
            gstAtSendData.usBufLen = 0;
            At_FormatResultData(ucIndex, AT_ERROR);
        }
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s",
                                               gaucAtCrLf);
        At_BufferorSendResultData(ucIndex, pgucAtSndCodeAddr, usLength);
        usLength = 0;

        /* 使用AT_STOP_TIMER_CMD_READY恢复AT命令实体状态为READY状态 */
        AT_STOP_TIMER_CMD_READY(ucIndex);
        gstAtSendData.usBufLen = usLength;
        At_FormatResultData(ucIndex, ulResult);
    }

    return VOS_OK;

}


VOS_UINT32 AT_RcvMmaCbcQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_BATTERY_CAPACITY_QRY_CNF_STRU                  *pstCbcCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_UINT16                          usLength = 0;

    /* 初始化 */
    pstCbcCnf           = (TAF_MMA_BATTERY_CAPACITY_QRY_CNF_STRU *)pMsg;
    ulResult            = AT_OK;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCbcCnf->stCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCbcQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCbcQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_CBC_SET */
    if (AT_CMD_CBC_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                      "%s: %d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      pstCbcCnf->stBatteryStatus.BatteryPowerStatus);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                      ",%d",
                                      pstCbcCnf->stBatteryStatus.BatteryRemains);


    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex,ulResult);
    return VOS_OK;

}


VOS_UINT32 AT_RcvMmaHsQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_HAND_SHAKE_QRY_CNF_STRU    *pstHsCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    TAF_UINT16                          usLength = 0;

    /* 初始化 */
    pstHsCnf            = (TAF_MMA_HAND_SHAKE_QRY_CNF_STRU *)pMsg;
    ulResult            = AT_OK;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstHsCnf->stCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaHsQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaHsQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_HS_READ */
    if (AT_CMD_HS_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }


    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s: %d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      *(TAF_UINT32*)pstHsCnf->aucBuf);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                      ",%d",pstHsCnf->aucBuf[4]);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                      ",%d",pstHsCnf->aucBuf[5]);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                      ",%d",pstHsCnf->aucBuf[6]);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                      ",%d",pstHsCnf->aucBuf[7]);

    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex,ulResult);
    return VOS_OK;

}


/*****************************************************************************
 函 数 名  : AT_RcvMmaHdrCsqInd
 功能描述  : 处理来自MMA模块ID_TAF_MMA_HDR_CSQ_IND消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : C00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaHdrCsqInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    MMA_TAF_HDR_CSQ_VALUE_IND_STRU     *pstHdrcsqInd;

    /* 初始化消息变量 */
    ucIndex             = 0;
    pstHdrcsqInd        = (MMA_TAF_HDR_CSQ_VALUE_IND_STRU*)pMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstHdrcsqInd->stCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaCdmaCsqInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^HDRCSQ: %d,%d,%d%s",
                                                    gaucAtCrLf,
                                                    pstHdrcsqInd->sHdrRssi,
                                                    pstHdrcsqInd->sHdrSnr,
                                                    pstHdrcsqInd->sHdrEcio,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : AT_RcvMmaHdrCsqSetCnf
 功能描述  : 处理来自MMA模块ID_TAF_MMA_HDR_CSQ_SET_CNF消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : C00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaHdrCsqSetCnf(
    VOS_VOID                           *pMsg
)
{
    MMA_TAF_HDR_CSQ_SET_CNF_STRU            *pstHdrCsqCnf;
    VOS_UINT8                                ucIndex;
    VOS_UINT32                               ulResult;

    pstHdrCsqCnf = (MMA_TAF_HDR_CSQ_SET_CNF_STRU *)pMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstHdrCsqCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaHdrCsqSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaHdrCsqSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstHdrCsqCnf->enRslt)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaHdrCsqQryCnf
 功能描述  : 处理来自MMA模块ID_TAF_MMA_CDMACSQ_QRY_CNF消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : C00299064
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaHdrCsqQryCnf(
    VOS_VOID                           *pMsg
)
{
    MMA_TAF_HDR_CSQ_QRY_SETTING_CNF_STRU *pstHdrCsqQueryCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    pstHdrCsqQueryCnf  = (MMA_TAF_HDR_CSQ_QRY_SETTING_CNF_STRU*)pMsg;
    usLength            = 0;
    ulResult            = AT_OK;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstHdrCsqQueryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaHdrCsqQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaHdrCsqQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_HDR_CSQ_QRY */
    if (AT_CMD_HDR_CSQ_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s: %d,%d,%d,%d,%d,%d,%d,%d",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                     pstHdrCsqQueryCnf->stHdrCsq.enMode,
                                     pstHdrCsqQueryCnf->stHdrCsq.ucTimeInterval,
                                     pstHdrCsqQueryCnf->stHdrCsq.ucRssiThreshold,
                                     pstHdrCsqQueryCnf->stHdrCsq.ucSnrThreshold,
                                     pstHdrCsqQueryCnf->stHdrCsq.ucEcioThreshold,
                                     pstHdrCsqQueryCnf->sHdrRssi,
                                     pstHdrCsqQueryCnf->sHdrSnr,
                                     pstHdrCsqQueryCnf->sHdrEcio);

    gstAtSendData.usBufLen = usLength;

    At_FormatResultData(ucIndex, ulResult);

    /* 输出结果 */
    return VOS_OK;
}



#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 函 数 名  : AT_RcvMmaImsSwitchSetCnf
 功能描述  : 处理ID_TAF_MMA_IMS_SWITCH_SET_CNF
 输入参数  :  VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月02日
    作    者   : zwx247453
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvMmaImsSwitchSetCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_IMS_SWITCH_SET_CNF_STRU   *pstCnfMsg = VOS_NULL_PTR;
    VOS_UINT8                          ucIndex;
    VOS_UINT32                         ulResult;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    pstCnfMsg = (TAF_MMA_IMS_SWITCH_SET_CNF_STRU*)pMsg;

    /* 通过ClientId获取ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstCnfMsg->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaImsSwitchSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* 广播消息不处理 */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaImsSwitchSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* 判断当前操作类型 */
    if (AT_CMD_IMS_SWITCH_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaImsSwitchSetCnf: WARNING:Not AT_CMD_IMS_SWITCH_SET!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstCnfMsg->enResult)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstCnfMsg->enErrorCause);
    }

    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaImsSwitchQryCnf
 功能描述  : 处理ID_TAF_MMA_IMS_SWITCH_QRY_CNF
 输入参数  :  VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月02日
    作    者   : zwx247453
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvMmaImsSwitchQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_IMS_SWITCH_QRY_CNF_STRU    *pstSwitchQryCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    /* 初始化 */
    pstSwitchQryCnf     = (TAF_MMA_IMS_SWITCH_QRY_CNF_STRU *)pMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstSwitchQryCnf->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaImsSwitchQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaImsSwitchQryCnf : AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_IMS_SWITCH_QRY */
    if (AT_CMD_IMS_SWITCH_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaImsSwitchQryCnf: WARNING:Not AT_CMD_IMS_SWITCH_QRY!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSwitchQryCnf->enImsSwitch);

    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : AT_RcvMmaVoiceDomainSetCnf
 功能描述  : 处理ID_TAF_MMA_VOICE_DOMAIN_SET_CNF
 输入参数  :  VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月02日
    作    者   : zwx247453
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvMmaVoiceDomainSetCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_VOICE_DOMAIN_SET_CNF_STRU  *pstCnfMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    ucIndex   = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    pstCnfMsg = (TAF_MMA_VOICE_DOMAIN_SET_CNF_STRU *)pMsg;

    /* 通过ClientId获取ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstCnfMsg->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaVoiceDomainSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* 广播消息不处理 */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaVoiceDomainSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* 判断当前操作类型 */
    if (AT_CMD_VOICE_DOMAIN_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaVoiceDomainSetCnf: WARNING:Not AT_CMD_VOICE_DOMAIN_SET!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstCnfMsg->enResult)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstCnfMsg->enErrorCause);
    }

    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_VoiceDomainTransToOutputValue
 功能描述  : modem侧对应的voice domain值转换为AT的输出值
 输入参数  : enVoiceDomain
 输出参数  : 无
 返 回 值  : ulValue
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月04日
    作    者   : zwx247453
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_VoiceDomainTransToOutputValue(
    TAF_MMA_VOICE_DOMAIN_ENUM_UINT32    enVoiceDoman,
    VOS_UINT32                         *pulValue
)
{
    VOS_UINT32                          ulRst;

    ulRst = VOS_TRUE;

    switch (enVoiceDoman)
    {
        case TAF_MMA_VOICE_DOMAIN_CS_ONLY:
            *pulValue = AT_VOICE_DOMAIN_TYPE_CS_ONLY;
            break;

        case TAF_MMA_VOICE_DOMAIN_IMS_PS_ONLY:
            *pulValue = AT_VOICE_DOMAIN_TYPE_IMS_PS_ONLY;
            break;

        case TAF_MMA_VOICE_DOMAIN_CS_PREFERRED:
            *pulValue = AT_VOICE_DOMAIN_TYPE_CS_PREFERRED;
            break;

        case TAF_MMA_VOICE_DOMAIN_IMS_PS_PREFERRED:
            *pulValue = AT_VOICE_DOMAIN_TYPE_IMS_PS_PREFERRED;
            break;

        default:
            *pulValue = AT_VOICE_DOMAIN_TYPE_BUTT;
            ulRst = VOS_FALSE;
            break;
    }

    return ulRst;

}

/*****************************************************************************
 函 数 名  : AT_RcvMmaVoiceDomainQryCnf
 功能描述  : 处理ID_TAF_MMA_VOICE_DOMAIN_QRY_CNF
 输入参数  :  VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月02日
    作    者   : zwx247453
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvMmaVoiceDomainQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_VOICE_DOMAIN_QRY_CNF_STRU  *pstDomainQryCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulValue;
    VOS_UINT32                          ulResult;

    /* 初始化 */
    ulValue             = 0;
    pstDomainQryCnf     = (TAF_MMA_VOICE_DOMAIN_QRY_CNF_STRU *)pMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstDomainQryCnf->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaVoiceDomainQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaVoiceDomainQryCnf : AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_VOICE_DOMAIN_QRY */
    if (AT_CMD_VOICE_DOMAIN_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaVoiceDomainQryCnf: WARNING:Not AT_CMD_VOICE_DOMAIN_QRY!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_TRUE != AT_VoiceDomainTransToOutputValue(pstDomainQryCnf->enVoiceDomain, &ulValue))
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
        gstAtSendData.usBufLen = 0;
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       "%s: %d",
                                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                       ulValue);
    }

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

#endif
/*****************************************************************************
 函 数 名  : AT_RcvMtaSetFemctrlCnf
 功能描述  : AT模块收到MTA回复的FEMCTRL消息的处理函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月15日
    作    者   : m00217266
    修改内容   : 新增
*****************************************************************************/
VOS_UINT32 AT_RcvMtaSetFemctrlCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_SET_FEMCTRL_CNF_STRU        *pstSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* 初始化 */
    pstRcvMsg    = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf    = (MTA_AT_SET_FEMCTRL_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex      = 0;
    ulResult     = AT_ERROR;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetFemctrlCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetFemctrlCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_FEMCTRL_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetFemctrlCnf : Current Option is not AT_CMD_FEMCTRL_SET.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化命令返回 */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR == pstSetCnf->enResult)
    {
        ulResult = AT_OK;
    }

    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMma1xChanSetCnf
 功能描述  : AT_MMA_1XCHAN_CNF消息处理函数,^CVER查询结果
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月16日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMma1xChanSetCnf(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_CFREQ_LOCK_SET_CNF_STRU    *pstCFreqLockSetCnf;
    VOS_UINT32                          ulResult;

    /* 初始化消息变量 */
    ucIndex             = 0;
    pstCFreqLockSetCnf  = (TAF_MMA_CFREQ_LOCK_SET_CNF_STRU*)pstMsg;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCFreqLockSetCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMma1xChanSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMma1xChanSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_1XCHAN_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMma1xChanSetCnf : Current Option is not AT_CMD_CFREQLOCK_SET.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化AT^1XCHAN命令返回 */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstCFreqLockSetCnf->ulRslt)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMma1xChanQueryCnf
 功能描述  : AT_MMA_1XCHAN_QUERY_CNF消息处理函数,^1XCHAN查询结果
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月16日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMma1xChanQueryCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_1XCHAN_QUERY_CNF_STRU      *pst1xChanQueryCnf;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    VOS_INT16                           sInvalidChan;

    /* 初始化 */
    pst1xChanQueryCnf   = (TAF_MMA_1XCHAN_QUERY_CNF_STRU*)pstMsg;
    usLength            = 0;
    sInvalidChan        = -1;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pst1xChanQueryCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMma1xChanQueryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMma1xChanQueryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_CVER_QRY */
    if (AT_CMD_1XCHAN_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMma1xChanQueryCnf : Current Option is not AT_CMD_1XCHAN_QRY.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_OK == pst1xChanQueryCnf->ulRslt)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s: %d",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                     pst1xChanQueryCnf->usChannel);

        gstAtSendData.usBufLen = usLength;
    }
    else
    {
        /* 查询失败，上报^1XCHAN: BUTT */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s: %d",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                     sInvalidChan);

        gstAtSendData.usBufLen = usLength;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaCVerQueryCnf
 功能描述  : AT_MMA_CVER_QUERY_CNF消息处理函数,^CVER查询结果
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月16日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaCVerQueryCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_CVER_QUERY_CNF_STRU        *pstCVerQueryCnf;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    TAF_MMA_1X_CAS_P_REV_ENUM_UINT8     enInvalidVersion;

    /* 初始化 */
    pstCVerQueryCnf     = (TAF_MMA_CVER_QUERY_CNF_STRU*)pstMsg;
    usLength            = 0;
    enInvalidVersion    = TAF_MMA_1X_CAS_P_REV_ENUM_BUTT;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstCVerQueryCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCVerQueryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCVerQueryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_CVER_QRY */
    if (AT_CMD_CVER_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaCVerQueryCnf : Current Option is not AT_CMD_CVER_QRY.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_OK == pstCVerQueryCnf->ulRslt)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s: %d",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                     pstCVerQueryCnf->enPrevInUse);

        gstAtSendData.usBufLen = usLength;
    }
    else
    {
        /* 查询失败，上报^CVER: BUTT */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s: %d",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                     enInvalidVersion);

        gstAtSendData.usBufLen = usLength;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaStateQueryCnf
 功能描述  : ID_TAF_MMA_GETST_QUERY_CNF消息处理函数,^CVER查询结果
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月16日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaStateQueryCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_STATE_QUERY_CNF_STRU       *pstStQryCnf;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    VOS_INT8                            cInvalidSta;

    /* 初始化 */
    pstStQryCnf     = (TAF_MMA_STATE_QUERY_CNF_STRU*)pstMsg;
    usLength        = 0;
    cInvalidSta     = -1;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstStQryCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaStateQueryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaStateQueryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_CVER_QRY */
    if (AT_CMD_GETSTA_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaStateQueryCnf : Current Option is not AT_CMD_GETST_QRY.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_OK == pstStQryCnf->ulRslt)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s: %d,%d",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                     pstStQryCnf->stHandsetSta.ucCasState,
                                     pstStQryCnf->stHandsetSta.ucCasSubSta);

        gstAtSendData.usBufLen = usLength;
    }
    else
    {
        /* 查询失败，上报^GETSTA: BUTT */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s: %d,%d",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                     cInvalidSta,
                                     cInvalidSta);

        gstAtSendData.usBufLen = usLength;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaCHverQueryCnf
 功能描述  : ID_TAF_MMA_CHVER_QUERY_CNF消息处理函数,^CVER查询结果
 输入参数  : VOS_VOID *pstMsg - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月16日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaCHverQueryCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_CHIGHVER_QUERY_CNF_STRU    *pstStaQryCnf;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    TAF_MMA_1X_CAS_P_REV_ENUM_UINT8     enInvalidVer;

    /* 初始化 */
    pstStaQryCnf     = (TAF_MMA_CHIGHVER_QUERY_CNF_STRU*)pstMsg;
    usLength         = 0;
    enInvalidVer     = TAF_MMA_1X_CAS_P_REV_ENUM_BUTT;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstStaQryCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCHverQueryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCHverQueryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*判断当前操作类型是否为AT_CMD_CHIGHVER_QRY */
    if (AT_CMD_CHIGHVER_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaCHverQueryCnf : Current Option is not AT_CMD_CHIGHVER_QRY.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_OK == pstStaQryCnf->ulRslt)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s: %d",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                     pstStaQryCnf->enHighRev);

        gstAtSendData.usBufLen = usLength;
    }
    else
    {
        /* 查询失败，上报^CHIGHVER: BUTT */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s: %d",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                     enInvalidVer);

        gstAtSendData.usBufLen = usLength;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_RcvMmaHplmnQryCnf
 功能描述  : AT收到ID_TAF_MMA_HPLMN_QRY_CNF消息处理函数,AT上报^HPLMN查询结果
 输入参数  : VOS_VOID                           *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月9日
    作    者   : n00355355
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaHplmnQryCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_HOME_PLMN_QRY_CNF_STRU     *pstHplmnQryCnf = VOS_NULL_PTR;
    VOS_UINT16                          usLength;
    VOS_UINT32                          i;
    VOS_UINT8                           aucImsiString[NAS_IMSI_STR_LEN + 1];

    /* 局部变量初始化 */
    pstHplmnQryCnf = (TAF_MMA_HOME_PLMN_QRY_CNF_STRU *)pstMsg;
    usLength       = 0;

    /* index的异常判断移到AT_RcvMmaEHplmnInfoQryCnf中 */

    /* 复位AT状态为READY状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ((0 == pstHplmnQryCnf->stEHplmnInfo.ulEHplmnNum)
     || (TAF_ERR_NO_ERROR != pstHplmnQryCnf->enErrorCause))
    {
        AT_WARN_LOG("AT_RcvMmaHplmnQryCnf : EHPLMN num error.");

        /* 查询命令失败，上报错误情况 */
        gstAtSendData.usBufLen = 0;

        At_FormatResultData(ucIndex, At_ChgTafErrorCode(ucIndex, pstHplmnQryCnf->enErrorCause));

        return VOS_ERR;
    }

    /* 将IMSI数字转换为字符串 */
    AT_ConvertImsiDigit2String(pstHplmnQryCnf->stEHplmnInfo.aucImsi, aucImsiString);

    /* 查询命令成功，上报AT^HPLMN */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                 (VOS_CHAR *)pgucAtSndCodeAddr,
                                 (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                 "%s: %s,%d,%d,",
                                 g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                 aucImsiString,
                                 pstHplmnQryCnf->stEHplmnInfo.ucHplmnMncLen,
                                 pstHplmnQryCnf->stEHplmnInfo.ulEHplmnNum);

    for ( i = 0; i < (VOS_UINT8)(pstHplmnQryCnf->stEHplmnInfo.ulEHplmnNum - 1); i++ )
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                   "%x%x%x",
                                   (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mcc & 0x0f00)>>8,
                                   (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mcc & 0xf0)>>4,
                                   (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mcc & 0x0f));

        if (0x0f00 == (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mnc & 0x0f00))
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%x%x,",
                                               (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mnc & 0xf0)>>4,
                                               (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mnc & 0x0f));
        }
        else
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%x%x%x,",
                                               (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mnc & 0x0f00)>>8,
                                               (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mnc & 0xf0)>>4,
                                               (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mnc & 0x0f));
        }
     }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                   "%x%x%x",
                                   (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mcc & 0x0f00)>>8,
                                   (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mcc & 0xf0)>>4,
                                   (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mcc & 0x0f));

    if (0x0f00 == (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mnc & 0x0f00))
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%x%x",
                                           (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mnc & 0xf0)>>4,
                                           (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mnc & 0x0f));
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%x%x%x",
                                           (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mnc & 0x0f00)>>8,
                                           (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mnc & 0xf0)>>4,
                                           (pstHplmnQryCnf->stEHplmnInfo.astEHplmnList[i].Mnc & 0x0f));
    }

    gstAtSendData.usBufLen = usLength;

    /* 输出结果 */
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaDplmnQryCnf
 功能描述  : AT收到MMA发送的DPLMN QRY CNF消息，上报^DPLMNLIST:<VER>命令
 输入参数  : VOS_VOID                           *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月16日
    作    者   : n00355355
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaDplmnQryCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_DPLMN_QRY_CNF_STRU         *pstDplmnQryCnf = VOS_NULL_PTR;
    VOS_UINT16                          usLength;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucTempVersion[NAS_VERSION_LEN + 1];

    /* 局部变量初始化*/
    pstDplmnQryCnf  = (TAF_MMA_DPLMN_QRY_CNF_STRU *)pstMsg;
    usLength        = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstDplmnQryCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaDplmnQryCnf At_ClientIdToUserId FAILURE");
        return VOS_ERR;
    }

    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &enModemId))
    {
        AT_ERR_LOG("AT_RcvMmaDplmnQryCnf: Get modem id fail.");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaDplmnQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_DPLMNLIST_QRY */
    if (AT_CMD_DPLMNLIST_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaDplmnQryCnf : Current Option is not AT_CMD_DPLMNLIST_READ.");
        return VOS_ERR;
    }

    /* 复位AT状态为READY状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 将version数字转换为字符串 */
    PS_MEM_CPY(aucTempVersion, pstDplmnQryCnf->aucVersionId, NAS_VERSION_LEN);

    /* 加字符串结束符 */
    aucTempVersion[NAS_VERSION_LEN]    = '\0';

    /* 查询命令成功，上报^DPLMN版本号 */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                 (VOS_CHAR *)pgucAtSndCodeAddr,
                                 (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                 "%s: %s",
                                 g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                 aucTempVersion);

    gstAtSendData.usBufLen = usLength;

    /* 输出结果 */
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_RcvMmaDplmnSetCnf
 功能描述  : AT收到ID_TAF_DPLMN_SET_CNF消息的处理，AT上报设置结果
 输入参数  : VOS_VOID                           *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : n00355355
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_RcvMmaDplmnSetCnf(
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_DPLMN_SET_CNF_STRU         *pstDplmnSetCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulRetVal;

    /* 局部变量初始化 */
    pstDplmnSetCnf = (TAF_MMA_DPLMN_SET_CNF_STRU *)pstMsg;
    ulRetVal       = VOS_ERR;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstDplmnSetCnf->stCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaDplmnSetCnf At_ClientIdToUserId FAILURE");
        return ulRetVal;
    }

    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &enModemId))
    {
        AT_ERR_LOG("AT_RcvMmaDplmnSetCnf: Get modem id fail.");
        return ulRetVal;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaDplmnSetCnf: AT_BROADCAST_INDEX.");
        return ulRetVal;
    }

    /* 判断当前操作类型是否为AT_CMD_DPLMNLIST_SET */
    if (AT_CMD_DPLMNLIST_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaDplmnSetCnf : Current Option is not AT_CMD_DPLMNLIST_SET.");
        return ulRetVal;
    }

    /* 复位AT状态为READY状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_OK == pstDplmnSetCnf->ulRslt)
    {
        ulResult = AT_OK;
        ulRetVal = VOS_OK;
    }
    else
    {
        ulResult = AT_CME_UNKNOWN;
    }

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return ulRetVal;
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : AT_RcvMtaSetFrCnf
 功能描述  : AT模块收到MTA回复的FRSTATUS消息的处理函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月03日
    作    者   : wx270776
    修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32 AT_RcvMtaSetFrCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg   = VOS_NULL_PTR;
    MTA_AT_SET_FR_CNF_STRU             *pstSetFrCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* 初始化 */
    pstRcvMsg    = (AT_MTA_MSG_STRU *)pMsg;
    pstSetFrCnf  = (MTA_AT_SET_FR_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex      = 0;
    ulResult     = AT_ERROR;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetFrCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetFrCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_FRSTATUS_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetFrCnf : Current Option is not AT_CMD_FRSTATUS_SET.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化命令返回 */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR == pstSetFrCnf->enRslt)
    {
        ulResult = AT_OK;
    }

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
#endif
/*****************************************************************************
 函 数 名  : AT_RcvMmaSrchedPlmnInfoInd
 功能描述  : 处理ID_TAF_MMA_SRCHED_PLMN_INFO_IND
 输入参数  :  VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月15日
    作    者   : h00285180
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvMmaSrchedPlmnInfoInd(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_SRCHED_PLMN_INFO_IND_STRU  *pstSrchedPlmnInfo = VOS_NULL_PTR;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          i;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    usLength    = 0;
    enModemId   = MODEM_ID_0;
    pstSrchedPlmnInfo  = (TAF_MMA_SRCHED_PLMN_INFO_IND_STRU*)pMsg;

    if (AT_FAILURE == At_ClientIdToUserId(pstSrchedPlmnInfo->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSrchedPlmnInfoInd At_ClientIdToUserId FAILURE");
        return VOS_ERR;
    }

    ulRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_RcvMmaSrchedPlmnInfoInd: Get modem id fail.");
        return VOS_ERR;
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s%s",
                                       gaucAtCrLf,
                                       gastAtStringTab[AT_STRING_SRCHEDPLMNINFO].pucText);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d,%d",
                                       pstSrchedPlmnInfo->enRat,
                                       pstSrchedPlmnInfo->ulLaiNum);

    for (i = 0; i < pstSrchedPlmnInfo->ulLaiNum; i++)
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",%x%x%x",
                                           (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mcc & 0x0f00) >> 8,
                                           (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mcc & 0xf0) >> 4,
                                           (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mcc & 0x0f));

        if (0x0f00 == (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mnc & 0x0f00))
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%x%x,",
                                               (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mnc & 0xf0) >> 4,
                                               (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mnc & 0x0f));
        }
        else
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%x%x%x,",
                                               (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mnc & 0x0f00) >> 8,
                                               (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mnc & 0xf0) >> 4,
                                               (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mnc & 0x0f));
        }

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%d",
                                           pstSrchedPlmnInfo->astLai[i].usLac);
    }


    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s",
                                       gaucAtCrLf);

    gstAtSendData.usBufLen = usLength;

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaTransModeQryCnf
 功能描述  : AT模块收到MTA回复的TransMode消息的处理函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月30日
    作    者   : lwx277467
    修改内容   : 新增
  2.日    期   : 2015年10月15日
    作    者   : zwx247453
    修改内容   : 网络安全代码修改
*****************************************************************************/
VOS_UINT32 AT_RcvMtaTransModeQryCnf(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg               = VOS_NULL_PTR;
    MTA_AT_TRANSMODE_QRY_CNF_STRU          *pstMtaAtQryTransModeCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* 初始化 */
    pstRcvMsg                = (AT_MTA_MSG_STRU *)pMsg;
    pstMtaAtQryTransModeCnf  = (MTA_AT_TRANSMODE_QRY_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult                 = AT_OK;
    ucIndex                  = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaTransModeQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaTransModeQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_TRANSMODE_READ!= gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaTransModeQryCnf : Current Option is not AT_CMD_RRC_VERSION_QUERY.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = 0;
    if (MTA_AT_RESULT_NO_ERROR != pstMtaAtQryTransModeCnf->enResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       "%s: %d",
                                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                       pstMtaAtQryTransModeCnf->ucTransMode);
    }
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaUECenterQryCnf
 功能描述  : AT模块收到MTA回复的查询UE模式消息的处理函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : lwx277467
    修改内容   : 新增
  2.日    期   : 2015年10月15日
    作    者   : zwx247453
    修改内容   : 网络安全代码修改
*****************************************************************************/
VOS_UINT32 AT_RcvMtaUECenterQryCnf(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg               = VOS_NULL_PTR;
    MTA_AT_QRY_UE_CENTER_CNF_STRU          *pstMtaAtQryUECenterCnf  = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* 初始化 */
    pstRcvMsg                = (AT_MTA_MSG_STRU *)pMsg;
    pstMtaAtQryUECenterCnf   = (MTA_AT_QRY_UE_CENTER_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult                 = AT_OK;
    ucIndex                  = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaUECenterQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaUECenterQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_UE_CENTER_QRY!= gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaUECenterQryCnf : Current Option is not AT_CMD_RRC_VERSION_QUERY.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = 0;
    if (MTA_AT_RESULT_NO_ERROR != pstMtaAtQryUECenterCnf->enResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       "%s: %d",
                                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                       pstMtaAtQryUECenterCnf->enUeCenter);
    }
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaUECenterSetCnf
 功能描述  : AT模块收到MTA回复的设置UE模式消息的处理函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月7日
    作    者   : lwx277467
    修改内容   : 新增
*****************************************************************************/
VOS_UINT32 AT_RcvMtaUECenterSetCnf(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg               = VOS_NULL_PTR;
    MTA_AT_SET_UE_CENTER_CNF_STRU          *pstMtaAtSetUECenterCnf  = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* 初始化 */
    pstRcvMsg                = (AT_MTA_MSG_STRU *)pMsg;
    pstMtaAtSetUECenterCnf   = (MTA_AT_SET_UE_CENTER_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult                 = AT_OK;
    ucIndex                  = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaUECenterQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaUECenterQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_UE_CENTER_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaUECenterQryCnf : Current Option is not AT_CMD_RRC_VERSION_QUERY.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = 0;
    if (MTA_AT_RESULT_NO_ERROR != pstMtaAtSetUECenterCnf->enResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
    }
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : At_MipiRdCnfProc
 功能描述  : AT模块收到HPA 回复的MipiRead 消息的处理函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月19日
    作    者   : l00227485
    修改内容   : 新增
*****************************************************************************/
VOS_UINT32  At_MipiRdCnfProc( HPA_AT_MIPI_RD_CNF_STRU *pstMsg )
{
    VOS_UINT32                          usRslt;
    VOS_UINT32                          usData;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;

    /* 初始化本地变量 */
    usLength        = 0;

    /*获取本地保存的用户索引*/
    ucIndex         = g_stAtDevCmdCtrl.ucIndex;

    if (AT_CMD_MIPI_RD != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
          return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (AT_HPA_RSLT_FAIL == pstMsg->ulResult)
    {
        AT_INFO_LOG("At_MipiRdCnfProc: read mipi err");
        usRslt = AT_ERROR;
    }
    else
    {
        usRslt      = AT_OK;
        usData      = pstMsg->ulValue;

        usLength    = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              "%s:%d",
                                              g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                              usData);
    }
    gstAtSendData.usBufLen  = usLength;
    At_FormatResultData(ucIndex, usRslt);
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : At_MipiWrCnfProc
 功能描述  : AT模块收到HPA 回复的MipiRead 消息的处理函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月19日
    作    者   : l00227485
    修改内容   : 新增
*****************************************************************************/
VOS_UINT32  At_MipiWrCnfProc( HPA_AT_MIPI_WR_CNF_STRU       *pstMsg )
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;

    /*获取本地保存的用户索引*/
    ucIndex = g_stAtDevCmdCtrl.ucIndex;

     if ( AT_CMD_MIPI_WR != gastAtClientTab[ucIndex].CmdCurrentOpt )
     {
          return VOS_ERR;
     }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (AT_HPA_RSLT_FAIL == pstMsg->usErrFlg)
    {
        AT_INFO_LOG("At_MipiWrCnfProc: set MipiCfg err");
        ulRslt  = AT_ERROR;
    }
    else
    {
        ulRslt  = AT_OK;
    }

    At_FormatResultData(ucIndex, ulRslt);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : At_SsiWrCnfProc
 功能描述  : AT模块收到HPA 回复的SsiRead 消息的处理函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月19日
    作    者   : l00227485
    修改内容   : 新增
*****************************************************************************/
VOS_UINT32  At_SsiWrCnfProc( HPA_AT_SSI_WR_CNF_STRU         *pstMsg )
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;

    /*获取本地保存的用户索引*/
    ucIndex     = g_stAtDevCmdCtrl.ucIndex;

    if (AT_CMD_SSI_WR != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
          return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);


    if (AT_HPA_RSLT_FAIL == pstMsg->usErrFlg)
    {
        AT_INFO_LOG("At_SsiWrCnfProc: set rfcfg err");
        ulRslt = AT_ERROR;
    }
    else
    {
        ulRslt  = AT_OK;
    }

    At_FormatResultData(ucIndex, ulRslt);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : At_SsiRdCnfProc
 功能描述  : AT模块收到HPA 回复的MipiRead 消息的处理函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月19日
    作    者   : l00227485
    修改内容   : 新增
*****************************************************************************/
VOS_UINT32  At_SsiRdCnfProc( HPA_AT_SSI_RD_CNF_STRU          *pstMsg )
{
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulData;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;

    /* 初始化本地变量 */
    usLength        = 0;

    /*获取本地保存的用户索引*/
    ucIndex         = g_stAtDevCmdCtrl.ucIndex;

    if ( AT_CMD_SSI_RD != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
          return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (AT_HPA_RSLT_FAIL == pstMsg->ulResult)
    {
        AT_INFO_LOG("At_MipiRdCnfProc: read SSI err");
        ulRslt = AT_ERROR;
    }
    else
    {
        ulRslt      = AT_OK;
        ulData      = pstMsg->ulValue;

        usLength    = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            "%s:%d",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            ulData );
    }

    gstAtSendData.usBufLen  = usLength;
    At_FormatResultData(ucIndex, ulRslt);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : At_PdmCtrlCnfProc
 功能描述  : AT模块收到HPA 回复的MipiRead 消息的处理函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月20日
    作    者   : x00316382
    修改内容   : 新增
*****************************************************************************/
VOS_UINT32  At_PdmCtrlCnfProc( HPA_AT_PDM_CTRL_CNF_STRU *pstMsg )
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;

    /*获取本地保存的用户索引*/
    ucIndex         = g_stAtDevCmdCtrl.ucIndex;

    if ( AT_CMD_PDM_CTRL != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
          return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (AT_HPA_RSLT_FAIL == pstMsg->ulResult)
    {
        AT_INFO_LOG("At_PdmCtrlCnfProc: read PdmCtrl err");
        ulRslt      = AT_ERROR;
    }
    else
    {
        ulRslt      = AT_OK;
    }

    At_FormatResultData(ucIndex, ulRslt);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMmaInitLocInfoInd
 功能描述  : AT模块收到TAF_MMA_INIT_LOC_INFO_IND_STRU消息,上报INITLOCINFO命令
 输入参数  : pstMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月10日
    作    者   : l00324781
    修改内容   : 新增
*****************************************************************************/

VOS_UINT32 AT_RcvMmaInitLocInfoInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    TAF_MMA_INIT_LOC_INFO_IND_STRU     *pstInitLocInfoInd;

    /* 初始化消息变量 */
    ucIndex             = 0;
    pstInitLocInfoInd   = (TAF_MMA_INIT_LOC_INFO_IND_STRU *)pMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstInitLocInfoInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMmaInitLocInfoInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^INITLOCINFO: %x%x%x,%d%s",
                                                    gaucAtCrLf,
                                                    (pstInitLocInfoInd->ulMcc & 0x0f00)>>8,
                                                    (pstInitLocInfoInd->ulMcc & 0x00f0)>>4,
                                                    (pstInitLocInfoInd->ulMcc & 0x000f),
                                                    pstInitLocInfoInd->lSid,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

