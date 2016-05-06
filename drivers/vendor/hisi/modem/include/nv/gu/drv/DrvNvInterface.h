/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : DrvNvInterface.h
  Description     : DrvNvInterface.h header file
  History         :

******************************************************************************/

#ifndef __DRVNVINTERFACE_H__
#define __DRVNVINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

/*****************************************************************************
  2 Macro
*****************************************************************************/
#if defined(__OS_VXWORKS__)
#else
typedef signed int          BSP_S32;
typedef signed short        BSP_S16;
typedef signed char         BSP_S8;
typedef char                BSP_CHAR;

typedef unsigned int        BSP_U32;
typedef unsigned short      BSP_U16;
typedef unsigned char       BSP_U8;
#endif

#define KPD_NV_UNIT               (16)  /* total 16 * 32Bit = 64bytes */
#define KPD_EVENT_MAX             (KPD_NV_UNIT-3)

#define NV_WLCOUNTRY_CODE_LEN     (5)
#define NV_WLMODE_LEN             (5)
#define NV_WLSSID_LEN             (33)

#define NV_FACTORY_INFO_I_SIZE    (78)

#define DYN_MAX_PORT_CNT          (17)

/* 设备枚举最大端口个数 */
#if defined (DYNAMIC_PID_MAX_PORT_NUM)
#undef DYNAMIC_PID_MAX_PORT_NUM
#endif
#define DYNAMIC_PID_MAX_PORT_NUM  (17)

/* 版本信息每条的最大长度 */
#if defined (VER_MAX_LENGTH)
#undef VER_MAX_LENGTH
#endif
#define VER_MAX_LENGTH            (30)

#define NV_HW_CFG_LENTH           (0x40)

/*NPNP 特性一级开关判断用宏*/
#define NPNP_OPEN    1
#define NPNP_CLOSE    0

/*NPNP特性NV项判断用宏*/
#define NV_NPNP_ENABLE    1
#define NV_NPNP_DISABLE    0
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
*                                                                            *
*                           参数设置消息结构                                 *
*                                                                            *
******************************************************************************/

/*****************************************************************************
 结构名    : RESUME_FLAG_STRU
 结构说明  : RESUME_FLAG结构
*****************************************************************************/
typedef struct
{
    BSP_U16   usResumeFlag; /*Range:[0, 1]*/
}RESUME_FLAG_STRU;

/*****************************************************************************
 结构名    : LED_CONTROL_NV_STRU
 结构说明  : LED_CONTROL_NV结构 ID=7
*****************************************************************************/
typedef struct
{
    BSP_U8   ucLedColor;      /*三色灯颜色，对应LED_COLOR的值*/
    BSP_U8   ucTimeLength;    /*该配置持续的时间长度，单位100ms*/
}LED_CONTROL_NV_STRU;

/*****************************************************************************
 结构名    : LED_CONTROL_STRU
 结构说明  : LED_CONTROL结构
*****************************************************************************/
typedef struct
{
    LED_CONTROL_NV_STRU   stLED[10];
}LED_CONTROL_STRU;

/*****************************************************************************
 结构名    : LED_CONTROL_STRU_ARRAY
 结构说明  : 三色灯状态序列单元结构
*****************************************************************************/
typedef struct
{
    LED_CONTROL_STRU    stLED_Control[32];
}LED_CONTROL_STRU_ARRAY;

/*****************************************************************************
 结构名    : NV_WDT_TIMEOUT_STRU
 结构说明  : NV_WDT_TIMEOUT结构 ID=11
*****************************************************************************/
typedef struct
{
    BSP_U32   ulWdtTimeOut;
}NV_WDT_TIMEOUT_STRU;


/*****************************************************************************
 结构名    : USIM_TEMP_SENSOR_TABLE
 结构说明  : USIM_TEMP_SENSOR_TABLE结构
*****************************************************************************/
typedef struct
{
    BSP_S16   Temperature;
    BSP_U16   Voltage;
}USIM_TEMP_SENSOR_TABLE;

/*****************************************************************************
 结构名    : USIM_TEMP_SENSOR_TABLE_STRU
 结构说明  : USIM_TEMP_SENSOR_TABLE结构
*****************************************************************************/
typedef struct
{
    USIM_TEMP_SENSOR_TABLE UsimTempSensorTable[19];
}USIM_TEMP_SENSOR_TABLE_STRU;


/*****************************************************************************
 结构名    : EXCEPTION_RECORD_STRU
 结构说明  : EXCEPTION_RECORD结构
*****************************************************************************/
typedef struct
{
    BSP_U32     IsEnable;
    BSP_U32     Config;
    BSP_U32     Reserve;
}EXCEPTION_RECORD_STRU;


/*****************************************************************************
 结构名    : NV_SYS_PRT_STRU
 结构说明  : NV_SYS_PRT结构
*****************************************************************************/
typedef struct
{
    BSP_U32    uintValue;
}NV_SYS_PRT_STRU;


/*****************************************************************************
 结构名    : USB_ENUM_STATUS_STRU
 结构说明  : USB_ENUM_STATUS结构
*****************************************************************************/
typedef struct
{
    BSP_U32    status;
    BSP_U32    value;
    BSP_U32    reserve1;
    BSP_U32    reserve2;
}USB_ENUM_STATUS_STRU;


/*****************************************************************************
 结构名    : LIVE_TIME_CONTROL_STRU
 结构说明  : LIVE_TIME_CONTROL结构
*****************************************************************************/
typedef struct
{
    BSP_U32    ulEnable;
    BSP_U32    ulCycle;
} LIVE_TIME_CONTROL_STRU;


