/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : SysNvId.h
  版 本 号   :
  作    者   : 胡骏 59254
  生成日期   : 2009年5月14日
  最近修改   :
  功能描述   : 定义了系统NV项ID枚举定义
  函数列表   :
  修改历史   :
  1.日    期   : 2009年5月14日
    作    者   : 胡骏 59254
    修改内容   : 创建文件

******************************************************************************/

#ifndef __SYSNVID_H__
#define __SYSNVID_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "NvIddef.h"


/*typedef VOS_UINT16  SYS_NV_ID_ENUM_U16;
 */

enum SYS_NV_ID_ENUM
{
/*    0  */      en_NV_Item_IMEI = GU_SYS_NV_ID_MIN,
/*    1  */      en_NV_Auth_Code_ID = GU_SYS_NV_ID_MIN + 1,
/*    2  */      en_NV_Auth_Num_ID,
/*    3  */      en_NV_Ttl_ID,
/*    4  */      en_NV_Resume_Flag,
/*    5  */      en_NV_Calibrated_Time,
/*    6  */      en_NV_Item_Serial_Num,
/*    7  */      en_NV_Item_LED_CONFIG_Data,
/*    8  */      en_NV_Item_Om_LogFile_Size,
/*    9  */      en_NV_Item_WatchDog_Flag,
/*   10  */      en_NV_Item_MonitorDSp_Flag,
/*   11  */      en_NV_Item_KickDog_Time = 11,
/*   12  */      en_NV_Item_ScheduleWatchDog_Time,
/*   13  */      en_NV_Item_USIM_TEMP_SENSOR_TABLE,
/*   14  */      en_NV_Item_USIM_TEMP_PROTECT,
/*   15  */      en_NV_Item_UE_Point_Ctrl,
/*   16  */      en_NV_Item_AGING_TEST_TABLE,
/*   17  */      en_NV_Item_Exception_Record,
/*   18  */      en_NV_Item_TA_Stub,
/*   19  */      en_NV_Item_TA_RF_DELAY_VAL,
/*   20  */      en_NV_Item_Sys_Prt_Task,
/*   21  */      en_NV_Item_USB_Enum_Status,
/*   22  */      en_NV_Item_LiveTimeControl,
/*   23  */      en_NV_Item_LiveTime,
/*   24  */      en_NV_Item_MONITORCPU_CFG,
/*   27  */      en_NV_Item_COMMDEGBUG_CFG = 27,
/*   28  */      en_NV_Item_Max_Gsm_Reg_Cnt,
/*   29  */      en_NV_Item_DFS_Config=29,
/*   30  */      en_NV_Item_HW_VER,
/*   31  */      en_NV_Item_PID_Enable_Type,
/*   32  */      en_NV_Item_AT_DISLOG_PWD,
/*   33  */      en_NV_Item_AT_SHELL_OPEN_FLAG,
/*   34  */      en_NV_Item_AT_E5_RIGHT_FLAG,
/*   35  */      en_NV_Item_BATTERY_TEMP_ADC,
/*   36  */      en_NV_Item_SW_VERSION_FLAG,
/*   37  */      en_NV_Item_ERRORLOG_ENABLEFLAG = 37,
/*   38  */      en_NV_Item_ERRORLOG_FLUSHBUFINTERVAL = 38,
/*   39  */      en_NV_Item_ERRORLOG_RECORDPERIOD = 39,
/*   40  */      en_NV_Item_USIM_TEMP_PROTECT_NEW,
/*   41  */      en_NV_Item_DRV_CUSTOMIZE_TYPE = 41,        /*这个NV项底软使用*/
/*   42  */      en_NV_Item_AT_DISSD_FLAG = 42,
/*   43  */      en_NV_Item_AT_DISSD_PWD = 43,
/*   44  */      en_NV_Item_WIFI_IP_ADDRESS,
/*   45  */      en_NV_Item_Om_Port_Type,
/*   46  */      en_NV_Item_Om_Printf_Port,
/*   47  */      en_NV_Item_Om_PsLog_Port,
/*   48  */      en_NV_Item_AT_DISLOG_PWD_NEW,
/*   49  */      en_NV_Item_OLED_TEMP_ADC,
/*   50  */      en_NV_Item_MODIFY_LINKINFO_FLAG,
/*   51  */      en_NV_Item_WEBNAS_SD_WORKMODE,
/*   52  */      en_NV_Item_HW_WDT_FLAG,
/*   53  */      en_NV_Item_DEFAULT_LINK_OF_UART = 53,
/*   54  */      en_NV_Item_POWER_LED_ENABLE = 54,
/*   55  */      en_NV_Item_HW_CONFIG = 55,
/*   59  */      en_NV_Item_M2_ENABLE_FLAG = 59,
/*   60  */      en_NV_Item_SVLTE_FLAG = 60,
/*   63  */      en_NV_Item_NPNP_CONFIG = 63,
/*   64  */      en_NV_Item_VSIM_SUPPORT_FLAG = 64,
/*   65  */      en_NV_Item_VSIM_HVSDH_INFO = 65,
/*   66  */      en_NV_Item_VSIM_Fplmn_Info = 66,
/*   67  */      en_NV_Item_VSIM_Loci_Info = 67,
/*   68  */      en_NV_Item_VSIM_PsLoci_Info = 68,
/*   69  */      en_NV_Item_Card_Status_Cb_Type = 69,
/*   70  */      en_NV_Item_LC_Ctrl_PARA = 70,
/*   71  */      en_NV_Item_Usimm_T1_Ctrl_PARA = 71,
/*   90  */      en_NV_Item_BATTERY_ADC = GU_SYS_NV_ID_MIN + 90,
/*   114 */      en_NV_Item_Factory_Info = GU_SYS_NV_ID_MIN + 114,
/*   115 */      en_NV_Item_AT_FACTORY_INFO = GU_SYS_NV_ID_MIN + 115,
/*   116 */      en_NV_Item_AT_MANUFACTURE_DATE = GU_SYS_NV_ID_MIN + 116,
/*   117 */      en_NV_Item_LOG_FILE_SAVE = GU_SYS_NV_ID_MIN + 117,
/*   118 */      en_NV_Item_USB_LOG_LEV = GU_SYS_NV_ID_MIN + 118,
/*   119 */      en_NV_Item_USB_MNTN_FLAG = GU_SYS_NV_ID_MIN + 119,
/*   120 */      en_NV_Item_OAM_Config = GU_SYS_NV_ID_MIN + 120,
/*   121 */      en_NV_Item_System_APP_Config = GU_SYS_NV_ID_MIN + 121,
/*   122 */      en_NV_Item_ZSP_LDF_CONFIG = GU_SYS_NV_ID_MIN + 122,
/*   123 */      en_NV_Item_HIFI_LDF_CONFIG = GU_SYS_NV_ID_MIN + 123,
/*   124 */      en_NV_Item_TTF_MEM_SOLUTION_ID = GU_SYS_NV_ID_MIN + 124,       /*未使用*/
/*   125 */      en_NV_Item_TTF_MEM_SOLUTION_CFG = GU_SYS_NV_ID_MIN + 125,
/*   126 */      en_NV_Item_PHY_SW_CFG = GU_SYS_NV_ID_MIN + 126,
/*   127 */      en_NV_Item_NV_PRIORITY_THRESHOLD = GU_SYS_NV_ID_MIN + 127,    /*FlashLess Phase II*/
/*   128 */      ev_NV_Item_SCI_DSDA_CFG = 128,
/*   129 */      en_NV_Item_Sim_ATR_Flag = GU_SYS_NV_ID_MIN + 129,
/*   130 */      en_NV_Item_TERMINAL_CAPABILITY = GU_SYS_NV_ID_MIN + 130,
/*   131 */      en_NV_Item_Write_Slice_Record_Flag = GU_SYS_NV_ID_MIN + 131,
                 en_NV_ID_SOCP_SDLOG_CFG = 132,
/*   133 */      en_NV_Item_CC_TimerLen  = 133,
/*   134 */      en_NV_Item_ErrLogCtrlInfo = 134,
/*   135 */      en_NV_Item_AlarmidRelationship = 135,
/*   136 */      en_NV_Item_FTMDetail = 136,
/*   137 */      en_NV_Item_RF_INTRUSION_CFG = GU_SYS_NV_ID_MIN + 137,
/*   138 */      en_NV_Item_GUMODE_CHAN_PARA = 138,
/*   139 */      en_NV_Item_RECORD_BASE_BORARD_ID = GU_SYS_NV_ID_MIN + 139,
/*   140 */      en_NV_Item_RECORD_CURRENT_BORARD_ID = GU_SYS_NV_ID_MIN + 140,
/*   141 */      en_NV_Item_UART_CFG = GU_SYS_NV_ID_MIN + 141,

/*   142 */      en_NV_Item_Usim_Support_Ims = GU_SYS_NV_ID_MIN + 142,
/*   143 */      en_NV_Item_FLASH_Log_Record_CFG = GU_SYS_NV_ID_MIN + 143,
/*   144 */      en_NV_Item_PORT_BUFF_CFG           = GU_SYS_NV_ID_MIN + 144,
/*   145 */      en_NV_Item_EVENT_RESEND_CFG = GU_SYS_NV_ID_MIN + 145,
/*   146 */      en_NV_Item_CBT_LOG_ENABLE = GU_SYS_NV_ID_MIN + 146,
/*   147 */      en_NV_Item_PS_TRANSFER_CFG = GU_SYS_NV_ID_MIN + 147,
/*   148 */      en_NV_Item_ProductTypeForLogDirectory = GU_SYS_NV_ID_MIN + 148,
/*   149 */      en_NV_Item_DRX_RESET_ENABLE_CFG = GU_SYS_NV_ID_MIN + 149,
/*   150 */      en_NV_Item_MTC_RF_LCD_CFG = GU_SYS_NV_ID_MIN + 150,
/*   151 */      en_NV_Item_MTC_RF_LCD_TIMER_INTERVAL_CFG = GU_SYS_NV_ID_MIN + 151,

/*   2000*/      en_NV_Item_1X_MRU_LIST = 2000,
/*   2001*/      en_NV_Item_PRL_LIST    = 2001,

/*   2002*/      en_NV_Item_1X_SMS_CFG = 2002,

/*   2003*/      en_NV_Item_CFreqLock_CFG = 2003,

/*   2005*/      en_NV_Item_1X_HOME_SID_NID_LIST       = 2005,
/*   2006*/      en_NV_Item_1X_OOC_TIMER_SCHEDULE_INFO = 2006,
/*   2007*/      en_NV_Item_1X_CHAN_REPEAT_SCAN_STRATEGY = 2007,

/*   2008*/      en_NV_Item_1X_EPDSZID_FEATURE_CFG       = 2008,

/*   2009*/      en_NV_Item_HRPD_MRU_LIST = 2009,
/*   2010*/      en_NV_Item_1X_LAST_SCI = 2010,

/*   2011*/      en_NV_Item_HRPD_LOC_INFO = 2011,
/*   2012*/      en_NV_Item_HRPD_STORAGE_BLOB = 2012,

/*  2013  */     en_NV_Item_CDATA_GENERIC_CONFIG  = 2013,

/* 2014 */       en_Nv_Item_Mmss_System_Acquire_Cfg = 2014,
/* 2015 */       en_Nv_Item_MmssLastLocationInfo = 2015,

/* 2016*/        en_NV_Item_MLPL_MSPL_FILE = 2016,
/*  2017  */     en_NV_Item_TEST_CONFIG  = 2017,

/*  2018  */     en_NV_Item_1X_MOB_TERM = 2018,
/*  2019  */     en_NV_Item_NO_CARD_MODE_CFG = 2019,

/*  2020  */     en_NV_Item_CNAS_HRPD_Session_Info_Ex = 2020,

/*  2021  */     en_NV_Item_CNAS_HRPD_Session_Ctrl_Cfg = 2021,

/* 2022 */      en_NV_Item_EHRPD_Retry_Conn_Est_Config  = 2022,
/* 2023 */      en_NV_Item_EHRPD_Retry_Pdn_Setup_Config = 2023,

/*  2024  */     en_NV_Item_1X_ADD_AVOID_LIST_CFG  = 2024,
/*  2025 */     en_NV_Item_1X_NEG_PREF_SYS_CMP_CTRL  = 2025,

/*  2026 */      en_NV_Item_1X_CALL_CFG  = 2026,

/*  2027  */     en_NV_Item_CNAS_HRPD_Session_Retry_Cfg  = 2027,
/*  2028  */     en_NV_Item_EHRPD_Support_Flg = 2028,
/*  2029  */     en_Nv_Item_CNAS_HRPD_Session_Keep_Alive_Info = 2029,
/*  2030  */     en_Nv_Item_CNAS_HRPD_Session_Info = 2030,
/*  2032  */     en_Nv_Item_EMC_CALLBACK_CFG                = 2032,           /* 紧急呼CallBack模式设置 */
/*  2033  */     en_Nv_Item_EMC_REDIAL_PERIOD               = 2033,           /* 紧急呼重拨定时器时长 */
/*  2034  */     en_NV_Item_HOME_SID_NID_DEPEND_ON_PRL_CFG  = 2034,
/*  2035  */     en_NV_Item_OPER_LOCK_SYS_WHITE_LIST_INFO   = 2035,
/*  2036  */     en_NV_Item_CTCC_CUSTOMIZE_FREQ_INFO        = 2036,
/*  2037  */     en_NV_Item_CDMA_STANDARD_CHANNLES_INFO     = 2037,
/*  2038  */     en_Nv_Item_1X_DATA_SO_CFG = 2038,
/*  2039  */     en_NV_Item_CDMA_1X_CUSTOM_PREF_CHANNELS_INFO   = 2039,
/*  2040  */     en_Nv_Item_1X_VOICE_SO_CFG   = 2040,
/*  2042  */    en_NV_Item_START_AND_STOP_CONT_DTMF_INTERVAL    = 2042,     /* StopContDtmfReq和StartContDtmfReq发送间隔时长 */
/*  2043 */     en_NV_Item_CL_DELAY_REPORT_SERVICE_STATUS_CFG  = 2043,    /* CL模服务状态延时上报定时器时长 */
/*  2044  */     en_Nv_Item_CNAS_HRPD_ACCESS_AUTH_INFO    = 2044,

/*  2045  */    en_NV_Item_1X_XSMS_KMC_ADDRESS             = 2045,     /* 电话加密，发送和接受短信的地址 */

/*  2046  */    en_NV_Item_VOICE_ENCRYPT_PUBLICKEY_AND_VERSION_INFO = 2046, /* ECC的公钥以及公钥版本号 */
/*  2047  */    en_NV_Item_VOICE_ENCRYPT_CAP_PARA_INFO              = 2047, /* 语音加密能力配置参数，即加密能力以及动态配置开关 */
/*  2048  */    en_NV_Item_VOICE_ENCRYPT_SECINFO_ERASE_SYSTIME_INFO = 2048, /* 安全信息擦除系统时间 */

/*  2049*/      en_NV_Item_OM_Port_Num = GU_SYS_NV_ID_MIN + 2049,

/*  2050  */    en_NV_Item_VOICE_ENCRYPT_PASSWD_RESET_SYSTIME_INFO  = 2050, /* 密码重置系统时间 */
/*  2051  */    en_NV_Item_VOICE_ENCRYPT_TIMER_CFG_INFO             = 2051, /* 语音加密延时密钥请求发送时长 */

/*  2052  */    en_NV_Item_EMC_REDIAL_SYS_ACQ_CFG    = 2052,

/*  2053  */    en_NV_Item_1X_PAGING_RSP_SO_CFG                 = 2053,

/*   2054*/      en_NV_Item_CDATA_DISCING_PARA_CFG = 2054,       /* CDMA网络下去激活流程中涉及到的参数 */

/*  2055  */    en_NV_Item_1X_AVOID_SCHEDULE_INFO             = 2055,

/*   2056*/      en_NV_Item_HRPD_OOC_TIMER_SCHEDULE_INFO = 2056,

/*  2057  */    en_NV_Item_1X_SMS_MO_TL_ACK_TIME_OUT_CFG        = 2057,  /* 短信发送时等待TL_ACK超时的处理配置 */
/*  2059  */    en_NV_Item_1X_SERVICE_CL_SYSTEM_ACQUIRE_STRATEGY_CFG = 2059, /* 1x有服务时CL系统捕获策略配置 */

/*   2060*/      en_NV_Item_PPP_AUTH_INFO_FROM_CARD_FLAG = 2060,       /* 1X HRPD PPP的鉴权参数来自于用户还是card */

/* 2061 */       en_NV_Item_EHRPD_AUTO_ATTACH_CTRL_CFG = 2061,

/* 2062 */       en_NV_Item_1X_POWER_OFF_CAMP_ON_CTRL = 2062,
/*  2063  */     en_NV_Item_CL_NO_SERVICE_DELAY_RPT_CFG  = 2063,       /* 延迟上报HRPD或LTE无服务定时器时长配置 */

/* 2064 */       en_NV_Item_NDIS_FILTER_ENABLE_FLAG_CFG = 2064,

/*   2300*/      en_NV_Item_DSDS_Active_Modem_Mode = 2300,
/*   2302*/      en_NV_Item_HIGH_PRIO_RAT_HPLMN_TIMER_CFG = 2302,
/* 2303 */       en_NV_Item_ChangeNWCause_CFG = 2303,
/*   2304*/      en_NV_Item_ECID_TL2GSM_CFG = 2304,
/* 2305  */      en_NV_Item_CMCC_Cfg_Dplmn_Nplmn = 2305,
/* 2306  */      en_NV_Item_UNICOM_Cfg_Dplmn_Nplmn = 2306,
/* 2307  */      en_NV_Item_CT_Cfg_Dplmn_Nplmn = 2307,
/* 2308  */      en_NV_Item_Cfg_Dplmn_Nplmn_Flag = 2308,
/*   2309*/     en_NV_Item_REL_PS_SIGNAL_CON_CFG = 2309,
/* 2310 */      en_NV_Item_Wcdma_Voice_Prefer_Cfg = 2310,
/*  2311 */      en_NV_Item_PDN_TEARDOWN_POLICY = 2311,

/*   2312*/     en_NV_Item_User_Cfg_Ext_Ehplmn_Info = 2312,            /* 用户配置的EHplmn NVIM组 ID */

/*   2313*/     en_NV_Item_LTE_REJ_CAUSE_14_CFG = 2313,

/*   2314*/     en_NV_Item_TTY_Mode = 2314,
/*  2315 */     en_NV_Item_Csmo_Supported_Cfg_Info  = 2315,                     /* 配置是否支持CSMO */
/*   2317 */     en_NV_Item_CC_T303_Len_Cfg  = 2317,           /* T303定时器时长，范围为30~255，单位为秒 */
/*  2318 */     en_NV_Item_T3212_Timer_Cfg_Info     = 2318,                     /* 配置T3212定时器时长信息 */
/*  2319 */     en_NV_Item_Roam_Display_Cfg = 2319,                /* 漫游显示配置 */
/*   2320*/     en_NV_Item_Rat_Frequently_Switch_Chr_Rpt_Cfg = 2320,
/* 2324 */      en_NV_Item_Protect_Mt_Csfb_Paging_Procedure_Len = 2324,         /* csmt 保护时长 */

/*  2321 */     en_NV_Item_NVWR_SEC_CTRL            = 2321,                     /* NVWR命令安全控制 */
/* Added by c00318887 for file refresh需要触发背景搜, 2015-4-28, begin */
/* 2325 */      en_NV_Item_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG   = 2325,
/* Added by c00318887 for file refresh需要触发背景搜, 2015-4-28, end */

/*   2322*/     en_NV_Item_DELAY_REPORT_SERVICE_STATUS_CFG = 2322,
                en_NV_Item_SMS_PS_CTRL              = 2326,
/* Added by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, begin */
/* 2327  */      en_NV_Item_First_Preset_Dplmn_Nplmn_Cfg = 2327,
/* 2328  */      en_NV_Item_Second_Preset_Dplmn_Nplmn_Cfg = 2328,
/* 2329  */      en_NV_Item_Self_Learn_Dplmn_Nplmn_Cfg = 2329,
/* Added by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, begin */


/*  2330 */     en_NV_Item_Non_Oos_Plmn_Search_Feature_Support_Cfg       = 2330,                     /* 周期性HISTORY搜网定时器时长配置 */
/*  2331 */     en_NV_Item_Ccpu_Reset_Record        = 2331,                     /* C核单独复位记录 */
/*  2332 */     en_NV_Item_Get_Geo_Cfg_Info         = 2332,                     /* 获取国家码的配置信息 */
/*  2333 */     en_NV_Item_Roam_Plmn_Selection_Sort_Cfg     = 2333,             /* 漫游选网重新排序控制NV,在此NV打开时候，才考虑将漫游网络按DUO顺序排序到前面 */



/* Added by c00318887 for 移植T3402 , 2015-6-17, begin */
/* 2334 */      en_NV_Item_DISABLE_LTE_START_T3402_ENABLE_LTE_CFG   = 2334,
/* Added by c00318887 for 移植T3402 , 2015-6-17, end */
/*   2335*/     en_NV_Item_LTE_OOS_2G_PREF_PLMN_SEL_CFG = 2335,

/*  2336 */     en_NV_Item_Ipv6_Address_Test_Mode_Cfg = 2336,                   /* IPV6地址测试模式配置，0x55AA55AA为测试模式，其他值为正常模式 */

/*  2337 */     en_NV_Item_Rnic_Netif_Rx_Type       = 2337,                     /* RNIC模块使用netif_rx内核函数的类型 */

/*  2338 */     en_NV_Item_Dynload_CTRL     = 2338,

/* 2339 */      en_NV_Item_Nw_Search_Chr_Record_Cfg = 2339,                     /* 搜网CHR记录配置 */
/*  2341 */     en_NV_Item_PS_REG_FAIL_MAX_TIMES_TRIG_LAU_ONCE_CFG              = 2341,
/*  2342 */     en_NV_Item_KEEP_SRCH_HPLMN_EVEN_REJ_BY_CAUSE_13_CFG             = 2342,
/*  2343 */     en_NV_Item_EPS_REJ_BY_CAUSE_14_IN_VPLMN_Allow_PS_REG_CFG        = 2343,
/*  2344 */     en_NV_Item_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG                      = 2344,
/*  2345 */     en_NV_Item_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST                    = 2345,
/*  2346 */     en_NV_Item_LAU_REJ_TRIG_PLMN_SEARCH                             = 2346,
/*  2347 */     en_NV_Item_CALL_REDIAL_CM_SRV_REJ_CAUSE_CFG                     = 2347,
/*  2348 */     en_NV_Item_SMS_RETRY_CM_SRV_REJ_CAUSE_CFG                       = 2348,
/*  2349 */     en_NV_Item_SS_RETRY_CM_SRV_REJ_CAUSE_CFG                        = 2349,
/*  2350 */     en_NV_Item_REDIAL_IMS_TO_CS_DOMAIN_CFG                          = 2350,

/*  2340 */     en_NV_Item_Ccwa_Ctrl_Mode                   = 2340,

/* Added by c00318887 for 预置频点搜网优化, 2015-8-26, begin */
/*  2351 */     en_NV_Item_Plmn_Search_Phase_One_Total_Timer_CFG       = 2351,  /* 第一阶段搜网总时间配置 */
/* Added by c00318887 for 预置频点搜网优化, 2015-8-26, end */
/* 2352 */      en_NV_Item_Sms_Log_Filter_Cfg           = 2352,
/* added by y00176023 for DTS2015091602371 澳电低优先级ANYCELL搜LTE定制, 2015-9-17, begin */
/* 2353 */      en_NV_Item_Low_Prio_Anycell_Search_Lte_Cfg   = 2353,
/* added by y00176023 for DTS2015091602371 澳电低优先级ANYCELL搜LTE定制, 2015-9-17, end */
/*  2354 */     en_NV_Item_ADS_WAKE_LOCK_CFG = 2354,                            /* ADS WAKELOCK 配置 */
/*  2355 */     en_NV_Item_CS_REG_FAIL_FORB_LA_TIME_CFG                = 2355,  /* cs注册失败将当前LA加入FORB LA时间配置 */

/*  2356 */     en_NV_Item_Add_EHPLMN_WHEN_SRCH_HPLMN_CFG = 2356,               /* 搜索HPLMN时携带EHPLMN 配置 */

/*  2357 */     en_NV_Item_BUFFER_SERVICE_REQ_PROTECT_TIMER_CFG = 2357,         /* 缓存cc ss sms 服务请求时的保护定时器配置 */

/*  2358 */     en_NV_Item_REFRESH_RPLMN_WHEN_EPLMN_INVALID_CFG                 = 2358,

/*  2359  */    en_NV_Item_PROGRESS_INDICATOR_START_T310_INFO   = 2359,         /* 当progress indicator 为#1，#2, #64时，是否启动T310 */

/*  2360 */     en_NV_Item_Dplmn_Nplmn_Cfg                  = 2360,

/*  2361 */     en_NV_Item_Print_Modem_Log_Type     = 2361,                     /* 控制是否输出modem log的类型 */

/*  2362 */     en_NV_Item_Oos_Plmn_Search_Strategy_Cfg     = 2362,             /* 周期性搜网定时器时长配置 */

/*  2363 */     en_NV_Item_NONNORMAL_REG_STATUS_MERGE_CFG     = 2363,  /* 非正常服务下是否上报注册状态改变的配置 */

/*  2365 */     en_NV_Item_Dynload_Exception_CTRL     = 2365,

/* 2366 */      en_NV_Item_CSG_CTRL_CFG            = 2366,     /* CSG特性相关配置NV项 */

/* 2367 */      en_NV_Item_KEEP_CS_FORB_INFO_WHEN_PS_REG_SUCC_CFG = 2367,              /* PS注册成功时是否保留FORB信息的配置 */

/*  2369 */     en_NV_Item_ADS_MEM_POOL_CFG = 2369,

/* 2370 */      en_NV_Item_CLEAR_CKSN_CFG = 2370,                               /* 需要清除CKSN的配置 */

/*   3000*/      en_NV_Item_ErrLog_CsHo_Len = 3000,
 /* 3001 */      en_NV_Item_SBM_CUSTOM_DUAL_IMSI_NEW = 3001,

/* 3002 */      en_NV_Item_GAS_UTRAN_TDD_DEFAULT_Q_RXLMIN = 3002,

/* 3003 */      en_NV_Item_GAS_C1_Calc_Opt_White_Plmn_List = 3003,

/* 3004 */      en_NV_Item_ErrLog_Stay_Self_Rat_Timer_Threshold      = 3004,

/* 3005 */  en_NV_Item_GSM_RAPID_HO_CUSTOMIZE_CFG     = 3005,
/* 3006 */      en_NV_Item_Was_DMCR_CFG      = 3006,
/* 3007 */      en_NV_Item_Was_T320          = 3007,

