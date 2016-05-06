/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : GasNvInterface.h
  Description     : GasNvInterface.h header file
  History         :

******************************************************************************/

#ifndef __GASNVINTERFACE_H__
#define __GASNVINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(2)
#else
#pragma pack(push, 2)
#endif

#include "vos.h"

/*****************************************************************************
  2 Macro
*****************************************************************************/
#define NVIM_ULTRA_CLASSMARK_LEN                            (24)
#define NVIM_BAND_PWR_LEN                                   (8)
#define NVIM_CLASSMARK1_LEN                                 (2)
#define NVIM_CLASSMARK2_LEN                                 (4)
#define NVIM_CLASSMARK3_LEN                                 (16)
#define NVIM_CLASSMARK3_R8_LEN                              (36)
#define NVIM_GCF_ITEM_LEN                                   (80)
#define NVIM_GSM_BA_MAX_SIZE                                (33)
#define NVIM_EGPRS_RA_CAPABILITY_DATA_LEN                   (53)
#define NVIM_PREFER_GSM_PLMN_LIST_LEN                       (976)
#define NVIM_GSM_DEC_FAIL_ARFCN_LIST_LEN                    (120)
#define NVIM_EUTRA_MAX_SUPPORT_BANDS_NUM                    (64)
#define NVIM_TDS_MAX_SUPPORT_BANDS_NUM                      (8)
#define NVIM_EUTRA_CAPA_COMM_INFO_SIZE                      (260)
#define NVIM_CBS_MID_LIST_LEN                               (2004)
#define NVIM_CBS_MID_RANGE_LIST_LEN                         (2004)
#define NVIM_GAS_C1_CALC_OPT_PLMN_WHITE_LIST_CNT_MAX        (20)

#define NVIM_GAS_GSM_BAND_CUSTOMIZE_LIST_MAX_CNT            (80)

#define NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_PLMN_MAX_CNT        (10)
#define NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_RANGE_MAX_CNT       (8)
#define NVIM_GSM_OPERATE_CUSTOMIZE_DESCRETE_FREQ_MAX_CNT    (16)

#if defined( __PS_WIN32_RECUR__ ) || defined (DMT)
#define MAX_CHR_ALARM_ID_NUM (20)
#endif

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum NVIM_TDS_FREQ_BAND_LIST_ENUM
{
    ID_NVIM_TDS_FREQ_BAND_A         = 0x01,         /* 频点范围: 9504~9596  10054~10121 */
    ID_NVIM_TDS_FREQ_BAND_B         = 0x02,         /* 频点范围: 9254~9546  9654~9946 */
    ID_NVIM_TDS_FREQ_BAND_C         = 0x04,         /* 频点范围: 9554~9646 */
    ID_NVIM_TDS_FREQ_BAND_D         = 0x08,         /* 频点范围: 12854~13096 */
    ID_NVIM_TDS_FREQ_BAND_E         = 0x10,         /* 频点范围: 11504~11996 */
    ID_NVIM_TDS_FREQ_BAND_F         = 0x20,         /* 频点范围: 9404~9596 */
    ID_NVIM_TDS_FREQ_BAND_BUTT
};
typedef VOS_UINT8  NVIM_TDS_FREQ_BAND_LIST_ENUM_UINT8;

/*****************************************************************************
 枚 举 名  : NVIM_BAND_IND
 枚举说明  : NV的BAND指示
 修改历史  :
  1.日  期   : 2015年9月14日
    作  者   : s00184266
    修改内容 : 新生成枚举

*****************************************************************************/
enum NVIM_BAND_IND_ENUM
{
    NVIM_BAND_IND_2                 = 0x2,          /* BAND2 */
    NVIM_BAND_IND_3                 = 0x3,          /* BAND3 */
    NVIM_BAND_IND_5                 = 0x5,          /* BAND5 */
    NVIM_BAND_IND_8                 = 0x8,          /* BAND8 */
    NVIM_BAND_IND_BUTT
};
typedef VOS_UINT8 NVIM_BAND_IND_ENUM_UINT8;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
*                                                                            *
*                           参数设置消息结构                                 *
*                                                                            *
******************************************************************************/

/*****************************************************************************
 结构名    : NVIM_ULTRA_CLASSMARK_STRU
 结构说明  : en_NV_Item_Ultra_Classmark 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucUltraClassmark[NVIM_ULTRA_CLASSMARK_LEN];
}NVIM_ULTRA_CLASSMARK_STRU;

/*****************************************************************************
 结构名    : NVIM_GAS_MULTIRATE_FLAG_STRU
 结构说明  : en_NV_Item_Gas_MultiRateFlag 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMultiRateFlag;
    VOS_UINT8                           aucReserve[2];
}NVIM_GAS_MULTIRATE_FLAG_STRU;

/*****************************************************************************
 结构名    : NVIM_BAND_PWR_STRU
 结构说明  : en_NV_Item_Band_Pwr 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucBandPwr[NVIM_BAND_PWR_LEN];
}NVIM_BAND_PWR_STRU;

/*****************************************************************************
 结构名    : NVIM_VGCS_FLAG_STRU
 结构说明  : en_NV_Item_Vgcs_Flag 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usVgcsFlag;
    VOS_UINT8                           aucReserve[2];
}NVIM_VGCS_FLAG_STRU;

/*****************************************************************************
 结构名    : NVIM_EGPRS_MULTI_SLOT_CLASS_STRU
 结构说明  : en_NV_Item_Egprs_Multi_Slot_Class 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEgprsMultiSlotClass;                  /* Range: [0,12] */
    VOS_UINT8                           aucReserve[2];
}NVIM_EGPRS_MULTI_SLOT_CLASS_STRU;