/*****************************************************************************
 结构名    : LIVE_TIME_STRU
 结构说明  : LIVE_TIME结构
*****************************************************************************/
typedef struct
{
    BSP_U32    ulLiveTime;
}LIVE_TIME_STRU;


/*****************************************************************************
 结构名    : USB_SN_NV_INFO_STRU
 结构说明  : USB_SN_NV_INFO结构
*****************************************************************************/
typedef struct
{
    BSP_U32    usbSnNvStatus;
    BSP_U32    usbSnNvSucFlag;
    BSP_U32    usbSnReserved1;
    /*BSP_U32    usbSnReserved2;*/
}USB_SN_NV_INFO_STRU;


/*****************************************************************************
 结构名    : NVHWVER
 结构说明  : NVHWVER结构
*****************************************************************************/
typedef struct
{
    BSP_U32    NV_HW_VER_Flag;
    BSP_U8     NV_HW_VER_VAL[8];
} NVHWVER;

/*****************************************************************************
 结构名    : nv_pid_enable_type
 结构说明  : nv_pid_enable_type结构
*****************************************************************************/
typedef struct
{
    BSP_U32    pid_enabled;
}nv_pid_enable_type;


/*****************************************************************************
 结构名    : NV_AT_SHELL_OPEN_FLAG_STRU
 结构说明  : NV_AT_SHELL_OPEN_FLAG结构
*****************************************************************************/
typedef struct
{
    BSP_U32    NV_AT_SHELL_OPEN_FLAG;
}NV_AT_SHELL_OPEN_FLAG_STRU;

/*****************************************************************************
 结构名    : TEMP_ADC_STRU
 结构说明  : TEMP_ADC结构
*****************************************************************************/
typedef struct
{
    BSP_S16    sTemp;
    BSP_U16    usADC;
}TEMP_ADC_STRU;

/*****************************************************************************
 结构名    : TEMP_ADC_STRU_ARRAY
 结构说明  : TEMP_ADC_STRU_ARRAY结构
*****************************************************************************/
typedef struct
{
    TEMP_ADC_STRU    stTempAdc[28];
}TEMP_ADC_STRU_ARRAY;

/*****************************************************************************
 结构名    : nv_drv_customize_type
 结构说明  : nv_drv_customize_type结构
*****************************************************************************/
typedef struct DRV_CUSTOMIZE_TYPE
{
    BSP_U32 drv_customize_type;
} nv_drv_customize_type;

/*****************************************************************************
 结构名    : NV_ITEM_MODIFY_LINKINFO_FLAG_STRU
 结构说明  : NV_ITEM_MODIFY_LINKINFO_FLAG结构
*****************************************************************************/
typedef struct
{
    BSP_U16    NV_ITEM_MODIFY_LINKINFO_FLAG;  /*Range:[0,1]*/
}NV_ITEM_MODIFY_LINKINFO_FLAG_STRU;


/*****************************************************************************
 结构名    : CHG_TEMP_ADC_TYPE
 结构说明  : CHG_TEMP_ADC_TYPE结构
*****************************************************************************/
typedef struct
{
    BSP_S16   temperature;
    BSP_U16   voltage;
}CHG_TEMP_ADC_TYPE;

/*****************************************************************************
 结构名    : FACTORY_MODE_TYPE
 结构说明  : FACTORY_MODE_TYPE结构
             工厂模式nv项,0 : 工厂模式 1: 非工厂模式 36
*****************************************************************************/
typedef struct
{
    BSP_U32 factory_mode;
}FACTORY_MODE_TYPE;

/*****************************************************************************
 结构名    : NV_WEBNAS_SD_WORKMODE_STRU
 结构说明  : NV_WEBNAS_SD_WORKMODE结构
*****************************************************************************/
typedef struct
{
    BSP_U32 ulSDWorkMode;
}NV_WEBNAS_SD_WORKMODE_STRU;

/*****************************************************************************
 结构名    : HW_WDT_FLAG_STRU
 结构说明  : HW_WDT_FLAG结构
*****************************************************************************/
typedef struct
{
    BSP_U32   HW_WDT_FLAG;
}HW_WDT_FLAG_STRU;

/*****************************************************************************
 结构名    : POWER_LED_ENABLE_STRU
 结构说明  : POWER_LED_ENABLE结构
*****************************************************************************/
typedef struct
{
    BSP_U32   POWER_LED_ENABLE;
}POWER_LED_ENABLE_STRU;

/*****************************************************************************
 结构名    : NV_HW_CONFIG_STRU
 结构说明  : NV_HW_CONFIG结构
*****************************************************************************/
/* PMU每一路配置,8Byte */
typedef struct
{
	BSP_U8 PowerEn;
	BSP_U8 ModuleID;
	BSP_U8 DevID;
	BSP_U8 PowerID;
	BSP_U8 ConsumerID;
	BSP_U8 Reserve;
	BSP_U16 Voltage;
}PMU_POWER_CFG;

/*针对个别电源需要限定电压输出范围,使用相同的结构,但是重新命名*/
/*BUCK1*/
typedef struct
{
	BSP_U8 PowerEn;
	BSP_U8 ModuleID;
	BSP_U8 DevID;
	BSP_U8 PowerID;
	BSP_U8 ConsumerID;
	BSP_U8 Reserve;
	BSP_U16 Voltage;  /*Range:[0,2200]*/
}PMU_POWER_CFG_RFICTX;