                en_NV_Item_Csfb_Mcc_Band_Info = 3008,

/* 3009 */     en_NV_Item_GAS_GSM_BAND_CUSTOMIZE_CFG    = 3009,
/* 3010 */     en_NV_Item_Was_Ac_CHECK_Ctrl_Info         = 3010,
/* 3011 */      en_NV_Item_SBM_CUSTOM_DCDPA_CTRL = 3011,

/* 3012 */      en_NV_Item_Was_Csfb_Search_Ctr_Info          = 3012,

/* 3013 */     en_NV_Item_GAS_GSM_CELL_HISTORY_BCCH_SI_CFG    = 3013,

/* Added by y00142674 for 漫游搜网优化, 2015-04-30, begin */
/* 3014 */      en_NV_Item_GSM_SEARCH_CUSTOMIZE_CFG     = 3014,
/* Added by y00142674 for 漫游搜网优化, 2015-04-30, end */

/* 3015 */      en_NV_Item_GAS_FAST_AREA_LOST_CFG = 3015,

/* Added by w00146666 for H_PRIO定制，2015-05-18, begin */
/* 3016 */      en_NV_Item_Inter_Rat_Resel_H_PRIO_Customization      = 3016,
/* Added by w00146666 for H_PRIO定制，2015-05-18, end */
/* 3017 */     en_NV_Item_Was_Eutra_Cell_Resel_Ctr_Info = 3017,

/* 3018 */      en_NV_Item_GAS_AUTO_FR_CFG      = 3018,

/* 3019 */      en_NV_Item_Was_Report_Connected_Location_Info    = 3019,
/* 3024 */      en_NV_Item_Was_Capbility_FddList_Ctr_Info    = 3024,
/* 3020 */      en_NV_Item_Was_Radom_Acc_Ctr_Info            = 3020,
/* 3022 */      en_NV_Item_Was_Noise_Optimize_Ctr_Info       = 3022,
/* Added by x00220225 for 云端频点收集, 2015-07-17, begin */
/* 3023 */      en_NV_Item_WCDMA_HISTORY_PLMN_FREQ_LIST      = 3023,
/* Added by x00220225 for 云端频点收集, 2015-07-17, end */
/* 3025 */     en_NV_Item_Was_Cell_Indi_Offset_Ctrl_Info = 3025,

/* Added by p00166345 for DTS2015052601104(伪基站识别), 2015-08-02, begin */
/* 3026 */      en_NV_Item_GAS_PSEUD_BTS_IDENT_CUST_CFG      = 3026,
/* Added by p00166345 for DTS2015052601104(伪基站识别), 2015-08-02, end */

/* 3027 */      en_NV_Item_GSM_PARALLEL_SEARCH_CUSTOMIZE_CFG    = 3027,

/* 3028 */     en_NV_Item_Was_Cu_Cell_Search_Ctrl_Info       = 3028,
/* 3029 */     en_NV_Item_Was_Operator_Freq_List_Info   = 3029,  /* 运营商定制频点 */
/* 3030 */     en_NV_Item_Was_Broken_Cell_Info   = 3030,         /* BrokenCellList */

/* 3031 */      en_NV_Item_GSM_NETWORK_SEARCH_CUSTOMIZE_CFG             = 3031,
/* 3032 */      en_NV_Item_GSM_OPERATOR_CUSTOMIZE_FREQ_LIST_PART1       = 3032,
/* 3033 */      en_NV_Item_GSM_OPERATOR_CUSTOMIZE_FREQ_LIST_PART2       = 3033,
/* 3034 */      en_NV_Item_GSM_PREFER_PLMN_CUSTOMIZE_CFG                = 3034,

/* 3035 */      en_NV_Item_GSM_ENABLE_HISTORY_ARFCN_WITH_SPEC_ARFCN_LST = 3035,