/*****************************************************************************
 结构名    : NVIM_GSM_CLASSMARK1_STRU
 结构说明  : en_NV_Item_Gsm_Classmark1 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucGsmClassmark1[NVIM_CLASSMARK1_LEN];
    VOS_UINT8                           aucReserve[2];
}NVIM_GSM_CLASSMARK1_STRU;

/*****************************************************************************
 结构名    : NVIM_GSM_CLASSMARK2_STRU
 结构说明  : en_NV_Item_Gsm_Classmark2 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucGsmClassmark2[NVIM_CLASSMARK2_LEN];
}NVIM_GSM_CLASSMARK2_STRU;

/*****************************************************************************
 结构名    : NVIM_GSM_CLASSMARK3_STRU
 结构说明  : en_NV_Item_Gsm_Classmark3 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucGsmClassmark3[NVIM_CLASSMARK3_LEN];
}NVIM_GSM_CLASSMARK3_STRU;

/*****************************************************************************
 结构名    : NVIM_GSM_IND_FREQ_STRU
 结构说明  : en_NV_Item_Gsm_Ind_Freq 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmIndFreq;
    VOS_UINT8                           aucReserve[2];
}NVIM_GSM_IND_FREQ_STRU;

/*****************************************************************************
 结构名    : NVIM_GCF_ITEM_STRU
 结构说明  : en_NV_Item_GCF_Item 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucGcfItem[NVIM_GCF_ITEM_LEN];
}NVIM_GCF_ITEM_STRU;

/*****************************************************************************
 结构名    : NVIM_G2W_RSSI_RSCP_OFFSET_STRU
 结构说明  : en_NV_Item_G2W_RSSI_RSCP_OFFSET 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usG2WRssiRscpOffset;
    VOS_UINT8                           aucReserve[2];
}NVIM_G2W_RSSI_RSCP_OFFSET_STRU;

/*****************************************************************************
 结构名    : NVIM_GSM_BA_COUNT_STRU
 结构说明  : en_NV_Item_GSM_Ba_Count 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmBaCount;
    VOS_UINT8                           aucReserve[2];
}NVIM_GSM_BA_COUNT_STRU;

/*****************************************************************************
 结构名    : NVIM_GSM_BA_LIST_STRU
 结构说明  : en_NV_Item_GSM_Ba_List 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
    VOS_UINT16                          usArfcn[NVIM_GSM_BA_MAX_SIZE];
    VOS_UINT8                           aucReserve[2];
}NVIM_GSM_BA_LIST_STRU;

/*****************************************************************************
 结构名    : NVIM_EGPRS_FLAG_STRU
 结构说明  : en_NV_Item_Egprs_Flag 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEgprsFlag;
    VOS_UINT8                           aucReserve[2];
}NVIM_EGPRS_FLAG_STRU;

/*****************************************************************************
 结构名    : NVIM_EGPRS_RA_CAPABILITY_STRU
 结构说明  : en_NV_Item_EgprsRaCapability 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLength;
    VOS_UINT8                           aucEgprsRaCapabilityData[NVIM_EGPRS_RA_CAPABILITY_DATA_LEN];
    VOS_UINT8                           aucReserve[2];
}NVIM_EGPRS_RA_CAPABILITY_STRU;

/*****************************************************************************
 结构名    : NVIM_PREFER_GSM_PLMN_COUNT_STRU
 结构说明  : en_NV_Item_Prefer_GSM_PLMN_Count 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPreferGsmPlmnCount;
    VOS_UINT8                           aucReserve[2];
}NVIM_PREFER_GSM_PLMN_COUNT_STRU;

/*****************************************************************************
 结构名    : NVIM_PREFER_GSM_PLMN_LIST_STRU
 结构说明  : en_NV_Item_Prefer_GSM_PLMN_List 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          ausPreferGsmPlmnListData[NVIM_PREFER_GSM_PLMN_LIST_LEN];
}NVIM_PREFER_GSM_PLMN_LIST_STRU;

/*****************************************************************************
 结构名    : NVIM_GSM_DEC_FAIL_ARFCN_COUNT_STRU
 结构说明  : en_NV_Item_GSM_DEC_FAIL_ARFCN_Count 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmDecFailArfcnCount;
    VOS_UINT8                           aucReserve[2];
}NVIM_GSM_DEC_FAIL_ARFCN_COUNT_STRU;

/*****************************************************************************
 结构名    : NVIM_GSM_DEC_FAIL_ARFCN_LIST_STRU
 结构说明  : en_NV_Item_GSM_DEC_FAIL_ARFCN_List 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmDecFailArfcnList[NVIM_GSM_DEC_FAIL_ARFCN_LIST_LEN];
}NVIM_GSM_DEC_FAIL_ARFCN_LIST_STRU;

/*****************************************************************************
 结构名    : NVIM_PREFER_GSM_PLMN_SWITCH_STRU
 结构说明  : en_NV_Item_Prefer_GSM_PLMN_Switch 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPreferGsmPlmnSwitch;
    VOS_UINT8                           aucReserve[2];
}NVIM_PREFER_GSM_PLMN_SWITCH_STRU;

/*****************************************************************************
 结 构 名  : NVIM_PREFER_GSM_PLMN_CUSTOMIZE_CFG_STRU
 结构说明  : 优选小区性能定制
 修改历史  :
  1.日  期   : 2015年9月9日
    作  者   : s00184266
    修改内容 : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAgingEnable;                          /* 优选小区老化的NV使能 */
    VOS_UINT8                           ucRsrv1;                                /* 保留位 */
    VOS_UINT8                           ucRsrv2;                                /* 保留位 */
    VOS_UINT8                           ucRsrv3;                                /* 保留位 */
    VOS_INT16                           sDecFailedRssiThreshold;                /* 从优选小区列表中删除解码失败的RSSI门限 */
    VOS_UINT16                          usRsrv1;                                /* 保留位 */
    VOS_UINT16                          usRsrv2;                                /* 保留位 */
    VOS_UINT16                          usRsrv3;                                /* 保留位 */
    VOS_UINT32                          ulRsrv1;                                /* 保留位 */
    VOS_UINT32                          ulRsrv2;                                /* 保留位 */
}NVIM_PREFER_GSM_PLMN_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
 结构名    : NVIM_GERAN_FEATURE_PACKAGE1_STRU
 结构说明  : en_NV_Item_Geran_Feature_Package1 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGeranFeaturePackage1;                 /* Range: [0,1] */
    VOS_UINT8                           aucReserve[2];
}NVIM_GERAN_FEATURE_PACKAGE1_STRU;

/*****************************************************************************
 结构名    : NVIM_GSM_A5_STRU
 结构说明  : en_NV_Item_Gsm_A5 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmA5;                                /* Range: [0,7] */
    VOS_UINT8                           aucReserve[2];
}NVIM_GSM_A5_STRU;

/*****************************************************************************
 结构名    : NVIM_LOW_COST_EDGE_FLAG_STRU
 结构说明  : en_NV_Item_LowCostEdge_Flag 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usLowCostEdgeFlag;                      /* Range: [0,1] */
    VOS_UINT8                           aucReserve[2];
}NVIM_LOW_COST_EDGE_FLAG_STRU;

/*****************************************************************************
 结构名    : NVIM_GPRS_ACTIVE_TIMER_LENGTH_STRU
 结构说明  : en_NV_Item_GPRS_ActiveTimerLength 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulGprsActiveTimerLength;
}NVIM_GPRS_ACTIVE_TIMER_LENGTH_STRU;

/*****************************************************************************
 结构名    : NVIM_GPRS_MULTI_SLOT_CLASS_STRU
 结构说明  : en_Nv_Item_Gprs_Multi_Slot_Class 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGprsMultiSlotClass;                   /* Range: [0,12] */
    VOS_UINT8                           aucReserve[2];
}NVIM_GPRS_MULTI_SLOT_CLASS_STRU;

/*****************************************************************************
 结构名    : NVIM_GSM_PLMN_SEARCH_ARFCN_MAX_NUM_STRU
 结构说明  : en_NV_Item_GSM_PLMN_SEARCH_ARFCN_MAX_NUM 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmPlmnSearchArfcmMaxNum;             /* Range: [0x1,0x8C] */
    VOS_UINT8                           aucReserve[2];
}NVIM_GSM_PLMN_SEARCH_ARFCN_MAX_NUM_STRU;

/*****************************************************************************
 结构名    : NVIM_GCBS_CONF_STRU
 结构说明  : en_Nv_Item_GCBS_Conf 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usECBCHSwitch;              /* Range: [0,1] */
    VOS_UINT16                                      usDrxSwitch;                /* Range: [0,1] */
    VOS_UINT32                                      ulGCBSActiveTimerLength;
}NVIM_GCBS_CONF_STRU;

/*****************************************************************************
 结构名    : NVIM_REPEATED_ACCH_CAPABILITY_STRU
 结构说明  : en_NV_Item_Repeated_Acch_Capability 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usRepeatedAcchCapability;
    VOS_UINT8                                       aucReserve[2];
}NVIM_REPEATED_ACCH_CAPABILITY_STRU;


/*****************************************************************************
 结构名    : NVIM_ES_IND_STRU
 结构说明  : en_NV_Item_ES_IND 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usEsInd;                    /* Range: [0,1] */
    VOS_UINT8                                       aucReserve[2];
}NVIM_ES_IND_STRU;

/*****************************************************************************
 结构名    : NVIM_GPRS_EXTENDED_DYNAMIC_ALLOCATION_CAPABILITY_STRU
 结构说明  : en_NV_Item_GPRS_Extended_Dynamic_Allocation_Capability 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usGprsExtDynAllocCap;       /* Range: [0,1] */
    VOS_UINT8                                       aucReserve[2];
}NVIM_GPRS_EXTENDED_DYNAMIC_ALLOCATION_CAPABILITY_STRU;

/*****************************************************************************
 结构名    : NVIM_EGPRS_EXTENDED_DYNAMIC_ALLOCATION_CAPABILITY_STRU
 结构说明  : en_NV_Item_EGPRS_Extended_Dynamic_Allocation_Capability 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usEGprsExtDynAllocCap;      /* Range: [0,1] */
    VOS_UINT8                                       aucReserve[2];
}NVIM_EGPRS_EXTENDED_DYNAMIC_ALLOCATION_CAPABILITY_STRU;

/*****************************************************************************
 结构名    : NVIM_REVISION_LEVEL_INDICATOR_STRU
 结构说明  : en_NV_Item_Revision_Level_Indicator 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usRevLvlInd;                /* Range: [0,1] */
    VOS_UINT8                                       aucReserve[2];
}NVIM_REVISION_LEVEL_INDICATOR_STRU;

