/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : uttest_AtQueryParaCmd.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2012年5月17日
  最近修改   :
  功能描述   : uttest_AtQueryParaCmd.cpp 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年5月17日
    作    者   : l60609
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TEST_ATQUERYPARACMD_H__
#define __TEST_ATQUERYPARACMD_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "mdrv.h"
#include "ATCmdProc.h"
#include "AtCheckFunc.h"
#include "AtParseCmd.h"
#include "UsimPsInterface.h"
#include "AtPhyInterface.h"
#include "TafDrvAgent.h"
#include "MnCommApi.h"
#include "PppInterface.h"
#include "AtDataProc.h"
#include "MnMsgApi.h"
#include "mdrv.h"
#include "AtCmdMsgProc.h"
#include "Taf_Tafm_Remote.h"
#include "MnCallApi.h"
#include "AtCheckFunc.h"
#include "AtSndMsg.h"
#include "AtRnicInterface.h"
#include "AtDeviceCmd.h"
#include "AtCheckFunc.h"
#include "TtfMemAtInterface.h"
#include "TafApsApi.h"
#include "AtInputProc.h"
#if (FEATURE_ON==FEATURE_LTE)
#include "msp_nvim.h"
#include "msp_nv_def.h"
#include "msp_nv_id.h"
#include "at_common.h"
#endif


#include "SysNvId.h"
#include "phyoaminterface.h"
#include "TafAgentInterface.h"
#include "TafAppMma.h"

#include "AtTafAgentInterface.h"
#include "AppVcApi.h"
#include "AtTestParaCmd.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_QUERYPARACMD_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/* 记录天线信号格数  */
#define AT_ANTENNA_LEVEL_MAX_NUM        3

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_UINT32  At_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase);

extern MsgBlock* TEST_Build_NdisAtMsg(
    VOS_UINT8                          *pucBuf,
    VOS_UINT16                          usMsgLen,
    VOS_UINT32                          ulMsgId
);

extern AT_DIAL_CONNECT_DISPLAY_RATE_STRU    g_stDialConnectDisplayRate;

extern TAF_PS_EVT_STRU* TEST_Build_ApsAtMsg(
    VOS_UINT32                          ulEvtId,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
    );
extern VOS_UINT32 AT_GetWifiNvValue(VOS_UINT16 *pusCsdValue);
extern TAF_UINT8 At_GetDspLoadMode(VOS_UINT32 ulRatMode);
extern VOS_UINT32 TAF_AGENT_GetSysMode(
    VOS_UINT16                                 usClientId,
    TAF_AGENT_SYS_MODE_STRU                   *pstSysMode
);

extern VOS_UINT32 TAF_PS_SndMsg(
    VOS_UINT32                          ulTaskId,
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
);

extern AT_CMD_ANTENNA_LEVEL_ENUM_UINT8 AT_CalculateAntennaLevel(
           VOS_INT16                           sRscp,
           VOS_INT16                           sEcio
       );
extern VOS_VOID At_CovertMsInternalRxDivParaToUserSet(
                           VOS_UINT16 usCurBandSwitch,
                           VOS_UINT32 *pulUserDivBandsLow,
                           VOS_UINT32 *pulUserDivBandsHigh
                           );
extern VOS_UINT32 AT_DeciDigit2Ascii(
           VOS_UINT8                           aucDeciDigit[],
           VOS_UINT32                          ulLength,
           VOS_UINT8                           aucAscii[]
       );
extern VOS_UINT32  At_DelCtlAndBlankCharWithEndPadding(
           VOS_UINT8                               *pucData,
           VOS_UINT16                              *pusCmdLen
       );
extern VOS_UINT32 AT_GetCsdValue(
           VOS_BOOL                            bSimlockEnableFlg,
           VOS_UINT16                         *pusCsdValue);
extern VOS_UINT32 AT_GetGsmBandStr(
           VOS_UINT8                          *pucGsmBandstr ,
           AT_UE_BAND_CAPA_ST                 *pstBandCapa
       );
extern VOS_UINT32 AT_GetPhynumMac(VOS_UINT8 aucMac[]);
extern VOS_VOID AT_GetSmoothAntennaLevel(
    VOS_UINT8                           ucIndex,
    AT_CMD_ANTENNA_LEVEL_ENUM_UINT8     enLevel
    );