                 en_NV_Item_GAS_RR_CONNECT_FAIL_PUNISH_CFG              = 3036,
/* 3037 */en_NV_Item_WAS_NETWORK_SEARCH_CUSTOMIZE_CFG                   = 3037,

/* 3038 */      en_NV_Item_GSM_PING_PONG_HO_CUSTOMIZE_CFG               = 3038,
               en_NV_Item_Was_Gsm_Meas_Offset_Ctrl_Info                 = 3039,
/* 3040 */      en_NV_Item_GAS_SAME_LAI_PREFER_CFG                      = 3040,

/* 3041 */     en_NV_Item_WAS_T314_CFG                                  = 3041,

/* 3042 */     en_NV_Item_GSM_LTE_MEASURE_CFG                           = 3042,

/* 3043 */      en_NV_Item_GSM_HO_CUSTOMIZE_CFG                         = 3043,

/* 3044 */     en_NV_Item_GSM_SEC_RXQUAL_SUB_ALPHA_FILTERING_CFG        = 3044,

               en_NV_Item_Plmn_List_Search_Threshold                    = 3045,

/* 3046 */     en_NV_Item_GSM_PMR_CFG                                   = 3046,


/* 3500 */     en_NV_Item_CAS_1X_RC_PREF                     = 3500,
/* 3501 */     en_NV_Item_CAS_1X_NVIM_TERMINAL_INFO          = 3501,
/* 3502 */     en_NV_Item_CAS_1X_NVIM_CELL_THRESHOLD         = 3502,
/* 3503 */     en_NV_Item_CAS_1X_NVIM_ENCRYPT_CAPA           = 3503,
/* 3504 */     en_NV_Item_CAS_1X_NVIM_CHANNEL_CFG_CAPA_INFO  = 3504,
/* 3505 */     en_NV_Item_CAS_1X_NVIM_CAPA_INFO              = 3505,
/* 3506 */     en_NV_Item_CAS_1X_NVIM_RATE_FEATURE_CAPA_INFO = 3506,
/* 3507 */     en_NV_Item_CAS_1X_NVIM_MO_CAPA                = 3507,
/* 3508 */     en_NV_Item_CAS_1X_NVIM_IMSI_TYPE_INFO         = 3508,
/* 3509 */     en_NV_Item_CAS_1X_NVIM_PROTOCOL_OPTIMIZE      = 3509,
/* 3510 */     en_NV_Item_CPROC_1X_NVIM_FILTER_COEF          = 3510,
/* 3511 */     en_NV_Item_CPROC_1X_NVIM_OPTIMIZE_SWITCH      = 3511,
/* 3512 */     en_NV_Item_CPROC_1X_NVIM_SM_MPS_THRESHOLD     = 3512,
/* 3513 */     en_NV_Item_CPROC_1X_NVIM_TAS_PARA_INFO        = 3513,

/* 3600 */     en_NV_Item_CAS_HRPD_NVIM_AT_REV                          = 3600,
/* 3601 */     en_NV_Item_CDMA_SUPPORT_BANDCLASS_MASK                   = 3601,
/* 3602 */     en_NV_Item_CAS_HRPD_NVIM_CELL_THRESHOLD                  = 3602,
/* 3603 */     en_NV_Item_CAS_HRPD_NVIM_SUSPEND_TIMER                   = 3603,
/* 3604 */     en_NV_Item_CAS_HRPD_NVIM_CONNCLOSE_TO_1X_SWITCH          = 3604,
/* 3605 */     en_NV_Item_CAS_HRPD_NVIM_C2L_PARA                        = 3605,
/* 3606 */     en_NV_Item_CAS_HRPD_NVIM_IDLE_HO_PARA                    = 3606,
/* 3607 */     en_NV_Item_CAS_HRPD_NVIM_CFG_PARA                        = 3607,
/* 3608 */     en_NV_Item_CAS_HRPD_NVIM_TIMER                           = 3608,

/* 3609 */     en_NV_Item_CAS_HRPD_NVIM_SESSION_CFG_DATA_PART1          = 3609,
/* 3610 */     en_NV_Item_CAS_HRPD_NVIM_SESSION_CFG_DATA_PART2          = 3610,

/* 3611 */     en_NV_Item_CAS_HRPD_NVIM_SWITCH_PARA                     = 3611,

/*   4000 */     en_NV_Item_DDR_ADJUST_CFG  = 4000,
/*   4001 */     en_NV_Item_Usim_App_Priority_Cfg = 4001,
/* 4002 */       en_NV_Item_PESN   = 4002,
/* 4003 */       en_NV_Item_MEID   = 4003,
/* 4004 */       en_NV_Item_SLEEP_BBE16_CTRL    = 4004,
/* 4005 */       en_NV_Item_Cdma_Test_Card_Cfg                          = 4005,
/* 4006 */       en_NV_Item_STK_Support_Feature_Cfg                     = 4006,

/* 4007 */       en_NV_Item_SC_PERS_Support_Platform_Cfg                = 4007,
/* 4008 */       en_NV_Item_NV_SC_PERS_CTRL_CFG                         = 4008,
/* 4009 */       en_NV_Item_Xpds_Feature_Ctrl_Cfg                       = 4009,

/* 4500 */       en_NV_Item_TTF_PPPC_CONFIG_OPTIONS                       = 4500,

/* 4501 */       en_NV_Item_CTTF_MAC_PROBE_INIT_POWER_CTRL                = 4501,

/* 4800 */       en_NV_Item_WTTF_SRB_NOT_SEND_THRESHOLD                 = 4800,

/* 4502 */       en_NV_Item_NODE_RESET_CTRL                             = 4801,

/*   4900  */    en_NV_Item_Bastet_CONFIG = 4900,
/*   8250*/      en_NV_Item_GCF_TYPE_CONTENT_ID = 8250,
/*   8517*/      en_NV_Item_ENHANCE_SIMCARD_LOCK_STATUS = 8517,
/*   8518*/      en_NV_Item_GENHANCE_SIMCARD_REMAIN_TIMES = 8518,
/*   8524*/      en_NV_Item_TOTOLPC_PARA_CTRL = 8524,
/*   8525*/      en_NV_Item_Wcdma_OLPC_MapWeight_Para = 8525,
/*   9037*/      en_NV_Item_Flow_Ctrl_Config         = 9037,
/*   9040*/      en_NV_Item_WIFI_INFO                = 9040,
/*   9043 */     en_NV_Item_MED_CODEC_TYPE           = 9043,

/*  9046 */      en_NV_Item_Ho_Wait_Sysinfo_Timer_Config    = 9046,

/*   9049 */     en_NV_Item_FDN_Info                 = 9049,
/* 9050  */      en_NV_Item_CSFB_PPAC_Para           = 9050,                  /* WAS新增PPAC NV项 */
/*   9051*/      en_NV_BREATH_TIME = 9051,
/* 增加LTE国际漫游定制NV */
/* 9052 */       en_NV_Item_Lte_Internation_Roam_Config     = 9052,

/* 增加拨号被拒11,12,13,15定制NV */
/* 9053 */       en_NV_Item_Dail_Reject_Config              = 9053,

/* 增加关闭短信定制NV */
/* 9054 */       en_NV_Item_Close_SMS_Capability_Config     = 9054,

/*  9065 */      en_NV_Item_XO_DEFINE               = 9065,

/*  9041 */      en_NV_Item_SubPlatFormInfo      = 9041,
/*  9070 */      en_NV_Item_Eqver                        = 9070,
/*  9071 */      en_NV_Item_Csver                        = 9071,

/* 9066 */       en_NV_Item_Fastdorm_Enable_Flag         = 9066,
/*   9067 */     en_NV_Item_Report_Cell_Sign              = 9067,/* WAS新增NV项，上报小区信号强度 */
                 en_NV_Item_ETWS_Service_Cfg_Para = 9068,                              /* ETWS 相关配置项 */
/*   9069*/      en_NV_Item_WAS_Customized_Para        = 9069,       /* WAS新增NV项，存储定制NV参数 */
/* 9072 */       en_NV_Item_FC_ACPU_DRV_ASSEMBLE_PARA  = 9072, /* 动态调整驱动组包方案档位信息 */

/* 9080 */       en_NV_Item_Scan_Ctrl_Para             = 9080,
/* 9081 */       en_NV_Item_Att_Ens_Ctrl_Para          = 9081,
/* 9082 */       en_NV_Item_Pdp_Act_Limit_Para         = 9082,
/* 9083 */       en_NV_Item_REPORT_ECC_NUM_SUPPORT_FLAG = 9083,
/* 9084 */       en_NV_Item_CUSTOM_ECC_NUM_LIST         = 9084,
/* 9085 */       en_NV_Item_ACTING_PLMN_SUPPORT_FLAG    = 9085,
/* 9086 */       en_NV_Item_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT = 9086,
/* 9087 */       en_NV_Item_SINGLE_DOMAIN_FAIL_ACTION_LIST      = 9087,
/* 9088 */       en_NV_Item_CS_FAIL_NETWORK_FAILURE_PLMN_SEARCH_FLAG = 9088,
/* 9089 */       en_NV_Item_REPORT_PLMN_SUPPORT_FLAG                 = 9089,

/* 9090 */       en_NV_Item_Usim_Support_Feature_Config              = 9090,

/* 9091 */       en_NV_Item_UTRAN_TDD_FREQ_BAND		   = 9091, /* 指示TDS Band信息 */

/* 9092 */       en_NV_Item_Utran_Mode                 = 9092,                  /* 指示当前UTRAN模式为WCDMA还是TD-SCDMA */
/* 9094  */      en_NV_Item_CALL_CallNotSupportedCause = 9094,

/* Added by L60609 for MUX，2012-08-08,  Begin */
/* 9100 */       en_NV_Item_Mux_Support_Flg            = 9100,
/* Added by L60609 for MUX，2012-08-08,  End */

/* 9102 */       en_NV_Item_User_Cfg_Ehplmn_Info       = 9102,                  /* 用户配置的EHplmn NVIM ID */
/* 9103 */       en_NV_Item_Utran_Mode_Auto_Switch     = 9103,                  /* 在当前的GUTL版本，支持配置出GUL版本,GTL版本，以及GUTL版本配置NVIM ID */
/* 9104 */       en_NV_Item_Disabled_Rat_Plmn_Info     = 9104,                  /* 禁止带接入技术的PLMN信息 */

/* 9110 */       en_NV_Item_MULTI_WIFI_KEY             = 9110,       /* 支持多组SSID扩展新增WIKEY NV项 */
/* 9111 */       en_NV_Item_MULTI_WIFI_STATUS_SSID     = 9111,       /* 支持多组SSID扩展新增SSID NV项 */

/* 9112 */      en_NV_Item_UMTS_CODEC_TYPE              = 9112,

/* 9113 */       en_NV_Item_AT_ABORT_CMD_PARA          = 9113,
/* 9116 */       en_NV_Item_CCallState_Rpt_Status           = 9116,             /* ^CCALLSTATE命令主动上报状态 */
/* 9118 */       en_NV_Item_SMS_MT_CUSTOMIZE_INFO       = 9118,