/*****************************************************************************
 结构名    : NVIM_DOWNLINK_ADVANCED_RECEIVER_PERFORMANCE_STRU
 结构说明  : en_NV_Item_Downlink_Advanced_Receiver_Performance 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usDlAdvRcvPer;              /* Range: [0,1] */
    VOS_UINT8                                       aucReserve[2];
}NVIM_DOWNLINK_ADVANCED_RECEIVER_PERFORMANCE_STRU;

/*****************************************************************************
 结构名    : NVIM_EXT_RLC_MAC_CTRL_MSG_SEGMENT_CAPABILITY_STRU
 结构说明  : en_NV_Item_Ext_RLC_MAC_Ctrl_Msg_Segment_Capability 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usExtRlcMacCtrlMsgSegCap;   /* Range: [0,1] */
    VOS_UINT8                                       aucReserve[2];
}NVIM_EXT_RLC_MAC_CTRL_MSG_SEGMENT_CAPABILITY_STRU;

/*****************************************************************************
 结构名    : NVIM_PS_HANDOVER_CAPABILITY_STRU
 结构说明  : en_NV_Item_PS_Handover_Capability 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usPsHandoverCapability;     /* Range: [0,1] */
    VOS_UINT8                                       aucReserve[2];
}NVIM_PS_HANDOVER_CAPABILITY_STRU;

/*****************************************************************************
 结构名    : NVIM_GAS_WEAK_SIGNAL_THREHOLD_STRU
 结构说明  : en_NV_Item_GAS_Errorlog_Energy_Threshold 结构
*****************************************************************************/
typedef struct
{
    VOS_INT16                                       sWeakSignalThreshold;
    VOS_UINT8                                       aucReserve[2];
}NVIM_GAS_WEAK_SIGNAL_THREHOLD_STRU;

/*****************************************************************************
 结构名    : NVIM_GSM_MULTIRATE_CAP_STRU
 结构说明  : en_NV_Item_GSM_Multirate_Capability 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                       ucGsmMultirateCap;
    VOS_UINT8                                       aucRsv[3];
}NVIM_GSM_MULTIRATE_CAP_STRU;

/*****************************************************************************
 结构名    : NVIM_GSM_CLASSMARK3_R8_STRU
 结构说明  : en_NV_Item_Gsm_Classmark3_R8 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                       aucGsmClassMark3Data[NVIM_CLASSMARK3_R8_LEN];
}NVIM_GSM_CLASSMARK3_R8_STRU;

/*****************************************************************************
 结构名    : NVIM_EUTRA_MEAS_AND_REPORTING_SUPPORT_FLG_STRU
 结构说明  : en_NV_Item_EUTRA_MEAS_AND_REPORTING_SUPPORT_FLG 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usLteMeasSupportedFlg;      /* Range: [0,1] */
    VOS_UINT8                                       aucReserve[2];
}NVIM_EUTRA_MEAS_AND_REPORTING_SUPPORT_FLG_STRU;

/*****************************************************************************
 结构名    : NVIM_PRI_BASED_RESEL_SUPPORT_FLG_STRU
 结构说明  : en_NV_Item_PRI_BASED_RESEL_SUPPORT_FLG 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usPriBasedReselSupportFlg;  /* Range: [0,1] */
    VOS_UINT8                                       aucReserve[2];
}NVIM_PRI_BASED_RESEL_SUPPORT_FLG_STRU;

/*****************************************************************************
 结构名    : NVIM_GERAN_TO_EUTRA_SUPPORT_IN_TRANSFER_MODE_STRU
 结构说明  : en_NV_Item_GERAN_TO_EUTRA_SUPPORT_IN_TRANSFER_MODE 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usLteSupportInTransferMode; /* Range: [0,3] */
    VOS_UINT8                                       aucReserve[2];
}NVIM_GERAN_TO_EUTRA_SUPPORT_IN_TRANSFER_MODE_STRU;

/*****************************************************************************
 结构名    : NVIM_UE_EUTRA_FREQ_BAND_INFO_STRU
 结构说明  : 用于描述一个 LTE 频段
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucBandNo;
    VOS_UINT8                           ucDuplexModeFlg;
    VOS_UINT8                           aucReserve[2];
}NVIM_UE_EUTRA_FREQ_BAND_INFO_STRU;

/*****************************************************************************
 结构名    : NVIM_UE_EUTRA_SUPPORT_FREQ_BAND_LIST_STRU
 结构说明  : en_NV_Item_EUTRA_CAPA_COMM_INFO 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usBandCnt;
    VOS_UINT8                               aucReserved1[2];
    NVIM_UE_EUTRA_FREQ_BAND_INFO_STRU       astCandBands[NVIM_EUTRA_MAX_SUPPORT_BANDS_NUM];
}NVIM_UE_EUTRA_SUPPORT_FREQ_BAND_LIST_STRU;

/*****************************************************************************
 结构名    : NVIM_GAS_HIGH_MULTISLOT_CLASS_STRU
 结构说明  : en_NV_Item_GAS_High_Multislot_Class 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usHighMultislotClassFlg;
    VOS_UINT16                              usHighMultislotClass;
}NVIM_GAS_HIGH_MULTISLOT_CLASS_STRU;

/*****************************************************************************
 结构名    : NVIM_GPRS_NON_DRX_TIMER_LENGTH_STRU
 结构说明  : en_NV_Item_GPRS_Non_Drx_Timer_Length 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usNonDrxTimerLen;                   /* Range: [0,7] */
    VOS_UINT8                               aucReserve[2];
}NVIM_GPRS_NON_DRX_TIMER_LENGTH_STRU;

/*****************************************************************************
 结构名    : NVIM_UE_TDS_SUPPORT_FREQ_BAND_LIST_STRU
 结构说明  : en_NV_Item_UTRAN_TDD_FREQ_BAND 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucBandCnt;                          /* Range: [0,6] */
    VOS_UINT8                               aucReserved[3];
    VOS_UINT8                               aucBandNo[NVIM_TDS_MAX_SUPPORT_BANDS_NUM];
}NVIM_UE_TDS_SUPPORT_FREQ_BAND_LIST_STRU;

/*****************************************************************************
 结构名    : NVIM_QSEARCH_CUSTOMIZATION_STRU
 结构说明  : en_NV_Item_QSearch_Customization 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usQSearchCustomMode;
    VOS_UINT8                               aucReserve[2];
}NVIM_QSEARCH_CUSTOMIZATION_STRU;

/*****************************************************************************
 结构名    : NVIM_GSM_POOR_RXQUAL_THRESHOLD_STRU
 结构说明  : en_NV_Item_Gsm_Poor_RxQual_ThresHold 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usRrPoorRxQualThresHold;
    VOS_UINT8                               aucReserve[2];
}NVIM_GSM_POOR_RXQUAL_THRESHOLD_STRU;

/*****************************************************************************
 结构名    : NVIM_CSFB_CUSTOMIZATION_STRU
 结构说明  : en_NV_Item_Csfb_Customization 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usCsfbCustomization;
    VOS_UINT8                               aucReserve[2];
}NVIM_CSFB_CUSTOMIZATION_STRU;

/*****************************************************************************
 结构名    : NVIM_CBS_MID_LIST_STRU
 结构说明  : en_NV_Item_CBS_MID_List 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               aucCbsMidList[NVIM_CBS_MID_LIST_LEN];
}NVIM_CBS_MID_LIST_STRU;

/*****************************************************************************
 结构名    : NVIM_CBS_MID_RANGE_LIST_STRU
 结构说明  : en_NV_Item_CBS_MID_Range_List 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               aucCbsMidRangeList[NVIM_CBS_MID_RANGE_LIST_LEN];
}NVIM_CBS_MID_RANGE_LIST_STRU;

/*****************************************************************************
 结构名    : NVIM_GSM_AUTO_FR_LTE_MEAS_CONFIG_STRU
 结构说明  : GSM自主重定向到LTE的LTE频点测量配置
 修改历史  :
 1.日    期    : 2013年08月05日
   作    者    : y00142674
   修改内容    : 新建结构体, GSM自主重定向到LTE
*****************************************************************************/
typedef struct
{
   VOS_UINT8                            ucFrLteMeasFlag;                        /* 是否开启GSM自主重定向到LTE的LTE频点测量，0: 关闭, 1: 开启，默认值为1 */
   VOS_UINT8                            ucMaxSavedMeasTimes;                    /* 最大保存的测量次数，默认值为8，范围:[0,8] */

   VOS_UINT8                            ucFrInvalidMeasFlag;                    /* 是否开启用测量结果判断GSM自主重定向到LTE是否有效，0: 关闭, 1: 开启，默认值为1 */
   VOS_UINT8                            ucMaxInvalidMeasTimes;                  /* 最大无效测量次数，用来判定频点是否有效，不大于最大保存的测量次数，默认值为8，范围:[0,8] */
}NVIM_GSM_AUTO_FR_LTE_MEAS_CONFIG_STRU;

