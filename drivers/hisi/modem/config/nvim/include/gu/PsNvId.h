/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : PsNvId.h
  版 本 号   :
  作    者   : 胡骏 59254
  生成日期   : 2009年5月14日
  最近修改   :
  功能描述   : 定义了协议栈NV项ID枚举定义
  函数列表   :
  修改历史   :
  1.日    期   : 2009年5月14日
    作    者   : 胡骏 59254
    修改内容   : 创建文件

******************************************************************************/

#ifndef __PSNVID_H__
#define __PSNVID_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "NvIddef.h"

/*typedef VOS_UINT16  PS_NV_ID_ENUM_U16;
 */

enum PS_NV_ID_ENUM
{

                 /* 快速开机 */
/*  0x1A00 */    en_NV_Item_FollowOn_OpenSpeed_Flag =GU_RF_BASE_NV_ID_MIN + 2559,
/* 6657  */      en_NV_Item_EF6F62,
/* 6658  */      en_NV_Item_EF6F7B,
/* 6659  */      en_NV_Item_EF6F60,
/* 6660  */      en_NV_Item_EF6F61,
/* 6661  */      en_NV_Item_EF6F31,
/* 6662  */      en_NV_Item_EF6FAD,
/* 6663  */      en_NV_Item_EF6F38,
/* 6664  */      en_NV_Item_EF6F7E,
/* 6665  */      en_NV_Item_EF6F73,
/* 6666  */      en_NV_Item_EF6F53,
/* 6667  */      en_NV_Item_EF6F07,
/* 6668  */      en_NV_Item_EF6F08,
/* 6669  */      en_NV_Item_EF6F09,
/* 6670  */      en_NV_Item_EF6F20,
/* 6671  */      en_NV_Item_EF6F52,
/* 6672  */      en_NV_Item_EF4F20,
/* 6673  */      en_NV_Item_EF4F52,
/* 6674  */      en_NV_Item_EF6FB7,
/* 6675  */      en_NV_Item_EF6F78,
/* 6676  */      en_NV_Item_EF6F5B,
/* 6677  */      en_NV_Item_EF6F5C,
/* 6678  */      en_NV_Item_EF6FC4,
/* 6679  */      en_NV_Item_EF6F74,