/* PMU配置,16路 */
typedef struct
{
	PMU_POWER_CFG 		 RF0_PA;
	PMU_POWER_CFG_RFICTX RFIC0_TX;
	PMU_POWER_CFG 		 RFIC0_RX;
	PMU_POWER_CFG 		 FEM0;
	PMU_POWER_CFG 		 RF0_VBIAS;

	PMU_POWER_CFG 		 RF1_PA;
	PMU_POWER_CFG_RFICTX RFIC1_TX;
	PMU_POWER_CFG 		 RFIC1_RX;
	PMU_POWER_CFG 		 FEM1;
	PMU_POWER_CFG 		 RF1_VBIAS;

	PMU_POWER_CFG FEM0_AUX;
	PMU_POWER_CFG PMU_RESERVE1;
	PMU_POWER_CFG PMU_RESERVE2;
	PMU_POWER_CFG PMU_RESERVE3;
	PMU_POWER_CFG PMU_RESERVE4;
	PMU_POWER_CFG PMU_RESERVE5;
}PMU_CFG_STRU;


typedef struct
{
    BSP_U16 ConsumerID;
    BSP_U16 PowerEn;/*0:该路电源无效；1: 有效电源*/
    BSP_U16 Voltage;
    BSP_U16 ModuleID;
    BSP_U16 DevID;
    BSP_U16 PowerID;
    BSP_U16 Reserve;
}RF_PMU_CFG_STRU;

#define RF_POWER_MAX_NUM (24)
#define RF_POWER_RESERVE_NUM  (8)/*不能用24-14-2，工具HIMS解析不支持*/

typedef struct
{
    BSP_U16 W_PA_VCC;
    BSP_U16 G_PA_VCC;
    BSP_U16 CH0_W_RFIC_TX_ANA;
    BSP_U16 CH0_G_RFIC_TX_ANA;
    BSP_U16 CH1_W_RFIC_TX_ANA;
    BSP_U16 CH1_G_RFIC_TX_ANA;
    RF_PMU_CFG_STRU CH0_PA_VCC;
    RF_PMU_CFG_STRU CH0_PA_VBIAS;
    RF_PMU_CFG_STRU CH0_SWITCH_VCC;
    RF_PMU_CFG_STRU CH0_RFIC_TX_ANA;
    RF_PMU_CFG_STRU CH0_RFIC_RX_ANA;
    RF_PMU_CFG_STRU CH0_FEM_VIO;
    RF_PMU_CFG_STRU CH0_TUNNER_VCC;
    RF_PMU_CFG_STRU CH1_PA_VCC;
    RF_PMU_CFG_STRU CH1_PA_VBIAS;
    RF_PMU_CFG_STRU CH1_SWITCH_VCC;
    RF_PMU_CFG_STRU CH1_RFIC_TX_ANA;
    RF_PMU_CFG_STRU CH1_RFIC_RX_ANA;
    RF_PMU_CFG_STRU CH1_FEM_VIO;
    RF_PMU_CFG_STRU CH1_TUNNER_VCC;
    RF_PMU_CFG_STRU CH0_RFIC_XO_2P85;
    RF_PMU_CFG_STRU CH1_RFIC_XO_2P85;
    RF_PMU_CFG_STRU PMU_CFG[RF_POWER_RESERVE_NUM];
 }RF_VOLT_CONFIG_STRU;

/*----------------------【RF RSE方案】Begin--------------------------------*/
/* gpio控制 天线开关特性NV*/
#define DRV_ANT_SW_UNPD_ENFLAG_DISABLE 0
#define DRV_ANT_SW_UNPD_ENFLAG_ENABLE  1
typedef struct
{
    BSP_U32 is_enable;/*Range [0,1] 其中: 0-特性关闭 1-特性打开*/
 }DRV_ANT_SW_UNPD_ENFLAG;

#define DRV_ANT_GPIO_CFG_UNUSED 0
#define DRV_ANT_GPIO_CFG_USED   1
typedef struct
{
    BSP_U32 gpio_num;/*gpio编号*//*给出的是RF_GPIO_NUM ??*/
    BSP_U32 is_used;  /*Range[0,1]*//*是否使用*/
    BSP_U32 value;   /*配置值*/
}DRV_ANT_GPIO_CFG;

#define GPIO_RF_ANT_SW_MAX 8
typedef struct{
    DRV_ANT_GPIO_CFG antn_switch[GPIO_RF_ANT_SW_MAX];
} DRV_ANT_SW_UNPD_CFG;

typedef struct
{
    DRV_ANT_SW_UNPD_CFG  all_switch[3];/*其中，下标0对应主卡主集，1对应主卡分集，2对应副卡*/
} NV_DRV_ANT_SW_UNPD_CFG;


/* mipi控制 天线开关特性NV*/
#define DRV_ANT_SW_MIPI_ENFLAG_DISABLE 0
#define DRV_ANT_SW_MIPI_ENFLAG_ENABLE  1
typedef struct
{
	BSP_U32 is_enable;/*Range:[0,1] 其中，0-特性关闭 1-特性打开*/
} DRV_ANT_SW_MIPI_ENFLAG;

#define DRV_ANT_SW_MIPI_INVALID 0
#define DRV_ANT_SW_MIPI_VALID   1
typedef struct
{
    BSP_U32 is_invalid;/*Range:[0,1] 其中，0-该组数据无效 1-该组数据有效*/
    BSP_U8 mipi_chn;/*Range:[0,1]*/
    BSP_U8 slave_id;
    BSP_U8 reg_offset;
    BSP_U8 value;
} DRV_ANT_SW_MIPI;

#define MIPI_RF_ANT_SW_MAX 8
typedef struct
{
	DRV_ANT_SW_MIPI modem_switch[MIPI_RF_ANT_SW_MAX];
} DRV_ANT_SW_MIPI_CONFIG;

typedef struct
{
	DRV_ANT_SW_MIPI_CONFIG all_switch[2];/*其中，下标0对应主卡，1对应副卡*/
} DRV_DRV_ANT_SW_MIPI_CONFIG;

/*----------------------【RF RSE方案】End--------------------------------*/