/*****************************************************************************
 结构名    : NVIM_GSM_C1_CUSTOMIZE_CFG_STRU
 结构说明  : C1准则定制配置
 修改历史  :
 1.日    期    : 2014年01月17日
   作    者    : w00146666
   修改内容    : 新建结构体, 应用于C1准则定制
*****************************************************************************/
typedef struct
{
   VOS_UINT8                            ucC1CustomizeSwitchFlag;          /* 是否开启路损C1定制，0: 关闭, 1: 开启，默认值为0 */
   VOS_UINT8                            ucRxlevAccessMin;                 /* 开启路损C1定制后，定制的最小接入电平等级，默认等级为8，范围:[0,63] */
   VOS_UINT8                            ucC1ValueThreshold;               /* C1阈值 */
   VOS_UINT8                            aucRsv[1];
}NVIM_GSM_C1_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
 结构名    : NVIM_GSM_NFREQ_THRESHOLD_STRU
 结构说明  : en_NV_Item_Gsm_NFreq_Threshold 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucFirstNFreqThreshold;                 /* 邻频干扰过滤门限 */
    VOS_UINT8                            aucRsv[3];
}NVIM_GSM_NFREQ_THRESHOLD_STRU;

/*****************************************************************************
 结构名    : NVIM_GAS_W_NON_NCELL_MEAS_CTRL_STRU
 结构说明  : en_NV_Item_Gas_W_Non_NCell_Meas_Ctrl 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucIdleNonNCellMeasEnable;              /* 空闲态下是否启动非邻区测量 */
    VOS_UINT8                            ucTransferNonNCellMeasEnable;          /* 传输态下是否启动非邻区测量 */
    VOS_INT16                            sRscpThreshold;                        /* 启动非邻区测量的 RSCP 门限 */
    VOS_INT16                            sEcn0Threshold;                        /* 启动非邻区测量的 ECN0 门限 */
    VOS_INT16                            sRssiThreshold;                        /* 启动非邻区测量的 RSSI 门限 */
}NVIM_GAS_W_NON_NCELL_MEAS_CTRL_STRU;
/*****************************************************************************
 结构名    : NV_GSM_RF_UNAVAILABLE_CFG_STRU
 结构说明  : en_NV_Item_GSM_RF_UNAVAILABLE_CFG 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStartSearchFlag;                      /* 是否启动搜网:,1:是; 0:否 */
    VOS_UINT8                           ucSearchTimerLen;                       /* 多长时间启动搜网，单位:s */
    VOS_UINT8                           aucRsv[2];
}NV_GSM_RF_UNAVAILABLE_CFG_STRU;

/*****************************************************************************
 结构名    : NVIM_GSM_CELL_INFO_RPT_CFG_STRU
 结构说明  : en_NV_Item_Gsm_Cell_Info_Rpt_Cfg 结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucCellInfoRptFlg;      /* 是否启动上报: 0:不启动; 1:启动 */
    VOS_UINT8                            aucRsv[1];             /* 保留位 */
    VOS_UINT16                           usRptInterval;         /* 上报周期长度, 单位: ms */
}NVIM_GSM_CELL_INFO_RPT_CFG_STRU;

/*****************************************************************************
 结构名    : NVIM_GAS_INDIVIDUAL_CUSTOMIZE_CFG_STRU
 结构说明  : en_NV_Item_Gas_Individual_Customize_Cfg 结构,用于设置非标的特殊定制相关的配置
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAccFailNoPunishCfg;                   /* 是否惩罚随即接入失败的小区:
                                                                                   bit0: 1: PS失败不惩罚; 0: PS失败惩罚
                                                                                   bit1: 1: CS失败不惩罚; 0: CS失败惩罚 */
    VOS_INT8                            cFreqRxlevThreshold;                    /* 有效频点能量门限,主要用于搜网流程
                                                                                   被动重选 目标小区选择时也会用到 */

    VOS_UINT8                           ucAutoFrNonChanRelCase;                 /* 没有收到 Channel Release 的异常场景下是否启动 FR:
                                                                                   bit0: 1: 主动挂断时启动 FR;
                                                                                         0: 主动挂断时不启动FR
                                                                                   bit1: 1: 语音链路失败启动FR;
                                                                                         0: 语音链路失败不启动FR */

    VOS_UINT8                           ucScellPrioFastEnableFlg;

    VOS_UINT8                           aucRsv[36];
}NVIM_GAS_INDIVIDUAL_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
 结构名    : NVIM_GSM_MNTN_CONFIG_STRU
 结构说明  : GSM可维可测相关的NV配置
 修改历史  :
 1.日    期    : 2014年07月03日
   作    者    : w00146666
   修改内容    : 新建结构体
 2.日    期    : 2015年10月26日
   作    者    : w00146666
   修改内容    : 调整结构，新增两次伪基站CHR上报的最短时间间隔 NV配置 
*****************************************************************************/
typedef struct
{
   VOS_UINT16                           usCsHoTimeAlarmThreshold;              /* CS切换时间长度门限，超过该切换时间，GAS主动上报告警信息 */

   VOS_UINT16                           usRptPseudBtsMinTimeInterval;         /* 两次伪基站CHR上报的最短时间间隔，单位:分钟；默认值为30分钟 */   

   VOS_UINT16                           usRsv1;                                /* 预留位1，为以后KWKC预留 */

   VOS_UINT16                           usRsv2;                                /* 预留位2，为以后KWKC预留 */

   VOS_UINT16                           usRsv3;                                /* 预留位3，为以后KWKC预留 */

   VOS_UINT8                            ucRsv4;                                /* 预留位4，为以后KWKC预留 */   

   VOS_UINT8                            ucRsv5;                                /* 预留位5，为以后KWKC预留 */      

   VOS_UINT32                           ulRsv6;                                /* 预留位6，为以后KWKC预留 */

   VOS_UINT32                           ulRsv7;                                /* 预留位7，为以后KWKC预留 */
}NVIM_GAS_MNTN_CONFIG_STRU;

/*****************************************************************************
 结构名    : NVIM_GAS_UTRAN_TDD_DEFAULT_Q_RXLMIN
 结构说明  : en_NV_Item_GAS_UTRAN_TDD_DEFAULT_Q_RXLMIN NV结构 网络没有配置
             基于优先级的 UTRAN 重选参数时, 默认的 UTRAN TDD Q_RXLMIN. 仅在基于
             优先级重选时使用. 基于 Ranking 的默认重选门限是 -90dB, 不需要定制
 修改历史  :
 1.日    期    : 2014年12月20日
   作    者    : p00166345
   修改内容    : 新建结构体
*****************************************************************************/
typedef struct
{
   VOS_UINT8                            ucTdsDefaultQRxlMin;            /* TDS 默认重选门限, 单位: -1dB */

   VOS_UINT8                            aucRsv[3];                      /* 保留位 */
}NVIM_GAS_UTRAN_TDD_DEFAULT_Q_RXLMIN;

/*****************************************************************************
 结构名    : NVIM_GAS_C1_CALC_OPT_PLMN_WHITE_LIST_STRU
 结构说明  : C1计算优化网络白名单(目前仅在L CSFB G流程中使用)
 修改历史  : 
 1.日    期    : 2015年02月06日
   作    者    : y00265681
   修改内容    : 新建结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
}NVIM_GAS_PLMN_ID_STRU;

typedef struct
{
   VOS_UINT16                           usPlmnCnt;                                                  /* 白名单中PLMN个数 */  
   VOS_UINT16                           usReserve;
   NVIM_GAS_PLMN_ID_STRU                astPlmn[NVIM_GAS_C1_CALC_OPT_PLMN_WHITE_LIST_CNT_MAX];       /* 预留位，为以后KWKC预留 */
}NVIM_GAS_C1_CALC_OPT_PLMN_WHITE_LIST_STRU;

