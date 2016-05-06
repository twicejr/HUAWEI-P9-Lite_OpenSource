/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : LNvCommon.h
  Description     : LNvCommon.h header file
  History           :
     1.Name+ID      yyyy-mm-dd  Draft Enact

******************************************************************************/

#ifndef __LNVCOMMON_H__
#define __LNVCOMMON_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
/* this file is included by drv, submit by zhouluojun, reviewed by hujianbo */
/* #pragma pack(4) */

/*****************************************************************************
  2 macro
*****************************************************************************/

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
    PS NV值使用范围：0xD200 ~ 0xD38F
*****************************************************************************/
enum NV_ITEM_ID_ENUM
{
    EN_NV_ID_BEGIN                                  = 0,
    EN_NV_ID_PS_BEGIN                               = 0xD200,/*Modem begin D000*/
    EN_NV_ID_LTEAPT_TOTAL_FLG                       = 0xD201,
    EN_NV_ID_IMS_SIP_CONFIG                         = 0xD202,
    EN_NV_ID_IMS_CONFIG                             = 0xD203,
    EN_NV_ID_UE_NET_CAPABILITY                      = 0xD204,
    EN_NV_ID_UE_CENTER                              = 0xD205,
    EN_NV_ID_NAS_RELEASE                            = 0xD206,
    EN_NV_ID_IMS_RAT_SUPPORT                        = 0xD207,
    EN_NV_ID_SEC_CONTEXT                            = 0xD208,
    EN_NV_ID_IMSA_CONFIG                            = 0xD209,
    EN_NV_ID_EPS_LOC                                = 0xD20a,
    EN_NV_ID_IMS_CAPABILITY                         = 0xD20b,
    EN_NV_ID_SIP_PORT_CONFIG                        = 0xD20c,
    EN_NV_ID_IMSI                                   = 0xD20d,
    EN_NV_ID_UE_VOICE_DOMAIN                        = 0xD20e,
    EN_NV_ID_IMS_VOIP_CONFIG                        = 0xD20f,
    EN_NV_ID_IMS_CODE_CONFIG                        = 0xD210,
    EN_NV_ID_IMS_SS_CONF_CONFIG                     = 0xD211,
    EN_NV_ID_ATTACH_BEARER_RE_ESTABLISH             = 0xD212,
    EN_NV_ID_IMS_SECURITY_CONFIG                    = 0xD213,
    EN_NV_ID_IMS_MEDIA_PARM_CONFIG                  = 0xD214,
    EN_NV_ID_PS_LOCALIP_CAP                         = 0xD215,
    EN_NV_ID_PS_COMM_BAND_CONFIG                    = 0xD216,
    EN_NV_ID_PS_RAT_RSSI_THRESHOLD                  = 0xD217,
    EN_NV_ID_LPP_PARA_CONFIG                        = 0xD218,
    EN_NV_ID_LNAS_SWITCH_PARA                       = 0xD219,
    EN_NV_ID_CONFIG_NWCAUSE                         = 0xD21a,
    EN_NV_ID_DAM_CONFIG_PARA                        = 0xD21b,
    EN_NV_ID_LNAS_COMM_CONFIG_PARA                  = 0xD21c,
    EN_NV_ID_PCSCF_DISCOVERY_POLICY                 = 0xD21d,
    EN_NV_ID_BACKOFF_ALG_CONFIG                     = 0xD21e,
    EN_NV_ID_LCS_COMMON_CONFIG                      = 0xD21f,
    EN_NV_ID_CELL_MEAS_THREDHOLD                    = 0xD220,
    EN_NV_ID_GET_SIB_THRESHOLD                      = 0xD221,
    EN_NV_ID_UE_CAP_V9a0                            = 0xD222,/* R10 NV修改 begin */
    EN_NV_ID_UE_CAP_V1020                           = 0xD223,
    EN_NV_ID_UE_CAP_V1060                           = 0xD224,
    EN_NV_ID_UE_CAP_RF_PARA_V1060                   = 0xD225,/* R10 NV修改 end */
    EN_NV_ID_IRAT_REDIR_SWITCH                      = 0xD226,
    EN_NV_ID_LTE_SPAC_BAND_INFO                     = 0xD227,
    EN_NV_ID_LTE_ABANDON_BAND_INFO                  = 0xD228,
    EN_NV_ID_LTE_MTC_NOTCH_FEATURE_INFO             = 0xD229,
    EN_NV_ID_LTE_CUSTOM_MCC_INFO                    = 0xD22a,/*Delete FDD Band */
    EN_NV_ID_RRC_THRESHOLD                          = 0XD22b,/* adapt filter begin */
    EN_NV_ID_UE_CAPABILITY                          = 0xD22c,
    EN_NV_ID_SUPPORT_FREQ_BAND                      = 0xD22d,
    NV_ID_RRC_NV_CALIBRATION_BAND_LIST              = 0xD22e,
    EN_NV_ID_SUPPORT_SUPPORT_RESEL                  = 0xD22f,
    EN_NV_ID_UE_MAX_TX_POWER                        = 0xD230,
    EN_NV_ID_CGI_INFO                               = 0xD231,
    EN_NV_ID_RRC_LOCK_FREQ_SWITCH                   = 0xD232,
    EN_NV_ID_RRC_RESELECT_3DB_SWITCH                = 0xD233,
    EN_NV_ID_UE_RFRD_TYPE                           = 0xD234,
    EN_NV_ID_LTE_IRAT_TDS_CAPABILITY_INFO           = 0xD235,
    EN_NV_ID_UE_EXTBAND_INFO                        = 0xD236,/*BEGIN DTS2014041603793 c00203521 modify for B28全频段特性*/
    EN_NV_ID_EXTBAND_INFO_WITH_BANDWIDTH		    = 0xD237,/*END DTS2014041603793 c00203521 modify for B28全频段特性*/
    EN_NV_ID_DSDS_CFG_INFO                          = 0xD238,
    EN_NV_ID_FIX_MUTI_PLMNS_CAND_INFO               = 0xD239,
    EN_NV_ID_DYN_MUTI_PLMNS_CAND_INFO               = 0xD23A,
    EN_NV_ID_LATEST_CAND_FREQ_WITHPLMN_INFO         = 0xD23B,
    EN_NV_ID_IDC_PARA                               = 0xD23c,
    EN_NV_ID_OTDOA_ADDITIONAL_NCELL_PARA            = 0xD23d,
    EN_NV_ID_LRRC_NV_CELL_SELECT_CTRL               = 0xD23E,
    EN_NV_ID_LRRC_NV_INTER_OPT_CTRL                 = 0xD23F,
    EN_NV_ID_LRRC_ONLY_DL_BAND_CTRL                 = 0xD241,
    EN_NV_ID_RF_HW                                  = 0xD242,
    EN_NV_ID_L2_LUP_MEM_CTRL                        = 0xD243,
    EN_NV_ID_PS_CLOUD_FREQ_STRATEGY                 = 0xD244,
    EN_NV_ID_PS_CLOUD_PREFER_FREQ_MCC1              = 0xD245,
    EN_NV_ID_PS_CLOUD_PREFER_FREQ_MCC2              = 0xD246,
    EN_NV_ID_PS_CLOUD_PREFER_FREQ_MCC3              = 0xD247,
    EN_NV_ID_GUTL_COMM_RESEL_THRES_CFG              = 0xD248,
    EN_NV_ID_USIM_BEGIN                             = 0xD250,
    EN_NV_ID_VOLTE_CARD_LOCK                        = 0xD251,
    EN_NV_ID_MNC_LEN_FILE                           = 0xD252,
    EN_NV_ID_IMSA_COMM_PARA_CONFIG                  = 0xD253,
    EN_NV_ID_IMS_PARM_UE_CAPABILITY                 = 0xD254,
    EN_NV_ID_OPLMN_SEL_FILE                         = 0xD255,
    EN_NV_ID_HPLMN_PERI_FILE                        = 0xD256,
    EN_NV_ID_SEC_CONTEXT_FILE                       = 0xD257,
    EN_NV_ID_CS_LOC_FILE                            = 0xD258,
    EN_NV_ID_PS_LOC_FILE                            = 0xD259,
    EN_NV_ID_EPS_LOC_FILE                           = 0xD25a,
    EN_NV_ID_IMSI_FILE                              = 0xD25b,
    EN_NV_ID_CS_CKIK_FILE                           = 0xD25c,
    EN_NV_ID_PS_KEY_FILE                            = 0xD25d,
    EN_NV_ID_KC_FILE                                = 0xD25e,
    EN_NV_ID_UE_NAS_SECURITY_ALGORITHMS             = 0xD25f,
    EN_NV_ID_USIM_VISION                            = 0xD260,
    EN_NV_ID_ACC_CLASSMASK_FILE                     = 0xD261,
    EN_NV_ID_HPLMN_ACT_FILE                         = 0xD262,/* 未使用 */
    EN_NV_ID_SEQ_INFO                               = 0xD263,
    EN_NV_ID_LRPLMNSI_FILE                          = 0xD264,
    EN_NV_ID_USIM_END                               = 0xD269,
    EN_NV_ID_CAND_CELL                              = 0xD26a,
    EN_NV_CSQ_RPT_INFO                              = 0xD26b,
    EN_NV_ID_TPS_SWITCH_PARA                        = 0xD26c,
    EN_NV_ID_SWITCH_PARA                            = 0xD275,
    EN_NV_ID_LTE_CONFIG                             = 0xD276,
    EN_NV_ID_LTE_GATE_WAY_IP                        = 0xD277,
    EN_NV_ID_SIB_SUPPORT                            = 0xD280,
    EN_NV_ID_GATE_CLOCK_SWITCH_CONFIG               = 0xD281,
    EN_NV_ID_POWER_CONFIG                           = 0xD282,
    EN_NV_ID_LTE_COMP_SWITCH                        = 0xD283,
    EN_NV_ID_UE_CAP_MEAS_PARA_BAND7                 = 0xD284,
    EN_NV_ID_UE_CAP_MEAS_PARA_BAND20                = 0xD285,
    EN_NV_ID_UE_CAP_MEAS_PARA_BAND38                = 0xD286,
    EN_NV_ID_UE_CAP_MEAS_PARA_BAND40                = 0xD287,
    EN_NV_ID_UE_CAP_MEAS_PARA_BAND41                = 0xD288,
    EN_NV_ID_BAND1_CAND_INFO                        = 0xD2a0,/* mul Band */
    EN_NV_ID_BAND2_CAND_INFO                        = 0xD2a1,
    /*EN_NV_ID_BAND3_CAND_INFO                      = 0xD2a2,*/
    EN_NV_ID_BAND4_CAND_INFO                        = 0xD2a3,
    EN_NV_ID_BAND5_CAND_INFO                        = 0xD2a4,
    EN_NV_ID_BAND6_CAND_INFO                        = 0xD2a5,
    /*EN_NV_ID_BAND7_CAND_INFO                      = 0xD2a6,*/
    EN_NV_ID_BAND8_CAND_INFO                        = 0xD2a7,
    EN_NV_ID_BAND9_CAND_INFO                        = 0xD2a8,
    EN_NV_ID_BAND10_CAND_INFO                       = 0xD2a9,
    EN_NV_ID_BAND11_CAND_INFO                       = 0xD2aa,
    EN_NV_ID_BAND12_CAND_INFO                       = 0xD2ab,
    EN_NV_ID_BAND13_CAND_INFO                       = 0xD2ac,
    EN_NV_ID_BAND14_CAND_INFO                       = 0xD2ad,
    EN_NV_ID_BAND15_CAND_INFO                       = 0xD2ae,
    EN_NV_ID_BAND16_CAND_INFO                       = 0xD2af,
    EN_NV_ID_BAND17_CAND_INFO                       = 0xD2b0,
    EN_NV_ID_BAND18_CAND_INFO                       = 0xD2b1,
    EN_NV_ID_BAND19_CAND_INFO                       = 0xD2b2,
    /*EN_NV_ID_BAND20_CAND_INFO                     = 0xD2b3,*/
    EN_NV_ID_BAND21_CAND_INFO                       = 0xD2b4,
    EN_NV_ID_BAND22_CAND_INFO                       = 0xD2b5,
    EN_NV_ID_BAND23_CAND_INFO                       = 0xD2b6,
    EN_NV_ID_BAND24_CAND_INFO                       = 0xD2b7,
    EN_NV_ID_BAND25_CAND_INFO                       = 0xD2b8,
    EN_NV_ID_BAND26_CAND_INFO                       = 0xD2b9,
    EN_NV_ID_BAND27_CAND_INFO                       = 0xD2ba,
    EN_NV_ID_BAND28_CAND_INFO                       = 0xD2bb,
    EN_NV_ID_BAND29_CAND_INFO                       = 0xD2bc,
    EN_NV_ID_BAND30_CAND_INFO                       = 0xD2bd,
    EN_NV_ID_BAND31_CAND_INFO                       = 0xD2be,
    EN_NV_ID_BAND32_CAND_INFO                       = 0xD2bf,
    EN_NV_ID_BAND33_CAND_INFO                       = 0xD2c0,
    EN_NV_ID_BAND34_CAND_INFO                       = 0xD2c1,
    EN_NV_ID_BAND35_CAND_INFO                       = 0xD2c2,
    EN_NV_ID_BAND36_CAND_INFO                       = 0xD2c3,
    EN_NV_ID_BAND37_CAND_INFO                       = 0xD2c4,
    /*EN_NV_ID_BAND38_CAND_INFO                     = 0xD2c5,*/
    /*EN_NV_ID_BAND39_CAND_INFO                     = 0xD2c6,*/
    /*EN_NV_ID_BAND40_CAND_INFO                     = 0xD2c7,*/
    /*EN_NV_ID_BAND41_CAND_INFO                     = 0xD2c8,*/
    EN_NV_LWCLASH_RANGE_INFO                        = 0xD2c8,
    EN_NV_ID_BAND42_CAND_INFO                       = 0xD2c9,
    EN_NV_ID_BAND43_CAND_INFO                       = 0xD2ca,
    EN_NV_ID_BAND3_CAND_INFO                        = 0xD2d1,
    EN_NV_ID_BAND7_CAND_INFO                        = 0xD2d2,
    EN_NV_ID_BAND20_CAND_INFO                       = 0xD2d3,
    EN_NV_ID_BAND38_CAND_INFO                       = 0xD2d4,
    EN_NV_ID_BAND39_CAND_INFO                       = 0xD2d5,
    EN_NV_ID_BAND40_CAND_INFO                       = 0xD2d6,
    EN_NV_ID_BAND41_CAND_INFO                       = 0xD2d7,
    EN_NV_ID_BAND64_CAND_INFO                       = 0xD2d8,
    EN_NV_ID_FLOWCTRL_CONFIG                        = 0xD2d9,
    EN_NV_ID_BANDXX_CAND_INFO                       = 0xD2da,/* gaojishan-nv-bands-cfg-begin */
    EN_NV_ID_BANDNon2_CAND_INFO                     = 0xD2DB,/* 非标频段的候补信息begin */
    EN_NV_ID_BANDNon3_CAND_INFO                     = 0xD2DC,
    EN_NV_ID_BANDNon4_CAND_INFO                     = 0xD2DD,
    EN_NV_ID_BANDNon5_CAND_INFO                     = 0xD2DE,
    EN_NV_ID_BANDNon6_CAND_INFO                     = 0xD2DF,
    EN_NV_ID_BANDNon7_CAND_INFO                     = 0xD2E0,
    EN_NV_ID_BANDNon8_CAND_INFO                     = 0xD2E1,
    EN_NV_ID_BANDNon9_CAND_INFO                     = 0xD2E2,
    EN_NV_ID_BANDNon10_CAND_INFO                    = 0xD2E3,
    EN_NV_ID_BANDNon11_CAND_INFO                    = 0xD2E4,
    EN_NV_ID_BANDNon12_CAND_INFO                    = 0xD2E5,
    EN_NV_ID_BANDNon13_CAND_INFO                    = 0xD2E6,
    EN_NV_ID_BANDNon14_CAND_INFO                    = 0xD2E7,
    EN_NV_ID_BANDNon15_CAND_INFO                    = 0xD2E8,
    EN_NV_ID_BANDNon16_CAND_INFO                    = 0xD2E9,
    EN_NV_ID_BANDNon1_CAND_INFO                     = 0xD2EA,/* 非标频段的候补信息end */
    EN_NV_ID_BANDNon1_BAND_INFO                     = 0xD2ED,/* 非标频段的频段信息begin */
    EN_NV_ID_BANDNon2_BAND_INFO                     = 0xD2EE,
    EN_NV_ID_BANDNon3_BAND_INFO                     = 0xD2EF,
    EN_NV_ID_BANDNon4_BAND_INFO                     = 0xD2F0,
    EN_NV_ID_BANDNon5_BAND_INFO                     = 0xD2F1,
    EN_NV_ID_BANDNon6_BAND_INFO                     = 0xD2F2,
    EN_NV_ID_BANDNon7_BAND_INFO                     = 0xD2F3,
    EN_NV_ID_BANDNon8_BAND_INFO                     = 0xD2F4,
    EN_NV_ID_BANDNon9_BAND_INFO                     = 0xD2F5,
    EN_NV_ID_BANDNon10_BAND_INFO                    = 0xD2F6,
    EN_NV_ID_BANDNon11_BAND_INFO                    = 0xD2F7,
    EN_NV_ID_BANDNon12_BAND_INFO                    = 0xD2F8,
    EN_NV_ID_BANDNon13_BAND_INFO                    = 0xD2F9,
    EN_NV_ID_BANDNon14_BAND_INFO                    = 0xD2FA,
    EN_NV_ID_BANDNon15_BAND_INFO                    = 0xD2FB,
    EN_NV_ID_BANDNon16_BAND_INFO                    = 0xD2FC,/* 非标频段的频段信息end */
    EN_NV_ID_FLOWCTRL_LIMIT_CONFIG                  = 0xD2FD,
    EN_NV_ID_TDS_FREQ_CELL_LOCK_SWITCH              = 0xD2FE,
    EN_NV_ID_PS_END                                 = 0xD2ff,
    EN_NV_ID_TDS_UTRANCAPABILITY                    = 0xD300,
    EN_NV_ID_TDS_CERSSI_REPROT_PARA                 = 0xD301,
    EN_NV_ID_TDS_MAC_HSPA_CTRPARA                   = 0xD302,
    EN_NV_ID_TDS_RRC_LOCK_FREQ_SWITCH               = 0xD303,
    EN_NV_ID_TDS_SUPPORT_FREQ_BAND                  = 0xD304,
    EN_NV_ID_TDS_FLOWCTRPARA                        = 0xD305,
    EN_NV_ID_TDS_ENG_NULLTIMER_CONTROL_TESTFLAG_EQPOUT = 0xD306,
    EN_NV_ID_TDS_NET_SELECT_MODE                    = 0xD307,
    EN_NV_ID_TDS_PLMN_SELECT_MODE                   = 0xD308,
    EN_NV_ID_TDS_POWER_ON_ATTACH_MODE               = 0xD309,
    EN_NV_ID_TDS_MOBILESTATION_CLASS                = 0xD30a,
    EN_NV_ID_TDS_UTRAN_CFG_DSP                      = 0xD30b,
    EN_NV_ID_TDS_BA_LIST                            = 0xD30c,/* TRRC CHANGE FOR BA begin */
    EN_NV_ID_TDS_CUSTOMIZE_CS_SERVICE               = 0xD30d,
    EN_NV_ID_CTRL_PARA                              = 0xD30e,/* gaojishan-fast-dorm-cfg-3 */
    EN_NV_ID_TDS_ALFA_FILTER                        = 0xD30f,/* filter the serve cell begin*/
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND1        = 0xD310,/* CA NV begin,d310~d32f,d350~d37f,d390~d3bf */
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND2        = 0xD311,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND3        = 0xD312,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND4        = 0xD313,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND5        = 0xD314,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND6        = 0xD315,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND7        = 0xD316,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND8        = 0xD317,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND9        = 0xD318,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND10       = 0xD319,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND11       = 0xD31a,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND12       = 0xD31b,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND13       = 0xD31c,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND14       = 0xD31d,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND15       = 0xD31e,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND16       = 0xD31f,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND17       = 0xD320,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND18       = 0xD321,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND19       = 0xD322,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND20       = 0xD323,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND21       = 0xD324,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND22       = 0xD325,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND23       = 0xD326,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND24       = 0xD327,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND25       = 0xD328,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND26       = 0xD329,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND27       = 0xD32a,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND28       = 0xD32b,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND29       = 0xD32c,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND30       = 0xD32d,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND31       = 0xD32e,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND32       = 0xD32f,/* CA NV end,d310~d32f,d350~d37f,d390~d3bf */
    EN_NV_ID_TDS_AREA_LOST_TIMER                    = 0xD330,
    EN_NV_ID_TDS_FEATHURE_PARA                      = 0xD331,
    EN_NV_ID_TDS_AREA_LOST_THSD                     = 0xD332,/* MTC AREA LOST Begin */
    EN_NV_ID_TDS_MTC_RESEL_PARA                     = 0xD333,/* MTC RESEL Begin */
    EN_NV_ID_TL_L2_PARA                             = 0xD334,
    EN_NV_ID_BSIC_FRAME_PARA                        = 0xD335,
    EN_NV_ID_TDS_MEAS_IMPROVE_PARA                  = 0xD336,
    EN_NV_ID_CELL_SEARCH_TIME                       = 0xD338,
    EN_NV_ID_CHR_ERROR_LOG_INFO                     = 0xD339,
    EN_NV_ID_UE_CAP_V1090                           = 0xD340,/* R11 NV修改 begin */
    EN_NV_ID_UE_CAP_V1130                           = 0xD341,
    EN_NV_ID_UE_CAP_V1170                           = 0xD342,
    EN_NV_ID_UE_CAP_V9c0                            = 0xD343,
    EN_NV_ID_UE_CAP_V9d0                            = 0xD344,
    EN_NV_ID_UE_CAP_V9e0                            = 0xD345,
    EN_NV_ID_UE_CAP_V9h0                            = 0xD346,
    EN_NV_ID_UE_CAP_V10c0                           = 0xD347,
    EN_NV_ID_UE_CAP_V1180                           = 0xD348,
    EN_NV_ID_UE_CAP_V11A0                           = 0xD349,
    EN_NV_ID_UE_CAP_V1250                           = 0xD34a,
    EN_NV_ID_UE_CAP_V10f0                           = 0xD34b,/* R11 NV修改 end */
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND33       = 0xD350,/* CA NV begin,d310~d32f,d350~d37f,d390~d3bf */
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND34       = 0xD351,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND35       = 0xD352,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND36       = 0xD353,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND37       = 0xD354,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND38       = 0xD355,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND39       = 0xD356,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND40       = 0xD357,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND41       = 0xD358,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND42       = 0xD359,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND43       = 0xD35a,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND44       = 0xD35b,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND45       = 0xD35c,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND46       = 0xD35d,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND47       = 0xD35e,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND48       = 0xD35f,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND49       = 0xD360,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND50       = 0xD361,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND51       = 0xD362,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND52       = 0xD363,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND53       = 0xD364,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND54       = 0xD365,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND55       = 0xD366,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND56       = 0xD367,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND57       = 0xD368,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND58       = 0xD369,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND59       = 0xD36a,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND60       = 0xD36b,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND61       = 0xD36c,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND62       = 0xD36d,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND63       = 0xD36e,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND64       = 0xD36f,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND65       = 0xD370,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND66       = 0xD371,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND67       = 0xD372,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND68       = 0xD373,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND69       = 0xD374,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND70       = 0xD375,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND71       = 0xD376,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND72       = 0xD377,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND73       = 0xD378,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND74       = 0xD379,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND75       = 0xD37a,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND76       = 0xD37b,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND77       = 0xD37c,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND78       = 0xD37d,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND79       = 0xD37e,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND80       = 0xD37f,/* CA NV end,d310~d32f,d350~d37f,d390~d3bf */
    EN_NV_ID_UE_CAP_MCC_CA_INFO_0                   = 0xD380,
    EN_NV_ID_UE_CAP_MCC_CA_INFO_1                   = 0xD381,
    EN_NV_ID_UE_CAP_MCC_CA_INFO_2                   = 0xD382,
    EN_NV_ID_UE_CAP_MCC_CA_INFO_3                   = 0xD383,
    EN_NV_ID_UE_CAP_MCC_CA_INFO_4                   = 0xD384,
    EN_NV_ID_UE_CAP_MCC_CA_INFO_5                   = 0xD385,
    EN_NV_ID_UE_CAP_MCC_CA_INFO_6                   = 0xD386,
    EN_NV_ID_BAND44_CAND_INFO                       = 0xD387,
    EN_NV_ID_UE_CAP_MCC_BAND_INFO                   = 0xD388,
    EN_NV_ID_SBM_CUSTOM_DUAL_IMSI                   = 0xD389,/* Begin: 2015/5/6 sbm */
    EN_NV_ID_ACC_FAIL_BAR_INFO                      = 0xD38c,/*begin accfail bar byhanlei*/
    EN_NV_ID_BG_LTE_LIMIT_THREHHOLD                 = 0xD38d,
    EN_NV_ID_BG_LTE_LIMIT_THREHHOLD_TYPE            = 0xD38e,
    EN_NV_ID_DPDT_SWITCH_PARA                       = 0xD38f,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND81       = 0xD390,/* CA NV begin,d310~d32f,d350~d37f,d390~d3bf */
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND82       = 0xD391,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND83       = 0xD392,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND84       = 0xD393,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND85       = 0xD394,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND86       = 0xD395,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND87       = 0xD396,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND88       = 0xD397,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND89       = 0xD398,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND90       = 0xD399,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND91       = 0xD39a,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND92       = 0xD39b,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND93       = 0xD39c,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND94       = 0xD39d,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND95       = 0xD39e,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND96       = 0xD39f,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND97       = 0xD3a0,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND98       = 0xD3a1,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND99       = 0xD3a2,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND100      = 0xD3a3,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND101      = 0xD3a4,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND102      = 0xD3a5,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND103      = 0xD3a6,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND104      = 0xD3a7,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND105      = 0xD3a8,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND106      = 0xD3a9,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND107      = 0xD3aa,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND108      = 0xD3ab,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND109      = 0xD3ac,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND110      = 0xD3ad,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND111      = 0xD3ae,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND112      = 0xD3af,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND113      = 0xD3b0,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND114      = 0xD3b1,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND115      = 0xD3b2,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND116      = 0xD3b3,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND117      = 0xD3b4,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND118      = 0xD3b5,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND119      = 0xD3b6,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND120      = 0xD3b7,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND121      = 0xD3b8,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND122      = 0xD3b9,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND123      = 0xD3ba,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND124      = 0xD3bb,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND125      = 0xD3bc,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND126      = 0xD3bd,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND127      = 0xD3be,
    EN_NV_ID_UE_CAP_V1020_RF_MEAS_PARA_BAND128      = 0xD3bf,/* CA NV end,d310~d32f,d350~d37f,d390~d3bf */
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM1          = 0xD5a0,/* 以下是DSP的NV范围，PSNV不够用，暂时借用之 */
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM2          = 0xD5a1,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM3          = 0xD5a2,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM4          = 0xD5a3,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM5          = 0xD5a4,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM6          = 0xD5a5,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM7          = 0xD5a6,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM8          = 0xD5a7,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM9          = 0xD5a8,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM10         = 0xD5a9,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM11         = 0xD5aa,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM12         = 0xD5ab,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM13         = 0xD5ac,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM14         = 0xD5ad,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM15         = 0xD5ae,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM16         = 0xD5af,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM17         = 0xD5b0,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM18         = 0xD5b1,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM19         = 0xD5b2,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM20         = 0xD5b3,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM21         = 0xD5b4,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM22         = 0xD5b5,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM23         = 0xD5b6,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM24         = 0xD5b7,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM25         = 0xD5b8,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM26         = 0xD5b9,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM27         = 0xD5ba,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM28         = 0xD5bb,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM29         = 0xD5bc,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM30         = 0xD5bd,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM31         = 0xD5be,
    EN_NV_ID_UE_CAP_V1180_BAND_COMB_PARAM32         = 0xD5bf,
    EN_NV_ID_CAMPED_CSG_CELL_INFO                   = 0xD5c0,
    EN_NV_ID_CAMPED_CSG_MACRO_NEIGH_CELL_INFO_PART1 = 0xD5c1,
    EN_NV_ID_CAMPED_CSG_MACRO_NEIGH_CELL_INFO_PART2 = 0xD5c2,
};
typedef unsigned long NV_ITEM_ID_ENUM_UINT32;

/*****************************************************************************
    PS NV值使用范围：0xD200 ~ 0xD38F
    0xD390 ~ 0xD3bf已用作CA
*****************************************************************************/


/* this file is included by drv, submit by zhouluojun, reviewed by hujianbo */
/*
#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif
*/



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of PsNvInterface.h */