                 /* PS NV */
/* 8193  */      en_NV_Item_Ultra_Classmark = GU_PS_NV_ID_MIN,
/* 8194  */      en_NV_Item_Classmark1,
/* 8195  */      en_NV_Item_Classmark2,
/* 8196  */      en_NV_Item_Classmark3,
/* 8197  */      en_NV_Item_NetworkCapability,
/* 8198  */      en_NV_Item_RaCapability,
/* 8199  */      en_NV_Item_UMTS_Auth,
/* 8200  */      en_NV_Item_GmmInfo,
/* 8201  */      en_NV_Item_MMInfo,
/* 8202  */      en_NV_Item_Autoattach,
/* 8203  */      en_NV_Item_FMRID,
/* 8205  */      en_NV_Item_ProductName = 8205,
/* 8206  */      en_NV_Item_MMA_OperatorName,
/* 8207  */      en_NV_Item_Gas_MultiRateFlag,
/* 8208  */      en_NV_Item_Band_Pwr,
/* 8209  */      en_NV_Item_Vgcs_Flag,
/* 8210  */      en_NV_Item_Egprs_Multi_Slot_Class,
/* 8211  */      en_NV_Item_Gsm_Classmark1,
/* 8212  */      en_NV_Item_Gsm_Classmark2,
/* 8213  */      en_NV_Item_Gsm_Classmark3,
/* 8214  */      en_NV_Item_SelPlmn_Mode,
/* 8215  */      en_NV_Item_EquivalentPlmn,
/* 8216  */      en_NV_Item_Rplmn,

/* 8229  */      en_NV_Item_Support_Freqbands = 8229,
/* 8230  */      en_NV_Item_CCA_TelePara,
/* 8231  */      en_NV_Item_PS_TelePara,
/* 8232  */      en_NV_Item_MMA_AccessMode,
/* 8233  */      en_NV_Item_MMA_MsClass,
/* 8234  */      en_NV_Item_SMS_Content,
/* 8235  */      en_NV_Item_SMS_Status,
/* 8236  */      en_NV_Item_SMS_TEXT_Para,
/* 8237  */      en_NV_Item_SMS_SERVICE_Para,
/* 8238  */      en_NV_Item_SMS_EFSMSS_Para,
/* 8239  */      en_NV_Item_SMS_EFSMSP_Para,
/* 8240  */      en_NV_Item_CBS_Service_Para,
/* 8241  */      en_NV_Item_CBS_MID_List,         /*用于存储当前拒绝CBS消息ID列表*/
/* 8242  */      en_NV_Item_CBS_MID_Range_List,   /*用于存储当前拒绝CBS消息ID范围列表*/
/* 8243  */      en_NV_Item_Gsm_NFreq_Threshold,          /* GSM 邻频干扰过滤门限 */
/* 8244  */      en_NV_Item_Usim_PB_Ctrl_Info,
/* 8246  */      en_NV_Item_NetWorkPara = 8246,
/* 8248  */      en_NV_Item_Wcdma_Ind_Freq = 8248,
/* 8249  */      en_NV_Item_Gsm_Ind_Freq,
/* 8250  */      en_NV_Item_GCF_Type,
/* 8251  */      en_NV_Item_GCF_Item,
/* 8252  */      en_NV_Item_PHY_GCF_Item,
/* 8253  */      en_NV_Item_Sim_Personalisation_Pwd,
/* 8254  */      en_NV_Item_Sim_Personalisation_Imsi_Str,
/* 8255  */      en_NV_Item_Me_Personalisation_Active_Flag,
/* 8256  */      en_NV_Item_W_CellSrch_Meas_Para,
/* 8257  */      en_NV_Item_Usim_Debug_Mode_Set,
/* 8258  */      en_NV_Item_G2W_RSSI_RSCP_OFFSET,
/* 8259  */      en_NV_Item_W_RF8960_BER_Test,
/* 8261  */      en_NV_Item_TerminalProfile_Set = 8261,
/* 8262  */      en_NV_Item_RF_Auto_Test_Flag,
/* 8263  */      en_NV_Item_Meas_Threshold,
/* 8264  */      en_NV_Item_WAS_RadioAccess_Capa,
/* 8265  */      en_NV_Item_User_Set_Freqbands,
/* 8266  */      en_NV_Item_Roam_Capa,
/* 8270  */      en_NV_Item_CustomizeGprsRecentActivityTimer = 8270,
/* 8271  */      en_NV_Item_CustomizeService,
/* 8272  */      en_NV_Item_Ps_Delay_Flag,
/* 8273  */      en_NV_Item_GSM_Ba_Count,
/* 8274  */      en_NV_Item_GSM_Ba_List,
/* 8275  */      en_NV_Item_RPlmnWithRat,
/* 8276  */      en_NV_Item_HPlmnFirstTimer,
/* 8277  */      en_NV_Item_Egprs_Flag,
/* 8278  */      en_NV_Item_EgprsRaCapability,
/* 8279  */      en_NV_Item_Prefer_GSM_PLMN_Count,
/* 8280  */      en_NV_Item_Prefer_GSM_PLMN_List,
/* 8281  */      en_NV_Item_GSM_DEC_FAIL_ARFCN_Count,
/* 8282  */      en_NV_Item_GSM_DEC_FAIL_ARFCN_List,
/* 8283  */      en_NV_Item_Prefer_GSM_PLMN_Switch,
/* 8284  */      en_NV_Item_WCDMA_PLMN_FREQ_PAIR_List,
/* 8285  */      en_NV_Item_EFust_Service_Cfg,
/* 8288  */      en_NV_Item_NAS_Supported_3GPP_Release = 8288,
/* 8289  */      en_NV_Item_UE_MSCR_VERSION,
/* 8290  */      en_NV_Item_UE_SGSNR_VERSION,
/* 8291  */      en_NV_Item_GEA_SUPPORT_CTRL,
/* 8292  */      en_NV_Item_SteeringofRoaming_SUPPORT_CTRL,
/* 8293  */      en_NV_Item_SMS_MO_RETRY_PERIOD,
/* 8294  */      en_NV_Item_SMS_MO_RETRY_INTERVAL,
/* 8295  */      en_NV_Item_SMS_SEND_DOMAIN,
/* 8296  */      en_NV_Item_Display_Spn_Flag,
/* 8297  */      en_NV_Item_WINS_Config,
/* 8298  */      en_NV_Item_Geran_Feature_Package1,
/* 8299  */      en_NV_Item_Gsm_A5,
/* 8300  */      en_NV_Item_EHPlmn_Support_Flag,
/* 8301  */      en_NV_Item_NDIS_Authdata_0,
/* 8302  */      en_NV_Item_NDIS_Authdata_1,
/* 8303  */      en_NV_Item_NDIS_Authdata_2,
/* 8304  */      en_NV_Item_NDIS_Authdata_3,
/* 8305  */      en_NV_Item_NDIS_Authdata_4,
/* 8306  */      en_NV_Item_NDIS_Authdata_5,
/* 8307  */      en_NV_Item_NDIS_Authdata_6,
/* 8308  */      en_NV_Item_NDIS_Authdata_7,
/* 8309  */      en_NV_Item_NDIS_Authdata_8,
/* 8310  */      en_NV_Item_NDIS_Authdata_9,
/* 8311  */      en_NV_Item_NDIS_Authdata_10,
/* 8312  */      en_NV_Item_NDIS_Authdata_11,
/* 8313  */      en_NV_Item_LowCostEdge_Flag,

/* 8314 */       en_NV_Item_Opr_Freq_List,
/* 8315 */       en_NV_Item_BG_FS_FBS_Ratio,
/* 8316 */       en_NV_Item_BG_Threshold,
/* 8317 */       en_NV_Item_GPRS_ActiveTimerLength,

/* 8318 */       en_NV_Item_Stk_DualImsi_Ctrl,
/* 8319 */       en_NV_Item_RXDIV_CONFIG,
/* 8320 */       en_NV_Item_Max_Forb_Roam_La,
/* 8321 */       en_NV_Item_Default_Max_Hplmn_Srch_Peri,
/* 8322 */       en_NV_Item_SMS_ActiveMessage_Para,
/* 8323 */       en_NV_Item_BG_Search_Switch,
/* 8324 */       en_NV_Item_PDCP_LossLess_Switch = 8324,
/* 8325 */       en_NV_Item_Last_Imsi,
/* 8326 */       en_Nv_Item_Gprs_Multi_Slot_Class,
/* 8327 */       en_NV_Item_USSD_Apha_To_Ascii,
/* 8328 */       en_NV_Item_Roaming_Broker,
/* 8329 */       en_NV_Item_GSM_PLMN_SEARCH_ARFCN_MAX_NUM,
/* 8330 */       en_NV_Item_Stk_SmsInd_Ctrl = 8330,
/* 8331 */       en_NV_Item_LAPDM_RAND_BIT = 8331,
/* 8332  */      en_NV_Item_CBS_MID_Range_List_New = 8332,                     /*用于存储当前拒绝CBS消息ID范围列表*/
/* 8333 */       en_NV_Item_CBS_W_DRX_Switch           = 8333,
/* 8334 */       en_NV_Item_CBS_W_WaitNewCBSMsgTimer  = 8334,
/* 8335 */       en_NV_Item_CBS_W_WaitSchedMsgTimer   = 8335,
/* 8336 */       en_Nv_Item_GCBS_Conf = 8336,
/* 8337 */       en_NV_Item_Imei_Svn = 8337,
/* 8338 */       en_NV_Item_Register_Fail_Cnt = 8338,
/* 8340 */       en_NV_Item_REPORT_REG_ACT_FLG = 8340,
/* 8341 */       en_NV_Item_WAS_BROKEN_CELL_PARA = 8341,
/* 8342 */       en_NV_Item_Eplmn_Use_Rat_Flag = 8342,
/* 8343 */       en_NV_Item_Use_Single_Rplmn_When_Area_Lost = 8343,
/* 8344 */       en_NV_Item_NDIS_DHCP_DEF_LEASE_TIME    = 8344,
/* 8345 */       en_NV_Item_CREG_CGREG_CI_Four_Byte_Rpt = 8345,
/* 8449 */       en_NV_Item_Repeated_Acch_Capability = 0x2101,
/* 8450 */       en_NV_Item_ALS_LINE_Config = 8450,
             /* 关于NV项en_NV_Item_Taf_PdpPara_0~en_NV_Item_Taf_PdpPara_11的说明:
                  这11个NV项在V3版本较V2版本扩展了长度(R7协议升级)，为了保证V2和V3间的一致性，
                  修改这11个NV项的ID值，范围为[8451,8462] */
/* 8451  */      en_NV_Item_Taf_PdpPara_0 = 8451,
/* 8452  */      en_NV_Item_Taf_PdpPara_1,
/* 8453  */      en_NV_Item_Taf_PdpPara_2,
/* 8454  */      en_NV_Item_Taf_PdpPara_3,
/* 8455  */      en_NV_Item_Taf_PdpPara_4,
/* 8456  */      en_NV_Item_Taf_PdpPara_5,
/* 8457  */      en_NV_Item_Taf_PdpPara_6,
/* 8458  */      en_NV_Item_Taf_PdpPara_7,
/* 8459  */      en_NV_Item_Taf_PdpPara_8,
/* 8460  */      en_NV_Item_Taf_PdpPara_9,
/* 8461  */      en_NV_Item_Taf_PdpPara_10,
/* 8462  */      en_NV_Item_Taf_PdpPara_11,

/* 8463  */      en_NV_Item_SrchHplmnFlg_StartInManualMode,
/* 8464  */      en_NV_Item_SrchHplmnFlg_StartOrAreaLostInAutoMode,
/* 8465  */      en_NV_Item_Standard_EHplmn_Support_Flg,
/* 8466  */      en_NV_Item_Standard_STK_SteeringOfRoaming_Support_Flg,
/* 8467  */      en_NV_Item_Network_Name_From_MM_Info,
/* 8468  */      en_NV_Item_W_UL_RF_GATE0,
/* 8469  */      en_NV_Item_W_UL_RF_GATE1,
/* 8470  */      en_NV_Item_W_DRX_CTRL_PARA_POOL,
/* 8471  */      en_NV_Item_PCVOICE_Support_Flg = 0x2117,
/* 8472  */      en_NV_Item_Was_UeFeature_Ctrl = 0x2118,
/* 8473  */      en_NV_Item_ES_IND                          = 0x2119,
/* 8474  */      en_NV_Item_GPRS_Extended_Dynamic_Allocation_Capability,
/* 8475  */      en_NV_Item_EGPRS_Extended_Dynamic_Allocation_Capability,
/* 8476  */      en_NV_Item_Revision_Level_Indicator,
/* 8477  */      en_NV_Item_Downlink_Advanced_Receiver_Performance,
/* 8478  */      en_NV_Item_Ext_RLC_MAC_Ctrl_Msg_Segment_Capability,
/* 8479  */      en_NV_Item_PS_Handover_Capability,
/* 8480  */      en_NV_Item_GWMAC_ADDR,
/* 8482 */       en_NV_Item_WAS_ALGORITHM_SWITCH = 8482,
/* 8483  */      en_NV_Item_Plmn_Search_Threshold,
/* 8484  */      en_NV_Item_Plmn_Search_Flow,
/* 8485  */      en_NV_Item_All_Band_Search_Para,
/* 8486  */      en_NV_Item_Wcdma_Psch_Para,
/* 8487  */      en_NV_Item_BG_IRat_List_Srch_Time,
/* 8488  */      en_NV_Item_ATSETZ_RET_VALUE = 8488,
/* 8489  */      en_NV_Item_NOT_SUPPORT_RET_VALUE,
/* 8490  */      en_NV_Item_SEARCH_TIMER_INFO,
/* 8491  */      en_NV_Item_RABM_TOTAL_RX_BYTES,
/* 8492  */      en_NV_Item_AT_RIGHT_PASSWORD,
/* 8493  */      en_NV_Item_DSFLOW_REPORT,
/* 8495  */      en_NV_Item_CQI_CORRECT_CTRL = 8495,
/* 8496  */      en_NV_Item_SUPPORT_CPHS_FLAG = 8496,
/* 8497  */      en_NV_Item_CPU_FLOW_CTRL_Config,
/* 8498  */      en_NV_Item_RITF_FLOW_CTRL_Config,
/* 8499  */      en_NV_Item_WAS_Errorlog_Energy_Threshold = 8499,
/* 8500  */      en_NV_Item_GAS_Errorlog_Energy_Threshold,
/* 8501  */      en_NV_Item_Sms_Me_Storage_Info = 8501,
/* 8502  */      en_NV_Item_PREVENT_TEST_IMSI_REG = 8502,
/* 8503  */      en_NV_Item_TFC_POWER_FUN_ENABLE = 8503,
/* 8504  */      en_NV_Item_E5_RoamingWhiteList_Support_Flg = 8504,
/* 8505  */      en_NV_Item_BRAZIL_VIVO_STK_CODEC_CORRECT = 8505,
/* 8506  */      en_NV_Item_DISCARD_DELIVER_MSG_FEATURE = 8506,
/* 8507  */      en_NV_Item_REPLACE_DELIVER_MSG_FEATURE = 8507,
/* 8508 */       en_NV_Item_SearchHplmnAtPowerOn = 8508,
/* 8509 */       en_NV_Item_SearchHplmnTtimerValue = 8509,
/* 8513  */      en_NV_Item_IPV6_ROUTER_MTU = 8513,
/* 8514  */      en_NV_Item_IPV6_CAPABILITY = 8514,
/* 8516 */       en_NV_Item_DIAL_CONNECT_DISPLAY_RATE = 8516,
/* 8518 */       en_NV_Item_EnhancedSimCardLockRemainTimes = 8518,
/* 8519  */      en_NV_Item_MO_SMS_CONTROL_FEATURE = 8519,
/* 8520  */      en_NV_Item_GSM_Multirate_Capability = 8520,
/* 8523  */      en_NV_Item_AisRoamingTot = 8523,
/* 9001  */      en_NV_Item_Gsm_Classmark3_R8 = 9001,
/* 9002  */      en_NV_Item_EUTRA_MEAS_AND_REPORTING_SUPPORT_FLG = 9002,
/* 9003  */      en_NV_Item_PRI_BASED_RESEL_SUPPORT_FLG = 9003,
/* 9004  */      en_NV_Item_GERAN_TO_EUTRA_SUPPORT_IN_TRANSFER_MODE = 9004,
/* 9005  */      en_NV_Item_EUTRA_CAPA_COMM_INFO = 9005,
/* 9006  */      en_NV_Item_TIN_INFO = 9006,
/* 9007  */      en_NV_Item_RAT_PRIO_LIST = 9007,
/* 9008  */      en_NV_Item_WAS_RadioAccess_Capa_New = 9008,/* WAS新增NV项 */
/* 9009  */      en_NV_Item_GAS_High_Multislot_Class = 9009,
/* 9010  */      en_NV_Item_NDIS_DIALUP_ADDRESS = 9010,
/* 9011  */      en_NV_Item_WPHY_CPC_DRX_STRU = 9011,                           /*WPHY CPC DRX项目新增加的NV项*/

/* 9012  */      en_NV_Item_PS_START                 = 9012,
/* 9013  */      en_NV_Item_W_HSPA_CQI_TABLE1 = 9013,
/* 9014  */      en_NV_Item_W_HSPA_CQI_TABLE2,
/* 9015  */      en_NV_Item_W_HSPA_CQI_TABLE3,
/* 9016  */      en_NV_Item_W_HSPA_CQI_TABLE4,
/* 9017 */       en_NV_Item_USER_SET_LTEBANDS = 9017,                           /* V7R1_PHASEII新增NV,保存用户设置的LTE频段 */
/* 9018 */       en_NV_Item_SINGLE_DOMAIN_FAIL_SRCH_PLMN_CNT = 9018,           /* DT的定制需求，单域注册被拒时，需要发起搜网 */
/* 9019  */      en_NV_Item_Ps_Loci = 9019,

/* 9020  */      en_NV_Item_W_RX_EEIC_EN = 9020,

/* 9021  */      en_NV_Item_W_HSPA_RTT_Test_Switch = 9021,
/* 9022 */       en_NV_Item_GPRS_Non_Drx_Timer_Length = 9022,
/* 9023  */      en_NV_Item_Wcdma_Prach_Para = 9023,
/* 9024 */       en_NV_Item_W_HSPA_CQI_TABLE5 = 9024,
/* 9025 */       en_NV_Item_W_HSPA_CQI_TABLE6,
/* 9026 */       en_NV_Item_W_RX_IPS_FlAG,
/* 9027  */      en_NV_Item_Fastdorm_Para = 9027,
/* 9028 */       en_NV_Item_W_HSPA_EEIC_CQI_TABLE1 = 9028,
/* 9029 */       en_NV_Item_W_HSPA_EEIC_CQI_TABLE2,
/* 9030 */       en_NV_Item_W_HSPA_EEIC_CQI_TABLE3,
/* 9031 */       en_NV_Item_W_HSPA_EEIC_CQI_TABLE4,
/* 9032 */       en_NV_Item_W_HSPA_EEIC_CQI_TABLE5,
/* 9033 */       en_NV_Item_W_HSPA_EEIC_CQI_TABLE6,
/* 9034 */       en_NV_Item_Lte_Ue_Operation_Mode    = 9034,
/* 9035 */       en_NV_Item_Lte_Cs_Service_Config    = 9035,
/* 9036  */      en_NV_Item_DSFLOW_STATS_CTRL        = 9036,


/* 9038 */       en_NV_Item_Linux_CPU_Moniter_Timer_Len  = 9038,

/* 9039 */       en_NV_Item_ADS_Queue_Scheduler_Pri  = 9039,

/* 9055 */       en_NV_Item_NVIM_WCDMA_PRIORITY_GSM_SUPPORT_FLG = 9055,         /*H3G需求,W网络优先于GSM网络定制 */
/* 9056 */       en_NV_Item_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG = 9056,         /* 服务域设置为PS ONLY时，是否支持CS域短信和呼叫业务(紧急呼叫除外)*/
/* 9057 */       en_NV_Item_NVIM_CCBS_SUPPORT_FLG = 9057,                       /*CCBS(遇忙呼叫完成)业务*/
/* 9058 */       en_NV_Item_NVIM_SIM_CALL_CONTROL_SUPPORT_FLG = 9058,           /* SIM卡Call Control业务*/
/* 9059 */       en_NV_Item_NVIM_CALL_DEFLECTION_SUPPORT_FLG = 9059,            /*支持呼叫偏转业务*/
/* 9060 */       en_NV_Item_NVIM_ALS_SUPPORT_FLG = 9060,                        /* 支持线路切换业务*/
/* 9061 */       en_NV_Item_NVIM_GET_CSMP_PARA_FROM_USIM_SUPPORT_FLG = 9061,    /*从(U)SIM卡中读取CSMP参数 */
/* 9062 */       en_NV_Item_NVIM_SMS_PP_DOWNLOAD_SUPPORT_FLG = 9062,            /*表明是否支持短信的PP-DOWNLOAD功能*/
/* 9063 */       en_NV_Item_NVIM_SMS_NVIM_SMSREXIST_SUPPORT_FLG = 9063,         /*表明NVIM中是否能保存短信状态报告*/
/* 9064 */       en_NV_Item_NVIM_SMS_STATUS_REPORT_IN_EFSMS_SUPPORT_FLG = 9064, /*支持短信状态报告存到EFSMS文件*/

/* Modified by z40661 for 泰国AIS特性 2012-05-17, begin */
                en_NV_Item_NVIM_AIS_ROAMING_CFG  = 9073                        ,       /*  */
/* Modified by z40661 for 泰国AIS特性 2012-05-17, end */