/*****************************************************************************
 结构名    : NVIM_GSM_RAPID_HO_CUSTOMIZE_CFG_STRU
 结构说明  : en_NV_Item_GSM_RAPID_HO_CUSTOMIZE_CFG 结构,GSM快速切换定制特性相关配置
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSwitchFlag;                   /* 特性开关 */
    VOS_UINT8                           ucBadQualityThreshold;          /* 信号质量判定门限.误码率.单位: 百分之一 */
    VOS_UINT16                          usAlpha;                        /* Alpha因子. 单位: 0.001 */
    VOS_UINT8                           ucBadQualityCntThreshold;       /* 信号质量差统计门限 */
    VOS_UINT8                           ucNCellRptAddValue;             /* 邻区上报增加值 */
    VOS_UINT8                           aucRsv[2];                      /* 保留位 */
}NVIM_GSM_RAPID_HO_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
 结构名    : NVIM_GSM_BAND_CUSTOMIZE_STRU
 结构说明  : GSM 频段定制结构定义
 修改历史  : 
 1.日    期    : 2015-04-23
   作    者    : p00166345
   修改内容    : 新建结构体
*****************************************************************************/
typedef struct
{
    NVIM_GAS_PLMN_ID_STRU               stPlmn;
    VOS_UINT32                          ulBand;
}NVIM_GSM_BAND_CUSTOMIZE_STRU;

/*****************************************************************************
 结构名    : NVIM_GAS_GSM_BAND_CUSTOMIZE_CFG_STRU
 结构说明  : en_NV_Item_GAS_GSM_BAND_CUSTOMIZE_CFG NV 结构定义
 修改历史  : 
 1.日    期    : 2015-04-23
   作    者    : p00166345
   修改内容    : 新建结构体
*****************************************************************************/
typedef struct
{
   VOS_UINT16                           usItemCnt;                  /* 定制项个数 */
   VOS_UINT16                           usRestoreEnableMask;        /* 启用被丢弃的超出协议范围的频点生效场景 */
   VOS_UINT32                           ulCustomizeBandEnableMask;  /* 定制 Band 生效场景 */
   NVIM_GSM_BAND_CUSTOMIZE_STRU         astCustomizeBand[NVIM_GAS_GSM_BAND_CUSTOMIZE_LIST_MAX_CNT];
}NVIM_GAS_GSM_BAND_CUSTOMIZE_CFG_STRU;

/* Added by y00142674 for 漫游搜网优化, 2015-04-30, begin */
/*****************************************************************************
 结构名    : NVIM_GSM_SEARCH_CUSTOMIZE_CFG_STRU
 结构说明  : en_NV_Item_GSM_SEARCH_CUSTOMIZE_CFG 结构，GSM搜网流程相关配置
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRsv1;                                 /* 废弃，高质量指定搜流程是否使用历史频点 */
    VOS_UINT8                           ucRsv2;                                 /* 废弃，GOos搜流程是否使用历史频点 */

    VOS_UINT8                           ucGeoHighUseStoreFlag;           /* 高质量获取地理信息流程是否使用历史频点 */
    VOS_UINT8                           ucGeoHighRemoveStoreFlag;        /* 高质量获取地理信息流程是否在高质量扫频阶段删除历史频点 */
    VOS_UINT8                           ucGeoNormalUseStoreFlag;         /* 非高质量获取地理信息流程是否使用历史频点 */

    VOS_UINT8                           ucRmvDecFailSamePlmnFlag;        /* 频点解码失败后是否删除所有相同PLMN的优选小区 */

    VOS_UINT8                           ucUpdateRssiBySi;                /* 根据系统消息更新信号强度 */

    VOS_UINT8                           ucHistorySrchOperatorCustomizeCellCnt;  /* HISTORY搜索运营商定制频点的个数范围 */

}NVIM_GSM_SEARCH_CUSTOMIZE_CFG_STRU;
/* Added by y00142674 for 漫游搜网优化, 2015-04-30, end */

/*****************************************************************************
 结构名    : NVIM_GAS_GSM_CELL_HISTORY_BCCH_SI_CFG_STRU
 结构说明  : en_NV_Item_GAS_GSM_CELL_HISTORY_BCCH_SI_CFG NV 结构定义
 修改历史  : 
 1.日    期    : 2015-05-06
   作    者    : p00166345
   修改内容    : 新建结构体
 2.日    期    : 2015-07-15
   作    者    : y00142674
   修改内容    : 增加邻区系统消息使能标志和有效时长

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;                    /* 是否生效 */
    VOS_UINT8                           ucRefreshTimeLen;               /* 使用历史系统消息驻留后多久强制刷新系统消息.
                                                                           单位:秒. 0表示不强制刷新 */

    VOS_UINT16                          usValidTimeLen;                 /* 有效时长, 单位:分钟 */
    VOS_UINT32                          ulUsableMask;                   /* 用于指定可以使用历史系统消息驻留的流程 */
    VOS_UINT8                           ucNcellEnableFlg;               /* 邻区系统消息是否生效 */
    VOS_UINT8                           ucNcellValidTimeLen;            /* 有效时长, 单位:秒 */
    VOS_UINT8                           ucRsv3;                         /* 保留位 */
    VOS_UINT8                           ucRsv4;                         /* 保留位 */
}NVIM_GAS_GSM_CELL_HISTORY_BCCH_SI_CFG_STRU;

/*****************************************************************************
 结构名    : NVIM_GAS_H_PRIO_CONDITION_FLAG_STRU
 结构说明  : H_PRIO使用场景定制配置 
 修改历史  : 
 1.日    期    : 2015年05月17日
   作    者    : w00146666
   修改内容    : 新建结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucHPrioCustomizeFlag;   /* H_PRIO使用场景定制配置, 0表示使用H_PRIO参数不考虑异系统小区的优先级，
                                                                    1表示使用H_PRIO参数的前提条件是异系统小区的优先级比服务小区优先级低 */
    
    VOS_UINT8                            ucRsv1;                 /* 保留位1 */
    
    VOS_UINT8                            ucRsv2;                 /* 保留位2 */
    
    VOS_UINT8                            ucRsv3;                 /* 保留位3 */
}NVIM_GAS_INTER_RAT_RESEL_H_PRIO_CUSTOMIZE_STRU;

/*****************************************************************************
 结构名    : NVIM_GAS_FAST_AREA_LOST_CFG_STRU
 结构说明  : en_NV_Item_GAS_FAST_AREA_LOST_CFG NV结构
             用于定制 RR 随机接入失败后是否快速给 NAS 上报丢网
 修改历史  : 
 1.日    期    : 2015年05月15日
   作    者    : p00166345
   修改内容    : 新建结构体
*****************************************************************************/
typedef struct
{
   VOS_UINT8                            ucRrRaFailEnableFlg;        /* 生效标志 */

   VOS_UINT8                            ucRsv1;                     /* 保留位 */
   VOS_UINT8                            ucRsv2;                     /* 保留位 */
   VOS_UINT8                            ucRsv3;                     /* 保留位 */
}NVIM_GAS_FAST_AREA_LOST_CFG_STRU;

/*****************************************************************************
 结构名    : NVIM_GAS_AUTO_FR_CFG_STRU
 结构说明  : en_NV_Item_GAS_AUTO_FR_CFG NV结构
             用于配置在具体场景下是否可以启动自主 FR.
 修改历史  : 
 1.日    期    : 2015-06-09
   作    者    : p00166345
   修改内容    : 新建结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucAutoFrInvalidMask;   /* 生效标志。各bit值 0 表示可以返回, 1 表示无效不可以返回 */
                                                                /* bit0: CSFB 主叫, NAS仍未反馈业务建立结果的情况下是否可以返回 */
                                                                /* bit1: CSFB 被叫, NAS仍未反馈业务建立结果的情况下是否可以返回 */
                                                                /* bit2~bit8: 保留位 */

    VOS_UINT8                            ucAutoFrNonCsfbFlg;       /* 非CSFB场景下, 业务结束时是否自主返回 */
    VOS_UINT8                            ucRsv2;                /* 保留位 */
    VOS_UINT8                            ucRsv3;                /* 保留位 */
}NVIM_GAS_AUTO_FR_CFG_STRU;