extern VOS_UINT32 AT_GetWcdmaBandStr(
           VOS_UINT8                          *pucGsmBandstr,
           AT_UE_BAND_CAPA_ST                 *pstBandCapa
       );
extern AT_PDP_STATUS_ENUM_UINT32 AT_NdisGetConnStatus(
           AT_PDP_STATE_ENUM_U8                enPdpState
       );
extern VOS_UINT32 AT_OutputCsdfltDefault(
           VOS_UINT8                           ucIndex,
           VOS_BOOL                            bSimlockEnableFlg
       );
extern VOS_UINT32 AT_QryAcpuMemInfoPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryAdcTempPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_QryAlsPara( TAF_UINT8 ucIndex );
extern VOS_UINT32 AT_QryAnQuery( VOS_UINT8 ucIndex );
extern VOS_UINT32 AT_QryAntState(VOS_UINT8 ucIndex);
extern VOS_UINT32  At_QryApDialModePara(
           VOS_UINT8                           ucIndex
       );
extern VOS_UINT32 At_QryApHplmn( VOS_UINT8  ucIndex );
extern VOS_UINT32 AT_QryApLanAddrPara(VOS_UINT8 ucIndex);
extern VOS_UINT32  AT_QryAppdmverPara ( VOS_UINT8 ucIndex );
extern VOS_UINT32  At_QryAppWronReg( VOS_UINT8 ucIndex );
extern VOS_UINT32 AT_QryApRptPortSelectPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryApRptSrvUrlPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_QryApXmlInfoTypePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryApXmlRptFlagPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 AT_QryAuthdataPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_QryAuthorityIdPara( VOS_UINT8 ucIndex );
extern VOS_UINT32 AT_QryAuthorityVerPara( VOS_UINT8 ucIndex );
extern VOS_UINT32 AT_QryAuthverPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_QryAutoAttach(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_QryBatVolPara(VOS_UINT8 ucIndex);
extern VOS_UINT32  At_QryBsn(VOS_UINT8 ucIndex );
extern VOS_UINT32 At_QryCallSrvPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_QryCardlockPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCbndPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCbstPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_QryCcpuMemInfoPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCcugPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCcwaPara(TAF_UINT8 ucIndex);
extern VOS_UINT32  AT_QryCellRoamPara ( VOS_UINT8 ucIndex );
extern VOS_UINT32 At_QryCellSearch(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_QryCemode(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_QryCeregPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_QryCfunPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 AT_QryCgactPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_QryCgattPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 AT_QryCgautoPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_QryCgcattPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_QryCgclassPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_QryCgdcontPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 AT_QryCgdnsPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_QryCgdscontPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_QryCgeqminPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryCgeqreqPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_QryCgregPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCgsmsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 AT_QryCgtftPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_QryChdataPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_QryChipTempPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryChrgEnablePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryChrgInfoPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryCipherPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_QryClipPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryClirPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_QryClvlPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_QryCmeePara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCmgdPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCmgfPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCmmsPara(
           TAF_UINT8                           ucIndex
       );
extern TAF_UINT32 At_QryCmodPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCmsrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCnmiPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryColpPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCommDebugPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCopsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCpamPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCpbsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCpin2Para(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCpinPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCpinStatus(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCplsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCpmsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCPNNPara (TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCpolPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_QryCpuLoadPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_QryCrcPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCregPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCrpnPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_QryCscaPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_QryCscbPara(
           VOS_UINT8                           ucIndex
       );
extern TAF_UINT32 At_QryCscsPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_QryCsdfltPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_QryCsdhPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCsmpPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCsmsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCSNR(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCssnPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCstaPara(TAF_UINT8 ucIndex);
extern VOS_UINT32  At_QryCsVer(VOS_UINT8 ucIndex );
extern TAF_UINT32 At_QryCtzrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCurcPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryCusdPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_QryCuus1Para(
           VOS_UINT8                           ucIndex
       );
extern VOS_UINT32 At_QryCvoicePara (VOS_UINT8 ucIndex);
extern VOS_UINT32  At_QryDataLock(VOS_UINT8 ucIndex );
extern VOS_UINT32 At_QryDdsetexPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_QryDhcpPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryDhcpv6Para(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_QryDialModePara(TAF_UINT8 ucIndex);
extern VOS_UINT32  AT_QryDislogPara ( VOS_UINT8 ucIndex );
extern VOS_UINT32 AT_QryDloadInfoPara( VOS_UINT8 ucIndex );
extern VOS_UINT32 At_QryDnsPrim(
           VOS_UINT8                           ucIndex
       );
extern VOS_UINT32 At_QryDnsSnd(
           VOS_UINT8                           ucIndex
       );
extern VOS_UINT32   At_QryDpaCat(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_QryDwinsPara(TAF_UINT8 ucIndex);
extern VOS_UINT32  AT_QryEcioCfgPara ( VOS_UINT8 ucIndex );
extern VOS_UINT32 AT_QryEqverPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryFacInfoPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryFastDormPara(VOS_UINT8 ucIndex);
extern TAF_UINT32  At_QryFChanPara(TAF_UINT8 ucIndex );
extern TAF_UINT32  AT_QryFDac(TAF_UINT8 ucIndex );
extern VOS_UINT32 AT_QryFeaturePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryFlashInfoPara( VOS_UINT8 ucIndex );
extern VOS_UINT32  At_QryFlnaPara(VOS_UINT8 ucIndex);
extern VOS_UINT32  At_QryFpaPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_QryFPlmnPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryFreqLock(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_QryFrssiPara(
           VOS_UINT8                           ucIndex
       );
extern VOS_UINT32  At_QryFRxonPara(VOS_UINT8 ucIndex);
extern TAF_UINT32  At_QryFTxonPara(TAF_UINT8 ucIndex );
extern TAF_UINT32 At_QryGetportmodePara (TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryGlastErrPara( TAF_UINT8 ucIndex );
extern VOS_UINT32   At_QryGPIOPL(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryGTimerPara(VOS_UINT8 ucIndex);
extern VOS_UINT32   AT_QryHspaSpt(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_QryIccidPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryImsichgPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_QryIpv6CapPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_QryLcStartTimePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryLocinfoPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_QryLtecsInfo(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_QryMaxFreelockSizePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_QryMaxLockTimes(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryMDatePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryNandBadBlockPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryNandDevInfoPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_QryNdisAddPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_QryNdisConnPara(
           VOS_UINT8                           ucIndex
       );
extern VOS_UINT32 At_QryNdisdupPara(
           VOS_UINT8                           ucIndex
       );
extern VOS_UINT32 AT_QryNdisStatPara(
           VOS_UINT8                           ucIndex
       );
extern VOS_UINT32 AT_QryNvBackupStatusPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryNvResumePara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_QryOPLPara (TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryParaCmd(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryPcscInfo(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_QryPdprofmodPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryPhonePhynumPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryPhoneSimlockInfoPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryPhyNumPara(VOS_UINT8 ucIndex);
extern TAF_UINT32  At_QryPlatForm(TAF_UINT8 ucIndex );
extern TAF_UINT32 At_QryPNNPara (TAF_UINT8 ucIndex);
extern VOS_UINT32 At_QryPort(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryPortAttribSetPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryPortCtrlTmpPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_QryPortSelPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_QryProdNamePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryProdTypePara(VOS_UINT8 ucIndex);
extern VOS_UINT32  At_QryQosPara(VOS_UINT8 ucIndex );
extern VOS_UINT32 At_QryQuickStart(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryRRCVersion(TAF_UINT8 ucIndex);
extern VOS_UINT32  AT_QryRscpCfgPara ( VOS_UINT8 ucIndex );
extern VOS_UINT32 AT_QryRsimPara(VOS_UINT8 ucIndex);
extern VOS_UINT32  AT_QryRsrpCfgPara ( VOS_UINT8 ucIndex );
extern TAF_UINT32 AT_QryRstriggerPara(
           TAF_UINT8                           ucIndex
       );
extern VOS_UINT32 At_QryRxDiv(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_QryRxPri(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_QryS0Para(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryS3Para(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryS4Para(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryS5Para(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryS6Para(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryS7Para(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_QrySARReduction(VOS_UINT8 ucIndex);
extern VOS_UINT32  At_QrySD(VOS_UINT8 ucIndex );
extern VOS_UINT32   At_QrySDomainPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_QrySecuBootFeaturePara( VOS_UINT8 ucIndex  );
extern VOS_UINT32 At_QrySecuBootPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_QrySfm(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryShellPara (VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QrySimlockDataReadPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_QrySimLockPlmnInfo(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_QryStgiPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryStsfPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_QrySysCfgExPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_QrySysCfgPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryTimePara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_QryTmmiPara(VOS_UINT8 ucIndex);
extern TAF_UINT32  At_QryTModePara(TAF_UINT8 ucIndex );
extern TAF_UINT32 At_QryU2DiagPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_QryUsbSwitchPara (VOS_UINT8 ucIndex);
extern TAF_UINT32 At_QryUssdModePara(TAF_UINT8 ucIndex);
extern VOS_UINT32  At_QryVersion(VOS_UINT8 ucIndex );
extern VOS_UINT32 At_QryVMSETPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWebPwdPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWiFiBandPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWiFiEnablePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWiFiFreqPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWifiGlobalMacPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWiFiKeyPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWiFiLogPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWiFiModePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWiFiPacketPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWifiPaRangePara (VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWiFiPowerPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWiFiRatePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWiFiRxPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWiFiSsidPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWiFiTxPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_QryYjcxPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_ReadAccessModeNV(
           VOS_UINT8                           *pucSearchMode,
           VOS_UINT16                          *pusValueInfo
       );
extern VOS_UINT32 At_ReadCustomizeServiceNV(
           NAS_NVIM_CUSTOMIZE_SERVICE_STRU              *pstCustSrv,
           VOS_UINT16                          *pusValueInfo
       );
//extern VOS_UINT32  At_ReadDpaCatFromNV(VOS_UINT8 *pucDpaRate);
extern VOS_UINT32 At_ReadGprsActiveTimerLenNV(
           VOS_UINT32                          *pulGprsActiveTimerLen,
           VOS_UINT16                          *pusValueInfo
       );
extern VOS_UINT32 At_ReadMsClassNV(
           TAF_PH_MS_CLASS_TYPE                *pucMsClass,
           VOS_UINT16                          *pusValueInfo
       );
extern VOS_UINT32 AT_ReadRrcVerFromNV(VOS_UINT8 *pucRrcVer);
extern VOS_UINT32 At_ReadTrafficClassTypeNV(
           AT_TRAFFIC_CLASS_CUSTOMIZE_STRU     *pstNvTrafficClass,
           VOS_UINT16                          *pusValueInfo
       );
extern VOS_UINT32 At_ReadUsbEnumStatusNV(
           AT_USB_ENUM_STATUS_STRU             *pstUsbEnumStatus,
           VOS_UINT16                          *pusValueInfo
       );
extern VOS_UINT32 At_ReadWasRadioAccessCapaNV(
           AT_UE_CAPA_STRU                     *pstUECapa,
           VOS_UINT16                          *pusValueInfo,
           VOS_UINT8                           *pucDpaRate
       );
extern VOS_UINT32 AT_ReportNdisStatInfo(VOS_UINT8 ucIndex);
extern VOS_UINT32  At_SimlockPlmnNumToAscii(
           const VOS_UINT8                     *pucPlmnRange,
           VOS_UINT8                           ucPlmnRangeLen,
           VOS_UINT8                            *pucAsciiStr
       );
extern VOS_UINT32 AT_WriteActiveMessage(
                                        MODEM_ID_ENUM_UINT16                enModemId,
                                        MN_MSG_ACTIVE_MESSAGE_STRU         *pstOrgActiveMessageInfo,
                                        MN_MSG_ACTIVE_MESSAGE_STRU         *pstActiveMessageInfo
                                        );
extern VOS_UINT32 AT_RcvMtaCposSetCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvMtaCposrInd(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvMtaXcposrRptInd(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvMtaCgpsClockSetCnf(VOS_VOID *pMsg);
extern VOS_VOID At_ProcMtaMsg(AT_MTA_MSG_STRU *pMsg);


extern VOS_UINT32 AT_FillBodySarWcdmaQryPara(
    MTA_BODY_SAR_PARA_STRU             *pstBodySarPara,
    AT_BODYSARWCDMA_SET_PARA_STRU      *pstBodySarWcdmaPara
);

extern unsigned int  BSP_USB_PortTypeQuery(DRV_DYNAMIC_PID_TYPE_STRU *current_dev_value);

extern void UT_STUB_INIT(void);


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of Test_AtQueryParaCmd.h */