                 /* Custom NV项 */
/* 9074 */       en_NV_Item_User_Auto_Resel_Switch = 9074,                      /* User Reselction功能是否使能 */


/* 9075 */		 en_NV_Item_PRIO_HPLMNACT_CFG = 9075,                               /* 定制的HplmnAct的优先接入技术 */


/* 9093 */       en_NV_Item_UE_POSITION_CAPABILITIES = 9093,                    /* UE定位能力 */

/* 9109 */       en_NV_Item_NVIM_SMS_BUFFER_CAPABILITY = 9109,                         /* SMS的缓冲大小 */

/* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, begin */
/* 9106 */       en_NV_Item_PLMN_EXACTLY_COMPARE_FLG = 9106,                    /*表明是否精确比较PLMN(MNC比较三位)*/
/* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, end */

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, begin */
/* 9105 */      en_NV_Item_Csfb_Emg_Call_LaiChg_Lau_First_CFG = 9105,     /* csfb紧急呼叫到GU,LAI改变先做lau再进行呼叫配置*/
/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, end */
                 en_NV_Item_W_DRX_LTE_EVALUATE_PARA_STRU = 9107,
/* 9108 */      en_NV_Item_USIM_Status_Need_Fcp = 9108,

/* 9114 */      en_NV_Item_ANT2_OFF_EVA_THRESH  = 9114,
/* 9115 */      en_NV_Item_VOLT_LOWPOWER_CTRL   = 9115,
/* 9117  */      en_NV_Item_NotDisplayLocalNetworkName = 9117,

/* 9136 */       en_NV_Item_SMS_Close_Path = 9136,

/* 9137  */      en_NV_Item_NasIsrSupport = 9137,

/* Added by y00142674 for GSM自主重定向到LTE, 2013-08-05, begin */
/* 9139 */       en_NV_Item_GSM_AUTO_FR_LTE_MEAS_CONFIG = 9139,                 /* GSM自主重定向到LTE的LTE频点测量配置 */
/* Added by y00142674 for GSM自主重定向到LTE, 2013-08-05, end */
                 
/* 9140 */       en_NV_Item_NAS_GMM_REL_CONN_AFTER_PDP_DEACT = 9140,

/* 9204 */       en_NV_Item_NETFILTER_HOOK_MASK = 9204,