/* Added by p00166345 for DTS2015052601104(伪基站识别), 2015-08-02, begin */
/*****************************************************************************
 Structure      : NVIM_GAS_PSEUD_BTS_IDENT_CUSTOMIZE_CFG_STRU
 Description    : 伪基站判断定制用NV结构
 Message origin :
 修改历史 :
  1.日    期    : 2015年07月29日
    作    者    : yangsicong
    修改内容    : 伪基站识别项目
*****************************************************************************/
typedef struct
{
    VOS_UINT16      usEnableBitmap;             /* 识别算法是否使能 ：0=是；1=否 */
                                                    /* bit0: X2G REDIR流程是否使能识别算法; */
                                                    /* bit1: X2G reselect流程是否使能识别算法; */
                                                    /* bit2: X2G CCO流程是否使能识别算法; */
                                                    /* bit3: GSM  SPEC搜/GOOS搜流程是否使能识别算法; */
                                                    /* bit4: GSM HISTORY搜/GSM FAST搜流程是否使能识别算法; */
                                                    /* bit5~bit15: 预留 */
    VOS_UINT16      ucReserve1;                 /* 备用字段 */
    VOS_UINT16      usFeatureSetEnableBitmap;   /* 使能的伪基站特征集BITMAP: bit (n)=1表示第n个特征集是有效的; */
    VOS_UINT16      usReserve2;                 /* 备用字段 */
    VOS_UINT16      usPseudBTSFeatureSet0;      /* 特征集0,每个bit代表一个特征,该bit为1时表示该特征属于这个特征集合:
                                                    bit0代表 RX_ACCESS_MIN=0; 
                                                    bit1 代表 CCCH-CONF='001'时,BS-AG-BLKS-RES=2; 
                                                    bit2 代表 不支持GPRS; 
                                                    bit3 代码CRO超过 60;
                                                    bit4 代码MCC为460;
                                                    bit5~bit15预留 */
    VOS_UINT16      usPseudBTSFeatureSet1;      /* 备用字段*/
    VOS_UINT16      usPseudBTSFeatureSet2;      /* 备用字段*/
    VOS_UINT16      usPseudBTSFeatureSet3;      /* 备用字段*/
    VOS_UINT16      usPseudBTSFeatureSet4;      /* 备用字段*/
    VOS_UINT16      usPseudBTSFeatureSet5;      /* 备用字段*/
    VOS_UINT16      usPseudBTSFeatureSet6;      /* 备用字段*/
    VOS_UINT16      usPseudBTSFeatureSet7;      /* 备用字段*/
} NVIM_GAS_PSEUD_BTS_IDENT_CUSTOMIZE_CFG_STRU;
/* Added by p00166345 for DTS2015052601104(伪基站识别), 2015-08-02, end */

/*****************************************************************************
 结 构 名  : NVIM_GAS_NETWORK_SEARCH_CUSTOMIZE_CFG_STRU
 结构说明  : 网络搜索定制NV
 修改历史  :
  1.日  期   : 2015年9月14日
    作  者   : s00184266
    修改内容 : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT32              ulHistoryFreqEnableBitmap;                          /* 历史频点搜索流程使能bit位 */
    VOS_UINT32              ulOperateFreqEnableBitmap;                          /* 运营商定制频点搜索流程使能bit位 */
    VOS_UINT32              ulFullListEnableBitmap;                             /* 全频段搜索流程使能bit位 */
    VOS_UINT32              ulHistoryFilterSrchedFreqEnableBitmap;              /* 历史频点搜索流程过滤已搜索频点功能使能 bit位 */
    VOS_UINT32              ulOperateFilterSrchedFreqEnableBitmap;              /* 运营商定制频点搜索流程过滤已搜索频点功能使能 bit位 */
    VOS_UINT32              ulFullListFilterSrchedFreqEnableBitmap;             /* 全频段频点搜索流程过滤已搜索频点功能使能 bit位 */
    VOS_UINT32              ulIgnoreLowPrioJudgeEnableBitmap;                   /* 不区分低优先级功能使能bit位 */
    VOS_UINT32              ulCloudFreqEnableBitmap;                            /* 云端定制频点搜索流程使能bit位 */
    VOS_UINT32              ulHistoryFreqBandSrchEnableBitmap;                  /* 历史频点所在频段搜索流程使能位 */
    VOS_UINT32              ulPresetFreqBandSrchEnableBitmap;                   /* 预置频点搜做频段搜索流程使能位 */
    VOS_UINT32              ulCloudBandEnableBitmap;                            /* 云端定制频段搜索流程使能bit位 */
    VOS_UINT32              ulCloudFreqFilterSrchedFreqEnableBitmap;            /* 云端频点搜索流程过滤已搜索频点功能使能 bit位 */
    VOS_UINT32              ulReserved1;                                        /* 保留位 */
    VOS_UINT32              ulReserved2;                                        /* 保留位 */
    VOS_UINT32              ulReserved3;                                        /* 保留位 */
    VOS_UINT32              ulReserved4;                                        /* 保留位 */
    VOS_UINT32              ulReserved5;                                        /* 保留位 */
}NVIM_GSM_NETWORK_SEARCH_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
 结 构 名  : NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_RANGE_STRU
 结构说明  : GSM运营商定制的频点范围结构
 修改历史  :
  1.日  期   : 2015年8月28日
    作  者   : s00184266
    修改内容 : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqBegin;                            /* 起始频点 */
    VOS_UINT16                          usFreqEnd;                              /* 终止频点 */
    NVIM_BAND_IND_ENUM_UINT8            enBand;                                 /* BAND指示 */
    VOS_UINT8                           ucRsv1;                                 /* 保留位 */
    VOS_UINT8                           ucRsv2;                                 /* 保留位 */
    VOS_UINT8                           ucRsv3;                                 /* 保留位 */
}NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_RANGE_STRU;

/*****************************************************************************
 结 构 名  : NVIM_GSM_OPERATE_CUSTOMIZE_DISCRETE_STRU
 结构说明  : GSM运营商定制的GSM离散频点结构
 修改历史  :
  1.日  期   : 2015年9月1日
    作  者   : s00184266
    修改内容 : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreq;                                 /* 频点号 */
    NVIM_BAND_IND_ENUM_UINT8            enBand;                                 /* BAND指示 */
    VOS_UINT8                           ucRsv1;                                 /* 保留位 */
}NVIM_GSM_OPERATE_CUSTOMIZE_DISCRETE_STRU;

/*****************************************************************************
 结 构 名  : NVIM_GSM_OPERATOR_CUSTOMIZE_PLMN_ITEM_STRU
 结构说明  : 运营商定制的GSM频点列表，由PLMN、BAND、起始频点、终止频点、离散频点
 修改历史  :
  1.日  期   : 2015年8月28日
    作  者   : s00184266
    修改内容 : 新生成结构

*****************************************************************************/
typedef struct
{
    NVIM_GAS_PLMN_ID_STRU                       stPlmn;                         /* PLMN结构 */
    VOS_UINT8                                   ucRangeCnt;                     /* 频点范围的个数，最大个数:NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_RANGE_MAX_CNT */
    VOS_UINT8                                   ucDiscreteCnt;                  /* 离散频点的个数，最大个数:NVIM_GSM_OPERATE_CUSTOMIZE_DESCRETE_FREQ_MAX_CNT */
    VOS_UINT8                                   ucRsv1;                         /* 保留位 */
    VOS_UINT8                                   ucRsv2;                         /* 保留位 */
    NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_RANGE_STRU  astGsmOperateCustomFreqRange[NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_RANGE_MAX_CNT];
                                                                                /* 频点范围结构列表 */
    NVIM_GSM_OPERATE_CUSTOMIZE_DISCRETE_STRU    astGsmOperateCustomDiscrete[NVIM_GSM_OPERATE_CUSTOMIZE_DESCRETE_FREQ_MAX_CNT];
                                                                                /* 离散频点结构列表 */
    VOS_UINT8                                   ucRsv3;                         /* 保留位 */
    VOS_UINT8                                   ucRsv4;                         /* 保留位 */
    VOS_UINT16                                  usRsv1;                         /* 保留位 */
    VOS_UINT32                                  ulRsv1;                         /* 保留位 */
}NVIM_GSM_OPERATOR_CUSTOMIZE_PLMN_ITEM_STRU;