/*----------------------【TDS/L B34/39 & GSM B3共存抗干扰方案】Begin--------------------------------*/

#define NV_GSM_GPIO_RESERVED_NUM_L 2
/*****************************************************************************
 结构名    : UCOM_NV_GSM_GPIO_FUNC_SEL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GPIO2~5功能选择
*****************************************************************************/
typedef struct
{
    BSP_U16 uhwGpioAndOrSel;        /* GPIO输出与或选择
                                        bit0~1	 	Reserved
                                        bit2    	GPIO2的与或选择    0--GPIO双modem相或输出(默认)、1--GPIO双modem相与输出
                                        bit3 		GPIO3的与或选择    类似
                                        bit4 		GPIO4的与或选择    类似
                                        bit5 		GPIO5的与或选择    类似
                                        bit6~15	Reserved*/
    BSP_U16 uhwGpioCtrlAbbTxSel;    /* GPIO与或输出是否控制abb tx
                                        bit0~1	 	Reserved
                                        bit2    	GPIO2的与或输出是否控制abb tx   0--不控制abb的tx(默认)、1--控制abb的tx
                                        bit3 		GPIO3的与或输出是否控制abb tx   	类似
                                        bit4~15	Reserved*/
}UCOM_NV_GSM_GPIO_FUNC_SEL_STRU;

/*----------------------【TDS/L B34/39 & GSM B3共存抗干扰方案】End--------------------------------*/

/*过热保护设置*/
typedef struct
{
	BSP_U8 OTMP_TMP;          /*过热保护温度设置*/
	BSP_U8 OTMP_PWR_DOWN;     /*过热后，非核心电源是否下点*/
	BSP_U8 OTMP_RESET;        /*过热后，是否进行软复位*/
	BSP_U8 RESERVE;
}PMU_PROTECT_STRU;

typedef struct
{
	BSP_U32 RESERVE0;           	/* 保留,4Byte */
	BSP_U16 W_PA_V;            		/* W PA电压 2Byte */
	BSP_U16 G_PA_V;             	/* G PA电压 2Byte */
	BSP_U32 USB_EYE_CFG;        	/* USB眼图 4Byte */
	BSP_U32 APT_MODE;           	/* APT 模式 4Byte，参见DR_APT_CFG_ENUM */
	PMU_PROTECT_STRU PMU_PROTECT;   /* PMU 过热保护 4Byte*/
	BSP_U32 DRV_LOG_CTRL;       	/* DRVLOG打印开关 4Byte */
	BSP_U32 DRV_LOG_LEVEL;      	/* DRVLOG打印等级 4Byte */
	BSP_U32 RESERVE7;           	/* 保留,4Byte */

	/*PMU NV项配置*/
	PMU_CFG_STRU PMU_CFG;
	BSP_U32 PMU_CRC32;	     /* PMU CRC校验,4Byte */

	/* 保留,剩余23(*)4Byte */
	BSP_U32 RESERVE41;
	BSP_U32 RESERVE42;
	BSP_U32 RESERVE43;
	BSP_U32 RESERVE44;
	BSP_U32 RESERVE45;
	BSP_U32 RESERVE46;
	BSP_U32 RESERVE47;
	BSP_U32 RESERVE48;
	BSP_U32 RESERVE49;
	BSP_U32 RESERVE50;
	BSP_U32 RESERVE51;
	BSP_U32 RESERVE52;
	BSP_U32 RESERVE53;
	BSP_U32 RESERVE54;
	BSP_U32 RESERVE55;
	BSP_U32 RESERVE56;
	BSP_U32 RESERVE57;
	BSP_U32 RESERVE58;
	BSP_U32 RESERVE59;
	BSP_U32 RESERVE60;
	BSP_U32 RESERVE61;
	BSP_U32 RESERVE62;
	BSP_U32 ANT_MODE;
}NV_HW_CONFIG_STRU;

/*****************************************************************************
 枚举名    : UART_SWITCH_ENUM
 枚举说明  : UART特性是否使能

  1.日    期   : 2013年12月19日
    作    者   : f00204170
    修改内容   : UART项目新增
*****************************************************************************/
enum UART_SWITCH_ENUM
{
    UART_SWITCH_DISABLE = 0,
    UART_SWITCH_ENABLE  = 1,
    UART_SWITCH_BUTT
};

typedef BSP_U8 UART_SWITCH_ENUM_UINT8;
/*****************************************************************************
 结构名    : NV_UART_SWITCH_STRU
 协议表格  : 无
 结构说明  :  用于记录UART功能是否处于使能状态

 修改历史      :
  1.日    期   : 2013年12月19日
    作    者   : f00204170
    修改内容   :
*****************************************************************************/
typedef struct
{
    UART_SWITCH_ENUM_UINT8  enUartEnableCfg;
    BSP_U8  uartRsv[3];
}NV_UART_SWITCH_STRU;

/*****************************************************************************
 结构名    : KPD_NV_VERSION_1_1_T
 结构说明  : KPD_NV_VERSION_1_1_T结构
*****************************************************************************/
typedef struct
{
    BSP_U32  ulversion;                    /* Should be 0x0001_0000. major + minor */
    BSP_U32  ulkeyupdatetime;              /* 0 means not support. non-zero is the update check time */
    BSP_U32  ultickunit;                   /* the tick unit. ms */
    BSP_U32  ulitemtable[ KPD_EVENT_MAX ]; /* sizeof(versio_1_1) = 64bytes */
}KPD_NV_VERSION_1_1_T;                     /* version 1.1 structure */