 /* 9221 */       en_NV_Item_W_High_Speed_Detect_Config = 9221,

/* 9222 */      en_NV_Item_PHY_WCDMA_MAIL_BOX_CFG = 9222,

/* 9223 */      en_NV_Item_Oos_RL_FAIL_TimerLen           = 9223,

/* 9226 */      en_NV_Item_SS_Retry_CFG           = 9226,

/* 9245 */      en_NV_Item_Gas_W_Non_NCell_Meas_Ctrl = 9245,
/* 9271 */      en_NV_Item_GSM_RF_UNAVAILABLE_CFG    =  9271,

/* 9253 */      en_NV_Item_CBS_DRX_OPTIMIZATION_CFG = 9253,

/* Added by p00166345 for DTS2014050808614(离网重选), 2014-01-16, begin */
/* 9255 */      en_NV_Item_Gsm_Cell_Info_Rpt_Cfg    = 9255,
/* Added by p00166345 for DTS2014050808614(离网重选), 2014-01-16, end */

/* 9260 */      en_NV_Item_YOIGO_CUSTOM_PARA_INFO   = 9260,

/* 9261 */      en_NV_Item_Gas_Individual_Customize_Cfg = 9261,

/* 9267 */      en_NV_Item_JAM_DETECT_CFG         = 9267,

/* 9273 */      en_NV_Item_FREQ_LOCK_CFG         = 9273,
                 en_NV_Item_GAS_MNTN_CONFIG        = 9277,
                 
/* 2316 */      en_NV_Item_ENHANCED_OPERATOR_NAME_SRV_CFG = 2316,
/* 2323 */      en_NV_Item_REFRESH_ALL_FILE_RESTART_CFG   = 2323,

                 /* Custom NV项 */
                 en_NV_Item_ManufactureInfo = GU_CUSTOM_BASE_NV_ID_MIN,
/* 32769 */      en_NV_Item_PPP_CONFIG_MRU_Type,

/* 50001 */      en_NV_Item_GU_CHECK_ITEM = 50001,
/* 50002 */      en_NV_Item_TL_CHECK_ITEM,
/* 50003 */      en_NV_Item_GU_M2_CHECK_ITEM,

/* 32770 */      en_NV_Item_PS_Butt

};


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* __PSNVID_H__ */