/*****************************************************************************
 结 构 名  : NVIM_GSM_OPERATOR_CUSTOMIZE_FREQ_CFG_STRU
 结构说明  : 运营商定制的GSM频点列表的NV结构
 修改历史  :
  1.日  期   : 2015年8月28日
    作  者   : s00184266
    修改内容 : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucPlmnCnt;                      /* 运营商定制的PLMN列表个数，最大个数:NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_PLMN_MAX_CNT */
    VOS_UINT8                                   ucRsv1;                         /* 保留位 */
    VOS_UINT8                                   ucRsv2;                         /* 保留位 */
    VOS_UINT8                                   ucRsv3;                         /* 保留位 */
    NVIM_GSM_OPERATOR_CUSTOMIZE_PLMN_ITEM_STRU  astGsmOperatorCustomPlmnItem[NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_PLMN_MAX_CNT];   
                                                                                /* 定制的PLMN列表 */
}NVIM_GSM_OPERATOR_CUSTOMIZE_FREQ_CFG_STRU;

/*****************************************************************************
 结构名    : NVIM_GSM_PARALLEL_SEARCH_CUSTOMIZE_CFG_STRU
 结构说明  : en_NV_Item_GSM_PARALLEL_SEARCH_CUSTOMIZE_CFG 结构，GSM并行搜网流程相关配置
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulWaitFirstUsableMask;          /* 用于指定等待第一小区的流程 */
    VOS_UINT16                          usWaitFirstTimerLen;            /* 等待第一小区定时器长度，单位:ms */

    VOS_INT16                           sSameLaiThreshold;              /* 优先选择同一个LAI频点的RSSI门限 */
    VOS_UINT32                          ulSameLaiUsableMask;            /* 用于指定优先选择同一个LAI的流程 */
    VOS_UINT16                          usSameLaiTimerLen;              /* 等待同一个LAI小区定时器长度，单位:ms */
    VOS_UINT8                           ucStoreSameLaiFlag;             /* 历史频点阶段是否优先选择同一个LAI频点 */
    VOS_UINT8                           ucFullSameLaiFlag;              /* 全频段阶段是否优先选择同一个LAI频点 */

    VOS_UINT32                          ulWithSiUsableMask;             /* 用于指定优先选择带系统消息的流程 */
    VOS_UINT8                           ucStoreWithSiFlag;              /* 历史频点阶段是否优先选择带系统消息频点 */
    VOS_UINT8                           ucFullWithSiFlag;               /* 全频段阶段是否优先选择带系统消息频点 */
    VOS_INT16                           sWithSiThreshold;               /* 优先选择带系统消息频点的RSSI门限 */

    VOS_UINT8                           ucRmvUtranImpactFlg;            /* 扫频结果中是否删除Utran干扰频点 */
    VOS_UINT8                           ucRmvPseudoNCell;               /* 扫频结果中是否删除邻频干扰频点 */
    VOS_UINT8                           ucAutoAnycellCamp;              /* 指定搜SUITABLE驻留失败后是否主动尝试ANYCELL驻留 */
    VOS_UINT8                           ucMaxArfcnNum;                  /* 并行搜搜索最大频点个数 */

    VOS_UINT8                           ucFirstTcIgnoreSi2Q;            /* 第一个TC周期前是否忽略SI2Quater */
    VOS_UINT8                           ucRsv4;                         /* 保留位 */
    VOS_UINT8                           ucRsv5;                         /* 保留位 */
    VOS_UINT8                           ucRsv6;                         /* 保留位 */

    VOS_UINT16                          usRsv1;                         /* 保留位 */
    VOS_UINT16                          usRsv2;                         /* 保留位 */
    VOS_UINT16                          usRsv3;                         /* 保留位 */
    VOS_UINT16                          usRsv4;                         /* 保留位 */

    VOS_INT16                           sRsv1;                          /* 保留位 */
    VOS_INT16                           sRsv2;                          /* 保留位 */
    VOS_INT16                           sRsv3;                          /* 保留位 */
    VOS_INT16                           sRsv4;                          /* 保留位 */

    VOS_UINT32                          ulRsv1;                         /* 保留位 */
    VOS_UINT32                          ulRsv2;                         /* 保留位 */
    VOS_UINT32                          ulRsv3;                         /* 保留位 */
    VOS_UINT32                          ulRsv4;                         /* 保留位 */

}NVIM_GSM_PARALLEL_SEARCH_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
 结 构 名  : NVIM_GSM_ENABLE_HISTORY_ARFCN_WITH_SPEC_ARFCN_LST_STRU
 结构说明  : en_NV_Item_GSM_ENABLE_HISTORY_ARFCN_WITH_SPEC_ARFCN_LST NV结构
             L2G 重定向过程中,搜索网络指定频点时使用历史频点的相关配置
 修改历史  :
  1.日  期   : 2015-10-16
    作  者   : p00166345
    修改内容 : 新生成结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCsfbEnableFlg;
    VOS_UINT8                           ucRedirEnableFlg;
    VOS_INT8                            cSpecArfcnPreferThreshold;
    VOS_UINT8                           ucHistoryArfcnRssiReduceValue;
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
}NVIM_GSM_ENABLE_HISTORY_ARFCN_WITH_SPEC_ARFCN_LST_STRU;

/*****************************************************************************
 结构名    : NVIM_GAS_RR_CONNECT_FAIL_PUNISH_CFG_STRU
 结构说明  : RR建链失败惩罚的开关以及门限配置
 修改历史  :
  1.日  期   : 2015年10月21日
    作  者   : w00146666
    修改内容 : 新生成结构
  2.日  期   : 2015年12月4日
    作  者   : w00146666
    修改内容 : for DTS2015112600361, 增加信号强度变化老化和时间老化机制
*****************************************************************************/
typedef struct
{
    /* ===============惩罚机制总体相关的NV配置项===================== */
    VOS_UINT8           ucCsAccFailPunishSwitchFlag;        /* 是否开启CS随机接入失败惩罚机制，0: 关闭, 1: 开启，默认值为1 */

    VOS_UINT8           ucPsAccFailPunishSwitchFlag;        /* 是否开启PS随机接入失败惩罚机制，0: 关闭, 1: 开启，默认值为0 */

    VOS_UINT8           ucRrConnFailOptimizeSwtichFlag;     /* 是否开启接入失败优化机制开关，
                                                               0: 关闭, 1: 开启，默认值为1
                                                               打开该NV项后，
                                                               1.
                                                               随机接入失败一次后该小区为FORBIND优先级小区，
                                                               随机接入失败超过一定次数启动惩罚机制，惩罚周期内将认为该小区被BAR；惩罚时间超时则认为是低优先级小区；

                                                               2.
                                                               N200失败次数达到一定次数(NV可配置)，执行被动重选；
                                                               N200失败达到一定次数(NV可配置), 启动惩罚机制，惩罚周期内将认为该小区被BAR；惩罚时间超时则认为是低优先级小区；

                                                               3.
                                                               重新随机接入成功，如果该小区是因为随机接入失败加入列表，从列表中删除该小区；
                                                               重新层二建链成功，如果该小区是因为N200失败加入列表，从列表中删除该小区；                                                               

                                                               关闭该NV项，则FORBIND优先级没有迭代惩罚策略；也没有N200惩罚机制
                                                               随机接入失败一次后该小区为FORBIND优先级小区，超过3次不能驻留；
                                                               */

    /* ===============随机接入失败相关的NV配置项===================== */
    VOS_UINT8           ucStartPunishRaFailTimesThreshold;     /* 在该GSM小区上随机接入失败次数门限, 达到该次数对该小区启动惩罚机制 */

    VOS_UINT8           ucRssiOffset;                         /* 历史信号强度低于门限，小区信号强度增加门限达到该门限将该小区从Bar列表中删除 */


    /* ===============N200相关的NV配置项============================== */
    VOS_UINT8           ucN200FailPunishSwitchFlag;             /* 是否开启N200失败惩罚机制，0: 关闭, 1: 开启，默认值为1 */

    VOS_UINT8           ucStartReselN200FailTimesThreshold;     /* 在该GSM小区上N200失败次数门限, 达到该次数对启动被动重选 */

    VOS_UINT8           ucStartPunishN200FailTimesThreshold;    /* 在该GSM小区上N200失败次数门限, 达到该次数对该小区启动惩罚机制 */
    
    VOS_INT16           sN200FailRssiThreshold;                 /* 在该GSM小区上N200失败RSSI门限，单位:dBm  */

    /* ===============惩罚时间相关的NV配置项============================== */
    VOS_UINT16          usInitialForbidTimeLen;                /* 建链失败第一次的惩罚时间，单位:秒 */

    VOS_UINT16          usMaxForbidTimeLen;                    /* 建链失败的小区的最大惩罚时长，单位:秒 */

    VOS_INT16           sRssiHighThresh;                      /* 单位:dBm, 加入惩罚列表的小区如果信号强度超过该值，该小区从惩罚列表中移除将不考虑信号强度变化 */

    VOS_UINT32          ulForbidCellMaxReServeTimeLen;        /* Forbid小区在惩罚列表中的最大保留时长，单位:分 */
    
    VOS_UINT32          ulRsv4;                              /* 保留位 */
    VOS_UINT32          ulRsv5;                              /* 保留位 */
    VOS_UINT32          ulRsv6;                              /* 保留位 */
    VOS_UINT32          ulRsv7;                              /* 保留位 */

}NVIM_GAS_RR_CONNECT_FAIL_PUNISH_CFG_STRU;