/*****************************************************************************
 结构名    : HWIFI_TARGET_ASSERT_ENABLE_STRU
 结构说明  : HWIFI_TARGET_ASSERT_ENABLE结构
*****************************************************************************/
typedef struct
{
    BSP_U32   WIFI_TARGET_ASSERT_ENABLE;
}HWIFI_TARGET_ASSERT_ENABLE_STRU;


/*****************************************************************************
 结构名    : HILINK_AUTORUN_FLAG_STRU
 结构说明  : HILINK_AUTORUN_FLAG结构
*****************************************************************************/
typedef struct
{
    BSP_U16   HILINK_AUTORUN_FLAG;
}HILINK_AUTORUN_FLAG_STRU;

/*****************************************************************************
 结构名    : VBAT_CALIBART_TYPE
 结构说明  : 电池校准参数数据结构
*****************************************************************************/
typedef struct
{
    BSP_U16 min_value;
    BSP_U16 max_value;
}VBAT_CALIBART_TYPE;

/*****************************************************************************
 结构名    : NV_FACTORY_INFO_I_STRU
 结构说明  : NV_FACTORY_INFO_I结构
*****************************************************************************/
typedef struct
{
    BSP_CHAR aucFactoryInfo[NV_FACTORY_INFO_I_SIZE];
}NV_FACTORY_INFO_I_STRU;

/*****************************************************************************
 结构名    : NV_USB_LOG_SAVE_LEV
 结构说明  : NV_USB_LOG_SAVE_LEV结构
*****************************************************************************/
typedef struct
{
    BSP_U32 NV_USB_LOG_SAVE_LEV;
}NV_USB_LOG_SAVE_LEV_STRU;


/*****************************************************************************
 结构名    : DR_NV_ENHANCE_SIMCARD_LOCK_STATUS_STRU
 结构说明  : 增强的锁卡状态结构体   ID=8517
*****************************************************************************/
typedef struct
{
    BSP_U8  EnhanceSimcardStatus;     /* 增强的锁卡特性是否激活 0:不激活, 1: 激活 */
    BSP_U8  SimcardStatus;            /* SimCardLockStatus各种状态 1: 锁卡版本, 2: 非锁卡版本 */
}DR_NV_ENHANCE_SIMCARD_LOCK_STATUS_STRU;

/*****************************************************************************
 结构名    : NV_BREATH_LED_STR
 结构说明  : NV_BREATH_LED结构     ID=9051
*****************************************************************************/
typedef struct
{
    BSP_U8 ucBreathOnTime;
    BSP_U8 ucBreathOffTime;
    BSP_U8 ucBreathRiseTime;
    BSP_U8 ucBreathFallTime;
}NV_BREATH_LED_STR;

/*****************************************************************************
 结构名    : CHG_BATTERY_TEMP_PROTECT_NV_TYPE
 结构说明  : CHG_BATTERY_TEMP_PROTECT_NV_TYPE结构     ID=50016
*****************************************************************************/
typedef struct
{
    BSP_U32  ulIsEnable;
    BSP_S32  lCloseAdcThreshold;
    BSP_U32  ulTempOverCount;
}CHG_BATTERY_TEMP_PROTECT_NV_TYPE;

/*****************************************************************************
 结构名    : nv_huawei_connect_display_rate_type
 结构说明  : nv_huawei_connect_display_rate_type结构     ID=50027
*****************************************************************************/
typedef struct
{
    BSP_U8 gsm_connect_rate;
    BSP_U8 gprs_connect_rate;
    BSP_U8 edge_connect_rate;
    BSP_U8 wcdma_connect_rate;
    BSP_U8 hspda_connect_rate;
    BSP_U8 reserved;           /*对齐使用*/
}nv_huawei_connect_display_rate_type;


/*****************************************************************************
 结构名    : PROIDNvInfo
 结构说明  : PROIDNvInfo结构     ID=50018,ID=50048
*****************************************************************************/
typedef struct _productIDNvInfo
{
    BSP_U32   NvStatus;
    BSP_U8    ucCompVer[VER_MAX_LENGTH];
} PROIDNvInfo;

/*****************************************************************************
 结构名    : NV_HUAWEI_PCCW_HS_HSPA_BLUE_STRU
 结构说明  : NV_HUAWEI_PCCW_HS_HSPA_BLUE结构 ID=50032
*****************************************************************************/
typedef struct
{
    BSP_U32  NVhspa_hs_blue; /*Range:[0,3]*/
}NV_HUAWEI_PCCW_HS_HSPA_BLUE_STRU;


/*****************************************************************************
 结构名    : nvi_cust_pid_type
 结构说明  : nvi_cust_pid_type结构
*****************************************************************************/
typedef struct
{
    BSP_U32  nv_status;
    BSP_U16  cust_first_pid;
    BSP_U16  cust_rewind_pid;
}nvi_cust_pid_type;


/*****************************************************************************
 结构名    : nv_protocol_base_type
 结构说明  : nv_protocol_base_type结构
*****************************************************************************/
typedef struct
{
    BSP_U32  nv_status;
    BSP_U32  protocol_base;
}nv_protocol_base_type;

/*****************************************************************************
 结构名    : nv_huawei_dynamic_pid_type
 结构说明  : nv_huawei_dynamic_pid_type结构 ID=50091 端口形态
*****************************************************************************/
typedef struct PACKED_POST
{
    BSP_U32 nv_status;
    BSP_U8  first_port_style[DYNAMIC_PID_MAX_PORT_NUM];
    BSP_U8  rewind_port_style[DYNAMIC_PID_MAX_PORT_NUM];
    BSP_U8  reserved[22];
} nv_huawei_dynamic_pid_type;