 /* 9119  */     en_NV_Item_CS_Call_Redial_CFG = 9119,

 /* 9120  */     en_NV_Item_QSearch_Customization = 9120,

/* 9121 */       en_NV_Item_Gsm_Poor_RxQual_ThresHold = 9121,

/* 9122 */       en_NV_Item_Hplmn_Register_Ctrl_Flg = 9122,
/*9123*/        en_NV_Item_CELL_SIGN_REPORT_CFG        = 9123,
/* 9124 */       en_NV_Item_LOW_POWER_Cell_Resel_OffSet = 9124,
/* 9125 */       en_NV_Item_MUX_REPORT_CFG = 9125,
/* 9126 */       en_NV_Item_Usim_OpFile_Init_Cfg = 9126,
/* 9127 */       en_NV_Item_Sim_OpFile_Init_Cfg = 9127,
/* 9128 */       en_NV_Item_CIMI_PORT_CFG = 9128,
/* 9129 */       en_NV_Item_Test_Card_Cfg = 9129,

/* 9130 */       en_NV_Item_IPV6_BACKPROC_EXT_CAUSE = 9130,

                 en_NV_Item_SMS_TIMER_LENGTH = 9131,
                 en_NV_Item_SS_CUSTOMIZE_PARA = 9132,
/* 9133 */       en_NV_Item_UCS2_Customization = 9133,

/* 9134 */       en_NV_Item_Csfb_Customization = 9134,

/* 9200 */       en_NV_Item_WTTF_MACDL_WATERMARK_LEVEL_Config = 9200, /* BBP译码中断水线等级控制信息 */
/* 9201 */       en_NV_Item_WTTF_MACDL_BBPMST_TB_HEAD_Config  = 9201, /* BBPMST头部TB块信息 */

/* 9202 */       en_NV_Item_AT_CLIENT_CONFIG    = 9202,                           /* 双卡双通控制AT通道归属哪个Modem信息 */

/* 9203 */       en_NV_Item_Platform_RAT_CAP        = 9203,
/* 9205 */       en_NV_Item_BBP_DUMP_ENABLE             = 9205,  /* BBP 数采开关 */
/* 9206 */       en_NV_Item_SUPPORT_RATMODE_MASK    = 9206, /* 告知物理层每个MODEM支持的模式 */

/* 9207 */       en_NV_Item_Clvl_Volume         = 9207,

/* 9206 */       en_NV_Item_BODY_SAR_PARA               = 9208,

/* 9209 */       en_NV_Item_Ext_Tebs_Flag              = 9209, /* TTF BO扩展功能 */
/* 9210 */       en_NV_Item_TCP_ACK_Delete_Flg         = 9210, /* TTF 旧的TCP ACK删除功能 */

/* 9211 */       en_NV_Item_H3g_Customization          = 9211,

/* 9212 */       en_NV_Item_TEMP_PROTECT_CONFIG = 9212,

/*9213*/         en_NV_Item_THERMAL_TSENSOR_CONFIG          = 9213, /* 温保tsensor控制NV */
/*9214*/         en_NV_Item_THERMAL_BAT_CONFIG              = 9214, /* 温保电池控制NV */
/*9215*/         en_NV_Item_THERMAL_HKADC_CONFIG            = 9215, /* 温保HKADC通道控制NV */
/*9216*/         en_NV_Item_HKADC_PHYTOLOGICAL_CONFIG       = 9216, /* 温保物理到逻辑转换控制NV */
/*9217*/         en_NV_Item_NV_TCXO_CFG                     = 9217, /* TCXO配置参数 */

/*9218*/         en_NV_Item_SHARE_PDP_INFO                  = 9218, /* Share PDP特性控制NV */
/*9219*/         en_NV_Item_DEACT_USIM_WHEN_POWEROFF        = 9219, /* AT+CFUN=0命令软关机，去激活SIM卡功能控制NV */
                en_NV_Item_Enable_Lte_Timer_Len = 9220,