/*****************************************************************************
 结构名    : NVIM_GSM_PING_PONG_HO_CUSTOMIZE_CFG_STRU
 结构说明  : en_NV_Item_GSM_PING_PONG_HO_CUSTOMIZE_CFG 结构,GSM 乒乓切换定制特性相关配置
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSwitchFlag;                   /* 特性开关 */
    VOS_UINT8                           ucHoTimeThreshold;              /* 统计范围内的小区平均驻留时间门限, 初步推荐30s */
    VOS_UINT8                           ucBadCellTimeScale;             /* 坏小区平均时间评估因子, 单位: 0.1, 初步推荐 20 */
    VOS_UINT8                           ucGoodQualityThreshold;         /* 信号质量好判定门限.误码率. 单位: 千分之一, 初步推荐值为5 */
    VOS_UINT8                           ucGoodQualityCntThreshold;      /* 信号质量好的统计次数门限, 初步推荐值 3 */
    VOS_UINT8                           ucNCellRptReduceValue;          /* 优化生效时,邻区上报调整量, 单位 dB, 初步推荐值为20 */
    VOS_UINT8                           ucWatchHoTimes;                 /* 切换次数, 初步推荐值为 4 */
    VOS_UINT8                           aucRsv1;                        /* 保留位 */
    VOS_UINT16                          ausRsv1;
    VOS_UINT16                          ausRsv2;
    VOS_UINT8                           aucRsv3;
    VOS_UINT8                           aucRsv4;
    VOS_UINT8                           aucRsv5;
    VOS_UINT8                           aucRsv6;
}NVIM_GSM_PING_PONG_HO_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
 结 构 名  : NVIM_GSM_LTE_MEASURE_CFG_STRU
 结构说明  : GSM测量LTE配置NV
 修改历史  :
  1.日  期   : 2015年12月7日
    作  者   : s00184266
    修改内容 : dts2015100803984,新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDistLteAcsTypeEnable;         /* 使能区分LTE制式进行测量的开关 */
    VOS_UINT8                           aucRsv1;                        /* 保留位 */
    VOS_UINT8                           aucRsv2;
    VOS_UINT8                           aucRsv3;
    VOS_UINT16                          ausRsv1;
    VOS_UINT16                          ausRsv2;
}NVIM_GSM_LTE_MEASURE_CFG_STRU;

/*****************************************************************************
 结构名    : NVIM_GSM_SEC_RXQUAL_SUB_ALPHA_FILTERING_CFG_STRU
 结构说明  : en_NV_Item_GSM_SEC_RXQUAL_SUB_ALPHA_FILTERING_CFG 结构,对GSM SUB集的误码率进行ALPHA滤波, 以判断服务小区是否可以继续驻留的相关配置
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSecRrPoorRxQualSubThresHold;  /* 信号质量误码率判定门限, 精度:千分之一, 有效值为0~1000, 推荐值: 80, 即误码率为8% */
    VOS_UINT16                          usSecRxQualSubAlpha;            /* Alpha因子, 精度:千分之一, 有效值为0~1000, 推荐值: 250, 即Alpha为0.25 */
    VOS_UINT16                          usSecConSubBerCntThresHold;     /* 连续usSecConSubBerCntThresHold个数样点大于阈值, 再开启Poor机制, 推荐值: 2, 即连续三次 */
    VOS_UINT8                           ucRsv1;                         /* 保留位 */
    VOS_UINT8                           ucRsv2;
    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usRsv2;
}NVIM_GSM_SEC_RXQUAL_SUB_ALPHA_FILTERING_CFG_STRU;

#if defined( __PS_WIN32_RECUR__ ) || defined (DMT)
/*****************************************************************************
 结 构 名  : NVIM_GAS_CHR_PC_CFG_STRU
 结构说明  : 
 修改历史  :
  1.日  期   : 2015年12月28日
    作  者   : w00146666
    修改内容 : 新生成结构
*****************************************************************************/
typedef struct  
{
    VOS_UINT32  ulPermitedChrAlarmIdCount;

    VOS_UINT16  aucAlarmIds[MAX_CHR_ALARM_ID_NUM];
    
}NVIM_GAS_CHR_PC_CFG_STRU;
#endif

/*****************************************************************************
 结构名    : NVIM_Item_GAS_SAME_LAI_PREFER_CFG_STRU
 结构说明  : en_NV_Item_GAS_SAME_LAI_PREFER_CFG 结构, 搜网过程中优先选择相同 LAI 小区
             的相关配置.
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMtSwitchFlag;                 /* 特性开关 */
    VOS_UINT8                           ucMoSwitchFlag;                 /* 特性开关 */

    VOS_INT8                            cFirstLevelAddValue;           /* 第一能量等级中相同 LAI 小区排序时的能量增加值 */
    VOS_INT8                            cFirstLevelThreshold;          /* 第一能量等级门限 */

    VOS_INT8                            cSecLevelAddValue;             /* 第二能量等级中相同 LAI 小区排序时的能量增加值 */
    VOS_INT8                            cSecLevelThreshold;            /* 第二能量等级门限 */
    VOS_UINT16                          usValidTimeLen;                 /* 有效时长, 单位:分钟 */
    VOS_UINT8                           aucRsv1;                        /* 保留位 */
	VOS_UINT8                           aucRsv2;                        /* 保留位 */
    VOS_UINT8                           aucRsv3;                        /* 保留位 */
    VOS_UINT8                           aucRsv4;                        /* 保留位 */
}NVIM_Item_GAS_SAME_LAI_PREFER_CFG_STRU;

/*****************************************************************************
 结构名    : NVIM_GSM_HO_CUSTOMIZE_CFG_STRU
 结构说明  : en_NV_Item_GSM_HO_CUSTOMIZE_CFG 结构,GSM 切换定制特性相关配置
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucChanModeRptIndication;        /* 语音信道切换切换过程,中给 MM 上报 GAS_RR_CHAN_IND 的时机 */
    VOS_UINT8                           aucRsv1;
    VOS_UINT16                          ausRsv1;
    VOS_UINT8                           aucRsv2;
    VOS_UINT8                           aucRsv3;
    VOS_UINT8                           aucRsv4;
    VOS_UINT8                           aucRsv5;
}NVIM_GSM_HO_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
 结构名    : NVIM_GSM_PMR_CFG_STRU
 结构说明  : en_NV_Item_GSM_PMR_CFG 结构,GSM PMR相关定制
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNcReportPeriodIMin;           /* 空闲态 PMR 周期最小值 */
    VOS_UINT8                           aucRsv1;
    VOS_UINT16                          ausRsv1;
    VOS_UINT8                           aucRsv2;
    VOS_UINT8                           aucRsv3;
    VOS_UINT8                           aucRsv4;
    VOS_UINT8                           aucRsv5;
}NVIM_GSM_PMR_CFG_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/










#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasNvInterface.h */