/*****************************************************************************
 结构名    : USB_NV_SN_INFO_T
 结构说明  : USB_NV_SN_INFO_T结构
*****************************************************************************/
typedef struct tagUSB_NV_SN_INFO_T
{
    BSP_U32 u32USBNvState;
    BSP_U32 u32USBReserved1;
    BSP_U32 u32USBReserved2;
    BSP_U32 u32USBNvResult;
} USB_NV_SN_INFO_T;

/*****************************************************************************
 结构名    : USB_NV_DEV_INFO_T
 结构说明  : USB_NV_DEV_INFO_T结构
*****************************************************************************/
typedef struct tagUSB_NV_DEV_INFO_T
{
    BSP_U32 u32USBNvState;
    BSP_U32 u32USBDevTypeIdx;
    BSP_U32 u32USBReserved1;
    BSP_U32 u32USBReserved2;
/*    BSP_U32 u32USBNvResult;*/
} USB_NV_DEV_INFO_T;

/*****************************************************************************
 结构名    : USB_NV_SERIAL_NUM_T
 结构说明  : USB_NV_SERIAL_NUM_T结构
*****************************************************************************/
typedef struct tagUSB_NV_SERIAL_NUM_T
{
    BSP_U32 u32USBSerialNumSupp;
    BSP_U32 u32USBReserved1;
    BSP_U32 u32USBReserved2;
    BSP_U32 u32USBNvResult;
} USB_NV_SERIAL_NUM_T;

/*****************************************************************************
 结构名    : USB_NV_NEW_PID_INFO_T
 结构说明  : USB_NV_NEW_PID_INFO_T结构
*****************************************************************************/
typedef struct tagUSB_NV_NEW_PID_INFO_T
{
    BSP_U32 u32USBNewPidSupp;
} USB_NV_NEW_PID_INFO_T;

/*****************************************************************************
 结构名    : USB_NV_PID_UNION_T
 结构说明  : USB_NV_PID_UNION_T结构
*****************************************************************************/
typedef struct tagUSB_NV_PID_UNION_T
{
    BSP_U32 u32USBNvState;
    BSP_U32 u32USBProtOfs;   /* change from "u32USBVDFCust" to "u32USBProtOfs" */
    BSP_U32 u32USBCdromPid;
    BSP_U32 u32USBUniquePid;
} USB_NV_PID_UNION_T;

/*****************************************************************************
 结构名    : USB_NV_DEV_PROFILE_T
 结构说明  : USB_NV_DEV_PROFILE_T结构
*****************************************************************************/
typedef struct tagUSB_NV_DEV_PROFILE_T
{
    BSP_U32 u32USBNvState;
    BSP_U8  u8USBFirstPortSeq[DYN_MAX_PORT_CNT];
    BSP_U8  u8USBMultiPortSeq[DYN_MAX_PORT_CNT];
    BSP_U8  u8USBPortReserved[2];
} USB_NV_DEV_PROFILE_T;


/*****************************************************************************
 结构名    : NV_SECBOOT_ENABLE_FLAG
 结构说明  : NV_SECBOOT_ENABLE_FLAG结构 ID=50201
*****************************************************************************/
typedef struct
{
    BSP_U16 usNVSecBootEnableFlag; /*Range:[0,1]*/
}NV_SECBOOT_ENABLE_FLAG;


/*****************************************************************************
 结构名    : nv_wifibs_type
 结构说明  : nv_wifibs_type结构
*****************************************************************************/
typedef struct
{
    BSP_U8   aucwlSsid[NV_WLSSID_LEN];
    BSP_U32  ulwlChannel;
    BSP_U32  ulwlHide;
    BSP_U8   aucwlCountry[NV_WLCOUNTRY_CODE_LEN];
    BSP_U8   aucwlMode[NV_WLMODE_LEN];
    BSP_U32  ulwlRate;
    BSP_U32  ulwlTxPwrPcnt;
    BSP_U32  ulwlMaxAssoc;
    BSP_U8   ucwlEnbl;
    BSP_U32  ulwlFrgThrshld;
    BSP_U32  ulwlRtsThrshld;
    BSP_U32  ulwlDtmIntvl;
    BSP_U32  ulwlBcnIntvl;
    BSP_U32  ulwlWme;
    BSP_U32  ulwlPamode;
    BSP_U32  ulwlIsolate;
    BSP_U32  ulwlProtectionmode;
    BSP_U32  ulwloffenable;
    BSP_U32  ulwlofftime;
    BSP_U8   aucwlExtends[12];
}nv_wifibs_type;


/*****************************************************************************
 结构名    : CHG_BATTERY_LOW_TEMP_PROTECT_NV
 结构说明  : CHG_BATTERY_LOW_TEMP_PROTECT_NV结构 ID=52005
*****************************************************************************/
typedef struct
{
    BSP_U32  ulIsEnable;
    BSP_S32  lCloseAdcThreshold;
    BSP_U32  ulTempLowCount;
}CHG_BATTERY_LOW_TEMP_PROTECT_NV;

/*****************************************************************************
 结构名    : NV_SCI_CFG_STRU
 结构说明  : NV_SCI_CFG结构 ID=128
*****************************************************************************/
typedef struct
{
    BSP_U32 value;
} NV_SCI_CFG_STRU;

/*****************************************************************************
 结构名    : NV_GCF_TYPE_CONTENT_STRU
 结构说明  : NV_GCF_TYPE_CONTENT结构 ID=8250
*****************************************************************************/
typedef struct
{
    BSP_U8 GCFTypeContent[4];
}NV_GCF_TYPE_CONTENT_STRU;