                en_Item_NAS_VSIM_CTRL_FEATURE               = 9224,

/*   9225  */   en_NV_Item_CSFB_RAU_FOLLOW_ON_FLAG = 9225,

/* 9227 */      en_NV_Item_ChangeRegRejectCause_Flg           = 9227,

/* 9228  */      en_NV_Item_ACC_BAR_PLMN_SEARCH_FLG = 9228,           /*定制非HPLMN和RPLMN接入禁止时是否需要搜网 */
/* 9229  */      en_NV_Item_USER_CFG_OPLMN_LIST = 9229,               /*定制用户预制OPLMN列表，与SIM卡互斥，优先级高于SIM卡 */

/* 9230  */      en_NV_Item_Rat_Forbidden_List_Config = 9230,

/* 9231 */       en_NV_Item_SMC_Ctrl_Flg                    = 9231,             /* UTRAN SMC控制NV */

/* 9232  */      en_NV_Item_HKADC_CHANNEL_CONFIG = 9232, /* 温保通道配置 */

/* 9233 */      en_NV_Item_Dfs_Dsflow_Rate_Config     = 9233,

/* 9234 */       en_NV_Item_DSDA_PLMN_SEARCH_ENHANCED_CFG = 9234,

/* 9235 */       en_NV_Item_VOICE_TEST_FLAG       = 9235,


/* 9236  */      en_NV_Item_USER_CFG_OPLMN_EXTEND_LIST = 9236,  /*定制用户预制OPLMN列表(支持256个OPLMN)，与SIM卡互斥，优先级高于SIM卡 */

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, begin */
/* 9237  */      en_NV_Item_SMS_DOMAIN                         = 9237,
/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, end */

/* Added by j00169676 for 三步法搜索项目, 2014-1-23, begin */
               en_NV_Item_3G_TO_2G_Config      = 9238,
/* Added by j00169676 for 三步法搜索项目, 2014-1-23, begin */
/* 9239 */       en_NV_Item_UART_SWITCH_CFG = 9239,
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-30, begin */
                en_NV_Item_WAIT_IMS_VOICE_AVAIL_Timer_Len      = 9240,
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-30, end */