/*****************************************************************************
 结构名    : nv_wifi_info
 结构说明  : nv_wifi_info结构
*****************************************************************************/
typedef struct
{
    BSP_U32 ulOpSupport;
    BSP_U8  usbHighChannel;
    BSP_U8  usbLowChannel;
    BSP_U8  aucRsv1[2];
    BSP_U16 ausbPower[2];
    BSP_U8  usgHighsChannel;
    BSP_U8  usgLowChannel;
    BSP_U8  aucRsv2[2];
    BSP_U16 ausgPower[2];
    BSP_U8  usnHighsChannel;
    BSP_U8  usnLowChannel;
    BSP_U8  ausnRsv3[2];
    BSP_U16 ausnPower[2];
}nv_wifi_info;

/*****************************************************************************
 结构名    : NV_ITEM_USB_PKT_HOOK_STRU
 结构说明  : NV_ITEM_USB_PKT_HOOK结构 ID=119
*****************************************************************************/
typedef struct
{
    BSP_U16 usUsbPktHookFlag;
}NV_ITEM_USB_PKT_HOOK_STRU;   /*USB勾包NV控制项*/

/*****************************************************************************
 结构名    : TEM_VOLT_TABLE
 结构说明  : TEM_VOLT_TABLE结构
*****************************************************************************/
typedef struct tem_volt_table
{
    BSP_S16   temperature;
    BSP_U16   voltage;
}TEM_VOLT_TABLE;

/*****************************************************************************
 结构名    : UE_POINT_CTRL_STRU
 结构说明  : UE_POINT_CTRL结构 ID=15
*****************************************************************************/
typedef struct
{
    BSP_U32     Status;
    BSP_U32     ProductForm;
    BSP_U16     Pid;
    BSP_U16     FakePid;
    BSP_U8      Mac[8];
}UE_POINT_CTRL_STRU;

/*****************************************************************************
 结构名    : NV_CUSTOMIZE_REWIND_DELAY_TIME_I_STRU
 结构说明  : NV_CUSTOMIZE_REWIND_DELAY_TIME_I结构 ID=25
*****************************************************************************/
typedef struct
{
    BSP_U32     Status;    /*Range:[0,1]*/
    BSP_U16     Timeout;
}NV_CUSTOMIZE_REWIND_DELAY_TIME_I_STRU;

/*****************************************************************************
 结构名    : NV_OLED_TEMP_ADC_STRU
 结构说明  : NV_OLED_TEMP_ADC结构
*****************************************************************************/
typedef struct
{
    BSP_S16       sTemp;
    BSP_S16       sADC;
}NV_OLED_TEMP_ADC_STRU;

/*****************************************************************************
 结构名    : NV_OLED_TEMP_ADC_STRU_ARRAY
 结构说明  : NV_OLED_TEMP_ADC_STRU_ARRAY结构  ID=49
*****************************************************************************/
typedef struct
{
    NV_OLED_TEMP_ADC_STRU          stNV_OLED_TEMP_ADC[28];
}NV_OLED_TEMP_ADC_STRU_ARRAY;

/*****************************************************************************
 结构名    : NV_SW_VER_STRU
 结构说明  : NV_SW_VER结构
*****************************************************************************/
typedef struct
{
    BSP_S32        nvStatus;
    BSP_S8         nv_version_info[30];
}NV_SW_VER_STRU;

/*****************************************************************************
 结构名    : NV_TCXO_CFG_STRU
 结构说明  : NV_TCXO_CFG结构 ID=9217
*****************************************************************************/
typedef struct
{
    BSP_U32 tcxo_cfg;
}NV_TCXO_CFG_STRU;

/*****************************************************************************
 结构名    : NV_KADC_PHYTOLOGICAL_CONFIGTCXO_CFG_STRU
 结构说明  : NV_KADC_PHYTOLOGICAL_CONFIGTCXO_CFG结构 ID=9216
*****************************************************************************/
typedef struct
{
    BSP_U16 hkadc[14];
}NV_KADC_PHYTOLOGICAL_CONFIGTCXO_CFG_STRU;

/*****************************************************************************
 结构名    : NV_THERMAL_HKADC_CONFIG
 结构说明  : NV_THERMAL_HKADC_CONFIG结构 ID=9232
*****************************************************************************/
typedef struct
{
    BSP_U16 hkadc[32];
}NV_KADC_CHANNEL_CFG_STRU;
typedef struct
{
    BSP_U32   outconfig;
    BSP_U16   outperiod;
    BSP_U16   convertlistlen;
    BSP_U32   reserved[2];
}NV_THERMAL_HKADC_CONFIG;

/*****************************************************************************
 结构名    : NV_THERMAL_HKADC_CONFIG_STRU
 结构说明  : NV_THERMAL_HKADC_CONFIG结构 ID=9215
*****************************************************************************/
typedef struct
{
    NV_THERMAL_HKADC_CONFIG   hkadcCfg[14];
}NV_THERMAL_HKADC_CONFIG_STRU;

/*****************************************************************************
 结构名    : NV_THERMAL_BAT_CONFIG_STRU
 结构说明  : NV_THERMAL_BAT_CONFIG结构 ID=9214
*****************************************************************************/
typedef struct
{
    BSP_U16       enable;
    BSP_U16       hkadcid;
    BSP_S16       highthres;
    BSP_U16       highcount;
    BSP_S16       lowthres;
    BSP_U16       lowcount;
    BSP_U32       reserved[2];

}NV_THERMAL_BAT_CONFIG_STRU;

/*****************************************************************************
 结构名    : NV_THERMAL_TSENSOR_CONFIG_STRU
 结构说明  : NV_THERMAL_TSENSOR_CONFIG结构 ID=9213
*****************************************************************************/
typedef struct
{
    BSP_U32       enable;
    BSP_U32       lagvalue0;
    BSP_U32       lagvalue1;
    BSP_U32       thresvalue0;
    BSP_U32       thresvalue1;
    BSP_U32       rstthresvalue0;
    BSP_U32       rstthresvalue1;
    BSP_U32       alarmcount1;
    BSP_U32       alarmcount2;
    BSP_U32       resumecount;
    BSP_U32       acpumaxfreq;
    BSP_U32       gpumaxfreq;
    BSP_U32       ddrmaxfreq;
    BSP_U32       reserved[4];
}NV_THERMAL_TSENSOR_CONFIG_STRU;