                 en_NV_Item_REDIAL_IMS_TO_CS_DOMAIN          = 9241,
                 en_NV_Item_IMS_ROAMING_SUPPORT_FLG          = 9242,

/* Added by f00261443 for VoLTE_PhaseIII  项目, 2013-12-25, begin */
                en_NV_Item_IMS_VOICE_MOBILE_MANAGEMENT       = 9243,
/* Added by f00261443 for VoLTE_PhaseIII  项目, 2013-12-25, end */
/* Added by h00163499 for SVLTE 共天线项目, 2014-1-21, begin */
/* 9244 */       en_NV_MODEM_RF_SHARE_CFG          = 9244,
/* Added by h00163499 for SVLTE 共天线项目, 2014-1-21, end */
/* 9246  */      en_NV_Item_CS_ONLY_DATA_SERVICE_SUPPORT_FLG = 9246,            /* 用户定制NV: PS注册被禁止情况下，是否允许数据业务触发注册的标志 */
/* 9247  */      en_NV_Item_Ignore_Auth_Rej_CFG = 9247,
/* 9248 */       en_NV_Item_GSM_C1_CUSTOMIZE = 9248,
/* 9249 */       en_NV_Item_HIGH_PRIO_RAT_HPLMN_TIMER_INFO = 9249,
/*9250*/         en_NV_Item_LTE_DISABLED_USE_LTE_INFO_FLAG = 9250,            /* L能力不支持时gmm做rau时是否需要从l获取安全上下文或guti映射信息，VOS_TRUE:L disable后rau需要从l获取信息；VOS_FALSE:L disable后rau不需要从l获取信息 */
/* 9251 */      en_NV_Item_SBM_CUSTOM_DUAL_IMSI        = 9251,       /* WAS新增NV项，存储软银双imsi的开关是否打开 */
/* 9252 */      en_NV_Item_Roam_Search_Rplmn_Config    = 9252,
/* 9254 */       en_NV_Item_IMS_USSD_SUPPORT_FLG            = 9254,
/* 9256  */      en_Nv_Item_RCM_PARA_CONFIG                  = 9256,

/* 9257 */       en_NV_Item_GSM_DSDS_PS_CONFIG               = 9257,
/* 9258  */      en_NV_Item_PHY_MODE_DSDS_FLAG               = 9258,
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-4, begin */
/* 9259 */       en_NV_Item_ECALL_CFG_INFO                  = 9259,
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-4, end */
/* 9262 */       en_NV_Item_GSM_SSC_CONFIG_PARA              = 9262,      /* GSM SSC模块NV参数配置  */

/* 9263 */       en_NV_Item_Multi_Dfs_Dsflow_Rate_CFG    = 9263,
/* 9266 */       en_NV_Item_Ultra_Flash_Csfb_Support_Flg    = 9266,
/* 9268 */       en_NV_Item_ADS_DYNAMIC_THRESHOLD_CFG        = 9268,

/* 9269 */       en_NV_Item_DMS_DEBUG_CFG = 9269,

/* 9270 */       en_NV_Item_3GPP2_Uplmn_Not_Pref_Flg    = 9270,

/* 9272 */       en_NV_Item_ROAMING_REJECT_NORETRY_CFG  = 9272,   /* 定制NV: Other Plmn上收到reject 17时不重试 */

/* 9274  */      en_NV_Item_GSM_PCH_DUMMY_DETECT_FLAG    = 9274,

/* ATA是否异步方式上报OK NV控制，异步方式即发送了connect未收
   到网络connect ack就上报ok，非异步方式是等收到网络connect ack再上报ok*/
/* 9276 */     en_NV_Item_Ata_Report_Ok_Async_Cfg = 9276,

/* 9278  */     en_NV_Item_W_HARQ_OUT_CONFIG = 9278,

/* 9279 */       en_NV_Item_W_Drx_Ctrl                  = 9279,         /* WCDMA是否支持DRX的参数设置 */
/* 9280 */       en_NV_Item_GSM_Drx_Ctrl                = 9280,         /* GSM是否支持DRX的参数设置 */

/* 9281 */       en_NV_Item_DSDS_END_SESSION_DELAY      = 9281,

/* 9282 */     en_NV_Item_Syscfg_Trigger_Plmn_Search_Cfg = 9282,

/* 9283 */       en_NV_Item_ESN_MEID = 9283,

/* 9284 */       en_Nv_Item_RCM_TAS_TABLE_CONFIG       = 9284,

/* 9285 */       en_Nv_Item_TAS_FUNC_CONFIG         = 9285,

/* 9286  */     en_NV_Item_Was_Freqbands_Priority  = 9286,

/* 9287 */       en_Nv_Item_TAS_CDMA_CONFIG         = 9287,

/* 9288 */       en_NV_Item_RCM_TEST_CTRL           = 9288,

/* 9289  */     en_NV_Item_GSM_HARQ_OUT_CONFIG      = 9289,

/* Added by g00260269 for SVLTE 共天线项目, 2015-7-20, begin */
/* 9290 */       en_NV_MODEM_RF_SHARE_EX_CFG        = 9290,
/* Added by g00260269 for SVLTE 共天线项目, 2015-7-20, end */

/* 16042  */     en_NV_Item_W_T313_BACK_CTRL  = 16042,

/* 9284 */      en_Nv_Item_RCM_TAS_TABLE_CONFIG_TRI_MODEM   = 16043,

/* 16044  */     en_NV_Item_W_SYNC_MODULE_OPTIMIZE_PARA = 16044,
/* 16046 */     en_Nv_Item_GSM_PSRCH_PCELL_NUM   = 16046,

/* 16044  */     en_NV_Item_W_FET_CTRL = 16047,
/* 20765 */      en_NV_Item_CDMA_PA_TEMP_DET_CHANNEL_BC0 = 20765,

/* 50009 */      en_NV_Item_TRAFFIC_CLASS_Type = GU_CUSTOM_EXTEND_NV_ID_MIN + 9,
/* 50012 */      en_NV_Item_WIFI_KEY = GU_CUSTOM_EXTEND_NV_ID_MIN + 12,
/* 50014 */      en_NV_Item_WIFI_MAC_ADDR = 50014,
/* 50016 */      en_NV_Item_BATTERY_TEMP_PROTECT = 50016,
/* 50018 */      en_NV_Item_SW_VER = 50018,
/* 50023 */      en_NV_Item_PRI_VERSION = 50023,
/* 50024  */     en_NV_Item_HUAWEI_NW_OPL_NAME_CUSTOMIZED = 50024,
/* 50025  */     en_NV_Item_PRIVATE_CMD_STATUS_RPT = 50025,
/* 50027  */     en_NV_Item_DEFAULT_RATE = 50027,
/* 50029  */     en_NV_Item_HUAWEI_IRAN_OPEN_PAGE_I = 50029,
/* 50031  */     en_NV_Item_MEAN_THROUGHPUT = 50031,
/* 50032  */     en_NV_Item_HUAWEI_PCCW_HS_HSPA_BLUE = 50032,
/* 50036  */     en_NV_Item_HUAWEI_CARDLOCK_PERM_EXT      = 50036,
/* 50037  */     en_NV_Item_HUAWEI_CARDLOCK_OPERATOR_EXT  = 50037,
/* 50041  */     en_NV_Item_NV_HUAWEI_DOUBLE_IMSI_CFG_I   = 50041,
/* 50048 */      en_NV_Item_PRODUCT_ID = 50048,
/* 50050  */     en_NV_Item_APN_Customize = 50050,
/* 50051  */     en_NV_Item_VIDEO_CALL = 50051,
/* 50052  */     en_NV_Item_CUST_USSD_MODE = 50052,
/* 50054  */     en_NV_Item_Forbidden_Band = 50054,
/* 50055  */     en_NV_Item_Enhanced_Hplmn_Srch_Flg = 50055,
/* 50056  */     en_NV_Item_SMS_CLASS0_TAILOR = 50056,
/* 50060  */     en_NV_Item_2G_DISABLE_SPARE_BIT3 = 50060,
/* 50061  */     en_NV_Item_PPP_DIAL_ERR_CODE = 50061,
/* 50063  */     en_NV_Item_Special_Roam_Flag = 50063,
/* 50064  */     en_NV_Item_MultiSimCallConf = 50064,
/* 50071  */     en_NV_Item_Cust_PID_Type = 50071,
/* 50091  */     en_NV_Item_Huawei_Dynamic_PID_Type = 50091,
/* 50110  */     en_NV_Item_Protocol_Base_Type = 50110,
/* 50201  */     en_NV_Item_SEC_BOOT_FLAG = 50201,
/* 50549 */      en_NV_Item_WCDMA_JAM_DETECT_CFG     = 50549,
/* 52000 */      en_NV_Item_WIFI_STATUS_SSID = 52000,
/* 52001 */      en_NV_Item_WEB_ADMIN_PASSWORD = 52001,
/* 52002 */      en_NV_Item_AP_RPT_SRV_URL = 52002,
/* 52003 */      en_NV_Item_AP_XML_INFO_TYPE = 52003,
/* 52004 */      en_NV_Item_AP_XML_RPT_FLAG = 52004,
/* 52005 */      en_NV_Item_BATT_LOW_TEMP_PROTECT = 52005,
/* 52006 */      en_NV_Item_ISDB_DEFAULT_KEY = 52006,

/* 52008 */      en_NV_Item_REFRESH_TERMINAL_RESPONSE_CP_OR_AP = 52008,

                 en_NV_Item_SYS_Butt
};


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* __SYSNVID_H__ */