/*****************************************************************************
 结构名    : NV_TUNER_MIPI_INIT_CONFIG_STRU
 结构说明  : NV_TUNER_MIPI_INIT_CONFIG_STRU结构 ID=10046
*****************************************************************************/
#define TUNER_USER_DATA_MAX_NUM (9)
#define TUNER_MAX_NUM           (2)
typedef struct
{
    BSP_U8 mipiChan;
    BSP_U8 validNum;
    BSP_U16 cmdFrame[TUNER_USER_DATA_MAX_NUM];
    BSP_U16 dataFrame[TUNER_USER_DATA_MAX_NUM];
}NV_TUNER_MIPI_FRAME_CONFIG_STRU;

typedef struct
{
    NV_TUNER_MIPI_FRAME_CONFIG_STRU RFInitReg[TUNER_MAX_NUM];
}NV_GU_RF_FEND_MIPI_INIT_CONFIG_STRU;
/*****************************************************************************
 结构名    : WG_DRX_RESUME_TIME_STRU
 结构说明  : WG_DRX_RESUME_TIME_STRU结构 ID=10031
*****************************************************************************/
typedef struct
{
    unsigned long ulAbbPwrRsmTime;
    unsigned long ulRfPwrRsmTime;
    unsigned long ulAntSwitchPwrRsmTime;
    unsigned long ulAbbWpllRsmTime;
    unsigned long ulAbbGpllRsmTime;
    unsigned long ulBbpPllRsmTime;
    unsigned long ulPaStarRsmTime;
    unsigned long ulSysProtectTime;
    unsigned long ulTcxoRsmTime;
    unsigned long ulDcxoRsmTime;
    unsigned long ulSlowToMcpuRsmTime;
    unsigned long ulWphyRsmTime;
    unsigned long ulGphyRsmTime;
    unsigned long ulTaskSwitchRsmTime;
    unsigned long ulPaPwrRsmTime;
}WG_DRX_RESUME_TIME_STRU;

/*****************************************************************************
 结构名    : NV_NPNP_CONFIG_INFO
 结构说明  : NV_NPNP_CONFIG_INFO
*****************************************************************************/
typedef struct
{
    BSP_U32 npnp_open_flag;                           /* NPNP 特性一级NV开关, 0为未开启不可以使用, 1为开启可以使用 */
    BSP_U32 npnp_enable_flag;                         /* NPNP 特性二级NV项, 0为特性未使能, 1为特性使能             */
}NV_NPNP_CONFIG_INFO;
/*****************************************************************************
 结构名    : NV_RF_GPIO_CFG_STRU
 结构说明  : RF_GPIO中有若干可以复用为DRV_GPIO
             在一些射频功能场景需要改变这些RF_GPIO引脚的复用功能及输出状态
             通过该NV配置 ID=10047
*****************************************************************************/
typedef struct
{
    BSP_U16 is_used;    /*Range:[0,1]*/
	BSP_U16 gpio_level; /*Range:[0,1]*/
}RF_MODEM_CONTROL;
typedef struct
{
    BSP_U32 rf_gpio_num;
    RF_MODEM_CONTROL modem_inside;
    RF_MODEM_CONTROL modem_outside;
}RF_GPIO_CFG;
typedef struct
{
    RF_GPIO_CFG rf_switch_cfg[16];
}NV_RF_SWITCH_CFG_STRU;
/*****************************************************************************
 结构名    : NV_RF_ANT_OTG_CFG_STRU
 结构说明  : 主、副卡的天线热拔插功能需要根据不同的产品形态决定是否打开，能够
             通过该NV配置，并且通过该NV配置使用哪一根GPIO引脚作为中断输入
             ID=10051
*****************************************************************************/
typedef struct
{
    BSP_U16 ANT0_GPIO_NUM;
    BSP_U16 ANT1_GPIO_NUM;
}NV_RF_ANT_OTG_CFG_STRU;

/*****************************************************************************
 结构名    : NV_T1_CTRL_PARA_STRU
 结构说明  : NV_T1_CTRL_PARA_STRU ID=71
*****************************************************************************/
typedef struct
{
    BSP_U32             TMode;
    BSP_U32             enEDM;
    BSP_U32             aulRsv[4];
}NV_T1_CTRL_PARA_STRU;

/*****************************************************************************
 结构名    : NV_PRODUCT_TYPE_FOR_LOG_DIRECTORY
 结构说明  : NV_PRODUCT_TYPE_FOR_LOG_DIRECTORY ID=148
*****************************************************************************/
typedef struct
{
    BSP_U16         usProductType;/*0:MBB V3R3 stick/E5,etc.; 1:V3R3 M2M & V7R2; 2:V9R1 phone; 3:K3V3&V8R1;*/
    BSP_U16         usRsv;
}NV_PRODUCT_TYPE_FOR_LOG_DIRECTORY;

/*****************************************************************************
 结构名    : UCOM_NV_NV_ITEM_XO_DEFINE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 单时钟类型定义 ID=10056
*****************************************************************************/
typedef struct
{
    BSP_U16      enSingleXoType;                     /* 单时钟是否使能,0:不支持，1:单tcxo，2:单dcxo */
    BSP_U16      en32kType;                          /* 0:32000,1:32764，2:32768*/
}DRV_NV_SINGLE_XO_DEFINE_STRU;
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








#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of DrvNvInterface.h */
